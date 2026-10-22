# Plugins / AccumulationDOFEditor

- module root: `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOFEditor`
- headers: 6; symbols: 133
- symbol kinds: class=5, delegate=1, function=16, macro=1, member=49, namespace=1, prototype=56, struct=3, typedef=1
- PrivateDependencyModuleNames: AccumulationDOF, CinematicCamera, Core, CoreUObject, Engine, InputCore, LevelEditor, RHI, RenderCore, Renderer, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOFEditor/Private/AccumulationDOFEditorCommands.h` (Private)


#### class `FAccumulationDOFEditorCommands`  
`class FAccumulationDOFEditorCommands : public TCommands<FAccumulationDOFEditorCommands>`  
_L11-27_
- inherits: `TCommands<FAccumulationDOFEditorCommands>`
- L14 _public function_ `FAccumulationDOFEditorCommands() : TCommands<FAccumulationDOFEditorCommands>( TEXT("AccumulationDOFEditor"), LOCTEXT("AccumulationDOFEditorCommandsContext", "Accumulation DOF"), TEXT("LevelViewport"), FAppStyle::GetAppStyleSetName() )`
- L24 _public prototype_ `virtual void RegisterCommands() override;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ToggleAccumulate;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "AccumulationDOFEditor"`

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOFEditor/Private/AccumulationDOFEditorModule.h` (Private)


#### class `FAccumulationDOFEditorModule`  
`class FAccumulationDOFEditorModule : public IModuleInterface`  
_L20-92_
- inherits: `IModuleInterface`
- desc: Editor module for AccumulationDOF viewport integration. Provides DOF preview via the scalability dropdown menu of each editor level viewport.
- L24 _public prototype_ `virtual void StartupModule() override;`
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L29 _public function_ `FAccumulationDOFViewportManager& GetViewportManager()` — Get the viewport manager. Only valid after StartupModule() and before ShutdownModule().
- L36 _public function_ `static FAccumulationDOFEditorModule& Get()` — Get this module's instance
- L44 _private prototype_ `void RegisterViewMenuExtension();` — Register the View menu extension
- L47 _private prototype_ `void UnregisterViewMenuExtension();` — Unregister the View menu extension
- L50 _private prototype_ `void AddAccumulationDOFControls(FToolMenuSection& InSection);` — Add Accumulate checkbox and One-shot button to the section
- L53 _private prototype_ `void AddAccumulationDOFSettingsSubMenu(UToolMenu* Menu);` — Build the settings submenu (Samples, Splat Size)
- L56 _private prototype_ `void OnLevelViewportClientListChanged();` — Called when level viewport client list changes
- L59 _private prototype_ `void OnEngineLoopInitComplete();` — Called when engine loop initialization is complete
- L62 _private prototype_ `void SetupViewportDisplaySettings(FLevelEditorViewportClient* Client);` — Setup viewport display settings from saved config
- L65 _private prototype_ `void EnsureViewportTrackedForPersistence(FLevelEditorViewportClient* Client, TSharedPtr<class SLevelViewport> LevelViewport);` — Ensure viewport is tracked for settings persistence on removal
- L68 _private prototype_ `void ToggleAccumulationForViewport(FLevelEditorViewportClient* ViewportClient);` — Toggle accumulation for a specific viewport client
- L71 _private prototype_ `bool IsAccumulationEnabledForViewport(FLevelEditorViewportClient* ViewportClient) const;` — Check if accumulation is enabled for a specific viewport client
- L74 _private prototype_ `void BindCommands();` — Bind keyboard shortcut commands
- L79 _private member_ `TSharedPtr<FAccumulationDOFViewportManager> ViewportManager;` — Manages per-viewport DOF configurations and extensions
- L82 _private typedef_ `using FViewportPair = TPair<FLevelEditorViewportClient*, FName>;` — Track configured viewports for cleanup
- L85 _private member_ `TArray<FViewportPair> ConfiguredViewports;` — List of configured level editor viewports
- L88 _private member_ `FDelegateHandle ToolMenusStartupCallbackHandle;` — Delegate handle for ToolMenus startup callback
- L91 _private member_ `TSharedPtr<FUICommandList> BoundCommands;` — Command list for keyboard shortcuts

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOFEditor/Private/AccumulationDOFEditorSettings.h` (Private)


#### struct `FAccumulationDOFPerViewportSettingsPair`  
`struct FAccumulationDOFPerViewportSettingsPair`  
_L15-66_
- reflection: `USTRUCT()`
- desc: Pair of viewport identifier and its settings.
- L21 _public member_ `FName ViewportIdentifier;` — `UPROPERTY(config)` — Viewport identifier
- L25 _public member_ `bool bIsEnabled = false;` — `UPROPERTY(config)` — Whether DOF is enabled
- L29 _public member_ `bool bUseCameraSettings = false;` — `UPROPERTY(config)` — Use settings from camera's AccumulationDOFComponent
- L33 _public member_ `int32 NumApertureSamples = 256;` — `UPROPERTY(config)` — Number of aperture samples
- L37 _public member_ `float DOFSplatSize = 0.125f;` — `UPROPERTY(config)` — Splats size (aperture diameter fraction)
- L41 _public member_ `int32 SamplesPerFrame = 2;` — `UPROPERTY(config)` — Samples to render per frame
- L44 _public function_ `FAccumulationDOFViewportSettings ToSettings() const` — Convert to FAccumulationDOFViewportSettings with validated ranges
- L58 _public function_ `void FromSettings(const FAccumulationDOFViewportSettings& Settings)` — Convert from FAccumulationDOFViewportSettings

#### class `UAccumulationDOFLevelViewportSettings`  
`class UAccumulationDOFLevelViewportSettings : public UObject`  
_L72-130_
- reflection: `UCLASS(config = AccumulationDOF)`
- inherits: `UObject`
- desc: Saved per-viewport settings for Accumulation DOF.
- L80 _public member_ `TArray<FAccumulationDOFPerViewportSettingsPair> ViewportsSettings;` — `UPROPERTY(config)` — Settings array
- L83 _public function_ `TOptional<FAccumulationDOFViewportSettings> GetViewportSettings(FName ViewportIdentifier) const` — Get settings for a viewport if they exist
- L105 _public function_ `void SetViewportSettings(FName ViewportIdentifier, const FAccumulationDOFViewportSettings& Settings)` — Set settings for a viewport

#### Free symbols / members of external scopes

- L92 _function_ `` (scope `UAccumulationDOFLevelViewportSettings::GetViewportSettings`)
- L114 _function_ `` (scope `UAccumulationDOFLevelViewportSettings::SetViewportSettings`)

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOFEditor/Private/AccumulationDOFViewportExtension.h` (Private)


#### struct `FCameraParamsSnapshot`  
`struct FCameraParamsSnapshot`  
_L26-42_
- desc: Snapshot of camera parameters for change detection
- L28 _public member_ `FVector Location = FVector::ZeroVector;`
- L29 _public member_ `FRotator Rotation = FRotator::ZeroRotator;`
- L30 _public member_ `float FocusDistance = 0.0f;`
- L31 _public member_ `float Aperture = 0.0f;`
- L32 _public member_ `float FocalLength = 0.0f;`
- L34 _public function_ `bool Equals(const FCameraParamsSnapshot& Other, float Tolerance = 0.01f) const`

#### class `FAccumulationDOFViewportExtension`  
`class FAccumulationDOFViewportExtension : public FSceneViewExtensionBase , public FGCObject`  
_L48-260_
- inherits: `FSceneViewExtensionBase,FGCObject`
- desc: Scene View Extension for viewport-based Accumulation DOF preview. Orchestrates amortized aperture sample rendering for a specific viewport.
- L53 _public prototype_ `FAccumulationDOFViewportExtension(const FAutoRegister& AutoRegister, FLevelEditorViewportClient* AssociatedViewportClient);`
- L54 _public prototype_ `virtual ~FAccumulationDOFViewportExtension();`
- L58 _public function_ `virtual int32 GetPriority() const override`
- L63 _public prototype_ `virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;`
- L64 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L65 _public prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;`
- L67 _public prototype_ `virtual void SubscribeToPostProcessingPass( EPostProcessingPass Pass, const FSceneView& View, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled) override;`
- L77 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L79 _public function_ `virtual FString GetReferencerName() const override`
- L87 _public function_ `FViewportClient* GetAssociatedViewportClient() const` — Get the associated viewport client
- L93 _public prototype_ `void InvalidateViewportClient();` — Invalidate the viewport client pointer (call before removing from manager)
- L96 _public function_ `FAccumulationDOFViewportSettings& GetSettings()` — Get settings
- L102 _public function_ `const FAccumulationDOFViewportSettings& GetSettings() const` — Get settings (const)
- L108 _public prototype_ `void RestartAccumulation();` — Force restart of accumulation
- L111 _public prototype_ `void CaptureOneshot();` — Perform blocking oneshot capture of all samples
- L114 _public prototype_ `float GetProgressFraction() const;` — Get progress fraction (0-1)
- L117 _public prototype_ `bool IsComplete() const;` — Check if accumulation is complete
- L120 _public function_ `bool IsFrozen() const` — Check if preview is frozen (one-shot result preserved from scene changes)
- L123 _public prototype_ `void Unfreeze();` — Unfreeze and restart accumulation
- L128 _private prototype_ `void TickAmortizedRendering();` — Tick amortized rendering (called once per frame)
- L131 _private prototype_ `ACineCameraActor* GetPilotedCineCameraActor() const;` — Get the CineCameraActor being piloted
- L134 _private prototype_ `UCineCameraComponent* GetPilotedCineCameraComponent() const;` — Get CineCameraComponent from piloted camera
- L137 _private prototype_ `UAccumulationDOFComponent* GetPilotedDOFComponent() const;` — Get AccumulationDOFComponent from piloted camera
- L140 _private prototype_ `bool IsViewModeCompatible(const FSceneView& View) const;` — Check if current view mode is compatible with DOF rendering
- L143 _private prototype_ `AccumulationDOF::FApertureSamplerCameraState BuildCameraStateFromViewport() const;` — Build camera state from viewport. Only valid when piloting a CineCameraActor.
- L146 _private prototype_ `UWorld* GetWorld() const;` — Get world from viewport
- L149 _private prototype_ `FScreenPassTexture ProcessAtMotionBlurPass_RenderThread( FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& Inputs);` — Inject callback for post-processing
- L155 _private prototype_ `void OnSceneActorMoved(AActor* Actor);` — Callback when an actor is moved
- L158 _private prototype_ `void OnSceneLevelActorAdded(AActor* Actor);` — Callback when a level actor is added
- L161 _private prototype_ `void OnSceneLevelActorDeleted(AActor* Actor);` — Callback when a level actor is deleted
- L164 _private prototype_ `void OnSceneComponentTransformChanged(USceneComponent* Component, ETeleportType Teleport);` — Callback when a component transform changes
- L167 _private prototype_ `void OnSceneObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& Event);` — Callback when an object property changes
- L170 _private prototype_ `void IncrementInvalidationCounter();` — Increment the scene invalidation counter
- L173 _private prototype_ `bool IsActorRelevantToOurWorld(AActor* Actor) const;` — Check if an actor is relevant to our world
- L176 _private prototype_ `void CheckFrozenCameraStateChanged();` — Check if camera state changed while frozen, unfreeze if so
- L179 _private prototype_ `FCameraParamsSnapshot CaptureCameraParams() const;` — Capture current camera parameters for change detection
- L184 _private member_ `FLevelEditorViewportClient* LinkedViewportClient = nullptr;` — The viewport client this extension is bound to
- L187 _private member_ `bool bIsInvalidated = false;` — Flag set when viewport is invalidated to guard against dangling pointer access
- L190 _private member_ `FAccumulationDOFViewportSettings Settings;` — Per-viewport settings
- L193 _private member_ `TObjectPtr<UApertureSampler> ApertureSampler = nullptr;` — Aperture sampler instance (owns render targets)
- L196 _private member_ `TWeakObjectPtr<UWorld> CachedWorld;` — Cached world reference
- L199 _private member_ `uint64 LastTickFrame = 0;` — Frame counter for single-tick-per-frame detection
- L202 _private member_ `FIntPoint CachedViewportResolution = FIntPoint::ZeroValue;` — Cached viewport resolution for change detection
- L205 _private member_ `FIntRect CachedViewRect;` — Cached view rect from current frame (set in SetupView)
- L208 _private member_ `bool bIsViewModeCompatible = false;` — Whether we're currently in a compatible view mode
- L211 _private member_ `EViewModeIndex CachedViewMode = VMI_Lit;` — Cached view mode for propagating to aperture sampler config
- L214 _private member_ `TWeakObjectPtr<UTextureRenderTarget2D> CachedPreviewTexture;` — Cached preview texture prepared on game thread for render thread injection
- L217 _private member_ `FTextureRHIRef CachedPreviewRHITexture_RenderThread;` — Cached RHI texture for render thread access
- L220 _private member_ `float CachedProgressFraction = 0.0f;` — Cached progress fraction for render thread (avoids race condition)
- L223 _private member_ `bool bCachedIsComplete = false;` — Cached completion state for render thread (avoids race condition)
- L226 _private member_ `bool bCachedIsFrozen = false;` — Cached frozen state for render thread
- L229 _private member_ `float CachedOverscanFraction = 0.0f;` — Cached overscan fraction for render thread (only set when bCropOverscan is true)
- L232 _private member_ `FDelegateHandle OnActorMovedHandle;` — Delegate handle for actor moved events
- L235 _private member_ `FDelegateHandle OnLevelActorAddedHandle;` — Delegate handle for level actor added events
- L238 _private member_ `FDelegateHandle OnLevelActorDeletedHandle;` — Delegate handle for level actor deleted events
- L241 _private member_ `FDelegateHandle OnComponentTransformChangedHandle;` — Delegate handle for component transform changed events
- L244 _private member_ `FDelegateHandle OnObjectPropertyChangedHandle;` — Delegate handle for object property changed events
- L247 _private member_ `uint32 SceneInvalidationCounter = 0;` — Counter incremented when scene changes are detected
- L250 _private member_ `uint32 LastSeenInvalidationCounter = 0;` — Last seen invalidation counter for change detection
- L253 _private member_ `bool bDOFSettingsNeedReinit = false;` — Set when DOF component settings change, forcing full reinit to pick up new config
- L256 _private member_ `bool bIsFrozen = false;` — Frozen state: prevents scene-change resets after one-shot capture
- L259 _private member_ `FCameraParamsSnapshot FrozenCameraParams;` — Cached camera state for detecting Sequencer-driven changes while frozen

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace AccumulationDOF`

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOFEditor/Private/AccumulationDOFViewportManager.h` (Private)


#### class `FAccumulationDOFViewportManager`  
`class FAccumulationDOFViewportManager : public TSharedFromThis<FAccumulationDOFViewportManager>`  
_L19-59_
- inherits: `TSharedFromThis<FAccumulationDOFViewportManager>`
- desc: Manages per-viewport Accumulation DOF configurations and scene view extensions.
- L22 _public prototype_ `FAccumulationDOFViewportManager() = default;`
- L23 _public prototype_ `~FAccumulationDOFViewportManager();`
- L29 _public prototype_ `FAccumulationDOFViewportSettings& FindOrAddViewportSettings(FLevelEditorViewportClient* InViewportClient);` — Find or create configuration for a viewport. Creates a scene view extension if one doesn't exist.
- L32 _public prototype_ `const FAccumulationDOFViewportSettings* GetViewportSettings(const FViewportClient* InViewportClient) const;` — Get settings for a viewport if it's tracked
- L35 _public prototype_ `bool RemoveViewportSettings(const FViewportClient* InViewportClient);` — Remove viewport tracking and cleanup
- L38 _public prototype_ `void RemoveInvalidViewports(const TArray<FLevelEditorViewportClient*>& ValidViewports);` — Remove all extensions for viewports not in the valid list
- L41 _public prototype_ `bool IsTrackingViewport(const FViewportClient* InViewportClient) const;` — Check if viewport is being tracked
- L44 _public prototype_ `void RestartAccumulation(FViewportClient* InViewportClient);` — Force a viewport to restart its accumulation
- L47 _public prototype_ `void CaptureOneshot(FViewportClient* InViewportClient);` — Perform blocking oneshot capture for a viewport
- L50 _public prototype_ `void Unfreeze(FViewportClient* InViewportClient);` — Unfreeze a viewport (clears frozen state and restarts accumulation)
- L53 _public prototype_ `TSharedPtr<FAccumulationDOFViewportExtension> GetViewportExtension(const FViewportClient* InViewportClient) const;` — Get the extension for a viewport if it exists
- L58 _private member_ `TArray<TSharedPtr<FAccumulationDOFViewportExtension, ESPMode::ThreadSafe>> ViewportExtensions;` — SVEs for each tracked viewport

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOFEditor/Private/AccumulationDOFViewportSettings.h` (Private)


#### struct `FAccumulationDOFViewportSettings`  
`struct FAccumulationDOFViewportSettings`  
_L10-26_
- desc: Per-viewport settings for Accumulation DOF preview.
- L13 _public member_ `bool bIsEnabled = false;` — Accumulation DOF is enabled for this viewport
- L16 _public member_ `bool bUseCameraSettings = false;` — Use settings from camera's AccumulationDOFComponent instead of overrides below
- L19 _public member_ `int32 NumApertureSamples = 256;` — Number of aperture samples to accumulate
- L22 _public member_ `float DOFSplatSize = 0.125f;` — Fraction of main aperture diameter for DOF splat size. Expected range 0-1, clamped by UI.
- L25 _public member_ `int32 SamplesPerFrame = 2;` — Number of samples to render per frame in amortized mode.

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAccumulationDOFSettingsChanged, const FAccumulationDOFViewportSettings&);` — Delegate for settings changes
- L29 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAccumulationDOFSettingsChanged, const FAccumulationDOFViewportSettings&);` — Delegate for settings changes
