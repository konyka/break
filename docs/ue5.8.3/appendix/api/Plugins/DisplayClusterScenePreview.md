# Plugins / DisplayClusterScenePreview

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterScenePreview`
- headers: 5; symbols: 242
- symbol kinds: class=3, delegate=1, enum=3, enumerator=20, function=17, member=57, prototype=134, struct=7
- PrivateDependencyModuleNames: Core, CoreUObject, DisplayClusterConfiguration, Engine, ProceduralMeshComponent, RenderCore, UnrealEd
- PublicDependencyModuleNames: DisplayCluster, DisplayClusterLightCardEditorShaders, DisplayClusterLightCardExtender, RHI

### `Plugins/Runtime/nDisplay/Source/DisplayClusterScenePreview/Private/DisplayClusterScenePreviewModule.h` (Private)


#### enum `EDisplayClusterRendererConfigFlags`  
`enum class EDisplayClusterRendererConfigFlags : uint16`  
_L21-60_
- desc: Flags for the renderer config.
- L23 _public enumerator_ `None = 0`
- L26 _public enumerator_ `ObjectTransacted = 1 << 0` — Updated in OnObjectTransacted().
- L29 _public enumerator_ `BlueprintCompiled = 1 << 1` — When BP is recompiled.
- L32 _public enumerator_ `LevelActorAdded = 1 << 2` — OnLevelActorAdded()
- L35 _public enumerator_ `LevelActorDeleted = 1 << 3` — OnLevelActorDeleted()
- L38 _public enumerator_ `LevelActorBeingModified = 1 << 4` — OnActorPropertyChanged() for objects owned by the RootActor.
- L41 _public enumerator_ `RootActorBeingModified = 1 << 5` — OnActorPropertyChanged() for the RootActor.
- L44 _public enumerator_ `UpdateRootActorRef = 1 << 6` — The reference to RootActor has been updated.
- L47 _public enumerator_ `UpdateRootActorProxyRef = 1 << 7` — The reference to RootActorProxy has been updated.
- L50 _public enumerator_ `LostRootActorRef = 1 << 8` — we have lost the reference to the RootActor, it needs to be restored in another way.
- L53 _public enumerator_ `RootActorPathModified = 1 << 9` — RootActorPath has been changed.
- L56 _public enumerator_ `RootActorPropertyOverridesModified = 1 << 14` — Root actor property overrides has been changed.
- L59 _public enumerator_ `PreviewFlagsModified = 1 << 15` — RootActor preview flags has been changed.

#### class `FDisplayClusterScenePreviewModule`  
`class FDisplayClusterScenePreviewModule : public IDisplayClusterScenePreview`  
_L66-316_
- inherits: `IDisplayClusterScenePreview`
- desc: Module containing tools for rendering nDisplay scene previews.
- L71 _public prototype_ `virtual void StartupModule() override;`
- L72 _public prototype_ `virtual void ShutdownModule() override;`
- L75 _public prototype_ `virtual int32 CreateRenderer() override;`
- L76 _public prototype_ `virtual bool DestroyRenderer(int32 RendererId) override;`
- L77 _public prototype_ `virtual bool SetRendererRootActorPath(int32 RendererId, const FString& ActorPath, const FDisplayClusterRootActorPropertyOverrides& InPropertyOverrides, const EDisplayClusterScenePreviewFlags PreviewFlags = EDisplayClusterScenePreviewFlags::None) override;`
- L78 _public prototype_ `virtual bool SetRendererRootActor(int32 RendererId, ADisplayClusterRootActor* Actor, const FDisplayClusterRootActorPropertyOverrides& InPropertyOverrides, const EDisplayClusterScenePreviewFlags PreviewFlags = EDisplayClusterScenePreviewFlags::None) override;`
- L79 _public prototype_ `virtual ADisplayClusterRootActor* GetRendererRootActor(int32 RendererId) override;`
- L80 _public prototype_ `virtual ADisplayClusterRootActor* GetRendererRootActorOrProxy(int32 RendererId) override;`
- L82 _public function_ `virtual bool GetActorsInRendererScene(int32 RendererId, bool bIncludeRoot, TArray<AActor*>& OutActors) override`
- L88 _public function_ `virtual bool AddActorToRenderer(int32 RendererId, AActor* Actor) override`
- L94 _public function_ `virtual bool AddActorToRenderer(int32 RendererId, AActor* Actor, const TFunctionRef<bool(const UPrimitiveComponent*)>& PrimitiveFilter) override`
- L100 _public function_ `virtual bool RemoveActorFromRenderer(int32 RendererId, AActor* Actor) override`
- L106 _public function_ `virtual bool ClearRendererScene(int32 RendererId) override`
- L112 _public function_ `virtual bool SetRendererActorSelectedDelegate(int32 RendererId, FDisplayClusterMeshProjectionRenderer::FSelection ActorSelectedDelegate) override`
- L118 _public function_ `virtual bool SetRendererRenderSimpleElementsDelegate(int32 RendererId, FDisplayClusterMeshProjectionRenderer::FSimpleElementPass RenderSimpleElementsDelegate) override`
- L124 _public prototype_ `virtual bool Render(int32 RendererId, FDisplayClusterMeshProjectionRenderSettings& RenderSettings, FCanvas& Canvas) override;`
- L125 _public prototype_ `virtual bool RenderQueued(int32 RendererId, FDisplayClusterMeshProjectionRenderSettings& RenderSettings, const FIntPoint& Size, FRenderResultDelegate ResultDelegate) override;`
- L126 _public prototype_ `virtual bool RenderQueued(int32 RendererId, FDisplayClusterMeshProjectionRenderSettings& RenderSettings, const TWeakPtr<FCanvas> Canvas, FRenderResultDelegate ResultDelegate) override;`
- L127 _public prototype_ `virtual bool IsRealTimePreviewEnabled() const override;`
- L233 _private prototype_ `void InternalUpdateRendererConfig(int32 RendererId, FRendererConfig& RendererConfig);` — Handle all changes in the renderer config.
- L236 _private prototype_ `ADisplayClusterRootActor* InternalGetRendererRootActor(int32 RendererId, FRendererConfig& RendererConfig);` — Get the root actor for a config. If the root actor pointer is invalid but we have a path to the actor, try to reacquire a pointer using the path first.
- L239 _private prototype_ `ADisplayClusterRootActor* InternalGetRendererRootActorOrProxy(int32 RendererId, FRendererConfig& RendererConfig);` — Get the root actor or proxy.
- L242 _private prototype_ `void InternalSetRendererRootActor(int32 RendererId, FRendererConfig& RendererConfig, ADisplayClusterRootActor* Actor);` — Set the root actor for a config, update its scene, and register events accordingly.
- L245 _private prototype_ `bool InternalRenderQueued(int32 RendererId, FDisplayClusterMeshProjectionRenderSettings& RenderSettings, TWeakPtr<FCanvas> Canvas, const FIntPoint& Size, FRenderResultDelegate ResultDelegate);` — Queue a preview to be rendered.
- L249 _private prototype_ `bool InternalRenderImmediate(int32 RendererId, FRendererConfig& RendererConfig, FDisplayClusterMeshProjectionRenderSettings& RenderSettings, FCanvas& Canvas);` — Immediately render with the given renderer config and settings to the given canvas.
- L252 _private prototype_ `void RegisterOrUnregisterGlobalActorEvents();` — Check if any of the tracked root actors are set to auto-update their lightcards and register/unregister event listeners accordingly.
- L255 _private prototype_ `void RegisterRootActorEvents(int32 RendererId, FRendererConfig& RendererConfig, bool bShouldRegister);` — Register/unregister to events affecting a cluster root actor.
- L258 _private prototype_ `void AutoPopulateScene(int32 RendererId, FRendererConfig& RendererConfig);` — Clear and re-populate a renderer's scene with the root actor and lightcards if applicable.
- L261 _private prototype_ `bool UpdateIsRealTimePreviewEnabled();` — Check whether nDisplay preview textures are being updated in real time.
- L264 _private prototype_ `bool OnTick(float DeltaTime);` — Called on tick to process the queued renders.
- L267 _private prototype_ `void OnActorPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);` — Called when a property on a root DisplayCluster actor has changed.
- L270 _private prototype_ `void OnLevelActorDeleted(AActor* Actor);` — Called when the user deletes an actor from the level.
- L273 _private prototype_ `void OnLevelActorAdded(AActor* Actor);` — Called when the user adds an actor to the level.
- L276 _private prototype_ `void OnBlueprintCompiled(UBlueprint* Blueprint);` — Called when a blueprint for an actor we care about is compiled.
- L279 _private prototype_ `void OnObjectTransacted(UObject* Object, const FTransactionObjectEvent& TransactionObjectEvent);` — Called when any object is transacted.
- L282 _private prototype_ `void Release();` — release all internals data.
- L285 _private prototype_ `FDisplayClusterScenePreviewProxyManager& GetProxyManager();` — Return ProxyManager object.
- L290 _private member_ `FDelegateHandle EditorClosedEventHandle;` — Callbacks
- L291 _private prototype_ `void OnEditorClosed();`
- L297 _private member_ `TMap<int32, FRendererConfig> RendererConfigs;` — Map from renderer ID to configuration data for that renderer.
- L300 _private member_ `TQueue<FPreviewRenderJob> RenderQueue;` — Queue of render jobs pending completion.
- L303 _private member_ `FTSTicker::FDelegateHandle RenderTickerHandle;` — Handle for the render ticker.
- L306 _private member_ `int32 NextRendererId = 0;` — The ID to use for the next created renderer.
- L309 _private member_ `bool bIsRegisteredForActorEvents = false;` — Whether this is currently registered for actor update events.
- L312 _private member_ `bool bIsRealTimePreviewEnabled = false;` — Whether nDisplay preview textures are being updated in real time.
- L315 _private member_ `TUniquePtr<FDisplayClusterScenePreviewProxyManager> ProxyManagerPtr;` — Manager for DCRA proxy objects.

#### struct `FDisplayClusterScenePreviewModule::FRendererConfig`  
`struct FRendererConfig`  
_L132-200_
- desc: Holds information about an active renderer created by this module.
- L135 _public prototype_ `bool GetActorsInRendererScene(bool bIncludeRoot, TArray<AActor*>& OutActors);` — Get the actors that were used in this render scene.
- L138 _public prototype_ `bool AddActorToRenderer(AActor* Actor, bool bAutoPopulate = false);` — Add actor to renderer.
- L141 _public prototype_ `bool AddActorToRenderer(AActor* Actor, const TFunctionRef<bool(const UPrimitiveComponent*)>& PrimitiveFilter, bool bAutoPopulate = false);` — Add actor to renderer with primitive filter.
- L144 _public prototype_ `bool RemoveActorFromRenderer(AActor* Actor);` — remove actor from renderer.
- L147 _public prototype_ `bool ClearRendererScene();` — Clear renderer scene.
- L149 _public prototype_ `bool SetRendererActorSelectedDelegate(FDisplayClusterMeshProjectionRenderer::FSelection ActorSelectedDelegate);`
- L150 _public prototype_ `bool SetRendererRenderSimpleElementsDelegate(FDisplayClusterMeshProjectionRenderer::FSimpleElementPass RenderSimpleElementsDelegate);`
- L153 _public prototype_ `bool IsBlueprintMatchesRendererRootActor(UBlueprint* Blueprint) const;` — Returns true if the Blueprint class matches the RootActor class used in the renderer configuration.
- L156 _public prototype_ `ADisplayClusterRootActor* GetRootActor();` — Get root of the display cluster that this renderer is previewing.
- L159 _public prototype_ `bool SetRootActor(ADisplayClusterRootActor* InRootActorPtr);` — Set new root actor ptr.
- L162 _public prototype_ `bool IsRootActorEquals(ADisplayClusterRootActor* InRootActorPtr) const;` — Compare current root actor ptr and input.
- L165 _public function_ `bool IsDefinedRootActor() const` — return true if RootActor already defined.
- L171 _public member_ `TWeakObjectPtr<UBlueprint> RootActorBlueprintClass;` — Reference to root actor BP.
- L174 _public member_ `TSharedPtr<FDisplayClusterMeshProjectionRenderer> Renderer;` — The renderer itself.
- L177 _public member_ `FString RootActorPath;` — The path of the root actor that this renderer is previewing. If this is not empty and the root actor becomes invalid, we will attempt to find it again using this path.
- L180 _public member_ `TArray<TWeakObjectPtr<AActor>> AddedActors;` — All actors that have been added to the renderer (except for the root actor).
- L183 _public member_ `TArray<TWeakObjectPtr<AActor>> AutoPopulateActors;` — Actors that have been automatically added to the scene.
- L186 _public member_ `EDisplayClusterScenePreviewFlags PreviewFlags = EDisplayClusterScenePreviewFlags::None;` — Special flags that control the behavior of the renderer.
- L189 _public member_ `FDisplayClusterRootActorPropertyOverrides RootActorPropertyOverrides;` — Container with properties to be overridden for the root actor used by this renderer.
- L192 _public member_ `EDisplayClusterRendererConfigFlags Flags = EDisplayClusterRendererConfigFlags::None;` — Renderer flags.
- L195 _public member_ `TStrongObjectPtr<UTextureRenderTarget2D> RenderTarget = nullptr;` — The render target to use for queued renders.
- L199 _private member_ `FDisplayClusterActorRef RootActorRef;` — Saved reference to the root actor. It is used to restore a reference to a new root actor object after BP recompilation.

#### struct `FDisplayClusterScenePreviewModule::FPreviewRenderJob`  
`struct FPreviewRenderJob`  
_L203-230_
- desc: Holds information about a preview render that was queued to be completed later.
- L205 _public function_ `FPreviewRenderJob()`
- L207 _public function_ `FPreviewRenderJob(int32 RendererId, const FDisplayClusterMeshProjectionRenderSettings& Settings, const FIntPoint& Size, TWeakPtr<FCanvas> Canvas, FRenderResultDelegate ResultDelegate) : RendererId(RendererId), Settings(Settings), Size(Size), Canvas(Canvas), bWasCanvasProvided(Canvas.IsValid()), ResultDelegate(ResultDelegate)`
- L214 _public member_ `int32 RendererId;` — The ID of the renderer to use.
- L217 _public member_ `FDisplayClusterMeshProjectionRenderSettings Settings;` — The settings to use for the render.
- L220 _public member_ `FIntPoint Size;` — The size of the image to render.
- L223 _public member_ `TWeakPtr<FCanvas> Canvas;` — The canvas to render to, if provided.
- L226 _public member_ `bool bWasCanvasProvided;` — Whether a canvas was provided for this job.
- L229 _public member_ `FRenderResultDelegate ResultDelegate;` — The delegate to call when the render is completed.

#### Free symbols / members of external scopes

- L61 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterRendererConfigFlags);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterScenePreview/Private/DisplayClusterScenePreviewProxyManager.h` (Private)


#### class `FDisplayClusterScenePreviewProxyManager`  
`class FDisplayClusterScenePreviewProxyManager : public FGCObject`  
_L15-102_
- inherits: `FGCObject`
- desc: Creates and handle DCRA proxies.
- L18 _public prototype_ `~FDisplayClusterScenePreviewProxyManager();`
- L26 _public prototype_ `void SetSceneRootActorForRenderer(int32 RendererId, ADisplayClusterRootActor* RootActor, EDisplayClusterScenePreviewFlags PreviewFlags);` — Assign SceneRootActor to the renderer with the specified ID to create a root proxy actor for it. @param RendererId - ID of renderer that uses this DCRA @param RootActor  - the new scene root actor that used by this renderer Note: If RootActor is null, it means that the renderer is no longer using the proxy.
- L36 _public prototype_ `ADisplayClusterRootActor* GetProxyRootActor(int32 RendererId) const;` — Get the DCRA proxy for the renderer by id. @param RendererId - ID of renderer that uses this DCRA @return - A reference to the RootActor proxy, if it exists, or nullptr. Note: You must call SetSceneRootActorForRenderer() for the renderer and the root actor being used before using this function.
- L46 _public prototype_ `ADisplayClusterRootActor* GetSceneRootActor(int32 RendererId) const;` — Get the DCRA in scene used to create a proxy for the renderer by id. @param RendererId - ID of renderer that uses this DCRA @return - A reference to the RootActor in scene, if it exists, or nullptr. Note: You must call SetSceneRootActorForRenderer() for the renderer and the root actor being used before using this function.
- L49 _public prototype_ `void TickPreviewWorld(float DeltaTime);` — Run the Tick() function for the preview world.
- L52 _public prototype_ `void Release();` — Release all internal data.
- L56 _private prototype_ `void OnTick(float DeltaTime);` — This function calls Tick() for a preview world with proxy root actors, which triggers rendering of previews for them.
- L57 _private prototype_ `void CreatePreviewWorld();`
- L58 _private prototype_ `void DestroyPreviewWorld();`
- L61 _private prototype_ `ADisplayClusterRootActor* CreateRootActorProxy(int32 RendererId, ADisplayClusterRootActor* SceneRootActor);` — Create RootActor proxy.
- L63 _private prototype_ `void DestroyRootActorProxy(ADisplayClusterRootActor* ProxyRootActor);`
- L66 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L67 _private prototype_ `virtual FString GetReferencerName() const override;`
- L94 _private member_ `TMap<int32, FRendererProxy> RendererProxies;` — Registered proxies for renderers by ID.
- L97 _private member_ `TObjectPtr<class UWorld> PreviewWorld = nullptr;` — The preview world is only used when using the DCRA proxy.
- L101 _private member_ `TUniquePtr<FDisplayClusterTickableGameObject> TickableGameObject;` — When CachedObjects is not empty, this ticking object will be created. Also, this object will be deleted when CachedObjects becomes empty.

#### struct `FDisplayClusterScenePreviewProxyManager::FRendererProxy`  
`struct FRendererProxy`  
_L72-91_
- desc: Container for RootActorProxy and related data.
- L75 _public prototype_ `ADisplayClusterRootActor* GetProxyRootActor() const;` — Get value from the ProxyRootActorWeakPtr variable.
- L78 _public prototype_ `ADisplayClusterRootActor* GetSceneRootActor() const;` — Get value from the SceneRootActorWeakPtr variable.
- L81 _public prototype_ `void TickProxyRootActor() const;` — Update ProxyRootActor.
- L84 _public member_ `TWeakObjectPtr<ADisplayClusterRootActor> ProxyRootActorWeakPtr;` — RootActorProxy object created based on the RootActor in the scene.
- L87 _public member_ `TWeakObjectPtr<ADisplayClusterRootActor> SceneRootActorWeakPtr;` — RootActor in scene that used to create DCRA proxy
- L90 _public member_ `EDisplayClusterScenePreviewFlags PreviewFlags;` — Special flags that control the behavior of the renderer.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterScenePreview/Public/DisplayClusterLightCardEditorHelper.h` (Public)


#### struct `FDisplayClusterLightCardEditorHelper`  
`struct FDisplayClusterLightCardEditorHelper`  
_L33-407_
- desc: Helper class for moving lightcards in an nDisplay cluster in various projection modes. Contains functions to perform coordinate conversion, scene setup, and lightcard movement, and manages the normal maps needed to convert from projected to world coordinates.
- L75 _public prototype_ `FDisplayClusterLightCardEditorHelper();` — Create a projection helper that automatically creates its own preview renderer for normal map generation.
- L78 _public prototype_ `FDisplayClusterLightCardEditorHelper(int32 RendererId);` — Create a projection helper that uses an existing preview renderer for normal map generation.
- L81 _public prototype_ `~FDisplayClusterLightCardEditorHelper();` — Clean up the projection renderer and any data used by the helper.
- L85 _public prototype_ `void SetEditorViewportClient(TWeakPtr<FEditorViewportClient> InViewportClient);` — Set the viewport client for which this is handling rendering. If set, its data will be included in the SceneViewInitOptions generated by this helper.
- L89 _public prototype_ `void SetProjectionMode(EDisplayClusterMeshProjectionType Value);` — Set the projection mode to use.
- L92 _public prototype_ `EDisplayClusterMeshProjectionType GetProjectionMode() const;` — Get the projection mode to use.
- L95 _public prototype_ `void SetIsOrthographic(bool bValue);` — Set whether to use an orthographic projection.
- L98 _public prototype_ `bool GetIsOrthographic() const;` — Get whether this is using an orthographic projection.
- L104 _public prototype_ `void SetRootActor(ADisplayClusterRootActor& NewRootActor);` — Set the root actor of the DisplayCluster being controlled. This will also update the renderer's root actor. Don't call this if the helper was created with an existing preview renderer, as it will automatically the root actor from that renderer.
- L109 _public prototype_ `void SetLevelInstanceRootActor(ADisplayClusterRootActor& NewRootActor);` — If the root actor is a proxy, use this to set the corresponding level instance that is being proxied.
- L117 _public prototype_ `const UTexture2D* GetNormalMapTexture(bool bShowNorthMap);` — `UE_DEPRECATED(5.3, "The raw stage geoemetry normal maps are no longer exposed by the stage geometry component")` — Get (or generate) a visualization of one of the helper's normal maps. @param bShowNorthMap If true, return the texture for the north normal map. Otherwise, return the texture for the south normal map.
- L126 _public prototype_ `void MoveActorsToPixel(const TArray<FDisplayClusterWeakStageActorPtr>& Actors, const FIntPoint& PixelPos, const FSceneView& SceneView);` — Moves the given light cards to the specified pixel position within the provided scene view. @param Actors The actors that we are moving @param PixelPos The pixel location to move the actors to @param SceneView The scene view used to convert from pixel position to 3D position
- L134 _public prototype_ `void MoveActorsTo(const TArray<FDisplayClusterWeakStageActorPtr>& Actors, const FSphericalCoordinates& SphericalCoords);` — Moves specified actors to desired coordinates. Actual radius will be based on flush constraint and actor's RadialOffset. @param Actors The actors that we are moving @param SphericalCoords The desired location of the actors in spherical coordinates with respect to origin.
- L147 _public prototype_ `void DragActors(const TArray<FDisplayClusterWeakStageActorPtr>& Actors, const FIntPoint& PixelPos, const FSceneView& SceneView, ECoordinateSystem CoordinateSystem, const FVector& DragWidgetOffset, EAxisList::Type DragAxis, FDisplayClusterWeakStageActorPtr PrimaryActor = nullptr);` — Moves specified cards to a coordinate in viewport space as if dragged by a translate widget. @param Actors The actors that we are moving @param PixelPos The screen pixel position of the widget @param SceneView The scene view used to convert from pixel position to 3D position @param CoordinateSystem The coordinate system to use when computing drag constraints @param DragWidgetOffset The offset between the actual cursor position and the position of the widget when the drag action started @param DragAxis The axis along which the widget is being dragged @param PrimaryActor The actor used to calculate the translation/rotation delta. If not provided, the last entry in Actors will be used.
- L160 _public prototype_ `void DragUVActors(const TArray<FDisplayClusterWeakStageActorPtr>& Actors, const FIntPoint& PixelPos, const FSceneView& SceneView, const FVector& DragWidgetOffset, EAxisList::Type DragAxis, FDisplayClusterWeakStageActorPtr PrimaryActor = nullptr);` — Moves specified UV actors to a coordinate in viewport space as if dragged by a translate widget. @param Actors The actors that we are moving @param PixelPos The screen pixel position of the widget @param SceneView The scene view used to convert from pixel position to 3D position @param DragWidgetOffset The offset between the actual cursor position and the position of the widget when the drag action started @param DragAxis The axis along which the widget is being dragged @param PrimaryActor The actor used to calculate the translation/rotation delta. If not provided, the last entry in Actors will be used.
- L164 _public prototype_ `void VerifyAndFixActorOrigin(const FDisplayClusterWeakStageActorPtr& Actor);` — Ensures that the actor root component is at the same location as the projection/origin
- L176 _public prototype_ `bool CalculateNormalAndPositionInDirection(const FVector& InOrigin, const FVector& InDirection, FVector& OutWorldPosition, FVector& OutRelativeNormal, double InDesiredDistanceFromFlush = 0.);` — Calculates the relative normal vector and world position in the specified direction from the given origin. @param InOrigin The origin point of the view. @param InDirection The direction in which check the normal. @param OutWorldPosition The world-space coordinates of the calculated position. @param OutRelativeNormal The normal vector at the calculated position. @param InDesiredDistanceFromFlush The desired flush distance from the initial calculated position. @return true if the position was found, or false if the normal maps need to be updated first.
- L189 _public prototype_ `bool CalculateOriginAndDirectionFromPixelPosition(const FIntPoint& InPixelPos, const FSceneView& InSceneView, const FVector& InOriginOffset, FVector& OutOrigin, FVector& OutDirection);` — Calculates the desired direction from the origin given a pixel position within the view. @param InPixelPos The desired position within the view in pixels. @param InSceneView The view that was displayed when the pixel position was chosen. @param InOriginOffset An offset to apply to the origin before calling TraceScreenRay (if this is in orthographic mode). @param OutOrigin The origin point of the view. @param OutDirection The direction relative to the origin. @return true if the direction was found
- L193 _public prototype_ `void PixelToWorld(const FSceneView& View, const FIntPoint& PixelPos, FVector& OutOrigin, FVector& OutDirection) const;` — Converts a pixel coordinate into a point and direction vector in world space
- L196 _public prototype_ `bool WorldToPixel(const FSceneView& View, const FVector& WorldPos, FVector2D& OutPixelPos) const;` — Converts a world coordinate into a point in screen space, and returns true if the world position is on the screen.
- L199 _public prototype_ `bool WorldToPixel(const FSceneView& View, const FVector& WorldPos, FVector2D& OutPixelPos, EDisplayClusterMeshProjectionType OverrideProjectionMode) const;` — Converts a world coordinate into a point in screen space using a specific projection mode, and returns true if the world position is on the screen.
- L205 _public prototype_ `void GetSceneViewInitOptions( FSceneViewInitOptions& OutViewInitOptions, float InFOV, const FIntPoint& InViewportSize, const FVector& InLocation, const FRotator& InRotation, const EAspectRatioAxisConstraint InAspectRatioAxisConstraint = EAspectRatioAxisConstraint::AspectRatio_MaintainYFOV, float InNearClipPlane = GNearClippingPlane, const FMatrix* InRotationMatrix = nullptr, float InDPIScale = 1.f);` — Sets up FSceneViewInitOptions' basic settings in a consistent way for preview renders. If RotationMatrix is not provided, one will be automatically generated based on the view rotation.
- L221 _public prototype_ `void ConfigureRenderProjectionSettings(FDisplayClusterMeshProjectionRenderSettings& OutRenderSettings, FVector ViewLocation = FVector::ZeroVector) const;` — Sets up projection-related settings of a preview render in a consistent way. This includes the ProjectionType and its related ProjectionTypeSettings. If provided, the UV projection's panning settings will updated to reflect the ViewLocation passed in.
- L224 _public prototype_ `FSphericalCoordinates GetActorCoordinates(const FDisplayClusterWeakStageActorPtr& Actor);` — Gets the spherical coordinates of the specified actor.
- L230 _public prototype_ `FDisplayClusterMeshProjectionPrimitiveFilter::FPrimitiveFilter CreateDefaultShouldRenderPrimitiveFilter() const;` — Creates the default ShouldRenderPrimitive filter that most FDisplayClusterMeshProjectionRenderSettings will use. Filters actors so that only UV lightcards are shown in UV mode, and only non-UV light cards are shown otherwise.
- L236 _public prototype_ `FDisplayClusterMeshProjectionPrimitiveFilter::FPrimitiveFilter CreateDefaultShouldApplyProjectionToPrimitiveFilter() const;` — Creates the default ShouldApplyProjectionToPrimitive filter that most FDisplayClusterMeshProjectionRenderSettings will use. Filters actors so that in UV projection mode, UV light cards are rendered linearly.
- L291 _public prototype_ `static AActor* SpawnStageActor(const FSpawnActorArgs& InSpawnArgs);` — Spawns a new actor for stage use and adds it to the root actor if it is a light card
- L294 _public prototype_ `static void AddLightCardsToRootActor(const TArray<ADisplayClusterLightCardActor*>& LightCards, ADisplayClusterRootActor* RootActor, const FAddLightCardArgs& AddLightCardArgs = FAddLightCardArgs());` — Adds the given Light Card to the root actor
- L302 _private prototype_ `ADisplayClusterRootActor* UpdateRootActor();` — Update the cached pointer to the root actor from the associated preview renderer and, if the actor has changed, update related data. Returns the root actor.
- L308 _private prototype_ `USceneComponent* UpdateProjectionOriginComponent();` — Update the cached pointer to the component marking the origin point of the projection and return it. Note that this has a cost, so avoid calling it frequently.
- L311 _private prototype_ `FVector GetProjectionOrigin() const;` — Get the origin point of the projection from the ProjectionOriginComponent (or root actor as a fallback).
- L314 _private prototype_ `FRotator GetActorRotationDelta(const FIntPoint& PixelPos, const FSceneView& View, const FDisplayClusterWeakStageActorPtr& Actor, ECoordinateSystem CoordinateSystem, EAxisList::Type DragAxis, const FVector& DragWidgetOffset);` — Determines the appropriate delta rotation needed to move the specified light card to the given position within the view.
- L318 _private prototype_ `FSphericalCoordinates GetActorTranslationDelta(const FIntPoint& PixelPos, const FSceneView& View, const FDisplayClusterWeakStageActorPtr& Actor, ECoordinateSystem CoordinateSystem, EAxisList::Type DragAxis, const FVector& DragWidgetOffset);` — Determines the appropriate delta in spherical coordinates needed to move the specified actor to the given position within the view.
- L322 _private prototype_ `FVector2D GetUVActorTranslationDelta(const FIntPoint& PixelPos, const FSceneView& View, const FDisplayClusterWeakStageActorPtr& Actor, EAxisList::Type DragAxis, const FVector& DragWidgetOffset);` — Determines the appropriate delta in UV coordinates needed to move the specified UV actor to the given position within the view.
- L326 _private prototype_ `void InternalMoveActorTo(const FDisplayClusterWeakStageActorPtr& Actor, const FSphericalCoordinates& Position, bool bIsFinalChange) const;` — Moves specified actor to desired coordinates immediately using the current normal maps. Requires valid normal maps.
- L329 _private prototype_ `void InternalDragActors(const TArray<FDisplayClusterWeakStageActorPtr>& Actors, const FIntPoint& PixelPos, const FSceneView& View, ECoordinateSystem CoordinateSystem, const FVector& DragWidgetOffset, EAxisList::Type DragAxis, FDisplayClusterWeakStageActorPtr PrimaryActor);` — Moves specified actors to a coordinate in viewport space as if dragged by a widget. Requires valid normal maps.
- L333 _private prototype_ `void SetActorCoordinates(const FDisplayClusterWeakStageActorPtr& Actor, const FSphericalCoordinates& SphericalCoords) const;` — Sets the actor position to the given spherical coordinates
- L336 _private prototype_ `bool TraceStage(const FVector& RayStart, const FVector& RayEnd, FVector& OutHitLocation);` — Performs a ray trace against the stage's geometry, and returns the hit point.
- L339 _private prototype_ `FVector TraceScreenRay(const FVector& RayOrigin, const FVector& RayDirection, const FVector& ViewOrigin);` — Traces the world geometry to find the best direction vector from the origin to a valid point in space using a screen ray. Requires valid normal maps.
- L342 _private prototype_ `double CalculateFinalLightCardDistance(double FlushDistance, double DesiredOffsetFromFlush = 0.) const;` — Calculates the final distance from the origin of a light card, given its flush distance and a desired offset
- L345 _private prototype_ `void InvalidateNormalMap();` — Invalidates the viewport's normal map, forcing it to be re-rendered before using it next
- L348 _private prototype_ `bool UpdateNormalMaps();` — Update the normal maps and mesh if necessary. Returns true if there are now valid normal maps to read from.
- L351 _private prototype_ `void UpdateNormalMapMesh();` — Update the normal map mesh. Only call this once both maps are valid.
- L354 _private prototype_ `void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);` — Called when a world beings cleanup. We destroy our preview scene if the world containing the root actor is cleaned up.
- L358 _private prototype_ `void OnActorPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);` — Called when any actor properties changed, so we can invalidate normals if it is the root actor.
- L361 _private prototype_ `void OnRootActorBlueprintCompiled(UBlueprint* Blueprint);` — Called when the root actor's blueprint is compiled so we can invalidate normals.
- L366 _private prototype_ `void PostEditChangePropertiesForMovedActor(const FDisplayClusterWeakStageActorPtr& Actor) const;` — Send property change events for any properties that may have changed due to a actor being moved.
- L372 _private member_ `TWeakPtr<FEditorViewportClient> ViewportClient;` — The viewport client for which this is handling projections. This can be null.
- L376 _private member_ `TSharedPtr<FPreviewScene> NormalMeshScene;` — The preview scene containing NormalMapMeshComponent.
- L379 _private member_ `TWeakObjectPtr<UProceduralMeshComponent> NormalMapMeshComponent;` — A morphed ico-sphere mesh component that approximates the normal and depth map.
- L382 _private member_ `TWeakObjectPtr<ADisplayClusterRootActor> CachedRootActor;` — The cached root actor of the DisplayCluster being controlled. You should generally use UpdateRootActor() instead of accessing this directly.
- L385 _private member_ `TWeakObjectPtr<ADisplayClusterRootActor> LevelInstanceRootActor;` — The level instance root actor of the DisplayCluster being controlled, if RootActor is a proxy.
- L388 _private member_ `TWeakObjectPtr<USceneComponent> ProjectionOriginComponent;` — The component of the root actor that is acting as the projection origin. Can be either the root component (stage origin) or a view point component
- L391 _private member_ `EDisplayClusterMeshProjectionType ProjectionMode;` — The projection mode of the view this is helping.
- L394 _private member_ `int32 RendererId;` — The ID of the preview renderer used for normal map generation, as returned by IDisplayClusterScenePreview.
- L397 _private member_ `float RootActorBoundingRadius = 0.0f;` — The radius of the bounding sphere that entirely encapsulates the root actor
- L400 _private member_ `bool bCreatedRenderer = false;` — Whether this created its own preview renderer (and therefore is responsible for destroying it).
- L403 _private member_ `bool bIsOrthographic = false;` — If true, this is using an orthographic projection mode.
- L406 _private member_ `bool bNormalMapInvalid = false;` — Indicates if the cached normal map is invalid and needs to be redrawn

#### enum `FDisplayClusterLightCardEditorHelper::ECoordinateSystem`  
`enum class ECoordinateSystem : uint8`  
_L36-40_
- L38 _public enumerator_ `Cartesian`
- L39 _public enumerator_ `Spherical`

#### struct `FDisplayClusterLightCardEditorHelper::FSphericalCoordinates`  
`struct FSphericalCoordinates`  
_L42-71_
- L47 _public prototype_ `FSphericalCoordinates(const FVector& CartesianPosition);` — Constructors
- L48 _public prototype_ `FSphericalCoordinates();`
- L51 _public prototype_ `FVector AsCartesian() const;` — Return equivalent cartesian coordinates
- L54 _public prototype_ `FSphericalCoordinates operator+(FSphericalCoordinates const& Other) const;` — Addition operator
- L57 _public prototype_ `FSphericalCoordinates operator-(FSphericalCoordinates const& Other) const;` — Subtraction operator
- L60 _public prototype_ `void Conform();` — Conform parameters to their normal ranges
- L63 _public prototype_ `FSphericalCoordinates GetConformed() const;` — Returns a conformed version of this struct without changing the current one
- L66 _public prototype_ `bool IsPointingAtPole(double Margin = 1e-6) const;` — Returns true if the inclination is pointing at north or south poles, within the given margin (in radians)
- L68 _public member_ `double Radius = 0;` — unitless   0+      (when conforming)
- L69 _public member_ `double Inclination = 0;` — radians    0 to PI (when conforming)
- L70 _public member_ `double Azimuth = 0;` — radians  -PI to PI (when conforming)

#### struct `FDisplayClusterLightCardEditorHelper::FAddLightCardArgs`  
`struct FAddLightCardArgs`  
_L238-252_
- L241 _public member_ `bool bShowLabels = false;` — `UE_DEPRECATED(5.3, "Use LabelConfiguration to configure label visibility.")`
- L243 _public member_ `float LabelScale = 1.f;` — `UE_DEPRECATED(5.3, "Use LabelConfiguration to configure label scale.")`
- L246 _public member_ `FDisplayClusterLabelConfiguration LabelConfiguration;` — Label configuration to use for the new light card
- L248 _public function_ `FAddLightCardArgs(): LabelConfiguration()`

#### struct `FDisplayClusterLightCardEditorHelper::FSpawnActorArgs`  
`struct FSpawnActorArgs`  
_L254-288_
- L257 _public member_ `ADisplayClusterRootActor* RootActor;` — [Required] The root actor managing the stage
- L260 _public member_ `TSubclassOf<AActor> ActorClass;` — [Required if Template is null] The class to spawn
- L263 _public member_ `const class UDisplayClusterStageActorTemplate* Template;` — [Required if ActorClass is null] The template to use
- L266 _public member_ `FName ActorName;` — The name to set for the actor and label
- L269 _public member_ `EDisplayClusterMeshProjectionType ProjectionMode;` — The projection mode the actor should be spawned in under
- L272 _public member_ `ULevel* Level;` — An override level for the actor, otherwise the RootActor level is used
- L275 _public member_ `FAddLightCardArgs AddLightCardArgs;` — Args if this is a light card being added to the root actor
- L278 _public member_ `bool bIsPreview;` — Notify this actor should be used as a preview (such as for drag & drop)
- L280 _public function_ `FSpawnActorArgs(): RootActor(nullptr), Template(nullptr), ActorName(NAME_None), ProjectionMode(), Level(nullptr), bIsPreview(false)`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterScenePreview/Public/DisplayClusterScenePreviewEnums.h` (Public)


#### enum `EDisplayClusterScenePreviewFlags`  
`enum class EDisplayClusterScenePreviewFlags : uint8`  
_L10-25_
- desc: Special flags that control the behavior of the renderer.
- L12 _public enumerator_ `None = 0`
- L15 _public enumerator_ `UseRootActorProxy = 1 << 0` — Use DCRA proxy for rendering.
- L18 _public enumerator_ `AutoUpdateStageActors = 1 << 1` — Automatically update the renderer with stage actors belonging to the RootActor in scene.
- L21 _public enumerator_ `ProxyFollowSceneRootActor = 1 << 2` — Move the RootActorProxy to the same position as RootActor in the scene to match the position of the StageActors in world space.
- L24 _public enumerator_ `ProxyTickPreviewRenderer= 1 << 3` — The proxy always calls the TickPreviewRenderer() function.

#### Free symbols / members of external scopes

- L26 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterScenePreviewFlags);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterScenePreview/Public/IDisplayClusterScenePreview.h` (Public)


#### class `IDisplayClusterScenePreview`  
`class IDisplayClusterScenePreview : public IModuleInterface`  
_L21-234_
- inherits: `IModuleInterface`
- desc: Interface for module containing tools for generation Display Cluster scene previews.
- L24 _public member_ `static constexpr const TCHAR* ModuleName = TEXT("Dis`
- L27 _public prototype_ `virtual ~IDisplayClusterScenePreview() = default;`
- L35 _public function_ `static inline IDisplayClusterScenePreview& Get()` — Singleton-like access to this module's interface. This is just for convenience! Beware of calling this during the shutdown phase, though. Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L45 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready. It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L53 _public prototype_ `virtual int32 CreateRenderer() = 0;` — Create a preview renderer. Returns an index used to refer to this renderer in future API calls.
- L60 _public prototype_ `virtual bool DestroyRenderer(int32 RendererId) = 0;` — Destroy a renderer, cleaning up all of its resources. @param RendererId The ID of the renderer as returned from CreateRenderer.
- L71 _public prototype_ `virtual bool SetRendererRootActorPath(int32 RendererId, const FString& ActorPath, const FDisplayClusterRootActorPropertyOverrides& InPropertyOverrides, const EDisplayClusterScenePreviewFlags PreviewFlags = EDisplayClusterScenePreviewFlags::None) = 0;` — Set the path of the ADisplayClusterRootActor actor for a renderer, which will be added to the preview scene and used to determine the render world. Whenever a render is performed with this renderer, it will try to find the actor at that path and use it as the root. @param RendererId The ID of the renderer as returned from CreateRenderer. @param ActorPath The path of the ADisplayClusterRootActor actor to preview. @param InPropertyOverrides optional overrides for root actor @param PreviewFlags Special flags that control the behavior of the renderer.
- L83 _public prototype_ `virtual bool SetRendererRootActor(int32 RendererId, ADisplayClusterRootActor* Actor, const FDisplayClusterRootActorPropertyOverrides& InPropertyOverrides, const EDisplayClusterScenePreviewFlags PreviewFlags = EDisplayClusterScenePreviewFlags::None) = 0;` — Set the root DisplayCluster actor for the renderer with the given ID, which will be added to the preview scene and used to determine the render world. Note that if the actor is destroyed (including by a recompile, reload, etc.), you will need to call this again to update the actor. This will also clear the path set by SetRendererRootActorPath. @param RendererId The ID of the renderer as returned from CreateRenderer. @param Actor The actor to preview. @param InPropertyOverrides optional overrides for root actor @param PreviewFlags Special flags that control the behavior of the renderer.
- L90 _public prototype_ `virtual ADisplayClusterRootActor* GetRendererRootActor(int32 RendererId) = 0;` — Get the root actor of a renderer. @param RendererId The ID of the renderer as returned from CreateRenderer.
- L97 _public prototype_ `virtual ADisplayClusterRootActor* GetRendererRootActorOrProxy(int32 RendererId) = 0;` — Get the root actor (or its proxy) of a renderer. @param RendererId The ID of the renderer as returned from CreateRenderer.
- L107 _public prototype_ `virtual bool GetActorsInRendererScene(int32 RendererId, bool bIncludeRoot, TArray<AActor*>& OutActors) = 0;` — Get a list of all actors that have been added to a renderer's scene. This includes any actors that the renderer automatically added to itself. @param RendererId The ID of the renderer as returned from CreateRenderer. @param bIncludeRoot If true, include the renderer's root actor. @param OutActors The array to fill with actors.
- L115 _public prototype_ `virtual bool AddActorToRenderer(int32 RendererId, AActor* Actor) = 0;` — Add an actor to the preview scene for a renderer. @param RendererId The ID of the renderer as returned from CreateRenderer. @param Actor The actor to add to the renderer's scene.
- L124 _public prototype_ `virtual bool AddActorToRenderer(int32 RendererId, AActor* Actor, const TFunctionRef<bool(const UPrimitiveComponent*)>& PrimitiveFilter) = 0;` — Add an actor to the preview scene for a renderer. @param RendererId The ID of the renderer as returned from CreateRenderer. @param Actor The actor to add to the renderer's scene. @param PrimitiveFilter A custom filter used to determine which of the actor's primitives are added to the renderer's scene.
- L132 _public prototype_ `virtual bool RemoveActorFromRenderer(int32 RendererId, AActor* Actor) = 0;` — Removes an actor from the preview scene for a renderer. @param RendererId The ID of the renderer as returned from CreateRenderer. @param Actor The actor to remove to the renderer's scene.
- L139 _public prototype_ `virtual bool ClearRendererScene(int32 RendererId) = 0;` — Clear the scene of a renderer. @param RendererId The ID of the renderer as returned from CreateRenderer.
- L148 _public prototype_ `virtual bool SetRendererActorSelectedDelegate(int32 RendererId, FDisplayClusterMeshProjectionRenderer::FSelection ActorSelectedDelegate) = 0;` — Set the ActorSelectedDelegate of a renderer. See FDisplayClusterMeshProjectionRenderer::ActorSelectedDelegate for more info. @param RendererId The ID of the renderer as returned from CreateRenderer. @param ActorSelectedDelegate The delegate to set on the renderer.
- L157 _public prototype_ `virtual bool SetRendererRenderSimpleElementsDelegate(int32 RendererId, FDisplayClusterMeshProjectionRenderer::FSimpleElementPass RenderSimpleElementsDelegate) = 0;` — Set the RenderSimpleElementsDelegate of a renderer. See FDisplayClusterMeshProjectionRenderer::RenderSimpleElementsDelegate for more info. @param RendererId The ID of the renderer as returned from CreateRenderer. @param RenderSimpleElementsDelegate The delegate to set on the renderer.
- L166 _public prototype_ `virtual bool Render(int32 RendererId, FDisplayClusterMeshProjectionRenderSettings& RenderSettings, FCanvas& Canvas) = 0;` — Immediately render a preview. @param RendererId The ID of the renderer as returned from CreateRenderer. @param RenderSettings Settings controlling how the scene will be rendered. @param Canvas The canvas to render to.
- L176 _public prototype_ `virtual bool RenderQueued(int32 RendererId, FDisplayClusterMeshProjectionRenderSettings& RenderSettings, const FIntPoint& Size, FRenderResultDelegate ResultDelegate) = 0;` — Queue a preview to be rendered in the future, automatically creating a canvas and render target. @param RendererId The ID of the renderer as returned from CreateRenderer. @param RenderSettings Settings controlling how the scene will be rendered. @param Size The size of the image to produce. Note that whenever this changes for a given renderer, the underlying RenderTarget will be resized, which has a performance cost. @param ResultDelegate The delegate to call when the render is complete. It will be passed a FRenderTarget containing the rendered preview, or null if the render failed.
- L186 _public prototype_ `virtual bool RenderQueued(int32 RendererId, FDisplayClusterMeshProjectionRenderSettings& RenderSettings, TWeakPtr<FCanvas> Canvas, FRenderResultDelegate ResultDelegate) = 0;` — Queue a preview to be rendered in the future using an existing canvas. The canvas must have a valid render target assigned. @param RendererId The ID of the renderer as returned from CreateRenderer. @param RenderSettings Settings controlling how the scene will be rendered. @param Canvas The canvas to draw to. If this is invalid when the render is ready to start, the render will be skipped. @param ResultDelegate The delegate to call when the render is complete. It will be passed a FRenderTarget containing the rendered preview, or null if the render failed.
- L191 _public prototype_ `virtual bool IsRealTimePreviewEnabled() const = 0;` — Check whether nDisplay preview textures are being updated in real time.
- L202 _public function_ `virtual bool SetRendererRootActorPath(int32 RendererId, const FString& ActorPath, bool bAutoUpdateLightcards = false)` — `UE_DEPRECATED(5.5, "This function has been deprecated. Use EDisplayClusterScenePreviewFlags.")` — Set the path of the ADisplayClusterRootActor actor for a renderer, which will be added to the preview scene and used to determine the render world. Whenever a render is performed with this renderer, it will try to find the actor at that path and use it as the root. @param RendererId The ID of the renderer as returned from CreateRenderer. @param ActorPath The path of the ADisplayClusterRootActor actor to preview. @param bAutoUpdateLightcards If true, the renderer scene will also be automatically populated with the actor's associated lightcards, including future changes to them.
- L217 _public function_ `virtual bool SetRendererRootActor(int32 RendererId, ADisplayClusterRootActor* Actor, bool bAutoUpdateLightcards = false)` — `UE_DEPRECATED(5.5, "This function has been deprecated.")` — Set the root DisplayCluster actor for the renderer with the given ID, which will be added to the preview scene and used to determine the render world. Note that if the actor is destroyed (including by a recompile, reload, etc.), you will need to call this again to update the actor. This will also clear the path set by SetRendererRootActorPath. @param RendererId The ID of the renderer as returned from CreateRenderer. @param Actor The actor to preview. @param bAutoUpdateLightcards If true, the renderer scene will also be automatically populated with the actor's associated lightcards, including future changes to them.
- L229 _public function_ `virtual bool SetRendererUsePostProcessTexture(int32 RendererId, bool bUsePostProcessTexture)` — `UE_DEPRECATED(5.5, "This function has been deprecated.")` — Set whether the renderer should use post-processed nDisplay preview textures. @param RendererId The ID of the renderer as returned from CreateRenderer. @param bUsePostProcessTexture Whether to use post-processed nDisplay preview texture for future renders.

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FRenderResultDelegate, FRenderTarget*);`
- L16 _prototype_ `DECLARE_DELEGATE_OneParam(FRenderResultDelegate, FRenderTarget*);`
