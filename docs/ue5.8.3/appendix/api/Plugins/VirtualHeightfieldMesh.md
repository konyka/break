# Plugins / VirtualHeightfieldMesh

- module root: `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh`
- headers: 10; symbols: 155
- symbol kinds: class=8, function=19, macro=2, member=65, namespace=3, prototype=55, struct=2, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Projects, RHI, RenderCore, Renderer

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh/Private/HeightfieldMinMaxTextureMaterialExpression.h` (Private)


#### class `UMaterialExpressionHeightfieldMinMaxTexture`  
`class UMaterialExpressionHeightfieldMinMaxTexture : public UMaterialExpression`  
_L14-41_
- reflection: `UCLASS(collapsecategories, hidecategories=Object, MinimalAPI)`
- inherits: `UMaterialExpression`
- desc: Node which outputs a texture object contained in a UHeightfieldMinMaxTexture.
- L19 _private member_ `TObjectPtr<UHeightfieldMinMaxTexture> MinMaxTexture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MaterialExpressionTexture)`
- L22 _private member_ `TEnumAsByte<EMaterialSamplerType> SamplerType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MaterialExpressionTexture)`
- L27 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L33 _protected prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L34 _protected prototype_ `virtual int32 CompilePreview(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L35 _protected prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L36 _protected prototype_ `virtual EMaterialValueType GetOutputValueType(int32 OutputIndex) override;`
- L37 _protected function_ `virtual bool CanReferenceTexture() const override`
- L39 _protected prototype_ `virtual UObject* GetReferencedTexture() const override;`

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh/Private/HeightfieldMinMaxTextureNotify.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace VirtualHeightfieldMesh`
- L15 _prototype_ `void NotifyComponents(UHeightfieldMinMaxTexture const* MinMaxTexture);` (scope `VirtualHeightfieldMesh`) — Find any UVirtualHeightfieldMeshComponent that reference this UHeightfieldMinMaxTexture and mark them dirty. We need to do this after editing the UHeightfieldMinMaxTexture settings.

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh/Private/VirtualHeightfieldMeshEnable.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace VirtualHeightfieldMesh`
- L10 _prototype_ `bool IsEnabled(FStaticFeatureLevel InFeatureLevel);` (scope `VirtualHeightfieldMesh`) — Returns true if VirtualHeightfieldMesh is enabled.

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh/Private/VirtualHeightfieldMeshSceneProxy.h` (Private)


#### class `FVirtualHeightfieldMeshSceneProxy`  
`class FVirtualHeightfieldMeshSceneProxy final : public FPrimitiveSceneProxy`  
_L12-71_
- inherits: `FPrimitiveSceneProxy`
- desc: Scene proxy responsible for rendering of a Virtual Heightfield Mesh.
- L15 _public prototype_ `FVirtualHeightfieldMeshSceneProxy(class UVirtualHeightfieldMeshComponent* InComponent);`
- L19 _protected prototype_ `virtual SIZE_T GetTypeHash() const override;`
- L20 _protected prototype_ `virtual uint32 GetMemoryFootprint() const override;`
- L21 _protected prototype_ `virtual void CreateRenderThreadResources(FRHICommandListBase& RHICmdList) override;`
- L22 _protected prototype_ `virtual void DestroyRenderThreadResources() override;`
- L23 _protected prototype_ `virtual void OnTransformChanged(FRHICommandListBase& RHICmdList) override;`
- L24 _protected prototype_ `virtual bool HasSubprimitiveOcclusionQueries() const override;`
- L25 _protected prototype_ `virtual const TArray<FBoxSphereBounds>* GetOcclusionQueries(const FSceneView* View) const override;`
- L26 _protected prototype_ `virtual void AcceptOcclusionResults(const FSceneView* View, TArray<bool>* Results, int32 ResultsStart, int32 NumResults) override;`
- L27 _protected prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L28 _protected prototype_ `virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;`
- L32 _private prototype_ `void BuildOcclusionVolumes(TArrayView<FVector2D> const& InMinMaxData, FIntPoint const& InMinMaxSize, TArrayView<int32> const& InMinMaxMips, int32 InNumLods);`
- L33 _private prototype_ `static void OnVirtualTextureDestroyedCB(const FVirtualTextureProducerHandle& InHandle, void* Baton);`
- L36 _public member_ `bool bHiddenInEditor;`
- L38 _public member_ `class URuntimeVirtualTexture* RuntimeVirtualTexture;`
- L39 _public member_ `class FMaterialRenderProxy* Material;`
- L40 _public member_ `FMaterialRelevance MaterialRelevance;`
- L42 _public member_ `class UTexture2D* HeightMinMaxTexture;`
- L43 _public member_ `class UTexture2D* LodBiasTexture;`
- L44 _public member_ `class UTexture2D* LodBiasMinMaxTexture;`
- L46 _public member_ `class IAllocatedVirtualTexture* AllocatedVirtualTexture;`
- L47 _public member_ `bool bCallbackRegistered;`
- L49 _public member_ `uint32 NumQuadsPerTileSide;`
- L51 _public member_ `FVector UVToWorldScale;`
- L52 _public member_ `FMatrix UVToLocal;`
- L53 _public member_ `FMatrix UVToWorld;`
- L54 _public member_ `FMatrix WorldToUV;`
- L55 _public member_ `FMatrix WorldToUVTransposeAdjoint;`
- L57 _public member_ `class FVirtualHeightfieldMeshVertexFactory* VertexFactory;`
- L59 _public member_ `float Lod0ScreenSize;`
- L60 _public member_ `float Lod0Distribution;`
- L61 _public member_ `float LodDistribution;`
- L62 _public member_ `float LodBiasScale;`
- L64 _public member_ `int32 NumForceLoadLods;`
- L66 _public member_ `TArray<FVector2D> OcclusionData;`
- L67 _public member_ `int32 NumOcclusionLods;`
- L68 _public member_ `FIntPoint OcclusionGridSize;`
- L69 _public member_ `TArray<FBoxSphereBounds> OcclusionVolumes;`
- L70 _public member_ `TArray<FBoxSphereBounds> DefaultOcclusionVolumes;`

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh/Private/VirtualHeightfieldMeshVertexFactory.h` (Private)


#### struct `FVirtualHeightfieldMeshUserData`  
`struct FVirtualHeightfieldMeshUserData : public FOneFrameResource`  
_L37-42_
- inherits: `FOneFrameResource`
- desc: Per frame UserData to pass to the vertex shader.
- L39 _public member_ `FRHIShaderResourceView* InstanceBufferSRV;`
- L40 _public member_ `FVector3f LodViewOrigin;`
- L41 _public member_ `FVector4f LodDistances;`

#### class `FVirtualHeightfieldMeshIndexBuffer`  
`class FVirtualHeightfieldMeshIndexBuffer : public FIndexBuffer`  
_L47-62_
- inherits: `FIndexBuffer`
- desc: Index buffer for a single Virtual Heightfield Mesh tile.
- L51 _public function_ `FVirtualHeightfieldMeshIndexBuffer(int32 InNumQuadsPerSide) : NumQuadsPerSide(InNumQuadsPerSide)`
- L55 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L57 _public function_ `int32 GetIndexCount() const`
- L60 _private member_ `int32 NumIndices = 0;`
- L61 _private member_ `const int32 NumQuadsPerSide = 0;`

#### class `FVirtualHeightfieldMeshVertexFactory`  
`class FVirtualHeightfieldMeshVertexFactory : public FVertexFactory`  
_L67-91_
- inherits: `FVertexFactory`
- desc: Virtual Heightfield Mesh vertex factory.
- L69 _private prototype_ `DECLARE_VERTEX_FACTORY_TYPE(FVirtualHeightfieldMeshVertexFactory);`
- L72 _public prototype_ `FVirtualHeightfieldMeshVertexFactory(ERHIFeatureLevel::Type InFeatureLevel, const FVirtualHeightfieldMeshVertexFactoryParameters& InParams);`
- L74 _public prototype_ `~FVirtualHeightfieldMeshVertexFactory();`
- L76 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L77 _public prototype_ `virtual void ReleaseRHI() override;`
- L79 _public prototype_ `static bool ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters);`
- L80 _public prototype_ `static void ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`
- L81 _public prototype_ `static void ValidateCompiledResult(const FVertexFactoryType* Type, EShaderPlatform Platform, const FShaderParameterMap& ParameterMap, TArray<FString>& OutErrors);`
- L83 _public function_ `FIndexBuffer const* GetIndexBuffer() const`
- L86 _private member_ `FVirtualHeightfieldMeshVertexFactoryParameters Params;`
- L87 _private member_ `FVirtualHeightfieldMeshVertexFactoryBufferRef UniformBuffer;`
- L88 _private member_ `FVirtualHeightfieldMeshIndexBuffer* IndexBuffer = nullptr;`

#### Free symbols / members of external scopes

- L32 _typedef_ `typedef TUniformBufferRef<FVirtualHeightfieldMeshVertexFactoryParameters> FVirtualHeightfieldMeshVertexFactoryBufferRef;`

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh/Public/HeightfieldMinMaxRender.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace VirtualHeightfieldMesh`
- L17 _prototype_ `void DownsampleMinMaxAndCopy(FRDGBuilder& GraphBuilder, FRDGTexture* SrcTexture, FIntPoint SrcSize, FRDGTextureUAV* DstTexture, FIntPoint DstCoord);` (scope `VirtualHeightfieldMesh`) — Utility funtion to downsample a height texture and then pack and write the MinMax values to a texel in the destination texture. SrcTexture is expected to by G16 and DstTexture is expected to be RGBA8 packed as 16 bit min and max split across the 8 bit channels.
- L20 _prototype_ `void GenerateMinMaxTextureMips(FRDGBuilder& GraphBuilder, FRDGTexture* Texture, FIntPoint SrcSize, int32 NumMips);` (scope `VirtualHeightfieldMesh`) — Utility function to generate all additional mips from mip0 for a MinMax height texture already packed in RGBA8.

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh/Public/HeightfieldMinMaxTexture.h` (Public)


#### struct `FHeightfieldMinMaxTextureBuildDesc`  
`struct FHeightfieldMinMaxTextureBuildDesc`  
_L14-20_
- desc: Description object used to build the contents of a UHeightfieldMinMaxTexture.
- L16 _public member_ `uint32 SizeX = 0;`
- L17 _public member_ `uint32 SizeY = 0;`
- L18 _public member_ `uint32 NumMips = 0;`
- L19 _public member_ `uint8 const* Data = nullptr;`

#### class `UHeightfieldMinMaxTexture`  
`class UHeightfieldMinMaxTexture : public UObject`  
_L28-81_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Rendering, BlueprintType)`
- inherits: `UObject`
- desc: Container for a UTexture2D that can be built from a FHeightfieldMinMaxTextureBuildDesc description.
- L35 _public member_ `TObjectPtr<class UTexture2D> Texture = nullptr;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Texture, meta = (DisplayName = "Height MinMax Texture"))` — The Height MinMax texture.
- L39 _public member_ `TObjectPtr<class UTexture2D> LodBiasTexture = nullptr;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Texture, meta = (DisplayName = "LodBias Texture"))` — A LodBias texture derived from the Height MinMax texture
- L43 _public member_ `TObjectPtr<class UTexture2D> LodBiasMinMaxTexture = nullptr;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Texture, meta = (DisplayName = "LodBias MinMax Texture"))` — A LodBias MinMax texture derived from the LodBias texture
- L48 _protected member_ `int32 MaxCPULevels;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Texture, meta = (DisplayName = "Num CPU Levels", UIMin = "0", ClampMin = "0"))` — The number of mip levels to clone for CPU access.
- L53 _public member_ `TArray<FVector2D> TextureData;` — `UPROPERTY()` — The raw MinMax data from the low resolution mip levels of Texture. These are CPU access of the MinMax bounds.
- L57 _public member_ `FIntPoint TextureDataSize;` — `UPROPERTY()` — The size of the largest mip stored in TextureData.
- L61 _public member_ `TArray<int32> TextureDataMips;` — `UPROPERTY()` — The starting array index for the data of each mip stored in TextureData.
- L65 _public prototype_ `void BuildTexture(FHeightfieldMinMaxTextureBuildDesc const& InBuildDesc);` — Creates a new UTexture2D and stores it in the contained Texture.
- L71 _protected prototype_ `void RebuildMinMaxTexture(FHeightfieldMinMaxTextureBuildDesc const& InBuildDesc);` — Rebuild the contents of Texture using the passed in build description.
- L73 _protected prototype_ `void RebuildLodBiasTexture(FHeightfieldMinMaxTextureBuildDesc const& InBuildDesc);` — Rebuild the contents of LodBiasTexture from the MinMaxTexture.
- L75 _protected prototype_ `void RebuildCPUTextureData();` — Rebuild the contents of TextureData for the specified number of CPU mip levels.
- L78 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API VIRTUALHEIGHTFIELDMESH_API`

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh/Public/VirtualHeightfieldMeshActor.h` (Public)


#### class `AVirtualHeightfieldMesh`  
`class AVirtualHeightfieldMesh : public AActor`  
_L9-28_
- reflection: `UCLASS(hidecategories = (Actor, Collision, Cooking, Input, LOD, Replication), MinimalAPI)`
- inherits: `AActor`
- L16 _private member_ `TObjectPtr<class UVirtualHeightfieldMeshComponent> VirtualHeightfieldMeshComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VirtualTexture, meta = (AllowPrivateAccess = "true"))` — Component for rendering the big mesh.
- L21 _private member_ `TObjectPtr<class UBoxComponent> Box = nullptr;` — `UPROPERTY(Transient)` — Box for visualizing virtual texture extents.
- L26 _protected function_ `virtual bool NeedsLoadForServer() const override`

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh/Public/VirtualHeightfieldMeshComponent.h` (Public)


#### class `UVirtualHeightfieldMeshComponent`  
`class UVirtualHeightfieldMeshComponent : public UPrimitiveComponent`  
_L18-153_
- reflection: `UCLASS(MinimalAPI, Blueprintable, ClassGroup = Rendering, hideCategories = (Activation, Collision, Cooking, HLOD, Navigation, Mobility, Object, Physics, VirtualTexture))`
- inherits: `UPrimitiveComponent`
- desc: Component to render a heightfield mesh using a virtual texture heightmap.
- L25 _protected member_ `TSoftObjectPtr<ARuntimeVirtualTextureVolume> VirtualTexture;` — `UPROPERTY(EditAnywhere, Category = Heightfield)` — The RuntimeVirtualTextureVolume that contains virtual texture heightmap.
- L29 _protected member_ `TObjectPtr<ARuntimeVirtualTextureVolume> VirtualTextureRef;` — `UPROPERTY(Transient)` — UObject ref resolved from VirtualTexture weak ref.
- L33 _protected member_ `TObjectPtr<UObject> VirtualTextureThumbnail = nullptr;` — `UPROPERTY(VisibleAnywhere, Transient, Category = Heightfield)` — Placeholder for details customization image.
- L37 _protected member_ `bool bCopyBoundsButton;` — `UPROPERTY(VisibleAnywhere, Transient, Category = Heightfield)` — Placeholder for details customization button.
- L41 _protected member_ `TObjectPtr<UHeightfieldMinMaxTexture> MinMaxTexture = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HeightfieldBuild, meta = (DisplayName = "MinMax Texture"))` — Texture object containing minimum and maximum height values.
- L45 _protected member_ `int32 NumMinMaxTextureBuildLevels = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HeightfieldBuild, meta = (DisplayName = "MinMax Build Levels", UIMin = "0"))` — Number of levels to build in the MinMax Texture. A default value of 0 will build all levels from the heightfield.
- L49 _protected member_ `bool bBuildMinMaxTextureButton;` — `UPROPERTY(VisibleAnywhere, Transient, Category = HeightfieldBuild)` — Placeholder for details customization button.
- L53 _protected member_ `TObjectPtr<UMaterialInterface> Material = nullptr;` — `UPROPERTY(EditAnywhere, Category = Rendering)` — The material to apply.
- L57 _protected member_ `float Lod0ScreenSize = 1.f;` — `UPROPERTY(EditAnywhere, Category = Rendering, meta = (DisplayName = "LOD 0 Screen Size", ClampMin = "0.1", UIMin = "0.1"))` — Target screen size for a LOD 0 tile. A smaller value uniformly increases the geometry resolution on screen.
- L61 _protected member_ `float Lod0Distribution = 1.f;` — `UPROPERTY(EditAnywhere, Category = Rendering, meta = (DisplayName = "LOD 0 Distance Scale", ClampMin = "1.0", UIMin = "1.0"))` — Distribution multiplier applied only for LOD 0. A larger value increases the distance to the first LOD transition.
- L65 _protected member_ `float LodDistribution = 2.f;` — `UPROPERTY(EditAnywhere, Category = Rendering, meta = (DisplayName = "LOD Distribution", ClampMin = "1.0", UIMin = "1.0", UIMax = "3.0"))` — Distribution multiplier applied for each LOD level. A larger value increases the distance exponentially between each LOD transition.
- L69 _protected member_ `float LodBiasScale = 0.f;` — `UPROPERTY(EditAnywhere, Category = Rendering, meta = (DisplayName = "LOD Bias Scale", ClampMin = "0.0", ClampMax = "10.0", UIMin = "0.0", UIMax = "10.0"))` — Scale applied to LodBias texture. A larger value increases resolution where the LodBias texture is set.
- L73 _protected member_ `int32 NumForceLoadLods = 0;` — `UPROPERTY(EditAnywhere, Category = Rendering, meta = (DisplayName = "Force Load LODs", ClampMin = "0", ClampMax = "4"))` — The number of levels that we force loaded. A higher number can reduce LOD pop in but allocates more of the virtual texture memory pool.
- L77 _protected member_ `int32 NumOcclusionLods = 0;` — `UPROPERTY(EditAnywhere, Category = Rendering, meta = (DisplayName = "Occlusion LODs", ClampMin = "0", ClampMax = "5"))` — The number of levels that we calculate occlusion volumes for. A higher number gives finer occlusion at the cost of more queries.
- L81 _protected member_ `bool bHiddenInEditor = true;` — `UPROPERTY(EditAnywhere, Category = Rendering, meta = (DisplayName = "Actor Hidden In Editor", DisplayAfter = "bHiddenInGame"))` — Allows us to only see this actor in game and not in the Editor. This is useful if we only want to see the Heightfield virtual texture source primitives during edition.
- L85 _protected member_ `bool bWorldPositionOffsetVelocity = false;` — `UPROPERTY(EditAnywhere, Category = Rendering, AdvancedDisplay)` — Allows material World Position Offset to contribute to velocity rendering.
- L89 _public function_ `bool GetHiddenInEditor() const` — Get the HiddenInEditor flag  on this component.
- L92 _public prototype_ `ARuntimeVirtualTextureVolume* GetVirtualTextureVolume() const;` — Get the associated runtime virtual texture volume. Can return nullptr if the volume is from an unloaded level.
- L94 _public prototype_ `FTransform GetVirtualTextureTransform() const;` — Get the associated runtime virtual texture transform including any texel snap offset.
- L96 _public prototype_ `URuntimeVirtualTexture* GetVirtualTexture() const;` — Get the associated runtime virtual texture.
- L99 _public prototype_ `bool IsMinMaxTextureEnabled() const;` — Returns true if a MinMax height texture is relevant for this virtual texture type.
- L101 _public function_ `UHeightfieldMinMaxTexture* GetMinMaxTexture() const` — Get the MinMax height texture on this component.
- L103 _public function_ `int32 GetNumMinMaxTextureBuildLevels()` — Get the number of levels to build in the MinMax Texture.
- L107 _public function_ `void SetMinMaxTexture(UHeightfieldMinMaxTexture* InTexture)` — Set a new asset to hold the MinMax height texture. This should only be called directly before setting data to the new asset.
- L109 _public prototype_ `void InitializeMinMaxTexture(uint32 InSizeX, uint32 InSizeY, uint32 InNumMips, uint8* InData);` — Initialize the MinMax height texture with the passed in size and data.
- L112 _public function_ `UMaterialInterface* GetMaterial() const`
- L113 _public function_ `float GetLod0ScreenSize() const`
- L114 _public function_ `float GetLod0Distribution() const`
- L115 _public function_ `float GetLodDistribution() const`
- L116 _public function_ `float GetLodBiasScale() const`
- L117 _public function_ `int32 GetNumForceLoadLods() const`
- L118 _public function_ `int32 GetNumOcclusionLods() const`
- L123 _protected prototype_ `void GatherHideFlags(bool& InOutHidePrimitivesInEditor, bool& InOutHidePrimitivesInGame) const;` — `UFUNCTION()` — Function used by the VirtualTexture delegate to retrieve our HidePrimitives flags.
- L126 _protected prototype_ `void OnVirtualTextureTransformUpdate(USceneComponent* InRootComponent, EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport);` — Handles when the transform is updated on the associated VirtualTexture.
- L130 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L135 _protected prototype_ `virtual void OnRegister() override;`
- L136 _protected prototype_ `virtual void OnUnregister() override;`
- L137 _protected prototype_ `virtual void ApplyWorldOffset(const FVector& InOffset, bool bWorldShift) override;`
- L141 _protected prototype_ `virtual bool IsVisible() const override;`
- L142 _protected prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L146 _protected prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L147 _protected function_ `virtual bool SupportsStaticLighting() const override`
- L148 _protected prototype_ `virtual void SetMaterial(int32 ElementIndex, class UMaterialInterface* Material) override;`
- L149 _protected function_ `virtual UMaterialInterface* GetMaterial(int32 Index) const override`
- L150 _protected prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;`
- L151 _protected function_ `virtual bool SupportsWorldPositionOffsetVelocity() const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API VIRTUALHEIGHTFIELDMESH_API`

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh/Public/VirtualHeightfieldMeshModule.h` (Public)


#### class `FVirtualHeightfieldMeshModule`  
`class FVirtualHeightfieldMeshModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- desc: Implements the VirtualHeightfieldMesh module
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
