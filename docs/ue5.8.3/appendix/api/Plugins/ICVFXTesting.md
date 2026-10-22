# Plugins / ICVFXTesting

- module root: `Plugins/VirtualProduction/ICVFXTesting/Source/ICVFXTesting`
- headers: 3; symbols: 93
- symbol kinds: class=4, delegate=1, enum=1, enumerator=6, function=11, member=24, prototype=45, typedef=1
- PrivateDependencyModuleNames: CinematicCamera, DisplayCluster, Engine, LiveLink, LiveLinkComponents, LiveLinkInterface, RenderCore
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Gauntlet

### `Plugins/VirtualProduction/ICVFXTesting/Source/ICVFXTesting/Public/ICVFXTestControllerAutoTest.h` (Public)


#### enum `EICVFXAutoTestState`  
`enum class EICVFXAutoTestState : uint8`  
_L26-35_
- reflection: `UENUM()`
- L28 _public enumerator_ `InitialLoad`
- L29 _public enumerator_ `Soak`
- L30 _public enumerator_ `TraverseTestLocations`
- L31 _public enumerator_ `Finished`
- L32 _public enumerator_ `Shutdown`
- L34 _public enumerator_ `MAX`

#### class `FICVFXAutoTestState`  
`class FICVFXAutoTestState`  
_L37-60_
- L40 _public typedef_ `using Super = FICVFXAutoTestState;`
- L42 _public prototype_ `FICVFXAutoTestState() = delete;`
- L43 _public function_ `FICVFXAutoTestState(class UICVFXTestControllerAutoTest* const TestController) : Controller(TestController)`
- L44 _public function_ `virtual ~FICVFXAutoTestState()`
- L46 _public prototype_ `virtual void Start(const EICVFXAutoTestState PrevState);`
- L47 _public function_ `virtual void End(const EICVFXAutoTestState NewState)`
- L48 _public prototype_ `virtual void Tick(const float TimeDelta);`
- L50 _public function_ `double GetTestStateTime() const`
- L56 _protected member_ `class UICVFXTestControllerAutoTest* Controller;`
- L59 _private member_ `double TimeSinceStart = 0.0;`

#### class `UICVFXTestControllerAutoTest`  
`class UICVFXTestControllerAutoTest : public UICVFXTestControllerBase`  
_L63-148_
- reflection: `UCLASS()`
- inherits: `UICVFXTestControllerBase`
- L68 _public prototype_ `FString GetStateName(const EICVFXAutoTestState State) const;`
- L69 _public prototype_ `FICVFXAutoTestState& GetTestState() const;`
- L70 _public prototype_ `FICVFXAutoTestState& SetTestState(const EICVFXAutoTestState NewState);`
- L71 _public prototype_ `void SetTestLocations(const TArray<AActor*> TestLocations);`
- L72 _public prototype_ `virtual void EndICVFXTest(const int32 ExitCode=0) override;`
- L74 _public function_ `double GetCurrentStateTime() const`
- L79 _public function_ `int32 GetCurrentTestLocationIndex() const`
- L84 _public prototype_ `void GoToTestLocation(int32 Index);`
- L86 _public function_ `void GoToNextTestLocation()`
- L92 _public function_ `int32 NumTestLocations() const`
- L97 _public function_ `void SetInnerGPUIndex(int32 InGPUIndex)`
- L102 _public function_ `int32 GetInnerGPUIndex() const`
- L107 _public prototype_ `void InitializeLiveLink();`
- L108 _public prototype_ `void UpdateInnerGPUIndex();`
- L109 _public prototype_ `void UpdateTestLocations();`
- L112 _protected prototype_ `virtual void OnInit() override;`
- L113 _protected prototype_ `virtual void OnPreMapChange() override;`
- L114 _protected prototype_ `virtual void OnTick(float TimeDelta) override;`
- L115 _protected prototype_ `virtual void BeginDestroy() override;`
- L118 _public member_ `float TimePerTestLocation = 60.f;`
- L119 _public member_ `double TimeAtTestLocation = 0.0;`
- L120 _public member_ `TObjectPtr<AActor> DisplayClusterActor = nullptr;`
- L123 _private prototype_ `virtual void UnbindAllDelegates() override;`
- L125 _private member_ `FICVFXAutoTestState* States[(uint8)EICVFXAutoTestState::MAX];`
- L126 _private member_ `float StateTimeouts[(uint8)EICVFXAutoTestState::MAX];`
- L127 _private member_ `EICVFXAutoTestState CurrentState;`
- L129 _private prototype_ `virtual void OnPreWorldInitialize(UWorld* World) override;`
- L132 _private prototype_ `void OnWorldBeginPlay();` — `UFUNCTION()`
- L135 _private prototype_ `void OnGameStateSet(AGameStateBase* const GameStateBase);` — `UFUNCTION()`
- L137 _private member_ `FConsoleVariableSinkHandle SoakTimeSink;`
- L140 _private prototype_ `void OnSoakTimeChanged();` — `UFUNCTION()`
- L142 _private member_ `TArray<AActor*> TestLocations;`
- L144 _private member_ `int32 CurrentTestLocationIndex = 0;`
- L147 _private member_ `std::atomic<int32> InnerGPUIndex = 0;` — What GPU Index should be used for the inner viewport.

### `Plugins/VirtualProduction/ICVFXTesting/Source/ICVFXTesting/Public/ICVFXTestControllerBase.h` (Public)


#### class `UICVFXTestControllerBase`  
`class UICVFXTestControllerBase : public UGauntletTestController`  
_L22-102_
- reflection: `UCLASS()`
- inherits: `UGauntletTestController`
- L27 _public prototype_ `UICVFXTestControllerBase(const FObjectInitializer& ObjectInitializer);`
- L31 _protected prototype_ `virtual void OnInit() override;`
- L32 _protected prototype_ `virtual void OnTick(float TimeDelta) override;`
- L33 _protected prototype_ `virtual void OnStateChange(FName OldState, FName NewState) override;`
- L34 _protected prototype_ `virtual void BeginDestroy() override;`
- L37 _protected prototype_ `virtual void EndICVFXTest(const int32 ExitCode=0);`
- L38 _protected prototype_ `virtual void UnbindAllDelegates();`
- L41 _public prototype_ `uint32 GetRunCount() const;`
- L42 _public prototype_ `uint32 GetMaxRunCount() const;`
- L43 _public prototype_ `uint32 GetRunsRemaining() const;`
- L44 _public prototype_ `uint32 MarkRunComplete();`
- L46 _public prototype_ `bool RequestsFPSChart();`
- L47 _public prototype_ `bool RequestsMemReport();`
- L48 _public prototype_ `bool RequestsVideoCapture();`
- L50 _public prototype_ `void ConsoleCommand(const TCHAR* Cmd);`
- L52 _public prototype_ `void ExecuteMemReport(const TOptional<FString> Args=TOptional<FString>());`
- L53 _public prototype_ `void SetMemReportTimer(const TOptional<float> Interval=TOptional<float>());`
- L54 _public prototype_ `void ClearMemReportTimer();`
- L56 _public prototype_ `bool TryStartingVideoCapture();`
- L57 _public prototype_ `bool TryFinalizingVideoCapture(const bool bStopAutoContinue = false);`
- L60 _public member_ `FString DisplayClusterUObjectPath;`
- L63 _private member_ `float WarnStuckTime;`
- L64 _private member_ `float NextWarnStuckTime;`
- L66 _private prototype_ `void OnPreWorldInitializeInternal(UWorld* World, const UWorld::InitializationValues IVS);`
- L67 _private function_ `virtual void OnPreWorldInitialize(UWorld* World)`
- L70 _private prototype_ `void TryEarlyExec(UWorld* const World);` — `UFUNCTION()`
- L73 _private member_ `const TArray<FString> CmdsToExecEarly = { TEXT("t.FPSChart.DoCsvProfile"), TEXT("ICVFXTest"), TEXT("r.nanite"), TEXT("r.ScreenPercentage"), TEXT("r.RayTracing"), TEXT("r.DynamicGlobalIlluminationMethod"), TEXT("r.ReflectionMethod"), TEXT("r.Lumen"), TEXT("FX.AllowGPUParticles"), TEXT("r.Sh` — List of command prefixes used to find and execute commands passed in through commandline or config OnInit.
- L85 _private member_ `uint32 RunCount;`
- L87 _private member_ `bool bRequestsFPSChart;`
- L88 _private member_ `bool bRequestsMemReport;`
- L89 _private member_ `bool bRequestsVideoCapture;`
- L91 _private member_ `FTimerHandle MemReportTimerHandle;`
- L92 _private member_ `FTimerDelegate MemReportTimerDelegate;`
- L93 _private member_ `FConsoleVariableSinkHandle MemReportIntervalSink;`
- L96 _private prototype_ `void OnMemReportTimerExpired();` — `UFUNCTION()`
- L99 _private prototype_ `void OnMemReportIntervalChanged();` — `UFUNCTION()`
- L101 _private member_ `FText VideoRecordingTitle;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogICVFXTest, Log, All) class AActor;`

### `Plugins/VirtualProduction/ICVFXTesting/Source/ICVFXTesting/Public/ICVFXTestLocation.h` (Public)


#### class `AICVFXTestLocation`  
`class AICVFXTestLocation : public ACameraActor`  
_L13-18_
- reflection: `UCLASS(Blueprintable, BlueprintType, Category="ICVFX", DisplayName="ICVFXTestLocation")`
- inherits: `ACameraActor`
- desc: Actor used when running ICVFX perf tests. For every test location, the display cluster root actor will be moved to this location and perf data will be connected for a minute.
