# Plugins / LiveLinkLens

- module root: `Plugins/VirtualProduction/LiveLinkLens/Source/LiveLinkLens`
- headers: 4; symbols: 35
- symbol kinds: class=3, member=11, prototype=18, struct=3
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, LensComponent, LiveLinkMovieScene, MovieScene, MovieSceneTracks
- PublicDependencyModuleNames: CameraCalibrationCore, CinematicCamera, LiveLinkComponents, LiveLinkInterface

### `Plugins/VirtualProduction/LiveLinkLens/Source/LiveLinkLens/Private/MovieSceneLiveLinkSubSectionLensRole.h` (Private)


#### class `UMovieSceneLiveLinkSubSectionLensRole`  
`class UMovieSceneLiveLinkSubSectionLensRole : public UMovieSceneLiveLinkSubSection`  
_L15-35_
- reflection: `UCLASS()`
- inherits: `UMovieSceneLiveLinkSubSection`
- desc: A LiveLinkSubSection managing special properties of the LensRole
- L20 _public prototype_ `virtual void Initialize(TSubclassOf<ULiveLinkRole> InSubjectRole, const TSharedPtr<FLiveLinkStaticDataStruct>& InStaticData) override;`
- L21 _public prototype_ `virtual int32 CreateChannelProxy(int32 InChannelIndex, TArray<bool>& OutChannelMask, FMovieSceneChannelProxyData& OutChannelData) override;`
- L22 _public prototype_ `virtual void RecordFrame(FFrameNumber InFrameNumber, const FLiveLinkFrameDataStruct& InFrameData) override;`
- L23 _public prototype_ `virtual void FinalizeSection(bool bReduceKeys, const FKeyDataOptimizationParams& OptimizationParams) override;`
- L26 _public prototype_ `virtual bool IsRoleSupported(const TSubclassOf<ULiveLinkRole>& RoleToSupport) const override;`
- L29 _private prototype_ `void CreatePropertiesChannel();`
- L33 _protected member_ `TSharedPtr<IMovieSceneLiveLinkPropertyHandler> PropertyHandler;` — Helper struct to manage filling channels from distortion parameter array

### `Plugins/VirtualProduction/LiveLinkLens/Source/LiveLinkLens/Public/LiveLinkLensController.h` (Public)


#### class `ULiveLinkLensController`  
`class ULiveLinkLensController : public ULiveLinkControllerBase`  
_L15-52_
- reflection: `UCLASS()`
- inherits: `ULiveLinkControllerBase`
- desc: LiveLink Controller for the LensRole to drive lens distortion data
- L21 _public prototype_ `virtual void OnEvaluateRegistered() override;`
- L22 _public prototype_ `virtual void Tick(float DeltaTime, const FLiveLinkSubjectFrameData& SubjectData) override;`
- L23 _public prototype_ `virtual bool IsRoleSupported(const TSubclassOf<ULiveLinkRole>& RoleToSupport) override;`
- L24 _public prototype_ `virtual TSubclassOf<UActorComponent> GetDesiredComponentClass() const override;`
- L25 _public prototype_ `virtual void SetAttachedComponent(UActorComponent* ActorComponent) override;`
- L26 _public prototype_ `virtual void Cleanup() override;`
- L30 _public prototype_ `virtual void PostLoad() override;`
- L38 _protected member_ `TObjectPtr<ULensDistortionModelHandlerBase> LensDistortionHandler_DEPRECATED = nullptr;` — `UE_DEPRECATED(5.1, "This property has been deprecated. Distortion is handled directly by controlled Lens Component.")` — `UPROPERTY(Transient)`
- L42 _protected member_ `FGuid DistortionProducerID_DEPRECATED;` — `UE_DEPRECATED(5.1, "This property has been deprecated and is no longer used.")` — `UPROPERTY(DuplicateTransient)`
- L46 _protected member_ `bool bScaleOverscan_DEPRECATED = false;` — `UE_DEPRECATED(5.1, "This property has been deprecated. Overscan multipliers should now be applied from a Lens Component.")` — `UPROPERTY()`
- L50 _protected member_ `float OverscanMultiplier_DEPRECATED = 1.0f;` — `UE_DEPRECATED(5.1, "This property has been deprecated. Overscan multipliers should now be applied from a Lens Component.")` — `UPROPERTY()`

### `Plugins/VirtualProduction/LiveLinkLens/Source/LiveLinkLens/Public/LiveLinkLensRole.h` (Public)


#### class `ULiveLinkLensRole`  
`class ULiveLinkLensRole : public ULiveLinkCameraRole`  
_L13-27_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "Lens Role"))`
- inherits: `ULiveLinkCameraRole`
- desc: Role associated with lens data
- L19 _public prototype_ `virtual UScriptStruct* GetStaticDataStruct() const override;`
- L20 _public prototype_ `virtual UScriptStruct* GetFrameDataStruct() const override;`
- L21 _public prototype_ `virtual UScriptStruct* GetBlueprintDataStruct() const override;`
- L23 _public prototype_ `virtual bool InitializeBlueprintData(const FLiveLinkSubjectFrameData& InSourceData, FLiveLinkBlueprintDataStruct& OutBlueprintData) const override;`
- L25 _public prototype_ `virtual FText GetDisplayName() const override;`

### `Plugins/VirtualProduction/LiveLinkLens/Source/LiveLinkLens/Public/LiveLinkLensTypes.h` (Public)


#### struct `FLiveLinkLensStaticData`  
`struct FLiveLinkLensStaticData : public FLiveLinkCameraStaticData`  
_L16-23_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkCameraStaticData`
- desc: Struct for static lens data
- L22 _public member_ `FName LensModel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Specifies the type/character of the lens (spherical, anamorphic, etc.)

#### struct `FLiveLinkLensFrameData`  
`struct FLiveLinkLensFrameData : public FLiveLinkCameraFrameData`  
_L29-44_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkCameraFrameData`
- desc: Struct for dynamic (per-frame) lens data
- L35 _public member_ `TArray<float> DistortionParameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — Parameters used by the distortion model
- L39 _public member_ `FVector2D FxFy = FVector2D(1.0f, (16.0f / 9.0f));` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — Normalized focal length used by the distortion model
- L43 _public member_ `FVector2D PrincipalPoint = FVector2D(0.5f, 0.5f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp, meta = (DisplayName = "Image Center"))` — Normalized center of the image, in the range [0.0f, 1.0f]

#### struct `FLiveLinkLensBlueprintData`  
`struct FLiveLinkLensBlueprintData : public FLiveLinkBaseBlueprintData`  
_L50-61_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseBlueprintData`
- desc: Facility structure to handle lens data in blueprint
- L56 _public member_ `FLiveLinkLensStaticData StaticData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Static data that should not change every frame
- L60 _public member_ `FLiveLinkLensFrameData FrameData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Dynamic data that can change every frame
