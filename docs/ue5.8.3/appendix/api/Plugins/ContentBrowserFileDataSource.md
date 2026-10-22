# Plugins / ContentBrowserFileDataSource

- module root: `Plugins/Editor/ContentBrowser/ContentBrowserFileDataSource/Source/ContentBrowserFileDataSource`
- headers: 4; symbols: 256
- symbol kinds: class=8, delegate=15, enum=1, enumerator=2, function=12, macro=3, member=53, namespace=5, prototype=151, struct=6
- DynamicallyLoadedModuleNames: DirectoryWatcher
- PrivateDependencyModuleNames: AssetTools, Slate, SlateCore, SourceControl, SourceControlWindows, ToolMenus, UncontrolledChangelists, UnrealEd
- PrivateIncludePathModuleNames: DirectoryWatcher
- PublicDependencyModuleNames: ContentBrowserData, Core, CoreUObject

### `Plugins/Editor/ContentBrowser/ContentBrowserFileDataSource/Source/ContentBrowserFileDataSource/Private/FileSourceControlContextMenu.h` (Private)


#### class `FFileSourceControlContextMenu`  
`class FFileSourceControlContextMenu`  
_L13-23_
- desc: Display source control options in the given menu section based on what's selected in the menu context
- L16 _public prototype_ `~FFileSourceControlContextMenu();`
- L19 _public prototype_ `void MakeContextMenu(FToolMenuSection& InSection, const UContentBrowserDataMenuContext_FileMenu* InFileMenuContext, const UContentBrowserDataMenuContext_FolderMenu* InFolderMenuContext);` — Makes the context menu widget
- L22 _private member_ `TSharedPtr<FFileSourceControlContextMenuState> InnerState;`

### `Plugins/Editor/ContentBrowser/ContentBrowserFileDataSource/Source/ContentBrowserFileDataSource/Public/ContentBrowserFileDataCore.h` (Public)


#### class `ContentBrowserFileData::FDefaultFileActions`  
`class FDefaultFileActions`  
_L138-143_
- L141 _public prototype_ `static bool ItemPassesFilter(const FName InFilePath, const FString& InFilename, const FContentBrowserDataFilter& InFilter, const bool bIsFile);`
- L142 _public prototype_ `static bool GetItemAttribute(const FName InFilePath, const FString& InFilename, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CONTENTBROWSERFILEDATASOURCE_API`
- L13 _namespace_ `namespace ContentBrowserFileData`
- L14 _namespace_ `namespace ContentBrowserFileData`
- L15 _namespace_ `namespace ContentBrowserFileData`
- L20 _namespace_ `namespace ContentBrowserFileData`
- L23 _prototype_ `FContentBrowserItemData CreateFolderItem(UContentBrowserDataSource* InOwnerDataSource, const FName InVirtualPath, const FName InInternalPath, const FString& InFilename, TWeakPtr<const ContentBrowserFileData::FDirectoryActions> InDirectoryActions);` (scope `ContentBrowserFileData`)
- L25 _prototype_ `FContentBrowserItemData CreateFileItem(UContentBrowserDataSource* InOwnerDataSource, const FName InVirtualPath, const FName InInternalPath, const FString& InFilename, TWeakPtr<const ContentBrowserFileData::FFileActions> InFileActions);` (scope `ContentBrowserFileData`)
- L27 _prototype_ `TSharedPtr<const FContentBrowserFolderItemDataPayload> GetFolderItemPayload(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem);` (scope `ContentBrowserFileData`)
- L29 _prototype_ `TSharedPtr<const FContentBrowserFileItemDataPayload> GetFileItemPayload(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem);` (scope `ContentBrowserFileData`)
- L31 _prototype_ `void EnumerateFolderItemPayloads(const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, TFunctionRef<bool(const TSharedRef<const FContentBrowserFolderItemDataPayload>&)> InFolderPayloadCallback);` (scope `ContentBrowserFileData`)
- L33 _prototype_ `void EnumerateFileItemPayloads(const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, TFunctionRef<bool(const TSharedRef<const FContentBrowserFileItemDataPayload>&)> InFilePayloadCallback);` (scope `ContentBrowserFileData`)
- L35 _prototype_ `void EnumerateItemPayloads(const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, TFunctionRef<bool(const TSharedRef<const FContentBrowserFolderItemDataPayload>&)> InFolderPayloadCallback, TFunctionRef<bool(const TSharedRef<const FContentBrowserFileItemDataPayload>&)> InFilePayloadCallback);` (scope `ContentBrowserFileData`)
- L37 _prototype_ `void SetOptionalErrorMessage(FText* OutErrorMsg, FText InErrorMsg);` (scope `ContentBrowserFileData`)
- L39 _prototype_ `void MakeUniqueFilename(FString& InOutFilename);` (scope `ContentBrowserFileData`)
- L41 _prototype_ `bool CanModifyDirectory(const FString& InFilename, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L43 _prototype_ `bool CanModifyFile(const FString& InFilename, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L45 _prototype_ `bool CanModifyItem(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L47 _prototype_ `bool CanModifyFolderItem(const FContentBrowserFolderItemDataPayload& InFolderPayload, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L49 _prototype_ `bool CanModifyFileItem(const FContentBrowserFileItemDataPayload& InFilePayload, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L51 _prototype_ `bool CanEditItem(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L53 _prototype_ `bool CanEditFileItem(const FContentBrowserFileItemDataPayload& InFilePayload, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L55 _prototype_ `bool EditItems(const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems);` (scope `ContentBrowserFileData`)
- L57 _prototype_ `bool EditFileItems(TArrayView<const TSharedRef<const FContentBrowserFileItemDataPayload>> InFilePayloads);` (scope `ContentBrowserFileData`)
- L59 _prototype_ `bool CanPreviewItem(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L61 _prototype_ `bool CanPreviewFileItem(const FContentBrowserFileItemDataPayload& InFilePayload, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L63 _prototype_ `bool PreviewItems(const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems);` (scope `ContentBrowserFileData`)
- L65 _prototype_ `bool PreviewFileItems(TArrayView<const TSharedRef<const FContentBrowserFileItemDataPayload>> InFilePayloads);` (scope `ContentBrowserFileData`)
- L67 _prototype_ `bool CanDuplicateItem(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L69 _prototype_ `bool CanDuplicateFileItem(const FContentBrowserFileItemDataPayload& InFilePayload, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L71 _prototype_ `bool DuplicateItem(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, TSharedPtr<const FContentBrowserFileItemDataPayload_Duplication>& OutNewItemPayload);` (scope `ContentBrowserFileData`)
- L73 _prototype_ `bool DuplicateFileItem(const FContentBrowserFileItemDataPayload& InFilePayload, TSharedPtr<const FContentBrowserFileItemDataPayload_Duplication>& OutNewItemPayload);` (scope `ContentBrowserFileData`)
- L75 _prototype_ `bool DuplicateItems(const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, TArray<TSharedRef<const FContentBrowserFileItemDataPayload>>& OutNewFilePayloads);` (scope `ContentBrowserFileData`)
- L77 _prototype_ `bool DuplicateFileItems(TArrayView<const TSharedRef<const FContentBrowserFileItemDataPayload>> InFilePayloads, TArray<TSharedRef<const FContentBrowserFileItemDataPayload>>& OutNewFilePayloads);` (scope `ContentBrowserFileData`)
- L79 _prototype_ `bool CanDeleteItem(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L81 _prototype_ `bool CanDeleteFolderItem(const FContentBrowserFolderItemDataPayload& InFolderPayload, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L83 _prototype_ `bool CanDeleteFileItem(const FContentBrowserFileItemDataPayload& InFilePayload, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L85 _prototype_ `bool DeleteItems(const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems);` (scope `ContentBrowserFileData`)
- L87 _prototype_ `bool DeleteFolderItems(TArrayView<const TSharedRef<const FContentBrowserFolderItemDataPayload>> InFolderPayloads);` (scope `ContentBrowserFileData`)
- L89 _prototype_ `bool DeleteFileItems(TArrayView<const TSharedRef<const FContentBrowserFileItemDataPayload>> InFilePayloads);` (scope `ContentBrowserFileData`)
- L91 _prototype_ `bool CanRenameItem(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, const FString* InNewName, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L92 _prototype_ `bool CanRenameItem(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, const bool bCheckUniqueName, const FString* InNewName, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L94 _prototype_ `bool CanRenameFolderItem(const FContentBrowserFolderItemDataPayload& InFolderPayload, const bool bCheckUniqueName, const FString* InNewName, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L96 _prototype_ `bool CanRenameFileItem(const FContentBrowserFileItemDataPayload& InFilePayload, const bool bCheckUniqueName, const FString* InNewName, FText* OutErrorMsg);` (scope `ContentBrowserFileData`)
- L98 _prototype_ `bool RenameItem(const FFileConfigData& InConfig, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, const FString& InNewName, FName& OutNewInternalPath, FString& OutNewFilename);` (scope `ContentBrowserFileData`)
- L100 _prototype_ `bool RenameFolderItem(const FFileConfigData& InConfig, const FContentBrowserFolderItemDataPayload& InFolderPayload, const FString& InNewName, FName& OutNewInternalPath, FString& OutNewFilename);` (scope `ContentBrowserFileData`)
- L102 _prototype_ `bool RenameFileItem(const FContentBrowserFileItemDataPayload& InFilePayload, const FString& InNewName, FName& OutNewInternalPath, FString& OutNewFilename);` (scope `ContentBrowserFileData`)
- L104 _prototype_ `bool CopyItems(const FFileConfigData& InConfig, const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, const FString& InDestDiskPath);` (scope `ContentBrowserFileData`)
- L106 _prototype_ `bool CopyFolderItems(const FFileConfigData& InConfig, TArrayView<const TSharedRef<const FContentBrowserFolderItemDataPayload>> InFolderPayloads, const FString& InDestDiskPath);` (scope `ContentBrowserFileData`)
- L108 _prototype_ `bool CopyFileItems(TArrayView<const TSharedRef<const FContentBrowserFileItemDataPayload>> InFilePayloads, const FString& InDestDiskPath);` (scope `ContentBrowserFileData`)
- L110 _prototype_ `bool MoveItems(const FFileConfigData& InConfig, const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, const FString& InDestDiskPath);` (scope `ContentBrowserFileData`)
- L112 _prototype_ `bool MoveFolderItems(const FFileConfigData& InConfig, TArrayView<const TSharedRef<const FContentBrowserFolderItemDataPayload>> InFolderPayloads, const FString& InDestDiskPath);` (scope `ContentBrowserFileData`)
- L114 _prototype_ `bool MoveFileItems(TArrayView<const TSharedRef<const FContentBrowserFileItemDataPayload>> InFilePayloads, const FString& InDestDiskPath);` (scope `ContentBrowserFileData`)
- L116 _prototype_ `bool UpdateItemThumbnail(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FAssetThumbnail& InThumbnail);` (scope `ContentBrowserFileData`)
- L118 _prototype_ `bool UpdateFileItemThumbnail(const FContentBrowserFileItemDataPayload& InFilePayload, FAssetThumbnail& InThumbnail);` (scope `ContentBrowserFileData`)
- L120 _prototype_ `bool GetItemPhysicalPath(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FString& OutDiskPath);` (scope `ContentBrowserFileData`)
- L122 _prototype_ `bool GetFolderItemPhysicalPath(const FContentBrowserFolderItemDataPayload& InFolderPayload, FString& OutDiskPath);` (scope `ContentBrowserFileData`)
- L124 _prototype_ `bool GetFileItemPhysicalPath(const FContentBrowserFileItemDataPayload& InFilePayload, FString& OutDiskPath);` (scope `ContentBrowserFileData`)
- L126 _prototype_ `bool GetItemAttribute(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue);` (scope `ContentBrowserFileData`)
- L128 _prototype_ `bool GetFolderItemAttribute(const FContentBrowserFolderItemDataPayload& InFolderPayload, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue);` (scope `ContentBrowserFileData`)
- L130 _prototype_ `bool GetFileItemAttribute(const FContentBrowserFileItemDataPayload& InFilePayload, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue);` (scope `ContentBrowserFileData`)
- L132 _prototype_ `bool GetItemAttributes(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, const bool InIncludeMetaData, FContentBrowserItemDataAttributeValues& OutAttributeValues);` (scope `ContentBrowserFileData`)
- L134 _prototype_ `bool GetFolderItemAttributes(const FContentBrowserFolderItemDataPayload& InFolderPayload, const bool InIncludeMetaData, FContentBrowserItemDataAttributeValues& OutAttributeValues);` (scope `ContentBrowserFileData`)
- L136 _prototype_ `bool GetFileItemAttributes(const FContentBrowserFileItemDataPayload& InFilePayload, const bool InIncludeMetaData, FContentBrowserItemDataAttributeValues& OutAttributeValues);` (scope `ContentBrowserFileData`)

### `Plugins/Editor/ContentBrowser/ContentBrowserFileDataSource/Source/ContentBrowserFileDataSource/Public/ContentBrowserFileDataPayload.h` (Public)


#### struct `ContentBrowserFileData::FCommonActions`  
`struct FCommonActions`  
_L14-51_
- L16 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FCanCreate, const FName , const FString& , FText* );`
- L17 _public member_ `FCanCreate CanCreate;`
- L25 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FConfigureCreation, FString& , FStructOnScope& );` — Queries user for arbitrary creation settings @param OutFileBasename outputs a file basename suggestion (no path, no extension) which can be empty @param OutCreationConfig outputs opaque creation settings @return false if creation gets canceled.
- L26 _public member_ `FConfigureCreation ConfigureCreation;`
- L28 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FCreate, const FName , const FString& , const FStructOnScope& );`
- L29 _public member_ `FCreate Create;`
- L31 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FCanDelete, const FName , const FString& , FText* );`
- L32 _public member_ `FCanDelete CanDelete;`
- L34 _public prototype_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FCanRename, const FName , const FString& , const FString* , FText* );`
- L35 _public member_ `FCanRename CanRename;`
- L37 _public prototype_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FCanCopy, const FName , const FString& , const FString& , FText* );`
- L38 _public member_ `FCanCopy CanCopy;`
- L40 _public prototype_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FCanMove, const FName , const FString& , const FString& , FText* );`
- L41 _public member_ `FCanMove CanMove;`
- L43 _public prototype_ `DECLARE_DELEGATE_RetVal_FiveParams(bool, FGetAttribute, const FName , const FString& , const bool , const FName , FContentBrowserItemDataAttributeValue& );`
- L44 _public member_ `FGetAttribute GetAttribute;`
- L46 _public prototype_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FGetAttributes, const FName , const FString& , const bool , FContentBrowserItemDataAttributeValues& );`
- L47 _public member_ `FGetAttributes GetAttributes;`
- L49 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FPassesFilter, const FName , const FString& , const FContentBrowserDataFilter& );`
- L50 _public member_ `FPassesFilter PassesFilter;`

#### struct `ContentBrowserFileData::FDirectoryActions`  
`struct FDirectoryActions : public FCommonActions`  
_L53-55_
- inherits: `FCommonActions`

#### struct `ContentBrowserFileData::FFileActions`  
`struct FFileActions : public FCommonActions`  
_L57-89_
- inherits: `FCommonActions`
- L59 _public member_ `FString TypeExtension;`
- L61 _public member_ `FTopLevelAssetPath TypeName;`
- L63 _public member_ `FText TypeDisplayName;`
- L65 _public member_ `FText TypeShortDescription;`
- L67 _public member_ `FText TypeFullDescription;`
- L69 _public member_ `FString DefaultNewFileName;`
- L71 _public member_ `FLinearColor TypeColor;`
- L73 _public member_ `ELaunchVerb::Type DefaultEditVerb = ELaunchVerb::Edit;`
- L75 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FCanEdit, const FName , const FString& , FText* );`
- L76 _public member_ `FCanEdit CanEdit;`
- L78 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FEdit, const FName , const FString& );`
- L79 _public member_ `FEdit Edit;`
- L81 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FCanPreview, const FName , const FString& , FText* );`
- L82 _public member_ `FCanPreview CanPreview;`
- L84 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FPreview, const FName , const FString& );`
- L85 _public member_ `FPreview Preview;`
- L87 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FCanDuplicate, const FName , const FString& , FText* );`
- L88 _public member_ `FCanDuplicate CanDuplicate;`

#### class `ContentBrowserFileData::FFileConfigData`  
`class FFileConfigData`  
_L91-111_
- L94 _public prototype_ `void SetDirectoryActions(const FDirectoryActions& InDirectoryActions);`
- L96 _public prototype_ `TSharedPtr<const FDirectoryActions> GetDirectoryActions();`
- L98 _public prototype_ `void RegisterFileActions(const FFileActions& InFileActions);`
- L100 _public prototype_ `TSharedPtr<const FFileActions> FindFileActionsForExtension(FStringView InTypeExtension) const;`
- L101 _public prototype_ `TSharedPtr<const FFileActions> FindFileActionsForFilename(FStringView InFilename) const;`
- L103 _public prototype_ `void EnumerateFileActions(TFunctionRef<bool(TSharedRef<const FFileActions>)> InCallback) const;`
- L105 _public prototype_ `FText GetDiscoveryDescription() const;`
- L108 _private member_ `TSharedPtr<const FDirectoryActions> DirectoryActions;`
- L110 _private member_ `TMap<FString, TSharedPtr<const FFileActions>> FileActionsMap;`

#### class `FContentBrowserFolderItemDataPayload`  
`class FContentBrowserFolderItemDataPayload : public IContentBrowserItemDataPayload`  
_L114-145_
- inherits: `IContentBrowserItemDataPayload`
- L117 _public function_ `explicit FContentBrowserFolderItemDataPayload(const FName InInternalPath, const FString& InFilename, TWeakPtr<const ContentBrowserFileData::FDirectoryActions> InDirectoryActions) : InternalPath(InInternalPath) , Filename(InFilename) , DirectoryActions(MoveTemp(InDirectoryActions))`
- L124 _public function_ `FName GetInternalPath() const`
- L129 _public function_ `const FString& GetFilename() const`
- L134 _public function_ `TSharedPtr<const ContentBrowserFileData::FDirectoryActions> GetDirectoryActions() const`
- L140 _private member_ `FName InternalPath;`
- L142 _private member_ `FString Filename;`
- L144 _private member_ `TWeakPtr<const ContentBrowserFileData::FDirectoryActions> DirectoryActions;`

#### class `FContentBrowserFileItemDataPayload`  
`class FContentBrowserFileItemDataPayload : public IContentBrowserItemDataPayload`  
_L147-178_
- inherits: `IContentBrowserItemDataPayload`
- L150 _public function_ `FContentBrowserFileItemDataPayload(const FName InInternalPath, const FString& InFilename, TWeakPtr<const ContentBrowserFileData::FFileActions> InFileActions) : InternalPath(InInternalPath) , Filename(InFilename) , FileActions(MoveTemp(InFileActions))`
- L157 _public function_ `FName GetInternalPath() const`
- L162 _public function_ `const FString& GetFilename() const`
- L167 _public function_ `TSharedPtr<const ContentBrowserFileData::FFileActions> GetFileActions() const`
- L173 _private member_ `FName InternalPath;`
- L175 _private member_ `FString Filename;`
- L177 _private member_ `TWeakPtr<const ContentBrowserFileData::FFileActions> FileActions;`

#### class `FContentBrowserFileItemDataPayload_Duplication`  
`class FContentBrowserFileItemDataPayload_Duplication : public FContentBrowserFileItemDataPayload`  
_L180-197_
- inherits: `FContentBrowserFileItemDataPayload`
- L183 _public function_ `FContentBrowserFileItemDataPayload_Duplication(const FName InInternalPath, const FString& InFilename, TWeakPtr<const ContentBrowserFileData::FFileActions> InFileActions, const FString& InSourceFilename) : FContentBrowserFileItemDataPayload(InInternalPath, InFilename, MoveTemp(InFileActions)) , SourceFilename(InSourceFilename)`
- L189 _public function_ `const FString& GetSourceFilename() const`
- L196 _private member_ `FString SourceFilename;` — The source file that we're duplicating

#### class `FContentBrowserFileItemDataPayload_Creation`  
`class FContentBrowserFileItemDataPayload_Creation : public FContentBrowserFileItemDataPayload`  
_L200-216_
- inherits: `FContentBrowserFileItemDataPayload`
- L203 _public function_ `FContentBrowserFileItemDataPayload_Creation(const FName InInternalPath, const FString& InFilename, TWeakPtr<const ContentBrowserFileData::FFileActions> InFileActions, FStructOnScope&& InCreationConfig) : FContentBrowserFileItemDataPayload(InInternalPath, InFilename, MoveTemp(InFileActions)) , CreationConfig(MoveTemp(InCreationConfig))`
- L209 _public function_ `const FStructOnScope& GetCreationConfig() const`
- L215 _private member_ `FStructOnScope CreationConfig;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CONTENTBROWSERFILEDATASOURCE_API`
- L12 _namespace_ `namespace ContentBrowserFileData`
- L16 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FCanCreate, const FName , const FString& , FText* );`
- L25 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FConfigureCreation, FString& , FStructOnScope& );` — Queries user for arbitrary creation settings @param OutFileBasename outputs a file basename suggestion (no path, no extension) which can be empty @param OutCreationConfig outputs opaque creation settings @return false if creation gets canceled.
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FCreate, const FName , const FString& , const FStructOnScope& );`
- L31 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FCanDelete, const FName , const FString& , FText* );`
- L34 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FCanRename, const FName , const FString& , const FString* , FText* );`
- L37 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FCanCopy, const FName , const FString& , const FString& , FText* );`
- L40 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FCanMove, const FName , const FString& , const FString& , FText* );`
- L43 _delegate_ `DECLARE_DELEGATE_RetVal_FiveParams(bool, FGetAttribute, const FName , const FString& , const bool , const FName , FContentBrowserItemDataAttributeValue& );`
- L46 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FGetAttributes, const FName , const FString& , const bool , FContentBrowserItemDataAttributeValues& );`
- L49 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FPassesFilter, const FName , const FString& , const FContentBrowserDataFilter& );`
- L75 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FCanEdit, const FName , const FString& , FText* );`
- L78 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FEdit, const FName , const FString& );`
- L81 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FCanPreview, const FName , const FString& , FText* );`
- L84 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FPreview, const FName , const FString& );`
- L87 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FCanDuplicate, const FName , const FString& , FText* );`

### `Plugins/Editor/ContentBrowser/ContentBrowserFileDataSource/Source/ContentBrowserFileDataSource/Public/ContentBrowserFileDataSource.h` (Public)


#### struct `FContentBrowserCompiledFileDataFilter`  
`struct FContentBrowserCompiledFileDataFilter`  
_L19-30_
- reflection: `USTRUCT()`
- L24 _public member_ `FName VirtualPathName;`
- L25 _public member_ `FString VirtualPath;`
- L26 _public member_ `bool bRecursivePaths = false;`
- L27 _public member_ `EContentBrowserItemAttributeFilter ItemAttributeFilter = EContentBrowserItemAttributeFilter::IncludeNone;`
- L28 _public member_ `TSharedPtr<FPathPermissionList> PermissionList;`
- L29 _public member_ `TArray<FString> FileExtensionsToInclude;`

#### class `UContentBrowserFileDataSource`  
`class UContentBrowserFileDataSource : public UContentBrowserDataSource`  
_L33-209_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContentBrowserDataSource`
- L38 _public prototype_ `void Initialize(const ContentBrowserFileData::FFileConfigData& InConfig, const bool InAutoRegister = true);`
- L40 _public prototype_ `virtual void Shutdown() override;`
- L42 _public prototype_ `void AddFileMount(const FName InFileMountPath, const FString& InFileMountDiskPath);`
- L44 _public prototype_ `void RemoveFileMount(const FName InFileMountPath);`
- L46 _public prototype_ `bool HasFileMount(const FName InFileMountPath) const;`
- L48 _public prototype_ `virtual void Tick(const float InDeltaTime);`
- L50 _public prototype_ `virtual void CompileFilter(const FName InPath, const FContentBrowserDataFilter& InFilter, FContentBrowserDataCompiledFilter& OutCompiledFilter) override;`
- L52 _public prototype_ `virtual void EnumerateItemsMatchingFilter(const FContentBrowserDataCompiledFilter& InFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;`
- L54 _public prototype_ `virtual void EnumerateItemsAtPath(const FName InPath, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;`
- L56 _public prototype_ `virtual void EnumerateItemsAtUserProvidedPath(const FStringView InPath, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;`
- L58 _public prototype_ `virtual bool CanCreateFolder(const FName InPath, FText* OutErrorMsg) override;`
- L60 _public prototype_ `virtual bool CreateFolder(const FName InPath, const TSharedPtr<IContentBrowserHideFolderIfEmptyFilter>& HideFolderIfEmptyFilter, FContentBrowserItemDataTemporaryContext& OutPendingItem) override;`
- L62 _public prototype_ `virtual bool IsDiscoveringItems(FText* OutStatus = nullptr) override;`
- L64 _public prototype_ `virtual bool PrioritizeSearchPath(const FName InPath) override;`
- L66 _public prototype_ `virtual bool IsFolderVisible(const FName InPath, const EContentBrowserIsFolderVisibleFlags InFlags, const FContentBrowserFolderContentsFilter& InContentsFilter) override;`
- L68 _public prototype_ `virtual bool DoesItemPassFilter(const FContentBrowserItemData& InItem, const FContentBrowserDataCompiledFilter& InFilter) override;`
- L70 _public prototype_ `virtual bool GetItemAttribute(const FContentBrowserItemData& InItem, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue) override;`
- L72 _public prototype_ `virtual bool GetItemAttributes(const FContentBrowserItemData& InItem, const bool InIncludeMetaData, FContentBrowserItemDataAttributeValues& OutAttributeValues) override;`
- L74 _public prototype_ `virtual bool GetItemPhysicalPath(const FContentBrowserItemData& InItem, FString& OutDiskPath) override;`
- L76 _public prototype_ `virtual bool CanEditItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg) override;`
- L78 _public prototype_ `virtual bool EditItem(const FContentBrowserItemData& InItem) override;`
- L80 _public prototype_ `virtual bool BulkEditItems(TArrayView<const FContentBrowserItemData> InItems) override;`
- L82 _public prototype_ `virtual bool CanPreviewItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg) override;`
- L84 _public prototype_ `virtual bool PreviewItem(const FContentBrowserItemData& InItem) override;`
- L86 _public prototype_ `virtual bool BulkPreviewItems(TArrayView<const FContentBrowserItemData> InItems) override;`
- L88 _public prototype_ `virtual bool CanDuplicateItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg) override;`
- L90 _public prototype_ `virtual bool DuplicateItem(const FContentBrowserItemData& InItem, FContentBrowserItemDataTemporaryContext& OutPendingItem) override;`
- L92 _public prototype_ `virtual bool BulkDuplicateItems(TArrayView<const FContentBrowserItemData> InItems, TArray<FContentBrowserItemData>& OutNewItems) override;`
- L94 _public prototype_ `virtual bool CanDeleteItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg) override;`
- L96 _public prototype_ `virtual bool DeleteItem(const FContentBrowserItemData& InItem) override;`
- L98 _public prototype_ `virtual bool BulkDeleteItems(TArrayView<const FContentBrowserItemData> InItems) override;`
- L100 _public prototype_ `virtual bool CanRenameItem(const FContentBrowserItemData& InItem, const FString* InNewName, const IContentBrowserHideFolderIfEmptyFilter* HideFolderIfEmptyFilter, FText* OutErrorMsg) override;`
- L102 _public prototype_ `virtual bool RenameItem(const FContentBrowserItemData& InItem, const FString& InNewName, FContentBrowserItemData& OutNewItem) override;`
- L104 _public prototype_ `virtual bool CanCopyItem(const FContentBrowserItemData& InItem, const FName InDestPath, FText* OutErrorMsg) override;`
- L106 _public prototype_ `virtual bool CopyItem(const FContentBrowserItemData& InItem, const FName InDestPath) override;`
- L108 _public prototype_ `virtual bool BulkCopyItems(TArrayView<const FContentBrowserItemData> InItems, const FName InDestPath) override;`
- L110 _public prototype_ `virtual bool CanMoveItem(const FContentBrowserItemData& InItem, const FName InDestPath, FText* OutErrorMsg) override;`
- L112 _public prototype_ `virtual bool MoveItem(const FContentBrowserItemData& InItem, const FName InDestPath) override;`
- L114 _public prototype_ `virtual bool BulkMoveItems(TArrayView<const FContentBrowserItemData> InItems, const FName InDestPath) override;`
- L116 _public prototype_ `virtual bool UpdateThumbnail(const FContentBrowserItemData& InItem, FAssetThumbnail& InThumbnail) override;`
- L118 _public prototype_ `virtual void BuildRootPathVirtualTree() override;`
- L141 _protected prototype_ `FContentBrowserItemData CreateFolderItem(const FName InInternalPath, const FString& InFilename);`
- L143 _protected prototype_ `FContentBrowserItemData CreateFileItem(const FName InInternalPath, const FString& InFilename);`
- L145 _protected prototype_ `FContentBrowserItemData CreateItemFromDiscovered(const FName InInternalPath, const FDiscoveredItem& InDiscoveredItem);`
- L147 _protected prototype_ `TSharedPtr<const FContentBrowserFolderItemDataPayload> GetFolderItemPayload(const FContentBrowserItemData& InItem) const;`
- L149 _protected prototype_ `TSharedPtr<const FContentBrowserFileItemDataPayload> GetFileItemPayload(const FContentBrowserItemData& InItem) const;`
- L151 _protected prototype_ `bool HideFolderIfEmpty(const IContentBrowserHideFolderIfEmptyFilter& HideFolderIfEmptyFilter, FName Path, FStringView PathString) const;`
- L153 _protected prototype_ `bool IsKnownFileMount(const FName InMountPath, FString* OutDiskPath = nullptr) const;`
- L155 _protected prototype_ `bool IsRootFileMount(const FName InMountPath, FString* OutDiskPath = nullptr) const;`
- L157 _protected prototype_ `void AddDiscoveredItem(FDiscoveredItem::EType InItemType, const FString& InMountPath, const FString& InDiskPath, const bool bIsRootPath);`
- L158 _protected prototype_ `void AddDiscoveredItemImpl(FDiscoveredItem::EType InItemType, const FString& InMountPath, const FString& InDiskPath, const FName InChildMountPathName, const bool bIsRootPath);`
- L160 _protected prototype_ `void RemoveDiscoveredItem(const FString& InMountPath);`
- L161 _protected prototype_ `void RemoveDiscoveredItem(const FName InMountPath);`
- L162 _protected prototype_ `void RemoveDiscoveredItemImpl(const FName InMountPath, const bool bParentIsOrphan);`
- L164 _protected prototype_ `void OnPathPopulated(const FName InPath);`
- L165 _protected prototype_ `void OnPathPopulated(const FStringView InPath);`
- L167 _protected prototype_ `void OnAlwaysShowPath(const FName InPath);`
- L168 _protected prototype_ `void OnAlwaysShowPath(const FStringView InPath);`
- L171 _protected prototype_ `void OnDirectoryChanged(const TArray<FFileChangeData>& InFileChanges, const FString InFileMountPath, const FString InFileMountDiskPath);` — Called when a file in a watched directory changes on disk
- L173 _protected prototype_ `void PopulateAddNewContextMenu(UToolMenu* InMenu);`
- L175 _protected prototype_ `void OnNewFileRequested(const FName InDestFolderPath, const FString InDestFolder, TSharedRef<const ContentBrowserFileData::FFileActions> InFileActions, UContentBrowserDataMenuContext_AddNewMenu::FOnBeginItemCreation InOnBeginItemCreation);`
- L177 _protected prototype_ `bool OnValidateItemName(const FContentBrowserItemData& InItem, const FString& InProposedName, FText* OutErrorMsg);`
- L179 _protected prototype_ `FContentBrowserItemData OnFinalizeCreateFolder(const FContentBrowserItemData& InItemData, const FString& InProposedName, FText* OutErrorMsg);`
- L181 _protected prototype_ `FContentBrowserItemData OnFinalizeCreateFile(const FContentBrowserItemData& InItemData, const FString& InProposedName, FText* OutErrorMsg);`
- L183 _protected prototype_ `FContentBrowserItemData OnFinalizeDuplicateFile(const FContentBrowserItemData& InItemData, const FString& InProposedName, FText* OutErrorMsg);`
- L185 _protected prototype_ `bool PassesFilters(const FName InPath, const int32 InFolderDepthChecked, const FContentBrowserCompiledFileDataFilter& InFileDataFilter) const;`
- L186 _protected prototype_ `static bool PassesFilters(const FStringView InPath, const FDiscoveredItem& InDiscoveredItem, const int32 InFolderDepthChecked, const FContentBrowserCompiledFileDataFilter& InFileDataFilter);`
- L188 _protected member_ `ContentBrowserFileData::FFileConfigData Config;`
- L190 _protected member_ `TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;`
- L192 _protected member_ `TSortedMap<FName, FFileMount, FDefaultAllocator, FNameFastLess> RegisteredFileMounts;`
- L193 _protected member_ `TMap<FName, TArray<FName>> RegisteredFileMountRoots;`
- L195 _protected member_ `TMap<FName, FDiscoveredItem> DiscoveredItems;`
- L197 _protected member_ `TSharedPtr<FContentBrowserFileDataDiscovery> BackgroundDiscovery;`
- L203 _protected member_ `TSet<FString> AlwaysVisibleFolders;` — The set of folders that should always be visible, even if they contain no files in the Content Browser view. This will include root file mounts, and any folders that have been created directly (or indirectly) by a user action.
- L208 _protected member_ `TSet<FString> EmptyFolders;` — A cache of folders that contain no files in the Content Browser view.

#### struct `UContentBrowserFileDataSource::FFileMount`  
`struct FFileMount`  
_L122-126_
- L124 _public member_ `FString DiskPath;`
- L125 _public member_ `FDelegateHandle DirectoryWatcherHandle;`

#### struct `UContentBrowserFileDataSource::FDiscoveredItem`  
`struct FDiscoveredItem`  
_L128-139_
- L136 _public member_ `EType Type;`
- L137 _public member_ `FString DiskPath;`
- L138 _public member_ `TSet<FName> ChildItems;`

#### enum `UContentBrowserFileDataSource::FDiscoveredItem::EType`  
`enum class EType : uint8`  
_L130-134_
- L132 _public enumerator_ `Directory`
- L133 _public enumerator_ `File`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONTENTBROWSERFILEDATASOURCE_API`
