# Editor / ContentBrowser

- module root: `Source/Editor/ContentBrowser`
- headers: 69; symbols: 3585
- symbol kinds: class=107, delegate=109, enum=12, enumerator=38, function=294, macro=10, member=1015, namespace=74, prototype=1838, struct=64, typedef=24
- DynamicallyLoadedModuleNames: CollectionManager, GameProjectGeneration, MainFrame, PackagesDialog, PropertyEditor
- PrivateDependencyModuleNames: AddContentDialog, AppFramework, ApplicationCore, AssetDefinition, AssetRegistry, AssetTagsEditor, AssetTools, ContentBrowserData, Core, CoreUObject, DesktopPlatform, DeveloperSettings, Documentation, EditorConfig, EditorFramework, EditorStyle, EditorWidgets, Engine, InputCore, Projects, Slate, SlateCore, SourceControl, SourceControlWindows, StatusBar, TelemetryUtils, ToolMenus, ToolWidgets, TypedElementFramework, UnrealEd, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: MainFrame
- PublicIncludePathModuleNames: AssetTools, CollectionManager, ContentBrowserData

### `Source/Editor/ContentBrowser/Internal/SAssetPicker.h` (Internal)


#### class `SAssetPicker`  
`class SAssetPicker : public SCompoundWidget`  
_L39-238_
- inherits: `SCompoundWidget`
- desc: Small content browser designed to allow for asset picking
- L42 _public function_ `SLATE_BEGIN_ARGS( SAssetPicker )`
- L45 _public prototype_ `SLATE_ARGUMENT(FAssetPickerConfig, AssetPickerConfig) SLATE_END_ARGS() virtual ~SAssetPicker();` — A struct containing details about how the asset picker should behave
- L52 _public prototype_ `void Construct( const FArguments& InArgs );` — Constructs this widget with InArgs
- L55 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — SWidget implementation
- L59 _public function_ `const TSharedPtr<SAssetView>& GetAssetView() const` — Return the associated AssetView
- L62 _public prototype_ `void ExecuteRenameCommand();` — Function that's called when someone wants to execute a Rename Command
- L64 _public prototype_ `TSharedPtr<SWidget> GetSearchBox() const;`
- L67 _public prototype_ `void ClearSearchText();` — Clears the search box text programmatically. Triggers OnSearchTextChanged -> OnSearchTextChangedDelegate.
- L70 _public prototype_ `TSharedPtr<SFilterList> GetFilterList() const;` — Returns the filter list widget, or nullptr if none was created.
- L73 _public prototype_ `void SyncToItems(TArrayView<const FContentBrowserItem> ItemsToSync, const bool bAllowImplicitSync = false, const bool bDisableFiltersThatHideAssets = true);` — Syncs the AssetPicker to select the provided items.
- L77 _private prototype_ `EActiveTimerReturnType SetFocusPostConstruct( double InCurrentTime, float InDeltaTime );` — Focuses the search box post-construct
- L80 _private prototype_ `FReply HandleKeyDownFromSearchBox(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — Special case handling for SAssetSearchBox key commands
- L82 _private prototype_ `void FolderEntered(const FString& FolderPath);`
- L85 _private prototype_ `void SetSearchBoxText(const FText& InSearchText);` — Called when the editable text needs to be set or cleared
- L88 _private prototype_ `void OnSearchBoxChanged(const FText& InSearchText);` — Called by the editable text control when the search text is changed by the user
- L91 _private prototype_ `void OnSearchBoxCommitted(const FText& InSearchText, ETextCommit::Type CommitInfo);` — Called by the editable text control when the user commits a text change
- L94 _private prototype_ `void SetNewBackendFilter(const FARFilter& NewFilter);` — Called from external code to set the filter after the widget was created
- L97 _private prototype_ `void OnFilterChanged();` — Called when the user changes filters
- L100 _private prototype_ `FReply OnNoneButtonClicked();` — Handler for when the "None" button is clicked
- L103 _private prototype_ `void HandleNewItemRequested(const FContentBrowserItem& NewItem);` — Handler for when a new item is requested in the asset view
- L106 _private prototype_ `void HandleItemSelectionChanged(const FContentBrowserItem& InSelectedItem, ESelectInfo::Type InSelectInfo);` — Handle forwarding picking events. We wrap OnAssetSelected here to prevent 'Direct' selections being identified as user actions
- L109 _private prototype_ `void HandleItemsActivated(TArrayView<const FContentBrowserItem> ActivatedItems, EAssetTypeActivationMethod::Type ActivationMethod);` — Handler for when the user double clicks, presses enter, or presses space on an asset
- L112 _private prototype_ `void HandleItemsDragged(TArrayView<const FContentBrowserItem> DraggedItems);` — Handler for when the user drags an asset
- L115 _private prototype_ `void SyncToAssets(const TArray<FAssetData>& AssetDataList);` — Selects the paths containing the specified assets.
- L118 _private prototype_ `TArray< FAssetData > GetCurrentSelection();` — @return The currently selected asset
- L121 _private prototype_ `void RefreshAssetView(bool bRefreshSources);` — Forces a refresh
- L124 _private prototype_ `FText GetHighlightedText() const;` — @return The text to highlight on the assets
- L127 _private prototype_ `FText GetShowOtherDevelopersToolTip() const;` — @return The tooltip for the other developers filter button depending on checked state.
- L130 _private prototype_ `void HandleShowOtherDevelopersCheckStateChanged( const ECheckBoxState InCheckboxState );` — Toggles the filter for showing other developers assets
- L133 _private prototype_ `ECheckBoxState GetShowOtherDevelopersCheckState() const;` — Gets if showing other developers assets
- L136 _private prototype_ `bool IsShowingOtherDevelopersContent() const;` — Returns whether the ShowOtherDevelopersFilter is active i.e. if we should show content belonging to other developers
- L139 _private prototype_ `void OnRenameRequested() const;` — Called upon the Rename UICommand being executed, sends rename request to the asset view
- L142 _private prototype_ `bool CanExecuteRenameRequested();` — Returns true if the user is able to execute a rename request
- L145 _private prototype_ `bool CanFilterBySelection();` — Returns true if the user is able to execute filter by selection request
- L148 _private prototype_ `void OnFilterBySelection();` — Executes command and applies filters based on active selection
- L151 _private prototype_ `void BindCommands();` — Bind our UI commands
- L154 _private prototype_ `void LoadSettings();` — Loads settings for this asset picker if SaveSettingsName was set
- L157 _private prototype_ `void SaveSettings() const;` — Saves settings for this asset picker if SaveSettingsName was set
- L159 _private prototype_ `void HandleSearchSettingsChanged();`
- L162 _private prototype_ `TSharedPtr<SWidget> GetItemContextMenu(TArrayView<const FContentBrowserItem> SelectedItems);` — Handler for the context menu for asset or folder items
- L165 _private prototype_ `TOptional<FAssetCategoryPath> ConvertAssetTypeCategoryToAssetCategoryPath(EAssetTypeCategories::Type DefaultFilterMenuExpansion);` — Converts an asset type category into an asset category path, if possible. This is done because the asset picker config still uses asset type categories.
- L170 _private member_ `TSharedPtr<FAssetFilterCollectionType> FrontendFilters;` — The list of FrontendFilters currently applied to the asset view
- L173 _private member_ `TSharedPtr<SAssetView> AssetViewPtr;` — The asset view widget
- L176 _private member_ `TSharedPtr<SAssetSearchBox> SearchBoxPtr;` — The search box
- L179 _private member_ `TSharedPtr<SFilterList> FilterListPtr;` — The filter list
- L182 _private member_ `TSharedPtr<SComboButton> FilterComboButtonPtr;` — The filter combo button
- L185 _private member_ `FOnAssetSelected OnAssetSelected;` — Called to when an asset is selected or the none button is pressed
- L188 _private member_ `FOnAssetDoubleClicked OnAssetDoubleClicked;` — Called to when an asset is double clicked
- L191 _private member_ `FOnAssetEnterPressed OnAssetEnterPressed;` — Called when enter is pressed while an asset is selected
- L194 _private member_ `FOnAssetsActivated OnAssetsActivated;` — Called when any number of assets are activated
- L197 _private member_ `FOnAssetsDragged OnAssetsDragged;` — Called any number of assets are dragged
- L200 _private member_ `FOnPathSelected OnFolderEnteredDelegate;` — Called when a folder is entered in the asset view
- L203 _private member_ `FOnSearchTextChanged OnSearchTextChangedDelegate;` — Fired when the search box text changes, forwarded from FAssetPickerConfig::OnSearchTextChanged.
- L206 _private member_ `FOnGetAssetContextMenu OnGetAssetContextMenu;` — Delegate to invoke when a context menu for an asset is opening.
- L209 _private member_ `FOnGetFolderContextMenu OnGetFolderContextMenu;` — Delegate to invoke when a context menu for a folder is opening.
- L212 _private member_ `bool bPendingFocusNextFrame;` — True if the search box will take keyboard focus next frame
- L215 _private member_ `TSharedPtr< FAssetFilterCollectionType > FilterCollection;` — Filters needed for filtering the assets
- L216 _private member_ `TSharedPtr<class FAssetTextFilter> TextFilter;`
- L217 _private member_ `TSharedPtr<FFilter_HideOtherDevelopers> HideOtherDevelopersFilter;`
- L219 _private member_ `EAssetTypeCategories::Type DefaultFilterMenuExpansion;`
- L222 _private member_ `FAssetViewContentSources CurrentContentSources;` — The sources data currently used by the picker
- L225 _private member_ `FARFilter CurrentBackendFilter;` — Current filter we are using, needed reset asset view after we have custom filtered
- L228 _private member_ `TSharedPtr< FUICommandList > Commands;` — UICommand list, holds list of actions for processing
- L231 _private member_ `FString SaveSettingsName;` — If set, view settings will be saved and loaded for the asset view using this name in ini files
- L234 _private member_ `TOptional<FString> FilterBarSaveSettingsNameOverride;` — If set, uses this name for the filter bar identifier instead of the SaveSettingsName
- L237 _private member_ `bool bAllowRename;` — Wether to allow renaming of items

### `Source/Editor/ContentBrowser/Internal/SFilterList.h` (Internal)


#### class `SFilterList`  
`class SFilterList : public SAssetFilterBar<FAssetFilterType>`  
_L41-262_
- inherits: `SAssetFilterBar<FAssetFilterType>`
- desc: A list of filters currently applied to an asset view.
- L43 _private typedef_ `using Super = SAssetFilterBar<FAssetFilterType>;`
- L49 _public prototype_ `DECLARE_EVENT_OneParam(SFilterList, FCustomTextFilterEvent, TSharedPtr<SWidget> );` — An event delegate that is executed when a custom text filter has been created/modified/deleted in any FilterList that is using shared settings.
- L51 _public typedef_ `using FOnFilterChanged = typename SAssetFilterBar<FAssetFilterType>::FOnFilterChanged;`
- L53 _public function_ `SLATE_BEGIN_ARGS( SFilterList ) : _UseSharedSettings(false) , _FilterBarLayout(EFilterBarLayout::Horizontal) , _CanChangeOrientation(false) , _DefaultMenuExpansionCategory(EAssetCategoryPaths::Basic) , _bUseSectionsForCustomCategories(false)`
- L63 _public prototype_ `SLATE_EVENT( FOnFilterChanged, OnFilterChanged ) SLATE_EVENT(FOnExtendAddFilterMenu, OnExtendAddFilterMenu) SLATE_ARGUMENT( TSharedPtr<FAssetFilterCollectionType>, FrontendFilters) SLATE_ARGUMENT( TArray<UClass*>, InitialClassFilters) SLATE_ARGUMENT( TArray< TSharedRef<FFrontendFilter> >, ExtraFrontendFilters ) SLATE_ARGUMENT(FCreateTextFilter, CreateTextFilter) SLATE_ARGUMENT(FName, FilterBarIdentifier) SLATE_ARGUMENT(bool, UseSharedSettings) SLATE_EVENT(FOnFilterBarLayoutChanging, OnFilterBarLayoutChanging) SLATE_ARGUMENT(EFilterBarLayout, FilterBarLayout) SLATE_ARGUMENT(bool, CanChangeOrientation) SLATE_ARGUMENT(TOptional<FAssetCategoryPath>, DefaultMenuExpansionCategory)` — Delegate for when filters have changed
- L114 _public prototype_ `void SetFrontendFilterCheckState(const TSharedPtr<FFrontendFilter>& InFrontendFilter, ECheckBoxState CheckState);` — Set the check box state of the specified frontend filter (in the filter drop down) and pin/unpin a filter widget on/from the filter bar. When a filter is pinned (was not already pinned), it is activated and deactivated when unpinned.
- L117 _public prototype_ `ECheckBoxState GetFrontendFilterCheckState(const TSharedPtr<FFrontendFilter>& InFrontendFilter) const;` — Returns the check box state of the specified frontend filter (in the filter drop down). This tells whether the filter is pinned or not on the filter bar, but not if filter is active or not. @see IsFrontendFilterActive().
- L120 _public prototype_ `bool IsFrontendFilterActive(const TSharedPtr<FFrontendFilter>& InFrontendFilter) const;` — Returns true if the specified frontend filter is both checked (pinned on the filter bar) and active (contributing to filter the result).
- L123 _public prototype_ `TSharedPtr<FFrontendFilter> GetFrontendFilter(const FString& InName) const;` — Retrieve a specific frontend filter
- L130 _public prototype_ `FARFilter GetCombinedBackendFilter(TArray<TSharedRef<const FPathPermissionList>>& OutPermissionLists) const;` — Replaces super version of GetCombinedBackendFilter to allow returning FPathPermissionLists as well. Permission lists will be combined into a content browser data filter after a delay. Filters may modify them via the shared ref but should not do so off the game thread.
- L131 _public prototype_ `FARFilter GetCombinedBackendFilter() const = delete;`
- L134 _public prototype_ `TSharedRef<SWidget> ExternalMakeAddFilterMenu();` — Handler for when the floating add filter button was clicked
- L137 _public prototype_ `void DisableFiltersThatHideItems(TArrayView<const FContentBrowserItem> ItemList);` — Disables any active filters that would hide the supplied items
- L140 _public prototype_ `const TArray<UClass*>& GetInitialClassFilters();` — Returns the class filters specified at construction using argument 'InitialClassFilters'.
- L143 _public prototype_ `void CreateCustomFilterDialog(const FText& InText);` — Open the dialog to create a custom filter from the given text
- L146 _public prototype_ `void UpdateCustomTextFilterIncludes(const bool InIncludeClassName, const bool InIncludeAssetPath, const bool InIncludeCollectionNames);` — Updates bIncludeClassName, bIncludeAssetPath and bIncludeCollectionNames for all custom text filters
- L149 _public prototype_ `void AddWidgetToCurrentLayout(TSharedRef<SWidget> InWidget);` — Add a custom widget to the filter bar alongside the filters
- L152 _public prototype_ `virtual void LoadSettings() override;`
- L155 _public prototype_ `void LoadSettings(const FName& InInstanceName);` — Copy the settings from a specific instance name
- L158 _public prototype_ `void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString);` — Helper functions for backwards compatibility with filters that save state until they are ported to EditorConfig
- L159 _public prototype_ `void LoadSettings(const FName& InInstanceName, const FString& IniFilename, const FString& IniSection, const FString& SettingsString);`
- L162 _public prototype_ `virtual void OnCreateCustomTextFilter(const FCustomTextFilterData& InFilterData, bool bApplyFilter) override;` — Handler for when a custom text filter is created
- L165 _public prototype_ `void DeleteCustomTextFilterByLabel(const FText& FilterLabel);` — Deletes the custom text filter with the matching label
- L168 _public prototype_ `void ModifyCustomTextFilterByLabel(const FCustomTextFilterData& NewFilterData, const FText& FilterLabel);` — Modifies the custom text filter with the matching label
- L171 _public prototype_ `bool IsFilteringPathsRecursively() const;` — Whether the filters are being applied to paths recursively
- L174 _public prototype_ `void SetFilterPathsRecursively(const bool bInFilterRecursively);` — Sets whether the filters are being applied to paths recursively
- L177 _public prototype_ `void ToggleFilterPathsRecursively();` — Toggle whether the filters are being applied to paths recursively
- L180 _public prototype_ `void ToggleSortFiltersAlphabetically();` — Toggle whether the filters are sorted and displayed alphabetically
- L183 _public prototype_ `TSharedPtr<SWidget> GetActiveFilterContainer() const;` — Returns a pointer to the active filter container widget (Horizontal or Vertical), nullptr if neither is active
- L186 _public function_ `const TArray<TSharedRef<FFrontendFilter>>& GetAllFrontendFilters() const` — Returns all frontend filters registered with this filter bar (built-in, extra, and extension-provided).
- L189 _public function_ `const TArray<TSharedRef<FCustomClassFilterData>>& GetCustomClassFilters() const` — Returns all custom class/type filters registered with this filter bar.
- L196 _public prototype_ `void ActivateClassFilterByPath(const FTopLevelAssetPath& ClassPath);` — Activates a class filter by class path: - If not yet pinned: pins and enables it. - If already pinned (e.g. disabled): enables it in-place without re-pinning.
- L203 _protected prototype_ `virtual void SaveSettingsInternal(FFilterBarSettings* InSettingsToSave) override;`
- L206 _protected prototype_ `virtual void OnModifyCustomTextFilter(const FCustomTextFilterData& InFilterData, TSharedPtr<ICustomTextFilter<FAssetFilterType>> InFilter) override;` — Handler for when a custom text filter is modified
- L209 _protected prototype_ `virtual void OnDeleteCustomTextFilter(const TSharedPtr<ICustomTextFilter<FAssetFilterType>> InFilter) override;` — Handler for when a custom text filter is deleted
- L216 _private prototype_ `virtual UAssetFilterBarContext* CreateAssetFilterBarContext() override;`
- L219 _private prototype_ `virtual void PopulateAddFilterMenu(UToolMenu* Menu, TSharedPtr<FFilterCategory> MenuExpansion, FOnFilterAssetType OnFilterAssetType) override;` — Handler to Populate the Add Filter Menu. Use OnFilterAssetType in Subclasses to add classes to the exclusion list
- L222 _private prototype_ `void OnExternalCustomTextFilterCreated(TSharedPtr<SWidget> BroadcastingFilterList);` — Handler for when another SFilterList using shared settings creates a custom text filter
- L225 _private prototype_ `void LoadCustomTextFilters(const FFilterBarSettings* FilterBarConfig);` — Empty our list of custom text filters, and load from the given config
- L230 _private prototype_ `bool RestoreCustomTextFilterState(const FCustomTextFilterState& InFilterState);` — Find the custom text filter corresponding to the specified state, and restore it's state to what is specified @return True if the filter was restored successfully, false if not
- L234 _private member_ `TArray<UClass*> InitialClassFilters;` — List of classes that our filters must match
- L237 _private member_ `FOnFilterChanged OnFilterChanged;` — Delegate for when filters have changed
- L240 _private member_ `TArray< TSharedRef<FFrontendFilter> > AllFrontendFilters_Internal;` — A reference to AllFrontEndFilters so we can access the filters as FFrontEndFilter instead of FFilterBase<FAssetFilterType>
- L243 _private member_ `static const FName SharedIdentifier;` — An identifier shared by all SFilterLists, used to save and load settings common to every instance
- L246 _private member_ `bool bIncludeClassName;` — If bIncludeClassName is true, custom text filters will include an asset's class name in the search
- L249 _private member_ `bool bIncludeAssetPath;` — If bIncludeAssetPath is true, custom text filters will match against full Asset path
- L252 _private member_ `bool bIncludeCollectionNames;` — If bIncludeCollectionNames is true, custom text filters will match against collection names as well
- L255 _private member_ `bool bUseSharedSettings;` — Whether this FilterList wants to load/save from the settings common to all instances
- L258 _private member_ `bool bFilterPathsRecursively = true;` — Whether this FilterList applies to paths recursively
- L261 _private member_ `static FCustomTextFilterEvent CustomTextFilterEvent;` — The event that executes when a custom text filter is created/modified/deleted in any filter list that is using Shared Settings

#### class `FFrontendFilter_CustomText`  
`class FFrontendFilter_CustomText : public ICustomTextFilter<FAssetFilterType>, public FFrontendFilter, public TSharedFromThis<FFrontendFilter_CustomText>`  
_L269-313_
- inherits: `ICustomTextFilter<FAssetFilterType>,FFrontendFilter,TSharedFromThis<FFrontendFilter_CustomText>`
- desc: A custom implementation of ICustomTextFilter that uses FFrontendFilter_Text to handle comparing items in the Asset View to Custom Text Filters. This ensures that the advanced search syntax etc behaves properly when used by a custom text filter created by saving a search. This is implemented as a fake frontend filter which modifies background asynchronous text filtering behavior in the asset view.
- L275 _public prototype_ `FFrontendFilter_CustomText();`
- L278 _public prototype_ `virtual FString GetName() const override;` — FFrontendFilter implementation
- L279 _public prototype_ `virtual FText GetDisplayName() const override;`
- L280 _public prototype_ `virtual FText GetToolTipText() const override;`
- L281 _public prototype_ `virtual FLinearColor GetColor() const override;`
- L282 _public prototype_ `virtual TOptional<FText> GetAsCustomTextFilter();`
- L283 _public function_ `virtual bool PassesFilter(FAssetFilterType InItem) const override`
- L286 _public prototype_ `void UpdateCustomTextFilterIncludes(const bool InIncludeClassName, const bool InIncludeAssetPath, const bool InIncludeCollectionNames);` — Updates bIncludeClassName, bIncludeAssetPath and bIncludeCollectionNames for this filter
- L291 _public prototype_ `virtual void SetFromCustomTextFilterData(const FCustomTextFilterData& InFilterData) override;` — Set the internals of this filter from an FCustomTextFilterData
- L294 _public prototype_ `virtual FCustomTextFilterData CreateCustomTextFilterData() const override;` — Create an FCustomTextFilterData from the internals of this filter
- L297 _public prototype_ `virtual TSharedPtr<FFilterBase<FAssetFilterType>> GetFilter() override;` — Get the actual filter
- L302 _protected member_ `FText DisplayName;` — The Display Name of this custom filter that the user sees
- L305 _protected member_ `FText RawFilterText;` — The raw text of the query, either simple string or advanced search syntax.
- L308 _protected member_ `FLinearColor Color;` — The Color of this filter pill
- L310 _protected member_ `bool bIncludeClassName = false;`
- L311 _protected member_ `bool bIncludeAssetPath = false;`
- L312 _protected member_ `bool bIncludeCollectionNames = false;`

#### Free symbols / members of external scopes

- L49 _delegate_ `DECLARE_EVENT_OneParam(SFilterList, FCustomTextFilterEvent, TSharedPtr<SWidget> );` — An event delegate that is executed when a custom text filter has been created/modified/deleted in any FilterList that is using shared settings.

### `Source/Editor/ContentBrowser/Private/AssetContextMenu.h` (Private)


#### class `FAssetContextMenu`  
`class FAssetContextMenu : public TSharedFromThis<FAssetContextMenu>`  
_L28-206_
- inherits: `TSharedFromThis<FAssetContextMenu>`
- L32 _public prototype_ `FAssetContextMenu(const TWeakPtr<SAssetView>& InAssetView);` — Constructor
- L35 _public prototype_ `void BindCommands(TSharedPtr< FUICommandList >& Commands);` — Binds the commands used by the asset view context menu to the content browser command list
- L38 _public prototype_ `TSharedRef<SWidget> MakeContextMenu(TArrayView<const FContentBrowserItem> InSelectedItems, const FAssetViewContentSources& InContentSources, TSharedPtr< FUICommandList > InCommandList);` — Makes the context menu widget
- L41 _public prototype_ `void SetSelectedItems(TArrayView<const FContentBrowserItem> InSelectedItems);` — Updates the list of currently selected items to those passed in
- L44 _public function_ `const TArray<FContentBrowserItem>& GetSelectedItems() const` — Read-only access to the list of currently selected items
- L46 _public typedef_ `using FOnShowInPathsViewRequested = UContentBrowserDataMenuContext_FileMenu::FOnShowInPathsView;`
- L47 _public prototype_ `void SetOnShowInPathsViewRequested(const FOnShowInPathsViewRequested& InOnShowInPathsViewRequested);`
- L50 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnRenameRequested, const FContentBrowserItem& , EContentBrowserViewContext );` — Delegate for when the context menu requests a rename
- L51 _public prototype_ `void SetOnRenameRequested(const FOnRenameRequested& InOnRenameRequested);`
- L54 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDuplicateRequested, TArrayView<const FContentBrowserItem> );` — Delegate for when the context menu requests an item duplication
- L55 _public prototype_ `void SetOnDuplicateRequested(const FOnDuplicateRequested& InOnDuplicateRequested);`
- L58 _public typedef_ `using FOnAssetViewRefreshRequested = UContentBrowserDataMenuContext_FileMenu::FOnRefreshView;` — Delegate for when the context menu requests an asset view refresh
- L59 _public prototype_ `void SetOnAssetViewRefreshRequested(const FOnAssetViewRefreshRequested& InOnAssetViewRefreshRequested);`
- L62 _public prototype_ `bool CanExecuteRename() const;` — Handler to check to see if a rename command is allowed
- L65 _public prototype_ `void ExecuteRename(EContentBrowserViewContext ViewContext);` — Handler for Rename
- L68 _public prototype_ `bool CanExecuteDelete() const;` — Handler to check to see if a delete command is allowed
- L71 _public prototype_ `void ExecuteDelete();` — Handler for Delete
- L74 _public prototype_ `bool CanExecuteSaveAsset() const;` — Handler to check to see if "Save Asset" can be executed
- L77 _public prototype_ `void ExecuteSaveAsset();` — Handler for when "Save Asset" is selected
- L81 _private prototype_ `bool CanExecuteDuplicate() const;` — Handler to check to see if a duplicate command is allowed
- L84 _private prototype_ `void ExecuteDuplicate();` — Handler for Duplicate
- L87 _private prototype_ `static void RegisterMenuHierarchy(UClass* InClass);` — Registers all unregistered menus in the hierarchy for a class
- L90 _private prototype_ `void AddMenuOptions(UToolMenu* InMenu);` — Adds options to menu
- L93 _private prototype_ `bool AddAssetTypeMenuOptions(UToolMenu* Menu);` — Adds asset type-specific menu options to a menu builder. Returns true if any options were added.
- L96 _private prototype_ `bool AddCommonMenuOptions(UToolMenu* Menu);` — Adds common menu options to a menu builder. Returns true if any options were added.
- L99 _private prototype_ `void AddExploreMenuOptions(UToolMenu* Menu);` — Adds explore menu options to a menu builder.
- L102 _private prototype_ `bool AddReferenceMenuOptions(UToolMenu* Menu);` — Adds asset reference menu options to a menu builder. Returns true if any options were added.
- L105 _private prototype_ `FText GetEditAssetEditorLabel(bool bInCanEdit, bool bInCanView) const;` — Get the correct Label for the OpenAssetEditor command
- L108 _private prototype_ `FText GetEditAssetEditorTooltip(bool bInCanEdit, bool bInCanView) const;` — Get the correct Tooltip for the OpenAssetEditor command
- L111 _private prototype_ `FSlateIcon GetEditAssetEditorIcon(bool bInCanEdit, bool bInCanView) const;` — Get the correct Icon for the OpenAssetEditor command
- L114 _private prototype_ `FText GetCopyTooltip(EAssetViewCopyType InCopyType) const;` — Return the tooltip based on the copy type
- L117 _private prototype_ `FText GetSelectionInformationForCopy(EAssetViewCopyType InCopyType) const;` — Append information on the path for the Copy tooltip based on the current selection
- L119 _private prototype_ `bool AddPublicStateMenuOptions(UToolMenu* Menu);`
- L122 _private prototype_ `bool AddCollectionMenuOptions(UToolMenu* Menu);` — Adds menu options related to working with collections
- L125 _private prototype_ `void ExecuteSyncToAssetTree();` — Handler for when sync to asset tree is selected
- L128 _private prototype_ `void ExecuteFindInExplorer();` — Handler for when find in explorer is selected
- L131 _private prototype_ `FReply ExecuteDeleteFolderConfirmed();` — Handler for confirmation of folder deletion
- L134 _private prototype_ `FText GetDeleteToolTip() const;` — Get tooltip for delete
- L137 _private prototype_ `bool GetAssetAccessSpecifierFromSelection(EAssetAccessSpecifier& OutAssetAccessSpecifier);` — Try to get AssetAccessSpecifier for asset
- L140 _private prototype_ `static int32 CompareAssetAccessSpecifiers(EAssetAccessSpecifier A, EAssetAccessSpecifier B);` — Compares two access specifiers.  Returns < 0 if A less accessible than B, > 0 if A more accessible than B, and 0 if they are equal.
- L143 _private prototype_ `void ExecuteSetAssetAccessSpecifier(EAssetAccessSpecifier InAssetAccessSpecifier);` — Handler for when new AssetAccessSpecifier is chosen.
- L146 _private prototype_ `bool CanSetAssetAccessSpecifier(const EAssetAccessSpecifier InAssetAccessSpecifier) const;` — Handler to check to see if can set to a specific AssetAccessSpecifier is allowed
- L149 _private prototype_ `void ExecuteBulkSetAssetAccessSpecifier(EAssetAccessSpecifier InAssetAccessSpecifier);` — Handler for setting all selected assets to a specific AssetAccessSpecifier
- L152 _private prototype_ `bool CanExecuteBulkSetAssetAccessSpecifier(EAssetAccessSpecifier InAssetAccessSpecifier);` — Handler to check if all selected assets can have their AssetAccessSpecifier changed
- L155 _private prototype_ `bool IsSelectedAssetAccessSpecifier(EAssetAccessSpecifier InAssetAccessSpecifier);` — Handler for determining the selected asset's AssetAccessSpecifier state
- L158 _private prototype_ `void ExecuteCopyFilePath();` — Handler for CopyFilePath
- L161 _private prototype_ `void ExecuteRemoveFromCollection();` — Handler for when "Remove from collection" is selected
- L164 _private prototype_ `bool CanExecuteSyncToAssetTree() const;` — Handler to check to see if a sync to asset tree command is allowed
- L167 _private prototype_ `bool CanExecuteFindInExplorer() const;` — Handler to check to see if a find in explorer command is allowed
- L170 _private prototype_ `bool CanExecuteRemoveFromCollection() const;` — Handler to check to see if a "Remove from collection" command is allowed
- L173 _private prototype_ `void CacheCanExecuteVars();` — Initializes some variable used to in "CanExecute" checks that won't change at runtime or are too expensive to check every frame.
- L176 _private prototype_ `void RegisterContextMenu(const FName MenuName);` — Registers the base context menu for assets
- L178 _private member_ `TArray<FContentBrowserItem> SelectedItems;`
- L179 _private member_ `TArray<FContentBrowserItem> SelectedFiles;`
- L180 _private member_ `TArray<FContentBrowserItem> SelectedFolders;`
- L182 _private member_ `FAssetViewContentSources ContentSources;`
- L185 _private member_ `TWeakPtr<SAssetView> AssetView;` — The asset view this context menu is a part of
- L187 _private member_ `FOnShowInPathsViewRequested OnShowInPathsViewRequested;`
- L188 _private member_ `FOnRenameRequested OnRenameRequested;`
- L189 _private member_ `FOnDuplicateRequested OnDuplicateRequested;`
- L190 _private member_ `FOnAssetViewRefreshRequested OnAssetViewRefreshRequested;`
- L193 _private member_ `bool bCanExecuteFindInExplorer = false;` — Cached CanExecute vars
- L195 _private member_ `bool bCanShowSetAssetAccessMenu = false;`
- L197 _private member_ `bool bCanExecuteSetPublicAsset = false;`
- L198 _private member_ `bool bCanExecuteSetEpicInternalAsset = false;`
- L199 _private member_ `bool bCanExecuteSetPrivateAsset = false;`
- L201 _private member_ `bool bCanExecuteBulkSetPublicAsset = false;`
- L202 _private member_ `bool bCanExecuteBulkSetEpicInternalAsset = false;`
- L203 _private member_ `bool bCanExecuteBulkSetPrivateAsset = false;`
- L205 _private member_ `FText DisallowSetPublicReason;`

#### Free symbols / members of external scopes

- L50 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRenameRequested, const FContentBrowserItem& , EContentBrowserViewContext );` — Delegate for when the context menu requests a rename
- L54 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDuplicateRequested, TArrayView<const FContentBrowserItem> );` — Delegate for when the context menu requests an item duplication

### `Source/Editor/ContentBrowser/Private/AssetSystemContentBrowserInfoProvider.h` (Private)


#### class `FAssetSystemContentBrowserInfoProvider`  
`class FAssetSystemContentBrowserInfoProvider : public IAssetSystemInfoProvider`  
_L16-73_
- inherits: `IAssetSystemInfoProvider`
- L19 _public prototype_ `FAssetSystemContentBrowserInfoProvider() = delete;`
- L20 _public prototype_ `FAssetSystemContentBrowserInfoProvider(const TSharedPtr<FAssetViewItem>& InAssetItem);`
- L23 _public prototype_ `virtual void PopulateAssetInfo(TArray<FAssetDisplayInfo>& OutAssetDisplayInfo) const override;`
- L27 _private prototype_ `void CacheDisplayTags();` — Cache the Display Tags for this asset, called everytime the ItemAssetData change
- L30 _private prototype_ `void CacheDirtyExternalPackageInfo();` — Cache the External Package Info if any, called everytime the ItemAssetData change
- L33 _private prototype_ `FText GetExternalPackagesText() const;` — Get the CachedDirtyExternalPackage Text
- L36 _private prototype_ `FText GetAssetUserDescription() const;` — Get the Item Description for this item
- L57 _private member_ `TArray<FTagContentBrowserDisplayItem> CachedDisplayTags;` — The cached display tags for this item
- L60 _private member_ `bool bShouldSaveExternalPackages = false;` — Whether it should save external package
- L63 _private member_ `FString CachedDirtyExternalPackagesList;` — The cached external package to save
- L66 _private member_ `FDelegateHandle OnItemDataChangedCacheDisplayTagsDelegateHandle;` — Delegate handle of the CacheDisplayTags
- L69 _private member_ `FDelegateHandle OnItemDataChangedCacheDirtyExternalPackageDelegateHandle;` — Delegate handle of the CacheDirtyPackage
- L72 _private member_ `TSharedPtr<FAssetViewItem> AssetItem;` — AssetViewItem of this provider

#### struct `FAssetSystemContentBrowserInfoProvider::FTagContentBrowserDisplayItem`  
`struct FTagContentBrowserDisplayItem`  
_L40-54_
- desc: Data for a cached display tag for this item (used in the tooltip, and also as the display string in column views)
- L42 _public function_ `FTagContentBrowserDisplayItem(FName InTagKey, FText InDisplayKey, FText InDisplayValue, const bool InImportant) : TagKey(InTagKey) , DisplayKey(MoveTemp(InDisplayKey)) , DisplayValue(MoveTemp(InDisplayValue)) , bImportant(InImportant)`
- L50 _public member_ `FName TagKey;`
- L51 _public member_ `FText DisplayKey;`
- L52 _public member_ `FText DisplayValue;`
- L53 _public member_ `bool bImportant;`

### `Source/Editor/ContentBrowser/Private/AssetView/AssetViewConfig.h` (Private)


#### struct `FAssetViewInstanceConfig`  
`struct FAssetViewInstanceConfig`  
_L16-37_
- reflection: `USTRUCT()`
- L24 _public member_ `uint8 ThumbnailSize = 0;` — `UPROPERTY()` — The current thumbnail size, as cast from EThumbnailSize, because that enum is not a UENUM.
- L30 _public member_ `uint8 ViewType = 0;` — `UPROPERTY()` — The current thumbnail size, as cast from EAssetViewType, because that enum is not a UENUM.
- L33 _public member_ `TArray<FName> HiddenColumns;` — `UPROPERTY()`
- L36 _public member_ `TArray<FName> ListHiddenColumns;` — `UPROPERTY()`

#### class `UAssetViewConfig`  
`class UAssetViewConfig : public UEditorConfigBase`  
_L40-55_
- reflection: `UCLASS(MinimalAPI, EditorConfig="AssetView")`
- inherits: `UEditorConfigBase`
- L45 _public prototype_ `static void Initialize();`
- L46 _public function_ `static UAssetViewConfig* Get()`
- L48 _public prototype_ `FAssetViewInstanceConfig& GetInstanceConfig(FName ViewName);`
- L51 _public member_ `TMap<FName, FAssetViewInstanceConfig> Instances;` — `UPROPERTY(meta=(EditorConfig))`
- L54 _private member_ `static TObjectPtr<UAssetViewConfig> Instance;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CONTENTBROWSER_API`

### `Source/Editor/ContentBrowser/Private/CollectionAssetRegistryBridge.h` (Private)


#### class `FCollectionAssetRegistryBridge`  
`class FCollectionAssetRegistryBridge`  
_L12-27_
- desc: The bridge between the asset registry and the collections manager - used to update collections as certain asset events happen
- L15 _public prototype_ `FCollectionAssetRegistryBridge();`
- L16 _public prototype_ `~FCollectionAssetRegistryBridge();`
- L20 _private prototype_ `void OnAssetRegistryLoadComplete();` — Called when the asset registry initial load has completed
- L23 _private prototype_ `void OnAssetRenamed(const FAssetData& AssetData, const FString& OldObjectPath);` — Handler for when an asset was renamed in the asset registry
- L26 _private prototype_ `void OnAssetsRemoved(TConstArrayView<FAssetData> AssetDatas);` — Handler for when assets were removed from the asset registry

### `Source/Editor/ContentBrowser/Private/CollectionContextMenu.h` (Private)


#### class `FCollectionContextMenu`  
`class FCollectionContextMenu : public TSharedFromThis<FCollectionContextMenu>`  
_L18-120_
- inherits: `TSharedFromThis<FCollectionContextMenu>`
- L22 _public prototype_ `FCollectionContextMenu(const TWeakPtr<SCollectionView>& InCollectionView);` — Constructor
- L25 _public prototype_ `void BindCommands(TSharedPtr< FUICommandList > InCommandList);` — Bind menu selection commands to the command list
- L28 _public prototype_ `TSharedPtr<SWidget> MakeCollectionTreeContextMenu(TSharedPtr< FUICommandList > InCommandList);` — Makes the collection tree context menu widget
- L31 _public prototype_ `void MakeNewCollectionSubMenu(FMenuBuilder& MenuBuilder, ECollectionStorageMode::Type StorageMode, SCollectionView::FCreateCollectionPayload InCreationPayload);` — Makes the new collection submenu
- L34 _public prototype_ `void MakeSaveDynamicCollectionSubMenu(FMenuBuilder& MenuBuilder, FText InSearchQuery);` — Makes the save dynamic collection submenu
- L37 _public prototype_ `void MakeCollectionShareTypeSubMenu(FMenuBuilder& MenuBuilder);` — Makes the collection share type submenu
- L40 _public prototype_ `void UpdateProjectSourceControl();` — Update the source control flag the 'CanExecute' functions rely on
- L43 _public prototype_ `bool CanRenameSelectedCollections() const;` — Can the selected collections be renamed?
- L47 _protected prototype_ `void MakeSetColorSubMenu(FMenuBuilder& MenuBuilder);` — Makes the set color submenu
- L51 _private prototype_ `void ExecuteNewCollection(ECollectionShareType::Type CollectionType, ECollectionStorageMode::Type StorageMode, SCollectionView::FCreateCollectionPayload InCreationPayload);` — Handler for when a collection is selected in the "New" menu
- L54 _private prototype_ `void ExecuteSetCollectionShareType(ECollectionShareType::Type CollectionType);` — Handler for when a collection share type is changed in the "Share Type" menu
- L57 _private prototype_ `void ExecuteSaveDynamicCollection(FCollectionNameType InCollection, FText InSearchQuery);` — Handler for when a dynamic collection is selected in the "Save" menu
- L60 _private prototype_ `void ExecuteRenameCollection();` — Handler for when "Rename Collection" is selected
- L63 _private prototype_ `void ExecuteUpdateCollection();` — Handler for when "Update Collection" is selected
- L66 _private prototype_ `void ExecuteRefreshCollection();` — Handler for when "Refresh Collection" is selected
- L69 _private prototype_ `void ExecuteSaveCollection();` — Handler for when "Save Collection" is selected
- L72 _private prototype_ `void ExecuteDestroyCollection();` — Handler for when "Destroy Collection" is selected
- L75 _private prototype_ `FReply ExecuteDestroyCollectionConfirmed(TArray<TSharedPtr<FCollectionItem>> CollectionList);` — Handler for when "Destroy Collection" is confirmed
- L78 _private prototype_ `void ExecuteResetColor();` — Handler for when reset color is selected
- L81 _private prototype_ `void ExecutePickColor();` — Handler for when new or set color is selected
- L84 _private prototype_ `bool CanExecuteNewCollection(ECollectionShareType::Type CollectionType, bool bIsValidChildType) const;` — Handler to check to see if "New Collection" can be executed
- L87 _private prototype_ `bool CanExecuteSetCollectionShareType(ECollectionShareType::Type CollectionType) const;` — Handler to check to see if a entry in the "Share Type" menu can be executed
- L90 _private prototype_ `bool IsSetCollectionShareTypeChecked(ECollectionShareType::Type CollectionType) const;` — Handler to check to see if an entry in the "Share Type" menu should be checked
- L93 _private prototype_ `bool CanExecuteSaveDynamicCollection(FCollectionNameType InCollection) const;` — Handler to check to see if "Save Dynamic Collection" can be executed
- L96 _private prototype_ `bool CanExecuteRenameCollection() const;` — Handler to check to see if "Rename Collection" can be executed
- L99 _private prototype_ `bool CanExecuteDestroyCollection(bool bAnyManagedBySCC, bool bAnyWritable) const;` — Handler to check to see if "Destroy Collection" can be executed
- L102 _private prototype_ `bool SelectedHasCustomColors() const;` — Checks to see if any of the selected collections use custom colors
- L105 _private prototype_ `bool CanExecuteColorChange() const;` — Handler to check to see if "Set/Clear Color" can be executed
- L108 _private prototype_ `FReply OnColorClicked( const FLinearColor InColor );` — Callback when the color is picked from the set color submenu
- L111 _private prototype_ `void OnColorCommitted( const FLinearColor InColor );` — Callback when the color is picked from the set color submenu or picker
- L114 _private prototype_ `void ResetColors();` — Resets the colors of the selected collections
- L116 _private member_ `TWeakPtr<SCollectionView> CollectionView;`
- L119 _private member_ `bool bCollectionsUnderSourceControl;` — Flag caching whether the shared collections folder is under source control

### `Source/Editor/ContentBrowser/Private/CollectionViewTypes.h` (Private)


#### enum `ECollectionItemStatus`  
`enum class ECollectionItemStatus : uint8`  
_L11-33_
- desc: Status states that a collection item can be in
- L14 _public enumerator_ `IsUpToDateAndPopulated` — The collection is up-to-date in source control, and isn't empty
- L17 _public enumerator_ `IsUpToDateAndEmpty` — The collection is up-to-date in source control, but is empty
- L20 _public enumerator_ `IsOutOfDate` — The collection is out-of-date in source control
- L23 _public enumerator_ `IsCheckedOutByAnotherUser` — The collection is checked out by another source control user, so can't be modified at this time
- L26 _public enumerator_ `IsConflicted` — The collection is conflicted in source control, so can't be modified at this time
- L29 _public enumerator_ `IsMissingSCCProvider` — The collection is under source control but the SCC provider is currently unavailable, so can't be modified at this time
- L32 _public enumerator_ `HasLocalChanges` — The collection has local changes that either haven't been saved, or haven't been committed to source control

#### struct `FCollectionItem`  
`struct FCollectionItem`  
_L36-105_
- desc: A list item representing a collection
- L47 _public member_ `TSharedPtr<ICollectionContainer> CollectionContainer;` — The container of this item
- L50 _public member_ `FName CollectionName;` — The name of the collection
- L53 _public member_ `ECollectionShareType::Type CollectionType;` — The type of the collection
- L56 _public member_ `ECollectionStorageMode::Type StorageMode;` — How does this collection store its objects? (static or dynamic)
- L59 _public member_ `TWeakPtr<FCollectionItem> ParentCollection;` — Pointer to our parent collection (if any)
- L62 _public member_ `TArray<TWeakPtr<FCollectionItem>> ChildCollections;` — Array of pointers to our child collections (if any)
- L65 _public member_ `bool bRenaming;` — If true, will set up an inline rename after next ScrollIntoView
- L68 _public member_ `bool bNewCollection;` — If true, this item will be created the next time it is renamed
- L71 _public member_ `int32 NumObjects;` — The number of objects in this collection (static collections only)
- L74 _public member_ `ECollectionItemStatus CurrentStatus;` — Current status of this collection item
- L77 _public member_ `FLinearColor CollectionColor;` — The color of the collection
- L80 _public prototype_ `DECLARE_DELEGATE_OneParam( FCollectionCreatedEvent, FCollectionNameType ) DECLARE_MULTICAST_DELEGATE( FRenamedRequestEvent ) FCollectionCreatedEvent OnCollectionCreatedEvent;` — Called once after the collection is created (see bNewCollection)
- L89 _public member_ `FRenamedRequestEvent OnRenamedRequestEvent;` — Broadcasts whenever a rename is requested
- L92 _public function_ `FCollectionItem(const TSharedRef<ICollectionContainer>& InCollectionContainer, const FName& InCollectionName, const ECollectionShareType::Type InCollectionType) : CollectionContainer(InCollectionContainer) , CollectionName(InCollectionName) , CollectionType(InCollectionType) , StorageMode(ECollectionStorageMode::Static) , ParentCollection() , ChildCollections() , bRenaming(false) , bNewCollection(false) , NumObjects(0) , CurrentStatus(ECollectionItemStatus::IsUpToDateAndEmpty) , CollectionColor(FLinearColor::White)` — Constructor

#### struct `FCollectionItem::FCompareFCollectionItemByName`  
`struct FCompareFCollectionItemByName`  
_L38-44_
- L40 _public function_ `FORCEINLINE bool operator()( const TSharedPtr<FCollectionItem>& A, const TSharedPtr<FCollectionItem>& B ) const`

#### Free symbols / members of external scopes

- L80 _delegate_ `DECLARE_DELEGATE_OneParam( FCollectionCreatedEvent, FCollectionNameType ) DECLARE_MULTICAST_DELEGATE( FRenamedRequestEvent ) FCollectionCreatedEvent OnCollectionCreatedEvent;` — Called once after the collection is created (see bNewCollection)
- L83 _delegate_ `DECLARE_MULTICAST_DELEGATE( FRenamedRequestEvent ) FCollectionCreatedEvent OnCollectionCreatedEvent;` — Broadcasts whenever renaming a collection item is requested

### `Source/Editor/ContentBrowser/Private/CollectionViewUtils.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace CollectionViewUtils`
- L22 _prototype_ `FLinearColor ResolveColor(const ICollectionContainer& InCollectionContainer, const FName InCollectionName, const ECollectionShareType::Type& InCollectionType);` (scope `CollectionViewUtils`) — Resolve the color of the collection, falling back to the default if no custom color is set @param InCollectionName - The name of the collection to resolve the color for @param InCollectionType - The type of the collection to resolve the color for @return The color the collection should appear as
- L31 _prototype_ `TOptional<FLinearColor> GetCustomColor(const ICollectionContainer* InCollectionContainer, const FName InCollectionName, const ECollectionShareType::Type& InCollectionType);` (scope `CollectionViewUtils`) — Gets the color of the collection @param InCollectionName - The name of the collection to get the color for @param InCollectionType - The type of the collection to get the color for @return The color the collection should appear as, will be empty if not customized
- L40 _prototype_ `void SetCustomColor(ICollectionContainer& InCollectionContainer, const FName InCollectionName, const ECollectionShareType::Type& InCollectionType, const TOptional<FLinearColor>& CollectionColor);` (scope `CollectionViewUtils`) — Sets the color of the collection @param InCollectionName - The name of the collection to set the color for @param InCollectionType - The type of the collection to set the color for @param CollectionColor - The color the collection should appear as, or an empty color to clear it
- L48 _prototype_ `bool HasCustomColors(const ICollectionContainer& InCollectionContainer, TArray<FLinearColor>* OutColors = nullptr);` (scope `CollectionViewUtils`) — Checks to see if any collection has a custom color, optionally outputs them to a list @param OutColors - If specified, returns all the custom colors being used @return true, if custom colors are present
- L51 _prototype_ `FLinearColor GetDefaultColor();` (scope `CollectionViewUtils`) — Gets the default color the collection should appear as

### `Source/Editor/ContentBrowser/Private/ContentBrowserCommands.h` (Private)


#### class `FContentBrowserCommands`  
`class FContentBrowserCommands : public TCommands<FContentBrowserCommands>`  
_L15-45_
- inherits: `TCommands<FContentBrowserCommands>`
- L19 _public member_ `static const FName GenericCommandsName;`
- L22 _public function_ `FContentBrowserCommands() : TCommands<FContentBrowserCommands>(TEXT("ContentBrowser"), NSLOCTEXT( "ContentBrowser", "ContentBrowser", "Content Browser" ), (FInputBindingManager::Get().GetContextByName(GenericCommandsName).IsValid() ? GenericCommandsName : NAME_None), FAppStyle::GetAppStyleSetName())` — Default constructor.
- L27 _public prototype_ `virtual void RegisterCommands() override;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> CreateNewFolder;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> OpenAssetsOrFolders;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> GoUpToParentFolder;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> PreviewAssets;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> SaveSelectedAsset;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> SaveAllCurrentFolder;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ResaveAllCurrentFolder;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> EditPath;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> AssetViewCopyObjectPath;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> AssetViewCopyPackageName;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> GridViewShortcut;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> ListViewShortcut;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> ColumnViewShortcut;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> FilterBySelection;`
- L44 _public member_ `TArray<TSharedPtr<FUICommandInfo>> FavoriteShortcuts;`

### `Source/Editor/ContentBrowser/Private/ContentBrowserConfig.h` (Private)


#### struct `FPathViewConfig`  
`struct FPathViewConfig`  
_L14-23_
- reflection: `USTRUCT()`
- L19 _public member_ `bool bExpanded = false;` — `UPROPERTY()`
- L22 _public member_ `TArray<FString> PluginFilters;` — `UPROPERTY()`

#### struct `FContentBrowserInstanceConfig`  
`struct FContentBrowserInstanceConfig`  
_L26-77_
- reflection: `USTRUCT()`
- L31 _public member_ `FPathViewConfig PathView;` — `UPROPERTY()`
- L34 _public member_ `bool bShowFavorites = true;` — `UPROPERTY()`
- L37 _public member_ `bool bFavoritesExpanded = true;` — `UPROPERTY()`
- L40 _public member_ `bool bSourcesExpanded = true;` — `UPROPERTY()`
- L43 _public member_ `bool bFilterRecursively = false;` — `UPROPERTY()`
- L46 _public member_ `bool bShowFolders = true;` — `UPROPERTY()`
- L49 _public member_ `bool bShowEmptyFolders = true;` — `UPROPERTY()`
- L52 _public member_ `bool bShowEngineContent = false;` — `UPROPERTY()`
- L55 _public member_ `bool bShowDeveloperContent = false;` — `UPROPERTY()`
- L58 _public member_ `bool bShowLocalizedContent = false;` — `UPROPERTY()`
- L61 _public member_ `bool bShowPluginContent = false;` — `UPROPERTY()`
- L64 _public member_ `bool bShowCppFolders = false;` — `UPROPERTY()`
- L67 _public member_ `bool bSearchClasses = false;` — `UPROPERTY()`
- L70 _public member_ `bool bSearchAssetPaths = false;` — `UPROPERTY()`
- L73 _public member_ `bool bSearchCollections = false;` — `UPROPERTY()`
- L76 _public member_ `bool bShowAssetAccessSpecifier = false;` — `UPROPERTY()`

#### struct `FContentBrowserFavoriteItem`  
`struct FContentBrowserFavoriteItem`  
_L80-110_
- reflection: `USTRUCT()`
- L86 _public member_ `FString Path;` — `UPROPERTY()` — Internal path to the folder/item
- L90 _public member_ `FString Alias;` — `UPROPERTY()` — Friendly name given to this item
- L94 _public member_ `FName ShortcutCommandName;` — `UPROPERTY()` — Name of the command this item should respond to
- L96 _public function_ `bool operator==(const FContentBrowserFavoriteItem& Other) const`
- L101 _public function_ `bool operator!=(const FContentBrowserFavoriteItem& Other) const`

#### class `UContentBrowserConfig`  
`class UContentBrowserConfig : public UEditorConfigBase`  
_L113-126_
- reflection: `UCLASS(EditorConfig="ContentBrowser")`
- inherits: `UEditorConfigBase`
- L118 _public prototype_ `static void Initialize();`
- L119 _public function_ `static UContentBrowserConfig* Get()`
- L122 _public member_ `TMap<FName, FContentBrowserInstanceConfig> Instances;` — `UPROPERTY(meta=(EditorConfig))`
- L125 _private member_ `static TObjectPtr<UContentBrowserConfig> Instance;`

#### class `UContentBrowserCollectionProjectSettings`  
`class UContentBrowserCollectionProjectSettings : public UDeveloperSettings`  
_L129-136_
- reflection: `UCLASS(minimalapi, Config=Editor, DisplayName="Content Browser")`
- inherits: `UDeveloperSettings`
- L135 _public member_ `TArray<FName> ExcludedCollectionsFromView;` — `UPROPERTY(config, EditAnywhere, Category=Collections, meta = (DisplayName="Exclude these collections from Content Browser"))`

#### class `UContentBrowserFavoriteProjectSettings`  
`class UContentBrowserFavoriteProjectSettings : public UDeveloperSettings`  
_L139-149_
- reflection: `UCLASS(MinimalApi, Config = EditorPerProjectUserSettings)`
- inherits: `UDeveloperSettings`
- L144 _public prototype_ `static UContentBrowserFavoriteProjectSettings* Get();`
- L148 _public member_ `TArray<FContentBrowserFavoriteItem> FavoriteItems;` — `UPROPERTY(Config)` — Favorite items for a specific project

#### Free symbols / members of external scopes

- L106 _function_ `friend uint32 GetTypeHash(const FContentBrowserFavoriteItem& InItem)`

### `Source/Editor/ContentBrowser/Private/ContentBrowserLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogContentBrowser, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogContentBrowser, Log, All);`

### `Source/Editor/ContentBrowser/Private/ContentBrowserMenuUtils.h` (Private)


#### struct `FFiltersAdditionalParams`  
`struct FFiltersAdditionalParams`  
_L15-31_
- desc: Additional parameter for the content filters
- L17 _public function_ `FFiltersAdditionalParams()`
- L26 _public member_ `FCanExecuteAction CanShowCPPClasses;`
- L27 _public member_ `FCanExecuteAction CanShowDevelopersContent;`
- L28 _public member_ `FCanExecuteAction CanShowEngineFolder;`
- L29 _public member_ `FCanExecuteAction CanShowPluginFolder;`
- L30 _public member_ `FCanExecuteAction CanShowLocalizedContent;`

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace ContentBrowserMenuUtils`
- L41 _prototype_ `void AddFiltersToMenu(UToolMenu* InMenu, const FName& InOwningContentBrowserName, FFiltersAdditionalParams InFiltersAdditionalParams = FFiltersAdditionalParams());` (scope `ContentBrowserMenuUtils`) — Add content browser filters to the given InMenu @param InMenu Menu to add filter to @param InOwningContentBrowserName ContentBrowser owner name @param InFiltersAdditionalParams Additional filters params

### `Source/Editor/ContentBrowser/Private/ContentBrowserPathViewMenuContexts.h` (Private)


#### class `UContentBrowserPathViewContextMenuContext`  
`class UContentBrowserPathViewContextMenuContext : public UObject`  
_L17-24_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Context for the PathView setting combo button
- L22 _public member_ `FName OwningContentBrowserName;`
- L23 _public member_ `TWeakPtr<SPathView> PathView;`

### `Source/Editor/ContentBrowser/Private/ContentBrowserSingleton.h` (Private)


#### struct `FContentBrowserPluginSettings`  
`struct FContentBrowserPluginSettings`  
_L44-58_
- reflection: `USTRUCT()`
- L49 _public member_ `FName PluginName;` — `UPROPERTY()`
- L53 _public member_ `float RootFolderSortPriority;` — `UPROPERTY()` — Used to control the order of plugin root folders in the path view. A higher priority sorts higher in the list. Game and Engine folders are priority 1.0
- L55 _public function_ `FContentBrowserPluginSettings() : RootFolderSortPriority(0.f)`

#### struct `FShowPrivateContentState`  
`struct FShowPrivateContentState`  
_L60-64_
- L62 _public member_ `TSharedPtr<FPathPermissionList> InvariantPaths;`
- L63 _public member_ `TSharedPtr<FPathPermissionList> CachedVirtualPaths;`

#### class `FContentBrowserSingleton`  
`class FContentBrowserSingleton : public IContentBrowserSingleton`  
_L69-245_
- inherits: `IContentBrowserSingleton`
- desc: Content browser module singleton implementation class
- L73 _public prototype_ `FContentBrowserSingleton();` — Constructor, Destructor
- L74 _public prototype_ `virtual ~FContentBrowserSingleton();`
- L77 _public prototype_ `virtual TSharedRef<SWidget> CreateContentBrowser( const FName InstanceName, TSharedPtr<SDockTab> ContainingTab, const FContentBrowserConfig* ContentBrowserConfig ) override;` — IContentBrowserSingleton interface
- L78 _public prototype_ `virtual TSharedRef<SWidget> CreateAssetPicker(const FAssetPickerConfig& AssetPickerConfig) override;`
- L79 _public prototype_ `virtual TSharedPtr<SWidget> GetAssetPickerSearchBox(const TSharedRef<SWidget>& AssetPickerWidget) override;`
- L80 _public prototype_ `virtual TSharedRef<SWidget> CreatePathPicker(const FPathPickerConfig& PathPickerConfig) override;`
- L81 _public prototype_ `virtual TSharedRef<SWidget> CreateCollectionPicker(const FCollectionPickerConfig& CollectionPickerConfig) override;`
- L82 _public prototype_ `virtual TSharedRef<SWidget> CreateContentBrowserDrawer(const FContentBrowserConfig& ContentBrowserConfig, TFunction<TSharedPtr<SDockTab>()> InOnGetTabForDrawer) override;`
- L83 _public prototype_ `virtual void CreateOpenAssetDialog(const FOpenAssetDialogConfig& OpenAssetConfig, const FOnAssetsChosenForOpen& OnAssetsChosenForOpen, const FOnAssetDialogCancelled& OnAssetDialogCancelled) override;`
- L84 _public prototype_ `virtual TArray<FAssetData> CreateModalOpenAssetDialog(const FOpenAssetDialogConfig& InConfig) override;`
- L85 _public prototype_ `virtual void CreateSaveAssetDialog(const FSaveAssetDialogConfig& SaveAssetConfig, const FOnObjectPathChosenForSave& OnAssetNameChosenForSave, const FOnAssetDialogCancelled& OnAssetDialogCancelled) override;`
- L86 _public prototype_ `virtual FString CreateModalSaveAssetDialog(const FSaveAssetDialogConfig& SaveAssetConfig) override;`
- L87 _public prototype_ `virtual bool HasPrimaryContentBrowser() const override;`
- L88 _public prototype_ `virtual bool SetPrimaryContentBrowser(FName InstanceName) override;`
- L89 _public prototype_ `virtual void FocusPrimaryContentBrowser(bool bFocusSearch) override;`
- L90 _public prototype_ `virtual void FocusContentBrowserSearchField(TSharedPtr<SWidget> ContentBrowserWidget) override;`
- L91 _public prototype_ `virtual void CreateNewAsset(const FString& DefaultAssetName, const FString& PackagePath, UClass* AssetClass, UFactory* Factory) override;`
- L92 _public prototype_ `virtual void SyncBrowserToAssets(const TArray<struct FAssetData>& AssetDataList, bool bAllowLockedBrowsers = false, bool bFocusContentBrowser = true, const FName& InstanceName = FName(), bool bNewSpawnBrowser = false) override;`
- L93 _public prototype_ `virtual void SyncBrowserToAssets(const TArray<UObject*>& AssetList, bool bAllowLockedBrowsers = false, bool bFocusContentBrowser = true, const FName& InstanceName = FName(), bool bNewSpawnBrowser = false) override;`
- L94 _public prototype_ `virtual void SyncBrowserToFolders(const TArray<FString>& FolderList, bool bAllowLockedBrowsers = false, bool bFocusContentBrowser = true, const FName& InstanceName = FName(), bool bNewSpawnBrowser = false) override;`
- L95 _public prototype_ `virtual void SyncBrowserToCollections(const TArray<FCollectionRef>& CollectionsToSync, bool bAllowLockedBrowsers = false, bool bFocusContentBrowser = true, const FName& InstanceName = FName(), bool bNewSpawnBrowser = false) override;`
- L96 _public prototype_ `virtual void SyncBrowserToItems(const TArray<FContentBrowserItem>& ItemsToSync, bool bAllowLockedBrowsers = false, bool bFocusContentBrowser = true, const FName& InstanceName = FName(), bool bNewSpawnBrowser = false) override;`
- L97 _public prototype_ `virtual void SyncBrowserTo(const FContentBrowserSelection& ItemSelection, bool bAllowLockedBrowsers = false, bool bFocusContentBrowser = true, const FName& InstanceName = FName(), bool bNewSpawnBrowser = false) override;`
- L98 _public prototype_ `virtual void GetSelectedAssets(TArray<FAssetData>& SelectedAssets) override;`
- L99 _public prototype_ `virtual void GetAllSelectedAssets(TArray<FAssetData>& SelectedAssets) override;`
- L100 _public prototype_ `virtual void GetSelectedFolders(TArray<FString>& SelectedFolders) override;`
- L101 _public prototype_ `virtual void GetSelectedPathViewFolders(TArray<FString>& SelectedFolders) override;`
- L103 _public prototype_ `virtual FString GetCurrentPath(const EContentBrowserPathType PathType) override;`
- L105 _public prototype_ `virtual FContentBrowserItemPath GetCurrentPath() override;`
- L106 _public prototype_ `virtual void CaptureThumbnailFromViewport(FViewport* InViewport, TArray<FAssetData>& SelectedAssets) override;`
- L107 _public prototype_ `virtual void SetSelectedPaths(const TArray<FString>& FolderPaths, bool bNeedsRefresh = false, bool bPathsAreVirtual = false) override;`
- L108 _public prototype_ `virtual void ForceShowPluginContent(bool bEnginePlugin) override;`
- L109 _public prototype_ `virtual FContentBrowserItemPath GetInitialPathToSaveAsset(const FContentBrowserItemPath& InPath) override;`
- L110 _public prototype_ `virtual void SaveContentBrowserSettings(TSharedPtr<SWidget> ContentBrowserWidget) override;`
- L111 _public prototype_ `virtual void ExecuteRename(TSharedPtr<SWidget> PickerWidget) override;`
- L112 _public prototype_ `virtual void ExecuteAddFolder(TSharedPtr<SWidget> PathPickerWidget) override;`
- L113 _public prototype_ `virtual void RefreshPathView(TSharedPtr<SWidget> PathPickerWidget) override;`
- L114 _public prototype_ `virtual bool IsShowingPrivateContent(const FStringView VirtualFolderPath) override;`
- L115 _public prototype_ `virtual bool IsFolderShowPrivateContentToggleable(const FStringView VirtualFolderPath) override;`
- L116 _public prototype_ `virtual const TSharedPtr<FPathPermissionList>& GetShowPrivateContentPermissionList() override;`
- L117 _public prototype_ `virtual const TSharedPtr<FPathPermissionList>& GetShowEpicInternalContentPermissionList() override;`
- L118 _public prototype_ `virtual void SetPrivateContentPermissionListDirty() override;`
- L119 _public prototype_ `virtual void RegisterIsFolderShowPrivateContentToggleableDelegate(FIsFolderShowPrivateContentToggleableDelegate InIsFolderShowPrivateContentToggleableDelegate) override;`
- L120 _public prototype_ `virtual void UnregisterIsFolderShowPrivateContentToggleableDelegate() override;`
- L121 _public prototype_ `virtual FDelegateHandle RegisterOnFavoritesChangedHandler(FOnFavoritesChanged::FDelegate InOnFavoritesChanged) override;`
- L123 _public prototype_ `virtual FDelegateHandle RegisterOnFavoritesChangedHandler(FSimpleDelegate OnFavoritesChanged) override;` — `UE_DEPRECATED(5.7, "Use the overload that takes in an FOnFavoritesChanged delegate")`
- L124 _public prototype_ `virtual void UnregisterOnFavoritesChangedDelegate(FDelegateHandle Handle) override;`
- L125 _public prototype_ `virtual void RefreshFavoritesPathView() override;`
- L126 _public prototype_ `virtual TArray<FString> GetAliasesForPath(const FSoftObjectPath& InPath) const override;`
- L127 _public prototype_ `virtual void AddCustomTextFilter(const FCustomTextFilterData& FilterData, bool bApplyFilter) override;`
- L128 _public prototype_ `virtual void DeleteCustomTextFilterByLabel(const FText& FilterLabel) override;`
- L129 _public prototype_ `virtual void ModifyCustomTextFilterByLabel(const FCustomTextFilterData& NewFilterData, const FText& FilterLabel) override;`
- L130 _public prototype_ `virtual bool IsAssetViewDoneFiltering() override;`
- L131 _public prototype_ `virtual void SetSearchText(const FText& NewText) override;`
- L132 _public prototype_ `virtual void ToggleFolderFavorite(const TArray<FString>& FolderPaths) override;`
- L133 _public prototype_ `virtual void ForEachFavoriteFolder(TFunctionRef<void(const FContentBrowserItemPath&)> InDelegate) override;`
- L134 _public prototype_ `virtual void SetFilterLayout(EFilterBarLayout InFilterBarLayout) override;`
- L135 _public prototype_ `virtual TSharedPtr<SWidget> GetActiveFilterContainer() override;`
- L136 _public prototype_ `virtual EFilterBarLayout GetFilterLayout() override;`
- L137 _public prototype_ `virtual void DockContentBrowserDrawer() override;`
- L138 _public prototype_ `virtual void RegisterContentSourceFactory(const FName& InContentSourceName, const FContentSourceFactory& InContentSourceFactory) override;`
- L139 _public prototype_ `virtual void UnregisterContentSourceFactory(const FName& InContentSourceName) override;`
- L140 _public prototype_ `virtual void ForEachContentSourceFactory(const TFunctionRef<void(const FName&, const FContentSourceFactory&)>& InFunction) override;`
- L141 _public prototype_ `virtual FOnContentSourceFactoriesChanged& OnContentSourceFactoriesChanged() override;`
- L144 _public prototype_ `void BroadcastFavoritesChanged(const FContentBrowserItemPath& ChangedItem, bool bAdded) const;` — Broadcast that the favorites have changed.
- L147 _public prototype_ `static FContentBrowserSingleton& Get();` — Gets the content browser singleton as a FContentBrowserSingleton
- L150 _public prototype_ `void SetPrimaryContentBrowser(const TSharedRef<SContentBrowser>& NewPrimaryBrowser);` — Sets the current primary content browser.
- L153 _public prototype_ `void ContentBrowserClosed(const TSharedRef<SContentBrowser>& ClosedBrowser);` — Notifies the singleton that a browser was closed
- L156 _public prototype_ `const FContentBrowserPluginSettings& GetPluginSettings(FName PluginName) const;` — Gets the settings for the plugin with the specified name
- L159 _public prototype_ `void OpenEditFavoriteItemWindow(const FContentBrowserFavoriteItem& InItem);` — Opens window to edit a favorite item and close old one if any
- L163 _private prototype_ `void OnFavoriteItemEdited(const FContentBrowserFavoriteItem& InItem, bool bInAnyChanges);` — Callback for when favorite item has been edited
- L166 _private prototype_ `TSharedPtr<SContentBrowser> FindContentBrowserToSync(bool bAllowLockedBrowsers, const FName& InstanceName = FName(), bool bNewSpawnBrowser = false);` — Util to get or create the content browser that should be used by the various Sync functions
- L169 _private prototype_ `void SharedCreateAssetDialogWindow(const TSharedRef<class SAssetDialog>& AssetDialog, const FSharedAssetDialogConfig& InConfig, bool bModal) const;` — Shared code to open an asset dialog window with a config
- L174 _private prototype_ `void OnEditorLoadSelectedAssetsIfNeeded();` — Delegate handlers
- L177 _private prototype_ `void ChooseNewPrimaryBrowser();` — Sets the primary content browser to the next valid browser in the list of all browsers
- L180 _private prototype_ `void FocusContentBrowser(const TSharedPtr<SContentBrowser>& BrowserToFocus);` — Gives focus to the specified content browser
- L183 _private prototype_ `FName SummonNewBrowser(bool bAllowLockedBrowsers = false, TSharedPtr<FTabManager> SpecificTabManager = nullptr);` — Summons a new content browser
- L186 _private prototype_ `TSharedRef<SDockTab> SpawnContentBrowserTab( const FSpawnTabArgs& SpawnTabArgs, int32 BrowserIdx );` — Handler for a request to spawn a new content browser tab
- L189 _private prototype_ `FText GetContentBrowserTabLabel(int32 BrowserIdx);` — Handler for a request to spawn a new content browser tab
- L192 _private prototype_ `bool IsLocked(const FName& InstanceName) const;` — Returns true if this content browser is locked (can be used even when closed)
- L195 _private prototype_ `static FText GetContentBrowserLabelWithIndex( int32 BrowserIdx );` — Returns a localized name for the tab/menu entry with index
- L198 _private prototype_ `void PopulateConfigValues();` — Populates properties that come from ini files
- L201 _private prototype_ `void GetContentBrowserSubMenu(UToolMenu* Menu, TSharedRef<FWorkspaceItem> ContentBrowserGroup);` — Creates the Content Browser submenu in the Level Editor Toolbar Add menu
- L203 _private prototype_ `void ExtendContentBrowserTabContextMenu(FMenuBuilder& InMenuBuilder);`
- L206 _private prototype_ `void RebuildPrivateContentStateCache();` — Rebuilds the private content state cache based off of the currently registered Invariant Path permission list
- L210 _public member_ `FName ContentBrowserTabIDs[MAX_CONTENT_BROWSERS];` — The tab identifier/instance name for content browser tabs
- L214 _private member_ `FIsFolderShowPrivateContentToggleableDelegate IsFolderShowPrivateContentToggleableDelegate;`
- L216 _private member_ `TArray<TWeakPtr<SContentBrowser>> AllContentBrowsers;`
- L218 _private member_ `TWeakPtr<SContentBrowser> ContentBrowserDrawer;`
- L220 _private member_ `TFunction<TSharedPtr<SDockTab>()> OnGetTabForDrawer;`
- L222 _private member_ `TMap<FName, TWeakPtr<FTabManager>> BrowserToLastKnownTabManagerMap;`
- L224 _private member_ `TWeakPtr<SContentBrowser> PrimaryContentBrowser;`
- L226 _private member_ `TSharedRef<FCollectionAssetRegistryBridge> CollectionAssetRegistryBridge;`
- L228 _private member_ `TArray<FContentBrowserPluginSettings> PluginSettings;`
- L230 _private member_ `TArray<TSharedPtr<FTabSpawnerEntry>> ContentBrowserTabs;`
- L233 _private member_ `int32 SettingsStringID;` — An incrementing int32 which is used when making unique settings strings
- L235 _private member_ `FShowPrivateContentState ShowPrivateContentState;`
- L236 _private member_ `FShowPrivateContentState ShowEpicInternalContentState;`
- L238 _private member_ `FOnFavoritesChanged OnFavoritesChanged;`
- L241 _private member_ `TWeakPtr<SWindow> EditFavoriteItemWindowWeak;` — Window dialog to edit a favorite item
- L243 _private member_ `TMap<FName, FContentSourceFactory> ContentSourceFactories;`
- L244 _private member_ `FOnContentSourceFactoriesChanged ContentSourceFactoriesChangedEvent;`

#### Free symbols / members of external scopes

- L41 _macro_ `#define MAX_CONTENT_BROWSERS 4`

### `Source/Editor/ContentBrowser/Private/ContentBrowserStyle.h` (Private)


#### class `UE::ContentBrowser::Private::FContentBrowserStyle`  
`class FContentBrowserStyle : public FSlateStyleSet`  
_L29-52_
- inherits: `FSlateStyleSet`
- L33 _public prototype_ `static FContentBrowserStyle& Get();`
- L35 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L38 _private prototype_ `FContentBrowserStyle();`
- L42 _private member_ `static FName StyleName;`
- L45 _private member_ `FSlateColor DefaultForeground;` — Colors and Styles inherited from the parent style
- L46 _private member_ `FSlateColor InvertedForeground;`
- L47 _private member_ `FSlateColor SelectionColor;`
- L48 _private member_ `FSlateColor SelectionColor_Pressed;`
- L50 _private member_ `FTextBlockStyle NormalText;`
- L51 _private member_ `FButtonStyle Button;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)
- L11 _function_ `static bool IsNewStyleEnabled()` (scope `UE::Editor::ContentBrowser`)
- L15 _function_ `` (scope `UE::Editor::ContentBrowser::IsNewStyleEnabled`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace ContentBrowser` (scope `UE`)
- L27 _namespace_ `namespace Private` (scope `UE::ContentBrowser`)

### `Source/Editor/ContentBrowser/Private/ContentBrowserUtils.h` (Private)


#### enum `ContentBrowserUtils::EDisplayMessageType`  
`enum class EDisplayMessageType`  
_L45-51_
- desc: Display Message type, mainly used to decide the icon to use
- L47 _public enumerator_ `Successful`
- L48 _public enumerator_ `Info`
- L49 _public enumerator_ `Warning`
- L50 _public enumerator_ `Error`

#### Free symbols / members of external scopes

- L39 _namespace_ `namespace ContentBrowserUtils`
- L54 _prototype_ `void DisplayMessage(const FText& Message, const FSlateRect& ScreenAnchor, const TSharedRef<SWidget>& ParentContent, EDisplayMessageType InMessageType);` (scope `ContentBrowserUtils`) — Displays a modeless message at the specified anchor. It is fine to specify a zero-size anchor, just use the top and left fields
- L57 _prototype_ `void DisplayConfirmationPopup(const FText& Message, const FText& YesString, const FText& NoString, const TSharedRef<SWidget>& ParentContent, const FOnClicked& OnYesClicked, const FOnClicked& OnNoClicked = FOnClicked());` (scope `ContentBrowserUtils`) — Displays a modeless message asking yes or no type question
- L60 _prototype_ `bool DisplayConfirmationDialog(const FText& InTitle, const FText& InMessage);` (scope `ContentBrowserUtils`) — Displays a modal dialog asking yes or no question (blocking)
- L63 _prototype_ `FString GetItemReferencesText(const TArray<FContentBrowserItem>& Items);` (scope `ContentBrowserUtils`) — Returns references to the specified items
- L66 _prototype_ `FString GetItemObjectPathText(const TArray<FContentBrowserItem>& Items);` (scope `ContentBrowserUtils`) — Returns object path of the specified items
- L69 _prototype_ `FString GetItemPackageNameText(const TArray<FContentBrowserItem>& Items);` (scope `ContentBrowserUtils`) — Returns package name of the specified items
- L72 _prototype_ `FString GetFolderReferencesText(const TArray<FContentBrowserItem>& Folders);` (scope `ContentBrowserUtils`) — Returns references to the specified folders
- L75 _prototype_ `void CopyItemReferencesToClipboard(const TArray<FContentBrowserItem>& ItemsToCopy);` (scope `ContentBrowserUtils`) — Copies references to the specified items to the clipboard
- L78 _prototype_ `void CopyItemObjectPathToClipboard(const TArray<FContentBrowserItem>& ItemsToCopy);` (scope `ContentBrowserUtils`) — Copies object path of the specified items to the clipboard
- L81 _prototype_ `void CopyItemPackageNameToClipboard(const TArray<FContentBrowserItem>& ItemsToCopy);` (scope `ContentBrowserUtils`) — Copies package name of the specified items to the clipboard
- L84 _prototype_ `void CopyFolderReferencesToClipboard(const TArray<FContentBrowserItem>& FoldersToCopy);` (scope `ContentBrowserUtils`) — Copies references to the specified folders to the clipboard
- L87 _prototype_ `void CopyFilePathsToClipboard(const TArray<FContentBrowserItem>& ItemsToCopy);` (scope `ContentBrowserUtils`) — Copies file paths on disk to the specified items to the clipboard
- L90 _prototype_ `bool IsItemDeveloperContent(const FContentBrowserItem& InItem);` (scope `ContentBrowserUtils`) — Check whether the given item is considered to be developer content
- L93 _prototype_ `bool IsItemLocalizedContent(const FContentBrowserItem& InItem);` (scope `ContentBrowserUtils`) — Check whether the given item is considered to be localized content
- L96 _prototype_ `bool IsItemEngineContent(const FContentBrowserItem& InItem);` (scope `ContentBrowserUtils`) — Check whether the given item is considered to be engine content (including engine plugins)
- L99 _prototype_ `bool IsItemProjectContent(const FContentBrowserItem& InItem);` (scope `ContentBrowserUtils`) — Check whether the given item is considered to be project content (including project plugins)
- L102 _prototype_ `bool IsItemPluginContent(const FContentBrowserItem& InItem);` (scope `ContentBrowserUtils`) — Check whether the given item is considered to be plugin content (engine or project)
- L105 _prototype_ `bool IsItemPluginRootFolder(const FContentBrowserItem& InItem);` (scope `ContentBrowserUtils`) — Check whether the given item is the root folder of a plugin
- L108 _prototype_ `bool TryGetFolderBrushAndShadowName(const FContentBrowserItem& InFolder, FName& OutBrushName, FName& OutShadowBrushName);` (scope `ContentBrowserUtils`) — Given a Folder, work out the BrushName and ShadowBrushName to use for it
- L111 _prototype_ `bool TryGetFolderBrushAndShadowNameSmall(const FContentBrowserItem& InFolder, FName& OutBrushName, FName& OutShadowBrushName);` (scope `ContentBrowserUtils`) — Given a Folder, work out the small version of the BrushName and ShadowBrushName to use for it
- L114 _prototype_ `bool IsCollectionPath(const FString& InPath, TSharedPtr<ICollectionContainer>* OutCollectionContainer = nullptr, FName* OutCollectionName = nullptr, ECollectionShareType::Type* OutCollectionShareType = nullptr);` (scope `ContentBrowserUtils`) — Check to see whether the given path is rooted against a collection directory, optionally extracting the collection container, name and share type from the path
- L117 _prototype_ `void CountPathTypes(const TArray<FString>& InPaths, int32& OutNumAssetPaths, int32& OutNumClassPaths);` (scope `ContentBrowserUtils`) — Given an array of paths, work out how many are rooted against class roots, and how many are rooted against asset roots
- L120 _prototype_ `void CountPathTypes(const TArray<FName>& InPaths, int32& OutNumAssetPaths, int32& OutNumClassPaths);` (scope `ContentBrowserUtils`) — Given an array of paths, work out how many are rooted against class roots, and how many are rooted against asset roots
- L123 _prototype_ `void CountItemTypes(const TArray<FAssetData>& InItems, int32& OutNumAssetItems, int32& OutNumClassItems);` (scope `ContentBrowserUtils`) — Given an array of "asset" data, work out how many are assets, and how many are classes
- L126 _prototype_ `FText GetExploreFolderText();` (scope `ContentBrowserUtils`) — Gets the platform specific text for the "explore" command (FPlatformProcess::ExploreFolder)
- L129 _prototype_ `void ExploreFolders(const TArray<FContentBrowserItem>& InItems, const TSharedRef<SWidget>& InParentContent);` (scope `ContentBrowserUtils`) — Perform a batched "explore" operation on the specified file and/or folder paths
- L132 _prototype_ `bool CanExploreFolders(const TArray<FContentBrowserItem>& InItems);` (scope `ContentBrowserUtils`) — Returns if can perform a batched "explore" operation on the specified file and/or folder paths
- L135 _prototype_ `TArray<FContentBrowserItem> ConvertLegacySelectionToItems(TArrayView<const FAssetData> InAssets, TArrayView<const FString> InFolders);` (scope `ContentBrowserUtils`) — Convert a legacy asset and path selection to their corresponding content browser data items
- L138 _prototype_ `void AppendAssetFilterToContentBrowserFilter(const FARFilter& InAssetFilter, const TSharedPtr<FPathPermissionList>& InAssetClassPermissionList, const TSharedPtr<FPathPermissionList>& InFolderPermissionList, FContentBrowserDataFilter& OutDataFilter);` (scope `ContentBrowserUtils`) — Append the asset registry filter and permission lists to the content browser data filter
- L141 _prototype_ `TSharedPtr<FPathPermissionList> GetCombinedFolderPermissionList(const TSharedPtr<FPathPermissionList>& FolderPermissionList, const TSharedPtr<FPathPermissionList>& WritableFolderPermissionList);` (scope `ContentBrowserUtils`) — Combine folder filters into a new filter if either are active
- L144 _prototype_ `bool CanDeleteFromAssetView(TWeakPtr<SAssetView> AssetView, FText* OutErrorMsg = nullptr);` (scope `ContentBrowserUtils`) — Shared logic to know if we can perform certain operation depending on which view it occurred, either PathView or AssetView
- L145 _prototype_ `bool CanRenameFromAssetView(TWeakPtr<SAssetView> AssetView, FText* OutErrorMsg = nullptr);` (scope `ContentBrowserUtils`)
- L146 _prototype_ `bool CanDeleteFromPathView(TWeakPtr<SPathView> PathView, FText* OutErrorMsg = nullptr);` (scope `ContentBrowserUtils`)
- L147 _prototype_ `bool CanRenameFromPathView(TWeakPtr<SPathView> PathView, FText* OutErrorMsg = nullptr);` (scope `ContentBrowserUtils`)
- L150 _prototype_ `FName GetInvariantPath(const FContentBrowserItemPath& ItemPath);` (scope `ContentBrowserUtils`) — Returns internal path if it has one, otherwise strips /All prefix from virtual path
- L153 _prototype_ `EContentBrowserIsFolderVisibleFlags GetIsFolderVisibleFlags(const bool bDisplayEmpty);` (scope `ContentBrowserUtils`) — Get the set of flags to use with IsFolderVisible
- L157 _prototype_ `bool IsFavoriteFolder(const FString& FolderPath);` (scope `ContentBrowserUtils`) — `UE_DEPRECATED(5.3, "Use function that takes FContentBrowserItemPath instead.")` — Returns if this folder has been marked as a favorite folder
- L158 _prototype_ `bool IsFavoriteFolder(const FContentBrowserItemPath& FolderPath);` (scope `ContentBrowserUtils`)
- L161 _prototype_ `void AddFavoriteFolder(const FString& FolderPath, bool bFlushConfig = true);` (scope `ContentBrowserUtils`) — `UE_DEPRECATED(5.3, "Use function that takes FContentBrowserItemPath instead.")`
- L162 _prototype_ `void AddFavoriteFolder(const FContentBrowserItemPath& FolderPath);` (scope `ContentBrowserUtils`)
- L165 _prototype_ `void InsertFavoriteFolder(const FContentBrowserItemPath& InFolderPath, const FContentBrowserItemPath& InFolderContext, EItemDropZone InPositionContext);` (scope `ContentBrowserUtils`) — Adds a new favorite folder at a specific position
- L168 _prototype_ `void MoveFavoriteFolder(const FContentBrowserItemPath& InFolderPath, const FContentBrowserItemPath& InFolderContext, EItemDropZone InPositionContext);` (scope `ContentBrowserUtils`) — Moves an existing favorite folder at a new position
- L171 _prototype_ `FContentBrowserFavoriteItem* FindFavoriteFolder(const FContentBrowserItemPath& InFolderPath);` (scope `ContentBrowserUtils`) — Finds existing favorite item based on path
- L174 _prototype_ `void RemoveFavoriteFolder(const FString& FolderPath, bool bFlushConfig = true);` (scope `ContentBrowserUtils`) — `UE_DEPRECATED(5.3, "Use function that takes FContentBrowserItemPath instead.")`
- L175 _prototype_ `void RemoveFavoriteFolder(const FContentBrowserItemPath& FolderPath);` (scope `ContentBrowserUtils`)
- L177 _prototype_ `TArray<FString> GetFavoriteFolders();` (scope `ContentBrowserUtils`)
- L180 _prototype_ `void AddShowPrivateContentFolder(const FStringView VirtualFolderPath, const FName Owner);` (scope `ContentBrowserUtils`) — Adds FolderPath as a private content edit folder if it's allowed to be toggled as such
- L183 _prototype_ `void RemoveShowPrivateContentFolder(const FStringView VirtualFolderPath, const FName Owner);` (scope `ContentBrowserUtils`) — Removes FolderPath as a private content edit folder if it's allowed to be toggled as such
- L186 _prototype_ `bool ShouldShowCustomVirtualFolderIcon();` (scope `ContentBrowserUtils`) — Returns whether we should display icons for custom virtual folders in the content browser
- L189 _prototype_ `bool ShouldShowPluginFolderIcon();` (scope `ContentBrowserUtils`) — Returns whether we should display icons for plugins in the content browser
- L192 _prototype_ `bool ShouldShowRedirectors(TSharedPtr<SFilterList> Filters);` (scope `ContentBrowserUtils`) — Returns whether the content browser should be showing redirectors based on the current filter state or content browser settings
- L198 _prototype_ `FContentBrowserInstanceConfig* GetContentBrowserConfig(FName InstanceName);` (scope `ContentBrowserUtils`) — Returns config settings for the given content browser name. A name of none returns null.
- L204 _prototype_ `FPathViewConfig* GetPathViewConfig(FName InstanceName);` (scope `ContentBrowserUtils`) — returns config settings for the path view for the given content browser name. A name of none returns null.
- L210 _prototype_ `EContentBrowserItemAttributeFilter GetContentBrowserItemAttributeFilter(FName InstanceName);` (scope `ContentBrowserUtils`) — Returns the attribute filter to use when retrieving conent browser data for the given instance. An instance name of None gives global settings.
- L222 _prototype_ `FContentBrowserItem TryGetItemFromUserProvidedPath(FStringView RequestedPathView);` (scope `ContentBrowserUtils`) — Try and find a valid content browser item from a path provided from user text input. Examples of paths: - A full virtual folder or item path such as /All/Game/Maps /All/Game/Maps/Arena.Arena - An internal asset path such as /Game/Maps/Arena.Arena - An internal package name such as /Game/Maps/Arena - An internal package path such as /Game/Maps - An 'export text' path / asset reference such as /Script/Engine.World'/Game/Maps/Arena.Arena' - A filesystem path to a uasset or umap file.
- L225 _prototype_ `TArray<FString> GetChildPathsFromUserProvidedPath(FStringView RequestedPathView, EContentBrowserItemCategoryFilter ItemCategoryFilter, EContentBrowserItemAttributeFilter ItemAttributeFilter, const FName& ConfigInstanceName, const SPathView& PathViewForFiltering);` (scope `ContentBrowserUtils`) — Finds the child paths that are children of the supplied path, while obeying the supplied filters.
- L228 _prototype_ `FText GetUserFacingPathFromVirtualPath(FName VirtualPath);` (scope `ContentBrowserUtils`) — Gets the actual path the user should edit when they start editing a virtual path in the navigation bar
- L230 _prototype_ `FString FormatCollectionCrumbData(const ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection);` (scope `ContentBrowserUtils`)
- L233 _prototype_ `void UpdateNavigationBar(const TSharedPtr<SNavigationBar>& NavigationBar, const TSharedPtr<SAssetView>& AssetView, const TSharedPtr<SPathView>& PathView);` (scope `ContentBrowserUtils`) — Updates a navigation bar based on the current state of an asset view and path view
- L236 _prototype_ `TArray<FContentBrowserItem> FilterOrAliasItems(TArrayView<const FContentBrowserItem> Items, const SPathView& PathViewForFiltering);` (scope `ContentBrowserUtils`) — Filter a list of items based on permissions or find a valid alias.
- L239 _prototype_ `const FContentBrowserInstanceConfig* GetConstInstanceConfig(const FName& ForInstance);` (scope `ContentBrowserUtils`) — Retrieves a named config.
- L242 _prototype_ `TArray<FContentBrowserItem> GetChildItemsFromVirtualPath(const FName& Path, EContentBrowserItemCategoryFilter ItemCategoryFilter, EContentBrowserItemAttributeFilter ItemAttributeFilter, const FName& ConfigInstanceName, const SPathView& PathViewForFiltering);` (scope `ContentBrowserUtils`) — Finds the content items that are children of the supplied path, while obeying the supplied filters.
- L245 _prototype_ `TSharedPtr<SWidget> GetFolderWidgetForNavigationBar(const FText& InFolderName, const FName& InFolderBrushName, const FLinearColor& InFolderColor);` (scope `ContentBrowserUtils`) — Creates a widget that represents a folder with the given name, brush, and color.

### `Source/Editor/ContentBrowser/Private/ContentSources/Widgets/SContentSource.h` (Private)


#### class `UE::Editor::ContentBrowser::SContentSource`  
`class SContentSource : public SCompoundWidget`  
_L17-35_
- inherits: `SCompoundWidget`
- desc: Displays the widgets for a single content source that is currently active
- L20 _public function_ `SLATE_BEGIN_ARGS(SContentSource)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `void SetContentSource(const TSharedPtr<IContentSource>& ContentSource);`
- L28 _private prototype_ `TSharedRef<SWidget> CreateWidget();`
- L32 _private member_ `TSharedPtr<IContentSource> ContentSource;` — The currently active content source
- L33 _private member_ `DataStorage::ICoreProvider* DataStorage = nullptr;`
- L34 _private member_ `DataStorage::IUiProvider* DataStorageUi = nullptr;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)

### `Source/Editor/ContentBrowser/Private/ContentSources/Widgets/SContentSourcesView.h` (Private)


#### class `UContentSourcesViewMenuContext`  
`class UContentSourcesViewMenuContext : public UObject`  
_L21-27_
- reflection: `UCLASS()`
- inherits: `UObject`
- L26 _public member_ `TWeakPtr<UE::Editor::ContentBrowser::SContentSourcesView> ContentSourcesWidget;`

#### class `UE::Editor::ContentBrowser::SContentSourcesView`  
`class SContentSourcesView : public SCompoundWidget`  
_L37-96_
- inherits: `SCompoundWidget`
- desc: Widget that displays a vertical toolbar to swap between known content sources and a child widget that contains the contents of the currently active content source
- L40 _public function_ `SLATE_BEGIN_ARGS(SContentSourcesView)`
- L43 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SLegacyContentSource>, LegacyContentSource) SLATE_EVENT(FOnLegacyContentSourceEnabled, OnLegacyContentSourceEnabled) SLATE_EVENT(FOnLegacyContentSourceDisabled, OnLegacyContentSourceDisabled) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — A legacy content source can be used to displays the widgets of the old asset based content browser
- L51 _public prototype_ `void ForEachContentSource(const TFunctionRef<void(const TSharedRef<IContentSource>&)>& InFunctor);`
- L52 _public prototype_ `void ActivateContentSource(const TSharedRef<IContentSource>& InContentSource);`
- L53 _public prototype_ `bool IsContentSourceActive(const TSharedRef<IContentSource>& InContentSource) const;`
- L56 _public prototype_ `bool HasLegacyContentSource() const;` — Whether this widget currently supports showing the legacy content source
- L59 _public prototype_ `bool IsLegacyContentSourceActive() const;` — Whether the legacy content source is supported and currently active
- L60 _public prototype_ `void ActivateLegacyContentSource();`
- L63 _public prototype_ `void ChooseActiveContentSource();` — Pick the first valid content source that is found
- L66 _private prototype_ `TSharedRef<SWidget> CreateSourceBar();`
- L67 _private prototype_ `void OnContentSourcesChanged();`
- L68 _private prototype_ `void UpdateContentSourcesList();`
- L73 _private member_ `TArray<TSharedRef<IContentSource>> ContentSources;` — List of currently known content sources
- L76 _private member_ `TSharedPtr<IContentSource> ActiveContentSource;` — Currently active content source
- L79 _private member_ `TSharedPtr<SContentSource> ContentSourceWidget;` — Widget that displays the contents of the currently active content source
- L82 _private member_ `TSharedPtr<SBox> SourcesBarContainer;` — Container widget for the vertical toolbar to display all known content source
- L85 _private member_ `TSharedPtr<SLegacyContentSource> LegacyContentSource;` — The legacy content source
- L87 _private member_ `bool bIsLegacyContentSourceActive = false;`
- L88 _private member_ `FOnLegacyContentSourceEnabled OnLegacyContentSourceEnabledEvent;`
- L89 _private member_ `FOnLegacyContentSourceDisabled OnLegacyContentSourceDisabledEvent;`
- L92 _private member_ `TSharedPtr<SWidgetSwitcher> LegacyWidgetSwitcher;` — Widget switcher to display either the legacy content source or the currently active content source
- L95 _private member_ `static FDelayedAutoRegisterHelper SourceBarMenuRegistration;` — Registers the content source bar

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Editor` (scope `UE`)
- L30 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)
- L32 _delegate_ `DECLARE_DELEGATE(FOnLegacyContentSourceEnabled) DECLARE_DELEGATE(FOnLegacyContentSourceDisabled)`
- L33 _delegate_ `DECLARE_DELEGATE(FOnLegacyContentSourceDisabled)`

### `Source/Editor/ContentBrowser/Private/ContentSources/Widgets/SLegacyContentSource.h` (Private)


#### class `UE::Editor::ContentBrowser::SLegacyContentSource`  
`class SLegacyContentSource : public SCompoundWidget`  
_L14-24_
- inherits: `SCompoundWidget`
- desc: Widget to display the old asset based content browser Currently does not contain any logic and simply displays a pre-existing widget that is supplied by SContentBrowser
- L17 _public function_ `SLATE_BEGIN_ARGS(SLegacyContentSource)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L22 _public prototype_ `void SetContent(const TSharedRef<SWidget>& InWidget);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)

### `Source/Editor/ContentBrowser/Private/DragDropHandler.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace DragDropHandler`
- L20 _prototype_ `TSharedPtr<FDragDropOperation> CreateDragOperation(TArrayView<const FContentBrowserItem> InItems);` (scope `DragDropHandler`) — Called to provide drag and drop handling when starting a drag event. @return A drag operation, or null if no drag can be performed.
- L26 _prototype_ `bool HandleDragEnterItem(const FContentBrowserItem& InItem, const FDragDropEvent& InDragDropEvent);` (scope `DragDropHandler`) — Called to provide drag and drop handling when a drag event enters an item, such as performing validation and reporting error information. @return True if the drag event can be handled (even if it won't be because it's invalid), or false to allow something else to deal with it instead.
- L32 _prototype_ `bool HandleDragOverItem(const FContentBrowserItem& InItem, const FDragDropEvent& InDragDropEvent);` (scope `DragDropHandler`) — Called to provide drag and drop handling while a drag event is over an item, such as performing validation and reporting error information. @return True if the drag event can be handled (even if it won't be because it's invalid), or false to allow something else to deal with it instead.
- L38 _prototype_ `bool HandleDragLeaveItem(const FContentBrowserItem& InItem, const FDragDropEvent& InDragDropEvent);` (scope `DragDropHandler`) — Called to provide drag and drop handling when a drag event leaves an item, such as clearing any error information set during earlier validation. @return True if the drag event can be handled (even if it won't be because it's invalid), or false to allow something else to deal with it instead.
- L44 _prototype_ `bool HandleDragDropOnItem(const FContentBrowserItem& InItem, const FDragDropEvent& InDragDropEvent, const TSharedRef<SWidget>& InParentWidget);` (scope `DragDropHandler`) — Called to provide drag and drop handling when a drag event is dropped on an item. @return True if the drag event can be handled (even if it wasn't because it was invalid), or false to allow something else to deal with it instead.

### `Source/Editor/ContentBrowser/Private/Experimental/ContentBrowserSearchOverrideInternal.h` (Private)


#### class `UE::Editor::ContentBrowser::Extension::FInternalApiWrapper`  
`class FInternalApiWrapper`  
_L13-39_
- desc: Provides write access to the private state of ICBSearchOverrideInstance. Only ContentBrowser internals should hold a reference to this wrapper.
- L16 _public function_ `explicit FInternalApiWrapper(ICBSearchOverrideInstance& InInstance) : Instance(InInstance)`
- L20 _public prototype_ `void OnFilteringReset();`
- L21 _public prototype_ `void OnAllKnownItemsAvailable();`
- L24 _public member_ `FSimpleMulticastDelegate OnOverrideActiveChanged;` — Fires when the override is toggled on or off.
- L27 _public member_ `TDelegate<void(bool)> OnRequestSetUserSearching;` — Executed when the override calls SetUserSearching().
- L30 _public member_ `FSimpleDelegate OnRequestQuickFrontendListRefresh;` — Executed when the override calls RequestQuickFrontendListRefresh().
- L33 _public member_ `TArray<TSharedPtr<FAssetViewItem>> PublishedResults;` — Results set by PublishResults(); consumed by the asset view on the next tick.
- L35 _public member_ `bool bAllKnownItemsAvailableNotified = false;`
- L38 _private member_ `ICBSearchOverrideInstance& Instance;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Editor` (scope `UE`)
- L7 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)
- L7 _namespace_ `namespace Extension` (scope `UE::Editor::ContentBrowser`)

### `Source/Editor/ContentBrowser/Private/Filters.h` (Private)


#### class `FFilter_ShowRedirectors`  
`class FFilter_ShowRedirectors : public FFrontendFilter`  
_L21-59_
- inherits: `FFrontendFilter`
- desc: A custom filter that appears in the filter bar but actually controls a content browser setting controlling visibility of redirectors for use in backend filtering.
- L26 _public prototype_ `FFilter_ShowRedirectors (TSharedPtr<FFrontendFilterCategory> InCategory);` — TODO: Consider not giving this the entire viewmodel to sync with filter state could make viewmode own/create this, or send a smaller interface ptr into the constructor?
- L29 _public function_ `virtual FString GetName() const override` — Returns the system name for this filter
- L32 _public prototype_ `virtual FText GetDisplayName() const override;` — Returns the human readable name for this filter
- L35 _public prototype_ `virtual FText GetToolTipText() const override;` — Returns the tooltip for this filter, shown in the filters menu
- L38 _public prototype_ `virtual FName GetIconName() const override;` — Returns the name of the icon to use in menu entries
- L42 _public function_ `virtual bool IsInverseFilter() const` — If true, the filter will be active in the FilterBar when it is inactive in the UI (i.e the filter pill is grayed out)
- L49 _public prototype_ `virtual void ActiveStateChanged(bool bActive) override;` — Notification that the filter became active or inactive
- L52 _public prototype_ `virtual void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const override;` — Can be overriden for custom FilterBar subclasses to save settings, currently not implemented in any gneeric Filter Bar
- L55 _public prototype_ `virtual void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) override;` — Can be overriden for custom FilterBar subclasses to load settings, currently not implemented in any gneeric Filter Bar
- L58 _public function_ `virtual bool PassesFilter(FAssetFilterType InItem) const override` — Pass all objects - filter is just used to set backend query state.

#### class `FFrontendFilter_GatherDynamicCollectionsExpressionContext`  
`class FFrontendFilter_GatherDynamicCollectionsExpressionContext : public ITextFilterExpressionContext`  
_L65-101_
- inherits: `ITextFilterExpressionContext`
- desc: Expression context which gathers up the names of any dynamic collections being referenced by the current query Private utility class for FAssetTextFilter and deprecated FFrontendFilter_Text
- L68 _public prototype_ `FFrontendFilter_GatherDynamicCollectionsExpressionContext(const TArray<TSharedPtr<ICollectionContainer>>& CollectionContainers, TArray<FCollectionRef>& OutReferencedDynamicCollections);`
- L69 _public prototype_ `~FFrontendFilter_GatherDynamicCollectionsExpressionContext();`
- L71 _public prototype_ `virtual bool TestBasicStringExpression(const FTextFilterString& InValue, const ETextFilterTextComparisonMode InTextComparisonMode) const override;`
- L72 _public prototype_ `virtual bool TestComplexExpression(const FName& InKey, const FTextFilterString& InValue, const ETextFilterComparisonOperation InComparisonOperation, const ETextFilterTextComparisonMode InTextComparisonMode) const override;`
- L75 _private prototype_ `bool TestAgainstAvailableCollections(const FTextFilterString& InValue, const ETextFilterTextComparisonMode InTextComparisonMode) const;`
- L91 _private member_ `TArray<FCollectionRef> AvailableDynamicCollections;` — The currently available dynamic collections
- L94 _private member_ `TArray<FCollectionRef>& ReferencedDynamicCollections;` — This will be populated with any dynamic collections that are being referenced by the current query - these collections may not all match when tested against the actual asset data
- L97 _private member_ `mutable TArray<FDynamicCollectionRefAndDepth> FoundDynamicCollections;` — Dynamic collections that have currently be found as part of the query (or recursive sub-query)
- L100 _private member_ `mutable int32 CurrentRecursionDepth;` — Incremented when we test a sub-query, decremented once we're done

#### struct `FFrontendFilter_GatherDynamicCollectionsExpressionContext::FDynamicCollectionRefAndDepth`  
`struct FDynamicCollectionRefAndDepth`  
_L78-88_
- desc: Contains a collection ref along with its recursion depth in the dynamic query - used so we can test them depth first
- L80 _public function_ `FDynamicCollectionRefAndDepth(const FCollectionRef& InCollection, const int32 InRecursionDepth) : Collection(InCollection) , RecursionDepth(InRecursionDepth)`
- L86 _public member_ `FCollectionRef Collection;`
- L87 _public member_ `int32 RecursionDepth;`

#### class `FFilter_HideOtherDevelopers`  
`class FFilter_HideOtherDevelopers : public FFrontendFilter`  
_L104-154_
- inherits: `FFrontendFilter`
- desc: Non-frontend filter which modifies content browser backend query to exclude folders belonging to other developers
- L107 _public prototype_ `FFilter_HideOtherDevelopers(TSharedPtr<FFrontendFilterCategory> InCategory, FName FilterBarIdentifier);`
- L108 _public prototype_ `FFilter_HideOtherDevelopers& operator=(const FFilter_HideOtherDevelopers&) = delete;`
- L109 _public prototype_ `virtual ~FFilter_HideOtherDevelopers();`
- L112 _public prototype_ `TSharedRef<const FPathPermissionList> GetPathPermissionList();` — Get the list of folders to be denied when this filter is active (visually disabled, becuase it's an inverse filter)
- L116 _public function_ `virtual bool PassesFilter(FAssetFilterType InItem) const override` — Pass all objects - filter is just used to set backend query state.
- L119 _public function_ `virtual FString GetName() const override` — Returns the system name for this filter
- L122 _public prototype_ `virtual FText GetDisplayName() const override;` — Returns the human readable name for this filter
- L125 _public prototype_ `virtual FText GetToolTipText() const override;` — Returns the tooltip for this filter, shown in the filters menu
- L128 _public prototype_ `virtual FName GetIconName() const override;` — Returns the name of the icon to use in menu entries
- L131 _public prototype_ `virtual void ActiveStateChanged(bool bActive) override;` — Notification that the filter became active or inactive
- L134 _public function_ `virtual void ModifyContextMenu(FMenuBuilder& MenuBuilder) override` — Called when the right-click context menu is being built for this filter
- L137 _public prototype_ `virtual void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const override;` — Can be overriden for custom FilterBar subclasses to save settings, currently not implemented in any gneeric Filter Bar
- L140 _public prototype_ `virtual void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) override;` — Can be overriden for custom FilterBar subclasses to load settings, currently not implemented in any gneeric Filter Bar
- L143 _private prototype_ `void BuildFilter();`
- L146 _private prototype_ `void HandleItemDataUpdated(TArrayView<const FContentBrowserItemDataUpdate> InUpdatedItems);` — Handle new folders being added to rebuild the filter
- L147 _private prototype_ `void HandleItemDataRefreshed();`
- L149 _private member_ `FName FilterBarIdentifier;`
- L150 _private member_ `TSet<FName> OtherDeveloperFolders;`
- L151 _private member_ `TSharedRef<FPathPermissionList> PathPermissionList;`
- L152 _private member_ `FDelegateHandle ItemDataUpdatedHandle;`
- L153 _private member_ `FDelegateHandle ItemDataRefreshedHandle;`

### `Source/Editor/ContentBrowser/Private/NewAssetOrClassContextMenu.h` (Private)


#### class `FNewAssetOrClassContextMenu`  
`class FNewAssetOrClassContextMenu`  
_L12-32_
- L15 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnNewFolderRequested, const FString& );`
- L16 _public prototype_ `DECLARE_DELEGATE( FOnGetContentRequested ) static void MakeContextMenu( UToolMenu* Menu, const TArray<FName>& InSelectedPaths, const FOnNewFolderRequested& InOnNewFolderRequested, const FOnGetContentRequested& InOnGetContentRequested );`
- L28 _private prototype_ `static void ExecuteNewFolder(FName InPath, FOnNewFolderRequested InOnNewFolderRequested);` — Create a new folder at the specified path
- L31 _private prototype_ `static void ExecuteGetContent( FOnGetContentRequested InOnGetContentRequested );` — Handle when the "Get Content" button is clicked

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_OneParam( FOnNewFolderRequested, const FString& );`
- L16 _delegate_ `DECLARE_DELEGATE( FOnGetContentRequested ) static void MakeContextMenu( UToolMenu* Menu, const TArray<FName>& InSelectedPaths, const FOnNewFolderRequested& InOnNewFolderRequested, const FOnGetContentRequested& InOnGetContentRequested );`

### `Source/Editor/ContentBrowser/Private/PathContextMenu.h` (Private)


#### class `FPathContextMenu`  
`class FPathContextMenu : public TSharedFromThis<FPathContextMenu>`  
_L24-141_
- inherits: `TSharedFromThis<FPathContextMenu>`
- L28 _public prototype_ `FPathContextMenu(const TWeakPtr<SWidget>& InParentContent);` — Constructor
- L31 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnRenameFolderRequested, const FContentBrowserItem& , EContentBrowserViewContext );` — Delegate for when the context menu requests a rename of a folder
- L32 _public prototype_ `void SetOnRenameFolderRequested(const FOnRenameFolderRequested& InOnRenameFolderRequested);`
- L35 _public prototype_ `DECLARE_DELEGATE(FOnFolderDeleted) void SetOnFolderDeleted(const FOnFolderDeleted& InOnFolderDeleted);` — Delegate for when the context menu has successfully deleted a folder
- L39 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnFolderFavoriteToggled, const TArray<FString>& ) void SetOnFolderFavoriteToggled(const FOnFolderFavoriteToggled& InOnFolderFavoriteToggled);` — Delegate for when the context menu has successfully toggled the favorite status of a folder
- L43 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnFolderFavoriteEdited, const FContentBrowserItemPath& ) void SetOnFolderFavoriteEdited(const FOnFolderFavoriteEdited& InOnFolderFavoriteEdited);` — Delegate for when the context menu has successfully edited a favorite folder
- L47 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnPrivateContentEditToggled, const TArray<FString>& ) void SetOnPrivateContentEditToggled(const FOnPrivateContentEditToggled& InOnPrivateContentEditableToggled);` — Delegate for when the context menu has succesfully toggled the private content edit mode of a folder
- L51 _public prototype_ `const TArray<FContentBrowserItem>& GetSelectedFolders() const;` — Gets the currently selected folders
- L54 _public prototype_ `void SetSelectedFolders(const TArray<FContentBrowserItem>& InSelectedFolders);` — Sets the currently selected folders
- L57 _public prototype_ `TSharedRef<FExtender> MakePathViewContextMenuExtender(const TArray<FString>& InSelectedPaths);` — Makes the asset tree context menu extender
- L60 _public prototype_ `void MakePathViewContextMenu(UToolMenu* Menu);` — Makes the asset tree context menu widget
- L63 _public prototype_ `void MakeNewAssetSubMenu(UToolMenu* Menu);` — Makes the new asset submenu
- L66 _public prototype_ `void MakeSetColorSubMenu(UToolMenu* Menu);` — Makes the set color submenu
- L69 _public prototype_ `void ExecuteExplore();` — Handler for when "Explore" is selected
- L72 _public prototype_ `bool CanExecuteRename() const;` — Handler to check to see if a rename command is allowed
- L75 _public prototype_ `void ExecuteRename(EContentBrowserViewContext ViewContext);` — Handler for Rename
- L78 _public prototype_ `bool CanExecuteDelete() const;` — Handler to check to see if a delete command is allowed
- L81 _public prototype_ `void ExecuteDelete();` — Handler for Delete
- L84 _public prototype_ `void ExecuteResetColor();` — Handler for when reset color is selected
- L87 _public prototype_ `void ExecutePickColor();` — Handler for when new or set color is selected
- L90 _public prototype_ `void ExecuteFavorite();` — Handler for favoriting
- L93 _public prototype_ `void ExecuteEditFavorite();` — Handler for favorite editing
- L96 _public prototype_ `void ExecutePrivateContentEdit();` — Handler for enabling private content editing
- L99 _public prototype_ `void ExecuteSaveFolder();` — Handler for when "Save" is selected
- L102 _public prototype_ `void ExecuteResaveFolder();` — Handler for when "Resave" is selected
- L105 _public prototype_ `void CopySelectedFolder();` — Handler for when "Copy AssetPath" is selected
- L108 _public prototype_ `FReply ExecuteDeleteFolderConfirmed();` — Handler for when "Delete" is selected and the delete was confirmed
- L111 _public function_ `TSharedPtr<SWidget> GetParentContent() const` — Get the parent widget for which this menu was summoned.
- L115 _private prototype_ `FText GetDeleteToolTip() const;` — Get tooltip for delete
- L117 _private prototype_ `void SaveFilesWithinSelectedFolders(EContentBrowserItemSaveFlags InSaveFlags);`
- L119 _private prototype_ `void CopySelectedFoldersToClipoard();`
- L122 _private prototype_ `bool SelectedHasCustomColors() const;` — Checks to see if any of the selected paths use custom colors
- L125 _private prototype_ `void OnLinearColorValueChanged(const FLinearColor InColor);` — Callback when the color picker dialog changed the color.
- L128 _private prototype_ `FReply OnColorClicked( const FLinearColor InColor );` — Callback when the color is picked from the set color submenu
- L131 _private prototype_ `void ResetColors();` — Resets the colors of the selected paths
- L134 _private member_ `TArray<FContentBrowserItem> SelectedFolders;`
- L135 _private member_ `TWeakPtr<SWidget> ParentContent;`
- L136 _private member_ `FOnRenameFolderRequested OnRenameFolderRequested;`
- L137 _private member_ `FOnFolderDeleted OnFolderDeleted;`
- L138 _private member_ `FOnFolderFavoriteToggled OnFolderFavoriteToggled;`
- L139 _private member_ `FOnFolderFavoriteEdited OnFolderFavoriteEdited;`
- L140 _private member_ `FOnPrivateContentEditToggled OnPrivateContentEditToggled;`

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRenameFolderRequested, const FContentBrowserItem& , EContentBrowserViewContext );` — Delegate for when the context menu requests a rename of a folder
- L35 _delegate_ `DECLARE_DELEGATE(FOnFolderDeleted) void SetOnFolderDeleted(const FOnFolderDeleted& InOnFolderDeleted);` — Delegate for when the context menu has successfully deleted a folder
- L39 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFolderFavoriteToggled, const TArray<FString>& ) void SetOnFolderFavoriteToggled(const FOnFolderFavoriteToggled& InOnFolderFavoriteToggled);` — Delegate for when the context menu has successfully toggled the favorite status of a folder
- L43 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFolderFavoriteEdited, const FContentBrowserItemPath& ) void SetOnFolderFavoriteEdited(const FOnFolderFavoriteEdited& InOnFolderFavoriteEdited);` — Delegate for when the context menu has successfully edited a favorite folder
- L47 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPrivateContentEditToggled, const TArray<FString>& ) void SetOnPrivateContentEditToggled(const FOnPrivateContentEditToggled& InOnPrivateContentEditableToggled);` — Delegate for when the context menu has succesfully toggled the private content edit mode of a folder

### `Source/Editor/ContentBrowser/Private/PathViewTypes.h` (Private)


#### class `FTreeItem`  
`class FTreeItem : public TSharedFromThis<FTreeItem>`  
_L23-127_
- inherits: `TSharedFromThis<FTreeItem>`
- desc: A folder item shown in the asset tree
- L26 _public prototype_ `FTreeItem() = default;`
- L28 _public prototype_ `explicit FTreeItem(FContentBrowserItem&& InItem);`
- L29 _public prototype_ `explicit FTreeItem(const FContentBrowserItem& InItem);`
- L31 _public prototype_ `explicit FTreeItem(FContentBrowserItemData&& InItemData);`
- L32 _public prototype_ `explicit FTreeItem(const FContentBrowserItemData& InItemData);`
- L35 _public prototype_ `void SetItemData(FContentBrowserItem InItem);` — Replace the current item data or pending item data with the given item data
- L37 _public prototype_ `void AppendItemData(const FContentBrowserItem& InItem);`
- L38 _public prototype_ `void AppendItemData(const FContentBrowserItemData& InItemData);`
- L39 _public prototype_ `void RemoveItemData(const FContentBrowserItem& InItem);`
- L40 _public prototype_ `void RemoveItemData(const FContentBrowserItemData& InItemData);`
- L41 _public prototype_ `FContentBrowserItemData RemoveItemData(const FContentBrowserMinimalItemData& InItemKey);`
- L44 _public prototype_ `const FContentBrowserItem& GetItem() const;` — Get the underlying Content Browser item
- L47 _public prototype_ `FSimpleMulticastDelegate& OnRenameRequested();` — Get the event fired whenever a rename is requested
- L50 _public prototype_ `void SetVisible(bool bInIsVisible);` — Set whether the item passes current filtering and should be displayed
- L53 _public prototype_ `void SetHasVisibleDescendants(bool bValue);` — Set whether this item has any descendants which explicitly passed filtering
- L56 _public prototype_ `bool GetHasVisibleDescendants() const;` — Return whether this item has any descendants which explicitly passed filtering
- L59 _public prototype_ `bool IsVisible() const;` — Returns whether the item passes current filtering and should be displayed, or whether any of its descendants did
- L62 _public prototype_ `bool IsNamingFolder() const;` — True if this folder is in the process of being named
- L65 _public prototype_ `void SetNamingFolder(const bool InNamingFolder);` — Set whether this folder is in the process of being named
- L68 _public prototype_ `bool IsChildOf(const FTreeItem& InParent);` — Returns true if this item is a child of the specified item
- L71 _public prototype_ `void AddChild(const TSharedRef<FTreeItem>& InChild);` — Add a child item and link its Parent backreference.
- L74 _public prototype_ `void RemoveChild(const TSharedRef<FTreeItem>& InChild);` — Remove a child item and unlink its Parent backreference.
- L77 _public prototype_ `void RemoveAllChildren();` — Remove all children when recycling this item. They may be re-added later.
- L80 _public prototype_ `TConstArrayView<TSharedPtr<FTreeItem>> GetChildren() const;` — Get a view of all the direct children of this node
- L83 _public prototype_ `TSharedPtr<FTreeItem> GetChild(const FName InChildFolderName) const;` — Returns the child item by name or NULL if the child does not exist
- L86 _public prototype_ `TSharedPtr<FTreeItem> GetParent() const;` — Returns the parent item if any
- L89 _public prototype_ `TSharedPtr<FTreeItem> FindItemRecursive(const FName InFullPath);` — Finds the child who's path matches the one specified
- L92 _public prototype_ `void ForAllChildrenRecursive(TFunctionRef<void(const TSharedRef<FTreeItem>&)> Functor);` — Execute the given functor on all children of this item recursively
- L95 _public prototype_ `void RequestSortChildren();` — Request that the children be sorted the next time someone calls SortChildrenIfNeeded
- L98 _public prototype_ `void GetSortedVisibleChildren(TArray<TSharedPtr<FTreeItem>>& OutChildren);` — Sort the children if necessary and populate the output parameter with a copy
- L101 _public prototype_ `bool IsDisplayOnlyFolder() const;` — Represents a folder that does not correspond to a mounted location
- L105 _private member_ `TArray<TSharedPtr<FTreeItem>> AllChildren;` — The children of this tree item
- L108 _private member_ `TWeakPtr<FTreeItem> Parent;` — The parent folder for this item
- L111 _private member_ `FContentBrowserItem Item;` — Underlying Content Browser item data
- L114 _private member_ `FSimpleMulticastDelegate RenameRequestedEvent;` — Broadcasts whenever a rename is requested
- L117 _private member_ `bool bNamingFolder = false;` — If true, this folder is in the process of being named
- L120 _private member_ `bool bChildrenRequireSort = false;` — If true, the children of this item need sorting
- L123 _private member_ `bool bIsVisible = true;` — Whether this node has passed the current set of filters in use
- L126 _private member_ `bool bHasVisibleDescendants = true;` — Whether this node has any descendants that are visible, so this node needs to be shown too

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_TwoParams(FSortTreeItemChildrenDelegate, const FTreeItem* , TArray<TSharedPtr<FTreeItem>>& );` — Sorts array of tree items
- L15 _prototype_ `DECLARE_DELEGATE_TwoParams(FSortTreeItemChildrenDelegate, const FTreeItem* , TArray<TSharedPtr<FTreeItem>>& );` — Sorts array of tree items
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace PathView` (scope `UE`)
- L19 _prototype_ `void DefaultSort(TArray<TSharedPtr<FTreeItem>>& InChildren);` (scope `UE::PathView`)

### `Source/Editor/ContentBrowser/Private/SAssetDialog.h` (Private)


#### enum `EAssetDialogCommandContext`  
`enum class EAssetDialogCommandContext`  
_L37-41_
- L39 _public enumerator_ `AssetView`
- L40 _public enumerator_ `PathView`

#### class `SAssetDialog`  
`class SAssetDialog : public SCompoundWidget`  
_L43-281_
- inherits: `SCompoundWidget`
- L46 _public function_ `SLATE_BEGIN_ARGS(SAssetDialog)`
- L50 _public prototype_ `SAssetDialog();`
- L51 _public prototype_ `virtual ~SAssetDialog();`
- L53 _public prototype_ `virtual void Construct(const FArguments& InArgs, const FSharedAssetDialogConfig& InConfig);`
- L55 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L56 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L57 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L60 _public prototype_ `void SetOnAssetsChosenForOpen(const FOnAssetsChosenForOpen& InOnAssetsChosenForOpen);` — Sets the delegate handler for when an open operation is committed
- L63 _public prototype_ `void SetOnObjectPathChosenForSave(const FOnObjectPathChosenForSave& InOnObjectPathChosenForSave);` — Sets the delegate handler for when a save operation is committed
- L66 _public prototype_ `void SetOnAssetDialogCancelled(const FOnAssetDialogCancelled& InOnAssetDialogCancelled);` — Sets the delegate handler for when the dialog is closed or cancelled
- L69 _public prototype_ `void SelectDefaultPaths();` — Reset selected paths to default choices
- L74 _private prototype_ `EActiveTimerReturnType SetFocusPostConstruct( double InCurrentTime, float InDeltaTime );` — Used to focus the name box immediately following construction
- L77 _private prototype_ `void FocusNameBox();` — Moves keyboard focus to the name box if this is a save dialog
- L81 _private prototype_ `bool IsBackEnabled() const;` — --- History Callbacks ---
- L82 _private prototype_ `bool IsForwardEnabled() const;`
- L84 _private prototype_ `FText GetBackTooltip() const;`
- L85 _private prototype_ `FText GetForwardTooltip() const;`
- L87 _private prototype_ `FReply OnBackClicked();`
- L88 _private prototype_ `FReply OnForwardClicked();`
- L91 _private prototype_ `void OnApplyHistoryData(const FHistoryData& History);` — Handles when the history manager shifts to a different history state.
- L93 _private prototype_ `void OnUpdateHistoryData(FHistoryData& History) const;` — Fills in the history item with the current state.
- L97 _private prototype_ `FText GetAssetNameText() const;` — Gets the name to display in the asset name box
- L100 _private prototype_ `FText GetPathNameText() const;` — Gets the name to display in the path text block
- L103 _private prototype_ `void OnAssetNameTextCommited(const FText& InText, ETextCommit::Type InCommitType);` — Fired when the asset name box text is commited
- L106 _private prototype_ `EVisibility GetNameErrorLabelVisibility() const;` — Gets the visibility of the name error label
- L109 _private prototype_ `FText GetNameErrorLabelText() const;` — Gets the text to display in the name error label
- L114 _private prototype_ `FText OnGetEditPathAsText(const FString& Path) const;` — Returns how the currently shown location should be presented to the user as text when beginning to edit the path
- L117 _private prototype_ `void OnPathTextEdited(const FString& NewPath);` — Respond to edited text from the navigation bar
- L120 _private prototype_ `TArray<FNavigationBarComboOption> OnCompletePathPrefix(const FString& Prefix) const;` — Provides autocomplete for text-based path editing in the navigation bar
- L123 _private prototype_ `TSharedRef<SWidget> OnGetCrumbDelimiterContent(const FString& CrumbData) const;` — Provide content for the navigation bar's breadcrumb menues.
- L124 _private prototype_ `void OnCrumbDelimiterItemClicked(FString ClickedPath);`
- L127 _private prototype_ `TArray<FNavigationBarComboOption> GetRecentPaths() const;` — Get a list of recently visited paths for the navigation bar.
- L132 _private prototype_ `void SetCurrentlySelectedPath(const FString& NewPath, const EContentBrowserPathType InPathType);` — Synchronizes all pickers & views to a new path state
- L135 _private prototype_ `void SyncToItems(TArrayView<const FContentBrowserItem> ItemsToSync, const bool bAllowImplicitSync = false);` — Changes sources to show the specified items and selects them
- L139 _private prototype_ `bool IsConfirmButtonEnabled() const;` — Determines if the confirm button (e.g. Open/Save) is enabled.
- L142 _private prototype_ `FReply OnConfirmClicked();` — Handler for when the confirm button (e.g. Open/Save) is clicked
- L145 _private prototype_ `FReply OnCancelClicked();` — Handler for when the cancel button is clicked
- L148 _private prototype_ `void OnAssetSelected(const FAssetData& AssetData);` — Handler for when an asset was selected in the asset picker
- L151 _private prototype_ `void OnAssetsActivated(const TArray<FAssetData>& SelectedAssets, EAssetTypeActivationMethod::Type ActivationType);` — Handler for when an asset was double clicked in the asset picker
- L155 _private prototype_ `TSharedPtr<SWidget> OnGetAssetContextMenu(const TArray<FAssetData>& SelectedAssets);` — Will generate the context menu if an asset or a folder is selected, either from the PathView or AssetView
- L156 _private prototype_ `TSharedPtr<SWidget> OnGetFolderContextMenu(const TArray<FString>& SelectedPaths, FContentBrowserMenuExtender_SelectedPaths InMenuExtender, FOnCreateNewFolder InOnCreateNewFolder, EAssetDialogCommandContext CommandContext);`
- L159 _private prototype_ `bool CanExecuteRename(EAssetDialogCommandContext CommandContext) const;` — Handler to check to see if a rename command is allowed
- L162 _private prototype_ `void ExecuteRename(EAssetDialogCommandContext CommandContext);` — Handler for Rename
- L165 _private prototype_ `bool CanExecuteDelete(EAssetDialogCommandContext CommandContext) const;` — Handler to check to see if a delete command is allowed
- L168 _private prototype_ `void ExecuteDelete(EAssetDialogCommandContext CommandContext);` — Handler for Delete
- L169 _private prototype_ `FReply ExecuteDeleteFolderConfirmed(const TArray<FString> SelectedFolderInternalPaths, const bool bResetSelection);`
- L171 _private prototype_ `FContentBrowserItem GetCreateNewFolderParent(EAssetDialogCommandContext CommandContext) const;`
- L174 _private prototype_ `bool CanExecuteCreateNewFolder(EAssetDialogCommandContext CommandContext) const;` — Handler to check to see if a create new folder command is allowed
- L177 _private prototype_ `void ExecuteCreateNewFolder(EAssetDialogCommandContext CommandContext);` — Handler for creating new folder
- L180 _private prototype_ `void ExecuteExplore(EAssetDialogCommandContext Widget);` — Handler for show in explorer
- L181 _private prototype_ `bool CanExecuteExplore(EAssetDialogCommandContext Widget);`
- L184 _private prototype_ `void SetupContextMenuContent(EAssetDialogCommandContext CommandContext, FMenuBuilder& MenuBuilder);` — Setup function for the context menu creation of folder and assets
- L186 _private prototype_ `void BindCommands();`
- L189 _private prototype_ `void CloseDialog();` — Closes this dialog
- L191 _private prototype_ `void SetCurrentlyEnteredAssetName(const FString& NewName);`
- L193 _private prototype_ `FName GetCurrentSelectedVirtualPath() const;`
- L195 _private prototype_ `void UpdateInputValidity();`
- L198 _private prototype_ `void ChooseAssetsForOpen(const TArray<FAssetData>& SelectedAssets);` — Used to commit the assets that were selected for open in this dialog
- L200 _private prototype_ `FString GetObjectPathForSave() const;`
- L203 _private prototype_ `void CommitObjectPathForSave();` — Used to commit the object path used for saving in this dialog
- L208 _private member_ `EAssetDialogType::Type DialogType;` — Whether this is an open or save dialog
- L211 _private member_ `FHistoryManager HistoryManager;` — Tracks the history data for the dialog
- L214 _private member_ `TMRUArray<FString> RecentDirectories;` — The most recently visited directories
- L217 _private member_ `FSetPathPickerPathsDelegate SetPathsDelegate;` — Used to update the path view after it has been created
- L220 _private member_ `FSetARFilterDelegate SetFilterDelegate;` — Used to update the asset view after it has been created
- L223 _private member_ `FGetCurrentSelectionDelegate GetCurrentSelectionDelegate;` — Used to get the currently selected assets
- L226 _private member_ `TArray<FTopLevelAssetPath> AssetClassNames;` — Only assets of these classes will show up
- L229 _private member_ `FOnAssetsChosenForOpen OnAssetsChosenForOpen;` — Fired when assets are chosen for open. Only fired in open dialogs.
- L232 _private member_ `FOnObjectPathChosenForSave OnObjectPathChosenForSave;` — Fired when an object path was chosen for save. Only fired in save dialogs.
- L235 _private member_ `FOnAssetDialogCancelled OnAssetDialogCancelled;` — Fired when the asset dialog is cancelled or closed
- L238 _private member_ `TSharedPtr<SEditableTextBox> NameEditableText;` — The name box. Only used in save dialogs.
- L241 _private member_ `TSharedPtr<STextBlock> PathText;` — The path box.
- L244 _private member_ `FString CurrentlySelectedPath;` — The object path of the asset to save. Only used in save dialogs.
- L246 _private member_ `EContentBrowserPathType CurrentlySelectedPathType = EContentBrowserPathType::None;`
- L249 _private member_ `FString CurrentlyEnteredAssetName;` — The object name of the asset to save. Only used in save dialogs.
- L252 _private member_ `ESaveAssetDialogExistingAssetPolicy::Type ExistingAssetPolicy;` — The behavior when the user chooses an existing asset. Only used in save dialogs.
- L255 _private member_ `FText LastInputValidityErrorText;` — The error text from the last validity check
- L258 _private member_ `bool bLastInputValidityCheckSuccessful;` — True if the last validity check returned that the class name/path is valid for creation
- L261 _private member_ `bool bPendingFocusNextFrame;` — Used to focus the name box after opening the dialog
- L264 _private member_ `bool bValidAssetsChosen;` — Used to specify that valid assets were chosen
- L267 _private member_ `TSharedPtr<FUICommandList> AssetViewCommands;` — Commands handled by this widget
- L268 _private member_ `TSharedPtr<FUICommandList> PathViewCommands;`
- L271 _private member_ `TSharedPtr<SPathPicker> PathPicker;` — Path Picker used by the dialog
- L274 _private member_ `TSharedPtr<SNavigationBar> NavigationBar;` — Navigation Bar used by the dialog
- L277 _private member_ `TSharedPtr<SAssetPicker> AssetPicker;` — Asset Picker used by the dialog
- L280 _private member_ `FOnPathSelected OnPathSelected;` — Callback for refreshing content

### `Source/Editor/ContentBrowser/Private/SCollectionPicker.h` (Private)


#### class `SCollectionPicker`  
`class SCollectionPicker : public SCompoundWidget`  
_L12-24_
- inherits: `SCompoundWidget`
- desc: A sources view designed for collection picking
- L15 _public function_ `SLATE_BEGIN_ARGS( SCollectionPicker )`
- L18 _public prototype_ `SLATE_ARGUMENT(FCollectionPickerConfig, CollectionPickerConfig) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — A struct containing details about how the collection picker should behave

### `Source/Editor/ContentBrowser/Private/SCollectionView.h` (Private)


#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<class SCollectionView>`  
_L52-55_
- L54 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SCollectionView`  
`class SCollectionView : public SCompoundWidget , public IScrollableWidget`  
_L60-415_
- inherits: `SCompoundWidget,IScrollableWidget`
- desc: The list view of collections.
- L66 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnCollectionSelected, const FCollectionNameType& );`
- L68 _public function_ `SLATE_BEGIN_ARGS( SCollectionView ) : _AllowCollectionButtons(true) , _AllowRightClickMenu(true) , _AllowContextMenu(true) , _IsDocked(false) , _AllowCollectionDrag(false) , _AllowQuickAssetManagement(false) , _ShowSeparator(true)`
- L79 _public prototype_ `SLATE_EVENT( FOnCollectionSelected, OnCollectionSelected ) SLATE_ARGUMENT( bool, AllowCollectionButtons ) SLATE_ARGUMENT( bool, AllowRightClickMenu ) SLATE_ARGUMENT( bool, AllowContextMenu ) SLATE_ATTRIBUTE( bool, IsDocked) SLATE_ARGUMENT( bool, AllowCollectionDrag ) SLATE_ARGUMENT( bool, AllowQuickAssetManagement ) SLATE_ARGUMENT( bool, ShowSeparator ) SLATE_ARGUMENT (TSharedPtr<ICollectionContainer>, CollectionContainer ) SLATE_ARGUMENT( TSharedPtr<FSourcesSearch>, ExternalSearch ) SLATE_END_ARGS() ~SCollectionView();` — Called when a collection was selected
- L107 _public prototype_ `void Construct( const FArguments& InArgs );` — Constructs this widget with InArgs
- L110 _public prototype_ `bool IsEmpty();` — Returns true if there are no collections being presented in this widget.
- L113 _public prototype_ `void SetSelectedCollections(const TArray<FCollectionNameType>& CollectionsToSelect, const bool bEnsureVisible = true);` — Selects the specified collections
- L116 _public prototype_ `void SetExpandedCollections(const TArray<FCollectionNameType>& CollectionsToExpand);` — Expands the specified collections
- L119 _public prototype_ `void ClearSelection();` — Clears selection of all collections
- L122 _public prototype_ `const TSharedPtr<ICollectionContainer>& GetCollectionContainer() const;` — Gets all the collection container this widget was constructed with
- L125 _public prototype_ `TArray<FCollectionNameType> GetSelectedCollections() const;` — Gets all the currently selected collections
- L128 _public prototype_ `void SetSelectedAssetPaths(const TArray<FSoftObjectPath>& SelectedAssets);` — Let the collections view know that the list of selected assets has changed, so that it can update the quick asset management check boxes
- L131 _public prototype_ `void ApplyHistoryData ( const FHistoryData& History );` — Sets the state of the collection view to the one described by the history data
- L134 _public prototype_ `void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const;` — Saves any settings to config that should be persistent between editor sessions
- L137 _public prototype_ `void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString);` — Loads any settings to config that should be persistent between editor sessions
- L139 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L140 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L141 _public prototype_ `virtual void OnDragEnter( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L142 _public prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;`
- L143 _public prototype_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L144 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L147 _public prototype_ `void MakeSaveDynamicCollectionMenu(FMenuBuilder& InMenuBuilder, FText InQueryString);` — Creates the menu for the save dynamic collection button
- L150 _public prototype_ `FReply OnAddCollectionClicked();` — Creates the menu for the add collection button
- L151 _public prototype_ `void MakeAddCollectionMenu(TSharedRef<SWidget> MenuParent);`
- L154 _public prototype_ `virtual FVector2D GetScrollDistance() override;`
- L155 _public prototype_ `virtual FVector2D GetScrollDistanceRemaining() override;`
- L156 _public prototype_ `virtual TSharedRef<SWidget> GetScrollWidget() override;`
- L196 _private prototype_ `bool ShouldAllowSelectionChangedDelegate() const;` — True if the selection changed delegate is allowed at the moment
- L199 _private prototype_ `void CreateCollectionItem( ECollectionShareType::Type CollectionType, ECollectionStorageMode::Type StorageMode, const FCreateCollectionPayload& InCreationPayload );` — Sets up an inline creation process for a new collection of the specified type
- L202 _private prototype_ `void RenameCollectionItem( const TSharedPtr<FCollectionItem>& ItemToRename );` — Sets up an inline rename for the specified collection
- L205 _private prototype_ `void DeleteCollectionItems( const TArray<TSharedPtr<FCollectionItem>>& ItemsToDelete );` — Delete the given collections
- L208 _private prototype_ `EVisibility GetCollectionTreeVisibility() const;` — Returns the visibility of the collection tree
- L211 _private prototype_ `EVisibility GetHeaderVisibility() const;` — Returns the visibility of the collection tree header. Collapsed if the collection tree is docked
- L214 _private prototype_ `EVisibility GetAddCollectionButtonVisibility() const;` — Returns the visibility of the add collection button
- L217 _private prototype_ `const FSlateBrush* GetCollectionViewDropTargetBorder() const;` — Get the border of the collection tree
- L220 _private prototype_ `TSharedRef<ITableRow> GenerateCollectionRow( TSharedPtr<FCollectionItem> CollectionItem, const TSharedRef<STableViewBase>& OwnerTable );` — Creates a list item for the collection tree
- L223 _private prototype_ `void GetCollectionItemChildren( TSharedPtr<FCollectionItem> InParentItem, TArray< TSharedPtr<FCollectionItem> >& OutChildItems ) const;` — Get the tree view children for the given item
- L226 _private prototype_ `FReply OnCollectionDragDetected(const FGeometry& Geometry, const FPointerEvent& MouseEvent);` — Handle starting a drag and drop operation for the currently selected collections
- L229 _private prototype_ `bool ValidateDragDropOnCollectionTree(const FGeometry& Geometry, const FDragDropEvent& DragDropEvent, bool& OutIsKnownDragOperation);` — Validate a drag drop operation on our collection tree
- L232 _private prototype_ `FReply HandleDragDropOnCollectionTree(const FGeometry& Geometry, const FDragDropEvent& DragDropEvent);` — Handle dropping something on collection tree
- L235 _private prototype_ `bool ValidateDragDropOnCollectionItem(TSharedRef<FCollectionItem> CollectionItem, const FGeometry& Geometry, const FDragDropEvent& DragDropEvent, bool& OutIsKnownDragOperation);` — Validate a drag drop operation on one of our collection items
- L238 _private prototype_ `FReply HandleDragDropOnCollectionItem(TSharedRef<FCollectionItem> CollectionItem, const FGeometry& Geometry, const FDragDropEvent& DragDropEvent);` — Handle dropping something on one of our collections
- L240 _private prototype_ `void HandleSettingChanged(FName PropertyName);`
- L243 _private prototype_ `void ExpandParentItems(const TSharedRef<FCollectionItem>& InCollectionItem);` — Recursively expand the parent items of this collection to ensure that it is visible
- L246 _private prototype_ `TSharedPtr<SWidget> MakeCollectionTreeContextMenu();` — Makes the context menu for the collection tree
- L249 _private prototype_ `bool IsCollectionCheckBoxEnabled( TSharedPtr<FCollectionItem> CollectionItem ) const;` — Whether the check box of the given collection item is currently enabled
- L252 _private prototype_ `ECheckBoxState IsCollectionChecked( TSharedPtr<FCollectionItem> CollectionItem ) const;` — Whether the check box of the given collection item is currently in a checked state
- L255 _private prototype_ `void OnCollectionCheckStateChanged( ECheckBoxState NewState, TSharedPtr<FCollectionItem> CollectionItem );` — Handler for when the checked state of the given collection item check box is changed
- L258 _private prototype_ `void CollectionSelectionChanged( TSharedPtr< FCollectionItem > CollectionItem, ESelectInfo::Type SelectInfo );` — Handler for collection list selection changes
- L261 _private prototype_ `void CollectionItemScrolledIntoView( TSharedPtr<FCollectionItem> CollectionItem, const TSharedPtr<ITableRow>& Widget );` — Handles focusing a collection item widget after it has been created with the intent to rename
- L264 _private prototype_ `bool IsCollectionNameReadOnly() const;` — Checks whether the selected collection is not allowed to be renamed
- L267 _private prototype_ `bool CollectionNameChangeCommit( const TSharedPtr< FCollectionItem >& CollectionItem, const FString& NewName, bool bChangeConfirmed, FText& OutWarningMessage );` — Handler for when a name was given to a collection. Returns false if the rename or create failed and sets OutWarningMessage depicting what happened.
- L270 _private prototype_ `bool CollectionVerifyRenameCommit(const TSharedPtr< FCollectionItem >& CollectionItem, const FString& NewName, const FSlateRect& MessageAnchor, FText& OutErrorMessage);` — Checks if the collection name being committed is valid
- L273 _private prototype_ `void HandleCollectionCreated( ICollectionContainer& InCollectionContainer, const FCollectionNameType& Collection );` — Handles an on collection created event
- L276 _private prototype_ `void HandleCollectionRenamed( ICollectionContainer& InCollectionContainer, const FCollectionNameType& OriginalCollection, const FCollectionNameType& NewCollection );` — Handles an on collection renamed event
- L279 _private prototype_ `void HandleCollectionReparented( ICollectionContainer& InCollectionContainer, const FCollectionNameType& Collection, const TOptional<FCollectionNameType>& OldParent, const TOptional<FCollectionNameType>& NewParent );` — Handles an on collection reparented event
- L282 _private prototype_ `void HandleCollectionDestroyed( ICollectionContainer& InCollectionContainer, const FCollectionNameType& Collection );` — Handles an on collection destroyed event
- L285 _private prototype_ `void HandleCollectionUpdated( ICollectionContainer& InCollectionContainer, const FCollectionNameType& Collection );` — Handles an on collection updated event
- L288 _private prototype_ `void HandleAssetsAddedToCollection( ICollectionContainer& InCollectionContainer, const FCollectionNameType& Collection, TConstArrayView<FSoftObjectPath> AssetsAdded );` — Handles assets being added to a collection
- L291 _private prototype_ `void HandleAssetsRemovedFromCollection( ICollectionContainer& InCollectionContainer, const FCollectionNameType& Collection, TConstArrayView<FSoftObjectPath> AssetsRemoved );` — Handles assets being removed from a collection
- L294 _private prototype_ `void HandleSourceControlProviderChanged(class ISourceControlProvider& OldProvider, class ISourceControlProvider& NewProvider);` — Handles the source control provider changing
- L297 _private prototype_ `void HandleSourceControlStateChanged();` — Handles the source control state changing
- L300 _private prototype_ `static void UpdateCollectionItemStatus( const TSharedRef<FCollectionItem>& CollectionItem );` — Handles updating the status of the given collection item
- L303 _private prototype_ `void UpdateCollectionItems();` — Updates the collections shown in the tree view
- L306 _private prototype_ `void UpdateFilteredCollectionItems();` — Update the visible collections based on the active filter text
- L309 _private prototype_ `void SetCollectionsSearchFilterText( const FText& InSearchText, TArray<FText>& OutErrors );` — Set the active filter text
- L312 _private prototype_ `FText GetCollectionsSearchFilterText() const;` — Get the active filter text
- L337 _private member_ `TSharedPtr<ICollectionContainer> CollectionContainer;` — The collection container to view
- L340 _private member_ `TSharedPtr<FSourcesSearch> ExternalSearchPtr;` — The collection external search interface (if any)
- L343 _private member_ `TSharedPtr<SHorizontalBox> TitleContent;` — The collection title content
- L346 _private member_ `TSharedPtr< STreeView< TSharedPtr<FCollectionItem> > > CollectionTreePtr;` — The collection tree widget
- L349 _private typedef_ `typedef TMap< FCollectionNameType, TSharedPtr<FCollectionItem> > FAvailableCollectionsMap;` — A map of collection keys to their associated collection items - this map contains all available collections, even those that aren't currently visible
- L350 _private member_ `FAvailableCollectionsMap AvailableCollections;`
- L353 _private member_ `TSet< FCollectionNameType > VisibleCollections;` — A set of collections that are currently visible, including parents that are only visible due to their children
- L356 _private member_ `TArray< TSharedPtr<FCollectionItem> > VisibleRootCollectionItems;` — The list of root items to show in the collections tree - this will be filtered as required
- L359 _private typedef_ `typedef TTextFilter<const FCollectionItem&> FCollectionItemTextFilter;` — The filter to apply to the available collections
- L360 _private member_ `TSharedPtr< FCollectionItemTextFilter > CollectionItemTextFilter;`
- L363 _private member_ `TSharedPtr<class FCollectionContextMenu> CollectionContextMenu;` — The context menu logic and data
- L366 _private member_ `FOnCollectionSelected OnCollectionSelected;` — Delegate to invoke when selection changes.
- L369 _private member_ `TAttribute<bool> IsDocked;` — Whether or not the collection view is docked under the sources panel
- L372 _private member_ `bool bAllowCollectionButtons;` — If true, collection buttons (such as add) are allowed
- L375 _private member_ `bool bAllowRightClickMenu;` — If true, the user will be able to access the right click menu of a collection
- L378 _private member_ `bool bAllowCollectionDrag;` — If true, the user will be able to drag collections from this view
- L381 _private member_ `bool bAllowExternalSearch;` — If true, we will use the external search if provided during construction
- L384 _private member_ `bool bDraggedOver;` — True when a drag is over this view with a valid operation for drop
- L387 _private member_ `int32 PreventSelectionChangedDelegateCount;` — If > 0, the selection changed delegate will not be called. Used to update the tree from an external source or in certain bulk operations.
- L390 _private member_ `TSharedPtr< FUICommandList > Commands;` — Commands handled by this widget
- L393 _private member_ `TSharedPtr<FCollectionAssetManagement> QuickAssetManagement;` — Handles the collection management for the currently selected assets (if available)
- L399 _private member_ `TWeakPtr<class FCollectionDragDropOp> CurrentCollectionDragDropOp;` — This is set after this view has initiated a drag and drop for some collections in our tree. We keep a weak pointer to this so we can tell if that drag and drop is still ongoing, and if so, what collections it affects
- L402 _private member_ `FDelegateHandle SourceControlProviderChangedHandle;` — Delegate handle for the HandleSourceControlProviderChanged function callback
- L405 _private member_ `FDelegateHandle SourceControlStateChangedDelegateHandle;` — Delegate handle for the HandleSourceControlStateChanged function callback
- L408 _private member_ `bool bQueueCollectionItemsUpdate;` — True if we should queue a collection items update for the next Tick
- L411 _private member_ `bool bQueueSCCRefresh;` — True if we should queue an SCC refresh for the collections on the next Tick
- L414 _private member_ `bool bQueueItemStatusUpdate = false;` — True if we need to update the source control state of items on next tick

#### struct `SCollectionView::FCreateCollectionPayload`  
`struct FCreateCollectionPayload`  
_L162-193_
- desc: Payload data for CreateCollectionItem (likely from a delegate binding)
- L164 _public function_ `FCreateCollectionPayload() : ParentCollection() , OnCollectionCreatedEvent()`
- L170 _public function_ `explicit FCreateCollectionPayload(TOptional<FCollectionNameType> InParentCollection) : ParentCollection(InParentCollection) , OnCollectionCreatedEvent()`
- L176 _public function_ `explicit FCreateCollectionPayload(FCollectionItem::FCollectionCreatedEvent InCollectionCreatedEvent) : ParentCollection() , OnCollectionCreatedEvent(InCollectionCreatedEvent)`
- L182 _public function_ `FCreateCollectionPayload(TOptional<FCollectionNameType> InParentCollection, FCollectionItem::FCollectionCreatedEvent InCollectionCreatedEvent) : ParentCollection(InParentCollection) , OnCollectionCreatedEvent(InCollectionCreatedEvent)`
- L189 _public member_ `TOptional<FCollectionNameType> ParentCollection;` — Should this collection be created as a child of another collection?
- L192 _public member_ `FCollectionItem::FCollectionCreatedEvent OnCollectionCreatedEvent;` — Callback for after the collection has been fully created (delayed due to user naming, and potential cancellation)

#### class `SCollectionView::FScopedPreventSelectionChangedDelegate`  
`class FScopedPreventSelectionChangedDelegate`  
_L317-334_
- desc: A helper class to manage PreventSelectionChangedDelegateCount by incrementing it when constructed (on the stack) and decrementing when destroyed
- L320 _public function_ `FScopedPreventSelectionChangedDelegate(const TSharedRef<SCollectionView>& InCollectionView) : CollectionView(InCollectionView)`
- L326 _public function_ `~FScopedPreventSelectionChangedDelegate()`
- L333 _private member_ `TSharedRef<SCollectionView> CollectionView;`

#### Free symbols / members of external scopes

- L66 _delegate_ `DECLARE_DELEGATE_OneParam( FOnCollectionSelected, const FCollectionNameType& );`

### `Source/Editor/ContentBrowser/Private/SContentBrowser.h` (Private)


#### enum `EContentBrowserViewContext`  
`enum class EContentBrowserViewContext : uint8`  
_L88-93_
- L90 _public enumerator_ `AssetView`
- L91 _public enumerator_ `PathView`
- L92 _public enumerator_ `FavoriteView`

#### class `SContentBrowser`  
`class SContentBrowser : public SCompoundWidget`  
_L98-887_
- inherits: `SCompoundWidget`
- desc: A widget to display and work with all game and engine content
- L101 _private typedef_ `using Super = SCompoundWidget;`
- L104 _public function_ `SLATE_BEGIN_ARGS( SContentBrowser ) : _ContainingTab() , _InitiallyLocked(false) , _IsDrawer(false)`
- L110 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SDockTab>, ContainingTab) SLATE_ARGUMENT(bool, InitiallyLocked ) SLATE_ARGUMENT(bool, IsDrawer) SLATE_END_ARGS() SContentBrowser();` — The tab in which the content browser resides
- L119 _public prototype_ `~SContentBrowser();`
- L121 _public prototype_ `bool ShouldShowRedirectors() const;`
- L124 _public prototype_ `void Construct( const FArguments& InArgs, const FName& InstanceName, const FContentBrowserConfig* Config );` — Constructs this widget with InArgs
- L126 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L129 _public prototype_ `void CreateNewAsset(const FString& DefaultAssetName, const FString& PackagePath, UClass* AssetClass, UFactory* Factory);` — Sets up an inline-name for the creation of a new asset using the specified path and the specified class and/or factory
- L139 _public prototype_ `void SyncToAssets( TArrayView<const FAssetData> AssetDataList, const bool bAllowImplicitSync = false, const bool bDisableFiltersThatHideAssets = true );` — Changes sources to show the specified assets and selects them in the asset view @param AssetDataList		- A list of assets to sync the view to @param bAllowImplicitSync	- true to allow the view to sync to parent folders if they are already selected, false to force the view to select the explicit Parent folders of each asset
- L149 _public prototype_ `void SyncToFolders( TArrayView<const FString> FolderList, const bool bAllowImplicitSync = false );` — Changes sources to show the specified folders and selects them in the asset view @param FolderList			- A list of folders to sync the view to @param bAllowImplicitSync	- true to allow the view to sync to parent folders if they are already selected, false to force the view to select the explicit Parent folders of each asset
- L156 _public prototype_ `void SyncToCollections(TArrayView<const FCollectionRef> CollectionsToSync);` — Changes sources to show the specified collections and selects them in the collection view @param CollectionsToSync	- A list of collections to sync the view to
- L166 _public prototype_ `void SyncToItems( TArrayView<const FContentBrowserItem> ItemsToSync, const bool bAllowImplicitSync = false, const bool bDisableFiltersThatHideAssets = true );` — Changes sources to show the specified items and selects them in the asset view @param ItemsToSync			- A list of items to sync the view to @param bAllowImplicitSync	- true to allow the view to sync to parent folders if they are already selected, false to force the view to select the explicit Parent folders of each asset
- L177 _public prototype_ `void SyncToLegacy( TArrayView<const FAssetData> AssetDataList, TArrayView<const FString> FolderList, const bool bAllowImplicitSync = false, const bool bDisableFiltersThatHideAssets = true );` — Changes sources to show the specified assets and folders and selects them in the asset view @param AssetDataList		- A list of assets to sync the view to @param FolderList			- A list of folders to sync the view to @param bAllowImplicitSync	- true to allow the view to sync to parent folders if they are already selected, false to force the view to select the explicit Parent folders of each asset
- L187 _public prototype_ `void SyncTo( const FContentBrowserSelection& ItemSelection, const bool bAllowImplicitSync = false, const bool bDisableFiltersThatHideAssets = true );` — Changes sources to show the specified items and selects them in the asset view @param AssetDataList		- A list of assets to sync the view to @param bAllowImplicitSync	- true to allow the view to sync to parent folders if they are already selected, false to force the view to select the explicit Parent folders of each asset
- L190 _public prototype_ `void SetIsPrimaryContentBrowser(bool NewIsPrimary);` — Sets this content browser as the primary browser. The primary browser is the target for asset syncs and contributes to the global selection set.
- L193 _public prototype_ `bool CanSetAsPrimaryContentBrowser() const;` — Returns if this browser can be used as the primary browser.
- L196 _public prototype_ `TSharedPtr<FTabManager> GetTabManager() const;` — Gets the tab manager for the tab containing this browser
- L199 _public prototype_ `void LoadSelectedObjectsIfNeeded();` — Loads all selected assets if unloaded
- L202 _public prototype_ `bool IsLegacyContentSourceActive() const;` — Returns true if the legacy (asset view) content source is the active content source
- L205 _public prototype_ `void GetSelectedAssets(TArray<FAssetData>& SelectedAssets);` — Returns all the assets that are selected in the asset view
- L208 _public prototype_ `void GetSelectedFolders(TArray<FString>& SelectedFolders);` — Returns all the folders that are selected in the asset view
- L211 _public prototype_ `TArray<FString> GetSelectedPathViewFolders();` — Returns the folders that are selected in the path view
- L214 _public prototype_ `void SaveSettings() const;` — Saves all persistent settings to config and returns a string identifier
- L217 _public prototype_ `void SetSelectedPaths(const TArray<FString>& FolderPaths, bool bNeedsRefresh = false);` — Sets the content browser to show the specified paths
- L220 _public prototype_ `FString GetCurrentPath(const EContentBrowserPathType PathType) const;` — Gets the current path if one exists, otherwise returns empty string.
- L227 _public prototype_ `void ForceShowPluginContent(bool bEnginePlugin);` — Forces the content browser to show plugin content @param bEnginePlugin		If true, the content browser will also be forced to show engine content
- L230 _public prototype_ `const FName GetInstanceName() const;` — Get the unique name of this content browser's in
- L233 _public prototype_ `bool IsLocked() const;` — Returns true if this content browser does not accept syncing from an external source
- L236 _public prototype_ `void SetKeyboardFocusOnSearch() const;` — Gives keyboard focus to the asset search box
- L242 _public prototype_ `void CopySettingsFromBrowser(TSharedPtr<SContentBrowser> OtherBrowser);` — Copies settings from a different browser to this browser Note this overrides any settings already saved for this browser
- L245 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — SWidget interface
- L246 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L247 _public prototype_ `virtual FReply OnPreviewMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L248 _public prototype_ `virtual FReply OnMouseButtonDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override;`
- L251 _public prototype_ `bool CanWriteToCurrentPath() const;` — Returns true if current path can be written to
- L254 _public prototype_ `bool CanWriteToPath(const FContentBrowserItemPath InPath) const;` — Returns true if path can be written to
- L257 _public prototype_ `void AddCustomTextFilter(const FCustomTextFilterData& FilterData, bool bApplyFilter);` — Adds a new Custom Text Filter to the Filter List
- L260 _public prototype_ `void DeleteCustomTextFilterByLabel(const FText& FilterLabel);` — Deletes the specified Custom Text Filter
- L263 _public prototype_ `void ModifyCustomTextFilterByLabel(const FCustomTextFilterData& NewFilterData, const FText& FilterLabel);` — Modifies the specified Custom Text Filter
- L266 _public prototype_ `bool IsAssetViewDoneFiltering();` — Gets whether the AssetView in the Content Browser is done filtering
- L269 _public prototype_ `void SetSearchText(const FText& InSearchText);` — Sets the actual text in the Search Box
- L272 _public prototype_ `void OnSearchBoxCommitted(const FText& InSearchText, ETextCommit::Type CommitInfo);` — Called by the editable text control when the user commits a text change
- L275 _public prototype_ `void ToggleFolderFavorite(const TArray<FString>& FolderPaths);` — Toggles the favorite status of an array of folders
- L278 _public prototype_ `void EditFolderFavorite(const FContentBrowserItemPath& InItemPath);` — Edit favorite folder options
- L281 _public prototype_ `void SetFilterLayout(EFilterBarLayout InFilterBarLayout) const;` — Sets the Content Browser filter layout to either vertical or horizontal
- L284 _public prototype_ `EFilterBarLayout GetFilterLayout() const;` — Gets the current Content Browser filter layout
- L287 _public prototype_ `TSharedPtr<SWidget> GetActiveFilterContainer() const;` — Gets a pointer to the active filter container widget (Horizontal or Vertical), nullptr if neither is active
- L293 _private prototype_ `void PrepareToSyncItems(TArrayView<const FContentBrowserItem> ItemsToSync, const bool bDisableFiltersThatHideAssets);` — Called prior to syncing the selection in this Content Browser
- L296 _private prototype_ `FText GetHighlightedText() const;` — Called to retrieve the text that should be highlighted on assets
- L299 _private prototype_ `void OnContainingTabSavingVisualState() const;` — Called when a containing tab is closing, if there is one
- L302 _private prototype_ `void OnContainingTabClosed(TSharedRef<SDockTab> DockTab);` — Called when a containing tab is closed, if there is one
- L305 _private prototype_ `void OnContainingTabActivated(TSharedRef<SDockTab> DockTab, ETabActivationCause InActivationCause);` — Called when a containing tab is activated, if there is one
- L308 _private prototype_ `void GetSourceTreeSplitterSlotSizeSettingKeyAndFilename(int32 SlotIndex, FString& OutKey, FString& OutFilename) const;` — Gets the key and ini file used to store the settings for each splitter slot
- L311 _private prototype_ `void LoadSettings(const FName& InstanceName);` — Loads settings from config based on the browser's InstanceName
- L314 _private prototype_ `void SourcesChanged(const TArray<FString>& SelectedPaths, const TArray<FCollectionRef>& SelectedCollections);` — Handler for when the sources were changed
- L317 _private prototype_ `void FolderEntered(const FContentBrowserItem& Folder);` — Handler for when a folder has been entered in the asset view
- L320 _private prototype_ `void PathSelected(const FString& FolderPath);` — Handler for when a path has been selected in the path view
- L323 _private prototype_ `void FavoritePathSelected(const FString& FolderPath);` — Handler for when a path has been selected in the favorite path view
- L326 _private prototype_ `TSharedRef<FExtender> GetPathContextMenuExtender(const TArray<FString>& SelectedPaths) const;` — Get the asset tree context menu
- L329 _private prototype_ `void CollectionSelected(const TSharedPtr<ICollectionContainer>& CollectionContainer, const FCollectionNameType& SelectedCollection);` — Handler for when a collection has been selected in the collection view
- L332 _private prototype_ `void OnApplyHistoryData(const FHistoryData& History);` — Sets the state of the browser to the one described by the supplied history data
- L335 _private prototype_ `void OnUpdateHistoryData(FHistoryData& History) const;` — Updates the supplied history data with current information
- L338 _private prototype_ `void NewFolderRequested(const FString& SelectedPath);` — Handler for when the path context menu requests a folder creation
- L341 _private prototype_ `void NewFileItemRequested(const FContentBrowserItemDataTemporaryContext& NewItemContext);` — Handler for when a data source requests file item creation
- L344 _private prototype_ `void SetSearchBoxText(const FText& InSearchText);` — Called when the editable text needs to be set or cleared
- L347 _private prototype_ `void SetAssetViewUserSearching(bool bIsSearching);` — Forwards the user-searching state to the asset view
- L350 _private prototype_ `void OnSearchBoxChanged(const FText& InSearchText);` — Called by the editable text control when the search text is changed by the user
- L353 _private prototype_ `FReply OnSearchKeyDown(const FGeometry& Geometry, const FKeyEvent& InKeyEvent);` — Called by the editable text control to allow the content browser to handle specific key presses without it resulting in typing into the search box
- L356 _private prototype_ `bool IsSaveSearchButtonEnabled() const;` — Should the "Save Search" button be enabled?
- L359 _private prototype_ `void OnSaveSearchButtonClicked(const FText& InSearchText);` — Open the menu to let you save the current search text as a filter or dynamic collection
- L362 _private prototype_ `void SaveSearchAsFilter();` — Save the current search as a filter pill
- L365 _private prototype_ `void EditPathCommand();` — Binding for begining to edit text in the location bar
- L368 _private prototype_ `void OnPathClicked(const FString& VirtualPath);` — Called when a crumb in the path breadcrumb trail or menu is clicked
- L371 _private prototype_ `void OnPathMenuItemClicked(FString ClickedPath);` — Called when item in the path delimiter arrow menu is clicked
- L379 _private prototype_ `TSharedRef<SWidget> OnGetCrumbDelimiterContent(const FString& CrumbData) const;` — Populates the delimiter arrow with a menu of directories under the current directory that can be navigated to @param CrumbData	The current directory path @return The directory menu
- L381 _private prototype_ `bool ParseCollectionCrumbData(const FString& CrumbData, FCollectionSource*& OutCollectionSource, FCollectionNameType& OutCollection) const;`
- L384 _private prototype_ `TArray<FNavigationBarComboOption> GetRecentPaths() const;` — Return a list of recently visited locations which can be used with OnNavigateToPath to return to those locations
- L387 _private prototype_ `void OnNavigateToPath(const FString& Path);` — Navigate to a location by text identifier. E.g. a virtual path such as /All/Game/MyFolder
- L390 _private prototype_ `FText OnGetEditPathAsText(const FString& Text) const;` — Returns how the currently shown location should be presented to the user as text when beginning to edit the path
- L393 _private prototype_ `TArray<FNavigationBarComboOption> OnCompletePathPrefix(const FString& Prefix) const;` — Returns a list of valid paths starting with Prefix which can be navigated to with OnNavigateToPath
- L396 _private prototype_ `void AppendNewMenuContextObjects(const EContentBrowserDataMenuContext_AddNewMenuDomain InDomain, const TArray<FName>& InSelectedPaths, FToolMenuContext& InOutMenuContext, UContentBrowserToolbarMenuContext* CommonContext, bool bCanBeModified);` — Register the context objects needed for the "Add New" menu
- L399 _private prototype_ `TSharedRef<SWidget> MakeAddNewContextMenu(const EContentBrowserDataMenuContext_AddNewMenuDomain InDomain, UContentBrowserToolbarMenuContext* CommonContext);` — Handle creating a context menu for the "Add New" button
- L402 _private prototype_ `void PopulateAddNewContextMenu(class UToolMenu* Menu);` — Handle populating a context menu for the "Add New" button
- L405 _private prototype_ `bool IsAddNewEnabled() const;` — Called to work out whether the import button should be enabled
- L408 _private prototype_ `FText GetAddNewToolTipText() const;` — Gets the tool tip for the "Add New" button
- L411 _private prototype_ `FReply OnSaveClicked();` — Saves dirty content.
- L414 _private prototype_ `void OnAddContentRequested();` — Opens the add content dialog.
- L417 _private prototype_ `void OnNewItemRequested(const FContentBrowserItem& NewItem);` — Handler for when a new item is requested in the asset view
- L420 _private prototype_ `void OnItemSelectionChanged(const FContentBrowserItem& SelectedItem, ESelectInfo::Type SelectInfo, EContentBrowserViewContext ViewContext);` — Handler for when the selection set in any view has changed.
- L423 _private prototype_ `void OnItemsActivated(TArrayView<const FContentBrowserItem> ActivatedItems, EAssetTypeActivationMethod::Type ActivationMethod);` — Handler for when the user double clicks, presses enter, or presses space on a Content Browser item
- L426 _private prototype_ `FReply ToggleLockClicked();` — Handler for clicking the lock button
- L429 _private prototype_ `FReply DockInLayoutClicked();` — Handler for clicking the dock drawer in layout button
- L432 _private prototype_ `FText GetLockMenuText() const;` — Gets the menu text
- L435 _private prototype_ `FSlateIcon GetLockIcon() const;` — Gets icon for the lock button
- L438 _private prototype_ `const FSlateBrush* GetLockIconBrush() const;` — Gets brush for the lock button
- L441 _private prototype_ `EVisibility GetSourcesViewVisibility() const;` — Gets the visibility state of the asset tree
- L444 _private prototype_ `void SetSourcesViewExpanded(bool bExpanded);` — Set whether or not we the sources view is expanded.
- L447 _private prototype_ `FReply SourcesViewExpandClicked();` — Handler for clicking the tree expand/collapse button
- L450 _private prototype_ `void OnContentBrowserSettingsChanged(FName PropertyName);` — Called to handle the Content Browser settings changing
- L456 _private prototype_ `void OnConsoleVariableChanged();` — Called when engine Cvars change to update content browser settings e.g. private content feature
- L459 _private prototype_ `FReply BackClicked();` — Handler for clicking the history back button
- L462 _private prototype_ `FReply ForwardClicked();` — Handler for clicking the history forward button
- L465 _private prototype_ `bool HandleFilterBySelectionCommandCanExecute() const;` — Handler to check if filter by selection command is allowed
- L468 _private prototype_ `void HandleFilterBySelectionCommandExecute();` — Handler for filter by selection
- L471 _private prototype_ `void HandleFavoriteShortcutCommandExecute(FName InCommandName);` — Handler for favorite shortcuts
- L474 _private prototype_ `bool HandleRenameCommandCanExecute() const;` — Handler to check to see if a rename command is allowed
- L477 _private prototype_ `void HandleRenameCommand();` — Handler for Rename
- L480 _private prototype_ `bool HandleSaveAssetCommandCanExecute() const;` — Handler to check to see if a save asset command is allowed
- L483 _private prototype_ `void HandleSaveAssetCommand();` — Handler for save asset
- L486 _private prototype_ `void HandleSaveAllCurrentFolderCommand() const;` — Handler for SaveAll in folder
- L489 _private prototype_ `void HandleResaveAllCurrentFolderCommand() const;` — Handler for Resave on a folder
- L492 _private prototype_ `void CopySelectedAssetPathCommand() const;` — Handler for Copy path on an asset
- L495 _private prototype_ `bool HandleDeleteCommandCanExecute() const;` — Handler to check to see if a delete command is allowed
- L498 _private prototype_ `void HandleDeleteCommandExecute();` — Handler for Delete
- L501 _private prototype_ `void HandleDeleteFavorite(TSharedPtr<SWidget> ParentWidget);` — Handler for deleting a favorite using a keybind.
- L504 _private prototype_ `void HandleOpenAssetsOrFoldersCommandExecute();` — Handler for opening assets or folders
- L507 _private prototype_ `void HandlePreviewAssetsCommandExecute();` — Handler for previewing assets
- L510 _private prototype_ `void HandleCreateNewFolderCommandExecute();` — Handler for creating new folder
- L513 _private prototype_ `void HandleGoUpToParentFolder();` — Handler for navigating up to the parent folder of the one currently open
- L516 _private prototype_ `bool HandleCanGoUpToParentFolder() const;` — True if the user may navigate from the currently selected folder to its parent
- L519 _private prototype_ `bool IsBackEnabled() const;` — True if the user may use the history back button
- L522 _private prototype_ `bool IsForwardEnabled() const;` — True if the user may use the history forward button
- L525 _private prototype_ `FText GetHistoryBackTooltip() const;` — Gets the tool tip text for the history back button
- L528 _private prototype_ `FText GetHistoryForwardTooltip() const;` — Gets the tool tip text for the history forward button
- L531 _private prototype_ `void SyncGlobalSelectionSet();` — Sets the global selection set to the asset view's selected items
- L534 _private prototype_ `void UpdatePath();` — Updates the breadcrumb trail to the current path
- L537 _private prototype_ `void OnFilterChanged();` — Handler for when a filter in the filter list has changed
- L540 _private prototype_ `FText GetPathText() const;` — Gets the text for the path label
- L543 _private prototype_ `bool IsFilteredBySource() const;` — Returns true if currently filtering by a source
- L546 _private prototype_ `void OnShowInPathsViewRequested(TArrayView<const FContentBrowserItem> ItemsToFind);` — Handler for when the context menu or asset view requests to find items in the paths view
- L549 _private prototype_ `void OnItemRenameCommitted(TArrayView<const FContentBrowserItem> Items);` — Handler for when the user has committed a rename of an item
- L552 _private prototype_ `void OnRenameRequested(const FContentBrowserItem& Item, EContentBrowserViewContext ViewContext);` — Handler for when the asset context menu requests to rename an item
- L555 _private prototype_ `void OnOpenedFolderDeleted();` — Handler for when the path context menu has successfully deleted a folder
- L558 _private prototype_ `void OnDuplicateRequested(TArrayView<const FContentBrowserItem> OriginalItems);` — Handler for when the asset context menu requests to duplicate an item
- L561 _private prototype_ `void OnAssetViewRefreshRequested();` — Handler for when the asset context menu requests to refresh the asset view
- L564 _private prototype_ `void HandleCollectionContainerAdded(const TSharedRef<ICollectionContainer>& CollectionContainer);` — Handles an on collection container created event
- L566 _private prototype_ `void ShowCollectionContainer(const TSharedRef<ICollectionContainer>& CollectionContainer);`
- L569 _private prototype_ `void HandleCollectionContainerRemoved(const TSharedRef<ICollectionContainer>& CollectionContainer);` — Handles an on collection container destroyed event
- L571 _private prototype_ `void HideCollectionContainer(const TSharedRef<ICollectionContainer>& CollectionContainer);`
- L574 _private prototype_ `void HandleIsHiddenChanged(ICollectionContainer& CollectionContainer, bool bIsHidden);` — Handles an on collection container is hidden changed event
- L577 _private prototype_ `void HandleCollectionRemoved(ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection);` — Handles an on collection destroyed event
- L580 _private prototype_ `void HandleCollectionRenamed(ICollectionContainer& CollectionContainer, const FCollectionNameType& OriginalCollection, const FCollectionNameType& NewCollection);` — Handles an on collection renamed event
- L583 _private prototype_ `void HandleCollectionUpdated(ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection);` — Handles an on collection updated event
- L586 _private prototype_ `void HandlePathRemoved(const FName Path);` — Handles a path removed event
- L589 _private prototype_ `void HandleItemDataUpdated(TArrayView<const FContentBrowserItemDataUpdate> InUpdatedItems);` — Handles content items being updated
- L592 _private prototype_ `void OnAssetSearchSuggestionFilter(const FText& SearchText, TArray<FAssetSearchBoxSuggestion>& PossibleSuggestions, FText& SuggestionHighlightText) const;` — Gets all suggestions for the asset search box
- L595 _private prototype_ `FText OnAssetSearchSuggestionChosen(const FText& SearchText, const FString& Suggestion) const;` — Combines the chosen suggestion with the active search text
- L598 _private prototype_ `FText GetSearchAssetsHintText() const;` — Gets the dynamic hint text for the "Search Assets" search text box
- L601 _private prototype_ `TSharedPtr<SWidget> GetItemContextMenu(TArrayView<const FContentBrowserItem> SelectedItems, EContentBrowserViewContext ViewContext);` — Delegate called when generating the context menu for an item
- L604 _private prototype_ `void PopulateFolderContextMenu(UToolMenu* Menu);` — Populate the context menu for a folder
- L607 _private prototype_ `void GetSelectionState(TArray<FAssetData>& SelectedAssets, TArray<FString>& SelectedPaths);` — Delegate called to get the current selection state
- L610 _private prototype_ `void CreateNewFolder(FString FolderPath, FOnCreateNewFolder OnCreateNewFolder);` — Sets up an inline-name for the creation of a default-named folder the specified path
- L613 _private prototype_ `void OpenNewContentBrowser();` — Handler for when "Open in new Content Browser" is selected
- L616 _private prototype_ `void BindCommands();` — Bind our UI commands
- L619 _private prototype_ `void UnbindCommands();` — Unbind our UI commands
- L622 _private prototype_ `EVisibility GetFavoriteFolderVisibility() const;` — Gets the visibility of the favorites view
- L625 _private prototype_ `EVisibility GetLockButtonVisibility() const;` — Get the visibility of the lock button
- L628 _private prototype_ `void UpdateFolderFavorite(const TArray<FString>& FolderPaths, const FString& InFolder, EItemDropZone InPosition);` — Updates favorite status of an array of folders
- L631 _private prototype_ `void SaveAndShowNewFolderFavorites(const TArray<FString>& FolderPaths);` — Save the favorite paths to settings and optionally select and show the paths passed in
- L634 _private prototype_ `void TogglePrivateContentEdit(const TArray<FString>& FolderPaths);` — Toggles the private show private content state of an array of folders
- L637 _private prototype_ `void HandleAssetViewSearchOptionsChanged();` — Called when Asset View Options "Search" options change
- L640 _private prototype_ `void PopulatePathViewFiltersMenu(UToolMenu* Menu);` — Fill menu for filtering path view with items
- L643 _private prototype_ `void ExtendAssetViewButtonMenuContext(FToolMenuContext& InMenuContext);` — Add data so that menus can access content browser
- L646 _private prototype_ `TSharedRef<SWidget> CreateToolBar(const FContentBrowserConfig* Config);` — Creates various widgets for the content browser main view
- L648 _private prototype_ `TSharedRef<SWidget> CreateNavigationToolBar(const FContentBrowserConfig* Config);`
- L650 _private prototype_ `TSharedRef<SWidget> CreateLockButton(const FContentBrowserConfig* Config);`
- L651 _private prototype_ `TSharedRef<SWidget> CreateAssetView(const FContentBrowserConfig* Config);`
- L652 _private prototype_ `TSharedRef<SWidget> CreateFavoritesView(const FContentBrowserConfig* Config);`
- L653 _private prototype_ `TSharedRef<SWidget> CreatePathView(const FContentBrowserConfig* Config);`
- L654 _private prototype_ `TSharedRef<UE::Editor::ContentBrowser::Private::SContentBrowserSourceTreeArea> CreateCollectionsView(FCollectionSource& CollectionSource);`
- L655 _private prototype_ `TSharedRef<SWidget> CreateDrawerDockButton(const FContentBrowserConfig* Config);`
- L657 _private prototype_ `FCollectionSource& AddSlotForCollectionContainer(int32 Index, const TSharedRef<ICollectionContainer>& CollectionContainer);`
- L658 _private prototype_ `void RemoveSlotForCollectionContainer(const TSharedRef<ICollectionContainer>& CollectionContainer);`
- L660 _private prototype_ `void SetFavoritesExpanded(bool bExpanded);`
- L661 _private prototype_ `void SetPathViewExpanded(bool bExpanded);`
- L664 _private prototype_ `void ExtendViewOptionsMenu(const FContentBrowserConfig* Config);` — Adds menu options to the view menu
- L667 _private prototype_ `SSplitter::ESizeRule GetFavoritesAreaSizeRule() const;` — Gets the size rule for various areas. When areas are a collapsed the splitter slot becomes auto sized, otherwise it is user sized
- L668 _private prototype_ `SSplitter::ESizeRule GetPathAreaSizeRule() const;`
- L671 _private prototype_ `void OnPathViewBoxColumnResized(float InSize);` — Called when the Splitter containing the PathView Box gets resized
- L674 _private prototype_ `FOptionalSize GetPathViewBoxWidthOverride() const;` — Returns the PathView Box width
- L677 _private prototype_ `void OnFilterBoxColumnResized(float InSize);` — Called when the Splitter containing the filters Box gets resized
- L680 _private prototype_ `FOptionalSize GetFilterViewBoxWidthOverride() const;` — Returns the filters Box width
- L683 _private prototype_ `float GetFavoritesAreaMinSize() const;` — Gets the min size for various areas. When areas are not visible the min size is 0, otherwise there is a minimum size to prevent overlap
- L686 _private prototype_ `void OnFilterBarLayoutChanging(EFilterBarLayout NewLayout);` — Called when the layout of the SFilterList is changing
- L689 _private prototype_ `const FContentBrowserInstanceConfig* GetConstInstanceConfig() const;` — Fetch the const config for this content browser instance.
- L692 _private prototype_ `FContentBrowserInstanceConfig* GetMutableInstanceConfig();` — Fetch the mutable config for this content browser instance.
- L695 _private prototype_ `FContentBrowserInstanceConfig* CreateEditorConfigIfRequired();` — Initialize an editor config for this instance if one does not exist.
- L697 _private prototype_ `void UpdatePrivateContentFeatureEnabled(bool bUpdateFilterIfChanged);`
- L700 _private prototype_ `void OnLegacyContentSourceEnabled();` — Executed when the legacy content source is enabled.
- L703 _private prototype_ `void OnLegacyContentSourceDisabled();` — Executed when the legacy content source is enabled.
- L706 _private prototype_ `TSharedRef<SWidget> CreateLegacyAssetViewWidgets();` — Create the content browser widgets (SPathView, SAssetView, search and filter bars etc)
- L708 _private prototype_ `void OnSearchOverrideToggled();`
- L769 _private member_ `TUniquePtr<FLegacyContentSourceWidgets> LegacyContentSourceWidgets;`
- L772 _private member_ `TWeakPtr<SDockTab> ContainingTab;` — The tab that contains this browser
- L775 _private member_ `FHistoryManager HistoryManager;` — The manager that keeps track of history data for this browser
- L781 _private member_ `TMRUArray<FString> JumpMRU;` — A list of locations "jumped" to for populating a dropdown of such locations. As a general rule, simple up/down navigation should not populate this list and only direct entries such as "find in content browser" or typing in a path should populate it
- L784 _private member_ `TSharedPtr<FSourcesSearch> FavoritesSearch;` — The sources search for favorites
- L787 _private member_ `TSharedPtr<FSourcesSearch> SourcesSearch;` — The sources search for paths
- L790 _private member_ `TSharedPtr<SWidget> FilterComboButton;` — The Combo Button used to summon the filter dropdown
- L793 _private member_ `TSharedPtr<UE::Editor::ContentBrowser::Private::SContentBrowserSourceTreeArea> FavoritesArea;` — Favorites area widget
- L796 _private member_ `TSharedPtr<UE::Editor::ContentBrowser::Private::SContentBrowserSourceTreeArea> PathArea;` — Path area widget
- L799 _private member_ `TArray<TUniquePtr<FCollectionSource>> CollectionSources;` — Widgets for each collection container
- L802 _private member_ `bool bSourcesViewExpanded = true;` — The expanded state of the asset tree
- L805 _private member_ `bool bIsPrimaryBrowser = false;` — True if this browser is the primary content browser
- L808 _private member_ `bool bCanSetAsPrimaryBrowser = true;` — True if this content browser can be set to the primary browser.
- L811 _private member_ `bool bIsDrawer = false;` — True if this content browser is an a drawer
- L814 _private member_ `bool bIsLocked = false;` — True if source should not be changed from an outside source
- L817 _private member_ `bool bPrivateContentFilterEnabled = false;` — True if bShouldEnablePrivateContentFilter was true and we are filtering this->AssetView.
- L820 _private member_ `float PathViewBoxWidth = 230.f;` — Starting width of the PathView Box
- L823 _private member_ `float FilterBoxWidth = 180.f;` — Starting width of the Filter Box
- L826 _private member_ `mutable bool bCachedCanWriteToCurrentPath = false;` — Cached result of CanWriteToPath to avoid recalculating it every frame
- L829 _private member_ `FName InstanceName;` — Unique name for this Content Browser.
- L832 _private member_ `mutable TOptional<FName> CachedCanWriteToCurrentPath;` — Path that was last used to determine bCachedCanWriteToCurrentPath
- L835 _private member_ `TSharedPtr<FAssetFilterCollectionType> FrontendFilters;` — The list of FrontendFilters currently applied to the asset view
- L838 _private member_ `TSharedPtr<FAssetTextFilter> TextFilter;` — The text filter to use on the assets, separate from FrontendFilters so it can be specifically optimized
- L841 _private member_ `TSharedPtr< FUICommandList > Commands;` — Commands handled by this widget
- L844 _private member_ `FOnCreateNewFolder OnCreateNewFolder;` — Delegate used to create a new folder
- L847 _private member_ `TSharedPtr<FPluginFilterCollectionType> PluginPathFilters;` — The list of plugin filters currently applied to the path view
- L850 _private member_ `TOptional<FText> StashedSearchBoxText;` — When viewing a dynamic collection, the active search query will be stashed in this variable so that it can be restored again later
- L853 _private member_ `FConsoleVariableSinkHandle CVarSinkHandle;` — Handle to a callback for when CVars change
- L856 _private member_ `TSharedPtr<UE::Editor::ContentBrowser::SContentSourcesView> ContentSourcesContainer;` — Widget that contains the content sources selector (if enabled) and the currently enabled content source
- L859 _private member_ `TSharedPtr<UE::Editor::ContentBrowser::SLegacyContentSource> LegacyContentSource;` — A legacy content source, which when enabled displays the default content browser widgets
- L864 _private member_ `FContentBrowserConfig InitConfig;` — A copy of the init params used by the content browser so we can re-create the widgets dynamically If no init params were provided, the default values will be used.
- L867 _private member_ `bool bHasInitConfig = false;` — Whether this content browser was specified an init config
- L870 _private member_ `static FDelayedAutoRegisterHelper AddNewContextMenuRegistration;` — Registers the "Add New" drop-down menu
- L873 _private member_ `static FDelayedAutoRegisterHelper NavigationBarMenuRegistration;` — Registers the bottom navigation bar
- L876 _private member_ `static FDelayedAutoRegisterHelper FolderContextMenuRegistration;` — Registers the context menu for folders
- L879 _private member_ `static FDelayedAutoRegisterHelper PathViewFiltersMenuRegistration;` — Registers a sub-menu within the settings button menu
- L882 _private member_ `static FDelayedAutoRegisterHelper ToolBarMenuRegistration;` — Registers the top toolbar
- L886 _public member_ `static const FString SettingsIniSection;` — The section of EditorPerProjectUserSettings in which to save content browser settings

#### struct `SContentBrowser::FLegacyContentSourceWidgets`  
`struct FLegacyContentSourceWidgets`  
_L716-767_
- desc: Struct that contains the widgets used by content browser's default layout (i.e Legacy Content Source) ContentBrowser 2.0 will use TEDS, this is moved here but is still in use and correct while Content Browser refactor is on hold
- L719 _public member_ `TSharedPtr<class FPathContextMenu> PathContextMenu;` — The context menu manager for the path view
- L722 _public member_ `TSharedPtr<SAssetView> AssetViewPtr;` — The asset view widget
- L725 _public member_ `TSharedPtr<SBorder> AssetViewBorder;` — The border that holds the content in AssetView
- L728 _public member_ `TSharedPtr<class FAssetContextMenu> AssetContextMenu;` — A helper class to manage asset context menu options
- L731 _public member_ `TSharedPtr<SFilterList> FilterListPtr;` — The filter list
- L734 _public member_ `TSharedPtr<SAssetSearchBox> SearchBoxPtr;` — The text box used to search for assets
- L737 _public member_ `TSharedPtr<UE::Editor::ContentBrowser::Extension::ICBSearchOverrideInstance> AssetSearchOverrideInstance;` — Per-view instance of the active search override, if any
- L740 _public member_ `TSharedPtr<UE::Editor::ContentBrowser::Private::TWidgetDesiredSizeSwitcher<EAxis::X>> SearchBoxSizeSwitcher;` — Handles the search box sizing within the toolbar
- L743 _public member_ `TSharedPtr<SNavigationBar> NavigationBar;` — Combine breadcrumb/text-box widget for showing & changing location
- L746 _public member_ `TSharedPtr<SFavoritePathView> FavoritePathViewPtr;` — The favorites tree widget
- L749 _public member_ `TSharedPtr<SPathView> PathViewPtr;` — The asset tree widget
- L751 _public member_ `TSharedPtr<UE::Editor::ContentBrowser::Private::SContentBrowserSourceTree> SourceTreePtr;`
- L754 _public member_ `TSharedPtr<SWidget> NavigationToolBarWidget;` — The generated navigation toolbar widget
- L757 _public member_ `TSharedPtr<SSplitter> PathAssetSplitterPtr;` — The splitter between the path & asset view
- L760 _public member_ `TSharedPtr<SSplitter> PathFavoriteSplitterPtr;` — The splitter between the path, favorite and collection views
- L763 _public member_ `int32 SourceTreeSplitterNumFixedSlots = 0;` — The number of fixed slots in the splitter, slots after this number are collection view slots
- L766 _public member_ `TSharedPtr<SBox> VerticalFilterViewContainer;` — The containing widget for the vertical filter view

#### Free symbols / members of external scopes

- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace Editor` (scope `UE`)
- L34 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)
- L39 _namespace_ `namespace Private` (scope `UE::Editor::ContentBrowser`)

### `Source/Editor/ContentBrowser/Private/SNavigationBar.h` (Private)


#### struct `FNavigationBarComboOption`  
`struct FNavigationBarComboOption`  
_L25-32_
- L27 _public prototype_ `FNavigationBarComboOption() = default;`
- L28 _public prototype_ `FNavigationBarComboOption(const FText& InDisplayPath, const FString& InPath);`
- L30 _public member_ `FText DisplayPath;`
- L31 _public member_ `FString Path;`

#### class `SNavigationBar`  
`class SNavigationBar : public SComboButton`  
_L45-164_
- inherits: `SComboButton`
- L48 _public function_ `SLATE_BEGIN_ARGS(SNavigationBar) : _ComboBoxStyle(&FAppStyle::Get().GetWidgetStyle< FComboBoxStyle >("ComboBox")) , _ItemStyle(&FAppStyle::Get().GetWidgetStyle< FTableRowStyle >("ComboBox.Row")) , _TextBoxStyle(&FAppStyle::Get().GetWidgetStyle<FEditableTextBoxStyle>("NormalEditableTextBox")) , _BreadcrumbButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("SimpleButton")) , _BreadcrumbTextStyle(&FAppStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText")) , _BreadcrumbButtonContentPadding(FMargin(2,2)) , _BreadcrumbDelimiterImage(FAppStyle::Get().GetBrush("Icons.ChevronRight"))`
- L58 _public prototype_ `SLATE_STYLE_ARGUMENT( FComboBoxStyle, ComboBoxStyle ) SLATE_STYLE_ARGUMENT(FTableRowStyle, ItemStyle) SLATE_STYLE_ARGUMENT(FTableViewStyle, SuggestionsStyle) SLATE_STYLE_ARGUMENT(FEditableTextBoxStyle, TextBoxStyle) SLATE_STYLE_ARGUMENT(FButtonStyle, BreadcrumbButtonStyle) SLATE_STYLE_ARGUMENT(FTextBlockStyle, BreadcrumbTextStyle) SLATE_ATTRIBUTE(FMargin, BreadcrumbButtonContentPadding) SLATE_ATTRIBUTE(const FSlateBrush*, BreadcrumbDelimiterImage) SLATE_EVENT(FOnNavigateToPath , OnNavigateToPath) SLATE_EVENT(FOnPathClicked , OnPathClicked) SLATE_EVENT(FGetPathMenuContent, GetPathMenuContent) SLATE_EVENT(FGetComboOptions, GetComboOptions) SLATE_EVENT(FOnCompletePrefix, OnCompletePrefix) SLATE_EVENT(FGetEditPathAsText, OnGetEditPathAsText)` — The styling of the combo box which wraps the other navigation controls
- L104 _public prototype_ `void ClearPaths();` — Remove all paths from the breadcrumb bar
- L106 _public prototype_ `void PushPath(const FText& SegmentDisplayText, const FString& FullLocation, bool bHasChildren);` — Add a new segment to the breadcrumb bar
- L108 _public prototype_ `void StartEditingPath();` — Replace the breadcrumb bar with an editable text box and focus it
- L112 _private prototype_ `virtual void OnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent) override;` — SWidget overrides
- L114 _private prototype_ `virtual FReply OnButtonClicked() override;` — SComboButton overrides
- L117 _private prototype_ `FReply HandleBlankSpaceClicked();` — Handle clicking on part of the navigation bar which is not the combo button or the breadcrumb bar, to switch to edit mode
- L118 _private prototype_ `void HandleTextChanged(const FText& NewText);`
- L119 _private prototype_ `void HandleTextCommitted(const FText& InText, ETextCommit::Type CommitType);`
- L120 _private prototype_ `void HandleComboSelectionChanged(TSharedPtr<FLocationItem> SelectedItem, ESelectInfo::Type SelectInfo);`
- L121 _private prototype_ `TSharedRef<ITableRow> HandleGenerateComboRow(TSharedPtr<FLocationItem> ForItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L122 _private prototype_ `FReply HandleEditableTextKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent);`
- L123 _private prototype_ `FReply HandleComboKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L124 _private prototype_ `FReply HandleComboKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharEvent);`
- L125 _private prototype_ `void HandleCrumbClicked(const FNavigationCrumb& Crumb);`
- L126 _private prototype_ `bool HandleHasCrumbMenuContent(const FNavigationCrumb& Crumb);`
- L127 _private prototype_ `TSharedRef<SWidget> HandleGetCrumbMenuContent(const FNavigationCrumb& Crumb);`
- L129 _private prototype_ `EActiveTimerReturnType HandleUpdateCompletionOptions(double InCurrentTime, float InDeltaTime);`
- L131 _private prototype_ `void GenerateHistoryOptions();`
- L132 _private prototype_ `void GenerateCompletionOptions(const FString& Prefix);`
- L134 _private prototype_ `EVisibility GetEditTextVisibility() const;`
- L135 _private prototype_ `EVisibility GetNonEditVisibility() const;`
- L136 _private prototype_ `FText GetPopupHeading() const;`
- L137 _private prototype_ `const FSlateBrush* GetImageForItem(const FLocationItem& ForItem) const;`
- L139 _private prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L141 _private member_ `const FComboBoxStyle* ComboBoxStyle;`
- L142 _private member_ `const FTableRowStyle* TableRowStyle;`
- L143 _private member_ `const FEditableTextBoxStyle* TextBoxStyle;`
- L144 _private member_ `const FSlateBrush* SuggestionIcon;`
- L145 _private member_ `const FSlateBrush* HistoryIcon;`
- L147 _private member_ `EVisibility EditTextVisibility = EVisibility::Hidden;`
- L148 _private member_ `TSharedPtr<FActiveTimerHandle> CompletionTimerHandle;`
- L150 _private member_ `TSharedPtr<SEditableText> EditableText;`
- L151 _private member_ `TSharedPtr<SBreadcrumbTrail<FNavigationCrumb>> BreadcrumbBar;`
- L152 _private member_ `TSharedPtr<SLocationListView> ComboListView;`
- L154 _private member_ `FText PopupHeading;`
- L156 _private member_ `bool bNoSuggestionsFromTextChange = false;`
- L158 _private member_ `FOnNavigateToPath OnNavigateToPath;`
- L159 _private member_ `FGetComboOptions OnGetComboOptions;`
- L160 _private member_ `FOnCompletePrefix OnCompletePrefix;`
- L161 _private member_ `FGetEditPathAsText OnGetEditPathAsText;`
- L162 _private member_ `FOnPathClicked OnPathClicked;`
- L163 _private member_ `FGetPathMenuContent OnGetPathMenuContent;`

#### Free symbols / members of external scopes

- L34 _typedef_ `using FOnPathClicked = TDelegate<void(const FString&)>;`
- L35 _typedef_ `using FGetPathMenuContent = TDelegate<TSharedRef<SWidget>(const FString&)>;`
- L36 _typedef_ `using FGetComboOptions = TDelegate<TArray<FNavigationBarComboOption>(void)>;`
- L37 _typedef_ `using FOnCompletePrefix = TDelegate<TArray<FNavigationBarComboOption>(const FString&)>;`
- L38 _typedef_ `using FOnNavigateToPath = TDelegate<void(const FString&)>;`
- L39 _typedef_ `using FGetEditPathAsText = TDelegate<FText(const FString&)>;`

### `Source/Editor/ContentBrowser/Private/SPathPicker.h` (Private)


#### class `SPathPicker`  
`class SPathPicker : public SCompoundWidget`  
_L22-87_
- inherits: `SCompoundWidget`
- desc: A sources view designed for path picking
- L25 _public function_ `SLATE_BEGIN_ARGS( SPathPicker )`
- L28 _public prototype_ `SLATE_ARGUMENT(FPathPickerConfig, PathPickerConfig) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — A struct containing details about how the path picker should behave
- L36 _public prototype_ `void SetPaths(const TArray<FString>& NewPaths);` — Sets the selected paths in this picker
- L39 _public prototype_ `TArray<FString> GetPaths() const;` — Return the selected paths in this picker
- L42 _public prototype_ `const TSharedPtr<SPathView>& GetPathView() const;` — Return the associated SPathView
- L44 _public prototype_ `void SyncToItems(TArrayView<const FContentBrowserItem> ItemsToSync, const bool bAllowImplicitSync);`
- L47 _public prototype_ `void CreateNewFolder(FString FolderPath, FOnCreateNewFolder InOnCreateNewFolder);` — Handler for creating a new folder in the path picker
- L50 _public prototype_ `void ExecuteRenameFolder();` — Rename the selected, will just use the first folder selected
- L53 _public prototype_ `void ExecuteAddFolder();` — Add a folder to the first selected folder
- L56 _public prototype_ `void RefreshPathView();` — Refresh the path view
- L61 _private prototype_ `void OnItemSelectionChanged(const FContentBrowserItem& SelectedItem, ESelectInfo::Type SelectInfo);` — Handle for when selection changes
- L64 _private prototype_ `TSharedPtr<SWidget> GetItemContextMenu(TArrayView<const FContentBrowserItem> SelectedItems);` — Handler for the context menu for folder items
- L65 _private prototype_ `TSharedPtr<SWidget> GetFolderContextMenu(TArrayView<const FContentBrowserItem> SelectedItems, FContentBrowserMenuExtender_SelectedPaths InMenuExtender, FOnCreateNewFolder InOnCreateNewFolder);`
- L66 _private prototype_ `static TArray<FString> GetInternalPaths(TArrayView<const FContentBrowserItem> SelectedItems);`
- L71 _private member_ `TSharedPtr<SPathView> PathViewPtr;` — The path view in this picker
- L74 _private member_ `FOnPathSelected OnPathSelected;` — Delegate to invoke when selection changes.
- L77 _private member_ `FOnGetFolderContextMenu OnGetFolderContextMenu;` — Delegate to invoke when a context menu for a folder is opening.
- L80 _private member_ `FContentBrowserMenuExtender_SelectedPaths OnGetPathContextMenuExtender;` — The delegate that fires when a path is right clicked and a context menu is requested
- L83 _private member_ `bool bOnPathSelectedPassesVirtualPaths;` — If true, passes virtual paths to OnPathSelected instead of internal asset paths
- L86 _private member_ `FString LastSelectedPath;` — Path currently selected in this picker. Used to suppress redundant OnPathSelected events.

### `Source/Editor/ContentBrowser/Private/SPathView.h` (Private)


#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<class SPathView>`  
_L65-68_
- L67 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SPathView`  
`class SPathView : public SCompoundWidget , public IScrollableWidget`  
_L73-600_
- inherits: `SCompoundWidget,IScrollableWidget`
- desc: The tree view of folders which contain content.
- L81 _public prototype_ `DECLARE_DELEGATE( FOnFrontendPluginFilterChanged );` — Delegate for when plugin filters have changed
- L83 _public function_ `SLATE_BEGIN_ARGS( SPathView ) : _bEnableShadowBoxStyle(false) , _InitialCategoryFilter(EContentBrowserItemCategoryFilter::IncludeAll) , _FocusSearchBoxWhenOpened(true) , _ShowTreeTitle(false) , _SearchBarVisibility(EVisibility::Visible) , _ShowSeparator(true) , _AllowContextMenu(true) , _AllowClassesFolder(false) , _AllowReadOnlyFolders(true) , _ShowFavorites(false) , _CanShowDevelopersFolder(false) , _ForceShowEngineContent(false) , _ForceShowPluginContent(false) , _ShowViewOptions(false) , _SelectionMode( ESelectionMode::Multi )`
- L102 _public prototype_ `SLATE_NAMED_SLOT( FArguments, SearchContent ) SLATE_ARGUMENT(const FScrollBoxStyle*, ShadowBoxStyle) SLATE_ARGUMENT(bool, bEnableShadowBoxStyle) SLATE_EVENT( FOnContentBrowserItemSelectionChanged, OnItemSelectionChanged ) SLATE_EVENT( FOnGetContentBrowserItemContextMenu, OnGetItemContextMenu ) SLATE_ARGUMENT( EContentBrowserItemCategoryFilter, InitialCategoryFilter ) SLATE_ARGUMENT( bool, FocusSearchBoxWhenOpened ) SLATE_ARGUMENT( bool, ShowTreeTitle ) SLATE_ATTRIBUTE( EVisibility, SearchBarVisibility ) SLATE_ARGUMENT( bool, ShowSeparator ) SLATE_ARGUMENT( bool, AllowContextMenu ) SLATE_ARGUMENT( bool, AllowClassesFolder ) SLATE_ARGUMENT( bool, AllowReadOnlyFolders ) SLATE_ARGUMENT(bool, ShowFavorites);` — Content displayed to the left of the search bar
- L144 _public prototype_ `SLATE_ARGUMENT(bool, CanShowDevelopersFolder) SLATE_ARGUMENT(bool, ForceShowEngineContent) SLATE_ARGUMENT(bool, ForceShowPluginContent) SLATE_ARGUMENT(bool, ShowViewOptions) SLATE_ATTRIBUTE(bool, ShowRedirectors);` — Indicates if the 'Show Developers' option should be enabled or disabled
- L159 _public prototype_ `SLATE_ARGUMENT( ESelectionMode::Type, SelectionMode ) SLATE_ARGUMENT( TSharedPtr<FSourcesSearch>, ExternalSearch ) SLATE_ARGUMENT( TSharedPtr<FPathPermissionList>, CustomFolderPermissionList) SLATE_ARGUMENT( TSharedPtr<FPluginFilterCollectionType>, PluginPathFilters) SLATE_ARGUMENT( FName, OwningContentBrowserName ) SLATE_ARGUMENT(FString, DefaultPath) SLATE_ARGUMENT(bool, CreateDefaultPath) SLATE_END_ARGS() SPathView();` — The selection mode for the tree view
- L184 _public prototype_ `~SPathView();` — Destructor
- L187 _public prototype_ `virtual void Construct( const FArguments& InArgs );` — Constructs this widget with InArgs
- L190 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — Paint to poll attributes. This avoids the need for the widget to tick each frame
- L193 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — Process the Commands of the PathView
- L196 _public prototype_ `virtual bool IsEmpty() const;` — Returns true if there are no items being presented in this widget.
- L199 _public prototype_ `void SetSelectedPaths(const TArray<FName>& Paths);` — Selects the closest matches to the supplied paths in the tree. "/" delimited
- L202 _public prototype_ `void SetSelectedPaths(const TArray<FString>& Paths);` — Selects the closest matches to the supplied paths in the tree. "/" delimited
- L205 _public prototype_ `void ClearSelection();` — Clears selection of all paths
- L208 _public prototype_ `FString GetSelectedPath() const;` — Returns the first selected path in the tree view
- L211 _public prototype_ `TArray<FString> GetSelectedPaths() const;` — Returns all selected paths in the tree view
- L214 _public prototype_ `TArray<FContentBrowserItem> GetSelectedFolderItems() const;` — Returns all the folder items currently selected in the view
- L217 _public prototype_ `void NewFolderItemRequested(const FContentBrowserItemTemporaryContext& NewItemContext);` — Called when "new folder" is selected in the context menu
- L220 _public prototype_ `void RenameFolderItem(const FContentBrowserItem& InItem);` — Sets up an inline rename for the specified folder
- L230 _public prototype_ `void SyncToItems( TArrayView<const FContentBrowserItem> ItemsToSync, const bool bAllowImplicitSync = false );` — Selects the paths containing or corresponding to the specified items. @param ItemsToSync			- A list of items to sync the view to @param bAllowImplicitSync	- true to allow the view to sync to parent folders if they are already selected, false to force the view to select the explicit Parent folders of each asset
- L233 _public prototype_ `void ApplyHistoryData( const FHistoryData& History );` — Sets the state of the path view to the one described by the history data
- L236 _public prototype_ `virtual void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& InstanceName) const;` — Saves any settings to config that should be persistent between editor sessions
- L239 _public prototype_ `virtual void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& InstanceName);` — Loads any settings to config that should be persistent between editor sessions
- L247 _public prototype_ `bool InternalPathPassesBlockLists(const FStringView InInternalPath, const int32 InAlreadyCheckedDepth = 0) const;` — Return true if passes path block lists @param InInternalPath			- Internal Path (e.g. /Game) @param InAlreadyCheckedDepth	- Folder depth that has already been checked, 0 if no parts of path already checked
- L253 _public prototype_ `bool DisablePluginPathFiltersThatHideItems(TConstArrayView<FContentBrowserItem> Items);` — Disable any filters which would prevent us from syncing to the given items in the content browser. Returns true if any filtering changed.
- L258 _public prototype_ `void RequestPopulation(FSimpleMulticastDelegate::FDelegate&& AfterPopulation = FSimpleMulticastDelegate::FDelegate());` — Request a population of the path view the next time the widget is ticked.
- L264 _public prototype_ `virtual void Populate(const bool bIsRefreshingFilter = false);` — Populates the tree with all folders that are not filtered out Note: This can be very long in large project. prefer calling request population to avoid multiple population in one frame.
- L267 _public function_ `void SetTreeTitle(FText InTitle)` — Sets an alternate tree title
- L272 _public function_ `FText GetTreeTitle() const`
- L277 _public prototype_ `void PopulatePathViewFiltersMenu(UToolMenu* Menu);`
- L280 _public prototype_ `TArray<FName> GetDefaultPathsToSelect() const;` — Get paths to select by default
- L283 _public prototype_ `TArray<FName> GetRootPathItemNames() const;` — Get list of root path item names
- L286 _public prototype_ `EContentBrowserItemCategoryFilter GetContentBrowserItemCategoryFilter() const;` — Get current item category filter enum
- L289 _public prototype_ `EContentBrowserItemAttributeFilter GetContentBrowserItemAttributeFilter() const;` — Get current item attribute filter enum
- L292 _public prototype_ `virtual FVector2D GetScrollDistance() override;`
- L293 _public prototype_ `virtual FVector2D GetScrollDistanceRemaining() override;`
- L294 _public prototype_ `virtual TSharedRef<SWidget> GetScrollWidget() override;`
- L299 _protected prototype_ `void RecursiveExpandParents(const TSharedPtr<FTreeItem>& Item);` — Expands all parents of the specified item
- L302 _protected prototype_ `virtual void HandleItemDataUpdated(TArrayView<const FContentBrowserItemDataUpdate> InUpdatedItems);` — Handles updating the view when content items are changed
- L305 _protected prototype_ `void HandleItemDataRefreshed();` — Handles updating the view when content items are refreshed
- L308 _protected prototype_ `virtual TSharedRef<ITableRow> GenerateTreeRow(TSharedPtr<FTreeItem> TreeItem, const TSharedRef<STableViewBase>& OwnerTable);` — Creates a list item for the tree view
- L311 _protected prototype_ `void TreeItemScrolledIntoView(TSharedPtr<FTreeItem> TreeItem, const TSharedPtr<ITableRow>& Widget);` — Handles focusing a folder widget after it has been created with the intent to rename
- L314 _protected prototype_ `void TreeSelectionChanged(TSharedPtr< FTreeItem > TreeItem, ESelectInfo::Type SelectInfo);` — Handler for tree view selection changes
- L317 _protected prototype_ `TSharedPtr<SWidget> MakePathViewContextMenu();` — Gets the content for a context menu
- L320 _protected prototype_ `void GetChildrenForTree(TSharedPtr< FTreeItem > TreeItem, TArray< TSharedPtr<FTreeItem> >& OutChildren);` — Handler for returning a list of children associated with a particular tree node
- L323 _protected prototype_ `void FolderNameChanged(const TSharedPtr< FTreeItem >& TreeItem, const FString& ProposedName, const UE::Slate::FDeprecateVector2DParameter& MessageLocation, const ETextCommit::Type CommitType);` — Handler for when a name was given to a new folder
- L326 _protected prototype_ `bool VerifyFolderNameChanged(const TSharedPtr< FTreeItem >& TreeItem, const FString& ProposedName, FText& OutErrorMessage) const;` — Handler used to verify the name of a new folder
- L329 _protected prototype_ `void SetSearchFilterText(const FText& InSearchText, TArray<FText>& OutErrors);` — Set the active filter text
- L332 _protected prototype_ `FText GetHighlightText() const;` — Gets the string to highlight in tree items (used in folder searching)
- L335 _protected prototype_ `bool IsTreeItemSelected(TSharedPtr<FTreeItem> TreeItem) const;` — True if the specified item is selected in the asset tree
- L338 _protected prototype_ `FReply OnFolderDragDetected(const FGeometry& Geometry, const FPointerEvent& MouseEvent);` — Handler for tree view folders are dragged
- L340 _protected prototype_ `FContentBrowserDataCompiledFilter CreateCompiledFolderFilter() const;`
- L343 _protected prototype_ `FPathViewConfig* GetPathViewConfig() const;` — Get this path view's editor config if OwningContentBrowserName is set.
- L346 _protected prototype_ `FContentBrowserInstanceConfig* GetContentBrowserConfig() const;` — Get this path view's content browser instance config if OwningContentBrowserName is set.
- L348 _protected prototype_ `virtual void ConfigureTreeView(STreeView<TSharedPtr<FTreeItem>>::FArguments& InArgs);`
- L351 _protected prototype_ `void SharedPostPopulate();` — Should be call after a populate
- L353 _protected function_ `constexpr virtual bool ShouldDoJustInTimePopulation() const`
- L360 _private prototype_ `bool ExplicitlyAddPathToSelection(const FName Path);` — Selects the given path only if it exists. Returns true if selected.
- L363 _private prototype_ `bool ShouldAllowTreeItemChangedDelegate() const;` — Returns true if the selection changed delegate should be allowed
- L366 _private prototype_ `void SetTreeItemExpansionRecursive( TSharedPtr< FTreeItem > TreeItem, bool bInExpansionState );` — Handler for recursively expanding/collapsing items in the tree view
- L369 _private prototype_ `void TreeExpansionChanged( TSharedPtr< FTreeItem > TreeItem, bool bIsExpanded );` — Handler for tree view expansion changes
- L372 _private prototype_ `void FilterUpdated();` — Handler for when the search box filter has changed
- L375 _private prototype_ `bool FolderAlreadyExists(const TSharedPtr< FTreeItem >& TreeItem, TSharedPtr< FTreeItem >& ExistingItem);` — Returns true if the supplied folder item already exists in the tree. If so, ExistingItem will be set to the found item.
- L378 _private prototype_ `bool IsTreeItemExpanded(TSharedPtr<FTreeItem> TreeItem) const;` — True if the specified item is expanded in the asset tree
- L381 _private prototype_ `void HandleSettingChanged(FName PropertyName);` — Delegate called when an editor setting is changed
- L384 _private prototype_ `void PostPopulateHandleSettingChanged(bool bHadSelectedPath);` — Handle the logic that is done after population when requested by a setting change
- L387 _private prototype_ `void PostInitialPopulation();` — Handle the logic that is done after the initial population of the view
- L390 _private prototype_ `bool IsPopulationRequested() const;` — Is the view waiting for a population of its tree
- L393 _private prototype_ `EActiveTimerReturnType SetFocusPostConstruct(double InCurrentTime, float InDeltaTime);` — One-off active timer to focus the widget post-construct
- L396 _private prototype_ `void SetPluginPathFilterActive(const TSharedRef<FContentBrowserPluginFilter>& Filter, bool bActive);` — Sets the active state of a filter.
- L399 _private prototype_ `void ResetPluginPathFilters();` — Unchecks all plugin filters.
- L402 _private prototype_ `void PluginPathFilterClicked(TSharedRef<FContentBrowserPluginFilter> Filter);` — Toggle plugin filter.
- L405 _private prototype_ `bool IsPluginPathFilterChecked(TSharedRef<FContentBrowserPluginFilter> Filter) const;` — Return whether the given filter should be shown enabled in the UI.
- L411 _private prototype_ `bool IsPluginPathFilterInUse(TSharedRef<FContentBrowserPluginFilter> Filter) const;` — Returns true if filter is being used. Note that because some filters are 'inverse' this is not the same as whether the filter should be visibly checked in the UI to be shown as 'enabled' to the user.
- L413 _private prototype_ `TArray<FName> GetDefaultPathsToExpand() const;`
- L416 _private prototype_ `void DirtyLastExpandedPaths();` — Tell the tree that the LastExpandedPath set should be refreshed
- L419 _private prototype_ `void UpdateLastExpandedPathsIfDirty();` — Update the LastExpandedPath if required
- L422 _private prototype_ `TSharedRef<SWidget> CreateFavoritesView();` — Create a favorites view.
- L425 _private prototype_ `static void RegisterGetViewButtonMenu();` — Register menu for when the view combo button is clicked
- L428 _private prototype_ `void PopulateFilterAdditionalParams(FFiltersAdditionalParams& OutParams);` — Populate the given params for this PathView
- L431 _private prototype_ `bool IsToggleShowCppContentAllowed() const;` — Whether or not it's possible to show C++ content
- L434 _private prototype_ `bool IsToggleShowDevelopersContentAllowed() const;` — Whether or not it's possible to toggle developers content
- L437 _private prototype_ `bool IsToggleShowEngineContentAllowed() const;` — Whether or not it's possible to toggle engine content
- L440 _private prototype_ `bool IsToggleShowPluginContentAllowed() const;` — Whether or not it's possible to toggle plugin content
- L443 _private prototype_ `bool IsToggleShowLocalizedContentAllowed() const;` — Whether or not it's possible to show localized content
- L446 _private prototype_ `TSharedRef<SWidget> GetViewButtonContent();` — Handler for when the view combo button is clicked
- L449 _private prototype_ `void CopySelectedFolder() const;` — Callback for the Copy command for the PathView
- L452 _private prototype_ `void BindCommands();` — Bind our UI commands
- L493 _protected member_ `TSharedPtr< STreeView< TSharedPtr<FTreeItem>> > TreeViewPtr;` — The tree view widget
- L496 _protected member_ `TSharedPtr<FSourcesSearch> SearchPtr;` — The path view search interface
- L499 _protected member_ `TSharedPtr<FPathViewData> TreeData;` — Items in the tree and associated data. Shared ptr for easy binding to delegates/attributes
- L502 _protected member_ `bool bFlat = false;` — Should this path tree be flat like the favorites tree
- L505 _protected member_ `TSet<FName> LastSelectedPaths;` — The paths that were last reported by OnPathSelected event. Used in preserving selection when filtering folders
- L511 _protected member_ `TArray<FName> PendingInitialPaths;` — If not empty, this is the path of the folders to sync once they are available while assets are still being discovered. It should be emptied when user interaction overides the default selections.
- L514 _protected member_ `FContentBrowserItemTemporaryContext PendingNewFolderContext;` — Context information for the folder item that is currently being created, if any
- L516 _protected member_ `TSharedPtr<SWidget> PathViewWidget;`
- L519 _protected member_ `TSharedPtr<FPathPermissionList> FolderPermissionList;` — Permission filter to hide folders
- L522 _protected member_ `TSharedPtr<FPathPermissionList> WritableFolderPermissionList;` — Writable folder filter
- L525 _protected member_ `TSharedPtr<FPathPermissionList> CustomFolderPermissionList;` — Custom Folder permissions
- L528 _protected member_ `FName OwningContentBrowserName;` — The config instance to use.
- L531 _protected member_ `FSimpleMulticastDelegate OnNextPopulate;` — Event(s) called to run any queued logic after a population of the widget
- L534 _private member_ `TSlateAttribute<bool> bShowRedirectorsAttribute;`
- L536 _private member_ `TSlateAttribute<uint64> TreeDataVersionAttribute;` — Last version number retrieved from TreeData so we can decide if the tree view need rebuilding
- L539 _private member_ `bool bLastExpandedPathsDirty = false;` — Used to track if the list of last expanded path should be updated
- L542 _private member_ `TSet<FName> LastExpandedPaths;` — The paths that were last reported by OnPathExpanded event. Used in preserving expansion when filtering folders
- L545 _private member_ `FOnContentBrowserItemSelectionChanged OnItemSelectionChanged;` — Delegate to invoke when selection changes.
- L548 _private member_ `FOnGetContentBrowserItemContextMenu OnGetItemContextMenu;` — Delegate to invoke when generating the context menu for an item
- L551 _private member_ `int32 PreventTreeItemChangedDelegateCount = 0;` — If > 0, the selection or expansion changed delegate will not be called. Used to update the tree from an external source or in certain bulk operations.
- L554 _private member_ `EContentBrowserItemCategoryFilter InitialCategoryFilter = EContentBrowserItemCategoryFilter::IncludeAll;` — Initial set of item categories that this view should show - may be adjusted further by things like AllowClassesFolder
- L557 _private member_ `bool bAllowContextMenu : 1;` — If false, the context menu will not open when right clicking an item in the tree
- L560 _private member_ `bool bAllowClassesFolder : 1;` — If false, the classes folder will not be added to the tree automatically
- L563 _private member_ `bool bAllowReadOnlyFolders : 1;` — If true, read only folders will be displayed
- L566 _private member_ `bool bCanShowDevelopersFolder : 1;` — Indicates if the 'Show Developers' option should be enabled or disabled
- L569 _private member_ `bool bForceShowEngineContent : 1;` — If true, engine content is always shown
- L572 _private member_ `bool bForceShowPluginContent : 1;` — If true, plugin content is always shown
- L575 _private member_ `TSlateAttribute<bool> bPopulationRequestedAttribute;` — Request a population of the path view
- L578 _private member_ `TSlateAttribute<bool> bInitialPopulationRequestedAttribute;` — Request the initial population of the path view
- L581 _private member_ `TSlateAttribute<bool> bPopulationForSettingChangeRequestedAttribute;` — Request a population of the path view but because of a setting change
- L583 _private member_ `bool bCreateDefaultPath : 1;`
- L584 _private member_ `FString DefaultPath;`
- L587 _private member_ `FText TreeTitle;` — The title of this path view
- L590 _private member_ `TSharedPtr<FUICommandList> Commands;` — Commands handled by this widget
- L593 _private member_ `TSharedPtr<FPluginFilterCollectionType> PluginPathFilters;` — The filter collection used to filter plugins
- L596 _private member_ `TArray< TSharedRef<FContentBrowserPluginFilter> > AllPluginPathFilters;` — Plugins filters that are currently active
- L599 _private member_ `TSharedPtr<SExpandableArea> FavoritesArea;` — The favorites path view if one is set.

#### class `SPathView::FScopedPreventTreeItemChangedDelegate`  
`class FScopedPreventTreeItemChangedDelegate`  
_L456-473_
- desc: A helper class to manage PreventTreeItemChangedDelegateCount by incrementing it when constructed (on the stack) and decrementing when destroyed
- L459 _public function_ `FScopedPreventTreeItemChangedDelegate(const TSharedRef<SPathView>& InPathView) : PathView(InPathView)`
- L465 _public function_ `~FScopedPreventTreeItemChangedDelegate()`
- L472 _private member_ `TSharedRef<SPathView> PathView;`

#### class `SPathView::FScopedSelectionChangedEvent`  
`class FScopedSelectionChangedEvent`  
_L476-490_
- desc: A helper class to scope a selection change notification so that it only emits if the selection has actually changed after the scope ends
- L479 _public prototype_ `FScopedSelectionChangedEvent(const TSharedRef<SPathView>& InPathView, const bool InShouldEmitEvent = true);`
- L480 _public prototype_ `~FScopedSelectionChangedEvent();`
- L482 _public prototype_ `bool IsInitialSelectionEmpty() const;`
- L485 _private prototype_ `TSet<FName> GetSelectionSet() const;`
- L487 _private member_ `TSharedRef<SPathView> PathView;`
- L488 _private member_ `TSet<FName> InitialSelectionSet;`
- L489 _private member_ `bool bShouldEmitEvent = true;`

#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<class SFavoriteAssetTreeItem>`  
_L603-606_
- L67 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SFavoriteAssetTreeItem`  
`class SFavoriteAssetTreeItem : public SAssetTreeItem`  
_L609-639_
- inherits: `SAssetTreeItem`
- desc: AssetTreeItem for the Favorite view to override some behavior
- L611 _private function_ `SLATE_BEGIN_ARGS(SFavoriteAssetTreeItem)`
- L612 _private prototype_ `SLATE_ARGUMENT(SAssetTreeItem::FArguments, Parent) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L619 _protected prototype_ `virtual FText GetNameText() const override;`
- L620 _protected prototype_ `virtual FText GetToolTipText() const override;`
- L624 _protected prototype_ `virtual void OnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L625 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& InDragDropEvent) override;`
- L626 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L627 _protected prototype_ `virtual FReply OnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L630 _protected prototype_ `void OnFavoriteUpdated(const FContentBrowserItemPath& InItemPath, bool bInAdded);`
- L631 _protected prototype_ `void UpdateItem(const FContentBrowserItemPath& InPath);`
- L635 _private prototype_ `static TSharedPtr<FContentBrowserDataDragDropOp> GetFavoriteMoveOperation(const FDragDropEvent& InDragDropEvent);` — Retrieves only drag operation that favorites view will handle
- L637 _private member_ `FText Alias;`
- L638 _private member_ `FText Shortcut;`

#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<class SFavoritePathView>`  
_L642-645_
- L67 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SFavoritePathView`  
`class SFavoritePathView : public SPathView`  
_L650-709_
- inherits: `SPathView`
- desc: The tree view of folders which contain favorited folders.
- L653 _public prototype_ `SFavoritePathView();`
- L657 _public prototype_ `virtual void Construct(const FArguments& InArgs) override;` — Constructs this widget with InArgs
- L659 _public prototype_ `virtual void Populate(const bool bIsRefreshingFilter = false) override;`
- L662 _public prototype_ `virtual void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) override;` — Loads any settings to config that should be persistent between editor sessions
- L665 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — Validate that the drop operation is valid for the favorites. Accept FAssetDragDropOp objects with folders only.
- L668 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;` — Restore any cursor overrides, in case once was set for invalid drop in OnDragEnter.
- L671 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — Detect if a folder was dropped in the favorites view and add that folder (or folders) to favorites
- L674 _public prototype_ `void FixupFavoritesFromExternalChange(TArrayView<const AssetViewUtils::FMovedContentFolder> MovedFolders);` — Updates favorites based on an external change.
- L676 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnFolderFavoriteUpdated, const TArray<FString>& , const FString& , EItemDropZone ) void SetOnFolderFavoriteUpdated(const FOnFolderFavoriteUpdated& InOnFolderFavoriteUpdated);`
- L680 _protected function_ `constexpr virtual bool ShouldDoJustInTimePopulation() const override`
- L686 _private prototype_ `virtual TSharedRef<ITableRow> GenerateTreeRow(TSharedPtr<FTreeItem> TreeItem, const TSharedRef<STableViewBase>& OwnerTable) override;`
- L689 _private prototype_ `TOptional<EItemDropZone> OnFolderCanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InItemDropZone, TSharedPtr<FTreeItem> InTreeItem);` — Handler for tree view to accept drop
- L692 _private prototype_ `FReply OnFolderAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InItemDropZone, TSharedPtr<FTreeItem> InTreeItem);` — Handler for tree view when dropping items
- L694 _private prototype_ `void OnFavoriteAdded(const FContentBrowserItemPath& ChangedItem, bool bAdded);`
- L697 _private prototype_ `virtual void HandleItemDataUpdated(TArrayView<const FContentBrowserItemDataUpdate> InUpdatedItems) override;` — Handles updating the view when content items are changed
- L699 _private prototype_ `virtual void ConfigureTreeView(STreeView<TSharedPtr<FTreeItem>>::FArguments& InArgs) override;`
- L702 _private prototype_ `TSharedPtr<FContentBrowserDataDragDropOp> GetContentBrowserDragDropOpFromEvent(const FDragDropEvent& DragDropEvent) const;` — Returns an FContentBrowserDataDragDropOp object but only if it qualifies as a proper droppable content browser drag drop op
- L704 _private member_ `TArray<FString> RemovedByFolderMove;`
- L705 _private member_ `FDelegateHandle OnFavoritesChangedHandle;`
- L707 _private member_ `FOnFolderFavoriteUpdated OnFolderFavoriteUpdated;`
- L708 _private member_ `bool bIsLoadingSettings = false;`

#### Free symbols / members of external scopes

- L81 _delegate_ `DECLARE_DELEGATE( FOnFrontendPluginFilterChanged );` — Delegate for when plugin filters have changed
- L676 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnFolderFavoriteUpdated, const TArray<FString>& , const FString& , EItemDropZone ) void SetOnFolderFavoriteUpdated(const FOnFolderFavoriteUpdated& InOnFolderFavoriteUpdated);`

### `Source/Editor/ContentBrowser/Private/SRenameWindow.h` (Private)


#### class `SRenameWindow`  
`class SRenameWindow : public SWindow`  
_L13-42_
- inherits: `SWindow`
- desc: floating Rename Window
- L15 _private function_ `SLATE_BEGIN_ARGS(SRenameWindow) : _ScreenPosition(FVector2D(0.f, 0.f)) , _OnTextCommitted() , _OnVerifyTextChanged() , _OnBeginTextEdit() , _InitialText()`
- L23 _private prototype_ `SLATE_ARGUMENT(UE::Slate::FDeprecateVector2DParameter, ScreenPosition) SLATE_EVENT(FOnTextCommitted, OnTextCommitted) SLATE_EVENT(FOnVerifyTextChanged, OnVerifyTextChanged) SLATE_EVENT(FOnBeginTextEdit, OnBeginTextEdit) SLATE_ARGUMENT(FText, InitialText) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L38 _private prototype_ `void DeactivateWindow();`
- L41 _private member_ `TSharedPtr<SRenameEditableTextBox> RenameEditableTextBox;`

### `Source/Editor/ContentBrowser/Private/SThumbnailEditModeTools.h` (Private)


#### class `SThumbnailEditModeTools`  
`class SThumbnailEditModeTools : public SCompoundWidget`  
_L24-75_
- inherits: `SCompoundWidget`
- L27 _public function_ `SLATE_BEGIN_ARGS(SThumbnailEditModeTools) : _SmallView(false)`
- L31 _public prototype_ `SLATE_ARGUMENT( bool, SmallView ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedPtr<FAssetThumbnail>& InAssetThumbnail );`
- L39 _public prototype_ `FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;` — SWidget Interface
- L40 _public prototype_ `FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L41 _public prototype_ `FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L42 _public prototype_ `FCursorReply OnCursorQuery( const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override;`
- L46 _protected prototype_ `EVisibility GetPrimitiveToolsVisibility() const;` — Gets the visibility for the primitives toolbar
- L49 _protected prototype_ `EVisibility GetPrimitiveToolsResetToDefaultVisibility() const;` — Gets the visibility for the the thumbnail reset to default button
- L52 _protected prototype_ `const FSlateBrush* GetCurrentPrimitiveBrush() const;` — Gets the brush used to display the currently used primitive
- L55 _protected prototype_ `FReply ChangePrimitive();` — Sets the primitive type for the supplied thumbnail, if possible
- L58 _protected prototype_ `FReply ResetToDefault();` — Resets the primitive to default
- L61 _protected prototype_ `USceneThumbnailInfo* GetSceneThumbnailInfo() const;` — Helper accessors for ThumbnailInfo objects
- L62 _protected prototype_ `USceneThumbnailInfoWithPrimitive* GetSceneThumbnailInfoWithPrimitive() const;`
- L64 _protected prototype_ `EThumbnailPrimType GetDefaultThumbnailType() const;`
- L67 _protected member_ `bool bInSmallView;`
- L68 _protected member_ `bool bModifiedThumbnailWhileDragging;`
- L69 _protected member_ `FIntPoint DragStartLocation;`
- L70 _protected member_ `TWeakPtr<FAssetThumbnail> AssetThumbnail;`
- L74 _private member_ `mutable TWeakObjectPtr<USceneThumbnailInfo> SceneThumbnailInfoPtr;` — Never access this directly.

### `Source/Editor/ContentBrowser/Private/SourcesSearch.h` (Private)


#### class `FSourcesSearch`  
`class FSourcesSearch : public TSharedFromThis<FSourcesSearch>`  
_L15-49_
- inherits: `TSharedFromThis<FSourcesSearch>`
- desc: Implementation for a sources search, used by the path and collections views
- L19 _public prototype_ `void Initialize();` — Initialize the search widget
- L22 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSearchChanged, const FText& , TArray<FText>& );` — Delegate invoked when the search text is changed
- L23 _public function_ `FOnSearchChanged& OnSearchChanged()`
- L29 _public prototype_ `void ClearSearch();` — Clear the current search text
- L32 _public prototype_ `void SetHintText(const TAttribute<FText>& InHintText);` — Set the active hint text for the underlying search widget
- L35 _public prototype_ `TSharedRef<SSearchBox> GetWidget() const;` — Get the underlying search widget
- L39 _private prototype_ `void OnSearchBoxTextChanged(const FText& InSearchText);` — Handler for when search term changes
- L42 _private prototype_ `void OnSearchBoxTextCommitted(const FText& InSearchText, ETextCommit::Type InCommitType);` — Handler for when search term is committed
- L45 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — Underlying search widget
- L48 _private member_ `FOnSearchChanged OnSearchChangedDelegate;` — Delegate invoked when the search text is changed

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSearchChanged, const FText& , TArray<FText>& );` — Delegate invoked when the search text is changed

### `Source/Editor/ContentBrowser/Private/SourcesViewWidgets.h` (Private)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SAssetTreeItem>`  
_L36-39_
- L38 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SAssetTreeItem`  
`class SAssetTreeItem : public SCompoundWidget`  
_L42-143_
- inherits: `SCompoundWidget`
- desc: A single item in the asset tree. Represents a folder.
- L45 _public prototype_ `DECLARE_DELEGATE_FourParams( FOnNameChanged, const TSharedPtr<FTreeItem>& , const FString& , const UE::Slate::FDeprecateVector2DParameter& , const ETextCommit::Type );`
- L46 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams( bool, FOnVerifyNameChanged, const TSharedPtr<FTreeItem>& , const FString& , FText& );`
- L48 _public function_ `SLATE_BEGIN_ARGS( SAssetTreeItem ) : _TreeItem( TSharedPtr<FTreeItem>() ) , _IsItemExpanded( false )`
- L54 _public prototype_ `SLATE_ARGUMENT( TSharedPtr<FTreeItem>, TreeItem ) SLATE_EVENT( FOnNameChanged, OnNameChanged ) SLATE_EVENT( FOnVerifyNameChanged, OnVerifyNameChanged ) SLATE_ATTRIBUTE( bool, IsItemExpanded ) SLATE_ATTRIBUTE( FText, HighlightText) SLATE_ATTRIBUTE( FSlateFontInfo, FontOverride) SLATE_EVENT( FIsSelected, IsSelected ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — Data for the folder this item represents
- L80 _public prototype_ `virtual void OnDragEnter( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L81 _public prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;`
- L82 _public prototype_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L83 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L88 _protected prototype_ `virtual FText GetNameText() const;` — Returns the text of the folder name
- L91 _protected prototype_ `bool VerifyNameChanged(const FText& InName, FText& OutError) const;` — Handles verifying name changes
- L94 _protected prototype_ `void HandleNameCommitted( const FText& NewText, ETextCommit::Type );` — Handles committing a name change
- L97 _protected prototype_ `bool IsReadOnly() const;` — Returns false if this folder is in the process of being created
- L100 _protected prototype_ `const FSlateBrush* GetFolderIcon() const;` — Gets the brush used to draw the folder icon
- L103 _protected prototype_ `FSlateColor GetFolderColor() const;` — Gets the color used to draw the folder icon
- L106 _protected prototype_ `virtual FText GetToolTipText() const;` — Returns the text to use for the folder tooltip
- L109 _protected prototype_ `const FSlateBrush* GetBorderImage() const;` — Returns the image for the border around this item. Used for drag/drop operations
- L112 _protected prototype_ `TSharedRef<SWidget> GenerateStateIcons();` — Returns a widget that combines the results of calling all registered PathViewStateIconGenerators
- L115 _protected member_ `TWeakPtr<FTreeItem> TreeItem;` — The data for this item
- L118 _protected member_ `TSharedPtr<SEditableTextBox> EditableName;` — The name of the asset as an editable text box
- L121 _protected member_ `FOnNameChanged OnNameChanged;` — Delegate for when the user commits a new name to the folder
- L124 _protected member_ `FOnVerifyNameChanged OnVerifyNameChanged;` — Delegate for when a user is typing a name for the folder
- L127 _protected member_ `TAttribute<bool> IsItemExpanded;` — True when this item has children and is expanded
- L130 _protected member_ `FIsSelected IsSelected;` — Delegate called to get the selection state of an asset path
- L133 _protected member_ `bool bDraggedOver;` — True when a drag is over this item with a drag operation that we know how to handle. The operation itself may not be valid to drop.
- L136 _protected member_ `EFolderType FolderType;` — What type of stuff does this folder hold
- L139 _protected member_ `TSharedPtr<SInlineEditableTextBlock> InlineRenameWidget;` — Widget to display the name of the asset item and allows for renaming
- L142 _protected member_ `FDelegateHandle EnterEditingModeDelegateHandle;` — Handle to the registered EnterEditingMode delegate.

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SCollectionTreeItem>`  
_L146-149_
- L38 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SCollectionTreeItem`  
`class SCollectionTreeItem : public SCompoundWidget`  
_L152-283_
- inherits: `SCompoundWidget`
- desc: A single item in the collection tree.
- L156 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnBeginNameChange, const TSharedPtr<FCollectionItem>& );` — Delegates for when a collection is renamed. If returning false, OutWarningMessage will be displayed over the collection.
- L157 _public prototype_ `DECLARE_DELEGATE_RetVal_FourParams( bool, FOnNameChangeCommit, const TSharedPtr<FCollectionItem>& , const FString& , bool , FText& );`
- L158 _public prototype_ `DECLARE_DELEGATE_RetVal_FourParams( bool, FOnVerifyRenameCommit, const TSharedPtr<FCollectionItem>& , const FString& , const FSlateRect& , FText& ) DECLARE_DELEGATE_RetVal_FourParams( bool, FOnValidateDragDrop, TSharedRef<FCollectionItem> , const FGeometry& , const FDragDropEvent& , bool& );`
- L162 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams( FReply, FOnHandleDragDrop, TSharedRef<FCollectionItem> , const FGeometry& , const FDragDropEvent& );`
- L164 _public function_ `SLATE_BEGIN_ARGS( SCollectionTreeItem ) : _CollectionItem( TSharedPtr<FCollectionItem>() ) , _ParentWidget()`
- L170 _public prototype_ `SLATE_ARGUMENT( TSharedPtr<FCollectionItem>, CollectionItem ) SLATE_ARGUMENT( TSharedPtr<SWidget>, ParentWidget ) SLATE_EVENT( FOnBeginNameChange, OnBeginNameChange ) SLATE_EVENT( FOnNameChangeCommit, OnNameChangeCommit ) SLATE_EVENT( FOnVerifyRenameCommit, OnVerifyRenameCommit ) SLATE_EVENT( FOnValidateDragDrop, OnValidateDragDrop ) SLATE_EVENT( FOnHandleDragDrop, OnHandleDragDrop ) SLATE_EVENT( FIsSelected, IsSelected ) SLATE_ATTRIBUTE( bool, IsReadOnly ) SLATE_ATTRIBUTE( FText, HighlightText ) SLATE_ATTRIBUTE( bool, IsCheckBoxEnabled ) SLATE_ATTRIBUTE( ECheckBoxState, IsCollectionChecked ) SLATE_EVENT( FOnCheckStateChanged, OnCollectionCheckStateChanged ) SLATE_END_ARGS()` — Data for the collection this item represents
- L213 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L214 _public prototype_ `virtual void OnDragEnter( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L215 _public prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;`
- L216 _public prototype_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L217 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L220 _public function_ `bool IsDraggedOver() const` — True when a drag is over this item with a drag operation that we know how to handle. The operation itself may not be valid to drop.
- L227 _private prototype_ `bool ValidateDragDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent, bool& OutIsKnownDragOperation ) const;` — Used by OnDragEnter, OnDragOver, and OnDrop to check and update the validity of the drag operation
- L230 _private prototype_ `void HandleBeginNameChange( const FText& OldText );` — Handles beginning a name change
- L233 _private prototype_ `void HandleNameCommitted( const FText& NewText, ETextCommit::Type CommitInfo );` — Handles committing a name change
- L236 _private prototype_ `bool HandleVerifyNameChanged( const FText& NewText, FText& OutErrorMessage );` — Handles verifying a name change
- L239 _private prototype_ `FText GetNameText() const;` — Returns the text of the collection name
- L242 _private prototype_ `FLinearColor GetCollectionColor() const;` — Returns the color of the collection name
- L245 _private prototype_ `FText GetCollectionObjectCountText() const;` — Get the object count text for the current collection item
- L248 _private prototype_ `FText GetCollectionWarningText() const;` — Get the warning message for the current collection item
- L251 _private prototype_ `void BuildToolTipInfo(const FOnBuildAssetTagItemToolTipInfoEntry& InCallback) const;` — Build the tooltip info for this collection
- L255 _private member_ `TWeakPtr<SWidget> ParentWidget;` — A weak pointer to the parent widget.
- L258 _private member_ `TWeakPtr<FCollectionItem> CollectionItem;` — The data for this item
- L261 _private member_ `TSharedPtr<SEditableTextBox> EditableName;` — The name of the asset as an editable text box
- L264 _private member_ `bool bDraggedOver;` — True when a drag is over this item with a drag operation that we know how to handle. The operation itself may not be valid to drop.
- L267 _private member_ `FOnValidateDragDrop OnValidateDragDrop;` — Delegate to validate a drag drop operation on this collection item
- L270 _private member_ `FOnHandleDragDrop OnHandleDragDrop;` — Delegate to handle a drag drop operation on this collection item
- L273 _private member_ `FGeometry CachedGeometry;` — The geometry as of the last frame. Used to open warning messages over the item
- L276 _private member_ `FOnBeginNameChange OnBeginNameChange;` — Delegate for when the user starts to rename an item
- L279 _private member_ `FOnNameChangeCommit OnNameChangeCommit;` — Delegate for when the user commits a new name to the collection
- L282 _private member_ `FOnVerifyRenameCommit OnVerifyRenameCommit;` — Delegate for when a collection name has been entered for an item to verify the name before commit

#### Free symbols / members of external scopes

- L45 _delegate_ `DECLARE_DELEGATE_FourParams( FOnNameChanged, const TSharedPtr<FTreeItem>& , const FString& , const UE::Slate::FDeprecateVector2DParameter& , const ETextCommit::Type );`
- L46 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams( bool, FOnVerifyNameChanged, const TSharedPtr<FTreeItem>& , const FString& , FText& );`
- L156 _delegate_ `DECLARE_DELEGATE_OneParam( FOnBeginNameChange, const TSharedPtr<FCollectionItem>& );` — Delegates for when a collection is renamed. If returning false, OutWarningMessage will be displayed over the collection.
- L157 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams( bool, FOnNameChangeCommit, const TSharedPtr<FCollectionItem>& , const FString& , bool , FText& );`
- L158 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams( bool, FOnVerifyRenameCommit, const TSharedPtr<FCollectionItem>& , const FString& , const FSlateRect& , FText& ) DECLARE_DELEGATE_RetVal_FourParams( bool, FOnValidateDragDrop, TSharedRef<FCollectionItem> , const FGeometry& , const FDragDropEvent& , bool& );`
- L161 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams( bool, FOnValidateDragDrop, TSharedRef<FCollectionItem> , const FGeometry& , const FDragDropEvent& , bool& );` — Delegates for when a collection item has something dropped into it
- L162 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams( FReply, FOnHandleDragDrop, TSharedRef<FCollectionItem> , const FGeometry& , const FDragDropEvent& );`

### `Source/Editor/ContentBrowser/Private/TextFilterKeyValueHandlers.h` (Private)


#### struct `FTextFilterKeyValueHandlerEntry`  
`struct FTextFilterKeyValueHandlerEntry`  
_L20-31_
- reflection: `USTRUCT()`
- L25 _public member_ `FName Key;` — `UPROPERTY(config)`
- L29 _public member_ `TSoftClassPtr<UTextFilterKeyValueHandler> HandlerClass;` — `UPROPERTY(config)`

#### class `UTextFilterKeyValueHandlers`  
`UTextFilterKeyValueHandlers : public UObject`  
_L35-45_
- reflection: `UCLASS(transient, config = Editor)`
- reflection: `UE_DEPRECATED(5.5, "This type has been replaced by IAssetTextFilterHandler which must be manually instantiated and registered and must be implemented in a threadsafe way.")`
- inherits: `UObject`
- L41 _public member_ `TArray<FTextFilterKeyValueHandlerEntry> TextFilterKeyValueHandlers;` — `UPROPERTY(config)`
- L44 _public prototype_ `static bool HandleTextFilterKeyValue(const FContentBrowserItem& InContentBrowserItem, const FName& InKey, const FTextFilterString& InValue, const ETextFilterComparisonOperation InComparisonOperation, const ETextFilterTextComparisonMode InTextComparisonMode, bool& bOutIsMatch);`

### `Source/Editor/ContentBrowser/Private/TextFilterValueHandlers.h` (Private)


#### class `UTextFilterValueHandlers`  
`UTextFilterValueHandlers : public UObject`  
_L20-30_
- reflection: `UCLASS(transient, config = Editor)`
- reflection: `UE_DEPRECATED(5.5, "This type has been replaced by IAssetTextFilterHandler which must be manually instantiated and registered and must be implemented in a threadsafe way.")`
- inherits: `UObject`
- L26 _public member_ `TArray<TSoftClassPtr<UTextFilterValueHandler>> TextFilterValueHandlers;` — `UPROPERTY(config)`
- L29 _public prototype_ `static bool HandleTextFilterValue(const FContentBrowserItem& InContentBrowserItem, const FTextFilterString& InValue, const ETextFilterTextComparisonMode InTextComparisonMode, bool& bOutIsMatch);`

### `Source/Editor/ContentBrowser/Private/Widgets/ParentWidgetSwitcher.h` (Private)


#### class `UE::Editor::ContentBrowser::Private::FWidgetParentSwitcher`  
`class FWidgetParentSwitcher`  
_L13-59_
- desc: Takes a single widget and two or more containing widgets (SBox) to switch between, depending on a custom condition.
- L16 _public prototype_ `virtual ~FWidgetParentSwitcher() = default;`
- L18 _public function_ `FWidgetParentSwitcher( const TSharedPtr<SWidget>& InSubjectWidget, const TArray<TSharedPtr<SBox>>& InParentWidgets) : SubjectWidget(InSubjectWidget) , ParentWidgets(InParentWidgets)`
- L27 _public function_ `[[maybe_unused]] bool Update()` — Call to check and switch the widget's parent. Return true if switched.
- L46 _public function_ `TSharedPtr<SWidget> GetParentWidget() const`
- L53 _protected prototype_ `virtual int32 GetParentIndex() const = 0;`
- L56 _protected member_ `TSharedPtr<SWidget> SubjectWidget;`
- L57 _protected member_ `int32 CurrentSubjectWidgetParentIdx = 0;`
- L58 _protected member_ `TArray<TSharedPtr<SBox>> ParentWidgets;`

#### class `UE::Editor::ContentBrowser::Private::TWidgetSizeParentSwitcher`  
`template <EOrientation Orientation> class TWidgetSizeParentSwitcher : public FWidgetParentSwitcher`  
_L63-142_
- inherits: `FWidgetParentSwitcher`
- desc: Switches parent widgets based on widget size
- L67 _public prototype_ `virtual ~TWidgetSizeParentSwitcher() override = default;`
- L69 _public function_ `TWidgetSizeParentSwitcher( const TSharedPtr<SWidget>& InSubjectWidget, const TArray<TSharedPtr<SBox>>& InParentWidgets, const TArray<FInt16Range>& InSwitchSizeRanges, TUniqueFunction<float()>&& InSizeGetter) : FWidgetParentSwitcher(InSubjectWidget, InParentWidgets) , SwitchSizeRanges(InSwitchSizeRanges) , SizeGetter(MoveTemp(InSizeGetter))`
- L82 _protected function_ `virtual int32 GetParentIndex() const override`
- L140 _private member_ `TArray<FInt16Range> SwitchSizeRanges;`
- L141 _private member_ `TUniqueFunction<float()> SizeGetter;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)
- L10 _namespace_ `namespace Private` (scope `UE::Editor::ContentBrowser`)
- L89 _function_ `` (scope `UE::Editor::ContentBrowser::Private::TWidgetSizeParentSwitcher::GetParentIndex`)

### `Source/Editor/ContentBrowser/Private/Widgets/SContentBrowserFavoriteItem.h` (Private)


#### class `SContentBrowserFavoriteItem`  
`class SContentBrowserFavoriteItem : public SCompoundWidget`  
_L19-69_
- inherits: `SCompoundWidget`
- desc: Content browser favorite item dialog form to edit options
- L22 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnConfirmClicked, const FContentBrowserFavoriteItem& , bool );`
- L23 _public prototype_ `DECLARE_DELEGATE(FOnCancelClicked);`
- L25 _public function_ `SLATE_BEGIN_ARGS(SContentBrowserFavoriteItem)`
- L28 _public prototype_ `SLATE_ARGUMENT(TArray<TSharedPtr<FUICommandInfo>>, CommandOptions) SLATE_EVENT(FOnConfirmClicked, OnConfirm) SLATE_EVENT(FOnCancelClicked, OnCancel) SLATE_END_ARGS() static TSharedRef<SWindow> CreateAndShowWindow(const FArguments& InArguments, const FContentBrowserFavoriteItem& InItemToEdit);` — Commands to pick from for this item
- L38 _public prototype_ `void Construct(const FArguments& InArgs, const FContentBrowserFavoriteItem& InItemToEdit);`
- L41 _protected prototype_ `TSharedRef<SWidget> OnCommandGenerateWidget(TSharedPtr<FUICommandInfo> InCommand);`
- L42 _protected prototype_ `void OnCommandSelectionChanged(TSharedPtr<FUICommandInfo> InCommand, ESelectInfo::Type InSelectType);`
- L43 _protected prototype_ `FText GetItemCommandLabel() const;`
- L44 _protected prototype_ `FText GetCommandLabel(TSharedPtr<FUICommandInfo> InCommand) const;`
- L46 _protected prototype_ `FText GetAliasText() const;`
- L47 _protected prototype_ `void OnAliasTextChanged(const FText& InText);`
- L50 _protected prototype_ `FReply OnConfirmButtonClicked() const;` — Called when cancel button is clicked
- L53 _protected prototype_ `FReply OnCancelButtonClicked() const;` — Called when cancel button is clicked
- L55 _protected member_ `TArray<TSharedPtr<FUICommandInfo>> CommandOptions;`
- L56 _protected member_ `TSharedPtr<FUICommandInfo> SelectedCommand;`
- L58 _protected member_ `FOnConfirmClicked OnConfirmClicked;`
- L59 _protected member_ `FOnCancelClicked OnCancelClicked;`
- L62 _protected member_ `FContentBrowserFavoriteItem FavoriteItemEdited;` — Current item being edited
- L65 _protected member_ `TWeakPtr<SWindow> ParentWindowWeak;` — Self containing window
- L68 _protected member_ `bool bAnyChanges = false;` — Whether any changes have been done to this item

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnConfirmClicked, const FContentBrowserFavoriteItem& , bool );`
- L23 _delegate_ `DECLARE_DELEGATE(FOnCancelClicked);`

### `Source/Editor/ContentBrowser/Private/Widgets/SContentBrowserSourceTree.h` (Private)


#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<UE::Editor::ContentBrowser::Private::SContentBrowserSourceTree>`  
_L34-37_
- L36 _public function_ `static constexpr bool SupportsInvalidation()`

#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<UE::Editor::ContentBrowser::Private::SContentBrowserSourceTreeArea>`  
_L40-43_
- L36 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `UE::Editor::ContentBrowser::Private::SContentBrowserSourceTree`  
`class SContentBrowserSourceTree : public SCompoundWidget`  
_L49-153_
- inherits: `SCompoundWidget`
- desc: The Content Browser Source Tree, containing "Favorites", etc.
- L51 _private typedef_ `using Super = SCompoundWidget;`
- L92 _public prototype_ `static FSlot::FSlotArguments Slot();` — @return Add a new FSlot().
- L94 _public function_ `SLATE_BEGIN_ARGS(SContentBrowserSourceTree)`
- L96 _public function_ `SLATE_SLOT_ARGUMENT(FSlot, Slots) SLATE_END_ARGS() SContentBrowserSourceTree() : Slots(this) , TotalHeaderHeight(0.0f)`
- L108 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget with InArgs.
- L110 _public function_ `TSharedPtr<SSplitter> GetSplitter() const`
- L112 _public typedef_ `using FScopedWidgetSlotArguments = TPanelChildren<FSlot>::FScopedWidgetSlotArguments;`
- L114 _public prototype_ `FScopedWidgetSlotArguments AddSlot(const int32 InAtIndex = INDEX_NONE);`
- L121 _public prototype_ `int32 RemoveSlot(const TSharedRef<SWidget>& InSlotWidget);` — Removes a slot from this panel which contains the specified SWidget @param InSlotWidget The widget to match when searching through the slots @returns The index in the children array where the slot was removed and INDEX_NONE if no slot was found matching the widget
- L128 _public prototype_ `int32 RemoveSlotAt(int32 InIndex);` — Removes a slot from this panel at the specified slot index @param InIndex The index of the slot to remove @returns The index in the children array where the slot was removed and INDEX_NONE if there was no slot at that index
- L131 _public prototype_ `void ClearChildren();` — Removes all children from the panel.
- L134 _public prototype_ `int32 NumSlots() const;` — @return the number of slots.
- L137 _public prototype_ `bool IsValidSlotIndex(int32 InIndex) const;` — @return if it's a valid index slot index.
- L140 _private prototype_ `float GetMinHeight(TSharedPtr<SContentBrowserSourceTreeArea> InEntryWidget) const;`
- L141 _private prototype_ `float GetTotalHeaderHeight() const;`
- L142 _private prototype_ `SSplitter::ESizeRule GetExpandedSizeRule(TSharedPtr<SContentBrowserSourceTreeArea> InEntryWidget) const;`
- L143 _private prototype_ `float GetSlotSize(const int32 InSlotIdx) const;`
- L144 _private prototype_ `void OnSlotResized(float InNewSize, const int32 InSlotIdx);`
- L145 _private prototype_ `void UpdateTotalHeaderHeight();`
- L148 _private member_ `TSharedPtr<SSplitter> Splitter;`
- L149 _private member_ `TPanelChildren<FSlot> Slots;`
- L152 _private member_ `float TotalHeaderHeight;` — Cached total header height, recalculated one Slot Add/Remove.

#### class `UE::Editor::ContentBrowser::Private::SContentBrowserSourceTree::FSlot`  
`class FSlot : public TSlotBase<FSlot>`  
_L54-88_
- inherits: `TSlotBase<FSlot>`
- L57 _public prototype_ `SLATE_SLOT_BEGIN_ARGS(FSlot, TSlotBase<FSlot>) SLATE_ARGUMENT(TSharedPtr<SContentBrowserSourceTreeArea>, AreaWidget) SLATE_ARGUMENT(TOptional<float>, Size) SLATE_ARGUMENT(TOptional<SSplitter::ESizeRule>, ExpandedSizeRule) SLATE_ATTRIBUTE(EVisibility, Visibility) SLATE_ARGUMENT(TOptional<float>, HeaderHeight) SLATE_SLOT_END_ARGS() void Construct(const FChildren& SlotOwner, FSlotArguments&& InArgs);`
- L68 _public prototype_ `SSplitter::ESizeRule GetExpandedSizeRule() const;`
- L69 _public prototype_ `SSplitter::ESizeRule GetEmptyExpandedSizeRule() const;`
- L70 _public prototype_ `float GetMinHeight() const;`
- L71 _public prototype_ `float GetHeaderHeight() const;`
- L72 _public prototype_ `float GetInitialSlotSize() const;`
- L73 _public prototype_ `float GetSlotSize() const;`
- L74 _public prototype_ `TSharedPtr<SContentBrowserSourceTreeArea> GetEntryWidget() const;`
- L76 _public prototype_ `bool IsVisible() const;`
- L78 _public prototype_ `void OnSlotResized(float InNewSize);`
- L81 _private member_ `SSplitter::ESizeRule ExpandedSizeRule = SSplitter::ESizeRule::FractionOfParent;`
- L82 _private member_ `SSplitter::ESizeRule EmptyExpandedSizeRule = SSplitter::ESizeRule::FractionOfParent;`
- L83 _private member_ `float HeaderHeight = 36.0f;`
- L84 _private member_ `float InitialSlotSize = 0.0f;`
- L85 _private member_ `float SlotSize = 0.0f;` — The current slot height
- L86 _private member_ `TSharedPtr<SContentBrowserSourceTreeArea> EntryWidget = nullptr;`
- L87 _private member_ `TAttribute<EVisibility> EntryVisibility;`

#### class `UE::Editor::ContentBrowser::Private::SContentBrowserSourceTreeArea`  
`class SContentBrowserSourceTreeArea : public SCompoundWidget`  
_L156-241_
- inherits: `SCompoundWidget`
- desc: Represents a single item in the source tree view, ie. "Favorites".
- L158 _private typedef_ `using Super = SCompoundWidget;`
- L161 _public function_ `SLATE_BEGIN_ARGS(SContentBrowserSourceTreeArea) : _IsEmpty(false) , _bEnableShadowBoxStyle(false)`
- L166 _public prototype_ `SLATE_ATTRIBUTE(FText, Label) SLATE_NAMED_SLOT(FArguments, HeaderContent) SLATE_ATTRIBUTE(bool, IsEmpty) SLATE_ATTRIBUTE(FText, EmptyBodyLabel) SLATE_ARGUMENT(bool, ExpandedByDefault) SLATE_STYLE_ARGUMENT(FScrollBorderStyle, ShadowBoxStyle) SLATE_ARGUMENT(bool, bEnableShadowBoxStyle) SLATE_EVENT(FOnBooleanValueChanged, OnExpansionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FName InId, const TSharedPtr<FSourcesSearch>& InSearch, TSharedRef<IScrollableWidget> InBody);` — Label to display in the header, ie. "Favorites"
- L198 _public prototype_ `bool IsExpanded() const;`
- L199 _public prototype_ `void SetExpanded(bool bInExpanded);`
- L202 _public prototype_ `bool IsEmpty() const;` — Returns true if the contents is "Empty", regardless of expansion state.
- L205 _public prototype_ `void SaveSettings(const FString& InIniFilename, const FString& InIniSection, const FString& InSettingsString) const;` — Saves all persistent settings to config.
- L208 _public prototype_ `void LoadSettings(const FString& InIniFilename, const FString& InIniSection, const FString& InSettingsString);` — Loads settings from config based on the browser's InstanceName.
- L210 _public function_ `bool HasSearch() const`
- L212 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L213 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L214 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L216 _public prototype_ `TSharedPtr<SSearchToggleButton> GetSearchToggleButton() const;`
- L219 _private prototype_ `EVisibility GetHeaderSearchActionVisibility() const;`
- L221 _private prototype_ `void OnAreaExpansionChanged(bool bInIsExpanded);`
- L224 _private member_ `FName Id;`
- L226 _private member_ `TAttribute<bool> bIsEmpty;`
- L229 _private member_ `TSharedPtr<FSourcesSearch> Search = nullptr;` — The (optional) source search.
- L232 _private member_ `TSharedPtr<SSearchToggleButton> SearchToggleButton = nullptr;` — Toggle button for showing/hiding the search area, only visible if Search IsValid.
- L234 _private member_ `TSharedPtr<IScrollableWidget> BodyScrollableWidget;`
- L236 _private member_ `TSharedPtr<SExpandableArea> ExpandableArea;`
- L238 _private member_ `FOnBooleanValueChanged OnExpansionChanged;`
- L240 _private member_ `bool bExpandedByDefault = false;`

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Editor` (scope `UE`)
- L27 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)
- L27 _namespace_ `namespace Private` (scope `UE::Editor::ContentBrowser`)
- L46 _namespace_ `namespace UE`
- L46 _namespace_ `namespace Editor` (scope `UE`)
- L46 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)
- L46 _namespace_ `namespace Private` (scope `UE::Editor::ContentBrowser`)

### `Source/Editor/ContentBrowser/Private/Widgets/WidgetSizeSwitcher.h` (Private)


#### class `UE::Editor::ContentBrowser::Private::TWidgetDesiredSizeSwitcher`  
`template <EAxis::Type Axis> class TWidgetDesiredSizeSwitcher`  
_L18-84_
- desc: Returns a size override to bind to based on a single subject widget's desired size, clamped between a provided size range. If a reference widget is provided, it's (allotted, not desired) size is used for the range max value. Axis is 0 for x/width, 1 for y/height.
- L23 _public prototype_ `virtual ~TWidgetDesiredSizeSwitcher() = default;`
- L25 _public function_ `TWidgetDesiredSizeSwitcher( const TSharedPtr<SWidget>& InSubjectWidget, const TSharedPtr<SWidget>& InMaxSizeReferenceWidget, const FInt16Range& InSizeRange) : SubjectWidget(InSubjectWidget) , MaxSizeReferenceWidget(InMaxSizeReferenceWidget) , SizeRange(InSizeRange)`
- L35 _public function_ `void SetMaxSizeReferenceWidget(const TSharedPtr<SWidget>& InWidget)`
- L43 _public function_ `void SetSizeRange(const FInt16Range& InRange)`
- L51 _public function_ `float GetDesiredSizeOverride()`
- L77 _protected member_ `TSharedPtr<SWidget> SubjectWidget;`
- L78 _protected member_ `TSharedPtr<SWidget> MaxSizeReferenceWidget;`
- L79 _protected member_ `FInt16Range SizeRange;`
- L81 _protected member_ `int16 LastMaxSize = INDEX_NONE;`
- L82 _protected member_ `float LastDesiredSizeOverride = -1.0f;`
- L83 _protected member_ `int16 LastSubjectWidgetDesiredSize = INDEX_NONE;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)
- L10 _namespace_ `namespace Private` (scope `UE::Editor::ContentBrowser`)

### `Source/Editor/ContentBrowser/Public/AssetTextFilter.h` (Public)


#### class `FAssetTextFilter`  
`class FAssetTextFilter : public TSharedFromThis<FAssetTextFilter>`  
_L20-134_
- inherits: `TSharedFromThis<FAssetTextFilter>`
- desc: Class handling text filtering for content browser views. Unlike FFrontendFilter, guarantees that filtering can be performed concurrently. @see FAssetTextFilterContext used to share the settings of this filter across multiple parallel workers.
- L23 _public prototype_ `FAssetTextFilter();`
- L24 _public prototype_ `~FAssetTextFilter();`
- L27 _public prototype_ `FAssetTextFilter(FAssetTextFilter&& Other) = delete;` — Cannot be moved or copied because of bound delegates.
- L28 _public prototype_ `FAssetTextFilter& operator=(FAssetTextFilter&& Other) = delete;`
- L30 _public prototype_ `FAssetTextFilter(const FAssetTextFilter& Other) = delete;`
- L31 _public prototype_ `FAssetTextFilter& operator=(const FAssetTextFilter& Other) = delete;`
- L38 _public prototype_ `TSharedPtr<FCompiledAssetTextFilter> Compile();` — Create a compiled filter which can safely be used on other threads. Combines the primary text filter with custom saved filters.
- L41 _public prototype_ `bool IsEmpty() const;` — Returns true if the filter contains no primary text and no custom saved queries
- L44 _public prototype_ `void SetCustomTextFilters(TArray<FText> InQueries);` — Provides a set of saved filters/queries to be performed asynchronously alongside the main text filtering.
- L47 _public prototype_ `FText GetRawFilterText() const;` — Returns the unsanitized and unsplit filter terms
- L50 _public prototype_ `void SetRawFilterText(const FText& InFilterText);` — Set the Text to be used as the Filter's restrictions
- L53 _public prototype_ `FText GetFilterErrorText() const;` — Get the last error returned from lexing or compiling the current filter text
- L56 _public prototype_ `void SetIncludeClassName(const bool InIncludeClassName);` — If bIncludeClassName is true, the text filter will include an asset's class name in the search
- L59 _public prototype_ `void SetIncludeAssetPath(const bool InIncludeAssetPath);` — If bIncludeAssetPath is true, the text filter will match against full Asset path
- L62 _public prototype_ `bool GetIncludeAssetPath() const;` — Returns the last value set with SetIncludeAssetPath
- L65 _public prototype_ `void SetIncludeCollectionNames(const bool InIncludeCollectionNames);` — If bIncludeCollectionNames is true, the text filter will match against collection names as well
- L68 _public prototype_ `bool GetIncludeCollectionNames() const;` — Returns the last value set with SetIncludeCollectionNames
- L71 _public function_ `FSimpleMulticastDelegate& OnChanged()` — Delegate to bind for when the effective text filter changes so filtering can be re-run.
- L75 _private prototype_ `void HandleCollectionContainerCreated(const TSharedRef<ICollectionContainer>& CollectionContainer);` — Handles an on collection container created event
- L78 _private prototype_ `void HandleCollectionContainerDestroyed(const TSharedRef<ICollectionContainer>& CollectionContainer);` — Handles an on collection container destroyed event
- L81 _private prototype_ `void HandleIsHiddenChanged(ICollectionContainer& CollectionContainer, bool bIsHidden);` — Handles an on collection container is hidden changed event
- L84 _private prototype_ `void HandleCollectionCreated(ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection);` — Handles an on collection created event
- L87 _private prototype_ `void HandleCollectionDestroyed(ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection);` — Handles an on collection destroyed event
- L90 _private prototype_ `void HandleCollectionRenamed(ICollectionContainer& CollectionContainer, const FCollectionNameType& OriginalCollection, const FCollectionNameType& NewCollection);` — Handles an on collection renamed event
- L93 _private prototype_ `void HandleCollectionUpdated(ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection);` — Handles an on collection updated event
- L95 _private function_ `void BroadcastChangedEvent() const`
- L98 _private member_ `TArray<TSharedPtr<ICollectionContainer>> CollectionContainers;` — An array of collection containers that are being monitored
- L101 _private member_ `TArray<FCollectionRef> ReferencedDynamicCollections;` — An array of dynamic collections that are being referenced by the current query. These should be tested against each asset when it's looking for collections that contain it
- L107 _private member_ `FTextFilterExpressionEvaluator TextFilterExpressionEvaluator;` — Expression evaluator that can be used to perform complex text filter queries. When CustomTextFilters is empty, this filter can be used as-is, otherwise it is necessary to compiled a combined evaluator.
- L110 _private member_ `TArray<FText> CustomTextFilters;` — Additional queries from saved user filters. These and any primary text filter are combined with AND semantics.
- L113 _private member_ `FDelegateHandle OnCollectionContainerCreatedHandle;` — Delegate handles
- L114 _private member_ `FDelegateHandle OnCollectionContainerDestroyedHandle;`
- L124 _private member_ `TArray<FCollectionContainerHandles> CollectionContainerHandles;`
- L127 _private member_ `bool bIncludeClassName = false;` — Filter options
- L128 _private member_ `bool bIncludeAssetPath = false;`
- L129 _private member_ `bool bIncludeCollectionNames = false;`
- L131 _private member_ `bool bReferencedDynamicCollectionsDirty = true;`
- L133 _private member_ `FSimpleMulticastDelegate ChangedEvent;`

#### struct `FAssetTextFilter::FCollectionContainerHandles`  
`struct FCollectionContainerHandles`  
_L116-123_
- L118 _public member_ `FDelegateHandle OnIsHiddenChangedHandle;`
- L119 _public member_ `FDelegateHandle OnCollectionCreatedHandle;`
- L120 _public member_ `FDelegateHandle OnCollectionDestroyedHandle;`
- L121 _public member_ `FDelegateHandle OnCollectionRenamedHandle;`
- L122 _public member_ `FDelegateHandle OnCollectionUpdatedHandle;`

#### class `FCompiledAssetTextFilter`  
`class FCompiledAssetTextFilter : private ITextFilterExpressionContext, public TSharedFromThis<FCompiledAssetTextFilter>`  
_L141-230_
- inherits: `ITextFilterExpressionContext,TSharedFromThis<FCompiledAssetTextFilter>`
- desc: Context object for parallel filtering Allows reuse of memory when filtering in ParallelForWithTaskContext
- L143 _private typedef_ `typedef TRemoveReference<FAssetFilterType>::Type* FAssetFilterTypePtr;`
- L149 _public prototype_ `FCompiledAssetTextFilter( FPrivateToken, TSharedRef<const FTextFilterExpressionEvaluator> InSharedEvaluator, TSharedPtr<const TArray<FCollectionRef>> InReferencedDynamicCollections, TSharedPtr<const TArray<TSharedPtr<ICollectionContainer>>> InCollectionContainers, bool InIncludeClassName, bool InIncludeAssetPath, bool InIncludeCollectionNames);`
- L157 _public prototype_ `virtual ~FCompiledAssetTextFilter() = default;`
- L159 _public prototype_ `FCompiledAssetTextFilter(FCompiledAssetTextFilter&&) = default;`
- L160 _public prototype_ `FCompiledAssetTextFilter& operator=( FCompiledAssetTextFilter&&) = default;`
- L166 _public prototype_ `FCompiledAssetTextFilter CloneForThreading();` — Clone a copy of this which shares filtering data but can be used on a different thread to the original. Each FCompiledAssetTextFilter should only be used on a single thread at once.
- L172 _public prototype_ `bool PassesFilter(FAssetFilterType InItem);` — Non-const method to check an item against the filter, using member fields to amortize memory allocations for many such checks
- L173 _public prototype_ `bool PassesFilter(FAssetFilterType InItem, FStringView InItemVersePath);`
- L176 _public prototype_ `virtual bool TestBasicStringExpression( const FTextFilterString& InValue, const ETextFilterTextComparisonMode InTextComparisonMode) const override;` — Test the given value against the strings extracted from the current item
- L180 _public prototype_ `virtual bool TestComplexExpression( const FName& InKey, const FTextFilterString& InValue, const ETextFilterComparisonOperation InComparisonOperation, const ETextFilterTextComparisonMode InTextComparisonMode) const override;` — Perform a complex expression test for the current item
- L187 _private prototype_ `FCompiledAssetTextFilter(FCompiledAssetTextFilter&) = default;` — Private copying for explicit clone operation
- L188 _private prototype_ `FCompiledAssetTextFilter& operator=(const FCompiledAssetTextFilter&) = default;`
- L191 _private member_ `TSharedRef<const FTextFilterExpressionEvaluator> Evaluator;` — Compiled text query
- L194 _private member_ `TSharedPtr<const TArray<FCollectionRef>> ReferencedDynamicCollections;` — Dynamic collections referenced by the compiled query
- L197 _private member_ `TSharedPtr<const TArray<TSharedPtr<ICollectionContainer>>> CollectionContainers;` — Cached Collection containers
- L200 _private member_ `bool bIncludeClassName = false;` — Filter options
- L201 _private member_ `bool bIncludeAssetPath = false;`
- L202 _private member_ `bool bIncludeCollectionNames = false;`
- L206 _private member_ `bool bIsFile = false;`
- L209 _private member_ `FAssetFilterTypePtr AssetPtr;` — Pointer to the asset we're currently filtering
- L212 _private member_ `FString TextBuffer;` — Shared buffer for text keys to search
- L215 _private member_ `mutable FTextFilterString TextFilterString;` — Recyclable text filter string so reduce allocations
- L218 _private member_ `FStringView AssetDisplayName;` — Display name of the current asset
- L220 _private member_ `FStringView AssetFullPath;` — Full path of the current asset
- L222 _private member_ `FStringView AssetVirtualPath;` — Virtual path of the current asset
- L224 _private member_ `FStringView AssetExportTextPath;` — The export text name of the current asset
- L226 _private member_ `FStringView AssetVersePath;` — Verse path of the current asset
- L229 _private member_ `TArray<FName> AssetCollectionNames;` — Names of the collections that the current asset is in

#### struct `FCompiledAssetTextFilter::FPrivateToken`  
`struct FPrivateToken`  
_L146-146_
- L146 _public prototype_ `struct FPrivateToken`

#### class `IAssetTextFilterHandler`  
`class IAssetTextFilterHandler`  
_L241-284_
- desc: Interface that can be implemented to extend text filtering in the content browser. Objects implementing this interface must be manually added and removed from participation in text filtering with RegisterHandler and UnregisterHandler to allow synchronization with async text filtering. Objects implementing this interface must be able to have HandleTextFilterValue and HandleTextFilterKeyValue called on any thread in between RegisterHandler and UnregisterHandler
- L244 _public prototype_ `virtual ~IAssetTextFilterHandler() = default;`
- L256 _public prototype_ `virtual bool HandleTextFilterValue(const FContentBrowserItem& InContentBrowserItem, const FTextFilterString& InValue, const ETextFilterTextComparisonMode InTextComparisonMode, bool& bOutIsMatch) = 0;` — Implement this function to handle basic text matching. @param InContentBrowserItem The item to be filtered. @param InValue The text string the user wants to filter items against. @param InTextComparisonMode How to compare text e.g. prefix/suffix/contains @param bOutIsMatch Whether the item matches the user's query @return true If this handler provided an answer for whether the item matches. bOutIsMatch may be true or false in this case. @return false If this handler did not decide whether this item was filtered, and other handlers or the built-in implementation should continue.
- L273 _public prototype_ `virtual bool HandleTextFilterKeyValue(const FContentBrowserItem& InContentBrowserItem, const FName& InKey, const FTextFilterString& InValue, const ETextFilterComparisonOperation InComparisonOperation, const ETextFilterTextComparisonMode InTextComparisonMode, bool& bOutIsMatch) = 0;` — Implement this function to handle complex tests of keys against values (e.g. class=actor) @param InContentBrowserItem The item to be filtered. @param InKey The key identifying what data from InContentBrowserItem to compare against. @param InValue The user's provided text to compare the item against. @param InComparisonOperation Comparison operator for numeric comparisons. @param InTextComparisonMode How to compare text e.g. prefix/suffix/contains @param bOutIsMatch Whether the item matches the user's query @return true If this handler provided an answer for whether the item matches. bOutIsMatch may be true or false in this case. @return false If this handler did not decide whether this item was filtered, and other handlers or the built-in implementation should continue.
- L281 _public prototype_ `void RegisterHandler();` — Call on your derived instance of IAssetTextFilterHandler to have it participate in asset text filtering.
- L283 _public prototype_ `void UnregisterHandler();` — Call on your derived instance of IAssetTextFilterHandler to remove it from asset text filtering.

### `Source/Editor/ContentBrowser/Public/AssetViewContentSources.h` (Public)


#### struct `FAssetViewContentSources`  
`struct FAssetViewContentSources`  
_L8-76_
- L10 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnEnumerateCustomSourceItemDatas, TFunctionRef<bool(class FContentBrowserItemData&&)>) FOnEnumerateCustomSourceItemDatas OnEnumerateCustomSourceItemDatas;`
- L13 _public member_ `bool bIncludeVirtualPaths = true;`
- L15 _public prototype_ `FAssetViewContentSources() = default;`
- L17 _public prototype_ `explicit FAssetViewContentSources(FName InVirtualPath);`
- L18 _public prototype_ `explicit FAssetViewContentSources(TArray<FName> InVirtualPaths);`
- L20 _public prototype_ `explicit FAssetViewContentSources(FCollectionRef InCollection);`
- L21 _public prototype_ `explicit FAssetViewContentSources(TArray<FCollectionRef> InCollections);`
- L23 _public prototype_ `FAssetViewContentSources(TArray<FName> InVirtualPaths, TArray<FCollectionRef> InCollections);`
- L25 _public prototype_ `FAssetViewContentSources(const FAssetViewContentSources&) = default;`
- L26 _public prototype_ `FAssetViewContentSources(FAssetViewContentSources&&) = default;`
- L28 _public prototype_ `FAssetViewContentSources& operator=(const FAssetViewContentSources&) = default;`
- L29 _public prototype_ `FAssetViewContentSources& operator=(FAssetViewContentSources&&) = default;`
- L31 _public function_ `bool IsEmpty() const`
- L36 _public function_ `bool HasVirtualPaths() const`
- L41 _public function_ `const TArray<FName>& GetVirtualPaths() const`
- L46 _public prototype_ `void SetVirtualPath(FName InVirtualPath);`
- L47 _public prototype_ `void SetVirtualPaths(const TArray<FName>& InVirtualPaths);`
- L49 _public function_ `bool HasCollections() const`
- L54 _public function_ `const TArray<FCollectionRef>& GetCollections() const`
- L59 _public prototype_ `void SetCollection(const FCollectionRef& InCollection);`
- L60 _public prototype_ `void SetCollections(const TArray<FCollectionRef>& InCollections);`
- L62 _public function_ `bool IsIncludingVirtualPaths() const`
- L67 _public prototype_ `bool IsDynamicCollection() const;`
- L69 _public prototype_ `void Reset();`
- L72 _private prototype_ `void SanitizeCollections();`
- L74 _private member_ `TArray<FName> VirtualPaths;`
- L75 _private member_ `TArray<FCollectionRef> Collections;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnEnumerateCustomSourceItemDatas, TFunctionRef<bool(class FContentBrowserItemData&&)>) FOnEnumerateCustomSourceItemDatas OnEnumerateCustomSourceItemDatas;`

### `Source/Editor/ContentBrowser/Public/AssetViewSortManager.h` (Public)


#### class `FAssetViewSortManager`  
`class FAssetViewSortManager`  
_L21-71_
- L25 _public prototype_ `FAssetViewSortManager();` — Constructor
- L28 _public prototype_ `void ResetSort();` — Reset the sort mode back to default
- L31 _public prototype_ `void SortList(TArray<TSharedPtr<FAssetViewItem>>& AssetItems, const FName& MajorityAssetType, const TArray<FAssetViewCustomColumn>& CustomColumns) const;` — Sorts a list using the current ColumnId and Mode. Supply a MajorityAssetType to help discover sorting type (numerical vs alphabetical)
- L34 _public prototype_ `void ExportColumnsToCSV(TArray<TSharedPtr<FAssetViewItem>>& AssetItems, TArray<FName>& ColumnList, const TArray<FAssetViewCustomColumn>& CustomColumns, FString& OutString) const;` — Exports the list of asset items to CSV, in order and with the listed columns
- L37 _public prototype_ `bool SetOrToggleSortColumn(const EColumnSortPriority::Type InSortPriority, const FName& InColumnId);` — Sets the sort mode based on the column that was clicked, returns true if newly assigned
- L40 _public prototype_ `void SetSortColumnId(const EColumnSortPriority::Type InSortPriority, const FName& InColumnId);` — Sets the column to sort
- L43 _public prototype_ `void SetSortMode(const EColumnSortPriority::Type InSortPriority, const EColumnSortMode::Type InSortMode);` — Sets the current sort mode
- L46 _public function_ `EColumnSortMode::Type GetSortMode(const EColumnSortPriority::Type InSortPriority) const` — Gets the current sort mode
- L49 _public function_ `FName GetSortColumnId(const EColumnSortPriority::Type InSortPriority) const` — Gets the current sort column id
- L52 _public prototype_ `bool FindAndRefreshCustomColumn(const TArray<TSharedPtr<FAssetViewItem>>& AssetItems, const FName ColumnName, const TArray<FAssetViewCustomColumn>& CustomColumns, UObject::FAssetRegistryTag::ETagType& TagType) const;` — Refresh a custom column if needed.  If found, returns true with TagType parameter set
- L56 _public member_ `static const FName NameColumnId;` — The names of non-type specific columns in the columns view.
- L57 _public member_ `static const FName ClassColumnId;`
- L58 _public member_ `static const FName PathColumnId;`
- L59 _public member_ `static const FName DiskSizeColumnId;`
- L60 _public member_ `static const FName AssetAccessSpecifierColumnId;`
- L63 _public member_ `static const FName RevisionControlColumnId;` — The revision control column. NOTE: This column currently doesn't support sorting, but is wired through the Sort Manager so the feature can be added in the future
- L67 _private member_ `FName SortColumnId[EColumnSortPriority::Max];` — The name of the column that is currently used for sorting.
- L70 _private member_ `EColumnSortMode::Type SortMode[EColumnSortPriority::Max];` — Whether the sort is ascending or descending.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API CONTENTBROWSER_API`

### `Source/Editor/ContentBrowser/Public/AssetViewTypes.h` (Public)


#### enum `EFolderType`  
`enum class EFolderType : uint8`  
_L22-29_
- L24 _public enumerator_ `Normal`
- L25 _public enumerator_ `CustomVirtual` — No corresponding on-disk path, used for organization in the content browser
- L26 _public enumerator_ `PluginRoot` — Root content folder of a plugin
- L27 _public enumerator_ `Code`
- L28 _public enumerator_ `Developer`

#### class `FAssetViewItem`  
`class FAssetViewItem`  
_L34-188_
- desc: An item (folder or file) displayed in the asset view
- L37 _public prototype_ `FAssetViewItem(int32 Index);`
- L39 _public prototype_ `explicit FAssetViewItem(int32 Index, FContentBrowserItem&& InItem);`
- L40 _public prototype_ `explicit FAssetViewItem(int32 Index, const FContentBrowserItem& InItem);`
- L42 _public prototype_ `explicit FAssetViewItem(int32 Index, FContentBrowserItemData&& InItemData);`
- L43 _public prototype_ `explicit FAssetViewItem(int32 Index, const FContentBrowserItemData& InItemData);`
- L46 _public prototype_ `void ResetItemData(int32 OldIndex, int32 Index, FContentBrowserItemData InItemData);` — When recycling an object, clear the item data and replace it with the given data.
- L48 _public prototype_ `void AppendItemData(const FContentBrowserItem& InItem);`
- L50 _public prototype_ `void AppendItemData(const FContentBrowserItemData& InItemData);`
- L52 _public prototype_ `void RemoveItemData(const FContentBrowserItem& InItem);`
- L54 _public prototype_ `void RemoveItemData(const FContentBrowserItemData& InItemData);`
- L56 _public prototype_ `void RemoveItemData(const FContentBrowserMinimalItemData& InItemKey);`
- L59 _public prototype_ `UE_INTERNAL void ConfigureAssetPathText(bool bInShowingContentVersePath);` — Configures the type of path GetAssetPathText should return.
- L62 _public prototype_ `UE_INTERNAL void CacheVersePathTextForTextFiltering();` — Caches the Verse path to use when filtering items.
- L65 _public prototype_ `UE_INTERNAL FText GetAssetClassText() const;` — Gets the asset class name to use when viewing.
- L68 _public prototype_ `UE_INTERNAL const FText& GetAssetPathText() const;` — Gets the asset path to use when viewing or sorting the path column.
- L71 _public prototype_ `UE_INTERNAL const FText& GetVersePathTextForTextFiltering() const;` — Gets the Verse path to use when filtering items. Requires a call to CacheVersePathTextForTextFiltering first.
- L74 _public prototype_ `void ClearCachedCustomColumns();` — Clear cached custom column data
- L80 _public prototype_ `void CacheCustomColumns(TArrayView<const FAssetViewCustomColumn> CustomColumns, const bool bUpdateSortData, const bool bUpdateDisplayText, const bool bUpdateExisting);` — Updates cached custom column data (only does something for files) @param bUpdateExisting If true, only updates existing columns, if false only adds missing columns
- L83 _public prototype_ `bool GetCustomColumnDisplayValue(const FName ColumnName, FText& OutText) const;` — Get the display value of a custom column on this item
- L86 _public prototype_ `bool GetCustomColumnValue(const FName ColumnName, FString& OutString, UObject::FAssetRegistryTag::ETagType* OutType = nullptr) const;` — Get the value (and optionally also the type) of a custom column on this item
- L89 _public prototype_ `bool GetTagValue(const FName Tag, FString& OutString, UObject::FAssetRegistryTag::ETagType* OutType = nullptr) const;` — Get the value (and optionally also the type) of a named tag on this item
- L98 _public prototype_ `bool GetItemAssetAccessSpecifier(EAssetAccessSpecifier& OutAssetAccessSpecifier) const;` — Query the EAssetAccessSpecifier of the item. @param OutAssetAccessSpecifier The EAssetAccessSpecifier reference that will be filled. @return True if OutAssetAccessSpecifier was filled.
- L105 _public prototype_ `FText GetItemAssetAccessSpecifierText() const;` — Query a readable FText of the EAssetAccessSpecifier for the item. @return If the item has a modifiable EAssetAccessSpecifier, then a readable text version. Otherwise blank.
- L112 _public prototype_ `FName GetItemAssetAccessSpecifierIconStyleName(const TCHAR* InSizeSuffix = TEXT("")) const;` — Query the icon brush style name to use for the EAssetAccessSpecifier of the item. @return If the item has a modifiable EAssetAccessSpecifier, then the style name of the brush to use. Otherwise NAME_None.
- L119 _public prototype_ `bool CanModifyItemAssetAccessSpecifier() const;` — Query the item's ability to modify its EAssetAccessSpecifier. @return True if the item has an EAssetAccessSpecifier that can be modified.
- L122 _public prototype_ `static FName GetPublicAssetAccessSpecifierIconStyleName(const TCHAR* InSizeSuffix = TEXT(""));` — Returns the brush style name to use for a public asset access specifier
- L125 _public prototype_ `static FName GetPrivateAssetAccessSpecifierIconStyleName(const TCHAR* InSizeSuffix = TEXT(""));` — Returns the brush style name to use for a private asset access specifier
- L128 _public prototype_ `static FName GetEpicInternalAssetAccessSpecifierIconStyleName(const TCHAR* InSizeSuffix = TEXT(""));` — Returns the brush style name to use for an Epic Internal asset access specifier
- L131 _public prototype_ `const FContentBrowserItem& GetItem() const;` — Get the underlying Content Browser item
- L133 _public prototype_ `bool IsFolder() const;`
- L135 _public prototype_ `bool IsFile() const;`
- L137 _public prototype_ `bool IsTemporary() const;`
- L142 _public prototype_ `void BroadcastItemDataChanged();` — Called when the view explicitly wants to notify widgets of changes Not called during bulk rebuilds when the view will be re-populated even if items are being recycled Updates cached paths then raises the OnItemDataChanged event.
- L145 _public prototype_ `FSimpleMulticastDelegate& OnItemDataChanged();` — Get the event fired when the data for this item changes
- L148 _public prototype_ `FSimpleDelegate& OnRenameRequested();` — Get the event fired whenever a rename is requested
- L151 _public prototype_ `FSimpleDelegate& OnRenameCanceled();` — Get the event fired whenever a rename is canceled
- L154 _public prototype_ `static FString ItemToString_Debug(TSharedPtr<FAssetViewItem> AssetItem);` — Helper function to turn an item into a string for debugging
- L157 _private prototype_ `void CacheAssetPathText();`
- L158 _private prototype_ `void CacheVersePathText() const;`
- L161 _private member_ `FContentBrowserItem Item;` — Underlying Content Browser item data
- L167 _private member_ `std::atomic<int32> Index;` — Index at which this is stored in the asset view's item collection. Can be used to detect an item being added to the collection twice by mistake.
- L169 _private member_ `bool bShowingContentVersePath;`
- L170 _private member_ `mutable bool bHasCachedVersePathText;`
- L171 _private member_ `FText CachedAssetPathText;`
- L172 _private member_ `mutable FText CachedVersePathText;`
- L175 _private member_ `FSimpleMulticastDelegate ItemDataChangedEvent;` — An event to fire when the data for this item changes
- L178 _private member_ `FSimpleDelegate RenameRequestedEvent;` — Broadcasts whenever a rename is requested
- L181 _private member_ `FSimpleDelegate RenameCanceledEvent;` — Broadcasts whenever a rename is canceled
- L184 _private member_ `TMap<FName, TTuple<FString, UObject::FAssetRegistryTag::ETagType>> CachedCustomColumnData;` — Map of values/types for custom columns
- L187 _private member_ `TMap<FName, FText> CachedCustomColumnDisplayText;` — Map of display text for custom columns

### `Source/Editor/ContentBrowser/Public/AssetViewWidgets.h` (Public)


#### struct `FAssetViewItemHelper`  
`struct FAssetViewItemHelper`  
_L72-81_
- L75 _public prototype_ `static TSharedRef<SWidget> CreateListItemContents(SAssetListItem* const InListItem, const TSharedRef<SWidget>& InThumbnail, FName& OutItemShadowBorder, const FMargin& InFolderOverlayPadding = FMargin(0.f));`
- L76 _public prototype_ `static TSharedRef<SWidget> CreateTileItemContents(SAssetTileItem* const InTileItem, const TSharedRef<SWidget>& InThumbnail, FName& OutItemShadowBorder, const FMargin& InFolderOverlayPadding = FMargin(0.f), bool bShowAssetAccessSpecifier = false);`
- L80 _private prototype_ `template <typename T> static TSharedRef<SWidget> CreateListTileItemContents(T* const InTileOrListItem, const TSharedRef<SWidget>& InThumbnail, FName& OutItemShadowBorder, const FMargin& InFolderOverlayPadding, bool bShowAssetAccessSpecifier);`

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SAssetTileView>`  
_L85-88_
- L87 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SAssetTileView`  
`class SAssetTileView : public STileView<TSharedPtr<FAssetViewItem>>`  
_L91-96_
- inherits: `STileView<TSharedPtr<FAssetViewItem>>`
- desc: The tile view mode of the asset view
- L94 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L95 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SAssetListView>`  
_L100-103_
- L87 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SAssetListView`  
`class SAssetListView : public SListView<TSharedPtr<FAssetViewItem>>`  
_L106-111_
- inherits: `SListView<TSharedPtr<FAssetViewItem>>`
- desc: The list view mode of the asset view
- L109 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L110 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SAssetColumnView>`  
_L115-118_
- L87 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SAssetColumnView`  
`class SAssetColumnView : public SListView<TSharedPtr<FAssetViewItem>>`  
_L121-126_
- inherits: `SListView<TSharedPtr<FAssetViewItem>>`
- desc: The columns view mode of the asset view
- L124 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L125 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SAssetViewItem>`  
_L130-133_
- L87 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SAssetViewItem`  
`class SAssetViewItem : public SCompoundWidget`  
_L136-419_
- inherits: `SCompoundWidget`
- desc: A base class for all asset view items
- L142 _public function_ `SLATE_BEGIN_ARGS( SAssetViewItem ) : _ShouldAllowToolTip(true) , _ThumbnailEditMode(false) , _ShowAssetAccessSpecifier(false)`
- L149 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FAssetViewItem>, AssetItem) SLATE_EVENT(FOnRenameBegin, OnRenameBegin) SLATE_EVENT(FOnRenameCommit, OnRenameCommit) SLATE_EVENT(FOnVerifyRenameCommit, OnVerifyRenameCommit) SLATE_EVENT(FOnItemDestroyed, OnItemDestroyed) SLATE_ATTRIBUTE(bool, ShouldAllowToolTip) SLATE_ATTRIBUTE(bool, ThumbnailEditMode) SLATE_ARGUMENT(bool, ShowAssetAccessSpecifier) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_EVENT(FOnIsAssetValidForCustomToolTip, OnIsAssetValidForCustomToolTip) SLATE_EVENT(FOnGetCustomAssetToolTip, OnGetCustomAssetToolTip) SLATE_EVENT(FOnVisualizeAssetToolTip, OnVisualizeAssetToolTip) SLATE_EVENT(FOnAssetToolTipClosing, OnAssetToolTipClosing) SLATE_ARGUMENT(FIsSelected, IsSelected)` — Data for the asset this item represents
- L196 _public prototype_ `void Construct( const FArguments& InArgs );` — Performs common initialization logic for all asset view items
- L199 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — NOTE: Any functions overridden from the base widget classes *must* also be overridden by SAssetColumnViewRow and forwarded on to its internal item
- L200 _public prototype_ `virtual TSharedPtr<IToolTip> GetToolTip() override;`
- L201 _public prototype_ `virtual void OnDragEnter( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L202 _public prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;`
- L203 _public prototype_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L204 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L205 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent, const TSharedRef<SWidget>& InParentWidget);`
- L206 _public prototype_ `virtual bool OnVisualizeTooltip( const TSharedPtr<SWidget>& TooltipContent ) override;`
- L207 _public prototype_ `virtual void OnToolTipClosing() override;`
- L210 _public prototype_ `virtual FSlateColor GetAssetColor() const;` — Returns the color this item should be tinted with
- L213 _public prototype_ `virtual const FSlateBrush* GetBorderImage() const;` — Get the border image to display
- L216 _public prototype_ `FText GetNameText() const;` — Get the name text to be displayed for this item
- L220 _protected prototype_ `bool IsNameReadOnly() const;` — Check to see if the name should be read-only
- L223 _protected prototype_ `virtual void HandleBeginNameChange( const FText& OriginalText );` — Handles starting a name change
- L226 _protected prototype_ `virtual void HandleNameCommitted( const FText& NewText, ETextCommit::Type CommitInfo );` — Handles committing a name change
- L229 _protected prototype_ `virtual bool HandleVerifyNameChanged( const FText& NewText, FText& OutErrorMessage );` — Handles verifying a name change
- L232 _protected prototype_ `virtual void OnAssetDataChanged();` — Handles committing a name change
- L235 _protected prototype_ `virtual void DirtyStateChanged();` — Notification for when the dirty flag changes
- L238 _protected prototype_ `FText GetAssetClassText() const;` — Gets the name of the class of this asset
- L241 _protected prototype_ `const FSlateBrush* GetDirtyImage() const;` — Gets the brush for the dirty indicator image
- L244 _protected prototype_ `TSharedRef<SWidget> GenerateSourceControlIconWidget();` — Generates the source control icon widget
- L247 _protected prototype_ `TSharedRef<SWidget> GenerateExtraStateIconWidget(TAttribute<float> InMaxExtraStateIconWidth) const;` — Generate a widget to inject extra external state indicator on the asset.
- L250 _protected prototype_ `TSharedRef<SWidget> GenerateExtraStateTooltipWidget() const;` — Generate a widget to inject extra external state indicator on the asset tooltip.
- L253 _protected prototype_ `TSharedPtr<SWidget> GenerateExtraStateTooltipWidgetNewStyle() const;` — Generate a widget to inject extra external state indicator on the asset tooltip. Need to be TSharedPtr for AssetThumbnail
- L256 _protected prototype_ `EVisibility GetThumbnailEditModeUIVisibility() const;` — Gets the visibility for the thumbnail edit mode UI
- L259 _protected prototype_ `TSharedRef<SWidget> CreateToolTipWidget() const;` — Creates a tooltip widget for this item
- L262 _protected prototype_ `EVisibility GetSourceControlTextVisibility() const;` — Gets the visibility of the source control text block in the tooltip
- L265 _protected prototype_ `FText GetSourceControlText() const;` — Gets the text for the source control text block in the tooltip
- L268 _protected prototype_ `FText GetExternalPackagesText() const;` — Gets the text detailing all the modified external packages (and their contained objects)
- L271 _protected prototype_ `FText GetAssetUserDescription() const;` — Helper function for CreateToolTipWidget. Gets the user description for the asset, if it exists.
- L274 _protected prototype_ `void AddToToolTipInfoBox(const TSharedRef<SVerticalBox>& InfoBox, const FText& Key, const FText& Value, bool bImportant) const;` — Helper function for CreateToolTipWidget. Adds a key value pair to the info box of the tooltip
- L277 _protected prototype_ `void UpdateDirtyState();` — Updates the bPackageDirty flag
- L280 _protected prototype_ `bool IsDirty() const;` — Returns true if the item is dirty.
- L283 _protected prototype_ `void UpdateSourceControlState(float InDeltaTime);` — Update the source control state of this item if required
- L286 _protected prototype_ `void CacheDisplayTags();` — Cache the display tags for this item
- L289 _protected prototype_ `bool IsFolder() const;` — Whether this item is a folder
- L292 _protected prototype_ `void HandleSourceControlProviderChanged(class ISourceControlProvider& OldProvider, class ISourceControlProvider& NewProvider);` — Delegate handler for when the source control provider changes
- L295 _protected prototype_ `void HandleSourceControlStateChanged();` — Delegate handler for when source control state changes
- L298 _protected function_ `virtual float GetNameTextWrapWidth() const` — Returns the width at which the name label will wrap the name
- L301 _protected prototype_ `void CacheDirtyExternalPackageInfo();` — Caches the ExternalPackagesText
- L304 _protected prototype_ `bool ShouldExpandTooltip() const;` — If true it will expand the tooltip by default
- L307 _protected prototype_ `TSharedRef<SWidget> GetAssetAccessSpecifierIconBox() const;` — Returns the SBox that will hold the AssetAccessSpecifierIcon
- L310 _protected prototype_ `void UpdateAssetAccessSpecifierIcon();` — Renders the appropriate AssetAccessSpecifierIcon based on the EAssetAccessSpecifier of the asset
- L313 _protected prototype_ `FText GetAssetAccessSpecifierText() const;` — Gets the AssetAccessSpecifier as FText.
- L333 _protected member_ `TSharedPtr< SInlineEditableTextBlock > InlineRenameWidget;`
- L335 _protected member_ `TSharedPtr<STextBlock> ClassTextWidget;`
- L338 _protected member_ `TSharedPtr<FAssetViewItem> AssetItem;` — The data for this item
- L341 _protected member_ `TArray<FTagDisplayItem> CachedDisplayTags;` — The cached display tags for this item
- L344 _protected member_ `FOnRenameBegin OnRenameBegin;` — Delegate for when an asset name has entered a rename state
- L347 _protected member_ `FOnRenameCommit OnRenameCommit;` — Delegate for when an asset name has been entered for an item that is in a rename state
- L350 _protected member_ `FOnVerifyRenameCommit OnVerifyRenameCommit;` — Delegate for when an asset name has been entered for an item to verify the name before commit
- L353 _protected member_ `FOnItemDestroyed OnItemDestroyed;` — Called when any asset item is destroyed. Used in thumbnail management
- L356 _protected member_ `FOnIsAssetValidForCustomToolTip OnIsAssetValidForCustomToolTip;` — Called to test if it is valid to make a custom tool tip for that asset
- L359 _protected member_ `FOnGetCustomAssetToolTip OnGetCustomAssetToolTip;` — Called if bound to get a custom asset item tooltip
- L362 _protected member_ `FOnVisualizeAssetToolTip OnVisualizeAssetToolTip;` — Called if bound when about to show a tooltip
- L365 _protected member_ `FOnAssetToolTipClosing OnAssetToolTipClosing;` — Called if bound when a tooltip is closing
- L368 _protected member_ `FIsSelected IsSelected;` — Delegate for getting the selection state of this item
- L370 _protected member_ `FGeometry LastGeometry;`
- L373 _protected member_ `TAttribute<bool> ShouldAllowToolTip;` — If false, the tooltip will not be displayed
- L376 _protected member_ `TAttribute<bool> ThumbnailEditMode;` — If true, display the thumbnail edit mode UI
- L379 _protected member_ `TAttribute<FText> HighlightText;` — The substring to be highlighted in the name and tooltip path
- L382 _protected member_ `const FSlateBrush* AssetDirtyBrush;` — Cached brushes for the dirty state
- L385 _protected member_ `bool bItemDirty;` — Cached flag describing if the item is dirty
- L388 _protected member_ `bool bSourceControlStateRequested;` — Flag indicating whether we have requested initial source control state
- L391 _protected member_ `float SourceControlStateDelay;` — Delay timer before we request a source control state update, to prevent spam
- L394 _protected member_ `bool bDraggedOver;` — True when a drag is over this item with a drag operation that we know how to handle. The operation itself may not be valid to drop.
- L397 _protected member_ `TSharedPtr<SLayeredImage> SCCStateWidget;` — Widget for the source control state
- L400 _protected member_ `TSharedPtr<IToolTip> ThumbnailWidgetITooltip;` — Thumbnail tooltip widget used for asset if no given custom widget is passed
- L403 _protected member_ `bool bHasCCStateBrush = false;` — Whether the item has a valid scc state brush (not empty)
- L405 _protected member_ `bool bShouldSaveExternalPackages = false;`
- L406 _protected member_ `FString CachedDirtyPackagesList;`
- L409 _protected member_ `FDelegateHandle SourceControlStateChangedDelegateHandle;` — Delegate handle for the HandleSourceControlStateChanged function callback
- L412 _protected member_ `bool bShowAssetAccessSpecifier = false;` — Whether to show the icon / text for the item's EAssetAccessSpecifier
- L415 _protected member_ `TSharedPtr<SBox> AssetAccessSpecifierIconBox;` — Widget holding the EAssetAccessSpecifier as an icon
- L418 _protected member_ `TSharedPtr<STextBlock> AssetAccessSpecifierText;` — Widget rendering the EAssetAccessSpecifier as text

#### struct `SAssetViewItem::FTagDisplayItem`  
`struct FTagDisplayItem`  
_L317-331_
- desc: Data for a cached display tag for this item (used in the tooltip, and also as the display string in column views)
- L319 _public function_ `FTagDisplayItem(FName InTagKey, FText InDisplayKey, FText InDisplayValue, const bool InImportant) : TagKey(InTagKey) , DisplayKey(MoveTemp(InDisplayKey)) , DisplayValue(MoveTemp(InDisplayValue)) , bImportant(InImportant)`
- L327 _public member_ `FName TagKey;`
- L328 _public member_ `FText DisplayKey;`
- L329 _public member_ `FText DisplayValue;`
- L330 _public member_ `bool bImportant;`

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SAssetListItem>`  
_L423-426_
- L87 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SAssetListItem`  
`class SAssetListItem : public SAssetViewItem`  
_L429-603_
- inherits: `SAssetViewItem`
- desc: An item in the asset list view
- L434 _public function_ `SLATE_BEGIN_ARGS( SAssetListItem ) : _ThumbnailPadding(0) , _ThumbnailLabel( EThumbnailLabel::ClassName ) , _CurrentThumbnailSize(EThumbnailSize::Medium) , _ThumbnailHintColorAndOpacity( FLinearColor( 0.0f, 0.0f, 0.0f, 0.0f ) ) , _ItemHeight(16) , _ShouldAllowToolTip(true) , _ThumbnailEditMode(false) , _AllowThumbnailHintLabel(false) , _ShowAssetAccessSpecifier(false)`
- L447 _public prototype_ `SLATE_ARGUMENT( TSharedPtr<FAssetThumbnail>, AssetThumbnail) SLATE_ARGUMENT( TSharedPtr<FAssetViewItem>, AssetItem ) SLATE_ARGUMENT( float, ThumbnailPadding ) SLATE_ARGUMENT( EThumbnailLabel::Type, ThumbnailLabel ) SLATE_ATTRIBUTE(EThumbnailSize, CurrentThumbnailSize) SLATE_ATTRIBUTE( FLinearColor, ThumbnailHintColorAndOpacity ) SLATE_ATTRIBUTE( float, ItemHeight ) SLATE_EVENT( FOnRenameBegin, OnRenameBegin ) SLATE_EVENT( FOnRenameCommit, OnRenameCommit ) SLATE_EVENT( FOnVerifyRenameCommit, OnVerifyRenameCommit ) SLATE_EVENT( FOnItemDestroyed, OnItemDestroyed ) SLATE_ATTRIBUTE( bool, ShouldAllowToolTip ) SLATE_ATTRIBUTE( FText, HighlightText ) SLATE_ATTRIBUTE( bool, ThumbnailEditMode )` — The handle to the thumbnail this item should render
- L518 _public prototype_ `void Construct( const FArguments& InArgs );` — Constructs this widget with InArgs
- L521 _public prototype_ `virtual void OnAssetDataChanged() override;` — Handles committing a name change
- L524 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Handles realtime thumbnails
- L527 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;` — Handles realtime thumbnails
- L530 _public function_ `bool CanDisplayPrimitiveTools() const` — Whether the widget should allow primitive tools to be displayed
- L533 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName, FIsSelected InIsSelected);` — Generates a widget for a particular column
- L537 _protected prototype_ `int32 GetGenericThumbnailSize() const;` — Generic ThumbnailSize for the Thumbnail
- L540 _protected prototype_ `bool ShouldAllowAssetStatusOverlay(bool bForceGenericThumbnail) const;` — Get if AssetStatus should be visible
- L543 _protected prototype_ `bool ShouldAllowAssetActionOverlay(bool bForceGenericThumbnail) const;` — Get if AssetAction should be visible
- L546 _protected prototype_ `bool ShouldAllowAssetActionOverlayIndicator(bool bForceGenericThumbnail) const;` — Get if the AssetAction indicator should be visible
- L550 _private prototype_ `TSharedRef<SWidget> GenerateWidgetForColumnNewStyle(const FName& ColumnName, FIsSelected InIsSelected);` — New Style columns generation
- L553 _private prototype_ `float GetExtraStateIconWidth() const;` — Get the expected width of an extra state icon.
- L556 _private prototype_ `FOptionalSize GetExtraStateIconMaxSize() const;` — Returns the max size to be used by extra state icons.
- L559 _private prototype_ `FOptionalSize GetStateIconImageSize() const;` — Returns the size of the state icon box widget (i.e dirty image, scc)
- L562 _private prototype_ `FOptionalSize GetThumbnailBoxSize() const;` — Returns the size of the thumbnail widget
- L565 _private prototype_ `FSlateColor GetColumnTextColor(FIsSelected InIsSelected) const;` — Get the text color for the columns
- L568 _private prototype_ `FText GetAssetPathText() const;` — Gets the path to this asset
- L571 _private prototype_ `FText GetAssetTagText(FName InTag) const;` — Gets the value for the specified tag in this asset
- L574 _private prototype_ `int32 GetWidgetSwitcherIndex() const;` — Get the index to use for the Thumbnail WidgetSwitcher, based on the ThumbnailSize
- L577 _private prototype_ `EVisibility GetDirtyBadgeVisibility() const;` — Get the visibility of the dirty badge in the list view based on the current size
- L581 _private member_ `TSharedPtr<FAssetThumbnail> AssetThumbnail;` — The handle to the thumbnail that this item is rendering
- L584 _private member_ `TAttribute<float> ItemHeight;` — The height allowed for this item
- L587 _private member_ `float ThumbnailPadding;` — The padding for the thumbnail
- L590 _private member_ `TSharedPtr<SWidget> ThumbnailWidget;` — The actual widget for the thumbnail
- L593 _private member_ `TAttribute<FText> HighlightText;` — The string in the title to highlight (used when searching by string)
- L596 _private member_ `FIsSelected IsSelectedExclusively;` — Whether the item is selected in the view without anything else being selected
- L599 _private member_ `TAttribute<EThumbnailSize> CurrentThumbnailSize;` — Current thumbnail size when this widget was generated
- L602 _private member_ `TSharedPtr<STextBlock> PathTextWidget;` — Path text widget, need to be updated when the AssetData changes

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SAssetListViewRow>`  
_L607-610_
- L87 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SAssetListViewRow`  
`class SAssetListViewRow : public SMultiColumnTableRow< TSharedPtr<FAssetViewItem> >`  
_L612-709_
- inherits: `SMultiColumnTableRow<TSharedPtr<FAssetViewItem>>`
- L615 _public function_ `SLATE_BEGIN_ARGS( SAssetListViewRow ) : _Padding(FMargin(0.f))`
- L619 _public function_ `SLATE_STYLE_ARGUMENT( FTableRowStyle, Style ) SLATE_EVENT( FOnDragDetected, OnDragDetected ) SLATE_ARGUMENT( TSharedPtr<SAssetListItem>, AssetListItem ) SLATE_ATTRIBUTE( FMargin, Padding ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView )`
- L641 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override`
- L654 _public function_ `virtual FVector2D GetRowSizeForColumn(const FName& InColumnName) const override`
- L666 _public function_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override`
- L671 _public function_ `virtual TSharedPtr<IToolTip> GetToolTip() override`
- L676 _public function_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L681 _public function_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override`
- L686 _public function_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L691 _public function_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L696 _public function_ `virtual bool OnVisualizeTooltip(const TSharedPtr<SWidget>& TooltipContent) override`
- L703 _public function_ `virtual void OnToolTipClosing() override`
- L708 _public member_ `TSharedPtr<SAssetListItem> AssetListItem;`

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SAssetTileItem>`  
_L712-715_
- L87 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SAssetTileItem`  
`class SAssetTileItem : public SAssetViewItem`  
_L718-923_
- inherits: `SAssetViewItem`
- desc: An item in the asset tile view
- L723 _public function_ `SLATE_BEGIN_ARGS( SAssetTileItem ) : _ThumbnailPadding(0) , _ThumbnailDimension(64) , _ThumbnailLabel( EThumbnailLabel::ClassName ) , _ThumbnailHintColorAndOpacity( FLinearColor( 0.0f, 0.0f, 0.0f, 0.0f ) ) , _AllowThumbnailHintLabel(true) , _CurrentThumbnailSize(EThumbnailSize::Medium) , _ItemWidth(16) , _ShouldAllowToolTip(true) , _ShowType(true) , _ThumbnailEditMode(false) , _ShowAssetAccessSpecifier(false)`
- L739 _public prototype_ `SLATE_ARGUMENT( TSharedPtr<FAssetThumbnail>, AssetThumbnail) SLATE_ARGUMENT( TSharedPtr<FAssetViewItem>, AssetItem ) SLATE_ARGUMENT( float, ThumbnailPadding ) SLATE_ATTRIBUTE(float, ThumbnailDimension) SLATE_ARGUMENT( EThumbnailLabel::Type, ThumbnailLabel ) SLATE_ATTRIBUTE( FLinearColor, ThumbnailHintColorAndOpacity ) SLATE_ARGUMENT( bool, AllowThumbnailHintLabel ) SLATE_ATTRIBUTE(EThumbnailSize, CurrentThumbnailSize) SLATE_ATTRIBUTE( float, ItemWidth ) SLATE_EVENT( FOnRenameBegin, OnRenameBegin ) SLATE_EVENT( FOnRenameCommit, OnRenameCommit ) SLATE_EVENT( FOnVerifyRenameCommit, OnVerifyRenameCommit ) SLATE_EVENT( FOnItemDestroyed, OnItemDestroyed ) SLATE_ATTRIBUTE( bool, ShouldAllowToolTip )` — The handle to the thumbnail this item should render
- L816 _public prototype_ `void Construct( const FArguments& InArgs );` — Constructs this widget with InArgs
- L819 _public prototype_ `virtual void OnAssetDataChanged() override;` — Handles committing a name change
- L822 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Handles realtime thumbnails
- L825 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;` — Handles realtime thumbnails
- L828 _public function_ `bool CanDisplayPrimitiveTools() const` — Whether the widget should allow primitive tools to be displayed
- L831 _public prototype_ `virtual const FSlateBrush* GetBorderImage() const;` — Get the border image to display
- L833 _public prototype_ `static void InitializeAssetNameHeights();`
- L834 _public function_ `static float GetRegularFontHeight()`
- L835 _public function_ `static float GetSmallFontHeight()`
- L839 _protected prototype_ `virtual void OnRequestingRename();` — Called when requesting renaming
- L842 _protected function_ `virtual float GetNameTextWrapWidth() const override` — SAssetViewItem interface
- L845 _protected prototype_ `float GetExtraStateIconWidth() const;` — Get the expected width of an extra state icon.
- L848 _protected prototype_ `FOptionalSize GetExtraStateIconMaxSize() const;` — Returns the max size to be used by extra state icons.
- L851 _protected prototype_ `FOptionalSize GetStateIconImageSize() const;` — Returns the size of the state icon box widget (i.e dirty image, scc)
- L854 _protected prototype_ `FOptionalSize GetThumbnailBoxSize() const;` — Returns the size of the thumbnail widget
- L857 _protected prototype_ `FOptionalSize GetTinyFolderNameWidth() const;` — Returns the width of the tiny folder name overlay widget
- L860 _protected prototype_ `EVisibility GetTinyFolderNameOverlayVisibility() const;` — Gets the visibility of the folder name overlay on the folder icon
- L863 _protected prototype_ `EVisibility GetAssetClassLabelVisibility() const;` — Gets the visibility of the asset class label in thumbnails
- L866 _protected prototype_ `FSlateColor GetAssetClassLabelTextColor() const;` — Gets the color of the asset class label in thumbnails
- L869 _protected prototype_ `FSlateFontInfo GetThumbnailFont() const;` — Returns the font to use for the thumbnail label
- L871 _protected prototype_ `const FSlateBrush* GetFolderSlotBackgroundImage() const;`
- L872 _protected prototype_ `const FSlateBrush* GetFolderBackgroundImage() const;`
- L873 _protected prototype_ `const FSlateBrush* GetFolderBackgroundShadowImage() const;`
- L875 _protected prototype_ `const FSlateBrush* GetNameAreaBackgroundImage() const;`
- L876 _protected prototype_ `const FSlateBrush* GetAssetAreaOverlayBackgroundImage() const;`
- L877 _protected prototype_ `FSlateColor GetNameAreaTextColor() const;`
- L879 _protected prototype_ `FOptionalSize GetNameAreaMaxDesiredHeight() const;`
- L882 _protected prototype_ `int32 GetGenericThumbnailSize() const;` — Generic ThumbnailSize for the Thumbnail
- L885 _protected prototype_ `EVisibility GetSCCIconVisibility() const;` — Gets the visibility of the SCC icons
- L888 _protected prototype_ `EVisibility GetNameAreaVisibility() const;` — Get the visibility for the name area, collapsed if Tiny
- L891 _protected prototype_ `FOptionalSize GetSourceControlIconSize() const;` — Return the size of the class text at the bottom, based on the current ThumbnailSize
- L895 _private member_ `TSharedPtr<SWidget> Thumbnail;` — Thumbnail Widget or Folder image holder
- L898 _private member_ `bool bShowType;` — If false, the tooltip will not be displayed
- L901 _private member_ `TSharedPtr<FAssetThumbnail> AssetThumbnail;` — The handle to the thumbnail that this item is rendering
- L904 _private member_ `TAttribute<float> ItemWidth;` — The width of the item. Used to enforce a square thumbnail.
- L907 _private member_ `TAttribute<float> ThumbnailDimension;` — Actual size that the thumbnail should have
- L910 _private member_ `static float AssetNameHeights[(int32)EThumbnailSize::MAX];` — Max name height for each thumbnail size
- L913 _private member_ `static float RegularFontHeight;` — Regular thumbnail font size
- L916 _private member_ `static float SmallFontHeight;` — Small thumbnail font size
- L919 _private member_ `float ThumbnailPadding;` — The padding allotted for the thumbnail
- L922 _private member_ `TAttribute<EThumbnailSize> CurrentThumbnailSize;` — Current thumbnail size when this widget was generated

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SAssetColumnItem>`  
_L926-929_
- L87 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SAssetColumnItem`  
`class SAssetColumnItem : public SAssetViewItem`  
_L932-998_
- inherits: `SAssetViewItem`
- desc: An item in the asset column view
- L935 _public function_ `SLATE_BEGIN_ARGS( SAssetColumnItem ) : _ShowAssetAccessSpecifier(false)`
- L940 _public prototype_ `SLATE_ARGUMENT( TSharedPtr<FAssetViewItem>, AssetItem ) SLATE_ARGUMENT(bool, ShowAssetAccessSpecifier) SLATE_EVENT( FOnRenameBegin, OnRenameBegin ) SLATE_EVENT( FOnRenameCommit, OnRenameCommit ) SLATE_EVENT( FOnVerifyRenameCommit, OnVerifyRenameCommit ) SLATE_EVENT( FOnItemDestroyed, OnItemDestroyed ) SLATE_ATTRIBUTE( FText, HighlightText ) SLATE_EVENT(FOnIsAssetValidForCustomToolTip, OnIsAssetValidForCustomToolTip) SLATE_EVENT( FOnGetCustomAssetToolTip, OnGetCustomAssetToolTip) SLATE_EVENT( FOnVisualizeAssetToolTip, OnVisualizeAssetToolTip) SLATE_EVENT( FOnAssetToolTipClosing, OnAssetToolTipClosing ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — Data for the asset this item represents
- L978 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName, FIsSelected InIsSelected );` — Generates a widget for a particular column
- L981 _public prototype_ `virtual void OnAssetDataChanged() override;` — Handles committing a name change
- L985 _private prototype_ `FText GetAssetPathText() const;` — Gets the path to this asset
- L988 _private prototype_ `FText GetAssetTagText(FName Tag) const;` — Gets the value for the specified tag in this asset
- L991 _private prototype_ `FSlateColor GetColumnTextColor(FIsSelected InIsSelected) const;` — Get the text color for the columns
- L994 _private member_ `TAttribute<FText> HighlightText;`
- L996 _private member_ `TSharedPtr<STextBlock> ClassText;`
- L997 _private member_ `TSharedPtr<STextBlock> PathText;`

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SAssetColumnViewRow>`  
_L1002-1005_
- L87 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SAssetColumnViewRow`  
`class SAssetColumnViewRow : public SMultiColumnTableRow< TSharedPtr<FAssetViewItem> >`  
_L1007-1100_
- inherits: `SMultiColumnTableRow<TSharedPtr<FAssetViewItem>>`
- L1010 _public function_ `SLATE_BEGIN_ARGS( SAssetColumnViewRow )`
- L1013 _public function_ `SLATE_EVENT( FOnDragDetected, OnDragDetected ) SLATE_ARGUMENT( TSharedPtr<SAssetColumnItem>, AssetColumnItem ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView )`
- L1032 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override`
- L1045 _public function_ `virtual FVector2D GetRowSizeForColumn(const FName& InColumnName) const override`
- L1057 _public function_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override`
- L1062 _public function_ `virtual TSharedPtr<IToolTip> GetToolTip() override`
- L1067 _public function_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L1072 _public function_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override`
- L1077 _public function_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L1082 _public function_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L1087 _public function_ `virtual bool OnVisualizeTooltip(const TSharedPtr<SWidget>& TooltipContent) override`
- L1094 _public function_ `virtual void OnToolTipClosing() override`
- L1099 _public member_ `TSharedPtr<SAssetColumnItem> AssetColumnItem;`

#### Free symbols / members of external scopes

- L64 _delegate_ `DECLARE_DELEGATE_ThreeParams( FOnRenameBegin, const TSharedPtr<FAssetViewItem>& , const FString& , const FSlateRect& ) DECLARE_DELEGATE_FourParams( FOnRenameCommit, const TSharedPtr<FAssetViewItem>& , const FString& , const FSlateRect& , ETextCommit::Type ) DECLARE_DELEGATE_RetVal_FourParams( bool, FOnVerifyRenameCommit, const TSharedPtr<FAssetViewItem>& , const FText& , const FSlateRect& , FText& ) DECLARE_DELEGATE_OneParam( FOnItemDestroyed, const TSharedPtr<FAssetViewItem>& );`
- L64 _prototype_ `DECLARE_DELEGATE_ThreeParams( FOnRenameBegin, const TSharedPtr<FAssetViewItem>& , const FString& , const FSlateRect& ) DECLARE_DELEGATE_FourParams( FOnRenameCommit, const TSharedPtr<FAssetViewItem>& , const FString& , const FSlateRect& , ETextCommit::Type ) DECLARE_DELEGATE_RetVal_FourParams( bool, FOnVerifyRenameCommit, const TSharedPtr<FAssetViewItem>& , const FText& , const FSlateRect& , FText& ) DECLARE_DELEGATE_OneParam( FOnItemDestroyed, const TSharedPtr<FAssetViewItem>& );`
- L65 _delegate_ `DECLARE_DELEGATE_FourParams( FOnRenameCommit, const TSharedPtr<FAssetViewItem>& , const FString& , const FSlateRect& , ETextCommit::Type ) DECLARE_DELEGATE_RetVal_FourParams( bool, FOnVerifyRenameCommit, const TSharedPtr<FAssetViewItem>& , const FText& , const FSlateRect& , FText& ) DECLARE_DELEGATE_OneParam( FOnItemDestroyed, const TSharedPtr<FAssetViewItem>& );`
- L66 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams( bool, FOnVerifyRenameCommit, const TSharedPtr<FAssetViewItem>& , const FText& , const FSlateRect& , FText& ) DECLARE_DELEGATE_OneParam( FOnItemDestroyed, const TSharedPtr<FAssetViewItem>& );`
- L67 _delegate_ `DECLARE_DELEGATE_OneParam( FOnItemDestroyed, const TSharedPtr<FAssetViewItem>& );`

### `Source/Editor/ContentBrowser/Public/ContentBrowserDelegates.h` (Public)


#### struct `FAssetViewDragAndDropExtender`  
`struct FAssetViewDragAndDropExtender`  
_L171-219_
- desc: Contains the delegates used to handle a custom drag-and-drop in the asset view
- L194 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDropDelegate, const FPayload&);`
- L195 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDragOverDelegate, const FPayload&);`
- L196 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDragLeaveDelegate, const FPayload&);`
- L198 _public function_ `FAssetViewDragAndDropExtender(FOnDropDelegate InOnDropDelegate) : OnDropDelegate(MoveTemp(InOnDropDelegate)) , OnDragOverDelegate() , OnDragLeaveDelegate()`
- L204 _public function_ `FAssetViewDragAndDropExtender(FOnDropDelegate InOnDropDelegate, FOnDragOverDelegate InOnDragOverDelegate) : OnDropDelegate(MoveTemp(InOnDropDelegate)) , OnDragOverDelegate(MoveTemp(InOnDragOverDelegate)) , OnDragLeaveDelegate()`
- L210 _public function_ `FAssetViewDragAndDropExtender(FOnDropDelegate InOnDropDelegate, FOnDragOverDelegate InOnDragOverDelegate, FOnDragLeaveDelegate InOnDragLeaveDelegate) : OnDropDelegate(MoveTemp(InOnDropDelegate)) , OnDragOverDelegate(MoveTemp(InOnDragOverDelegate)) , OnDragLeaveDelegate(MoveTemp(InOnDragLeaveDelegate))`
- L216 _public member_ `FOnDropDelegate OnDropDelegate;`
- L217 _public member_ `FOnDragOverDelegate OnDragOverDelegate;`
- L218 _public member_ `FOnDragLeaveDelegate OnDragLeaveDelegate;`

#### struct `FAssetViewDragAndDropExtender::FPayload`  
`struct FPayload`  
_L173-192_
- L175 _public prototype_ `FPayload(TSharedPtr<FDragDropOperation> InDragDropOp, const TArray<FName>& InPackagePaths, const TArray<FCollectionRef>& InCollectionSources);`
- L178 _public prototype_ `FPayload(TSharedPtr<FDragDropOperation> InDragDropOp, const TArray<FName>& InPackagePaths, const TArray<FCollectionNameType>& InCollections);` — `UE_DEPRECATED(5.6, "Use the FCollectionRef overload instead.")`
- L180 _public member_ `TSharedPtr<FDragDropOperation> DragDropOp;`
- L183 _private member_ `TArray<FCollectionRef> TempCollectionSources;`
- L184 _private member_ `TArray<FCollectionNameType> TempCollections;`
- L187 _public member_ `const TArray<FName>& PackagePaths;`
- L188 _public member_ `const TArray<FCollectionRef>& CollectionSources;`
- L191 _public member_ `const TArray<FCollectionNameType> Collections;` — `UE_DEPRECATED(5.6, "Use CollectionSources instead.")`

#### struct `FAssetViewCustomColumn`  
`struct FAssetViewCustomColumn`  
_L222-254_
- desc: Struct to define a custom column for the asset view
- L225 _public member_ `FName ColumnName;` — Internal name of the column
- L228 _public member_ `FText DisplayName;` — Display name of the column
- L231 _public member_ `FText TooltipText;` — Tooltip for the column
- L234 _public member_ `UObject::FAssetRegistryTag::ETagType DataType;` — Type of column, used for sorting
- L237 _public member_ `FOnGetCustomAssetColumnData OnGetColumnData;` — Delegate to get String value for this column, used for sorting and internal use
- L240 _public member_ `FOnGetCustomAssetColumnDisplayText OnGetColumnDisplayText;` — Delegate to get Text value for this column, used to actually display
- L242 _public function_ `FAssetViewCustomColumn() : DataType(UObject::FAssetRegistryTag::TT_Alphabetical)`
- L246 _public function_ `FAssetViewCustomColumn(FName InColumnName, const FText& InDisplayName, const FText& InTooltipText, UObject::FAssetRegistryTag::ETagType InDataType, const FOnGetCustomAssetColumnData& InOnGetColumnData, const FOnGetCustomAssetColumnDisplayText& InOnGetColumnDisplayText = FOnGetCustomAssetColumnDisplayText()) : ColumnName(InColumnName) , DisplayName(InDisplayName) , TooltipText(InTooltipText) , DataType(InDataType) , OnGetColumnData(InOnGetColumnData) , OnGetColumnDisplayText(InOnGetColumnDisplayText)`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FOnContentBrowserItemRenameCommitted, TArrayView<const FContentBrowserItem> );` — Called when the user has committed a rename of one or more items
- L22 _prototype_ `DECLARE_DELEGATE_OneParam(FOnContentBrowserItemRenameCommitted, TArrayView<const FContentBrowserItem> );` — Called when the user has committed a rename of one or more items
- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnContentBrowserItemSelectionChanged, const FContentBrowserItem& , ESelectInfo::Type );` — Delegate called when item selection is changed
- L25 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnContentBrowserItemSelectionChanged, const FContentBrowserItem& , ESelectInfo::Type );` — Delegate called when item selection is changed
- L28 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnContentBrowserItemsActivated, TArrayView<const FContentBrowserItem> , EAssetTypeActivationMethod::Type );` — Called when the user double clicks, presses enter, or presses space on a Content Browser item
- L28 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnContentBrowserItemsActivated, TArrayView<const FContentBrowserItem> , EAssetTypeActivationMethod::Type );` — Called when the user double clicks, presses enter, or presses space on a Content Browser item
- L31 _delegate_ `DECLARE_DELEGATE_OneParam(FOnContentBrowserItemsDragged, TArrayView<const FContentBrowserItem> );` — Called when the user drags one or more Content Browser items
- L31 _prototype_ `DECLARE_DELEGATE_OneParam(FOnContentBrowserItemsDragged, TArrayView<const FContentBrowserItem> );` — Called when the user drags one or more Content Browser items
- L34 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGetContentBrowserItemContextMenu, TArrayView<const FContentBrowserItem> );` — Called to request the menu when right clicking on an selection of items (maybe be a mix of folders and files)
- L34 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGetContentBrowserItemContextMenu, TArrayView<const FContentBrowserItem> );` — Called to request the menu when right clicking on an selection of items (maybe be a mix of folders and files)
- L37 _delegate_ `DECLARE_DELEGATE_OneParam( FOnCollectionSelected, const FCollectionNameType& );` — Called when a collection is selected in the collections view
- L37 _prototype_ `DECLARE_DELEGATE_OneParam( FOnCollectionSelected, const FCollectionNameType& );` — Called when a collection is selected in the collections view
- L40 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef< SToolTip >, FConstructToolTipForAsset, const FAssetData& );` — Called to retrieve the tooltip for the specified asset
- L40 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef< SToolTip >, FConstructToolTipForAsset, const FAssetData& );` — Called to retrieve the tooltip for the specified asset
- L43 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterAsset, const FAssetData& );` — Called to check if an asset should be filtered out by external code. Return true to exclude the asset from the view.
- L43 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterAsset, const FAssetData& );` — Called to check if an asset should be filtered out by external code. Return true to exclude the asset from the view.
- L46 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterItem, const FContentBrowserItem& );` — Called to check if an item should be filtered out by external code. Return true to exclude the item from the view.
- L46 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterItem, const FContentBrowserItem& );` — Called to check if an item should be filtered out by external code. Return true to exclude the item from the view.
- L49 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnShouldDisplayAssetTag, FName , FName );` — Called to check if an asset tag should be display in details view. Return false to exclude the asset from the view.
- L49 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnShouldDisplayAssetTag, FName , FName );` — Called to check if an asset tag should be display in details view. Return false to exclude the asset from the view.
- L52 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSearchTextChanged, const FText& ) DECLARE_DELEGATE( FClearSelectionDelegate );` — Fired when the search box text changes. Allows embedding widgets to observe the search text without replacing the built-in search behavior.
- L52 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSearchTextChanged, const FText& ) DECLARE_DELEGATE( FClearSelectionDelegate );` — Fired when the search box text changes. Allows embedding widgets to observe the search text without replacing the built-in search behavior.
- L55 _delegate_ `DECLARE_DELEGATE( FClearSelectionDelegate );` — Called to clear the selection of the specified assetdata or all selection if an invalid assetdata is passed
- L58 _delegate_ `DECLARE_DELEGATE_OneParam( FOnThumbnailScaleChanged, const float );` — Called when thumbnail scale changes and the thumbnail scale is bound to a delegate
- L58 _prototype_ `DECLARE_DELEGATE_OneParam( FOnThumbnailScaleChanged, const float );` — Called when thumbnail scale changes and the thumbnail scale is bound to a delegate
- L61 _delegate_ `DECLARE_DELEGATE_RetVal( TArray< FAssetData >, FGetCurrentSelectionDelegate );` — Called to retrieve an array of the currently selected asset data
- L61 _prototype_ `DECLARE_DELEGATE_RetVal( TArray< FAssetData >, FGetCurrentSelectionDelegate );` — Called to retrieve an array of the currently selected asset data
- L64 _delegate_ `DECLARE_DELEGATE_OneParam(FSyncToAssetsDelegate, const TArray< FAssetData >& );` — Called to retrieve an array of the currently selected asset data
- L64 _prototype_ `DECLARE_DELEGATE_OneParam(FSyncToAssetsDelegate, const TArray< FAssetData >& );` — Called to retrieve an array of the currently selected asset data
- L67 _delegate_ `DECLARE_DELEGATE_OneParam(FRefreshAssetViewDelegate, bool );` — Called to force the asset view to refresh
- L67 _prototype_ `DECLARE_DELEGATE_OneParam(FRefreshAssetViewDelegate, bool );` — Called to force the asset view to refresh
- L70 _delegate_ `DECLARE_DELEGATE(FSaveAssetViewSettingsDelegate);` — Called to save the asset view settings (column widths, sort order, hidden columns, etc.)
- L70 _prototype_ `DECLARE_DELEGATE(FSaveAssetViewSettingsDelegate);` — Called to save the asset view settings (column widths, sort order, hidden columns, etc.)
- L73 _delegate_ `DECLARE_DELEGATE(FLoadAssetViewSettingsDelegate);` — Called to load/restore the asset view settings
- L73 _prototype_ `DECLARE_DELEGATE(FLoadAssetViewSettingsDelegate);` — Called to load/restore the asset view settings
- L76 _delegate_ `DECLARE_DELEGATE_OneParam(FSetARFilterDelegate, const FARFilter& );` — Called to set a new filter for an existing asset picker
- L76 _prototype_ `DECLARE_DELEGATE_OneParam(FSetARFilterDelegate, const FARFilter& );` — Called to set a new filter for an existing asset picker
- L79 _delegate_ `DECLARE_DELEGATE_OneParam(FSetPathPickerPathsDelegate, const TArray<FString>& );` — A pointer to an existing delegate that, when executed, will set the filter an the asset picker after it is created.
- L79 _prototype_ `DECLARE_DELEGATE_OneParam(FSetPathPickerPathsDelegate, const TArray<FString>& );` — A pointer to an existing delegate that, when executed, will set the filter an the asset picker after it is created.
- L82 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAssetSelected, const FAssetData& );` — Called when an asset is selected in the asset view
- L82 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAssetSelected, const FAssetData& );` — Called when an asset is selected in the asset view
- L85 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnAssetsActivated, const TArray<FAssetData>& , EAssetTypeActivationMethod::Type );` — Called when the user double clicks, presses enter, or presses space on an asset
- L85 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnAssetsActivated, const TArray<FAssetData>& , EAssetTypeActivationMethod::Type );` — Called when the user double clicks, presses enter, or presses space on an asset
- L88 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAssetsDragged, const TArray<FAssetData>& );` — Called when asset(s) are dragged in the asset view
- L88 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAssetsDragged, const TArray<FAssetData>& );` — Called when asset(s) are dragged in the asset view
- L91 _delegate_ `DECLARE_DELEGATE_OneParam(FOnColumnVisibilityChanged, const TArray<FString>& );` — Called when the user changes which columns are hidden in the asset column/list view
- L91 _prototype_ `DECLARE_DELEGATE_OneParam(FOnColumnVisibilityChanged, const TArray<FString>& );` — Called when the user changes which columns are hidden in the asset column/list view
- L94 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAssetDoubleClicked, const FAssetData& );` — Called when an asset is double clicked in the asset view
- L94 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAssetDoubleClicked, const FAssetData& );` — Called when an asset is double clicked in the asset view
- L97 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAssetEnterPressed, const TArray<FAssetData>& );` — Called when enter is pressed on an asset in the asset view
- L97 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAssetEnterPressed, const TArray<FAssetData>& );` — Called when enter is pressed on an asset in the asset view
- L100 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCreateNewFolder, const FContentBrowserItemTemporaryContext& );` — Called when a new folder is starting to be created
- L100 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCreateNewFolder, const FContentBrowserItemTemporaryContext& );` — Called when a new folder is starting to be created
- L103 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeleteFolders, const TArray<FContentBrowserItemPath>& );` — Called when one or more folders are being deleted
- L103 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeleteFolders, const TArray<FContentBrowserItemPath>& );` — Called when one or more folders are being deleted
- L106 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGetAssetContextMenu, const TArray<FAssetData>& );` — Called to request the menu when right clicking on an asset
- L106 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGetAssetContextMenu, const TArray<FAssetData>& );` — Called to request the menu when right clicking on an asset
- L109 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPathSelected, const FString& );` — Called when a path is selected in the path picker
- L109 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPathSelected, const FString& );` — Called when a path is selected in the path picker
- L112 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnContentBrowserGetSelection, TArray<FAssetData>& , TArray<FString>& );` — Called when registering a custom command/keybinding for the content browser
- L112 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnContentBrowserGetSelection, TArray<FAssetData>& , TArray<FString>& );` — Called when registering a custom command/keybinding for the content browser
- L113 _delegate_ `DECLARE_DELEGATE_TwoParams(FContentBrowserCommandExtender, TSharedRef<FUICommandList> , FOnContentBrowserGetSelection );`
- L113 _prototype_ `DECLARE_DELEGATE_TwoParams(FContentBrowserCommandExtender, TSharedRef<FUICommandList> , FOnContentBrowserGetSelection );`
- L116 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<FExtender>, FContentBrowserMenuExtender);` — Called to request the menu when right clicking on a path
- L116 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<FExtender>, FContentBrowserMenuExtender);` — Called to request the menu when right clicking on a path
- L117 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<FExtender>, FContentBrowserMenuExtender_SelectedAssets, const TArray<FAssetData>& );`
- L117 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<FExtender>, FContentBrowserMenuExtender_SelectedAssets, const TArray<FAssetData>& );`
- L118 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<FExtender>, FContentBrowserMenuExtender_SelectedPaths, const TArray<FString>& );`
- L118 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<FExtender>, FContentBrowserMenuExtender_SelectedPaths, const TArray<FString>& );`
- L121 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnContentBrowserCanShowSetAssetAccessMenu, const FStringView , const FAssetData& );` — Called to check if should show menu entries to set asset public/private
- L121 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnContentBrowserCanShowSetAssetAccessMenu, const FStringView , const FAssetData& );` — Called to check if should show menu entries to set asset public/private
- L124 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(TSharedPtr<SWidget>, FOnGetFolderContextMenu, const TArray<FString>& , FContentBrowserMenuExtender_SelectedPaths , FOnCreateNewFolder );` — Called to request the menu when right clicking on an asset
- L124 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(TSharedPtr<SWidget>, FOnGetFolderContextMenu, const TArray<FString>& , FContentBrowserMenuExtender_SelectedPaths , FOnCreateNewFolder );` — Called to request the menu when right clicking on an asset
- L127 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnIsAssetValidForCustomToolTip, FAssetData& );` — Called to see if it is valid to request a custom asset item tooltip
- L127 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnIsAssetValidForCustomToolTip, FAssetData& );` — Called to see if it is valid to request a custom asset item tooltip
- L130 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<SToolTip>, FOnGetCustomAssetToolTip, FAssetData& );` — Called to request a custom asset item tooltip
- L130 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<SToolTip>, FOnGetCustomAssetToolTip, FAssetData& );` — Called to request a custom asset item tooltip
- L133 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FString, FOnGetCustomAssetColumnData, FAssetData& , FName );` — Called to get string/text value for a custom column, will get converted as necessary
- L133 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FString, FOnGetCustomAssetColumnData, FAssetData& , FName );` — Called to get string/text value for a custom column, will get converted as necessary
- L134 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FText, FOnGetCustomAssetColumnDisplayText, FAssetData& , FName );`
- L134 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FText, FOnGetCustomAssetColumnDisplayText, FAssetData& , FName );`
- L137 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnGenerateAssetViewExtraStateIndicators, const FAssetData& );` — Called to generate extra state information icons or tooltips on asset items.
- L137 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnGenerateAssetViewExtraStateIndicators, const FAssetData& );` — Called to generate extra state information icons or tooltips on asset items.
- L140 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FPathViewStateIconGenerator, const FContentBrowserItem& );` — Called to generate state information icons for path view items.
- L140 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FPathViewStateIconGenerator, const FContentBrowserItem& );` — Called to generate state information icons for path view items.
- L144 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FGetItemDataAttribute, const FContentBrowserItemData& , const bool , const FName , FContentBrowserItemDataAttributeValue& );`
- L147 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnVisualizeAssetToolTip, const TSharedPtr<SWidget>& , FAssetData& );` — Called when an asset item visualizes its tooltip
- L147 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnVisualizeAssetToolTip, const TSharedPtr<SWidget>& , FAssetData& );` — Called when an asset item visualizes its tooltip
- L150 _delegate_ `DECLARE_DELEGATE(FOnAssetDialogCancelled);` — Called from the Asset Dialog when a non-modal dialog is closed or cancelled
- L150 _prototype_ `DECLARE_DELEGATE(FOnAssetDialogCancelled);` — Called from the Asset Dialog when a non-modal dialog is closed or cancelled
- L153 _delegate_ `DECLARE_DELEGATE( FOnAssetToolTipClosing );` — Called when an asset item's tooltip is closing
- L153 _prototype_ `DECLARE_DELEGATE( FOnAssetToolTipClosing );` — Called when an asset item's tooltip is closing
- L156 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAssetsChosenForOpen, const TArray<FAssetData>& );` — Called from the Asset Dialog when assets are chosen in non-modal Open dialogs
- L156 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAssetsChosenForOpen, const TArray<FAssetData>& );` — Called from the Asset Dialog when assets are chosen in non-modal Open dialogs
- L159 _delegate_ `DECLARE_DELEGATE_OneParam(FOnObjectPathChosenForSave, const FString& );` — Called from the Asset Dialog when an asset name is chosen in non-modal Save dialogs
- L159 _prototype_ `DECLARE_DELEGATE_OneParam(FOnObjectPathChosenForSave, const FString& );` — Called from the Asset Dialog when an asset name is chosen in non-modal Save dialogs
- L162 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsFolderShowPrivateContentToggleableDelegate, const FStringView );` — Called when custom behavior is needed for allowing folders to toggle their private content edit state
- L162 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsFolderShowPrivateContentToggleableDelegate, const FStringView );` — Called when custom behavior is needed for allowing folders to toggle their private content edit state
- L165 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetFolderColor, const FString& ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFavoritesChanged, const FContentBrowserItemPath& , bool ) struct FAssetViewDragAndDropExtender { struct FPayload { FPayload(TSharedPtr<FDragDropOperation> InDragDropOp, const TArray<FName>& InPackagePaths, const TArray<FCollectionRef>& InCollectionSources); UE_DEPRECATED(5.6, "Use the FCollectionRef overload instead.") FPayload(TSharedPtr<FDragDropOperation> InDragDropOp, const TArray<FName>& InPackagePaths, const TArray<FCollectionNameType>& InCollections); TSharedPtr<FDragDropOperation> DragDropOp; private: TArray<FCollectionRef> TempCollectionSources; TArray<FCollectionNameType> TempCollections; public: const TArray<FName>& PackagePaths; const TArray<FCollectionRef>& CollectionSources; UE_DEPRECATED(5.6, "Use CollectionSources instead.") const TArray<FCollectionNameType> Collections; }; DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDropDelegate, const FPayload&); DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDragOverDelegate, const FPayload&); DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDragLeaveDelegate, const FPayload&); FAssetViewDragAndDropExtender(FOnDropDelegate InOnDropDelegate) : OnDropDelegate(MoveTemp(InOnDropDelegate)) , OnDragOverDelegate() , OnDragLeaveDelegate() { } FAssetViewDragAndDropExtender(FOnDropDelegate InOnDropDelegate, FOnDragOverDelegate InOnDragOverDelegate)` — Called when a custom folder color is set on a folder
- L168 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFavoritesChanged, const FContentBrowserItemPath& , bool ) struct FAssetViewDragAndDropExtender { struct FPayload { FPayload(TSharedPtr<FDragDropOperation> InDragDropOp, const TArray<FName>& InPackagePaths, const TArray<FCollectionRef>& InCollectionSources); UE_DEPRECATED(5.6, "Use the FCollectionRef overload instead.") FPayload(TSharedPtr<FDragDropOperation> InDragDropOp, const TArray<FName>& InPackagePaths, const TArray<FCollectionNameType>& InCollections); TSharedPtr<FDragDropOperation> DragDropOp; private: TArray<FCollectionRef> TempCollectionSources; TArray<FCollectionNameType> TempCollections; public: const TArray<FName>& PackagePaths; const TArray<FCollectionRef>& CollectionSources; UE_DEPRECATED(5.6, "Use CollectionSources instead.") const TArray<FCollectionNameType> Collections; }; DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDropDelegate, const FPayload&); DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDragOverDelegate, const FPayload&); DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDragLeaveDelegate, const FPayload&); FAssetViewDragAndDropExtender(FOnDropDelegate InOnDropDelegate) : OnDropDelegate(MoveTemp(InOnDropDelegate)) , OnDragOverDelegate() , OnDragLeaveDelegate() { } FAssetViewDragAndDropExtender(FOnDropDelegate InOnDropDelegate, FOnDragOverDelegate InOnDragOverDelegate) : OnDropDelegate(MoveTemp(InOnDropDelegate)) , OnDragOverDelegate(MoveTemp(InOnDragOverDelegate)) , OnDragLeaveDelegate()` — Called when an item is added or removed from favorites
- L194 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDropDelegate, const FPayload&);`
- L195 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDragOverDelegate, const FPayload&);`
- L196 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDragLeaveDelegate, const FPayload&);`

### `Source/Editor/ContentBrowser/Public/ContentBrowserFrontEndFilterExtension.h` (Public)


#### class `UContentBrowserFrontEndFilterExtension`  
`class UContentBrowserFrontEndFilterExtension : public UObject`  
_L13-20_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Override this class in order to make an additional front-end filter available in the Content Browser
- L19 _public function_ `virtual void AddFrontEndFilterExtensions(TSharedPtr<class FFrontendFilterCategory> DefaultCategory, TArray< TSharedRef<class FFrontendFilter> >& InOutFilterList) const` — Override this method to add new frontend filters

### `Source/Editor/ContentBrowser/Public/ContentBrowserInstanceUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CONTENTBROWSER_API`
- L10 _namespace_ `namespace ContentBrowserInstanceUtils`
- L13 _prototype_ `TArray<FName> GetConfigNames();` (scope `ContentBrowserInstanceUtils`) — Gets a list of names for all existing content browser configs
- L16 _prototype_ `void SaveAllConfigs();` (scope `ContentBrowserInstanceUtils`) — Saves all content browser configs
- L21 _prototype_ `bool GetShowPluginContent(const FName& InstanceName);` (scope `ContentBrowserInstanceUtils`) — Gets whether we are allowed to display plugin content @param InstanceName Instance name of the content browser
- L28 _prototype_ `void SetShowPluginContent(const FName& InstanceName, const bool bInShowPluginContent, const bool bInSaveConfig = true);` (scope `ContentBrowserInstanceUtils`) — Sets whether we are allowed to display plugin content @param InstanceName Instance name of the content browser to be modified @param bInShowPluginContent True to display plugin content @param bInSaveConfig True to save the config after modification
- L33 _prototype_ `bool GetShowLocalizedContent(const FName& InstanceName);` (scope `ContentBrowserInstanceUtils`) — Gets whether we are allowed to display localized content @param InstanceName Instance name of the content browser
- L40 _prototype_ `void SetShowLocalizedContent(const FName& InstanceName, const bool bInShowLocalizedContent, const bool bInSaveConfig = true);` (scope `ContentBrowserInstanceUtils`) — Sets whether we are allowed to display localized content @param InstanceName Instance name of the content browser to be modified @param bInShowLocalizedContent True to display localized content @param bInSaveConfig True to save the config after modification
- L45 _prototype_ `bool GetShowEngineContent(const FName& InstanceName);` (scope `ContentBrowserInstanceUtils`) — Gets whether we are allowed to display engine content @param InstanceName Instance name of the content browser
- L52 _prototype_ `void SetShowEngineContent(const FName& InstanceName, const bool bInShowEngineContent, const bool bInSaveConfig = true);` (scope `ContentBrowserInstanceUtils`) — Sets whether we are allowed to display engine content @param InstanceName Instance name of the content browser to be modified @param bInShowEngineContent True to display engine content @param bInSaveConfig True to save the config after modification
- L57 _prototype_ `bool GetShowDeveloperContent(const FName& InstanceName);` (scope `ContentBrowserInstanceUtils`) — Gets whether we are allowed to display developer content @param InstanceName Instance name of the content browser
- L64 _prototype_ `void SetShowDeveloperContent(const FName& InstanceName, const bool bInShowDeveloperContent, const bool bInSaveConfig = true);` (scope `ContentBrowserInstanceUtils`) — Sets whether we are allowed to display developer content @param InstanceName Instance name of the content browser to be modified @param bInShowDeveloperContent True to display developer content @param bInSaveConfig True to save the config after modification
- L69 _prototype_ `bool GetShowCppFolders(const FName& InstanceName);` (scope `ContentBrowserInstanceUtils`) — Gets whether we are allowed to display cpp folders @param InstanceName Instance name of the content browser
- L76 _prototype_ `void SetShowCppFolders(const FName& InstanceName, const bool bInShowCppFolders, const bool bInSaveConfig = true);` (scope `ContentBrowserInstanceUtils`) — Sets whether we are allowed to display cpp folders @param InstanceName Instance name of the content browser to be modified @param bInShowCppFolders True to display cpp folders @param bInSaveConfig True to save the config after modification
- L81 _prototype_ `bool GetShowFavorites(const FName& InstanceName);` (scope `ContentBrowserInstanceUtils`) — Gets whether we are allowed to display favorites @param InstanceName Instance name of the content browser
- L88 _prototype_ `void SetShowFavorites(const FName& InstanceName, const bool bInShowFavorites, const bool bInSaveConfig = true);` (scope `ContentBrowserInstanceUtils`) — Sets whether we are allowed to display favorites @param InstanceName Instance name of the content browser to be modified @param bInShowFavorites True to display favorites @param bInSaveConfig True to save the config after modification
- L93 _prototype_ `bool GetFavoritesExpanded(const FName& InstanceName);` (scope `ContentBrowserInstanceUtils`) — Gets whether we are allowed to expand favorites @param InstanceName Instance name of the content browser
- L100 _prototype_ `void SetFavoritesExpanded(const FName& InstanceName, const bool bInFavoritesExpanded, const bool bInSaveConfig = true);` (scope `ContentBrowserInstanceUtils`) — Sets whether we are allowed to expand favorites @param InstanceName Instance name of the content browser to be modified @param bInFavoritesExpanded True to expand favorites @param bInSaveConfig True to save the config after modification
- L105 _prototype_ `bool GetSourcesExpanded(const FName& InstanceName);` (scope `ContentBrowserInstanceUtils`) — Gets whether we are allowed to expand sources @param InstanceName Instance name of the content browser
- L112 _prototype_ `void SetSourcesExpanded(const FName& InstanceName, const bool bInSourcesExpanded, const bool bInSaveConfig = true);` (scope `ContentBrowserInstanceUtils`) — Sets whether we are allowed to expand sources @param InstanceName Instance name of the content browser to be modified @param bInSourcesExpanded True to expand sources @param bInSaveConfig True to save the config after modification
- L117 _prototype_ `bool GetFilterRecursively(const FName& InstanceName);` (scope `ContentBrowserInstanceUtils`) — Gets whether we are allowed to filter recursively when a filter is applied @param InstanceName Instance name of the content browser
- L124 _prototype_ `void SetFilterRecursively(const FName& InstanceName, const bool bInFilterRecursively, const bool bInSaveConfig = true);` (scope `ContentBrowserInstanceUtils`) — Sets whether we are allowed to filter recursively when a filter is applied @param InstanceName Instance name of the content browser to be modified @param bInFilterRecursively True to filter recursively @param bInSaveConfig True to save the config after modification
- L129 _prototype_ `bool GetShowFolders(const FName& InstanceName);` (scope `ContentBrowserInstanceUtils`) — Gets whether we are allowed to display folders @param InstanceName Instance name of the content browser
- L136 _prototype_ `void SetShowFolders(const FName& InstanceName, const bool bInShowFolders, const bool bInSaveConfig = true);` (scope `ContentBrowserInstanceUtils`) — Sets whether we are allowed to display folders @param InstanceName Instance name of the content browser to be modified @param bInShowFolders True to display folders @param bInSaveConfig True to save the config after modification
- L141 _prototype_ `bool GetShowEmptyFolders(const FName& InstanceName);` (scope `ContentBrowserInstanceUtils`) — Gets whether we are allowed to display empty folders @param InstanceName Instance name of the content browser
- L148 _prototype_ `void SetShowEmptyFolders(const FName& InstanceName, const bool bInShowEmptyFolders, const bool bInSaveConfig = true);` (scope `ContentBrowserInstanceUtils`) — Sets whether we are allowed to display empty folders @param InstanceName Instance name of the content browser to be modified @param bInShowEmptyFolders True to display empty folders @param bInSaveConfig True to save the config after modification
- L153 _prototype_ `bool GetSearchClasses(const FName& InstanceName);` (scope `ContentBrowserInstanceUtils`) — Gets whether we are allowed to search in asset class names @param InstanceName Instance name of the content browser
- L160 _prototype_ `void SetSearchClasses(const FName& InstanceName, const bool bInSearchClasses, const bool bInSaveConfig = true);` (scope `ContentBrowserInstanceUtils`) — Sets whether we are allowed to search in asset class names @param InstanceName Instance name of the content browser to be modified @param bInSearchClasses True to search in asset class names @param bInSaveConfig True to save the config after modification
- L165 _prototype_ `bool GetSearchAssetPaths(const FName& InstanceName);` (scope `ContentBrowserInstanceUtils`) — Gets whether we are allowed to search asset paths (instead of asset name only) @param InstanceName Instance name of the content browser
- L172 _prototype_ `void SetSearchAssetPaths(const FName& InstanceName, const bool bInSearchAssetPaths, const bool bInSaveConfig = true);` (scope `ContentBrowserInstanceUtils`) — Sets whether we are allowed to search asset paths (instead of asset name only) @param InstanceName Instance name of the content browser to be modified @param bInSearchAssetPaths True to search asset paths @param bInSaveConfig True to save the config after modification
- L177 _prototype_ `bool GetSearchCollections(const FName& InstanceName);` (scope `ContentBrowserInstanceUtils`) — Gets whether we are allowed to search for collection names @param InstanceName Instance name of the content browser
- L184 _prototype_ `void SetSearchCollections(const FName& InstanceName, const bool bInSearchCollections, const bool bInSaveConfig = true);` (scope `ContentBrowserInstanceUtils`) — Sets whether we are allowed to search for collection names @param InstanceName Instance name of the content browser to be modified @param bInSearchCollections True to search for collection names @param bInSaveConfig True to save the config after modification

### `Source/Editor/ContentBrowser/Public/ContentBrowserMenuContexts.h` (Public)


#### enum `EIncludeSubclasses`  
`enum class EIncludeSubclasses : uint8`  
_L34-38_
- L36 _public enumerator_ `No`
- L37 _public enumerator_ `Yes`

#### class `UContentBrowserAssetContextMenuContext`  
`class UContentBrowserAssetContextMenuContext : public UObject`  
_L41-265_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L47 _public member_ `TWeakPtr<FAssetContextMenu> AssetContextMenu;`
- L50 _public member_ `TWeakPtr<IAssetTypeActions> CommonAssetTypeActions;` — `UE_DEPRECATED(5.2, "IAssetTypeActions (CommonAssetTypeActions) is being phased out too much menu related stuff was built into their design that forced loading assets. Please use UAssetDefinition (CommonAssetDefinition).")`
- L53 _public member_ `TObjectPtr<const UAssetDefinition> CommonAssetDefinition;` — `UPROPERTY()`
- L59 _public member_ `TArray<FAssetData> SelectedAssets;` — `UPROPERTY(BlueprintReadOnly, Category="Tool Menus")` — The currently selected assets in the content browser.
- L62 _public member_ `TObjectPtr<UClass> CommonClass;` — `UPROPERTY()`
- L65 _public member_ `bool bCanBeModified;` — `UPROPERTY()`
- L68 _public member_ `bool bCanView;` — `UPROPERTY()`
- L71 _public member_ `bool bHasCookedPackages;` — `UPROPERTY()`
- L74 _public member_ `bool bContainsUnsupportedAssets = true;` — `UPROPERTY(BlueprintReadOnly, Category = ContentBrowser)`
- L78 _public function_ `TArray<UObject*> GetSelectedObjects() const` — `UE_DEPRECATED(5.5, "GetSelectedObjects has been deprecated. We no longer automatically load assets on right click. Please use SelectedAssets and determine whatever you need for your context menu options without actually loading the assets. When you finally need all or a subset of the selected assets use LoadSelectedAssets or LoadSelectedAssetsIf")` — `UFUNCTION(BlueprintCallable, Category="Tool Menus", meta=(DeprecatedFunction, DeprecationMessage = "GetSelectedObjects has been deprecated. We no longer automatically load assets on right click. If you can work without loading the assets, please use SelectedAssets. Otherwise call LoadSelectedObjects"))`
- L84 _public function_ `template<typename ExpectedAssetType> TArray<ExpectedAssetType*> GetSelectedObjectsInMemory() const`
- L110 _public prototype_ `TArray<UObject*> LoadSelectedObjectsIfNeeded() const;` — `UFUNCTION(BlueprintCallable, Category="Tool Menus")` — Loads the selected assets (if needed) which is based on AssetViewUtils::LoadAssetsIfNeeded, this exists primarily for backwards compatability.  Reliance on a black box to determine 'neededness' is not recommended, this function will likely be deprecated a few versions after GetSelectedObjects.
- L116 _public function_ `TArray<UObject*> LoadSelectedObjects(TSet<FName> LoadTags) const` — `UFUNCTION(BlueprintCallable, Category="Tool Menus")` — Loads all the selected assets and returns an array of the objects.
- L125 _public function_ `template<typename ExpectedAssetType> TArray<ExpectedAssetType*> LoadSelectedObjects(TSet<FName> LoadTags = {}) const` — Loads all the selected assets and returns an array of the ExpectedAssetType.
- L134 _public function_ `template<typename ExpectedAssetType> TArray<ExpectedAssetType*> LoadSelectedObjectsIf(TFunctionRef<bool(const FAssetData& AssetData)> PredicateFilter) const` — Loads the selected assets if the PredicateFilter returns true, and returns an array of the objects.
- L143 _public function_ `template<typename ExpectedAssetType> TArray<ExpectedAssetType*> LoadSelectedObjectsIf(TSet<FName> LoadTags, TFunctionRef<bool(const FAssetData& AssetData)> PredicateFilter) const` — Loads the selected assets if the PredicateFilter returns true, and returns an array of the objects.
- L170 _public function_ `template<typename ExpectedAssetType> ExpectedAssetType* LoadFirstSelectedObject(const TSet<FName>& LoadTags = {}) const` — Loads the first selected valid asset and returns it.
- L189 _public prototype_ `TArray<FAssetData> GetSelectedAssetsOfType(const UClass* AssetClass, EIncludeSubclasses IncludeSubclasses = EIncludeSubclasses::Yes) const;` — Returns a filtered array of assets that are of the desired class and potentially any subclasses.
- L196 _public prototype_ `const FAssetData* GetSingleSelectedAssetOfType(const UClass* AssetClass, EIncludeSubclasses IncludeSubclasses = EIncludeSubclasses::Yes) const;` — Sometimes you want to write actions that will only operate on a singular selected asset, in those cases you can use the following function which will only return a live ptr if it's an instance of that asset type, and only one thing is selected.
- L202 _public function_ `template<typename ExpectedAssetType> TArray<TSoftObjectPtr<ExpectedAssetType>> GetSelectedAssetSoftObjects(EIncludeSubclasses IncludeSubclasses = EIncludeSubclasses::Yes) const` — Get the selected assets as an array of SoftObjectPtr<T>'s.
- L225 _public prototype_ `const TArray<FContentBrowserItem>& GetSelectedItems() const;` — Read-only access to the list of currently selected items
- L232 _public function_ `template<typename MenuOrSectionType> static const UContentBrowserAssetContextMenuContext* FindContextWithAssets(const MenuOrSectionType& MenuOrSection)` — Finds the Content Browser MenuContext from a Menu or Section, and returns the context provided there are some selected assets.
- L244 _public function_ `template<typename MenuOrSectionType> static int32 GetNumAssetsSelected(const MenuOrSectionType& MenuOrSection)`
- L254 _public function_ `template<typename ExpectedType, typename MenuOrSectionType> static ExpectedType* LoadSingleSelectedAsset(const MenuOrSectionType& MenuOrSection)`

#### class `UContentBrowserAssetViewContextMenuContext`  
`class UContentBrowserAssetViewContextMenuContext : public UObject`  
_L268-275_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L273 _public member_ `TWeakPtr<SContentBrowser> OwningContentBrowser;`
- L274 _public member_ `TWeakPtr<SAssetView> AssetView;`

#### class `UContentBrowserAssetSortingContextMenuContext`  
`class UContentBrowserAssetSortingContextMenuContext : public UObject`  
_L278-286_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L283 _public member_ `TWeakPtr<SContentBrowser> OwningContentBrowser;`
- L284 _public member_ `TWeakPtr<SAssetView> AssetView;`
- L285 _public member_ `TWeakPtr<FAssetViewSortManager> AssetViewSortManager;`

#### class `UContentBrowserMenuContext`  
`class UContentBrowserMenuContext : public UObject`  
_L289-296_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L295 _public member_ `TWeakPtr<SContentBrowser> ContentBrowser;`

#### class `UContentBrowserFolderContext`  
`class UContentBrowserFolderContext : public UContentBrowserMenuContext`  
_L299-323_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContentBrowserMenuContext`
- L306 _public member_ `bool bCanBeModified;` — `UPROPERTY(BlueprintReadOnly, Category = "ContentBrowser")`
- L309 _public member_ `bool bNoFolderOnDisk;` — `UPROPERTY(BlueprintReadOnly, Category = "ContentBrowser")`
- L312 _public member_ `int32 NumAssetPaths;` — `UPROPERTY(BlueprintReadOnly, Category = "ContentBrowser")`
- L315 _public member_ `int32 NumClassPaths;` — `UPROPERTY(BlueprintReadOnly, Category = "ContentBrowser")`
- L318 _public member_ `TArray<FString> SelectedPackagePaths;` — `UPROPERTY(BlueprintReadOnly, Category = "ContentBrowser")`
- L320 _public member_ `FOnCreateNewFolder OnCreateNewFolder;`
- L322 _public function_ `const TArray<FString>& GetSelectedPackagePaths() const`

#### class `UContentBrowserAddNewContextMenuContext`  
`class UContentBrowserAddNewContextMenuContext : public UObject`  
_L326-333_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L332 _public member_ `TWeakPtr<SContentBrowser> ContentBrowser;`

#### class `UContentBrowserToolbarMenuContext`  
`class UContentBrowserToolbarMenuContext : public UObject`  
_L336-348_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L341 _public prototype_ `FName GetCurrentPath() const;`
- L343 _public prototype_ `bool CanWriteToCurrentPath() const;`
- L345 _public member_ `TWeakPtr<SContentBrowser> ContentBrowser;`
- L346 _public member_ `TWeakPtr<SAssetView> AssetView;`
- L347 _public member_ `const FContentBrowserConfig* ContentBrowserConfig = nullptr;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API CONTENTBROWSER_API`
- L127 _function_ `return LoadSelectedObjectsIf<ExpectedAssetType>(LoadTags, [](const FAssetData& AssetData){ return true; });` (scope `UContentBrowserAssetContextMenuContext::LoadSelectedObjects`)
- L209 _function_ `Algo::TransformIf(SelectedAssets, Result, [](const FAssetData& AssetData) { return AssetData.IsInstanceOf(ExpectedAssetType::StaticClass()); }, [](const FAssetData& AssetData) { return TSoftObjectPtr<ExpectedAssetType>(AssetData.ToSoftObjectPath()); } );` (scope `UContentBrowserAssetContextMenuContext::GetSelectedAssetSoftObjects`)
- L216 _function_ `Algo::TransformIf(SelectedAssets, Result, [](const FAssetData& AssetData) { return AssetData.GetClass() == ExpectedAssetType::StaticClass(); }, [](const FAssetData& AssetData) { return TSoftObjectPtr<ExpectedAssetType>(AssetData.ToSoftObjectPath()); } );` (scope `UContentBrowserAssetContextMenuContext::GetSelectedAssetSoftObjects`)
- L352 _namespace_ `namespace UE`
- L352 _namespace_ `namespace ContentBrowser` (scope `UE`)
- L354 _prototype_ `UToolMenu* ExtendToolMenu_AssetContextMenu(UClass* AssetClass);` (scope `UE::ContentBrowser`)
- L355 _prototype_ `UToolMenu* ExtendToolMenu_AssetContextMenu(TSoftClassPtr<UObject> AssetSoftClass);` (scope `UE::ContentBrowser`)
- L356 _prototype_ `TArray<UToolMenu*> ExtendToolMenu_AssetContextMenus(TConstArrayView<UClass*> AssetClasses);` (scope `UE::ContentBrowser`)

### `Source/Editor/ContentBrowser/Public/ContentBrowserModule.h` (Public)


#### class `FAssetViewExtraStateGenerator`  
`class FAssetViewExtraStateGenerator`  
_L32-52_
- desc: Extra state generator that adds an icon and a corresponding legend entry on an asset.
- L35 _public function_ `FAssetViewExtraStateGenerator(FOnGenerateAssetViewExtraStateIndicators InIconGenerator, FOnGenerateAssetViewExtraStateIndicators InToolTipGenerator) : IconGenerator(MoveTemp(InIconGenerator)) , ToolTipGenerator(MoveTemp(InToolTipGenerator)) , Handle(FDelegateHandle::GenerateNewHandle)`
- L42 _public member_ `FOnGenerateAssetViewExtraStateIndicators IconGenerator;` — Delegate called to generate an extra icon on an asset view.
- L45 _public member_ `FOnGenerateAssetViewExtraStateIndicators ToolTipGenerator;` — Delegate called to generate an extra tooltip on an asset view.
- L49 _private member_ `FDelegateHandle Handle;` — The handle to this extra state generator.

#### struct `FCollectionCreatedTelemetryEvent`  
`struct FCollectionCreatedTelemetryEvent`  
_L55-61_
- desc: Workflow event when a collection is created
- L57 _public member_ `static inline constexpr FGuid TelemetryID = FGuid(0x2F9C8896, 0xCB2C402B, 0xB8D6DCF1, 0xE3F22D41);`
- L59 _public member_ `double DurationSec = 0.0;`
- L60 _public member_ `ECollectionShareType::Type CollectionShareType = ECollectionShareType::CST_All;`

#### struct `FCollectionsDeletedTelemetryEvent`  
`struct FCollectionsDeletedTelemetryEvent`  
_L64-70_
- desc: Workflow event when a set of collections are deleted
- L66 _public member_ `static inline constexpr FGuid TelemetryID = FGuid(0x1362ABC8, 0x6CDD4FF9, 0xB4B0E06C, 0x2CA418DC);`
- L68 _public member_ `double DurationSec = 0.0;`
- L69 _public member_ `int32 CollectionsDeleted = 0;`

#### enum `ECollectionTelemetryAssetAddedWorkflow`  
`enum class ECollectionTelemetryAssetAddedWorkflow : int32`  
_L72-76_
- L74 _public enumerator_ `ContextMenu = 0`
- L75 _public enumerator_ `DragAndDrop = 1`

#### struct `FAssetAddedToCollectionTelemetryEvent`  
`struct FAssetAddedToCollectionTelemetryEvent`  
_L79-87_
- desc: Workflow event when assets are added to a collection
- L81 _public member_ `static inline constexpr FGuid TelemetryID = FGuid(0x3676C84E, 0xFEB74E21, 0x99FF6FB8, 0x622431D2);`
- L83 _public member_ `double DurationSec;`
- L84 _public member_ `ECollectionShareType::Type CollectionShareType;`
- L85 _public member_ `uint32 NumAdded;`
- L86 _public member_ `ECollectionTelemetryAssetAddedWorkflow Workflow;`

#### enum `ECollectionTelemetryAssetRemovedWorkflow`  
`enum class ECollectionTelemetryAssetRemovedWorkflow : int32`  
_L89-92_
- L91 _public enumerator_ `ContextMenu = 0`

#### struct `FAssetRemovedFromCollectionTelemetryEvent`  
`struct FAssetRemovedFromCollectionTelemetryEvent`  
_L95-103_
- desc: Workflow event when assets are removed from a collection
- L97 _public member_ `static inline constexpr FGuid TelemetryID = FGuid(0xF7660FA4, 0x744F44F5, 0x9B647690, 0x3C5689BD);`
- L99 _public member_ `double DurationSec;`
- L100 _public member_ `ECollectionShareType::Type CollectionShareType;`
- L101 _public member_ `uint32 NumRemoved;`
- L102 _public member_ `ECollectionTelemetryAssetRemovedWorkflow Workflow;`

#### class `FContentBrowserModule`  
`class FContentBrowserModule : public IModuleInterface`  
_L108-317_
- inherits: `IModuleInterface`
- desc: Content browser module
- L114 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams( FOnFilterChanged, const FARFilter& , bool );`
- L116 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams( FOnSearchBoxChanged, const FText& , bool );`
- L118 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams( FOnAssetSelectionChanged, const TArray<FAssetData>& , bool );`
- L120 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam( FOnSourcesViewChanged, bool );`
- L122 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam( FOnAssetPathChanged, const FString& );`
- L124 _public prototype_ `DECLARE_DELEGATE_OneParam( FAddPathViewPluginFilters, TArray<TSharedRef<FContentBrowserPluginFilter>>& );`
- L126 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam( FOnContentBrowserSettingChanged, FName );`
- L128 _public prototype_ `DECLARE_DELEGATE_OneParam( FDefaultSelectedPathsDelegate, TArray<FName>& );`
- L130 _public prototype_ `DECLARE_DELEGATE_OneParam( FDefaultPathsToExpandDelegate, TArray<FName>& );`
- L132 _public prototype_ `DECLARE_DELEGATE_RetVal(TSharedPtr<IContentBrowserViewExtender>, FCreateViewExtender);` — Delegate that creates an instance of the custom view extender
- L137 _public prototype_ `virtual void StartupModule();` — Called right after the plugin DLL has been loaded and the plugin object has been created
- L142 _public prototype_ `virtual void ShutdownModule();` — Called before the plugin is unloaded, right before the plugin object is destroyed.
- L145 _public prototype_ `virtual IContentBrowserSingleton& Get() const;` — Gets the content browser singleton
- L152 _public prototype_ `virtual FDelegateHandle AddAssetViewExtraStateGenerator(const FAssetViewExtraStateGenerator& Generator);` — Add a generator to add extra state functionality to the content browser's assets. @param Generator the delegates that add functionality. @return FDelegateHandle the handle to the extra state generator.
- L158 _public prototype_ `virtual void RemoveAssetViewExtraStateGenerator(const FDelegateHandle& GeneratorHandle);` — Remove an asset view extra state generator. @param GeneratorHandle the extra state generator's handle.
- L161 _public function_ `virtual TArray<FContentBrowserMenuExtender_SelectedPaths>& GetAllAssetContextMenuExtenders()` — Delegates to be called to extend the content browser menus
- L162 _public function_ `virtual TArray<FContentBrowserMenuExtender_SelectedPaths>& GetAllPathViewContextMenuExtenders()`
- L163 _public function_ `virtual TArray<FContentBrowserMenuExtender>& GetAllCollectionListContextMenuExtenders()`
- L164 _public function_ `virtual TArray<FContentBrowserMenuExtender>& GetAllCollectionViewContextMenuExtenders()`
- L165 _public function_ `virtual TArray<FContentBrowserMenuExtender_SelectedAssets>& GetAllAssetViewContextMenuExtenders()`
- L166 _public function_ `virtual TArray<FContentBrowserMenuExtender>& GetAllAssetViewViewMenuExtenders()`
- L167 _public function_ `virtual TArray<FPathViewStateIconGenerator>& GetAllPathViewStateIconGenerators()`
- L170 _public function_ `virtual TArray<FContentBrowserCommandExtender>& GetAllContentBrowserCommandExtenders()` — Delegates to call to extend the command/keybinds for content browser
- L173 _public function_ `virtual const TArray<FAssetViewExtraStateGenerator>& GetAllAssetViewExtraStateGenerators()` — Delegates to be called to add extra state indicators on the asset view
- L176 _public function_ `virtual TArray<FAssetViewDragAndDropExtender>& GetAssetViewDragAndDropExtenders()` — Delegates to be called to extend the drag-and-drop support of the asset view
- L179 _public function_ `virtual TArray<FAddPathViewPluginFilters>& GetAddPathViewPluginFilters()` — Delegates to be called to extend list of content browser Plugin Filters
- L184 _public function_ `virtual TArray<FGetItemDataAttribute>& GetAllItemDataAttributeDelegates()` — Delegates to call to provide the value for a ContentBrowserItemData's attribute
- L188 _public prototype_ `virtual void SetContentBrowserViewExtender(const FCreateViewExtender& InCreateViewExtender);` — Register a delegate that creates a custom view that can show up inside SAssetView in the Content Browser
- L190 _public prototype_ `virtual FCreateViewExtender GetContentBrowserViewExtender();` — Get the currently registered custom view
- L193 _public function_ `FOnFilterChanged& GetOnFilterChanged()` — Delegate accessors
- L194 _public function_ `FOnSearchBoxChanged& GetOnSearchBoxChanged()`
- L195 _public function_ `FOnAssetSelectionChanged& GetOnAssetSelectionChanged()`
- L196 _public function_ `FOnSourcesViewChanged& GetOnSourcesViewChanged()`
- L197 _public function_ `FOnAssetPathChanged& GetOnAssetPathChanged()`
- L198 _public function_ `FOnContentBrowserSettingChanged& GetOnContentBrowserSettingChanged()`
- L199 _public function_ `FOnDeleteFolders& GetOnDeleteFolders()`
- L200 _public function_ `FOnContentBrowserCanShowSetAssetAccessMenu& GetOnContentBrowserCanShowSetAssetAccessMenu()`
- L203 _public function_ `FDefaultSelectedPathsDelegate& GetDefaultSelectedPathsDelegate()` — Override list of paths to select by default
- L206 _public function_ `FDefaultPathsToExpandDelegate& GetDefaultPathsToExpandDelegate()` — Override list of paths to expand by default
- L208 _public prototype_ `FMainMRUFavoritesList* GetRecentlyOpenedAssets() const;`
- L210 _public member_ `static const FName NumberOfRecentAssetsName;`
- L212 _public prototype_ `void RegisterDynamicTagAssetClass(const FTopLevelAssetPath& InClassPathName);`
- L213 _public prototype_ `void UnregisterDynamicTagAssetClass(const FTopLevelAssetPath& InClassPathName);`
- L214 _public prototype_ `bool IsDynamicTagAssetClass(const FTopLevelAssetPath& InClassPathName) const;`
- L217 _public function_ `void AddDynamicTagAssetClass(const FName& InName)` — `UE_DEPRECATED(5.8, "Use the new version of this function, which uses a FTopLevelAssetPath")`
- L219 _public function_ `void RemoveDynamicTagAssetClass(const FName& InName)` — `UE_DEPRECATED(5.8, "Use the new version of this function, which uses a FTopLevelAssetPath")`
- L221 _public function_ `bool IsDynamicTagAssetClass(const FName& InName)` — `UE_DEPRECATED(5.8, "Use the new version of this function, which uses a FTopLevelAssetPath")`
- L223 _public function_ `FOnSetFolderColor& GetOnSetFolderColor()`
- L238 _public prototype_ `void RegisterWizard(const FWizard& InWizard);`
- L239 _public prototype_ `void UnregisterWizard(const FName WizardIdentifier);`
- L240 _public prototype_ `const TArray<FWizard>& GetWizards() const;`
- L245 _public prototype_ `bool RegisterAssetSearchOverride(TUniquePtr<UE::Editor::ContentBrowser::Extension::IAssetSearchOverride>&& InOverride);`
- L250 _public prototype_ `void UnregisterAssetSearchOverride();`
- L255 _public prototype_ `UE::Editor::ContentBrowser::Extension::IAssetSearchOverride* GetActiveAssetSearchOverride() const;`
- L259 _private member_ `TArray<FWizard> Wizards;`
- L262 _private prototype_ `void ContentBrowserSettingChanged(FName InName);` — Handle changes to content browser settings
- L265 _private member_ `TArray<FTopLevelAssetPath> AssetClassesRequiringDynamicTags;` — List of asset classes whose tags are dynamic and therefore we should union all asset's tags rather than grabbing the first available.
- L268 _private member_ `FOnSetFolderColor OnSetFolderColor;` — Called when a custom folder color is set on a folder
- L271 _private member_ `IContentBrowserSingleton* ContentBrowserSingleton;`
- L272 _private member_ `TSharedPtr<class FContentBrowserSpawner> ContentBrowserSpawner;`
- L275 _private member_ `TArray<FContentBrowserMenuExtender_SelectedPaths> AssetContextMenuExtenders;` — All extender delegates for the content browser menus
- L276 _private member_ `TArray<FContentBrowserMenuExtender_SelectedPaths> PathViewContextMenuExtenders;`
- L277 _private member_ `TArray<FContentBrowserMenuExtender> CollectionListContextMenuExtenders;`
- L278 _private member_ `TArray<FContentBrowserMenuExtender> CollectionViewContextMenuExtenders;`
- L279 _private member_ `TArray<FContentBrowserMenuExtender_SelectedAssets> AssetViewContextMenuExtenders;`
- L280 _private member_ `TArray<FContentBrowserMenuExtender> AssetViewViewMenuExtenders;`
- L281 _private member_ `TArray<FPathViewStateIconGenerator> PathViewStateIconGenerators;`
- L282 _private member_ `TArray<FContentBrowserCommandExtender> ContentBrowserCommandExtenders;`
- L285 _private member_ `TArray<FAssetViewExtraStateGenerator> AssetViewExtraStateGenerators;` — All delegates generating extra state indicators
- L288 _private member_ `TArray<FAssetViewDragAndDropExtender> AssetViewDragAndDropExtenders;` — All extender delegates for the drag-and-drop support of the asset view
- L291 _private member_ `TArray<FAddPathViewPluginFilters> PathViewPluginFilters;` — All delegates that extend available path view plugin filters
- L295 _private member_ `TArray<FGetItemDataAttribute> ItemDataAttributeDelegates;` — All delegates that return values for ContentItemData attributes
- L298 _private member_ `FOnFilterChanged OnFilterChanged;`
- L299 _private member_ `FOnSearchBoxChanged OnSearchBoxChanged;`
- L300 _private member_ `FOnAssetSelectionChanged OnAssetSelectionChanged;`
- L301 _private member_ `FOnSourcesViewChanged OnSourcesViewChanged;`
- L302 _private member_ `FOnAssetPathChanged OnAssetPathChanged;`
- L303 _private member_ `FOnContentBrowserSettingChanged OnContentBrowserSettingChanged;`
- L304 _private member_ `FOnDeleteFolders OnDeleteFolders;`
- L306 _private member_ `FDefaultSelectedPathsDelegate DefaultSelectedPathsDelegate;`
- L307 _private member_ `FDefaultPathsToExpandDelegate DefaultPathsToExpandDelegate;`
- L310 _private member_ `FCreateViewExtender ContentBrowserViewExtender;` — Extension used to provide a custom view to the Content Browser
- L313 _private member_ `TUniquePtr<UE::Editor::ContentBrowser::Extension::IAssetSearchOverride> ActiveAssetSearchOverride = nullptr;` — The currently active asset search override, if any. Only one may be registered at a time.
- L316 _private member_ `FOnContentBrowserCanShowSetAssetAccessMenu OnContentBrowserCanShowSetAssetAccessMenu;` — Override to selectively hide menu entries for viewing and setting asset as Public/Private

#### struct `FContentBrowserModule::FWizard`  
`struct FWizard`  
_L228-236_
- L230 _public member_ `FName WizardIdentifier;`
- L231 _public member_ `FText DisplayName;`
- L232 _public member_ `FText Description;`
- L233 _public member_ `FSlateIcon Icon;`
- L234 _public member_ `FAdvancedAssetCategory CategoryPath;`
- L235 _public member_ `FSimpleDelegate OnOpen;`

#### Free symbols / members of external scopes

- L114 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams( FOnFilterChanged, const FARFilter& , bool );`
- L116 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams( FOnSearchBoxChanged, const FText& , bool );`
- L118 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams( FOnAssetSelectionChanged, const TArray<FAssetData>& , bool );`
- L120 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam( FOnSourcesViewChanged, bool );`
- L122 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam( FOnAssetPathChanged, const FString& );`
- L124 _delegate_ `DECLARE_DELEGATE_OneParam( FAddPathViewPluginFilters, TArray<TSharedRef<FContentBrowserPluginFilter>>& );`
- L126 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam( FOnContentBrowserSettingChanged, FName );`
- L128 _delegate_ `DECLARE_DELEGATE_OneParam( FDefaultSelectedPathsDelegate, TArray<FName>& );`
- L130 _delegate_ `DECLARE_DELEGATE_OneParam( FDefaultPathsToExpandDelegate, TArray<FName>& );`
- L132 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedPtr<IContentBrowserViewExtender>, FCreateViewExtender);` — Delegate that creates an instance of the custom view extender

### `Source/Editor/ContentBrowser/Public/ContentBrowserPluginFilters.h` (Public)


#### class `FContentBrowserPluginFilter`  
`class FContentBrowserPluginFilter : public IFilter<FPluginFilterType>`  
_L19-66_
- inherits: `IFilter<FPluginFilterType>`
- L24 _public prototype_ `virtual FString GetName() const = 0;` — Returns the system name for this filter
- L27 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Returns the human readable name for this filter
- L30 _public prototype_ `virtual FText GetToolTipText() const = 0;` — Returns the tooltip for this filter, shown in the filters menu
- L33 _public function_ `virtual FLinearColor GetColor() const` — Returns the color this filter button will be when displayed as a button
- L36 _public function_ `virtual FName GetIconName() const` — Returns the name of the icon to use in menu entries
- L39 _public function_ `virtual bool IsInverseFilter() const` — Returns true if the filter should be in the list when disabled and not in the list when enabled
- L42 _public function_ `virtual void ActiveStateChanged(bool bActive)` — Notification that the filter became active or inactive
- L45 _public function_ `virtual void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const` — Called when the state of a particular Content Browser is being saved to INI
- L48 _public function_ `virtual void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString)` — Called when the state of a particular Content Browser is being loaded from INI
- L51 _public function_ `void SetActive(bool bInActive)` — Set this filter as active/inactive
- L54 _public prototype_ `DECLARE_DERIVED_EVENT( FContentBrowserPluginFilter, IFilter<FPluginFilterType>::FChangedEvent, FChangedEvent );` — IFilter implementation
- L55 _public function_ `virtual FChangedEvent& OnChanged() override`
- L58 _protected function_ `void BroadcastChangedEvent() const`
- L61 _private member_ `FChangedEvent ChangedEvent;`
- L64 _private prototype_ `DECLARE_EVENT_OneParam(FContentBrowserPluginFilter, FSetActiveEvent, bool);` — This event is broadcast to set this filter active in the content browser it is being used in
- L65 _private member_ `FSetActiveEvent SetActiveEvent;`

#### class `FContentBrowserPluginFilter_ContentOnlyPlugins`  
`class FContentBrowserPluginFilter_ContentOnlyPlugins : public FContentBrowserPluginFilter`  
_L68-78_
- inherits: `FContentBrowserPluginFilter`
- L72 _public function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L73 _public function_ `virtual FText GetDisplayName() const override`
- L74 _public function_ `virtual FText GetToolTipText() const override`
- L77 _public prototype_ `virtual bool PassesFilter(FPluginFilterType InItem) const override;` — IFilter implementation

#### Free symbols / members of external scopes

- L17 _macro_ `#define LOCTEXT_NAMESPACE "ContentBrowser"`
- L54 _delegate_ `DECLARE_DERIVED_EVENT( FContentBrowserPluginFilter, IFilter<FPluginFilterType>::FChangedEvent, FChangedEvent );` — IFilter implementation
- L64 _delegate_ `DECLARE_EVENT_OneParam(FContentBrowserPluginFilter, FSetActiveEvent, bool);` — This event is broadcast to set this filter active in the content browser it is being used in

### `Source/Editor/ContentBrowser/Public/ContentBrowserTelemetry.h` (Public)


#### struct `UE::Telemetry::ContentBrowser::FBackendFilterTelemetry`  
`struct FBackendFilterTelemetry`  
_L14-36_
- L16 _public member_ `static inline constexpr FGuid TelemetryID = FGuid(0x3a026bff,0x041444d0, 0x9457c4e5, 0x1378d03c);`
- L18 _public function_ `FBackendFilterTelemetry(FGuid InViewCorrelationGuid, FGuid InFilterSessionCorrelationGuid) : ViewCorrelationGuid(InViewCorrelationGuid) , FilterSessionCorrelationGuid(InFilterSessionCorrelationGuid)`
- L25 _public member_ `FGuid ViewCorrelationGuid;` — Guid assigned to the originating instance of SAssetView
- L27 _public member_ `FGuid FilterSessionCorrelationGuid;` — Guid assigned to this set of backend items for correlation with frontend filtering
- L29 _public member_ `bool bHasCustomItemSources = false;` — Whether this view had a delegate bound for providing custom items
- L31 _public member_ `double RefreshSourceItemsDurationSeconds = 0.0;` — Wall-clock duration of fetching all items from the backend
- L33 _public member_ `int32 NumBackendItems = 0;` — Number of items returned from the backend
- L35 _public member_ `const FContentBrowserDataFilter* DataFilter = nullptr;` — Optional pointer to the filter passed to the backend - not to be stored past the lifetime of the telemetry handler.

#### struct `UE::Telemetry::ContentBrowser::FFrontendFilterTelemetry`  
`struct FFrontendFilterTelemetry`  
_L38-75_
- L40 _public member_ `static inline constexpr FGuid TelemetryID = FGuid(0xee47ffd0, 0x86c74117, 0x86416a64, 0x85460b31);`
- L42 _public function_ `FFrontendFilterTelemetry()`
- L46 _public function_ `FFrontendFilterTelemetry(FGuid InViewCorrelationGuid, FGuid InFilterSessionCorrelationGuid) : ViewCorrelationGuid(InViewCorrelationGuid) , FilterSessionCorrelationGuid(InFilterSessionCorrelationGuid)`
- L53 _public member_ `FGuid ViewCorrelationGuid = FGuid();` — Guid assigned to the originating instance of SAssetView
- L55 _public member_ `FGuid FilterSessionCorrelationGuid = FGuid();` — Guid assigned to the set of backend items the frontend is filtering here
- L57 _public member_ `int32 TotalItemsToFilter = 0;` — The total number of items returned from the backend that needed filtering
- L59 _public member_ `int32 PriorityItemsToFilter = 0;` — The number of items that were required to be filtered immediately
- L61 _public member_ `int32 TotalResults = 0;` — Total number of items that passed the filters
- L63 _public member_ `double AmortizeDuration = 0.0;` — Wall clock duration of filtering all items
- L65 _public member_ `double WorkDuration = 0.0;` — Actual cumulative tick time of filtering
- L67 _public member_ `TOptional<double> ResultLatency;` — Latency until first result is added (if any results were found)
- L69 _public member_ `TOptional<double> TimeUntilInteraction;` — Time until user interacted with filter results - e.g. opened an asset from the list, even if filtering was not complete
- L71 _public member_ `bool bCompleted = false;` — Whether this filtering session completed before being interrupted/cancelled in some way
- L74 _public member_ `TSharedPtr<FAssetFilterCollectionType> FrontendFilters;` — 'Frontend' filter (amortized in asset view tick) 'Backend' filter data is available in backend items telemetry - requires correlation

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Telemetry` (scope `UE`)
- L12 _namespace_ `namespace ContentBrowser` (scope `UE::Telemetry`)

### `Source/Editor/ContentBrowser/Public/ContentSources/Columns/ContentSourcesColumns.h` (Public)


#### struct `FContentSourceColumn`  
`struct FContentSourceColumn : public FEditorDataStorageColumn`  
_L14-19_
- reflection: `USTRUCT(meta = (DisplayName = "Content Source"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column added to a widget row that contains a pointer to the content source the widget belongs to
- L18 _public member_ `TWeakPtr<UE::Editor::ContentBrowser::IContentSource> ContentSource;`

### `Source/Editor/ContentBrowser/Public/ContentSources/IContentSource.h` (Public)


#### struct `UE::Editor::ContentBrowser::FTableViewerInitParams`  
`struct FTableViewerInitParams`  
_L17-30_
- desc: Init Params used by the STedsTableViewer displayed in place of the legacy Content Browser when this content source is active
- L20 _public member_ `DataStorage::FQueryDescription QueryDescription;` — Query description to populate the rows of the table viewer
- L23 _public member_ `TArray<TWeakObjectPtr<const UScriptStruct>> Columns;` — The columns shown in the table viewer
- L26 _public member_ `DataStorage::IUiProvider::FPurposeID CellWidgetPurpose;` — The widget purposes used by the table viewer to display the widgets in the cells
- L29 _public member_ `ETableViewMode::Type TableViewMode = ETableViewMode::Type::List;` — The table view type to use, currently only supports list and tile

#### class `UE::Editor::ContentBrowser::IContentSource`  
`class IContentSource`  
_L42-64_
- desc: A Content Source is a construct that can customize the look and behavior of the content browser through TEDS (Editor Data Storage) intended to replace the legacy asset specific content browser. Currently supports displaying an STedsTableViewer driven by a query specified by the content source in place of the legacy content browser layout and widgets Content Sources can be registered with IContentBrowserSingleton which will cause them to be displayed in a vertical toolbar next to the Content Browser allowing a user to select and activate them. NOTE: This API is experimental and subject to change
- L45 _public prototype_ `virtual ~IContentSource() = default;`
- L48 _public prototype_ `virtual FName GetName() = 0;` — Get the internal name of the content source
- L51 _public prototype_ `virtual FText GetDisplayName() = 0;` — Get the user facing name of the content source
- L54 _public prototype_ `virtual FSlateIcon GetIcon() = 0;` — Get an icon representing the content source
- L57 _public prototype_ `virtual void GetAssetViewInitParams(FTableViewerInitParams& OutInitParams) = 0;` — Get the init params used by the TEDS Table Viewer when this content source is active
- L60 _public function_ `virtual void OnContentSourceEnabled()` — Called when this content source is switched in
- L63 _public function_ `virtual void OnContentSourceDisabled()` — Called when this content source is swapped out

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)

### `Source/Editor/ContentBrowser/Public/Experimental/ContentBrowserExtensionUtils.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)
- L11 _namespace_ `namespace ExtensionUtils` (scope `UE::Editor::ContentBrowser`)

### `Source/Editor/ContentBrowser/Public/Experimental/ContentBrowserSearchOverride.h` (Public)


#### class `UE::Editor::ContentBrowser::Extension::ICBSearchOverrideInstance`  
`class ICBSearchOverrideInstance`  
_L21-98_
- desc: Interface to contains the state per view of the search override
- L24 _public prototype_ `ICBSearchOverrideInstance();`
- L25 _public prototype_ `virtual ~ICBSearchOverrideInstance();`
- L27 _public prototype_ `bool IsOverrideActive() const;`
- L28 _public prototype_ `void ToggleOverride();`
- L34 _public prototype_ `void SetUserSearching(bool bIsSearching);` — Call from the override to notify the Content Browser to update the asset view's user-searching state. Pass true when a search is in progress, false when results are cleared.
- L40 _public prototype_ `void RequestQuickFrontendListRefresh();` — Call from the override to trigger a quick frontend list refresh on the asset view. Use this when the search query changes so the filter pipeline re-runs immediately.
- L42 _public prototype_ `virtual TSharedRef<class SWidget> GetOverrideModeToggleWidget() = 0;`
- L45 _public prototype_ `virtual void OnSearchTextChanged(const FText& NewText) = 0;` — Called when the search box text changes, only when IsOverrideActive() returns true.
- L48 _public prototype_ `virtual void OnSearchTextCommitted(const FText& NewText, ETextCommit::Type CommitType) = 0;` — Called when the search box text is committed, only when IsOverrideActive() returns true.
- L55 _public prototype_ `virtual void OnItemsAvailable(TArrayView<const TSharedPtr<FAssetViewItem>> Items) = 0;` — Called each filter pass with all items that passed the frontend filters. The override is responsible for deciding which of these to surface via PublishResults().
- L57 _public prototype_ `virtual void SortItemList(TArrayView<TSharedPtr<FAssetViewItem>> Items) = 0;`
- L63 _public function_ `virtual bool IsSortOverridden() const` — Returns true if the override wants to handle sorting instead of the default Content Browser sort manager. When false, SortItemList will not be called.
- L69 _public function_ `virtual bool HasPendingResults() const` — Returns true while the override has async work in flight whose results have not yet been published. The asset view will keep ticking while this is true.
- L75 _public prototype_ `void PublishResults(TArrayView<TSharedPtr<FAssetViewItem>> Items);` — Call when results are ready. The asset view will inject these items into the visible set on the next tick.
- L78 _public prototype_ `class FInternalApiWrapper& GetInternalApi();` — Private API for ContentBrowser internals.
- L88 _protected prototype_ `virtual void OnFilteringResetImplementation() = 0;` — Called at the start of each filter pass when the override is active. Override to reset any pending state before new items start arriving.
- L93 _protected prototype_ `virtual void OnAllKnownItemsAvailableImplementation() = 0;` — Called when the extension has received all the known items that it has to process.
- L96 _private member_ `bool bIsOverrideActive = false;`
- L97 _private member_ `TUniquePtr<FInternalApiWrapper> InternalApi;`

#### class `UE::Editor::ContentBrowser::Extension::IAssetSearchOverride`  
`class IAssetSearchOverride`  
_L105-111_
- desc: Interface for an asset search override that can hook into the Content Browser's filter and sort pipeline. Only one override may be active at any given time.
- L108 _public prototype_ `virtual ~IAssetSearchOverride() = default;`
- L110 _public prototype_ `virtual TSharedRef<ICBSearchOverrideInstance> MakePerViewOverride() const = 0;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)
- L16 _namespace_ `namespace Extension` (scope `UE::Editor::ContentBrowser`)

### `Source/Editor/ContentBrowser/Public/Experimental/ContentBrowserViewExtender.h` (Public)


#### class `IContentBrowserViewExtender`  
`class IContentBrowserViewExtender`  
_L16-65_
- desc: Interface that can be used to add a custom view to the Content Browser NOTE: This API is likely to change as it is being actively iterated on
- L20 _public prototype_ `virtual TSharedRef<SWidget> CreateView(TArray<TSharedPtr<FAssetViewItem>>* InItemsSource) = 0;` — Create the widget for the view with the given input items
- L22 _public prototype_ `virtual ~IContentBrowserViewExtender() = default;`
- L25 _public prototype_ `virtual void OnItemListChanged(TArray<TSharedPtr<FAssetViewItem>>* InItemsSource) = 0;` — Function called when the items source has some changes and the view needs a refresh
- L27 _public typedef_ `using FOnSelectionChanged = TSlateDelegates<TSharedPtr<FAssetViewItem>>::FOnSelectionChanged;`
- L29 _public prototype_ `virtual FOnSelectionChanged& OnSelectionChanged() = 0;` — Delegate the extender must fire when the selection in the UI changes
- L31 _public typedef_ `using FOnItemScrolledIntoView = TSlateDelegates<TSharedPtr<FAssetViewItem>>::FOnItemScrolledIntoView;`
- L33 _public prototype_ `virtual FOnItemScrolledIntoView& OnItemScrolledIntoView() = 0;` — Delegate the extender must fire when an item is scrolled into view in the UI
- L35 _public typedef_ `using FOnMouseButtonClick = TSlateDelegates<TSharedPtr<FAssetViewItem>>::FOnMouseButtonClick;`
- L37 _public prototype_ `virtual FOnMouseButtonClick& OnItemDoubleClicked() = 0;` — Delegate the extender must fire when an item is double clicked
- L40 _public prototype_ `virtual FOnContextMenuOpening& OnContextMenuOpened() = 0;` — Delegate the extender must fire when the context menu is opened on the list
- L43 _public prototype_ `virtual TArray<TSharedPtr<FAssetViewItem>> GetSelectedItems() = 0;` — Get the items selected by the custom view
- L46 _public prototype_ `virtual void SetSelection(const TSharedPtr<FAssetViewItem>& Item, bool bSelected, const ESelectInfo::Type SelectInfo) = 0;` — Select the given item in the view
- L49 _public prototype_ `virtual void ClearSelection() = 0;` — Clear the current selection in the view
- L52 _public prototype_ `virtual void FocusList() = 0;` — Transfer focus to the internal view widget
- L55 _public prototype_ `virtual void RequestScrollIntoView(const TSharedPtr<FAssetViewItem>& Item) = 0;` — Scroll the given item into view
- L58 _public prototype_ `virtual bool IsRightClickScrolling() = 0;` — true if the view is currently right click scrolling
- L61 _public prototype_ `virtual FText GetViewDisplayName() = 0;` — Get a display name for the view used in the Settings menu
- L64 _public prototype_ `virtual FText GetViewTooltipText() = 0;` — Get a tooltip for the custom view

### `Source/Editor/ContentBrowser/Public/FrontendFilterBase.h` (Public)


#### class `FFrontendFilterCategory`  
`class FFrontendFilterCategory : public FFilterCategory`  
_L13-17_
- inherits: `FFilterCategory`
- L16 _public function_ `FFrontendFilterCategory(const FText& InTitle, const FText& InTooltip) : FFilterCategory(InTitle,InTooltip)`

#### class `FFrontendFilter`  
`class FFrontendFilter : public FFilterBase<FAssetFilterType>`  
_L19-53_
- inherits: `FFilterBase<FAssetFilterType>`
- L22 _public function_ `FFrontendFilter(TSharedPtr<FFrontendFilterCategory> InCategory) : FFilterBase<FAssetFilterType>(MoveTemp(InCategory))`
- L25 _public function_ `virtual void SetCurrentFilter(TArrayView<const FName> InSourcePaths, const FContentBrowserDataFilter& InBaseFilter)` — Invoke to set the source filter that is currently used to filter assets in the asset view
- L28 _public function_ `virtual TOptional<FText> GetAsCustomTextFilter()` — If this filter is a saved custom text filter, return the text query it represents.
- L33 _public function_ `virtual FLinearColor GetColor() const override` — Returns the color this filter button will be when displayed as a button
- L36 _public function_ `virtual FName GetIconName() const override` — Returns the name of the icon to use in menu entries
- L39 _public function_ `virtual bool IsInverseFilter() const override` — Returns true if the filter should be in the list when disabled and not in the list when enabled
- L42 _public function_ `virtual void ActiveStateChanged(bool bActive) override` — Notification that the filter became active or inactive
- L45 _public function_ `virtual void ModifyContextMenu(FMenuBuilder& MenuBuilder) override` — Called when the right-click context menu is being built for this filter
- L48 _public function_ `virtual void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const` — Called when the state of a particular Content Browser is being saved to INI
- L51 _public function_ `virtual void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString)` — Called when the state of a particular Content Browser is being loaded from INI

### `Source/Editor/ContentBrowser/Public/FrontendFilters.h` (Public)


#### class `FFrontendFilter_Text`  
`class FFrontendFilter_Text : public FFrontendFilter`  
_L42-128_
- reflection: `UE_DEPRECATED(5.5, "FFrontendFilter_Text has been deprecated in favor of FAssetTextFilter, used by SAssetView to perform text filtering in parallel.")`
- inherits: `FFrontendFilter`
- desc: A filter for text search
- L45 _public prototype_ `FFrontendFilter_Text();`
- L46 _public prototype_ `~FFrontendFilter_Text();`
- L49 _public function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L50 _public function_ `virtual FText GetDisplayName() const override`
- L51 _public function_ `virtual FText GetToolTipText() const override`
- L54 _public prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation
- L58 _public prototype_ `FText GetRawFilterText() const;` — Returns the unsanitized and unsplit filter terms
- L61 _public prototype_ `void SetRawFilterText(const FText& InFilterText);` — Set the Text to be used as the Filter's restrictions
- L64 _public prototype_ `FText GetFilterErrorText() const;` — Get the last error returned from lexing or compiling the current filter text
- L67 _public prototype_ `void SetIncludeClassName(const bool InIncludeClassName);` — If bIncludeClassName is true, the text filter will include an asset's class name in the search
- L70 _public prototype_ `void SetIncludeAssetPath(const bool InIncludeAssetPath);` — If bIncludeAssetPath is true, the text filter will match against full Asset path
- L72 _public prototype_ `bool GetIncludeAssetPath() const;`
- L75 _public prototype_ `void SetIncludeCollectionNames(const bool InIncludeCollectionNames);` — If bIncludeCollectionNames is true, the text filter will match against collection names as well
- L77 _public prototype_ `bool GetIncludeCollectionNames() const;`
- L80 _private prototype_ `void HandleCollectionContainerCreated(const TSharedRef<ICollectionContainer>& CollectionContainer);` — Handles an on collection container created event
- L83 _private prototype_ `void HandleCollectionContainerDestroyed(const TSharedRef<ICollectionContainer>& CollectionContainer);` — Handles an on collection container destroyed event
- L86 _private prototype_ `void HandleIsHiddenChanged(ICollectionContainer& CollectionContainer, bool bIsHidden);` — Handles an on collection container is hidden changed event
- L89 _private prototype_ `void HandleCollectionCreated(ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection);` — Handles an on collection created event
- L92 _private prototype_ `void HandleCollectionDestroyed(ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection);` — Handles an on collection destroyed event
- L95 _private prototype_ `void HandleCollectionRenamed(ICollectionContainer& CollectionContainer, const FCollectionNameType& OriginalCollection, const FCollectionNameType& NewCollection);` — Handles an on collection renamed event
- L98 _private prototype_ `void HandleCollectionUpdated(ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection);` — Handles an on collection updated event
- L101 _private prototype_ `void RebuildReferencedDynamicCollections();` — Rebuild the array of dynamic collections that are being referenced by the current query
- L104 _private member_ `TArray<TSharedPtr<ICollectionContainer>> CollectionContainers;` — An array of collection containers that are being monitored
- L107 _private member_ `TArray<FCollectionRef> ReferencedDynamicCollections;` — An array of dynamic collections that are being referenced by the current query. These should be tested against each asset when it's looking for collections that contain it
- L110 _private member_ `TSharedRef<class FFrontendFilter_TextFilterExpressionContext> TextFilterExpressionContext;` — Transient context data, used when calling PassesFilter. Kept around to minimize re-allocations between multiple calls to PassesFilter
- L113 _private member_ `FTextFilterExpressionEvaluator TextFilterExpressionEvaluator;` — Expression evaluator that can be used to perform complex text filter queries
- L116 _private member_ `FDelegateHandle OnCollectionContainerCreatedHandle;` — Delegate handles
- L117 _private member_ `FDelegateHandle OnCollectionContainerDestroyedHandle;`
- L127 _private member_ `TArray<FCollectionContainerHandles> CollectionContainerHandles;`

#### struct `FFrontendFilter_Text::FCollectionContainerHandles`  
`struct FCollectionContainerHandles`  
_L119-126_
- L121 _public member_ `FDelegateHandle OnIsHiddenChangedHandle;`
- L122 _public member_ `FDelegateHandle OnCollectionCreatedHandle;`
- L123 _public member_ `FDelegateHandle OnCollectionDestroyedHandle;`
- L124 _public member_ `FDelegateHandle OnCollectionRenamedHandle;`
- L125 _public member_ `FDelegateHandle OnCollectionUpdatedHandle;`

#### class `FFrontendFilter_CheckedOut`  
`class FFrontendFilter_CheckedOut : public FFrontendFilter, public TSharedFromThis<FFrontendFilter_CheckedOut>`  
_L131-155_
- inherits: `FFrontendFilter,TSharedFromThis<FFrontendFilter_CheckedOut>`
- desc: A filter that displays only checked out assets
- L134 _public prototype_ `FFrontendFilter_CheckedOut(TSharedPtr<FFrontendFilterCategory> InCategory);`
- L137 _public function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L138 _public function_ `virtual FText GetDisplayName() const override`
- L139 _public function_ `virtual FText GetToolTipText() const override`
- L140 _public prototype_ `virtual void ActiveStateChanged(bool bActive) override;`
- L141 _public prototype_ `virtual void SetCurrentFilter(TArrayView<const FName> InSourcePaths, const FContentBrowserDataFilter& InBaseFilter) override;`
- L144 _public prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation
- L149 _private prototype_ `void RequestStatus();` — Request the source control status for this filter
- L152 _private prototype_ `void SourceControlOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Callback when source control operation has completed
- L154 _private member_ `bool bSourceControlEnabled;`

#### class `FFrontendFilter_NotSourceControlled`  
`class FFrontendFilter_NotSourceControlled : public FFrontendFilter, public TSharedFromThis<FFrontendFilter_NotSourceControlled>`  
_L158-184_
- inherits: `FFrontendFilter,TSharedFromThis<FFrontendFilter_NotSourceControlled>`
- desc: A filter that displays assets not tracked by source control
- L161 _public prototype_ `FFrontendFilter_NotSourceControlled(TSharedPtr<FFrontendFilterCategory> InCategory);`
- L164 _public function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L165 _public function_ `virtual FText GetDisplayName() const override`
- L166 _public function_ `virtual FText GetToolTipText() const override`
- L167 _public prototype_ `virtual void ActiveStateChanged(bool bActive) override;`
- L168 _public prototype_ `virtual void SetCurrentFilter(TArrayView<const FName> InSourcePaths, const FContentBrowserDataFilter& InBaseFilter) override;`
- L171 _public prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation
- L176 _private prototype_ `void RequestStatus();` — Request the source control status for this filter
- L179 _private prototype_ `void SourceControlOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Callback when source control operation has completed
- L181 _private member_ `bool bSourceControlEnabled;`
- L182 _private member_ `bool bIsRequestStatusRunning;`
- L183 _private member_ `bool bInitialRequestCompleted;`

#### class `FFrontendFilter_Modified`  
`class FFrontendFilter_Modified : public FFrontendFilter`  
_L187-208_
- inherits: `FFrontendFilter`
- desc: A filter that displays only modified assets
- L190 _public prototype_ `FFrontendFilter_Modified(TSharedPtr<FFrontendFilterCategory> InCategory);`
- L191 _public prototype_ `~FFrontendFilter_Modified();`
- L194 _public function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L195 _public function_ `virtual FText GetDisplayName() const override`
- L196 _public function_ `virtual FText GetToolTipText() const override`
- L197 _public prototype_ `virtual void ActiveStateChanged(bool bActive) override;`
- L200 _public prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation
- L205 _private prototype_ `void OnPackageDirtyStateUpdated(UPackage* Package);` — Handler for when a package's dirty state has changed
- L207 _private member_ `bool bIsCurrentlyActive;`

#### class `FFrontendFilter_ReplicatedBlueprint`  
`class FFrontendFilter_ReplicatedBlueprint : public FFrontendFilter`  
_L211-223_
- inherits: `FFrontendFilter`
- desc: A filter that displays blueprints that have replicated properties
- L214 _public function_ `FFrontendFilter_ReplicatedBlueprint(TSharedPtr<FFrontendFilterCategory> InCategory) : FFrontendFilter(InCategory)`
- L217 _public function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L218 _public function_ `virtual FText GetDisplayName() const override`
- L219 _public function_ `virtual FText GetToolTipText() const override`
- L222 _public prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation

#### class `FFrontendFilter_ArbitraryComparisonOperation`  
`class FFrontendFilter_ArbitraryComparisonOperation : public FFrontendFilter`  
_L226-257_
- inherits: `FFrontendFilter`
- desc: A filter that compares the value of an asset registry tag to a target value
- L229 _public prototype_ `FFrontendFilter_ArbitraryComparisonOperation(TSharedPtr<FFrontendFilterCategory> InCategory);`
- L232 _public prototype_ `virtual FString GetName() const override;` — FFrontendFilter implementation
- L233 _public prototype_ `virtual FText GetDisplayName() const override;`
- L234 _public prototype_ `virtual FText GetToolTipText() const override;`
- L235 _public prototype_ `virtual void ModifyContextMenu(FMenuBuilder& MenuBuilder) override;`
- L236 _public prototype_ `virtual void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const override;`
- L237 _public prototype_ `virtual void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) override;`
- L240 _public prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation
- L243 _protected prototype_ `static FString ConvertOperationToString(ETextFilterComparisonOperation Op);`
- L245 _protected prototype_ `void SetComparisonOperation(ETextFilterComparisonOperation NewOp);`
- L246 _protected prototype_ `bool IsComparisonOperationEqualTo(ETextFilterComparisonOperation TestOp) const;`
- L248 _protected prototype_ `FText GetKeyValueAsText() const;`
- L249 _protected prototype_ `FText GetTargetValueAsText() const;`
- L250 _protected prototype_ `void OnKeyValueTextCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L251 _protected prototype_ `void OnTargetValueTextCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L254 _public member_ `FName TagName;`
- L255 _public member_ `FString TargetTagValue;`
- L256 _public member_ `ETextFilterComparisonOperation ComparisonOp;`

#### class `FFrontendFilter_ShowOtherDevelopers`  
`FFrontendFilter_ShowOtherDevelopers : public FFrontendFilter`  
_L261-290_
- reflection: `UE_DEPRECATED(5.5, "This frontend filter has been deprecated and replaced with backend filtering. see FFilter_HideOtherDevelopers.")`
- inherits: `FFrontendFilter`
- desc: An inverse filter that allows display of content in developer folders that are not the current user's
- L265 _public prototype_ `FFrontendFilter_ShowOtherDevelopers(TSharedPtr<FFrontendFilterCategory> InCategory);` — Constructor
- L268 _public function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L269 _public function_ `virtual FText GetDisplayName() const override`
- L270 _public function_ `virtual FText GetToolTipText() const override`
- L271 _public function_ `virtual bool IsInverseFilter() const override`
- L272 _public prototype_ `virtual void SetCurrentFilter(TArrayView<const FName> InSourcePaths, const FContentBrowserDataFilter& InBaseFilter) override;`
- L275 _public prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation
- L279 _public prototype_ `void SetShowOtherDeveloperAssets(bool bValue);` — Sets if we should filter out assets from other developers
- L282 _public prototype_ `bool GetShowOtherDeveloperAssets() const;` — Gets if we should filter out assets from other developers
- L285 _private member_ `FString BaseDeveloperPath;`
- L286 _private member_ `TArray<ANSICHAR> BaseDeveloperPathAnsi;`
- L287 _private member_ `FString UserDeveloperPath;`
- L288 _private member_ `bool bIsOnlyOneDeveloperPathSelected;`
- L289 _private member_ `bool bShowOtherDeveloperAssets;`

#### class `FFrontendFilter_ShowRedirectors`  
`FFrontendFilter_ShowRedirectors : public FFrontendFilter`  
_L294-313_
- reflection: `UE_DEPRECATED(5.5, "FFrontendFilter_ShowRedirectors is deprecated. FFilter_ShowRedirectors is a virtual filter which controls backend search state instead.")`
- inherits: `FFrontendFilter`
- desc: An inverse filter that allows display of object redirectors
- L298 _public prototype_ `FFrontendFilter_ShowRedirectors(TSharedPtr<FFrontendFilterCategory> InCategory);` — Constructor
- L301 _public function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L302 _public function_ `virtual FText GetDisplayName() const override`
- L303 _public function_ `virtual FText GetToolTipText() const override`
- L304 _public function_ `virtual bool IsInverseFilter() const override`
- L305 _public prototype_ `virtual void SetCurrentFilter(TArrayView<const FName> InSourcePaths, const FContentBrowserDataFilter& InBaseFilter) override;`
- L308 _public prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation
- L311 _private member_ `bool bAreRedirectorsInBaseFilter;`
- L312 _private member_ `FString RedirectorClassName;`

#### class `FFrontendFilter_InUseByLoadedLevels`  
`class FFrontendFilter_InUseByLoadedLevels : public FFrontendFilter`  
_L316-348_
- inherits: `FFrontendFilter`
- desc: A filter that only displays assets used by loaded levels
- L320 _public prototype_ `FFrontendFilter_InUseByLoadedLevels(TSharedPtr<FFrontendFilterCategory> InCategory);` — Constructor/Destructor
- L324 _public function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L325 _public function_ `virtual FText GetDisplayName() const override`
- L326 _public function_ `virtual FText GetToolTipText() const override`
- L327 _public prototype_ `virtual void ActiveStateChanged(bool bActive) override;`
- L330 _public prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation
- L333 _public prototype_ `void OnEditorMapChange( uint32 MapChangeFlags );` — Handler for when maps change in the editor
- L336 _public prototype_ `void OnAssetPostRename(const TArray<FAssetRenameData>& AssetsAndNames);` — Handler for when an asset is renamed
- L339 _public prototype_ `void OnAssetPostCompile(const TArray<FAssetCompileData>& CompiledAssets);` — Handler for when assets are finished compiling
- L342 _private prototype_ `void Refresh();`
- L343 _private prototype_ `void RegisterDelayedRefresh(float DelayInSeconds);`
- L344 _private prototype_ `void UnregisterDelayedRefresh();`
- L345 _private member_ `FTSTicker::FDelegateHandle DelayedRefreshHandle;`
- L346 _private member_ `bool bIsDirty = false;`
- L347 _private member_ `bool bIsCurrentlyActive = false;`

#### class `FFrontendFilter_UsedInAnyLevel`  
`class FFrontendFilter_UsedInAnyLevel: public FFrontendFilter`  
_L351-369_
- inherits: `FFrontendFilter`
- desc: A filter that only displays assets used by any level
- L355 _public prototype_ `FFrontendFilter_UsedInAnyLevel(TSharedPtr<FFrontendFilterCategory> InCategory);` — Constructor/Destructor
- L358 _public function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L359 _public function_ `virtual FText GetDisplayName() const override`
- L360 _public function_ `virtual FText GetToolTipText() const override`
- L361 _public prototype_ `virtual void ActiveStateChanged(bool bActive) override;`
- L364 _public prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation
- L367 _private member_ `class IAssetRegistry* AssetRegistry;`
- L368 _private member_ `TSet<FName> LevelsDependencies;`

#### class `FFrontendFilter_NotUsedInAnyLevel`  
`class FFrontendFilter_NotUsedInAnyLevel : public FFrontendFilter`  
_L372-390_
- inherits: `FFrontendFilter`
- desc: A filter that only displays assets not used by any level
- L376 _public prototype_ `FFrontendFilter_NotUsedInAnyLevel(TSharedPtr<FFrontendFilterCategory> InCategory);` — Constructor/Destructor
- L379 _public function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L380 _public function_ `virtual FText GetDisplayName() const override`
- L381 _public function_ `virtual FText GetToolTipText() const override`
- L382 _public prototype_ `virtual void ActiveStateChanged(bool bActive) override;`
- L385 _public prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation
- L388 _private member_ `class IAssetRegistry* AssetRegistry;`
- L389 _private member_ `TSet<FName> LevelsDependencies;`

#### class `FFrontendFilter_NotUsedInAnyAsset`  
`class FFrontendFilter_NotUsedInAnyAsset : public FFrontendFilter`  
_L393-409_
- inherits: `FFrontendFilter`
- desc: A filter that only displays assets not used in another asset (Note It does not update itself automatically)
- L397 _public prototype_ `FFrontendFilter_NotUsedInAnyAsset(TSharedPtr<FFrontendFilterCategory> InCategory);` — Constructor/Destructor
- L400 _public function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L401 _public function_ `virtual FText GetDisplayName() const override`
- L402 _public function_ `virtual FText GetToolTipText() const override`
- L405 _public prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation
- L408 _private member_ `class IAssetRegistry* AssetRegistry = nullptr;`

#### class `FFrontendFilter_Recent`  
`class FFrontendFilter_Recent : public FFrontendFilter`  
_L412-435_
- inherits: `FFrontendFilter`
- desc: A filter that displays recently opened assets
- L415 _public prototype_ `FFrontendFilter_Recent(TSharedPtr<FFrontendFilterCategory> InCategory);`
- L416 _public prototype_ `~FFrontendFilter_Recent();`
- L419 _public function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L420 _public function_ `virtual FText GetDisplayName() const override`
- L421 _public function_ `virtual FText GetToolTipText() const override`
- L422 _public prototype_ `virtual void ActiveStateChanged(bool bActive) override;`
- L423 _public prototype_ `virtual void SetCurrentFilter(TArrayView<const FName> InSourcePaths, const FContentBrowserDataFilter& InBaseFilter) override;`
- L426 _public prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation
- L428 _public prototype_ `void ResetFilter(FName InName);`
- L431 _private prototype_ `void RefreshRecentPackagePaths();`
- L433 _private member_ `TSet<FName> RecentPackagePaths;`
- L434 _private member_ `bool bIsCurrentlyActive;`

#### class `FFrontendFilter_Writable`  
`class FFrontendFilter_Writable : public FFrontendFilter`  
_L438-453_
- inherits: `FFrontendFilter`
- desc: A filter that displays only assets that are not read only
- L441 _public prototype_ `FFrontendFilter_Writable(TSharedPtr<FFrontendFilterCategory> InCategory);`
- L442 _public prototype_ `~FFrontendFilter_Writable();`
- L445 _public function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L446 _public function_ `virtual FText GetDisplayName() const override`
- L447 _public function_ `virtual FText GetToolTipText() const override`
- L450 _public prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation

#### class `FFrontendFilter_VirtualizedData`  
`class FFrontendFilter_VirtualizedData : public FFrontendFilter`  
_L456-470_
- inherits: `FFrontendFilter`
- desc: A filter that displays only packages that contain virtualized data
- L459 _public prototype_ `FFrontendFilter_VirtualizedData(TSharedPtr<FFrontendFilterCategory> InCategory);`
- L460 _public prototype_ `~FFrontendFilter_VirtualizedData() = default;`
- L464 _private function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L465 _private function_ `virtual FText GetDisplayName() const override`
- L466 _private function_ `virtual FText GetToolTipText() const override`
- L469 _private prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation

#### class `FFrontendFilter_Unsupported`  
`class FFrontendFilter_Unsupported : public FFrontendFilter`  
_L473-486_
- inherits: `FFrontendFilter`
- desc: A filter that displays only assets the are mark as unsupported
- L476 _public prototype_ `FFrontendFilter_Unsupported(TSharedPtr<FFrontendFilterCategory> InCategory);`
- L477 _public prototype_ `~FFrontendFilter_Unsupported() = default;`
- L480 _public function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L481 _public function_ `virtual FText GetDisplayName() const override`
- L482 _public function_ `virtual FText GetToolTipText() const override`
- L485 _public prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation

#### class `FFrontendFilter_Favorites`  
`class FFrontendFilter_Favorites : public FFrontendFilter`  
_L489-506_
- inherits: `FFrontendFilter`
- desc: A filter that displays only assets the are mark as Favorite
- L492 _public prototype_ `FFrontendFilter_Favorites(TSharedPtr<FFrontendFilterCategory> InCategory);`
- L493 _public prototype_ `~FFrontendFilter_Favorites() = default;`
- L496 _public function_ `virtual FString GetName() const override` — FFrontendFilter implementation
- L497 _public function_ `virtual FText GetDisplayName() const override`
- L498 _public function_ `virtual FText GetToolTipText() const override`
- L499 _public function_ `virtual FLinearColor GetColor() const override`
- L502 _public prototype_ `virtual bool PassesFilter(FAssetFilterType InItem) const override;` — IFilter implementation
- L505 _private member_ `UE::Editor::DataStorage::ICoreProvider* DataStorage;`

#### Free symbols / members of external scopes

- L28 _macro_ `#define UE_API CONTENTBROWSER_API`
- L35 _macro_ `#define LOCTEXT_NAMESPACE "ContentBrowser"`

### `Source/Editor/ContentBrowser/Public/HistoryManager.h` (Public)


#### struct `FSelectionData`  
`struct FSelectionData`  
_L18-45_
- L21 _public member_ `TSet<FName> SelectedVirtualPaths;` — Virtual paths (for both folders and files) of the selected items
- L23 _public function_ `int32 Num() const`
- L28 _public function_ `void Reset()`
- L33 _public function_ `void Empty()`
- L38 _public function_ `void AddMissingVirtualPaths(const FSelectionData& SelectionData)`

#### struct `FHistoryData`  
`struct FHistoryData`  
_L48-73_
- desc: The history data object, storing all important history data
- L50 _public prototype_ `FHistoryData() = default;`
- L54 _public prototype_ `FHistoryData(const FHistoryData&) = default;`
- L55 _public prototype_ `FHistoryData(FHistoryData&&) = default;`
- L57 _public prototype_ `FHistoryData& operator=(const FHistoryData&) = default;`
- L58 _public prototype_ `FHistoryData& operator=(FHistoryData&&) = default;`
- L63 _public member_ `FText HistoryDesc;` — History Description
- L66 _public member_ `FAssetViewContentSources ContentSources;` — The base set of filters on the asset view which includes selected paths and collections
- L69 _public member_ `FSourcesData SourcesData;` — `UE_DEPRECATED(5.6, "Use ContentSources instead.")`
- L72 _public member_ `FSelectionData SelectionData;` — The selection data from before the sources changed

#### class `FHistoryManager`  
`class FHistoryManager`  
_L82-181_
- desc: The class responsible for managing all content browser history
- L86 _public prototype_ `FHistoryManager();` — Constructor
- L89 _public prototype_ `void SetOnApplyHistoryData(const FOnApplyHistoryData& InOnApplyHistoryData);` — Set the delegate for applying history data
- L92 _public prototype_ `void SetOnUpdateHistoryData(const FOnUpdateHistoryData& InOnUpdateHistoryData);` — Set the delegate for updating history data
- L95 _public prototype_ `bool GoBack();` — Goes back one history snapshot and returns the history data at that snapshot
- L98 _public prototype_ `bool GoForward();` — Goes forward one history snapshot and returns the history data at that snapshot
- L101 _public prototype_ `void AddHistoryData();` — Stores new history data.  Called when creating a history snapshot
- L104 _public prototype_ `void UpdateHistoryData();` — Triggers an update for the current history data. This is typically done right before changing the history.
- L107 _public prototype_ `bool CanGoForward() const;` — Determines if a user can go forward in history
- L110 _public prototype_ `bool CanGoBack() const;` — Determines if a user can go back in history
- L113 _public prototype_ `FText GetBackDesc() const;` — Gets the description of the previous history entry
- L116 _public prototype_ `FText GetForwardDesc() const;` — Gets the description of the next history entry
- L125 _public prototype_ `void GetAvailableHistoryMenuItems(bool bGetPrior, FMenuBuilder& MenuBuilder);` — Populates a list of menu items that can be added to a context menu to allow a user to jump to different history snapshots instead of using the back and forward buttons @param bGetPrior If true gets history snapshots prior to the current history index(for navigating back). If false get history snapshots after the current history index (for navigating forward). @param MenuBuilder The menubuilder to populate with menu items
- L129 _public function_ `template <class PREDICATE_CLASS> void RewriteHistoryData(const PREDICATE_CLASS& Predicate)` — Rewrite all history data as determined by the passed in predicate
- L139 _public function_ `template <class PREDICATE_CLASS> void RemoveHistoryData(const PREDICATE_CLASS& Predicate)` — Removes all history data as determined by the passed in predicate
- L158 _private prototype_ `void ApplyCurrentHistoryData();` — Notifies the owner to update to the state described by the current history data
- L161 _private prototype_ `void UpdateCurrentHistoryData();` — Notifies the owner to update the current history data
- L164 _private prototype_ `void ExecuteJumpToHistory(int32 HistoryIndex);` — Handler for when a history item is chosen in the GetAvailableHistroyMenuItems list
- L168 _private member_ `FOnApplyHistoryData OnApplyHistoryData;` — The delegate for when history data should be applied
- L171 _private member_ `FOnUpdateHistoryData OnUpdateHistoryData;` — The delegate for when history data should be updated
- L174 _private member_ `TArray<FHistoryData> HistoryData;` — A list of history snapshots
- L177 _private member_ `int32 CurrentHistoryIndex;` — The current history index the user is at (changes when the user goes back,forward, or history snapshots are taken)
- L180 _private member_ `int32 MaxHistoryEntries;` — Max number of history items that can be stored.  Once the max is reached, the oldest history item is removed

#### Free symbols / members of external scopes

- L76 _delegate_ `DECLARE_DELEGATE_OneParam(FOnApplyHistoryData, const FHistoryData& );` — The delegate for when history data should be applied
- L76 _prototype_ `DECLARE_DELEGATE_OneParam(FOnApplyHistoryData, const FHistoryData& );` — The delegate for when history data should be applied
- L79 _delegate_ `DECLARE_DELEGATE_OneParam(FOnUpdateHistoryData, FHistoryData& );` — The delegate for when history data should be updated
- L79 _prototype_ `DECLARE_DELEGATE_OneParam(FOnUpdateHistoryData, FHistoryData& );` — The delegate for when history data should be updated

### `Source/Editor/ContentBrowser/Public/IContentBrowserSingleton.h` (Public)


#### enum `EAssetViewType::Type`  
`enum Type`  
_L41-49_
- L43 _public enumerator_ `List`
- L44 _public enumerator_ `Tile`
- L45 _public enumerator_ `Column`
- L46 _public enumerator_ `Custom`
- L48 _public enumerator_ `MAX`

#### struct `FContentBrowserSelection`  
`struct FContentBrowserSelection`  
_L59-90_
- desc: A selection of items in the Content Browser
- L61 _public member_ `TArray<FContentBrowserItem> SelectedItems;`
- L64 _public member_ `TArray<FAssetData> SelectedAssets;` — Legacy data - if set will take precedence over SelectedItems
- L65 _public member_ `TArray<FString> SelectedFolders;`
- L67 _public function_ `bool IsLegacy() const`
- L72 _public function_ `int32 Num() const`
- L77 _public function_ `void Reset()`
- L84 _public function_ `void Empty()`

#### struct `FContentBrowserConfig`  
`struct FContentBrowserConfig`  
_L94-172_
- desc: A struct containing details about how the content browser should behave
- L97 _public member_ `EThumbnailLabel::Type ThumbnailLabel;` — The contents of the label on the thumbnail
- L100 _public member_ `TAttribute< float > ThumbnailScale;` — The default scale for thumbnails. [0-1] range
- L103 _public member_ `EAssetViewType::Type InitialAssetViewType;` — The default view mode
- L106 _public member_ `FCollectionRef SelectedCollection;` — Collection to view initially
- L109 _public member_ `FCollectionNameType SelectedCollectionName;` — `UE_DEPRECATED(5.6, "Use SelectedCollection instead.")`
- L112 _public member_ `bool bShowBottomToolbar : 1;` — If true, show the bottom toolbar which shows # of assets selected, view mode buttons, etc...
- L115 _public member_ `bool bCanShowClasses : 1;` — Indicates if this view is allowed to show classes
- L118 _public member_ `bool bUseSourcesView : 1;` — Whether the sources view for choosing folders/collections is available or not
- L121 _public member_ `bool bExpandSourcesView : 1;` — Whether the sources view should initially be expanded or not
- L124 _public member_ `bool bUsePathPicker : 1;` — Whether the path picker is available or not
- L127 _public member_ `bool bCanShowFilters : 1;` — Whether to show filters
- L130 _public member_ `bool bCanShowAssetSearch : 1;` — Whether to show asset search
- L133 _public member_ `bool bCanShowFolders : 1;` — Indicates if the 'Show folders' option should be enabled or disabled
- L136 _public member_ `bool bCanShowRealTimeThumbnails : 1;` — Indicates if the 'Real-Time Thumbnails' option should be enabled or disabled
- L139 _public member_ `bool bCanShowDevelopersFolder : 1;` — Indicates if the 'Show Developers' option should be enabled or disabled
- L142 _public member_ `bool bCanShowLockButton : 1;` — Whether the 'lock' button is visible on the toolbar
- L145 _public member_ `bool bCanSetAsPrimaryBrowser : 1;` — Whether or not this Content Browser can be used as the Primary Browser for SyncBrowserTo functions
- L147 _public function_ `FContentBrowserConfig() : ThumbnailLabel( EThumbnailLabel::ClassName ) , ThumbnailScale(0.1f) , InitialAssetViewType(EAssetViewType::Tile) , SelectedCollection(nullptr, NAME_None, ECollectionShareType::CST_Local) PRAGMA_DISABLE_DEPRECATION_WARNINGS , SelectedCollectionName( NAME_None, ECollectionShareType::CST_Local ) PRAGMA_ENABLE_DEPRECATION_WARNINGS , bShowBottomToolbar(true) , bCanShowClasses(true) , bUseSourcesView(true) , bExpandSourcesView(true) , bUsePathPicker(true) , bCanShowFilters(true) , bCanShowAssetSearch(true) , bCanShowFolders(true) , bCanShowRealTimeThumbnails(true) , bCanShowDevelopersFolder(true) , bCanShowLockButton(true) , bCanSetAsPrimaryBrowser(true)`
- L170 _public prototype_ `FContentBrowserConfig& operator=(const FContentBrowserConfig&) = default;`

#### struct `FAssetPickerConfig`  
`struct FAssetPickerConfig`  
_L176-438_
- desc: A struct containing details about how the asset picker should behave
- L179 _public member_ `ESelectionMode::Type SelectionMode;` — The selection mode the picker should use
- L182 _public member_ `TArray<FGetCurrentSelectionDelegate*> GetCurrentSelectionDelegates;` — An array of pointers to existing delegates which the AssetView will register a function which returns the current selection
- L185 _public member_ `TArray<FSyncToAssetsDelegate*> SyncToAssetsDelegates;` — An array of pointers to existing delegates which the AssetView will register a function which sync the asset list
- L188 _public member_ `TArray<FSetARFilterDelegate*> SetFilterDelegates;` — A pointer to an existing delegate that, when executed, will set the filter an the asset picker after it is created.
- L191 _public member_ `TArray<FRefreshAssetViewDelegate*> RefreshAssetViewDelegates;` — A pointer to an existing delegate that, when executed, will refresh the asset view.
- L194 _public member_ `TArray<FSaveAssetViewSettingsDelegate*> SaveAssetViewSettingsDelegates;` — A pointer to an existing delegate that, when executed, will save the asset view settings.
- L197 _public member_ `TArray<FLoadAssetViewSettingsDelegate*> LoadAssetViewSettingsDelegates;` — A pointer to an existing delegate that, when executed, will load/restore the asset view settings.
- L200 _public member_ `FARFilter Filter;` — The asset registry filter to use to cull results
- L203 _public member_ `TArray< TSharedRef<class FFrontendFilter> > ExtraFrontendFilters;` — Custom front end filters to be displayed
- L206 _public member_ `TArray<FString> HiddenColumnNames;` — The names of columns to hide by default in the column view
- L209 _public member_ `TArray<FString> ListHiddenColumnNames;` — The names of columns to hide by default in the list view, by default the Type column is hidden
- L212 _public member_ `TArray<FAssetViewCustomColumn> CustomColumns;` — List of custom columns that fill out data with a callback
- L215 _public member_ `EThumbnailLabel::Type ThumbnailLabel;` — The contents of the label on the thumbnail
- L218 _public member_ `TAttribute< float > ThumbnailScale;` — The default scale for thumbnails. [0-1] range
- L221 _public member_ `EThumbnailSize InitialThumbnailSize;` — Initial thumbnail size
- L224 _public member_ `TArray<FCollectionRef> CollectionsFilter;` — Only display results in these collections
- L227 _public member_ `TArray<FCollectionNameType> Collections;` — `UE_DEPRECATED(5.6, "Use CollectionsFilter instead.")`
- L230 _public member_ `FAssetData InitialAssetSelection;` — The asset that should be initially selected
- L233 _public member_ `TSharedPtr<class IPropertyHandle> PropertyHandle;` — The handle to the property that opened this picker. Needed for contextual filtering.
- L236 _public member_ `TArray<FAssetData> AdditionalReferencingAssets;` — The passed in property handle will be used to gather referencing assets. If additional referencing assets should be reported, supply them here.
- L239 _public member_ `FOnAssetSelected OnAssetSelected;` — The delegate that fires when an asset was selected
- L242 _public member_ `FOnPathSelected OnFolderEntered;` — The delegate that fires when a folder was double clicked
- L245 _public member_ `FOnAssetDoubleClicked OnAssetDoubleClicked;` — The delegate that fires when an asset is double clicked
- L248 _public member_ `FOnAssetEnterPressed OnAssetEnterPressed;` — The delegate that fires when an asset has enter pressed while selected
- L251 _public member_ `FOnAssetsActivated OnAssetsActivated;` — The delegate that fires when any number of assets are activated
- L254 _public member_ `FOnAssetsDragged OnAssetsDragged;` — The delegate that fires when any number of assets are dragged
- L257 _public member_ `FOnColumnVisibilityChanged OnColumnVisibilityChanged;` — Fires when the user changes which columns are hidden in the column or list view. Useful for syncing column state.
- L260 _public member_ `FOnGetAssetContextMenu OnGetAssetContextMenu;` — The delegate that fires when an asset is right clicked and a context menu is requested
- L263 _public member_ `FOnGetFolderContextMenu OnGetFolderContextMenu;` — The delegate that fires when a folder is right clicked and a context menu is requested
- L266 _public member_ `FOnIsAssetValidForCustomToolTip OnIsAssetValidForCustomToolTip;` — Called to see if it is valid to get a custom asset tool tip
- L269 _public member_ `FOnGetCustomAssetToolTip OnGetCustomAssetToolTip;` — Fired when an asset item is constructed and a tooltip is requested. If unbound the item will use the default widget
- L272 _public member_ `FOnGetCustomSourceAssets OnGetCustomSourceAssets;` — Called to add extra asset data to the asset view, to display virtual assets. These get treated similar to Class assets
- L275 _public member_ `FOnVisualizeAssetToolTip OnVisualizeAssetToolTip;` — Fired when an asset item is about to show its tool tip
- L278 _public member_ `FOnAssetToolTipClosing OnAssetToolTipClosing;` — Fired when an asset item's tooltip is closing
- L281 _public member_ `FOnShouldFilterAsset OnShouldFilterAsset;` — If more detailed filtering is required than simply Filter, this delegate will get fired for every asset to determine if it should be culled.
- L285 _public member_ `FOnShouldDisplayAssetTag OnAssetTagWantsToBeDisplayed;` — This delegate will be called in Details view when a new asset registry searchable tag is encountered, to determine if it should be displayed or not.  If it returns true or isn't bound, the tag will be displayed normally.
- L288 _public member_ `FOnSearchTextChanged OnSearchTextChanged;` — Fired when the search box text changes. Allows embedding widgets to observe the search text without replacing the built-in search behavior.
- L291 _public member_ `EAssetViewType::Type InitialAssetViewType;` — The default view mode
- L294 _public member_ `TAttribute<FText> AssetShowWarningText;` — The warning text to show as heading (e.g. when there are no assets to show)
- L297 _public member_ `TAttribute<ETextJustify::Type> AssetShowWarningTextJustification;` — The justification to use for the AssetShowWarning text (see AssetShowWarningText)
- L300 _public member_ `TAttribute<bool> AssetShowWarningTextSelectable;` — Whether the warning text is selectable or not (see AssetShowWarningText)
- L303 _public member_ `FString SaveSettingsName;` — If set, view settings will be saved and loaded for the asset view using this name in ini files
- L306 _public member_ `TOptional<FString> FilterBarSaveSettingsNameOverride;` — If set, will use this name for filter bar saving purposes instead of the SaveSettingsName.
- L309 _public member_ `bool bFocusSearchBoxWhenOpened;` — If true, the search box will gain focus when the asset picker is created
- L312 _public member_ `bool bAllowNullSelection;` — If true, a "None" item will always appear at the top of the list
- L315 _public member_ `bool bShowBottomToolbar;` — If true, show the bottom toolbar which shows # of assets selected, view mode buttons, etc...
- L318 _public member_ `bool bAutohideSearchBar;` — If false, auto-hide the search bar above
- L321 _public member_ `bool bAllowDragging;` — Whether to allow dragging of items
- L324 _public member_ `bool bAllowRename;` — Whether to allow renaming of items
- L327 _public member_ `bool bCanShowClasses;` — Indicates if this view is allowed to show classes
- L330 _public member_ `bool bCanShowFolders;` — Indicates if the 'Show folders' option should be enabled or disabled
- L333 _public member_ `bool bCanShowReadOnlyFolders;` — If true, will allow read-only folders to be shown in the picker
- L336 _public member_ `bool bCanShowRealTimeThumbnails;` — Indicates if the 'Real-Time Thumbnails' option should be enabled or disabled
- L339 _public member_ `bool bCanShowDevelopersFolder;` — Indicates if the 'Show Developers' option should be enabled or disabled
- L342 _public member_ `bool bForceShowEngineContent;` — Indicates if engine content should always be shown
- L345 _public member_ `bool bForceShowPluginContent;` — Indicates if plugin content should always be shown
- L348 _public member_ `bool bAddFilterUI;` — Indicates that we would like to build the filter UI with the Asset Picker
- L351 _public member_ `bool bShowPathInColumnView;` — If true, show path in column view
- L353 _public member_ `bool bShowTypeInColumnView;` — If true, show class in column view
- L355 _public member_ `bool bSortByPathInColumnView;` — If true, sort by path in column view. Only works if initial view type is Column
- L358 _public member_ `TDelegate<void(UToolMenu*)> OnExtendAddFilterMenu;` — Can be used to freely change the Add Filter menu. This is executed on the dynamically instanced menu, not the registered menu.
- L368 _public member_ `TDelegate<void(TSharedRef<SHorizontalBox>)> OnExtendAssetPickerTopBar;` — Can be used to extend the asset picker top bar via slot manipulation. Current default slots are as follows: 0. Add Filter Menu 1. SearchBar 2. Show Developer Content Checkbox 3. Asset View Options
- L371 _public member_ `EAssetTypeCategories::Type DefaultFilterMenuExpansion;` — Override the default filter context menu layout
- L374 _public member_ `bool bUseSectionsForCustomFilterCategories;` — If we display filters & set to true, we will add sections instead of sub-menus for other filters. Useful if the number of additional filters is small.
- L377 _public member_ `TOptional<FName> AssetViewOptionsProfile;` — If specified, the asset view options menu will use this tool menu profile for customization purposes.
- L379 _public function_ `FAssetPickerConfig() : SelectionMode( ESelectionMode::Multi ) , ListHiddenColumnNames( { TEXT("Class") } ) , ThumbnailLabel( EThumbnailLabel::ClassName ) , ThumbnailScale(0.1f) , InitialThumbnailSize(EThumbnailSize::Medium) , InitialAssetViewType(EAssetViewType::Tile) , bFocusSearchBoxWhenOpened(true) , bAllowNullSelection(false) , bShowBottomToolbar(true) , bAutohideSearchBar(false) , bAllowDragging(true) , bAllowRename(true) , bCanShowClasses(true) , bCanShowFolders(false) , bCanShowReadOnlyFolders(true) , bCanShowRealTimeThumbnails(false) , bCanShowDevelopersFolder(true) , bForceShowEngineContent(false) , bForceShowPluginContent(false) , bAddFilterUI(false) , bShowPathInColumnView(false) , bShowTypeInColumnView(true) , bSortByPathInColumnView(false) , DefaultFilterMenuExpansion(EAssetTypeCategories::Basic) , bUseSectionsForCustomFilterCategories(false)`
- L415 _public prototype_ `FAssetPickerConfig(const FAssetPickerConfig&) = default;`
- L416 _public prototype_ `FAssetPickerConfig(FAssetPickerConfig&&) = default;`
- L418 _public prototype_ `FAssetPickerConfig& operator=(const FAssetPickerConfig&) = default;`
- L419 _public prototype_ `FAssetPickerConfig& operator=(FAssetPickerConfig&&) = default;`
- L424 _private function_ `static bool IsNewStyleEnabled()`

#### struct `FPathPickerConfig`  
`struct FPathPickerConfig`  
_L441-511_
- desc: A struct containing details about how the path picker should behave
- L444 _public member_ `FString DefaultPath;` — The initial path to select. Leave empty to skip initial selection.
- L447 _public member_ `TSharedPtr<FPathPermissionList> CustomFolderPermissionList;` — Custom Folder permissions to be used to filter folders in this Path Picker.
- L450 _public member_ `FOnPathSelected OnPathSelected;` — The delegate that fires when a path was selected
- L453 _public member_ `FContentBrowserMenuExtender_SelectedPaths OnGetPathContextMenuExtender;` — The delegate that fires when a path is right clicked and a context menu is requested
- L456 _public member_ `FOnGetFolderContextMenu OnGetFolderContextMenu;` — The delegate that fires when a folder is right clicked and a context menu is requested
- L459 _public member_ `TArray<FSetPathPickerPathsDelegate*> SetPathsDelegates;` — A pointer to an existing delegate that, when executed, will set the paths for the path picker after it is created.
- L462 _public member_ `bool bFocusSearchBoxWhenOpened : 1;` — If true, the search box will gain focus when the path picker is created
- L465 _public member_ `bool bAllowContextMenu : 1;` — If false, the context menu will not open when an item is right clicked
- L468 _public member_ `bool bAllowClassesFolder : 1;` — If true, will allow class folders to be shown in the picker
- L471 _public member_ `bool bAllowReadOnlyFolders : 1;` — If true, will allow read-only folders to be shown in the picker
- L474 _public member_ `bool bAddDefaultPath : 1;` — If true, will add the path specified in DefaultPath to the tree if it doesn't exist already
- L477 _public member_ `bool bOnPathSelectedPassesVirtualPaths : 1;` — If true, passes virtual paths to OnPathSelected instead of internal asset paths
- L480 _public member_ `bool bShowFavorites : 1;` — Whether or not to show the favorites selector.
- L483 _public member_ `bool bNotifyDefaultPathSelected : 1;` — Whether to call OnPathSelected during construction for DefaultPath if DefaultPath is allowed
- L486 _public member_ `bool bCanShowDevelopersFolder;` — Indicates if the 'Show Developers' option should be enabled or disabled
- L489 _public member_ `bool bForceShowEngineContent;` — Indicates if engine content should always be shown
- L492 _public member_ `bool bForceShowPluginContent;` — Indicates if plugin content should always be shown
- L495 _public member_ `bool bShowViewOptions;` — if true, will add the filter setting to the path picker
- L497 _public function_ `FPathPickerConfig() : bFocusSearchBoxWhenOpened(true) , bAllowContextMenu(true) , bAllowClassesFolder(false) , bAllowReadOnlyFolders(true) , bAddDefaultPath(false) , bOnPathSelectedPassesVirtualPaths(false) , bShowFavorites(true) , bNotifyDefaultPathSelected(false) , bCanShowDevelopersFolder(true) , bForceShowEngineContent(false) , bForceShowPluginContent(false) , bShowViewOptions(false)`

#### struct `FCollectionPickerConfig`  
`struct FCollectionPickerConfig`  
_L514-534_
- desc: A struct containing details about how the collection picker should behave
- L517 _public member_ `bool AllowCollectionButtons;` — If true, collection buttons will be displayed
- L520 _public member_ `bool AllowRightClickMenu;` — If true, users will be able to access the right-click menu of a collection
- L523 _public member_ `TSharedPtr<ICollectionContainer> CollectionContainer;` — The collection container to view
- L526 _public member_ `FOnCollectionSelected OnCollectionSelected;` — Called when a collection was selected
- L528 _public function_ `FCollectionPickerConfig() : AllowCollectionButtons(true) , AllowRightClickMenu(true) , CollectionContainer(FCollectionManagerModule::GetModule().Get().GetProjectCollectionContainer()) , OnCollectionSelected()`

#### enum `EAssetDialogType::Type`  
`enum Type`  
_L538-542_
- L540 _public enumerator_ `Open`
- L541 _public enumerator_ `Save`

#### struct `FSharedAssetDialogConfig`  
`struct FSharedAssetDialogConfig`  
_L546-563_
- desc: A struct containing shared details about how asset dialogs should behave. You should not instanciate this config, but use FOpenAssetDialogConfig or FSaveAssetDialogConfig instead.
- L548 _public member_ `FText DialogTitleOverride;`
- L549 _public member_ `FString DefaultPath;`
- L550 _public member_ `TArray<FTopLevelAssetPath> AssetClassNames;`
- L551 _public member_ `FVector2D WindowSizeOverride;`
- L552 _public member_ `FOnPathSelected OnPathSelected;`
- L554 _public member_ `TSharedPtr<SWindow> WindowOverride;` — When specified, this window will be used instead of the mainframe window.
- L556 _public prototype_ `virtual EAssetDialogType::Type GetDialogType() const = 0;`
- L558 _public function_ `FSharedAssetDialogConfig() : WindowSizeOverride(ForceInitToZero)`
- L562 _public prototype_ `virtual ~FSharedAssetDialogConfig() = default;`

#### struct `FOpenAssetDialogConfig`  
`struct FOpenAssetDialogConfig : public FSharedAssetDialogConfig`  
_L566-576_
- inherits: `FSharedAssetDialogConfig`
- desc: A struct containing details about how the open asset dialog should behave.
- L568 _public member_ `bool bAllowMultipleSelection;`
- L570 _public function_ `virtual EAssetDialogType::Type GetDialogType() const override`
- L572 _public function_ `FOpenAssetDialogConfig() : FSharedAssetDialogConfig() , bAllowMultipleSelection(false)`

#### enum `ESaveAssetDialogExistingAssetPolicy::Type`  
`enum Type`  
_L581-588_
- L584 _public enumerator_ `Disallow` — Display an error and disallow the save
- L587 _public enumerator_ `AllowButWarn` — Allow the save, but warn that the existing file will be overwritten

#### struct `FSaveAssetDialogConfig`  
`struct FSaveAssetDialogConfig : public FSharedAssetDialogConfig`  
_L592-603_
- inherits: `FSharedAssetDialogConfig`
- desc: A struct containing details about how the save asset dialog should behave.
- L594 _public member_ `FString DefaultAssetName;`
- L595 _public member_ `ESaveAssetDialogExistingAssetPolicy::Type ExistingAssetPolicy;`
- L597 _public function_ `virtual EAssetDialogType::Type GetDialogType() const override`
- L599 _public function_ `FSaveAssetDialogConfig() : FSharedAssetDialogConfig() , ExistingAssetPolicy(ESaveAssetDialogExistingAssetPolicy::Disallow)`

#### class `IContentBrowserSingleton`  
`class IContentBrowserSingleton`  
_L608-939_
- desc: Content browser module singleton
- L611 _public prototype_ `static IContentBrowserSingleton& Get();`
- L614 _public prototype_ `virtual ~IContentBrowserSingleton() = default;` — Virtual destructor
- L625 _public prototype_ `virtual TSharedRef<SWidget> CreateContentBrowser( const FName InstanceName, TSharedPtr<SDockTab> ContainingTab, const FContentBrowserConfig* ContentBrowserConfig ) = 0;` — Generates a content browser.  Generally you should not call this function, but instead use CreateAssetPicker(). @param	InstanceName			Global name of this content browser instance @param	ContainingTab			The tab the browser is contained within or nullptr @param	ContentBrowserConfig	Initial defaults for the new content browser, or nullptr to use saved settings @return The newly created content browser widget
- L633 _public prototype_ `virtual TSharedRef<SWidget> CreateAssetPicker(const FAssetPickerConfig& AssetPickerConfig) = 0;` — Generates an asset picker widget locked to the specified FARFilter. @param AssetPickerConfig		A struct containing details about how the asset picker should behave @return The asset picker widget
- L636 _public prototype_ `virtual TSharedPtr<SWidget> GetAssetPickerSearchBox(const TSharedRef<SWidget>& AssetPickerWidget) = 0;` — Focus the search box of the given asset picker widget.
- L644 _public prototype_ `virtual TSharedRef<SWidget> CreatePathPicker(const FPathPickerConfig& PathPickerConfig) = 0;` — Generates a path picker widget. @param PathPickerConfig		A struct containing details about how the path picker should behave @return The path picker widget
- L652 _public prototype_ `virtual TSharedRef<SWidget> CreateCollectionPicker(const FCollectionPickerConfig& CollectionPickerConfig) = 0;` — Generates a collection picker widget. @param CollectionPickerConfig		A struct containing details about how the collection picker should behave @return The collection picker widget
- L661 _public prototype_ `virtual TSharedRef<SWidget> CreateContentBrowserDrawer(const FContentBrowserConfig& ContentBrowserConfig, TFunction<TSharedPtr<SDockTab>()> InOnGetTabForDrawer) = 0;` — Generates a content browser for use in a drawer. This content browser is a singleton and is reused among all drawers. @param ContentBrowserConfig	Initial defaults for the new content browser @return The content browser drawer widget
- L670 _public prototype_ `virtual void CreateOpenAssetDialog(const FOpenAssetDialogConfig& OpenAssetConfig, const FOnAssetsChosenForOpen& OnAssetsChosenForOpen, const FOnAssetDialogCancelled& OnAssetDialogCancelled) = 0;` — Opens the Open Asset dialog in a non-modal window @param OpenAssetConfig				A struct containing details about how the open asset dialog should behave @param OnAssetsChosenForOpen			A delegate that is fired when assets are chosen and the open button is pressed @param OnAssetDialogCancelled		A delegate that is fired when the asset dialog is closed or cancelled
- L678 _public prototype_ `virtual TArray<FAssetData> CreateModalOpenAssetDialog(const FOpenAssetDialogConfig& InConfig) = 0;` — Opens the Open Asset dialog in a modal window @param OpenAssetConfig				A struct containing details about how the open asset dialog should behave @return The assets that were chosen to be opened
- L687 _public prototype_ `virtual void CreateSaveAssetDialog(const FSaveAssetDialogConfig& SaveAssetConfig, const FOnObjectPathChosenForSave& OnAssetNameChosenForSave, const FOnAssetDialogCancelled& OnAssetDialogCancelled) = 0;` — Opens the Save Asset dialog in a non-modal window @param SaveAssetConfig				A struct containing details about how the save asset dialog should behave @param OnAssetNameChosenForSave		A delegate that is fired when an object path is chosen and the save button is pressed @param OnAssetDialogCancelled		A delegate that is fired when the asset dialog is closed or cancelled
- L695 _public prototype_ `virtual FString CreateModalSaveAssetDialog(const FSaveAssetDialogConfig& SaveAssetConfig) = 0;` — Opens the Save Asset dialog in a modal window @param SaveAssetConfig				A struct containing details about how the save asset dialog should behave @return The object path that was chosen
- L698 _public prototype_ `virtual bool HasPrimaryContentBrowser() const = 0;` — Returns true if there is at least one browser open that is eligible to be a primary content browser
- L703 _public prototype_ `virtual bool SetPrimaryContentBrowser(FName InstanceName) = 0;` — Sets the primary content browser for subsequent state changes through this singleton Returns true if content browser was changed sucessfully
- L706 _public prototype_ `virtual void FocusPrimaryContentBrowser(bool bFocusSearch) = 0;` — Brings the primary content browser to the front or opens one if it does not exist.
- L709 _public prototype_ `virtual void FocusContentBrowserSearchField(TSharedPtr<SWidget> ContentBrowserWidget) = 0;` — Focuses the search field of a content browser widget
- L712 _public prototype_ `virtual void CreateNewAsset(const FString& DefaultAssetName, const FString& PackagePath, UClass* AssetClass, UFactory* Factory) = 0;` — Sets up an inline-name for the creation of a new asset in the primary content browser using the specified path and the specified class and/or factory
- L722 _public prototype_ `virtual void SyncBrowserToAssets(const TArray<struct FAssetData>& AssetDataList, bool bAllowLockedBrowsers = false, bool bFocusContentBrowser = true, const FName& InstanceName = FName(), bool bNewSpawnBrowser = false) = 0;` — Selects the supplied assets in the primary content browser. @param AssetList                     An array of AssetDataList structs to sync. @param bAllowLockedBrowsers 	        When true, even locked browsers may handle the sync. Only set to true if the sync doesn't seem external to the content browser. @param bFocusContentBrowser          When true, brings the ContentBrowser into the foreground. @param InstanceName					When supplied, will only sync the Content Browser with the matching InstanceName.  bAllowLockedBrowsers is ignored.
- L732 _public prototype_ `virtual void SyncBrowserToAssets(const TArray<UObject*>& AssetList, bool bAllowLockedBrowsers = false, bool bFocusContentBrowser = true, const FName& InstanceName = FName(), bool bNewSpawnBrowser = false) = 0;` — Selects the supplied assets in the primary content browser. @param AssetList                     An array of UObject pointers to sync. @param bAllowLockedBrowsers 	        When true, even locked browsers may handle the sync. Only set to true if the sync doesn't seem external to the content browser. @param bFocusContentBrowser          When true, brings the ContentBrowser into the foreground. @param InstanceName					When supplied, will only sync the Content Browser with the matching InstanceName.  bAllowLockedBrowsers is ignored.
- L743 _public prototype_ `virtual void SyncBrowserToFolders(const TArray<FString>& FolderList, bool bAllowLockedBrowsers = false, bool bFocusContentBrowser = true, const FName& InstanceName = FName(), bool bNewSpawnBrowser = false) = 0;` — Selects the supplied assets in the primary content browser. @param AssetList                     An array of strings representing folder asset paths to sync. @param bAllowLockedBrowsers 	        When true, even locked browsers may handle the sync. Only set to true if the sync doesn't seem external to the content browser. @param bFocusContentBrowser          When true, brings the ContentBrowser into the foreground. @param InstanceName					When supplied, will only sync the Content Browser with the matching InstanceName.  bAllowLockedBrowsers is ignored. @param bNewSpawnBrowser				When supplied, will spawn a new Content Browser instead of selecting the assets in an existing one.
- L754 _public prototype_ `virtual void SyncBrowserToCollections(const TArray<FCollectionRef>& CollectionsToSync, bool bAllowLockedBrowsers = false, bool bFocusContentBrowser = true, const FName& InstanceName = FName(), bool bNewSpawnBrowser = false) = 0;` — Selects the supplied collections in the primary content browser. @param CollectionsToSync				An array of collections to sync. @param bAllowLockedBrowsers 	        When true, even locked browsers may handle the sync. Only set to true if the sync doesn't seem external to the content browser. @param bFocusContentBrowser          When true, brings the ContentBrowser into the foreground. @param InstanceName					When supplied, will only sync the Content Browser with the matching InstanceName.  bAllowLockedBrowsers is ignored. @param bNewSpawnBrowser				When supplied, will spawn a new Content Browser instead of selecting the assets in an existing one.
- L765 _public prototype_ `virtual void SyncBrowserToItems(const TArray<FContentBrowserItem>& ItemsToSync, bool bAllowLockedBrowsers = false, bool bFocusContentBrowser = true, const FName& InstanceName = FName(), bool bNewSpawnBrowser = false) = 0;` — Selects the supplied items in the primary content browser. @param ItemsToSync                   An array of items to sync. @param bAllowLockedBrowsers 	        When true, even locked browsers may handle the sync. Only set to true if the sync doesn't seem external to the content browser. @param bFocusContentBrowser          When true, brings the ContentBrowser into the foreground. @param InstanceName					When supplied, will only sync the Content Browser with the matching InstanceName.  bAllowLockedBrowsers is ignored. @param bNewSpawnBrowser				When supplied, will spawn a new Content Browser instead of selecting the assets in an existing one.
- L776 _public prototype_ `virtual void SyncBrowserTo(const FContentBrowserSelection& ItemSelection, bool bAllowLockedBrowsers = false, bool bFocusContentBrowser = true, const FName& InstanceName = FName(), bool bNewSpawnBrowser = false) = 0;` — Selects the supplied assets in the primary content browser. @param ItemSelection 				A struct containing AssetData and Folders to sync. @param bAllowLockedBrowsers 	        When true, even locked browsers may handle the sync. Only set to true if the sync doesn't seem external to the content browser. @param bFocusContentBrowser          When true, brings the ContentBrowser into the foreground. @param InstanceName					When supplied, will only sync the Content Browser with the matching InstanceName.  bAllowLockedBrowsers is ignored. @param bNewSpawnBrowser				When supplied, will spawn a new Content Browser instead of selecting the assets in an existing one.
- L779 _public prototype_ `virtual void GetSelectedAssets(TArray<FAssetData>& SelectedAssets) = 0;` — Generates a list of assets that are selected in the primary content browser
- L782 _public prototype_ `virtual void GetAllSelectedAssets(TArray<FAssetData>& SelectedAssets) = 0;` — Generates a list of assets that are selected across all open content browsers
- L785 _public prototype_ `virtual void GetSelectedFolders(TArray<FString>& SelectedFolders) = 0;` — Generates a list of folders that are selected in the primary content browser
- L788 _public prototype_ `virtual void GetSelectedPathViewFolders(TArray<FString>& SelectedFolders) = 0;` — Returns the folders that are selected in the path view
- L792 _public prototype_ `virtual FString GetCurrentPath(const EContentBrowserPathType PathType) = 0;` — `UE_DEPRECATED(5.0, "This function is deprecated. Use GetCurrentPath without argument instead.")` — Gets the current path if one exists, otherwise returns empty string.
- L795 _public prototype_ `virtual FContentBrowserItemPath GetCurrentPath() = 0;` — Gets the current path if one exists, otherwise returns empty string.
- L803 _public prototype_ `virtual void CaptureThumbnailFromViewport(FViewport* InViewport, TArray<FAssetData>& SelectedAssets) = 0;` — Capture active viewport to thumbnail and assigns that thumbnail to incoming assets @param InViewport - viewport to sample from @param InAssetsToAssign - assets that should receive the new thumbnail ONLY if they are assets that use GenericThumbnails
- L808 _public prototype_ `virtual void SetSelectedPaths(const TArray<FString>& FolderPaths, bool bNeedsRefresh = false, bool bPathsAreVirtual = false) = 0;` — Sets the content browser to display the selected paths
- L815 _public prototype_ `virtual void ForceShowPluginContent(bool bEnginePlugin) = 0;` — Forces the content browser to show plugin content if it's not already showing. @param bEnginePlugin	If this is true, it will also force the content browser to show engine content
- L822 _public prototype_ `virtual void SaveContentBrowserSettings(TSharedPtr<SWidget> ContentBrowserWidget) = 0;` — Saves the settings for a particular content browser instance @param ContentBrowserWidget The content browser widget to save
- L829 _public prototype_ `virtual void ExecuteRename(TSharedPtr<SWidget> PickerWidget) = 0;` — Rename current first selected content item on the passed in widget. @param PickerWidget The picker widget whose asset we want to rename, should be a asset or path picker widget.
- L836 _public prototype_ `virtual void ExecuteAddFolder(TSharedPtr<SWidget> PathPickerWidget) = 0;` — Add a folder to the path picker widget under the current selected path. @param PathPickerWidget The path picker widget where we want to add an folder
- L843 _public prototype_ `virtual void RefreshPathView(TSharedPtr<SWidget> PathPickerWidget) = 0;` — Force refresh on the path picker widget.  You may need to do this if you have changed the filter on the path picker. @param PathPickerWidget The path picker widget where we want to add an folder
- L846 _public prototype_ `virtual FContentBrowserItemPath GetInitialPathToSaveAsset(const FContentBrowserItemPath& InPath) = 0;` — Returns InPath if can be written to, otherwise picks a default path that can be written to
- L849 _public prototype_ `virtual bool IsShowingPrivateContent(const FStringView VirtualFolderPath) = 0;` — Returns true if FolderPath is a private content edit folder
- L852 _public prototype_ `virtual bool IsFolderShowPrivateContentToggleable(const FStringView VirtualFolderPath) = 0;` — Returns true if FolderPath's private content edit mode is allowed to be toggled
- L855 _public prototype_ `virtual const TSharedPtr<FPathPermissionList>& GetShowPrivateContentPermissionList() = 0;` — Returns the Private Content Permission List
- L858 _public prototype_ `virtual const TSharedPtr<FPathPermissionList>& GetShowEpicInternalContentPermissionList() = 0;` — Returns the Internal Content Permission List
- L861 _public prototype_ `virtual void SetPrivateContentPermissionListDirty() = 0;` — Declares the Private Content Permission List dirty
- L864 _public prototype_ `virtual void RegisterIsFolderShowPrivateContentToggleableDelegate(FIsFolderShowPrivateContentToggleableDelegate InIsFolderShowPrivateContentToggleableDelegate) = 0;` — Registers the delegate for custom handling of if a Folder allows private content edits
- L867 _public prototype_ `virtual void UnregisterIsFolderShowPrivateContentToggleableDelegate() = 0;` — Unregisters the delegate for custom handling of if a Folder allows private content edits
- L870 _public prototype_ `virtual FDelegateHandle RegisterOnFavoritesChangedHandler(FOnFavoritesChanged::FDelegate InOnFavoritesChanged) = 0;` — Register a delegate to be called when the Favorites changes.
- L873 _public prototype_ `virtual void UnregisterOnFavoritesChangedDelegate(FDelegateHandle Handle) = 0;` — Unregister a previously-registered handler for when Favorites changes.
- L885 _public prototype_ `virtual TArray<FString> GetAliasesForPath(const FSoftObjectPath& InPath) const = 0;` — Get a list of other paths that the data source may be using to represent a specific path @param The internal path (or object path) of an asset to get aliases for @return All alternative paths that represent the input path (not including the input path itself)
- L888 _public prototype_ `virtual void AddCustomTextFilter(const FCustomTextFilterData& FilterData, bool bApplyFilter) = 0;` — Adds a Custom Text Filter to the Filter List
- L891 _public prototype_ `virtual void DeleteCustomTextFilterByLabel(const FText& FilterLabel) = 0;` — Deletes the specified Custom Text Filter
- L894 _public prototype_ `virtual void ModifyCustomTextFilterByLabel(const FCustomTextFilterData& FilterData, const FText& FilterLabel) = 0;` — Modifies the specified Custom Text Filter
- L897 _public prototype_ `virtual bool IsAssetViewDoneFiltering() = 0;` — Gets whether the AssetView in the Content Browser is done filtering
- L900 _public prototype_ `virtual void SetSearchText(const FText& NewText) = 0;` — Sets the AssetSearchBox text
- L903 _public prototype_ `virtual void ToggleFolderFavorite(const TArray<FString>& FolderPaths) = 0;` — Toggle the Favorite status of the given folder list
- L906 _public prototype_ `virtual void ForEachFavoriteFolder(TFunctionRef<void(const FContentBrowserItemPath&)> InDelegate) = 0;` — Iterate through each favorite folder and call the delegate
- L909 _public prototype_ `virtual void SetFilterLayout(EFilterBarLayout InFilterBarLayout) = 0;` — Sets the Content Browser filter layout to either vertical or horizontal
- L912 _public prototype_ `virtual EFilterBarLayout GetFilterLayout() = 0;` — Gets the current Content Browser filter layout
- L915 _public prototype_ `virtual TSharedPtr<SWidget> GetActiveFilterContainer() = 0;` — Gets a pointer to the active filter container widget (Horizontal or Vertical), nullptr if neither is active
- L918 _public prototype_ `virtual void DockContentBrowserDrawer() = 0;` — Docks the current content browser drawer as a tabbed content browser in a layout
- L921 _public prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<UE::Editor::ContentBrowser::IContentSource>, FContentSourceFactory) virtual void RegisterContentSourceFactory(const FName& InContentSourceName, const FContentSourceFactory& InContentSourceFactory) = 0;` — Factory delegate that instantiates a content source
- L927 _public prototype_ `virtual void UnregisterContentSourceFactory(const FName& InContentSourceName) = 0;` — Unregister a content source by name
- L930 _public prototype_ `virtual void ForEachContentSourceFactory(const TFunctionRef<void(const FName&, const FContentSourceFactory&)>& InFunction) = 0;` — Execute a delegate for each registered content source factory
- L933 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnContentSourceFactoriesChanged) virtual FOnContentSourceFactoriesChanged& OnContentSourceFactoriesChanged() = 0;` — Delegate fired when a new content source factory is registered/unregistered
- L938 _public prototype_ `virtual FDelegateHandle RegisterOnFavoritesChangedHandler(FSimpleDelegate OnFavoritesChanged) = 0;` — `UE_DEPRECATED(5.7, "Use the overload that takes in an FOnFavoritesChanged delegate")` — Register a delegate to be called when the Favorites changes.

#### Free symbols / members of external scopes

- L32 _typedef_ `typedef const FContentBrowserItem& FAssetFilterType;`
- L33 _typedef_ `typedef TFilterCollection<FAssetFilterType> FAssetFilterCollectionType;`
- L35 _typedef_ `typedef const TSharedRef<IPlugin>& FPluginFilterType;`
- L36 _typedef_ `typedef TFilterCollection<FPluginFilterType> FPluginFilterCollectionType;`
- L39 _namespace_ `namespace EAssetViewType`
- L52 _namespace_ `namespace UE`
- L52 _namespace_ `namespace Editor` (scope `UE`)
- L52 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)
- L427 _function_ `` (scope `FAssetPickerConfig::IsNewStyleEnabled`)
- L536 _namespace_ `namespace EAssetDialogType`
- L579 _namespace_ `namespace ESaveAssetDialogExistingAssetPolicy`
- L921 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<UE::Editor::ContentBrowser::IContentSource>, FContentSourceFactory) virtual void RegisterContentSourceFactory(const FName& InContentSourceName, const FContentSourceFactory& InContentSourceFactory) = 0;` — Factory delegate that instantiates a content source
- L933 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnContentSourceFactoriesChanged) virtual FOnContentSourceFactoriesChanged& OnContentSourceFactoriesChanged() = 0;` — Delegate fired when a new content source factory is registered/unregistered

### `Source/Editor/ContentBrowser/Public/SAssetView.h` (Public)


#### enum `EAssetViewCopyType`  
`enum class EAssetViewCopyType`  
_L104-109_
- desc: Copy types
- L106 _public enumerator_ `ExportTextPath`
- L107 _public enumerator_ `ObjectPath`
- L108 _public enumerator_ `PackageName`

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SAssetView>`  
_L112-115_
- L114 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SAssetView`  
`class SAssetView : public SCompoundWidget`  
_L120-1466_
- inherits: `SCompoundWidget`
- desc: A widget to display a list of filtered assets
- L124 _public function_ `SLATE_BEGIN_ARGS( SAssetView ) : _InitialCategoryFilter(EContentBrowserItemCategoryFilter::IncludeAll) , _AssetShowWarningTextJustification(ETextJustify::Center) , _AssetShowWarningTextSelectable(false) , _ThumbnailLabel( EThumbnailLabel::ClassName ) , _AllowThumbnailHintLabel(true) , _bShowPathViewFilters(false) , _InitialViewType(EAssetViewType::Tile) , _InitialThumbnailSize(EThumbnailSize::Medium) , _ShowBottomToolbar(true) , _ShowViewOptions(true) , _AllowThumbnailEditMode(false) , _CanShowClasses(true) , _CanShowFolders(false) , _CanShowReadOnlyFolders(true) , _FilterRecursivelyWithBackendFilter(true) , _CanShowRealTimeThumbnails(false) , _CanShowDevelopersFolder(false) , _CanShowFavorites(false) , _CanDockCollections(false) , _SelectionMode( ESelectionMode::Multi ) , _AllowDragging(true) , _AllowFocusOnSync(true) , _FillEmptySpaceInTileView(true) , _ShowPathInColumnView(false) , _ShowTypeInColumnView(true) , _ShowAssetAccessSpecifier(false) , _SortByPathInColumnView(false) , _ShowTypeInTileView(true) , _ForceShowEngineContent(false) , _ForceShowPluginContent(false) , _ForceHideScrollbar(false) , _ShowDisallowedAssetClassAsUnsupportedItems(false) , _AllowCustomView(false)`
- L161 _public prototype_ `SLATE_EVENT( FOnShouldFilterAsset, OnShouldFilterAsset ) SLATE_EVENT(FOnShouldFilterItem, OnShouldFilterItem) SLATE_EVENT( FOnAssetViewNewItemRequested, OnNewItemRequested ) SLATE_EVENT( FOnContentBrowserItemSelectionChanged, OnItemSelectionChanged ) SLATE_EVENT( FOnContentBrowserItemsActivated, OnItemsActivated ) SLATE_EVENT( FOnContentBrowserItemsDragged, OnItemsDragged ) SLATE_EVENT( FOnGetContentBrowserItemContextMenu, OnGetItemContextMenu ) SLATE_EVENT( FOnContentBrowserItemRenameCommitted, OnItemRenameCommitted ) SLATE_EVENT(FOnIsAssetValidForCustomToolTip, OnIsAssetValidForCustomToolTip) SLATE_EVENT( FOnGetCustomAssetToolTip, OnGetCustomAssetToolTip ) SLATE_EVENT( FOnVisualizeAssetToolTip, OnVisualizeAssetToolTip ) SLATE_EVENT(FOnAssetToolTipClosing, OnAssetToolTipClosing) SLATE_EVENT(FOnExtendAssetViewOptionsMenuContext, OnExtendAssetViewOptionsMenuContext) SLATE_ARGUMENT( EContentBrowserItemCategoryFilter, InitialCategoryFilter )` — Called to check if an asset should be filtered out by external code
- L356 _public prototype_ `SAssetView();`
- L360 _public prototype_ `void Construct( const FArguments& InArgs );` — Constructs this widget with InArgs
- L363 _public prototype_ `void SetContentSources(const FAssetViewContentSources& InContentSources);` — Changes the base sources for this view
- L366 _public prototype_ `void SetSourcesData(const FSourcesData& InSourcesData);` — `UE_DEPRECATED(5.6, "Use SetContentSources() instead.")`
- L369 _public prototype_ `const FAssetViewContentSources& GetContentSources() const;` — Returns the sources filter applied to this asset view
- L372 _public prototype_ `FSourcesData GetSourcesData() const;` — `UE_DEPRECATED(5.6, "Use GetContentSources() instead.")`
- L375 _public prototype_ `bool IsAssetPathSelected() const;` — Returns true if a real asset path is selected (i.e \Engine\* or \Game\*)
- L384 _public prototype_ `void SetBackendFilter(const FARFilter& InBackendFilter, TArray<TSharedRef<const FPathPermissionList>>* InCustomPermissionLists = nullptr);` — @brief Provide a backend filter for the asset view and invalidate current source items. @param InBackendFilter Asset registry filter for uassets @param InCustomPermissionLists Optional permission lists to allow/deny specific folders. All folders will be allowed by default, so only denials will have any effect.
- L387 _public function_ `const FARFilter& GetBackendFilter() const` — Get the current backend filter
- L390 _public prototype_ `void NewFolderItemRequested(const FContentBrowserItemTemporaryContext& NewItemContext);` — Handler for when a data source requests folder item creation
- L393 _public prototype_ `void NewFileItemRequested(const FContentBrowserItemDataTemporaryContext& NewItemContext);` — Handler for when a data source requests file item creation
- L396 _public prototype_ `void CreateNewAsset(const FString& DefaultAssetName, const FString& PackagePath, UClass* AssetClass, UFactory* Factory);` — Creates a new asset item designed to allocate a new object once it is named. Uses the supplied factory to create the asset
- L399 _public prototype_ `void RenameItem(const FContentBrowserItem& ItemToRename);` — Sets up an inline rename for the specified item
- L402 _public prototype_ `void SyncToItems( TArrayView<const FContentBrowserItem> ItemsToSync, const bool bFocusOnSync = true );` — Selects the specified items.
- L406 _public prototype_ `void SyncToVirtualPaths( TArrayView<const FName> VirtualPathsToSync, const bool bFocusOnSync = true );` — `UE_DEPRECATED(5.8, "Use SyncToItems() instead.")` — Selects the specified virtual paths.
- L409 _public prototype_ `void SyncToLegacy( TArrayView<const FAssetData> AssetDataList, TArrayView<const FString> FolderList, const bool bFocusOnSync = true );` — Selects the specified assets and paths.
- L412 _public prototype_ `void InitDeferredPendingSyncItems();` — Setup Deferred Pending Sync for recently added PendingSyncItems.
- L415 _public prototype_ `void ApplyHistoryData( const FHistoryData& History );` — Sets the state of the asset view to the one described by the history data
- L418 _public prototype_ `TArray<TSharedPtr<FAssetViewItem>> GetSelectedViewItems() const;` — Returns all the items currently selected in the view
- L421 _public prototype_ `TArray<FContentBrowserItem> GetSelectedItems() const;` — Returns all the items currently selected in the view
- L424 _public prototype_ `TArray<FContentBrowserItem> GetSelectedFolderItems() const;` — Returns all the folder items currently selected in the view
- L427 _public prototype_ `TArray<FContentBrowserItem> GetSelectedFileItems() const;` — Returns all the file items currently selected in the view
- L430 _public prototype_ `TArray<FAssetData> GetSelectedAssets() const;` — Returns all the asset data objects in items currently selected in the view
- L433 _public prototype_ `TArray<FString> GetSelectedFolders() const;` — Returns all the folders currently selected in the view
- L436 _public prototype_ `void RequestSlowFullListRefresh();` — Requests that the asset view refreshes all it's source items. This is slow and should only be used if the source items change.
- L439 _public prototype_ `void RequestQuickFrontendListRefresh();` — Requests that the asset view refreshes only items that are filtered through frontend sources. This should be used when possible.
- L442 _public prototype_ `void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const;` — Saves any settings to config that should be persistent between editor sessions
- L445 _public prototype_ `void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString);` — Loads any settings to config that should be persistent between editor sessions
- L448 _public prototype_ `void AdjustActiveSelection(int32 SelectionDelta);` — Adjusts the selected asset by the selection delta, which should be +1 or -1)
- L451 _public prototype_ `bool IsRenamingAsset() const;` — Returns true if an asset is currently in the process of being renamed
- L454 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget inherited
- L455 _public prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;`
- L456 _public prototype_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L457 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L458 _public prototype_ `virtual FReply OnKeyChar( const FGeometry& MyGeometry,const FCharacterEvent& InCharacterEvent ) override;`
- L459 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L460 _public prototype_ `virtual FReply OnMouseWheel( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L461 _public prototype_ `virtual void OnFocusChanging( const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent ) override;`
- L464 _public prototype_ `void OnOpenAssetsOrFolders();` — Opens the selected assets or folders, depending on the selection
- L467 _public prototype_ `void OnPreviewAssets();` — Loads the selected assets and previews them if possible
- L470 _public prototype_ `void ClearSelection(bool bForceSilent = false);` — Clears the selection of all the lists in the view
- L473 _public prototype_ `bool IsThumbnailEditMode() const;` — Returns true if the asset view is in thumbnail editing mode
- L476 _public prototype_ `void HandleSettingChanged(FName PropertyName);` — Delegate called when an editor setting is changed
- L479 _public prototype_ `void SetUserSearching(bool bInSearching);` — Set whether the user is currently searching or not
- L486 _public prototype_ `void ForceShowPluginFolder( bool bEnginePlugin );` — Forces the plugin content folder to be shown. @param bEnginePlugin		If true, also forces the engine folder to be shown.
- L489 _public prototype_ `void OverrideShowEngineContent();` — Enables the Show Engine Content setting for the active Content Browser. The user can still toggle the setting manually.
- L492 _public prototype_ `void OverrideShowDeveloperContent();` — Enables the Show Developer Content setting for the active Content Browser. The user can still toggle the setting manually.
- L495 _public prototype_ `void OverrideShowPluginContent();` — Enables the Show Plugin Content setting for the active Content Browser. The user can still toggle the setting manually.
- L498 _public prototype_ `void OverrideShowLocalizedContent();` — Enables the Show Localized Content setting for the active Content Browser. The user can still toggle the setting manually.
- L501 _public prototype_ `bool IsIncludingClassNames() const;` — @return true when we are including class names in search criteria
- L504 _public prototype_ `bool IsIncludingAssetPaths() const;` — @return true when we are including the entire asset path in search criteria
- L507 _public prototype_ `bool IsIncludingCollectionNames() const;` — @return true when we are including collection names in search criteria
- L510 _public prototype_ `TSharedRef<SWidget> GetViewButtonContent();` — Handler for when the view combo button is clicked
- L513 _public prototype_ `void SetCurrentViewType(EAssetViewType::Type NewType);` — Sets the view type and updates lists accordingly
- L516 _public prototype_ `void SetCurrentThumbnailSize(EThumbnailSize NewThumbnailSize);` — Sets the thumbnail size and updates lists accordingly
- L519 _public prototype_ `FText GetAssetCountText() const;` — Gets the text for the asset count label
- L522 _public prototype_ `EVisibility GetMajorityAssetTypeTextVisibility() const;` — Gets the visibility for the majority asset type label
- L525 _public prototype_ `FText GetMajorityAssetTypeText() const;` — Gets the text for the majority asset type label
- L528 _public prototype_ `FText GetMajorityAssetTypeToolTipText() const;` — Gets the tooltip text for the majority asset type label
- L531 _public prototype_ `static FText ThumbnailSizeToDisplayName(EThumbnailSize InSize);` — Gets text name for given thumbnail
- L534 _public prototype_ `void SetFilterBar(TSharedPtr<SFilterList> InFilterBar);` — Set the filter list attached to this asset view - allows toggling of the the filter bar layout from the view options
- L537 _public prototype_ `void SetShouldFilterItem(FOnShouldFilterItem InCallback);` — Change the delegate bound via the widget argument OnShouldFilterAsset after construction.
- L545 _public prototype_ `void SetAssetSearchOverride(TSharedPtr<UE::Editor::ContentBrowser::Extension::ICBSearchOverrideInstance> InOverride);` — Pass the active per-view search override instance to the asset view. The asset view will intercept items at the publish step and wire publish-results back. EXPERIMENTAL: This API is subject to change.
- L549 _public prototype_ `bool HasItemsPendingFilter() const;` — True if we have items pending that ProcessItemsPendingFilter still needs to process
- L552 _public prototype_ `bool HasThumbnailsPendingUpdate() const;` — True if we have thumbnails that are pending update
- L555 _public prototype_ `bool HasDeferredItemToCreate() const;` — True if we have deferred item to create
- L558 _public prototype_ `TWeakPtr<FAssetViewSortManager> GetSortManager() const;` — Get the underlying sort manager
- L561 _public prototype_ `void SetSortParameters( const TOptional<const EColumnSortPriority::Type>& InSortPriority, const TOptional<const FName>& InColumnId, const TOptional<const EColumnSortMode::Type>& InNewSortMode);` — Set's sorting based on the given parameters, using the current value if not specified
- L567 _public prototype_ `UE_INTERNAL bool IsShowingFavorites() const;` — @return true when we are showing favorites
- L570 _public prototype_ `UE_INTERNAL bool IsShowingCppContent() const;` — @return true when we are showing C++ content
- L573 _public prototype_ `UE_INTERNAL bool IsShowingFolders() const;` — @return true when we are showing folders
- L576 _public prototype_ `UE_INTERNAL bool IsShowingEmptyFolders() const;` — @return true when we are showing empty folders
- L579 _public prototype_ `UE_INTERNAL bool IsShowingPluginContent() const;` — @return true when we are showing plugin content
- L582 _public prototype_ `UE_INTERNAL bool IsShowingEngineContent() const;` — @return true when we are showing engine content
- L585 _public prototype_ `UE_INTERNAL bool IsShowingDevelopersContent() const;` — @return true when we are showing the developers content
- L588 _public prototype_ `UE_INTERNAL bool IsShowingAllFolder() const;` — @return true when we are showing the all virtual folder
- L591 _public prototype_ `UE_INTERNAL bool IsOrganizingFolders() const;` — @return true when we are organizing folders into virtual locations
- L594 _public prototype_ `UE_INTERNAL bool IsThumbnailSizeChecked(EThumbnailSize InThumbnailSize) const;` — Is the current thumbnail size menu option checked
- L597 _public prototype_ `UE_INTERNAL bool IsCurrentViewType(EAssetViewType::Type ViewType) const;` — Returns true if ViewType is the current view type
- L601 _private prototype_ `void SyncToSelection( const bool bFocusOnSync = true );` — Sets the pending selection to the current selection (used when changing views or refreshing the view).
- L604 _private prototype_ `FString GetThumbnailScaleSettingPath(const FString& SettingsString, const FString& InViewTypeString) const;` — @return the thumbnail scale setting path to use when looking up the setting in an ini.
- L607 _private prototype_ `void LoadScaleSetting(const FString& IniFilename, const FString& IniSection, const FString& SettingsString, const FString& InViewTypeString, EThumbnailSize& OutThumbnailSize);` — Load the config for each AssetViewType size into their own container
- L610 _private prototype_ `FString GetCurrentViewTypeSettingPath(const FString& SettingsString) const;` — @return the view type setting path to use when looking up the setting in an ini.
- L613 _private prototype_ `void CalculateFillScale( const FGeometry& AllottedGeometry );` — Calculates a new filler scale used to adjust the thumbnails to fill empty space.
- L616 _private prototype_ `void CalculateThumbnailHintColorAndOpacity();` — Calculates the latest color and opacity for the hint on thumbnails
- L619 _private prototype_ `void ProcessItemsPendingFilter(const double TickStartTime);` — Handles amortizing the additional filters
- L622 _private prototype_ `TSharedRef<SAssetTileView> CreateTileView();` — Creates a new tile view
- L625 _private prototype_ `TSharedRef<SAssetListView> CreateListView();` — Creates a new list view
- L628 _private prototype_ `TSharedRef<SAssetColumnView> CreateColumnView();` — Creates a new column view
- L631 _private prototype_ `TSharedRef<SWidget> CreateCustomView();` — Creates a custom view (if specified to the content browser module)
- L633 _private prototype_ `const FSlateBrush* GetRevisionControlColumnIconBadge() const;`
- L636 _private prototype_ `bool IsValidSearchToken(const FString& Token) const;` — Returns true if the specified search token is allowed
- L639 _private prototype_ `void RefreshSourceItems();` — Regenerates the AssetItems list from the AssetRegistry
- L642 _private prototype_ `void RefreshFilteredItems();` — Regenerates the FilteredAssetItems list from the AssetItems list
- L645 _private prototype_ `void SetMajorityAssetType(FName NewMajorityAssetType);` — Sets the asset type that represents the majority of the assets in view
- L648 _private prototype_ `void OnAssetsAddedToCollection( ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection, TConstArrayView<FSoftObjectPath> ObjectPaths );` — Handler for when an asset is added to a collection
- L651 _private prototype_ `void OnAssetsRemovedFromCollection(ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection, TConstArrayView<FSoftObjectPath> ObjectPaths );` — Handler for when an asset is removed from a collection
- L654 _private prototype_ `void OnCollectionRenamed(ICollectionContainer& CollectionContainer, const FCollectionNameType& OriginalCollection, const FCollectionNameType& NewCollection );` — Handler for when a collection is renamed
- L657 _private prototype_ `void OnCollectionUpdated(ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection );` — Handler for when a collection is updated
- L660 _private prototype_ `void OnFrontendFiltersChanged();` — Handler for when any frontend filters have been changed
- L663 _private prototype_ `bool IsFrontendFilterActive() const;` — Returns true if there is any frontend filter active
- L666 _private prototype_ `bool PassesCurrentFrontendFilter(const FContentBrowserItem& Item) const;` — Returns true if the specified Content Browser item passes all applied frontend (non asset registry) filters
- L669 _private prototype_ `bool ShouldFilterRecursively() const;` — Returns true if the current filters deem that the asset view should be filtered recursively (overriding folder view)
- L672 _private prototype_ `void SortList(bool bSyncToSelection = true);` — Sorts the contents of the asset view alphabetically
- L675 _private prototype_ `FLinearColor GetThumbnailHintColorAndOpacity() const;` — Returns the thumbnails hint color and opacity
- L678 _private prototype_ `void PopulateFilterAdditionalParams(FFiltersAdditionalParams& OutParams);` — Populate the given params for this AssetView
- L681 _private member_ `static FDelayedAutoRegisterHelper AssetViewOptionsMenuRegistration;` — Registers the menu used by the settings button
- L684 _private member_ `static FDelayedAutoRegisterHelper ToolBarMenuExtensionRegistration;` — Extend the top toolbar
- L687 _private member_ `static FDelayedAutoRegisterHelper NavigationBarMenuExtensionRegistration;` — Extend the bottom navigation bar
- L689 _private prototype_ `void OnSetSortParameters(const FToolMenuContext& InMenuContext, const TOptional<const EColumnSortPriority::Type> InSortPriority, const TOptional<const FName> InColumnId, const TOptional<const EColumnSortMode::Type> InNewSortMode);`
- L695 _private prototype_ `void PopulateSortingButtonMenu(UToolMenu* Menu);` — Fill in menu content for when the sorting combo button is clicked
- L698 _private prototype_ `void ToggleShowFolders();` — Toggle whether folders should be shown or not
- L701 _private prototype_ `bool IsToggleShowFoldersAllowed() const;` — Whether or not it's possible to show folders
- L704 _private prototype_ `bool IsShowingReadOnlyFolders() const;` — @return true when we are showing read-only folders
- L707 _private prototype_ `void ToggleShowEmptyFolders();` — Toggle whether empty folders should be shown or not
- L710 _private prototype_ `bool IsToggleShowEmptyFoldersAllowed() const;` — Whether or not it's possible to show empty folders
- L713 _private prototype_ `bool IsShowingRedirectors() const;` — @return true when the asset view is showing object redirectors
- L716 _private prototype_ `void ToggleShowLocalizedContent();` — Toggle whether localized content should be shown or not
- L719 _private prototype_ `bool IsToggleShowLocalizedContentAllowed() const;` — Whether or not it's possible to show localized content
- L722 _private prototype_ `bool IsShowingLocalizedContent() const;` — @return true when we are showing folders
- L725 _private prototype_ `void ToggleRealTimeThumbnails();` — Toggle whether to show real-time thumbnails
- L728 _private prototype_ `bool CanShowRealTimeThumbnails() const;` — Whether it is possible to show real-time thumbnails
- L731 _private prototype_ `bool IsShowingRealTimeThumbnails() const;` — @return true if we are showing real-time thumbnails
- L734 _private prototype_ `void ToggleShowPluginContent();` — Toggle whether plugin content should be shown or not
- L737 _private prototype_ `void ToggleShowEngineContent();` — Toggle whether engine content should be shown or not
- L740 _private prototype_ `void ToggleShowDevelopersContent();` — Toggle whether developers content should be shown or not
- L743 _private prototype_ `bool IsToggleShowDevelopersContentAllowed() const;` — Whether or not it's possible to toggle developers content
- L746 _private prototype_ `bool IsToggleShowEngineContentAllowed() const;` — Whether or not it's possible to toggle engine content
- L749 _private prototype_ `bool IsToggleShowPluginContentAllowed() const;` — Whether or not it's possible to toggle plugin content
- L752 _private prototype_ `void ToggleShowFavorites();` — Toggle whether favorites should be shown or not
- L755 _private prototype_ `bool IsToggleShowFavoritesAllowed() const;` — Whether or not it's possible to toggle favorites
- L758 _private prototype_ `bool IsToggleShowCppContentAllowed() const;` — Whether or not it's possible to show C++ content
- L761 _private prototype_ `void ToggleIncludeClassNames();` — Toggle whether class names should be included in search criteria
- L764 _private prototype_ `bool IsToggleIncludeClassNamesAllowed() const;` — Whether or not it's possible to include class names in search criteria
- L767 _private prototype_ `void ToggleIncludeAssetPaths();` — Toggle whether the entire asset path should be included in search criteria
- L770 _private prototype_ `bool IsToggleIncludeAssetPathsAllowed() const;` — Whether or not it's possible to include the entire asset path in search criteria
- L773 _private prototype_ `void ToggleIncludeCollectionNames();` — Toggle whether collection names should be included in search criteria
- L776 _private prototype_ `bool IsToggleIncludeCollectionNamesAllowed() const;` — Whether or not it's possible to include collection names in search criteria
- L779 _private prototype_ `bool IsFilteringRecursively() const;` — @return true when we are filtering recursively when we have an asset path
- L782 _private prototype_ `bool IsToggleFilteringRecursivelyAllowed() const;` — Whether or not it's possible to toggle how to filtering recursively
- L785 _private prototype_ `void ToggleFilteringRecursively();` — Toggle whether we're filtering recursively
- L788 _private prototype_ `void ToggleShowAllFolder();` — Toggle whether we are showing the all virtual folder
- L791 _private prototype_ `void ToggleOrganizeFolders();` — Toggle whether we are re-organizing folders into virtual locations
- L794 _private prototype_ `void SetCurrentViewTypeFromMenu(EAssetViewType::Type NewType);` — Sets the view type and forcibly dismisses all currently open context menus
- L797 _private prototype_ `void CreateCurrentView();` — Clears the reference to the current view and creates a new one, based on CurrentViewType
- L800 _private prototype_ `EAssetViewType::Type GetCurrentViewType() const;` — Gets the current view type (list or tile)
- L802 _private prototype_ `TSharedRef<SWidget> CreateShadowOverlay( TSharedRef<STableViewBase> Table );`
- L805 _private prototype_ `void FocusList() const;` — Set the keyboard focus to the correct list view that should be active
- L808 _private prototype_ `bool IsPendingRefresh();` — Return true if there is currently a refresh pending, false otherwise
- L811 _private prototype_ `void RefreshList();` — Refreshes the list view to display any changes made to the non-filtered assets
- L814 _private prototype_ `void SetSelection(const TSharedPtr<FAssetViewItem>& Item);` — Sets the sole selection for all lists in the view
- L817 _private prototype_ `void SetItemSelection(const TSharedPtr<FAssetViewItem>& Item, bool bSelected, const ESelectInfo::Type SelectInfo = ESelectInfo::Direct);` — Sets selection for an item in all lists in the view
- L820 _private prototype_ `void RequestScrollIntoView(const TSharedPtr<FAssetViewItem>& Item);` — Scrolls the selected item into view for all lists in the view
- L823 _private prototype_ `TSharedRef<ITableRow> MakeListViewWidget(TSharedPtr<FAssetViewItem> AssetItem, const TSharedRef<STableViewBase>& OwnerTable);` — Handler for list view widget creation
- L826 _private prototype_ `TSharedRef<ITableRow> MakeTileViewWidget(TSharedPtr<FAssetViewItem> AssetItem, const TSharedRef<STableViewBase>& OwnerTable);` — Handler for tile view widget creation
- L829 _private prototype_ `TSharedRef<ITableRow> MakeColumnViewWidget(TSharedPtr<FAssetViewItem> AssetItem, const TSharedRef<STableViewBase>& OwnerTable);` — Handler for column view widget creation
- L832 _private prototype_ `void AssetItemWidgetDestroyed(const TSharedPtr<FAssetViewItem>& Item);` — Handler for when any asset item widget gets destroyed
- L835 _private prototype_ `void UpdateThumbnails();` — Creates new thumbnails that are near the view area and deletes old thumbnails that are no longer relevant.
- L838 _private prototype_ `TSharedPtr<FAssetThumbnail> AddItemToNewThumbnailRelevancyMap(const TSharedPtr<FAssetViewItem>& Item, TMap< TSharedPtr<FAssetViewItem>, TSharedPtr<FAssetThumbnail> >& NewRelevantThumbnails);` — Helper function for UpdateThumbnails. Adds the specified item to the new thumbnail relevancy map and creates any thumbnails for new items. Returns the thumbnail.
- L841 _private prototype_ `void AssetSelectionChanged( TSharedPtr<FAssetViewItem > AssetItem, ESelectInfo::Type SelectInfo );` — Handler for tree view selection changes
- L844 _private prototype_ `void ItemScrolledIntoView(TSharedPtr<FAssetViewItem> AssetItem, const TSharedPtr<ITableRow>& Widget);` — Handler for when an item has scrolled into view after having been requested to do so
- L847 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuContent();` — Handler for context menus
- L850 _private prototype_ `bool CanOpenContextMenu() const;` — Handler called when an asset context menu is about to open
- L853 _private prototype_ `void OnListMouseButtonDoubleClick(TSharedPtr<FAssetViewItem> AssetItem);` — Handler for double clicking an item
- L856 _private prototype_ `FReply OnDraggingAssetItem(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Handle dragging an asset
- L859 _private prototype_ `bool AssetVerifyRenameCommit(const TSharedPtr<FAssetViewItem>& Item, const FText& NewName, const FSlateRect& MessageAnchor, FText& OutErrorMessage);` — Checks if the asset name being committed is valid
- L862 _private prototype_ `void AssetRenameBegin(const TSharedPtr<FAssetViewItem>& Item, const FString& NewName, const FSlateRect& MessageAnchor);` — An asset item has started to be renamed
- L865 _private prototype_ `void AssetRenameCommit(const TSharedPtr<FAssetViewItem>& Item, const FString& NewName, const FSlateRect& MessageAnchor, const ETextCommit::Type CommitType);` — An asset item that was prompting the user for a new name was committed. Return false to indicate that the user should enter a new name
- L868 _private prototype_ `FLinearColor GetAssetNameColorAndOpacity() const;` — Gets the color and opacity for all names of assets in the asset view
- L871 _private prototype_ `bool ShouldAllowToolTips() const;` — Returns true if tooltips should be allowed right now. Tooltips are typically disabled while right click scrolling.
- L874 _private prototype_ `bool IsThumbnailEditModeAllowed() const;` — Returns true if the asset view is currently allowing the user to edit thumbnails
- L877 _private prototype_ `FReply EndThumbnailEditModeClicked();` — The "Done Editing" button was pressed in the thumbnail edit mode strip
- L880 _private prototype_ `EVisibility GetEditModeLabelVisibility() const;` — Gets the visibility of the Thumbnail Edit Mode label
- L883 _private prototype_ `EVisibility GetListViewVisibility() const;` — Gets the visibility of the list view
- L886 _private prototype_ `EVisibility GetTileViewVisibility() const;` — Gets the visibility of the tile view
- L889 _private prototype_ `EVisibility GetColumnViewVisibility() const;` — Gets the visibility of the column view
- L892 _private prototype_ `void ToggleTooltipExpandedState();` — Toggles tooltip expanded default state
- L895 _private prototype_ `bool IsTooltipExpandedByDefault();` — True if the default state of tooltip is expanded
- L898 _private prototype_ `void ToggleThumbnailEditMode();` — Toggles thumbnail editing mode
- L901 _private prototype_ `void OnThumbnailSizeChanged(EThumbnailSize NewThumbnailSize);` — Called when  thumbnail size is changed
- L904 _private prototype_ `bool IsThumbnailScalingAllowed() const;` — Are thumbnails allowed to be scaled by the user
- L907 _private prototype_ `float GetThumbnailScale() const;` — Gets the current thumbnail scale
- L910 _private prototype_ `float GetThumbnailSizeValue() const;` — Gets the current thumbnail size
- L913 _private prototype_ `void UpdateThumbnailSizeValue();` — Set the Min/Max Thumbnail size based on the EThumbnailSize chosen
- L916 _private function_ `EThumbnailSize GetThumbnailSize() const` — Gets the current thumbnail size enum
- L919 _private prototype_ `float GetTileViewTypeNameHeight() const;` — Gets the spacing dedicated to support type names
- L922 _private prototype_ `float GetSourceControlIconHeight() const;` — Gets the spacing needed to support source control icons. No scaling is required for this since the icon itself is not scaled by the thumbnail size.
- L925 _private prototype_ `float GetListViewItemHeight() const;` — Gets the scaled item height for the list view
- L928 _private prototype_ `FMargin GetListViewItemPadding() const;` — Gets the padding for the list view rows
- L931 _private prototype_ `float GetTileViewItemHeight() const;` — Gets the final scaled item height for the tile view
- L934 _private prototype_ `float GetTileViewThumbnailDimension() const;` — Get the TileView Thumbnail dimension height and width are the same for the thumbnail itself
- L937 _private prototype_ `float GetTileViewItemBaseHeight() const;` — Gets the scaled item height for the tile view before the filler scale is applied
- L940 _private prototype_ `float GetTileViewItemWidth() const;` — Gets the final scaled item width for the tile view
- L943 _private prototype_ `float GetTileViewItemBaseWidth() const;` — Gets the scaled item width for the tile view before the filler scale is applied
- L946 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;` — Gets the sort mode for the supplied ColumnId
- L949 _private prototype_ `EColumnSortPriority::Type GetColumnSortPriority(const FName ColumnId) const;` — Gets the sort order for the supplied ColumnId
- L952 _private prototype_ `void OnSortColumnHeader(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type NewSortMode);` — Handler for when a column header is clicked
- L955 _private prototype_ `TOptional< float > GetIsWorkingProgressBarState() const;` — @return The state of the is working progress bar
- L958 _private prototype_ `EVisibility IsAssetShowWarningTextVisible() const;` — Is the no assets to show warning visible?
- L961 _private prototype_ `FText GetAssetShowWarningText() const;` — Gets the warning text to show as heading (e.g. when there are no assets to show)
- L964 _private prototype_ `bool HasSingleCollectionSource() const;` — Whether we have a single source collection selected
- L967 _private prototype_ `void BeginCreateDeferredItem();` — Starts the async flow of creating a file or folder item from deferred data
- L970 _private prototype_ `FContentBrowserItem EndCreateDeferredItem(const TSharedPtr<FAssetViewItem>& InItem, const FString& InName, const bool bFinalize, FText& OutErrorText);` — Finishes the async flow of creating a file or folder item from deferred data
- L973 _private prototype_ `FText GetQuickJumpTerm() const;` — @return The current quick-jump term
- L976 _private prototype_ `EVisibility IsQuickJumpVisible() const;` — @return Whether the quick-jump term is currently visible?
- L979 _private prototype_ `FSlateColor GetQuickJumpColor() const;` — @return The color that should be used for the quick-jump term
- L982 _private prototype_ `void ResetQuickJump();` — Reset the quick-jump to its empty state
- L992 _private prototype_ `FReply HandleQuickJumpKeyDown(const TCHAR InCharacter, const bool bIsControlDown, const bool bIsAltDown, const bool bTestOnly);` — Called from OnKeyChar and OnKeyDown to handle quick-jump key presses @param InCharacter		The character that was typed @param bIsControlDown	Was the control key pressed? @param bIsAltDown		Was the alt key pressed? @param bTestOnly			True if we only want to test whether the key press would be handled, but not actually update the quick-jump term @return FReply::Handled or FReply::Unhandled
- L999 _private prototype_ `bool PerformQuickJump(const bool bWasJumping);` — Perform a quick-jump to the next available asset in FilteredAssetItems that matches the current term @param bWasJumping		True if we were performing an ongoing quick-jump last Tick @return True if the quick-jump found a valid match, false otherwise
- L1002 _private prototype_ `void ResetColumns();` — Resets the column filtering state to make them all visible
- L1005 _private prototype_ `void ExportColumns();` — Export columns to CSV
- L1008 _private prototype_ `void OnHiddenColumnsChanged();` — Called when a column is shown/hidden in the column view
- L1011 _private prototype_ `FVector2D GetMaxRowSizeForColumn(const FName& ColumnId);` — Will compute the max row size from all its children for the specified column id
- L1014 _private prototype_ `void AppendBackendFilter(FARFilter& FilterToAppendTo) const;` — Append the current effective backend filter (intersection of BackendFilter and SupportedFilter) to the given filter.
- L1016 _private prototype_ `EContentBrowserItemCategoryFilter DetermineItemCategoryFilter() const;`
- L1017 _private prototype_ `FContentBrowserDataFilter CreateBackendDataFilter(bool bInvalidateCache) const;`
- L1020 _private prototype_ `void HandleItemDataUpdated(TArrayView<const FContentBrowserItemDataUpdate> InUpdatedItems);` — Handles updating the view when content items are changed
- L1023 _private prototype_ `void HandleItemDataDiscoveryComplete();` — Notification for when the content browser has completed it's initial search
- L1026 _private prototype_ `FContentBrowserInstanceConfig* GetContentBrowserConfig() const;` — Get the config struct for the owning Content Browser, if one exists.
- L1029 _private prototype_ `FAssetViewInstanceConfig* GetAssetViewConfig() const;` — Get the config struct for this asset view, if one exists.
- L1032 _private prototype_ `void BindCommands();` — Bind our UI commands
- L1035 _private prototype_ `void PopulateSelectedFilesAndFolders(TArray<FContentBrowserItem>& OutSelectedFolders, TArray<FContentBrowserItem>& OutSelectedFiles) const;` — Populate the given parameters based on the current selection
- L1038 _private prototype_ `void ExecuteCopy(EAssetViewCopyType InCopyType) const;` — Handler for the CopyReference CopyObjectPath and CopyPackageName
- L1041 _private prototype_ `void ExecuteCopyFolders(const TArray<FContentBrowserItem>& InSelectedFolders, FString& OutClipboardText) const;` — Append folders path to the given ClipboardText
- L1044 _private prototype_ `void ExecutePaste();` — Handler for Paste
- L1047 _private prototype_ `bool IsCustomViewSet() const;` — Check if the custom view view is available
- L1051 _private prototype_ `void CancelPendingRename();` — Cancel the ongoing rename if there is one before starting another one.
- L1056 _private member_ `TPimplPtr<FAssetViewItemCollection> Items;` — Private type managing data retrieved from the backend and async filtering thereof
- L1059 _private member_ `TArray<TSharedPtr<FAssetViewItem>> FilteredAssetItems;` — The items that are being shown in the filtered view list
- L1062 _private member_ `TMap<FName, int32> FilteredAssetItemTypeCounts;` — Map of an item name to the current count of FilteredAssetItems that are of that type
- L1065 _private member_ `EAssetViewType::Type CurrentViewType;` — The list view that is displaying the assets
- L1066 _private member_ `TSharedPtr<SAssetListView> ListView;`
- L1067 _private member_ `TSharedPtr<SAssetTileView> TileView;`
- L1068 _private member_ `TSharedPtr<SListView<TSharedPtr<FAssetViewItem>>> ColumnView;`
- L1069 _private member_ `TSharedPtr<SBox> ViewContainer;`
- L1072 _private member_ `TWeakPtr<SContentBrowser> OwningContentBrowser;` — The content browser that created this asset view if any
- L1075 _private member_ `TWeakPtr<SFilterList> FilterBar;` — The Filter Bar attached to this asset view if any
- L1078 _private member_ `FAssetViewContentSources ContentSources;` — The current base source filter for the view
- L1079 _private member_ `FARFilter BackendFilter;`
- L1080 _private member_ `TSharedPtr<FPathPermissionList> AssetClassPermissionList;`
- L1081 _private member_ `TSharedPtr<FPathPermissionList> FolderPermissionList;`
- L1082 _private member_ `TSharedPtr<FPathPermissionList> WritableFolderPermissionList;`
- L1085 _private member_ `TArray<TSharedRef<const FPathPermissionList>> BackendCustomPathFilters;` — Paths which should be filtered out based on current filters the user has selected - not 'permissions' so may be ignore if e.g. the user explicitly selects a filtered folder
- L1086 _private member_ `TSharedPtr<FAssetFilterCollectionType> FrontendFilters;`
- L1087 _private member_ `TSharedPtr<FAssetTextFilter> TextFilter;`
- L1092 _private member_ `float ZoomScale = 0.0f;` — Scale when using CTRL+Wheel, will go from 0.f to 1.f and reset accordingly when ThumbnailSize chosen changes\n When going over/under the limit will also change the ThumbnailSize
- L1095 _private member_ `static constexpr int32 TileViewHeightPadding = 9;` — Vertical padding for the TileViewItem
- L1098 _private member_ `static constexpr int32 TileViewWidthPadding = 8;` — Horizontal padding for the TileViewItem
- L1100 _private member_ `TAttribute<bool> bShowRedirectors;`
- L1101 _private member_ `bool bLastShowRedirectors;`
- L1104 _private member_ `bool bShowPathViewFilters;` — Show path view filters submenu in view options menu
- L1107 _private member_ `bool bSlowFullListRefreshRequested;` — If true, the source items will be refreshed next frame. Very slow.
- L1110 _private member_ `bool bQuickFrontendListRefreshRequested;` — If true, the frontend items will be refreshed next frame. Much faster.
- L1113 _private member_ `bool bLoadingSettings = false;` — True when loading settings, this is needed for the HiddenColumns for example to not double update them
- L1116 _private member_ `bool bListViewColumnsManuallyChangedOnce = false;` — Set to true as soon as the user change the ListView visibility of a column, after that point the Loaded Hidden Columns will be used instead of any default given
- L1119 _private member_ `bool bColumnViewColumnsManuallyChangedOnce = false;` — Set to true as soon as the user change the ColumnView visibility of a column, after that point the Loaded Hidden Columns will be used instead of any default given
- L1122 _private member_ `FSelectionData PendingSyncItems;` — The list of items to sync next frame
- L1125 _private member_ `FSelectionData DeferredPendingSyncItems;` — The list of items used to ensure all the pending sync items are selected due to async nature of filtering
- L1128 _private member_ `int32 DeferredSyncTimeoutFrames = 0;` — A Timeout counter to safeguard against infinite deferement of pending sync items
- L1131 _private member_ `bool bPendingFocusOnSync;` — Should we take focus when the PendingSyncAssets are processed?
- L1134 _private member_ `bool bWereItemsRecursivelyFiltered;` — Was recursive filtering enabled the last time a full slow refresh performed?
- L1137 _private member_ `FOnShouldFilterAsset OnShouldFilterAsset;` — Called to check if an asset should be filtered out by external code
- L1140 _private member_ `FOnShouldFilterItem OnShouldFilterItem;` — Called to check if an item should be filtered out by external code
- L1144 _private member_ `TSharedPtr<UE::Editor::ContentBrowser::Extension::ICBSearchOverrideInstance> AssetSearchOverride;` — Active per-view search override instance; when set, intercepts items at the publish step.
- L1148 _private member_ `FOnAssetViewNewItemRequested OnNewItemRequested;` — Called when the asset view is asked to start to create a temporary item
- L1151 _private member_ `FOnContentBrowserItemSelectionChanged OnItemSelectionChanged;` — Called when an item was selected in the list. Provides more context than OnAssetSelected.
- L1154 _private member_ `FOnContentBrowserItemsActivated OnItemsActivated;` — Called when the user double clicks, presses enter, or presses space on a Content Browser item
- L1157 _private member_ `FOnContentBrowserItemsDragged OnItemsDragged;` — Called when the user drags a Content Browser item
- L1160 _private member_ `FOnGetContentBrowserItemContextMenu OnGetItemContextMenu;` — Delegate to invoke when generating the context menu for an item
- L1163 _private member_ `FOnContentBrowserItemRenameCommitted OnItemRenameCommitted;` — Called when the user has committed a rename of one or more items
- L1166 _private member_ `FOnShouldDisplayAssetTag OnAssetTagWantsToBeDisplayed;` — Called to check if an asset tag should be display in details view.
- L1169 _private member_ `FOnIsAssetValidForCustomToolTip OnIsAssetValidForCustomToolTip;` — Called to see if it is valid to get a custom asset tool tip
- L1172 _private member_ `FOnGetCustomAssetToolTip OnGetCustomAssetToolTip;` — Called to get a custom asset item tooltip (If necessary)
- L1175 _private member_ `FOnVisualizeAssetToolTip OnVisualizeAssetToolTip;` — Called when a custom asset item is about to show a tooltip
- L1178 _private member_ `FOnAssetToolTipClosing OnAssetToolTipClosing;` — Called when a custom asset item's tooltip is closing
- L1181 _private member_ `FOnGetCustomSourceAssets OnGetCustomSourceAssets;` — Called to add extra asset data to the asset view, to display virtual assets. These get treated similar to Class assets
- L1184 _private member_ `FOnSearchOptionChanged OnSearchOptionsChanged;` — Called when a search option changes to notify that results should be rebuilt
- L1187 _private member_ `FOnColumnVisibilityChanged OnColumnVisibilityChanged;` — Called when the user changes column visibility
- L1190 _private member_ `FOnExtendAssetViewOptionsMenuContext OnExtendAssetViewOptionsMenuContext;` — Called when opening view options menu
- L1193 _private member_ `TOptional<FName> AssetViewOptionsProfile;` — An optional profile name for the asset view options menu.
- L1196 _private member_ `bool bPendingSortFilteredItems;` — When true, filtered list items will be sorted next tick. Provided another sort hasn't happened recently or we are renaming an asset
- L1197 _private member_ `double CurrentTime;`
- L1198 _private member_ `double LastSortTime;`
- L1199 _private member_ `double SortDelaySeconds;`
- L1202 _private member_ `TWeakPtr<FAssetViewItem> AwaitingScrollIntoViewForRename;` — Weak ptr to the asset that is waiting to be renamed when scrolled into view, and the window is active
- L1205 _private member_ `TWeakPtr<FAssetViewItem> AwaitingRename;` — Weak ptr to the asset that is waiting to be renamed now that it has scrolled into view, if window is active
- L1208 _private member_ `TWeakPtr<FAssetViewItem> RenamingAsset;` — Set when the user is in the process of naming an asset
- L1211 _private member_ `TSharedPtr<FAssetThumbnailPool> AssetThumbnailPool;` — Pool for maintaining and rendering thumbnails
- L1214 _private member_ `TMap< TSharedPtr<FAssetViewItem>, TSharedPtr<FAssetThumbnail> > RelevantThumbnails;` — A map of FAssetViewAsset to the thumbnail that represents it. Only items that are currently visible or within half of the FilteredAssetItems array index distance described by NumOffscreenThumbnails are in this list
- L1217 _private member_ `TArray< TSharedPtr<FAssetViewItem> > VisibleItems;` — The set of FAssetItems that currently have widgets displaying them.
- L1220 _private member_ `int32 NumOffscreenThumbnails;` — The number of thumbnails to keep for asset items that are not currently visible. Half of the thumbnails will be before the earliest item and half will be after the latest.
- L1223 _private member_ `int32 CurrentThumbnailSize;` — The current size of relevant thumbnails
- L1226 _private member_ `bool bPendingUpdateThumbnails;` — Flag to defer thumbnail updates until the next frame
- L1229 _private member_ `int32 ListViewThumbnailResolution;` — The size of thumbnails
- L1230 _private member_ `int32 ListViewThumbnailSize;`
- L1231 _private member_ `int32 ListViewThumbnailPadding;`
- L1232 _private member_ `float ListViewItemHeight;`
- L1233 _private member_ `int32 TileViewThumbnailResolution;`
- L1234 _private member_ `int32 TileViewThumbnailSize;`
- L1235 _private member_ `int32 TileViewThumbnailPadding;`
- L1236 _private member_ `int32 TileViewNameHeight;`
- L1239 _private member_ `float MinThumbnailScale;` — The max and min thumbnail scales as a fraction of the rendered size
- L1240 _private member_ `float MaxThumbnailScale;`
- L1243 _private member_ `float MinThumbnailSize;` — The max and min thumbnail sizes
- L1244 _private member_ `float MaxThumbnailSize;`
- L1247 _private member_ `float ThumbnailScaleRangeScalar;` — Scalar applied to thumbnail sizes so that users thumbnails are scaled based on users display area size
- L1250 _private member_ `TMap<EAssetViewType::Type, EThumbnailSize> ThumbnailSizes;` — Current thumbnail sizes
- L1253 _private member_ `const FString GridViewSpecifier = TEXT("Gri` — Specifiers used for Config
- L1254 _private member_ `const FString ListViewSpecifier = TEXT("Lis`
- L1255 _private member_ `const FString ColumnViewSpecifier = TEXT("Col`
- L1256 _private member_ `const FString CustomViewSpecifier = TEXT("Cus`
- L1259 _private member_ `float FillScale;` — The amount to scale each thumbnail so that the empty space is filled.
- L1262 _private member_ `FName MajorityAssetType;` — When in columns view, this is the name of the asset type which is most commonly found in the recent results
- L1265 _private member_ `FText MajorityAssetTypeText;` — When in columns view, this is the display name of the asset type which is most commonly found in the recent results
- L1268 _private member_ `TSharedPtr<FAssetViewSortManager> SortManager;` — The manager responsible for sorting assets in the view
- L1271 _private member_ `bool bFillEmptySpaceInTileView;` — Flag indicating if we will be filling the empty space in the tile view.
- L1274 _private member_ `bool bBulkSelecting;` — When true, selection change notifications will not be sent
- L1277 _private member_ `bool bAllowThumbnailEditMode : 1;` — When true, the user may edit thumbnails
- L1280 _private member_ `bool bThumbnailEditMode : 1;` — True when the asset view is currently allowing the user to edit thumbnails
- L1283 _private member_ `bool bCanShowClasses : 1;` — Indicates if this view is allowed to show classes
- L1286 _private member_ `bool bCanShowFolders : 1;` — Indicates if the 'Show Folders' option should be enabled or disabled
- L1289 _private member_ `bool bCanShowReadOnlyFolders : 1;` — Indicates if this view is allowed to show folders that cannot be written to
- L1292 _private member_ `bool bFilterRecursivelyWithBackendFilter : 1;` — If true, recursive filtering will be caused by applying a backend filter
- L1295 _private member_ `bool bCanShowRealTimeThumbnails : 1;` — Indicates if the 'Real-Time Thumbnails' option should be enabled or disabled
- L1298 _private member_ `bool bCanShowDevelopersFolder : 1;` — Indicates if the 'Show Developers' option should be enabled or disabled
- L1301 _private member_ `bool bCanShowFavorites : 1;` — Indicates if the 'Show Favorites' option should be enabled or disabled
- L1304 _private member_ `bool bShowPathInColumnView : 1;` — If true, it will show path column in the asset view
- L1307 _private member_ `bool bShowTypeInColumnView : 1;` — If true, it will show type in the asset view
- L1310 _private member_ `bool bShowAssetAccessSpecifier : 1;` — If true, it will show EAssetAccessSpecifier
- L1313 _private member_ `bool bSortByPathInColumnView : 1;` — If true, it sorts by path and then name
- L1316 _private member_ `bool bShowTypeInTileView : 1;` — If true, it will show type in the tile view
- L1319 _private member_ `bool bForceShowEngineContent : 1;` — If true, engine content is always shown
- L1322 _private member_ `bool bForceShowPluginContent : 1;` — If true, plugin content is always shown
- L1325 _private member_ `bool bForceHideScrollbar : 1;` — If true, scrollbar is never shown, removes scroll border entirely
- L1328 _private member_ `bool bAllowDragging : 1;` — Whether to allow dragging of items
- L1331 _private member_ `bool bAllowFocusOnSync : 1;` — Whether this asset view should allow focus on sync or not
- L1334 _private member_ `bool bUserSearching : 1;` — Flag set if the user is currently searching
- L1337 _private member_ `bool bShouldNotifyNextAssetSync : 1;` — Whether or not to notify about newly selected items on on the next asset sync
- L1340 _private member_ `ESelectionMode::Type SelectionMode;` — The current selection mode used by the asset view
- L1343 _private member_ `float MaxSecondsPerFrame;` — The max number of results to process per tick
- L1346 _private member_ `double AmortizeStartTime;` — When delegate amortization began
- L1349 _private member_ `double TotalAmortizeTime;` — The total time spent amortizing the delegate filter
- L1352 _private member_ `int32 InitialNumAmortizedTasks;` — The initial number of tasks when we started performing amortized work (used to display a progress cue to the user)
- L1355 _private member_ `TAttribute< FText > HighlightedText;` — The text to highlight on the assets
- L1358 _private member_ `EThumbnailLabel::Type ThumbnailLabel;` — What the label on the thumbnails should be
- L1361 _private member_ `bool AllowThumbnailHintLabel;` — Whether to ever show the hint label on thumbnails
- L1364 _private member_ `FCurveSequence ThumbnailHintFadeInSequence;` — The sequence used to generate the opacity of the thumbnail hint
- L1367 _private member_ `FLinearColor ThumbnailHintColorAndOpacity;` — The current thumbnail hint color and opacity
- L1370 _private member_ `TAttribute<FText> AssetShowWarningText;` — The warning text to show as heading (e.g. when there are no assets to show)
- L1373 _private member_ `TAttribute<ETextJustify::Type> AssetShowWarningTextJustification;` — The justification to use for the AssetShowWarning text (see AssetShowWarningText)
- L1376 _private member_ `TAttribute<bool> AssetShowWarningTextSelectable;` — Whether to allow selection of the warning text or not
- L1379 _private member_ `EContentBrowserItemCategoryFilter InitialCategoryFilter;` — Initial set of item categories that this view should show - may be adjusted further by things like CanShowClasses or legacy delegate bindings
- L1382 _private member_ `TSharedPtr<FUICommandList> Commands;` — Commands handled by this widget
- L1384 _private member_ `bool bShowDisallowedAssetClassAsUnsupportedItems = false;`
- L1395 _private member_ `TUniquePtr<FCreateDeferredItemData> DeferredItemToCreate;` — File or folder item pending deferred creation
- L1425 _private member_ `FQuickJumpData QuickJumpData;` — Data for the asset quick-jump
- L1428 _private member_ `TArray<FString> DefaultHiddenColumnNames;` — Column filtering state
- L1429 _private member_ `TArray<FString> HiddenColumnNames;`
- L1430 _private member_ `TArray<FString> ListHiddenColumnNames;`
- L1431 _private member_ `TArray<FString> DefaultListHiddenColumnNames;`
- L1433 _private member_ `TArray<FAssetViewCustomColumn> CustomColumns;`
- L1436 _private member_ `FContentBrowserDataFilterCacheIDOwner FilterCacheID;` — An Id for the cache of the data sources for the filters compilation
- L1439 _private member_ `TSharedPtr<IContentBrowserViewExtender> ViewExtender;` — An extender to create the custom view
- L1442 _private member_ `TSharedPtr<SWidget> CustomView;` — The actual widget for the custom view
- L1445 _private member_ `TSet<FSoftObjectPath> AlreadyAddedOriginalAssets;` — Existing item paths to avoid duplicates
- L1451 _private member_ `FGuid ViewCorrelationGuid;` — Guid to correlate different telemetry events for this instance of an asset view over time
- L1453 _private member_ `FGuid FilterSessionCorrelationGuid;` — Guid to correlate different telemetry events for a 'session' of search/filtering, reset when new backend items are gathered for filtering
- L1455 _private member_ `UE::Telemetry::ContentBrowser::FFrontendFilterTelemetry CurrentFrontendFilterTelemetry;` — In progress filter session telemetry - will be sent when filtering ends or user cancels or interacts with a partial filter set
- L1458 _private prototype_ `void OnCompleteFiltering(double InAmortizeDuration);` — If there is in-progress filter telemetry, mark it as complete and send pending data
- L1460 _private prototype_ `void OnInterruptFiltering();` — If there is in-progress filter telemetry, mark it as incomplete and send pending data
- L1462 _private prototype_ `void OnInteractDuringFiltering();` — Update telemetry for user interaction during an incomplete filtering
- L1465 _public prototype_ `bool ShouldColumnGenerateWidget(const FString ColumnName) const;`

#### struct `SAssetView::FCreateDeferredItemData`  
`struct FCreateDeferredItemData`  
_L1387-1392_
- desc: A struct to hold data for the deferred creation of a file or folder item
- L1389 _public member_ `FContentBrowserItemTemporaryContext ItemContext;`
- L1391 _public member_ `bool bWasAddedToView = false;`

#### struct `SAssetView::FQuickJumpData`  
`struct FQuickJumpData`  
_L1398-1422_
- desc: Struct holding the data for the asset quick-jump
- L1400 _public function_ `FQuickJumpData() : bIsJumping(false) , bHasChangedSinceLastTick(false) , bHasValidMatch(false) , LastJumpTime(0)`
- L1409 _public member_ `bool bIsJumping;` — True if we're currently performing an ongoing quick-jump
- L1412 _public member_ `bool bHasChangedSinceLastTick;` — True if the jump data has changed since the last Tick
- L1415 _public member_ `bool bHasValidMatch;` — True if the jump term found a valid match
- L1418 _public member_ `double LastJumpTime;` — Time (taken from Tick) that we last performed a quick-jump
- L1421 _public member_ `FString JumpTerm;` — The string we should be be looking for

#### Free symbols / members of external scopes

- L52 _macro_ `#define UE_API CONTENTBROWSER_API`
- L95 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAssetViewNewItemRequested, const FContentBrowserItem& );` — Fires whenever the asset view is asked to start to create a temporary item
- L95 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAssetViewNewItemRequested, const FContentBrowserItem& );` — Fires whenever the asset view is asked to start to create a temporary item
- L98 _delegate_ `DECLARE_DELEGATE(FOnSearchOptionChanged);` — Fires whenever one of the "Search" options changes, useful for modifying search criteria to match
- L98 _prototype_ `DECLARE_DELEGATE(FOnSearchOptionChanged);` — Fires whenever one of the "Search" options changes, useful for modifying search criteria to match
- L101 _delegate_ `DECLARE_DELEGATE_OneParam(FOnExtendAssetViewOptionsMenuContext, FToolMenuContext&);` — Fires whenever asset view options menu is being opened, gives chance for external code to set additional context
- L101 _prototype_ `DECLARE_DELEGATE_OneParam(FOnExtendAssetViewOptionsMenuContext, FToolMenuContext&);` — Fires whenever asset view options menu is being opened, gives chance for external code to set additional context

### `Source/Editor/ContentBrowser/Public/SourcesData.h` (Public)


#### struct `FSourcesData`  
`struct FSourcesData`  
_L12-79_
- reflection: `UE_DEPRECATED(5.6, "FSourcesData has been deprecated in favor of FAssetViewContentSources")`
- L14 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnEnumerateCustomSourceItemDatas, TFunctionRef<bool(class FContentBrowserItemData&&)>) TArray<FName> VirtualPaths;`
- L17 _public member_ `TArray<FCollectionNameType> Collections;`
- L18 _public member_ `FOnEnumerateCustomSourceItemDatas OnEnumerateCustomSourceItemDatas;`
- L19 _public member_ `bool bIncludeVirtualPaths = true;`
- L21 _public prototype_ `FSourcesData() = default;`
- L23 _public function_ `explicit FSourcesData(FName InVirtualPath)`
- L28 _public function_ `explicit FSourcesData(FCollectionNameType InCollection)`
- L33 _public function_ `FSourcesData(TArray<FName> InVirtualPaths, TArray<FCollectionNameType> InCollections) : VirtualPaths(MoveTemp(InVirtualPaths)) , Collections(MoveTemp(InCollections))`
- L39 _public prototype_ `FSourcesData(const FSourcesData& Other) = default;`
- L40 _public prototype_ `FSourcesData(FSourcesData&& Other) = default;`
- L42 _public prototype_ `FSourcesData& operator=(const FSourcesData& Other) = default;`
- L43 _public prototype_ `FSourcesData& operator=(FSourcesData&& Other) = default;`
- L45 _public function_ `FORCEINLINE bool IsEmpty() const`
- L50 _public function_ `FORCEINLINE bool HasVirtualPaths() const`
- L55 _public function_ `FORCEINLINE bool HasCollections() const`
- L60 _public function_ `FORCEINLINE bool IsIncludingVirtualPaths() const`
- L65 _public function_ `bool IsDynamicCollection() const`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnEnumerateCustomSourceItemDatas, TFunctionRef<bool(class FContentBrowserItemData&&)>) TArray<FName> VirtualPaths;`

### `Source/Editor/ContentBrowser/Public/TextFilterKeyValueHandler.h` (Public)


#### class `UTextFilterKeyValueHandler`  
`UTextFilterKeyValueHandler : public UObject`  
_L12-17_
- reflection: `UCLASS(abstract, transient, MinimalAPI)`
- reflection: `UE_DEPRECATED(5.5, "This type has been replaced by IAssetTextFilterHandler which must be manually instantiated and registered and must be implemented in a threadsafe way.")`
- inherits: `UObject`
- L16 _public function_ `virtual bool HandleTextFilterKeyValue(const FContentBrowserItem& InContentBrowserItem, const FName& InKey, const FTextFilterString& InValue, const ETextFilterComparisonOperation InComparisonOperation, const ETextFilterTextComparisonMode InTextComparisonMode, bool& bOutIsMatch) const`

### `Source/Editor/ContentBrowser/Public/TextFilterValueHandler.h` (Public)


#### class `UTextFilterValueHandler`  
`UTextFilterValueHandler : public UObject`  
_L12-17_
- reflection: `UCLASS(abstract, transient, MinimalAPI)`
- reflection: `UE_DEPRECATED(5.5, "This type has been replaced by IAssetTextFilterHandler which must be manually instantiated and registered and must be implemented in a threadsafe way.")`
- inherits: `UObject`
- L16 _public function_ `virtual bool HandleTextFilterValue(const FContentBrowserItem& InContentBrowserItem, const FTextFilterString& InValue, const ETextFilterTextComparisonMode InTextComparisonMode, bool& bOutIsMatch) const`

### `Source/Editor/ContentBrowser/Public/Widgets/SAssetMenuIcon.h` (Public)


#### class `SAssetMenuIcon`  
`class SAssetMenuIcon : public SCompoundWidget`  
_L15-28_
- inherits: `SCompoundWidget`
- desc: Represents an Asset Type within a menu.
- L18 _public function_ `SLATE_BEGIN_ARGS(SAssetMenuIcon) : _IconContainerSize(32.0f, 32.0f) , _IconSize(28.0f, 28.0f)`
- L22 _public prototype_ `SLATE_ARGUMENT(FVector2D, IconContainerSize) SLATE_ARGUMENT(FVector2D, IconSize) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UClass* InAssetClass, const FName InIconOverride = NAME_None);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CONTENTBROWSER_API`
