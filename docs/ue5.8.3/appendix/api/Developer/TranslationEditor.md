# Developer / TranslationEditor

- module root: `Source/Developer/TranslationEditor`
- headers: 10; symbols: 327
- symbol kinds: class=16, delegate=1, function=41, macro=3, member=135, prototype=125, struct=4, typedef=2
- DynamicallyLoadedModuleNames: DesktopPlatform, WorkspaceMenuStructure
- PrivateDependencyModuleNames: ApplicationCore, Documentation, EditorFramework, EngineSettings, GraphEditor, InputCore, Json, LocalizationCommandletExecution, LocalizationService, MessageLog, PropertyEditor, Slate, SlateCore, SourceControl, ToolMenus, UnrealEd
- PrivateIncludePathModuleNames: DesktopPlatform, LocalizationService
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Localization
- PublicIncludePathModuleNames: LevelEditor, WorkspaceMenuStructure

### `Source/Developer/TranslationEditor/Private/CustomFontColumn.h` (Private)


#### class `FCustomFontColumn`  
`class FCustomFontColumn : public IPropertyTableCustomColumn`  
_L25-74_
- inherits: `IPropertyTableCustomColumn`
- desc: A property table custom column used to display text cells in a chosen font
- L28 _public function_ `FCustomFontColumn(FSlateFontInfo InFont = FAppStyle::GetFontStyle( PropertyTableConstants::NormalFontStyle ), FOnClicked InOnChangeFontButtonClicked = NULL, FOnInt32ValueCommitted InOnFontSizeValueCommitted = NULL) : Font(InFont) , OnChangeFontButtonClicked(InOnChangeFontButtonClicked) , OnFontSizeValueCommitted(InOnFontSizeValueCommitted)`
- L35 _public prototype_ `virtual bool Supports( const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities ) const override;` — Begin IPropertyTableCustomColumn interface
- L36 _public prototype_ `virtual TSharedPtr< SWidget > CreateColumnLabel( const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style ) const override;`
- L37 _public prototype_ `virtual TSharedPtr< IPropertyTableCellPresenter > CreateCellPresenter( const TSharedRef< IPropertyTableCell >& Cell, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style ) const override;`
- L43 _private member_ `FSlateFontInfo Font;` — Font to use for this column's cells
- L46 _private member_ `TArray<FProperty*> SupportedProperties;` — List of properties that this Custom Font Column should be used to display
- L49 _private member_ `FOnClicked OnChangeFontButtonClicked;` — Function to call when Change Font button clicked
- L52 _private member_ `FOnInt32ValueCommitted OnFontSizeValueCommitted;` — Function to call when Font Size SpinBox's Value is committed
- L55 _public function_ `void SetFont(FSlateFontInfo InFont)`
- L60 _public function_ `void AddSupportedProperty(FProperty* Property)`
- L65 _public function_ `void SetOnChangeFontButtonClicked(FOnClicked InOnClicked)`
- L70 _public function_ `void SetOnFontSizeValueCommitted(FOnInt32ValueCommitted InOnFontSizeValueCommitted)`

### `Source/Developer/TranslationEditor/Private/TranslationDataManager.h` (Private)


#### class `FTranslationDataManager`  
`class FTranslationDataManager : public TSharedFromThis<FTranslationDataManager>`  
_L15-143_
- inherits: `TSharedFromThis<FTranslationDataManager>`
- L20 _public prototype_ `FTranslationDataManager(const FString& InManifestFilePath, const FString& InNativeArchiveFilePath, const FString& InArchiveFilePath);`
- L21 _public prototype_ `FTranslationDataManager(ULocalizationTarget* const LocalizationTarget, const FString& CulturetoEdit);`
- L23 _public prototype_ `virtual ~FTranslationDataManager();`
- L25 _public function_ `TArray<UTranslationUnit*>& GetAllTranslationsArray()`
- L30 _public function_ `TArray<UTranslationUnit*>& GetUntranslatedArray()`
- L35 _public function_ `TArray<UTranslationUnit*>& GetReviewArray()`
- L40 _public function_ `TArray<UTranslationUnit*>& GetCompleteArray()`
- L45 _public function_ `TArray<UTranslationUnit*>& GetSearchResultsArray()`
- L50 _public function_ `TArray<UTranslationUnit*>& GetChangedOnImportArray()`
- L59 _public prototype_ `bool WriteTranslationData(bool bForceWrite = false);` — Write the translation data in memory out to .archive file (check out the .archive file first if necessary) @param bForceWrite Whether or not to force a write even if the data hasn't changed @param return Whether or not the write succeeded (true is succeeded)
- L62 _public prototype_ `void HandlePropertyChanged(FName PropertyName);` — Delegate called when a TranslationDataObject property is changed
- L65 _public prototype_ `void PreviewAllTranslationsInEditor(ULocalizationTarget* LocalizationTarget);` — Regenerate and reload archives to reflect modifications in the UI
- L68 _public prototype_ `void PopulateSearchResultsUsingFilter(const FString& SearchFilter);` — Put items in the Search Array if they match this filter
- L71 _public prototype_ `void LoadFromArchive(TArray<UTranslationUnit*>& InTranslationUnits, bool bTrackChanges = false, bool bReloadFromFile = false);` — Load (or reload) Translations from Archive file
- L74 _public prototype_ `void GetHistoryForTranslationUnits();` — Get the history data for all translation units
- L77 _public prototype_ `void UnloadHistoryInformation();` — Unload History information (in the case we reload it)
- L80 _public prototype_ `static bool SaveSelectedTranslations(TArray<UTranslationUnit*> TranslationUnitsToSave, bool bSaveChangesToTranslationService = false);` — Save the specified translations
- L83 _public prototype_ `static void SaveSelectedTranslationsToTranslationServiceCallback(const FLocalizationServiceOperationRef& Operation, ELocalizationServiceOperationCommandResult::Type Result);` — Save the specified translations
- L86 _public function_ `bool GetLoadedSuccessfully()` — Whether or not we successfully loaded the .manifest and .archive
- L92 _private prototype_ `void Initialize();`
- L95 _private prototype_ `TSharedPtr< FInternationalizationManifest > ReadManifest ( const FString& ManifestFilePath );` — Take a path and a manifest name and return a manifest data structure
- L97 _private prototype_ `TSharedPtr< FInternationalizationArchive > ReadArchive(const FString& ArchiveFilePath);` — Retrieve an archive data structure from ArchiveFilePath
- L100 _private prototype_ `bool WriteJSONToTextFile( const FString& Output, const FString& Filename );` — Write JSON string to text file
- L103 _private prototype_ `void RemoveTranslationUnitArrayfromRoot( TArray<UTranslationUnit*>& TranslationUnits );` — Removes each UTranslationUnit in the passed array from the root set, allowing it to be garbage collected
- L106 _private member_ `TArray<UTranslationUnit*> AllTranslations;` — Arrays containing the translation data
- L107 _private member_ `TArray<UTranslationUnit*> Untranslated;`
- L108 _private member_ `TArray<UTranslationUnit*> Review;`
- L109 _private member_ `TArray<UTranslationUnit*> Complete;`
- L110 _private member_ `TArray<UTranslationUnit*> SearchResults;`
- L111 _private member_ `TArray<UTranslationUnit*> ChangedOnImport;`
- L114 _private member_ `TSharedPtr< FInternationalizationArchive > NativeArchivePtr;` — Archive for the current project and native language
- L116 _private member_ `TSharedPtr< FInternationalizationArchive > ArchivePtr;` — Archive for the current project and translation language
- L118 _private member_ `TSharedPtr< FInternationalizationManifest > ManifestAtHeadRevisionPtr;` — Manifest for the current project
- L121 _private member_ `FString ManifestName;` — Name of the manifest file
- L123 _private member_ `FString ProjectPath;` — Path to the project
- L125 _private member_ `FString ArchiveName;` — Name of the archive file
- L127 _private member_ `FString CulturePath;` — Path to the culture (language, sort of) we are targeting
- L129 _private member_ `FString OpenedManifestFilePath;` — Path to the manifest file
- L131 _private member_ `FString NativeArchiveFilePath;` — Path to the native culture's archive file
- L133 _private member_ `FString OpenedArchiveFilePath;` — Path to the archive file
- L136 _private member_ `TArray<FString> CheckedOutFiles;` — Files that are already checked out from Perforce
- L139 _private member_ `TWeakObjectPtr<ULocalizationTarget> AssociatedLocalizationTarget;` — The localization target associated with the files being used/edited, if any.
- L142 _private member_ `bool bLoadedSuccessfully;` — Whether or not we successfully loaded the .manifest and .archive

### `Source/Developer/TranslationEditor/Private/TranslationEditor.h` (Private)


#### class `FTranslationEditor`  
`class FTranslationEditor : public ITranslationEditor`  
_L22-310_
- inherits: `ITranslationEditor`
- L28 _public function_ `static TSharedRef< FTranslationEditor > Create(TSharedRef< FTranslationDataManager > DataManager, const FString& InManifestFile, const FString& InArchiveFile)` — Creates a new FTranslationEditor and calls Initialize
- L44 _public function_ `static TSharedRef< FTranslationEditor > Create(TSharedRef< FTranslationDataManager > DataManager, ULocalizationTarget* const LocalizationTarget, const FString& CultureToEdit)`
- L62 _public prototype_ `virtual ~FTranslationEditor() = default;`
- L64 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L65 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L74 _public prototype_ `void InitTranslationEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost );` — Edits the specified table @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	ObjectToEdit			The object to edit
- L77 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L78 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L79 _public prototype_ `virtual FText GetToolkitName() const override;`
- L80 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L81 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L82 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L86 _protected prototype_ `virtual void SaveAsset_Execute() override;` — Called when "Save" is clicked for this asset
- L90 _private function_ `FTranslationEditor(TSharedRef< FTranslationDataManager > InDataManager, const FString& InManifestFile, const FString& InArchiveFile, ULocalizationTarget* const LocalizationTarget) : ITranslationEditor(InManifestFile, InArchiveFile, LocalizationTarget) , DataManager(InDataManager) , SourceFont(FAppStyle::GetFontStyle( PropertyTableConstants::NormalFontStyle )) , TranslationTargetFont(FAppStyle::GetFontStyle( PropertyTableConstants::NormalFontStyle )) , SourceColumn(MakeShareable(new FCustomFontColumn(SourceFont))) , TranslationColumn(MakeShareable(new FCustomFontColumn(TranslationTargetFont))) , PreviewTextBlock(SNew(STextBlock) .Text(FText::FromString("")) .Font(TranslationTargetFont)) , NamespaceTextBlock(SNew(STextBlock) .Text(FText::FromString("")))`
- L105 _private prototype_ `void Initialize();` — Does some things we can't do in the constructor because we can't get a SharedRef to "this" there
- L108 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Untranslated( const FSpawnTabArgs& Args );` — Spawns the untranslated tab
- L110 _private prototype_ `FText GetTabLabel_Untranslated() const;` — Getter function bound to the label attribute for the untranslated tab.
- L112 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Review( const FSpawnTabArgs& Args );` — Spawns the review tab
- L114 _private prototype_ `FText GetTabLabel_Review() const;` — Getter function bound to the label attribute for the review tab.
- L116 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Completed( const FSpawnTabArgs& Args );` — Spawns the completed tab
- L118 _private prototype_ `FText GetTabLabel_Completed() const;` — Getter function bound to the label attribute for the completed tab.
- L120 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Preview( const FSpawnTabArgs& Args );` — Spawns the preview tab
- L122 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Context( const FSpawnTabArgs& Args );` — Spawns the context tab
- L124 _private prototype_ `TSharedRef<SDockTab> SpawnTab_History( const FSpawnTabArgs& Args );` — Spawns the history tab
- L126 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Search( const FSpawnTabArgs& Args );` — Spawns the search tab
- L128 _private prototype_ `TSharedRef<SDockTab> SpawnTab_ChangedOnImport(const FSpawnTabArgs& Args);` — Spawns the Changed on Import tab
- L131 _private prototype_ `void MapActions();` — Map actions for the UI_COMMANDS
- L134 _private prototype_ `void ChangeSourceFont();` — Change the font for the source language
- L137 _private function_ `FReply ChangeSourceFont_FReply()` — For button delegate
- L145 _private prototype_ `void ChangeTranslationTargetFont();` — Change the font for the target translation language
- L148 _private function_ `FReply ChangeTranslationTargetFont_FReply()` — For button delegate
- L156 _private function_ `void OnSourceFontSizeCommitt(int32 NewFontSize, ETextCommit::Type)` — Called on SpinBox OnValueCommitted
- L162 _private function_ `void OnTranslationTargetFontSizeCommitt(int32 NewFontSize, ETextCommit::Type)`
- L169 _private prototype_ `bool OpenFontPicker(const FString DefaultFile, FString& OutFile);` — Open the file dialog prompt (at the DefaultFile location) to allow the user to pick a font, then return the user's selection, and a boolean of whether something was selected
- L172 _private prototype_ `void RefreshUI();` — Reset all of the UI after a new font is chosen
- L175 _private prototype_ `void UpdateTranslationUnitSelection(TSet<TSharedRef<IPropertyTableRow>>& SelectedRows);` — Update content when a new translation unit selection is made
- L178 _private prototype_ `void UpdateUntranslatedSelection();` — Update content when a new translation unit selection is made in the Untranslated PropertyTable
- L181 _private prototype_ `void UpdateNeedsReviewSelection();` — Update content when a new translation unit selection is made in the Needs Review PropertyTable
- L184 _private prototype_ `void UpdateCompletedSelection();` — Update content when a new translation unit selection is made in the Completed PropertyTable
- L187 _private prototype_ `void UpdateSearchSelection();` — Update content when a new translation unit selection is made in the Search PropertyTable
- L190 _private prototype_ `void UpdateChangedOnImportSelection();` — Update content when a new translation unit selection is made in the ChangedOnImport PropertyTable
- L193 _private prototype_ `void UpdateContextSelection();` — Update content when a new context selection is made
- L196 _private prototype_ `void PreviewAllTranslationsInEditor_Execute();` — Called when "Preview in Editor" is clicked for this Localization Target
- L199 _private prototype_ `void ImportLatestFromLocalizationService_Execute();` — Called when "Import from Localization Service" is clicked for this Localization Target
- L202 _private prototype_ `void DownloadLatestFromLocalizationServiceComplete(const FLocalizationServiceOperationRef& Operation, ELocalizationServiceOperationCommandResult::Type Result);` — Callback for when the Localization Service operation started when "Import from Localization Service" was clicked finishes
- L205 _private prototype_ `void ExportToPortableObjectFormat_Execute();` — Called when "Export to .PO" is clicked for this Localization Target
- L208 _private prototype_ `void ImportFromPortableObjectFormat_Execute();` — Called when "Import from .PO" is clicked for this Localization Target
- L211 _private prototype_ `void ImportFromPoFile(FString FileToImport);` — Import from the specified .po file into this localization target
- L214 _private prototype_ `void OpenSearchTab_Execute();` — Open the search tab
- L217 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);` — Called when the filter text in the SearchBox is changed
- L220 _private prototype_ `void OnFilterTextCommitted(const FText& InFilterText, ETextCommit::Type CommitInfo);` — Called when text is committed to the SearchBox
- L223 _private prototype_ `FReply OnGetHistoryButtonClicked();` — Called when the get history button is clicked to retrieve history from source control
- L226 _private member_ `static const FName UntranslatedTabId;` — The tab id for the untranslated tab
- L228 _private member_ `static const FName ReviewTabId;` — The tab id for the review tab
- L230 _private member_ `static const FName CompletedTabId;` — The tab id for the completed tab
- L232 _private member_ `static const FName PreviewTabId;` — The tab id for the preview tab
- L234 _private member_ `static const FName ContextTabId;` — The tab id for the context tab
- L236 _private member_ `static const FName HistoryTabId;` — The tab id for the history tab
- L238 _private member_ `static const FName SearchTabId;` — The tab id for the search tab
- L240 _private member_ `static const FName ChangedOnImportTabId;` — The tab id for the changed on import tab
- L243 _private member_ `TWeakPtr<SDockTab> UntranslatedTab;` — The Untranslated Tab
- L245 _private member_ `TWeakPtr<SDockTab> ReviewTab;` — The Review Tab
- L247 _private member_ `TWeakPtr<SDockTab> CompletedTab;` — The Review Tab
- L249 _private member_ `TWeakPtr<SDockTab> SearchTab;` — The Search Tab
- L251 _private member_ `TWeakPtr<SDockTab> ChangedOnImportTab;` — The Changed On Import Tab
- L254 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — Search box for searching the source and translation strings
- L256 _private member_ `FString CurrentSearchFilter;` — Current search filter
- L259 _private member_ `TSharedRef< FTranslationDataManager > DataManager;` — Manages the reading and writing of data to file
- L262 _private member_ `TSharedPtr< class IPropertyTable > UntranslatedPropertyTable;` — The table of untranslated items
- L264 _private member_ `TSharedPtr< class IPropertyTable > ReviewPropertyTable;` — The table of translations to review
- L266 _private member_ `TSharedPtr< class IPropertyTable > CompletedPropertyTable;` — The table of completed translations
- L268 _private member_ `TSharedPtr< class IPropertyTable > ContextPropertyTable;` — The table of context information
- L270 _private member_ `TSharedPtr< class IPropertyTable > HistoryPropertyTable;` — The table of previous revision information
- L272 _private member_ `TSharedPtr< class IPropertyTable > SearchPropertyTable;` — The table of search results
- L274 _private member_ `TSharedPtr< class IPropertyTable > ChangedOnImportPropertyTable;` — The table of changed on import results
- L277 _private member_ `TSharedPtr< class IPropertyTableWidgetHandle > UntranslatedPropertyTableWidgetHandle;` — The slate widget table of untranslated items
- L279 _private member_ `TSharedPtr< class IPropertyTableWidgetHandle > ReviewPropertyTableWidgetHandle;` — The slate widget table of translations to review
- L281 _private member_ `TSharedPtr< class IPropertyTableWidgetHandle > CompletedPropertyTableWidgetHandle;` — The slate widget table of completed items
- L283 _private member_ `TSharedPtr< class IPropertyTableWidgetHandle > ContextPropertyTableWidgetHandle;` — The slate widget table of contexts for this item
- L285 _private member_ `TSharedPtr< class IPropertyTableWidgetHandle > HistoryPropertyTableWidgetHandle;` — The slate widget table of previous revision information
- L287 _private member_ `TSharedPtr< class IPropertyTableWidgetHandle > SearchPropertyTableWidgetHandle;` — The slate widget table of search results
- L289 _private member_ `TSharedPtr< class IPropertyTableWidgetHandle > ChangedOnImportPropertyTableWidgetHandle;` — The slate widget table of translations that changed on import
- L292 _private member_ `FSlateFontInfo SourceFont;` — Font to use for the source language
- L294 _private member_ `FSlateFontInfo TranslationTargetFont;` — Font to use for the translation target language
- L297 _private member_ `TSharedRef<FCustomFontColumn> SourceColumn;` — Custom FontColumn for columns that display source text
- L299 _private member_ `TSharedRef<FCustomFontColumn> TranslationColumn;` — Custom FontColumn for columns that display source text
- L302 _private member_ `TSharedRef<STextBlock> PreviewTextBlock;` — Text block for previewing the currently selected translation
- L304 _private member_ `TSharedRef<STextBlock> NamespaceTextBlock;` — Text block displaying the namespace of the currently selected translation unit
- L307 _private member_ `FString LastExportFilePath;` — Used to remember the location of the file the user last exported to
- L309 _private member_ `FString LastImportFilePath;` — Used to remember the location of the file the user last imported

### `Source/Developer/TranslationEditor/Private/TranslationPickerEditWindow.h` (Private)


#### class `UTranslationPickerSettings`  
`class UTranslationPickerSettings : public UObject`  
_L34-42_
- reflection: `UCLASS(config = TranslationPickerSettings)`
- inherits: `UObject`
- L41 _public member_ `bool bSubmitTranslationPickerChangesToLocalizationService;` — `UPROPERTY(config)` — Bool submit translation picker changes to Localization Service

#### class `FTranslationPickerSettingsManager`  
`class FTranslationPickerSettingsManager`  
_L44-89_
- L46 _private function_ `FTranslationPickerSettingsManager()`
- L53 _public function_ `void SaveSettings()`
- L58 _public function_ `void LoadSettings()`
- L63 _public function_ `UTranslationPickerSettings* GetSettings()`
- L73 _public function_ `static inline TSharedPtr<FTranslationPickerSettingsManager>& Get()` — Gets a reference to the translation picker manager instance. @return A reference to the translation picker manager instance.
- L85 _private member_ `static TSharedPtr<FTranslationPickerSettingsManager> TranslationPickerSettingsManagerInstance;`
- L88 _private member_ `UTranslationPickerSettings* TranslationPickerSettingsObject;` — Used to load and store settings for the Translation Picker

#### struct `FTranslationPickerTextItem`  
`struct FTranslationPickerTextItem : public FGCObject`  
_L92-143_
- inherits: `FGCObject`
- desc: A text item in the item list
- L94 _public function_ `FTranslationPickerTextItem(const FText& InText, bool bAllowEditing) : PickedText(InText), bAllowEditing(bAllowEditing)`
- L97 _public prototype_ `static TSharedPtr<FTranslationPickerTextItem> BuildTextItem(const FText& InText, bool bAllowEditing);` — Create new text item
- L99 _public function_ `inline bool operator==(const FTranslationPickerTextItem& Other) const`
- L107 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L108 _public function_ `virtual FString GetReferencerName() const override`
- L114 _public prototype_ `UTranslationUnit* GetTranslationUnitWithAnyChanges();` — Return the translation unit for this text, with any modifications
- L117 _public function_ `bool CanSave()` — Whether or not we can save
- L123 _public member_ `FText PickedText;` — The FText that we are using this widget to translate
- L126 _public member_ `bool bAllowEditing = true;` — Whether or not to show the save button
- L129 _public member_ `bool bHasRequiredLocalizationInfoForSaving = true;` — Whether or not we were able to find the necessary info for saving
- L131 _public member_ `FTextId TextId;`
- L132 _public member_ `FString SourceString;`
- L133 _public member_ `FString TranslationString;`
- L134 _public member_ `FString LocTargetName;`
- L135 _public member_ `FString LocResCultureName;`
- L136 _public member_ `FString CleanNamespace;`
- L139 _public member_ `TObjectPtr<UTranslationUnit> TranslationUnit;` — The translation we're editing represented in a UTranslationUnit object
- L142 _public member_ `TSharedPtr<SMultiLineEditableTextBox> TextBox;` — The text box for entering/modifying a translation

#### class `STranslationPickerEditWidget`  
`class STranslationPickerEditWidget : public STableRow<TSharedPtr<FTranslationPickerTextItem>>`  
_L145-157_
- inherits: `STableRow<TSharedPtr<FTranslationPickerTextItem>>`
- L149 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TSharedPtr<FTranslationPickerTextItem> InListItem);`
- L152 _private prototype_ `FReply SaveAndPreview();`
- L154 _private prototype_ `FReply CopyNamespaceAndKey();`
- L156 _private member_ `TSharedPtr<FTranslationPickerTextItem> Item;`

#### class `STranslationPickerEditWindow`  
`class STranslationPickerEditWindow : public SCompoundWidget`  
_L160-231_
- inherits: `SCompoundWidget`
- desc: Translation picker edit window to allow you to translate selected FTexts in place
- L162 _private function_ `SLATE_BEGIN_ARGS(STranslationPickerEditWindow)`
- L164 _private prototype_ `SLATE_ARGUMENT(TWeakPtr<SWindow>, ParentWindow) SLATE_END_ARGS() virtual ~STranslationPickerEditWindow();`
- L170 _private prototype_ `void Construct(const FArguments& InArgs);`
- L173 _private member_ `static const int32 DefaultEditWindowWidth;` — Default dimensions of the Translation Picker edit window (floating window also uses these sizes, so it matches roughly)
- L174 _private member_ `static const int32 DefaultEditWindowHeight;`
- L179 _private prototype_ `FReply Close();`
- L181 _private prototype_ `FReply Exit();`
- L184 _private function_ `virtual bool SupportsKeyboardFocus() const override` — We need to support keyboard focus to process the 'Esc' key
- L190 _private prototype_ `FReply RestorePicker();` — Return to picker floating window
- L193 _private prototype_ `FReply SaveAllAndExit();` — Save all translations and exit
- L196 _private prototype_ `void UpdateListItems();` — Update text list items
- L199 _private prototype_ `EActiveTimerReturnType SetFocusPostConstruct(double InCurrentTime, float InDeltaTime);` — On open, set the keyboard focus to the filter box
- L202 _private prototype_ `void FilterBox_OnTextChanged(const FText& InText);` — Filters the widgets when the user changes the search text box
- L205 _private prototype_ `void FilterBox_OnTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);` — Filters the widgets when the user hits enter or clears the search box
- L207 _private prototype_ `TSharedRef<ITableRow> TextListView_OnGenerateRow(TSharedPtr<FTranslationPickerTextItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L210 _private member_ `TSharedPtr<FTranslationPickerEditInputProcessor> InputProcessor;` — Input processor used to capture key and mouse events
- L213 _private member_ `TWeakPtr<SWindow> ParentWindow;` — Handle to the window that contains this widget
- L216 _private member_ `TSharedPtr<SBox> WindowContents;` — Contents of the window
- L219 _private member_ `TArray<TSharedPtr<FTranslationPickerTextItem>> AllItems;` — Full unfiltered list of items
- L222 _private member_ `TArray<TSharedPtr<FTranslationPickerTextItem>> FilteredItems;` — Filtered list of items
- L225 _private typedef_ `typedef SListView<TSharedPtr<FTranslationPickerTextItem>> STextListView;` — List view control
- L226 _private member_ `TSharedPtr<STextListView> TextListView;`
- L229 _private member_ `TSharedPtr<SSearchBox> FilterBox;` — Box to filter by text
- L230 _private member_ `FText FilterText;`

#### Free symbols / members of external scopes

- L31 _macro_ `#define LOCTEXT_NAMESPACE "TranslationPicker"`

### `Source/Developer/TranslationEditor/Private/TranslationPickerFloatingWindow.h` (Private)


#### class `STranslationPickerFloatingWindow`  
`class STranslationPickerFloatingWindow : public SCompoundWidget`  
_L30-106_
- inherits: `SCompoundWidget`
- desc: Translation picker floating window to show details of FText(s) under cursor, and allow in-place translation via TranslationPickerEditWindow
- L32 _private function_ `SLATE_BEGIN_ARGS(STranslationPickerFloatingWindow)`
- L34 _private prototype_ `SLATE_ARGUMENT(TWeakPtr<SWindow>, ParentWindow) SLATE_END_ARGS() virtual ~STranslationPickerFloatingWindow();`
- L40 _private prototype_ `void Construct(const FArguments& InArgs);`
- L45 _private prototype_ `FReply Close();`
- L47 _private prototype_ `FReply Exit();`
- L49 _private prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L52 _private prototype_ `void PickTextFromWidget(TSharedRef<SWidget> Widget, const FWidgetPath& Path, bool IsToolTip);` — Pull the FText reference out of an SWidget
- L55 _private prototype_ `void PickTextFromChildWidgets(TSharedRef<SWidget> Widget, const FWidgetPath& Path, bool IsToolTip);` — Pull the FText reference out of the child widgets of an SWidget
- L58 _private prototype_ `bool SwitchToEditWindow();` — Switch from floating window to edit window
- L61 _private prototype_ `static FVector2f GetNearestPoint(const FSlateRect& Rect, const FVector2f& Point, bool& Contains);` — Find the nearest point on the rectangle, and whether it is contained in the rect
- L63 _private prototype_ `static float DistSquaredToRect(const FSlateRect& Rect, const FVector2f& Point, bool& Contains);`
- L65 _private prototype_ `static bool IsNearlyEqual(const FSlateRect& RectLHS, const FSlateRect& RectRHS);`
- L67 _private prototype_ `static FSlateRect GetRect(const FPaintGeometry& Geometry);`
- L70 _private prototype_ `void UpdateListItems();` — Update text list items
- L73 _private prototype_ `void SetViewportMouseIgnoreLook(bool bLookIgnore);` — Toggle 3D viewport mouse turning
- L76 _private prototype_ `UWorld* GetWorld() const;` — Get world from editor or engine
- L78 _private prototype_ `FPaintGeometry GetPaintGeometry(const TSharedPtr<SWidget>& PickedWidget, const FWidgetPath& PickedPath, bool IsToolTip) const;`
- L80 _private prototype_ `bool GetGeometry(const TSharedRef<const SWidget>& Widget, FPaintGeometry& PaintGeometry, const FSlateLayoutTransform& TransformOffset) const;`
- L82 _private prototype_ `TSharedRef<ITableRow> TextListView_OnGenerateWidget(TSharedPtr<FTranslationPickerTextItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L85 _private member_ `TSharedPtr<FTranslationPickerInputProcessor> InputProcessor;` — Input processor used to capture key and mouse events
- L88 _private member_ `TWeakPtr<SWindow> ParentWindow;` — Handle to the window that contains this widget
- L91 _private member_ `TSharedPtr<SToolTip> WindowContents;` — Contents of the window
- L94 _private member_ `TArray<TSharedPtr<FTranslationPickerTextItem>> TextListItems;` — List items for the text list
- L97 _private typedef_ `typedef SListView<TSharedPtr<FTranslationPickerTextItem>> STextListView;` — List of all texts
- L98 _private member_ `TSharedPtr<STextListView> TextListView;`
- L100 _private member_ `FVector2f MousePosPrev;`
- L103 _private member_ `FWeakWidgetPath LastTickHoveringWidgetPath;` — The path widgets we were hovering over last tick
- L105 _private member_ `bool bMouseLookInputIgnored = false;`

#### class `STranslationPickerOverlay`  
`class STranslationPickerOverlay : public SCompoundWidget`  
_L108-122_
- inherits: `SCompoundWidget`
- L111 _public function_ `SLATE_BEGIN_ARGS(STranslationPickerOverlay)`
- L116 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L121 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`

#### Free symbols / members of external scopes

- L27 _macro_ `#define LOCTEXT_NAMESPACE "TranslationPicker"`

### `Source/Developer/TranslationEditor/Private/TranslationPickerWidget.h` (Private)


#### class `TranslationPickerManager`  
`class TranslationPickerManager`  
_L18-40_
- L21 _public member_ `static TSharedPtr<SWindow> PickerWindow;`
- L22 _public member_ `static TSharedPtr<STranslationPickerFloatingWindow> PickerWindowWidget;`
- L23 _public member_ `static TSharedPtr<STranslationPickerOverlay> MainWindowOverlay;`
- L26 _public member_ `static TArray<FTranslationPickerTextAndGeom> PickedTexts;` — The FTexts that we have found under the cursor
- L29 _public member_ `static bool bDrawBoxes;` — Whether to draw boxes in the overlay
- L31 _public function_ `static bool IsPickerWindowOpen()`
- L33 _public prototype_ `static bool OpenPickerWindow();`
- L35 _public prototype_ `static void ClosePickerWindow();`
- L37 _public prototype_ `static void ResetPickerWindow();`
- L39 _public prototype_ `static void RemoveOverlay();`

#### class `STranslationWidgetPicker`  
`class STranslationWidgetPicker : public SCompoundWidget`  
_L43-65_
- inherits: `SCompoundWidget`
- desc: Widget used to launch a 'picking' session
- L46 _public function_ `SLATE_BEGIN_ARGS(STranslationWidgetPicker)`
- L48 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L59 _private prototype_ `ECheckBoxState IsChecked() const;` — Called by slate to determine if this button should appear checked @return ECheckBoxState::Checked if it should be checked, ECheckBoxState::Unchecked if not.
- L64 _private prototype_ `void OnCheckStateChanged(const ECheckBoxState NewCheckedState);` — Called by Slate when this tool bar check box button is toggled

#### struct `FTranslationPickerTextAndGeom`  
`struct FTranslationPickerTextAndGeom`  
_L67-77_
- L69 _public member_ `FText Text;`
- L70 _public member_ `FPaintGeometry Geometry;`
- L72 _public function_ `FTranslationPickerTextAndGeom(const FText& InText, const FPaintGeometry& InGeometry) : Text(InText) , Geometry(InGeometry)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "TranslationPicker"`

### `Source/Developer/TranslationEditor/Private/TranslationUnit.h` (Private)


#### struct `FTranslationChange`  
`struct FTranslationChange`  
_L18-39_
- reflection: `USTRUCT()`
- L26 _public member_ `FString Version;` — `UPROPERTY(Category=Translation, VisibleAnywhere)` — The changelist of this change
- L30 _public member_ `FDateTime DateAndTime = FDateTime(0);` — `UPROPERTY(Category=Translation, VisibleAnywhere)` — Date of this change
- L34 _public member_ `FString Source;` — `UPROPERTY(Category=Translation, VisibleAnywhere, meta=(MultiLine=true))` — Source at time of this change
- L38 _public member_ `FString Translation;` — `UPROPERTY(Category=Translation, VisibleAnywhere, meta=(MultiLine=true))` — Translation at time of this change

#### struct `FTranslationContextInfo`  
`struct FTranslationContextInfo`  
_L42-64_
- reflection: `USTRUCT()`
- L50 _public member_ `FString Key;` — `UPROPERTY(Category=Translation, VisibleAnywhere)` — The key specified in LOCTEXT
- L54 _public member_ `FString Context;` — `UPROPERTY(Category=Translation, VisibleAnywhere)` — What file and line this translation is from
- L58 _public member_ `FString DevNotes;` — `UPROPERTY(Category=Translation, VisibleAnywhere)`
- L63 _public member_ `TArray<FTranslationChange> Changes;` — `UPROPERTY(Category=Translation, VisibleAnywhere)` — List of previous versions of the source text for this context

#### class `UTranslationUnit`  
`class UTranslationUnit : public UObject`  
_L67-129_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `UObject`
- L75 _public member_ `FString Namespace;` — `UPROPERTY(Category=Translation, VisibleAnywhere)` — The localization namespace for this translation
- L79 _public member_ `FString Key;` — `UPROPERTY(Category=Translation, VisibleAnywhere)` — The localization key for this translation
- L83 _public member_ `FString Source;` — `UPROPERTY(Category=Translation, VisibleAnywhere, meta=(MultiLine=true))` — Original text from the source language
- L87 _public member_ `FString Translation;` — `UPROPERTY(Category=Translation, EditAnywhere, meta=(MultiLine=true))` — Translations
- L91 _public member_ `TArray<FTranslationContextInfo> Contexts;` — `UPROPERTY(Category=Translation, VisibleAnywhere)` — Contexts the source was found in
- L95 _public member_ `bool HasBeenReviewed;` — `UPROPERTY(Category=Translation, EditAnywhere)` — Whether the changes have been reviewed
- L99 _public member_ `FString TranslationBeforeImport;` — `UPROPERTY(Category=Translation, EditAnywhere, meta=(MultiLine=true))` — If this Translation Unit had a different translation before import, it will be stored here
- L103 _public member_ `FString LocresPath;` — `UPROPERTY(Category = Translation, EditAnywhere)` — Optional: Which Locres File this translation is in
- L110 _public prototype_ `DECLARE_EVENT_OneParam(UTranslationUnit, FTranslationUnitPropertyChangedEvent, FName );` — Returns an event delegate that is executed when a property has changed. @return The delegate.
- L111 _public function_ `FTranslationUnitPropertyChangedEvent& OnPropertyChanged()`
- L113 _public member_ `TSharedPtr<FLocMetadataObject> KeyMetaDataObject;`
- L122 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — Called when a property on this object has been modified externally @param PropertyThatChanged the property that was modified
- L128 _private member_ `FTranslationUnitPropertyChangedEvent TranslationUnitPropertyChangedEvent;` — Holds an event delegate that is executed when a property has changed.

#### Free symbols / members of external scopes

- L110 _delegate_ `DECLARE_EVENT_OneParam(UTranslationUnit, FTranslationUnitPropertyChangedEvent, FName );` — Returns an event delegate that is executed when a property has changed. @return The delegate.

### `Source/Developer/TranslationEditor/Public/ITranslationEditor.h` (Public)


#### class `ITranslationEditor`  
`class ITranslationEditor : public FAssetEditorToolkit #else class ITranslationEditor #endif`  
_L12-53_
- inherits: `FAssetEditorToolkit`
- desc: Translation Editor public interface
- L18 _public prototype_ `static void OpenTranslationPicker();`
- L21 _public prototype_ `static void OpenTranslationEditor(const FString& InManifestFile, const FString& InNativeArchiveFile, const FString& InArchiveFileToEdit);`
- L22 _public prototype_ `static void OpenTranslationEditor(ULocalizationTarget* const LocalizationTarget, const FString& CultureToEdit);`
- L24 _public function_ `ITranslationEditor(const FString& InManifestFile, const FString& InArchiveFile, ULocalizationTarget* const InAssociatedLocalizationTarget) : ManifestFilePath(InManifestFile) , ArchiveFilePath(InArchiveFile) , AssociatedLocalizationTarget(InAssociatedLocalizationTarget)`
- L30 _public prototype_ `virtual void OnClose() override;`
- L35 _protected member_ `FString ManifestFilePath;` — The path to the manifest file being used for contexts.
- L37 _protected member_ `FString ArchiveFilePath;` — The path to the archive file being edited.
- L39 _protected member_ `TWeakObjectPtr<ULocalizationTarget> AssociatedLocalizationTarget;` — The localization target associated with the files being used/edited, if any.
- L44 _private member_ `static TMap<FString, ITranslationEditor*> OpenTranslationEditors;` — To keep track of what translation editors are open editing which manifest files
- L47 _private prototype_ `void RegisterTranslationEditor();` — Called on open to add this to our list of open translation editors
- L50 _private prototype_ `void UnregisterTranslationEditor();` — Called on close to remove this from our list of open translation editors

### `Source/Developer/TranslationEditor/Public/TranslationEditorMenu.h` (Public)


#### class `FTranslationEditorMenu`  
`class FTranslationEditorMenu`  
_L16-25_
- desc: Translation Editor menu
- L19 _public prototype_ `static void SetupTranslationEditorMenu( TSharedPtr< FExtender > Extender, FTranslationEditor& TranslationEditor);`
- L20 _public prototype_ `static void SetupTranslationEditorToolbar( TSharedPtr< FExtender > Extender, FTranslationEditor& TranslationEditor);`
- L24 _protected prototype_ `static void FillTranslationMenu( FMenuBuilder& MenuBuilder );`

#### class `FTranslationEditorCommands`  
`class FTranslationEditorCommands : public TCommands<FTranslationEditorCommands>`  
_L28-64_
- inherits: `TCommands<FTranslationEditorCommands>`
- L32 _public function_ `FTranslationEditorCommands() : TCommands<FTranslationEditorCommands>("TranslationEditor", NSLOCTEXT("Contexts", "TranslationEditor", "Translation Editor"), NAME_None, FAppStyle::GetAppStyleSetName())` — Constructor
- L38 _public member_ `TSharedPtr<FUICommandInfo> ChangeSourceFont;` — Switch fonts
- L39 _public member_ `TSharedPtr<FUICommandInfo> ChangeTranslationTargetFont;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> SaveTranslations;` — Save the translations to file
- L45 _public member_ `TSharedPtr<FUICommandInfo> PreviewAllTranslationsInEditor;` — Save the translations to file
- L48 _public member_ `TSharedPtr<FUICommandInfo> ImportLatestFromLocalizationService;` — Download and import the latest translations from the active Translation Service
- L51 _public member_ `TSharedPtr<FUICommandInfo> ExportToPortableObjectFormat;` — Export to PortableObject format (.po)
- L54 _public member_ `TSharedPtr<FUICommandInfo> ImportFromPortableObjectFormat;` — Import from PortableObject format (.po)
- L57 _public member_ `TSharedPtr<FUICommandInfo> OpenSearchTab;` — Open the tab for searching
- L60 _public member_ `TSharedPtr<FUICommandInfo> OpenTranslationPicker;` — Open the translation picker
- L63 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Source/Developer/TranslationEditor/Public/TranslationEditorModule.h` (Public)


#### class `FTranslationEditorModule`  
`class FTranslationEditorModule : public IModuleInterface #if WITH_EDITOR , public IHasMenuExtensibility #endif`  
_L14-68_
- inherits: `IModuleInterface,IHasMenuExtensibility`
- L23 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L24 _public prototype_ `virtual void ShutdownModule() override;`
- L30 _public prototype_ `virtual void OpenTranslationPicker();` — Open the translation picker. @note Alias for ITranslationEditor::OpenTranslationPicker.
- L43 _public prototype_ `virtual TSharedRef<FTranslationEditor> CreateTranslationEditor(const FString& ManifestFile, const FString& NativeArchiveFile, const FString& ArchiveFileToEdit, bool& OutLoadedSuccessfully);` — Creates an instance of translation editor object.  Only virtual so that it can be called across the DLL boundary. @param ManifestFile			The path to the manifest file to be used for contexts. @param NativeArchiveFile		The path to the archive file for the native language. @param ArchiveFileToEdit		The path to the archive file to be viewed and edited. @param OutLoadedSuccessfully	Whether or not the translation editor was able to load successfully from the .manifest and .archive files @return	The new instance of the translation editor
- L54 _public prototype_ `virtual TSharedRef<FTranslationEditor> CreateTranslationEditor(ULocalizationTarget* const LocalizationTarget, const FString& CultureToEdit, bool& OutLoadedSuccessfully);` — Creates an instance of translation editor object.  Only virtual so that it can be called across the DLL boundary. @param LocalizationTarget	The localization target whose data is to be used and edited. @param CultureToEdit			The name of a supported culture of the localization target, whose archives should be edited. @param OutLoadedSuccessfully	Whether or not the translation editor was able to load successfully from the .manifest and .archive files @return	The new instance of the translation editor
- L58 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override` — Gets the extensibility managers for outside entities to extend translation editor's menus and toolbars
- L59 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolbarExtensibilityManager()`
- L62 _public member_ `static const FName TranslationEditorAppIdentifier;` — Translation Editor app identifier string
- L65 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L66 _private member_ `TSharedPtr<FExtensibilityManager> ToolbarExtensibilityManager;`
