# Plugins / LiveLinkOpenVR

- module root: `Plugins/Experimental/LiveLinkOpenVR/Source/LiveLinkOpenVR`
- headers: 4; symbols: 67
- symbol kinds: class=4, delegate=1, function=8, member=28, namespace=1, prototype=23, struct=2
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, LiveLinkInterface, OpenVR, Projects, Slate, SlateCore

### `Plugins/Experimental/LiveLinkOpenVR/Source/LiveLinkOpenVR/Private/LiveLinkOpenVRModule.h` (Private)


#### class `FLiveLinkOpenVRModule`  
`class FLiveLinkOpenVRModule : public IModuleInterface`  
_L17-37_
- inherits: `IModuleInterface`
- L20 _public function_ `static FLiveLinkOpenVRModule& Get()`
- L25 _public prototype_ `virtual void StartupModule() override;`
- L26 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _public prototype_ `vr::IVRSystem* GetVrSystem();`
- L31 _private prototype_ `bool LoadOpenVRLibrary();`
- L32 _private prototype_ `bool UnloadOpenVRLibrary();`
- L35 _private member_ `void* OpenVRDLLHandle = nullptr;`
- L36 _private member_ `vr::IVRSystem* VrSystem = nullptr;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace vr`
- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkOpenVR, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkOpenVR, Log, All);`

### `Plugins/Experimental/LiveLinkOpenVR/Source/LiveLinkOpenVR/Private/LiveLinkOpenVRSource.h` (Private)


#### class `FLiveLinkOpenVRSource`  
`class FLiveLinkOpenVRSource : public ILiveLinkSource , public FRunnable , public TSharedFromThis<FLiveLinkOpenVRSource>`  
_L11-93_
- inherits: `ILiveLinkSource,FRunnable,TSharedFromThis<FLiveLinkOpenVRSource>`
- L17 _public prototype_ `FLiveLinkOpenVRSource(const FLiveLinkOpenVRConnectionSettings& InConnectionSettings);`
- L19 _public prototype_ `virtual ~FLiveLinkOpenVRSource();`
- L22 _public prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;`
- L23 _public prototype_ `virtual void InitializeSettings(ULiveLinkSourceSettings* InSettings) override;`
- L24 _public function_ `virtual void Update() override`
- L26 _public prototype_ `virtual bool IsSourceStillValid() const override;`
- L28 _public prototype_ `virtual bool RequestSourceShutdown() override;`
- L30 _public function_ `virtual FText GetSourceType() const override`
- L31 _public function_ `virtual FText GetSourceMachineName() const override`
- L32 _public function_ `virtual FText GetSourceStatus() const override`
- L34 _public prototype_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const override;`
- L38 _public function_ `virtual bool Init() override`
- L39 _public prototype_ `virtual uint32 Run() override;`
- L40 _public prototype_ `void Start();`
- L41 _public prototype_ `virtual void Stop() override;`
- L42 _public function_ `virtual void Exit() override`
- L45 _public prototype_ `void Send(FLiveLinkFrameDataStruct&& InFrameData, FName InSubjectName);`
- L49 _private prototype_ `void OnLiveLinkSubjectAdded(FLiveLinkSubjectKey InSubjectKey);` — Callback when the a livelink subject has been added
- L52 _private member_ `const FLiveLinkOpenVRConnectionSettings ConnectionSettings;`
- L53 _private member_ `ILiveLinkClient* Client = nullptr;`
- L56 _private member_ `FGuid SourceGuid;` — Our identifier in LiveLink
- L58 _private member_ `FText SourceType;`
- L59 _private member_ `FText SourceMachineName;`
- L60 _private member_ `FText SourceStatus;`
- L63 _private member_ `std::atomic<bool> bStopping = false;` — Threadsafe flag for terminating the main thread loop
- L66 _private member_ `FRunnableThread* Thread = nullptr;` — Thread to update poses from
- L69 _private member_ `FString ThreadName;` — Name of the update thread
- L72 _private member_ `TStaticArray<FName, 64> SubjectNames;` — List of subjects we've already encountered
- L75 _private member_ `TSet<FName> SubjectsToRebroadcast;` — List of subjects to automatically set to rebroadcast
- L78 _private member_ `FDelegateHandle DeferredStartDelegateHandle;` — Deferred start delegate handle.
- L81 _private member_ `int64 FrameCounter = 0;` — frame counter for data
- L83 _private member_ `TWeakObjectPtr<ULiveLinkOpenVRSourceSettings> Settings;`
- L86 _private member_ `std::atomic<bool> bTrackTrackers_AnyThread;` — Atomic copies of UObject fields updated on change notification
- L87 _private member_ `std::atomic<bool> bTrackControllers_AnyThread;`
- L88 _private member_ `std::atomic<bool> bTrackHMDs_AnyThread;`
- L89 _private member_ `std::atomic<uint32> LocalUpdateRateInHz_AnyThread;`
- L92 _private member_ `FDelegateHandle OnSubjectAddedDelegate;` — Delegate for when the LiveLink client has ticked

### `Plugins/Experimental/LiveLinkOpenVR/Source/LiveLinkOpenVR/Private/LiveLinkOpenVRSourceFactory.h` (Private)


#### class `ULiveLinkOpenVRSourceFactory`  
`class ULiveLinkOpenVRSourceFactory : public ULiveLinkSourceFactory`  
_L11-27_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceFactory`
- L17 _public prototype_ `virtual FText GetSourceDisplayName() const override;`
- L18 _public prototype_ `virtual FText GetSourceTooltip() const override;`
- L20 _public function_ `virtual EMenuType GetMenuType() const override`
- L21 _public prototype_ `virtual TSharedPtr<SWidget> BuildCreationPanel(FOnLiveLinkSourceCreated InOnLiveLinkSourceCreated) const override;`
- L22 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& InConnectionString) const override;`
- L26 _private prototype_ `void CreateSourceFromSettings(FLiveLinkOpenVRConnectionSettings InConnectionSettings, FOnLiveLinkSourceCreated InOnSourceCreated) const;`

### `Plugins/Experimental/LiveLinkOpenVR/Source/LiveLinkOpenVR/Private/LiveLinkOpenVRTypes.h` (Private)


#### struct `FLiveLinkOpenVRCommonSettings`  
`struct FLiveLinkOpenVRCommonSettings`  
_L11-19_
- reflection: `USTRUCT()`
- desc: Settings relevant to both initial factory/"connection" as well as existing sources.
- L18 _public member_ `uint32 LocalUpdateRateInHz = 60;` — `UPROPERTY(EditAnywhere, Category="LiveLinkOpenVR Settings", meta=(ClampMin=1, ClampMax=1000))` — Update rate (in Hz) at which to read the tracking data for each device

#### struct `FLiveLinkOpenVRConnectionSettings`  
`struct FLiveLinkOpenVRConnectionSettings`  
_L23-45_
- reflection: `USTRUCT()`
- L28 _public member_ `FLiveLinkOpenVRCommonSettings CommonSettings;` — `UPROPERTY(EditAnywhere, Category="LiveLinkOpenVR Settings", meta=(ShowOnlyInnerProperties))`
- L32 _public member_ `bool bTrackTrackers = true;` — `UPROPERTY(EditAnywhere, Category="LiveLinkOpenVR Settings")` — Track all tracker pucks
- L36 _public member_ `bool bTrackTrackingReferences = true;` — `UPROPERTY(EditAnywhere, Category="LiveLinkOpenVR Settings")` — Track all tracking references (e.g. base stations)
- L40 _public member_ `bool bTrackControllers = false;` — `UPROPERTY(EditAnywhere, Category="LiveLinkOpenVR Settings")` — Track all controllers
- L44 _public member_ `bool bTrackHMDs = false;` — `UPROPERTY(EditAnywhere, Category="LiveLinkOpenVR Settings")` — Track all HMDs

#### class `ULiveLinkOpenVRSourceSettings`  
`class ULiveLinkOpenVRSourceSettings : public ULiveLinkSourceSettings`  
_L49-56_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceSettings`
- L55 _public member_ `FLiveLinkOpenVRCommonSettings CommonSettings;` — `UPROPERTY(EditAnywhere, Category="LiveLinkOpenVR Settings", meta=(ShowOnlyInnerProperties))`
