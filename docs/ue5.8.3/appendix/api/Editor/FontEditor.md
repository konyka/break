# Editor / FontEditor

- module root: `Source/Editor/FontEditor`
- headers: 8; symbols: 330
- symbol kinds: class=14, delegate=3, enum=1, enumerator=11, externvar=1, function=12, member=80, prototype=204, struct=1, typedef=3
- DynamicallyLoadedModuleNames: MainFrame, WorkspaceMenuStructure
- PrivateDependencyModuleNames: AppFramework, AssetRegistry, ContentBrowser, Core, CoreUObject, DesktopPlatform, DesktopWidgets, EditorStyle, Engine, InputCore, PropertyEditor, RenderCore, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: EditorFramework

### `Source/Editor/FontEditor/Private/FontEditor.h` (Private)


#### class `FFontEditor`  
`class FFontEditor : public IFontEditor, public FGCObject, public FNotifyHook, public FEditorUndoClient`  
_L39-203_
- inherits: `IFontEditor,FGCObject,FNotifyHook,FEditorUndoClient`
- L42 _public prototype_ `FFontEditor();`
- L44 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L45 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L48 _public prototype_ `virtual ~FFontEditor();` — Destructor
- L51 _public prototype_ `void InitFontEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* ObjectToEdit);` — Edits the specified Font object
- L54 _public prototype_ `virtual UFont* GetFont() const override;` — IFontEditor interface
- L55 _public prototype_ `virtual void SetSelectedPage(int32 PageIdx) override;`
- L56 _public prototype_ `virtual void RefreshPreview() override;`
- L59 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L60 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L61 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L62 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L65 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L66 _public function_ `virtual FString GetReferencerName() const override`
- L72 _public prototype_ `virtual bool ShouldPromptForNewFilesOnReload(const UObject& object) const override;` — Called to determine if the user should be prompted for a new file if one is missing during an asset reload
- L76 _protected prototype_ `void OnPreviewTextChanged(const FText& Text);` — Called when the preview text changes
- L79 _protected prototype_ `ECheckBoxState GetDrawFontMetricsState() const;` — Called to handle the "Draw Font Metrics" check box
- L80 _protected prototype_ `void OnDrawFontMetricsStateChanged(ECheckBoxState NewState);`
- L83 _protected prototype_ `TOptional<float> GetDrawFontScale() const;` — Called to handle the "Draw Font Scale" numeric entry box
- L84 _protected prototype_ `void OnDrawFontScaleChanged(float InNewValue, ETextCommit::Type CommitType);`
- L88 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;` — Handles any post undo cleanup of the GUI so that we don't have stale data being displayed.
- L89 _protected function_ `virtual void PostRedo(bool bSuccess) override`
- L94 _private prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, class FEditPropertyChain* PropertyThatChanged) override;` — FNotifyHook interface
- L97 _private prototype_ `void UpdateLayout();` — Update the font editor UI based on the type of font being edited
- L100 _private prototype_ `ETabSpawnerMenuType::Type GetTabSpawnerMenuType( FName InTabName ) const;` — Get the menu type to use for the given tab spawner
- L103 _private prototype_ `void CreateInternalWidgets();` — Creates all internal widgets for the tabs to point at
- L106 _private prototype_ `void ExtendToolbar();` — Builds the toolbar widget for the font editor
- L109 _private prototype_ `void BindCommands();` — Binds our UI commands to delegates
- L112 _private prototype_ `void OnUpdate();` — Toolbar command methods
- L113 _private prototype_ `bool OnUpdateEnabled() const;`
- L114 _private prototype_ `void OnUpdateAll();`
- L115 _private prototype_ `bool OnUpdateAllEnabled() const;`
- L116 _private prototype_ `void OnExport();`
- L117 _private prototype_ `bool OnExportEnabled() const;`
- L118 _private prototype_ `void OnExportAll();`
- L119 _private prototype_ `bool OnExportAllEnabled() const;`
- L120 _private prototype_ `void OnBackgroundColor();`
- L121 _private prototype_ `bool OnBackgroundColorEnabled() const;`
- L122 _private prototype_ `void OnForegroundColor();`
- L123 _private prototype_ `bool OnForegroundColorEnabled() const;`
- L124 _private prototype_ `void OnPostReimport(UObject* InObject, bool bSuccess);`
- L125 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, struct FPropertyChangedEvent& InPropertyChangedEvent);`
- L128 _private prototype_ `bool ImportPage(int32 PageNum, const TCHAR* FileName);` — Common method for replacing a font page with a new texture
- L131 _private prototype_ `TSharedRef<SDockTab> SpawnTab_TexturePagesViewport( const FSpawnTabArgs& Args );` — Spawns the text pages viewport tab
- L134 _private prototype_ `TSharedRef<SDockTab> SpawnTab_CompositeFontEditor( const FSpawnTabArgs& Args );` — Spawns the composite font editor UI
- L137 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Preview( const FSpawnTabArgs& Args );` — Spawns the preview tab
- L140 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Properties( const FSpawnTabArgs& Args );` — Spawns the properties tab
- L143 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PageProperties( const FSpawnTabArgs& Args );` — Spawns the page properties tab
- L146 _private prototype_ `void AddToSpawnedToolPanels( const FName& TabIdentifier, const TSharedRef<SDockTab>& SpawnedTab );` — Caches the specified tab for later retrieval
- L149 _private prototype_ `void OnObjectReimported(UObject* InObject);` — Callback when an object is reimported, handles steps needed to keep the editor up-to-date.
- L152 _private prototype_ `bool RecreateFontObject(const EFontCacheType NewCacheType);` — Recreate the font object so that it's using the given caching method
- L155 _private prototype_ `bool GetIsPropertyVisible(const struct FPropertyAndParent& PropertyAndParent) const;` — Check to see if the given property should be visible in the details panel
- L159 _private member_ `TObjectPtr<UFont> Font;` — The font asset being inspected
- L162 _private member_ `TMap< FName, TWeakPtr<SDockTab> > SpawnedToolPanels;` — List of open tool panels; used to ensure only one exists at any one time
- L165 _private member_ `TSharedPtr<SFontEditorViewport> FontViewport;` — Viewport
- L168 _private member_ `TSharedPtr<SCompositeFontEditor> CompositeFontEditor;` — Composite font editor UI
- L171 _private member_ `TSharedPtr<SVerticalBox> FontPreview;` — Preview tab
- L174 _private member_ `TSharedPtr<class IDetailsView> FontProperties;` — Properties tab
- L177 _private member_ `TSharedPtr<class IDetailsView> FontPageProperties;` — Page properties tab
- L180 _private member_ `TSharedPtr<SFontEditorViewport> FontPreviewWidget;` — Preview viewport widget
- L183 _private member_ `TSharedPtr<SEditableTextBox> FontPreviewText;` — Preview text
- L186 _private member_ `static FString LastPath;` — The last path exported to or from
- L189 _private member_ `TObjectPtr<UTextureExporterTGA> TGAExporter;` — The exporter to use for all font page exporting
- L192 _private member_ `TObjectPtr<UTextureFactory> Factory;` — The factory to create updated pages with
- L195 _private member_ `TOptional<EFontCacheType> CurrentEditorLayout;` — The current font editor layout (if any)
- L198 _private member_ `static const FName TexturePagesViewportTabId;` — The tab ids for the font editor
- L199 _private member_ `static const FName CompositeFontEditorTabId;`
- L200 _private member_ `static const FName PreviewTabId;`
- L201 _private member_ `static const FName PropertiesTabId;`
- L202 _private member_ `static const FName PagePropertiesTabId;`

### `Source/Editor/FontEditor/Private/FontFaceDetailsCustomization.h` (Private)


#### class `FFontFaceDetailsCustomization`  
`class FFontFaceDetailsCustomization : public IDetailCustomization`  
_L19-48_
- inherits: `IDetailCustomization`
- desc: Customize the font face asset to allow you to pick a file and store the result in the asset
- L22 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L28 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L32 _private prototype_ `FText GetFontDisplayName() const;` — Get the leaf name of the font to show in the UI.
- L35 _private prototype_ `FText GetFontDisplayToolTip() const;` — Get the full name of the font to show in the tooltip.
- L38 _private prototype_ `FReply OnBrowseFontPath();` — Called in response to the user wanting to pick a new font file.
- L41 _private prototype_ `FReply OnExportFont();` — Called in response to the user wanting to export the font to a file.
- L44 _private prototype_ `void OnFontPathPicked(const FString& InNewFontFilename);` — Called in response to a new font file being picked.
- L47 _private member_ `TArray<TWeakObjectPtr<UObject>> ObjectsBeingEdited;` — Array of objects being edited by this customization.

### `Source/Editor/FontEditor/Private/FontFaceEditor.h` (Private)


#### class `FFontFaceEditor`  
`class FFontFaceEditor : public IFontFaceEditor, public FGCObject, public FNotifyHook, public FEditorUndoClient`  
_L34-172_
- inherits: `IFontFaceEditor,FGCObject,FNotifyHook,FEditorUndoClient`
- L37 _public prototype_ `FFontFaceEditor();`
- L39 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L40 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L43 _public prototype_ `virtual ~FFontFaceEditor();` — Destructor
- L46 _public prototype_ `void InitFontFaceEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* ObjectToEdit);` — Edits the specified Font object
- L49 _public prototype_ `virtual UFontFace* GetFontFace() const override;` — IFontFaceEditor interface
- L50 _public prototype_ `virtual void RefreshPreview() override;`
- L53 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L54 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L55 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L56 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L59 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L60 _public function_ `virtual FString GetReferencerName() const override`
- L66 _public prototype_ `virtual bool ShouldPromptForNewFilesOnReload(const UObject& object) const override;` — Called to determine if the user should be prompted for a new file if one is missing during an asset reload
- L70 _protected prototype_ `void OnPreviewTextChanged(const FText& Text);` — Called when the preview text changes
- L73 _protected prototype_ `TOptional<int32> GetPreviewFontSize() const;` — Called to handle the "Preview Font Size" numeric entry box
- L74 _protected prototype_ `void OnPreviewFontSizeChanged(int32 InNewValue, ETextCommit::Type CommitType);`
- L78 _private prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, class FEditPropertyChain* PropertyThatChanged) override;` — FNotifyHook interface
- L81 _private prototype_ `void CreateInternalWidgets();` — Creates all internal widgets for the tabs to point at
- L83 _private prototype_ `void OnPostReimport(UObject* InObject, bool bSuccess);`
- L84 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, struct FPropertyChangedEvent& InPropertyChangedEvent);`
- L87 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Preview(const FSpawnTabArgs& Args);` — Spawns the preview tab
- L90 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);` — Spawns the properties tab
- L93 _private prototype_ `void AddToSpawnedToolPanels(const FName& TabIdentifier, const TSharedRef<SDockTab>& SpawnedTab);` — Caches the specified tab for later retrieval
- L96 _private prototype_ `void OnObjectReimported(UObject* InObject);` — Callback when an object is reimported, handles steps needed to keep the editor up-to-date.
- L99 _private prototype_ `bool GetIsPropertyVisible(const struct FPropertyAndParent& PropertyAndParent) const;` — Check to see if the given property should be visible in the details panel
- L120 _private member_ `TObjectPtr<UFontFace> FontFace;` — The font asset being inspected
- L123 _private member_ `TArray<TObjectPtr<UObject>> PreviewFonts;` — Virtual fonts for editor preview only
- L126 _private member_ `TArray<TObjectPtr<UFontFace>> PreviewFaces;` — Virtual font faces for editor preview only
- L129 _private member_ `TMap< FName, TWeakPtr<SDockTab> > SpawnedToolPanels;` — List of open tool panels; used to ensure only one exists at any one time
- L132 _private member_ `TSharedPtr<SVerticalBox> FontFacePreview;` — Preview tab
- L135 _private member_ `TSharedPtr<class IDetailsView> FontFaceProperties;` — Properties tab
- L138 _private member_ `TSharedPtr<SEditableTextBox> FontFacePreviewText;` — Preview text
- L141 _private member_ `TSharedPtr<SComboButton> PreviewVisibilityButton;` — Preview visibility menu button
- L144 _private member_ `TSharedPtr<STextBlock> PreviewTextBlocks[2][(int32)EPreviewRow::Count];` — Preview widgets
- L147 _private member_ `TSharedPtr<SGridPanel> PreviewTextGridPanel;` — Preview grid panel
- L150 _private member_ `TSharedPtr<STextBlock> PreviewNoteTextBlock;` — Preview note text
- L153 _private member_ `int32 PreviewFontSize = 24;` — Preview font size
- L156 _private member_ `bool PreviewRowVisibility[(int32)EPreviewRow::Count];` — Preview row user visibility filter
- L159 _private member_ `static const FName PreviewTabId;` — The tab ids for the font editor
- L160 _private member_ `static const FName PropertiesTabId;`
- L162 _private prototype_ `void ClonePreviewFontFace(TObjectPtr<UFontFace>& TargetFontFace, EFontRasterizationMode RasterizationMode, int32 DistanceFieldPpem = 0) const;`
- L163 _private prototype_ `void MakePreviewFont(TObjectPtr<UObject>& TargetObject, UFontFace* Face) const;`
- L164 _private prototype_ `bool IsFontFaceDistanceFieldEnabled() const;`
- L166 _private prototype_ `void UpdatePreviewFonts();`
- L167 _private prototype_ `void UpdatePreviewVisibility();`
- L168 _private prototype_ `void ApplyPreviewFontSize();`
- L169 _private prototype_ `void ChangePreviewRowVisibility(EPreviewRow Row);`
- L170 _private prototype_ `bool GetPreviewRowVisibility(EPreviewRow Row) const;`
- L171 _private prototype_ `float GetPreviewTextPadding() const;`

#### enum `FFontFaceEditor::EPreviewRow`  
`enum class EPreviewRow : int32`  
_L104-117_
- desc: Preview text rows that can have their visibility toggled
- L106 _public enumerator_ `Reference`
- L107 _public enumerator_ `ApproximateSdfLow`
- L108 _public enumerator_ `ApproximateSdfMedium`
- L109 _public enumerator_ `ApproximateSdfHigh`
- L110 _public enumerator_ `SdfLow`
- L111 _public enumerator_ `SdfMedium`
- L112 _public enumerator_ `SdfHigh`
- L113 _public enumerator_ `MsdfLow`
- L114 _public enumerator_ `MsdfMedium`
- L115 _public enumerator_ `MsdfHigh`
- L116 _public enumerator_ `Count`

### `Source/Editor/FontEditor/Private/SCompositeFontEditor.h` (Private)


#### class `SCompositeFontEditor`  
`class SCompositeFontEditor : public SCompoundWidget`  
_L56-128_
- inherits: `SCompoundWidget`
- L59 _public function_ `SLATE_BEGIN_ARGS(SCompositeFontEditor) : _FontEditor()`
- L64 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<IFontEditor>, FontEditor) SLATE_END_ARGS() ~SCompositeFontEditor();` — Pointer back to the Font editor tool that owns us
- L72 _public prototype_ `void Construct(const FArguments& InArgs);` — SCompoundWidget interface
- L75 _public prototype_ `void Refresh();` — Refresh the editor in response to an external change
- L78 _public prototype_ `void FlushCachedFont();` — Flush the font cache for the current font
- L81 _public prototype_ `UFont* GetFontObject() const;` — Get the root font object being edited
- L85 _private prototype_ `FCompositeFont* GetCompositeFont() const;` — Get the composite font being edited
- L88 _private prototype_ `FTypeface* GetDefaultTypeface() const;` — Get the default typeface
- L91 _private prototype_ `const FTypeface* GetConstDefaultTypeface() const;` — Get the default typeface
- L94 _private prototype_ `FTypeface* GetFallbackTypeface() const;` — Get the fallback typeface
- L97 _private prototype_ `const FTypeface* GetConstFallbackTypeface() const;` — Get the fallback typeface
- L100 _private prototype_ `FCompositeFallbackFont* GetFallbackFont() const;` — Get the fallback font
- L103 _private prototype_ `void UpdateSubTypefaceList();` — Update the list of sub-typefaces in this composite font
- L106 _private prototype_ `TSharedRef<ITableRow> MakeSubTypefaceEntryWidget(FSubTypefaceListViewEntryPtr InSubTypefaceEntry, const TSharedRef<STableViewBase>& OwnerTable);` — Make the widget for an entry in the sub-typeface entries list view
- L109 _private prototype_ `FReply OnAddSubFontFamily();` — Called in response to the "Add Sub-Font Family" button being clicked"
- L112 _private prototype_ `void OnDeleteSubFontFamily(const FSubTypefaceListViewEntryPtr& SubTypefaceEntryToRemove);` — Delete the given sub-font family from this composite font
- L115 _private member_ `TWeakPtr<IFontEditor> FontEditorPtr;` — Pointer back to the Font editor tool that owns us
- L118 _private member_ `TSharedPtr<class STypefaceEditor> DefaultTypefaceEditor;` — Widget for editing the default typeface
- L121 _private member_ `TSharedPtr<class STypefaceEditor> FallbackTypefaceEditor;` — Widget for editing the fallback typeface
- L124 _private member_ `TArray<FSubTypefaceListViewEntryPtr> SubTypefaceEntries;` — Internal list of sub-typeface pointers for the list view (generated from CompositeFontPtr->SubTypefaces)
- L127 _private member_ `TSharedPtr<SListView<FSubTypefaceListViewEntryPtr>> SubTypefaceEntriesListView;` — List view widget showing the sub-typeface editors (uses SubTypefaceEntries as its source)

#### class `STypefaceEditor`  
`class STypefaceEditor : public SCompoundWidget`  
_L130-208_
- inherits: `SCompoundWidget`
- L133 _public function_ `SLATE_BEGIN_ARGS(STypefaceEditor) : _CompositeFontEditor(nullptr) , _Typeface(nullptr) , _TypefaceDisplayName() , _OnDisplayNameCommitted() , _TypefaceDisplayNameToolTip() , _HeaderContent() , _BodyContent()`
- L144 _public prototype_ `SLATE_ARGUMENT(SCompositeFontEditor*, CompositeFontEditor) SLATE_ATTRIBUTE(FTypeface*, Typeface) SLATE_ATTRIBUTE(FText, TypefaceDisplayName) SLATE_EVENT(FOnTextCommitted, OnDisplayNameCommitted) SLATE_ATTRIBUTE(FText, TypefaceDisplayNameToolTip) SLATE_NAMED_SLOT(FArguments, HeaderContent) SLATE_NAMED_SLOT(FArguments, BodyContent) SLATE_END_ARGS() ~STypefaceEditor();` — Pointer back to the composite font editor that owns us
- L170 _public prototype_ `void Construct(const FArguments& InArgs);` — SCompoundWidget interface
- L173 _public prototype_ `void Refresh();` — Refresh the editor in response to an external change
- L176 _public prototype_ `void RequestRename();` — Request that we begin editing the display name
- L180 _private prototype_ `void UpdateFontList();` — Update the list of fonts in this typeface
- L183 _private prototype_ `TSharedRef<ITableRow> MakeTypefaceEntryWidget(FTypefaceListViewEntryPtr InTypefaceEntry, const TSharedRef<STableViewBase>& OwnerTable);` — Make the widget for an entry in the typeface entries list view
- L186 _private prototype_ `FReply OnAddFont();` — Called in response to the "Add Font" button being clicked"
- L189 _private prototype_ `void OnDeleteFont(const FTypefaceListViewEntryPtr& TypefaceEntryToRemove);` — Delete the given entry from this typeface
- L192 _private prototype_ `bool OnVerifyFontName(const FTypefaceListViewEntryPtr& TypefaceEntryBeingRenamed, const FName& NewName, FText& OutFailureReason) const;` — Verify that the name of the given typeface entry is valid
- L195 _private member_ `SCompositeFontEditor* CompositeFontEditorPtr;` — Pointer back to the composite font editor that owns us
- L198 _private member_ `TAttribute<FTypeface*> Typeface;` — Typeface to edit (may be invalid, or change in response to an undo/redo)
- L201 _private member_ `TArray<FTypefaceListViewEntryPtr> TypefaceEntries;` — Internal list of font pointers for the list view (generated from TypefacePtr->Fonts)
- L204 _private member_ `TSharedPtr<SInlineEditableTextBlock> NameEditableTextBox;` — Inline editable text for the typeface display name
- L207 _private member_ `TSharedPtr<STileView<FTypefaceListViewEntryPtr>> TypefaceEntriesTileView;` — Tile view widget showing the font entries (uses TypefaceEntries as its source)

#### class `STypefaceEntryEditor`  
`class STypefaceEntryEditor : public SCompoundWidget`  
_L210-325_
- inherits: `SCompoundWidget`
- L214 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDeleteFont, const FTypefaceListViewEntryPtr& );` — Declares a delegate that is executed when this typeface entry should be deleted
- L217 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnVerifyFontName, const FTypefaceListViewEntryPtr& , const FName& , FText& );` — Declares a delegate that is executed when this typeface entry name is changed - used to verify that the new name is valid
- L219 _public function_ `SLATE_BEGIN_ARGS(STypefaceEntryEditor) : _CompositeFontEditor(nullptr) , _TypefaceEntry() , _OnDeleteFont() , _OnVerifyFontName()`
- L227 _public prototype_ `SLATE_ARGUMENT(SCompositeFontEditor*, CompositeFontEditor) SLATE_ARGUMENT(FTypefaceListViewEntryPtr, TypefaceEntry) SLATE_EVENT(FOnDeleteFont, OnDeleteFont) SLATE_EVENT(FOnVerifyFontName, OnVerifyFontName) SLATE_END_ARGS() ~STypefaceEntryEditor();` — Pointer back to the composite font editor that owns us
- L244 _public prototype_ `void Construct(const FArguments& InArgs);` — SCompoundWidget interface
- L245 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L255 _private prototype_ `FText GetTypefaceEntryName() const;` — Get the current name of this typeface entry
- L258 _private prototype_ `void OnTypefaceEntryNameCommitted(const FText& InNewName, ETextCommit::Type InCommitType);` — Set the current name of this typeface entry
- L261 _private prototype_ `bool OnTypefaceEntryChanged(const FText& InNewName, FText& OutFailureReason) const;` — Verify the given typename entry name is valid
- L264 _private prototype_ `FString GetFontFaceAssetPath() const;` — Get the path to the font face asset used by this typeface entry
- L267 _private prototype_ `void OnFontFaceAssetChanged(const FAssetData& InAssetData);` — Update the font face asset used by this typeface entry
- L270 _private prototype_ `FReply OnBrowseTypefaceEntryFontPath();` — Open a file picker to let you pick a new font file
- L273 _private prototype_ `void OnTypefaceEntryFontPathPicked(const FString& InNewFontFilename);` — Set the current font filename (and associated font data)
- L276 _private prototype_ `FReply OnDeleteFontClicked();` — Called in response to the "Delete Font" button being clicked"
- L279 _private prototype_ `void CacheSubFaceData();` — Cache the current sub-face data for the selected font face
- L282 _private prototype_ `EVisibility GetSubFaceVisibility() const;` — Should the sub-faces combo be visible?
- L285 _private prototype_ `FText GetCurrentSubFaceSelectionDisplayName() const;` — Get the display name of the current sub-face selection
- L288 _private prototype_ `void OnSubFaceSelectionChanged(TSharedPtr<FSubFaceInfo> InSubFace, ESelectInfo::Type);` — Called when the selection of the sub-face selection combo is changed
- L291 _private prototype_ `TSharedRef<SWidget> MakeSubFaceSelectionWidget(TSharedPtr<FSubFaceInfo> InSubFace);` — Make the widget for an entry in the range selection combo
- L294 _private prototype_ `EVisibility GetUpgradeDataVisibility() const;` — Should the "Upgrade Data" button be visible?
- L297 _private prototype_ `FReply OnUpgradeDataClicked();` — Called in response to the "Upgrade Data" button being clicked"
- L300 _private prototype_ `UFontFace* SaveFontFaceAsAsset(const UFontFace* InFontFace, const TCHAR* InDefaultNameOverride);` — Saves the given font face as a real asset, and returns the asset font face instance
- L303 _private prototype_ `FSlateFontInfo GetPreviewFontStyle() const;` — Get the current font style to use for the preview text
- L306 _private member_ `SCompositeFontEditor* CompositeFontEditorPtr;` — Pointer back to the composite font editor that owns us
- L309 _private member_ `FTypefaceListViewEntryPtr TypefaceEntry;` — Typeface entry to edit (may be invalid, or change in response to an undo/redo)
- L312 _private member_ `FOnDeleteFont OnDeleteFont;` — Holds a delegate that is executed when this typeface entry should be deleted
- L315 _private member_ `FOnVerifyFontName OnVerifyFontName;` — Holds a delegate that is executed when this typeface entry name is changed - used to verify that the new name is valid
- L318 _private member_ `TSharedPtr<SInlineEditableTextBlock> NameEditableTextBox;` — Inline editable text for the font name
- L321 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FSubFaceInfo>>> SubFacesCombo;` — Sub-face selection combo box widget
- L324 _private member_ `TArray<TSharedPtr<FSubFaceInfo>> SubFacesData;` — Source data for the sub-faces combo box

#### struct `STypefaceEntryEditor::FSubFaceInfo`  
`struct FSubFaceInfo`  
_L248-252_
- L250 _public member_ `int32 Index;`
- L251 _public member_ `FText Description;`

#### class `SSubTypefaceEditor`  
`class SSubTypefaceEditor : public SCompoundWidget`  
_L327-412_
- inherits: `SCompoundWidget`
- L331 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDeleteSubFontFamily, const FSubTypefaceListViewEntryPtr& );` — Declares a delegate that is executed when this sub-typeface entry should be deleted
- L333 _public function_ `SLATE_BEGIN_ARGS(SSubTypefaceEditor) : _CompositeFontEditor(nullptr) , _SubTypeface() , _ParentTypeface(nullptr) , _OnDeleteSubFontFamily()`
- L341 _public prototype_ `SLATE_ARGUMENT(SCompositeFontEditor*, CompositeFontEditor) SLATE_ARGUMENT(FSubTypefaceListViewEntryPtr, SubTypeface) SLATE_ATTRIBUTE(const FTypeface*, ParentTypeface) SLATE_EVENT(FOnDeleteSubFontFamily, OnDeleteSubFontFamily) SLATE_END_ARGS() ~SSubTypefaceEditor();` — Pointer back to the composite font editor that owns us
- L358 _public prototype_ `void Construct(const FArguments& InArgs);` — SCompoundWidget interface
- L359 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L363 _private prototype_ `FTypeface* GetTypeface() const;` — Get the typeface used by this sub-typeface
- L366 _private prototype_ `FText GetDisplayName() const;` — Get the display name of this sub-font family
- L369 _private prototype_ `void OnDisplayNameCommitted(const FText& InNewName, ETextCommit::Type InCommitType);` — Set the display name of this sub-font family
- L372 _private prototype_ `FReply OnDeleteSubFontFamilyClicked();` — Called in response to the "Delete Sub-Font Family" button being clicked"
- L375 _private prototype_ `void UpdateCharacterRangesList();` — Update the list of character ranges for this sub-font
- L378 _private prototype_ `TSharedRef<ITableRow> MakeCharacterRangesEntryWidget(FCharacterRangeTileViewEntryPtr InCharacterRangeEntry, const TSharedRef<STableViewBase>& OwnerTable);` — Make the widget for an entry in the character ranges tile view
- L381 _private prototype_ `FReply OnAddCharacterRangeClicked();` — Called in response to the "Add Character Range" button being clicked"
- L384 _private prototype_ `FReply OnDeleteCharacterRangeClicked(FCharacterRangeTileViewEntryPtr InCharacterRangeEntry);` — Called in response to the "Delete Character Range" button being clicked"
- L387 _private prototype_ `FText GetCultures() const;` — Get the semi-colon separated cultures list
- L390 _private prototype_ `void OnCulturesCommitted(const FText& InCultures, ETextCommit::Type InCommitType);` — Set the semi-colon separated cultures list
- L393 _private member_ `SCompositeFontEditor* CompositeFontEditorPtr;` — Pointer back to the composite font editor that owns us
- L396 _private member_ `FSubTypefaceListViewEntryPtr SubTypeface;` — Sub-typeface to edit (may be invalid, or change in response to an undo/redo)
- L399 _private member_ `TAttribute<const FTypeface*> ParentTypeface;` — Parent typeface to inherit font slots from (may be invalid, or change in response to an undo/redo)
- L402 _private member_ `FOnDeleteSubFontFamily OnDeleteSubFontFamily;` — Called when this typeface entry should be deleted
- L405 _private member_ `TSharedPtr<STypefaceEditor> TypefaceEditor;` — Nested typeface editor widget
- L408 _private member_ `TArray<FCharacterRangeTileViewEntryPtr> CharacterRangeEntries;` — Internal list of sub-typeface pointers for the list view (generated from SubTypeface->CharacterRanges)
- L411 _private member_ `TSharedPtr<STileView<FCharacterRangeTileViewEntryPtr>> CharacterRangeEntriesTileView;` — Tile view widget showing the character range editors (uses CharacterRangeEntries as its source)

#### class `SCharacterRangeEditor`  
`class SCharacterRangeEditor : public SCompoundWidget`  
_L414-490_
- inherits: `SCompoundWidget`
- L417 _public function_ `SLATE_BEGIN_ARGS(SCharacterRangeEditor) : _CompositeFontEditor(nullptr) , _CharacterRange()`
- L423 _public prototype_ `SLATE_ARGUMENT(SCompositeFontEditor*, CompositeFontEditor) SLATE_ARGUMENT(FCharacterRangeTileViewEntryPtr, CharacterRange) SLATE_END_ARGS() ~SCharacterRangeEditor();` — Pointer back to the composite font editor that owns us
- L434 _public prototype_ `void Construct(const FArguments& InArgs);` — SCompoundWidget interface
- L438 _private prototype_ `FText GetRangeComponentAsTCHAR(int32 InComponentIndex) const;` — Get the given range component in its TCHAR form (0 for min, 1 for max)
- L441 _private prototype_ `FText GetRangeComponentAsHexString(int32 InComponentIndex) const;` — Get the given range component in its numerical hex form (0 for min, 1 for max)
- L444 _private prototype_ `TOptional<int32> GetRangeComponentAsOptional(int32 InComponentIndex) const;` — Get the given range component in its numeric form (0 for min, 1 for max)
- L447 _private prototype_ `int32 GetRangeComponent(const int32 InComponentIndex) const;` — Get the given range component in its numeric form (0 for min, 1 for max)
- L450 _private prototype_ `void OnRangeComponentCommittedAsTCHAR(const FText& InNewValue, ETextCommit::Type InCommitType, int32 InComponentIndex);` — Set the the given range component from its TCHAR form (0 for min, 1 for max)
- L453 _private prototype_ `void OnRangeComponentCommittedAsHexString(const FText& InNewValue, ETextCommit::Type InCommitType, int32 InComponentIndex);` — Set the the given range component from its numerical hex form (0 for min, 1 for max)
- L456 _private prototype_ `void OnRangeComponentCommittedAsNumeric(int32 InNewValue, ETextCommit::Type InCommitType, int32 InComponentIndex);` — Set the the given range component from its numerical form (0 for min, 1 for max)
- L459 _private prototype_ `void SetRangeComponent(const int32 InNewValue, const int32 InComponentIndex);` — Set the given range component from its numeric form (0 for min, 1 for max)
- L462 _private prototype_ `void CacheCurrentRangeSelection();` — Cache the current range selection (calculated based on the current range)
- L465 _private prototype_ `FText GetCurrentRangeSelectionDisplayName() const;` — Get the display name of the current range selection (or "Custom" if there is no range selection)
- L468 _private prototype_ `void OnRangeSelectionComboOpening();` — Called before the range selection combo is opened - used to sort the list of available range selections
- L471 _private prototype_ `void OnRangeSelectionChanged(TSharedPtr<FUnicodeBlockRange> InNewRangeSelection, ESelectInfo::Type);` — Called when the selection of the range selection combo is changed
- L474 _private prototype_ `TSharedRef<SWidget> MakeRangeSelectionWidget(TSharedPtr<FUnicodeBlockRange> InRangeSelection);` — Make the widget for an entry in the range selection combo
- L477 _private member_ `SCompositeFontEditor* CompositeFontEditorPtr;` — Pointer back to the composite font editor that owns us
- L480 _private member_ `FCharacterRangeTileViewEntryPtr CharacterRange;` — Character range to edit (may be invalid, or change in response to an undo/redo)
- L483 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FUnicodeBlockRange>>> RangeSelectionCombo;` — Range selection combo box widget
- L486 _private member_ `TArray<TSharedPtr<FUnicodeBlockRange>> RangeSelectionComboData;` — Source data for the range selection combo widget
- L489 _private member_ `TOptional<FUnicodeBlockRange> CurrentRangeSelection;` — The currently selected range selection preset

#### class `SFontScalingFactorEditor`  
`class SFontScalingFactorEditor : public SCompoundWidget`  
_L492-523_
- inherits: `SCompoundWidget`
- L495 _public function_ `SLATE_BEGIN_ARGS(SFontScalingFactorEditor) : _CompositeFontEditor(nullptr) , _FallbackFont(nullptr)`
- L501 _public prototype_ `SLATE_ARGUMENT(SCompositeFontEditor*, CompositeFontEditor) SLATE_ATTRIBUTE(FCompositeFallbackFont*, FallbackFont) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Pointer back to the composite font editor that owns us
- L513 _private prototype_ `TOptional<float> GetScalingFactorAsOptional() const;` — Get the scaling factor in its numeric form
- L516 _private prototype_ `void OnScalingFactorCommittedAsNumeric(float InNewValue, ETextCommit::Type InCommitType);` — Set the the scaling factor from its numerical form
- L519 _private member_ `SCompositeFontEditor* CompositeFontEditorPtr;` — Pointer back to the composite font editor that owns us
- L522 _private member_ `TAttribute<FCompositeFallbackFont*> FallbackFont;` — Fallback font that we should edit the scaling factor of (may be invalid, or change in response to an undo/redo)

#### class `SFontOverrideSelector`  
`class SFontOverrideSelector : public SCompoundWidget`  
_L525-585_
- inherits: `SCompoundWidget`
- L528 _public function_ `SLATE_BEGIN_ARGS(SFontOverrideSelector) : _CompositeFontEditor(nullptr) , _TypefaceEditor(nullptr) , _Typeface(nullptr) , _ParentTypeface(nullptr)`
- L536 _public prototype_ `SLATE_ARGUMENT(SCompositeFontEditor*, CompositeFontEditor) SLATE_ATTRIBUTE(STypefaceEditor*, TypefaceEditor) SLATE_ATTRIBUTE(FTypeface*, Typeface) SLATE_ATTRIBUTE(const FTypeface*, ParentTypeface) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Pointer back to the composite font editor that owns us
- L554 _private prototype_ `EVisibility GetAddFontOverrideVisibility() const;` — Get the visibility of the "Add Font Override" combo button
- L557 _private prototype_ `bool IsFontOverrideComboEnabled() const;` — True if the font override combo should be enabled (due to still having parent fonts that can be overridden in this sub-font)
- L560 _private prototype_ `void OnAddFontOverrideComboOpening();` — Called before the font override combo is opened - used to update the list of available font overrides
- L563 _private prototype_ `void OnAddFontOverrideSelectionChanged(TSharedPtr<FName> InNewSelection, ESelectInfo::Type);` — Called when the selection of the font override combo is changed
- L566 _private prototype_ `TSharedRef<SWidget> MakeAddFontOverrideWidget(TSharedPtr<FName> InFontEntry);` — Make the widget for an entry in the font override combo
- L569 _private member_ `SCompositeFontEditor* CompositeFontEditorPtr;` — Pointer back to the composite font editor that owns us
- L572 _private member_ `TAttribute<STypefaceEditor*> TypefaceEditor;` — Pointer back to the typeface editor that owns us
- L575 _private member_ `TAttribute<FTypeface*> Typeface;` — Typeface that we should edit the fonts on (may be invalid, or change in response to an undo/redo)
- L578 _private member_ `TAttribute<const FTypeface*> ParentTypeface;` — Parent typeface to override font slots from (may be invalid, or change in response to an undo/redo)
- L581 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FName>>> FontOverrideCombo;` — Font override combo box widget
- L584 _private member_ `TArray<TSharedPtr<FName>> FontOverrideComboData;` — Source data for the font override combo widget

#### Free symbols / members of external scopes

- L50 _typedef_ `typedef TSharedPtr<FTypefaceListViewEntry> FTypefaceListViewEntryPtr;`
- L52 _typedef_ `typedef TSharedPtr<FSubTypefaceListViewEntry> FSubTypefaceListViewEntryPtr;`
- L54 _typedef_ `typedef TSharedPtr<FCharacterRangeTileViewEntry> FCharacterRangeTileViewEntryPtr;`
- L214 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDeleteFont, const FTypefaceListViewEntryPtr& );` — Declares a delegate that is executed when this typeface entry should be deleted
- L217 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnVerifyFontName, const FTypefaceListViewEntryPtr& , const FName& , FText& );` — Declares a delegate that is executed when this typeface entry name is changed - used to verify that the new name is valid
- L331 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDeleteSubFontFamily, const FSubTypefaceListViewEntryPtr& );` — Declares a delegate that is executed when this sub-typeface entry should be deleted

### `Source/Editor/FontEditor/Private/SFontEditorViewport.h` (Private)


#### class `SFontEditorViewport`  
`class SFontEditorViewport : public SCompoundWidget`  
_L23-91_
- inherits: `SCompoundWidget`
- L26 _public function_ `SLATE_BEGIN_ARGS( SFontEditorViewport ) : _IsPreview(false)`
- L30 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<IFontEditor>, FontEditor) SLATE_ARGUMENT(bool, IsPreview) SLATE_END_ARGS() ~SFontEditorViewport();`
- L38 _public prototype_ `void Construct(const FArguments& InArgs);` — SCompoundWidget interface
- L41 _public prototype_ `void RefreshViewport();` — Refreshes the viewport
- L44 _public prototype_ `int32 GetCurrentSelectedPage() const;` — Accessors
- L45 _public prototype_ `void SetPreviewText(const FText& PreviewText);`
- L46 _public prototype_ `void SetPreviewBackgroundColor(const FColor& BackgroundColor);`
- L47 _public prototype_ `const FColor& GetPreviewBackgroundColor() const;`
- L48 _public prototype_ `void SetPreviewForegroundColor(const FColor& ForgroundColor);`
- L49 _public prototype_ `const FColor& GetPreviewForegroundColor() const;`
- L50 _public prototype_ `void SetPreviewFontScale(float InScale);`
- L51 _public prototype_ `float GetPreviewFontScale() const;`
- L52 _public prototype_ `void SetPreviewFontMetrics(const bool InDrawFontMetrics);`
- L53 _public prototype_ `bool GetPreviewFontMetrics() const;`
- L54 _public prototype_ `TWeakPtr<IFontEditor> GetFontEditor() const;`
- L55 _public prototype_ `bool IsPreviewViewport() const;`
- L56 _public prototype_ `TSharedPtr<FSceneViewport> GetViewport() const;`
- L57 _public prototype_ `TSharedPtr<SViewport> GetViewportWidget() const;`
- L58 _public prototype_ `TSharedPtr<SScrollBar> GetVerticalScrollBar() const;`
- L59 _public prototype_ `TSharedPtr<SScrollBar> GetHorizontalScrollBar() const;`
- L63 _protected prototype_ `EVisibility GetViewportVerticalScrollBarVisibility() const;` — Returns the visibility of the viewport scrollbars
- L64 _protected prototype_ `EVisibility GetViewportHorizontalScrollBarVisibility() const;`
- L67 _protected prototype_ `void OnViewportVerticalScrollBarScrolled(float InScrollOffsetFraction);` — Called when the viewport scrollbars are scrolled
- L68 _protected prototype_ `void OnViewportHorizontalScrollBarScrolled(float InScrollOffsetFraction);`
- L72 _private member_ `TWeakPtr<IFontEditor> FontEditorPtr;` — Pointer back to the Font editor tool that owns us
- L75 _private member_ `bool bIsPreview;` — If true, this is a viewport for the font editor's preview tab
- L78 _private member_ `TSharedPtr<FFontEditorViewportClient> ViewportClient;` — Level viewport client
- L81 _private member_ `TSharedPtr<FSceneViewport> Viewport;` — Slate viewport for rendering and I/O
- L84 _private member_ `TSharedPtr<SViewport> ViewportWidget;` — Viewport widget
- L87 _private member_ `TSharedPtr<SScrollBar> FontViewportVerticalScrollBar;` — Vertical scrollbar
- L90 _private member_ `TSharedPtr<SScrollBar> FontViewportHorizontalScrollBar;` — Horizontal scrollbar

### `Source/Editor/FontEditor/Public/FontEditorModule.h` (Public)


#### class `IFontEditorModule`  
`class IFontEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L25-34_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- L30 _public prototype_ `virtual TSharedRef<IFontEditor> CreateFontEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UFont* Font ) = 0;` — Creates a new Font editor
- L33 _public prototype_ `virtual TSharedRef<IFontFaceEditor> CreateFontFaceEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UFontFace* FontFace ) = 0;` — Creates a new Font Face editor

#### Free symbols / members of external scopes

- L18 _externvar_ `extern const FName FontEditorAppIdentifier;`

### `Source/Editor/FontEditor/Public/IFontEditor.h` (Public)


#### class `IFontEditor`  
`class IFontEditor : public FAssetEditorToolkit`  
_L14-25_
- inherits: `FAssetEditorToolkit`
- L18 _public prototype_ `virtual UFont* GetFont() const = 0;` — Returns the font asset being inspected by the font editor
- L21 _public prototype_ `virtual void SetSelectedPage(int32 PageIdx) = 0;` — Assigns a font texture object to the page properties control when a new page is selected
- L24 _public prototype_ `virtual void RefreshPreview() = 0;` — Refresh the preview viewport

### `Source/Editor/FontEditor/Public/IFontFaceEditor.h` (Public)


#### class `IFontFaceEditor`  
`class IFontFaceEditor : public FAssetEditorToolkit`  
_L14-22_
- inherits: `FAssetEditorToolkit`
- L18 _public prototype_ `virtual UFontFace* GetFontFace() const = 0;` — Returns the font face asset being inspected by the font face editor
- L21 _public prototype_ `virtual void RefreshPreview() = 0;` — Refresh the preview viewport
