# Plugins / Composite

- module root: `Plugins/Compositing/Composite/Source/Composite`
- headers: 37; symbols: 855
- symbol kinds: class=45, delegate=2, enum=19, enumerator=54, function=29, macro=31, member=246, namespace=23, prototype=395, struct=11
- PrivateDependencyModuleNames: CQTest, CameraCalibrationCore, ConcertSyncCore, GeometryCore, LevelEditor, LevelSequence, MediaFrameworkUtilities, MediaProfile, ModelingComponentsEditorOnly, MovieScene, Projects, RHI, RenderCore, Renderer, Sequencer, Slate, SlateCore, SourceControl, UnrealEd, VPRoles
- PublicDependencyModuleNames: CompositeCore, Core, CoreUObject, Engine, GameplayTags, MediaAssets, OpenColorIO

### `Plugins/Compositing/Composite/Source/Composite/Private/Components/CompositePlateTexturePreviewComponent.h` (Private)


#### class `UCompositePlateTexturePreviewComponent`  
`class UCompositePlateTexturePreviewComponent : public UActorComponent`  
_L18-60_
- reflection: `UCLASS()`
- inherits: `UActorComponent`
- desc: A component that is used to display the plate texture of a composite actor's plate layer in the level viewport's 'picture-in-picture' preview widget. Used by keyer passes to allow color picking from raw plate textures instead of from potentially post-processed textures on the composite actor's meshes
- L26 _public prototype_ `virtual bool GetEditorPreviewInfo(float DeltaTime, FMinimalViewInfo& ViewOut) override;` — UActorComponent interface
- L27 _public prototype_ `virtual TSharedPtr<SWidget> GetCustomEditorPreviewWidget() override;`
- L35 _public prototype_ `bool ShowPreview(TObjectPtr<UCompositePassColorKeyer> InRequestingKeyer);` — Displays the plate texture preview in the level editor's 'picture-in-picture' @param InRequestingKeyer The keyer pass on the plate layer that is requesting the preview be displayed @return true if the preview was started
- L38 _public prototype_ `void HidePreview();` — Hides the plate texture preview
- L41 _public function_ `bool IsPreviewActive() const` — Gets whether the plate texture preview is currently being displayed
- L45 _private prototype_ `FLevelEditorViewportClient* GetActiveViewportClient();` — Gets the active level editor viewport client from the level editor
- L50 _private member_ `bool bShowPreview = false;` — Indicates if the preview should be shown
- L53 _private member_ `TOptional<float> CachedCameraPreviewSize = TOptional<float>();` — Cached camera preview size from the editor preferences config, restored when the plate preview is hidden
- L56 _private member_ `TWeakObjectPtr<UCompositeLayerPlate> PlateToPreview = nullptr;` — A reference to the plate whose texture is being previewed
- L59 _private member_ `TSharedPtr<FSlateBrush> PreviewBrush = nullptr;` — The slate brush used to display the preview texture

### `Plugins/Compositing/Composite/Source/Composite/Private/CompositeCVarOverrideManager.h` (Private)


#### class `FCompositeCVarOverrideManager`  
`class FCompositeCVarOverrideManager`  
_L12-46_
- desc: Console variable override manager.
- L16 _public prototype_ `static FCompositeCVarOverrideManager& Get();` — Singleton getter.
- L18 _public prototype_ `FCompositeCVarOverrideManager(const FCompositeCVarOverrideManager&) = delete;`
- L19 _public prototype_ `FCompositeCVarOverrideManager& operator=(const FCompositeCVarOverrideManager&) = delete;`
- L23 _public prototype_ `template <typename T> void Override(const TCHAR* CVarName, T NewValue);` — Overrides a console variable with a new value.
- L26 _public prototype_ `void Restore(const TCHAR* CVarName);` — Restore a specific console variable to its original cached value.
- L29 _public prototype_ `void RestoreAll();` — Restore all overrides to their original values.
- L32 _public prototype_ `void PrintActiveOverrides();` — Debug function to print all active overrides.
- L35 _private prototype_ `FCompositeCVarOverrideManager() = default;`
- L36 _private prototype_ `~FCompositeCVarOverrideManager() = default;`
- L45 _private member_ `TSortedMap<FString, FCachedCVarData> OverrideCache;` — Cached original cvar data

#### struct `FCompositeCVarOverrideManager::FCachedCVarData`  
`struct FCachedCVarData`  
_L38-42_
- L40 _public member_ `IConsoleVariable* CVarPtr = nullptr;`
- L41 _public member_ `FString OriginalValue;`

### `Plugins/Compositing/Composite/Source/Composite/Private/CompositeRenderTargetPool.h` (Private)


#### class `FCompositeRenderTargetPool`  
`class FCompositeRenderTargetPool final : public FGCObject #if WITH_EDITOR , public FTickableEditorObject #endif`  
_L23-130_
- inherits: `FGCObject,FTickableEditorObject`
- desc: While we favor RDG render targets whenever possible, scene captures rely on regular UTextureRenderTarget objects which by definition need to live across multiple renders (each with their own render dependency graphs). This class provides a central location for transient render target management for regular scene captures.
- L30 _public member_ `static const FIntPoint DefaultSize;` — Default render target size/resolution.
- L33 _public prototype_ `static FCompositeRenderTargetPool& Get();` — Static singleton pool getter.
- L43 _public prototype_ `TObjectPtr<UTextureRenderTarget2D> AcquireTarget(const UObject* InAssignee, const FIntPoint& InSize, ETextureRenderTargetFormat InFormat = ETextureRenderTargetFormat::RTF_RGBA16f);` — Acquire new or recyled render target. @param InAssignee Assignee object whose lifetime is to be paired with the transient render target. If the assignee is invalid, we automatically destroy the render target resource. @param InSize Render target texture size. @param InFormat Render target texture format. @return Render target object.
- L54 _public prototype_ `bool ConditionalAcquireTarget(const UObject* InAssignee, TObjectPtr<UTextureRenderTarget2D>& InOutTarget, const FIntPoint& InSize, ETextureRenderTargetFormat InFormat = ETextureRenderTargetFormat::RTF_RGBA16f);` — Conditionally acquire new or recyled render target, only if the size & format are mismatched with the current render target. @param InAssignee Assignee object whose lifetime is to be paired with the transient render target. If the assignee is invalid, we automatically destroy the render target resource. @param InOutTarget Render target object to update. @param InSize Render target texture size. @param InFormat Render target texture format. @return True if the render target object was updated.
- L57 _public prototype_ `bool IsAssignedTarget(const TObjectPtr<UTextureRenderTarget2D>& InTarget) const;` — Check if the render target was created by the pool and is currently assigned.
- L63 _public prototype_ `void ReleaseTarget(TObjectPtr<UTextureRenderTarget2D>& InTarget);` — Release a previously acquired render target, and return it into the pool (for 'Composite.Pool.FramesUntilFlush' number of frames). @param InTarget Render target to release.
- L66 _public prototype_ `void ReleaseAssigneeTargets(UObject* InAssignee);` — Release previously assigned render targets to specified UObject.
- L69 _public prototype_ `void EmptyPool(bool bInForceCollectGarbage = true);` — Destroy available pool render targets.
- L72 _public prototype_ `void Empty();` — Destroy all render targets, both available & assigned.
- L75 _public prototype_ `int32 Num() const;` — Number of managed render targets, both available & assigned.
- L78 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L79 _public prototype_ `virtual FString GetReferencerName() const override;`
- L84 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L85 _public prototype_ `virtual bool IsTickable() const override;`
- L86 _public prototype_ `virtual TStatId GetStatId() const override;`
- L104 _private function_ `friend uint32 GetTypeHash(const FRenderTargetDesc& InTargetDesc)`
- L126 _private member_ `TMap<const FRenderTargetDesc, TArray<FPooledRenderTarget>> PooledTargets;` — Available pooled render targets.
- L129 _private member_ `TMap<TObjectPtr<UTextureRenderTarget2D>, TWeakObjectPtr<const UObject>> AssignedTargets;` — Assigned render targets (to be returned into the pool).

#### struct `FCompositeRenderTargetPool::FRenderTargetDesc`  
`struct FRenderTargetDesc`  
_L93-108_
- desc: Render target descriptor for finding matching available targets in the pool.
- L95 _public member_ `FIntPoint Size;`
- L97 _public member_ `ETextureRenderTargetFormat Format;`
- L99 _public function_ `bool operator==(const FRenderTargetDesc& Rhs) const`

#### struct `FCompositeRenderTargetPool::FPooledRenderTarget`  
`struct FPooledRenderTarget`  
_L111-123_
- desc: Pool render target struct with a stale frame counter.
- L113 _public prototype_ `FPooledRenderTarget() = default;`
- L115 _public function_ `FPooledRenderTarget(TObjectPtr<UTextureRenderTarget2D> InTextureTarget) : Texture(MoveTemp(InTextureTarget))`
- L119 _public member_ `TObjectPtr<UTextureRenderTarget2D> Texture;`
- L121 _public member_ `int32 StaleFrameCount = 0;`

### `Plugins/Compositing/Composite/Source/Composite/Private/CompositeWorldSubsystem.h` (Private)


#### class `UCompositeWorldSubsystem`  
`class UCompositeWorldSubsystem : public UCompositeCoreSubsystem`  
_L16-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCompositeCoreSubsystem`
- desc: Subsystem for composite actors, deriving from the CompositeCore subsystem.
- L22 _public prototype_ `virtual void PostInitialize() override;` — Called once all UWorldSubsystems have been initialized
- L25 _public prototype_ `virtual void PreDeinitialize() override;` — Called once all UWorldSubsystems are about to be deinitialized
- L28 _public prototype_ `void RegisterActor(TWeakObjectPtr<ACompositeActor> InActor);` — Register composite actor.
- L31 _public prototype_ `void UnregisterActor(TWeakObjectPtr<ACompositeActor> InActor);` — Unregister composite actor.
- L34 _public prototype_ `const TSet<TWeakObjectPtr<ACompositeActor>>& GetActors() const;` — Get all registered composite actors.
- L37 _public prototype_ `static bool IsCompositeActorSettingsValid();` — Whether the recommended project settings for Composite actors are set (auto exposure off, screen percentage manual @ 100).
- L41 _private prototype_ `void ValidateCompositeActorSettings();` — Once per editor session, surface a recommendation toast if Composite-actor project settings are not at recommended values.
- L45 _private prototype_ `void CompositeActorSettingsNotification();` — Shows the editor toast that offers to apply the recommended settings.
- L48 _private member_ `TWeakPtr<SNotificationItem> CompositeActorNotificationItem;` — Weak handle to the active recommendation toast so it can be dismissed when acted upon.
- L52 _private member_ `TSet<TWeakObjectPtr<ACompositeActor>> CompositeActors;` — List of registered actors.
- L55 _private member_ `FDelegateHandle RolesChangedDelegateHandle;` — Event delegate for a device VP role change.

### `Plugins/Compositing/Composite/Source/Composite/Public/Components/CompositeDepthMeshComponent.h` (Public)


#### class `UCompositeDepthMeshComponent`  
`class UCompositeDepthMeshComponent : public UStaticMeshComponent`  
_L13-57_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Composite, editinlinenew, HideCategories = (Transform, Tags, Cooking, Physics, LOD, AssetUserData, Navigation), PrioritizeCategories = ("Composite"), meta = (BlueprintSpawnableComponent))`
- inherits: `UStaticMeshComponent`
- L20 _public prototype_ `virtual void PostLoad() override;`
- L24 _public prototype_ `virtual void OnComponentCreated() override;`
- L25 _public prototype_ `virtual void OnRegister() override;`
- L26 _public prototype_ `virtual void OnUnregister() override;`
- L30 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L31 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& InTransactionEvent) override;`
- L36 _public member_ `FIntVector2 GridResolution;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Composite")` — Planar grid mesh resolution.
- L40 _public member_ `TObjectPtr<UTexture> DepthTexture;` — `UPROPERTY(EditAnywhere, Category = "Composite", meta = (AllowedClasses = "/Script/Engine.Texture2D, /Script/Engine.Texture2DDynamic, /Script/Engine.TextureRenderTarget2D, /Script/MediaAssets.MediaTexture"))` — Depth texture sent to material.
- L44 _public member_ `float ScaleFactor = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Composite")` — Scale factor sent to material, to convert depth units into Unreal units.
- L47 _protected prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L51 _private prototype_ `void UpdateMaterial();` — Convert material to MID and update its parameters.
- L55 _private prototype_ `void GenerateGridMesh_Editor();` — Generate our static grid mesh based on the resolution parameters.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Components/CompositeMeshComponent.h` (Public)


#### enum `ECompositeMeshMaterialType`  
`enum class ECompositeMeshMaterialType : uint8`  
_L14-24_
- reflection: `UENUM(BlueprintType)`
- desc: Material selection type for convenience.
- L17 _public enumerator_ `DefaultLitMasked` — Default lit material. Perfect for catching shadows and/or reflections, but poor alpha edge quality due to masked alpha.
- L20 _public enumerator_ `DefaultUnlitAlphaComposite` — Default unlit alpha composite (translucent pre-multiplied alpha) material. Perfect for .
- L23 _public enumerator_ `Custom` — Custom user material

#### class `UCompositeMeshComponent`  
`class UCompositeMeshComponent : public UStaticMeshComponent`  
_L27-73_
- reflection: `UCLASS(MinimalAPI, Blueprintable, ClassGroup = Composite, EditInlineNew)`
- inherits: `UStaticMeshComponent`
- L33 _public prototype_ `virtual void PostInitProperties() override;`
- L34 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L35 _public prototype_ `virtual void PostEditImport() override;`
- L36 _public prototype_ `virtual void PostLoad() override;`
- L40 _public prototype_ `virtual void OnRegister() override;`
- L41 _public prototype_ `virtual void OnUnregister() override;`
- L45 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L50 _public function_ `ECompositeMeshMaterialType GetMaterialType() const` — `UFUNCTION(BlueprintGetter)` — Get material type.
- L54 _public prototype_ `void SetMaterialType(ECompositeMeshMaterialType InMaterialType);` — `UFUNCTION(BlueprintSetter)` — Set material type.
- L58 _protected prototype_ `virtual void CreateRenderState_Concurrent(FRegisterComponentContext* Context) override;`
- L64 _private member_ `ECompositeMeshMaterialType MaterialType;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetMaterialType, BlueprintSetter = SetMaterialType, Category = "Materials", meta = (AllowPrivateAccess))` — Material type selection for easier access to default plugin materials.
- L68 _private member_ `TObjectPtr<UMaterialInterface> DefaultLitMaskedMaterial;` — `UPROPERTY()` — Default masked material.
- L72 _private member_ `TObjectPtr<UMaterialInterface> DefaultUnlitAlphaCompositeMaterial;` — `UPROPERTY()` — Default alpha composite material.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Components/CompositeSceneCapture2DComponent.h` (Public)


#### class `UCompositeSceneCapture2DComponent`  
`class UCompositeSceneCapture2DComponent : public USceneCaptureComponent2D`  
_L13-30_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Composite, EditInlineNew, meta = (BlueprintSpawnableComponent))`
- inherits: `USceneCaptureComponent2D`
- L20 _public prototype_ `virtual void BeginDestroy() override;`
- L23 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L28 _public prototype_ `virtual const AActor* GetViewOwner() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Components/CompositeShadowReflectionCatcherComponent.h` (Public)


#### class `UCompositeShadowReflectionCatcherComponent`  
`class UCompositeShadowReflectionCatcherComponent : public UCompositeSceneCapture2DComponent`  
_L13-17_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Composite, EditInlineNew, meta = (BlueprintSpawnableComponent))`
- inherits: `UCompositeSceneCapture2DComponent`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Components/CompositeViewProjectionComponent.h` (Public)


#### class `UCompositeViewProjectionComponent`  
`class UCompositeViewProjectionComponent : public UActorComponent`  
_L18-106_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, HideCategories = (Activation, Transform, Lighting, Rendering, Tags, Cooking, Physics, LOD, AssetUserData, Navigation), ClassGroup = Composite, meta = (BlueprintSpawnableComponent, DisplayName = "Camera View Projection"))`
- inherits: `UActorComponent`
- desc: Component responsible for continuously updating the specified material parameter collection with a camera view projection matrix (to be used for texture projection in materials).
- L24 _public prototype_ `virtual void PostInitProperties() override;`
- L25 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L26 _public prototype_ `virtual void PostEditImport() override;`
- L27 _public prototype_ `virtual void PostLoad() override;`
- L31 _public prototype_ `virtual void OnRegister() override;`
- L32 _public prototype_ `virtual void OnUnregister() override;`
- L33 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L37 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L43 _public member_ `bool bIsEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "CameraProjection")` — Whether or not the component activates the view-projection matrix Material Parameter Collection update.
- L47 _public member_ `TObjectPtr<UMaterialParameterCollection> MaterialParameterCollection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "CameraProjection")` — The Material Parameter Collection in which the view-projection matrix should be stored.
- L51 _public member_ `FName ViewProjectionMatrixParameter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "CameraProjection")` — Parameter name of the first element of the view projection matrix in the Material Parameter Collection set above.  Requires space for 4 vectors.
- L55 _public member_ `FName ClipToWorldMatrixParameter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "CameraProjection", AdvancedDisplay)` — Parameter name of the first element of the inverse view projection matrix in the Material Parameter Collection set above.  Requires space for 4 vectors.
- L59 _public member_ `FName ScreenToClipMatrixParameter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "CameraProjection", AdvancedDisplay)` — Parameter name of the first element of the screen to clip matrix in the Material Parameter Collection set above.  Requires space for 4 vectors.
- L64 _public prototype_ `void ForceUpdate();` — `UFUNCTION(BlueprintCallable, Category = "CameraProjection")` — Force update the Material Parameter Collection this frame.
- L68 _public prototype_ `UCameraComponent* GetCameraComponent() const;` — `UFUNCTION(BlueprintGetter)` — Camera component getter.
- L72 _public prototype_ `void SetCameraComponent(UCameraComponent* InComponent);` — `UFUNCTION(BlueprintSetter)` — Camera component setter.
- L76 _public prototype_ `const TSoftObjectPtr<AActor>& GetCameraActor();` — `UFUNCTION(BlueprintGetter)` — Camera actor getter.
- L80 _public prototype_ `void SetCameraActor(const TSoftObjectPtr<AActor>& InActor);` — `UFUNCTION(BlueprintSetter)` — Camera actor setter.
- L85 _private member_ `TSoftObjectPtr<AActor> CameraActor;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetCameraActor, BlueprintSetter = SetCameraActor, Category = "CameraProjection", meta = (AllowPrivateAccess))` — The camera whose view-projection matrix is used.
- L90 _private member_ `FComponentReference TargetCameraComponent_DEPRECATED;` — `UE_DEPRECATED(5.8, "TargetCameraComponent has been deprecated, use CameraActor instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "TargetCameraComponent has been deprecated, use CameraActor instead."))`
- L94 _private prototype_ `void InitDefaultCamera();` — Initialize CameraActor from the outer CompositeActor's camera, or default to the owning actor.
- L97 _private prototype_ `void UpdateProjection(UWorld* InWorld) const;` — Update the Material Parameter Collection with the camera view transform information.
- L100 _private member_ `mutable FMatrix LastViewProjectionMatrix = FMatrix::Identity;` — Cached view projection matrix, to avoid needless MPC updates.
- L103 _private member_ `FDelegateHandle OnWorldPreSendAllEndOfFrameUpdatesHandle;` — Post-viewport update callback.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/CompositeActor.h` (Public)


#### struct `FSceneCaptureComponentArray`  
`struct FSceneCaptureComponentArray`  
_L24-30_
- reflection: `USTRUCT()`
- L29 _public member_ `TArray<TObjectPtr<UCompositeSceneCapture2DComponent>> Components;` — `UPROPERTY()`

#### enum `ECompositeMainRenderOutputMode`  
`enum class ECompositeMainRenderOutputMode : uint8`  
_L34-39_
- reflection: `UENUM(BlueprintType)`
- desc: Main render color space & encoding output mode.
- L36 _public enumerator_ `Default UMETA(DisplayName = "Default", ToolTip = "Default output from post-processing's tonemap, usually sRGB display output with tone curve, equivalent to Final Color (LDR) in RGB.")`
- L37 _public enumerator_ `FinalColorHDR UMETA(DisplayName = "HDR Linear", ToolTip = "Linear output from post-processing's tonemap, equivalent to Final Color (HDR) in Linear Working Color Space.")`
- L38 _public enumerator_ `FinalToneCurveHDR UMETA(DisplayName = "HDR Linear with Tone Curve", ToolTip = "Linear with tone curve output from post-processing's tonemap, equivalent to Final Color (with tone curve) in Linear sRGB gamut.")`

#### enum `ECompositeAllowedViewModes`  
`enum class ECompositeAllowedViewModes : uint8`  
_L45-50_
- reflection: `UENUM(BlueprintType)`
- desc: Constrain composite render to certain view modes for multi-viewport workflows where unlit or wireframe viewports will not conflict with the composite.
- L47 _public enumerator_ `Default UMETA(ToolTip = "Compositing is allowed on viewports with Lit, Path Tracing or Unknown view modes.")`
- L48 _public enumerator_ `MediaProfileUnknown UMETA(DisplayName = "Media Profile (Unknown)", ToolTip = "Compositing is only allowed with the Unknown view mode, the default when media profile does its own rendering.")`
- L49 _public enumerator_ `AllViewModes UMETA(ToolTip = "Compositing is allowed with all view modes.")`

#### class `ACompositeActor`  
`class ACompositeActor : public AActor`  
_L54-280_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- desc: Actor used to control properties of the composite pipeline.
- L60 _public prototype_ `ACompositeActor(const FObjectInitializer& ObjectInitializer);` — Constructor.
- L63 _public prototype_ `~ACompositeActor();` — Destructor.
- L66 _public prototype_ `virtual void PostLoad() override;`
- L70 _public prototype_ `virtual void PreRegisterAllComponents() override;`
- L71 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L72 _public prototype_ `virtual void UnregisterAllComponents(bool bForReregister = false) override;`
- L73 _public prototype_ `virtual void PostUnregisterAllComponents() override;`
- L74 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L75 _public prototype_ `virtual void Destroyed() override;`
- L79 _public prototype_ `virtual void PreDuplicateFromRoot(FObjectDuplicationParameters& DupParams) override;`
- L80 _public prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L81 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L82 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedChainEvent) override;`
- L83 _public prototype_ `virtual void PreEditUndo() override;`
- L84 _public prototype_ `virtual void PostEditUndo() override;`
- L85 _public prototype_ `virtual void SetIsTemporarilyHiddenInEditor(bool bIsHidden) override;`
- L86 _public prototype_ `virtual bool ShouldTickIfViewportsOnly() const override;`
- L91 _public prototype_ `bool GetIsActive() const;` — `UFUNCTION(BlueprintGetter)` — Get the (locally) active state.
- L95 _public prototype_ `void SetIsActive(bool bInActive);` — `UFUNCTION(BlueprintSetter)` — Set the (locally) active state.
- L99 _public prototype_ `bool GetIsEnabled() const;` — `UFUNCTION(BlueprintGetter)` — Get the enabled state.
- L103 _public prototype_ `void SetIsEnabled(bool bInEnabled);` — `UFUNCTION(BlueprintSetter, CallInEditor)` — Set the enabled state.
- L107 _public prototype_ `UCameraComponent* GetCameraComponent() const;` — `UFUNCTION(BlueprintGetter)` — Camera component getter.
- L111 _public prototype_ `void SetCameraComponent(UCameraComponent* InComponent);` — `UFUNCTION(BlueprintSetter)` — Camera component setter.
- L115 _public prototype_ `const TSoftObjectPtr<AActor>& GetCameraActor() const;` — `UFUNCTION(BlueprintGetter)` — Camera actor getter.
- L119 _public prototype_ `void SetCameraActor(const TSoftObjectPtr<AActor>& InActor);` — `UFUNCTION(BlueprintSetter, CallInEditor)` — Camera actor setter.
- L123 _public prototype_ `void ClearCameraActor();` — `UFUNCTION(BlueprintCallable, Category = "Composite")` — Clear the camera actor and any stored spawnable binding. Use this rather than SetCameraActor(nullptr) to fully clear; SetCameraActor(nullptr) preserves the binding so Tick can re-resolve through sequencer despawns.
- L127 _public prototype_ `TArray<UCompositeLayerBase*> GetCompositeLayers();` — `UFUNCTION(BlueprintGetter)` — Get the composite layers.
- L130 _public prototype_ `const TArray<TObjectPtr<UCompositeLayerBase>>& GetCompositeLayers() const;` — Get the composite layers.
- L134 _public prototype_ `void SetCompositeLayers(TArray<UCompositeLayerBase*> InLayers);` — `UFUNCTION(BlueprintSetter)` — Set the composite layers.
- L138 _public prototype_ `FGameplayTag GetVPRole() const;` — `UFUNCTION(BlueprintGetter)` — Get the vp role.
- L142 _public prototype_ `void SetVPRole(FGameplayTag Value);` — `UFUNCTION(BlueprintSetter)` — Set the vp role.
- L150 _public prototype_ `bool ShowPlatePreview(TObjectPtr<class UCompositePassColorKeyer> InRequestingKeyer);` — Displays the plate texture preview in the level editor's 'picture-in-picture' @param InRequestingKeyer The keyer pass on the plate layer that is requesting the preview be displayed @return true if the preview was started
- L152 _public prototype_ `void HidePlatePreview();` — Hides the plate texture preview
- L155 _public prototype_ `bool IsPlatePreviewActive() const;` — Gets whether the plate texture preview is currently being displayed
- L161 _private member_ `TObjectPtr<class UCompositeViewProjectionComponent> ViewProjectionComponent;` — `UPROPERTY(Instanced)` — Component responsible for continuously updating a material parameter collection with the composite camera view projection matrix.
- L166 _private member_ `TObjectPtr<class UCompositePlateTexturePreviewComponent> PlatePreviewComponent;` — `UPROPERTY(Transient)` — Component used to preview a plate layer texture in the level viewport
- L171 _private member_ `bool bIsActive;` — `UPROPERTY(NonTransactional, EditInstanceOnly, BlueprintGetter = GetIsActive, BlueprintSetter = SetIsActive, Category = "Composite", meta = (AllowPrivateAccess = true))` — Whether or not the composite behavior is active locally - used primarily for multi-user.
- L175 _private member_ `bool bIsEnabled;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetIsEnabled, BlueprintSetter = SetIsEnabled, Interp, Category = "Composite", meta = (DisplayName = "Enabled", AllowPrivateAccess = true, DisplayPriority = "0"))` — Whether or not the composite behavior is enabled.
- L180 _private member_ `TSoftObjectPtr<AActor> CameraActor;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetCameraActor, BlueprintSetter = SetCameraActor, Interp, Category = "Composite", meta = (AllowPrivateAccess))` — The primary camera used for the composite. Used by the camera view projection component for continuous view-projection matrix updates.
- L184 _private member_ `FCompositeSpawnableBinding CameraSpawnableBinding;` — `UPROPERTY()` — Spawnable binding for the camera actor. Used to resolve spawnable cameras across reloads.
- L188 _public function_ `bool HasSpawnableBinding() const` — Returns true if the actor has a stored spawnable camera binding.
- L191 _public prototype_ `void DetectAndStoreSpawnableBinding(AActor* InActor);` — Detect if a camera actor is a sequencer spawnable and store its binding info.
- L196 _private member_ `TArray<TObjectPtr<UCompositeLayerBase>> CompositeLayers;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetCompositeLayers, BlueprintSetter = SetCompositeLayers, Instanced, Category = "Composite", meta = (DisplayName = "Layers"))` — Array of composite layers for merging or processing images.
- L201 _public member_ `bool bEnableScreenSpaceReflections;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite", AdvancedDisplay)` — Also provide the post-processing composite graph to SSR input.
- L205 _public member_ `bool bOverridesViewUserFlags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite", AdvancedDisplay)` — Override default view user flags.
- L209 _public member_ `int32 ViewUserFlags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", AdvancedDisplay, meta = (EditCondition = "bOverridesViewUserFlags"))` — Custom user flags value used to alter materials in the composite render pass. Set to one by default such that branching can be used in Lit materials.
- L213 _public member_ `ECompositeMainRenderOutputMode MainRenderOutput;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite", AdvancedDisplay)` — Main render color space & encoding output mode.
- L217 _public member_ `ECompositeAllowedViewModes AllowedViewModes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite", AdvancedDisplay)` — Constrain composite rendering to specific view modes.
- L226 _public member_ `bool bRestrictToActiveViewport;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite", AdvancedDisplay)` — When true, compositing is restricted to a single viewport: the one piloting CameraActor if any, otherwise the active level viewport (editor only). Use for multi-viewport setups to avoid scene-capture conflicts (e.g. Shadow Reflection Catcher), since per-actor captures render once per frame from a single camera. No effect in standalone/cooked builds.
- L235 _private member_ `FGameplayTag VPRole;` — `UPROPERTY(EditAnywhere, BlueprintGetter = "GetVPRole", BlueprintSetter = "SetVPRole", Category = "Composite", AdvancedDisplay, meta = (DisplayName = "VP Role"))` — Optional virtual production role to deactivate the actor when its role does not match the current device role. When unspecified, activation is unmodified (on load) or re-activated (on property change).
- L240 _public prototype_ `template<class RetType> RetType* FindOrCreateSceneCapture(const UCompositePassBase* InPass, int32 InIndex = 0, FName InBaseName = NAME_None);` — Convenience function used by passes or layers to request a scene capture component.
- L243 _public prototype_ `void DestroySceneCaptures(const UCompositePassBase* InPass);` — Convenience function used by passes or layers to remove scene capture components.
- L246 _public prototype_ `bool IsRendering() const;` — Returns true if the composite is actively rendering.
- L249 _public prototype_ `bool IsInVPRole() const;` — Check if the actor's role matches the session role.
- L253 _private prototype_ `void PropagateStateChange(ECompositeStateChangeType ChangeType);` — Propagate rendering state changes to layers and the composite core subsystem.
- L257 _private member_ `TMap<TWeakObjectPtr<const UCompositePassBase>, FSceneCaptureComponentArray> SceneCapturesPerPass;` — `UPROPERTY()` — Pass-managed scene capture components (populated at runtime by FindOrCreateSceneCapture).
- L262 _private member_ `FComponentReference Camera_DEPRECATED;` — `UE_DEPRECATED(5.8, "Camera has been deprecated, use CameraActor instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Camera has been deprecated, use CameraActor instead."))`
- L265 _private member_ `TArray<UCompositeLayerBase*> PreEditCompositeLayers;` — Used to update components after we remove layers.
- L268 _private member_ `FGameplayTag PreEditVPRole;` — Used to track changes to the VP role.
- L272 _private member_ `bool bIsModifyingAProperty;` — Flag used to determine in which cases we should ignore PostRegister / Unregister calls.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/CompositeAssetUserData.h` (Public)


#### class `UCompositeAssetUserData`  
`class UCompositeAssetUserData : public UAssetUserData`  
_L16-27_
- reflection: `UCLASS()`
- inherits: `UAssetUserData`
- desc: AssetUserData to keep track of edits on composite meshes.
- L22 _public member_ `FOnPostEditChangeOwner OnPostEditChangeOwner;` — Bind to this to get a callback when something is changed on the associated component.
- L25 _public prototype_ `virtual void PostEditChangeOwner(const FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPostEditChangeOwner, UPrimitiveComponent& );`
- L10 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPostEditChangeOwner, UPrimitiveComponent& );`

### `Plugins/Compositing/Composite/Source/Composite/Public/CompositeDepthMeshActor.h` (Public)


#### class `ACompositeDepthMeshActor`  
`class ACompositeDepthMeshActor : public AActor`  
_L16-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- desc: Convenience compositing depth mesh actor. This actor must still be assigned to a plate layer.
- L21 _public prototype_ `ACompositeDepthMeshActor(const FObjectInitializer& ObjectInitializer);`
- L22 _public prototype_ `~ACompositeDepthMeshActor();`
- L27 _private member_ `TObjectPtr<UCompositeDepthMeshComponent> CompositeDepthMeshComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Composite", meta = (AllowPrivateAccess = "true"))` — Composite mesh component.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/CompositeMeshActor.h` (Public)


#### class `ACompositeMeshActor`  
`class ACompositeMeshActor : public AActor`  
_L16-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- desc: Convenience compositing mesh actor. This actor must still be assigned to a plate layer.
- L21 _public prototype_ `ACompositeMeshActor(const FObjectInitializer& ObjectInitializer);`
- L22 _public prototype_ `~ACompositeMeshActor();`
- L27 _private member_ `TObjectPtr<UCompositeMeshComponent> CompositeMeshComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Composite", meta = (AllowPrivateAccess = "true"))` — Composite mesh component.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/CompositeModule.h` (Public)


#### class `FCompositeModule`  
`class FCompositeModule : public IModuleInterface`  
_L13-26_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _private prototype_ `void OnAllModuleLoadingPhasesComplete();` — Engine all module loaded callback
- L25 _private prototype_ `void OnEnginePreExit();` — Engine pre-exit callback

#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogComposite, Log, All);`
- L11 _delegate_ `DECLARE_STATS_GROUP(TEXT("Composite"), STATGROUP_Composite, STATCAT_A`

### `Plugins/Compositing/Composite/Source/Composite/Public/CompositeSkySphereActor.h` (Public)


#### class `ACompositeSkySphereActor`  
`class ACompositeSkySphereActor : public AActor`  
_L23-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- desc: Convenience actor providing image-based lighting from a plate texture. Wraps an inverted sphere mesh and a real-time skylight. Assign Texture and a sky sphere material with a "CompositeTexture" parameter to get image- based lighting from footage.
- L28 _public prototype_ `ACompositeSkySphereActor(const FObjectInitializer& ObjectInitializer);`
- L29 _public prototype_ `~ACompositeSkySphereActor();`
- L32 _public prototype_ `virtual void OnConstruction(const FTransform& Transform) override;`
- L33 _public prototype_ `virtual void PostLoad() override;`
- L34 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L39 _public prototype_ `void SetTexture(UTexture* InTexture);` — `UFUNCTION(BlueprintCallable, Category = "Texture")` — Sets the sky sphere texture and immediately updates the material.
- L43 _public function_ `UTexture* GetTexture() const` — `UFUNCTION(BlueprintPure, Category = "Texture")` — Returns the current sky sphere texture.
- L47 _public member_ `FName TextureParameterName = TEXT("Com` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")` — Name of the texture parameter in the sky sphere material to receive Texture.
- L50 _public prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;`
- L51 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L58 _private prototype_ `void UpdateMaterial();` — Updates the sky sphere MID with the current Texture value.
- L61 _private prototype_ `void TryOpenMediaProfileSource();` — If Texture is a MediaTexture from the active Media Profile, registers this actor as a consumer.
- L64 _private prototype_ `void TryCloseMediaProfileSource();` — Unregisters this actor as a consumer of any Media Profile source it previously opened.
- L69 _private member_ `TObjectPtr<UTexture> Texture;` — `UPROPERTY(EditAnywhere, Category = "Texture", meta = (AllowPrivateAccess = "true", AllowedClasses = "/Script/Engine.Texture2D,/Script/Engine.Texture2DDynamic,/Script/Engine.TextureRenderTarget2D,/Script/MediaAssets.MediaTexture"))` — Texture to drive the sky sphere material's "CompositeTexture" parameter.
- L73 _private member_ `TObjectPtr<UStaticMeshComponent> SkySphereComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Composite", meta = (AllowPrivateAccess = "true"))` — Sky sphere mesh component.
- L77 _private member_ `TObjectPtr<USkyLightComponent> SkyLightComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Composite", meta = (AllowPrivateAccess = "true"))` — Real-time skylight that captures the sky sphere for IBL.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/CompositeSpawnableBinding.h` (Public)


#### struct `FCompositeSpawnableBinding`  
`struct FCompositeSpawnableBinding`  
_L23-40_
- reflection: `USTRUCT()`
- desc: Stores the sequencer binding information needed to re-resolve a spawnable actor after its transient instance is destroyed (e.g. on level reload or sequence restart).
- L29 _public member_ `FGuid BindingId;` — `UPROPERTY()` — Binding GUID of the actor within the level sequence.
- L33 _public member_ `TSoftObjectPtr<ULevelSequence> LevelSequence;` — `UPROPERTY()` — Level sequence containing the spawnable binding.
- L36 _public prototype_ `bool IsValid() const;` — Returns true if this binding has been populated with valid data.
- L39 _public prototype_ `void Invalidate();` — Reset the binding to an invalid state.

#### struct `FCompositeSpawnableBindings`  
`struct FCompositeSpawnableBindings`  
_L50-104_
- reflection: `USTRUCT()`
- desc: Helper that manages a parallel array of spawnable bindings alongside a TArray<TSoftObjectPtr<AActor>>.  Provides detect, sync, and resolve operations so that each layer only needs one-liner calls at its existing lifecycle points (setter, PreEditChange, PostEditChangeProperty, PostEditUndo, OnEndOfFrameUpdate).
- L59 _public prototype_ `bool HasBindingAt(int32 Index) const;` — True if a spawnable binding is stored at Index. Used by details-panel customizations to detect entries that should surface a [Pending Spawnable] hint — the caller is responsible for first checking that the corresponding actor soft pointer is unresolved.
- L66 _public prototype_ `bool TryResolveStale(TArray<TSoftObjectPtr<AActor>>& Actors, UWorld* InWorld) const;` — Resolve stale actor soft pointers from their stored bindings. Returns true if at least one actor was resolved (callers may want to re-apply side effects such as scene-capture component updates).
- L75 _public prototype_ `bool TickResolveStale(TArray<TSoftObjectPtr<AActor>>& Actors, UWorld* InWorld, uint32 InstanceId) const;` — Throttled wrapper around TryResolveStale for per-frame contexts (Tick / OnEndOfFrameUpdate). Fires once every 60 frames (≈1 Hz at 60 FPS; scales with frame rate at higher refresh rates, which is intentional — the throttle is a per-frame amortization, not a wall-clock cadence). The frame phase is salted by InstanceId so different instances don't all hit Sequencer/world iteration on the same frame. Pass the owning UObject's GetUniqueID().
- L81 _public prototype_ `void CachePreEditState(TArrayView<const TSoftObjectPtr<AActor>> Actors);` — Cache pre-edit state. Call before any operation that will replace the actor array (PreEditChange, Blueprint/C++ setter) so that SyncOnPropertyChange can diff against it.
- L90 _public prototype_ `void SyncOnPropertyChange(TArrayView<TSoftObjectPtr<AActor>> NewActors, UWorld* InWorld);` — Sync bindings after the actor array has been replaced, using the state cached by CachePreEditState. Carries over existing bindings for actors whose soft path is unchanged, detects bindings for newly resolved actors, and leaves the side-channel empty for stale entries with no prior binding. Call AFTER the internal setter has applied the new array.
- L95 _private member_ `TArray<FCompositeSpawnableBinding> Bindings;` — `UPROPERTY()` — Parallel array of bindings; entry i corresponds to actor i in the owning layer's actor array.
- L103 _private member_ `TMap<FSoftObjectPath, FCompositeSpawnableBinding> PreEditBindingsByPath;` — Pre-edit bindings keyed by their actor's soft path, populated by CachePreEditState and consumed by SyncOnPropertyChange to carry bindings across path-stable edits. Only entries whose binding was valid at cache time are stored; nullptr/empty paths and invalid bindings are filtered out at cache time.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API COMPOSITE_API`
- L106 _namespace_ `namespace UE`
- L106 _namespace_ `namespace Composite` (scope `UE`)
- L109 _prototype_ `FCompositeSpawnableBinding DetectSpawnableBinding(AActor* InActor, UWorld* InWorld);` (scope `UE::Composite`) — Detect if an actor is a sequencer spawnable. Returns a valid binding or an empty struct.
- L112 _prototype_ `AActor* TryResolveSpawnable(const FCompositeSpawnableBinding& Binding, UWorld* InWorld);` (scope `UE::Composite`) — Resolve a spawnable actor from binding data. Returns nullptr if unresolved.

### `Plugins/Compositing/Composite/Source/Composite/Public/Layers/CompositeLayerBase.h` (Public)


#### enum `ECompositeStateChangeType`  
`enum class ECompositeStateChangeType : uint8`  
_L19-27_
- desc: Describes the intent of a rendering state change propagated to layers.
- L22 _public enumerator_ `Activate` — Show meshes, register primitives (activate rendering).
- L24 _public enumerator_ `Deactivate` — Hide meshes, unregister primitives (deactivate rendering).
- L26 _public enumerator_ `Release` — Restore mesh visibility, unregister primitives (removal/destruction cleanup).

#### class `UCompositeLayerBase`  
`class UCompositeLayerBase : public UCompositePassBase`  
_L34-122_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew)`
- inherits: `UCompositePassBase`
- desc: Base class for a composite layer: a named unit that merges an input into the composite stack and runs sub-passes on it. Subclasses spawn a per-frame render proxy via GetProxy() and own a list of UCompositePassBase to apply after merging.
- L40 _public prototype_ `UCompositeLayerBase(const FObjectInitializer& ObjectInitializer);` — Constructor.
- L43 _public prototype_ `virtual ~UCompositeLayerBase();` — Destructor.
- L46 _public prototype_ `virtual void PostLoad() override;`
- L47 _public prototype_ `virtual void BeginDestroy() override;`
- L50 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L51 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L59 _public function_ `virtual void OnEndOfFrameUpdate(UWorld* InWorld)` — End-of-frame update callback to inherit. Called when enabled by RegisterEndOfFrameUpdate.
- L65 _public function_ `virtual void OnRenderingStateChange(ECompositeStateChangeType ChangeType)` — Called when composite actor rendering state changes. @param ChangeType - Activation, deactivation or release state.
- L72 _public function_ `virtual void OnRemoved(ACompositeActor* LastOwner)` — Called when the layer is removed or composite actor is destroyed. @param LastOwner - Last composite actor owner, from which the layer was removed. Ignore if null.
- L75 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;` — Override to return a render-thread proxy for this layer. Proxy objects should be allocated from the provided allocator. Only called when GetIsActive() returns true.
- L79 _protected prototype_ `static void UpdateSceneCaptureComponents(USceneCaptureComponent2D& SceneCaptureComponent, TArrayView<TSoftObjectPtr<AActor>> InActors);` — Convenience function to update scene capture primitive components, depending on the scene capture primitive render mode.
- L82 _protected prototype_ `void RegisterEndOfFrameUpdate(bool bInEnabled);` — Activate the end-of-frame update callback.
- L87 _public member_ `bool bIsSolo = false;` — `UPROPERTY()` — Whether or not the pass is solo.
- L92 _public member_ `FString Name_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use DisplayName instead."))` — Deprecated layer display name, use UCompositePassBase::DisplayName.
- L97 _public member_ `ECompositeCoreMergeOp Operation = ECompositeCoreMergeOp::Over;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (DisplayPriority = "3"))` — Merge operation applied on Input0 with Input1.
- L102 _public member_ `TArray<TObjectPtr<UCompositePassBase>> LayerPasses;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Composite", meta = (DisallowedClasses = "/Script/Composite.CompositeLayerBase, /Script/Composite.CompositePassDistortion"))` — Sub-passes applied to this layer's input before it is merged into the composite stack.
- L105 _public prototype_ `void AddChildPasses(UE::CompositeCore::FPassInputDecl& InBasePassInput, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator, TArrayView<const TObjectPtr<UCompositePassBase>> InPasses) const;` — Convenience function to register post-processing child passes.
- L108 _public member_ `static constexpr int32 FixedNumLayerInputs = 2;` — Fixed number of inputs used by layer merge passes.
- L111 _public prototype_ `ECompositeCoreMergeOp GetMergeOperation(const FCompositeTraversalContext& InContext) const;` — Convenience function that returns the merge operation depending on the traversal context.
- L114 _public prototype_ `UE::CompositeCore::FPassInputDecl GetDefaultSecondInput(const FCompositeTraversalContext& InContext) const;` — Convenience function that returns the default secondary input depending on the traversal context.
- L118 _private prototype_ `void ConditionalOnEndOfFrameUpdate(UWorld* InWorld);` — Private end of frame callback implementation to condition the inherited function.
- L121 _private member_ `FDelegateHandle OnWorldPreSendAllEndOfFrameUpdatesHandle;` — Post-viewport update callback.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Layers/CompositeLayerMainRender.h` (Public)


#### class `UCompositeLayerMainRender`  
`class UCompositeLayerMainRender : public UCompositeLayerBase`  
_L16-40_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta = (DisplayName = "Main Render"))`
- inherits: `UCompositeLayerBase`
- desc: Layer that fetches scene color from the main render during post-processing after tonemap. Preferable (for performance and rendering systems) to use the main render instead of additional scene captures.
- L22 _public prototype_ `UCompositeLayerMainRender(const FObjectInitializer& ObjectInitializer);` — Constructor.
- L25 _public prototype_ `virtual ~UCompositeLayerMainRender();` — Destructor.
- L28 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;` — Getter function to override, returning pass layer proxies to be passed to the render thread. (Proxy objects should be allocated from the provided allocator.)
- L39 _public member_ `bool bUltimatteBlend = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", AdvancedDisplay, meta = (DisplayName = "Ultimatte Blend"))` — When enabled, blending with the layer beneath is performed in sRGB display color space rather than linear. Required to match the 2D-plate Ultimatte path when composite meshes use a translucent grayscale holdout. Additional Ultimatte requirements: - "Encoding Override" should be set to "Linear" on the (alpha) key media source to avoid color decoding. - On the Plate layer feeding the composite meshes, use an Ultimatte Masking pass to mask the fill texture with the alpha key texture.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Layers/CompositeLayerPlanarReflection.h` (Public)


#### class `UCompositeLayerPlanarReflection`  
`class UCompositeLayerPlanarReflection : public UCompositeLayerBase`  
_L21-119_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta = (DisplayName = "Planar Reflection"))`
- inherits: `UCompositeLayerBase`
- desc: Layer that renders a planar reflection of selected actors via a mirrored scene capture. The result is blended as a reflection contribution onto the layer below.
- L27 _public prototype_ `UCompositeLayerPlanarReflection(const FObjectInitializer& ObjectInitializer);` — Constructor.
- L30 _public prototype_ `virtual ~UCompositeLayerPlanarReflection();` — Destructor.
- L32 _public prototype_ `virtual void OnRemoved(ACompositeActor* LastOwner) override;`
- L35 _public prototype_ `virtual void BeginDestroy() override;`
- L38 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L39 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L40 _public prototype_ `virtual void PostEditUndo() override;`
- L41 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L46 _public prototype_ `virtual void OnEndOfFrameUpdate(UWorld* InWorld) override;` — End-of-frame update callback.
- L48 _public prototype_ `virtual bool GetIsActive() const override;`
- L49 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L53 _public prototype_ `const TArray<TSoftObjectPtr<AActor>> GetActors() const;` — `UFUNCTION(BlueprintGetter)` — Get reflection & shadow caster actors.
- L57 _public prototype_ `void SetActors(TArray<TSoftObjectPtr<AActor>> InActors);` — `UFUNCTION(BlueprintSetter)` — Set reflection & shadow caster actors.
- L61 _public prototype_ `bool IsCustomRenderPass() const;` — `UFUNCTION(BlueprintGetter)` — Get whether the planar reflection is rendered as a custom render pass.
- L65 _public prototype_ `void SetCustomRenderPass(bool bInIsFastRenderPass);` — `UFUNCTION(BlueprintSetter)` — Set whether the planar reflection is rendered as a custom render pass.
- L69 _public function_ `FIntPoint GetRenderTargetResolution() const` — `UFUNCTION(BlueprintGetter)` — Get the render target resolution for the planar reflection.
- L73 _public prototype_ `void SetRenderTargetResolution(FIntPoint InRenderTargetResolution);` — `UFUNCTION(BlueprintSetter)` — Set the render target resolution for the planar reflection.
- L77 _public function_ `float GetReflectionStrength() const` — `UFUNCTION(BlueprintGetter)` — Get the planar reflection strength.
- L81 _public prototype_ `void SetReflectionStrength(float InReflectionStrength);` — `UFUNCTION(BlueprintSetter)` — Set the planar reflection strength.
- L86 _private prototype_ `class UCompositeSceneCapture2DComponent* GetSceneCaptureComponent() const;` — Convenience function to access the actor-managed planar reflection component.
- L89 _private prototype_ `void UpdatePlanarReflectionTransform(USceneCaptureComponent2D* CaptureComponent);` — Update the scene capture transform for planar reflection.
- L92 _private prototype_ `void SetActorsInternal(TArray<TSoftObjectPtr<AActor>> InActors);` — Apply actor-change side effects without touching spawnable bindings.
- L96 _private member_ `TArray<TSoftObjectPtr<AActor>> Actors;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetActors, BlueprintSetter = SetActors, Category = "Composite", meta = (AllowPrivateAccess = true))` — List of actors to be rendered from the planar reflection.
- L100 _private member_ `FCompositeSpawnableBindings SpawnableBindings;` — `UPROPERTY()` — Parallel spawnable binding data for the Actors array.
- L104 _private member_ `FIntPoint RenderTargetResolution;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetRenderTargetResolution, BlueprintSetter = SetRenderTargetResolution, Interp, Category = "Composite", meta = (AllowPrivateAccess = true))` — Render target resolution for the planar reflection.
- L108 _private member_ `float ReflectionStrength = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetReflectionStrength, BlueprintSetter = SetReflectionStrength, Interp, Category = "Composite", meta = (AllowPrivateAccess = true, ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Strength of the planar reflection.
- L112 _private member_ `float PlaneHeight = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (AllowPrivateAccess = true))` — World-space Z coordinate of the horizontal plane for planar reflection. Note that we currently do not clip against this plane.
- L116 _private member_ `bool bCustomRenderPass;` — `UPROPERTY(EditAnywhere, BlueprintGetter = IsCustomRenderPass, BlueprintSetter = SetCustomRenderPass, Category = "Composite", AdvancedDisplay, meta = (AllowPrivateAccess = true))` — Convenience toggle to render the planar reflection as a fast/minimal Custom Render Pass, inlined in the main render & without support for lighting.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Layers/CompositeLayerPlate.h` (Public)


#### enum `ECompositePlateMode`  
`enum class ECompositePlateMode : uint8`  
_L22-26_
- reflection: `UENUM(BlueprintType)`
- desc: Plate sampling & rendering mode.
- L24 _public enumerator_ `Texture = 0 UMETA(ToolTip = "Sample the texture directly in 2D screen space.")`
- L25 _public enumerator_ `CompositeMesh = 1 UMETA(ToolTip = "Sample the composite meshes rendered in a built-in custom render pass (default). Automatic fallback to Texture.")`

#### struct `FCompositeMeshPrimitiveReference`  
`struct FCompositeMeshPrimitiveReference`  
_L29-40_
- reflection: `USTRUCT()`
- L35 _public member_ `TSoftObjectPtr<AActor> CompositeMeshActor;` — `UPROPERTY()` — The actor whose primitives will be used for the composite meshes
- L39 _public member_ `TArray<TSoftObjectPtr<UPrimitiveComponent>> CompositeMeshPrimitives;` — `UPROPERTY()` — The primitives to use for the composite meshes

#### class `UCompositeLayerPlate`  
`class UCompositeLayerPlate : public UCompositeLayerBase, public FTickableGameObject`  
_L54-355_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta = (DisplayName = "Plate"))`
- inherits: `UCompositeLayerBase,FTickableGameObject`
- desc: Layer that renders a media texture into the composite stack, with optional scene projection via composite meshes. With composite meshes and default plugin materials, the media texture is projected into the scene. These meshes are rendered separately in a custom render pass without post-processing. By default, they are also marked as holdout such that the plate layer can be composited under the main render. Without composite meshes, the plate layer can be used solely as a 2D layer. In this case however, interactions between CG and media in the scene are lost.
- L60 _public member_ `static const FLazyName CompositeTextureName;` — Composite (media) texture material parameter name.
- L63 _public prototype_ `UCompositeLayerPlate(const FObjectInitializer& ObjectInitializer);` — Constructor.
- L66 _public prototype_ `virtual ~UCompositeLayerPlate();` — Destructor.
- L68 _public prototype_ `virtual void OnRemoved(ACompositeActor* LastOwner) override;`
- L70 _public prototype_ `virtual void OnRenderingStateChange(ECompositeStateChangeType ChangeType) override;`
- L73 _public prototype_ `virtual void SetIsEnabled(bool bInEnabled) override;` — Set the enabled state.
- L76 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L78 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L79 _public function_ `virtual bool IsTickableInEditor() const override`
- L80 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L81 _public prototype_ `virtual bool IsTickable() const override;`
- L83 _public prototype_ `virtual UWorld* GetTickableGameObjectWorld() const override;`
- L84 _public prototype_ `virtual TStatId GetStatId() const override;`
- L88 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;` — Getter function to override, returning pass layer proxies to be passed to the render thread. (Proxy objects should be allocated from the provided allocator.)
- L91 _public prototype_ `TArray<UPrimitiveComponent*> GetPrimitives() const;` — Get array of all composite mesh primitives.
- L94 _public prototype_ `TArray<UPrimitiveComponent*> GetPrimitivesForActor(TSoftObjectPtr<AActor> InActor) const;` — Get list of composite mesh primitives for a specified composite mesh actor
- L98 _public prototype_ `TArray<UPrimitiveComponent*> GetIncludedPrimitivesForActor(TSoftObjectPtr<AActor> InActor) const;` — Gets the list of primitives that are specifically included for the composite mesh actor. Differs from GetPrimitivesForActor in that this returns an empty list if no primitives are specifically included, whereas GetPrimitivesForActor falls back to all primitives
- L101 _public prototype_ `void SetPrimitiveIncluded(UPrimitiveComponent* InPrimitive, bool bInIncluded);` — Sets whether a composite mesh actor's primitive should be included as a composite mesh primitive or not
- L105 _public prototype_ `virtual void PostLoad() override;`
- L106 _public prototype_ `virtual void BeginDestroy() override;`
- L109 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L110 _public prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;`
- L111 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L112 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& InTransactionEvent) override;`
- L120 _public prototype_ `const TArray<TSoftObjectPtr<AActor>> GetCompositeMeshes() const;` — `UFUNCTION(BlueprintGetter)` — Get composite meshes.
- L124 _public prototype_ `void SetCompositeMeshes(TArray<TSoftObjectPtr<AActor>> InCompositeMeshes);` — `UFUNCTION(BlueprintSetter)` — Set composite meshes.
- L128 _public function_ `ECompositePlateMode GetPlateMode() const` — `UFUNCTION(BlueprintGetter)` — Get the plate sampling & rendering mode
- L132 _public prototype_ `void SetPlateMode(ECompositePlateMode InPlateMode);` — `UFUNCTION(BlueprintSetter)` — Set the plate sampling & rendering mode
- L136 _public function_ `bool GetIsHoldoutEnabled() const` — `UFUNCTION(BlueprintGetter)` — Get whether primitive alpha holdout is active for composite meshes in the main render.
- L140 _public prototype_ `void SetIsHoldoutEnabled(bool bInIsHoldoutEnabled);` — `UFUNCTION(BlueprintSetter)` — Set whether primitive alpha holdout is active for composite meshes in the main render.
- L144 _public function_ `bool GetControlMeshVisibility() const` — `UFUNCTION(BlueprintGetter)` — Get whether plate layers automatically control the visibility of registered composite meshes.
- L151 _public prototype_ `void SetControlMeshVisibility(bool bInControlMeshVisibility);` — `UFUNCTION(BlueprintSetter)` — Set whether plate layers automatically control the visibility of registered composite meshes: turned invisible if the layer or actor is disabled or hidden. Disabling restores visibility on all registered composite meshes.
- L155 _public prototype_ `UTexture* GetCompositeTexture() const;` — `UFUNCTION(BlueprintCallable, Category = "Composite")` — Returns the media texture, optionally pre-processed with layer & scene-only passes into a render target.
- L160 _private member_ `TArray<TSoftObjectPtr<AActor>> CompositeMeshes;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetCompositeMeshes, BlueprintSetter = SetCompositeMeshes, Category = "Composite", meta = (AllowPrivateAccess = true))` — Actors whose primitive mesh components will be marked as primitive alpha holdout, and rendered separately with the projected (media) texture.
- L164 _private member_ `TArray<FCompositeMeshPrimitiveReference> CompositeMeshPrimitives;` — `UPROPERTY()` — A list of actual primitives from the composite mesh actors that will be marked as primitive alpha holdout, and rendered separately with the projected (media) texture
- L168 _private member_ `FCompositeSpawnableBindings SpawnableBindings;` — `UPROPERTY()` — Parallel spawnable binding data for the CompositeMeshes array.
- L173 _public member_ `TObjectPtr<UTexture> Texture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite", meta = (AllowedClasses="/Script/Engine.Texture2D, /Script/Engine.Texture2DDynamic, /Script/Engine.TextureRenderTarget2D, /Script/MediaAssets.MediaTexture"))` — Media texture for compositing layer.
- L181 _public member_ `TArray<TObjectPtr<UCompositePassBase>> MediaPasses;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Composite", meta = (DisallowedClasses = "/Script/Composite.CompositeLayerBase, /Script/Composite.CompositePassDistortion"))` — Media texture pre-processing passes, applied before rendering. The texture is replaced with an internal render target.
- L193 _public member_ `TArray<TObjectPtr<UCompositePassBase>> ScenePasses;` — `UPROPERTY(BlueprintReadWrite, Instanced, Category = "Composite", meta = (AllowedClasses = "/Script/Composite.CompositePassDistortion", DisallowedClasses = "/Script/Composite.CompositeLayerBase"))` — Passes applied after media passes, onto composite meshes only. The texture is replaced with an internal render target. NOTE: Set the plate "Mode" to "Texture" in order to skip these scene passes during final compositing in post-processing. We now have an automatic scene pass to undistort a plate projected onto composite meshes. Using Texture mode can therefore avoid the automatic undistort -> distort pipeline.
- L198 _private member_ `ECompositePlateMode PlateMode;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetPlateMode, BlueprintSetter = SetPlateMode, Interp, Category = "Composite", AdvancedDisplay, meta = (AllowPrivateAccess = true, DisplayName = "Mode"))` — The plate sampling & rendering mode: direct texture sampling or separate composite mesh render.
- L208 _private member_ `bool bIsHoldoutEnabled;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetIsHoldoutEnabled, BlueprintSetter = SetIsHoldoutEnabled, Interp, Category = "Composite", AdvancedDisplay, meta = (AllowPrivateAccess = true))` — Composite meshes are marked as primitive alpha holdout for the main render. This is default-enabled to bypass post-processing on media pixels, primarily to avoid temporal upscaling artifacts and the tone curve. However when working in 3D, holdout can be disabled to only preserve the plate projection functionality and media passes.
- L212 _private member_ `bool bControlMeshVisibility;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetControlMeshVisibility, BlueprintSetter = SetControlMeshVisibility, Category = "Composite", AdvancedDisplay, meta = (AllowPrivateAccess = true))` — When enabled, the plate layers automatically control the visibility of registered composite meshes. Disabling restores visibility on all registered composite meshes.
- L227 _public member_ `bool bUltimatteBlend = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", AdvancedDisplay, meta = (DisplayName = "Ultimatte Blend"))` — When enabled, blending with the background is performed in sRGB display color space rather than linear. Use for Ultimatte Key & Fill workflows where the content is in display space. Additional Ultimatte requirements: - "Encoding Override" should be set to "Linear" on the (alpha) key media source to avoid color decoding. - Use an Ultimatte Masking pass to mask the fill texture with the alpha key texture. Note: With composite meshes acting as holdouts, Ultimatte Blend needs to be set on the main render layer instead.
- L235 _public member_ `bool bRemoveOverscan = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", AdvancedDisplay)` — Automatically remove overscan from the media texture by reading the camera's overscan value. This inserts an implicit media pass that scales the footage to counteract the overscan expansion. Has no effect when the camera overscan is zero.
- L239 _private prototype_ `void AppendIncludedPrimitivesForActor(const TSoftObjectPtr<AActor>& InActor, TArray<UPrimitiveComponent*>& OutPrimitiveComponents) const;` — Append specifically-included primitives for InActor to OutPrimitiveComponents. Empty if none are specifically included.
- L242 _private prototype_ `void AppendPrimitivesForActor(const TSoftObjectPtr<AActor>& InActor, TArray<UPrimitiveComponent*>& OutPrimitiveComponents) const;` — Append effective primitives for InActor to OutPrimitiveComponents (included, or all valid as fallback).
- L245 _private prototype_ `void SetCompositeMeshesInternal(TArray<TSoftObjectPtr<AActor>> InCompositeMeshes);` — Apply composite-mesh-change side effects without touching spawnable bindings.
- L248 _private prototype_ `void TryRegisterCompositePrimitives(const TArray<UPrimitiveComponent*>& InPrimitives, const UWorld* SourceWorld = nullptr) const;` — Condtionally register composite mesh primitives: active holdout and add to the scene view extension custom render pass.
- L251 _private prototype_ `void UnregisterCompositePrimitives(const TArray<UPrimitiveComponent*>& InPrimitives, const UWorld* SourceWorld = nullptr) const;` — Unregister composite mesh primitives: deactive holdout and remove from the scene view extension custom render pass.
- L254 _private prototype_ `void UpdateCompositeMeshes(bool bRegisterOnly = false) const;` — Update the (media) texture on all composite meshes. We also add a user asset data to track changes.
- L257 _private prototype_ `void UpdatePrimitiveComponent(UPrimitiveComponent& InPrimitiveComponent) const;` — Update the (media) texture on a primitive component.
- L260 _private prototype_ `void PropagateStateChange(ECompositeStateChangeType ChangeType, const UWorld* SourceWorld) const;` — Propagate rendering state change to composite meshes.
- L263 _private prototype_ `bool IsCompositeMeshActorAlreadyInUse(TSoftObjectPtr<AActor> InCompositeMeshActor) const;` — Convenience function verify if the composite mesh actor is already in use by another layer.
- L266 _private prototype_ `TSet<UPrimitiveComponent*> GetPrimitivesUsedByOtherActors() const;` — Get set of primitives already in use by other actors.
- L269 _private prototype_ `TObjectPtr<UTextureRenderTarget2D> GetOrCreateRenderTarget(TObjectPtr<UTextureRenderTarget2D>& InRenderTarget) const;` — Convenience function to get or create the specified render target at composite actor resolution.
- L272 _private prototype_ `int32 GetValidPrimitivesNum() const;` — Get number of valid primitives.
- L275 _private prototype_ `int32 GetValidPassesNum(TArrayView<const TObjectPtr<UCompositePassBase>> InPasses) const;` — Get number of valid passes.
- L278 _private prototype_ `void TryOpenMediaProfileSource();` — If Texture is a media profile media texture, attempt to open the associated media source
- L281 _private prototype_ `void TryCloseMediaProfileSource();` — Attempt to close any media profile sources being played for this plate
- L284 _private prototype_ `bool IsRendering() const;` — Returns true if the plate layer is actively rendering.
- L288 _private prototype_ `int32 FindLastValidPassIndex(TArrayView<const TObjectPtr<UCompositePassBase>> InPasses) const;` — Convenience function to find the last valid pass.
- L291 _private prototype_ `UE::CompositeCore::ResourceId AddPreprocessingPasses( FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator, TArrayView<const TObjectPtr<UCompositePassBase>> InPasses, UE::CompositeCore::ResourceId TextureId, UE::CompositeCore::ResourceId OriginalTextureId, TFunction<TObjectPtr<UTextureRenderTarget2D>()> GetRenderTargetFn ) const;` — Convenience function to register pre-processing child passes.
- L302 _private member_ `TArray<TSoftObjectPtr<AActor>> PreEditCompositeMeshes;` — Pre-edit list of registered composite meshes.
- L305 _private member_ `TArray<FCompositeMeshPrimitiveReference> PreSaveCompositeMeshPrimitives;` — Transient copy of CompositeMeshPrimitives that keeps non-valid soft pointers during a save as they will be removed from CompositeMeshPrimitives during saving
- L310 _private prototype_ `void OnPreSaveWorld(UWorld* InWorld, FObjectPreSaveContext ObjectSaveContext);` — Called before a level saves.
- L315 _private prototype_ `void OnPostSaveWorld(UWorld* InWorld, FObjectPostSaveContext ObjectSaveContext);` — Called after a level has saved.
- L322 _private prototype_ `void OverrideTranslucencyConsoleVariables(bool bOverride) const;` — Override the required translucency console variables. These overrides are needed to avoid double depth-of-field on keyed footaged + composite meshes.
- L325 _private prototype_ `bool HasAfterDOFTranslucentMaterial() const;` — Returns true if any composite mesh primitive in this layer currently uses at least one AfterDOF translucent material.
- L328 _private prototype_ `void UpdateTranslucencyOverride() const;` — Pushes or releases the translucency CVar overrides based on whether AfterDOF translucent materials are currently present in this layer.
- L331 _private prototype_ `bool IsUsingAfterDOFTranslucency(UMaterialInterface* MaterialInterface) const;` — Convenience function to check if the material is AfterDOF translucent.
- L335 _private member_ `mutable TObjectPtr<UTextureRenderTarget2D> MediaRenderTarget;` — `UPROPERTY(Transient, NonTransactional)` — Processed media texture render target.
- L339 _private member_ `mutable TObjectPtr<UTextureRenderTarget2D> SceneRenderTarget;` — `UPROPERTY(Transient, NonTransactional)` — Processed media texture with additional passes only for scene composite meshes.
- L343 _private member_ `TObjectPtr<UCompositePassTransform2D> OverscanPass;` — `UPROPERTY(Transient, NonTransactional)` — Internal pass to automatically remove overscan from the media texture. Not serialized.
- L346 _private member_ `int32 CachedValidMediaPasses = 0;` — Cached number of valid media passes.
- L349 _private member_ `int32 CachedValidScenePasses = 0;` — Cached number of valid scene passes.
- L352 _private member_ `mutable bool bRebindRenderTarget = false;` — Toggled when a render target is resized to trigger a mesh material texture parameter rebind in Tick.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Layers/CompositeLayerProcessing.h` (Public)


#### class `UCompositeLayerProcessing`  
`class UCompositeLayerProcessing : public UCompositeLayerBase`  
_L16-34_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta = (DisplayName = "Processing"))`
- inherits: `UCompositeLayerBase`
- desc: Layer that runs sub-passes on the output of previous layers without merging an additional input. Useful for inserting transforms or color operations between merged layers.
- L22 _public prototype_ `UCompositeLayerProcessing(const FObjectInitializer& ObjectInitializer);` — Constructor.
- L25 _public prototype_ `virtual ~UCompositeLayerProcessing();` — Destructor.
- L28 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;` — Getter function to override, returning pass layer proxies to be passed to the render thread. (Proxy objects should be allocated from the provided allocator.)
- L31 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const;`
- L32 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Layers/CompositeLayerSceneCapture.h` (Public)


#### class `UCompositeLayerSceneCapture`  
`class UCompositeLayerSceneCapture : public UCompositeLayerBase`  
_L21-133_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta = (DisplayName = "Scene Capture"))`
- inherits: `UCompositeLayerBase`
- desc: Layer that renders selected primitives through a scene capture (or inlined custom render pass) and merges the result. By default, registered primitives are hidden from the main render so they are rendered exclusively into this capture.
- L27 _public prototype_ `UCompositeLayerSceneCapture(const FObjectInitializer& ObjectInitializer);` — Constructor.
- L30 _public prototype_ `virtual ~UCompositeLayerSceneCapture();` — Destructor.
- L32 _public prototype_ `virtual void OnRemoved(ACompositeActor* LastOwner) override;`
- L35 _public prototype_ `virtual void BeginDestroy() override;`
- L38 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L39 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L40 _public prototype_ `virtual void PreEditUndo() override;`
- L41 _public prototype_ `virtual void PostEditUndo() override;`
- L42 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L47 _public prototype_ `virtual void OnEndOfFrameUpdate(UWorld* InWorld) override;` — End-of-frame update callback.
- L49 _public prototype_ `virtual bool GetIsActive() const override;`
- L50 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L54 _public prototype_ `const TArray<TSoftObjectPtr<AActor>> GetActors() const;` — `UFUNCTION(BlueprintGetter)` — Get reflection & shadow caster actors.
- L58 _public prototype_ `void SetActors(TArray<TSoftObjectPtr<AActor>> InActors);` — `UFUNCTION(BlueprintSetter)` — Set reflection & shadow caster actors.
- L62 _public prototype_ `bool IsCustomRenderPass() const;` — `UFUNCTION(BlueprintGetter)` — Get whether the scene capture is rendered as a custom render pass.
- L66 _public prototype_ `void SetCustomRenderPass(bool bInIsFastRenderPass);` — `UFUNCTION(BlueprintSetter)` — Set whether the scene capture is rendered as a custom render pass.
- L70 _public prototype_ `bool IsVisibleInSceneCaptureOnly() const;` — `UFUNCTION(BlueprintGetter)` — Get whether registered meshes are marked as visible in scene capture only.
- L74 _public prototype_ `void SetVisibleInSceneCaptureOnly(bool bInVisible);` — `UFUNCTION(BlueprintSetter)` — Set whether registered meshes are marked as visible in scene capture only.
- L78 _public function_ `FIntPoint GetRenderTargetResolution() const` — `UFUNCTION(BlueprintGetter)` — Get the render target resolution for the scene capture.
- L82 _public prototype_ `void SetRenderTargetResolution(FIntPoint InRenderTargetResolution);` — `UFUNCTION(BlueprintSetter)` — Set the render target resolution for the scene capture.
- L87 _private prototype_ `class UCompositeSceneCapture2DComponent* GetSceneCaptureComponent() const;` — Convenience function to access the actor-managed scene capture component.
- L90 _private prototype_ `void UpdatePrimitiveVisibilityState(bool bInVisibleInSceneCaptureOnly) const;` — Update scene capture visibility on registered mesh actors primitives.
- L93 _private prototype_ `void RestorePrimitiveVisibilityState() const;` — Restore scene capture visibility on registered mesh actors primitives.
- L96 _private prototype_ `void SetActorsInternal(TArray<TSoftObjectPtr<AActor>> InActors);` — Apply actor-change side effects (visibility, scene capture update) without touching spawnable bindings.
- L104 _private member_ `TArray<TSoftObjectPtr<AActor>> Actors;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetActors, BlueprintSetter = SetActors, Category = "Composite", meta = (AllowPrivateAccess = true))` — List of actors to be rendered from the scene capture. Automatically sets the scene capture's ShowOnlyComponents when updated.
- L108 _private member_ `FCompositeSpawnableBindings SpawnableBindings;` — `UPROPERTY()` — Parallel spawnable binding data for the Actors array.
- L113 _private member_ `TMap<TWeakObjectPtr<UPrimitiveComponent>, bool> CachedVisibilityInSceneCapture;` — `UE_DEPRECATED(5.8, "CachedVisibilityInSceneCapture is now deprecated.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "CachedVisibilityInSceneCapture is now deprecated."))`
- L118 _private member_ `FIntPoint RenderTargetResolution;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetRenderTargetResolution, BlueprintSetter = SetRenderTargetResolution, Interp, Category = "Composite", meta = (AllowPrivateAccess = true))` — Render target resolution for the scene capture.
- L122 _private member_ `bool bVisibleInSceneCaptureOnly;` — `UPROPERTY(EditAnywhere, BlueprintGetter = IsVisibleInSceneCaptureOnly, BlueprintSetter = SetVisibleInSceneCaptureOnly, Category = "Composite", meta = (AllowPrivateAccess = true))` — Visibility setting applied to registered actors. By default, registered meshes will only be visible in scene captures and no longer in the main render.
- L130 _private member_ `bool bCustomRenderPass;` — `UPROPERTY(EditAnywhere, BlueprintGetter = IsCustomRenderPass, BlueprintSetter = SetCustomRenderPass, Category = "Composite", meta = (AllowPrivateAccess = true))` — Convenience toggle to render the scene capture as a fast/minimal Custom Render Pass, inlined in the main render & without support for lighting. Automatically sets the scene capture's CaptureSource, bRenderInMainRenderer & bIgnoreScreenPercentage when updated.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Layers/CompositeLayerShadowReflection.h` (Public)


#### enum `ECompositeHiddenInSceneCaptureConfiguration`  
`enum class UE_DEPRECATED(5.8, "ECompositeHiddenInSceneCaptureConfiguration is now deprecated.") ECompositeHiddenInSceneCaptureConfiguration : uint8`  
_L23-28_
- reflection: `UENUM(BlueprintType)`
- desc: Automatic primitive configuration mode for registered primitives.
- L25 _public enumerator_ `None UMETA(ToolTip = "No primitive properties are updated")`
- L26 _public enumerator_ `Visible UMETA(ToolTip = "The following properties are set to false: bHiddenInSceneCapture, bAffectIndirectLightingWhileHidden & bCastHiddenShadow.")`
- L27 _public enumerator_ `Hidden UMETA(ToolTip = "The following properties are set to true: bHiddenInSceneCapture, bAffectIndirectLightingWhileHidden & bCastHiddenShadow.")`

#### struct `FCompositeShadowReflectionPrimitiveState`  
`struct UE_DEPRECATED(5.8, "FCompositeShadowReflectionPrimitiveState is now deprecated.") FCompositeShadowReflectionPrimitiveState`  
_L32-47_
- reflection: `USTRUCT()`
- desc: Primitive visibility settings cached state.
- L38 _public member_ `bool bHiddenInSceneCapture = false;` — `UPROPERTY()` — Hidden in scene capture.
- L42 _public member_ `bool bAffectIndirectLightingWhileHidden = false;` — `UPROPERTY()` — Affect indirect lighting while hidden.
- L46 _public member_ `bool bCastHiddenShadow = false;` — `UPROPERTY()` — Cast hidden shadow.

#### class `UCompositeLayerShadowReflection`  
`class UCompositeLayerShadowReflection : public UCompositeLayerBase`  
_L54-162_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta = (DisplayName = "Shadow Reflection Catcher"))`
- inherits: `UCompositeLayerBase`
- desc: Layer that catches shadows and reflections received by registered primitives, producing a matte that is merged onto the plate. Implemented with two scene captures (one with the primitives, one without); the ratio of their results yields a multiplicative matte.
- L60 _public prototype_ `UCompositeLayerShadowReflection(const FObjectInitializer& ObjectInitializer);` — Constructor.
- L63 _public prototype_ `virtual ~UCompositeLayerShadowReflection();` — Destructor.
- L65 _public prototype_ `virtual void OnRemoved(ACompositeActor* LastOwner) override;`
- L68 _public prototype_ `virtual void PostLoad() override;`
- L69 _public prototype_ `virtual void BeginDestroy() override;`
- L72 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L73 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L74 _public prototype_ `virtual void PreEditUndo() override;`
- L75 _public prototype_ `virtual void PostEditUndo() override;`
- L76 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L81 _public prototype_ `virtual void OnEndOfFrameUpdate(UWorld* InWorld) override;` — End-of-frame update callback.
- L83 _public prototype_ `virtual bool GetIsActive() const override;`
- L84 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L88 _public function_ `FIntPoint GetRenderTargetResolution() const` — `UFUNCTION(BlueprintGetter)` — Get the render target resolution for the scene captures.
- L92 _public prototype_ `void SetRenderTargetResolution(FIntPoint InRenderTargetResolution);` — `UFUNCTION(BlueprintSetter)` — Set the render target resolution for the scene captures.
- L96 _public prototype_ `const TArray<TSoftObjectPtr<AActor>> GetActors() const;` — `UFUNCTION(BlueprintGetter)` — Get reflection & shadow caster actors.
- L100 _public prototype_ `void SetActors(TArray<TSoftObjectPtr<AActor>> InActors);` — `UFUNCTION(BlueprintSetter)` — Set reflection & shadow caster actors.
- L103 _public prototype_ `virtual void SetIsEnabled(bool bInEnabled) override;` — Set the enabled state.
- L109 _public member_ `ECompositeHiddenInSceneCaptureConfiguration AutoConfigureActors_DEPRECATED;` — `UE_DEPRECATED(5.8, "AutoConfigureActors is now deprecated.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "AutoConfigureActors is now deprecated."))`
- L115 _private prototype_ `void UpdatePrimitiveVisibilityState(bool bInHiddenInSceneCapture, bool bInAffectIndirectLightingWhileHidden, bool bInCastHiddenShadow, bool bConditionOnVisibility) const;` — Update scene capture visibility on registered mesh actors primitives.
- L118 _private prototype_ `void SetHiddenPrimitiveState(bool bInHiddenInSceneCapture) const;` — Set primitive visibility state and console variables required for hidden in scene capture.
- L121 _private prototype_ `TStaticArray<TWeakObjectPtr<UCompositeShadowReflectionCatcherComponent>, 2> FindOrCreateSceneCapturePair(ACompositeActor& InOuter) const;` — Find or create scene captures with CG and without CG.
- L126 _private member_ `FIntPoint RenderTargetResolution;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetRenderTargetResolution, BlueprintSetter = SetRenderTargetResolution, Interp, Category = "Composite", meta = (AllowPrivateAccess = true))` — Render target resolution for the scene captures.
- L129 _private prototype_ `void SetActorsInternal(TArray<TSoftObjectPtr<AActor>> InActors);` — Apply actor-change side effects without touching spawnable bindings.
- L133 _private member_ `TArray<TSoftObjectPtr<AActor>> Actors;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetActors, BlueprintSetter = SetActors, Category = "Composite", meta = (AllowPrivateAccess = true))` — List of reflection & shadow caster actors.
- L137 _private member_ `FCompositeSpawnableBindings SpawnableBindings;` — `UPROPERTY()` — Parallel spawnable binding data for the Actors array.
- L146 _public member_ `bool bLuminanceOnly = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite")` — When true, the matte is computed from a single (grayscale) luminance ratio applied uniformly to all channels, instead of independent per-channel ratios. This can help minimize noise from divisions by values near zero, or avoid incorrect chromaticity in Lumen reflections.
- L153 _private member_ `TMap<TWeakObjectPtr<UPrimitiveComponent>, FCompositeShadowReflectionPrimitiveState> CachedVisibilityInSceneCapture;` — `UE_DEPRECATED(5.8, "CachedVisibilityInSceneCapture is now deprecated.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "CachedVisibilityInSceneCapture is now deprecated."))`
- L159 _private member_ `mutable TStaticArray<TWeakObjectPtr<UCompositeShadowReflectionCatcherComponent>, 2> CachedSceneCaptures;` — Cached pointer to the scene captures with CG and without CG.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Layers/CompositeLayerSingleLightShadow.h` (Public)


#### class `UCompositeLayerSingleLightShadow`  
`class UCompositeLayerSingleLightShadow : public UCompositeLayerBase`  
_L31-149_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta = (DisplayName = "Single Light Shadow"))`
- inherits: `UCompositeLayerBase`
- desc: Layer that catches shadows cast by registered actors from a single specified light. Uses classic shadow-map percentage-closer filtering (5x5 by default, no cascades). Implemented with custom render passes for minimal performance cost.
- L37 _public prototype_ `UCompositeLayerSingleLightShadow(const FObjectInitializer& ObjectInitializer);` — Constructor.
- L40 _public prototype_ `virtual ~UCompositeLayerSingleLightShadow() = default;` — Destructor.
- L42 _public prototype_ `virtual void OnRemoved(ACompositeActor* LastOwner) override;`
- L45 _public prototype_ `virtual void BeginDestroy() override;`
- L48 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L49 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L50 _public prototype_ `virtual void PostEditUndo() override;`
- L51 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L56 _public prototype_ `virtual void OnEndOfFrameUpdate(UWorld* InWorld) override;` — End-of-frame update callback.
- L58 _public prototype_ `virtual bool GetIsActive() const override;`
- L59 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L68 _public member_ `TObjectPtr<ALight> Light;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite", meta=(AllowedClasses="/Script/Engine.DirectionalLight"))` — The reference light, whose direction or exact transform will by used to render a shadow map. Only directional lights are currently supported.
- L72 _public prototype_ `const TArray<TSoftObjectPtr<AActor>> GetShadowCastingActors() const;` — `UFUNCTION(BlueprintGetter)` — Get shadow caster actors.
- L76 _public prototype_ `void SetShadowCastingActors(TArray<TSoftObjectPtr<AActor>> InShadowCaster);` — `UFUNCTION(BlueprintSetter)` — Set shadow caster actors.
- L83 _public member_ `bool bAutomaticBounds;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite")` — When enable, the shadow map render transform and orthographic width are automatically derived from the selected meshes and light angle. When disabled, the shadow map transform is copied from the light transform, which should be piloted to align with shadow casting geometry.
- L90 _public member_ `float OrthographicWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (EditCondition = "!bAutomaticBounds", EditConditionHides))` — The desired width (in world units) of the shadow map view (ignored if light is not directional). Reduce size to only contain the shadow casting geometry in view of the light.
- L94 _public function_ `FIntPoint GetRenderTargetResolution() const` — `UFUNCTION(BlueprintGetter)` — Get the render target resolution for the scene depth capture.
- L98 _public prototype_ `void SetRenderTargetResolution(FIntPoint InRenderTargetResolution);` — `UFUNCTION(BlueprintSetter)` — Set the render target resolution for the scene depth capture.
- L104 _public member_ `int32 ShadowMapResolution;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite", meta = (ClampMin = "128", UIMin = "128", UIMax="4096"))` — Resolution of the shadow map texture. Lower resolutions will cause more blurry shadows.
- L108 _public member_ `float ShadowStrength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Basic shadow strength multiplier, from 0 to 1.
- L113 _public member_ `float ShadowBias_DEPRECATED = 0.5f;` — `UE_DEPRECATED(5.8, "Shadow Bias is now deprecated.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Shadow Bias is now deprecated."))`
- L118 _private prototype_ `UCompositeSceneCapture2DComponent* FindOrCreateSceneDepthCapture(ACompositeActor& InOuter) const;` — Find or create scene depth capture component, correctly configured.
- L121 _private prototype_ `UCompositeSceneCapture2DComponent* FindOrCreateShadowMapCapture(ACompositeActor& InOuter) const;` — Find or create shadow map capture component, correctly configured.
- L124 _private prototype_ `void GetShadowMatrices(UCompositeSceneCapture2DComponent& ShadowMapCapture, FMatrix44f& OutShadowMatrix, FVector4f& OutShadowInvDeviceZToWorldZ) const;` — Convenience function to calculate shadow matrices.
- L129 _private member_ `FIntPoint RenderTargetResolution;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetRenderTargetResolution, BlueprintSetter = SetRenderTargetResolution, Interp, Category = "Composite", meta = (AllowPrivateAccess = true))` — Render target resolution for the scene depth capture.
- L132 _private prototype_ `void SetShadowCastingActorsInternal(TArray<TSoftObjectPtr<AActor>> InShadowCasters);` — Apply actor-change side effects without touching spawnable bindings.
- L136 _private member_ `TArray<TSoftObjectPtr<AActor>> ShadowCastingActors;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetShadowCastingActors, BlueprintSetter = SetShadowCastingActors, Category = "Composite", meta = (AllowPrivateAccess = true))` — List of shadow casting actors (required).
- L140 _private member_ `FCompositeSpawnableBindings SpawnableBindings;` — `UPROPERTY()` — Parallel spawnable binding data for the ShadowCastingActors array.
- L143 _private member_ `mutable TWeakObjectPtr<UCompositeSceneCapture2DComponent> CachedShadowMapCapture;` — Cached pointer to the composite-managed shadow map scene capture.
- L146 _private member_ `mutable TWeakObjectPtr<UCompositeSceneCapture2DComponent> CachedSceneDepthCapture;` — Cached pointer to the scene depth capture.

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Passes/CompositePassBase.h` (Public)


#### struct `FCompositeTraversalContext`  
`struct FCompositeTraversalContext`  
_L16-49_
- desc: Context used while traversing passes and layers to collect frame proxies.
- L19 _public member_ `bool bIsSolo = false;` — Flag to indicate solo pass
- L22 _public member_ `bool bIsFirstPass = true;` — Flag to indicate first pass
- L28 _public member_ `bool bNeedsSceneTextures = false;` — Flag to indicate that a layer is dependent on scene textures. Work from scene-independent layers can be shared between post-processing locations.
- L31 _public member_ `bool bIsPreprocessing = false;` — Flag to indicate that passes are being collected for preprocessing (before the main render).
- L34 _public member_ `TSortedMap<UE::CompositeCore::ResourceId, TArray<const FCompositeCorePassProxy*>> PreprocessingPasses;` — Array of passes applied at the start of rendering.
- L41 _public prototype_ `UE::CompositeCore::ResourceId FindOrCreateExternalTexture(TWeakObjectPtr<UTexture> InTexture, UE::CompositeCore::FResourceMetadata InMetadata);` — Find or create an external texture resource. @return ResourceId Texture resource identifier
- L44 _public prototype_ `const TArray<UE::CompositeCore::FExternalTexture>& GetExternalTextures() const;` — Get external textures.
- L48 _private member_ `TArray<UE::CompositeCore::FExternalTexture> ExternalTextures;` — List of external textures

#### class `UCompositePassBase`  
`class UCompositePassBase : public UObject`  
_L56-128_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew)`
- inherits: `UObject`
- desc: Base class for a composite pass: a render-thread operation applied to a layer's input. Subclasses spawn a per-frame render proxy via GetProxy() that runs on the GPU.
- L62 _public prototype_ `UCompositePassBase(const FObjectInitializer& ObjectInitializer);` — Constructor.
- L65 _public prototype_ `virtual ~UCompositePassBase();` — Destructor.
- L68 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const;`
- L72 _public function_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const` — Override to return a render-thread proxy for this pass. Proxy objects should be allocated from the provided allocator. Only called when GetIsActive() returns true.
- L76 _public prototype_ `virtual bool GetIsEnabled() const;` — `UFUNCTION(BlueprintGetter)` — Get the enabled state.
- L80 _public prototype_ `virtual void SetIsEnabled(bool bInEnabled);` — `UFUNCTION(BlueprintSetter, CallInEditor)` — Set the enabled state.
- L83 _public function_ `virtual bool GetIsActive() const` — Returns true if the pass should participate in rendering this frame. Checked before GetProxy() is called.
- L87 _public function_ `FString GetDisplayName() const` — Gets the display name of the pass
- L90 _public function_ `void SetDisplayName(const FString& InDisplayName)` — Sets the display name of the pass
- L94 _public function_ `template<typename T> static FString MakeUniqueDisplayName(const FString& BaseName, TArrayView<TObjectPtr<T>> Siblings, const UCompositePassBase* Exclude)` — Generates a unique display name by appending a number if siblings share the same base type name. First instance stays clean; duplicates start at 2.
- L119 _protected member_ `bool bIsEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetIsEnabled, BlueprintSetter = SetIsEnabled, Interp, Category = "Composite", meta = (DisplayPriority = "1"))` — Whether or not the pass is active.
- L124 _protected member_ `FString DisplayName;` — `UPROPERTY(EditAnywhere, Category = "Composite", meta = (DisplayName="Name", DisplayPriority = "0"))` — The display name of the pass

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Passes/CompositePassBlur.h` (Public)


#### enum `ECompositePassBlurMethod`  
`enum class ECompositePassBlurMethod : uint8`  
_L13-16_
- reflection: `UENUM(BlueprintType)`
- desc: Blur method type.
- L15 _public enumerator_ `Gaussian`

#### class `UCompositePassBlur`  
`class UCompositePassBlur : public UCompositePassBase`  
_L23-60_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta = (DisplayName = "Blur"))`
- inherits: `UCompositePassBase`
- desc: Applies a blur to the layer input. Currently supports Gaussian blur with independent X and Y radius controls.
- L29 _public prototype_ `UCompositePassBlur(const FObjectInitializer& ObjectInitializer);` — Constructor
- L32 _public prototype_ `~UCompositePassBlur();` — Destructor
- L34 _public prototype_ `virtual bool GetIsActive() const override;`
- L36 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L38 _public prototype_ `virtual void PostLoad() override;`
- L43 _public member_ `ECompositePassBlurMethod Method;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite")` — Blur pass method.
- L47 _public member_ `FIntPoint RadiusXY = FIntPoint(1, 1);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (DisplayName = "Radius", ClampMin = "1", ClampMax = "64", UIMin = "1", UIMax = "64", AllowPreserveRatio))` — Blur radius in pixels (X = horizontal, Y = vertical).
- L51 _public member_ `bool bAlphaOnly = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", AdvancedDisplay)` — Only blur the alpha channel, leaving RGB unchanged.
- L58 _private member_ `int32 Radius_DEPRECATED = 0;` — `UE_DEPRECATED(5.8, "Radius has been deprecated, use RadiusXY instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Radius has been deprecated, use RadiusXY instead."))` — Deprecated scalar radius from prior versions. Tagged-property load matches old "Radius" int32 tag; migrated to RadiusXY in PostLoad.

#### class `UE::Composite::Private::FCompositePassBlurProxy`  
`class FCompositePassBlurProxy : public FCompositeCorePassProxy`  
_L71-85_
- inherits: `FCompositeCorePassProxy`
- desc: Render-thread proxy for the Gaussian blur pass. Runs a separable horizontal + vertical convolution over the input.
- L74 _public prototype_ `IMPLEMENT_COMPOSITE_PASS(FCompositePassBlurProxy);`
- L79 _public prototype_ `FPassTexture Add(FRDGBuilder& GraphBuilder, const FSceneView& InView, const FPassInputArray& Inputs, const FPassContext& PassContext) const override;` — Adds the Gaussian blur RDG passes (horizontal then vertical) and returns the blurred output.
- L82 _public member_ `FIntPoint Radius = FIntPoint(1, 1);` — Blur kernel half-width in pixels (X = horizontal, Y = vertical).
- L84 _public member_ `bool bAlphaOnly = false;` — When true, only the alpha channel is blurred; RGB is passed through unchanged.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMPOSITE_API`
- L62 _namespace_ `namespace UE`
- L64 _namespace_ `namespace Composite` (scope `UE`)
- L66 _namespace_ `namespace Private` (scope `UE::Composite`)

### `Plugins/Compositing/Composite/Source/Composite/Public/Passes/CompositePassColorGrading.h` (Public)


#### struct `FCompositeTemperatureSettings`  
`struct FCompositeTemperatureSettings`  
_L16-35_
- reflection: `USTRUCT(BlueprintType)`
- desc: Color grading pass temperature settings.
- L30 _public member_ `float WhiteTemp = 6500.0f;` — `UPROPERTY(interp, BlueprintReadWrite, Category = "Color Grading|Temperature", meta = (UIMin = "1500.0", UIMax = "15000.0", DisplayName = "Temp"))` — Controls the color temperature or white balance in degrees Kelvin which the scene considers as white light.
- L34 _public member_ `float WhiteTint = 0.0f;` — `UPROPERTY(interp, BlueprintReadWrite, Category = "Color Grading|Temperature", meta = (UIMin = "-1.0", UIMax = "1.0", DisplayName = "Tint"))` — Controls the color of the scene along the magenta - green axis (orthogonal to the color temperature).  This feature is equivalent to color tint in digital cameras.

#### class `UCompositePassColorGrading`  
`class UCompositePassColorGrading : public UCompositePassBase`  
_L42-70_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta = (DisplayName = "Color Grading"))`
- inherits: `UCompositePassBase`
- desc: Applies exposure, contrast, saturation, temperature and color-wheel adjustments to the layer input. Assumes input is in the linear working color space.
- L48 _public prototype_ `UCompositePassColorGrading(const FObjectInitializer& ObjectInitializer);` — Constructor
- L50 _public prototype_ `~UCompositePassColorGrading();` — Destructor
- L52 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L61 _public member_ `bool bInputIsPremultiplied;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Composite")` — Set true when the input texture stores premultiplied alpha (RGB already scaled by A). The pass will unpremultiply before processing and re-premultiply after, so color grading operates on straight-alpha values. Leave false for straight-alpha inputs.
- L65 _public member_ `FCompositeTemperatureSettings TemperatureSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Composite", meta = (DisplayName = "Temperature"))` — Color temperature settings.
- L69 _public member_ `FColorGradingSettings ColorGradingSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Composite", meta = (ShowOnlyInnerProperties))` — Color grading settings.

#### struct `FCompositeColorGradingPassSettings`  
`struct FCompositeColorGradingPassSettings`  
_L73-96_
- reflection: `USTRUCT(BlueprintType)`
- L79 _public member_ `bool bEnableColorGrading = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Composite")` — Hidden in scene capture.
- L87 _public member_ `bool bInputIsPremultiplied = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Composite")` — Set true when the input texture stores premultiplied alpha (RGB already scaled by A). The pass will unpremultiply before processing and re-premultiply after, so color grading operates on straight-alpha values. Leave false for straight-alpha inputs.
- L91 _public member_ `FCompositeTemperatureSettings TemperatureSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Composite", meta = (DisplayName = "Temperature"))` — Color temperature settings.
- L95 _public member_ `FColorGradingSettings ColorGradingSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Composite", meta = (ShowOnlyInnerProperties))` — Color grading settings.

#### class `UE::Composite::Private::FColorGradingCompositePassProxy`  
`class FColorGradingCompositePassProxy : public FCompositeCorePassProxy`  
_L105-124_
- inherits: `FCompositeCorePassProxy`
- desc: Render-thread proxy for the color grading pass. Applies white balance and shadow/midtone/highlight color grading to the input.
- L108 _public prototype_ `IMPLEMENT_COMPOSITE_PASS(FColorGradingCompositePassProxy);`
- L111 _public prototype_ `FColorGradingCompositePassProxy(CompositeCore::FPassInputDeclArray InPassDeclaredInputs);` — Constructor
- L114 _public prototype_ `CompositeCore::FPassTexture Add(FRDGBuilder& GraphBuilder, const FSceneView& InView, const CompositeCore::FPassInputArray& Inputs, const CompositeCore::FPassContext& PassContext) const override;` — Adds the color grading RDG pass; applies temperature and color grading adjustments and returns the graded output.
- L117 _public member_ `bool bInputIsPremultiplied = true;` — When true, the input is treated as premultiplied alpha: RGB is divided by alpha before processing and multiplied back after.
- L120 _public member_ `FCompositeTemperatureSettings TemperatureSettings;` — Color temperature settings.
- L123 _public member_ `FColorGradingSettings ColorGradingSettings;` — Color grading settings.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API COMPOSITE_API`
- L98 _namespace_ `namespace UE`
- L100 _namespace_ `namespace Composite` (scope `UE`)
- L102 _namespace_ `namespace Private` (scope `UE::Composite`)

### `Plugins/Compositing/Composite/Source/Composite/Public/Passes/CompositePassColorKeyer.h` (Public)


#### enum `ECompositeColorKeyerVisualization`  
`enum class ECompositeColorKeyerVisualization : uint8`  
_L13-18_
- reflection: `UENUM(BlueprintType)`
- desc: Visualization mode, for inspecting your key.
- L15 _public enumerator_ `Key = 0`
- L16 _public enumerator_ `Fill = 1`
- L17 _public enumerator_ `Alpha = 2`

#### enum `ECompositeColorKeyerScreenType`  
`enum class ECompositeColorKeyerScreenType : uint8`  
_L22-27_
- reflection: `UENUM(BlueprintType)`
- desc: Background screen color type (red, green or blue).
- L24 _public enumerator_ `Red = 0`
- L25 _public enumerator_ `Green = 1`
- L26 _public enumerator_ `Blue = 2`

#### enum `ECompositeColorKeyerMode`  
`enum class ECompositeColorKeyerMode : uint8`  
_L31-35_
- reflection: `UENUM(BlueprintType)`
- desc: Keying mode: chroma key (color-based) or luma key (luminance-based).
- L33 _public enumerator_ `Chroma = 0 UMETA(DisplayName = "Chroma Key")`
- L34 _public enumerator_ `Luma = 1 UMETA(DisplayName = "Luma Key")`

#### enum `ECompositeDenoiseMethod`  
`enum class ECompositeDenoiseMethod : uint8`  
_L39-43_
- reflection: `UENUM(BlueprintType)`
- desc: Denoising method applied before keying.
- L41 _public enumerator_ `None`
- L42 _public enumerator_ `Median3x3 UMETA(DisplayName = "Median 3x3")`

#### enum `ECompositeKeyerSource`  
`enum class ECompositeKeyerSource : uint8`  
_L46-50_
- reflection: `UENUM(BlueprintType)`
- L48 _public enumerator_ `Color`
- L49 _public enumerator_ `CleanPlate`

#### class `UCompositePassColorKeyer`  
`class UCompositePassColorKeyer : public UCompositePassBase`  
_L57-168_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta=(DisplayName="Color Keyer"))`
- inherits: `UCompositePassBase`
- desc: Extracts alpha from a colored background (red, green or blue) using chroma keying. Supports clean-plate differencing, despill and denoising.
- L63 _public prototype_ `UCompositePassColorKeyer(const FObjectInitializer& ObjectInitializer);` — Constructor
- L66 _public prototype_ `~UCompositePassColorKeyer();` — Destructor
- L68 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L70 _public prototype_ `virtual void PostLoad() override;`
- L73 _public prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;`
- L74 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L80 _public member_ `ECompositeColorKeyerScreenType ScreenType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite")` — Type of screen color (required). The keyer works best against red, green or blue backgrounds.
- L84 _public member_ `ECompositeKeyerSource KeyerSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite", meta = (PropertyGroup = "Keyer Settings"))` — Source used by the keyer to derive the screen color: either a static key color or a clean plate texture.
- L88 _public member_ `FLinearColor KeyColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (PropertyGroup = "Keyer Settings", OnlyUpdateOnInteractionEnd, EditCondition = "KeyerSource == ECompositeKeyerSource::Color", EditConditionHides))` — Static background key color.
- L95 _public member_ `TObjectPtr<UTexture> CleanPlate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite", meta = (PropertyGroup = "Keyer Settings", OnlyUpdateOnInteractionEnd, AllowedClasses = "/Script/Engine.Texture2D, /Script/Engine.Texture2DDynamic, /Script/Engine.TextureRenderTarget2D, /Script/MediaAssets.MediaTexture", EditCondition = "KeyerSource == ECompositeKeyerSource::CleanPlate", EditConditionHides))` — Clean plate background for calculating color differences per pixel, instead of the static key color. Resolution must match the composite actor render resolution.
- L100 _public member_ `float CleanPlateCountdown = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Composite", meta = (PropertyGroup = "Keyer Settings", EditCondition = "KeyerSource == ECompositeKeyerSource::CleanPlate", EditConditionHides, ClampMin=0.0, UIMin=0.0, ClampMax=60.0, UIMax=60.0))` — Setting that controls how long to delay before capturing a clean plate
- L104 _public member_ `float PlateTexturePreviewSize = 5.0f;` — `UPROPERTY(EditAnywhere, Category = "Composite", meta = (PropertyGroup = "Keyer Settings", EditCondition = "KeyerSource == ECompositeKeyerSource::Color", EditConditionHides, ClampMin=1.0, UIMin=1.0, ClampMax=10.0, UIMax=10.0))` — Setting that determines how large to display the plate texture 'picture-in-picture' preview in the level editor when using the eye dropper color picker
- L109 _public member_ `float RedWeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (UIMin = 0.0f, UIMax = 1.0f, EditCondition = "ScreenType != ECompositeColorKeyerScreenType::Red"))` — Weight of the foreground red channel contributing to the key matte hardness.
- L113 _public member_ `float GreenWeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (UIMin = 0.0f, UIMax = 1.0f, EditCondition = "ScreenType != ECompositeColorKeyerScreenType::Green"))` — Weight of the foreground green channel contributing to the key matte hardness.
- L117 _public member_ `float BlueWeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (UIMin = 0.0f, UIMax = 1.0f, EditCondition = "ScreenType != ECompositeColorKeyerScreenType::Blue"))` — Weight of the foreground blue channel contributing to the key matte hardness.
- L121 _public member_ `FVector2f AlphaThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (UIMin = 0.0f, UIMax = 1.0f))` — Thresholds any alpha value outside the specified range to zero or one respectively, with linear interpolation in-between.
- L125 _public member_ `float DespillStrength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (UIMin = 0.0f, UIMax = 1.0f))` — Strength of the spill reduction, 0.0: none, 1.0: full.
- L129 _public member_ `float DevignetteStrength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (UIMin = 0.0f, UIMax = 1.0f))` — Strength of the vignette removal. Used to improve plate uniformity & remove darker corners.
- L133 _public member_ `bool bPreserveVignetteAfterKey;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", AdvancedDisplay)` — When enabled, we undo devignetting before outputting the keyed plate.
- L137 _public member_ `ECompositeDenoiseMethod DenoiseMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite", AdvancedDisplay)` — Denoising method applied before the keyer.
- L147 _public member_ `float ChromaShift;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", AdvancedDisplay, meta = (UIMin = -1.0f, UIMax = 1.0f, ClampMin = -1.0f, ClampMax = 1.0f))` — Provided so users can compensate for upstream media whose chroma may be offset relative to luma with chroma-subsampled sources (such as 4:2:2 YUV captures). Applies a horizontal chroma shift, in input texels, to the foreground sampled by the color keyer pass. Center-pixel luma is preserved. Zero disables the shift.
- L151 _public member_ `ECompositeColorKeyerVisualization Visualization;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite")` — Vizualize the alpha key or fill.
- L155 _public member_ `bool bDespillOnly;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", AdvancedDisplay)` — Only apply the despill algorithm controlled by DespillStrength, alpha is unmodified.
- L159 _public member_ `bool bInvertAlpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", AdvancedDisplay)` — Invert the alpha key.
- L163 _public member_ `bool bEditorThrottleDisabled = false;` — Flag tracking whether we disabled throttling to later restore it.

#### class `UCompositePassLumaKeyer`  
`class UCompositePassLumaKeyer : public UCompositePassBase`  
_L175-208_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta=(DisplayName="Luma Keyer"))`
- inherits: `UCompositePassBase`
- desc: Extracts alpha from pixel luminance (luma key). Useful for isolating bright or dark regions without a colored backdrop.
- L180 _public prototype_ `UCompositePassLumaKeyer(const FObjectInitializer& ObjectInitializer);`
- L181 _public prototype_ `~UCompositePassLumaKeyer();`
- L183 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L188 _public member_ `FVector2f LumaRange;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (ClampMin = 0.0f, ClampMax = 1.0f, UIMin = 0.0f, UIMax = 1.0f))` — Luminance range [min, max] that maps to alpha [0, 1]. Pixels with luminance below min are fully transparent; above max are fully opaque.
- L192 _public member_ `ECompositeColorKeyerVisualization Visualization;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite")` — Vizualize the alpha key or fill.
- L196 _public member_ `bool bInvertAlpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", AdvancedDisplay)` — Invert the alpha key.
- L203 _public member_ `bool bDisplaySpaceLuminance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", AdvancedDisplay)` — When enabled, luminance is computed after converting the pixel to display space (sRGB encoding) rather than in linear light. This matches the luma-key behavior of other tools, where LumaRange values correspond to what you see on screen.
- L207 _public member_ `ECompositeDenoiseMethod DenoiseMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite", AdvancedDisplay)` — Denoising method applied before the keyer.

#### class `UE::Composite::Private::FCompositePassColorKeyerProxy`  
`class FCompositePassColorKeyerProxy : public FCompositeCorePassProxy`  
_L218-251_
- inherits: `FCompositeCorePassProxy`
- desc: Render-thread proxy for the color keyer pass. Performs chroma-key extraction and optional despill on the input.
- L221 _public prototype_ `IMPLEMENT_COMPOSITE_PASS(FCompositePassColorKeyerProxy);`
- L225 _public prototype_ `FPassTexture Add(FRDGBuilder& GraphBuilder, const FSceneView& InView, const FPassInputArray& Inputs, const FPassContext& PassContext) const override;` — Adds the color keyer RDG pass and returns a premultiplied keyed RGBA output.
- L228 _public member_ `ECompositeColorKeyerMode KeyerMode = ECompositeColorKeyerMode::Chroma;` — Whether this proxy uses chroma or luma keying.
- L230 _public member_ `ECompositeColorKeyerScreenType ScreenType = ECompositeColorKeyerScreenType::Green;` — Background screen color used to drive the key algorithm.
- L232 _public member_ `FLinearColor KeyColor;` — Static background reference color; used when no clean plate is provided.
- L234 _public member_ `FVector4f Params0 = FVector4f(0.0f, 0.0f, 0.0f, 0.0f);` — Shader parameter vector: (RedWeight, GreenWeight, BlueWeight, DespillStrength).
- L236 _public member_ `FVector4f Params1 = FVector4f(0.0f, 0.0f, 0.0f, 0.0f);` — Shader parameter vector: chroma=(AlphaMin, AlphaMax, DevignetteStrength, ChromaShift), luma=(LumaMin, LumaMax, 0, 0).
- L238 _public member_ `ECompositeColorKeyerVisualization Visualization = ECompositeColorKeyerVisualization::Key;` — Which output channel to display: final composite key, fill layer, or raw alpha matte.
- L240 _public member_ `bool bPreserveVignetteAfterKey = true;` — When true, devignette correction is reversed before outputting the keyed result.
- L242 _public member_ `ECompositeDenoiseMethod DenoiseMethod = ECompositeDenoiseMethod::None;` — Denoising pre-pass applied to the foreground before keying.
- L244 _public member_ `bool bDespillOnly = false;` — When true, only despill is applied; alpha is left unchanged.
- L246 _public member_ `bool bInvertAlpha = false;` — When true, the output alpha is inverted (1 − alpha).
- L248 _public member_ `bool bDisplaySpaceLuminance = false;` — When true, luminance is computed in display (sRGB encoding) space to match other tools.
- L250 _public member_ `TWeakObjectPtr<UTexture> CleanPlateWeakPtr;` — Weak pointer to the clean plate texture used as the per-pixel background reference. Null when KeyColor is used instead.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMPOSITE_API`
- L210 _namespace_ `namespace UE`
- L212 _namespace_ `namespace Composite` (scope `UE`)
- L214 _namespace_ `namespace Private` (scope `UE::Composite`)

### `Plugins/Compositing/Composite/Source/Composite/Public/Passes/CompositePassDilation.h` (Public)


#### enum `ECompositeDilationChannel`  
`enum class ECompositeDilationChannel : uint8`  
_L14-21_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Channel bitmask controlling which channels the morphological operation reads and writes.
- L16 _public enumerator_ `None = 0 UMETA(Hidden)`
- L17 _public enumerator_ `Red = 0x1`
- L18 _public enumerator_ `Green = 0x2`
- L19 _public enumerator_ `Blue = 0x4`
- L20 _public enumerator_ `Alpha = 0x8`

#### class `UCompositePassDilation`  
`class UCompositePassDilation : public UCompositePassBase`  
_L29-69_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta = (DisplayName = "Dilation"))`
- inherits: `UCompositePassBase`
- desc: Morphologically dilates or erodes selected channels of the layer input by a configurable pixel radius. Used to grow or shrink mattes before downstream compositing operations.
- L35 _public prototype_ `UCompositePassDilation(const FObjectInitializer& ObjectInitializer);` — Constructor
- L38 _public prototype_ `~UCompositePassDilation();` — Destructor
- L40 _public prototype_ `virtual bool GetIsActive() const override;`
- L42 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L47 _public member_ `int32 Size = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (UIMin = "-20", UIMax = "20", ClampMin = "-64", ClampMax = "64"))` — Signed size: negative = erode (shrink), positive = dilate (expand), 0 = identity (pass disabled).
- L52 _public member_ `int32 Channels = static_cast<int32>(ECompositeDilationChannel::Red) | static_cast<int32>(ECompositeDilationChannel::Green) | static_cast<int32>(ECompositeDilationChannel::Blue) | static_cast<int32>(ECompositeDilationChannel::Alpha);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite", meta = (Bitmask, BitmaskEnum = "/Script/Composite.ECompositeDilationChannel"))` — Channels the operation reads and writes. Defaults to all channels so a fresh Dilation Pass affects RGB and alpha together.
- L60 _public member_ `bool bUseThreshold = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, AdvancedDisplay, Category = "Composite")` — When true, the operation only fires on pixels that are essentially off (at or below a small epsilon), thus only affecting matte edges.
- L64 _public member_ `float Threshold = 0.0001f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, AdvancedDisplay, Category = "Composite", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bUseThreshold", EditConditionHides))` — In standard opacity space (0 = transparent, 1 = opaque): a channel's value is treated as "off" at or below this threshold and "on" above it. Only used when Use Threshold is enabled.
- L68 _public member_ `bool bCarryRGBWithAlpha = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Composite", meta = (DisplayName = "Carry RGB With Alpha"))` — When Alpha is selected, the alpha-winning neighbor's RGB is copied into any color channels that aren't explicitly in the Channels mask, so mattes grow/shrink visibly. Disable for strict "alpha only" semantics (RGB untouched).

#### class `UE::Composite::Private::FCompositePassDilationProxy`  
`class FCompositePassDilationProxy : public FCompositeCorePassProxy`  
_L82-106_
- inherits: `FCompositeCorePassProxy`
- desc: Render-thread proxy for the morphological dilation/erosion pass.
- L85 _public prototype_ `IMPLEMENT_COMPOSITE_PASS(FCompositePassDilationProxy);`
- L92 _public prototype_ `FPassTexture Add(FRDGBuilder& GraphBuilder, const FSceneView& InView, const FPassInputArray& Inputs, const FPassContext& PassContext) const override;` — Adds ceil(AbsSize/2) RDG compute passes covering AbsSize pixels of dilation or erosion and returns the result. Each pass uses a DILATION_SIZE=2 kernel (2 pixels/dispatch) where possible, falling back to DILATION_SIZE=1 for an odd remainder. Intermediate results ping-pong through internal textures.
- L95 _public member_ `int32 AbsSize = 1;` — Total pixel reach of the dilation/erosion (dispatched in greedy 2-pixel steps).
- L97 _public member_ `bool bErode = false;` — When true, runs erosion (shrink opaque); when false, runs dilation (expand opaque).
- L99 _public member_ `uint32 ChannelMask = 0xFu;` — Bitmask of channels to operate on: R=0x1, G=0x2, B=0x4, A=0x8.
- L101 _public member_ `bool bUseThreshold = false;` — When true, gate the operation on Threshold. When false, run true min/max morphology.
- L103 _public member_ `float Threshold = 0.0001f;` — Opacity threshold (standard opacity space) used only when bUseThreshold is true.
- L105 _public member_ `bool bCarryRGBWithAlpha = true;` — When true, copy the alpha-winning neighbor's RGB into RGB channels not in the mask (so mattes grow visibly).

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMPOSITE_API`
- L22 _prototype_ `ENUM_CLASS_FLAGS(ECompositeDilationChannel);`
- L73 _namespace_ `namespace UE`
- L75 _namespace_ `namespace Composite` (scope `UE`)
- L77 _namespace_ `namespace Private` (scope `UE::Composite`)

### `Plugins/Compositing/Composite/Source/Composite/Public/Passes/CompositePassDistortion.h` (Public)


#### enum `ECompositeDistortion`  
`enum class ECompositeDistortion : uint8`  
_L16-20_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `Undistort`
- L19 _public enumerator_ `Distort`

#### class `UCompositePassDistortion`  
`class UCompositePassDistortion : public UCompositePassBase`  
_L27-53_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta = (DisplayName = "Distortion"))`
- inherits: `UCompositePassBase`
- desc: Applies a lens distortion or undistortion transform to the layer input. Driven by a distortion model supplied through the camera calibration system.
- L33 _public prototype_ `UCompositePassDistortion(const FObjectInitializer& ObjectInitializer);` — Constructor
- L35 _public prototype_ `~UCompositePassDistortion();` — Destructor
- L38 _public prototype_ `virtual void PostInitProperties() override;`
- L41 _public prototype_ `virtual bool GetIsActive() const override;`
- L43 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L48 _public member_ `ECompositeDistortion Distortion;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite")` — Distortion to apply on input.
- L52 _private member_ `TSharedPtr<FLensDistortionSceneViewExtension, ESPMode::ThreadSafe> LensDistortionSVE;` — Cached lens distortion scene view extension.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Passes/CompositePassFXAA.h` (Public)


#### class `UCompositePassFXAA`  
`class UCompositePassFXAA : public UCompositePassBase`  
_L16-38_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta=(DisplayName="FXAA"))`
- inherits: `UCompositePassBase`
- desc: Applies FXAA anti-aliasing to the layer input. Primarily intended for CG or motion-graphics layers rendered through a custom render pass.
- L22 _public prototype_ `UCompositePassFXAA(const FObjectInitializer& ObjectInitializer);` — Constructor
- L25 _public prototype_ `~UCompositePassFXAA();` — Destructor
- L27 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L33 _public member_ `int32 Quality;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta=(ClampMin="0", ClampMax="5", UIMin = "0", UIMax = "5"))` — FXAA quality control, matching the "r.fxaa.quality" console variable values.
- L37 _public member_ `bool bDisplayTransform = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", AdvancedDisplay)` — Apply a display transform (tonemap + gamma encode) before AA and invert it after. Improves perceptual edge detection on linear content but may darken edges at alpha boundaries.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Passes/CompositePassMasking.h` (Public)


#### enum `ECompositeColorChannel`  
`enum class ECompositeColorChannel : uint8`  
_L15-21_
- reflection: `UENUM(BlueprintType)`
- desc: Color channel.
- L17 _public enumerator_ `Red`
- L18 _public enumerator_ `Green`
- L19 _public enumerator_ `Blue`
- L20 _public enumerator_ `Alpha`

#### enum `ECompositeMaskingMode`  
`enum class ECompositeMaskingMode : uint8`  
_L25-29_
- reflection: `UENUM(BlueprintType)`
- desc: Masking source mode.
- L27 _public enumerator_ `Texture = 0 UMETA(ToolTip = "Use a texture as the mask source.")`
- L28 _public enumerator_ `Geometry = 1 UMETA(ToolTip = "Render selected meshes as a geometry mask via custom render pass.")`

#### class `UCompositePassMasking`  
`class UCompositePassMasking : public UCompositePassBase, public FTickableGameObject`  
_L40-180_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta=(DisplayName="Masking"))`
- inherits: `UCompositePassBase,FTickableGameObject`
- desc: Masks the layer alpha using a texture, a geometry render of selected actors, or a combination of both. The resulting mask is multiplied into the input alpha.
- L46 _public prototype_ `UCompositePassMasking(const FObjectInitializer& ObjectInitializer);` — Constructor
- L49 _public prototype_ `~UCompositePassMasking();` — Destructor
- L51 _public prototype_ `virtual bool GetIsActive() const override;`
- L53 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L56 _public prototype_ `virtual void BeginDestroy() override;`
- L59 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L60 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L61 _public prototype_ `virtual void PostEditUndo() override;`
- L66 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L67 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L68 _public function_ `virtual bool IsTickableInEditor() const override`
- L69 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L70 _public prototype_ `virtual bool IsTickable() const override;`
- L71 _public prototype_ `virtual UWorld* GetTickableGameObjectWorld() const override;`
- L72 _public prototype_ `virtual TStatId GetStatId() const override;`
- L77 _public function_ `ECompositeMaskingMode GetMaskingMode() const` — `UFUNCTION(BlueprintGetter)` — Get the masking mode.
- L81 _public prototype_ `void SetMaskingMode(ECompositeMaskingMode InMaskingMode);` — `UFUNCTION(BlueprintSetter)` — Set the masking mode.
- L85 _public prototype_ `const TArray<TSoftObjectPtr<AActor>> GetMaskActors() const;` — `UFUNCTION(BlueprintGetter)` — Get mask actors.
- L89 _public prototype_ `void SetMaskActors(TArray<TSoftObjectPtr<AActor>> InMaskActors);` — `UFUNCTION(BlueprintSetter)` — Set mask actors.
- L93 _public prototype_ `bool IsVisibleInSceneCaptureOnly() const;` — `UFUNCTION(BlueprintGetter)` — Get whether mask meshes are visible in scene capture only.
- L97 _public prototype_ `void SetVisibleInSceneCaptureOnly(bool bInVisible);` — `UFUNCTION(BlueprintSetter)` — Set whether mask meshes are visible in scene capture only.
- L101 _public function_ `FIntPoint GetRenderTargetResolution() const` — `UFUNCTION(BlueprintGetter)` — Get the render target resolution for the geometry mask.
- L105 _public prototype_ `void SetRenderTargetResolution(FIntPoint InRenderTargetResolution);` — `UFUNCTION(BlueprintSetter)` — Set the render target resolution for the geometry mask.
- L110 _private member_ `ECompositeMaskingMode MaskingMode;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetMaskingMode, BlueprintSetter = SetMaskingMode, Interp, Category = "Composite", meta = (AllowPrivateAccess = true))` — Masking source mode.
- L115 _public member_ `TObjectPtr<UTexture> MaskTexture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite", meta = (AllowedClasses = "/Script/Engine.Texture2D, /Script/Engine.Texture2DDynamic, /Script/Engine.TextureRenderTarget2D, /Script/MediaAssets.MediaTexture", EditCondition = "MaskingMode == ECompositeMaskingMode::Texture", EditConditionHides))` — Masking texture.
- L119 _public member_ `ECompositeColorChannel MaskSource;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Composite", meta = (EditCondition = "MaskingMode == ECompositeMaskingMode::Texture", EditConditionHides))` — Color channel used as the mask source.
- L124 _private member_ `TArray<TSoftObjectPtr<AActor>> MaskActors;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetMaskActors, BlueprintSetter = SetMaskActors, Category = "Composite", meta = (AllowPrivateAccess = true, EditCondition = "MaskingMode == ECompositeMaskingMode::Geometry", EditConditionHides))` — Actors whose mesh primitives are rendered as a geometry mask.
- L128 _private member_ `FCompositeSpawnableBindings SpawnableBindings;` — `UPROPERTY()` — Parallel spawnable binding data for the MaskActors array.
- L132 _private member_ `FIntPoint RenderTargetResolution;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetRenderTargetResolution, BlueprintSetter = SetRenderTargetResolution, Interp, Category = "Composite", meta = (AllowPrivateAccess = true, EditCondition = "MaskingMode == ECompositeMaskingMode::Geometry", EditConditionHides))` — Render target resolution for the geometry mask scene capture.
- L136 _private member_ `bool bVisibleInSceneCaptureOnly;` — `UPROPERTY(EditAnywhere, BlueprintGetter = IsVisibleInSceneCaptureOnly, BlueprintSetter = SetVisibleInSceneCaptureOnly, Category = "Composite", meta = (AllowPrivateAccess = true, EditCondition = "MaskingMode == ECompositeMaskingMode::Geometry", EditConditionHides))` — Visibility setting applied to mask actors. By default, mask meshes will only be visible in scene captures.
- L145 _public member_ `bool bInputIsPremultiplied;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Composite")` — Set true when the input texture stores premultiplied alpha (RGB already scaled by A). The pass will unpremultiply before masking and re-premultiply against the new alpha after, so RGB stays consistent with the masked alpha. Leave false for straight-alpha inputs.
- L155 _public member_ `bool bPremultipliedInDisplaySpace;` — `UPROPERTY(BlueprintReadWrite, Interp, Category = "Composite")` — Set true when the input's premultiplication was applied in sRGB display space rather than linear (e.g. an Ultimatte fill, where the upstream processor multiplies the camera fill by the matte in display before delivering it). Has no effect when bInputIsPremultiplied is false.
- L159 _public member_ `bool bInvert;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Composite")` — Invert mask alpha.
- L163 _private prototype_ `void SetMaskActorsInternal(TArray<TSoftObjectPtr<AActor>> InMaskActors);` — Apply mask-actor-change side effects without touching spawnable bindings.
- L166 _private prototype_ `UCompositeSceneCapture2DComponent* FindOrCreateSceneCaptureComponent() const;` — Find or create the scene capture component from the owning composite actor. Configures it as custom render pass on creation.
- L170 _private member_ `ECompositeMaskingMode PreEditMaskingMode = ECompositeMaskingMode::Texture;` — Cached masking mode from PreEditChange, used to detect transitions in PostEditChangeProperty.
- L174 _private prototype_ `void UpdatePrimitiveVisibilityState(bool bInVisibleInSceneCaptureOnly) const;` — Update scene capture visibility on mask actor primitives.
- L177 _private prototype_ `void RestorePrimitiveVisibilityState() const;` — Restore scene capture visibility on mask actor primitives to class defaults.

#### class `UE::Composite::Private::FMaskingPassProxy`  
`class FMaskingPassProxy : public FCompositeCorePassProxy`  
_L191-209_
- inherits: `FCompositeCorePassProxy`
- desc: Render-thread proxy for the alpha masking pass. Takes two inputs: [0] main, [1] mask.
- L194 _public prototype_ `IMPLEMENT_COMPOSITE_PASS(FMaskingPassProxy);`
- L199 _public prototype_ `FPassTexture Add(FRDGBuilder& GraphBuilder, const FSceneView& InView, const FPassInputArray& Inputs, const FPassContext& PassContext) const override;` — Adds the masking RDG pass; multiplies the main input's alpha by the chosen mask channel and returns the masked output.
- L202 _public member_ `uint32 MaskSourceChannel = 0;` — Index of the mask texture channel to read (0=R, 1=G, 2=B, 3=A).
- L204 _public member_ `bool bInputIsPremultiplied = true;` — When true, RGB is divided by alpha before masking and multiplied back after, preserving straight-alpha color values.
- L206 _public member_ `bool bPremultipliedInDisplaySpace = false;` — When true (and bInputIsPremultiplied is true), the unpremultiply step is performed in display space rather than linear so display-premult content (e.g. an Ultimatte fill) round-trips to a clean linear-premult output.
- L208 _public member_ `bool bInvert = false;` — When true, the mask value is inverted (1 − mask) before it is applied.

#### class `UCompositePassUltimatteMasking`  
`class UCompositePassUltimatteMasking : public UCompositePassBase`  
_L220-238_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta=(DisplayName="Ultimatte Masking"))`
- inherits: `UCompositePassBase`
- desc: Convenience masking pass for Ultimatte inputs. The input is always treated as premultiplied; only the mask texture and invert toggle are exposed. The mask is sampled from the red channel (the matte is delivered as a grayscale image).
- L225 _public prototype_ `UCompositePassUltimatteMasking(const FObjectInitializer& ObjectInitializer);`
- L227 _public prototype_ `virtual bool GetIsActive() const override;`
- L228 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L233 _public member_ `TObjectPtr<UTexture> MaskTexture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite", meta = (AllowedClasses = "/Script/Engine.Texture2D, /Script/Engine.Texture2DDynamic, /Script/Engine.TextureRenderTarget2D, /Script/MediaAssets.MediaTexture"))` — Masking texture. The red channel is used as the mask source (Ultimatte mattes are grayscale).
- L237 _public member_ `bool bInvert;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Composite")` — Invert mask alpha.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMPOSITE_API`
- L182 _namespace_ `namespace UE`
- L184 _namespace_ `namespace Composite` (scope `UE`)
- L186 _namespace_ `namespace Private` (scope `UE::Composite`)

### `Plugins/Compositing/Composite/Source/Composite/Public/Passes/CompositePassMaterial.h` (Public)


#### class `UCompositePassMaterial`  
`class UCompositePassMaterial : public UCompositePassBase`  
_L18-37_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta = (DisplayName = "Post-Process Material"))`
- inherits: `UCompositePassBase`
- desc: Runs a post-process material on the layer input. Input0 is mapped to the material's PostprocessInput0 SceneTexture.
- L24 _public prototype_ `UCompositePassMaterial(const FObjectInitializer& ObjectInitializer);` — Constructor
- L27 _public prototype_ `~UCompositePassMaterial();` — Destructor
- L29 _public prototype_ `virtual bool GetIsActive() const override;`
- L31 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L36 _public member_ `TObjectPtr<UMaterialInterface> PostProcessMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite")` — Post-process material to execute. Input0 is connected to SceneTexture's PostprocessInput0.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Passes/CompositePassOpenColorIO.h` (Public)


#### class `UCompositePassOpenColorIO`  
`class UCompositePassOpenColorIO : public UCompositePassBase`  
_L20-44_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta = (DisplayName = "OpenColorIO"))`
- inherits: `UCompositePassBase`
- desc: Applies an OpenColorIO color transform to the layer input. Typically used for color-space conversion or to apply a view transform.
- L26 _public prototype_ `UCompositePassOpenColorIO(const FObjectInitializer& ObjectInitializer);` — Constructor
- L28 _public prototype_ `~UCompositePassOpenColorIO();` — Destructor
- L30 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L35 _public member_ `FOpenColorIOColorConversionSettings ColorConversionSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composite")` — Color conversion settings.
- L43 _public member_ `bool bInputIsPremultiplied;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Composite")` — Set true when the input texture stores premultiplied alpha (RGB already scaled by A). The pass will unpremultiply before the color transform and re-premultiply after, so the transform operates on straight-alpha values. Leave false for straight-alpha inputs.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Passes/CompositePassSMAA.h` (Public)


#### class `UCompositePassSMAA`  
`class UCompositePassSMAA : public UCompositePassBase`  
_L16-38_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta=(DisplayName="SMAA"))`
- inherits: `UCompositePassBase`
- desc: Applies SMAA anti-aliasing to the layer input. Primarily intended for CG or motion-graphics layers rendered through a custom render pass.
- L22 _public prototype_ `UCompositePassSMAA(const FObjectInitializer& ObjectInitializer);` — Constructor
- L25 _public prototype_ `~UCompositePassSMAA();` — Destructor
- L27 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L33 _public member_ `int32 Quality;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta=(ClampMin="0", ClampMax="5", UIMin = "0", UIMax = "5"))` — SMAA quality control, matching the "r.SMAA.quality" console variable values.
- L37 _public member_ `bool bDisplayTransform = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", AdvancedDisplay)` — Apply a display transform (tonemap + gamma encode) before AA and invert it after. Improves perceptual edge detection on linear content but may darken edges at alpha boundaries.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMPOSITE_API`

### `Plugins/Compositing/Composite/Source/Composite/Public/Passes/CompositePassTransform2D.h` (Public)


#### enum `ECompositePassScaleMode`  
`enum class ECompositePassScaleMode : uint8`  
_L13-29_
- reflection: `UENUM(BlueprintType)`
- desc: Primary scale calculation mode.
- L16 _public enumerator_ `None` — Disabled
- L19 _public enumerator_ `Automatic` — Automatically derive aspect ratio from the parent layer media texture & composite actor camera.
- L22 _public enumerator_ `AspectRatio` — Scale based on the difference between container & content aspect ratios.
- L25 _public enumerator_ `Unpad` — Remove black bar padding by specifying pixels to crop on each axis.
- L28 _public enumerator_ `Manual` — Manually define the scale factor.

#### class `UCompositePassTransform2D`  
`class UCompositePassTransform2D : public UCompositePassBase`  
_L36-102_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta=(DisplayName="Transform 2D"))`
- inherits: `UCompositePassBase`
- desc: Scales, rotates and translates the layer input in UV space. Supports aspect-ratio fit, padding removal and manual scale modes.
- L42 _public prototype_ `UCompositePassTransform2D(const FObjectInitializer& ObjectInitializer);` — Constructor
- L45 _public prototype_ `~UCompositePassTransform2D();` — Destructor
- L47 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L49 _public prototype_ `virtual bool GetIsActive() const override;`
- L53 _public prototype_ `FVector2f CalculateScale() const;` — `UFUNCTION(BlueprintCallable, Category = "Composite")` — Calculate the final texture UV scale.
- L58 _public member_ `FVector2f Pivot;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite")` — Normalized pivot point for rotation and scale. (0.5, 0.5) = viewport center.
- L62 _public member_ `ECompositePassScaleMode ScaleMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite")` — How to scale-fit the video content into the camera viewport.
- L66 _public member_ `FVector2f ContainerAspectRatio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (EditCondition = "ScaleMode == ECompositePassScaleMode::AspectRatio", EditConditionHides))` — Container (source) aspect ratio, as width:height (e.g. 16:9). Automatic derives this from the plate texture.
- L70 _public member_ `FVector2f ContentAspectRatio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (EditCondition = "ScaleMode == ECompositePassScaleMode::AspectRatio", EditConditionHides))` — Content (target) aspect ratio, typically matching the cine camera, as width:height (e.g. 16:9). Automatic derives this from the camera component.
- L74 _public member_ `bool bScaleSingleAxis;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (EditCondition = "ScaleMode == ECompositePassScaleMode::Automatic || ScaleMode == ECompositePassScaleMode::AspectRatio", EditConditionHides))` — How to resolve aspect ratio mismatch. Scales only the mismatched axis, or both axes equally.
- L78 _public member_ `FIntPoint UnpadPixels;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (EditCondition = "ScaleMode == ECompositePassScaleMode::Unpad", EditConditionHides, ClampMin = "0", UIMax = "500"))` — Pixels of black bar padding to crop from each side, per axis. For example, (656, 0) removes 656px of pillarbox from left and right.
- L82 _public member_ `FVector2f ManualScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (EditCondition = "ScaleMode == ECompositePassScaleMode::Manual", EditConditionHides))` — Manual scale factor per axis. Values > 1 zoom in, values < 1 zoom out.
- L86 _public member_ `bool bRemoveOverscan;` — `UPROPERTY(BlueprintReadWrite, Category = "Composite")` — Automatically remove overscan by reading the camera's overscan value.
- L90 _public member_ `float RotationAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite", meta = (UIMin="-360.0", UIMax="360.0", ClampMin="-360.0", ClampMax="360.0"))` — Counter-clockwise rotation in degrees.
- L94 _public member_ `FVector2f Translation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Composite")` — 2D translation offset in normalized viewport coordinates. Y > 0 moves the image up.
- L98 _private prototype_ `FIntVector2 GetPlateTextureSize() const;` — Return the plate texture size from the owning plate layer, or ZeroValue if unavailable.
- L101 _private member_ `mutable TOptional<FVector2f> CachedScaleUV;` — Cached scale UV computed in GetIsActive() and reused in GetProxy(). Reset after consumption.

#### class `UE::Composite::Private::FTransform2DPassProxy`  
`class FTransform2DPassProxy : public FCompositeCorePassProxy`  
_L113-137_
- inherits: `FCompositeCorePassProxy`
- desc: Render-thread proxy for the 2D transform pass. Applies scale, rotation, and translation around a configurable pivot in UV space.
- L116 _public prototype_ `IMPLEMENT_COMPOSITE_PASS(FTransform2DPassProxy);`
- L121 _public prototype_ `FPassTexture Add(FRDGBuilder& GraphBuilder, const FSceneView& InView, const FPassInputArray& Inputs, const FPassContext& PassContext) const override;` — Adds the 2D transform RDG pass; bilinear-resamples the input with the full affine transform and returns the transformed output.
- L124 _public member_ `FVector2f Pivot = FVector2f(0.5f, 0.5f);` — Normalized pivot point for rotation and scale.
- L127 _public member_ `FVector2f ScaleUV = FVector2f::One();` — Per-axis UV scale factor. (1, 1) is identity.
- L130 _public member_ `float RotationRadians = 0.0f;` — Rotation in radians.
- L133 _public member_ `FVector2f Translation = FVector2f::ZeroVector;` — 2D translation in normalized viewport coordinates.
- L136 _public member_ `float AspectRatio = 1.0f;` — Viewport aspect ratio (width/height) for rotation correction.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMPOSITE_API`
- L104 _namespace_ `namespace UE`
- L106 _namespace_ `namespace Composite` (scope `UE`)
- L108 _namespace_ `namespace Private` (scope `UE::Composite`)

### `Plugins/Compositing/Composite/Source/Composite/Public/Passes/CompositePassTranslucency.h` (Public)


#### enum `ECompositeAlphaPremultiplication`  
`enum class ECompositeAlphaPremultiplication : uint8`  
_L14-19_
- reflection: `UENUM(BlueprintType)`
- desc: Alpha premultiplication operation type.
- L16 _public enumerator_ `None`
- L17 _public enumerator_ `Premultiply`
- L18 _public enumerator_ `Unpremultiply`

#### enum `ECompositeAlphaOverride`  
`enum class ECompositeAlphaOverride : uint8`  
_L22-27_
- reflection: `UENUM(BlueprintType)`
- L24 _public enumerator_ `None`
- L25 _public enumerator_ `Zero`
- L26 _public enumerator_ `One`

#### class `UCompositePassTranslucency`  
`class UCompositePassTranslucency : public UCompositePassBase`  
_L34-58_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, EditInlineNew, CollapseCategories, meta=(DisplayName="Translucency"))`
- inherits: `UCompositePassBase`
- desc: Modifies the layer alpha channel. Supports alpha-premultiplication toggles, fade and explicit alpha overrides.
- L40 _public prototype_ `UCompositePassTranslucency(const FObjectInitializer& ObjectInitializer);` — Constructor
- L43 _public prototype_ `~UCompositePassTranslucency();` — Destructor
- L45 _public prototype_ `virtual FCompositeCorePassProxy* GetProxy(const UE::CompositeCore::FPassInputDecl& InputDecl, FCompositeTraversalContext& InContext, FSceneRenderingBulkObjectAllocator& InFrameAllocator) const override;`
- L50 _public member_ `ECompositeAlphaPremultiplication PremultOp;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Composite")` — Alpha premultiplication operation.
- L54 _public member_ `float Fade = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Composite", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Fade the alpha from 0 to 1. Assumes pre-multiplied alpha, so both RGB and A are scaled together.
- L57 _public member_ `ECompositeAlphaOverride OverrideOutputAlpha;` — `UPROPERTY()`

#### class `UE::Composite::Private::FTranslucencyPassProxy`  
`class FTranslucencyPassProxy : public FCompositeCorePassProxy`  
_L69-85_
- inherits: `FCompositeCorePassProxy`
- desc: Render-thread proxy for the translucency pass. Applies alpha premultiplication, fade, and optional alpha override.
- L72 _public prototype_ `IMPLEMENT_COMPOSITE_PASS(FTranslucencyPassProxy);`
- L77 _public prototype_ `FPassTexture Add(FRDGBuilder& GraphBuilder, const FSceneView& InView, const FPassInputArray& Inputs, const FPassContext& PassContext) const override;` — Adds the translucency RDG pass and returns the modified output texture.
- L80 _public member_ `ECompositeAlphaPremultiplication PremultOp = ECompositeAlphaPremultiplication::None;` — Whether to premultiply, unpremultiply, or leave alpha unchanged before applying Fade.
- L82 _public member_ `float Fade = 1.0f;` — Uniform multiplier applied to the output (0 = fully transparent, 1 = unchanged).
- L84 _public member_ `ECompositeAlphaOverride OverrideOutputAlpha = ECompositeAlphaOverride::None;` — Optionally force the output alpha to 0 or 1 after all other operations.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMPOSITE_API`
- L60 _namespace_ `namespace UE`
- L62 _namespace_ `namespace Composite` (scope `UE`)
- L64 _namespace_ `namespace Private` (scope `UE::Composite`)
