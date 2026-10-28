# Developer / MaterialBaking

- module root: `Source/Developer/MaterialBaking`
- headers: 11; symbols: 270
- symbol kinds: class=13, enum=2, enumerator=5, function=89, macro=3, member=92, prototype=54, struct=9, typedef=3
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, MainFrame, MeshDescription, PropertyEditor, RHI, RenderCore, Renderer, Slate, SlateCore, StaticMeshDescription, UnrealEd

### `Source/Developer/MaterialBaking/Private/ExportMaterialProxy.h` (Private)


#### struct `FExportMaterialCompiler`  
`struct FExportMaterialCompiler : public FProxyMaterialCompiler`  
_L29-211_
- inherits: `FProxyMaterialCompiler`
- L31 _public function_ `FExportMaterialCompiler(FMaterialCompiler* InCompiler) : FProxyMaterialCompiler(InCompiler)`
- L36 _public function_ `virtual EShaderFrequency GetCurrentShaderFrequency() const override` — gets value stored by SetMaterialProperty()
- L41 _public function_ `virtual FMaterialShadingModelField GetMaterialShadingModels() const override`
- L46 _public function_ `virtual FMaterialShadingModelField GetCompiledShadingModels() const override`
- L51 _public function_ `virtual int32 WorldPosition(EWorldPositionIncludedOffsets WorldPositionIncludedOffsets) override`
- L60 _public function_ `virtual int32 DistanceCullFade() override`
- L65 _public function_ `virtual int32 ParticleRelativeTime() override`
- L70 _public function_ `virtual int32 ParticleMotionBlurFade() override`
- L75 _public function_ `virtual int32 PixelNormalWS() override`
- L81 _public function_ `virtual int32 ParticleRandom() override`
- L86 _public function_ `virtual int32 ParticleDirection() override`
- L91 _public function_ `virtual int32 ParticleSpeed() override`
- L96 _public function_ `virtual int32 ParticleSize() override`
- L101 _public function_ `virtual int32 ParticleSpriteRotation() override`
- L106 _public function_ `virtual int32 CameraVector() override`
- L112 _public function_ `virtual int32 ReflectionAboutCustomWorldNormal(int32 CustomWorldNormal, int32 bNormalizeCustomWorldNormal) override`
- L132 _public function_ `virtual int32 PreSkinnedPosition() override`
- L137 _public function_ `virtual int32 PreSkinnedNormal() override`
- L142 _public function_ `virtual int32 VertexInterpolator(uint32 InterpolatorIndex) override`
- L147 _public function_ `virtual int32 ReflectionVector() override`
- L154 _public function_ `virtual int32 MaterialBakingWorldPosition() override`
- L162 _public function_ `virtual int32 AccessCollectionParameter(UMaterialParameterCollection* ParameterCollection, int32 ParameterIndex, int32 ComponentIndex) override`
- L210 _public function_ `virtual EMaterialCompilerType GetCompilerType() const override`

#### class `FExportMaterialProxy`  
`class FExportMaterialProxy : public FEditorMaterialResourceBase, public FMaterialRenderProxy`  
_L213-734_
- inherits: `FEditorMaterialResourceBase,FMaterialRenderProxy`
- L216 _public function_ `FExportMaterialProxy(UMaterialInterface* InMaterialInterface, EMaterialProperty InPropertyToCompile, const FString& InCustomOutputToCompile = TEXT(""), bool bInSynchronousCompilation = true, bool bTangentSpaceNormal = false, EBlendMode ProxyBlendMode = BLEND_Opaque, bool bAllowPixelDepthOffset = true) : FEditorMaterialResourceBase() , FMaterialRenderProxy(GetPathNameSafe(InMaterialInterface->GetMaterial())) , MaterialInterface(InMaterialInterface) , PropertyToCompile(InPropertyToCompile) , CustomOutputToCompile(InCustomOutputToCompile) , bSynchronousCompilation(bInSynchronousCompilation) , bTangentSpaceNormal(bTangentSpaceNormal) , ProxyBlendMode(ProxyBlendMode)`
- L284 _public function_ `virtual bool RequiresSynchronousCompilation() const override` — This override is required otherwise the shaders aren't ready for use when the surface is rendered resulting in a blank image
- L295 _public function_ `virtual bool ShouldCache(const FShaderType* ShaderType, const FVertexFactoryType* VertexFactoryType) const override` — Should the shader for this material with the given platform, shader type and vertex factory type combination be compiled @param ShaderType	Which shader is being compiled @param VertexFactory	Which vertex factory is being compiled (can be NULL) @return true if the shader should be compiled
- L303 _public function_ `virtual void GetStaticParameterSet(FStaticParameterSet& OutSet) const override`
- L313 _public function_ `virtual const FMaterial* GetMaterialNoFallback(ERHIFeatureLevel::Type InFeatureLevel) const override` — FMaterialRenderProxy interface.
- L322 _public function_ `virtual const FMaterialRenderProxy* GetFallback(ERHIFeatureLevel::Type InFeatureLevel) const override`
- L327 _public function_ `virtual bool GetParameterValue(EMaterialParameterType Type, const FHashedMaterialParameterInfo& ParameterInfo, FMaterialParameterValue& OutValue, const FMaterialRenderContext& Context) const override`
- L334 _public function_ `virtual int32 CompilePropertyAndSetMaterialProperty(EMaterialProperty Property, FMaterialCompiler* Compiler, EShaderFrequency OverrideShaderFrequency, bool bUsePreviousFrameTime) const override` — Entry point for compiling a specific material property.  This must call SetMaterialProperty.
- L343 _public function_ `int32 CompilePropertyAndSetMaterialPropertyWithoutCast(EMaterialProperty Property, FMaterialCompiler* Compiler) const` — helper for CompilePropertyAndSetMaterialProperty()
- L503 _public function_ `virtual EMaterialShaderMapUsage::Type GetShaderMapUsage() const override` — Gets the shader map usage of the material, which will be included in the DDC key. This mechanism allows derived material classes to create different DDC keys with the same base material.
- L505 _public function_ `virtual FString GetMaterialUsageDescription() const override`
- L509 _public function_ `virtual EMaterialDomain GetMaterialDomain() const override`
- L515 _public function_ `virtual bool IsTangentSpaceNormal() const override`
- L523 _public function_ `virtual bool IsTwoSided() const override`
- L531 _public function_ `virtual bool IsThinSurface() const override`
- L539 _public function_ `virtual bool IsDitheredLODTransition() const override`
- L547 _public function_ `virtual bool IsLightFunction() const override`
- L555 _public function_ `virtual bool IsDeferredDecal() const override`
- L562 _public function_ `virtual bool IsUIMaterial() const override`
- L566 _public function_ `virtual bool IsVolumetricPrimitive() const override`
- L570 _public function_ `virtual bool IsSpecialEngineMaterial() const override`
- L578 _public function_ `virtual bool IsWireframe() const override`
- L586 _public function_ `virtual bool IsMasked() const override`
- L587 _public function_ `virtual enum EBlendMode GetBlendMode() const override`
- L588 _public function_ `virtual enum ERefractionMode GetRefractionMode() const override`
- L589 _public function_ `virtual bool GetRootNodeOverridesDefaultRefraction()const override`
- L591 _public function_ `virtual FMaterialShadingModelField GetShadingModels() const override`
- L598 _public function_ `virtual bool IsShadingModelFromMaterialExpression() const override`
- L599 _public function_ `virtual float GetOpacityMaskClipValue() const override`
- L600 _public function_ `virtual bool GetCastDynamicShadowAsMasked() const override`
- L601 _public function_ `virtual FString GetFriendlyName() const override`
- L605 _public function_ `virtual bool IsPersistent() const override` — Should shaders compiled for this material be saved to disk?
- L607 _public function_ `virtual FGuid GetMaterialId() const override`
- L615 _public function_ `virtual UMaterialInterface* GetMaterialInterface() const override`
- L625 _public function_ `virtual bool IsUsedWithStaticLighting() const override`
- L630 _public function_ `virtual void GatherExpressionsForCustomInterpolators(TArray<UMaterialExpression*>& OutExpressions) const override`
- L638 _public function_ `virtual bool CheckInValidStateForCompilation(FMaterialCompiler* Compiler) const override`
- L644 _private function_ `int32 CompileInputForCustomOutput(FMaterialCompiler* Compiler, const FMaterialCustomOutputAttributeDefintion* CustomAttribute, int32 InputIndex, uint32 ForceCastFlags) const`
- L674 _private function_ `UMaterialExpressionCustomOutput* GetCustomOutputExpression(const FString& FunctionName) const`
- L688 _private function_ `int32 CompileNormalTransform(FMaterialCompiler* Compiler, int32 NormalInput) const`
- L694 _private function_ `static int32 CompileNormalEncoding(FMaterialCompiler* Compiler, int32 NormalInput)`
- L701 _private function_ `static int32 CompileRefractionEncoding(FMaterialCompiler* Compiler, int32 RefractionInput)`
- L709 _private function_ `static int32 CompileShadingModelEncoding(FMaterialCompiler* Compiler, int32 ShadingModelInput)`
- L719 _private member_ `UMaterialInterface* MaterialInterface;` — The material interface for this proxy
- L720 _private member_ `UMaterial* Material;`
- L722 _private member_ `EMaterialProperty PropertyToCompile;` — The property to compile for rendering the sample
- L724 _private member_ `EMaterialShaderMapUsage::Type Usage;` — Stores which exported attribute this proxy is compiling for.
- L726 _private member_ `FString CustomOutputToCompile;` — The name of the specific custom output to compile for rendering the sample. Only used if PropertyToCompile is MP_CustomOutput
- L727 _private member_ `bool bSynchronousCompilation;`
- L731 _public member_ `bool bTangentSpaceNormal;` — Whether to transform normals from world-space to tangent-space (does nothing if material already uses tangent-space normals)
- L733 _public member_ `EBlendMode ProxyBlendMode;` — The blend mode used when baking the proxy material

#### Free symbols / members of external scopes

- L620 _function_ `friend FArchive& operator<< (FArchive& Ar, FExportMaterialProxy& V)`

### `Source/Developer/MaterialBaking/Private/MaterialBakingModule.h` (Private)


#### class `FMaterialBakingModule`  
`class FMaterialBakingModule : public IMaterialBakingModule`  
_L26-109_
- inherits: `IMaterialBakingModule`
- L30 _public prototype_ `virtual void StartupModule();` — IModuleInterface overrides begin
- L31 _public prototype_ `virtual void ShutdownModule();`
- L35 _public prototype_ `virtual void BakeMaterials(const TArray<FMaterialData*>& MaterialSettings, const TArray<FMeshData*>& MeshSettings, TArray<FBakeOutput>& Output) override;` — Bakes out material properties according to MaterialSettings using MeshSettings and stores the output in Output
- L38 _public prototype_ `virtual void BakeMaterials(const TArray<FMaterialDataEx*>& MaterialSettings, const TArray<FMeshData*>& MeshSettings, TArray<FBakeOutputEx>& Output) override;` — Bakes out material properties according to extended MaterialSettings using MeshSettings and stores the output in Output
- L41 _public prototype_ `virtual void BakeMaterials(const TArray<FMaterialData*>& MaterialSettings, const TArray<FMeshData*>& MeshSettings, FBakeOutput& Output) override;` — Bakes out material properties according to MaterialSettings using MeshSettings and stores the output in Output
- L44 _public prototype_ `virtual void BakeMaterials(const TArray<FMaterialDataEx*>& MaterialSettings, const TArray<FMeshData*>& MeshSettings, FBakeOutputEx& Output) override;` — Bakes out material properties according to extended MaterialSettings using MeshSettings and stores the output in Output
- L47 _public prototype_ `virtual bool SetupMaterialBakeSettings(TArray<TWeakObjectPtr<UObject>>& OptionObjects, int32 NumLODs) override;` — Promps a slate window to allow the user to populate specific material baking settings used while baking out materials
- L50 _public prototype_ `virtual void SetEmissiveHDR(bool bHDR) override;` — Outputs true HDR version of emissive color
- L53 _public prototype_ `virtual void SetLinearBake(bool bCorrectLinear) override;` — Bakes all material properties to linear textures, except for non-emissive colors
- L56 _public prototype_ `virtual bool IsLinearBake(FMaterialPropertyEx Property) override;` — Returns whether a specific material property is baked to a linear texture or not
- L59 _public prototype_ `virtual uint32 GetCRC() const override;` — Obtain a CRC than can help trigger a rebake if code/global settings impacting the bake result change
- L65 _protected prototype_ `UTextureRenderTarget2D* CreateRenderTarget(FMaterialPropertyEx InProperty, const FIntPoint& InTargetSize, bool bInUsePooledRenderTargets, const FColor& BackgroundColor);` — Creates and adds or reuses a RenderTarget from the pool
- L68 _protected prototype_ `FExportMaterialProxy* CreateMaterialProxy(const FMaterialDataEx* MaterialSettings, const FMaterialPropertyEx& Property);` — Creates and adds (or reuses a ExportMaterialProxy from the pool if MaterialBaking.UseMaterialProxyCaching is set to 1)
- L71 _protected prototype_ `void CleanupMaterialProxies();` — Cleans up all cached material proxies in MaterialProxyPool
- L74 _protected prototype_ `void CleanupRenderTargets();` — Free up all pooled render targets
- L77 _protected prototype_ `void OnObjectModified(UObject* Object);` — Callback for modified objects which should be removed from MaterialProxyPool in that case
- L80 _protected prototype_ `void OnPreGarbageCollect();` — Callback used to clear material proxy cache on garbage collection
- L90 _private member_ `TArray<TStrongObjectPtr<UTextureRenderTarget2D>> RenderTargetPool;` — Pool of available render targets, cached for re-using on consecutive property rendering
- L93 _private typedef_ `typedef TWeakObjectPtr<UMaterialInterface> FMaterialPoolKey;` — Pool of cached material proxies to optimize material baking workflow, stays resident when MaterialBaking.UseMaterialProxyCaching is set to 1
- L94 _private typedef_ `typedef TPair<FMaterialPropertyEx, FExportMaterialProxy*> FMaterialPoolValue;`
- L95 _private typedef_ `typedef TMultiMap<FMaterialPoolKey, FMaterialPoolValue, FDefaultSetAllocator, TWeakObjectPtrMapKeyFuncs<FMaterialPoolKey, FMaterialPoolValue, true >> FMaterialPoolMap;`
- L96 _private member_ `FMaterialPoolMap MaterialProxyPool;`
- L99 _private member_ `TMap<FMaterialPropertyEx, EPixelFormat> PerPropertyFormat;` — Pixel formats to use for baking out specific material properties
- L102 _private member_ `TMap<FMaterialPropertyEx, EPropertyColorSpace> PerPropertyColorSpace;` — Whether or not to enforce gamma correction while baking out specific material properties
- L104 _private member_ `EPropertyColorSpace DefaultColorSpace;`
- L106 _private member_ `bool bEmissiveHDR;`
- L108 _private member_ `bool bIsBakingMaterials;`

#### enum `FMaterialBakingModule::EPropertyColorSpace`  
`enum EPropertyColorSpace`  
_L83-87_
- L85 _public enumerator_ `Linear`
- L86 _public enumerator_ `sRGB`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MATERIALBAKING_API`

### `Source/Developer/MaterialBaking/Private/MaterialOptionsCustomization.h` (Private)


#### class `FPropertyEntryCustomization`  
`class FPropertyEntryCustomization : public IPropertyTypeCustomization`  
_L10-24_
- inherits: `IPropertyTypeCustomization`
- desc: Property customization for Material Property entries
- L13 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L14 _public prototype_ `FPropertyEntryCustomization();`
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L17 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L19 _protected prototype_ `void UpdateRestrictions(const int32 EntryIndex);`
- L22 _protected member_ `TSharedPtr<FPropertyRestriction> PropertyRestriction;` — Property restriction instance used for limiting EMaterialProperty selection
- L23 _protected member_ `class UMaterialOptions* CurrentOptions;`

#### class `FMaterialOptionsCustomization`  
`class FMaterialOptionsCustomization : public IDetailCustomization`  
_L27-36_
- inherits: `IDetailCustomization`
- desc: Detail customization for UMaterialOptions
- L30 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(int32 InNumLODs);`
- L31 _public prototype_ `FMaterialOptionsCustomization(int32 InNumLODs);`
- L33 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L35 _protected member_ `int32 NumLODs;`

#### Free symbols / members of external scopes

- L38 _prototype_ `static void AddTextureSizeClamping(TSharedPtr<IPropertyHandle> TextureSizeProperty);`

### `Source/Developer/MaterialBaking/Private/MaterialOptionsWindow.h` (Private)


#### class `SMaterialOptions`  
`class SMaterialOptions : public SCompoundWidget`  
_L14-49_
- inherits: `SCompoundWidget`
- desc: Options window used to populate provided settings objects
- L17 _public function_ `SLATE_BEGIN_ARGS(SMaterialOptions) : _WidgetWindow(), _NumLODs(1)`
- L26 _public prototype_ `SMaterialOptions();`
- L27 _public prototype_ `void Construct(const FArguments& InArgs);`
- L30 _public function_ `virtual bool SupportsKeyboardFocus() const override` — Begin SCompoundWidget overrides
- L31 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L35 _public prototype_ `FReply OnConfirm();` — Callbacks used for Confirm and Cancel buttons
- L36 _public prototype_ `FReply OnCancel();`
- L39 _public prototype_ `bool WasUserCancelled();` — Returns whether or not the user cancelled the operation
- L42 _private member_ `TWeakPtr< SWindow > WidgetWindow;` — Owning window this widget is part of
- L44 _private member_ `bool bUserCancelled;` — Whether or not the cancel button was clicked by the user
- L46 _private member_ `TSharedPtr<class IDetailsView> DetailsView;` — Detailsview used to display SettingsObjects, and allowing user to change options
- L48 _private member_ `TSharedPtr<SButton> ConfirmButton;` — Shared ptr to Confirm button

### `Source/Developer/MaterialBaking/Private/MaterialRenderItem.h` (Private)


#### class `FMeshBuilderResources`  
`class FMeshBuilderResources : public FMeshBuilderOneFrameResources`  
_L20-48_
- inherits: `FMeshBuilderOneFrameResources`
- desc: This will hold onto the resources until not needed anymore. Move constructor makes it easier to send the destruction to another thread (render thread).
- L23 _public prototype_ `FMeshBuilderResources() = default;`
- L24 _public function_ `FMeshBuilderResources(FMeshBuilderResources&& Other)`
- L40 _public function_ `void Clear()`

#### class `FMeshMaterialRenderItem`  
`class FMeshMaterialRenderItem : public FCanvasBaseRenderItem`  
_L50-89_
- inherits: `FCanvasBaseRenderItem`
- L53 _public prototype_ `FMeshMaterialRenderItem(const FIntPoint& InTextureSize, const FMeshData* InMeshSettings, FDynamicMeshBufferAllocator* InDynamicMeshBufferAllocator = nullptr);`
- L54 _public prototype_ `virtual ~FMeshMaterialRenderItem();`
- L57 _public prototype_ `virtual bool Render_RenderThread(FCanvasRenderContext& RenderContext, FMeshPassProcessorRenderState& DrawRenderState, const FCanvas* Canvas) final;` — Begin FCanvasBaseRenderItem overrides
- L58 _public prototype_ `virtual bool Render_GameThread(const FCanvas* Canvas, FCanvasRenderThreadScope& RenderScope) final;`
- L62 _public prototype_ `void GenerateRenderData();` — Populate vertices and indices according to available mesh data and otherwise uses simple quad
- L65 _protected prototype_ `void QueueMaterial(FCanvasRenderContext& RenderContext, FMeshPassProcessorRenderState& DrawRenderState, const FSceneView* View);` — Enqueues the current material to be rendered
- L68 _protected prototype_ `void PopulateWithQuadData();` — Helper functions to populate render data using either mesh data or a simple quad
- L69 _protected prototype_ `void PopulateWithMeshData();`
- L72 _public member_ `const FMeshData* MeshSettings;` — Mesh settings to use while baking out the material
- L74 _public member_ `FIntPoint TextureSize;` — The texture size to use while baking
- L76 _public member_ `FMaterialRenderProxy* MaterialRenderProxy;` — Material render proxy (material/shader) to use while baking
- L78 _public member_ `TArray<FDynamicMeshVertex> Vertices;` — Vertex and index data representing the mesh or a quad
- L79 _public member_ `TArray<uint32> Indices;`
- L81 _public member_ `FLightCacheInterface* LCI;` — Light cache interface object to simulate lightmap behavior in case the material used prebaked ambient occlusion
- L83 _public member_ `FSceneViewFamily* ViewFamily;` — View family to use while baking
- L85 _private member_ `FMeshBatch MeshElement;`
- L86 _private member_ `bool bMeshElementDirty;`
- L87 _private member_ `FMeshBuilderResources MeshBuilderResources;`
- L88 _private member_ `FDynamicMeshBufferAllocator* DynamicMeshBufferAllocator;`

### `Source/Developer/MaterialBaking/Private/MaterialRenderItemData.h` (Private)


#### class `FMeshRenderInfo`  
`class FMeshRenderInfo : public FLightCacheInterface`  
_L11-30_
- inherits: `FLightCacheInterface`
- desc: Simple implementation for light cache to simulated lightmap behaviour (used for accessing prebaked ambient occlusion values)
- L14 _public function_ `FMeshRenderInfo(const FLightMap* InLightMap, const FShadowMap* InShadowMap, FUniformBufferRHIRef Buffer, const FLightmapResourceCluster* InLightmapResourceCluster) : FLightCacheInterface()`
- L26 _public function_ `virtual FLightInteraction GetInteraction(const class FLightSceneProxy* LightSceneProxy) const override`

### `Source/Developer/MaterialBaking/Public/IMaterialBakingModule.h` (Public)


#### class `IMaterialBakingModule`  
`class IMaterialBakingModule : public IModuleInterface`  
_L24-53_
- inherits: `IModuleInterface`
- L28 _public prototype_ `virtual void BakeMaterials(const TArray<FMaterialData*>& MaterialSettings, const TArray<FMeshData*>& MeshSettings, TArray<FBakeOutput>& Output) = 0;` — Bakes out material properties according to MaterialSettings using MeshSettings and stores the output in Output
- L31 _public prototype_ `virtual void BakeMaterials(const TArray<FMaterialDataEx*>& MaterialSettings, const TArray<FMeshData*>& MeshSettings, TArray<FBakeOutputEx>& Output) = 0;` — Bakes out material properties according to extended MaterialSettings using MeshSettings and stores the output in Output
- L34 _public prototype_ `virtual void BakeMaterials(const TArray<FMaterialData*>& MaterialSettings, const TArray<FMeshData*>& MeshSettings, FBakeOutput& Output) = 0;` — Bakes out material properties according to MaterialSettings using MeshSettings and stores the output in Output
- L37 _public prototype_ `virtual void BakeMaterials(const TArray<FMaterialDataEx*>& MaterialSettings, const TArray<FMeshData*>& MeshSettings, FBakeOutputEx& Output) = 0;` — Bakes out material properties according to extended MaterialSettings using MeshSettings and stores the output in Output
- L40 _public prototype_ `virtual bool SetupMaterialBakeSettings(TArray<TWeakObjectPtr<UObject>>& OptionObjects, int32 NumLODs) = 0;` — Promps a slate window to allow the user to populate specific material baking settings used while baking out materials
- L43 _public prototype_ `virtual void SetEmissiveHDR(bool bHDR) = 0;` — Outputs true HDR version of emissive color
- L46 _public prototype_ `virtual void SetLinearBake(bool bCorrectLinear) = 0;` — Bakes all material properties to linear textures, except for colors
- L49 _public prototype_ `virtual bool IsLinearBake(FMaterialPropertyEx Property) = 0;` — Returns whether a specific material property is baked to a linear texture or not
- L52 _public prototype_ `virtual uint32 GetCRC() const = 0;` — Obtain a CRC than can help trigger a rebake if code/global settings impacting the bake result change

### `Source/Developer/MaterialBaking/Public/MaterialBakingHelpers.h` (Public)


#### class `FMaterialBakingHelpers`  
`class FMaterialBakingHelpers`  
_L12-45_
- L23 _public prototype_ `static void PerformUVBorderSmear(TArray<FColor>& InOutPixels, int32 ImageWidth, int32 ImageHeight, int32 MaxIterations = -1, FColor BackgroundColor = FColor::Magenta);` — Applies a box blur to magenta pixels found in given texture represented by InOutPixels using non-background pixels, this creates a smear across the magenta/filled pixels. @param  InOutPixels     The image to apply the smear to @param  ImageWidth      The width of the image in pixels @param  ImageHeight     The height of the image in pixels @param  MaxIterations   The max distance in pixels to smear the edges of the texture. When set to -1 this value is the max of the width and height of the buffer @param  BackgroundColor The pixel color considered background in the image, and that can be smeared into
- L33 _public prototype_ `static void PerformShrinking(TArray<FColor>& InOutPixels, int32& OnOutImageWidth, int32& InOutImageHeight, FColor BackgroundColor = FColor::Magenta);` — Shrinks the array to a single pixel if the entire output is monochrome. Params will be adjusted accordingly when this occurs. It's useful to perform this before the border smear as a single non-magenta pixel value would have led to a monochrome image post-smear anyway, so the actual smearing process can be skipped. @param  InOutPixels     The image to shrink @param  ImageWidth      The width of the image in pixels @param  ImageHeight     The height of the image in pixels
- L44 _public prototype_ `static void PerformUVBorderSmearAndShrink(TArray<FColor>& InOutPixels, int32& InOutImageWidth, int32& InOutImageHeight, FColor BackgroundColor = FColor::Magenta);` — Applies a box blur to magenta pixels found in given texture represented by InOutPixels using non-background pixels, this creates a smear across the magenta/filled pixels. @param  InOutPixels      The image to apply the smear to @param  InOutImageWidth  The width of the image in pixels @param  InOutImageHeight The height of the image in pixels @param  BackgroundColor  The pixel color considered background in the image, and that can be smeared into @note   This version is allowed to shrink the array to a single pixel if the entire output is monochrome. Params will be adjusted accordingly when this occurs.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MATERIALBAKING_API`

### `Source/Developer/MaterialBaking/Public/MaterialBakingStructures.h` (Public)


#### struct `FMaterialData`  
`struct FMaterialData`  
_L18-40_
- desc: Structure containing information about the material which is being baked out
- L21 _public member_ `UMaterialInterface* Material = nullptr;` — Material to bake out
- L24 _public member_ `TMap<EMaterialProperty, FIntPoint> PropertySizes;` — Properties and the texture size at which they should be baked out
- L27 _public member_ `bool bPerformBorderSmear = true;` — Whether to smear borders after baking
- L30 _public member_ `bool bPerformShrinking = true;` — Whether to try to shrink the color values to a single non-magenta color value after baking
- L33 _public member_ `bool bTangentSpaceNormal = false;` — Whether to transform normals from world-space to tangent-space (does nothing if material already uses tangent-space normals)
- L36 _public member_ `EBlendMode BlendMode = BLEND_Opaque;` — Blend mode to use when baking, allowing for example detection of overlapping UVs
- L39 _public member_ `FColor BackgroundColor = FColor::Magenta;` — Background color used to initially fill the output texture and used for border smear

#### struct `FMaterialDataEx`  
`struct FMaterialDataEx`  
_L43-65_
- desc: Structure containing extended information about the material and properties which is being baked out
- L46 _public member_ `UMaterialInterface* Material = nullptr;` — Material to bake out
- L49 _public member_ `TMap<FMaterialPropertyEx, FIntPoint> PropertySizes;` — Extended properties and the texture size at which they should be baked out
- L52 _public member_ `bool bPerformBorderSmear = true;` — Whether to smear borders after baking
- L55 _public member_ `bool bPerformShrinking = true;` — Whether to try to shrink the color values to a single non-magenta color value after baking
- L58 _public member_ `bool bTangentSpaceNormal = false;` — Whether to transform normals from world-space to tangent-space (does nothing if material already uses tangent-space normals)
- L61 _public member_ `EBlendMode BlendMode = BLEND_Opaque;` — Blend mode to use when baking, allowing for example detection of overlapping UVs
- L64 _public member_ `FColor BackgroundColor = FColor::Magenta;` — Background color used to initially fill the output texture and used for border smear

#### struct `FPrimitiveData`  
`struct FPrimitiveData`  
_L68-116_
- desc: Structure containing primitive information (regarding a mesh or mesh component) that is accessible through material expressions
- L70 _public function_ `FPrimitiveData(const FBoxSphereBounds& LocalBounds = FBoxSphereBounds(ForceInitToZero)) : LocalToWorld(FMatrix::Identity) , ActorPosition(ForceInitToZero) , WorldBounds(LocalBounds) , LocalBounds(LocalBounds) , PreSkinnedLocalBounds(LocalBounds) , CustomPrimitiveData(nullptr)`
- L79 _public function_ `FPrimitiveData(const UStaticMesh* StaticMesh) : FPrimitiveData(StaticMesh->GetBounds())`
- L83 _public function_ `FPrimitiveData(const USkeletalMesh* SkeletalMesh) : FPrimitiveData(SkeletalMesh->GetBounds())`
- L87 _public function_ `FPrimitiveData(const UMeshComponent* MeshComponent) : LocalToWorld(MeshComponent->GetRenderMatrix()) , ActorPosition(MeshComponent->GetActorPositionForRenderer()) , WorldBounds(MeshComponent->Bounds) , LocalBounds(MeshComponent->GetLocalBounds()) , CustomPrimitiveData(&MeshComponent->GetCustomPrimitiveData())`
- L105 _public member_ `FMatrix LocalToWorld;` — The mesh component's local-to-world transform
- L107 _public member_ `FVector ActorPosition;` — The actor's location in world-space
- L109 _public member_ `FBoxSphereBounds WorldBounds;` — The mesh component's bounds in world-space
- L111 _public member_ `FBoxSphereBounds LocalBounds;` — The mesh component's bounds in local-space
- L113 _public member_ `FBoxSphereBounds PreSkinnedLocalBounds;` — The mesh component's pre-skinning bounds in local-space
- L115 _public member_ `const FCustomPrimitiveData* CustomPrimitiveData;` — The mesh component's custom primitive data

#### struct `FMeshData`  
`struct FMeshData`  
_L118-155_
- L121 _public member_ `const FMeshDescription* MeshDescription = nullptr;` — Ptr to raw mesh data to use for baking out the material data, if nullptr a standard quad is used
- L124 _public member_ `const UStaticMesh* Mesh = nullptr;` — Ptr to original static mesh this mesh data came from
- L127 _public member_ `bool bMirrored = false;` — Transform determinant used to detect mirroring
- L130 _public member_ `uint32 VertexColorHash = 0;` — A hash of the vertex color buffer for the rawmesh
- L133 _public member_ `TArray<int32> MaterialIndices;` — Material indices to test the Raw Mesh data against, ensuring we only bake out triangles which use the currently baked out material
- L136 _public member_ `TArray<FVector2D> CustomTextureCoordinates;` — Set of custom texture coordinates which ensure that the material is baked out with unique/non-overlapping positions
- L139 _public member_ `FBox2D TextureCoordinateBox = FBox2D(FVector2D(0.0f, 0.0f), FVector2D(1.0f, 1.0f));` — Box which's space contains the UV coordinates used to bake out the material
- L142 _public member_ `int32 TextureCoordinateIndex = 0;` — Specific texture coordinate index to use as texture coordinates to bake out the material (is overruled if CustomTextureCoordinates contains any data)
- L145 _public member_ `int32 LightMapIndex = 0;` — Light map index used to retrieve the light-map UVs from RawMesh
- L148 _public member_ `FLightMapRef LightMap = nullptr;` — Reference to the lightmap texture part of the level in the currently being baked out mesh instance data is resident
- L151 _public member_ `const FLightmapResourceCluster* LightmapResourceCluster = nullptr;` — Pointer to the LightmapResourceCluster to be passed on the the LightCacheInterface when baking
- L154 _public member_ `TOptional<FPrimitiveData> PrimitiveData;` — Optional primitive data that is accessible through material expressions

#### struct `FBakeOutput`  
`struct FBakeOutput`  
_L158-174_
- desc: Structure containing data being processed while baking out materials
- L161 _public member_ `TMap<EMaterialProperty, TArray<FColor>> PropertyData;` — Contains the resulting texture data for baking out a material's property
- L164 _public member_ `TMap<EMaterialProperty, FIntPoint> PropertySizes;` — Contains the resulting texture size for baking out a material's property
- L167 _public member_ `TMap<EMaterialProperty, TArray<FFloat16Color>> HDRPropertyData;` — Contains the resulting HDR texture data for baking out a material's property, may be empty
- L170 _public member_ `TMap<EMaterialProperty, bool> PropertyIsLinearColor;` — Wether or not a baked texture data is using a linear color or sRGB encoding.
- L173 _public member_ `float EmissiveScale = 1.0f;` — Scale used to allow having wide ranges of emissive values in the source materials, the final proxy material will use this value to scale the emissive texture's pixel values

#### struct `FBakeOutputEx`  
`struct FBakeOutputEx`  
_L177-193_
- desc: Structure containing extended data being processed while baking out materials
- L180 _public member_ `TMap<FMaterialPropertyEx, TArray<FColor>> PropertyData;` — Contains the resulting texture data for baking out a extened material's property
- L183 _public member_ `TMap<FMaterialPropertyEx, FIntPoint> PropertySizes;` — Contains the resulting texture size for baking out a extened material's property
- L186 _public member_ `TMap<FMaterialPropertyEx, TArray<FFloat16Color>> HDRPropertyData;` — Contains the resulting HDR texture data for baking out a material's property, may be empty
- L189 _public member_ `TMap<FMaterialPropertyEx, bool> PropertyIsLinearColor;` — Wether or not a baked texture data is using a linear color or sRGB encoding.
- L192 _public member_ `float EmissiveScale = 1.0f;` — Scale used to allow having wide ranges of emissive values in the source materials, the final proxy material will use this value to scale the emissive texture's pixel values

### `Source/Developer/MaterialBaking/Public/MaterialOptions.h` (Public)


#### enum `EMaterialBakeMethod`  
`enum class EMaterialBakeMethod : uint8`  
_L12-17_
- reflection: `UENUM()`
- desc: Enum to define different types of baking materials
- L14 _public enumerator_ `IndividualMaterial UMETA(DisplayName = "Bake out Materials Individually")`
- L15 _public enumerator_ `AtlasMaterial UMETA(DisplayName = "Combine Materials into Atlassed Material")`
- L16 _public enumerator_ `BinnedMaterial UMETA(DisplayName = "Combine Materials into Binned Material")`

#### struct `FPropertyEntry`  
`struct FPropertyEntry`  
_L21-60_
- reflection: `USTRUCT(Blueprintable)`
- desc: Structure to represent a single property the user wants to bake out for a given set of materials
- L25 _public function_ `FPropertyEntry() : Property(MP_EmissiveColor) , bUseCustomSize(false) , CustomSize(0, 0) , bUseConstantValue(false) , ConstantValue(0.0f)`
- L33 _public function_ `FPropertyEntry(EMaterialProperty InProperty) : Property(InProperty) , bUseCustomSize(false) , CustomSize(0, 0) , bUseConstantValue(false) , ConstantValue(0.0f)`
- L43 _public member_ `TEnumAsByte<EMaterialProperty> Property;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property, meta = (ExposeOnSpawn))` — Property which should be baked out
- L47 _public member_ `bool bUseCustomSize;` — `UPROPERTY(EditAnywhere, Category = Property, BlueprintReadWrite, meta = (InlineEditConditionToggle, ExposeOnSpawn))` — Whether or not to use the value of custom size for the output texture
- L51 _public member_ `FIntPoint CustomSize;` — `UPROPERTY(EditAnywhere, Category = Property, BlueprintReadWrite, meta = (EditCondition = bUseCustomSize, ExposeOnSpawn, ClampMin = "1", UIMin = "1"))` — Defines the size of the output textures for the baked out material properties
- L55 _public member_ `bool bUseConstantValue;` — `UPROPERTY(EditAnywhere, Category = Property, BlueprintReadWrite, meta = (InlineEditConditionToggle, ExposeOnSpawn))` — Wheter or not to use Constant Value as the final 'baked out' value for the this property
- L59 _public member_ `float ConstantValue;` — `UPROPERTY(EditAnywhere, Category = Property, BlueprintReadWrite, meta = (EditCondition = bUseConstantValue, ExposeOnSpawn))` — Defines the value representing this property in the final proxy material

#### class `UMaterialOptions`  
`class UMaterialOptions : public UObject`  
_L64-100_
- reflection: `UCLASS(MinimalAPI, config = Editor, Blueprintable)`
- inherits: `UObject`
- desc: Options object to define what and how a material should be baked out
- L70 _public function_ `UMaterialOptions() : TextureSize(128, 128), bUseMeshData(false), bUseSpecificUVIndex(false), TextureCoordinateIndex(0)`
- L79 _public member_ `TArray<FPropertyEntry> Properties;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category= MaterialBakeSettings, meta = (ExposeOnSpawn))` — Properties which are supposed to be baked out for the material(s)
- L83 _public member_ `FIntPoint TextureSize;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = MaterialBakeSettings, meta = (ExposeOnSpawn, ClampMin = "1", UIMin = "1"))` — Size of the final texture(s) containing the baked out property data
- L87 _public member_ `TArray<int32> LODIndices;` — `UPROPERTY(BlueprintReadWrite, Category = MeshSettings, meta = (ExposeOnSpawn))` — LOD indices for which the materials should be baked out
- L91 _public member_ `bool bUseMeshData;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = MeshSettings, meta = (ExposeOnSpawn))` — Determines whether to not allow usage of the source mesh data while baking out material properties
- L95 _public member_ `bool bUseSpecificUVIndex;` — `UPROPERTY(EditAnywhere, Category = MeshSettings, BlueprintReadWrite, meta = (InlineEditConditionToggle, EditCondition = bUseMeshData, ExposeOnSpawn))` — Flag whether or not the value of TextureCoordinateIndex should be used while baking out material properties
- L99 _public member_ `int32 TextureCoordinateIndex;` — `UPROPERTY(EditAnywhere, Category = MeshSettings, BlueprintReadWrite, meta = (EditCondition = bUseSpecificUVIndex, ExposeOnSpawn))` — Specific texture coordinate which should be used to while baking out material properties as the positions stream

#### class `UAssetBakeOptions`  
`class UAssetBakeOptions : public UObject`  
_L104-112_
- reflection: `UCLASS(MinimalAPI, Config = Editor, Blueprintable)`
- inherits: `UObject`
- desc: Asset bake options object
- L109 _public function_ `UAssetBakeOptions()`

#### class `UMaterialMergeOptions`  
`class UMaterialMergeOptions: public UObject`  
_L116-132_
- reflection: `UCLASS(MinimalAPI, Config = Editor, Blueprintable)`
- inherits: `UObject`
- desc: Material merge options object
- L121 _public function_ `UMaterialMergeOptions() : Method(EMaterialBakeMethod::IndividualMaterial), BlendMode(EBlendMode::BLEND_Opaque)`
- L127 _public member_ `EMaterialBakeMethod Method;` — `UPROPERTY(/*EditAnywhere, BlueprintReadWrite, config, Category = MeshSettings, meta = (ExposeOnSpawn)*/)` — Method used to bake out the materials, hidden for now
- L131 _public member_ `TEnumAsByte<EBlendMode> BlendMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = OutputMaterialSettings, meta = (ExposeOnSpawn))` — Blend mode for the final proxy material(s)

### `Source/Developer/MaterialBaking/Public/MaterialPropertyEx.h` (Public)


#### struct `FMaterialPropertyEx`  
`struct FMaterialPropertyEx`  
_L15-65_
- desc: Structure extending EMaterialProperty to allow detailed information about custom output
- L17 _public function_ `FMaterialPropertyEx(EMaterialProperty Type = MP_MAX, const FName& CustomOutput = NAME_None) : Type(Type) , CustomOutput(CustomOutput)`
- L22 _public function_ `FMaterialPropertyEx(const FName& CustomOutput) : Type(MP_CustomOutput) , CustomOutput(CustomOutput)`
- L27 _public function_ `FMaterialPropertyEx(const TCHAR* CustomOutput) : Type(MP_CustomOutput) , CustomOutput(CustomOutput)`
- L32 _public function_ `FORCEINLINE bool IsCustomOutput() const`
- L37 _public function_ `FORCEINLINE bool operator ==(const FMaterialPropertyEx& Other) const`
- L42 _public function_ `FORCEINLINE bool operator !=(const FMaterialPropertyEx& Other) const`
- L52 _public prototype_ `FString ToString() const;`
- L55 _public member_ `EMaterialProperty Type;` — The material property
- L58 _public member_ `FName CustomOutput;` — The name of a specific custom output. Only used if property is MP_CustomOutput
- L61 _public member_ `static const FMaterialPropertyEx ClearCoatBottomNormal;` — The identifier for custom output Clear Coat Bottom Normal (used by shading model Clear Coat)
- L64 _public member_ `static const FMaterialPropertyEx TransmittanceColor;` — The identifier for custom output Transmittance Color (used by shading model Thin Translucent)

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MATERIALBAKING_API`
- L47 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FMaterialPropertyEx& Other)`
