# Plugins / NiagaraUIRenderer

- module root: `Plugins/FX/NiagaraUIRenderer/Source/NiagaraUIRenderer`
- headers: 9; symbols: 137
- symbol kinds: class=8, enum=1, enumerator=3, function=12, member=55, prototype=53, struct=3, typedef=2
- PrivateDependencyModuleNames: RHI, RenderCore
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Niagara, NiagaraCore, Slate, SlateCore, UMG

### `Plugins/FX/NiagaraUIRenderer/Source/NiagaraUIRenderer/Private/NiagaraUISlateRenderContext.h` (Private)


#### class `FNiagaraUISlateRenderContext`  
`class FNiagaraUISlateRenderContext : public FNiagaraUIRenderContext`  
_L6-16_
- inherits: `FNiagaraUIRenderContext`
- L9 _public prototype_ `explicit FNiagaraUISlateRenderContext(FMaterialCacheMap& InCacheMap, const FGeometry& InAllottedGeometry, FSlateWindowElementList& InOutDrawElements);`
- L10 _public prototype_ `virtual ~FNiagaraUISlateRenderContext() = default;`
- L12 _public prototype_ `virtual void DrawCustomVerts(const UMaterialInterface* Material, const TArray<FSlateVertex>& Vertices, const TArray<SlateIndex>& Indices) const override;`
- L15 _private member_ `FSlateWindowElementList& OutDrawElements;`

### `Plugins/FX/NiagaraUIRenderer/Source/NiagaraUIRenderer/Public/NiagaraUIComponent.h` (Public)


#### class `UNiagaraUIComponent`  
`class UNiagaraUIComponent : public UNiagaraComponent`  
_L10-30_
- reflection: `UCLASS(ClassGroup=FX, meta=(BlueprintSpawnableComponent, DisplayName="Niagara UI Component"))`
- inherits: `UNiagaraComponent`
- L15 _public prototype_ `UNiagaraUIComponent();`
- L18 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;` — BEGIN: UNiagaraComponent interface
- L19 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L23 _public prototype_ `const FNiagaraUIRenderData* GetRenderData() const;` — Get the last generated UI render data
- L26 _private prototype_ `void CreateRenderData();`
- L29 _private member_ `TUniquePtr<FNiagaraUIRenderData> RenderData;`

### `Plugins/FX/NiagaraUIRenderer/Source/NiagaraUIRenderer/Public/NiagaraUIDebugRenderer.h` (Public)


#### class `FNiagaraUIDebugRenderer`  
`class FNiagaraUIDebugRenderer : public FNiagaraRenderer`  
_L11-20_
- inherits: `FNiagaraRenderer`
- L14 _public prototype_ `explicit FNiagaraUIDebugRenderer(ERHIFeatureLevel::Type FeatureLevel, const UNiagaraRendererProperties* InProps, const FNiagaraEmitterInstance* Emitter);`
- L15 _public prototype_ `virtual ~FNiagaraUIDebugRenderer() = default;`
- L18 _public prototype_ `virtual FNiagaraDynamicDataBase* GenerateDynamicData(const FNiagaraSceneProxy* Proxy, const UNiagaraRendererProperties* InProperties, const FNiagaraEmitterInstance* Emitter) const override;` — FNiagaraRenderer interface

### `Plugins/FX/NiagaraUIRenderer/Source/NiagaraUIRenderer/Public/NiagaraUIRenderContext.h` (Public)


#### struct `FNiagaraUIRendererScratchBuffers`  
`struct FNiagaraUIRendererScratchBuffers`  
_L15-19_
- L17 _public member_ `TArray<FSlateVertex>& ScratchVertices;`
- L18 _public member_ `TArray<SlateIndex>& ScratchIndices;`

#### class `FNiagaraUIRenderContext`  
`class FNiagaraUIRenderContext`  
_L21-80_
- L24 _public typedef_ `using FMaterialCacheMap = TMap<FObjectKey, FSlateResourceHandle>;`
- L27 _public prototype_ `explicit FNiagaraUIRenderContext(FMaterialCacheMap& InCacheMap, const FGeometry& InAllottedGeometry);`
- L28 _public prototype_ `virtual ~FNiagaraUIRenderContext() = default;`
- L31 _public prototype_ `FNiagaraUIRendererScratchBuffers GetScratchBuffers(int32 NumVertices, int32 NumInidices) const;` — Get scratch buffers for generating vertex data into
- L34 _public prototype_ `TConstArrayView<int32> CreateParticleOrderTable(int32 NumInstances, ENiagaraSortMode SortMode, FNiagaraDataSetReaderFloat<FNiagaraPosition> PositionReader, FNiagaraDataSetReaderFloat<float> SortOrderReader, int32 RendererVisibility, FNiagaraDataSetReaderInt32<int32> VisTagReader) const;` — Genrate an indirection table for particles both sorting and culling particles
- L37 _public prototype_ `void DrawCustomVerts(const UMaterialInterface* Material) const;` — Draw the vertices build in the scratch buffer, will clear the buffer post draw
- L40 _public prototype_ `virtual void DrawCustomVerts(const UMaterialInterface* Material, const TArray<FSlateVertex>& Vertices, const TArray<SlateIndex>& Indices) const = 0;` — Draw the verticies provided
- L43 _public function_ `FVector2f PositionToScreen(const FNiagaraPosition& WorldPosition) const` — Convert Simulation Posiiton to Widget Screen
- L51 _public function_ `FVector2f SizeToScreen(const FVector2f& WorldSize) const`
- L57 _public function_ `void SetLayerId(int32 InLayerId)` — Set functions to override default behavior
- L58 _public function_ `void SetDrawEffect(ESlateDrawEffect InDrawEffect)`
- L59 _public function_ `void SetScreenParameters(ENiagaraUIScreenPlane InScreenPlane)`
- L60 _public function_ `void SetScreenOrigin(const FVector2f& InScreenOrigin)`
- L61 _public prototype_ `void SetScreenOriginAlignment(EHorizontalAlignment HorizontalAlignment, EVerticalAlignment VerticalAlignment);`
- L62 _public function_ `void SetScreenScale(float InScreenScale)`
- L65 _protected prototype_ `const FSlateResourceHandle& GetOrCreateMaterialHandle(const UMaterialInterface* Material) const;`
- L68 _protected member_ `mutable TArray<FSlateVertex> ScratchVertices;`
- L69 _protected member_ `mutable TArray<SlateIndex> ScratchIndices;`
- L70 _protected member_ `mutable TArray<int32> ParticleOrderTable;`
- L72 _protected member_ `FMaterialCacheMap& MaterialHandleCache;`
- L73 _protected member_ `const FGeometry& AllottedGeometry;`
- L74 _protected member_ `int32 LayerId = 0;`
- L75 _protected member_ `ESlateDrawEffect DrawEffect = ESlateDrawEffect::None;`
- L77 _protected member_ `ENiagaraUIScreenPlane ScreenPlane = ENiagaraUIScreenPlane::XZ;`
- L78 _protected member_ `FVector2f ScreenOrigin = FVector2f::Zero();`
- L79 _protected member_ `float ScreenScale = 1.0f;`

### `Plugins/FX/NiagaraUIRenderer/Source/NiagaraUIRenderer/Public/NiagaraUIRendererProperties.h` (Public)


#### class `UNiagaraUIRendererProperties`  
`class UNiagaraUIRendererProperties : public UNiagaraRendererProperties`  
_L14-30_
- reflection: `UCLASS(ABSTRACT, MinimalAPI)`
- inherits: `UNiagaraRendererProperties`
- L20 _public prototype_ `virtual FNiagaraRenderer* CreateEmitterRenderer(ERHIFeatureLevel::Type FeatureLevel, const FNiagaraEmitterInstance* Emitter, const FNiagaraSystemInstanceController& InController) final override;`
- L21 _public prototype_ `virtual FNiagaraBoundsCalculator* CreateBoundsCalculator() final override;`
- L22 _public prototype_ `virtual bool IsSimTargetSupported(ENiagaraSimTarget InSimTarget) const final override;`
- L24 _public function_ `virtual bool SupportsDebugDraw() const`
- L28 _public function_ `virtual FNiagaraUIRendererRenderData* CreateRenderData(const FNiagaraEmitterInstance&) const`
- L29 _public function_ `virtual void ExecuteRender(const FNiagaraUIRenderContext& RenderContext, const FNiagaraUIRendererRenderData& RendererRenderData) const`

### `Plugins/FX/NiagaraUIRenderer/Source/NiagaraUIRenderer/Public/NiagaraUISpriteRendererProperties.h` (Public)


#### class `UNiagaraUISpriteRendererProperties`  
`class UNiagaraUISpriteRendererProperties : public UNiagaraUIRendererProperties`  
_L9-88_
- reflection: `UCLASS(EditInlineNew, meta=(DisplayName="UI Sprite Renderer", PrioritizeCategories="Material Bindings SubUV Sorting"))`
- inherits: `UNiagaraUIRendererProperties`
- desc: Niagara Renderer for sprites in the UI (Slate / UMG)
- L14 _public prototype_ `UNiagaraUISpriteRendererProperties();`
- L17 _public prototype_ `virtual void GetUsedMaterials(const FNiagaraEmitterInstance* EmitterInstance, TArray<UMaterialInterface*>& OutMaterials) const override;`
- L18 _public prototype_ `virtual void PostInitProperties() override;`
- L19 _public prototype_ `virtual void PostLoad() override;`
- L21 _public prototype_ `virtual void GetRendererWidgets(const FNiagaraEmitterInstance* InEmitter, TArray<TSharedPtr<SWidget>>& OutWidgets, TSharedPtr<FAssetThumbnailPool> InThumbnailPool) const override;`
- L22 _public prototype_ `virtual void GetRendererTooltipWidgets(const FNiagaraEmitterInstance* InEmitter, TArray<TSharedPtr<SWidget>>& OutWidgets, TSharedPtr<FAssetThumbnailPool> InThumbnailPool) const override;`
- L23 _public prototype_ `virtual void GetRendererFeedback(const FVersionedNiagaraEmitter& InEmitter, TArray<FNiagaraRendererFeedback>& OutErrors, TArray<FNiagaraRendererFeedback>& OutWarnings, TArray<FNiagaraRendererFeedback>& OutInfo) const override;`
- L25 _public prototype_ `virtual void CacheFromCompiledData(const FNiagaraDataSetCompiledData* CompiledData) override;`
- L29 _public prototype_ `virtual FNiagaraUIRendererRenderData* CreateRenderData(const FNiagaraEmitterInstance& EmitterInstance) const override;`
- L30 _public prototype_ `virtual void ExecuteRender(const FNiagaraUIRenderContext& RenderContext, const FNiagaraUIRendererRenderData& RendererRenderData) const override;`
- L33 _public prototype_ `void InitBindings();`
- L35 _public prototype_ `static void ProcessDeferredInit();`
- L39 _public member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, Category="Material")`
- L42 _public member_ `FVector2f SubImageSize = FVector2f(1.0f, 1.0f);` — `UPROPERTY(EditAnywhere, Category="SubUV", meta=(ClampMin="1"))`
- L48 _public member_ `ENiagaraSortMode SortMode = ENiagaraSortMode::None;` — `UPROPERTY(EditAnywhere, Category="Sorting And Visibility")`
- L52 _public member_ `uint32 RendererVisibility = 0;` — `UPROPERTY(EditAnywhere, Category = "Sorting And Visibility")` — If a render visibility tag is present, particles whose tag matches this value will be visible in this renderer.
- L55 _public member_ `FNiagaraVariableAttributeBinding PositionBinding;` — `UPROPERTY(EditAnywhere, Category="Bindings")`
- L58 _public member_ `FNiagaraVariableAttributeBinding ColorBinding;` — `UPROPERTY(EditAnywhere, Category="Bindings")`
- L61 _public member_ `FNiagaraVariableAttributeBinding SpriteSizeBinding;` — `UPROPERTY(EditAnywhere, Category="Bindings")`
- L64 _public member_ `FNiagaraVariableAttributeBinding SpriteRotationBinding;` — `UPROPERTY(EditAnywhere, Category="Bindings")`
- L67 _public member_ `FNiagaraVariableAttributeBinding SubImageIndexBinding;` — `UPROPERTY(EditAnywhere, Category="Bindings")`
- L71 _public member_ `FNiagaraVariableAttributeBinding DynamicMaterialParameterBinding;` — `UPROPERTY(EditAnywhere, Category="Bindings")` — Packed into TexCoord[1] / TexCoord[2]
- L74 _public member_ `FNiagaraVariableAttributeBinding CustomSortingBinding;` — `UPROPERTY(EditAnywhere, Category = "Bindings")`
- L77 _public member_ `FNiagaraVariableAttributeBinding RendererVisibilityTagBinding;` — `UPROPERTY(EditAnywhere, Category = "Bindings")`
- L80 _private member_ `FNiagaraDataSetAccessor<FNiagaraPosition> PositionDataSetAccessor;`
- L81 _private member_ `FNiagaraDataSetAccessor<FLinearColor> ColorDataSetAccessor;`
- L82 _private member_ `FNiagaraDataSetAccessor<FVector2f> SpriteSizeDataSetAccessor;`
- L83 _private member_ `FNiagaraDataSetAccessor<float> SpriteRotationDataSetAccessor;`
- L84 _private member_ `FNiagaraDataSetAccessor<float> SubImageIndexDataSetAccessor;`
- L85 _private member_ `FNiagaraDataSetAccessor<FVector4f> DynamicMaterialParameterDataSetAccessor;`
- L86 _private member_ `FNiagaraDataSetAccessor<float> CustomSortingDataSetAccessor;`
- L87 _private member_ `FNiagaraDataSetAccessor<int32> RendererVisibilityTagDataSetAccessor;`

### `Plugins/FX/NiagaraUIRenderer/Source/NiagaraUIRenderer/Public/NiagaraUITypes.h` (Public)


#### enum `ENiagaraUIScreenPlane`  
`enum class ENiagaraUIScreenPlane : uint8`  
_L12-20_
- reflection: `UENUM(BlueprintType)`
- desc: Which world-space plane to project Niagara particle positions onto.
- L15 _public enumerator_ `XY` — Project X (right) and Y (up) — typical for effects simulated in the XY plane.
- L17 _public enumerator_ `XZ` — Project X (right) and Z (up).
- L19 _public enumerator_ `YZ` — Project Y (right) and Z (up).

#### struct `FNiagaraUIRendererRenderData`  
`struct FNiagaraUIRendererRenderData`  
_L22-28_
- L24 _public member_ `TWeakObjectPtr<const UNiagaraUIRendererProperties> WeakProperties;`
- L25 _public member_ `TWeakObjectPtr<UMaterialInterface> WeakMaterial;`
- L26 _public member_ `FNiagaraDataBufferRef DataBuffer;`
- L27 _public member_ `int32 SortOrder = 0;`

#### struct `FNiagaraUIRenderData`  
`struct FNiagaraUIRenderData`  
_L30-33_
- L32 _public member_ `TArray<TUniquePtr<FNiagaraUIRendererRenderData>> RendererRenderDatas;`

### `Plugins/FX/NiagaraUIRenderer/Source/NiagaraUIRenderer/Public/NiagaraUIWidget.h` (Public)


#### class `UNiagaraUIWidget`  
`class UNiagaraUIWidget : public UWidget`  
_L14-72_
- reflection: `UCLASS(meta=(DisplayName="Niagara UI Widget"))`
- inherits: `UWidget`
- L19 _public prototype_ `UNiagaraUIWidget(const FObjectInitializer& ObjectInitializer);`
- L23 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L28 _public prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — BEGIN: UWidget interface
- L29 _public prototype_ `virtual void SynchronizeProperties() override;`
- L30 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L32 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L37 _public prototype_ `void SetDesiredWidgetSize(FVector2D InSize);` — `UFUNCTION(BlueprintCallable, Category = "Niagara")`
- L40 _private prototype_ `void RecreateOrInitialize();`
- L45 _protected member_ `FVector2D DesiredWidgetSize = FVector2D(100.0, 100.0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Rendering")` — Layout for widget, does not impact simulation coordinate translation
- L49 _protected member_ `float WorldToScreenScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Rendering")` — Scale to translate Niagara units to UI units
- L53 _protected member_ `ENiagaraUIScreenPlane WorldToScreenPlane = ENiagaraUIScreenPlane::XY;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Rendering")` — Axis to translate Niagara to UI
- L57 _protected member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = HAlign_Center;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Rendering")` — Horizontal alignment that represents the world origin
- L61 _protected member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment = VAlign_Center;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Rendering")` — Vertical alignment that represents the world origin
- L65 _protected member_ `TObjectPtr<UNiagaraSystem> NiagaraSystem;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")` — System simulation to use
- L69 _protected member_ `TObjectPtr<UNiagaraUIComponent> NiagaraComponent;` — `UPROPERTY(Transient)` — Active component, used for rendering
- L71 _protected member_ `TSharedPtr<SNiagaraUIWidget> NiagaraWidget;`

### `Plugins/FX/NiagaraUIRenderer/Source/NiagaraUIRenderer/Public/SNiagaraUIWidget.h` (Public)


#### class `SNiagaraUIWidget`  
`class SNiagaraUIWidget : public SLeafWidget`  
_L12-54_
- inherits: `SLeafWidget`
- L14 _private typedef_ `using Super = SLeafWidget;`
- L17 _public function_ `SLATE_BEGIN_ARGS(SNiagaraUIWidget)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L21 _public prototype_ `virtual ~SNiagaraUIWidget();`
- L24 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — BEGIN: SWidget interface
- L25 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L26 _public prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L27 _public function_ `virtual bool ComputeVolatility() const override`
- L31 _public prototype_ `void SetNiagaraComponent(UNiagaraUIComponent* InComponent);` — Switch which component this widget reads from.
- L32 _public prototype_ `void SetDesiredSize(FVector2D InSize);`
- L33 _public prototype_ `void SetWorldToScreenScale(float InScale);`
- L34 _public prototype_ `void SetWorldToScreenPlane(ENiagaraUIScreenPlane InScreenPlane);`
- L35 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);`
- L36 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);`
- L39 _private member_ `TWeakObjectPtr<UNiagaraUIComponent> WeakNiagaraComponent;`
- L41 _private member_ `FVector2D DesiredWidgetSize = FVector2D(100.0, 100.0);`
- L43 _private member_ `float WorldToScreenScale = 1.0f;`
- L44 _private member_ `ENiagaraUIScreenPlane WorldToScreenPlane = ENiagaraUIScreenPlane::XY;`
- L45 _private member_ `EHorizontalAlignment HorizontalAlignment = HAlign_Center;`
- L46 _private member_ `EVerticalAlignment VerticalAlignment = VAlign_Center;`
- L49 _private member_ `mutable TMap<FObjectKey, FSlateResourceHandle> MaterialHandleCache;` — Cached map from material to slate resource
- L52 _private member_ `FDelegateHandle MaterialCompilationFinishedHandle;`
