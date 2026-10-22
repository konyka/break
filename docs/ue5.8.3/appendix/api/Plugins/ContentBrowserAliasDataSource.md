# Plugins / ContentBrowserAliasDataSource

- module root: `Plugins/Editor/ContentBrowser/ContentBrowserAliasDataSource/Source/ContentBrowserAliasDataSource`
- headers: 3; symbols: 118
- symbol kinds: class=3, delegate=1, function=9, macro=1, member=23, prototype=78, struct=2, typedef=1
- PrivateDependencyModuleNames: AssetTools, Engine
- PublicDependencyModuleNames: AssetRegistry, ContentBrowserAssetDataSource, ContentBrowserData, Core, CoreUObject

### `Plugins/Editor/ContentBrowser/ContentBrowserAliasDataSource/Source/ContentBrowserAliasDataSource/Public/ContentBrowserAliasDataSource.h` (Public)


#### class `FContentBrowserAliasItemDataPayload`  
`class FContentBrowserAliasItemDataPayload : public FContentBrowserAssetFileItemDataPayload`  
_L29-38_
- inherits: `FContentBrowserAssetFileItemDataPayload`
- L32 _public function_ `FContentBrowserAliasItemDataPayload(const FAssetData& InAssetData, const FContentBrowserUniqueAlias& InAlias) : FContentBrowserAssetFileItemDataPayload(InAssetData), Alias(InAlias)`
- L37 _public member_ `FContentBrowserUniqueAlias Alias;`

#### class `UContentBrowserAliasDataSource`  
`class UContentBrowserAliasDataSource : public UContentBrowserDataSource`  
_L49-265_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContentBrowserDataSource`
- desc: A companion to the ContentBrowserAssetDataSource which can display assets in folders other than their actual folder. Aliases mimic their source asset as closely as possible, including editing, saving, thumbnails, and more. Some behavior is restricted such as moving or deleting an alias item. Aliases can either be created automatically by tagging the asset with the value defined by AliasTagName and giving it a comma-separated list of aliases, or manually managed by calling AddAlias and RemoveAlias. ReconcileAliasesForAsset is provided as a helper function to automatically update new/removed aliases for an existing asset.
- L55 _public member_ `static FName AliasTagName;` — The metadata tag to set for the AliasDataSource to automatically create aliases for an asset
- L58 _public prototype_ `void Initialize(const bool InAutoRegister = true);`
- L59 _public prototype_ `virtual void Shutdown() override;`
- L61 _public prototype_ `virtual void CompileFilter(const FName InPath, const FContentBrowserDataFilter& InFilter, FContentBrowserDataCompiledFilter& OutCompiledFilter) override;`
- L62 _public prototype_ `virtual void EnumerateItemsMatchingFilter(const FContentBrowserDataCompiledFilter& InFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;`
- L63 _public prototype_ `virtual void EnumerateItemsAtPath(const FName InPath, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;`
- L64 _public prototype_ `virtual void EnumerateItemsAtUserProvidedPath(const FStringView InPath, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;`
- L66 _public prototype_ `virtual bool IsFolderVisible(const FName Path, const EContentBrowserIsFolderVisibleFlags Flags, const FContentBrowserFolderContentsFilter& ContentsFilter) override;`
- L68 _public prototype_ `virtual bool DoesItemPassFilter(const FContentBrowserItemData& InItem, const FContentBrowserDataCompiledFilter& InFilter) override;`
- L71 _public prototype_ `virtual TArray<FContentBrowserItemPath> GetAliasesForPath(const FSoftObjectPath& InInternalPath) const override;`
- L72 _public prototype_ `virtual bool GetItemAliasedPath(const FContentBrowserItemData& InItemData, FSoftObjectPath& OutObjectPath) const override;`
- L74 _public prototype_ `bool HasAliasesForPath(const FSoftObjectPath& InInternalPath) const;`
- L76 _public prototype_ `virtual bool GetItemAttribute(const FContentBrowserItemData& InItem, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue) override;`
- L77 _public prototype_ `virtual bool GetItemAttributes(const FContentBrowserItemData& InItem, const bool InIncludeMetaData, FContentBrowserItemDataAttributeValues& OutAttributeValues) override;`
- L78 _public prototype_ `virtual bool GetItemPhysicalPath(const FContentBrowserItemData& InItem, FString& OutDiskPath) override;`
- L79 _public prototype_ `virtual bool IsItemDirty(const FContentBrowserItemData& InItem) override;`
- L81 _public prototype_ `virtual bool CanEditItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg) override;`
- L82 _public prototype_ `virtual bool EditItem(const FContentBrowserItemData& InItem) override;`
- L83 _public prototype_ `virtual bool BulkEditItems(TArrayView<const FContentBrowserItemData> InItems) override;`
- L85 _public prototype_ `virtual bool CanViewItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg) override;`
- L86 _public prototype_ `virtual bool ViewItem(const FContentBrowserItemData& InItem) override;`
- L87 _public prototype_ `virtual bool BulkViewItems(TArrayView<const FContentBrowserItemData> InItems) override;`
- L89 _public prototype_ `virtual bool CanPreviewItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg) override;`
- L90 _public prototype_ `virtual bool PreviewItem(const FContentBrowserItemData& InItem) override;`
- L91 _public prototype_ `virtual bool BulkPreviewItems(TArrayView<const FContentBrowserItemData> InItems) override;`
- L93 _public prototype_ `virtual bool CanSaveItem(const FContentBrowserItemData& InItem, const EContentBrowserItemSaveFlags InSaveFlags, FText* OutErrorMsg) override;`
- L94 _public prototype_ `virtual bool SaveItem(const FContentBrowserItemData& InItem, const EContentBrowserItemSaveFlags InSaveFlags) override;`
- L95 _public prototype_ `virtual bool BulkSaveItems(TArrayView<const FContentBrowserItemData> InItems, const EContentBrowserItemSaveFlags InSaveFlags) override;`
- L97 _public prototype_ `virtual bool CanPrivatizeItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg) override;`
- L98 _public prototype_ `virtual bool PrivatizeItem(const FContentBrowserItemData& InItem, const EAssetAccessSpecifier InAssetAccessSpecifier = EAssetAccessSpecifier::Private) override;`
- L99 _public prototype_ `virtual bool BulkPrivatizeItems(TArrayView<const FContentBrowserItemData> InItems, const EAssetAccessSpecifier InAssetAccessSpecifier = EAssetAccessSpecifier::Private) override;`
- L101 _public prototype_ `virtual bool AppendItemReference(const FContentBrowserItemData& InItem, FString& InOutStr) override;`
- L102 _public prototype_ `virtual bool AppendItemObjectPath(const FContentBrowserItemData& InItem, FString& InOutStr) override;`
- L103 _public prototype_ `virtual bool AppendItemPackageName(const FContentBrowserItemData& InItem, FString& InOutStr) override;`
- L104 _public prototype_ `virtual bool UpdateThumbnail(const FContentBrowserItemData& InItem, FAssetThumbnail& InThumbnail) override;`
- L106 _public prototype_ `virtual bool TryGetCollectionId(const FContentBrowserItemData& InItem, FSoftObjectPath& OutCollectionId) override;`
- L108 _public prototype_ `virtual bool GetItemAssetAccessSpecifier(const FContentBrowserItemData& InItem, EAssetAccessSpecifier& OutAssetAccessSpecifier) override;`
- L109 _public prototype_ `virtual bool CanModifyItemAssetAccessSpecifier(const FContentBrowserItemData& InItem) override;`
- L112 _public prototype_ `virtual bool Legacy_TryGetPackagePath(const FContentBrowserItemData& InItem, FName& OutPackagePath) override;` — Legacy functions seem necessary for FrontendFilters to work
- L113 _public prototype_ `virtual bool Legacy_TryGetAssetData(const FContentBrowserItemData& InItem, FAssetData& OutAssetData) override;`
- L114 _public prototype_ `virtual bool Legacy_TryConvertPackagePathToVirtualPath(const FName InPackagePath, FName& OutPath) override;`
- L115 _public prototype_ `virtual bool Legacy_TryConvertAssetDataToVirtualPath(const FAssetData& InAssetData, const bool InUseFolderPaths, FName& OutPath) override;`
- L118 _public prototype_ `virtual void RemoveUnusedCachedFilterData(const FContentBrowserDataFilterCacheIDOwner& IDOwner, TArrayView<const FName> InVirtualPathsInUse, const FContentBrowserDataFilter& DataFilter) override;`
- L120 _public prototype_ `virtual void ClearCachedFilterData(const FContentBrowserDataFilterCacheIDOwner& IDOwner) override;`
- L130 _public prototype_ `void AddAliases(const FAssetData& Asset, const TArray<FName>& Aliases, const bool bInIsFromMetaData = false, const bool bSkipPrimaryAssetValidation = false);` — Add a list of aliases for a given asset. @param Asset 						The asset to add aliases for. @param Aliases 						The aliases to add @param bInIsFromMetaData 			Should only be `true` if the list of aliases came from the `AliasTagName` metadata. @param bSkipPrimaryAssetValidation 	Use this if the asset being added is not a primary asset/is a re-director but should still be included in the Content Browser. (e.g. Verse classes)
- L131 _public prototype_ `void AddAliases(const FAssetData& Asset, const TArray<FContentBrowserLocalizedAlias>& Aliases, const bool bInIsFromMetaData = false, const bool bSkipPrimaryAssetValidation = false);`
- L133 _public prototype_ `void AddAlias(const FAssetData& Asset, const FName Alias, const bool bInIsFromMetaData = false, const bool bSkipPrimaryAssetValidation = false);` — Add an alias for a given asset. bInIsFromMetaData should only be true if the alias came from the AliasTagName metadata.
- L134 _public prototype_ `void AddAlias(const FAssetData& Asset, const FContentBrowserLocalizedAlias& Alias, const bool bInIsFromMetaData = false, const bool bSkipPrimaryAssetValidation = false);`
- L136 _public prototype_ `void RemoveAlias(const FSoftObjectPath& ObjectPath, const FName Alias);` — Remove the given alias from the data source
- L138 _public prototype_ `void RemoveAliases(const FSoftObjectPath& ObjectPath);` — Remove all aliases for the given object
- L140 _public function_ `void RemoveAliases(const FAssetData& Asset)` — Remove all aliases for the given asset
- L143 _public prototype_ `void RemoveAlias(const FName ObjectPath, const FName Alias);` — `UE_DEPRECATED(5.1, "FNames containing full asset paths are deprecated, use FSoftObjectPath instead")`
- L145 _public prototype_ `void RemoveAliases(const FName ObjectPath);` — `UE_DEPRECATED(5.1, "FNames containing full asset paths are deprecated, use FSoftObjectPath instead")`
- L151 _public prototype_ `void AddAliasFolderDisplayName(const FName AliasFolder, const FText& DisplayName);` — Add a display name override for the given alias folder, eg /MyAliases. @note To provide a display name override for an alias itself, use the overloads that take a FContentBrowserLocalizedAlias.
- L155 _public prototype_ `void RemoveAliasFolderDisplayName(const FName AliasFolder);` — Remove a display name override for the given alias folder, eg /MyAliases.
- L158 _public prototype_ `void RebuildAliases();` — When called, removes all aliases and triggers delegate for various systems to re-add aliases
- L161 _public function_ `FSimpleMulticastDelegate& OnRebuildAliases()` — Broadcast after RebuildAliases() called to allow systems to re-add aliases
- L164 _public prototype_ `void ReconcileAliasesFromMetaData(const FAssetData& Asset);` — Get all aliases from metadata for the given asset, then calls AddAlias or RemoveAlias for every alias that doesn't match the stored data.
- L166 _public prototype_ `void ReconcileAliasesForAsset(const FAssetData& Asset, const TArray<FName>& NewAliases);` — Calls AddAlias or RemoveAlias for every alias that doesn't match the stored data for the given asset.
- L167 _public prototype_ `void ReconcileAliasesForAsset(const FAssetData& Asset, const TArray<FContentBrowserLocalizedAlias>& NewAliases);`
- L170 _public prototype_ `void LogAliases() const;` — Logs all the content browser aliases
- L172 _public prototype_ `void SetFilterShouldMatchCollectionContent(bool bInFilterShouldMatchCollectionContent);`
- L175 _protected prototype_ `virtual void BuildRootPathVirtualTree() override;`
- L179 _private prototype_ `template <typename AliasType> void AddAliasImpl(const FAssetData& Asset, const AliasType& Alias, const bool bInIsFromMetaData, const bool bSkipPrimaryAssetValidation);`
- L181 _private prototype_ `template <typename AliasType> void AddAliasesImpl(const FAssetData& Asset, const TArray<AliasType>& Aliases, const bool bInIsFromMetaData, const bool bSkipPrimaryAssetValidation);`
- L183 _private prototype_ `template <typename AliasType> void ReconcileAliasesForAssetImpl(const FAssetData& Asset, const TArray<AliasType>& NewAliases);`
- L185 _private prototype_ `void OnAssetAdded(const FAssetData& InAssetData);`
- L186 _private prototype_ `void OnAssetRemoved(const FAssetData& InAssetData);`
- L187 _private prototype_ `void OnAssetUpdated(const FAssetData& InAssetData);`
- L188 _private prototype_ `void OnAssetLoaded(UObject* InAsset);`
- L189 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);`
- L192 _private prototype_ `void RemoveFoldersRecursively(FStringView LeafFolder);` — Helper function to remove a folder from the PathTree including all parent folders that are now empty as a result of the removal
- L194 _private prototype_ `void UpdateAliasesCachedAssetData(const FAssetData& InAssetData);`
- L195 _private prototype_ `void MakeItemModifiedUpdate(const FSoftObjectPath& ObjectPath);`
- L197 _private prototype_ `FContentBrowserItemData CreateAssetFolderItem(const FName InFolderPath);`
- L198 _private prototype_ `FContentBrowserItemData CreateAssetFileItem(const FContentBrowserUniqueAlias& Alias);`
- L200 _private member_ `IAssetRegistry* AssetRegistry = nullptr;`
- L201 _private member_ `IAssetTools* AssetTools = nullptr;`
- L202 _private member_ `FContentBrowserModule* ContentBrowserModule = nullptr;`
- L243 _private prototype_ `bool DoesAliasPassFilter(const FAliasData& AliasData, const FContentBrowserCompiledAssetDataFilter& Filter) const;`
- L246 _private member_ `FPathTree PathTree;` — The full folder hierarchy for all alias paths
- L248 _private member_ `TMap<FContentBrowserUniqueAlias, FAliasData> AllAliases;` — Alias data keyed by their full alias path, eg /Game/MyData/Aliases/SourceMesh
- L250 _private member_ `TMap<FSoftObjectPath, TArray<FName>> AliasesForObjectPath;` — A list of alias paths to display for each asset, eg /Game/Meshes/SourceMesh.SourceMesh
- L252 _private member_ `TMap<FName, TArray<FContentBrowserUniqueAlias>> AliasesInPackagePath;` — A list of alias paths to display for each folder, eg /Game/MyData/Aliases
- L254 _private member_ `TMap<FName, FContentBrowserUniqueAlias> AliasForInternalPath;` — The alias path to display for each file
- L256 _private member_ `TMap<FName, FText> AliasFolderDisplayNames;` — Alias folder display names keyed against their alias path, eg /Game/MyData/Aliases/
- L258 _private member_ `UContentBrowserAssetDataSource::FAssetDataSourceFilterCache FilterCache;`
- L261 _private member_ `FSimpleMulticastDelegate RebuildAliasesDelegate;` — Delegate broadcast after all aliases removed to give chance for systems to re-add aliases
- L264 _private member_ `bool bFilterShouldMatchCollectionContent = true;` — If true, EnumerateItemsMatchingFilter will include aliases of items contained in collections included in the filter

#### struct `UContentBrowserAliasDataSource::FAliasData`  
`struct FAliasData`  
_L204-242_
- L206 _public function_ `FAliasData()`
- L207 _public function_ `FAliasData(const FAssetData& InAssetData, const FName InPackagePath, const FText& InDisplayName, const bool bInIsFromMetaData = false) : AssetData(InAssetData), PackagePath(InPackagePath), AliasDisplayName(InDisplayName), bIsFromMetaData(bInIsFromMetaData)`
- L231 _public member_ `FAssetData AssetData;` — The source asset for this alias
- L233 _public member_ `FName PackagePath;` — The folder path that contains the alias, /MyAliases
- L235 _public member_ `FName PackageName;` — PackagePath/SourceAssetName, /MyAliases/SomeAsset_Hash
- L237 _public member_ `FName InternalPath;` — PackageName.SourceAssetName, /MyAliases/SomeAsset_Hash.SomeAsset_Hash
- L239 _public member_ `FText AliasDisplayName;` — A non-unique display name for this alias
- L241 _public member_ `bool bIsFromMetaData = false;` — Whether this alias was generated from package metadata or manually through the C++ interface

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API CONTENTBROWSERALIASDATASOURCE_API`
- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogContentBrowserAliasDataSource, Log, All);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogContentBrowserAliasDataSource, Log, All);`
- L27 _typedef_ `typedef TPair<FSoftObjectPath, FName> FContentBrowserUniqueAlias;` — A unique alias is a pair of SourceObjectPath:AliasPath, eg /Game/MyAsset.MyAsset:/Game/SomeFolder/MyAlias

### `Plugins/Editor/ContentBrowser/ContentBrowserAliasDataSource/Source/ContentBrowserAliasDataSource/Public/ContentBrowserAliasDataSourceModule.h` (Public)


#### class `FContentBrowserAliasDataSourceModule`  
`class FContentBrowserAliasDataSourceModule : public FDefaultModuleImpl`  
_L9-22_
- inherits: `FDefaultModuleImpl`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void PreUnloadCallback() override;`
- L16 _public function_ `TWeakObjectPtr<UContentBrowserAliasDataSource> GetAliasDataSource()` — `UE_DEPRECATED(5.4, "Call TryGetAliasDataSource instead.")`
- L18 _public prototype_ `UContentBrowserAliasDataSource* TryGetAliasDataSource();`
- L21 _private member_ `TStrongObjectPtr<UContentBrowserAliasDataSource> AliasDataSource;`

### `Plugins/Editor/ContentBrowser/ContentBrowserAliasDataSource/Source/ContentBrowserAliasDataSource/Public/ContentBrowserLocalizedAlias.h` (Public)


#### struct `FContentBrowserLocalizedAlias`  
`struct FContentBrowserLocalizedAlias`  
_L9-28_
- desc: Container for an alias and its optional display name override
- L11 _public member_ `FName Alias;`
- L12 _public member_ `FText DisplayName;`
- L14 _public function_ `bool operator==(const FContentBrowserLocalizedAlias& Other) const`
- L19 _public function_ `bool operator!=(const FContentBrowserLocalizedAlias& Other) const`

#### Free symbols / members of external scopes

- L24 _function_ `friend uint32 GetTypeHash(const FContentBrowserLocalizedAlias& This)`
