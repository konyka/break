# Plugins / ContentBrowserAssetDataSource

- module root: `Plugins/Editor/ContentBrowser/ContentBrowserAssetDataSource/Source/ContentBrowserAssetDataSource`
- headers: 10; symbols: 522
- symbol kinds: class=11, delegate=7, function=19, macro=7, member=106, namespace=7, prototype=350, struct=11, typedef=4
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, CollectionManager, ContentBrowser, EditorFramework, EditorWidgets, Engine, InputCore, Json, Projects, Slate, SlateCore, SourceControl, SourceControlWindows, ToolMenus, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: ContentBrowserData, Core, CoreUObject
- PublicIncludePathModuleNames: AssetRegistry

### `Plugins/Editor/ContentBrowser/ContentBrowserAssetDataSource/Source/ContentBrowserAssetDataSource/Private/ContentBrowserAssetDataSourceCommands.h` (Private)


#### class `FContentBrowserAssetDataSourceCommands`  
`class FContentBrowserAssetDataSourceCommands : public TCommands<FContentBrowserAssetDataSourceCommands>`  
_L8-18_
- inherits: `TCommands<FContentBrowserAssetDataSourceCommands>`
- L11 _public prototype_ `FContentBrowserAssetDataSourceCommands();`
- L14 _public prototype_ `virtual void RegisterCommands() override;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> CaptureThumbnail;`

### `Plugins/Editor/ContentBrowser/ContentBrowserAssetDataSource/Source/ContentBrowserAssetDataSource/Private/ContentBrowserUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)
- L12 _function_ `static bool IsNewStyleEnabled()` (scope `UE::Editor::ContentBrowser`)
- L16 _function_ `` (scope `UE::Editor::ContentBrowser::IsNewStyleEnabled`)

### `Plugins/Editor/ContentBrowser/ContentBrowserAssetDataSource/Source/ContentBrowserAssetDataSource/Public/AssetFileContextMenu.h` (Public)


#### class `FAssetFileContextMenu`  
`class FAssetFileContextMenu : public TSharedFromThis<FAssetFileContextMenu>`  
_L15-267_
- inherits: `TSharedFromThis<FAssetFileContextMenu>`
- L18 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnShowAssetsInPathsView, const TArray<FAssetData>& );`
- L19 _public prototype_ `DECLARE_DELEGATE(FOnRefreshView);`
- L22 _public prototype_ `void MakeContextMenu( UToolMenu* InMenu, const TArray<FAssetData>& InSelectedAssets, const FOnShowAssetsInPathsView& InOnShowAssetsInPathsView );` — Makes the context menu widget
- L43 _private prototype_ `void GetSelectedAssetsByClass(TMap<UClass*, TArray<FAssetData> >& OutSelectedAssetsByClass) const;` — Helper to load selected assets and sort them by UClass
- L46 _private prototype_ `void GetSelectedAssetSourceFilePaths(TArray<FString>& OutFilePaths, TArray<FString>& OutUniqueSourceFileLabels, int32 &OutValidSelectedAssetCount) const;` — Helper to collect resolved filepaths for all selected assets
- L49 _private prototype_ `bool AreImportedAssetActionsVisible() const;` — Handler to check to see if a imported asset actions should be visible in the menu
- L52 _private prototype_ `bool CanExecuteImportedAssetActions(const TArray<FString> ResolvedFilePaths) const;` — Handler to check to see if imported asset actions are allowed
- L55 _private prototype_ `bool CanExecuteReimportAssetActions(const TArray<FString> ResolvedFilePaths) const;` — Handler to check to see if reimport asset actions are allowed
- L58 _private prototype_ `void ExecuteReimport(int32 SourceFileIndex = INDEX_NONE);` — Handler for Reimport
- L60 _private prototype_ `void ExecuteReimportWithNewFile(int32 SourceFileIndex = INDEX_NONE);`
- L63 _private prototype_ `void ExecuteFindSourceInExplorer(const TArray<FString> ResolvedFilePaths);` — Handler for FindInExplorer
- L66 _private prototype_ `void ExecuteOpenInExternalEditor(const TArray<FString> ResolvedFilePaths);` — Handler for OpenInExternalEditor
- L69 _private prototype_ `bool CanExecuteLoad() const;` — Handler to check to see if a load command is allowed
- L72 _private prototype_ `void ExecuteLoad();` — Handler for Load
- L75 _private prototype_ `bool CanExecuteReload() const;` — Handler to check to see if a reload command is allowed
- L78 _private prototype_ `void ExecuteReload();` — Handler for Reload
- L81 _private prototype_ `bool CanExecuteReloadUncooked() const;` — Handler to check to see if a reload uncooked command is allowed
- L84 _private prototype_ `void ExecuteReloadUncooked();` — Handler for Reload Uncooked
- L87 _private prototype_ `bool CanModifyPath(const FString& InPath) const;` — Is allowed to modify files or folders under this path
- L90 _private prototype_ `void AddMenuOptions(UToolMenu* Menu);` — Adds options to menu
- L93 _private prototype_ `bool AddImportedAssetMenuOptions(UToolMenu* Menu);` — Adds asset type-specific menu options to a menu builder. Returns true if any options were added.
- L96 _private prototype_ `bool AddCommonMenuOptions(UToolMenu* Menu);` — Adds common menu options to a menu builder. Returns true if any options were added.
- L99 _private prototype_ `void MakeAssetActionsSubMenu(UToolMenu* Menu);` — Adds Asset Actions sub-menu to a menu builder.
- L102 _private prototype_ `bool CanExecuteAssetActions() const;` — Handler to check to see if "Asset Actions" are allowed
- L105 _private prototype_ `void MakeAssetLocalizationSubMenu(UToolMenu* Menu);` — Adds Asset Localization sub-menu to a menu builder.
- L108 _private prototype_ `void MakeCreateLocalizedAssetSubMenu(UToolMenu* Menu, TSet<FSoftObjectPath> InSelectedSourceAssets, TArray<FLocalizedAssetsState> InLocalizedAssetsState);` — Adds the Create Localized Asset sub-menu to a menu builder.
- L111 _private prototype_ `void MakeShowLocalizedAssetSubMenu(UToolMenu* Menu, TArray<FLocalizedAssetsState> InLocalizedAssetsState);` — Adds the Show Localized Assets sub-menu to a menu builder.
- L114 _private prototype_ `void MakeEditLocalizedAssetSubMenu(UToolMenu* Menu, TArray<FLocalizedAssetsState> InLocalizedAssetsState);` — Adds the Edit Localized Assets sub-menu to a menu builder.
- L117 _private prototype_ `void ExecuteCreateLocalizedAsset(TSet<FSoftObjectPath> InSelectedSourceAssets, FLocalizedAssetsState InLocalizedAssetsStateForCulture);` — Create new localized assets for the given culture
- L120 _private prototype_ `void ExecuteFindInAssetTree(TArray<FSoftObjectPath> InAssets);` — Find the given assets in the Content Browser
- L123 _private prototype_ `void ExecuteOpenEditorsForAssets(TArray<FSoftObjectPath> InAssets);` — Open the given assets in their respective editors
- L126 _private prototype_ `bool AddDocumentationMenuOptions(UToolMenu* Menu);` — Adds asset documentation menu options to a menu builder. Returns true if any options were added.
- L129 _private prototype_ `void MakeChunkIDListMenu(UToolMenu* Menu);` — Creates a sub-menu of Chunk IDs that are are assigned to all selected assets
- L132 _private prototype_ `void ExecuteCreateBlueprintUsing();` — Handler for when create using asset is selected
- L135 _private prototype_ `void ExecuteFindAssetInWorld();` — Handler for when "Find in World" is selected
- L138 _private prototype_ `void ExecutePropertyMatrix();` — Handler for when "Property Matrix..." is selected
- L141 _private prototype_ `void ExecuteShowAssetMetaData();` — Handler for when "Show MetaData" is selected
- L144 _private prototype_ `void ExecuteCopyAssetRegistryTags();` — Handler for when "Copy Asset Registry Tags" is selected
- L147 _private prototype_ `void ExecuteDiffSelected() const;` — Handler for when "Diff Selected" is selected
- L150 _private prototype_ `void ExecuteConsolidate();` — Handler for Consolidate
- L154 _private prototype_ `void ExecuteCaptureThumbnail();` — `UE_DEPRECATED(5.8, "Use UE::Editor::ContentBrowserAssetDataSource instead")` — Handler for Capture Thumbnail
- L157 _private prototype_ `void ExecuteClearThumbnail();` — Handler for Clear Thumbnail
- L160 _private prototype_ `void ExecuteMigrateAsset();` — Handler for when "Migrate Asset" is selected
- L163 _private prototype_ `void ExecuteGoToCodeForAsset(UClass* SelectedClass);` — Handler for GoToAssetCode
- L166 _private prototype_ `void ExecuteGoToDocsForAsset(UClass* SelectedClass);` — Handler for GoToAssetDocs
- L169 _private prototype_ `void ExecuteGoToDocsForAsset(UClass* SelectedClass, const FString ExcerptSection);` — Handler for GoToAssetDocs
- L173 _private prototype_ `void ExecuteResetLocalizationId();` — Handler for resetting the localization ID of the current selection
- L177 _private prototype_ `void ExecuteShowLocalizationCache(const FAssetData InAsset, const FString InPackageFilename);` — Handler for showing the cached list of localized texts stored in the package header
- L180 _private prototype_ `void ExecuteExport();` — Handler for Export
- L183 _private prototype_ `void ExecuteBulkExport();` — Handler for Bulk Export
- L186 _private prototype_ `void ExecuteAssignChunkID();` — Handler to assign ChunkID to a selection of assets
- L189 _private prototype_ `void ExecuteRemoveAllChunkID();` — Handler to remove all ChunkID assignments from a selection of assets
- L192 _private prototype_ `void ExecuteRemoveChunkID(int32 ChunkID);` — Handler to remove a single ChunkID assignment from a selection of assets
- L195 _private prototype_ `void ExportSelectedAssetsToText();` — Handler to export the selected asset(s) to experimental text format
- L198 _private prototype_ `void ViewSelectedAssetAsText();` — Handler to export the selected asset(s) to experimental text format
- L199 _private prototype_ `bool CanViewSelectedAssetAsText() const;`
- L202 _private prototype_ `void DoTextFormatRoundtrip();` — Run the rountrip test on this asset
- L205 _private prototype_ `bool CanExecuteCreateBlueprintUsing() const;` — Handler to check if we can create blueprint using selected asset
- L208 _private prototype_ `bool CanExecuteFindAssetInWorld() const;` — Handler to check to see if a find in world command is allowed
- L211 _private prototype_ `bool CanExecuteProperties() const;` — Handler to check to see if a properties command is allowed
- L214 _private prototype_ `bool CanExecutePropertyMatrix(FText& OutErrorMessage) const;` — Handler to check to see if a property matrix command is allowed
- L215 _private prototype_ `bool CanExecutePropertyMatrix() const;`
- L219 _private prototype_ `bool CanExecuteCaptureThumbnail() const;` — `UE_DEPRECATED(5.8, "Use UE::Editor::ContentBrowserAssetDataSource instead")` — Handler to check to see if "Capture Thumbnail" can be executed
- L222 _private prototype_ `bool CanClearCustomThumbnails() const;` — Handler to check to see if "Clear Thumbnail" should be visible
- L225 _private prototype_ `void CacheCanExecuteVars();` — Initializes some variable used to in "CanExecute" checks that won't change at runtime or are too expensive to check every frame.
- L228 _private prototype_ `void GetSelectedPackageNames(TArray<FString>& OutPackageNames) const;` — Helper function to gather the package names of all selected assets
- L231 _private prototype_ `void GetSelectedPackages(TArray<UPackage*>& OutPackages) const;` — Helper function to gather the packages containing all selected assets
- L234 _private prototype_ `void OnChunkIDAssignChanged(int32 ChunkID);` — Update internal state logic
- L237 _private prototype_ `TOptional<int32> GetChunkIDSelection() const;` — Gets the current value of the ChunkID entry box
- L240 _private prototype_ `FReply OnChunkIDAssignCommit(TSharedPtr<SWindow> Window);` — Handles when the Assign chunkID dialog OK button is clicked
- L243 _private prototype_ `FReply OnChunkIDAssignCancel(TSharedPtr<SWindow> Window);` — Handles when the Assign chunkID dialog Cancel button is clicked
- L246 _private prototype_ `FText GetExecutePropertyMatrixTooltip() const;` — Generates tooltip for the Property Matrix menu option
- L249 _private prototype_ `void GetSelectedAssets(TArray<UObject*>& Assets, bool SkipRedirectors) const;` — Generates a list of selected assets in the content browser
- L252 _private prototype_ `void GetSelectedAssetData(TArray<FAssetData>& AssetDataList, bool SkipRedirectors) const;` — Generates a list of selected assets in the content browser, and returns the asset data so you do not have to load them
- L255 _private member_ `TArray<FAssetData> SelectedAssets;`
- L257 _private member_ `TWeakPtr<SWidget> ParentWidget;`
- L259 _private member_ `FOnShowAssetsInPathsView OnShowAssetsInPathsView;`
- L260 _private member_ `FOnRefreshView OnRefreshView;`
- L263 _private member_ `bool bAtLeastOneNonRedirectorSelected = false;` — Cached CanExecute vars
- L266 _private member_ `int32 ChunkIDSelected = 0;`

#### struct `FAssetFileContextMenu::FSourceAssetsState`  
`struct FSourceAssetsState`  
_L29-33_
- L31 _public member_ `TSet<FSoftObjectPath> SelectedAssets;`
- L32 _public member_ `TSet<FSoftObjectPath> CurrentAssets;`

#### struct `FAssetFileContextMenu::FLocalizedAssetsState`  
`struct FLocalizedAssetsState`  
_L35-39_
- L37 _public member_ `FCulturePtr Culture;`
- L38 _public member_ `TSet<FSoftObjectPath> CurrentAssets;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CONTENTBROWSERASSETDATASOURCE_API`
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnShowAssetsInPathsView, const TArray<FAssetData>& );`
- L19 _delegate_ `DECLARE_DELEGATE(FOnRefreshView);`

### `Plugins/Editor/ContentBrowser/ContentBrowserAssetDataSource/Source/ContentBrowserAssetDataSource/Public/AssetFolderContextMenu.h` (Public)


#### class `FAssetFolderContextMenu`  
`class FAssetFolderContextMenu : public TSharedFromThis<FAssetFolderContextMenu>`  
_L11-50_
- inherits: `TSharedFromThis<FAssetFolderContextMenu>`
- L15 _public prototype_ `void MakeContextMenu( UToolMenu* InMenu, const TArray<FString>& InSelectedPackagePaths );` — `UE_DEPRECATED(5.1, "Use the new overload.")`
- L26 _public prototype_ `void MakeContextMenu( UToolMenu* InMenu, const TArray<FString>& InSelectedPackagePaths, const TArray<FString>& InSelectedPackages );` — Makes the context menu widget @param InMenu The menu in which the entries will be added @param InSelectedPackagePaths The path of the selected folders @param InSelectedPackages The package names of the selected asset item. Empty if the selection is only some folder items.
- L34 _private prototype_ `void AddMenuOptions(UToolMenu* Menu);` — Makes the asset tree context menu widget
- L37 _private prototype_ `void ExecuteMigrateFolder();` — Handler for when "Migrate Folder" is selected
- L40 _private prototype_ `void ExecuteFixUpRedirectorsInFolder();` — Handler for when "Fix up Redirectors in Folder" is selected
- L43 _private prototype_ `FString GetFirstSelectedPath() const;` — Gets the first selected path, if it exists
- L46 _private member_ `TArray<FString> SelectedPaths;`
- L49 _private member_ `TArray<FString> SelectedPackages;` — Not null if the selection contained some assets also

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CONTENTBROWSERASSETDATASOURCE_API`

### `Plugins/Editor/ContentBrowser/ContentBrowserAssetDataSource/Source/ContentBrowserAssetDataSource/Public/AssetPropertyTagCache.h` (Public)


#### class `FAssetPropertyTagCache`  
`class FAssetPropertyTagCache`  
_L12-86_
- desc: Singleton cache of property tags data for each asset class.
- L61 _public prototype_ `static FAssetPropertyTagCache& Get();` — Get the singleton instance
- L64 _public prototype_ `void TryCacheClass(FTopLevelAssetPath InClassName);` — Try and populate the cache for the given class if it is loaded
- L67 _public prototype_ `void CachePendingClasses();` — Try and populate the cache with classes which were not reigstered when TryCacheClass was called.
- L70 _public prototype_ `const FClassPropertyTagCache& GetCacheForClass(FTopLevelAssetPath InClassName);` — Get (or populate) the cache for the given asset class
- L73 _public prototype_ `const FClassPropertyTagCache* FindCacheForClass(FTopLevelAssetPath InClassName);` — Get the cache for the given asset class if it has been created
- L76 _private member_ `mutable FRWLock Lock;`
- L82 _private member_ `TMap<FTopLevelAssetPath, TSharedPtr<FClassPropertyTagCache>> ClassToCacheMap;` — Mapping of the asset class name to its cache. Values are not modified after construction, so they can safely be returned after releasing the lock.
- L85 _private member_ `TSet<FTopLevelAssetPath> PendingClasses;` — Classes we'd like to register but were not loaded when an asset of that type was last scanned

#### struct `FAssetPropertyTagCache::FPropertyTagCache`  
`struct FPropertyTagCache`  
_L15-34_
- L18 _public member_ `UObject::FAssetRegistryTag::ETagType TagType = UObject::FAssetRegistryTag::TT_Hidden;` — The kind of data represented by this tag value
- L21 _public member_ `uint32 DisplayFlags = UObject::FAssetRegistryTag::TD_None;` — Flags giving hints at how to display this tag value in the UI (see ETagDisplay)
- L24 _public member_ `FText DisplayName;` — Resolved display name of the associated tag
- L27 _public member_ `FText TooltipText;` — Optional tooltip of the associated tag
- L30 _public member_ `FText Suffix;` — Optional suffix to apply to values of the tag attribute in the UI
- L33 _public member_ `FString ImportantValue;` — Optional value which denotes which values should be considered "important" in the UI

#### struct `FAssetPropertyTagCache::FClassPropertyTagCache`  
`struct FClassPropertyTagCache`  
_L36-58_
- L41 _public function_ `const FPropertyTagCache* GetCacheForTag(const FName InTagName) const`
- L47 _public function_ `FName GetTagNameFromAlias(const FName InTagName) const` — See whether the given name is a known alias of a tag, and if so, return the real tag name
- L54 _private member_ `TSortedMap<FName, FPropertyTagCache, FDefaultAllocator, FNameFastLess> TagNameToCachedDataMap;` — Map of an internal tag name to its cached data
- L57 _private member_ `TSortedMap<FName, FName, FDefaultAllocator, FNameFastLess> DisplayNameToTagNameMap;` — Map of a tag display name back to its real internal name

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CONTENTBROWSERASSETDATASOURCE_API`

### `Plugins/Editor/ContentBrowser/ContentBrowserAssetDataSource/Source/ContentBrowserAssetDataSource/Public/ContentBrowserAssetDataCore.h` (Public)


#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogContentBrowserAssetDataSource, Log, Log);`
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogContentBrowserAssetDataSource, Log, Log);`
- L24 _namespace_ `namespace ContentBrowserAssetData`
- L27 _prototype_ `FContentBrowserItemData CreateAssetFolderItem( UContentBrowserDataSource* InOwnerDataSource, const FName InVirtualPath, const FName InInternalFolderPath, const bool bIsCookedPath = false, const bool bIsPlugin = false);` (scope `ContentBrowserAssetData`)
- L34 _prototype_ `FContentBrowserItemData CreateAssetFileItem( UContentBrowserDataSource* InOwnerDataSource, const FName InVirtualPath, const FName InInternalPath, const FAssetData& InAssetData, const bool bIsPlugin = false);` (scope `ContentBrowserAssetData`)
- L41 _prototype_ `FContentBrowserItemData CreateUnsupportedAssetFileItem( UContentBrowserDataSource* InOwnerDataSource, const FName InVirtualPath, const FName InInternalPath, const FAssetData& InAssetData);` (scope `ContentBrowserAssetData`)
- L47 _prototype_ `TSharedPtr<const FContentBrowserAssetFolderItemDataPayload> GetAssetFolderItemPayload(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem);` (scope `ContentBrowserAssetData`)
- L49 _prototype_ `TSharedPtr<const FContentBrowserAssetFileItemDataPayload> GetAssetFileItemPayload(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem);` (scope `ContentBrowserAssetData`)
- L51 _prototype_ `TSharedPtr<const FContentBrowserUnsupportedAssetFileItemDataPayload> GetUnsupportedAssetFileItemPayload(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem);` (scope `ContentBrowserAssetData`)
- L53 _prototype_ `void EnumerateAssetFolderItemPayloads(const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, TFunctionRef<bool(const TSharedRef<const FContentBrowserAssetFolderItemDataPayload>&)> InFolderPayloadCallback);` (scope `ContentBrowserAssetData`)
- L55 _prototype_ `void EnumerateAssetFileItemPayloads(const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, TFunctionRef<bool(const TSharedRef<const FContentBrowserAssetFileItemDataPayload>&)> InAssetPayloadCallback);` (scope `ContentBrowserAssetData`)
- L57 _prototype_ `void EnumerateAssetItemPayloads(const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, TFunctionRef<bool(const TSharedRef<const FContentBrowserAssetFolderItemDataPayload>&)> InFolderPayloadCallback, TFunctionRef<bool(const TSharedRef<const FContentBrowserAssetFileItemDataPayload>&)> InAssetPayloadCallback);` (scope `ContentBrowserAssetData`)
- L61 _prototype_ `bool IsPrimaryAsset(const FAssetData& InAssetData);` (scope `ContentBrowserAssetData`)
- L63 _prototype_ `bool IsPrimaryAsset(UObject* InObject);` (scope `ContentBrowserAssetData`)
- L65 _prototype_ `void SetOptionalErrorMessage(FText* OutErrorMsg, FText InErrorMsg);` (scope `ContentBrowserAssetData`)
- L67 _prototype_ `bool CanModifyPath(IAssetTools* InAssetTools, const FName InFolderPath, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L69 _prototype_ `bool CanModifyItem(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L71 _prototype_ `bool CanModifyAssetFolderItem(IAssetTools* InAssetTools, const FContentBrowserAssetFolderItemDataPayload& InFolderPayload, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L73 _prototype_ `bool CanModifyAssetFileItem(IAssetTools* InAssetTools, const FContentBrowserAssetFileItemDataPayload& InAssetPayload, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L75 _prototype_ `bool CanEditItem(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L77 _prototype_ `bool CanEditAssetFileItem(IAssetTools* InAssetTools, const FContentBrowserAssetFileItemDataPayload& InAssetPayload, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L79 _prototype_ `bool EditItems(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems);` (scope `ContentBrowserAssetData`)
- L81 _prototype_ `bool EditAssetFileItems(TArrayView<const TSharedRef<const FContentBrowserAssetFileItemDataPayload>> InAssetPayloads);` (scope `ContentBrowserAssetData`)
- L83 _prototype_ `bool CanViewItem(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L85 _prototype_ `bool CanViewAssetFileItem(IAssetTools* InAssetTools, const FContentBrowserAssetFileItemDataPayload& InAssetPayload, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L87 _prototype_ `bool ViewItems(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems);` (scope `ContentBrowserAssetData`)
- L89 _prototype_ `bool ViewAssetFileItems(TArrayView<const TSharedRef<const FContentBrowserAssetFileItemDataPayload>> InAssetPayloads);` (scope `ContentBrowserAssetData`)
- L91 _prototype_ `bool CanPreviewItem(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L93 _prototype_ `bool CanPreviewAssetFileItem(IAssetTools* InAssetTools, const FContentBrowserAssetFileItemDataPayload& InAssetPayload, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L95 _prototype_ `bool PreviewItems(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems);` (scope `ContentBrowserAssetData`)
- L97 _prototype_ `bool PreviewAssetFileItems(TArrayView<const TSharedRef<const FContentBrowserAssetFileItemDataPayload>> InAssetPayloads);` (scope `ContentBrowserAssetData`)
- L99 _prototype_ `bool CanDuplicateItem(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L101 _prototype_ `bool CanDuplicateAssetFileItem(IAssetTools* InAssetTools, const FContentBrowserAssetFileItemDataPayload& InAssetPayload, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L103 _prototype_ `bool DuplicateItem(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, UObject*& OutSourceAsset, FAssetData& OutNewAsset);` (scope `ContentBrowserAssetData`)
- L105 _prototype_ `bool DuplicateAssetFileItem(IAssetTools* InAssetTools, const FContentBrowserAssetFileItemDataPayload& InAssetPayload, UObject*& OutSourceAsset, FAssetData& OutNewAsset);` (scope `ContentBrowserAssetData`)
- L107 _prototype_ `bool DuplicateItems(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, TArray<FAssetData>& OutNewAssets);` (scope `ContentBrowserAssetData`)
- L109 _prototype_ `bool DuplicateAssetFileItems(TArrayView<const TSharedRef<const FContentBrowserAssetFileItemDataPayload>> InAssetPayloads, TArray<FAssetData>& OutNewAssets);` (scope `ContentBrowserAssetData`)
- L111 _prototype_ `bool CanSaveItem(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, const EContentBrowserItemSaveFlags InSaveFlags, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L113 _prototype_ `bool CanSaveAssetFileItem(IAssetTools* InAssetTools, const FContentBrowserAssetFileItemDataPayload& InAssetPayload, const EContentBrowserItemSaveFlags InSaveFlags, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L115 _prototype_ `bool SaveItems(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, const EContentBrowserItemSaveFlags InSaveFlags);` (scope `ContentBrowserAssetData`)
- L117 _prototype_ `bool SaveAssetFileItems(TArrayView<const TSharedRef<const FContentBrowserAssetFileItemDataPayload>> InAssetPayloads, const EContentBrowserItemSaveFlags InSaveFlags);` (scope `ContentBrowserAssetData`)
- L119 _prototype_ `bool CanDeleteItem(IAssetTools* InAssetTools, IAssetRegistry* InAssetRegistry, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L121 _prototype_ `bool CanDeleteAssetFolderItem(IAssetTools* InAssetTools, IAssetRegistry* InAssetRegistry, const FContentBrowserAssetFolderItemDataPayload& InFolderPayload, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L123 _prototype_ `bool CanDeleteAssetFileItem(IAssetTools* InAssetTools, const FContentBrowserAssetFileItemDataPayload& InAssetPayload, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L125 _prototype_ `bool CanDeleteUnsupportedAssetFileItem(IAssetTools* InAssetTools, const FContentBrowserUnsupportedAssetFileItemDataPayload& InUnsupportedAssetPayload, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L127 _prototype_ `bool DeleteItems(FContentBrowserModule* InContentBrowserModule, IAssetTools* InAssetTools, IAssetRegistry* InAssetRegistry, const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems);` (scope `ContentBrowserAssetData`)
- L129 _prototype_ `bool DeleteAssetFolderItems(FContentBrowserModule* InContentBrowserModule, TArrayView<const TSharedRef<const FContentBrowserAssetFolderItemDataPayload>> InFolderPayloads);` (scope `ContentBrowserAssetData`)
- L131 _prototype_ `bool DeleteAssetFileItems(TArrayView<const TSharedRef<const FContentBrowserAssetFileItemDataPayload>> InAssetPayloads);` (scope `ContentBrowserAssetData`)
- L133 _prototype_ `bool DeleteUnsupportedAssetFileItems(TArrayView<const TSharedRef<const FContentBrowserUnsupportedAssetFileItemDataPayload>> InUnsupportedAssetPayloads);` (scope `ContentBrowserAssetData`)
- L135 _prototype_ `bool CanPrivatizeItem(IAssetTools* InAssetTools, IAssetRegistry* InAssetRegistry, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L137 _prototype_ `bool CanPrivatizeAssetFileItem(IAssetTools* InAssetTools, const FContentBrowserAssetFileItemDataPayload& InAssetPayload, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L139 _prototype_ `bool PrivatizeItems(IAssetTools* InAssetTools, IAssetRegistry* InAssetRegistry, const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, const EAssetAccessSpecifier InAssetAccessSpecifier = EAssetAccessSpecifier::Private);` (scope `ContentBrowserAssetData`)
- L141 _prototype_ `bool CanRenameItem(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, const FString* InNewName, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L142 _prototype_ `bool CanRenameItem(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, const bool bCheckUniqueName, const FString* InNewName, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L144 _prototype_ `bool CanRenameAssetFolderItem(IAssetTools* InAssetTools, const FContentBrowserAssetFolderItemDataPayload& InFolderPayload, const FString* InNewName, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L145 _prototype_ `bool CanRenameAssetFolderItem(IAssetTools* InAssetTools, const FContentBrowserAssetFolderItemDataPayload& InFolderPayload, const bool bCheckUniqueName, const FString* InNewName, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L147 _prototype_ `bool CanRenameAssetFileItem(IAssetTools* InAssetTools, const FContentBrowserAssetFileItemDataPayload& InAssetPayload, const FString* InNewName, const bool InIsTempoarary, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L148 _prototype_ `bool CanRenameAssetFileItem(IAssetTools* InAssetTools, const FContentBrowserAssetFileItemDataPayload& InAssetPayload, const bool bCheckUniqueName, const FString* InNewName, const bool InIsTempoarary, FText* OutErrorMsg);` (scope `ContentBrowserAssetData`)
- L150 _prototype_ `bool RenameItem(IAssetTools* InAssetTools, IAssetRegistry* InAssetRegistry, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, const FString& InNewName);` (scope `ContentBrowserAssetData`)
- L152 _prototype_ `bool RenameAssetFolderItem(IAssetRegistry* InAssetRegistry, const FContentBrowserAssetFolderItemDataPayload& InFolderPayload, const FString& InNewName);` (scope `ContentBrowserAssetData`)
- L154 _prototype_ `bool RenameAssetFileItem(IAssetTools* InAssetTools, const FContentBrowserAssetFileItemDataPayload& InAssetPayload, const FString& InNewName);` (scope `ContentBrowserAssetData`)
- L156 _prototype_ `bool CopyItems(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, const FName InDestPath);` (scope `ContentBrowserAssetData`)
- L158 _prototype_ `bool CopyAssetFolderItems(TArrayView<const TSharedRef<const FContentBrowserAssetFolderItemDataPayload>> InFolderPayloads, const FName InDestPath);` (scope `ContentBrowserAssetData`)
- L160 _prototype_ `bool CopyAssetFileItems(TArrayView<const TSharedRef<const FContentBrowserAssetFileItemDataPayload>> InAssetPayloads, const FName InDestPath);` (scope `ContentBrowserAssetData`)
- L162 _prototype_ `bool MoveItems(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, const FName InDestPath);` (scope `ContentBrowserAssetData`)
- L164 _prototype_ `bool MoveAssetFolderItems(TArrayView<const TSharedRef<const FContentBrowserAssetFolderItemDataPayload>> InFolderPayloads, const FName InDestPath);` (scope `ContentBrowserAssetData`)
- L166 _prototype_ `bool MoveAssetFileItems(TArrayView<const TSharedRef<const FContentBrowserAssetFileItemDataPayload>> InAssetPayloads, const FName InDestPath);` (scope `ContentBrowserAssetData`)
- L168 _prototype_ `bool IsItemDirty(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem);` (scope `ContentBrowserAssetData`)
- L170 _prototype_ `bool IsAssetFileItemDirty(const FContentBrowserAssetFileItemDataPayload& InAssetPayload);` (scope `ContentBrowserAssetData`)
- L172 _prototype_ `bool UpdateItemThumbnail(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FAssetThumbnail& InThumbnail);` (scope `ContentBrowserAssetData`)
- L174 _prototype_ `bool UpdateAssetFileItemThumbnail(const FContentBrowserAssetFileItemDataPayload& InAssetPayload, FAssetThumbnail& InThumbnail);` (scope `ContentBrowserAssetData`)
- L176 _prototype_ `bool AppendItemReference(IAssetRegistry* InAssetRegistry, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FString& InOutStr);` (scope `ContentBrowserAssetData`)
- L178 _prototype_ `bool AppendItemObjectPath(IAssetRegistry* InAssetRegistry, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FString& InOutStr);` (scope `ContentBrowserAssetData`)
- L180 _prototype_ `bool AppendItemPackageName(IAssetRegistry* InAssetRegistry, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FString& InOutStr);` (scope `ContentBrowserAssetData`)
- L182 _prototype_ `bool AppendAssetFolderItemReference(IAssetRegistry* InAssetRegistry, const FContentBrowserAssetFolderItemDataPayload& InFolderPayload, FString& InOutStr);` (scope `ContentBrowserAssetData`)
- L184 _prototype_ `bool AppendAssetFileItemReference(const FContentBrowserAssetFileItemDataPayload& InAssetPayload, FString& InOutStr);` (scope `ContentBrowserAssetData`)
- L186 _prototype_ `bool AppendAssetFileObjectPath(const FContentBrowserAssetFileItemDataPayload& InAssetPayload, FString& InOutStr);` (scope `ContentBrowserAssetData`)
- L188 _prototype_ `bool AppendAssetFilePackageName(const FContentBrowserAssetFileItemDataPayload& InAssetPayload, FString& InOutStr);` (scope `ContentBrowserAssetData`)
- L190 _prototype_ `bool AppendUnsupportedAssetFileItemReference(const FContentBrowserUnsupportedAssetFileItemDataPayload& InUnsupportedAssetPayload, FString& InOutStr);` (scope `ContentBrowserAssetData`)
- L192 _prototype_ `bool AppendUnsupportedAssetFileObjectPath(const FContentBrowserUnsupportedAssetFileItemDataPayload& InUnsupportedAssetPayload, FString& InOutStr);` (scope `ContentBrowserAssetData`)
- L194 _prototype_ `bool AppendUnsupportedAssetFilePackageName(const FContentBrowserUnsupportedAssetFileItemDataPayload& InUnsupportedAssetPayload, FString& InOutStr);` (scope `ContentBrowserAssetData`)
- L196 _prototype_ `bool GetItemPhysicalPath(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FString& OutDiskPath);` (scope `ContentBrowserAssetData`)
- L198 _prototype_ `bool GetAssetFolderItemPhysicalPath(const FContentBrowserAssetFolderItemDataPayload& InFolderPayload, FString& OutDiskPath);` (scope `ContentBrowserAssetData`)
- L200 _prototype_ `bool GetAssetFileItemPhysicalPath(const FContentBrowserAssetFileItemDataPayload& InAssetPayload, FString& OutDiskPath);` (scope `ContentBrowserAssetData`)
- L202 _prototype_ `bool GetUnsupportedAssetFileItemPhysicalPath(const FContentBrowserUnsupportedAssetFileItemDataPayload& InUnsupportedAssetPayload, FString& OutDiskPath);` (scope `ContentBrowserAssetData`)
- L204 _prototype_ `bool GetItemAttribute(FContentBrowserModule* InContentBrowserModule, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue);` (scope `ContentBrowserAssetData`)
- L206 _prototype_ `bool GetAssetFolderItemAttribute(const FContentBrowserAssetFolderItemDataPayload& InFolderPayload, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue);` (scope `ContentBrowserAssetData`)
- L208 _prototype_ `bool GetAssetFileItemAttribute(const FContentBrowserAssetFileItemDataPayload& InAssetPayload, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue);` (scope `ContentBrowserAssetData`)
- L210 _prototype_ `bool GetUnsupportedAssetFileItemAttribute(const FContentBrowserUnsupportedAssetFileItemDataPayload& InUnsupportedAssetPayload, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue);` (scope `ContentBrowserAssetData`)
- L212 _prototype_ `bool GetAssetDataAttribute(const FAssetData& InAssetData, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue);` (scope `ContentBrowserAssetData`)
- L214 _prototype_ `bool GetItemAttributes(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, const bool InIncludeMetaData, FContentBrowserItemDataAttributeValues& OutAttributeValues);` (scope `ContentBrowserAssetData`)
- L216 _prototype_ `bool GetAssetFileItemAttributes(const FContentBrowserAssetFileItemDataPayload& InAssetPayload, const bool InIncludeMetaData, FContentBrowserItemDataAttributeValues& OutAttributeValues);` (scope `ContentBrowserAssetData`)
- L218 _prototype_ `bool GetUnsupportedAssetFileItemAttributes(const FContentBrowserUnsupportedAssetFileItemDataPayload& InUnsupportedAssetPayload, const bool InIncludeMetaData, FContentBrowserItemDataAttributeValues& OutAttributeValues);` (scope `ContentBrowserAssetData`)
- L220 _prototype_ `bool GetAssetDataAttributes(const FAssetData& InAssetData, const bool InIncludeMetaData, FContentBrowserItemDataAttributeValues& OutAttributeValues);` (scope `ContentBrowserAssetData`)
- L222 _prototype_ `bool GetAssetAccessSpecifier(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, EAssetAccessSpecifier& OutAssetAccessSpecifier);` (scope `ContentBrowserAssetData`)
- L224 _prototype_ `bool CanModifyAssetAccessSpecifier(IAssetTools* InAssetTools, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem);` (scope `ContentBrowserAssetData`)
- L226 _prototype_ `void PopulateAssetFolderContextMenu(UContentBrowserDataSource* InOwnerDataSource, UToolMenu* InMenu, FAssetFolderContextMenu& InAssetFolderContextMenu);` (scope `ContentBrowserAssetData`)
- L228 _prototype_ `void PopulateAssetFileContextMenu(UContentBrowserDataSource* InOwnerDataSource, UToolMenu* InMenu, FAssetFileContextMenu& InAssetFileContextMenu);` (scope `ContentBrowserAssetData`)

### `Plugins/Editor/ContentBrowser/ContentBrowserAssetDataSource/Source/ContentBrowserAssetDataSource/Public/ContentBrowserAssetDataPayload.h` (Public)


#### class `FContentBrowserAssetFolderItemDataPayload`  
`class FContentBrowserAssetFolderItemDataPayload : public IContentBrowserItemDataPayload`  
_L16-36_
- inherits: `IContentBrowserItemDataPayload`
- L19 _public function_ `explicit FContentBrowserAssetFolderItemDataPayload(const FName InInternalPath) : InternalPath(InInternalPath)`
- L24 _public function_ `FName GetInternalPath() const`
- L29 _public prototype_ `const FString& GetFilename() const;`
- L32 _private member_ `FName InternalPath;`
- L34 _private member_ `mutable bool bHasCachedFilename = false;`
- L35 _private member_ `mutable FString CachedFilename;`

#### class `FContentBrowserAssetFileItemDataPayload`  
`class FContentBrowserAssetFileItemDataPayload : public IContentBrowserItemDataPayload`  
_L38-86_
- inherits: `IContentBrowserItemDataPayload`
- L41 _public prototype_ `explicit FContentBrowserAssetFileItemDataPayload(FAssetData&& InAssetData);`
- L42 _public prototype_ `explicit FContentBrowserAssetFileItemDataPayload(const FAssetData& InAssetData);`
- L44 _public function_ `const FAssetData& GetAssetData() const`
- L49 _public prototype_ `UPackage* GetPackage(const bool bTryRecacheIfNull = false) const;`
- L52 _public prototype_ `UPackage* LoadPackage(TSet<FName> LoadTags = {}) const;` — LoadTags(optional) allows passing specific tags to the linker when loading the asset package (@see ULevel::LoadAllExternalObjectsTag for an example usage)
- L54 _public prototype_ `UObject* GetAsset(const bool bTryRecacheIfNull = false) const;`
- L57 _public prototype_ `UObject* LoadAsset(TSet<FName> LoadTags = {}) const;` — LoadTags (optional) allows passing specific tags to the linker when loading the asset (@see ULevel::LoadAllExternalObjectsTag for an example usage)
- L59 _public prototype_ `TSharedPtr<IAssetTypeActions> GetAssetTypeActions() const;`
- L61 _public prototype_ `const UAssetDefinition* GetAssetDefinition() const;`
- L63 _public prototype_ `const FString& GetFilename() const;`
- L65 _public prototype_ `void UpdateThumbnail(FAssetThumbnail& InThumbnail) const;`
- L68 _private member_ `FAssetData AssetData;`
- L70 _private member_ `mutable bool bHasCachedPackagePtr = false;`
- L71 _private member_ `mutable TWeakObjectPtr<UPackage> CachedPackagePtr;`
- L73 _private member_ `mutable bool bHasCachedAssetPtr = false;`
- L74 _private member_ `mutable TWeakObjectPtr<UObject> CachedAssetPtr;`
- L76 _private member_ `mutable bool bHasCachedAssetTypeActionsPtr = false;`
- L77 _private member_ `mutable TWeakPtr<IAssetTypeActions> CachedAssetTypeActionsPtr;`
- L79 _private member_ `mutable bool bHasCachedAssetDefinitionPtr = false;`
- L80 _private member_ `mutable TWeakObjectPtr<const UAssetDefinition> CachedAssetDefinitionPtr;`
- L82 _private member_ `mutable bool bHasCachedFilename = false;`
- L83 _private member_ `mutable FString CachedFilename;`
- L85 _private prototype_ `void FlushCaches() const;`

#### class `FContentBrowserAssetFileItemDataPayload_Creation`  
`class FContentBrowserAssetFileItemDataPayload_Creation : public FContentBrowserAssetFileItemDataPayload, public FGCObject`  
_L88-120_
- inherits: `FContentBrowserAssetFileItemDataPayload,FGCObject`
- L91 _public prototype_ `FContentBrowserAssetFileItemDataPayload_Creation(FAssetData&& InAssetData, UClass* InAssetClass, UFactory* InFactory);`
- L94 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L99 _public function_ `virtual FString GetReferencerName() const override`
- L104 _public function_ `UClass* GetAssetClass() const`
- L109 _public function_ `UFactory* GetFactory() const`
- L116 _private member_ `TObjectPtr<UClass> AssetClass = nullptr;` — The class to use when creating the asset
- L119 _private member_ `TObjectPtr<UFactory> Factory = nullptr;` — The factory to use when creating the asset.

#### class `FContentBrowserAssetFileItemDataPayload_Duplication`  
`class FContentBrowserAssetFileItemDataPayload_Duplication : public FContentBrowserAssetFileItemDataPayload`  
_L122-135_
- inherits: `FContentBrowserAssetFileItemDataPayload`
- L125 _public prototype_ `FContentBrowserAssetFileItemDataPayload_Duplication(FAssetData&& InAssetData, TWeakObjectPtr<UObject> InSourceObject);`
- L127 _public function_ `UObject* GetSourceObject() const`
- L134 _private member_ `TWeakObjectPtr<UObject> SourceObject;` — The context to use when creating the asset. Used when initializing an asset with another related asset.

#### class `FContentBrowserUnsupportedAssetFileItemDataPayload`  
`class FContentBrowserUnsupportedAssetFileItemDataPayload : public IContentBrowserItemDataPayload`  
_L137-161_
- inherits: `IContentBrowserItemDataPayload`
- L141 _public prototype_ `explicit FContentBrowserUnsupportedAssetFileItemDataPayload(FAssetData&& InAssetData);` — Unsupported asset file but it does have an asset data
- L142 _public prototype_ `explicit FContentBrowserUnsupportedAssetFileItemDataPayload(const FAssetData& InAssetData);`
- L144 _public prototype_ `const FAssetData* GetAssetDataIfAvailable() const;`
- L146 _public prototype_ `const FString& GetFilename() const;`
- L148 _public prototype_ `UPackage* GetPackage() const;`
- L151 _private prototype_ `void FlushCaches() const;`
- L154 _private member_ `TUniquePtr<FAssetData> OptionalAssetData;`
- L156 _private member_ `mutable bool bHasCachedPackagePtr = false;`
- L157 _private member_ `mutable TWeakObjectPtr<UPackage> CachedPackagePtr;`
- L159 _private member_ `mutable bool bHasCachedFilename = false;`
- L160 _private member_ `mutable FString CachedFilename;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONTENTBROWSERASSETDATASOURCE_API`

### `Plugins/Editor/ContentBrowser/ContentBrowserAssetDataSource/Source/ContentBrowserAssetDataSource/Public/ContentBrowserAssetDataSource.h` (Public)


#### struct `FContentBrowserCompiledAssetDataFilter`  
`struct FContentBrowserCompiledAssetDataFilter`  
_L36-63_
- reflection: `USTRUCT()`
- L42 _public member_ `bool bRunFolderQueryOnDemand = false;` — Folder filtering
- L44 _public member_ `bool bRecursivePackagePathsToInclude = false;` — On-demand filtering (always recursive on PathToScanOnDemand)
- L45 _public member_ `bool bRecursivePackagePathsToExclude = false;`
- L46 _public member_ `FPathPermissionList PackagePathsToInclude;`
- L47 _public member_ `FPathPermissionList PackagePathsToExclude;`
- L48 _public member_ `FPathPermissionList PathPermissionList;`
- L49 _public member_ `TSet<FName> ExcludedPackagePaths;`
- L50 _public member_ `EContentBrowserItemAttributeFilter ItemAttributeFilter = EContentBrowserItemAttributeFilter::IncludeAll;`
- L51 _public member_ `EContentBrowserItemCategoryFilter ItemCategoryFilter = EContentBrowserItemCategoryFilter::IncludeAll;`
- L52 _public member_ `FString VirtualPathToScanOnDemand;`
- L54 _public member_ `TSet<FName> CachedSubPaths;` — Cached filtering
- L57 _public member_ `bool bFilterExcludesAllAssets = false;` — Asset filtering
- L58 _public member_ `FARCompiledFilter InclusiveFilter;`
- L59 _public member_ `FARCompiledFilter ExclusiveFilter;`
- L62 _public member_ `TArray<FAssetData> CustomSourceAssets;` — Legacy custom assets

#### struct `FContentBrowserCompiledUnsupportedAssetDataFilter`  
`struct FContentBrowserCompiledUnsupportedAssetDataFilter`  
_L66-82_
- reflection: `USTRUCT()`
- L72 _public member_ `FARCompiledFilter ConvertIfFailInclusiveFilter;` — Filter that are used to determine if an asset is supported
- L73 _public member_ `FARCompiledFilter ConvertIfFailExclusiveFilter;`
- L76 _public member_ `FARCompiledFilter ShowInclusiveFilter;` — Filter for where to show or not the unsupported assets
- L77 _public member_ `FARCompiledFilter ShowExclusiveFilter;`
- L80 _public member_ `FARCompiledFilter InclusiveFilter;` — Standard asset filter modified for the need of the unsupported assets
- L81 _public member_ `FARCompiledFilter ExclusiveFilter;`

#### class `UContentBrowserAssetDataSource`  
`class UContentBrowserAssetDataSource : public UContentBrowserDataSource`  
_L87-566_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContentBrowserDataSource`
- L92 _public prototype_ `void Initialize(const bool InAutoRegister = true);`
- L94 _public prototype_ `virtual void Shutdown() override;`
- L171 _public typedef_ `typedef TFunctionRef<void(const FCollectionRef&, ECollectionRecursionFlags::Flags, TFunctionRef<void(const FSoftObjectPath&)>)> FCollectionEnumerationFunc;`
- L172 _public typedef_ `typedef TFunctionRef<void(FName, TFunctionRef<bool(FName)>, bool)> FSubPathEnumerationFunc;`
- L173 _public typedef_ `typedef TFunctionRef<void(FARFilter&, FARCompiledFilter&)> FCompileARFilterFunc;`
- L174 _public typedef_ `typedef TFunctionRef<FContentBrowserItemData(FName)> FCreateFolderItemFunc;`
- L188 _public prototype_ `static bool PopulateAssetFilterInputParams(FAssetFilterInputParams& Params, UContentBrowserDataSource* DataSource, IAssetRegistry* InAssetRegistry, const FContentBrowserDataFilter& InFilter, FContentBrowserDataCompiledFilter& OutCompiledFilter, ICollectionManager* CollectionManager = nullptr, FAssetDataSourceFilterCache* InFilterCache = nullptr);` — Call in CompileFilter() to populate an FAssetFilterInputParams for use in CreatePathFilter and CreateAssetFilter. @param Params The FAssetFilterInputParams struct to populate with data @param DataSource The DataSource that CompileFilter() is being called on @param InAssetRegistry A pointer to the Asset Registry to save time having to find it @param InFilter The input filter supplied to CompileFilter() @param OutCompiledFilter The output filer supplied to CompileFilter() @param CollectionManager If set, this will be used to filter objects when a collection filter is requested. If not set, and a collection filter is requested, the function will return false. @return false if it's not possible to display folders or assets, otherwise true
- L201 _public prototype_ `static bool CreatePathFilter(FAssetFilterInputParams& Params, FName InPath, const FContentBrowserDataFilter& InFilter, FContentBrowserDataCompiledFilter& OutCompiledFilter, FSubPathEnumerationFunc SubPathEnumeration);` — Call in CompileFilter() after PopulateAssetFilterInputParams() to fill OutCompiledFilter with an FContentBrowserCompiledAssetDataFilter capable of filtering folders @param Params The params generated from PopulateAssetFilterInputParams() @param InPath The input path supplied to CompileFilter() @param InFilter The input filter supplied to CompileFilter() @param OutCompiledFilter The output filer supplied to CompileFilter() @param SubPathEnumeration A function that calls its input function on all subpaths of the given input path, optionally recursive @return false if it's not possible to display any folders, otherwise true
- L214 _public prototype_ `static bool CreateAssetFilter(FAssetFilterInputParams& Params, FName InPath, const FContentBrowserDataFilter& InFilter, FContentBrowserDataCompiledFilter& OutCompiledFilter, FSubPathEnumerationFunc* GetSubPackagePathsFunc = nullptr, FCollectionEnumerationFunc* GetCollectionObjectPathsFunc = nullptr);` — Call in CompileFilter() after CreatePathFilter() to fill OutCompiledFilter with an FContentBrowserCompiledAssetDataFilter capable of filtering assets @param Params The params generated from PopulateAssetFilterInputParams() @param InPath The input path supplied to CompileFilter() @param InFilter The input filter supplied to CompileFilter() @param OutCompiledFilter The output filer supplied to CompileFilter() @param FGetSubPathsFunc A optional function to override how the package paths are expended. @return false if it's not possible to display any assets, otherwise true
- L217 _public prototype_ `static bool CreateAssetFilter(FAssetFilterInputParams& Params, FName InPath, const FContentBrowserDataFilter& InFilter, FContentBrowserDataCompiledFilter& OutCompiledFilter, FCompileARFilterFunc CreateCompiledFilter);` — `UE_DEPRECATED(5.3, "Use the override without the function to customize the compilation the ARFilter or duplicate this function logic. This function will no longer be supported and will be removed to allow future performence improvements")`
- L231 _public prototype_ `static void EnumerateFoldersMatchingFilter(UContentBrowserDataSource* DataSource, const FContentBrowserCompiledAssetDataFilter* AssetDataFilter, const TGetOrEnumerateSink<FContentBrowserItemData>& InSink, FSubPathEnumerationFunc SubPathEnumeration, FCreateFolderItemFunc CreateFolderItem);` — Call in EnumerateItemsMatchingFilter() to generate a list of folders that match the compiled filter. It is the caller's responsibility to verify EContentBrowserItemTypeFilter::IncludeFolders is set before enumerating. @param DataSource The DataSource that EnumerateItemsMatchingFilter is being called on @param AssetDataFilter The filter to use when deciding whether a path is a valid folder @param InCallback The callback function supplied by EnumerateItemsMatchingFilter() @param SubPathEnumeration A function that calls its input function on all subpaths of the given input path, optionally recursive @param CreateFolderItem A function that generates an FContentBrowserItemData folder for the given input path @return
- L243 _public prototype_ `static bool DoesItemPassFolderFilter(UContentBrowserDataSource* DataSource, const FContentBrowserItemData& InItem, const FContentBrowserCompiledAssetDataFilter& Filter);` — Call in DoesItemPassFilter() to check if a folder passes the compiled asset data filter. It is the caller's responsibility to verify EContentBrowserItemTypeFilter::IncludeFolders is set before enumerating. @param DataSource The DataSource that DoesItemPassFilter() is being called on @param InItem The folder item to test against the filter supplied by DoesItemPassFilter() @param Filter The compiled filter to test with supplied by DoesItemPassFilter() @return true if the folder passes the filter
- L245 _public prototype_ `virtual void CompileFilter(const FName InPath, const FContentBrowserDataFilter& InFilter, FContentBrowserDataCompiledFilter& OutCompiledFilter) override;`
- L247 _public prototype_ `virtual void EnumerateItemsMatchingFilter(const FContentBrowserDataCompiledFilter& InFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;`
- L248 _public prototype_ `virtual void EnumerateItemsMatchingFilter(const FContentBrowserDataCompiledFilter& InFilter, const TGetOrEnumerateSink<FContentBrowserItemData>& InSink) override;`
- L250 _public prototype_ `virtual void EnumerateItemsAtPath(const FName InPath, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;`
- L252 _public prototype_ `virtual bool EnumerateItemsAtPaths(const TArrayView<FContentBrowserItemPath> InPaths, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;`
- L254 _public prototype_ `virtual void EnumerateItemsAtUserProvidedPath(const FStringView InPath, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;`
- L256 _public prototype_ `virtual bool IsDiscoveringItems(FText* OutStatus = nullptr) override;`
- L258 _public prototype_ `virtual bool PrioritizeSearchPath(const FName InPath) override;`
- L260 _public prototype_ `virtual bool IsFolderVisible(const FName InPath, const EContentBrowserIsFolderVisibleFlags InFlags, const FContentBrowserFolderContentsFilter& InContentsFilter) override;`
- L262 _public prototype_ `virtual bool CanCreateFolder(const FName InPath, FText* OutErrorMsg) override;`
- L264 _public prototype_ `virtual bool CreateFolder(const FName InPath, const TSharedPtr<IContentBrowserHideFolderIfEmptyFilter>& HideFolderIfEmptyFilter, FContentBrowserItemDataTemporaryContext& OutPendingItem) override;`
- L266 _public prototype_ `virtual bool DoesItemPassFilter(const FContentBrowserItemData& InItem, const FContentBrowserDataCompiledFilter& InFilter) override;`
- L268 _public prototype_ `virtual bool ConvertItemForFilter(FContentBrowserItemData& Item, const FContentBrowserDataCompiledFilter& InFilter) override;`
- L270 _public prototype_ `virtual bool GetItemAttribute(const FContentBrowserItemData& InItem, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue) override;`
- L272 _public prototype_ `virtual bool GetItemAttributes(const FContentBrowserItemData& InItem, const bool InIncludeMetaData, FContentBrowserItemDataAttributeValues& OutAttributeValues) override;`
- L274 _public prototype_ `virtual bool GetItemPhysicalPath(const FContentBrowserItemData& InItem, FString& OutDiskPath) override;`
- L276 _public prototype_ `virtual bool GetItemAssetAccessSpecifier(const FContentBrowserItemData& InItem, EAssetAccessSpecifier& OutAssetAccessSpecifier) override;`
- L278 _public prototype_ `virtual bool CanModifyItemAssetAccessSpecifier(const FContentBrowserItemData& InItem) override;`
- L280 _public prototype_ `virtual bool IsItemDirty(const FContentBrowserItemData& InItem) override;`
- L282 _public prototype_ `virtual bool CanEditItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg) override;`
- L284 _public prototype_ `virtual bool EditItem(const FContentBrowserItemData& InItem) override;`
- L286 _public prototype_ `virtual bool BulkEditItems(TArrayView<const FContentBrowserItemData> InItems) override;`
- L288 _public prototype_ `virtual bool CanViewItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg) override;`
- L290 _public prototype_ `virtual bool ViewItem(const FContentBrowserItemData& InItem) override;`
- L292 _public prototype_ `virtual bool BulkViewItems(TArrayView<const FContentBrowserItemData> InItems) override;`
- L294 _public prototype_ `virtual bool CanPreviewItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg) override;`
- L296 _public prototype_ `virtual bool PreviewItem(const FContentBrowserItemData& InItem) override;`
- L298 _public prototype_ `virtual bool BulkPreviewItems(TArrayView<const FContentBrowserItemData> InItems) override;`
- L300 _public prototype_ `virtual bool CanDuplicateItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg) override;`
- L302 _public prototype_ `virtual bool DuplicateItem(const FContentBrowserItemData& InItem, FContentBrowserItemDataTemporaryContext& OutPendingItem) override;`
- L304 _public prototype_ `virtual bool BulkDuplicateItems(TArrayView<const FContentBrowserItemData> InItems, TArray<FContentBrowserItemData>& OutNewItems) override;`
- L306 _public prototype_ `virtual bool CanSaveItem(const FContentBrowserItemData& InItem, const EContentBrowserItemSaveFlags InSaveFlags, FText* OutErrorMsg) override;`
- L308 _public prototype_ `virtual bool SaveItem(const FContentBrowserItemData& InItem, const EContentBrowserItemSaveFlags InSaveFlags) override;`
- L310 _public prototype_ `virtual bool BulkSaveItems(TArrayView<const FContentBrowserItemData> InItems, const EContentBrowserItemSaveFlags InSaveFlags) override;`
- L312 _public prototype_ `virtual bool CanDeleteItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg) override;`
- L314 _public prototype_ `virtual bool DeleteItem(const FContentBrowserItemData& InItem) override;`
- L316 _public prototype_ `virtual bool BulkDeleteItems(TArrayView<const FContentBrowserItemData> InItems) override;`
- L318 _public prototype_ `virtual bool CanPrivatizeItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg);`
- L320 _public prototype_ `virtual bool PrivatizeItem(const FContentBrowserItemData& InItem, const EAssetAccessSpecifier InAssetAccessSpecifier = EAssetAccessSpecifier::Private) override;`
- L322 _public prototype_ `virtual bool BulkPrivatizeItems(TArrayView<const FContentBrowserItemData> InItems, const EAssetAccessSpecifier InAssetAccessSpecifier = EAssetAccessSpecifier::Private) override;`
- L324 _public prototype_ `virtual bool CanRenameItem(const FContentBrowserItemData& InItem, const FString* InNewName, const IContentBrowserHideFolderIfEmptyFilter* HideFolderIfEmptyFilter, FText* OutErrorMsg) override;`
- L326 _public prototype_ `virtual bool RenameItem(const FContentBrowserItemData& InItem, const FString& InNewName, FContentBrowserItemData& OutNewItem) override;`
- L328 _public prototype_ `virtual bool CanCopyItem(const FContentBrowserItemData& InItem, const FName InDestPath, FText* OutErrorMsg) override;`
- L330 _public prototype_ `virtual bool CopyItem(const FContentBrowserItemData& InItem, const FName InDestPath) override;`
- L332 _public prototype_ `virtual bool BulkCopyItems(TArrayView<const FContentBrowserItemData> InItems, const FName InDestPath) override;`
- L334 _public prototype_ `virtual bool CanMoveItem(const FContentBrowserItemData& InItem, const FName InDestPath, FText* OutErrorMsg) override;`
- L336 _public prototype_ `virtual bool MoveItem(const FContentBrowserItemData& InItem, const FName InDestPath) override;`
- L338 _public prototype_ `virtual bool BulkMoveItems(TArrayView<const FContentBrowserItemData> InItems, const FName InDestPath) override;`
- L340 _public prototype_ `virtual bool AppendItemReference(const FContentBrowserItemData& InItem, FString& InOutStr) override;`
- L342 _public prototype_ `virtual bool AppendItemObjectPath(const FContentBrowserItemData& InItem, FString& InOutStr) override;`
- L344 _public prototype_ `virtual bool AppendItemPackageName(const FContentBrowserItemData& InItem, FString& InOutStr) override;`
- L346 _public prototype_ `virtual bool UpdateThumbnail(const FContentBrowserItemData& InItem, FAssetThumbnail& InThumbnail) override;`
- L348 _public prototype_ `virtual bool HandleDragEnterItem(const FContentBrowserItemData& InItem, const FDragDropEvent& InDragDropEvent) override;`
- L350 _public prototype_ `virtual bool HandleDragOverItem(const FContentBrowserItemData& InItem, const FDragDropEvent& InDragDropEvent) override;`
- L352 _public prototype_ `virtual bool HandleDragLeaveItem(const FContentBrowserItemData& InItem, const FDragDropEvent& InDragDropEvent) override;`
- L354 _public prototype_ `virtual bool HandleDragDropOnItem(const FContentBrowserItemData& InItem, const FDragDropEvent& InDragDropEvent) override;`
- L356 _public prototype_ `virtual bool TryGetCollectionId(const FContentBrowserItemData& InItem, FSoftObjectPath& OutCollectionId) override;`
- L358 _public prototype_ `virtual bool Legacy_TryGetPackagePath(const FContentBrowserItemData& InItem, FName& OutPackagePath) override;`
- L360 _public prototype_ `virtual bool Legacy_TryGetAssetData(const FContentBrowserItemData& InItem, FAssetData& OutAssetData) override;`
- L362 _public prototype_ `virtual bool Legacy_TryConvertPackagePathToVirtualPath(const FName InPackagePath, FName& OutPath) override;`
- L364 _public prototype_ `virtual bool Legacy_TryConvertAssetDataToVirtualPath(const FAssetData& InAssetData, const bool InUseFolderPaths, FName& OutPath) override;`
- L366 _public prototype_ `static bool PathPassesCompiledDataFilter(const FContentBrowserCompiledAssetDataFilter& InFilter, const FName InPath);`
- L368 _public prototype_ `virtual void RemoveUnusedCachedFilterData(const FContentBrowserDataFilterCacheIDOwner& IDOwner, TArrayView<const FName> InVirtualPathsInUse, const FContentBrowserDataFilter& DataFilter) override;`
- L370 _public prototype_ `virtual void ClearCachedFilterData(const FContentBrowserDataFilterCacheIDOwner& IDOwner) override;`
- L373 _protected prototype_ `virtual void BuildRootPathVirtualTree() override;`
- L376 _private prototype_ `bool IsKnownContentPath(const FName InPackagePath) const;`
- L378 _private prototype_ `static bool GetObjectPathsForCollections(TArrayView<const FCollectionRef> InCollections, const bool bIncludeChildCollections, FCollectionEnumerationFunc* GetCollectionObjectPathsFunc, TArray<FSoftObjectPath>& OutObjectPaths);`
- L380 _private prototype_ `FContentBrowserItemData CreateAssetFolderItem(const FName InInternalFolderPath);`
- L382 _private prototype_ `FContentBrowserItemData CreateAssetFileItem(const FAssetData& InAssetData);`
- L384 _private prototype_ `FContentBrowserItemData CreateUnsupportedAssetFileItem(const FAssetData& InAssetData);`
- L386 _private prototype_ `TSharedPtr<const FContentBrowserAssetFolderItemDataPayload> GetAssetFolderItemPayload(const FContentBrowserItemData& InItem) const;`
- L388 _private prototype_ `TSharedPtr<const FContentBrowserAssetFileItemDataPayload> GetAssetFileItemPayload(const FContentBrowserItemData& InItem) const;`
- L390 _private prototype_ `TSharedPtr<const FContentBrowserUnsupportedAssetFileItemDataPayload> GetUnsupportedAssetFileItemPayload(const FContentBrowserItemData& InItem) const;`
- L392 _private prototype_ `bool CanHandleDragDropEvent(const FContentBrowserItemData& InItem, const FDragDropEvent& InDragDropEvent) const;`
- L394 _private prototype_ `void OnAssetRegistryFileLoadProgress(const IAssetRegistry::FFileLoadProgressUpdateData& InProgressUpdateData);`
- L396 _private prototype_ `void OnAssetsAdded(TConstArrayView<FAssetData> InAssets);`
- L398 _private prototype_ `void OnAssetRemoved(const FAssetData& InAssetData);`
- L400 _private prototype_ `void OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath);`
- L402 _private prototype_ `void OnAssetUpdated(const FAssetData& InAssetData);`
- L404 _private prototype_ `void OnAssetUpdatedOnDisk(const FAssetData& InAssetData);`
- L406 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);`
- L408 _private prototype_ `void OnObjectPreSave(UObject* InObject, class FObjectPreSaveContext InObjectPreSaveContext);`
- L410 _private prototype_ `void OnPathsAdded(TConstArrayView<FStringView> Paths);`
- L412 _private prototype_ `void OnPathsRemoved(TConstArrayView<FStringView> Paths);`
- L414 _private prototype_ `void OnPathPopulated(const FAssetData& InAssetData);`
- L416 _private prototype_ `void OnPathPopulated(const FStringView InPath, const EContentBrowserFolderAttributes InAttributesToSet);`
- L418 _private prototype_ `void OnAlwaysShowPath(const FString& InPath);`
- L420 _private prototype_ `void OnContentPathMounted(const FString& InAssetPath, const FString& InFileSystemPath);`
- L422 _private prototype_ `void OnContentPathDismounted(const FString& InAssetPath, const FString& InFileSystemPath);`
- L424 _private prototype_ `EContentBrowserFolderAttributes GetAssetFolderAttributes(const FName InPath) const;`
- L426 _private prototype_ `bool SetAssetFolderAttributes(const FName InPath, const EContentBrowserFolderAttributes InAttributesToSet);`
- L428 _private prototype_ `bool ClearAssetFolderAttributes(const FName InPath, const EContentBrowserFolderAttributes InAttributesToClear);`
- L430 _private prototype_ `bool HideFolderIfEmpty(const IContentBrowserHideFolderIfEmptyFilter& HideFolderIfEmptyFilter, FName Path, FStringView PathString) const;`
- L432 _private prototype_ `void PopulateAddNewContextMenu(UToolMenu* InMenu);`
- L434 _private prototype_ `void PopulateContentBrowserToolBar(UToolMenu* InMenu);`
- L436 _private prototype_ `void PopulateAssetFolderContextMenu(UToolMenu* InMenu);`
- L438 _private prototype_ `void PopulateAssetFileContextMenu(UToolMenu* InMenu);`
- L440 _private prototype_ `void PopulateDragDropContextMenu(UToolMenu* InMenu);`
- L442 _private prototype_ `void OnAdvancedCopyRequested(const TArray<FName>& InAdvancedCopyInputs, const FString& InDestinationPath);`
- L444 _private prototype_ `void OnImportAsset(const FName InPath);`
- L446 _private prototype_ `void OnNewAssetRequested(const FName InPath, TWeakObjectPtr<UClass> InFactoryClass, UContentBrowserDataMenuContext_AddNewMenu::FOnBeginItemCreation InOnBeginItemCreation);`
- L448 _private prototype_ `void OnBeginCreateAsset(const FName InDefaultAssetName, const FName InPackagePath, UClass* InAssetClass, UFactory* InFactory, UContentBrowserDataMenuContext_AddNewMenu::FOnBeginItemCreation InOnBeginItemCreation);`
- L450 _private prototype_ `bool OnValidateItemName(const FContentBrowserItemData& InItem, const FString& InProposedName, FText* OutErrorMsg);`
- L452 _private prototype_ `FReply OnImportClicked(const UContentBrowserToolbarMenuContext* ContextObject);`
- L454 _private prototype_ `bool IsImportEnabled(const UContentBrowserToolbarMenuContext* ContextObject) const;`
- L456 _private prototype_ `FContentBrowserItemData OnFinalizeCreateFolder(const FContentBrowserItemData& InItemData, const FString& InProposedName, FText* OutErrorMsg);`
- L458 _private prototype_ `FContentBrowserItemData OnFinalizeCreateAsset(const FContentBrowserItemData& InItemData, const FString& InProposedName, FText* OutErrorMsg);`
- L460 _private prototype_ `FContentBrowserItemData OnFinalizeDuplicateAsset(const FContentBrowserItemData& InItemData, const FString& InProposedName, FText* OutErrorMsg);`
- L462 _private prototype_ `void AddRootContentPathToStateMachine(const FString& InAssetPath);`
- L464 _private prototype_ `void RemoveRootContentPathFromStateMachine(const FString& InAssetPath);`
- L466 _private prototype_ `void OnExtendContentBrowserCommands(TSharedRef<FUICommandList> InCommandList, FOnContentBrowserGetSelection InGetSelectionDelegate);`
- L468 _private member_ `IAssetRegistry* AssetRegistry = nullptr;`
- L470 _private member_ `IAssetTools* AssetTools = nullptr;`
- L472 _private member_ `FContentBrowserModule* ContentBrowserModule = nullptr;`
- L474 _private member_ `ICollectionManager* CollectionManager;`
- L476 _private member_ `TSharedPtr<FAssetFolderContextMenu> AssetFolderContextMenu;`
- L478 _private member_ `TSharedPtr<FAssetFileContextMenu> AssetFileContextMenu;`
- L480 _private member_ `FText DiscoveryStatusText;`
- L486 _private member_ `TArray<FString> RootContentPaths;` — The array of known root content paths that can hold assets. @note These paths include a trailing slash.
- L547 _private member_ `FCharacterNode RootContentPathsTrie;` — Tree of character nodes all in lower case. Used to speed up queries against the RootContentPaths Array.
- L552 _private member_ `TMap<FName, EContentBrowserFolderAttributes> AssetFolderToAttributes;` — Map of folders that have attributes set.
- L557 _private member_ `TMap<FName, EContentBrowserFolderAttributes> RecentlyPopulatedAssetFolders;` — A cache of folders that have been populated since the last time any new asset folders were added.
- L559 _private prototype_ `DECLARE_MULTICAST_DELEGATE_SixParams(FOnAssetDataSourcePathAdded, FName, FStringView, uint32, FName, uint32, int32);`
- L560 _private member_ `static FOnAssetDataSourcePathAdded OnAssetPathAddedDelegate;`
- L562 _private prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAssetDataSourcePathRemoved, FName, uint32);`
- L563 _private member_ `static FOnAssetDataSourcePathRemoved OnAssetPathRemovedDelegate;`
- L565 _private member_ `FAssetDataSourceFilterCache FilterCache;`

#### struct `UContentBrowserAssetDataSource::FAssetDataSourceFilterCache`  
`struct FAssetDataSourceFilterCache`  
_L99-134_
- desc: A struct used to cache some data to accelerate the compilation of the filters for the asset data source
- L102 _public prototype_ `FAssetDataSourceFilterCache();`
- L103 _public prototype_ `~FAssetDataSourceFilterCache();`
- L105 _public prototype_ `FAssetDataSourceFilterCache(const FAssetDataSourceFilterCache&) = delete;`
- L106 _public prototype_ `FAssetDataSourceFilterCache(FAssetDataSourceFilterCache&&) = delete;`
- L108 _public prototype_ `FAssetDataSourceFilterCache& operator=(const FAssetDataSourceFilterCache&) = delete;`
- L109 _public prototype_ `FAssetDataSourceFilterCache& operator=(FAssetDataSourceFilterCache&&) = delete;`
- L111 _public prototype_ `void RemoveUnusedCachedData(const FContentBrowserDataFilterCacheIDOwner& IDOwner, TArrayView<const FName> InVirtualPathsInUse, const FContentBrowserDataFilter& DataFilter);`
- L112 _public prototype_ `void ClearCachedData(const FContentBrowserDataFilterCacheIDOwner& IDOwner);`
- L113 _public prototype_ `void Reset();`
- L118 _private prototype_ `bool GetCachedCompiledInternalPaths(const FContentBrowserDataFilter& InFilter, FName InVirtualPath, TSet<FName>& OutCompiledInternalPath) const;`
- L119 _private prototype_ `void CacheCompiledInternalPaths(const FContentBrowserDataFilter& InFilter, FName InVirtualPath, const TSet<FName>& CompiledInternalPaths);`
- L121 _private prototype_ `void OnPathAdded(FName Path, FStringView PathString, uint32 PathHash, FName ParentPath, uint32 ParentPathHash, int32 PathDepth);`
- L122 _private prototype_ `void OnPathRemoved(FName Path, uint32 PathHash);`
- L133 _private member_ `TMap<FContentBrowserDataFilterCacheID, FCachedDataPerID> CachedCompiledInternalPaths;` — A cache for the recursive internal paths (Possible improvement: Rework the cache into a shared cache across multiple IDs for the simple filters and a not shared cache for the more complex filters)

#### struct `UContentBrowserAssetDataSource::FAssetDataSourceFilterCache::FCachedDataPerID`  
`struct FCachedDataPerID`  
_L124-128_
- L126 _public member_ `TMap<FName, TSet<FName>> InternalPaths;`
- L127 _public member_ `EContentBrowserItemAttributeFilter ItemAttributeFilter = EContentBrowserItemAttributeFilter::IncludeAll;`

#### struct `UContentBrowserAssetDataSource::FAssetFilterInputParams`  
`struct FAssetFilterInputParams`  
_L139-169_
- desc: All of the data necessary to generate a compiled filter for folders and assets
- L141 _public member_ `TSet<FName> InternalPaths;`
- L143 _public member_ `UContentBrowserDataSource* DataSource = nullptr;`
- L145 _public member_ `ICollectionManager* CollectionManager = nullptr;` — `UE_DEPRECATED(5.6, "CollectionManager is no longer used.")`
- L146 _public member_ `FAssetDataSourceFilterCache* AssetFilterCache = nullptr;`
- L147 _public member_ `IAssetRegistry* AssetRegistry = nullptr;`
- L149 _public member_ `const FContentBrowserDataObjectFilter* ObjectFilter = nullptr;`
- L150 _public member_ `const FContentBrowserDataPackageFilter* PackageFilter = nullptr;`
- L151 _public member_ `const FContentBrowserDataClassFilter* ClassFilter = nullptr;`
- L152 _public member_ `const FContentBrowserDataCollectionFilter* CollectionFilter = nullptr;`
- L155 _public member_ `const FContentBrowserDataUnsupportedClassFilter* UnsupportedClassFilter = nullptr;` — Filter that convert showed items as unsupported items
- L157 _public member_ `const FPathPermissionList* PathPermissionList = nullptr;`
- L158 _public member_ `const FPathPermissionList* ClassPermissionList = nullptr;`
- L160 _public member_ `FContentBrowserDataFilterList* FilterList = nullptr;`
- L161 _public member_ `FContentBrowserCompiledAssetDataFilter* AssetDataFilter = nullptr;`
- L162 _public member_ `FContentBrowserCompiledUnsupportedAssetDataFilter* ConvertToUnsupportedAssetDataFilter = nullptr;`
- L165 _public member_ `bool bIncludeFolders = false;`
- L166 _public member_ `bool bIncludeFiles = false;`
- L167 _public member_ `bool bIncludeAssets = false;`
- L168 _public member_ `bool bIncludeRedirectors = false;`

#### struct `UContentBrowserAssetDataSource::FCharacterNodePtr`  
`struct FCharacterNodePtr`  
_L490-536_
- L492 _public function_ `FCharacterNodePtr() : Node(MakeUnique<FCharacterNode>())`
- L497 _public prototype_ `FCharacterNodePtr(FCharacterNodePtr&&) = default;`
- L498 _public prototype_ `FCharacterNodePtr& operator=(FCharacterNodePtr&&) = default;`
- L500 _public prototype_ `FCharacterNodePtr(const FCharacterNodePtr&) = delete;`
- L501 _public prototype_ `FCharacterNodePtr& operator=(const FCharacterNodePtr&) = delete;`
- L503 _public function_ `const FCharacterNode& operator*() const`
- L508 _public function_ `const FCharacterNode* operator->() const`
- L513 _public function_ `FCharacterNode& operator*()`
- L518 _public function_ `FCharacterNode* operator->()`
- L523 _public function_ `const FCharacterNode* Get() const`
- L528 _public function_ `FCharacterNode* Get()`
- L535 _private member_ `TUniquePtr<FCharacterNode> Node;`

#### struct `UContentBrowserAssetDataSource::FCharacterNode`  
`struct FCharacterNode`  
_L538-544_
- L541 _public member_ `TMap<TCHAR, TPair<FCharacterNodePtr, int32>> NextNodes;` — The next characters in the tree and the number of paths beginning with the prefix including that character for use in removing paths.
- L543 _public member_ `bool bIsEndOfAMountPoint = false;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API CONTENTBROWSERASSETDATASOURCE_API`
- L559 _delegate_ `DECLARE_MULTICAST_DELEGATE_SixParams(FOnAssetDataSourcePathAdded, FName, FStringView, uint32, FName, uint32, int32);`
- L562 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAssetDataSourcePathRemoved, FName, uint32);`

### `Plugins/Editor/ContentBrowser/ContentBrowserAssetDataSource/Source/ContentBrowserAssetDataSource/Public/ContentBrowserAssetDataSourceUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CONTENTBROWSERASSETDATASOURCE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace ContentBrowserAssetDataSource` (scope `UE::Editor`)
- L12 _prototype_ `int32 CaptureThumbnail(const TArray<FAssetData>& InAssets);` (scope `UE::Editor::ContentBrowserAssetDataSource`)
- L13 _prototype_ `bool CanCaptureThumbnail(const TArray<FAssetData>& InAssets);` (scope `UE::Editor::ContentBrowserAssetDataSource`)

### `Plugins/Editor/ContentBrowser/ContentBrowserAssetDataSource/Source/ContentBrowserAssetDataSource/Public/NewAssetContextMenu.h` (Public)


#### class `FNewAssetContextMenu`  
`class FNewAssetContextMenu`  
_L13-37_
- L16 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnImportAssetRequested, const FName );`
- L17 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnNewAssetRequested, const FName , TWeakObjectPtr<UClass> );`
- L20 _public prototype_ `static void MakeContextMenu( UToolMenu* Menu, const TArray<FName>& InSelectedAssetPaths, const FOnImportAssetRequested& InOnImportAssetRequested, const FOnNewAssetRequested& InOnNewAssetRequested );` — Makes the context menu widget
- L29 _private prototype_ `static void CreateNewAssetMenuCategory(UToolMenu* Menu, FName SectionName, EAssetTypeCategories::Type AssetTypeCategory, FName InPath, FOnNewAssetRequested InOnNewAssetRequested, FCanExecuteAction InCanExecuteAction);` — Handle creating a new asset from an asset category
- L30 _private prototype_ `static void CreateNewAssetMenus(UToolMenu* Menu, FName SectionName, TSharedPtr<FCategorySubMenuItem> SubMenuData, FName InPath, FOnNewAssetRequested InOnNewAssetRequested, FCanExecuteAction InCanExecuteAction);`
- L33 _private prototype_ `static void ExecuteImportAsset(FOnImportAssetRequested InOnImportAssetRequested, FName InPath);` — Handle when the "Import" button is clicked
- L36 _private prototype_ `static void ExecuteNewAsset(FOnNewAssetRequested InOnNewAssetRequested, FName InPath, TWeakObjectPtr<UClass> FactoryClass);` — Create a new asset using the specified factory at the specified path

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CONTENTBROWSERASSETDATASOURCE_API`
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnImportAssetRequested, const FName );`
- L17 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnNewAssetRequested, const FName , TWeakObjectPtr<UClass> );`
