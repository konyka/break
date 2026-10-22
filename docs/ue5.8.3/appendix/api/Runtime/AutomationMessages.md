# Runtime / AutomationMessages

- module root: `Source/Runtime/AutomationMessages`
- headers: 1; symbols: 166
- symbol kinds: function=18, member=121, prototype=2, struct=25
- PrivateDependencyModuleNames: Core
- PublicDependencyModuleNames: AutomationTest, CoreUObject

### `Source/Runtime/AutomationMessages/Public/AutomationWorkerMessages.h` (Public)


#### struct `FAutomationWorkerMessageBase`  
`struct FAutomationWorkerMessageBase`  
_L15-23_
- reflection: `USTRUCT()`

#### struct `FAutomationWorkerFindWorkers`  
`struct FAutomationWorkerFindWorkers : public FAutomationWorkerMessageBase`  
_L32-62_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- desc: Implements a message that is published to find automation workers.
- L38 _public member_ `int32 Changelist;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the change list number to find workers for.
- L42 _public member_ `FString GameName;` — `UPROPERTY(EditAnywhere, Category="Message")` — The name of the game.
- L46 _public member_ `FString ProcessName;` — `UPROPERTY(EditAnywhere, Category="Message")` — The name of the process.
- L50 _public member_ `FGuid SessionId;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the session identifier to find workers for.
- L53 _public function_ `FAutomationWorkerFindWorkers() : Changelist(0)` — Default constructor.
- L56 _public function_ `FAutomationWorkerFindWorkers(int32 InChangelist, const FString& InGameName, const FString& InProcessName, const FGuid& InSessionId) : Changelist(InChangelist) , GameName(InGameName) , ProcessName(InProcessName) , SessionId(InSessionId)` — Creates and initializes a new instance.

#### struct `FAutomationWorkerFindWorkersResponse`  
`struct FAutomationWorkerFindWorkersResponse : public FAutomationWorkerMessageBase`  
_L69-119_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- desc: Implements a message that is sent in response to FAutomationWorkerFindWorkers.
- L75 _public member_ `FString DeviceName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the device that the worker is running on.
- L79 _public member_ `FString InstanceName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the worker's application instance.
- L83 _public member_ `FString Platform;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the platform that the worker is running on.
- L87 _public member_ `FString OSVersionName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the operating system version.
- L91 _public member_ `FString ModelName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the device model.
- L95 _public member_ `FString GPUName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the GPU.
- L99 _public member_ `FString CPUModelName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the CPU model.
- L103 _public member_ `uint32 RAMInGB;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the amount of RAM this device has in gigabytes.
- L107 _public member_ `FString RenderModeName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the current render mode.
- L111 _public member_ `FGuid SessionId;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the worker's application session identifier.
- L115 _public member_ `FString RHIName;` — `UPROPERTY(EditAnywhere, Category = "Message")` — Holds the name of the current RHI.
- L118 _public function_ `FAutomationWorkerFindWorkersResponse() : RAMInGB(0)` — Default constructor.

#### struct `FAutomationWorkerWorkerOffline`  
`struct FAutomationWorkerWorkerOffline : public FAutomationWorkerMessageBase`  
_L126-129_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- desc: Implements a message that notifies automation controllers that a worker went off-line.

#### struct `FAutomationWorkerPing`  
`struct FAutomationWorkerPing : public FAutomationWorkerMessageBase`  
_L135-138_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`

#### struct `FAutomationWorkerStartTestSession`  
`struct FAutomationWorkerStartTestSession : public FAutomationWorkerMessageBase`  
_L144-147_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`

#### struct `FAutomationWorkerStopTestSession`  
`struct FAutomationWorkerStopTestSession : public FAutomationWorkerMessageBase`  
_L153-156_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`

#### struct `FAutomationWorkerStopTests`  
`struct FAutomationWorkerStopTests : public FAutomationWorkerMessageBase`  
_L162-165_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`

#### struct `FAutomationWorkerPong`  
`struct FAutomationWorkerPong : public FAutomationWorkerMessageBase`  
_L171-174_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`

#### struct `FAutomationWorkerRequestTests`  
`struct FAutomationWorkerRequestTests : public FAutomationWorkerMessageBase`  
_L181-202_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- desc: Implements a message for requesting available automation tests from a worker.
- L187 _public member_ `bool DeveloperDirectoryIncluded = false;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds a flag indicating whether the developer directory should be included.
- L191 _public member_ `uint32 RequestedTestFlags = 0;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds a flag indicating which tests we'd like to request.
- L194 _public prototype_ `FAutomationWorkerRequestTests() = default;` — Default constructor.
- L197 _public function_ `FAutomationWorkerRequestTests(bool InDeveloperDirectoryIncluded, EAutomationTestFlags InRequestedTestFlags) : DeveloperDirectoryIncluded(InDeveloperDirectoryIncluded) , RequestedTestFlags((uint32)InRequestedTestFlags)` — Creates and initializes a new instance.

#### struct `FAutomationWorkerSingleTestReply`  
`struct FAutomationWorkerSingleTestReply : public FAutomationWorkerMessageBase`  
_L209-280_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- desc: A single test reply, used by FAutomationWorkerRequestTestsReplyComplete
- L214 _public member_ `FString DisplayName;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L217 _public member_ `FString FullTestPath;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L220 _public member_ `FString TestName;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L223 _public member_ `FString TestParameter;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L226 _public member_ `FString SourceFile;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L229 _public member_ `int32 SourceFileLine = 0;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L232 _public member_ `FString AssetPath;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L235 _public member_ `FString OpenCommand;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L238 _public member_ `uint32 TestFlags = 0;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L241 _public member_ `uint32 NumParticipantsRequired = 0;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L244 _public member_ `FString TestTags;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L247 _public prototype_ `FAutomationWorkerSingleTestReply() = default;` — Default constructor.
- L250 _public function_ `FAutomationWorkerSingleTestReply(const FAutomationTestInfo& InTestInfo)` — Creates and initializes a new instance.
- L265 _public function_ `FAutomationTestInfo GetTestInfo() const`

#### struct `FAutomationWorkerRequestTestsReplyComplete`  
`struct FAutomationWorkerRequestTestsReplyComplete : public FAutomationWorkerMessageBase`  
_L287-293_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- desc: Returns list of all tests
- L292 _public member_ `TArray<FAutomationWorkerSingleTestReply> Tests;` — `UPROPERTY(EditAnywhere, Category = "Message")`

#### struct `FAutomationWorkerRunTests`  
`struct FAutomationWorkerRunTests : public FAutomationWorkerMessageBase`  
_L300-345_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- desc: Implements a message to request the running of automation tests on a worker.
- L306 _public member_ `uint32 ExecutionCount;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L310 _public member_ `int32 RoleIndex;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L314 _public member_ `FString TestName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the test to run.
- L318 _public member_ `FString BeautifiedTestName;` — `UPROPERTY()` — Holds the name of the test to run.
- L322 _public member_ `FString FullTestPath;` — `UPROPERTY()` — Holds the full test path of the test to run.
- L326 _public member_ `bool bSendAnalytics;` — `UPROPERTY()` — If true, send results to analytics when complete
- L330 _public member_ `bool bPruneLogsOnSuccess;` — `UPROPERTY()` — If true, prune log events from test report on success
- L333 _public function_ `FAutomationWorkerRunTests( ) :ExecutionCount(0), RoleIndex(0), bSendAnalytics(false), bPruneLogsOnSuccess(false)` — Default constructor.
- L336 _public function_ `FAutomationWorkerRunTests( uint32 InExecutionCount, int32 InRoleIndex, FString InTestName, FString InBeautifiedTestName, FString InFullTestPath, bool InSendAnalytics, bool InPruneLogsOnSuccess) : ExecutionCount(InExecutionCount) , RoleIndex(InRoleIndex) , TestName(InTestName) , BeautifiedTestName(InBeautifiedTestName) , FullTestPath(InFullTestPath) , bSendAnalytics(InSendAnalytics) , bPruneLogsOnSuccess(InPruneLogsOnSuccess)` — Creates and initializes a new instance.

#### struct `FAutomationWorkerRunTestsReply`  
`struct FAutomationWorkerRunTestsReply : public FAutomationWorkerMessageBase`  
_L352-382_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- desc: Implements a message that is sent in response to FAutomationWorkerRunTests.
- L359 _public member_ `FString TestName;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L363 _public member_ `TArray<FAutomationExecutionEntry> Entries;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L366 _public member_ `int32 WarningTotal = 0;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L369 _public member_ `int32 ErrorTotal = 0;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L373 _public member_ `float Duration = 0;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L377 _public member_ `uint32 ExecutionCount = 0;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L381 _public member_ `EAutomationState State = EAutomationState::NotRun;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FAutomationWorkerRequestNextNetworkCommand`  
`struct FAutomationWorkerRequestNextNetworkCommand : public FAutomationWorkerMessageBase`  
_L388-403_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- L394 _public member_ `uint32 ExecutionCount;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L397 _public function_ `FAutomationWorkerRequestNextNetworkCommand() : ExecutionCount(0)` — Default constructor.
- L400 _public function_ `FAutomationWorkerRequestNextNetworkCommand(uint32 InExecutionCount) : ExecutionCount(InExecutionCount)` — Creates and initializes a new instance.

#### struct `FAutomationWorkerNextNetworkCommandReply`  
`struct FAutomationWorkerNextNetworkCommandReply : public FAutomationWorkerMessageBase`  
_L409-412_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`

#### struct `FAutomationScreenshotMetadata`  
`struct FAutomationScreenshotMetadata`  
_L416-728_
- reflection: `USTRUCT()`
- L423 _public member_ `FString ScreenShotName;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L426 _public member_ `FString VariantName;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L429 _public member_ `FString Context;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L432 _public member_ `FString TestName;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L435 _public member_ `FString Notes;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L438 _public member_ `FGuid Id;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L440 _public member_ `FString Commit;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L443 _public member_ `int32 Width;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L445 _public member_ `int32 Height;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L449 _public member_ `FString Rhi;` — `UPROPERTY(EditAnywhere, Category="Message")` — RHI Details
- L451 _public member_ `FString Platform;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L453 _public member_ `FString FeatureLevel;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L455 _public member_ `bool bIsStereo;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L459 _public member_ `bool bIsSubstrate;` — `UPROPERTY(EditAnywhere, Category="Message")` — Track if ScreenShotMetadata was created with Substrate enabled or not
- L463 _public member_ `FString Vendor;` — `UPROPERTY(EditAnywhere, Category="Message")` — Hardware Details
- L465 _public member_ `FString AdapterName;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L467 _public member_ `FString AdapterInternalDriverVersion;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L469 _public member_ `FString AdapterUserDriverVersion;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L471 _public member_ `FString UniqueDeviceId;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L475 _public member_ `float ResolutionQuality;` — `UPROPERTY(EditAnywhere, Category="Message")` — Quality Levels
- L477 _public member_ `int32 ViewDistanceQuality;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L479 _public member_ `int32 AntiAliasingQuality;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L481 _public member_ `int32 ShadowQuality;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L483 _public member_ `int32 GlobalIlluminationQuality;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L485 _public member_ `int32 ReflectionQuality;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L487 _public member_ `int32 PostProcessQuality;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L489 _public member_ `int32 TextureQuality;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L491 _public member_ `int32 EffectsQuality;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L493 _public member_ `int32 FoliageQuality;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L495 _public member_ `int32 ShadingQuality;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L499 _public member_ `bool bHasComparisonRules;` — `UPROPERTY(EditAnywhere, Category="Message")` — Comparison Requests
- L501 _public member_ `uint8 ToleranceRed;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L503 _public member_ `uint8 ToleranceGreen;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L505 _public member_ `uint8 ToleranceBlue;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L507 _public member_ `uint8 ToleranceAlpha;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L509 _public member_ `uint8 ToleranceMinBrightness;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L511 _public member_ `uint8 ToleranceMaxBrightness;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L513 _public member_ `float MaximumLocalError;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L515 _public member_ `float MaximumGlobalError;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L517 _public member_ `bool bIgnoreAntiAliasing;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L519 _public member_ `bool bIgnoreColors;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L523 _public function_ `FAutomationScreenshotMetadata() : Width(0) , Height(0) , bIsStereo(false) , bIsSubstrate(false) , ResolutionQuality(0.0f) , ViewDistanceQuality(0) , AntiAliasingQuality(0) , ShadowQuality(0) , GlobalIlluminationQuality(0) , ReflectionQuality(0) , PostProcessQuality(0) , TextureQuality(0) , EffectsQuality(0) , FoliageQuality(0) , ShadingQuality(0) , bHasComparisonRules(0) , ToleranceRed(0) , ToleranceGreen(0) , ToleranceBlue(0) , ToleranceAlpha(0) , ToleranceMinBrightness(0) , ToleranceMaxBrightness(0) , MaximumLocalError(0.0f) , MaximumGlobalError(0.0f) , bIgnoreAntiAliasing(false) , bIgnoreColors(false)`
- L553 _public function_ `FAutomationScreenshotMetadata(const FAutomationScreenshotData& Data)`
- L618 _public function_ `int32 Compare(const FAutomationScreenshotMetadata& OtherMetadata) const`

#### struct `FAutomationWorkerScreenImage`  
`struct FAutomationWorkerScreenImage : public FAutomationWorkerMessageBase`  
_L734-752_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- desc: Implements a message that is sent in containing a screen shot run during performance test.
- L740 _public member_ `TArray<uint8> ScreenImage;` — `UPROPERTY(EditAnywhere, Category="Message")` — The screen shot data.
- L744 _public member_ `TArray<uint8> FrameTrace;` — `UPROPERTY(EditAnywhere, Category = "Message")` — The frame trace data.
- L748 _public member_ `FString ScreenShotName;` — `UPROPERTY(EditAnywhere, Category="Message")` — The screen shot name.
- L751 _public member_ `FAutomationScreenshotMetadata Metadata;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FAutomationWorkerImageComparisonResults`  
`struct FAutomationWorkerImageComparisonResults : public FAutomationWorkerMessageBase`  
_L760-840_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- desc: Implements a message that is sent in containing a screen shot run during performance test.
- L766 _public function_ `FAutomationWorkerImageComparisonResults(FGuid InInstanceId = FGuid{}) : FAutomationWorkerMessageBase`
- L775 _public function_ `FAutomationWorkerImageComparisonResults( FGuid InInstanceId, FGuid InUniqueId, const FString& InScreenshotPath, bool InIsNew, bool InAreSimilar, double InMaxLocalDifference, double InGlobalDifference, const FString& InErrorMessage, const FString& InIncomingFilePath, const FString& InReportComparisonFilePath, const FString& InReportApprovedFilePath, const FString& InReportIncomingFilePath ) : FAutomationWorkerMessageBase`
- L806 _public member_ `FGuid UniqueId;` — `UPROPERTY(EditAnywhere, Category="Message")` — The unique id for the comparison.
- L810 _public member_ `FString ScreenshotPath;` — `UPROPERTY(EditAnywhere, Category = "Message")` — The path of the screenshot.
- L814 _public member_ `bool bNew;` — `UPROPERTY(EditAnywhere, Category="Message")` — Was this a new image we've never seen before and have no ground truth for?
- L818 _public member_ `bool bSimilar;` — `UPROPERTY(EditAnywhere, Category="Message")` — Were the images similar?  If they're not you should log an error.
- L821 _public member_ `double MaxLocalDifference;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L824 _public member_ `double GlobalDifference;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L827 _public member_ `FString ErrorMessage;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L830 _public member_ `FString IncomingFilePath;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L833 _public member_ `FString ReportComparisonFilePath;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L836 _public member_ `FString ReportApprovedFilePath;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L839 _public member_ `FString ReportIncomingFilePath;` — `UPROPERTY(EditAnywhere, Category = "Message")`

#### struct `FAutomationWorkerTestDataRequest`  
`struct FAutomationWorkerTestDataRequest : public FAutomationWorkerMessageBase`  
_L848-871_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- desc: Implements a message that handles both storing and requesting ground truth data. for the first time this test is run, it might need to store things, or get things.
- L854 _public member_ `FString DataType;` — `UPROPERTY(EditAnywhere, Category="Message")` — The category of the data, this is purely to bucket and separate the ground truth data we store into different directories.
- L858 _public member_ `FString DataPlatform;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L862 _public member_ `FString DataTestName;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L866 _public member_ `FString DataName;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L870 _public member_ `FString JsonData;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FAutomationWorkerTestDataResponse`  
`struct FAutomationWorkerTestDataResponse : public FAutomationWorkerMessageBase`  
_L877-887_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- desc: Implements a message that responds to TestDataRequests.
- L883 _public member_ `FString JsonData;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L886 _public member_ `bool bIsNew = false;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FAutomationWorkerPerformanceDataRequest`  
`struct FAutomationWorkerPerformanceDataRequest : public FAutomationWorkerMessageBase`  
_L893-912_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- desc: Implements a message to request the performance data for this hardware.
- L899 _public member_ `FString Platform;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L903 _public member_ `FString Hardware;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L907 _public member_ `FString TestName;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L911 _public member_ `TArray<double> DataPoints;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FAutomationWorkerPerformanceDataResponse`  
`struct FAutomationWorkerPerformanceDataResponse : public FAutomationWorkerMessageBase`  
_L918-929_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- desc: Implements a message that responds to PerformanceDataRequest.
- L924 _public member_ `bool bSuccess = false;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L928 _public member_ `FString ErrorMessage;` — `UPROPERTY(EditAnywhere, Category="Message")`

#### struct `FAutomationWorkerTelemetryItem`  
`struct FAutomationWorkerTelemetryItem : public FAutomationWorkerMessageBase`  
_L935-966_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- desc: Implements a message that contains telemetry data point.
- L941 _public member_ `FString DataPoint;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L945 _public member_ `double Measurement;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L949 _public member_ `FString Context;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L951 _public function_ `FAutomationWorkerTelemetryItem() : Measurement(0.0)`
- L953 _public function_ `FAutomationWorkerTelemetryItem(FString& InDataPoint, double InMeasurement, FString& InContext) : DataPoint(InDataPoint) , Measurement(InMeasurement) , Context(InContext)`
- L960 _public function_ `FAutomationWorkerTelemetryItem(const FAutomationTelemetryData& InItem) : DataPoint(InItem.DataPoint) , Measurement(InItem.Measurement) , Context(InItem.Context)`

#### struct `FAutomationWorkerTelemetryData`  
`struct FAutomationWorkerTelemetryData : public FAutomationWorkerMessageBase`  
_L972-995_
- reflection: `USTRUCT()`
- inherits: `FAutomationWorkerMessageBase`
- desc: Implements a message that contains telemetry data.
- L978 _public member_ `FString Storage;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L982 _public member_ `FString Configuration;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L986 _public member_ `FString Platform;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L990 _public member_ `FString TestName;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L994 _public member_ `TArray<FAutomationWorkerTelemetryItem> Items;` — `UPROPERTY(EditAnywhere, Category = "Message")`
