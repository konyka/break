# Plugins / OpenXRAR

- module root: `Plugins/Runtime/OpenXR/Source/OpenXRAR`
- headers: 2; symbols: 174
- symbol kinds: class=4, delegate=2, enum=1, enumerator=4, function=33, member=40, prototype=84, struct=6
- PrivateDependencyModuleNames: ApplicationCore, AugmentedReality, CoreUObject, HeadMountedDisplay, OpenXRHMD, Projects, RHI, RenderCore, UnrealEd, XRBase
- PublicDependencyModuleNames: Core, Engine, MRMesh
- PublicIncludePathModuleNames: OpenXR

### `Plugins/Runtime/OpenXR/Source/OpenXRAR/Private/OpenXRAR.h` (Private)


#### class `FOpenXRARSystem`  
`class FOpenXRARSystem : public FARSystemSupportBase, public IOpenXRARTrackedMeshHolder, public IOpenXRARTrackedGeometryHolder, public FGCObject, public TSharedFromThis<FOpenXRARSystem, ESPMode::ThreadSafe>`  
_L21-297_
- inherits: `FARSystemSupportBase,IOpenXRARTrackedMeshHolder,IOpenXRARTrackedGeometryHolder,FGCObject,TSharedFromThis<FOpenXRARSystem,ESPMode::ThreadSafe>`
- L56 _public prototype_ `FOpenXRARSystem();`
- L57 _public prototype_ `virtual ~FOpenXRARSystem();`
- L59 _public prototype_ `void SetTrackingSystem(IXRTrackingSystem& InTrackingSystem);`
- L62 _public function_ `virtual void OnARSystemInitialized()` — Invoked after the base AR system has been initialized.
- L64 _public prototype_ `virtual bool OnStartARGameFrame(FWorldContext& WorldContext);`
- L67 _public function_ `virtual EARTrackingQuality OnGetTrackingQuality() const` — @return the tracking quality; if unable to determine tracking quality, return EARTrackingQuality::NotAvailable
- L70 _public function_ `virtual EARTrackingQualityReason OnGetTrackingQualityReason() const` — @return the reason of limited tracking quality; if the state is not limited, return EARTrackingQualityReason::None
- L79 _public prototype_ `virtual void OnStartARSession(UARSessionConfig* SessionConfig);` — Start the AR system. @param SessionType The type of AR session to create @return true if the system was successfully started
- L82 _public prototype_ `virtual void OnPauseARSession();` — Stop the AR system but leave its internal state intact.
- L85 _public prototype_ `virtual void OnStopARSession();` — Stop the AR system and reset its internal state; this task must succeed.
- L88 _public prototype_ `virtual FARSessionStatus OnGetARSessionStatus() const;` — @return the info about whether the session is running normally or encountered some kind of error.
- L91 _public prototype_ `virtual bool IsARAvailable() const;` — Returns true/false based on whether AR features are available
- L99 _public prototype_ `virtual void OnSetAlignmentTransform(const FTransform& InAlignmentTransform);` — Set a transform that will align the Tracking Space origin to the World Space origin. This is useful for supporting static geometry and static lighting in AR. Note: Usually, an app will ask the user to select an appropriate location for some experience. This allows us to choose an appropriate alignment transform.
- L107 _public prototype_ `virtual TArray<FARTraceResult> OnLineTraceTrackedObjects(const FVector2D ScreenCoord, EARLineTraceChannels TraceChannels);` — Trace all the tracked geometries and determine which have been hit by a ray cast from `ScreenCoord`. Only geometries specified in `TraceChannels` are considered. @return a list of all the geometries that were hit, sorted by distance
- L109 _public prototype_ `virtual TArray<FARTraceResult> OnLineTraceTrackedObjects(const FVector Start, const FVector End, EARLineTraceChannels TraceChannels);`
- L112 _public prototype_ `virtual TArray<UARTrackedGeometry*> OnGetAllTrackedGeometries() const;` — @return a TArray of all the tracked geometries known to your ar system
- L115 _public prototype_ `virtual TArray<UARPin*> OnGetAllPins() const;` — @return a TArray of all the pins that attach components to TrackedGeometries
- L118 _public prototype_ `virtual bool OnIsTrackingTypeSupported(EARSessionType SessionType) const;` — @return whether the specified tracking type is supported by this device
- L121 _public function_ `virtual UARLightEstimate* OnGetCurrentLightEstimate() const` — @return the best available light estimate; nullptr if light estimation is inactive or not available
- L126 _public prototype_ `virtual UARPin* FindARPinByComponent(const USceneComponent* Component) const;` — Given a scene component find the ARPin which it is pinned by, if any.
- L133 _public prototype_ `virtual UARPin* OnPinComponent(USceneComponent* ComponentToPin, const FTransform& PinToWorldTransform, UARTrackedGeometry* TrackedGeometry = nullptr, const FName DebugName = NAME_None);` — Pin an Unreal Component to a location in the world. Optionally, associate with a TrackedGeometry to receive transform updates that effectively attach the component to the geometry. @return the UARPin object that is pinning the component to the world and (optionally) a TrackedGeometry
- L139 _public prototype_ `virtual void OnRemovePin(UARPin* PinToRemove);` — Given a pin, remove it and stop updating the associated component based on the tracked geometry. The component in question will continue to track with the world, but will not get updates specific to a TrackedGeometry.
- L142 _public function_ `virtual bool OnAddManualEnvironmentCaptureProbe(FVector Location, FVector Extent)` — Tells the ARSystem to generate a capture probe at the specified location if supported
- L145 _public function_ `virtual TSharedPtr<FARGetCandidateObjectAsyncTask, ESPMode::ThreadSafe> OnGetCandidateObject(FVector Location, FVector Extent) const` — Generates a UARCandidateObject from the point cloud data within the location and its extent using an async task
- L148 _public function_ `virtual TSharedPtr<FARSaveWorldAsyncTask, ESPMode::ThreadSafe> OnSaveWorld() const` — Saves the AR world to a byte array using an async task
- L151 _public function_ `virtual EARWorldMappingState OnGetWorldMappingStatus() const` — @return the current mapping status
- L154 _public function_ `virtual TArray<FARVideoFormat> OnGetSupportedVideoFormats(EARSessionType SessionType) const` — @return The list of supported video formats for this device and session type
- L157 _public function_ `virtual TArray<FVector> OnGetPointCloud() const` — @return the current point cloud data for the ar scene
- L160 _public function_ `virtual bool OnAddRuntimeCandidateImage(UARSessionConfig* InSessionConfig, UTexture2D* CandidateTexture, FString FriendlyName, float PhysicalWidth)` — Add candidate image at runtime @return True if it added the iamge successfully
- L162 _public function_ `virtual void* GetARSessionRawPointer()`
- L163 _public function_ `virtual void* GetGameThreadARFrameRawPointer()`
- L166 _public function_ `virtual bool OnIsSessionTrackingFeatureSupported(EARSessionType SessionType, EARSessionTrackingFeature SessionTrackingFeature) const` — @return if a particular session feature is supported on this device
- L169 _public function_ `virtual TArray<FARPose2D> OnGetTracked2DPose() const` — @return all the tracked 2D poses in AR
- L172 _public function_ `virtual bool OnIsSceneReconstructionSupported(EARSessionType SessionType, EARSceneReconstruction SceneReconstructionMethod) const` — @return the required scene construction method is supported
- L174 _public function_ `virtual bool OnAddTrackedPointWithName(const FTransform& WorldTransform, const FString& PointName, bool bDeletePointsWithSameName)`
- L177 _public function_ `virtual int32 OnGetNumberOfTrackedFacesSupported() const` — @return the max number of faces can be tracked at the same time
- L180 _public prototype_ `virtual UARTexture* OnGetARTexture(EARTextureType TextureType) const;` — @return the AR texture for the specified type
- L182 _public prototype_ `virtual bool OnToggleARCapture(const bool bOnOff, const EARCaptureType CaptureType) override;`
- L183 _public prototype_ `virtual bool OnGetCameraIntrinsics(FARCameraIntrinsics& OutCameraIntrinsics) const override;`
- L189 _public prototype_ `virtual bool IsLocalPinSaveSupported() const;`
- L191 _public prototype_ `virtual bool ArePinsReadyToLoad();`
- L193 _public prototype_ `virtual void LoadARPins(TMap<FName, UARPin*>& LoadedPins);`
- L195 _public prototype_ `virtual bool SaveARPin(FName InName, UARPin* InPin);`
- L197 _public prototype_ `virtual void RemoveSavedARPin(FName InName);`
- L199 _public prototype_ `virtual void RemoveAllSavedARPins();`
- L207 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector);` — Pure virtual that must be overloaded by the inheriting class. Use this method to serialize any UObjects contained that you wish to keep around. @param Collector The collector of referenced objects.
- L208 _public function_ `virtual FString GetReferencerName() const override`
- L214 _private member_ `IXRTrackingSystem* TrackingSystem = nullptr;`
- L215 _private member_ `IOpenXRHMD* OpenXRHMD = nullptr;`
- L217 _private member_ `class IOpenXRCustomAnchorSupport* CustomAnchorSupport = nullptr;`
- L219 _private member_ `FARSessionStatus SessionStatus;`
- L221 _private prototype_ `void UpdateAnchors();`
- L222 _private prototype_ `void ClearAnchors();`
- L227 _private member_ `TObjectPtr<UARSessionConfig> SessionConfig = nullptr;` — PROPERTIES REPORTED TO FGCObject ...
- L228 _private member_ `TArray<TObjectPtr<UARPin>> Pins;`
- L229 _private member_ `TMap<FGuid, FTrackedGeometryGroup> TrackedGeometryGroups;`
- L236 _private prototype_ `virtual void StartMeshUpdates();` — IOpenXRARTrackedMeshHolder
- L237 _private prototype_ `virtual FOpenXRMeshUpdate* AllocateMeshUpdate(FGuid InGuidMeshUpdate);`
- L238 _private prototype_ `virtual void RemoveMesh(FGuid InGuidMeshUpdate);`
- L239 _private prototype_ `virtual FOpenXRPlaneUpdate* AllocatePlaneUpdate(FGuid InGuidPlaneUpdate);`
- L240 _private prototype_ `virtual void RemovePlane(FGuid InGuidPlaneUpdate);`
- L241 _private prototype_ `virtual void EndMeshUpdates();`
- L242 _private prototype_ `virtual void ObjectUpdated(FOpenXRARTrackedGeometryData* InUpdate);`
- L243 _private prototype_ `virtual void ObjectUpdated(TSharedPtr<FOpenXRARTrackedGeometryData> InUpdate);`
- L245 _private prototype_ `void RemoveMesh_GameThread(FGuid InGuidMeshUpdate);`
- L246 _private prototype_ `void ProcessMeshUpdates_GameThread();`
- L247 _private prototype_ `void AddOrUpdateMesh_GameThread(FOpenXRMeshUpdate* CurrentMesh);`
- L248 _private prototype_ `void ProcessSUPlaneUpdates_GameThread();`
- L249 _private prototype_ `void AddOrUpdatePlane_GameThread(FOpenXRPlaneUpdate* CurrentPlane);`
- L250 _private prototype_ `void OnSpawnARActor(AARActor* NewARActor, UARComponent* NewARComponent, FGuid NativeID);`
- L251 _private prototype_ `void OnObjectUpdated_GameThread(TSharedPtr<FOpenXRARTrackedGeometryData> InUpdate);`
- L254 _private prototype_ `void ClearTrackedGeometries();` — Removes all tracked geometries, marking them as not tracked and sending the delegate event
- L257 _private member_ `FCriticalSection CurrentUpdateSync;` — Used to lock access to the update list that will be queued for the game thread
- L259 _private member_ `FMeshUpdateSet* CurrentUpdate;` — This pointer is locked until the list construction is complete, where this gets queued for game thread processing
- L261 _private member_ `FCriticalSection MeshUpdateListSync;` — Controls the access to the queue of mesh updates for the game thread to process
- L263 _private member_ `TArray<FMeshUpdateSet*> MeshUpdateList;` — List of mesh updates for the game thread to process
- L265 _private member_ `TSet<FGuid> LastKnownMeshes;` — Holds the set of last known meshes so we can detect removed meshes. Only touched on the game thread
- L267 _private member_ `FPlaneUpdateSet* SUCurrentPlaneUpdate;` — This pointer is locked until the list construction is complete, where this gets queued for game thread processing
- L269 _private member_ `FCriticalSection SUPlaneUpdateListSync;` — Controls the access to the queue of plane updates for the game thread to process
- L271 _private member_ `TArray<FPlaneUpdateSet*> SUPlaneUpdateList;` — List of plane updates for the game thread to process
- L274 _private member_ `FDelegateHandle SpawnARActorDelegateHandle;` — for networked callbacks
- L278 _private prototype_ `virtual void ARTrackedGeometryAdded(FOpenXRARTrackedGeometryData* InData);` — IOpenXRARTrackedGeometryHolder
- L279 _private prototype_ `virtual void ARTrackedGeometryUpdated(FOpenXRARTrackedGeometryData* InData);`
- L280 _private prototype_ `virtual void ARTrackedGeometryRemoved(FOpenXRARTrackedGeometryData* InData);`
- L282 _private prototype_ `virtual void ARTrackedGeometryAdded(TSharedPtr<FOpenXRARTrackedGeometryData> InData);`
- L283 _private prototype_ `virtual void ARTrackedGeometryUpdated(TSharedPtr<FOpenXRARTrackedGeometryData> InData);`
- L284 _private prototype_ `virtual void ARTrackedGeometryRemoved(TSharedPtr<FOpenXRARTrackedGeometryData> InData);`
- L286 _private prototype_ `void ARTrackedGeometryAdded_GameThread(TSharedPtr<FOpenXRARTrackedGeometryData> InData);`
- L287 _private prototype_ `void ARTrackedGeometryUpdated_GameThread(TSharedPtr<FOpenXRARTrackedGeometryData> InData);`
- L288 _private prototype_ `void ARTrackedGeometryRemoved_GameThread(TSharedPtr<FOpenXRARTrackedGeometryData> InData);`
- L290 _private member_ `class IOpenXRCustomCaptureSupport* QRCapture = nullptr;`
- L291 _private member_ `class IOpenXRCustomCaptureSupport* CamCapture = nullptr;`
- L292 _private member_ `class IOpenXRCustomCaptureSupport* SpatialMappingCapture = nullptr;`
- L293 _private member_ `class IOpenXRCustomCaptureSupport* SceneUnderstandingCapture = nullptr;`
- L294 _private member_ `class IOpenXRCustomCaptureSupport* HandMeshCapture = nullptr;`
- L296 _private member_ `TArray<IOpenXRCustomCaptureSupport*> CustomCaptureSupports;`

#### struct `FOpenXRARSystem::FMeshUpdateSet`  
`struct FMeshUpdateSet`  
_L30-41_
- desc: A set of updates to be processed at once
- L32 _public function_ `FMeshUpdateSet()`
- L35 _public function_ `~FMeshUpdateSet()`
- L40 _public member_ `TMap<FGuid, FOpenXRMeshUpdate*> GuidToMeshUpdateList;`

#### struct `FOpenXRARSystem::FPlaneUpdateSet`  
`struct FPlaneUpdateSet`  
_L43-54_
- L45 _public function_ `FPlaneUpdateSet()`
- L48 _public function_ `~FPlaneUpdateSet()`
- L53 _public member_ `TMap<FGuid, FOpenXRPlaneUpdate*> GuidToPlaneUpdateList;`

#### class `OpenXRARModuleImpl`  
`class OpenXRARModuleImpl : public IOpenXRARModule`  
_L300-319_
- inherits: `IOpenXRARModule`
- L305 _public prototype_ `virtual IARSystemSupport* CreateARSystem();` — Used to init our AR system
- L306 _public prototype_ `virtual void SetTrackingSystem(IXRTrackingSystem& InTrackingSystem);`
- L308 _public prototype_ `virtual void StartupModule() override;`
- L310 _public prototype_ `virtual void ShutdownModule() override;`
- L312 _public prototype_ `virtual bool GetExtensions(TArray<const ANSICHAR*>& OutExtensions) override;`
- L314 _public prototype_ `virtual class IOpenXRARTrackedMeshHolder * GetTrackedMeshHolder() override;`
- L318 _private member_ `TSharedPtr<FOpenXRARSystem, ESPMode::ThreadSafe> ARSystem;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_STATS_GROUP(TEXT("OpenXRAR"), STATGROUP_OPENXRAR, STATCAT_Ad`
- L321 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenXRAR, Log, All);`
- L321 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenXRAR, Log, All);`

### `Plugins/Runtime/OpenXR/Source/OpenXRAR/Public/IOpenXRARTrackedGeometryHolder.h` (Public)


#### class `IOpenXRARTrackedGeometryHolder`  
`class IOpenXRARTrackedGeometryHolder : public IModularFeature`  
_L8-30_
- inherits: `IModularFeature`
- L11 _public function_ `static FName GetModularFeatureName()`
- L17 _public function_ `virtual ~IOpenXRARTrackedGeometryHolder()`
- L21 _public prototype_ `virtual void ARTrackedGeometryAdded(struct FOpenXRARTrackedGeometryData* InData) = 0;` — `UE_DEPRECATED(4.27, "Use overload with SharedPtr instead.")` — @todo: deprecation - since existing third party plugins already out there use this interface, we'll need to revisit the deprecations. Disabling for now to avoid CIS errors.
- L23 _public prototype_ `virtual void ARTrackedGeometryUpdated(struct FOpenXRARTrackedGeometryData* InData) = 0;` — `UE_DEPRECATED(4.27, "Use overload with SharedPtr instead.")`
- L25 _public prototype_ `virtual void ARTrackedGeometryRemoved(struct FOpenXRARTrackedGeometryData* InData) = 0;` — `UE_DEPRECATED(4.27, "Use overload with SharedPtr instead.")`
- L27 _public prototype_ `virtual void ARTrackedGeometryAdded(TSharedPtr<struct FOpenXRARTrackedGeometryData> InData) = 0;`
- L28 _public prototype_ `virtual void ARTrackedGeometryUpdated(TSharedPtr<struct FOpenXRARTrackedGeometryData> InData) = 0;`
- L29 _public prototype_ `virtual void ARTrackedGeometryRemoved(TSharedPtr<struct FOpenXRARTrackedGeometryData> InData) = 0;`

#### class `IOpenXRARTrackedMeshHolder`  
`class IOpenXRARTrackedMeshHolder`  
_L32-46_
- L35 _public function_ `virtual ~IOpenXRARTrackedMeshHolder()`
- L37 _public prototype_ `virtual void StartMeshUpdates() = 0;`
- L38 _public prototype_ `virtual struct FOpenXRMeshUpdate* AllocateMeshUpdate(FGuid InGuidMeshUpdate) = 0;`
- L39 _public prototype_ `virtual void RemoveMesh(FGuid InGuidMeshUpdate) = 0;`
- L40 _public prototype_ `virtual struct FOpenXRPlaneUpdate* AllocatePlaneUpdate(FGuid InGuidPlaneUpdate) = 0;`
- L41 _public prototype_ `virtual void RemovePlane(FGuid InGuidPlaneUpdate) = 0;`
- L42 _public prototype_ `virtual void EndMeshUpdates() = 0;`
- L44 _public prototype_ `virtual void ObjectUpdated(FOpenXRARTrackedGeometryData* InUpdate) = 0;` — `UE_DEPRECATED(4.27, "Use overload with SharedPtr instead.")`
- L45 _public prototype_ `virtual void ObjectUpdated(TSharedPtr<struct FOpenXRARTrackedGeometryData>) = 0;`

#### struct `FOpenXRARTrackedGeometryData`  
`struct FOpenXRARTrackedGeometryData : public FNoncopyable`  
_L51-77_
- inherits: `FNoncopyable`
- desc: Base class for ARTrackedGeometryData These structs are designed to be constructed by openxr plugin code on any thread and then used by UE4 on the Game Thread. All their data members need to be safe to create on any thread.
- L60 _public member_ `const EDataType DataType;`
- L61 _public member_ `FGuid Id;`
- L62 _public member_ `EARTrackingState TrackingState = EARTrackingState::Unknown;`
- L63 _public member_ `FTransform LocalToTrackingTransform;`
- L67 _protected function_ `FOpenXRARTrackedGeometryData(EDataType InDataType) : DataType(InDataType)` — Force derived classes to init the type.
- L73 _public function_ `virtual ~FOpenXRARTrackedGeometryData()`
- L75 _public prototype_ `virtual UARTrackedGeometry* ConstructNewTrackedGeometry(TSharedPtr<FARSupportInterface, ESPMode::ThreadSafe> ARSupportInterface) = 0;`
- L76 _public prototype_ `virtual void UpdateTrackedGeometry(UARTrackedGeometry* TrackedGeometry, TSharedPtr<FARSupportInterface, ESPMode::ThreadSafe> ARSupportInterface) = 0;`

#### enum `FOpenXRARTrackedGeometryData::EDataType`  
`enum class EDataType : int8`  
_L53-59_
- L55 _public enumerator_ `Unknown`
- L56 _public enumerator_ `Mesh`
- L57 _public enumerator_ `QRCode`
- L58 _public enumerator_ `Plane`

#### struct `FOpenXRQRCodeData`  
`struct FOpenXRQRCodeData : public FOpenXRARTrackedGeometryData`  
_L79-94_
- inherits: `FOpenXRARTrackedGeometryData`
- L82 _public member_ `FVector2D Size = {};`
- L83 _public member_ `FString QRCode;`
- L84 _public member_ `int32 Version = 0;`
- L85 _public member_ `double Timestamp = 0;`
- L87 _public function_ `FOpenXRQRCodeData() : FOpenXRARTrackedGeometryData(EDataType::QRCode)`
- L92 _public prototype_ `virtual UARTrackedGeometry* ConstructNewTrackedGeometry(TSharedPtr<FARSupportInterface, ESPMode::ThreadSafe> ARSupportInterface) override;`
- L93 _public prototype_ `virtual void UpdateTrackedGeometry(UARTrackedGeometry* TrackedGeometry, TSharedPtr<FARSupportInterface, ESPMode::ThreadSafe> ARSupportInterface) override;`

#### struct `FOpenXRMeshUpdate`  
`struct FOpenXRMeshUpdate : public FOpenXRARTrackedGeometryData`  
_L96-115_
- inherits: `FOpenXRARTrackedGeometryData`
- L98 _public member_ `EARObjectClassification Type = EARObjectClassification::NotApplicable;`
- L99 _public member_ `EARSpatialMeshUsageFlags SpatialMeshUsageFlags = EARSpatialMeshUsageFlags::NotApplicable;`
- L100 _public member_ `TArray<FVector3f> Vertices;`
- L101 _public member_ `TArray<MRMESH_INDEX_TYPE> Indices;`
- L103 _public function_ `FOpenXRMeshUpdate() : FOpenXRARTrackedGeometryData(EDataType::Mesh)`
- L108 _public prototype_ `virtual UARTrackedGeometry* ConstructNewTrackedGeometry(TSharedPtr<FARSupportInterface, ESPMode::ThreadSafe> ARSupportInterface) override;`
- L109 _public prototype_ `virtual void UpdateTrackedGeometry(UARTrackedGeometry* TrackedGeometry, TSharedPtr<FARSupportInterface, ESPMode::ThreadSafe> ARSupportInterface) override;`
- L111 _public function_ `bool HasSpatialMeshUsageFlag(const EARSpatialMeshUsageFlags& InFlag)`

#### struct `FOpenXRPlaneUpdate`  
`struct FOpenXRPlaneUpdate : public FOpenXRARTrackedGeometryData`  
_L117-135_
- inherits: `FOpenXRARTrackedGeometryData`
- L119 _public member_ `EARObjectClassification Type = EARObjectClassification::NotApplicable;`
- L120 _public member_ `EARSpatialMeshUsageFlags SpatialMeshUsageFlags = EARSpatialMeshUsageFlags::NotApplicable;`
- L121 _public member_ `FVector Extent;`
- L123 _public function_ `FOpenXRPlaneUpdate() : FOpenXRARTrackedGeometryData(EDataType::Plane)`
- L128 _public prototype_ `virtual UARTrackedGeometry* ConstructNewTrackedGeometry(TSharedPtr<FARSupportInterface, ESPMode::ThreadSafe> ARSupportInterface) override;`
- L129 _public prototype_ `virtual void UpdateTrackedGeometry(UARTrackedGeometry* TrackedGeometry, TSharedPtr<FARSupportInterface, ESPMode::ThreadSafe> ARSupportInterface) override;`
- L131 _public function_ `bool HasSpatialMeshUsageFlag(const EARSpatialMeshUsageFlags& InFlag)`
