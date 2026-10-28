# Plugins / CineCameraRigs

- module root: `Plugins/Experimental/CineCameraRigs/Source/CineCameraRigs`
- headers: 9; symbols: 197
- symbol kinds: class=7, delegate=3, enum=3, enumerator=10, function=6, macro=5, member=69, prototype=91, struct=3
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ConcertSyncCore, CoreUObject, Engine, LevelSequence, LevelSequenceEditor, MovieScene, MovieSceneTracks, SequencerScriptingEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: AnimationCore, CinematicCamera, Constraints, Core

### `Plugins/Experimental/CineCameraRigs/Source/CineCameraRigs/Private/CineSplineLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCineSpline, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCineSpline, Log, All);`

### `Plugins/Experimental/CineCameraRigs/Source/CineCameraRigs/Public/CineCameraAttachMount.h` (Public)


#### class `ACineCameraAttachMount`  
`class ACineCameraAttachMount : public AActor`  
_L19-142_
- reflection: `UCLASS(Blueprintable, Category = "VirtualProduction")`
- inherits: `AActor`
- L24 _public prototype_ `ACineCameraAttachMount(const FObjectInitializer& ObjectInitializer);`
- L26 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L27 _public prototype_ `virtual bool ShouldTickIfViewportsOnly() const override;`
- L28 _public prototype_ `virtual class USceneComponent* GetDefaultAttachComponent() const override;`
- L32 _public member_ `TSoftObjectPtr<AActor> TargetActor;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Constraint")` — Constraint target actor
- L36 _public member_ `FName TargetSocket;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Constraint")` — Constraint target socket name
- L40 _public member_ `FTransformFilter TransformFilter;` — `UPROPERTY(EditAnywhere, BlueprintSetter=SetTransformFilter, Category = "Constraint")` — Constraint axis filter
- L44 _public member_ `TObjectPtr<USpringArmComponent> SpringArmComponent;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Default")` — SprintArm component for lag effect
- L48 _public member_ `bool bEnableLocationLag = true;` — `UPROPERTY(EditAnywhere, BlueprintSetter=SetEnableLocationLag, Category = "Lag")` — If true, attached actors lag behind target position to smooth its movement
- L52 _public member_ `bool bEnableRotationLag = true;` — `UPROPERTY(EditAnywhere, BlueprintSetter=SetEnableRotationLag, Category = "Lag")` — If true, attached actors lag behind target position to smooth its movement
- L56 _public member_ `float LocationLagSpeed = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintSetter=SetLocationLagSpeed, Category = "Lag", meta = (editcondition = "bEnableLocationLag", ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))` — If bEnableLocationLag is true, controls how quickly camera reaches target position. Low values are slower (more lag), high values are faster (less lag), while zero is instant (no lag)
- L60 _public member_ `float RotationLagSpeed = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintSetter=SetRotationLagSpeed, Category = "Lag", meta = (editcondition = "bEnableRotationLag", ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))` — If bEnableRotationLag is true, controls how quickly camera reaches target position. Low values are slower (more lag), high values are faster (less lag), while zero is instant (no lag)
- L64 _public prototype_ `void SetEnableLocationLag(bool bEnabled);` — `UFUNCTION(BlueprintSetter)` — Set bEnableLocationLag
- L68 _public prototype_ `void SetEnableRotationLag(bool bEnabled);` — `UFUNCTION(BlueprintSetter)` — Set bEnableRotationLag
- L72 _public prototype_ `void SetLocationLagSpeed(float Speed);` — `UFUNCTION(BlueprintSetter)` — Set LocationLagSpeed
- L76 _public prototype_ `void SetRotationLagSpeed(float Speed);` — `UFUNCTION(BlueprintSetter)` — Set RotationLagSpeed
- L80 _public prototype_ `void SetTransformFilter(const FTransformFilter& InFilter);` — `UFUNCTION(BlueprintSetter)` — Set TransformFilter for the internal constraint
- L86 _public member_ `bool bShowPreviewMeshes;` — `UPROPERTY(Transient, EditAnywhere, Category = "Preview")` — If enabled, it shows the preview meshes
- L90 _public member_ `float PreviewMeshScale;` — `UPROPERTY(Transient, EditAnywhere, Category = "Preview")` — Scale of the preview meshes
- L94 _public member_ `TObjectPtr<UStaticMeshComponent> PreviewMesh_Root;` — `UPROPERTY(Transient)` — Preview mesh for this actor itself
- L98 _public member_ `TObjectPtr<UStaticMesh> MountMesh;` — `UPROPERTY(Transient)` — Preview mesh
- L102 _public member_ `TArray<TObjectPtr<UStaticMeshComponent>> PreviewMeshes_Mount;` — `UPROPERTY(Transient)` — Preview mount mesh components
- L107 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L108 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L113 _public prototype_ `UTickableParentConstraint* GetConstraint();` — `UFUNCTION(BlueprintPure, Category = "Constraint")` — Get ParentConstraint object. Returns nullptr if there is no constraint
- L117 _public prototype_ `void ResetLocationOffset();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Constraint")` — Reset constraint offset for location
- L121 _public prototype_ `void ResetRotationOffset();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Constraint")` — Reset constraint offset for rotation
- L125 _public prototype_ `void ZeroRoll();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Constraint")` — Zero out rotationX in world space. This can help setting the mount parallel to the ground.
- L129 _public prototype_ `void ZeroTilt();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Constraint")` — Zero out rotationY in world space. This can help setting the mount parallel to the ground.
- L132 _private member_ `bool bConstraintUpdated = false;`
- L134 _private prototype_ `void CreateConstraint();`
- L135 _private prototype_ `void UpdateAxisFilter();`
- L138 _private prototype_ `void CreatePreviewMesh();`
- L139 _private prototype_ `void UpdatePreviewMeshes();`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CINECAMERARIGS_API`

### `Plugins/Experimental/CineCameraRigs/Source/CineCameraRigs/Public/CineCameraRigRail.h` (Public)


#### enum `ECineCameraRigRailDriveMode`  
`enum class ECineCameraRigRailDriveMode : uint8`  
_L19-29_
- reflection: `UENUM(BlueprintType)`
- L22 _public enumerator_ `Manual` — Manual Mode
- L25 _public enumerator_ `Duration` — Duration Mode. AbsolutePostionOnRail is updated based on the spline duration
- L28 _public enumerator_ `Speed` — Speed Mode. AbsolutePositionOnRail is updated based on the specified speed

#### enum `ECineCameraRigRailLoopMode`  
`enum class ECineCameraRigRailLoopMode : uint8`  
_L32-42_
- reflection: `UENUM(BlueprintType)`
- L35 _public enumerator_ `NoLoop` — Play once
- L38 _public enumerator_ `Loop` — Play Loop
- L41 _public enumerator_ `Bounce` — Play forward then backward

#### class `ACineCameraRigRail`  
`class ACineCameraRigRail : public ACameraRig_Rail`  
_L45-225_
- reflection: `UCLASS(Blueprintable, Category = "VirtualProduction")`
- inherits: `ACameraRig_Rail`
- L50 _public prototype_ `ACineCameraRigRail(const FObjectInitializer& ObjectInitializer);`
- L52 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L53 _public prototype_ `virtual void PostLoad() override;`
- L57 _public function_ `UCineSplineComponent* GetCineSplineComponent() const` — `UFUNCTION(BlueprintPure, Category = "Rail Components")` — Returns CineSplineComponent
- L60 _public function_ `void SetSplineComponent(UCineSplineComponent* NewSplineComponent)` — `UFUNCTION(BlueprintSetter, Category = "Rail Components")`
- L64 _public member_ `bool bUseAbsolutePosition = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rail Controls")` — Use AbsolutePosition metadata to parameterize the spline
- L68 _public member_ `float AbsolutePositionOnRail = 1.0f;` — `UPROPERTY(EditAnywhere, Interp, BlueprintSetter="SetAbsolutePositionOnRail", Category = "Rail Controls", meta = (EditCondition = "bUseAbsolutePosition"))` — Custom parameter to drive current position
- L72 _public member_ `bool bUsePointRotation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rail Controls")` — Use PointRotation metadata for attachment orientation. If false, attachment orientation is based on the spline curvature
- L76 _public member_ `TObjectPtr<UMaterialInterface> SplineMeshMaterial;` — `UPROPERTY(BlueprintSetter=SetSplineMeshMaterial, Category = "SplineVisualization")` — Material assigned to spline component mesh
- L80 _public member_ `TArray<TObjectPtr<UMaterialInstanceDynamic>> SplineMeshMIDs;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "SplineVisualization")` — Material Instance Dynamic created for the spline mesh
- L84 _public member_ `TObjectPtr<UTexture2D> SplineMeshTexture;` — `UPROPERTY(BlueprintSetter=SetSplineMeshTexture, Category = "SplineVisualization")` — Texture that can be set to SplineMeshMIDs
- L88 _public member_ `bool bDisplaySpeedHeatmap = true;` — `UPROPERTY(EditAnywhere, BlueprintSetter=SetDisplaySpeedHeatmap, Category = "SplineVisualization", meta=(EditCondition="!IsSequencerDriven()"))` — Enable speed visualization. Automatically disabled when position property is driven in Sequencer
- L92 _public member_ `int32 SpeedSampleCountPerSegment = 4;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SplineVisualization", meta=(ClampMin=1, EditCondition="bDisplaySpeedHeatmap"))` — Number of speed samples per spline segment
- L96 _public member_ `bool bAttachLocationX = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment|Location")` — Determines if camera mount inherits LocationX
- L100 _public member_ `bool bAttachLocationY = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment|Location")` — Determines if camera mount inherits LocationY
- L104 _public member_ `bool bAttachLocationZ = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment|Location")` — Determines if camera mount inherits LocationZ
- L108 _public member_ `bool bAttachRotationX = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment|Rotation")` — Determines if camera mount inherits RotationX
- L112 _public member_ `bool bAttachRotationY = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment|Rotation")` — Determines if camera mount inherits RotationY
- L116 _public member_ `bool bAttachRotationZ = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment|Rotation")` — Determines if camera mount inherits RotationZ
- L120 _public member_ `bool bInheritFocalLength = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment|Camera")` — Determines if it can drive focal length on the attached actors
- L124 _public member_ `bool bInheritAperture = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment|Camera")` — Determines if it can drive aperture on the attached actors
- L128 _public member_ `bool bInheritFocusDistance = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment|Camera")` — Determines if it can drive focus distance on the attached actors
- L132 _public member_ `ECineCameraRigRailDriveMode DriveMode = ECineCameraRigRailDriveMode::Manual;` — `UPROPERTY(EditAnywhere, BlueprintSetter=SetDriveMode, Category = "DriveMode")` — Drive Mode to update position in tick
- L136 _public member_ `float Speed = 100;` — `UPROPERTY(EditAnywhere, Interp, Category = "DriveMode")` — Specifies the drive speed of the rig rail in centimeter per second
- L140 _public member_ `bool bPlay = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DriveMode")` — Determine if it can update position in Duration mode or Speed mode. If false, it pauses the update.
- L144 _public member_ `bool bReverse = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DriveMode", meta = (EditCondition="LoopMode != ECineCameraRigRailLoopMode::Bounce"))` — Determine if it plays in reverse.
- L148 _public member_ `bool bLoop = true;` — `UPROPERTY(BlueprintReadWrite, Category = "DriveMode", meta = (DeprecatedProperty, DeprecationMessage = "Use LoopMode instead"))` — Enable loop in speed or duration mode
- L151 _public member_ `ECineCameraRigRailLoopMode LoopMode = ECineCameraRigRailLoopMode::Loop;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DriveMode")`
- L155 _public member_ `bool bCompensateTimeScale = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DriveMode")` — If enabled, it compensates world time dilation in Speed/Duration mode so that the spline moves as intended speed regardless of recording time scale
- L159 _public prototype_ `void SetSplineMeshMaterial(UMaterialInterface* InMaterial);` — `UFUNCTION(BlueprintSetter)` — Set spline mesh material
- L163 _public prototype_ `void SetSplineMeshTexture(UTexture2D* InTexture);` — `UFUNCTION(BlueprintSetter)` — Set texture used in the spline mesh material
- L167 _public prototype_ `FVector GetVelocityAtPosition(const float InPosition, const float delta = 0.001) const;` — `UFUNCTION(BlueprintCallable, Category = "CineCameraRigRail")` — Calculate internal velocity at the given position
- L171 _public prototype_ `void SetDriveMode(ECineCameraRigRailDriveMode InMode);` — `UFUNCTION(BlueprintSetter)` — Set drive mode
- L175 _public prototype_ `void SetDisplaySpeedHeatmap(bool bEnable);` — `UFUNCTION(BlueprintSetter)` — Enable display speed heatmap
- L179 _public prototype_ `bool IsSequencerDriven();` — `UFUNCTION()` — Returns true if the rig rail is driven by Sequencer
- L183 _public prototype_ `void SetAbsolutePositionOnRail(float Value);` — `UFUNCTION(BlueprintSetter)` — Set AbsolutePositionOnRail value
- L186 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L191 _protected member_ `TObjectPtr<class UCineSplineComponent> CineSplineComponent;` — `UPROPERTY(Category = "CineSpline", VisibleAnywhere, BlueprintReadOnly)`
- L193 _protected prototype_ `virtual void UpdateRailComponents() override;`
- L195 _protected prototype_ `void UpdateSplineMeshMID();`
- L196 _protected prototype_ `void SetMIDParameters();`
- L197 _protected prototype_ `void UpdateSpeedHeatmap();`
- L199 _protected prototype_ `void OnSplineEdited();`
- L201 _protected prototype_ `void DriveByParam(float DeltaTime);`
- L202 _protected prototype_ `void DriveBySpeed(float DeltaTime);`
- L203 _protected prototype_ `float StartPositionValue() const;`
- L204 _protected prototype_ `float LastPositionValue() const;`
- L205 _protected member_ `float SpeedProgress = 0.0f;`
- L206 _protected prototype_ `void UpdateSpeedProgress();`
- L207 _protected prototype_ `float AdjustDeltaTime(float InDeltaTime) const;`
- L209 _protected member_ `bool bBounceForward = true;`
- L210 _protected prototype_ `bool PlayForward() const;`
- L213 _protected prototype_ `void ConditionalRegisterTimerManager();`
- L214 _protected prototype_ `UMovieSceneFloatTrack* FindPositionTrack(const UMovieSceneSequence* InSequence);`
- L216 _protected member_ `FTimerHandle SequencerCheckHandle;`
- L220 _protected prototype_ `void OnSequencerCheck();` — `UFUNCTION()` — Check if the rig rail is driven by Sequencer
- L222 _protected member_ `bool bSequencerDriven = false;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CINECAMERARIGS_API`

### `Plugins/Experimental/CineCameraRigs/Source/CineCameraRigs/Public/CineCameraRigRailHelpers.h` (Public)


#### class `UCineCameraRigRailHelpers`  
`class UCineCameraRigRailHelpers : public UBlueprintFunctionLibrary`  
_L14-21_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L20 _public prototype_ `static void CreateOrUpdateSplineHeatmapTexture(UPARAM(ref) UTexture2D*& Texture, const TArray<float>& DataValues, const float LowValue, const float AverageValue, const float HighValue);` — `UFUNCTION(BlueprintCallable, Category = "CineCameraRigRail")` — Create a transient heatmap texture from data values

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CINECAMERARIGS_API`

### `Plugins/Experimental/CineCameraRigs/Source/CineCameraRigs/Public/CineCameraRigs.h` (Public)


#### class `FCineCameraRigsModule`  
`class FCineCameraRigsModule : public IModuleInterface`  
_L8-18_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _public prototype_ `static float GetAbsolutePositionOnRail(const UObject* Object);`
- L17 _public prototype_ `static void SetAbsolutePositionOnRail(UObject* Object, float InNewValue);`

### `Plugins/Experimental/CineCameraRigs/Source/CineCameraRigs/Public/CineCameraRigsSettings.h` (Public)


#### class `UCineCameraRigRailSettings`  
`class UCineCameraRigRailSettings : public UObject`  
_L14-29_
- reflection: `UCLASS(BlueprintType, Config = CineCameraRigs)`
- inherits: `UObject`
- L20 _public member_ `TSoftObjectPtr<UMaterialInterface> DefaultSplineMeshMaterial;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = CineCameraRigRail)` — Path to the default spline mesh material used in CineCameraRigRail
- L24 _public member_ `TSoftObjectPtr<UTexture2D> DefaultSplineMeshTexture;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = CineCameraRigRail)` — Path to the default spline mesh texture used when speed visualization is off
- L28 _public member_ `TSoftObjectPtr<UTexture2D> SpeedModeSplineMeshTexture;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = CineCameraRigRail)` — Path to the texture used in the speed visualization when drive mode is Speed

### `Plugins/Experimental/CineCameraRigs/Source/CineCameraRigs/Public/CineSplineComponent.h` (Public)


#### class `UCineSplineComponent`  
`class UCineSplineComponent : public USplineComponent`  
_L19-136_
- reflection: `UCLASS(ClassGroup = Utility, ShowCategories = (Mobility), HideCategories = (Physics, Collision, Lighting, Rendering, Mobile), meta = (BlueprintSpawnableComponent))`
- inherits: `USplineComponent`
- L24 _public prototype_ `UCineSplineComponent(const FObjectInitializer& ObjectInitializer);`
- L30 _public member_ `FCineSplineCurveDefaults CameraSplineDefaults;` — `UPROPERTY(Category = Camera, EditDefaultsOnly)` — Defaults which are used to propagate values to spline points on instances of this in the world
- L34 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L36 _public prototype_ `virtual void PostLoad() override;`
- L40 _public prototype_ `virtual USplineMetadata* GetSplinePointsMetadata() override;` — Spline component interface
- L41 _public prototype_ `virtual const USplineMetadata* GetSplinePointsMetadata() const override;`
- L42 _public function_ `virtual bool AllowsSplinePointScaleEditing() const override`
- L44 _public prototype_ `void ApplyComponentInstanceData(struct FCineSplineInstanceData* ComponentInstanceData, const bool bPostUCS);`
- L47 _public prototype_ `virtual TStructOnScope<FActorComponentInstanceData> GetComponentInstanceData() const override;` — UActorComponent Interface
- L51 _public member_ `TObjectPtr<UCineSplineMetadata> CineSplineMetadata;` — `UPROPERTY(Instanced)` — Pointer to metadata
- L55 _public prototype_ `void SetFocalLengthAtSplinePoint(const int32 PointIndex, const float Value );` — `UFUNCTION(BlueprintCallable, Category = "CineSpline")` — Set focal lenght metadata at a given splint point
- L59 _public prototype_ `void SetApertureAtSplinePoint(const int32 PointIndex, const float value );` — `UFUNCTION(BlueprintCallable, Category = "CineSpline")` — Set aperture metadata at a given spline point
- L63 _public prototype_ `void SetFocusDistanceAtSplinePoint(const int32 PointIndex, const float value);` — `UFUNCTION(BlueprintCallable, Category = "CineSpline")` — Set focus distance metadata at a given spline point
- L67 _public prototype_ `void SetAbsolutePositionAtSplinePoint(const int32 PointIndex, const float value);` — `UFUNCTION(BlueprintCallable, Category = "CineSpline")` — Set custom position metadata at a given spline point
- L71 _public prototype_ `void SetPointRotationAtSplinePoint(const int32 PointIndex, const FQuat value);` — `UFUNCTION(BlueprintCallable, Category = "CineSpline")` — Set camera rotation metadata at a given spline point
- L75 _public prototype_ `bool FindSplineDataAtPosition(const float InPosition, int32& OutIndex, const float Tolerance=0.001f) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CineSpline")` — Returns true if there is a spline point at given custom position
- L79 _public prototype_ `void UpdateSplineDataAtIndex(const int InIndex, const FCineSplinePointData& InPointData );` — `UFUNCTION(BlueprintCallable, Category = "CineSpline")` — Update spline point data at the given spline point
- L83 _public prototype_ `void AddSplineDataAtPosition(const float InPosition, const FCineSplinePointData& InPointData);` — `UFUNCTION(BlueprintCallable, Category = "CineSpline")` — Add a new spline point data at the given custom position
- L87 _public prototype_ `FCineSplinePointData GetSplineDataAtPosition(const float InPosition) const;` — `UFUNCTION(BlueprintCallable, Category = "CineSpline")` — Get a spline point data at the given custom position
- L91 _public prototype_ `float GetInputKeyAtPosition(const float InPosition) const;` — `UFUNCTION(BlueprintCallable, Category = "CineSpline")` — Get input key value from custom position
- L95 _public prototype_ `float GetPositionAtInputKey(const float InKey) const;` — `UFUNCTION(BlueprintCallable, Category = "CineSpline")` — Get custom position value at spline input key
- L99 _public prototype_ `FQuat GetPointRotationAtSplinePoint(int32 Index) const;` — `UFUNCTION(BlueprintCallable, Category = "CineSpline")` — Get camera rotation metadata property value along the spline at spline point
- L103 _public prototype_ `FQuat GetPointRotationAtSplineInputKey(float InKey) const;` — `UFUNCTION(BlueprintCallable, Category = "CineSpline")` — Get camera rotation metadata value along the spline at spline input key
- L106 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSplineEdited);`
- L107 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSplineEdited_BP);`
- L109 _public member_ `FOnSplineEdited OnSplineEdited;`
- L113 _public member_ `FOnSplineEdited_BP OnSplineEdited_BP;` — `UPROPERTY(BlueprintAssignable, Category = "CineSpline", meta = (DisplayName = "OnSplineEdited"))` — Event trigerred when spline is edited
- L116 _public prototype_ `virtual void UpdateSpline() override;` — Update the spline tangents and SplineReparamTable. And trigers OnSplineEdited delegates
- L121 _public member_ `bool bShouldVisualizeNormalizedPosition;` — `UPROPERTY(EditAnywhere, Category = "CineSplineEditor", meta = (InlineEditConditionToggle = true))` — Toggle if visualizer displays normalized position or absolute position
- L125 _public member_ `bool bShouldVisualizeSplineLength;` — `UPROPERTY(EditAnywhere, Category = "CineSplineEditor", meta = (InlineEditConditionToggle = true))` — Whether spline length value should be displayed in visualizer
- L129 _public member_ `bool bShouldVisualizePointRotation;` — `UPROPERTY(EditAnywhere, Category = "CineSplineEditor", meta = (InlineEditConditionToggle = true))` — Whether point rotation arrows should be displayed in visualizer
- L134 _protected prototype_ `void SynchronizeProperties();`

#### struct `FCineSplineInstanceData`  
`struct FCineSplineInstanceData : public FSplineInstanceData`  
_L139-150_
- reflection: `USTRUCT()`
- inherits: `FSplineInstanceData`
- L143 _public prototype_ `FCineSplineInstanceData() = default;`
- L144 _public function_ `explicit FCineSplineInstanceData(const UCineSplineComponent* SourceComponent) : FSplineInstanceData(SourceComponent)`
- L146 _public prototype_ `virtual void ApplyToComponent(UActorComponent* Component, const ECacheApplyPhase CacheApplyPhase) override;`
- L149 _public member_ `TObjectPtr<UCineSplineMetadata> CineSplineMetadata;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API CINECAMERARIGS_API`
- L106 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSplineEdited);`
- L107 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSplineEdited_BP);`

### `Plugins/Experimental/CineCameraRigs/Source/CineCameraRigs/Public/CineSplineMetadata.h` (Public)


#### struct `FCineSplineCurveDefaults`  
`struct FCineSplineCurveDefaults`  
_L15-41_
- reflection: `USTRUCT()`
- L19 _public function_ `FCineSplineCurveDefaults() : DefaultAbsolutePosition(-1.0f) , DefaultFocalLength(35.0f) , DefaultAperture(2.8f) , DefaultFocusDistance(100000.f) , DefaultPointRotation(FQuat::Identity)`
- L28 _public member_ `float DefaultAbsolutePosition;` — `UPROPERTY(EditDefaultsOnly, Category = CineSplineCurveDefaults)`
- L31 _public member_ `float DefaultFocalLength;` — `UPROPERTY(EditDefaultsOnly, Category = CineSplineCurveDefaults)`
- L34 _public member_ `float DefaultAperture;` — `UPROPERTY(EditDefaultsOnly, Category = CineSplineCurveDefaults)`
- L37 _public member_ `float DefaultFocusDistance;` — `UPROPERTY(EditDefaultsOnly, Category = CineSplineCurveDefaults)`
- L40 _public member_ `FQuat DefaultPointRotation;` — `UPROPERTY(EditDefaultsOnly, Category = CineSplineCurveDefaults)`

#### enum `ECineSplineMetadataTangentType`  
`enum class ECineSplineMetadataTangentType : uint8`  
_L45-51_
- reflection: `UENUM()`
- desc: Interpolation type for CineSpline Metadata
- L47 _public enumerator_ `Linear`
- L48 _public enumerator_ `Curve`
- L49 _public enumerator_ `Constant`
- L50 _public enumerator_ `CurveClamped`

#### class `UCineSplineMetadata`  
`class UCineSplineMetadata : public USplineMetadata`  
_L60-100_
- reflection: `UCLASS()`
- inherits: `USplineMetadata`
- L66 _public prototype_ `virtual void InsertPoint(int32 Index, float Alpha, bool bClosedLoop) override;` — Insert point before index, lerping metadata between previous and next key values
- L68 _public prototype_ `virtual void UpdatePoint(int32 Index, float Alpha, bool bClosedLoop) override;` — Update point at index by lerping metadata between previous and next key values
- L69 _public prototype_ `virtual void AddPoint(float InputKey) override;`
- L70 _public prototype_ `virtual void RemovePoint(int32 Index) override;`
- L71 _public prototype_ `virtual void DuplicatePoint(int32 Index) override;`
- L72 _public prototype_ `virtual void CopyPoint(const USplineMetadata* FromSplineMetadata, int32 FromIndex, int32 ToIndex) override;`
- L73 _public prototype_ `virtual void Reset(int32 NumPoints) override;`
- L74 _public prototype_ `virtual void Fixup(int32 NumPoints, USplineComponent* SplineComp) override;`
- L77 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L81 _public member_ `FInterpCurveFloat AbsolutePosition;` — `UPROPERTY(EditAnywhere, Category = "Point")`
- L84 _public member_ `FInterpCurveFloat FocalLength;` — `UPROPERTY(EditAnywhere, Category = "Camera")`
- L87 _public member_ `FInterpCurveFloat Aperture;` — `UPROPERTY(EditAnywhere, Category = "Camera")`
- L90 _public member_ `FInterpCurveFloat FocusDistance;` — `UPROPERTY(EditAnywhere, Category = "Camera")`
- L93 _public member_ `FInterpCurveQuat PointRotation;` — `UPROPERTY(EditAnywhere, Category = "Camera")`
- L96 _public prototype_ `void AutoSetTangents();` — Automatically set the tangents on the metadata parameters based on surrounding points
- L99 _public prototype_ `void SetTangentType(int32 Index, ECineSplineMetadataTangentType TangentType);` — Specify tangent type on the spline point metadata

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CINECAMERARIGS_API`
- L54 _prototype_ `EInterpCurveMode ConvertCineSplineMetadataTangentTypeToInterpCurveMode(ECineSplineMetadataTangentType MetadataTangentType);` — Convert ECineSplineMetadataTangentType value to EInterpCurveMode value
- L57 _prototype_ `ECineSplineMetadataTangentType ConvertInterpCurveModeToCineSplineMetadataTangentType(EInterpCurveMode InterpCurveMode);` — Convert EInterpCurveMode value to ECineSplineMetadataTangentType value

### `Plugins/Experimental/CineCameraRigs/Source/CineCameraRigs/Public/CineSplinePointData.h` (Public)


#### struct `FCineSplinePointData`  
`struct FCineSplinePointData`  
_L12-38_
- reflection: `USTRUCT(BlueprintType)`
- desc: Simple struct to hold spline point data
- L16 _public function_ `FCineSplinePointData() : Location(FVector::ZeroVector) , Rotation(FRotator::ZeroRotator) ,FocalLength(35.0f) , Aperture(2.8f) , FocusDistance(100000.f)`
- L25 _public member_ `FVector Location;` — `UPROPERTY(BlueprintReadWrite, Category="CineSpline")`
- L28 _public member_ `FRotator Rotation;` — `UPROPERTY(BlueprintReadWrite, Category = "CineSpline")`
- L31 _public member_ `float FocalLength;` — `UPROPERTY(BlueprintReadWrite, Category = "CineSpline")`
- L34 _public member_ `float Aperture;` — `UPROPERTY(BlueprintReadWrite, Category = "CineSpline")`
- L37 _public member_ `float FocusDistance;` — `UPROPERTY(BlueprintReadWrite, Category = "CineSpline")`
