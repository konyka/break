# Plugins / LiveLinkXR

- module root: `Plugins/VirtualProduction/LiveLinkXR/Source/LiveLinkXR`
- headers: 6; symbols: 67
- symbol kinds: class=5, delegate=2, function=8, member=26, prototype=25, struct=1
- PrivateDependencyModuleNames: CoreUObject, Engine, HeadMountedDisplay, LiveLinkXROpenXRExt, OpenXRHMD, Slate, SlateCore
- PublicDependencyModuleNames: Core, LiveLinkInterface

### `Plugins/VirtualProduction/LiveLinkXR/Source/LiveLinkXR/Private/SLiveLinkXRSourceFactory.h` (Private)


#### class `SLiveLinkXRSourceFactory`  
`class SLiveLinkXRSourceFactory : public SCompoundWidget`  
_L19-39_
- inherits: `SCompoundWidget`
- L21 _private function_ `SLATE_BEGIN_ARGS(SLiveLinkXRSourceFactory)`
- L23 _private prototype_ `SLATE_EVENT(FOnLiveLinkXRConnectionSettingsAccepted, OnConnectionSettingsAccepted) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L30 _private member_ `FLiveLinkXRConnectionSettings ConnectionSettings;`
- L33 _private member_ `TSharedPtr<FStructOnScope> StructOnScope;`
- L34 _private member_ `TSharedPtr<IStructureDetailsView> StructureDetailsView;`
- L37 _private prototype_ `FReply OnSettingsAccepted();`
- L38 _private member_ `FOnLiveLinkXRConnectionSettingsAccepted OnConnectionSettingsAccepted;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLiveLinkXRConnectionSettingsAccepted, FLiveLinkXRConnectionSettings);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLiveLinkXRConnectionSettingsAccepted, FLiveLinkXRConnectionSettings);`

### `Plugins/VirtualProduction/LiveLinkXR/Source/LiveLinkXR/Public/LiveLinkXR.h` (Public)


#### class `FLiveLinkXRModule`  
`class FLiveLinkXRModule : public IModuleInterface`  
_L10-22_
- inherits: `IModuleInterface`
- L14 _public function_ `static FLiveLinkXRModule& Get()`
- L20 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L21 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkXR, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkXR, Log, All);`

### `Plugins/VirtualProduction/LiveLinkXR/Source/LiveLinkXR/Public/LiveLinkXRConnectionSettings.h` (Public)


#### struct `FLiveLinkXRConnectionSettings`  
`struct FLiveLinkXRConnectionSettings`  
_L9-29_
- reflection: `USTRUCT()`
- L16 _public member_ `bool bTrackTrackers = true;` — `UPROPERTY(EditAnywhere, Category = "Connection Settings")` — Track all tracker pucks
- L20 _public member_ `bool bTrackControllers = false;` — `UPROPERTY(EditAnywhere, Category = "Connection Settings")` — Track all controllers
- L24 _public member_ `bool bTrackHMDs = false;` — `UPROPERTY(EditAnywhere, Category = "Connection Settings")` — Track all HMDs
- L28 _public member_ `uint32 LocalUpdateRateInHz = 60;` — `UPROPERTY(EditAnywhere, Category = "Connection Settings", meta = (ClampMin = 1, ClampMax = 1000))` — Update rate (in Hz) at which to read the tracking data for each device

### `Plugins/VirtualProduction/LiveLinkXR/Source/LiveLinkXR/Public/LiveLinkXRSource.h` (Public)


#### class `FLiveLinkXRSource`  
`class FLiveLinkXRSource : public ILiveLinkSource , public FRunnable , public TSharedFromThis<FLiveLinkXRSource>`  
_L17-106_
- inherits: `ILiveLinkSource,FRunnable,TSharedFromThis<FLiveLinkXRSource>`
- L23 _public prototype_ `FLiveLinkXRSource(const FLiveLinkXRConnectionSettings& InConnectionSettings);`
- L25 _public prototype_ `virtual ~FLiveLinkXRSource();`
- L29 _public prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;`
- L30 _public prototype_ `virtual void InitializeSettings(ULiveLinkSourceSettings* Settings) override;`
- L31 _public prototype_ `virtual void Update() override;`
- L33 _public prototype_ `virtual bool IsSourceStillValid() const override;`
- L35 _public prototype_ `virtual bool RequestSourceShutdown() override;`
- L37 _public function_ `virtual FText GetSourceType() const override`
- L38 _public function_ `virtual FText GetSourceMachineName() const override`
- L39 _public function_ `virtual FText GetSourceStatus() const override`
- L41 _public prototype_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const override;`
- L47 _public function_ `virtual bool Init() override`
- L48 _public prototype_ `virtual uint32 Run() override;`
- L49 _public prototype_ `void Start();`
- L50 _public prototype_ `virtual void Stop() override;`
- L51 _public function_ `virtual void Exit() override`
- L55 _public prototype_ `void Send(FLiveLinkFrameDataStruct* FrameDataToSend, FName SubjectName);`
- L58 _public prototype_ `const FString GetDeviceTypeName(EXRTrackedDeviceType DeviceType);` — `UE_DEPRECATED(5.1, "LiveLinkXR no longer uses EXRTrackedDeviceType.")`
- L62 _private prototype_ `void OnLiveLinkSubjectAdded(FLiveLinkSubjectKey InSubjectKey);` — Callback when the a livelink subject has been added
- L65 _private member_ `ILiveLinkClient* Client = nullptr;`
- L68 _private member_ `FGuid SourceGuid;` — Our identifier in LiveLink
- L70 _private member_ `FText SourceType;`
- L71 _private member_ `FText SourceMachineName;`
- L72 _private member_ `FText SourceStatus;`
- L75 _private member_ `std::atomic<bool> bStopping = false;` — Threadsafe flag for terminating the main thread loop
- L78 _private member_ `FRunnableThread* Thread = nullptr;` — Thread to update poses from
- L81 _private member_ `FString ThreadName;` — Name of the update thread
- L84 _private member_ `TSet<FName> EncounteredSubjects;` — List of subjects we've already encountered
- L87 _private member_ `TSet<FName> SubjectsToRebroadcast;` — List of subjects to automatically set to rebroadcast
- L90 _private member_ `FDelegateHandle DeferredStartDelegateHandle;` — Deferred start delegate handle.
- L93 _private member_ `int32 FrameCounter = 0;` — frame counter for data
- L96 _private member_ `std::atomic<uint32> LocalUpdateRateInHz;` — Update rate (in Hz) at which to read the tracking data for each device
- L99 _private member_ `FCriticalSection TrackedDeviceCriticalSection;` — Critical section protection tracked devices
- L102 _private member_ `FDelegateHandle OnSubjectAddedDelegate;` — Delegate for when the LiveLink client has ticked
- L104 _private member_ `const FLiveLinkXRConnectionSettings ConnectionSettings;`
- L105 _private member_ `ULiveLinkXRSourceSettings* SavedSourceSettings = nullptr;`

### `Plugins/VirtualProduction/LiveLinkXR/Source/LiveLinkXR/Public/LiveLinkXRSourceFactory.h` (Public)


#### class `ULiveLinkXRSourceFactory`  
`class ULiveLinkXRSourceFactory : public ULiveLinkSourceFactory`  
_L10-24_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceFactory`
- L15 _public prototype_ `virtual FText GetSourceDisplayName() const override;`
- L16 _public prototype_ `virtual FText GetSourceTooltip() const override;`
- L18 _public function_ `virtual EMenuType GetMenuType() const override`
- L19 _public prototype_ `virtual TSharedPtr<SWidget> BuildCreationPanel(FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const override;`
- L20 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& ConnectionString) const override;`
- L23 _private prototype_ `void CreateSourceFromSettings(FLiveLinkXRConnectionSettings ConnectionSettings, FOnLiveLinkSourceCreated OnSourceCreated) const;`

### `Plugins/VirtualProduction/LiveLinkXR/Source/LiveLinkXR/Public/LiveLinkXRSourceSettings.h` (Public)


#### class `ULiveLinkXRSourceSettings`  
`class ULiveLinkXRSourceSettings : public ULiveLinkSourceSettings`  
_L11-19_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceSettings`
- L18 _public member_ `uint32 LocalUpdateRateInHz = 60;` — `UPROPERTY(EditAnywhere, Category="LiveLinkXR", meta=(ClampMin=1, ClampMax=1000))` — Update rate (in Hz) at which to read the tracking data for each device
