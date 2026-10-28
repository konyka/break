# Runtime / CinematicCamera

- module root: `Source/Runtime/CinematicCamera`
- headers: 6; symbols: 233
- symbol kinds: class=6, enum=2, enumerator=8, function=12, member=101, prototype=95, struct=9
- PrivateDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, MovieScene, MovieSceneTracks, Slate, SlateCore

### `Source/Runtime/CinematicCamera/Public/CameraRig_Crane.h` (Public)


#### class `ACameraRig_Crane`  
`class ACameraRig_Crane : public AActor`  
_L18-92_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `AActor`
- desc: A simple rig for simulating crane-like camera movements.
- L25 _public prototype_ `ACameraRig_Crane(const FObjectInitializer& ObjectInitialier);` — ctor
- L27 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L28 _public prototype_ `virtual bool ShouldTickIfViewportsOnly() const override;`
- L32 _public member_ `float CranePitch;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Crane Controls", meta = (UIMin = "-360", UIMax = "360", Units = deg))` — Controls the pitch of the crane arm.
- L36 _public member_ `float CraneYaw;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Crane Controls", meta = (UIMin = "-360", UIMax = "360", Units = deg))` — Controls the yaw of the crane arm.
- L40 _public member_ `float CraneArmLength;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Crane Controls", meta = (ClampMin=0, Units = cm))` — Controls the length of the crane arm.
- L44 _public member_ `bool bLockMountPitch;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Crane Controls")` — Lock the mount pitch so that an attached camera is locked and pitched in the direction of the crane arm
- L48 _public member_ `bool bLockMountYaw;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Crane Controls")` — Lock the mount yaw so that an attached camera is locked and oriented in the direction of the crane arm
- L51 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L52 _public prototype_ `virtual void PostEditUndo() override;`
- L54 _public prototype_ `virtual class USceneComponent* GetDefaultAttachComponent() const override;`
- L58 _private prototype_ `void UpdatePreviewMeshes();`
- L60 _private prototype_ `void UpdateCraneComponents();`
- L64 _private member_ `TObjectPtr<USceneComponent> TransformComponent;` — `UPROPERTY(EditDefaultsOnly, Category = "Crane Components")` — Root component to give the whole actor a transform.
- L68 _private member_ `TObjectPtr<USceneComponent> CraneYawControl;` — `UPROPERTY(EditDefaultsOnly, Category = "Crane Components")` — Component to control Yaw.
- L72 _private member_ `TObjectPtr<USceneComponent> CranePitchControl;` — `UPROPERTY(EditDefaultsOnly, Category = "Crane Components")` — Component to control Pitch.
- L76 _private member_ `TObjectPtr<USceneComponent> CraneCameraMount;` — `UPROPERTY(EditDefaultsOnly, Category = "Crane Components")` — Component to define the attach point for cameras.
- L81 _private member_ `TObjectPtr<UStaticMeshComponent> PreviewMesh_CraneArm;` — `UPROPERTY(Transient)` — Preview meshes for visualization
- L84 _private member_ `TObjectPtr<UStaticMeshComponent> PreviewMesh_CraneBase;` — `UPROPERTY(Transient)`
- L87 _private member_ `TObjectPtr<UStaticMeshComponent> PreviewMesh_CraneMount;` — `UPROPERTY(Transient)`
- L90 _private member_ `TObjectPtr<UStaticMeshComponent> PreviewMesh_CraneCounterWeight;` — `UPROPERTY(Transient)`

### `Source/Runtime/CinematicCamera/Public/CameraRig_Rail.h` (Public)


#### class `ACameraRig_Rail`  
`class ACameraRig_Rail : public AActor`  
_L19-93_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `AActor`
- L25 _public prototype_ `ACameraRig_Rail(const FObjectInitializer& ObjectInitialier);` — ctor
- L27 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L28 _public prototype_ `virtual bool ShouldTickIfViewportsOnly() const override;`
- L32 _public member_ `float CurrentPositionOnRail;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Rail Controls", meta=(ClampMin="0.0", ClampMax = "1.0"))` — Defines current position of the mount point along the rail, in terms of normalized distance from the beginning of the rail.
- L36 _public member_ `bool bLockOrientationToRail;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Rail Controls")` — Determines whether the orientation of the mount should be in the direction of the rail.
- L41 _public member_ `bool bShowRailVisualization;` — `UPROPERTY(Transient, EditAnywhere, Category = "Rail Controls")` — Determines whether or not to show the rail mesh preview.
- L45 _public member_ `float PreviewMeshScale;` — `UPROPERTY(Transient, EditAnywhere, Category = "Rail Controls")` — Determines the scale of the rail mesh preview
- L48 _public prototype_ `virtual class USceneComponent* GetDefaultAttachComponent() const override;`
- L50 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L51 _public prototype_ `virtual void PostEditUndo() override;`
- L52 _public prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L57 _public function_ `USplineComponent* GetRailSplineComponent()` — `UFUNCTION(BlueprintPure, Category = "Rail Components")` — Returns the spline component that defines the rail path
- L61 _protected prototype_ `virtual void UpdateRailComponents();` — Makes sure all components are arranged properly. Call when something changes that might affect components.
- L63 _protected prototype_ `void UpdatePreviewMeshes();`
- L65 _protected prototype_ `USplineMeshComponent* CreateSplinePreviewSegment();`
- L69 _protected member_ `TObjectPtr<USceneComponent> TransformComponent;` — `UPROPERTY(EditDefaultsOnly, Category = "Rail Components")` — Root component to give the whole actor a transform.
- L73 _protected member_ `TObjectPtr<USplineComponent> RailSplineComponent;` — `UPROPERTY(EditDefaultsOnly, Category = "Rail Components")` — Spline component to define the rail path.
- L77 _protected member_ `TObjectPtr<USceneComponent> RailCameraMount;` — `UPROPERTY(EditDefaultsOnly, Category = "Rail Components")` — Component to define the attach point for cameras. Moves along the rail.
- L82 _protected member_ `TObjectPtr<USplineMeshComponent> PreviewMesh_Rail;` — `UPROPERTY(Transient)` — Preview meshes for visualization
- L85 _protected member_ `TArray<TObjectPtr<USplineMeshComponent>> PreviewRailMeshSegments;` — `UPROPERTY(Transient)`
- L88 _protected member_ `TObjectPtr<UStaticMesh> PreviewRailStaticMesh;` — `UPROPERTY(Transient)`
- L91 _protected member_ `TObjectPtr<UStaticMeshComponent> PreviewMesh_Mount;` — `UPROPERTY(Transient)`

### `Source/Runtime/CinematicCamera/Public/CineCameraActor.h` (Public)


#### struct `FCameraLookatTrackingSettings`  
`struct FCameraLookatTrackingSettings`  
_L23-67_
- reflection: `USTRUCT(BlueprintType)`
- desc: Settings to control the camera's lookat feature
- L27 _public function_ `FCameraLookatTrackingSettings() : bEnableLookAtTracking(false) , bDrawDebugLookAtTrackingPosition(false) , LookAtTrackingInterpSpeed(0.f) , LastLookatTrackingRotation(FRotator::ZeroRotator) , LastLookatTrackingRotationFrame(-1) , RelativeOffset(FVector::ZeroVector) , bAllowRoll(false)`
- L40 _public member_ `uint8 bEnableLookAtTracking : 1;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "LookAt")` — True to enable lookat tracking, false otherwise.
- L44 _public member_ `uint8 bDrawDebugLookAtTrackingPosition : 1;` — `UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "LookAt")` — True to draw a debug representation of the lookat location
- L48 _public member_ `float LookAtTrackingInterpSpeed;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "LookAt")` — Controls degree of smoothing. 0.f for no smoothing, higher numbers for faster/tighter tracking.
- L51 _public member_ `FRotator LastLookatTrackingRotation;` — Last known lookat tracking rotation (used during interpolation)
- L54 _public member_ `uint32 LastLookatTrackingRotationFrame;` — The frame we set the above on, so the camera component can restore it
- L58 _public member_ `TSoftObjectPtr<AActor> ActorToTrack;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "LookAt")` — If set, camera will track this actor's location
- L62 _public member_ `FVector RelativeOffset;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "LookAt")` — Offset from actor position to look at. Relative to actor if tracking an actor, relative to world otherwise.
- L66 _public member_ `uint8 bAllowRoll : 1;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "LookAt")` — True to allow user-defined roll, false otherwise.

#### class `ACineCameraActor`  
`class ACineCameraActor : public ACameraActor`  
_L73-105_
- reflection: `UCLASS(ClassGroup = Common, hideCategories = (Input, Rendering, AutoPlayerActivation), showcategories = ("Input|MouseInput", "Input|TouchInput"), Blueprintable, MinimalAPI)`
- inherits: `ACameraActor`
- desc: A CineCameraActor is a CameraActor specialized to work like a cinematic camera.
- L79 _public prototype_ `ACineCameraActor(const FObjectInitializer& ObjectInitializer);` — Ctor
- L81 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L82 _public prototype_ `virtual bool ShouldTickIfViewportsOnly() const override;`
- L83 _public prototype_ `virtual void PostInitializeComponents() override;`
- L86 _public member_ `FCameraLookatTrackingSettings LookatTrackingSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Camera Settings")`
- L90 _public function_ `UCineCameraComponent* GetCineCameraComponent() const` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Returns the CineCameraComponent of this CineCamera
- L94 _protected member_ `uint8 bResetInterplation : 1;` — Set to true to skip any interpolations on the next update. Resets to false automatically.
- L96 _protected prototype_ `FVector GetLookatLocation() const;`
- L98 _protected prototype_ `virtual void NotifyCameraCut() override;`
- L100 _protected prototype_ `bool ShouldTickForTracking() const;`
- L104 _private member_ `class UCineCameraComponent* CineCameraComponent;` — Returns CineCameraComponent subobject

### `Source/Runtime/CinematicCamera/Public/CineCameraComponent.h` (Public)


#### class `UCineCameraComponent`  
`class UCineCameraComponent : public UCameraComponent`  
_L21-272_
- reflection: `UCLASS(HideCategories = (CameraSettings), HideFunctions = (SetFieldOfView, SetAspectRatio), Blueprintable, ClassGroup = Camera, meta = (BlueprintSpawnableComponent), Config = Engine, MinimalAPI)`
- inherits: `UCameraComponent`
- desc: A specialized version of a camera component, geared toward cinematic usage.
- L27 _public prototype_ `UCineCameraComponent();` — Default constuctor.
- L29 _public prototype_ `virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView) override;`
- L31 _public prototype_ `virtual FText GetFilmbackText() const override;`
- L34 _public member_ `FCameraFilmbackSettings FilmbackSettings_DEPRECATED;` — `UPROPERTY()`
- L38 _public member_ `FCameraFilmbackSettings Filmback;` — `UPROPERTY(Interp, BlueprintSetter = SetFilmback, EditAnywhere, BlueprintReadWrite, Category = "Current Camera Settings")` — Controls the filmback of the camera.
- L41 _public prototype_ `void SetFilmback(const FCameraFilmbackSettings& NewFilmback);` — `UFUNCTION(BlueprintSetter)`
- L45 _public member_ `FCameraLensSettings LensSettings;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetLensSettings, BlueprintReadWrite, Category = "Current Camera Settings")` — Controls the camera's lens.
- L48 _public prototype_ `void SetLensSettings(const FCameraLensSettings& NewLensSettings);` — `UFUNCTION(BlueprintSetter)`
- L52 _public member_ `FCameraFocusSettings FocusSettings;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetFocusSettings, BlueprintReadWrite, Category = "Current Camera Settings")` — Controls the camera's focus.
- L55 _public prototype_ `void SetFocusSettings(const FCameraFocusSettings& NewFocusSettings);` — `UFUNCTION(BlueprintSetter)`
- L59 _public member_ `FPlateCropSettings CropSettings;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetCropSettings, BlueprintReadWrite, Category = "Current Camera Settings")` — Controls the crop settings.
- L62 _public prototype_ `void SetCropSettings(const FPlateCropSettings& NewCropSettings);` — `UFUNCTION(BlueprintSetter)`
- L66 _public member_ `float CurrentFocalLength;` — `UPROPERTY(Interp, BlueprintSetter = SetCurrentFocalLength, EditAnywhere, BlueprintReadWrite, Category = "Current Camera Settings")` — Current focal length of the camera (i.e. controls FoV, zoom)
- L70 _public member_ `float CurrentAperture;` — `UPROPERTY(Interp, BlueprintSetter = SetCurrentAperture, EditAnywhere, BlueprintReadWrite, Category = "Current Camera Settings")` — Current aperture, in terms of f-stop (e.g. 2.8 for f/2.8)
- L73 _public prototype_ `void SetCurrentAperture(const float NewCurrentAperture);` — `UFUNCTION(BlueprintSetter)`
- L77 _public member_ `float CurrentFocusDistance;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Current Camera Settings")` — Read-only. Control this value via FocusSettings.
- L81 _public member_ `ECameraExposureMethod ExposureMethod;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Current Camera Settings")` — Exposure method, for determining whether exposure-related post-process settings should be automatically set from camera parameters
- L84 _public member_ `uint32 bOverride_CustomNearClippingPlane:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Current Camera Settings", meta = (InlineEditConditionToggle))`
- L88 _public member_ `float CustomNearClippingPlane;` — `UPROPERTY(Interp, BlueprintSetter = SetCustomNearClippingPlane, EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Current Camera Settings", meta = (UIMin = "0.00001", ClampMin = "0.00001", editcondition = "bOverride_CustomNearClippingPlane", Units = cm))` — Set bOverride_CustomNearClippingPlane to true if you want to use a custom clipping plane instead of GNearClippingPlane.
- L93 _public member_ `float CurrentHorizontalFOV;` — `UPROPERTY(VisibleAnywhere, Category = "Current Camera Settings")` — Read-only. Control this value with CurrentFocalLength (and filmback settings).
- L97 _public prototype_ `virtual void SetFieldOfView(float InFieldOfView) override;` — Override setting FOV to manipulate Focal Length.
- L100 _public prototype_ `void SetCurrentFocalLength(float InFocalLength);` — `UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Cine Camera")`
- L104 _public prototype_ `void SetCustomNearClippingPlane(const float NewCustomNearClippingPlane);` — `UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Cine Camera")` — Sets near clipping plane of the cine camera.
- L108 _public prototype_ `float GetHorizontalFieldOfView() const;` — `UFUNCTION(BlueprintCallable, Category = "Cine Camera")` — Returns the horizonal FOV of the camera with current settings.
- L112 _public prototype_ `float GetVerticalFieldOfView() const;` — `UFUNCTION(BlueprintCallable, Category = "Cine Camera")` — Returns the vertical FOV of the camera with current settings.
- L115 _public prototype_ `float GetHorizontalProjectionOffset() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Cine Camera")`
- L118 _public prototype_ `float GetVerticalProjectionOffset() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Cine Camera")`
- L122 _public prototype_ `FString GetFilmbackPresetName() const;` — `UFUNCTION(BlueprintCallable, Category = "Cine Camera")` — Returns the filmback name of the camera with the current settings.
- L127 _public prototype_ `FString GetDefaultFilmbackPresetName() const;` — `UE_DEPRECATED(5.1, "This function has been deprecated, please access the presets via the CineCameraSettings object.")` — `UFUNCTION(BlueprintPure, Category = "Cine Camera")` — Returns the name of the default filmback preset.
- L131 _public prototype_ `void SetFilmbackPresetByName(const FString& InPresetName);` — `UFUNCTION(BlueprintCallable, Category = "Cine Camera")` — Set the current preset settings by preset name.
- L135 _public prototype_ `FString GetLensPresetName() const;` — `UFUNCTION(BlueprintCallable, Category = "Cine Camera")` — Returns the lens name of the camera with the current settings.
- L139 _public prototype_ `void SetLensPresetByName(const FString& InPresetName);` — `UFUNCTION(BlueprintCallable, Category = "Cine Camera")` — Set the current lens settings by preset name.
- L143 _public prototype_ `FString GetCropPresetName() const;` — `UFUNCTION(BlueprintCallable, Category = "Cine Camera")` — Returns the lens name of the camera with the current settings.
- L147 _public prototype_ `void SetCropPresetByName(const FString& InPresetName);` — `UFUNCTION(BlueprintCallable, Category = "Cine Camera")` — Set the current lens settings by preset name.
- L152 _public prototype_ `static TArray<FNamedFilmbackPreset> GetFilmbackPresetsCopy();` — `UE_DEPRECATED(5.1, "This function has been deprecated, please access the presets via the CineCameraSettings object.")` — `UFUNCTION(BlueprintCallable, Category = "Cine Camera")` — Returns a copy of the list of available filmback presets.
- L157 _public prototype_ `static TArray<FNamedLensPreset> GetLensPresetsCopy();` — `UE_DEPRECATED(5.1, "This function has been deprecated, please access the presets via the CineCameraSettings object.")` — `UFUNCTION(BlueprintCallable, Category = "Cine Camera")` — Returns a copy of the list of available lens presets.
- L161 _public prototype_ `static TArray<FNamedFilmbackPreset> const& GetFilmbackPresets();` — `UE_DEPRECATED(5.1, "This function has been deprecated, please access the presets via the CineCameraSettings object.")` — Returns a list of available filmback presets.
- L165 _public prototype_ `static TArray<FNamedLensPreset> const& GetLensPresets();` — `UE_DEPRECATED(5.1, "This function has been deprecated, please access the presets via the CineCameraSettings object.")` — Returns a list of available lens presets.
- L169 _public prototype_ `void UpdateDebugFocusPlane();` — Update the debug focus plane position and orientation.
- L173 _public prototype_ `float GetWorldToMetersScale() const;` — Returns the world to meters scale for the current UWorld
- L178 _protected member_ `float LastFocusDistance;` — Most recent calculated focus distance. Used for interpolation.
- L181 _protected member_ `uint8 bResetInterpolation : 1;` — Set to true to skip any interpolations on the next update. Resets to false automatically.
- L185 _protected prototype_ `virtual void PostLoad() override;`
- L189 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L190 _protected prototype_ `virtual void PostInitProperties() override;`
- L191 _protected prototype_ `virtual void OnRegister() override;`
- L192 _protected prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L195 _protected prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L201 _protected member_ `TObjectPtr<UStaticMesh> FocusPlaneVisualizationMesh;` — `UPROPERTY(transient)` — Mesh used for debug focus plane visualization
- L205 _protected member_ `TObjectPtr<UMaterial> FocusPlaneVisualizationMaterial;` — `UPROPERTY(transient)` — Material used for debug focus plane visualization
- L209 _protected member_ `TObjectPtr<UStaticMeshComponent> DebugFocusPlaneComponent;` — `UPROPERTY(transient)` — Component for the debug focus plane visualization
- L213 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> DebugFocusPlaneMID;` — `UPROPERTY(transient)` — Dynamic material instance for the debug focus plane visualization
- L215 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L216 _protected prototype_ `virtual void ResetProxyMeshTransform() override;`
- L222 _protected member_ `TArray<FNamedFilmbackPreset> FilmbackPresets;` — `UE_DEPRECATED(5.1, "This property is now located on the UCineCameraSettings object")` — `UPROPERTY(config)` — List of available filmback presets
- L227 _protected member_ `TArray<FNamedLensPreset> LensPresets;` — `UE_DEPRECATED(5.1, "This property is now located on the UCineCameraSettings object")` — `UPROPERTY(config)` — List of available lens presets
- L232 _protected member_ `FString DefaultFilmbackPresetName_DEPRECATED;` — `UE_DEPRECATED(5.1, "This property has been removed and fully replaced by DefaultFilmbackPreset on the UCineCameraSettings object")` — `UPROPERTY(config)` — Deprecated. See DefaultFilmbackPreset
- L237 _protected member_ `FString DefaultFilmbackPreset;` — `UE_DEPRECATED(5.1, "This property is now located on the UCineCameraSettings object")` — `UPROPERTY(config)` — Name of the default filmback preset
- L242 _protected member_ `FString DefaultLensPresetName;` — `UE_DEPRECATED(5.1, "This property is now located on the UCineCameraSettings object")` — `UPROPERTY(config)` — Name of the default lens preset
- L247 _protected member_ `float DefaultLensFocalLength;` — `UE_DEPRECATED(5.1, "This property is now located on the UCineCameraSettings object")` — `UPROPERTY(config)` — Default focal length (will be constrained by default lens)
- L252 _protected member_ `float DefaultLensFStop;` — `UE_DEPRECATED(5.1, "This property is now located on the UCineCameraSettings object")` — `UPROPERTY(config)` — Default aperture (will be constrained by default lens)
- L254 _protected prototype_ `virtual void UpdateCameraLens(float DeltaTime, FMinimalViewInfo& DesiredView);`
- L256 _protected prototype_ `virtual void NotifyCameraCut() override;`
- L258 _protected prototype_ `void RecalcDerivedData();`
- L261 _private prototype_ `float GetDesiredFocusDistance(const FVector& InLocation) const;`
- L262 _private prototype_ `void SetLensPresetByNameInternal(const FString& InPresetName);`
- L263 _private prototype_ `void SetFilmbackPresetByNameInternal(const FString& InPresetName, FCameraFilmbackSettings& InOutFilmbackSettings);`
- L264 _private prototype_ `void SetCropPresetByNameInternal(const FString& InPresetName);`
- L265 _private prototype_ `float GetHorizontalFieldOfViewInternal(bool bIncludeOverscan = true) const;`
- L266 _private prototype_ `float GetVerticalFieldOfViewInternal(bool bIncludeOverscan) const;`
- L269 _private prototype_ `void CreateDebugFocusPlane();`
- L270 _private prototype_ `void DestroyDebugFocusPlane();`

### `Source/Runtime/CinematicCamera/Public/CineCameraSettings.h` (Public)


#### struct `FCameraFilmbackSettings`  
`struct FCameraFilmbackSettings`  
_L15-65_
- reflection: `USTRUCT(BlueprintType)`
- desc: #note, this struct has a details customization in CameraFilmbackSettingsCustomization.cpp/h
- L21 _public member_ `float SensorWidth;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Filmback", meta = (ClampMin = "0.001", ForceUnits = mm))` — Horizontal size of filmback or digital sensor, in mm.
- L25 _public member_ `float SensorHeight;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Filmback", meta = (ClampMin = "0.001", ForceUnits = mm))` — Vertical size of filmback or digital sensor, in mm.
- L29 _public member_ `float SensorHorizontalOffset;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Filmback", meta = (ForceUnits = mm))` — Horizontal offset of the filmback, in mm.
- L33 _public member_ `float SensorVerticalOffset;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Filmback", meta = (ForceUnits = mm))` — Vertical offset of the filmback, in mm.
- L37 _public member_ `float SensorAspectRatio;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Filmback")` — Read-only. Computed from Sensor dimensions.
- L39 _public function_ `bool operator==(const FCameraFilmbackSettings& Other) const`
- L47 _public function_ `bool operator!=(const FCameraFilmbackSettings& Other) const`
- L52 _public function_ `void RecalcSensorAspectRatio()`
- L57 _public function_ `FCameraFilmbackSettings() : SensorWidth(24.89f) , SensorHeight(18.67f) , SensorHorizontalOffset(0.0f) , SensorVerticalOffset(0.0f) , SensorAspectRatio(1.33f)`

#### struct `FNamedFilmbackPreset`  
`struct FNamedFilmbackPreset`  
_L69-83_
- reflection: `USTRUCT(BlueprintType)`
- desc: A named bundle of filmback settings used to implement filmback presets
- L75 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Filmback")` — Name for the preset.
- L79 _public member_ `FText DisplayName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Filmback")` — Display name for the preset.
- L82 _public member_ `FCameraFilmbackSettings FilmbackSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Filmback")`

#### struct `FCameraLensSettings`  
`struct FCameraLensSettings`  
_L89-142_
- reflection: `USTRUCT(BlueprintType)`
- desc: #note, this struct has a details customization in CameraLensSettingsCustomization.cpp/h
- L94 _public function_ `FCameraLensSettings() : MinFocalLength(50.f) , MaxFocalLength(50.f) , MinFStop(2.f) , MaxFStop(2.f) , MinimumFocusDistance(15.f) , DiaphragmBladeCount(FPostProcessSettings::kDefaultDepthOfFieldBladeCount)` — Default constructor, initializing with default values
- L106 _public member_ `float MinFocalLength = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lens", meta = (ForceUnits = mm, ClampMin = "0.001"))` — Minimum focal length for this lens
- L110 _public member_ `float MaxFocalLength = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lens", meta = (ForceUnits = mm, ClampMin = "0.001"))` — Maximum focal length for this lens
- L114 _public member_ `float MinFStop = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lens")` — Minimum aperture for this lens (e.g. 2.8 for an f/2.8 lens)
- L118 _public member_ `float MaxFStop = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lens")` — Maximum aperture for this lens (e.g. 2.8 for an f/2.8 lens)
- L122 _public member_ `float MinimumFocusDistance = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lens", meta = (ForceUnits = mm))` — Shortest distance this lens can focus on.
- L126 _public member_ `float SqueezeFactor = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lens", meta = (ClampMin = "1", ClampMax = "2"))` — Squeeze factor for anamorphic lenses.
- L130 _public member_ `int32 DiaphragmBladeCount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lens", meta = (ClampMin = "4", ClampMax = "16"))` — Number of blades of diaphragm.
- L132 _public function_ `bool operator==(const FCameraLensSettings& Other) const`

#### struct `FNamedLensPreset`  
`struct FNamedLensPreset`  
_L146-156_
- reflection: `USTRUCT(BlueprintType)`
- desc: A named bundle of lens settings used to implement lens presets.
- L152 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lens")` — Name for the preset.
- L155 _public member_ `FCameraLensSettings LensSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lens")`

#### struct `FPlateCropSettings`  
`struct FPlateCropSettings`  
_L162-173_
- reflection: `USTRUCT(BlueprintType)`
- desc: #note, this struct has a details customization in CameraCropSettingsCustomization.cpp/h
- L167 _public member_ `float AspectRatio = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop", meta=(DisplayName = "Cropped Aspect Ratio"))`
- L169 _public function_ `bool operator==(const FPlateCropSettings& Other) const`

#### struct `FNamedPlateCropPreset`  
`struct FNamedPlateCropPreset`  
_L177-187_
- reflection: `USTRUCT(BlueprintType)`
- desc: A named bundle of crop settings used to implement crop presets.
- L183 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Crop")` — Name for the preset.
- L186 _public member_ `FPlateCropSettings CropSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Crop")`

#### enum `ECameraFocusMethod`  
`enum class ECameraFocusMethod : uint8`  
_L191-206_
- reflection: `UENUM()`
- desc: Supported methods for focusing the camera.
- L194 _public enumerator_ `DoNotOverride` — Don't override, ie. allow post process volume settings to persist.
- L197 _public enumerator_ `Manual` — Allows for specifying or animating exact focus distances.
- L200 _public enumerator_ `Tracking` — Locks focus to specific object.
- L203 _public enumerator_ `Disable` — Disable depth of field entirely.
- L205 _public enumerator_ `MAX UMETA(Hidden)`

#### struct `FCameraTrackingFocusSettings`  
`struct FCameraTrackingFocusSettings`  
_L210-230_
- reflection: `USTRUCT(BlueprintType)`
- desc: Settings to control tracking-focus mode.
- L216 _public member_ `TSoftObjectPtr<AActor> ActorToTrack;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Tracking Focus")` — Focus distance will be tied to this actor's location.
- L220 _public member_ `FVector RelativeOffset;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Tracking Focus")` — Offset from actor position to track. Relative to actor if tracking an actor, relative to world otherwise.
- L224 _public member_ `uint8 bDrawDebugTrackingFocusPoint : 1;` — `UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Tracking Focus")` — True to draw a debug representation of the tracked position.
- L226 _public function_ `FCameraTrackingFocusSettings() : RelativeOffset(ForceInitToZero), bDrawDebugTrackingFocusPoint(false)`

#### struct `FCameraFocusSettings`  
`struct FCameraFocusSettings`  
_L234-284_
- reflection: `USTRUCT(BlueprintType)`
- desc: Settings to control camera focus
- L240 _public member_ `ECameraFocusMethod FocusMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Focus Method")` — Which method to use to handle camera focus
- L244 _public member_ `float ManualFocusDistance;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Manual Focus Settings", meta=(Units=cm))` — Manually-controlled focus distance (manual focus mode only)
- L248 _public member_ `FCameraTrackingFocusSettings TrackingFocusSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tracking Focus Settings")` — Settings to control tracking focus (tracking focus mode only)
- L253 _public member_ `uint8 bDrawDebugFocusPlane : 1;` — `UPROPERTY(Transient, EditAnywhere, Category = "Focus Settings")` — True to draw a translucent plane at the current focus depth, for easy tweaking.
- L257 _public member_ `FColor DebugFocusPlaneColor;` — `UPROPERTY(EditAnywhere, Category = "Focus Settings", meta = (EditCondition = "bDrawDebugFocusPlane"))` — For customizing the focus plane color, in case the default doesn't show up well in your scene.
- L262 _public member_ `uint8 bSmoothFocusChanges : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Focus Settings")` — True to use interpolation to smooth out changes in focus distance, false for focus distance changes to be instantaneous.
- L266 _public member_ `float FocusSmoothingInterpSpeed;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Focus Settings")` — Controls interpolation speed when smoothing focus distance changes. Ignored if bSmoothFocusChanges is false.
- L270 _public member_ `float FocusOffset;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Focus Settings")` — Additional focus depth offset, used for manually tweaking if your chosen focus method needs adjustment
- L272 _public function_ `FCameraFocusSettings() : FocusMethod(ECameraFocusMethod::Manual), ManualFocusDistance(100000.f), TrackingFocusSettings(), #if WITH_EDITORONLY_DATA bDrawDebugFocusPlane(false), DebugFocusPlaneColor(102, 26, 204, 153),`

#### enum `ECameraExposureMethod`  
`enum class ECameraExposureMethod : uint8`  
_L288-297_
- reflection: `UENUM()`
- desc: Supported methods for exposure handling.
- L291 _public enumerator_ `DoNotOverride` — Don't override, ie. allow post process volume settings to persist.
- L294 _public enumerator_ `Enabled` — Set exposure settings based on the current lens and filmback settings.
- L296 _public enumerator_ `MAX UMETA(Hidden)`

#### class `UCineCameraSettings`  
`class UCineCameraSettings : public UDeveloperSettings`  
_L300-410_
- reflection: `UCLASS(config=Engine, defaultconfig, meta=(DisplayName="Cinematic Camera"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- L305 _public prototype_ `virtual void PostInitProperties() override;`
- L308 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L313 _public member_ `FString DefaultLensPresetName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetDefaultLensPresetName, Category=Lens, meta=(GetOptions=GetLensPresetNames))` — Name of the default lens preset
- L317 _public member_ `float DefaultLensFocalLength;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetDefaultLensFocalLength, Category=Lens)` — Default focal length (will be constrained by default lens)
- L321 _public member_ `float DefaultLensFStop;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetDefaultLensFStop, Category=Lens)` — Default aperture (will be constrained by default lens)
- L325 _public member_ `TArray<FNamedLensPreset> LensPresets;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetLensPresets, Category=Lens, meta=(TitleProperty=Name))` — List of available lens presets
- L329 _public member_ `FString DefaultFilmbackPreset;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetDefaultfilmbackPreset, Category=Filmback, meta=(GetOptions=GetFilmbackPresetNames))` — Name of the default filmback preset
- L333 _public member_ `TArray<FNamedFilmbackPreset> FilmbackPresets;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetFilmbackPresets, Category=Filmback, meta=(TitleProperty=Name))` — List of available filmback presets
- L337 _public member_ `FString DefaultCropPresetName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetDefaultCropPresetName, Category=Crop, meta=(GetOptions=GetCropPresetNames))` — Name of the default crop preset
- L341 _public member_ `TArray<FNamedPlateCropPreset> CropPresets;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetCropPresets, Category=Crop, meta=(TitleProperty=Name))` — List of available crop presets
- L343 _public prototype_ `static TArray<FNamedLensPreset> const& GetLensPresets();`
- L344 _public prototype_ `static TArray<FNamedFilmbackPreset> const& GetFilmbackPresets();`
- L345 _public prototype_ `static TArray<FNamedPlateCropPreset> const& GetCropPresets();`
- L350 _public prototype_ `bool GetLensPresetByName(const FString PresetName, FCameraLensSettings& LensSettings);` — `UFUNCTION(BlueprintCallable, Category=Cinematics, meta=(ReturnDisplayName = "Success"))` — Gets the Lens settings associated with a given preset name Returns true if a preset with the given name was found
- L355 _public prototype_ `bool GetFilmbackPresetByName(const FString PresetName, FCameraFilmbackSettings& FilmbackSettings);` — `UFUNCTION(BlueprintCallable, Category=Cinematics, meta=(ReturnDisplayName = "Success"))` — Gets the Filmback settings associated with a given preset name Returns true if a preset with the given name was found
- L360 _public prototype_ `bool GetCropPresetByName(const FString PresetName, FPlateCropSettings& CropSettings);` — `UFUNCTION(BlueprintCallable, Category=Cinematics, meta=(ReturnDisplayName = "Success"))` — Gets the Crop settings associated with a given preset name Returns true if a preset with the given name was found
- L364 _private prototype_ `static UCineCameraSettings* GetCineCameraSettings();` — `UFUNCTION(BlueprintCallable, Category=Cinematics)`
- L369 _private prototype_ `void SetDefaultLensPresetName(const FString InDefaultLensPresetName);` — `UFUNCTION(BlueprintSetter)`
- L372 _private prototype_ `void SetDefaultLensFocalLength(const float InDefaultLensFocalLength);` — `UFUNCTION(BlueprintSetter)`
- L375 _private prototype_ `void SetDefaultLensFStop(const float InDefaultLensFStop);` — `UFUNCTION(BlueprintSetter)`
- L378 _private prototype_ `void SetLensPresets(const TArray<FNamedLensPreset>& InLensPresets);` — `UFUNCTION(BlueprintSetter)`
- L381 _private prototype_ `void SetDefaultFilmbackPreset(const FString InDefaultFilmbackPreset);` — `UFUNCTION(BlueprintSetter)`
- L384 _private prototype_ `void SetFilmbackPresets(const TArray<FNamedFilmbackPreset>& InFilmbackPresets);` — `UFUNCTION(BlueprintSetter)`
- L387 _private prototype_ `void SetDefaultCropPresetName(const FString InDefaultCropPresetName);` — `UFUNCTION(BlueprintSetter)`
- L390 _private prototype_ `void SetCropPresets(const TArray<FNamedPlateCropPreset>& InCropPresets);` — `UFUNCTION(BlueprintSetter)`
- L395 _private prototype_ `TArray<FString> GetLensPresetNames() const;` — `UFUNCTION()`
- L398 _private prototype_ `TArray<FString> GetFilmbackPresetNames() const;` — `UFUNCTION()`
- L401 _private prototype_ `TArray<FString> GetCropPresetNames() const;` — `UFUNCTION()`
- L403 _private member_ `static const FString CineCameraConfigSection;`
- L404 _private member_ `TSharedPtr<SNotificationItem> Notification;`
- L405 _private prototype_ `void CopyOldConfigSettings();`
- L406 _private prototype_ `void CloseNotification();`
- L409 _private prototype_ `void RecalcSensorAspectRatios();` — Sensor aspect ratio is derived from Sensor Height and Width so needs to be updated when either property is updated

### `Source/Runtime/CinematicCamera/Public/CinematicCameraModule.h` (Public)


#### class `ICinematicCameraModule`  
`class ICinematicCameraModule : public IModuleInterface`  
_L11-14_
- inherits: `IModuleInterface`
- desc: Foliage Edit mode module interface
