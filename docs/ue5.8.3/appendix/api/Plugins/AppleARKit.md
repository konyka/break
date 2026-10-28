# Plugins / AppleARKit

- module root: `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit`
- headers: 21; symbols: 514
- symbol kinds: class=19, delegate=2, enum=7, enumerator=26, externvar=3, function=63, macro=15, member=159, namespace=2, prototype=209, struct=7, typedef=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ARUtilities, AppleImageUtils, AugmentedReality, CoreUObject, HeadMountedDisplay, IOSRuntimeSettings, MetalRHI, Projects, RHI, RenderCore, Renderer, Slate, SlateCore, XRBase
- PublicDependencyModuleNames: Core, Engine, EyeTracker, MRMesh

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Private/ARKitCoachingOverlay.h` (Private)
_(no declarations extracted)_

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Private/ARKitGeoTrackingSupport.h` (Private)


#### class `UARKitGeoTrackingSupport`  
`class UARKitGeoTrackingSupport : public UARGeoTrackingSupport`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UARGeoTrackingSupport`
- L16 _public prototype_ `TSharedPtr<FCheckGeoTrackingAvailabilityAsyncTask, ESPMode::ThreadSafe> CheckGeoTrackingAvailability(FString& OutError) override;`
- L17 _public prototype_ `TSharedPtr<FCheckGeoTrackingAvailabilityAsyncTask, ESPMode::ThreadSafe> CheckGeoTrackingAvailability(float Longitude, float Latitude, FString& OutError) override;`
- L18 _public prototype_ `TSharedPtr<FGetGeoLocationAsyncTask, ESPMode::ThreadSafe> GetGeoLocationAtWorldPosition(const FVector& WorldPosition, FString& OutError) override;`
- L20 _public prototype_ `EARGeoTrackingState GetGeoTrackingState() const override;`
- L21 _public prototype_ `EARGeoTrackingStateReason GetGeoTrackingStateReason() const override;`
- L22 _public prototype_ `EARGeoTrackingAccuracy GetGeoTrackingAccuracy() const override;`
- L24 _public prototype_ `bool AddGeoAnchorAtLocation(float Longitude, float Latitude, FString OptionalAnchorName) override;`
- L25 _public prototype_ `bool AddGeoAnchorAtLocationWithAltitude(float Longitude, float Latitude, float AltitudeMeters, FString OptionalAnchorName) override;`

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Private/ARKitTrackables.h` (Private)


#### class `UARKitMeshGeometry`  
`class UARKitMeshGeometry : public UARMeshGeometry`  
_L11-17_
- reflection: `UCLASS(NotBlueprintType)`
- inherits: `UARMeshGeometry`
- L16 _public prototype_ `bool GetObjectClassificationAtLocation(const FVector& InWorldLocation, EARObjectClassification& OutClassification, FVector& OutClassificationLocation, float MaxLocationDiff = 10.f) override;`

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Private/AppleARKitCamera.h` (Private)


#### enum `EAppleARKitBackgroundFitMode`  
`enum class EAppleARKitBackgroundFitMode : uint8`  
_L23-33_
- L26 _public enumerator_ `Fit` — The background image will be letterboxed to fit the screen
- L29 _public enumerator_ `Fill` — The background will be scaled & cropped to the screen
- L32 _public enumerator_ `Stretch` — The background image will be stretched to fill the screen

#### struct `FAppleARKitCamera`  
`struct FAppleARKitCamera`  
_L40-147_
- reflection: `USTRUCT(Category="AppleARKit")`
- desc: A model representing the camera and its properties at a single point in time.
- L45 _public function_ `FAppleARKitCamera() : TrackingQuality(EARTrackingQuality::NotTracking) , TrackingQualityReason(EARTrackingQualityReason::None) , Orientation(ForceInit) , Translation(ForceInitToZero) , ImageResolution(ForceInitToZero) , FocalLength(ForceInitToZero) , PrincipalPoint(ForceInitToZero)` — Default constructor
- L61 _public prototype_ `FAppleARKitCamera( ARCamera* InARCamera );` — This is a conversion copy-constructor that takes a raw ARCamera and fills this structs members with the UE-ified versions of ARCamera's properties.
- L69 _public member_ `EARTrackingQuality TrackingQuality;` — `UPROPERTY()` — The tracking quality of the camera.
- L75 _public member_ `EARTrackingQualityReason TrackingQualityReason;` — `UPROPERTY()` — The reason for the current tracking quality of the camera.
- L81 _public member_ `FTransform Transform;` — `UPROPERTY()` — The transformation matrix that defines the camera's rotation and translation in world coordinates.
- L85 _public member_ `FQuat Orientation;` — `UPROPERTY()` — Raw orientation of the camera
- L89 _public member_ `FVector Translation;` — `UPROPERTY()` — Raw position of the camera
- L95 _public member_ `FVector2D ImageResolution;` — `UPROPERTY()` — Camera image resolution in pixels
- L101 _public member_ `FVector2D FocalLength;` — `UPROPERTY()` — Camera focal length in pixels
- L107 _public member_ `FVector2D PrincipalPoint;` — `UPROPERTY()` — Camera principal point in pixels
- L110 _public prototype_ `float GetAspectRatio() const;` — Returns the ImageResolution aspect ration (Width / Height)
- L113 _public prototype_ `float GetHorizontalFieldOfView() const;` — Returns the horizonal FOV of the camera on this frame in degrees.
- L116 _public prototype_ `float GetVerticalFieldOfView() const;` — Returns the vertical FOV of the camera on this frame in degrees.
- L119 _public prototype_ `float GetHorizontalFieldOfViewForScreen( EAppleARKitBackgroundFitMode BackgroundFitMode ) const;` — Returns the effective horizontal field of view for the screen dimensions and fit mode in those dimensions
- L122 _public prototype_ `float GetVerticalFieldOfViewForScreen( EAppleARKitBackgroundFitMode BackgroundFitMode ) const;` — Returns the effective horizontal field of view for the screen when a device is in portrait mode
- L125 _public prototype_ `float GetHorizontalFieldOfViewForScreen( EAppleARKitBackgroundFitMode BackgroundFitMode, float ScreenWidth, float ScreenHeight ) const;` — Returns the effective horizontal field of view for the screen dimensions and fit mode in those dimensions
- L128 _public prototype_ `float GetVerticalFieldOfViewForScreen( EAppleARKitBackgroundFitMode BackgroundFitMode, float ScreenWidth, float ScreenHeight ) const;` — Returns the effective vertical field of view for the screen dimensions and fit mode in those dimensions
- L131 _public prototype_ `void GetViewProjectionMatrix(EDeviceScreenOrientation DeviceOrientation, FSceneViewProjectionData& InOutProjectionData) const;` — Returns the Projection Matrix we need to render our virtual content with.
- L136 _public function_ `FVector2D GetImageCoordinateForScreenPosition( FVector2D ScreenPosition, EAppleARKitBackgroundFitMode BackgroundFitMode ) const` — For the given screen position, returns the normalised capture image coordinates accounting for the fit mode of the image on screen
- L146 _public prototype_ `FVector2D GetImageCoordinateForScreenPosition( FVector2D ScreenPosition, EAppleARKitBackgroundFitMode BackgroundFitMode, float ScreenWidth, float ScreenHeight ) const;` — For the given screen position, returns the normalised capture image coordinates accounting for the fit mode of the image on screen

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Private/AppleARKitFrame.h` (Private)


#### struct `FAppleARKitFrame`  
`struct FAppleARKitFrame`  
_L17-97_
- reflection: `USTRUCT(Category="AppleARKit")`
- desc: An object representing a frame processed by FAppleARKitSystem. @discussion Each frame contains information about the current state of the scene.
- L21 _public prototype_ `FAppleARKitFrame() = default;`
- L22 _public prototype_ `FAppleARKitFrame(const FAppleARKitFrame& Other) = delete;`
- L27 _public prototype_ `FAppleARKitFrame& operator=(const FAppleARKitFrame& Other);` — Assignment operator. CapturedImage is skipped as we don't need / want to retain access to the image buffer.
- L38 _public prototype_ `FAppleARKitFrame(ARFrame* InARFrame, const FVector2D MinCameraUV, const FVector2D MaxCameraUV, CVMetalTextureCacheRef MetalTextureCache);` — This is a conversion copy-constructor that takes a raw ARFrame and fills this structs members with the UE-ified versions of ARFrames properties. @param InARFrame 		- The frame to convert / copy @param MinCameraUV 		- The minimum (top left) UV used to render the passthrough camera @param MaxCameraUV 		- The maximum (bottom right) UV used to render the passthrough camera
- L41 _public prototype_ `virtual ~FAppleARKitFrame();` — Destructor. Calls CFRelease on CapturedImage
- L43 _public prototype_ `void ReleaseResources();`
- L47 _public member_ `double Timestamp = 0.0;` — A timestamp identifying the frame.
- L52 _public member_ `CVPixelBufferRef CameraImage = nullptr;` — The raw camera buffer from ARKit
- L54 _public member_ `AVDepthData* CameraDepth = nullptr;` — The raw camera depth info from ARKit (needs iPhone X)
- L55 _public member_ `ARFrame* NativeFrame = nullptr;`
- L58 _public member_ `CVMetalTextureRef CapturedYImage = nullptr;` — The frame's captured images
- L59 _public member_ `CVMetalTextureRef CapturedCbCrImage = nullptr;`
- L64 _public member_ `FIntPoint CapturedYImageSize = FIntPoint::ZeroValue;` — The size in pixels of the frame's captured images.
- L65 _public member_ `FIntPoint CapturedCbCrImageSize = FIntPoint::ZeroValue;`
- L68 _public member_ `FAppleARKitCamera Camera;` — The camera used to capture the frame's image.
- L73 _public member_ `FAppleARKitLightEstimate LightEstimate;` — A light estimate representing the estimated light in the scene.
- L76 _public member_ `EARWorldMappingState WorldMappingState = EARWorldMappingState::NotAvailable;` — The current world mapping state is reported on the frame
- L79 _public member_ `FARPose2D Tracked2DPose;` — The current tracked 2D pose
- L83 _public member_ `CVPixelBufferRef SegmentationBuffer = nullptr;` — The person segmentation buffer from ARKit
- L86 _public member_ `CVPixelBufferRef EstimatedDepthData = nullptr;` — The estimated depth buffer for person segmentation from ARKit
- L90 _public member_ `ARDepthData* SceneDepth = nullptr;`

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Private/AppleARKitLightEstimate.h` (Private)


#### struct `FAppleARKitLightEstimate`  
`struct FAppleARKitLightEstimate`  
_L22-62_
- reflection: `USTRUCT()`
- desc: A light estimate represented as spherical harmonics
- L27 _public function_ `FAppleARKitLightEstimate() : bIsValid(false) , AmbientIntensity(0.f) , AmbientColorTemperatureKelvin(0.f)` — Default constructor
- L39 _public prototype_ `FAppleARKitLightEstimate( ARLightEstimate* InARLightEstimate );` — This is a conversion copy-constructor that takes a raw ARLightEstimate and fills this structs members with the UE-ified versions of ARLightEstimate's properties.
- L45 _public member_ `bool bIsValid;` — `UPROPERTY()` — True if light estimation was enabled for the session and light estimation was successful
- L54 _public member_ `float AmbientIntensity;` — `UPROPERTY()` — Ambient intensity of the lighting. In a well lit environment, this value is close to 1000. It typically ranges from 0 (very dark) to around 2000 (very bright).
- L61 _public member_ `float AmbientColorTemperatureKelvin;` — `UPROPERTY()` — Color Temperature in Kelvin of light

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Private/AppleARKitModule.h` (Private)


#### class `FAppleARKitModule`  
`class FAppleARKitModule : public IHeadMountedDisplayModule`  
_L10-30_
- inherits: `IHeadMountedDisplayModule`
- L13 _public prototype_ `virtual TSharedPtr<class IXRTrackingSystem, ESPMode::ThreadSafe> CreateTrackingSystem() override;`
- L15 _public prototype_ `static TSharedPtr<class FAppleARKitSystem, ESPMode::ThreadSafe> GetARKitSystem();`
- L17 _public prototype_ `FString GetModuleKeyName() const override;`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _public prototype_ `void PreExit();`
- L26 _public prototype_ `void PostEngineInit();`
- L27 _public prototype_ `void RegisterSettings();`
- L28 _public prototype_ `void UnregisterSettings();`

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAppleARKit, Log, All);`
- L32 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAppleARKit, Log, All);`

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Private/AppleARKitSessionDelegate.h` (Private)
_(no declarations extracted)_

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Private/AppleARKitSystem.h` (Private)


#### class `FAppleARKitSystem`  
`class FAppleARKitSystem : public FARSystemSupportBase, public FXRTrackingSystemBase, public FGCObject, public TSharedFromThis<FAppleARKitSystem, ESPMode::ThreadSafe>`  
_L30-231_
- inherits: `FARSystemSupportBase,FXRTrackingSystemBase,FGCObject,TSharedFromThis<FAppleARKitSystem,ESPMode::ThreadSafe>`
- L36 _public prototype_ `FAppleARKitSystem();`
- L37 _public prototype_ `~FAppleARKitSystem();`
- L40 _public prototype_ `FName GetSystemName() const override;`
- L41 _public prototype_ `int32 GetXRSystemFlags() const override;`
- L42 _public prototype_ `bool GetCurrentPose(int32 DeviceId, FQuat& OutOrientation, FVector& OutPosition) override;`
- L43 _public prototype_ `FString GetVersionString() const override;`
- L44 _public prototype_ `bool EnumerateTrackedDevices(TArray<int32>& OutDevices, EXRTrackedDeviceType Type) override;`
- L45 _public prototype_ `void ResetOrientationAndPosition(float Yaw) override;`
- L46 _public prototype_ `bool IsHeadTrackingAllowed() const override;`
- L47 _public prototype_ `TSharedPtr<class IXRCamera, ESPMode::ThreadSafe> GetXRCamera(int32 DeviceId) override;`
- L48 _public prototype_ `float GetWorldToMetersScale() const override;`
- L49 _public prototype_ `void OnBeginRendering_GameThread(FSceneViewFamily& InViewFamily) override;`
- L50 _public prototype_ `bool OnStartGameFrame(FWorldContext& WorldContext) override;`
- L53 _public prototype_ `void* GetARSessionRawPointer() override;`
- L54 _public prototype_ `void* GetGameThreadARFrameRawPointer() override;`
- L57 _public prototype_ `void Shutdown();` — So the module can shut down the ar services cleanly
- L59 _public prototype_ `bool GetGuidForGeometry(UARTrackedGeometry* InGeometry, FGuid& OutGuid) const;`
- L63 _private prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L64 _private function_ `virtual FString GetReferencerName() const override`
- L69 _protected prototype_ `virtual bool IsARAvailable() const override;` — Returns true/false based on whether AR features are available
- L70 _protected prototype_ `virtual void OnARSystemInitialized() override;`
- L71 _protected prototype_ `virtual EARTrackingQuality OnGetTrackingQuality() const override;`
- L72 _protected prototype_ `virtual EARTrackingQualityReason OnGetTrackingQualityReason() const override;`
- L73 _protected prototype_ `virtual void OnStartARSession(UARSessionConfig* SessionConfig) override;`
- L74 _protected prototype_ `virtual void OnPauseARSession() override;`
- L75 _protected prototype_ `virtual void OnStopARSession() override;`
- L76 _protected prototype_ `virtual FARSessionStatus OnGetARSessionStatus() const override;`
- L77 _protected prototype_ `virtual void OnSetAlignmentTransform(const FTransform& InAlignmentTransform) override;`
- L78 _protected prototype_ `virtual TArray<FARTraceResult> OnLineTraceTrackedObjects( const FVector2D ScreenCoord, EARLineTraceChannels TraceChannels ) override;`
- L79 _protected prototype_ `virtual TArray<FARTraceResult> OnLineTraceTrackedObjects(const FVector Start, const FVector End, EARLineTraceChannels TraceChannels) override;`
- L80 _protected prototype_ `virtual TArray<UARTrackedGeometry*> OnGetAllTrackedGeometries() const override;`
- L81 _protected prototype_ `virtual TArray<UARPin*> OnGetAllPins() const override;`
- L82 _protected prototype_ `virtual bool OnIsTrackingTypeSupported(EARSessionType SessionType) const override;`
- L83 _protected prototype_ `virtual UARLightEstimate* OnGetCurrentLightEstimate() const override;`
- L84 _protected prototype_ `virtual UARPin* FindARPinByComponent(const USceneComponent* Component) const override;`
- L85 _protected prototype_ `virtual UARPin* OnPinComponent(USceneComponent* ComponentToPin, const FTransform& PinToWorldTransform, UARTrackedGeometry* TrackedGeometry = nullptr, const FName DebugName = NAME_None) override;`
- L86 _protected prototype_ `virtual void OnRemovePin(UARPin* PinToRemove) override;`
- L87 _protected prototype_ `virtual bool OnTryGetOrCreatePinForNativeResource(void* InNativeResource, const FString& InAnchorName, UARPin*& OutAnchor) override;`
- L88 _protected prototype_ `virtual UARTexture* OnGetARTexture(EARTextureType TextureType) const override;`
- L89 _protected prototype_ `virtual bool OnAddManualEnvironmentCaptureProbe(FVector Location, FVector Extent) override;`
- L90 _protected prototype_ `virtual TSharedPtr<FARGetCandidateObjectAsyncTask, ESPMode::ThreadSafe> OnGetCandidateObject(FVector Location, FVector Extent) const override;`
- L91 _protected prototype_ `virtual TSharedPtr<FARSaveWorldAsyncTask, ESPMode::ThreadSafe> OnSaveWorld() const override;`
- L92 _protected prototype_ `virtual EARWorldMappingState OnGetWorldMappingStatus() const override;`
- L93 _protected prototype_ `virtual TArray<FARVideoFormat> OnGetSupportedVideoFormats(EARSessionType SessionType) const override;`
- L94 _protected prototype_ `virtual TArray<FVector> OnGetPointCloud() const override;`
- L95 _protected function_ `virtual bool OnAddRuntimeCandidateImage(UARSessionConfig* SessionConfig, UTexture2D* CandidateTexture, FString FriendlyName, float PhysicalWidth) override`
- L97 _protected prototype_ `virtual bool OnIsSessionTrackingFeatureSupported(EARSessionType SessionType, EARSessionTrackingFeature SessionTrackingFeature) const override;`
- L98 _protected prototype_ `virtual TArray<FARPose2D> OnGetTracked2DPose() const override;`
- L99 _protected prototype_ `virtual bool OnIsSceneReconstructionSupported(EARSessionType SessionType, EARSceneReconstruction SceneReconstructionMethod) const override;`
- L100 _protected prototype_ `virtual bool OnAddTrackedPointWithName(const FTransform& WorldTransform, const FString& PointName, bool bDeletePointsWithSameName) override;`
- L101 _protected prototype_ `virtual int32 OnGetNumberOfTrackedFacesSupported() const override;`
- L102 _protected prototype_ `bool OnGetCameraIntrinsics(FARCameraIntrinsics& OutCameraIntrinsics) const override;`
- L106 _private prototype_ `bool Run(UARSessionConfig* SessionConfig);`
- L107 _private prototype_ `bool IsRunning() const;`
- L108 _private prototype_ `bool Pause();`
- L109 _private prototype_ `void OrientationChanged(const int32 NewOrientation);`
- L110 _private prototype_ `void UpdateFrame();`
- L111 _private prototype_ `void CalcTrackingToWorldRotation();`
- L114 _private prototype_ `void WriteCameraImageToDisk(CVPixelBufferRef PixelBuffer);` — Asynchronously writes a JPEG to disk
- L116 _private prototype_ `class FAppleARKitXRCamera* GetARKitXRCamera();`
- L120 _public prototype_ `void SessionDidUpdateFrame_DelegateThread( TSharedPtr< FAppleARKitFrame, ESPMode::ThreadSafe > Frame );` — Session delegate callbacks
- L121 _public prototype_ `void SessionDidFailWithError_DelegateThread( const FString& Error );`
- L123 _public prototype_ `void SessionDidAddAnchors_DelegateThread( NSArray<ARAnchor*>* anchors );`
- L124 _public prototype_ `void SessionDidUpdateAnchors_DelegateThread( NSArray<ARAnchor*>* anchors );`
- L125 _public prototype_ `void SessionDidRemoveAnchors_DelegateThread( NSArray<ARAnchor*>* anchors );`
- L127 _private prototype_ `void SessionDidAddAnchors_Internal( TSharedRef<FAppleARKitAnchorData> AnchorData );`
- L128 _private prototype_ `void SessionDidUpdateAnchors_Internal( TSharedRef<FAppleARKitAnchorData> AnchorData );`
- L129 _private prototype_ `void SessionDidRemoveAnchors_Internal( FGuid AnchorGuid );`
- L131 _private prototype_ `void SessionDidUpdateFrame_Internal( TSharedRef< FAppleARKitFrame, ESPMode::ThreadSafe > Frame );`
- L133 _private prototype_ `void ClearTrackedGeometries();` — Removes all tracked geometries, marking them as not tracked and sending the delegate event
- L139 _private member_ `bool bIsRunning = false;`
- L141 _private prototype_ `void SetDeviceOrientationAndDerivedTracking(EDeviceScreenOrientation InOrientation);`
- L144 _private prototype_ `void CheckForFaceARSupport(UARSessionConfig* InSessionConfig);` — Creates or clears the face ar support object if face ar has been requested
- L147 _private prototype_ `void CheckForPoseTrackingARLiveLink(UARSessionConfig* InSessionConfig);` — Creates or clears the pose tracking ar support object if face ar has been requested
- L150 _private prototype_ `void UpdateARKitPerfStats();` — Updates the ARKit perf counters
- L153 _private prototype_ `void SetupCameraTextures();` — Inits the textures and sets the texture on the overlay
- L155 _private prototype_ `UARTrackedGeometry* TryCreateTrackedGeometry(TSharedRef<FAppleARKitAnchorData> AnchorData);`
- L157 _private prototype_ `void OnSpawnARActor(AARActor* NewARActor, UARComponent* NewARComponent, FGuid NativeID);`
- L159 _private prototype_ `FGuid GetSessionGuid() const;`
- L163 _private member_ `EDeviceScreenOrientation DeviceOrientation;` — The orientation of the device; see EDeviceScreenOrientation
- L166 _private member_ `FRotator DerivedTrackingToUnrealRotation;` — A rotation from ARKit TrackingSpace to Unreal Space. It is re-derived based on other parameters; users should not set it directly.
- L171 _private member_ `ARSession* Session = nullptr;` — ARKit Session
- L174 _private member_ `FAppleARKitSessionDelegate* Delegate = nullptr;` — ARKit Session Delegate
- L177 _private member_ `CVMetalTextureCacheRef MetalTextureCache = nullptr;` — The Metal texture cache for unbuffered texture uploads.
- L180 _private member_ `TMap< FString, CGImage* > ConvertedCandidateImages;` — Cache of images that we've converted previously to prevent repeated conversion
- L183 _private member_ `TMap<FGuid, ARAnchor*> AllAnchors;` — All the anchors added from the current session
- L185 _private member_ `FCriticalSection AnchorsLock;`
- L189 _private member_ `FARKitCoachingOverlay* CoachingOverlay = nullptr;`
- L195 _private member_ `TMap< FGuid, FTrackedGeometryGroup > TrackedGeometryGroups;` — PROPERTIES REPORTED TO FGCObject ...
- L196 _private member_ `TArray<TObjectPtr<UARPin>> Pins;`
- L197 _private member_ `TObjectPtr<UARLightEstimate> LightEstimate = nullptr;`
- L198 _private member_ `TObjectPtr<UAppleARKitCameraVideoTexture> CameraImage = nullptr;`
- L199 _private member_ `TObjectPtr<UAppleARKitTextureCameraDepth> CameraDepth = nullptr;`
- L200 _private member_ `TMap< FString, TObjectPtr<UARCandidateImage> > CandidateImages;`
- L201 _private member_ `TMap< FString, TObjectPtr<UARCandidateObject> > CandidateObjects;`
- L202 _private member_ `TObjectPtr<UAppleARKitTextureCameraImage> SceneDepthMap = nullptr;`
- L203 _private member_ `TObjectPtr<UAppleARKitTextureCameraImage> SceneDepthConfidenceMap = nullptr;`
- L209 _private member_ `uint32 LastTrackedGeometry_DebugId;` — An int counter that provides a human-readable debug number for Tracked Geometries.
- L213 _private member_ `FCriticalSection FrameLock;` — 'threadsafe' sharedptrs merely guaranteee atomicity when adding/removing refs.  You can still have a race with destruction and copying sharedptrs.
- L216 _private member_ `TSharedPtr< FAppleARKitFrame, ESPMode::ThreadSafe > GameThreadFrame;` — Last frame grabbed & processed by via the ARKit session delegate
- L217 _private member_ `TSharedPtr< FAppleARKitFrame, ESPMode::ThreadSafe > RenderThreadFrame;`
- L218 _private member_ `TSharedPtr< FAppleARKitFrame, ESPMode::ThreadSafe > LastReceivedFrame;`
- L221 _private member_ `IAppleARKitFaceSupport* FaceARSupport = nullptr;` — The object that is handling face support if present
- L224 _private member_ `IAppleARKitPoseTrackingLiveLink* PoseTrackingARLiveLink;` — The object that is handling pose tracking livelink if present
- L227 _private member_ `TObjectPtr<UTimecodeProvider> TimecodeProvider = nullptr;` — The time code provider to use when tagging time stamps
- L230 _private member_ `FDelegateHandle SpawnARActorDelegateHandle;` — for networked callbacks

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_STATS_GROUP(TEXT("ARKit"), STATGROUP_ARKIT, STATCAT_Advan`
- L234 _namespace_ `namespace AppleARKitSupport`
- L236 _prototype_ `TSharedPtr<class FAppleARKitSystem, ESPMode::ThreadSafe> CreateAppleARKitSystem();` (scope `AppleARKitSupport`)

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Private/AppleARKitTimecodeProvider.h` (Private)


#### class `UAppleARKitTimecodeProvider`  
`class UAppleARKitTimecodeProvider : public UTimecodeProvider`  
_L13-31_
- reflection: `UCLASS()`
- inherits: `UTimecodeProvider`
- desc: This class is an implementation of the ITimecodeProvider and is used to abstract out the calculation of the frame & time for an update
- L19 _public prototype_ `UAppleARKitTimecodeProvider();`
- L22 _public prototype_ `virtual FQualifiedFrameTime GetQualifiedFrameTime() const override;`
- L23 _public prototype_ `virtual ETimecodeProviderSynchronizationState GetSynchronizationState() const override;`
- L24 _public prototype_ `virtual bool Initialize(class UEngine* InEngine) override;`
- L25 _public prototype_ `virtual void Shutdown(class UEngine* InEngine) override;`
- L30 _private member_ `FFrameRate FrameRate;` — The frame rate of updates is 60 hz

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Private/AppleARKitTrackable.h` (Private)


#### class `UAppleARKitEnvironmentCaptureProbe`  
`class UAppleARKitEnvironmentCaptureProbe : public UAREnvironmentCaptureProbe`  
_L18-35_
- reflection: `UCLASS(NotBlueprintType)`
- inherits: `UAREnvironmentCaptureProbe`
- L24 _public prototype_ `UAppleARKitEnvironmentCaptureProbe();`
- L28 _public prototype_ `void UpdateEnvironmentCapture(const TSharedRef<FARSupportInterface , ESPMode::ThreadSafe>& InTrackingSystem, uint32 FrameNumber, double Timestamp, const FTransform& InLocalToTrackingTransform, const FTransform& InAlignmentTransform, FVector InExtent, id<MTLTexture> InMetalTexture);` — Updates the current capture with the new metal texture. This will trigger a render resource update if the textures have changed
- L34 _private member_ `TObjectPtr<UAppleARKitEnvironmentCaptureProbeTexture> ARKitEnvironmentTexture;` — `UPROPERTY()` — The cube map of the reflected environment

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Private/AppleARKitVideoOverlay.h` (Private)


#### enum `EARKitOcclusionType`  
`enum class EARKitOcclusionType : uint8`  
_L23-28_
- L25 _public enumerator_ `None`
- L26 _public enumerator_ `PersonSegmentation`
- L27 _public enumerator_ `SceneDepth`

#### class `UARKitCameraOverlayMaterialLoader`  
`class UARKitCameraOverlayMaterialLoader : public UObject`  
_L32-75_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Helper class to ensure the ARKit camera material is cooked.
- L38 _public member_ `TObjectPtr<UMaterialInterface> DefaultCameraOverlayMaterial;` — `UPROPERTY()`
- L41 _public member_ `TObjectPtr<UMaterialInterface> DepthOcclusionOverlayMaterial;` — `UPROPERTY()`
- L44 _public member_ `TObjectPtr<UMaterialInterface> MatteOcclusionOverlayMaterial;` — `UPROPERTY()`
- L47 _public member_ `TObjectPtr<UMaterialInterface> SceneDepthOcclusionMaterial;` — `UPROPERTY()`
- L50 _public member_ `TObjectPtr<UMaterialInterface> SceneDepthColorationMaterial;` — `UPROPERTY()`
- L52 _public function_ `UARKitCameraOverlayMaterialLoader()`
- L70 _public member_ `static const FString OverlayMaterialPath;`
- L71 _public member_ `static const FString DepthOcclusionOverlayMaterialPath;`
- L72 _public member_ `static const FString MatteOcclusionOverlayMaterialPath;`
- L73 _public member_ `static const FString SceneDepthOcclusionMaterialPath;`
- L74 _public member_ `static const FString SceneDepthColorationMaterialPath;`

#### class `FAppleARKitVideoOverlay`  
`class FAppleARKitVideoOverlay : public FGCObject`  
_L77-138_
- inherits: `FGCObject`
- L80 _public prototype_ `FAppleARKitVideoOverlay();`
- L81 _public prototype_ `virtual ~FAppleARKitVideoOverlay();`
- L83 _public prototype_ `void SetCameraTexture(UARTextureCameraImage* InCameraImage);`
- L85 _public prototype_ `void RenderVideoOverlay_RenderThread(FRHICommandList& RHICmdList, const FSceneView& InView, struct FAppleARKitFrame& Frame, const float WorldToMeterScale);`
- L86 _public prototype_ `bool GetPassthroughCameraUVs_RenderThread(TArray<FVector2D>& OutUVs, const EDeviceScreenOrientation DeviceOrientation);`
- L88 _public prototype_ `void SetOverlayTexture(UARTextureCameraImage* InCameraImage);`
- L89 _public prototype_ `void SetOcclusionType(EARKitOcclusionType InOcclusionType);`
- L91 _public prototype_ `void UpdateSceneDepthTextures(UTexture* SceneDepthTexture, UTexture* DepthConfidenceTexture);`
- L93 _public function_ `UAppleARKitOcclusionTexture* GetOcclusionMatteTexture() const`
- L94 _public function_ `UAppleARKitOcclusionTexture* GetOcclusionDepthTexture() const`
- L98 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L99 _private function_ `virtual FString GetReferencerName() const override`
- L105 _private prototype_ `void RenderVideoOverlayWithMaterial(FRHICommandList& RHICmdList, const FSceneView& InView, struct FAppleARKitFrame& Frame, UMaterialInstanceDynamic* RenderingOverlayMaterial, const bool bRenderingOcclusion);`
- L106 _private prototype_ `void UpdateOcclusionTextures(const FAppleARKitFrame& Frame);`
- L107 _private prototype_ `void UpdateVideoTextures(const FAppleARKitFrame& Frame);`
- L109 _private prototype_ `void UpdateDebugOverlay();`
- L112 _private member_ `FBufferRHIRef OverlayVertexBufferRHI;` — 0 for landscape, 1 for portrait
- L113 _private member_ `FBufferRHIRef IndexBufferRHI;`
- L115 _private member_ `EARKitOcclusionType OcclusionType = EARKitOcclusionType::None;`
- L118 _private member_ `ARMatteGenerator* MatteGenerator = nullptr;`
- L119 _private member_ `id<MTLCommandQueue> CommandQueue = nullptr;`
- L122 _private member_ `bool bOcclusionDepthTextureRecentlyUpdated = false;`
- L124 _private member_ `TObjectPtr<UMaterialInstanceDynamic> MID_CameraOverlay = nullptr;`
- L125 _private member_ `TObjectPtr<UMaterialInstanceDynamic> MID_DepthOcclusionOverlay = nullptr;`
- L126 _private member_ `TObjectPtr<UMaterialInstanceDynamic> MID_MatteOcclusionOverlay = nullptr;`
- L127 _private member_ `TObjectPtr<UMaterialInstanceDynamic> MID_SceneDepthOcclusion = nullptr;`
- L128 _private member_ `TObjectPtr<UMaterialInstanceDynamic> MID_SceneDepthColoration = nullptr;`
- L130 _private member_ `TObjectPtr<UAppleARKitOcclusionTexture> OcclusionMatteTexture = nullptr;`
- L131 _private member_ `TObjectPtr<UAppleARKitOcclusionTexture> OcclusionDepthTexture = nullptr;`
- L132 _private member_ `TObjectPtr<UARTextureCameraImage> CameraTexture = nullptr;`
- L133 _private member_ `TObjectPtr<UTexture> SceneDepthTexture = nullptr;`
- L134 _private member_ `TObjectPtr<UTexture> SceneDepthConfidenceTexture = nullptr;`
- L137 _private member_ `FVector2D UVOffsets[2] = { FVector2D::ZeroVector, FVector2D::ZeroVector };` — 0: landscape, 1: portrait

#### Free symbols / members of external scopes

- L21 _typedef_ `typedef TRefCountPtr<FRHIBuffer> FBufferRHIRef;`

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Private/ExternalTextureGuid.h` (Private)


#### Free symbols / members of external scopes

- L9 _externvar_ `extern const FGuid ARKitPassthroughCameraExternalTextureYGuid;` — GUID used to indicate that this external texture is the ARKit camera Y component. 0a417e66-bcda-4610-8594-92248c914a20
- L12 _externvar_ `extern const FGuid ARKitPassthroughCameraExternalTextureCbCrGuid;` — GUID used to indicate that this external texture is the ARKit camera CbCr component. d61a2708-55fe-4cb1-9cde-df2a9bb2a2d2
- L15 _externvar_ `extern const FGuid ARKitPassthroughCameraExternalTextureDepthGuid;` — GUID used to indicate that this external texture is the ARKit camera depth texture. cba06c09-03b2-4818-8913-6424d99acf28

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Private/ExternalTextureMaterialExpression.h` (Private)


#### enum `EARKitTextureType`  
`enum EARKitTextureType : int`  
_L11-15_
- reflection: `UENUM()`
- L13 _public enumerator_ `TextureY`
- L14 _public enumerator_ `TextureCbCr`

#### class `UDEPRECATED_MaterialExpressionARKitPassthroughCamera`  
`class UDEPRECATED_MaterialExpressionARKitPassthroughCamera : public UMaterialExpression`  
_L21-42_
- reflection: `UCLASS(collapsecategories, hidecategories = Object, Deprecated)`
- inherits: `UMaterialExpression`
- desc: Implements a node sampling from the ARKit Passthrough external textures.
- L26 _private member_ `FExpressionInput Coordinates;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstCoordinate' if not specified"))`
- L30 _private member_ `uint32 ConstCoordinate;` — `UPROPERTY(EditAnywhere, Category = UMaterialExpressionARKitPassthroughCamera)` — Only used if Coordinates is not hooked up
- L37 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L38 _private prototype_ `virtual int32 CompilePreview(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L39 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Public/AppleARKitAvailability.h` (Public)


#### class `FAppleARKitAvailability`  
`class FAppleARKitAvailability`  
_L82-125_
- L95 _public function_ `static bool SupportsARKit15()`
- L102 _public function_ `static bool SupportsARKit20()`
- L109 _public function_ `static bool SupportsARKit30()`
- L116 _public function_ `static bool SupportsARKit35()`
- L123 _public function_ `static bool SupportsARKit40()`

#### Free symbols / members of external scopes

- L15 _macro_ `#define SUPPORTS_ARKIT_1_0 1`
- L17 _macro_ `#define SUPPORTS_ARKIT_1_0 0`
- L22 _macro_ `#define SUPPORTS_ARKIT_1_5 1`
- L24 _macro_ `#define SUPPORTS_ARKIT_1_5 0`
- L29 _macro_ `#define SUPPORTS_ARKIT_2_0 1`
- L31 _macro_ `#define SUPPORTS_ARKIT_2_0 0`
- L36 _macro_ `#define SUPPORTS_ARKIT_3_0 1`
- L38 _macro_ `#define SUPPORTS_ARKIT_3_0 0`
- L43 _macro_ `#define SUPPORTS_ARKIT_3_5 1`
- L45 _macro_ `#define SUPPORTS_ARKIT_3_5 0`
- L50 _macro_ `#define SUPPORTS_ARKIT_4_0 1`
- L52 _macro_ `#define SUPPORTS_ARKIT_4_0 0`
- L66 _macro_ `#define ADD_ARKIT_SUPPORT_CHECK(ARKitVersion,iOSVersion) \`

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Public/AppleARKitConversion.h` (Public)


#### enum `EARSaveWorldVersions`  
`enum class EARSaveWorldVersions : uint8`  
_L25-30_
- L27 _public enumerator_ `Default = 1`
- L28 _public enumerator_ `AddAlignmentTransform = 2`
- L29 _public enumerator_ `Latest = AddAlignmentTransform`

#### struct `FARWorldSaveHeader`  
`struct FARWorldSaveHeader`  
_L32-53_
- L34 _public member_ `uint32 Magic;`
- L35 _public member_ `uint32 UncompressedSize;`
- L36 _public member_ `uint8 Version;`
- L38 _public function_ `FARWorldSaveHeader() : Magic(AR_SAVE_WORLD_KEY), UncompressedSize(0), Version((uint8)EARSaveWorldVersions::Latest)`
- L46 _public function_ `FARWorldSaveHeader(uint8* Header)`

#### struct `FAppleARKitConversion`  
`struct FAppleARKitConversion`  
_L57-338_
- L59 _public function_ `static inline float ToUEScale()`
- L64 _public function_ `static inline float ToARKitScale()`
- L76 _public function_ `static inline FTransform ToFTransform(const matrix_float4x4& RawYUpMatrix, const FRotator& AdjustBy = FRotator::ZeroRotator)` — Convert's an ARKit 'Y up' 'right handed' coordinate system transform to Unreal's 'Z up' 'left handed' coordinate system. Scale is removed because some ARKit transforms are less normalized than unreal requires.
- L109 _public function_ `static inline matrix_float4x4 ToARKitMatrix( const FTransform& InTransform, float WorldToMetersScale = 100.0f )` — Convert's an Unreal 'Z up' transform to ARKit's 'Y up' 'right handed' coordinate system 'left handed' coordinate system. Ignores scale.
- L141 _public function_ `static inline FVector ToFVector(const vector_float3& RawYUpVector)` — Convert's an ARKit 'Y up' 'right handed' coordinate system vector to Unreal's 'Z up' 'left handed' coordinate system.
- L150 _public function_ `static inline vector_float3 ToARKitVector( const FVector& InFVector, float WorldToMetersScale = 100.0f )` — Convert's an Unreal's 'Z up' to ARKit's 'Y up' vector 'left handed' coordinate system.
- L165 _public function_ `static inline FGuid ToFGuid( uuid_t UUID )`
- L172 _public function_ `static inline FGuid ToFGuid( NSUUID* Identifier )`
- L182 _public prototype_ `static ARWorldAlignment ToARWorldAlignment( const EARWorldAlignment& InWorldAlignment );`
- L187 _public function_ `static inline EARPlaneOrientation ToEARPlaneOrientation(ARPlaneAnchorAlignment Alignment)` — Coverts plane orientation
- L198 _public function_ `static inline EARObjectClassification ToEARObjectClassification(ARPlaneClassification Classification)`
- L232 _public function_ `static inline EARObjectClassification ToEARObjectClassification(ARMeshClassification Classification)`
- L285 _public prototype_ `static ARVideoFormat* ToARVideoFormat(const FARVideoFormat& DesiredFormat, NSArray<ARVideoFormat*>* Formats, bool bUseOptimalFormat);`
- L287 _public prototype_ `static FARVideoFormat FromARVideoFormat(ARVideoFormat* Format);`
- L289 _public prototype_ `static TArray<FARVideoFormat> FromARVideoFormatArray(NSArray<ARVideoFormat*>* Formats);`
- L291 _public prototype_ `static NSSet* InitImageDetection(UARSessionConfig* SessionConfig, TMap<FString, UARCandidateImage*>& CandidateImages, TMap<FString, CGImageRef>& ConvertedCandidateImages);`
- L293 _public prototype_ `static NSArray<ARVideoFormat*>* GetSupportedVideoFormats(EARSessionType SessionType);`
- L297 _public prototype_ `static void InitImageDetection(UARSessionConfig* SessionConfig, ARImageTrackingConfiguration* ImageConfig, TMap<FString, UARCandidateImage*>& CandidateImages, TMap<FString, CGImageRef>& ConvertedCandidateImages);`
- L299 _public prototype_ `static AREnvironmentTexturing ToAREnvironmentTexturing(EAREnvironmentCaptureProbeType CaptureType);`
- L301 _public prototype_ `static ARWorldMap* ToARWorldMap(const TArray<uint8>& WorldMapData, TOptional<FTransform>& AlignmentTransform);`
- L303 _public prototype_ `static NSSet* ToARReferenceObjectSet(const TArray<UARCandidateObject*>& CandidateObjects, TMap< FString, UARCandidateObject* >& CandidateObjectMap);`
- L306 _public prototype_ `static ARConfiguration* ToARConfiguration(UARSessionConfig* SessionConfig, TMap<FString, UARCandidateImage*>& CandidateImages, TMap<FString, CGImageRef>& ConvertedCandidateImages, TMap<FString, UARCandidateObject*>& CandidateObjects, TOptional<FTransform>& InitialAlignmentTransform);`
- L308 _public prototype_ `static void ConfigureSessionTrackingFeatures(UARSessionConfig* SessionConfig, ARConfiguration* SessionConfiguration);`
- L315 _public prototype_ `static bool IsSessionTrackingFeatureSupported(EARSessionType SessionType, EARSessionTrackingFeature SessionTrackingFeature);` — Helper function to check if a particular session feature is supported with the specified session type
- L316 _public prototype_ `static bool IsSceneReconstructionSupported(EARSessionType SessionType, EARSceneReconstruction SceneReconstructionMethod);`
- L318 _public function_ `static bool IsSessionTrackingFeatureSupported(EARSessionType SessionType, EARSessionTrackingFeature SessionTrackingFeature)`
- L319 _public function_ `static bool IsSceneReconstructionSupported(EARSessionType SessionType, EARSceneReconstruction SceneReconstructionMethod)`
- L323 _public prototype_ `static EARGeoTrackingState ToGeoTrackingState(ARGeoTrackingState InState);`
- L324 _public prototype_ `static EARGeoTrackingStateReason ToGeoTrackingStateReason(ARGeoTrackingStateReason InReason);`
- L325 _public prototype_ `static EARGeoTrackingAccuracy ToGeoTrackingAccuracy(ARGeoTrackingAccuracy InAccuracy);`
- L326 _public prototype_ `static EARAltitudeSource ToAltitudeSource(ARAltitudeSource InSource);`
- L330 _public prototype_ `static ARFrameSemantics ToARFrameSemantics(EARSessionTrackingFeature SessionTrackingFeature);`
- L331 _public prototype_ `static FARPose2D ToARPose2D(const ARBody2D* InARPose2D);`
- L332 _public prototype_ `static FARPose3D ToARPose3D(const ARBodyAnchor* InARBodyAnchor);`
- L333 _public prototype_ `static FARPose3D ToARPose3D(const ARSkeleton3D* InSkeleton3D, bool bIdentityForUntracked);`
- L336 _private prototype_ `static void ToSkeletonDefinition(const ARSkeletonDefinition* InARSkeleton, FARSkeletonDefinition& OutSkeletonDefinition);`

#### enum `EAppleAnchorType`  
`enum class EAppleAnchorType : uint8`  
_L341-353_
- L343 _public enumerator_ `Anchor`
- L344 _public enumerator_ `PlaneAnchor`
- L345 _public enumerator_ `FaceAnchor`
- L346 _public enumerator_ `ImageAnchor`
- L347 _public enumerator_ `EnvironmentProbeAnchor`
- L348 _public enumerator_ `ObjectAnchor`
- L349 _public enumerator_ `PoseAnchor`
- L350 _public enumerator_ `MeshAnchor`
- L351 _public enumerator_ `GeoAnchor`
- L352 _public enumerator_ `MAX`

#### struct `FAppleARKitAnchorData`  
`struct FAppleARKitAnchorData`  
_L355-493_
- L357 _public prototype_ `FAppleARKitAnchorData() = default;`
- L360 _public function_ `FAppleARKitAnchorData(FGuid InAnchorGuid, FTransform InTransform) : Transform( InTransform ) , AnchorType( EAppleAnchorType::Anchor ) , AnchorGUID( InAnchorGuid ) , bIsTracked(false)` — Generic Anchor
- L369 _public function_ `FAppleARKitAnchorData(FGuid InAnchorGuid, FTransform InTransform, FVector InCenter, FVector InExtent, EARPlaneOrientation InOrientation) : Transform( InTransform ) , AnchorType( EAppleAnchorType::PlaneAnchor ) , AnchorGUID( InAnchorGuid ) , Center(InCenter) , Extent(InExtent) , Orientation(InOrientation)` — Plane Anchor
- L380 _public function_ `FAppleARKitAnchorData(FGuid InAnchorGuid, FTransform InTransform, FARBlendShapeMap InBlendShapes, TArray<FVector> InFaceVerts, TArray<FVector2D> InFaceUVData, FTransform InLeftEyeTransform, FTransform InRightEyeTransform, FVector InLookAtTarget, const FTimecode& InTimecode, uint32 InFrameRate) : Transform( InTransform ) , AnchorType( EAppleAnchorType::FaceAnchor ) , AnchorGUID( InAnchorGuid ) , BlendShapes( MoveTemp(InBlendShapes) ) , FaceVerts( MoveTemp(InFaceVerts) ) , FaceUVData( MoveTemp(InFaceUVData) ) , LeftEyeTransform( InLeftEyeTransform ) , RightEyeTransform( InRightEyeTransform ) , LookAtTarget( InLookAtTarget ) , Timecode( InTimecode ) , FrameRate( InFrameRate )` — Face Anchor
- L396 _public function_ `FAppleARKitAnchorData(FGuid InAnchorGuid, FTransform InTransform, EAppleAnchorType InAnchorType, FString InDetectedAnchorName) : Transform( InTransform ) , AnchorType( InAnchorType ) , AnchorGUID( InAnchorGuid ) , DetectedAnchorName( MoveTemp(InDetectedAnchorName) )` — Image Anchor
- L405 _public function_ `FAppleARKitAnchorData(FGuid InAnchorGuid, FTransform InTransform, FVector InExtent, id<MTLTexture> InProbeTexture) : Transform( InTransform ) , AnchorType( EAppleAnchorType::EnvironmentProbeAnchor ) , AnchorGUID( InAnchorGuid ) , Extent(InExtent) , ProbeTexture(InProbeTexture)` — Probe Anchor
- L415 _public function_ `FAppleARKitAnchorData(FGuid InAnchorGuid, FTransform InTransform, FARPose3D InTrackedPose) : Transform( InTransform ) , AnchorType( EAppleAnchorType::PoseAnchor ) , AnchorGUID( InAnchorGuid ) , TrackedPose( MoveTemp(InTrackedPose) )` — Body Anchor
- L424 _public function_ `FAppleARKitAnchorData(FGuid InAnchorGuid, FTransform InTransform, FARKitMeshData::MeshDataPtr InMeshData) : Transform( InTransform ) , AnchorType( EAppleAnchorType::MeshAnchor ) , AnchorGUID( InAnchorGuid ) , MeshData( InMeshData )` — Mesh Anchor
- L433 _public function_ `FAppleARKitAnchorData(FGuid InAnchorGuid, FTransform InTransform, float InLongitude, float InLatitude, float InAltitudeMeters, EARAltitudeSource InAltitudeSource) : Transform( InTransform ) , AnchorType( EAppleAnchorType::GeoAnchor ) , AnchorGUID( InAnchorGuid ) , Longitude( InLongitude ) , Latitude( InLatitude ) , AltitudeMeters( InAltitudeMeters ) , AltitudeSource( InAltitudeSource )` — Geo Anchor
- L444 _public member_ `FTransform Transform = FTransform::Identity;`
- L445 _public member_ `EAppleAnchorType AnchorType = EAppleAnchorType::Anchor;`
- L446 _public member_ `FGuid AnchorGUID;`
- L447 _public member_ `FVector Center = FVector::ZeroVector;`
- L448 _public member_ `FVector Extent = FVector::ZeroVector;`
- L449 _public member_ `EARPlaneOrientation Orientation = EARPlaneOrientation::Horizontal;`
- L450 _public member_ `EARObjectClassification ObjectClassification = EARObjectClassification::NotApplicable;`
- L452 _public member_ `static bool bGenerateGeometry;` — Set by the session config to detemine whether to generate geometry or not
- L453 _public member_ `TArray<FVector> BoundaryVerts;`
- L454 _public member_ `TArray<FVector> Vertices;`
- L455 _public member_ `TArray<uint32> Indices;`
- L457 _public member_ `FARBlendShapeMap BlendShapes;`
- L458 _public member_ `TArray<FVector> FaceVerts;`
- L459 _public member_ `TArray<FVector2D> FaceUVData;`
- L461 _public member_ `static TArray<int32> FaceIndices;` — Note: the index buffer never changes so can be safely read once
- L463 _public member_ `FString DetectedAnchorName;`
- L465 _public member_ `id<MTLTexture> ProbeTexture = nullptr;`
- L467 _public member_ `FTransform LeftEyeTransform = FTransform::Identity;`
- L468 _public member_ `FTransform RightEyeTransform = FTransform::Identity;`
- L469 _public member_ `FVector LookAtTarget = FVector::ZeroVector;`
- L470 _public member_ `double Timestamp = 0.0;`
- L471 _public member_ `uint32 FrameNumber = 0;`
- L472 _public member_ `FTimecode Timecode;`
- L473 _public member_ `uint32 FrameRate = 0;`
- L476 _public member_ `bool bIsTracked = true;` — Only valid for tracked real world objects (face, images)
- L479 _public member_ `FARPose3D TrackedPose;` — Only valid if this is a body anchor
- L481 _public member_ `FARKitMeshData::MeshDataPtr MeshData;`
- L483 _public member_ `FString AnchorName;`
- L486 _public member_ `float Longitude = 0.f;` — Geo Anchor Properties
- L487 _public member_ `float Latitude = 0.f;`
- L488 _public member_ `float AltitudeMeters = 0.f;`
- L489 _public member_ `EARAltitudeSource AltitudeSource = EARAltitudeSource::Unknown;`
- L492 _public member_ `static TSharedPtr<FARPose3D> BodyRefPose;` — only need to be initialized once

#### Free symbols / members of external scopes

- L23 _macro_ `#define AR_SAVE_WORLD_KEY 0x505A474A`
- L55 _macro_ `#define AR_SAVE_WORLD_HEADER_SIZE (sizeof(FARWorldSaveHeader))`
- L496 _namespace_ `namespace ARKitUtil`
- L498 _function_ `static UARPin* PinFromComponent( const USceneComponent* Component, const TArray<UARPin*>& InPins )` (scope `ARKitUtil`)
- L511 _function_ `static TArray<UARPin*> PinsFromGeometry( const UARTrackedGeometry* Geometry, const TArray<UARPin*>& InPins )` (scope `ARKitUtil`)

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Public/AppleARKitFaceSupport.h` (Public)


#### class `IAppleARKitFaceSupport`  
`class IAppleARKitFaceSupport : public IModularFeature`  
_L22-84_
- inherits: `IModularFeature`
- L36 _public function_ `virtual TArray<TSharedPtr<FAppleARKitAnchorData>> MakeAnchorData(NSArray<ARAnchor*>* NewAnchors, const FRotator& AdjustBy, EARFaceTrackingUpdate UpdateSetting)` — Converts a set of generic ARAnchors into their face anchor equivalents without exposing the main code to the face APIs @param NewAnchors the list of anchors to convert to our intermediate format @param AdjustBy the additional rotation to apply to put the rotation in the proper space (camera alignment only) @param UpdateSetting whether to just update curves or geo too @return the set of face anchors to dispatch
- L47 _public function_ `virtual void PublishLiveLinkData(const FGuid& SessionGuid, TSharedPtr<FAppleARKitAnchorData> Anchor)` — Publishes any face AR data that needs to be sent to LiveLink. Done as a separate step because MakeAnchorData is called on an arbitrary thread and we can't access UObjects there safely @param SessionGuid the Guid of the session @param AnchorList the list of anchors to publish to LiveLink @return the set of face anchors to dispatch
- L55 _public function_ `virtual ARConfiguration* ToARConfiguration(UARSessionConfig* SessionConfig, UTimecodeProvider* InProvider)` — Creates a face ar specific configuration object if that is requested without exposing the main code to the face APIs @param SessionConfig the UE configuration object that needs processing @param InProvider the custom timecode provider to use
- L60 _public function_ `virtual bool DoesSupportFaceAR()` — @return whether this device supports face ar
- L66 _public function_ `virtual NSArray<ARVideoFormat*>* GetSupportedVideoFormats() const` — @return the supported video formats by the face ar device
- L73 _public function_ `virtual bool IsARFrameSemanticsSupported(ARFrameSemantics InSemantics) const` — @return If the desired frame semantics is supported by AR face tracking
- L77 _public prototype_ `virtual int32 GetNumberOfTrackedFacesSupported() const = 0;` — @return the max number of faces can be tracked at the same time
- L79 _public function_ `static FName GetModularFeatureName()`

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Public/AppleARKitMeshData.h` (Public)


#### class `FARKitMeshData`  
`class FARKitMeshData : public IMRMesh::FBrickDataReceipt`  
_L16-87_
- inherits: `IMRMesh::FBrickDataReceipt`
- desc: Represents a cached version of the data coming from an ARKit mesh anchor
- L19 _public prototype_ `~FARKitMeshData();`
- L21 _public typedef_ `typedef TSharedPtr<FARKitMeshData, ESPMode::ThreadSafe> MeshDataPtr;`
- L24 _public prototype_ `static void ClearAllMeshData();` — Clears the cached data for all the mesh anchors
- L27 _public prototype_ `static void RemoveMeshData(const FGuid& InGuid);` — Removes the cached data for a particular mesh anchor, identified by the GUID
- L30 _public prototype_ `static void UpdateMRMesh(const FTransform& MeshTransform, MeshDataPtr MeshData, UMRMeshComponent* InMeshComponent);` — Updates a MR mesh with the data cached in a particular mesh data object
- L33 _public prototype_ `static MeshDataPtr GetMeshData(const FGuid& InGuid);` — Returns the cached data for a particular mesh anchor, identified by the GUID
- L39 _public prototype_ `bool GetClassificationAtLocation(const FVector& InWorldLocation, const FTransform& InLocalToWorldTransform, uint8& OutClassification, FVector& OutClassificationLocation, float MaxLocationDiff);` — Gets the object classification for a location in the world space See UARBlueprintLibrary::GetObjectClassificationAtLocation
- L43 _public prototype_ `static TSharedPtr<FARKitMeshData, ESPMode::ThreadSafe> CacheMeshData(const FGuid& InGuid, ARMeshAnchor* InMeshAnchor);` — Grabs the data from the incoming mesh anchor and cache it in a data object
- L46 _private prototype_ `void UpdateMeshData(ARMeshAnchor* InMeshAnchor);`
- L47 _private prototype_ `void UpdateMeshData();`
- L48 _private prototype_ `void ClearData();`
- L51 _private member_ `ARMeshGeometry* PendingMeshGeometry = nullptr;` — The ARKit mesh geometry waiting to be processed
- L54 _private member_ `FCriticalSection PendingMeshLock;` — Lock protecting the access to PendingMeshGeometry
- L59 _private member_ `TArray<FVector3f> Vertices;` — Mesh vertices in the anchor's local space
- L62 _private member_ `TArray<FPackedNormal> TangentData;` — Mesh tangents in the anchor's local space
- L65 _private member_ `TArray<MRMESH_INDEX_TYPE> Indices;` — Mesh face indices
- L68 _private member_ `TArray<uint8> Classifications;` — Classification ID for each face, might be empty if mesh classification is not used
- L71 _private member_ `TArray<FVector2D> DummyUVData;` — Dummy UV data, filled with zeros
- L74 _private member_ `TArray<FColor> DummyColorData;` — Dummy color data, filled with zeros
- L77 _private member_ `FBox BoundingBox;` — Bounding box of the vertices, in the anchor's local space
- L80 _private member_ `TArray<FAccumulatedNormal> AccumulatedNormals;` — Temporary data used for calculating the normals from vertices
- L83 _private member_ `static TMap<FGuid, MeshDataPtr> CachedMeshData;` — Global cached mesh data records, one for each anchor
- L86 _private member_ `static FCriticalSection GlobalLock;` — Lock protecting the access to CachedMeshData

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Public/AppleARKitPoseTrackingLiveLink.h` (Public)


#### class `IAppleARKitPoseTrackingLiveLink`  
`class IAppleARKitPoseTrackingLiveLink : public IModularFeature`  
_L16-36_
- inherits: `IModularFeature`
- L28 _public function_ `virtual void PublishLiveLinkData(TSharedPtr<FAppleARKitAnchorData> Anchor)` — Publishes any body tracking AR data that needs to be sent to LiveLink. Done as a separate step because MakeAnchorData is called on an arbitrary thread and we can't access UObjects there safely @param AnchorList the list of anchors to publish to LiveLink @return the set of body tracking anchors to dispatch
- L30 _public function_ `virtual const TArray<FTransform>* GetRefPoseTransforms() const`
- L31 _public function_ `static FName GetModularFeatureName()`

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Public/AppleARKitSettings.h` (Public)


#### enum `EARFaceTrackingFileWriterType`  
`enum class EARFaceTrackingFileWriterType : uint8`  
_L17-25_
- reflection: `UENUM(BlueprintType, Category="AR AugmentedReality", meta=(Experimental))`
- L20 _public enumerator_ `None` — Disables creation of a file writer
- L22 _public enumerator_ `CSV` — Comma delimited file, one row per captured frame
- L24 _public enumerator_ `JSON` — JSON object array, one frame object per captured frame

#### enum `ELivelinkTrackingType`  
`enum class ELivelinkTrackingType : uint8`  
_L28-32_
- reflection: `UENUM(BlueprintType, Category="AR AugmentedReality")`
- L30 _public enumerator_ `FaceTracking`
- L31 _public enumerator_ `PoseTracking`

#### class `UAppleARKitSettings`  
`class UAppleARKitSettings : public UObject, public FSelfRegisteringExec`  
_L36-174_
- reflection: `UCLASS(Config=Engine, defaultconfig)`
- inherits: `UObject,FSelfRegisteringExec`
- L43 _public function_ `UAppleARKitSettings() : bRequireARKitSupport(true) , bFaceTrackingLogData(false) , bFaceTrackingWriteEachFrame(false) , FaceTrackingFileWriterType(EARFaceTrackingFileWriterType::None) , bShouldWriteCameraImagePerFrame(false) , WrittenCameraImageScale(1.f) , WrittenCameraImageQuality(85) , LiveLinkPublishingPort(11111) , DefaultFaceTrackingLiveLinkSubjectName(FName("iPhoneXFaceAR")) , DefaultPoseTrackingLiveLinkSubjectName(FName("PoseTracking")) , DefaultFaceTrackingDirection(EARFaceTrackingDirection::FaceRelative) , bAdjustThreadPrioritiesDuringARSession(false) , GameThreadPriorityOverride(47) , RenderThreadPriorityOverride(45) , ARKitTimecodeProvider(TEXT("/Script/AppleARKit.AppleARKitTimecodeProvider"))`
- L63 _public prototype_ `static UTimecodeProvider* GetTimecodeProvider();`
- L64 _public prototype_ `static void CreateFaceTrackingLogDir();`
- L65 _public prototype_ `static void CreateImageLogDir();`
- L68 _public prototype_ `FString GetFaceTrackingLogDir();` — Accessors to the properties
- L69 _public prototype_ `bool IsLiveLinkEnabledForFaceTracking();`
- L70 _public prototype_ `bool IsLiveLinkEnabledForPoseTracking();`
- L71 _public prototype_ `bool IsFaceTrackingLoggingEnabled();`
- L72 _public prototype_ `bool ShouldFaceTrackingLogPerFrame();`
- L73 _public prototype_ `EARFaceTrackingFileWriterType GetFaceTrackingFileWriterType();`
- L74 _public prototype_ `bool ShouldWriteCameraImagePerFrame();`
- L75 _public prototype_ `float GetWrittenCameraImageScale();`
- L76 _public prototype_ `int32 GetWrittenCameraImageQuality();`
- L77 _public prototype_ `ETextureRotationDirection GetWrittenCameraImageRotation();`
- L78 _public prototype_ `int32 GetLiveLinkPublishingPort();`
- L79 _public prototype_ `FName GetFaceTrackingLiveLinkSubjectName();`
- L80 _public prototype_ `FName GetPoseTrackingLiveLinkSubjectName();`
- L81 _public prototype_ `EARFaceTrackingDirection GetFaceTrackingDirection();`
- L82 _public prototype_ `bool ShouldAdjustThreadPriorities();`
- L83 _public prototype_ `int32 GetGameThreadPriorityOverride();`
- L84 _public prototype_ `int32 GetRenderThreadPriorityOverride();`
- L88 _protected prototype_ `virtual bool Exec_Runtime(UWorld*, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L93 _protected member_ `bool bRequireARKitSupport;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings", meta=(ToolTip="When True the project can only be installed on devices that support ARKit."))` — Where to write the curve files and image files
- L96 _protected member_ `FString FaceTrackingLogDir;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")`
- L100 _protected member_ `TArray<ELivelinkTrackingType> LivelinkTrackingTypes;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")` — Livelink tracking type. To publish face blend shapes, or body pose data to LiveLink, or none
- L104 _protected member_ `bool bFaceTrackingLogData;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")` — Whether file writing is enabled at all or not
- L108 _protected member_ `bool bFaceTrackingWriteEachFrame;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")` — Whether to publish each frame or when the "FaceAR WriteCurveFile
- L112 _protected member_ `EARFaceTrackingFileWriterType FaceTrackingFileWriterType;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")` — The type of face AR publisher that writes to disk to create
- L116 _protected member_ `bool bShouldWriteCameraImagePerFrame;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")` — Whether to publish the camera image each frame
- L120 _protected member_ `float WrittenCameraImageScale;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")` — The scale to write the images at. Used to reduce data footprint
- L124 _protected member_ `int32 WrittenCameraImageQuality;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")` — The quality setting to generate the jpeg images at. Defaults to 85, which is "high quality". Lower values reduce data footprint
- L128 _protected member_ `ETextureRotationDirection WrittenCameraImageRotation;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")` — Defaults to none. Use Right when in portrait mode
- L132 _protected member_ `int32 LiveLinkPublishingPort;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")` — The port to use when listening/sending LiveLink face blend shapes via the network
- L142 _protected member_ `FName DefaultFaceTrackingLiveLinkSubjectName;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")` — The default name to use when publishing face tracking name If multiple faces are tracked, the subject name for the faces will be: #1: DefaultFaceTrackingLiveLinkSubjectName #2: DefaultFaceTrackingLiveLinkSubjectName-1 #3: DefaultFaceTrackingLiveLinkSubjectName-2, etc
- L146 _protected member_ `FName DefaultPoseTrackingLiveLinkSubjectName;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")` — The default name to use when publishing pose tracking name
- L150 _protected member_ `EARFaceTrackingDirection DefaultFaceTrackingDirection;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")` — The default tracking to use when tracking face blend shapes (face relative or mirrored). Defaults to face relative
- L154 _protected member_ `bool bAdjustThreadPrioritiesDuringARSession;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")` — Whether to adjust thread priorities during an AR session or not
- L158 _protected member_ `int32 GameThreadPriorityOverride;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")` — The game thread priority to change to when an AR session is running, default is 47
- L162 _protected member_ `int32 RenderThreadPriorityOverride;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")` — The render thread priority to change to when an AR session is running, default is 45
- L169 _protected member_ `FString ARKitTimecodeProvider;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="AR Settings")` — Used to specify the timecode provider to use when identifying when an update occurred. Useful when using external timecode generators to sync multiple devices/machines
- L173 _private member_ `FCriticalSection CriticalSection;` — Used because these defaults need to be read on multiple threads

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Public/AppleARKitTextures.h` (Public)


#### struct `FImageBlurParams`  
`struct FImageBlurParams`  
_L23-30_
- desc: Parameters used to scale and blur an image
- L26 _public member_ `float GaussianBlurSigma = 0.f;` — Sigma for the gaussian blur operation
- L29 _public member_ `float ImageSizeScale = 1.f;` — Scale applied to the original image before it's blurred

#### class `UAppleARKitTextureCameraImage`  
`class UAppleARKitTextureCameraImage : public UARTextureCameraImage, public IAppleImageInterface`  
_L33-62_
- reflection: `UCLASS(NotBlueprintType)`
- inherits: `UARTextureCameraImage,IAppleImageInterface`
- L41 _public prototype_ `virtual void BeginDestroy() override;` — UTexture interface implementation
- L42 _public prototype_ `virtual FTextureResource* CreateResource() override;`
- L43 _public function_ `virtual EMaterialValueType GetMaterialType() const override`
- L46 _public function_ `virtual EAppleTextureType GetTextureType() const override`
- L49 _public prototype_ `void UpdateCameraImage(float InTimestamp, CVPixelBufferRef InCameraImage, EPixelFormat InPixelFormat, const CFStringRef ColorSpace = kCGColorSpaceGenericRGBLinear, FImageBlurParams BlurParams = {});`
- L52 _public function_ `CVPixelBufferRef GetCameraImage() const` — Returns the cached camera image. You must retain this if you hold onto it
- L55 _public function_ `virtual CVPixelBufferRef GetPixelBuffer() const override` — IAppleImageInterface interface implementation
- L60 _private member_ `CVPixelBufferRef CameraImage = nullptr;` — The Apple specific representation of the ar camera image

#### class `UAppleARKitTextureCameraDepth`  
`class UAppleARKitTextureCameraDepth : public UARTextureCameraDepth`  
_L65-90_
- reflection: `UCLASS(NotBlueprintType)`
- inherits: `UARTextureCameraDepth`
- L72 _public prototype_ `virtual void BeginDestroy() override;` — UTexture interface implementation
- L73 _public prototype_ `virtual FTextureResource* CreateResource() override;`
- L74 _public function_ `virtual EMaterialValueType GetMaterialType() const override`
- L79 _public prototype_ `virtual void Init(float InTimestamp, AVDepthData* InCameraDepth);` — Sets any initialization data
- L84 _public function_ `AVDepthData* GetCameraDepth()` — Returns the cached camera depth. You must retain this if you hold onto it
- L88 _private member_ `AVDepthData* CameraDepth = nullptr;` — The Apple specific representation of the ar depth image

#### class `UAppleARKitEnvironmentCaptureProbeTexture`  
`class UAppleARKitEnvironmentCaptureProbeTexture : public UAREnvironmentCaptureProbeTexture, public IAppleImageInterface`  
_L93-121_
- reflection: `UCLASS(NotBlueprintType)`
- inherits: `UAREnvironmentCaptureProbeTexture,IAppleImageInterface`
- L102 _public prototype_ `virtual void BeginDestroy() override;` — UTexture interface implementation
- L103 _public prototype_ `virtual FTextureResource* CreateResource() override;`
- L104 _public function_ `virtual EMaterialValueType GetMaterialType() const override`
- L107 _public function_ `virtual EAppleTextureType GetTextureType() const override`
- L111 _public prototype_ `virtual void Init(float InTimestamp, id<MTLTexture> InEnvironmentTexture);` — Sets any initialization data
- L114 _public function_ `virtual id<MTLTexture> GetMetalTexture() const override` — IAppleImageInterface interface implementation
- L119 _private member_ `id<MTLTexture> MetalTexture = nullptr;` — The Apple specific representation of the ar environment texture

#### class `UAppleARKitOcclusionTexture`  
`class UAppleARKitOcclusionTexture : public UARTexture, public IAppleImageInterface`  
_L124-151_
- reflection: `UCLASS(NotBlueprintType)`
- inherits: `UARTexture,IAppleImageInterface`
- L132 _public prototype_ `virtual void BeginDestroy() override;` — UTexture interface implementation
- L133 _public prototype_ `virtual FTextureResource* CreateResource() override;`
- L134 _public function_ `virtual EMaterialValueType GetMaterialType() const override`
- L137 _public function_ `virtual EAppleTextureType GetTextureType() const override`
- L140 _public prototype_ `void SetMetalTexture(float InTimestamp, id<MTLTexture> InMetalTexture, EPixelFormat PixelFormat, const CFStringRef ColorSpace = kCGColorSpaceGenericRGBLinear);`
- L143 _public prototype_ `virtual id<MTLTexture> GetMetalTexture() const override;` — IAppleImageInterface interface implementation
- L148 _private member_ `id<MTLTexture> MetalTexture = nullptr;` — The Apple specific representation of the ar camera image
- L149 _private member_ `mutable FCriticalSection MetalTextureLock;`

#### class `UAppleARKitCameraVideoTexture`  
`class UAppleARKitCameraVideoTexture : public UARTextureCameraImage, public IAppleImageInterface`  
_L154-172_
- reflection: `UCLASS(NotBlueprintType)`
- inherits: `UARTextureCameraImage,IAppleImageInterface`
- L160 _public prototype_ `virtual FTextureResource* CreateResource() override;` — UTexture interface implementation
- L161 _public function_ `virtual EMaterialValueType GetMaterialType() const override`
- L164 _public prototype_ `void Init();`
- L165 _public prototype_ `void UpdateFrame(const FAppleARKitFrame& InFrame);`
- L167 _public function_ `virtual EAppleTextureType GetTextureType() const override`
- L170 _public prototype_ `virtual id<MTLTexture> GetMetalTexture() const override;`
