# Plugins / MeshPaintEditorMode

- module root: `Plugins/MeshPainting/Source/MeshPaintEditorMode`
- headers: 9; symbols: 265
- symbol kinds: class=17, enum=2, enumerator=10, function=17, macro=1, member=76, prototype=141, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopPlatform, DynamicMesh, EditorFramework, EditorInteractiveToolsFramework, EditorWidgets, Engine, GeometryCollectionEngine, GeometryCore, ImageCore, InputCore, InteractiveToolsFramework, InterchangeEngine, InterchangePipelines, Landscape, MainFrame, MeshConversionEngineTypes, MeshPaintingToolset, PropertyEditor, RHI, RenderCore, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: EditorSubsystem, Slate, SlateCore

### `Plugins/MeshPainting/Source/MeshPaintEditorMode/Private/BrushSettingsCustomization.h` (Private)


#### class `FMeshPaintModeSettingsCustomization`  
`class FMeshPaintModeSettingsCustomization : public IDetailCustomization`  
_L11-18_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IPropertyTypeCustomization interface

#### class `FMeshPaintingSettingsCustomization`  
`class FMeshPaintingSettingsCustomization : public IDetailCustomization`  
_L20-30_
- inherits: `IDetailCustomization`
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IPropertyTypeCustomization interface
- L29 _protected prototype_ `FReply OnSwapColorsClicked(TSharedRef<IPropertyHandle> PaintColor, TSharedRef<IPropertyHandle> EraseColor);`

#### class `FVertexPaintingSettingsCustomization`  
`class FVertexPaintingSettingsCustomization : public FMeshPaintingSettingsCustomization`  
_L32-39_
- inherits: `FMeshPaintingSettingsCustomization`
- L35 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L38 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IPropertyTypeCustomization interface

#### class `FVertexColorPaintingSettingsCustomization`  
`class FVertexColorPaintingSettingsCustomization : public FVertexPaintingSettingsCustomization`  
_L41-48_
- inherits: `FVertexPaintingSettingsCustomization`
- L44 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L47 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IPropertyTypeCustomization interface

#### class `FVertexWeightPaintingSettingsCustomization`  
`class FVertexWeightPaintingSettingsCustomization : public FVertexPaintingSettingsCustomization`  
_L50-64_
- inherits: `FVertexPaintingSettingsCustomization`
- L53 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L56 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IPropertyTypeCustomization interface
- L60 _protected member_ `TSharedPtr<FPropertyRestriction> BlendPaintEnumRestriction;` — Property restriction applied to blend paint enum dropdown box
- L63 _protected prototype_ `void OnTextureWeightTypeChanged(TSharedRef<IPropertyHandle> WeightTypeProperty, TSharedRef<IPropertyHandle> PaintWeightProperty, TSharedRef<IPropertyHandle> EraseWeightProperty);` — Callback for when texture weight type changed so we can update restrictions

#### class `FTexturePaintingSettingsCustomization`  
`class FTexturePaintingSettingsCustomization : public FMeshPaintingSettingsCustomization`  
_L66-73_
- inherits: `FMeshPaintingSettingsCustomization`
- L69 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L72 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IPropertyTypeCustomization interface

#### class `FTextureColorPaintingSettingsCustomization`  
`class FTextureColorPaintingSettingsCustomization : public FTexturePaintingSettingsCustomization`  
_L75-82_
- inherits: `FTexturePaintingSettingsCustomization`
- L78 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L81 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IPropertyTypeCustomization interface

#### class `FTextureAssetPaintingSettingsCustomization`  
`class FTextureAssetPaintingSettingsCustomization : public FTexturePaintingSettingsCustomization`  
_L84-91_
- inherits: `FTexturePaintingSettingsCustomization`
- L87 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L90 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IPropertyTypeCustomization interface

### `Plugins/MeshPainting/Source/MeshPaintEditorMode/Private/ImportVertexColorOptions.h` (Private)


#### class `UImportVertexColorOptions`  
`class UImportVertexColorOptions : public UObject`  
_L12-63_
- reflection: `UCLASS()`
- inherits: `UObject`
- L17 _public function_ `UImportVertexColorOptions() : UVIndex(0), LODIndex(0), bRed(true), bBlue(true), bGreen(true), bAlpha(true), bImportToInstance(true), NumLODs(0), bCanImportToInstance(false)`
- L21 _public member_ `int UVIndex;` — `UPROPERTY(EditAnywhere, Category=Options)` — Texture Coordinate Channel to use for Sampling the Texture
- L25 _public member_ `int LODIndex;` — `UPROPERTY(EditAnywhere, Category = Options)` — LOD Index to import the Vertex Colors to
- L29 _public member_ `bool bRed;` — `UPROPERTY(EditAnywhere, Category = Options)` — Red Texture Channel
- L33 _public member_ `bool bBlue;` — `UPROPERTY(EditAnywhere, Category = Options)` — Blue Texture Channel
- L37 _public member_ `bool bGreen;` — `UPROPERTY(EditAnywhere, Category = Options)` — Green Texture Channel
- L41 _public member_ `bool bAlpha;` — `UPROPERTY(EditAnywhere, Category = Options)` — Alpha Texture Channel
- L45 _public member_ `bool bImportToInstance;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether or not to import the Vertex Colors to Mesh Component instance or the underlying Static Mesh
- L47 _public member_ `TMap<int32, int32> LODToMaxUVMap;`
- L48 _public member_ `int32 NumLODs;`
- L51 _public member_ `bool bCanImportToInstance;` — `UPROPERTY()`
- L53 _public function_ `FColor CreateColorMask() const`

#### class `SImportVertexColorOptionsWindow`  
`class SImportVertexColorOptionsWindow : public SCompoundWidget`  
_L68-129_
- inherits: `SCompoundWidget`
- L71 _public function_ `SLATE_BEGIN_ARGS(SImportVertexColorOptionsWindow)`
- L78 _public prototype_ `void Construct(const FArguments& InArgs);`
- L79 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L81 _public function_ `FReply OnImport()`
- L91 _public function_ `FReply OnCancel()`
- L101 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L111 _public function_ `bool ShouldImport() const`
- L116 _public function_ `UImportVertexColorOptions* GetOptions() const`
- L121 _public function_ `SImportVertexColorOptionsWindow()`
- L124 _private member_ `TWeakPtr< SWindow > WidgetWindow;`
- L125 _private member_ `TSharedPtr< SButton > ImportButton;`
- L126 _private member_ `bool bShouldImport;`
- L127 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L128 _private member_ `UImportVertexColorOptions* Options;`

### `Plugins/MeshPainting/Source/MeshPaintEditorMode/Private/ImportVertexColorOptionsCustomization.h` (Private)


#### class `FImportVertexColorOptionsCustomization`  
`class FImportVertexColorOptionsCustomization : public IDetailCustomization`  
_L10-22_
- inherits: `IDetailCustomization`
- desc: Customization for importing vertex colors from a texture see SImportVertexColorOptions
- L13 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L21 _private prototype_ `TSharedRef<SHorizontalBox> CreateColorChannelWidget(TSharedRef<class IPropertyHandle> ChannelProperty);`

### `Plugins/MeshPainting/Source/MeshPaintEditorMode/Private/MeshPaintMode.h` (Private)


#### class `UMeshPaintMode`  
`class UMeshPaintMode : public UEdMode, public ILegacyEdModeViewportInterface`  
_L25-167_
- reflection: `UCLASS()`
- inherits: `UEdMode,ILegacyEdModeViewportInterface`
- desc: Mesh paint Mode.  Extends editor viewports with the ability to paint data on meshes
- L30 _public prototype_ `UMeshPaintMode();`
- L32 _public prototype_ `virtual void Enter() override;`
- L33 _public prototype_ `virtual void Exit() override;`
- L34 _public prototype_ `virtual void CreateToolkit() override;`
- L35 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L36 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;`
- L37 _public prototype_ `virtual TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetModeCommands() const override;`
- L39 _public prototype_ `static UMeshPaintingToolProperties* GetToolProperties();`
- L40 _public prototype_ `static UMeshVertexPaintingToolProperties* GetVertexToolProperties();`
- L41 _public prototype_ `static UMeshVertexColorPaintingToolProperties* GetVertexColorToolProperties();`
- L42 _public prototype_ `static UMeshVertexWeightPaintingToolProperties* GetVertexWeightToolProperties();`
- L43 _public prototype_ `static UMeshTexturePaintingToolProperties* GetTextureToolProperties();`
- L44 _public prototype_ `static UMeshTextureColorPaintingToolProperties* GetTextureColorToolProperties();`
- L45 _public prototype_ `static UMeshTextureAssetPaintingToolProperties* GetTextureAssetToolProperties();`
- L46 _public prototype_ `static UMeshPaintMode* GetMeshPaintMode();`
- L47 _public prototype_ `static FName GetValidPaletteName(const FName InName);`
- L49 _public member_ `static FName MeshPaintMode_VertexColor;`
- L50 _public member_ `static FName MeshPaintMode_VertexWeights;`
- L51 _public member_ `static FName MeshPaintMode_TextureColor;`
- L52 _public member_ `static FName MeshPaintMode_TextureAsset;`
- L53 _public member_ `static FString VertexSelectToolName;`
- L54 _public member_ `static FString TextureColorSelectToolName;`
- L55 _public member_ `static FString TextureAssetSelectToolName;`
- L56 _public member_ `static FString VertexColorPaintToolName;`
- L57 _public member_ `static FString VertexWeightPaintToolName;`
- L58 _public member_ `static FString TextureColorPaintToolName;`
- L59 _public member_ `static FString TextureAssetPaintToolName;`
- L63 _public prototype_ `template<typename ComponentClass> TArray<ComponentClass*> GetSelectedComponents() const;` — Returns the instance of ComponentClass found in the current Editor selection
- L66 _public function_ `uint32 GetVertexDataSizeInBytes() const` — Returns data size of per-instance vertex color data for the currently selected components.
- L68 _public function_ `uint32 GetMeshPaintTextureResourceSizeInBytes() const` — Returns resource size of mesh paint textures for the currently selected components.
- L71 _public prototype_ `bool GetSelectionWarning(FText& OutMessage) const;` — Returns true and fills the message if there is the current selection is not in an expectd state for the current painting mode.
- L75 _protected prototype_ `virtual void BindCommands() override;` — Binds UI commands to actions for the mesh paint mode
- L78 _protected prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;` — UEdMode interface
- L79 _protected prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L80 _protected prototype_ `virtual void ActorSelectionChangeNotify() override;`
- L81 _protected prototype_ `virtual void ElementSelectionChangeNotify() override;`
- L82 _protected prototype_ `virtual void ActorPropChangeNotify() override;`
- L83 _protected prototype_ `virtual void ActivateDefaultTool() override;`
- L84 _protected prototype_ `virtual void UpdateOnPaletteChange(FName NewPalette);`
- L88 _protected prototype_ `void UpdateSelectedMeshes();`
- L89 _protected prototype_ `void UpdateOnMaterialChange(bool bInvalidateHitProxies);`
- L90 _protected prototype_ `void UpdateOnPostCompile(const TArray<struct FAssetCompileData>& Data);`
- L91 _protected prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& InOldToNewInstanceMap);`
- L92 _protected prototype_ `void OnResetViewMode();`
- L93 _protected prototype_ `void OnVertexPaintFinished();`
- L94 _protected prototype_ `void OnTextureColorVertexPaintFinished(UMeshComponent* MeshComponent);`
- L96 _protected prototype_ `void UpdateCachedDataSizes();`
- L97 _protected prototype_ `void EndPaintToolIfNoLongerValid();`
- L99 _protected prototype_ `bool IsInSelectTool() const;`
- L100 _protected prototype_ `bool IsInPaintTool() const;`
- L103 _protected prototype_ `void SwapColors();` — Start command bindings
- L104 _protected prototype_ `bool CanSwapColors() const;`
- L105 _protected prototype_ `void FillVertexColors();`
- L106 _protected prototype_ `bool CanFillVertexColors() const;`
- L107 _protected prototype_ `void FillTexture();`
- L108 _protected prototype_ `bool CanFillTexture() const;`
- L109 _protected prototype_ `void PropagateVertexColorsToMesh();`
- L110 _protected prototype_ `bool CanPropagateVertexColorsToMesh() const;`
- L111 _protected prototype_ `void PropagateVertexColorsToLODs();`
- L112 _protected prototype_ `bool CanPropagateVertexColorsToLODs() const;`
- L113 _protected prototype_ `void SaveVertexColorsToAssets();`
- L114 _protected prototype_ `bool CanSaveVertexColorsToAssets() const;`
- L115 _protected prototype_ `void SaveTexturePackages();`
- L116 _protected prototype_ `bool CanSaveTexturePackages() const;`
- L117 _protected prototype_ `void AddMeshPaintTextures();`
- L118 _protected prototype_ `bool CanAddMeshPaintTextures() const;`
- L119 _protected prototype_ `void RemoveInstanceVertexColors();`
- L120 _protected prototype_ `bool CanRemoveInstanceVertexColors() const;`
- L121 _protected prototype_ `void RemoveMeshPaintTexture();`
- L122 _protected prototype_ `bool CanRemoveMeshPaintTextures() const;`
- L123 _protected prototype_ `void CopyInstanceVertexColors();`
- L124 _protected prototype_ `bool CanCopyInstanceVertexColors() const;`
- L125 _protected prototype_ `void CopyMeshPaintTexture();`
- L126 _protected prototype_ `bool CanCopyMeshPaintTexture() const;`
- L127 _protected prototype_ `void Copy();`
- L128 _protected prototype_ `bool CanCopy() const;`
- L129 _protected prototype_ `void PasteInstanceVertexColors();`
- L130 _protected prototype_ `bool CanPasteInstanceVertexColors() const;`
- L131 _protected prototype_ `void PasteMeshPaintTexture();`
- L132 _protected prototype_ `bool CanPasteMeshPaintTexture() const;`
- L133 _protected prototype_ `void Paste();`
- L134 _protected prototype_ `bool CanPaste() const;`
- L135 _protected prototype_ `void ImportVertexColorsFromFile();`
- L136 _protected prototype_ `bool CanImportVertexColorsFromFile() const;`
- L137 _protected prototype_ `void ImportVertexColorsFromMeshPaintTexture();`
- L138 _protected prototype_ `bool CanImportVertexColorsFromMeshPaintTexture() const;`
- L139 _protected prototype_ `void ImportMeshPaintTextureFromVertexColors();`
- L140 _protected prototype_ `bool CanImportMeshPaintTextureFromVertexColors() const;`
- L141 _protected prototype_ `void FixVertexColors();`
- L142 _protected prototype_ `bool CanFixVertexColors() const;`
- L143 _protected prototype_ `void FixTextureColors();`
- L144 _protected prototype_ `bool CanFixTextureColors() const;`
- L145 _protected prototype_ `void CycleMeshLODs(int32 Direction);`
- L146 _protected prototype_ `bool CanCycleMeshLODs() const;`
- L147 _protected prototype_ `void CycleTextures(int32 Direction);`
- L148 _protected prototype_ `bool CanCycleTextures() const;`
- L149 _protected prototype_ `void ChangeBrushRadius(int32 Direction);`
- L150 _protected prototype_ `void ChangeBrushStrength(int32 Direction);`
- L151 _protected prototype_ `void ChangeBrushFalloff(int32 Direction);`
- L152 _protected prototype_ `bool CanChangeBrush() const;`
- L157 _protected member_ `TObjectPtr<UMeshPaintModeSettings> ModeSettings;` — `UPROPERTY(Transient)`
- L159 _protected member_ `bool bRecacheDataSizes = false;`
- L160 _protected member_ `uint32 CachedVertexDataSize = 0;`
- L161 _protected member_ `uint32 CachedMeshPaintTextureResourceSize = 0;`
- L163 _protected member_ `bool bRecacheValidForPaint = false;`
- L165 _protected member_ `FDelegateHandle PaletteChangedHandle;`
- L166 _protected member_ `FConsoleVariableSinkHandle CVarDelegateHandle;`

### `Plugins/MeshPainting/Source/MeshPaintEditorMode/Private/MeshPaintModeSettings.h` (Private)


#### enum `EMeshPaintColorView`  
`enum class EMeshPaintColorView : uint8`  
_L11-30_
- reflection: `UENUM()`
- desc: Mesh paint color view modes (somewhat maps to EVertexColorViewMode engine enum.)
- L14 _public enumerator_ `Normal UMETA(DisplayName = "Off")` — Normal view mode (vertex color visualization off)
- L17 _public enumerator_ `RGB UMETA(DisplayName = "RGB Channels")` — RGB only
- L20 _public enumerator_ `Alpha UMETA(DisplayName = "Alpha Channel")` — Alpha only
- L23 _public enumerator_ `Red UMETA(DisplayName = "Red Channel")` — Red only
- L26 _public enumerator_ `Green UMETA(DisplayName = "Green Channel")` — Green only
- L29 _public enumerator_ `Blue UMETA(DisplayName = "Blue Channel")` — Blue only

#### class `UMeshPaintModeSettings`  
`class UMeshPaintModeSettings : public UObject`  
_L36-49_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Implements the Mesh Editor's settings.
- L44 _public member_ `EMeshPaintDataColorViewMode ColorViewMode = EMeshPaintDataColorViewMode::Normal;` — `UPROPERTY(config, EditAnywhere, Category = Visualization)` — Color view mode used to display Vertex Colors
- L48 _public member_ `FName DefaultPalette;` — `UPROPERTY(config)` — Palette tab to use when entering the tool

### `Plugins/MeshPainting/Source/MeshPaintEditorMode/Private/MeshPaintModeToolkit.h` (Private)


#### class `FMeshPaintModeToolkit`  
`class FMeshPaintModeToolkit : public FModeToolkit`  
_L10-36_
- inherits: `FModeToolkit`
- desc: Mode Toolkit for the Mesh Paint Mode
- L14 _public function_ `FMeshPaintModeToolkit( )`
- L17 _public prototype_ `~FMeshPaintModeToolkit();`
- L20 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;` — FModeToolkit interface
- L23 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit overrides
- L24 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L25 _public prototype_ `virtual void GetToolPaletteNames(TArray<FName>& PaletteNames) const override;`
- L26 _public prototype_ `virtual FText GetToolPaletteDisplayName(FName Palette) const override;`
- L28 _public prototype_ `virtual FText GetActiveToolDisplayName() const;`
- L29 _public prototype_ `virtual FText GetActiveToolMessage() const;`
- L31 _public prototype_ `void SetActiveToolMessage(const FText&);`
- L34 _private member_ `FText ActiveToolMessageCache;`

### `Plugins/MeshPainting/Source/MeshPaintEditorMode/Public/MeshPaintEditorMode.h` (Public)
_(no declarations extracted)_

### `Plugins/MeshPainting/Source/MeshPaintEditorMode/Public/MeshPaintModeCommands.h` (Public)


#### class `FMeshPaintEditorModeCommands`  
`class FMeshPaintEditorModeCommands : public TCommands<FMeshPaintEditorModeCommands>`  
_L10-73_
- inherits: `TCommands<FMeshPaintEditorModeCommands>`
- L13 _public function_ `FMeshPaintEditorModeCommands() : TCommands<FMeshPaintEditorModeCommands> ( "MeshPaint", NSLOCTEXT("MeshPaintEditorMode", "MeshPaintingModeCommands", "Mesh Painting Mode"), NAME_None, FAppStyle::GetAppStyleSetName() )`
- L25 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L27 _public function_ `static TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetCommands()`
- L33 _public member_ `TSharedPtr<FUICommandInfo> SelectVertex;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> SelectTextureColor;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> SelectTextureAsset;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> PaintVertexColor;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> PaintVertexWeight;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> PaintTextureColor;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> PaintTextureAsset;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> SwapColor;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> FillVertex;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> FillTexture;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> PropagateMesh;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> PropagateLODs;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> SaveVertex;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> SaveTexture;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> Add;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> RemoveVertex;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> RemoveTexture;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> Copy;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> Paste;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> Import;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> GetTextureColors;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> GetVertexColors;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> FixVertex;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> FixTexture;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> PreviousLOD;`
- L61 _public member_ `TSharedPtr<FUICommandInfo> NextLOD;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> PreviousTexture;`
- L63 _public member_ `TSharedPtr<FUICommandInfo> NextTexture;`
- L65 _public member_ `TSharedPtr<FUICommandInfo> IncreaseBrushRadius;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> DecreaseBrushRadius;`
- L67 _public member_ `TSharedPtr<FUICommandInfo> IncreaseBrushStrength;`
- L68 _public member_ `TSharedPtr<FUICommandInfo> DecreaseBrushStrength;`
- L69 _public member_ `TSharedPtr<FUICommandInfo> IncreaseBrushFalloff;`
- L70 _public member_ `TSharedPtr<FUICommandInfo> DecreaseBrushFalloff;`
- L72 _public member_ `TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> Commands;`

#### class `FMeshPaintingToolActionCommands`  
`class FMeshPaintingToolActionCommands : public TInteractiveToolCommands<FMeshPaintingToolActionCommands>`  
_L76-112_
- inherits: `TInteractiveToolCommands<FMeshPaintingToolActionCommands>`
- L79 _public function_ `FMeshPaintingToolActionCommands() : TInteractiveToolCommands<FMeshPaintingToolActionCommands>( "MeshPaintingTools",`
- L89 _public prototype_ `virtual void GetToolDefaultObjectList(TArray<UInteractiveTool*>& ToolCDOs) override;`
- L99 _public prototype_ `static void RegisterAllToolActions();` — Register all Tool command sets. Call this in module startup
- L104 _public prototype_ `static void UnregisterAllToolActions();` — Unregister all Tool command sets. Call this from module shutdown.
- L111 _public prototype_ `static void UpdateToolCommandBinding(UInteractiveTool* Tool, TSharedPtr<FUICommandList> UICommandList, bool bUnbind = false);` — Add or remove commands relevant to Tool to the given UICommandList. Call this when the active tool changes (eg on ToolManager.OnToolStarted / OnToolEnded) @param bUnbind if true, commands are removed, otherwise added

### `Plugins/MeshPainting/Source/MeshPaintEditorMode/Public/MeshPaintModeHelpers.h` (Public)


#### enum `EMeshPaintActiveMode`  
`enum class EMeshPaintActiveMode : uint8`  
_L31-37_
- reflection: `UENUM()`
- L33 _public enumerator_ `VertexColor UMETA(DisplayName = "VertexColor")`
- L34 _public enumerator_ `VertexWeights UMETA(DisplayName = "VertexWeights")`
- L35 _public enumerator_ `TextureColor UMETA(DisplayName = "TextureColor")`
- L36 _public enumerator_ `Texture UMETA(DisplayName = "Texture")`

#### class `UMeshPaintModeSubsystem`  
`class UMeshPaintModeSubsystem : public UEditorSubsystem`  
_L41-92_
- inherits: `UEditorSubsystem`
- L45 _public prototype_ `void SetViewportColorMode(EMeshPaintActiveMode ActiveMode, EMeshPaintDataColorViewMode ColorViewMode, FEditorViewportClient* ViewportClient, UInteractiveTool const* ActiveTool);` — Forces the Viewport Client to render using the given Viewport Color ViewMode
- L48 _public prototype_ `void SetRealtimeViewport(FEditorViewportClient* ViewportClient, bool bRealtime);` — Sets whether or not the viewport should be real time rendered
- L52 _public prototype_ `void ImportVertexColorsFromTexture(UMeshComponent* MeshComponent);` — Helper function to import Vertex Colors from a Texture to the specified MeshComponent (makes use of SImportVertexColorsOptions Widget)
- L55 _public prototype_ `void ImportVertexColorsToSkeletalMesh(USkeletalMesh* SkeletalMesh, const UImportVertexColorOptions* Options, UTexture2D* Texture);` — Imports vertex colors from a Texture to the specified Skeletal Mesh according to user-set options
- L58 _public prototype_ `void ImportVertexColorsFromMeshPaintTexture(UMeshComponent* MeshComponent);` — Helper function to import Vertex Colors from a the MeshPaintTexture on the mesh component
- L61 _public prototype_ `void ImportMeshPaintTextureFromVertexColors(UMeshComponent* MeshComponent);` — Helper function to import the MeshPaintTexture on the mesh component from the vertex colors
- L72 _public prototype_ `bool RetrieveViewportPaintRays(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI, TArray<FPaintRay>& OutPaintRays);`
- L75 _public prototype_ `void ImportVertexColorsToStaticMesh(UStaticMesh* StaticMesh, const UImportVertexColorOptions* Options, UTexture2D* Texture);` — Imports vertex colors from a Texture to the specified Static Mesh according to user-set options
- L78 _public prototype_ `void ImportVertexColorsToStaticMeshComponent(UStaticMeshComponent* StaticMeshComponent, const UImportVertexColorOptions* Options, UTexture2D* Texture);` — Imports vertex colors from a Texture to the specified Static Mesh Component according to user-set options
- L80 _public prototype_ `void PropagateVertexColors(const TArray<UStaticMeshComponent *> StaticMeshComponents);`
- L81 _public prototype_ `bool CanPropagateVertexColors(TArray<UStaticMeshComponent*>& StaticMeshComponents, TArray<UStaticMesh*>& StaticMeshes, int32 NumInstanceVertexColorBytes);`
- L82 _public prototype_ `void CopyVertexColors(const TArray<UStaticMeshComponent*> StaticMeshComponents, TArray<FPerComponentVertexColorData>& CopiedVertexColors);`
- L83 _public prototype_ `bool CanCopyInstanceVertexColors(const TArray<UStaticMeshComponent*>& StaticMeshComponents, int32 PaintingMeshLODIndex);`
- L84 _public prototype_ `void PasteVertexColors(const TArray<UStaticMeshComponent*>& StaticMeshComponents, TArray<FPerComponentVertexColorData>& CopiedColorsByComponent);`
- L85 _public prototype_ `bool CanPasteInstanceVertexColors(const TArray<UStaticMeshComponent*>& StaticMeshComponents, const TArray<FPerComponentVertexColorData>& CopiedColorsByComponent);`
- L86 _public prototype_ `void RemovePerLODColors(const TArray<UMeshComponent*>& PaintableComponents);`
- L88 _public prototype_ `bool CanFixTextureColors(const TArray<UMeshComponent*>& Components);`
- L89 _public prototype_ `void FixTextureColors(const TArray<UMeshComponent*>& Components);`
- L91 _public prototype_ `void SwapColors();`

#### struct `UMeshPaintModeSubsystem::FPaintRay`  
`struct FPaintRay`  
_L63-69_
- L65 _public member_ `FVector CameraLocation;`
- L66 _public member_ `FVector RayStart;`
- L67 _public member_ `FVector RayDirection;`
- L68 _public member_ `UViewportInteractor* ViewportInteractor;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MESHPAINTEDITORMODE_API`
