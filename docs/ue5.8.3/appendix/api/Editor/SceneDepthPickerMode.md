# Editor / SceneDepthPickerMode

- module root: `Source/Editor/SceneDepthPickerMode`
- headers: 2; symbols: 30
- symbol kinds: class=2, delegate=1, enum=1, enumerator=2, function=1, macro=1, member=3, prototype=19
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, InputCore, Slate, SlateCore, UnrealEd

### `Source/Editor/SceneDepthPickerMode/Private/EditorModeSceneDepthPicker.h` (Private)


#### enum `ESceneDepthPickState`  
`enum class ESceneDepthPickState : uint8`  
_L14-18_
- L16 _public enumerator_ `NotOverViewport`
- L17 _public enumerator_ `OverViewport`

#### class `FEdModeSceneDepthPicker`  
`class FEdModeSceneDepthPicker : public FEdMode`  
_L23-56_
- inherits: `FEdMode`
- desc: Editor mode used to interactively pick actors in the level editor viewports.
- L26 _public prototype_ `FEdModeSceneDepthPicker();`
- L29 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;` — Begin FEdMode interface
- L30 _public prototype_ `virtual bool MouseEnter(FEditorViewportClient* ViewportClient, FViewport* Viewport,int32 x, int32 y) override;`
- L31 _public prototype_ `virtual bool MouseLeave(FEditorViewportClient* ViewportClient, FViewport* Viewport) override;`
- L32 _public prototype_ `virtual bool MouseMove(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 x, int32 y) override;`
- L33 _public prototype_ `virtual bool LostFocus(FEditorViewportClient* ViewportClient, FViewport* Viewport) override;`
- L34 _public prototype_ `virtual bool InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;`
- L35 _public prototype_ `virtual bool GetCursor(EMouseCursor::Type& OutCursor) const override;`
- L36 _public prototype_ `virtual bool UsesToolkits() const override;`
- L37 _public prototype_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override;`
- L38 _public prototype_ `virtual void Initialize() override;`
- L39 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L43 _public prototype_ `virtual void Exit() override;` — End the mode
- L46 _public prototype_ `FText GetCursorDecoratorText() const;` — Delegate used to display information about picking near the cursor
- L49 _public member_ `ESceneDepthPickState PickState;` — Flag for display state
- L52 _public member_ `TSharedPtr<SWindow> CursorDecoratorWindow;` — The window that owns the decorator widget
- L55 _public member_ `FOnSceneDepthLocationSelected OnSceneDepthLocationSelected;` — Delegates used to pick actors

### `Source/Editor/SceneDepthPickerMode/Public/SceneDepthPickerMode.h` (Public)


#### class `FSceneDepthPickerModeModule`  
`class FSceneDepthPickerModeModule : public IModuleInterface`  
_L15-34_
- inherits: `IModuleInterface`
- desc: Scene depth picker mode module
- L19 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L27 _public prototype_ `void BeginSceneDepthPickingMode(FOnSceneDepthLocationSelected InOnSceneDepthLocationSelected);` — Enter scene depth picking mode (note: will cancel any current scene depth picking) @param	InOnDepthSelected		Delegate to call when user has selected a location to sample the scene depth
- L30 _public prototype_ `void EndSceneDepthPickingMode();` — Exit scene depth picking mode
- L33 _public prototype_ `bool IsInSceneDepthPickingMode() const;` — @return Whether or not scene depth picking mode is currently active

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENEDEPTHPICKERMODE_API`
- L10 _delegate_ `DECLARE_DELEGATE_OneParam( FOnSceneDepthLocationSelected, FVector );`
- L10 _prototype_ `DECLARE_DELEGATE_OneParam( FOnSceneDepthLocationSelected, FVector );`
