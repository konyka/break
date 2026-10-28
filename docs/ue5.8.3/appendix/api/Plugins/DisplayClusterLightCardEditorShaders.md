# Plugins / DisplayClusterLightCardEditorShaders

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditorShaders`
- headers: 3; symbols: 82
- symbol kinds: class=5, delegate=3, enum=2, enumerator=5, function=5, member=22, prototype=37, struct=3
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Projects, RHI, RenderCore, Renderer

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditorShaders/Private/DisplayClusterLightCardEditorShadersModule.h` (Private)


#### class `FDisplayClusterLightCardEditorShadersModule`  
`class FDisplayClusterLightCardEditorShadersModule : public IDisplayClusterLightCardEditorShaders`  
_L11-18_
- inherits: `IDisplayClusterLightCardEditorShaders`
- desc: Display Cluster editor module
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditorShaders/Public/DisplayClusterMeshProjectionRenderer.h` (Public)


#### enum `EDisplayClusterMeshProjectionType`  
`enum EDisplayClusterMeshProjectionType`  
_L21-31_
- desc: Indicates which kind of projection is used by the renderer
- L24 _public enumerator_ `Linear` — Default linear projection
- L27 _public enumerator_ `Azimuthal` — Non-linear spherical projection based on the azimuthal equidistant map projection
- L30 _public enumerator_ `UV` — Projection that positions vertices based on their UV coordinates

#### enum `EDisplayClusterMeshProjectionOutput`  
`enum EDisplayClusterMeshProjectionOutput`  
_L34-41_
- desc: Indicates the quantity that is output to the canvas by the renderer
- L37 _public enumerator_ `Color` — Outputs the emissive color of the rendered primitives
- L40 _public enumerator_ `Normals` — Outputs the normals and depth of the rendered primitives

#### class `FDisplayClusterMeshProjectionPrimitiveFilter`  
`class FDisplayClusterMeshProjectionPrimitiveFilter`  
_L44-61_
- desc: A filter that allows specific primitive components to be filtered from a render pass
- L47 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FPrimitiveFilter, const UPrimitiveComponent*);`
- L51 _public member_ `FPrimitiveFilter ShouldRenderPrimitiveDelegate;` — A delegate that returns true if the primitive component should be included in the render pass
- L54 _public member_ `FPrimitiveFilter ShouldApplyProjectionDelegate;` — A delegate that returns true if the primitive component should be rendered using the render pass's projection type
- L57 _public prototype_ `bool ShouldRenderPrimitive(const UPrimitiveComponent* InPrimitiveComponent) const;` — Gets whether a primitive component should be filtered out of the render pass or not
- L60 _public prototype_ `bool ShouldApplyProjection(const UPrimitiveComponent* InPrimitiveComponent) const;` — Gets whether a primitive component should be rendered using the current projection type or not

#### struct `FDisplayClusterMeshProjectionTypeSettings`  
`struct FDisplayClusterMeshProjectionTypeSettings`  
_L64-77_
- desc: Settings for specific mesh projection types
- L67 _public member_ `uint32 UVProjectionIndex = 0;` — The index of the UV to use when performing a UV projection
- L70 _public member_ `float UVProjectionPlaneSize = 100.0f;` — The size of the plane the UVs are projected to, in view space
- L73 _public member_ `float UVProjectionPlaneDistance = 100.0f;` — The distance from the view point of the plane the UVs are projected to, in view space
- L76 _public member_ `FVector UVProjectionPlaneOffset = FVector::ZeroVector;` — A translation offset for the UV projection plane

#### struct `FDisplayClusterMeshProjectionRenderSettings`  
`struct FDisplayClusterMeshProjectionRenderSettings`  
_L80-108_
- desc: Settings for producing a single render.
- L83 _public member_ `FSceneViewInitOptions ViewInitOptions;` — Camera setup options for the render.
- L89 _public member_ `FEngineShowFlags EngineShowFlags = FEngineShowFlags(ESFIM_Editor);` — Flags controlling renderer features to enable/disable for this preview. Only flags supported by FDisplayClusterMeshProjectionRenderer will have an impact on the render output.
- L92 _public member_ `EDisplayClusterMeshProjectionType ProjectionType = EDisplayClusterMeshProjectionType::Azimuthal;` — Type of projection to use for the renderer.
- L95 _public member_ `FDisplayClusterMeshProjectionTypeSettings ProjectionTypeSettings;` — Settings used by the projection type when rendering
- L98 _public member_ `EDisplayClusterMeshProjectionOutput RenderType = EDisplayClusterMeshProjectionOutput::Color;` — The output type to use for the renderer.
- L101 _public member_ `FMatrix44f NormalCorrectionMatrix = FMatrix44f::Identity;` — A matrix used to rotate the normals in order to account for the root actor's rotation.
- L107 _public member_ `FDisplayClusterMeshProjectionPrimitiveFilter PrimitiveFilter;` — Optional filter to prevent specific primitives from being rendered. This only applies when RenderType is ERenderType::Normals.

#### class `FDisplayClusterMeshProjectionTransform`  
`class FDisplayClusterMeshProjectionTransform`  
_L111-131_
- desc: A transform that can be passed around to project and unprojection positions for a specific projection type
- L114 _public function_ `FDisplayClusterMeshProjectionTransform() : FDisplayClusterMeshProjectionTransform(EDisplayClusterMeshProjectionType::Linear, FMatrix::Identity)`
- L118 _public function_ `FDisplayClusterMeshProjectionTransform(EDisplayClusterMeshProjectionType InProjection, const FMatrix& InViewMatrix) : Projection(InProjection) , ViewMatrix(InViewMatrix) , InvViewMatrix(InViewMatrix.Inverse())`
- L124 _public prototype_ `FVector ProjectPosition(const FVector& WorldPosition) const;`
- L125 _public prototype_ `FVector UnprojectPosition(const FVector& ProjectedPosition) const;`
- L128 _private member_ `EDisplayClusterMeshProjectionType Projection;`
- L129 _private member_ `FMatrix ViewMatrix;`
- L130 _private member_ `FMatrix InvViewMatrix;`

#### class `FDisplayClusterMeshProjectionRenderer`  
`class FDisplayClusterMeshProjectionRenderer`  
_L134-309_
- desc: A renderer that projects meshes to screen space using non-linear projection methods
- L138 _public prototype_ `~FDisplayClusterMeshProjectionRenderer();` — Clean up any references to the renderer.
- L141 _public prototype_ `static FVector ProjectViewPosition(const FVector& ViewPosition, EDisplayClusterMeshProjectionType ProjectionType);` — Projects a position in view coordinates into the projected view space of the specified projection type
- L144 _public prototype_ `static FVector UnprojectViewPosition(const FVector& ProjectedViewPosition, EDisplayClusterMeshProjectionType ProjectionType);` — Projects a position in the projected view space of the specified projection type to ordinary view coordinates
- L147 _public prototype_ `void AddActor(AActor* Actor);` — Adds an actor's primitive components to the list of primitives to render
- L150 _public prototype_ `void AddActor(AActor* Actor, const TFunctionRef<bool(const UPrimitiveComponent*)>& PrimitiveFilter);` — Adds an actor's primitive components to the list of primitives to render, filtering which primitive components get rendered using the specified callback
- L153 _public prototype_ `void RemoveActor(AActor* Actor);` — Removes an actor's primitive components from the list of primitives to render
- L156 _public prototype_ `void ClearScene();` — Clears the list of primitives to render
- L161 _public prototype_ `void Render(FCanvas* Canvas, FSceneInterface* Scene, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings);` — Renders its list of primitive components to the specified canvas using the desired projection type. Can be called from either the game thread or the rendering thread.
- L167 _public prototype_ `void RenderScenes(FCanvas* Canvas, const TArray<FSceneInterface*>& Scenes, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings);` — Renders its list of primitive components to the specified canvas using the desired projection type. Can be called from either the game thread or the rendering thread. Render scene by scene
- L171 _private prototype_ `void RenderColorOutput(FRDGBuilder& GraphBuilder, const FSceneView* View, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings, FRenderTargetBinding& OutputRenderTargetBinding);` — Constructs the necessary render passes for the default output of the rendered primitives
- L177 _private prototype_ `void RenderColorOutputs(FRDGBuilder& GraphBuilder, const TArray<const FSceneView*>& Views, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings, FRenderTargetBinding& OutputRenderTargetBinding);` — Constructs the necessary render passes for the default output of the rendered primitives
- L183 _private prototype_ `void RenderHitProxyOutput(FRDGBuilder& GraphBuilder, const FSceneView* View, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings, FRenderTargetBinding& OutputRenderTargetBinding, FHitProxyConsumer* HitProxyConsumer);` — Constructs the necessary render passes for the hit proxy output of the rendered primitives
- L190 _private prototype_ `void RenderNormalsOutput(FRDGBuilder& GraphBuilder, const FSceneView* View, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings, FRenderTargetBinding& OutputRenderTargetBinding);` — Constructs the necessary render passes for the normals/depth output of the rendered primitives
- L196 _private prototype_ `void AddBaseRenderPass(FRDGBuilder& GraphBuilder, const FSceneView* View, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings, FRenderTargetBinding& OutputRenderTargetBinding, FDepthStencilBinding& OutputDepthStencilBinding);` — Adds a pass to perform the base render for the mesh projection.
- L203 _private prototype_ `void AddTranslucencyRenderPass(FRDGBuilder& GraphBuilder, const FSceneView* View, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings, FRenderTargetBinding& OutputRenderTargetBinding, FDepthStencilBinding& OutputDepthStencilBinding);` — Adds a pass to perform the translucency render for the mesh projection.
- L210 _private prototype_ `void AddHitProxyRenderPass(FRDGBuilder& GraphBuilder, const FSceneView* View, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings, FRenderTargetBinding& OutputRenderTargetBinding, FDepthStencilBinding& OutputDepthStencilBinding);` — Adds a pass to perform the hit proxy render for the mesh projection
- L217 _private prototype_ `void AddNormalsRenderPass(FRDGBuilder& GraphBuilder, const FSceneView* View, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings, FRenderTargetBinding& OutputRenderTargetBinding, FDepthStencilBinding& OutputDepthStencilBinding);` — Adds a pass to perform a render of the primitives' normals for the mesh projection
- L225 _private prototype_ `void AddNormalsFilterPass(FRDGBuilder& GraphBuilder, const FSceneView* View, FRenderTargetBinding& OutputRenderTargetBinding, FRDGTexture* SceneColor, FRDGTexture* SceneDepth, const FMatrix44f& NormalCorrectionMatrix);` — Adds a pass to filter the output normal map for the mesh projection, dilating and blurring it to obtain a continuous normal map from primitives into empty space
- L234 _private prototype_ `void AddSelectionDepthRenderPass(FRDGBuilder& GraphBuilder, const FSceneView* View, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings, FDepthStencilBinding& OutputDepthStencilBinding);` — Adds a pass to perform the depth render for any selected primitives for the mesh projection
- L240 _private prototype_ `void AddSelectionOutlineScreenPass(FRDGBuilder& GraphBuilder, const FSceneView* View, FRenderTargetBinding& OutputRenderTargetBinding, FRDGTexture* SceneColor, FRDGTexture* SceneDepth, FRDGTexture* SelectionDepth);` — Adds a pass to perform the post process selection outline for the mesh projection
- L249 _private prototype_ `void AddSimpleElementPass(FRDGBuilder& GraphBuilder, const FSceneView* View, FRenderTargetBinding& OutputRenderTargetBinding, FSimpleElementCollector& ElementCollector);` — Adds a pass that renders any elements added to the PDI through the renderer's RenderSimpleElements callback
- L256 _private prototype_ `template<EDisplayClusterMeshProjectionType ProjectionType> void RenderPrimitives_RenderThread(const FSceneView* View, FRHICommandList& RHICmdList, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings, bool bTranslucencyPass);` — Renders the list of primitive components using the appropriate mesh pass processor given by the template parameter
- L263 _private prototype_ `template<EDisplayClusterMeshProjectionType ProjectionType> void RenderHitProxies_RenderThread(const FSceneView* View, FRHICommandList& RHICmdList, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings);` — Renders the hit proxies of the list of primitive components using the appropriate mesh pass processor given by the template parameter
- L269 _private prototype_ `template<EDisplayClusterMeshProjectionType ProjectionType> void RenderNormals_RenderThread(const FSceneView* View, FRHICommandList& RHICmdList, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings);` — Renders the normals of the list of primitive components using the appropriate mesh pass processor given by the template parameter
- L276 _private prototype_ `template<EDisplayClusterMeshProjectionType ProjectionType> void RenderSelection_RenderThread(const FSceneView* View, FRHICommandList& RHICmdList, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings);` — Renders the list of primitive components using the appropriate mesh pass processor given by the template parameter
- L283 _private prototype_ `bool IsPrimitiveComponentSelected(const UPrimitiveComponent* InPrimitiveComponent);` — Callback used to determine if a primitive component should be rendered with a selection outline
- L293 _private prototype_ `void GetSceneProxies(TArray<FSceneProxyElement>& OutSceneProxyElements, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings, const TFunctionRef<bool(const UPrimitiveComponent*)> PrimitiveFilter = [](const UPrimitiveComponent*) { return true; });` — Collects all valid scene proxies to be rendered from the scene's primitive componets
- L295 _private function_ `void GetSceneProxies(TArray<FSceneProxyElement>& OutSceneProxyElements, const FDisplayClusterMeshProjectionRenderSettings& RenderSettings, const TFunctionRef<bool(const UPrimitiveComponent*)> PrimitiveFilter = [](const UPrimitiveComponent*) { return true; });` — Collects all valid scene proxies to be rendered from the scene's primitive componets
- L299 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FSelection, const AActor*);` — Delegate to determine if an actor should be rendered as selected
- L300 _public member_ `FSelection ActorSelectedDelegate;`
- L303 _public prototype_ `DECLARE_DELEGATE_TwoParams(FSimpleElementPass, const FSceneView*, FPrimitiveDrawInterface*);` — Delegate raised during a render pass allowing simple elements ro be rendered to the viewport after meshes are projected to it
- L304 _public member_ `FSimpleElementPass RenderSimpleElementsDelegate;`
- L308 _private member_ `TArray<TWeakObjectPtr<UPrimitiveComponent>> PrimitiveComponents;` — The list of primitive components to render

#### struct `FDisplayClusterMeshProjectionRenderer::FSceneProxyElement`  
`struct FSceneProxyElement`  
_L286-290_
- desc: Data struct that contains the scene proxy and the render configuration needed to render the scene's primitive components
- L288 _public member_ `FPrimitiveSceneProxy* PrimitiveSceneProxy;`
- L289 _public member_ `bool bApplyProjection;`

#### Free symbols / members of external scopes

- L47 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FPrimitiveFilter, const UPrimitiveComponent*);`
- L299 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FSelection, const AActor*);` — Delegate to determine if an actor should be rendered as selected
- L303 _delegate_ `DECLARE_DELEGATE_TwoParams(FSimpleElementPass, const FSceneView*, FPrimitiveDrawInterface*);` — Delegate raised during a render pass allowing simple elements ro be rendered to the viewport after meshes are projected to it

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditorShaders/Public/IDisplayClusterLightCardEditorShaders.h` (Public)


#### class `IDisplayClusterLightCardEditorShaders`  
`class IDisplayClusterLightCardEditorShaders : public IModuleInterface`  
_L12-40_
- inherits: `IModuleInterface`
- desc: Display Cluster Light Card Editor Shaders module interface
- L15 _public member_ `static constexpr const TCHAR* ModuleName = TEXT("Dis`
- L18 _public prototype_ `virtual ~IDisplayClusterLightCardEditorShaders() = default;`
- L26 _public function_ `static inline IDisplayClusterLightCardEditorShaders& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L36 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
