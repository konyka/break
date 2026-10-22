# Editor / CurveAssetEditor

- module root: `Source/Editor/CurveAssetEditor`
- headers: 4; symbols: 36
- symbol kinds: class=4, function=4, member=8, prototype=20
- DynamicallyLoadedModuleNames: WorkspaceMenuStructure
- PrivateDependencyModuleNames: Core, CoreUObject, CurveEditor, EditorFramework, Engine, InputCore, Slate, SlateCore, TimeManagement, UnrealEd
- PublicIncludePathModuleNames: LevelEditor, WorkspaceMenuStructure

### `Source/Editor/CurveAssetEditor/Private/CurveAssetEditor.h` (Private)


#### class `FCurveAssetEditor`  
`class FCurveAssetEditor : public ICurveAssetEditor`  
_L22-78_
- inherits: `ICurveAssetEditor`
- L26 _public function_ `FCurveAssetEditor()`
- L29 _public prototype_ `virtual ~FCurveAssetEditor() = default;`
- L31 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L32 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L41 _public prototype_ `void InitCurveAssetEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UCurveBase* CurveToEdit );` — Edits the specified table @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	CurveToEdit				The curve to edit
- L44 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L45 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L46 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L47 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L49 _public prototype_ `TSharedPtr<FExtender> GetToolbarExtender();`
- L50 _public prototype_ `TSharedRef<SWidget> MakeCurveEditorCurveOptionsMenu();`
- L55 _private prototype_ `TSharedRef<SDockTab> SpawnTab_CurveAsset( const FSpawnTabArgs& Args );` — Spawns the tab with the curve asset inside
- L57 _private prototype_ `TSharedRef<SDockTab> SpawnTab_ColorCurveEditor(const FSpawnTabArgs& Args);` — Spawns the details panel for the color curve
- L60 _private prototype_ `EOrientation GetSnapLabelOrientation() const;` — Get the orientation for the snap value controls.
- L63 _private prototype_ `float GetColorGradientViewMin() const;` — Get the view min range from the Bounds to feed to the Color Gradient Editor when we're editing a color curve.
- L65 _private prototype_ `float GetColorGradientViewMax() const;` — Get the view max range from the Bounds to feed to the Color Gradient Editor when we're editing a color curve.
- L68 _private member_ `TSharedPtr<FCurveEditor> CurveEditor;`
- L69 _private member_ `TSharedPtr<SCurveEditorPanel> CurveEditorPanel;`
- L72 _private member_ `static const FName CurveTabId;` — The tab id for the curve asset tab
- L74 _private member_ `static const FName ColorCurveEditorTabId;` — The tab id for the color curve editor tab
- L77 _private member_ `TSharedPtr<class IDetailsView> ColorCurveDetailsView;` — Holds the details panel for the color curve

### `Source/Editor/CurveAssetEditor/Private/SColorGradientCurveEditorView.h` (Private)


#### class `SColorGradientCurveEditorView`  
`class SColorGradientCurveEditorView : public SCurveEditorView`  
_L24-46_
- inherits: `SCurveEditorView`
- desc: This wraps a SColorGradientEditor widget. The SColorGradientEditor widget doesn't know about Curve Models, but we need to show the SColorGradientEditor inside the normal curve stack of the new SCurveEditorPanel. To facilitate this, the FCurveAssetEditor creates an instance of this view and adds it as a pinned view to the SCurveEditorPanel it created. Then FCurveAssetEditor can directly set up the SColorGradientEditor (that this wraps) since it already knows about the FCurveOwnerInterface*. Because of this, this view is tucked inside the CurveAssetEditor as a private class.
- L27 _public function_ `SLATE_BEGIN_ARGS(SColorGradientCurveEditorView)`
- L30 _public prototype_ `SLATE_ATTRIBUTE(float, ViewMinInput) SLATE_ATTRIBUTE(float, ViewMaxInput) SLATE_ATTRIBUTE(bool, IsEditingEnabled) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FCurveEditor> InCurveEditor);` — Min Bounds for the View (in Seconds)
- L41 _public function_ `TSharedRef<SColorGradientEditor> GetGradientEditor() const`
- L43 _public prototype_ `virtual void CheckCacheAndInvalidateIfNeeded() override;`
- L45 _private member_ `TSharedPtr<SColorGradientEditor> GradientViewer;`

### `Source/Editor/CurveAssetEditor/Public/CurveAssetEditorModule.h` (Public)


#### class `FCurveAssetEditorModule`  
`class FCurveAssetEditorModule : public IModuleInterface, public IHasMenuExtensibility`  
_L18-46_
- inherits: `IModuleInterface,IHasMenuExtensibility`
- desc: DataTable Editor module
- L24 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L36 _public prototype_ `virtual TSharedRef<ICurveAssetEditor> CreateCurveAssetEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UCurveBase* CurveToEdit );` — Creates an instance of table editor object.  Only virtual so that it can be called across the DLL boundary. @param	Mode					Mode that this editor should operate in @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	CurveToEdit				The Curve to start editing @return	Interface to the new curve asset editor
- L39 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override` — Gets the extensibility managers for outside entities to extend curve asset editor's menus and toolbars
- L42 _public member_ `static const FName CurveAssetEditorAppIdentifier;` — Curve Asset Editor app identifier string
- L45 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`

### `Source/Editor/CurveAssetEditor/Public/ICurveAssetEditor.h` (Public)


#### class `ICurveAssetEditor`  
`class ICurveAssetEditor : public FAssetEditorToolkit`  
_L10-17_
- inherits: `FAssetEditorToolkit`
- desc: Curve Asset Editor public interface
