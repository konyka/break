# Plugins / TimecodeSynchronizerEditor

- module root: `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizerEditor`
- headers: 10; symbols: 131
- symbol kinds: class=11, enum=1, enumerator=3, function=9, macro=1, member=35, prototype=69, struct=1, typedef=1
- PrivateDependencyModuleNames: AssetTools, Core, CoreUObject, EditorFramework, Engine, InputCore, MediaAssets, MediaPlayerEditor, PropertyEditor, Slate, SlateCore, TimecodeSynchronizer, UnrealEd

### `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizerEditor/Private/AssetEditor/TimecodeSynchronizerEditorToolkit.h` (Private)


#### class `FTimecodeSynchronizerEditorToolkit`  
`class FTimecodeSynchronizerEditorToolkit : public FAssetEditorToolkit`  
_L15-61_
- inherits: `FAssetEditorToolkit`
- desc: Viewer/editor for a TimecodeSynchronizer
- L18 _private typedef_ `using Super = FAssetEditorToolkit;`
- L21 _public prototype_ `static TSharedRef<FTimecodeSynchronizerEditorToolkit> CreateEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UTimecodeSynchronizer* InTimecodeSynchronizer);`
- L30 _public prototype_ `void InitTimecodeSynchronizerEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UTimecodeSynchronizer* InTimecodeSynchronizer);` — Edits the specified table @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	InTimecodeSynchronizer	The TimecodeSynchronizer asset to edit
- L31 _public prototype_ `~FTimecodeSynchronizerEditorToolkit();`
- L34 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L35 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L36 _public prototype_ `virtual FText GetToolkitName() const override;`
- L37 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L38 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L39 _public prototype_ `virtual void RemoveEditingObject(UObject* Object) override;`
- L41 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L42 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L45 _public prototype_ `class UTimecodeSynchronizer* GetTimecodeSynchronizer() const;` — Get the TimecodeSynchronizer Asset being edited
- L48 _private prototype_ `void HandleAssetPostImport(UFactory* InFactory, UObject* InObject);`
- L49 _private prototype_ `TSharedRef<SDockTab> SpawnPropertiesTab(const FSpawnTabArgs& Args);`
- L50 _private prototype_ `TSharedRef<SDockTab> SpawnSourceViewerTab(const FSpawnTabArgs& Args);`
- L51 _private prototype_ `TSharedRef<SDockTab> SpawnSynchronizerWidgetTab(const FSpawnTabArgs& Args);`
- L53 _private prototype_ `void ExtendToolBar();`
- L55 _private prototype_ `FLinearColor GetProgressColor() const;`
- L56 _private prototype_ `void HandleSynchronizationEvent(ETimecodeSynchronizationEvent Event);`
- L60 _private member_ `TSharedPtr<class IDetailsView> DetailsView;` — Details view

### `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizerEditor/Private/AssetTypeActions/AssetTypeActions_TimecodeSynchronizer.h` (Private)


#### class `FAssetTypeActions_TimecodeSynchronizer`  
`class FAssetTypeActions_TimecodeSynchronizer : public FAssetTypeActions_Base`  
_L7-17_
- inherits: `FAssetTypeActions_Base`
- L10 _public function_ `virtual FColor GetTypeColor() const override`
- L11 _public function_ `virtual uint32 GetCategories() override`
- L12 _public function_ `virtual bool IsImportedAsset() const override`
- L14 _public prototype_ `virtual FText GetName() const override;`
- L15 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L16 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`

### `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizerEditor/Private/UI/TimecodeSynchronizerEditorCommand.h` (Private)


#### class `FTimecodeSynchronizerEditorCommand`  
`class FTimecodeSynchronizerEditorCommand : public TCommands<FTimecodeSynchronizerEditorCommand>`  
_L10-26_
- inherits: `TCommands<FTimecodeSynchronizerEditorCommand>`
- L13 _public prototype_ `FTimecodeSynchronizerEditorCommand();`
- L16 _public prototype_ `virtual void RegisterCommands() override;` — Describe and instantiate the commands in here by using the UI COMMAND macro.
- L19 _private prototype_ `static void OpenTimecodeSynchronizerEditor();`
- L20 _private prototype_ `static bool CanOpenTimecodeSynchronizerEditor();`
- L23 _public member_ `TSharedPtr<FUICommandInfo> OpenEditorCommand;`
- L25 _public member_ `TSharedPtr<class FUICommandList> CommandActionList;`

### `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizerEditor/Private/UI/TimecodeSynchronizerEditorLevelToolbar.h` (Private)


#### class `FTimecodeSynchronizerEditorLevelToolbar`  
`class FTimecodeSynchronizerEditorLevelToolbar`  
_L18-38_
- desc: FTimecodeSynchronizerEditorLevelToolbar
- L21 _public prototype_ `FTimecodeSynchronizerEditorLevelToolbar();`
- L22 _public prototype_ `~FTimecodeSynchronizerEditorLevelToolbar();`
- L25 _private prototype_ `void ExtendLevelEditorToolbar();`
- L26 _private prototype_ `void FillToolbar(FToolBarBuilder& ToolbarBuilder);`
- L28 _private prototype_ `void AddObjectSubMenu(FMenuBuilder& MenuBuilder);`
- L29 _private prototype_ `TSharedRef<SWidget> GenerateMenuContent();`
- L30 _private prototype_ `void OpenCurrentTimecodeSynchronizer();`
- L31 _private prototype_ `void CreateNewTimecodeSynchronizer();`
- L32 _private prototype_ `void NewTimecodeSynchronizerSelected(const FAssetData& AssetData);`
- L36 _private member_ `TSharedPtr<FExtender> LevelToolbarExtender;`
- L37 _private member_ `TWeakObjectPtr<UTimecodeSynchronizer> CurrentTimecodeSynchronizer;`

### `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizerEditor/Private/UI/TimecodeSynchronizerEditorStyle.h` (Private)


#### class `FTimecodeSynchronizerEditorStyle`  
`class FTimecodeSynchronizerEditorStyle`  
_L13-22_
- L16 _public prototype_ `static void Register();`
- L17 _public prototype_ `static void Unregister();`
- L19 _public prototype_ `static FName GetStyleSetName();`
- L21 _public prototype_ `static const ISlateStyle& Get();`

### `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizerEditor/Private/Widgets/STimecodeSynchronizerSourceViewer.h` (Private)


#### class `STimecodeSynchronizerSourceViewer`  
`class STimecodeSynchronizerSourceViewer : public SCompoundWidget`  
_L21-60_
- inherits: `SCompoundWidget`
- desc: Implements the contents of the viewer tab in the TimecodeSynchronizer editor.
- L26 _public function_ `SLATE_BEGIN_ARGS(STimecodeSynchronizerSourceViewer)`
- L32 _public prototype_ `STimecodeSynchronizerSourceViewer();` — Default constructor.
- L35 _public prototype_ `virtual ~STimecodeSynchronizerSourceViewer();` — Default destructor.
- L45 _public prototype_ `void Construct(const FArguments& InArgs, UTimecodeSynchronizer& InTimecodeSynchronizer);` — Construct this widget @param InArgs The declaration data for this widget. @param InTimecodeSynchronizer The active Asset.
- L49 _private prototype_ `void PopulateActiveSources();`
- L50 _private prototype_ `void HandleSynchronizationEvent(ETimecodeSynchronizationEvent Event);`
- L51 _private prototype_ `static TSharedRef<SWidget> GetVisualWidget(const FTimecodeSynchronizerActiveTimecodedInputSource& InSource);`
- L56 _private member_ `TStrongObjectPtr<UTimecodeSynchronizer> TimecodeSynchronizer;` — Active TimecodeSynchronizer
- L59 _private member_ `TSharedPtr<SVerticalBox> ViewportVerticalBox;` — VerticalBox holding active sources viewport

### `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizerEditor/Private/Widgets/STimecodeSynchronizerSourceViewport.h` (Private)


#### class `STimecodeSynchronizerSourceViewport`  
`class STimecodeSynchronizerSourceViewport : public SCompoundWidget`  
_L15-70_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(STimecodeSynchronizerSourceViewport)`
- L26 _public prototype_ `STimecodeSynchronizerSourceViewport();` — Default constructor.
- L38 _public prototype_ `void Construct(const FArguments& InArgs, UTimecodeSynchronizer* InTimecodeSynchronization, int32 InAttachedSourceIndex, bool InTimecodedSource, TSharedRef<SWidget> InVisualWidget);` — Construct this widget @param InArgs The declaration data for this widget. @param InTimecodeSynchronization The Asset currently active. @param InAttachedSource The Source to display. @param InTexture The source texture to render if any
- L43 _private prototype_ `FText HandleIntervalMinTimecodeText() const;` — Callback for getting the overlay text of Source minimum Timecode buffered.
- L46 _private prototype_ `FText HandleIntervalMaxTimecodeText() const;` — Callback for getting the overlay text of Source maximum Timecode buffered.
- L49 _private prototype_ `FText HandleCurrentTimecodeText() const;` — Callback for getting the text of the Current Synchronized Timecode.
- L52 _private prototype_ `FText HandleIsSourceMainText() const;` — Callback setuping the text if the source is the main source.
- L55 _private prototype_ `const FTimecodeSynchronizerActiveTimecodedInputSource* GetAttachedSource() const;` — Get the attached Input source in TimecodeSynchronization.GetActiveSources() at the AttachedSourceIndex index
- L60 _private member_ `TSharedPtr<SEditableTextBox> SourceTextBox;` — Media Source name text box.
- L63 _private member_ `TStrongObjectPtr<UTimecodeSynchronizer> TimecodeSynchronization;` — Current TimecodeSynchronization being used.
- L66 _private member_ `int32 AttachedSourceIndex;` — Attached Input source index in either TimecodeSynchronization.GetSynchronizedSources() or GetNonSynchronizedSources().
- L69 _private member_ `bool bIsSynchronizedSource;` — Whether or not this source is used for synchronization.

### `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizerEditor/Private/Widgets/STimecodeSynchronizerWidget.h` (Private)


#### class `STimecodeSynchronizerBarWidget`  
`class STimecodeSynchronizerBarWidget : public SWidget`  
_L16-87_
- inherits: `SWidget`
- L19 _public prototype_ `STimecodeSynchronizerBarWidget();`
- L21 _public function_ `SLATE_BEGIN_ARGS(STimecodeSynchronizerBarWidget) : _UpdateRate(1) , _FrameWidth(10)`
- L25 _public prototype_ `SLATE_ATTRIBUTE(int32, UpdateRate);`
- L26 _public prototype_ `SLATE_ATTRIBUTE(int32, FrameWidth);`
- L30 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L31 _public prototype_ `virtual FChildren* GetChildren() override;`
- L32 _public prototype_ `virtual void OnArrangeChildren(const FGeometry&, FArrangedChildren&) const override;`
- L33 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L34 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InCullingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;`
- L35 _public prototype_ `void Construct(const FArguments& InArgs, UTimecodeSynchronizer& InTimecodeSynchronizer);`
- L38 _public prototype_ `void SetUpdateRate(int32 InUpdateFrequency);`
- L39 _public prototype_ `void SetFrameWidth(int32 InFrameWidth);`
- L49 _private prototype_ `void DrawBoxWithBorder(const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 InLayerId, float InMinX, float InMaxX, float InMinY, float InMaxY, const FWidgetStyle& InWidgetStyle, const FSlateBrush* InBorderBrush, const FLinearColor& InBorderTint, const FSlateBrush* InInsideBrush, const FLinearColor& InInsideTint) const;`
- L50 _private prototype_ `void DrawText(const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, uint32 InLayerId, Justification InJustification, const FString& InText, const FBox2D& InRegion, const FWidgetStyle& InWidgetStyle) const;`
- L53 _private member_ `TAttribute<int32> UpdateRate;`
- L54 _private member_ `TAttribute<int32> FrameWidth;`
- L56 _private member_ `int32 CurrentFrameWidth;`
- L57 _private member_ `FFrameRate CurrentFrameRate;`
- L58 _private member_ `int32 CurrentFrameValue;`
- L59 _private member_ `int32 CurrentFrame;`
- L60 _private member_ `int32 CurrentOwnerIndex;`
- L69 _private member_ `TArray<FrameTimeDisplayData> DisplayData;`
- L71 _private member_ `int32 MinOldestFrameTime;`
- L72 _private member_ `int32 MaxOldestFrameTime;`
- L73 _private member_ `int32 MinNewestFrameTime;`
- L74 _private member_ `int32 MaxNewestFrameTime;`
- L76 _private member_ `const FSlateBrush* DarkBrush;`
- L77 _private member_ `const FSlateBrush* BrightBrush;`
- L79 _private member_ `const TSharedRef<FSlateFontMeasure> FontMeasureService;`
- L80 _private member_ `const FSlateFontInfo FontInfo;`
- L82 _private member_ `const FLinearColor ColorSynchronizedSamples;`
- L83 _private member_ `const FLinearColor ColorFutureSamples;`
- L84 _private member_ `const FLinearColor ColorPastSamples;`
- L86 _private member_ `TStrongObjectPtr<UTimecodeSynchronizer> TimecodeSynchronizer;`

#### enum `STimecodeSynchronizerBarWidget::Justification`  
`enum Justification`  
_L42-47_
- L44 _public enumerator_ `LeftJustification`
- L45 _public enumerator_ `CenterJustification`
- L46 _public enumerator_ `RightJustification`

#### struct `STimecodeSynchronizerBarWidget::FrameTimeDisplayData`  
`struct FrameTimeDisplayData`  
_L62-67_
- L64 _public member_ `int32 OldestFrameTime;`
- L65 _public member_ `int32 NewestFrameTime;`
- L66 _public member_ `FString Name;`

#### class `STimecodeSynchronizerWidget`  
`class STimecodeSynchronizerWidget : public SCompoundWidget`  
_L89-104_
- inherits: `SCompoundWidget`
- L92 _public function_ `SLATE_BEGIN_ARGS(STimecodeSynchronizerWidget)`
- L97 _public prototype_ `void Construct(const FArguments& InArgs, UTimecodeSynchronizer& InTimecodeSynchronizer);`
- L99 _public prototype_ `void SetUpdateRate(int32 InUpdateRate);`
- L100 _public prototype_ `void SetFrameWidth(int32 InFrameWidth);`
- L103 _private member_ `TSharedPtr<STimecodeSynchronizerBarWidget> BarWidget;`

### `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizerEditor/Public/TimecodeSynchronizerEditorModule.h` (Public)


#### class `ITimecodeSynchronizerEditorModule`  
`class ITimecodeSynchronizerEditorModule : public IModuleInterface`  
_L12-32_
- reflection: `UE_DEPRECATED(5.0, "The TimecodeSynchronizer plugin is deprecated. Please update your project to use the features of the TimedDataMonitor plugin.")`
- inherits: `IModuleInterface`
- L19 _public function_ `static inline ITimecodeSynchronizerEditorModule& Get()` — Singleton-like access to TimecodeSynchronizerEditor @return Returns TimecodeSynchronizerEditor singleton instance, loading the module on demand if needed
- L28 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L9 _macro_ `#define TIMECODESYNCHRONIZEREDITOR_MODULE_NAME TEXT("TimecodeSynchronizerEditor")`

### `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizerEditor/Public/TimecodeSynchronizerFactory.h` (Public)


#### class `UTimecodeSynchronizerFactory`  
`class UTimecodeSynchronizerFactory : public UFactory`  
_L12-19_
- reflection: `UE_DEPRECATED(5.0, "The TimecodeSynchronizer plugin is deprecated. Please update your project to use the features of the TimedDataMonitor plugin.")`
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- L17 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
