# Developer / LauncherServices

- module root: `Source/Developer/LauncherServices`
- headers: 26; symbols: 1615
- symbol kinds: class=27, delegate=30, enum=16, enumerator=128, function=541, member=224, namespace=11, prototype=608, struct=5, typedef=25
- PrivateDependencyModuleNames: CoreUObject, DesktopPlatform, Json, SessionMessages, TargetPlatform, TurnkeyIO, UnrealEdMessages, Zen
- PrivateIncludePathModuleNames: DerivedDataCache
- PublicDependencyModuleNames: Core
- PublicIncludePathModuleNames: TargetDeviceServices

### `Source/Developer/LauncherServices/Private/Launcher/Launcher.h` (Private)


#### class `FLauncher`  
`class FLauncher : public ILauncher`  
_L13-26_
- inherits: `ILauncher`
- desc: Implements the game launcher.
- L20 _public prototype_ `virtual ILauncherWorkerPtr Launch(const TSharedRef<ITargetDeviceProxyManager>& DeviceProxyManager, const ILauncherProfileRef& Profile) override;`
- L25 _private member_ `static FThreadSafeCounter WorkerCounter;` — Worker counter, used to generate unique thread names for each worker.

### `Source/Developer/LauncherServices/Private/Launcher/LauncherProjectPath.h` (Private)


#### class `FLauncherProjectPath`  
`class FLauncherProjectPath`  
_L10-24_
- desc: Implements the launcher project path utilities.
- L17 _public prototype_ `static FString GetProjectName(const FString& ProjectPath);` — Gets the name of the Unreal project to use.
- L22 _public prototype_ `static FString GetProjectBasePath(const FString& ProjectPath);` — Gets the base project path for the project (e.g. Samples/Showcases/MyShowcase)

### `Source/Developer/LauncherServices/Private/Launcher/LauncherTask.h` (Private)


#### class `FLauncherTask`  
`class FLauncherTask : public FRunnable , public ILauncherTask`  
_L16-358_
- inherits: `FRunnable,ILauncherTask`
- desc: Abstract base class for launcher tasks.
- L28 _public function_ `FLauncherTask(FString InName, FString InDesc) : Name` — Creates and initializes a new instance. @param InName - The name of the task. @param InDesc - The description of the task.
- L33 _public function_ `virtual ~FLauncherTask() override`
- L50 _public function_ `void AddContinuation( const TSharedPtr<FLauncherTask>& Task )` — Adds a task that will execute after this task completed. Continuations must be added before this task starts. @param Task - The task to add.
- L63 _public function_ `void Execute(const FLauncherTaskChainState* ChainState)` — Executes the tasks. @param ChainState - State data of the task chain.
- L81 _public function_ `virtual const TArray<TSharedPtr<FLauncherTask> >& GetContinuations( ) const` — Gets the list of tasks to be executed after this task. @return Continuation task list.
- L93 _public function_ `bool IsChainFinished( ) const` — Checks whether the task chain has finished execution. A task chain is finished when this task and all its continuations are finished. @return true if the chain is finished, false otherwise.
- L111 _public function_ `bool Succeeded() const`
- L127 _public function_ `int32 ReturnCode() const override`
- L147 _public function_ `virtual bool Init( ) override`
- L152 _public function_ `virtual uint32 Run( ) override`
- L194 _public function_ `virtual void Stop( ) override`
- L199 _public function_ `virtual void Exit( ) override`
- L207 _public function_ `virtual void Cancel() override`
- L219 _public function_ `virtual FTimespan GetDuration( ) const override`
- L234 _public function_ `virtual const FString& GetName( ) const override`
- L239 _public function_ `virtual const FString& GetDesc( ) const override`
- L244 _public function_ `virtual bool IsCancelling() const override`
- L246 _public function_ `virtual ELauncherTaskStatus::Type GetStatus( ) const override`
- L251 _public function_ `virtual bool IsFinished( ) const override`
- L258 _public function_ `virtual FOnTaskStartedDelegate& OnStarted() override`
- L263 _public function_ `virtual FOnTaskCompletedDelegate& OnCompleted() override`
- L268 _public function_ `virtual uint32 GetWarningCount() const override`
- L273 _public function_ `virtual uint32 GetErrorCount() const override`
- L289 _protected prototype_ `virtual bool PerformTask(const FLauncherTaskChainState& ChainState) = 0;` — Performs the actual task. @param ChainState - Holds the state of the task chain. @return true if the task completed successfully, false otherwise.
- L296 _protected function_ `void CancelContinuations( ) const` — Cancels all continuation tasks.
- L307 _protected function_ `void ExecuteContinuations( ) const` — Executes all continuation tasks.
- L318 _private member_ `TArray<TSharedPtr<FLauncherTask> > Continuations;` — Holds the tasks that execute after this task completed.
- L321 _private member_ `FDateTime EndTime;` — Holds the time at which the task ended.
- L324 _private member_ `const FLauncherTaskChainState* LocalChainState = nullptr;` — Holds the local state of this task chain.
- L327 _private member_ `FString Name;` — Holds the task's name.
- L330 _private member_ `FString Desc;` — Holds the task's description
- L333 _private member_ `FDateTime StartTime;` — Holds the time at which the task started.
- L336 _private member_ `ELauncherTaskStatus::Type Status = ELauncherTaskStatus::Pending;` — Holds the status of this task
- L339 _private member_ `bool bCancelling = false;` — set if this should be cancelled
- L342 _private member_ `TUniquePtr<FRunnableThread> Thread;` — Holds the thread that's running this task.
- L345 _private member_ `FOnTaskStartedDelegate TaskStarted;` — message delegates
- L346 _private member_ `FOnTaskCompletedDelegate TaskCompleted;`
- L350 _protected member_ `int32 Result = 0;` — result
- L353 _protected member_ `uint32 ErrorCounter = 0;` — counters
- L354 _protected member_ `uint32 WarningCounter = 0;`
- L357 _protected member_ `static FThreadSafeCounter TaskCounter;` — task counter, used to generate unique thread names for each task

### `Source/Developer/LauncherServices/Private/Launcher/LauncherTaskChainState.h` (Private)


#### struct `FLauncherTaskChainState`  
`struct FLauncherTaskChainState`  
_L12-31_
- desc: Structure for passing launcher task chain state data.
- L15 _public member_ `FString BinariesDirectory;` — The path to the binaries directory (for deployment).
- L18 _public member_ `FString ContentDirectory;` — The path to the content directory (for deployment).
- L21 _public member_ `FString DeployedAppId;` — The identifier of the deployed application.
- L24 _public member_ `FString FileServerAddressListString;` — The list of IP addresses and port numbers at which the file server is reachable.
- L27 _public member_ `ILauncherProfilePtr Profile;` — A pointer to the launcher profile.
- L30 _public member_ `FGuid SessionId;` — The session identifier.

### `Source/Developer/LauncherServices/Private/Launcher/LauncherUATTask.h` (Private)


#### class `FLauncherUATTask`  
`class FLauncherUATTask : public FLauncherTask`  
_L15-115_
- inherits: `FLauncherTask`
- desc: class for UAT launcher tasks.
- L20 _public function_ `FLauncherUATTask(FString InCommandLine, FString InName, FString InDesc, UE::HAL::FWriteHandle InWritePipe, UE::HAL::FProcess& InProcess, ILauncherWorker* InWorker, FString InCommandEnd) : FLauncherTask`
- L39 _protected function_ `virtual bool PerformTask(const FLauncherTaskChainState& ChainState) override` — Performs the actual task. @param ChainState - Holds the state of the task chain. @return true if the task completed successfully, false otherwise.
- L86 _protected function_ `void HandleOutputReceived(const FString& InMessage)`
- L103 _private member_ `FString CommandLine;` — Command line
- L106 _private member_ `UE::HAL::FWriteHandle WritePipe;` — write pipe
- L109 _private member_ `UE::HAL::FProcess& Process;` — process
- L112 _private member_ `FString CommandText;` — The end text marker for this UAT command
- L114 _private member_ `std::atomic_bool EndTextFound = false;`

### `Source/Developer/LauncherServices/Private/Launcher/LauncherWorker.h` (Private)


#### class `FLauncherWorker`  
`class FLauncherWorker : public FRunnable , public ILauncherWorker`  
_L19-199_
- inherits: `FRunnable,ILauncherWorker`
- desc: Implements the launcher's worker thread.
- L32 _public prototype_ `FLauncherWorker(const TSharedRef<ITargetDeviceProxyManager>& InDeviceProxyManager, const ILauncherProfileRef& InProfile, const TCHAR* InWorkerName);` — Creates and initializes a new instance. @param InDeviceProxyManager The target device proxy manager to use. @param InProfile The profile to process. @param InWorkerName The name of the worker thread.
- L34 _public function_ `virtual ~FLauncherWorker() override`
- L46 _public function_ `bool IsValid() const` — Returns whether the worker is valid to run.
- L53 _public prototype_ `virtual bool Init( ) override;`
- L55 _public prototype_ `virtual uint32 Run( ) override;`
- L57 _public prototype_ `virtual void Stop( ) override;`
- L59 _public function_ `virtual void Exit( ) override`
- L63 _public prototype_ `virtual void Cancel( ) override;`
- L65 _public prototype_ `virtual void CancelAndWait( ) override;`
- L67 _public function_ `virtual ELauncherWorkerStatus::Type GetStatus() const override`
- L72 _public prototype_ `virtual int32 GetTasks( TArray<ILauncherTaskPtr>& OutTasks ) const override;`
- L74 _public function_ `virtual FOutputMessageReceivedDelegate& OnOutputReceived() override`
- L79 _public function_ `virtual FOnStageStartedDelegate& OnStageStarted() override`
- L84 _public function_ `virtual FOnStageCompletedDelegate& OnStageCompleted() override`
- L89 _public function_ `virtual FOnLaunchCompletedDelegate& OnCompleted() override`
- L94 _public function_ `virtual FOnLaunchCanceledDelegate& OnCanceled() override`
- L99 _public function_ `virtual ILauncherProfilePtr GetLauncherProfile() const override`
- L105 _public prototype_ `void HandleDeviceProxyManagerProxyRemoved(const TSharedRef<ITargetDeviceProxy>& RemovedProxy, ILauncherProfileUATCommandPtr UnifiedUATCommand);` — Callback for when a device proxy has been removed from the device proxy manager.
- L110 _public function_ `virtual void AddDevicePackagePair(const FString& Device, const FString& Package) override` — Set the app id running on the device
- L119 _public prototype_ `static FString MakeBuildCookRunParamsForProjectCustomBuild(const ILauncherProfileRef& InProfile, const TArray<FString>& InPlatforms);` — Returns best-guess BuildCookRun parameters for the given profile in the format expected by FProjectBuidSettings::BuildCookRunParams Used by the Project custom Build's "import from Project Launcher" menu
- L128 _protected prototype_ `void CreateAndExecuteTasks( const ILauncherProfileRef& InProfile );` — Creates the tasks for the specified profile. @param InProfile - The profile to create tasks for.
- L130 _protected prototype_ `void OnTaskStarted(const FString& TaskName, ILauncherProfileUATCommandPtr UnifiedUATCommand);`
- L131 _protected prototype_ `void OnTaskCompleted(const FString& TaskName);`
- L138 _protected prototype_ `FString CreateUATCommandForBuildCookRun( const ILauncherProfileBuildCookRunRef& InBuildCookRun, const ILauncherProfileRef& InProfile, TArray<FCommandDesc>& OutCommands, FString& OutCommandStart, const FCommandAdjustments& Adjustments, bool bForTurnkeyCustomBuild = false );`
- L140 _protected prototype_ `FString CreateUATCommand( const ILauncherProfileUATCommandRef& InUATCommand, const ILauncherProfileRef& InProfile, const TArray<FString>& InPlatforms, TArray<FCommandDesc>& OutCommands, FString& OutCommandStart, const FCommandAdjustments& Adjustments );`
- L142 _protected prototype_ `FString CreateUATCommandForAutomatedTest( const ILauncherProfileAutomatedTestRef& InAutomatedTest, const ILauncherProfileRef& InProfile, const TArray<FString>& InPlatforms, TArray<FCommandDesc>& OutCommands, FString& OutCommandStart, const FCommandAdjustments& Adjustments );`
- L144 _protected prototype_ `ILauncherProfileUATCommandPtr MakeTemporaryUnifiedRunCommand(const ILauncherProfileRef& InProfile);`
- L145 _protected prototype_ `TArray<FString> FinalizePlatforms( const TArray<FString>& CookPlatforms, const ILauncherDeviceGroupPtr& DeviceGroup, bool bPreferCookedPlatforms ) const;`
- L146 _protected prototype_ `FString FinalizeCommandLine( const FString& CommandLine ) const;`
- L149 _protected prototype_ `void EnableDeviceDiscoveryListener(ILauncherProfileUATCommandPtr UnifiedUATCommand);` — start listening to the device discovery routine
- L152 _protected prototype_ `void DisableDeviceDiscoveryListener();` — stop listening to the device discovery routine
- L155 _protected prototype_ `bool TerminateLaunchedProcess();` — Cancel the currently running application on all devices
- L158 _protected function_ `FLauncherWorker(ENoInit)` — just used by MakeBuildCookRunParamsForProjectCustomBuild
- L163 _private member_ `FCriticalSection CriticalSection;` — Holds a critical section to lock access to selected properties.
- L166 _private member_ `TSharedPtr<ITargetDeviceProxyManager> DeviceProxyManager;` — Holds a pointer  to the device proxy manager.
- L169 _private member_ `ILauncherProfilePtr Profile;` — Holds a pointer to the launcher profile.
- L172 _private member_ `std::atomic<ELauncherWorkerStatus::Type> Status = ELauncherWorkerStatus::Busy;` — Holds the worker's current status.
- L175 _private member_ `TSharedPtr<FLauncherTask> TaskChain;` — Holds the first task in the task chain.
- L176 _private member_ `FLauncherTaskChainState ChainState;`
- L178 _private member_ `TUniquePtr<FRunnableThread> Thread;`
- L181 _private member_ `UE::HAL::FInputPipe InputPipe;` — Holds the input pipe and the running UAT process.
- L182 _private member_ `UE::HAL::FProcess Process;`
- L184 _private member_ `double StageStartTime = 0.0;`
- L185 _private member_ `double LaunchStartTime = 0.0;`
- L188 _private member_ `FOutputMessageReceivedDelegate OutputMessageReceived;` — message delegate
- L189 _private member_ `FOnStageStartedDelegate StageStarted;`
- L190 _private member_ `FOnStageCompletedDelegate StageCompleted;`
- L191 _private member_ `FOnLaunchCompletedDelegate LaunchCompleted;`
- L192 _private member_ `FOnLaunchCanceledDelegate LaunchCanceled;`
- L195 _private member_ `FDelegateHandle OnProxyRemovedDelegateHandle;` — delegate for device discovery (device removed)
- L198 _private member_ `TMap<FString, FString> CachedDevicePackagePair;` — Dictionary holding the appid@device pairs from the last launch

#### struct `FLauncherWorker::FCommandAdjustments`  
`struct FCommandAdjustments`  
_L133-137_
- L135 _public member_ `bool bDisableRun = false;`
- L136 _public member_ `bool bPreferCookedPlatforms = false;`

### `Source/Developer/LauncherServices/Private/Profiles/LauncherDeviceGroup.h` (Private)


#### class `FLauncherDeviceGroup`  
`class FLauncherDeviceGroup : public TSharedFromThis<FLauncherDeviceGroup> , public ILauncherDeviceGroup`  
_L12-118_
- inherits: `TSharedFromThis<FLauncherDeviceGroup>,ILauncherDeviceGroup`
- desc: Implements a group of devices for the Launcher user interface.
- L21 _public function_ `FLauncherDeviceGroup()` — Default constructor.
- L29 _public function_ `FLauncherDeviceGroup(const FGuid& InId, const FString& InName) : Id(InId) , Name(InName)` — Creates and initializes a new instance. @param InId - The unique group identifier. @param InName - The name of the group.
- L38 _public function_ `virtual void AddDevice(const FString& DeviceID) override`
- L45 _public function_ `virtual const TArray<FString>& GetDeviceIDs() override`
- L50 _public function_ `virtual FGuid GetId() const override`
- L55 _public function_ `virtual const FString& GetName() const override`
- L60 _public function_ `virtual int32 GetNumDevices() const override`
- L65 _public function_ `virtual FOnLauncherDeviceGroupDeviceAdded& OnDeviceAdded() override`
- L70 _public function_ `virtual FOnLauncherDeviceGroupDeviceRemoved& OnDeviceRemoved() override`
- L75 _public function_ `virtual void RemoveDevice(const FString& DeviceID) override`
- L82 _public function_ `virtual void RemoveAllDevices() override`
- L93 _public function_ `virtual void SetName(const FString& NewName) override`
- L103 _private member_ `TArray<FString> Devices;` — Holds the devices that are part of this group.
- L106 _private member_ `FGuid Id;` — Holds the group's unique identifier.
- L109 _private member_ `FString Name;` — Holds the human readable name of this group.
- L114 _private member_ `FOnLauncherDeviceGroupDeviceAdded DeviceAddedDelegate;` — Holds a delegate to be invoked when a device was added to this group.
- L117 _private member_ `FOnLauncherDeviceGroupDeviceRemoved DeviceRemovedDelegate;` — Holds a delegate to be invoked when a device was removed from this group.

### `Source/Developer/LauncherServices/Private/Profiles/LauncherProfile.h` (Private)


#### enum `ESimpleLauncherVersion`  
`enum ESimpleLauncherVersion`  
_L31-35_
- L33 _public enumerator_ `LAUNCHERSERVICES_SIMPLEPROFILEVERSION=1`
- L34 _public enumerator_ `LAUNCHERSERVICES_SIMPLEFILEFORMATCHANGE = 2`

#### class `FLauncherSimpleProfile`  
`class FLauncherSimpleProfile final : public ILauncherSimpleProfile`  
_L40-171_
- inherits: `ILauncherSimpleProfile`
- desc: Implements a simple profile which controls the desired output of the Launcher for simple
- L45 _public function_ `FLauncherSimpleProfile(const FString& InDeviceName) : DeviceName(InDeviceName)`
- L53 _public function_ `virtual const FString& GetDeviceName() const override`
- L58 _public function_ `virtual FName GetDeviceVariant() const override`
- L63 _public function_ `virtual EBuildConfiguration GetBuildConfiguration() const override`
- L68 _public function_ `virtual ELauncherProfileCookModes::Type GetCookMode() const override`
- L73 _public function_ `virtual void SetDeviceName(const FString& InDeviceName) override`
- L81 _public function_ `virtual void SetDeviceVariant(FName InVariant) override`
- L86 _public function_ `virtual void SetBuildConfiguration(EBuildConfiguration InConfiguration) override`
- L91 _public function_ `virtual void SetCookMode(ELauncherProfileCookModes::Type InMode) override`
- L97 _public function_ `virtual bool Serialize(FArchive& Archive) override` — `UE_DEPRECATED(5.8, "this will be removed. there is no alternative implementation : ILauncherSimpleProfile is designed to be transient")`
- L117 _public function_ `virtual void Save(TJsonWriter<>& Writer) override`
- L130 _public function_ `virtual bool Load(const FJsonObject& Object) override`
- L146 _public function_ `virtual void SetDefaults() override`
- L161 _private member_ `FString DeviceName;` — Holds the name of the device this simple profile is for
- L164 _private member_ `FName Variant;` — Holds the name of the device variant.
- L167 _private member_ `EBuildConfiguration BuildConfiguration;` — Holds the desired build configuration (only used if creating new builds).
- L170 _private member_ `TEnumAsByte<ELauncherProfileCookModes::Type> CookMode;` — Holds the cooking mode.

#### class `FLauncherProfile`  
`class FLauncherProfile final : public ILauncherProfile , public TSharedFromThis<FLauncherProfile>`  
_L177-3112_
- inherits: `ILauncherProfile,TSharedFromThis<FLauncherProfile>`
- desc: Implements a profile which controls the desired output of the Launcher
- L188 _public function_ `static FString GetProfileFolder(bool bNotForLicensees)` — Gets the folder in which profile files are stored. @return The folder path.
- L200 _public function_ `FLauncherProfile(ILauncherProfileManagerRef ProfileManager) : LauncherProfileManager(ProfileManager)` — Default constructor.
- L211 _public function_ `FLauncherProfile(ILauncherProfileManagerRef ProfileManager, FGuid InId, const FString& InProfileName) : LauncherProfileManager(ProfileManager) , Id(InId) , Name(InProfileName)` — Creates and initializes a new instance. @param InProfileName - The name of the profile.
- L222 _public function_ `~FLauncherProfile( )` — Destructor.
- L250 _public function_ `virtual void AddCookedCulture( const FString& CultureName ) override`
- L256 _public function_ `virtual void AddCookedMap( const FString& MapName ) override`
- L262 _public function_ `virtual void AddCookedPlatform( const FString& PlatformName ) override`
- L270 _public function_ `virtual void SetDefaultDeployPlatform(const FName PlatformName) override`
- L276 _public function_ `virtual void ClearCookedCultures( ) override`
- L282 _public function_ `virtual void ClearCookedMaps( ) override`
- L288 _public function_ `virtual void ClearCookedPlatforms( ) override`
- L296 _public function_ `virtual ILauncherProfileLaunchRolePtr CreateLaunchRole( ) override`
- L302 _public function_ `virtual EBuildConfiguration GetBuildConfiguration( ) const override`
- L308 _public function_ `virtual bool HasBuildTargetSpecified() const override`
- L314 _public function_ `virtual FString GetBuildTarget() const override`
- L330 _public function_ `virtual EBuildConfiguration GetCookConfiguration( ) const override`
- L336 _public function_ `virtual ELauncherProfileCookModes::Type GetCookMode( ) const override`
- L342 _public function_ `virtual const FString& GetCookOptions( ) const override`
- L348 _public function_ `virtual const TArray<FString>& GetCookedCultures( ) const override`
- L354 _public function_ `virtual const bool GetSkipCookingEditorContent() const override`
- L360 _public function_ `virtual const TArray<FString>& GetCookedMaps( ) const override`
- L366 _public function_ `virtual const TArray<FString>& GetCookedPlatforms( ) const override`
- L372 _public function_ `virtual const ILauncherProfileLaunchRoleRef& GetDefaultLaunchRole( ) const override`
- L378 _public function_ `virtual ILauncherDeviceGroupPtr GetDeployedDeviceGroup( ) override`
- L384 _public function_ `virtual const FName GetDefaultDeployPlatform() const override`
- L390 _public function_ `virtual bool IsGeneratingPatch() const override`
- L396 _public function_ `virtual bool ShouldAddPatchLevel() const override`
- L402 _public function_ `virtual bool ShouldStageBaseReleasePaks() const override`
- L407 _public function_ `virtual bool IsCreatingDLC() const override`
- L412 _public function_ `virtual void SetCreateDLC(bool InBuildDLC) override`
- L418 _public function_ `virtual FString GetDLCName() const override`
- L423 _public function_ `virtual void SetDLCName(const FString& InDLCName) override`
- L429 _public function_ `virtual bool IsDLCIncludingEngineContent() const`
- L434 _public function_ `virtual void SetDLCIncludeEngineContent(bool InDLCIncludeEngineContent)`
- L442 _public function_ `virtual bool IsCreatingReleaseVersion() const override`
- L448 _public function_ `virtual void SetCreateReleaseVersion(bool InCreateReleaseVersion) override`
- L454 _public function_ `virtual FString GetCreateReleaseVersionName() const override`
- L460 _public function_ `virtual void SetCreateReleaseVersionName(const FString& InCreateReleaseVersionName) override`
- L467 _public function_ `virtual FString GetBasedOnReleaseVersionName() const override`
- L473 _public function_ `virtual void SetBasedOnReleaseVersionName(const FString& InBasedOnReleaseVersionName) override`
- L479 _public function_ `virtual FString GetOriginalReleaseVersionName() const override`
- L485 _public function_ `virtual void SetOriginalReleaseVersionName(const FString& InOriginalReleaseVersionName) override`
- L491 _public function_ `virtual FString GetReferenceContainerGlobalFileName() const override`
- L496 _public function_ `virtual void SetReferenceContainerGlobalFileName(const FString& InReferenceContainerGlobalFileName) override`
- L501 _public function_ `virtual FString GetReferenceContainerCryptoKeysFileName() const override`
- L506 _public function_ `virtual void SetReferenceContainerCryptoKeysFileName(const FString& InReferenceContainerCryptoKeysFileName) override`
- L512 _public function_ `virtual ELauncherProfileDeploymentModes::Type GetDeploymentMode( ) const override`
- L518 _public function_ `virtual bool GetForceClose() const override`
- L524 _public function_ `virtual FGuid GetId( ) const override`
- L529 _public function_ `virtual void AssignId( bool bOverrideExisting ) override`
- L538 _public function_ `virtual FString GetFileName() const override`
- L544 _public function_ `virtual FString GetFilePath() const override`
- L549 _public function_ `virtual ELauncherProfileLaunchModes::Type GetLaunchMode( ) const override`
- L555 _public function_ `virtual const TArray<ILauncherProfileLaunchRolePtr>& GetLaunchRoles( ) const override`
- L561 _public function_ `virtual const int32 GetLaunchRolesFor( const FString& DeviceId, TArray<ILauncherProfileLaunchRolePtr>& OutRoles ) override`
- L567 _public function_ `virtual FString GetName( ) const override`
- L572 _public function_ `virtual FString GetDescription() const override`
- L577 _public function_ `virtual ELauncherProfilePackagingModes::Type GetPackagingMode( ) const override`
- L583 _public function_ `virtual FString GetPackageDirectory( ) const override`
- L589 _public function_ `virtual bool IsArchiving( ) const override`
- L595 _public function_ `virtual FString GetArchiveDirectory( ) const override`
- L601 _public function_ `virtual bool HasProjectSpecified() const override`
- L606 _public function_ `virtual FString GetProjectName() const override`
- L616 _public function_ `virtual FString GetProjectBasePath() const override`
- L625 _public function_ `virtual FString GetProjectPath() const override`
- L634 _public function_ `virtual uint32 GetTimeout() const override`
- L640 _public function_ `virtual bool HasValidationError(ILauncherProfileUATCommandPtr UATCommand) const override`
- L646 _public function_ `virtual bool HasValidationError( ELauncherProfileValidationErrors::Type Error, ILauncherProfileUATCommandPtr UATCommand ) const override`
- L652 _public function_ `virtual void AddCustomError( const FString& UniqueId, const FText& Text, ILauncherProfileUATCommandPtr UATCommand ) override`
- L661 _public function_ `virtual bool HasCustomError( const FString& UniqueId, ILauncherProfileUATCommandPtr UATCommand ) const override`
- L667 _public function_ `virtual FText GetCustomErrorText( const FString& UniqueId, ILauncherProfileUATCommandPtr UATCommand ) const override`
- L674 _public function_ `virtual TArray<FString> GetAllCustomErrors(ILauncherProfileUATCommandPtr UATCommand) const override`
- L687 _public function_ `virtual void AddCustomWarning( const FString& UniqueId, const FText& Text, ILauncherProfileUATCommandPtr UATCommand ) override`
- L696 _public function_ `virtual bool HasCustomWarning( const FString& UniqueId, ILauncherProfileUATCommandPtr UATCommand ) const override`
- L702 _public function_ `virtual FText GetCustomWarningText( const FString& UniqueId, ILauncherProfileUATCommandPtr UATCommand ) const override`
- L709 _public function_ `virtual TArray<FString> GetAllCustomWarnings(ILauncherProfileUATCommandPtr UATCommand) const override`
- L720 _public function_ `virtual void RefreshCustomWarningsAndErrors(ILauncherProfileUATCommandPtr UATCommand) override`
- L741 _public function_ `virtual FString GetInvalidPlatform(ILauncherProfileUATCommandPtr UATCommand) const override`
- L747 _public function_ `virtual ELauncherProfileBuildModes::Type GetBuildMode() const override`
- L753 _public function_ `virtual bool ShouldBuild() override`
- L759 _public function_ `virtual bool IsFastIterate() const override`
- L765 _public function_ `virtual bool IsBuildingUAT() const override`
- L770 _public function_ `virtual FString GetAdditionalCommandLineParameters() const override`
- L776 _public function_ `virtual FString GetAdditionalTargetCommandLineParameters( EBuildTargetType BuildTargetType ) const override`
- L782 _public function_ `virtual bool IsCookingIncrementally( ) const override`
- L788 _public function_ `virtual ELauncherProfileIncrementalCookMode::Type GetIncrementalCookMode() const override`
- L795 _public function_ `virtual bool IsIterateSharedCookedBuild() const override`
- L801 _public function_ `virtual bool IsCompressed() const override`
- L807 _public function_ `virtual bool IsEncryptingIniFiles() const override`
- L813 _public function_ `virtual bool IsForDistribution() const override`
- L819 _public function_ `virtual bool IsCookingUnversioned( ) const override`
- L825 _public function_ `virtual bool IsDeployablePlatform( const FString& PlatformName ) override`
- L831 _public function_ `virtual bool IsDeployingIncrementally( ) const override`
- L837 _public function_ `virtual bool IsFileServerHidden( ) const override`
- L843 _public function_ `virtual bool IsFileServerStreaming( ) const override`
- L849 _public function_ `virtual bool IsPackingWithUnrealPak( ) const override`
- L855 _public function_ `virtual bool IsIncludingPrerequisites() const override`
- L861 _public function_ `virtual bool IsGeneratingChunks() const override`
- L867 _public function_ `virtual bool IsGenerateHttpChunkData() const override`
- L873 _public function_ `virtual FString GetHttpChunkDataDirectory() const override`
- L879 _public function_ `virtual FString GetHttpChunkDataReleaseName() const override`
- L885 _public function_ `virtual bool IsValidForLaunch( ) override`
- L903 _public function_ `virtual void RemoveCookedCulture( const FString& CultureName ) override`
- L911 _public function_ `virtual void RemoveCookedMap( const FString& MapName ) override`
- L919 _public function_ `virtual void RemoveCookedPlatform( const FString& PlatformName ) override`
- L928 _public function_ `virtual void RemoveLaunchRole( const ILauncherProfileLaunchRoleRef& Role ) override`
- L937 _public prototype_ `virtual bool Serialize( FArchive& Archive ) override;` — `UE_DEPRECATED(5.8, "please use the Json Save/Load API instead")`
- L939 _public function_ `virtual void Save(TJsonWriter<>& Writer) override`
- L974 _public function_ `void SaveUATParams(TJsonWriter<>& Writer)`
- L1390 _public function_ `TMap<FString, FString> ParseCommands(FString CommandLine)`
- L1424 _public function_ `TArray<FString> FindPlatforms()`
- L1466 _public function_ `bool FindAllPlatforms(TArray<FString>& ServerPlatforms, TArray<FString>& ClientPlatforms, FString& OptionalParams)`
- L1501 _public function_ `virtual bool Load(const FJsonObject& Object) override`
- L1627 _public function_ `virtual void SetDefaults( ) override`
- L1686 _public function_ `virtual void SetBuildMode(ELauncherProfileBuildModes::Type Mode) override`
- L1692 _public function_ `virtual void SetFastIterate(bool Enable) override`
- L1698 _public function_ `virtual void SetBuildUAT(bool Build) override`
- L1708 _public function_ `virtual void SetAdditionalCommandLineParameters(const FString& Params) override`
- L1714 _public function_ `virtual void SetAdditionalTargetCommandLineParameters(const FString& Params, EBuildTargetType BuildTargetType ) override`
- L1722 _public function_ `virtual void SetBuildConfiguration( EBuildConfiguration Configuration ) override`
- L1728 _public function_ `virtual void SetBuildTargetSpecified(bool Specified) override`
- L1734 _public function_ `virtual void FallbackBuildTargetUpdated() override`
- L1743 _public function_ `virtual void SetBuildTarget( const FString& TargetName ) override`
- L1760 _public function_ `virtual void SetCookConfiguration( EBuildConfiguration Configuration ) override`
- L1766 _public function_ `virtual void SetCookMode( ELauncherProfileCookModes::Type Mode ) override`
- L1772 _public function_ `virtual void SetCookOptions(const FString& Options) override`
- L1778 _public function_ `virtual void SetSkipCookingEditorContent(const bool InSkipCookingEditorContent) override`
- L1784 _public function_ `virtual void SetDeployWithUnrealPak( bool UseUnrealPak ) override`
- L1790 _public function_ `virtual void SetGenerateChunks(bool bInGenerateChunks) override`
- L1796 _public function_ `virtual void SetGenerateHttpChunkData(bool bInGenerateHttpChunkData) override`
- L1802 _public function_ `virtual void SetHttpChunkDataDirectory(const FString& InHttpChunkDataDirectory) override`
- L1808 _public function_ `virtual void SetHttpChunkDataReleaseName(const FString& InHttpChunkDataReleaseName) override`
- L1814 _public function_ `virtual void SetDeployedDeviceGroup( const ILauncherDeviceGroupPtr& DeviceGroup ) override`
- L1820 _public function_ `virtual FIsCookFinishedDelegate& OnIsCookFinished() override`
- L1825 _public function_ `virtual FCookCanceledDelegate& OnCookCanceled() override`
- L1830 _public function_ `virtual void SetDeploymentMode( ELauncherProfileDeploymentModes::Type Mode ) override`
- L1836 _public function_ `virtual void SetForceClose( bool Close ) override`
- L1842 _public function_ `virtual void SetHideFileServerWindow( bool Hide ) override`
- L1848 _public function_ `virtual void SetIncrementalCooking( bool Incremental ) override`
- L1854 _public function_ `virtual void SetIncrementalCookMode( ELauncherProfileIncrementalCookMode::Type Mode ) override`
- L1862 _public function_ `virtual void SetIterateSharedCookedBuild( bool SharedCookedBuild ) override`
- L1868 _public function_ `virtual void SetCompressed( bool Enabled ) override`
- L1874 _public function_ `virtual void SetForDistribution(bool Enabled)override`
- L1880 _public function_ `virtual void SetEncryptingIniFiles(bool Enabled) override`
- L1886 _public function_ `virtual void SetIncrementalDeploying( bool Incremental ) override`
- L1892 _public function_ `virtual void SetLaunchMode( ELauncherProfileLaunchModes::Type Mode ) override`
- L1898 _public function_ `virtual void SetName( const FString& NewName ) override`
- L1908 _public function_ `virtual void SetDescription(const FString& NewDescription) override`
- L1918 _public function_ `virtual void SetNotForLicensees() override`
- L1923 _public function_ `virtual void SetPackagingMode( ELauncherProfilePackagingModes::Type Mode ) override`
- L1929 _public function_ `virtual void SetPackageDirectory( const FString& Dir ) override`
- L1935 _public function_ `virtual void SetArchive( bool bInArchive ) override`
- L1941 _public function_ `virtual void SetArchiveDirectory( const FString& Dir ) override`
- L1947 _public function_ `virtual void SetProjectSpecified(bool Specified) override`
- L1960 _public function_ `virtual void FallbackProjectUpdated() override`
- L1971 _public function_ `virtual void SetProjectPath( const FString& Path ) override`
- L2009 _public function_ `virtual void SetStreamingFileServer( bool Streaming ) override`
- L2015 _public function_ `virtual void SetIncludePrerequisites(bool InValue) override`
- L2021 _public function_ `virtual void SetTimeout( uint32 InTime ) override`
- L2027 _public function_ `virtual void SetUnversionedCooking( bool Unversioned ) override`
- L2033 _public function_ `virtual void SetGeneratePatch( bool InGeneratePatch ) override`
- L2039 _public function_ `virtual void SetAddPatchLevel( bool InAddPatchLevel) override`
- L2045 _public function_ `virtual void SetStageBaseReleasePaks(bool InStageBaseReleasePaks) override`
- L2050 _public function_ `virtual bool SupportsEngineMaps( ) const override`
- L2055 _public function_ `virtual FOnProfileProjectChanged& OnProjectChanged() override`
- L2060 _public function_ `virtual FOnProfileBuildTargetOptionsChanged& OnBuildTargetOptionsChanged() override`
- L2065 _public function_ `virtual FOnProfileCustomValidation& OnCustomValidation() override`
- L2070 _public function_ `virtual FOnProfileCustomUATCommandValidation& OnCustomUATCommandValidation() override`
- L2075 _public function_ `virtual void SetEditorExe( const FString& InEditorExe ) override`
- L2080 _public function_ `virtual FString GetEditorExe( ) const override`
- L2085 _public function_ `virtual void SetUseIoStore(bool bInUseIoStore) override`
- L2091 _public function_ `virtual bool IsUsingIoStore() const override`
- L2097 _public function_ `virtual void SetUseZenStore(bool bInUseZenStore) override`
- L2103 _public function_ `virtual bool IsUsingZenStore() const override`
- L2109 _public prototype_ `virtual int32 GetZenSnapshot() override;`
- L2111 _public function_ `virtual void SetImportingZenSnapshot( bool Import ) override`
- L2117 _public function_ `virtual bool IsImportingZenSnapshot() const override`
- L2123 _public function_ `virtual void SetUseZenPakStreaming( bool UseZenPakStreaming ) override`
- L2129 _public function_ `virtual bool IsUsingZenPakStreaming() const override`
- L2135 _public function_ `virtual void SetZenPakStreamingPath( const FString& Path ) override`
- L2141 _public function_ `virtual FString GetZenPakStreamingPath() const override`
- L2147 _public function_ `virtual void SetShouldUpdateDeviceFlash(bool bInShouldUpdateFlash) override`
- L2155 _public function_ `virtual bool ShouldUpdateDeviceFlash() const override` — Whether or not the flash image/software on the device should attempt to be updated before running
- L2160 _public function_ `virtual void SetDeviceIsASimulator(bool bInIsDeviceASimualtor) override`
- L2169 _public function_ `virtual bool IsDeviceASimulator() const override` — Is the Launch device actually a simulator?
- L2175 _public function_ `virtual void SetMakeBinaryConfig(bool bInMakeBinaryConfig) override`
- L2181 _public function_ `virtual bool MakeBinaryConfig() const override`
- L2187 _public function_ `virtual TArray<FString> GetExplicitBuildTargetNames() const override`
- L2192 _public function_ `virtual bool RequiresExplicitBuildTargetName() const override`
- L2197 _public function_ `virtual void SetClientArchitectures( const TArray<FString>& InArchitectures )`
- L2203 _public function_ `virtual const TArray<FString>& GetClientArchitectures() const override`
- L2209 _public function_ `virtual void SetServerArchitectures( const TArray<FString>& InArchitectures )`
- L2215 _public function_ `virtual const TArray<FString>& GetServerArchitectures() const override`
- L2221 _public function_ `virtual void SetEditorArchitectures( const TArray<FString>& InArchitectures )`
- L2227 _public function_ `virtual const TArray<FString>& GetEditorArchitectures() const override`
- L2233 _public function_ `virtual TMap<FString,FString>& GetCustomStringProperties() override`
- L2238 _public function_ `virtual TMap<FString, bool>& GetCustomBoolProperties() override`
- L2243 _public function_ `virtual const TArray<ILauncherProfileAutomatedTestRef> GetAutomatedTests() const override`
- L2258 _public function_ `virtual ILauncherProfileAutomatedTestPtr GetAutomatedTest( const TCHAR* InternalName ) const override`
- L2264 _public function_ `virtual ILauncherProfileAutomatedTestRef FindOrAddAutomatedTest( const TCHAR* InternalName, const TCHAR* UserTypeName ) override`
- L2285 _public function_ `virtual void RemoveAutomatedTest( const TCHAR* InternalName ) override`
- L2290 _public function_ `virtual void SetAutomatedTestBuildPath( const FString& InAutomatedTestBuildPath )`
- L2294 _public function_ `virtual const FString& GetAutomatedTestBuildPath() const`
- L2299 _public function_ `virtual void SetIsUsingAutomatedTestBuild( bool bInWantAutomatedTestBuild ) override`
- L2303 _public function_ `virtual bool IsUsingAutomatedTestBuild() const override`
- L2312 _public function_ `virtual const TArray<ILauncherProfileBuildCookRunRef> GetBuildCookRunCommands() const override`
- L2328 _public function_ `virtual ILauncherProfileBuildCookRunPtr GetBuildCookRunCommand( const TCHAR* InternalName ) const override`
- L2334 _public function_ `virtual ILauncherProfileBuildCookRunRef FindOrAddBuildCookRunCommand( const TCHAR* InternalName, const TCHAR* UserTypeName ) override`
- L2365 _public function_ `virtual const TArray<ILauncherProfileUATCommandRef>& GetUATCommands() const override`
- L2370 _public function_ `virtual ILauncherProfileUATCommandPtr GetUATCommand( const TCHAR* InternalName ) const`
- L2381 _public function_ `virtual ILauncherProfileUATCommandRef FindOrAddUATCommand( const TCHAR* InternalName, const TCHAR* UserTypeName ) override`
- L2404 _public function_ `virtual void RemoveUATCommand( const TCHAR* InternalName ) override`
- L2422 _public function_ `virtual FOnLauncherProfileUATCommandChanged& OnUATCommandAdded() override`
- L2427 _public function_ `virtual FOnLauncherProfileUATCommandChanged& OnUATCommandRemoved() override`
- L2437 _public function_ `virtual TArray<FString> GetBuildTargets() const`
- L2443 _public function_ `virtual void AddBuildTarget( const FString& InBuildTarget )`
- L2450 _public function_ `virtual void RemoveBuildTarget( const FString& InBuildTarget )`
- L2457 _public function_ `virtual void ClearBuildTargets()`
- L2465 _public function_ `virtual bool SupportsLegacyProjectLauncher() const override`
- L2470 _public function_ `virtual ILauncherProfileBuildCookRunPtr GetFirstBuildCookRun() const override`
- L2487 _protected function_ `void Validate( )` — Validates the profile's current settings. Possible validation errors and warnings can be retrieved using the HasValidationError() method. @return true if the profile passed validation, false otherwise.
- L2522 _protected function_ `void Validate(const ILauncherProfileBuildCookRunRef& BuildCookRun)`
- L2698 _protected function_ `void ValidatePlatformSDKs(const ILauncherProfileBuildCookRunRef& BuildCookRun)`
- L2768 _protected function_ `void ValidateDeviceStatus(const ILauncherProfileBuildCookRunRef& BuildCookRun)`
- L2796 _protected function_ `void ValidateBuildTarget(const ILauncherProfileBuildCookRunRef& BuildCookRun)`
- L2888 _protected function_ `void RefreshValidBuildTargets()`
- L2924 _protected function_ `TSet<EBuildTargetType> GetCookTargetTypes(const ILauncherProfileBuildCookRunRef& BuildCookRun) const`
- L2950 _protected function_ `void OnSelectedProjectChanged()`
- L2958 _private function_ `FValidationData* GetValidationData(ILauncherProfileUATCommandPtr UATCommand)`
- L2976 _private function_ `const FValidationData* GetValidationData(ILauncherProfileUATCommandPtr UATCommand) const`
- L2995 _private function_ `FString GetUniqueUATCommandName( const TCHAR* Base ) const`
- L3008 _private prototype_ `ILauncherProfileUATCommandRef CreateUATCommandInternal( const TCHAR* InternalName, const TCHAR* UserTypeName );`
- L3009 _private prototype_ `ILauncherProfileAutomatedTestRef CreateAutomatedTestInternal( const TCHAR* InternalName, const TCHAR* UserTypeName );`
- L3010 _private prototype_ `ILauncherProfileBuildCookRunRef CreateBuildCookRunInternal( const TCHAR* InternalName, const TCHAR* UserTypeName );`
- L3011 _private prototype_ `ILauncherProfileUATCommandPtr CreateUATCommandByTypeNameInternal( const TCHAR* TypeName, const TCHAR* InternalName );`
- L3012 _private prototype_ `ILauncherProfileBuildCookRunPtr LoadBuildCookRunInternal(const FJsonObject& Object, int32 Version);`
- L3014 _private function_ `void AddUATCommandInternal( const ILauncherProfileUATCommandRef& UATCommand )`
- L3021 _private prototype_ `void QueryZenSnapshotsForProject();`
- L3022 _private prototype_ `TSharedPtr<UE::Zen::Build::FBuildListRetriever> GetBuildListRetriever();`
- L3025 _private member_ `ILauncherProfileManagerRef LauncherProfileManager;` — Holds a reference to the launcher profile manager.
- L3029 _private member_ `bool BuildUAT;` — Holds a flag indicating whether UAT should be built
- L3031 _private member_ `bool StageBaseReleasePaks;` — This build stages pak files from the release version it is based on (deprecated)
- L3033 _private member_ `FGuid Id;` — Holds the profile's unique identifier.
- L3035 _private member_ `FString Name;` — Holds the profile's name.
- L3038 _private member_ `FString Description;` — Holds the profile's description.
- L3040 _private member_ `bool ProjectSpecified;` — Holds a flag indicating whether the project is specified by this profile.
- L3043 _private member_ `FString FullProjectPath;` — Holds the full absolute path to the Unreal project used by this profile.
- L3047 _private member_ `FString ShareableProjectPath;` — Holds the path that might be shareable between people.  Only works if the project is under the UE root. otherwise this is an absolute path.
- L3050 _private member_ `FValidationData ProfileValidation;` — Profile validation
- L3051 _private member_ `TMap<ILauncherProfileUATCommandPtr, FValidationData> UATCommandValidation;`
- L3054 _private member_ `FString EditorExe;` — Path to the editor executable to pass to UAT, for cooking, etc... May be empty.
- L3057 _private member_ `bool bNotForLicensees;` — Profile is for an internal project
- L3060 _private member_ `bool bShouldUpdateFlash;` — Update flash on device before running
- L3063 _private member_ `TMap<FString,FString> CustomStringProperties;` — Key-Value pairs for extsibility. Not user-facing.
- L3064 _private member_ `TMap<FString, bool> CustomBoolProperties;`
- L3067 _private member_ `FString AutomatedTestBuildPath;` — Automated tests
- L3068 _private member_ `bool bWantAutomatedTestBuild;`
- L3071 _private member_ `TArray<ILauncherProfileUATCommandRef> UATCommands;` — Extra UAT commands
- L3072 _private member_ `FOnLauncherProfileUATCommandChanged UATCommandAdded;`
- L3073 _private member_ `FOnLauncherProfileUATCommandChanged UATCommandRemoved;`
- L3079 _private member_ `TSharedPtr<ILauncherProfileBuildCookRun> FirstBuildCookRun;` — Cache of the first BuildCookRun command in the list, for convenience & for backwards compatibilty with Legacy Project Launcher NOTE: a profile is not guaranteed to have a BuildCookRun command - it can be deleted
- L3082 _private member_ `FIsCookFinishedDelegate IsCookFinishedDelegate;` — cook in the editor callbacks (not valid for any other cook mode)
- L3083 _private member_ `FCookCanceledDelegate CookCanceledDelegate;`
- L3086 _private member_ `FOnLauncherProfileDeployedDeviceGroupChanged DeployedDeviceGroupChangedDelegate;` — Holds a delegate to be invoked when changing the device group to deploy to.
- L3089 _private member_ `FOnProfileProjectChanged ProjectChangedDelegate;` — Holds a delegate to be invoked when the project has changed
- L3092 _private member_ `FOnProfileBuildTargetOptionsChanged BuildTargetOptionsChangedDelegate;` — Holds a delegate to be invoked when the project build target options have changed
- L3095 _private member_ `FOnProfileCustomValidation CustomValidationDelegate;` — Holds a delegate to be invoked when the profile is validated to gather custom warnings and errors
- L3096 _private member_ `FOnProfileCustomUATCommandValidation CustomUATCommandValidationDelegate;`
- L3099 _private member_ `TArray<FString> ExplictBuildTargetNames;` — Cached build target options (not serialized)
- L3102 _private member_ `static TSharedPtr<UE::Zen::Build::FBuildListRetriever> BuildListRetriever;` — Utility class instance used to query build list
- L3105 _private typedef_ `typedef TMap<FString, int32> FPlatformToBuildsMap;` — Cache all builds for projects and platforms, shared between profiles
- L3106 _private member_ `static TMap<FString, FPlatformToBuildsMap> PerProjectBuilds;`

#### struct `FLauncherProfile::FValidationData`  
`struct FValidationData`  
_L227-244_
- L229 _public function_ `void Reset()`
- L238 _public member_ `TArray<ELauncherProfileValidationErrors::Type> Errors;` — Holds the collection of validation errors.
- L239 _public member_ `FString InvalidPlatform;`
- L242 _public member_ `TMap<FString,FText> CustomErrors;` — Holds the collection of custom errors & warnings.
- L243 _public member_ `TMap<FString,FText> CustomWarnings;`

#### Free symbols / members of external scopes

- L2373 _function_ `` (scope `FLauncherProfile::GetUATCommand`)

### `Source/Developer/LauncherServices/Private/Profiles/LauncherProfileAutomatedTest.h` (Private)


#### class `FLauncherProfileAutomatedTest`  
`class FLauncherProfileAutomatedTest final : public ILauncherProfileAutomatedTest, public TSharedFromThis<FLauncherProfileAutomatedTest>`  
_L12-233_
- inherits: `ILauncherProfileAutomatedTest,TSharedFromThis<FLauncherProfileAutomatedTest>`
- L15 _public member_ `static const TCHAR* TypeName;`
- L17 _public function_ `FLauncherProfileAutomatedTest( TSharedPtr<FLauncherProfile> InProfile, const TCHAR* InInternalName = TEXT(""), const TCHAR* InUserTypeName = TEXT("") ) : Profile(InProfile) , InternalName(InInternalName) , UserTypeName(InUserTypeName)`
- L25 _public function_ `FLauncherProfileAutomatedTest( FArchive& Archive )` — `UE_DEPRECATED(5.8, "please use the Json Save/Load API")`
- L32 _public function_ `virtual void SetUATCommand( const TCHAR* InUATCommand ) override`
- L41 _public function_ `virtual const FString& GetUATCommand() const override`
- L46 _public function_ `virtual void SetTests( const TCHAR* InTests ) override`
- L54 _public function_ `virtual const FString& GetTests() const override`
- L59 _public function_ `virtual void SetAdditionalUATCommandLine( const TCHAR* InAdditionalCommandLine ) override`
- L67 _public function_ `virtual const FString& GetAdditionalUATCommandLine() const override`
- L72 _public function_ `virtual void SetEnabled( bool bInEnabled ) override`
- L80 _public function_ `virtual bool IsEnabled() const override`
- L85 _public function_ `virtual void SetOrder( int32 InOrder ) override`
- L93 _public function_ `virtual int32 GetOrder() const override`
- L98 _public function_ `virtual const TCHAR* GetInternalName() const override`
- L103 _public function_ `virtual void SetDescription(const FString& NewDescription) override`
- L112 _public function_ `virtual FString GetDescription() const`
- L117 _public function_ `virtual void SetUserTypeName(const FString& NewUserTypeName) override`
- L126 _public function_ `virtual FString GetUserTypeName() const override`
- L131 _public function_ `virtual ILauncherProfileAutomatedTestPtr AsAutomatedTest() override`
- L136 _public function_ `virtual ILauncherProfileBuildCookRunPtr AsBuildCookRun() override`
- L153 _public function_ `virtual bool Load(const FJsonObject& Object) override`
- L191 _public function_ `virtual void Save(TJsonWriter<>& Writer) override`
- L208 _public function_ `virtual void Serialize( FArchive& Archive ) override final` — `UE_DEPRECATED(5.8, "please use the Json Save/Load API")`
- L221 _private member_ `TSharedPtr<FLauncherProfile> Profile;`
- L223 _private member_ `FString UATCommand = TEXT("Run`
- L224 _private member_ `FString Tests;` — -Test=xxx,yyy
- L225 _private member_ `FString UATCommandLine;`
- L227 _private member_ `bool bEnabled = true;`
- L228 _private member_ `int32 Order = 1;` — longer tests should generally have a higher order
- L230 _private member_ `FString InternalName;`
- L231 _private member_ `FString UserTypeName;`
- L232 _private member_ `FString Description = NSLOCTEXT("FLauncherProfileAutoma`

#### enum `FLauncherProfileAutomatedTest::EVersion`  
`enum class EVersion : uint32`  
_L141-150_
- L143 _public enumerator_ `Original = 0`
- L144 _public enumerator_ `FirstVersioned = 1`
- L145 _public enumerator_ `AddUserTypeName = 2`
- L148 _public enumerator_ `Final`
- L149 _public enumerator_ `Latest = Final-1`

### `Source/Developer/LauncherServices/Private/Profiles/LauncherProfileBuildCookRun.h` (Private)


#### class `FLauncherProfileBuildCookRun`  
`class FLauncherProfileBuildCookRun final : public ILauncherProfileBuildCookRun , public TSharedFromThis<FLauncherProfileBuildCookRun>`  
_L51-2167_
- inherits: `ILauncherProfileBuildCookRun,TSharedFromThis<FLauncherProfileBuildCookRun>`
- desc: Implements a BuildCookRun UAT command
- L56 _public member_ `static const TCHAR* TypeName;`
- L63 _public function_ `static FString GetProfileFolder(bool bNotForLicensees)` — Gets the folder in which profile files are stored. @return The folder path.
- L75 _public function_ `FLauncherProfileBuildCookRun( ILauncherProfileManagerRef InProfileManager, TSharedPtr<FLauncherProfile> InProfile, const TCHAR* InInternalName = TEXT(""), const TCHAR* InUserTypeName = TEXT("") ) : LauncherProfileManager(InProfileManager) , DefaultLaunchRole(MakeShareable(new FLauncherProfileLaunchRole())) , Profile(InProfile) , InternalName(InInternalName) , UserTypeName(InUserTypeName)` — Default constructor.
- L94 _public function_ `~FLauncherProfileBuildCookRun( )` — Destructor.
- L117 _public function_ `virtual const FGuid& GetDeployedDeviceGroupId( ) const override` — Gets the identifier of the device group to deploy to. This method is used internally by the profile manager to read the device group identifier after loading this profile from a file. The profile manager will use this identifier to locate the actual device group to deploy to. @return The device group identifier, or an invalid GUID if no group was set or deployment is disabled.
- L124 _public function_ `virtual void AddCookedCulture( const FString& CultureName ) override`
- L131 _public function_ `virtual void AddCookedMap( const FString& MapName ) override`
- L138 _public function_ `virtual void AddCookedPlatform( const FString& PlatformName ) override`
- L145 _public function_ `virtual void SetDefaultDeployPlatform(const FName PlatformName) override`
- L184 _public function_ `virtual void ClearCookedCultures( ) override`
- L194 _public function_ `virtual void ClearCookedMaps( ) override`
- L204 _public function_ `virtual void ClearCookedPlatforms( ) override`
- L214 _public function_ `virtual ILauncherProfileLaunchRolePtr CreateLaunchRole( ) override`
- L225 _public function_ `virtual EBuildConfiguration GetBuildConfiguration( ) const override`
- L230 _public function_ `virtual bool HasBuildTargetSpecified() const override`
- L235 _public function_ `virtual EBuildConfiguration GetCookConfiguration( ) const override`
- L240 _public function_ `virtual ELauncherProfileCookModes::Type GetCookMode( ) const override`
- L245 _public function_ `virtual const FString& GetCookOptions( ) const override`
- L250 _public function_ `virtual const TArray<FString>& GetCookedCultures( ) const override`
- L255 _public function_ `virtual const bool GetSkipCookingEditorContent() const override`
- L260 _public function_ `virtual const TArray<FString>& GetCookedMaps( ) const override`
- L265 _public function_ `virtual const TArray<FString>& GetCookedPlatforms( ) const override`
- L270 _public function_ `virtual const ILauncherProfileLaunchRoleRef& GetDefaultLaunchRole( ) const override`
- L275 _public function_ `virtual ILauncherDeviceGroupPtr GetDeployedDeviceGroup( bool bRefreshDevices = true ) override`
- L286 _public function_ `virtual const FName GetDefaultDeployPlatform() const override`
- L291 _public function_ `virtual bool IsGeneratingPatch() const override`
- L296 _public function_ `virtual bool ShouldAddPatchLevel() const override`
- L301 _public function_ `virtual bool IsCreatingDLC() const override`
- L305 _public function_ `virtual void SetCreateDLC(bool InBuildDLC) override`
- L310 _public function_ `virtual FString GetDLCName() const override`
- L314 _public function_ `virtual void SetDLCName(const FString& InDLCName) override`
- L319 _public function_ `virtual bool IsDLCIncludingEngineContent() const`
- L323 _public function_ `virtual void SetDLCIncludeEngineContent(bool InDLCIncludeEngineContent)`
- L330 _public function_ `virtual bool IsCreatingReleaseVersion() const override`
- L335 _public function_ `virtual void SetCreateReleaseVersion(bool InCreateReleaseVersion) override`
- L340 _public function_ `virtual FString GetCreateReleaseVersionName() const override`
- L345 _public function_ `virtual void SetCreateReleaseVersionName(const FString& InCreateReleaseVersionName) override`
- L351 _public function_ `virtual FString GetBasedOnReleaseVersionName() const override`
- L356 _public function_ `virtual void SetBasedOnReleaseVersionName(const FString& InBasedOnReleaseVersionName) override`
- L361 _public function_ `virtual FString GetOriginalReleaseVersionName() const override`
- L366 _public function_ `virtual void SetOriginalReleaseVersionName(const FString& InOriginalReleaseVersionName) override`
- L371 _public function_ `virtual FString GetReferenceContainerGlobalFileName() const override`
- L375 _public function_ `virtual void SetReferenceContainerGlobalFileName(const FString& InReferenceContainerGlobalFileName) override`
- L379 _public function_ `virtual FString GetReferenceContainerCryptoKeysFileName() const override`
- L383 _public function_ `virtual void SetReferenceContainerCryptoKeysFileName(const FString& InReferenceContainerCryptoKeysFileName) override`
- L388 _public function_ `virtual ELauncherProfileDeploymentModes::Type GetDeploymentMode( ) const override`
- L393 _public function_ `virtual bool GetForceClose() const override`
- L398 _public function_ `virtual ELauncherProfileLaunchModes::Type GetLaunchMode( ) const override`
- L403 _public function_ `virtual const TArray<ILauncherProfileLaunchRolePtr>& GetLaunchRoles( ) const override`
- L408 _public function_ `virtual const int32 GetLaunchRolesFor( const FString& DeviceId, TArray<ILauncherProfileLaunchRolePtr>& OutRoles ) override`
- L432 _public function_ `virtual FString GetDescription() const override`
- L437 _public function_ `virtual ELauncherProfilePackagingModes::Type GetPackagingMode( ) const override`
- L442 _public function_ `virtual FString GetPackageDirectory( ) const override`
- L447 _public function_ `virtual bool IsArchiving( ) const override`
- L452 _public function_ `virtual FString GetArchiveDirectory( ) const override`
- L457 _public function_ `virtual uint32 GetTimeout() const override`
- L462 _public function_ `virtual ELauncherProfileBuildModes::Type GetBuildMode() const override`
- L467 _public function_ `virtual bool ShouldBuild() override`
- L528 _public function_ `virtual bool IsFastIterate() const override`
- L533 _public function_ `virtual FString GetAdditionalCommandLineParameters() const override`
- L538 _public function_ `virtual FString GetAdditionalTargetCommandLineParameters( EBuildTargetType BuildTargetType ) const override`
- L546 _public function_ `virtual bool IsCookingIncrementally( ) const override`
- L555 _public function_ `virtual bool IsIterateSharedCookedBuild() const override`
- L564 _public function_ `virtual bool IsCompressed() const override`
- L569 _public function_ `virtual bool IsEncryptingIniFiles() const override`
- L574 _public function_ `virtual bool IsForDistribution() const override`
- L579 _public function_ `virtual bool IsCookingUnversioned( ) const override`
- L584 _public function_ `virtual bool IsDeployablePlatform( const FString& PlatformName ) override`
- L594 _public function_ `virtual bool IsDeployingIncrementally( ) const override`
- L599 _public function_ `virtual bool IsFileServerHidden( ) const override`
- L604 _public function_ `virtual bool IsFileServerStreaming( ) const override`
- L609 _public function_ `virtual bool IsPackingWithUnrealPak( ) const override`
- L614 _public function_ `virtual bool IsIncludingPrerequisites() const override`
- L619 _public function_ `virtual bool IsGeneratingChunks() const override`
- L624 _public function_ `virtual bool IsGenerateHttpChunkData() const override`
- L629 _public function_ `virtual FString GetHttpChunkDataDirectory() const override`
- L634 _public function_ `virtual FString GetHttpChunkDataReleaseName() const override`
- L639 _public function_ `virtual void RemoveCookedCulture( const FString& CultureName ) override`
- L646 _public function_ `virtual void RemoveCookedMap( const FString& MapName ) override`
- L653 _public function_ `virtual void RemoveCookedPlatform( const FString& PlatformName ) override`
- L660 _public function_ `virtual void RemoveLaunchRole( const ILauncherProfileLaunchRoleRef& Role ) override`
- L667 _public function_ `virtual void Save(TJsonWriter<>& Writer) override`
- L820 _public function_ `TArray<FString> FindPlatforms()`
- L871 _public function_ `virtual bool Load(const FJsonObject& Object) override`
- L876 _public function_ `bool Load(const FJsonObject& Object, int32 ProfileVersion)`
- L1181 _public function_ `virtual void SetDefaults( ) override`
- L1265 _public function_ `virtual void SetBuildMode(ELauncherProfileBuildModes::Type Mode) override`
- L1275 _public function_ `virtual void SetFastIterate(bool Enable) override`
- L1280 _public function_ `virtual void SetAdditionalCommandLineParameters(const FString& Params) override`
- L1290 _public function_ `virtual void SetAdditionalTargetCommandLineParameters(const FString& Params, EBuildTargetType BuildTargetType ) override`
- L1312 _public function_ `virtual void SetBuildConfiguration( EBuildConfiguration Configuration ) override`
- L1322 _public function_ `virtual void SetBuildTargetSpecified(bool Specified) override`
- L1331 _public function_ `virtual void SetCookConfiguration( EBuildConfiguration Configuration ) override`
- L1341 _public function_ `virtual void SetCookMode( ELauncherProfileCookModes::Type Mode ) override`
- L1351 _public function_ `virtual void SetCookOptions(const FString& Options) override`
- L1361 _public function_ `virtual void SetSkipCookingEditorContent(const bool InSkipCookingEditorContent) override`
- L1370 _public function_ `virtual void SetDeployWithUnrealPak( bool UseUnrealPak ) override`
- L1380 _public function_ `virtual void SetGenerateChunks(bool bInGenerateChunks) override`
- L1389 _public function_ `virtual void SetGenerateHttpChunkData(bool bInGenerateHttpChunkData) override`
- L1398 _public function_ `virtual void SetHttpChunkDataDirectory(const FString& InHttpChunkDataDirectory) override`
- L1407 _public function_ `virtual void SetHttpChunkDataReleaseName(const FString& InHttpChunkDataReleaseName) override`
- L1416 _public function_ `virtual void SetDeployedDeviceGroup( const ILauncherDeviceGroupPtr& DeviceGroup ) override`
- L1443 _public function_ `virtual void SetDeploymentMode( ELauncherProfileDeploymentModes::Type Mode ) override`
- L1453 _public function_ `virtual void SetForceClose( bool Close ) override`
- L1462 _public function_ `virtual void SetHideFileServerWindow( bool Hide ) override`
- L1467 _public function_ `virtual void SetIncrementalCooking( bool Incremental ) override`
- L1476 _public function_ `virtual void SetIterateSharedCookedBuild( bool SharedCookedBuild ) override`
- L1486 _public function_ `virtual void SetCompressed( bool Enabled ) override`
- L1496 _public function_ `virtual void SetForDistribution(bool Enabled)override`
- L1506 _public function_ `virtual void SetEncryptingIniFiles(bool Enabled) override`
- L1516 _public function_ `virtual void SetIncrementalDeploying( bool Incremental ) override`
- L1526 _public function_ `virtual void SetLaunchMode( ELauncherProfileLaunchModes::Type Mode ) override`
- L1536 _public function_ `virtual void SetDescription(const FString& NewDescription) override`
- L1541 _public function_ `virtual void SetPackagingMode( ELauncherProfilePackagingModes::Type Mode ) override`
- L1551 _public function_ `virtual void SetPackageDirectory( const FString& Dir ) override`
- L1561 _public function_ `virtual void SetArchive( bool bInArchive ) override`
- L1571 _public function_ `virtual void SetArchiveDirectory( const FString& Dir ) override`
- L1581 _public function_ `virtual void SetStreamingFileServer( bool Streaming ) override`
- L1591 _public function_ `virtual void SetIncludePrerequisites(bool InValue) override`
- L1601 _public function_ `virtual void SetTimeout( uint32 InTime ) override`
- L1611 _public function_ `virtual void SetUnversionedCooking( bool Unversioned ) override`
- L1621 _public function_ `virtual void SetGeneratePatch( bool InGeneratePatch ) override`
- L1626 _public function_ `virtual void SetAddPatchLevel( bool InAddPatchLevel) override`
- L1631 _public function_ `virtual void SetUseIoStore(bool bInUseIoStore) override`
- L1643 _public function_ `virtual bool IsUsingIoStore() const override`
- L1648 _public function_ `virtual void SetUseZenStore(bool bInUseZenStore) override`
- L1655 _public function_ `virtual bool IsUsingZenStore() const override`
- L1660 _public function_ `virtual void SetImportingZenSnapshot( bool Import ) override`
- L1670 _public function_ `virtual bool IsImportingZenSnapshot() const override`
- L1675 _public function_ `virtual bool IsUsingZenStreaming() const override`
- L1680 _public function_ `virtual void SetUseZenStreaming( bool UseZenStreaming) override`
- L1690 _public function_ `virtual void SetUseZenPakStreaming( bool UseZenPakStreaming ) override`
- L1700 _public function_ `virtual bool IsUsingZenPakStreaming() const override`
- L1709 _public function_ `virtual void SetZenPakStreamingPath( const FString& Path ) override`
- L1719 _public function_ `virtual FString GetZenPakStreamingPath() const override`
- L1724 _public function_ `virtual void SetUsePreStagedBuild( bool UsePreStagedBuild ) override`
- L1733 _public function_ `virtual bool IsUsingPreStagedBuild() const override`
- L1739 _public function_ `virtual void SetDeviceIsASimulator(bool bInIsDeviceASimualtor) override`
- L1747 _public function_ `virtual bool IsDeviceASimulator() const override` — Is the Launch device actually a simulator?
- L1752 _public function_ `virtual void SetMakeBinaryConfig(bool bInMakeBinaryConfig) override`
- L1757 _public function_ `virtual bool MakeBinaryConfig() const override`
- L1762 _public function_ `virtual void SetClientArchitectures( const TArray<FString>& InArchitectures )`
- L1767 _public function_ `virtual const TArray<FString>& GetClientArchitectures() const override`
- L1772 _public function_ `virtual void SetServerArchitectures( const TArray<FString>& InArchitectures )`
- L1777 _public function_ `virtual const TArray<FString>& GetServerArchitectures() const override`
- L1782 _public function_ `virtual void SetEditorArchitectures( const TArray<FString>& InArchitectures )`
- L1787 _public function_ `virtual const TArray<FString>& GetEditorArchitectures() const override`
- L1798 _public function_ `virtual TArray<FString> GetBuildTargets() const`
- L1810 _public function_ `virtual void AddBuildTarget( const FString& InBuildTarget )`
- L1816 _public function_ `virtual void RemoveBuildTarget( const FString& InBuildTarget )`
- L1822 _public function_ `virtual void ClearBuildTargets()`
- L1833 _public function_ `virtual void SetUATCommand( const TCHAR* InUATCommand ) override` — ILauncherProfileUATCommand interface
- L1842 _public function_ `virtual const FString& GetUATCommand() const override`
- L1847 _public function_ `virtual void SetAdditionalUATCommandLine( const TCHAR* InAdditionalCommandLine ) override`
- L1855 _public function_ `virtual const FString& GetAdditionalUATCommandLine() const override`
- L1860 _public function_ `virtual void SetEnabled( bool bInEnabled ) override`
- L1868 _public function_ `virtual bool IsEnabled() const override`
- L1873 _public function_ `virtual void SetOrder( int32 InOrder ) override`
- L1881 _public function_ `virtual int32 GetOrder() const override`
- L1886 _public function_ `virtual const TCHAR* GetInternalName() const override`
- L1891 _public function_ `virtual void SetUserTypeName(const FString& NewUserTypeName) override`
- L1900 _public function_ `virtual FString GetUserTypeName() const override`
- L1905 _public function_ `virtual ILauncherProfileAutomatedTestPtr AsAutomatedTest() override`
- L1910 _public function_ `virtual ILauncherProfileBuildCookRunPtr AsBuildCookRun() override`
- L1917 _protected function_ `void Validate()`
- L1925 _protected function_ `void OnLauncherDeviceGroupDeviceAdded(const ILauncherDeviceGroupRef& DeviceGroup, const FString& DeviceId)`
- L1933 _protected function_ `void OnLauncherDeviceGroupDeviceRemove(const ILauncherDeviceGroupRef& DeviceGroup, const FString& DeviceId)`
- L1941 _protected function_ `void OnSelectedProjectChanged()`
- L1950 _private member_ `ILauncherProfileManagerRef LauncherProfileManager;` — Holds a reference to the launcher profile manager.
- L1953 _private member_ `EBuildConfiguration BuildConfiguration;` — Holds the desired build configuration (only used if creating new builds).
- L1956 _private member_ `bool BuildTargetSpecified;` — Holds a flag indicating whether the build target is specified by this profile.
- L1959 _private member_ `TArray<FString> BuildTargets;` — Holds the names of the build targets (matching a .cs file) to build. Needed when multiple targets of a type exist
- L1963 _private member_ `EBuildConfiguration CookConfiguration;` — Holds the build mode. Holds the build configuration name of the cooker.
- L1966 _private member_ `FString CookOptions;` — Holds additional cooker command line options.
- L1969 _private member_ `TEnumAsByte<ELauncherProfileCookModes::Type> CookMode;` — Holds the cooking mode.
- L1972 _private member_ `TEnumAsByte<ELauncherProfileBuildModes::Type> BuildMode;` — Holds the build mode
- L1975 _private member_ `bool bFastIterate;` — Holds a flag indicating whether fast iteration is enabled
- L1978 _private member_ `bool Compressed;` — Generate compressed content
- L1981 _private member_ `bool EncryptIniFiles;` — encrypt ini files in the pak file
- L1983 _private member_ `bool ForDistribution;` — is this build for distribution
- L1986 _private member_ `bool CookIncremental;` — Holds a flag indicating whether only modified content should be cooked.
- L1989 _private member_ `bool IterateSharedCookedBuild;` — hold a flag indicating if we want to iterate on the shared cooked build
- L1992 _private member_ `bool CookUnversioned;` — Holds a flag indicating whether packages should be saved without a version.
- L1994 _private member_ `bool bSkipCookingEditorContent;`
- L1997 _private member_ `TArray<FString> CookedCultures;` — This setting is used only if cooking by the book (only used if cooking by the book).
- L2000 _private member_ `TArray<FString> CookedMaps;` — Holds the collection of maps to cook (only used if cooking by the book).
- L2003 _private member_ `TArray<FString> CookedPlatforms;` — Holds the platforms to include in the build (only used if creating new builds).
- L2006 _private member_ `FName DefaultDeployPlatform;` — Holds the platforms to deploy to if no specific devices were chosen for deploy.
- L2009 _private member_ `ILauncherProfileLaunchRoleRef DefaultLaunchRole;` — Holds the default role (only used if launch mode is DefaultRole).
- L2012 _private member_ `bool DeployStreamingServer;` — Holds a flag indicating whether a streaming file server should be used.
- L2015 _private member_ `bool DeployWithUnrealPak;` — Holds a flag indicating whether content should be packaged with UnrealPak.
- L2018 _private member_ `bool IncludePrerequisites;` — Flag to indicate if game prerequisites should be included
- L2021 _private member_ `bool bGenerateChunks;` — Flag indicating if content should be split into chunks
- L2024 _private member_ `bool bGenerateHttpChunkData;` — Flag indicating if chunked content should be used to generate HTTPChunkInstall data
- L2027 _private member_ `FString HttpChunkDataDirectory;` — Where to store HTTPChunkInstall data
- L2030 _private member_ `FString HttpChunkDataReleaseName;` — Version name of the HTTPChunkInstall data
- L2035 _private member_ `FString ReferenceContainerGlobalFileName;` — if present, iostore container creation will try to use existing compressed blocks instead of compressing new ones, to avoid patches from compressor version changes, and to speed up iostore container creation time. See IoStoreUtilities.cpp ReferenceContainerGlobalFileName.
- L2039 _private member_ `FString ReferenceContainerCryptoKeysFileName;` — If ReferenceContainerGlobalFileName refers to encrypted containers, this is the filename of the json file containing the keys.
- L2042 _private member_ `bool CreateReleaseVersion;` — create a release version of the content (this can be used to base dlc / patches from)
- L2045 _private member_ `FString CreateReleaseVersionName;` — name of the release version
- L2048 _private member_ `FString BasedOnReleaseVersionName;` — name of the release version to base this dlc / patch on
- L2051 _private member_ `FString OriginalReleaseVersionName;` — name of the original release version
- L2054 _private member_ `bool GeneratePatch;` — This build generate a patch based on some source content seealso PatchSourceContentPath
- L2057 _private member_ `bool AddPatchLevel;` — This build generates a new tier patch file for modified content
- L2060 _private member_ `bool CreateDLC;` — This build will cook content for dlc See also DLCName
- L2063 _private member_ `FString DLCName;` — name of the dlc we are going to build (the name of the dlc plugin)
- L2068 _private member_ `bool DLCIncludeEngineContent;` — should the dlc include engine content in the current dlc engine content which was not referenced by original release otherwise error on any access of engine content during dlc cook
- L2071 _private member_ `bool DeployIncremental;` — Holds a flag indicating whether to use incremental deployment
- L2074 _private member_ `ILauncherDeviceGroupPtr DeployedDeviceGroup;` — Holds the device group to deploy to.
- L2077 _private member_ `FDelegateHandle OnLauncherDeviceGroupDeviceAddedDelegateHandle;` — Delegate handles for registered DeployedDeviceGroup event handlers.
- L2078 _private member_ `FDelegateHandle OnLauncherDeviceGroupDeviceRemoveDelegateHandle;`
- L2081 _private member_ `FGuid DeployedDeviceGroupId;` — Holds the identifier of the deployed device group.
- L2084 _private member_ `TEnumAsByte<ELauncherProfileDeploymentModes::Type> DeploymentMode;` — Holds the deployment mode.
- L2087 _private member_ `bool HideFileServerWindow;` — Holds a flag indicating whether the file server's console window should be hidden.
- L2090 _private member_ `TEnumAsByte<ELauncherProfileLaunchModes::Type> LaunchMode;` — Holds the launch mode.
- L2093 _private member_ `TArray<ILauncherProfileLaunchRolePtr> LaunchRoles;` — Holds the launch roles (only used if launch mode is UsingRoles).
- L2096 _private member_ `FString Description;` — Holds the profile's description.
- L2099 _private member_ `TEnumAsByte<ELauncherProfilePackagingModes::Type> PackagingMode;` — Holds the packaging mode.
- L2102 _private member_ `FString PackageDir;` — Holds the package directory
- L2105 _private member_ `bool bArchive;` — Whether to run archive step
- L2108 _private member_ `FString ArchiveDir;` — Holds the archive directory
- L2111 _private member_ `FString ZenPakStreamingPath;` — Holds the full path to a folder to use for Zen pak streaming
- L2114 _private member_ `bool bUsePreStagedBuild;` — Whether to use a pre-staged build
- L2117 _private member_ `uint32 Timeout;` — Holds the time out time for the cook on the fly server
- L2120 _private member_ `bool ForceClose;` — Holds the close value for the cook on the fly server
- L2123 _private member_ `FString AdditionalCommandLineParameters;` — Additional command line parameters to set for the application when it launches
- L2126 _private member_ `TMap<EBuildTargetType,FString> AdditionalTargetCommandLineParameters;` — Additional command line parameters to set for a given build target type when it launches
- L2129 _private member_ `bool bUseIoStore;` — Use I/O store.
- L2132 _private member_ `bool bUseZenStore;` — Use Zen storage server
- L2135 _private member_ `bool bImportingZenSnapshot;` — Import a Zen snapshot before cooking
- L2137 _private member_ `bool bUseZenStreaming;`
- L2140 _private member_ `bool bUseZenPakStreaming;` — Use Zen pak streaming
- L2143 _private member_ `bool bMakeBinaryConfig;` — Make binary config.
- L2146 _private member_ `bool bIsDeviceASimulator;` — Is the launch device actually a Simulator
- L2149 _private member_ `TArray<FString> ClientArchitectures;` — Architectures to build (x64, arm64 etc)
- L2150 _private member_ `TArray<FString> ServerArchitectures;`
- L2151 _private member_ `TArray<FString> EditorArchitectures;`
- L2154 _private member_ `TSharedPtr<FLauncherProfile> Profile;`
- L2156 _private member_ `FString UATCommand = TEXT("Bui`
- L2157 _private member_ `FString UATCommandLine;`
- L2159 _private member_ `bool bEnabled = true;`
- L2160 _private member_ `int32 Order = 0;`
- L2162 _private member_ `FString InternalName;`
- L2163 _private member_ `FString UserTypeName;`

#### enum `FLauncherProfileBuildCookRun::EVersion`  
`enum class EVersion : uint32`  
_L858-867_
- L860 _public enumerator_ `PreInnerBuildCookRun=0`
- L861 _public enumerator_ `Original=1`
- L862 _public enumerator_ `AddUserTypeName=2`
- L865 _public enumerator_ `Final`
- L866 _public enumerator_ `Latest = Final-1`

#### Free symbols / members of external scopes

- L31 _prototype_ `bool HasPromotedTarget(const TCHAR* BaseDir, const TCHAR* TargetName, const TCHAR* Platform, EBuildConfiguration Configuration, const TCHAR* Architecture);`
- L33 _function_ `inline bool TryGetDefaultTargetName(const FString& ProjectFile, EBuildTargetType TargetType, FString& OutTargetName)`

### `Source/Developer/LauncherServices/Private/Profiles/LauncherProfileLaunchRole.h` (Private)


#### class `FLauncherProfileLaunchRole`  
`class FLauncherProfileLaunchRole final : public ILauncherProfileLaunchRole`  
_L9-173_
- inherits: `ILauncherProfileLaunchRole`
- L15 _public function_ `FLauncherProfileLaunchRole( ) : InstanceType(ELauncherProfileRoleInstanceTypes::StandaloneClient) , Name(TEXT("Unnamed Role"))` — Default constructor.
- L26 _public function_ `FLauncherProfileLaunchRole( FArchive& Archive )` — `UE_DEPRECATED(5.8, "please use the Json Save/Load API")` — Creates and initializes a new instance from the given archive. @param Archive - The archive to serialize from.
- L33 _public function_ `FLauncherProfileLaunchRole(const FJsonObject& Object)`
- L42 _public function_ `virtual const FString& GetAssignedDevice( ) const override`
- L47 _public function_ `virtual const FString& GetUATCommandLine( ) const override`
- L52 _public function_ `virtual const FString& GetInitialCulture( ) const override`
- L57 _public function_ `virtual const FString& GetInitialMap( ) const override`
- L62 _public function_ `virtual ELauncherProfileRoleInstanceTypes::Type GetInstanceType( ) const override`
- L67 _public function_ `virtual const FString& GetName( ) const override`
- L72 _public function_ `virtual bool IsVsyncEnabled( ) const override`
- L77 _public function_ `virtual void Load(const FJsonObject& Object)`
- L89 _public function_ `virtual void Save(TJsonWriter<>& Writer, const TCHAR* InName = TEXT(""))`
- L104 _public function_ `virtual void Serialize( FArchive& Archive ) override final` — `UE_DEPRECATED(5.8, "please use the Json Save/Load API")`
- L116 _public function_ `virtual void SetCommandLine( const FString& NewCommandLine ) override`
- L121 _public function_ `virtual void SetInitialCulture( const FString& CultureName ) override`
- L126 _public function_ `virtual void SetInitialMap( const FString& MapName ) override`
- L131 _public function_ `virtual void SetInstanceType( ELauncherProfileRoleInstanceTypes::Type InInstanceType ) override`
- L136 _public function_ `virtual void SetName( const FString& NewName ) override`
- L141 _public function_ `virtual void SetVsyncEnabled( bool Enabled ) override`
- L151 _private member_ `FString AssignedDevice;` — Holds the identifier of the device that is assigned to this role.
- L154 _private member_ `FString CommandLine;` — Holds optional command line parameters.
- L157 _private member_ `FString DeviceId;` — Holds the identifier of the device that is assigned to this role.
- L160 _private member_ `FString InitialCulture;` — Holds the initial localization culture to launch with.
- L163 _private member_ `FString InitialMapName;` — Holds the name of the map to launch.
- L166 _private member_ `TEnumAsByte<ELauncherProfileRoleInstanceTypes::Type> InstanceType;` — Holds the role instance type.
- L169 _private member_ `FString Name;` — Holds the role's name.
- L172 _private member_ `bool VsyncEnabled;` — Holds a flag indicating whether VSync should be enabled.

### `Source/Developer/LauncherServices/Private/Profiles/LauncherProfileManager.h` (Private)


#### class `FLauncherProfileManager`  
`class FLauncherProfileManager : public TSharedFromThis<FLauncherProfileManager> , public ILauncherProfileManager`  
_L12-241_
- inherits: `TSharedFromThis<FLauncherProfileManager>,ILauncherProfileManager`
- desc: Implements a helper class that manages all profiles in the Launcher
- L19 _public prototype_ `FLauncherProfileManager();` — Default constructor.
- L27 _public prototype_ `void Load();` — Loads the profiles and device groups.
- L31 _public prototype_ `virtual void AddDeviceGroup( const ILauncherDeviceGroupRef& DeviceGroup ) override;`
- L33 _public prototype_ `virtual ILauncherDeviceGroupRef AddNewDeviceGroup( ) override;`
- L35 _public prototype_ `virtual ILauncherDeviceGroupRef CreateUnmanagedDeviceGroup() override;`
- L37 _public prototype_ `virtual ILauncherSimpleProfilePtr FindOrAddSimpleProfile(const FString& DeviceName) override;`
- L39 _public prototype_ `virtual ILauncherSimpleProfilePtr FindSimpleProfile(const FString& DeviceName) override;`
- L41 _public prototype_ `virtual ILauncherProfileRef AddNewProfile() override;`
- L43 _public prototype_ `virtual ILauncherProfileRef CreateUnsavedProfile(FString ProfileName) override;`
- L45 _public prototype_ `virtual void AddProfile( const ILauncherProfileRef& Profile ) override;`
- L47 _public prototype_ `virtual ILauncherProfilePtr FindProfile( const FString& ProfileName ) override;`
- L49 _public prototype_ `virtual const TArray<ILauncherDeviceGroupPtr>& GetAllDeviceGroups( ) const override;`
- L51 _public prototype_ `virtual const TArray<ILauncherProfilePtr>& GetAllProfiles( ) const override;`
- L53 _public prototype_ `virtual ILauncherDeviceGroupPtr GetDeviceGroup( const FGuid& GroupId ) const override;`
- L55 _public prototype_ `virtual ILauncherProfilePtr GetProfile( const FGuid& ProfileId ) const override;`
- L58 _public prototype_ `virtual ILauncherProfilePtr LoadProfile( FArchive& Archive ) override;` — `UE_DEPRECATED(5.8, "Please use LoadJSONProfile")`
- L60 _public prototype_ `virtual ILauncherProfilePtr LoadJSONProfile(FString ProfileFile) override;`
- L62 _public prototype_ `virtual void LoadSettings() override;`
- L64 _public function_ `virtual FOnLauncherProfileManagerDeviceGroupAdded& OnDeviceGroupAdded( ) override`
- L69 _public function_ `virtual FOnLauncherProfileManagerDeviceGroupRemoved& OnDeviceGroupRemoved( ) override`
- L74 _public function_ `virtual FOnLauncherProfileManagerProfileAdded& OnProfileAdded( ) override`
- L79 _public function_ `virtual FOnLauncherProfileManagerProfileRemoved& OnProfileRemoved( ) override`
- L84 _public function_ `virtual FOnLauncherProfileManagerProjectChanged& OnProjectChanged( ) override`
- L89 _public function_ `virtual FOnLauncherProfilePostProcessCommandLine& OnPostProcessLaunchCommandLine( ) override`
- L95 _public function_ `virtual FOnLauncherProfilePostProcessAutomatedTestCommandLine& OnPostProcessAutomatedTestCommandLine( ) override` — `UE_DEPRECATED(5.8, "Use OnPostProcessUATCommandLine")`
- L100 _public function_ `virtual FOnLauncherProfilePostProcessUATCommandLine& OnPostProcessUATCommandLine( ) override`
- L105 _public prototype_ `virtual void RemoveDeviceGroup( const ILauncherDeviceGroupRef& DeviceGroup ) override;`
- L107 _public prototype_ `virtual void SaveDeviceGroups( bool bTrimUnused = false ) override;`
- L109 _public prototype_ `virtual void RemoveSimpleProfile(const ILauncherSimpleProfileRef& SimpleProfile) override;`
- L111 _public prototype_ `virtual void RemoveProfile( const ILauncherProfileRef& Profile ) override;`
- L114 _public prototype_ `virtual bool SaveProfile( const ILauncherProfileRef& Profile) override;` — `UE_DEPRECATED(5.8, "Please use SaveJSONProfile")`
- L116 _public prototype_ `virtual bool SaveJSONProfile(const ILauncherProfileRef& Profile) override;`
- L118 _public prototype_ `virtual void ChangeProfileName( const ILauncherProfileRef& Profile, FString Name) override;`
- L120 _public prototype_ `virtual void RegisterProfileWizard(const ILauncherProfileWizardPtr& ProfileWizard) override;`
- L122 _public prototype_ `virtual void UnregisterProfileWizard(const ILauncherProfileWizardPtr& ProfileWizard) override;`
- L124 _public prototype_ `virtual const TArray<ILauncherProfileWizardPtr>& GetProfileWizards() const override;`
- L126 _public prototype_ `virtual void SaveSettings( ) override;`
- L128 _public prototype_ `virtual FString GetProjectName() const override;`
- L130 _public prototype_ `virtual FString GetProjectBasePath() const override;`
- L132 _public prototype_ `virtual FString GetProjectPath() const override;`
- L134 _public prototype_ `virtual void SetProjectPath(const FString& InProjectPath) override;`
- L136 _public prototype_ `virtual FString GetBuildTarget() const override;`
- L138 _public prototype_ `virtual void SetBuildTarget( const FString& InBuildTarget ) override;`
- L141 _public prototype_ `virtual const TArray<FString> GetAllExplicitBuildTargetNames() const override;` — `UE_DEPRECATED(5.8, "this was only used for the legacy project launcher")`
- L143 _public prototype_ `virtual FString MakeBuildCookRunParamsForProjectCustomBuild(const ILauncherProfileRef& InProfile, const TArray<FString>& InPlatforms) const override;`
- L152 _protected prototype_ `void LoadDeviceGroups( );` — Loads all the device groups from a config file
- L157 _protected prototype_ `void LoadProfiles( );` — Load all profiles from disk.
- L166 _protected prototype_ `ILauncherDeviceGroupPtr ParseDeviceGroup( const FString& GroupString );` — Create a new device group from the specified string value. @param GroupString - The string to parse. @return The new device group object.
- L171 _protected prototype_ `void SaveSimpleProfiles();` — Saves all simple profiles to disk.
- L176 _protected prototype_ `void SaveProfiles();` — Saves all profiles to disk.
- L185 _protected function_ `static FString GetLegacyProfileFolder()` — Gets the folder in which old profile files were stored. @return The folder path.
- L193 _private member_ `TArray<ILauncherDeviceGroupPtr> DeviceGroups;` — Holds the collection of device groups.
- L196 _private member_ `TArray<ILauncherSimpleProfilePtr> SimpleProfiles;` — Holds the collection of simple launcher profiles.
- L199 _private member_ `TArray<ILauncherProfilePtr> SavedProfiles;` — Holds the collection of launcher profiles.
- L202 _private member_ `TArray<ILauncherProfilePtr> AllProfiles;` — Holds the collection of launcher profiles.
- L205 _private member_ `FString ProjectPath;` — Holds the currently selected project path
- L208 _private member_ `FString BuildTarget;` — Holds the currently selected build target
- L211 _private member_ `TArray<ILauncherProfileWizardPtr> ProfileWizards;` — Holds all registered profile wizards
- L214 _private member_ `FString ConfigFileName;` — Holds the config file name to save to
- L219 _private member_ `FOnLauncherProfileManagerDeviceGroupAdded DeviceGroupAddedDelegate;` — Holds a delegate to be invoked when a device group was added.
- L222 _private member_ `FOnLauncherProfileManagerDeviceGroupRemoved DeviceGroupRemovedDelegate;` — Holds a delegate to be invoked when a device group was removed.
- L225 _private member_ `FOnLauncherProfileManagerProfileAdded ProfileAddedDelegate;` — Holds a delegate to be invoked when a launcher profile was added.
- L228 _private member_ `FOnLauncherProfileManagerProfileRemoved ProfileRemovedDelegate;` — Holds a delegate to be invoked when a launcher profile was removed.
- L231 _private member_ `FOnLauncherProfileManagerProjectChanged ProjectChangedDelegate;` — Holds a delegate to be invoked when the project changes.
- L234 _private member_ `FOnLauncherProfilePostProcessCommandLine ProcessProcessLaunchCommandLine;` — Holds a delegate to be invoked to modify the command line before launching
- L237 _private member_ `FOnLauncherProfilePostProcessAutomatedTestCommandLine PostProcessAutomatedTestCommandLine;` — Holds a delegate to be involked to modify the command line for an automated test before launching
- L240 _private member_ `FOnLauncherProfilePostProcessUATCommandLine PostProcessUATCommandLine;` — Holds a delegate to be involked to modify the command line for an extra UAT command before launching

### `Source/Developer/LauncherServices/Private/Profiles/LauncherProfileUATCommand.h` (Private)


#### class `FLauncherProfileUATCommand`  
`class FLauncherProfileUATCommand final : public ILauncherProfileUATCommand, public TSharedFromThis<FLauncherProfileUATCommand>`  
_L13-191_
- inherits: `ILauncherProfileUATCommand,TSharedFromThis<FLauncherProfileUATCommand>`
- L16 _public member_ `static const TCHAR* TypeName;`
- L18 _public function_ `FLauncherProfileUATCommand(TSharedPtr<FLauncherProfile> InProfile, const TCHAR* InInternalName = TEXT(""), const TCHAR* InUserTypeName = TEXT("") ) : Profile(InProfile) , InternalName(InInternalName) , UserTypeName(InUserTypeName)`
- L25 _public function_ `virtual void SetUATCommand( const TCHAR* InUATCommand ) override`
- L34 _public function_ `virtual const FString& GetUATCommand() const override`
- L39 _public function_ `virtual void SetAdditionalUATCommandLine( const TCHAR* InAdditionalCommandLine ) override`
- L47 _public function_ `virtual const FString& GetAdditionalUATCommandLine() const override`
- L52 _public function_ `virtual void SetEnabled( bool bInEnabled ) override`
- L60 _public function_ `virtual bool IsEnabled() const override`
- L65 _public function_ `virtual void SetOrder( int32 InOrder ) override`
- L73 _public function_ `virtual int32 GetOrder() const override`
- L78 _public function_ `virtual const TCHAR* GetInternalName() const override`
- L83 _public function_ `virtual void SetDescription(const FString& NewDescription) override`
- L92 _public function_ `virtual FString GetDescription() const override`
- L97 _public function_ `virtual void SetUserTypeName(const FString& NewUserTypeName) override`
- L106 _public function_ `virtual FString GetUserTypeName() const override`
- L111 _public function_ `virtual ILauncherProfileAutomatedTestPtr AsAutomatedTest() override`
- L116 _public function_ `virtual ILauncherProfileBuildCookRunPtr AsBuildCookRun() override`
- L132 _public function_ `virtual bool Load(const FJsonObject& Object) override`
- L163 _public function_ `virtual void Save(TJsonWriter<>& Writer) override`
- L180 _private member_ `TSharedPtr<FLauncherProfile> Profile;`
- L182 _private member_ `FString UATCommand = TEXT("Run`
- L183 _private member_ `FString UATCommandLine;`
- L185 _private member_ `bool bEnabled = true;`
- L186 _private member_ `int32 Order = -100000;` — negative order items will run before the main BuildCookRun, positive order items will run afterwards
- L188 _private member_ `FString InternalName;`
- L189 _private member_ `FString UserTypeName;`
- L190 _private member_ `FString Description = NSLOCTEXT("FLauncherProfileUATCom`

#### enum `FLauncherProfileUATCommand::EVersion`  
`enum class EVersion : uint32`  
_L121-130_
- L123 _public enumerator_ `Original = 0`
- L124 _public enumerator_ `FirstVersioned = 1`
- L125 _public enumerator_ `AddUserTypeName = 2`
- L128 _public enumerator_ `Final`
- L129 _public enumerator_ `Latest = Final-1`

### `Source/Developer/LauncherServices/Private/Profiles/LauncherProfileVersion.h` (Private)


#### enum `ELauncherVersion`  
`enum ELauncherVersion`  
_L7-53_
- L9 _public enumerator_ `LAUNCHERSERVICES_MINPROFILEVERSION=10`
- L10 _public enumerator_ `LAUNCHERSERVICES_ADDEDINCREMENTALDEPLOYVERSION=11`
- L11 _public enumerator_ `LAUNCHERSERVICES_ADDEDPATCHSOURCECONTENTPATH=12`
- L12 _public enumerator_ `LAUNCHERSERVICES_ADDEDRELEASEVERSION=13`
- L13 _public enumerator_ `LAUNCHERSERVICES_REMOVEDPATCHSOURCECONTENTPATH=14`
- L14 _public enumerator_ `LAUNCHERSERVICES_ADDEDDLCINCLUDEENGINECONTENT=15`
- L15 _public enumerator_ `LAUNCHERSERVICES_ADDEDGENERATECHUNKS=16`
- L16 _public enumerator_ `LAUNCHERSERVICES_ADDEDNUMCOOKERSTOSPAWN=17`
- L17 _public enumerator_ `LAUNCHERSERVICES_ADDEDSKIPCOOKINGEDITORCONTENT=18`
- L18 _public enumerator_ `LAUNCHERSERVICES_ADDEDDEFAULTDEPLOYPLATFORM=19`
- L19 _public enumerator_ `LAUNCHERSERVICES_FIXCOMPRESSIONSERIALIZE=20`
- L20 _public enumerator_ `LAUNCHERSERVICES_SHAREABLEPROJECTPATHS = 21`
- L21 _public enumerator_ `LAUNCHERSERVICES_FILEFORMATCHANGE = 22`
- L22 _public enumerator_ `LAUNCHERSERVICES_ADDARCHIVE = 23`
- L23 _public enumerator_ `LAUNCHERSERVICES_ADDEDENCRYPTINIFILES = 24`
- L24 _public enumerator_ `LAUNCHERSERVICES_ADDEDMULTILEVELPATCHING = 25`
- L25 _public enumerator_ `LAUNCHERSERVICES_ADDEDADDITIONALCOMMANDLINE = 26`
- L26 _public enumerator_ `LAUNCHERSERVICES_ADDEDINCLUDEPREREQUISITES = 27`
- L27 _public enumerator_ `LAUNCHERSERVICES_ADDEDBUILDMODE = 28`
- L28 _public enumerator_ `LAUNCHERSERVICES_ADDEDUSEIOSTORE = 29`
- L29 _public enumerator_ `LAUNCHERSERVICES_ADDEDMAKEBINARYCONFIG = 30`
- L30 _public enumerator_ `LAUNCHERSERVICES_ADDEDREFERENCECONTAINERS = 31`
- L31 _public enumerator_ `LAUNCHERSERVICES_REMOVEDNUMCOOKERSTOSPAWN = 32`
- L32 _public enumerator_ `LAUNCHERSERVICES_ADDEDORIGINALRELEASEVERSION = 33`
- L33 _public enumerator_ `LAUNCHERSERVICES_ADDBUILDTARGETNAME = 34`
- L34 _public enumerator_ `LAUNCHERSERVICES_ADDEDRETAINSTAGEDDIRECTORY = 35`
- L35 _public enumerator_ `LAUNCHERSERVICES_REMOVEDRETAINSTAGEDDIRECTORY = 36`
- L36 _public enumerator_ `LAUNCHERSERVICES_ADDZENOPTIONS = 37`
- L37 _public enumerator_ `LAUNCHERSERVICES_ADDBUILDARCHITECTURE = 38`
- L38 _public enumerator_ `LAUNCHERSERVICES_ADDCUSTOMPROPERTIES = 39`
- L39 _public enumerator_ `LAUNCHERSERVICES_INCREMENTALCOOKMODE = 40`
- L40 _public enumerator_ `LAUNCHERSERVICES_AUTOMATEDTESTS = 41`
- L41 _public enumerator_ `LAUNCHERSERVICES_FASTITERATE = 42`
- L42 _public enumerator_ `LAUNCHERSERVICES_REMOVEDINCREMENTALCOOKMODE = 43`
- L43 _public enumerator_ `LAUNCHERSERVICES_ADDMULTIPLEBUILDTARGETS = 44`
- L44 _public enumerator_ `LAUNCHERSERVICES_ADDUATCOMMANDS = 45`
- L45 _public enumerator_ `LAUNCHERSERVICES_INNERBUILDCOOKRUN = 46`
- L46 _public enumerator_ `LAUNCHERSERVICES_ADDZENSTREAMINGOPTIONS = 47`
- L47 _public enumerator_ `LAUNCHERSERVICES_ADDPRESTAGED = 48`
- L51 _public enumerator_ `LAUNCHERSERVICES_FINALPLUSONE`
- L52 _public enumerator_ `LAUNCHERSERVICES_FINAL = LAUNCHERSERVICES_FINALPLUSONE-1`

### `Source/Developer/LauncherServices/Public/GameProjectHelper.h` (Public)


#### class `FGameProjectHelper`  
`class FGameProjectHelper`  
_L14-181_
- desc: Implements a helper class for finding project specific information.
- L25 _public function_ `static TArray<FString> GetAvailableConfigurations( const FString& GameName )` — Gets a list of available build configurations for the specified game name. @param GameName - The name of the game (i.e. Example or UDK). @return A list of build configuration names.
- L43 _public function_ `static TArray<FString> GetAvailableGames( )` — Gets a list of available game names. @return Game names.
- L76 _public function_ `static TArray<FString> GetAvailableMaps( FString GameName, bool IncludeEngineMaps, bool Sorted )` — Gets the list of available maps for the specified game. @param GameName - The name of the game (i.e. Example or UDK). @param IncludeEngineMaps - Whether maps in the Engine folder should be included. @param Sorted - Whether the list of maps should be sorted alphabetically. @return A list of available map names.
- L123 _public function_ `static bool IsGameAvailable( FString GameName )` — Checks whether the specified game is available. @param GameName - The name of the game (i.e. ExampleGame or UDKGame). @return true if the game is available, false otherwise.
- L139 _public function_ `static TArray<FString> GetExplicitBuildTargetsForProject( const FString& InProjectFilePath, const TSet<EBuildTargetType>* InFilterTargetTypes = nullptr )` — Returns the list of build targets that must be explicitly specified for the given project. @param InProjectFilePath - the project to use @param InFilterTargetTypes - if specified, the returned list will be restricted to the given target types.

### `Source/Developer/LauncherServices/Public/ILauncher.h` (Public)


#### class `ILauncher`  
`class ILauncher`  
_L24-43_
- desc: Interface for game launchers.
- L35 _public prototype_ `virtual ILauncherWorkerPtr Launch(const TSharedRef<ITargetDeviceProxyManager>& DeviceProxyManager, const ILauncherProfileRef& Profile) = 0;` — Launches the specified profile. @param DeviceProxyManager The target device proxy manager to use. @param Profile The profile to launch. @return The worker thread, or nullptr if not launched.
- L40 _public prototype_ `virtual ~ILauncher( ) = default;` — Virtual destructor.
- L42 _public member_ `FOnLauncherWorkerStarted FLauncherWorkerStartedDelegate;`

#### Free symbols / members of external scopes

- L13 _typedef_ `typedef TSharedPtr<class ILauncher> ILauncherPtr;` — Type definition for shared pointers to instances of ILauncher.
- L16 _typedef_ `typedef TSharedRef<class ILauncher> ILauncherRef;` — Type definition for shared references to instances of ILauncher.
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLauncherWorkerStarted, ILauncherWorkerPtr, ILauncherProfileRef);`
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLauncherWorkerStarted, ILauncherWorkerPtr, ILauncherProfileRef);`

### `Source/Developer/LauncherServices/Public/ILauncherDeviceGroup.h` (Public)


#### class `ILauncherDeviceGroup`  
`class ILauncherDeviceGroup`  
_L37-116_
- desc: Interface for Launcher device groups.
- L46 _public prototype_ `virtual void AddDevice(const FString& DeviceID) = 0;` — Adds a device to the group. @param DeviceID The identifier of the device to add.
- L53 _public prototype_ `virtual const TArray<FString>& GetDeviceIDs() = 0;` — Get a list of identifiers for devices associated with this device group. @return The list of device identifiers.
- L60 _public prototype_ `virtual FGuid GetId() const = 0;` — Gets the unique identifier of the device group. @return The device group identifier.
- L67 _public prototype_ `virtual const FString& GetName() const = 0;` — Gets the human readable name of the device group. @return The name of the device group.
- L74 _public prototype_ `virtual int32 GetNumDevices() const = 0;` — Get a list of devices associated with this device group. @return The number of devices the device group maintains.
- L81 _public prototype_ `virtual void RemoveDevice(const FString& DeviceID) = 0;` — Removes a device from the group. @param DeviceID The identifier of the device to remove.
- L87 _public prototype_ `virtual void RemoveAllDevices() = 0;` — Removes all devices from the group.
- L94 _public prototype_ `virtual void SetName(const FString& NewName) = 0;` — Sets the name of the device group. @param NewName The new name.
- L103 _public prototype_ `virtual FOnLauncherDeviceGroupDeviceAdded& OnDeviceAdded() = 0;` — Returns a delegate that is invoked when device was added to this group. @return The delegate.
- L110 _public prototype_ `virtual FOnLauncherDeviceGroupDeviceRemoved& OnDeviceRemoved() = 0;` — Returns a delegate that is invoked when device was removed from this group. @return The delegate.
- L115 _public prototype_ `virtual ~ILauncherDeviceGroup() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef TSharedPtr<class ILauncherDeviceGroup> ILauncherDeviceGroupPtr;` — Type definition for shared pointers to instances of ILauncherDeviceGroup.
- L14 _typedef_ `typedef TSharedRef<class ILauncherDeviceGroup> ILauncherDeviceGroupRef;` — Type definition for shared references to instances of ILauncherDeviceGroup.
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLauncherDeviceGroupDeviceAdded, const ILauncherDeviceGroupRef&, const FString&) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLauncherDeviceGroupDeviceRemoved, const ILauncherDeviceGroupRef&, const FString&) class ILauncherDeviceGroup { public: virtual void AddDevice(const FString& DeviceID) = 0; virtual const TArray<FString>& GetDeviceIDs() = 0; virtual FGuid GetId() const = 0; /**` — Delegate type for adding devices. The first parameter is the device group that invoked the delegate. The second parameter is the identifier of the device that was removed.
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLauncherDeviceGroupDeviceRemoved, const ILauncherDeviceGroupRef&, const FString&) class ILauncherDeviceGroup { public: virtual void AddDevice(const FString& DeviceID) = 0; virtual const TArray<FString>& GetDeviceIDs() = 0; virtual FGuid GetId() const = 0; virtual const FString& GetName() const = 0; /** * Get a list of devices associated with this device group.` — Delegate type for removing devices. The first parameter is the device group that invoked the delegate. The second parameter is the identifier of the device that was removed.

### `Source/Developer/LauncherServices/Public/ILauncherProfile.h` (Public)


#### class `ILauncherSimpleProfile`  
`class ILauncherSimpleProfile`  
_L30-127_
- desc: Interface for simple launcher profile.
- L39 _public prototype_ `virtual const FString& GetDeviceName() const = 0;` — Gets the device name this profile is for. @return Device Name.
- L47 _public prototype_ `virtual FName GetDeviceVariant() const = 0;` — Gets the device variant to use when deploying and launching. @return Device Variant name. @see SetDeviceVariant
- L55 _public prototype_ `virtual EBuildConfiguration GetBuildConfiguration() const = 0;` — Gets the name of the build configuration. @return Build configuration name. @see SetBuildConfigurationName
- L62 _public prototype_ `virtual ELauncherProfileCookModes::Type GetCookMode() const = 0;` — Gets the selected cook mode. @return Cook mode.
- L69 _public prototype_ `virtual bool Load(const FJsonObject& Object) = 0;` — Loads the simple profile from the specified file. @return true if the profile was loaded, false otherwise.
- L76 _public prototype_ `virtual void Save(TJsonWriter<>& Writer) = 0;` — Saves the simple profile to the specified file. @return true if the profile was saved, false otherwise.
- L83 _public prototype_ `virtual void SetDeviceName(const FString& InDeviceName) = 0;` — Updates the device name. @param InDeviceName The new device name.
- L91 _public prototype_ `virtual void SetDeviceVariant(FName InVariant) = 0;` — Sets the device variant. @param InVariant The variant to set. @see GetDeviceVariant
- L99 _public prototype_ `virtual void SetBuildConfiguration(EBuildConfiguration InConfiguration) = 0;` — Sets the build configuration. @param InConfiguration The build configuration name to set. @see GetBuildConfigurationName
- L107 _public prototype_ `virtual void SetCookMode(ELauncherProfileCookModes::Type InMode) = 0;` — Sets the cook mode. @param InMode The cook mode. @see GetCookMode
- L116 _public prototype_ `virtual bool Serialize(FArchive& Archive) = 0;` — `UE_DEPRECATED(5.8, "this will be removed. there is no alternative implementation : ILauncherSimpleProfile is designed to be transient")` — Serializes the simple profile from or into the specified archive. @param Archive The archive to serialize from or into. @return true if the profile was serialized, false otherwise.
- L119 _public prototype_ `virtual void SetDefaults() = 0;` — Sets all profile settings to their defaults.
- L126 _public prototype_ `virtual ~ILauncherSimpleProfile() = default;` — Virtual destructor.

#### class `ILauncherProfile`  
`class ILauncherProfile`  
_L170-1720_
- desc: Interface for launcher profile.
- L179 _public prototype_ `virtual FGuid GetId( ) const = 0;` — Gets the unique identifier of the profile. @return The profile identifier.
- L186 _public prototype_ `virtual FString GetFileName( ) const = 0;` — Gets the file name for serialization. @return The file name.
- L193 _public prototype_ `virtual FString GetFilePath() const = 0;` — Gets the full file path for serialization. @return The file path.
- L200 _public prototype_ `virtual FString GetName( ) const = 0;` — Gets the human readable name of the profile. @return The profile name.
- L207 _public prototype_ `virtual FString GetDescription() const = 0;` — Gets the human readable description of the profile. @return The profile description.
- L215 _public prototype_ `virtual bool HasValidationError(ILauncherProfileUATCommandPtr UATCommand = nullptr) const = 0;` — Checks whether the last validation yielded any error. @param UATCommand Optional UAT command associated with this error @return true if the any error is present, false otherwise.
- L224 _public prototype_ `virtual bool HasValidationError( ELauncherProfileValidationErrors::Type Error, ILauncherProfileUATCommandPtr UATCommand = nullptr ) const = 0;` — Checks whether the last validation yielded the specified error. @param Error The validation error to check for. @param UATCommand Optional UAT command associated with this error @return true if the error is present, false otherwise.
- L236 _public prototype_ `virtual void AddCustomError( const FString& UniqueId, const FText& Text, ILauncherProfileUATCommandPtr UATCommand = nullptr ) = 0;` — Add a custom error. This will prevent launching @param UniqueId Unique identifier for this error @param Text Localized string describing this error @param UATCommand Optional UAT command associated with this error
- L244 _public prototype_ `virtual bool HasCustomError( const FString& UniqueId, ILauncherProfileUATCommandPtr UATCommand = nullptr ) const = 0;` — Checks whether this profile has the given custom error @param UniqueId Unique identifier for this error
- L252 _public prototype_ `virtual FText GetCustomErrorText( const FString& UniqueId, ILauncherProfileUATCommandPtr UATCommand = nullptr ) const = 0;` — Gets the localized string representation of the given error @param UniqueId @returns Localized string describing this error, or empty text if we don't have it
- L259 _public prototype_ `virtual TArray<FString> GetAllCustomErrors(ILauncherProfileUATCommandPtr UATCommand = nullptr) const = 0;` — Gets all custom errors in this profile @returns UniqueIds for all custom errors in this profile
- L270 _public prototype_ `virtual void AddCustomWarning( const FString& UniqueId, const FText& Text, ILauncherProfileUATCommandPtr UATCommand = nullptr ) = 0;` — Add a custom warning. This does not prevent launching. @param UniqueId Unique identifier for this warning @param Text Localized string describing this warning @param UATCommand Optional UAT command associated with this warning
- L277 _public prototype_ `virtual bool HasCustomWarning( const FString& UniqueId, ILauncherProfileUATCommandPtr UATCommand = nullptr ) const = 0;` — Checks whether this profile has the given custom warning @param UniqueId Unique identifier for this warning
- L285 _public prototype_ `virtual FText GetCustomWarningText( const FString& UniqueId, ILauncherProfileUATCommandPtr UATCommand = nullptr ) const = 0;` — Gets the localized string representation of the given warning @param UniqueId @returns Localized string describing this warning, or empty text if we don't have it
- L292 _public prototype_ `virtual TArray<FString> GetAllCustomWarnings(ILauncherProfileUATCommandPtr UATCommand = nullptr) const = 0;` — Gets all custom warnings in this profile @returns UniqueIds for all custom warnings in this profile
- L298 _public prototype_ `virtual void RefreshCustomWarningsAndErrors(ILauncherProfileUATCommandPtr UATCommand = nullptr) = 0;` — Refreshes the custom warnings and errors. Resets the lists and triggers the OnValidation callback.
- L307 _public prototype_ `virtual FString GetInvalidPlatform(ILauncherProfileUATCommandPtr UATCommand = nullptr) const = 0;` — Gets the invalid platform, this is only valid when there is a platform centric validation error. @return string specifying the invalid platform.
- L319 _public prototype_ `virtual bool IsDeployablePlatform( const FString& PlatformName ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Checks whether devices of the specified platform can be deployed to. Whether a platform is deployable depends on the current profile settings. The right combination of build, cook and package settings must be present. @param PlatformName The name of the platform to deploy. @return true if the platform is deployable, false otherwise.
- L326 _public prototype_ `virtual bool IsValidForLaunch( ) = 0;` — Checks whether this profile is valid to use when running a game instance. @return Whether the profile is valid or not.
- L331 _public prototype_ `virtual bool Load(const FJsonObject& Object) = 0;` — Loads the profile from a JSON file
- L340 _public prototype_ `virtual bool Serialize( FArchive& Archive ) = 0;` — `UE_DEPRECATED(5.8, "please use the Json Save/Load API instead")` — Serializes the profile from or into the specified archive. @param Archive The archive to serialize from or into. @return true if the profile was serialized, false otherwise.
- L345 _public prototype_ `virtual void Save(TJsonWriter<>& Writer) = 0;` — Saves the profile into a JSON file
- L348 _public prototype_ `virtual void SetDefaults( ) = 0;` — Sets all profile settings to their defaults.
- L353 _public prototype_ `virtual void AssignId( bool bOverrideExisting = false) = 0;` — Ensures this profile has an Id, if it doesn't already have one
- L360 _public prototype_ `virtual void SetName( const FString& NewName ) = 0;` — Updates the name of the profile. @param NewName The new name of the profile.
- L367 _public prototype_ `virtual void SetDescription(const FString& NewDescription) = 0;` — Updates the description of the profile. @param NewDescription The new description of the profile.
- L373 _public prototype_ `virtual void SetNotForLicensees() = 0;` — Changes the save location to an internal project path.
- L380 _public prototype_ `virtual FIsCookFinishedDelegate& OnIsCookFinished() = 0;` — Returns the cook delegate which can be used to query if the cook is finished. Used by cook by the book in the editor.
- L386 _public prototype_ `virtual FCookCanceledDelegate& OnCookCanceled() = 0;` — Returns the cook delegate which should be called if the cook is canceled Used by cook by the book in the editor
- L397 _public prototype_ `virtual EBuildConfiguration GetBuildConfiguration( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the name of the build configuration. @return Build configuration name. @see SetBuildConfigurationName
- L405 _public prototype_ `virtual bool HasBuildTargetSpecified() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Checks whether the profile specifies a build target. @return true if the profile specifies a build target.
- L414 _public prototype_ `virtual FString GetBuildTarget() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version and GetBuildTargets")` — Gets the build target. @Return Target name to build/run (it would match a .Target.cs file) @see SetBuildTarget
- L423 _public prototype_ `virtual EBuildConfiguration GetCookConfiguration( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the build configuration name of the cooker. @return Cook configuration name. @see SetCookConfigurationName
- L431 _public prototype_ `virtual ELauncherProfileCookModes::Type GetCookMode( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the selected cook mode. @return Cook mode.
- L439 _public prototype_ `virtual const FString& GetCookOptions( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the cooker command line options. @return Cook options string.
- L443 _public prototype_ `virtual const bool GetSkipCookingEditorContent() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L452 _public prototype_ `virtual void SetSkipCookingEditorContent(const bool InSkipCookingEditorContent) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Skip editor content while cooking, This will strip editor content from final builds @param InSkipCookingEditorContent
- L462 _public prototype_ `virtual const TArray<FString>& GetCookedCultures( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the list of cooked culture. @return Collection of culture names. @see AddCookedCulture, ClearCookedCultures, RemoveCookedCulture
- L472 _public prototype_ `virtual const TArray<FString>& GetCookedMaps( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the list of cooked maps. @return Collection of map names. @see AddCookedMap, ClearCookedMaps, RemoveCookedMap
- L482 _public prototype_ `virtual const TArray<FString>& GetCookedPlatforms( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the names of the platforms to build for. @return Read-only collection of platform names. @see AddCookedPlatform, ClearCookedPlatforms, RemoveCookedPlatform
- L490 _public prototype_ `virtual const ILauncherProfileLaunchRoleRef& GetDefaultLaunchRole( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the default launch role. @return A reference to the default launch role.
- L499 _public prototype_ `virtual ILauncherDeviceGroupPtr GetDeployedDeviceGroup( ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the device group to deploy to. @return The device group, or NULL if none was configured. @see SetDeployedDeviceGroup
- L506 _public prototype_ `virtual const FName GetDefaultDeployPlatform() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the default platforms to deploy if no specific devices were selected.
- L515 _public prototype_ `virtual ELauncherProfileDeploymentModes::Type GetDeploymentMode( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the deployment mode. @return The deployment mode. @see SetDeploymentMode
- L524 _public prototype_ `virtual bool GetForceClose() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the close mode for the cook on the fly server @return The close mode. @see SetForceClose
- L533 _public prototype_ `virtual ELauncherProfileLaunchModes::Type GetLaunchMode( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the launch mode. @return The launch mode. @see SetLaunchMode
- L542 _public prototype_ `virtual const TArray<ILauncherProfileLaunchRolePtr>& GetLaunchRoles( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the profile's collection of launch roles. @return A read-only collection of launch roles. @see CreateLaunchRole, RemoveLaunchRole
- L551 _public prototype_ `virtual const int32 GetLaunchRolesFor( const FString& DeviceId, TArray<ILauncherProfileLaunchRolePtr>& OutRoles ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the launch roles assigned to the specified device. @param DeviceId The identifier of the device. @param OutRoles Will hold the assigned roles, if any.
- L560 _public prototype_ `virtual ELauncherProfilePackagingModes::Type GetPackagingMode( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the packaging mode. @return The packaging mode. @see SetPackagingMode
- L569 _public prototype_ `virtual FString GetPackageDirectory( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the packaging directory. @return The packaging directory. @see SetPackageDirectory
- L577 _public prototype_ `virtual bool IsArchiving( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Whether to archive build @see SetArchive
- L586 _public prototype_ `virtual FString GetArchiveDirectory( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the archive directory. @return The archive directory. @see SetArchiveDirectory
- L594 _public prototype_ `virtual bool HasProjectSpecified() const = 0;` — Checks whether the profile specifies a project. Not specifying a project means that it can be used for any project. @return true if the profile specifies a project.
- L599 _public prototype_ `virtual FString GetProjectName( ) const = 0;` — Gets the name of the Unreal project to use.
- L604 _public prototype_ `virtual FString GetProjectBasePath() const = 0;` — Gets the base project path for the project (e.g. Samples/Showcases/MyShowcase)
- L612 _public prototype_ `virtual FString GetProjectPath( ) const = 0;` — Gets the full path to the Unreal project to use. @return The path. @see SetProjectPath
- L622 _public prototype_ `virtual FString GetAdditionalCommandLineParameters() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the additional command line parameters that will be used when the app launches. These will be used by all launch roles @return The additional command line parameters @see SetAdditionalCommandLineParameters
- L632 _public prototype_ `virtual FString GetAdditionalTargetCommandLineParameters( EBuildTargetType BuildTargetType ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the additional command line parameters that will be used for the given target type when the app launches. @param	BuildTargetType	The type of build target to query @return The additional command line parameters @see SetAdditionalTargetCommandLineParameters
- L641 _public prototype_ `virtual uint32 GetTimeout() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the timeout time for the cook on the fly server. @return The timeout time. @see SetTimeout
- L648 _public prototype_ `virtual bool IsGeneratingPatch() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Are we going to generate a patch (Source content patch needs to be specified) @Seealso GetPatchSourceContentPath	 * @Seealso SetPatchSourceContentPath
- L653 _public prototype_ `virtual bool ShouldAddPatchLevel() const = 0;` — Are we going to generate a new patch tier
- L659 _public prototype_ `virtual bool ShouldStageBaseReleasePaks() const = 0;` — `UE_DEPRECATED(5.6, "ShouldStageBaseReleasePaks is no longer used")` — Should we stage the pak files from the base release version this patch is built on
- L668 _public prototype_ `virtual ELauncherProfileBuildModes::Type GetBuildMode() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the current build mode. @return The current build mode. @see SetBuildMode
- L677 _public prototype_ `virtual bool ShouldBuild() = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Determines whether the current profile requires building @return The current build mode. @see SetBuildMode
- L686 _public prototype_ `virtual bool IsFastIterate() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Checks if fast iterate is enabled. @return true if fast iterate is enabled, false otherwise. @see SetFastIterate
- L694 _public prototype_ `virtual bool IsBuildingUAT() const = 0;` — Checks whether UAT should be built. @return true if building UAT, false otherwise. @see SetBuildGame
- L703 _public prototype_ `virtual bool IsCookingIncrementally( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Checks whether legacy incremental cooking is enabled. @return true if cooking incrementally, false otherwise. @see SetIncrementalCooking
- L712 _public prototype_ `virtual ELauncherProfileIncrementalCookMode::Type GetIncrementalCookMode() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version and IsCookingIncrementally again instead")` — Get the current incremental cook mode @return incremental cook mode @see SetIncrementalCookMode
- L715 _public prototype_ `virtual bool IsIterateSharedCookedBuild() const =0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L724 _public prototype_ `virtual bool IsCompressed( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Checks if compression is enabled @return true if compression is enabled @see SetCompressed
- L732 _public prototype_ `virtual bool IsEncryptingIniFiles() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Checks if encrypting ini files is enabled @return true if encrypting ini files is enabled
- L740 _public prototype_ `virtual bool IsForDistribution() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Checks if encrypting ini files is enabled @return true if encrypting ini files is enabled
- L749 _public prototype_ `virtual bool IsCookingUnversioned( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Checks whether unversioned cooking is enabled. @return true if cooking unversioned, false otherwise. @see SetUnversionedCooking
- L758 _public prototype_ `virtual bool IsDeployingIncrementally( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Checks whether incremental deployment is enabled. @return true if deploying incrementally, false otherwise. @see SetIncrementalDeploying
- L767 _public prototype_ `virtual bool IsFileServerHidden( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Checks whether the file server's console window should be hidden. @return true if the file server should be hidden, false otherwise. @see SetHideFileServer
- L776 _public prototype_ `virtual bool IsFileServerStreaming( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Checks whether the file server is a streaming file server. @return true if the file server is streaming, false otherwise. @see SetStreamingFileServer
- L785 _public prototype_ `virtual bool IsPackingWithUnrealPak( ) const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Checks whether packaging with UnrealPak is enabled. @return true if UnrealPak is used, false otherwise. @see SetPackageWithUnrealPak
- L794 _public prototype_ `virtual bool IsIncludingPrerequisites() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Checks whether to include an installer for prerequisites of packaged games, such as redistributable operating system components, on platforms that support it. @return true if prerequisites are to be included, false otherwise. @see SetIncludePrerequisites
- L802 _public prototype_ `virtual bool IsGeneratingChunks() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Return whether packaging will generate chunk data. @return true if Chunks will be generated, false otherwise.
- L810 _public prototype_ `virtual bool IsGenerateHttpChunkData() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Return whether packaging will use chunk data to generate http chunk install data. @return true if data will be generated, false otherwise.
- L818 _public prototype_ `virtual FString GetHttpChunkDataDirectory() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Where generated http chunk install data will be stored. @return true if data will be generated, false otherwise.
- L826 _public prototype_ `virtual FString GetHttpChunkDataReleaseName() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — What name to tag the generated http chunk install data with. @return true if data will be generated, false otherwise.
- L833 _public prototype_ `virtual bool SupportsEngineMaps( ) const = 0;` — Checks whether the profile's selected project supports Engine maps. @return true if Engine maps are supported, false otherwise.
- L840 _public prototype_ `virtual void SetEditorExe( const FString& EditorExe ) = 0;` — Sets the path to the editor executable to use in UAT. @param EditorExe Path to the editor executable.
- L847 _public prototype_ `virtual FString GetEditorExe( ) const = 0;` — Gets the path to the editor executable. @return Path to the editor executable.
- L859 _public prototype_ `virtual void AddCookedCulture( const FString& CultureName ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Adds a culture to cook (only used if cooking by the book). @param CultureName The name of the culture to cook. @see ClearCookedCultures, GetCookedCultures, RemoveCookedCulture
- L869 _public prototype_ `virtual void AddCookedMap( const FString& MapName ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Adds a map to cook (only used if cooking by the book). @param MapName The name of the map to cook. @see ClearCookedMaps, GetCookedMaps, RemoveCookedMap
- L879 _public prototype_ `virtual void AddCookedPlatform( const FString& PlatformName ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Adds a platform to cook (only used if cooking by the book). @param PlatformName The name of the platform to add. @see ClearCookedPlatforms, GetCookedPlatforms, RemoveCookedPlatform
- L889 _public prototype_ `virtual void SetDefaultDeployPlatform(const FName PlatformName) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Adds a platform to deploy (only used if a specific device is not specified). Will deploy to the default device of the given platform, or the first device if none are marked as 'default'. @param PlatformName The name of the platform to add.
- L897 _public prototype_ `virtual void ClearCookedCultures( ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Removes all cooked cultures. @see AddCookedCulture, GetCookedCulture, RemoveCookedCulture
- L905 _public prototype_ `virtual void ClearCookedMaps( ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Removes all cooked maps. @see AddCookedMap, GetCookedMap, RemoveCookedMap
- L913 _public prototype_ `virtual void ClearCookedPlatforms( ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Removes all cooked platforms. @see AddCookedPlatform, GetCookedPlatforms, RemoveCookedPlatform
- L922 _public prototype_ `virtual ILauncherProfileLaunchRolePtr CreateLaunchRole( ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Creates a new launch role and adds it to the profile. @return The created role. @see GetLaunchRoles, RemoveLaunchRole
- L931 _public prototype_ `virtual void RemoveCookedCulture( const FString& CultureName ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Removes a cooked culture. @param CultureName The name of the culture to remove. @see AddCookedCulture, ClearCookedCultures, GetCookedCultures
- L940 _public prototype_ `virtual void RemoveCookedMap( const FString& MapName ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Removes a cooked map. @param MapName The name of the map to remove. @see AddCookedMap, ClearCookedMaps, GetCookedMaps
- L949 _public prototype_ `virtual void RemoveCookedPlatform( const FString& PlatformName ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Removes a platform from the cook list. @param PlatformName The name of the platform to remove. @see AddBuildPlatform, ClearCookedPlatforms, GetBuildPlatforms
- L958 _public prototype_ `virtual void RemoveLaunchRole( const ILauncherProfileLaunchRoleRef& Role ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Removes the given launch role from the profile. @param Role The role to remove. @see CreateLaunchRole, GetLaunchRoles
- L967 _public prototype_ `virtual void SetBuildMode(ELauncherProfileBuildModes::Type Mode) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the current build mode @param Mode Whether the game should be built. @see GetBuildMode
- L976 _public prototype_ `virtual void SetFastIterate(bool Enable) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets fast iterate. @param Enable fast iterate. @see IsFastIterate
- L984 _public prototype_ `virtual void SetBuildUAT( bool Build ) = 0;` — Sets whether to build UAT. @param Build Whether UAT should be built. @see IsBuilding
- L993 _public prototype_ `virtual void SetBuildConfiguration( EBuildConfiguration Configuration ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the build configuration. @param ConfigurationName The build configuration name to set. @see GetBuildConfigurationName
- L1001 _public prototype_ `virtual void SetBuildTargetSpecified(bool Specified) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets whether this profile specfies a build target. @param Specified Whether a build target is specified.
- L1004 _public prototype_ `virtual void FallbackBuildTargetUpdated() = 0;` — Notifies the profile that the fallback build target changed.
- L1013 _public prototype_ `virtual void SetBuildTarget( const FString& TargetName ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version and AddBuildTarget instead")` — Sets the build target. @param TargetName The target name to set (it would match a .Target.cs file) @see GetBuildTarget
- L1022 _public prototype_ `virtual void SetCookConfiguration( EBuildConfiguration Configuration ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the build configuration of the cooker. @param Configuration The cooker's build configuration to set. @see GetCookConfiguration
- L1031 _public prototype_ `virtual void SetCookMode( ELauncherProfileCookModes::Type Mode ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the cook mode. @param Mode The cook mode. @see GetCookMode
- L1040 _public prototype_ `virtual void SetCookOptions(const FString& Options) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the cook options. @param Options The cook options. @see GetCookOptions
- L1049 _public prototype_ `virtual void SetDeployWithUnrealPak( bool UseUnrealPak ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets whether to pack with UnrealPak. @param UseUnrealPak Whether UnrealPak should be used. @see IsPackingWithUnrealPak
- L1057 _public prototype_ `virtual void SetGenerateChunks(bool bGenerateChunks) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Set whether packaging will generate chunk data. @param true if Chunks should be generated, false otherwise.
- L1064 _public prototype_ `virtual void SetGenerateHttpChunkData(bool bGenerateHttpChunkData) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Set whether packaging will use chunk data to generate http chunk install data. @param true if data should be generated, false otherwise.
- L1071 _public prototype_ `virtual void SetHttpChunkDataDirectory(const FString& InHttpChunkDataDirectory ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Set where generated http chunk install data will be stored. @return the directory path to use.
- L1078 _public prototype_ `virtual void SetHttpChunkDataReleaseName(const FString& InHttpChunkDataReleaseName ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Set what name to tag the generated http chunk install data with. @param the name to use.
- L1087 _public prototype_ `virtual void SetDeployedDeviceGroup( const ILauncherDeviceGroupPtr& DeviceGroup ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the device group to deploy to. @param DeviceGroup The device group, or NULL to reset this setting. @see GetDeployedDeviceGroup
- L1096 _public prototype_ `virtual void SetDeploymentMode( ELauncherProfileDeploymentModes::Type Mode ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the deployment mode. @param Mode The deployment mode to set. @see GetDeploymentMode
- L1102 _public prototype_ `virtual bool IsCreatingReleaseVersion() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Creating a release version of the cooked content
- L1105 _public prototype_ `virtual void SetCreateReleaseVersion(bool InCreateReleaseVersion) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1108 _public prototype_ `virtual FString GetCreateReleaseVersionName() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1111 _public prototype_ `virtual void SetCreateReleaseVersionName(const FString& InCreateReleaseVersionName) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1114 _public prototype_ `virtual FString GetBasedOnReleaseVersionName() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1117 _public prototype_ `virtual void SetBasedOnReleaseVersionName(const FString& InBasedOnReleaseVersion) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1120 _public prototype_ `virtual FString GetOriginalReleaseVersionName() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1123 _public prototype_ `virtual void SetOriginalReleaseVersionName(const FString& InOriginalReleaseVersion) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1130 _public prototype_ `virtual FString GetReferenceContainerGlobalFileName() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Provides a database of compressed iostore chunks to reuse during the staging process. See IoStoreUtilities.cpp ReferenceContainerGlobalFileName.
- L1132 _public prototype_ `virtual void SetReferenceContainerGlobalFileName(const FString& InReferenceContainerGlobalFileName) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1134 _public prototype_ `virtual FString GetReferenceContainerCryptoKeysFileName() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1136 _public prototype_ `virtual void SetReferenceContainerCryptoKeysFileName(const FString& InReferenceContainerCryptoKeysFileName) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1145 _public prototype_ `virtual void SetGeneratePatch( bool InShouldGeneratePatch ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets if we are going to generate a patch @param InShouldGeneratePatch enable generating patch @seealso IsGeneratingPatch
- L1147 _public prototype_ `virtual void SetAddPatchLevel( bool InAddPatchLevel) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1149 _public prototype_ `virtual void SetStageBaseReleasePaks(bool InStageBaseReleasePaks) = 0;` — `UE_DEPRECATED(5.6, "ShouldStageBaseReleasePaks is no longer used")`
- L1152 _public prototype_ `virtual bool IsCreatingDLC() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1154 _public prototype_ `virtual void SetCreateDLC(bool InBuildDLC) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1157 _public prototype_ `virtual FString GetDLCName() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1159 _public prototype_ `virtual void SetDLCName(const FString& InDLCName) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1162 _public prototype_ `virtual bool IsDLCIncludingEngineContent() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1164 _public prototype_ `virtual void SetDLCIncludeEngineContent(bool InDLCIncludeEngineContent) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1174 _public prototype_ `virtual void SetForceClose( bool Close ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the cook on the fly close mode @param Close the close mode to set. @see GetForceClose
- L1183 _public prototype_ `virtual void SetHideFileServerWindow( bool Hide ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets whether to hide the file server's console window. @param Hide Whether to hide the window. @see GetHideFileServerWindow
- L1192 _public prototype_ `virtual void SetIncrementalCooking( bool Incremental ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets legacy incremental cooking. @param Incremental Whether cooking should be incremental. @see IsCookingIncrementally
- L1201 _public prototype_ `virtual void SetIncrementalCookMode( ELauncherProfileIncrementalCookMode::Type Mode ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version with SetIncrementalCooking again instead")` — Set the incremental cook mode. @param Mode the incremental cooking mode to use @see GetIncrementalCookMode
- L1204 _public prototype_ `virtual void SetIterateSharedCookedBuild( bool IterateSharedCookedBuild ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")`
- L1213 _public prototype_ `virtual void SetCompressed( bool Enable ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets Compression. @param Enable compression @see IsCompressed
- L1223 _public prototype_ `virtual void SetEncryptingIniFiles(bool Enabled) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Set encrypt ini files @param Enable encrypt ini files @see IsEncryptIniFiles
- L1232 _public prototype_ `virtual void SetForDistribution(bool Enabled) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Set this build is for distribution to the public @param enable for distribution @see IsForDistribution
- L1242 _public prototype_ `virtual void SetIncrementalDeploying( bool Incremental ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets incremental deploying. @param Incremental Whether deploying should be incremental. @see IsDeployingIncrementally
- L1251 _public prototype_ `virtual void SetLaunchMode( ELauncherProfileLaunchModes::Type Mode ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the launch mode. @param Mode The launch mode to set. @see GetLaunchMode
- L1260 _public prototype_ `virtual void SetPackagingMode( ELauncherProfilePackagingModes::Type Mode ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the packaging mode. @param Mode The packaging mode to set. @see GetPackagingMode
- L1269 _public prototype_ `virtual void SetPackageDirectory( const FString& Dir ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the packaging directory. @param Dir The packaging directory to set. @see GetPackageDirectory
- L1277 _public prototype_ `virtual void SetArchive( bool bArchive ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets whether to archive build @see GetArchiveMode
- L1286 _public prototype_ `virtual void SetArchiveDirectory( const FString& Dir ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the archive directory. @param Dir The archive directory to set. @see GetArchiveDirectory
- L1293 _public prototype_ `virtual void SetProjectSpecified(bool Specified) = 0;` — Sets whether this profile specifies the a project. @param Specified Whether a project is specified.
- L1296 _public prototype_ `virtual void FallbackProjectUpdated() = 0;` — Notifies the profile that the fallback project path changed.
- L1304 _public prototype_ `virtual void SetProjectPath( const FString& Path ) = 0;` — Sets the path to the Unreal project to use. @param Path The full path to the project. @see GetProjectPath
- L1314 _public prototype_ `virtual void SetAdditionalCommandLineParameters(const FString& Params) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the additional command line parameters for the application to use at launch. These will be used by all launch roles @param	Params	The additional command line parameters to use @see GetAdditionalCommandLineParameters
- L1324 _public prototype_ `virtual void SetAdditionalTargetCommandLineParameters(const FString& Params, EBuildTargetType BuildTargetType ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the additional command line parameters that will be used for the given target type when the app launches. @param	Params	The additional command line parameters to use @param	BuildTargetType	The type of build target to modify @see GetAdditionalTargetCommandLineParameters
- L1334 _public prototype_ `virtual void SetStreamingFileServer( bool Streaming ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets whether to use a streaming file server. @param Streaming Whether a streaming server should be used. @see GetStreamingFileServer
- L1343 _public prototype_ `virtual void SetIncludePrerequisites(bool InValue) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets whether to include game prerequisites. @param Value Whether prerequisites should be used. @see IsIncludingPrerequisites
- L1352 _public prototype_ `virtual void SetTimeout(uint32 InTime) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the cook on the fly server timeout @param InTime Amount of time to wait before timing out. @see GetTimeout
- L1361 _public prototype_ `virtual void SetUnversionedCooking( bool Unversioned ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets unversioned cooking. @param Unversioned Whether cooking is unversioned. @see IsCookingUnversioned
- L1368 _public prototype_ `virtual FOnProfileProjectChanged& OnProjectChanged() = 0;` — Accesses delegate used when the project changes. @return The delegate.
- L1376 _public prototype_ `virtual FOnProfileBuildTargetOptionsChanged& OnBuildTargetOptionsChanged() = 0;` — `UE_DEPRECATED(5.8, "this was only used for the legacy project launcher")` — Access delegate used when build target options change. @return The delegate.
- L1383 _public prototype_ `virtual FOnProfileCustomValidation& OnCustomValidation() = 0;` — Access delegate used when validation changes to gather custom warnings and errors @return The delegate.
- L1390 _public prototype_ `virtual FOnProfileCustomUATCommandValidation& OnCustomUATCommandValidation() = 0;` — Access delegate used when validation changes to gather custom warnings and errors for custom UAT commands @return The delegate.
- L1397 _public prototype_ `virtual void SetUseIoStore(bool bUseIoStore) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets whether to use I/O store for optimized loading. @param bUseIoStore Whether to use I/O store
- L1405 _public prototype_ `virtual bool IsUsingIoStore() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Using I/O store or not. @return true if using I/O store
- L1412 _public prototype_ `virtual void SetUseZenStore(bool bUseZenStore) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets whether to use the Zen storage server. Note, this property is ignored if the project itself is configured to use Zen store (via UProjectPackagingSettings::bUseZenStore) @param bUseZenStore Whether to use the Zen storage server
- L1420 _public prototype_ `virtual bool IsUsingZenStore() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Using Zen storage server or not. @return true if using Zen storage server
- L1427 _public prototype_ `virtual int32 GetZenSnapshot() = 0;` — Get the Zen snapshot build number used for import. @return Zen snapshot build number
- L1435 _public prototype_ `virtual void SetImportingZenSnapshot( bool Import ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Set whether to import a Zen snapshot before cooking. @param Import Whether to import a Zen snapshot
- L1443 _public prototype_ `virtual bool IsImportingZenSnapshot() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Checks whether a Zen snapshot will be imported before cooking. @return true if importing a Zen snapshot, false otherwise
- L1451 _public prototype_ `virtual void SetUseZenPakStreaming( bool UseZenPakStreaming ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Set whether to use Zen pak streaming. @param UseZenPakStreaming Whether use Zen pak streaming.
- L1459 _public prototype_ `virtual bool IsUsingZenPakStreaming() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Checks whether Zen pak streaming will be used. @return true if using Zen pak streaming, false otherwise
- L1468 _public prototype_ `virtual void SetZenPakStreamingPath( const FString& Path ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets whether to use Zen pak streaming from the given path. Assumes the path contains a suitable build @param Path Path to the build to use for Zen pak streaming
- L1476 _public prototype_ `virtual FString GetZenPakStreamingPath() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Get the current Zen pak streaming path, if it is being used. @return current Zen pak streaming path, if any
- L1483 _public prototype_ `virtual void SetMakeBinaryConfig(bool bMakeBinaryConfig) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets whether to make a binary config file during packaging @param bMakeBinaryConfig Whether to make a binary config file during staging
- L1490 _public prototype_ `virtual bool MakeBinaryConfig() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Make binary config file during staging or not. @return true to make binary config file
- L1495 _public prototype_ `virtual void SetShouldUpdateDeviceFlash(bool bInShouldUpdateFlash) = 0;` — Sets whether or not the flash image/software on the device should attempt to be updated before running
- L1500 _public prototype_ `virtual bool ShouldUpdateDeviceFlash() const = 0;` — Whether or not the flash image/software on the device should attempt to be updated before running
- L1506 _public prototype_ `virtual void SetDeviceIsASimulator(bool bInIsDeviceASimualtor) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets whether or not the Device is a Simulator
- L1512 _public prototype_ `virtual bool IsDeviceASimulator() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Whether or not the Device is a Simulator
- L1518 _public prototype_ `virtual void SetClientArchitectures( const TArray<FString>& InArchitectures ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the client architecture(s) to build (x64, arm64 etc). Leave empty to use the default
- L1524 _public prototype_ `virtual const TArray<FString>& GetClientArchitectures() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Returns the client architecture(s) that will be build. empty means the default will be used
- L1530 _public prototype_ `virtual void SetServerArchitectures( const TArray<FString>& InArchitectures ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the server architecture(s) to build (x64, arm64 etc). Leave empty to use the default
- L1536 _public prototype_ `virtual const TArray<FString>& GetServerArchitectures() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Returns the server architecture(s) that will be build. empty means the default will be used
- L1542 _public prototype_ `virtual void SetEditorArchitectures( const TArray<FString>& InArchitectures ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Sets the editor architecture(s) to build (x64, arm64 etc). Leave empty to use the default
- L1548 _public prototype_ `virtual const TArray<FString>& GetEditorArchitectures() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Returns the editor architecture(s) that will be build. empty means the default will be used
- L1558 _public prototype_ `virtual const TArray<ILauncherProfileUATCommandRef>& GetUATCommands() const = 0;` — Returns a list of all UAT commands in the profile
- L1563 _public prototype_ `virtual ILauncherProfileUATCommandPtr GetUATCommand( const TCHAR* InternalName ) const = 0;` — Returns an existing UAT command by internal name
- L1569 _public prototype_ `virtual ILauncherProfileUATCommandRef FindOrAddUATCommand( const TCHAR* InternalName, const TCHAR* UserTypeName = nullptr ) = 0;` — Returns an UAT command by internal name, creating it if it doesn't already exist Passing a null internal name will generate a new unique name
- L1574 _public prototype_ `virtual void RemoveUATCommand( const TCHAR* InternalName ) = 0;` — Removes an UAT command by internal name
- L1580 _public prototype_ `virtual FOnLauncherProfileUATCommandChanged& OnUATCommandAdded() = 0;` — Callback for when a UAT command is added
- L1585 _public prototype_ `virtual FOnLauncherProfileUATCommandChanged& OnUATCommandRemoved() = 0;` — Callback for when a UAT command is removed, prior to deletion
- L1596 _public prototype_ `virtual const TArray<ILauncherProfileBuildCookRunRef> GetBuildCookRunCommands() const = 0;` — Returns a list of all build cook run commands in the profile
- L1601 _public prototype_ `virtual ILauncherProfileBuildCookRunPtr GetBuildCookRunCommand( const TCHAR* InternalName ) const = 0;` — Return an existing UAT build cook run command by internal name
- L1607 _public prototype_ `virtual ILauncherProfileBuildCookRunRef FindOrAddBuildCookRunCommand( const TCHAR* InternalName, const TCHAR* UserTypeName = nullptr ) = 0;` — Returns a UAT build cook run command by internal name, creating it if it doesn't already exist Passing a null internal name will generate a new unique name
- L1615 _public prototype_ `virtual const TArray<ILauncherProfileAutomatedTestRef> GetAutomatedTests() const = 0;` — Returns a list of all automated tests in the profile
- L1620 _public prototype_ `virtual ILauncherProfileAutomatedTestPtr GetAutomatedTest( const TCHAR* InternalName ) const = 0;` — Returns an existing automated test by internal name
- L1626 _public prototype_ `virtual ILauncherProfileAutomatedTestRef FindOrAddAutomatedTest( const TCHAR* InternalName, const TCHAR* UserTypeName = nullptr ) = 0;` — Returns an automated test by internal name, creating it if it doesn't already exist Passing a null internal name will generate a new unique name
- L1631 _public prototype_ `virtual void RemoveAutomatedTest( const TCHAR* InternalName ) = 0;` — Removes an automated test by internal name
- L1637 _public prototype_ `virtual void SetAutomatedTestBuildPath( const FString& AutomatedTestBuildPath ) = 0;` — Sets the build to use for ALL automated tests, equivalent to the -build parameter on RunUnreal etc. See also SetIsUsingAutomatedTestBuild.
- L1642 _public prototype_ `virtual const FString& GetAutomatedTestBuildPath() const = 0;` — Returns the current automated test build path
- L1647 _public prototype_ `virtual void SetIsUsingAutomatedTestBuild( bool bWantAutomatedTestBuild ) = 0;` — Set whether to use the specified automated test build or the current launch build. Default is to use the current build.
- L1652 _public prototype_ `virtual bool IsUsingAutomatedTestBuild() const = 0;` — Returns whether we are using the specified automated test build or not.
- L1662 _public prototype_ `virtual TArray<FString> GetBuildTargets() const = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Gets the names of the build targets @see AddBuildTarget, RemoveBuildTarget, ClearBuildTargets
- L1669 _public prototype_ `virtual void AddBuildTarget( const FString& InBuildTarget ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Add a build target to the list @see GetBuildTargets, RemoveBuildTarget, ClearBuildTargets
- L1676 _public prototype_ `virtual void RemoveBuildTarget( const FString& InBuildTarget ) = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Remove a build target from the list @see GetBuildTargets, AddBuildTarget, ClearBuildTargets
- L1683 _public prototype_ `virtual void ClearBuildTargets() = 0;` — `UE_DEPRECATED(5.8, "use GetFirstBuildCookRun version")` — Clears the list of build targets @see GetBuildTargets, AddBuildTarget, RemoveBuildTarget
- L1692 _public prototype_ `virtual TArray<FString> GetExplicitBuildTargetNames() const = 0;` — `UE_DEPRECATED(5.8, "this was only used for the legacy project launcher")` — Helper function to get all of the build targets available for this profile, based on its current project & cook platforms
- L1698 _public prototype_ `virtual bool RequiresExplicitBuildTargetName() const = 0;` — `UE_DEPRECATED(5.8, "this was only used for the legacy project launcher")` — Whether the profile will require an explicit -target=XXX parameter
- L1703 _public prototype_ `virtual TMap<FString,FString>& GetCustomStringProperties() = 0;` — Key-Value pairs for extsibility. Not user-facing.
- L1708 _public prototype_ `virtual TMap<FString, bool>& GetCustomBoolProperties() = 0;` — Key-Value pairs for extsibility. Not user-facing.
- L1713 _public prototype_ `virtual bool SupportsLegacyProjectLauncher() const = 0;` — Whether this profile can be used by the legacy Project Launcher
- L1716 _public prototype_ `virtual ILauncherProfileBuildCookRunPtr GetFirstBuildCookRun() const = 0;` — Get access to the first build cook run command, if any
- L1719 _public prototype_ `virtual ~ILauncherProfile( ) = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLauncherProfile, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLauncherProfile, Log, All);`
- L22 _typedef_ `typedef TSharedPtr<class ILauncherSimpleProfile> ILauncherSimpleProfilePtr;` — Type definition for shared pointers to instances of ILauncherProfile.
- L25 _typedef_ `typedef TSharedRef<class ILauncherSimpleProfile> ILauncherSimpleProfileRef;` — Type definition for shared references to instances of ILauncherProfile.
- L131 _typedef_ `typedef TSharedPtr<class ILauncherProfile> ILauncherProfilePtr;` — Type definition for shared pointers to instances of ILauncherProfile.
- L134 _typedef_ `typedef TSharedRef<class ILauncherProfile> ILauncherProfileRef;` — Type definition for shared references to instances of ILauncherProfile.
- L142 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLauncherProfileDeployedDeviceGroupChanged, const ILauncherDeviceGroupPtr&) DECLARE_MULTICAST_DELEGATE(FOnProfileProjectChanged);` — Delegate type for changing the device group to deploy to. The first parameter is the selected device group (or NULL if the selection was cleared).
- L142 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLauncherProfileDeployedDeviceGroupChanged, const ILauncherDeviceGroupPtr&) DECLARE_MULTICAST_DELEGATE(FOnProfileProjectChanged);` — Delegate type for changing the device group to deploy to. The first parameter is the selected device group (or NULL if the selection was cleared).
- L145 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnProfileProjectChanged);` — Delegate type for a change in project
- L148 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnProfileBuildTargetOptionsChanged);` — Delegate type for a change in build target options
- L148 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnProfileBuildTargetOptionsChanged);` — Delegate type for a change in build target options
- L152 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLauncherProfileUATCommandChanged, const ILauncherProfileUATCommandRef&) DECLARE_DELEGATE_RetVal(bool, FIsCookFinishedDelegate);` — Delegate type for a UAT command
- L152 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLauncherProfileUATCommandChanged, const ILauncherProfileUATCommandRef&) DECLARE_DELEGATE_RetVal(bool, FIsCookFinishedDelegate);` — Delegate type for a UAT command
- L159 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FIsCookFinishedDelegate);` — Delegate type for detecting if cook is finished Used when cooking from the editor.  Specific cook task will wait for the cook to be finished by the editor
- L165 _delegate_ `DECLARE_DELEGATE(FCookCanceledDelegate);` — Delegate type used to callback if the cook has been canceled only used for cook by the book in editor
- L165 _prototype_ `DECLARE_DELEGATE(FCookCanceledDelegate);` — Delegate type used to callback if the cook has been canceled only used for cook by the book in editor

### `Source/Developer/LauncherServices/Public/ILauncherProfileAutomatedTest.h` (Public)


#### class `ILauncherProfileAutomatedTest`  
`class ILauncherProfileAutomatedTest : public ILauncherProfileUATCommand`  
_L13-31_
- inherits: `ILauncherProfileUATCommand`
- desc: Automated test parameters
- L18 _public prototype_ `virtual void SetTests( const TCHAR* Tests ) = 0;` — -Test=xxx,yyy
- L19 _public prototype_ `virtual const FString& GetTests() const = 0;`
- L21 _public prototype_ `virtual bool Load(const FJsonObject& Object) = 0;`
- L22 _public prototype_ `virtual void Save(TJsonWriter<>& Writer) = 0;`
- L25 _public prototype_ `virtual void Serialize( FArchive& Archive ) = 0;` — `UE_DEPRECATED(5.8, "please use the Json Save/Load API")`
- L28 _public function_ `inline void SetPriority( int32 Priority )` — `UE_DEPRECATED(5.8, "Use SetOrder")`
- L30 _public prototype_ `virtual ~ILauncherProfileAutomatedTest() = default;`

#### Free symbols / members of external scopes

- L33 _typedef_ `typedef TSharedPtr<ILauncherProfileAutomatedTest> ILauncherProfileAutomatedTestPtr;`
- L34 _typedef_ `typedef TSharedRef<ILauncherProfileAutomatedTest> ILauncherProfileAutomatedTestRef;`

### `Source/Developer/LauncherServices/Public/ILauncherProfileBuildCookRun.h` (Public)


#### enum `ELauncherProfileBuildModes::Type`  
`enum Type`  
_L19-29_
- desc: Enumerates modes in which the launcher cooks builds.
- L22 _public enumerator_ `Auto` — Build if there is not already an existing pre-built target available.
- L25 _public enumerator_ `Build` — Always build.
- L28 _public enumerator_ `DoNotBuild` — Do not build.

#### enum `ELauncherProfileCookModes::Type`  
`enum Type`  
_L39-55_
- desc: Enumerates modes in which the launcher cooks builds.
- L42 _public enumerator_ `DoNotCook` — Do not cook the build (default).
- L45 _public enumerator_ `ByTheBook` — Pre-cook using user specified settings.
- L48 _public enumerator_ `OnTheFly` — Cook the build on the fly while the game is running.
- L51 _public enumerator_ `ByTheBookInEditor` — Cook by the book in the editor process space
- L54 _public enumerator_ `OnTheFlyInEditor` — Cook on the fly in the editor process space

#### enum `ELauncherProfileCookedMaps::Type`  
`enum Type`  
_L64-75_
- desc: Enumerates selections for maps to cook.
- L67 _public enumerator_ `AllMaps` — Cook all maps.
- L70 _public enumerator_ `NoMaps` — Don't cook any maps. Only startup packages will be cooked.
- L73 _public enumerator_ `SelectedMaps` — Cook user selected maps.

#### enum `ELauncherProfileDeploymentModes::Type`  
`enum Type`  
_L84-97_
- desc: Enumerates deployment modes.
- L87 _public enumerator_ `DoNotDeploy` — Do not deploy the build to any device.
- L90 _public enumerator_ `CopyToDevice` — Copy all required file to the device.
- L93 _public enumerator_ `FileServer` — Let the device get required files from a file server.
- L96 _public enumerator_ `CopyRepository` — Copy a build from a repository to the device.

#### enum `ELauncherProfileLaunchModes::Type`  
`enum Type`  
_L106-116_
- desc: Enumerates launch modes.
- L109 _public enumerator_ `DoNotLaunch` — Do not launch.
- L112 _public enumerator_ `CustomRoles` — Launch with customized roles per device.
- L115 _public enumerator_ `DefaultRole` — Launch with the default role on all deployed devices.

#### enum `ELauncherProfilePackagingModes::Type`  
`enum Type`  
_L125-135_
- desc: Enumerates packaging modes.
- L128 _public enumerator_ `DoNotPackage` — Do not package.
- L131 _public enumerator_ `Locally` — Package and store the build locally.
- L134 _public enumerator_ `SharedRepository` — Package and store the build in a shared repository.

#### enum `ELauncherProfileIncrementalCookMode::Type`  
`enum Type`  
_L144-154_
- desc: Enumerates modes in which the launcher handles incremental cooking
- L147 _public enumerator_ `None` — Do not cook incrementally (default).
- L150 _public enumerator_ `ModifiedOnly` — -iterativecooking : Only recook specifically modified assets without recooking dependencies. This is the legacy method and is must less robust.
- L153 _public enumerator_ `ModifiedAndDependencies` — -cookincremental : Recook modified assets and any dependencies. This is the new method and is currently slower but far more robust.

#### enum `ELauncherProfileValidationErrors::Type`  
`enum Type`  
_L164-266_
- desc: Enumerates profile validation messages.
- L170 _public enumerator_ `CopyToDeviceRequiresCookByTheBook` — Deployment by copying required files to a device requires cooking by the book and is incompatible with cook on the fly.
- L173 _public enumerator_ `CustomRolesNotSupportedYet` — Custom launch roles are not yet supported.
- L176 _public enumerator_ `DeployedDeviceGroupRequired` — A device group must be selected when deploying builds.
- L179 _public enumerator_ `InitialCultureNotAvailable` — The initial culture configured for launch is not part of the selected build.
- L182 _public enumerator_ `InitialMapNotAvailable` — The initial map configured for launch is not part of the selected build.
- L185 _public enumerator_ `MalformedLaunchCommandLine` — The specified launch command line is not formatted correctly.
- L188 _public enumerator_ `NoBuildConfigurationSelected` — A build configuration is required when creating new builds.
- L191 _public enumerator_ `NoCookedCulturesSelected` — When cooking a build, at least one culture must be included.
- L194 _public enumerator_ `NoLaunchRoleDeviceAssigned` — One or more launch roles do not have a device assigned.
- L197 _public enumerator_ `NoPlatformSelected` — At least one platform is required when creating new builds.
- L200 _public enumerator_ `NoProjectSelected` — A game is required when creating new builds.
- L203 _public enumerator_ `NoPackageDirectorySpecified` — The deployment requires a package directory to be specified
- L206 _public enumerator_ `NoPlatformSDKInstalled` — The platform SDK is not installed but is required.
- L209 _public enumerator_ `UnversionedAndIncremental` — The profile has unversioned and incremental specified these are not compatible together
- L212 _public enumerator_ `UnversionedAndIncrimental UE_DEPRECATED(5.6, "Update to use the correctly spelt 'ELauncherProfileValidationErrors::UnversionedAndIncremental' instead") = UnversionedAndIncremental` — Deprecated, do not use
- L215 _public enumerator_ `GeneratingPatchesCanOnlyRunFromByTheBookCookMode` — generating patch requires cook by the book mode
- L218 _public enumerator_ `GeneratingMultiLevelPatchesRequiresGeneratePatch` — generating multilevel patch requires generating patch
- L221 _public enumerator_ `StagingBaseReleasePaksWithoutABaseReleaseVersion` — staging base release pak files requires a base release version to be specified
- L224 _public enumerator_ `GeneratingChunksRequiresCookByTheBook` — Generating Chunks requires cook by the book mode
- L227 _public enumerator_ `GeneratingChunksRequiresUnrealPak` — Generating Chunks requires UnrealPak
- L230 _public enumerator_ `GeneratingHttpChunkDataRequiresGeneratingChunks` — Generating http chunk install data requires generating chunks or DLC
- L233 _public enumerator_ `GeneratingHttpChunkDataRequiresValidDirectoryAndName` — Generating http chunk install data requires valid install directorys and release name
- L236 _public enumerator_ `ShippingDoesntSupportCommandlineOptionsCantUseCookOnTheFly` — Shipping doesn't support commandline options can't use cook on the fly
- L239 _public enumerator_ `CookOnTheFlyDoesntSupportServer` — Cook on the fly doesn't support server target platforms
- L242 _public enumerator_ `NoArchiveDirectorySpecified` — The archive step requires a directory to be specified
- L245 _public enumerator_ `LaunchDeviceIsUnauthorized` — Device is unauthorized or is locked
- L248 _public enumerator_ `IoStoreRequiresPakFiles` — Using I/O store container file(s) requires using UnrealPak
- L251 _public enumerator_ `BuildTargetCookVariantMismatch` — Build Target and Cook Variant mismatch
- L254 _public enumerator_ `BuildTargetIsRequired` — Build Target is required
- L257 _public enumerator_ `FallbackBuildTargetIsRequired` — Fallback Build Target is required
- L260 _public enumerator_ `ZenPakStreamingRequiresDeployAndLaunch` — Zen Pak Streaming requires deployment and launching
- L263 _public enumerator_ `AutomatedTestRequiredBuildCookRun` — Automated Tests currently require at least one active BuildCookRun
- L265 _public enumerator_ `Count`

#### class `ILauncherProfileBuildCookRun`  
`class ILauncherProfileBuildCookRun : public ILauncherProfileUATCommand`  
_L289-1253_
- inherits: `ILauncherProfileUATCommand`
- desc: Interface for BuildCookRun UAT command.
- L303 _public prototype_ `virtual bool IsDeployablePlatform( const FString& PlatformName ) = 0;` — Checks whether devices of the specified platform can be deployed to. Whether a platform is deployable depends on the current profile settings. The right combination of build, cook and package settings must be present. @param PlatformName The name of the platform to deploy. @return true if the platform is deployable, false otherwise.
- L308 _public prototype_ `virtual bool Load(const FJsonObject& Object) = 0;` — Loads the profile from a JSON file
- L313 _public prototype_ `virtual void Save(TJsonWriter<>& Writer) = 0;` — Saves the profile into a JSON file
- L316 _public prototype_ `virtual void SetDefaults( ) = 0;` — Sets all profile settings to their defaults.
- L327 _public prototype_ `virtual const FGuid& GetDeployedDeviceGroupId() const = 0;` — Gets the identifier of the device group to deploy to. This method is used internally by the profile manager to read the device group identifier after loading this profile from a file. The profile manager will use this identifier to locate the actual device group to deploy to. @return The device group identifier, or an invalid GUID if no group was set or deployment is disabled.
- L337 _public prototype_ `virtual EBuildConfiguration GetBuildConfiguration( ) const = 0;` — Gets the name of the build configuration. @return Build configuration name. @see SetBuildConfigurationName
- L344 _public prototype_ `virtual bool HasBuildTargetSpecified() const = 0;` — Checks whether the profile specifies a build target. @return true if the profile specifies a build target.
- L352 _public prototype_ `virtual EBuildConfiguration GetCookConfiguration( ) const = 0;` — Gets the build configuration name of the cooker. @return Cook configuration name. @see SetCookConfigurationName
- L359 _public prototype_ `virtual ELauncherProfileCookModes::Type GetCookMode( ) const = 0;` — Gets the selected cook mode. @return Cook mode.
- L366 _public prototype_ `virtual const FString& GetCookOptions( ) const = 0;` — Gets the cooker command line options. @return Cook options string.
- L369 _public prototype_ `virtual const bool GetSkipCookingEditorContent() const = 0;`
- L377 _public prototype_ `virtual void SetSkipCookingEditorContent(const bool InSkipCookingEditorContent) = 0;` — Skip editor content while cooking, This will strip editor content from final builds @param InSkipCookingEditorContent
- L386 _public prototype_ `virtual const TArray<FString>& GetCookedCultures( ) const = 0;` — Gets the list of cooked culture. @return Collection of culture names. @see AddCookedCulture, ClearCookedCultures, RemoveCookedCulture
- L395 _public prototype_ `virtual const TArray<FString>& GetCookedMaps( ) const = 0;` — Gets the list of cooked maps. @return Collection of map names. @see AddCookedMap, ClearCookedMaps, RemoveCookedMap
- L404 _public prototype_ `virtual const TArray<FString>& GetCookedPlatforms( ) const = 0;` — Gets the names of the platforms to build for. @return Read-only collection of platform names. @see AddCookedPlatform, ClearCookedPlatforms, RemoveCookedPlatform
- L411 _public prototype_ `virtual const ILauncherProfileLaunchRoleRef& GetDefaultLaunchRole( ) const = 0;` — Gets the default launch role. @return A reference to the default launch role.
- L420 _public prototype_ `virtual ILauncherDeviceGroupPtr GetDeployedDeviceGroup( bool bRefreshDevices = true ) = 0;` — Gets the device group to deploy to. @param bRefreshDevices Whether to update the devices in the group before returning, in case some have been discovered since the last call @return The device group, or NULL if none was configured. @see SetDeployedDeviceGroup
- L426 _public prototype_ `virtual const FName GetDefaultDeployPlatform() const = 0;` — Gets the default platforms to deploy if no specific devices were selected.
- L434 _public prototype_ `virtual ELauncherProfileDeploymentModes::Type GetDeploymentMode( ) const = 0;` — Gets the deployment mode. @return The deployment mode. @see SetDeploymentMode
- L442 _public prototype_ `virtual bool GetForceClose() const = 0;` — Gets the close mode for the cook on the fly server @return The close mode. @see SetForceClose
- L450 _public prototype_ `virtual ELauncherProfileLaunchModes::Type GetLaunchMode( ) const = 0;` — Gets the launch mode. @return The launch mode. @see SetLaunchMode
- L458 _public prototype_ `virtual const TArray<ILauncherProfileLaunchRolePtr>& GetLaunchRoles( ) const = 0;` — Gets the profile's collection of launch roles. @return A read-only collection of launch roles. @see CreateLaunchRole, RemoveLaunchRole
- L466 _public prototype_ `virtual const int32 GetLaunchRolesFor( const FString& DeviceId, TArray<ILauncherProfileLaunchRolePtr>& OutRoles ) = 0;` — Gets the launch roles assigned to the specified device. @param DeviceId The identifier of the device. @param OutRoles Will hold the assigned roles, if any.
- L474 _public prototype_ `virtual ELauncherProfilePackagingModes::Type GetPackagingMode( ) const = 0;` — Gets the packaging mode. @return The packaging mode. @see SetPackagingMode
- L482 _public prototype_ `virtual FString GetPackageDirectory( ) const = 0;` — Gets the packaging directory. @return The packaging directory. @see SetPackageDirectory
- L489 _public prototype_ `virtual bool IsArchiving( ) const = 0;` — Whether to archive build @see SetArchive
- L497 _public prototype_ `virtual FString GetArchiveDirectory( ) const = 0;` — Gets the archive directory. @return The archive directory. @see SetArchiveDirectory
- L506 _public prototype_ `virtual FString GetAdditionalCommandLineParameters() const = 0;` — Gets the additional command line parameters that will be used when the app launches. These will be used by all launch roles @return The additional command line parameters @see SetAdditionalCommandLineParameters
- L515 _public prototype_ `virtual FString GetAdditionalTargetCommandLineParameters( EBuildTargetType BuildTargetType ) const = 0;` — Gets the additional command line parameters that will be used for the given target type when the app launches. @param	BuildTargetType	The type of build target to query @return The additional command line parameters @see SetAdditionalTargetCommandLineParameters
- L523 _public prototype_ `virtual uint32 GetTimeout() const = 0;` — Gets the timeout time for the cook on the fly server. @return The timeout time. @see SetTimeout
- L529 _public prototype_ `virtual bool IsGeneratingPatch() const = 0;` — Are we going to generate a patch (Source content patch needs to be specified) @Seealso GetPatchSourceContentPath	 * @Seealso SetPatchSourceContentPath
- L534 _public prototype_ `virtual bool ShouldAddPatchLevel() const = 0;` — Are we going to generate a new patch tier
- L542 _public prototype_ `virtual ELauncherProfileBuildModes::Type GetBuildMode() const = 0;` — Gets the current build mode. @return The current build mode. @see SetBuildMode
- L550 _public prototype_ `virtual bool ShouldBuild() = 0;` — Determines whether the current profile requires building @return The current build mode. @see SetBuildMode
- L558 _public prototype_ `virtual bool IsFastIterate() const = 0;` — Checks if fast iterate is enabled. @return true if fast iterate is enabled, false otherwise. @see SetFastIterate
- L566 _public prototype_ `virtual bool IsCookingIncrementally( ) const = 0;` — Checks whether legacy incremental cooking is enabled. @return true if cooking incrementally, false otherwise. @see SetIncrementalCooking
- L568 _public prototype_ `virtual bool IsIterateSharedCookedBuild() const =0;`
- L576 _public prototype_ `virtual bool IsCompressed( ) const = 0;` — Checks if compression is enabled @return true if compression is enabled @see SetCompressed
- L583 _public prototype_ `virtual bool IsEncryptingIniFiles() const = 0;` — Checks if encrypting ini files is enabled @return true if encrypting ini files is enabled
- L590 _public prototype_ `virtual bool IsForDistribution() const = 0;` — Checks if encrypting ini files is enabled @return true if encrypting ini files is enabled
- L598 _public prototype_ `virtual bool IsCookingUnversioned( ) const = 0;` — Checks whether unversioned cooking is enabled. @return true if cooking unversioned, false otherwise. @see SetUnversionedCooking
- L606 _public prototype_ `virtual bool IsDeployingIncrementally( ) const = 0;` — Checks whether incremental deployment is enabled. @return true if deploying incrementally, false otherwise. @see SetIncrementalDeploying
- L614 _public prototype_ `virtual bool IsFileServerHidden( ) const = 0;` — Checks whether the file server's console window should be hidden. @return true if the file server should be hidden, false otherwise. @see SetHideFileServer
- L622 _public prototype_ `virtual bool IsFileServerStreaming( ) const = 0;` — Checks whether the file server is a streaming file server. @return true if the file server is streaming, false otherwise. @see SetStreamingFileServer
- L630 _public prototype_ `virtual bool IsPackingWithUnrealPak( ) const = 0;` — Checks whether packaging with UnrealPak is enabled. @return true if UnrealPak is used, false otherwise. @see SetPackageWithUnrealPak
- L638 _public prototype_ `virtual bool IsIncludingPrerequisites() const = 0;` — Checks whether to include an installer for prerequisites of packaged games, such as redistributable operating system components, on platforms that support it. @return true if prerequisites are to be included, false otherwise. @see SetIncludePrerequisites
- L645 _public prototype_ `virtual bool IsGeneratingChunks() const = 0;` — Return whether packaging will generate chunk data. @return true if Chunks will be generated, false otherwise.
- L652 _public prototype_ `virtual bool IsGenerateHttpChunkData() const = 0;` — Return whether packaging will use chunk data to generate http chunk install data. @return true if data will be generated, false otherwise.
- L659 _public prototype_ `virtual FString GetHttpChunkDataDirectory() const = 0;` — Where generated http chunk install data will be stored. @return true if data will be generated, false otherwise.
- L666 _public prototype_ `virtual FString GetHttpChunkDataReleaseName() const = 0;` — What name to tag the generated http chunk install data with. @return true if data will be generated, false otherwise.
- L677 _public prototype_ `virtual void AddCookedCulture( const FString& CultureName ) = 0;` — Adds a culture to cook (only used if cooking by the book). @param CultureName The name of the culture to cook. @see ClearCookedCultures, GetCookedCultures, RemoveCookedCulture
- L686 _public prototype_ `virtual void AddCookedMap( const FString& MapName ) = 0;` — Adds a map to cook (only used if cooking by the book). @param MapName The name of the map to cook. @see ClearCookedMaps, GetCookedMaps, RemoveCookedMap
- L695 _public prototype_ `virtual void AddCookedPlatform( const FString& PlatformName ) = 0;` — Adds a platform to cook (only used if cooking by the book). @param PlatformName The name of the platform to add. @see ClearCookedPlatforms, GetCookedPlatforms, RemoveCookedPlatform
- L704 _public prototype_ `virtual void SetDefaultDeployPlatform(const FName PlatformName) = 0;` — Adds a platform to deploy (only used if a specific device is not specified). Will deploy to the default device of the given platform, or the first device if none are marked as 'default'. @param PlatformName The name of the platform to add.
- L711 _public prototype_ `virtual void ClearCookedCultures( ) = 0;` — Removes all cooked cultures. @see AddCookedCulture, GetCookedCulture, RemoveCookedCulture
- L718 _public prototype_ `virtual void ClearCookedMaps( ) = 0;` — Removes all cooked maps. @see AddCookedMap, GetCookedMap, RemoveCookedMap
- L725 _public prototype_ `virtual void ClearCookedPlatforms( ) = 0;` — Removes all cooked platforms. @see AddCookedPlatform, GetCookedPlatforms, RemoveCookedPlatform
- L733 _public prototype_ `virtual ILauncherProfileLaunchRolePtr CreateLaunchRole( ) = 0;` — Creates a new launch role and adds it to the profile. @return The created role. @see GetLaunchRoles, RemoveLaunchRole
- L741 _public prototype_ `virtual void RemoveCookedCulture( const FString& CultureName ) = 0;` — Removes a cooked culture. @param CultureName The name of the culture to remove. @see AddCookedCulture, ClearCookedCultures, GetCookedCultures
- L749 _public prototype_ `virtual void RemoveCookedMap( const FString& MapName ) = 0;` — Removes a cooked map. @param MapName The name of the map to remove. @see AddCookedMap, ClearCookedMaps, GetCookedMaps
- L757 _public prototype_ `virtual void RemoveCookedPlatform( const FString& PlatformName ) = 0;` — Removes a platform from the cook list. @param PlatformName The name of the platform to remove. @see AddBuildPlatform, ClearCookedPlatforms, GetBuildPlatforms
- L765 _public prototype_ `virtual void RemoveLaunchRole( const ILauncherProfileLaunchRoleRef& Role ) = 0;` — Removes the given launch role from the profile. @param Role The role to remove. @see CreateLaunchRole, GetLaunchRoles
- L773 _public prototype_ `virtual void SetBuildMode(ELauncherProfileBuildModes::Type Mode) = 0;` — Sets the current build mode @param Mode Whether the game should be built. @see GetBuildMode
- L781 _public prototype_ `virtual void SetFastIterate(bool Enable) = 0;` — Sets fast iterate. @param Enable fast iterate. @see IsFastIterate
- L789 _public prototype_ `virtual void SetBuildConfiguration( EBuildConfiguration Configuration ) = 0;` — Sets the build configuration. @param ConfigurationName The build configuration name to set. @see GetBuildConfigurationName
- L796 _public prototype_ `virtual void SetBuildTargetSpecified(bool Specified) = 0;` — Sets whether this profile specfies a build target. @param Specified Whether a build target is specified.
- L804 _public prototype_ `virtual void SetCookConfiguration( EBuildConfiguration Configuration ) = 0;` — Sets the build configuration of the cooker. @param Configuration The cooker's build configuration to set. @see GetCookConfiguration
- L812 _public prototype_ `virtual void SetCookMode( ELauncherProfileCookModes::Type Mode ) = 0;` — Sets the cook mode. @param Mode The cook mode. @see GetCookMode
- L820 _public prototype_ `virtual void SetCookOptions(const FString& Options) = 0;` — Sets the cook options. @param Options The cook options. @see GetCookOptions
- L828 _public prototype_ `virtual void SetDeployWithUnrealPak( bool UseUnrealPak ) = 0;` — Sets whether to pack with UnrealPak. @param UseUnrealPak Whether UnrealPak should be used. @see IsPackingWithUnrealPak
- L835 _public prototype_ `virtual void SetGenerateChunks(bool bGenerateChunks) = 0;` — Set whether packaging will generate chunk data. @param true if Chunks should be generated, false otherwise.
- L841 _public prototype_ `virtual void SetGenerateHttpChunkData(bool bGenerateHttpChunkData) = 0;` — Set whether packaging will use chunk data to generate http chunk install data. @param true if data should be generated, false otherwise.
- L847 _public prototype_ `virtual void SetHttpChunkDataDirectory(const FString& InHttpChunkDataDirectory ) = 0;` — Set where generated http chunk install data will be stored. @return the directory path to use.
- L853 _public prototype_ `virtual void SetHttpChunkDataReleaseName(const FString& InHttpChunkDataReleaseName ) = 0;` — Set what name to tag the generated http chunk install data with. @param the name to use.
- L861 _public prototype_ `virtual void SetDeployedDeviceGroup( const ILauncherDeviceGroupPtr& DeviceGroup ) = 0;` — Sets the device group to deploy to. @param DeviceGroup The device group, or NULL to reset this setting. @see GetDeployedDeviceGroup
- L869 _public prototype_ `virtual void SetDeploymentMode( ELauncherProfileDeploymentModes::Type Mode ) = 0;` — Sets the deployment mode. @param Mode The deployment mode to set. @see GetDeploymentMode
- L874 _public prototype_ `virtual bool IsCreatingReleaseVersion() const = 0;` — Creating a release version of the cooked content
- L876 _public prototype_ `virtual void SetCreateReleaseVersion(bool InCreateReleaseVersion) = 0;`
- L878 _public prototype_ `virtual FString GetCreateReleaseVersionName() const = 0;`
- L880 _public prototype_ `virtual void SetCreateReleaseVersionName(const FString& InCreateReleaseVersionName) = 0;`
- L882 _public prototype_ `virtual FString GetBasedOnReleaseVersionName() const = 0;`
- L884 _public prototype_ `virtual void SetBasedOnReleaseVersionName(const FString& InBasedOnReleaseVersion) = 0;`
- L886 _public prototype_ `virtual FString GetOriginalReleaseVersionName() const = 0;`
- L888 _public prototype_ `virtual void SetOriginalReleaseVersionName(const FString& InOriginalReleaseVersion) = 0;`
- L894 _public prototype_ `virtual FString GetReferenceContainerGlobalFileName() const = 0;` — Provides a database of compressed iostore chunks to reuse during the staging process. See IoStoreUtilities.cpp ReferenceContainerGlobalFileName.
- L895 _public prototype_ `virtual void SetReferenceContainerGlobalFileName(const FString& InReferenceContainerGlobalFileName) = 0;`
- L896 _public prototype_ `virtual FString GetReferenceContainerCryptoKeysFileName() const = 0;`
- L897 _public prototype_ `virtual void SetReferenceContainerCryptoKeysFileName(const FString& InReferenceContainerCryptoKeysFileName) = 0;`
- L905 _public prototype_ `virtual void SetGeneratePatch( bool InShouldGeneratePatch ) = 0;` — Sets if we are going to generate a patch @param InShouldGeneratePatch enable generating patch @seealso IsGeneratingPatch
- L906 _public prototype_ `virtual void SetAddPatchLevel( bool InAddPatchLevel) = 0;`
- L908 _public prototype_ `virtual bool IsCreatingDLC() const = 0;`
- L909 _public prototype_ `virtual void SetCreateDLC(bool InBuildDLC) = 0;`
- L911 _public prototype_ `virtual FString GetDLCName() const = 0;`
- L912 _public prototype_ `virtual void SetDLCName(const FString& InDLCName) = 0;`
- L914 _public prototype_ `virtual bool IsDLCIncludingEngineContent() const = 0;`
- L915 _public prototype_ `virtual void SetDLCIncludeEngineContent(bool InDLCIncludeEngineContent) = 0;`
- L924 _public prototype_ `virtual void SetForceClose( bool Close ) = 0;` — Sets the cook on the fly close mode @param Close the close mode to set. @see GetForceClose
- L932 _public prototype_ `virtual void SetHideFileServerWindow( bool Hide ) = 0;` — Sets whether to hide the file server's console window. @param Hide Whether to hide the window. @see GetHideFileServerWindow
- L940 _public prototype_ `virtual void SetIncrementalCooking( bool Incremental ) = 0;` — Sets legacy incremental cooking. @param Incremental Whether cooking should be incremental. @see IsCookingIncrementally
- L943 _public prototype_ `virtual void SetIterateSharedCookedBuild( bool IterateSharedCookedBuild ) = 0;`
- L951 _public prototype_ `virtual void SetCompressed( bool Enable ) = 0;` — Sets Compression. @param Enable compression @see IsCompressed
- L960 _public prototype_ `virtual void SetEncryptingIniFiles(bool Enabled) = 0;` — Set encrypt ini files @param Enable encrypt ini files @see IsEncryptIniFiles
- L968 _public prototype_ `virtual void SetForDistribution(bool Enabled) = 0;` — Set this build is for distribution to the public @param enable for distribution @see IsForDistribution
- L977 _public prototype_ `virtual void SetIncrementalDeploying( bool Incremental ) = 0;` — Sets incremental deploying. @param Incremental Whether deploying should be incremental. @see IsDeployingIncrementally
- L985 _public prototype_ `virtual void SetLaunchMode( ELauncherProfileLaunchModes::Type Mode ) = 0;` — Sets the launch mode. @param Mode The launch mode to set. @see GetLaunchMode
- L993 _public prototype_ `virtual void SetPackagingMode( ELauncherProfilePackagingModes::Type Mode ) = 0;` — Sets the packaging mode. @param Mode The packaging mode to set. @see GetPackagingMode
- L1001 _public prototype_ `virtual void SetPackageDirectory( const FString& Dir ) = 0;` — Sets the packaging directory. @param Dir The packaging directory to set. @see GetPackageDirectory
- L1008 _public prototype_ `virtual void SetArchive( bool bArchive ) = 0;` — Sets whether to archive build @see GetArchiveMode
- L1016 _public prototype_ `virtual void SetArchiveDirectory( const FString& Dir ) = 0;` — Sets the archive directory. @param Dir The archive directory to set. @see GetArchiveDirectory
- L1025 _public prototype_ `virtual void SetAdditionalCommandLineParameters(const FString& Params) = 0;` — Sets the additional command line parameters for the application to use at launch. These will be used by all launch roles @param	Params	The additional command line parameters to use @see GetAdditionalCommandLineParameters
- L1034 _public prototype_ `virtual void SetAdditionalTargetCommandLineParameters(const FString& Params, EBuildTargetType BuildTargetType ) = 0;` — Sets the additional command line parameters that will be used for the given target type when the app launches. @param	Params	The additional command line parameters to use @param	BuildTargetType	The type of build target to modify @see GetAdditionalTargetCommandLineParameters
- L1043 _public prototype_ `virtual void SetStreamingFileServer( bool Streaming ) = 0;` — Sets whether to use a streaming file server. @param Streaming Whether a streaming server should be used. @see GetStreamingFileServer
- L1051 _public prototype_ `virtual void SetIncludePrerequisites(bool InValue) = 0;` — Sets whether to include game prerequisites. @param Value Whether prerequisites should be used. @see IsIncludingPrerequisites
- L1059 _public prototype_ `virtual void SetTimeout(uint32 InTime) = 0;` — Sets the cook on the fly server timeout @param InTime Amount of time to wait before timing out. @see GetTimeout
- L1067 _public prototype_ `virtual void SetUnversionedCooking( bool Unversioned ) = 0;` — Sets unversioned cooking. @param Unversioned Whether cooking is unversioned. @see IsCookingUnversioned
- L1073 _public prototype_ `virtual void SetUseIoStore(bool bUseIoStore) = 0;` — Sets whether to use I/O store for optimized loading. @param bUseIoStore Whether to use I/O store
- L1080 _public prototype_ `virtual bool IsUsingIoStore() const = 0;` — Using I/O store or not. @return true if using I/O store
- L1086 _public prototype_ `virtual void SetUseZenStore(bool bUseZenStore) = 0;` — Sets whether to use the Zen storage server. Note, this property is ignored if the project itself is configured to use Zen store (via UProjectPackagingSettings::bUseZenStore) @param bUseZenStore Whether to use the Zen storage server
- L1093 _public prototype_ `virtual bool IsUsingZenStore() const = 0;` — Using Zen storage server or not. @return true if using Zen storage server
- L1100 _public prototype_ `virtual void SetImportingZenSnapshot( bool Import ) = 0;` — Set whether to import a Zen snapshot before cooking. @param Import Whether to import a Zen snapshot
- L1107 _public prototype_ `virtual bool IsImportingZenSnapshot() const = 0;` — Checks whether a Zen snapshot will be imported before cooking. @return true if importing a Zen snapshot, false otherwise
- L1114 _public prototype_ `virtual bool IsUsingZenStreaming() const = 0;` — Checks whether Zen streaming will be used. @return true if using Zen streaming, false otherwise
- L1121 _public prototype_ `virtual void SetUseZenStreaming( bool UseZenStreaming ) = 0;` — Set whether to use Zen streaming. @param UseZenStreaming Whether use Zen stremaing.
- L1128 _public prototype_ `virtual void SetUseZenPakStreaming( bool UseZenPakStreaming ) = 0;` — Set whether to use Zen pak streaming. @param UseZenPakStreaming Whether use Zen pak streaming.
- L1135 _public prototype_ `virtual bool IsUsingZenPakStreaming() const = 0;` — Checks whether Zen pak streaming will be used. @return true if using Zen pak streaming, false otherwise
- L1143 _public prototype_ `virtual void SetZenPakStreamingPath( const FString& Path ) = 0;` — Sets whether to use Zen pak streaming from the given path. Assumes the path contains a suitable build @param Path Path to the build to use for Zen pak streaming
- L1150 _public prototype_ `virtual FString GetZenPakStreamingPath() const = 0;` — Get the current Zen pak streaming path, if it is being used. @return current Zen pak streaming path, if any
- L1157 _public prototype_ `virtual void SetUsePreStagedBuild( bool UsePreStagedBuild ) = 0;` — Set whether to use a pre-staged build @param UsePreStagedBuild Whether use a pre-staged build
- L1164 _public prototype_ `virtual bool IsUsingPreStagedBuild() const = 0;` — Checks whether a pre-staged build willbe used @return true if using a pre-staged build, false otherwise
- L1170 _public prototype_ `virtual void SetMakeBinaryConfig(bool bMakeBinaryConfig) = 0;` — Sets whether to make a binary config file during packaging @param bMakeBinaryConfig Whether to make a binary config file during staging
- L1176 _public prototype_ `virtual bool MakeBinaryConfig() const = 0;` — Make binary config file during staging or not. @return true to make binary config file
- L1181 _public prototype_ `virtual void SetDeviceIsASimulator(bool bInIsDeviceASimualtor) = 0;` — Sets whether or not the Device is a Simulator
- L1186 _public prototype_ `virtual bool IsDeviceASimulator() const = 0;` — Whether or not the Device is a Simulator
- L1191 _public prototype_ `virtual void SetClientArchitectures( const TArray<FString>& InArchitectures ) = 0;` — Sets the client architecture(s) to build (x64, arm64 etc). Leave empty to use the default
- L1196 _public prototype_ `virtual const TArray<FString>& GetClientArchitectures() const = 0;` — Returns the client architecture(s) that will be build. empty means the default will be used
- L1201 _public prototype_ `virtual void SetServerArchitectures( const TArray<FString>& InArchitectures ) = 0;` — Sets the server architecture(s) to build (x64, arm64 etc). Leave empty to use the default
- L1206 _public prototype_ `virtual const TArray<FString>& GetServerArchitectures() const = 0;` — Returns the server architecture(s) that will be build. empty means the default will be used
- L1211 _public prototype_ `virtual void SetEditorArchitectures( const TArray<FString>& InArchitectures ) = 0;` — Sets the editor architecture(s) to build (x64, arm64 etc). Leave empty to use the default
- L1216 _public prototype_ `virtual const TArray<FString>& GetEditorArchitectures() const = 0;` — Returns the editor architecture(s) that will be build. empty means the default will be used
- L1226 _public prototype_ `virtual TArray<FString> GetBuildTargets() const = 0;` — Gets the names of the build targets @see AddBuildTarget, RemoveBuildTarget, ClearBuildTargets
- L1232 _public prototype_ `virtual void AddBuildTarget( const FString& InBuildTarget ) = 0;` — Add a build target to the list @see GetBuildTargets, RemoveBuildTarget, ClearBuildTargets
- L1238 _public prototype_ `virtual void RemoveBuildTarget( const FString& InBuildTarget ) = 0;` — Remove a build target from the list @see GetBuildTargets, AddBuildTarget, ClearBuildTargets
- L1244 _public prototype_ `virtual void ClearBuildTargets() = 0;` — Clears the list of build targets @see GetBuildTargets, AddBuildTarget, RemoveBuildTarget
- L1252 _public prototype_ `virtual ~ILauncherProfileBuildCookRun( ) = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace ELauncherProfileBuildModes`
- L34 _namespace_ `namespace ELauncherProfileCookModes`
- L59 _namespace_ `namespace ELauncherProfileCookedMaps`
- L79 _namespace_ `namespace ELauncherProfileDeploymentModes`
- L101 _namespace_ `namespace ELauncherProfileLaunchModes`
- L120 _namespace_ `namespace ELauncherProfilePackagingModes`
- L139 _namespace_ `namespace ELauncherProfileIncrementalCookMode`
- L159 _namespace_ `namespace ELauncherProfileValidationErrors`
- L269 _prototype_ `FString LexToStringLocalized(ELauncherProfileValidationErrors::Type Value);`
- L275 _typedef_ `typedef TSharedPtr<class ILauncherProfileBuildCookRun> ILauncherProfileBuildCookRunPtr;` — Type definition for shared pointers to instances of ILauncherProfileBuildCookRun.
- L278 _typedef_ `typedef TSharedRef<class ILauncherProfileBuildCookRun> ILauncherProfileBuildCookRunRef;` — Type definition for shared references to instances of ILauncherProfileBuildCookRun.
- L281 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnProfileCustomValidation);` — Delegate type for gathering custom profile validation
- L281 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnProfileCustomValidation);` — Delegate type for gathering custom profile validation
- L284 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnProfileCustomUATCommandValidation, ILauncherProfileUATCommandRef);` — Delegate type for gathering custom profile validation for a UAT command
- L284 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnProfileCustomUATCommandValidation, ILauncherProfileUATCommandRef);` — Delegate type for gathering custom profile validation for a UAT command

### `Source/Developer/LauncherServices/Public/ILauncherProfileLaunchRole.h` (Public)


#### enum `ELauncherProfileRoleInstanceTypes::Type`  
`enum Type`  
_L16-29_
- desc: Enumerates launch role instance types.
- L19 _public enumerator_ `DedicatedServer` — The instance is a dedicated server.
- L22 _public enumerator_ `ListenServer` — The instance is a listen server.
- L25 _public enumerator_ `StandaloneClient` — The instance is a game client.
- L28 _public enumerator_ `UnrealEditor` — The instance is an Unreal Editor.

#### class `ILauncherProfileLaunchRole`  
`class ILauncherProfileLaunchRole`  
_L71-191_
- desc: Interface for launch roles.
- L80 _public prototype_ `virtual const FString& GetAssignedDevice( ) const = 0;` — Gets the identifier of the device that is assigned to this role. @return The device identifier, or an empty string if the role is unassigned.
- L88 _public prototype_ `virtual const FString& GetUATCommandLine( ) const = 0;` — Gets optional command line parameters to launch with. @return The command line string. @see SetCommandLine
- L96 _public prototype_ `virtual const FString& GetInitialCulture( ) const = 0;` — Gets the initial culture to launch with. @return Culture name. @see SetInitialCulture
- L104 _public prototype_ `virtual const FString& GetInitialMap( ) const = 0;` — Gets the initial map to launch with. @return Map name. @see SetInitialMap
- L111 _public prototype_ `virtual ELauncherProfileRoleInstanceTypes::Type GetInstanceType( ) const = 0;` — Gets the instance type (i.e. client, server, etc). @return Instance type.
- L118 _public prototype_ `virtual const FString& GetName( ) const = 0;` — Gets the name of this role. @return The role name.
- L126 _public prototype_ `virtual bool IsVsyncEnabled( ) const = 0;` — Checks whether vertical sync is enabled. @return true if VSync is enabled, false otherwise. @see SetVsyncEnabled
- L128 _public prototype_ `virtual void Load(const FJsonObject& Object) = 0;`
- L130 _public prototype_ `virtual void Save(TJsonWriter<>& Writer, const TCHAR* Name = TEXT("")) = 0;`
- L138 _public prototype_ `virtual void Serialize( FArchive& Archive ) = 0;` — `UE_DEPRECATED(5.8, "please use the Json Save/Load API")` — Serializes the role from or into the specified archive. @param Archive The archive to serialize from or into.
- L146 _public prototype_ `virtual void SetCommandLine( const FString& NewCommandLine ) = 0;` — Sets optional command line parameters to launch with. @param NewCommandLine Command line string. @see GetUATCommandLine
- L154 _public prototype_ `virtual void SetInitialCulture( const FString& CultureName ) = 0;` — Sets the initial culture to launch with. @param CultureName The culture name. @see GetInitialCulture
- L162 _public prototype_ `virtual void SetInitialMap( const FString& MapName ) = 0;` — Sets the initial map to launch with. @param MapName The name of the map. @see GetInitialMap
- L169 _public prototype_ `virtual void SetInstanceType( ELauncherProfileRoleInstanceTypes::Type InInstanceType ) = 0;` — Sets the role instance type (i.e. client, server, etc). @param InInstanceType The instance type to set.
- L177 _public prototype_ `virtual void SetName( const FString& NewName ) = 0;` — Sets the name of this role. @param NewName The name to set. @see GetName
- L185 _public prototype_ `virtual void SetVsyncEnabled( bool Enabled ) = 0;` — Sets whether vertical sync should be enabled. @param Enabled Whether VSync is enabled. @see IsVsyncEnabled
- L190 _public prototype_ `virtual ~ILauncherProfileLaunchRole( ) = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ELauncherProfileRoleInstanceTypes`
- L38 _function_ `inline FString ToString( ELauncherProfileRoleInstanceTypes::Type InstanceType )` (scope `ELauncherProfileRoleInstanceTypes`) — Returns the string representation of the specified ELauncherProfileRoleInstanceTypes value. @param InstanceType - The value to get the string for. @return A string value.
- L62 _typedef_ `typedef TSharedPtr<class ILauncherProfileLaunchRole> ILauncherProfileLaunchRolePtr;` — Type definition for shared pointers to instances of ILauncherProfileLaunchRole.
- L65 _typedef_ `typedef TSharedRef<class ILauncherProfileLaunchRole> ILauncherProfileLaunchRoleRef;` — Type definition for shared references to instances of ILauncherProfileLaunchRole.

### `Source/Developer/LauncherServices/Public/ILauncherProfileManager.h` (Public)


#### struct `FUATCommandPostProcessParameters`  
`struct FUATCommandPostProcessParameters`  
_L19-29_
- desc: Parameters for customizing a UAT command via a callback
- L21 _public member_ `bool bShouldBeSkipped;`
- L23 _public member_ `const ILauncherProfileRef Profile;`
- L24 _public member_ `const ILauncherProfileUATCommandRef UATCommand;`
- L25 _public member_ `FString& UATCommandLine;`
- L27 _public member_ `TArray<FCommandDesc>& Commands;`
- L28 _public member_ `FString& CommandStart;`

#### class `ILauncherProfileWizard`  
`class ILauncherProfileWizard`  
_L96-119_
- desc: Interface for a factory to create pre-defined launcher profiles.
- L102 _public prototype_ `virtual FText GetName() const = 0;` — Wizard name that will be used for menu
- L107 _public prototype_ `virtual FText GetDescription() const = 0;` — Wizard description text that will be used for menu tooltip
- L114 _public prototype_ `virtual void HandleCreateLauncherProfile(const ILauncherProfileManagerRef& ProfileManager) = 0;` — Handle request to create launcher profile using this wizard @param ProfileManager The profile manager initiated this request.
- L118 _public prototype_ `virtual ~ILauncherProfileWizard( ) = default;` — Virtual destructor.

#### class `ILauncherProfileManager`  
`class ILauncherProfileManager`  
_L124-465_
- desc: Interface for launcher profile managers.
- L133 _public prototype_ `virtual void AddDeviceGroup( const ILauncherDeviceGroupRef& DeviceGroup ) = 0;` — Adds the given device group. @param DeviceGroup The group to add.
- L140 _public prototype_ `virtual ILauncherDeviceGroupRef AddNewDeviceGroup( ) = 0;` — Create a new device group and maintains a reference for its future usage. @return The device group created.
- L147 _public prototype_ `virtual ILauncherDeviceGroupRef CreateUnmanagedDeviceGroup() = 0;` — Creates a new device group but does not add it to the internal tracking. @return The new device group created.
- L154 _public prototype_ `virtual const TArray<ILauncherDeviceGroupPtr>& GetAllDeviceGroups( ) const = 0;` — Gets the collection of device groups. @return A read-only collection of device groups.
- L162 _public prototype_ `virtual ILauncherDeviceGroupPtr GetDeviceGroup( const FGuid& GroupId ) const = 0;` — Gets the device group with the specified identifier. @param GroupId The unique identifier of the group to get. @return A shared pointer to the group, or nullptr if the group was not found.
- L169 _public prototype_ `virtual void RemoveDeviceGroup( const ILauncherDeviceGroupRef& DeviceGroup ) = 0;` — Deletes the specified device group. @param DeviceGroup The group to remove.
- L172 _public prototype_ `virtual void SaveDeviceGroups( bool bTrimUnused = false ) = 0;` — Saves all the device groups to a config file
- L182 _public prototype_ `virtual ILauncherSimpleProfilePtr FindOrAddSimpleProfile(const FString& DeviceName) = 0;` — Finds or Adds then returns a simple profile for the specified Device @param DeviceName The name of the device we want the simple profile for. @return The simple profile for the specified device.
- L190 _public prototype_ `virtual ILauncherSimpleProfilePtr FindSimpleProfile(const FString& DeviceName) = 0;` — Gets the simple profile for the specified device. @param DeviceName The name of the device we want the simple profile for. @return The simple profile for the specified device, or nullptr if the simple profile doesn't exist.
- L197 _public prototype_ `virtual void RemoveSimpleProfile(const ILauncherSimpleProfileRef& SimpleProfile) = 0;` — Deletes the given simple profile. @param Profile The simple profile to delete.
- L206 _public prototype_ `virtual ILauncherProfileRef AddNewProfile( ) = 0;` — Creates a new profile. @return The new profile created.
- L214 _public prototype_ `virtual ILauncherProfileRef CreateUnsavedProfile(FString ProfileName) = 0;` — Creates a new profile but does not add it to the internal tracking. @param ProfileName The name of the profile to create. @return The new profile created.
- L224 _public prototype_ `virtual void AddProfile( const ILauncherProfileRef& Profile ) = 0;` — Adds the given profile to the list of managed profiles. If a profile with the same identifier already exists in the profile collection, it will be deleted before the given profile is added. @param Profile The profile to add.
- L233 _public prototype_ `virtual ILauncherProfilePtr FindProfile( const FString& ProfileName ) = 0;` — Gets the profile with the specified name. @param ProfileName The name of the profile to get. @return The profile, or nullptr if the profile doesn't exist. @see GetProfile
- L242 _public prototype_ `virtual const TArray<ILauncherProfilePtr>& GetAllProfiles( ) const = 0;` — Gets the collection of profiles. @return A read-only collection of profiles. @see GetSelectedProfile
- L251 _public prototype_ `virtual ILauncherProfilePtr GetProfile( const FGuid& ProfileId ) const = 0;` — Gets the profile with the specified identifier. @param ProfileId The identifier of the profile to get. @return The profile, or nullptr if the profile doesn't exist. @see FindProfile
- L264 _public prototype_ `virtual ILauncherProfilePtr LoadProfile( FArchive& Archive ) = 0;` — `UE_DEPRECATED(5.8, "Please use LoadJSONProfile")` — Attempts to load a profile from the specified archive. The loaded profile is NOT automatically added to the profile manager. Use AddProfile() to add it to the collection. @param Archive The archive to load from. @return The loaded profile, or nullptr if loading failed. @see AddProfile, SaveProfile
- L276 _public prototype_ `virtual ILauncherProfilePtr LoadJSONProfile(FString ProfileFile) = 0;` — Attempts to load a profile from the specified file. The loaded profile is NOT automatically added to the profile manager. Use AddProfile() to add it to the collection. @param ProfileFile The file to load from. @return The loaded profile, or nullptr if loading failed. @see AddProfile, SaveProfile
- L282 _public prototype_ `virtual void RemoveProfile( const ILauncherProfileRef& Profile ) = 0;` — Deletes the given profile. @param Profile The profile to delete.
- L292 _public prototype_ `virtual bool SaveProfile(const ILauncherProfileRef& Profile) = 0;` — `UE_DEPRECATED(5.8, "Please use SaveJSONProfile")` — Saves the given profile to the specified archive. @param Profile The profile to save. @param Archive The archive to save to. @see LoadProfile
- L300 _public prototype_ `virtual bool SaveJSONProfile(const ILauncherProfileRef& Profile) = 0;` — Saves the given profile to the specified file. @param Profile The profile to save. @see LoadJSONProfile
- L307 _public prototype_ `virtual void ChangeProfileName(const ILauncherProfileRef& Profile, FString Name) = 0;` — Modifies profile name. Saves file to new location and deletes old one to avoid duplicating profiles. @param Profile The profile to change
- L314 _public prototype_ `virtual void RegisterProfileWizard(const ILauncherProfileWizardPtr& ProfileWizard) = 0;` — Register wizard that can be used to create pre-defined launcher profiles @param ProfileWizard The wizard to register
- L321 _public prototype_ `virtual void UnregisterProfileWizard(const ILauncherProfileWizardPtr& ProfileWizard) = 0;` — Unregister launcher profile wizard @param ProfileWizard The wizard to unregister
- L326 _public prototype_ `virtual const TArray<ILauncherProfileWizardPtr>& GetProfileWizards() const = 0;` — Return list of all registered profile wizards
- L332 _public prototype_ `virtual FString MakeBuildCookRunParamsForProjectCustomBuild(const ILauncherProfileRef& InProfile, const TArray<FString>& InPlatforms) const = 0;` — Returns best-guess BuildCookRun parameters for the given profile in the format expected by FProjectBuidSettings::BuildCookRunParams Used by the Project custom Build's "import from Project Launcher" menu
- L345 _public prototype_ `virtual void LoadSettings( ) = 0;` — Loads all device groups and launcher profiles from disk. When this function is called, it will discard any in-memory changes to device groups and launcher profiles that are not yet persisted to disk. Settings are also loaded automatically when a profile manager is first created. @see SaveSettings
- L352 _public prototype_ `virtual void SaveSettings( ) = 0;` — Persists all device groups, launcher profiles and other settings to disk.\ @see LoadSettings
- L359 _public prototype_ `virtual FString GetProjectName() const = 0;` — Gets the name of the Unreal project to use.
- L364 _public prototype_ `virtual FString GetProjectBasePath() const = 0;` — Gets the base project path for the project
- L372 _public prototype_ `virtual FString GetProjectPath() const = 0;` — Gets the full path to the Unreal project to use. @return The path. @see SetProjectPath
- L380 _public prototype_ `virtual void SetProjectPath(const FString& InProjectPath) = 0;` — Sets the path to the Unreal project to use. @param Path The full path to the project. @see GetProjectPath
- L387 _public prototype_ `virtual FString GetBuildTarget() const = 0;` — Gets the default build target to use.
- L392 _public prototype_ `virtual void SetBuildTarget( const FString& InBuildTarget ) = 0;` — Sets the default buid target to use.
- L399 _public prototype_ `virtual const TArray<FString> GetAllExplicitBuildTargetNames() const = 0;` — `UE_DEPRECATED(5.8, "this was only used for the legacy project launcher")` — Return a list of all build build targets for the current project that need to be specified explicitly via -target= If a build target isn't in the list, it does not need to be specified (and BuildTarget can be an empty string)
- L408 _public prototype_ `virtual FOnLauncherProfileManagerDeviceGroupAdded& OnDeviceGroupAdded( ) = 0;` — Returns a delegate that is invoked when a device group was added. @return The delegate.
- L415 _public prototype_ `virtual FOnLauncherProfileManagerDeviceGroupRemoved& OnDeviceGroupRemoved( ) = 0;` — Returns a delegate that is invoked when a device group was removed. @return The delegate.
- L422 _public prototype_ `virtual FOnLauncherProfileManagerProfileAdded& OnProfileAdded( ) = 0;` — Returns a delegate that is invoked when a profile was added. @return The delegate.
- L429 _public prototype_ `virtual FOnLauncherProfileManagerProfileRemoved& OnProfileRemoved( ) = 0;` — Returns a delegate that is invoked when a profile was removed. @return The delegate.
- L437 _public prototype_ `virtual FOnLauncherProfileManagerProjectChanged& OnProjectChanged( ) = 0;` — Returns a delegate that is invoked when the project is changed. @return The delegate.
- L445 _public prototype_ `virtual FOnLauncherProfilePostProcessCommandLine& OnPostProcessLaunchCommandLine( ) = 0;` — Returns a delegate that is invoked to post-process the command line before a profile launched @return The delegate.
- L452 _public prototype_ `virtual FOnLauncherProfilePostProcessAutomatedTestCommandLine& OnPostProcessAutomatedTestCommandLine( ) = 0;` — Returns a delegate that is invoked to post-process the command line before an automated test is launched @return The delegate.
- L459 _public prototype_ `virtual FOnLauncherProfilePostProcessUATCommandLine& OnPostProcessUATCommandLine( ) = 0;` — Returns a delegate that is invoked to post-process the command line before a UAT command is launched @return The delegate.
- L464 _public prototype_ `virtual ~ILauncherProfileManager( ) = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L13 _typedef_ `typedef TSharedPtr<class ILauncherProfileManager> ILauncherProfileManagerPtr;` — Type definition for shared pointers to instances of ILauncherProfileManager.
- L16 _typedef_ `typedef TSharedRef<class ILauncherProfileManager> ILauncherProfileManagerRef;` — Type definition for shared references to instances of ILauncherProfileManager.
- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLauncherProfileManagerDeviceGroupAdded, const ILauncherDeviceGroupRef&);` — Declares a delegate to be invoked when a device group was added to a profile manager. The first parameter is the profile that was added.
- L37 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLauncherProfileManagerDeviceGroupAdded, const ILauncherDeviceGroupRef&);` — Declares a delegate to be invoked when a device group was added to a profile manager. The first parameter is the profile that was added.
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLauncherProfileManagerDeviceGroupRemoved, const ILauncherDeviceGroupRef&);` — Declares a delegate to be invoked when a device group was removed from a profile manager. The first parameter is the profile that was removed.
- L44 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLauncherProfileManagerDeviceGroupRemoved, const ILauncherDeviceGroupRef&);` — Declares a delegate to be invoked when a device group was removed from a profile manager. The first parameter is the profile that was removed.
- L51 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLauncherProfileManagerProfileAdded, const ILauncherProfileRef&);` — Declares a delegate to be invoked when a launcher profile was added to a profile manager. The first parameter is the profile that was added.
- L51 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLauncherProfileManagerProfileAdded, const ILauncherProfileRef&);` — Declares a delegate to be invoked when a launcher profile was added to a profile manager. The first parameter is the profile that was added.
- L58 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLauncherProfileManagerProfileRemoved, const ILauncherProfileRef&);` — Declares a delegate to be invoked when a launcher profile was removed from a profile manager. The first parameter is the profile that was removed.
- L58 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLauncherProfileManagerProfileRemoved, const ILauncherProfileRef&);` — Declares a delegate to be invoked when a launcher profile was removed from a profile manager. The first parameter is the profile that was removed.
- L65 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnLauncherProfileManagerProjectChanged);` — Declares a delegate to be invoked when the project is changed.
- L65 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnLauncherProfileManagerProjectChanged);` — Declares a delegate to be invoked when the project is changed.
- L72 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLauncherProfilePostProcessCommandLine, const ILauncherProfileRef&, EBuildTargetType, FString& );` — Declares a delegate to be invoked to post-process a command line before launching The first parameter is the profile that is being launched, the second parameter is the build target type (or 'unknown' for global arguments), and the third parameter is the command line to modify.
- L72 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLauncherProfilePostProcessCommandLine, const ILauncherProfileRef&, EBuildTargetType, FString& );` — Declares a delegate to be invoked to post-process a command line before launching The first parameter is the profile that is being launched, the second parameter is the build target type (or 'unknown' for global arguments), and the third parameter is the command line to modify.
- L79 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLauncherProfilePostProcessAutomatedTestCommandLine, const ILauncherProfileAutomatedTestRef&, const ILauncherProfileRef&, FString& );` — Declares a delegate to be invoked to post-process a command line before launching and automated test The first parameter is the automated test, the second is the profile that is being launched, the third parameter is the command line to modify.
- L79 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLauncherProfilePostProcessAutomatedTestCommandLine, const ILauncherProfileAutomatedTestRef&, const ILauncherProfileRef&, FString& );` — Declares a delegate to be invoked to post-process a command line before launching and automated test The first parameter is the automated test, the second is the profile that is being launched, the third parameter is the command line to modify.
- L84 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLauncherProfilePostProcessUATCommandLine, FUATCommandPostProcessParameters& );` — Declares a delegate to be invoked to post-process a command line before launching a UAT command
- L84 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLauncherProfilePostProcessUATCommandLine, FUATCommandPostProcessParameters& );` — Declares a delegate to be invoked to post-process a command line before launching a UAT command
- L88 _typedef_ `typedef TSharedPtr<class ILauncherProfileWizard> ILauncherProfileWizardPtr;` — Type definition for shared references to instances of ILauncherProfile.
- L91 _typedef_ `typedef TSharedRef<class ILauncherProfileWizard> ILauncherProfileWizardRef;` — Type definition for shared references to instances of ILauncherProfile.

### `Source/Developer/LauncherServices/Public/ILauncherProfileUATCommand.h` (Public)


#### class `ILauncherProfileUATCommand`  
`class ILauncherProfileUATCommand`  
_L15-48_
- desc: UAT command parameters
- L20 _public prototype_ `virtual void SetUATCommand( const TCHAR* UATCommand ) = 0;`
- L21 _public prototype_ `virtual const FString& GetUATCommand() const = 0;`
- L23 _public prototype_ `virtual void SetAdditionalUATCommandLine( const TCHAR* AdditionalCommandLine ) = 0;`
- L24 _public prototype_ `virtual const FString& GetAdditionalUATCommandLine() const = 0;`
- L26 _public prototype_ `virtual void SetEnabled( bool bEnabled ) = 0;`
- L27 _public prototype_ `virtual bool IsEnabled() const = 0;`
- L29 _public prototype_ `virtual void SetOrder( int32 Order ) = 0;` — negative order items will run before the main BuildCookRun, positive order items will run afterwards
- L30 _public prototype_ `virtual int32 GetOrder() const = 0;`
- L33 _public prototype_ `virtual const TCHAR* GetInternalName() const = 0;` — recommendation for InternalName is is "ExtensionName.InternalName"
- L35 _public prototype_ `virtual void SetDescription(const FString& NewDescription) = 0;`
- L36 _public prototype_ `virtual FString GetDescription() const = 0;`
- L38 _public prototype_ `virtual void SetUserTypeName(const FString& NewUserTypeName) = 0;`
- L39 _public prototype_ `virtual FString GetUserTypeName() const = 0;`
- L41 _public prototype_ `virtual bool Load(const FJsonObject& Object) = 0;`
- L42 _public prototype_ `virtual void Save(TJsonWriter<>& Writer) = 0;`
- L44 _public prototype_ `virtual TSharedPtr<ILauncherProfileAutomatedTest> AsAutomatedTest() = 0;`
- L45 _public prototype_ `virtual TSharedPtr<ILauncherProfileBuildCookRun> AsBuildCookRun() = 0;`
- L47 _public prototype_ `virtual ~ILauncherProfileUATCommand() = default;`

#### Free symbols / members of external scopes

- L50 _typedef_ `typedef TSharedPtr<ILauncherProfileUATCommand> ILauncherProfileUATCommandPtr;`
- L51 _typedef_ `typedef TSharedRef<ILauncherProfileUATCommand> ILauncherProfileUATCommandRef;`

### `Source/Developer/LauncherServices/Public/ILauncherServicesModule.h` (Public)


#### class `ILauncherServicesModule`  
`class ILauncherServicesModule : public IModuleInterface`  
_L23-87_
- inherits: `IModuleInterface`
- desc: Interface for launcher tools modules.
- L33 _public prototype_ `virtual ILauncherDeviceGroupRef CreateDeviceGroup( ) = 0;` — Creates a new device group. @return A new device group.
- L40 _public prototype_ `virtual ILauncherDeviceGroupRef CreateDeviceGroup(const FGuid& Guid, const FString& Name ) = 0;` — Creates a new device group. @return A new device group.
- L47 _public prototype_ `virtual ILauncherRef CreateLauncher( ) = 0;` — Creates a game launcher. @return A new game launcher.
- L54 _public prototype_ `virtual ILauncherProfileRef CreateProfile( const FString& ProfileName ) = 0;` — Creates a launcher profile. @param ProfileName - The name of the profile to create.
- L61 _public prototype_ `virtual ILauncherProfileManagerRef GetProfileManager( ) = 0;` — Gets the launcher profile manager. @return The launcher profile manager.
- L66 _public prototype_ `DECLARE_EVENT_TwoParams(ILauncherServicesModule, FLauncherServicesSDKNotInstalled, const FString&, const FString&);` — Delegate for when a platform SDK isn't installed corrected (takes the platform name and the documentation link to show)
- L67 _public prototype_ `virtual FLauncherServicesSDKNotInstalled& OnLauncherServicesSDKNotInstalled( ) = 0;`
- L68 _public prototype_ `virtual void BroadcastLauncherServicesSDKNotInstalled(const FString& PlatformName, const FString& DocLink) = 0;`
- L73 _public prototype_ `virtual FString GetExecutableForCommandlets() const = 0;` — Determines the executable that should be used for executing commandlets
- L78 _public prototype_ `virtual ~ILauncherServicesModule( ) = default;` — Virtual destructor.
- L84 _public member_ `static FOnLauncherProfileManagerInitialized ProfileManagerInitializedDelegate;` — Delegate that is invoked when a profile manager is initialized.
- L86 _public member_ `FOnCreateLauncher OnCreateLauncherDelegate;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLauncherProfileManagerInitialized, ILauncherProfileManager&);` — Declares a delegate to be invoked when a launcher profile manager has been initialized. The first parameter is the profile manager.
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLauncherProfileManagerInitialized, ILauncherProfileManager&);` — Declares a delegate to be invoked when a launcher profile manager has been initialized. The first parameter is the profile manager.
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateLauncher, ILauncherRef);`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateLauncher, ILauncherRef);`
- L66 _delegate_ `DECLARE_EVENT_TwoParams(ILauncherServicesModule, FLauncherServicesSDKNotInstalled, const FString&, const FString&);` — Delegate for when a platform SDK isn't installed corrected (takes the platform name and the documentation link to show)

### `Source/Developer/LauncherServices/Public/ILauncherTask.h` (Public)


#### enum `ELauncherTaskStatus::Type`  
`enum Type`  
_L14-30_
- desc: Enumerates launcher task status types.
- L17 _public enumerator_ `Busy` — The task is currently busy executing.
- L20 _public enumerator_ `Canceled` — The task has been canceled.
- L23 _public enumerator_ `Completed` — The task completed successfully.
- L26 _public enumerator_ `Failed` — The task failed.
- L29 _public enumerator_ `Pending` — The task is waiting to execute.

#### class `ILauncherTask`  
`class ILauncherTask`  
_L50-139_
- desc: Interface for launcher worker tasks.
- L57 _public prototype_ `virtual void Cancel( ) = 0;` — Cancels the task.
- L64 _public prototype_ `virtual FTimespan GetDuration( ) const = 0;` — Gets the duration of time that the task has been running. @return Time duration.
- L71 _public prototype_ `virtual const FString& GetName( ) const = 0;` — Gets the task's name. @return Task name.
- L78 _public prototype_ `virtual const FString& GetDesc( ) const = 0;` — Gets the task's name. @return Task name.
- L85 _public prototype_ `virtual ELauncherTaskStatus::Type GetStatus( ) const = 0;` — Gets the task's current status. @return Task status.
- L92 _public prototype_ `virtual bool IsCancelling() const = 0;` — Gets if the task is trying to cancel @return if task is trying to cancel
- L102 _public prototype_ `virtual bool IsFinished( ) const = 0;` — Checks whether the task has finished execution. A task is finished when it is neither pending, nor busy. @return true if the task finished, false otherwise.
- L110 _public prototype_ `virtual int32 ReturnCode() const = 0;` — retrieves the return code from the task @return return code from the task
- L117 _public prototype_ `virtual FOnTaskStartedDelegate& OnStarted() = 0;` — Gets the stage completed delegate @return the delegate
- L124 _public prototype_ `virtual FOnTaskCompletedDelegate& OnCompleted() = 0;` — Gets the completed delegate @return the delegate
- L131 _public prototype_ `virtual uint32 GetErrorCount() const = 0;` — Gets the amount of errors that were generated during this task @return the amount
- L138 _public prototype_ `virtual uint32 GetWarningCount() const = 0;` — Gets the amount of warnings that were generated during this task @return the amount

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ELauncherTaskStatus`
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTaskStartedDelegate, const FString&);`
- L34 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTaskStartedDelegate, const FString&);`
- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTaskCompletedDelegate, const FString&);` — Delegate used to notify when a stage ends
- L37 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTaskCompletedDelegate, const FString&);` — Delegate used to notify when a stage ends
- L41 _typedef_ `typedef TSharedPtr<class ILauncherTask> ILauncherTaskPtr;` — Type definition for shared pointers to instances of ILauncherTask.
- L44 _typedef_ `typedef TSharedRef<class ILauncherTask> ILauncherTaskRef;` — Type definition for shared references to instances of ILauncherTask.

### `Source/Developer/LauncherServices/Public/ILauncherWorker.h` (Public)


#### enum `ELauncherWorkerStatus::Type`  
`enum Type`  
_L13-22_
- L15 _public enumerator_ `Busy`
- L17 _public enumerator_ `Canceling`
- L19 _public enumerator_ `Canceled`
- L21 _public enumerator_ `Completed`

#### struct `FCommandDesc`  
`struct FCommandDesc`  
_L49-54_
- desc: For task list customization
- L51 _public member_ `FString Name;`
- L52 _public member_ `FString Desc;`
- L53 _public member_ `FString EndText;`

#### class `ILauncherWorker`  
`class ILauncherWorker`  
_L60-141_
- desc: Interface for launcher worker threads.
- L67 _public prototype_ `virtual void Cancel( ) = 0;` — Cancels the operation.
- L72 _public prototype_ `virtual void CancelAndWait( ) = 0;` — Cancels the operation and waits for the thread to finish any remaining work.
- L79 _public prototype_ `virtual ELauncherWorkerStatus::Type GetStatus( ) const = 0;` — Gets the worker's status. @return Worker status.
- L88 _public prototype_ `virtual int32 GetTasks( TArray<ILauncherTaskPtr>& OutTasks ) const = 0;` — Gets the worker's list of tasks. @param OutTasks - Will hold the task list. @return The number of tasks returned.
- L95 _public prototype_ `virtual FOutputMessageReceivedDelegate& OnOutputReceived() = 0;` — Gets the output message delegate @return the delegate
- L102 _public prototype_ `virtual FOnStageStartedDelegate& OnStageStarted() = 0;` — Gets the stage started delegate @return the delegate
- L109 _public prototype_ `virtual FOnStageCompletedDelegate& OnStageCompleted() = 0;` — Gets the stage completed delegate @return the delegate
- L116 _public prototype_ `virtual FOnLaunchCompletedDelegate& OnCompleted() = 0;` — Gets the completed delegate @return the delegate
- L123 _public prototype_ `virtual FOnLaunchCanceledDelegate& OnCanceled() = 0;` — Gets the canceled delegate @return the delegate
- L130 _public prototype_ `virtual ILauncherProfilePtr GetLauncherProfile() const = 0;` — Get the launcher profile @return the variable
- L135 _public function_ `virtual void AddDevicePackagePair(const FString& Device, const FString& Package)` — Set the app id running on the device
- L140 _protected prototype_ `virtual ~ILauncherWorker( ) = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ELauncherWorkerStatus`
- L27 _typedef_ `typedef TSharedPtr<class ILauncherWorker> ILauncherWorkerPtr;` — Type definition for shared pointers to instances of ILauncherWorker.
- L30 _typedef_ `typedef TSharedRef<class ILauncherWorker> ILauncherWorkerRef;` — Type definition for shared references to instances of ILauncherWorker.
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOutputMessageReceivedDelegate, const FString&);` — Delegate used to notify of an output message
- L34 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOutputMessageReceivedDelegate, const FString&);` — Delegate used to notify of an output message
- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageStartedDelegate, const FString&);` — Delegate used to notify when a stage starts
- L37 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageStartedDelegate, const FString&);` — Delegate used to notify when a stage starts
- L40 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStageCompletedDelegate, const FString&, double);` — Delegate used to notify when a stage ends
- L40 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStageCompletedDelegate, const FString&, double);` — Delegate used to notify when a stage ends
- L43 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLaunchCompletedDelegate, bool, double, int32);` — Delegate used to notify when the launch is complete
- L43 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLaunchCompletedDelegate, bool, double, int32);` — Delegate used to notify when the launch is complete
- L46 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLaunchCanceledDelegate, double);` — Delegate used to notify when the launch was canceled
- L46 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLaunchCanceledDelegate, double);` — Delegate used to notify when the launch was canceled
