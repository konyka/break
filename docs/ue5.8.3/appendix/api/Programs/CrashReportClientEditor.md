# Programs / CrashReportClientEditor

- module root: `Source/Programs/CrashReportClient`
- headers: 8; symbols: 151
- symbol kinds: class=7, delegate=1, enum=1, enumerator=3, function=11, macro=2, member=45, namespace=1, prototype=78, struct=2
- DynamicallyLoadedModuleNames: ConcertSyncServer, UdpMessaging
- PrivateDependencyModuleNames: Concert, EditorAnalyticsSession, Messaging
- PrivateIncludePathModuleNames: ConcertSyncCore, ConcertSyncServer

### `Source/Programs/CrashReportClient/Private/CrashReportAnalyticsSessionSummary.h` (Private)


#### class `FCrashReportAnalyticsSessionSummary`  
`class FCrashReportAnalyticsSessionSummary : public FOutputDevice`  
_L25-159_
- inherits: `FOutputDevice`
- desc: Creates a summary of CRC session for analytics purpose. The summary should be merged with the monitored application one.
- L29 _public prototype_ `static FCrashReportAnalyticsSessionSummary& Get();` — Return the summary instance.
- L32 _public prototype_ `void Initialize(const FString& ProcessGroupId, uint32 ForProcessId);` — Initialize the summary. The implementation do nothing unless the instance is successfully initialized.
- L35 _public prototype_ `void Shutdown(IAnalyticsProviderET* AnalyticsProvider = nullptr, TFunction<void()> HandleAbnormalShutdownFn = TFunction<void()>());` — Shuts down and submits the summary if a non-null provider is specified and invoke HandleAbnormalShutdownFn if bound and an abnormal shutdown was detected.
- L38 _public prototype_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override;`
- L39 _public prototype_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category, const double Time) override;`
- L40 _public prototype_ `virtual bool CanBeUsedOnAnyThread() const override;`
- L41 _public prototype_ `virtual bool CanBeUsedOnMultipleThreads() const override;`
- L42 _public prototype_ `virtual bool CanBeUsedOnPanicThread() const override;`
- L45 _public prototype_ `void LogEvent(const TCHAR* Event, bool bForwardToUELog = true);` — Logs an events in the analytics session summary diagnostic log. The event text is expected to be short and concise.
- L48 _public prototype_ `void LogEvent(const FString& Event);` — Logs an events in the analytics session summary diagnostic log. The event text is expected to be short and concise.
- L51 _public prototype_ `void OnMonitoredAppDeath(FProcHandle& Handle);` — Invoked when monitored application death was detected.
- L54 _public prototype_ `void OnCrcCrashing(int32 ExceptCode);` — Invoked by the unhandled exception handler while CRC is crashing.
- L57 _public prototype_ `void OnUserLoggingOut();` — Invoked when the user is logging out. This is also called if the computer is shutting down or restarting.
- L60 _public prototype_ `void OnQuitSignal();` — Invoked when the system gently signal CRC to quit.
- L63 _public prototype_ `void OnCrashReportStarted(ECrashContextType Type, const TCHAR* ErrorMsg);` — Invoked when CRC starts to process a crash/ensure/stall.
- L66 _public prototype_ `void OnCrashReportCollecting();` — Invoked when CRC starts collecting the crash artifacts.
- L69 _public prototype_ `void OnCrashReportRemoteStackWalking();` — Invoked when CRC starts stack-walking the crash.
- L72 _public prototype_ `void OnCrashReportGatheringFiles();` — Invoked when CRC starts collecting crash artifacts such as the log/minidump/etc.
- L75 _public prototype_ `void OnCrashReportSignalingAppToResume();` — Invoked when CRC finished collecting crash artifacts and replies to the monitored app.
- L78 _public prototype_ `void OnCrashReportProcessing(bool bUserInteractive);` — Invoked when CRC starts the process to submit the crash report (this also includes showing the dialog to user in needed.
- L81 _public prototype_ `void OnCrashReportCompleted(bool bSubmitted);` — Invoked when CRC finished handling a crash report and resume its main loop.
- L85 _private function_ `static bool IsEnabled()` — Returns whether the analytics summary is enabled or not.
- L88 _private prototype_ `bool IsValid() const;` — Returns true if the analytics session summary is valid.
- L91 _private prototype_ `FCrashReportAnalyticsSessionSummary();` — Creates the summary sessions.
- L94 _private prototype_ `void AppendLog(const TCHAR* Event);` — Appends a log entry to the log buffer, rotate the buffer if full and flush it to file.
- L97 _private prototype_ `void Flush();` — Flush CRC analytics summary file to disk.
- L100 _private prototype_ `void OnApplicationWillTerminate();` — Invoked by the core when the application is about to terminate.
- L103 _private prototype_ `void OnHandleSystemError();` — Invoked by the core when a system error is detected, like fatal logs.
- L106 _private prototype_ `bool UpdatePowerStatus();` — Invoked periodically by the monitoring thread to update the power status (Battery/AC Power).
- L110 _private member_ `FCriticalSection LoggerLock;` — Serialize access to the diagnostic logs.
- L113 _private member_ `TSharedPtr<IAnalyticsPropertyStore> PropertyStore;` — The CRC session summary store.
- L116 _private member_ `TUniquePtr<FAnalyticsSessionSummaryManager> SessionSummaryManager;` — The session summary manager.
- L119 _private member_ `FString DiagnosticLog;` — Contains the rotating diagnostic log entries.
- L122 _private member_ `TUniquePtr<FThread> AnalyticsThread;` — Runs in background to collect CRC analytics because the main thread might be busy handling a crash and important event could be missed.
- L125 _private member_ `double SessionStartTimeSecs;` — The CRC startup time, i.e. when the summary is successfully initialized.
- L128 _private member_ `double CrashReportStartTimeSecs = 0.0;` — Time at which the last crash report started.
- L131 _private member_ `double CrashReportCollectingStartTimeSecs = 0.0;` — Time at which collecting the artifacts of the last crash started.
- L134 _private member_ `double CrashReportStackWalkingStartTimeSecs = 0.0;` — Time at which remote stack-walking started.
- L137 _private member_ `double CrashReportGatheringFilesStartTimeSecs = 0.0;` — Time at which gathering crash files (logs, minidump, etct) started.
- L140 _private member_ `double CrashReportSignalingRemoteAppTimeSecs = 0.0;` — Time at which CRC signaled the application to resume.
- L143 _private member_ `double CrashReportProcessingStartTimeSecs = 0.0;` — Time at which processing the last crash started.
- L146 _private member_ `bool bProcessingCrashUnattended = false;` — Whether the crash being processed unattended.
- L149 _private member_ `bool bLoggerReentrantGuard = false;` — Prevent a reentrency in the diagnostic logger.
- L152 _private member_ `bool bIsValid = false;` — Flag if the session is usable.
- L155 _private member_ `std::atomic<bool> bMonitoredAppDeathRecorded;` — Indicates whether the monitored application death is reported.
- L158 _private member_ `std::atomic<bool> bShutdown;` — Used to signal the analytics thread to exit.

#### Free symbols / members of external scopes

- L19 _prototype_ `FProcHandle OpenProcessForMonitoring(uint32 pid);` — Open the monitored process with restricted permissions, for security reasons.

### `Source/Programs/CrashReportClient/Private/CrashReportClient.h` (Private)


#### class `FDiagnoseReportWorker`  
`class FDiagnoseReportWorker : public FNonAbandonableTask`  
_L28-54_
- inherits: `FNonAbandonableTask`
- desc: Helper task class to process a crash report in the background
- L32 _public member_ `FCrashReportClient* CrashReportClient;` — Pointer to the crash report client, used to store the results.
- L35 _public prototype_ `FDiagnoseReportWorker( FCrashReportClient* InCrashReportClient );` — Initialization constructor.
- L40 _public prototype_ `void DoWork();` — Do platform-specific work to get information about the crash.
- L42 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L50 _public function_ `static const TCHAR* Name()` — @return The name to display in external event viewers

#### class `FCrashReportClient`  
`class FCrashReportClient : public TSharedFromThis<FCrashReportClient>`  
_L59-223_
- inherits: `TSharedFromThis<FCrashReportClient>`
- desc: Main implementation of the crash report client application
- L68 _public prototype_ `FCrashReportClient( const FPlatformErrorReport& InErrorReport, bool bImplicitSend );` — Constructor: sets up background diagnosis @param ErrorReport Error report to upload
- L71 _public prototype_ `virtual ~FCrashReportClient();` — Destructor.
- L74 _public prototype_ `void StopBackgroundThread();` — Stops processing work in the background.
- L77 _public prototype_ `FReply CloseWithoutSending();` — Closes the crash report client without sending any data. Except the startup analytics.
- L80 _public prototype_ `FReply Close();` — Closes the crash report client allowing data to finish being sent.
- L84 _public prototype_ `FReply CopyFilesToClipboard();` — Copy report files to the clipboard for user to immediately request help with.
- L91 _public prototype_ `FReply Submit(bool bIncludeOptionalAttachments = false);` — Respond to the user pressing Submit @return Whether the request was handled
- L97 _public prototype_ `FReply SubmitOptionalAttachmentsAndClose();` — Respond to the user pressing Submit for optional attachments @return Whether the request was handled
- L103 _public prototype_ `FReply SubmitAndRestart();` — Respond to the user pressing Submit and Restart @return Whether the request was handled
- L109 _public prototype_ `FReply CopyCallstack();` — Respond to the user requesting the callstack to be copied to the clipboard @return Whether the request was handled
- L115 _public prototype_ `FText GetDiagnosticText() const;` — Pass on exception and callstack from the platform error report code @return Localized text to display
- L120 _public prototype_ `FString GetCrashDirectory() const;` — @return the full path of the crash directory.
- L127 _public prototype_ `void UserCommentChanged(const FText& Comment, ETextCommit::Type CommitType);` — Handle the user updating the user comment text @param Comment Text provided by the user @param CommitType Event that caused this update
- L133 _public prototype_ `void RequestCloseWindow(const TSharedRef<SWindow>& Window);` — Handle user closing the main window @param Window Main window
- L136 _public function_ `bool ShouldWindowBeHidden() const` — Whether the main window should be hidden.
- L142 _public prototype_ `bool AreCallstackWidgetsEnabled() const;` — Whether the app should enable widgets related to the displayed callstack.
- L145 _public prototype_ `EVisibility IsThrobberVisible() const;` — Whether the throbber should be visible while processing the callstack.
- L148 _public function_ `bool GetIsSuccesfullRestart() const` — Returns true if user has elected to restart crashing process, and if it was a success
- L151 _public function_ `bool WasClosedWithoutSending() const` — Retruns true if user has elected to close without sending the report.
- L153 _public prototype_ `void AllowToBeContacted_OnCheckStateChanged( ECheckBoxState NewRadioState );`
- L154 _public prototype_ `void SendLogFile_OnCheckStateChanged( ECheckBoxState NewRadioState );`
- L156 _public function_ `bool IsUploadComplete() const`
- L162 _private prototype_ `void StoreCommentAndUpload();` — Write the user's comment to the report and begin uploading the entire report
- L169 _private prototype_ `bool Tick(float DeltaTime);` — Update received every second @param DeltaTime Time since last update, unused @return Whether the updates should continue
- L174 _private prototype_ `void StartTicker();` — Begin calling Tick once a second
- L177 _private prototype_ `void FinalizeDiagnoseReportWorker();` — Enqueued from the diagnose report worker thread to be executed on the game thread.
- L182 _private prototype_ `bool IsProcessingCallstack() const;` — @return true if we are still processing a callstack
- L185 _private member_ `FText UserComment;` — Comment provided by the user
- L188 _private member_ `FText DiagnosticText;` — Exception and call-stack to show, valid once diagnosis task is complete
- L191 _private member_ `FText FormattedDiagnosticText;` — Formatted diagnostics crash reporter data.
- L194 _private member_ `FAsyncTask<FDiagnoseReportWorker>* DiagnoseReportTask;` — Background worker to get a callstack from the report
- L197 _private member_ `FPlatformErrorReport ErrorReport;` — Platform code for accessing the report
- L200 _private member_ `FCrashUploadToReceiver ReceiverUploader;` — Object that uploads report files to the server
- L203 _private member_ `FCrashUploadToDataRouter DataRouterUploader;` — Object that uploads report files to the server
- L206 _private member_ `bool bShouldWindowBeHidden;` — Whether the main window should be hidden.
- L209 _private member_ `bool bSendData;` — Whether we send the data.
- L212 _private member_ `bool bSendOptionalAttachments;` — Whether to send optional attachments, after the base crash report has been successfully sent.
- L215 _private member_ `bool bIsSuccesfullRestart;` — Store if user has elected to restart crashing process, and if it was a success.
- L218 _private member_ `bool bIsUploadComplete;` — Is the uploading complete.
- L221 _private member_ `FTSTicker::FDelegateHandle TickHandle;` — To know if the ticker was started.

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(CrashReportClientLog, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(CrashReportClientLog, Log, All);`

### `Source/Programs/CrashReportClient/Private/CrashReportClientDefines.h` (Private)


#### Free symbols / members of external scopes

- L6 _macro_ `#define CRASH_REPORT_WITH_RECOVERY 0`
- L10 _macro_ `#define CRASH_REPORT_WITH_MTBF 0`

### `Source/Programs/CrashReportClient/Private/CrashReportClientStyle.h` (Private)


#### struct `FCrashReportClientStyleOptions`  
`struct FCrashReportClientStyleOptions`  
_L12-17_
- L16 _public member_ `} OptionalCrashScreenshot;`

#### struct `FCrashReportClientStyleOptions::(anonymous)`  
`struct`  
_L13-16_

#### class `FCrashReportClientStyle`  
`class FCrashReportClientStyle`  
_L20-43_
- desc: Slate styles for the crash report client app
- L26 _public prototype_ `static void Initialize(const FCrashReportClientStyleOptions& Options);` — Set up specific styles for the crash report client app
- L31 _public prototype_ `static void Shutdown();` — Tidy up on shut-down
- L36 _public prototype_ `static const ISlateStyle& Get();` — Access to singleton style object
- L39 _private prototype_ `static TSharedRef<FSlateStyleSet> Create(const FCrashReportClientStyleOptions& Options);`
- L42 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;` — Singleton style object

#### Free symbols / members of external scopes

- L14 _member_ `FString Filepath;` (scope `FCrashReportClientStyleOptions::__anon3a0d9f880108`)
- L15 _member_ `FVector2D ImageSize = { 0,0 };` (scope `FCrashReportClientStyleOptions::__anon3a0d9f880108`)

### `Source/Programs/CrashReportClient/Private/MainLoopTiming.h` (Private)


#### enum `EMainLoopOptions::Type`  
`enum Type`  
_L10-20_
- L13 _public enumerator_ `CoreTickerOnly = 0` — No flags set: only update the core ticker
- L16 _public enumerator_ `UsingSlate = 0x01` — Call Tick on Slate
- L19 _public enumerator_ `Default = UsingSlate` — Default to running Slate if no options passed

#### class `FMainLoopTiming`  
`class FMainLoopTiming`  
_L26-45_
- desc: Calls Tick on Slate and the core ticker at a set rate
- L32 _public prototype_ `explicit FMainLoopTiming(float IdealTickRate, EMainLoopOptions::Type Options = EMainLoopOptions::Default);` — Constructor: set up initial timing values
- L37 _public prototype_ `void Tick();` — Tick core application objects and throttle rate as requested in constructor
- L41 _private member_ `float IdealFrameTime;` — Interval between each Tick that we're aiming for
- L44 _private member_ `bool bTickSlate;` — Should Slate's Tick be called?

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace EMainLoopOptions`

### `Source/Programs/CrashReportClient/Private/RecoveryService.h` (Private)


#### class `FRecoveryService`  
`class FRecoveryService`  
_L13-33_
- desc: Manage the life time of the Disaster recovery service.
- L16 _public function_ `FRecoveryService(uint64 InClientPid) : MonitorPid(InClientPid)`
- L17 _public function_ `~FRecoveryService()`
- L20 _public prototype_ `bool CollectFiles(const FString& DestDir, bool bMetaDataOnly = true, bool bAnonymizeMetaData = false);` — Collects the session files.
- L23 _private prototype_ `bool Startup();`
- L24 _private prototype_ `void Shutdown();`
- L26 _private prototype_ `FString GetRecoveryServiceWorkingDir() const;`
- L27 _private prototype_ `FString GetRecoveryServiceArchivedDir() const;`
- L28 _private prototype_ `FGuid GetRecoverySessionId() const;`
- L31 _private member_ `TSharedPtr<IConcertSyncServer> Server;`
- L32 _private member_ `uint64 MonitorPid = 0;`

### `Source/Programs/CrashReportClient/Private/SCrashReportClient.h` (Private)


#### class `SCrashReportClient`  
`class SCrashReportClient : public SCompoundWidget`  
_L16-92_
- inherits: `SCompoundWidget`
- desc: UI for the crash report client app
- L22 _public function_ `SLATE_BEGIN_ARGS(SCrashReportClient) : _bHideSubmitAndRestart(false)` — Slate arguments
- L28 _public prototype_ `SLATE_ARGUMENT(bool, bHideSubmitAndRestart) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FCrashReportClient>& Client, bool bSimpleDialog);` — Should the Submit and Send button be hitten. This can be overriden by a platform settings in the crash report config ini file.
- L40 _public function_ `bool IsFinished()`
- L47 _private prototype_ `void ConstructDetailedDialog(const TSharedRef<FCrashReportClient>& Client, const FText& CrashDetailedMessage);` — Construct the detailed Slate ui with controls for sending the report and comments @param Client Crash report client implementation object
- L53 _private prototype_ `void ConstructSimpleDialog(const TSharedRef<FCrashReportClient>& Client, const FText& CrashDetailedMessage);` — Construct the minimal Slate ui with just a button to close @param Client Crash report client implementation object
- L60 _private prototype_ `FReply OnUnhandledKeyDown(const FKeyEvent& InKeyEvent);` — Keyboard short-cut handler @param InKeyEvent Which key was released, and which auxiliary keys were pressed @return Whether the event was handled
- L63 _private prototype_ `void OnUserCommentTextChanged(const FText& NewText);` — Called if the multi line widget text changes
- L66 _private prototype_ `EVisibility IsHintTextVisible() const;` — Whether the hint text should be visible.
- L69 _private prototype_ `bool IsSendEnabled() const;` — Whether the send buttons are enabled.
- L72 _private prototype_ `static FText GetSendTooltip();` — Returns the tooltop text for send button
- L75 _private prototype_ `static FText GetContactText();` — Returns the 'allow contact' text
- L79 _private prototype_ `bool IsCopyToClipboardEnabled() const;` — Whether the copy to clipboard button is available.
- L83 _private member_ `TSharedPtr<FCrashReportClient> CrashReportClient;` — Crash report client implementation object
- L85 _private member_ `TSharedPtr<SMultiLineEditableTextBox> CrashDetailsInformation;`
- L87 _private member_ `bool bIsUserCommentEmpty;`
- L88 _private member_ `bool bHasUserCommentErrors;`
- L89 _private member_ `bool bHideSubmitAndRestart;`
- L91 _private member_ `bool bIncludeScreenshotInCrashReport = false;`

### `Source/Programs/CrashReportClient/Public/CrashReportClientApp.h` (Public)


#### Free symbols / members of external scopes

- L17 _prototype_ `void RunCrashReportClient(const TCHAR* Commandline);` — Run the crash report client app
