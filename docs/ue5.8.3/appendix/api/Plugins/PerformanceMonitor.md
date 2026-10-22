# Plugins / PerformanceMonitor

- module root: `Plugins/Performance/PerformanceMonitor/Source/PerformanceMonitor`
- headers: 1; symbols: 48
- symbol kinds: class=1, function=4, member=24, prototype=18, struct=1
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, RHI, RenderCore

### `Plugins/Performance/PerformanceMonitor/Source/PerformanceMonitor/Private/PerformanceMonitor.h` (Private)


#### class `FPerformanceMonitorModule`  
`class FPerformanceMonitorModule : public IModuleInterface, public FSelfRegisteringExec`  
_L11-105_
- inherits: `IModuleInterface,FSelfRegisteringExec`
- L21 _private member_ `TArray<FString> DesiredStats;`
- L22 _private member_ `TArray<FString> StatGroupsToUse;`
- L24 _private member_ `TArray<TArray<FStatMessage>> StoredMessages;`
- L26 _private member_ `TArray<FStatMessage>ReceivedFramePayload[10];` — Received frame data. Cleared after parsing.
- L28 _private member_ `TMap<FString, TArray<float>> GeneratedStats;`
- L29 _private member_ `FArchive * FileToLogTo;`
- L30 _private member_ `FString LogFileName;`
- L31 _private member_ `FTSTicker::FDelegateHandle TickHandler;`
- L33 _private member_ `bool bRecording;`
- L34 _private member_ `float TimeOfTestStart;`
- L35 _private member_ `float TestTimeOut;`
- L36 _private member_ `float TimeOfLastRecord;`
- L37 _private member_ `float TimeBetweenRecords;`
- L38 _private member_ `int32 NumOfCapturedFrames;`
- L39 _private member_ `int32 NumOfFramesToCapture;`
- L40 _private member_ `FString MapToTest;`
- L41 _private member_ `bool bHasWarnedAboutTime;`
- L42 _private member_ `bool bExitOnCompletion;`
- L43 _private member_ `bool bRequiresCutsceneStart;`
- L44 _private member_ `bool bCvsToolsMode;`
- L48 _public prototype_ `FPerformanceMonitorModule();`
- L49 _public prototype_ `~FPerformanceMonitorModule();`
- L51 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — FSelfRegisteringExec
- L53 _public prototype_ `virtual void StartupModule() override;`
- L55 _public prototype_ `virtual void ShutdownModule() override;`
- L57 _public prototype_ `void Init();`
- L65 _public function_ `static inline FPerformanceMonitorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L75 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L81 _public prototype_ `bool Tick(float DeltaTime);` — [FTickableGameObject] tick function
- L84 _public function_ `bool IsTickable() const` — [FTickableGameObject] tick when recording as long as we are not CDO.
- L87 _public member_ `bool bNewFrameDataReady[10];` — Whether the received frame is ready to be interacted with on the game thread.
- L88 _public prototype_ `void GetDataFromStatsThread(int64 CurrentFrame);`
- L90 _public function_ `bool IsRecordingPerfTimers()`
- L91 _public prototype_ `void StartRecordingPerfTimers(FString FileName, TArray<FString> StatsToRecord);`
- L92 _public prototype_ `void SetRecordInterval(float NewInterval);`
- L94 _public prototype_ `void RecordFrame();`
- L95 _public prototype_ `void GetStatsBreakdown();`
- L96 _public prototype_ `void RecordDataInCvsToolsMode();`
- L97 _public prototype_ `void RecordData();`
- L99 _public prototype_ `float GetAverageOfArray(TArray<float>ArrayToAvg, FString StatName);`
- L101 _public prototype_ `void StopRecordingPerformanceTimers();`
- L102 _public prototype_ `void FinalizeFTestPerfReport();`
- L103 _public prototype_ `void CleanUpPerfFileHandles();`

#### struct `FPerformanceMonitorModule::FStatData`  
`struct FStatData`  
_L14-19_
- desc: Mapping between thread name and stats, where stats are a mapping between name and time
- L16 _public member_ `float StatIncAvg;`
- L17 _public member_ `float StatIncMax;`
- L18 _public member_ `int FrameNum;`
