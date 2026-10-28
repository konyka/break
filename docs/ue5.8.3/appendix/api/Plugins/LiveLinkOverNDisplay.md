# Plugins / LiveLinkOverNDisplay

- module root: `Plugins/Runtime/LiveLinkOvernDisplay/Source/LiveLinkOverNDisplay`
- headers: 6; symbols: 61
- symbol kinds: class=5, delegate=1, enum=1, enumerator=3, function=7, member=8, prototype=36
- PrivateDependencyModuleNames: DisplayCluster, Engine, LiveLinkInterface, Settings
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Runtime/LiveLinkOvernDisplay/Source/LiveLinkOverNDisplay/Private/LiveLinkOverNDisplayModule.h` (Private)


#### class `FLiveLinkOverNDisplayModule`  
`class FLiveLinkOverNDisplayModule : public ILiveLinkOverNDisplayModule, public TSharedFromThis<FLiveLinkOverNDisplayModule>`  
_L15-39_
- inherits: `ILiveLinkOverNDisplayModule,TSharedFromThis<FLiveLinkOverNDisplayModule>`
- desc: Entry point for LiveLinkOverNDisplay functionality.
- L19 _public prototype_ `FLiveLinkOverNDisplayModule();`
- L22 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _public prototype_ `virtual FNDisplayLiveLinkSubjectReplicator& GetSubjectReplicator() override;`
- L31 _private prototype_ `void OnEngineLoopInitComplete();`
- L32 _private prototype_ `void OnDisplayClusterStartSceneCallback() const;`
- L33 _private prototype_ `void OnDisplayClusterEndSceneCallback() const;`
- L38 _private member_ `TUniquePtr<FNDisplayLiveLinkSubjectReplicator> LiveLinkReplicator;` — Replicator SyncObject used to transfer data across all cluster machines

### `Plugins/Runtime/LiveLinkOvernDisplay/Source/LiveLinkOverNDisplay/Private/LiveLinkOverNDisplayPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkOverNDisplay, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkOverNDisplay, Log, All);`

### `Plugins/Runtime/LiveLinkOvernDisplay/Source/LiveLinkOverNDisplay/Private/NDisplayAgentVirtualSubject.h` (Private)


#### class `UNDisplayAgentVirtualSubject`  
`class UNDisplayAgentVirtualSubject : public ULiveLinkVirtualSubject`  
_L19-42_
- reflection: `UCLASS()`
- inherits: `ULiveLinkVirtualSubject`
- desc: LiveLink VirtualSubject used on nDisplay agents to replicate real subjects Controller sends data to use for each frame to make sure all machines display / uses the same data Uses Replicator object that this module creates.
- L26 _public prototype_ `virtual void Update() override;`
- L29 _public prototype_ `void UpdateFrameData(FLiveLinkFrameDataStruct&& NewFrameData);`
- L32 _public prototype_ `void SetTrackedSubjectInfo(const FLiveLinkSubjectKey& SubjectKey, TSubclassOf<ULiveLinkRole> Role);`
- L34 _public prototype_ `void UpdateTranslators(const TArray<ULiveLinkFrameTranslator*>& SourceTranslators);`
- L36 _public function_ `FLiveLinkSubjectKey GetAssociatedSubjectKey() const`
- L41 _private member_ `FLiveLinkSubjectKey AssociatedSubject;` — Real subject that this virtual subject replicates

### `Plugins/Runtime/LiveLinkOvernDisplay/Source/LiveLinkOverNDisplay/Private/NDisplayLiveLinkSubjectReplicator.h` (Private)


#### class `FNDisplayLiveLinkSubjectReplicator`  
`class FNDisplayLiveLinkSubjectReplicator : public IDisplayClusterClusterSyncObject, public FGCObject`  
_L25-119_
- inherits: `IDisplayClusterClusterSyncObject,FGCObject`
- desc: Classes used to replicates data to be used for each frame for each enabled subjects on the Controller machines. Agents will use that replicated data to use the same thing on each machines
- L37 _public prototype_ `FNDisplayLiveLinkSubjectReplicator() = default;`
- L38 _public prototype_ `virtual ~FNDisplayLiveLinkSubjectReplicator();`
- L41 _public prototype_ `FNDisplayLiveLinkSubjectReplicator(const FNDisplayLiveLinkSubjectReplicator&) = delete;` — Move only type since we're owning LiveLink base structs
- L42 _public prototype_ `FNDisplayLiveLinkSubjectReplicator& operator=(const FNDisplayLiveLinkSubjectReplicator&) = delete;`
- L45 _public prototype_ `virtual bool IsActive() const override;`
- L46 _public prototype_ `virtual FString GetSyncId() const override;`
- L47 _public function_ `virtual bool IsDirty() const override`
- L48 _public prototype_ `virtual void SerializeDC(FArchive& Ar) override;`
- L52 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L53 _public function_ `virtual FString GetReferencerName() const override`
- L60 _public prototype_ `void Initialize();` — Initializes all required callbacks and LiveLink source
- L63 _public prototype_ `void Release();` — Releases all internal resources and callbacks
- L66 _public prototype_ `void Activate();` — Registers ourself as sync object in nDisplay
- L69 _public prototype_ `void Deactivate();` — Unregisters ourself as sync object from nDisplay
- L77 _protected prototype_ `void OnEngineBeginFrame();` — Hook to beginning of frames to make sure our replicated virtual subjects are the ones enabled @note Only called on Agent
- L80 _protected prototype_ `void OnDataSynchronization(FArchive& Ar);` — Synchronization point when object is going to be synchronized across nDisplay cluster
- L83 _protected prototype_ `void HandleNewSubject(FArchive& Ar, FLiveLinkSubjectKey& SubjectKey, TSubclassOf<ULiveLinkRole>& SubjectRole, FLiveLinkSubjectFrameData& SubjectFrame);` — Process new subject data when serializing SyncObject
- L86 _protected prototype_ `void HandleFrame(FArchive& Ar, EFrameType& FrameType, FLiveLinkSubjectKey& SubjectKey, TSubclassOf<ULiveLinkRole>& SubjectRole, FLiveLinkSubjectFrameData& SubjectFrame);` — Process a frame for a specific subject
- L89 _protected prototype_ `void ProcessLiveLinkData_Agent(EFrameType FrameType, const FLiveLinkSubjectKey& SubjectKey, FLiveLinkFrameDataStruct& FrameData);` — Only used on agents, handles this frame data for a subject. If a new subject is handled, the associated VirtualSubject will be created
- L92 _protected prototype_ `void ReInitializeVirtualSource();` — For agent only, remove tracked subjets, add ourself as a source
- L95 _protected prototype_ `void OnLiveLinkSourceRemoved(FGuid SourceGuid);` — If our source is removed (could happen if a new preset is applied), reinitialize ourself to stay awake
- L98 _protected prototype_ `void OnModularFeatureRemoved(const FName& Type , IModularFeature* ModularFeature);` — Listen for modular feature removed in case LiveLink gets unloaded
- L101 _protected prototype_ `void OnDisplayClusterPrimaryNodeChanged(const FString& NewPrimaryId);` — Post-failover handler. It's a callback that informs about new p-node ID
- L104 _protected prototype_ `void SetSubjectsEnabled(bool bIncludeDisabled, bool bIncludeVirtual, bool bEnabled);` — A helper to enable/disable all the subjects
- L109 _private member_ `ILiveLinkClient* LiveLinkClient = nullptr;` — Cached LiveLinkClient when modular feature is registered
- L112 _private member_ `TArray<TObjectPtr<UNDisplayAgentVirtualSubject>> TrackedSubjects;` — List of Subjects that we are replicating across cluster. On Agents, it will actually be added to the LiveLink subject's list
- L115 _private member_ `FGuid LiveLinkSourceGuid;` — Guid associated to our Virtual Subject Source
- L118 _private member_ `std::atomic<bool> bBecamePrimary = false;` — Used to re-initialize current node after failure handling

#### enum `FNDisplayLiveLinkSubjectReplicator::EFrameType`  
`enum class EFrameType : uint8`  
_L28-33_
- L30 _public enumerator_ `DataOnly`
- L31 _public enumerator_ `NewSubject` — A new subject was sent this frame.
- L32 _public enumerator_ `UpdatedSubject` — The subject's static data or role was updated this frame.

### `Plugins/Runtime/LiveLinkOvernDisplay/Source/LiveLinkOverNDisplay/Public/ILiveLinkOverNDisplayModule.h` (Public)


#### class `ILiveLinkOverNDisplayModule`  
`class ILiveLinkOverNDisplayModule : public IModuleInterface`  
_L13-36_
- inherits: `IModuleInterface`
- desc: Interface for LiveLinkOverNDisplay module.
- L20 _public function_ `static ILiveLinkOverNDisplayModule& Get()` — Gets a reference to the LiveLinkOverNDisplay module instance.
- L25 _public function_ `static inline bool IsAvailable()`
- L30 _public prototype_ `virtual FNDisplayLiveLinkSubjectReplicator& GetSubjectReplicator() = 0;`
- L35 _public function_ `virtual ~ILiveLinkOverNDisplayModule()` — Virtual destructor.

### `Plugins/Runtime/LiveLinkOvernDisplay/Source/LiveLinkOverNDisplay/Public/LiveLinkOverNDisplaySettings.h` (Public)


#### class `ULiveLinkOverNDisplaySettings`  
`class ULiveLinkOverNDisplaySettings : public UObject`  
_L10-30_
- reflection: `UCLASS(config=Engine)`
- inherits: `UObject`
- L15 _public prototype_ `ULiveLinkOverNDisplaySettings();`
- L18 _public function_ `bool IsLiveLinkOverNDisplayEnabled() const` — Whether or not LiveLink over NDisplay is enabled, from command line first or from project settings
- L26 _protected member_ `bool bIsEnabled = true;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkOverNDisplay Settings")` — Enables nDisplay specific LiveLink subjects management across nDisplay cluster. @note Can be overrided via the command line using -EnableLiveLinkOverNDisplay=false
- L29 _protected member_ `TOptional<bool> bIsEnabledFromCommandLine;` — Command line override value if it was set on the command line
