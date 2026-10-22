# Plugins / TextureAlignMode

- module root: `Plugins/Editor/GeometryMode/Source/TextureAlignMode`
- headers: 2; symbols: 31
- symbol kinds: class=4, function=3, member=5, prototype=19
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, GeometryMode, SlateCore, UnrealEd

### `Plugins/Editor/GeometryMode/Source/TextureAlignMode/Public/TextureAlignEdMode.h` (Public)


#### class `FTextureAlignModeModule`  
`class FTextureAlignModeModule : public IModuleInterface`  
_L17-30_
- inherits: `IModuleInterface`
- desc: Texture mode module
- L20 _private member_ `TSharedPtr<class FEdModeTexture> EdModeTexture;`
- L25 _public prototype_ `virtual void StartupModule() override;` — Called right after the module's DLL has been loaded and the module object has been created
- L30 _public prototype_ `virtual void ShutdownModule() override;` — Called before the module is unloaded, right before the module object is destroyed.

#### class `FEdModeTexture`  
`class FEdModeTexture : public FEdMode`  
_L35-61_
- inherits: `FEdMode`
- desc: Allows texture alignment on BSP surfaces via the widget.
- L38 _public prototype_ `FEdModeTexture();`
- L39 _public prototype_ `virtual ~FEdModeTexture();`
- L42 _public member_ `ECoordSystem SaveCoordSystem;` — Stores the coordinate system that was active when the mode was entered so it can restore it later.
- L44 _public prototype_ `virtual void Enter() override;`
- L45 _public prototype_ `virtual void Exit() override;`
- L46 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L47 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L48 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem( FMatrix& InMatrix, void* InData ) override;`
- L49 _public prototype_ `virtual bool GetCustomInputCoordinateSystem( FMatrix& InMatrix, void* InData ) override;`
- L50 _public prototype_ `virtual EAxisList::Type GetWidgetAxisToDraw( UE::Widget::EWidgetMode InWidgetMode ) const override;`
- L51 _public prototype_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L52 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L53 _public function_ `virtual bool AllowWidgetMove() override`
- L54 _public prototype_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override;`
- L58 _protected member_ `FScopedTransaction* ScopedTransaction;` — The current transaction.
- L60 _protected member_ `UWorld* TrackingWorld;` — The world that brush that we started tracking with belongs to. Cleared when tracking ends.

#### class `FModeTool_Texture`  
`class FModeTool_Texture : public FModeTool`  
_L66-79_
- inherits: `FModeTool`
- desc: FModeTool_Texture
- L69 _public prototype_ `FModeTool_Texture();`
- L71 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient,FViewport* InViewport,FVector& InDrag,FRotator& InRot,FVector& InScale);`
- L74 _public function_ `virtual bool StartModify()` — override these to allow this tool to keep track of the users dragging during a single drag event
- L75 _public function_ `virtual bool EndModify()`
- L78 _private member_ `FVector PreviousInputDrag;`

### `Plugins/Editor/GeometryMode/Source/TextureAlignMode/Public/TextureAlignMode.h` (Public)


#### class `FTextureAlignMode`  
`class FTextureAlignMode : public FModeToolkit`  
_L10-20_
- inherits: `FModeToolkit`
- desc: Mode Toolkit for the Texture Align Tools
- L14 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L15 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L16 _public prototype_ `virtual class FEdMode* GetEditorMode() const override;`
