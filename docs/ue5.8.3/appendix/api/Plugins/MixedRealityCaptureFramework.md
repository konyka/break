# Plugins / MixedRealityCaptureFramework

- module root: `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework`
- headers: 11; symbols: 229
- symbol kinds: class=18, delegate=3, function=5, member=85, prototype=111, struct=7
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, HeadMountedDisplay, InputCore, Media, MediaUtils, OpenCVHelper, OpenCVLensDistortion, RenderCore, UnrealEd, XRBase
- PublicDependencyModuleNames: MediaAssets

### `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Private/MrcFrameworkSettings.h` (Private)


#### class `UMrcFrameworkSettings`  
`class UMrcFrameworkSettings : public UObject`  
_L8-33_
- reflection: `UCLASS(config=Engine)`
- inherits: `UObject`
- L14 _public member_ `FSoftObjectPath DefaulVideoSource;` — `UPROPERTY(Config)`
- L17 _public member_ `FSoftObjectPath DefaultVideoProcessingMat;` — `UPROPERTY(Config)`
- L20 _public member_ `FSoftObjectPath DefaultRenderTarget;` — `UPROPERTY(Config)`
- L23 _public member_ `FSoftObjectPath DefaultDistortionDisplacementMap;` — `UPROPERTY(Config)`
- L26 _public member_ `FSoftObjectPath DefaulGarbageMatteMesh;` — `UPROPERTY(Config)`
- L29 _public member_ `FSoftObjectPath DefaulGarbageMatteMaterial;` — `UPROPERTY(Config)`
- L32 _public member_ `FSoftObjectPath DefaulGarbageMatteTarget;` — `UPROPERTY(Config)`

### `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Private/MrcLatencyViewExtension.h` (Private)


#### class `FMrcLatencyViewExtension`  
`class FMrcLatencyViewExtension : public FMotionDelayClient`  
_L14-37_
- inherits: `FMotionDelayClient`
- L17 _public prototype_ `FMrcLatencyViewExtension(const FAutoRegister& AutoRegister, UMixedRealityCaptureComponent* Owner);`
- L18 _public function_ `virtual ~FMrcLatencyViewExtension()`
- L20 _public prototype_ `bool SetupPreCapture(FSceneInterface* Scene);`
- L21 _public prototype_ `void SetupPostCapture(FSceneInterface* Scene);`
- L25 _public prototype_ `virtual uint32 GetDesiredDelay() const override;` — FMotionDelayClient interface
- L26 _public prototype_ `virtual void GetExemptTargets(TArray<USceneComponent*>& ExemptTargets) const override;`
- L30 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;` — ISceneViewExtension interface
- L31 _public prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;`
- L34 _private member_ `TWeakObjectPtr<UMixedRealityCaptureComponent> Owner;`
- L35 _private member_ `uint32 CachedRenderDelay = 0;`
- L36 _private member_ `FTransform CachedOwnerTransform;`

### `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Private/MrcProjectionBillboard.h` (Private)


#### class `UMixedRealityCaptureBillboard`  
`class UMixedRealityCaptureBillboard : public UMaterialBillboardComponent`  
_L12-36_
- reflection: `UCLASS()`
- inherits: `UMaterialBillboardComponent`
- L18 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L23 _public function_ `virtual uint64 GetHiddenEditorViews() const override`
- L32 _public member_ `float DepthOffset = 0.0f;`
- L35 _public prototype_ `void EnableHMDDepthTracking(bool bEnable = true);`

#### class `AMrcProjectionActor`  
`class AMrcProjectionActor : public AActor`  
_L42-61_
- reflection: `UCLASS(notplaceable)`
- inherits: `AActor`
- L47 _private member_ `TObjectPtr<UMixedRealityCaptureBillboard> ProjectionComponent;` — `UPROPERTY()`
- L51 _public prototype_ `virtual void BeginPlay() override;`
- L52 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L55 _public prototype_ `void SetProjectionMaterial(UMaterialInterface* VidProcessingMat);`
- L56 _public prototype_ `void SetProjectionAspectRatio(const float NewAspectRatio);`
- L60 _private member_ `TWeakObjectPtr<USceneComponent> AttachTarget;` — `UPROPERTY(Transient)`

### `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Public/IMrcFocalDriver.h` (Public)


#### class `UMrcFocalDriver`  
`class UMrcFocalDriver : public UInterface`  
_L12-16_
- reflection: `UINTERFACE(Category="MixedRealityCapture", Blueprintable, meta=(DisplayName = "Focal Driver"))`
- inherits: `UInterface`

#### class `IMrcFocalDriver`  
`class IMrcFocalDriver`  
_L19-29_
- desc: Interface that should be implemented to provide focal information such as field of view.
- L28 _public prototype_ `float GetHorizontalFieldOfView() const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MixedRealityCapture", DisplayName = "GetHorizontalFieldOfView", meta = (CallInEditor = "true"))` — Get the horizontal field of view of this provider.

### `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Public/IMrcFrameworkModule.h` (Public)


#### class `IMrcFrameworkModule`  
`class IMrcFrameworkModule : public IModuleInterface`  
_L14-21_
- inherits: `IModuleInterface`
- L18 _public function_ `virtual ~IMrcFrameworkModule()` — Virtual destructor.
- L20 _public function_ `virtual class AMixedRealityCaptureActor* GetMixedRealityCaptureActor()`

### `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Public/MixedRealityCaptureActor.h` (Public)


#### class `AMixedRealityCaptureActor`  
`class AMixedRealityCaptureActor : public AActor`  
_L19-88_
- reflection: `UCLASS(Blueprintable, config=Engine)`
- inherits: `AActor`
- L25 _public member_ `TObjectPtr<UMixedRealityCaptureComponent> CaptureComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=MixedRealityCapture, meta=(AllowPrivateAccess="true"))`
- L28 _public member_ `bool bAutoAttachToVRPlayer;` — `UPROPERTY(EditAnywhere, config, BlueprintReadOnly, Category=Tracking)`
- L31 _public member_ `bool bAutoHidePlayer;` — `UPROPERTY(EditAnywhere, config, BlueprintReadOnly, Category=SceneCapture)`
- L34 _public member_ `bool bHideAttachmentsWithPlayer;` — `UPROPERTY(EditAnywhere, config, BlueprintReadOnly, Category=SceneCapture, meta=(editcondition="bAutoHidePlayer"))`
- L38 _public member_ `bool bAutoBroadcast;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, BlueprintSetter=SetAutoBroadcast, Category=SceneCapture)` — If true the capture texture will automatically be applied to the Spectator Screen.
- L44 _public prototype_ `void SetAutoBroadcast(const bool bNewValue);` — `UFUNCTION(BlueprintSetter)`
- L47 _public prototype_ `bool IsBroadcasting();` — `UFUNCTION(BlueprintPure, Category = SceneCapture)`
- L50 _public prototype_ `UTexture* GetCaptureTexture();` — `UFUNCTION(BlueprintPure, Category = SceneCapture)`
- L53 _public prototype_ `bool SetTargetPlayer(APawn* PlayerPawn, USceneComponent* TrackingOrigin);`
- L58 _public prototype_ `virtual void BeginPlay() override;`
- L59 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L63 _private prototype_ `void OnTargetDestroyed(AActor* DestroyedActor);` — `UFUNCTION()`
- L66 _private member_ `TWeakObjectPtr<APawn> TargetPlayer;`
- L67 _private member_ `TSharedPtr<FMRCaptureAutoTargeter> AutoTargeter;`
- L84 _private member_ `FCastingModeRestore BroadcastManager;`
- L87 _private member_ `TObjectPtr<UStaticMesh> DebugVisualizerMesh;` — `UPROPERTY(Transient)`

#### struct `AMixedRealityCaptureActor::FCastingModeRestore`  
`struct FCastingModeRestore`  
_L70-83_
- desc: @TODO: The SpectatorScreenController really should expose setting screen modes as a stack w/ a push/pop interface
- L73 _public prototype_ `FCastingModeRestore();`
- L75 _public prototype_ `bool BeginCasting(UTexture* DisplayTexture);`
- L76 _public function_ `bool IsCasting() const`
- L77 _public prototype_ `void EndCasting();`
- L80 _private member_ `UTexture* RestoreTexture;`
- L81 _private member_ `ESpectatorScreenMode RestoreMode;`
- L82 _private member_ `bool bIsCasting;`

### `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Public/MixedRealityCaptureComponent.h` (Public)


#### class `UMixedRealityCaptureComponent`  
`class UMixedRealityCaptureComponent : public USceneCaptureComponent2D`  
_L35-260_
- reflection: `UCLASS(ClassGroup = Rendering, editinlinenew, Blueprintable, BlueprintType, config = Engine, meta = (BlueprintSpawnableComponent))`
- inherits: `USceneCaptureComponent2D`
- L41 _public member_ `TObjectPtr<UMediaPlayer> MediaSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=VideoCapture)`
- L44 _public member_ `TObjectPtr<UMaterialInterface> VideoProcessingMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetVidProjectionMat, Category=Composition)`
- L47 _public member_ `FMrcVideoProcessingParams VideoProcessingParams;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetVidProcessingParams, Category=Composition)`
- L50 _public member_ `FMrcVideoCaptureFeedIndex CaptureFeedRef;` — `UPROPERTY(BlueprintReadWrite, BlueprintSetter=SetCaptureDevice, Category=Composition)`
- L53 _public member_ `FOpenCVLensDistortionParameters LensDistortionParameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetLensDistortionParameters, Category=VideoCapture)`
- L56 _public member_ `FName TrackingSourceName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Tracking)`
- L59 _public member_ `TObjectPtr<UTextureRenderTarget2D> GarbageMatteCaptureTextureTarget;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Composition)`
- L63 _public member_ `int32 TrackingLatency;` — `UPROPERTY(BlueprintReadWrite, Config, BlueprintGetter=GetTrackingDelay, BlueprintSetter=SetTrackingDelay, Category=Composition, meta=(ClampMin="0", UIMin="0"))` — Millisecond delay to apply to motion controller components when rendering to the capture view (to better align with latent camera feeds)
- L67 _public member_ `bool bAutoLoadConfiguration;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Config, Category=Calibration)` — Determines if this component should attempt to load the default MR calibration file on initialization
- L71 _public member_ `float ProjectionDepthOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, BlueprintSetter=SetProjectionDepthOffset, Category=Composition)` — Depth offset (in UE units) for the card that the camera feed is projected onto. By default the card is aligned with the HMD.
- L75 _public member_ `bool bProjectionDepthTracking;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, BlueprintSetter=SetEnableProjectionDepthTracking, Category=Tracking)` — Enabled by default, the projection plane tracks with the HMD to simulate the depth of the player. Disable to keep the projection plane from moving.
- L80 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L85 _public prototype_ `virtual void OnRegister() override;`
- L86 _public prototype_ `virtual void Activate(bool bReset = false) override;`
- L87 _public prototype_ `virtual void Deactivate() override;`
- L88 _public prototype_ `virtual void InitializeComponent() override;`
- L89 _public prototype_ `virtual void OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport) override;`
- L90 _public prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L96 _public prototype_ `virtual bool GetEditorPreviewInfo(float DeltaTime, FMinimalViewInfo& ViewOut) override;`
- L102 _public prototype_ `virtual const AActor* GetViewOwner() const override;`
- L103 _public prototype_ `virtual void UpdateSceneCaptureContents(FSceneInterface* Scene, ISceneRenderBuilder& SceneRenderBuilder) override;`
- L109 _public prototype_ `bool SaveAsDefaultConfiguration_K2();` — `UFUNCTION(BlueprintCallable, Category = "MixedRealityCapture|Calibration", meta = (DisplayName = "SaveAsDefaultConfiguration"))` — non-const to make it an exec node
- L110 _public prototype_ `bool SaveAsDefaultConfiguration() const;`
- L113 _public prototype_ `bool SaveConfiguration_K2(const FString& SlotName, int32 UserIndex);` — `UFUNCTION(BlueprintCallable, Category = "MixedRealityCapture|Calibration", meta = (DisplayName="SaveConfiguration"))` — non-const to make it an exec node
- L114 _public prototype_ `bool SaveConfiguration(const FString& SlotName, int32 UserIndex) const;`
- L117 _public prototype_ `bool LoadDefaultConfiguration();` — `UFUNCTION(BlueprintCallable, Category = "MixedRealityCapture|Calibration")`
- L120 _public prototype_ `bool LoadConfiguration(const FString& SlotName, int32 UserIndex);` — `UFUNCTION(BlueprintCallable, Category = "MixedRealityCapture|Calibration")`
- L123 _public prototype_ `UMrcCalibrationData* ConstructCalibrationData() const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MixedRealityCapture|Calibration")`
- L126 _public prototype_ `void FillOutCalibrationData(UMrcCalibrationData* Dst) const;` — `UFUNCTION(BlueprintCallable, Category = "MixedRealityCapture|Calibration")`
- L129 _public prototype_ `void ApplyCalibrationData(UMrcCalibrationData* ConfigData);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MixedRealityCapture|Calibration")`
- L137 _public prototype_ `bool SetGarbageMatteActor(AMrcGarbageMatteActor* Actor);` — `UFUNCTION(BlueprintCallable, Category = "MixedRealityCapture|GarbageMatting")` — Set an external garbage matte actor to be used instead of the mixed reality component's normal configuration save game based actor.  This is used during garbage matte setup to preview the garbage mask in realtime.
- L140 _public prototype_ `void SetVidProjectionMat(UMaterialInterface* NewMaterial);` — `UFUNCTION(BlueprintSetter)`
- L143 _public prototype_ `void SetVidProcessingParams(const FMrcVideoProcessingParams& NewVidProcessingParams);` — `UFUNCTION(BlueprintSetter)`
- L146 _public prototype_ `void SetDeviceAttachment(FName SourceName);` — `UFUNCTION(BlueprintCallable, Category = "MixedRealityCapture|Tracking")`
- L149 _public prototype_ `void DetatchFromDevice();` — `UFUNCTION(BlueprintCallable, Category = "MixedRealityCapture|Tracking")`
- L152 _public prototype_ `bool IsTracked() const;` — `UFUNCTION(BlueprintCallable, Category = "MixedRealityCapture|Tracking")`
- L155 _public prototype_ `void SetCaptureDevice(const FMrcVideoCaptureFeedIndex& FeedRef);` — `UFUNCTION(BlueprintSetter)`
- L158 _public prototype_ `void SetLensDistortionParameters(const FOpenCVLensDistortionParameters& ModelRef);` — `UFUNCTION(BlueprintSetter)`
- L161 _public prototype_ `int32 GetTrackingDelay() const;` — `UFUNCTION(BlueprintGetter)`
- L164 _public prototype_ `void SetTrackingDelay(int32 DelayMS);` — `UFUNCTION(BlueprintSetter)`
- L167 _public prototype_ `void SetProjectionDepthOffset(float DepthOffset);` — `UFUNCTION(BlueprintSetter)`
- L170 _public prototype_ `AActor* GetProjectionActor_K2() const;` — `UFUNCTION(BlueprintPure, Category = "MixedRealityCapture|Projection", meta=(DisplayName="GetProjectionActor"))`
- L171 _public prototype_ `AMrcProjectionActor* GetProjectionActor() const;`
- L173 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMRCaptureFeedOpenedDelegate, const FMrcVideoCaptureFeedIndex&, FeedRef);`
- L175 _public member_ `FMRCaptureFeedOpenedDelegate OnCaptureSourceOpened;` — `UPROPERTY(BlueprintAssignable, Category = VideoCapture)`
- L182 _public prototype_ `void SetEnableProjectionDepthTracking(bool bEnable = true);` — `UFUNCTION(BlueprintSetter)` — Enabled by default, the projection plane tracks with the HMD to simulate the depth of the player. Disable to keep the projection plane from moving.
- L188 _public prototype_ `void RefreshCameraFeed();`
- L193 _public prototype_ `void RefreshDevicePairing();`
- L198 _public prototype_ `void RefreshTrackingOriginOffset();`
- L203 _private prototype_ `void OnVideoFeedOpened(const FMrcVideoCaptureFeedIndex& FeedRef);` — `UFUNCTION()`
- L208 _private prototype_ `void RefreshProjectionDimensions();`
- L213 _private prototype_ `float GetDesiredAspectRatio() const;`
- L218 _private prototype_ `void RefreshDistortionDisplacementMap();`
- L223 _private prototype_ `void RefreshFOV();`
- L228 _private prototype_ `void OnTrackingOriginChanged(const IXRTrackingSystem* TrackingSys);`
- L233 _private member_ `TObjectPtr<UStaticMesh> ProxyMesh;` — `UPROPERTY(Transient)`
- L236 _private member_ `TObjectPtr<UStaticMeshComponent> ProxyMeshComponent;` — `UPROPERTY(Transient)`
- L240 _private member_ `TObjectPtr<UChildActorComponent> ProjectionActor;` — `UPROPERTY(Transient)`
- L243 _private member_ `TObjectPtr<UMotionControllerComponent> PairedTracker;` — `UPROPERTY(Transient)`
- L246 _private member_ `TObjectPtr<USceneComponent> TrackingOriginOffset;` — `UPROPERTY(Transient)`
- L248 _private member_ `EHMDTrackingOrigin::Type RelativeOriginType;`
- L251 _private member_ `TObjectPtr<UMrcGarbageMatteCaptureComponent> GarbageMatteCaptureComponent;` — `UPROPERTY(Transient)`
- L254 _private member_ `TObjectPtr<UTexture2D> DistortionDisplacementMap;` — `UPROPERTY(Transient)`
- L256 _private member_ `float CalibratedFOV;`
- L257 _private member_ `FOpenCVCameraViewInfo UndistortedCameraInfo;`
- L259 _private member_ `TSharedPtr<FMrcLatencyViewExtension, ESPMode::ThreadSafe> ViewExtension;`

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMixedRealityCapture, Log, All);`
- L29 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMixedRealityCapture, Log, All);`
- L173 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMRCaptureFeedOpenedDelegate, const FMrcVideoCaptureFeedIndex&, FeedRef);`

### `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Public/MrcCalibrationData.h` (Public)


#### struct `FMrcLensCalibrationData`  
`struct FMrcLensCalibrationData`  
_L16-25_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public member_ `float FOV = 90.f;` — `UPROPERTY(BlueprintReadWrite, Category = Data)`
- L24 _public member_ `FOpenCVLensDistortionParameters DistortionParameters;` — `UPROPERTY(BlueprintReadWrite, Category = Data)`

#### struct `FMrcAlignmentSaveData`  
`struct FMrcAlignmentSaveData`  
_L28-43_
- reflection: `USTRUCT(BlueprintType)`
- L33 _public member_ `FVector CameraOrigin = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, Category = Data)`
- L36 _public member_ `FRotator Orientation = FRotator::ZeroRotator;` — `UPROPERTY(BlueprintReadWrite, Category = Data)`
- L39 _public member_ `FName TrackingAttachmentId;` — `UPROPERTY(BlueprintReadWrite, Category = Data)`
- L42 _public member_ `TEnumAsByte<EHMDTrackingOrigin::Type> TrackingOrigin;` — `UPROPERTY(BlueprintReadWrite, Category = Data)`

#### struct `FMrcGarbageMatteSaveData`  
`struct FMrcGarbageMatteSaveData`  
_L46-52_
- reflection: `USTRUCT(BlueprintType)`
- L51 _public member_ `FTransform Transform;` — `UPROPERTY(BlueprintReadWrite, Category = Data)`

#### struct `FMrcVideoProcessingParams`  
`struct FMrcVideoProcessingParams`  
_L55-64_
- reflection: `USTRUCT(BlueprintType)`
- L60 _public member_ `TMap<FName, float> MaterialScalarParams;` — `UPROPERTY(BlueprintReadWrite, Category = Data)`
- L63 _public member_ `TMap<FName, FLinearColor> MaterialVectorParams;` — `UPROPERTY(BlueprintReadWrite, Category = Data)`

#### struct `FMrcCompositingSaveData`  
`struct FMrcCompositingSaveData`  
_L67-82_
- reflection: `USTRUCT(BlueprintType)`
- L72 _public member_ `FMrcVideoCaptureFeedIndex CaptureDeviceURL;` — `UPROPERTY(BlueprintReadWrite, Category = Data)`
- L75 _public member_ `float DepthOffset = 0.0f;` — `UPROPERTY(BlueprintReadWrite, Category = Data)`
- L78 _public member_ `int32 TrackingLatency = 0;` — `UPROPERTY(BlueprintReadWrite, Category = Data)`
- L81 _public member_ `FMrcVideoProcessingParams VideoProcessingParams;` — `UPROPERTY(BlueprintReadWrite, Category = Data)`

#### class `UMrcCalibrationData`  
`class UMrcCalibrationData : public USaveGame`  
_L85-101_
- reflection: `UCLASS(BlueprintType, Blueprintable, config = Engine)`
- inherits: `USaveGame`
- L91 _public member_ `FMrcLensCalibrationData LensData;` — `UPROPERTY(BlueprintReadWrite, Category = SaveData)`
- L94 _public member_ `FMrcAlignmentSaveData AlignmentData;` — `UPROPERTY(BlueprintReadWrite, Category = SaveData)`
- L97 _public member_ `TArray<FMrcGarbageMatteSaveData> GarbageMatteSaveDatas;` — `UPROPERTY(BlueprintReadWrite, Category = SaveData)`
- L100 _public member_ `FMrcCompositingSaveData CompositingData;` — `UPROPERTY(BlueprintReadWrite, Category = SaveData)`

#### class `UMrcCalibrationSaveGame`  
`class UMrcCalibrationSaveGame : public UMrcCalibrationData`  
_L107-122_
- reflection: `UCLASS(BlueprintType, config = Engine)`
- inherits: `UMrcCalibrationData`
- L115 _public member_ `FString SaveSlotName;` — `UPROPERTY(BlueprintReadWrite, config, Category = SaveMetadata)`
- L118 _public member_ `int32 UserIndex;` — `UPROPERTY(BlueprintReadWrite, config, Category = SaveMetadata)`
- L121 _public member_ `int32 ConfigurationSaveVersion;` — `UPROPERTY(BlueprintReadOnly, Category = SaveMetadata)`

### `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Public/MrcGarbageMatteCaptureComponent.h` (Public)


#### class `UMrcGarbageMatteCaptureComponent`  
`class UMrcGarbageMatteCaptureComponent : public USceneCaptureComponent2D`  
_L18-70_
- reflection: `UCLASS(ClassGroup = Rendering, editinlinenew, config = Engine, meta=(BlueprintSpawnableComponent))`
- inherits: `USceneCaptureComponent2D`
- L24 _public prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L25 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L29 _public prototype_ `virtual const AActor* GetViewOwner() const override;`
- L33 _public prototype_ `void SetTrackingOrigin(USceneComponent* TrackingOrigin);` — `UFUNCTION()`
- L36 _public prototype_ `void ApplyCalibrationData(const UMrcCalibrationData* ConfigData);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MixedRealityCapture|GarbageMatting")`
- L39 _public prototype_ `void SetGarbageMatteActor(AMrcGarbageMatteActor* NewActor);` — `UFUNCTION(BlueprintCallable, Category = "MixedRealityCapture|GarbageMatting")`
- L42 _public prototype_ `void GetGarbageMatteData(TArray<FMrcGarbageMatteSaveData>& GarbageMatteDataOut);` — `UFUNCTION(BlueprintCallable, Category = "MixedRealityCapture|GarbageMatting")`
- L45 _public prototype_ `void SetFocalDriver(TScriptInterface<IMrcFocalDriver> InFocalDriver);` — `UFUNCTION(BlueprintCallable, Category = "MixedRealityCapture|GarbageMatting")`
- L48 _public prototype_ `AMrcGarbageMatteActor* SpawnNewGarbageMatteActor(USceneComponent* TrackingOrigin);` — `UFUNCTION(BlueprintNativeEvent, Category = "MixedRealityCapture|GarbageMatting")`
- L51 _private prototype_ `void CleanupSpawnedActors();`
- L53 _private prototype_ `void PollFocalDriver();`
- L57 _private member_ `TSubclassOf<AMrcGarbageMatteActor> GarbageMatteActorClass;` — `UPROPERTY(Transient, Config)`
- L60 _private member_ `TObjectPtr<AMrcGarbageMatteActor> GarbageMatteActor;` — `UPROPERTY(Transient)`
- L63 _private member_ `TArray<TObjectPtr<AMrcGarbageMatteActor>> SpawnedActors;` — `UPROPERTY(Transient)`
- L66 _private member_ `TWeakObjectPtr<USceneComponent> TrackingOriginPtr;` — `UPROPERTY(Transient)`
- L69 _private member_ `TScriptInterface<IMrcFocalDriver> FocalDriver;` — `UPROPERTY(Transient)`

#### class `AMrcGarbageMatteActor`  
`class AMrcGarbageMatteActor : public AActor`  
_L79-106_
- reflection: `UCLASS(Blueprintable)`
- inherits: `AActor`
- L86 _public prototype_ `void ApplyCalibrationData(const TArray<FMrcGarbageMatteSaveData>& GarbageMatteData);` — `UFUNCTION(BlueprintCallable, Category = "MixedRealityCapture|GarbageMatting")`
- L89 _public prototype_ `UPrimitiveComponent* AddNewGabageMatte(const FMrcGarbageMatteSaveData& GarbageMatteData);` — `UFUNCTION(BlueprintCallable, Category = "MixedRealityCapture|GarbageMatting")`
- L92 _public prototype_ `UPrimitiveComponent* CreateGarbageMatte(const FMrcGarbageMatteSaveData& GarbageMatteData);` — `UFUNCTION(BlueprintNativeEvent, Category = "MixedRealityCapture|GarbageMatting")`
- L95 _public prototype_ `void GetGarbageMatteData(TArray<FMrcGarbageMatteSaveData>& GarbageMatteDataOut);` — `UFUNCTION(BlueprintCallable, Category = "MixedRealityCapture|GarbageMatting")`
- L99 _private member_ `TObjectPtr<UStaticMesh> GarbageMatteMesh;` — `UPROPERTY(Transient)`
- L102 _private member_ `TObjectPtr<UMaterial> GarbageMatteMaterial;` — `UPROPERTY(Transient)`
- L105 _private member_ `TArray<TObjectPtr<UPrimitiveComponent>> GarbageMattes;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "MixedRealityCapture|GarbageMatting", meta=(AllowPrivateAccess="true"))`

### `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Public/MrcUtilLibrary.h` (Public)


#### class `UMrcUtilLibrary`  
`class UMrcUtilLibrary : public UBlueprintFunctionLibrary`  
_L16-47_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L25 _public prototype_ `static bool IsMixedRealityCaptureBroadcasting();` — `UFUNCTION(BlueprintPure, Category = "MixedRealityCapture|Utils")` — Return true if the system is sending the capture texture to the spectator screen.
- L31 _public prototype_ `static void SetMixedRealityCaptureBroadcasting(bool bEnable);` — `UFUNCTION(BlueprintCallable, Category = "MixedRealityCapture|Utils")` — Toggle whether the capture system is sending the capture texture to the spectator screen or not.
- L37 _public prototype_ `static UTexture* GetMixedRealityCaptureTexture();` — `UFUNCTION(BlueprintPure, Category = "MixedRealityCapture|Utils")` — Return the Capture Texture, or nullptr if there isn't one.
- L40 _public prototype_ `static USceneComponent* FindAssociatedHMDRoot(AActor* ActorInst);`
- L41 _public prototype_ `static USceneComponent* GetHMDRootComponent(const APawn* PlayerPawn);`
- L44 _private prototype_ `static APawn* FindAssociatedPlayerPawn(AActor* ActorInst);`
- L45 _private prototype_ `static UCameraComponent* GetHMDCameraComponent(const APawn* PlayerPawn);`
- L46 _private prototype_ `static USceneComponent* GetHMDRootComponent(const UObject* WorldContextObject, int32 PlayerIndex);`

### `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Public/MrcVideoCaptureDevice.h` (Public)


#### struct `FMrcVideoCaptureFeedIndex`  
`struct FMrcVideoCaptureFeedIndex`  
_L17-38_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public prototype_ `FMrcVideoCaptureFeedIndex();`
- L23 _public prototype_ `FMrcVideoCaptureFeedIndex(UMediaPlayer* MediaPlayer);`
- L24 _public prototype_ `FMrcVideoCaptureFeedIndex(FMediaCaptureDeviceInfo& DeviceInfo);`
- L27 _public member_ `FString DeviceURL;` — `UPROPERTY(BlueprintReadWrite, Category="MixedRealityCapture|CaptureDevice")`
- L29 _public member_ `int32 StreamIndex;` — `UPROPERTY(BlueprintReadWrite, Category="MixedRealityCapture|CaptureDevice")`
- L31 _public member_ `int32 FormatIndex;` — `UPROPERTY(BlueprintReadWrite, Category="MixedRealityCapture|CaptureDevice")`
- L33 _public prototype_ `bool IsSet(UMediaPlayer* MediaPlayer) const;`
- L34 _public prototype_ `bool IsDeviceUrlValid() const;`
- L36 _public prototype_ `bool operator==(const FMrcVideoCaptureFeedIndex& Rhs) const;`
- L37 _public prototype_ `bool operator!=(const FMrcVideoCaptureFeedIndex& Rhs) const;`

#### class `FMrcVideoCaptureUtils`  
`class FMrcVideoCaptureUtils`  
_L43-52_
- L46 _public prototype_ `static TArray<FMrcVideoCaptureFeedIndex> EnumerateAvailableFeeds(UMediaPlayer* MediaPlayer);`
- L48 _public prototype_ `static bool FeedSortPredicate(UMediaPlayer* MediaPlayer, const FMrcVideoCaptureFeedIndex& Rhs, const FMrcVideoCaptureFeedIndex& Lhs, const float PrioritizedAspectRatio = 16/9.f, const int32 PrioritizedResolution = 1080, const FString& PreferedFormat = FString());`

#### class `UAsyncTask_OpenMrcVidCaptureFeedBase`  
`class UAsyncTask_OpenMrcVidCaptureFeedBase : public UBlueprintAsyncActionBase`  
_L61-93_
- reflection: `UCLASS(Abstract)`
- inherits: `UBlueprintAsyncActionBase`
- L67 _public member_ `FMRCaptureFeedDelegate OnSuccess;` — `UPROPERTY(BlueprintAssignable)`
- L70 _public member_ `FMRCaptureFeedDelegate OnFail;` — `UPROPERTY(BlueprintAssignable)`
- L73 _public prototype_ `void Open(UMediaPlayer* Target, const FString& DeviceURL);`
- L77 _protected prototype_ `virtual void OnVideoFeedOpened(FString DeviceUrl);` — `UFUNCTION()`
- L80 _protected prototype_ `virtual void OnVideoFeedOpenFailure(FString DeviceUrl);` — `UFUNCTION()`
- L82 _protected prototype_ `bool SetTrackFormat(const int32 StreamIndex, const int32 FormatIndex);`
- L83 _protected prototype_ `void CleanUp();`
- L86 _protected member_ `TObjectPtr<UMediaPlayer> MediaPlayer;` — `UPROPERTY()`
- L90 _private member_ `bool bCachedPlayOnOpenVal;`
- L92 _private member_ `TWeakPtr<FLatentPlayMrcCaptureFeedAction> LatentPlayer;`

#### class `UAsyncTask_OpenMrcVidCaptureDevice`  
`class UAsyncTask_OpenMrcVidCaptureDevice : public UAsyncTask_OpenMrcVidCaptureFeedBase`  
_L99-108_
- reflection: `UCLASS()`
- inherits: `UAsyncTask_OpenMrcVidCaptureFeedBase`
- L104 _public prototype_ `static UAsyncTask_OpenMrcVidCaptureDevice* OpenMrcVideoCaptureDevice(const FMediaCaptureDeviceInfo& DeviceId, UMediaPlayer* Target, FMRCaptureFeedDelegate::FDelegate OpenedCallback);`
- L107 _private prototype_ `virtual void OnVideoFeedOpened(FString DeviceUrl) override;`

#### class `UAsyncTask_OpenMrcVidCaptureFeed`  
`class UAsyncTask_OpenMrcVidCaptureFeed : public UAsyncTask_OpenMrcVidCaptureFeedBase`  
_L114-128_
- reflection: `UCLASS()`
- inherits: `UAsyncTask_OpenMrcVidCaptureFeedBase`
- L119 _public prototype_ `static UAsyncTask_OpenMrcVidCaptureFeed* OpenMrcVideoCaptureFeed(const FMrcVideoCaptureFeedIndex& FeedRef, UMediaPlayer* Target, FMRCaptureFeedDelegate::FDelegate OpenedCallback);`
- L122 _protected prototype_ `void Open(const FMrcVideoCaptureFeedIndex& FeedRef, UMediaPlayer* Target);`
- L125 _private prototype_ `virtual void OnVideoFeedOpened(FString DeviceUrl) override;`
- L127 _private member_ `FMrcVideoCaptureFeedIndex DesiredFeedRef;`

#### Free symbols / members of external scopes

- L58 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMRCaptureFeedDelegate, const FMrcVideoCaptureFeedIndex&, FeedRef);`
- L58 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMRCaptureFeedDelegate, const FMrcVideoCaptureFeedIndex&, FeedRef);`
