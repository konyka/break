# Plugins / ToolPresetEditor

- module root: `Plugins/Experimental/ToolPresets/Source/ToolPresetEditor`
- headers: 4; symbols: 119
- symbol kinds: class=5, enum=1, enumerator=3, externvar=1, function=14, macro=1, member=48, prototype=44, struct=2
- PrivateDependencyModuleNames: ApplicationCore, AssetTools, ContentBrowser, ContentBrowserData, CoreUObject, DeveloperSettings, EditorConfig, EditorFramework, EditorStyle, Engine, InputCore, Projects, Slate, SlateCore, ToolPresetAsset, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/ToolPresets/Source/ToolPresetEditor/Private/ToolPresetEditorStyle.h` (Private)


#### class `FToolPresetEditorStyle`  
`class FToolPresetEditorStyle`  
_L9-28_
- L12 _public prototype_ `static void Initialize();`
- L14 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static TSharedPtr< class ISlateStyle > Get();`
- L18 _public prototype_ `static FName GetStyleSetName();`
- L21 _public prototype_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = nullptr);` — use to access icons defined by the style set by name, eg GetBrush("BrushFalloffIcons.Smooth")
- L24 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L27 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;`

### `Plugins/Experimental/ToolPresets/Source/ToolPresetEditor/Private/Widgets/SToolPresetManager.h` (Private)


#### class `SToolPresetManager`  
`class SToolPresetManager : public SCompoundWidget`  
_L27-254_
- inherits: `SCompoundWidget`
- desc: Implements the preset manager panel.
- L152 _public function_ `SLATE_BEGIN_ARGS(SToolPresetManager)`
- L155 _public prototype_ `virtual ~SToolPresetManager();`
- L162 _public prototype_ `void Construct( const FArguments& InArgs );` — Construct this widget @param InArgs The declaration data for this widget.
- L165 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L169 _private prototype_ `void BindCommands();`
- L171 _private prototype_ `void RegeneratePresetTrees();`
- L173 _private prototype_ `int32 GetTotalPresetCount() const;`
- L175 _private prototype_ `TSharedRef<ITableRow> HandleTreeGenerateRow(TSharedPtr<FToolPresetViewEntry> TreeEntry, const TSharedRef<STableViewBase>& OwnerTable);`
- L176 _private prototype_ `void HandleTreeGetChildren(TSharedPtr<FToolPresetViewEntry> TreeEntry, TArray< TSharedPtr<FToolPresetViewEntry> >& ChildrenOut);`
- L177 _private prototype_ `void HandleTreeSelectionChanged(TSharedPtr<FToolPresetViewEntry> TreeEntry, ESelectInfo::Type);`
- L178 _private prototype_ `void HandleUserTreeSelectionChanged(TSharedPtr<FToolPresetViewEntry> TreeEntry, ESelectInfo::Type);`
- L179 _private prototype_ `void HandleEditorTreeSelectionChanged(TSharedPtr<FToolPresetViewEntry> TreeEntry, ESelectInfo::Type);`
- L180 _private prototype_ `EVisibility ProjectPresetCollectionsVisibility() const;`
- L182 _private prototype_ `TSharedPtr<SWidget> OnGetPresetContextMenuContent() const;`
- L183 _private prototype_ `TSharedPtr<SWidget> OnGetCollectionContextMenuContent() const;`
- L185 _private prototype_ `void GeneratePresetList(TSharedPtr<FToolPresetViewEntry> TreeEntry);`
- L186 _private prototype_ `TSharedRef<ITableRow> HandleListGenerateRow(TSharedPtr<FToolPresetViewEntry> TreeEntry, const TSharedRef<STableViewBase>& OwnerTable);`
- L187 _private prototype_ `void HandleListSelectionChanged(TSharedPtr<FToolPresetViewEntry> TreeEntry, ESelectInfo::Type SelectInfo);`
- L189 _private prototype_ `bool EditAreaEnabled() const;`
- L190 _private prototype_ `void SetCollectionEnabled(TSharedPtr<FToolPresetViewEntry> TreeEntry, ECheckBoxState State);`
- L191 _private prototype_ `void DeletePresetFromCollection(TSharedPtr< FToolPresetViewEntry > Entry);`
- L193 _private prototype_ `void CollectionRenameStarted(TSharedPtr<FToolPresetViewEntry> TreeEntry, TSharedPtr<SEditableTextBox> RenameWidget);`
- L194 _private prototype_ `void CollectionRenameEnded(TSharedPtr<FToolPresetViewEntry> TreeEntry, const FText& NewText);`
- L196 _private prototype_ `void DeleteSelectedUserPresetCollection();`
- L197 _private prototype_ `void AddNewUserPresetCollection();`
- L199 _private prototype_ `void SetPresetLabel(TSharedPtr< FToolPresetViewEntry >, FText InLabel);`
- L200 _private prototype_ `void SetPresetTooltip(TSharedPtr< FToolPresetViewEntry >, FText InTooltip);`
- L202 _private prototype_ `const FSlateBrush* GetProjectCollectionsExpanderImage() const;`
- L203 _private prototype_ `const FSlateBrush* GetUserCollectionsExpanderImage() const;`
- L204 _private prototype_ `const FSlateBrush* GetExpanderImage(TSharedPtr<SWidget> ExpanderWidget, bool bIsUserCollections) const;`
- L206 _private prototype_ `UInteractiveToolsPresetCollectionAsset* GetCollectionFromEntry(TSharedPtr<FToolPresetViewEntry> Entry);`
- L207 _private prototype_ `void SaveIfDefaultCollection(TSharedPtr<FToolPresetViewEntry> Entry);`
- L209 _private prototype_ `void OnDeleteClicked();`
- L210 _private prototype_ `bool CanDelete();`
- L212 _private prototype_ `void OnRenameClicked();`
- L213 _private prototype_ `bool CanRename();`
- L216 _private member_ `TSharedPtr<FUICommandList> UICommandList;`
- L218 _private member_ `TWeakObjectPtr<UToolPresetUserSettings> UserSettings;`
- L220 _private member_ `TWeakPtr< SListView<TSharedPtr<FToolPresetViewEntry> > > LastFocusedList;`
- L222 _private member_ `bool bAreProjectCollectionsExpanded = true;`
- L223 _private member_ `TSharedPtr<SButton> ProjectCollectionsExpander;`
- L224 _private member_ `TArray< TSharedPtr< FToolPresetViewEntry > > ProjectCollectionsDataList;`
- L225 _private member_ `TSharedPtr<STreeView<TSharedPtr<FToolPresetViewEntry> > > ProjectPresetCollectionTreeView;`
- L227 _private member_ `bool bAreUserCollectionsExpanded = true;`
- L228 _private member_ `TSharedPtr<SButton> UserCollectionsExpander;`
- L229 _private member_ `TArray< TSharedPtr< FToolPresetViewEntry > > UserCollectionsDataList;`
- L230 _private member_ `TSharedPtr<STreeView<TSharedPtr<FToolPresetViewEntry> > > UserPresetCollectionTreeView;`
- L232 _private member_ `TArray< TSharedPtr< FToolPresetViewEntry > > EditorCollectionsDataList;`
- L233 _private member_ `TSharedPtr<STreeView<TSharedPtr<FToolPresetViewEntry> > > EditorPresetCollectionTreeView;`
- L236 _private member_ `TArray< TSharedPtr< FToolPresetViewEntry > > PresetDataList;`
- L237 _private member_ `TSharedPtr<SListView<TSharedPtr<FToolPresetViewEntry> > > PresetListView;`
- L239 _private member_ `int32 TotalPresetCount = 0;`
- L240 _private member_ `bool bHasActiveCollection = false;`
- L241 _private member_ `bool bHasPresetsInCollection = false;`
- L242 _private member_ `FText ActiveCollectionLabel;`
- L243 _private member_ `bool bIsActiveCollectionEnabled = false;`
- L245 _private member_ `TSharedPtr<SSplitter> Splitter;`
- L247 _private member_ `TSharedPtr<SVerticalBox> EditPresetArea;`
- L248 _private member_ `TSharedPtr<SEditableTextBox> EditPresetLabel;`
- L249 _private member_ `TSharedPtr<SEditableTextBox> EditPresetTooltip;`
- L250 _private member_ `TSharedPtr<FToolPresetViewEntry> ActivePresetToEdit;`
- L252 _private member_ `TSharedPtr<SPositiveActionButton> AddUserPresetButton;`
- L253 _private member_ `TSharedPtr<SNegativeActionButton> DeleteUserPresetButton;`

#### struct `SToolPresetManager::FToolPresetCollectionInfo`  
`struct FToolPresetCollectionInfo`  
_L30-38_
- L32 _public member_ `FSoftObjectPath PresetCollectionPath;`
- L33 _public member_ `bool bCollectionEnabled;`
- L35 _public function_ `FToolPresetCollectionInfo(FSoftObjectPath InPresetCollectionPath, bool bInEnabled) : PresetCollectionPath(InPresetCollectionPath), bCollectionEnabled(bInEnabled)`

#### struct `SToolPresetManager::FToolPresetViewEntry`  
`struct FToolPresetViewEntry`  
_L41-150_
- L50 _public member_ `EEntryType EntryType;`
- L53 _public member_ `bool bEnabled = false;` — Used for Collections/Tool Entries
- L54 _public member_ `FSoftObjectPath CollectionPath;`
- L55 _public member_ `bool bIsDefaultCollection = false;`
- L56 _public member_ `bool bIsRenaming = false;`
- L57 _public member_ `FText EntryLabel;`
- L58 _public member_ `FSlateBrush EntryIcon;`
- L59 _public member_ `int32 Count = 0;`
- L62 _public member_ `FString ToolName = "";` — Used for Preset/Tool entries
- L63 _public member_ `int32 PresetIndex = 0;`
- L64 _public member_ `FString PresetLabel = "";`
- L65 _public member_ `FString PresetTooltip = "";`
- L67 _public member_ `TSharedPtr< FToolPresetViewEntry> Parent;`
- L68 _public member_ `TArray<TSharedPtr< FToolPresetViewEntry> > Children;`
- L71 _public function_ `FToolPresetViewEntry(bool bEnabledIn, FSoftObjectPath CollectionPathIn, FText EntryLabelIn, int32 CountIn) : EntryType(EEntryType::Collection), bEnabled(bEnabledIn), CollectionPath(CollectionPathIn), EntryLabel(EntryLabelIn), Count(CountIn)` — Collection Constructor
- L80 _public function_ `FToolPresetViewEntry(FText EntryLabelIn, FSlateBrush EntryIconIn, FSoftObjectPath CollectionPathIn, FString ToolNameIn, int32 CountIn) : EntryType(EEntryType::Tool), CollectionPath(CollectionPathIn), EntryLabel(EntryLabelIn), EntryIcon(EntryIconIn), Count(CountIn), ToolName(ToolNameIn)` — Tool Constructor
- L90 _public function_ `FToolPresetViewEntry(FString ToolNameIn, int32 PresetIndexIn, FString PresetLabelIn, FString PresetTooltipIn, FText EntryLabelIn) : EntryType(EEntryType::Preset), EntryLabel(EntryLabelIn), ToolName(ToolNameIn), PresetIndex(PresetIndexIn), PresetLabel(PresetLabelIn), PresetTooltip(PresetTooltipIn)` — Preset Constructor
- L99 _public function_ `bool HasSameMetadata(FToolPresetViewEntry& Other)`
- L119 _public function_ `bool operator==(FToolPresetViewEntry& Other)`
- L141 _public function_ `FToolPresetViewEntry& Root()`

#### enum `SToolPresetManager::FToolPresetViewEntry::EEntryType`  
`enum class EEntryType : uint8`  
_L43-48_
- L45 _public enumerator_ `Collection`
- L46 _public enumerator_ `Tool`
- L47 _public enumerator_ `Preset`

### `Plugins/Experimental/ToolPresets/Source/ToolPresetEditor/Public/IToolPresetEditorModule.h` (Public)


#### class `IToolPresetEditorModule`  
`class IToolPresetEditorModule : public IModuleInterface`  
_L11-20_
- inherits: `IModuleInterface`
- L14 _public function_ `static IToolPresetEditorModule& Get()`
- L19 _public prototype_ `virtual void ExecuteOpenPresetEditor() = 0;`

#### Free symbols / members of external scopes

- L9 _externvar_ `extern const FName PresetEditorTabName;`

### `Plugins/Experimental/ToolPresets/Source/ToolPresetEditor/Public/ToolPresetSettings.h` (Public)


#### class `UToolPresetUserSettings`  
`class UToolPresetUserSettings : public UEditorConfigBase`  
_L19-41_
- reflection: `UCLASS(MinimalAPI, EditorConfig = "UToolPresetUserSettings")`
- inherits: `UEditorConfigBase`
- desc: Implements the settings for the PresetEditor.
- L25 _public member_ `TSet<FSoftObjectPath> EnabledPresetCollections;` — `UPROPERTY(EditAnywhere, Category = "Interactive Tool Presets|Collections", meta = (EditorConfig, AllowedClasses = "/Script/ToolPresetAsset.InteractiveToolsPresetCollectionAsset"))`
- L34 _public member_ `bool bDefaultCollectionEnabled = true;` — `UPROPERTY(EditAnywhere, Category = "Interactive Tool Presets|Collections", meta = (EditorConfig))`
- L36 _public prototype_ `static void Initialize();`
- L37 _public prototype_ `static UToolPresetUserSettings* Get();`
- L40 _private member_ `static TObjectPtr<UToolPresetUserSettings> Instance;`

#### class `UToolPresetProjectSettings`  
`class UToolPresetProjectSettings : public UDeveloperSettings`  
_L48-67_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UDeveloperSettings`
- desc: Implements the settings for the Tool Project Preset Collections.
- L56 _public function_ `virtual FName GetContainerName() const override`
- L57 _public function_ `virtual FName GetCategoryName() const override`
- L58 _public function_ `virtual FName GetSectionName() const override`
- L60 _public function_ `virtual FText GetSectionText() const override`
- L61 _public function_ `virtual FText GetSectionDescription() const override`
- L66 _public member_ `TSet<FSoftObjectPath> LoadedPresetCollections;` — `UPROPERTY(config, EditAnywhere, Category = "Interactive Tool Presets|Collections", meta = (AllowedClasses = "/Script/ToolPresetAsset.InteractiveToolsPresetCollectionAsset"))` — Controls which preset collection assets are to be loaded for this project.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TOOLPRESETEDITOR_API`
