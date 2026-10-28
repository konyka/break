# Plugins / AutomatedPerfTesting

- module root: `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting`
- headers: 15; symbols: 447
- symbol kinds: class=21, delegate=9, enum=1, enumerator=7, function=39, macro=11, member=146, namespace=1, prototype=205, struct=7
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, DeveloperSettings, Engine, Json, JsonUtilities, LevelSequence, MovieScene, Slate, SlateCore
- PublicDependencyModuleNames: Core, Gauntlet

### `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/AutomatedMaterialPerfTest.h` (Public)


#### class `UAutomatedMaterialPerfTestProjectSettings`  
`class UAutomatedMaterialPerfTestProjectSettings : public UDeveloperSettings`  
_L19-93_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Config=Engine, DefaultConfig, DisplayName="Automated Performance Testing | Materials")`
- inherits: `UDeveloperSettings`
- L24 _public prototype_ `UAutomatedMaterialPerfTestProjectSettings(const FObjectInitializer&);`
- L27 _public function_ `virtual FName GetContainerName() const override` — Gets the settings container name for the settings, either Project or Editor
- L29 _public function_ `virtual FName GetCategoryName() const override` — Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc.
- L35 _public member_ `TArray<FSoftObjectPath> MaterialsToTest;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Material Perf Test | Parameters", meta=(AllowedClasses="/Script/Engine.MaterialInterface"))` — List of materials to load and review for the Material Performance Test
- L41 _public member_ `bool bCaptureScreenshots;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Material Perf Test | Parameters")` — If true, will capture a screenshot for each material tested after gathering data
- L47 _public member_ `float WarmUpTime;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Material Perf Test | Parameters")` — For how long the material performance test should delay before beginning to gather data for a material, in seconds
- L53 _public member_ `float SoakTime;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Material Perf Test | Parameters")` — For how long the material performance test should gather data on each material, in seconds
- L59 _public member_ `float CooldownTime;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Material Perf Test | Parameters")` — For how long the material performance test should delay after ending evaluation before switching to the next material
- L66 _public member_ `FSoftObjectPath MaterialPerformanceTestMap;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Material Perf Test | Scene", meta=(AllowedClasses="/Script/Engine.World"))` — The map in which the material test will take place. Useful if you need to set up things like RVT volumes that are required by your materials.
- L73 _public member_ `FString GameModeOverride;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Material Perf Test | Scene")` — If set, will launch the material performance test map with this game mode alias (make sure you've set the game mode alias in the Maps and Modes settings of your project!)
- L79 _public member_ `TEnumAsByte<ECameraProjectionMode::Type> CameraProjectionMode;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Material Perf Test | Camera")` — Which camera projection mode to use
- L86 _public member_ `float PlateDistanceFromCamera;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Material Perf Test | Plate")` — How far away from the camera should the material test plate be placed (will also be used for Ortho Width if the camera projection mode is orthographic)
- L92 _public member_ `FSoftObjectPath MaterialPlate;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Material Perf Test | Plate")` — Which static mesh to use as the material plate

#### class `UAutomatedMaterialPerfTest`  
`class UAutomatedMaterialPerfTest : public UAutomatedPerfTestControllerBase`  
_L99-145_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAutomatedPerfTestControllerBase`
- L105 _public prototype_ `virtual void SetupTest() override;`
- L108 _public prototype_ `virtual void RunTest() override;` — `UFUNCTION()`
- L110 _public prototype_ `virtual FString GetPerfTestTypeID() const override;`
- L112 _public prototype_ `virtual void GatherTestMetadata(TArray<TPair<FString, FString>>& OutMetadata) const override;`
- L116 _public prototype_ `void SetUpNextMaterial();` — `UFUNCTION()`
- L119 _public prototype_ `void EvaluateMaterial();` — `UFUNCTION()`
- L122 _public prototype_ `void FinishMaterialEvaluation();` — `UFUNCTION()`
- L125 _public prototype_ `void ScreenshotMaterial();` — `UFUNCTION()`
- L127 _public prototype_ `FString GetCurrentMaterialRegionName() const;`
- L129 _public prototype_ `void MarkMaterialStart();`
- L130 _public prototype_ `void MarkMaterialEnd();`
- L133 _protected prototype_ `virtual void OnInit() override;`
- L134 _protected prototype_ `virtual void UnbindAllDelegates() override;`
- L135 _protected prototype_ `virtual void TeardownTest(bool bExitAfterTeardown = true) override;`
- L137 _protected prototype_ `void OpenMaterialPerformanceTestMap() const;`
- L140 _private member_ `ACameraActor* Camera;`
- L141 _private member_ `AStaticMeshActor* MaterialPlate;`
- L142 _private member_ `UMaterialInterface* CurrentMaterial;`
- L143 _private member_ `int CurrentMaterialIndex;`
- L144 _private member_ `const UAutomatedMaterialPerfTestProjectSettings* Settings;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUTOMATEDPERFTESTING_API`

### `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/AutomatedPerfTestControllerBase.h` (Public)


#### class `UAutomatedPerfTestControllerBase`  
`class UAutomatedPerfTestControllerBase : public UGauntletTestController`  
_L77-195_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGauntletTestController`
- L81 _public prototype_ `void OnPreWorldInitializeInternal(UWorld* World, const UWorld::InitializationValues IVS);`
- L82 _public prototype_ `virtual void OnPreWorldInitialize(UWorld* World);`
- L85 _public prototype_ `void OnWorldBeginPlay();` — `UFUNCTION()`
- L89 _public prototype_ `UAutomatedPerfTestControllerBase(const FObjectInitializer& ObjectInitializer);`
- L91 _public prototype_ `FString GetTestName() const;`
- L92 _public prototype_ `FString GetTestID() const;`
- L95 _public prototype_ `virtual FString GetPerfTestTypeID() const;` — Unique identifier for the class type provided to output artifact generation.
- L97 _public prototype_ `FString GetOverallRegionName();`
- L98 _public prototype_ `FString GetTraceChannels();`
- L100 _public prototype_ `bool RequestsInsightsTrace() const;`
- L101 _public prototype_ `bool RequestsCSVProfiler() const;`
- L102 _public prototype_ `bool RequestsFPSChart() const;`
- L103 _public prototype_ `bool RequestsVideoCapture() const;`
- L104 _public prototype_ `bool RequestsLockedDynRes() const;`
- L106 _public prototype_ `bool TryStartInsightsTrace();`
- L107 _public prototype_ `bool TryStopInsightsTrace();`
- L109 _public prototype_ `bool TryStartCSVProfiler(FString CSVFileName, const FString& DestinationFolder = FString(), int32 Frames = -1);`
- L110 _public prototype_ `bool TryStopCSVProfiler();`
- L112 _public prototype_ `bool TryStartFPSChart();`
- L113 _public prototype_ `bool TryStopFPSChart();`
- L115 _public prototype_ `bool TryStartVideoCapture();`
- L116 _public prototype_ `bool TryFinalizingVideoCapture(const bool bStopAutoContinue = false);`
- L122 _public prototype_ `virtual void GatherTestMetadata(TArray<TPair<FString, FString>>& OutMetadata) const;` — Gather test metadata key-value pairs for profiling instruments. Override this method to add controller specific metadata (map names, material names, etc). Always call Super::GatherTestMetadata() to include base metadata.
- L124 _public prototype_ `virtual void SetupTest();`
- L125 _public prototype_ `virtual void RunTest();`
- L126 _public prototype_ `virtual void TeardownTest(bool bExitAfterTeardown = true);`
- L127 _public prototype_ `virtual void TriggerExitAfterDelay();`
- L128 _public prototype_ `virtual void Exit();`
- L130 _public prototype_ `AGameModeBase* GetGameMode() const;`
- L132 _public prototype_ `void TakeScreenshot(FString ScreenshotName);`
- L134 _public prototype_ `void ConsoleCommand(const TCHAR* Cmd);`
- L138 _protected prototype_ `virtual void OnInit() override;`
- L139 _protected prototype_ `virtual void OnTick(float TimeDelta) override;`
- L140 _protected prototype_ `virtual void BeginDestroy() override;`
- L145 _protected prototype_ `void EndTestSuccess();` — `UFUNCTION()` — Shut down and queue an exit with an exit code of 0 to indicate success.
- L151 _protected prototype_ `void EndTestFailure(const int32 ExitCode = 1);` — `UFUNCTION()` — Shut down and queue an exit with an exit code of 1 to indicate generic failure. A custom non-zero value may be provided if needed, though any new systemic failures should be implemented as a new function with a custom reserved value.
- L154 _protected prototype_ `virtual void OnVideoRecordingFinalized(bool Succeeded, const FString& FilePath);` — `UFUNCTION()`
- L156 _protected prototype_ `virtual void UnbindAllDelegates();`
- L158 _protected prototype_ `void SetupGameModeInstance();`
- L160 _protected prototype_ `APlayerController* GetPlayerController();`
- L163 _protected prototype_ `void SetupProfiling();` — Profiling Functions
- L164 _protected prototype_ `void InitializeInsights();`
- L165 _protected prototype_ `void ShutdownInsights();`
- L166 _protected prototype_ `void TeardownProfiling();`
- L167 _protected prototype_ `void MarkProfilingStart();`
- L168 _protected prototype_ `void MarkProfilingEnd();`
- L173 _private prototype_ `void EndAutomatedPerfTest(const int32 ExitCode);` — Shut down and request the process exit with the provided error code.
- L175 _private member_ `FString TraceChannels;`
- L176 _private member_ `FString TestDatetime;`
- L177 _private member_ `FString TestID;`
- L178 _private member_ `bool bRequestsFPSChart;`
- L179 _private member_ `bool bRequestsInsightsTrace;`
- L180 _private member_ `bool bRequestsCSVProfiler;`
- L181 _private member_ `bool bRequestsVideoCapture;`
- L182 _private member_ `bool bRequestsLockedDynRes;`
- L183 _private member_ `uint64 InsightsRegionID;`
- L184 _private member_ `FString ArtifactOutputPath;`
- L186 _private member_ `FText VideoRecordingTitle;`
- L188 _private member_ `AGameModeBase* GameMode;`
- L192 _private member_ `FGraphEventRef CsvProfileEndCaptureEvent;` — Event for the most recent call to TryStopCSVProfiler. Used to ensure the resulting csv file is flushed before exiting via EndAutomatedPerfTest().
- L194 _private member_ `FDelegateHandle CsvProfilerDelegateHandle;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API AUTOMATEDPERFTESTING_API`
- L19 _namespace_ `namespace AutomatedPerfTest`
- L21 _function_ `static UWorld* FindCurrentWorld()` (scope `AutomatedPerfTest`)
- L46 _function_ `static bool IsWorldLoaded(const FString & WorldName)` (scope `AutomatedPerfTest`) — New function because there could be more than one Game world alive at any point with MultiWorld

### `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/AutomatedPerfTestGameModeBase.h` (Public)


#### class `AAutomatedPerfTestGameModeBase`  
`class AAutomatedPerfTestGameModeBase : public AGameModeBase, public IAutomatedPerfTestInterface`  
_L14-35_
- reflection: `UCLASS(Blueprintable)`
- inherits: `AGameModeBase,IAutomatedPerfTestInterface`
- L22 _public prototype_ `void SetupTest();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Automated Perf Test")`
- L22 _public prototype_ `void SetupTest();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Automated Perf Test")`
- L25 _public prototype_ `void TeardownTest();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Automated Perf Test")`
- L25 _public prototype_ `void TeardownTest();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Automated Perf Test")`
- L28 _public prototype_ `void RunTest();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Automated Perf Test")`
- L28 _public prototype_ `void RunTest();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Automated Perf Test")`
- L31 _public prototype_ `void Exit();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Automated Perf Test")`
- L31 _public prototype_ `void Exit();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Automated Perf Test")`

### `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/AutomatedPerfTestInterface.h` (Public)


#### class `UAutomatedPerfTestInterface`  
`class UAutomatedPerfTestInterface : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType)`
- inherits: `UInterface`
- desc: This class does not need to be modified.

#### class `IAutomatedPerfTestInterface`  
`class IAutomatedPerfTestInterface`  
_L20-37_
- L27 _public prototype_ `void SetupTest();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Automated Perf Test")`
- L30 _public prototype_ `void TeardownTest();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Automated Perf Test")`
- L33 _public prototype_ `void RunTest();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Automated Perf Test")`
- L36 _public prototype_ `void Exit();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Automated Perf Test")`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUTOMATEDPERFTESTING_API`

### `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/AutomatedPerfTestProjectSettings.h` (Public)


#### class `UAutomatedPerfTestProjectSettings`  
`class UAutomatedPerfTestProjectSettings : public UDeveloperSettings`  
_L14-29_
- reflection: `UCLASS(MinimalAPI, Config=Engine)`
- inherits: `UDeveloperSettings`
- L19 _public prototype_ `UAutomatedPerfTestProjectSettings(const FObjectInitializer&);`
- L22 _public function_ `virtual FName GetContainerName() const override` — Gets the settings container name for the settings, either Project or Editor
- L24 _public function_ `virtual FName GetCategoryName() const override` — Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc.
- L28 _public member_ `float TeardownToExitDelay = 5.0;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Automated Performance Testing")` — How many seconds to wait before transition from Teardown to Exiting the test

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUTOMATEDPERFTESTING_API`

### `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/AutomatedPerfTestSubsystem.h` (Public)


#### class `UAutomatedPerfTestSubsystem`  
`class UAutomatedPerfTestSubsystem : public UEngineSubsystem`  
_L13-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem`
- L18 _private prototype_ `static FString GetTestID();` — `UFUNCTION(BlueprintCallable, Category="Automated Perf Testing")`

### `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/AutomatedPerfTesting.h` (Public)


#### class `FAutomatedPerfTestingModule`  
`class FAutomatedPerfTestingModule : public IModuleInterface`  
_L12-21_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L18 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAutomatedPerfTest, Log, All) CSV_DECLARE_CATEGORY_EXTERN(AutomatedPerfTest);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAutomatedPerfTest, Log, All) CSV_DECLARE_CATEGORY_EXTERN(AutomatedPerfTest);`

### `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/AutomatedProfileGoTest.h` (Public)


#### class `UAutomatedProfileGoTest`  
`class UAutomatedProfileGoTest : public UAutomatedPerfTestControllerBase`  
_L26-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAutomatedPerfTestControllerBase`
- desc: Automated Perf Profile Go Test.
- L31 _public prototype_ `UAutomatedProfileGoTest(const FObjectInitializer& ObjectInitializer);`
- L33 _public prototype_ `virtual void OnInit() override;`
- L34 _public prototype_ `virtual FString GetPerfTestTypeID() const override;`
- L35 _public prototype_ `virtual void SetupTest() override;`
- L36 _public prototype_ `virtual void OnTick(float TimeDelta) override;`
- L39 _protected prototype_ `virtual void OnRequestFailed();`
- L40 _protected prototype_ `virtual void OnScenarioStarted(const FString& InName);`
- L41 _protected prototype_ `virtual void OnScenarioEnded(const FString& InName);`
- L42 _protected prototype_ `virtual void OnPassStarted();`
- L43 _protected prototype_ `virtual void OnPassEnded();`
- L44 _protected prototype_ `virtual void UnbindAllDelegates() override;`
- L45 _protected prototype_ `virtual void CompleteTest(bool bSuccess);`
- L47 _protected prototype_ `void LoadFromJSON(const FString& Filename);`
- L48 _protected prototype_ `void SaveToJSON(const FString& Filename);`
- L49 _protected prototype_ `FString GetProfileGoArgsString();`
- L51 _protected member_ `bool bPlayerSetupFinished;`
- L52 _protected member_ `bool bIgnorePawn;`
- L53 _protected member_ `bool bBoundDelegates;`
- L54 _protected member_ `bool bRequestedProfileGo;`
- L55 _protected member_ `bool bStartedProfileGo;`
- L56 _protected member_ `bool bShouldTick;`
- L57 _protected member_ `FString ProfileGoStatus;`
- L58 _protected member_ `FString ProfileGoConfigFile;`
- L60 _protected member_ `FString ProfileGoCommand;`
- L61 _protected member_ `FString ProfileGoScenario;`
- L62 _protected member_ `int32 NumRequiredLoops;`
- L63 _protected member_ `int32 NumCompletedLoops;`

#### class `UAutomatedProfileGoTestProjectSettings`  
`class UAutomatedProfileGoTestProjectSettings : public UDeveloperSettings`  
_L68-91_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Config = Engine, DefaultConfig, DisplayName = "Automated Performance Testing | ProfileGo")`
- inherits: `UDeveloperSettings`
- L73 _public prototype_ `UAutomatedProfileGoTestProjectSettings(const FObjectInitializer&);`
- L76 _public function_ `virtual FName GetContainerName() const override` — Gets the settings container name for the settings, either Project or Editor
- L78 _public function_ `virtual FName GetCategoryName() const override` — Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc.
- L81 _public member_ `TArray<FProfileGoScenarioAPT> Scenarios;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "ProfileGo")`
- L84 _public member_ `TArray<FProfileGoCollectionAPT> Collections;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "ProfileGo")`
- L87 _public member_ `TArray<FProfileGoCommandAPT> Commands;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "ProfileGo")`
- L90 _public member_ `TArray<FProfileGoGeneratedScenarioAPT> GeneratedScenarios;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "ProfileGo")`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API AUTOMATEDPERFTESTING_API`

### `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/AutomatedReplayPerfTest.h` (Public)


#### class `UAutomatedReplayPerfTestProjectSettings`  
`class UAutomatedReplayPerfTestProjectSettings : public UDeveloperSettings`  
_L20-39_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Config = Engine, DefaultConfig, DisplayName = "Automated Performance Testing | Replay")`
- inherits: `UDeveloperSettings`
- L25 _public prototype_ `UAutomatedReplayPerfTestProjectSettings(const FObjectInitializer&);`
- L28 _public function_ `virtual FName GetContainerName() const override` — Gets the settings container name for the settings, either Project or Editor
- L30 _public function_ `virtual FName GetCategoryName() const override` — Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc.
- L34 _public member_ `TArray<FFilePath> ReplaysToTest;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Replay Perf Test", meta = (FilePathFilter = "replay", RelativeToGameDir))` — Path to replay file to be used during Replay Perf Test
- L38 _public prototype_ `bool GetReplayPathFromName(FName TestName, FString& FoundReplay) const;` — `UFUNCTION(BlueprintCallable, Category = "Replay Perf Test")` — Get replay path from given replay name

#### class `UAutomatedReplayPerfTest`  
`class UAutomatedReplayPerfTest : public UAutomatedPerfTestControllerBase`  
_L45-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAutomatedPerfTestControllerBase`
- L51 _public prototype_ `virtual FString GetPerfTestTypeID() const override;`
- L52 _public prototype_ `virtual void SetupTest() override;`
- L55 _public prototype_ `virtual void RunTest() override;` — `UFUNCTION()`
- L56 _public prototype_ `virtual void TeardownTest(bool bExitAfterTeardown = true) override;`
- L59 _protected prototype_ `virtual void OnInit() override;`
- L60 _protected prototype_ `virtual void UnbindAllDelegates() override;`
- L62 _protected prototype_ `void OnReplayStarted(UWorld* World);`
- L63 _protected prototype_ `void OnReplayComplete(UWorld* World);`
- L64 _protected prototype_ `void OnReplayFailure(UWorld* World, const UE::Net::TNetResult<EReplayResult>& Error);`
- L67 _private member_ `FString ReplayName;`
- L68 _private member_ `bool bIsReplayTriggered = false;`
- L69 _private member_ `bool bIsTearingDown = false;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API AUTOMATEDPERFTESTING_API`

### `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/AutomatedSequencePerfTest.h` (Public)


#### struct `FAutomatedPerfTestMapSequenceCombo`  
`struct FAutomatedPerfTestMapSequenceCombo`  
_L23-44_
- reflection: `USTRUCT(BlueprintType)`
- L31 _public member_ `FName ComboName;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Sequence Perf Test", meta=(AllowedClasses="/Script/Engine.World"))` — Use this name to directly reference this map/sequence combo via BuildGraph or UAT with -AutomatedPerfTest.SequenceTest.MapSequenceComboName
- L34 _public member_ `FSoftObjectPath Map;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Sequence Perf Test", meta=(AllowedClasses="/Script/Engine.World"))`
- L37 _public member_ `FSoftObjectPath Sequence;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Sequence Perf Test", meta=(AllowedClasses="/Script/LevelSequence.LevelSequence"))`
- L43 _public member_ `FString GameModeOverride;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Sequence Perf Test", meta=(AllowedClasses="/Script/GameFramework.GameModeBase"))` — The name of the alias of the game mode you can optionally override when opening the level

#### class `UAutomatedSequencePerfTestProjectSettings`  
`class UAutomatedSequencePerfTestProjectSettings : public UDeveloperSettings`  
_L48-74_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Config=Engine, DefaultConfig, DisplayName="Automated Performance Testing | Sequence")`
- inherits: `UDeveloperSettings`
- L53 _public prototype_ `UAutomatedSequencePerfTestProjectSettings(const FObjectInitializer&);`
- L56 _public function_ `virtual FName GetContainerName() const override` — Gets the settings container name for the settings, either Project or Editor
- L58 _public function_ `virtual FName GetCategoryName() const override` — Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc.
- L66 _public member_ `TArray<FAutomatedPerfTestMapSequenceCombo> MapsAndSequencesToTest;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Sequence Perf Test")` — When the project is run with a Sequence Perf Test, cycle through the input maps, and load and run the associated sequence outputting separate profiling results for each map/sequence combo Can be overridden via commandline with -AutomatedPerfTest.SequencePerfTest.TestName, which will only run the test with the matching name
- L69 _public prototype_ `bool GetComboFromTestName(FName TestName, FAutomatedPerfTestMapSequenceCombo& FoundSequence) const;` — `UFUNCTION(BlueprintCallable, Category="Sequence Perf Test")`
- L73 _public member_ `float SequenceStartDelay=5.0;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Sequence Perf Test")` — How long to delay between setting up the sequence for the map before the sequence actually starts

#### class `UAutomatedSequencePerfTest`  
`class UAutomatedSequencePerfTest : public UAutomatedPerfTestControllerBase`  
_L80-125_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAutomatedPerfTestControllerBase`
- L86 _public prototype_ `virtual FString GetPerfTestTypeID() const override;`
- L87 _public prototype_ `virtual void SetupTest() override;`
- L90 _public prototype_ `virtual void RunTest() override;` — `UFUNCTION()`
- L92 _public prototype_ `virtual void TeardownTest(bool bExitAfterTeardown = true) override;`
- L94 _public prototype_ `void GatherTestMetadata(TArray<TPair<FString, FString>>& OutMetadata) const override;`
- L99 _public prototype_ `void NextMap();` — `UFUNCTION()` — This function is called on world change to set up the map for the correct map/sequence combo
- L102 _public prototype_ `void OnSequenceFinished();` — `UFUNCTION()`
- L105 _public prototype_ `void OnCameraCut(UCameraComponent* CameraComponent);` — `UFUNCTION()`
- L107 _public prototype_ `FString GetCameraCutID();`
- L110 _protected prototype_ `virtual void OnInit() override;`
- L111 _protected prototype_ `virtual void UnbindAllDelegates() override;`
- L114 _private member_ `const UAutomatedSequencePerfTestProjectSettings* Settings;`
- L116 _private member_ `FName SequenceTestName;`
- L117 _private member_ `TOptional<FAutomatedPerfTestMapSequenceCombo> CurrentMapSequenceCombo;`
- L118 _private member_ `TArray<FAutomatedPerfTestMapSequenceCombo> MapSequenceCombos;`
- L120 _private member_ `ALevelSequenceActor* SequenceActor;`
- L121 _private member_ `ULevelSequencePlayer* SequencePlayer;`
- L123 _private member_ `UCameraComponent* CurrentCamera;`
- L124 _private member_ `int NumCameraCuts;` — TODO this is temporary until a reliable method is found for getting the user-set name of a camera cut out of Sequencer in packaged builds

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API AUTOMATEDPERFTESTING_API`

### `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/ProfileGo/ProfileGo.h` (Public)


#### enum `EProfileGoStateAPT`  
`enum class EProfileGoStateAPT : int8`  
_L27-36_
- reflection: `UENUM()`
- L29 _public enumerator_ `None`
- L30 _public enumerator_ `StartingRequest`
- L31 _public enumerator_ `SettlingLocation`
- L32 _public enumerator_ `RunningCommands`
- L33 _public enumerator_ `CompletedScenario`
- L34 _public enumerator_ `Summary`
- L35 _public enumerator_ `Completed`

#### struct `FProfileGoScenarioAPT`  
`struct FProfileGoScenarioAPT`  
_L40-77_
- reflection: `USTRUCT(BlueprintType, Category = "APT")`
- L45 _public member_ `FString Name;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "APT")`
- L48 _public member_ `FVector Position;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "APT")`
- L51 _public member_ `FRotator Orientation;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "APT")`
- L54 _public member_ `FString OnBegin;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "APT")`
- L57 _public member_ `FString OverrideCommands;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "APT")`
- L60 _public member_ `FString OnEnd;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "APT")`
- L63 _public member_ `bool AutoGenerated = false;` — `UPROPERTY()`
- L66 _public member_ `bool SkipRunCommands = false;` — `UPROPERTY()`
- L68 _public function_ `FProfileGoScenarioAPT() : Position(ForceInitToZero) , Orientation(ForceInitToZero)`

#### struct `FProfileGoGeneratedScenarioAPT`  
`struct FProfileGoGeneratedScenarioAPT : public FProfileGoScenarioAPT`  
_L80-102_
- reflection: `USTRUCT(BlueprintType, Category = "APT")`
- inherits: `FProfileGoScenarioAPT`
- L85 _public member_ `FString ScenarioCommand;` — `UPROPERTY()`
- L88 _public member_ `FString Arguments;` — `UPROPERTY()`
- L91 _public member_ `FString CopyLocation;` — `UPROPERTY()`
- L93 _public function_ `FProfileGoGeneratedScenarioAPT() : FProfileGoScenarioAPT()`
- L101 _public prototype_ `TArray<FProfileGoCommandAPT> Generate() const;`

#### struct `FProfileGoCollectionAPT`  
`struct FProfileGoCollectionAPT`  
_L105-114_
- reflection: `USTRUCT(BlueprintType, Category = "APT")`
- L110 _public member_ `FString Name;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "APT")`
- L113 _public member_ `TArray<FString> Scenarios;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "APT")`

#### struct `FProfileGoCommandAPT`  
`struct FProfileGoCommandAPT`  
_L117-142_
- reflection: `USTRUCT(BlueprintType, Category = "APT")`
- L122 _public member_ `FString Group;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "APT")`
- L125 _public member_ `FString Command;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "APT")`
- L128 _public member_ `float Wait = 0.0f;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "APT")`
- L131 _public member_ `FString Log;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "APT")`
- L134 _public member_ `bool CopyOutputToGameLog = true;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "APT")`
- L137 _public member_ `bool WaitForCallback = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "APT")`
- L139 _public function_ `FProfileGoCommandAPT()`

#### struct `FProfileGoScenarioResultAPT`  
`struct FProfileGoScenarioResultAPT`  
_L153-176_
- reflection: `USTRUCT()`
- L158 _public member_ `FProfileGoScenarioAPT Scenario;` — `UPROPERTY()`
- L160 _public member_ `bool bArrivedAtLocation = false;`
- L162 _public member_ `bool bRetriedTeleport = false;`
- L164 _public member_ `bool bRetracedZ = false;`
- L166 _public member_ `bool bCompleted = false;`
- L168 _public member_ `bool bRanGC = false;`
- L170 _public member_ `float AsyncLoadTime = 0.0f;`
- L172 _public function_ `FProfileGoScenarioResultAPT()`

#### struct `FProfileGoRequestAPT`  
`struct FProfileGoRequestAPT`  
_L180-218_
- reflection: `USTRUCT()`
- desc: Contains data about the current profilego request
- L185 _public member_ `FString RequestName;` — profile name passed into the request
- L188 _public member_ `FString RequestArgs;` — arguments passed into the request
- L191 _public member_ `TArray<FProfileGoScenarioAPT> PendingScenarios;` — a list of scenarios to run
- L194 _public member_ `TArray<FProfileGoScenarioResultAPT> ScenarioResults;` — a list of results from each location
- L198 _public member_ `FProfileGoScenarioResultAPT CurrentResult;` — `UPROPERTY()` — current result
- L201 _public member_ `TArray<FProfileGoCommandAPT> PendingCommands;` — Commands to be executed (generate anew at each location)
- L204 _public member_ `float SettleTime = 0.0f;` — Time to settle before running commands
- L207 _public member_ `bool bSkipSettling = false;` — Do we want to skip settling and everything that comes with it.
- L210 _public member_ `bool bIgnorePawn = false;` — Do we want to ignore whether the player pawn exists and skip all functionality related to it.
- L213 _public member_ `bool bRetraceZ = false;` — Use FindBestStandingPoint() during settling to retrace the Z coordinate of each scenario
- L215 _public function_ `FProfileGoRequestAPT()`

#### class `UProfileGo`  
`class UProfileGo : public UObject`  
_L225-375_
- reflection: `UCLASS(Config = Game, MinimalAPI)`
- inherits: `UObject`
- desc: ProfileGo Automated Perf Test
- L230 _public prototype_ `UProfileGo();`
- L233 _public function_ `static UProfileGo& GetCDO()` — This getter is primarily used as a static way to access Config data.
- L239 _public prototype_ `bool IsRunning() const;`
- L240 _public prototype_ `void Tick(float DeltaTime);`
- L242 _public prototype_ `bool Run(UProfileGoSubsystem* InSubsystem, const TCHAR* InProfileName, const TCHAR* InProfileArgs);`
- L244 _public prototype_ `void AddNewProfileGoCollection(FProfileGoCollectionAPT NewCollection);`
- L245 _public prototype_ `void AddNewProfileGoScenario(FProfileGoScenarioAPT NewScenario);`
- L246 _public prototype_ `bool AddScenariosToCurrentRequest(TArray<FProfileGoScenarioAPT> Scenarios, int InsertIndex = INDEX_NONE);`
- L249 _public prototype_ `bool AddScenariosToCurrentRequest(const TCHAR* ProfileName, bool bErrorIfNotFound = false, int InsertIndex = INDEX_NONE);` — Returns true if a scenario or collection was found matching ProfileName. Begins test pass once all scenario names passed through ProfileGo have been added to the CurrentRequest.
- L250 _public prototype_ `bool TryFindScenarios(const TCHAR* ProfileName, TArray<FProfileGoScenarioAPT>& OutScenarios);`
- L251 _public prototype_ `bool WaitForLoadingAndStreaming(UWorld* InWorld, float DeltaTime, bool bIncrementalResourceStreaming = false);`
- L252 _public prototype_ `bool HasEncounteredError() const;`
- L254 _public prototype_ `FString GetStatus() const;`
- L255 _public prototype_ `FString GetCurrentScenarioName() const;`
- L257 _public prototype_ `void LoadFromJSON(const FString& Filename);`
- L258 _public prototype_ `void SaveToJSON(const FString& Filename);`
- L259 _public prototype_ `void AddScenariosInLevel(UWorld* World);`
- L260 _public prototype_ `void UpdateProjectSettings();`
- L262 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, CommandHandlerDelegate, FString&, const FProfileGoCommandAPT& ProfileGoCommand) void RegisterCommandDelegate(const FString& Command, CommandHandlerDelegate&& Handler);`
- L265 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, GeneratedScenarioHandlerDelegate, FString&, FString&) void RegisterGeneratedScenarioDelegate(const FString& Command, GeneratedScenarioHandlerDelegate&& Handler);`
- L269 _protected prototype_ `virtual void TickStartingRequest(float DeltaTime);`
- L270 _protected prototype_ `virtual void TickSettling(float DeltaTime);`
- L271 _protected prototype_ `virtual void TickProfiling(float DeltaTime);`
- L272 _protected prototype_ `virtual void TickCompletedScenario(float DeltaTime);`
- L273 _protected prototype_ `virtual void TickSummary(float DeltaTime);`
- L274 _protected prototype_ `virtual void TickCompleted(float DeltaTime);`
- L276 _protected prototype_ `virtual void StartNextScenario();`
- L277 _protected prototype_ `virtual void TeleportToScenario(FProfileGoScenarioAPT& CurrentScenario);`
- L278 _protected prototype_ `virtual bool TickSettlingLocation(float DeltaTime);`
- L280 _protected prototype_ `void AbortWithError(const TCHAR* InErrorMessage);`
- L281 _protected prototype_ `void ConsoleCommand(const TCHAR* InCommand);`
- L282 _protected prototype_ `void ClientMessage(const TCHAR* InMsg);`
- L283 _protected prototype_ `void StartCommandLog(const FProfileGoCommandAPT& ProfileGoCommand);`
- L284 _protected prototype_ `void StopCommandLog();`
- L286 _protected prototype_ `virtual bool TryGenerateScenariosForCurrentRequest(const TCHAR* InProfileName, const TCHAR* InProfileArgs);`
- L287 _protected prototype_ `bool TryParseValue(const TCHAR* Stream, const TCHAR* ParamName, FString& OutValue, bool bShouldStopOnSeparator = false);`
- L289 _protected prototype_ `void ExecuteProfileGoCommand(const FProfileGoCommandAPT& ProfileGoCommand);`
- L292 _protected prototype_ `void MarkCommandComplete();` — `UFUNCTION()`
- L295 _protected prototype_ `void WaitForCommandComplete(float MaxWaitSeconds = 10.f);` — `UFUNCTION()`
- L296 _protected member_ `FTimerHandle CommandCompleteFallbackTimerHandle;`
- L299 _protected prototype_ `void WaitForStreamingCommandComplete();` — `UFUNCTION()`
- L302 _protected prototype_ `void CheckIfStreamingCompleted();` — `UFUNCTION()`
- L304 _protected prototype_ `virtual bool TryHandleProfileGoCommandString(const FProfileGoCommandAPT& ProfileGoCommand);`
- L306 _protected prototype_ `void RegisterInternalCommandDelegates();`
- L307 _protected prototype_ `void RegisterInternalGeneratedScenarioDelegates();`
- L309 _protected prototype_ `APlayerController* GetPlayerController() const;`
- L311 _protected prototype_ `void SetState(EProfileGoStateAPT InState);`
- L312 _protected prototype_ `FString GetStateName(EProfileGoStateAPT InState) const;`
- L314 _protected prototype_ `static bool FindBestStandingPoint(UWorld* InWorld, FVector StartXyHalfHeightZ, FVector& OutPos, bool bIgnoreKillVolume = false, bool bIgnoreBlockingVolume = false);`
- L316 _protected prototype_ `TArray<FProfileGoCommandAPT> CreateCommandList(const FString& InCommandString);`
- L317 _protected prototype_ `virtual bool TryExecuteNextPendingCommand();`
- L318 _protected prototype_ `FProfileGoScenarioAPT CreateScenarioHere(const TCHAR* ScenarioName);`
- L320 _protected function_ `TArray<FProfileGoScenarioAPT>& GetScenarioTemplates()`
- L321 _protected function_ `TArray<FProfileGoGeneratedScenarioAPT>& GetGeneratedScenarioTemplates()`
- L322 _protected function_ `TArray<FProfileGoCollectionAPT>& GetCollectionTemplates()`
- L323 _protected function_ `TArray<FProfileGoCommandAPT>& GetCommandTemplates()`
- L325 _protected prototype_ `bool CollectionExists(const FString& Name);`
- L326 _protected prototype_ `bool ScenarioExists(const FString& Name);`
- L331 _protected member_ `int NumRequestedScenarios;` — The number of requested scenarios or collections requested by the ProfileGo command. The test pass will not begin until this is decremented to zero by AddScenariosToCurrentRequest()
- L332 _protected member_ `TSharedPtr<FOutputDeviceFile> ResultsFile;`
- L333 _protected member_ `TSet<FString> PreviousLogs;`
- L336 _protected member_ `float DefaultSettleTime;` — `UPROPERTY(Config)`
- L338 _protected prototype_ `DECLARE_DELEGATE_OneParam(StateTickerDelegate, float) TMap<EProfileGoStateAPT, StateTickerDelegate> StateTickers;`
- L341 _protected member_ `TMap<FString, CommandHandlerDelegate> CommandHandlers;`
- L342 _protected member_ `TMap<FString, GeneratedScenarioHandlerDelegate> GenerateScenarioHandlers;`
- L344 _protected member_ `EProfileGoStateAPT CurrentState;`
- L345 _protected member_ `TSharedPtr<FProfileGoRequestAPT> CurrentRequest;`
- L347 _protected member_ `bool bEncounteredError;`
- L348 _protected member_ `FString ErrorMessage;`
- L349 _protected member_ `bool bFirstTickInState;`
- L350 _protected member_ `float TimeInState;`
- L351 _protected member_ `double LastPlatformTimeSeconds;`
- L352 _protected member_ `bool bWaitingOnCommandComplete;`
- L353 _protected member_ `double LastTeleportPlatformTimeSeconds;`
- L354 _protected member_ `int32 ResourceStreamingIteration;`
- L356 _protected member_ `int32 DefaultSyncInterval;`
- L357 _protected member_ `int32 DutyCycle;`
- L358 _protected member_ `double SenarioStartTime;`
- L359 _protected member_ `float DutyCycleTime;`
- L361 _protected member_ `UProfileGoSubsystem* ProfileGoSubsystem;`
- L365 _private member_ `TArray<FProfileGoScenarioAPT> ProfileGoScenarios;` — `UPROPERTY(Config)`
- L368 _private member_ `TArray<FProfileGoGeneratedScenarioAPT> ProfileGoGeneratedScenarios;` — `UPROPERTY(Config)`
- L371 _private member_ `TArray<FProfileGoCollectionAPT> ProfileGoCollections;` — `UPROPERTY(Config)`
- L374 _private member_ `TArray<FProfileGoCommandAPT> ProfileGoCommands;` — `UPROPERTY(Config)`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API AUTOMATEDPERFTESTING_API`
- L145 _delegate_ `DECLARE_MULTICAST_DELEGATE(FProfileGoOnRequestFailed);` — Callback for state changes
- L145 _prototype_ `DECLARE_MULTICAST_DELEGATE(FProfileGoOnRequestFailed);` — Callback for state changes
- L146 _delegate_ `DECLARE_MULTICAST_DELEGATE(FProfileGoOnPassStarted);`
- L146 _prototype_ `DECLARE_MULTICAST_DELEGATE(FProfileGoOnPassStarted);`
- L147 _delegate_ `DECLARE_MULTICAST_DELEGATE(FProfileGoOnPassEnded);`
- L147 _prototype_ `DECLARE_MULTICAST_DELEGATE(FProfileGoOnPassEnded);`
- L148 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FProfileGoOnScenarioStarted, const FString&);`
- L148 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FProfileGoOnScenarioStarted, const FString&);`
- L149 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FProfileGoOnScenarioEnded, const FString&);`
- L149 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FProfileGoOnScenarioEnded, const FString&);`
- L262 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, CommandHandlerDelegate, FString&, const FProfileGoCommandAPT& ProfileGoCommand) void RegisterCommandDelegate(const FString& Command, CommandHandlerDelegate&& Handler);`
- L265 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, GeneratedScenarioHandlerDelegate, FString&, FString&) void RegisterGeneratedScenarioDelegate(const FString& Command, GeneratedScenarioHandlerDelegate&& Handler);`
- L338 _delegate_ `DECLARE_DELEGATE_OneParam(StateTickerDelegate, float) TMap<EProfileGoStateAPT, StateTickerDelegate> StateTickers;`

### `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/ProfileGo/ProfileGoSubsystem.h` (Public)


#### class `UProfileGoSubsystem`  
`class UProfileGoSubsystem : public UTickableWorldSubsystem`  
_L22-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTickableWorldSubsystem`
- L28 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem implementation Begin
- L29 _public prototype_ `virtual void Deinitialize() override;`
- L30 _public function_ `virtual TStatId GetStatId() const override`
- L34 _public prototype_ `virtual bool IsTickable() const override;` — FTickableGameObject implementation Begin
- L35 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L39 _public function_ `template <typename TProfileGoClass> bool Run(const TCHAR* ProfileName, const TCHAR* ProfileArgs)`
- L40 _public prototype_ `bool Run(TSubclassOf<UProfileGo> ProfileGoClass, const TCHAR* ProfileName, const TCHAR* ProfileArgs);`
- L42 _public function_ `FString GetStatusMessage() const`
- L43 _public function_ `bool IsRunning() const`
- L44 _public function_ `bool HasEncounteredError() const`
- L45 _public function_ `static bool WaitForLoadingAndStreaming(UWorld* InWorld, float DeltaTime, bool bIncrementalResourceStreaming = false)`
- L47 _public function_ `FProfileGoOnRequestFailed& OnRequestFailed()`
- L48 _public function_ `FProfileGoOnScenarioStarted& OnScenarioStarted()`
- L49 _public function_ `FProfileGoOnScenarioEnded& OnScenarioEnded()`
- L50 _public function_ `FProfileGoOnPassStarted& OnPassStarted()`
- L51 _public function_ `FProfileGoOnPassEnded& OnPassEnded()`
- L53 _public function_ `void LoadFromJSON(const FString& Filename)`
- L54 _public function_ `void SaveToJSON(const FString& Filename)`
- L56 _public function_ `void SetTestController(UAutomatedPerfTestControllerBase* Controller)`
- L57 _public function_ `UAutomatedPerfTestControllerBase* GetTestController() const`
- L61 _protected member_ `TObjectPtr<UProfileGo> ProfileGo;` — `UPROPERTY()`
- L63 _protected member_ `FProfileGoOnRequestFailed RequestFailedDelegate;`
- L64 _protected member_ `FProfileGoOnScenarioStarted ScenarioStartedDelegate;`
- L65 _protected member_ `FProfileGoOnScenarioStarted ScenarioEndedDelegate;`
- L66 _protected member_ `FProfileGoOnPassStarted PassStartedDelegate;`
- L67 _protected member_ `FProfileGoOnPassStarted PassEndedDelegate;`
- L69 _protected member_ `TObjectPtr<UAutomatedPerfTestControllerBase> TestController;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API AUTOMATEDPERFTESTING_API`

### `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/StaticCameraTests/AutomatedPerfTestStaticCamera.h` (Public)


#### class `AAutomatedPerfTestStaticCamera`  
`class AAutomatedPerfTestStaticCamera : public ACameraActor`  
_L8-17_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, ClassGroup=Performance)`
- inherits: `ACameraActor`
- L13 _public prototype_ `AAutomatedPerfTestStaticCamera(const FObjectInitializer& ObjectInitializer);`
- L16 _public member_ `FString CollectionName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProfileGo | Scenario", meta = (DefaultValue = "Default"))`

### `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/StaticCameraTests/AutomatedPlacedStaticCameraPerfTest.h` (Public)


#### class `UAutomatedPlacedStaticCameraPerfTest`  
`class UAutomatedPlacedStaticCameraPerfTest : public UAutomatedStaticCameraPerfTestBase`  
_L13-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAutomatedStaticCameraPerfTestBase`
- L18 _public prototype_ `virtual TArray<ACameraActor*> GetMapCameraActors() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUTOMATEDPERFTESTING_API`

### `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/StaticCameraTests/AutomatedStaticCameraPerfTestBase.h` (Public)


#### class `UAutomatedStaticCameraPerfTestProjectSettings`  
`class UAutomatedStaticCameraPerfTestProjectSettings : public UDeveloperSettings`  
_L13-64_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Config=Engine, DefaultConfig, DisplayName="Automated Performance Testing | Static Camera")`
- inherits: `UDeveloperSettings`
- L18 _public prototype_ `UAutomatedStaticCameraPerfTestProjectSettings(const FObjectInitializer&);`
- L21 _public function_ `virtual FName GetContainerName() const override` — Gets the settings container name for the settings, either Project or Editor
- L23 _public function_ `virtual FName GetCategoryName() const override` — Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc.
- L26 _public prototype_ `bool GetMapFromAssetName(FString AssetName, FSoftObjectPath& OutSoftObjectPath) const;` — `UFUNCTION(BlueprintCallable, Category="Static Camera Perf Test")`
- L32 _public member_ `TArray<FSoftObjectPath> MapsToTest;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Static Cameras", meta=(AllowedClasses="/Script/Engine.World"))` — List of levels to test
- L39 _public member_ `FString GameModeOverride;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Static Cameras")` — If set, will launch the material performance test map with this game mode alias (make sure you've set the game mode alias in the Maps and Modes settings of your project!)
- L45 _public member_ `bool bCaptureScreenshots;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Static Cameras")` — If true, will capture a screenshot for each camera tested after gathering data
- L51 _public member_ `float WarmUpTime;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Static Cameras")` — For how long the material performance test should delay before beginning to gather data for a material, in seconds
- L57 _public member_ `float SoakTime;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Static Cameras")` — For how long the static camera performance test should gather data on each camera, in seconds
- L63 _public member_ `float CooldownTime;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Static Cameras")` — For how long the static camera performance test should delay after ending evaluation before switching to the next camera

#### class `UAutomatedStaticCameraPerfTestBase`  
`class UAutomatedStaticCameraPerfTestBase : public UAutomatedPerfTestControllerBase`  
_L70-125_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAutomatedPerfTestControllerBase`
- L76 _public prototype_ `virtual void SetupTest() override;`
- L79 _public prototype_ `virtual void RunTest() override;` — `UFUNCTION()`
- L81 _public prototype_ `virtual FString GetPerfTestTypeID() const override;`
- L83 _public prototype_ `virtual void GatherTestMetadata(TArray<TPair<FString, FString>>& OutMetadata) const override;`
- L87 _public prototype_ `void SetUpNextCamera();` — `UFUNCTION()`
- L90 _public prototype_ `void EvaluateCamera();` — `UFUNCTION()`
- L93 _public prototype_ `void FinishCamera();` — `UFUNCTION()`
- L96 _public prototype_ `void ScreenshotCamera();` — `UFUNCTION()`
- L99 _public prototype_ `void NextMap();` — `UFUNCTION()`
- L101 _public prototype_ `virtual TArray<ACameraActor*> GetMapCameraActors();`
- L103 _public prototype_ `ACameraActor* GetCurrentCamera() const;`
- L104 _public prototype_ `FString GetCurrentCameraRegionName() const;`
- L106 _public prototype_ `void MarkCameraStart();`
- L107 _public prototype_ `void MarkCameraEnd();`
- L110 _protected prototype_ `virtual void OnInit() override;`
- L111 _protected prototype_ `virtual void UnbindAllDelegates() override;`
- L112 _protected prototype_ `virtual void TriggerExitAfterDelay() override;`
- L116 _private member_ `TArray<TObjectPtr<ACameraActor>> CamerasToTest;` — `UPROPERTY()`
- L119 _private member_ `TObjectPtr<ACameraActor> CurrentCamera;` — `UPROPERTY()`
- L121 _private member_ `FString CurrentMapName;`
- L122 _private member_ `FSoftObjectPath CurrentMapPath;`
- L123 _private member_ `TArray<FSoftObjectPath> MapsToTest;`
- L124 _private member_ `const UAutomatedStaticCameraPerfTestProjectSettings* Settings;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUTOMATEDPERFTESTING_API`
