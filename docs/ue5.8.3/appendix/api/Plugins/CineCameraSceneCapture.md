# Plugins / CineCameraSceneCapture

- module root: `Plugins/Experimental/CineCameraSceneCapture/Source/CineCameraSceneCapture`
- headers: 2; symbols: 20
- symbol kinds: class=2, delegate=1, member=7, prototype=10
- PrivateDependencyModuleNames: CinematicCamera, Core, CoreUObject, Engine, RenderCore, Renderer, Slate, SlateCore
- PublicDependencyModuleNames: OpenColorIO

### `Plugins/Experimental/CineCameraSceneCapture/Source/CineCameraSceneCapture/Public/CineCameraSceneCapture.h` (Public)


#### class `FCineCameraSceneCaptureModule`  
`class FCineCameraSceneCaptureModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/CineCameraSceneCapture/Source/CineCameraSceneCapture/Public/CineCameraSceneCaptureComponent.h` (Public)


#### class `UCineCaptureComponent2D`  
`class UCineCaptureComponent2D : public USceneCaptureComponent2D`  
_L21-74_
- reflection: `UCLASS(hidecategories = (Transform, Collision, Object, Physics, SceneComponent, PostProcessVolume, Projection, Rendering, PlanarReflection), ClassGroup = Rendering, editinlinenew, meta = (BlueprintSpawnableComponent))`
- inherits: `USceneCaptureComponent2D`
- desc: Cine Capture Component extends Scene Capture to allow users to render Cine Camera Component into a render target. Cine Capture has a few modifiable properties, but most of the properties are controlled by Cine Camera Component. Cine Capture Component is required to be parented to Cine Camera Component or a class that extends it.
- L31 _public member_ `int32 RenderTargetHighestDimension;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture Settings", meta = (ClampMin = "1", ClampMax = "8192", UIMin = "1", UIMax = "8192"))` — Highest possible dimension of specified render target in either X or Y (depends on cine camera aspect ratio). Used to adjust the render target size. Example: With cine camera's censor aspect ratio is 2:1, and Highest Dimension set to 1000, the render target will be resized to 1000x500.
- L38 _public member_ `bool bFollowSceneCaptureRenderPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture Settings", AdvancedDisplay)` — Affects rendering path cine capture takes. Scene Capture takes a slightly different rendering route compared to viewport rendering for the purposes of optimization. If the results of cine capture are vastly different to what cine camera displays try disabling this.
- L42 _public member_ `bool bOverrideUserFlags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture Settings", AdvancedDisplay)` — Override state for per-view user flags accessible in materials via TestPostVolumeUserFlag node.
- L46 _public member_ `int32 UserFlags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture Settings", AdvancedDisplay, meta = (EditCondition = "bOverrideUserFlags"))` — Per-view user flags accessible in materials via TestPostVolumeUserFlag node, allowing per-view overrides of material behavior.
- L52 _public member_ `FOpenColorIODisplayConfiguration OCIOConfiguration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color", meta = (DisplayName = "OpenColorIO Display Configuration"))` — Open Color IO Configuration. Used to apply color transforms.
- L56 _public member_ `TSoftObjectPtr<UCineCameraComponent> CineCameraComponent;` — `UPROPERTY()` — Used to gather relevant properties for View rendering.
- L59 _public prototype_ `virtual void UpdateSceneCaptureContents(FSceneInterface* Scene, ISceneRenderBuilder& SceneRenderBuilder) override;`
- L60 _public prototype_ `virtual void OnRegister() override;`
- L61 _public prototype_ `virtual void OnUnregister() override;`
- L64 _public prototype_ `virtual void OnAttachmentChanged() override;` — Used for validation of this componet's attachment to Cine Camera Component.
- L65 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L68 _private prototype_ `void CheckResizeRenderTarget();`
- L69 _private prototype_ `void ValidateCineCameraComponent();`
- L73 _private member_ `TSharedPtr<FCineCameraCaptureSceneViewExtension, ESPMode::ThreadSafe> CineCaptureSVE;` — This scene view extension is used to get ahold of views during the setup process.

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCineCapture, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCineCapture, Log, All);`
