# Runtime / TraceBasedDebuggersAnalysis

- module root: `Source/Runtime/Experimental/TraceBasedDebuggersAnalysis`
- headers: 4; symbols: 247
- symbol kinds: class=6, delegate=1, enum=3, enumerator=11, function=23, macro=4, member=78, namespace=12, prototype=103, struct=5, typedef=1
- PrivateDependencyModuleNames: EditorSubsystem, EditorWidgets, Slate, SlateCore, Sockets, StatusBar, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, TraceBasedDebuggers

### `Source/Runtime/Experimental/TraceBasedDebuggersAnalysis/Public/TraceDataStreamTypes.h` (Public)


#### struct `UE::TraceBasedDebuggers::FSerializedDataBuffer`  
`struct FSerializedDataBuffer`  
_L25-63_
- desc: Wrapper around a data buffer used for serialization of trace-based debuggers data
- L27 _public function_ `FSerializedDataBuffer(const TConstArrayView<uint8> ConstView) : DataBuffer(ConstView.GetData(), ConstView.Num())`
- L32 _public function_ `FSerializedDataBuffer(TArray<uint8>&& InByteArray) : DataBuffer(MoveTemp(InByteArray))`
- L37 _public function_ `FSerializedDataBuffer(const TArray<uint8>& InByteArray) : DataBuffer(InByteArray)`
- L42 _public function_ `FSerializedDataBuffer()`
- L46 _public function_ `TArray<uint8>& GetDataAsByteArrayRef()`
- L51 _public function_ `int32 GetSize() const`
- L56 _public function_ `void Serialize(FArchive& Ar)`
- L62 _private member_ `TArray<uint8> DataBuffer;`

#### class `UE::TraceBasedDebuggers::IRemoteSessionDataStream`  
`class IRemoteSessionDataStream`  
_L71-78_
- L74 _public prototype_ `virtual ~IRemoteSessionDataStream() = default;`
- L75 _public prototype_ `virtual FGuid GetOwningRemoteSessionID() const = 0;`
- L76 _public prototype_ `virtual uint64 UpdateAndGetBytesReadSinceLastMeasurement() = 0;`
- L77 _public prototype_ `virtual TSharedPtr<FRemoteSessionsManager> GetSessionsManager() const = 0;`

#### class `UE::TraceBasedDebuggers::FSessionStreamStatsUpdater`  
`class FSessionStreamStatsUpdater : FTSTickerObjectBase`  
_L80-96_
- inherits: `FTSTickerObjectBase`
- L85 _public function_ `explicit FSessionStreamStatsUpdater(IRemoteSessionDataStream* const DataStreamInstance) : DataStreamInstance(DataStreamInstance)`
- L91 _private prototype_ `virtual bool Tick(float DeltaTime) override;`
- L93 _private member_ `IRemoteSessionDataStream* DataStreamInstance;`
- L95 _private member_ `double ElapsedTimeSinceLastUpdate = 0.0;`

#### class `UE::TraceBasedDebuggers::FDirectSocketStream`  
`class FDirectSocketStream : public Trace::FDirectSocketStream, public IRemoteSessionDataStream`  
_L98-128_
- inherits: `Trace::FDirectSocketStream,IRemoteSessionDataStream`
- L102 _public prototype_ `FDirectSocketStream() = delete;`
- L104 _public function_ `explicit FDirectSocketStream(const TSharedRef<FRemoteSessionsManager>& InSessionsManager , const FGuid& InRemoteSessionID , TUniquePtr<FArchiveFileWriterGeneric>&& InFileWriter ) : Trace::FDirectSocketStream(MoveTemp(InFileWriter)) , WeakSessionManager(InSessionsManager.ToWeakPtr()) , BytesReadSinceLastMeasurement(0) , RemoteSessionID(InRemoteSessionID) , StatsUpdater(this)`
- L116 _public prototype_ `virtual int32 Read(void* Data, uint32 Size) override;`
- L118 _public prototype_ `virtual FGuid GetOwningRemoteSessionID() const override;`
- L119 _public prototype_ `virtual uint64 UpdateAndGetBytesReadSinceLastMeasurement() override;`
- L120 _public prototype_ `virtual TSharedPtr<FRemoteSessionsManager> GetSessionsManager() const override;`
- L123 _private member_ `TWeakPtr<FRemoteSessionsManager> WeakSessionManager;`
- L124 _private member_ `std::atomic<uint64> BytesReadSinceLastMeasurement;`
- L125 _private member_ `FGuid RemoteSessionID;`
- L127 _private member_ `FSessionStreamStatsUpdater StatsUpdater;`

#### class `UE::TraceBasedDebuggers::FRelayDataStream`  
`class FRelayDataStream : public Trace::IInDataStream, public IRemoteSessionDataStream`  
_L131-171_
- inherits: `Trace::IInDataStream,IRemoteSessionDataStream`
- desc: A trace data stream object that listens for data coming from a relay stream via provided DataRelayTransport instance
- L134 _public prototype_ `explicit FRelayDataStream(const TSharedRef<FRemoteSessionsManager>& InSessionsManager , const TSharedRef<IDataRelayTransport>& InDataRelay , const FGuid& InRemoteSessionID , TUniquePtr<FArchiveFileWriterGeneric>&& InFileWriter);`
- L141 _public prototype_ `void EnqueueRelayedData(const TConstArrayView<uint8> InTraceDataBuffer);`
- L142 _public prototype_ `void EnqueueRelayedData(TArray<uint8>&& InTraceDataBuffer);`
- L144 _public prototype_ `virtual FGuid GetOwningRemoteSessionID() const override;`
- L145 _public prototype_ `virtual uint64 UpdateAndGetBytesReadSinceLastMeasurement() override;`
- L146 _public prototype_ `virtual TSharedPtr<FRemoteSessionsManager> GetSessionsManager() const override;`
- L149 _private prototype_ `virtual int32 Read(void* Dest, uint32 DestSize) override;`
- L150 _private prototype_ `virtual void Close() override;`
- L151 _private prototype_ `virtual bool WaitUntilReady() override;`
- L153 _private member_ `TWeakPtr<FRemoteSessionsManager> WeakSessionManager;`
- L154 _private member_ `TSpscQueue<FSerializedDataBuffer> DataQueue;`
- L155 _private member_ `FEvent* CancelEvent = nullptr;`
- L156 _private member_ `FEvent* WaitForDataEvent = nullptr;`
- L157 _private member_ `TOptional<FSerializedDataBuffer> CurrentPacket;`
- L159 _private member_ `FGuid RemoteSessionID = FGuid();`
- L161 _private member_ `TUniquePtr<FArchiveFileWriterGeneric> FileWriter;`
- L164 _private member_ `TSharedPtr<IDataRelayTransport> RelayTransportInstance;`
- L167 _private member_ `std::atomic<uint64> BytesReadSinceLastMeasurement;`
- L168 _private member_ `FSessionStreamStatsUpdater StatsUpdater;`
- L169 _private member_ `uint32 CurrentPacketOffset = 0;`
- L170 _private member_ `bool bClosed = false;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TRACEBASEDDEBUGGERSANALYSIS_API`
- L14 _namespace_ `namespace TraceServices`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L65 _function_ `inline FArchive& operator<<(FArchive& Ar, FSerializedDataBuffer& Data)` (scope `UE::TraceBasedDebuggers`)

### `Source/Runtime/Experimental/TraceBasedDebuggersAnalysis/Public/TraceSessionsManager.h` (Public)


#### struct `UE::TraceBasedDebuggers::FTraceSessionDescriptor`  
`struct FTraceSessionDescriptor`  
_L37-67_
- desc: Structure containing info about a trace session used by trace-based debuggers
- L40 _public member_ `FString SessionName;` — The trace session name. Used to get the trace analysis instance for this session
- L43 _public member_ `FGuid RemoteSessionID;` — Session ID of this session in the Remote Session management system
- L46 _public member_ `uint16 SessionPort = 0;` — Port number used to establish a connection to this session. The value is 0 if no specific port was used
- L49 _public member_ `bool bIsLiveSession = false;` — True if this is a session recorded live (not loaded from disk)
- L52 _public function_ `bool IsValid() const` — Returns true if valid. For a session to be valued needs at minimum have a Trace Session name

#### class `UE::TraceBasedDebuggers::FTraceSessionsManager`  
`class FTraceSessionsManager`  
_L70-201_
- desc: Manager class used by trace-based debuggers to interact/control UE Trace systems
- L73 _private typedef_ `typedef FNoLoggingCategory FLogCategoryAlias;`
- L86 _public prototype_ `FTraceSessionsManager(FRuntimeModule& RuntimeModule , FEngineEditorBridge& Bridge , const TSharedPtr<TraceServices::IModule>& TraceModule , FStringView SaveDirectorySubPathInUserDir);` — @param RuntimeModule Debugger runtime module used to provide names for the trace files @param Bridge The engine-editor bridge instance used to provide access to the remote sessions manager @param TraceModule Optional trace module that will be registered/deregistered as a ModularFeature for the TraceServices @param SaveDirectorySubPathInUserDir Subdirectory path that will be used by GetDefaultSaveDirPath
- L90 _public prototype_ `~FTraceSessionsManager();`
- L92 _public function_ `void SetSavePathOverride(const TAttribute<FFilePath>& InSavePathOverride)`
- L97 _public function_ `void SetSaveRecordingsToDisk(const TAttribute<bool>& bInSaveRecordingsToDisk)`
- L107 _public prototype_ `FString LoadTraceFile(const FString& InTraceFilename, const TFunction<void()>& PreStartAnalysisFunc = nullptr);` — Loads a trace file and starts analyzing it @param InTraceFilename File Name including (Path Included) of the Trace file to load @param PreStartAnalysisFunc Optional function called right before starting the trace analysis (i.e., TraceServices::IAnalysisService::StartAnalysis)
- L109 _public prototype_ `FString LoadTraceFile(TUniquePtr<IFileHandle>&& InFileHandle, const FString& InTraceSessionName, const TFunction<void()>& PreStartAnalysisFunc = nullptr);`
- L118 _public prototype_ `FString ConnectToLiveSession(FStringView InSessionHost, uint32 SessionID, TFunction<void()> PreStartAnalysisFunc = nullptr);` — Connects to a live Trace Session and starts analyzing it. @param InSessionHost Trace Store Address for this session @param SessionID Trace ID in the Trace Store provided as host @param PreStartAnalysisFunc Optional function called right before starting the trace analysis (i.e., TraceServices::IAnalysisService::StartAnalysis) @return Session Name
- L127 _public prototype_ `FString ConnectToLiveSession_Direct(FGuid RemoteSessionID, uint16& OutSessionPort, TFunction<void()> PreStartAnalysisFunc = nullptr);` — Opens up a direct trace stream and waits for data @param RemoteSessionID Session ID to which we want to connect to @param OutSessionPort Number of the port we open for this session @param PreStartAnalysisFunc Optional function called right before starting the trace analysis (i.e., TraceServices::IAnalysisService::StartAnalysis) @return Session Name
- L135 _public prototype_ `FString ConnectToLiveSession_Relay(FGuid RemoteSessionID, TFunction<void()> PreStartAnalysisFunc = nullptr);` — Opens up a relay trace stream and waits for data @param RemoteSessionID Session ID to which we want to connect to @param PreStartAnalysisFunc Optional function called right before starting the trace analysis (i.e., TraceServices::IAnalysisService::StartAnalysis) @return Session Name
- L138 _public prototype_ `FString GetLocalTraceStoreDirPath();` — Returns the path to the local trace store
- L141 _public prototype_ `TSharedPtr<const TraceServices::IAnalysisSession> GetSession(const FString& InSessionName);` — Returns a ptr to the session registered with the provided session name. Null if no session is found
- L144 _public prototype_ `void CloseSession(const FString& InSessionName);` — Stops and de-registers a trace session registered with the provided session name
- L147 _public prototype_ `void StopSession(const FString& InSessionName);` — Stops a trace session registered with the provided session name
- L149 _public prototype_ `static const Trace::FStoreClient::FSessionInfo* GetTraceSessionInfo(FStringView InSessionHost, FGuid TraceGuid);`
- L152 _public prototype_ `template <typename TVisitor> void EnumerateActiveSessions(TVisitor Callback);`
- L159 _public prototype_ `FString GetTraceFileNameFromStoreForSession(FStringView InSessionHost, uint32 SessionID);` — Access the trace store at the provided host address, and returns the file name for the trace file @param InSessionHost Address of the Trace Store @param SessionID Session id of the trace data from which get the file name from @return Full Filename with path to the trace file if it exists. Returns an empty string if a trace file cannot be found
- L165 _public prototype_ `Trace::FStoreClient::FTraceData GetTraceDataStreamFromStore(FStringView InSessionHost, uint32 SessionID);` — Access the trace store at the provided host address, and returns a trace data stream ready to use @param InSessionHost Address of the Trace Store @param SessionID Session id of the trace data
- L174 _public prototype_ `FString GetSaveDirPath() const;` — Returns the actual path where recordings should be saved. That path is either the override provided by the path override or the default one. @see SetSavePathOverride @see GetDefaultSaveDirPath
- L177 _public prototype_ `FString GetDefaultSaveDirPath() const;` — @return The default path inside the user directory where recordings should be saved.
- L180 _private prototype_ `TUniquePtr<FArchiveFileWriterGeneric> OpenTraceFileForWrite(const FString& InDirectoryToSavePath) const;`
- L182 _private prototype_ `bool ConnectToLiveSession_Internal(uint32 SessionID, const TFunction<void()>& PreStartAnalysisFunc, const FString& InRequestedSessionName, Trace::FStoreClient::FTraceData&& InTraceDataStream);`
- L184 _private prototype_ `static TUniquePtr<Trace::IInDataStream> CreateFileDataStream(TUniquePtr<IFileHandle>&& InFileHandle);`
- L185 _private prototype_ `TUniquePtr<FRelayDataStream> CreateRelayDataStream(FGuid RemoteSessionID) const;`
- L187 _private member_ `FRuntimeModule& RuntimeModule;`
- L188 _private member_ `FEngineEditorBridge& EngineEditorBridge;`
- L191 _private member_ `TMap<FString, TSharedPtr<const TraceServices::IAnalysisSession>> AnalysisSessionByName;` — The trace analysis sessions.
- L193 _private member_ `TSharedPtr<TraceServices::IModule> TraceModule;`
- L195 _private member_ `const FString SaveDirectorySubPathInUserDir;`
- L196 _private member_ `TAttribute<FFilePath> SavePathOverride;`
- L197 _private member_ `TAttribute<bool> bSaveRecordingsToDisk = true;`
- L199 _private member_ `static uint16 CurrentDirectModeStartingPort;`
- L200 _private member_ `static constexpr uint16 DefaultStartingPort = 1993;`
- L204 _function_ `template <typename TVisitor> void FTraceSessionsManager::EnumerateActiveSessions(TVisitor Callback)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Trace` (scope `UE`)
- L20 _namespace_ `namespace TraceServices`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L32 _macro_ `#define UE_API TRACEBASEDDEBUGGERSANALYSIS_API`
- L57 _function_ `friend bool operator==(const FTraceSessionDescriptor& Lhs, const FTraceSessionDescriptor& RHS)` (scope `UE::TraceBasedDebuggers`)
- L63 _function_ `friend bool operator!=(const FTraceSessionDescriptor& Lhs, const FTraceSessionDescriptor& RHS)` (scope `UE::TraceBasedDebuggers`)

### `Source/Runtime/Experimental/TraceBasedDebuggersAnalysis/Public/Widgets/RecordingControls.h` (Public)


#### enum `UE::TraceBasedDebuggers::ELiveConnectionAttemptResult`  
`enum class ELiveConnectionAttemptResult`  
_L28-33_
- reflection: `UENUM()`
- L30 _public enumerator_ `Success`
- L31 _public enumerator_ `Failed`
- L32 _public enumerator_ `Canceled`

#### struct `UE::TraceBasedDebuggers::FRecordingControlsConfig`  
`struct FRecordingControlsConfig`  
_L36-46_
- desc: Toolbar integration options for FRecordingControls.
- L39 _public member_ `FName OptionsMenuName = NAME_None;` — Options menu shown by the combo button. NAME_None hides the button.
- L42 _public member_ `bool bHasRecordingLabel = true;` — Show a "Start Recording" text label next to the record icon.
- L45 _public member_ `FToolMenuInsert SectionInsertPosition = FToolMenuInsert();` — Insert position of the "RecordingControls" section within the host toolbar.

#### struct `UE::TraceBasedDebuggers::FRecordingControls`  
`struct FRecordingControls : TSharedFromThis<FRecordingControls>`  
_L48-280_
- inherits: `TSharedFromThis<FRecordingControls>`
- L51 _public member_ `static const FName BaseRecordingOptionsMenuName;` — Parent menu plugins can extend to add entries to all debugger options menus.
- L53 _public prototype_ `FRecordingControls(const FName InStatusBarId , const TSharedRef<FRemoteSessionsManager>& InRemoteSessionManager , const FGuid& InDebuggerId , const FLogCategoryBase& InLogCategory);`
- L58 _public prototype_ `virtual ~FRecordingControls();`
- L60 _public prototype_ `void Initialize();`
- L61 _public prototype_ `void Deinitialize();`
- L62 _public prototype_ `void AddToMenu(FName ExistingMenu);`
- L65 _public prototype_ `TSharedPtr<FSessionInfo> GetCurrentSessionInfo() const;` — Return the details about the currently selected session
- L68 _public member_ `FOnSessionEvent OnRecordingStarted;` — Delegate executed when recording got started in a given session
- L71 _public member_ `FOnSessionEvent OnRecordingStopped;` — Delegate executed when recording got stopped in a given session
- L74 _public member_ `FOnSessionEvent OnSessionSelected;` — Delegate executed when a given session got selected
- L78 _protected function_ `virtual void AddToMenuInternal(FToolMenuSection& InSection)`
- L82 _protected function_ `virtual void OnGenerateTargetSessionSelectorInternal(FMenuBuilder& InMenuBuilder)`
- L87 _protected function_ `virtual FRecordingControlsConfig GetControlsConfig() const` — Override to opt in to the options combo button and toolbar-style entries. Defaults keep the widget path.
- L92 _protected prototype_ `virtual TSharedRef<SWidget> GenerateTargetSessionSelector();`
- L93 _protected prototype_ `TSharedRef<SWidget> GenerateTargetSessionDropdown();`
- L95 _protected prototype_ `virtual FString GetSaveDirPath() const = 0;`
- L97 _protected prototype_ `virtual int32 GetMaxConnectionRetriesInternal() const;`
- L98 _protected prototype_ `ETraceTransportMode GetTransportMode(EBuildTargetType InBuildTarget) const;`
- L99 _protected prototype_ `virtual ETraceTransportMode GetTransportModeOverrideForTargetTypeInternal(EBuildTargetType InBuildTarget) const;`
- L101 _protected prototype_ `virtual bool ConnectToLiveSession_RelayInternal(const FGuid& InSessionId) = 0;`
- L102 _protected prototype_ `virtual bool ConnectToLiveSession_DirectInternal(const FGuid& InSessionId) = 0;`
- L125 _protected prototype_ `[[nodiscard]] virtual TNotNull<TUniquePtr<FStartRecordingCommandMessage>> BuildStartRecordingParamsInternal() = 0;` — Derived classes must override this method to provide the specific message type required to start recording That type must inherit from FStartRecordingCommandMessage. Once message is ready to be sent the RecordingControls base class will call SendStartRecordingCommandInternal so the type can be de-referenced to call the templated function SendCommand of the sessions manager. e.g., TNotNull<TUniquePtr<FStartRecordingCommandMessage>> FMyRecordingControls::BuildStartRecordingParamsInternal() { return MakeUnique<FMyStartRecordingCommandMessage>(); } void FMyRecordingControls::SendStartRecordingCommandInternal(const FMessageAddress& InAddress, TUniquePtr<FStartRecordingCommandMessage> InStartRecordingCommand) { if (const TSharedPtr<FRemoteSessionsManager> SessionsManager = RemoteSessionManagerWeakPtr.Pin()) { const FMyStartRecordingCommandMessage* StartRecordingCommand = static_cast<FMyStartRecordingCommandMessage*>(InStartRecordingCommand.Get()); SessionsManager->SendCommand(InAddress, *StartRecordingCommand); } } @see SendStartRecordingCommandInternal
- L127 _protected prototype_ `virtual void SendStartRecordingCommandInternal(const FMessageAddress& InAddress, TUniquePtr<FStartRecordingCommandMessage> InStartRecordingCommand) = 0;`
- L129 _protected prototype_ `virtual void SendStopRecordingCommandInternal(const FMessageAddress& InAddress) = 0;`
- L131 _protected prototype_ `virtual bool IsRecordingAvailableForSessionInternal(const TSharedRef<FSessionInfo>& InSessionInfo) const;`
- L136 _protected prototype_ `virtual bool ShouldFilterOutSessionInternal(const TSharedRef<FSessionInfo>& InSessionInfo) const;` — @return Whether a given session info should be excluded from the list exposed to the user
- L138 _protected prototype_ `virtual void OnToggleRecordingStateInternal(const TSharedRef<FSessionInfo>& InSessionInfo) = 0;`
- L139 _protected prototype_ `virtual void CloseSessionByRemoteSessionIDInternal(const FGuid& InSessionId) = 0;`
- L141 _protected prototype_ `virtual const FTraceSessionDescriptor& GetCurrentSessionDescriptorInternal() = 0;`
- L143 _protected prototype_ `void SelectTargetSession(FGuid SessionId);`
- L145 _protected prototype_ `void ToggleRecordingState(const TSharedPtr<FSessionInfo>& InSessionInfo);`
- L146 _protected function_ `FReply ToggleRecordingState()`
- L152 _protected prototype_ `void ToggleSingleSessionRecordingState(const TSharedRef<FSessionInfo>& InSessionInfo);`
- L154 _protected prototype_ `void SetSessionRecordingState(bool bIsRecording, const TSharedRef<FSessionInfo>& SessionInfoRef);`
- L155 _protected prototype_ `bool IsRecording() const;`
- L156 _protected prototype_ `bool IsRecordingPossibleForSession(const TSharedPtr<FSessionInfo>& InSessionInfo) const;`
- L157 _protected function_ `bool IsRecordingToggleButtonEnabled() const`
- L162 _protected prototype_ `FSlateIcon GetIconForSession(FGuid SessionId) const;`
- L164 _protected member_ `const TWeakPtr<FRemoteSessionsManager> RemoteSessionManagerWeakPtr;`
- L166 _protected member_ `TWeakPtr<IDataRelayTransport> TraceRelayTransportInstanceWeakPtr;`
- L168 _protected member_ `const FSlateBrush* StartRecordingBrush = nullptr;`
- L169 _protected member_ `const FSlateBrush* StopRecordingBrush = nullptr;`
- L170 _protected member_ `const FSlateBrush* StatusBarRecordingBrush = nullptr;`
- L171 _protected member_ `FSlateIcon RecordingSessionIcon;`
- L173 _protected member_ `const FLogCategoryBase& LogCategory;`
- L174 _protected member_ `FGuid DebuggerGuid;`
- L231 _private prototype_ `TSharedRef<SWidget> GenerateToggleRecordingStateButton(const FText& StartRecordingTooltip);`
- L232 _private prototype_ `TSharedRef<SWidget> GenerateRecordingTimeTextBlock();`
- L234 _private prototype_ `EVisibility GetRecordingTimeTextBlockVisibility() const;`
- L236 _private prototype_ `TSharedPtr<FSessionInfo> GetSessionInfo(FGuid Id) const;`
- L238 _private prototype_ `void HandleRemoteSessionsUpdated();`
- L240 _private prototype_ `const FSlateBrush* GetRecordOrStopButton() const;`
- L242 _private prototype_ `void HandleRecordingStop(const TSharedPtr<FSessionInfo>& InSessionInfo);`
- L243 _private prototype_ `void HandleRecordingStart(const TSharedPtr<FSessionInfo>& InSessionInfo);`
- L245 _private prototype_ `void ExecuteAsyncConnectionAttemptTaskWithRetry(FGuid SessionID, int32 RemainingRetries, const TFunction<bool()>& InRecordingStartAttemptCallback, const TFunction<void()>& InRecordingFailedCallback);`
- L247 _private prototype_ `static EVisibility IsRecordingToggleButtonVisible();`
- L249 _private prototype_ `FText GetRecordingTimeText() const;`
- L251 _private prototype_ `static TSharedPtr<SNotificationItem> PushConnectionAttemptNotification(const FNotificationInfo& InNotificationInfo);`
- L252 _private prototype_ `static void UpdateConnectionAttemptNotification(const TSharedPtr<SNotificationItem>& InNotification, int32 AttemptsRemaining);`
- L253 _private prototype_ `void HandleConnectionAttemptResult(FGuid SessionGUID, ELiveConnectionAttemptResult Result, const TSharedPtr<SNotificationItem>& InNotification);`
- L254 _private prototype_ `void CancelInFlightConnectionAttempt(const TSharedPtr<FSessionInfo>& SessionInfo);`
- L256 _private prototype_ `FText GetCurrentSelectedSessionName() const;`
- L258 _private member_ `FGuid CurrentSelectedSessionId = FGuid();`
- L260 _private member_ `FDelegateHandle RecordingStartedHandle;`
- L261 _private member_ `FDelegateHandle RecordingStoppedHandle;`
- L263 _private member_ `FCurveSequence RecordingAnimation;`
- L265 _private member_ `TMap<FGuid, TSharedPtr<FAsyncConnectionAttemptTask>> InFlightAsyncConnectionRequests;`
- L267 _private member_ `const FName StatusBarID;`
- L269 _private member_ `FStatusBarMessageHandle RecordingMessageHandle;`
- L270 _private member_ `FStatusBarMessageHandle RecordingPathMessageHandle;`
- L271 _private member_ `FStatusBarMessageHandle LiveSessionEndedMessageHandle;`
- L273 _private member_ `float IntervalBetweenAutoplayConnectionAttemptsSeconds = 1.0f;`
- L275 _private member_ `bool bInitialized = false;`
- L277 _private member_ `bool bRecordingButtonHovered = false;`
- L279 _private member_ `static constexpr int32 DefaultNumberOfConnectionRetries = 3;`

#### struct `UE::TraceBasedDebuggers::FRecordingControls::FAsyncConnectionAttemptTask`  
`struct FAsyncConnectionAttemptTask : public TSharedFromThis<FAsyncConnectionAttemptTask>`  
_L178-228_
- inherits: `TSharedFromThis<FAsyncConnectionAttemptTask>`
- L180 _public function_ `explicit FAsyncConnectionAttemptTask(const FGuid InSessionID , const FLogCategoryBase& LogCategory , const TFunction<bool()>& InRecordingStartAttemptCallback , const TFunction<void()>& InRecordingFailedCallback , const TWeakPtr<FRecordingControls>& RequestOwner ) : RecordingStartAttemptCallback(InRecordingStartAttemptCallback), RecordingFailedCallback(InRecordingFailedCallback), Owner(RequestOwner), SessionID(InSessionID), LogCategory(LogCategory)`
- L194 _public prototype_ `~FAsyncConnectionAttemptTask();`
- L205 _public prototype_ `void Cancel();`
- L207 _public prototype_ `void Start(int32 InMaxRetriesAttempts, float InIntervalBetweenAttemptsSeconds);`
- L208 _public prototype_ `void ScheduleRetry();`
- L209 _public prototype_ `void HandleSuccess();`
- L210 _public prototype_ `void HandleFailure();`
- L214 _private prototype_ `bool CanExecute() const;`
- L216 _private prototype_ `void Execute();`
- L218 _private member_ `TFunction<bool()> RecordingStartAttemptCallback;`
- L219 _private member_ `TSharedPtr<SNotificationItem> ProgressNotification;`
- L220 _private member_ `const TFunction<void()> RecordingFailedCallback;`
- L221 _private member_ `FTSTicker::FDelegateHandle RetryDelegateHandle;`
- L222 _private member_ `TWeakPtr<FRecordingControls> Owner;`
- L223 _private member_ `FGuid SessionID;`
- L224 _private member_ `const FLogCategoryBase& LogCategory;`
- L225 _private member_ `int32 RemainingRetries = 10;`
- L226 _private member_ `float IntervalBetweenAttemptsSeconds = 1.0f;`
- L227 _private member_ `EState State = EState::NotStarted;`

#### enum `UE::TraceBasedDebuggers::FRecordingControls::FAsyncConnectionAttemptTask::EState`  
`enum class EState : uint8`  
_L196-203_
- L198 _public enumerator_ `NotStarted`
- L199 _public enumerator_ `InProgress`
- L200 _public enumerator_ `Success`
- L201 _public enumerator_ `Canceled`
- L202 _public enumerator_ `Failed`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TRACEBASEDDEBUGGERSANALYSIS_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSessionEvent, const TSharedPtr<FSessionInfo>&) UENUM() enum class ELiveConnectionAttemptResult { Success, Failed, Canceled };`

### `Source/Runtime/Experimental/TraceBasedDebuggersAnalysis/Public/Widgets/SConnectionStatusBar.h` (Public)


#### class `UE::TraceBasedDebuggers::SConnectionStatusBar`  
`class SConnectionStatusBar : public SCompoundWidget`  
_L18-61_
- inherits: `SCompoundWidget`
- desc: Status Bar widget that provides information about active trace-based debugger connections
- L23 _public function_ `SLATE_BEGIN_ARGS(SConnectionStatusBar)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FGuid& InDebuggerGuid, const TSharedRef<FRemoteSessionsManager>& InRemoteSessionManager);`
- L32 _private prototype_ `const FSlateBrush* GetStateBackgroundIcon() const;`
- L33 _private prototype_ `FText GetTitleText() const;`
- L34 _private prototype_ `FText GetTitleToolTipText() const;`
- L35 _private prototype_ `FSlateColor GetDownloadIconColor() const;`
- L36 _private prototype_ `FSlateColor GetUploadingIconColor() const;`
- L37 _private prototype_ `FSlateColor GetWaitingIconColor() const;`
- L38 _private prototype_ `FSlateColor GetReadyIconColor() const;`
- L40 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L42 _private prototype_ `void UpdateConnectionStatus(double DeltaTime);`
- L44 _private member_ `double ElapsedTime = 0.0;`
- L45 _private member_ `double ElapsedTimeSinceLastUpdate = 0.0;`
- L54 _private member_ `TWeakPtr<FRemoteSessionsManager> RemoteSessionManagerWeakPtr;`
- L55 _private member_ `FGuid DebuggerGuid;`
- L56 _private member_ `EState State = EState::Ready;`
- L58 _private member_ `int64 CurrentPendingBytes = 0;`
- L59 _private member_ `uint64 CurrentReceivedDataBytesPerSecond = 0;`
- L60 _private member_ `uint64 CurrentTotalReceivedData = 0;`

#### enum `UE::TraceBasedDebuggers::SConnectionStatusBar::EState`  
`enum class EState`  
_L47-52_
- L49 _public enumerator_ `Ready`
- L50 _public enumerator_ `ReceivingData`
- L51 _public enumerator_ `WaitingForData`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TRACEBASEDDEBUGGERSANALYSIS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
