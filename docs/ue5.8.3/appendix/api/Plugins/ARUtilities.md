# Plugins / ARUtilities

- module root: `Plugins/Runtime/AR/ARUtilities/Source/ARUtilities`
- headers: 5; symbols: 45
- symbol kinds: class=6, enum=1, enumerator=2, function=1, member=13, prototype=21, struct=1
- PrivateDependencyModuleNames: AugmentedReality, CoreUObject, Engine, MRMesh, Slate, SlateCore
- PublicDependencyModuleNames: Core, LiveLinkAnimationCore

### `Plugins/Runtime/AR/ARUtilities/Source/ARUtilities/Public/ARLiveLinkRetargetAsset.h` (Public)


#### enum `EARLiveLinkSourceType`  
`enum class EARLiveLinkSourceType : uint8`  
_L13-17_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `None`
- L16 _public enumerator_ `ARKitPoseTracking`

#### struct `FARKitPoseTrackingConfig`  
`struct FARKitPoseTrackingConfig`  
_L21-30_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public member_ `FVector HumanForward = FVector(-1, 0, 0);` — `UPROPERTY(EditAnywhere, Category = "LiveLink|ARKit")`
- L29 _public member_ `FVector MeshForward = FVector(0, 1, 0);` — `UPROPERTY(EditAnywhere, Category = "LiveLink|ARKit")`

#### class `UARLiveLinkRetargetAsset`  
`class UARLiveLinkRetargetAsset : public ULiveLinkRetargetAsset`  
_L35-59_
- reflection: `UCLASS(Blueprintable, Abstract)`
- inherits: `ULiveLinkRetargetAsset`
- desc: Platform agnostic live link retarget asset
- L41 _public member_ `EARLiveLinkSourceType SourceType = EARLiveLinkSourceType::None;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")`
- L45 _public member_ `TMap<FName, FName> BoneMap;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")` — Mapping from AR platform bone name to UE4 skeleton bone name
- L49 _public member_ `FARKitPoseTrackingConfig ARKitPoseTrackingConfig;` — `UPROPERTY(EditAnywhere, Category = "LiveLink|ARKit", meta = (editcondition = "SourceType == EARLiveLinkSourceType::ARKitPoseTracking"))` — Configuration when using ARKit pose tracking
- L53 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L56 _public prototype_ `virtual void BuildPoseFromAnimationData(float DeltaTime, const FLiveLinkSkeletonStaticData* InSkeletonData, const FLiveLinkAnimationFrameData* InFrameData, FCompactPose& OutPose) override;`
- L58 _public prototype_ `FName GetRemappedBoneName(FName BoneName) const;`

#### class `IARLiveLinkRetargetingLogic`  
`class IARLiveLinkRetargetingLogic : public IModularFeature`  
_L63-74_
- inherits: `IModularFeature`
- desc: Interface that allows each platform to implement its own retarting logic
- L66 _public function_ `static const FName& GetModularFeatureName()`
- L72 _public prototype_ `virtual void BuildPoseFromAnimationData(const UARLiveLinkRetargetAsset& SourceAsset, float DeltaTime, const FLiveLinkSkeletonStaticData* InSkeletonData, const FLiveLinkAnimationFrameData* InFrameData, FCompactPose& OutPose) = 0;`

### `Plugins/Runtime/AR/ARUtilities/Source/ARUtilities/Public/ARPassthroughManager.h` (Public)


#### class `AARPassthroughManager`  
`class AARPassthroughManager : public AActor`  
_L18-41_
- reflection: `UCLASS(BlueprintType, ClassGroup = "AR")`
- inherits: `AActor`
- desc: A helper actor that collects the ARComponent in the scene and apply the passthrough material to them.
- L24 _public prototype_ `UPassthroughMaterialUpdateComponent* GetPassthroughMaterialUpdateComponent() const;` — `UFUNCTION(BlueprintPure, Category = "Passthrough")`
- L27 _protected prototype_ `virtual void BeginPlay() override;`
- L31 _protected member_ `TArray<TSubclassOf<UARComponent>> ARComponentClasses = { UARMeshComponent::StaticClass() };` — `UPROPERTY(EditAnywhere, Category = "Passthrough")` — What kinds of AR components should be gathered
- L34 _private prototype_ `void OnSpawnARActor(AARActor* NewARActor, UARComponent* NewARComponent, FGuid NativeID);`
- L35 _private prototype_ `void OnMRMeshCreated(UMRMeshComponent* MeshComponent);`
- L36 _private prototype_ `void OnMRMeshDestroyed(UMRMeshComponent* MeshComponent);`
- L40 _private member_ `TObjectPtr<UPassthroughMaterialUpdateComponent> PassthroughUpdateComponent;` — `UPROPERTY()`

### `Plugins/Runtime/AR/ARUtilities/Source/ARUtilities/Public/ARUtilities.h` (Public)


#### class `FARUtilitiesModule`  
`class FARUtilitiesModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/AR/ARUtilities/Source/ARUtilities/Public/ARUtilitiesFunctionLibrary.h` (Public)


#### class `UARUtilitiesFunctionLibrary`  
`class UARUtilitiesFunctionLibrary : public UBlueprintFunctionLibrary`  
_L14-47_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L20 _public prototype_ `static FVector2D GetUVOffset(const FVector2D& ViewSize, const FVector2D& TextureSize);` — Return the UV offset by trying to fit a specific texture size onto the view (cropping)
- L23 _public prototype_ `static void GetPassthroughCameraUVs(TArray<FVector2D>& OutUVs, const FVector2D& UVOffset);` — Fill out quad vertices in OutUVs using the specified UV offset
- L31 _public prototype_ `static void UpdateCameraTextureParam(UMaterialInstanceDynamic* MaterialInstance, UTexture* CameraTexture, float ColorScale = 1.f);` — `UFUNCTION(BlueprintCallable, Category = "AR Utilities")` — Update material texture parameter using pre-defined names: For regular texture: CameraTexture For external texture: ExternalCameraTexture
- L39 _public prototype_ `static void UpdateSceneDepthTexture(UMaterialInstanceDynamic* MaterialInstance, UTexture* SceneDepthTexture, float DepthToMeterScale = 1.f);` — `UFUNCTION(BlueprintCallable, Category = "AR Utilities")` — Update material texture parameter using pre-defined names: Scene depth texture: SceneDepthTexture Depth to meter scale: DepthToMeterScale
- L46 _public prototype_ `static void UpdateWorldToMeterScale(UMaterialInstanceDynamic* MaterialInstance, float WorldToMeterScale = 100.f);` — `UFUNCTION(BlueprintCallable, Category = "AR Utilities")` — Update material texture parameter using pre-defined names: World to meter scale: WorldToMeterScale

### `Plugins/Runtime/AR/ARUtilities/Source/ARUtilities/Public/PassthroughMaterialUpdateComponent.h` (Public)


#### class `UPassthroughMaterialUpdateComponent`  
`class UPassthroughMaterialUpdateComponent : public UActorComponent`  
_L19-66_
- reflection: `UCLASS(BlueprintType, ClassGroup = "AR", meta=(BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: Helper component that automatically pick the correct passthrough material to use and handles updating the camera texture in the tick.
- L24 _public prototype_ `UPassthroughMaterialUpdateComponent();`
- L26 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L30 _public prototype_ `void AddAffectedComponent(UPrimitiveComponent* InComponent);` — `UFUNCTION(BlueprintCallable, Category = "Passthrough")` — Add a component to be affected by the passthrough rendering
- L34 _public prototype_ `void RemoveAffectedComponent(UPrimitiveComponent* InComponent);` — `UFUNCTION(BlueprintCallable, Category = "Passthrough")` — Remove the component from passthrough rendering
- L38 _public prototype_ `void SetPassthroughDebugColor(FLinearColor NewDebugColor);` — `UFUNCTION(BlueprintCallable, Category = "Passthrough")` — Update the passthrough debug color
- L43 _protected member_ `EARTextureType TextureType = EARTextureType::CameraImage;` — `UPROPERTY(EditAnywhere, Category = "Passthrough")` — Which AR texture to use as the camera texture
- L47 _protected member_ `TObjectPtr<UMaterialInterface> PassthroughMaterial;` — `UPROPERTY(EditAnywhere, Category = "Passthrough")` — Which material to use for a regular camera texture
- L51 _protected member_ `TObjectPtr<UMaterialInterface> PassthroughMaterialExternalTexture;` — `UPROPERTY(EditAnywhere, Category = "Passthrough")` — Which material to use for an external camera texture
- L58 _protected member_ `FLinearColor PassthroughDebugColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, Category = "Passthrough")` — The debug color used to modulate the passthrough material. This can be used to visualize the affected meshes.
- L62 _private member_ `TArray<TObjectPtr<UPrimitiveComponent>> AffectedComponents;` — `UPROPERTY(Transient)`
- L65 _private member_ `TArray<TObjectPtr<UPrimitiveComponent>> PendingComponents;` — `UPROPERTY(Transient)`
