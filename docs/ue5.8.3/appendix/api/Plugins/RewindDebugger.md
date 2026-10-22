# Plugins / RewindDebugger

- module root: `Plugins/Animation/GameplayInsights/Source/RewindDebugger`
- headers: 22; symbols: 592
- symbol kinds: class=23, delegate=12, enum=5, enumerator=13, function=56, macro=2, member=179, namespace=17, prototype=273, struct=7, typedef=5
- PrivateDependencyModuleNames: ActorPickerMode, Core, CoreUObject, DeveloperSettings, Engine, GameplayInsights, InputCore, LevelSequence, RewindDebuggerInterface, RewindDebuggerRuntime, Slate, SlateCore, Sockets, StatusBar, ToolMenus, ToolWidgets, TraceAnalysis, TraceBasedDebuggers, TraceBasedDebuggersAnalysis, TraceInsights, TraceLog, TraceServices, UnrealEd

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/AnimInstanceHelpers.h` (Private)


#### class `FAnimInstanceDoubleClickHandler`  
`class FAnimInstanceDoubleClickHandler : public IRewindDebuggerDoubleClickHandler`  
_L6-10_
- inherits: `IRewindDebuggerDoubleClickHandler`
- L8 _private prototype_ `virtual FName GetTargetTypeName() const override;`
- L9 _private prototype_ `bool HandleDoubleClick(IRewindDebugger* RewindDebugger) override;`

#### class `FAnimInstanceMenu`  
`class FAnimInstanceMenu`  
_L12-16_
- L15 _public prototype_ `static void Register();`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/BindableProperty.h` (Private)


#### enum `EBindingType`  
`enum EBindingType`  
_L35-40_
- L37 _public enumerator_ `BindingType_In` — default - for value to be copied in to widget on change
- L38 _public enumerator_ `BindingType_Out` — value copied out of widget on change
- L39 _public enumerator_ `BindingType_TwoWay` — value copied both ways on change

#### struct `TBindablePropertyInitializer`  
`template <typename T, EBindingType BindingType = BindingType_In> struct TBindablePropertyInitializer`  
_L46-74_
- L48 _public function_ `TBindablePropertyInitializer()`
- L54 _public function_ `TBindablePropertyInitializer(TBindableProperty<T, BindingType>* InSource)`
- L60 _public function_ `TBindablePropertyInitializer(TBindableProperty<T, BindingType>* InSource, const T& InitialValue)`
- L66 _public function_ `TBindablePropertyInitializer(const T& InValue)`
- L72 _public member_ `TBindableProperty<T, BindingType>* Source;`
- L73 _public member_ `T Value;`

#### class `TBindableProperty`  
`template <typename T, EBindingType BindingType = BindingType_In> class TBindableProperty`  
_L77-200_
- L80 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnPropertyChanged, T NewValue);`
- L84 _public prototype_ `TBindableProperty(const TBindableProperty<T,BindingType>&) =delete;` — delete copy/move constructors and equals operator because we are storing raw pointers to other properties, so they can't move around in memory todo: handle move constructor correctly so that Bindable properties can be stored in arrays
- L85 _public prototype_ `TBindableProperty(TBindableProperty<T,BindingType>&&) =delete;`
- L86 _public prototype_ `TBindableProperty& operator=(const TBindableProperty<T,BindingType>&) =delete;`
- L88 _public function_ `TBindableProperty() : InternalValue()`
- L93 _public function_ `~TBindableProperty()`
- L103 _public function_ `bool IsBound()`
- L108 _public function_ `void Set(const T& NewValue)`
- L116 _public function_ `const T& Get() const`
- L121 _public function_ `void ClearBinding()`
- L130 _public function_ `void Bind(TBindableProperty<T, BindingType>* Source)`
- L150 _public function_ `void Initialize(const TBindablePropertyInitializer<T, BindingType> &Initializer)` — either set an initial value, or bind to another property (for Out properties, maybe need to support both?)
- L163 _public member_ `FOnPropertyChanged OnPropertyChanged;`
- L166 _private member_ `T InternalValue;`
- L168 _private member_ `TArray<TBindableProperty<T, BindingType>*> BoundTo;` — properties I will write to on write if BindingType is TwoWay or In
- L169 _private member_ `TBindableProperty<T, BindingType>* BoundFrom = nullptr;` — a Property that will write to me if BindingType is From, and I write to if BindingType is TwoWay or Out
- L171 _private function_ `void AddBinding(TBindableProperty<T, BindingType>* Target)`
- L177 _private function_ `void RemoveBinding(TBindableProperty<T, BindingType>* Target)`
- L182 _private function_ `void SetInternal(const T& NewValue)`

#### Free symbols / members of external scopes

- L80 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPropertyChanged, T NewValue);`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/BlueprintDoubleClickHandler.h` (Private)


#### class `FBlueprintDoubleClickHandler`  
`class FBlueprintDoubleClickHandler : public IRewindDebuggerDoubleClickHandler`  
_L6-10_
- inherits: `IRewindDebuggerDoubleClickHandler`
- L8 _private prototype_ `virtual FName GetTargetTypeName() const override;`
- L9 _private prototype_ `virtual bool HandleDoubleClick(IRewindDebugger* RewindDebugger) override;`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/PropertyTraceMenu.h` (Private)


#### class `FPropertyTraceMenu`  
`class FPropertyTraceMenu`  
_L6-10_
- L9 _public prototype_ `static void Register();`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/RewindDebugger.h` (Private)


#### class `FRewindDebugger`  
`class FRewindDebugger : public IRewindDebugger`  
_L45-436_
- inherits: `IRewindDebugger`
- desc: Singleton class that handles the logic for the Rewind Debugger: - Playback/Scrubbing state - Start/Stop recording - Keeping track of the current Debug Target object, and outputting a list of its sub objects/elements for the UI
- L48 _public prototype_ `FRewindDebugger();`
- L49 _public prototype_ `virtual ~FRewindDebugger();`
- L52 _public function_ `virtual double CurrentTraceTime() const override`
- L57 _public function_ `virtual double GetScrubTime() const override`
- L62 _public function_ `virtual void SetScrubTime(double Time) override`
- L71 _public function_ `virtual void CenterViewOnTime(double Time) override`
- L76 _public function_ `virtual const TRange<double>& GetCurrentTraceRange() const override`
- L81 _public function_ `virtual const TRange<double>& GetCurrentViewRange() const override`
- L86 _public prototype_ `virtual TSharedPtr<UE::TraceBasedDebuggers::FSessionInfo> GetSelectedDebugSessionInfo() const override;`
- L87 _public prototype_ `virtual const TraceServices::IAnalysisSession* GetAnalysisSession() const override;`
- L88 _public prototype_ `virtual TSharedPtr<const TraceServices::IAnalysisSession> GetAnalysisSessionAsShared() const override;`
- L89 _public prototype_ `virtual uint64 GetRootObjectId() const override;`
- L90 _public prototype_ `virtual bool GetRootObjectPosition(FVector& OutPosition) const override;`
- L91 _public prototype_ `virtual void SetRootObjectPosition(const TOptional<FVector>& InPosition) override;`
- L92 _public prototype_ `virtual UWorld* GetWorldToVisualize() const override;`
- L93 _public prototype_ `virtual bool IsRecording() const override;`
- L94 _public function_ `virtual bool IsPIESimulating() const override`
- L98 _public function_ `bool IsPIEStarted() const`
- L103 _public function_ `virtual double GetRecordingDuration() const override`
- L108 _public prototype_ `virtual TSharedPtr<FDebugObjectInfo> GetSelectedObject() const override;`
- L109 _public prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> GetSelectedTrack() const override;`
- L110 _public prototype_ `virtual void SelectTrack(RewindDebugger::FObjectId ObjectId) override;`
- L111 _public prototype_ `virtual void SetObjectToDebug(RewindDebugger::FObjectId ObjectId) override;`
- L112 _public prototype_ `virtual TArray<TSharedPtr<FDebugObjectInfo>>& GetDebuggedObjects() override;`
- L113 _public prototype_ `virtual bool IsObjectCurrentlyDebugged(uint64 ObjectId) const override;`
- L114 _public function_ `virtual bool ShouldDisplayWorld(uint64 WorldId) override`
- L120 _public prototype_ `bool IsAnalyzingLocalSession() const;` — @return Whether the debugger is currently analyzing a trace session from the current process (e.g., PIE)
- L123 _public prototype_ `bool IsAnalyzingRemoteSession() const;` — @return Whether the debugger is currently analyzing a remote trace session (e.g., external process like standalone game, client, server)
- L126 _public prototype_ `bool IsAnalyzingTraceFile() const;` — @return Whether the debugger is currently analyzing a trace file
- L128 _public prototype_ `void GetTargetObjectIds(TArray<RewindDebugger::FObjectId>& OutTargetObjectIds) const;`
- L130 _public function_ `TArray<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>& GetTracks()`
- L136 _public prototype_ `static void Initialize();` — create singleton instance
- L139 _public prototype_ `static void Shutdown();` — destroy singleton instance
- L142 _public function_ `static FRewindDebugger* Instance()` — get singleton instance
- L147 _public prototype_ `virtual bool CanStartRecording() const override;`
- L150 _public prototype_ `virtual void StartRecording() const override;` — Starts a new recording for the local session
- L152 _public prototype_ `void StartRecordingLocalSession() const;`
- L153 _public prototype_ `bool CanStartRecordingLocalSession() const;`
- L154 _public prototype_ `bool IsRecordingLocalSession() const;`
- L156 _public prototype_ `void OnClearRecording();`
- L158 _public prototype_ `bool CanOpenTrace() const;`
- L159 _public prototype_ `void OpenTrace(const FString& FilePath);`
- L160 _public prototype_ `void OpenTrace();`
- L163 _public prototype_ `bool CanClearAnalysis() const;` — @return Whether there is an active analysis session to close and/or tracks data to clear
- L166 _public prototype_ `void ClearAnalysis();` — Closes the currently selected analysis session and clears debugger and tracks data
- L169 _public prototype_ `void ClearTrackData();` — Clears all debugger and track data associated to the current, or last, analysis session
- L171 _public prototype_ `void ToggleAutoScroll();`
- L172 _public prototype_ `bool CanEnableAutoScroll() const;`
- L173 _public prototype_ `bool IsAutoScrollEnabled() const;`
- L175 _public prototype_ `bool ShouldAutoRecordOnPIE() const;`
- L176 _public prototype_ `void SetShouldAutoRecordOnPIE(bool InValue);`
- L178 _public prototype_ `bool ShouldAutoEject() const;`
- L179 _public prototype_ `void SetShouldAutoEject(bool InValue);`
- L181 _public prototype_ `void StopRecordingLocalSession() const;`
- L182 _public function_ `bool CanStopRecordingLocalSession() const`
- L189 _public prototype_ `bool CanPause() const;`
- L190 _public prototype_ `void Pause();`
- L192 _public prototype_ `bool CanPlay() const;`
- L193 _public prototype_ `void Play();`
- L194 _public prototype_ `bool IsPlaying() const;`
- L196 _public prototype_ `bool CanPlayReverse() const;`
- L197 _public prototype_ `void PlayReverse();`
- L199 _public prototype_ `void ScrubToStart();`
- L200 _public prototype_ `void ScrubToEnd();`
- L201 _public prototype_ `void Step(int32 InNumberOfFrames);`
- L202 _public prototype_ `void StepForward();`
- L203 _public prototype_ `void StepBackward();`
- L205 _public prototype_ `bool CanScrub() const;`
- L206 _public prototype_ `void ScrubToTime(double ScrubTime, bool bIsScrubbing);`
- L209 _public prototype_ `void Tick(float DeltaTime);` — Tick function: While recording, update recording duration.  While paused, and we have recorded data, update skinned mesh poses for the current frame, and handle playback.
- L212 _public prototype_ `void RefreshDebugTracks();` — update the list of tracks for the currently selected debug target
- L214 _public prototype_ `void SetCurrentViewRange(const TRange<double>& Range);`
- L216 _public prototype_ `DECLARE_DELEGATE(FOnTrackListChanged) void SetTrackListChangedDelegate(const FOnTrackListChanged& InTrackListChangedDelegate);`
- L219 _public prototype_ `void TrackDoubleClicked(TSharedPtr<RewindDebugger::FRewindDebuggerTrack> InSelectedTrack);`
- L220 _public prototype_ `void TrackSelectionChanged(TSharedPtr<RewindDebugger::FRewindDebuggerTrack> InSelectedTrack);`
- L221 _public prototype_ `void ClearTrackSelection();`
- L223 _public prototype_ `TSharedPtr<SWidget> BuildTrackContextMenu() const;`
- L225 _public prototype_ `void UpdateDetailsPanel(TSharedRef<SDockTab> DetailsTab);`
- L226 _public prototype_ `static void RegisterTrackContextMenu();`
- L227 _public prototype_ `static void MakeOtherWorldsMenu(class UToolMenu* Menu);`
- L228 _public prototype_ `void SetDisplayWorld(uint64 WorldId);`
- L229 _public prototype_ `static void MakeWorldsMenu(class UToolMenu* Menu);`
- L230 _public prototype_ `static void RegisterPreviewMenu();`
- L231 _public prototype_ `static void RegisterToolBar();`
- L233 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnTrackCursor, bool) void SetTrackCursorDelegate(const FOnTrackCursor& InTrackCursorDelegate);`
- L236 _public function_ `DECLARE_DELEGATE_OneParam(FOnCenterViewOnTime, double) void SetCenterViewOnTimeDelegate(const FOnCenterViewOnTime& InCenterViewOnTimeDelegate)`
- L242 _public member_ `TSharedPtr<SBox> DetailsPanelWidget;`
- L243 _public member_ `TSharedPtr<SWidget> EmptyDetails;`
- L245 _public function_ `TBindableProperty<double>* GetTraceTimeProperty()`
- L250 _public function_ `TBindableProperty<double>* GetRecordingDurationProperty()`
- L255 _public function_ `TBindableProperty<FString, BindingType_Out>* GetRootObjectNameProperty()`
- L261 _public function_ `TBindableProperty<FString, BindingType_Out>* GetDebugTargetActorProperty()` — `UE_DEPRECATED(5.7, "Use GetRootObjectNameProperty instead")`
- L266 _public prototype_ `virtual void OpenDetailsPanel() override;`
- L267 _public function_ `void SetIsDetailsPanelOpen(bool bIsOpen)`
- L272 _public prototype_ `virtual const FObjectInfo* FindTypedOuterInfo(TNotNull<const UStruct*> InType, TNotNull<const IGameplayProvider*> InGameplayProvider, uint64 InObjectId) const override;`
- L274 _public function_ `TArrayView<RewindDebugger::FRewindDebuggerTrackType> GetTrackTypes()`
- L281 _public prototype_ `bool ConnectToLiveSession(uint32 SessionID, FStringView InSessionAddress);`
- L282 _public prototype_ `bool ConnectToLiveSession_Direct(const FGuid& InRemoteSessionID);`
- L283 _public prototype_ `bool ConnectToLiveSession_Relay(const FGuid& InRemoteSessionID);`
- L290 _public prototype_ `void ClearAnalysisSessionLinkedToRemoteSessionID(const FGuid& InRemoteSessionID);` — Finds the trace session analysis linked to the provided remote session ID, then calls ClearAnalysisSession. @see ClearAnalysisSession
- L292 _public function_ `const UE::TraceBasedDebuggers::FTraceSessionDescriptor& GetCurrentSessionDescriptor() const`
- L299 _private prototype_ `void SetSelectedAnalysisSession(const UE::TraceBasedDebuggers::FTraceSessionDescriptor& InSessionDescriptor);` — Sets the analysis session as the one used by the debugger
- L306 _private prototype_ `void OpenAnalysisSession(const UE::TraceBasedDebuggers::FTraceSessionDescriptor& InSessionDescriptor);` — Adds the provided session descriptor to the list of active analysis sessions, sets the selected analysis session that the debugger will represent and notifies extensions. @see SetSelectedAnalysisSession
- L316 _private prototype_ `void StopAnalysisSession(const UE::TraceBasedDebuggers::FTraceSessionDescriptor& InSessionDescriptor);` — Stops the trace analysis session associated to the remote session specified in the provided session descriptor and notifies the extensions. @note Unlike ClearAnalysisSession this method will keep the session available by not removing it from the Trace Sessions Manager. The current session selection is not affected. @see ClearAnalysisSession
- L327 _private prototype_ `void ClearAnalysisSession(const UE::TraceBasedDebuggers::FTraceSessionDescriptor& InSessionDescriptor);` — Closes the trace analysis session (i.e., stop and remove from the Trace Sessions Manager) associated to the remote session specified in the provided session descriptor, notifies the extensions and removes the session from the active sessions. Clears the current selected session, if applicable. @note Consider using StopAnalysisSession if the session information still need to be accessed after stopping the analysis. @see StopAnalysisSession @see SetSelectedAnalysisSession
- L329 _private prototype_ `void HandleRecordingStarted(const TSharedPtr<UE::TraceBasedDebuggers::FSessionInfo>& InSessionInfo);`
- L330 _private prototype_ `void HandleRecordingStopped(const TSharedPtr<UE::TraceBasedDebuggers::FSessionInfo>& InSessionInfo);`
- L331 _private prototype_ `void HandleSessionSelected(const TSharedPtr<UE::TraceBasedDebuggers::FSessionInfo>& InSessionInfo);`
- L336 _private prototype_ `void ClearActiveAnalysisSession();`
- L339 _private prototype_ `void StopLocalRecording() const;`
- L342 _private prototype_ `static void RefreshDebuggedObjects(TArray<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>& InTracks, TArray<TSharedPtr<FDebugObjectInfo>>& OutObjects);`
- L344 _private prototype_ `void OnTrackListChanged();`
- L346 _private prototype_ `void OnPIEStarted(bool bSimulating);`
- L347 _private prototype_ `void OnPIEPaused(bool bSimulating);`
- L348 _private prototype_ `void OnPIEResumed(bool bSimulating);`
- L349 _private prototype_ `void OnPIEStopped(bool bSimulating);`
- L350 _private prototype_ `void OnPIESingleStepped(bool bSimulating);`
- L351 _private prototype_ `void OnSIESwitch(bool bSimulating);`
- L353 _private prototype_ `bool CanUsePlaybackControls() const;`
- L355 _private member_ `FDelegateHandle PreBeginPIEHandle;`
- L356 _private member_ `FDelegateHandle PausePIEHandle;`
- L357 _private member_ `FDelegateHandle ResumePIEHandle;`
- L358 _private member_ `FDelegateHandle SingleStepPIEHandle;`
- L359 _private member_ `FDelegateHandle ShutdownPIEHandle;`
- L360 _private member_ `FDelegateHandle SIESwitchHandle;`
- L362 _private member_ `FDelegateHandle ClearRecordingHandle;`
- L370 _private prototype_ `void SetCurrentScrubTime(double Time, EAutoScrollChange AutoScrollChange);`
- L372 _private member_ `TBindableProperty<double> TraceTime;`
- L373 _private member_ `TBindableProperty<double> RecordingDuration;`
- L374 _private member_ `TBindableProperty<FString, BindingType_Out> RootObjectName;`
- L383 _private member_ `EControlState ControlState = EControlState::Pause;`
- L385 _private member_ `FOnTrackListChanged TrackListChangedDelegate;`
- L386 _private member_ `FOnTrackCursor TrackCursorDelegate;`
- L387 _private member_ `FOnCenterViewOnTime CenterViewOnTimeDelegate;`
- L389 _private member_ `bool bPIEStarted = false;`
- L390 _private member_ `bool bPIESimulating = false;`
- L393 _private member_ `bool bAutoScrollToLastItem = false;` — Instructs the debugger to always scrub to the last received event
- L395 _private member_ `double PreviousTraceTime = -1;`
- L396 _private member_ `TRange<double> CurrentViewRange{ 0, 10 };`
- L397 _private member_ `TRange<double> CurrentTraceRange{ 0, 0 };`
- L398 _private member_ `uint16 RecordingIndex = 0;`
- L400 _private member_ `FScrubTimeInformation ScrubTimeInformation;`
- L401 _private member_ `FScrubTimeInformation LowerBoundViewTimeInformation;`
- L402 _private member_ `FScrubTimeInformation UpperBoundViewTimeInformation;`
- L404 _private prototype_ `static void GetScrubTimeInformation(double InDebugTime, FScrubTimeInformation& InOutTimeInformation, uint16 InRecordingIndex, const TraceServices::IAnalysisSession* AnalysisSession);`
- L408 _private member_ `TArray<UE::TraceBasedDebuggers::FTraceSessionDescriptor> ActiveAnalysisDescriptors;` — List of session descriptors associated to active trace analysis sessions
- L415 _private member_ `UE::TraceBasedDebuggers::FTraceSessionDescriptor SelectedDescriptor;` — Trace analysis descriptor associated to the selected remote session An invalid descriptor indicates that no active recording/analysis is active for the currently selected session.
- L417 _private member_ `TArray<TSharedPtr<FDebugObjectInfo>> DebuggedObjects;`
- L418 _private member_ `mutable TSharedPtr<FDebugObjectInfo> SelectedObject;`
- L420 _private member_ `TArray<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>> DebugTracks;`
- L421 _private member_ `TSharedPtr<RewindDebugger::FRewindDebuggerTrack> SelectedTrack;`
- L422 _private member_ `TSharedPtr<UE::RewindDebugger::FDebuggerRecordingControls> RecordingControls;`
- L424 _private member_ `TArray<RewindDebugger::FObjectId> CandidateIds;`
- L426 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L428 _private member_ `TOptional<FVector> RootObjectPosition;`
- L430 _private member_ `TArray<RewindDebugger::FRewindDebuggerTrackType> TrackTypes;`
- L432 _private member_ `bool bIsDetailsPanelOpen = true;`
- L434 _private member_ `uint64 DisplayWorldId = 0;`
- L435 _private member_ `bool bDisplayWorldIdValid = false;`

#### enum `FRewindDebugger::EAutoScrollChange`  
`enum class EAutoScrollChange : int8`  
_L364-368_
- L366 _public enumerator_ `PreserveCurrentState`
- L367 _public enumerator_ `Disable`

#### enum `FRewindDebugger::EControlState`  
`enum class EControlState : int8`  
_L376-381_
- L378 _public enumerator_ `Play`
- L379 _public enumerator_ `PlayReverse`
- L380 _public enumerator_ `Pause`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace TraceServices`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace RewindDebugger` (scope `UE`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L216 _delegate_ `DECLARE_DELEGATE(FOnTrackListChanged) void SetTrackListChangedDelegate(const FOnTrackListChanged& InTrackListChangedDelegate);`
- L233 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTrackCursor, bool) void SetTrackCursorDelegate(const FOnTrackCursor& InTrackCursorDelegate);`
- L236 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCenterViewOnTime, double) void SetCenterViewOnTimeDelegate(const FOnCenterViewOnTime& InCenterViewOnTimeDelegate) { CenterViewOnTimeDelegate = InCenterViewOnTimeDelegate; } TSharedPtr<SBox> DetailsPanelWidget;`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/RewindDebuggerAnimation.h` (Private)


#### class `FRewindDebuggerAnimation`  
`class FRewindDebuggerAnimation : public IRewindDebuggerExtension`  
_L22-87_
- inherits: `IRewindDebuggerExtension`
- L26 _public prototype_ `FRewindDebuggerAnimation();`
- L27 _public prototype_ `virtual ~FRewindDebuggerAnimation() = default;`
- L28 _public prototype_ `void Initialize();`
- L29 _public prototype_ `void Shutdown();`
- L31 _public prototype_ `virtual void Update(float DeltaTime, IRewindDebugger* RewindDebugger) override;`
- L32 _public prototype_ `virtual void Clear(IRewindDebugger* RewindDebugger) override;`
- L33 _public function_ `virtual FString GetName()`
- L35 _public prototype_ `void OnPIEResumed(bool bSimulating);`
- L36 _public prototype_ `void OnPIEStopped(bool bSimulating);`
- L37 _public prototype_ `void OnPIESingleStepped(bool bSimulating);`
- L39 _public prototype_ `UAnimInstance* GetDebugAnimInstance(uint64 ObjectId);`
- L41 _public function_ `static FRewindDebuggerAnimation* GetInstance()`
- L43 _private prototype_ `void ClearSpawnedComponents();`
- L44 _private prototype_ `void ApplyPoseToMesh(const class IAnimationProvider* AnimationProvider, const IGameplayProvider* GameplayProvider, const TraceServices::FFrame& Frame, const IAnimationProvider::SkeletalMeshPoseTimeline& TimelineData, USkeletalMeshComponent* MeshComponent, uint64 ObjectId, bool bQueueForReset, bool bApplyMesh);`
- L73 _private prototype_ `FSpawnedMeshComponentInfo* SpawnMesh(uint64 ObjectId, const IGameplayProvider* GameplayProvider);`
- L74 _private prototype_ `UAnimInstance* SpawnAnimInstance(uint64 ObjectId, const IGameplayProvider* GameplayProvider);`
- L76 _private member_ `TMap<uint64, FSpawnedMeshComponentInfo> SpawnedMeshComponents;`
- L77 _private member_ `TMap<uint64, FSpawnedAnimInstanceInfo> SpawnedAnimInstances;`
- L79 _private member_ `TMap<uint64, FMeshComponentResetData> MeshComponentsToReset;`
- L80 _private member_ `double LastScrubTime = -1;`
- L82 _private member_ `RewindDebugger::FObjectId TargetActorMeshId;`
- L83 _private member_ `RewindDebugger::FObjectId TargetActorIdForMesh;`
- L84 _private member_ `TOptional<FVector> TargetActorPosition;`
- L86 _private member_ `static FRewindDebuggerAnimation* Instance;`

#### struct `FRewindDebuggerAnimation::FMeshComponentResetData`  
`struct FMeshComponentResetData`  
_L47-53_
- L49 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> Component;`
- L50 _public member_ `FTransform RelativeTransform;`
- L51 _public member_ `int ForcedLod = -1;`
- L52 _public member_ `bool bIsVisible = true;`

#### struct `FRewindDebuggerAnimation::FSpawnedMeshComponentInfo`  
`struct FSpawnedMeshComponentInfo`  
_L55-63_
- L58 _public member_ `uint64 id;` — mesh component object id
- L60 _public member_ `TWeakObjectPtr<AActor> Actor;` — actor to hold the mesh component
- L62 _public member_ `TObjectPtr<USkeletalMeshComponent> Component;` — mesh

#### struct `FRewindDebuggerAnimation::FSpawnedAnimInstanceInfo`  
`struct FSpawnedAnimInstanceInfo`  
_L65-71_
- L68 _public member_ `uint64 id;` — AnimInstance id
- L70 _public member_ `TWeakObjectPtr<UAnimInstance> AnimInstance;` — Data used for anim BP debugging

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/RewindDebuggerCamera.h` (Private)


#### class `FRewindDebuggerCamera`  
`class FRewindDebuggerCamera : public IRewindDebuggerExtension`  
_L16-39_
- inherits: `IRewindDebuggerExtension`
- L21 _public prototype_ `FRewindDebuggerCamera();`
- L22 _public prototype_ `virtual ~FRewindDebuggerCamera();`
- L23 _public prototype_ `void Initialize();`
- L25 _public prototype_ `virtual void Update(float DeltaTime, IRewindDebugger* RewindDebugger) override;`
- L26 _public function_ `virtual FString GetName()`
- L28 _public prototype_ `ERewindDebuggerCameraMode CameraMode() const;`
- L29 _public prototype_ `void SetCameraMode(ERewindDebuggerCameraMode Mode);`
- L33 _private prototype_ `void MakeCameraModeMenu(UToolMenu* InMenu);`
- L35 _private member_ `bool bLastPositionValid;`
- L36 _private member_ `FVector LastPosition;`
- L38 _private member_ `TWeakObjectPtr<ACameraActor> CameraActor;`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/RewindDebuggerCommands.h` (Private)


#### class `FRewindDebuggerCommands`  
`class FRewindDebuggerCommands : public TCommands<FRewindDebuggerCommands>`  
_L11-56_
- inherits: `TCommands<FRewindDebuggerCommands>`
- L16 _public function_ `FRewindDebuggerCommands() : TCommands<FRewindDebuggerCommands>(TEXT("RewindDebugger"), LOCTEXT("RewindDebugger", "Rewind Debugger"), NAME_None, "RewindDebuggerStyle")` — Default constructor.
- L21 _public function_ `virtual void RegisterCommands() override`
- L41 _public member_ `TSharedPtr<FUICommandInfo> StartRecording;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> StopRecording;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> FirstFrame;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> PreviousFrame;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> ReversePlay;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> Pause;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> Play;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> NextFrame;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> LastFrame;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> PauseOrPlay;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> AutoEject;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> AutoRecord;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> OpenTrace;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> ClearAnalysis;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> AutoScroll;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "FRewindDebuggerCommands"`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/RewindDebuggerFallbackTrack.h` (Private)


#### class `RewindDebugger::FRewindDebuggerFallbackTrack`  
`class FRewindDebuggerFallbackTrack : public FRewindDebuggerTrack`  
_L10-32_
- inherits: `FRewindDebuggerTrack`
- L14 _public function_ `FRewindDebuggerFallbackTrack(uint64 InObjectId, const IRewindDebuggerViewCreator* InViewCreator) : ViewCreator(InViewCreator), ObjectId(InObjectId)`
- L20 _private prototype_ `virtual FSlateIcon GetIconInternal() override;`
- L21 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L22 _private function_ `virtual FName GetNameInternal() const override`
- L23 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L24 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L25 _private prototype_ `virtual bool UpdateInternal() override;`
- L27 _private member_ `const IRewindDebuggerViewCreator* ViewCreator;`
- L28 _private member_ `TWeakPtr<IRewindDebuggerView> View;`
- L29 _private member_ `FSlateIcon Icon;`
- L30 _private member_ `TRange<double> ExistenceRange;`
- L31 _private member_ `uint64 ObjectId;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/RewindDebuggerModule.h` (Private)


#### class `FRewindDebuggerModule`  
`class FRewindDebuggerModule : public IRewindDebuggerModule`  
_L18-62_
- inherits: `IRewindDebuggerModule`
- L22 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _public prototype_ `static FRewindDebuggerModule& Get();`
- L26 _public prototype_ `virtual FName GetMainTabName() const override;`
- L27 _public prototype_ `virtual FName GetMainToolbarName() const override;`
- L28 _public prototype_ `virtual FName GetPreviewMenuName() const override;`
- L29 _public prototype_ `virtual FName GetDetailsTabName() const override;`
- L30 _public prototype_ `virtual TSharedRef<SDockTab> SpawnRewindDebuggerTab(const FSpawnTabArgs& SpawnTabArgs) override;`
- L31 _public prototype_ `virtual TSharedRef<SDockTab> SpawnRewindDebuggerDetailsTab(const FSpawnTabArgs& SpawnTabArgs) override;`
- L33 _public member_ `static const FName MainToolBarName;`
- L34 _public member_ `static const FName RightToolBarName;`
- L35 _public member_ `static const FName CategoriesMenuName;`
- L36 _public member_ `static const FName PreviewMenuName;`
- L37 _public member_ `static const FName MainStatusBarName;`
- L38 _public member_ `static const FName MainTabName;`
- L39 _public member_ `static const FName DetailsTabName;`
- L40 _public member_ `static const FName TrackContextMenuName;`
- L45 _public function_ `TSharedPtr<UE::TraceBasedDebuggers::FTraceSessionsManager>& GetTraceSessionsManager()` — Returns the trace sessions manager instance used by RewindDebugger
- L51 _private member_ `TSharedPtr<UE::TraceBasedDebuggers::FTraceSessionsManager> TraceSessionsManager;`
- L55 _private member_ `TSharedPtr<SRewindDebugger> RewindDebuggerWidget;`
- L57 _private member_ `FRewindDebuggerCamera RewindDebuggerCameraExtension;`
- L58 _private member_ `FRewindDebuggerAnimation RewindDebuggerAnimationExtension;`
- L60 _private member_ `FDelegateHandle LevelEditorTabManagerChangedHandle;`
- L61 _private member_ `FDelegateHandle LevelEditorLayoutExtensionHandle;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/RewindDebuggerObjectTrack.h` (Private)


#### struct `RewindDebugger::FTrackCreatorAndTrack`  
`struct FTrackCreatorAndTrack`  
_L13-17_
- L15 _public member_ `const IRewindDebuggerTrackCreator* Creator;`
- L16 _public member_ `TSharedPtr<FRewindDebuggerTrack> Track;`

#### class `RewindDebugger::FRewindDebuggerObjectTrack`  
`class FRewindDebuggerObjectTrack : public FRewindDebuggerTrack`  
_L19-58_
- inherits: `FRewindDebuggerTrack`
- L23 _public prototype_ `FRewindDebuggerObjectTrack(const FObjectId& InObjectId, const FString& InObjectName, bool bInAddController = false);`
- L25 _public function_ `TSharedPtr<SEventTimelineView::FTimelineEventData> GetExistenceRange() const`
- L31 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L32 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L33 _private prototype_ `virtual bool UpdateInternal() override;`
- L34 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L35 _private prototype_ `virtual FName GetNameInternal() const override;`
- L36 _private prototype_ `virtual FSlateIcon GetIconInternal() override;`
- L37 _private prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L38 _private prototype_ `virtual uint64 GetObjectIdInternal() const override;`
- L39 _private prototype_ `virtual bool HasDebugDataInternal() const override;`
- L40 _private prototype_ `virtual bool HandleDoubleClickInternal() override;`
- L41 _private prototype_ `virtual FText GetStepCommandTooltipInternal(EStepMode) const override;`
- L42 _private prototype_ `virtual TOptional<double> GetStepFrameTimeInternal(EStepMode, const FScrubTimeInformation&) const override;`
- L44 _private member_ `mutable FText DisplayName;`
- L45 _private member_ `FString ObjectName;`
- L46 _private member_ `FSlateIcon Icon;`
- L47 _private member_ `TSharedPtr<SEventTimelineView::FTimelineEventData> ExistenceRange;`
- L48 _private member_ `FObjectId ObjectId;`
- L49 _private member_ `TArray<FTrackCreatorAndTrack> ChildTrackCreators;`
- L50 _private member_ `TArray<TSharedPtr<FRewindDebuggerTrack>> Children;`
- L53 _private member_ `TSharedPtr<FRewindDebuggerTrack> PrimaryChildTrack;` — This child track will be used by the current object track to replace its own appearance and timeline values
- L55 _private member_ `bool bAddController;`
- L56 _private member_ `mutable bool bDisplayNameValid;`
- L57 _private member_ `bool bIconSearched;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/RewindDebuggerRecordingControls.h` (Private)


#### struct `UE::RewindDebugger::FDebuggerRecordingControls`  
`struct FDebuggerRecordingControls : TraceBasedDebuggers::FRecordingControls`  
_L10-50_
- inherits: `TraceBasedDebuggers::FRecordingControls`
- L12 _public prototype_ `FDebuggerRecordingControls(const FName& InStatusBarId , const TSharedRef<TraceBasedDebuggers::FRemoteSessionsManager>& InRemoteSessionManager , const FGuid& InDebuggerId , const FLogCategoryBase& InLogCategory);`
- L18 _public prototype_ `bool IsRecordingLocalSession() const;`
- L20 _public prototype_ `bool CanStartRecordingLocalSession() const;`
- L23 _public prototype_ `void StartRecordingLocalSession();` — Starts recording in the local session and makes it the selected session.
- L25 _public prototype_ `void StopRecordingLocalSession();`
- L28 _protected prototype_ `TSharedPtr<TraceBasedDebuggers::FSessionInfo> GetLocalSessionInfo() const;`
- L30 _protected prototype_ `virtual TraceBasedDebuggers::FRecordingControlsConfig GetControlsConfig() const override;`
- L31 _protected prototype_ `virtual TSharedRef<SWidget> GenerateTargetSessionSelector() override;`
- L32 _protected prototype_ `virtual void AddToMenuInternal(FToolMenuSection& InSection) override;`
- L33 _protected prototype_ `virtual FString GetSaveDirPath() const override;`
- L35 _protected prototype_ `virtual UE::TraceBasedDebuggers::ETraceTransportMode GetTransportModeOverrideForTargetTypeInternal(EBuildTargetType InBuildTarget) const override;`
- L36 _protected prototype_ `virtual bool ConnectToLiveSession_RelayInternal(const FGuid& InSessionId) override;`
- L37 _protected prototype_ `virtual bool ConnectToLiveSession_DirectInternal(const FGuid& InSessionId) override;`
- L38 _protected prototype_ `virtual bool IsRecordingAvailableForSessionInternal(const TSharedRef<TraceBasedDebuggers::FSessionInfo>& InSessionInfo) const override;`
- L39 _protected prototype_ `virtual bool ShouldFilterOutSessionInternal(const TSharedRef<TraceBasedDebuggers::FSessionInfo>& InSessionInfo) const override;`
- L41 _protected prototype_ `virtual TNotNull<TUniquePtr<TraceBasedDebuggers::FStartRecordingCommandMessage>> BuildStartRecordingParamsInternal() override;`
- L42 _protected prototype_ `virtual void SendStartRecordingCommandInternal(const FMessageAddress& InAddress, TUniquePtr<TraceBasedDebuggers::FStartRecordingCommandMessage> InStartRecordingCommand) override;`
- L43 _protected prototype_ `virtual void SendStopRecordingCommandInternal(const FMessageAddress& InAddress) override;`
- L45 _protected prototype_ `virtual void OnToggleRecordingStateInternal(const TSharedRef<TraceBasedDebuggers::FSessionInfo>& InSessionInfo) override;`
- L46 _protected prototype_ `virtual void CloseSessionByRemoteSessionIDInternal(const FGuid& InSessionId) override;`
- L47 _protected prototype_ `virtual const TraceBasedDebuggers::FTraceSessionDescriptor& GetCurrentSessionDescriptorInternal() override;`
- L49 _protected member_ `static const FName RecordingOptionsMenuName;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace RewindDebugger` (scope `UE`)

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/RewindDebuggerStyle.h` (Private)


#### class `FRewindDebuggerStyle`  
`class FRewindDebuggerStyle : FSlateStyleSet`  
_L10-22_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of RewindDebugger
- L13 _public prototype_ `FRewindDebuggerStyle();`
- L14 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L17 _public prototype_ `static const ISlateStyle& Get();`
- L21 _private member_ `static TSharedPtr< FRewindDebuggerStyle > StyleInstance;`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/RewindDebuggerTrackCreators.h` (Private)


#### class `RewindDebugger::FRewindDebuggerTrackCreators`  
`class FRewindDebuggerTrackCreators`  
_L11-16_
- L14 _public prototype_ `static void EnumerateCreators(TFunctionRef<void(const IRewindDebuggerTrackCreator*)> Callback);`
- L15 _public prototype_ `static const IRewindDebuggerTrackCreator* GetCreator(FName CreatorName);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/RewindDebuggerViewCreators.h` (Private)


#### class `FRewindDebuggerViewCreators`  
`class FRewindDebuggerViewCreators`  
_L14-19_
- L17 _public prototype_ `static void EnumerateCreators(TFunctionRef<void(const IRewindDebuggerViewCreator*)> Callback);`
- L18 _public prototype_ `static const IRewindDebuggerViewCreator* GetCreator(FName CreatorName);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/SModalSessionBrowser.h` (Private)


#### class `SModalSessionBrowser`  
`class SModalSessionBrowser : public SWindow`  
_L23-83_
- inherits: `SWindow`
- desc: Modal window used to find, show and select active Trace Sessions to be used with Chaos Visual Debugger
- L34 _public function_ `SLATE_BEGIN_ARGS(SModalSessionBrowser)`
- L39 _public prototype_ `virtual ~SModalSessionBrowser() override;`
- L41 _public prototype_ `void Construct(const FArguments& InArgs);`
- L44 _public prototype_ `EAppReturnType::Type ShowModal();` — Displays the dialog in a blocking fashion
- L47 _public function_ `EAppReturnType::Type GetResponse() const` — Response that triggered the closing of this modal
- L50 _public prototype_ `FTraceSessionInfo GetSelectedTraceInfo();` — Returns information about the active trace session selected
- L53 _public function_ `FString GetSelectedTraceStoreAddress() const` — Returns the address of the trace store selected while looking for active Trace Sessions
- L55 _public prototype_ `void ModalTick(float InDeltaTime);`
- L59 _protected prototype_ `bool CanOpenSession() const;`
- L61 _protected prototype_ `void UpdateCurrentSessionInfoMap();`
- L63 _protected prototype_ `FReply OnButtonClick(EAppReturnType::Type ButtonID);`
- L65 _protected prototype_ `void HandleSessionNameSelected(TSharedPtr<FName> SelectedName);`
- L67 _protected prototype_ `void OnTraceStoreAddressUpdated(const FText& InText, ETextCommit::Type CommitType);`
- L69 _protected member_ `TSharedPtr<SModalSessionNameListPicker> NamePickerWidget;`
- L71 _protected member_ `TSharedPtr<SEditableTextBox> TraceStoreAddressWidget;`
- L73 _protected member_ `TMap<FName, FTraceSessionInfo> CurrentSessionInfosMap;`
- L75 _protected member_ `EAppReturnType::Type UserResponse = EAppReturnType::Cancel;`
- L77 _protected member_ `FString CurrentTraceStoreAddress;`
- L79 _protected member_ `FName CurrentTraceSessionSelected;`
- L81 _protected member_ `FDelegateHandle ModalTickHandle;`
- L82 _protected member_ `float AccumulatedTimeBetweenTicks = 0.0f;`

#### struct `SModalSessionBrowser::FTraceSessionInfo`  
`struct FTraceSessionInfo`  
_L26-32_
- L28 _public member_ `uint32 TraceID = 0;`
- L29 _public member_ `uint32 IPAddress = 0;`
- L30 _public member_ `uint32 ControlPort = 0;`
- L31 _public member_ `bool bIsValid = false;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace EAppReturnType`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/SModalSessionNameListPicker.h` (Private)


#### class `SModalSessionNameListPicker`  
`class SModalSessionNameListPicker : public SCompoundWidget`  
_L16-58_
- inherits: `SCompoundWidget`
- desc: Widget that takes a list of String Views and creates a drop down menu for it for the Chaos Visual Debugger Tool.
- L19 _public function_ `SLATE_BEGIN_ARGS(SModalSessionNameListPicker)`
- L20 _public prototype_ `SLATE_EVENT(FModalSessionNameListSelected, OnNameSleceted) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `void UpdateNameList(TArray<TSharedPtr<FName>>&& NewNameList);` — Replaces the names in the list view @param NewNameList Array of Name to represent.
- L31 _public prototype_ `void SelectName(const TSharedPtr<FName>& NameToSelect, ESelectInfo::Type SelectionInfo = ESelectInfo::Direct);`
- L35 _protected prototype_ `bool HasElements() const;`
- L37 _protected prototype_ `FText GetCurrentDropDownButtonLabel() const;`
- L39 _protected prototype_ `void OnClickItem(TSharedPtr<FName> Item);`
- L41 _protected prototype_ `void OnListOpened();`
- L43 _protected prototype_ `TSharedRef<ITableRow> MakeNameItemForList(TSharedPtr<FName> Name, const TSharedRef<STableViewBase>& OwnerTable);`
- L45 _protected member_ `TSharedPtr<SComboButton> PickerComboButton;`
- L47 _protected member_ `TSharedPtr<STextBlock> DropDownButtonLabelTextBox;`
- L49 _protected member_ `TSharedPtr<SListView<TSharedPtr<FName>>> NameListWidget;`
- L51 _protected member_ `TSharedPtr<SListViewSelectorDropdownMenu<TSharedPtr<FName>>> NamesListDropdown;`
- L53 _protected member_ `TArray<TSharedPtr<FName>> CachedNameList;`
- L55 _protected member_ `TSharedPtr<FName> CurrentSelectedName;`
- L57 _protected member_ `FModalSessionNameListSelected NameSelectedDelegate;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FModalSessionNameListSelected, TSharedPtr<FName>) class SModalSessionNameListPicker : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SModalSessionNameListPicker){} SLATE_EVENT(FModalSessionNameListSelected, OnNameSleceted) SLATE_END_ARGS() void Construct(const FArguments& InArgs); void UpdateNameList(TArray<TSharedPtr<FName>>&& NewNameList); void SelectName(const TSharedPtr<FName>& NameToSelect, ESelectInfo::Type SelectionInfo = ESelectInfo::Direct); protected: bool HasElements() const; FText GetCurrentDropDownButtonLabel() const; void OnClickItem(TSharedPtr<FName> Item); void OnListOpened(); TSharedRef<ITableRow> MakeNameItemForList(TSharedPtr<FName> Name, const TSharedRef<STableViewBase>& OwnerTable); TSharedPtr<SComboButton> PickerComboButton; TSharedPtr<STextBlock> DropDownButtonLabelTextBox; TSharedPtr<SListView<TSharedPtr<FName>>> NameListWidget; TSharedPtr<SListViewSelectorDropdownMenu<TSharedPtr<FName>>> NamesListDropdown;`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/SRewindDebugger.h` (Private)


#### class `SRewindDebugger`  
`class SRewindDebugger : public SCompoundWidget`  
_L20-125_
- inherits: `SCompoundWidget`
- L22 _private typedef_ `typedef TBindablePropertyInitializer<FString, BindingType_Out> DebugTargetInitializer;`
- L25 _public function_ `DECLARE_DELEGATE_TwoParams(FOnScrubPositionChanged, double, bool) DECLARE_DELEGATE_OneParam(FOnViewRangeChanged, const TRange<double>&) DECLARE_DELEGATE_OneParam(FOnDebugTargetChanged, TSharedPtr<FString>) DECLARE_DELEGATE_OneParam(FOnTrackDoubleClicked, TSharedPtr<RewindDebugger::FRewindDebuggerTrack>) DECLARE_DELEGATE_OneParam(FOnTrackSelectionChanged, TSharedPtr<RewindDebugger::FRewindDebuggerTrack>) DECLARE_DELEGATE_RetVal(TSharedPtr<SWidget>, FBuildTrackContextMenu) DECLARE_DELEGATE(FForceRefreshTracks) SLATE_BEGIN_ARGS(SRewindDebugger)`
- L34 _public prototype_ `SLATE_ARGUMENT(TArray< TSharedPtr< RewindDebugger::FRewindDebuggerTrack > >*, Tracks);`
- L35 _public prototype_ `SLATE_ARGUMENT(DebugTargetInitializer, DebuggedObjectName);`
- L36 _public prototype_ `SLATE_ARGUMENT(TBindablePropertyInitializer<double>, TraceTime);`
- L37 _public prototype_ `SLATE_ARGUMENT(TBindablePropertyInitializer<double>, RecordingDuration);`
- L38 _public prototype_ `SLATE_ATTRIBUTE(TArrayView<RewindDebugger::FRewindDebuggerTrackType>, TrackTypes);`
- L39 _public prototype_ `SLATE_ATTRIBUTE(double, ScrubTime);`
- L40 _public prototype_ `SLATE_ATTRIBUTE(bool, IsPIESimulating);`
- L41 _public prototype_ `SLATE_EVENT(FOnScrubPositionChanged, OnScrubPositionChanged);`
- L42 _public prototype_ `SLATE_EVENT(FOnViewRangeChanged, OnViewRangeChanged);`
- L43 _public prototype_ `SLATE_EVENT(FBuildTrackContextMenu, BuildTrackContextMenu);`
- L44 _public prototype_ `SLATE_EVENT(FOnTrackDoubleClicked, OnTrackDoubleClicked);`
- L45 _public prototype_ `SLATE_EVENT(FOnTrackSelectionChanged, OnTrackSelectionChanged);`
- L46 _public prototype_ `SLATE_EVENT(FForceRefreshTracks, ForceRefreshTracks);`
- L47 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FUICommandList> CommandList, const TSharedRef<SDockTab>& ConstructUnderMajorTab, const TSharedPtr<SWindow>& ConstructUnderWindow);`
- L59 _public prototype_ `SRewindDebugger();`
- L60 _public prototype_ `virtual ~SRewindDebugger();`
- L61 _public prototype_ `void TrackCursor(bool bReverse);`
- L62 _public prototype_ `void CenterView(double Time);`
- L63 _public prototype_ `void RefreshTracks();`
- L66 _private prototype_ `void SetViewRange(TRange<double> NewRange);`
- L68 _private prototype_ `void ToggleHideTrackType(const FName& TrackType);`
- L69 _private prototype_ `bool ShouldHideTrackType(const FName& TrackType) const;`
- L70 _private prototype_ `void ToggleDisplayEmptyTracks();`
- L71 _private prototype_ `bool ShouldDisplayEmptyTracks() const;`
- L73 _private prototype_ `void SortObjectsByName();`
- L74 _private prototype_ `bool ShouldSortObjectsByName() const;`
- L75 _private prototype_ `void SortObjectsByTime();`
- L76 _private prototype_ `bool ShouldSortObjectsByTime() const;`
- L78 _private prototype_ `virtual FReply OnPreviewKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L79 _private function_ `virtual bool SupportsKeyboardFocus() const override`
- L82 _private member_ `TAttribute<double> ScrubTimeAttribute;` — Time Slider
- L83 _private member_ `TAttribute<bool> IsPIESimulating;`
- L84 _private member_ `TAttribute<bool> TrackScrubbingAttribute;`
- L85 _private member_ `TAttribute<TArrayView<RewindDebugger::FRewindDebuggerTrackType>> TrackTypesAttribute;`
- L86 _private member_ `FOnScrubPositionChanged OnScrubPositionChanged;`
- L87 _private member_ `FOnViewRangeChanged OnViewRangeChanged;`
- L88 _private member_ `TRange<double> ViewRange;`
- L89 _private member_ `TBindableProperty<double> TraceTime;`
- L90 _private member_ `TBindableProperty<double> RecordingDuration;`
- L92 _private member_ `FForceRefreshTracks ForceRefreshTracks;`
- L93 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L94 _private member_ `const FRewindDebuggerCommands& Commands;`
- L97 _private prototype_ `TSharedRef<SWidget> MakeObjectSelectionMenu();` — debug object selector
- L98 _private prototype_ `void SetDebuggedObject(const UObject* Object);`
- L100 _private prototype_ `FReply OnSelectActorClicked();`
- L102 _private member_ `TBindableProperty<FString, BindingType_Out> DebuggedObjectName;`
- L104 _private prototype_ `TSharedRef<SWidget> MakeFilterMenu();`
- L108 _private member_ `TArray<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>* Tracks = nullptr;` — Track tree view
- L109 _private member_ `TSharedPtr<RewindDebugger::FRewindDebuggerTrack> SelectedComponent;`
- L110 _private prototype_ `void OnSelectedTrackChanged(TSharedPtr<RewindDebugger::FRewindDebuggerTrack> SelectedItem, ESelectInfo::Type SelectInfo);`
- L111 _private member_ `FBuildTrackContextMenu BuildTrackContextMenu;`
- L112 _private member_ `FOnTrackSelectionChanged OnTrackSelectionChanged;`
- L114 _private member_ `TSharedPtr<SRewindDebuggerTrackTree> TrackTreeView;`
- L115 _private member_ `TSharedPtr<SRewindDebuggerTimelines> TimelinesView;`
- L116 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L118 _private member_ `TSharedPtr<SSearchBox> TrackFilterBox;`
- L120 _private member_ `bool bInExpansionChanged = false;`
- L121 _private member_ `bool bInSelectionChanged = false;`
- L122 _private member_ `bool bDisplayEmptyTracks = false;`
- L124 _private member_ `URewindDebuggerSettings& Settings;`

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnScrubPositionChanged, double, bool) DECLARE_DELEGATE_OneParam(FOnViewRangeChanged, const TRange<double>&) DECLARE_DELEGATE_OneParam(FOnDebugTargetChanged, TSharedPtr<FString>) DECLARE_DELEGATE_OneParam(FOnTrackDoubleClicked, TSharedPtr<RewindDebugger::FRewindDebuggerTrack>) DECLARE_DELEGATE_OneParam(FOnTrackSelectionChanged, TSharedPtr<RewindDebugger::FRewindDebuggerTrack>) DECLARE_DELEGATE_RetVal(TSharedPtr<SWidget>, FBuildTrackContextMenu) DECLARE_DELEGATE(FForceRefreshTracks) SLATE_BEGIN_ARGS(SRewindDebugger) {} SLATE_ARGUMENT(TArray< TSharedPtr< RewindDebugger::FRewindDebuggerTrack > >*, Tracks);`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnViewRangeChanged, const TRange<double>&) DECLARE_DELEGATE_OneParam(FOnDebugTargetChanged, TSharedPtr<FString>) DECLARE_DELEGATE_OneParam(FOnTrackDoubleClicked, TSharedPtr<RewindDebugger::FRewindDebuggerTrack>) DECLARE_DELEGATE_OneParam(FOnTrackSelectionChanged, TSharedPtr<RewindDebugger::FRewindDebuggerTrack>) DECLARE_DELEGATE_RetVal(TSharedPtr<SWidget>, FBuildTrackContextMenu) DECLARE_DELEGATE(FForceRefreshTracks) SLATE_BEGIN_ARGS(SRewindDebugger) {} SLATE_ARGUMENT(TArray< TSharedPtr< RewindDebugger::FRewindDebuggerTrack > >*, Tracks);`
- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDebugTargetChanged, TSharedPtr<FString>) DECLARE_DELEGATE_OneParam(FOnTrackDoubleClicked, TSharedPtr<RewindDebugger::FRewindDebuggerTrack>) DECLARE_DELEGATE_OneParam(FOnTrackSelectionChanged, TSharedPtr<RewindDebugger::FRewindDebuggerTrack>) DECLARE_DELEGATE_RetVal(TSharedPtr<SWidget>, FBuildTrackContextMenu) DECLARE_DELEGATE(FForceRefreshTracks) SLATE_BEGIN_ARGS(SRewindDebugger) {} SLATE_ARGUMENT(TArray< TSharedPtr< RewindDebugger::FRewindDebuggerTrack > >*, Tracks);`
- L28 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTrackDoubleClicked, TSharedPtr<RewindDebugger::FRewindDebuggerTrack>) DECLARE_DELEGATE_OneParam(FOnTrackSelectionChanged, TSharedPtr<RewindDebugger::FRewindDebuggerTrack>) DECLARE_DELEGATE_RetVal(TSharedPtr<SWidget>, FBuildTrackContextMenu) DECLARE_DELEGATE(FForceRefreshTracks) SLATE_BEGIN_ARGS(SRewindDebugger) {} SLATE_ARGUMENT(TArray< TSharedPtr< RewindDebugger::FRewindDebuggerTrack > >*, Tracks);`
- L29 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTrackSelectionChanged, TSharedPtr<RewindDebugger::FRewindDebuggerTrack>) DECLARE_DELEGATE_RetVal(TSharedPtr<SWidget>, FBuildTrackContextMenu) DECLARE_DELEGATE(FForceRefreshTracks) SLATE_BEGIN_ARGS(SRewindDebugger) {} SLATE_ARGUMENT(TArray< TSharedPtr< RewindDebugger::FRewindDebuggerTrack > >*, Tracks);`
- L30 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedPtr<SWidget>, FBuildTrackContextMenu) DECLARE_DELEGATE(FForceRefreshTracks) SLATE_BEGIN_ARGS(SRewindDebugger) {} SLATE_ARGUMENT(TArray< TSharedPtr< RewindDebugger::FRewindDebuggerTrack > >*, Tracks);`
- L31 _delegate_ `DECLARE_DELEGATE(FForceRefreshTracks) SLATE_BEGIN_ARGS(SRewindDebugger) {} SLATE_ARGUMENT(TArray< TSharedPtr< RewindDebugger::FRewindDebuggerTrack > >*, Tracks);`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/SRewindDebuggerDetails.h` (Private)


#### class `SRewindDebuggerDetails`  
`class SRewindDebuggerDetails : public SCompoundWidget`  
_L11-27_
- inherits: `SCompoundWidget`
- L13 _private typedef_ `typedef TBindablePropertyInitializer<FString, BindingType_Out> FDebugTargetInitializer;`
- L16 _public function_ `SLATE_BEGIN_ARGS(SRewindDebuggerDetails)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SDockTab>& ConstructUnderMajorTab, const TSharedPtr<SWindow>& ConstructUnderWindow);`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/SRewindDebuggerTimelines.h` (Private)


#### class `SRewindDebuggerTimelines`  
`class SRewindDebuggerTimelines : public SSimpleTimeSlider`  
_L11-70_
- inherits: `SSimpleTimeSlider`
- L13 _private typedef_ `using FOnSelectionChanged = STreeView<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>::FOnSelectionChanged;`
- L15 _public function_ `SLATE_BEGIN_ARGS(SRewindDebuggerTimelines)`
- L17 _public prototype_ `SLATE_ARGUMENT(TArray< TSharedPtr< RewindDebugger::FRewindDebuggerTrack > >*, Tracks);`
- L18 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SScrollBar>, ExternalScrollbar) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnTableViewScrolled, OnScrolled) SLATE_EVENT(FSimpleDelegate, OnExpansionChanged) SLATE_ATTRIBUTE(double, ScrubPosition);`
- L28 _public prototype_ `SLATE_ATTRIBUTE(TRange<double>, ViewRange);` — View time range
- L31 _public prototype_ `SLATE_ATTRIBUTE(TRange<double>, ClampRange);` — Clamp time range
- L34 _public prototype_ `SLATE_EVENT(FOnScrubPositionChanged, OnScrubPositionChanged);` — Called when the scrub position changes
- L37 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnBeginScrubberMovement);` — Called right before the scrubber begins to move
- L40 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnEndScrubberMovement);` — Called right after the scrubber handle is released by the user
- L43 _public prototype_ `SLATE_EVENT(FOnRangeChanged, OnViewRangeChanged);` — Called when the view range changes
- L45 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L54 _public prototype_ `void Refresh();`
- L55 _public prototype_ `void RestoreExpansion();`
- L57 _public prototype_ `void SetSelection(TSharedPtr<RewindDebugger::FRewindDebuggerTrack> SelectedItem) const;`
- L58 _public prototype_ `void ScrollTo(double ScrollOffset) const;`
- L60 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L63 _private prototype_ `TSharedRef<ITableRow> TreeViewGenerateRow(TSharedPtr<RewindDebugger::FRewindDebuggerTrack> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L64 _private prototype_ `void TimelineViewExpansionChanged(TSharedPtr<RewindDebugger::FRewindDebuggerTrack> InItem, bool bShouldBeExpanded) const;`
- L66 _private member_ `TArray<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>* Tracks = nullptr;`
- L67 _private member_ `TSharedPtr<STreeView<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>> TreeView;`
- L69 _private member_ `FSimpleDelegate OnExpansionChanged;`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Private/SRewindDebuggerTrackTree.h` (Private)


#### class `SRewindDebuggerTrackTree`  
`class SRewindDebuggerTrackTree : public SCompoundWidget`  
_L10-47_
- inherits: `SCompoundWidget`
- L12 _private typedef_ `using FOnSelectionChanged = STreeView<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>::FOnSelectionChanged;`
- L13 _private typedef_ `using FOnMouseButtonDoubleClick = STreeView<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>::FOnMouseButtonDoubleClick;`
- L16 _public function_ `SLATE_BEGIN_ARGS(SRewindDebuggerTrackTree)`
- L17 _public prototype_ `SLATE_ARGUMENT(TArray< TSharedPtr< RewindDebugger::FRewindDebuggerTrack > >*, Tracks);`
- L18 _public prototype_ `SLATE_ARGUMENT(TSharedPtr< SScrollBar >, ExternalScrollBar);`
- L19 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnMouseButtonDoubleClick, OnMouseButtonDoubleClick) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_EVENT(FSimpleDelegate, OnExpansionChanged) SLATE_EVENT(FOnTableViewScrolled, OnScrolled) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L33 _public prototype_ `void Refresh();`
- L34 _public prototype_ `void RestoreExpansion();`
- L36 _public prototype_ `void SetSelection(const TSharedPtr<RewindDebugger::FRewindDebuggerTrack>& SelectedItem) const;`
- L37 _public prototype_ `void ScrollTo(double ScrollOffset) const;`
- L40 _private prototype_ `TSharedRef<ITableRow> TreeViewGenerateRow(TSharedPtr<RewindDebugger::FRewindDebuggerTrack> InItem, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L41 _private prototype_ `void TreeViewExpansionChanged(TSharedPtr<RewindDebugger::FRewindDebuggerTrack> InItem, bool bShouldBeExpanded) const;`
- L43 _private member_ `TArray<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>* Tracks = nullptr;`
- L44 _private member_ `TSharedPtr<STreeView<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>> TreeView;`
- L46 _private member_ `FSimpleDelegate OnExpansionChanged;`

### `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Public/RewindDebuggerSettings.h` (Public)


#### enum `ERewindDebuggerCameraMode`  
`enum class ERewindDebuggerCameraMode : uint8`  
_L24-29_
- reflection: `UENUM()`
- L26 _public enumerator_ `Replay UMETA(Tooltip="Replay Recorded Camera")`
- L27 _public enumerator_ `FollowTargetActor UMETA(Tooltip="Follow Target Actor")`
- L28 _public enumerator_ `Disabled UMETA(Tooltip="Disable Camera On Playback")`

#### enum `ERewindDebuggerObjectSortMode`  
`enum class ERewindDebuggerObjectSortMode : uint8`  
_L32-36_
- reflection: `UENUM()`
- L34 _public enumerator_ `Time UMETA(Tooltip="Sort Object tracks By Id, making older objects display first")`
- L35 _public enumerator_ `Name UMETA(Tooltip="Sort Object Tracks alphabetically by Name")`

#### class `URewindDebuggerProjectSettings`  
`class URewindDebuggerProjectSettings : public UDeveloperSettings`  
_L42-68_
- reflection: `UCLASS(config = RewindDebugger, defaultconfig, EditInlineNew, DisplayName = "Rewind Debugger", collapseCategories, MinimalAPI)`
- inherits: `UDeveloperSettings`
- desc: Implements project settings for the Rewind Debugger.
- L47 _public prototype_ `URewindDebuggerProjectSettings();`
- L50 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L53 _public prototype_ `virtual FName GetCategoryName() const override;`
- L60 _public member_ `TArray<FSoftClassPath> SelectorAllowedTypes;` — `UPROPERTY(Config, EditAnywhere, Category = "Target selection")` — Class types allowed in the target selection dropdown for the project. Empty list means that all types are allowed (if SelectorAllowedStructTypes is also empty).
- L67 _public member_ `TArray<FInstancedStruct> SelectorAllowedStructTypes;` — `UPROPERTY(Config, EditAnywhere, Category = "Target selection")` — Struct types allowed in the target selection dropdown for the project. Empty list means that all types are allowed (if SelectorAllowedTypes is also empty).

#### class `URewindDebuggerSettings`  
`class URewindDebuggerSettings : public UDeveloperSettings`  
_L74-159_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, meta=(DisplayName="Rewind Debugger (user preferences)"))`
- inherits: `UDeveloperSettings`
- desc: Implements user settings for the Rewind Debugger.
- L79 _public prototype_ `URewindDebuggerSettings();`
- L80 _public prototype_ `~URewindDebuggerSettings();`
- L83 _public prototype_ `virtual FText GetSectionText() const override;`
- L84 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L87 _public prototype_ `virtual FName GetCategoryName() const override;`
- L92 _public prototype_ `UE::TraceBasedDebuggers::ETraceTransportMode GetTransportModeForTargetType(EBuildTargetType InTargetType) const;` — Returns the configured transport mode for the provided target type @param InTargetType Build target type to evaluate
- L98 _public prototype_ `void SetTransportModeForTargetType(EBuildTargetType InTargetType, UE::TraceBasedDebuggers::ETraceTransportMode InTransportMode);` — Sets a specific transport mode for the provided target type @param InTargetType Build target type to evaluate @param InTransportMode New transport mode to use for the provided target
- L102 _public member_ `ERewindDebuggerCameraMode CameraMode;` — `UPROPERTY(EditAnywhere, Config, Category = Camera)` — Rewind Debugger Playback Camera Mode
- L106 _public member_ `ERewindDebuggerObjectSortMode ObjectTrackSortMode = ERewindDebuggerObjectSortMode::Time;` — `UPROPERTY(EditAnywhere, Config, Category = Other)` — Rewind Debugger Object Track Sort Mode
- L110 _public member_ `bool bShouldAutoEject;` — `UPROPERTY(EditAnywhere, Config, Category = Other)` — If enabled, automatically detach player control when PIE is paused
- L114 _public member_ `bool bShouldAutoRecordOnPIE;` — `UPROPERTY(EditAnywhere, Config, Category = Other)` — If enabled, start recording information at the start of PIE
- L118 _public member_ `float PlaybackRate = 1.0;` — `UPROPERTY(EditAnywhere, Config, Category = Other)` — Playback speed multiplier
- L122 _public member_ `bool bShowEmptyObjectTracks;` — `UPROPERTY(EditAnywhere, Config, Category = Filters)` — If enabled, show empty tracks on Rewind Debugger Timeline
- L126 _public member_ `TArray<FName> HiddenTrackTypes;` — `UPROPERTY(EditAnywhere, Config, Category = Filters)` — The track types listed here will be hidden from the track tree view
- L130 _public member_ `FString DebugTargetActor;` — `UPROPERTY(Config)` — Currently selected target actor's name
- L137 _public member_ `TArray<FSoftClassPath> SelectorAllowedTypes;` — `UPROPERTY(Config, EditAnywhere, Category = "Target selection")` — Additional class types allowed in the target selection dropdown @note These can only add more allowed types to the types allowed by the project settings, not replace/override them
- L144 _public member_ `TArray<FInstancedStruct> SelectorAllowedStructTypes;` — `UPROPERTY(Config, EditAnywhere, Category = "Target selection")` — Additional struct types allowed in the target selection dropdown @note These can only add more allowed types to the types allowed by the project settings, not replace/override them
- L147 _public prototype_ `static URewindDebuggerSettings& Get();` — Get Mutable CDO of URewindDebuggerSettings
- L152 _private member_ `UE::TraceBasedDebuggers::ETraceTransportMode GameServerDataTransportMode;` — `UPROPERTY(EditAnywhere, Category = Connection)` — Default Data Transport for Game Servers - Used to change the transport mode for the trace data. This is not saved in the config by design
- L156 _private member_ `UE::TraceBasedDebuggers::ETraceTransportMode GameClientDataTransportMode;` — `UPROPERTY(EditAnywhere, Category = Connection)` — Default Data Transport for Game Clients - Used to change the transport mode for the trace data. This is not saved in the config by design
- L158 _private member_ `FDelegateHandle OnPreExitHandle;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API REWINDDEBUGGER_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
