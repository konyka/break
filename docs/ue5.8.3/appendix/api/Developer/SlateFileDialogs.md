# Developer / SlateFileDialogs

- module root: `Source/Developer/SlateFileDialogs`
- headers: 5; symbols: 153
- symbol kinds: class=6, enum=1, enumerator=4, function=22, macro=5, member=59, prototype=53, struct=2, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, DirectoryWatcher, InputCore, Slate, SlateCore
- PrivateIncludePathModuleNames: TargetPlatform

### `Source/Developer/SlateFileDialogs/Private/SlateFileDialogsPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define HIDE_HIDDEN_FILES 1`
- L8 _macro_ `#define MAX_FILTER_LENGTH 8192`
- L9 _macro_ `#define MAX_PATH_LENGTH 8192`
- L11 _macro_ `#define ENABLE_DIRECTORY_WATCHER 1`

### `Source/Developer/SlateFileDialogs/Private/SlateFileDlgWindow.h` (Private)


#### struct `FFileEntry`  
`struct FFileEntry`  
_L34-57_
- L36 _public member_ `FString Label;`
- L37 _public member_ `FString ModDate;`
- L38 _public member_ `FString FileSize;`
- L39 _public member_ `bool bIsSelected;`
- L40 _public member_ `bool bIsDirectory;`
- L42 _public function_ `FFileEntry()`
- L44 _public function_ `FFileEntry(FString InLabel, FString InModDate, FString InFileSize, bool InIsDirectory) : Label(MoveTemp(InLabel)) , ModDate(MoveTemp(InModDate)) , FileSize(MoveTemp(InFileSize)) , bIsSelected(false) , bIsDirectory(InIsDirectory)`
- L53 _public function_ `inline static bool ConstPredicate ( const TSharedPtr<FFileEntry> Entry1, const TSharedPtr<FFileEntry> Entry2)`

#### class `FSlateFileDlgWindow`  
`class FSlateFileDlgWindow`  
_L63-100_
- L74 _public prototype_ `FSlateFileDlgWindow(FSlateFileDialogsStyle *InStyleSet);`
- L76 _public prototype_ `bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex, int32 DefaultFilterIndex = 0);`
- L80 _public prototype_ `bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames);`
- L83 _public prototype_ `bool OpenDirectoryDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, FString& OutFoldername);`
- L86 _public prototype_ `bool SaveFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex, int32 DefaultFilterIndex = 0);`
- L90 _public prototype_ `bool SaveFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames);`
- L94 _private member_ `TSharedPtr<class SSlateFileOpenDlg> DialogWidget;`
- L95 _private member_ `FString CurrentDirectory;`
- L97 _private member_ `FSlateFileDialogsStyle* StyleSet;`
- L99 _private prototype_ `void TrimFilenameFromPath(FString &Path);`

#### enum `FSlateFileDlgWindow::EResult`  
`enum EResult`  
_L66-72_
- L68 _public enumerator_ `Cancel = 0`
- L69 _public enumerator_ `Accept = 1`
- L70 _public enumerator_ `Engine = 2`
- L71 _public enumerator_ `Project = 3`

#### class `SSlateFileOpenDlg`  
`class SSlateFileOpenDlg : public SCompoundWidget`  
_L105-257_
- inherits: `SCompoundWidget`
- L123 _public function_ `SLATE_BEGIN_ARGS(SSlateFileOpenDlg) : _CurrentPath(TEXT("")), _Filters(TEXT("")), _bMultiSelectEnabled(false), _WindowTitleText(TEXT("")), _AcceptText(LOCTEXT("SlateDialogOpen","Open")), _bDirectoriesOnly(false), _bSaveFile(false), _OutNames(nullptr), _OutFilterIndex(nullptr), _ParentWindow(nullptr), _StyleSet(nullptr)`
- L137 _public prototype_ `SLATE_ARGUMENT(FString, CurrentPath) SLATE_ARGUMENT(FString, Filters) SLATE_ARGUMENT(bool, bMultiSelectEnabled) SLATE_ARGUMENT(FString, WindowTitleText) SLATE_ARGUMENT(FText, AcceptText) SLATE_ARGUMENT(bool, bDirectoriesOnly) SLATE_ARGUMENT(bool, bSaveFile) SLATE_ARGUMENT(TArray<FString>*, OutNames) SLATE_ARGUMENT(int32*, OutFilterIndex) SLATE_ARGUMENT(TWeakPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(FSlateFileDialogsStyle*, StyleSet) SLATE_END_ARGS() ~SSlateFileOpenDlg();`
- L152 _public prototype_ `void Construct(const FArguments& InArgs);`
- L153 _public function_ `FSlateFileDlgWindow::EResult GetResponse()`
- L154 _public function_ `void SetOutNames(TArray<FString>* Ptr)`
- L155 _public function_ `void SetOutFilterIndex(int32* InOutFilterIndex)`
- L156 _public function_ `void SetDefaultFilterIndex(int32 DefaultFilterIndex)`
- L157 _public prototype_ `void SetDefaultFile(FString DefaultFile);`
- L160 _private prototype_ `void OnPathClicked( const FString& CrumbData );`
- L161 _private prototype_ `TSharedRef<SWidget> OnGetCrumbDelimiterContent(const FString& CrumbData) const;`
- L162 _private prototype_ `void RebuildFileTable();`
- L163 _private prototype_ `void BuildDirectoryPath();`
- L164 _private prototype_ `void ReadDir(bool bIsRefresh = false);`
- L165 _private prototype_ `void RefreshCrumbs();`
- L166 _private prototype_ `void OnPathMenuItemClicked( FString ClickedPath );`
- L167 _private prototype_ `void OnItemSelected(TSharedPtr<FFileEntry> Item, ESelectInfo::Type SelectInfo);`
- L168 _private prototype_ `void ParseTextField(TArray<FString> &FilenameArray, FString Files);`
- L169 _private prototype_ `void Tick(const FGeometry &AllottedGeometry, const double InCurrentTime, const float InDeltaTime);`
- L171 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForList(TSharedPtr<FFileEntry> Item, const TSharedRef<STableViewBase> &OwnerTable);`
- L172 _private prototype_ `void OnItemDoubleClicked(TSharedPtr<FFileEntry> Item);`
- L174 _private prototype_ `void OnFilterChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);`
- L175 _private prototype_ `bool IsAcceptEnabled() const;`
- L176 _private prototype_ `FReply OnAcceptCancelClick(FSlateFileDlgWindow::EResult ButtonID);`
- L177 _private prototype_ `FReply OnQuickLinkClick(FSlateFileDlgWindow::EResult ButtonID);`
- L178 _private prototype_ `FReply OnDirSublevelClick(int32 Level);`
- L179 _private prototype_ `void OnDirectoryChanged(const TArray <FFileChangeData> &FileChanges);`
- L180 _private prototype_ `void OnFileNameCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L182 _private prototype_ `void OnNewDirectoryCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L183 _private prototype_ `FReply OnNewDirectoryClick();`
- L184 _private prototype_ `bool OnNewDirectoryTextChanged(const FText &InText, FText &ErrorMsg);`
- L185 _private prototype_ `FReply OnNewDirectoryAcceptCancelClick(FSlateFileDlgWindow::EResult ButtonID);`
- L187 _private prototype_ `void OnNewDirectoryClickPostTick(float);`
- L189 _private prototype_ `FReply OnGoForwardClick();`
- L190 _private prototype_ `FReply OnGoBackClick();`
- L193 _private prototype_ `void SetOutputFiles();` — Collects the output files.
- L195 _private prototype_ `bool GetFilterExtensions(TArray< FString >& OutExtensions);`
- L196 _private prototype_ `void ParseFilters();`
- L198 _private prototype_ `bool IsWildcardExtension(const FString& Extension);` — @return true if the extension filter contains a wildcard or not
- L201 _private prototype_ `TSharedPtr<FFileEntry> GetSoloDirectorySelected() const;` — @return ptr to directory if only one directory and zero files are selected, else nullptr
- L203 _private member_ `TArray< FDirNode > DirectoryNodesArray;`
- L204 _private member_ `TArray<TSharedPtr<FFileEntry>> FoldersArray;`
- L205 _private member_ `TArray<TSharedPtr<FFileEntry>> FilesArray;`
- L206 _private member_ `TArray<TSharedPtr<FFileEntry>> LineItemArray;`
- L208 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> FilterCombo;`
- L209 _private member_ `TSharedPtr<STextBlock> FilterComboBoxTitleBlock;`
- L210 _private member_ `TSharedPtr<SHorizontalBox> FilterHBox;`
- L211 _private member_ `TSharedPtr<SInlineEditableTextBlock> SaveFilenameEditBox;`
- L212 _private member_ `TSharedPtr<SInlineEditableTextBlock> NewDirectoryEditBox;`
- L213 _private member_ `TSharedPtr<SBox> SaveFilenameSizeBox;`
- L214 _private member_ `TSharedPtr<STextBlock> WindowTitle;`
- L215 _private member_ `TSharedPtr<SListView<TSharedPtr<FFileEntry>>> ListView;`
- L216 _private member_ `TSharedPtr<SBreadcrumbTrail<FString>> PathBreadcrumbTrail;`
- L218 _private member_ `TSharedPtr<SButton> NewDirCancelButton;`
- L219 _private member_ `TSharedPtr<SBox> NewDirectorySizeBox;`
- L220 _private member_ `TSharedPtr<STextBlock> DirErrorMsg;`
- L222 _private member_ `TArray<TSharedPtr<FString>> FilterNameArray;`
- L223 _private member_ `TArray<FString> FilterListArray;`
- L225 _private member_ `int32 FilterIndex;`
- L227 _private member_ `FSlateFileDlgWindow::EResult UserResponse;`
- L229 _private member_ `bool bNeedsBuilding;`
- L230 _private member_ `bool bRebuildDirPath;`
- L231 _private member_ `bool bDirectoryHasChanged;`
- L233 _private member_ `int32 DirNodeIndex;`
- L234 _private member_ `FString SaveFilename;`
- L236 _private member_ `TWeakPtr<SWindow> ParentWindow;`
- L237 _private member_ `FString CurrentPath;`
- L238 _private member_ `FString Filters;`
- L239 _private member_ `FString WindowTitleText;`
- L240 _private member_ `bool bMultiSelectEnabled;`
- L241 _private member_ `TArray<FString>* OutNames;`
- L242 _private member_ `int32* OutFilterIndex;`
- L243 _private member_ `bool bDirectoriesOnly;`
- L244 _private member_ `bool bSaveFile;`
- L245 _private member_ `FText AcceptText;`
- L246 _private member_ `FSlateFileDialogsStyle* StyleSet;`
- L248 _private member_ `IDirectoryWatcher *DirectoryWatcher;`
- L249 _private member_ `FDelegateHandle OnDialogDirectoryChangedDelegateHandle;`
- L250 _private member_ `FString RegisteredPath;`
- L251 _private member_ `FString NewDirectoryName;`
- L253 _private member_ `TArray<FString> History;`
- L254 _private member_ `int32 HistoryIndex;`
- L256 _private member_ `FDelegateHandle PostTickHandle;`

#### struct `SSlateFileOpenDlg::FDirNode`  
`struct FDirNode`  
_L108-121_
- L110 _public member_ `FString Label;`
- L111 _public member_ `TSharedPtr<STextBlock> TextBlock;`
- L112 _public member_ `TSharedPtr<SButton> Button;`
- L114 _public function_ `FDirNode()`
- L116 _public function_ `FDirNode(FString InLabel, TSharedPtr<STextBlock> InTextBlock)`

#### class `SSlateFileDialogRow`  
`class SSlateFileDialogRow : public SMultiColumnTableRow<SSlateFileDialogItemPtr>`  
_L262-390_
- inherits: `SMultiColumnTableRow<SSlateFileDialogItemPtr>`
- L266 _public function_ `SLATE_BEGIN_ARGS(SSlateFileDialogRow)`
- L267 _public function_ `SLATE_ARGUMENT(SSlateFileDialogItemPtr, DialogItem) SLATE_ARGUMENT(FSlateFileDialogsStyle *, StyleSet) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase> &InOwnerTableView)`
- L283 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override`
- L388 _private member_ `SSlateFileDialogItemPtr DialogItem;`
- L389 _private member_ `FSlateFileDialogsStyle* StyleSet;`

#### Free symbols / members of external scopes

- L27 _macro_ `#define LOCTEXT_NAMESPACE "SlateFileDialogsNamespace"`
- L59 _typedef_ `typedef TSharedPtr<FFileEntry> SSlateFileDialogItemPtr;`

### `Source/Developer/SlateFileDialogs/Public/ISlateFileDialogModule.h` (Public)


#### class `ISlateFileDialogsModule`  
`class ISlateFileDialogsModule : public IModuleInterface`  
_L11-54_
- inherits: `IModuleInterface`
- desc: Interface for slate file dialog modules.
- L17 _public prototype_ `virtual ~ISlateFileDialogsModule( ) = default;` — Virtual destructor.
- L19 _public function_ `virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex, int32 DefaultFilterIndex = 0)`
- L26 _public function_ `virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames)`
- L33 _public function_ `virtual bool OpenDirectoryDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, FString& OutFoldername)`
- L39 _public function_ `virtual bool SaveFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex, int32 DefaultFilterIndex = 0)`
- L46 _public function_ `virtual bool SaveFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames)`
- L53 _public function_ `virtual ISlateFileDialogsModule* Get()`

### `Source/Developer/SlateFileDialogs/Public/SlateFileDialogs.h` (Public)


#### class `FSlateFileDialogsModule`  
`class FSlateFileDialogsModule : public ISlateFileDialogsModule`  
_L10-43_
- inherits: `ISlateFileDialogsModule`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _public prototype_ `virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex, int32 DefaultFilterIndex = 0) override;`
- L27 _public prototype_ `virtual bool OpenDirectoryDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, FString& OutFoldername) override;`
- L31 _public prototype_ `virtual bool SaveFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex, int32 DefaultFilterIndex = 0) override;`
- L35 _public prototype_ `virtual ISlateFileDialogsModule* Get() override;`
- L37 _public function_ `FSlateFileDialogsStyle *GetFileDialogsStyle()`
- L40 _private member_ `ISlateFileDialogsModule *SlateFileDialog;`
- L42 _private member_ `FSlateFileDialogsStyle *FileDialogStyle;`

### `Source/Developer/SlateFileDialogs/Public/SlateFileDialogsStyles.h` (Public)


#### class `FSlateFileDialogsStyle`  
`class FSlateFileDialogsStyle`  
_L9-30_
- L12 _public prototype_ `static void Initialize();`
- L13 _public prototype_ `static void Shutdown();`
- L14 _public prototype_ `static const FSlateStyleSet *Get();`
- L15 _public prototype_ `static FName GetStyleSetName();`
- L17 _public function_ `static const FSlateBrush * GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL)`
- L22 _public function_ `static FSlateFontInfo GetFontStyle(FName PropertyName, const ANSICHAR* Specifier = NULL)`
- L28 _private prototype_ `static TSharedPtr<class FSlateStyleSet> Create();`
- L29 _private member_ `static TSharedPtr<class FSlateStyleSet> StyleInstance;`
