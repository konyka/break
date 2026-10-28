# Editor / SourceControlWindows

- module root: `Source/Editor/SourceControlWindows`
- headers: 11; symbols: 676
- symbol kinds: class=19, delegate=6, enum=6, enumerator=24, function=82, macro=1, member=177, namespace=14, prototype=324, struct=17, typedef=6
- PrivateDependencyModuleNames: AssetDefinition, AssetTools, Core, CoreUObject, EditorFramework, Engine, InputCore, Projects, Slate, SlateCore, SourceControl, ToolMenus, ToolWidgets, UncontrolledChangelists, UnrealEd, UnsavedAssetsTracker, WorkspaceMenuStructure

### `Source/Editor/SourceControlWindows/Private/SSourceControlChangelistRows.h` (Private)


#### enum `SourceControlFileViewColumn::EPathFlags`  
`enum class EPathFlags`  
_L103-109_
- L105 _public enumerator_ `Default = 0`
- L107 _public enumerator_ `ShowingPackageName = 1 << 0`
- L108 _public enumerator_ `ShowingVersePath = 1 << 1`

#### class `SChangelistTableRow`  
`class SChangelistTableRow : public STableRow<TSharedPtr<IChangelistTreeItem>>`  
_L119-157_
- inherits: `STableRow<TSharedPtr<IChangelistTreeItem>>`
- desc: Displays a changed list row (icon, cl number, description)
- L122 _public function_ `SLATE_BEGIN_ARGS(SChangelistTableRow) : _TreeItemToVisualize() , _HighlightText() , _OnPostDrop()`
- L139 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwner);` — Construct child widgets that comprise this widget. @param InArgs Declaration from which to construct this widget.
- L141 _public prototype_ `FText GetChangelistText() const;`
- L142 _public prototype_ `FText GetChangelistDescriptionText() const;`
- L143 _public prototype_ `FText GetChangelistDescriptionSingleLineText() const;`
- L145 _public prototype_ `static void PopulateSearchString(const FChangelistTreeItem& Item, TArray<FString>& OutStrings);`
- L149 _protected prototype_ `virtual FReply OnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L153 _private member_ `FChangelistTreeItem* TreeItem;` — The info about the widget that we are visualizing.
- L156 _private member_ `FSimpleDelegate OnPostDrop;` — Delegate invoked once the drag and drop operation finished.

#### class `SUncontrolledChangelistTableRow`  
`class SUncontrolledChangelistTableRow : public STableRow<FChangelistTreeItemPtr>`  
_L161-197_
- inherits: `STableRow<FChangelistTreeItemPtr>`
- desc: Displays an uncontrolled changed list (icon, cl name, description)
- L164 _public function_ `SLATE_BEGIN_ARGS(SUncontrolledChangelistTableRow) : _TreeItemToVisualize() , _HighlightText() , _OnPostDrop()`
- L181 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwner);` — Construct child widgets that comprise this widget. @param InArgs Declaration from which to construct this widget.
- L183 _public prototype_ `FText GetChangelistText() const;`
- L185 _public prototype_ `static void PopulateSearchString(const FUncontrolledChangelistTreeItem& Item, TArray<FString>& OutStrings);`
- L189 _protected prototype_ `virtual FReply OnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L193 _private member_ `FUncontrolledChangelistTreeItem* TreeItem;` — The info about the widget that we are visualizing.
- L196 _private member_ `FSimpleDelegate OnPostDrop;` — Invoked once a drag and drop operation completes.

#### class `SUnsavedAssetsTableRow`  
`class SUnsavedAssetsTableRow : public STableRow<FChangelistTreeItemPtr>`  
_L200-209_
- inherits: `STableRow<FChangelistTreeItemPtr>`
- desc: Displays a block for unsaved assets with icon and count
- L208 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwner);` — Construct child widgets that comprise this widget. @param InArgs Declaration from which to construct this widget.

#### class `SFileTableRow`  
`class SFileTableRow : public SMultiColumnTableRow<FChangelistTreeItemPtr>`  
_L212-264_
- inherits: `SMultiColumnTableRow<FChangelistTreeItemPtr>`
- desc: Display information about a file (icon, name, location, type, etc.)
- L215 _public function_ `SLATE_BEGIN_ARGS(SFileTableRow) : _TreeItemToVisualize(nullptr) , _HighlightText() , _PathFlags(SourceControlFileViewColumn::EPathFlags::Default)`
- L233 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwner);` — Construct child widgets that comprise this widget. @param InArgs Declaration from which to construct this widget.
- L236 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — SMultiColumnTableRow overrides
- L238 _public prototype_ `ECheckBoxState GetCheckBoxState() const;`
- L239 _public prototype_ `void SetCheckBoxState(ECheckBoxState NewState);`
- L240 _public prototype_ `FText GetDisplayName() const;`
- L241 _public prototype_ `FText GetFilename() const;`
- L242 _public prototype_ `FText GetDisplayPath() const;`
- L243 _public prototype_ `FText GetDisplayType() const;`
- L244 _public prototype_ `FSlateColor GetDisplayColor() const;`
- L245 _public prototype_ `FText GetLastModifiedTimestamp() const;`
- L246 _public prototype_ `FText GetCheckedOutByUser() const;`
- L248 _public prototype_ `static void PopulateSearchString(const FFileTreeItem& Item, SourceControlFileViewColumn::EPathFlags PathFlags, TArray<FString>& OutStrings);`
- L252 _protected prototype_ `virtual void OnDragEnter(FGeometry const& InGeometry, FDragDropEvent const& InDragDropEvent) override;`
- L253 _protected prototype_ `virtual void OnDragLeave(FDragDropEvent const& InDragDropEvent) override;`
- L258 _private member_ `FFileTreeItem* TreeItem;` — The info about the widget that we are visualizing.
- L261 _private member_ `TAttribute<FText> HighlightText;` — The text to highlight
- L263 _private member_ `TAttribute<SourceControlFileViewColumn::EPathFlags> PathFlags;`

#### class `SShelvedFilesTableRow`  
`class SShelvedFilesTableRow : public STableRow<TSharedPtr<IChangelistTreeItem>>`  
_L268-289_
- inherits: `STableRow<TSharedPtr<IChangelistTreeItem>>`
- desc: Display the shelved files group node. It displays 'Shelved Files (x)' where X is the nubmer of file shelved.
- L271 _public function_ `SLATE_BEGIN_ARGS(SShelvedFilesTableRow) : _TreeItemToVisualize() , _HighlightText()`
- L281 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L282 _public prototype_ `static void PopulateSearchString(const FShelvedChangelistTreeItem& Item, TArray<FString>& OutStrings);`
- L285 _private member_ `FShelvedChangelistTreeItem* TreeItem;`
- L288 _private member_ `TAttribute<FText> HighlightText;` — The text to highlight

#### class `SOfflineFileTableRow`  
`class SOfflineFileTableRow : public SMultiColumnTableRow<FChangelistTreeItemPtr>`  
_L293-344_
- inherits: `SMultiColumnTableRow<FChangelistTreeItemPtr>`
- desc: Display information about an offline file (icon, name, location, type, etc.).
- L296 _public function_ `SLATE_BEGIN_ARGS(SOfflineFileTableRow) : _TreeItemToVisualize() , _HighlightText() , _PathFlags(SourceControlFileViewColumn::EPathFlags::Default)`
- L314 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwner);` — Construct child widgets that comprise this widget. @param InArgs Declaration from which to construct this widget.
- L317 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — SMultiColumnTableRow overrides
- L319 _public prototype_ `ECheckBoxState GetCheckBoxState() const;`
- L320 _public prototype_ `void SetCheckBoxState(ECheckBoxState NewState);`
- L321 _public prototype_ `FText GetDisplayName() const;`
- L322 _public prototype_ `FText GetFilename() const;`
- L323 _public prototype_ `FText GetDisplayPath() const;`
- L324 _public prototype_ `FText GetDisplayType() const;`
- L325 _public prototype_ `FSlateColor GetDisplayColor() const;`
- L326 _public prototype_ `FText GetLastModifiedTimestamp() const;`
- L328 _public prototype_ `static void PopulateSearchString(const FOfflineFileTreeItem& Item, SourceControlFileViewColumn::EPathFlags PathFlags, TArray<FString>& OutStrings);`
- L332 _protected prototype_ `virtual void OnDragEnter(FGeometry const& InGeometry, FDragDropEvent const& InDragDropEvent) override;`
- L333 _protected prototype_ `virtual void OnDragLeave(FDragDropEvent const& InDragDropEvent) override;`
- L338 _private member_ `FOfflineFileTreeItem* TreeItem;` — The info about the widget that we are visualizing.
- L341 _private member_ `TAttribute<FText> HighlightText;` — The text to highlight
- L343 _private member_ `TAttribute<SourceControlFileViewColumn::EPathFlags> PathFlags;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace SourceControlFileViewColumn`
- L18 _namespace_ `namespace CheckBox` (scope `SourceControlFileViewColumn`)
- L20 _prototype_ `FName Id();` (scope `SourceControlFileViewColumn::CheckBox`)
- L24 _namespace_ `namespace Icon` (scope `SourceControlFileViewColumn`)
- L26 _prototype_ `FName Id();` (scope `SourceControlFileViewColumn::Icon`)
- L27 _prototype_ `FText GetDisplayText();` (scope `SourceControlFileViewColumn::Icon`)
- L28 _prototype_ `FText GetToolTipText();` (scope `SourceControlFileViewColumn::Icon`)
- L32 _namespace_ `namespace Shelve` (scope `SourceControlFileViewColumn`)
- L34 _prototype_ `FName Id();` (scope `SourceControlFileViewColumn::Shelve`)
- L35 _prototype_ `FText GetDisplayText();` (scope `SourceControlFileViewColumn::Shelve`)
- L36 _prototype_ `FText GetToolTipText();` (scope `SourceControlFileViewColumn::Shelve`)
- L40 _namespace_ `namespace Name` (scope `SourceControlFileViewColumn`)
- L42 _prototype_ `FName Id();` (scope `SourceControlFileViewColumn::Name`)
- L43 _prototype_ `FText GetDisplayText();` (scope `SourceControlFileViewColumn::Name`)
- L44 _prototype_ `FText GetToolTipText();` (scope `SourceControlFileViewColumn::Name`)
- L48 _namespace_ `namespace Path` (scope `SourceControlFileViewColumn`)
- L50 _prototype_ `FName Id();` (scope `SourceControlFileViewColumn::Path`)
- L51 _prototype_ `FText GetDisplayText();` (scope `SourceControlFileViewColumn::Path`)
- L52 _prototype_ `FText GetToolTipText();` (scope `SourceControlFileViewColumn::Path`)
- L56 _namespace_ `namespace Type` (scope `SourceControlFileViewColumn`)
- L58 _prototype_ `FName Id();` (scope `SourceControlFileViewColumn::Type`)
- L59 _prototype_ `FText GetDisplayText();` (scope `SourceControlFileViewColumn::Type`)
- L60 _prototype_ `FText GetToolTipText();` (scope `SourceControlFileViewColumn::Type`)
- L64 _namespace_ `namespace LastModifiedTimestamp` (scope `SourceControlFileViewColumn`)
- L66 _prototype_ `FName Id();` (scope `SourceControlFileViewColumn::LastModifiedTimestamp`)
- L67 _prototype_ `FText GetDisplayText();` (scope `SourceControlFileViewColumn::LastModifiedTimestamp`)
- L68 _prototype_ `FText GetToolTipText();` (scope `SourceControlFileViewColumn::LastModifiedTimestamp`)
- L72 _namespace_ `namespace CheckedOutByUser` (scope `SourceControlFileViewColumn`)
- L74 _prototype_ `FName Id();` (scope `SourceControlFileViewColumn::CheckedOutByUser`)
- L75 _prototype_ `FText GetDisplayText();` (scope `SourceControlFileViewColumn::CheckedOutByUser`)
- L76 _prototype_ `FText GetToolTipText();` (scope `SourceControlFileViewColumn::CheckedOutByUser`)
- L80 _namespace_ `namespace Changelist` (scope `SourceControlFileViewColumn`)
- L82 _prototype_ `FName Id();` (scope `SourceControlFileViewColumn::Changelist`)
- L83 _prototype_ `FText GetDisplayText();` (scope `SourceControlFileViewColumn::Changelist`)
- L84 _prototype_ `FText GetToolTipText();` (scope `SourceControlFileViewColumn::Changelist`)
- L88 _namespace_ `namespace Dirty` (scope `SourceControlFileViewColumn`)
- L90 _prototype_ `FName Id();` (scope `SourceControlFileViewColumn::Dirty`)
- L91 _prototype_ `FText GetDisplayText();` (scope `SourceControlFileViewColumn::Dirty`)
- L92 _prototype_ `FText GetToolTipText();` (scope `SourceControlFileViewColumn::Dirty`)
- L96 _namespace_ `namespace Discard` (scope `SourceControlFileViewColumn`)
- L98 _prototype_ `FName Id();` (scope `SourceControlFileViewColumn::Discard`)
- L99 _prototype_ `FText GetDisplayText();` (scope `SourceControlFileViewColumn::Discard`)
- L100 _prototype_ `FText GetToolTipText();` (scope `SourceControlFileViewColumn::Discard`)
- L110 _prototype_ `ENUM_CLASS_FLAGS(EPathFlags) TFunction<int32(const IFileViewTreeItem&, const IFileViewTreeItem&)> GetColumnComparer(FName ColumnId, EPathFlags PathFlags);` (scope `SourceControlFileViewColumn`)
- L114 _prototype_ `TFunction<bool(const IFileViewTreeItem&, const IFileViewTreeItem&)> GetSortPredicate(EColumnSortMode::Type, FName ColumnId, EPathFlags PathFlags);` (scope `SourceControlFileViewColumn`)

### `Source/Editor/SourceControlWindows/Private/SSourceControlChangelists.h` (Private)


#### class `SSourceControlChangelistsWidget`  
`class SSourceControlChangelistsWidget : public SCompoundWidget`  
_L30-277_
- inherits: `SCompoundWidget`
- desc: Displays the user source control change lists.
- L33 _public function_ `SLATE_BEGIN_ARGS(SSourceControlChangelistsWidget)`
- L34 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L38 _public prototype_ `virtual ~SSourceControlChangelistsWidget();`
- L41 _public prototype_ `void SetSelectedFiles(const TArray<FString>& Filenames);` — Set selected files
- L69 _private prototype_ `TSharedRef<SWidget> MakeToolBar();`
- L70 _private prototype_ `TSharedRef<STreeView<FChangelistTreeItemPtr>> CreateChangelistTreeView(TArray<TSharedPtr<IChangelistTreeItem>>& ItemSources);`
- L71 _private prototype_ `TSharedRef<SListView<FChangelistTreeItemPtr>> CreateChangelistFilesView();`
- L72 _private prototype_ `TSharedRef<SListView<FChangelistTreeItemPtr>> CreateUnsavedAssetsFilesView();`
- L74 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FChangelistTreeItemPtr InTreeItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L75 _private prototype_ `void OnGetChangelistChildren(FChangelistTreeItemPtr InParent, TArray<FChangelistTreeItemPtr>& OutChildren);`
- L76 _private prototype_ `void OnFileViewHiddenColumnsListChanged();`
- L78 _private prototype_ `EColumnSortPriority::Type GetColumnSortPriority(const FName ColumnId) const;`
- L79 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;`
- L80 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L81 _private prototype_ `bool IsFileViewSortedByFileStatusIcon() const;`
- L82 _private prototype_ `bool IsFileViewSortedByFileShelveIcon() const;`
- L83 _private prototype_ `bool IsFileViewSortedByLastModifiedTimestamp() const;`
- L84 _private prototype_ `void SortFileView();`
- L86 _private prototype_ `void OnChangelistSearchTextChanged(const FText& InFilterText);`
- L87 _private prototype_ `void OnUncontrolledChangelistSearchTextChanged(const FText& InFilterText);`
- L88 _private prototype_ `void OnFileSearchTextChanged(const FText& InFilterText);`
- L89 _private prototype_ `void PopulateItemSearchStrings(const IChangelistTreeItem& Item, TArray<FString>& OutStrings);`
- L90 _private prototype_ `void OnUnsavedAssetChanged(const FString& Filepath);`
- L92 _private prototype_ `FReply OnFilesDragged(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);`
- L93 _private prototype_ `FReply OnUnsavedAssetsDragged(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);`
- L95 _private prototype_ `void RequestChangelistsRefresh();`
- L96 _private prototype_ `void RequestFileStatusRefresh(const IChangelistTreeItem& Changelist);`
- L97 _private prototype_ `void RequestFileStatusRefresh(TSet<FString>&& Pathnames);`
- L98 _private prototype_ `void OnRefreshUI(ERefreshFlags RefreshFlags);`
- L99 _private prototype_ `void OnRefreshUnsavedAssetsWidgets(int64 CurrUpdateNum, const TFunction<void(TSharedPtr<IFileViewTreeItem>&)>& AddItemToFileView);`
- L100 _private prototype_ `void OnRefreshSourceControlWidgets(int64 CurreUpdateNum, const TFunction<void(TSharedPtr<IFileViewTreeItem>&)>& AddItemToFileView);`
- L101 _private prototype_ `void OnRefreshUncontrolledChangelistWidgets(int64 CurreUpdateNum, const TFunction<void(TSharedPtr<IFileViewTreeItem>&)>& AddItemToFileView);`
- L102 _private prototype_ `void ClearChangelistsTree();`
- L104 _private prototype_ `TSharedPtr<SWidget> OnOpenContextMenu();`
- L107 _private prototype_ `FSourceControlChangelistStatePtr GetCurrentChangelistState() const;` — Returns the currently selected changelist state ptr or null in invalid cases
- L108 _private prototype_ `FUncontrolledChangelistStatePtr GetCurrentUncontrolledChangelistState() const;`
- L109 _private prototype_ `FSourceControlChangelistPtr GetCurrentChangelist();`
- L110 _private prototype_ `TOptional<FUncontrolledChangelist> GetCurrentUncontrolledChangelist() const;`
- L111 _private prototype_ `FSourceControlChangelistStatePtr GetChangelistStateFromSelection();`
- L112 _private prototype_ `FSourceControlChangelistPtr GetChangelistFromSelection();`
- L115 _private prototype_ `TArray<FString> GetSelectedFiles();` — Returns list of currently selected files
- L116 _private prototype_ `bool HasFilesSelected() const;`
- L119 _private prototype_ `TArray<FString> GetSelectedShelvedFiles();` — Returns list of currently selected shelved files
- L120 _private prototype_ `bool HasShelvedFilesSelected() const;`
- L127 _private prototype_ `void GetSelectedFiles(TArray<FString>& OutControlledFiles, TArray<FString>& OutUncontrolledFiles);` — Splits selected files between Controlled and Uncontrolled files. @param 	OutControlledFiles 		Selected source controlled files will be added to this array. @param 	OutUncontrolledFiles	Selected uncontrolled files will be added to this array.
- L134 _private prototype_ `void GetSelectedFileStates(TArray<FSourceControlStateRef>& OutControlledFileStates, TArray<FSourceControlStateRef>& OutUncontrolledFileStates);` — Splits selected files between Controlled and Uncontrolled files. @param 	OutControlledFileStates 	Selected source controlled file states will be added to this array. @param 	OutUncontrolledFileStates	Selected uncontrolled file states will be added to this array.
- L137 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Intercept Enter and Delete key presses to Submit or Delete the selected changelist (if conditions are met)
- L140 _private prototype_ `void OnNewChangelist();` — Changelist operations
- L141 _private prototype_ `void OnDeleteChangelist();`
- L142 _private prototype_ `bool CanDeleteChangelist() const;`
- L143 _private prototype_ `bool CanDeleteChangelist(FText* OutFailureMessage) const;`
- L144 _private prototype_ `void OnEditChangelist();`
- L145 _private prototype_ `void OnSubmitChangelist();`
- L146 _private prototype_ `FText GetCanSubmitChangelistToolTip() const;`
- L147 _private prototype_ `bool CanSubmitChangelist() const;`
- L148 _private prototype_ `bool CanSubmitChangelist(FText* OutFailureMessage) const;`
- L149 _private prototype_ `void OnValidateChangelist();`
- L150 _private prototype_ `bool CanValidateChangelist() const;`
- L153 _private prototype_ `void OnNewUncontrolledChangelist();` — Uncontrolled Changelist operations
- L154 _private prototype_ `void OnEditUncontrolledChangelist();`
- L155 _private prototype_ `bool CanEditUncontrolledChangelist();`
- L156 _private prototype_ `void OnDeleteUncontrolledChangelist();`
- L157 _private prototype_ `bool CanDeleteUncontrolledChangelist();`
- L160 _private prototype_ `void OnRevertUnchanged();` — Changelist & File operations
- L161 _private prototype_ `bool CanRevertUnchanged();`
- L162 _private prototype_ `void OnRevert();`
- L163 _private prototype_ `bool CanRevert();`
- L164 _private prototype_ `void OnShelve();`
- L167 _private prototype_ `void OnUnshelve();` — Changelist & shelved files operations
- L168 _private prototype_ `void OnDeleteShelvedFiles();`
- L171 _private prototype_ `TValueOrError<void, void> TryMoveFiles();` — Files operations
- L172 _private prototype_ `void OnShowHistory();`
- L173 _private prototype_ `void OnDiffAgainstDepot();`
- L174 _private prototype_ `bool CanDiffAgainstDepot();`
- L177 _private prototype_ `void OnDiffAgainstWorkspace();` — Shelved files operations
- L178 _private prototype_ `bool CanDiffAgainstWorkspace();`
- L181 _private prototype_ `void OnSaveAssetsInChangelist();` — Save assets in changelist operations
- L182 _private prototype_ `bool CanSaveAssetsInChangelist();`
- L185 _private prototype_ `void OnUncontrolledChangelistStateChanged();` — Uncontrolled changelist module callback.
- L188 _private prototype_ `void OnSourceControlProviderChanged(ISourceControlProvider& OldProvider, ISourceControlProvider& NewProvider);` — Source control callbacks
- L189 _private prototype_ `void OnSourceControlStateChanged();`
- L190 _private prototype_ `void OnItemDoubleClicked(TSharedPtr<IChangelistTreeItem> Item);`
- L191 _private prototype_ `void OnChangelistSelectionChanged(TSharedPtr<IChangelistTreeItem> SelectedItem, ESelectInfo::Type SelectionType);`
- L192 _private prototype_ `void OnChangelistsStatusUpdated(const TSharedRef<ISourceControlOperation>& InOperation, ECommandResult::Type InType);`
- L194 _private prototype_ `void OnStartSourceControlOperation(TSharedRef<ISourceControlOperation> Operation, const FText& Message);`
- L195 _private prototype_ `void OnEndSourceControlOperation(const TSharedRef<ISourceControlOperation>& Operation, ECommandResult::Type InType);`
- L198 _private prototype_ `void Execute(const FText& Message, const TSharedRef<ISourceControlOperation>& InOperation, TSharedPtr<ISourceControlChangelist> InChangelist, const TArray<FString>& InFiles, EConcurrency::Type InConcurrency, const FSourceControlOperationComplete& InOperationCompleteDelegate);` — Wrapper functions on top of the source control ones to display slow tasks for synchronous operations or toast notifications for async ones.
- L199 _private prototype_ `void Execute(const FText& Message, const TSharedRef<ISourceControlOperation>& InOperation, TSharedPtr<ISourceControlChangelist> InChangelist, const EConcurrency::Type InConcurrency, const FSourceControlOperationComplete& InOperationCompleteDelegate);`
- L200 _private prototype_ `void Execute(const FText& Message, const TSharedRef<ISourceControlOperation>& InOperation, const EConcurrency::Type InConcurrency, const FSourceControlOperationComplete& InOperationCompleteDelegate);`
- L201 _private prototype_ `void Execute(const FText& Message, const TSharedRef<ISourceControlOperation>& InOperation, const TArray<FString>& InFiles, EConcurrency::Type InConcurrency, const FSourceControlOperationComplete& InOperationCompleteDelegate);`
- L202 _private prototype_ `void ExecuteUncontrolledChangelistOperation(const FText& Message, const TFunction<void()>& UncontrolledChangelistTask);`
- L204 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L207 _private prototype_ `void EditChangelistDescription(const FText& InNewChangelistDescription, const FSourceControlChangelistStatePtr& InChangelistState);` — Executes an operation to updates the changelist description of the provided changelist with a new description.
- L210 _private prototype_ `void OnPackageSaved(const FString& PackageFilename, UPackage* Package, FObjectPostSaveContext ObjectSaveContext);` — Invoked when a package is saved, to refresh the last saved timestamp.
- L212 _private prototype_ `void OnPluginEdited(IPlugin& InPlugin);`
- L215 _private member_ `TSharedPtr<SExpandableChangelistArea> UnsavedAssetsExpandableArea;`
- L216 _private member_ `TSharedPtr<STreeView<FChangelistTreeItemPtr>> UnsavedAssetsTreeView;`
- L217 _private member_ `TArray<TSharedPtr<IChangelistTreeItem>> UnsavedAssetsTreeNode;`
- L219 _private member_ `TSharedPtr<SExpandableChangelistArea> ChangelistExpandableArea;`
- L220 _private member_ `TSharedPtr<STreeView<FChangelistTreeItemPtr>> ChangelistTreeView;`
- L221 _private member_ `TArray<TSharedPtr<IChangelistTreeItem>> ChangelistTreeNodes;`
- L223 _private member_ `TSharedPtr<SExpandableChangelistArea> UncontrolledChangelistExpandableArea;`
- L224 _private member_ `TSharedPtr<STreeView<FChangelistTreeItemPtr>> UncontrolledChangelistTreeView;`
- L225 _private member_ `TArray<TSharedPtr<IChangelistTreeItem>> UncontrolledChangelistTreeNodes;`
- L227 _private member_ `TSharedPtr<SListView<FChangelistTreeItemPtr>> FileListView;`
- L228 _private member_ `TArray<TSharedPtr<IChangelistTreeItem>> FileListNodes;`
- L229 _private member_ `TArray<FName> FileViewHiddenColumnsList;`
- L231 _private member_ `TSharedPtr<SListView<FChangelistTreeItemPtr>> UnsavedAssetsFileListView;`
- L232 _private member_ `TSharedPtr<SWidgetSwitcher> FileListViewSwitcher;`
- L234 _private prototype_ `SListView<FChangelistTreeItemPtr>& GetActiveFileListView() const;`
- L236 _private member_ `TMap<TSharedPtr<void>, TSharedPtr<IChangelistTreeItem>> SourceControlItemCache;`
- L237 _private member_ `TMap<TSharedPtr<void>, TSharedPtr<IChangelistTreeItem>> UncontrolledChangelistItemCache;`
- L238 _private member_ `TMap<FString, TSharedPtr<IFileViewTreeItem>> OfflineFileItemCache;`
- L240 _private member_ `TUniquePtr<FAsyncTask<FAsyncTimestampUpdater>> TimestampUpdateTask;`
- L241 _private member_ `TSet<FString> OutdatedTimestampFiles;`
- L244 _private member_ `FDelegateHandle SourceControlStateChangedDelegateHandle;` — Source control state changed delegate handle
- L246 _private member_ `int64 UpdateRequestNum = 0;`
- L247 _private member_ `bool bInitialRefreshDone = false;`
- L248 _private member_ `bool bShouldRefresh = false;`
- L249 _private member_ `bool bShouldRefreshVersePaths = false;`
- L250 _private member_ `bool bShowingContentVersePath = false;`
- L251 _private member_ `bool bSourceControlAvailable = false;`
- L252 _private member_ `bool bUpdateMonitoredFileStatusList = false;`
- L255 _private member_ `TArray<FString> FilesToSelect;` — Files to select after refresh
- L257 _private member_ `FName PrimarySortedColumn;`
- L258 _private member_ `FName SecondarySortedColumn;`
- L259 _private member_ `EColumnSortMode::Type PrimarySortMode = EColumnSortMode::Ascending;`
- L260 _private member_ `EColumnSortMode::Type SecondarySortMode = EColumnSortMode::None;`
- L262 _private member_ `TSharedPtr<TTextFilter<const IChangelistTreeItem&>> ChangelistTextFilter;`
- L263 _private member_ `TSharedPtr<TTextFilter<const IChangelistTreeItem&>> UncontrolledChangelistTextFilter;`
- L264 _private member_ `TSharedPtr<TTextFilter<const IChangelistTreeItem&>> FileTextFilter;`
- L265 _private member_ `TSharedPtr<SSearchBox> FileSearchBox;`
- L267 _private prototype_ `void StartRefreshStatus();`
- L268 _private prototype_ `void TickRefreshStatus(double InDeltaTime);`
- L269 _private prototype_ `void EndRefreshStatus();`
- L271 _private member_ `FText RefreshStatus;`
- L272 _private member_ `bool bIsRefreshing = false;`
- L273 _private member_ `double RefreshStatusStartSecs;`
- L275 _private member_ `float ChangelistAreaSize = 0.3f;` — [0.0f, 1.0f]
- L276 _private member_ `float FileAreaSize = 0.7f;`

#### enum `SSourceControlChangelistsWidget::ERefreshFlags`  
`enum class ERefreshFlags`  
_L44-50_
- L46 _public enumerator_ `SourceControlChangelists = 1 << 0`
- L47 _public enumerator_ `UnsavedAssets = 1 << 1`
- L48 _public enumerator_ `UncontrolledChangelists = 1 << 2`
- L49 _public enumerator_ `All = SourceControlChangelists | UnsavedAssets | UncontrolledChangelists`

#### class `SSourceControlChangelistsWidget::FAsyncTimestampUpdater`  
`class FAsyncTimestampUpdater`  
_L54-66_
- desc: Queries files timestamp asynchronously.
- L57 _public prototype_ `void DoWork();`
- L58 _public function_ `bool CanAbandon()`
- L59 _public function_ `void Abandon()`
- L60 _public function_ `TStatId GetStatId() const`
- L61 _public function_ `static const TCHAR* Name()`
- L63 _public member_ `std::atomic<bool> bAbandon;`
- L64 _public member_ `TSet<FString> RequestedFileTimestamps;`
- L65 _public member_ `TMap<FString, FDateTime> QueriedFileTimestamps;`

### `Source/Editor/SourceControlWindows/Private/SSourceControlCheckedOutDialog.h` (Private)


#### class `SSourceControlCheckedOutDialog`  
`class SSourceControlCheckedOutDialog : public SCompoundWidget`  
_L18-111_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SSourceControlCheckedOutDialog) : _ParentWindow() , _Items() , _ShowColumnAssetName(true) , _ShowColumnAssetClass(true) , _ShowColumnUserName(true) , _MessageText() , _CloseText() , _CheckBoxText()`
- L32 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(TArray<FSourceControlStateRef>, Items) SLATE_ARGUMENT(bool, ShowColumnAssetName) SLATE_ARGUMENT(bool, ShowColumnAssetClass) SLATE_ARGUMENT(bool, ShowColumnUserName) SLATE_ARGUMENT(FText, MessageText) SLATE_ARGUMENT(FText, CloseText) SLATE_ARGUMENT(FText, CheckBoxText) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L47 _public function_ `bool IsCheckBoxChecked()` — Get whether to hide the checkbox is checked
- L51 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowForList(FChangelistTreeItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Callback to generate ListBoxRows
- L60 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;` — Returns the current column sort mode (ascending or descending) if the ColumnId parameter matches the current column to be sorted by, otherwise returns EColumnSortMode_None. @param	ColumnId	Column ID to query sort mode for. @return	The sort mode for the column, or EColumnSortMode_None if it is not known.
- L68 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);` — Callback for SHeaderRow::Column::OnSort, called when the column to sort by is changed. @param	ColumnId	The new column to sort by @param	InSortMode	The sort mode (ascending or descending)
- L74 _private prototype_ `void RequestSort();` — Requests that the source list data be sorted according to the current sort column and mode, and refreshes the list view.
- L79 _private prototype_ `void SortTree();` — Sorts the source list data according to the current sort column and mode.
- L82 _private prototype_ `FReply CloseClicked();` — Called when the cancel button is clicked
- L86 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L90 _private member_ `TWeakPtr<SWindow> ParentFrame;` — Pointer to the parent modal window
- L93 _private member_ `TArray<FChangelistTreeItemPtr> ListViewItems;` — Collection of objects to display in the List View
- L96 _private member_ `TSharedPtr<SListView<FChangelistTreeItemPtr>> ListView;` — ListBox for displaying items
- L99 _private member_ `FName SortByColumn;` — Specify which column to sort with
- L102 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::Ascending;` — Currently selected sorting mode
- L104 _private member_ `bool bShowingContentVersePath = false;`
- L107 _private member_ `TSharedPtr<SButton> CloseButton;` — The close button widget.
- L110 _private member_ `TSharedPtr<SCheckBox> CheckBox;` — The checkbox widget.

### `Source/Editor/SourceControlWindows/Private/SSourceControlCommon.h` (Private)


#### struct `IChangelistTreeItem`  
`struct IChangelistTreeItem : TSharedFromThis<IChangelistTreeItem>`  
_L34-85_
- inherits: `TSharedFromThis<IChangelistTreeItem>`
- desc: Modelizes a changelist node in a source control tree-like structure. The modelized tree stored is as below in memory. > Changelist File > ShelvedChangelist ShelvedFile > UncontrolledChangelist File Offline File > UnsavedAssets Offline File
- L47 _public prototype_ `virtual ~IChangelistTreeItem() = default;`
- L50 _public prototype_ `TSharedPtr<IChangelistTreeItem> GetParent() const;` — Get this item's parent. Can be nullptr for root nodes.
- L53 _public prototype_ `const TArray<TSharedPtr<IChangelistTreeItem>>& GetChildren() const;` — Get this item's children, if any. Although we store as weak pointers, they are guaranteed to be valid.
- L56 _public function_ `const TreeItemType GetTreeItemType() const` — Returns the TreeItem's type
- L59 _public prototype_ `void AddChild(TSharedRef<IChangelistTreeItem> Child);` — Add a child to this item
- L62 _public prototype_ `void RemoveChild(const TSharedRef<IChangelistTreeItem>& Child);` — Remove a child from this item
- L65 _public prototype_ `void RemoveAllChildren();` — Remove all children from this item.
- L69 _public member_ `int64 VisitedUpdateNum = -1;` — A sequence number representing the last time the item was inspected by the widget owning this UI item. Detect when the underlying model object stopped to exist between two UI updates.
- L72 _public member_ `int64 DisplayedUpdateNum = -1;` — A sequence number representing the last time the item was displayed by the widget owning this item. Used to detect when an existing item started/stopped to be visible between two UI updates.
- L75 _protected function_ `IChangelistTreeItem(TreeItemType InType)`
- L78 _protected member_ `TSharedPtr<IChangelistTreeItem> Parent;` — This item's parent, if any.
- L81 _protected member_ `TArray<TSharedPtr<IChangelistTreeItem>> Children;` — Array of children contained underneath this item
- L84 _protected member_ `TreeItemType Type;` — This item type.

#### enum `IChangelistTreeItem::TreeItemType`  
`enum TreeItemType`  
_L36-45_
- L38 _public enumerator_ `Changelist` — Node displaying a change list description.
- L39 _public enumerator_ `UncontrolledChangelist` — Node displaying an uncontrolled change list description.
- L40 _public enumerator_ `File` — Node displaying a file information.
- L41 _public enumerator_ `ShelvedChangelist` — Node displaying shelved files as children.
- L42 _public enumerator_ `ShelvedFile` — Node displaying a shelved file information.
- L43 _public enumerator_ `OfflineFile` — Node displaying an offline file information.
- L44 _public enumerator_ `UnsavedAssets` — Node displaying unsaved asset category

#### struct `IFileViewTreeItem`  
`struct IFileViewTreeItem : public IChangelistTreeItem`  
_L93-150_
- inherits: `IChangelistTreeItem`
- desc: Abstracts the values displayed in the file view that has a set of columns. The API returns values as string rather than FText to avoid conversion when sorting very large collection (as FText convert internally to FString for comparison).
- L96 _public prototype_ `virtual ECheckBoxState GetCheckBoxState() const = 0;` — Returns the checkbox state of this item
- L99 _public prototype_ `virtual void SetCheckBoxState(ECheckBoxState NewState) = 0;` — Sets the checkbox state of this item
- L102 _public prototype_ `virtual int32 GetIconSortingPriority() const = 0;` — The 'Priority' given to the item icon when sorting ascending (lower will be sorted first).
- L105 _public prototype_ `virtual const FString& GetName() const = 0;` — The values displayed in the 'Name' column.
- L108 _public prototype_ `virtual const FString& GetPath() const = 0;` — The values displayed in the 'Path' column when not displaying package names or Verse paths.
- L111 _public prototype_ `virtual const UE::Core::FVersePath& GetVersePath() const = 0;` — The values displayed in the 'Path' column when displaying Verse paths.
- L114 _public prototype_ `virtual const FString& GetType() const = 0;` — The values displayed in the 'Type' column.
- L117 _public function_ `virtual const FString& GetTypeName() const` — The values displayed in the 'Type Name' column.
- L120 _public function_ `virtual const FString& GetCheckedOutBy() const` — The values displayed in the 'User' column.
- L123 _public prototype_ `virtual const FString& GetFullPathname() const = 0;` — Returns the full pathname of the files on the file sytem.
- L126 _public prototype_ `void SetLastModifiedDateTime(const FDateTime& Timestamp);` — Set the last modified time timestamp.
- L129 _public function_ `const FDateTime& GetLastModifiedDateTime() const` — The values displayed in the 'Last Modified' column.
- L132 _public function_ `FText GetLastModifiedTimestamp() const` — The values displayed in the 'Last Modified' column as text.
- L134 _public prototype_ `virtual bool RefreshVersePath() = 0;`
- L138 _public member_ `int32 DisplayedIconPriority = -1;` — Keep the icon sorting priority as it was the last time the item was displayed. Used to detect if the priority changed between two refreshes of the UI.
- L141 _protected function_ `IFileViewTreeItem(TreeItemType InType) : IChangelistTreeItem(InType)`
- L145 _private member_ `static const FString DefaultStrValue;` — Use an empty string to return as default for const FString&.
- L148 _private member_ `FText LastModifiedTimestampText;` — The timestamp of the last modification to the file.
- L149 _private member_ `FDateTime LastModifiedDateTime;`

#### struct `FShelvedChangelistTreeItem`  
`struct FShelvedChangelistTreeItem : public IChangelistTreeItem`  
_L154-158_
- inherits: `IChangelistTreeItem`
- desc: Root node to group shelved files as children.
- L156 _public function_ `FShelvedChangelistTreeItem() : IChangelistTreeItem(IChangelistTreeItem::ShelvedChangelist)`
- L157 _public prototype_ `FText GetDisplayText() const;`

#### struct `FChangelistTreeItem`  
`struct FChangelistTreeItem : public IChangelistTreeItem`  
_L162-192_
- inherits: `IChangelistTreeItem`
- desc: Displays a changelist icon/number/description.
- L164 _public function_ `FChangelistTreeItem(TSharedRef<ISourceControlChangelistState> InChangelistState) : IChangelistTreeItem(IChangelistTreeItem::Changelist) , ChangelistState(MoveTemp(InChangelistState))`
- L170 _public function_ `FText GetDisplayText() const`
- L175 _public function_ `FText GetDescriptionText() const`
- L180 _public function_ `int32 GetFileCount() const`
- L185 _public function_ `int32 GetShelvedFileCount() const`
- L190 _public member_ `TSharedRef<ISourceControlChangelistState> ChangelistState;`
- L191 _public member_ `TSharedPtr<FShelvedChangelistTreeItem> ShelvedChangelistItem;`

#### struct `FUncontrolledChangelistTreeItem`  
`struct FUncontrolledChangelistTreeItem : public IChangelistTreeItem`  
_L196-220_
- inherits: `IChangelistTreeItem`
- desc: Displays an uncontrolled changelist icon/number/description.
- L198 _public function_ `FUncontrolledChangelistTreeItem(FUncontrolledChangelistStateRef InUncontrolledChangelistState) : IChangelistTreeItem(IChangelistTreeItem::UncontrolledChangelist) , UncontrolledChangelistState(InUncontrolledChangelistState)`
- L204 _public function_ `FText GetDisplayText() const`
- L209 _public function_ `FText GetDescriptionText() const`
- L214 _public function_ `int32 GetFileCount() const`
- L219 _public member_ `FUncontrolledChangelistStateRef UncontrolledChangelistState;`

#### struct `FUnsavedAssetsTreeItem`  
`struct FUnsavedAssetsTreeItem : public IChangelistTreeItem`  
_L223-231_
- inherits: `IChangelistTreeItem`
- desc: Displays a changelist icon/number/description.
- L225 _public function_ `FUnsavedAssetsTreeItem() : IChangelistTreeItem(IChangelistTreeItem::UnsavedAssets)`
- L230 _public prototype_ `FString GetDisplayString() const;`

#### struct `FFileTreeItem`  
`struct FFileTreeItem : public IFileViewTreeItem`  
_L234-348_
- inherits: `IFileViewTreeItem`
- desc: Displays a set of files under a changelist or uncontrolled changelist.
- L236 _public prototype_ `explicit FFileTreeItem(FSourceControlStateRef InFileState, bool bBeautifyPaths = true, bool bIsShelvedFile = false);`
- L238 _public function_ `virtual ECheckBoxState GetCheckBoxState() const override`
- L239 _public function_ `virtual void SetCheckBoxState(ECheckBoxState NewState) override`
- L240 _public prototype_ `virtual int32 GetIconSortingPriority() const override;`
- L241 _public function_ `virtual const FString& GetName() const override`
- L242 _public function_ `virtual const FString& GetPath() const override`
- L243 _public function_ `virtual const UE::Core::FVersePath& GetVersePath() const override`
- L244 _public function_ `virtual const FString& GetType() const override`
- L245 _public function_ `virtual const FString& GetTypeName() const override`
- L246 _public function_ `virtual const FString& GetFullPathname() const override`
- L247 _public prototype_ `virtual const FString& GetCheckedOutBy() const override;`
- L249 _public prototype_ `virtual bool RefreshVersePath() override;`
- L252 _public prototype_ `void RefreshAssetInformation();` — Updates informations based on AssetData
- L255 _public prototype_ `FText GetAssetName();` — Returns the asset name of the item. This might update the asset names from the asset registry.
- L258 _public prototype_ `FText GetAssetName() const;` — Returns the asset name. This returns the currently cached asset name.
- L261 _public function_ `FText GetAssetPath() const` — Returns the asset path of the item
- L264 _public function_ `FText GetAssetVersePath() const` — Returns the asset Verse path of the item
- L267 _public function_ `FText GetAssetType() const` — Returns the asset type of the item
- L270 _public function_ `FText GetAssetTypeName() const` — Returns the asset type name of the item
- L273 _public function_ `FSlateColor GetAssetTypeColor() const` — Returns the asset type color of the item
- L276 _public prototype_ `FText GetCheckedOutByUser() const;` — Returns the user that checked out the file/asset (if any).
- L279 _public prototype_ `FText GetFileName() const;` — Returns the file name of the item in source control
- L282 _public function_ `bool NeedsAdding() const` — true if the item is not in source control and needs to be added prior to checkin
- L285 _public function_ `bool CanCheckIn() const` — true if the item is in source control and is able to be checked in
- L288 _public function_ `bool IsEnabled() const` — true if the item is enabled in the list
- L291 _public function_ `bool CanDiff() const` — true if the item is source controlled and not marked for add nor for delete
- L294 _public function_ `bool CanRevert() const` — true if the item is source controlled and can be reverted
- L296 _public function_ `const FAssetDataArrayPtr& GetAssetData() const`
- L301 _public function_ `bool IsShelved() const`
- L305 _public member_ `FSourceControlStateRef FileState;` — Shared pointer to the source control state object itself
- L309 _private member_ `ECheckBoxState CheckBoxState;` — Checkbox state
- L312 _private member_ `FText AssetName;` — Cached asset name to display
- L313 _private member_ `FString AssetNameStr;`
- L316 _private member_ `FText AssetPath;` — Cached asset path to display
- L317 _private member_ `FString AssetPathStr;`
- L320 _private member_ `FText AssetVersePath;` — Cached Verse path to display
- L321 _private member_ `UE::Core::FVersePath AssetVersePathStruct;`
- L324 _private member_ `FText AssetType;` — Cached asset type to display
- L325 _private member_ `FString AssetTypeStr;`
- L328 _private member_ `FText AssetTypeName;` — Cached asset type name to display
- L329 _private member_ `FString AssetTypeNameStr;`
- L332 _private member_ `FColor AssetTypeColor;` — Cached asset type related color to display
- L335 _private member_ `mutable FString CheckedOutBy;` — The other user that has the checked out.
- L338 _private member_ `FAssetDataArrayPtr Assets;` — Matching asset(s) to facilitate Locate in content browser
- L341 _private member_ `const FTimespan MinTimeBetweenUpdate;` — Represents the minimum amount of time between to attempt to refresh AssetData
- L344 _private member_ `FTimespan LastUpdateTime;` — Timestamp representing the time at which the last information update was made
- L347 _private member_ `bool bAssetsUpToDate;` — True if informations returned from the cache are up to date

#### struct `FShelvedFileTreeItem`  
`struct FShelvedFileTreeItem : public FFileTreeItem`  
_L351-357_
- inherits: `FFileTreeItem`
- L353 _public function_ `explicit FShelvedFileTreeItem(FSourceControlStateRef InFileState, bool bBeautifyPaths = true) : FFileTreeItem(InFileState, bBeautifyPaths, true)`

#### struct `FOfflineFileTreeItem`  
`struct FOfflineFileTreeItem : public IFileViewTreeItem`  
_L360-401_
- inherits: `IFileViewTreeItem`
- L362 _public prototype_ `explicit FOfflineFileTreeItem(const FString& InFilename);`
- L364 _public prototype_ `void RefreshAssetInformation();`
- L367 _public function_ `virtual ECheckBoxState GetCheckBoxState() const override`
- L368 _public function_ `virtual void SetCheckBoxState(ECheckBoxState NewState) override`
- L369 _public function_ `virtual int32 GetIconSortingPriority() const override`
- L370 _public function_ `virtual const FString& GetName() const override`
- L371 _public function_ `virtual const FString& GetPath() const override`
- L372 _public function_ `virtual const UE::Core::FVersePath& GetVersePath() const override`
- L373 _public function_ `virtual const FString& GetType() const override`
- L374 _public function_ `virtual const FString& GetFullPathname() const override`
- L376 _public prototype_ `virtual bool RefreshVersePath() override;`
- L378 _public function_ `const FText& GetDisplayFilename() const`
- L379 _public function_ `const FText& GetDisplayName() const`
- L380 _public function_ `const FText& GetDisplayPath() const`
- L381 _public function_ `const FText& GetDisplayVersePath() const`
- L382 _public function_ `const FText& GetDisplayType() const`
- L383 _public function_ `const FColor& GetDisplayColor() const`
- L386 _private member_ `ECheckBoxState CheckBoxState;`
- L387 _private member_ `TArray<FAssetData> Assets;`
- L388 _private member_ `FText Filename;`
- L389 _private member_ `FString FilenameStr;`
- L390 _private member_ `FText AssetName;`
- L391 _private member_ `FString AssetNameStr;`
- L392 _private member_ `FText AssetPath;`
- L393 _private member_ `FString AssetPathStr;`
- L394 _private member_ `FText AssetVersePath;`
- L395 _private member_ `UE::Core::FVersePath AssetVersePathStruct;`
- L396 _private member_ `FText AssetType;`
- L397 _private member_ `FString AssetTypeStr;`
- L398 _private member_ `FText AssetTypeName;`
- L399 _private member_ `FString AssetTypeNameStr;`
- L400 _private member_ `FColor AssetTypeColor;`

#### enum `SSourceControlCommon::ESingleLineFlags`  
`enum ESingleLineFlags`  
_L415-420_
- L417 _public enumerator_ `NewlineTerminates =0x0`
- L418 _public enumerator_ `NewlineConvertToSpace =0x1`
- L419 _public enumerator_ `Mask_NewlineBehavior =0x1`

#### struct `FSCCFileDragDropOp`  
`struct FSCCFileDragDropOp : public FDragDropOperation`  
_L439-460_
- inherits: `FDragDropOperation`
- desc: Implements drag and drop operation.
- L441 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FSCCFileDragDropOp, FDragDropOperation);`
- L445 _public function_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override`
- L457 _public member_ `TArray<FSourceControlStateRef> Files;`
- L458 _public member_ `TArray<FSourceControlStateRef> UncontrolledFiles;`
- L459 _public member_ `TArray<FString> OfflineFiles;`

#### Free symbols / members of external scopes

- L404 _namespace_ `namespace SSourceControlCommon`
- L406 _prototype_ `TSharedRef<SWidget> GetSCCStatusWidget(FSourceControlStateRef InFileState);` (scope `SSourceControlCommon`)
- L407 _prototype_ `TSharedRef<SWidget> GetSCCStatusWidget();` (scope `SSourceControlCommon`)
- L408 _prototype_ `TSharedRef<SWidget> GetSCCShelveWidget(bool bIsShelvedFile);` (scope `SSourceControlCommon`)
- L409 _prototype_ `TSharedRef<SWidget> GetSCCShelveWidget();` (scope `SSourceControlCommon`)
- L410 _prototype_ `FText GetDefaultAssetName();` (scope `SSourceControlCommon`)
- L411 _prototype_ `FText GetDefaultAssetType();` (scope `SSourceControlCommon`)
- L412 _prototype_ `FText GetDefaultUnknownAssetType();` (scope `SSourceControlCommon`)
- L413 _prototype_ `FText GetDefaultMultipleAsset();` (scope `SSourceControlCommon`)
- L421 _prototype_ `ENUM_CLASS_FLAGS(ESingleLineFlags);` (scope `SSourceControlCommon`)
- L425 _prototype_ `FText GetSingleLineChangelistDescription(const FText& InFullDescription, ESingleLineFlags Flags = ESingleLineFlags::NewlineTerminates);` (scope `SSourceControlCommon`) — returns the first non-whitespace line, or an empty FText if InFullDescription is empty or only whitespace
- L427 _prototype_ `void ExecuteChangelistOperationWithSlowTaskWrapper(const FText& Message, const TFunction<void()>& ChangelistTask);` (scope `SSourceControlCommon`)
- L428 _prototype_ `void ExecuteUncontrolledChangelistOperationWithSlowTaskWrapper(const FText& Message, const TFunction<void()>& UncontrolledChangelistTask);` (scope `SSourceControlCommon`)
- L430 _prototype_ `void DisplaySourceControlOperationNotification(const FText& Message, SNotificationItem::ECompletionState CompletionState);` (scope `SSourceControlCommon`)
- L431 _prototype_ `void DisplaySourceControlOperationNotification(const FNotificationInfo& NotificationInfo, SNotificationItem::ECompletionState CompletionState);` (scope `SSourceControlCommon`)
- L432 _prototype_ `TOptional<FNotificationInfo> ConstructSourceControlOperationNotification(const FText& Message);` (scope `SSourceControlCommon`)
- L434 _prototype_ `bool OpenConflictDialog(const TArray<FSourceControlStateRef>& InFilesConflicts);` (scope `SSourceControlCommon`)
- L463 _typedef_ `typedef TSharedPtr<FUncontrolledChangelistTreeItem> FUncontrolledChangelistTreeItemPtr;`
- L464 _typedef_ `typedef TSharedRef<FUncontrolledChangelistTreeItem> FUncontrolledChangelistTreeItemRef;`
- L465 _typedef_ `typedef TSharedPtr<IChangelistTreeItem> FChangelistTreeItemPtr;`
- L466 _typedef_ `typedef TSharedRef<IChangelistTreeItem> FChangelistTreeItemRef;`
- L467 _typedef_ `typedef TSharedPtr<FFileTreeItem> FFileTreeItemPtr;`
- L468 _typedef_ `typedef TSharedRef<FFileTreeItem> FFileTreeItemRef;`

### `Source/Editor/SourceControlWindows/Private/SSourceControlDescription.h` (Private)


#### struct `SSourceControlDescriptionItem`  
`struct SSourceControlDescriptionItem`  
_L20-29_
- L22 _public function_ `SSourceControlDescriptionItem(const FText& InTitle, const FText& InDescription, bool bInCanEditDescription) : Title(InTitle), Description(InDescription), bCanEditDescription(bInCanEditDescription)`
- L26 _public member_ `FText Title;`
- L27 _public member_ `FText Description;`
- L28 _public member_ `bool bCanEditDescription;`

#### class `SSourceControlDescriptionWidget`  
`class SSourceControlDescriptionWidget : public SCompoundWidget`  
_L31-86_
- inherits: `SCompoundWidget`
- L34 _public function_ `SLATE_BEGIN_ARGS(SSourceControlDescriptionWidget) : _ParentWindow() , _Label() , _Text() , _Items()`
- L41 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<SWindow>, ParentWindow) SLATE_ATTRIBUTE(FText, Label) SLATE_ATTRIBUTE(FText, Text) SLATE_ARGUMENT(const TArray<SSourceControlDescriptionItem>*, Items) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L52 _public function_ `bool GetResult() const` — Gets dialog result
- L55 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Used to intercept Escape key press, and interpret it as cancel
- L58 _public prototype_ `FText GetDescription() const;` — Returns the text currently in the edit box
- L61 _public function_ `int32 GetSelectedItemIndex() const` — Returns the currently selected item index if any
- L65 _private prototype_ `FReply OKClicked();` — Called when the settings of the dialog are to be accepted
- L68 _private prototype_ `FReply CancelClicked();` — Called when the settings of the dialog are to be ignored
- L71 _private prototype_ `TSharedRef<SWidget> GetSelectionContent();` — Called to populate the dropdown
- L74 _private prototype_ `FText GetSelectedItemTitle() const;` — Returns title of currently selected item
- L77 _private member_ `bool bResult = false;`
- L80 _private member_ `TWeakPtr<SWindow> ParentWindow;` — Pointer to the parent modal window
- L82 _private member_ `TSharedPtr< SMultiLineEditableTextBox> TextBox;`
- L84 _private member_ `const TArray<SSourceControlDescriptionItem>* Items;`
- L85 _private member_ `int32 CurrentlySelectedItemIndex;`

#### Free symbols / members of external scopes

- L88 _prototype_ `bool GetChangelistDescription( const TSharedPtr<SWidget>& ParentWidget, const FText& InWindowTitle, const FText& InLabel, FText& OutDescription);`
- L94 _prototype_ `bool PickChangelistOrNewWithDescription( const TSharedPtr<SWidget>& ParentWidget, const FText& InWindowTitle, const FText& InLabel, const TArray<SSourceControlDescriptionItem>& Items, int32& OutPickedIndex, FText& OutDescription);`

### `Source/Editor/SourceControlWindows/Private/SSourceControlFileDialog.h` (Private)


#### class `SSourceControlFileDialog`  
`class SSourceControlFileDialog : public SCompoundWidget`  
_L14-140_
- inherits: `SCompoundWidget`
- desc: Represents dialog displaying a provided message along with source control files
- L17 _public function_ `SLATE_BEGIN_ARGS(SSourceControlFileDialog) : _Message() , _Warning() , _Files()`
- L24 _public prototype_ `SLATE_ARGUMENT(FText, Message) SLATE_ARGUMENT(FText, Warning) SLATE_ARGUMENT(TArray<FSourceControlStateRef>, Files) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The message of the widget
- L46 _public prototype_ `void SetMessage(const FText& InMessage);` — Sets the message of the widget @param	InMessage	The string that the message should be set to
- L53 _public prototype_ `void SetWarning(const FText& InMessage);` — Sets the warning message of the widget @param	InMessage	The string that the warning message should be set to
- L60 _public prototype_ `void SetFiles(const TArray<FSourceControlStateRef>& InFiles);` — Sets source control files to display @param	InFiles		The Source Control Files to display
- L63 _public prototype_ `void Reset();` — Reset the state of this dialogs buttons
- L66 _public function_ `bool IsProceedButtonPressed() const` — Returns true if the user pressed the primary button
- L72 _public prototype_ `void SetWindow(TSharedPtr<SWindow> InWindow);` — Sets the owner's window handle @param	InWindow	The window owning the dialog
- L76 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L79 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(FName ColumnId) const;`
- L81 _private prototype_ `void OnColumnSortModeChanged(EColumnSortPriority::Type SortPriority, const FName& ColumnId, EColumnSortMode::Type InSortMode);`
- L83 _private prototype_ `EVisibility GetIconColumnContentVisibility() const;`
- L85 _private prototype_ `void SortFiles();`
- L88 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<IChangelistTreeItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Treeview callback
- L91 _private function_ `void OnGetFileChildren(FChangelistTreeItemPtr InParent, TArray<FChangelistTreeItemPtr>& OutChildren)` — Treeview callback
- L94 _private prototype_ `FText GetMessage() const;` — Used to supply message text to the widget
- L97 _private prototype_ `FText GetWarning() const;` — Used to supply warning text to the widget
- L100 _private prototype_ `EVisibility GetWarningVisibility() const;` — Used to determine visibility of the warning
- L103 _private prototype_ `FReply OnProceedClicked();` — Called when the proceed button is clicked
- L106 _private prototype_ `FReply OnCancelClicked();` — Called when the cancel button is clicked
- L109 _private prototype_ `void CloseDialog();` — Closes the dialog by requesting the owning window to be destroyed
- L113 _private member_ `TSharedPtr<SWindow> Window;` — The Window owning the dialog
- L115 _private member_ `FName SortByColumn;`
- L116 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::Ascending;`
- L119 _private member_ `TArray<TSharedPtr<IChangelistTreeItem>> FileTreeNodes;` — Hold the nodes displayed by the file tree.
- L122 _private member_ `TSharedPtr<STreeView<FChangelistTreeItemPtr>> FileTreeView;` — Display the list of files associated to the selected changelist, uncontrolled changelist or shelved node.
- L125 _private member_ `TSharedPtr<SButton> ProceedButton;` — The primary button widget.
- L128 _private member_ `TSharedPtr<SButton> CancelButton;` — The secondary button widget.
- L131 _private member_ `FText Message;` — The message to display
- L134 _private member_ `FText Warning;` — The warning to display
- L136 _private member_ `bool bShowingContentVersePath = false;`
- L139 _private member_ `bool bIsProceedButtonPressed = false;` — Set to true if the user clicked on the primary button

### `Source/Editor/SourceControlWindows/Private/SSourceControlSubmit.h` (Private)


#### enum `ESubmitResults::Type`  
`enum Type`  
_L25-30_
- L27 _public enumerator_ `SUBMIT_ACCEPTED`
- L28 _public enumerator_ `SUBMIT_CANCELED`
- L29 _public enumerator_ `SUBMIT_SAVED`

#### class `FChangeListDescription`  
`class FChangeListDescription`  
_L36-42_
- L39 _public member_ `TArray<FString> FilesForAdd;`
- L40 _public member_ `TArray<FString> FilesForSubmit;`
- L41 _public member_ `FText Description;`

#### class `SSourceControlSubmitWidget`  
`class SSourceControlSubmitWidget : public SCompoundWidget`  
_L49-231_
- inherits: `SCompoundWidget`
- L52 _public function_ `SLATE_BEGIN_ARGS(SSourceControlSubmitWidget) : _ParentWindow() , _Items() , _Description() , _ChangeValidationResult() , _ChangeValidationWarnings() , _ChangeValidationErrors() , _AllowDescriptionChange(true) , _AllowUncheckFiles(true) , _AllowKeepCheckedOut(true) , _AllowSubmit(true) , _AllowSaveAndClose(false) , _AllowDiffAgainstDepot(true)`
- L67 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<SWindow>, ParentWindow) SLATE_ATTRIBUTE(TArray<FSourceControlStateRef>, Items) SLATE_ATTRIBUTE(FText, Description) SLATE_ATTRIBUTE(FString, ChangeValidationResult) SLATE_ATTRIBUTE(FString, ChangeValidationWarnings) SLATE_ATTRIBUTE(FString, ChangeValidationErrors) SLATE_ATTRIBUTE(bool, AllowDescriptionChange) SLATE_ATTRIBUTE(bool, AllowUncheckFiles) SLATE_ATTRIBUTE(bool, AllowKeepCheckedOut) SLATE_ATTRIBUTE(bool, AllowSubmit) SLATE_ATTRIBUTE(bool, AllowSaveAndClose) SLATE_ATTRIBUTE(bool, AllowDiffAgainstDepot) SLATE_END_ARGS() ~SSourceControlSubmitWidget();`
- L85 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs the widget
- L88 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — Used to intercept Escape key press, and interpret it as cancel
- L91 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Used to tick the AssetDataCache via the SourceControlModule when the dialog is open to refresh asset names
- L94 _public function_ `ESubmitResults::Type GetResult()` — Get dialog result
- L97 _public prototype_ `void FillChangeListDescription(FChangeListDescription& OutDesc);` — Gets the requested files and the change list description
- L100 _public prototype_ `bool WantToKeepCheckedOut();` — Does the user want to keep the files checked out
- L103 _public prototype_ `void ClearChangeListDescription();` — Clears the current change list description
- L110 _private prototype_ `ECheckBoxState GetToggleSelectedState() const;` — @return the desired toggle state for the ToggleSelectedCheckBox. Returns Unchecked, unless all of the selected items are Checked.
- L116 _private prototype_ `void OnToggleSelectedCheckBox(ECheckBoxState InNewState);` — Toggles the highlighted items. If no items are explicitly highlighted, toggles all items in the list.
- L119 _private prototype_ `FReply SubmitClicked();` — Called when the settings of the dialog are to be accepted
- L122 _private prototype_ `FReply CancelClicked();` — Called when the settings of the dialog are to be ignored
- L125 _private prototype_ `FReply SaveAndCloseClicked();` — Called when the user click the 'Save' button.
- L128 _private prototype_ `bool IsSubmitEnabled() const;` — Called to check if the submit button is enabled or not.
- L131 _private prototype_ `EVisibility IsWarningPanelVisible() const;` — Check if the warning panel should be visible.
- L134 _private prototype_ `bool IsValidationWarningVisible() const;` — Check if the warning should be visible in the warning panel.
- L135 _private prototype_ `bool IsCheckoutWarningVisible() const;`
- L136 _private prototype_ `bool IsDescriptionWarningVisible() const;`
- L139 _private prototype_ `void OnCheckStateChanged_KeepCheckedOut(ECheckBoxState InState);` — Called when the Keep checked out Checkbox is changed
- L142 _private prototype_ `ECheckBoxState GetKeepCheckedOut() const;` — Get the current state of the Keep Checked Out checkbox
- L145 _private prototype_ `bool CanCheckOut() const;` — Check if Provider can checkout files
- L148 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowForList(FChangelistTreeItemPtr SubmitItemData, const TSharedRef<STableViewBase>& OwnerTable);` — Called by SListView to get a widget corresponding to the supplied item
- L158 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;` — Returns the current column sort mode (ascending or descending) if the ColumnId parameter matches the current column to be sorted by, otherwise returns EColumnSortMode_None. @param	ColumnId	Column ID to query sort mode for. @return	The sort mode for the column, or EColumnSortMode_None if it is not known.
- L166 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);` — Callback for SHeaderRow::Column::OnSort, called when the column to sort by is changed. @param	ColumnId	The new column to sort by @param	InSortMode	The sort mode (ascending or descending)
- L168 _private prototype_ `EVisibility GetIconColumnContentVisibility() const;`
- L174 _private prototype_ `void RequestSort();` — Requests that the source list data be sorted according to the current sort column and mode, and refreshes the list view.
- L179 _private prototype_ `void SortTree();` — Sorts the source list data according to the current sort column and mode.
- L181 _private prototype_ `TSharedPtr<SWidget> OnCreateContextMenu();`
- L183 _private prototype_ `bool CanDiffAgainstDepot() const;`
- L184 _private prototype_ `void OnDiffAgainstDepot();`
- L185 _private prototype_ `void OnDiffAgainstDepotSelected(FChangelistTreeItemPtr InSelectedItem);`
- L188 _private prototype_ `bool AllowRevert() const;` — Called to check whether the selected files in the ListView can be reverted
- L189 _private prototype_ `bool CanRevert() const;`
- L192 _private prototype_ `void OnRevert();` — Reverts the files selected in the ListView
- L194 _private prototype_ `static FFileTreeItem* GetFileItem(const FChangelistTreeItemPtr& ChangelistItem);`
- L197 _private member_ `ESubmitResults::Type DialogResult;`
- L200 _private member_ `TSharedPtr<SListView<FChangelistTreeItemPtr>> ListView;` — ListBox for selecting which object to consolidate
- L203 _private member_ `TArray<FChangelistTreeItemPtr> ListViewItems;` — Collection of objects (Widgets) to display in the List View.
- L206 _private member_ `TArray<FSourceControlStateRef> CheckedOutByOther;` — Collection of states that are checked out by other users.
- L209 _private member_ `TWeakPtr<SWindow> ParentFrame;` — Pointer to the parent modal window
- L212 _private member_ `TSharedPtr<SMultiLineEditableTextBox> ChangeListDescriptionTextCtrl;` — Internal widgets to save having to get in multiple places
- L215 _private member_ `ECheckBoxState KeepCheckedOut;` — State of the "Keep checked out" checkbox
- L218 _private member_ `bool bAllowSubmit;` — Whether the submit button should be enabled or not
- L221 _private member_ `bool bAllowDiffAgainstDepot;` — Whether a diff against the depot may be performed from within the submit dialog
- L224 _private member_ `bool bShowingContentVersePath;` — Whether the content verse path should be shown or not
- L227 _private member_ `FName SortByColumn;` — Specify which column to sort with
- L230 _private member_ `EColumnSortMode::Type SortMode;` — Currently selected sorting mode

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace ESubmitResults`
- L44 _prototype_ `bool TryToVirtualizeFilesToSubmit(const TArray<FString>& FilesToSubmit, FText& Description, FText& OutFailureMsg);`
- L45 _prototype_ `bool TryToVirtualizeFilesToSubmit(const TArray<FSourceControlStateRef>& FileStates, FText& Description, FText& OutFailureMsg);`
- L47 _delegate_ `DECLARE_DELEGATE_OneParam(FSourceControlSaveChangelistDescription, const FText& );`
- L47 _prototype_ `DECLARE_DELEGATE_OneParam(FSourceControlSaveChangelistDescription, const FText& );`

### `Source/Editor/SourceControlWindows/Private/SourceControlSettings.h` (Private)


#### class `USourceControlSettings`  
`class USourceControlSettings : public UObject`  
_L10-25_
- reflection: `UCLASS(config=Editor)`
- inherits: `UObject`
- desc: Serializes source control window settings.
- L15 _public function_ `USourceControlSettings()`
- L18 _public member_ `bool bShowAssetTypeColumn = true;` — `UPROPERTY(config, EditAnywhere, Category="Revision Control Changelist View", meta = (Keywords = "Source Control"))`
- L21 _public member_ `bool bShowAssetLastModifiedTimeColumn = true;` — `UPROPERTY(config, EditAnywhere, Category="Revision Control Changelist View", meta = (Keywords = "Source Control"))`
- L24 _public member_ `bool bShowAssetCheckedOutByColumn = true;` — `UPROPERTY(config, EditAnywhere, Category="Revision Control Changelist View", meta = (Keywords = "Source Control"))`

### `Source/Editor/SourceControlWindows/Public/ISourceControlWindowsModule.h` (Public)


#### enum `FSubmitOverrideReply`  
`enum class FSubmitOverrideReply`  
_L14-21_
- L16 _public enumerator_ `Handled`
- L17 _public enumerator_ `ProviderNotSupported`
- L18 _public enumerator_ `Error`
- L20 _public enumerator_ `Num`

#### struct `SSubmitOverrideParameters`  
`struct SSubmitOverrideParameters`  
_L23-27_
- L25 _public member_ `TUnion<FString, TArray<FString>> ToSubmit;`
- L26 _public member_ `FString Description;`

#### struct `FSubmitTitleOverrideParameters`  
`struct FSubmitTitleOverrideParameters`  
_L29-32_
- L31 _public member_ `TUnion<FString, TArray<FString>> ToSubmit;`

#### class `ISourceControlWindowsModule`  
`class ISourceControlWindowsModule : public IModuleInterface`  
_L38-76_
- inherits: `IModuleInterface`
- L44 _public function_ `static inline ISourceControlWindowsModule& Get()` — Get reference to the SourceControlWindows module instance
- L49 _public function_ `static inline ISourceControlWindowsModule* TryGet()`
- L54 _public prototype_ `virtual void ShowChangelistsTab() = 0;`
- L55 _public prototype_ `virtual bool CanShowChangelistsTab() const = 0;`
- L57 _public prototype_ `virtual void ShowSnapshotHistoryTab() = 0;`
- L58 _public prototype_ `virtual bool CanShowSnapshotHistoryTab() const = 0;`
- L60 _public prototype_ `virtual void ShowConflictResolutionTab() = 0;`
- L61 _public prototype_ `virtual bool CanShowConflictResolutionTab() const = 0;`
- L63 _public prototype_ `virtual void ShowBranchExplorerTab() = 0;`
- L64 _public prototype_ `virtual bool CanShowBranchExplorerTab() const = 0;`
- L65 _public prototype_ `virtual bool IsVisibleBranchExplorerTab() const = 0;`
- L67 _public prototype_ `virtual void SelectFiles(const TArray<FString>& Filenames) = 0;`
- L69 _public prototype_ `DECLARE_EVENT_OneParam(ISourceControlWindowsModule, FChangelistFileDoubleClickedEvent, const FString&);`
- L70 _public prototype_ `virtual FChangelistFileDoubleClickedEvent& OnChangelistFileDoubleClicked() = 0;`
- L72 _public member_ `FCanSubmitOverrideDelegate CanSubmitOverrideDelegate;`
- L73 _public member_ `FSubmitOverrideDelegate SubmitOverrideDelegate;`
- L75 _public member_ `FSubmitTitleOverrideDelegate SubmitTitleOverrideDelegate;`

#### Free symbols / members of external scopes

- L34 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FSubmitOverrideReply, FCanSubmitOverrideDelegate, const SSubmitOverrideParameters& , FText* );`
- L34 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FSubmitOverrideReply, FCanSubmitOverrideDelegate, const SSubmitOverrideParameters& , FText* );`
- L35 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FSubmitOverrideReply, FSubmitOverrideDelegate, const SSubmitOverrideParameters& );`
- L35 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FSubmitOverrideReply, FSubmitOverrideDelegate, const SSubmitOverrideParameters& );`
- L36 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FSubmitTitleOverrideDelegate, const FSubmitTitleOverrideParameters& );`
- L36 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FSubmitTitleOverrideDelegate, const FSubmitTitleOverrideParameters& );`
- L69 _delegate_ `DECLARE_EVENT_OneParam(ISourceControlWindowsModule, FChangelistFileDoubleClickedEvent, const FString&);`

### `Source/Editor/SourceControlWindows/Public/SourceControlMenuContext.h` (Public)


#### class `USourceControlMenuContext`  
`class USourceControlMenuContext : public UObject`  
_L15-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Source control window menu context providing information for menu extenders.
- L20 _public function_ `USourceControlMenuContext(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`
- L27 _public member_ `TArray<FString> SelectedFiles;` — `UPROPERTY()`
- L29 _public member_ `FSourceControlChangelistPtr SelectedChangelist;`

### `Source/Editor/SourceControlWindows/Public/SourceControlWindows.h` (Public)


#### class `USourceControlHistoryWidgetContext`  
`class USourceControlHistoryWidgetContext : public UObject`  
_L19-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Context object for SSourceControlHistoryWidget's right-click context menu to get info about which history widget is trying to generate the menu
- L30 _public member_ `TWeakPtr<class SSourceControlHistoryWidget> HistoryWidget;`
- L32 _public function_ `TArray<SelectedItem>& GetSelectedItems()`
- L38 _private member_ `TArray<SelectedItem> SelectedItems;`

#### struct `USourceControlHistoryWidgetContext::SelectedItem`  
`struct SelectedItem`  
_L24-28_
- L26 _public member_ `FString FileName;`
- L27 _public member_ `FString Revision;`

#### class `USourceControlSubmitWidgetContext`  
`class USourceControlSubmitWidgetContext : public UObject`  
_L43-62_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Context object for SSourceControlSubmitWidget's right-click context menu to get info about which submit widget is trying to generate the menu
- L53 _public member_ `TWeakPtr<class SSourceControlSubmitWidget> SubmitWidget;`
- L55 _public function_ `TArray<SelectedItem>& GetSelectedItems()`
- L61 _private member_ `TArray<SelectedItem> SelectedItems;`

#### struct `USourceControlSubmitWidgetContext::SelectedItem`  
`struct SelectedItem`  
_L48-51_
- L50 _public member_ `FString FileName;`

#### struct `FCheckinResultInfo`  
`struct FCheckinResultInfo`  
_L65-84_
- desc: Info supplied as argument to delegate FSourceControlWindowsOnCheckInComplete called by FSourceControlWindows::ChoosePackagesToCheckIn() and optional argument to PromptForCheckin().
- L68 _public prototype_ `FCheckinResultInfo();` — Default Constructor
- L71 _public member_ `ECommandResult::Type Result;` — Succeeded - if packages were selected and successfully checked in, Cancelled - if the user aborted the process, Failed - if an issue was encountered during the process
- L74 _public member_ `bool bAutoCheckedOut;` — true if added and modified files were automatically checked out from source control again after being submitted, false if not
- L77 _public member_ `TArray<FString> FilesAdded;` — Files that were added.
- L80 _public member_ `TArray<FString> FilesSubmitted;` — Files that were modified and checked in.
- L83 _public member_ `FText Description;` — Text that describes result whether failed, cancelled or successful.

#### class `FSourceControlWindows`  
`class FSourceControlWindows`  
_L89-224_
- L98 _public prototype_ `static bool ChoosePackagesToCheckIn(const FSourceControlWindowsOnCheckInComplete& OnCompleteDelegate = FSourceControlWindowsOnCheckInComplete());` — Opens a user dialog to choose packages to submit. @param	OnCompleteDelegate	Delegate to call when this user-based operation is complete. Also see FCheckinResultInfo. @return	true - if command successfully in progress and OnCompleteDelegate will be called when complete, false - if immediately unable to comply (such as source control not enabled)
- L101 _public prototype_ `static bool CanChoosePackagesToCheckIn();` — Determines whether we can choose packages to check in (we can't if an operation is already in progress)
- L105 _public function_ `static bool ShouldChoosePackagesToCheckBeVisible()` — `UE_DEPRECATED(5.6, "ShouldChoosePackagesToCheckBeVisible is deprecated and will be removed")` — Determines if the Submit Content action should be visible or not
- L112 _public prototype_ `static bool SyncLatest();` — Saves all unsaved levels and assets and then - conditionally - performs an FSync operation to get latest and reloads the world @return	true - if command completed successfully.
- L119 _public prototype_ `static bool SyncRevision(const FString& InRevision);` — Saves all unsaved levels and assets and then - conditionally - performs an FSync operation to get the specified revision, and reloads the world @return	true - if command completed successfully.
- L122 _public prototype_ `static bool CanSyncLatest();` — Determines whether we can sync to latest
- L135 _public prototype_ `static bool PromptForCheckin(FCheckinResultInfo& OutResultInfo, const TArray<FString>& InPackageNames, const TArray<FString>& InPendingDeletePaths = TArray<FString>(), const TArray<FString>& InConfigFiles = TArray<FString>(), bool bUseSourceControlStateCache = false);` — Display check in dialog for the specified packages and get additional result information @param	OutResultInfo					Optional FCheckinResultInfo to store information about checked in files and whether the check in was successful @param	InPackageNames					Names of packages to check in @param	InPendingDeletePaths			Directories to check for files marked 'pending delete' @param	InConfigFiles					Config filenames to check in @param	bUseSourceControlStateCache		Whether to use the cached source control status, or force the status to be updated @return	true - if completed successfully in progress and OnCompleteDelegate will be called when complete, false - if immediately unable to comply (such as source control not enabled)
- L147 _public prototype_ `static bool PromptForCheckin(bool bUseSourceControlStateCache, const TArray<FString>& InPackageNames, const TArray<FString>& InPendingDeletePaths = TArray<FString>(), const TArray<FString>& InConfigFiles = TArray<FString>());` — Display check in dialog for the specified packages @param	bUseSourceControlStateCache		Whether to use the cached source control status, or force the status to be updated @param	InPackageNames					Names of packages to check in @param	InPendingDeletePaths			Directories to check for files marked 'pending delete' @param	InConfigFiles					Config filenames to check in @return	true - if completed successfully in progress and OnCompleteDelegate will be called when complete, false - if immediately unable to comply (such as source control not enabled)
- L169 _public prototype_ `static bool PromptForCheckedOut(bool bUseSourceControlStateCache, const TArray<FString>& InFileNames, const FCheckedOutSetupInfo& InSetupInfo);`
- L176 _public prototype_ `static void DisplayRevisionHistory( const TArray<FString>& InPackagesNames );` — Display file revision history for the provided packages @param	InPackageNames	Names of packages to display file revision history for
- L186 _public prototype_ `static bool PromptForRevert(const TArray<FString>& InPackageNames, bool bInReloadWorld = false );` — Prompt the user with a revert files dialog, allowing them to specify which packages, if any, should be reverted. @param	InPackageNames	Names of the packages to consider for reverting @param	bInReloadWorld	Reload the world as part of the revert operation @return	true if the files were reverted; false if the user canceled out of the dialog
- L191 _public prototype_ `static bool RevertAllChangesAndReloadWorld();` — Revert all locally modified files, and reload the world
- L200 _public prototype_ `static bool DiffAgainstWorkspace(const FString& InFileName);` — Displays file diff against workspace version @param InFileName Name of the file to diff @return true if the diff could be performed
- L209 _public prototype_ `static bool DiffAgainstShelvedFile(const FSourceControlStateRef& InFileState);` — Displays file diff against shelved file @param InFileState SCC file state of the file to diff @return true if the diff could be performed
- L213 _protected prototype_ `static void ChoosePackagesToCheckInCallback(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult, FSourceControlWindowsOnCheckInComplete OnCompleteDelegate);` — Callback for ChoosePackagesToCheckIn(), continues to bring up UI once source control operations are complete
- L216 _protected prototype_ `static void ChoosePackagesToCheckInCompleted(const TArray<UPackage*>& LoadedPackages, const TArray<FString>& PackageNames, const TArray<FString>& ConfigFiles, FCheckinResultInfo& OutResultInfo);` — Called when the user selection process has completed and we have packages to check in.
- L219 _protected prototype_ `static void ChoosePackagesToCheckInCancelled(FSourceControlOperationRef InOperation);` — Delegate called when the user has decided to cancel the check in process
- L223 _private member_ `static TWeakPtr<class SNotificationItem> ChoosePackagesToCheckInNotification;` — The notification in place while we choose packages to check in

#### struct `FSourceControlWindows::FCheckedOutSetupInfo`  
`struct FCheckedOutSetupInfo`  
_L157-167_
- desc: Display checked out dialog for the specified filenames @param	bUseSourceControlStateCache		Whether to use the cached source control status, or force the status to be updated @param	InFileNames						Filenames of files that are checked out @param	InSetupInfo						Config options @return	true - if the dialog was closed with the optional checkbox checked
- L159 _public member_ `FText TitleText;`
- L160 _public member_ `FText MessageText;`
- L161 _public member_ `FText CloseText;`
- L162 _public member_ `FText CheckboxText;`
- L164 _public member_ `bool bShowColumnAssetName = true;`
- L165 _public member_ `bool bShowColumnAssetClass = true;`
- L166 _public member_ `bool bShowColumnUserName = true;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API SOURCECONTROLWINDOWS_API`
- L87 _delegate_ `DECLARE_DELEGATE_OneParam(FSourceControlWindowsOnCheckInComplete, const FCheckinResultInfo&);` — Optional delegate called when FSourceControlWindows::ChoosePackagesToCheckIn() completes.
- L87 _prototype_ `DECLARE_DELEGATE_OneParam(FSourceControlWindowsOnCheckInComplete, const FCheckinResultInfo&);` — Optional delegate called when FSourceControlWindows::ChoosePackagesToCheckIn() completes.
