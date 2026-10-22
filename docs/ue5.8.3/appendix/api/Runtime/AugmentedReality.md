# Runtime / AugmentedReality

- module root: `Source/Runtime/AugmentedReality`
- headers: 26; symbols: 1300
- symbol kinds: class=63, delegate=26, enum=42, enumerator=230, function=108, macro=25, member=290, namespace=1, prototype=489, struct=22, typedef=4
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, EngineSettings, RHI, RenderCore, UnrealEd
- PublicDependencyModuleNames: MRMesh
- PublicIncludePathModuleNames: HeadMountedDisplay

### `Source/Runtime/AugmentedReality/Private/ARDebugDrawHelpers.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ARDebugHelpers`
- L13 _prototype_ `void DrawDebugString(const UWorld* InWorld, FVector const& TextLocation, const FString& Text, float Scale, FColor const& TextColor, float Duration, bool bDrawShadow);` (scope `ARDebugHelpers`)

### `Source/Runtime/AugmentedReality/Private/AugmentedRealityModule.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAR, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAR, Log, All);`
- L9 _delegate_ `DECLARE_STATS_GROUP(TEXT("AR"), STATGROUP_AR, STATCAT_Advanced`

### `Source/Runtime/AugmentedReality/Public/ARActor.h` (Public)


#### class `AARActor`  
`class AARActor: public AActor`  
_L15-27_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Experimental, Category="AR Gameplay")`
- inherits: `AActor`
- L20 _public prototype_ `AARActor();`
- L23 _public prototype_ `UARComponent* AddARComponent(TSubclassOf<UARComponent> InComponentClass, const FGuid& NativeID);` — `UFUNCTION(BlueprintCallable, Category="AR Gameplay")`
- L25 _public prototype_ `static void RequestSpawnARActor(FGuid NativeID, UClass* InComponentClass);`
- L26 _public prototype_ `static void RequestDestroyARActor(AARActor* InActor);`

#### struct `FTrackedGeometryGroup`  
`struct FTrackedGeometryGroup`  
_L30-47_
- reflection: `USTRUCT()`
- L35 _public prototype_ `FTrackedGeometryGroup() = default;`
- L37 _public prototype_ `FTrackedGeometryGroup(UARTrackedGeometry* InTrackedGeometry);`
- L40 _public member_ `TObjectPtr<AARActor> ARActor = nullptr;` — `UPROPERTY()`
- L43 _public member_ `TObjectPtr<UARComponent> ARComponent = nullptr;` — `UPROPERTY()`
- L46 _public member_ `TObjectPtr<UARTrackedGeometry> TrackedGeometry = nullptr;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUGMENTEDREALITY_API`

### `Source/Runtime/AugmentedReality/Public/ARBlueprintLibrary.h` (Public)


#### class `UARBlueprintLibrary`  
`class UARBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L52-430_
- reflection: `UCLASS(MinimalAPI, meta=(ScriptName="ARLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L63 _public prototype_ `static bool IsARSupported();` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Session", meta = (DisplayName="Is AR Supported", Keywords = "ar augmentedreality augmented reality session start run running"))` — Checks if the current device can support AR
- L71 _public prototype_ `static void StartARSession(UARSessionConfig* SessionConfig);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Session", meta = (DisplayName="Start AR Session", Keywords = "ar augmentedreality augmented reality session start run running"))` — Begin a new Augmented Reality session. Subsequently, use the \c GetARSessionStatus() function to figure out the status of the session. @param SessionConfig    Describes the tracking method to use, what kind of geometry to detect in the world, etc.
- L75 _public prototype_ `static void PauseARSession();` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Session", meta = (DisplayName="Pause AR Session", Keywords = "ar augmentedreality augmented reality session stop run running"))` — Pause a running Augmented Reality session without clearing existing state.
- L79 _public prototype_ `static void StopARSession();` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Session", meta = (DisplayName="Stop AR Session", Keywords = "ar augmentedreality augmented reality session stop run running"))` — Stop a running Augmented Reality session and clear any state.
- L88 _public prototype_ `static FARSessionStatus GetARSessionStatus();` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Session", meta = (DisplayName="Get AR Session Status", Keywords = "ar augmentedreality augmented reality session start stop run running"))` — It is intended that you check the status of the Augmented Reality session on every frame and take action accordingly. e.g. if the session stopped for an unexpected reason, you might give the user a prompt to re-start the session @return The status of a current Augmented Reality session: e.g. Running or Not running for a specific reason.
- L92 _public prototype_ `static UARSessionConfig* GetSessionConfig();` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Session", meta = (DisplayName="Get AR Session Config", Keywords = "ar augmentedreality augmented reality session"))` — @return the configuration that the current session was started with.
- L96 _public prototype_ `static bool ToggleARCapture(const bool bOnOff, const EARCaptureType CaptureType);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Session", meta = (Keywords = "ar augmentedreality augmented reality capture start stop"))` — Starts or stops a battery intensive service on device.
- L100 _public prototype_ `static void SetEnabledXRCamera(bool bOnOff);` — `UFUNCTION(BlueprintCallable, Category = "AR", meta = (Keywords = "ar all"))` — Enable or disable Mixed Reality Capture camera.
- L104 _public prototype_ `static FIntPoint ResizeXRCamera(const FIntPoint& InSize);` — `UFUNCTION(BlueprintCallable, Category = "AR", meta = (Keywords = "ar all"))` — Change screen size of Mixed Reality Capture camera.
- L120 _public prototype_ `static void SetAlignmentTransform( const FTransform& InAlignmentTransform );` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Alignment", meta = (DisplayName="Set AR Alignment Transform", Keywords = "ar augmentedreality augmented reality tracking alignment"))` — Set a transform that will be applied to the tracking space. This effectively moves any camera possessed by the Augmented Reality system such that it is pointing at a different spot in Unreal's World Space. This is often done to support AR scenarios that rely on static geometry and/or lighting. Note: any movable components that are pinned will appear to stay in place, while anything not pinned or is not movable (static or stationary) will appear to move. \see PinComponent \see PinComponentToTraceResult
- L131 _public prototype_ `static TArray<FARTraceResult> LineTraceTrackedObjects( const FVector2D ScreenCoord, bool bTestFeaturePoints = true, bool bTestGroundPlane = true, bool bTestPlaneExtents = true, bool bTestPlaneBoundaryPolygon = true );` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Trace Result", meta = (AdvancedDisplay="1", Keywords = "ar augmentedreality augmented reality tracking tracing linetrace"))` — Perform a line trace against any real-world geometry as tracked by the AR system. @param ScreenCoord	         Coordinate of the point on the screen from which to cast a ray into the tracking space. @return a list of \c FARTraceResult sorted by distance from camera.
- L142 _public prototype_ `static TArray<FARTraceResult> LineTraceTrackedObjects3D(const FVector Start, const FVector End, bool bTestFeaturePoints = true, bool bTestGroundPlane = true, bool bTestPlaneExtents = true, bool bTestPlaneBoundaryPolygon = true);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Trace Result", meta = (AdvancedDisplay = "1", Keywords = "ar augmentedreality augmented reality tracking tracing linetrace"))` — Perform a line trace against any real-world geometry as tracked by the AR system. @param Start					Start point of the trace, in world space. @param End					End point of the trace, in world space. @return a list of \c FARTraceResult sorted by distance from camera.
- L146 _public prototype_ `static EARTrackingQuality GetTrackingQuality();` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Tracking", meta = (DisplayName="Get AR Tracking Quality", Keywords = "ar augmentedreality augmented reality tracking quality"))` — @return how well the tracking system is performing at the moment
- L150 _public prototype_ `static EARTrackingQualityReason GetTrackingQualityReason();` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Tracking", meta = (DisplayName="Get AR Tracking Quality Reason", Keywords = "ar augmentedreality augmented reality tracking quality reason"))` — @return The reason for the current limited tracking state
- L154 _public prototype_ `static TArray<UARTrackedGeometry*> GetAllGeometries();` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Tracking", meta = (DisplayName="Get All AR Geometries", Keywords = "ar augmentedreality augmented reality tracking geometry anchor"))` — @return a list of all the real-world geometry as currently seen by the Augmented Reality system
- L158 _public prototype_ `static TArray<UARTrackedGeometry*> GetAllGeometriesByClass(TSubclassOf<UARTrackedGeometry> GeometryClass);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Tracking", meta = (DisplayName="Get All AR Geometries By Class", Keywords = "ar augmentedreality augmented reality tracking geometry anchor", DeterminesOutputType = "GeometryClass"))` — @return a list of all the real-world geometry of the specified class as currently seen by the Augmented Reality system
- L162 _public prototype_ `static UARTexture* GetARTexture(EARTextureType TextureType);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Texture", meta = (DisplayName="Get AR Texture", Keywords = "ar augmentedreality augmented reality texture"))` — @return the AR texture for the specified type
- L169 _public prototype_ `static bool IsSessionTypeSupported(EARSessionType SessionType);` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Tracking", meta = (DisplayName="Is AR Session Type Supported", Keywords = "ar augmentedreality augmented reality tracking"))` — Test whether this type of session is supported by the current Augmented Reality platform. e.g. is your device capable of doing positional tracking or orientation only?
- L174 _public prototype_ `static void DebugDrawTrackedGeometry( UARTrackedGeometry* TrackedGeometry, UObject* WorldContextObject, FLinearColor Color = FLinearColor(1.0f, 1.0f, 0.0f, 0.75f), float OutlineThickness=5.0f, float PersistForSeconds = 0.0f );` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Debug", meta = (WorldContext = "WorldContextObject", AdvancedDisplay="1", Keywords = "ar augmentedreality augmented reality tracked geometry debug draw"))` — Given some real-world geometry being tracked by the Augmented Reality system, draw it on the screen for debugging purposes (rudimentary)
- L178 _public prototype_ `static void DebugDrawPin( UARPin* ARPin, UObject* WorldContextObject, FLinearColor Color = FLinearColor(1.0f, 1.0f, 0.0f, 0.75f), float Scale=5.0f, float PersistForSeconds = 0.0f );` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Debug", meta = (WorldContext = "WorldContextObject", AdvancedDisplay="1", Keywords = "ar augmentedreality augmented reality pin debug draw"))` — Given a \c UARPin, draw it for debugging purposes.
- L191 _public prototype_ `static UARLightEstimate* GetCurrentLightEstimate();` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Light Estimate")` — An AugmentedReality session can be configured to provide light estimates. The specific approach to light estimation can be configured by the \c UARSessionConfig specified during \c StartARSession(). This function assumes that you will cast the returned \c UARLightEstimate to a derived type corresponding to your session config. @return a \c UARLighEstimate that can be cast to a derived class.
- L210 _public prototype_ `static UARPin* PinComponent( USceneComponent* ComponentToPin, const FTransform& PinToWorldTransform, UARTrackedGeometry* TrackedGeometry = nullptr, const FName DebugName = NAME_None );` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|ARPin", meta = (AdvancedDisplay="3", Keywords = "ar augmentedreality augmented reality tracking arpin tracked geometry pinning anchor"))` — Pin an Unreal Component to a location in tracking spce (i.e. the real world). @param ComponentToPin         The component that should be pinned. @param PinToWorldTransform    A transform (in Unreal World Space) that corresponds to a physical location where the component should be pinned. @param TrackedGeometry        An optional, real-world geometry that is recognized by the AR system; any correction to the position of this geometry will be applied to the pinned component. @param DebugName              An optional name that will be displayed when this pin is being drawn for debugging purposes. @return an object representing the pin that connects \c ComponentToPin component to a real-world location and optionally to the \c TrackedGeometry.
- L217 _public prototype_ `static UARPin* PinComponentToTraceResult( USceneComponent* ComponentToPin, const FARTraceResult& TraceResult, const FName DebugName = NAME_None );` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|ARPin", meta = (AdvancedDisplay="2", Keywords = "ar augmentedreality augmented reality tracking arpin tracked geometry pinning anchor"))` — A convenient version of \c PinComponent() that can be used in conjunction with a result of a \c LineTraceTrackedObjects call.
- L228 _public prototype_ `static bool PinComponentToARPin(USceneComponent* ComponentToPin, UARPin* Pin);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|ARPin", meta = (Keywords = "ar augmentedreality augmented reality tracking arpin tracked geometry pinning anchor"))` — Associate a component with an ARPin, so that its transform will be updated by the pin.  Any previously associated component will be detached. @param ComponentToPin	The Component which will be updated by the Pin. @param Pin				The Pin which the component will be updated by. @return					True if the operation was successful.
- L232 _public prototype_ `static void UnpinComponent( USceneComponent* ComponentToUnpin );` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|ARPin", meta = (Keywords = "ar augmentedreality augmented reality tracking arpin tracked geometry pinning anchor"))` — Given a pinned \c ComponentToUnpin, remove its attachment to the real world.
- L236 _public prototype_ `static void RemovePin( UARPin* PinToRemove );` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|ARPin", meta = (Keywords = "ar augmentedreality augmented reality tracking arpin tracked geometry pinning anchor"))` — Remove a pin such that it no longer updates the associated component.
- L240 _public prototype_ `static TArray<UARPin*> GetAllPins();` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|ARPin", meta = (Keywords = "ar augmentedreality augmented reality tracking arpin anchor"))` — Get a list of all the \c UARPin objects that the Augmented Reality session is currently using to connect virtual objects to real-world, tracked locations.
- L248 _public prototype_ `static bool IsARPinLocalStoreSupported();` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|ARPin", meta = (Keywords = "ar augmentedreality augmented reality tracking arpin anchor LocalStore"))` — Is ARPin Local Store Supported @return					True if Local Pin saving is supported by the device/platform.
- L256 _public prototype_ `static bool IsARPinLocalStoreReady();` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|ARPin", meta = (Keywords = "ar augmentedreality augmented reality tracking arpin anchor LocalStore"))` — Is ARPin Local Store Ready @return					True if local store is ready for use.
- L265 _public prototype_ `static TMap<FName, UARPin*> LoadARPinsFromLocalStore();` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|ARPin", meta = (Keywords = "ar augmentedreality augmented reality tracking arpin anchor LocalStore"))` — Load all ARPins from local save Note: Multiple loads of a saved pin may result in duplicate pins OR overwritten pins.  It is reccomended to only load once. @return					Map of SaveName:ARPin.
- L275 _public prototype_ `static bool SaveARPinToLocalStore(FName InSaveName, UARPin* InPin);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|ARPin", meta = (Keywords = "ar augmentedreality augmented reality tracking arpin anchor LocalStore"))` — Save an ARPin to local store @param InName			The save name for the pin. @param InPin				The ARPin which will be saved to the local store. @return					True if saved successfully.
- L282 _public prototype_ `static void RemoveARPinFromLocalStore(FName InSaveName);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|ARPin", meta = (Keywords = "ar augmentedreality augmented reality tracking arpin anchor LocalStore"))` — Remove an ARPin from the local store @param InName			The save name to remove.
- L288 _public prototype_ `static void RemoveAllARPinsFromLocalStore();` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|ARPin", meta = (Keywords = "ar augmentedreality augmented reality tracking arpin anchor LocalStore"))` — Remove all ARPins from the local store
- L292 _public prototype_ `static bool AddManualEnvironmentCaptureProbe(FVector Location, FVector Extent);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Tracking", meta = (DisplayName="Add AR Environment Probe", Keywords = "ar augmentedreality augmented reality tracking anchor"))` — Adds an environment capture probe to the ar world
- L296 _public prototype_ `static EARWorldMappingState GetWorldMappingStatus();` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Tracking", meta = (DisplayName="Get AR World Mapping Status", Keywords = "ar augmentedreality augmented reality tracking anchor"))` — @return the current world mapping status for the AR world
- L300 _public prototype_ `static TArray<FVector> GetPointCloud();` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Tracking", meta = (DisplayName="Get AR Point Cloud", Keywords = "ar augmentedreality augmented reality tracking point cloud"))` — @return the raw point cloud view of the AR scene
- L304 _public prototype_ `static TArray<FARVideoFormat> GetSupportedVideoFormats(EARSessionType SessionType);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Capabilities", meta = (DisplayName="Get Supported AR Video Formats", Keywords = "ar augmentedreality augmented reality config video formats"))` — @return The list of supported video formats for this device
- L306 _public prototype_ `static TSharedPtr<FARSaveWorldAsyncTask, ESPMode::ThreadSafe> SaveWorld();`
- L307 _public prototype_ `static TSharedPtr<FARGetCandidateObjectAsyncTask, ESPMode::ThreadSafe> GetCandidateObject(FVector Location, FVector Extent);`
- L322 _public prototype_ `static UARCandidateImage* AddRuntimeCandidateImage(UARSessionConfig* SessionConfig, UTexture2D* CandidateTexture, FString FriendlyName, float PhysicalWidth);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Session", meta = (Keywords = "ar augmentedreality augmented reality candidate image"))` — Create an ARCandidateImage object and add it to the ARCandidateImageList of the given \c UARSessionConfig object. Note that you need to restart the AR session with the \c UARSessionConfig you are adding to to make the change take effect. On ARCore platform, you can leave the PhysicalWidth to 0 if you don't know the physical size of the image or the physical size is dynamic. And this function takes time to perform non-trivial image processing (20ms - 30ms), and should be run on a background thread. @return A \c UARCandidateImage Object pointer if the underlying ARPlatform added the candidate image at runtime successfully. Return nullptr otherwise.
- L326 _public prototype_ `static bool IsSessionTrackingFeatureSupported(EARSessionType SessionType, EARSessionTrackingFeature SessionTrackingFeature);` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Session", meta = (DisplayName="Is AR Session Tracking Feature Supported", Keywords = "ar augmentedreality augmented reality session tracking feature"))` — @return if a particular session feature is supported with the specified session type on the current platform
- L330 _public prototype_ `static bool IsSceneReconstructionSupported(EARSessionType SessionType, EARSceneReconstruction SceneReconstructionMethod);` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Session", meta = (DisplayName="Is AR Scene Reconstruction Supported", Keywords = "ar augmentedreality augmented reality session scene reconstruction"))` — @return if a particular scene reconstruction method is supported with the specified session type on the current platform
- L334 _public prototype_ `static TArray<FARPose2D> GetAllTracked2DPoses();` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Pose Tracking", meta = (DisplayName="Get All AR Tracked 2D Poses", Keywords = "ar augmentedreality augmented reality pose tracking"))` — @return all the 2D poses tracked by the AR system
- L345 _public prototype_ `static bool GetObjectClassificationAtLocation(const FVector& InWorldLocation, EARObjectClassification& OutClassification, FVector& OutClassificationLocation, float MaxLocationDiff = 10.f);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Classification")` — Try to determine the classification of the object at a world space location @InWorldLocation: the world location where the classification is needed @OutClassification: the classification result @OutClassificationLocation: the world location at where the classification is calculated @MaxLocationDiff: the max distance between the specified world location and the classification location @return: whether a valid classification result is calculated
- L354 _public prototype_ `static void SetARWorldOriginLocationAndRotation(FVector OriginLocation, FRotator OriginRotation, bool bIsTransformInWorldSpace = true, bool bMaintainUpDirection = true);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Alignment", meta = (DisplayName="Set AR World Origin Location and Rotation", Keywords = "ar augmentedreality augmented reality world origin"))` — For a point P in the AR local space, whose location and rotation are "OriginLocation" and "OriginRotation" in the world space modify the alignment transform so that the same point P will be transformed to the origin in the world space. @bIsTransformInWorldSpace: whether "OriginLocation" and "OriginRotation" are specified in UE4's world space or AR system's local space. @bMaintainUpDirection: if set, only the yaw roation of the alignment transform will be modified, pitch and roll will be zeroed out.
- L362 _public prototype_ `static void SetARWorldScale(float InWorldScale);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Alignment", meta = (DisplayName="Set AR World Scale", Keywords = "ar augmentedreality augmented reality world scale"))` — Helper function that modifies the alignment transform scale so that virtual content in the world space appears to be "scaled". Note that ultimately the scaling effect is achieved through modifying the translation of the camera: moving the camera further away from the origin makes objects appear to be smaller, and vice versa.
- L366 _public prototype_ `static float GetARWorldScale();` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Alignment", meta = (DisplayName="Get AR World Scale", Keywords = "ar augmentedreality augmented reality world scale"))` — @return the AR world scale, see "SetARWorldScale"
- L370 _public prototype_ `static FTransform GetAlignmentTransform();` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Alignment", meta = (DisplayName="Get Alignment Transform", Keywords = "ar augmentedreality augmented reality alignment transform"))` — @return the alignment transform, see "SetAlignmentTransform"
- L381 _public prototype_ `static bool AddTrackedPointWithName(const FTransform& WorldTransform, const FString& PointName, bool bDeletePointsWithSameName = true);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality", meta = (Keywords = "ar augmentedreality augmented reality add point"))` — Manually add a tracked point with name and world transform. @WorldTransform: transform in the world space where the point should be created. @PointName: the name of the created point, must be non-empty. @bDeletePointsWithSameName: if existing points with the same name should be deleted. @return if the operation succeeds. Note that this is an async operation - the added point won't be available until a few frames later.
- L385 _public prototype_ `static TArray<UARTrackedPoint*> FindTrackedPointsByName(const FString& PointName);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality", meta = (Keywords = "ar augmentedreality augmented reality find point"))` — @return a list of the tracked points with the given name
- L389 _public prototype_ `DEFINE_AR_BPLIB_DELEGATE_FUNCS(OnTrackableUpdated) DEFINE_AR_BPLIB_DELEGATE_FUNCS(OnTrackableRemoved)`
- L399 _public prototype_ `static void CalculateAlignmentTransform(const FTransform& TransformInFirstCoordinateSystem, const FTransform& TransformInSecondCoordinateSystem, FTransform& AlignmentTransform);` — `UFUNCTION(BlueprintCallable, Category = Alignment)` — Computes a transform that aligns two coordinate systems. Requires the transform of the same known point in each coordinate system.
- L403 _public prototype_ `static int32 GetNumberOfTrackedFacesSupported();` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Face Tracking")` — @return the max number of faces can be tracked at the same time
- L407 _public prototype_ `static bool GetCameraIntrinsics(FARCameraIntrinsics& OutCameraIntrinsics);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Geo Tracking")` — @return the intrinsics of the AR camera.
- L411 _public function_ `template<class T> static TArray<T*> GetAllGeometriesByClass()` — @return a list of all the real-world geometry of the specified class as currently seen by the Augmented Reality system
- L425 _public prototype_ `static void RegisterAsARSystem(const TSharedRef<FARSupportInterface , ESPMode::ThreadSafe>& NewArSystem);`
- L428 _private prototype_ `static const TWeakPtr<FARSupportInterface , ESPMode::ThreadSafe>& GetARSystem();`
- L429 _private member_ `static TWeakPtr<FARSupportInterface , ESPMode::ThreadSafe> RegisteredARSystem;`

#### class `UARTraceResultLibrary`  
`class UARTraceResultLibrary : public UBlueprintFunctionLibrary`  
_L434-467_
- reflection: `UCLASS(MinimalAPI, meta=(ScriptName="ARTraceResultLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L442 _public prototype_ `static float GetDistanceFromCamera( const FARTraceResult& TraceResult );` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Trace Result")` — @return  the distance from the camera to the traced location in Unreal Units.
- L450 _public prototype_ `static FTransform GetLocalToTrackingTransform( const FARTraceResult& TraceResult );` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Trace Result")` — @return The transform of the trace result in tracking space (after it is modified by the \c AlignmentTransform). \see SetAlignmentTransform()
- L454 _public prototype_ `static FTransform GetLocalToWorldTransform( const FARTraceResult& TraceResult );` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Trace Result")` — @return Get the transform of the trace result in Unreal World Space.
- L458 _public prototype_ `static FTransform GetLocalTransform( const FARTraceResult& TraceResult );` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Trace Result")` — @return Get the transform of the trace result in the AR system's local space.
- L462 _public prototype_ `static UARTrackedGeometry* GetTrackedGeometry( const FARTraceResult& TraceResult );` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Trace Result")` — @return Get the real-world object (as observed by the Augmented Reality system) that was intersected by the line trace.
- L466 _public prototype_ `static EARLineTraceChannels GetTraceChannel( const FARTraceResult& TraceResult );` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Trace Result")` — @return  Get the type of the tracked object (if any) that effected this trace result.

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API AUGMENTEDREALITY_API`
- L21 _macro_ `#define DEFINE_AR_BPLIB_DELEGATE_FUNCS(DelegateName) \`

### `Source/Runtime/AugmentedReality/Public/ARBlueprintProxy.h` (Public)


#### class `UARBaseAsyncTaskBlueprintProxy`  
`class UARBaseAsyncTaskBlueprintProxy : public UBlueprintAsyncActionBase, public FTickableGameObject`  
_L20-48_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UBlueprintAsyncActionBase,FTickableGameObject`
- L28 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L29 _public function_ `virtual bool IsTickable() const override`
- L30 _public function_ `virtual TStatId GetStatId() const override`
- L33 _public function_ `virtual void ReportSuccess()`
- L34 _public function_ `virtual void ReportFailure()`
- L36 _public prototype_ `static void RegisterAsARSystem(const TSharedRef<FARSupportInterface , ESPMode::ThreadSafe>& NewArSystem);`
- L39 _protected prototype_ `static const TWeakPtr<FARSupportInterface , ESPMode::ThreadSafe>& GetARSystem();`
- L41 _protected member_ `TSharedPtr<FARAsyncTask, ESPMode::ThreadSafe> AsyncTask;` — The async task to check during Tick()
- L45 _private member_ `bool bShouldTick;` — True until the async task completes, then false
- L47 _private member_ `static TWeakPtr<FARSupportInterface , ESPMode::ThreadSafe> RegisteredARSystem;`

#### class `UARSaveWorldAsyncTaskBlueprintProxy`  
`class UARSaveWorldAsyncTaskBlueprintProxy : public UARBaseAsyncTaskBlueprintProxy`  
_L53-83_
- reflection: `UCLASS()`
- inherits: `UARBaseAsyncTaskBlueprintProxy`
- L60 _public member_ `FARSaveWorldPin OnSuccess;` — `UPROPERTY(BlueprintAssignable)`
- L63 _public member_ `FARSaveWorldPin OnFailed;` — `UPROPERTY(BlueprintAssignable)`
- L71 _public prototype_ `static UARSaveWorldAsyncTaskBlueprintProxy* ARSaveWorld(UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, meta=(DisplayName="Save AR World", BlueprintInternalUseOnly="true", Category = "Augmented Reality", WorldContext = "WorldContextObject"))` — Saves an AR world to a byte array for network replication or saving to disk @param bCompressData whether to compress the data or not
- L75 _private prototype_ `virtual void Activate() override;` — UBlueprintAsyncActionBase interface
- L79 _private member_ `TSharedPtr<FARSaveWorldAsyncTask, ESPMode::ThreadSafe> SaveWorldTask;` — The async task to check during Tick()
- L81 _private prototype_ `virtual void ReportSuccess() override;`
- L82 _private prototype_ `virtual void ReportFailure() override;`

#### class `UARGetCandidateObjectAsyncTaskBlueprintProxy`  
`class UARGetCandidateObjectAsyncTaskBlueprintProxy : public UARBaseAsyncTaskBlueprintProxy`  
_L88-122_
- reflection: `UCLASS()`
- inherits: `UARBaseAsyncTaskBlueprintProxy`
- L95 _public member_ `FARGetCandidateObjectPin OnSuccess;` — `UPROPERTY(BlueprintAssignable)`
- L98 _public member_ `FARGetCandidateObjectPin OnFailed;` — `UPROPERTY(BlueprintAssignable)`
- L107 _public prototype_ `static UARGetCandidateObjectAsyncTaskBlueprintProxy* ARGetCandidateObject(UObject* WorldContextObject, FVector Location, FVector Extent);` — `UFUNCTION(BlueprintCallable, Meta=(DisplayName="Get AR Candidate Object", BlueprintInternalUseOnly = "true", Category = "Augmented Reality", WorldContext = "WorldContextObject"))` — Saves the point cloud centered at the specified location capturing all of the features within the specified extent as an object that can be detected later @param Location the center of the extent to grab features at @param Extent the size of the region to grab feature points
- L109 _public member_ `FVector Location;`
- L110 _public member_ `FVector Extent;`
- L114 _private prototype_ `virtual void Activate() override;` — UBlueprintAsyncActionBase interface
- L118 _private member_ `TSharedPtr<FARGetCandidateObjectAsyncTask, ESPMode::ThreadSafe> CandidateObjectTask;` — The async task to check during Tick()
- L120 _private prototype_ `virtual void ReportSuccess() override;`
- L121 _private prototype_ `virtual void ReportFailure() override;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API AUGMENTEDREALITY_API`
- L50 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FARSaveWorldPin, const TArray<uint8>&, SavedWorld);`
- L50 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FARSaveWorldPin, const TArray<uint8>&, SavedWorld);`
- L85 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FARGetCandidateObjectPin, UARCandidateObject*, SavedObject);`
- L85 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FARGetCandidateObjectPin, UARCandidateObject*, SavedObject);`

### `Source/Runtime/AugmentedReality/Public/ARComponent.h` (Public)


#### enum `EARSessionConfigFlags`  
`enum class EARSessionConfigFlags : uint8`  
_L20-28_
- reflection: `UENUM(BlueprintType)`
- L22 _public enumerator_ `None = 0`
- L23 _public enumerator_ `GenerateMeshData = 1 << 0`
- L24 _public enumerator_ `RenderMeshDataInWireframe = 1 << 1`
- L25 _public enumerator_ `GenerateCollisionForMeshData = 1 << 2`
- L26 _public enumerator_ `GenerateNavMeshForMeshData = 1 << 3`
- L27 _public enumerator_ `UseMeshDataForOcclusion = 1 << 4`

#### struct `FARSessionPayload`  
`struct FARSessionPayload`  
_L31-48_
- reflection: `USTRUCT(BlueprintType, Category = "AR Gameplay")`
- L36 _public member_ `int32 ConfigFlags = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`
- L39 _public member_ `TObjectPtr<UMaterialInterface> DefaultMeshMaterial = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`
- L42 _public member_ `TObjectPtr<UMaterialInterface> DefaultWireframeMeshMaterial = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`
- L44 _public prototype_ `void SetFlag(EARSessionConfigFlags InFlag);`
- L45 _public prototype_ `bool HasFlag(EARSessionConfigFlags InFlag) const;`
- L46 _public prototype_ `void FromSessionConfig(const UARSessionConfig& InConfig);`
- L47 _public prototype_ `bool ShouldCreateMeshComponent() const;`

#### struct `FARPlaneUpdatePayload`  
`struct FARPlaneUpdatePayload`  
_L51-72_
- reflection: `USTRUCT(BlueprintType, Category = "AR Gameplay")`
- L56 _public member_ `FARSessionPayload SessionPayload;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`
- L59 _public member_ `FTransform WorldTransform = FTransform::Identity;` — `UPROPERTY(BlueprintReadWrite, Category = "AR")`
- L62 _public member_ `FVector Center = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, Category = "AR")`
- L65 _public member_ `FVector Extents = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, Category = "AR")`
- L68 _public member_ `TArray<FVector> BoundaryVertices;` — `UPROPERTY(BlueprintReadWrite, Category = "AR")`
- L71 _public member_ `EARObjectClassification ObjectClassification = EARObjectClassification::Unknown;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`

#### struct `FARPointUpdatePayload`  
`struct FARPointUpdatePayload`  
_L75-78_
- reflection: `USTRUCT(BlueprintType, Category = "AR Gameplay")`

#### struct `FARFaceUpdatePayload`  
`struct FARFaceUpdatePayload`  
_L82-97_
- reflection: `USTRUCT(BlueprintType, Category = "AR Gameplay")`
- L87 _public member_ `FARSessionPayload SessionPayload;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`
- L90 _public member_ `FVector LeftEyePosition = FVector(0.0f);` — `UPROPERTY(BlueprintReadWrite, Category = "AR")`
- L93 _public member_ `FVector RightEyePosition = FVector(0.0f);` — `UPROPERTY(BlueprintReadWrite, Category = "AR")`
- L96 _public member_ `FVector LookAtTarget = FVector(0.0f);` — `UPROPERTY(BlueprintReadWrite, Category = "AR")`

#### struct `FARImageUpdatePayload`  
`struct FARImageUpdatePayload`  
_L101-116_
- reflection: `USTRUCT(BlueprintType, Category = "AR Gameplay")`
- L106 _public member_ `FARSessionPayload SessionPayload;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`
- L109 _public member_ `FTransform WorldTransform = FTransform::Identity;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`
- L112 _public member_ `TObjectPtr<UARCandidateImage> DetectedImage = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`
- L115 _public member_ `FVector2D EstimatedSize = FVector2D::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`

#### struct `FARQRCodeUpdatePayload`  
`struct FARQRCodeUpdatePayload`  
_L119-134_
- reflection: `USTRUCT(BlueprintType, Category = "AR Gameplay")`
- L124 _public member_ `FARSessionPayload SessionPayload;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`
- L127 _public member_ `FTransform WorldTransform = FTransform::Identity;` — `UPROPERTY(BlueprintReadWrite, Category = "AR")`
- L130 _public member_ `FVector Extents = FVector(0.0f);` — `UPROPERTY(BlueprintReadWrite, Category = "AR")`
- L133 _public member_ `FString QRCode;` — `UPROPERTY(BlueprintReadWrite, Category = "AR")`

#### struct `FARPoseUpdatePayload`  
`struct FARPoseUpdatePayload`  
_L137-146_
- reflection: `USTRUCT(BlueprintType, Category = "AR Gameplay")`
- L142 _public member_ `FTransform WorldTransform = FTransform::Identity;` — `UPROPERTY(BlueprintReadWrite, Category = "AR")`
- L145 _public member_ `TArray<FTransform> JointTransforms;` — `UPROPERTY(BlueprintReadWrite, Category = "AR")`

#### struct `FAREnvironmentProbeUpdatePayload`  
`struct FAREnvironmentProbeUpdatePayload`  
_L149-155_
- reflection: `USTRUCT(BlueprintType, Category = "AR Gameplay")`
- L154 _public member_ `FTransform WorldTransform = FTransform::Identity;` — `UPROPERTY(BlueprintReadWrite, Category = "AR")`

#### struct `FARObjectUpdatePayload`  
`struct FARObjectUpdatePayload`  
_L158-164_
- reflection: `USTRUCT(BlueprintType, Category = "AR Gameplay")`
- L163 _public member_ `FTransform WorldTransform = FTransform::Identity;` — `UPROPERTY(BlueprintReadWrite, Category = "AR")`

#### struct `FARMeshUpdatePayload`  
`struct FARMeshUpdatePayload`  
_L168-180_
- reflection: `USTRUCT(BlueprintType, Category = "AR Gameplay")`
- L173 _public member_ `FARSessionPayload SessionPayload;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`
- L176 _public member_ `FTransform WorldTransform = FTransform::Identity;` — `UPROPERTY(BlueprintReadWrite, Category = "AR")`
- L179 _public member_ `EARObjectClassification ObjectClassification = EARObjectClassification::Unknown;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`

#### struct `FARGeoAnchorUpdatePayload`  
`struct FARGeoAnchorUpdatePayload`  
_L184-208_
- reflection: `USTRUCT(BlueprintType, Category = "AR Gameplay")`
- L189 _public member_ `FARSessionPayload SessionPayload;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`
- L192 _public member_ `FTransform WorldTransform = FTransform::Identity;` — `UPROPERTY(BlueprintReadWrite, Category = "AR")`
- L195 _public member_ `float Longitude = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`
- L198 _public member_ `float Latitude = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`
- L201 _public member_ `float AltitudeMeters = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`
- L204 _public member_ `EARAltitudeSource AltitudeSource = EARAltitudeSource::Unknown;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`
- L207 _public member_ `FString AnchorName;` — `UPROPERTY(BlueprintReadOnly, Category = "AR")`

#### struct `FAccumulatedNormal`  
`struct FAccumulatedNormal`  
_L210-217_
- L212 _public member_ `FVector Normal = FVector::ZeroVector;`
- L213 _public member_ `uint32 NumFaces = 0;`
- L216 _public prototype_ `template<typename VertexType> static void CalculateVertexNormals(TArray<FAccumulatedNormal>& AccumulatedNormals, const TArray<VertexType>& Vertices, const TArray<MRMESH_INDEX_TYPE>& Indices, TArray<FPackedNormal>& OutTangentData, FVector MeshCenter = FVector::ZeroVector, float PositionScale = 1.f);`

#### class `UARComponent`  
`class UARComponent : public USceneComponent`  
_L233-311_
- reflection: `UCLASS(MinimalAPI, abstract, BlueprintType, Category = "AR Gameplay")`
- inherits: `USceneComponent`
- desc: ARComponent handles replication and visualization update for AR tracked geometries ARComponent is created in either multiplayer or local only environment To customize the visualization logic, override 'UpdateVisualization' in Blueprint or 'UpdateVisualization_Implementation' in C++ To customize the replication logic, disable 'bUseDefaultReplication' and implement your own replication logic when the ARComponent is updated (see how 'Update' is implemented in the sub classes) A MRMeshComponent will be created if mesh visualization is enabled (see UARSessionConfig::bGenerateMeshDataFromTrackedGeometry) It can be accessed via 'GetMRMesh' or 'UARTrackedGeometry::GetUnderlyingMesh'
- L237 _private prototype_ `virtual void BeginPlay() override;`
- L240 _public prototype_ `UARComponent();`
- L243 _public prototype_ `void SetNativeID(FGuid NativeID);` — `UFUNCTION(BlueprintCallable, Category = "AR Gameplay")`
- L246 _public function_ `UMRMeshComponent* GetMRMesh()` — `UFUNCTION(BlueprintPure, Category = "AR Gameplay")`
- L250 _public prototype_ `void ReceiveRemove();` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Remove"))` — Event when native representation is removed, called on server and clients.
- L253 _public prototype_ `void UpdateVisualization();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (DisplayName = "Update Visualization"), Category = "AR Gameplay")`
- L255 _public function_ `virtual void Update(UARTrackedGeometry* TrackedGeometry)`
- L256 _public prototype_ `virtual void Remove(UARTrackedGeometry* TrackedGeometry);`
- L259 _public member_ `FGuid NativeID;` — `UPROPERTY(Replicated)`
- L261 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMRMeshDelegate, UMRMeshComponent*);`
- L262 _public member_ `FMRMeshDelegate OnMRMeshCreated;`
- L263 _public member_ `FMRMeshDelegate OnMRMeshDestroyed;`
- L266 _protected prototype_ `virtual void OnUnregister() override;`
- L269 _protected prototype_ `virtual void OnRep_Payload();` — `UFUNCTION()`
- L271 _protected prototype_ `void RemoveMeshComponent(UARTrackedGeometry* TrackedGeometry);`
- L273 _protected prototype_ `void ManageMeshComponentForDebugMode(bool bDebugModeEnabled, const FARSessionPayload& SessionPayload);`
- L275 _protected prototype_ `FLinearColor GetDebugColor() const;`
- L279 _protected member_ `bool bUseDefaultReplication = true;` — `UPROPERTY(EditAnywhere, Category = "AR Gameplay")` — If the default replication logic should be used for this component
- L286 _protected member_ `TObjectPtr<UMaterialInterface> DefaultMeshMaterial = nullptr;` — `UPROPERTY(EditAnywhere, Category = "AR Gameplay")` — The default material to be used for the generated mesh component. If not set, the DefaultMeshMaterial from ARSessionConfig will be used.
- L293 _protected member_ `TObjectPtr<UMaterialInterface> DefaultWireframeMeshMaterial = nullptr;` — `UPROPERTY(EditAnywhere, Category = "AR Gameplay")` — The default wireframe material to be used for the generated mesh component. If not set, the DefaultMeshMaterial from ARSessionConfig will be used.
- L296 _protected member_ `TObjectPtr<UMRMeshComponent> MRMeshComponent;` — `UPROPERTY()`
- L300 _protected member_ `TObjectPtr<UARTrackedGeometry> MyTrackedGeometry;` — `UPROPERTY()` — The tracked geometry used for updating this component, only set on "local" client
- L303 _protected member_ `bool bFirstUpdate = true;` — If this component has ever been updated
- L306 _protected member_ `bool bIsRemoved = false;` — If 'ReceiveRemove' has been called for this component
- L308 _protected member_ `bool bInDebugMode = false;`
- L309 _protected member_ `bool bSavedWireframeMode;`
- L310 _protected member_ `FLinearColor SavedWireframeColor;`

#### enum `EPlaneComponentDebugMode`  
`enum class EPlaneComponentDebugMode : uint8`  
_L314-324_
- reflection: `UENUM(BlueprintType)`
- L317 _public enumerator_ `None = 0` — The debug mode is disabled
- L320 _public enumerator_ `ShowNetworkRole = 1` — Use different coloration to indicate if the plane belongs to the local or remote client
- L323 _public enumerator_ `ShowClassification = 2` — Use different coloration to indicate the classification of this plane

#### class `UARPlaneComponent`  
`class UARPlaneComponent : public UARComponent`  
_L327-364_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, Category = "AR Gameplay")`
- inherits: `UARComponent`
- L332 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L336 _public prototype_ `void ReceiveAdd(const FARPlaneUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Add"))` — Event when native representation is first added, called on server and clients.
- L340 _public prototype_ `void ReceiveUpdate(const FARPlaneUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Update"))` — Event when native representation is updated, called on server and clients.
- L343 _public prototype_ `virtual void Update(UARTrackedGeometry* TrackedGeometry) override;` — Overridable native event for when native representation is updated.
- L346 _public prototype_ `static void SetPlaneComponentDebugMode(EPlaneComponentDebugMode NewDebugMode);` — `UFUNCTION(BlueprintCallable, Category = "AR Gameplay | Debug", meta=(DevelopmentOnly))`
- L349 _public prototype_ `static void SetObjectClassificationDebugColors(const TMap<EARObjectClassification, FLinearColor>& InColors);` — `UFUNCTION(BlueprintCallable, Category = "AR Gameplay | Debug", meta=(DevelopmentOnly))`
- L352 _public prototype_ `static const TMap<EARObjectClassification, FLinearColor>& GetObjectClassificationDebugColors();` — `UFUNCTION(BlueprintPure, Category = "AR Gameplay | Debug", meta=(DevelopmentOnly))`
- L356 _protected prototype_ `void ServerUpdatePayload(const FARPlaneUpdatePayload& NewPayload);` — `UFUNCTION(Reliable, Server, WithValidation)`
- L359 _protected member_ `FARPlaneUpdatePayload ReplicatedPayload;` — `UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Payload, Category = "AR Gameplay")`
- L361 _protected prototype_ `virtual void OnRep_Payload() override;`
- L362 _protected prototype_ `virtual void UpdateVisualization_Implementation() override;`
- L363 _protected prototype_ `static int32 GetDebugMode();`

#### class `UARPointComponent`  
`class UARPointComponent : public UARComponent`  
_L368-391_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, Category = "AR Gameplay")`
- inherits: `UARComponent`
- L374 _public prototype_ `void ReceiveAdd(const FARPointUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Add"))` — Event when native representation is first added, called on server and clients.
- L378 _public prototype_ `void ReceiveUpdate(const FARPointUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Update"))` — Event when native representation is updated, called on server and clients.
- L381 _public prototype_ `virtual void Update(UARTrackedGeometry* TrackedGeometry) override;` — Overridable native event for when native representation is updated.
- L385 _protected prototype_ `void ServerUpdatePayload(const FARPointUpdatePayload& NewPayload);` — `UFUNCTION(Reliable, Server, WithValidation)`
- L388 _protected member_ `FARPointUpdatePayload ReplicatedPayload;` — `UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Payload, Category = "AR Gameplay")`
- L390 _protected prototype_ `virtual void OnRep_Payload() override;`

#### enum `EFaceComponentDebugMode`  
`enum class EFaceComponentDebugMode : uint8`  
_L394-404_
- reflection: `UENUM(BlueprintType)`
- L397 _public enumerator_ `None = 0` — The debug mode is disabled
- L400 _public enumerator_ `ShowEyeVectors = 1` — Display vectors for both eyes
- L403 _public enumerator_ `ShowFaceMesh = 2` — Display the face mesh in wireframe

#### enum `EARFaceTransformMixing`  
`enum class EARFaceTransformMixing : uint8`  
_L407-420_
- reflection: `UENUM(BlueprintType)`
- L410 _public enumerator_ `ComponentOnly` — Uses the component's transform exclusively. Only setting for non-tracked meshes
- L413 _public enumerator_ `ComponentLocationTrackedRotation` — Use the component's location and apply the rotation from the tracked mesh
- L416 _public enumerator_ `ComponentWithTracked` — Concatenate the component and the tracked face transforms
- L419 _public enumerator_ `TrackingOnly` — Use only the tracked face transform

#### class `UARFaceComponent`  
`class UARFaceComponent : public UARComponent`  
_L423-472_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, Category = "AR Gameplay")`
- inherits: `UARComponent`
- L428 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L432 _public prototype_ `void ReceiveAdd(const FARFaceUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Add"))` — Event when native representation is first added, called on server and clients.
- L436 _public prototype_ `void ReceiveUpdate(const FARFaceUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Update"))` — Event when native representation is updated, called on server and clients.
- L439 _public prototype_ `virtual void Update(UARTrackedGeometry* TrackedGeometry) override;` — Overridable native event for when native representation is updated.
- L442 _public prototype_ `static void SetFaceComponentDebugMode(EFaceComponentDebugMode NewDebugMode);` — `UFUNCTION(BlueprintCallable, Category = "AR Gameplay | Debug", meta=(DevelopmentOnly))`
- L447 _protected member_ `EARFaceTransformMixing TransformSetting = EARFaceTransformMixing::TrackingOnly;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AR Gameplay")` — Determines how the transform from tracking data and the component's transform are mixed together.
- L451 _protected member_ `bool bUpdateVertexNormal = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AR Gameplay")` — Whether to automatically update the vertex normal when the mesh is updated.
- L455 _protected member_ `bool bFaceOutOfScreen = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AR Gameplay")` — Whether the mesh should be rotated so that it's facing out of the screen.
- L458 _protected prototype_ `void ServerUpdatePayload(const FARFaceUpdatePayload& NewPayload);` — `UFUNCTION(Reliable, Server, WithValidation)`
- L461 _protected member_ `FARFaceUpdatePayload ReplicatedPayload;` — `UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Payload, Category = "AR Gameplay")`
- L463 _protected prototype_ `virtual void OnRep_Payload() override;`
- L464 _protected prototype_ `virtual void UpdateVisualization_Implementation() override;`
- L465 _protected prototype_ `static int32 GetDebugMode();`
- L469 _private member_ `TArray<FAccumulatedNormal> AccumulatedNormals;` — Temporary data used for calculating the normals from vertices
- L471 _private member_ `TArray<FPackedNormal> TangentData;`

#### enum `EImageComponentDebugMode`  
`enum class EImageComponentDebugMode : uint8`  
_L475-482_
- reflection: `UENUM(BlueprintType)`
- L478 _public enumerator_ `None = 0` — The debug mode is disabled
- L481 _public enumerator_ `ShowDetectedImage = 1` — Display info about the detected image

#### class `UARImageComponent`  
`class UARImageComponent : public UARComponent`  
_L485-516_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, Category = "AR Gameplay")`
- inherits: `UARComponent`
- L490 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L494 _public prototype_ `void ReceiveAdd(const FARImageUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Add"))` — Event when native representation is first added, called on server and clients.
- L498 _public prototype_ `void ReceiveUpdate(const FARImageUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Update"))` — Event when native representation is updated, called on server and clients.
- L501 _public prototype_ `static void SetImageComponentDebugMode(EImageComponentDebugMode NewDebugMode);` — `UFUNCTION(BlueprintCallable, Category = "AR Gameplay | Debug", meta=(DevelopmentOnly))`
- L504 _public prototype_ `virtual void Update(UARTrackedGeometry* TrackedGeometry) override;` — Overridable native event for when native representation is updated.
- L508 _protected prototype_ `void ServerUpdatePayload(const FARImageUpdatePayload& NewPayload);` — `UFUNCTION(Reliable, Server, WithValidation)`
- L511 _protected member_ `FARImageUpdatePayload ReplicatedPayload;` — `UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Payload, Category = "AR Gameplay")`
- L513 _protected prototype_ `virtual void OnRep_Payload() override;`
- L514 _protected prototype_ `virtual void UpdateVisualization_Implementation() override;`
- L515 _protected prototype_ `static int32 GetDebugMode();`

#### enum `EQRCodeComponentDebugMode`  
`enum class EQRCodeComponentDebugMode : uint8`  
_L519-526_
- reflection: `UENUM(BlueprintType)`
- L522 _public enumerator_ `None = 0` — The debug mode is disabled
- L525 _public enumerator_ `ShowQRCode = 1` — Show info about the detected QR code

#### class `UARQRCodeComponent`  
`class UARQRCodeComponent : public UARComponent`  
_L529-560_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, Category = "AR Gameplay")`
- inherits: `UARComponent`
- L534 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L538 _public prototype_ `void ReceiveAdd(const FARQRCodeUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Add"))` — Event when native representation is first added, called on server and clients.
- L542 _public prototype_ `void ReceiveUpdate(const FARQRCodeUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Update"))` — Event when native representation is updated, called on server and clients.
- L545 _public prototype_ `virtual void Update(UARTrackedGeometry* TrackedGeometry) override;` — Overridable native event for when native representation is updated.
- L548 _public prototype_ `static void SetQRCodeComponentDebugMode(EQRCodeComponentDebugMode NewDebugMode);` — `UFUNCTION(BlueprintCallable, Category = "AR Gameplay | Debug", meta=(DevelopmentOnly))`
- L552 _protected prototype_ `void ServerUpdatePayload(const FARQRCodeUpdatePayload& NewPayload);` — `UFUNCTION(Reliable, Server, WithValidation)`
- L555 _protected member_ `FARQRCodeUpdatePayload ReplicatedPayload;` — `UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Payload, Category = "AR Gameplay")`
- L557 _protected prototype_ `virtual void OnRep_Payload() override;`
- L558 _protected prototype_ `virtual void UpdateVisualization_Implementation() override;`
- L559 _protected prototype_ `static int32 GetDebugMode();`

#### enum `EPoseComponentDebugMode`  
`enum class EPoseComponentDebugMode : uint8`  
_L563-570_
- reflection: `UENUM(BlueprintType)`
- L566 _public enumerator_ `None = 0` — The debug mode is disabled
- L569 _public enumerator_ `ShowSkeleton = 1` — Show the skeleton with debug draw

#### class `UARPoseComponent`  
`class UARPoseComponent : public UARComponent`  
_L573-603_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, Category = "AR Gameplay")`
- inherits: `UARComponent`
- L578 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L582 _public prototype_ `void ReceiveAdd(const FARPoseUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Add"))` — Event when native representation is first added, called on server and clients.
- L586 _public prototype_ `void ReceiveUpdate(const FARPoseUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Update"))` — Event when native representation is updated, called on server and clients.
- L589 _public prototype_ `virtual void Update(UARTrackedGeometry* TrackedGeometry) override;` — Overridable native event for when native representation is updated.
- L592 _public prototype_ `static void SetPoseComponentDebugMode(EPoseComponentDebugMode NewDebugMode);` — `UFUNCTION(BlueprintCallable, Category = "AR Gameplay | Debug", meta=(DevelopmentOnly))`
- L596 _protected prototype_ `void ServerUpdatePayload(const FARPoseUpdatePayload& NewPayload);` — `UFUNCTION(Reliable, Server, WithValidation)`
- L599 _protected member_ `FARPoseUpdatePayload ReplicatedPayload;` — `UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Payload, Category = "AR Gameplay")`
- L601 _protected prototype_ `virtual void OnRep_Payload() override;`
- L602 _protected prototype_ `static int32 GetDebugMode();`

#### class `UAREnvironmentProbeComponent`  
`class UAREnvironmentProbeComponent : public UARComponent`  
_L607-630_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, Category = "AR Gameplay")`
- inherits: `UARComponent`
- L613 _public prototype_ `void ReceiveAdd(const FAREnvironmentProbeUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Add"))` — Event when native representation is first added, called on server and clients.
- L617 _public prototype_ `void ReceiveUpdate(const FAREnvironmentProbeUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Update"))` — Event when native representation is updated, called on server and clients.
- L620 _public prototype_ `virtual void Update(UARTrackedGeometry* TrackedGeometry) override;` — Overridable native event for when native representation is updated.
- L624 _protected prototype_ `void ServerUpdatePayload(const FAREnvironmentProbeUpdatePayload& NewPayload);` — `UFUNCTION(Reliable, Server, WithValidation)`
- L627 _protected member_ `FAREnvironmentProbeUpdatePayload ReplicatedPayload;` — `UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Payload, Category = "AR Gameplay")`
- L629 _protected prototype_ `virtual void OnRep_Payload() override;`

#### class `UARObjectComponent`  
`class UARObjectComponent : public UARComponent`  
_L634-657_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, Category = "AR Gameplay")`
- inherits: `UARComponent`
- L640 _public prototype_ `void ReceiveAdd(const FARObjectUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Add"))` — Event when native representation is first added, called on server and clients.
- L644 _public prototype_ `void ReceiveUpdate(const FARObjectUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Update"))` — Event when native representation is updated, called on server and clients.
- L647 _public prototype_ `virtual void Update(UARTrackedGeometry* TrackedGeometry) override;` — Overridable native event for when native representation is updated.
- L651 _protected prototype_ `void ServerUpdatePayload(const FARObjectUpdatePayload& NewPayload);` — `UFUNCTION(Reliable, Server, WithValidation)`
- L654 _protected member_ `FARObjectUpdatePayload ReplicatedPayload;` — `UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Payload, Category = "AR Gameplay")`
- L656 _protected prototype_ `virtual void OnRep_Payload() override;`

#### class `UARMeshComponent`  
`class UARMeshComponent : public UARComponent`  
_L661-685_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, Category = "AR Gameplay")`
- inherits: `UARComponent`
- L667 _public prototype_ `void ReceiveAdd(const FARMeshUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Add"))` — Event when native representation is first added, called on server and clients.
- L671 _public prototype_ `void ReceiveUpdate(const FARMeshUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Update"))` — Event when native representation is updated, called on server and clients.
- L674 _public prototype_ `virtual void Update(UARTrackedGeometry* TrackedGeometry) override;` — Overridable native event for when native representation is updated.
- L678 _protected prototype_ `void ServerUpdatePayload(const FARMeshUpdatePayload& NewPayload);` — `UFUNCTION(Reliable, Server, WithValidation)`
- L681 _protected member_ `FARMeshUpdatePayload ReplicatedPayload;` — `UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Payload, Category = "AR Gameplay")`
- L683 _protected prototype_ `virtual void OnRep_Payload() override;`
- L684 _protected prototype_ `virtual void UpdateVisualization_Implementation() override;`

#### enum `EGeoAnchorComponentDebugMode`  
`enum class EGeoAnchorComponentDebugMode : uint8`  
_L689-696_
- reflection: `UENUM(BlueprintType)`
- L692 _public enumerator_ `None = 0` — The debug mode is disabled
- L695 _public enumerator_ `ShowGeoData = 1` — Display Geo related data

#### class `UARGeoAnchorComponent`  
`class UARGeoAnchorComponent : public UARComponent`  
_L699-729_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, Category = "AR Gameplay")`
- inherits: `UARComponent`
- L705 _public prototype_ `static void SetGeoAnchorComponentDebugMode(EGeoAnchorComponentDebugMode NewDebugMode);` — `UFUNCTION(BlueprintCallable, Category = "AR Gameplay | Debug", meta=(DevelopmentOnly))`
- L709 _public prototype_ `void ReceiveAdd(const FARGeoAnchorUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Add"))` — Event when native representation is first added, called on server and clients.
- L713 _public prototype_ `void ReceiveUpdate(const FARGeoAnchorUpdatePayload& Payload);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Update"))` — Event when native representation is updated, called on server and clients.
- L716 _public prototype_ `virtual void Update(UARTrackedGeometry* TrackedGeometry) override;` — Overridable native event for when native representation is updated.
- L718 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L722 _protected prototype_ `void ServerUpdatePayload(const FARGeoAnchorUpdatePayload& NewPayload);` — `UFUNCTION(Reliable, Server, WithValidation)`
- L725 _protected member_ `FARGeoAnchorUpdatePayload ReplicatedPayload;` — `UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Payload, Category = "AR Gameplay")`
- L727 _protected prototype_ `virtual void OnRep_Payload() override;`
- L728 _protected prototype_ `static int32 GetDebugMode();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUGMENTEDREALITY_API`
- L261 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMRMeshDelegate, UMRMeshComponent*);`

### `Source/Runtime/AugmentedReality/Public/ARDependencyHandler.h` (Public)


#### enum `EARServiceAvailability`  
`enum class EARServiceAvailability : uint8`  
_L22-44_
- reflection: `UENUM(BlueprintType)`
- L25 _public enumerator_ `UnknownError` — Availability is unknown due to an error during checking
- L28 _public enumerator_ `UnknownChecking` — Availability is being checked
- L31 _public enumerator_ `UnknownTimedOut` — Availability is unknown due to timeout during checking
- L34 _public enumerator_ `UnsupportedDeviceNotCapable` — The device is not capable of running the AR service
- L37 _public enumerator_ `SupportedNotInstalled` — AR service is not installed
- L40 _public enumerator_ `SupportedVersionTooOld` — AR service is installed but the version is too old
- L43 _public enumerator_ `SupportedInstalled` — AR service is supported and installed

#### enum `EARServiceInstallRequestResult`  
`enum class EARServiceInstallRequestResult : uint8`  
_L47-60_
- reflection: `UENUM(BlueprintType)`
- L50 _public enumerator_ `Installed` — AR service is installed
- L53 _public enumerator_ `DeviceNotCompatible` — The device is not capable of running the AR service
- L56 _public enumerator_ `UserDeclinedInstallation` — The user declined the request to install the AR service
- L59 _public enumerator_ `FatalError` — Other error while installing the AR service

#### enum `EARServicePermissionRequestResult`  
`enum class EARServicePermissionRequestResult : uint8`  
_L63-70_
- reflection: `UENUM(BlueprintType)`
- L66 _public enumerator_ `Granted` — The permission is granted by the user
- L69 _public enumerator_ `Denied` — The permission is denied by the user

#### class `UARDependencyHandler`  
`class UARDependencyHandler : public UObject, public IModularFeature`  
_L83-119_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract, Category="")`
- inherits: `UObject,IModularFeature`
- desc: Helper class that allows the user to explicitly request AR service installation and permission granting. Recommended flow for explicit management: 1. Call "GetARDependencyHandler" to get a handler, if valid: 2. Call "CheckARServiceAvailability" to check availability, if the device is supported: 3. Call "InstallARService" to install AR service dependency, if installed: 4. Call "RequestARSessionPermission" to request permission, if granted: 5. Call "UARBlueprintLibrary::StartARSession" to start the session. Alternatively, you can also call "StartARSessionLatent" which handles dependency and permission internally.
- L88 _public function_ `static FName GetModularFeatureName()`
- L99 _public prototype_ `static UARDependencyHandler* GetARDependencyHandler();` — `UFUNCTION(BlueprintCallable, Category = "")` — @return the dependency handler for the current platform. Can return null if the current platform doesn't support AR, or the AR system doesn't require dependency handling.
- L103 _public prototype_ `virtual void CheckARServiceAvailability(UObject* WorldContextObject, FLatentActionInfo LatentInfo, EARServiceAvailability& OutAvailability) PURE_VIRTUAL(UARDependencyHandler::CheckARServiceAvailability, );` — `UFUNCTION(BlueprintCallable, Category = "", meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"))` — Latent action to check AR availability on the current platform.
- L107 _public prototype_ `virtual void InstallARService(UObject* WorldContextObject, FLatentActionInfo LatentInfo, EARServiceInstallRequestResult& OutInstallResult) PURE_VIRTUAL(UARDependencyHandler::InstallARService, );` — `UFUNCTION(BlueprintCallable, Category = "", meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"))` — Latent action to install AR service on the current platform.
- L111 _public prototype_ `virtual void RequestARSessionPermission(UObject* WorldContextObject, UARSessionConfig* SessionConfig, FLatentActionInfo LatentInfo, EARServicePermissionRequestResult& OutPermissionResult) PURE_VIRTUAL(UARDependencyHandler::RequestARSessionPermission, );` — `UFUNCTION(BlueprintCallable, Category = "", meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"))` — Latent action to request permission to run the supplied session configuration.
- L118 _public prototype_ `virtual void StartARSessionLatent(UObject* WorldContextObject, UARSessionConfig* SessionConfig, FLatentActionInfo LatentInfo) PURE_VIRTUAL(UARDependencyHandler::StartARSessionLatent, );` — `UFUNCTION(BlueprintCallable, Category = "", meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"))` — Latent action to start AR session. Will make sure dependency and permission issues are resolved internally, only returns the AR session starts successfully.

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API AUGMENTEDREALITY_API`

### `Source/Runtime/AugmentedReality/Public/ARGeoTrackingSupport.h` (Public)


#### enum `EARGeoTrackingState`  
`enum class EARGeoTrackingState : uint8`  
_L20-33_
- reflection: `UENUM(BlueprintType)`
- L23 _public enumerator_ `Initializing` — The session is initializing geo tracking.
- L26 _public enumerator_ `Localized` — Geo tracking is localized.
- L29 _public enumerator_ `Localizing` — Geo tracking is attempting to localize against a map.
- L32 _public enumerator_ `NotAvailable` — Geo tracking is not available.

#### enum `EARGeoTrackingStateReason`  
`enum class EARGeoTrackingStateReason : uint8`  
_L37-65_
- reflection: `UENUM(BlueprintType)`
- L40 _public enumerator_ `None` — No issues reported.
- L43 _public enumerator_ `NotAvailableAtLocation` — Geo tracking is not available at the location.
- L46 _public enumerator_ `NeedLocationPermissions` — Geo tracking needs location permissions from the user.
- L49 _public enumerator_ `DevicePointedTooLow` — The user is pointing the device too low to use geo tracking.
- L52 _public enumerator_ `WorldTrackingUnstable` — The session is unsure of the device’s pose in the physical environment.
- L55 _public enumerator_ `WaitingForLocation` — The framework is waiting for a position for the user.
- L58 _public enumerator_ `GeoDataNotLoaded` — The framework is actively attempting to download localization imagery.
- L61 _public enumerator_ `VisualLocalizationFailed` — The framework failed to match its localization imagery with the device’s camera captures.
- L64 _public enumerator_ `WaitingForAvailabilityCheck` — The framework is waiting for the availability check.

#### enum `EARGeoTrackingAccuracy`  
`enum class EARGeoTrackingAccuracy : uint8`  
_L69-82_
- reflection: `UENUM(BlueprintType)`
- L72 _public enumerator_ `Undetermined` — Geo-tracking accuracy is undetermined.
- L75 _public enumerator_ `Low` — Geo-tracking accuracy is low.
- L78 _public enumerator_ `Medium` — Geo-tracking accuracy is average.
- L81 _public enumerator_ `High` — Geo-tracking accuracy is high.

#### class `UARGeoTrackingSupport`  
`class UARGeoTrackingSupport : public UObject, public IModularFeature`  
_L89-151_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract, Category="AR|Geo Tracking")`
- inherits: `UObject,IModularFeature`
- desc: Interface class for Geo tracking related features.
- L94 _public function_ `static FName GetModularFeatureName()`
- L102 _public prototype_ `static class UARGeoTrackingSupport* GetGeoTrackingSupport();` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Geo Tracking")` — @return the interface object to support Geo tracking, return null on platforms don't support the feature.
- L108 _public prototype_ `virtual TSharedPtr<FCheckGeoTrackingAvailabilityAsyncTask, ESPMode::ThreadSafe> CheckGeoTrackingAvailability(FString& OutError);` — @return the async task to check Geo tracking availability at the user's current location. Can return null if the feature is not supported.
- L114 _public prototype_ `virtual TSharedPtr<FCheckGeoTrackingAvailabilityAsyncTask, ESPMode::ThreadSafe> CheckGeoTrackingAvailability(float Longitude, float Latitude, FString& OutError);` — @return the async task to check Geo tracking availability at a specific location. Can return null if the feature is not supported.
- L120 _public prototype_ `virtual TSharedPtr<FGetGeoLocationAsyncTask, ESPMode::ThreadSafe> GetGeoLocationAtWorldPosition(const FVector& WorldPosition, FString& OutError);` — @return the async task to convert a UE4 world position into a Geo location. Can return null if the feature is not supported.
- L126 _public function_ `virtual EARGeoTrackingState GetGeoTrackingState() const` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Geo Tracking")` — @return the current session's Geo tracking state.
- L132 _public function_ `virtual EARGeoTrackingStateReason GetGeoTrackingStateReason() const` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Geo Tracking")` — @return the current session's Geo tracking state reason.
- L138 _public function_ `virtual EARGeoTrackingAccuracy GetGeoTrackingAccuracy() const` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Geo Tracking")` — @return the current session's Geo tracking state accuracy.
- L144 _public function_ `virtual bool AddGeoAnchorAtLocation(float Longitude, float Latitude, FString OptionalAnchorName)` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Geo Tracking")` — @return add an Geo anchor at a specific location.
- L150 _public function_ `virtual bool AddGeoAnchorAtLocationWithAltitude(float Longitude, float Latitude, float AltitudeMeters, FString OptionalAnchorName)` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Geo Tracking")` — @return add an Geo anchor at a specific location with an altitude (in meters).

#### class `FCheckGeoTrackingAvailabilityAsyncTask`  
`class FCheckGeoTrackingAvailabilityAsyncTask : public FARAsyncTask`  
_L157-174_
- inherits: `FARAsyncTask`
- desc: Async task to check Geo tracking availability.
- L160 _public function_ `bool IsAvailable() const`
- L165 _public prototype_ `void FinishWithAvailability(bool bInIsAvailable);` — Finish the task with the availability result.
- L170 _public prototype_ `void FinishWithError(const FString& InError);` — Finish the task with an error.
- L173 _private member_ `bool bIsAvailable = false;`

#### class `UCheckGeoTrackingAvailabilityAsyncTaskBlueprintProxy`  
`class UCheckGeoTrackingAvailabilityAsyncTaskBlueprintProxy : public UARBaseAsyncTaskBlueprintProxy`  
_L181-220_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UARBaseAsyncTaskBlueprintProxy`
- desc: Blueprint async task to check Geo tracking availability.
- L186 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGeoTrackingAvailabilityDelegate, bool, bIsAvailable, FString, Error);`
- L189 _public member_ `FGeoTrackingAvailabilityDelegate OnSuccess;` — `UPROPERTY(BlueprintAssignable)`
- L192 _public member_ `FGeoTrackingAvailabilityDelegate OnFailed;` — `UPROPERTY(BlueprintAssignable)`
- L198 _public prototype_ `static UCheckGeoTrackingAvailabilityAsyncTaskBlueprintProxy* CheckGeoTrackingAvailability(UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Geo Tracking", meta=(BlueprintInternalUseOnly="true", WorldContext = "WorldContextObject"))` — Check Geo tracking availability at the user's current location.
- L204 _public prototype_ `static UCheckGeoTrackingAvailabilityAsyncTaskBlueprintProxy* CheckGeoTrackingAvailabilityAtLocation(UObject* WorldContextObject, float Longitude, float Latitude);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Geo Tracking", meta=(BlueprintInternalUseOnly="true", WorldContext = "WorldContextObject"))` — Check Geo tracking availability at a specific Geo location.
- L208 _private prototype_ `void Activate() override;` — UBlueprintAsyncActionBase interface
- L209 _private prototype_ `void ReportSuccess() override;`
- L210 _private prototype_ `void ReportFailure() override;`
- L213 _private member_ `TOptional<float> Longitude;`
- L214 _private member_ `TOptional<float> Latitude;`
- L217 _private member_ `TSharedPtr<FCheckGeoTrackingAvailabilityAsyncTask, ESPMode::ThreadSafe> MyTask;` — The async task to check during Tick()
- L219 _private member_ `FString Error;`

#### class `FGetGeoLocationAsyncTask`  
`class FGetGeoLocationAsyncTask : public FARAsyncTask`  
_L226-258_
- inherits: `FARAsyncTask`
- desc: Async task to convert Geo location.
- L232 _public prototype_ `void FinishWithGeoLocation(float InLongitude, float InLatitude, float InAltitude);` — Finish the task with a Geo location.
- L237 _public prototype_ `void FinishWithError(const FString& InError);` — Finish the task with an error.
- L242 _public function_ `float GetLongitude() const` — @return the longitude of the converted Geo location.
- L247 _public function_ `float GetLatitude() const` — @return the latitude of the converted Geo location.
- L252 _public function_ `float GetAltitude() const` — @return the altitude of the converted Geo location.
- L255 _private member_ `float Longitude = 0.f;`
- L256 _private member_ `float Latitude = 0.f;`
- L257 _private member_ `float Altitude = 0.f;`

#### class `UGetGeoLocationAsyncTaskBlueprintProxy`  
`class UGetGeoLocationAsyncTaskBlueprintProxy : public UARBaseAsyncTaskBlueprintProxy`  
_L265-297_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UARBaseAsyncTaskBlueprintProxy`
- desc: Blueprint async task to convert Geo location.
- L270 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FGetGeoLocationDelegate, float, Longitude, float, Latitude, float, Altitude, FString, Error);`
- L273 _public member_ `FGetGeoLocationDelegate OnSuccess;` — `UPROPERTY(BlueprintAssignable)`
- L276 _public member_ `FGetGeoLocationDelegate OnFailed;` — `UPROPERTY(BlueprintAssignable)`
- L282 _public prototype_ `static UGetGeoLocationAsyncTaskBlueprintProxy* GetGeoLocationAtWorldPosition(UObject* WorldContextObject, const FVector& WorldPosition);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Geo Tracking", meta=(BlueprintInternalUseOnly="true", WorldContext = "WorldContextObject"))` — Convert a position in UE4 world space into a Geo location.
- L286 _private prototype_ `void Activate() override;` — UBlueprintAsyncActionBase interface
- L287 _private prototype_ `void ReportSuccess() override;`
- L288 _private prototype_ `void ReportFailure() override;`
- L291 _private member_ `FVector WorldPosition = FVector::ZeroVector;`
- L294 _private member_ `TSharedPtr<FGetGeoLocationAsyncTask, ESPMode::ThreadSafe> MyTask;` — The async task to check during Tick()
- L296 _private member_ `FString Error;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AUGMENTEDREALITY_API`
- L186 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGeoTrackingAvailabilityDelegate, bool, bIsAvailable, FString, Error);`
- L270 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FGetGeoLocationDelegate, float, Longitude, float, Latitude, float, Altitude, FString, Error);`

### `Source/Runtime/AugmentedReality/Public/ARLifeCycleComponent.h` (Public)


#### class `UARLifeCycleComponent`  
`class UARLifeCycleComponent : public USceneComponent`  
_L17-59_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Experimental, meta = (BlueprintSpawnableComponent), ClassGroup = "AR Gameplay")`
- inherits: `USceneComponent`
- L21 _private prototype_ `virtual void OnComponentCreated() override;`
- L22 _private prototype_ `virtual void DestroyComponent(bool bPromoteChildren = false) override;`
- L25 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FRequestSpawnARActorDelegate, UClass*, FGuid);`
- L26 _public member_ `static FRequestSpawnARActorDelegate RequestSpawnARActorDelegate;`
- L28 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSpawnARActorDelegate, AARActor*, UARComponent*, FGuid);`
- L29 _public member_ `static FOnSpawnARActorDelegate OnSpawnARActorDelegate;`
- L31 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FRequestDestroyARActorDelegate, AARActor*);`
- L32 _public member_ `static FRequestDestroyARActorDelegate RequestDestroyARActorDelegate;`
- L35 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInstanceARActorSpawnedDelegate, UClass*, ComponentClass, FGuid, NativeID, AARActor*, SpawnedActor);` — Called when an AR actor is spawned on the server
- L37 _public member_ `FInstanceARActorSpawnedDelegate OnARActorSpawnedDelegate;` — `UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnARActorSpawned"))`
- L40 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInstanceARActorToBeDestroyedDelegate, AARActor*, Actor);` — Called just before the AR actor is destroyed on the server
- L42 _public member_ `FInstanceARActorToBeDestroyedDelegate OnARActorToBeDestroyedDelegate;` — `UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnARActorToBeDestroyed"))`
- L45 _protected prototype_ `virtual void OnUnregister() override;`
- L48 _private prototype_ `void CallInstanceRequestSpawnARActorDelegate(UClass* Class, FGuid NativeID);`
- L49 _private prototype_ `void CallInstanceRequestDestroyARActorDelegate(AARActor* Actor);`
- L52 _private prototype_ `void ServerSpawnARActor(UClass* ComponentClass, FGuid NativeID);` — `UFUNCTION(Reliable, Server, WithValidation)`
- L55 _private prototype_ `void ServerDestroyARActor(AARActor* Actor);` — `UFUNCTION(Reliable, Server, WithValidation)`
- L57 _private member_ `FDelegateHandle SpawnDelegateHandle;`
- L58 _private member_ `FDelegateHandle DestroyDelegateHandle;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AUGMENTEDREALITY_API`
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FRequestSpawnARActorDelegate, UClass*, FGuid);`
- L28 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSpawnARActorDelegate, AARActor*, UARComponent*, FGuid);`
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FRequestDestroyARActorDelegate, AARActor*);`
- L35 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInstanceARActorSpawnedDelegate, UClass*, ComponentClass, FGuid, NativeID, AARActor*, SpawnedActor);` — Called when an AR actor is spawned on the server
- L40 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInstanceARActorToBeDestroyedDelegate, AARActor*, Actor);` — Called just before the AR actor is destroyed on the server

### `Source/Runtime/AugmentedReality/Public/ARLightEstimate.h` (Public)


#### class `UARLightEstimate`  
`class UARLightEstimate : public UObject`  
_L19-22_
- reflection: `UCLASS(BlueprintType, Experimental, Category="AR AugmentedReality|Light Estimation")`
- inherits: `UObject`

#### class `UARBasicLightEstimate`  
`class UARBasicLightEstimate : public UARLightEstimate`  
_L25-54_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Category = "AR AugmentedReality|Light Estimation")`
- inherits: `UARLightEstimate`
- L30 _public prototype_ `void SetLightEstimate(float InAmbientIntensityLumens, float InColorTemperatureKelvin);`
- L32 _public prototype_ `void SetLightEstimate(FVector InRGBScaleFactor, float InPixelIntensity);`
- L34 _public prototype_ `void SetLightEstimate(float InColorTemperatureKelvin, FLinearColor InAmbientColor);`
- L37 _public prototype_ `float GetAmbientIntensityLumens() const;` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Light Estimation")`
- L40 _public prototype_ `float GetAmbientColorTemperatureKelvin() const;` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Light Estimation")`
- L43 _public prototype_ `FLinearColor GetAmbientColor() const;` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Light Estimation")`
- L47 _private member_ `float AmbientIntensityLumens;` — `UPROPERTY()`
- L50 _private member_ `float AmbientColorTemperatureKelvin;` — `UPROPERTY()`
- L53 _private member_ `FLinearColor AmbientColor;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUGMENTEDREALITY_API`

### `Source/Runtime/AugmentedReality/Public/AROriginActor.h` (Public)


#### class `AAROriginActor`  
`class AAROriginActor : public AActor`  
_L16-23_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `AActor`
- desc: Simple actor that is spawned at the origin for AR systems that want to hang components on an actor Spawned as a custom class for easier TObjectIterator use
- L22 _public prototype_ `static AAROriginActor* GetOriginActor();` — Used by the AR system to get the origin actor for the current world

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUGMENTEDREALITY_API`

### `Source/Runtime/AugmentedReality/Public/ARPin.h` (Public)


#### class `UARPin`  
`class UARPin : public UObject`  
_L14-124_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Experimental, Category="AR AugmentedReality")`
- inherits: `UObject`
- L19 _public prototype_ `virtual void InitARPin( const TSharedRef<FARSupportInterface , ESPMode::ThreadSafe>& InTrackingSystemOwner, USceneComponent* InComponentToPin, const FTransform& InLocalToTrackingTransform, UARTrackedGeometry* InTrackedGeometry, const FName InDebugName );`
- L27 _public prototype_ `FTransform GetLocalToTrackingTransform() const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Pin")` — Maps from a Pin's Local Space to the Tracking Space. Mapping the origin from the Pin's Local Space to Tracking Space yield the Pin's position in Tracking Space.
- L35 _public prototype_ `FTransform GetLocalToWorldTransform() const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Pin")` — Convenience function. Same as LocalToTrackingTransform, but appends the TrackingToWorld Transform.
- L41 _public prototype_ `EARTrackingState GetTrackingState() const;` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Pin")` — Return the current tracking state of this Pin.
- L47 _public prototype_ `UARTrackedGeometry* GetTrackedGeometry() const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Pin")` — The TrackedGeometry (if any) that this this pin is being "stuck" into.
- L51 _public prototype_ `USceneComponent* GetPinnedComponent() const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Pin")` — @return the PinnedComponent that this UARPin is pinning to the TrackedGeometry
- L54 _public prototype_ `virtual void DebugDraw( UWorld* World, const FLinearColor& Color, float Scale = 5.0f, float PersistForSeconds = 0.0f) const;` — `UFUNCTION()`
- L57 _public prototype_ `FName GetDebugName() const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Pin")`
- L59 _public prototype_ `void SetOnARTrackingStateChanged( const FOnARTrackingStateChanged& InHandler );`
- L61 _public prototype_ `void SetOnARTransformUpdated( const FOnARTransformUpdated& InHandler );`
- L63 _public function_ `void SetNativeResource(void* InNativeResource)`
- L68 _public function_ `void* GetNativeResource()`
- L75 _public prototype_ `FTransform GetLocalToTrackingTransform_NoAlignment() const;`
- L78 _public prototype_ `void OnTrackingStateChanged(EARTrackingState NewTrackingState);` — Notify the ARPin about changes to how it is being tracked.
- L81 _public prototype_ `void OnTransformUpdated(const FTransform& NewLocalToTrackingTransform);` — Notify this UARPin that the transform of the Pin has changed
- L84 _public prototype_ `void UpdateAlignmentTransform( const FTransform& NewAlignmentTransform );` — Notify the UARPin that the AlignmentTransform has changing.
- L86 _public function_ `void SetPinnedComponent(USceneComponent* InComponentToPin)`
- L92 _protected prototype_ `TSharedPtr<FARSupportInterface , ESPMode::ThreadSafe> GetARSystem() const;`
- L95 _private member_ `static uint32 DebugPinId;`
- L98 _private member_ `TObjectPtr<UARTrackedGeometry> TrackedGeometry;` — `UPROPERTY()`
- L101 _private member_ `TObjectPtr<USceneComponent> PinnedComponent;` — `UPROPERTY()`
- L104 _private member_ `FTransform LocalToTrackingTransform;` — `UPROPERTY()`
- L107 _private member_ `FTransform LocalToAlignedTrackingTransform;` — `UPROPERTY()`
- L110 _private member_ `EARTrackingState TrackingState;` — `UPROPERTY()`
- L112 _private member_ `TWeakPtr<FARSupportInterface , ESPMode::ThreadSafe> ARSystem;`
- L114 _private member_ `FName DebugName;`
- L117 _private member_ `FOnARTrackingStateChanged OnARTrackingStateChanged;` — `UPROPERTY(BlueprintAssignable, Category="AR AugmentedReality|Pin")`
- L120 _private member_ `FOnARTransformUpdated OnARTransformUpdated;` — `UPROPERTY(BlueprintAssignable, Category="AR AugmentedReality|Pin")`
- L123 _private member_ `void* NativeResource;` — The native resource pointer on the AR platform.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUGMENTEDREALITY_API`

### `Source/Runtime/AugmentedReality/Public/ARSessionConfig.h` (Public)


#### enum `EARWorldAlignment`  
`enum class EARWorldAlignment : uint8`  
_L19-32_
- reflection: `UENUM(BlueprintType, Category="AR AugmentedReality", meta=(Experimental))`
- desc: Options for how the scene’s coordinate system is constructed. This feature is used by ARKit.
- L22 _public enumerator_ `Gravity` — The coordinate system is aligned with gravity, defined by the vector (0, -1, 0). Origin is the initial position of the device.
- L28 _public enumerator_ `GravityAndHeading` — The coordinate system is aligned with gravity, defined by the vector (0, -1, 0), and compass heading based on True North, defined by the vector (0, 0, -1). Origin is the initial position of the device.
- L31 _public enumerator_ `Camera` — The coordinate system matches the camera's orientation. This option is recommended for Face AR.

#### enum `EARSessionType`  
`enum class EARSessionType : uint8`  
_L36-61_
- reflection: `UENUM(BlueprintType, Category = "AR AugmentedReality", meta = (Experimental))`
- desc: Options for the tracking type of the session. All AR platforms use this structure but only some session tracking are supported on each platform. The options are mutually exclusive.
- L39 _public enumerator_ `None` — No tracking in the session.
- L42 _public enumerator_ `Orientation` — A session where only the orientation of the device is tracked. ARKit supports this type of tracking.
- L45 _public enumerator_ `World` — A session where the position and orientation of the device is tracked relative to objects in the environment. All platforms support this type of tracking.
- L48 _public enumerator_ `Face` — A session where only faces are tracked. ARKit and ARCore support this type of tracking using the front-facing camera.
- L51 _public enumerator_ `Image` — A session where only images supplied by the app are tracked. There is no world tracking. ARKit supports this type of tracking.
- L54 _public enumerator_ `ObjectScanning` — A session where objects are scanned for object detection in a later World Tracking session. ARKit supports this type of tracking.
- L57 _public enumerator_ `PoseTracking` — A session where human poses in 3D are tracked. ARKit supports this type of tracking using the rear-facing camera.
- L60 _public enumerator_ `GeoTracking` — A session where geographic locations are tracked. ARKit supports this type of tracking.

#### enum `EARPlaneDetectionMode`  
`enum class EARPlaneDetectionMode : uint8`  
_L65-75_
- reflection: `UENUM(BlueprintType, Category = "AR AugmentedReality", meta = (Experimental, Bitflags))`
- desc: Options for how flat surfaces are detected. This feature is used by ARCore and ARKit.
- L68 _public enumerator_ `None = 0` — Disables plane detection.
- L71 _public enumerator_ `HorizontalPlaneDetection = 1` — Detects horizontal, flat surfaces.
- L74 _public enumerator_ `VerticalPlaneDetection = 2` — Detects vertical, flat surfaces.

#### enum `EARLightEstimationMode`  
`enum class EARLightEstimationMode : uint8`  
_L80-93_
- reflection: `UENUM(BlueprintType, Category = "AR AugmentedReality", meta = (Experimental))`
- desc: Options for how light is estimated based on the camera capture. This feature is used by ARCore and ARKit.
- L83 _public enumerator_ `None = 0` — Disables light estimation.
- L86 _public enumerator_ `AmbientLightEstimate = 1` — Estimates an ambient light.
- L92 _public enumerator_ `DirectionalLightEstimate = 2` — Estimates a directional light of the environment with an additional key light. Currently not supported.

#### enum `EARFrameSyncMode`  
`enum class EARFrameSyncMode : uint8`  
_L97-104_
- reflection: `UENUM(BlueprintType, Category = "AR AugmentedReality", meta = (Experimental))`
- desc: Options for how the Unreal frame synchronizes with camera image updates. This feature is used by ARCore.
- L100 _public enumerator_ `SyncTickWithCameraImage = 0` — Unreal tick will be synced with the camera image update rate.
- L103 _public enumerator_ `SyncTickWithoutCameraImage = 1` — Unreal tick will not related to the camera image update rate.

#### enum `EAREnvironmentCaptureProbeType`  
`enum class EAREnvironmentCaptureProbeType : uint8`  
_L110-120_
- reflection: `UENUM(BlueprintType)`
- desc: Options for how environment textures are generated. This feature is used by ARKit.
- L113 _public enumerator_ `None` — Disables environment texture generation.
- L116 _public enumerator_ `Manual` — The app specifies where the environment capture probes are located and their size.
- L119 _public enumerator_ `Automatic` — The AR system automatically creates and places the environment capture probes.

#### enum `EARFaceTrackingUpdate`  
`enum class EARFaceTrackingUpdate : uint8`  
_L127-134_
- reflection: `UENUM(BlueprintType)`
- L130 _public enumerator_ `CurvesAndGeo` — Both curves and geometry are updated. This is useful for mesh visualization.
- L133 _public enumerator_ `CurvesOnly` — Only the curve data is updated.

#### enum `EARSessionTrackingFeature`  
`enum class EARSessionTrackingFeature : uint8`  
_L141-160_
- reflection: `UENUM(BlueprintType)`
- L144 _public enumerator_ `None` — No additional features are enabled.
- L147 _public enumerator_ `PoseDetection2D` — Adds tracking for 2D human poses to the session. This feature is used by ARKit.
- L150 _public enumerator_ `PersonSegmentation` — Uses person segmentation for occlusion in the session. This feature is used by ARKit.
- L153 _public enumerator_ `PersonSegmentationWithDepth` — Uses person segmentation with depth information for occlusion in the session. This feature is used by ARKit.
- L156 _public enumerator_ `SceneDepth` — Uses scene depth for occlusion while tracking in the session. This feature is used by ARCore and ARKit.
- L159 _public enumerator_ `SmoothedSceneDepth` — Uses smoothed scene depth for occlusion while tracking in the session. This feature is used by ARKit.

#### enum `EARSceneReconstruction`  
`enum class EARSceneReconstruction : uint8`  
_L166-176_
- reflection: `UENUM(BlueprintType)`
- desc: Options for how the scene should be reconstructed. This feature is used by ARKit.
- L169 _public enumerator_ `None` — Disables scene reconstruction
- L172 _public enumerator_ `MeshOnly` — Creates a mesh approximation of the environment.
- L175 _public enumerator_ `MeshWithClassification` — Creates a mesh approximation of the environment and classifies the objects constructed.

#### class `UARSessionConfig`  
`class UARSessionConfig : public UDataAsset`  
_L182-561_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Category="AR Settings")`
- inherits: `UDataAsset`
- desc: An Unreal Data Asset that defines what features are used in the AR session.
- L188 _public prototype_ `UARSessionConfig();` — The constructor for the AR Session Config Data Asset.
- L193 _public prototype_ `EARWorldAlignment GetWorldAlignment() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see EARWorldAlignment
- L197 _public prototype_ `EARSessionType GetSessionType() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see SessionType
- L201 _public prototype_ `EARPlaneDetectionMode GetPlaneDetectionMode() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see PlaneDetectionMode
- L205 _public prototype_ `EARLightEstimationMode GetLightEstimationMode() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see LightEstimationMode
- L209 _public prototype_ `EARFrameSyncMode GetFrameSyncMode() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see FrameSyncMode
- L213 _public prototype_ `bool ShouldRenderCameraOverlay() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see bEnableAutomaticCameraOverlay
- L217 _public prototype_ `bool ShouldEnableCameraTracking() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see bEnableAutomaticCameraTracking
- L221 _public prototype_ `bool ShouldEnableAutoFocus() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see bEnableAutoFocus
- L225 _public prototype_ `void SetEnableAutoFocus(bool bNewValue);` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see bEnableAutoFocus
- L229 _public prototype_ `bool ShouldResetCameraTracking() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see bResetCameraTracking
- L233 _public prototype_ `void SetResetCameraTracking(bool bNewValue);` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see bResetCameraTracking
- L237 _public prototype_ `bool ShouldResetTrackedObjects() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see bResetTrackedObjects
- L241 _public prototype_ `void SetResetTrackedObjects(bool bNewValue);` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see bResetTrackedObjects
- L245 _public prototype_ `const TArray<UARCandidateImage*>& GetCandidateImageList() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see CandidateImages
- L249 _public prototype_ `void AddCandidateImage(UARCandidateImage* NewCandidateImage);` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — Add a new CandidateImage to the ARSessionConfig.
- L253 _public prototype_ `void RemoveCandidateImage(UARCandidateImage* CandidateImage);` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — Remove a candidate image from the ARSessionConfig, by pointer, note the image object must match, not the content of the image.
- L257 _public prototype_ `void RemoveCandidateImageAtIndex(int Index);` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — Remove a candidate image from the ARSessionConfig, by index.
- L261 _public prototype_ `void ClearCandidateImages();` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — Remove all candidate images from the ARSessionConfig
- L265 _public prototype_ `int32 GetMaxNumSimultaneousImagesTracked() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see MaxNumSimultaneousImagesTracked
- L269 _public prototype_ `EAREnvironmentCaptureProbeType GetEnvironmentCaptureProbeType() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see EnvironmentCaptureProbeType
- L273 _public prototype_ `const TArray<uint8>& GetWorldMapData() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see WorldMapData
- L276 _public prototype_ `void SetWorldMapData(TArray<uint8> WorldMapData);` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see WorldMapData
- L280 _public prototype_ `const TArray<UARCandidateObject*>& GetCandidateObjectList() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see CandidateObjects
- L283 _public prototype_ `void SetCandidateObjectList(const TArray<UARCandidateObject*>& InCandidateObjects);` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see CandidateObjects
- L286 _public prototype_ `void AddCandidateObject(UARCandidateObject* CandidateObject);` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see CandidateObjects
- L290 _public prototype_ `FARVideoFormat GetDesiredVideoFormat() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see DesiredVideoFormat
- L293 _public prototype_ `void SetDesiredVideoFormat(FARVideoFormat NewFormat);` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see DesiredVideoFormat
- L297 _public prototype_ `EARFaceTrackingDirection GetFaceTrackingDirection() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see FaceTrackingDirection
- L300 _public prototype_ `void SetFaceTrackingDirection(EARFaceTrackingDirection InDirection);` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see FaceTrackingDirection
- L304 _public prototype_ `EARFaceTrackingUpdate GetFaceTrackingUpdate() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see FaceTrackingUpdate
- L307 _public prototype_ `void SetFaceTrackingUpdate(EARFaceTrackingUpdate InUpdate);` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see FaceTrackingUpdate
- L311 _public prototype_ `EARSessionTrackingFeature GetEnabledSessionTrackingFeature() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see EnabledSessionTrackingFeatures
- L315 _public prototype_ `EARSceneReconstruction GetSceneReconstructionMethod() const;` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see SceneReconstructionMethod
- L319 _public prototype_ `void SetSessionTrackingFeatureToEnable(EARSessionTrackingFeature InSessionTrackingFeature);` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see EnabledSessionTrackingFeatures
- L323 _public prototype_ `void SetSceneReconstructionMethod(EARSceneReconstruction InSceneReconstructionMethod);` — `UFUNCTION(BlueprintCallable, Category = "AR Settings")` — @see SceneReconstructionMethod
- L326 _public function_ `bool ShouldDoHorizontalPlaneDetection() const` — @see bHorizontalPlaneDetection
- L328 _public function_ `bool ShouldDoVerticalPlaneDetection() const` — @see bVerticalPlaneDetection
- L331 _public prototype_ `const TArray<uint8>& GetSerializedARCandidateImageDatabase() const;` — @see  SerializedARCandidateImageDatabase
- L334 _public prototype_ `UClass* GetPlaneComponentClass(void) const;` — @see PlaneComponentClass
- L336 _public prototype_ `UClass* GetPointComponentClass(void) const;` — @see PointComponentClass
- L338 _public prototype_ `UClass* GetFaceComponentClass(void) const;` — @see FaceComponentClass
- L340 _public prototype_ `UClass* GetImageComponentClass(void) const;` — @see ImageComponentClass
- L342 _public prototype_ `UClass* GetQRCodeComponentClass(void) const;` — @see QRCodeComponentClass
- L344 _public prototype_ `UClass* GetPoseComponentClass(void) const;` — @see PoseComponentClass
- L346 _public prototype_ `UClass* GetEnvironmentProbeComponentClass(void) const;` — @see EnvironmentProbeComponentClass
- L348 _public prototype_ `UClass* GetObjectComponentClass(void) const;` — @see ObjectComponentClass
- L350 _public prototype_ `UClass* GetMeshComponentClass(void) const;` — @see MeshComponentClass
- L352 _public prototype_ `UClass* GetGeoAnchorComponentClass(void) const;` — @see GeoAnchorComponentClass
- L355 _public function_ `UMaterialInterface* GetDefaultMeshMaterial() const` — @see DefaultMeshMaterial
- L357 _public function_ `UMaterialInterface* GetDefaultWireframeMeshMaterial() const` — @see DefaultWireframeMeshMaterial
- L360 _public function_ `int32 GetMaxNumberOfTrackedFaces() const` — @see MaxNumberOfTrackedFaces
- L364 _public member_ `bool bGenerateMeshDataFromTrackedGeometry;` — `UPROPERTY(EditAnywhere, Category = "AR Settings | World Mapping")` — Boolean to determine whether the AR system should generate mesh data that can be used for rendering, collision, NavMesh, and more. This feature is used by OpenXR, Windows Mixed Reality.
- L368 _public member_ `bool bGenerateCollisionForMeshData;` — `UPROPERTY(EditAnywhere, Category = "AR Settings | World Mapping")` — Boolean to determine whether the AR system should generate collision data from the mesh data.
- L372 _public member_ `bool bGenerateNavMeshForMeshData;` — `UPROPERTY(EditAnywhere, Category = "AR Settings | World Mapping")` — Boolean to determine whether the AR system should generate collision data from the mesh data.
- L376 _public member_ `bool bUseMeshDataForOcclusion;` — `UPROPERTY(EditAnywhere, Category = "AR Settings | World Mapping")` — Boolean to determine whether the AR system should render the mesh data as occlusion meshes.
- L380 _public member_ `bool bRenderMeshDataInWireframe;` — `UPROPERTY(EditAnywhere, Category = "AR Settings | World Mapping")` — Boolean to determine whether the AR system should render the mesh data as wireframe.  It is reccomended to simply set the DefaultMeshMaterial to whatever is desired, including a wireframe material and ignore this setting (there is no good reason for this to exist as a special case).
- L384 _public member_ `bool bTrackSceneObjects;` — `UPROPERTY(EditAnywhere, Category = "AR Settings | World Mapping")` — Boolean to determine whether the AR system should track scene objects: @see EARObjectClassification::SceneObject.
- L388 _public member_ `bool bUsePersonSegmentationForOcclusion = true;` — `UPROPERTY(EditAnywhere, Category = "AR Settings | Occlusion")` — Boolean to determine whether to use the person segmentation results for occluding virtual content. This feature is used by ARKit.
- L392 _public member_ `bool bUseSceneDepthForOcclusion = false;` — `UPROPERTY(EditAnywhere, Category = "AR Settings | Occlusion")` — Boolean to determine whether to use the scene depth information for occluding virtual content. This feature is used by ARCore and ARKit.
- L396 _public member_ `bool bUseAutomaticImageScaleEstimation = true;` — `UPROPERTY(EditAnywhere, Category = "AR Settings | Image Tracking")` — Boolean to determine whether to automatically estimate and set the scale of a detected, or tracked, image. This feature is used by ARKit.
- L400 _public member_ `bool bUseStandardOnboardingUX = false;` — `UPROPERTY(EditAnywhere, Category = "AR Settings")` — Boolean to determine whether to use the standard onboarding UX, if the system supports it. This feature is used by ARKit.
- L403 _public prototype_ `bool ShouldUseOptimalVideoFormat() const;` — @see bUseOptimalVideoFormat
- L407 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L413 _protected member_ `EARWorldAlignment WorldAlignment;` — @see EARWorldAlignment
- L417 _protected member_ `EARSessionType SessionType;` — `UPROPERTY(EditAnywhere, Category = "AR Settings")` — @see EARSessionType
- L421 _protected member_ `EARPlaneDetectionMode PlaneDetectionMode_DEPRECATED;` — `UPROPERTY()` — @see EARPlaneDetectionMode
- L425 _protected member_ `bool bHorizontalPlaneDetection;` — `UPROPERTY(EditAnywhere, Category = "AR Settings")` — Boolean to determine whether flat, horizontal surfaces are detected. This feature is used by ARCore and ARKit.
- L429 _protected member_ `bool bVerticalPlaneDetection;` — `UPROPERTY(EditAnywhere, Category = "AR Settings")` — Boolean to determine whether flat, vertical surfaces are detected. This feature is used by ARCore and ARKit.
- L433 _protected member_ `bool bEnableAutoFocus;` — `UPROPERTY(EditAnywhere, Category = "AR Settings")` — Boolean to determine whether the camera should autofocus. Autofocus can cause subtle shifts in position for small objects at further camera distance. This feature is used by ARCore and ARKit.
- L437 _protected member_ `EARLightEstimationMode LightEstimationMode;` — `UPROPERTY(EditAnywhere, Category = "AR Settings")` — @see EARLightEstimationMode
- L441 _protected member_ `EARFrameSyncMode FrameSyncMode;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "AR Settings")` — @see EARFrameSyncMode
- L445 _protected member_ `bool bEnableAutomaticCameraOverlay;` — `UPROPERTY(EditAnywhere, Category="AR Settings")` — Boolean to determine whether the AR camera feed should be drawn as an overlay. Defaults to true. This feature is used by ARCore and ARKit.
- L449 _protected member_ `bool bEnableAutomaticCameraTracking;` — `UPROPERTY(EditAnywhere, Category="AR Settings")` — Boolean to determine whether the virtual camera should track the device movement. Defaults to true. This feature is used by ARCore and ARKit.
- L453 _protected member_ `bool bResetCameraTracking;` — `UPROPERTY(EditAnywhere, Category="AR Settings")` — Boolean to determine whether the AR system should reset camera tracking, such as its origin and transforms, when a new AR session starts. Defaults to true. This feature is used by ARKit.
- L457 _protected member_ `bool bResetTrackedObjects;` — `UPROPERTY(EditAnywhere, Category="AR Settings")` — Boolean to determine whether the AR system should remove any tracked objects when a new AR session starts. Defaults to true. This feature is used by ARKit.
- L461 _protected member_ `TArray<TObjectPtr<UARCandidateImage>> CandidateImages;` — `UPROPERTY(EditAnywhere, Category="AR Settings | Image Tracking")` — The list of candidate images to detect within the AR camera view. This feature is used by ARKit.
- L465 _protected member_ `int32 MaxNumSimultaneousImagesTracked;` — `UPROPERTY(EditAnywhere, Category="AR Settings | Image Tracking")` — The maximum number of images to track at the same time. Defaults to 1. This feature is used by ARKit.
- L469 _protected member_ `EAREnvironmentCaptureProbeType EnvironmentCaptureProbeType;` — `UPROPERTY(EditAnywhere, Category="AR Settings")` — @see EAREnvironmentCaptureProbeType
- L473 _protected member_ `TArray<uint8> WorldMapData;` — `UPROPERTY(VisibleAnywhere, Category="AR Settings | World Mapping")` — A previously saved world that will be loaded when the session starts. This feature is used by ARKit.
- L477 _protected member_ `TArray<TObjectPtr<UARCandidateObject>> CandidateObjects;` — `UPROPERTY(EditAnywhere, Category="AR Settings")` — The list of candidate objects to search for in the scene. This feature is used by ARKit.
- L484 _protected member_ `FARVideoFormat DesiredVideoFormat;` — `UPROPERTY(EditAnywhere, Category="AR Settings")` — The desired video format (or the default, if not supported) that this session should use if the camera is enabled. Use GetSupportedVideoFormats to get a list of device-supported formats.
- L488 _protected member_ `bool bUseOptimalVideoFormat = true;` — `UPROPERTY(EditAnywhere, Category="AR Settings")` — Boolean to determine whether to automatically pick the video format that best matches the device screen size
- L492 _protected member_ `EARFaceTrackingDirection FaceTrackingDirection;` — `UPROPERTY(EditAnywhere, Category="Face AR Settings")` — @see EARFaceTrackingDirection
- L496 _protected member_ `EARFaceTrackingUpdate FaceTrackingUpdate;` — `UPROPERTY(EditAnywhere, Category="Face AR Settings")` — @see EARFaceTrackingUpdate
- L500 _protected member_ `int32 MaxNumberOfTrackedFaces = 1;` — `UPROPERTY(EditAnywhere, Category="Face AR Settings")` — The maximum number of faces to track simultaneously. This feature is used by ARKit.
- L504 _protected member_ `TArray<uint8> SerializedARCandidateImageDatabase;` — `UPROPERTY()` — Data array for storing the cooked image database. This feature is used by ARCore.
- L508 _protected member_ `EARSessionTrackingFeature EnabledSessionTrackingFeature = EARSessionTrackingFeature::None;` — `UPROPERTY(EditAnywhere, Category="AR Settings")` — @see EARSessionTrackingFeature
- L512 _protected member_ `EARSceneReconstruction SceneReconstructionMethod = EARSceneReconstruction::None;` — `UPROPERTY(EditAnywhere, Category="AR Settings")` — @see EARSceneReconstruction
- L516 _protected member_ `TSubclassOf<UARPlaneComponent> PlaneComponentClass;` — `UPROPERTY(EditAnywhere, Category = "AR Gameplay")` — @see UARPlaneComponent
- L520 _protected member_ `TSubclassOf<UARPointComponent> PointComponentClass;` — `UPROPERTY(EditAnywhere, Category = "AR Gameplay")` — @see UARPointComponent
- L524 _protected member_ `TSubclassOf<UARFaceComponent> FaceComponentClass;` — `UPROPERTY(EditAnywhere, Category = "AR Gameplay")` — @see UARFaceComponent
- L528 _protected member_ `TSubclassOf<UARImageComponent> ImageComponentClass;` — `UPROPERTY(EditAnywhere, Category = "AR Gameplay")` — @see UARImageComponent
- L532 _protected member_ `TSubclassOf<UARQRCodeComponent> QRCodeComponentClass;` — `UPROPERTY(EditAnywhere, Category = "AR Gameplay")` — @see UARQRCodeComponent
- L536 _protected member_ `TSubclassOf<UARPoseComponent> PoseComponentClass;` — `UPROPERTY(EditAnywhere, Category = "AR Gameplay")` — @see UARPoseComponent
- L540 _protected member_ `TSubclassOf<UAREnvironmentProbeComponent> EnvironmentProbeComponentClass;` — `UPROPERTY(EditAnywhere, Category = "AR Gameplay")` — @see UAREnvironmentProbeComponent
- L544 _protected member_ `TSubclassOf<UARObjectComponent> ObjectComponentClass;` — `UPROPERTY(EditAnywhere, Category = "AR Gameplay")` — @see UARObjectComponent
- L548 _protected member_ `TSubclassOf<UARMeshComponent> MeshComponentClass;` — `UPROPERTY(EditAnywhere, Category = "AR Gameplay")` — @see UARMeshComponent
- L552 _protected member_ `TSubclassOf<UARGeoAnchorComponent> GeoAnchorComponentClass;` — `UPROPERTY(EditAnywhere, Category = "AR Gameplay")` — @see UARGeoAnchorComponent
- L556 _protected member_ `TObjectPtr<UMaterialInterface> DefaultMeshMaterial;` — `UPROPERTY(EditAnywhere, Category = "AR Settings | World Mapping")` — The default mesh material used by the generated mesh component.
- L560 _protected member_ `TObjectPtr<UMaterialInterface> DefaultWireframeMeshMaterial;` — `UPROPERTY(EditAnywhere, Category = "AR Settings | World Mapping")` — The default mesh material used by the wireframe setting of the generated mesh component.  Note: It is recommended to ignore this wireframe feature and use a wireframe material for the DefaultMeshMaterial instead.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUGMENTEDREALITY_API`
- L76 _prototype_ `ENUM_CLASS_FLAGS(EARPlaneDetectionMode);`

### `Source/Runtime/AugmentedReality/Public/ARSessionConfigCookSupport.h` (Public)


#### class `IARSessionConfigCookSupport`  
`class IARSessionConfigCookSupport : public IModularFeature`  
_L11-21_
- inherits: `IModularFeature`
- L14 _public function_ `static FName GetModularFeatureName()`
- L20 _public prototype_ `virtual void OnSerializeSessionConfig(UARSessionConfig* SessionConfig, FArchive& Ar, TArray<uint8>& SerializedARCandidateImageDatabase) = 0;`

### `Source/Runtime/AugmentedReality/Public/ARSharedWorldGameMode.h` (Public)


#### struct `FARSharedWorldReplicationState`  
`struct FARSharedWorldReplicationState`  
_L16-32_
- reflection: `USTRUCT(BlueprintType)`
- desc: Per player information about what data has been sent to them
- L20 _public function_ `FARSharedWorldReplicationState()`
- L27 _public member_ `int32 PreviewImageOffset;` — `UPROPERTY(BlueprintReadOnly, Category="AR Shared World")` — The offset in the overall image data buffer
- L31 _public member_ `int32 ARWorldOffset;` — `UPROPERTY(BlueprintReadOnly, Category="AR Shared World")` — The offset in the overall ARWorld data buffer

#### class `AARSharedWorldGameMode`  
`class AARSharedWorldGameMode : public AGameMode`  
_L35-85_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `AGameMode`
- L43 _public member_ `int32 BufferSizePerChunk;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="AR Shared World")` — The size of the buffer to use per send request. Must be between 1 and 65535, though should not be max to avoid saturation
- L51 _public prototype_ `void SetPreviewImageData(TArray<uint8> ImageData);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, meta=(DisplayName="Set AR Preview Image Data"), Category="AR Shared World")` — Sets the image data for the shared world game session @param ImageData the blob to use as the image data
- L59 _public prototype_ `void SetARSharedWorldData(TArray<uint8> ARWorldData);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, meta=(DisplayName="Set AR Shared World Data"), Category="AR Shared World")` — Sets the image data for the shared world game session @param ARWorldData the blob to use as the AR world data
- L65 _public prototype_ `void SetARWorldSharingIsReady();` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, meta=(DisplayName="Set AR World Sharing Is Ready"), Category="AR Shared World")` — Tells the game mode that the AR data is ready and should be replicated to all connected clients
- L71 _public prototype_ `AARSharedWorldGameState* GetARSharedWorldGameState();` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="AR Shared World")` — @return the game state for this game mode
- L74 _private prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L75 _private prototype_ `virtual void Logout(AController* Exiting) override;`
- L78 _private member_ `bool bShouldSendSharedWorldData;` — Tracks whether the data should be sent to all clients or not
- L81 _private member_ `TMap<AARSharedWorldPlayerController*, FARSharedWorldReplicationState> PlayerToReplicationStateMap;` — Holds the progress for each player that is being replicated to
- L84 _private member_ `TArray<uint8> SendBuffer;` — Scratch buffer for sending chunks, cached to avoid allocation churn

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AUGMENTEDREALITY_API`

### `Source/Runtime/AugmentedReality/Public/ARSharedWorldGameState.h` (Public)


#### class `AARSharedWorldGameState`  
`class AARSharedWorldGameState : public AGameState`  
_L13-77_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `AGameState`
- L22 _public member_ `TArray<uint8> PreviewImageData;` — The image taken at the time of world saving for use when aligning the AR world later in the session
- L26 _public member_ `TArray<uint8> ARWorldData;` — `UPROPERTY(BlueprintReadOnly, Category="AR Shared World")` — Each client and the host have a copy of the shared world data
- L30 _public member_ `int32 PreviewImageBytesTotal;` — `UPROPERTY(BlueprintReadOnly, Category="AR Shared World")` — The size of the image that will be replicated to each client
- L34 _public member_ `int32 ARWorldBytesTotal;` — `UPROPERTY(BlueprintReadOnly, Category="AR Shared World")` — The size of the AR world data that will be replicated to each client
- L38 _public member_ `int32 PreviewImageBytesDelivered;` — `UPROPERTY(BlueprintReadOnly, Category="AR Shared World")` — The amount of the preview image data that has been replicated to this client so far
- L42 _public member_ `int32 ARWorldBytesDelivered;` — `UPROPERTY(BlueprintReadOnly, Category="AR Shared World")` — The amount of the AR world data that has been replicated to this client so far
- L50 _public prototype_ `void InitSharedWorld(int32 PreviewImageSize, int32 ARWorldDataSize);` — Used to setup the initial values and size the arrays (client) @param PreviewImageSize the total size in bytes of the image data that will be sent @param ARWorldDataSize the total size in bytes of the AR world data that will be sent
- L59 _public prototype_ `void UpdatePreviewImageData(int32 Offset, const uint8* Buffer, int32 Size);` — Copies the buffer into the image data (client) @param Offset where in the buffer to start the copying @param Buffer the chunk of data to copy @param BufferSize the amount of data to copy
- L68 _public prototype_ `void UpdateARWorldData(int32 Offset, const uint8* Buffer, int32 Size);` — Copies the buffer into the AR world data (client) @param Offset where in the buffer to start the copying @param Buffer the chunk of data to copy @param BufferSize the amount of data to copy
- L71 _public prototype_ `void K2_OnARWorldMapIsReady();` — `UFUNCTION(BlueprintImplementableEvent, Category="AR Shared World", meta = (DisplayName = "OnARWorldMapIsReady", ScriptName = "OnARWorldMapIsReady"))`
- L74 _private prototype_ `void TriggerCompletionIfDone();`
- L76 _private member_ `bool bFiredCompletionEvent;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUGMENTEDREALITY_API`

### `Source/Runtime/AugmentedReality/Public/ARSharedWorldPlayerController.h` (Public)


#### class `AARSharedWorldPlayerController`  
`class AARSharedWorldPlayerController : public APlayerController`  
_L13-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `APlayerController`
- L23 _public prototype_ `void ServerMarkReadyForReceiving();` — `UFUNCTION(Reliable, Server, WithValidation)` — Tells the server it is ready for receiving any shared world data
- L32 _public prototype_ `void ClientInitSharedWorld(int32 PreviewImageSize, int32 ARWorldDataSize);` — `UFUNCTION(Reliable, Client, WithValidation)` — Used to setup the initial values and size the arrays (client) @param PreviewImageSize the total size in bytes of the image data that will be sent @param ARWorldDataSize the total size in bytes of the AR world data that will be sent
- L42 _public prototype_ `void ClientUpdatePreviewImageData(int32 Offset, const TArray<uint8>& Buffer);` — `UFUNCTION(Reliable, Client, WithValidation)` — Copies the buffer into the image data (client) @param Offset where in the buffer to start the copying @param Buffer the chunk of data to copy @param BufferSize the amount of data to copy
- L52 _public prototype_ `void ClientUpdateARWorldData(int32 Offset, const TArray<uint8>& Buffer);` — `UFUNCTION(Reliable, Client, WithValidation)` — Copies the buffer into the AR world data (client) @param Offset where in the buffer to start the copying @param Buffer the chunk of data to copy @param BufferSize the amount of data to copy
- L55 _public function_ `bool IsReadyToReceive() const` — @return whether this player can start receiving the ar world data
- L58 _private prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L60 _private prototype_ `AARSharedWorldGameState* GetGameState();`
- L61 _private prototype_ `bool IsGameStateReady();`
- L63 _private member_ `bool bIsReadyToReceive;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUGMENTEDREALITY_API`

### `Source/Runtime/AugmentedReality/Public/ARSkyLight.h` (Public)


#### class `AARSkyLight`  
`class AARSkyLight : public ASkyLight`  
_L16-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ASkyLight`
- desc: This sky light class forces a refresh of the cube map data when an AR environment probe changes
- L24 _public prototype_ `void SetEnvironmentCaptureProbe(UAREnvironmentCaptureProbe* InCaptureProbe);` — `UFUNCTION(BlueprintCallable, Category="AR AugmentedReality|SkyLight")` — Sets the environment capture probe that this sky light is driven by
- L27 _private prototype_ `virtual void Tick(float DeltaTime) override;`
- L30 _private member_ `TObjectPtr<UAREnvironmentCaptureProbe> CaptureProbe;` — `UPROPERTY()`
- L33 _private member_ `float LastUpdateTimestamp;` — The timestamp from the environment probe when we last updated the cube map

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUGMENTEDREALITY_API`

### `Source/Runtime/AugmentedReality/Public/ARSupportInterface.h` (Public)


#### class `FARSupportInterface`  
`class FARSupportInterface : public TSharedFromThis<FARSupportInterface, ESPMode::ThreadSafe>, public FGCObject, public IModularFeature`  
_L28-180_
- inherits: `TSharedFromThis<FARSupportInterface,ESPMode::ThreadSafe>,FGCObject,IModularFeature`
- L31 _public prototype_ `FARSupportInterface (IARSystemSupport* InARImplementation, IXRTrackingSystem* InXRTrackingSystem);`
- L32 _public prototype_ `virtual ~FARSupportInterface ();`
- L35 _public function_ `static FName GetModularFeatureName()`
- L41 _public prototype_ `void InitializeARSystem();`
- L42 _public prototype_ `IXRTrackingSystem* GetXRTrackingSystem();`
- L44 _public prototype_ `bool StartARGameFrame(FWorldContext& WorldContext);`
- L46 _public prototype_ `const FTransform& GetAlignmentTransform() const;`
- L47 _public prototype_ `const UARSessionConfig& GetSessionConfig() const;`
- L48 _public prototype_ `UARSessionConfig& AccessSessionConfig();`
- L51 _public prototype_ `EARTrackingQuality GetTrackingQuality() const;` — \see UARBlueprintLibrary::GetTrackingQuality()
- L53 _public prototype_ `EARTrackingQualityReason GetTrackingQualityReason() const;` — \see UARBlueprintLibrary::GetTrackingQualityReason()
- L55 _public prototype_ `void StartARSession(UARSessionConfig* InSessionConfig);` — \see UARBlueprintLibrary::StartARSession()
- L57 _public prototype_ `void PauseARSession();` — \see UARBlueprintLibrary::PauseARSession()
- L59 _public prototype_ `void StopARSession();` — \see UARBlueprintLibrary::StopARSession()
- L61 _public prototype_ `FARSessionStatus GetARSessionStatus() const;` — \see UARBlueprintLibrary::GetARSessionStatus()
- L63 _public prototype_ `bool IsSessionTypeSupported(EARSessionType SessionType) const;` — \see UARBlueprintLibrary::IsSessionTypeSupported()
- L66 _public prototype_ `bool ToggleARCapture(const bool bOnOff, const EARCaptureType CaptureType);` — \see UARBlueprintLibrary::ToggleARCapture()
- L69 _public prototype_ `void SetEnabledXRCamera(bool bOnOff);` — \see UARBlueprintLibrary::ToggleARCapture()
- L71 _public prototype_ `FIntPoint ResizeXRCamera(const FIntPoint& InSize);` — \see UARBlueprintLibrary::ToggleARCapture()
- L78 _public prototype_ `void SetAlignmentTransform(const FTransform& InAlignmentTransform);` — \see UARBlueprintLibrary::SetAlignmentTransform() \see IARSystemSupport To understand the various spaces involved in Augmented Reality system, \see IARSystemSupport.
- L81 _public prototype_ `TArray<FARTraceResult> LineTraceTrackedObjects(const FVector2D ScreenCoords, EARLineTraceChannels TraceChannels);` — \see UARBlueprintLibrary::LineTraceTrackedObjects()
- L83 _public prototype_ `TArray<FARTraceResult> LineTraceTrackedObjects(const FVector Start, const FVector End, EARLineTraceChannels TraceChannels);` — \see UARBlueprintLibrary::LineTraceTrackedObjects()
- L85 _public prototype_ `TArray<UARTrackedGeometry*> GetAllTrackedGeometries() const;` — \see UARBlueprintLibrary::GetAllTrackedGeometries()
- L87 _public prototype_ `TArray<UARPin*> GetAllPins() const;` — \see UARBlueprintLibrary::GetAllPins()
- L89 _public prototype_ `bool IsEnvironmentCaptureSupported() const;` — \see UARBlueprintLibrary::IsEnvironmentCaptureSupported()
- L91 _public prototype_ `bool AddManualEnvironmentCaptureProbe(FVector Location, FVector Extent);` — \see UARBlueprintLibrary::AddEnvironmentCaptureProbe()
- L93 _public prototype_ `TSharedPtr<FARGetCandidateObjectAsyncTask, ESPMode::ThreadSafe> GetCandidateObject(FVector Location, FVector Extent) const;` — Creates an async task that will perform the work in the background
- L95 _public prototype_ `TSharedPtr<FARSaveWorldAsyncTask, ESPMode::ThreadSafe> SaveWorld() const;` — Creates an async task that will perform the work in the background
- L97 _public prototype_ `EARWorldMappingState GetWorldMappingStatus() const;` — @return the current mapping status
- L100 _public prototype_ `UARLightEstimate* GetCurrentLightEstimate() const;` — \see UARBlueprintLibrary::GetCurrentLightEstimate()
- L103 _public prototype_ `UARPin* PinComponent(USceneComponent* ComponentToPin, const FTransform& PinToWorldTransform, UARTrackedGeometry* TrackedGeometry = nullptr, const FName DebugName = NAME_None);` — \see UARBlueprintLibrary::PinComponent()
- L105 _public prototype_ `UARPin* PinComponent(USceneComponent* ComponentToPin, const FARTraceResult& HitResult, const FName DebugName = NAME_None);` — \see UARBlueprintLibrary::PinComponentToTraceResult()
- L107 _public prototype_ `void RemovePin(UARPin* PinToRemove);` — \see UARBlueprintLibrary::RemovePin()
- L108 _public prototype_ `bool TryGetOrCreatePinForNativeResource(void* InNativeResource, const FString& InAnchorName, UARPin*& OutAnchor);`
- L111 _public prototype_ `TArray<FARVideoFormat> GetSupportedVideoFormats(EARSessionType SessionType = EARSessionType::World) const;` — \see UARBlueprintLibrary::GetSupportedVideoFormats()
- L114 _public prototype_ `TArray<FVector> GetPointCloud() const;` — @return the current point cloud data for the ar scene
- L117 _public prototype_ `UARCandidateImage* AddRuntimeCandidateImage(UARSessionConfig* SessionConfig, UTexture2D* CandidateTexture, FString FriendlyName, float PhysicalWidth);` — \see UARBlueprintLibrary::AddRuntimeCandidateImage()
- L119 _public prototype_ `void* GetARSessionRawPointer();`
- L120 _public prototype_ `void* GetGameThreadARFrameRawPointer();`
- L123 _public prototype_ `bool IsSessionTrackingFeatureSupported(EARSessionType SessionType, EARSessionTrackingFeature SessionTrackingFeature) const;` — \see UARBlueprintLibrary::IsSessionTrackingFeatureSupported()
- L126 _public prototype_ `TArray<FARPose2D> GetTracked2DPose() const;` — \see UARBlueprintLibrary::GetTracked2DPose()
- L129 _public prototype_ `bool IsSceneReconstructionSupported(EARSessionType SessionType, EARSceneReconstruction SceneReconstructionMethod) const;` — \see UARBlueprintLibrary::IsSceneReconstructionSupported()
- L132 _public prototype_ `bool AddTrackedPointWithName(const FTransform& WorldTransform, const FString& PointName, bool bDeletePointsWithSameName);` — \see UARBlueprintLibrary::AddTrackedPointWithName()
- L135 _public prototype_ `int32 GetNumberOfTrackedFacesSupported() const;` — \see UARBlueprintLibrary::GetNumberOfTrackedFacesSupported()
- L138 _public prototype_ `UARTexture* GetARTexture(EARTextureType TextureType) const;` — \see UARBlueprintLibrary::GetARTexture()
- L141 _public prototype_ `bool GetCameraIntrinsics(FARCameraIntrinsics& OutCameraIntrinsics) const;` — \see UARBlueprintLibrary::GetCameraIntrinsics()
- L144 _public prototype_ `bool IsARAvailable() const;` — \see UARBlueprintLibrary::IsARSupported()
- L147 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L148 _public function_ `virtual FString GetReferencerName() const override`
- L156 _public prototype_ `DECLARE_AR_SI_DELEGATE_FUNCS(OnTrackableUpdated) DECLARE_AR_SI_DELEGATE_FUNCS(OnTrackableRemoved)`
- L162 _public prototype_ `bool IsLocalPinSaveSupported() const;`
- L163 _public prototype_ `bool ArePinsReadyToLoad();`
- L164 _public prototype_ `void LoadARPins(TMap<FName, UARPin*>& LoadedPins);`
- L165 _public prototype_ `bool SaveARPin(FName InName, UARPin* InPin);`
- L166 _public prototype_ `void RemoveSavedARPin(FName InName);`
- L167 _public prototype_ `void RemoveAllSavedARPins();`
- L170 _public member_ `FARSystemOnSessionStarted OnARSessionStarted;`
- L171 _public member_ `FARSystemOnAlignmentTransformUpdated OnAlignmentTransformUpdated;`
- L174 _private member_ `IARSystemSupport* ARImplemention;`
- L175 _private member_ `IXRTrackingSystem* XRTrackingSystem;`
- L178 _private member_ `FTransform AlignmentTransform;` — Alignment transform between AR System's tracking space and Unreal's World Space. Useful in static lighting/geometry scenarios.
- L179 _private member_ `TObjectPtr<UARSessionConfig> ARSettings;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUGMENTEDREALITY_API`
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE(FARSystemOnSessionStarted);`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE(FARSystemOnSessionStarted);`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FARSystemOnAlignmentTransformUpdated, const FTransform&);`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FARSystemOnAlignmentTransformUpdated, const FTransform&);`
- L18 _macro_ `#define DECLARE_AR_SI_DELEGATE_FUNCS(DelegateName) \`

### `Source/Runtime/AugmentedReality/Public/ARSystem.h` (Public)


#### class `IARSystemSupport`  
`class IARSystemSupport`  
_L77-279_
- desc: Implement IARSystemSupport for any platform that wants to be an Unreal Augmented Reality System. e.g. AppleARKit, GoogleARCore. This interface is included as part of the abstract class \c FARSupportInterface . The functions you must override are coalesced here for clarity. Augmented Reality Spaces Engineers working on supporting Augmented Reality must be aware of three spaces: TrackingSpace : This is the space defined by the underlying AR system (e.g. ARKit, ARCore, etc.) Unreal has no control over the origin of this space. AlignedTrackingSpace : To regain control of TrackingSpace, Unreal applies the AlignmentTransform so bend TrackingSpace to its will. If you are implementing IARSystemSupport, you will need to understand this transform and apply it accordingly. WorldSpace : This is Unreal's coordinate system. Coordinates from Tracking Space can be translated into WorldSpace by using the AlignmentTransform and the TrackingToWorldTransform. \verbatim [TrackingSpace]--(AlignmentTransform)-->[AlignedTrackingSpace]--(TrackingToWorld)-->[WorldSpace] \endverbatim
- L81 _public function_ `virtual void OnARSystemInitialized()` — Invoked after the base AR system has been initialized.
- L83 _public function_ `virtual bool OnStartARGameFrame(FWorldContext& WorldContext)`
- L86 _public prototype_ `virtual EARTrackingQuality OnGetTrackingQuality() const = 0;` — @return the tracking quality; if unable to determine tracking quality, return EARTrackingQuality::NotAvailable
- L89 _public prototype_ `virtual EARTrackingQualityReason OnGetTrackingQualityReason() const = 0;` — @return the reason of limited tracking quality; if the state is not limited, return EARTrackingQualityReason::None
- L98 _public prototype_ `virtual void OnStartARSession(UARSessionConfig* SessionConfig) = 0;` — Start the AR system. @param SessionType The type of AR session to create @return true if the system was successfully started
- L101 _public prototype_ `virtual void OnPauseARSession() = 0;` — Stop the AR system but leave its internal state intact.
- L104 _public prototype_ `virtual void OnStopARSession() = 0;` — Stop the AR system and reset its internal state; this task must succeed.
- L107 _public prototype_ `virtual FARSessionStatus OnGetARSessionStatus() const = 0;` — @return the info about whether the session is running normally or encountered some kind of error.
- L110 _public prototype_ `virtual bool IsARAvailable() const = 0;` — Returns true/false based on whether AR features are available
- L118 _public prototype_ `virtual void OnSetAlignmentTransform(const FTransform& InAlignmentTransform) = 0;` — Set a transform that will align the Tracking Space origin to the World Space origin. This is useful for supporting static geometry and static lighting in AR. Note: Usually, an app will ask the user to select an appropriate location for some experience. This allows us to choose an appropriate alignment transform.
- L126 _public prototype_ `virtual TArray<FARTraceResult> OnLineTraceTrackedObjects( const FVector2D ScreenCoord, EARLineTraceChannels TraceChannels ) = 0;` — Trace all the tracked geometries and determine which have been hit by a ray cast from `ScreenCoord`. Only geometries specified in `TraceChannels` are considered. @return a list of all the geometries that were hit, sorted by distance
- L127 _public prototype_ `virtual TArray<FARTraceResult> OnLineTraceTrackedObjects( const FVector Start, const FVector End, EARLineTraceChannels TraceChannels ) = 0;`
- L130 _public prototype_ `virtual TArray<UARTrackedGeometry*> OnGetAllTrackedGeometries() const = 0;` — @return a TArray of all the tracked geometries known to your ar system
- L133 _public prototype_ `virtual TArray<UARPin*> OnGetAllPins() const = 0;` — @return a TArray of all the pins that attach components to TrackedGeometries
- L136 _public prototype_ `virtual bool OnIsTrackingTypeSupported(EARSessionType SessionType) const = 0;` — @return whether the specified tracking type is supported by this device
- L138 _public function_ `virtual bool OnToggleARCapture(const bool bOnOff, const EARCaptureType CaptureType)`
- L140 _public function_ `virtual void OnSetEnabledXRCamera(bool bOnOff)`
- L141 _public function_ `virtual FIntPoint OnResizeXRCamera(const FIntPoint& InSize)`
- L144 _public prototype_ `virtual UARLightEstimate* OnGetCurrentLightEstimate() const = 0;` — @return the best available light estimate; nullptr if light estimation is inactive or not available
- L149 _public prototype_ `virtual UARPin* FindARPinByComponent(const USceneComponent* Component) const = 0;` — Given a scene component find the ARPin which it is pinned by, if any.
- L157 _public prototype_ `virtual UARPin* OnPinComponent(USceneComponent* ComponentToPin, const FTransform& PinToWorldTransform, UARTrackedGeometry* TrackedGeometry = nullptr, const FName DebugName = NAME_None) = 0;` — Pin an Unreal Component to a location in the world. Optionally, associate with a TrackedGeometry to receive transform updates that effectively attach the component to the geometry. @return the UARPin object that is pinning the component to the world and (optionally) a TrackedGeometry
- L166 _public prototype_ `virtual bool OnPinComponentToARPin(USceneComponent* ComponentToPin, UARPin* Pin) = 0;` — Pin a component to an existing ARPin. If the component is alreayd pinned it will first be removed from that pin, which will be left empty. If the target Pin is already in use the component previously pinned to it will be unpinned. @return true if the operation was successful
- L172 _public prototype_ `virtual void OnRemovePin(UARPin* PinToRemove) = 0;` — Given a pin, remove it and stop updating the associated component based on the tracked geometry. The component in question will continue to track with the world, but will not get updates specific to a TrackedGeometry.
- L179 _public function_ `virtual bool OnTryGetOrCreatePinForNativeResource(void* InNativeResource, const FString& InPinName, UARPin*& OutPin)` — Given the platform specific native resource for a pin, create a pin. @return true when a pin is successfully created, otherwise false
- L182 _public prototype_ `virtual bool OnAddManualEnvironmentCaptureProbe(FVector Location, FVector Extent) = 0;` — Tells the ARSystem to generate a capture probe at the specified location if supported
- L185 _public prototype_ `virtual TSharedPtr<FARGetCandidateObjectAsyncTask, ESPMode::ThreadSafe> OnGetCandidateObject(FVector Location, FVector Extent) const = 0;` — Generates a UARCandidateObject from the point cloud data within the location and its extent using an async task
- L188 _public prototype_ `virtual TSharedPtr<FARSaveWorldAsyncTask, ESPMode::ThreadSafe> OnSaveWorld() const = 0;` — Saves the AR world to a byte array using an async task
- L191 _public prototype_ `virtual EARWorldMappingState OnGetWorldMappingStatus() const = 0;` — @return the current mapping status
- L194 _public prototype_ `virtual TArray<FARVideoFormat> OnGetSupportedVideoFormats(EARSessionType SessionType) const = 0;` — @return The list of supported video formats for this device and session type
- L197 _public prototype_ `virtual TArray<FVector> OnGetPointCloud() const = 0;` — @return the current point cloud data for the ar scene
- L200 _public prototype_ `virtual bool OnAddRuntimeCandidateImage(UARSessionConfig* SessionConfig, UTexture2D* CandidateTexture, FString FriendlyName, float PhysicalWidth) = 0;` — Add candidate image at runtime @return True if it added the iamge successfully
- L202 _public prototype_ `virtual void* GetARSessionRawPointer() = 0;`
- L203 _public prototype_ `virtual void* GetGameThreadARFrameRawPointer() = 0;`
- L206 _public function_ `virtual bool OnIsSessionTrackingFeatureSupported(EARSessionType SessionType, EARSessionTrackingFeature SessionTrackingFeature) const` — @return if a particular session feature is supported on this device
- L209 _public function_ `virtual TArray<FARPose2D> OnGetTracked2DPose() const` — @return all the tracked 2D poses in AR
- L212 _public function_ `virtual bool OnIsSceneReconstructionSupported(EARSessionType SessionType, EARSceneReconstruction SceneReconstructionMethod) const` — @return the required scene construction method is supported
- L214 _public function_ `virtual bool OnAddTrackedPointWithName(const FTransform& WorldTransform, const FString& PointName, bool bDeletePointsWithSameName)`
- L217 _public function_ `virtual int32 OnGetNumberOfTrackedFacesSupported() const` — @return the max number of faces can be tracked at the same time
- L220 _public function_ `virtual UARTexture* OnGetARTexture(EARTextureType TextureType) const` — @return the AR texture for the specified type
- L222 _public prototype_ `virtual ~IARSystemSupport()= default;`
- L229 _public prototype_ `DEFINE_AR_DELEGATE_ONE_PARAM(OnTrackableAdded, UARTrackedGeometry* );` — Delegate called when an ar item is added to the scene @param Added the item that was added
- L236 _public prototype_ `DEFINE_AR_DELEGATE_ONE_PARAM(OnTrackableUpdated, UARTrackedGeometry* );` — Delegate called when an ar item is updated @param Updated the item that was updated
- L243 _public prototype_ `DEFINE_AR_DELEGATE_ONE_PARAM(OnTrackableRemoved, UARTrackedGeometry* );` — Delegate called when an ar item is removed from the scene @param Removed the item that was removed
- L249 _public function_ `virtual bool IsLocalPinSaveSupported() const`
- L254 _public function_ `virtual bool ArePinsReadyToLoad()`
- L260 _public function_ `virtual void LoadARPins(TMap<FName, UARPin*>& LoadedPins)`
- L264 _public function_ `virtual bool SaveARPin(FName InName, UARPin* InPin)`
- L269 _public function_ `virtual void RemoveSavedARPin(FName InName)`
- L273 _public function_ `virtual void RemoveAllSavedARPins()`
- L278 _public function_ `virtual bool OnGetCameraIntrinsics(FARCameraIntrinsics& OutCameraIntrinsics) const`

#### Free symbols / members of external scopes

- L19 _macro_ `#define DEFINE_AR_DELEGATE_BASE(DelegateName) \`
- L39 _macro_ `#define DEFINE_AR_DELEGATE_ONE_PARAM(DelegateName, Param1Type) \` — need to move refactor some class hierarchies to make this protected again

### `Source/Runtime/AugmentedReality/Public/ARSystemSupportBase.h` (Public)


#### class `FARSystemSupportBase`  
`class FARSystemSupportBase : public IARSystemSupport`  
_L11-15_
- inherits: `IARSystemSupport`
- L14 _public prototype_ `virtual bool OnPinComponentToARPin(USceneComponent* ComponentToPin, UARPin* Pin) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUGMENTEDREALITY_API`

### `Source/Runtime/AugmentedReality/Public/ARTextures.h` (Public)


#### enum `EARTextureType`  
`enum class EARTextureType : uint8`  
_L12-22_
- reflection: `UENUM(BlueprintType, Category="AR AugmentedReality", meta=(Experimental))`
- L14 _public enumerator_ `Unknown`
- L15 _public enumerator_ `CameraImage`
- L16 _public enumerator_ `CameraDepth`
- L17 _public enumerator_ `EnvironmentCapture`
- L18 _public enumerator_ `PersonSegmentationImage`
- L19 _public enumerator_ `PersonSegmentationDepth`
- L20 _public enumerator_ `SceneDepthMap`
- L21 _public enumerator_ `SceneDepthConfidenceMap`

#### class `UARTexture`  
`class UARTexture : public UTexture`  
_L30-71_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `UTexture`
- desc: Base class for all AR texture types. Derived from UTexture instead of UTexture2D because UTexture2D is all about streaming and source art ? probably should have been UTexture2DDynamic
- L39 _public function_ `template<class T> static T* CreateARTexture(EARTextureType InTextureType)` — Factory function for creating a new AR  texture of a particular type
- L48 _public function_ `virtual float GetSurfaceWidth() const override` — UTexture interface implementation
- L49 _public function_ `virtual float GetSurfaceHeight() const override`
- L50 _public function_ `virtual float GetSurfaceDepth() const override`
- L51 _public function_ `virtual uint32 GetSurfaceArraySize() const override`
- L52 _public function_ `virtual FGuid GetExternalTextureGuid() const override`
- L53 _public function_ `virtual ETextureClass GetTextureClass() const`
- L58 _public member_ `EARTextureType TextureType = EARTextureType::Unknown;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality", meta=(Experimental))` — The type of texture this is
- L62 _public member_ `float Timestamp;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality", meta=(Experimental))` — The timestamp this texture was captured at
- L66 _public member_ `FGuid ExternalTextureGuid;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality", meta=(Experimental))` — The guid of texture that gets registered as an external texture
- L70 _public member_ `FVector2f Size;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality", meta=(Experimental))` — The width and height of the texture

#### class `UARTextureCameraImage`  
`class UARTextureCameraImage : public UARTexture`  
_L77-80_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `UARTexture`
- desc: Base class for all AR textures that represent the camera image data

#### enum `EARDepthQuality`  
`enum class EARDepthQuality : uint8`  
_L83-90_
- reflection: `UENUM(BlueprintType, Category="AR AugmentedReality", meta=(Experimental))`
- L85 _public enumerator_ `Unkown`
- L87 _public enumerator_ `Low` — Not suitable to use as part of a rendering pass or for scene reconstruction
- L89 _public enumerator_ `High` — Suitable for rendering against or for use in scene reconstruction

#### enum `EARDepthAccuracy`  
`enum class EARDepthAccuracy : uint8`  
_L93-100_
- reflection: `UENUM(BlueprintType, Category="AR AugmentedReality", meta=(Experimental))`
- L95 _public enumerator_ `Unkown`
- L97 _public enumerator_ `Approximate` — Suitable for gross sorting of depths
- L99 _public enumerator_ `Accurate` — Accurate depth values that match the physical world

#### class `UARTextureCameraDepth`  
`class UARTextureCameraDepth : public UARTexture`  
_L106-122_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `UARTexture`
- desc: Base class for all AR textures that represent the camera depth data
- L113 _public member_ `EARDepthQuality DepthQuality;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality", meta=(Experimental))` — The quality of the depth information captured this frame
- L117 _public member_ `EARDepthAccuracy DepthAccuracy;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality", meta=(Experimental))` — The accuracy of the depth information captured this frame
- L121 _public member_ `bool bIsTemporallySmoothed;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality", meta=(Experimental))` — Whether or not the depth information is temporally smoothed

#### class `UAREnvironmentCaptureProbeTexture`  
`class UAREnvironmentCaptureProbeTexture : public UTextureCube`  
_L128-156_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `UTextureCube`
- desc: Base class for all AR textures that represent the environment for lighting and reflection
- L134 _public function_ `virtual float GetSurfaceWidth() const override` — UTexture interface implementation
- L135 _public function_ `virtual float GetSurfaceHeight() const override`
- L136 _public function_ `virtual float GetSurfaceDepth() const override`
- L137 _public function_ `virtual uint32 GetSurfaceArraySize() const override`
- L138 _public function_ `virtual FGuid GetExternalTextureGuid() const override`
- L143 _public member_ `EARTextureType TextureType;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality", meta=(Experimental))` — The type of texture this is
- L147 _public member_ `float Timestamp;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality", meta=(Experimental))` — The timestamp this texture was captured at
- L151 _public member_ `FGuid ExternalTextureGuid;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality", meta=(Experimental))` — The guid of texture that gets registered as an external texture
- L155 _public member_ `FVector2f Size;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality", meta=(Experimental))` — The width and height of the texture

### `Source/Runtime/AugmentedReality/Public/ARTraceResult.h` (Public)


#### struct `FARTraceResult`  
`struct FARTraceResult`  
_L16-71_
- reflection: `USTRUCT(BlueprintType, Category="AR AugmentedReality", meta=(Experimental))`
- desc: A result of an intersection found during a hit-test.
- L20 _public prototype_ `FARTraceResult();`
- L22 _public prototype_ `FARTraceResult( const TSharedPtr<FARSupportInterface , ESPMode::ThreadSafe>& InARSystem, float InDistanceFromCamera, EARLineTraceChannels InTraceChannel, const FTransform& InLocalToTrackingTransform, UARTrackedGeometry* InTrackedGeometry );`
- L24 _public prototype_ `float GetDistanceFromCamera() const;`
- L26 _public prototype_ `void SetLocalToWorldTransform(const FTransform& LocalToWorldTransform);`
- L28 _public prototype_ `FTransform GetLocalToTrackingTransform() const;`
- L30 _public prototype_ `FTransform GetLocalToWorldTransform() const;`
- L32 _public prototype_ `FTransform GetLocalTransform() const;`
- L34 _public prototype_ `UARTrackedGeometry* GetTrackedGeometry() const;`
- L36 _public prototype_ `EARLineTraceChannels GetTraceChannel() const;`
- L50 _private member_ `float DistanceFromCamera;` — `UPROPERTY()` — Distance (in Unreal Units) between the camera and the point where the line trace contacted tracked geometry.
- L54 _private member_ `EARLineTraceChannels TraceChannel;` — `UPROPERTY()` — The trace channel that generated this trace result. (used for filtering)
- L61 _private member_ `FTransform LocalTransform;` — `UPROPERTY()` — The transformation matrix that defines the intersection's rotation, translation and scale in AR system's local space.
- L67 _private member_ `TObjectPtr<UARTrackedGeometry> TrackedGeometry;` — `UPROPERTY()` — A pointer to the geometry data that was intersected by this trace, if any.
- L70 _private member_ `TSharedPtr<FARSupportInterface , ESPMode::ThreadSafe> ARSystem;` — A reference to the AR system that creates this hit test result.

#### struct `FARTraceResult::FARTraceResultComparer`  
`struct FARTraceResultComparer`  
_L38-44_
- L40 _public function_ `inline bool operator()(const FARTraceResult& A, const FARTraceResult& B) const`

#### class `UARTraceResultDummy`  
`class UARTraceResultDummy : public UObject`  
_L74-77_
- reflection: `UCLASS()`
- inherits: `UObject`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUGMENTEDREALITY_API`

### `Source/Runtime/AugmentedReality/Public/ARTrackable.h` (Public)


#### class `UARTrackedGeometry`  
`class UARTrackedGeometry : public UObject`  
_L16-129_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L21 _public prototype_ `UARTrackedGeometry();`
- L23 _public prototype_ `void InitializeNativeResource(IARRef* InNativeResource);`
- L25 _public prototype_ `virtual void DebugDraw( UWorld* World, const FLinearColor& OutlineColor, float OutlineThickness, float PersistForSeconds = 0.0f) const;`
- L27 _public prototype_ `void GetNetworkPayload(FARMeshUpdatePayload& Payload);`
- L29 _public prototype_ `void UpdateTrackedGeometryNoMove(const TSharedRef<FARSupportInterface, ESPMode::ThreadSafe>& InTrackingSystem, uint32 FrameNumber, double Timestamp);`
- L30 _public prototype_ `void UpdateTrackedGeometry(const TSharedRef<FARSupportInterface , ESPMode::ThreadSafe>& InTrackingSystem, uint32 FrameNumber, double Timestamp, const FTransform& InLocalToTrackingTransform, const FTransform& InAlignmentTransform );`
- L32 _public prototype_ `void UpdateTrackingState( EARTrackingState NewTrackingState );`
- L34 _public prototype_ `void UpdateAlignmentTransform( const FTransform& NewAlignmentTransform );`
- L36 _public prototype_ `void SetDebugName( FName InDebugName );`
- L38 _public prototype_ `void SetName(const FString& InName);`
- L40 _public prototype_ `IARRef* GetNativeResource();`
- L43 _public prototype_ `FTransform GetLocalToWorldTransform() const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Tracked Geometry")`
- L46 _public prototype_ `FTransform GetLocalToTrackingTransform() const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Tracked Geometry")`
- L48 _public prototype_ `FTransform GetLocalToTrackingTransform_NoAlignment() const;`
- L51 _public prototype_ `EARTrackingState GetTrackingState() const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Tracked Geometry")`
- L52 _public prototype_ `void SetTrackingState(EARTrackingState NewState);`
- L55 _public prototype_ `bool IsTracked() const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Tracked Geometry")`
- L58 _public prototype_ `FName GetDebugName() const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Tracked Geometry")`
- L61 _public prototype_ `const FString& GetName() const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Tracked Geometry")`
- L64 _public prototype_ `int32 GetLastUpdateFrameNumber() const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Tracked Geometry")`
- L67 _public prototype_ `float GetLastUpdateTimestamp() const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Tracked Geometry")`
- L68 _public function_ `inline void SetLastUpdateTimestamp(double InTimestamp)`
- L71 _public prototype_ `UMRMeshComponent* GetUnderlyingMesh();` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Tracked Geometry")`
- L72 _public prototype_ `void SetUnderlyingMesh(UMRMeshComponent* InMRMeshComponent);`
- L75 _public member_ `FGuid UniqueId;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality|Tracked Geometry")`
- L78 _public function_ `EARObjectClassification GetObjectClassification() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Scene Understanding")`
- L79 _public function_ `void SetObjectClassification(EARObjectClassification InClassification)`
- L82 _public function_ `bool HasSpatialMeshUsageFlag(const EARSpatialMeshUsageFlags InFlag) const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Scene Understanding")`
- L83 _public function_ `void SetSpatialMeshUsageFlags(const EARSpatialMeshUsageFlags InFlags)`
- L86 _protected prototype_ `TSharedPtr<FARSupportInterface , ESPMode::ThreadSafe> GetARSystem() const;`
- L87 _protected prototype_ `void UpdateSessionPayload(FARSessionPayload& Payload) const;`
- L90 _protected member_ `FTransform LocalToTrackingTransform;` — `UPROPERTY()`
- L93 _protected member_ `FTransform LocalToAlignedTrackingTransform;` — `UPROPERTY()`
- L96 _protected member_ `EARTrackingState TrackingState;` — `UPROPERTY()`
- L99 _protected member_ `TUniquePtr<IARRef> NativeResource;` — A pointer to the native resource in the native AR system
- L103 _protected member_ `TObjectPtr<UMRMeshComponent> UnderlyingMesh;` — `UPROPERTY(Transient)` — For AR systems that support arbitrary mesh geometry associated with a tracked point
- L107 _protected member_ `EARObjectClassification ObjectClassification;` — `UPROPERTY()` — What the scene understanding system thinks this object is
- L111 _protected member_ `EARSpatialMeshUsageFlags SpatialMeshUsageFlags;` — `UPROPERTY()` — How the scene understanding system thinks this mesh should be displayed
- L114 _private member_ `TWeakPtr<FARSupportInterface , ESPMode::ThreadSafe> ARSystem;`
- L118 _private member_ `int32 LastUpdateFrameNumber;` — `UPROPERTY()` — The frame number this tracked geometry was last updated on
- L121 _private member_ `double LastUpdateTimestamp;` — The time reported by the AR system that this object was last updated
- L125 _private member_ `FName DebugName;` — `UPROPERTY()` — A unique name that can be used to identify the anchor for debug purposes
- L128 _private member_ `FString AnchorName;` — A descriptive name for the anchor

#### class `UARPlaneGeometry`  
`class UARPlaneGeometry : public UARTrackedGeometry`  
_L132-179_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UARTrackedGeometry`
- L138 _public prototype_ `void UpdateTrackedGeometry(const TSharedRef<FARSupportInterface , ESPMode::ThreadSafe>& InTrackingSystem, uint32 FrameNumber, double Timestamp, const FTransform& InLocalToTrackingTransform, const FTransform& InAlignmentTransform, const FVector InCenter, const FVector InExtent );`
- L142 _public prototype_ `virtual void DebugDraw( UWorld* World, const FLinearColor& OutlineColor, float OutlineThickness, float PersistForSeconds = 0.0f) const override;`
- L144 _public prototype_ `void GetNetworkPayload(FARPlaneUpdatePayload& Payload);`
- L148 _public function_ `FVector GetCenter() const` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Plane Geometry")`
- L151 _public function_ `FVector GetExtent() const` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Plane Geometry")`
- L154 _public function_ `TArray<FVector> GetBoundaryPolygonInLocalSpace() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Plane Geometry")`
- L157 _public function_ `UARPlaneGeometry* GetSubsumedBy() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Plane Geometry")`
- L160 _public function_ `EARPlaneOrientation GetOrientation() const` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Plane Geometry")`
- L161 _public function_ `void SetOrientation(EARPlaneOrientation InOrientation)`
- L165 _private member_ `EARPlaneOrientation Orientation;` — `UPROPERTY()`
- L168 _private member_ `FVector Center;` — `UPROPERTY()`
- L171 _private member_ `FVector Extent;` — `UPROPERTY()`
- L174 _private member_ `TArray<FVector> BoundaryPolygon;` — `UPROPERTY()`
- L178 _private member_ `TObjectPtr<UARPlaneGeometry> SubsumedBy = nullptr;` — `UPROPERTY()` — Used by ARCore Only

#### class `UARTrackedPoint`  
`class UARTrackedPoint : public UARTrackedGeometry`  
_L182-192_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UARTrackedGeometry`
- L187 _public prototype_ `virtual void DebugDraw(UWorld* World, const FLinearColor& OutlineColor, float OutlineThickness, float PersistForSeconds = 0.0f) const override;`
- L189 _public prototype_ `void GetNetworkPayload(FARPointUpdatePayload& Payload);`
- L191 _public prototype_ `void UpdateTrackedGeometry(const TSharedRef<FARSupportInterface , ESPMode::ThreadSafe>& InTrackingSystem, uint32 FrameNumber, double Timestamp, const FTransform& InLocalToTrackingTransform, const FTransform& InAlignmentTransform);`

#### class `UARTrackedImage`  
`class UARTrackedImage : public UARTrackedGeometry`  
_L195-230_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UARTrackedGeometry`
- L200 _public prototype_ `virtual void DebugDraw(UWorld* World, const FLinearColor& OutlineColor, float OutlineThickness, float PersistForSeconds = 0.0f) const override;`
- L202 _public prototype_ `void GetNetworkPayload(FARImageUpdatePayload& Payload);`
- L204 _public prototype_ `void UpdateTrackedGeometry(const TSharedRef<FARSupportInterface, ESPMode::ThreadSafe>& InTrackingSystem, uint32 FrameNumber, double Timestamp, const FTransform& InLocalToTrackingTransform, const FTransform& InAlignmentTransform, FVector2D InEstimatedSize, UARCandidateImage* InDetectedImage);`
- L208 _public function_ `UARCandidateImage* GetDetectedImage() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Image Detection")` — @see DetectedImage
- L220 _public prototype_ `FVector2D GetEstimateSize();` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Image Detection")` — Get the estimate size of the detected image, where X is the estimated width, and Y is the estimated height. Note that ARCore can return a valid estimate size of the detected image when the tracking state of the UARTrackedImage is tracking. The size should reflect the actual size of the image target, which could be different than the input physical size of the candidate image. ARKit will return the physical size of the ARCandidate image.
- L225 _protected member_ `TObjectPtr<UARCandidateImage> DetectedImage;` — `UPROPERTY()` — The candidate image that was detected in the scene
- L229 _protected member_ `FVector2D EstimatedSize;` — `UPROPERTY()` — The estimated image size that was detected in the scene

#### class `UARTrackedQRCode`  
`class UARTrackedQRCode : public UARTrackedImage`  
_L233-250_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UARTrackedImage`
- L239 _public prototype_ `void GetNetworkPayload(FARQRCodeUpdatePayload& Payload);`
- L241 _public prototype_ `void UpdateTrackedGeometry(const TSharedRef<FARSupportInterface, ESPMode::ThreadSafe>& InTrackingSystem, uint32 FrameNumber, double Timestamp, const FTransform& InLocalToTrackingTransform, const FTransform& InAlignmentTransform, FVector2D InEstimatedSize, const FString& CodeData, int32 InVersion);`
- L245 _public member_ `FString QRCode;` — `UPROPERTY(BlueprintReadOnly, Category="QR Code")` — The encoded information in the qr code
- L249 _public member_ `int32 Version;` — `UPROPERTY(BlueprintReadOnly, Category="QR Code")` — The version of the qr code

#### enum `EARFaceTrackingDirection`  
`enum class EARFaceTrackingDirection : uint8`  
_L253-259_
- reflection: `UENUM(BlueprintType, Category="AR AugmentedReality", meta=(Experimental))`
- L256 _public enumerator_ `FaceRelative` — Blend shapes are tracked as if looking out of the face, e.g. right eye is the mesh's right eye and left side of screen if facing you
- L258 _public enumerator_ `FaceMirrored` — Blend shapes are tracked as if looking at the face, e.g. right eye is the mesh's left eye and right side of screen if facing you (like a mirror)

#### enum `EARFaceBlendShape`  
`enum class EARFaceBlendShape : uint8`  
_L262-335_
- reflection: `UENUM(BlueprintType, Category="AR AugmentedReality", meta=(Experimental))`
- L265 _public enumerator_ `EyeBlinkLeft` — Left eye blend shapes
- L266 _public enumerator_ `EyeLookDownLeft`
- L267 _public enumerator_ `EyeLookInLeft`
- L268 _public enumerator_ `EyeLookOutLeft`
- L269 _public enumerator_ `EyeLookUpLeft`
- L270 _public enumerator_ `EyeSquintLeft`
- L271 _public enumerator_ `EyeWideLeft`
- L273 _public enumerator_ `EyeBlinkRight` — Right eye blend shapes
- L274 _public enumerator_ `EyeLookDownRight`
- L275 _public enumerator_ `EyeLookInRight`
- L276 _public enumerator_ `EyeLookOutRight`
- L277 _public enumerator_ `EyeLookUpRight`
- L278 _public enumerator_ `EyeSquintRight`
- L279 _public enumerator_ `EyeWideRight`
- L281 _public enumerator_ `JawForward` — Jaw blend shapes
- L282 _public enumerator_ `JawLeft`
- L283 _public enumerator_ `JawRight`
- L284 _public enumerator_ `JawOpen`
- L286 _public enumerator_ `MouthClose` — Mouth blend shapes
- L287 _public enumerator_ `MouthFunnel`
- L288 _public enumerator_ `MouthPucker`
- L289 _public enumerator_ `MouthLeft`
- L290 _public enumerator_ `MouthRight`
- L291 _public enumerator_ `MouthSmileLeft`
- L292 _public enumerator_ `MouthSmileRight`
- L293 _public enumerator_ `MouthFrownLeft`
- L294 _public enumerator_ `MouthFrownRight`
- L295 _public enumerator_ `MouthDimpleLeft`
- L296 _public enumerator_ `MouthDimpleRight`
- L297 _public enumerator_ `MouthStretchLeft`
- L298 _public enumerator_ `MouthStretchRight`
- L299 _public enumerator_ `MouthRollLower`
- L300 _public enumerator_ `MouthRollUpper`
- L301 _public enumerator_ `MouthShrugLower`
- L302 _public enumerator_ `MouthShrugUpper`
- L303 _public enumerator_ `MouthPressLeft`
- L304 _public enumerator_ `MouthPressRight`
- L305 _public enumerator_ `MouthLowerDownLeft`
- L306 _public enumerator_ `MouthLowerDownRight`
- L307 _public enumerator_ `MouthUpperUpLeft`
- L308 _public enumerator_ `MouthUpperUpRight`
- L310 _public enumerator_ `BrowDownLeft` — Brow blend shapes
- L311 _public enumerator_ `BrowDownRight`
- L312 _public enumerator_ `BrowInnerUp`
- L313 _public enumerator_ `BrowOuterUpLeft`
- L314 _public enumerator_ `BrowOuterUpRight`
- L316 _public enumerator_ `CheekPuff` — Cheek blend shapes
- L317 _public enumerator_ `CheekSquintLeft`
- L318 _public enumerator_ `CheekSquintRight`
- L320 _public enumerator_ `NoseSneerLeft` — Nose blend shapes
- L321 _public enumerator_ `NoseSneerRight`
- L322 _public enumerator_ `TongueOut`
- L324 _public enumerator_ `HeadYaw` — Treat the head rotation as curves for LiveLink support
- L325 _public enumerator_ `HeadPitch`
- L326 _public enumerator_ `HeadRoll`
- L328 _public enumerator_ `LeftEyeYaw` — Treat eye rotation as curves for LiveLink support
- L329 _public enumerator_ `LeftEyePitch`
- L330 _public enumerator_ `LeftEyeRoll`
- L331 _public enumerator_ `RightEyeYaw`
- L332 _public enumerator_ `RightEyePitch`
- L333 _public enumerator_ `RightEyeRoll`
- L334 _public enumerator_ `MAX`

#### enum `EAREye`  
`enum class EAREye : uint8`  
_L338-342_
- reflection: `UENUM(BlueprintType, Category="AR AugmentedReality", meta=(Experimental))`
- L340 _public enumerator_ `LeftEye`
- L341 _public enumerator_ `RightEye`

#### class `UARFaceGeometry`  
`class UARFaceGeometry : public UARTrackedGeometry`  
_L347-403_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UARTrackedGeometry`
- L352 _public prototype_ `void UpdateFaceGeometry(const TSharedRef<FARSupportInterface , ESPMode::ThreadSafe>& InTrackingSystem, uint32 FrameNumber, double Timestamp, const FTransform& InTransform, const FTransform& InAlignmentTransform, FARBlendShapeMap& InBlendShapes, TArray<FVector>& InVertices, const TArray<int32>& Indices, TArray<FVector2D>& InUVs, const FTransform& InLeftEyeTransform, const FTransform& InRightEyeTransform, const FVector& InLookAtTarget);`
- L354 _public prototype_ `virtual void DebugDraw( UWorld* World, const FLinearColor& OutlineColor, float OutlineThickness, float PersistForSeconds = 0.0f) const override;`
- L356 _public prototype_ `void GetNetworkPayload(FARFaceUpdatePayload& Payload);`
- L360 _public prototype_ `float GetBlendShapeValue(EARFaceBlendShape BlendShape) const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Face Geometry")`
- L363 _public prototype_ `const TMap<EARFaceBlendShape, float> GetBlendShapes() const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Face Geometry")`
- L365 _public function_ `const FARBlendShapeMap& GetBlendShapesRef() const`
- L367 _public function_ `const TArray<FVector>& GetVertexBuffer() const`
- L368 _public function_ `const TArray<int32>& GetIndexBuffer() const`
- L369 _public function_ `const TArray<FVector2D>& GetUVs() const`
- L372 _public prototype_ `const FTransform& GetLocalSpaceEyeTransform(EAREye Eye) const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Face Geometry")`
- L375 _public prototype_ `FTransform GetWorldSpaceEyeTransform(EAREye Eye) const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Face Geometry")`
- L379 _public member_ `FVector LookAtTarget;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality|Face Geometry")` — The target the eyes are looking at
- L384 _public member_ `bool bIsTracked;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality|Face Geometry", meta=(Deprecated, DeprecationMessage = "This property is now deprecated, please use GetTrackingState() and check for EARTrackingState::Tracking or IsTracked() instead."))` — Whether the face is currently being tracked by the AR system
- L388 _private member_ `TMap<EARFaceBlendShape, float> BlendShapes;` — `UPROPERTY()`
- L391 _private member_ `TArray<FVector> VertexBuffer;` — Holds the face data for one or more face components that want access
- L392 _private member_ `TArray<int32> IndexBuffer;`
- L394 _private member_ `TArray<FVector2D> UVs;` — @todo JoeG - route the uvs in
- L398 _private member_ `FTransform LeftEyeTransform;` — `UPROPERTY()` — The transform for the left eye
- L402 _private member_ `FTransform RightEyeTransform;` — `UPROPERTY()` — The transform for the right eye

#### class `UAREnvironmentCaptureProbe`  
`class UAREnvironmentCaptureProbe : public UARTrackedGeometry`  
_L407-437_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UARTrackedGeometry`
- desc: A tracked environment texture probe that gives you a cube map for reflections
- L413 _public prototype_ `UAREnvironmentCaptureProbe();`
- L416 _public prototype_ `virtual void DebugDraw(UWorld* World, const FLinearColor& OutlineColor, float OutlineThickness, float PersistForSeconds = 0.0f) const override;` — Draw a box visulizing the bounds of the probe
- L418 _public prototype_ `void GetNetworkPayload(FAREnvironmentProbeUpdatePayload& Payload);`
- L420 _public prototype_ `void UpdateEnvironmentCapture(const TSharedRef<FARSupportInterface , ESPMode::ThreadSafe>& InTrackingSystem, uint32 FrameNumber, double Timestamp, const FTransform& InLocalToTrackingTransform, const FTransform& InAlignmentTransform, FVector InExtent);`
- L424 _public prototype_ `FVector GetExtent() const;` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Environment Capture Probe")` — @see Extent
- L427 _public prototype_ `UAREnvironmentCaptureProbeTexture* GetEnvironmentCaptureTexture();` — `UFUNCTION(BlueprintPure, Category="AR AugmentedReality|Environment Capture Probe")` — @see EnvironmentCaptureTexture
- L432 _protected member_ `FVector Extent;` — `UPROPERTY()` — The size of area this probe covers
- L436 _protected member_ `TObjectPtr<UAREnvironmentCaptureProbeTexture> EnvironmentCaptureTexture;` — `UPROPERTY()` — The cube map of the reflected environment

#### class `UARTrackedObject`  
`class UARTrackedObject : public UARTrackedGeometry`  
_L440-459_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UARTrackedGeometry`
- L445 _public prototype_ `virtual void DebugDraw(UWorld* World, const FLinearColor& OutlineColor, float OutlineThickness, float PersistForSeconds = 0.0f) const override;`
- L447 _public prototype_ `void GetNetworkPayload(FARObjectUpdatePayload& Payload);`
- L449 _public prototype_ `void UpdateTrackedGeometry(const TSharedRef<FARSupportInterface , ESPMode::ThreadSafe>& InTrackingSystem, uint32 FrameNumber, double Timestamp, const FTransform& InLocalToTrackingTransform, const FTransform& InAlignmentTransform, UARCandidateObject* InDetectedObject);`
- L453 _public function_ `UARCandidateObject* GetDetectedObject() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Object Detection")` — @see DetectedObject
- L458 _private member_ `TObjectPtr<UARCandidateObject> DetectedObject;` — `UPROPERTY()` — The candidate object that was detected in the scene

#### class `UARTrackedPose`  
`class UARTrackedPose : public UARTrackedGeometry`  
_L462-480_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UARTrackedGeometry`
- L467 _public prototype_ `virtual void DebugDraw(UWorld* World, const FLinearColor& OutlineColor, float OutlineThickness, float PersistForSeconds = 0.0f) const override;`
- L469 _public prototype_ `void GetNetworkPayload(FARPoseUpdatePayload& Payload);`
- L471 _public prototype_ `void UpdateTrackedPose(const TSharedRef<FARSupportInterface , ESPMode::ThreadSafe>& InTrackingSystem, uint32 FrameNumber, double Timestamp, const FTransform& InLocalToTrackingTransform, const FTransform& InAlignmentTransform, const FARPose3D& InTrackedPose);`
- L474 _public function_ `const FARPose3D& GetTrackedPoseData() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Pose Tracking")`
- L479 _private member_ `FARPose3D TrackedPose;` — `UPROPERTY()` — The detailed info of the tracked pose

#### class `UARMeshGeometry`  
`class UARMeshGeometry : public UARTrackedGeometry`  
_L483-501_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UARTrackedGeometry`
- L489 _public prototype_ `void GetNetworkPayload(FARMeshUpdatePayload& Payload);`
- L500 _public function_ `virtual bool GetObjectClassificationAtLocation(const FVector& InWorldLocation, EARObjectClassification& OutClassification, FVector& OutClassificationLocation, float MaxLocationDiff = 10.f)` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Classification")` — Try to determine the classification of the object at a world space location @InWorldLocation: the world location where the classification is needed @OutClassification: the classification result @OutClassificationLocation: the world location at where the classification is calculated @MaxLocationDiff: the max distance between the specified world location and the classification location @return: whether a valid classification result is calculated

#### class `UARGeoAnchor`  
`class UARGeoAnchor : public UARTrackedGeometry`  
_L505-532_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UARTrackedGeometry`
- L510 _public prototype_ `void UpdateGeoAnchor(const TSharedRef<FARSupportInterface, ESPMode::ThreadSafe>& InTrackingSystem, uint32 FrameNumber, double Timestamp, const FTransform& InLocalToTrackingTransform, const FTransform& InAlignmentTransform, float InLongitude, float InLatitude, float InAltitudeMeters, EARAltitudeSource InAltitudeSource);`
- L513 _public prototype_ `void GetNetworkPayload(FARGeoAnchorUpdatePayload& Payload);`
- L516 _public function_ `float GetLongitude() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Geo Tracking")`
- L519 _public function_ `float GetLatitude() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Geo Tracking")`
- L522 _public function_ `float GetAltitudeMeters() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Geo Tracking")`
- L525 _public function_ `EARAltitudeSource GetAltitudeSource() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Geo Tracking")`
- L528 _private member_ `float Longitude = 0.f;`
- L529 _private member_ `float Latitude = 0.f;`
- L530 _private member_ `float AltitudeMeters = 0.f;`
- L531 _private member_ `EARAltitudeSource AltitudeSource = EARAltitudeSource::Unknown;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUGMENTEDREALITY_API`
- L344 _typedef_ `typedef TMap<EARFaceBlendShape, float> FARBlendShapeMap;`

### `Source/Runtime/AugmentedReality/Public/ARTrackableNotifyComponent.h` (Public)


#### class `UARTrackableNotifyComponent`  
`class UARTrackableNotifyComponent : public UActorComponent`  
_L22-149_
- reflection: `UCLASS(MinimalAPI, meta=(BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: Component used to listen to ar trackable object changes
- L31 _public member_ `FTrackableDelegate OnAddTrackedGeometry;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any new trackable ar item is added
- L35 _public member_ `FTrackableDelegate OnUpdateTrackedGeometry;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any trackable ar item is updated
- L39 _public member_ `FTrackableDelegate OnRemoveTrackedGeometry;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any trackable ar item is removed from the scene
- L44 _public member_ `FTrackablePlaneDelegate OnAddTrackedPlane;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any new ar plane item is added
- L48 _public member_ `FTrackablePlaneDelegate OnUpdateTrackedPlane;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any ar plane item is updated
- L52 _public member_ `FTrackablePlaneDelegate OnRemoveTrackedPlane;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any ar plane item is removed from the scene
- L57 _public member_ `FTrackablePointDelegate OnAddTrackedPoint;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any new ar Point item is added
- L61 _public member_ `FTrackablePointDelegate OnUpdateTrackedPoint;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any ar Point item is updated
- L65 _public member_ `FTrackablePointDelegate OnRemoveTrackedPoint;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any ar Point item is removed from the scene
- L70 _public member_ `FTrackableImageDelegate OnAddTrackedImage;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any new ar Image item is added
- L74 _public member_ `FTrackableImageDelegate OnUpdateTrackedImage;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any ar Image item is updated
- L78 _public member_ `FTrackableImageDelegate OnRemoveTrackedImage;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any ar Image item is removed from the scene
- L83 _public member_ `FTrackableFaceDelegate OnAddTrackedFace;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any new ar Face item is added
- L87 _public member_ `FTrackableFaceDelegate OnUpdateTrackedFace;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any ar Face item is updated
- L91 _public member_ `FTrackableFaceDelegate OnRemoveTrackedFace;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any ar Face item is removed from the scene
- L96 _public member_ `FTrackableEnvProbeDelegate OnAddTrackedEnvProbe;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any new ar environment capture probe item is added
- L100 _public member_ `FTrackableEnvProbeDelegate OnUpdateTrackedEnvProbe;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any ar environment capture probe item is updated
- L104 _public member_ `FTrackableEnvProbeDelegate OnRemoveTrackedEnvProbe;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any ar environment capture probe item is removed from the scene
- L109 _public member_ `FTrackableObjectDelegate OnAddTrackedObject;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any new ar detected object item is added
- L113 _public member_ `FTrackableObjectDelegate OnUpdateTrackedObject;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any ar detected object item is updated
- L117 _public member_ `FTrackableObjectDelegate OnRemoveTrackedObject;` — `UPROPERTY(BlueprintAssignable, Category="Event")` — Event that happens when any ar detected object item is removed from the scene
- L120 _private prototype_ `virtual void OnRegister() override;`
- L121 _private prototype_ `virtual void OnUnregister() override;`
- L129 _private prototype_ `template<typename OBJ_TYPE, typename DELEGATE_TYPE> bool ConditionalDispatchEvent(UARTrackedGeometry* Tracked, DELEGATE_TYPE& Delegate);` — Triggers the delegate type if the object is the desired class #return true if the class matched, false otherwise
- L136 _private prototype_ `void OnTrackableAdded(UARTrackedGeometry* Added);` — Routes the notification to the proper delegate set @param Added the newly added ar trackable
- L142 _private prototype_ `void OnTrackableUpdated(UARTrackedGeometry* Updated);` — Routes the notification to the proper delegate set @param Updated the updated ar trackable
- L148 _private prototype_ `void OnTrackableRemoved(UARTrackedGeometry* Removed);` — Routes the notification to the proper delegate set @param Removed the removed ar trackable

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUGMENTEDREALITY_API`
- L12 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrackableDelegate, UARTrackedGeometry*, TrackedGeometry);`
- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrackableDelegate, UARTrackedGeometry*, TrackedGeometry);`
- L13 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrackablePlaneDelegate, UARPlaneGeometry*, TrackedPlane);`
- L13 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrackablePlaneDelegate, UARPlaneGeometry*, TrackedPlane);`
- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrackablePointDelegate, UARTrackedPoint*, TrackedPoint);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrackablePointDelegate, UARTrackedPoint*, TrackedPoint);`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrackableImageDelegate, UARTrackedImage*, TrackedImage);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrackableImageDelegate, UARTrackedImage*, TrackedImage);`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrackableFaceDelegate, UARFaceGeometry*, TrackedFace);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrackableFaceDelegate, UARFaceGeometry*, TrackedFace);`
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrackableEnvProbeDelegate, UAREnvironmentCaptureProbe*, TrackedEnvProbe);`
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrackableEnvProbeDelegate, UAREnvironmentCaptureProbe*, TrackedEnvProbe);`
- L18 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrackableObjectDelegate, UARTrackedObject*, TrackedObject);`
- L18 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrackableObjectDelegate, UARTrackedObject*, TrackedObject);`

### `Source/Runtime/AugmentedReality/Public/ARTypes.h` (Public)


#### enum `EARTrackingState`  
`enum class EARTrackingState : uint8`  
_L29-42_
- reflection: `UENUM(BlueprintType, Category="AR AugmentedReality", meta=(Experimental))`
- L32 _public enumerator_ `Unknown` — Unknown tracking state
- L35 _public enumerator_ `Tracking` — Currently tracking.
- L38 _public enumerator_ `NotTracking` — Currently not tracking, but may resume tracking later.
- L41 _public enumerator_ `StoppedTracking` — Stopped tracking forever.

#### enum `EARCaptureType`  
`enum class EARCaptureType : uint8`  
_L46-62_
- reflection: `UENUM(BlueprintType, Category = "AR AugmentedReality", meta = (Experimental))`
- L49 _public enumerator_ `Camera` — Camera Capture
- L52 _public enumerator_ `QRCode` — QR Code Capture.
- L55 _public enumerator_ `SpatialMapping` — Spatial mapping so the app can selectively turn off discovering surfaces
- L58 _public enumerator_ `SceneUnderstanding` — Capture detailed information about the scene with all surfaces like walls, floors and so on
- L61 _public enumerator_ `HandMesh` — Capture a mesh around the player's hands

#### enum `EARLineTraceChannels`  
`enum class EARLineTraceChannels : uint8`  
_L69-84_
- reflection: `UENUM(BlueprintType, Category="AR AugmentedReality|Trace Result", meta=(Bitflags))`
- desc: Channels that let users select which kind of tracked geometry to trace against.
- L71 _public enumerator_ `None = 0`
- L74 _public enumerator_ `FeaturePoint = 1` — Trace against points that the AR system considers significant .
- L77 _public enumerator_ `GroundPlane = 2` — Trace against estimated plane that does not have an associated tracked geometry.
- L80 _public enumerator_ `PlaneUsingExtent = 4` — Trace against any plane tracked geometries using Center and Extent.
- L83 _public enumerator_ `PlaneUsingBoundaryPolygon = 8` — Trace against any plane tracked geometries using the boundary polygon.

#### enum `EARTrackingQuality`  
`enum class EARTrackingQuality : uint8`  
_L90-100_
- reflection: `UENUM(BlueprintType, Category="AR AugmentedReality", meta=(Experimental))`
- L93 _public enumerator_ `NotTracking` — The tracking quality is not available.
- L96 _public enumerator_ `OrientationOnly` — The tracking quality is limited, relying only on the device's motion.
- L99 _public enumerator_ `OrientationAndPosition` — The tracking quality is good.

#### enum `EARTrackingQualityReason`  
`enum class EARTrackingQualityReason : uint8`  
_L103-125_
- reflection: `UENUM(BlueprintType, Category="AR AugmentedReality", meta=(Experimental))`
- L106 _public enumerator_ `None` — Current Tracking is not limited
- L109 _public enumerator_ `Initializing` — The AR session has not yet gathered enough camera or motion data to provide tracking information.
- L112 _public enumerator_ `Relocalizing` — The AR session is attempting to resume after an interruption.
- L115 _public enumerator_ `ExcessiveMotion` — The device is moving too fast for accurate image-based position tracking.
- L118 _public enumerator_ `InsufficientFeatures` — The scene visible to the camera does not contain enough distinguishable features for image-based position tracking.
- L121 _public enumerator_ `InsufficientLight` — Tracking lost due to poor lighting conditions. Please move to a more brightly lit area
- L124 _public enumerator_ `BadState` — Tracking lost due to bad internal state. Please try restarting the AR experience.

#### enum `EARSessionStatus`  
`enum class EARSessionStatus : uint8`  
_L131-147_
- reflection: `UENUM(BlueprintType, meta=(ScriptName="ARSessionStatusType"))`
- desc: Describes the current status of the AR session.
- L134 _public enumerator_ `NotStarted` — Unreal AR session has not started yet.
- L136 _public enumerator_ `Running` — Unreal AR session is running.
- L138 _public enumerator_ `NotSupported` — Unreal AR session failed to start due to the AR subsystem not being supported by the device.
- L140 _public enumerator_ `FatalError` — The AR session encountered fatal error; the developer should call `StartARSession()` to re-start the AR subsystem.
- L142 _public enumerator_ `PermissionNotGranted` — AR session failed to start because it lacks the necessary permission (likely access to the camera or the gyroscope).
- L144 _public enumerator_ `UnsupportedConfiguration` — AR session failed to start because the configuration isn't supported.
- L146 _public enumerator_ `Other` — Session isn't running due to unknown reason; @see FARSessionStatus::AdditionalInfo for more information

#### enum `EARWorldMappingState`  
`enum class EARWorldMappingState : uint8`  
_L151-161_
- reflection: `UENUM(BlueprintType, Category="AR AugmentedReality", meta=(Experimental))`
- desc: Gives feedback as to whether the AR data can be saved and relocalized or not
- L154 _public enumerator_ `NotAvailable` — World mapping is not available
- L156 _public enumerator_ `StillMappingNotRelocalizable` — World mapping is still in progress but without enough data for relocalization
- L158 _public enumerator_ `StillMappingRelocalizable` — World mapping is still in progress but there is enough data captured for relocalization
- L160 _public enumerator_ `Mapped` — World mapping has mapped the area and is fully relocalizable

#### enum `EARPlaneOrientation`  
`enum class EARPlaneOrientation : uint8`  
_L165-171_
- reflection: `UENUM(BlueprintType)`
- desc: Describes the tracked plane orientation
- L167 _public enumerator_ `Horizontal`
- L168 _public enumerator_ `Vertical`
- L170 _public enumerator_ `Diagonal` — For AR systems that can match planes to slopes

#### enum `EARObjectClassification`  
`enum class EARObjectClassification : uint8`  
_L175-206_
- reflection: `UENUM(BlueprintType)`
- desc: Indicates what type of object the scene understanding system thinks it is
- L178 _public enumerator_ `NotApplicable` — Not applicable to scene understanding
- L180 _public enumerator_ `Unknown` — Scene understanding doesn't know what this is
- L182 _public enumerator_ `Wall` — A vertical plane that is a wall
- L184 _public enumerator_ `Ceiling` — A horizontal plane that is the ceiling
- L186 _public enumerator_ `Floor` — A horizontal plane that is the floor
- L188 _public enumerator_ `Table` — A horizontal plane that is a table
- L190 _public enumerator_ `Seat` — A horizontal plane that is a seat
- L192 _public enumerator_ `Face` — A human face
- L194 _public enumerator_ `Image` — A recognized image in the scene
- L196 _public enumerator_ `World` — A chunk of mesh that does not map to a specific object type but is seen by the AR system
- L198 _public enumerator_ `SceneObject` — A closed mesh that was identified in the scene
- L200 _public enumerator_ `HandMesh` — A user's hand
- L202 _public enumerator_ `Door` — A door
- L204 _public enumerator_ `Window` — A window

#### enum `EARSpatialMeshUsageFlags`  
`enum class EARSpatialMeshUsageFlags : uint8`  
_L210-218_
- reflection: `UENUM(BlueprintType)`
- desc: Indicates how the spatial mesh should be visualized
- L213 _public enumerator_ `NotApplicable = 0` — Not applicable to scene understanding.
- L215 _public enumerator_ `Visible = 1 << 0` — This mesh should have a visible material applied to it.
- L217 _public enumerator_ `Collision = 1 << 1` — This mesh should be used when placing objects on real world surfaces.  This must be set to use physics with this mesh.

#### enum `EARJointTransformSpace`  
`enum class EARJointTransformSpace : uint8`  
_L222-235_
- reflection: `UENUM(BlueprintType)`
- desc: Describes the potential spaces in which the join transform can be defined with AR pose tracking
- L229 _public enumerator_ `Model` — Joint transform is relative to the origin of the model space which is usually attached to a particular joint such as the hip
- L234 _public enumerator_ `ParentJoint` — Joint transform is relative to its parent

#### enum `EARAltitudeSource`  
`enum class EARAltitudeSource : uint8`  
_L238-251_
- reflection: `UENUM(BlueprintType)`
- L241 _public enumerator_ `Precise` — The framework sets the altitude using a high-resolution digital-elevation model.
- L244 _public enumerator_ `Coarse` — The framework sets the altitude using a coarse digital-elevation model.
- L247 _public enumerator_ `UserDefined` — The app defines the alitude.
- L250 _public enumerator_ `Unknown` — Altitude is not yet set.

#### struct `FARSessionStatus`  
`struct FARSessionStatus`  
_L255-279_
- reflection: `USTRUCT(BlueprintType)`
- desc: The current state of the AR subsystem including an optional explanation string.
- L261 _public function_ `FARSessionStatus() :FARSessionStatus(EARSessionStatus::Other)`
- L265 _public function_ `FARSessionStatus(EARSessionStatus InStatus, FString InExtraInfo = FString()) : AdditionalInfo(InExtraInfo) , Status(InStatus)`
- L274 _public member_ `FString AdditionalInfo;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality|Session")` — Optional information about the current status of the system.
- L278 _public member_ `EARSessionStatus Status;` — `UPROPERTY(BlueprintReadOnly, Category = "AR AugmentedReality|Session")` — The current status of the AR subsystem.

#### class `UARTypesDummyClass`  
`class UARTypesDummyClass : public UObject`  
_L285-288_
- reflection: `UCLASS()`
- inherits: `UObject`

#### class `IARRef`  
`class IARRef`  
_L291-299_
- desc: A reference to a system-level AR object
- L294 _public prototype_ `virtual void AddRef() = 0;`
- L295 _public prototype_ `virtual void RemoveRef() = 0;`
- L297 _public prototype_ `virtual ~IARRef() = default;`

#### enum `EARCandidateImageOrientation`  
`enum class EARCandidateImageOrientation : uint8`  
_L303-307_
- reflection: `UENUM(BlueprintType)`
- desc: Tells the image detection code how to assume the image is oriented
- L305 _public enumerator_ `Landscape`
- L306 _public enumerator_ `Portrait`

#### class `UARCandidateImage`  
`class UARCandidateImage : public UDataAsset`  
_L311-375_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- desc: An asset that points to an image to be detected in a scene and provides the size of the object in real life
- L318 _public function_ `static UARCandidateImage* CreateNewARCandidateImage(UTexture2D* InCandidateTexture, FString InFriendlyName, float InPhysicalWidth, float InPhysicalHeight, EARCandidateImageOrientation InOrientation)`
- L332 _public function_ `UTexture2D* GetCandidateTexture() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Image Detection")` — @see CandidateTexture
- L336 _public function_ `const FString& GetFriendlyName() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Image Detection")` — @see FriendlyName
- L340 _public function_ `float GetPhysicalWidth() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Image Detection")` — @see Width
- L344 _public function_ `float GetPhysicalHeight() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Image Detection")` — @see Height
- L348 _public function_ `EARCandidateImageOrientation GetOrientation() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Image Detection")` — @see Orientation
- L353 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Used to enforce physical sizes matching the aspect ratio of the images
- L358 _protected member_ `TObjectPtr<UTexture2D> CandidateTexture;` — `UPROPERTY(EditAnywhere, Category = "AR Candidate Image")` — The image to detect in scenes
- L362 _protected member_ `FString FriendlyName;` — `UPROPERTY(EditAnywhere, Category = "AR Candidate Image")` — The friendly name to report back when the image is detected in scenes
- L366 _protected member_ `float Width;` — `UPROPERTY(EditAnywhere, Category = "AR Candidate Image")` — The physical width in centimeters of the object that this candidate image represents
- L370 _protected member_ `float Height;` — `UPROPERTY(EditAnywhere, Category = "AR Candidate Image")` — The physical height in centimeters of the object that this candidate image represents. Ignored in ARCore
- L374 _protected member_ `EARCandidateImageOrientation Orientation;` — `UPROPERTY(EditAnywhere, Category = "AR Candidate Image")` — The orientation to treat the candidate image as. Ignored in ARCore

#### class `UARCandidateObject`  
`class UARCandidateObject : public UDataAsset`  
_L379-417_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- desc: An asset that points to an object to be detected in a scene
- L387 _public function_ `const TArray<uint8>& GetCandidateObjectData() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Object Detection")` — @see CandidateObjectData
- L390 _public function_ `void SetCandidateObjectData(const TArray<uint8>& InCandidateObject)` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Object Detection")`
- L394 _public function_ `const FString& GetFriendlyName() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Object Detection")` — @see FriendlyName
- L396 _public function_ `void SetFriendlyName(const FString& NewName)` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Object Detection")`
- L400 _public function_ `const FBox& GetBoundingBox() const` — `UFUNCTION(BlueprintPure, Category = "AR AugmentedReality|Object Detection")` — @see BoundingBox
- L403 _public function_ `void SetBoundingBox(const FBox& InBoundingBox)` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Object Detection")`
- L408 _private member_ `TArray<uint8> CandidateObjectData;` — `UPROPERTY(EditAnywhere, Category = "AR Candidate Object")` — The object to detect in scenes
- L412 _private member_ `FString FriendlyName;` — `UPROPERTY(EditAnywhere, Category = "AR Candidate Object")` — The friendly name to report back when the object is detected in scenes
- L416 _private member_ `FBox BoundingBox;` — `UPROPERTY(EditAnywhere, Category = "AR Candidate Image")` — The physical bounds in centimeters of the object that this candidate object represents

#### class `FARAsyncTask`  
`class FARAsyncTask`  
_L422-438_
- desc: Base class for async AR requests
- L425 _public prototype_ `virtual ~FARAsyncTask() = default;`
- L428 _public prototype_ `bool HadError() const;` — @return whether the task succeeded or not
- L430 _public prototype_ `FString GetErrorString() const;` — @return information about the error if there was one
- L432 _public prototype_ `bool IsDone() const;` — @return whether the task has completed or not
- L435 _protected member_ `FThreadSafeBool bIsDone;`
- L436 _protected member_ `FThreadSafeBool bHadError;`
- L437 _protected member_ `FString Error;`

#### class `FARSaveWorldAsyncTask`  
`class FARSaveWorldAsyncTask : public FARAsyncTask`  
_L441-450_
- inherits: `FARAsyncTask`
- desc: Async task that saves the world data into a buffer
- L446 _public prototype_ `TArray<uint8> GetSavedWorldData();` — @return the byte array that the world was saved into. Note uses MoveTemp() for efficiency so only valid once
- L449 _protected member_ `TArray<uint8> WorldData;`

#### class `FARGetCandidateObjectAsyncTask`  
`class FARGetCandidateObjectAsyncTask : public FARAsyncTask`  
_L453-459_
- inherits: `FARAsyncTask`
- desc: Async task that builds a candidate object used for detection from the ar session
- L458 _public prototype_ `virtual UARCandidateObject* GetCandidateObject() = 0;` — @return the candidate object that you can use for detection later

#### class `FARErrorGetCandidateObjectAsyncTask`  
`class FARErrorGetCandidateObjectAsyncTask : public FARGetCandidateObjectAsyncTask`  
_L461-472_
- inherits: `FARGetCandidateObjectAsyncTask`
- L465 _public function_ `FARErrorGetCandidateObjectAsyncTask(FString InError)`
- L471 _public function_ `virtual UARCandidateObject* GetCandidateObject() override`

#### class `FARErrorSaveWorldAsyncTask`  
`class FARErrorSaveWorldAsyncTask : public FARSaveWorldAsyncTask`  
_L474-484_
- inherits: `FARSaveWorldAsyncTask`
- L478 _public function_ `FARErrorSaveWorldAsyncTask(FString InError)`

#### struct `FARVideoFormat`  
`struct FARVideoFormat`  
_L488-532_
- reflection: `USTRUCT(BlueprintType)`
- desc: A specific AR video format
- L493 _public function_ `FARVideoFormat() : FPS(0) , Width(0) , Height(0)`
- L501 _public function_ `FARVideoFormat(int32 InFPS, int32 InWidth, int32 InHeight) : FPS(InFPS) , Width(InWidth) , Height(InHeight)`
- L509 _public function_ `bool operator==(const FARVideoFormat& Other) const`
- L516 _public member_ `int32 FPS;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AR AugmentedReality|Session")` — The desired or supported number of frames per second for this video format
- L520 _public member_ `int32 Width;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AR AugmentedReality|Session")` — The desired or supported width in pixels for this video format
- L524 _public member_ `int32 Height;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AR AugmentedReality|Session")` — The desired or supported height in pixels for this video format
- L526 _public function_ `bool IsValidFormat()`

#### struct `FARSkeletonDefinition`  
`struct FARSkeletonDefinition`  
_L536-552_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a hierarchy of a human pose skeleton tracked by the AR system
- L543 _public member_ `int32 NumJoints = 0;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality|Pose Tracking")` — How many joints this skeleton has
- L547 _public member_ `TArray<FName> JointNames;` — `UPROPERTY(BlueprintReadOnly, Category = "AR AugmentedReality|Pose Tracking")` — The name of each joint in this skeleton
- L551 _public member_ `TArray<int32> ParentIndices;` — `UPROPERTY(BlueprintReadOnly, Category = "AR AugmentedReality|Pose Tracking")` — The parent index of each joint in this skeleton

#### struct `FARPose2D`  
`struct FARPose2D`  
_L556-572_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a human pose tracked in the 2D space
- L563 _public member_ `FARSkeletonDefinition SkeletonDefinition;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality|Pose Tracking")` — The definition of this skeleton
- L567 _public member_ `TArray<FVector2D> JointLocations;` — `UPROPERTY(BlueprintReadOnly, Category = "AR AugmentedReality|Pose Tracking")` — The location of each joint in 2D normalized space
- L571 _public member_ `TArray<bool> IsJointTracked;` — `UPROPERTY(BlueprintReadOnly, Category = "AR AugmentedReality|Pose Tracking")` — Flags indicating if each joint is tracked

#### struct `FARPose3D`  
`struct FARPose3D`  
_L576-595_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a human pose tracked in the 3D space
- L583 _public member_ `FARSkeletonDefinition SkeletonDefinition;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality|Pose Tracking")` — The definition of this skeleton
- L587 _public member_ `TArray<FTransform> JointTransforms;` — `UPROPERTY(BlueprintReadOnly, Category = "AR AugmentedReality|Pose Tracking")` — The transform of each join in the model space
- L591 _public member_ `TArray<bool> IsJointTracked;` — `UPROPERTY(BlueprintReadOnly, Category = "AR AugmentedReality|Pose Tracking")` — Flags indicating if each joint is tracked
- L594 _public member_ `EARJointTransformSpace JointTransformSpace = EARJointTransformSpace::Model;` — `UPROPERTY(BlueprintReadOnly, Category = "AR AugmentedReality|Pose Tracking")`

#### struct `FARCameraIntrinsics`  
`struct FARCameraIntrinsics`  
_L600-616_
- reflection: `USTRUCT(BlueprintType)`
- desc: AR camera intrinsics
- L607 _public member_ `FIntPoint ImageResolution = FIntPoint::ZeroValue;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality|Camera")` — Camera image resolution in pixels
- L611 _public member_ `FVector2D FocalLength = FVector2D::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality|Camera")` — Camera focal length in pixels
- L615 _public member_ `FVector2D PrincipalPoint = FVector2D::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category="AR AugmentedReality|Camera")` — Camera principal point in pixels

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUGMENTEDREALITY_API`
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTrackableAdded, UARTrackedGeometry*);`
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTrackableAdded, UARTrackedGeometry*);`
- L19 _typedef_ `typedef FOnTrackableAdded::FDelegate FOnTrackableAddedDelegate;`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTrackableUpdated, UARTrackedGeometry*);`
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTrackableUpdated, UARTrackedGeometry*);`
- L22 _typedef_ `typedef FOnTrackableUpdated::FDelegate FOnTrackableUpdatedDelegate;`
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTrackableRemoved, UARTrackedGeometry*);`
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTrackableRemoved, UARTrackedGeometry*);`
- L25 _typedef_ `typedef FOnTrackableRemoved::FDelegate FOnTrackableRemovedDelegate;`
- L85 _prototype_ `ENUM_CLASS_FLAGS(EARLineTraceChannels);`
- L281 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnARTrackingStateChanged, EARTrackingState, NewTrackingState);`
- L281 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnARTrackingStateChanged, EARTrackingState, NewTrackingState);`
- L282 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnARTransformUpdated, const FTransform&, OldToNewTransform );`
- L282 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnARTransformUpdated, const FTransform&, OldToNewTransform );`
- L528 _function_ `friend FArchive& operator<<(FArchive& Ar, FARVideoFormat& Format)`
