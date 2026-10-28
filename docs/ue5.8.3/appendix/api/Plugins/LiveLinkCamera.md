# Plugins / LiveLinkCamera

- module root: `Plugins/VirtualProduction/LiveLinkCamera/Source/LiveLinkCamera`
- headers: 1; symbols: 39
- symbol kinds: class=1, member=25, prototype=12, struct=1
- PrivateDependencyModuleNames: LensComponent
- PublicDependencyModuleNames: CameraCalibrationCore, CinematicCamera, Core, CoreUObject, Engine, LiveLink, LiveLinkComponents, LiveLinkInterface

### `Plugins/VirtualProduction/LiveLinkCamera/Source/LiveLinkCamera/Public/LiveLinkCameraController.h` (Public)


#### struct `FLiveLinkCameraControllerUpdateFlags`  
`struct FLiveLinkCameraControllerUpdateFlags`  
_L21-52_
- reflection: `USTRUCT()`
- desc: Flags to control whether incoming values from LiveLink Camera FrameData should be applied or not
- L27 _public member_ `bool bApplyFieldOfView = true;` — `UPROPERTY(EditAnywhere, Category = "Updates")` — Whether to apply FOV if it's available in LiveLink FrameData
- L31 _public member_ `bool bApplyAspectRatio = true;` — `UPROPERTY(EditAnywhere, Category = "Updates")` — Whether to apply Aspect Ratio if it's available in LiveLink FrameData
- L35 _public member_ `bool bApplyFocalLength = true;` — `UPROPERTY(EditAnywhere, Category = "Updates")` — Whether to apply Focal Length if it's available in LiveLink FrameData
- L39 _public member_ `bool bApplyProjectionMode= true;` — `UPROPERTY(EditAnywhere, Category = "Updates")` — Whether to apply Projection Mode if it's available in LiveLink FrameData
- L43 _public member_ `bool bApplyFilmBack = true;` — `UPROPERTY(EditAnywhere, Category = "Updates")` — Whether to apply Filmback if it's available in LiveLink StaticData or sent in the LiveLink FrameData
- L47 _public member_ `bool bApplyAperture = true;` — `UPROPERTY(EditAnywhere, Category = "Updates")` — Whether to apply Aperture if it's available in LiveLink FrameData
- L51 _public member_ `bool bApplyFocusDistance = true;` — `UPROPERTY(EditAnywhere, Category = "Updates")` — Whether to apply Focus Distance if it's available in LiveLink FrameData

#### class `ULiveLinkCameraController`  
`class ULiveLinkCameraController : public ULiveLinkControllerBase`  
_L57-178_
- reflection: `UCLASS()`
- inherits: `ULiveLinkControllerBase`
- L62 _public prototype_ `ULiveLinkCameraController();`
- L65 _public prototype_ `virtual void Tick(float DeltaTime, const FLiveLinkSubjectFrameData& SubjectData) override;`
- L66 _public prototype_ `virtual bool IsRoleSupported(const TSubclassOf<ULiveLinkRole>& RoleToSupport) override;`
- L67 _public prototype_ `virtual TSubclassOf<UActorComponent> GetDesiredComponentClass() const override;`
- L71 _public prototype_ `virtual void PostLoad() override;`
- L75 _public prototype_ `const FLensFileEvalData& GetLensFileEvalDataRef() const;` — Returns a const reference to input data used to evaluate the lens file
- L78 _public prototype_ `void SetApplyNodalOffset(bool bInApplyNodalOffset);` — `UE_DEPRECATED(5.1, "This function has been deprecated. Nodal Offset is now applied by the LensComponent")`
- L82 _protected prototype_ `void ApplyFIZ(ULensFile* LensFile, UCineCameraComponent* CineCameraComponent, const FLiveLinkCameraStaticData* StaticData, const FLiveLinkCameraFrameData* FrameData);` — Applies FIZ data coming from LiveLink stream. Lens file is used if encoder mapping is required
- L85 _protected prototype_ `void ApplyNodalOffset(ULensFile* LensFile, UCineCameraComponent* CineCameraComponent);` — `UE_DEPRECATED(5.1, "This function has been deprecated. Nodal Offset is now applied by the LensComponent")`
- L88 _protected prototype_ `void ApplyDistortion(ULensFile* LensFile, UCineCameraComponent* CineCameraComponent, const FLiveLinkCameraStaticData* StaticData, const FLiveLinkCameraFrameData* FrameData);` — `UE_DEPRECATED(5.1, "This function has been deprecated. Distortion is now applied by the LensComponent")`
- L91 _protected prototype_ `void OnPostActorTick(UWorld* World, ELevelTick TickType, float DeltaSeconds);` — `UE_DEPRECATED(5.1, "The use of this callback by this class has been deprecated and it is no longer registered. You can register your own delegate with FWorldDelegates::OnWorldPostActorTick")`
- L97 _protected prototype_ `void VerifyFIZWithLensFileTables(ULensFile* LensFile, const FLiveLinkCameraStaticData* StaticData) const;` — If part of FIZ is not streamed, verify that LensFile associated tables have only one entry Used to warn user of potential problem evaluating LensFile
- L102 _public member_ `FComponentReference ComponentToControl_DEPRECATED;` — `UPROPERTY()`
- L105 _public member_ `FLiveLinkTransformControllerData TransformData_DEPRECATED;` — `UPROPERTY()`
- L112 _public member_ `bool bUseCameraRange = false;` — `UPROPERTY(EditAnywhere, Category = "Camera Calibration")` — Should LiveLink inputs be remapped (i.e normalized to physical units) using camera component range
- L116 _public member_ `FLensFilePicker LensFilePicker;` — `UPROPERTY(EditAnywhere, Category = "Camera Calibration")` — Asset containing encoder and fiz mapping
- L121 _public member_ `bool bApplyNodalOffset_DEPRECATED = true;` — `UE_DEPRECATED(5.1, "This property has been deprecated. The LiveLink camera controller no longer applies nodal offset.")` — `UPROPERTY()`
- L125 _public member_ `bool bUseCroppedFilmback_DEPRECATED = false;` — `UE_DEPRECATED(5.1, "This property has been deprecated. Use the corresponding setting in the LensComponent instead.")` — `UPROPERTY()`
- L129 _public member_ `FCameraFilmbackSettings CroppedFilmback_DEPRECATED;` — `UE_DEPRECATED(5.1, "This property has been deprecated. Use the corresponding setting in the LensComponent instead.")` — `UPROPERTY()`
- L133 _public member_ `bool bScaleOverscan_DEPRECATED = false;` — `UE_DEPRECATED(5.1, "This property has been deprecated. Use the corresponding setting in the LensComponent instead.")` — `UPROPERTY()`
- L137 _public member_ `float OverscanMultiplier_DEPRECATED = 1.0f;` — `UE_DEPRECATED(5.1, "This property has been deprecated. Use the corresponding setting in the LensComponent instead.")` — `UPROPERTY()`
- L145 _protected member_ `FRotator OriginalCameraRotation_DEPRECATED;` — `UE_DEPRECATED(5.1, "This property has been deprecated. The LiveLink camera controller no longer applies nodal offset.")` — `UPROPERTY()`
- L149 _protected member_ `FVector OriginalCameraLocation_DEPRECATED;` — `UE_DEPRECATED(5.1, "This property has been deprecated. The LiveLink camera controller no longer applies nodal offset.")` — `UPROPERTY()`
- L153 _protected member_ `TObjectPtr<ULensDistortionModelHandlerBase> LensDistortionHandler_DEPRECATED = nullptr;` — `UE_DEPRECATED(5.1, "This property has been deprecated. The LiveLink camera controller no longer evaluated distortion.")` — `UPROPERTY(Transient)`
- L157 _protected member_ `FGuid DistortionProducerID_DEPRECATED;` — `UE_DEPRECATED(5.1, "This property has been deprecated. The LiveLink camera controller no longer evaluated distortion.")` — `UPROPERTY(DuplicateTransient)`
- L162 _protected member_ `FLiveLinkCameraControllerUpdateFlags UpdateFlags;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Used to control which data from LiveLink is actually applied to camera
- L167 _protected member_ `bool bShouldUpdateVisualComponentOnChange = true;` — `UPROPERTY(EditAnywhere, Category = "Debug")` — Whether to refresh frustum drawing on value change
- L172 _protected member_ `FLensFileEvalData LensFileEvalData;` — Caches the latest inputs to the LensFile evaluation
- L175 _private member_ `double LastLensTableVerificationTimestamp = 0.0;`
- L177 _private member_ `bool bLastIsDepthOfFieldSupported = false;`
