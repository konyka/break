# Plugins / CompositeCore

- module root: `Plugins/Compositing/CompositeCore/Source/CompositeCore`
- headers: 10; symbols: 281
- symbol kinds: class=8, delegate=2, enum=5, enumerator=32, function=18, macro=6, member=75, namespace=16, prototype=103, struct=13, typedef=3
- PrivateDependencyModuleNames: Projects, RHI, RenderCore, Renderer, SettingsEditor, Slate, SlateCore, SourceControl, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine

### `Plugins/Compositing/CompositeCore/Source/CompositeCore/Private/CompositeCoreSceneViewExtension.h` (Private)


#### struct `UE::CompositeCore::FScopedExternalTextureMap`  
`struct FScopedExternalTextureMap`  
_L30-53_
- desc: Collection of external textures scoped to internal RDG access.
- L35 _public prototype_ `FScopedExternalTextureMap(const FCompositeCoreSceneViewExtension& SVE, FRDGBuilder& InGraphBuilder, const FSceneView& InView);` — Constructor
- L38 _public prototype_ `~FScopedExternalTextureMap();` — Destructor
- L41 _public function_ `const TSortedMap<UE::CompositeCore::ResourceId, UE::CompositeCore::FPassInput>& Get() const` — Get the map of ResourceId to pass input textures.
- L48 _private member_ `FRDGBuilder& GraphBuilder;` — Host graph builder
- L50 _private member_ `TSortedMap<UE::CompositeCore::ResourceId, UE::CompositeCore::FPassInput> Textures;` — Map of pass input external textures.
- L52 _private member_ `TArray<FRDGViewableResource*, SceneRenderingAllocator> RestoreToExternal;` — List of textures marked for internal access for external restoration upon destruction.

#### class `FCompositeCoreSceneViewExtension`  
`class FCompositeCoreSceneViewExtension : public FWorldSceneViewExtension`  
_L57-168_
- inherits: `FWorldSceneViewExtension`
- L60 _public prototype_ `FCompositeCoreSceneViewExtension(const FAutoRegister& AutoReg, UWorld* InWorld);`
- L61 _public prototype_ `~FCompositeCoreSceneViewExtension();`
- L64 _public prototype_ `void RegisterPrimitives_GameThread(const TArray<UPrimitiveComponent*>& InPrimitiveComponents, ECompositeCoreHoldoutManagement HoldoutManagement = ECompositeCoreHoldoutManagement::Automatic);` — Register primitives for compositing.
- L67 _public prototype_ `void UnregisterPrimitives_GameThread(const TArray<UPrimitiveComponent*>& InPrimitiveComponents, ECompositeCoreHoldoutManagement HoldoutManagement = ECompositeCoreHoldoutManagement::Automatic);` — Unregister primitives for compositing.
- L70 _public prototype_ `void SetRenderWork_GameThread(UE::CompositeCore::FRenderWork&& InWork);` — Set frame render work to be enqueued on the render thread.
- L73 _public prototype_ `void ResetRenderWork_GameThread();` — Reset frame render work.
- L76 _public prototype_ `void SetBuiltInRenderPassOptions_GameThread(const UE::CompositeCore::FBuiltInRenderPassOptions& InOptions);` — Set options for built-in composite custom render pass.
- L79 _public prototype_ `void ResetBuiltInRenderPassOptions_GameThread();` — Reset default options for built-in composite custom render pass.
- L82 _public prototype_ `void CollectCustomRenderTarget(uint32 InViewId, const TRefCountPtr<IPooledRenderTarget>& InRenderTarget);` — Called by the custom render pass to store its view render target for this frame.
- L85 _public prototype_ `virtual int32 GetPriority() const override;`
- L86 _public prototype_ `virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;`
- L87 _public prototype_ `virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;`
- L88 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L89 _public prototype_ `virtual void PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;`
- L90 _public prototype_ `virtual void PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override;`
- L91 _public prototype_ `virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& InView, const FPostProcessingInputs& Inputs) override;`
- L92 _public prototype_ `virtual void SubscribeToPostProcessingPass(EPostProcessingPass PassId, const FSceneView& InView, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled) override;`
- L93 _public prototype_ `virtual void PostRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;`
- L94 _public prototype_ `virtual void PostRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override;`
- L99 _protected prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;`
- L104 _private prototype_ `const UE::CompositeCore::FRenderWork& GetRenderWork() const;` — Getter for the frame render work, either from the actor or default.
- L107 _private prototype_ `bool IsAllowedForViewFamily(const FSceneViewFamily& InViewFamily) const;` — Check if render work is allowed on the view family.
- L110 _private prototype_ `void ApplyPreprocessing(FRDGBuilder& GraphBuilder, FSceneView& InView) const;` — Once-per frame external resource processing passes.
- L113 _private prototype_ `bool ApplyPassesRecursive( FRDGBuilder& GraphBuilder, const FSceneView& InView, const UE::CompositeCore::FPassInputArray& Inputs, const UE::CompositeCore::FPassInputArray& OriginalInputs, UE::CompositeCore::FPassContext& PassContext, const TArray<const FCompositeCorePassProxy*> InPasses, const UE::CompositeCore::FScopedExternalTextureMap& InExternalTextures, const int32 LastMergePassIndex, const int32 RecursionLevel, UE::CompositeCore::FPassTexture& Output ) const;` — Recursive pass application.
- L127 _private prototype_ `FScreenPassTexture PostProcessWork_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& InView, const FPostProcessMaterialInputs& Inputs, ISceneViewExtension::EPostProcessingPass InLocation);` — Callback for processing passes.
- L131 _private member_ `TSet<TWeakObjectPtr<UPrimitiveComponent>> CompositePrimitives;` — Collection of primitives to render as a custom render pass and composite after post-processing. .
- L134 _private member_ `TSortedMap<uint32, TRefCountPtr<IPooledRenderTarget>> CustomRenderTargetPerView_RenderThread;` — Custom render pass render targets for each active view .
- L137 _private member_ `TOptional<UE::CompositeCore::FRenderWork> RenderWork_RenderThread;` — Custom render work.
- L140 _private member_ `TOptional<UE::CompositeCore::FBuiltInRenderPassOptions> BuiltInRenderPassOptions;` — Built-in composite render pass options.
- L143 _private member_ `bool bHasCustomRenderWork = false;` — Used to keep the SVE active if any custom render work is present.
- L146 _private member_ `TOptional<ESceneCaptureSource> MainRenderMode;` — Optional main render mode override
- L149 _private member_ `TSet<EViewModeIndex> AllowedViewModes;` — View modes for which the compositing is allowed.
- L152 _private member_ `TOptional<UE::CompositeCore::FActiveViewportFilter> ActiveViewportFilter;` — Game-thread copy of the active viewport filter, consulted by SetupView.
- L155 _private member_ `TArray<TWeakObjectPtr<USceneCaptureComponent2D>> SceneCapturesUpdateQueue;` — List of scene captures to render-update this frame.
- L165 _private member_ `mutable TSortedMap<uint32, TSortedMap<const FCompositeCorePassProxy*, const UE::CompositeCore::FPassTexture>> CachedOutputsPerView_RenderThread;` — Map of cached proxy output textures per view (post-processing only currently). Passes can then refer to a previous proxy as an input type, and if that proxy has already been executed its output will be used directly without needing to duplicate work. This is possible since RDG automatically knows to connect & preserve the texture resource when it is later used as an input of a subsequent pass.

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UE`
- L27 _namespace_ `namespace CompositeCore` (scope `UE`)

### `Plugins/Compositing/CompositeCore/Source/CompositeCore/Private/Passes/CompositeCorePassDilate.h` (Private)


#### struct `UE::CompositeCore::Private::FDilateInputs`  
`struct FDilateInputs`  
_L14-24_
- L17 _public member_ `int32 DilationSize = 1;` — Dilation kernel radius in pixels (0 = no-op, 1 = 3×3 neighborhood, 2 = 5×5 neighborhood). Clamped to [0, 2].
- L20 _public member_ `bool bOpacifyOutput = true;` — Opacify the pass output to solid colors.
- L23 _public member_ `float AlphaThreshold = 0.0000001f;` — Opacity threshold - pixels at or below this (standard opacity space) are treated as fully transparent.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CompositeCore` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::CompositeCore`)
- L31 _prototype_ `void AddDilatePass(FRDGBuilder& GraphBuilder, FRDGTextureRef Input, FRDGTextureRef Output, ERHIFeatureLevel::Type FeatureLevel, const FDilateInputs& PassInputs = {});` (scope `UE::CompositeCore::Private`) — Compute shader dilation pass of non-translucent color texels. This is done as preparation for compositing to hide aliasing under the main render's anti-aliased edges, with an optional opacification step.

### `Plugins/Compositing/CompositeCore/Source/CompositeCore/Public/CompositeCoreModule.h` (Public)


#### class `FCompositeCoreModule`  
`class FCompositeCoreModule : public IModuleInterface`  
_L13-20_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L18 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCompositeCore, Log, All);`
- L11 _delegate_ `DECLARE_STATS_GROUP(TEXT("CompositeCore"), STATGROUP_CompositeCore, STATC`

### `Plugins/Compositing/CompositeCore/Source/CompositeCore/Public/CompositeCoreSettings.h` (Public)


#### class `UCompositeCorePluginSettings`  
`class UCompositeCorePluginSettings : public UDeveloperSettings`  
_L27-94_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig, meta = (DisplayName = "Composite Core"))`
- inherits: `UDeveloperSettings`
- desc: Settings for the CompositeCore module.
- L32 _public prototype_ `UCompositeCorePluginSettings();`
- L35 _public prototype_ `virtual FName GetCategoryName() const;`
- L37 _public prototype_ `virtual FText GetSectionText() const override;`
- L38 _public prototype_ `virtual FName GetSectionName() const override;`
- L39 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L44 _public prototype_ `virtual void PostInitProperties() override;`
- L48 _public prototype_ `bool IsAllowedPrimitiveClass(const UPrimitiveComponent* InPrimitiveComponent) const;` — Ensure that the primitive component class is allowed by checking against plugin settings.
- L51 _public prototype_ `bool IsAllowedComponentClass(const USceneComponent* InComponent) const;` — Ensure that the scene component class is allowed by checking against plugin settings.
- L58 _public member_ `uint32 bApplyPreExposure : 1;` — `UPROPERTY(config, EditAnywhere, Category = CompositeCore, meta = ( ConsoleVariable = "CompositeCore.ApplyPreExposure", DisplayName = "Apply Pre-Exposure", ToolTip = "When enabled, the scene main render pre-exposure is applied onto the separate composited render. This can be used to match exposure to the scene. (Maps to \"CompositeCore.ApplyPreExposure\" console variable).", ConfigRestartRequired = false))`
- L62 _public member_ `TArray<FSoftClassPath> DisabledPrimitiveClasses;` — `UPROPERTY(config, EditAnywhere, Category = CompositeCore)` — Primitive component classes that do not support the composite pipeline.
- L66 _public member_ `TArray<FSoftClassPath> AllowedComponentClasses;` — `UPROPERTY(config, EditAnywhere, Category = CompositeCore)` — Allowed component classes for which users will not be warned if associated primitive cannot immediately be found.
- L70 _public member_ `int32 SceneViewExtensionPriority;` — `UPROPERTY(config, EditAnywhere, Category = CompositeCore, AdvancedDisplay)` — Composite (scene view extension) post-processing priority, which defaults to before OpenColorIO.
- L75 _private prototype_ `void CacheDisabledPrimitiveClasses() const;` — Cache primitive class pointers to prevent load object calls during allowed class checks.
- L78 _private prototype_ `void CacheAllowedComponentClasses() const;` — Cache component class pointers to prevent load object calls during allowed class checks.
- L81 _private member_ `mutable TArray<const UClass*> CachedDisabledPrimitiveClasses;` — Cached list of disallowed primitive class types.
- L84 _private member_ `mutable bool bIsPrimitiveCacheDirty;` — Dirty primitive cache flag.
- L87 _private member_ `mutable TArray<const UClass*> CachedAllowedComponentClasses;` — Cached list of allowed component class types.
- L90 _private member_ `mutable bool bIsComponentCacheDirty;` — Dirty component cache flag.
- L93 _private member_ `mutable FCriticalSection CriticalSection;` — Mutable cache lock.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace CompositeCore` (scope `UE`)
- L19 _prototype_ `bool IsRegisterPrimitivesOnTickEnabled();` (scope `UE::CompositeCore`)

### `Plugins/Compositing/CompositeCore/Source/CompositeCore/Public/CompositeCoreSubsystem.h` (Public)


#### class `UCompositeCoreSubsystem`  
`class UCompositeCoreSubsystem : public UTickableWorldSubsystem`  
_L28-91_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Transient)`
- inherits: `UTickableWorldSubsystem`
- desc: Composite subsytem used as an interface to the (private) scene view extension.
- L33 _public prototype_ `UCompositeCoreSubsystem();`
- L36 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem implementation Begin
- L37 _public prototype_ `virtual void Deinitialize() override;`
- L41 _public function_ `virtual bool IsTickableInEditor() const override` — FTickableGameObject implementation Begin
- L42 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L45 _public function_ `virtual TStatId GetStatId() const override`
- L49 _public prototype_ `void RegisterPrimitive(UPrimitiveComponent* InPrimitiveComponent, ECompositeCoreHoldoutManagement HoldoutManagement = ECompositeCoreHoldoutManagement::Automatic);` — `UFUNCTION(BlueprintCallable, Category = "Composite Core")` — Register a single primitive for compositing.
- L52 _public prototype_ `void RegisterPrimitives(const TArray<UPrimitiveComponent*>& InPrimitiveComponents, ECompositeCoreHoldoutManagement HoldoutManagement = ECompositeCoreHoldoutManagement::Automatic);` — Register multiple primitives for compositing.
- L56 _public prototype_ `void UnregisterPrimitive(UPrimitiveComponent* InPrimitiveComponent, ECompositeCoreHoldoutManagement HoldoutManagement = ECompositeCoreHoldoutManagement::Automatic);` — `UFUNCTION(BlueprintCallable, Category = "Composite Core")` — Unregister a single primitive from compositing.
- L59 _public prototype_ `void UnregisterPrimitives(const TArray<UPrimitiveComponent*>& InPrimitiveComponents, ECompositeCoreHoldoutManagement HoldoutManagement = ECompositeCoreHoldoutManagement::Automatic);` — Unregister multiple primitives from compositing.
- L62 _public prototype_ `void SetRenderWork(UE::CompositeCore::FRenderWork&& InWork);` — Set scene view extension frame render work.
- L65 _public prototype_ `void ResetRenderWork();` — Reset scene view extension frame render work.
- L68 _public prototype_ `void SetBuiltInRenderPassOptions(const UE::CompositeCore::FBuiltInRenderPassOptions& InOptions);` — Set built-in composite render pass options.
- L71 _public prototype_ `void ResetBuiltInRenderPassOptions();` — Reset built-in composite render pass options.
- L74 _public prototype_ `static bool IsProjectSettingsValid();` — True if the project settings are valid for the CompositeCore plugin to work.
- L79 _private prototype_ `bool ValidateProjectSettings();` — Returns true if the (renderer) project settings are correctly enabled for the composite to be active.
- L83 _private prototype_ `void PrimitiveHoldoutSettingsNotification();` — Toast notification to ask users to enable the missing project settings.
- L86 _private member_ `TWeakPtr<SNotificationItem> HoldoutNotificationItem;` — Toast notification item.
- L90 _private member_ `TSharedPtr<FCompositeCoreSceneViewExtension, ESPMode::ThreadSafe> CompositeCoreViewExtension;` — Owned scene view extension.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMPOSITECORE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace CompositeCore` (scope `UE`)

### `Plugins/Compositing/CompositeCore/Source/CompositeCore/Public/CompositeCoreTypes.h` (Public)


#### enum `ECompositeCoreHoldoutManagement`  
`enum class ECompositeCoreHoldoutManagement : uint8`  
_L14-18_
- reflection: `UENUM(BlueprintType)`
- desc: Holdout property management on registered primitives.
- L16 _public enumerator_ `None`
- L17 _public enumerator_ `Automatic`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMPOSITECORE_API`

### `Plugins/Compositing/CompositeCore/Source/CompositeCore/Public/HoldoutCompositeComponent.h` (Public)


#### class `UHoldoutCompositeComponent`  
`class UHoldoutCompositeComponent : public USceneComponent`  
_L15-64_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Rendering, HideCategories=(Activation, Transform, Lighting, Rendering, Tags, Cooking, Physics, LOD, AssetUserData, Navigation), editinlinenew, meta = (BlueprintSpawnableComponent))`
- inherits: `USceneComponent`
- L21 _public prototype_ `virtual void BeginDestroy() override;`
- L25 _public prototype_ `virtual void OnRegister() override;`
- L26 _public prototype_ `virtual void OnUnregister() override;`
- L27 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L31 _public prototype_ `virtual void OnComponentCreated() override;`
- L32 _public prototype_ `virtual void OnAttachmentChanged() override;`
- L33 _public prototype_ `virtual void DetachFromComponent(const FDetachmentTransformRules& DetachmentRules) override;`
- L37 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L42 _public prototype_ `bool IsEnabled() const;` — `UFUNCTION(BlueprintGetter)` — Get the enabled state of the component.
- L46 _public prototype_ `void SetEnabled(bool bInEnabled);` — `UFUNCTION(BlueprintSetter)` — Set the enabled state of the component.
- L49 _public member_ `static FHoldoutCompositeComponentDelegate OnComponentCreatedDelegate;` — Event fired once a component is created.
- L54 _private prototype_ `void RegisterCompositeImpl();` — Private implementation of the register method.
- L57 _private prototype_ `void UnregisterCompositeImpl();` — Private implementation of the unregister method.
- L63 _private member_ `bool bIsEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintGetter = IsEnabled, BlueprintSetter = SetEnabled, Category = "CompositeCore", meta = (AllowPrivateAccess = true))` — Whether or not the component activates the composite.

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FHoldoutCompositeComponentDelegate, const UHoldoutCompositeComponent*);`
- L12 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FHoldoutCompositeComponentDelegate, const UHoldoutCompositeComponent*);`

### `Plugins/Compositing/CompositeCore/Source/CompositeCore/Public/Passes/CompositeCorePassFXAAProxy.h` (Public)


#### class `UE::CompositeCore::FFXAAPassProxy`  
`class FFXAAPassProxy : public FCompositeCorePassProxy`  
_L19-33_
- inherits: `FCompositeCorePassProxy`
- L22 _public prototype_ `IMPLEMENT_COMPOSITE_PASS(FFXAAPassProxy);`
- L26 _public prototype_ `FPassTexture Add(FRDGBuilder& GraphBuilder, const FSceneView& InView, const FPassInputArray& Inputs, const FPassContext& PassContext) const override;`
- L29 _public member_ `TOptional<int32> QualityOverride = {};` — Optional r.FXAA.Quality setting override.
- L32 _public member_ `bool bDisplayTransform = true;` — When true, applies a display transform (tonemap + gamma) before AA and inverts it after. Improves edge detection on linear content but may produce dark halos at alpha boundaries.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMPOSITECORE_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CompositeCore` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::CompositeCore`)
- L16 _prototype_ `FScreenPassTexture AddDisplayTransformPass(FRDGBuilder& GraphBuilder, const FScreenPassViewInfo ViewInfo, const FScreenPassTexture& Input, const FScreenPassRenderTarget& OverrideOutput, bool bIsForward, float InGamma = 2.2f);` (scope `UE::CompositeCore::Private`)

### `Plugins/Compositing/CompositeCore/Source/CompositeCore/Public/Passes/CompositeCorePassMergeProxy.h` (Public)


#### enum `ECompositeCoreMergeOp`  
`enum class ECompositeCoreMergeOp : uint8`  
_L16-39_
- reflection: `UENUM()`
- desc: Merge/blend operations, assuming inputs are alpha pre-multiplied.
- L18 _public enumerator_ `None UMETA(ToolTip = "Current layer A previous replaces previous layer B.")`
- L19 _public enumerator_ `Over UMETA(ToolTip = "Current layer A over previous layer B: A + B * (1-a).")`
- L20 _public enumerator_ `Under UMETA(ToolTip = "Current layer A under previous layer B: A * (1-b) + B.")`
- L21 _public enumerator_ `Add UMETA(ToolTip = "Current layer A added to previous layer B: A + B.")`
- L22 _public enumerator_ `Subtract UMETA(ToolTip = "Previous layer B subtracted from current layer A: A - B.")`
- L23 _public enumerator_ `Multiply UMETA(ToolTip = "Current layer A multiplied by previous layer B: A * B.")`
- L24 _public enumerator_ `Divide UMETA(ToolTip = "Current layer A (safely) divided by previous layer B: A / B.")`
- L25 _public enumerator_ `Min UMETA(ToolTip = "Per-component minimum between current layer A and previous layer B.")`
- L26 _public enumerator_ `Max UMETA(ToolTip = "Per-component maximum between current layer A and previous layer B.")`
- L27 _public enumerator_ `In UMETA(ToolTip = "Current layer A masked by the previous layer B's alpha: A * b.")`
- L28 _public enumerator_ `Mask UMETA(ToolTip = "Current layer A's alpha masking the previous layer B: B * a.")`
- L29 _public enumerator_ `Screen UMETA(ToolTip = "Screen advanced blend mode.")`
- L30 _public enumerator_ `Overlay UMETA(ToolTip = "Overlay advanced blend mode.")`
- L31 _public enumerator_ `Darken UMETA(ToolTip = "Darken advanced blend mode.")`
- L32 _public enumerator_ `Lighten UMETA(ToolTip = "Lighten advanced blend mode.")`
- L33 _public enumerator_ `ColorDodge UMETA(ToolTip = "Color dodge advanced blend mode.")`
- L34 _public enumerator_ `ColorBurn UMETA(ToolTip = "Color burn advanced blend mode.")`
- L35 _public enumerator_ `HardLight UMETA(ToolTip = "Hard light advanced blend mode.")`
- L36 _public enumerator_ `SoftLight UMETA(ToolTip = "Soft light advanced blend mode.")`
- L37 _public enumerator_ `Difference UMETA(ToolTip = "Difference advanced blend mode.")`
- L38 _public enumerator_ `Exclusion UMETA(ToolTip = "Exclusion advanced blend mode.")`

#### enum `UE::CompositeCore::ELensDistortionHandling`  
`enum class ELensDistortionHandling : uint8`  
_L46-50_
- desc: Describe whether lens distortion is handled in the merge shader pass.
- L48 _public enumerator_ `Disabled = 0u`
- L49 _public enumerator_ `Enabled = 1u`

#### class `UE::CompositeCore::FMergePassProxy`  
`class FMergePassProxy : public FCompositeCorePassProxy`  
_L52-82_
- inherits: `FCompositeCorePassProxy`
- L55 _public prototype_ `IMPLEMENT_COMPOSITE_PASS(FMergePassProxy);`
- L60 _public prototype_ `FMergePassProxy(FPassInputDeclArray InPassDeclaredInputs, ECompositeCoreMergeOp InMergeOp, const TCHAR* InParentName, ELensDistortionHandling bInUseLensDistortion = ELensDistortionHandling::Enabled, bool bInUltimatteBlend = false);` — Constructor
- L62 _public prototype_ `FPassTexture Add(FRDGBuilder& GraphBuilder, const FSceneView& InView, const FPassInputArray& Inputs, const FPassContext& PassContext) const override;`
- L66 _public member_ `ECompositeCoreMergeOp MergeOp = ECompositeCoreMergeOp::Over;` — Merge operation.
- L69 _public member_ `const TCHAR* ParentName = TEXT("Mer` — Parent pass debug name.
- L72 _public member_ `ELensDistortionHandling bUseLensDistortion = ELensDistortionHandling::Enabled;` — Flag to enable or disable application of engine-provided lens distortion LUTs, true by default.
- L75 _public member_ `bool bUltimatteBlend = false;` — When enabled, both inputs are encoded to sRGB before blending and decoded back to linear after. Matches Ultimatte Key & Fill workflows where content is in display space.
- L81 _public member_ `bool bLuminanceOnly = false;` — Divide-only: when true, the matte's RGB uses a single luminance ratio applied uniformly to all channels instead of independent per-channel ratios.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMPOSITECORE_API`
- L41 _namespace_ `namespace UE`
- L43 _namespace_ `namespace CompositeCore` (scope `UE`)
- L84 _prototype_ `const FName& GetMergePassPassName();` (scope `UE::CompositeCore`)

### `Plugins/Compositing/CompositeCore/Source/CompositeCore/Public/Passes/CompositeCorePassProxy.h` (Public)


#### enum `UE::CompositeCore::EEncoding`  
`enum class EEncoding : uint8`  
_L38-43_
- desc: Texture encoding type, used for scene color. (HDR is not currently supported.)
- L40 _public enumerator_ `Linear = 0`
- L41 _public enumerator_ `Gamma = 1`
- L42 _public enumerator_ `sRGB = 2`

#### enum `UE::CompositeCore::ResourceId`  
`enum class ResourceId : uint32`  
_L55-65_
- desc: Strongly-typed identifier for passes, textures, or built-in renderer sources/targets. Values in [0, ExternalRangeStart) are reserved for built-in identifiers. Values >= ExternalRangeStart are allocated sequentially for user-declared external textures; the underlying index is offset so that ExternalInputs[0] corresponds to ExternalRangeStart. Underlying type is uint32 and values are stable; enumerators must not be renumbered since they may be referenced from serialized state or by external plugins.
- L58 _public enumerator_ `None = 0` — Sentinel value; not a valid resource.
- L60 _public enumerator_ `BuiltInCRP = 1` — Built-in custom render pass identifier.
- L62 _public enumerator_ `BuiltInEmpty = 2` — Built-in empty/black identifier.
- L64 _public enumerator_ `ExternalRangeStart = 100` — First identifier of the external texture inputs, see ExternalInputs on FRenderWork.

#### struct `UE::CompositeCore::FResourceMetadata`  
`struct FResourceMetadata`  
_L93-127_
- desc: Texture resource metadata.
- L96 _public member_ `bool bInvertedAlpha = false;` — Is the alpha inverted (like scene color)?
- L99 _public member_ `bool bDistorted = false;` — Is the texture content distorted?
- L102 _public member_ `bool bPreExposed = false;` — Is the texture's exposure already adjusted?
- L105 _public member_ `EEncoding Encoding = EEncoding::Linear;` — Source color encoding.
- L108 _public member_ `ESamplerFilter Filter = SF_Bilinear;` — Sampler filter mode for the texture resource.
- L111 _public prototype_ `FRHISamplerState* GetSamplerState() const;` — Returns the RHI sampler state matching the Filter setting.
- L114 _public member_ `const TCHAR* DebugName = TEXT("Com` — Debug name
- L117 _public function_ `bool operator==(const FResourceMetadata& Other) const` — Equality operator

#### struct `UE::CompositeCore::FPassInternalResourceDesc`  
`struct FPassInternalResourceDesc`  
_L130-137_
- desc: Pass texture description for internal resources (default scene textures).
- L133 _public member_ `int32 Index = 0;` — Index, which maps to the default 0-4 post-processing inputs or beyond.
- L136 _public member_ `bool bOriginalCopyBeforePasses = false;` — Flag to bypass the previous pass textures & access the original scene textures.

#### struct `UE::CompositeCore::FPassExternalResourceDesc`  
`struct FPassExternalResourceDesc`  
_L140-144_
- desc: Pass texture description for external render targets.
- L143 _public member_ `ResourceId Id = ResourceId::None;` — External resource identifier.

#### struct `UE::CompositeCore::FExternalTexture`  
`struct FExternalTexture`  
_L172-179_
- desc: External texture resource and its accompanying metadata.
- L175 _public member_ `TWeakObjectPtr<UTexture> Texture = {};` — Texture weak object pointer, for use on the game thread.
- L178 _public member_ `FResourceMetadata Metadata = {};` — Texture metadata.

#### struct `UE::CompositeCore::FPassTexture`  
`struct FPassTexture`  
_L182-189_
- desc: Resolved texture resource with an active (screen) texture and its accompanying metadata.
- L185 _public member_ `FScreenPassTexture Texture = {};` — Pass screen texture.
- L188 _public member_ `FResourceMetadata Metadata = {};` — Texture metadata.

#### struct `UE::CompositeCore::FPassInputArray`  
`struct FPassInputArray`  
_L200-253_
- desc: Resolved pass inputs handed to FCompositeCorePassProxy::Add at render time. Render-thread, frame-scoped. Inputs are resolved from declared inputs (internal textures, external textures, or previous pass outputs) by the scene view extension before dispatch.
- L203 _public prototype_ `FPassInputArray() = default;` — Default constructor
- L204 _public prototype_ `FPassInputArray(FPassInputArray&&) = default;`
- L205 _public prototype_ `FPassInputArray(const FPassInputArray&) = default;`
- L206 _public prototype_ `FPassInputArray& operator=(FPassInputArray&&) = default;`
- L207 _public prototype_ `FPassInputArray& operator=(const FPassInputArray&) = default;`
- L210 _public prototype_ `FPassInputArray( FRDGBuilder& GraphBuilder, const FSceneView& InView, const FPostProcessMaterialInputs& InPostInputs, const ISceneViewExtension::EPostProcessingPass& InLocation );` — Constructor
- L218 _public function_ `const FPassInput& operator[] (int32 Index) const` — Array access operator overload
- L224 _public function_ `FPassInput& operator[] (int32 Index)` — Array access operator overload
- L230 _public function_ `bool IsValidIndex(int32 Index) const` — Tests if index is valid, i.e. greater than or equal to zero, and less than the number of elements in the array.
- L236 _public function_ `int32 Num() const` — Number of pass inputs
- L239 _public function_ `TArray<UE::CompositeCore::FPassInput>& GetInputs()` — Mutable access to the underlying input array. Prefer the subscript operator for read-only access.
- L242 _public function_ `TConstArrayView<UE::CompositeCore::FPassInput> GetInputs() const` — Read-only view of the underlying input array.
- L245 _public prototype_ `FPostProcessMaterialInputs ToPostProcessInputs(FRDGBuilder& GraphBuilder, FSceneTextureShaderParameters SceneTextures) const;` — Conversion function to engine post-process (material) inputs.
- L248 _public member_ `FScreenPassRenderTarget OverrideOutput;` — Pass override output.
- L252 _private member_ `TArray<UE::CompositeCore::FPassInput> Inputs;` — Pass texture input array.

#### struct `UE::CompositeCore::FPassContext`  
`struct FPassContext`  
_L260-273_
- desc: Per-dispatch pass parameter information. Render-thread, frame-scoped; passed by value/const-ref into FCompositeCorePassProxy::Add.
- L263 _public member_ `FSceneTextureShaderParameters SceneTextures = {};` — The uniform buffer containing all scene textures.
- L266 _public member_ `FIntRect OutputViewRect = {};` — Active post-processing output view rectangle.
- L269 _public member_ `ISceneViewExtension::EPostProcessingPass Location = ISceneViewExtension::EPostProcessingPass::BeforeDOF;` — Post-processing location in the scene view extension pipeline.
- L272 _public member_ `bool bOutputSceneColor = false;` — Is the current pass expected to output scene color?

#### struct `UE::CompositeCore::FBuiltInRenderPassOptions`  
`struct FBuiltInRenderPassOptions final`  
_L276-292_
- desc: Options to control the built-in custom render pass.
- L279 _public prototype_ `FBuiltInRenderPassOptions();` — Constructor. DilationSize is initialized from the CompositeCore.Debug.DilationSize CVar.
- L282 _public member_ `TOptional<int32> ViewUserFlagsOverride;` — Custom user flags value used to alter materials in the composite render pass.
- L285 _public member_ `bool bEnableUnlitViewmode = true;` — Enables the development shader debug feature that routes the Base Color output to Emissive for the separate render. Non-shipping PC build only.
- L288 _public member_ `int32 DilationSize = 1;` — Dilation kernel radius (0 = no-op, 1 = 3×3 neighborhood, 2 = 5×5 neighborhood). Clamped to [0, 2]. Default comes from CompositeCore.Debug.DilationSize.
- L291 _public member_ `bool bOpacifyOutput = true;` — Opacify to extract the solid colors behind translucent alpha holdout masks.

#### struct `UE::CompositeCore::FActiveViewportFilter`  
`struct FActiveViewportFilter`  
_L303-310_
- desc: Per-frame filter restricting compositing to a single viewport. Populated by the host (see ACompositeActor) when ACompositeActor::bRestrictToActiveViewport is enabled, and stored as a TOptional so the unset state represents "no restriction". TargetRenderTarget is used for pointer comparison only and never dereferenced. Read only on the game thread today (see SVE::SetupView). Any future render-thread consumer should reconsider TWeakObjectPtr / raw-pointer thread-safety before reading.
- L306 _public member_ `TWeakObjectPtr<const AActor> TargetViewActor;` — Target view actor, matched against FSceneView::ViewActor.
- L309 _public member_ `const FRenderTarget* TargetRenderTarget = nullptr;` — Target viewport render target (editor only). Pointer comparison only.

#### struct `UE::CompositeCore::FRenderWork`  
`struct FRenderWork final`  
_L321-355_
- desc: Render-thread struct for scene view extension render work per frame. Populated on the game thread (typically via UCompositeCoreSubsystem::SetRenderWork) and handed off via move. After handoff the struct is treated as immutable on the render thread for the duration of the frame. All FCompositeCorePassProxy pointers referenced by PreprocessingPasses and FramePasses must be allocated from FrameAllocator and must not outlive it.
- L324 _public prototype_ `static const FRenderWork& GetDefault();` — Default frame work.
- L327 _public prototype_ `FRenderWork();` — Constructor.
- L330 _public prototype_ `bool IsEmpty() const;` — Returns true if there are no active work passes.
- L333 _public member_ `TArray<FExternalTexture> ExternalInputs;` — Array of user-defined external input texture overrides, where array index + ResourceId::ExternalRangeStart maps to the ResourceId.
- L336 _public member_ `TSortedMap<ResourceId, TArray<const FCompositeCorePassProxy*>> PreprocessingPasses;` — Pre-processing passes applied on specific texture resources at the start of rendering. Passes within a value array execute strictly in array order.
- L339 _public member_ `TSortedMap<ISceneViewExtension::EPostProcessingPass, TArray<const FCompositeCorePassProxy*>> FramePasses;` — Post-processing passes at the specified pipeline locations. Passes within a value array execute strictly in array order; producers are responsible for emitting a valid order.
- L342 _public member_ `TUniquePtr<FSceneRenderingBulkObjectAllocator> FrameAllocator;` — Proxy allocator. Owns the lifetime of all FCompositeCorePassProxy pointers in this struct.
- L345 _public member_ `TOptional<ESceneCaptureSource> MainRenderMode;` — Optional main render mode override
- L348 _public member_ `TSet<EViewModeIndex> AllowedViewModes;` — View modes for which the compositing is allowed.
- L351 _public member_ `TOptional<FActiveViewportFilter> ActiveViewportFilter;` — Optional per-frame filter restricting compositing to a single viewport (see FActiveViewportFilter).
- L354 _public member_ `TArray<TWeakObjectPtr<USceneCaptureComponent2D>> SceneCapturesUpdateQueue;` — List of scene captures to render-update this frame.

#### struct `UE::CompositeCore::FPassTypeDescriptor`  
`struct FPassTypeDescriptor`  
_L367-389_
- desc: Static metadata describing the shape of a pass type. Surfaced by FCompositeCorePassProxy::GetTypeDescriptor. Intended to let tooling (future graph UI, validation, serialization) reason about a pass without dispatching it. This struct is intentionally not final: new descriptor fields may be added in the future (e.g., acceptable input variant kinds per slot, output slot metadata) without breaking existing consumers.
- L370 _public member_ `FName TypeName;` — Unique type name; matches FCompositeCorePassProxy::GetTypeName.
- L379 _public member_ `TArray<FName> InputSlotNames;` — Stable names for declared input slots, in declaration order. These are the identity used when a graph UI, inspector, or serialized asset needs to reference a specific input independent of its array index. If left empty, tooling should synthesize fallback names ("Input0", "Input1", ...) from GetNumDeclaredInputs.
- L385 _public member_ `TOptional<int32> FixedInputCount;` — Fixed input count, if the pass accepts exactly this many inputs (e.g., two-input merge). Unset means the pass accepts a variable number of inputs.
- L388 _public member_ `bool bSupportsVariadicInputs = false;` — True if the pass can accept more than FixedInputCount inputs (variadic).

#### class `FCompositeCorePassProxy`  
`class FCompositeCorePassProxy`  
_L394-495_
- desc: Render-thread pass proxy.
- L398 _public prototype_ `FCompositeCorePassProxy() = default;` — Default constructor. Intended for use by subclasses that populate declared inputs later.
- L401 _public prototype_ `FCompositeCorePassProxy(UE::CompositeCore::FPassInputDeclArray InPassDeclaredInputs);` — Constructor taking the pass's declared inputs.
- L404 _public prototype_ `virtual ~FCompositeCorePassProxy() = default;` — Virtual destructor
- L407 _public prototype_ `virtual const FName& GetTypeName() const = 0;` — Bare-bones RTTI method to allow users to differentiate / downcast the composite core pass they're interested in.
- L416 _public prototype_ `virtual UE::CompositeCore::FPassTypeDescriptor GetTypeDescriptor() const;` — Returns static metadata about this pass type. The default implementation synthesizes a descriptor from GetTypeName() and the currently declared inputs (with fallback slot names "Input0", "Input1", ...). Subclasses should override this to provide meaningful slot names and arity hints that tooling can rely on.
- L419 _public prototype_ `virtual UE::CompositeCore::FPassTexture Add( FRDGBuilder& GraphBuilder, const FSceneView& InView, const UE::CompositeCore::FPassInputArray& Inputs, const UE::CompositeCore::FPassContext& PassContext ) const = 0;` — Render-thread add pass method to override.
- L427 _public function_ `int32 GetNumDeclaredInputs() const` — Number of inputs used by the pass.
- L433 _public function_ `const UE::CompositeCore::FPassInputDecl& GetDeclaredInput(int32 InputIndex) const` — Get pass input at specified index.
- L445 _public prototype_ `void SetDeclaredInput(int32 InputIndex, UE::CompositeCore::FPassInputDecl InInput);` — Replaces the declared input at the specified index. The index must be in range [0, GetNumDeclaredInputs()). This intentionally does not resize the declared-input array — arity is fixed at construction time. Used by layer-traversal code to back-patch a declared input after its source pass has been constructed.
- L448 _public function_ `const TOptional<UE::CompositeCore::ResourceId>& GetDeclaredPrimaryOutputOverride() const` — Get declared primary output pass override.
- L459 _public function_ `void DeclarePrimaryOutputOverride(UE::CompositeCore::ResourceId InExternalId)` — Declares that the primary output of this pass should be written to the given external resource. "Primary" is used intentionally to leave semantic room for secondary/additional outputs without a breaking rename in a future revision.
- L465 _public function_ `void ResetPrimaryOutputOverride()` — Resets the declared primary output override.
- L471 _public prototype_ `static FScreenPassRenderTarget CreateOutputRenderTarget(FRDGBuilder& GraphBuilder, const FSceneView& InView, const FIntRect& OutputViewRect, FRDGTextureDesc OutputDesc, const TCHAR* InName);` — Convenience function to create an output render target with the specified resolution.
- L478 _public prototype_ `static EPixelFormat GetSceneColorFormatChecked(EPixelFormat Fallback = PF_FloatRGBA);` — Returns FSceneTexturesConfig::Get().ColorFormat, or Fallback if the config has not been initialized for the current view.
- L488 _protected prototype_ `bool ValidateInputs(const UE::CompositeCore::FPassInputArray& Inputs) const;` — Ensures that the received inputs are compatible with the declared inputs and the type descriptor. Returns false if the input count violates the descriptor's FixedInputCount (when set and bSupportsVariadicInputs is false). Otherwise requires Inputs.Num() >= max(1, declared count).
- L491 _protected member_ `UE::CompositeCore::FPassInputDeclArray PassDeclaredInputs;` — List of pass input types.
- L494 _protected member_ `TOptional<UE::CompositeCore::ResourceId> PassDeclaredPrimaryOutputOverride;` — Optional declared primary output pass override.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API COMPOSITECORE_API`
- L33 _namespace_ `namespace UE`
- L35 _namespace_ `namespace CompositeCore` (scope `UE`)
- L72 _function_ `constexpr ResourceId MakeExternalResourceId(int32 ExternalIndex)` (scope `UE::CompositeCore`) — Builds a ResourceId that identifies the external texture at the given array index in FRenderWork::ExternalInputs. This is the only supported way to construct an external ResourceId; callers should never compute one from raw integer arithmetic.
- L82 _function_ `constexpr TOptional<int32> TryGetExternalIndex(ResourceId Id)` (scope `UE::CompositeCore`) — If Id refers to an external texture (i.e., Id >= ExternalRangeStart), returns the corresponding array index into FRenderWork::ExternalInputs. Returns an unset optional for built-in identifiers (None, BuiltInCRP, BuiltInEmpty).
- L90 _function_ `constexpr uint32 ToIndex(ResourceId Id)` (scope `UE::CompositeCore`) — Returns the underlying integer value for a ResourceId; use for logging only.
- L147 _typedef_ `using FPassInputDecl = TVariant<FPassInternalResourceDesc, FPassExternalResourceDesc, const FCompositeCorePassProxy*>;` (scope `UE::CompositeCore`) — Pass input declaration, referring to internal textures, external textures or the output of another pass proxy.
- L150 _typedef_ `using FPassInputDeclArray = TArray<FPassInputDecl>;` (scope `UE::CompositeCore`) — Array of pass input declarations.
- L153 _prototype_ `FPassInputDeclArray GetDefaultInputDeclArray();` (scope `UE::CompositeCore`) — Returns a default input array declaring one internal texture resource.
- L163 _prototype_ `FPassInputDecl MakeInternalInput(int32 Index = 0, bool bOriginalCopyBeforePasses = false);` (scope `UE::CompositeCore`) — Build an input declaration referencing an internal post-processing texture by index.
- L166 _prototype_ `FPassInputDecl MakeExternalInput(ResourceId Id);` (scope `UE::CompositeCore`) — Build an input declaration referencing an external texture by ResourceId.
- L169 _prototype_ `FPassInputDecl MakePassInput(const FCompositeCorePassProxy* Pass);` (scope `UE::CompositeCore`) — Build an input declaration referencing the output of another pass proxy.
- L192 _typedef_ `using FPassInput = FPassTexture;` (scope `UE::CompositeCore`) — Pass texture input definition.
- L507 _macro_ `#define IMPLEMENT_COMPOSITE_PASS(TypeName) const FName& GetTypeName() const override { return GetTypeNameStatic(); } \` — Use this macro to implement the RTTI method for composite render passes. Should only be used on final classes (e.g. if C derives from B which derives from A, we won't be able to query a C* for whether it's a "B"; in other words, A and B should be abstract and C, final). Expands to an override of GetTypeName() plus a static GetTypeNameStatic() accessor usable for type comparison without an instance.
