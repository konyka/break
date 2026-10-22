# Editor / ClothPainter

- module root: `Source/Editor/ClothPainter`
- headers: 17; symbols: 390
- symbol kinds: class=26, delegate=2, enum=2, enumerator=7, externvar=1, function=53, macro=1, member=98, namespace=1, prototype=192, struct=4, typedef=3
- PrivateDependencyModuleNames: AdvancedPreviewScene, AssetRegistry, AssetTools, ClassViewer, ClothingSystemEditorInterface, ClothingSystemRuntimeCommon, ClothingSystemRuntimeInterface, ClothingSystemRuntimeNv, Core, CoreUObject, EditorFramework, EditorWidgets, Engine, InputCore, Kismet, MainFrame, MeshPaint, PropertyEditor, SkeletalMeshEditor, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd

### `Source/Editor/ClothPainter/Private/ClothMeshAdapter.h` (Private)


#### class `FClothMeshPaintAdapter`  
`class FClothMeshPaintAdapter : public FBaseMeshPaintGeometryAdapter`  
_L26-110_
- inherits: `FBaseMeshPaintGeometryAdapter`
- desc: Adapter used to paint simulation specific properties to cloth assets inside of a Skeletal mesh
- L46 _public function_ `static void InitializeAdapterGlobals()`
- L47 _public function_ `static void AddReferencedObjectsGlobals(FReferenceCollector& Collector)`
- L48 _public function_ `static void CleanupGlobals()`
- L50 _public prototype_ `virtual bool Construct(UMeshComponent* InComponent, int32 InPaintingMeshLODIndex) override;`
- L51 _public prototype_ `virtual bool Initialize() override;`
- L52 _public function_ `virtual void OnAdded() override`
- L53 _public function_ `virtual void OnRemoved() override`
- L54 _public function_ `virtual bool IsValid() const override`
- L56 _public function_ `virtual bool SupportsTexturePaint() const override`
- L57 _public function_ `virtual bool SupportsVertexPaint() const override`
- L59 _public prototype_ `virtual bool LineTraceComponent(struct FHitResult& OutHit, const FVector Start, const FVector End, const struct FCollisionQueryParams& Params) const override;`
- L60 _public prototype_ `virtual void QueryPaintableTextures(int32 MaterialIndex, int32& OutDefaultIndex, TArray<struct FPaintableTexture>& InOutTextureList) override;`
- L61 _public prototype_ `virtual void ApplyOrRemoveTextureOverride(UTexture* SourceTexture, UTexture* OverrideTexture) const override;`
- L62 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L64 _public prototype_ `virtual void PreEdit() override;`
- L65 _public prototype_ `virtual void PostEdit() override;`
- L67 _public prototype_ `virtual void GetTextureCoordinate(int32 VertexIndex, int32 ChannelIndex, FVector2D& OutTextureCoordinate) const override;`
- L68 _public prototype_ `virtual void GetVertexColor(int32 VertexIndex, FColor& OutColor, bool bInstance = true) const override;`
- L69 _public prototype_ `virtual void SetVertexColor(int32 VertexIndex, FColor Color, bool bInstance = true) override;`
- L70 _public prototype_ `virtual FMatrix GetComponentToWorldMatrix() const override;`
- L72 _public prototype_ `virtual TArray<FVector> SphereIntersectVertices(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing) const;`
- L75 _public prototype_ `virtual void SetSelectedClothingAsset(const FGuid& InAssetGuid, int32 InAssetLod, int32 InMaskIndex);` — Sets the represented clothing asset to the UClothingAssetBase retrieved from the AssetGUID
- L78 _public prototype_ `const TArray<int32>* GetVertexNeighbors(int32 InVertexIndex) const;` — Gets a list of the neighbors of the specified vertex
- L81 _public prototype_ `FPointWeightMap* GetCurrentMask() const;` — Get the current mask we're editing
- L86 _protected prototype_ `virtual bool InitializeVertexData();` — Initialize adapter data ready for painting
- L89 _protected prototype_ `bool HasValidSelection() const;` — Whether or not our current asset/lod/mask selection has a valid paintable surface
- L93 _protected member_ `USkeletalMeshComponent* SkeletalMeshComponent;` — (Debug) Skeletal Mesh Component this adapter represents
- L95 _protected member_ `USkeletalMesh* ReferencedSkeletalMesh;` — Skeletal mesh asset this adapter represents
- L98 _protected member_ `int32 PaintingClothLODIndex;` — LOD index to paint to (cloth LOD data)
- L101 _protected member_ `int32 PaintingClothMaskIndex;` — Mask inside the current LOD to paint
- L104 _protected member_ `UClothingAssetBase* SelectedAsset;` — Currently selected clothing asset object to paint to
- L107 _protected member_ `TArray<UClothingAssetBase*> ClothingAssets;` — List of clothing assets objects contained by ReferenceSkeletalMesh
- L109 _protected member_ `TArray<FClothAssetInfo> AssetInfoMap;` — List of clothing asset info structs contained by ReferenceSkeletalMesh

#### struct `FClothMeshPaintAdapter::FClothAssetInfo`  
`struct FClothAssetInfo`  
_L29-44_
- L32 _public member_ `int32 VertexStart;` — Begin/End for this asset's verts in the provided buffer.
- L33 _public member_ `int32 VertexEnd;`
- L36 _public member_ `int32 IndexStart;` — Begin/End for this asset's indices in the provided buffer.
- L37 _public member_ `int32 IndexEnd;`
- L40 _public member_ `TArray<TArray<int32>> NeighborMap;` — Map of index to neigbor indices
- L43 _public member_ `UClothingAssetCommon* Asset;` — The actual clothing asset relating to this data

#### class `FClothMeshPaintAdapterFactory`  
`class FClothMeshPaintAdapterFactory : public IMeshPaintGeometryAdapterFactory`  
_L115-122_
- inherits: `IMeshPaintGeometryAdapterFactory`
- L118 _public prototype_ `virtual TSharedPtr<IMeshPaintGeometryAdapter> Construct(UMeshComponent* InComponent, int32 InPaintingMeshLODIndex) const override;`
- L119 _public function_ `virtual void InitializeAdapterGlobals() override`
- L120 _public function_ `virtual void AddReferencedObjectsGlobals(FReferenceCollector& Collector) override`
- L121 _public function_ `virtual void CleanupGlobals() override`

### `Source/Editor/ClothPainter/Private/ClothPaintSettings.h` (Private)


#### enum `EPaintableClothProperty`  
`enum class EPaintableClothProperty`  
_L16-24_
- reflection: `UENUM()`
- L19 _public enumerator_ `MaxDistances` — Max distances cloth property
- L21 _public enumerator_ `BackstopDistances` — Backstop cloth property
- L23 _public enumerator_ `BackstopRadius` — Backstop radius property

#### class `UClothPainterSettings`  
`class UClothPainterSettings : public UMeshPaintSettings`  
_L27-100_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UMeshPaintSettings`
- L33 _public function_ `UClothPainterSettings() : UMeshPaintSettings() , ViewMin(0.0f) , ViewMax(100.0f) , bAutoViewRange(false) , AutoCalculatedViewMin(0.0f) , AutoCalculatedViewMax(0.0f) , bFlipNormal(false) , bCullBackface(false) , Opacity(1.f)`
- L45 _public function_ `float GetViewMin()`
- L54 _public function_ `float GetViewMax()`
- L60 _public member_ `FOnClothingAssetSelectionChangedMulticaster OnAssetSelectionChanged;` — Delegates to communicate with objects concerned with the settings changing
- L65 _protected member_ `float ViewMin;` — `UPROPERTY(EditAnywhere, Config, Category = View, meta = (UIMin = 0, UIMax = 100000, ClampMin = 0, ClampMax = 100000, EditCondition = "!bAutoViewRange"))` — When painting float/1D values, this is considered the zero or black point
- L69 _protected member_ `float ViewMax;` — `UPROPERTY(EditAnywhere, Config, Category = View, meta = (UIMin = 0, UIMax = 100000, ClampMin = 0, ClampMax = 100000, EditCondition = "!bAutoViewRange"))` — When painting float/1D values, this is considered the one or white point
- L75 _public member_ `bool bAutoViewRange;` — `UPROPERTY(EditAnywhere, Category = View)` — When set, the view min and max values will be calculated from the values present in the currently editable mask
- L79 _public member_ `float AutoCalculatedViewMin;` — `UPROPERTY()` — Storage for auto calculated view min value
- L83 _public member_ `float AutoCalculatedViewMax;` — `UPROPERTY()` — Storage for auto calculated view max value
- L87 _public member_ `TArray<TObjectPtr<UClothingAssetCommon>> ClothingAssets;` — `UPROPERTY()` — Array of Clothing assets
- L91 _public member_ `bool bFlipNormal;` — `UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = View)` — Whether to flip normals on the mesh preview
- L95 _public member_ `bool bCullBackface;` — `UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = View)` — Whether to cull backfacing triangles when rendering the mesh preview
- L99 _public member_ `float Opacity;` — `UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = View, meta = (UIMin = 0, UIMax = 1, ClampMin = 0, ClampMax = 1))` — Opacity of the mesh preview

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnClothingAssetSelectionChangedMulticaster, UClothingAssetCommon*, int32, int32);`
- L12 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnClothingAssetSelectionChangedMulticaster, UClothingAssetCommon*, int32, int32);`
- L13 _typedef_ `typedef FOnClothingAssetSelectionChangedMulticaster::FDelegate FOnClothingAssetSelectionChanged;`

### `Source/Editor/ClothPainter/Private/ClothPaintSettingsCustomization.h` (Private)


#### class `FClothPaintSettingsCustomization`  
`class FClothPaintSettingsCustomization : public IDetailCustomization`  
_L15-41_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `FClothPaintSettingsCustomization() = delete;`
- L20 _public prototype_ `FClothPaintSettingsCustomization(FClothPainter* InPainter);`
- L22 _public prototype_ `virtual ~FClothPaintSettingsCustomization();`
- L24 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(FClothPainter* InPainter);`
- L27 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L32 _private prototype_ `TSharedRef<SWidget> OnGenerateToolComboRow(TSharedPtr<FClothPaintToolBase> InItem);` — Handlers for SCombobox, generation of row widgets, combo text and handling selection change
- L33 _private prototype_ `void OnHandleToolSelection(TSharedPtr<FClothPaintToolBase> InItem, ESelectInfo::Type InSelectInfo, IDetailLayoutBuilder* DetailBuider);`
- L34 _private prototype_ `FText GetToolComboText() const;`
- L37 _private prototype_ `void OnAutoRangeFlagChanged();` — Callback to calculate auto view range values
- L40 _private member_ `FClothPainter* Painter;` — The painter containing the paint settings we are customizing

#### class `FClothPaintBrushSettingsCustomization`  
`class FClothPaintBrushSettingsCustomization : public IDetailCustomization`  
_L44-52_
- inherits: `IDetailCustomization`
- L48 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L51 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Source/Editor/ClothPainter/Private/ClothPaintToolBase.h` (Private)


#### class `FClothPaintToolBase`  
`class FClothPaintToolBase`  
_L14-74_
- desc: Base object for tools used to paint clothing Derive from this and register a new tool in FClothPainter::Init to add to the available tools
- L18 _public prototype_ `FClothPaintToolBase() = delete;`
- L19 _public prototype_ `FClothPaintToolBase(const FClothPaintToolBase& Other) = delete;`
- L21 _public function_ `explicit FClothPaintToolBase(TWeakPtr<FClothPainter> InPainter) : Painter(InPainter)`
- L25 _public prototype_ `virtual ~FClothPaintToolBase() = default;`
- L28 _public function_ `virtual FPerVertexPaintAction GetPaintAction(const FMeshPaintParameters& InPaintParams, UClothPainterSettings* InPainterSettings)` — Used by the painter to request a delegate to call to apply this tool to the current mesh
- L31 _public function_ `virtual bool InputKey(IMeshPaintGeometryAdapter* Adapter, FEditorViewportClient* InViewportClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent)` — Called when the user presses a key when this tool is selected
- L34 _public function_ `virtual bool ShouldRenderInteractors() const` — Whether or not the brush interactor should be drawn
- L37 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Display name for UI purposes
- L40 _public function_ `virtual bool IsPerVertex() const` — Whether this action should be executed once for each vertex in the brush or just once per operation
- L43 _public function_ `virtual void Render(USkeletalMeshComponent* InComponent, IMeshPaintGeometryAdapter* InAdapter, const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)` — Optionally render extra data to the viewport
- L46 _public function_ `virtual void Activate(TWeakPtr<FUICommandList> InCommands)` — Called as tool is selected, can be used to initialize and bind actions
- L49 _public function_ `virtual void Deactivate(TWeakPtr<FUICommandList> InCommands)` — Called as tool is deselected, can be used to shutdown and unbind actions
- L52 _public function_ `virtual void OnMeshChanged()` — Called as a change in the target geometry changes, to clear anything the tool may have cached
- L55 _public function_ `virtual bool HasValueRange()` — If true, the tool must provide the range of values used in GetValueRange, used to modify auto calculated view ranges
- L58 _public function_ `virtual void GetValueRange(float& OutRangeMin, float& OutRangeMax)` — If HasValueRange returns true, this should specify the range of values the tool is currently covering
- L65 _public function_ `virtual UObject* GetSettingsObject()` — Optionally return a UObject that will be displayed in the details panel when the tool is selected. This is intended for settings unique to the tool, common settings (brush size etc) are available from the brush settings in the Painter.
- L68 _public function_ `virtual void RegisterSettingsObjectCustomizations(IDetailsView* InDetailsView)` — Optionally register any applicable customizations for the settings object
- L73 _protected member_ `TWeakPtr<FClothPainter> Painter;` — The painter instance that owns this tool

### `Source/Editor/ClothPainter/Private/ClothPaintToolCommands.h` (Private)


#### class `FClothPaintToolCommands_Gradient`  
`class FClothPaintToolCommands_Gradient : public TCommands<FClothPaintToolCommands_Gradient>`  
_L20-35_
- inherits: `TCommands<FClothPaintToolCommands_Gradient>`
- L24 _public function_ `FClothPaintToolCommands_Gradient() : TCommands<FClothPaintToolCommands_Gradient>(TEXT("ClothPainter"), NSLOCTEXT("Contexts", "ClothFillTool", "Cloth Painter - Fill Tool"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L30 _public prototype_ `virtual void RegisterCommands() override;`
- L31 _public prototype_ `static const FClothPaintToolCommands_Gradient& Get();`
- L34 _public member_ `TSharedPtr<FUICommandInfo> ApplyGradient;` — Applies the gradient when using the gradient cloth paint tool

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace ClothPaintToolCommands`
- L17 _prototype_ `void RegisterClothPaintToolCommands();` (scope `ClothPaintToolCommands`)

### `Source/Editor/ClothPainter/Private/ClothPaintTools.h` (Private)


#### class `UClothPaintTool_BrushSettings`  
`class UClothPaintTool_BrushSettings : public UObject`  
_L35-50_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Unique settings for the Brush tool
- L41 _public function_ `UClothPaintTool_BrushSettings() : PaintValue(100.0f)`
- L49 _public member_ `float PaintValue;` — `UPROPERTY(EditAnywhere, Category = ToolSettings, meta=(UIMin=0, UIMax=100, ClampMin=0, ClampMax=100000))` — Value to paint onto the mesh for this parameter

#### class `FClothPaintTool_Brush`  
`class FClothPaintTool_Brush : public FClothPaintToolBase`  
_L54-83_
- inherits: `FClothPaintToolBase`
- desc: Standard brush tool for painting onto the mesh
- L58 _public function_ `FClothPaintTool_Brush(TWeakPtr<FClothPainter> InPainter) : FClothPaintToolBase(InPainter) , Settings(nullptr)`
- L65 _public prototype_ `virtual ~FClothPaintTool_Brush();`
- L68 _public prototype_ `virtual FText GetDisplayName() const override;` — FClothPaintToolBase interface
- L69 _public prototype_ `virtual FPerVertexPaintAction GetPaintAction(const FMeshPaintParameters& InPaintParams, UClothPainterSettings* InPainterSettings) override;`
- L70 _public prototype_ `virtual UObject* GetSettingsObject() override;`
- L71 _public prototype_ `virtual bool HasValueRange() override;`
- L72 _public prototype_ `virtual void GetValueRange(float& OutRangeMin, float& OutRangeMax) override;`
- L78 _protected member_ `UClothPaintTool_BrushSettings* Settings;` — The settings object shown in the details panel
- L81 _protected prototype_ `void PaintAction(FPerVertexPaintActionArgs& InArgs, int32 VertexIndex, FMatrix InverseBrushMatrix);` — Called when the paint action is applied

#### class `UClothPaintTool_GradientSettings`  
`class UClothPaintTool_GradientSettings : public UObject`  
_L87-113_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Unique settings for the Gradient tool
- L94 _public function_ `UClothPaintTool_GradientSettings() : GradientStartValue(0.0f) , GradientEndValue(100.0f) , bUseRegularBrush(false)`
- L104 _public member_ `float GradientStartValue;` — `UPROPERTY(EditAnywhere, Category = ToolSettings, meta=(UIMin=0, UIMax=100, ClampMin=0, ClampMax=100000))` — Value of the gradient at the start points
- L108 _public member_ `float GradientEndValue;` — `UPROPERTY(EditAnywhere, Category = ToolSettings, meta=(UIMin=0, UIMax=100, ClampMin=0, ClampMax=100000))` — Value of the gradient at the end points
- L112 _public member_ `bool bUseRegularBrush;` — `UPROPERTY(EditAnywhere, Category = ToolSettings)` — Enables the painting of selected points using a brush rather than just a point

#### class `FClothPaintTool_Gradient`  
`class FClothPaintTool_Gradient : public FClothPaintToolBase`  
_L120-172_
- inherits: `FClothPaintToolBase`
- desc: Gradient tool - Allows the user to select begin and end points to apply a gradient to. Pressing Enter will move from selecting begin points, to selecting end points and finally applying the operation to the mesh
- L124 _public function_ `FClothPaintTool_Gradient(TWeakPtr<FClothPainter> InPainter) : FClothPaintToolBase(InPainter) , bSelectingBeginPoints(true) , Settings(nullptr)`
- L132 _public prototype_ `virtual ~FClothPaintTool_Gradient();`
- L135 _public prototype_ `virtual FText GetDisplayName() const override;` — FClothPaintToolBase interface
- L136 _public prototype_ `virtual bool InputKey(IMeshPaintGeometryAdapter* Adapter, FEditorViewportClient* InViewportClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent) override;`
- L137 _public prototype_ `virtual FPerVertexPaintAction GetPaintAction(const FMeshPaintParameters& InPaintParams, UClothPainterSettings* InPainterSettings) override;`
- L138 _public prototype_ `virtual bool IsPerVertex() const override;`
- L139 _public prototype_ `virtual void Render(USkeletalMeshComponent* InComponent, IMeshPaintGeometryAdapter* InAdapter, const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L140 _public prototype_ `virtual bool ShouldRenderInteractors() const override;`
- L141 _public prototype_ `virtual UObject* GetSettingsObject() override;`
- L142 _public prototype_ `virtual void Activate(TWeakPtr<FUICommandList> InCommands) override;`
- L143 _public prototype_ `virtual void Deactivate(TWeakPtr<FUICommandList> InCommands) override;`
- L144 _public prototype_ `virtual void OnMeshChanged() override;`
- L145 _public prototype_ `virtual bool HasValueRange() override;`
- L146 _public prototype_ `virtual void GetValueRange(float& OutRangeMin, float& OutRangeMax) override;`
- L152 _protected member_ `bool bSelectingBeginPoints;` — Whether we're selecting the start points or end points
- L155 _protected member_ `TArray<int32> GradientStartIndices;` — List of vert indices to consider the start of the gradient
- L158 _protected member_ `TArray<int32> GradientEndIndices;` — List of vert indices to consider the end of the gradient
- L161 _protected member_ `UClothPaintTool_GradientSettings* Settings;` — The settings object shown in the details panel
- L164 _protected prototype_ `void PaintAction(FPerVertexPaintActionArgs& InArgs, int32 VertexIndex, FMatrix InverseBrushMatrix);` — Called when the paint action is applied
- L167 _protected prototype_ `void ApplyGradient();` — Applies the gradient to the currently selected points
- L170 _protected prototype_ `bool CanApplyGradient();` — Whether we can currently apply a gradient

#### class `UClothPaintTool_SmoothSettings`  
`class UClothPaintTool_SmoothSettings : public UObject`  
_L176-191_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Unique settings for the smoothing tool
- L182 _public function_ `UClothPaintTool_SmoothSettings() : Strength(0.2f)`
- L190 _public member_ `float Strength;` — `UPROPERTY(EditAnywhere, Category = ToolSettings, meta=(UIMin="0.0", UIMax="1.0", ClampMin="0.0", ClampMax="1.0"))` — Strength of the smoothing effect

#### class `FClothPaintTool_Smooth`  
`class FClothPaintTool_Smooth : public FClothPaintToolBase`  
_L197-224_
- inherits: `FClothPaintToolBase`
- desc: Smoothing tool, applies a blur similar to a box blur (even distribution of neighbors) Modulated by strength from settings object
- L201 _public function_ `FClothPaintTool_Smooth(TWeakPtr<FClothPainter> InPainter) : FClothPaintToolBase(InPainter) , Settings(nullptr)`
- L208 _public prototype_ `virtual ~FClothPaintTool_Smooth();`
- L210 _public prototype_ `virtual FPerVertexPaintAction GetPaintAction(const FMeshPaintParameters& InPaintParams, UClothPainterSettings* InPainterSettings) override;`
- L211 _public prototype_ `virtual FText GetDisplayName() const override;`
- L212 _public prototype_ `virtual UObject* GetSettingsObject() override;`
- L213 _public prototype_ `virtual void RegisterSettingsObjectCustomizations(IDetailsView* InDetailsView) override;`
- L214 _public prototype_ `virtual bool IsPerVertex() const override;`
- L217 _public prototype_ `void SmoothVertices(const TSet<int32> &InfluencedVertices, TSharedPtr<FClothPainter> SharedPainter);` — Given a set of vertex indices, apply the smooth operation over the set
- L221 _protected prototype_ `void PaintAction(FPerVertexPaintActionArgs& InArgs, int32 VertexIndex, FMatrix InverseBrushMatrix);`
- L223 _protected member_ `UClothPaintTool_SmoothSettings* Settings;`

#### class `UClothPaintTool_FillSettings`  
`class UClothPaintTool_FillSettings : public UObject`  
_L228-244_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Unique settings for the fill tool
- L233 _public function_ `UClothPaintTool_FillSettings() : Threshold(0.0f), FillValue(100.0f)`
- L239 _public member_ `float Threshold;` — `UPROPERTY(EditAnywhere, Category = ToolSettings, meta = (UIMin = 0, UIMax = 100, ClampMin = 0, ClampMax = 100000))` — Threshold for fill operation, will keep filling until sampled verts aren't within this range of the original vertex
- L243 _public member_ `float FillValue;` — `UPROPERTY(EditAnywhere, Category = ToolSettings, meta = (UIMin = 0, UIMax = 100, ClampMin = 0, ClampMax = 100000))` — The value to fill all selected verts to

#### class `FClothPaintTool_Fill`  
`class FClothPaintTool_Fill : public FClothPaintToolBase`  
_L249-284_
- inherits: `FClothPaintToolBase`
- desc: Basic fill tool with thresholding for changing the parameter values for a large area of similar cloth
- L253 _public function_ `FClothPaintTool_Fill(TWeakPtr<FClothPainter> InPainter) : FClothPaintToolBase(InPainter) , Settings(nullptr) , QueryRadius(20.0f)`
- L261 _public prototype_ `virtual ~FClothPaintTool_Fill();`
- L264 _public prototype_ `virtual FPerVertexPaintAction GetPaintAction(const FMeshPaintParameters& InPaintParams, UClothPainterSettings* InPainterSettings) override;` — FClothPaintToolBase interface
- L265 _public prototype_ `virtual FText GetDisplayName() const override;`
- L266 _public prototype_ `virtual UObject* GetSettingsObject() override;`
- L267 _public prototype_ `virtual bool IsPerVertex() const override;`
- L268 _public prototype_ `virtual bool ShouldRenderInteractors() const override;`
- L269 _public prototype_ `virtual void Render(USkeletalMeshComponent* InComponent, IMeshPaintGeometryAdapter* InAdapter, const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L270 _public prototype_ `virtual bool HasValueRange() override;`
- L271 _public prototype_ `virtual void GetValueRange(float& OutRangeMin, float& OutRangeMax) override;`
- L277 _protected prototype_ `void PaintAction(FPerVertexPaintActionArgs& InArgs, int32 VertexIndex, FMatrix InverseBrushMatrix);` — Called to apply the fill action
- L280 _protected member_ `UClothPaintTool_FillSettings* Settings;` — Settings for the paint operation
- L283 _protected member_ `float QueryRadius;` — Radius to query for points (will choose nearest point in this set)

### `Source/Editor/ClothPainter/Private/ClothPainter.h` (Private)


#### class `FClothPainter`  
`class FClothPainter : public IMeshPainter, public TSharedFromThis<FClothPainter>`  
_L39-154_
- inherits: `IMeshPainter,TSharedFromThis<FClothPainter>`
- L43 _public prototype_ `FClothPainter();`
- L44 _public prototype_ `~FClothPainter();`
- L46 _public prototype_ `void Init();`
- L50 _protected prototype_ `virtual bool PaintInternal(const FVector& InCameraOrigin, const TArrayView<TPair<FVector, FVector>>& Rays, EMeshPaintAction PaintAction, float PaintStrength) override;`
- L55 _public prototype_ `void EnterPaintMode();` — Mode transition, called by the paint mode as painting is enabled and disabled
- L56 _public prototype_ `void ExitPaintMode();`
- L59 _public prototype_ `void RecalculateAutoViewRange();` — Called to update the auto view min/max values
- L62 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;` — IMeshPainter interface
- L63 _public prototype_ `virtual void FinishPainting() override;`
- L64 _public function_ `virtual void ActorSelected(AActor* Actor) override`
- L65 _public function_ `virtual void ActorDeselected(AActor* Actor) override`
- L66 _public prototype_ `virtual void Reset() override;`
- L67 _public prototype_ `virtual TSharedPtr<IMeshPaintGeometryAdapter> GetMeshAdapterForComponent(const UMeshComponent* Component) override;`
- L68 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L69 _public prototype_ `virtual UPaintBrushSettings* GetBrushSettings() override;`
- L70 _public prototype_ `virtual UMeshPaintSettings* GetPainterSettings() override;`
- L71 _public prototype_ `virtual TSharedPtr<class SWidget> GetWidget() override;`
- L72 _public prototype_ `virtual const FHitResult GetHitResult(const FVector& Origin, const FVector& Direction) override;`
- L73 _public prototype_ `virtual void Refresh() override;`
- L74 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L75 _public prototype_ `virtual bool InputKey(FEditorViewportClient* InViewportClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent) override;`
- L79 _public prototype_ `void SetSkeletalMeshComponent(UDebugSkelMeshComponent* SkeletalMeshComponent);` — Sets the debug skeletal mesh to which we should currently paint
- L82 _public prototype_ `USkeletalMesh* GetSkeletalMesh() const;` — Gets the skeletal mesh of the current skeletal mesh component
- L85 _public prototype_ `FMeshPaintParameters CreatePaintParameters(const struct FHitResult& HitResult, const FVector& InCameraOrigin, const FVector& InRayOrigin, const FVector& InRayDirection, float PaintStrength);` — Creates paint parameters for the current setup
- L88 _public prototype_ `float GetPropertyValue(int32 VertexIndex);` — Retrieves the property value from the Cloth asset for the given EPaintableClothProperty
- L90 _public prototype_ `void SetPropertyValue(int32 VertexIndex, const float Value);` — Sets the EPaintableClothProperty property within the Clothing asset to Value
- L93 _public function_ `void SetIsPainting(bool bInPainting)` — Some complex clothing tools (gradients) require the ability to override these flags in different ways
- L96 _public function_ `const TSharedPtr<FClothPaintToolBase> GetSelectedTool() const` — Get the selected paint tool
- L99 _public function_ `TSharedPtr<IMeshPaintGeometryAdapter> GetAdapter() const` — Gets the current geometry adapter
- L102 _public prototype_ `void OnAssetSelectionChanged(UClothingAssetCommon* InNewSelectedAsset, int32 InAssetLod, int32 MaskIndex);` — When a different clothing asset is selected in the UI the painter should refresh the adapter
- L103 _public function_ `void OnAssetMaskSelectionChanged()`
- L107 _public function_ `FText GetViewportText() const` — Returns custom text to display in the skeletal mesh editor viewport
- L112 _protected prototype_ `void RefreshClothingAssets();` — Rebuild the list of editable clothing assets from the current mesh
- L115 _protected prototype_ `FPerVertexPaintAction GetPaintAction(const FMeshPaintParameters& InPaintParams);` — Get the action defined by the selected tool that we should run when we paint
- L121 _protected prototype_ `void SetTool(TSharedPtr<FClothPaintToolBase> InTool);` — Sets the currently selected paint tool NOTE: InTool *must* have been registered by adding it to the Tools array
- L124 _protected member_ `TSharedPtr<IMeshPaintGeometryAdapter> Adapter;` — Current adapter used to paint the clothing properties
- L126 _protected member_ `TObjectPtr<UDebugSkelMeshComponent> SkeletalMeshComponent;` — Debug skeletal mesh to which painting should be applied
- L128 _protected member_ `TSharedPtr<SClothPaintWidget> Widget;` — Widget used to represent the state/functionality of the painter
- L130 _protected member_ `TObjectPtr<UClothPainterSettings> PaintSettings;` — Cloth paint settings instance
- L132 _protected member_ `TObjectPtr<UPaintBrushSettings> BrushSettings;` — Cloth brush settings instance
- L135 _protected member_ `bool bShouldSimulate;` — Flag whether or not the simulation should run
- L137 _protected member_ `bool bShowHiddenVerts;` — Flag to render (hidden) sim verts during gradient painting
- L140 _protected member_ `TSharedPtr<FClothPaintToolBase> SelectedTool;` — The currently selected painting tool
- L143 _protected member_ `TArray<TSharedPtr<FClothPaintToolBase>> Tools;` — List of currently registered paint tools
- L146 _protected member_ `TSharedPtr<FUICommandList> CommandList;` — List of commands for the painter, tools can bind to this in activate
- L148 _protected member_ `FText CachedHoveredClothValueText;`
- L150 _protected member_ `FDelegateHandle HoveredTextCallbackHandle;`

### `Source/Editor/ClothPainter/Private/ClothPainterCommands.h` (Private)


#### class `FClothPainterCommands`  
`class FClothPainterCommands : public TCommands<FClothPainterCommands>`  
_L15-29_
- inherits: `TCommands<FClothPainterCommands>`
- L18 _public function_ `FClothPainterCommands() : TCommands<FClothPainterCommands>(TEXT("ClothPainterTools"), NSLOCTEXT("Contexts", "ClothPainter", "Cloth Painter"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L24 _public prototype_ `virtual void RegisterCommands() override;`
- L25 _public prototype_ `static const FClothPainterCommands& Get();`
- L28 _public member_ `TSharedPtr<FUICommandInfo> TogglePaintMode;` — Clothing commands

### `Source/Editor/ClothPainter/Private/ClothingAssetListCommands.h` (Private)


#### class `FClothingAssetListCommands`  
`class FClothingAssetListCommands : public TCommands<FClothingAssetListCommands>`  
_L16-33_
- inherits: `TCommands<FClothingAssetListCommands>`
- L19 _public function_ `FClothingAssetListCommands() : TCommands<FClothingAssetListCommands>( TEXT("ClothAssetList"), NSLOCTEXT("Contexts", "ClothAssetList", "Clothing Asset List"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L27 _public prototype_ `virtual void RegisterCommands() override;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> DeleteAsset;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> DeleteAssetLastLod;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> RebuildAssetParams;`
- L32 _public member_ `TMap<FName, TSharedPtr<FUICommandInfo>> ExportAssets;`

### `Source/Editor/ClothPainter/Private/ClothingPaintEditMode.h` (Private)


#### class `FClothingPaintEditMode`  
`class FClothingPaintEditMode : public IMeshPaintEdMode`  
_L12-35_
- inherits: `IMeshPaintEdMode`
- L15 _public prototype_ `FClothingPaintEditMode();`
- L16 _public prototype_ `virtual ~FClothingPaintEditMode();`
- L18 _public prototype_ `virtual void Initialize() override;`
- L19 _public function_ `virtual bool UsesToolkits() const override`
- L20 _public prototype_ `virtual TSharedPtr<class FModeToolkit> GetToolkit() override;`
- L22 _public prototype_ `void SetPersonaToolKit(class TSharedPtr<IPersonaToolkit> InToolkit);`
- L23 _public prototype_ `void SetupClothPaintTab(TSharedPtr<SClothPaintTab> InClothPaintTab);`
- L25 _public prototype_ `virtual void Enter() override;`
- L26 _public prototype_ `virtual void Exit() override;`
- L30 _protected member_ `TSharedPtr<FClothPainter> ClothPainter;`
- L32 _protected prototype_ `class IPersonaPreviewScene* GetAnimPreviewScene() const;`
- L33 _protected member_ `class TWeakPtr<IPersonaToolkit> PersonaToolkit;`
- L34 _protected member_ `TWeakPtr<SClothPaintTab> ClothPaintTab;`

### `Source/Editor/ClothPainter/Private/SClothAssetSelector.h` (Private)


#### struct `FClothingAssetListItem`  
`struct FClothingAssetListItem`  
_L40-43_
- L42 _public member_ `TWeakObjectPtr<UClothingAssetBase> ClothingAsset;`

#### struct `FClothingMaskListItem`  
`struct FClothingMaskListItem`  
_L45-59_
- L47 _public function_ `FClothingMaskListItem() : LodIndex(INDEX_NONE) , MaskIndex(INDEX_NONE)`
- L52 _public prototype_ `FPointWeightMap* GetMask();`
- L53 _public prototype_ `FClothPhysicalMeshData* GetMeshData();`
- L54 _public prototype_ `USkeletalMesh* GetOwningMesh();`
- L56 _public member_ `TWeakObjectPtr<UClothingAssetCommon> ClothingAsset;`
- L57 _public member_ `int32 LodIndex;`
- L58 _public member_ `int32 MaskIndex;`

#### class `SClothAssetSelector`  
`class SClothAssetSelector : public SCompoundWidget, public FEditorUndoClient`  
_L66-161_
- inherits: `SCompoundWidget,FEditorUndoClient`
- L70 _public function_ `SLATE_BEGIN_ARGS(SClothAssetSelector)`
- L71 _public prototype_ `SLATE_EVENT(FOnClothAssetSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() ~SClothAssetSelector();`
- L76 _public prototype_ `void Construct(const FArguments& InArgs, USkeletalMesh* InMesh);`
- L78 _public prototype_ `TWeakObjectPtr<UClothingAssetBase> GetSelectedAsset() const;`
- L79 _public prototype_ `int32 GetSelectedLod() const;`
- L80 _public prototype_ `int32 GetSelectedMask() const;`
- L83 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface
- L84 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L90 _protected prototype_ `void OnCopyClothingAssetSelected(const FAssetData& AssetData);` — Copies clothing setup from source SkelMesh
- L93 _protected prototype_ `TSharedRef<SWidget> OnGenerateSkeletalMeshPickerForClothCopy();` — Generate a drop-down for choosing the source skeletal mesh for copying cloth assets
- L95 _protected prototype_ `EVisibility GetAssetHeaderButtonTextVisibility() const;`
- L96 _protected prototype_ `EVisibility GetMaskHeaderButtonTextVisibility() const;`
- L98 _protected prototype_ `TSharedRef<SWidget> OnGetLodMenu();`
- L99 _protected prototype_ `FText GetLodButtonText() const;`
- L101 _protected prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForClothingAssetItem(TSharedPtr<FClothingAssetListItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L102 _protected prototype_ `void OnAssetListSelectionChanged(TSharedPtr<FClothingAssetListItem> InSelectedItem, ESelectInfo::Type InSelectInfo);`
- L104 _protected prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForMaskItem(TSharedPtr<FClothingMaskListItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L105 _protected prototype_ `void OnMaskSelectionChanged(TSharedPtr<FClothingMaskListItem> InSelectedItem, ESelectInfo::Type InSelectInfo);`
- L108 _protected prototype_ `FReply AddNewMask();` — Mask manipulation
- L109 _protected prototype_ `bool CanAddNewMask() const;`
- L111 _protected prototype_ `void OnRefresh();`
- L113 _protected prototype_ `void RefreshAssetList();`
- L114 _protected prototype_ `void RefreshMaskList();`
- L116 _protected prototype_ `TOptional<float> GetCurrentKernelRadius() const;`
- L117 _protected prototype_ `void OnCurrentKernelRadiusChanged(float InValue);`
- L118 _protected prototype_ `void OnCurrentKernelRadiusCommitted(float InValue, ETextCommit::Type CommitType);`
- L119 _protected prototype_ `bool CurrentKernelRadiusIsEnabled() const;`
- L121 _protected prototype_ `ECheckBoxState GetCurrentUseMultipleInfluences() const;`
- L122 _protected prototype_ `void OnCurrentUseMultipleInfluencesChanged(ECheckBoxState InValue);`
- L124 _protected prototype_ `ECheckBoxState GetCurrentSmoothTransition() const;`
- L125 _protected prototype_ `void OnCurrentSmoothTransitionChanged(ECheckBoxState InValue);`
- L127 _protected prototype_ `bool IsValidClothLodSelected() const;`
- L129 _protected prototype_ `void OnClothingLodSelected(int32 InNewLod);`
- L132 _protected prototype_ `void SetSelectedAsset(TWeakObjectPtr<UClothingAssetBase> InSelectedAsset);` — Setters for the list selections so we can handle list selections changing properly
- L133 _protected prototype_ `void SetSelectedLod(int32 InLodIndex, bool bRefreshMasks = true);`
- L134 _protected prototype_ `void SetSelectedMask(int32 InMaskIndex);`
- L136 _protected member_ `USkeletalMesh* Mesh;`
- L138 _protected member_ `TSharedPtr<SButton> NewMaskButton;`
- L139 _protected member_ `TSharedPtr<SAssetList> AssetList;`
- L140 _protected member_ `TSharedPtr<SMaskList> MaskList;`
- L142 _protected member_ `TSharedPtr<SHorizontalBox> AssetHeaderBox;`
- L143 _protected member_ `TSharedPtr<SHorizontalBox> MaskHeaderBox;`
- L145 _protected member_ `TArray<TSharedPtr<FClothingAssetListItem>> AssetListItems;`
- L146 _protected member_ `TArray<TSharedPtr<FClothingMaskListItem>> MaskListItems;`
- L149 _protected member_ `TWeakObjectPtr<UClothingAssetBase> SelectedAsset;` — Currently selected clothing asset, Lod Index and Mask index
- L150 _protected member_ `int32 SelectedLod;`
- L151 _protected member_ `int32 SelectedMask;`
- L153 _protected member_ `FOnClothAssetSelectionChanged OnSelectionChanged;`
- L156 _protected member_ `FDelegateHandle MeshClothingChangedHandle;` — Handle for mesh event callback when clothing changes.
- L159 _private prototype_ `bool CanSelectLod() const;`
- L160 _private prototype_ `bool CanEditDeformer() const;`

#### Free symbols / members of external scopes

- L61 _typedef_ `typedef SListView<TSharedPtr<FClothingAssetListItem>> SAssetList;`
- L62 _typedef_ `typedef SListView<TSharedPtr<FClothingMaskListItem>> SMaskList;`
- L64 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnClothAssetSelectionChanged, TWeakObjectPtr<UClothingAssetBase>, int32, int32);`
- L64 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnClothAssetSelectionChanged, TWeakObjectPtr<UClothingAssetBase>, int32, int32);`

### `Source/Editor/ClothPainter/Private/SClothPaintTab.h` (Private)


#### class `SClothPaintTab`  
`class SClothPaintTab : public SCompoundWidget`  
_L22-61_
- inherits: `SCompoundWidget`
- L25 _public function_ `SLATE_BEGIN_ARGS(SClothPaintTab)`
- L27 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<class FAssetEditorToolkit>, InHostingApp) SLATE_END_ARGS() SClothPaintTab();`
- L31 _public prototype_ `~SClothPaintTab();`
- L34 _public prototype_ `void Construct(const FArguments& InArgs);` — SWidget functions
- L35 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L38 _public prototype_ `void EnterPaintMode();` — Setup and teardown the cloth paint UI
- L39 _public prototype_ `void ExitPaintMode();`
- L44 _protected prototype_ `void OnAssetSelectionChanged(TWeakObjectPtr<UClothingAssetBase> InAssetPtr, int32 InLodIndex, int32 InMaskIndex);` — Called from the selector when the asset selection changes (Asset, LOD, Mask)
- L47 _protected prototype_ `bool IsAssetDetailsPanelEnabled();` — Whether or not the asset config section is enabled for editing
- L50 _protected prototype_ `ISkeletalMeshEditor* GetSkeletalMeshEditor() const;` — Helpers for getting editor objects
- L51 _protected prototype_ `TSharedRef<IPersonaToolkit> GetPersonaToolkit() const;`
- L53 _protected member_ `TWeakPtr<class FAssetEditorToolkit> HostingApp;`
- L55 _protected member_ `TSharedPtr<SClothAssetSelector> SelectorWidget;`
- L56 _protected member_ `TSharedPtr<SClothPaintWidget> ModeWidget;`
- L57 _protected member_ `TSharedPtr<SScrollBox> ContentBox;`
- L58 _protected member_ `TSharedPtr<IDetailsView> DetailsView;`
- L60 _protected member_ `bool bModeApplied;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CLOTHPAINTER_API`

### `Source/Editor/ClothPainter/Private/SClothPaintWidget.h` (Private)


#### class `SClothPaintWidget`  
`class SClothPaintWidget : public SCompoundWidget`  
_L15-43_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SClothPaintWidget)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FClothPainter* InPainter);`
- L22 _public prototype_ `void CreateDetailsView(FClothPainter* InPainter);`
- L25 _public prototype_ `void OnRefresh();` — Refresh the widget such as when entering the paint mode
- L28 _public prototype_ `void Reset();` — Resets the selections and puts the widget back to starting state
- L33 _protected member_ `TSharedPtr<IDetailsView> DetailsView;` — Details view placed below asset selection
- L36 _protected member_ `TArray<UObject*> Objects;` — Objects observed in the details view
- L39 _protected member_ `FClothPainter* Painter;` — The painter instance this widget is using
- L42 _protected member_ `UClothPainterSettings* ClothPainterSettings;` — Settings for the painter instance

### `Source/Editor/ClothPainter/Private/SCopyVertexColorSettingsPanel.h` (Private)


#### class `SCopyVertexColorSettingsPanel`  
`class SCopyVertexColorSettingsPanel : public SCompoundWidget`  
_L17-40_
- inherits: `SCompoundWidget`
- desc: Widget used for copying vertex colors from sim mesh to a selected mask.
- L20 _public function_ `SLATE_BEGIN_ARGS(SCopyVertexColorSettingsPanel)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UClothingAssetCommon* InAsset, int32 InLOD, FPointWeightMap* InMask);`
- L29 _private member_ `FCopyVertexColorToClothParams CopyParams;` — Params struct, displayed using details panel
- L32 _private prototype_ `FReply OnCopyClicked();` — Handle 'Copy' button being clicked
- L35 _private member_ `TWeakObjectPtr<UClothingAssetCommon> SelectedAssetPtr;` — Pointer to currently selected ClothingAsset
- L37 _private member_ `FPointWeightMap* SelectedMask;` — Pointer to selected mask
- L39 _private member_ `int32 SelectedLOD;` — Currently selected LOD

### `Source/Editor/ClothPainter/Public/ClothPaintingModule.h` (Public)


#### class `FClothPaintingModule`  
`class FClothPaintingModule : public IModuleInterface`  
_L22-68_
- inherits: `IModuleInterface`
- L25 _public prototype_ `virtual void StartupModule() override;`
- L26 _public prototype_ `virtual void ShutdownModule() override;`
- L29 _public prototype_ `void SetupMode();` — Setup and register our editmode
- L32 _public prototype_ `void ShutdownMode();` — Unregister and shut down our edit mode
- L37 _protected prototype_ `TSharedRef<FApplicationMode> ExtendApplicationMode(const FName ModeName, TSharedRef<FApplicationMode> InMode);` — Extends the skeletal mesh editor mode
- L40 _protected member_ `TArray<TWeakPtr<FApplicationMode>> RegisteredApplicationModes;`
- L41 _protected member_ `FWorkflowApplicationModeExtender Extender;`
- L46 _private prototype_ `void RegisterMenus();` — Extend toolbars and menus
- L49 _private prototype_ `TSharedRef<FExtender> ExtendSkelMeshEditorToolbar(const TSharedRef<FUICommandList> InCommandList, TSharedRef<ISkeletalMeshEditor> InSkeletalMeshEditor);` — Extends a skeletal mesh editor instance toolbar
- L52 _private member_ `FDelegateHandle SkelMeshEditorExtenderHandle;` — Handle for the extender delegate we created
- L55 _private prototype_ `FText GetPaintToolsButtonText(TWeakPtr<ISkeletalMeshEditor> InSkeletalMeshEditor) const;` — Gets text for the enable paint tools button
- L58 _private prototype_ `FText GetPaintToolsButtonToolTip(TWeakPtr<ISkeletalMeshEditor> InSkeletalMeshEditor) const;` — Gets tool tip for the enable paint tools button
- L61 _private prototype_ `void OnToggleMode(TWeakPtr<ISkeletalMeshEditor> InSkeletalMeshEditor) const;` — Toggles paint mode on the clothing tab
- L64 _private prototype_ `bool IsPaintModeActive(TWeakPtr<ISkeletalMeshEditor> InSkeletalMeshEditor) const;` — Return true if currently in paint mode
- L67 _private prototype_ `TSharedPtr<SClothPaintTab> GetActiveClothTab(TWeakPtr<ISkeletalMeshEditor> InSkeletalMeshEditor, bool bInvoke = true) const;` — Gets the current active clothing tab, will invoke (spawn or draw attention to) if bInvoke == true

#### Free symbols / members of external scopes

- L20 _externvar_ `extern const FName PaintModeID;`

### `Source/Editor/ClothPainter/Public/ClothingAssetExporter.h` (Public)


#### class `IClothingAssetExporterClassProvider`  
`class IClothingAssetExporterClassProvider : public IModularFeature`  
_L22-28_
- inherits: `IModularFeature`
- desc: A modular interface to provide ways to export clothing assets.
- L25 _public member_ `inline static const FName FeatureName = TEXT("Clo`
- L27 _public prototype_ `virtual TSubclassOf<UClothingAssetExporter> GetClothingAssetExporterClass() const = 0;`

#### class `UClothingAssetExporter`  
`class UClothingAssetExporter : public UObject`  
_L32-48_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Modular exporter base class.
- L38 _public prototype_ `virtual UClass* GetExportedType() const PURE_VIRTUAL(UClothingAssetExporter::GetExportedType, return nullptr;);` — Return the class of the exported asset type.
- L46 _public prototype_ `virtual void Export(const UClothingAssetBase* ClothingAsset, UObject* ExportedAsset) PURE_VIRTUAL(UClothingAssetExporter::Export,);` — Export the specified asset. \param ClothingAsset the source clothing asset to be exported. \param ExportedAsset the destination asset object in the exported type provided by the caller, ready to be filled by the Export function.

#### Free symbols / members of external scopes

- L54 _prototype_ `void ForEachClothingAssetExporter(TFunctionRef<void(UClass*)> Function);` — Call the specified function for each asset exporter plugin currently loaded, passing the target exported type as a parameter. \param Function the function to call for each asset exporter found.
- L61 _prototype_ `void ExportClothingAsset(const UClothingAssetBase* ClothingAsset, UClass* ExportedType);` — Open a dialog and create a new asset of the specified type, then call the associated export function on it. \param ClothingAsset the asset to export. \param ExportedType the exported type.

### `Source/Editor/ClothPainter/Public/CopyVertexColorToClothParams.h` (Public)


#### enum `ESourceColorChannel`  
`enum class ESourceColorChannel : uint8`  
_L11-17_
- reflection: `UENUM()`
- desc: Enum for selecting color channel to copy
- L13 _public enumerator_ `Red`
- L14 _public enumerator_ `Green`
- L15 _public enumerator_ `Blue`
- L16 _public enumerator_ `Alpha`

#### struct `FCopyVertexColorToClothParams`  
`struct FCopyVertexColorToClothParams`  
_L21-37_
- reflection: `USTRUCT()`
- desc: Helper struct used for specifying options when copying vertex colors
- L25 _public function_ `FCopyVertexColorToClothParams() : ColorChannel(ESourceColorChannel::Red) , ScalingFactor(1.f)`
- L32 _public member_ `ESourceColorChannel ColorChannel;` — `UPROPERTY(EditAnywhere, Category="Copy Vertex Colors")` — Color channel to copy from vertex colors.
- L36 _public member_ `float ScalingFactor;` — `UPROPERTY(EditAnywhere, Category = "Copy Vertex Colors")` — Scaling factor applied to vertex colours (in range 0-1) before applying to mask.
