# Plugins / LiveLink

- module root: `Plugins/Animation/LiveLink/Source/LiveLink`
- headers: 47; symbols: 1352
- symbol kinds: class=55, delegate=9, enum=7, enumerator=21, function=113, macro=31, member=457, namespace=9, prototype=618, struct=26, typedef=5, variable=1
- PrivateDependencyModuleNames: AnimationCore, CinematicCamera, HeadMountedDisplay, InputCore, LiveLinkAnimationCore, Media, MessageLog, Messaging, Projects, Slate, SlateCore, TimeManagement, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, LiveLinkInterface, LiveLinkMessageBusFramework

### `Plugins/Animation/LiveLink/Source/LiveLink/Private/ClientNetworkStatisticsModel.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace LiveLinkHub` (scope `UE`)
- L11 _namespace_ `namespace FClientNetworkStatisticsModel` (scope `UE::LiveLinkHub`)
- L13 _prototype_ `TOptional<FMessageTransportStatistics> GetLatestNetworkStatistics(const FMessageAddress& ClientAddress);` (scope `UE::LiveLinkHub::FClientNetworkStatisticsModel`)
- L14 _prototype_ `bool IsOnline(const FMessageAddress& ClientAddress);` (scope `UE::LiveLinkHub::FClientNetworkStatisticsModel`)

### `Plugins/Animation/LiveLink/Source/LiveLink/Private/LiveLinkBroadcastSubsystem.h` (Private)


#### class `ULiveLinkBroadcastSubsystem`  
`class ULiveLinkBroadcastSubsystem : public UEngineSubsystem`  
_L17-37_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- desc: Subsystem used primarily by the LiveLinkBroadcastComponent to rebroadcast a skeletal mesh on the network.
- L23 _public prototype_ `FLiveLinkSubjectKey CreateSubject(FName SubjectName, TSubclassOf<ULiveLinkRole> Role);` — Create a broadcast subject with a given subject name.
- L26 _public prototype_ `void RemoveSubject(const FLiveLinkSubjectKey& SubjectKey);` — Remove a LiveLink s
- L29 _public prototype_ `void BroadcastStaticData(const FLiveLinkSubjectKey& SubjectKey, TSubclassOf<ULiveLinkRole> Role, FLiveLinkStaticDataStruct&& StaticData) const;` — Broadcast static data for a subject.
- L32 _public prototype_ `void BroadcastFrameData(const FLiveLinkSubjectKey& SubjectKey, FLiveLinkFrameDataStruct&& FrameData) const;` — Broadcast frame data for a subject.
- L36 _private member_ `FGuid VirtualSourceGUID;` — ID of the source used to rebroadcast the data.

### `Plugins/Animation/LiveLink/Source/LiveLink/Private/LiveLinkDebugCommand.h` (Private)


#### class `FLiveLinkDebugCommand`  
`class FLiveLinkDebugCommand`  
_L11-31_
- L14 _public prototype_ `FLiveLinkDebugCommand(FLiveLinkClient& InClient);`
- L17 _private prototype_ `void ShowDebugInfo();`
- L18 _private prototype_ `void HideDebugInfo();`
- L21 _private member_ `FLiveLinkClient& Client;`
- L24 _private member_ `TUniquePtr<FAutoConsoleCommand> CommandShow;`
- L25 _private member_ `TUniquePtr<FAutoConsoleCommand> CommandHide;`
- L28 _private member_ `bool bRenderDebugInfo;`
- L29 _private member_ `TWeakPtr<SLiveLinkDebugView> DebugViewEditor;`
- L30 _private member_ `TWeakPtr<SLiveLinkDebugView> DebugViewGame;`

### `Plugins/Animation/LiveLink/Source/LiveLink/Private/LiveLinkDebugView.h` (Private)


#### class `SLiveLinkDebugView`  
`class SLiveLinkDebugView : public SCompoundWidget`  
_L18-50_
- inherits: `SCompoundWidget`
- L20 _private function_ `SLATE_BEGIN_ARGS(SLiveLinkDebugView)`
- L23 _private prototype_ `virtual ~SLiveLinkDebugView() override;`
- L25 _private prototype_ `void Construct(const FArguments& Args, FLiveLinkClient* InClient);`
- L28 _private prototype_ `TSharedRef<ITableRow> GenerateRow(FLiveLinkDebugUIEntryPtr Data, const TSharedRef<STableViewBase>& OwnerTable);`
- L29 _private prototype_ `void HandleSourcesChanged();`
- L30 _private prototype_ `void RefreshSourceItems();`
- L32 _private prototype_ `const FSlateBrush* GetSubjectIcon(FLiveLinkDebugUIEntryPtr SubjectEntry) const;` — Get the subject icon according to the subject's status.
- L35 _private member_ `FLiveLinkClient* Client;`
- L36 _private member_ `TArray<FLiveLinkDebugUIEntryPtr> DebugItemData;`
- L38 _private member_ `TSharedPtr<SListView<FLiveLinkDebugUIEntryPtr>> DebugItemView;`
- L39 _private member_ `TSharedPtr<FSlateColorBrush> BackgroundBrushSource;`
- L40 _private member_ `TSharedPtr<FSlateColorBrush> BackgroundBrushSubject;`
- L43 _private member_ `const FSlateBrush* ValidBrush = nullptr;` — Cached brush for valid subjects.
- L45 _private member_ `const FSlateBrush* InvalidBrush = nullptr;` — Cached brush for invalid subjects.
- L47 _private member_ `const FSlateBrush* PausedBrush = nullptr;` — Cached brush for paused subjects.
- L49 _private member_ `const FSlateBrush* DisabledBrush = nullptr;` — Cached brush for disabled subjects

#### Free symbols / members of external scopes

- L16 _typedef_ `using FLiveLinkDebugUIEntryPtr = TSharedPtr<FLiveLinkDebugUIEntry>;`

### `Plugins/Animation/LiveLink/Source/LiveLink/Private/LiveLinkHeartbeatEmitter.h` (Private)


#### class `FLiveLinkHeartbeatEmitter`  
`class FLiveLinkHeartbeatEmitter : public FRunnable`  
_L22-64_
- inherits: `FRunnable`
- desc: Sends out heartbeat signals at the rate defined by LiveLinkSettings::MessageBusHeartbeatFrequency to all recipients. Recipients for the heartbeat can be added by calling StartHeartbeat(). On the first call to StartHeartbeat a thread is spawned that keeps sending the heartbeat to everyone. The heartbeats and the sender thread can be stopped by calling Exit().
- L25 _public prototype_ `FLiveLinkHeartbeatEmitter();`
- L26 _public prototype_ `~FLiveLinkHeartbeatEmitter();`
- L33 _public prototype_ `void StartHeartbeat(const FMessageAddress& RecipientAddress, const TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe>& MessageEndpoint);` — Start sending a heartbeat to the specified Recipient by using the given MessageEndpoint. @note This will spawn a new thread when first called. @note It is assumed that each source that sends out heartbeats has its own MessageEndpoint.
- L38 _public prototype_ `void StopHeartbeat(const FMessageAddress& RecipientAddress, const TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe>& MessageEndpoint);` — Stop sending a heartbeat to the specified Recipient.
- L44 _public prototype_ `virtual uint32 Run() override;` — FRunnable Interface
- L45 _public prototype_ `virtual void Exit() override;`
- L57 _private member_ `mutable FCriticalSection CriticalSection;`
- L58 _private member_ `TArray<FHeartbeatRecipient> HeartbeatRecipients;`
- L59 _private member_ `FThreadSafeBool bIsRunning;`
- L60 _private member_ `float HeartbeatFrequencyInMs;`
- L62 _private member_ `FEvent* HeartbeatEvent;`
- L63 _private member_ `TUniquePtr<FRunnableThread> Thread;`

#### struct `FLiveLinkHeartbeatEmitter::FHeartbeatRecipient`  
`struct FHeartbeatRecipient`  
_L48-54_
- L50 _public member_ `TWeakPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;`
- L51 _public member_ `FMessageAddress ConnectionAddress;`
- L53 _public prototype_ `bool operator==(const FHeartbeatRecipient& other) const;`

### `Plugins/Animation/LiveLink/Source/LiveLink/Private/LiveLinkLogInstance.h` (Private)


#### class `FLiveLinkLogInstance`  
`class FLiveLinkLogInstance : public FLiveLinkLog`  
_L16-129_
- inherits: `FLiveLinkLog`
- L19 _public prototype_ `static void CreateInstance();`
- L20 _public prototype_ `static void DestroyInstance();`
- L24 _public prototype_ `static bool IsMessageEnabled(FName MessageID);` — Is the message ID is enabled.
- L27 _public prototype_ `static void SetEnableMessage(FName MessageID, bool bEnabled);` — Set if a Message ID is enabled.
- L30 _public prototype_ `static void SetSilent(bool bSilentMode);` — Set if we should log the message.
- L33 _public prototype_ `static void SetLogRepeatedMessage(bool bLog);` — Set if we should log all the message even if they are not the log for the first time.
- L35 _public prototype_ `virtual TPair<int32, FTimespan> GetOccurrence(FName MessageID, FLiveLinkSubjectKey SubjectKey) const override;`
- L36 _public prototype_ `virtual TPair<int32, FTimespan> GetSelectedOccurrence() const override;`
- L37 _public prototype_ `virtual void GetLogCount(int32& OutErrorCount, int32& OutWarningCount, int32& OutInfoCount) const override;`
- L40 _private prototype_ `FLiveLinkLogInstance();`
- L41 _private prototype_ `~FLiveLinkLogInstance();`
- L42 _private prototype_ `FLiveLinkLogInstance(const FLiveLinkLogInstance&) = delete;`
- L43 _private prototype_ `FLiveLinkLogInstance& operator=(const FLiveLinkLogInstance&) = delete;`
- L46 _protected prototype_ `virtual void LogMessage(EMessageSeverity::Type Severity, FName MessageID, const FLiveLinkSubjectKey& SubjectKey, FString&& Message) override;`
- L47 _protected prototype_ `virtual TSharedPtr<FTokenizedMessage> CreateTokenizedMessage(EMessageSeverity::Type Severity, FName MessageID, const FLiveLinkSubjectKey& SubjectKey, FString&& Message) override;`
- L69 _private prototype_ `void Update();`
- L70 _private prototype_ `FRepeatableMessage* FindRepeatableMessage(FName MessageID, const FLiveLinkSubjectKey& SubjectKey);`
- L71 _private prototype_ `const FRepeatableMessage* FindRepeatableMessage(FName MessageID, const FLiveLinkSubjectKey& SubjectKey) const;`
- L73 _private prototype_ `void LogMessage(EMessageSeverity::Type Severity, const FString& Message);`
- L74 _private prototype_ `void IncrementLogCount(EMessageSeverity::Type Severity);`
- L76 _private function_ `bool IsMessageEnabled_Internal(FName MessageID)`
- L81 _private prototype_ `void SetEnableMessage_Internal(FName MessageID, bool bEnabled);`
- L84 _private prototype_ `void OnSelectionChanged();`
- L85 _private prototype_ `void OnDataChanged();`
- L90 _private member_ `mutable FCriticalSection CriticalSection;` — Critical section for synchronizing access to the different list.
- L93 _private member_ `TArray<TSharedRef<FTokenizedMessage>> ToUpdateMessages;` — List of tokenized messages.
- L96 _private member_ `TArray<FRepeatableMessage> RepeatableMessages;` — List of all repeatable messages.
- L100 _private member_ `TSharedPtr<IMessageLogListing> LogListing;` — Listing used in the editor by the Message Log.
- L103 _private member_ `TPair<int32, FTimespan> SelectedMessageOccurrence;` — Last selected message occurrence.
- L106 _private member_ `TWeakPtr<FTokenizedMessage> SelectedToken;` — Last selected message.
- L110 _private member_ `TArray<FName> DisabledMessages;` — Disabled messages ID.
- L113 _private member_ `TAtomic<int32> ErrorCount;` — Number of error.
- L116 _private member_ `TAtomic<int32> WarningCount;` — Number of warning.
- L119 _private member_ `TAtomic<int32> InfoCount;` — Number of info.
- L122 _private member_ `bool bSilentMode = false;` — Should we be silent?
- L125 _private member_ `bool bLogAllRepeatableMessage = false;` — Should we all instance of the repeatable message or only the first one and last one?
- L128 _private member_ `double HighPerformanceClockDelta;` — Delta time between the fast clock and slow clock.

#### struct `FLiveLinkLogInstance::FRepeatableMessageData`  
`struct FRepeatableMessageData`  
_L50-58_
- L52 _public member_ `TAtomic<FTimespan> LastTimeOccured;`
- L53 _public member_ `TAtomic<int32> Occurrence;`
- L55 _public function_ `FRepeatableMessageData() : Occurrence(0)`

#### struct `FLiveLinkLogInstance::FRepeatableMessage`  
`struct FRepeatableMessage`  
_L60-66_
- L62 _public member_ `FName MessageID;`
- L63 _public member_ `FLiveLinkSubjectKey SubjectKey;`
- L64 _public member_ `TSharedRef<FRepeatableMessageData> Data;`
- L65 _public member_ `TWeakPtr<FTokenizedMessage> Token;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace EMessageSeverity`

### `Plugins/Animation/LiveLink/Source/LiveLink/Private/LiveLinkModule.h` (Private)


#### class `FLiveLinkModule`  
`class FLiveLinkModule : public ILiveLinkModule`  
_L19-74_
- inherits: `ILiveLinkModule`
- L22 _public prototype_ `FLiveLinkModule();`
- L25 _public prototype_ `virtual void StartupModule() override;`
- L26 _public prototype_ `virtual void ShutdownModule() override;`
- L27 _public function_ `virtual bool SupportsDynamicReloading() override`
- L31 _public function_ `virtual FLiveLinkHeartbeatEmitter& GetHeartbeatEmitter() override`
- L33 _public function_ `virtual FLiveLinkMessageBusDiscoveryManager& GetMessageBusDiscoveryManager() override`
- L35 _public function_ `virtual TSharedPtr<FSlateStyleSet> GetStyle() override`
- L37 _public prototype_ `virtual FDelegateHandle RegisterMessageBusSourceFilter(const FOnLiveLinkShouldDisplaySource& SourceFilter) override;`
- L38 _public prototype_ `virtual void UnregisterMessageBusSourceFilter(FDelegateHandle Handle) override;`
- L40 _public function_ `virtual const TMap<FDelegateHandle, FOnLiveLinkShouldDisplaySource>& GetSourceFilters() const override`
- L45 _public function_ `virtual FOnSubjectOutboundNameModified& OnSubjectOutboundNameModified() override`
- L53 _private prototype_ `void CreateStyle();`
- L54 _private prototype_ `void OnEngineLoopInitComplete();`
- L58 _private member_ `static FLiveLinkClient* LiveLinkClient_AnyThread;`
- L60 _private member_ `FLiveLinkClient LiveLinkClient;`
- L61 _private member_ `FLiveLinkMotionController LiveLinkMotionController;`
- L63 _private member_ `TSharedPtr<FSlateStyleSet> StyleSet;`
- L65 _private member_ `TUniquePtr<FLiveLinkHeartbeatEmitter> HeartbeatEmitter;`
- L66 _private member_ `TUniquePtr<FLiveLinkMessageBusDiscoveryManager> DiscoveryManager;`
- L67 _private member_ `TUniquePtr<FLiveLinkDebugCommand> LiveLinkDebugCommand;`
- L70 _private member_ `TMap<FDelegateHandle, FOnLiveLinkShouldDisplaySource> RegisteredSourceFilters;` — Filters registered externally used to filter what message bus sources should be displayed in the UI.
- L73 _private member_ `FOnSubjectOutboundNameModified OutboundNameModifiedDelegate;` — Delegate called by LiveLinkHubSubjectSettings to notify the hub of an outbound name change.

### `Plugins/Animation/LiveLink/Source/LiveLink/Private/LiveLinkMotionController.h` (Private)


#### class `FLiveLinkMotionController`  
`class FLiveLinkMotionController : public IMotionController`  
_L16-219_
- inherits: `IMotionController`
- L31 _private member_ `TArray<FLiveLinkMotionControllerEnumeratedSource> EnumeratedSources;` — Built array of Live Link Sources to give to Motion Controller system
- L34 _public function_ `FLiveLinkMotionController(FLiveLinkClient& InClient) : Client(InClient)`
- L41 _public function_ `~FLiveLinkMotionController()`
- L47 _public function_ `void RegisterController()`
- L52 _public function_ `void UnregisterController()`
- L57 _public function_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const FName MotionSource, FRotator& OutOrientation, FVector& OutPosition, float) const override`
- L74 _public function_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const FName MotionSource, FRotator& OutOrientation, FVector& OutPosition, bool& OutbProvidedLinearVelocity, FVector& OutLinearVelocity, bool& OutbProvidedAngularVelocity, FVector& OutAngularVelocityAsAxisAndLength, bool& OutbProvidedLinearAcceleration, FVector& OutLinearAcceleration, float WorldToMetersScale) const override`
- L82 _public function_ `virtual bool GetControllerOrientationAndPositionForTime(const int32 ControllerIndex, const FName MotionSource, FTimespan Time, bool& OutTimeWasUsed, FRotator& OutOrientation, FVector& OutPosition, bool& OutbProvidedLinearVelocity, FVector& OutLinearVelocity, bool& OutbProvidedAngularVelocity, FVector& OutAngularVelocityAsAxisAndLength, bool& OutbProvidedLinearAcceleration, FVector& OutLinearAcceleration, float WorldToMetersScale) const override`
- L91 _public function_ `float GetCustomParameterValue(const FName MotionSource, FName ParameterName, bool& bValueFound) const override`
- L115 _public function_ `virtual ETrackingStatus GetControllerTrackingStatus(const int32 ControllerIndex, const FName MotionSource) const override`
- L128 _public function_ `virtual FName GetMotionControllerDeviceTypeName() const override`
- L135 _public function_ `void BuildSourceData()` — Builds cached source data for passing to motion controller system
- L182 _public function_ `virtual void EnumerateSources(TArray<FMotionControllerSource>& Sources) const override`
- L195 _public function_ `virtual bool GetHandJointPosition(const FName MotionSource, int jointIndex, FVector& OutPosition) const override`
- L198 _private function_ `FLiveLinkSubjectKey GetSubjectKeyFromMotionSource(FName MotionSource) const`
- L209 _private function_ `void OnSubjectsChangedHandler()` — Registered with the client and called when client's subjects change
- L212 _private member_ `FLiveLinkClient& Client;` — Reference to the live link client
- L215 _private member_ `FDelegateHandle OnSubjectsChangedHandle;` — Handle to delegate registered with client so we can update when subject state changes
- L218 _private member_ `FGuid WildcardSource;` — Wildcard source, we don't care about the source itself, just the subject name

#### struct `FLiveLinkMotionController::FLiveLinkMotionControllerEnumeratedSource`  
`struct FLiveLinkMotionControllerEnumeratedSource`  
_L19-28_
- desc: Internal structure for caching enumerated data
- L22 _public member_ `FLiveLinkSubjectKey SubjectKey;` — Subject key for talking to live link
- L25 _public member_ `FName MotionSource;` — MotionSource name for interacting with Motion Controller system
- L27 _public function_ `FLiveLinkMotionControllerEnumeratedSource(const FLiveLinkSubjectKey& Key, FName MotionSourceName) : SubjectKey(Key), MotionSource(MotionSourceName)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "LiveLinkMotionController"`
- L151 _typedef_ `typedef TPair<FGuid, FText> FHeaderEntry;` (scope `FLiveLinkMotionController::BuildSourceData`)
- L163 _function_ `Headers.Sort([CaptureWildcardSource](const FHeaderEntry& A, const FHeaderEntry& B) { return A.Key == CaptureWildcardSource || A.Value.CompareToCaseIgnored(B.Value) <= 0; });` (scope `FLiveLinkMotionController::BuildSourceData`)
- L200 _function_ `const FLiveLinkMotionControllerEnumeratedSource* EnumeratedSource = EnumeratedSources.FindByPredicate([&](const FLiveLinkMotionControllerEnumeratedSource& Item) { return Item.MotionSource == MotionSource; });` (scope `FLiveLinkMotionController::GetSubjectKeyFromMotionSource`)

### `Plugins/Animation/LiveLink/Source/LiveLink/Private/LiveLinkVirtualSource.h` (Private)


#### class `FLiveLinkVirtualSubjectSource`  
`class FLiveLinkVirtualSubjectSource : public ILiveLinkSource`  
_L16-36_
- inherits: `ILiveLinkSource`
- desc: Completely empty "source" that virtual subjects can hang off
- L19 _public prototype_ `FLiveLinkVirtualSubjectSource() = default;`
- L20 _public prototype_ `virtual ~FLiveLinkVirtualSubjectSource() = default;`
- L23 _public prototype_ `virtual bool CanBeDisplayedInUI() const override;`
- L24 _public prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;`
- L25 _public prototype_ `virtual void InitializeSettings(ULiveLinkSourceSettings* Settings) override;`
- L26 _public prototype_ `virtual bool IsSourceStillValid() const override;`
- L27 _public prototype_ `virtual bool RequestSourceShutdown() override;`
- L29 _public prototype_ `virtual FText GetSourceType() const override;`
- L30 _public prototype_ `virtual FText GetSourceMachineName() const override;`
- L31 _public prototype_ `virtual FText GetSourceStatus() const override;`
- L35 _protected member_ `FName SourceName;`

#### class `ULiveLinkVirtualSubjectSourceSettings`  
`class ULiveLinkVirtualSubjectSourceSettings : public ULiveLinkSourceSettings`  
_L40-48_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceSettings`
- desc: VirtualSubjectSource Settings to be able to differentiate from live sources and keep a name associated to the source
- L47 _public member_ `FName SourceName;` — `UPROPERTY()`

### `Plugins/Animation/LiveLink/Source/LiveLink/Private/Visualizers/LiveLinkMarkerVisualizer.h` (Private)


#### enum `EAxisSign`  
`enum class EAxisSign : uint8`  
_L19-23_
- reflection: `UENUM(BlueprintType)`
- desc: Sign of the axis, to handle data coming from non-left handed systems.
- L21 _public enumerator_ `Positive = 0 UMETA(DisplayName = "Positive")`
- L22 _public enumerator_ `Negative = 1 UMETA(DisplayName = "Negative")`

#### class `ULiveLinkMarkerVisualizer`  
`class ULiveLinkMarkerVisualizer : public UInstancedStaticMeshComponent`  
_L29-90_
- reflection: `UCLASS(MinimalAPI, ClassGroup=(PerformanceCapture), meta=(BlueprintSpawnableComponent),Transient, DisplayName = "MocapMarkerVisualizer")`
- inherits: `UInstancedStaticMeshComponent`
- desc: An Instanced Static Mesh Component to represent Motion Capture marker data locations
- L35 _public prototype_ `ULiveLinkMarkerVisualizer(const FObjectInitializer& ObjectInitializer);` — Sets default values for this component's properties
- L38 _public prototype_ `~ULiveLinkMarkerVisualizer();` — Destructor
- L41 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;` — Called every frame
- L44 _public prototype_ `TArray<FTransform> GetMarkerTransforms();` — Get marker transforms defined in mocap tracking space
- L46 _public prototype_ `static void DrawLabels(TArray<FName> Labels);`
- L50 _public member_ `TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="PerformanceCapture|Visualization")` — Dynamic material to use on the instance static meshes.
- L54 _public member_ `FLiveLinkSubjectName LiveLinkSubject;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="PerformanceCapture|Visualization")` — Live Link subject to drive the instanced static mesh transforms.
- L58 _public member_ `bool bEvaluateLiveLink;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="PerformanceCapture|Visualization")` — Bool to control evaluation of Live Link data.
- L62 _public member_ `bool bDrawLabels;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="PerformanceCapture|Visualization")` — To Do - add text labels to drawn markers
- L66 _public member_ `EAxisSign XAxisSign;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="PerformanceCapture|Visualization")` — Sign for the x axis of the marker.
- L70 _public member_ `EAxisSign YAxisSign;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="PerformanceCapture|Visualization")` — Sign for the y axis of the marker.
- L74 _public member_ `TArray<FTransform> MarkerLocations;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="PerformanceCapture|Visualization")` — Array of Transforms for the markers.
- L78 _protected prototype_ `virtual void OnRegister() override;`
- L79 _protected prototype_ `virtual void OnUnregister() override;`
- L83 _private member_ `TArray<FName> MarkerLabels;`
- L85 _private function_ `static float GetAxisSign(EAxisSign AxisSign)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/ClockOffsetEstimatorRamp.h` (Public)


#### class `FClockOffsetEstimatorRamp`  
`class FClockOffsetEstimatorRamp`  
_L13-52_
- desc: Continually estimates the time offset between two live time sources. Samples of clock times corresponding to the same instant are provided, and it will update its estimation of the time difference between the clocks.
- L18 _public prototype_ `double GetEstimatedOffset() const;` — Get current estimated offset between the two tracked clocks
- L21 _public prototype_ `void UpdateEstimation(double Atime, double Btime);` — Update the current time offset estimation with a new data sample
- L24 _public prototype_ `void SetRequiredConsecutiveBigError(int32 NewCount);` — Set required consecutive big errors to clamp
- L27 _public prototype_ `void SetMaxAllowedEstimationError(double NewValue);` — Set maximum allowed estimation error before looking to clamp
- L30 _public prototype_ `void SetCorrectionStep(double NewValue);` — Sets incremental correction step
- L33 _public prototype_ `void Reset();` — Puts back the estimator in its initial state
- L38 _protected member_ `double EstimatedOffset = 0.0;` — Current estimated offset between two clocks
- L42 _protected member_ `double MaxAllowedEstimationError = 0.25;` — Maximum error tolerated before considering clamping to current offset
- L45 _protected member_ `double CorrectionStep = 100e-6;` — Correction step to apply, positive or negative depending on error sign
- L48 _protected member_ `int32 ConsecutiveTooBigErrorRequired = 5;` — Consecutive time a too big estimation error is required before clamping
- L51 _protected member_ `int32 ConsecutiveBigErrorCount = 5;` — Current consecutive big error count. Initialized at required count so first pass snaps

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/ILiveLinkModule.h` (Public)


#### class `ILiveLinkModule`  
`class ILiveLinkModule : public IModuleInterface`  
_L27-79_
- inherits: `IModuleInterface`
- desc: Interface for messaging modules.
- L37 _public function_ `static ILiveLinkModule& Get()` — Gets a reference to the live link module instance. @return A reference to the live link module.
- L47 _public prototype_ `virtual TSharedPtr<FSlateStyleSet> GetStyle() = 0;`
- L48 _public prototype_ `virtual FLiveLinkHeartbeatEmitter& GetHeartbeatEmitter() = 0;`
- L50 _public prototype_ `virtual FLiveLinkMessageBusDiscoveryManager& GetMessageBusDiscoveryManager() = 0;`
- L59 _public prototype_ `virtual FDelegateHandle RegisterMessageBusSourceFilter(const FOnLiveLinkShouldDisplaySource& SourceFilter) = 0;` — Register a message bus source filter invoked by the MessageBus Source Factory to filter out discovered sources. The delegate should return true if the poll result should be included in the discovered sources list, and false otherwise. @param SourceFilter The filter invoked by the source factory. @return A handle to the delegate, used for unregistering the filter.
- L65 _public prototype_ `virtual void UnregisterMessageBusSourceFilter(FDelegateHandle Handle) = 0;` — Unregister a previously registered message bus source filter. @param Handle A handle to the filter delegate that was registered.
- L70 _public prototype_ `virtual const TMap<FDelegateHandle, FOnLiveLinkShouldDisplaySource>& GetSourceFilters() const = 0;` — @return The list of source filters registered with this module.
- L72 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnSubjectOutboundNameModified, const FLiveLinkSubjectKey& , const FString& , const FString& );`
- L74 _public prototype_ `virtual FOnSubjectOutboundNameModified& OnSubjectOutboundNameModified() = 0;` — (Internal use) Delegate called by LiveLinkHubSubjectSettings to notify.
- L78 _public prototype_ `virtual ~ILiveLinkModule() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L9 _macro_ `#define WITH_LIVELINK_DISCOVERY_MANAGER_THREAD 1`
- L19 _typedef_ `using FProviderPollResultPtr = TSharedPtr<FProviderPollResult, ESPMode::ThreadSafe>;`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnLiveLinkShouldDisplaySource, UClass* , FProviderPollResultPtr );`
- L22 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnLiveLinkShouldDisplaySource, UClass* , FProviderPollResultPtr );`
- L72 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnSubjectOutboundNameModified, const FLiveLinkSubjectKey& , const FString& , const FString& );`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/InterpolationProcessor/LiveLinkAnimationFrameInterpolateProcessor.h` (Public)


#### class `ULiveLinkAnimationFrameInterpolationProcessor`  
`class ULiveLinkAnimationFrameInterpolationProcessor : public ULiveLinkBasicFrameInterpolationProcessor`  
_L15-36_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Animation Interpolation"))`
- inherits: `ULiveLinkBasicFrameInterpolationProcessor`
- desc: Default blending method for animation frames
- L31 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const override;`
- L32 _public prototype_ `virtual ULiveLinkFrameInterpolationProcessor::FWorkerSharedPtr FetchWorker() override;`
- L35 _private member_ `TSharedPtr<FLiveLinkAnimationFrameInterpolationProcessorWorker, ESPMode::ThreadSafe> Instance;`

#### class `ULiveLinkAnimationFrameInterpolationProcessor::FLiveLinkAnimationFrameInterpolationProcessorWorker`  
`class FLiveLinkAnimationFrameInterpolationProcessorWorker : public ULiveLinkBasicFrameInterpolationProcessor::FLiveLinkBasicFrameInterpolationProcessorWorker`  
_L20-28_
- inherits: `ULiveLinkBasicFrameInterpolationProcessor::FLiveLinkBasicFrameInterpolationProcessorWorker`
- L23 _public prototype_ `FLiveLinkAnimationFrameInterpolationProcessorWorker(bool bInterpolatePropertyValues);`
- L25 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const override;`
- L26 _public prototype_ `virtual void Interpolate(double InTime, const FLiveLinkStaticDataStruct& InStaticData, const TArray<FLiveLinkFrameDataStruct>& InSourceFrames, FLiveLinkSubjectFrameData& OutBlendedFrame, FLiveLinkInterpolationInfo& OutInterpolationInfo) override;`
- L27 _public prototype_ `virtual void Interpolate(const FQualifiedFrameTime& InTime, const FLiveLinkStaticDataStruct& InStaticData, const TArray<FLiveLinkFrameDataStruct>& InSourceFrames, FLiveLinkSubjectFrameData& OutBlendedFrame, FLiveLinkInterpolationInfo& OutInterpolationInfo) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/InterpolationProcessor/LiveLinkBasicFrameInterpolateProcessor.h` (Public)


#### class `ULiveLinkBasicFrameInterpolationProcessor`  
`class ULiveLinkBasicFrameInterpolationProcessor : public ULiveLinkFrameInterpolationProcessor`  
_L15-58_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Base Interpolation"))`
- inherits: `ULiveLinkFrameInterpolationProcessor`
- desc: Default blending method for any type of frames. It will interpolate numerical properties that are mark with "Interp".
- L49 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const override;`
- L50 _public prototype_ `virtual ULiveLinkFrameInterpolationProcessor::FWorkerSharedPtr FetchWorker() override;`
- L54 _public member_ `bool bInterpolatePropertyValues = true;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")`
- L57 _private member_ `TSharedPtr<FLiveLinkBasicFrameInterpolationProcessorWorker, ESPMode::ThreadSafe> BaseInstance;`

#### class `ULiveLinkBasicFrameInterpolationProcessor::FLiveLinkBasicFrameInterpolationProcessorWorker`  
`class FLiveLinkBasicFrameInterpolationProcessorWorker : public ILiveLinkFrameInterpolationProcessorWorker`  
_L20-46_
- inherits: `ILiveLinkFrameInterpolationProcessorWorker`
- L23 _public prototype_ `FLiveLinkBasicFrameInterpolationProcessorWorker(bool bInterpolatePropertyValues);`
- L25 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const override;`
- L27 _public prototype_ `virtual void Interpolate(double InTime, const FLiveLinkStaticDataStruct& InStaticData, const TArray<FLiveLinkFrameDataStruct>& InSourceFrames, FLiveLinkSubjectFrameData& OutBlendedFrame, FLiveLinkInterpolationInfo& OutInterpolationInfo) override;`
- L28 _public prototype_ `virtual void Interpolate(const FQualifiedFrameTime& InTime, const FLiveLinkStaticDataStruct& InStaticData, const TArray<FLiveLinkFrameDataStruct>& InSourceFrames, FLiveLinkSubjectFrameData& OutBlendedFrame, FLiveLinkInterpolationInfo& OutInterpolationInfo) override;`
- L38 _public prototype_ `static void GenericInterpolate(double InBlendFactor, const FGenericInterpolateOptions& Options, const FLiveLinkFrameDataStruct& FrameDataA, const FLiveLinkFrameDataStruct& FrameDataB, FLiveLinkFrameDataStruct& OutBlendedFrame);`
- L39 _public prototype_ `static double GetBlendFactor(double InTime, const FLiveLinkFrameDataStruct& FrameDataA, const FLiveLinkFrameDataStruct& FrameDataB);`
- L40 _public prototype_ `static double GetBlendFactor(FQualifiedFrameTime InTime, const FLiveLinkFrameDataStruct& FrameDataA, const FLiveLinkFrameDataStruct& FrameDataB);`
- L41 _public prototype_ `static bool FindInterpolateIndex(double InTime, const TArray<FLiveLinkFrameDataStruct>& InSourceFrames, int32& OutFrameIndexA, int32& OutFrameIndexB, FLiveLinkInterpolationInfo& OutInterpolationInfo);`
- L42 _public prototype_ `static bool FindInterpolateIndex(FQualifiedFrameTime InTime, const TArray<FLiveLinkFrameDataStruct>& InSourceFrames, int32& OutFrameIndexA, int32& OutFrameIndexB, FLiveLinkInterpolationInfo& OutInterpolationInfo);`
- L45 _protected member_ `bool bInterpolatePropertyValues = true;`

#### struct `ULiveLinkBasicFrameInterpolationProcessor::FLiveLinkBasicFrameInterpolationProcessorWorker::FGenericInterpolateOptions`  
`struct FGenericInterpolateOptions`  
_L30-36_
- L32 _public member_ `bool bInterpolatePropertyValues = true;`
- L33 _public member_ `bool bCopyClosestFrame = true;`
- L34 _public member_ `bool bCopyClosestMetaData = true;` — only used if bCopyClosestFrame is false. Does NOT apply to SceneTime, it will always be interpolated.
- L35 _public member_ `bool bInterpolateInterpProperties = true;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkAnimationVirtualSubject.h` (Public)


#### enum `EBoneTransformResolution`  
`enum class EBoneTransformResolution`  
_L18-26_
- reflection: `UENUM()`
- desc: What action should be taken when a bone name conflict happens between a parent and a child subject.
- L21 _public enumerator_ `KeepParent` — Keep parent bone transform.
- L23 _public enumerator_ `KeepChild` — Keep child bone transform.
- L25 _public enumerator_ `Combine` — Combine the child and parent's bone transforms.

#### class `ULiveLinkAnimationVirtualSubject`  
`class ULiveLinkAnimationVirtualSubject : public ULiveLinkVirtualSubject`  
_L30-137_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Animation Virtual Subject"))`
- inherits: `ULiveLinkVirtualSubject`
- desc: A Skeleton virtual subject is an assembly of different subjects supporting the animation or basic role
- L35 _public prototype_ `ULiveLinkAnimationVirtualSubject();`
- L37 _public prototype_ `virtual void Update() override;`
- L41 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L47 _protected prototype_ `bool AreSubjectsValid(const TArray<FLiveLinkSubjectKey>& InActiveSubjects) const;` — Validates current source subjects
- L49 _protected prototype_ `bool BuildSubjectSnapshot(TArray<FLiveLinkSubjectFrameData>& OutSnapshot);`
- L52 _protected prototype_ `virtual void BuildSkeleton(const TArray<FLiveLinkSubjectFrameData>& InSubjectSnapshots);` — Builds a new ref skeleton based on the current subject state(can early out if ref skeleton is already up to date)
- L54 _protected prototype_ `virtual void BuildFrame(const TArray<FLiveLinkSubjectFrameData>& InSubjectSnapshots);`
- L57 _protected function_ `virtual void PostSkeletonRebuild()` — Called after the update method.
- L60 _protected prototype_ `bool DoesSkeletonNeedRebuilding() const;` — Tests to see if current ref skeleton is up to data
- L61 _protected member_ `bool bInvalidate;`
- L64 _protected prototype_ `void SortSubjects();` — Sort the subjects according to the dependencies introduced by the attachments.
- L67 _protected prototype_ `void ProcessAttachmentsForStaticData(TArray<int32>& InOutBoneParents);` — Build the ChildBonesInfo list from the specified attachments.
- L70 _protected prototype_ `void ProcessAttachmentsForFrameData(struct FLiveLinkAnimationFrameData* SnapshotFrameData);` — Apply transform offsets generated by the attachments to the frame data.
- L73 _protected function_ `ELiveLinkSubjectState GetState() const override`
- L96 _public member_ `TArray<FLiveLinkVirtualSubjectBoneAttachment> Attachments;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")` — List of bone attachments between subjects.
- L100 _public member_ `EBoneTransformResolution LocationBehavior = EBoneTransformResolution::Combine;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")` — What should happen to the location of a bone when there's a conflict between the child and parent subject.
- L104 _public member_ `EBoneTransformResolution RotationBehavior = EBoneTransformResolution::Combine;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")` — What should happen to the rotation of a bone when there's a conflict between the child and parent subject.
- L108 _public member_ `bool bAppendSubjectNameToBones;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Whether to append SubjectName to each bones part of the virtual hierarchy
- L121 _private member_ `TMap<int32, FChildBoneInfo> ChildBonesInfo;` — Map of global child indices to their respective bone info structure.
- L124 _private member_ `TMap<TPair<FName, FName>, int32> BoneNameToIndex;` — Lookup table of Subject + bone name to index in the concatenated list of bone names.
- L127 _private member_ `TArray<FLiveLinkSubjectFrameData> LastFrameSnapshots;` — Cached snapshots, used when the subjects are invalid in order to maintain tranmission of data.
- L133 _private member_ `bool bLastSnapshotIsComplete = false;` — Returns whether all snapshots were successfully created. Will be false if no snapshot was created, or if one of the subject was invalid, causing the subject to use the previous frame's data.
- L136 _private member_ `bool bSubjectsNeedSorting = false;` — Whether the subjects need to be sorted because an attachment has been modified.

#### struct `ULiveLinkAnimationVirtualSubject::FChildBoneInfo`  
`struct FChildBoneInfo`  
_L112-118_
- desc: Information about a bone that needs to be attached to a parent subject.
- L115 _public member_ `int32 ParentBone = INDEX_NONE;` — Parent bone global index.
- L117 _public member_ `FTransform Offset = FTransform::Identity;` — Offset of the child bone to its parent bone.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkBlueprintLibrary.h` (Public)


#### class `ULiveLinkBlueprintLibrary`  
`class ULiveLinkBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L29-224_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L37 _private prototype_ `static bool GetPropertyValue(UPARAM(ref) FLiveLinkBasicBlueprintData& BasicData, FName PropertyName, float& Value);` — `UFUNCTION(BlueprintPure, Category = "LiveLink")` — Returns the value of a property stored in the Subject Frame
- L43 _private prototype_ `static void GetCurves(UPARAM(ref) FSubjectFrameHandle& SubjectFrameHandle, TMap<FName, float>& Curves);` — `UFUNCTION(BlueprintPure, Category = "LiveLink|Animation")` — Returns the float curves stored in the Subject Frame as a map
- L47 _private prototype_ `static int NumberOfTransforms(UPARAM(ref) FSubjectFrameHandle& SubjectFrameHandle);` — `UFUNCTION(BlueprintPure, Category = "LiveLink|Animation")` — Returns the number of Transforms stored in the Subject Frame
- L51 _private prototype_ `static void TransformNames(UPARAM(ref) FSubjectFrameHandle& SubjectFrameHandle, TArray<FName>& TransformNames);` — `UFUNCTION(BlueprintPure, Category = "LiveLink|Animation")` — Returns an array of Transform Names stored in the Subject Frame
- L55 _private prototype_ `static void GetRootTransform(UPARAM(ref) FSubjectFrameHandle& SubjectFrameHandle, FLiveLinkTransform& LiveLinkTransform);` — `UFUNCTION(BlueprintPure, Category = "LiveLink|Animation")` — Returns the Root Transform for the Subject Frame as a LiveLink Transform or the Identity if there are no transforms.
- L59 _private prototype_ `static void GetTransformByIndex(UPARAM(ref) FSubjectFrameHandle& SubjectFrameHandle, int TransformIndex, FLiveLinkTransform& LiveLinkTransform);` — `UFUNCTION(BlueprintPure, Category = "LiveLink|Animation")` — Returns the LiveLink Transform stored in a Subject Frame at a given index. Returns an Identity transform if Transform Index is invalid.
- L63 _private prototype_ `static void GetTransformByName(UPARAM(ref) FSubjectFrameHandle& SubjectFrameHandle, FName TransformName, FLiveLinkTransform& LiveLinkTransform);` — `UFUNCTION(BlueprintPure, Category = "LiveLink|Animation")` — Returns the LiveLink Transform stored in a Subject Frame with a given name. Returns an Identity transform if Transform Name is invalid.
- L67 _private prototype_ `static void GetMetadata(UPARAM(ref) FSubjectFrameHandle& SubjectFrameHandle, FSubjectMetadata& Metadata);` — `UFUNCTION(BlueprintPure, Category = "LiveLink|Animation")` — Returns the Subject Metadata structure stored in the Subject Frame
- L71 _private prototype_ `static void GetBasicData(UPARAM(ref) FSubjectFrameHandle& SubjectFrameHandle, FLiveLinkBasicBlueprintData& BasicBlueprintData);` — `UFUNCTION(BlueprintPure, Category = "LiveLink|Animation")` — Returns the Subject base structure stored in the Subject Frame
- L75 _private prototype_ `static bool GetAnimationStaticData(UPARAM(ref) FSubjectFrameHandle& SubjectFrameHandle, FLiveLinkSkeletonStaticData& AnimationStaticData);` — `UFUNCTION(BlueprintPure, Category = "LiveLink|Animation")` — Returns the Subject's static data stored in the Subject Frame. Returns false if no valid data found.
- L79 _private prototype_ `static bool GetAnimationFrameData(UPARAM(ref) FSubjectFrameHandle& SubjectFrameHandle, FLiveLinkAnimationFrameData& AnimationFrameData);` — `UFUNCTION(BlueprintPure, Category = "LiveLink|Animation")` — Returns the Subject's frame data stored in the Subject Frame. Returns false if no valid data found.
- L85 _private prototype_ `static void TransformName(UPARAM(ref) FLiveLinkTransform& LiveLinkTransform, FName& Name);` — `UFUNCTION(BlueprintPure, Category = "LiveLink")` — Returns the Name of a given LiveLink Transform
- L89 _private prototype_ `static void ParentBoneSpaceTransform(UPARAM(ref) FLiveLinkTransform& LiveLinkTransform, FTransform& Transform);` — `UFUNCTION(BlueprintPure, Category = "LiveLink")` — Returns the Transform value in Parent Space for a given LiveLink Transform
- L93 _private prototype_ `static void ComponentSpaceTransform(UPARAM(ref) FLiveLinkTransform& LiveLinkTransform, FTransform& Transform);` — `UFUNCTION(BlueprintPure, Category = "LiveLink")` — Returns the Transform value in Root Space for a given LiveLink Transform
- L97 _private prototype_ `static bool HasParent(UPARAM(ref) FLiveLinkTransform& LiveLinkTransform);` — `UFUNCTION(BlueprintPure, Category = "LiveLink")` — Returns whether a given LiveLink Transform has a parent transform
- L101 _private prototype_ `static void GetParent(UPARAM(ref) FLiveLinkTransform& LiveLinkTransform, FLiveLinkTransform& Parent);` — `UFUNCTION(BlueprintPure, Category = "LiveLink")` — Returns the Parent LiveLink Transform if one exists or an Identity transform if no parent exists
- L105 _private prototype_ `static int ChildCount(UPARAM(ref) FLiveLinkTransform& LiveLinkTransform);` — `UFUNCTION(BlueprintPure, Category = "LiveLink")` — Returns the number of Children for a given LiveLink Transform
- L109 _private prototype_ `static void GetChildren(UPARAM(ref) FLiveLinkTransform& LiveLinkTransform, TArray<FLiveLinkTransform>& Children);` — `UFUNCTION(BlueprintPure, Category = "LiveLink")` — Returns an array of Child LiveLink Transforms for a given LiveLink Transform
- L115 _private prototype_ `static bool IsSourceStillValid(UPARAM(ref) FLiveLinkSourceHandle& SourceHandle);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Checks whether the LiveLink Source is valid via its handle
- L119 _private prototype_ `static bool RemoveSource(UPARAM(ref) FLiveLinkSourceHandle& SourceHandle);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Requests the given LiveLink Source to shut down via its handle
- L123 _private prototype_ `static FText GetSourceStatus(UPARAM(ref) FLiveLinkSourceHandle& SourceHandle);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Get the text status of a LiveLink Source via its handle
- L127 _private prototype_ `static FText GetSourceType(UPARAM(ref) FLiveLinkSourceHandle& SourceHandle);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Get the type of a LiveLink Source via its handle
- L131 _private prototype_ `static FText GetSourceMachineName(UPARAM(ref) FLiveLinkSourceHandle& SourceHandle);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Get the machine name of a LiveLink Source via its handle
- L140 _public prototype_ `static FText GetSourceTypeFromGuid(FGuid SourceGuid);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Get the type of a source from the given GUID @param SourceGuid the GUID identifying the LiveLink Source @return The type of the Source as Text
- L144 _public prototype_ `static TArray<FLiveLinkSubjectName> GetLiveLinkEnabledSubjectNames(bool bIncludeVirtualSubject);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Get a list of all enabled subject names
- L148 _public prototype_ `static TArray<FLiveLinkSubjectKey> GetLiveLinkSubjects(bool bIncludeDisabledSubject, bool bIncludeVirtualSubject);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Get a list of all subjects
- L157 _public prototype_ `static bool IsSpecificLiveLinkSubjectEnabled(const FLiveLinkSubjectKey SubjectKey, bool bForThisFrame);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Whether or not a subject from the specific source is the enabled subject. Only 1 subject with the same name can be enabled. At the start of the frame, a snapshot of the enabled subjects will be made. That snapshot dictate which subject will be used for the duration of that frame.
- L166 _public prototype_ `static bool IsLiveLinkSubjectEnabled(const FLiveLinkSubjectName SubjectName);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Whether or not the client has a subject with this name enabled Only 1 subject with the same name can be enabled. At the start of the frame, a snapshot of the enabled subjects will be made. That snapshot dictate which subject will be used for the duration of that frame.
- L172 _public prototype_ `static ELiveLinkSubjectState GetLiveLinkSubjectState(const FLiveLinkSubjectName SubjectName);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Returns the state of the subject with the given name.
- L182 _public prototype_ `static void SetLiveLinkSubjectEnabled(const FLiveLinkSubjectKey SubjectKey, bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Set the subject's from a specific source to enabled, disabling the other in the process. Only 1 subject with the same name can be enabled. At the start of the frame, a snapshot of the enabled subjects will be made. That snapshot dictate which subject will be used for the duration of that frame. SetSubjectEnabled will take effect on the next frame.
- L186 _public prototype_ `static TSubclassOf<ULiveLinkRole> GetSpecificLiveLinkSubjectRole(const FLiveLinkSubjectKey SubjectKey);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Get the role of a subject from a specific source
- L190 _public prototype_ `static TSubclassOf<ULiveLinkRole> GetLiveLinkSubjectRole(const FLiveLinkSubjectName SubjectName);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Get the role of the subject with this name
- L194 _public prototype_ `static void PauseSubject(const FLiveLinkSubjectName SubjectName);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Pause a subject, freezing its evaluation to the last data it received.
- L198 _public prototype_ `static void UnpauseSubject(const FLiveLinkSubjectName SubjectName);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Unpause a subject, resuming its normal operation.
- L202 _public prototype_ `static bool EvaluateLiveLinkFrame(FLiveLinkSubjectRepresentation SubjectRepresentation, FLiveLinkBaseBlueprintData& OutBlueprintData);` — `UE_DEPRECATED(4.23, "EvaluateLiveLinkFrame with Subject Represention is deprecated, recreate the node.")` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = LiveLink, meta = (DeprecatedFunction, CustomStructureParam = "OutBlueprintData", BlueprintInternalUseOnly = "true", AllowAbstract = "false"))`
- L206 _public prototype_ `static bool EvaluateLiveLinkFrameWithSpecificRole(FLiveLinkSubjectName SubjectName, TSubclassOf<ULiveLinkRole> Role, FLiveLinkBaseBlueprintData& OutBlueprintData);` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = LiveLink, meta = (DisplayName="EvaluateLiveLinkFrame", CustomStructureParam = "OutBlueprintData", BlueprintInternalUseOnly = "true", AllowAbstract = "false"))` — Fetches a frame on a subject for a specific role. Output is evaluated based on the role
- L210 _public prototype_ `static bool EvaluateLiveLinkFrameAtWorldTimeOffset(FLiveLinkSubjectName SubjectName, TSubclassOf<ULiveLinkRole> Role, float WorldTimeOffset, FLiveLinkBaseBlueprintData& OutBlueprintData);` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = LiveLink, meta = (CustomStructureParam = "OutBlueprintData", BlueprintInternalUseOnly = "true", AllowAbstract = "false"))` — Fetches a frame on a subject for a specific role at an offset from the application current time. Output is evaluated based on the role
- L217 _public prototype_ `static bool EvaluateLiveLinkFrameAtSceneTime(FLiveLinkSubjectName SubjectName, TSubclassOf<ULiveLinkRole> Role, FTimecode SceneTime, FLiveLinkBaseBlueprintData& OutBlueprintData);` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = LiveLink, meta = (CustomStructureParam = "OutBlueprintData", BlueprintInternalUseOnly = "true", AllowAbstract = "false"))` — Fetches a frame on a subject for a specific role at a specified scene time (timecode). The Timecode should be at the frame rate as the engine timecode. Output is evaluated based on the role

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkBlueprintStructs.h` (Public)


#### Free symbols / members of external scopes

- L10 _function_ `inline void LiveLinkBlueprintStructsHeaderDeprecatedWarning()` — `UE_DEPRECATED(4.23, "Including LiveLinkBlueprintStructs.h has been deprecated. Please include Roles/LiveLinkAnimationBlueprintStructs.h instead.")`
- L14 _function_ `inline void TriggerLiveLinkBlueprintStructsHeaderDeprecatedWarning()`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkBroadcastComponent.h` (Public)


#### class `ULiveLinkBroadcastComponent`  
`class ULiveLinkBroadcastComponent : public UActorComponent`  
_L18-137_
- reflection: `UCLASS(BlueprintType, DisplayName="Live Link Broadcast", ClassGroup=("LiveLink"), meta=(BlueprintSpawnableComponent), HideCategories=(Navigation, Tags, AssetUserData, Activation), MinimalAPI)`
- inherits: `UActorComponent`
- L24 _public prototype_ `ULiveLinkBroadcastComponent();` — Sets default values for this component's properties
- L28 _public member_ `bool bEnable = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Live Link Broadcast")` — Whether this component should broadcast data.
- L34 _public member_ `FName SubjectName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Live Link Broadcast")` — The name of the Live Link subject. Will default to the actor name if left blank
- L41 _public member_ `TSubclassOf<ULiveLinkRole> Role;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Live Link Broadcast")` — What role should be used for evaluating the data. Choosing Transform Role will only send the transform of the chosen component, while picking Animation will send the full skeleton transforms.
- L48 _public member_ `FComponentReference SourceMesh;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Live Link Broadcast", meta=(UseComponentPicker))` — The source mesh to broadcast todo: Use customization to restrict the allowed classes metadata
- L54 _public member_ `TArray<FName> AllowedBoneNames;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Live Link Broadcast", meta=(ToolTip="Use this array to provide an inclusive list of bones to broadcast"))` — Optional list of allowed bone names (useful for Metahumans and other complex assets).
- L60 _public member_ `TArray<FName> AllowedCurveNames;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Live Link Broadcast", meta=(ToolTip="Curve data will be added to the broadcast data if listed here"))` — Optional list of allowed curve names (useful for Metahumans and other complex assets).
- L64 _public member_ `bool bRemoveSubjectWhenDisabled = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Live Link Broadcast")` — Whether the livelink subject should be removed when broadcasting is disabled.
- L67 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L70 _public function_ `void MarkDirty()` — Trigger retransmission of static data on the next tick.
- L76 _public prototype_ `void SetEnabled(bool bInEnabled);` — Sets whether this component should broadcast live link data.
- L80 _private prototype_ `void InitiateLiveLink();` — Creates the rebroadcast source if it doesn't exist.
- L83 _private prototype_ `FLiveLinkStaticDataStruct GetSkeletonStaticData() const;`
- L84 _private prototype_ `FLiveLinkStaticDataStruct GetCharacterStaticData() const;`
- L85 _private prototype_ `FLiveLinkStaticDataStruct GetCameraStaticData() const;`
- L86 _private prototype_ `FLiveLinkStaticDataStruct GetTransformStaticData() const;`
- L89 _private prototype_ `FLiveLinkFrameDataStruct GetSkeletonFrameData() const;`
- L90 _private prototype_ `FLiveLinkFrameDataStruct GetCharacterFrameData() const;`
- L91 _private prototype_ `FLiveLinkFrameDataStruct GetCameraFrameData() const;`
- L92 _private prototype_ `FLiveLinkFrameDataStruct GetTransformFrameData() const;`
- L95 _private prototype_ `TArray<FName> GetSkeletalBoneNames() const;` — Get bone names from the skekelal mesh.
- L98 _private prototype_ `TArray<int32> GetSkeletalBoneParents() const;` — Get bone parents from the skekelal mesh.
- L101 _private prototype_ `TArray<FTransform> GetBoneTransforms() const;` — Get the bone transforms from the mesh.
- L104 _private prototype_ `TArray<FName> GetCurveNames() const;` — Get the curve names from the mesh.
- L107 _private prototype_ `TArray<float> GetCurveValues() const;` — Get the curve values from the mesh.
- L110 _private prototype_ `void BroadcastStaticData() const;` — Send the static data to the broadcast subsystem.
- L113 _private prototype_ `void BroadcastFrameData() const;` — Send the frame data to the broadcast subsystem.
- L117 _protected prototype_ `virtual void OnComponentCreated() override;`
- L118 _protected prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L123 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L127 _protected prototype_ `void OnObjectModified(UObject* ModifiedObject);` — Object modified callback used to trigger the dirty flag if one of the properties on the tracked source object is modified.
- L132 _private member_ `class UActorComponent* CachedResolvedObject = nullptr;` — Cached resolved object, updated when bIsDirty gets triggered.
- L134 _private member_ `bool bIsDirty;` — Dirty flag used to trigger updates on the broadcast subsystem.
- L136 _private member_ `FLiveLinkSubjectKey SubjectKey;` — Cached subject key for this component.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkClient.h` (Public)


#### struct `FLiveLinkSubjectTimeSyncData`  
`struct FLiveLinkSubjectTimeSyncData`  
_L24-30_
- L26 _public member_ `bool bIsValid = false;`
- L27 _public member_ `FFrameTime OldestSampleTime;`
- L28 _public member_ `FFrameTime NewestSampleTime;`
- L29 _public member_ `FFrameRate SampleFrameRate;`

#### enum `ELiveLinkTickType`  
`enum class ELiveLinkTickType`  
_L33-38_
- desc: Describes what triggered the LiveLinkClient Tick.
- L35 _public enumerator_ `Default` — Default tick path, used in UE.
- L36 _public enumerator_ `Scheduled` — Scheduled tick that's triggered by the LiveLinkHub ticker.
- L37 _public enumerator_ `Triggered` — Tick triggered by frame data being received outside of the Game Thread.

#### class `FLiveLinkClient`  
`class FLiveLinkClient : public ILiveLinkClient`  
_L46-363_
- inherits: `ILiveLinkClient`
- L50 _public prototype_ `FLiveLinkClient();` — Default constructor that setups LiveLink to use the SamplingInput delegate to tick.
- L53 _public prototype_ `FLiveLinkClient(FSimpleMulticastDelegate& InTickingDelegate);`
- L54 _public prototype_ `FLiveLinkClient(FTSSimpleMulticastDelegate& InTickingDelegate);`
- L56 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FLiveLinkTickDelegate, ELiveLinkTickType) FLiveLinkClient(FLiveLinkTickDelegate& InTickingDelegate);`
- L59 _public prototype_ `virtual ~FLiveLinkClient();`
- L62 _public prototype_ `virtual FGuid AddSource(TSharedPtr<ILiveLinkSource> Source) override;`
- L63 _public prototype_ `virtual FGuid AddVirtualSubjectSource(FName SourceName) override;`
- L64 _public prototype_ `virtual bool CreateSource(const FLiveLinkSourcePreset& SourcePreset) override;`
- L65 _public prototype_ `virtual void RemoveSource(TSharedPtr<ILiveLinkSource> Source) override;`
- L66 _public prototype_ `virtual void RemoveSource(FGuid InEntryGuid) override;`
- L67 _public prototype_ `virtual bool HasSourceBeenAdded(TSharedPtr<ILiveLinkSource> Source) const override;`
- L68 _public prototype_ `virtual TArray<FGuid> GetSources(bool bEvenIfPendingKill = false) const override;`
- L69 _public prototype_ `virtual TArray<FGuid> GetVirtualSources(bool bEvenIfPendingKill = false) const override;`
- L70 _public prototype_ `virtual FLiveLinkSourcePreset GetSourcePreset(FGuid SourceGuid, UObject* DuplicatedObjectOuter) const override;`
- L71 _public prototype_ `virtual FText GetSourceType(FGuid EntryGuid) const override;`
- L72 _public prototype_ `virtual FText GetSourceStatus(FGuid EntryGuid) const override;`
- L73 _public prototype_ `virtual FText GetSourceToolTip(FGuid EntryGuid) const override;`
- L74 _public prototype_ `virtual FText GetSourceMachineName(FGuid EntryGuid) const override;`
- L75 _public prototype_ `virtual bool IsSourceStillValid(FGuid EntryGuid) const override;`
- L77 _public prototype_ `virtual void PushSubjectStaticData_AnyThread(const FLiveLinkSubjectKey& SubjectKey, TSubclassOf<ULiveLinkRole> Role, FLiveLinkStaticDataStruct&& StaticData) override;`
- L78 _public prototype_ `virtual void PushSubjectFrameData_AnyThread(const FLiveLinkSubjectKey& SubjectKey, FLiveLinkFrameDataStruct&& FrameData) override;`
- L80 _public prototype_ `virtual bool CreateSubject(const FLiveLinkSubjectPreset& SubjectPreset) override;`
- L81 _public prototype_ `virtual bool AddVirtualSubject(const FLiveLinkSubjectKey& VirtualSubjectKey, TSubclassOf<ULiveLinkVirtualSubject> VirtualSubjectClass) override;`
- L82 _public prototype_ `virtual void RemoveVirtualSubject(const FLiveLinkSubjectKey& VirtualSubjectKey) override;`
- L83 _public prototype_ `virtual void RemoveSubject_AnyThread(const FLiveLinkSubjectKey& SubjectKey) override;`
- L84 _public prototype_ `virtual void PauseSubject_AnyThread(FLiveLinkSubjectName SubjectName) override;`
- L85 _public prototype_ `virtual void UnpauseSubject_AnyThread(FLiveLinkSubjectName SubjectName) override;`
- L86 _public prototype_ `virtual void ClearSubjectsFrames_AnyThread(FLiveLinkSubjectName SubjectName) override;`
- L87 _public prototype_ `virtual void ClearSubjectsFrames_AnyThread(const FLiveLinkSubjectKey& InSubjectKey) override;`
- L88 _public prototype_ `virtual void ClearAllSubjectsFrames_AnyThread() override;`
- L89 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetSubjectRole_AnyThread(const FLiveLinkSubjectKey& SubjectKey) const override;`
- L90 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetSubjectRole_AnyThread(FLiveLinkSubjectName SubjectName) const override;`
- L91 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetSubjectTranslatedRole_AnyThread(const FLiveLinkSubjectKey& SubjectKey) const override;`
- L92 _public prototype_ `virtual bool DoesSubjectSupportsRole_AnyThread(const FLiveLinkSubjectKey& SubjectKey, TSubclassOf<ULiveLinkRole> SupportedRole) const override;`
- L93 _public prototype_ `virtual bool DoesSubjectSupportsRole_AnyThread(FLiveLinkSubjectName SubjectName, TSubclassOf<ULiveLinkRole> SupportedRole) const override;`
- L95 _public prototype_ `virtual FLiveLinkSubjectPreset GetSubjectPreset(const FLiveLinkSubjectKey& SubjectKey, UObject* DuplicatedObjectOuter) const override;`
- L96 _public prototype_ `virtual TArray<FLiveLinkSubjectKey> GetSubjects(bool bIncludeDisabledSubject, bool bIncludeVirtualSubject) const override;`
- L98 _public prototype_ `virtual bool IsSubjectValid(const FLiveLinkSubjectKey& SubjectKey) const override;`
- L99 _public prototype_ `virtual bool IsSubjectValid(FLiveLinkSubjectName SubjectName) const override;`
- L100 _public prototype_ `virtual bool IsSubjectEnabled(const FLiveLinkSubjectKey& SubjectKey, bool bForThisFrame) const override;`
- L101 _public prototype_ `virtual bool IsSubjectEnabled(FLiveLinkSubjectName SubjectName) const override;`
- L102 _public prototype_ `virtual void SetSubjectEnabled(const FLiveLinkSubjectKey& SubjectKey, bool bEnabled) override;`
- L103 _public prototype_ `virtual void SetSubjectEnabled(FLiveLinkSubjectName SubjectName, bool bEnabled) override;`
- L104 _public prototype_ `virtual bool IsSubjectTimeSynchronized(const FLiveLinkSubjectKey& SubjectKey) const override;`
- L105 _public prototype_ `virtual bool IsSubjectTimeSynchronized(FLiveLinkSubjectName SubjectName) const override;`
- L106 _public prototype_ `virtual bool IsVirtualSubject(const FLiveLinkSubjectKey& SubjectKey) const override;`
- L107 _public prototype_ `virtual ELiveLinkSubjectState GetSubjectState(FLiveLinkSubjectName InSubjectName) const override;`
- L110 _public prototype_ `virtual TArray<FLiveLinkSubjectKey> GetSubjectsSupportingRole(TSubclassOf<ULiveLinkRole> SupportedRole, bool bIncludeDisabledSubject, bool bIncludeVirtualSubject) const override;`
- L111 _public prototype_ `virtual TArray<FLiveLinkTime> GetSubjectFrameTimes(const FLiveLinkSubjectKey& SubjectKey) const override;`
- L112 _public prototype_ `virtual TArray<FLiveLinkTime> GetSubjectFrameTimes(FLiveLinkSubjectName SubjectName) const override;`
- L113 _public prototype_ `virtual FText GetSourceNameOverride(const FLiveLinkSubjectKey& SubjectKey) const override;`
- L114 _public prototype_ `virtual FText GetSubjectDisplayName(const FLiveLinkSubjectKey& SubjectKey) const override;`
- L115 _public prototype_ `virtual ULiveLinkSourceSettings* GetSourceSettings(const FGuid& SourceGuid) const override;`
- L116 _public prototype_ `virtual UObject* GetSubjectSettings(const FLiveLinkSubjectKey& SubjectKey) const override;`
- L117 _public prototype_ `virtual const FLiveLinkStaticDataStruct* GetSubjectStaticData_AnyThread(const FLiveLinkSubjectKey& InSubjectKey, bool bGetOverrideData=true) const override;`
- L120 _public prototype_ `virtual bool EvaluateFrameFromSource_AnyThread(const FLiveLinkSubjectKey& SubjectKey, TSubclassOf<ULiveLinkRole> Role, FLiveLinkSubjectFrameData& OutFrame) override;`
- L121 _public prototype_ `virtual bool EvaluateFrame_AnyThread(FLiveLinkSubjectName SubjectName, TSubclassOf<ULiveLinkRole> Role, FLiveLinkSubjectFrameData& OutFrame) override;`
- L122 _public prototype_ `virtual bool EvaluateFrameAtWorldTime_AnyThread(FLiveLinkSubjectName SubjectName, double WorldTime, TSubclassOf<ULiveLinkRole> DesiredRole, FLiveLinkSubjectFrameData& OutFrame) override;`
- L123 _public prototype_ `virtual bool EvaluateFrameAtSceneTime_AnyThread(FLiveLinkSubjectName SubjectName, const FQualifiedFrameTime& FrameTime, TSubclassOf<ULiveLinkRole> DesiredRole, FLiveLinkSubjectFrameData& OutFrame) override;`
- L124 _public prototype_ `virtual void ForceTick() override;`
- L125 _public prototype_ `virtual bool HasPendingSubjectFrames() override;`
- L126 _public prototype_ `virtual void ClearOverrideStaticData_AnyThread(const FLiveLinkSubjectKey& InSubjectKey) override;`
- L128 _public prototype_ `virtual FSimpleMulticastDelegate& OnLiveLinkTicked() override;`
- L129 _public prototype_ `virtual FSimpleMulticastDelegate& OnLiveLinkSourcesChanged() override;`
- L130 _public prototype_ `virtual FSimpleMulticastDelegate& OnLiveLinkSubjectsChanged() override;`
- L131 _public prototype_ `virtual FOnLiveLinkSourceChangedDelegate& OnLiveLinkSourceAdded() override;`
- L132 _public prototype_ `virtual FOnLiveLinkSourceChangedDelegate& OnLiveLinkSourceRemoved() override;`
- L133 _public prototype_ `virtual FOnLiveLinkSubjectChangedDelegate& OnLiveLinkSubjectAdded() override;`
- L134 _public prototype_ `virtual FOnLiveLinkSubjectChangedDelegate& OnLiveLinkSubjectRemoved() override;`
- L135 _public prototype_ `virtual FOnLiveLinkSubjectStateChanged& OnLiveLinkSubjectStateChanged() override;`
- L136 _public prototype_ `virtual FOnLiveLinkSubjectEnabledDelegate& OnLiveLinkSubjectEnabledChanged() override;`
- L139 _public prototype_ `virtual FOnLiveLinkSubjectEvaluated& OnLiveLinkSubjectEvaluated() override;`
- L142 _public prototype_ `virtual void RegisterForFrameDataReceived(const FLiveLinkSubjectKey& InSubjectKey, const FOnLiveLinkSubjectStaticDataReceived::FDelegate& OnStaticDataReceived_AnyThread, const FOnLiveLinkSubjectFrameDataReceived::FDelegate& OnFrameDataReceived_AnyThread, FDelegateHandle& OutStaticDataReceivedHandle, FDelegateHandle& OutFrameDataReceivedHandle) override;`
- L143 _public prototype_ `virtual void UnregisterForFrameDataReceived(const FLiveLinkSubjectKey& InSubjectKey, FDelegateHandle InStaticDataReceivedHandle, FDelegateHandle InFrameDataReceivedHandle) override;`
- L144 _public prototype_ `virtual bool RegisterForSubjectFrames(FLiveLinkSubjectName SubjectName, const FOnLiveLinkSubjectStaticDataAdded::FDelegate& OnStaticDataAdded, const FOnLiveLinkSubjectFrameDataAdded::FDelegate& OnFrameDataAdded, FDelegateHandle& OutStaticDataReceivedHandle, FDelegateHandle& OutFrameDataReceivedHandle, TSubclassOf<ULiveLinkRole>& OutSubjectRole, FLiveLinkStaticDataStruct* OutStaticData = nullptr) override;`
- L145 _public prototype_ `virtual void UnregisterSubjectFramesHandle(FLiveLinkSubjectName InSubjectName, FDelegateHandle InStaticDataReceivedHandle, FDelegateHandle InFrameDataReceivedHandle) override;`
- L167 _public prototype_ `void Tick(ELiveLinkTickType TickType = ELiveLinkTickType::Default);` — The tick callback to update the pending work and clear the subject's snapshot
- L170 _public prototype_ `void RemoveAllSources();` — Remove all sources from the live link client
- L177 _public prototype_ `bool RemoveAllSourcesWithTimeout(float InTimeout);` — Remove all sources and wait for them to be removed. This is a blocking operation. @param InTimeout The timeout in seconds to wait. @return Whether all sources were removed successfully.
- L181 _public prototype_ `void ReinitializeVirtualSubject(const FLiveLinkSubjectKey& SubjectKey);` — Call initialize again on an existing virtual subject. Used for when a Blueprint Virtual Subject is compiled
- L185 _public prototype_ `void OnPropertyChanged(FGuid EntryGuid, const FPropertyChangedEvent& PropertyChangedEvent);` — Callback when property changed for one of the source settings
- L192 _public prototype_ `TArray<FGuid> GetDisplayableSources(bool bIncludeVirtualSources = false) const;` — Get all sources that can be displayed in the UI's source list. @param bIncludeVirtualSources Whether or not to include virtual sources in the returned list, since virtual sources are not displayed in the source list. @return the list of displayable sources.
- L194 _public prototype_ `FLiveLinkSubjectTimeSyncData GetTimeSyncData(FLiveLinkSubjectName SubjectName);`
- L197 _public prototype_ `FName GetRebroadcastName(const FLiveLinkSubjectKey& InSubjectKey) const;` — Get the rebroadcast name for a given subject. (Defaults to the subject's subject name, but can be overriden.
- L200 _public prototype_ `void PushPendingSubject_AnyThread(FPendingSubjectStatic&& PendingSubject);` — Push subject static data with additional metadata.
- L203 _public function_ `virtual void CacheSubjectSettings(const FLiveLinkSubjectKey& SubjectKey, ULiveLinkSubjectSettings* Settings) const` — (Internal use only) Cache subject settings for a given subject. Currently no-op outside of LiveLinkHub.
- L205 _public prototype_ `void SetLastSavedPreset(ULiveLinkPreset* InPreset);`
- L206 _public prototype_ `ULiveLinkPreset* GetLastSavedPreset() const;`
- L217 _protected prototype_ `bool RegisterGlobalSubjectFramesDelegate(const FOnLiveLinkSubjectStaticDataAdded::FDelegate& InOnStaticDataAdded, const FOnLiveLinkSubjectFrameDataAdded::FDelegate& InOnFrameDataAdded, FDelegateHandle& OutStaticDataAddedHandle, FDelegateHandle& OutFrameDataAddedHandle, bool bUseUnmappedData);` — Add delegates that will be triggered for all subjects. @param InOnStaticDataAdded The delegate for when static data is added. @param InOnFrameDataAdded The delegate for when frame data is added. @param OutStaticDataAddedHandle [Out] The handle for adding static data. @param OutFrameDataAddedHandle [Out] The handle for adding frame data. @param bUseUnmappedData Whether to use raw, unmapped data. If false, then the data received may have a remapper applied.
- L226 _protected prototype_ `void UnregisterGlobalSubjectFramesDelegate(FDelegateHandle& InStaticDataAddedHandle, FDelegateHandle& InFrameDataAddedHandle, bool bUseUnmappedData);` — Remove the delegates that were triggered for all subjects. @param InStaticDataAddedHandle The static data handle to remove. @param InFrameDataAddedHandle The frame data handle to remove. @param bUseUnmappedData Whether this is for unmapped or remapped data.
- L230 _private prototype_ `void Initialize();` — Common initialization code for the different constructors.
- L233 _private prototype_ `void DoPendingWork(TSet<FLiveLinkSubjectKey>& OutUpdatedSubjects);` — Remove old sources & subject,
- L236 _private prototype_ `void UpdateSources();` — Update the added sources
- L243 _private prototype_ `TSet<FLiveLinkSubjectKey> BuildThisTicksSubjectSnapshot(const TSet<FLiveLinkSubjectKey>& ReceivedSubjects);` — Build subject data so that during the rest of the tick it can be read without thread locking or mem copying @return Subjects that were updated by this method.
- L247 _private prototype_ `void RebroadcastSubjects(const TSet<FLiveLinkSubjectKey>& UpdatedSubjects);` — Rebroadcast live (if using evaluated data) and virtual subjects.
- L249 _private prototype_ `void CacheValues();`
- L251 _private prototype_ `void PushSubjectStaticData_Internal(FPendingSubjectStatic&& SubjectStaticData);`
- L252 _private prototype_ `void PushSubjectFrameData_Internal(FPendingSubjectFrame&& SubjectFrameData);`
- L255 _private prototype_ `void Shutdown();` — Remove all sources.
- L258 _private prototype_ `bool HandleSubjectRebroadcast(ILiveLinkSubject* InSubject, const FLiveLinkFrameDataStruct& InFrameData);` — Process virtual subject for rebroadcast purpose
- L263 _private prototype_ `bool HandleSubjectRebroadcast(ILiveLinkSubject* InSubject, FLiveLinkSubjectFrameData&& SubjectFrameData);` — Rebroadcast evaluated livelink data. @note Calling this method will not apply preprocessors and translators since it's meant to be used to transmit evaluated data.
- L266 _private prototype_ `void OnSubjectRemovedCallback(FLiveLinkSubjectKey InSubjectKey);` — Called when a subject is removed. Used to remove rebroadcasted subjects
- L269 _private prototype_ `void RemoveRebroadcastedSubject(FLiveLinkSubjectKey InSubjectKey);` — Removes a subject from the rebroadcast provider and resets it if there are no more subjects
- L272 _private prototype_ `void ForEachLiveSubject(TFunctionRef<void(class FLiveLinkSubject*, struct FLiveLinkCollectionSourceItem&, struct FLiveLinkCollectionSubjectItem&)> VisitorFunc);` — Iterate over every live subject.
- L275 _private prototype_ `void ForEachVirtualSubject(TFunctionRef<void(class ULiveLinkVirtualSubject*, struct FLiveLinkCollectionSourceItem&, struct FLiveLinkCollectionSubjectItem&)> VisitorFunc);` — Iterate over every virtual subject.
- L279 _protected prototype_ `void BroadcastFrameDataUpdate(const FLiveLinkSubjectKey& InSubjectKey, const FLiveLinkFrameDataStruct& InFrameData);` — Broadcast out to the SubjectFrameAddedHandles a frame data update.
- L282 _protected prototype_ `virtual TSharedPtr<ILiveLinkProvider> GetRebroadcastLiveLinkProvider() const;` — Method that can be overriden in child classes to provide their own rebroadcast provider.
- L285 _protected member_ `TUniquePtr<FLiveLinkSourceCollection> Collection;` — The current collection used.
- L288 _protected member_ `TSharedPtr<ILiveLinkProvider> RebroadcastLiveLinkProvider;` — LiveLink Provider for rebroadcasting
- L291 _protected member_ `mutable FCriticalSection PendingFramesCriticalSection;` — Lock to protect access on SubjectFrameToPush and SubjectStaticToPush.
- L294 _protected member_ `TMap<FLiveLinkSubjectKey, FLiveLinkFrameIdentifier> SubjectFrameCounters;` — FrameId counters used when sources don't set it themselves.
- L297 _protected member_ `mutable FCriticalSection SubjectFrameCountersLock;` — Lock to protect access to SubjectFrameCounters.
- L301 _private member_ `TArray<FPendingSubjectStatic> SubjectStaticToPush;` — Pending static info to add to a subject.
- L304 _private member_ `TArray<FPendingSubjectFrame> SubjectFrameToPush;` — Pending frame info to add to a subject.
- L307 _private member_ `TMap<FLiveLinkSubjectName, TStrongObjectPtr<ULiveLinkSubjectSettings>> CachedPresetSubjectSettings;` — Cached subject settings from presets, used to restore preprocessors when subjects are recreated (e.g. after source reconnection).
- L310 _private member_ `TMap<FLiveLinkSubjectName, FLiveLinkSubjectKey> EnabledSubjects;` — Key funcs for looking up a set of cached keys by its layout element
- L323 _private member_ `TMap<FLiveLinkSubjectName, FSubjectFramesAddedHandles> SubjectFrameAddedHandles;` — Map of delegates to notify interested parties when the client receives a static or data frame for each subject
- L332 _private member_ `TMap<FLiveLinkSubjectKey, FSubjectFramesReceivedHandles> SubjectFrameReceivedHandles;` — Delegate when LiveLinkClient received a subject static or frame data.
- L335 _private member_ `mutable FCriticalSection SubjectFrameReceivedHandleseCriticalSection;` — Lock to to access SubjectFrameReceivedHandles
- L338 _private member_ `FSimpleMulticastDelegate OnLiveLinkTickedDelegate;` — Delegate when LiveLinkClient has ticked.
- L340 _private member_ `FString RebroadcastLiveLinkProviderName;`
- L341 _private member_ `TSet<FLiveLinkSubjectKey> RebroadcastedSubjects;`
- L345 _private member_ `bool bPreProcessRebroadcastFrames = false;` — Whether to Preprocess frames before rebroadcasting them.
- L348 _private member_ `bool bTranslateRebroadcastFrames = false;` — Whether to translate frames before rebroadcasting them.
- L351 _private member_ `bool bEnableParentSubjects = false;` — Whether or not parent subject support is enabled. Parent subjects allow resampling data to a different subject's rate before rebroadcasting it.
- L354 _private member_ `TWeakObjectPtr<ULiveLinkPreset> LastSavedPreset;` — Tracks the last preset saved or loaded by the user in this session.
- L358 _private member_ `FOnLiveLinkSubjectEvaluated OnLiveLinkSubjectEvaluatedDelegate;` — Delegate when a subject is evaluated.
- L361 _private member_ `TOptional<FQualifiedFrameTime> CachedEngineFrameTime;` — Cached value of the engine timecode and frame rate

#### struct `FLiveLinkClient::FPendingSubjectStatic`  
`struct FPendingSubjectStatic`  
_L150-156_
- desc: Struct that hold the pending static data that will be pushed next tick.
- L152 _public member_ `FLiveLinkSubjectKey SubjectKey;`
- L153 _public member_ `TSubclassOf<ULiveLinkRole> Role;`
- L154 _public member_ `FLiveLinkStaticDataStruct StaticData;`
- L155 _public member_ `TMap<FName, FString> ExtraMetadata;`

#### struct `FLiveLinkClient::FPendingSubjectFrame`  
`struct FPendingSubjectFrame`  
_L159-163_
- desc: Struct that hold the pending frame data that will be pushed next tick.
- L161 _public member_ `FLiveLinkSubjectKey SubjectKey;`
- L162 _public member_ `FLiveLinkFrameDataStruct FrameData;`

#### struct `FLiveLinkClient::FSubjectFramesAddedHandles`  
`struct FSubjectFramesAddedHandles`  
_L312-320_
- L314 _public member_ `FOnLiveLinkSubjectStaticDataAdded OnStaticDataAdded;`
- L315 _public member_ `FOnLiveLinkSubjectFrameDataAdded OnFrameDataAdded;`
- L317 _public member_ `FOnLiveLinkSubjectStaticDataAdded OnUnmappedStaticDataAdded;` — Original data that hasn't been remapped.
- L319 _public member_ `FOnLiveLinkSubjectFrameDataAdded OnUnmappedFrameDataAdded;` — Original data that hasn't been remapped.

#### struct `FLiveLinkClient::FSubjectFramesReceivedHandles`  
`struct FSubjectFramesReceivedHandles`  
_L325-329_
- L327 _public member_ `FOnLiveLinkSubjectStaticDataReceived OnStaticDataReceived;`
- L328 _public member_ `FOnLiveLinkSubjectFrameDataReceived OnFrameDataReceived;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LIVELINK_API`
- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLink, Log, All);` — Live Link Log Category
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLink, Log, All);` — Live Link Log Category
- L22 _delegate_ `DECLARE_STATS_GROUP(TEXT("Live Link"), STATGROUP_LiveLink, STATCAT_A`
- L40 _namespace_ `namespace UE`
- L40 _namespace_ `namespace LiveLink` (scope `UE`)
- L40 _namespace_ `namespace Private` (scope `UE::LiveLink`)
- L43 _variable_ `static const FName ALL_SUBJECTS_DELEGATE_TOKEN = "__` (scope `UE::LiveLink::Private`) — Name token  used to register to all subject updates.
- L56 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FLiveLinkTickDelegate, ELiveLinkTickType) FLiveLinkClient(FLiveLinkTickDelegate& InTickingDelegate);`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkClientReference.h` (Public)


#### struct `FLiveLinkClientReference`  
`struct FLiveLinkClientReference`  
_L12-16_
- desc: References the live link client
- L15 _public prototype_ `ILiveLinkClient* GetClient() const;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkComponent.h` (Public)


#### class `ULiveLinkComponent`  
`class ULiveLinkComponent : public UActorComponent`  
_L20-45_
- reflection: `UCLASS(MinimalAPI, ClassGroup=(LiveLink), meta=(BlueprintSpawnableComponent), meta = (DisplayName = "LiveLink Skeletal Animation"))`
- inherits: `UActorComponent`
- desc: An actor component to enable accessing LiveLink data in Blueprints. Data can be accessed in Editor through the "OnLiveLinkUpdated" event. Any Skeletal Mesh Components on the parent will be set to animate in editor causing their AnimBPs to run.
- L26 _public prototype_ `ULiveLinkComponent();` — Sets default values for this component's properties
- L29 _protected prototype_ `virtual void OnRegister() override;`
- L33 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;` — Called every frame
- L37 _public member_ `FLiveLinkTickSignature OnLiveLinkUpdated;` — `UPROPERTY(BlueprintAssignable, Category = "LiveLink")` — This Event is triggered any time new LiveLink data is available, including in the editor
- L39 _private prototype_ `bool HasLiveLinkClient();`
- L42 _private member_ `bool bIsDirty;` — Record whether we have been recently registered
- L44 _private member_ `ILiveLinkClient* LiveLinkClient;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LIVELINK_API`
- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLiveLinkTickSignature, float, DeltaTime);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLiveLinkTickSignature, float, DeltaTime);`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkCustomTimeStep.h` (Public)


#### class `ULiveLinkCustomTimeStep`  
`class ULiveLinkCustomTimeStep : public UGenlockedCustomTimeStep`  
_L37-183_
- reflection: `UCLASS(Blueprintable, editinlinenew, MinimalAPI)`
- inherits: `UGenlockedCustomTimeStep`
- desc: Control the Engine TimeStep via a live link source Philosophy: * Quantized time steps based on live link expected data rate. * Made for Live Link sources can receive data asynchronously, and therefore trigger the waiting game thread. * FApp::GetDeltaTime - Forced to a multiple of the desired FrameTime. - This multiple will depend on Frame Id increment and user settings. * FApp::GetCurrentTime - Incremented in multiples of the desired FrameTime.
- L43 _public prototype_ `virtual bool Initialize(UEngine* InEngine) override;`
- L44 _public prototype_ `virtual void Shutdown(UEngine* InEngine) override;`
- L45 _public prototype_ `virtual bool UpdateTimeStep(UEngine* InEngine) override;`
- L46 _public prototype_ `virtual ECustomTimeStepSynchronizationState GetSynchronizationState() const override;`
- L47 _public prototype_ `virtual FFrameRate GetFixedFrameRate() const override;`
- L48 _public prototype_ `virtual FFrameRate GetSyncRate() const override;`
- L49 _public prototype_ `virtual FString GetDisplayName() const override;`
- L52 _public prototype_ `virtual uint32 GetLastSyncCountDelta() const override;`
- L53 _public prototype_ `virtual bool IsLastSyncDataValid() const override;`
- L54 _public prototype_ `virtual bool WaitForSync() override;`
- L55 _public prototype_ `virtual uint32 GetExpectedSyncCountDelta() const override;`
- L58 _public prototype_ `FQualifiedFrameTime GetGenlockTriggerSceneTime() const;` — Returns the SceneTime captured at the most recent genlock trigger point.
- L61 _public prototype_ `virtual void BeginDestroy() override;`
- L63 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L70 _private prototype_ `void InitLiveLinkClient();` — Initializes the Live Link client (callbacks, etc)
- L73 _private prototype_ `void UninitLiveLinkClient();` — Uninitializes the Live Link client (callbacks, etc)
- L76 _private prototype_ `void RegisterLiveLinkSubject();` — Registers the selected subject for data callbacks
- L79 _private prototype_ `void UnregisterLiveLinkSubject();` — Unregisters the data callbacks related to the live link subject
- L82 _private prototype_ `void OnLiveLinkClientRegistered(const FName& Type, class IModularFeature* ModularFeature);` — Called when a Live Link modular features is registered
- L85 _private prototype_ `void OnLiveLinkClientUnregistered(const FName& Type, class IModularFeature* ModularFeature);` — Called when a Live Link modular feature is unregistered
- L88 _private prototype_ `void OnLiveLinkSubjectAdded(FLiveLinkSubjectKey SubjectKey);` — Called when a new live link subject is added, so that we can check if is the one we're listening for
- L91 _private prototype_ `void OnLiveLinkSubjectRemoved(FLiveLinkSubjectKey SubjectKey);` — Called when a live link subject is removed. It may be the one we were listening to
- L94 _private prototype_ `void OnLiveLinkFrameDataReceived_AnyThread(const FLiveLinkFrameDataStruct& FrameData);` — Called when our live link subject has received data. This is equivalent to a genlock sync signal
- L100 _public member_ `FFrameRate LiveLinkDataRate = FFrameRate(60, 1);` — `UPROPERTY(EditAnywhere, Category = Timing)` — Expected Live Link data rate. If real rate differs, then delta times will contract/expand with respect to real time
- L104 _public member_ `FLiveLinkSubjectKey SubjectKey;` — `UPROPERTY(EditAnywhere, Category = Timing)` — The specific subject that we listen to.
- L113 _public member_ `bool bLockStepMode = true;` — `UPROPERTY(EditAnywhere, Category = Timing)` — Lockstep mode means that we only allow FrameRateDivider data frames of the selected subject per engine loop. The idea here is to process all packets and avoid Live Link evaluation to skip frames when the engine hitches, and the live link transport will serve as implicit FIFO buffer. However if the Engine cannot keep up with the data rate, a large delay will be introduced and the transport buffer will eventually start dropping data.
- L117 _public member_ `uint32 FrameRateDivider = 1;` — `UPROPERTY(EditAnywhere, Category = Timing, meta = (ClampMin = 1, ClampMax = 256, UIMin = 1, UIMax = 256))` — Allows genlock to period to be a multiple of the live link data period. For example a value of 2 will run at half the live link data rate
- L121 _public member_ `double TimeoutInSeconds = 1.0;` — `UPROPERTY(EditAnywhere, Category = Advanced, AdvancedDisplay)` — Determines how long it should wait for live link data before deciding that it is not in synchronized state anymore
- L126 _private member_ `ILiveLinkClient* LiveLinkClient;` — This is how we access live link objects. It is obtained using modular features.
- L129 _private member_ `FLiveLinkSubjectKey RegisteredSubjectKey;` — Identifies the Live Link subject that we are genlocking to.
- L132 _private member_ `FDelegateHandle RegisterForFrameDataReceivedHandle;` — Gets called when the subject gets new data. This is the basis for the genlock.
- L135 _private member_ `std::atomic<ECustomTimeStepSynchronizationState> State = ECustomTimeStepSynchronizationState::Closed;` — Keeps track of the current state. For the most part, if we are getting data from the subject, it is synchronized.
- L138 _private member_ `FEventRef EventLiveLink{ EEventMode::AutoReset };` — Helps trigger the wait for sync function from an asynchronous thread
- L141 _private member_ `FEventRef EventWaitForSync{ EEventMode::AutoReset };` — Used in lockstep mode, where we only allow one live link subject data frame per engine tick
- L144 _private member_ `std::atomic<FLiveLinkFrameIdentifier> LastFrameId = 0;` — Keeps track of the last frame id received for a given subject, and used to calcualte delta time based on source data rate.
- L147 _private member_ `std::atomic<uint32> SyncCount = 0;` — Incremented based on frame id when live link data is received. Reset when internally read.
- L150 _private member_ `uint32 LastSyncCountDelta = 0;` — Cache of the last sync count delta, used for functions in the game thread that need it.
- L153 _private member_ `std::atomic<bool> bLockStepModeAnyThread = true;` — Shadow of bLockStepMode property
- L156 _private member_ `std::atomic<uint32> FrameRateDividerAnyThread = 1;` — Shadow of FrameRateDivider property
- L159 _private member_ `std::atomic<double> TimeoutInSecondsAnyThread = 1.0;` — Shadow of TimeoutInSeconds property
- L162 _private member_ `FQualifiedFrameTime GenlockTriggerSceneTime;` — SceneTime captured at the most recent genlock trigger point.
- L165 _private member_ `mutable FCriticalSection GenlockSceneTimeLock;` — Protects GenlockTriggerSceneTime across threads.
- L168 _private member_ `std::atomic<int32> LastCapturedTimecodeFrameNumber = INDEX_NONE;` — Frame number of the last captured genlock trigger time, used to ensure deterministic subframe behavior
- L171 _private member_ `std::atomic<int32> ReferenceFrameId = INDEX_NONE;` — FrameId of the reference frame, used for phase alignment
- L174 _private member_ `std::atomic<int32> FramesPerTimecodeAnyThread = 0;` — Cached frames per timecode period (SourceRate / TimecodeRate), calculated at initialization
- L177 _private member_ `std::atomic<bool> bIsSequencerSourceAnyThread = false;` — Cached flag indicating whether the monitored subject is from a sequencer source
- L182 _private member_ `std::atomic<bool> bSkipLockStepWait = false;` — When true, OnLiveLinkFrameDataReceived_AnyThread skips the lockstep wait. This is set before unregistering to avoid blocking the game thread on the critical section held during BroadcastFrameDataUpdate's lockstep wait.

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkDrivenComponent.h` (Public)


#### class `UDEPRECATED_LiveLinkDrivenComponent`  
`class UDEPRECATED_LiveLinkDrivenComponent : public UActorComponent`  
_L11-31_
- reflection: `UCLASS(MinimalAPI, ClassGroup = "LiveLink", deprecated)`
- inherits: `UActorComponent`
- desc: A component that applies data from Live Link to the owning actor
- L18 _public member_ `FLiveLinkSubjectName SubjectName;` — `UPROPERTY(EditAnywhere, Category = "Live Link", meta = (ShowOnlyInnerProperties))` — The name of the live link subject to take data from
- L22 _public member_ `FName ActorTransformBone;` — `UPROPERTY(EditAnywhere, Category = "Live Link")` — The name of the bone to drive the actors transform with (if None then we will take the first bone)
- L26 _public member_ `bool bModifyActorTransform;` — `UPROPERTY(EditAnywhere, Category = "Live Link")` — Should the actors transform be driven by live link
- L30 _public member_ `bool bSetRelativeLocation;` — `UPROPERTY(EditAnywhere, Category = "Live Link")` — Should the transform from live link be treated as relative or world space

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkHubSubjectSettings.h` (Public)


#### class `ULiveLinkHubSubjectSettings`  
`class ULiveLinkHubSubjectSettings : public ULiveLinkSubjectSettings`  
_L16-75_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ULiveLinkSubjectSettings`
- desc: Settings object for a livelinkhub subject.
- L22 _public prototype_ `virtual void Initialize(FLiveLinkSubjectKey InSubjectKey) override;`
- L24 _public function_ `virtual FName GetRebroadcastName() const override`
- L32 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L33 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L36 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPropertyModified, const FName& );`
- L37 _public function_ `FOnPropertyModified OnPropertyModified()`
- L40 _public function_ `static FName GetOutboundNamePropertyName()`
- L45 _public function_ `static FName GetSubjectNamePropertyName()`
- L53 _private member_ `FString SubjectName;` — `UPROPERTY(VisibleAnywhere, Category = "LiveLink")` — Name of this subject.
- L57 _private member_ `FString OutboundName;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")` — Name override that will be transmitted to clients instead of the subject name.
- L61 _private member_ `FString Source;` — `UPROPERTY(VisibleAnywhere, Category = "LiveLink")` — Source that contains the subject.
- L65 _private member_ `TObjectPtr<ULiveLinkFrameTranslator> TranslatorsProxy;` — `UPROPERTY(EditAnywhere, Instanced, Category = "LiveLink", DisplayName = "Translator")` — Proxy property used edit the translators.
- L69 _private member_ `FName PreviousOutboundName;` — Previous outbound name to be used for noticing clients to remove this entry from their subject list.
- L73 _private member_ `FOnPropertyModified OnPropertyModifiedDelegate;` — Triggered when a property is modified.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINK_API`
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPropertyModified, const FName& );`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkMessageBusDiscoveryManager.h` (Public)


#### class `FLiveLinkMessageBusDiscoveryManager`  
`class FLiveLinkMessageBusDiscoveryManager : FRunnable`  
_L17-72_
- inherits: `FRunnable`
- desc: A class to asynchronously discover message bus sources.
- L20 _public prototype_ `FLiveLinkMessageBusDiscoveryManager();`
- L21 _public prototype_ `~FLiveLinkMessageBusDiscoveryManager();`
- L25 _public prototype_ `virtual uint32 Run() override;`
- L27 _public prototype_ `virtual void Stop() override;`
- L31 _public prototype_ `void AddDiscoveryMessageRequest();`
- L32 _public prototype_ `void RemoveDiscoveryMessageRequest();`
- L33 _public prototype_ `TArray<FProviderPollResultPtr> GetDiscoveryResults() const;`
- L35 _public prototype_ `bool IsRunning() const;`
- L38 _public prototype_ `FMessageAddress GetEndpointAddress() const;` — Get the message bus address for the discovery manager's endpoint.
- L41 _private prototype_ `void HandlePongMessage(const FLiveLinkPongMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);`
- L45 _private member_ `TAtomic<int32> PingRequestCounter;` — Counter of item that request discovery message
- L48 _private member_ `FGuid LastPingRequest;` — Last ping Request id
- L51 _private member_ `double LastPingRequestTime;` — Time of the last ping request
- L54 _private member_ `FTimespan PingRequestFrequency;` — Ping request timeout
- L57 _private member_ `TArray<FProviderPollResultPtr> LastProviderPoolResults;` — Result from the last ping request
- L59 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;`
- L62 _private member_ `FThreadSafeBool bRunning;` — Thread safe bool for stopping the thread
- L65 _private member_ `FRunnableThread* Thread;` — Thread the heartbeats are sent on
- L68 _private member_ `class FEvent* PollEvent = nullptr;` — Event used to poll the discovery results.
- L71 _private member_ `mutable FCriticalSection SourcesCriticalSection;` — Critical section for accessing the Source Set

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkMessageBusFinder.h` (Public)


#### struct `FProviderPollResult`  
`struct FProviderPollResult`  
_L24-77_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public prototype_ `FProviderPollResult() = default;`
- L31 _public function_ `FProviderPollResult(const FMessageAddress& InAddress, const FString& InName, const FString& InMachineName, double InMachineOffset, bool bInIsValidProvider) : Address(InAddress) , Name(InName) , MachineName(InMachineName) , MachineTimeOffset(InMachineOffset) , bIsValidProvider(bInIsValidProvider) , Annotations()`
- L40 _public function_ `FProviderPollResult(const FMessageAddress& InAddress, const FString& InName, const FString& InMachineName, double InMachineOffset, bool bInIsValidProvider, TMap<FName, FString> InAnnotations) : Address(InAddress) , Name(InName) , MachineName(InMachineName) , MachineTimeOffset(InMachineOffset) , bIsValidProvider(bInIsValidProvider) , Annotations(MoveTemp(InAnnotations))`
- L50 _public function_ `const TMap<FName, FString>& GetAnnotations() const` — Get  the annotations that were present on the message.
- L53 _public member_ `FMessageAddress Address;` — Messagebus address of the provider
- L57 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="LiveLink", meta=(DisplayName = "Provider Name"))` — The name of the provider
- L61 _public member_ `FString MachineName;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="LiveLink")` — The name of the machine the provider is running on
- L65 _public member_ `double MachineTimeOffset = 0.0;` — `UPROPERTY()` — Offset between sender's engine time and receiver's engine time
- L69 _public member_ `bool bIsValidProvider = true;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LiveLink")` — Whether the provider is valid (compatible with the current version of LiveLink)
- L73 _public member_ `int32 DiscoveryProtocolVersion = 1;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LiveLink")` — Version of the discovery protocol.
- L76 _public member_ `TMap<FName, FString> Annotations;` — Annotations present on the message

#### class `ULiveLinkMessageBusFinder`  
`class ULiveLinkMessageBusFinder : public UObject`  
_L83-132_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: Asset for finding available Message Bus Sources.
- L89 _public prototype_ `ULiveLinkMessageBusFinder();`
- L98 _public prototype_ `void GetAvailableProviders(UObject* WorldContextObject, struct FLatentActionInfo LatentInfo, float Duration, TArray<FProviderPollResult>& AvailableProviders);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink", meta=(Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject", Duration = "0.2"))` — Broadcasts a message to the network and returns a list of all providers who replied within a set amount of time. @param AvailableProviders Will contain the collection of found Message Bus Providers. @param Duration The amount of time to wait for replies in seconds
- L107 _public prototype_ `static void ConnectToProvider(UPARAM(ref) FProviderPollResult& Provider, FLiveLinkSourceHandle& SourceHandle);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Connects to a given Message Bus Provider and returns a handle to the created LiveLink Source @param Provider The provider to connect to. @param SourceHandle A handle to the created LiveLink Source, lets you query information about the created source and request a shutdown
- L115 _public prototype_ `static ULiveLinkMessageBusFinder* ConstructMessageBusFinder();` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Constructs a new Message Bus Finder which enables you to detect available Message Bus Providers on the network @return The newly constructed Message Bus Finder
- L118 _public prototype_ `void PollNetwork();` — Broadcast a ping message to the network and listen for responses
- L121 _public prototype_ `void GetPollResults(TArray<FProviderPollResult>& AvailableProviders);` — Populates AvailableProviders with the Providers who have responded to the latest poll.
- L125 _private prototype_ `void HandlePongMessage(const FLiveLinkPongMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Runs when a Provider responds to the ping from PollNetwork()
- L127 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;`
- L128 _private member_ `TArray<FProviderPollResult> PollData;`
- L129 _private member_ `FGuid CurrentPollRequest;`
- L131 _private member_ `FCriticalSection PollDataCriticalSection;`

#### struct `FLiveLinkMessageBusFinderAction`  
`struct FLiveLinkMessageBusFinderAction : public FPendingLatentAction`  
_L135-174_
- inherits: `FPendingLatentAction`
- L138 _public member_ `FName ExecutionFunction;`
- L139 _public member_ `int32 OutputLink;`
- L140 _public member_ `FWeakObjectPtr CallbackTarget;`
- L141 _public member_ `TWeakObjectPtr<ULiveLinkMessageBusFinder> MessageBusFinderWeakPtr;`
- L142 _public member_ `TArray<FProviderPollResult>& OutAvailableProviders;`
- L143 _public member_ `float RemainingTime;`
- L145 _public function_ `FLiveLinkMessageBusFinderAction(const FLatentActionInfo& InLatentInfo, ULiveLinkMessageBusFinder* InMessageBusFinder, float Duration, TArray<FProviderPollResult>& InAvailableProviders) : FPendingLatentAction() , ExecutionFunction(InLatentInfo.ExecutionFunction) , OutputLink(InLatentInfo.Linkage) , CallbackTarget(InLatentInfo.CallbackTarget) , MessageBusFinderWeakPtr(InMessageBusFinder) , OutAvailableProviders(InAvailableProviders) , RemainingTime(Duration)`
- L155 _public function_ `virtual void UpdateOperation(FLatentResponse& Response) override`
- L169 _public function_ `virtual FString GetDescription() const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LIVELINK_API`
- L18 _namespace_ `namespace LiveLinkMessageBusHelper`
- L20 _prototype_ `double CalculateProviderMachineOffset(double SourceMachinePlatformSeconds, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` (scope `LiveLinkMessageBusHelper`)
- L79 _typedef_ `typedef TSharedPtr<FProviderPollResult, ESPMode::ThreadSafe> FProviderPollResultPtr;`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkMessageBusSource.h` (Public)


#### class `FLiveLinkMessageBusSource`  
`class FLiveLinkMessageBusSource : public ILiveLinkSource`  
_L24-247_
- inherits: `ILiveLinkSource`
- L28 _public prototype_ `static FText ValidSourceStatus();` — Text description for a valid source.
- L30 _public prototype_ `static FText InvalidSourceStatus();` — Text description for an invalid source.
- L32 _public prototype_ `static FText TimeoutSourceStatus();` — Text description for a source that has timed out.
- L34 _public prototype_ `FLiveLinkMessageBusSource(const FText& InSourceType, const FText& InSourceMachineName, const FMessageAddress& InConnectionAddress, double InMachineTimeOffset);`
- L37 _public prototype_ `virtual void InitializeSettings(ULiveLinkSourceSettings* Settings) override;`
- L38 _public prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;`
- L39 _public prototype_ `virtual void Update() override;`
- L41 _public prototype_ `virtual bool IsSourceStillValid() const override;`
- L43 _public prototype_ `virtual bool RequestSourceShutdown() override;`
- L45 _public function_ `virtual FText GetSourceType() const override`
- L46 _public function_ `virtual FText GetSourceMachineName() const override`
- L48 _public prototype_ `virtual FText GetSourceStatus() const override;`
- L49 _public prototype_ `virtual FText GetSourceToolTip() const override;`
- L50 _public prototype_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const override;`
- L54 _public prototype_ `FMessageAddress GetAddress() const;` — Get this source's message bus address.
- L58 _protected prototype_ `virtual const FName& GetSourceName() const;` — Returns the source name to uniquely identify it among the FLiveLinkMessageBusSource classes
- L60 _protected prototype_ `virtual void InitializeMessageEndpoint(FMessageEndpointBuilder& EndpointBuilder);` — This lets child classes the opportunity to add custom message handlers to the endpoint builder
- L62 _protected function_ `virtual void PostInitializeMessageEndpoint(const TSharedPtr<FMessageEndpoint>& Endpoint)` — This lets child classes get a shared ptr of the message endpoint after it's done initializing.
- L64 _protected prototype_ `void AddAnnotations(TMap<FName, FString>& InOutAnnotations) const;` — Add MessageBus annotations.
- L66 _protected function_ `bool IsMessageEndpointConnected() const` — Returns whether this endpoint is currently connected.
- L69 _protected prototype_ `virtual void InitializeAndPushStaticData_AnyThread(FName SubjectName, TSubclassOf<ULiveLinkRole> SubjectRole, const FLiveLinkSubjectKey& SubjectKey, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, UScriptStruct* MessageTypeInfo);` — Initialize the static data and send it to the clients
- L75 _protected prototype_ `virtual void InitializeAndPushFrameData_AnyThread(FName SubjectName, const FLiveLinkSubjectKey& SubjectKey, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, UScriptStruct* MessageTypeInfo);` — Initialize the frame data and send it to the clients
- L81 _protected prototype_ `virtual double GetDeadSourceTimeout() const;` — Allows derived classes to provide their own timeout duration before a source is removed because the heartbeat timeout was hit
- L84 _protected prototype_ `void PushClientSubjectStaticData_AnyThread(const FLiveLinkSubjectKey& SubjectKey, TSubclassOf<ULiveLinkRole> Role, FLiveLinkStaticDataStruct&& StaticData);` — Send the static data to the clients
- L86 _protected prototype_ `void PushClientSubjectFrameData_AnyThread(const FLiveLinkSubjectKey& SubjectKey, FLiveLinkFrameDataStruct&& FrameData);` — Send the frame data to the clients
- L89 _protected prototype_ `virtual void SendConnectMessage();` — Send connect message to the provider and start the heartbeat emitter
- L93 _protected function_ `template<typename MessageType> void SendMessage(MessageType* Message, const TMap<FName, FString>& Annotations = {})` — Send a message through the endpoint
- L104 _protected prototype_ `void StartHeartbeatEmitter();` — Start the heartbeat emitter for this connection
- L108 _protected member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Message bus endpoint responsible for communication with the livelink provider
- L111 _protected member_ `FMessageAddress ConnectionAddress;` — Connection address of the livelink provider
- L114 _protected member_ `std::atomic<bool> bIsValid;` — Current Validity of Source
- L116 _protected member_ `std::atomic<bool> bIsShuttingDown = false;` — Whether we're in the process of shutting down this source.
- L118 _protected member_ `ILiveLinkClient* Client;`
- L121 _protected member_ `FGuid SourceGuid;` — Our identifier in LiveLink
- L124 _protected member_ `std::atomic<bool> bCachedEnableFrameResequencing = true;` — Cached settings values (atomics for thread-safe access from _AnyThread methods)
- L125 _protected member_ `std::atomic<int32> CachedResequencerMaxBufferSize = 32;`
- L126 _protected member_ `std::atomic<float> CachedResequencerMaxWaitTimeSeconds = 0.1f;`
- L129 _private prototype_ `void CreateAndInitializeMessageEndpoint();`
- L132 _private prototype_ `void HandleHeartbeat(const FLiveLinkHeartbeatMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);`
- L133 _private prototype_ `void HandleClearSubject(const FLiveLinkClearSubject& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);`
- L134 _private prototype_ `void InternalHandleMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);`
- L138 _private prototype_ `inline void UpdateConnectionLastActive();` — Threadsafe update of the last active time
- L141 _private prototype_ `void StartDiscovering();` — Start discovering sources
- L144 _private prototype_ `void StopDiscovering();` — Stop discovering sources
- L147 _private prototype_ `void Initialize();` — Initialize (can be used after a shutdown request)
- L150 _private prototype_ `void ResequenceAndPushFrame(const FLiveLinkSubjectKey& SubjectKey, FLiveLinkFrameDataStruct&& FrameData);` — Resequencer for maintaining frame order per subject
- L153 _private prototype_ `void CacheMessageBusSourceSettings();` — Cache Message Bus settings
- L210 _private member_ `TMap<FName, FFrameResequencer> SubjectResequencers;` — Per-subject map of frame resequencers for maintaining ordered frame delivery
- L213 _private member_ `FCriticalSection ResequencerCriticalSection;` — Critical section for thread-safe access to SubjectResequencers
- L216 _private member_ `TArray<TWeakObjectPtr<ULiveLinkRole>> RoleInstances;` — List of the roles available when the bus was opened
- L218 _private member_ `FText SourceType;`
- L219 _private member_ `FText SourceMachineName;`
- L222 _private member_ `TWeakObjectPtr<class ULiveLinkMessageBusSourceSettings> SourceSettings;` — Weak pointer to the source settings, used to cache source settings values when they're modified.
- L225 _private member_ `double ConnectionLastActive;` — Time we last received anything
- L228 _private member_ `FCriticalSection ConnectionLastActiveSection;` — Critical section to allow for threadsafe updating of the connection time
- L231 _private member_ `double MachineTimeOffset;` — Offset between sender's machine engine time and receiver's machine engine time
- L234 _private member_ `float CachedThroughput = 0.f;` — Cached throughput (in kb/s) of data going through this messagebus source.
- L237 _private member_ `float LastThroughputUpdate = 0.f;` — Timestamp of the last update to the cached throughput.
- L240 _private member_ `float AccumulatedBytes = 0.f;` — Number of bytes received since LastThroughputUpdate.
- L243 _private member_ `bool bDiscovering;` — Actively discovering the source
- L246 _private member_ `bool bInitialized;` — Flag to keep track of initialization state

#### struct `FLiveLinkMessageBusSource::FFrameResequencer`  
`struct FFrameResequencer`  
_L158-207_
- desc: Per-subject frame resequencer to deliver live link frames in FrameId order
- L168 _public member_ `TArray<FBufferedFrame> BufferedFrames;` — Buffered frames waiting for delivery (only used when frames arrive out of order)
- L171 _public member_ `TOptional<FLiveLinkFrameIdentifier> LastDeliveredFrameId;` — Last delivered FrameId - used to detect and deliver the next expected frame immediately
- L174 _public member_ `double OldestFrameBufferTime = 0.0;` — Timestamp when oldest frame was buffered (for timeout detection)
- L177 _public member_ `int32 MaxBufferSize = 32;` — Maximum number of frames to buffer
- L180 _public member_ `double MaxWaitTimeSeconds = 0.1;` — Maximum time in seconds to wait for missing frames
- L183 _public member_ `int32 ReorderedFrameCount = 0;` — Stats: Number of frames that arrived out of order and were resequenced
- L186 _public member_ `int32 DroppedLateFrameCount = 0;` — Stats: Number of frames dropped because they arrived too late to be delivered in order
- L189 _public member_ `int32 PeakBufferDepth = 0;` — Stats: Maximum number of frames held in the buffer simultaneously
- L194 _public prototype_ `void AddFrame(FLiveLinkFrameDataStruct&& Frame, double CurrentTime);` — Add a frame to the buffer
- L197 _public prototype_ `bool TryPopNextFrame(FLiveLinkFrameDataStruct& OutFrame, double CurrentTime);` — Try to pop the next ordered frame from buffer
- L200 _public prototype_ `void Flush(TArray<FLiveLinkFrameDataStruct>& OutFrames);` — Flush all buffered frames
- L203 _public prototype_ `bool IsFrameTooLate(const FLiveLinkFrameDataStruct& Frame) const;` — Check if a frame should be dropped as too late
- L206 _public prototype_ `void UpdateLastDelivered(const FLiveLinkFrameDataStruct& Frame);` — Update last delivered tracking after delivering a frame

#### struct `FLiveLinkMessageBusSource::FFrameResequencer::FBufferedFrame`  
`struct FBufferedFrame`  
_L161-165_
- L163 _public member_ `FLiveLinkFrameDataStruct Frame;`
- L164 _public member_ `double BufferedAtSeconds = 0.0;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkMessageBusSourceFactory.h` (Public)


#### class `ULiveLinkMessageBusSourceFactory`  
`class ULiveLinkMessageBusSourceFactory : public ULiveLinkSourceFactory`  
_L15-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ULiveLinkSourceFactory`
- L20 _public prototype_ `virtual FText GetSourceDisplayName() const override;`
- L21 _public prototype_ `virtual FText GetSourceTooltip() const override;`
- L23 _public function_ `virtual EMenuType GetMenuType() const override`
- L24 _public prototype_ `virtual TSharedPtr<SWidget> BuildCreationPanel(FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const override;`
- L25 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& ConnectionString) const override;`
- L27 _public prototype_ `static FString CreateConnectionString(const struct FProviderPollResult& Result);`
- L31 _protected prototype_ `virtual TSharedPtr<class FLiveLinkMessageBusSource> MakeSource(const FText& Name, const FText& MachineName, const FMessageAddress& Address, double TimeOffset) const;` — This allows the creation of a message bus source derived from FLiveLinkMessageBusSource
- L36 _protected prototype_ `void OnSourceSelected(FProviderPollResultPtr SelectedSource, FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkMessageBusSourceSettings.h` (Public)


#### class `ULiveLinkMessageBusSourceSettings`  
`class ULiveLinkMessageBusSourceSettings : public ULiveLinkSourceSettings`  
_L19-57_
- reflection: `UCLASS(config=Game, MinimalAPI)`
- inherits: `ULiveLinkSourceSettings`
- desc: Settings for LiveLinkMessageBusSource. Used to apply default Evaluation mode from project settings when constructed
- L25 _public prototype_ `ULiveLinkMessageBusSourceSettings();`
- L29 _public member_ `bool bEnableFrameResequencing = true;` — `UPROPERTY(config, EditAnywhere, Category = "Resequencing")` — Enable frame resequencing to counteract UDP Messaging delivering them out of order.
- L33 _public member_ `int32 ResequencerMaxBufferSize = 32;` — `UPROPERTY(config, EditAnywhere, Category = "Resequencing", meta = (EditCondition = "bEnableFrameResequencing", ClampMin = "4", ClampMax = "128"))` — Maximum number of frames to buffer per subject. If exceeded, oldest frames are pushed even if out of order.
- L37 _public member_ `float ResequencerMaxWaitTimeSeconds = 0.1f;` — `UPROPERTY(config, EditAnywhere, Category = "Resequencing", meta = (EditCondition = "bEnableFrameResequencing", ClampMin = "0.01", ClampMax = "10.0"))` — Maximum time in seconds to hold frames waiting for missing frames.
- L40 _public function_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override`
- L54 _public member_ `FTSSimpleMulticastDelegate OnPropertyChangedDelegate;` — Delegate triggered whenever a message bus source settings property is modified.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkPreset.h` (Public)


#### class `ULiveLinkPreset`  
`class ULiveLinkPreset : public UObject`  
_L15-81_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L19 _private prototype_ `virtual ~ULiveLinkPreset();`
- L23 _private member_ `TArray<FLiveLinkSourcePreset> Sources;` — `UPROPERTY(VisibleAnywhere, Category = "LiveLinkSourcePresets")`
- L26 _private member_ `TArray<FLiveLinkSubjectPreset> Subjects;` — `UPROPERTY(VisibleAnywhere, Category = "LiveLinkSubjectPresets")`
- L30 _public function_ `const TArray<FLiveLinkSourcePreset>& GetSourcePresets() const` — Get the list of source presets.
- L33 _public function_ `const TArray<FLiveLinkSubjectPreset>& GetSubjectPresets() const` — Get the list of subject presets.
- L41 _public prototype_ `bool ApplyToClient() const;` — `UE_DEPRECATED(5.0, "This function is deprecated, please use ApplyToClientLatent")` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category="LiveLink")` — Remove all previous sources and subjects and add the sources and subjects from this preset. @return True is all sources and subjects from this preset could be created and added.
- L48 _public prototype_ `void ApplyToClientLatent(UObject* WorldContextObject, FLatentActionInfo LatentInfo);` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category="LiveLink", meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))` — Remove all previous sources and subjects and add the sources and subjects from this preset. @return True is all sources and subjects from this preset could be created and added.
- L49 _public prototype_ `void ApplyToClientLatent(TFunction<void(bool)> CompletionCallback = nullptr);`
- L52 _public prototype_ `void CancelLatentAction();` — Cancels the current latent action and prevents the callback from firing. Only valid for C++ variant.
- L62 _public prototype_ `bool AddToClient(const bool bRecreatePresets = true) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "LiveLink")` — Add the sources and subjects from this preset, but leave any existing sources and subjects connected. @param bRecreatePresets	When true, if subjects and sources from this preset already exist, we will recreate them. @return True is all sources and subjects from this preset could be created and added.
- L66 _public prototype_ `void BuildFromClient();` — `UFUNCTION(BlueprintCallable, Category="LiveLink")` — Reset this preset and build the list of sources and subjects from the client.
- L70 _private prototype_ `void ClearApplyToClientTimer();` — Clear the timer registered with the current world.
- L74 _private member_ `FDelegateHandle ApplyToClientEndFrameHandle;` — Holds a handle to the OnEndFrame delegate used to apply a preset asynchronously with ApplyToClientLatent.
- L77 _private member_ `static TPimplPtr<struct FApplyToClientPollingOperation> ApplyToClientPollingOperation;` — Holds the current ApplyToClient async operation. Only one operation for all presets can be done at a time.
- L80 _private member_ `uint32 ApplyCount = 0;` — Utility variable used to keep track of the number of times this was applied.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkRetargetAssetReference.h` (Public)


#### struct `FLiveLinkRetargetAssetReference`  
`FLiveLinkRetargetAssetReference`  
_L14-18_
- reflection: `UE_DEPRECATED(4.23, "FLiveLinkRetargetAssetReference is no longer used.")`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkSettings.h` (Public)


#### struct `FLiveLinkRoleProjectSetting`  
`struct FLiveLinkRoleProjectSetting`  
_L27-51_
- reflection: `USTRUCT()`
- desc: Settings for LiveLinkRole.
- L32 _public prototype_ `FLiveLinkRoleProjectSetting() = default;`
- L33 _public prototype_ `FLiveLinkRoleProjectSetting(TSubclassOf<ULiveLinkSubjectSettings> DefaultSettingsClass);`
- L38 _public member_ `TSubclassOf<ULiveLinkRole> Role;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLink")` — The role of the current setting.
- L42 _public member_ `TSubclassOf<ULiveLinkSubjectSettings> SettingClass;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLink")` — The settings class to use for the subject. If null, LiveLinkSubjectSettings will be used by default.
- L46 _public member_ `TSubclassOf<ULiveLinkFrameInterpolationProcessor> FrameInterpolationProcessor;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLink")` — The interpolation to use for the subject. If null, no interpolation will be performed.
- L50 _public member_ `TArray<TSubclassOf<ULiveLinkFramePreProcessor>> FramePreProcessors;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLink")` — The pre processors to use for the subject.

#### class `ULiveLinkUserSettings`  
`class ULiveLinkUserSettings : public UObject`  
_L54-65_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- L61 _public member_ `FDirectoryPath PresetSaveDir;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLink", meta = (DisplayName = "Preset Save Location"))` — The default location in which to save LiveLink presets
- L64 _public function_ `const FDirectoryPath& GetPresetSaveDir() const`

#### class `ULiveLinkSettings`  
`class ULiveLinkSettings : public UObject`  
_L71-194_
- reflection: `UCLASS(MinimalAPI, config=Game, defaultconfig)`
- inherits: `UObject`
- desc: Settings for LiveLink.
- L76 _public prototype_ `ULiveLinkSettings();`
- L79 _public prototype_ `virtual void PostInitProperties() override;`
- L84 _public member_ `TArray<FLiveLinkRoleProjectSetting> DefaultRoleSettings;` — `UPROPERTY(config, EditAnywhere, Category="LiveLink")`
- L88 _public member_ `FSoftClassPath DefaultSettingsClass;` — `UPROPERTY(config)` — When a settings class is not speficied for a role, this settings class will be used.
- L92 _public member_ `TSubclassOf<ULiveLinkFrameInterpolationProcessor> FrameInterpolationProcessor;` — `UPROPERTY(config)` — The interpolation class to use for new Subjects if no specific settings we set for the Subject's role.
- L96 _public member_ `TSoftObjectPtr<ULiveLinkPreset> DefaultLiveLinkPreset;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLink")` — The default preset that should be applied
- L100 _public member_ `TSubclassOf<ULiveLinkVirtualSubject> DefaultVirtualSubjectClass;` — `UPROPERTY(config)` — The default preset that should be applied
- L105 _public member_ `FDirectoryPath PresetSaveDir_DEPRECATED;` — `UE_DEPRECATED(5.1, "PresetSaveDir was moved into LiveLinkUserSettings. Please use ULiveLinkUserSettings::GetPresetSaveDir().")` — `UPROPERTY(config)`
- L110 _public member_ `float ClockOffsetCorrectionStep;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "LiveLink")` — Continuous clock offset correction step
- L114 _public member_ `ELiveLinkSourceMode DefaultMessageBusSourceMode;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "LiveLink")` — The default evaluation mode a source connected via the message bus should start with.
- L118 _public member_ `double MessageBusPingRequestFrequency;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category="LiveLink", meta=(ConfigRestartRequired=true, ForceUnits=s))` — The refresh frequency of the list of message bus provider (when discovery is requested).
- L122 _public member_ `double MessageBusHeartbeatFrequency;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category="LiveLink", meta=(ConfigRestartRequired=true, ForceUnits=s))` — The refresh frequency of the heartbeat when a provider didn't send us an updated.
- L126 _public member_ `double MessageBusHeartbeatTimeout;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category="LiveLink", meta=(ConfigRestartRequired=true, ForceUnits=s))` — How long we should wait before a provider become unresponsive.
- L130 _public member_ `double MessageBusTimeBeforeRemovingInactiveSource;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "LiveLink", meta=(ForceUnits=s))` — Subjects will be removed when their source has been unresponsive for this long.
- L134 _public member_ `bool bReEnableSubjectOnRemoval = false;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "LiveLink", meta = (DisplayName = "Re-enable shadowed subjects on removal"))` — When an enabled subject is removed and another subject with the same name exists, automatically enable it.
- L138 _public member_ `bool bPreProcessRebroadcastFrames = false;` — `UPROPERTY(config)` — Whether to Preprocess frames before rebroadcasting them.
- L142 _public member_ `bool bTranslateRebroadcastFrames = false;` — `UPROPERTY(config)` — Whether to translate frames before rebroadcasting them.
- L151 _public member_ `double TimeWithoutFrameToBeConsiderAsInvalid;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLink|UI", DisplayName="Time Without Frame to be Considered as Invalid", meta=(ForceUnits=s))` — A source may still exist but does not send frames for a subject. Time before considering the subject as "invalid". The subject still exists and can still be evaluated. An invalid subject is shown as yellow in the LiveLink UI.
- L156 _public member_ `FLinearColor ValidColor;` — `UE_DEPRECATED(5.6, "Not used anymore in favor of using icons.")` — `UPROPERTY(config, EditAnywhere, Category = "LiveLink|UI")` — Color for active Subjects receiving data from their Source.
- L161 _public member_ `FLinearColor InvalidColor;` — `UE_DEPRECATED(5.6, "Not used anymore in favor of using icons.")` — `UPROPERTY(config, EditAnywhere, Category = "LiveLink|UI")` — Color for Subjects that have not received data from their Source for TimeWithoutFrameToBeConsiderAsInvalid.
- L165 _public member_ `uint8 TextSizeSource;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLink|UI|Debug")` — Font size of Source names shown in LiveLink Debug View.
- L169 _public member_ `uint8 TextSizeSubject;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLink|UI|Debug")` — Font size of Subject names shown in LiveLink Debug View.
- L175 _public member_ `bool bTransmitEvaluatedData_DEPRECATED = false;` — `UE_DEPRECATED(5.7, "bTransmitEvaluatedData has been moved to the source settings.")` — `UPROPERTY(meta = (DeprecatedProperty))` — Whether to rebroadcast evaluted data.
- L180 _public prototype_ `FLiveLinkRoleProjectSetting GetDefaultSettingForRole(TSubclassOf<ULiveLinkRole> Role) const;`
- L182 _public function_ `double GetTimeWithoutFrameToBeConsiderAsInvalid() const`
- L183 _public function_ `float GetMessageBusPingRequestFrequency() const`
- L184 _public function_ `float GetMessageBusHeartbeatFrequency() const`
- L185 _public function_ `double GetMessageBusHeartbeatTimeout() const`
- L186 _public function_ `double GetMessageBusTimeBeforeRemovingDeadSource() const`
- L189 _public function_ `static FName GetDefaultRoleSettingsPropertyName()` — Retrieve the name of the protected DefaultRoleSettings property.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkSourceCollection.h` (Public)


#### struct `FLiveLinkCollectionSourceItem`  
`struct FLiveLinkCollectionSourceItem`  
_L26-44_
- L28 _public prototype_ `FLiveLinkCollectionSourceItem() = default;`
- L29 _public prototype_ `FLiveLinkCollectionSourceItem(FLiveLinkCollectionSourceItem&&) = default;`
- L30 _public prototype_ `FLiveLinkCollectionSourceItem& operator=(FLiveLinkCollectionSourceItem&&) = default;`
- L32 _public prototype_ `FLiveLinkCollectionSourceItem(const FLiveLinkCollectionSourceItem&) = delete;`
- L33 _public prototype_ `FLiveLinkCollectionSourceItem& operator=(const FLiveLinkCollectionSourceItem&) = delete;`
- L35 _public member_ `FGuid Guid;`
- L36 _public member_ `TStrongObjectPtr<ULiveLinkSourceSettings> Setting;`
- L37 _public member_ `TSharedPtr<ILiveLinkSource> Source;`
- L38 _public member_ `TSharedPtr<FLiveLinkTimedDataInput> TimedData;`
- L39 _public member_ `bool bPendingKill = false;`
- L40 _public member_ `bool bIsVirtualSource = false;`
- L43 _public prototype_ `bool IsVirtualSource() const;`

#### struct `FLiveLinkCollectionSubjectItem`  
`struct FLiveLinkCollectionSubjectItem`  
_L46-79_
- L48 _public prototype_ `FLiveLinkCollectionSubjectItem(FLiveLinkSubjectKey InKey, TUniquePtr<FLiveLinkSubject> InLiveSubject, ULiveLinkSubjectSettings* InSettings, bool bInEnabled);`
- L49 _public prototype_ `FLiveLinkCollectionSubjectItem(FLiveLinkSubjectKey InKey, ULiveLinkVirtualSubject* InVirtualSubject, bool bInEnabled);`
- L52 _public member_ `FLiveLinkSubjectKey Key;`
- L53 _public member_ `bool bEnabled;`
- L54 _public member_ `bool bPendingKill;`
- L58 _public function_ `ILiveLinkSubject* GetSubject()` — Todo: These methods should be revisited because they may not be safe to access when LiveLinkHub is ticked outside of  the game thread. ie. Calling methods on a subject that is about to be removed will not keep the underlying livelink subject alive.
- L59 _public function_ `ULiveLinkVirtualSubject* GetVirtualSubject()`
- L60 _public function_ `ILiveLinkSubject* GetSubject() const`
- L61 _public function_ `ULiveLinkVirtualSubject* GetVirtualSubject() const`
- L62 _public function_ `UObject* GetSettings() const`
- L63 _public function_ `ULiveLinkSubjectSettings* GetLinkSettings() const`
- L64 _public function_ `FLiveLinkSubject* GetLiveSubject() const`
- L68 _private member_ `TStrongObjectPtr<ULiveLinkSubjectSettings> Setting;`
- L69 _private member_ `TUniquePtr<FLiveLinkSubject> LiveSubject;`
- L70 _private member_ `TStrongObjectPtr<ULiveLinkVirtualSubject> VirtualSubject;`
- L73 _public prototype_ `FLiveLinkCollectionSubjectItem(const FLiveLinkCollectionSubjectItem&) = delete;`
- L74 _public prototype_ `FLiveLinkCollectionSubjectItem& operator=(const FLiveLinkCollectionSubjectItem&) = delete;`
- L75 _public prototype_ `FLiveLinkCollectionSubjectItem(FLiveLinkCollectionSubjectItem&&) = default;`
- L76 _public prototype_ `FLiveLinkCollectionSubjectItem& operator=(FLiveLinkCollectionSubjectItem&&) = default;`

#### class `FLiveLinkSourceCollection`  
`class FLiveLinkSourceCollection`  
_L82-211_
- L86 _public member_ `static const FGuid DefaultVirtualSubjectGuid;` — "source guid" for virtual subjects
- L87 _public prototype_ `FLiveLinkSourceCollection();`
- L93 _public prototype_ `void AddSource(FLiveLinkCollectionSourceItem Source);`
- L94 _public prototype_ `void RemoveSource(FGuid SourceGuid);`
- L95 _public prototype_ `void RemoveAllSources();`
- L96 _public prototype_ `FLiveLinkCollectionSourceItem* FindSource(TSharedPtr<ILiveLinkSource> Source);`
- L97 _public prototype_ `const FLiveLinkCollectionSourceItem* FindSource(TSharedPtr<ILiveLinkSource> Source) const;`
- L98 _public prototype_ `FLiveLinkCollectionSourceItem* FindSource(FGuid SourceGuid);`
- L99 _public prototype_ `const FLiveLinkCollectionSourceItem* FindSource(FGuid SourceGuid) const;`
- L100 _public prototype_ `FLiveLinkCollectionSourceItem* FindVirtualSource(FName VirtualSourceName);`
- L101 _public prototype_ `const FLiveLinkCollectionSourceItem* FindVirtualSource(FName VirtualSourceName) const;`
- L103 _public prototype_ `int32 NumSources() const;` — Get the number of sources in the collection.
- L105 _public prototype_ `void AddSubject(FLiveLinkCollectionSubjectItem Subject);`
- L106 _public prototype_ `void RemoveSubject(FLiveLinkSubjectKey SubjectKey);`
- L107 _public prototype_ `FLiveLinkCollectionSubjectItem* FindSubject(FLiveLinkSubjectKey SubjectKey);`
- L108 _public prototype_ `const FLiveLinkCollectionSubjectItem* FindSubject(FLiveLinkSubjectKey SubjectKey) const;`
- L109 _public prototype_ `const FLiveLinkCollectionSubjectItem* FindSubject(FLiveLinkSubjectName SubjectName) const;`
- L110 _public prototype_ `const FLiveLinkCollectionSubjectItem* FindEnabledSubject(FLiveLinkSubjectName SubjectName) const;`
- L112 _public prototype_ `int32 NumSubjects() const;` — Get the number of subjects in the collection.
- L114 _public prototype_ `bool IsSubjectEnabled(FLiveLinkSubjectKey SubjectKey) const;`
- L115 _public prototype_ `void SetSubjectEnabled(FLiveLinkSubjectKey SubjectKey, bool bEnabled);`
- L117 _public prototype_ `void RemovePendingKill();`
- L118 _public prototype_ `bool RequestShutdown();`
- L123 _public prototype_ `void ForEachSubject(TFunctionRef<void(FLiveLinkCollectionSourceItem& , FLiveLinkCollectionSubjectItem& )> VisitorFunc);` — Thread safe way to apply a method over every subject.
- L128 _public prototype_ `void ForEachSubject(TFunctionRef<void(const FLiveLinkCollectionSourceItem&, const FLiveLinkCollectionSubjectItem&)> VisitorFunc) const;` — Thread safe way to apply a method over every subject.
- L133 _public prototype_ `void ForEachSource(TFunctionRef<void(FLiveLinkCollectionSourceItem& )> VisitorFunc);` — Thread safe way to apply a method over every source.
- L138 _public prototype_ `void ForEachSource(TFunctionRef<void(const FLiveLinkCollectionSourceItem&)> VisitorFunc) const;` — Thread safe way to apply a method over every source.
- L143 _public prototype_ `void ApplyToSubject(const FLiveLinkSubjectKey& InSubjectKey, TFunctionRef<void(FLiveLinkCollectionSubjectItem& )> VisitorFunc);` — Thread safe way to apply a method over a subject.
- L145 _public function_ `FSimpleMulticastDelegate& OnLiveLinkSourcesChanged()`
- L146 _public function_ `FSimpleMulticastDelegate& OnLiveLinkSubjectsChanged()`
- L148 _public function_ `FOnLiveLinkSourceChangedDelegate& OnLiveLinkSourceAdded()`
- L149 _public function_ `FOnLiveLinkSourceChangedDelegate& OnLiveLinkSourceRemoved()`
- L150 _public function_ `FOnLiveLinkSubjectChangedDelegate& OnLiveLinkSubjectAdded()`
- L151 _public function_ `FOnLiveLinkSubjectChangedDelegate& OnLiveLinkSubjectRemoved()`
- L152 _public function_ `FOnLiveLinkSubjectStateChanged& OnLiveLinkSubjectStateChanged()`
- L153 _public function_ `FOnLiveLinkSubjectEnabledDelegate& OnLiveLinkSubjectEnabledChanged()`
- L157 _public function_ `template <typename DelegateType, typename... ArgTypes> void BroadcastOnGameThread(DelegateType& InDelegate, ArgTypes&&... InArgs)` — Utility method used to broadcast delegates on the game thread if this function is called on a different thread.
- L175 _private prototype_ `void HandleSubjectStateChanged(ELiveLinkSubjectState NewState, FLiveLinkSubjectKey SubjectKey);` — Handles broadcasting the inner subject state change delegate to all listeners of the collection's delegate.
- L178 _private member_ `TArray<FLiveLinkCollectionSourceItem> Sources;`
- L180 _private member_ `TArray<FLiveLinkCollectionSubjectItem> Subjects;`
- L183 _private member_ `FSimpleMulticastDelegate OnLiveLinkSourcesChangedDelegate;` — Notify when the client sources list has changed
- L186 _private member_ `FSimpleMulticastDelegate OnLiveLinkSubjectsChangedDelegate;` — Notify when a client subjects list has changed
- L189 _private member_ `FOnLiveLinkSourceChangedDelegate OnLiveLinkSourceAddedDelegate;` — Notify when a client source's is added
- L192 _private member_ `FOnLiveLinkSourceChangedDelegate OnLiveLinkSourceRemovedDelegate;` — Notify when a client source's is removed
- L195 _private member_ `FOnLiveLinkSubjectChangedDelegate OnLiveLinkSubjectAddedDelegate;` — Notify when a client subject's is added
- L198 _private member_ `FOnLiveLinkSubjectChangedDelegate OnLiveLinkSubjectRemovedDelegate;` — Notify when a client subject's is removed
- L201 _private member_ `FOnLiveLinkSubjectStateChanged OnLiveLinkSubjectStateChangedDelegate;` — Notify when a client subject's state has changed. (ie. it became stale)
- L204 _private member_ `FOnLiveLinkSubjectEnabledDelegate OnLiveLinkSubjectEnabledDelegate;` — Notify when a client subject's state of enabled has changed.
- L207 _private member_ `mutable UE::FTransactionallySafeRecursiveMutex SubjectsLock;` — Lock to stop multiple threads accessing the Subjects from the collection at the same time
- L210 _private member_ `mutable UE::FTransactionallySafeRecursiveMutex SourcesLock;` — Lock to stop multiple threads accessing the Sources from the collection at the same time

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LIVELINK_API`
- L166 _function_ `` (scope `FLiveLinkSourceCollection::BroadcastOnGameThread`)

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkSubject.h` (Public)


#### struct `FLiveLinkTimeSynchronizationData`  
`struct FLiveLinkTimeSynchronizationData`  
_L24-43_
- L27 _public member_ `bool bHasEstablishedSync = false;` — Whether or not synchronization has been established.
- L30 _public member_ `int32 RolloverFrame = INDEX_NONE;` — The frame in our buffer where a rollover was detected. Only applicable for time synchronized sources.
- L33 _public member_ `int32 Offset = 0;` — Frame offset that will be used for this source.
- L36 _public member_ `TOptional<FFrameTime> RolloverModulus;` — Frame Time value modulus. When this value is not set, we assume no rollover occurs.
- L39 _public member_ `FFrameRate SyncFrameRate;` — Frame rate used as the base for synchronization.
- L42 _public member_ `FFrameTime SyncStartTime;` — Frame time that synchronization was established (relative to SynchronizationFrameRate).

#### struct `FTimedDataMonitorInfo`  
`struct FTimedDataMonitorInfo`  
_L46-51_
- desc: Struct used to cache information that needs to be accessed on the Game Thread by Timed Data Monitor.
- L48 _public member_ `FTimedDataChannelSampleTime OldestDataTime;`
- L49 _public member_ `FTimedDataChannelSampleTime NewestDataTime;`
- L50 _public member_ `TArray<FTimedDataChannelSampleTime> DataTimes;`

#### class `FLiveLinkSubject`  
`class FLiveLinkSubject : public ILiveLinkSubject, public ITimedDataInputChannel`  
_L58-331_
- inherits: `ILiveLinkSubject,ITimedDataInputChannel`
- desc: Manages subject manipulation either to add or get frame data for specific roles
- L61 _private typedef_ `using Super = ILiveLinkSubject;`
- L64 _public prototype_ `explicit FLiveLinkSubject(TSharedPtr<FLiveLinkTimedDataInput> InTimedDataGroup);`
- L65 _public prototype_ `FLiveLinkSubject(const FLiveLinkSubject&) = delete;`
- L66 _public prototype_ `FLiveLinkSubject& operator=(const FLiveLinkSubject&) = delete;`
- L67 _public prototype_ `virtual ~FLiveLinkSubject();`
- L71 _public prototype_ `virtual void Initialize(FLiveLinkSubjectKey SubjectKey, TSubclassOf<ULiveLinkRole> InRole, ILiveLinkClient* LiveLinkClient) override;`
- L72 _public prototype_ `virtual void Update() override;`
- L73 _public prototype_ `virtual void ClearFrames() override;`
- L74 _public function_ `virtual FLiveLinkSubjectKey GetSubjectKey() const override`
- L75 _public function_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const override`
- L76 _public prototype_ `virtual bool HasValidFrameSnapshot() const override;`
- L77 _public prototype_ `virtual FLiveLinkStaticDataStruct& GetStaticData(bool bGetOverrideData=true) override;`
- L78 _public prototype_ `virtual const FLiveLinkStaticDataStruct& GetStaticData() const override;`
- L79 _public prototype_ `virtual TArray<FLiveLinkTime> GetFrameTimes() const override;`
- L80 _public function_ `virtual const TArray<ULiveLinkFrameTranslator::FWorkerSharedPtr> GetFrameTranslators() const override`
- L85 _public function_ `virtual const ULiveLinkSubjectRemapper::FWorkerSharedPtr GetFrameRemapper() const override`
- L90 _public function_ `virtual bool IsRebroadcasted() const override`
- L91 _public function_ `virtual bool HasStaticDataBeenRebroadcasted() const override`
- L92 _public function_ `virtual void SetStaticDataAsRebroadcasted(const bool bInSent) override`
- L94 _public prototype_ `virtual void PreprocessFrame(const FLiveLinkStaticDataStruct& InStaticData, FLiveLinkFrameDataStruct& InOutFrameData) override;`
- L95 _public prototype_ `virtual bool IsPaused() const override;`
- L96 _public prototype_ `virtual void PauseSubject() override;`
- L97 _public prototype_ `virtual void UnpauseSubject() override;`
- L100 _protected function_ `virtual const FLiveLinkSubjectFrameData& GetFrameSnapshot() const override`
- L104 _public prototype_ `virtual bool EvaluateFrame(TSubclassOf<ULiveLinkRole> InDesiredRole, FLiveLinkSubjectFrameData& OutFrame) override;`
- L111 _public prototype_ `virtual FText GetDisplayName() const override;`
- L112 _public prototype_ `virtual ETimedDataInputState GetState() const override;`
- L113 _public prototype_ `virtual FTimedDataChannelSampleTime GetOldestDataTime() const override;`
- L114 _public prototype_ `virtual FTimedDataChannelSampleTime GetNewestDataTime() const override;`
- L115 _public prototype_ `virtual TArray<FTimedDataChannelSampleTime> GetDataTimes() const override;`
- L116 _public prototype_ `virtual int32 GetNumberOfSamples() const override;`
- L117 _public prototype_ `virtual bool IsBufferStatsEnabled() const override;`
- L118 _public prototype_ `virtual void SetBufferStatsEnabled(bool bEnable) override;`
- L119 _public prototype_ `virtual int32 GetBufferUnderflowStat() const override;`
- L120 _public prototype_ `virtual int32 GetBufferOverflowStat() const override;`
- L121 _public prototype_ `virtual int32 GetFrameDroppedStat() const override;`
- L122 _public prototype_ `virtual void GetLastEvaluationData(FTimedDataInputEvaluationData& OutEvaluationData) const override;`
- L123 _public prototype_ `virtual void ResetBufferStats() override;`
- L127 _public prototype_ `bool EvaluateFrameAtWorldTime(double InWorldTime, TSubclassOf<ULiveLinkRole> InDesiredRole, FLiveLinkSubjectFrameData& OutFrame);`
- L128 _public prototype_ `bool EvaluateFrameAtSceneTime(const FQualifiedFrameTime& InSceneTime, TSubclassOf<ULiveLinkRole> InDesiredRole, FLiveLinkSubjectFrameData& OutFrame);`
- L130 _public prototype_ `bool HasStaticData() const;`
- L133 _public prototype_ `void SetStaticData(TSubclassOf<ULiveLinkRole> InRole, FLiveLinkStaticDataStruct&& InStaticData);` — Handling setting a new static data. Create role data if not found in map.
- L136 _public prototype_ `void AddFrameData(FLiveLinkFrameDataStruct&& InFrameData);` — Add a frame of data from a FLiveLinkFrameData
- L138 _public prototype_ `void CacheSettings(ULiveLinkSourceSettings* SourceSetting, ULiveLinkSubjectSettings* SubjectSetting);`
- L140 _public prototype_ `ELiveLinkSourceMode GetMode() const;`
- L141 _public prototype_ `FLiveLinkSubjectTimeSyncData GetTimeSyncData();`
- L142 _public prototype_ `bool IsTimeSynchronized() const;`
- L145 _public function_ `double GetLastPushTime() const` — Get the timestamp of the last time a frame was received for this subject.
- L147 _public function_ `void SetLastPushTime(double InLastPushTime)` — Set the last time a frame was received.
- L150 _public prototype_ `bool ValidateFrameData(const FLiveLinkFrameDataStruct& InFrameData);` — Validates if the incoming frame data is compatible with the static data for this subject.
- L153 _public prototype_ `void ClearOverrideStaticData_AnyThread();` — Clear the override static data for this subject.
- L155 _public function_ `FLiveLinkFrameIdentifier GetLastRebroadcastedFrameId() const`
- L160 _public function_ `void SetLastRebroadcastedFrameId(FLiveLinkFrameIdentifier FrameId)`
- L166 _public function_ `FOnStateChanged& OnStateChanged()` — Get the delegate triggered when the state changes.
- L169 _private prototype_ `int32 FindNewFrame_WorldTime(const FLiveLinkWorldTime& FrameTime) const;`
- L170 _private prototype_ `int32 FindNewFrame_WorldTimeInternal(const FLiveLinkWorldTime& FrameTime) const;`
- L171 _private prototype_ `int32 FindNewFrame_SceneTime(const FQualifiedFrameTime& FrameTime, const FLiveLinkWorldTime& WorldTime) const;`
- L172 _private prototype_ `int32 FindNewFrame_Latest(const FLiveLinkWorldTime& FrameTime) const;`
- L175 _private prototype_ `void AdjustSubFrame_SceneTime(int32 FrameIndex);` — Reorder frame with the same timecode and create subframes
- L178 _private prototype_ `bool GetFrameAtWorldTime(const double InSeconds, FLiveLinkSubjectFrameData& OutFrame);` — Populate OutFrame with a frame based off of the supplied time (pre offsetted)
- L179 _private prototype_ `bool GetFrameAtWorldTime_Closest(const double InSeconds, FLiveLinkSubjectFrameData& OutFrame);`
- L180 _private prototype_ `bool GetFrameAtWorldTime_Interpolated(const double InSeconds, FLiveLinkSubjectFrameData& OutFrame);`
- L183 _private prototype_ `bool GetFrameAtSceneTime(const FQualifiedFrameTime& InSceneTime, FLiveLinkSubjectFrameData& OutFrame);` — Populate OutFrame with a frame based off of the supplied scene time (pre offsetted).
- L184 _private prototype_ `bool GetFrameAtSceneTime_Closest(const FQualifiedFrameTime& InSceneTime, FLiveLinkSubjectFrameData& OutFrame);`
- L185 _private prototype_ `bool GetFrameAtSceneTime_Interpolated(const FQualifiedFrameTime& InSceneTime, FLiveLinkSubjectFrameData& OutFrame);`
- L188 _private prototype_ `void VerifyInterpolationInfo(const FLiveLinkInterpolationInfo& InterpolationInfo);` — Verify interpolation result to update our internal statistics
- L191 _private prototype_ `bool GetLatestFrame(FLiveLinkSubjectFrameData& OutFrame);` — Populate OutFrame with the latest frame.
- L193 _private prototype_ `void ResetFrame(FLiveLinkSubjectFrameData& OutFrame) const;`
- L196 _private prototype_ `void IncreaseFrameDroppedStat();` — Update our internal statistics
- L197 _private prototype_ `void IncreaseBufferUnderFlowStat();`
- L198 _private prototype_ `void IncreaseBufferOverFlowStat();`
- L199 _private prototype_ `void UpdateEvaluationData(const FTimedDataInputEvaluationData& EvaluationData);`
- L202 _private prototype_ `void RemoveFrames(int32 Count);` — Remove frames from our buffer - based on receiving order
- L205 _private prototype_ `void UpdateState();` — Update the cached state for this subject.
- L208 _private prototype_ `void UpdateCachedOldestDataTime();`
- L209 _private prototype_ `void UpdateCachedNewestDataTime();`
- L210 _private prototype_ `void UdpateCachedDataTimes();`
- L214 _protected member_ `TSubclassOf<ULiveLinkRole> Role;` — The role the subject was build with
- L216 _protected member_ `TArray<ULiveLinkFramePreProcessor::FWorkerSharedPtr> FramePreProcessors;`
- L218 _protected member_ `ULiveLinkFrameInterpolationProcessor::FWorkerSharedPtr FrameInterpolationProcessor = nullptr;`
- L221 _protected member_ `TArray<ULiveLinkFrameTranslator::FWorkerSharedPtr> FrameTranslators;` — List of available translator the subject can use.
- L224 _protected member_ `ULiveLinkSubjectRemapper::FWorkerSharedPtr SubjectRemapper;` — Subject remapper used to modify static and frame data for a subject.
- L246 _private member_ `FLiveLinkStaticDataStruct StaticData;` — Static data of the subject
- L249 _private member_ `TOptional<FLiveLinkStaticDataStruct> OverrideStaticData;` — Override static data, set by the remapper.
- L252 _private member_ `TArray<FLiveLinkFrameDataStruct> FrameData;` — Frames added to the subject
- L255 _private member_ `TQueue<FLiveLinkFrameIdentifier> ReceivedOrderedFrames;` — Contains identifier of each frame in the order they were received
- L258 _private member_ `FLiveLinkFrameIdentifier NextIdentifier = 0;` — Next identifier to assign to next received frame
- L261 _private member_ `FLiveLinkSubjectFrameData FrameSnapshot;` — Current frame snapshot of the evaluation
- L264 _private member_ `FLiveLinkSubjectKey SubjectKey;` — Name of the subject
- L267 _private member_ `TWeakPtr<FLiveLinkTimedDataInput> TimedDataGroup;` — Timed data input group for the subject
- L270 _private member_ `FLiveLinkCachedSettings CachedSettings;` — Connection settings specified by user
- L273 _private member_ `TOptional<ELiveLinkSourceMode> ModeOverride;` — Override mode, determined by frame data
- L276 _private member_ `double LastPushTime = 0.0;` — Last time a frame was pushed
- L279 _private member_ `bool bIsStatLoggingEnabled = true;` — Logging stats is enabled by default. If monitor opens at a later stage,previous stats will be able to be seen
- L282 _private member_ `FSubjectEvaluationStatistics EvaluationStatistics;` — Some stats compiled by the subject.
- L285 _private member_ `FFrameRate LastTimecodeFrameRate;` — Last Timecode FrameRate received
- L288 _private member_ `bool bRebroadcastSubject = false;` — If enabled, rebroadcast this subject
- L291 _private member_ `bool bRebroadcastStaticDataSent = false;` — If true, static data has been sent for this rebroadcast
- L294 _private member_ `bool bNeedsStaticRemap = false;` — If true, override static data may remap when caching settings.
- L297 _private member_ `std::atomic<bool> bPaused = false;` — Flag set to indicate that a subject is currently paused, so it should keep its last snapshot.
- L300 _private member_ `std::atomic<bool> bClearOverrideStaticData = false;` — Flag set to clear the override static data for a subject.
- L303 _private member_ `ELiveLinkSubjectState State;` — Current state of this subject.
- L306 _private member_ `FOnStateChanged OnStateChangedDelegate;` — Delegate called when the state of this subject has changed.
- L309 _private member_ `FLiveLinkFrameIdentifier LastRebroadcastFrameId = 0;` — Last frame ID that was rebroadcasted. Used to avoid LiveLinkClient from rebroadcasting the same frame twice when transmitting evaluated data.
- L315 _private member_ `FTimedDataMonitorInfo CachedTimeDataMonitorInfo;` — This struct is updated on the LiveLink thread (either GameThread or dedicated thread in Live Link Hub). Then it's accessed by TimedDataMonitor on the GameThread.
- L318 _private member_ `mutable FCriticalSection CachedTimedDataMonitorInfoCS;` — Critical section used to protect access to the cached timed data monitor information.
- L324 _private member_ `mutable FCriticalSection StatisticCriticalSection;` — Evaluation can be done on any thread so we need to protect statistic logging Some stats requires more than atomic sized vars so a critical section is used to protect when necessary
- L327 _private member_ `mutable FCriticalSection SettingsCriticalSection;` — Used to protect access to translators, preprocessors and interpolation processors since they can be set and accessed in different threads.
- L330 _private member_ `mutable FRWLock FrameSnapshotRWLock;` — Read-write lock to protect FrameSnapshot access. Allows multiple concurrent readers (EvaluateFrame_AnyThread) but exclusive writer access (Update).

#### struct `FLiveLinkSubject::FLiveLinkCachedSettings`  
`struct FLiveLinkCachedSettings`  
_L227-231_
- L229 _public member_ `ELiveLinkSourceMode SourceMode = ELiveLinkSourceMode::EngineTime;`
- L230 _public member_ `FLiveLinkSourceBufferManagementSettings BufferSettings;`

#### struct `FLiveLinkSubject::FSubjectEvaluationStatistics`  
`struct FSubjectEvaluationStatistics`  
_L233-243_
- L235 _public member_ `TAtomic<int32> BufferUnderflow;`
- L236 _public member_ `TAtomic<int32> BufferOverflow;`
- L237 _public member_ `TAtomic<int32> FrameDrop;`
- L238 _public member_ `FTimedDataInputEvaluationData LastEvaluationData;`
- L240 _public prototype_ `FSubjectEvaluationStatistics();`
- L241 _public prototype_ `FSubjectEvaluationStatistics(const FSubjectEvaluationStatistics&) = delete;`
- L242 _public prototype_ `FSubjectEvaluationStatistics& operator=(const FSubjectEvaluationStatistics&) = delete;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LIVELINK_API`
- L53 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStateChanged, ELiveLinkSubjectState );`
- L53 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStateChanged, ELiveLinkSubjectState );`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkTimeSynchronizationSource.h` (Public)


#### class `ULiveLinkTimeSynchronizationSource`  
`class ULiveLinkTimeSynchronizationSource : public UTimeSynchronizationSource`  
_L14-57_
- reflection: `UCLASS(MinimalAPI, EditInlineNew)`
- inherits: `UTimeSynchronizationSource`
- L20 _public member_ `FLiveLinkSubjectName SubjectName;` — `UPROPERTY(EditAnywhere, Category="LiveLink")`
- L23 _private member_ `FLiveLinkClient* LiveLinkClient;`
- L31 _private member_ `mutable ESyncState State = ESyncState::NotSynced;`
- L32 _private member_ `mutable FLiveLinkSubjectTimeSyncData CachedData;`
- L33 _private member_ `mutable int64 LastUpdateFrame;`
- L34 _private member_ `FLiveLinkSubjectKey SubjectKey;`
- L38 _public prototype_ `ULiveLinkTimeSynchronizationSource();`
- L41 _public prototype_ `virtual FFrameTime GetNewestSampleTime() const override;`
- L42 _public prototype_ `virtual FFrameTime GetOldestSampleTime() const override;`
- L43 _public prototype_ `virtual FFrameRate GetFrameRate() const override;`
- L44 _public prototype_ `virtual bool IsReady() const override;`
- L45 _public prototype_ `virtual bool Open(const FTimeSynchronizationOpenData& OpenData) override;`
- L46 _public prototype_ `virtual void Start(const FTimeSynchronizationStartData& StartData) override;`
- L47 _public prototype_ `virtual void Close() override;`
- L48 _public prototype_ `virtual FString GetDisplayName() const override;`
- L53 _private prototype_ `bool IsCurrentStateValid() const;`
- L54 _private prototype_ `void OnModularFeatureRegistered(const FName& FeatureName, class IModularFeature* Feature);`
- L55 _private prototype_ `void OnModularFeatureUnregistered(const FName& FeatureName, class IModularFeature* Feature);`
- L56 _private prototype_ `void UpdateCachedState() const;`

#### enum `ULiveLinkTimeSynchronizationSource::ESyncState`  
`enum class ESyncState`  
_L25-29_
- L27 _public enumerator_ `NotSynced`
- L28 _public enumerator_ `Opened`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkTimecodeProvider.h` (Public)


#### enum `ELiveLinkTimecodeProviderEvaluationType`  
`enum class ELiveLinkTimecodeProviderEvaluationType`  
_L19-29_
- reflection: `UENUM()`
- L22 _public enumerator_ `Lerp` — Interpolate between, or extrapolate using the 2 frames that are the closest to the current world time.
- L25 _public enumerator_ `Nearest` — Use the frame that is closest to the current world time.
- L28 _public enumerator_ `Latest` — Use the newest frame that was received. When LiveLink Custom Time Step is active, uses the timecode captured at the genlock trigger point.

#### class `ULiveLinkTimecodeProvider`  
`class ULiveLinkTimecodeProvider : public UTimecodeProvider`  
_L35-140_
- reflection: `UCLASS(MinimalAPI, config=Engine, Blueprintable, editinlinenew)`
- inherits: `UTimecodeProvider`
- desc: Fetch the latest frames from the LiveLink subject and create a Timecode from it.
- L40 _public prototype_ `ULiveLinkTimecodeProvider();`
- L43 _public prototype_ `virtual FQualifiedFrameTime GetQualifiedFrameTime() const override;`
- L45 _public function_ `virtual ETimecodeProviderSynchronizationState GetSynchronizationState() const override`
- L50 _public prototype_ `virtual bool Initialize(class UEngine* InEngine) override;`
- L51 _public prototype_ `virtual void Shutdown(class UEngine* InEngine) override;`
- L55 _public prototype_ `virtual void BeginDestroy() override;`
- L57 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L66 _public function_ `void SetTargetSubjectKey(const FLiveLinkSubjectKey& InKey)` — Allows users to override the target timecode provider subject key. Live Link Hub will send subject name to the host but the host has to "lookup" and match it with the available subject keys on the local machine.
- L72 _public prototype_ `void ClearFrameHistory();` — Clear the frame history. Useful when using Latest/Nearest evaluation type and wanting to accept timecoded frames older than what's currently in the buffer.
- L75 _private prototype_ `FQualifiedFrameTime ConvertTo(FQualifiedFrameTime Value) const;`
- L87 _private prototype_ `FQualifiedFrameTime LerpBetweenFrames(double Seconds, int32 IndexA, int32 IndexB) const;` — Infers the frame time for the current world time by either interpolating between or extrapolating a frame time value from two subject frames provided via live link. This method uses the FMath::Lerp function but will intentionally provide an Alpha value greater than 1.0 when extrapolation is required. @param Seconds The current world time. @param IndexA The first subject frame index. @param IndexB The second subject frame index. @return The inferred frame time.
- L89 _private prototype_ `void InitClient();`
- L90 _private prototype_ `void UninitClient();`
- L91 _private prototype_ `void RegisterSubject();`
- L92 _private prototype_ `void UnregisterSubject();`
- L93 _private prototype_ `void OnLiveLinkClientRegistered(const FName& Type, class IModularFeature* ModularFeature);`
- L94 _private prototype_ `void OnLiveLinkClientUnregistered(const FName& Type, class IModularFeature* ModularFeature);`
- L95 _private prototype_ `void OnLiveLinkSubjectAdded(FLiveLinkSubjectKey SubjectKey);`
- L96 _private prototype_ `void OnLiveLinkSubjectRemoved(FLiveLinkSubjectKey SubjectKey);`
- L97 _private prototype_ `void OnLiveLinkFrameDataReceived_AnyThread(const FLiveLinkFrameDataStruct& FrameData);`
- L102 _private member_ `FLiveLinkSubjectKey SubjectKey;` — `UPROPERTY(EditAnywhere, Category = Timecode)` — The specific subject that we listen to.
- L106 _private member_ `ELiveLinkTimecodeProviderEvaluationType Evaluation;` — `UPROPERTY(EditAnywhere, Category = Timecode)` — How to evaluate the timecode.
- L109 _private member_ `bool bOverrideFrameRate;` — `UPROPERTY(EditAnywhere, Category = Timecode, meta=(InlineEditConditionToggle))`
- L116 _private member_ `FFrameRate OverrideFrameRate;` — `UPROPERTY(EditAnywhere, Category = Timecode, meta=(EditCondition="bOverrideFrameRate"))` — Override the frame rate at which this timecode provider will create its timecode value. By default, we use the subject frame rate.
- L120 _private member_ `int32 BufferSize;` — `UPROPERTY(AdvancedDisplay, EditAnywhere, Category = Timecode, meta=(ClampMin = "2", UIMin = "2", ClampMax = "10", UIMax = "10"))` — The number of frame to keep in memory. The provider will not be synchronized until the buffer is full at least once.
- L123 _private member_ `TAtomic<ETimecodeProviderSynchronizationState> State;`
- L124 _private member_ `ILiveLinkClient* LiveLinkClient;`
- L125 _private member_ `FLiveLinkSubjectKey RegisteredSubjectKey;`
- L126 _private member_ `TArray<FLiveLinkTime> SubjectFrameTimes;`
- L127 _private member_ `mutable FCriticalSection SubjectFrameLock;` — Only lock SubjectFrameTimes
- L128 _private member_ `FDelegateHandle RegisterForFrameDataReceivedHandle;`
- L131 _private member_ `std::atomic<bool> bIsSequencerSourceAnyThread = false;` — Cached flag indicating whether the monitored subject is from a sequencer source
- L134 _private member_ `FLiveLinkSubjectKey OriginalExternalSubjectKey;` — Stores the original external subject key before sequencer takes over, so we can restore it when sequencer stops
- L137 _private member_ `FDelegateHandle ExternalSubjectFrameDataReceivedHandle;` — When sequencer takes over, we also register to the disabled external subject to read its timecode

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkTimedDataInput.h` (Public)


#### class `FLiveLinkTimedDataInput`  
`class FLiveLinkTimedDataInput : public ITimedDataInput`  
_L15-72_
- inherits: `ITimedDataInput`
- L18 _public prototype_ `FLiveLinkTimedDataInput(FLiveLinkClient* Client, FGuid Source);`
- L19 _public prototype_ `FLiveLinkTimedDataInput(const FLiveLinkTimedDataInput&) = delete;`
- L20 _public prototype_ `FLiveLinkTimedDataInput& operator=(const FLiveLinkTimedDataInput&) = delete;`
- L21 _public prototype_ `virtual ~FLiveLinkTimedDataInput();`
- L24 _public prototype_ `virtual FText GetDisplayName() const override;`
- L25 _public prototype_ `virtual TArray<ITimedDataInputChannel*> GetChannels() const override;`
- L26 _public prototype_ `virtual ETimedDataInputEvaluationType GetEvaluationType() const override;`
- L27 _public prototype_ `virtual void SetEvaluationType(ETimedDataInputEvaluationType Evaluation) override;`
- L28 _public prototype_ `virtual double GetEvaluationOffsetInSeconds() const override;`
- L29 _public prototype_ `virtual void SetEvaluationOffsetInSeconds(double Offset) override;`
- L30 _public prototype_ `virtual FFrameRate GetFrameRate() const override;`
- L31 _public prototype_ `virtual int32 GetDataBufferSize() const override;`
- L32 _public prototype_ `virtual void SetDataBufferSize(int32 BufferSize) override;`
- L33 _public function_ `virtual bool IsDataBufferSizeControlledByInput() const override`
- L34 _public function_ `virtual void AddChannel(ITimedDataInputChannel* Channel) override`
- L35 _public function_ `virtual void RemoveChannel(ITimedDataInputChannel* Channel) override`
- L36 _public prototype_ `virtual UObject* GetSettingsObject() const override;`
- L38 _public prototype_ `virtual const FSlateBrush* GetDisplayIcon() const override;`
- L44 _public prototype_ `void ProcessNewFrameTimingInfo(FLiveLinkBaseFrameData& NewFrameData);` — Tracks clock difference between each frame received and arrival time in engine referential.
- L48 _private prototype_ `void UpdateSmoothEngineTimeOffset(const FLiveLinkBaseFrameData& NewFrameData);` — Computes the smooth offset based on the average frame time intervals of the source time
- L51 _private member_ `FLiveLinkClient* LiveLinkClient;`
- L52 _private member_ `TArray<ITimedDataInputChannel*> Channels;`
- L53 _private member_ `FGuid Source;`
- L56 _private member_ `FClockOffsetEstimatorRamp EngineClockOffset;` — Continuous clock offset estimator for engine time and timecode
- L57 _private member_ `FClockOffsetEstimatorRamp TimecodeClockOffset;`
- L60 _private member_ `double LastWorldSourceTime = 0.0;` — We will receive each frame for each subject of this source. Stamp last source time/timecode to only update our offset estimation once per "source frame"
- L61 _private member_ `double LastSceneTime = 0.0;`
- L63 _private member_ `static constexpr double FrameIntervalThreshold = 0.005;`
- L64 _private member_ `static constexpr double VeryLargeFrameIntervalThreshold = 0.5;`
- L65 _private member_ `static constexpr int32 FrameIntervalSnapCount = 5;`
- L66 _private member_ `static constexpr int32 FrameTimeBufferSize = 200;`
- L68 _private member_ `TArray<double> FrameTimes;`
- L70 _private member_ `int32 FrameIntervalChangeCount = 0;`
- L71 _private member_ `int32 NumFramesToConsiderForAverage = TNumericLimits<int32>::Max();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkVirtualSubjectBoneAttachment.h` (Public)


#### struct `FLiveLinkVirtualSubjectBoneAttachment`  
`struct FLiveLinkVirtualSubjectBoneAttachment`  
_L17-51_
- reflection: `USTRUCT()`
- desc: A bone attachment used by the virtual subjects to attach 2 subjects together by specifying a child and parent bone.
- L23 _public prototype_ `bool IsValid(const TArray<FLiveLinkSubjectName>& ActiveSubjects) const;` — Returns whether the attachment can be used.
- L27 _public member_ `FLiveLinkSubjectName ParentSubject;` — `UPROPERTY(EditAnywhere, DisplayName = "Parent", Category = "Live Link")` — Subject that the child subject will be attached to.
- L31 _public member_ `FName ParentBone;` — `UPROPERTY(EditAnywhere, Category = "Live Link")` — Name of the bone in the parent subject that will serve as a parent to the child bone of the child subject.
- L35 _public member_ `FLiveLinkSubjectName ChildSubject;` — `UPROPERTY(EditAnywhere, DisplayName = "Child", Category = "Live Link")` — Subject that will be attached to the parent.
- L39 _public member_ `FName ChildBone;` — `UPROPERTY(EditAnywhere, Category = "Live Link")` — Bone that will be attached to the parent bone.
- L43 _public member_ `FVector LocationOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Live Link", meta=(LinearDeltaSensitivity = "1", Delta = "1.0"))` — Location of the component relative to its parent
- L47 _public member_ `FRotator RotationOffset = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, Category = "Live Link", meta=(LinearDeltaSensitivity = "1", Delta = "1.0"))` — Rotation of the component relative to its parent
- L50 _public member_ `mutable FText LastError;` — If not empty, hold the last error text set by the IsValid method. Used to bubble up errors to the UI.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/PreProcessor/LiveLinkAxisSwitchPreProcessor.h` (Public)


#### enum `ELiveLinkAxis`  
`enum class ELiveLinkAxis : uint8`  
_L13-21_
- reflection: `UENUM()`
- desc: DO NOT modify the order or values of these enums - the code relies on the order and values and will fail if it's changed
- L15 _public enumerator_ `X = 0 UMETA(DisplayName = "X-Axis")`
- L16 _public enumerator_ `Y = 1 UMETA(DisplayName = "Y-Axis")`
- L17 _public enumerator_ `Z = 2 UMETA(DisplayName = "Z-Axis")`
- L18 _public enumerator_ `XNeg = 3 UMETA(DisplayName = "-X-Axis")`
- L19 _public enumerator_ `YNeg = 4 UMETA(DisplayName = "-Y-Axis")`
- L20 _public enumerator_ `ZNeg = 5 UMETA(DisplayName = "-Z-Axis")`

#### class `ULiveLinkTransformAxisSwitchPreProcessor`  
`class ULiveLinkTransformAxisSwitchPreProcessor : public ULiveLinkFramePreProcessor`  
_L29-98_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Transform Axis Switch"))`
- inherits: `ULiveLinkFramePreProcessor`
- desc: Allows to switch any axis of an incoming transform with another axis. @note For example the Z-Axis of an incoming transform can be set to the (optionally negated) Y-Axis of the transform in UE. @note This implies that translation, rotation and scale will be affected by switching an axis.
- L54 _protected member_ `ELiveLinkAxis OrientationAxisX_DEPRECATED = ELiveLinkAxis::X;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use FrontAxis, RightAxis, UpAxis instead"))`
- L56 _protected member_ `ELiveLinkAxis OrientationAxisY_DEPRECATED = ELiveLinkAxis::Y;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use FrontAxis, RightAxis, UpAxis instead"))`
- L58 _protected member_ `ELiveLinkAxis OrientationAxisZ_DEPRECATED = ELiveLinkAxis::Z;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use FrontAxis, RightAxis, UpAxis instead"))`
- L60 _protected member_ `ELiveLinkAxis TranslationAxisX_DEPRECATED = ELiveLinkAxis::X;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use FrontAxis, RightAxis, UpAxis instead"))`
- L62 _protected member_ `ELiveLinkAxis TranslationAxisY_DEPRECATED = ELiveLinkAxis::Y;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use FrontAxis, RightAxis, UpAxis instead"))`
- L64 _protected member_ `ELiveLinkAxis TranslationAxisZ_DEPRECATED = ELiveLinkAxis::Z;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use FrontAxis, RightAxis, UpAxis instead"))`
- L68 _protected member_ `ELiveLinkAxis FrontAxis = ELiveLinkAxis::X;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")`
- L70 _protected member_ `ELiveLinkAxis RightAxis = ELiveLinkAxis::Y;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")`
- L72 _protected member_ `ELiveLinkAxis UpAxis = ELiveLinkAxis::Z;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")`
- L75 _protected member_ `bool bUseOffsetPosition = false;` — `UPROPERTY(EditAnywhere, Category = "Enables", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L77 _protected member_ `bool bUseOffsetOrientation = false;` — `UPROPERTY(EditAnywhere, Category = "Enables", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L80 _protected member_ `FVector OffsetPosition = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "LiveLink", meta = (EditCondition = "bUseOffsetPosition"))`
- L82 _protected member_ `FRotator OffsetOrientation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, Category = "LiveLink", meta = (EditCondition = "bUseOffsetOrientation"))`
- L85 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const override;`
- L86 _public prototype_ `virtual ULiveLinkFramePreProcessor::FWorkerSharedPtr FetchWorker() override;`
- L90 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L92 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L97 _protected member_ `TSharedPtr<FLiveLinkTransformAxisSwitchPreProcessorWorker, ESPMode::ThreadSafe> Instance;`

#### class `ULiveLinkTransformAxisSwitchPreProcessor::FLiveLinkTransformAxisSwitchPreProcessorWorker`  
`class FLiveLinkTransformAxisSwitchPreProcessorWorker : public ILiveLinkFramePreProcessorWorker`  
_L34-49_
- inherits: `ILiveLinkFramePreProcessorWorker`
- L37 _public member_ `ELiveLinkAxis FrontAxis = ELiveLinkAxis::X;`
- L38 _public member_ `ELiveLinkAxis RightAxis = ELiveLinkAxis::Y;`
- L39 _public member_ `ELiveLinkAxis UpAxis = ELiveLinkAxis::Z;`
- L41 _public member_ `bool bUseOffsetPosition = false;`
- L42 _public member_ `bool bUseOffsetOrientation = false;`
- L44 _public member_ `FVector OffsetPosition = FVector::ZeroVector;`
- L45 _public member_ `FRotator OffsetOrientation = FRotator::ZeroRotator;`
- L47 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const override;`
- L48 _public prototype_ `virtual bool PreProcessFrame(FLiveLinkFrameDataStruct& InOutFrame) const override;`

#### class `ULiveLinkAnimationAxisSwitchPreProcessor`  
`class ULiveLinkAnimationAxisSwitchPreProcessor : public ULiveLinkTransformAxisSwitchPreProcessor`  
_L106-121_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Animation Axis Switch"))`
- inherits: `ULiveLinkTransformAxisSwitchPreProcessor`
- desc: Allows to switch any axis of an incoming animation with another axis. @note For example the Z-Axis of an incoming transform can be set to the (optionally negated) Y-Axis of the transform in UE. @note This implies that translation, rotation and scale will be affected by switching an axis.
- L119 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const override;`
- L120 _public prototype_ `virtual ULiveLinkFramePreProcessor::FWorkerSharedPtr FetchWorker() override;`

#### class `ULiveLinkAnimationAxisSwitchPreProcessor::FLiveLinkAnimationAxisSwitchPreProcessorWorker`  
`class FLiveLinkAnimationAxisSwitchPreProcessorWorker : public ULiveLinkTransformAxisSwitchPreProcessor::FLiveLinkTransformAxisSwitchPreProcessorWorker`  
_L111-116_
- inherits: `ULiveLinkTransformAxisSwitchPreProcessor::FLiveLinkTransformAxisSwitchPreProcessorWorker`
- L114 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const override;`
- L115 _public prototype_ `virtual bool PreProcessFrame(FLiveLinkFrameDataStruct& InOutFrame) const override;`

#### class `ULiveLinkLocatorAxisSwitchPreProcessor`  
`class ULiveLinkLocatorAxisSwitchPreProcessor : public ULiveLinkTransformAxisSwitchPreProcessor`  
_L129-144_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Locator Axis Switch"))`
- inherits: `ULiveLinkTransformAxisSwitchPreProcessor`
- desc: Allows to switch any axis of an incoming locator subject with another axis. @note For example the Z-Axis of an incoming transform can be set to the (optionally negated) Y-Axis of the transform in UE. @note This implies that translation, rotation and scale will be affected by switching an axis.
- L142 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const override;`
- L143 _public prototype_ `virtual ULiveLinkFramePreProcessor::FWorkerSharedPtr FetchWorker() override;`

#### class `ULiveLinkLocatorAxisSwitchPreProcessor::FLiveLinkLocatorAxisSwitchPreProcessorWorker`  
`class FLiveLinkLocatorAxisSwitchPreProcessorWorker : public ULiveLinkTransformAxisSwitchPreProcessor::FLiveLinkTransformAxisSwitchPreProcessorWorker`  
_L134-139_
- inherits: `ULiveLinkTransformAxisSwitchPreProcessor::FLiveLinkTransformAxisSwitchPreProcessorWorker`
- L137 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const override;`
- L138 _public prototype_ `virtual bool PreProcessFrame(FLiveLinkFrameDataStruct& InOutFrame) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/PreProcessor/LiveLinkDeadbandPreProcessor.h` (Public)


#### class `ULiveLinkTransformDeadbandPreProcessor`  
`class ULiveLinkTransformDeadbandPreProcessor : public ULiveLinkFramePreProcessor`  
_L16-76_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Transform Deadband"))`
- inherits: `ULiveLinkFramePreProcessor`
- desc: Implements a deadband filter that gets applied to the transform, with independent thresholds for rotation and translation.
- L49 _protected member_ `bool bEnableDeadband = true;` — `UPROPERTY(EditAnywhere, Category = "Deadband")` — If false, transform is left untouched
- L53 _protected member_ `float TranslationDeadband = 0;` — `UPROPERTY(EditAnywhere, Category = "Deadband")` — Translation is updated only if the change is larger than this threshold
- L57 _protected member_ `float RotationDeadbandInDegrees = 0;` — `UPROPERTY(EditAnywhere, Category = "Deadband")` — Rotation is updated only if the change is larger than this threshold
- L61 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const override;`
- L62 _public prototype_ `virtual ULiveLinkFramePreProcessor::FWorkerSharedPtr FetchWorker() override;`
- L68 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L75 _protected member_ `TSharedPtr<FLiveLinkTransformDeadbandPreProcessorWorker, ESPMode::ThreadSafe> Instance;` — Instance of the worker object

#### class `ULiveLinkTransformDeadbandPreProcessor::FLiveLinkTransformDeadbandPreProcessorWorker`  
`class FLiveLinkTransformDeadbandPreProcessorWorker : public ILiveLinkFramePreProcessorWorker`  
_L21-43_
- inherits: `ILiveLinkFramePreProcessorWorker`
- L26 _public member_ `bool bEnableDeadband = true;` — If false, transform is left untouched
- L29 _public member_ `double TranslationDeadband = 0;` — Translation is updated only if the change is larger than this threshold
- L32 _public member_ `double RotationDeadbandInDegrees = 0;` — Rotation is updated only if the change is larger than this threshold
- L35 _public member_ `mutable FTransform StableTransform;` — Keeps track of the last accepted location and translation
- L40 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const override;`
- L41 _public prototype_ `virtual bool PreProcessFrame(FLiveLinkFrameDataStruct& InOutFrame) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/Remapper/LiveLinkSkeletonRemapper.h` (Public)


#### class `FLiveLinkSkeletonRemapperWorker`  
`class FLiveLinkSkeletonRemapperWorker : public ILiveLinkSubjectRemapperWorker`  
_L17-63_
- inherits: `ILiveLinkSubjectRemapperWorker`
- L20 _public function_ `virtual void RemapStaticData(FLiveLinkStaticDataStruct& InOutStaticData)`
- L28 _public function_ `virtual void RemapFrameData(const FLiveLinkStaticDataStruct& InOutStaticData, FLiveLinkFrameDataStruct& InOutFrameData)`
- L36 _public function_ `virtual void RemapSkeletonStaticData(FLiveLinkSkeletonStaticData& InOutSkeletonData)`
- L48 _public function_ `virtual void RemapSkeletonFrameData(const FLiveLinkSkeletonStaticData& InOutSkeletonData, FLiveLinkAnimationFrameData& InOutFrameData)`
- L52 _public function_ `FName GetRemappedBoneName(FName BoneName) const`
- L62 _public member_ `TMap<FName, FName> BoneNameMap;` — Map used to provide new names for the bones in the static data.

#### class `ULiveLinkSkeletonRemapper`  
`class ULiveLinkSkeletonRemapper : public ULiveLinkSubjectRemapper`  
_L66-124_
- reflection: `UCLASS(MinimalAPI, EditInlineNew)`
- inherits: `ULiveLinkSubjectRemapper`
- L71 _public function_ `virtual void Initialize(const FLiveLinkSubjectKey& SubjectKey) override`
- L88 _public function_ `virtual TSubclassOf<ULiveLinkRole> GetSupportedRole() const override`
- L94 _public function_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override`
- L100 _public function_ `virtual bool IsValidRemapper() const`
- L105 _public function_ `virtual FWorkerSharedPtr GetWorker() const override`
- L110 _public function_ `virtual FWorkerSharedPtr CreateWorker() override`
- L119 _public member_ `TSoftObjectPtr<USkeletalMesh> ReferenceSkeleton;` — `UPROPERTY(EditAnywhere, Category="Remapper", meta=(DisplayThumbnail="false"))`
- L123 _private member_ `TSharedPtr<FLiveLinkSkeletonRemapperWorker> Instance;` — Instance of the remapper.

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/SLiveLinkMessageBusSourceFactory.h` (Public)


#### class `SLiveLinkMessageBusSourceFactory`  
`class SLiveLinkMessageBusSourceFactory : public SCompoundWidget`  
_L24-84_
- inherits: `SCompoundWidget`
- L26 _private function_ `SLATE_BEGIN_ARGS(SLiveLinkMessageBusSourceFactory)`
- L27 _private prototype_ `SLATE_EVENT(FOnLiveLinkMessageBusSourceSelected, OnSourceSelected) SLATE_ARGUMENT(UClass*, FactoryClass) SLATE_END_ARGS() ~SLiveLinkMessageBusSourceFactory();`
- L33 _private prototype_ `void Construct(const FArguments& Args);`
- L35 _private function_ `FProviderPollResultPtr GetSelectedSource() const`
- L37 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);`
- L55 _private prototype_ `TSharedRef<ITableRow> MakeSourceListViewWidget(TSharedPtr<FLiveLinkSource> Source, const TSharedRef<STableViewBase>& OwnerTable) const;` — Create a widget entry in the source list based on a live link source.
- L58 _private prototype_ `void OnSourceListSelectionChanged(TSharedPtr<FLiveLinkSource> Source, ESelectInfo::Type SelectionType);` — Handles selection changing in the list.
- L62 _private member_ `TSharedPtr<SListView<TSharedPtr<FLiveLinkSource>>> ListView;` — The widgets displayed in the list.
- L65 _private member_ `TArray<FProviderPollResultPtr> PollData;` — Latest sources pulled from the discovery manager.
- L68 _private member_ `TArray<TSharedPtr<FLiveLinkSource>> Sources;` — The sources displayed by the list.
- L71 _private member_ `FProviderPollResultPtr SelectedResult;` — The source that was selected.
- L74 _private member_ `FOnLiveLinkMessageBusSourceSelected OnSourceSelected;` — The last source that was selected.
- L77 _private member_ `double LastUIUpdateSeconds = 0;` — The last time at which the UI was refreshed.
- L80 _private member_ `double SecondsBeforeSourcesDisappear = 2.0;` — Time before a source should disappear from the UI after its last pong.
- L83 _private member_ `UClass* FactoryClass = nullptr;` — Class of the factory that created this widget.

#### struct `SLiveLinkMessageBusSourceFactory::FLiveLinkSource`  
`struct FLiveLinkSource`  
_L41-51_
- desc: Represents a source with its latest time since it was polled successfully.
- L43 _public member_ `FProviderPollResultPtr PollResult;`
- L44 _public member_ `double LastTimeSincePong = 0.0;`
- L46 _public function_ `FLiveLinkSource(FProviderPollResultPtr InPollResult) : PollResult(MoveTemp(InPollResult)) , LastTimeSincePong(FApp::GetCurrentTime())`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINK_API`
- L11 _namespace_ `namespace ESelectInfo`
- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLiveLinkMessageBusSourceSelected, FProviderPollResultPtr);`
- L22 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLiveLinkMessageBusSourceSelected, FProviderPollResultPtr);`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/Translator/LiveLinkAnimationRoleToTransform.h` (Public)


#### class `ULiveLinkAnimationRoleToTransform`  
`class ULiveLinkAnimationRoleToTransform : public ULiveLinkFrameTranslator`  
_L15-47_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Animation To Transform"))`
- inherits: `ULiveLinkFrameTranslator`
- desc: Basic object to translate data from one role to another
- L31 _protected member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, Category="LiveLink")`
- L34 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetFromRole() const override;`
- L35 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetToRole() const override;`
- L36 _public prototype_ `virtual ULiveLinkFrameTranslator::FWorkerSharedPtr FetchWorker() override;`
- L41 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L46 _private member_ `TSharedPtr<FLiveLinkAnimationRoleToTransformWorker, ESPMode::ThreadSafe> Instance;`

#### class `ULiveLinkAnimationRoleToTransform::FLiveLinkAnimationRoleToTransformWorker`  
`class FLiveLinkAnimationRoleToTransformWorker : public ILiveLinkFrameTranslatorWorker`  
_L20-27_
- inherits: `ILiveLinkFrameTranslatorWorker`
- L23 _public member_ `FName BoneName;`
- L24 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetFromRole() const override;`
- L25 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetToRole() const override;`
- L26 _public prototype_ `virtual bool Translate(const FLiveLinkStaticDataStruct& InStaticData, const FLiveLinkFrameDataStruct& InFrameData, FLiveLinkSubjectFrameData& OutTranslatedFrame) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/Translator/LiveLinkTransformRoleToAnimation.h` (Public)


#### class `ULiveLinkTransformRoleToAnimation`  
`class ULiveLinkTransformRoleToAnimation : public ULiveLinkFrameTranslator`  
_L15-48_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Transform to Animation"))`
- inherits: `ULiveLinkFrameTranslator`
- desc: LiveLink Translator used to convert Transform frame data to Animation (Skeletal) frame data.
- L32 _public member_ `FName OutputBoneName = "Ro` — `UPROPERTY(EditAnywhere, Category="LiveLink")` — Name of the resulting bone. Defaults to "Root"
- L35 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetFromRole() const override;`
- L36 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetToRole() const override;`
- L37 _public prototype_ `virtual ULiveLinkFrameTranslator::FWorkerSharedPtr FetchWorker() override;`
- L42 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L47 _private member_ `TSharedPtr<FLiveLinkTransformRoleToAnimationWorker> Instance;`

#### class `ULiveLinkTransformRoleToAnimation::FLiveLinkTransformRoleToAnimationWorker`  
`class FLiveLinkTransformRoleToAnimationWorker : public ILiveLinkFrameTranslatorWorker`  
_L20-27_
- inherits: `ILiveLinkFrameTranslatorWorker`
- L23 _public member_ `FName OutputBoneName;`
- L24 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetFromRole() const override;`
- L25 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetToRole() const override;`
- L26 _public prototype_ `virtual bool Translate(const FLiveLinkStaticDataStruct& InStaticData, const FLiveLinkFrameDataStruct& InFrameData, FLiveLinkSubjectFrameData& OutTranslatedFrame) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/VirtualSubjects/LiveLinkBlueprintVirtualSubject.h` (Public)


#### class `ULiveLinkBlueprintVirtualSubject`  
`class ULiveLinkBlueprintVirtualSubject : public ULiveLinkVirtualSubject`  
_L13-50_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract)`
- inherits: `ULiveLinkVirtualSubject`
- desc: Base class for creating virtual subjects in Blueprints
- L18 _public prototype_ `ULiveLinkBlueprintVirtualSubject() = default;`
- L20 _public prototype_ `virtual void Initialize(FLiveLinkSubjectKey InSubjectKey, TSubclassOf<ULiveLinkRole> InRole, ILiveLinkClient* InLiveLinkClient) override;`
- L21 _public prototype_ `virtual void Update() override;`
- L24 _public prototype_ `void OnInitialize();` — `UFUNCTION(BlueprintImplementableEvent, Category="LiveLink")`
- L27 _public prototype_ `void OnUpdate();` — `UFUNCTION(BlueprintImplementableEvent, Category="LiveLink")`
- L29 _public prototype_ `void UpdateVirtualSubjectStaticData(const FLiveLinkBaseStaticData* InStaticData);`
- L30 _public prototype_ `void UpdateVirtualSubjectFrameData(const FLiveLinkBaseFrameData* InFrameData, bool bInShouldStampCurrentTime);`
- L33 _public prototype_ `bool UpdateVirtualSubjectStaticData_Internal(const FLiveLinkBaseStaticData& InStruct);` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = "LiveLink", meta = (CustomStructureParam = "InStruct", BlueprintInternalUseOnly = "true", AllowAbstract = "false"))`
- L36 _public prototype_ `bool UpdateVirtualSubjectFrameData_Internal(const FLiveLinkBaseFrameData& InStruct, bool bInShouldStampCurrentTime);` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = "LiveLink", meta = (CustomStructureParam = "InStruct", BlueprintInternalUseOnly = "true", AllowAbstract = "false"))`
- L42 _private prototype_ `UScriptStruct* GetRoleStaticStruct();`
- L43 _private prototype_ `UScriptStruct* GetRoleFrameStruct();`
- L45 _private member_ `FLiveLinkStaticDataStruct CachedStaticData;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINK_API`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/Visualizers/LiveLinkDataPreview.h` (Public)


#### class `ALiveLinkDataPreview`  
`class ALiveLinkDataPreview : public AActor`  
_L18-91_
- reflection: `UCLASS(Blueprintable, BlueprintType, DisplayName = "Live Link Data Preview Actor", Category = "LiveLink", MinimalApi)`
- inherits: `AActor`
- L24 _public prototype_ `ALiveLinkDataPreview();` — Sets default values for this actor's properties
- L31 _public prototype_ `void SetEnableLiveLinkData(bool bNewEvaluate);` — `UFUNCTION(CallInEditor, BlueprintCallable, DisplayName = "Evaluate Live Link", Category = LiveLink)` — Stop Start animation evaluation. @param bNewEvaluate Enable Live Link Evaluation
- L36 _public member_ `TArray<FLiveLinkSubjectName> Subjects;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LiveLink, meta = (ShowOnlyInnerProperties = "true"))` — The list of Live Link subjects this actor will draw.
- L38 _public member_ `TSoftObjectPtr<UStaticMesh> BoneMesh;`
- L39 _public member_ `TSoftObjectPtr<UStaticMesh> JointMesh;`
- L40 _public member_ `TSoftObjectPtr<UStaticMesh> AxisMesh;`
- L41 _public member_ `TSoftObjectPtr<UStaticMesh> TransformMesh;`
- L42 _public member_ `TSoftObjectPtr<UStaticMesh> CameraMesh;`
- L43 _public member_ `TSoftObjectPtr<UStaticMesh> LocatorMesh;`
- L44 _public member_ `TSoftObjectPtr<UTexture2D> SpriteTexture;`
- L47 _public member_ `bool bDrawLabels;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LiveLink)`
- L51 _public member_ `bool bEvaluateLiveLink;` — `UPROPERTY(EditAnywhere, Category = LiveLink)` — Enable Live Link evaluation
- L53 _public member_ `TArray<ULiveLinkDataPreviewComponent> Visualizers;`
- L57 _public member_ `TObjectPtr<UBillboardComponent> BillboardComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)` — The billboard component showing the actor's root position.
- L64 _protected prototype_ `void InitializeSubjects();` — `UFUNCTION(BlueprintCallable, DisplayName = "Initialize All Subjects", Category = LiveLink)` — Initialize all the subjects.
- L70 _protected prototype_ `void SetMaterialInstance(ULiveLinkDataPreviewComponent* InDataPreviewComponent);` — Set the material instance on a Live Link data preview component. @param InDataPreviewComponent Preview component instanced static mesh.
- L73 _protected prototype_ `virtual void Tick(float DeltaTime) override;` — Called every frame
- L76 _protected prototype_ `virtual void OnConstruction(const FTransform& Transform) override;` — Actor Interface
- L81 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L83 _protected function_ `virtual bool ShouldTickIfViewportsOnly() const override`
- L90 _private member_ `TArray<FLiveLinkSubjectKey> CachedSubjects;`

### `Plugins/Animation/LiveLink/Source/LiveLink/Public/Visualizers/LiveLinkDataPreviewComponent.h` (Public)


#### enum `ELiveLinkVisualBoneType`  
`enum class ELiveLinkVisualBoneType : uint8`  
_L19-23_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `Joint = 0 UMETA(DisplayName = "Joint", Toolip = "For use drawing the location of a joint")`
- L22 _public enumerator_ `Bone = 1 UMETA(DisplayName = "Bone", Toolip = "For use drawing a bone pointing at the next child in a chain")`

#### class `ULiveLinkDataPreviewComponent`  
`class ULiveLinkDataPreviewComponent : public UInstancedStaticMeshComponent`  
_L29-102_
- reflection: `UCLASS(ClassGroup=(LiveLink), Transient, DisplayName = "Live Link Data Preview", MinimalApi)`
- inherits: `UInstancedStaticMeshComponent`
- desc: An instance static mesh component for drawing LiveLink subject data in-level. Support drawing Transforms, Locators, Skeletons and Cameras
- L35 _public prototype_ `ULiveLinkDataPreviewComponent(const FObjectInitializer& ObjectInitializer);` — Sets default values for this component's properties
- L38 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;` — Called every frame
- L42 _public member_ `FLiveLinkSubjectName SubjectName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LiveLink)` — The Live Link subject this component will preview.
- L46 _public member_ `bool bEvaluateLiveLink;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=LiveLink)` — Bool to control animation evaluation.
- L50 _public member_ `bool bDrawLabels;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="LiveLink|Visualization")` — Bool to control visibility of labels.
- L54 _public member_ `ELiveLinkVisualBoneType BoneVisualType = ELiveLinkVisualBoneType::Bone;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LiveLink|Visualization")` — Type of bone visualization - joint or bone.
- L61 _public function_ `void SetEvaluateLiveLinkData(bool bNewEvaluateLiveLink)` — `UFUNCTION(BlueprintCallable, Category="LiveLink|Visualization")` — Stop/Start animation updates. @param bNewEvaluateLiveLink New evaluation state.
- L69 _public function_ `void SetDrawLabels(bool bNewDrawLabel)` — `UFUNCTION(BlueprintCallable, Category="LiveLink|Visualization")` — TODO: not yet implemented, waiting on slate immediate mode
- L71 _public member_ `bool bIsDirty;`
- L74 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L78 _protected prototype_ `virtual void OnRegister() override;`
- L79 _protected prototype_ `virtual void OnUnregister() override;`
- L81 _protected prototype_ `void CreateInstances();`
- L83 _protected prototype_ `TArray<FTransform> GetJointTransforms() const;`
- L84 _protected prototype_ `TArray<FTransform> GetBoneTransforms() const;`
- L85 _protected prototype_ `TArray<FVector> GetLocatorPositions() const;`
- L86 _protected prototype_ `FTransform GetSingleTransform() const;`
- L89 _private member_ `TArray<FName> MarkerLabels;`
- L91 _private prototype_ `void CacheSkeletalAnimationData(const FLiveLinkSkeletonStaticData* InStaticData, const FLiveLinkAnimationFrameData* InFrameData);`
- L93 _private member_ `FLiveLinkSkeletonStaticData CachedSkeletonData;`
- L94 _private member_ `FLiveLinkAnimationFrameData CachedAnimationData;`
- L96 _private prototype_ `void GetTransformRootSpace(const int32 InTransformIndex, FTransform& OutTransform) const;`
- L98 _private member_ `mutable TArray<TPair<bool, FTransform>> CachedRootSpaceTransforms;`
- L99 _private member_ `mutable TArray<TPair<bool, TArray<int32>>> CachedChildTransformIndices;`
- L100 _private prototype_ `static bool IsValidTransformIndex(int32 InTransformIndex, FLiveLinkAnimationFrameData AnimData);`
