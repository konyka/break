# Runtime / ChaosVDRuntime

- module root: `Source/Runtime/Experimental/ChaosVisualDebugger`
- headers: 13; symbols: 1031
- symbol kinds: class=2, delegate=7, enum=47, enumerator=215, function=69, macro=6, member=500, namespace=9, prototype=102, struct=73, variable=1
- PublicDependencyModuleNames: Core, CoreUObject, TraceBasedDebuggers, TraceLog

### `Source/Runtime/Experimental/ChaosVisualDebugger/Public/ChaosVDRecordingDetails.h` (Public)


#### struct `FChaosVDStartRecordingCommandMessage`  
`struct FChaosVDStartRecordingCommandMessage : public UE::TraceBasedDebuggers::FStartRecordingCommandMessage`  
_L23-29_
- reflection: `USTRUCT()`
- inherits: `UE::TraceBasedDebuggers::FStartRecordingCommandMessage`
- desc: CVD specific message to send a start recording command with optional list of data channels to force to be enabled.
- L28 _public member_ `TArray<FString> DataChannelsEnabledOverrideList;` — `UPROPERTY()`

#### enum `EChaosVDRecordingMode`  
`enum class UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::ERecordingMode instead.") EChaosVDRecordingMode : uint8`  
_L33-38_
- L35 _public enumerator_ `Invalid`
- L36 _public enumerator_ `Live`
- L37 _public enumerator_ `File`

#### enum `EChaosVDTransportMode`  
`enum class UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::ETraceTransportMode instead.") EChaosVDTransportMode : uint8`  
_L40-51_
- L42 _public enumerator_ `Invalid`
- L44 _public enumerator_ `FileSystem` — The data will be traced directly to a file in the local file system
- L46 _public enumerator_ `TraceServer` — Data will be traced to the selected trace store server
- L48 _public enumerator_ `Direct` — Data will be traced directly to the editor, accessible via sockets
- L50 _public enumerator_ `Relay` — Data will be traced via the trace relay system using a custom transport, like normal UE Networking or a direct socket connection

#### struct `FChaosVDTraceDetails`  
`struct UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FTraceConnectionDetails instead.") FChaosVDTraceDetails : public UE::TraceBasedDebuggers::FTraceConnectionDetails`  
_L53-62_
- inherits: `UE::TraceBasedDebuggers::FTraceConnectionDetails`
- L55 _public prototype_ `FChaosVDTraceDetails() = default;`
- L58 _public member_ `bool bIsConnected = false;` — `UE_DEPRECATED(5.7, "This property is no longer used and it will removed in the future")`
- L61 _public member_ `EChaosVDRecordingMode Mode = EChaosVDRecordingMode::Invalid;` — `UE_DEPRECATED(5.8, "Recording mode is no longer valid and will not be replaced")`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Chaos`
- L14 _namespace_ `namespace VD` (scope `Chaos`)
- L17 _variable_ `static constexpr FGuid DebuggerGuid = FGuid(0x34CFFA28, 0x72434D08, 0xB07AD3FE, 0xE2D96272);` (scope `Chaos::VD`) — Debugger Guid used to identify the debugger type when sending command and update messages

### `Source/Runtime/Experimental/ChaosVisualDebugger/Public/ChaosVDRuntimeModule.h` (Public)


#### enum `EChaosVDFullCaptureFlags`  
`enum class EChaosVDFullCaptureFlags : int32`  
_L36-40_
- desc: Option flags that controls what should be recorded when doing a full capture
- L38 _public enumerator_ `Geometry = 1 << 0`
- L39 _public enumerator_ `Particles = 1 << 1`

#### class `FChaosVDRuntimeModule`  
`class FChaosVDRuntimeModule : public UE::TraceBasedDebuggers::FRuntimeModule, public IModuleInterface`  
_L58-188_
- inherits: `UE::TraceBasedDebuggers::FRuntimeModule,IModuleInterface`
- L62 _public prototype_ `FChaosVDRuntimeModule();`
- L63 _public prototype_ `static FChaosVDRuntimeModule& Get();`
- L65 _public prototype_ `virtual void StartupModule() override;`
- L66 _public prototype_ `virtual void ShutdownModule() override;`
- L73 _public function_ `void StartRecording(const FChaosVDStartRecordingCommandMessage& InRecordingStartCommand)` — Starts a CVD recording by starting a Trace session. It will stop any existing trace session @param InRecordingStartCommand : Used to determine if we want to record to file or a local trace server among other settings
- L79 _public prototype_ `int32 GenerateUniqueID();` — Returns a unique ID used to be used to identify CVD (Chaos Visual Debugger) data
- L81 _public function_ `static FDelegateHandle RegisterRecordingStartedCallback(const FChaosVDRecordingStateChangedDelegate::FDelegate& InCallback)`
- L87 _public function_ `static FDelegateHandle RegisterPostRecordingStartedCallback(const FChaosVDRecordingStateChangedDelegate::FDelegate& InCallback)`
- L93 _public function_ `static FDelegateHandle RegisterRecordingStopCallback(const FChaosVDRecordingStateChangedDelegate::FDelegate& InCallback)`
- L99 _public function_ `static FDelegateHandle RegisterRecordingStartFailedCallback(const FChaosVDRecordingStartFailedDelegate::FDelegate& InCallback)`
- L105 _public function_ `static FDelegateHandle RegisterFullCaptureRequestedCallback(const FChaosVDCaptureRequestDelegate::FDelegate& InCallback)`
- L111 _public function_ `static bool RemoveRecordingStartedCallback(const FDelegateHandle& InDelegateToRemove)`
- L117 _public function_ `static bool RemovePostRecordingStartedCallback(const FDelegateHandle& InDelegateToRemove)`
- L123 _public function_ `static bool RemoveRecordingStopCallback(const FDelegateHandle& InDelegateToRemove)`
- L129 _public function_ `static bool RemoveRecordingStartFailedCallback(const FDelegateHandle& InDelegateToRemove)`
- L135 _public function_ `static bool RemoveFullCaptureRequestedCallback(const FDelegateHandle& InDelegateToRemove)`
- L145 _public prototype_ `FString GetLastRecordingFileNamePath() const;` — `UE_DEPRECATED(5.7, "This method is no longer used. Use GetCurrentTraceConnectionDetails")` — [Deprecated] Returns the full path of the active recording file
- L148 _public prototype_ `FChaosVDTraceDetails GetCurrentTraceSessionDetails() const;` — `UE_DEPRECATED(5.8, "This method is no longer used. Use GetCurrentTraceConnectionDetails")`
- L151 _public function_ `EChaosVDRecordingMode GetCurrentRecordingMode() const` — `UE_DEPRECATED(5.8, "This method is no longer used and will not be replaced")`
- L157 _public function_ `void RegisterExternalTraceStatusProvider(const FChaosVDExternalTraceStatusDelegate& InExternalTraceStatusCallback)` — `UE_DEPRECATED(5.8, "Use the overload taking FChaosVDExternalTraceConnectionStatusDelegate instead")`
- L162 _public function_ `Chaos::VD::FRelayTraceWriter* GetRelayWriterInstance() const` — `UE_DEPRECATED(5.8, "Use GetRelayTraceWriterInstance instead.")`
- L170 _private prototype_ `virtual void OnRecordingStartedInternal() override;`
- L171 _private prototype_ `virtual void OnRecordingStartFailedInternal(const FText& FailureReason) override;`
- L172 _private prototype_ `virtual void OnRecordingStoppedInternal() override;`
- L173 _private prototype_ `virtual void OnEnableRequiredTraceChannelsInternal() override;`
- L176 _private prototype_ `bool RequestFullCapture(float DeltaTime);` — Queues a full Capture of the simulation on the next frame
- L178 _private member_ `FTSTicker::FDelegateHandle FullCaptureRequesterHandle;`
- L180 _private member_ `static FChaosVDRecordingStateChangedDelegate RecordingStartedDelegate;`
- L181 _private member_ `static FChaosVDRecordingStateChangedDelegate PostRecordingStartedDelegate;`
- L182 _private member_ `static FChaosVDRecordingStateChangedDelegate RecordingStopDelegate;`
- L183 _private member_ `static FChaosVDRecordingStartFailedDelegate RecordingStartFailedDelegate;`
- L184 _private member_ `static FChaosVDCaptureRequestDelegate PerformFullCaptureDelegate;`
- L185 _private member_ `static FTransactionallySafeRWLock DelegatesRWLock;`
- L187 _private member_ `std::atomic<int32> LastGeneratedID;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API CHAOSVDRUNTIME_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L30 _namespace_ `namespace Chaos`
- L30 _namespace_ `namespace VD` (scope `Chaos`)
- L43 _delegate_ `DECLARE_MULTICAST_DELEGATE(FChaosVDRecordingStateChangedDelegate) DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDCaptureRequestDelegate, EChaosVDFullCaptureFlags) DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDRecordingStartFailedDelegate, const FText&) PRAGMA_DISABLE_DEPRECATION_WARNINGS UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FRelayTraceDataDelegate instead") DECLARE_DELEGATE_OneParam(FChaosVDRelayTraceDataDelegate, Chaos::VD::FRelayTraceWriter&) UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FExternalRelayBufferQueueSizeDelegate instead") DECLARE_DELEGATE_RetVal(uint64, FChaosVDExternalRelayBufferQueueSizeDelegate) UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FTraceConnectionDetails instead") DECLARE_DELEGATE_RetVal(FChaosVDTraceDetails, FChaosVDExternalTraceStatusDelegate) PRAGMA_ENABLE_DEPRECATION_WARNINGS DECLARE_LOG_CATEGORY_EXTERN(LogChaosVDRuntime, Log, All) class FChaosVDRuntimeModule : public UE::TraceBasedDebuggers::FRuntimeModule, public IModuleInterface { public: FChaosVDRuntimeModule(); static FChaosVDRuntimeModule& Get(); virtual void StartupModule() override; virtual void ShutdownModule() override; using FRuntimeModule::StartRecording; void StartRecording(const FChaosVDStartRecordingCommandMessage& InRecordingStartCommand) { FRuntimeModule::StartRecording(InRecordingStartCommand); } int32 GenerateUniqueID(); static FDelegateHandle RegisterRecordingStartedCallback(const FChaosVDRecordingStateChangedDelegate::FDelegate& InCallback) {`
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDCaptureRequestDelegate, EChaosVDFullCaptureFlags) DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDRecordingStartFailedDelegate, const FText&) PRAGMA_DISABLE_DEPRECATION_WARNINGS UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FRelayTraceDataDelegate instead") DECLARE_DELEGATE_OneParam(FChaosVDRelayTraceDataDelegate, Chaos::VD::FRelayTraceWriter&) UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FExternalRelayBufferQueueSizeDelegate instead") DECLARE_DELEGATE_RetVal(uint64, FChaosVDExternalRelayBufferQueueSizeDelegate) UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FTraceConnectionDetails instead") DECLARE_DELEGATE_RetVal(FChaosVDTraceDetails, FChaosVDExternalTraceStatusDelegate) PRAGMA_ENABLE_DEPRECATION_WARNINGS DECLARE_LOG_CATEGORY_EXTERN(LogChaosVDRuntime, Log, All) class FChaosVDRuntimeModule : public UE::TraceBasedDebuggers::FRuntimeModule, public IModuleInterface { public: FChaosVDRuntimeModule(); static FChaosVDRuntimeModule& Get(); virtual void StartupModule() override; virtual void ShutdownModule() override; using FRuntimeModule::StartRecording; void StartRecording(const FChaosVDStartRecordingCommandMessage& InRecordingStartCommand) { FRuntimeModule::StartRecording(InRecordingStartCommand); } int32 GenerateUniqueID(); static FDelegateHandle RegisterRecordingStartedCallback(const FChaosVDRecordingStateChangedDelegate::FDelegate& InCallback) { UE::TWriteScopeLock WriteLock(DelegatesRWLock);`
- L45 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDRecordingStartFailedDelegate, const FText&) PRAGMA_DISABLE_DEPRECATION_WARNINGS UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FRelayTraceDataDelegate instead") DECLARE_DELEGATE_OneParam(FChaosVDRelayTraceDataDelegate, Chaos::VD::FRelayTraceWriter&) UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FExternalRelayBufferQueueSizeDelegate instead") DECLARE_DELEGATE_RetVal(uint64, FChaosVDExternalRelayBufferQueueSizeDelegate) UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FTraceConnectionDetails instead") DECLARE_DELEGATE_RetVal(FChaosVDTraceDetails, FChaosVDExternalTraceStatusDelegate) PRAGMA_ENABLE_DEPRECATION_WARNINGS DECLARE_LOG_CATEGORY_EXTERN(LogChaosVDRuntime, Log, All) class FChaosVDRuntimeModule : public UE::TraceBasedDebuggers::FRuntimeModule, public IModuleInterface { public: FChaosVDRuntimeModule(); static FChaosVDRuntimeModule& Get(); virtual void StartupModule() override; virtual void ShutdownModule() override; using FRuntimeModule::StartRecording; void StartRecording(const FChaosVDStartRecordingCommandMessage& InRecordingStartCommand) { FRuntimeModule::StartRecording(InRecordingStartCommand); } int32 GenerateUniqueID(); static FDelegateHandle RegisterRecordingStartedCallback(const FChaosVDRecordingStateChangedDelegate::FDelegate& InCallback) { UE::TWriteScopeLock WriteLock(DelegatesRWLock); return RecordingStartedDelegate.Add(InCallback);`
- L49 _delegate_ `DECLARE_DELEGATE_OneParam(FChaosVDRelayTraceDataDelegate, Chaos::VD::FRelayTraceWriter&) UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FExternalRelayBufferQueueSizeDelegate instead") DECLARE_DELEGATE_RetVal(uint64, FChaosVDExternalRelayBufferQueueSizeDelegate) UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FTraceConnectionDetails instead") DECLARE_DELEGATE_RetVal(FChaosVDTraceDetails, FChaosVDExternalTraceStatusDelegate) PRAGMA_ENABLE_DEPRECATION_WARNINGS DECLARE_LOG_CATEGORY_EXTERN(LogChaosVDRuntime, Log, All) class FChaosVDRuntimeModule : public UE::TraceBasedDebuggers::FRuntimeModule, public IModuleInterface { public: FChaosVDRuntimeModule(); static FChaosVDRuntimeModule& Get(); virtual void StartupModule() override; virtual void ShutdownModule() override; using FRuntimeModule::StartRecording; void StartRecording(const FChaosVDStartRecordingCommandMessage& InRecordingStartCommand) { FRuntimeModule::StartRecording(InRecordingStartCommand); } int32 GenerateUniqueID(); static FDelegateHandle RegisterRecordingStartedCallback(const FChaosVDRecordingStateChangedDelegate::FDelegate& InCallback) { UE::TWriteScopeLock WriteLock(DelegatesRWLock); return RecordingStartedDelegate.Add(InCallback); } static FDelegateHandle RegisterPostRecordingStartedCallback(const FChaosVDRecordingStateChangedDelegate::FDelegate& InCallback) {`
- L51 _delegate_ `DECLARE_DELEGATE_RetVal(uint64, FChaosVDExternalRelayBufferQueueSizeDelegate) UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FTraceConnectionDetails instead") DECLARE_DELEGATE_RetVal(FChaosVDTraceDetails, FChaosVDExternalTraceStatusDelegate) PRAGMA_ENABLE_DEPRECATION_WARNINGS DECLARE_LOG_CATEGORY_EXTERN(LogChaosVDRuntime, Log, All) class FChaosVDRuntimeModule : public UE::TraceBasedDebuggers::FRuntimeModule, public IModuleInterface { public: FChaosVDRuntimeModule(); static FChaosVDRuntimeModule& Get(); virtual void StartupModule() override; virtual void ShutdownModule() override; using FRuntimeModule::StartRecording; void StartRecording(const FChaosVDStartRecordingCommandMessage& InRecordingStartCommand) { FRuntimeModule::StartRecording(InRecordingStartCommand); } int32 GenerateUniqueID(); static FDelegateHandle RegisterRecordingStartedCallback(const FChaosVDRecordingStateChangedDelegate::FDelegate& InCallback) { UE::TWriteScopeLock WriteLock(DelegatesRWLock); return RecordingStartedDelegate.Add(InCallback); } static FDelegateHandle RegisterPostRecordingStartedCallback(const FChaosVDRecordingStateChangedDelegate::FDelegate& InCallback) { UE::TWriteScopeLock WriteLock(DelegatesRWLock); return PostRecordingStartedDelegate.Add(InCallback);`
- L53 _delegate_ `DECLARE_DELEGATE_RetVal(FChaosVDTraceDetails, FChaosVDExternalTraceStatusDelegate) PRAGMA_ENABLE_DEPRECATION_WARNINGS DECLARE_LOG_CATEGORY_EXTERN(LogChaosVDRuntime, Log, All) class FChaosVDRuntimeModule : public UE::TraceBasedDebuggers::FRuntimeModule, public IModuleInterface { public: FChaosVDRuntimeModule(); static FChaosVDRuntimeModule& Get(); virtual void StartupModule() override; virtual void ShutdownModule() override; using FRuntimeModule::StartRecording; void StartRecording(const FChaosVDStartRecordingCommandMessage& InRecordingStartCommand) { FRuntimeModule::StartRecording(InRecordingStartCommand); } int32 GenerateUniqueID(); static FDelegateHandle RegisterRecordingStartedCallback(const FChaosVDRecordingStateChangedDelegate::FDelegate& InCallback) { UE::TWriteScopeLock WriteLock(DelegatesRWLock); return RecordingStartedDelegate.Add(InCallback); } static FDelegateHandle RegisterPostRecordingStartedCallback(const FChaosVDRecordingStateChangedDelegate::FDelegate& InCallback) { UE::TWriteScopeLock WriteLock(DelegatesRWLock); return PostRecordingStartedDelegate.Add(InCallback); }`
- L56 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosVDRuntime, Log, All) class FChaosVDRuntimeModule : public UE::TraceBasedDebuggers::FRuntimeModule, public IModuleInterface { public: FChaosVDRuntimeModule(); static FChaosVDRuntimeModule& Get(); virtual void StartupModule() override; virtual void ShutdownModule() override; using FRuntimeModule::StartRecording; void StartRecording(const FChaosVDStartRecordingCommandMessage& InRecordingStartCommand) { FRuntimeModule::StartRecording(InRecordingStartCommand); } int32 GenerateUniqueID(); static FDelegateHandle RegisterRecordingStartedCallback(const FChaosVDRecordingStateChangedDelegate::FDelegate& InCallback) { UE::TWriteScopeLock WriteLock(DelegatesRWLock); return RecordingStartedDelegate.Add(InCallback); } static FDelegateHandle RegisterPostRecordingStartedCallback(const FChaosVDRecordingStateChangedDelegate::FDelegate& InCallback) { UE::TWriteScopeLock WriteLock(DelegatesRWLock); return PostRecordingStartedDelegate.Add(InCallback); } static FDelegateHandle RegisterRecordingStopCallback(const FChaosVDRecordingStateChangedDelegate::FDelegate& InCallback) { UE::TWriteScopeLock WriteLock(DelegatesRWLock);`

### `Source/Runtime/Experimental/ChaosVisualDebugger/Public/DataWrappers/ChaosVDAccelerationStructureDataWrappers.h` (Public)


#### enum `EChaosVDAABBTreeNodeFlags`  
`enum class EChaosVDAABBTreeNodeFlags : uint8`  
_L10-15_
- reflection: `UENUM()`
- L12 _public enumerator_ `None = 0`
- L13 _public enumerator_ `IsLeaf = 1 << 0`
- L14 _public enumerator_ `IsDirty = 1 << 1`

#### enum `EChaosVDAccelerationStructureType`  
`enum class EChaosVDAccelerationStructureType : uint32`  
_L20-27_
- reflection: `UENUM()`
- L22 _public enumerator_ `BoundingVolume`
- L23 _public enumerator_ `AABBTree`
- L24 _public enumerator_ `AABBTreeBV`
- L25 _public enumerator_ `Collection`
- L26 _public enumerator_ `Unknown`

#### struct `FChaosVDAccelerationStructureBase`  
`struct FChaosVDAccelerationStructureBase : public FChaosVDWrapperDataBase`  
_L30-39_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L35 _public member_ `int32 SolverId = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="CVD Debug")`
- L38 _public member_ `EChaosVDAccelerationStructureType Type = EChaosVDAccelerationStructureType::Unknown;` — `UPROPERTY(VisibleAnywhere, Category="Data")`

#### struct `FChaosVDBVCellElementDataWrapper`  
`struct FChaosVDBVCellElementDataWrapper : public FChaosVDWrapperDataBase`  
_L42-56_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L47 _public member_ `FBox Bounds = FBox(EForceInit::ForceInit);` — `UPROPERTY(VisibleAnywhere, Category="Data")`
- L50 _public member_ `int32 ParticleIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="Data")`
- L52 _public member_ `FIntVector3 StartIdx = FIntVector3::ZeroValue;`
- L53 _public member_ `FIntVector3 EndIdx = FIntVector3::ZeroValue;`
- L55 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `FChaosVDBoundingVolumeDataWrapper`  
`struct FChaosVDBoundingVolumeDataWrapper : public FChaosVDAccelerationStructureBase`  
_L64-76_
- reflection: `USTRUCT()`
- inherits: `FChaosVDAccelerationStructureBase`
- L68 _public member_ `FIntVector3 MElementsCounts = FIntVector3::ZeroValue;`
- L70 _public member_ `TArray<TArray<FChaosVDBVCellElementDataWrapper>> MElements;`
- L73 _public member_ `double MaxPayloadBounds = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="Settings")`
- L75 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `FChaosVDAABBTreeNodeDataWrapper`  
`struct FChaosVDAABBTreeNodeDataWrapper : public FChaosVDWrapperDataBase`  
_L84-100_
- reflection: `USTRUCT(DisplayName="AABB Tree Node")`
- inherits: `FChaosVDWrapperDataBase`
- L89 _public member_ `FBox ChildrenBounds[2] = { FBox(ForceInitToZero), FBox(ForceInitToZero) };` — `UPROPERTY(VisibleAnywhere, Category="Node")`
- L91 _public member_ `int32 ChildrenNodes[2] = { INDEX_NONE, INDEX_NONE };` — `UPROPERTY(VisibleAnywhere, Category="Node")`
- L93 _public member_ `int32 ParentNode = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="Node")`
- L95 _public member_ `uint8 bLeaf : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="Node")`
- L97 _public member_ `uint8 bDirtyNode : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="Node")`
- L99 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `FChaosVDAABBTreePayloadBoundsElement`  
`struct FChaosVDAABBTreePayloadBoundsElement : public FChaosVDWrapperDataBase`  
_L108-124_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L113 _public member_ `int32 ParticleIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="Leaf")`
- L117 _public member_ `FBox Bounds = FBox(ForceInitToZero);` — `UPROPERTY(VisibleAnywhere, Category="Leaf")` — Bounds used to add this element into the AABBTree
- L121 _public member_ `FBox ActualBounds = FBox(ForceInitToZero);` — `UPROPERTY(VisibleAnywhere, Category="Leaf")` — Real Bounds of the element at the time we recorded the AABB Tree
- L123 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `FChaosVDAABBTreeLeafDataWrapper`  
`struct FChaosVDAABBTreeLeafDataWrapper : public FChaosVDWrapperDataBase`  
_L132-143_
- reflection: `USTRUCT(DisplayName="AABB Tree Leaf")`
- inherits: `FChaosVDWrapperDataBase`
- L137 _public member_ `TArray<FChaosVDAABBTreePayloadBoundsElement> Elements;` — `UPROPERTY(VisibleAnywhere, Category="Leaf")`
- L140 _public member_ `FBox Bounds = FBox(ForceInitToZero);` — `UPROPERTY(VisibleAnywhere, Category="Leaf")`
- L142 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `FChaosVDAccelerationStructureContainer`  
`struct FChaosVDAccelerationStructureContainer`  
_L151-156_
- reflection: `USTRUCT()`
- L155 _public member_ `TMap<int32, TArray<TSharedPtr<FChaosVDAABBTreeDataWrapper>>> RecordedAABBTreesBySolverID;`

#### struct `FChaosVDAABBTreeDataWrapper`  
`struct FChaosVDAABBTreeDataWrapper : public FChaosVDAccelerationStructureBase`  
_L159-199_
- reflection: `USTRUCT(DisplayName="AABB Tree Data")`
- inherits: `FChaosVDAccelerationStructureBase`
- L163 _public member_ `static FStringView WrapperTypeName;`
- L166 _public member_ `int32 RootNodeIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="Tree Data")`
- L169 _public member_ `int32 TreeDepth = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="Tree Data")`
- L172 _public member_ `int32 NodesNum = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="Tree Data")`
- L175 _public member_ `int32 LeavesNum = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="Tree Data")`
- L178 _public member_ `bool bDynamicTree = false;` — `UPROPERTY(VisibleAnywhere, Category="Tree Settings")`
- L181 _public member_ `int32 MaxChildrenInLeaf = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="Tree Settings")`
- L184 _public member_ `int32 MaxTreeDepth = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="Tree Settings")`
- L187 _public member_ `double MaxPayloadBounds = -1.0;` — `UPROPERTY(VisibleAnywhere, Category="Tree Settings")`
- L189 _public member_ `TArray<FChaosVDAABBTreeNodeDataWrapper> Nodes;`
- L191 _public member_ `TArray<FChaosVDAABBTreeLeafDataWrapper> TreeArrayLeafs;`
- L193 _public member_ `TArray<FChaosVDBoundingVolumeDataWrapper> BoundingVolumeLeafs;`
- L195 _public prototype_ `bool Serialize(FArchive& Ar);`
- L198 _public function_ `int32 GetCorrectedRootNodeIndex() const` — Returns a valid index for the root node taking ito account if this tree is dynamic or not

### `Source/Runtime/Experimental/ChaosVisualDebugger/Public/DataWrappers/ChaosVDCameraDataWrapper.h` (Public)


#### struct `FChaosVDCameraIdentifier`  
`struct FChaosVDCameraIdentifier`  
_L9-41_
- reflection: `USTRUCT()`
- L14 _public member_ `FName CameraName;` — `UPROPERTY()`
- L17 _public member_ `FName ActorName;` — `UPROPERTY()`
- L20 _public member_ `FTopLevelAssetPath ActorAssetPath;` — `UPROPERTY()`
- L23 _public member_ `FTopLevelAssetPath MapAssetPath;` — `UPROPERTY()`
- L25 _public function_ `bool operator==(const FChaosVDCameraIdentifier& CameraIdentifier) const`

#### struct `FChaosVDCameraDataWrapper`  
`struct FChaosVDCameraDataWrapper`  
_L44-64_
- reflection: `USTRUCT()`
- L48 _public member_ `static FStringView WrapperTypeName;`
- L51 _public member_ `FChaosVDCameraIdentifier Camera;` — `UPROPERTY()`
- L54 _public member_ `FVector Position = FVector::ZeroVector;` — `UPROPERTY()`
- L57 _public member_ `FQuat Rotation = FQuat::Identity;` — `UPROPERTY()`
- L60 _public member_ `float FOV = 0;` — `UPROPERTY()`
- L62 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `FChaosVDCameraDataContainer`  
`struct FChaosVDCameraDataContainer`  
_L67-72_
- reflection: `USTRUCT()`
- L71 _public member_ `TArray<TSharedPtr<FChaosVDCameraDataWrapper>> CameraData;`

#### Free symbols / members of external scopes

- L31 _function_ `friend uint32 GetTypeHash(const FChaosVDCameraIdentifier& Other)`

### `Source/Runtime/Experimental/ChaosVisualDebugger/Public/DataWrappers/ChaosVDCharacterGroundConstraintDataWrappers.h` (Public)


#### struct `FChaosVDCharacterGroundConstraintStateDataWrapper`  
`struct FChaosVDCharacterGroundConstraintStateDataWrapper : public FChaosVDWrapperDataBase`  
_L31-52_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L36 _public prototype_ `bool Serialize(FArchive& Ar);`
- L40 _public member_ `int32 Island = INDEX_NONE;`
- L41 _public member_ `int32 Level = INDEX_NONE;`
- L42 _public member_ `int32 Color = INDEX_NONE;`
- L43 _public member_ `int32 IslandSize = INDEX_NONE;`
- L46 _public member_ `bool bDisabled = false;` — `UPROPERTY(VisibleAnywhere, Category=ConstraintState)`
- L49 _public member_ `FVector SolverAppliedForce = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category= ConstraintState)`
- L51 _public member_ `FVector SolverAppliedTorque = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category= ConstraintState)`

#### struct `FChaosVDCharacterGroundConstraintSettingsDataWrapper`  
`struct FChaosVDCharacterGroundConstraintSettingsDataWrapper : public FChaosVDWrapperDataBase`  
_L57-89_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L61 _public prototype_ `bool Serialize(FArchive& Ar);`
- L64 _public member_ `FVector VerticalAxis = FVector(ForceInitToZero);` — `UPROPERTY(VisibleAnywhere, Category = Settings)`
- L67 _public member_ `double TargetHeight = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = Settings, meta = (ForceUnits = "cm"))`
- L70 _public member_ `double RadialForceLimit = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = Settings, meta = (ForceUnits = "Newtons"))`
- L73 _public member_ `double FrictionForceLimit = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = Settings, meta = (ForceUnits = "Newtons"))`
- L76 _public member_ `double TwistTorqueLimit = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = Settings, meta = (ForceUnits = "NewtonMeters"))`
- L79 _public member_ `double SwingTorqueLimit = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = Settings, meta = (ForceUnits = "NewtonMeters"))`
- L82 _public member_ `double CosMaxWalkableSlopeAngle = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = Settings)`
- L85 _public member_ `double DampingFactor = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = Settings)`
- L88 _public member_ `double AssumedOnGroundHeight = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = Settings, meta = (ForceUnits = "cm"))`

#### struct `FChaosVDCharacterGroundConstraintDataDataWrapper`  
`struct FChaosVDCharacterGroundConstraintDataDataWrapper : public FChaosVDWrapperDataBase`  
_L93-113_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L97 _public prototype_ `bool Serialize(FArchive& Ar);`
- L100 _public member_ `FVector GroundNormal = FVector(ForceInitToZero);` — `UPROPERTY(VisibleAnywhere, Category = Data)`
- L103 _public member_ `FVector TargetDeltaPosition = FVector(ForceInitToZero);` — `UPROPERTY(VisibleAnywhere, Category = Data, meta = (ForceUnits = "cm"))`
- L106 _public member_ `double TargetDeltaFacing = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = Data, meta = (ForceUnits = "radians"))`
- L109 _public member_ `double GroundDistance = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = Data, meta = (ForceUnits = "cm"))`
- L112 _public member_ `double CosMaxWalkableSlopeAngle = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = Data)`

#### struct `FChaosVDCharacterGroundConstraint`  
`struct FChaosVDCharacterGroundConstraint : public FChaosVDConstraintDataWrapperBase`  
_L118-147_
- reflection: `USTRUCT()`
- inherits: `FChaosVDConstraintDataWrapperBase`
- L123 _public member_ `static FStringView WrapperTypeName;`
- L125 _public prototype_ `bool Serialize(FArchive& Ar);`
- L127 _public member_ `int32 SolverID = INDEX_NONE;`
- L130 _public member_ `int32 ConstraintIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L132 _public member_ `int32 CharacterParticleIndex = INDEX_NONE;`
- L133 _public member_ `int32 GroundParticleIndex = INDEX_NONE;`
- L136 _public member_ `FChaosVDCharacterGroundConstraintStateDataWrapper State;` — `UPROPERTY(VisibleAnywhere, Category=State)`
- L139 _public member_ `FChaosVDCharacterGroundConstraintSettingsDataWrapper Settings;` — `UPROPERTY(VisibleAnywhere, Category=Settings)`
- L142 _public member_ `FChaosVDCharacterGroundConstraintDataDataWrapper Data;` — `UPROPERTY(VisibleAnywhere, Category=Data)`
- L144 _public function_ `virtual int32 GetSolverID() const override`
- L145 _public prototype_ `virtual int32 GetParticleIDAtSlot(EChaosVDParticlePairIndex IndexSlot) const override;`
- L146 _public function_ `virtual int32 GetConstraintIndex () const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define CVD_IMPLEMENT_SERIALIZER(Type) \`

### `Source/Runtime/Experimental/ChaosVisualDebugger/Public/DataWrappers/ChaosVDCollisionDataWrappers.h` (Public)


#### enum `EChaosVDContactShapesType`  
`enum class EChaosVDContactShapesType`  
_L16-43_
- reflection: `UENUM()`
- L18 _public enumerator_ `Unknown`
- L19 _public enumerator_ `SphereSphere`
- L20 _public enumerator_ `SphereCapsule`
- L21 _public enumerator_ `SphereBox`
- L22 _public enumerator_ `SphereConvex`
- L23 _public enumerator_ `SphereTriMesh`
- L24 _public enumerator_ `SphereHeightField`
- L25 _public enumerator_ `SpherePlane`
- L26 _public enumerator_ `CapsuleCapsule`
- L27 _public enumerator_ `CapsuleBox`
- L28 _public enumerator_ `CapsuleConvex`
- L29 _public enumerator_ `CapsuleTriMesh`
- L30 _public enumerator_ `CapsuleHeightField`
- L31 _public enumerator_ `BoxBox`
- L32 _public enumerator_ `BoxConvex`
- L33 _public enumerator_ `BoxTriMesh`
- L34 _public enumerator_ `BoxHeightField`
- L35 _public enumerator_ `BoxPlane`
- L36 _public enumerator_ `ConvexConvex`
- L37 _public enumerator_ `ConvexTriMesh`
- L38 _public enumerator_ `ConvexHeightField`
- L39 _public enumerator_ `GenericConvexConvex`
- L40 _public enumerator_ `LevelSetLevelSet`
- L42 _public enumerator_ `NumShapesTypes`

#### enum `EChaosVDContactPointType`  
`enum class EChaosVDContactPointType : int8`  
_L46-53_
- reflection: `UENUM()`
- L48 _public enumerator_ `Unknown`
- L49 _public enumerator_ `VertexPlane`
- L50 _public enumerator_ `EdgeEdge`
- L51 _public enumerator_ `PlaneVertex`
- L52 _public enumerator_ `VertexVertex`

#### struct `FChaosVDContactPoint`  
`struct FChaosVDContactPoint`  
_L56-81_
- reflection: `USTRUCT()`
- L62 _public member_ `FVector ShapeContactPoints[2] = { FVector(ForceInit), FVector(ForceInit) };` — `UPROPERTY(VisibleAnywhere, Category=Contact)` — Shape-space contact points on the two bodies
- L66 _public member_ `FVector ShapeContactNormal = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category=Contact)` — Shape-space contact normal on the second shape with direction that points away from shape 1
- L70 _public member_ `float Phi = 0.f;` — `UPROPERTY(VisibleAnywhere, Category=Contact)` — Contact separation (negative for overlap)
- L74 _public member_ `int32 FaceIndex = 0;` — `UPROPERTY(VisibleAnywhere, Category=Contact)` — Face index of the shape we hit. Only valid for Heightfield and Trimesh contact points, otherwise INDEX_NONE
- L78 _public member_ `EChaosVDContactPointType ContactType = EChaosVDContactPointType::Unknown;` — `UPROPERTY(VisibleAnywhere, Category=Contact)` — Whether this is a vertex-plane contact, edge-edge contact etc.
- L80 _public prototype_ `bool Serialize(FArchive& Ar);`

#### enum `EChaosVDManifoldPointFlags`  
`enum class EChaosVDManifoldPointFlags : uint8`  
_L86-95_
- reflection: `UENUM()`
- L88 _public enumerator_ `None = 0`
- L89 _public enumerator_ `Disabled = 1 << 0`
- L90 _public enumerator_ `WasRestored = 1 << 1`
- L91 _public enumerator_ `WasReplaced = 1 << 2`
- L92 _public enumerator_ `HasStaticFrictionAnchor = 1 << 3`
- L93 _public enumerator_ `IsValid = 1 << 4`
- L94 _public enumerator_ `InsideStaticFrictionCone = 1 << 5`

#### struct `FChaosVDManifoldPoint`  
`struct FChaosVDManifoldPoint`  
_L99-139_
- reflection: `USTRUCT()`
- L104 _public member_ `uint8 bDisabled:1 = false;` — `UPROPERTY(VisibleAnywhere, Category=ContactData)`
- L106 _public member_ `uint8 bWasRestored:1 = false;` — `UPROPERTY()`
- L108 _public member_ `uint8 bWasReplaced:1 = false;` — `UPROPERTY()`
- L110 _public member_ `uint8 bHasStaticFrictionAnchor:1 = false;` — `UPROPERTY(VisibleAnywhere, Category=ContactData)`
- L113 _public member_ `uint8 bIsValid:1 = false;` — `UPROPERTY()`
- L115 _public member_ `uint8 bInsideStaticFrictionCone:1 = false;` — `UPROPERTY(VisibleAnywhere, Category=ContactData)`
- L118 _public member_ `FVector NetPushOut = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category=ContactData)`
- L120 _public member_ `FVector NetImpulse = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category=ContactData)`
- L123 _public member_ `float TargetPhi = 0.f;` — `UPROPERTY(VisibleAnywhere, Category=ContactData)`
- L125 _public member_ `float InitialPhi = 0.f;` — `UPROPERTY(VisibleAnywhere, Category=ContactData)`
- L127 _public member_ `FVector ShapeAnchorPoints[2] = { FVector(ForceInit), FVector(ForceInit) };` — `UPROPERTY()`
- L129 _public member_ `FVector InitialShapeContactPoints[2] = { FVector(ForceInit), FVector(ForceInit) };` — `UPROPERTY()`
- L131 _public member_ `FChaosVDContactPoint ContactPoint;` — `UPROPERTY(VisibleAnywhere, Category=ContactData)`
- L134 _public member_ `FVector ShapeContactPoints[2] = { FVector(ForceInit), FVector(ForceInit) };` — `UPROPERTY()`
- L136 _public member_ `bool bIsSelectedInEditor = false;`
- L138 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `FChaosVDCollisionMaterial`  
`struct FChaosVDCollisionMaterial`  
_L144-185_
- reflection: `USTRUCT()`
- L149 _public member_ `int32 FaceIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = MaterialData)`
- L152 _public member_ `float MaterialDynamicFriction = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = MaterialData)`
- L155 _public member_ `float MaterialStaticFriction = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = MaterialData)`
- L158 _public member_ `float MaterialRestitution = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = MaterialData)`
- L161 _public member_ `float DynamicFriction = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = MaterialData)`
- L164 _public member_ `float StaticFriction = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = MaterialData)`
- L167 _public member_ `float Restitution = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = MaterialData)`
- L170 _public member_ `float RestitutionThreshold = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = MaterialData)`
- L173 _public member_ `float InvMassScale0 = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = MaterialData)`
- L176 _public member_ `float InvMassScale1 = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = MaterialData)`
- L179 _public member_ `float InvInertiaScale0 = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = MaterialData)`
- L182 _public member_ `float InvInertiaScale1 = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = MaterialData)`
- L184 _public prototype_ `bool Serialize(FArchive& Ar);`

#### enum `EChaosVDConstraintFlags`  
`enum class EChaosVDConstraintFlags : uint16`  
_L190-206_
- reflection: `UENUM()`
- L192 _public enumerator_ `None = 0`
- L193 _public enumerator_ `IsCurrent = 1 << 0`
- L194 _public enumerator_ `Disabled = 1 << 1`
- L195 _public enumerator_ `UseManifold = 1 << 2`
- L196 _public enumerator_ `UseIncrementalManifold = 1 << 3`
- L197 _public enumerator_ `CanRestoreManifold = 1 << 4`
- L198 _public enumerator_ `WasManifoldRestored = 1 << 5`
- L199 _public enumerator_ `IsQuadratic0 = 1 << 6`
- L200 _public enumerator_ `IsQuadratic1 = 1 << 7`
- L201 _public enumerator_ `IsProbe = 1 << 8`
- L202 _public enumerator_ `CCDEnabled = 1 << 9`
- L203 _public enumerator_ `CCDSweepEnabled = 1 << 10`
- L204 _public enumerator_ `ModifierApplied = 1 << 11`
- L205 _public enumerator_ `MaterialSet = 1 << 12`

#### struct `FChaosVDConstraint`  
`struct FChaosVDConstraint`  
_L209-308_
- reflection: `USTRUCT()`
- L213 _public member_ `static FStringView WrapperTypeName;`
- L216 _public member_ `uint8 bIsCurrent:1 = false;` — `UPROPERTY()`
- L218 _public member_ `uint8 bDisabled:1 = false;` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L220 _public member_ `uint8 bUseManifold:1 = false;` — `UPROPERTY()`
- L222 _public member_ `uint8 bUseIncrementalManifold:1 = false;` — `UPROPERTY()`
- L224 _public member_ `uint8 bCanRestoreManifold:1 = false;` — `UPROPERTY()`
- L226 _public member_ `uint8 bWasManifoldRestored:1 = false;` — `UPROPERTY()`
- L228 _public member_ `uint8 bIsQuadratic0:1 = false;` — `UPROPERTY()`
- L230 _public member_ `uint8 bIsQuadratic1:1 = false;` — `UPROPERTY()`
- L232 _public member_ `uint8 bIsProbe:1 = false;` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L234 _public member_ `uint8 bCCDEnabled:1 = false;` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L236 _public member_ `uint8 bCCDSweepEnabled:1 = false;` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L238 _public member_ `uint8 bModifierApplied:1 = false;` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L240 _public member_ `uint8 bMaterialSet:1 = false;` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L243 _public member_ `FChaosVDCollisionMaterial Material;` — `UPROPERTY(VisibleAnywhere, Category = ConstraintData)`
- L246 _public member_ `FVector AccumulatedImpulse = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L249 _public member_ `EChaosVDContactShapesType ShapesType = EChaosVDContactShapesType::Unknown;` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L252 _public member_ `FTransform ShapeWorldTransforms[2] = { FTransform::Identity, FTransform::Identity };` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L255 _public member_ `FTransform ImplicitTransforms[2] = { FTransform::Identity, FTransform::Identity };` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L258 _public member_ `float CullDistance = 0.f;` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L261 _public member_ `TArray<float> CollisionMargins;` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L264 _public member_ `float CollisionTolerance = 0.f;` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L267 _public member_ `int32 ClosestManifoldPointIndex = 0;` — `UPROPERTY()`
- L270 _public member_ `int32 ExpectedNumManifoldPoints = 0;` — `UPROPERTY()`
- L273 _public member_ `FVector LastShapeWorldPositionDelta = FVector(ForceInit);` — `UPROPERTY()`
- L276 _public member_ `FQuat LastShapeWorldRotationDelta = FQuat(ForceInit);` — `UPROPERTY()`
- L279 _public member_ `float Stiffness = 0.f;` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L282 _public member_ `float MinInitialPhi = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = ConstraintData)`
- L285 _public member_ `float InitialOverlapDepenetrationVelocity = -1.f;` — `UPROPERTY(VisibleAnywhere, Category = ConstraintData)`
- L288 _public member_ `float CCDTimeOfImpact = 0.f;` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L291 _public member_ `float CCDEnablePenetration = 0.f;` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L294 _public member_ `float CCDTargetPenetration = 0.f;` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L297 _public member_ `TArray<FChaosVDManifoldPoint> ManifoldPoints;` — `UPROPERTY(VisibleAnywhere, Category=ConstraintData)`
- L300 _public member_ `int32 Particle0Index = INDEX_NONE;` — `UPROPERTY()`
- L302 _public member_ `int32 Particle1Index = INDEX_NONE;` — `UPROPERTY()`
- L305 _public member_ `int32 SolverID = INDEX_NONE;` — `UPROPERTY()`
- L307 _public prototype_ `bool Serialize(FArchive& Ar);`

#### enum `EChaosVDMidPhaseFlags`  
`enum class EChaosVDMidPhaseFlags : uint8`  
_L313-321_
- reflection: `UENUM()`
- L315 _public enumerator_ `None = 0`
- L316 _public enumerator_ `IsActive = 1 << 0`
- L317 _public enumerator_ `IsCCD = 1 << 1`
- L318 _public enumerator_ `IsCCDActive = 1 << 2`
- L319 _public enumerator_ `IsSleeping = 1 << 3`
- L320 _public enumerator_ `IsModified = 1 << 4`

#### enum `EChaosVDMidPhaseType`  
`enum class EChaosVDMidPhaseType : int8`  
_L324-339_
- reflection: `UENUM()`
- L328 _public enumerator_ `Generic` — A general purpose midphase that handle BVHs, Meshes, Unions of Unions, etc in the geometry hierarchy.
- L333 _public enumerator_ `ShapePair` — A midphase optimized for particle pairs with a small number of shapes. Pre-expands the set of potentially colliding shape pairs.
- L336 _public enumerator_ `SphereApproximation` — A midphase used to collide particles as sphere approximations
- L338 _public enumerator_ `Unknown`

#### struct `FChaosVDParticlePairMidPhase`  
`struct FChaosVDParticlePairMidPhase`  
_L342-377_
- reflection: `USTRUCT()`
- L346 _public member_ `static FStringView WrapperTypeName;`
- L349 _public member_ `int32 SolverID = INDEX_NONE;` — `UPROPERTY()`
- L352 _public member_ `EChaosVDMidPhaseType MidPhaseType = EChaosVDMidPhaseType::Unknown;` — `UPROPERTY(VisibleAnywhere, Category=General)`
- L355 _public member_ `uint8 bIsActive:1 = false;` — `UPROPERTY(VisibleAnywhere, Category=Flags)`
- L357 _public member_ `uint8 bIsCCD:1 = false;` — `UPROPERTY(VisibleAnywhere, Category=Flags)`
- L359 _public member_ `uint8 bIsCCDActive:1 = false;` — `UPROPERTY(VisibleAnywhere, Category=Flags)`
- L361 _public member_ `uint8 bIsSleeping:1 = false;` — `UPROPERTY(VisibleAnywhere, Category=Flags)`
- L363 _public member_ `uint8 bIsModified:1 = false;` — `UPROPERTY(VisibleAnywhere, Category=Flags)`
- L366 _public member_ `int32 LastUsedEpoch = 0;` — `UPROPERTY(VisibleAnywhere, Category=Misc)`
- L369 _public member_ `int32 Particle0Idx = 0;` — `UPROPERTY(VisibleAnywhere, Category=Particle)`
- L371 _public member_ `int32 Particle1Idx = 0;` — `UPROPERTY(VisibleAnywhere, Category=Particle)`
- L374 _public member_ `TArray<FChaosVDConstraint> Constraints;` — `UPROPERTY(VisibleAnywhere, Category=Constraints)`
- L376 _public prototype_ `bool Serialize(FArchive& Ar);`

#### enum `EChaosVDCollisionTraceFlag`  
`enum class EChaosVDCollisionTraceFlag`  
_L382-394_
- reflection: `UENUM()`
- L385 _public enumerator_ `UseDefault` — Use project physics settings (DefaultShapeComplexity)
- L387 _public enumerator_ `UseSimpleAndComplex` — Create both simple and complex shapes. Simple shapes are used for regular scene queries and collision tests. Complex shape (per poly) is used for complex scene queries.
- L389 _public enumerator_ `UseSimpleAsComplex` — Create only simple shapes. Use simple shapes for all scene queries and collision tests.
- L391 _public enumerator_ `UseComplexAsSimple` — Create only complex shapes (per poly). Use complex shapes for all scene queries and collision tests. Can be used in simulation for static shapes only (i.e can be collided against but not moved through forces or velocity.)
- L393 _public enumerator_ `MAX`

#### struct `FChaosVDCollisionFilterData`  
`struct UE_DEPRECATED(5.8, "This struct is no longer used.") FChaosVDCollisionFilterData`  
_L397-413_
- reflection: `USTRUCT()`
- L402 _public member_ `uint32 Word0 = 0;` — `UPROPERTY(VisibleAnywhere, Category=CollisionData)`
- L404 _public member_ `uint32 Word1 = 0;` — `UPROPERTY(VisibleAnywhere, Category=CollisionData)`
- L406 _public member_ `uint32 Word2 = 0;` — `UPROPERTY(VisibleAnywhere, Category=CollisionData)`
- L408 _public member_ `uint32 Word3 = 0;` — `UPROPERTY(VisibleAnywhere, Category=CollisionData)`
- L410 _public prototype_ `bool Serialize(FArchive& Ar);`
- L412 _public prototype_ `bool operator==(const FChaosVDCollisionFilterData& Other) const = default;`

#### struct `TTypeTraits`  
`template <> struct TTypeTraits<FChaosVDCollisionFilterData> : public TTypeTraitsBase <FChaosVDCollisionFilterData>`  
_L418-421_
- inherits: `TTypeTraitsBase<FChaosVDCollisionFilterData>`

#### enum `TTypeTraits::(anonymous)`  
`enum`  
_L420-420_

#### struct `FChaosVDCollisionFilterDataV2`  
`struct FChaosVDCollisionFilterDataV2`  
_L426-466_
- L428 _public prototype_ `bool operator==(const FChaosVDCollisionFilterDataV2& Other) const = default;`
- L430 _public prototype_ `bool Serialize(FArchive& Ar);`
- L432 _public prototype_ `UE_INTERNAL uint8 GetMaskFilter() const;`
- L433 _public prototype_ `UE_INTERNAL uint32 GetFlags() const;`
- L434 _public prototype_ `UE_INTERNAL void SetMaskFilterAndFlags(uint32 InMaskFilter, uint32 InFlags);`
- L437 _public prototype_ `UE_INTERNAL void LoadLegacy(const FChaosVDCollisionFilterData& QueryData, const FChaosVDCollisionFilterData& SimData);`
- L440 _public prototype_ `UE_INTERNAL static void ExtractWord3(const uint32 Word3, uint8& OutMaskFilter, uint8& OutChannelIndex, uint32& OutFlags);`
- L442 _public member_ `UE_INTERNAL uint32 OwnerId = 0;`
- L443 _public member_ `UE_INTERNAL uint32 ComponentId = 0;`
- L444 _public member_ `UE_INTERNAL uint64 OverlapMask = 0;`
- L445 _public member_ `UE_INTERNAL uint64 BlockMask = 0;`
- L446 _public member_ `UE_INTERNAL uint64 CollisionChannelMask = 0;`
- L447 _public member_ `UE_INTERNAL uint32 MaskFilterAndFlags = 0;`
- L449 _public member_ `UE_INTERNAL bool bLoadedFromLegacy = false;`
- L450 _public member_ `UE_INTERNAL uint32 LegacySimBlockMask = 0;`
- L451 _public member_ `UE_INTERNAL uint32 LegacySimWord3 = 0;`
- L454 _private member_ `UE_INTERNAL static constexpr uint32 NumFlagsBits = 21;`
- L455 _private member_ `UE_INTERNAL static constexpr uint32 NumCollisionChannelIndexBits = 5;`
- L456 _private member_ `UE_INTERNAL static constexpr uint32 NumMaskFilterBits = 6;`
- L459 _private member_ `UE_INTERNAL static constexpr uint32 CollisionChannelIndexOffset = NumFlagsBits;`
- L460 _private member_ `UE_INTERNAL static constexpr uint32 MaskFilterOffset = CollisionChannelIndexOffset + NumCollisionChannelIndexBits;`
- L462 _private member_ `UE_INTERNAL static constexpr uint32 FlagsMask = ((1 << NumFlagsBits) - 1);`
- L463 _private member_ `UE_INTERNAL static constexpr uint32 CollisionChannelIndexMask = ((1 << NumCollisionChannelIndexBits) - 1) << CollisionChannelIndexOffset;`
- L464 _private member_ `UE_INTERNAL static constexpr uint32 MaskFilterMask = ((1 << NumMaskFilterBits) - 1) << MaskFilterOffset;`

#### enum `EChaosVDCollisionShapeDataFlags`  
`enum class EChaosVDCollisionShapeDataFlags : uint8`  
_L471-477_
- reflection: `UENUM()`
- L473 _public enumerator_ `None = 0`
- L474 _public enumerator_ `SimCollision = 1 << 0`
- L475 _public enumerator_ `QueryCollision = 1 << 1`
- L476 _public enumerator_ `IsProbe = 1 << 2`

#### struct `FChaosVDShapeCollisionData`  
`struct FChaosVDShapeCollisionData`  
_L480-525_
- reflection: `USTRUCT()`
- L485 _public prototype_ `FChaosVDShapeCollisionData() = default;`
- L486 _public prototype_ `FChaosVDShapeCollisionData(const FChaosVDShapeCollisionData&) = default;`
- L487 _public prototype_ `FChaosVDShapeCollisionData(FChaosVDShapeCollisionData&&) = default;`
- L488 _public prototype_ `FChaosVDShapeCollisionData& operator=(const FChaosVDShapeCollisionData&) = default;`
- L489 _public prototype_ `FChaosVDShapeCollisionData& operator=(FChaosVDShapeCollisionData&&) = default;`
- L493 _public member_ `EChaosVDCollisionTraceFlag CollisionTraceType = EChaosVDCollisionTraceFlag::UseDefault;` — `UPROPERTY(VisibleAnywhere, Category=CollisionData)`
- L496 _public member_ `uint8 bSimCollision : 1 = false;` — `UPROPERTY()`
- L498 _public member_ `uint8 bQueryCollision : 1 = false;` — `UPROPERTY()`
- L500 _public member_ `uint8 bIsProbe : 1 = false;` — `UPROPERTY()`
- L506 _public member_ `FChaosVDCollisionFilterData QueryData_DEPRECATED;` — `UE_DEPRECATED(5.8, "QueryData has been deprecated. Use FilterData instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "QueryData has been deprecated"))`
- L510 _public member_ `FChaosVDCollisionFilterData SimData_DEPRECATED;` — `UE_DEPRECATED(5.8, "SimData has been deprecated. Use FilterData instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "SimData has been deprecated"))`
- L514 _public member_ `FChaosVDCollisionFilterDataV2 FilterData;`
- L517 _public member_ `bool bIsComplex = false;` — `UPROPERTY(VisibleAnywhere, Category="CVD Data")`
- L520 _public member_ `bool bIsValid = false;` — `UPROPERTY(VisibleAnywhere, Category="CVD Data")`
- L522 _public prototype_ `bool Serialize(FArchive& Ar);`
- L524 _public prototype_ `bool operator==(const FChaosVDShapeCollisionData& Other) const;`

#### struct `TTypeTraits`  
`template <> struct TTypeTraits<FChaosVDShapeCollisionData> : public TTypeTraitsBase <FChaosVDShapeCollisionData>`  
_L528-531_
- inherits: `TTypeTraitsBase<FChaosVDShapeCollisionData>`

#### enum `TTypeTraits::(anonymous)`  
`enum`  
_L530-530_

#### struct `FChaosVDCollisionChannelInfo`  
`struct FChaosVDCollisionChannelInfo`  
_L539-553_
- reflection: `USTRUCT()`
- desc: Minimum amount of data needed to reconstruct Collision names in CVD based on already serialized flags
- L544 _public member_ `FString DisplayName;` — `UPROPERTY()`
- L547 _public member_ `int32 CollisionChannel = INDEX_NONE;` — `UPROPERTY()`
- L550 _public member_ `bool bIsTraceType = false;` — `UPROPERTY()`
- L552 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `FChaosVDCollisionChannelsInfoContainer`  
`struct FChaosVDCollisionChannelsInfoContainer`  
_L559-584_
- reflection: `USTRUCT()`
- desc: Container for recorded custom collision profile data
- L563 _public member_ `UE_INTERNAL static constexpr int32 MaxSupportedChannels = 64;`
- L566 _public prototype_ `FChaosVDCollisionChannelsInfoContainer() = default;`
- L567 _public prototype_ `FChaosVDCollisionChannelsInfoContainer(const FChaosVDCollisionChannelsInfoContainer&) = default;`
- L568 _public prototype_ `FChaosVDCollisionChannelsInfoContainer(FChaosVDCollisionChannelsInfoContainer&&) = default;`
- L569 _public prototype_ `FChaosVDCollisionChannelsInfoContainer& operator=(const FChaosVDCollisionChannelsInfoContainer&) = default;`
- L570 _public prototype_ `FChaosVDCollisionChannelsInfoContainer& operator=(FChaosVDCollisionChannelsInfoContainer&&) = default;`
- L573 _public member_ `static FStringView WrapperTypeName;`
- L578 _public member_ `FChaosVDCollisionChannelInfo CustomChannelsNames_DEPRECATED[32] = {};` — `UE_DEPRECATED(5.8, "CustomChannelsNames has been deprecated")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "CustomChannelsNames has been deprecated"))`
- L581 _public member_ `UE_INTERNAL TArray<FChaosVDCollisionChannelInfo> CollisionChannelInfos;`
- L583 _public prototype_ `bool Serialize(FArchive& Ar);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`
- L420 _enumerator_ `enum { IsBytewiseComparable = true };` (scope `TTypeTraits::__anon8f96585f0103`)
- L530 _enumerator_ `enum { IsBytewiseComparable = true };` (scope `TTypeTraits::__anon8f96585f0203`)

### `Source/Runtime/Experimental/ChaosVisualDebugger/Public/DataWrappers/ChaosVDDataSerializationMacros.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define CVD_UNPACK_BITFIELD_DATA(Value, PackedBits, EnumFlag) \`
- L11 _macro_ `#define CVD_PACK_BITFIELD_DATA(Value, PackedBits, EnumFlag) \`
- L19 _macro_ `#define CVD_SERIALIZE_STATIC_ARRAY(Archive, Array) \`
- L30 _macro_ `#define CVD_IMPLEMENT_SERIALIZER(Type) \`

### `Source/Runtime/Experimental/ChaosVisualDebugger/Public/DataWrappers/ChaosVDDebugShapeDataWrapper.h` (Public)


#### struct `FChaosVDDebugShapeDataContainer`  
`struct FChaosVDDebugShapeDataContainer`  
_L10-18_
- reflection: `USTRUCT()`
- L14 _public member_ `TArray<TSharedPtr<FChaosVDDebugDrawBoxDataWrapper>> RecordedDebugDrawBoxes;`
- L15 _public member_ `TArray<TSharedPtr<FChaosVDDebugDrawLineDataWrapper>> RecordedDebugDrawLines;`
- L16 _public member_ `TArray<TSharedPtr<FChaosVDDebugDrawSphereDataWrapper>> RecordedDebugDrawSpheres;`
- L17 _public member_ `TArray<TSharedPtr<FChaosVDDebugDrawImplicitObjectDataWrapper>> RecordedDebugDrawImplicitObjects;`

#### struct `FChaosVDMultiSolverDebugShapeDataContainer`  
`struct FChaosVDMultiSolverDebugShapeDataContainer`  
_L21-26_
- reflection: `USTRUCT()`
- L25 _public member_ `TMap<int32, TSharedPtr<FChaosVDDebugShapeDataContainer>> DataBySolverID;`

#### struct `FChaosVDDebugDrawShapeBase`  
`struct FChaosVDDebugDrawShapeBase : public FChaosVDWrapperDataBase`  
_L29-47_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L34 _public member_ `int32 SolverID = INDEX_NONE;` — `UPROPERTY()`
- L37 _public member_ `FName Tag = NAME_None;` — `UPROPERTY()`
- L40 _public member_ `FColor Color = FColor::Blue;` — `UPROPERTY()`
- L43 _public member_ `EChaosVDParticleContext ThreadContext = EChaosVDParticleContext::GameThread;` — `UPROPERTY()`
- L46 _protected prototype_ `void SerializeBase_Internal(FArchive& Ar);`

#### struct `FChaosVDDebugDrawBoxDataWrapper`  
`struct FChaosVDDebugDrawBoxDataWrapper : public FChaosVDDebugDrawShapeBase`  
_L50-60_
- reflection: `USTRUCT()`
- inherits: `FChaosVDDebugDrawShapeBase`
- L54 _public member_ `static FStringView WrapperTypeName;`
- L57 _public member_ `FBox Box = FBox(ForceInitToZero);` — `UPROPERTY()`
- L59 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `FChaosVDDebugDrawSphereDataWrapper`  
`struct FChaosVDDebugDrawSphereDataWrapper : public FChaosVDDebugDrawShapeBase`  
_L65-78_
- reflection: `USTRUCT()`
- inherits: `FChaosVDDebugDrawShapeBase`
- L69 _public member_ `static FStringView WrapperTypeName;`
- L72 _public member_ `FVector Origin = FVector::ZeroVector;` — `UPROPERTY()`
- L75 _public member_ `float Radius = 0.0f;` — `UPROPERTY()`
- L77 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `FChaosVDDebugDrawLineDataWrapper`  
`struct FChaosVDDebugDrawLineDataWrapper : public FChaosVDDebugDrawShapeBase`  
_L83-99_
- reflection: `USTRUCT()`
- inherits: `FChaosVDDebugDrawShapeBase`
- L87 _public member_ `static FStringView WrapperTypeName;`
- L90 _public member_ `FVector StartLocation = FVector::ZeroVector;` — `UPROPERTY()`
- L93 _public member_ `FVector EndLocation = FVector::ZeroVector;` — `UPROPERTY()`
- L96 _public member_ `bool bIsArrow = false;` — `UPROPERTY()`
- L98 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `FChaosVDDebugDrawImplicitObjectDataWrapper`  
`struct FChaosVDDebugDrawImplicitObjectDataWrapper : public FChaosVDDebugDrawShapeBase`  
_L104-115_
- reflection: `USTRUCT()`
- inherits: `FChaosVDDebugDrawShapeBase`
- L108 _public member_ `static FStringView WrapperTypeName;`
- L110 _public member_ `uint32 ImplicitObjectHash = 0;`
- L112 _public member_ `FTransform ParentTransform = FTransform();`
- L114 _public prototype_ `bool Serialize(FArchive& Ar);`

### `Source/Runtime/Experimental/ChaosVisualDebugger/Public/DataWrappers/ChaosVDImplicitObjectDataWrapper.h` (Public)


#### struct `FChaosVDImplicitObjectDataWrapper`  
`template<class SerializableImplicitType, class ArchiveType> struct FChaosVDImplicitObjectDataWrapper`  
_L13-21_
- desc: Data Wrapper for used to Trace Implicit objects @note This should not be templated. But making it so for now so this can live in the ChaosVDRuntime module without referencing Chaos types directly. Once we are close to ship the first version of the tool, this will likely change to the specific types and to the Chaos Module
- L15 _public member_ `inline static FStringView WrapperTypeName = TEXT("FCh`
- L17 _public member_ `uint32 Hash;`
- L18 _public member_ `SerializableImplicitType ImplicitObject;`
- L20 _public prototype_ `bool Serialize(ArchiveType& Ar);`
- L24 _function_ `template <class SerializableImplicitType, class ArchiveType> bool FChaosVDImplicitObjectDataWrapper<SerializableImplicitType, ArchiveType>::Serialize(ArchiveType& Ar)`

### `Source/Runtime/Experimental/ChaosVisualDebugger/Public/DataWrappers/ChaosVDJointDataWrappers.h` (Public)


#### enum `EChaosVDJointReSimType`  
`enum class EChaosVDJointReSimType`  
_L12-18_
- reflection: `UENUM()`
- L15 _public enumerator_ `FullResim = 0` — Fully re-run simulation and keep results (any forces must be applied again)
- L17 _public enumerator_ `ResimAsFollower = 1` — Use previous forces and snap to previous results regardless of variation - used to push other objects away

#### enum `EChaosVDJointSyncType`  
`enum class EChaosVDJointSyncType`  
_L21-27_
- reflection: `UENUM()`
- L24 _public enumerator_ `InSync` — In sync with recorded data
- L26 _public enumerator_ `HardDesync` — Recorded data mismatches, must run collision detection again

#### enum `EChaosVDJointStateFlags`  
`enum class EChaosVDJointStateFlags : uint8`  
_L30-38_
- reflection: `UENUM()`
- L32 _public enumerator_ `None = 0`
- L33 _public enumerator_ `Disabled = 1 << 0`
- L34 _public enumerator_ `Broken = 1 << 1`
- L35 _public enumerator_ `Breaking = 1 << 2`
- L36 _public enumerator_ `DriveTargetChanged = 1 << 3`
- L37 _public enumerator_ `EnabledDuringResim = 1 << 4`

#### enum `EChaosVDGTJointStateFlags`  
`enum class EChaosVDGTJointStateFlags : uint8`  
_L42-49_
- reflection: `UENUM()`
- L44 _public enumerator_ `None = 0`
- L45 _public enumerator_ `IsBreaking = 1 << 0`
- L46 _public enumerator_ `IsBroken = 1 << 1`
- L47 _public enumerator_ `DriveTargetChanged = 1 << 2`
- L48 _public enumerator_ `IsViolating = 1 << 3`

#### struct `FChaosVDJointStateDataWrapper`  
`struct FChaosVDJointStateDataWrapper : public FChaosVDWrapperDataBase`  
_L53-87_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L58 _public prototype_ `bool Serialize(FArchive& Ar);`
- L62 _public member_ `int32 Island = INDEX_NONE;`
- L63 _public member_ `int32 Level = INDEX_NONE;`
- L64 _public member_ `int32 Color = INDEX_NONE;`
- L65 _public member_ `int32 IslandSize = INDEX_NONE;`
- L68 _public member_ `uint8 bDisabled : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`
- L70 _public member_ `uint8 bBroken : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`
- L72 _public member_ `uint8 bBreaking : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`
- L74 _public member_ `uint8 bDriveTargetChanged : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`
- L76 _public member_ `uint8 bEnabledDuringResim : 1 = true;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`
- L79 _public member_ `FVector LinearImpulse = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`
- L81 _public member_ `FVector AngularImpulse = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`
- L83 _public member_ `EChaosVDJointReSimType ResimType = EChaosVDJointReSimType::FullResim;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`
- L85 _public member_ `EChaosVDJointSyncType SyncState = EChaosVDJointSyncType::InSync;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`

#### struct `FChaosVDGTJointStateDataWrapper`  
`struct FChaosVDGTJointStateDataWrapper : public FChaosVDWrapperDataBase`  
_L91-114_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L96 _public prototype_ `bool Serialize(FArchive& Ar);`
- L99 _public member_ `uint8 bIsBreaking : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`
- L101 _public member_ `uint8 bIsBroken : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`
- L103 _public member_ `uint8 bDriveTargetChanged : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`
- L105 _public member_ `uint8 bIsViolating : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`
- L107 _public member_ `FVector Force = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`
- L109 _public member_ `FVector Torque = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`
- L111 _public member_ `float LinearViolation = 0.f;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`
- L113 _public member_ `float AngularViolation = 0.f;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`

#### enum `EChaosVDJointSolverSettingsFlags`  
`enum class EChaosVDJointSolverSettingsFlags : uint16`  
_L118-129_
- reflection: `UENUM()`
- L120 _public enumerator_ `None = 0`
- L122 _public enumerator_ `UseLinearSolver = 1 << 0`
- L123 _public enumerator_ `SortEnabled = 1 << 1`
- L124 _public enumerator_ `SolvePositionLast = 1 << 2`
- L125 _public enumerator_ `UsePositionBasedDrives = 1 << 3`
- L126 _public enumerator_ `EnableTwistLimits = 1 << 4`
- L127 _public enumerator_ `EnableSwingLimits = 1 << 5`
- L128 _public enumerator_ `EnableDrives = 1 << 6`

#### struct `FChaosVDJointSolverSettingsDataWrapper`  
`struct FChaosVDJointSolverSettingsDataWrapper : public FChaosVDWrapperDataBase`  
_L134-208_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L138 _public prototype_ `bool Serialize(FArchive& Ar);`
- L141 _public member_ `double SwingTwistAngleTolerance = 0.0;` — `UPROPERTY(VisibleAnywhere, Category=Tolerances)`
- L143 _public member_ `double PositionTolerance = 0.0;` — `UPROPERTY(VisibleAnywhere, Category=Tolerances)`
- L145 _public member_ `double AngleTolerance = 0.0;` — `UPROPERTY(VisibleAnywhere, Category=Tolerances)`
- L148 _public member_ `double MinParentMassRatio = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="Stability Control")`
- L150 _public member_ `double MaxInertiaRatio = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="Stability Control")`
- L153 _public member_ `double MinSolverStiffness = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="Solver Stiffness")`
- L155 _public member_ `double MaxSolverStiffness = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="Solver Stiffness")`
- L157 _public member_ `int32 NumIterationsAtMaxSolverStiffness = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="Solver Stiffness")`
- L159 _public member_ `int32 NumShockPropagationIterations = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="Solver Stiffness")`
- L162 _public member_ `uint16 bUseLinearSolver : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L164 _public member_ `uint16 bSortEnabled : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L166 _public member_ `uint16 bSolvePositionLast : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L168 _public member_ `uint16 bUsePositionBasedDrives : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L170 _public member_ `uint16 bEnableTwistLimits : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L172 _public member_ `uint16 bEnableSwingLimits : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L174 _public member_ `uint16 bEnableDrives : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L177 _public member_ `double LinearStiffnessOverride = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L179 _public member_ `double TwistStiffnessOverride = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L181 _public member_ `double SwingStiffnessOverride = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L183 _public member_ `double LinearProjectionOverride = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L185 _public member_ `double AngularProjectionOverride = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L187 _public member_ `double ShockPropagationOverride = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L189 _public member_ `double LinearDriveStiffnessOverride = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L191 _public member_ `double LinearDriveDampingOverride = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L193 _public member_ `double AngularDriveStiffnessOverride = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L195 _public member_ `double AngularDriveDampingOverride = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L197 _public member_ `double SoftLinearStiffnessOverride = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L199 _public member_ `double SoftLinearDampingOverride = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L201 _public member_ `double SoftTwistStiffnessOverride = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L203 _public member_ `double SoftTwistDampingOverride = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L205 _public member_ `double SoftSwingStiffnessOverride = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L207 _public member_ `double SoftSwingDampingOverride = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`

#### enum `EChaosVDJointMotionType`  
`enum class EChaosVDJointMotionType : int32`  
_L212-217_
- reflection: `UENUM()`
- L214 _public enumerator_ `Free`
- L215 _public enumerator_ `Limited`
- L216 _public enumerator_ `Locked`

#### enum `EChaosVDJointForceMode`  
`enum class EChaosVDJointForceMode : int32`  
_L220-224_
- reflection: `UENUM()`
- L222 _public enumerator_ `Acceleration`
- L223 _public enumerator_ `Force`

#### enum `EChaosVDPlasticityType`  
`enum class EChaosVDPlasticityType : int32`  
_L227-232_
- reflection: `UENUM()`
- L229 _public enumerator_ `Free`
- L230 _public enumerator_ `Shrink`
- L231 _public enumerator_ `Grow`

#### enum `EChaosVDJointSettingsFlags`  
`enum class EChaosVDJointSettingsFlags : uint32`  
_L235-256_
- reflection: `UENUM()`
- L237 _public enumerator_ `None = 0`
- L238 _public enumerator_ `CollisionEnabled = 1 << 0`
- L239 _public enumerator_ `MassConditioningEnabled = 1 << 1`
- L240 _public enumerator_ `AngularSLerpPositionDriveEnabled = 1 << 2`
- L241 _public enumerator_ `AngularSLerpVelocityDriveEnabled = 1 << 3`
- L242 _public enumerator_ `AngularTwistPositionDriveEnabled = 1 << 4`
- L243 _public enumerator_ `AngularTwistVelocityDriveEnabled = 1 << 5`
- L244 _public enumerator_ `AngularSwingPositionDriveEnabled = 1 << 6`
- L245 _public enumerator_ `AngularSwingVelocityDriveEnabled = 1 << 7`
- L246 _public enumerator_ `SoftLinearLimitsEnabled = 1 << 8`
- L247 _public enumerator_ `SoftTwistLimitsEnabled = 1 << 9`
- L248 _public enumerator_ `SoftSwingLimitsEnabled = 1 << 10`
- L249 _public enumerator_ `LinearPositionDriveEnabled0 = 1 << 11`
- L250 _public enumerator_ `LinearPositionDriveEnable1 = 1 << 12`
- L251 _public enumerator_ `LinearPositionDriveEnable2 = 1 << 13`
- L252 _public enumerator_ `LinearVelocityDriveEnabled0 = 1 << 14`
- L253 _public enumerator_ `LinearVelocityDriveEnabled1 = 1 << 15`
- L254 _public enumerator_ `LinearVelocityDriveEnabled2 = 1 << 16`
- L255 _public enumerator_ `UseLinearSolver = 1 << 17`

#### struct `FChaosVDJointSettingsDataWrapper`  
`struct FChaosVDJointSettingsDataWrapper : public FChaosVDWrapperDataBase`  
_L259-399_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L264 _public prototype_ `bool Serialize(FArchive& Ar);`
- L267 _public member_ `FTransform ConnectorTransforms[2];` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L269 _public member_ `double Stiffness = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L271 _public member_ `double LinearProjection = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L273 _public member_ `double AngularProjection = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L275 _public member_ `double ShockPropagation = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L277 _public member_ `double TeleportDistance = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L279 _public member_ `double TeleportAngle = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L281 _public member_ `double ParentInvMassScale = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L284 _public member_ `uint16 bCollisionEnabled : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L286 _public member_ `uint16 bMassConditioningEnabled : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L288 _public member_ `uint16 bUseLinearSolver : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L290 _public member_ `uint16 bSoftLinearLimitsEnabled : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L292 _public member_ `uint16 bSoftTwistLimitsEnabled : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L294 _public member_ `uint16 bSoftSwingLimitsEnabled : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L296 _public member_ `uint16 bAngularSLerpPositionDriveEnabled : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L298 _public member_ `uint16 bAngularSLerpVelocityDriveEnabled : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L300 _public member_ `uint16 bAngularTwistPositionDriveEnabled : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L302 _public member_ `uint16 bAngularTwistVelocityDriveEnabled : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L304 _public member_ `uint16 bAngularSwingPositionDriveEnabled : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L306 _public member_ `uint16 bAngularSwingVelocityDriveEnabled : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L309 _public member_ `EChaosVDJointMotionType LinearMotionTypes[3] = { EChaosVDJointMotionType::Free, EChaosVDJointMotionType::Free, EChaosVDJointMotionType::Free };` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L311 _public member_ `double LinearLimit = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L313 _public member_ `EChaosVDJointMotionType AngularMotionTypes[3] = { EChaosVDJointMotionType::Free, EChaosVDJointMotionType::Free, EChaosVDJointMotionType::Free };` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L315 _public member_ `FVector AngularLimits = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L318 _public member_ `EChaosVDJointForceMode LinearSoftForceMode = EChaosVDJointForceMode::Acceleration;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L320 _public member_ `EChaosVDJointForceMode AngularSoftForceMode = EChaosVDJointForceMode::Acceleration;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L322 _public member_ `double SoftLinearStiffness = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L324 _public member_ `double SoftLinearDamping = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L326 _public member_ `double SoftTwistStiffness = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L328 _public member_ `double SoftTwistDamping = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L330 _public member_ `double SoftSwingStiffness = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L332 _public member_ `double SoftSwingDamping = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L334 _public member_ `double LinearRestitution = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L336 _public member_ `double TwistRestitution = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L338 _public member_ `double SwingRestitution = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L341 _public member_ `double LinearContactDistance = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L343 _public member_ `double TwistContactDistance = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L345 _public member_ `double SwingContactDistance = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L348 _public member_ `FVector LinearDrivePositionTarget = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L350 _public member_ `FVector LinearDriveVelocityTarget = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L353 _public member_ `uint8 bLinearPositionDriveEnabled0 : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L355 _public member_ `uint8 bLinearPositionDriveEnabled1 : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L357 _public member_ `uint8 bLinearPositionDriveEnabled2 : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L359 _public member_ `uint8 bLinearVelocityDriveEnabled0 : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L361 _public member_ `uint8 bLinearVelocityDriveEnabled1 : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L363 _public member_ `uint8 bLinearVelocityDriveEnabled2 : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L366 _public member_ `EChaosVDJointForceMode LinearDriveForceMode = EChaosVDJointForceMode::Acceleration;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L368 _public member_ `FVector LinearDriveStiffness = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L370 _public member_ `FVector LinearDriveDamping = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L372 _public member_ `FVector LinearDriveMaxForce = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L374 _public member_ `FQuat AngularDrivePositionTarget = FQuat::Identity;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L376 _public member_ `FVector AngularDriveVelocityTarget = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L378 _public member_ `EChaosVDJointForceMode AngularDriveForceMode = EChaosVDJointForceMode::Acceleration;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L380 _public member_ `FVector AngularDriveStiffness = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L382 _public member_ `FVector AngularDriveDamping = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L384 _public member_ `FVector AngularDriveMaxTorque = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L386 _public member_ `double LinearBreakForce = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L388 _public member_ `double LinearPlasticityLimit = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L390 _public member_ `EChaosVDPlasticityType LinearPlasticityType = EChaosVDPlasticityType::Free;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L392 _public member_ `double LinearPlasticityInitialDistanceSquared = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L394 _public member_ `double AngularBreakTorque = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L396 _public member_ `double AngularPlasticityLimit = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L398 _public member_ `double ContactTransferScale = 0.0;` — `UPROPERTY(VisibleAnywhere, Category="General")`

#### struct `FChaosVDJointConstraint`  
`struct FChaosVDJointConstraint : public FChaosVDConstraintDataWrapperBase`  
_L404-431_
- reflection: `USTRUCT()`
- inherits: `FChaosVDConstraintDataWrapperBase`
- L408 _public member_ `static FStringView WrapperTypeName;`
- L410 _public prototype_ `bool Serialize(FArchive& Ar);`
- L412 _public member_ `int32 SolverID = INDEX_NONE;`
- L415 _public member_ `int32 ConstraintIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="General")`
- L417 _public member_ `int32 ParticleParIndexes[2] = { INDEX_NONE, INDEX_NONE };`
- L420 _public member_ `FChaosVDJointStateDataWrapper PhysicsThreadJointState;` — `UPROPERTY(VisibleAnywhere, Category=JointState)`
- L423 _public member_ `FChaosVDGTJointStateDataWrapper GameThreadJointState;` — `UPROPERTY()`
- L426 _public member_ `FChaosVDJointSettingsDataWrapper JointSettings;` — `UPROPERTY(VisibleAnywhere, Category=JointSettings)`
- L428 _public function_ `virtual int32 GetSolverID() const override`
- L429 _public function_ `virtual int32 GetParticleIDAtSlot(EChaosVDParticlePairIndex IndexSlot) const override`
- L430 _public function_ `virtual int32 GetConstraintIndex () const override`

### `Source/Runtime/Experimental/ChaosVisualDebugger/Public/DataWrappers/ChaosVDParticleDataWrapper.h` (Public)


#### enum `EChaosVDParticleType`  
`enum class EChaosVDParticleType : uint8`  
_L13-23_
- reflection: `UENUM()`
- L15 _public enumerator_ `Static`
- L16 _public enumerator_ `Kinematic`
- L17 _public enumerator_ `Rigid`
- L18 _public enumerator_ `Clustered`
- L19 _public enumerator_ `StaticMesh`
- L20 _public enumerator_ `SkeletalMesh`
- L21 _public enumerator_ `GeometryCollection`
- L22 _public enumerator_ `Unknown`

#### enum `EChaosVDSleepType`  
`enum class EChaosVDSleepType : uint8`  
_L26-30_
- reflection: `UENUM()`
- L28 _public enumerator_ `MaterialSleep`
- L29 _public enumerator_ `NeverSleep`

#### enum `EChaosVDObjectStateType`  
`enum class EChaosVDObjectStateType: int8`  
_L33-42_
- reflection: `UENUM()`
- L35 _public enumerator_ `Uninitialized = 0`
- L36 _public enumerator_ `Sleeping = 1`
- L37 _public enumerator_ `Kinematic = 2`
- L38 _public enumerator_ `Static = 3`
- L39 _public enumerator_ `Dynamic = 4`
- L41 _public enumerator_ `Count`

#### struct `FChaosVDParticleMetadata`  
`struct FChaosVDParticleMetadata`  
_L45-71_
- reflection: `USTRUCT()`
- L49 _public member_ `static FStringView WrapperTypeName;`
- L52 _public member_ `FName OwnerName;` — `UPROPERTY(VisibleAnywhere, Category=ParticleName)`
- L54 _public member_ `FName ComponentName;` — `UPROPERTY(VisibleAnywhere, Category=ParticleName)`
- L56 _public member_ `FName BoneName;` — `UPROPERTY(VisibleAnywhere, Category=ParticleName)`
- L58 _public member_ `int32 Index = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category=ParticleName)`
- L61 _public member_ `FTopLevelAssetPath MapAssetPath;` — `UPROPERTY(VisibleAnywhere, Category=ParticleAssetData)`
- L63 _public member_ `FTopLevelAssetPath OwnerAssetPath;` — `UPROPERTY(VisibleAnywhere, Category=ParticleAssetData)`
- L66 _public member_ `uint64 MetadataID = 0;` — `UPROPERTY()`
- L68 _public prototype_ `bool Serialize(FArchive& Ar);`
- L70 _public prototype_ `FString ToString() const;`

#### struct `FChaosVDWrapperDataBase`  
`struct FChaosVDWrapperDataBase`  
_L75-87_
- reflection: `USTRUCT()`
- desc: Base struct that declares the interface to be used for any ParticleData Viewer
- L78 _public prototype_ `virtual ~FChaosVDWrapperDataBase() = default;`
- L80 _public function_ `virtual bool HasValidData() const`
- L82 _public function_ `void MarkAsValid()`
- L86 _protected member_ `bool bHasValidData = false;` — `UPROPERTY()`

#### enum `EChaosVDParticlePairIndex`  
`enum class EChaosVDParticlePairIndex : uint8`  
_L89-93_
- L91 _public enumerator_ `Index_0`
- L92 _public enumerator_ `Index_1`

#### struct `FChaosVDConstraintDataWrapperBase`  
`struct FChaosVDConstraintDataWrapperBase : public FChaosVDWrapperDataBase`  
_L97-105_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- desc: Base struct that declares the interface to be used for any Constraint data to be visualized
- L100 _public prototype_ `virtual ~FChaosVDConstraintDataWrapperBase() override = default;`
- L102 _public function_ `virtual int32 GetSolverID() const`
- L103 _public function_ `virtual int32 GetParticleIDAtSlot (EChaosVDParticlePairIndex IndexSlot) const`
- L104 _public function_ `virtual int32 GetConstraintIndex () const`

#### struct `FChaosVDFRigidParticleControlFlags`  
`struct FChaosVDFRigidParticleControlFlags : public FChaosVDWrapperDataBase`  
_L108-171_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L112 _public function_ `FChaosVDFRigidParticleControlFlags() : bGravityEnabled(false), bCCDEnabled(false), bOneWayInteractionEnabled(false), bInertiaConditioningEnabled(false), GravityGroupIndex(0), bMACDEnabled(false), bPartialIslandSleepAllowed(true), bGyroscopicTorqueEnabled(false)`
- L124 _public prototype_ `bool Serialize(FArchive& Ar);`
- L127 _public function_ `template <typename TOther> void CopyFrom(const TOther& Other)`
- L142 _public function_ `template <typename TOther> void CopyTo(TOther& Other) const`
- L156 _public member_ `bool bGravityEnabled;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Control Flags")`
- L158 _public member_ `bool bCCDEnabled;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Control Flags")`
- L160 _public member_ `bool bOneWayInteractionEnabled;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Control Flags")`
- L162 _public member_ `bool bInertiaConditioningEnabled;` — `UPROPERTY(VisibleAnywhere, Category = "Particle Control Flags")`
- L164 _public member_ `int32 GravityGroupIndex;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Control Flags")`
- L166 _public member_ `bool bMACDEnabled;` — `UPROPERTY(VisibleAnywhere, Category = "Particle Control Flags")`
- L168 _public member_ `bool bPartialIslandSleepAllowed;` — `UPROPERTY(VisibleAnywhere, Category = "Particle Control Flags")`
- L170 _public member_ `bool bGyroscopicTorqueEnabled;` — `UPROPERTY(VisibleAnywhere, Category = "Particle Control Flags")`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosVDFRigidParticleControlFlags> : public TStructOpsTypeTraitsBase2<FChaosVDFRigidParticleControlFlags>`  
_L176-182_
- inherits: `TStructOpsTypeTraitsBase2<FChaosVDFRigidParticleControlFlags>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L179-181_

#### struct `FChaosVDParticlePositionRotation`  
`struct FChaosVDParticlePositionRotation : public FChaosVDWrapperDataBase`  
_L188-242_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- desc: Simplified UStruct version of FParticlePositionRotation. Used to be able to show the values in the editor and allow changes via the Property Editor.
- L192 _public function_ `FChaosVDParticlePositionRotation()`
- L203 _public function_ `template <typename OtherType, EAccessorType AccessorType> void CopyFrom(const OtherType& Other)`
- L221 _public function_ `template <typename OtherType, EAccessorType AccessorType> void CopyTo(OtherType& Other) const`
- L235 _public prototype_ `bool Serialize(FArchive& Ar);`
- L238 _public member_ `FVector MX = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category= "Particle Velocities")`
- L241 _public member_ `FQuat MR = FQuat(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category= "Particle Velocities")`

#### enum `FChaosVDParticlePositionRotation::EAccessorType`  
`enum class EAccessorType`  
_L196-200_
- L198 _public enumerator_ `PQ`
- L199 _public enumerator_ `XR`

#### struct `FChaosVDParticleVelocities`  
`struct FChaosVDParticleVelocities : public FChaosVDWrapperDataBase`  
_L250-280_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- desc: Simplified UStruct version of FParticleVelocities. Used to be able to show the values in the editor and allow changes via the Property Editor.
- L254 _public function_ `FChaosVDParticleVelocities()`
- L258 _public prototype_ `bool Serialize(FArchive& Ar);`
- L261 _public function_ `template <typename TOther> void CopyFrom(const TOther& Other)`
- L269 _public function_ `template <typename TOther> void CopyTo(TOther& Other) const`
- L276 _public member_ `FVector MV = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category= "Particle Velocities")`
- L279 _public member_ `FVector MW = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category= "Particle Velocities")`

#### struct `FChaosVDParticleBounds`  
`struct FChaosVDParticleBounds : public FChaosVDWrapperDataBase`  
_L285-314_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L289 _public function_ `FChaosVDParticleBounds()`
- L293 _public prototype_ `bool Serialize(FArchive& Ar);`
- L296 _public function_ `template <typename TOther> void CopyFrom(const TOther& Other)`
- L304 _public function_ `template <typename TOther> void CopyTo(TOther& Other) const`
- L310 _public member_ `FVector MMin = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category = "Particle Bounds Min")`
- L313 _public member_ `FVector MMax = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category = "Particle Bounds Max")`

#### struct `FChaosVDParticleDynamics`  
`struct FChaosVDParticleDynamics : public FChaosVDWrapperDataBase`  
_L322-363_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- desc: Simplified UStruct version of FParticleDynamics. Used to be able to show the values in the editor and allow changes via the Property Editor.
- L326 _public function_ `FChaosVDParticleDynamics()`
- L330 _public prototype_ `bool Serialize(FArchive& Ar);`
- L333 _public function_ `template <typename TOther> void CopyFrom(TOther& Other)`
- L344 _public function_ `template <typename TOther> void CopyTo(TOther& Other) const`
- L353 _public member_ `FVector MAcceleration = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category= "Particle Dynamics")`
- L356 _public member_ `FVector MAngularAcceleration = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category= "Particle Dynamics")`
- L359 _public member_ `FVector MLinearImpulseVelocity = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category= "Particle Dynamics")`
- L362 _public member_ `FVector MAngularImpulseVelocity = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category= "Particle Dynamics")`

#### struct `FChaosVDParticleMassProps`  
`struct FChaosVDParticleMassProps : public FChaosVDWrapperDataBase`  
_L371-422_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- desc: Simplified UStruct version of FParticleMassProps. Used to be able to show the values in the editor and allow changes via the Property Editor.
- L375 _public function_ `FChaosVDParticleMassProps(): MM(0), MInvM(0)`
- L379 _public prototype_ `bool Serialize(FArchive& Ar);`
- L382 _public function_ `template <typename TOther> void CopyFrom(const TOther& Other)`
- L395 _public function_ `template <typename TOther> void CopyTo(TOther& Other) const`
- L406 _public member_ `FVector MCenterOfMass = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category= "Particle Mass Props")`
- L409 _public member_ `FQuat MRotationOfMass = FQuat(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category= "Particle Mass Props")`
- L412 _public member_ `FVector MI = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category= "Particle Mass Props")`
- L415 _public member_ `FVector MInvI = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category= "Particle Mass Props")`
- L418 _public member_ `double MM = 0.0;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Mass Props")`
- L421 _public member_ `double MInvM = 0.0;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Mass Props")`

#### struct `FChaosVDParticleDynamicMisc`  
`struct FChaosVDParticleDynamicMisc : public FChaosVDWrapperDataBase`  
_L430-535_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- desc: Simplified UStruct version of FParticleDynamicMisc. Used to be able to show the values in the editor and allow changes via the Property Editor.
- L434 _public function_ `FChaosVDParticleDynamicMisc(): MLinearEtherDrag(0), MAngularEtherDrag(0), MMaxLinearSpeedSq(0), MMaxAngularSpeedSq(0), MInitialOverlapDepenetrationVelocity(0), MSleepThresholdMultiplier(1), MCollisionGroup(0), MObjectState(), MSleepType(), bDisabled(false), PositionSolverIterationCount(INDEX_NONE), VelocitySolverIterationCount(INDEX_NONE), ProjectionSolverIterationCount(INDEX_NONE)`
- L439 _public prototype_ `bool Serialize(FArchive& Ar);`
- L442 _public function_ `template <typename TOther> void CopyFrom(const TOther& Other)`
- L467 _public function_ `template <typename OtherType, typename ControlFlagsType, typename SleepStateType> void CopyWithoutStateTo(OtherType& Other) const`
- L492 _public member_ `double MLinearEtherDrag;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Dynamic Misc")`
- L495 _public member_ `double MAngularEtherDrag;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Dynamic Misc")`
- L498 _public member_ `double MMaxLinearSpeedSq;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Dynamic Misc")`
- L501 _public member_ `double MMaxAngularSpeedSq;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Dynamic Misc")`
- L504 _public member_ `float MInitialOverlapDepenetrationVelocity;` — `UPROPERTY(VisibleAnywhere, Category = "Particle Dynamic Misc")`
- L507 _public member_ `float MSleepThresholdMultiplier;` — `UPROPERTY(VisibleAnywhere, Category = "Particle Dynamic Misc")`
- L510 _public member_ `int32 MCollisionGroup;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Dynamic Misc")`
- L513 _public member_ `EChaosVDObjectStateType MObjectState;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Dynamic Misc")`
- L516 _public member_ `EChaosVDSleepType MSleepType;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Dynamic Misc")`
- L519 _public member_ `uint32 MCollisionConstraintFlag = 0;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Dynamic Misc")`
- L522 _public member_ `FChaosVDFRigidParticleControlFlags MControlFlags;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Dynamic Misc")`
- L525 _public member_ `bool bDisabled;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Dynamic Misc")`
- L528 _public member_ `int8 PositionSolverIterationCount;` — `UPROPERTY(VisibleAnywhere, Category = "Particle Control Flags")`
- L531 _public member_ `int8 VelocitySolverIterationCount;` — `UPROPERTY(VisibleAnywhere, Category = "Particle Control Flags")`
- L534 _public member_ `int8 ProjectionSolverIterationCount;` — `UPROPERTY(VisibleAnywhere, Category = "Particle Control Flags")`

#### struct `FChaosVDConnectivityEdge`  
`struct FChaosVDConnectivityEdge`  
_L541-558_
- reflection: `USTRUCT()`
- desc: Represents the data of a connectivity Edge that CVD can use to reconstruct it during playback
- L546 _public member_ `int32 SiblingParticleID = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category=ConnectivityEdge)`
- L549 _public member_ `float Strain = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category=ConnectivityEdge)`
- L551 _public function_ `bool Serialize(FArchive& Ar)`

#### struct `FChaosVDParticleCluster`  
`struct FChaosVDParticleCluster : public FChaosVDWrapperDataBase`  
_L566-650_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- desc: Structure contained data from a Clustered Particle. Used to be able to show the values in the editor and allow changes via the Property Editor.
- L570 _public function_ `FChaosVDParticleCluster()`
- L574 _public prototype_ `bool Serialize(FArchive& Ar);`
- L577 _public function_ `template <typename TOther> void CopyFrom(const TOther& Other)`
- L607 _public function_ `template <typename TOther> void CopyTo(TOther& Other) const`
- L613 _public member_ `int32 ParentParticleID = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Cluster")`
- L616 _public member_ `int32 NumChildren = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Cluster | Cluster Id")`
- L619 _public member_ `FTransform ChildToParent;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Cluster")`
- L622 _public member_ `int32 ClusterGroupIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Cluster")`
- L625 _public member_ `bool bInternalCluster = false;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Cluster")`
- L628 _public member_ `float CollisionImpulse = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Cluster")`
- L631 _public member_ `float ExternalStrains = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Cluster")`
- L634 _public member_ `float InternalStrains = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Cluster")`
- L637 _public member_ `float Strain = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Cluster")`
- L640 _public member_ `TArray<FChaosVDConnectivityEdge> ConnectivityEdges;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Cluster")`
- L643 _public member_ `bool bIsAnchored = false;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Cluster")`
- L646 _public member_ `bool bUnbreakable = false;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Cluster")`
- L649 _public member_ `bool bIsChildToParentLocked = false;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Cluster")`

#### enum `EChaosVDParticleContext`  
`enum class EChaosVDParticleContext`  
_L655-660_
- reflection: `UENUM()`
- L657 _public enumerator_ `Invalid`
- L658 _public enumerator_ `GameThread`
- L659 _public enumerator_ `PhysicsThread`

#### enum `EChaosVDKinematicTargetMode`  
`enum class EChaosVDKinematicTargetMode`  
_L663-669_
- reflection: `UENUM()`
- L665 _public enumerator_ `None`
- L666 _public enumerator_ `Reset` — None,			  Particle does not move and no data is changed
- L667 _public enumerator_ `Position` — Reset,			  Particle does not move, velocity and angular velocity are zeroed, then mode is set to "None".
- L668 _public enumerator_ `Velocity` — Position,		  Particle is moved to Kinematic Target transform, velocity and angular velocity updated to reflect the change, then mode is set to "Reset".

#### struct `FChaosVDKinematicTarget`  
`struct FChaosVDKinematicTarget : public FChaosVDWrapperDataBase`  
_L672-707_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L676 _public prototype_ `bool Serialize(FArchive& Ar);`
- L679 _public function_ `template <typename OtherType> void CopyFrom(const OtherType& Other)`
- L693 _public function_ `template <typename OtherType, class ModeType> void CopyTo(OtherType& Other) const`
- L700 _public member_ `FQuat Rotation = FQuat(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category= "Kinematic Target")`
- L703 _public member_ `FVector Position = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category= "Kinematic Target")`
- L706 _public member_ `EChaosVDKinematicTargetMode Mode = EChaosVDKinematicTargetMode::None;` — `UPROPERTY(VisibleAnywhere, Category= "Kinematic Target")`

#### struct `FChaosVDVSmooth`  
`struct FChaosVDVSmooth : public FChaosVDWrapperDataBase`  
_L712-738_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L716 _public prototype_ `bool Serialize(FArchive& Ar);`
- L719 _public function_ `template <typename OtherType> void CopyFrom(const OtherType& Other)`
- L728 _public function_ `template <typename OtherType> void CopyTo(OtherType& Other) const`
- L735 _public member_ `FVector MV = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category= "VSmooth")`
- L737 _public member_ `FVector MW = FVector(ForceInit);` — `UPROPERTY(VisibleAnywhere, Category= "VSmooth")`

#### struct `FChaosVDParticleDataWrapper`  
`struct FChaosVDParticleDataWrapper : public FChaosVDWrapperDataBase`  
_L746-846_
- reflection: `USTRUCT(DisplayName="Particle Data")`
- inherits: `FChaosVDWrapperDataBase`
- desc: Simplified UStruct version of FChaosVDParticleDataWrapper. Used to be able to show the values in the editor and allow changes via the Property Editor.
- L750 _public prototype_ `FChaosVDParticleDataWrapper(const FChaosVDParticleDataWrapper& Other) = default;`
- L751 _public prototype_ `FChaosVDParticleDataWrapper(FChaosVDParticleDataWrapper&& Other) noexcept = default;`
- L752 _public prototype_ `FChaosVDParticleDataWrapper& operator=(const FChaosVDParticleDataWrapper& Other) = default;`
- L753 _public prototype_ `FChaosVDParticleDataWrapper& operator=(FChaosVDParticleDataWrapper&& Other) noexcept = default;`
- L754 _public prototype_ `virtual ~FChaosVDParticleDataWrapper() override = default;`
- L755 _public function_ `FChaosVDParticleDataWrapper()`
- L761 _public member_ `static FStringView WrapperTypeName;`
- L766 _public member_ `int32 DirtyFlagsBits = 0;` — `UPROPERTY()`
- L769 _public member_ `EChaosVDParticleContext ParticleContext = EChaosVDParticleContext::Invalid;` — `UPROPERTY()`
- L772 _public member_ `uint32 GeometryHash = 0;` — `UPROPERTY(VisibleAnywhere, Category= "General")`
- L780 _public member_ `FString DebugName;` — `UPROPERTY(VisibleAnywhere, Category= "General", DisplayName="Legacy Debug Name")` — Shows the serialized debug name of the particle. This is only valid in CVD recordings from UE 5.6 and earlier. Particles Debug name now is part of the particle metadata
- L786 _public member_ `bool bHasDebugName = false;` — `UE_DEPRECATED(5.7, "Please Use the HasLegacyDebugName accessor. This property is no longer in use")` — Serialized boolean used as a flag to know if a particle has the legacy debug name serialized as part of the particle data. If false, it means the particle either had no debug name at the time of being traced or it is using the new particle metadata system
- L790 _public member_ `uint64 MetadataId = 0;` — `UPROPERTY()`
- L793 _public member_ `int32 ParticleIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category= "General")`
- L796 _public member_ `int32 SolverID = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category= "General")`
- L799 _public member_ `EChaosVDParticleType Type = EChaosVDParticleType::Unknown;` — `UPROPERTY(VisibleAnywhere, Category= "General")`
- L802 _public member_ `FChaosVDParticlePositionRotation ParticlePositionRotation;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Position Rotation")`
- L805 _public member_ `FChaosVDParticleVelocities ParticleVelocities;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Velocities")`
- L808 _public member_ `FChaosVDParticleBounds ParticleInflatedBounds;` — `UPROPERTY(VisibleAnywhere, Category = "Particle Inflated Bounds")`
- L811 _public member_ `FChaosVDKinematicTarget ParticleKinematicTarget;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Kinematic Target")`
- L814 _public member_ `FChaosVDVSmooth ParticleVWSmooth;` — `UPROPERTY(VisibleAnywhere, Category= "Particle V/W Smooth")`
- L817 _public member_ `FChaosVDParticleDynamics ParticleDynamics;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Dynamics")`
- L820 _public member_ `FChaosVDParticleDynamicMisc ParticleDynamicsMisc;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Dynamics Misc")`
- L823 _public member_ `FChaosVDParticleMassProps ParticleMassProps;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Mass Props")`
- L826 _public member_ `FChaosVDParticleCluster ParticleCluster;` — `UPROPERTY(VisibleAnywhere, Category= "Particle Cluster Data")`
- L829 _public member_ `TArray<FChaosVDShapeCollisionData> CollisionDataPerShape;` — `UPROPERTY()`
- L831 _public prototype_ `bool HasLegacyDebugName() const;`
- L832 _public prototype_ `FString GetDebugName() const;`
- L833 _public prototype_ `void SetMetadataInstance(const TSharedPtr<FChaosVDParticleMetadata>& InMetadataInstance);`
- L834 _public prototype_ `const TSharedPtr<FChaosVDParticleMetadata>& GetMetadataInstance() const;`
- L836 _public function_ `virtual bool HasValidData() const override`
- L841 _public prototype_ `bool Serialize(FArchive& Ar);`
- L845 _private member_ `TSharedPtr<FChaosVDParticleMetadata> ParticleMetadataInstance;` — Debug Name instance

#### Free symbols / members of external scopes

- L180 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anoneb6ec8540103`)

### `Source/Runtime/Experimental/ChaosVisualDebugger/Public/DataWrappers/ChaosVDQueryDataWrappers.h` (Public)


#### enum `EChaosVDSceneQueryType`  
`enum class EChaosVDSceneQueryType`  
_L10-16_
- reflection: `UENUM()`
- L12 _public enumerator_ `Invalid`
- L13 _public enumerator_ `Sweep`
- L14 _public enumerator_ `Overlap`
- L15 _public enumerator_ `RayCast`

#### enum `EChaosVDSceneQueryMode`  
`enum class EChaosVDSceneQueryMode`  
_L19-25_
- reflection: `UENUM()`
- L21 _public enumerator_ `Single`
- L22 _public enumerator_ `Multi`
- L23 _public enumerator_ `Test`
- L24 _public enumerator_ `Invalid`

#### struct `FChaosVDCollisionResponseParams`  
`struct FChaosVDCollisionResponseParams : public FChaosVDWrapperDataBase`  
_L28-47_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L32 _public prototype_ `bool Serialize(FArchive& Ar);`
- L35 _public function_ `template <typename TOther> void CopyFrom(const TOther& Other)`
- L46 _public member_ `TArray<uint8, TInlineAllocator<32>> FlagsPerChannel;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosVDCollisionResponseParams> : public TStructOpsTypeTraitsBase2<FChaosVDCollisionResponseParams>`  
_L56-62_
- inherits: `TStructOpsTypeTraitsBase2<FChaosVDCollisionResponseParams>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L59-61_

#### struct `FChaosVDCollisionObjectQueryParams`  
`struct FChaosVDCollisionObjectQueryParams : public FChaosVDWrapperDataBase`  
_L65-99_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L70 _public prototype_ `FChaosVDCollisionObjectQueryParams() = default;`
- L71 _public prototype_ `FChaosVDCollisionObjectQueryParams(const FChaosVDCollisionObjectQueryParams&) = default;`
- L72 _public prototype_ `FChaosVDCollisionObjectQueryParams(FChaosVDCollisionObjectQueryParams&&) = default;`
- L73 _public prototype_ `FChaosVDCollisionObjectQueryParams& operator=(const FChaosVDCollisionObjectQueryParams&) = default;`
- L74 _public prototype_ `FChaosVDCollisionObjectQueryParams& operator=(FChaosVDCollisionObjectQueryParams&&) = default;`
- L77 _public prototype_ `bool Serialize(FArchive& Ar);`
- L80 _public function_ `template <typename TOther> void CopyFrom(const TOther& Other)`
- L92 _public member_ `uint8 ObjectTypesToQuery_DEPRECATED = 0;` — `UE_DEPRECATED(5.8, "ObjectTypesToQuery has been deprecated")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "ObjectTypesToQuery has been deprecated"))`
- L95 _public member_ `UE_INTERNAL uint64 ObjectTypesToQuery64 = 0;`
- L98 _public member_ `uint8 IgnoreMask = 0;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosVDCollisionObjectQueryParams> : public TStructOpsTypeTraitsBase2<FChaosVDCollisionObjectQueryParams>`  
_L108-114_
- inherits: `TStructOpsTypeTraitsBase2<FChaosVDCollisionObjectQueryParams>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L111-113_

#### enum `EChaosVDCollisionQueryParamsFlags`  
`enum class EChaosVDCollisionQueryParamsFlags : uint16`  
_L117-138_
- reflection: `UENUM()`
- L119 _public enumerator_ `None = 0`
- L121 _public enumerator_ `TraceComplex = 1 << 0` — Whether we should trace against complex collision
- L123 _public enumerator_ `FindInitialOverlaps = 1 << 1` — Whether we want to find out initial overlap or not. If true, it will return if this was initial overlap.
- L125 _public enumerator_ `ReturnFaceIndex = 1 << 2` — Whether we want to return the triangle face index for complex static mesh traces
- L127 _public enumerator_ `ReturnPhysicalMaterial = 1 << 3` — Whether we want to include the physical material in the results.
- L129 _public enumerator_ `IgnoreBlocks = 1 << 4` — Whether to ignore blocking results.
- L131 _public enumerator_ `IgnoreTouches = 1 << 5` — Whether to ignore touch/overlap results.
- L133 _public enumerator_ `SkipNarrowPhase = 1 << 6` — Whether to skip narrow phase checks (only for overlaps).
- L135 _public enumerator_ `TraceIntoSubComponents = 1 << 7` — Whether to ignore traces to the cluster union and trace against its children instead.
- L137 _public enumerator_ `ReplaceHitWithSubComponents = 1 << 8` — Extra filtering done on the query. See declaration for filtering logic

#### struct `FChaosVDCollisionQueryParams`  
`struct FChaosVDCollisionQueryParams : public FChaosVDWrapperDataBase`  
_L143-225_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L147 _public prototype_ `bool Serialize(FArchive& Ar);`
- L150 _public function_ `template <typename TOther> void CopyFrom(const TOther& Other)`
- L170 _public member_ `FName TraceTag;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)` — Tag used to provide extra information or filtering for debugging of the trace (e.g. Collision Analyzer)
- L174 _public member_ `FName OwnerTag;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)` — Tag used to indicate an owner for this trace
- L178 _public member_ `uint16 bTraceComplex : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)` — Whether we should trace against complex collision
- L182 _public member_ `uint16 bFindInitialOverlaps : 1= false;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)` — Whether we want to find out initial overlap or not. If true, it will return if this was initial overlap.
- L186 _public member_ `uint16 bReturnFaceIndex : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)` — Whether we want to return the triangle face index for complex static mesh traces
- L190 _public member_ `uint16 bReturnPhysicalMaterial : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)` — Whether we want to include the physical material in the results.
- L194 _public member_ `uint16 bIgnoreBlocks : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)` — Whether to ignore blocking results.
- L198 _public member_ `uint16 bIgnoreTouches : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)` — Whether to ignore touch/overlap results.
- L202 _public member_ `uint16 bSkipNarrowPhase : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)` — Whether to skip narrow phase checks (only for overlaps).
- L206 _public member_ `uint16 bTraceIntoSubComponents : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)` — Whether to ignore traces to the cluster union and trace against its children instead.
- L210 _public member_ `uint16 bReplaceHitWithSubComponents : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)` — If bTraceIntoSubComponents is true, whether to replace the hit of the cluster union with its children instead.
- L214 _public member_ `uint8 IgnoreMask = 0;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)` — Extra filtering done on the query. See declaration for filtering logic
- L216 _public member_ `TArray<uint32> IgnoredComponentsIDs;`
- L218 _public member_ `TArray<uint32> IgnoredActorsIDs;`
- L221 _public member_ `TArray<FName> IgnoredActorsNames;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)`
- L224 _public member_ `TArray<FName> IgnoredComponentsNames;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosVDCollisionQueryParams> : public TStructOpsTypeTraitsBase2<FChaosVDCollisionQueryParams>`  
_L234-240_
- inherits: `TStructOpsTypeTraitsBase2<FChaosVDCollisionQueryParams>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L237-239_

#### enum `EChaosVDQueryFastDataParallelFlags`  
`enum class EChaosVDQueryFastDataParallelFlags : uint8`  
_L243-249_
- reflection: `UENUM()`
- L245 _public enumerator_ `None = 0`
- L246 _public enumerator_ `Parallel0 = 1 << 0`
- L247 _public enumerator_ `Parallel1 = 1 << 1`
- L248 _public enumerator_ `Parallel2 = 1 << 2`

#### struct `FChaosVDQueryFastData`  
`struct FChaosVDQueryFastData : public FChaosVDWrapperDataBase`  
_L252-278_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L256 _public prototype_ `bool Serialize(FArchive& Ar);`
- L259 _public member_ `FVector Dir = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category=QueryFastData)`
- L262 _public member_ `FVector InvDir = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category=QueryFastData)`
- L265 _public member_ `double CurrentLength = 0.0;` — `UPROPERTY(VisibleAnywhere, Category=QueryFastData)`
- L268 _public member_ `double InvCurrentLength = 0.0;` — `UPROPERTY(VisibleAnywhere, Category=QueryFastData)`
- L271 _public member_ `uint8 bParallel0 : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=QueryFastData)`
- L274 _public member_ `uint8 bParallel1 : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=QueryFastData)`
- L277 _public member_ `uint8 bParallel2 : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category=QueryFastData)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosVDQueryFastData> : public TStructOpsTypeTraitsBase2<FChaosVDQueryFastData>`  
_L287-293_
- inherits: `TStructOpsTypeTraitsBase2<FChaosVDQueryFastData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L290-292_

#### enum `EChaosVDSQHitFlags`  
`enum class EChaosVDSQHitFlags : uint16`  
_L297-306_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Possible results from a scene query
- L299 _public enumerator_ `None = 0`
- L300 _public enumerator_ `Position = 1 << 0`
- L301 _public enumerator_ `Normal = 1 << 1`
- L302 _public enumerator_ `Distance = 1 << 2`
- L303 _public enumerator_ `UV = 1 << 3`
- L304 _public enumerator_ `MTD = 1 << 9`
- L305 _public enumerator_ `FaceIndex = 1 << 10`

#### struct `FChaosVDQueryHitData`  
`struct FChaosVDQueryHitData : public FChaosVDWrapperDataBase`  
_L311-335_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L315 _public prototype_ `bool Serialize(FArchive& Ar);`
- L318 _public member_ `float Distance = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)`
- L321 _public member_ `int32 FaceIdx = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)`
- L324 _public member_ `uint16 Flags = 0;` — `UPROPERTY(VisibleAnywhere, Category=QueryData, meta = (Bitmask, BitmaskEnum = "/Script/ChaosVDRuntime.EChaosVDSQHitFlags"))`
- L327 _public member_ `FVector WorldPosition = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)`
- L330 _public member_ `FVector WorldNormal = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)`
- L334 _public member_ `FVector FaceNormal = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)` — This is not used for Line Traces

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosVDQueryHitData> : public TStructOpsTypeTraitsBase2<FChaosVDQueryHitData>`  
_L344-350_
- inherits: `TStructOpsTypeTraitsBase2<FChaosVDQueryHitData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L347-349_

#### enum `EChaosVDCollisionQueryHitType`  
`enum class EChaosVDCollisionQueryHitType`  
_L353-358_
- reflection: `UENUM()`
- L355 _public enumerator_ `None = 0`
- L356 _public enumerator_ `Touch = 1`
- L357 _public enumerator_ `Block = 2`

#### enum `EChaosVDSQVisitRejectReason`  
`enum class EChaosVDSQVisitRejectReason`  
_L361-369_
- reflection: `UENUM()`
- L363 _public enumerator_ `None = 0`
- L364 _public enumerator_ `NoHit = 1`
- L365 _public enumerator_ `PreFilter = 2`
- L366 _public enumerator_ `PostFilter = 3`
- L367 _public enumerator_ `ColocatedHitHasWorseNormal = 4`
- L368 _public enumerator_ `FailedFastBoundTest = 5`

#### enum `EChaosVDSceneQueryVisitorType`  
`enum class EChaosVDSceneQueryVisitorType`  
_L372-377_
- reflection: `UENUM()`
- L374 _public enumerator_ `Invalid`
- L375 _public enumerator_ `BroadPhase`
- L376 _public enumerator_ `NarrowPhase`

#### struct `FChaosVDQueryVisitStep`  
`struct FChaosVDQueryVisitStep : public FChaosVDWrapperDataBase`  
_L380-418_
- reflection: `USTRUCT()`
- inherits: `FChaosVDWrapperDataBase`
- L384 _public member_ `static FStringView WrapperTypeName;`
- L386 _public prototype_ `bool Serialize(FArchive& Ar);`
- L388 _public member_ `int32 OwningQueryID = INDEX_NONE;`
- L391 _public member_ `EChaosVDSceneQueryVisitorType Type = EChaosVDSceneQueryVisitorType::Invalid;` — `UPROPERTY(VisibleAnywhere, Category="SQ Visit Data")`
- L394 _public member_ `uint32 ShapeIndex = 0;` — `UPROPERTY(VisibleAnywhere, Category="SQ Visit Data")`
- L397 _public member_ `int32 ParticleIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="SQ Visit Data")`
- L400 _public member_ `FTransform ParticleTransform;` — `UPROPERTY(VisibleAnywhere, Category="SQ Visit Data")`
- L403 _public member_ `FChaosVDQueryFastData QueryFastData;` — `UPROPERTY(VisibleAnywhere, Category="SQ Visit Data")`
- L406 _public member_ `EChaosVDCollisionQueryHitType HitType = EChaosVDCollisionQueryHitType::None;` — `UPROPERTY(VisibleAnywhere, Category="SQ Visit Data")`
- L409 _public member_ `FChaosVDQueryHitData HitData;` — `UPROPERTY(VisibleAnywhere, Category="SQ Visit Data")`
- L412 _public member_ `EChaosVDSQVisitRejectReason RejectReason = EChaosVDSQVisitRejectReason::None;` — `UPROPERTY(VisibleAnywhere, Category="SQ Visit Data")`
- L417 _public member_ `int32 SolverID_Editor = INDEX_NONE;` — Cached solver id property populated and used during playback of an already loaded file . This should not be serialized

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosVDQueryVisitStep> : public TStructOpsTypeTraitsBase2<FChaosVDQueryVisitStep>`  
_L427-433_
- inherits: `TStructOpsTypeTraitsBase2<FChaosVDQueryVisitStep>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L430-432_

#### struct `FChaosVDQueryDataWrapper`  
`struct FChaosVDQueryDataWrapper`  
_L436-493_
- reflection: `USTRUCT()`
- L440 _public member_ `static FStringView WrapperTypeName;`
- L442 _public prototype_ `bool Serialize(FArchive& Ar);`
- L445 _public member_ `int32 ID = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="CVD QueryData")`
- L448 _public member_ `int32 ParentQueryID = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="CVD QueryData")`
- L451 _public member_ `int32 WorldSolverID = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="CVD QueryData")`
- L454 _public member_ `bool bIsRetryQuery = false;` — `UPROPERTY(VisibleAnywhere, Category=RecordedQueryData)`
- L456 _public member_ `uint32 InputGeometryKey = 0;`
- L459 _public member_ `FQuat GeometryOrientation = FQuat::Identity;` — `UPROPERTY(VisibleAnywhere, Category=RecordedQueryData)`
- L462 _public member_ `EChaosVDSceneQueryType Type = EChaosVDSceneQueryType::Invalid;` — `UPROPERTY(VisibleAnywhere, Category=RecordedQueryData)`
- L465 _public member_ `EChaosVDSceneQueryMode Mode = EChaosVDSceneQueryMode::Invalid;` — `UPROPERTY(VisibleAnywhere, Category=RecordedQueryData)`
- L468 _public member_ `FVector StartLocation = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category=RecordedQueryData)`
- L471 _public member_ `FVector EndLocation = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category=RecordedQueryData)`
- L474 _public member_ `int32 CollisionChannel = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category=RecordedQueryData)`
- L477 _public member_ `FChaosVDCollisionQueryParams CollisionQueryParams;` — `UPROPERTY(VisibleAnywhere, Category=RecordedQueryData)`
- L480 _public member_ `FChaosVDCollisionResponseParams CollisionResponseParams;` — `UPROPERTY(VisibleAnywhere, Category=RecordedQueryData)`
- L483 _public member_ `FChaosVDCollisionObjectQueryParams CollisionObjectQueryParams;` — `UPROPERTY(VisibleAnywhere, Category=RecordedQueryData)`
- L485 _public member_ `TArray<FChaosVDQueryVisitStep> SQVisitData;`
- L488 _public member_ `TArray<FChaosVDQueryVisitStep> Hits;` — `UPROPERTY(VisibleAnywhere, Category=QueryData)`
- L490 _public member_ `TArray<int32> SubQueriesIDs;`
- L492 _public member_ `int32 CurrentVisitIndex = 0;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosVDQueryDataWrapper> : public TStructOpsTypeTraitsBase2<FChaosVDQueryDataWrapper>`  
_L502-508_
- inherits: `TStructOpsTypeTraitsBase2<FChaosVDQueryDataWrapper>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L505-507_

#### struct `FChaosVDSceneQueriesDataContainer`  
`struct FChaosVDSceneQueriesDataContainer`  
_L511-518_
- reflection: `USTRUCT()`
- L515 _public member_ `TMap<int32, TMap<int32, TSharedPtr<FChaosVDQueryDataWrapper>>> RecordedSceneQueriesBySolverID;`
- L517 _public member_ `TMap<int32, TSharedPtr<FChaosVDQueryDataWrapper>> RecordedSceneQueriesByQueryID;`

#### Free symbols / members of external scopes

- L49 _function_ `inline FArchive& operator<<(FArchive& Ar, FChaosVDCollisionResponseParams& Data)`
- L60 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonb85e80490103`)
- L101 _function_ `inline FArchive& operator<<(FArchive& Ar, FChaosVDCollisionObjectQueryParams& Data)`
- L112 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonb85e80490203`)
- L227 _function_ `inline FArchive& operator<<(FArchive& Ar, FChaosVDCollisionQueryParams& Data)`
- L238 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonb85e80490303`)
- L280 _function_ `inline FArchive& operator<<(FArchive& Ar, FChaosVDQueryFastData& Data)`
- L291 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonb85e80490403`)
- L337 _function_ `inline FArchive& operator<<(FArchive& Ar, FChaosVDQueryHitData& Data)`
- L348 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonb85e80490503`)
- L420 _function_ `inline FArchive& operator<<(FArchive& Ar, FChaosVDQueryVisitStep& Data)`
- L431 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonb85e80490603`)
- L495 _function_ `inline FArchive& operator<<(FArchive& Ar, FChaosVDQueryDataWrapper& Data)`
- L506 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonb85e80490703`)

### `Source/Runtime/Experimental/ChaosVisualDebugger/Public/Trace/RelayTraceWriter.h` (Public)


#### class `Chaos::VD::FRelayTraceWriter`  
`class UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FRelayTraceDataWriter directly instead.") FRelayTraceWriter : public UE::TraceBasedDebuggers::FRelayTraceDataWriter`  
_L20-25_
- inherits: `UE::TraceBasedDebuggers::FRelayTraceDataWriter`
- L23 _public prototype_ `FRelayTraceWriter();`
- L24 _public prototype_ `~FRelayTraceWriter();`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Chaos`
- L18 _namespace_ `namespace VD` (scope `Chaos`)
