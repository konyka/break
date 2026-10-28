# Plugins / ViewportWidgetOverlay

- module root: `Plugins/VirtualProduction/ViewportWidgetOverlay/Source/ViewportWidgetOverlay`
- headers: 7; symbols: 139
- symbol kinds: class=3, delegate=1, enum=1, enumerator=5, function=11, macro=4, member=39, namespace=8, prototype=62, struct=4, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, LevelEditor, Projects, RHI, RenderCore, Renderer, Slate, SlateCore, UnrealEd, ViewportInteraction
- PublicDependencyModuleNames: Core, CoreUObject, Engine, UMG

### `Plugins/VirtualProduction/ViewportWidgetOverlay/Source/ViewportWidgetOverlay/Private/LogViewportWidgetOverlay.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogViewportWidgetOverlay, Log, Log);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogViewportWidgetOverlay, Log, Log);`

### `Plugins/VirtualProduction/ViewportWidgetOverlay/Source/ViewportWidgetOverlay/Private/Misc/PostProcessSceneViewExtension.h` (Private)


#### class `UE::ViewportWidgetOverlay::Private::FPostProcessSceneViewExtension`  
`class FPostProcessSceneViewExtension : public FSceneViewExtensionBase`  
_L23-41_
- inherits: `FSceneViewExtensionBase`
- desc: Renders a post process material over the entirety of the screen. This method differs from adding a post process material as blend material to a cine camera by ignoring anamorphic squeeze. If the Anamorphic Squeeze == 1, both methods produce the same output; if anamorphic squeeze != 1, the cine camera will smallen the viewport vertically (adding black bars to the top and bottom) and render the blend material. This method will render the post process material over the entire area of the viewport (over the black bars as well). Intended to be used with a post process material that renders a widget over the viewport, e.g. useful for pixel streaming.
- L25 _private typedef_ `using Super = FSceneViewExtensionBase;`
- L28 _public prototype_ `FPostProcessSceneViewExtension(const FAutoRegister& AutoRegister, UTextureRenderTarget2D& WidgetRenderTarget);`
- L31 _public prototype_ `virtual void PostRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;`
- L32 _public prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;`
- L38 _private member_ `TWeakObjectPtr<UTextureRenderTarget2D> WidgetRenderTarget;` — Contains the widget that is supposed to be overlaid.
- L40 _private prototype_ `void RenderMaterial_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& InView, FRDGTextureRef ViewFamilyTexture);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ViewportWidgetOverlay` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::ViewportWidgetOverlay`)

### `Plugins/VirtualProduction/ViewportWidgetOverlay/Source/ViewportWidgetOverlay/Private/ViewportWidgetOverlayModule.h` (Private)


#### class `UE::ViewportWidgetOverlay::FViewportWidgetOverlayModule`  
`class FViewportWidgetOverlayModule : public IModuleInterface`  
_L9-17_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ViewportWidgetOverlay` (scope `UE`)

### `Plugins/VirtualProduction/ViewportWidgetOverlay/Source/ViewportWidgetOverlay/Public/Misc/ViewportWidgetOverlay_PostProcess.h` (Public)


#### struct `FViewportWidgetOverlay_PostProcess`  
`struct FViewportWidgetOverlay_PostProcess : public FViewportWidgetOverlay_PostProcessBase`  
_L17-72_
- reflection: `USTRUCT()`
- inherits: `FViewportWidgetOverlay_PostProcessBase`
- desc: Renders widget by adding it as a blend material.
- L26 _public member_ `TArray<TObjectPtr<AActor>> ComposureLayerTargets;` — `UE_DEPRECATED(5.7, "Composure layers are no longer supported on the VP Full screen user widget.")` — `UPROPERTY()`
- L29 _public prototype_ `FViewportWidgetOverlay_PostProcess() = default;`
- L30 _public prototype_ `FViewportWidgetOverlay_PostProcess(const FViewportWidgetOverlay_PostProcess&) = default;`
- L31 _public prototype_ `FViewportWidgetOverlay_PostProcess(FViewportWidgetOverlay_PostProcess&&) = default;`
- L32 _public prototype_ `FViewportWidgetOverlay_PostProcess& operator=(const FViewportWidgetOverlay_PostProcess&) = default;`
- L33 _public prototype_ `FViewportWidgetOverlay_PostProcess& operator=(FViewportWidgetOverlay_PostProcess&&) = default;`
- L36 _public prototype_ `void SetCustomPostProcessSettingsSource(TWeakObjectPtr<UObject> InCustomPostProcessSettingsSource);`
- L38 _public prototype_ `bool Display(UWorld* World, UUserWidget* Widget, TAttribute<float> InDPIScale);`
- L41 _public function_ `bool Display(UWorld* World, UUserWidget* Widget, bool bInRenderToTextureOnly, TAttribute<float> InDPIScale)` — `UE_DEPRECATED(5.7, "bInRenderToTextureOnly parameter is deprecated and use method call without that parameter.")`
- L46 _public prototype_ `virtual void Hide(UWorld* World) override;`
- L47 _public prototype_ `void Tick(UWorld* World, float DeltaSeconds);`
- L53 _private member_ `TObjectPtr<UPostProcessComponent> PostProcessComponent = nullptr;` — `UPROPERTY(Transient)` — Post process component used to add the material to the post process chain.
- L57 _private member_ `TObjectPtr<UMaterialInstanceDynamic> PostProcessMaterialInstance;` — `UPROPERTY(Transient)` — The dynamic instance of the material that the render target is attached to.
- L63 _private member_ `TWeakObjectPtr<UObject> CustomPostProcessSettingsSource;` — Optional. Some object that contains a FPostProcessSettings property. These settings will be used for PostProcessMaterialInstance. E.g. VCam uses this to use post process from a specific cine camera.
- L65 _private prototype_ `bool InitPostProcessComponent(UWorld* World);`
- L66 _private prototype_ `bool UpdateTargetPostProcessSettingsWithMaterial();`
- L67 _private prototype_ `void ReleasePostProcessComponent();`
- L69 _private prototype_ `virtual bool OnRenderTargetInited() override;`
- L71 _private prototype_ `FPostProcessSettings* GetPostProcessSettings() const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API VIEWPORTWIDGETOVERLAY_API`

### `Plugins/VirtualProduction/ViewportWidgetOverlay/Source/ViewportWidgetOverlay/Public/Misc/ViewportWidgetOverlay_PostProcessBase.h` (Public)


#### struct `FViewportWidgetOverlay_PostProcessBase`  
`struct FViewportWidgetOverlay_PostProcessBase`  
_L29-135_
- reflection: `USTRUCT()`
- desc: Implements shared widget initialization logic.
- L40 _public member_ `TObjectPtr<UMaterialInterface> PostProcessMaterial;` — `UPROPERTY(EditAnywhere, Category = PostProcess)` — Post process material used to display the widget. SlateUI [Texture] TintColorAndOpacity [Vector] OpacityFromTexture [Scalar]
- L44 _public member_ `FLinearColor PostProcessTintColorAndOpacity;` — `UPROPERTY(EditAnywhere, Category = PostProcess)` — Tint color and opacity for this component.
- L48 _public member_ `float PostProcessOpacityFromTexture;` — `UPROPERTY(EditAnywhere, Category = PostProcess, meta = (ClampMin = 0.0f, ClampMax = 1.0f))` — Sets the amount of opacity from the widget's UI texture to use when rendering the translucent or masked UI to the viewport (0.0-1.0).
- L52 _public member_ `bool bUseWidgetDrawSize;` — `UPROPERTY(EditAnywhere, Category = PostProcess, meta=(InlineEditConditionToggle))` — Whether to overwrite the size of the rendered widget.
- L56 _public member_ `FIntPoint WidgetDrawSize;` — `UPROPERTY(EditAnywhere, Category = PostProcess, meta=(EditCondition= bWidgetDrawSize))` — The size of the rendered widget.
- L60 _public member_ `bool bWindowFocusable;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = PostProcess)` — Is the virtual window created to host the widget focusable?
- L64 _public member_ `EWindowVisibility WindowVisibility;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = PostProcess)` — The visibility of the virtual window created to host the widget.
- L68 _public member_ `bool bReceiveHardwareInput;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category= PostProcess)` — Register with the viewport for hardware input from the mouse and keyboard. It can and will steal focus from the viewport.
- L72 _public member_ `FLinearColor RenderTargetBackgroundColor;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = PostProcess)` — The background color of the render target
- L76 _public member_ `EWidgetBlendMode RenderTargetBlendMode;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = PostProcess)` — The blend mode for the widget.
- L80 _public member_ `TObjectPtr<UTextureRenderTarget2D> WidgetRenderTarget;` — `UPROPERTY(Transient)` — The target to which the user widget is rendered.
- L88 _public member_ `TWeakPtr<FSceneViewport> EditorTargetViewport;` — The viewport to use for displaying. Defaults to GetFirstActiveLevelViewport().
- L91 _public prototype_ `FViewportWidgetOverlay_PostProcessBase();`
- L92 _public prototype_ `virtual ~FViewportWidgetOverlay_PostProcessBase() = default;`
- L95 _public prototype_ `virtual void Hide(UWorld* World);` — Deinits this output type
- L97 _public prototype_ `TSharedPtr<SVirtualWindow> GetSlateWindow() const;`
- L101 _protected prototype_ `bool CreateRenderer(UWorld* World, UUserWidget* Widget, TAttribute<float> InDPIScale);`
- L102 _protected prototype_ `virtual void ReleaseRenderer();`
- L103 _protected prototype_ `void TickRenderer(UWorld* World, float DeltaSeconds);`
- L108 _private member_ `FWidgetRenderer* WidgetRenderer;` — Helper class for drawing widgets to a render target.
- L111 _private member_ `FIntPoint CurrentWidgetDrawSize;` — The size of the rendered widget
- L114 _private member_ `TWeakPtr<SViewport> ViewportWidget;` — The slate viewport we are registered to.
- L116 _private member_ `TSharedPtr<SVirtualWindow> SlateWindow;` — The slate window that contains the user widget content.
- L119 _private member_ `TSharedPtr<UE::VPUtilities::Private::FVPWidgetPostProcessHitTester> CustomHitTestPath;` — Hit tester when we want the hardware input.
- L122 _private function_ `virtual bool OnRenderTargetInited()` — Creates the post process material and sets up its parameters.
- L125 _private prototype_ `FIntPoint CalculateWidgetDrawSize(UWorld* World);` — Determines widget size depending on the viewport type (PIE / Game)
- L126 _private prototype_ `bool IsTextureSizeValid(FIntPoint Size) const;`
- L129 _private prototype_ `void RegisterHitTesterWithViewport(UWorld* World);` — Starts detecting input to viewport and relays it to the user widget.
- L130 _private prototype_ `void UnRegisterHitTesterWithViewport();`
- L132 _private prototype_ `TSharedPtr<SViewport> GetViewport(UWorld* World) const;` — Gets the viewport to register the hit tester with.
- L134 _private prototype_ `float GetDPIScaleForPostProcessHitTester(TWeakObjectPtr<UWorld> World) const;` — Determines the DPI to apply for clicks depending on the type of viewport (PIE / Game).

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace VPUtilities` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::VPUtilities`)
- L23 _macro_ `#define UE_API VIEWPORTWIDGETOVERLAY_API`

### `Plugins/VirtualProduction/ViewportWidgetOverlay/Source/ViewportWidgetOverlay/Public/Misc/ViewportWidgetOverlay_PostProcessWithSVE.h` (Public)


#### struct `FViewportWidgetOverlay_PostProcessWithSVE`  
`struct FViewportWidgetOverlay_PostProcessWithSVE : public FViewportWidgetOverlay_PostProcessBase`  
_L19-43_
- reflection: `USTRUCT()`
- inherits: `FViewportWidgetOverlay_PostProcessBase`
- desc: Renders widget in post process phase by using Scene View Extensions (SVE).
- L23 _public prototype_ `bool Display(UWorld* World, UUserWidget* Widget, TAttribute<float> InDPIScale);`
- L24 _public prototype_ `void Hide(UWorld* World);`
- L25 _public prototype_ `void Tick(UWorld* World, float DeltaSeconds);`
- L34 _public prototype_ `void RegisterIsActiveFunctor(FSceneViewExtensionIsActiveFunctor IsActiveFunctor);` — Registers a functor that will determine whether the SVE will be applied for a given frame. The IsActive functor should only ever return false. If it is fine to render, it should return an empty optional. Functors may be registered before or after the widget is displayed that is before Display(...) is called. All functors are not retained when Hide(...) is called: they are removed
- L39 _private member_ `TSharedPtr<FSceneViewExtensionBase, ESPMode::ThreadSafe> SceneViewExtension;` — Implements the rendering side
- L42 _private member_ `TArray<FSceneViewExtensionIsActiveFunctor> IsActiveFunctorsToRegister;` — Functors registered before we were displayed.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API VIEWPORTWIDGETOVERLAY_API`

### `Plugins/VirtualProduction/ViewportWidgetOverlay/Source/ViewportWidgetOverlay/Public/ViewportWidgetOverlay.h` (Public)


#### enum `EViewportWidgetOverlay_DisplayType`  
`enum class EViewportWidgetOverlay_DisplayType : uint8`  
_L32-45_
- reflection: `UENUM(BlueprintType)`
- L35 _public enumerator_ `Inactive` — Do not display.
- L37 _public enumerator_ `Viewport` — Display on a game viewport.
- L39 _public enumerator_ `PostProcessWithBlendMaterial` — Display by adding post process material via post process volume settings. Widget added only over area rendered by anamorphic squeeze.
- L41 _public enumerator_ `Composure = PostProcessWithBlendMaterial UMETA(Deprecated, DisplayName = "DEPRECATED_Composure")`
- L44 _public enumerator_ `PostProcessSceneViewExtension` — Display by adding post process material via SceneViewExtensions. Widget added over entire viewport ignoring anamorphic squeeze.

#### struct `FViewportWidgetOverlay_Viewport`  
`struct FViewportWidgetOverlay_Viewport`  
_L49-73_
- reflection: `USTRUCT()`
- L53 _public prototype_ `bool Display(UWorld* World, UUserWidget* Widget, TAttribute<float> InDPIScale);`
- L54 _public prototype_ `void Hide(UWorld* World);`
- L61 _public member_ `TWeakPtr<FSceneViewport> EditorTargetViewport;` — The viewport to use for displaying. Defaults to GetFirstActiveLevelViewport().
- L67 _private member_ `TWeakPtr<SConstraintCanvas> FullScreenCanvasWidget;` — Constraint widget that contains the widget we want to display.
- L71 _private member_ `TWeakPtr<SLevelViewport> OverlayWidgetLevelViewport;` — Level viewport the widget was added to.

#### class `UViewportWidgetOverlay`  
`class UViewportWidgetOverlay : public UObject`  
_L79-212_
- reflection: `UCLASS(meta=(ShowOnlyInnerProperties))`
- inherits: `UObject`
- desc: Will set the Widgets on a viewport either by Widgets are first rendered to a render target, then that render target is displayed in the world.
- L84 _public prototype_ `UViewportWidgetOverlay(const FObjectInitializer& ObjectInitializer);`
- L87 _public prototype_ `virtual void BeginDestroy() override;`
- L89 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L93 _public prototype_ `virtual bool Display(UWorld* World);`
- L94 _public prototype_ `virtual void Hide();`
- L95 _public prototype_ `virtual void Tick(float DeltaTime);`
- L98 _public prototype_ `void SetDisplayTypes(EViewportWidgetOverlay_DisplayType InEditorDisplayType, EViewportWidgetOverlay_DisplayType InGameDisplayType, EViewportWidgetOverlay_DisplayType InPIEDisplayType);` — Sets the way the widget is supposed to be displayed
- L106 _public prototype_ `void SetCustomPostProcessSettingsSource(TWeakObjectPtr<UObject> InCustomPostProcessSettingsSource);` — If using EVPWidgetDisplayType::PostProcessWithBlendMaterial, you can specify a custom post process settings that should be modified. By default, a new post process component is added to AWorldSettings. @param InCustomPostProcessSettingsSource An object containing a FPostProcessSettings UPROPERTY()
- L108 _public prototype_ `bool ShouldDisplay(UWorld* World) const;`
- L109 _public prototype_ `EViewportWidgetOverlay_DisplayType GetDisplayType(UWorld* World) const;`
- L110 _public prototype_ `bool IsDisplayed() const;`
- L113 _public function_ `UUserWidget* GetWidget() const` — Get a pointer to the inner widget. Note: This should not be stored!
- L116 _public function_ `TSubclassOf<UUserWidget> GetWidgetClass() const` — Gets the widget class being displayed
- L118 _public prototype_ `void SetWidgetClass(TSubclassOf<UUserWidget> InWidgetClass);` — Sets the widget class to be displayed. This must be called while not widget is being displayed - the class will not be updated while IsDisplayed().
- L120 _public function_ `constexpr static bool DoesDisplayTypeUsePostProcessSettings(EViewportWidgetOverlay_DisplayType Type)`
- L122 _public prototype_ `FViewportWidgetOverlay_PostProcessBase* GetPostProcessDisplayTypeSettingsFor(EViewportWidgetOverlay_DisplayType Type);` — Returns the base post process settings for the given type if DoesDisplayTypeUsePostProcessSettings(Type) returns true.
- L123 _public function_ `FViewportWidgetOverlay_PostProcess& GetPostProcessDisplayTypeWithBlendMaterialSettings()`
- L126 _public function_ `FViewportWidgetOverlay_PostProcess& GetComposureDisplayTypeSettings()` — `UE_DEPRECATED(5.7, "Composure is no longer support for VPFullScreenUserWidgets")`
- L128 _public function_ `FViewportWidgetOverlay_PostProcessWithSVE& GetPostProcessDisplayTypeWithSceneViewExtensionsSettings()`
- L130 _public prototype_ `const FViewportWidgetOverlay_PostProcessBase* GetPostProcessDisplayTypeSettingsFor(EViewportWidgetOverlay_DisplayType Type) const;` — Returns the base post process settings for the given type if DoesDisplayTypeUsePostProcessSettings(Type) returns true.
- L131 _public function_ `const FViewportWidgetOverlay_PostProcess& GetPostProcessDisplayTypeWithBlendMaterialSettings() const`
- L134 _public function_ `const FViewportWidgetOverlay_PostProcess& GetComposureDisplayTypeSettings() const` — `UE_DEPRECATED(5.7, "Composure is no longer support for VPFullScreenUserWidgets")`
- L135 _public function_ `const FViewportWidgetOverlay_PostProcessWithSVE& GetPostProcessDisplayTypeWithSceneViewExtensionsSettings() const`
- L144 _public prototype_ `void SetEditorTargetViewport(TWeakPtr<FSceneViewport> InTargetViewport);` — Sets the TargetViewport to use on both the Viewport and the PostProcess class. Overrides the viewport to use for displaying. Defaults to GetFirstActiveLevelViewport().
- L146 _public prototype_ `void ResetEditorTargetViewport();` — Resets the TargetViewport
- L153 _protected member_ `TSubclassOf<UUserWidget> WidgetClass;` — `UPROPERTY(EditAnywhere, Category = "User Interface")` — The class of User Widget to create and display an instance of
- L157 _protected member_ `EViewportWidgetOverlay_DisplayType EditorDisplayType;` — `UPROPERTY(EditAnywhere, Category = "User Interface")` — The display type when the world is an editor world.
- L161 _protected member_ `EViewportWidgetOverlay_DisplayType GameDisplayType;` — `UPROPERTY(EditAnywhere, Category = "User Interface")` — The display type when the world is a game world.
- L165 _protected member_ `EViewportWidgetOverlay_DisplayType PIEDisplayType;` — `UPROPERTY(EditAnywhere, Category = "User Interface", meta = (DisplayName = "PIE Display Type"))` — The display type when the world is a PIE world.
- L169 _protected member_ `FViewportWidgetOverlay_Viewport ViewportDisplayType;` — `UPROPERTY(EditAnywhere, Category = "Viewport", meta = (ShowOnlyInnerProperties))` — Behavior when the widget should be display by the slate attached to the viewport.
- L173 _protected member_ `FViewportWidgetOverlay_PostProcess PostProcessDisplayTypeWithBlendMaterial;` — `UPROPERTY(EditAnywhere, Category = "Post Process (Blend Material)")` — Behavior when the widget is rendered via a post process material via post process volume settings; the widget is added only over area rendered by anamorphic squeeze.
- L177 _protected member_ `FViewportWidgetOverlay_PostProcessWithSVE PostProcessWithSceneViewExtensions;` — `UPROPERTY(EditAnywhere, Category = "Post Process (Scene View Extensions)")` — Behavior when the widget is rendered via a post process material via SceneViewExtensions; the widget is added over entire viewport, ignoring anamorphic squeeze.
- L179 _protected prototype_ `bool InitWidget();`
- L180 _protected prototype_ `void ReleaseWidget();`
- L182 _protected prototype_ `FVector2D FindSceneViewportSize();`
- L183 _protected prototype_ `float GetViewportDPIScale();`
- L189 _private member_ `TObjectPtr<UUserWidget> Widget;` — `UPROPERTY(Transient, DuplicateTransient)` — The User Widget object displayed and managed by this component
- L193 _private member_ `TWeakObjectPtr<UWorld> World;` — `UPROPERTY(Transient, DuplicateTransient)` — The world the widget is attached to.
- L197 _private member_ `EViewportWidgetOverlay_DisplayType CurrentDisplayType;` — `UPROPERTY(Transient, DuplicateTransient)` — How we currently displaying the widget.
- L200 _private member_ `bool bDisplayRequested;` — The user requested the widget to be displayed. It's possible that some setting are invalid and the widget will not be displayed.
- L207 _private member_ `TWeakPtr<FSceneViewport> EditorTargetViewport;` — The viewport to use for displaying. Defaults to GetFirstActiveLevelViewport().
- L210 _private prototype_ `void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld);`
- L211 _private prototype_ `void OnWorldCleanup(UWorld* InWorld, bool bSessionEnded, bool bCleanupResources);`

#### Free symbols / members of external scopes

- L29 _macro_ `#define UE_API VIEWPORTWIDGETOVERLAY_API`
