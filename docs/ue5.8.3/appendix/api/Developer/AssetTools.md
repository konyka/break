# Developer / AssetTools

- module root: `Source/Developer/AssetTools`
- headers: 37; symbols: 1150
- symbol kinds: class=35, delegate=24, enum=14, enumerator=71, function=146, macro=10, member=175, namespace=10, prototype=639, struct=20, typedef=6
- DynamicallyLoadedModuleNames: ActorPickerMode, AnimationBlueprintEditor, AnimationEditor, AnimationModifiers, AudioEditor, CollectionManager, ContentBrowser, CurveTableEditor, DataTableEditor, DesktopPlatform, EditorWidgets, FontEditor, GameProjectGeneration, MainFrame, MessageLog, PackagesDialog, Persona, SkeletalMeshEditor, SkeletonEditor, VirtualTexturingEditor
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetRegistry, ClassViewer, DeveloperSettings, Engine, EngineSettings, Foliage, InputCore, InterchangeCore, InterchangeEngine, Kismet, Landscape, MaterialEditor, PhysicsCore, PhysicsUtilities, Projects, PropertyEditor, RHI, Slate, SourceControl, ToolMenus, ToolWidgets
- PrivateIncludePathModuleNames: Analytics, AnimationEditor, CollectionManager, ContentBrowser, DesktopPlatform, EditorWidgets, MainFrame, MessageLog, PackagesDialog, Persona, VirtualTexturingEditor
- PublicDependencyModuleNames: Core, CoreUObject, EditorFramework, SlateCore, UnrealEd
- PublicIncludePathModuleNames: AssetDefinition, Merge, UnrealEd

### `Source/Developer/AssetTools/Internal/AssetHeaderPatcher.h` (Internal)


#### struct `FAssetHeaderPatcher`  
`UE_INTERNAL struct FAssetHeaderPatcher`  
_L20-278_
- L22 _public member_ `static const EUnrealEngineObjectUE5Version MinimumSupportedUE5FileVersion = EUnrealEngineObjectUE5Version::ADD_SOFTOBJECTPATH_LIST;`
- L136 _public prototype_ `FAssetHeaderPatcher() = default;`
- L137 _public function_ `FAssetHeaderPatcher(const FContext& InContext)`
- L143 _public prototype_ `void SetContext(const FContext& InContext);` — Resets the patcher state and sets a new patching context. It is an error to call while patching is already in progress.
- L176 _public prototype_ `UE::Tasks::FTask PatchAsync(const FPatchAsyncParams& Params = {});` — Schedules the reading of source files determined by the patcher context, as well as the writing of the patched versions of all source files read.
- L182 _public function_ `EResult GetPatchResult() const` — Returns the status of any inflight patching operations. In the case of multiple errors, the last seen error will be reported. Per file error status codes can be returned with GetErrorFiles().
- L190 _public function_ `TMap<FString, FString> GetPatchedFiles() const` — Returns source file -> destination mapping for all files that were patched successfully.
- L203 _public function_ `bool HasErrors()` — Returns true if the patcher encountered errors (even if patching was cancelled)
- L212 _public function_ `TMap<FString, EResult> GetErrorFiles()` — Returns a map of all files that had an error during patching with an error code to provide context as to the cause of the error.
- L221 _public function_ `bool IsPatching() const` — Returns true if the patcher is still in theprocess of patching.
- L233 _public function_ `bool CancelPatching()` — Cancels an in-flight patching operation. Patching work on individual files that has already started will run to completion however any files that have not started patching will be skipped. Even after cancelling, one must wait for the patcher to complete by waiting on the GetPatchingTask() explciitly or until IsPatching returns false. @return true if an in-flight patching operation was cancelled. If no patching operation is underway, returns false.
- L249 _public function_ `UE::Tasks::FTask GetPatchingTask() const` — Returns the task for all patcher work underway. Waiting on this task will guarantee all patch work is completed.
- L263 _public prototype_ `static EResult DoPatch(const FString& InSrcAsset, const FString& InDstAsset, const FContext& InContext);` — Patches object and package references contained within InSrcAsset using the mapping provided to InContext. The patched asset will be written to InDstAsset. @param InSrcAsset Long package name (/Root/Folder/Package) to read in to be patched. @param InDstAsset Long package name (/Root/Folder/Package) where the patched package will be written to. @param InContext Context for how the patching will be performed. Contains all remapping information to the patcher. @return Success patching was successful and the InDstAsset package was written. Returns an error status otherwise.
- L266 _private prototype_ `void Reset();`
- L268 _private member_ `FContext Context;`
- L270 _private member_ `TMap<FString, EResult> ErroredFiles;`
- L271 _private member_ `FCriticalSection ErroredFilesLock;`
- L273 _private member_ `TMap<FString, FString> PatchedFiles;`
- L275 _private member_ `UE::Tasks::FTask PatchingTask;`
- L276 _private member_ `EResult Status = EResult::NotStarted;`
- L277 _private member_ `std::atomic<bool> bCancelled = false;`

#### enum `FAssetHeaderPatcher::EResult`  
`enum class EResult`  
_L24-38_
- L26 _public enumerator_ `NotStarted`
- L27 _public enumerator_ `Cancelled`
- L28 _public enumerator_ `InProgress`
- L29 _public enumerator_ `Success`
- L30 _public enumerator_ `ErrorFailedToLoadSourceAsset`
- L31 _public enumerator_ `ErrorFailedToDeserializeSourceAsset`
- L32 _public enumerator_ `ErrorUnexpectedSectionOrder`
- L33 _public enumerator_ `ErrorBadOffset`
- L34 _public enumerator_ `ErrorUnkownSection`
- L35 _public enumerator_ `ErrorFailedToOpenDestinationFile`
- L36 _public enumerator_ `ErrorFailedToWriteToDestinationFile`
- L37 _public enumerator_ `ErrorEmptyRequireSection`

#### struct `FAssetHeaderPatcher::FContext`  
`UE_INTERNAL struct FContext`  
_L40-134_
- L42 _public prototype_ `FContext() = default;`
- L62 _public prototype_ `FContext( const TMap<FString, FString>& InSrcAndDstPackagePaths, const bool bInGatherDependentPackages = true, const TArray<FString>* InSrcPackagePathsToPatch = nullptr);` — Context used for patching. Contains all information for how object and package references will be changed as part of patching. * When bInGatherDependentPackages is true, the provided long package name (/Root/Folder/Package) to destination long package name mapping will be used to find any dependent packages that must also be patched due to internal references. The mapping provided in InSrcAndDstPackagePaths will be used to determine the filepath on disk to write when patching. @param	InSrcAndDstPackagePaths Map of all long package names (/Root/Folder/Package) that are patchable and to which new name they should be patched to. Note, this should be all possible remappings so that references to unpatched assets may still be corrected when patching assets. If a subset of packages should be written to disk during patching, pass that list in InSrcPackagePathsToPatch. @param	bInGatherDependentPackages If true (default), upon creating the context GatherDependentPackages() will be called. @param	InSrcPackagePathsToPatch Optional. List of long package names (/Root/Folder/Package) to be patched on disk. This set of package names must be a subset or complete set of the keys in InSrcAndDstPackagePaths. If not provided, the keys in InSrcAndDstPackagePaths will be used instead.
- L89 _public prototype_ `FContext( const FString& InSrcRoot, const FString& InDstRoot, const FString& InSrcBaseDir, const FString& InDstBaseDir, const TMap<FString, FString>& InSrcAndDstFilePathsForRemapping, const TMap<FString, FString>& InMountPointReplacements, const TArray<FString>* InSrcFilePathsToPatch = nullptr);` — Context used for patching. Contains all information for how object and package references will be changed as part of patching. When patching, package paths to patch will be deduced by the filepath mappings provided in InSrcAndDstFilePathsForRemapping. All assets under InSrcRoot will be written as package paths under a mountpoint located at InSrcBaseDir. e.g. Path "C:/User/Repo/Project/Content/Skeletons/Player.uasset" -> "/InSrcRoot/Skeletons/Player" when InSrcBaseDir=C:/User/Repo/Project (/Content is assumed internally) @param	InSrcRoot The root mount point for assets to be patched @param	InDstRoot The new root mount point for patched assets to be placed under @param	InSrcBaseDir Path to the directory holding the /Content/ directory for assets to patch @param	InSrcAndDstFilePathsForRemapping Map of filepaths of all files possible to be patched and where to write the patched version to. Note, this should be all possible remappings so that references to unpatched assets may still be corrected when patching assets. If a subset of files should be written to disk during patching, pass that list in InSrcFilePathsToPatch. @param	InMountPointReplacements Map of root mountpoints (name only, no "/" prefix or suffix) to replace when patching @param	InSrcFilePathsToPatch Optional. List of filepaths for the files to be patched on disk. This set of files must be a subset or complete set of the keys in InSrcAndDstFilePathsForRemapping. If not provided the keys in InSrcAndDstFilePathsForRema
- L104 _public function_ `const TMap<FString, FString>& GetLongPackagePathRemapping() const` — Returns the mapping of source long package names to destination package paths used when patching. This mapping may include more packages than initially supplied to the FContext if GatherDependentPackages has already been called. Note, this map can be invalidated by calls to GatherDependentPackages()
- L112 _protected prototype_ `void AddVerseMounts();`
- L113 _protected prototype_ `void GatherDependentPackages();`
- L114 _protected prototype_ `void GenerateFilePathsFromPackagePaths(const TArray<FString>* InFilePathsToPatch = nullptr);`
- L115 _protected prototype_ `void GeneratePackagePathsFromFilePaths(const FString& InSrcRoot, const FString& InDstRoot, const FString& InSrcBaseDir, const FString& InDstBaseDir);`
- L116 _protected prototype_ `void GenerateAdditionalRemappings();`
- L118 _protected member_ `TArray<FString> VerseMountPoints;`
- L120 _protected member_ `TMap<FString, FString> PackagePathRenameMap;` — PackagePath remapping information to use while patching
- L122 _protected member_ `TMap<FString, FString> FilePathRenameMap;` — FilePath remapping information to use while patching
- L124 _protected member_ `TMap<FString, FString> FilePathsToPatchMap;` — Map of Src -> Dst for files on disk to patch
- L127 _protected member_ `TArray<FCoreRedirect> Redirects;` — Todo: Make TSet once FCoreRedirect GetTypeHash is implemented
- L128 _protected member_ `mutable FCoreRedirectsContext RedirectsContext;`
- L132 _protected member_ `TMap<FString, FString> VerseStringReplacements;` — String mappings are only used for best-effort replacements. These will be error-prone and we should strive for more structured data formats to guard against errors here
- L133 _protected member_ `TMap<FString, FString> StringMountReplacements;`

#### struct `FAssetHeaderPatcher::FPatchAsyncParams`  
`struct FPatchAsyncParams`  
_L148-170_
- desc: PatchAsync optional parameters
- L151 _public member_ `int32* OutNumFilesToPatch;` — Optional value to know how many files are expected to be read/written during patching
- L154 _public member_ `int32* OutNumFilesPatched;` — Optional value used to know how the patcher is progressing (useful for progress bars)
- L157 _public member_ `FAssetHeaderPatcherCompletionDelegate OnSuccess;` — Thread-safe delegate invoked for each successful file copy
- L160 _public member_ `FAssetHeaderPatcherCompletionDelegate OnError;` — Thread-safe delegate invoked for each failed file copy
- L163 _public member_ `UE::Tasks::ETaskPriority TaskPriority;` — Task priority
- L165 _public function_ `FPatchAsyncParams() : OutNumFilesToPatch(nullptr) , OutNumFilesPatched(nullptr) , TaskPriority(UE::Tasks::ETaskPriority::Default)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ASSETTOOLS_API`
- L17 _delegate_ `DECLARE_DELEGATE_TwoParams(FAssetHeaderPatcherCompletionDelegate, const FString& , const FString& ) UE_INTERNAL struct FAssetHeaderPatcher { static const EUnrealEngineObjectUE5Version MinimumSupportedUE5FileVersion = EUnrealEngineObjectUE5Version::ADD_SOFTOBJECTPATH_LIST; enum class EResult { NotStarted, Cancelled, InProgress, Success, ErrorFailedToLoadSourceAsset, ErrorFailedToDeserializeSourceAsset, ErrorUnexpectedSectionOrder, ErrorBadOffset, ErrorUnkownSection, ErrorFailedToOpenDestinationFile, ErrorFailedToWriteToDestinationFile, ErrorEmptyRequireSection, }; UE_INTERNAL struct FContext { FContext() = default; /** * Context used for patching. Contains all information for how object and package references * will be changed as part of patching. * * * When bInGatherDependentPackages is true, the provided long package name (/Root/Folder/Package) to * destination long package name mapping will be used to find any dependent packages that must also * be patched due to internal references. The mapping provided in InSrcAndDstPackagePaths will be used * to determine the filepath on disk to write when patching. * * @param InSrcAndDstPackagePaths Map of all long package names (/Root/Folder/Package) that are patchable and to which new name they should be patched to. Note, this should be all possible remappings so that references to unpatched assets may still be corrected when patching assets. If a subset of packages should be written to disk during patching, pass that list in InSrcPac` — Delegate called on when patch operation completes @param	SrcFilePath		Path of file being read for patching @param	DstFilePath		Path of file being written to after patching
- L279 _prototype_ `UE_INTERNAL FString LexToString(FAssetHeaderPatcher::EResult InResult);`

### `Source/Developer/AssetTools/Private/AssetDefinition_AssetTypeActionsProxy.h` (Private)


#### class `UAssetDefinition_AssetTypeActionsProxy`  
`class UAssetDefinition_AssetTypeActionsProxy : public UAssetDefinitionDefault`  
_L12-64_
- reflection: `UCLASS(transient)`
- inherits: `UAssetDefinitionDefault`
- L16 _public function_ `UAssetDefinition_AssetTypeActionsProxy()`
- L18 _public prototype_ `void Initialize(const TSharedRef<IAssetTypeActions>& NewActions);`
- L20 _public function_ `const TSharedPtr<IAssetTypeActions>& GetAssetType() const`
- L22 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L23 _public prototype_ `virtual FText GetAssetDisplayName(const FAssetData& InAssetData) const override;`
- L24 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L25 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L26 _public prototype_ `virtual FText GetAssetDescription(const FAssetData& InAssetData) const override;`
- L27 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L29 _public prototype_ `virtual FAssetSupportResponse CanRename(const FAssetData& InAsset) const override;`
- L30 _public prototype_ `virtual FAssetSupportResponse CanDuplicate(const FAssetData& InAsset) const override;`
- L31 _public prototype_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const override;`
- L32 _public prototype_ `virtual bool CanImport() const override;`
- L33 _public prototype_ `virtual bool CanMerge() const override;`
- L34 _public prototype_ `virtual EAssetCommandResult Merge(const FAssetAutomaticMergeArgs& MergeArgs) const override;`
- L35 _public prototype_ `virtual EAssetCommandResult Merge(const FAssetManualMergeArgs& MergeArgs) const override;`
- L37 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`
- L38 _public prototype_ `virtual TArray<FAssetData> PrepareToActivateAssets(const FAssetActivateArgs& ActivateArgs) const override;`
- L39 _public prototype_ `virtual EAssetCommandResult ActivateAssets(const FAssetActivateArgs& ActivateArgs) const override;`
- L40 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L42 _public prototype_ `virtual void BuildFilters(TArray<FAssetFilterData>& OutFilters) const override;`
- L47 _public prototype_ `virtual FText GetObjectDisplayNameText(UObject* Object) const override;`
- L48 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`
- L50 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& Asset) const override;`
- L51 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L52 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L53 _public prototype_ `virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& InAssetData) const override;`
- L54 _public prototype_ `virtual bool GetThumbnailActionOverlay(const FAssetData& InAssetData, FAssetActionThumbnailOverlayInfo& OutActionOverlayInfo) const override;`
- L57 _protected function_ `virtual bool CanRegisterStatically() const override`
- L60 _private member_ `TSharedPtr<IAssetTypeActions> AssetType;`
- L62 _private member_ `mutable bool bAreAssetCategoriesInitialized = false;`
- L63 _private member_ `mutable TArray<FAssetCategoryPath> AssetCategories;`

### `Source/Developer/AssetTools/Private/AssetFixUpRedirectors.h` (Private)


#### class `FAssetFixUpRedirectors`  
`class FAssetFixUpRedirectors : public TSharedFromThis<FAssetFixUpRedirectors>`  
_L10-30_
- inherits: `TSharedFromThis<FAssetFixUpRedirectors>`
- L17 _public prototype_ `void FixupReferencers(const TArray<UObjectRedirector*>& Objects, bool bCheckoutDialogPrompt, ERedirectFixupMode FixupMode) const;` — Fix up references to the specified redirectors. @param bCheckoutDialogPrompt indicates whether to prompt the user with files checkout dialog or silently attempt to checkout all necessary files.
- L20 _public function_ `bool IsFixupReferencersInProgress() const` — Returns whether redirectors are being fixed up.
- L25 _private prototype_ `void ExecuteFixUp(TArray<TWeakObjectPtr<UObjectRedirector>> Objects, bool bCheckoutDialogPrompt, ERedirectFixupMode FixupMode) const;` — The core code of the fixup operation
- L29 _private member_ `mutable bool bIsFixupReferencersInProgress = false;`

### `Source/Developer/AssetTools/Private/AssetRenameManager.h` (Private)


#### struct `FCachedSoftReference`  
`struct FCachedSoftReference`  
_L11-18_
- L14 _public member_ `TMap<FSoftObjectPath, TSet<FWeakObjectPtr>> Map;` — Insert friendly
- L17 _public member_ `TArray<FSoftObjectPath> Keys;` — So we can binary search for the TMap keys

#### class `FAssetRenameManager`  
`class FAssetRenameManager : public TSharedFromThis<FAssetRenameManager>`  
_L29-147_
- inherits: `TSharedFromThis<FAssetRenameManager>`
- desc: The manager to handle renaming assets. This manager attempts to fix up references in memory if possible and only leaves UObjectRedirectors when needed. Redirectors are left unless ALL of the following are true about the asset 1) The asset has not yet been checked into source control. This does not apply when source control is disabled. 2) The user is able and willing to check out all uasset files that directly reference the asset from source control. The files must be at head revision and not checked out by another user. This rule does not apply when source control is disabled. 3) No maps reference the asset directly. 4) All uasset files that directly reference the asset are writable on disk.
- L33 _public prototype_ `bool RenameAssets(const TArray<FAssetRenameData>& AssetsAndNames) const;` — Renames assets using the specified names.
- L36 _public prototype_ `EAssetRenameResult RenameAssetsWithDialog(const TArray<FAssetRenameData>& AssetsAndNames, bool bAutoCheckout = false) const;` — Renames assets using the specified names.
- L39 _public prototype_ `void FindSoftReferencesToObject(FSoftObjectPath TargetObject, TArray<UObject*>& ReferencingObjects) const;` — Returns list of objects that soft reference the given soft object path. This will load assets into memory to verify
- L42 _public prototype_ `void FindSoftReferencesToObjects(const TArray<FSoftObjectPath>& TargetObjects, TMap<FSoftObjectPath, TArray<UObject*>>& ReferencingObjects) const;` — Returns list of objects that soft reference the given soft object paths. This will load assets into memory to verify
- L45 _public function_ `FAssetPostRenameEvent& OnAssetPostRenameEvent()` — Accessor for post rename event
- L53 _public prototype_ `void RenameReferencingSoftObjectPaths(TArray<UPackage*> PackagesToCheck, const TMap<FSoftObjectPath, FSoftObjectPath>& AssetRedirectorMap) const;` — Function that renames all FSoftObjectPath object with the old asset path to the new one. @param PackagesToCheck Packages to check for referencing FSoftObjectPath. @param AssetRedirectorMap Map from old asset path to new asset path
- L56 _public prototype_ `bool CheckPackageForSoftObjectReferences(UPackage* Package, const TMap<FSoftObjectPath, FSoftObjectPath>& AssetRedirectorMap, TArray<UObject*>& OutReferencingObjects) const;` — Filters packages list depending on if it actually has soft object paths pointing to the specific object being renamed
- L59 _public prototype_ `bool CheckPackageForSoftObjectReferences(UPackage* Package, const TMap<FSoftObjectPath, FSoftObjectPath>& AssetRedirectorMap, TMap<FSoftObjectPath, TArray<UObject*>>& OutReferencingObjects) const;` — Filters packages list depending on if it actually has soft object paths pointing to the specific object being renamed
- L63 _private prototype_ `void RenameAssetsAndVariantsCallback(TArray<FAssetRenameData> InAssetsRenameData, bool bAutoCheckout, bool bWithDialog) const;` — Callback used by DiscoverintAssetsDialog to call RenameAssetsAndVariants
- L66 _private prototype_ `bool RenameAssetsAndVariants(const TArray<FAssetRenameData>& InAssetsRenameData, bool bAutoCheckout, bool bWithDialog) const;` — Check if renaming these assets should also rename localized variants assets (or source asset)
- L69 _private prototype_ `bool FixReferencesAndRename(const TArray<FAssetRenameData>& AssetsAndNames, bool bAutoCheckout, bool bWithDialog, FScopedSlowTask& RenamingSlowTask) const;` — Attempts to load and fix redirector references for the supplied assets
- L78 _private prototype_ `void FindCDOReferences(const TArrayView<FAssetRenameDataWithReferencers>& AssetsToRename, TArray<FAssetRenameDataWithReferencers*>& OutHardReferences, TArray<FAssetRenameDataWithReferencers*>& OutSoftReferences, bool bSetRedirectorFlags) const;` — Get lists of assets with references from CDOs @param AssetsToRename      List of assets to be renamed @param OutReferences       Output array of hard asset references @param OutSoftReferences   Output array of soft path asset references @param bSetRedirectorFlags If true, each renamed asset with a soft reference will be marked as needing a redirector
- L81 _private prototype_ `void PopulateAssetReferencers(TArray<FAssetRenameDataWithReferencers>& AssetsToPopulate) const;` — Fills out the Referencing packages for all the assets described in AssetsToPopulate
- L84 _private prototype_ `bool UpdatePackageStatus(TArray<FAssetRenameDataWithReferencers>& AssetsToRename) const;` — Updates the source control status of the packages containing the assets to rename
- L92 _private prototype_ `void LoadReferencingPackages(TArray<FAssetRenameDataWithReferencers>& AssetsToRename, bool bLoadAllPackages, bool bCheckStatus, TArray<UPackage*>& OutReferencingPackagesToSave, TArray<UObject*>& OutSoftReferencingObjects) const;` — Loads all referencing packages to assets in AssetsToRename, finds assets whose references can not be fixed up to mark that a redirector should be left, and returns a list of referencing packages to save. If bLoadAllPackages is true, it will load all referencing packages even if they can't be checked out If bCheckStatus is true it will check the source control status
- L95 _private prototype_ `void GatherReferencingObjects(TArray<FAssetRenameDataWithReferencers>& AssetsToRename, TMap<FSoftObjectPath, TArray<UObject*>>& OutSoftReferencingObjects) const;` — Gather a list of referencing object for each of the asset in AssetsToRename. Will load all referencing packages
- L102 _private prototype_ `bool CheckOutPackages(TArray<FAssetRenameDataWithReferencers>& AssetsToRename, TArray<UPackage*>& InOutReferencingPackagesToSave, bool bAutoCheckout) const;` — Prompts to check out the source package and all referencing packages and marks assets whose referencing packages were not checked out to leave a redirector. Trims PackagesToSave when necessary. Returns true if the user opted to continue the operation or no dialog was required.
- L105 _private prototype_ `bool AutoCheckOut(TArray<UPackage*>& PackagesToCheckOut) const;` — Attempts to check out packages, returns false on any failure
- L108 _private prototype_ `void DetectReferencingCollections(TArray<FAssetRenameDataWithReferencers>& AssetsToRename) const;` — Finds any collections that are referencing the assets to be renamed. Assets referenced by collections will leave redirectors
- L111 _private prototype_ `void DetectReadOnlyPackages(TArray<FAssetRenameDataWithReferencers>& AssetsToRename, TArray<UPackage*>& InOutReferencingPackagesToSave) const;` — Finds any read only packages and removes them from the save list. Assets referenced by these packages will leave redirectors.
- L118 _private prototype_ `void SetupPublicAssets(TArray<FAssetRenameDataWithReferencers>& AssetsToRename) const;` — Make public any private asset that will be referenced from another plugin after the rename. If the asset cannot be made public or if moving it requires a referenced asset that's not being modified to become public, its rename will fail and other assets that have dependencies between them will also fail to be renamed.
- L121 _private prototype_ `void PerformAssetRename(TArray<FAssetRenameDataWithReferencers>& AssetsToRename, FScopedSlowTask& RenamingSlowTask) const;` — Performs the asset rename after the user has selected to proceed
- L124 _private prototype_ `void PerformAssetRename(TArray<FAssetRenameDataWithReferencers>& AssetsToRename, const TArray<UPackage*>& ReferencingPackagesToSave, FScopedSlowTask& RenamingSlowTask) const;` — Performs the asset rename after the user has selected to proceed, also saving the provided referencing packages at the same time
- L127 _private prototype_ `void SaveReferencingPackages(const TArray<UPackage*>& ReferencingPackagesToSave) const;` — Saves all the referencing packages and updates SCC state
- L130 _private prototype_ `void RenameInterrupted(const TArray<FAssetRenameData>& AssetsToRename, const FText& InterruptionReason, bool bWithDialog) const;` — Prematurely interrupt the rename process for the given reason
- L133 _private prototype_ `int32 ReportFailures(const TArray<FAssetRenameDataWithReferencers>& AssetsToRename, bool bWithDialog) const;` — Report any failures that may have happened during the rename. Return the number of failures
- L136 _private prototype_ `bool RequiresCheckingForVariants(const TArray<FAssetRenameData>& InAssetsToRename, TArray<FAssetRenameData>& OutAssetsAndVariants, TArray<FAssetRenameData>& OutAssetsToCheckForVariants) const;` — Internal check to know if we should look for localized variants
- L139 _private prototype_ `void OnMarkPackageDirty(UPackage* Pkg, bool bWasDirty);` — Called when a package is dirtied, clears the cache
- L142 _private member_ `FAssetPostRenameEvent AssetPostRenameEvent;` — Event issued at the end of the rename process
- L145 _private member_ `mutable TMap<FName, FCachedSoftReference> CachedSoftReferences;` — Cache of package->soft references, to avoid serializing the same package over and over
- L146 _private member_ `mutable FDelegateHandle DirtyDelegateHandle;`

### `Source/Developer/AssetTools/Private/AssetTools.h` (Private)


#### struct `FAssetImportParams`  
`struct FAssetImportParams`  
_L23-52_
- desc: Parameters for importing specific set of files
- L25 _public function_ `FAssetImportParams() : SpecifiedFactory(nullptr) , ImportData(nullptr) , AssetImportTask(nullptr) , bSyncToBrowser(true) , bForceOverrideExisting(false) , bAutomated(false) , bAllowAsyncImport(false) , bSceneImport(false)`
- L37 _public member_ `TStrongObjectPtr<UFactory> SpecifiedFactory;` — Factory to use for importing files
- L39 _public member_ `const UAutomatedAssetImportData* ImportData;` — Data used to determine rules for importing assets through the automated command line interface
- L41 _public member_ `UAssetImportTask* AssetImportTask;` — Script exposed rules and state for importing assets
- L43 _public member_ `bool bSyncToBrowser : 1;` — Whether or not to sync the content browser to the assets after import
- L45 _public member_ `bool bForceOverrideExisting : 1;` — Whether or not we are forcing existing assets to be overriden without asking
- L47 _public member_ `bool bAutomated : 1;` — Whether or not this is an automated import
- L49 _public member_ `bool bAllowAsyncImport : 1;` — Temporary setting to enable the async import. (We will figure a better solution in a later release)
- L51 _public member_ `bool bSceneImport : 1;` — Whether or not this is a scene import

#### class `UAssetToolsImpl`  
`class UAssetToolsImpl : public UObject, public IAssetTools`  
_L61-336_
- reflection: `UCLASS(transient)`
- inherits: `UObject,IAssetTools`
- L66 _public prototype_ `UAssetToolsImpl(const FObjectInitializer& ObjectInitializer);`
- L69 _public prototype_ `virtual void RegisterAssetTypeActions(const TSharedRef<IAssetTypeActions>& NewActions) override;` — IAssetTools implementation
- L70 _public prototype_ `virtual void UnregisterAssetTypeActions(const TSharedRef<IAssetTypeActions>& ActionsToRemove) override;`
- L71 _public prototype_ `virtual void GetAssetTypeActionsList( TArray<TWeakPtr<IAssetTypeActions>>& OutAssetTypeActionsList ) const override;`
- L72 _public prototype_ `virtual TWeakPtr<IAssetTypeActions> GetAssetTypeActionsForClass(const UClass* Class) const override;`
- L74 _public prototype_ `virtual TSharedPtr<ILocalizedAssetTools> GetLocalizedAssetTools() const override;`
- L75 _public prototype_ `virtual bool CanLocalize(const UClass* Class) const override;`
- L77 _public prototype_ `virtual TOptional<FLinearColor> GetTypeColor(const UClass* Class) const override;`
- L79 _public prototype_ `virtual TArray<TWeakPtr<IAssetTypeActions>> GetAssetTypeActionsListForClass(const UClass* Class) const override;`
- L80 _public prototype_ `virtual EAssetTypeCategories::Type RegisterAdvancedAssetCategory(FName CategoryKey, FText CategoryDisplayName) override;`
- L81 _public prototype_ `virtual EAssetTypeCategories::Type FindAdvancedAssetCategory(FName CategoryKey) const override;`
- L82 _public prototype_ `virtual void GetAllAdvancedAssetCategories(TArray<FAdvancedAssetCategory>& OutCategoryList) const override;`
- L83 _public prototype_ `virtual void RegisterClassTypeActions(const TSharedRef<IClassTypeActions>& NewActions) override;`
- L84 _public prototype_ `virtual void UnregisterClassTypeActions(const TSharedRef<IClassTypeActions>& ActionsToRemove) override;`
- L85 _public prototype_ `virtual void GetClassTypeActionsList( TArray<TWeakPtr<IClassTypeActions>>& OutClassTypeActionsList ) const override;`
- L86 _public prototype_ `virtual TWeakPtr<IClassTypeActions> GetClassTypeActionsForClass( UClass* Class ) const override;`
- L87 _public prototype_ `virtual UObject* CreateAsset(const FString& AssetName, const FString& PackagePath, UClass* AssetClass, UFactory* Factory, FName CallingContext = NAME_None, bool bOverwriteExisting = false) override;`
- L88 _public prototype_ `virtual bool CreateAssetAsync(const FString& AssetName, const FString& PackagePath, UClass* AssetClass, UFactory* Factory, FAssetCreateComplete OnComplete = FAssetCreateComplete(), FAssetCreateCancelled OnCancelled = FAssetCreateCancelled(), FName CallingContext = NAME_None, bool bOverwriteExisting = false) override;`
- L89 _public prototype_ `virtual void CreateAssetsFrom(TConstArrayView<UObject*> SourceObjects, UClass* CreateAssetType, const FString& DefaultSuffix, TFunctionRef<UFactory*(UObject*)> FactoryConstructor, FName CallingContext) override;`
- L90 _public prototype_ `virtual UObject* CreateAssetWithDialog(UClass* AssetClass, UFactory* Factory, FName CallingContext = NAME_None) override;`
- L91 _public prototype_ `virtual UObject* CreateAssetWithDialog(const FString& AssetName, const FString& PackagePath, UClass* AssetClass, UFactory* Factory, FName CallingContext, const bool bCallConfigureProperties = true) override;`
- L92 _public prototype_ `virtual bool CreateAssetWithDialogAsync(const FString& AssetName, const FString& PackagePath, UClass* AssetClass, UFactory* Factory, FAssetCreateComplete OnComplete, FAssetCreateCancelled OnCancelled, FName CallingContext) override;`
- L93 _public prototype_ `virtual bool CreateAssetWithDialogAsync(UClass* AssetClass, UFactory* Factory, FAssetCreateComplete OnComplete = FAssetCreateComplete(), FAssetCreateCancelled OnCancelled = FAssetCreateCancelled(), FName CallingContext = NAME_None) override;`
- L94 _public prototype_ `virtual UObject* DuplicateAsset(const FString& AssetName, const FString& PackagePath, UObject* OriginalObject) override;`
- L95 _public prototype_ `virtual UObject* DuplicateAssetWithDialog(const FString& AssetName, const FString& PackagePath, UObject* OriginalObject) override;`
- L96 _public prototype_ `virtual UObject* DuplicateAssetWithDialogAndTitle(const FString& AssetName, const FString& PackagePath, UObject* OriginalObject, FText DialogTitle) override;`
- L97 _public prototype_ `virtual void SetCreateAssetsAsExternallyReferenceable(bool bValue) override;`
- L98 _public prototype_ `virtual bool GetCreateAssetsAsExternallyReferenceable() override;`
- L99 _public prototype_ `virtual bool ShouldCreateAssetsAsExternallyReferenceableForPath(const FStringView AssetPath) const override;`
- L100 _public prototype_ `virtual UE::AssetTools::FShouldCreateAssetsAsExternallyReferenceableForPath& GetOnShouldCreateAssetsAsExternallyReferenceableForPath() override;`
- L101 _public prototype_ `virtual bool IsDiscoveringAssetsInProgress() const override;`
- L102 _public prototype_ `virtual void OpenDiscoveringAssetsDialog(const FOnAssetsDiscovered& InOnAssetsDiscovered) override;`
- L103 _public prototype_ `virtual bool RenameAssets(const TArray<FAssetRenameData>& AssetsAndNames) override;`
- L104 _public prototype_ `virtual EAssetRenameResult RenameAssetsWithDialog(const TArray<FAssetRenameData>& AssetsAndNames, bool bAutoCheckout = false) override;`
- L105 _public prototype_ `virtual void FindSoftReferencesToObject(FSoftObjectPath TargetObject, TArray<UObject*>& ReferencingObjects) override;`
- L106 _public prototype_ `virtual void FindSoftReferencesToObjects(const TArray<FSoftObjectPath>& TargetObjects, TMap<FSoftObjectPath, TArray<UObject*>>& ReferencingObjects) override;`
- L107 _public prototype_ `virtual void RenameReferencingSoftObjectPaths(const TArray<UPackage *> PackagesToCheck, const TMap<FSoftObjectPath, FSoftObjectPath>& AssetRedirectorMap) override;`
- L108 _public prototype_ `virtual TArray<UObject*> ImportAssetsWithDialog(const FString& DestinationPath) override;`
- L109 _public prototype_ `virtual void ImportAssetsWithDialogAsync(const FString& DestinationPath) override;`
- L110 _public prototype_ `virtual TArray<UObject*> ImportAssets(const TArray<FString>& Files, const FString& DestinationPath, UFactory* ChosenFactory, bool bSyncToBrowser = true, TArray<TPair<FString, FString>>* FilesAndDestinations = nullptr, bool bAllowAsyncImport = false, bool bSceneImport = false) const override;`
- L111 _public prototype_ `virtual TArray<UObject*> ImportAssetsAutomated(const UAutomatedAssetImportData* ImportData) override;`
- L112 _public prototype_ `virtual void ImportAssetTasks(const TArray<UAssetImportTask*>& ImportTasks) override;`
- L113 _public prototype_ `virtual void ExportAssets(const TArray<FString>& AssetsToExport, const FString& ExportPath) override;`
- L114 _public prototype_ `virtual void ExportAssets(const TArray<UObject*>& AssetsToExport, const FString& ExportPath) const override;`
- L115 _public prototype_ `virtual void ExportAssetsWithCleanFilename(const TArray<UObject*>& AssetsToExport, const FString& ExportPath) const override;`
- L116 _public prototype_ `virtual void ExportAssetsWithDialog(const TArray<UObject*>& AssetsToExport, bool bPromptForIndividualFilenames) override;`
- L117 _public prototype_ `virtual void ExportAssetsWithDialog(const TArray<FString>& AssetsToExport, bool bPromptForIndividualFilenames) override;`
- L118 _public prototype_ `virtual bool CanExportAssets(const TArray<FAssetData>& AssetsToExport) const override;`
- L119 _public prototype_ `virtual void CreateUniqueAssetName(const FString& InBasePackageName, const FString& InSuffix, FString& OutPackageName, FString& OutAssetName) override;`
- L120 _public prototype_ `virtual bool AssetUsesGenericThumbnail( const FAssetData& AssetData ) const override;`
- L121 _public prototype_ `virtual void DiffAgainstDepot(UObject* InObject, const FString& InPackagePath, const FString& InPackageName) const override;`
- L122 _public prototype_ `virtual void DiffAssets(UObject* OldAsset1, UObject* NewAsset, const struct FRevisionInfo& OldRevision, const struct FRevisionInfo& NewRevision) const override;`
- L123 _public prototype_ `virtual FString DumpAssetToTempFile(UObject* Asset) const override;`
- L124 _public prototype_ `virtual bool CreateDiffProcess(const FString& DiffCommand, const FString& OldTextFilename, const FString& NewTextFilename, const FString& DiffArgs = FString("")) const override;`
- L125 _public prototype_ `virtual void MigratePackages(const TArray<FName>& PackageNamesToMigrate) const override;`
- L126 _public prototype_ `virtual void MigratePackages(const TArray<FName>& PackageNamesToMigrate, const FString& TargetPath, const struct FMigrationOptions& Options = FMigrationOptions()) const override;`
- L127 _public prototype_ `virtual void MigratePackages(const TArray<FName>& PackageNamesToMigrate, const FString& TargetPath, TSet<FName> AllDependenciesToMigrate, TSet<FName> ExcludedDependencies, const struct FMigrationOptions& Options = FMigrationOptions()) const override;`
- L128 _public prototype_ `virtual void BuildMigrateDependencies(const TArray<FName>& PackageNamesToMigrate, TSet<FName>& OutAllDependenciesToMigrate, TSet<FName>& OutExcludedDependencies) const override;`
- L129 _public prototype_ `virtual UE::AssetTools::FOnPackageMigration& GetOnPackageMigration() override;`
- L130 _public prototype_ `virtual void BeginAdvancedCopyPackages(const TArray<FName>& InputNamesToCopy, const FString& TargetPath) const override;`
- L131 _public prototype_ `virtual void BeginAdvancedCopyPackages(const TArray<FName>& InputNamesToCopy, const FString& TargetPath, const FAdvancedCopyCompletedEvent& OnCopyComplete) const override;`
- L132 _public prototype_ `virtual void FixupReferencers(const TArray<UObjectRedirector*>& Objects, bool bCheckoutDialogPrompt = true, ERedirectFixupMode FixupMode = ERedirectFixupMode::DeleteFixedUpRedirectors) const override;`
- L133 _public prototype_ `virtual bool IsFixupReferencersInProgress() const override;`
- L134 _public function_ `virtual FAssetPostRenameEvent& OnAssetPostRename() override`
- L135 _public prototype_ `virtual void ExpandDirectories(const TArray<FString>& Files, const FString& DestinationPath, TArray<TPair<FString, FString>>& FilesAndDestinations) const override;`
- L136 _public prototype_ `virtual bool AdvancedCopyPackages(const FAdvancedCopyParams& CopyParams, const TArray<TMap<FString, FString>>& PackagesAndDestinations) const override;`
- L137 _public prototype_ `virtual bool AdvancedCopyPackages(const TMap<FString, FString>& SourceAndDestPackages, const bool bForceAutosave, const bool bCopyOverAllDestinationOverlaps, FDuplicatedObjects* OutDuplicatedObjects, EMessageSeverity::Type NotificationSeverityFilter) const override;`
- L138 _public prototype_ `virtual void GenerateAdvancedCopyDestinations(FAdvancedCopyParams& InParams, const TArray<FName>& InPackageNamesToCopy, const class UAdvancedCopyCustomization* CopyCustomization, TMap<FString, FString>& OutPackagesAndDestinations) const override;`
- L139 _public prototype_ `virtual bool FlattenAdvancedCopyDestinations(const TArray<TMap<FString, FString>>& PackagesAndDestinations, TMap<FString, FString>& FlattenedPackagesAndDestinations) const override;`
- L140 _public prototype_ `virtual bool ValidateFlattenedAdvancedCopyDestinations(const TMap<FString, FString>& FlattenedPackagesAndDestinations) const override;`
- L141 _public prototype_ `virtual void GetAllAdvancedCopySources(FName SelectedPackage, FAdvancedCopyParams& CopyParams, TArray<FName>& OutPackageNamesToCopy, TMap<FName, FName>& DependencyMap, const class UAdvancedCopyCustomization* CopyCustomization) const override;`
- L142 _public prototype_ `virtual void InitAdvancedCopyFromCopyParams(FAdvancedCopyParams CopyParams) const override;`
- L143 _public prototype_ `virtual void OpenEditorForAssets(const TArray<UObject*>& Assets) override;`
- L144 _public prototype_ `virtual void ConvertVirtualTextures(const TArray<UTexture2D*>& Textures, bool bConvertBackToNonVirtual, const TArray<UMaterial*>* RelatedMaterials = nullptr) const override;`
- L145 _public prototype_ `virtual bool IsAssetClassSupported(const UClass* AssetClass) const override;`
- L146 _public prototype_ `virtual TArray<UFactory*> GetNewAssetFactories() const override;`
- L147 _public prototype_ `virtual const TSharedRef<FPathPermissionList>& GetAssetClassPathPermissionList(EAssetClassAction AssetClassAction) const override;`
- L148 _public prototype_ `virtual const TSharedRef<FNamePermissionList>& GetImportExtensionPermissionList() const override;`
- L149 _public prototype_ `virtual bool IsImportExtensionAllowed(const FStringView& Extension) const override;`
- L150 _public prototype_ `virtual TSet<EBlueprintType>& GetAllowedBlueprintTypes() override;`
- L151 _public prototype_ `virtual TSharedRef<FPathPermissionList>& GetFolderPermissionList() override;`
- L152 _public prototype_ `virtual TSharedRef<FPathPermissionList>& GetWritableFolderPermissionList() override;`
- L153 _public prototype_ `virtual bool IsAssetVisible(const FAssetData& AssetData, bool bCheckAliases = true) const override;`
- L154 _public prototype_ `virtual bool IsAssetReadOnly(const FAssetData& AssetData) const override;`
- L155 _public prototype_ `virtual FAssetData FindAssetByVersePath(const UE::Core::FVersePath& VersePath, bool bIncludeOnlyOnDiskAssets = false, bool bSkipARFilteredAssets = true) const override;`
- L156 _public prototype_ `virtual bool ShowingContentVersePath() const override;`
- L157 _public prototype_ `virtual UE::AssetTools::FShowingContentVersePath& GetOnShowingContentVersePath() override;`
- L158 _public prototype_ `virtual const FString& GetUserFacingPluginName(const IPlugin& Plugin) const override;`
- L159 _public prototype_ `virtual FString GetUserFacingPluginName(FStringView PluginName) const override;`
- L160 _public prototype_ `virtual FString GetUserFacingLongPackagePath(FStringView LongPackagePath) const override;`
- L161 _public prototype_ `virtual FString GetUserFacingLongPackageName(FName PackageName) const override;`
- L162 _public prototype_ `virtual TArray<FString> GetUserFacingLongPackageNames(TConstArrayView<FName> PackageNames) const override;`
- L163 _public prototype_ `virtual FString GetUserFacingObjectPath(const FSoftObjectPath& ObjectPath) const override;`
- L164 _public prototype_ `virtual TArray<FString> GetUserFacingObjectPaths(TConstArrayView<FSoftObjectPath> ObjectPaths) const override;`
- L165 _public prototype_ `virtual FString GetUserFacingLongPackageName(const UPackage& Package) const override;`
- L166 _public prototype_ `virtual TArray<FString> GetUserFacingLongPackageNames(TConstArrayView<const UPackage*> Packages) const override;`
- L167 _public prototype_ `virtual FString GetUserFacingFullName(const UObject& Object) const override;`
- L168 _public prototype_ `virtual FString GetUserFacingPathName(const UObject& Object) const override;`
- L169 _public prototype_ `virtual FString GetUserFacingFullName(const FAssetData& AssetData) const override;`
- L170 _public prototype_ `virtual FString GetUserFacingPathName(const FAssetData& AssetData) const override;`
- L171 _public prototype_ `virtual bool AllPassWritableFolderFilter(const TArray<FString>& InPaths) const override;`
- L172 _public prototype_ `virtual void NotifyBlockedByWritableFolderFilter() const;`
- L173 _public prototype_ `virtual bool IsNameAllowed(const FString& Name, FText* OutErrorMessage = nullptr) const override;`
- L174 _public prototype_ `virtual void RegisterIsNameAllowedDelegate(const FName OwnerName, FIsNameAllowed Delegate) override;`
- L175 _public prototype_ `virtual void UnregisterIsNameAllowedDelegate(const FName OwnerName) override;`
- L176 _public prototype_ `virtual bool IsObjectPathAllowed(const FString& FullPathWithName, FText* OutErrorMessage = nullptr) const override;`
- L177 _public prototype_ `virtual void RegisterIsObjectPathAllowedDelegate(const FName OwnerName, FIsObjectPathAllowed Delegate) override;`
- L178 _public prototype_ `virtual void UnregisterIsObjectPathAllowedDelegate(const FName OwnerName) override;`
- L179 _public prototype_ `virtual bool SanitizeName(FString& NameToSanitize) override;`
- L180 _public prototype_ `virtual void RegisterSanitizeNameDelegate(const FName OwnerName, FSanitizeName Delegate) override;`
- L181 _public prototype_ `virtual void UnregisterSanitizeNameDelegate(const FName OwnerName) override;`
- L182 _public prototype_ `virtual TOptional<FString> GetDefaultAssetNameForClass(const UClass* Class, const UFactory* Factory, const UObject* SourceObject) override;`
- L183 _public prototype_ `virtual void RegisterDefaultAssetNameForClass(const UClass* Class, const FString& DefaultName) override;`
- L184 _public prototype_ `virtual void UnregisterDefaultAssetNameForClass(const UClass* Class) override;`
- L185 _public prototype_ `virtual void RegisterCanMigrateAsset(const FName OwnerName, UE::AssetTools::FCanMigrateAsset Delegate) override;`
- L186 _public prototype_ `virtual void UnregisterCanMigrateAsset(const FName OwnerName) override;`
- L187 _public prototype_ `virtual bool CanAssetBePublic(FStringView AssetPath, FText* DisallowReason = nullptr) const override;`
- L188 _public prototype_ `virtual void RegisterCanAssetBePublic(const FName OwnerName, UE::AssetTools::FCanAssetBePublic Delegate) override;`
- L189 _public prototype_ `virtual void UnregisterCanAssetBePublic(const FName OwnerName) override;`
- L191 _public prototype_ `virtual void SyncBrowserToAssets(const TArray<UObject*>& AssetsToSync) override;`
- L192 _public prototype_ `virtual void SyncBrowserToAssets(const TArray<FAssetData>& AssetsToSync) override;`
- L196 _public prototype_ `static UAssetToolsImpl& Get();` — Gets the asset tools singleton as a FAssetTools for asset tools module use
- L199 _public member_ `TSharedPtr<FAssetRenameManager> AssetRenameManager;` — The manager to handle renaming assets
- L202 _public member_ `TSharedPtr<ILocalizedAssetTools> LocalizedAssetTools;` — The tools to manage localized variants
- L205 _public member_ `TSharedPtr<FAssetFixUpRedirectors> AssetFixUpRedirectors;` — The manager to handle fixing up redirectors
- L208 _public prototype_ `static bool CanShowDialogs();` — Check if the Application can currently show dialogs, meaning the App is attended, Slate is initialized and we are not running an unattended or automation scripts
- L210 _private prototype_ `static FString GenerateAdvancedCopyDestinationPackageName(const FString& SourcePackage, const FString& SourcePath, const FString& DestinationFolder);`
- L213 _private prototype_ `bool CheckForDeletedPackage(const UPackage* Package) const;` — Checks to see if a package is marked for delete, then asks the user if they would like to check in the deleted file before they can continue. Returns true when it is safe to proceed.
- L216 _private prototype_ `bool CanCreateAsset(const FString& AssetName, const FString& PackageName, const FText& OperationText, bool bOverwriteExisting) const;` — Returns true if the supplied Asset name and package are currently valid for creation.
- L219 _private prototype_ `void PerformMigratePackages(const TArray<FName>& PackageNamesToMigrate, const FString& DestinationPath, const FMigrationOptions& Options, TSet<FName> AllDependenciesToMigrate, TSet<FName> ExcludedDependencies, bool bSanitizeInputs) const;` — Begins the package migration, after assets have been discovered
- L222 _private prototype_ `bool CanMigratePackage(FName PackageName) const;` — Check if an asset can migrated
- L224 _private prototype_ `TArray<FName> ExpandAssetsAndFoldersToJustAssets(TArray<FName> SelectedAssetAndFolderNames) const;`
- L227 _private prototype_ `void PerformAdvancedCopyPackages(TArray<FName> SelectedPackageNames, FString TargetPath, FAdvancedCopyCompletedEvent OnCopyComplete) const;` — Begins the package advanced copy, after assets have been discovered
- L230 _private prototype_ `void MigratePackages_ReportConfirmed(TSharedPtr<TArray<ReportPackageData>> PackageDataToMigrate, const FString DestinationPath, TSet<FName> ExcludedDependencies, TMap<FName, TSet<FName>> PackageToExternalObjectPackages, const FMigrationOptions Options) const;` — Copies files after the final list was confirmed
- L233 _private prototype_ `void AdvancedCopyPackages_ReportConfirmed(const FAdvancedCopyParams& CopyParam, const TArray<TMap<FString, FString>>& DestinationMap) const;` — Copies files after the final list was confirmed
- L236 _private prototype_ `void RecursiveGetDependencies(const FName& PackageName, TSet<FName>& AllDependencies, TSet<FString>& ExternalObjectsPaths, TSet<FName>& ExcludedDependencies, const TFunction<bool(FName)>& ShouldExcludeFromDependenciesSearch) const;` — Gets the dependencies of the specified package recursively
- L239 _private prototype_ `void RecursiveGetDependenciesAdvanced(const FName& PackageName, FAdvancedCopyParams& CopyParams, TArray<FName>& AllDependencies, TMap<FName, FName>& DependencyMap, const FARCompiledFilter& CompiledExclusionFilter, TArray<FAssetData>& OptionalAssetData) const;` — Gets the dependencies of the specified package recursively while omitting things that don't pass the FARFilter passed in from FAdvancedCopyParams
- L242 _private prototype_ `static void OnNewImportRecord(UClass* AssetType, const FString& FileExtension, bool bSucceeded, bool bWasCancelled, const FDateTime& StartTime);` — Records the time taken for an import and reports it to engine analytics, if available
- L245 _private prototype_ `static void OnNewCreateRecord(UClass* AssetType, bool bDuplicated);` — Records what assets users are creating
- L248 _private prototype_ `TArray<UObject*> ImportAssetsInternal(const TArray<FString>& Files, const FString& RootDestinationPath, TArray<TPair<FString, FString>> *FilesAndDestinationsPtr, const FAssetImportParams& ImportParams) const;` — Internal method that performs the actual asset importing
- L251 _private prototype_ `void ExportAssetsInternal(const TArray<UObject*>& ObjectsToExport, bool bPromptIndividualFilenames, bool bSaveAsCleanFilename, const FString& ExportPath) const;` — Internal method to export assets.  If no export path is created a user will be prompted for one.  if bPromptIndividualFilenames is true a user will be asked per file. if bSaveAsCleanFilename is true the file will be saved as the clean filename
- L253 _private prototype_ `UObject* PerformDuplicateAsset(const FString& AssetName, const FString& PackagePath, UObject* OriginalObject, bool bWithDialog);`
- L259 _private prototype_ `void AddSubContentDenyList(const FString& InMount);` — Add sub content deny list filter for a new mount point @param InMount The mount point
- L262 _private prototype_ `void OnContentPathMounted(const FString& InAssetPath, const FString& FileSystemPath);` — Called when a new mount is added to add the proper sub content deny list to it.
- L265 _private prototype_ `TArray<UObject*> ImportAssetsWithDialogImplementation(const FString& DestinationPath, bool bAllowAsyncImport);` — Implementation for the import with dialog functions
- L268 _private prototype_ `void SyncAssetTypesToAssetDefinitions();` — Make sure we're not syncing
- L271 _private prototype_ `void RemoveAssetTypeActionBySupportedClass(const UClass* SupportedClass);` — Helper to remove an entry AssetTypeActionsList given a class returned by GetSupportedClass
- L274 _private prototype_ `void CreateAssetAsync_OnComplete(UFactory* Factory, TStrongObjectPtr<UPackage> Package, UClass* AssetClass, FString AssetName, EObjectFlags Flags, FName CallingContext, FString PackageName, FAssetCreateComplete OnComplete, FAssetCreateCancelled OnCancelled);` — Called when async asset creation is completed successfully.
- L278 _private prototype_ `void CreateAssetWithDialogAsync_OnComplete(UFactory* Factory, UClass* AssetClass, FName CallingContext, FString SaveObjectPath, FAssetCreateComplete OnComplete, FAssetCreateCancelled OnCancelled);` — Called when async asset creation with a file location picker dialog is completed successfully.
- L282 _private member_ `uint64 CachedVersion = 0;`
- L285 _private member_ `TArray<TSharedRef<IAssetTypeActions>> AssetTypeActionsList;` — The list of all registered AssetTypeActions
- L288 _private member_ `TMap<const UClass*, int> AssetTypeActionsLookup;` — Lookup of the index into AssetTypeActionsList given the SupportedClass of a registered IAssetTypeActions
- L291 _private member_ `TArray<TSharedRef<IClassTypeActions>> ClassTypeActionsList;` — The list of all registered ClassTypeActions
- L294 _private member_ `TMap<FName, FAdvancedAssetCategory> AllocatedCategoryBits;` — The categories that have been allocated already
- L297 _private member_ `uint32 NextUserCategoryBit;` — The next user category bit to allocate (set to 0 when there are no more bits left)
- L300 _private member_ `TSharedRef<FNamePermissionList> AssetClassPermissionList_DEPRECATED;` — This should be removed with the removal of GetAssetClassPermissionList functions
- L303 _private member_ `TArray<TSharedRef<FPathPermissionList>> AssetClassPermissionList;` — Permission lists of assets by class path name, one for each EAssetClassAction
- L305 _private member_ `TSharedRef<FNamePermissionList> ImportExtensionPermissionList;`
- L308 _private member_ `TSet<EBlueprintType> AllowedBlueprintTypes;` — Which types of BlueprintFactories are allowed to be returned through GetNewAssetFactories. Empty set allows all types.
- L311 _private member_ `TSharedRef<FPathPermissionList> FolderPermissionList;` — Permission list of folder paths
- L314 _private member_ `TSharedRef<FPathPermissionList> WritableFolderPermissionList;` — Permission list of folder paths to write to
- L317 _private member_ `TArray<FString> SubContentDenyListPaths;` — List of sub content paths denied for every mount.
- L320 _private member_ `TMap<const UClass*, FString> DefaultNewAssetNames;` — Default names to use when creating new assets
- L322 _private member_ `bool CreateAssetsAsExternallyReferenceable;`
- L323 _private member_ `UE::AssetTools::FShouldCreateAssetsAsExternallyReferenceableForPath CreateAssetsAsExternallyReferenceableForPathDelegate;`
- L325 _private member_ `UE::AssetTools::FShowingContentVersePath ShowingContentVersePathDelegate;`
- L327 _private member_ `TMap<FName, FIsNameAllowed> IsNameAllowedDelegates;`
- L328 _private member_ `TMap<FName, FIsObjectPathAllowed> IsObjectPathAllowedDelegates;`
- L329 _private member_ `TMap<FName, FSanitizeName> SanitizeNameDelegates;`
- L331 _private member_ `UE::AssetTools::FOnPackageMigration OnPackageMigration;`
- L333 _private member_ `TMap<FName, UE::AssetTools::FCanMigrateAsset> CanMigrateAssetDelegates;`
- L335 _private member_ `TMap<FName, UE::AssetTools::FCanAssetBePublic> CanAssetBePublicDelegates;`

#### Free symbols / members of external scopes

- L56 _typedef_ `typedef class UAssetToolsImpl FAssetTools;` — For backwards compatibility

### `Source/Developer/AssetTools/Private/AssetToolsConsoleCommands.h` (Private)


#### class `FAssetToolsConsoleCommands`  
`class FAssetToolsConsoleCommands`  
_L11-29_
- L14 _public member_ `const FAssetToolsModule& Module;`
- L18 _public function_ `FAssetToolsConsoleCommands(const FAssetToolsModule& InModule) : Module(InModule)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define LOCTEXT_NAMESPACE "AssetTools"`

### `Source/Developer/AssetTools/Private/AssetToolsLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAssetTools, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAssetTools, Log, All);`

### `Source/Developer/AssetTools/Private/AssetTypeActions/AssetTypeActions_AnimBoneCompressionSettings.h` (Private)


#### class `FAssetTypeActions_AnimBoneCompressionSettings`  
`class FAssetTypeActions_AnimBoneCompressionSettings : public FAssetTypeActions_Base`  
_L9-27_
- inherits: `FAssetTypeActions_Base`
- L13 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L14 _public function_ `virtual FColor GetTypeColor() const override`
- L15 _public function_ `virtual UClass* GetSupportedClass() const override`
- L16 _public function_ `virtual bool CanFilter() override`
- L17 _public function_ `virtual uint32 GetCategories() override`
- L18 _public prototype_ `virtual const TArray<FText>& GetSubMenus() const override;`
- L20 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L22 _public prototype_ `virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;`
- L25 _private prototype_ `void AddToolbarExtension(FToolBarBuilder& Builder, TWeakObjectPtr<UAnimBoneCompressionSettings> BoneSettings);`
- L26 _private prototype_ `void ExecuteCompression(TWeakObjectPtr<UAnimBoneCompressionSettings> BoneSettings);`

### `Source/Developer/AssetTools/Private/AssetTypeActions/AssetTypeActions_AnimCurveCompressionSettings.h` (Private)


#### class `FAssetTypeActions_AnimCurveCompressionSettings`  
`class FAssetTypeActions_AnimCurveCompressionSettings : public FAssetTypeActions_Base`  
_L9-27_
- inherits: `FAssetTypeActions_Base`
- L13 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L14 _public function_ `virtual FColor GetTypeColor() const override`
- L15 _public function_ `virtual UClass* GetSupportedClass() const override`
- L16 _public function_ `virtual bool CanFilter() override`
- L17 _public function_ `virtual uint32 GetCategories() override`
- L18 _public prototype_ `virtual const TArray<FText>& GetSubMenus() const override;`
- L20 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L22 _public prototype_ `virtual void GetActions(const TArray<UObject*>& InObjects, struct FToolMenuSection& Section) override;`
- L25 _private prototype_ `void AddToolbarExtension(FToolBarBuilder& Builder, TWeakObjectPtr<UAnimCurveCompressionSettings> CurveSettings);`
- L26 _private prototype_ `void ExecuteCompression(TWeakObjectPtr<UAnimCurveCompressionSettings> CurveSettings);`

### `Source/Developer/AssetTools/Private/AssetTypeActions/AssetTypeActions_DeletedObjectPlaceholder.h` (Private)


#### class `FAssetTypeActions_DeletedObjectPlaceholder`  
`class FAssetTypeActions_DeletedObjectPlaceholder : public FAssetTypeActions_Base`  
_L10-21_
- inherits: `FAssetTypeActions_Base`
- L14 _public function_ `virtual FText GetName() const override` — IAssetTypeActions interface
- L15 _public function_ `virtual FColor GetTypeColor() const override`
- L16 _public function_ `virtual UClass* GetSupportedClass() const override`
- L17 _public function_ `virtual uint32 GetCategories() override`
- L18 _public function_ `virtual bool CanLocalize() const override`
- L19 _public prototype_ `virtual FString GetObjectDisplayName(UObject* InObject) const override;`

### `Source/Developer/AssetTools/Private/AssetTypeActions/AssetTypeActions_VariableFrameStrippingSettings.h` (Private)


#### class `FAssetTypeActions_VariableFrameStrippingSettings`  
`class FAssetTypeActions_VariableFrameStrippingSettings : public FAssetTypeActions_Base`  
_L9-24_
- inherits: `FAssetTypeActions_Base`
- L13 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L14 _public function_ `virtual FColor GetTypeColor() const override`
- L15 _public function_ `virtual UClass* GetSupportedClass() const override`
- L16 _public function_ `virtual bool CanFilter() override`
- L17 _public function_ `virtual uint32 GetCategories() override`
- L19 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`

### `Source/Developer/AssetTools/Private/LocalizedAssetTools.h` (Private)


#### class `FLocalizedAssetTools`  
`class FLocalizedAssetTools : public ILocalizedAssetTools`  
_L10-44_
- inherits: `ILocalizedAssetTools`
- L13 _public prototype_ `FLocalizedAssetTools();`
- L14 _public prototype_ `virtual ~FLocalizedAssetTools() = default;`
- L18 _public prototype_ `virtual bool CanLocalize(const UClass* Class) const override;`
- L20 _public prototype_ `virtual ELocalizedAssetsOnDiskResult GetLocalizedVariantsOnDisk(const TArray<FName>& InPackages, TMap<FName, TArray<FName>>& OutLocalizedVariantsBySource, TArray<FName>* OutPackagesNotFound = nullptr) const override;`
- L22 _public prototype_ `virtual ELocalizedAssetsInSCCResult GetLocalizedVariantsInRevisionControl(const TArray<FName>& InPackages, TMap<FName, TArray<FName>>& OutLocalizedVariantsBySource, TArray<FName>* OutPackagesNotFound = nullptr) const override;`
- L24 _public prototype_ `virtual ELocalizedAssetsResult GetLocalizedVariants(const TArray<FName>& InPackages, TMap<FName, TArray<FName>>& OutLocalizedVariantsBySourceOnDisk, bool bAlsoCheckInRevisionControl, TMap<FName, TArray<FName>>& OutLocalizedVariantsBySourceInRevisionControl, TArray<FName>* OutPackagesNotFound = nullptr) const override;`
- L26 _public prototype_ `virtual void OpenRevisionControlRequiredDialog() const override;`
- L28 _public prototype_ `virtual void OpenFilesInRevisionControlRequiredDialog(const TArray<FText>& FileList) const override;`
- L30 _public prototype_ `virtual void OpenLocalizedVariantsListMessageDialog(const FText& Header, const FText& Message, const TArray<FText>& FileList) const override;`
- L32 _public prototype_ `virtual ELocalizedVariantsInclusion OpenIncludeLocalizedVariantsListDialog( const TArray<FText>& FileList, ELocalizedVariantsInclusion RecommendedBehavior = ELocalizedVariantsInclusion::Include, bool bAllowOperationCanceling = true, ELocalizedVariantsInclusion UnattendedDefaultBehavior = ELocalizedVariantsInclusion::Exclude) const override;`
- L34 _public prototype_ `virtual const FText& GetRevisionControlIsNotAvailableWarningText() const override;`
- L36 _public prototype_ `virtual const FText& GetFilesNeedToBeOnDiskWarningText() const override;`
- L39 _private prototype_ `bool GetLocalizedVariantsDepotPaths(const TArray<FString>& InPackagesNames, TArray<FString>& OutLocalizedVariantsPaths) const;`
- L42 _private member_ `FText RevisionControlIsNotAvailableWarningText;`
- L43 _private member_ `FText FilesNeedToBeOnDiskWarningText;`

### `Source/Developer/AssetTools/Private/SAdvancedCopyReportDialog.h` (Private)


#### class `SAdvancedCopyColumn`  
`class SAdvancedCopyColumn : public TSharedFromThis< SAdvancedCopyColumn >`  
_L22-38_
- inherits: `TSharedFromThis<SAdvancedCopyColumn>`
- L25 _public function_ `SAdvancedCopyColumn(FName InColumnName)`
- L29 _public prototype_ `virtual ~SAdvancedCopyColumn() = default;`
- L31 _public function_ `virtual FName GetColumnID()`
- L33 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn();`
- L35 _public prototype_ `virtual const TSharedRef< SWidget > ConstructRowWidget(TSharedPtr<struct FAdvancedCopyReportNode> TreeItem, const SAdvancedCopyTreeRow& Row);`
- L37 _public member_ `FName ColumnName;`

#### struct `FAdvancedCopyReportNode`  
`struct FAdvancedCopyReportNode`  
_L40-69_
- L43 _public member_ `FString Source;` — The name of the tree node without the path
- L45 _public member_ `FString Destination;` — The name of the tree node without the path
- L47 _public member_ `TArray< TSharedPtr<FAdvancedCopyReportNode> > Children;` — The children of this node
- L49 _public member_ `TSharedPtr<TSet<FString>> IncludedSet;` — The included set
- L52 _public prototype_ `FAdvancedCopyReportNode();` — Constructor
- L53 _public prototype_ `FAdvancedCopyReportNode(const FString& InSource, const FString& InDestination, TSharedPtr<TSet<FString>> InIncludedSet);`
- L56 _public prototype_ `void AddPackage(const FString& Source, const FString& Destination, const FString& DependencyOf);` — Adds the path to the tree relative to this node, creating nodes as needed.
- L59 _public prototype_ `void ExpandChildrenRecursively(const TSharedRef<SAdvancedCopyReportTree>& TreeView);` — Expands this node and all its children
- L62 _public prototype_ `void ForAllDescendants(TFunctionRef<void(const TSharedPtr<FAdvancedCopyReportNode>& )> RecursiveAction);` — Perform recursive action on all descendants.
- L64 _public prototype_ `bool GetWillCopy() const;`
- L65 _public prototype_ `void SetWillCopy(bool bCopy);`
- L68 _private prototype_ `bool AddPackage_Recursive(const FString& Source, const FString& Destination, const FString& DependencyOf);`

#### class `SAdvancedCopyReportDialog`  
`class SAdvancedCopyReportDialog : public SCompoundWidget`  
_L71-131_
- inherits: `SCompoundWidget`
- L74 _public typedef_ `typedef TArray<TMap<FString, FString>> FCopyDestinationMap;`
- L75 _public function_ `DECLARE_DELEGATE_TwoParams(FOnReportConfirmed, const FAdvancedCopyParams&, const FCopyDestinationMap&) SLATE_BEGIN_ARGS(SAdvancedCopyReportDialog)`
- L79 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const FAdvancedCopyParams& InParams, const FString& InDestination, const TArray<TMap<FString, FString>>& DestinationMap, const TArray<TMap<FName, FName>>& DependencyMap, const FOnReportConfirmed& InOnReportConfirmed );`
- L84 _public prototype_ `ECheckBoxState IsGeneratingDependencies() const;`
- L86 _public prototype_ `void ToggleGeneratingDependencies(ECheckBoxState NewState);`
- L89 _public prototype_ `static void OpenPackageReportDialog(const FAdvancedCopyParams& InParams, const FString& Destination, const TArray<TMap<FString, FString>>& DestinationMap, const TArray<TMap<FName, FName>>& DependencyMap, const FOnReportConfirmed& InOnReportConfirmed);` — Opens the dialog in a new window
- L92 _public prototype_ `void CloseDialog();` — Closes the dialog.
- L94 _public function_ `TMap<FName, TSharedPtr<SAdvancedCopyColumn>> GetColumns() const`
- L96 _public function_ `const FString& GetDestination() const`
- L100 _private prototype_ `void ConstructNodeTree(const TArray<TMap<FString, FString>>& DestinationMap, const TArray<TMap<FName, FName>>& DependencyMap);` — Constructs the node tree given the list of package names
- L103 _private prototype_ `TSharedRef<ITableRow> GenerateTreeRow( TSharedPtr<FAdvancedCopyReportNode> TreeItem, const TSharedRef<STableViewBase>& OwnerTable );` — Handler to generate a row in the report tree
- L106 _private prototype_ `void GetChildrenForTree( TSharedPtr<FAdvancedCopyReportNode> TreeItem, TArray< TSharedPtr<FAdvancedCopyReportNode> >& OutChildren );` — Gets the children for the specified tree item
- L108 _private prototype_ `void SetItemExpansionRecursive(TSharedPtr<FAdvancedCopyReportNode> TreeItem, bool bInExpansionState);`
- L111 _private prototype_ `FReply OkClicked();` — Handler for when "Ok" is clicked
- L114 _private prototype_ `FReply CancelClicked();` — Handler for when "Cancel" is clicked
- L116 _private prototype_ `FText GetHeaderText(const FText InReportMessage) const;`
- L119 _private member_ `FOnReportConfirmed OnReportConfirmed;`
- L120 _private member_ `FAdvancedCopyReportNode PackageReportRootNode;`
- L121 _private member_ `TSharedPtr<SAdvancedCopyReportTree> ReportTreeView;`
- L123 _private member_ `TSharedPtr<TSet<FString>> CloneSet;` — The set of things to actually clone.
- L125 _private member_ `TMap<FName, TSharedPtr<SAdvancedCopyColumn>> Columns;` — Map of columns that are shown on this report.
- L126 _private member_ `FString Destination;`
- L127 _private member_ `FAdvancedCopyParams CurrentCopyParams;`
- L128 _private member_ `TArray<TMap<FString, FString>> InitialDestinationMap;`
- L129 _private member_ `FString FindString;`
- L130 _private member_ `FString ReplaceString;`

#### class `SAdvancedCopyTreeRow`  
`class SAdvancedCopyTreeRow : public SMultiColumnTableRow< TSharedPtr<struct FAdvancedCopyReportNode> >`  
_L135-169_
- inherits: `SMultiColumnTableRow<TSharedPtr<structFAdvancedCopyReportNode>>`
- desc: Widget that represents a row in the outliner's tree control.  Generates widgets for each column on demand.
- L141 _public function_ `SLATE_BEGIN_ARGS(SAdvancedCopyTreeRow)`
- L144 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<struct FAdvancedCopyReportNode>, Item) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SAdvancedCopyReportTree>& OutlinerTreeView, TSharedRef<SAdvancedCopyReportDialog> AdvancedCopyReport);` — The list item for this row
- L153 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the tree row.
- L155 _public function_ `TSharedPtr<SAdvancedCopyReportDialog> GetReportDialog() const`
- L161 _private prototype_ `ECheckBoxState GetWillCopyCheckedState() const;`
- L162 _private prototype_ `void ApplyWillCopyCheckedState(const ECheckBoxState NewCheckState);`
- L165 _private member_ `TWeakPtr< SAdvancedCopyReportDialog > ReportDialogWeak;` — Weak reference to the outliner widget that owns our list
- L168 _private member_ `TWeakPtr<struct FAdvancedCopyReportNode> Item;` — The item associated with this row of data

#### Free symbols / members of external scopes

- L20 _typedef_ `typedef STreeView< TSharedPtr<struct FAdvancedCopyReportNode> > SAdvancedCopyReportTree;`
- L75 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnReportConfirmed, const FAdvancedCopyParams&, const FCopyDestinationMap&) SLATE_BEGIN_ARGS(SAdvancedCopyReportDialog){} SLATE_END_ARGS() void Construct( const FArguments& InArgs, const FAdvancedCopyParams& InParams, const FString& InDestination, const TArray<TMap<FString, FString>>& DestinationMap, const TArray<TMap<FName, FName>>& DependencyMap, const FOnReportConfirmed& InOnReportConfirmed );`

### `Source/Developer/AssetTools/Private/SDiscoveringAssetsDialog.h` (Private)


#### class `SDiscoveringAssetsDialog`  
`class SDiscoveringAssetsDialog : public SCompoundWidget`  
_L10-42_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS( SDiscoveringAssetsDialog )`
- L17 _public prototype_ `SLATE_EVENT( FOnAssetsDiscovered, OnAssetsDiscovered) SLATE_END_ARGS() ~SDiscoveringAssetsDialog();`
- L25 _public prototype_ `void Construct( const FArguments& InArgs );` — Constructs this widget with InArgs
- L28 _public prototype_ `static void OpenDiscoveringAssetsDialog(const FOnAssetsDiscovered& InOnAssetsDiscovered);` — Opens the dialog in a new window
- L32 _private prototype_ `FReply CancelClicked();` — Handler for when "Cancel" is clicked
- L35 _private prototype_ `void AssetRegistryLoadComplete();` — Called when the asset registry initial load has completed
- L38 _private prototype_ `void CloseDialog();` — Closes the dialog.
- L41 _private member_ `FOnAssetsDiscovered OnAssetsDiscovered;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE(FOnAssetsDiscovered) SLATE_BEGIN_ARGS( SDiscoveringAssetsDialog ){} SLATE_EVENT( FOnAssetsDiscovered, OnAssetsDiscovered) SLATE_END_ARGS() ~SDiscoveringAssetsDialog();`

### `Source/Developer/AssetTools/Private/SFileListReportDialog.h` (Private)


#### class `SFileListReportDialog`  
`class SFileListReportDialog : public SCompoundWidget`  
_L12-52_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SFileListReportDialog)`
- L17 _public prototype_ `SLATE_ARGUMENT(FText, Header) SLATE_ARGUMENT(TArray<FText>, Files) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L24 _public prototype_ `static void OpenListDialog(const FText& InTitle, const FText& InHeader, const TArray<FText>& InFiles, bool bOpenAsModal = false);`
- L27 _protected prototype_ `TSharedRef<ITableRow> MakeListViewWidget(TSharedRef<FText> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L28 _protected prototype_ `virtual TSharedRef<SHorizontalBox> ConstructButtons(const FArguments& InArgs);`
- L30 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L31 _protected prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L33 _protected prototype_ `static void CreateWindow(TSharedRef<SFileListReportDialog> InFileListReportDialogRef);`
- L35 _protected prototype_ `FReply CloseWindow();`
- L36 _protected prototype_ `void OnWindowClosed(const TSharedRef<SWindow>& Window);`
- L37 _protected function_ `virtual void OnClosedWithTitleBarX(const TSharedRef<SWindow>& Window)`
- L39 _protected prototype_ `void SetModal(bool bIsModal);`
- L40 _protected prototype_ `void SetAllowTitleBarX(bool bInAllowTitleBarX);`
- L43 _protected member_ `bool bOpenAsModal = false;`
- L44 _protected member_ `bool bAllowTitleBarX = true;`
- L45 _protected member_ `FText Title;`
- L48 _private member_ `FText Header;`
- L49 _private member_ `TArray< TSharedRef<FText> > Files;`
- L51 _private member_ `bool bClosingWithoutTitleBarX = false;`

### `Source/Developer/AssetTools/Private/SPackageReportDialog.h` (Private)


#### struct `ReportPackageData`  
`struct ReportPackageData`  
_L17-21_
- L19 _public member_ `FString Name;`
- L20 _public member_ `bool bShouldMigratePackage;`

#### struct `FPackageReportNode`  
`struct FPackageReportNode`  
_L23-57_
- L26 _public member_ `FString NodeName;` — The name of the tree node without the path
- L28 _public member_ `FText NodeText;` — The display name of the tree node
- L30 _public member_ `FText ToolTipText;` — The tooltip of the tree node
- L32 _public member_ `ECheckBoxState CheckedState;` — A user-exposed flag determining whether the content of this node and its children should be migrated or not.
- L34 _public member_ `bool* bShouldMigratePackage;` — A pointer to an external bool describing whether this node ultimately should be migrated or not. Is only non-null for leaf nodes.
- L37 _public member_ `FPackageReportNode* Parent;` — The parent of this node
- L40 _public member_ `TArray< TSharedPtr<FPackageReportNode> > Children;` — The children of this node
- L43 _public prototype_ `FPackageReportNode();` — Constructor
- L44 _public prototype_ `FPackageReportNode(FString&& InNodeName, FText&& InNodeText, FText&& InToolTipText, bool* bInShouldMigratePackage, FPackageReportNode& Parent);`
- L47 _public prototype_ `void AddPackage(const FString& PackageName, bool* bInIsPackageIncluded);` — Adds the path to the tree relative to this node, creating nodes as needed.
- L50 _public prototype_ `void ExpandChildrenRecursively(const TSharedRef<PackageReportTree>& Treeview);` — Expands this node and all its children
- L53 _public prototype_ `void Finalize();` — Call after all nodes have been created to order the child nodes for display and calculate their initial CheckedState.
- L56 _public prototype_ `void UpdateCheckedStateFromChildren();` — Updates CheckedState from this node's child CheckedStates if bShouldMigratePackage is null

#### class `SPackageReportDialog`  
`class SPackageReportDialog : public SCompoundWidget`  
_L59-114_
- inherits: `SCompoundWidget`
- L64 _public function_ `SLATE_BEGIN_ARGS( SPackageReportDialog )`
- L66 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const FText& InReportMessage, TArray<ReportPackageData>& InPackageNames, const FOnReportConfirmed& InOnReportConfirmed );`
- L72 _public prototype_ `static void OpenPackageReportDialog(const FText& ReportMessage, TArray<ReportPackageData>& PackageNames, const FOnReportConfirmed& InOnReportConfirmed);` — Opens the dialog in a new window
- L75 _public prototype_ `void CloseDialog();` — Closes the dialog.
- L79 _private prototype_ `void SetStateRecursive(TSharedPtr<FPackageReportNode> TreeItem, bool bIsChecked);` — Recursively sets the checked/active state of every child of this node in the tree when a checkbox is toggled.
- L82 _private prototype_ `ECheckBoxState GetEnabledCheckState(TSharedPtr<FPackageReportNode> TreeItem) const;` — Callback to check whether a checkbox is checked or not.
- L85 _private prototype_ `void CheckBoxStateChanged(ECheckBoxState InCheckBoxState, TSharedPtr<FPackageReportNode> TreeItem, TSharedRef<STableViewBase> OwnerTable);` — Callback called whenever a checkbox is toggled.
- L88 _private prototype_ `void ConstructNodeTree(TArray<ReportPackageData>& PackageNames);` — Constructs the node tree given the list of package names
- L91 _private prototype_ `TSharedRef<ITableRow> GenerateTreeRow( TSharedPtr<FPackageReportNode> TreeItem, const TSharedRef<STableViewBase>& OwnerTable );` — Handler to generate a row in the report tree
- L94 _private prototype_ `void GetChildrenForTree( TSharedPtr<FPackageReportNode> TreeItem, TArray< TSharedPtr<FPackageReportNode> >& OutChildren );` — Gets the children for the specified tree item
- L97 _private prototype_ `const FSlateBrush* GetNodeIcon(TSharedPtr<FPackageReportNode> ReportNode) const;` — Determines which image to display next to a node
- L100 _private prototype_ `FReply OkClicked();` — Handler for when "Ok" is clicked
- L103 _private prototype_ `FReply CancelClicked();` — Handler for when "Cancel" is clicked
- L106 _private member_ `FOnReportConfirmed OnReportConfirmed;`
- L107 _private member_ `FPackageReportNode PackageReportRootNode;`
- L108 _private member_ `TSharedPtr<PackageReportTree> ReportTreeView;`
- L111 _private member_ `const FSlateBrush* FolderOpenBrush;` — Brushes for the different node states
- L112 _private member_ `const FSlateBrush* FolderClosedBrush;`
- L113 _private member_ `const FSlateBrush* PackageBrush;`

#### Free symbols / members of external scopes

- L15 _typedef_ `typedef STreeView< TSharedPtr<struct FPackageReportNode> > PackageReportTree;`
- L62 _delegate_ `DECLARE_DELEGATE(FOnReportConfirmed) SLATE_BEGIN_ARGS( SPackageReportDialog ){} SLATE_END_ARGS() void Construct( const FArguments& InArgs, const FText& InReportMessage, TArray<ReportPackageData>& InPackageNames, const FOnReportConfirmed& InOnReportConfirmed );`

### `Source/Developer/AssetTools/Public/AdvancedCopyCustomization.h` (Public)


#### class `UAdvancedCopyCustomization`  
`class UAdvancedCopyCustomization : public UObject`  
_L16-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L21 _public prototype_ `UAdvancedCopyCustomization(const class FObjectInitializer& ObjectInitializer);`
- L24 _public function_ `bool GetShouldGenerateRelativePaths() const` — Getter for whether or not we should generate relative paths for this advanced copy
- L30 _public function_ `virtual FARFilter GetARFilter() const` — Returns the ARFilter for this advanced copy
- L36 _public function_ `virtual void EditCopyParams(FAdvancedCopyParams& CopyParams) const` — Allows the customization to edit the parameters for the whole copy operation
- L39 _public function_ `virtual void ApplyAdditionalFiltering(TArray<FName>& PackagesToCopy) const` — Apply any additional filtering after the ARFilter is run on the packages to copy
- L42 _public function_ `virtual void TransformDestinationPaths(TMap<FString, FString>& OutPackagesAndDestinations) const` — Once the destination map is generated for the set of assets, the destinations can be manipulated for renaming, restructuring, etc.
- L45 _public function_ `virtual bool CustomCopyValidate(const TMap<FString, FString>& OutPackagesAndDestinations) const` — Allows for additional validation of the packages to be copied and their destination. Returns false if anything doesn't pass validation
- L48 _public prototype_ `void SetPackageThatInitiatedCopy(const FString& InBasePackage);` — Store the path of the package that caused this customization to be used
- L50 _public function_ `const FString GetPackageThatInitiatedCopy() const`
- L54 _protected member_ `bool bShouldGenerateRelativePaths;` — Whether or not the destinations for copy should be relative to the package that initiated the copy
- L57 _protected member_ `FARFilter FilterForExcludingDependencies;` — The filter to use when finding valid dependencies to also copy
- L60 _protected member_ `FString PackageThatInitiatedCopy;` — The path of the package that caused this customization to be used

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ASSETTOOLS_API`

### `Source/Developer/AssetTools/Public/AssetToolsModule.h` (Public)


#### class `FAssetToolsModule`  
`class FAssetToolsModule : public IModuleInterface`  
_L12-41_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule();`
- L16 _public prototype_ `virtual void ShutdownModule();`
- L18 _public prototype_ `virtual IAssetTools& Get() const;`
- L26 _public function_ `static inline FAssetToolsModule& GetModule()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsModuleLoaded()`
- L39 _private member_ `TWeakObjectPtr<class UAssetToolsImpl> AssetToolsPtr;`
- L40 _private member_ `class FAssetToolsConsoleCommands* ConsoleCommands = nullptr;`

### `Source/Developer/AssetTools/Public/AssetToolsSettings.h` (Public)


#### struct `FAdvancedCopyMap`  
`struct FAdvancedCopyMap`  
_L13-25_
- reflection: `USTRUCT()`
- L20 _public member_ `FSoftClassPath ClassToCopy;` — `UPROPERTY(EditAnywhere, Category = "Asset Tools", meta = (MetaClass = "/Script/CoreUObject.Object"))` — When copying this class, use a particular set of dependency and destination rules
- L24 _public member_ `FSoftClassPath AdvancedCopyCustomization;` — `UPROPERTY(EditAnywhere, Category = "Asset Tools", meta = (MetaClass = "/Script/AssetTools.AdvancedCopyCustomization"))` — The set of dependency and destination rules to use for advanced copy

#### class `UAssetToolsSettings`  
`class UAssetToolsSettings : public UDeveloperSettings`  
_L28-38_
- reflection: `UCLASS(MinimalAPI, config = Game, defaultconfig, meta = (DisplayName = "Asset Tools"))`
- inherits: `UDeveloperSettings`
- L33 _public function_ `UAssetToolsSettings()`
- L37 _public member_ `TArray<FAdvancedCopyMap> AdvancedCopyCustomizations;` — `UPROPERTY(config, EditAnywhere, Category = "Advanced Copy", Meta = (TitleProperty = "ClassToCopy"))` — List of rules to use when advanced copying assets

#### struct `FAssetNamingConventionEntry`  
`struct FAssetNamingConventionEntry`  
_L41-65_
- reflection: `USTRUCT()`
- L49 _public member_ `TOptional<FString> Prefix;` — `UPROPERTY(EditAnywhere, Category = "Asset Naming")` — An optional prefix to include when naming an asset
- L58 _public member_ `TOptional<FString> AssetName;` — `UPROPERTY(EditAnywhere, Category = "Asset Naming")` — Supports {source} when used in the context of creating assets from existing uobjects instead of purely from factory For instance, to override "NewBlueprint" with "BP_", "BP_{source}_" to preserve existing source object names, or "BP_" to always reset the link Note - if using a prefix or suffix, you must also set this (todo this is terrible)
- L64 _public member_ `TOptional<FString> Suffix;` — `UPROPERTY(EditAnywhere, Category = "Asset Naming")` — An optional suffix to include when naming an asset

#### class `UAssetToolsEditorSettings`  
`class UAssetToolsEditorSettings : public UDeveloperSettings`  
_L68-81_
- reflection: `UCLASS(config = EditorSettings, defaultconfig, meta = (DisplayName = "Asset Tools"))`
- inherits: `UDeveloperSettings`
- L73 _public function_ `UAssetToolsEditorSettings()`
- L80 _public member_ `TMap<TSoftClassPtr<UObject>, FAssetNamingConventionEntry> AssetNamingConventionOverrides;` — `UPROPERTY(EditAnywhere, config, Category = "Asset Naming")` — Override default name for new assets, by asset type. Use of an override will override any factory setting

### `Source/Developer/AssetTools/Public/AssetTypeActions/AssetTypeActions_AnimationAsset.h` (Public)


#### class `FAssetTypeActions_AnimationAsset`  
`FAssetTypeActions_AnimationAsset : public FAssetTypeActions_Base`  
_L16-44_
- reflection: `UE_DEPRECATED(5.2, "The AssetDefinition system is replacing AssetTypeActions and UAssetDefinition_AnimationAsset replaced this. Please see the Conversion Guide in AssetDefinition.h")`
- inherits: `FAssetTypeActions_Base`
- L20 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L21 _public function_ `virtual FColor GetTypeColor() const override`
- L22 _public function_ `virtual UClass* GetSupportedClass() const override`
- L23 _public prototype_ `virtual void OpenAssetEditor( const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>() ) override;`
- L24 _public function_ `virtual bool CanFilter() override`
- L25 _public function_ `virtual uint32 GetCategories() override`
- L26 _public prototype_ `virtual class UThumbnailInfo* GetThumbnailInfo(UObject* Asset) const override;`
- L31 _private prototype_ `void ExecuteFindSkeleton(TArray<TWeakObjectPtr<UAnimationAsset>> Objects);` — Handler for when FindSkeleton is selected
- L34 _private prototype_ `void ExecuteReplaceSkeleton(TArray<TWeakObjectPtr<UAnimationAsset>> Objects);` — Handler for when ReplaceSkeleton is selected
- L37 _private prototype_ `void ExecuteOpenInNewWindow(TArray<TWeakObjectPtr<UAnimationAsset>> Objects);` — Handle menu item for wanting to open asset in a new editor
- L40 _private prototype_ `void OpenAnimAssetEditor(const TArray<UObject*>& InObjects, bool bForceNewEditor, TSharedPtr<IToolkitHost> EditWithinLevelEditor);` — Open animation asset, will find existing editor if desired.
- L43 _private prototype_ `bool ReplaceMissingSkeleton(TArray<TObjectPtr<UObject>> InAnimationAssets) const;` — Replace skeleton when USkeleton is missing. Returns true only if Skeleton was replaced.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ASSETTOOLS_API`

### `Source/Developer/AssetTools/Public/AssetTypeActions/AssetTypeActions_Blueprint.h` (Public)


#### class `FAssetTypeActions_Blueprint`  
`FAssetTypeActions_Blueprint : public FAssetTypeActions_ClassTypeBase`  
_L18-66_
- reflection: `UE_DEPRECATED(5.2, "The AssetDefinition system is replacing AssetTypeActions and UAssetDefinition_Blueprint replaced this. Please see the Conversion Guide in AssetDefinition.h")`
- inherits: `FAssetTypeActions_ClassTypeBase`
- L22 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L23 _public function_ `virtual FColor GetTypeColor() const override`
- L24 _public function_ `virtual UClass* GetSupportedClass() const override`
- L29 _public function_ `virtual bool ShouldCallGetActions() const override` — AssetDefinition - The Blueprint actions are now in the UAssetDefinition_Blueprint, can't use false here, since FAssetTypeActions_Blueprint is inherited.  Need the others to function until they can move.
- L31 _public prototype_ `virtual void GetActions(const TArray<UObject*>& InObjects, FToolMenuSection& Section) override;`
- L32 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L33 _public prototype_ `virtual bool CanMerge() const override;`
- L34 _public prototype_ `virtual void Merge(UObject* InObject) override;`
- L35 _public prototype_ `virtual void Merge(UObject* BaseAsset, UObject* RemoteAsset, UObject* LocalAsset, const FOnMergeResolved& ResolutionCallback) override;`
- L36 _public function_ `virtual uint32 GetCategories() override`
- L37 _public prototype_ `virtual void PerformAssetDiff(UObject* Asset1, UObject* Asset2, const struct FRevisionInfo& OldRevision, const struct FRevisionInfo& NewRevision) const override;`
- L38 _public prototype_ `virtual class UThumbnailInfo* GetThumbnailInfo(UObject* Asset) const override;`
- L39 _public prototype_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override;`
- L42 _public prototype_ `virtual TWeakPtr<IClassTypeActions> GetClassTypeActions(const FAssetData& AssetData) const override;` — FAssetTypeActions_ClassTypeBase Implementation
- L46 _protected prototype_ `virtual bool CanCreateNewDerivedBlueprint() const;` — Whether or not this asset can create derived blueprints
- L49 _protected prototype_ `virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const;` — Return the factory responsible for creating this type of Blueprint
- L52 _protected prototype_ `FText GetNewDerivedBlueprintTooltip(TWeakObjectPtr<UBlueprint> InObject);` — Returns the tooltip to display when attempting to derive a Blueprint
- L55 _protected prototype_ `bool CanExecuteNewDerivedBlueprint(TWeakObjectPtr<UBlueprint> InObject);` — Returns TRUE if you can derive a Blueprint
- L59 _private prototype_ `void ExecuteEditDefaults(TArray<TWeakObjectPtr<UBlueprint>> Objects);` — Handler for when EditDefaults is selected
- L62 _private prototype_ `void ExecuteNewDerivedBlueprint(TWeakObjectPtr<UBlueprint> InObject);` — Handler for when NewDerivedBlueprint is selected
- L65 _private prototype_ `bool ShouldUseDataOnlyEditor( const UBlueprint* Blueprint ) const;` — Returns true if the blueprint is data only

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ASSETTOOLS_API`

### `Source/Developer/AssetTools/Public/AssetTypeActions/AssetTypeActions_BlueprintGeneratedClass.h` (Public)


#### class `FAssetTypeActions_BlueprintGeneratedClass`  
`FAssetTypeActions_BlueprintGeneratedClass : public FAssetTypeActions_ClassTypeBase`  
_L18-35_
- reflection: `UE_DEPRECATED(5.2, "The AssetDefinition system is replacing AssetTypeActions and UAssetDefinition_BlueprintGeneratedClass replaced this. Please see the Conversion Guide in AssetDefinition.h")`
- inherits: `FAssetTypeActions_ClassTypeBase`
- L22 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L23 _public function_ `virtual FColor GetTypeColor() const override`
- L24 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L27 _public function_ `virtual uint32 GetCategories() override` — We don't want BPGCs to show up in CB/Ref viewer filters since the BP filters already include them
- L33 _public prototype_ `virtual TWeakPtr<IClassTypeActions> GetClassTypeActions(const FAssetData& AssetData) const override;` — FAssetTypeActions_ClassTypeBase Implementation

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ASSETTOOLS_API`

### `Source/Developer/AssetTools/Public/AssetTypeActions/AssetTypeActions_ClassTypeBase.h` (Public)


#### class `FAssetTypeActions_ClassTypeBase`  
`FAssetTypeActions_ClassTypeBase : public FAssetTypeActions_Base`  
_L15-22_
- reflection: `UE_DEPRECATED(5.2, "The AssetDefinition system is replacing AssetTypeActions and this was replaced by AssetDefinition_ClassTypeBase. Please see the Conversion Guide in AssetDefinition.h")`
- inherits: `FAssetTypeActions_Base`
- L18 _public function_ `virtual bool CanLocalize() const override`
- L21 _public prototype_ `virtual TWeakPtr<IClassTypeActions> GetClassTypeActions(const FAssetData& AssetData) const = 0;` — Get the class type actions for this asset

### `Source/Developer/AssetTools/Public/AssetTypeActions/AssetTypeActions_DataAsset.h` (Public)


#### class `FAssetTypeActions_DataAsset`  
`FAssetTypeActions_DataAsset : public FAssetTypeActions_Base`  
_L14-24_
- reflection: `UE_DEPRECATED(5.8, "The AssetDefinition system is replacing AssetTypeActions and UAssetDefinition_DataAsset replaced this. Please see the Conversion Guide in AssetDefinition.h")`
- inherits: `FAssetTypeActions_Base`
- L18 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L19 _public function_ `virtual FColor GetTypeColor() const override`
- L20 _public function_ `virtual UClass* GetSupportedClass() const override`
- L21 _public function_ `virtual uint32 GetCategories() override`
- L22 _public prototype_ `virtual FText GetDisplayNameFromAssetData(const FAssetData& AssetData) const override;`
- L23 _public prototype_ `virtual void PerformAssetDiff(UObject* OldAsset, UObject* NewAsset, const FRevisionInfo& OldRevision, const FRevisionInfo& NewRevision) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ASSETTOOLS_API`

### `Source/Developer/AssetTools/Public/AssetTypeActions_Base.h` (Public)


#### class `FAssetTypeActions_Base`  
`class FAssetTypeActions_Base : public IAssetTypeActions`  
_L24-253_
- inherits: `IAssetTypeActions`
- desc: A base class for all AssetTypeActions. Provides helper functions useful for many types. Deriving from this class is optional.
- L29 _public function_ `virtual FString GetObjectDisplayName(UObject* Object) const override` — IAssetTypeActions interface
- L34 _public function_ `virtual bool ShouldFindEditorForAsset() const override`
- L39 _public function_ `virtual void OpenAssetEditor( const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>() ) override`
- L44 _public function_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, const EAssetTypeActivationOpenedMethod OpenedMethod, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override`
- L52 _public function_ `virtual bool AssetsActivatedOverride(const TArray<UObject*>& InObjects, EAssetTypeActivationMethod::Type ActivationType) override`
- L57 _public function_ `virtual TArray<FAssetData> GetValidAssetsForPreviewOrEdit(TArrayView<const FAssetData> InAssetDatas, bool bIsPreview) override`
- L62 _public function_ `virtual bool CanRename(const FAssetData& InAsset, FText* OutErrorMsg) const override`
- L67 _public function_ `virtual bool CanDuplicate(const FAssetData& InAsset, FText* OutErrorMsg) const override`
- L72 _public function_ `virtual bool CanFilter() override`
- L77 _public function_ `virtual bool CanLocalize() const override`
- L82 _public function_ `virtual bool CanMerge() const override`
- L87 _public function_ `virtual void Merge(UObject* InObject) override`
- L92 _public function_ `virtual void Merge(UObject* BaseAsset, UObject* RemoteAsset, UObject* LocalAsset, const FOnMergeResolved& ResolutionCallback) override`
- L97 _public function_ `virtual bool ShouldForceWorldCentric() override`
- L102 _public function_ `virtual void PerformAssetDiff(UObject* OldAsset, UObject* NewAsset, const struct FRevisionInfo& OldRevision, const struct FRevisionInfo& NewRevision) const override`
- L115 _public function_ `virtual class UThumbnailInfo* GetThumbnailInfo(UObject* Asset) const override`
- L120 _public function_ `virtual EThumbnailPrimType GetDefaultThumbnailPrimitiveType(UObject* Asset) const override`
- L125 _public function_ `virtual const TArray<FText>& GetSubMenus() const override`
- L131 _public function_ `virtual TSharedPtr<class SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override`
- L136 _public function_ `virtual bool IsImportedAsset() const override`
- L141 _public function_ `virtual void GetResolvedSourceFilePaths(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFilePaths) const override`
- L145 _public function_ `virtual void GetSourceFileLabels(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFileLabels) const override`
- L156 _public function_ `virtual void BuildBackendFilter(FARFilter& InFilter) override`
- L163 _public function_ `virtual FText GetDisplayNameFromAssetData(const FAssetData& AssetData) const override`
- L168 _public function_ `virtual bool SupportsOpenedMethod(const EAssetTypeActivationOpenedMethod OpenedMethod) const override`
- L173 _public function_ `virtual FName GetFilterName() const override`
- L178 _public function_ `virtual FTopLevelAssetPath GetClassPathName() const override`
- L183 _public function_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override`
- L185 _public function_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override`
- L192 _protected function_ `virtual void CreateUniqueAssetName(const FString& InBasePackageName, const FString& InSuffix, FString& OutPackageName, FString& OutAssetName) const` — Creates a unique package and asset name taking the form InBasePackageName+InSuffix
- L199 _protected function_ `virtual FString DumpAssetToTempFile(UObject* Asset) const` — Util for dumping an asset to a temporary text file. Returns absolute filename to temp file
- L206 _protected function_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override` — Returns additional tooltip information for the specified asset, if it has any (otherwise return the null widget)
- L213 _protected function_ `template <typename T> static TArray<TWeakObjectPtr<T>> GetTypedWeakObjectPtrs(const TArray<UObject*>& InObjects)` — Helper function to convert the input for GetActions to a list that can be used for delegates
- L227 _protected function_ `template <typename T> static TArray<TSoftObjectPtr<T>> GetTypedSoftObjectPtrs(const TArray<UObject*>& InObjects)`
- L241 _protected function_ `template <typename T> static TArray<T*> GetTypedObjectPtrs(const TArray<UObject*>& InObjects)`

### `Source/Developer/AssetTools/Public/AssetTypeActions_CSVAssetBase.h` (Public)


#### class `FAssetTypeActions_CSVAssetBase`  
`FAssetTypeActions_CSVAssetBase : public FAssetTypeActions_Base`  
_L12-28_
- reflection: `UE_DEPRECATED(5.2, "The AssetDefinition system is replacing AssetTypeActions and nothing replaced this, just subclass from UAssetDefinitionDefault. If you needed the ExecuteFindSourceFileInExplorer, you can now find that in FindSourceFileInExplorer.h. Please see the Conversion Guide in AssetDefinition.h")`
- inherits: `FAssetTypeActions_Base`
- L15 _public function_ `virtual FColor GetTypeColor() const override`
- L16 _public function_ `virtual uint32 GetCategories() override`
- L17 _public function_ `virtual bool IsImportedAsset() const override`
- L21 _protected prototype_ `void ExecuteFindSourceFileInExplorer(TArray<FString> Filenames, TArray<FString> OverrideExtensions);` — Handler for opening the source file for this asset
- L24 _protected prototype_ `bool CanExecuteFindSourceFileInExplorer(TArray<FString> Filenames, TArray<FString> OverrideExtensions) const;` — Determine whether the find source file in explorer editor command can execute or not
- L27 _protected prototype_ `bool VerifyFileExists(const FString& InFileName) const;` — Verify the specified filename exists

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ASSETTOOLS_API`

### `Source/Developer/AssetTools/Public/AssetTypeActivationOpenedMethod.h` (Public)


#### enum `EAssetTypeActivationOpenedMethod`  
`enum class EAssetTypeActivationOpenedMethod : uint8`  
_L16-20_
- reflection: `UENUM()`
- desc: Types of permissions allowed when attempting to open an asset in editor via activation (EAssetTypeActivationMethod)
- L18 _public enumerator_ `Edit`
- L19 _public enumerator_ `View`

### `Source/Developer/AssetTools/Public/AssetTypeCategories.h` (Public)


#### enum `EAssetTypeCategories::Type`  
`enum Type`  
_L15-36_
- L17 _public enumerator_ `None = 0`
- L18 _public enumerator_ `Basic = 1 << 0`
- L19 _public enumerator_ `Animation = 1 << 1`
- L20 _public enumerator_ `Materials = 1 << 2`
- L21 _public enumerator_ `Sounds = 1 << 3`
- L22 _public enumerator_ `Physics = 1 << 4`
- L23 _public enumerator_ `UI = 1 << 5`
- L24 _public enumerator_ `Misc = 1 << 6`
- L25 _public enumerator_ `Gameplay = 1 << 7`
- L26 _public enumerator_ `Blueprint = 1 << 8`
- L27 _public enumerator_ `Media = 1 << 9`
- L28 _public enumerator_ `Textures = 1 << 10`
- L29 _public enumerator_ `World = 1 << 11`
- L30 _public enumerator_ `FX = 1 << 12`
- L33 _public enumerator_ `FirstUser = 1 << 13` — Items below this will be allocated at runtime via RegisterAdvancedAssetCategory
- L34 _public enumerator_ `LastUser = 1 << 31`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace EAssetTypeCategories`

### `Source/Developer/AssetTools/Public/AssetViewUtils.h` (Public)


#### struct `AssetViewUtils::FLoadAssetsSettings`  
`struct FLoadAssetsSettings`  
_L22-38_
- L25 _public member_ `bool bAlwaysPromptBeforeLoading = false;` — Prompt the user with the number of unloaded assets before continuing to load
- L27 _public member_ `bool bShowFailureNotification = true;` — Show a notification to the user that some assets failed to load
- L31 _public member_ `bool bFollowRedirectors = false;` — Follow redirectors and return the target assets. We usually don't want to follow redirects when loading objects for the Content Browser.  It would allow a user to interact with a ghost/unverified asset as if it were still alive.
- L33 _public member_ `bool bAllowCancel = false;` — Allow the user to cancel the load operation
- L35 _public member_ `bool bLoadWorldPartitionMaps = false;` — Advanced setting: allow loading of world partition map packages.
- L37 _public member_ `bool bLoadAllExternalObjects = false;` — Advanced setting: load all external objects/actors with e.g. world partition map packages.

#### enum `AssetViewUtils::ELoadAssetsResult`  
`enum class ELoadAssetsResult : uint8`  
_L40-45_
- L42 _public enumerator_ `Success` — The user didn't cancel and all requested assets were successfully loaded
- L43 _public enumerator_ `Cancelled` — The user cancelled the load operation
- L44 _public enumerator_ `SomeFailed` — Some or all of the assets failed to load

#### struct `AssetViewUtils::FDeleteFolderParameters`  
`struct FDeleteFolderParameters`  
_L109-113_
- desc: Attempts to delete the specified folders and all assets inside them. Returns true if the operation succeeded.
- L111 _public member_ `TArray<FString> PathsToDelete;`
- L112 _public member_ `bool bShowConfirmationBeforeLoadingAssets = true;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AssetViewUtils`
- L14 _prototype_ `bool OpenEditorForAsset(const FString& ObjectPath);` (scope `AssetViewUtils`) — Loads the specified object if needed and opens the asset editor for it
- L17 _prototype_ `bool OpenEditorForAsset(UObject* Asset);` (scope `AssetViewUtils`) — Opens the asset editor for the specified asset
- L20 _prototype_ `bool OpenEditorForAsset(const TArray<UObject*>& Assets);` (scope `AssetViewUtils`) — Opens the asset editor for the specified assets
- L55 _prototype_ `ELoadAssetsResult LoadAssetsIfNeeded(TConstArrayView<FAssetData> Assets, TArray<UObject*>& LoadedObjects, const FLoadAssetsSettings& InSettings);` (scope `AssetViewUtils`) — Makes sure the specified assets are loaded into memory, with displayed progress and optional cancellation for the user. Prefer the overload taking FAssetData if possible. @param Assets The assets to load @param LoadedObjects The returned list of objects that were already loaded or loaded by this method. @return enum specifying whether the load was successful, cancelled or if some or all assets failed to load
- L56 _prototype_ `ELoadAssetsResult LoadAssetsIfNeeded(TConstArrayView<FString> ObjectPaths, TArray<UObject*>& LoadedObjects, const FLoadAssetsSettings& InSettings);` (scope `AssetViewUtils`)
- L57 _prototype_ `ELoadAssetsResult LoadAssetsIfNeeded(TConstArrayView<FSoftObjectPath> ObjectPaths, TArray<UObject*>& LoadedObjects, const FLoadAssetsSettings& InSettings);` (scope `AssetViewUtils`)
- L67 _prototype_ `bool LoadAssetsIfNeeded(const TArray<FString>& ObjectPaths, TArray<UObject*>& LoadedObjects, bool bAllowedToPromptToLoadAssets = true, bool bLoadRedirects = false);` (scope `AssetViewUtils`) — `UE_DEPRECATED(5.5, "Use LoadAssetsIfNeeded taking struct FLoadAssetsSettings instead.")` — Makes sure the specified assets are loaded into memory. @param ObjectPaths The paths to the objects to load. @param LoadedObjects The returned list of objects that were already loaded or loaded by this method. @return false if user canceled after being warned about loading very many packages.
- L76 _prototype_ `void GetUnloadedAssets(const TArray<FString>& ObjectPaths, TArray<FString>& OutUnloadedObjects);` (scope `AssetViewUtils`) — Determines the unloaded assets that need loading @param ObjectPaths		Paths to assets that may need to be loaded @param OutUnloadedObjects	List of the unloaded object paths @return true if the user should be prompted to load assets
- L84 _prototype_ `bool PromptToLoadAssets(const TArray<FString>& UnloadedObjects);` (scope `AssetViewUtils`) — Prompts the user to load the list of unloaded objects @param UnloadedObjects	The list of unloaded objects that we should prompt for loading @param true if the user allows the objects to be loaded
- L91 _prototype_ `void CopyAssets(const TArray<UObject*>& Assets, const FString& DestPath);` (scope `AssetViewUtils`) — Copies assets to a new path @param Assets The assets to copy @param DestPath The destination folder in which to copy the assets
- L100 _prototype_ `void MoveAssets(const TArray<UObject*>& Assets, const FString& DestPath, const FString& SourcePath = FString());` (scope `AssetViewUtils`) — Moves assets to a new path @param Assets The assets to move @param DestPath The destination folder in which to move the assets @param SourcePath If non-empty, this will specify the base folder which will cause the move to maintain folder structure
- L103 _prototype_ `int32 DeleteAssets(const TArray<UObject*>& AssetsToDelete);` (scope `AssetViewUtils`) — Attempts to deletes the specified assets. Returns the number of assets deleted
- L106 _prototype_ `bool DeleteFolders(const TArray<FString>& PathsToDelete);` (scope `AssetViewUtils`) — Attempts to delete the specified folders and all assets inside them. Returns true if the operation succeeded.
- L114 _prototype_ `bool DeleteFolders(const FDeleteFolderParameters& InOptions);` (scope `AssetViewUtils`)
- L117 _prototype_ `void GetAssetsInPaths(const TArray<FString>& InPaths, TArray<FAssetData>& OutAssetDataList);` (scope `AssetViewUtils`) — Gets an array of assets inside the specified folders
- L120 _prototype_ `bool SavePackages(const TArray<UPackage*>& Packages);` (scope `AssetViewUtils`) — Saves all the specified packages
- L123 _prototype_ `bool SaveDirtyPackages();` (scope `AssetViewUtils`) — Prompts to save all modified packages
- L126 _prototype_ `TArray<UPackage*> LoadPackages(const TArray<FString>& PackageNames);` (scope `AssetViewUtils`) — Loads all the specified packages
- L129 _prototype_ `bool RenameFolder(const FString& DestPath, const FString& SourcePath);` (scope `AssetViewUtils`) — Moves all assets from the source path to the destination path, preserving path structure, deletes source path afterwards if possible
- L132 _prototype_ `bool CopyFolders(const TArray<FString>& InSourcePathNames, const FString& DestPath);` (scope `AssetViewUtils`) — Copies all assets in all source paths to the destination path, preserving path structure
- L135 _prototype_ `bool MoveFolders(const TArray<FString>& InSourcePathNames, const FString& DestPath);` (scope `AssetViewUtils`) — Moves all assets in all source paths to the destination path, preserving path structure
- L143 _prototype_ `bool PrepareFoldersForDragDrop(const TArray<FString>& SourcePathNames, TMap< FString, TArray<UObject*> >& OutSourcePathToLoadedAssets);` (scope `AssetViewUtils`) — A helper function for folder drag/drop which loads all assets in a path (including sub-paths) and returns the assets found @param SourcePathNames				The paths to the folders to drag/drop @param OutSourcePathToLoadedAssets	The map of source folder paths to assets found
- L151 _prototype_ `void CaptureThumbnailFromViewport(FViewport* InViewport, const TArray<FAssetData>& InAssetsToAssign);` (scope `AssetViewUtils`) — Capture active viewport to thumbnail and assigns that thumbnail to incoming assets @param InViewport - viewport to sample from @param InAssetsToAssign - assets that should receive the new thumbnail ONLY if they are assets that use GenericThumbnails
- L158 _prototype_ `void ClearCustomThumbnails(const TArray<FAssetData>& InAssetsToAssign);` (scope `AssetViewUtils`) — Clears custom thumbnails for the selected assets @param InAssetsToAssign - assets that should have their thumbnail cleared
- L161 _prototype_ `bool AssetHasCustomThumbnail( const FAssetData& AssetData );` (scope `AssetViewUtils`) — Returns true if the specified asset that uses shared thumbnails has a thumbnail assigned to it
- L164 _prototype_ `bool IsProjectFolder(const FStringView InPath, const bool bIncludePlugins = false);` (scope `AssetViewUtils`) — Returns true if the passed-in path is a project folder
- L167 _prototype_ `bool IsEngineFolder(const FStringView InPath, const bool bIncludePlugins = false);` (scope `AssetViewUtils`) — Returns true if the passed-in path is a engine folder
- L170 _prototype_ `bool IsDevelopersFolder( const FStringView InPath );` (scope `AssetViewUtils`) — Returns true if the passed-in path is a developers folder
- L173 _prototype_ `bool IsPluginFolder(const FStringView InPath, EPluginLoadedFrom* OutPluginSource = nullptr);` (scope `AssetViewUtils`) — Returns true if the passed-in path is a plugin folder, optionally reporting where the plugin was loaded from
- L176 _prototype_ `TSharedPtr<IPlugin> GetPluginForFolder(const FStringView InPath);` (scope `AssetViewUtils`) — If the passed-in path is a plugin folder, then return its associated plugin
- L179 _prototype_ `void GetObjectsInAssetData(const TArray<FAssetData>& AssetList, TArray<UObject*>& OutDroppedObjects);` (scope `AssetViewUtils`) — Get all the objects in a list of asset data
- L182 _prototype_ `bool IsValidFolderName(const FString& FolderName, FText& Reason);` (scope `AssetViewUtils`) — Returns true if the supplied folder name can be used as part of a package name
- L185 _prototype_ `bool DoesFolderExist(const FString& FolderPath);` (scope `AssetViewUtils`) — Returns true if the path specified exists as a folder in the asset registry
- L194 _prototype_ `const TSharedPtr<FLinearColor> LoadColor(const FString& FolderPath);` (scope `AssetViewUtils`) — `UE_DEPRECATED(5.0, "LoadColor deprecated, please use GetPathColor")` — Loads the color of this path from the config @param FolderPath - The path to the folder @return The color the folder should appear as, will be NULL if not customized
- L202 _prototype_ `TOptional<FLinearColor> GetPathColor(const FString& FolderPath);` (scope `AssetViewUtils`) — Returns the color of this path from the config @param FolderPath - The path to the folder @return The color the folder should appear as, will be invalid if not customized
- L212 _prototype_ `void SaveColor(const FString& FolderPath, const TSharedPtr<FLinearColor>& FolderColor, bool bForceAdd = false);` (scope `AssetViewUtils`) — `UE_DEPRECATED(5.0, "SaveColor deprecated, please use SetPathColor")` — Saves the color of the path to the config @param FolderPath - The path to the folder @param FolderColor - The color the folder should appear as @param bForceAdd - If true, force the color to be added for the path
- L220 _prototype_ `void SetPathColor(const FString& FolderPath, TOptional<FLinearColor> FolderColor);` (scope `AssetViewUtils`) — Saves the color of the path to the config @param FolderPath - The path to the folder @param FolderColor - The color the folder should appear as
- L228 _prototype_ `bool HasCustomColors( TArray< FLinearColor >* OutColors = NULL );` (scope `AssetViewUtils`) — Checks to see if any folder has a custom color, optionally outputs them to a list @param OutColors - If specified, returns all the custom colors being used @return true, if custom colors are present
- L231 _prototype_ `FLinearColor GetDefaultColor();` (scope `AssetViewUtils`) — Gets the default color the folder should appear as
- L234 _prototype_ `bool IsValidObjectPathForCreate(const FString& ObjectPath, FText& OutErrorMessage, bool bAllowExistingAsset = false);` (scope `AssetViewUtils`) — Returns true if the specified path is available for object creation
- L237 _prototype_ `bool IsValidObjectPathForCreate(const FString& ObjectPath, const UClass* ObjectClass, FText& OutErrorMessage, bool bAllowExistingAsset = false);` (scope `AssetViewUtils`) — Returns true if the specified path is available for object creation
- L240 _prototype_ `bool IsValidFolderPathForCreate(const FString& FolderPath, const FString& NewFolderName, FText& OutErrorMessage, bool bAllowExistingFolder = false);` (scope `AssetViewUtils`) — Returns true if the specified folder name in the specified path is available for folder creation
- L243 _prototype_ `FString GetPackagePathWithinRoot(const FString& PackageName);` (scope `AssetViewUtils`) — Returns the relative path, from the workspace root, of the package
- L252 _prototype_ `int32 GetPackageLengthForCooking(const FString& PackageName, bool bIsInternalBuild, FString CookSubPath={});` (scope `AssetViewUtils`) — Returns the length of the computed cooked package name and path whether it's run on a build machine or locally. @param bIsInternalBuild Whether to behave like this being used within Epic and make certain assumptions about paths instead of using the local machine's workspace root path. @param CookSubPath Path relative to project root e.g. Saved/Cooked/SomePlatform
- L255 _prototype_ `bool IsValidPackageForCooking(const FString& PackageName, FText& OutErrorMessage);` (scope `AssetViewUtils`) — Checks to see whether the path is within the size restrictions for cooking
- L258 _prototype_ `int32 GetMaxAssetPathLen();` (scope `AssetViewUtils`) — Gets the maximum path length for an asset package file. Changes behavior based on whether the editor experimental setting for long paths is enabled.
- L261 _prototype_ `int32 GetMaxCookPathLen();` (scope `AssetViewUtils`) — Gets the maximum path length for a cooked file. Changes behavior based on whether the editor experimental setting for long paths is enabled.
- L265 _prototype_ `void SyncPackagesFromSourceControl(const TArray<FString>& PackageNames, bool bIsSyncLatestOperation);` (scope `AssetViewUtils`) — `UE_DEPRECATED(5.3, "The bIsSyncLatestOperation parameter is deprecated. Use SyncLatestFromSourceControl instead.")` — Syncs the specified packages from source control.
- L268 _prototype_ `bool SyncPackagesFromSourceControl(const TArray<FString>& PackageNames);` (scope `AssetViewUtils`) — Syncs the specified packages from source control.
- L271 _prototype_ `bool SyncPathsFromSourceControl(const TArray<FString>& Paths);` (scope `AssetViewUtils`) — Syncs the specified paths from source control.
- L274 _prototype_ `bool SyncRevisionFromSourceControl(const FString& Revision);` (scope `AssetViewUtils`) — Syncs a specific revision from source control.
- L277 _prototype_ `bool SyncLatestFromSourceControl();` (scope `AssetViewUtils`) — Syncs latest from source control.
- L280 _prototype_ `void ShowErrorNotifcation(const FText& InErrorMsg);` (scope `AssetViewUtils`) — Show an error notification toast if the given error message is not empty
- L283 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAlwaysShowPath, const FString& );` — Callback used when a folder should be forced to be visible in the Content Browser
- L283 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAlwaysShowPath, const FString& );` (scope `AssetViewUtils`) — Callback used when a folder should be forced to be visible in the Content Browser
- L284 _prototype_ `FOnAlwaysShowPath& OnAlwaysShowPath();` (scope `AssetViewUtils`)
- L287 _typedef_ `using FMovedContentFolder = TTuple<FString , FString >;` (scope `AssetViewUtils`) — Called when a folder is moved or renamed
- L288 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFolderPathChanged, TArrayView<const FMovedContentFolder> );`
- L288 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFolderPathChanged, TArrayView<const FMovedContentFolder> );` (scope `AssetViewUtils`)
- L289 _prototype_ `FOnFolderPathChanged& OnFolderPathChanged();` (scope `AssetViewUtils`)
- L292 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSyncStart);` — Called when a sync from AssetViewUtils starts
- L292 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSyncStart);` (scope `AssetViewUtils`) — Called when a sync from AssetViewUtils starts
- L294 _prototype_ `FOnSyncStart& OnSyncStart();` (scope `AssetViewUtils`) — `UE_DEPRECATED(5.8, "This is no longer supported")`
- L301 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSyncFinish, bool , const TArray<FString>* );` — Called when a sync from AssetViewUtils finishes If Files is non-nullptr, those are the files affected by the sync. If Files is nullptr, assume any file might have been changed by the sync.
- L301 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSyncFinish, bool , const TArray<FString>* );` (scope `AssetViewUtils`) — Called when a sync from AssetViewUtils finishes If Files is non-nullptr, those are the files affected by the sync. If Files is nullptr, assume any file might have been changed by the sync.
- L303 _prototype_ `FOnSyncFinish& OnSyncFinish();` (scope `AssetViewUtils`) — `UE_DEPRECATED(5.8, "This is no longer supported")`

### `Source/Developer/AssetTools/Public/ClassTypeActions_Base.h` (Public)


#### class `FClassTypeActions_Base`  
`class FClassTypeActions_Base : public IClassTypeActions`  
_L12-21_
- inherits: `IClassTypeActions`
- desc: A base class for all ClassTypeActions. Provides helper functions useful for many types. Deriving from this class is optional.
- L16 _public function_ `virtual TSharedPtr<class SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override`

### `Source/Developer/AssetTools/Public/CollectionAssetManagement.h` (Public)


#### class `FCollectionAssetManagement`  
`class FCollectionAssetManagement`  
_L15-83_
- desc: Handles the collection management for the given assets
- L20 _public prototype_ `FCollectionAssetManagement();` — `UE_DEPRECATED(5.6, "Use the ICollectionContainer constructor instead.")` — Constructor
- L21 _public prototype_ `explicit FCollectionAssetManagement(const TSharedRef<ICollectionContainer>& InCollectionContainer);`
- L22 _public prototype_ `FCollectionAssetManagement(const FCollectionAssetManagement&) = delete;`
- L25 _public prototype_ `~FCollectionAssetManagement();` — Destructor
- L27 _public prototype_ `FCollectionAssetManagement& operator=(const FCollectionAssetManagement&) = delete;`
- L30 _public prototype_ `void SetCurrentAssets(const TArray<FAssetData>& CurrentAssets);` — Set the assets that we are currently observing and managing the collection state of
- L33 _public prototype_ `void SetCurrentAssetPaths(const TArray<FSoftObjectPath>& CurrentAssets);` — Set the asset paths that we are currently observing and managing the collection state of
- L36 _public prototype_ `int32 GetCurrentAssetCount() const;` — Get the number of assets in the current set
- L39 _public prototype_ `void AddCurrentAssetsToCollection(FCollectionNameType InCollectionKey);` — Add the current assets to the given collection
- L42 _public prototype_ `void RemoveCurrentAssetsFromCollection(FCollectionNameType InCollectionKey);` — Remove the current assets from the given collection
- L45 _public prototype_ `bool IsCollectionEnabled(FCollectionNameType InCollectionKey) const;` — Return whether or not the given collection should be enabled in any management UIs
- L48 _public prototype_ `ECheckBoxState GetCollectionCheckState(FCollectionNameType InCollectionKey) const;` — Get the check box state the given collection should use in any management UIs
- L52 _private prototype_ `void UpdateAssetManagementState();` — Update the internal state used to track the check box status for each collection
- L55 _private prototype_ `void HandleCollectionRenamed(ICollectionContainer&, const FCollectionNameType& OriginalCollection, const FCollectionNameType& NewCollection);` — Handles an on collection renamed event
- L58 _private prototype_ `void HandleCollectionUpdated(ICollectionContainer&, const FCollectionNameType& Collection);` — Handles an on collection updated event
- L61 _private prototype_ `void HandleCollectionDestroyed(ICollectionContainer&, const FCollectionNameType& Collection);` — Handles an on collection destroyed event
- L64 _private prototype_ `void HandleAssetsAddedToCollection(ICollectionContainer&, const FCollectionNameType& Collection, TConstArrayView<FSoftObjectPath> AssetsAdded);` — Handles assets being added to a collection
- L67 _private prototype_ `void HandleAssetsRemovedFromCollection(ICollectionContainer&, const FCollectionNameType& Collection, TConstArrayView<FSoftObjectPath> AssetsRemoved);` — Handles assets being removed from a collection
- L69 _private member_ `TSharedRef<ICollectionContainer> CollectionContainer;`
- L72 _private member_ `TSet<FSoftObjectPath> CurrentAssetPaths;` — Set of asset paths that we are currently observing and managing the collection state of
- L75 _private member_ `TMap<FCollectionNameType, ECheckBoxState> AssetManagementState;` — Mapping between a collection and its asset management state (based on the current assets). A missing item is assumed to be unchecked
- L78 _private member_ `FDelegateHandle OnCollectionRenamedHandle;` — Delegate handles
- L79 _private member_ `FDelegateHandle OnCollectionDestroyedHandle;`
- L80 _private member_ `FDelegateHandle OnCollectionUpdatedHandle;`
- L81 _private member_ `FDelegateHandle OnAssetsAddedHandle;`
- L82 _private member_ `FDelegateHandle OnAssetsRemovedHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ASSETTOOLS_API`

### `Source/Developer/AssetTools/Public/FindSourceFileInExplorer.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace AssetTools` (scope `UE`)
- L13 _prototype_ `void ExecuteFindSourceFileInExplorer(TArray<FString> Filenames, TArray<FString> OverrideExtensions);` (scope `UE::AssetTools`)
- L14 _prototype_ `bool CanExecuteFindSourceFileInExplorer(TArray<FString> Filenames, TArray<FString> OverrideExtensions);` (scope `UE::AssetTools`)

### `Source/Developer/AssetTools/Public/IAssetTools.h` (Public)


#### enum `EAssetClassAction`  
`enum class EAssetClassAction : uint8`  
_L50-61_
- reflection: `UENUM()`
- L53 _public enumerator_ `CreateAsset` — Whether an action can be created by an AssetTypeAction
- L55 _public enumerator_ `ViewAsset` — Whether an asset can be viewed in the content browser
- L57 _public enumerator_ `ImportAsset` — Whether an asset can be imported
- L59 _public enumerator_ `ExportAsset` — Whether an asset can be exported
- L60 _public enumerator_ `AllAssetActions`

#### enum `EAssetRenameResult`  
`enum class EAssetRenameResult : uint8`  
_L64-72_
- reflection: `UENUM()`
- L67 _public enumerator_ `Failure` — The asset rename failed
- L69 _public enumerator_ `Success` — The asset rename succeeded
- L71 _public enumerator_ `Pending` — The asset rename is still pending, likely due to outstanding asset discovery

#### enum `ERedirectFixupMode`  
`enum class ERedirectFixupMode`  
_L75-86_
- reflection: `UENUM()`
- L78 _public enumerator_ `DeleteFixedUpRedirectors` — Remove fully fixed up redirectors after the fixup process is done
- L81 _public enumerator_ `LeaveFixedUpRedirectors` — Leave the redirectors around even if no longer locally referenced
- L85 _public enumerator_ `PromptForDeletingRedirectors` — If permitted, prompt the user to delete any redirectors that are no longer locally referenced. Projects may disable deletion if it interferes with their workflow/branch setup/etc.

#### struct `FAssetRenameData`  
`struct FAssetRenameData`  
_L89-152_
- reflection: `USTRUCT(BlueprintType)`
- L95 _public member_ `TWeakObjectPtr<UObject> Asset;` — `UPROPERTY(BlueprintReadWrite, Category=AssetRenameData)` — Object being renamed
- L99 _public member_ `FString NewPackagePath;` — `UPROPERTY(BlueprintReadWrite, Category = AssetRenameData)` — New path to package without package name, ie /Game/SubDirectory
- L103 _public member_ `FString NewName;` — `UPROPERTY(BlueprintReadWrite, Category = AssetRenameData)` — New package and asset name, new object path will be PackagePath/NewName.NewName
- L107 _public member_ `FSoftObjectPath OldObjectPath;` — `UPROPERTY()` — Full path to old name, in form /Game/SubDirectory/OldName.OldName:SubPath
- L111 _public member_ `FSoftObjectPath NewObjectPath;` — `UPROPERTY()` — New full path, may be a SubObject
- L115 _public member_ `bool bOnlyFixSoftReferences;` — `UPROPERTY()` — If true, only fix soft references. This will work even if Asset is null because it has already been renamed
- L119 _public member_ `bool bAlsoRenameLocalizedVariants;` — `UPROPERTY()` — If true, will also try to rename all localized variants with corresponding paths
- L121 _public function_ `FAssetRenameData() : bOnlyFixSoftReferences(false) , bAlsoRenameLocalizedVariants(false)`
- L127 _public function_ `FAssetRenameData(const TWeakObjectPtr<UObject>& InAsset, const FString& InNewPackagePath, const FString& InNewName) : Asset(InAsset) , NewPackagePath(InNewPackagePath) , NewName(InNewName) , bOnlyFixSoftReferences(false) , bAlsoRenameLocalizedVariants(false)` — These constructors leave some fields empty, they are fixed up inside AssetRenameManager
- L136 _public function_ `FAssetRenameData(const TWeakObjectPtr<UObject>& InAsset, const FString& InNewPackagePath, const FString& InNewName, bool bInOnlyFixSoftReferences, bool bInAlsoRenameLocalizedVariants) : Asset(InAsset) , NewPackagePath(InNewPackagePath) , NewName(InNewName) , bOnlyFixSoftReferences(bInOnlyFixSoftReferences) , bAlsoRenameLocalizedVariants(bInAlsoRenameLocalizedVariants)` — These constructors leave some fields empty, they are fixed up inside AssetRenameManager
- L145 _public function_ `FAssetRenameData(const FSoftObjectPath& InOldObjectPath, const FSoftObjectPath& InNewObjectPath, bool bInOnlyFixSoftReferences = false, bool bInAlsoRenameLocalizedVariants = false) : OldObjectPath(InOldObjectPath) , NewObjectPath(InNewObjectPath) , bOnlyFixSoftReferences(bInOnlyFixSoftReferences) , bAlsoRenameLocalizedVariants(bInAlsoRenameLocalizedVariants)`

#### struct `FAdvancedAssetCategory`  
`struct FAdvancedAssetCategory`  
_L161-171_
- L163 _public member_ `EAssetTypeCategories::Type CategoryType;`
- L164 _public member_ `FText CategoryName;`
- L166 _public function_ `FAdvancedAssetCategory(EAssetTypeCategories::Type InCategoryType, FText InCategoryName) : CategoryType(InCategoryType) , CategoryName(InCategoryName)`

#### struct `FAdvancedCopyParams`  
`struct FAdvancedCopyParams`  
_L174-226_
- reflection: `USTRUCT()`
- L178 _public member_ `bool bShouldForceSave = false;`
- L179 _public member_ `bool bCopyOverAllDestinationOverlaps = false;`
- L180 _public member_ `bool bShouldSuppressUI = false;`
- L181 _public member_ `bool bShouldCheckForDependencies = false;`
- L182 _public member_ `FAdvancedCopyCompletedEvent OnCopyComplete;`
- L185 _public function_ `const TArray<FName>& GetSelectedPackageNames() const` — `UE_DEPRECATED(5.0, "This function has been deprecated, use GetSelectedPackageOrFolderNames")`
- L190 _public function_ `const TArray<FName>& GetSelectedPackageOrFolderNames() const`
- L195 _public function_ `const FString& GetDropLocationForAdvancedCopy() const`
- L200 _public function_ `const TArray<UAdvancedCopyCustomization*>& GetCustomizationsToUse() const`
- L205 _public function_ `void AddCustomization(UAdvancedCopyCustomization* InCustomization)`
- L210 _public function_ `FAdvancedCopyParams(TArray<FName> InSelectedPackageOrFolderNames, FString InDropLocationForAdvancedCopy) : bShouldForceSave(false) , bCopyOverAllDestinationOverlaps(true) , bShouldSuppressUI(false) , bShouldCheckForDependencies(true) , SelectedPackageOrFolderNames(InSelectedPackageOrFolderNames) , DropLocationForAdvancedCopy(InDropLocationForAdvancedCopy)`
- L220 _public function_ `FAdvancedCopyParams()`
- L223 _private member_ `TArray<FName> SelectedPackageOrFolderNames;`
- L224 _private member_ `TArray<UAdvancedCopyCustomization*> CustomizationsToUse;`
- L225 _private member_ `FString DropLocationForAdvancedCopy;`

#### enum `EAssetMigrationConflict`  
`enum class EAssetMigrationConflict : uint8`  
_L230-238_
- reflection: `UENUM()`
- L233 _public enumerator_ `Skip` — Skip Assets
- L235 _public enumerator_ `Overwrite` — Overwrite Assets
- L237 _public enumerator_ `Cancel` — Cancel the whole Migration

#### struct `FMigrationOptions`  
`struct FMigrationOptions`  
_L241-266_
- reflection: `USTRUCT(BlueprintType)`
- L247 _public member_ `bool bPrompt;` — `UPROPERTY(BlueprintReadWrite, Category = MigrationOptions)` — Prompt user for confirmation (always false through scripting)
- L251 _public member_ `bool bIgnoreDependencies;` — `UPROPERTY(BlueprintReadWrite, Category = MigrationOptions)` — Ignore dependencies of assets, only migrate the given assets. usefull for automation. This will not migrate the actors of a OFPA (one file per actor) level
- L255 _public member_ `EAssetMigrationConflict AssetConflict;` — `UPROPERTY(BlueprintReadWrite, Category = MigrationOptions)` — What to do when Assets are conflicting on the destination
- L259 _public member_ `FString OrphanFolder;` — `UPROPERTY(BlueprintReadWrite, Category = MigrationOptions)` — Destination for assets that don't have a corresponding content folder. If left empty those assets are not migrated. (Not used by the new migration)
- L261 _public function_ `FMigrationOptions() : bPrompt(false) , bIgnoreDependencies(false) , AssetConflict(EAssetMigrationConflict::Skip)`

#### class `UAssetTools`  
`class UAssetTools : public UInterface`  
_L273-276_
- reflection: `UINTERFACE(MinimalApi, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IAssetTools`  
`class IAssetTools`  
_L283-889_
- L288 _public prototype_ `static IAssetTools& Get();`
- L290 _public prototype_ `DECLARE_DELEGATE(FOnAssetsDiscovered);`
- L293 _public prototype_ `virtual void RegisterAssetTypeActions(const TSharedRef<IAssetTypeActions>& NewActions) = 0;` — Registers an asset type actions object so it can provide information about and actions for asset types.
- L296 _public prototype_ `virtual void UnregisterAssetTypeActions(const TSharedRef<IAssetTypeActions>& ActionsToRemove) = 0;` — Unregisters an asset type actions object. It will no longer provide information about or actions for asset types.
- L299 _public prototype_ `virtual void GetAssetTypeActionsList(TArray<TWeakPtr<IAssetTypeActions>>& OutAssetTypeActionsList) const = 0;` — Generates a list of currently registered AssetTypeActions
- L302 _public prototype_ `virtual TWeakPtr<IAssetTypeActions> GetAssetTypeActionsForClass(const UClass* Class) const = 0;` — Gets the appropriate AssetTypeActions for the supplied class
- L304 _public prototype_ `virtual TSharedPtr<ILocalizedAssetTools> GetLocalizedAssetTools() const = 0;`
- L306 _public prototype_ `virtual bool CanLocalize(const UClass* Class) const = 0;`
- L308 _public prototype_ `virtual TOptional<FLinearColor> GetTypeColor(const UClass* Class) const = 0;`
- L311 _public prototype_ `virtual TArray<TWeakPtr<IAssetTypeActions>> GetAssetTypeActionsListForClass(const UClass* Class) const = 0;` — Gets the list of appropriate AssetTypeActions for the supplied class
- L317 _public prototype_ `virtual EAssetTypeCategories::Type RegisterAdvancedAssetCategory(FName CategoryKey, FText CategoryDisplayName) = 0;` — Allocates a Category bit for a user-defined Category, or EAssetTypeCategories::Misc if all available bits are allocated. Ignores duplicate calls with the same CategoryKey (returns the existing bit but does not change the display name).
- L320 _public prototype_ `virtual EAssetTypeCategories::Type FindAdvancedAssetCategory(FName CategoryKey) const = 0;` — Returns the allocated Category bit for a user-specified Category, or EAssetTypeCategories::Misc if it doesn't exist
- L323 _public prototype_ `virtual void GetAllAdvancedAssetCategories(TArray<FAdvancedAssetCategory>& OutCategoryList) const = 0;` — Returns the list of all advanced asset categories
- L326 _public prototype_ `virtual void RegisterClassTypeActions(const TSharedRef<IClassTypeActions>& NewActions) = 0;` — Registers a class type actions object so it can provide information about and actions for class asset types.
- L329 _public prototype_ `virtual void UnregisterClassTypeActions(const TSharedRef<IClassTypeActions>& ActionsToRemove) = 0;` — Unregisters a class type actions object. It will no longer provide information about or actions for class asset types.
- L332 _public prototype_ `virtual void GetClassTypeActionsList(TArray<TWeakPtr<IClassTypeActions>>& OutClassTypeActionsList) const = 0;` — Generates a list of currently registered ClassTypeActions
- L335 _public prototype_ `virtual TWeakPtr<IClassTypeActions> GetClassTypeActionsForClass(UClass* Class) const = 0;` — Gets the appropriate ClassTypeActions for the supplied class
- L349 _public prototype_ `virtual UObject* CreateAsset(const FString& AssetName, const FString& PackagePath, UClass* AssetClass, UFactory* Factory, FName CallingContext = NAME_None, bool bOverwriteExisting = false) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Creates an asset with the specified name, path, and factory @param AssetName the name of the new asset @param PackagePath the package that will contain the new asset @param AssetClass the class of the new asset @param Factory the factory that will build the new asset @param CallingContext optional name of the module or method calling CreateAsset() - this is passed to the factory @param bOverwriteExisting if set to true, this will overwrite an existing object without prompting @return the new asset or NULL if it fails
- L365 _public function_ `virtual bool CreateAssetAsync(const FString& AssetName, const FString& PackagePath, UClass* AssetClass, UFactory* Factory, FAssetCreateCompleteDynamic OnComplete, FAssetCreateCancelledDynamic OnCancelled, FName CallingContext = NAME_None, bool bOverwriteExisting = false)` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Creates an asset with the specified name, path, and factory asynchronously @param AssetName the name of the new asset @param PackagePath the package that will contain the new asset @param AssetClass the class of the new asset @param Factory the factory that will build the new asset @param OnComplete called when the factory has successfully created the asset @param OnCancelled called if the asynchronous method is cancelled @param CallingContext optional name of the module or method calling CreateAsset() - this is passed to the factory @param bOverwriteExisting if set to true, this will overwrite an existing object without prompting @return the new asset or NULL if it fails
- L379 _public prototype_ `virtual bool CreateAssetAsync(const FString& AssetName, const FString& PackagePath, UClass* AssetClass, UFactory* Factory, FAssetCreateComplete OnComplete = FAssetCreateComplete(), FAssetCreateCancelled OnCancelled = FAssetCreateCancelled(), FName CallingContext = NAME_None, bool bOverwriteExisting = false) = 0;`
- L389 _public prototype_ `virtual void CreateAssetsFrom(TConstArrayView<UObject*> SourceObjects, UClass* CreateAssetType, const FString& DefaultSuffix, TFunctionRef<UFactory*(UObject*)> FactoryConstructor, FName CallingContext = NAME_None) = 0;` — Creates one or more assets using the source objects as the basis for the next type.  This is a common enough operation it needed a utility.  In the case that you only have a single SourceObject, we'll lean on the content browser to create the asset and focus you to it so you can rename it inline.  However in the case that multiple assets get created we'll construct each one and then sync the content browser to them. You can return null for a factory if you need to skip a given SourceObject.
- L400 _public function_ `template<typename SourceObjectType, typename = typename TEnableIf<TIsDerivedFrom<SourceObjectType, UObject>::Value>::Type> void CreateAssetsFrom(TConstArrayView<SourceObjectType*> SourceObjects, UClass* CreateAssetType, const FString& DefaultSuffix, TFunctionRef<UFactory*(SourceObjectType*)> FactoryConstructor, FName CallingContext = NAME_None)` — Creates one or more assets using the source objects as the basis for the next type.  This is a common enough operation it needed a utility.  In the case that you only have a single SourceObject, we'll lean on the content browser to create the asset and focus you to it so you can rename it inline.  However in the case that multiple assets get created we'll construct each one and then sync the content browser to them. You can return null for a factory if you need to skip a given SourceObject.
- L407 _public prototype_ `virtual UObject* CreateAssetWithDialog(const FString& AssetName, const FString& PackagePath, UClass* AssetClass, UFactory* Factory, FName CallingContext = NAME_None, const bool bCallConfigureProperties = true) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Opens an asset picker dialog and creates an asset with the specified name and path
- L410 _public prototype_ `virtual UObject* CreateAssetWithDialog(UClass* AssetClass, UFactory* Factory, FName CallingContext = NAME_None) = 0;` — Opens an asset picker dialog and creates an asset with the path chosen in the dialog
- L417 _public function_ `virtual bool CreateAssetWithDialogAsync(const FString& AssetName, const FString& PackagePath, UClass* AssetClass, UFactory* Factory, FAssetCreateCompleteDynamic OnComplete, FAssetCreateCancelledDynamic OnCancelled, FName CallingContext = NAME_None)` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Opens an async dialog to create an asset. @returns true if the process was started successfully.
- L430 _public prototype_ `virtual bool CreateAssetWithDialogAsync(const FString& AssetName, const FString& PackagePath, UClass* AssetClass, UFactory* Factory, FAssetCreateComplete OnComplete = FAssetCreateComplete(), FAssetCreateCancelled OnCancelled = FAssetCreateCancelled(), FName CallingContext = NAME_None) = 0;`
- L436 _public prototype_ `virtual bool CreateAssetWithDialogAsync(UClass* AssetClass, UFactory* Factory, FAssetCreateComplete OnComplete = FAssetCreateComplete(), FAssetCreateCancelled OnCancelled = FAssetCreateCancelled(), FName CallingContext = NAME_None) = 0;` — Opens an async dialog to create an asset. @returns true if the process was started successfully.
- L440 _public prototype_ `virtual UObject* DuplicateAssetWithDialog(const FString& AssetName, const FString& PackagePath, UObject* OriginalObject) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Opens an asset picker dialog and creates an asset with the specified name and path. Uses OriginalObject as the duplication source.
- L447 _public prototype_ `virtual UObject* DuplicateAssetWithDialogAndTitle(const FString& AssetName, const FString& PackagePath, UObject* OriginalObject, FText DialogTitle) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Opens an asset picker dialog and creates an asset with the specified name and path. Uses OriginalObject as the duplication source. Uses DialogTitle as the dialog's title.
- L451 _public prototype_ `virtual UObject* DuplicateAsset(const FString& AssetName, const FString& PackagePath, UObject* OriginalObject) = 0;` — `UFUNCTION(BlueprintCallable, Category="Editor Scripting | Asset Tools")` — Creates an asset with the specified name and path. Uses OriginalObject as the duplication source.
- L454 _public prototype_ `virtual void SetCreateAssetsAsExternallyReferenceable(bool bValue) = 0;` — Controls whether or not newly created assets are made externally referneceable or not
- L457 _public prototype_ `virtual bool GetCreateAssetsAsExternallyReferenceable() = 0;` — Gets whether all assets being made at any location are externally referenceable or not
- L460 _public prototype_ `virtual bool ShouldCreateAssetsAsExternallyReferenceableForPath(const FStringView AssetPath) const = 0;` — Gets whether assets being made at this location are externally referenceable or not
- L463 _public prototype_ `virtual UE::AssetTools::FShouldCreateAssetsAsExternallyReferenceableForPath& GetOnShouldCreateAssetsAsExternallyReferenceableForPath() = 0;` — Delegate to control whether assets being made at a specific location are externally referenceable or not
- L466 _public prototype_ `virtual bool IsDiscoveringAssetsInProgress() const = 0;` — Gets whether assets registry is still loading assets or not
- L469 _public prototype_ `virtual void OpenDiscoveringAssetsDialog(const FOnAssetsDiscovered& InOnAssetsDiscovered) = 0;` — Opens a dialog asking the user to wait while assets are being discovered
- L473 _public prototype_ `virtual bool RenameAssets(const TArray<FAssetRenameData>& AssetsAndNames) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Renames assets using the specified names.
- L477 _public prototype_ `virtual EAssetRenameResult RenameAssetsWithDialog(const TArray<FAssetRenameData>& AssetsAndNames, bool bAutoCheckout = false) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Renames assets using the specified names.
- L481 _public prototype_ `virtual void FindSoftReferencesToObject(FSoftObjectPath TargetObject, TArray<UObject*>& ReferencingObjects) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Returns list of objects that soft reference the given soft object path. This will load assets into memory to verify
- L484 _public prototype_ `virtual void FindSoftReferencesToObjects(const TArray<FSoftObjectPath>& TargetObjects, TMap<FSoftObjectPath, TArray<UObject*>>& ReferencingObjects) = 0;` — Returns list of objects that soft reference the given soft object paths. This will load assets into memory to verify
- L493 _public prototype_ `virtual void RenameReferencingSoftObjectPaths(const TArray<UPackage *> PackagesToCheck, const TMap<FSoftObjectPath, FSoftObjectPath>& AssetRedirectorMap) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Function that renames all FSoftObjectPath object with the old asset path to the new one. @param PackagesToCheck Packages to check for referencing FSoftObjectPath. @param AssetRedirectorMap Map from old asset path to new asset path
- L496 _public prototype_ `virtual FAssetPostRenameEvent& OnAssetPostRename() = 0;` — Event issued at the end of the rename process
- L505 _public prototype_ `virtual TArray<UObject*> ImportAssetsWithDialog(const FString& DestinationPath) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Opens a file open dialog to choose files to import to the destination path. @param DestinationPath	Path to import files to @return list of successfully imported assets
- L513 _public prototype_ `virtual void ImportAssetsWithDialogAsync(const FString& DestinationPath) = 0;` — Opens a file open dialog to choose files to import to the destination path. It differ from ImportAssetsWithDialog by allowing an async import when it's available @param DestinationPath	Path to import files to
- L525 _public prototype_ `virtual TArray<UObject*> ImportAssets(const TArray<FString>& Files, const FString& DestinationPath, UFactory* ChosenFactory = NULL, bool bSyncToBrowser = true, TArray<TPair<FString, FString>>* FilesAndDestinations = nullptr, bool bAllowAsyncImport = false, bool bSceneImport = false) const = 0;` — Imports the specified files to the destination path. @param Files				Files to import @param DestinationPath	destination path for imported files @param ChosenFactory		Specific factory to use for object creation @param bSyncToBrowser	If true sync content browser to first imported asset after import @param bAllowAsyncImport	This allow the import code to use a async importer if enabled. (Note doing so will ignore the ChosenFactory arguments (If you want a async import prefer the InterchangeManager api)) @return list of successfully imported assets
- L534 _public prototype_ `virtual TArray<UObject*> ImportAssetsAutomated( const UAutomatedAssetImportData* ImportData) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Imports assets using data specified completely up front.  Does not ever ask any questions of the user or show any modal error messages @param AutomatedImportData	Data that specifies how to import each file @return list of successfully imported assets
- L542 _public prototype_ `virtual void ImportAssetTasks(const TArray<UAssetImportTask*>& ImportTasks) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Imports assets using tasks specified. @param ImportTasks	Tasks that specify how to import each file
- L551 _public prototype_ `virtual void ExportAssets(const TArray<FString>& AssetsToExport, const FString& ExportPath) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Exports the specified objects to file. @param	AssetsToExport					List of full asset names (e.g /Game/Path/Asset) to export @param	ExportPath						The directory path to export to.
- L559 _public prototype_ `virtual void ExportAssets(const TArray<UObject*>& AssetsToExport, const FString& ExportPath) const = 0;` — Exports the specified objects to file. @param	AssetsToExport					List of assets to export @param	ExportPath						The directory path to export to.
- L567 _public prototype_ `virtual void ExportAssetsWithCleanFilename(const TArray<UObject*>& AssetsToExport, const FString& ExportPath) const = 0;` — Exports the specified objects to file using the clean filename as the saved filename. @param	AssetsToExport					List of assets to export @param	ExportPath						The directory path to export to.
- L576 _public prototype_ `virtual void ExportAssetsWithDialog(const TArray<FString>& AssetsToExport, bool bPromptForIndividualFilenames) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Exports the specified objects to file. First prompting the user to pick an export directory and optionally prompting the user to pick a unique directory per file @param	AssetsToExport					List of assets to export @param	ExportPath						The directory path to export to.
- L584 _public prototype_ `virtual void ExportAssetsWithDialog(const TArray<UObject*>& AssetsToExport, bool bPromptForIndividualFilenames) = 0;` — Exports the specified objects to file. First prompting the user to pick an export directory and optionally prompting the user to pick a unique directory per file @param	AssetsToExport					List of full asset names (e.g /Game/Path/Asset) to export @param	ExportPath						The directory path to export to.
- L592 _public prototype_ `virtual bool CanExportAssets(const TArray<FAssetData>& AssetsToExport) const = 0;` — Check if specified assets can be exported. @param	AssetsToExport					List of assets to export @return true if all assets specified can be exported
- L596 _public prototype_ `virtual void CreateUniqueAssetName(const FString& InBasePackageName, const FString& InSuffix, FString& OutPackageName, FString& OutAssetName) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Creates a unique package and asset name taking the form InBasePackageName+InSuffix
- L599 _public prototype_ `virtual bool AssetUsesGenericThumbnail(const FAssetData& AssetData) const = 0;` — Returns true if the specified asset uses a stock thumbnail resource
- L609 _public prototype_ `virtual void DiffAgainstDepot(UObject* InObject, const FString& InPackagePath, const FString& InPackageName) const = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Try to diff the local version of an asset against the latest one from the depot @param InObject - The object we want to compare against the depot @param InPackagePath - The fullpath to the package @param InPackageName - The name of the package
- L613 _public prototype_ `virtual void DiffAssets(UObject* OldAsset, UObject* NewAsset, const struct FRevisionInfo& OldRevision, const struct FRevisionInfo& NewRevision) const = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Try and diff two assets using class-specific tool. Will do nothing if either asset is NULL, or they are not the same class.
- L616 _public prototype_ `virtual FString DumpAssetToTempFile(UObject* Asset) const = 0;` — Util for dumping an asset to a temporary text file. Returns absolute filename to temp file
- L627 _public prototype_ `virtual bool CreateDiffProcess(const FString& DiffCommand, const FString& OldTextFilename, const FString& NewTextFilename, const FString& DiffArgs = FString("")) const = 0;` — Attempt to spawn Diff tool as external process @param DiffCommand -		Command used to launch the diff tool @param OldTextFilename - File path to original file @param NewTextFilename - File path to new file @param DiffArgs -		Any extra command line arguments (defaulted to empty) @return Returns true if the process has successfully been created.
- L630 _public prototype_ `virtual void MigratePackages(const TArray<FName>& PackageNamesToMigrate) const = 0;` — Migrate packages to another game content folder
- L634 _public prototype_ `virtual void MigratePackages(const TArray<FName>& PackageNamesToMigrate, const FString& DestinationPath, const struct FMigrationOptions& Options = FMigrationOptions()) const = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools", BlueprintPure = false)` — Migrate packages and dependencies to another folder
- L637 _public prototype_ `virtual void MigratePackages(const TArray<FName>& PackageNamesToMigrate, const FString& DestinationPath, TSet<FName> AllDependenciesToMigrate, TSet<FName> ExcludedDependencies, const struct FMigrationOptions& Options = FMigrationOptions()) const = 0;` — Migrate packages and dependencies to another folder
- L640 _public prototype_ `virtual void BuildMigrateDependencies(const TArray<FName>& PackageNamesToMigrate, TSet<FName>& OutAllDependenciesToMigrate, TSet<FName>& OutExcludedDependencies) const = 0;` — Build dependency packages and excluded dependencies from a list of packages to migrate
- L646 _public prototype_ `virtual UE::AssetTools::FOnPackageMigration& GetOnPackageMigration() = 0;` — Event called when some packages are migrated Note this is only true when AssetTools.UseNewPackageMigration is true
- L649 _public prototype_ `virtual void BeginAdvancedCopyPackages(const TArray<FName>& InputNamesToCopy, const FString& TargetPath) const = 0;` — Copy packages and dependencies to another folder
- L652 _public prototype_ `virtual void BeginAdvancedCopyPackages(const TArray<FName>& InputNamesToCopy, const FString& TargetPath, const FAdvancedCopyCompletedEvent& OnCopyComplete) const = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools", BlueprintPure = false, meta = (AutoCreateRefTerm = "OnCopyComplete"))`
- L658 _public prototype_ `virtual void FixupReferencers(const TArray<UObjectRedirector*>& Objects, bool bCheckoutDialogPrompt = true, ERedirectFixupMode FixupMode = ERedirectFixupMode::DeleteFixedUpRedirectors) const = 0;` — Fix up references to the specified redirectors. @param bCheckoutDialogPrompt indicates whether to prompt the user with files checkout dialog or silently attempt to checkout all necessary files.
- L661 _public prototype_ `virtual bool IsFixupReferencersInProgress() const = 0;` — Returns whether redirectors are being fixed up.
- L664 _public prototype_ `virtual void ExpandDirectories(const TArray<FString>& Files, const FString& DestinationPath, TArray<TPair<FString, FString>>& FilesAndDestinations) const = 0;` — Expands any folders found in the files list, and returns a flattened list of destination paths and files.  Mirrors directory structure.
- L667 _public prototype_ `virtual bool AdvancedCopyPackages(const FAdvancedCopyParams& CopyParams, const TArray<TMap<FString, FString>>& PackagesAndDestinations) const = 0;` — Copies files after the final set of maps of sources and destinations was confirmed
- L670 _public prototype_ `virtual bool AdvancedCopyPackages(const TMap<FString, FString>& SourceAndDestPackages, const bool bForceAutosave = false, const bool bCopyOverAllDestinationOverlaps = true, FDuplicatedObjects* OutDuplicatedObjects = nullptr, EMessageSeverity::Type NotificationSeverityFilter = EMessageSeverity::Info) const = 0;` — Copies files after the flattened map of sources and destinations was confirmed
- L673 _public prototype_ `virtual void GenerateAdvancedCopyDestinations(FAdvancedCopyParams& InParams, const TArray<FName>& InPackageNamesToCopy, const UAdvancedCopyCustomization* CopyCustomization, TMap<FString, FString>& OutPackagesAndDestinations) const = 0;` — Given a set of packages to copy, generate the map of those packages to destination filenames
- L676 _public prototype_ `virtual bool FlattenAdvancedCopyDestinations(const TArray<TMap<FString, FString>>& PackagesAndDestinations, TMap<FString, FString>& FlattenedPackagesAndDestinations) const = 0;` — Flattens the maps for each selected package into one complete map to pass to the final copy function while checking for collisions
- L679 _public prototype_ `virtual bool ValidateFlattenedAdvancedCopyDestinations(const TMap<FString, FString>& FlattenedPackagesAndDestinations) const = 0;` — Validate the destinations for advanced copy once the map has been flattened
- L682 _public prototype_ `virtual void GetAllAdvancedCopySources(FName SelectedPackage, FAdvancedCopyParams& CopyParams, TArray<FName>& OutPackageNamesToCopy, TMap<FName, FName>& DependencyMap, const class UAdvancedCopyCustomization* CopyCustomization) const = 0;` — Find all the dependencies that also need to be copied in the advanced copy, mapping them to the file that depends on them and excluding any that don't pass the ARFilter stored on CopyParams
- L685 _public prototype_ `virtual void InitAdvancedCopyFromCopyParams(FAdvancedCopyParams CopyParams) const = 0;` — Given a complete set of copy parameters, which includes the selected package set, start the advanced copy process
- L689 _public prototype_ `virtual void OpenEditorForAssets(const TArray<UObject*>& Assets) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools", meta = (DeprecatedFunction, DeprecationMessage = "Please use UAssetEditorSubsystem::OpenEditorForAssets instead."))` — Opens editor for assets
- L696 _public prototype_ `virtual void ConvertVirtualTextures(const TArray<UTexture2D*>& Textures, bool bConvertBackToNonVirtual, const TArray<UMaterial*>* RelatedMaterials = nullptr) const = 0;` — Converts the given UTexture2D to virtual textures or converts virtual textures back to standard textures and updates the related UMaterials @param Textures					The given textures to convert. @param bConvertBackToNonVirtual	If true, virtual textures will be converted back to standard textures. @param RelatedMaterials			An optional array of materials to update after the conversion, this is useful during import when not all dependencies and caches are up to date.
- L699 _public prototype_ `virtual bool IsAssetClassSupported(const UClass* AssetClass) const = 0;` — Is the given asset class supported?
- L702 _public prototype_ `virtual TArray<UFactory*> GetNewAssetFactories() const = 0;` — Find all supported asset factories.
- L705 _public prototype_ `virtual const TSharedRef<FPathPermissionList>& GetAssetClassPathPermissionList(EAssetClassAction AssetClassAction) const = 0;` — Get asset class permission list for content browser and other systems
- L708 _public prototype_ `virtual const TSharedRef<FNamePermissionList>& GetImportExtensionPermissionList() const = 0;` — Get extension permission list allowed for importer
- L710 _public prototype_ `virtual bool IsImportExtensionAllowed(const FStringView& Extension) const = 0;`
- L713 _public prototype_ `virtual TSet<EBlueprintType>& GetAllowedBlueprintTypes() = 0;` — Which BlueprintTypes are allowed to be created. An empty list should allow everything.
- L716 _public prototype_ `virtual TSharedRef<FPathPermissionList>& GetFolderPermissionList() = 0;` — Get folder permission list for content browser and other systems
- L719 _public prototype_ `virtual TSharedRef<FPathPermissionList>& GetWritableFolderPermissionList() = 0;` — Get writable folder permission list for content browser and other systems
- L722 _public prototype_ `virtual bool IsAssetVisible(const FAssetData& AssetData, bool bCheckAliases = true) const = 0;` — Determines whether an asset has a viewable asset class and its folder is allowed. If not, it can also check if it's aliased to an allowed location.
- L729 _public prototype_ `virtual bool IsAssetReadOnly(const FAssetData& AssetData) const = 0;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")` — Determines whether an asset is considered read-only for editing, based on its flags and the current permissions (@see GetWritableFolderPermissionList). @note This does not check the read-only state of the file itself or anything regarding source control, as it's only checking if the asset can be edited in-memory, not that any edits can be saved to disk.
- L741 _public prototype_ `UE_INTERNAL virtual FAssetData FindAssetByVersePath(const UE::Core::FVersePath& VersePath, bool bIncludeOnlyOnDiskAssets = false, bool bSkipARFilteredAssets = true) const = 0;` — Find the asset data for the specified Verse path @note Verse paths to objects can be ambiguous. This function can be expensive for certain Verse paths. @param VersePath the Verse path of the object to be looked up @param bIncludeOnlyOnDiskAssets If true, use only DiskGatheredData, do not calculate from UObjects. @see IAssetRegistry class header for bIncludeOnlyOnDiskAssets. @param bSkipARFilteredAssets If true, skips Objects that return true for IsAsset but are not assets in the current platform. @return the assets data; Will be invalid if object could not be found
- L744 _public prototype_ `UE_INTERNAL virtual bool ShowingContentVersePath() const = 0;` — Return whether to surface Content Verse paths throughout the editor
- L747 _public prototype_ `UE_INTERNAL virtual UE::AssetTools::FShowingContentVersePath& GetOnShowingContentVersePath() = 0;` — Delegate to control whether we are showing content Verse paths or not
- L753 _public prototype_ `UE_INTERNAL virtual const FString& GetUserFacingPluginName(const IPlugin& Plugin) const = 0;` — Return the path to display to the user in editor UI for the given plugin. Attempts to convert the folder to a Verse path if ShowingContentVersePath is true.
- L759 _public prototype_ `UE_INTERNAL virtual FString GetUserFacingPluginName(FStringView PluginName) const = 0;` — Return the path to display to the user in editor UI for the given plugin. Attempts to convert the folder to a Verse path if ShowingContentVersePath is true.
- L765 _public prototype_ `UE_INTERNAL virtual FString GetUserFacingLongPackagePath(FStringView LongPackagePath) const = 0;` — Return the path to display to the user in editor UI for the given package path. Attempts to convert the folder to a Verse path if ShowingContentVersePath is true.
- L771 _public prototype_ `UE_INTERNAL virtual FString GetUserFacingLongPackageName(FName PackageName) const = 0;` — Return the path to display to the user in editor UI for the given long package name. Attempts to convert the primary asset in the package to a Verse path if ShowingContentVersePath is true.
- L778 _public prototype_ `UE_INTERNAL virtual TArray<FString> GetUserFacingLongPackageNames(TConstArrayView<FName> PackageNames) const = 0;` — Return the paths to display to the user in editor UI for the given long package names. Attempts to convert the primary asset in each package to a Verse path if ShowingContentVersePath is true. @note The array return value is guaranteed to have the same size as PackageNames.
- L784 _public prototype_ `UE_INTERNAL virtual FString GetUserFacingObjectPath(const FSoftObjectPath& ObjectPath) const = 0;` — Return the path to display to the user in editor UI for the given soft object path. Attempts to convert the object path to a Verse path if ShowingContentVersePath is true.
- L791 _public prototype_ `UE_INTERNAL virtual TArray<FString> GetUserFacingObjectPaths(TConstArrayView<FSoftObjectPath> ObjectPaths) const = 0;` — Return the paths to display to the user in editor UI for the given soft object paths. Attempts to convert each object path to a Verse path if ShowingContentVersePath is true. @note The array return value is guaranteed to have the same size as ObjectPaths.
- L797 _public prototype_ `UE_INTERNAL virtual FString GetUserFacingLongPackageName(const UPackage& Package) const = 0;` — Return the path to display to the user in editor UI for the given package. Attempts to convert the primary asset in the package to a Verse path if ShowingContentVersePath is true.
- L804 _public prototype_ `UE_INTERNAL virtual TArray<FString> GetUserFacingLongPackageNames(TConstArrayView<const UPackage*> Packages) const = 0;` — Return the paths to display to the user in editor UI for the given packages. Attempts to convert the primary asset in each package to a Verse path if ShowingContentVersePath is true. @note The array return value is guaranteed to have the same size as Packages.
- L810 _public prototype_ `UE_INTERNAL virtual FString GetUserFacingFullName(const UObject& Object) const = 0;` — Return the full name to display to the user in editor UI for the given object. Attempts to convert the object path portion of the full name to a Verse path if ShowingContentVersePath is true.
- L816 _public prototype_ `UE_INTERNAL virtual FString GetUserFacingPathName(const UObject& Object) const = 0;` — Return the path to display to the user in editor UI for the given asset data. Attempts to convert the object path to a Verse path if ShowingContentVersePath is true.
- L822 _public prototype_ `UE_INTERNAL virtual FString GetUserFacingFullName(const FAssetData& AssetData) const = 0;` — Return the full name to display to the user in editor UI for the given object. Attempts to convert the asset path portion of the full name to a Verse path if ShowingContentVersePath is true.
- L828 _public prototype_ `UE_INTERNAL virtual FString GetUserFacingPathName(const FAssetData& AssetData) const = 0;` — Return the path to display to the user in editor UI for the given asset data. Attempts to convert the asset path to a Verse path if ShowingContentVersePath is true.
- L831 _public prototype_ `virtual bool AllPassWritableFolderFilter(const TArray<FString>& InPaths) const = 0;` — Returns true if all in list pass writable folder filter
- L834 _public prototype_ `virtual bool IsNameAllowed(const FString& Name, FText* OutErrorMessage = nullptr) const = 0;` — Returns true if IsNameAllowedDelegate is not set, or if the name passes the filter function
- L836 _public prototype_ `virtual void RegisterIsNameAllowedDelegate(const FName OwnerName, FIsNameAllowed Delegate) = 0;` — Allows setting of a global name filter that is applied to assets and folders
- L838 _public prototype_ `virtual void UnregisterIsNameAllowedDelegate(const FName OwnerName) = 0;` — Remove a previously-set global name filter
- L841 _public prototype_ `virtual bool IsObjectPathAllowed(const FString& FullObjectPathWithName, FText* OutErrorMessage = nullptr) const = 0;` — Returns true if IsObjectPathAllowedDelegate is not set, or if the name passes the filter function
- L843 _public prototype_ `virtual void RegisterIsObjectPathAllowedDelegate(const FName OwnerName, FIsObjectPathAllowed Delegate) = 0;` — Allows setting of a global name filter that is applied to assets and folders
- L845 _public prototype_ `virtual void UnregisterIsObjectPathAllowedDelegate(const FName OwnerName) = 0;` — Remove a previously-set global name filter
- L848 _public prototype_ `virtual bool SanitizeName(FString& NameToSanitize) = 0;` — Sanitize the name by calling all registered delegates.
- L850 _public prototype_ `virtual void RegisterSanitizeNameDelegate(const FName OwnerName, FSanitizeName Delegate) = 0;` — Allows setting of a global name filter that is applied to assets and folders
- L852 _public prototype_ `virtual void UnregisterSanitizeNameDelegate(const FName OwnerName) = 0;` — Remove a previously-set global name filter
- L855 _public prototype_ `virtual TOptional<FString> GetDefaultAssetNameForClass(const UClass* Class, const UFactory* Factory = nullptr, const UObject* SourceObject = nullptr) = 0;` — Get the default name for the supplied class (if one is registered) to use when creating new assets of that type
- L859 _public function_ `virtual TOptional<FString> GetDefaultAssetNameForClassFromSource(const UClass* Class, const UObject* SourceObject, const UFactory* Factory = nullptr) final` — `UE_DEPRECATED(5.8, "Use GetDefaultAssetNameForClass and pass a source object")` — Get the default name for the supplied class (if one is registered) to use when creating a new asset of that type from the input source object
- L864 _public prototype_ `virtual void RegisterDefaultAssetNameForClass(const UClass* Class, const FString& DefaultName) = 0;` — Register a default name for the supplied class to use when creating new assets of that type
- L866 _public prototype_ `virtual void UnregisterDefaultAssetNameForClass(const UClass* Class) = 0;` — Remove any previously registered name for the supplied class
- L869 _public prototype_ `virtual void NotifyBlockedByWritableFolderFilter() const = 0;` — Show notification that writable folder filter blocked an action
- L872 _public prototype_ `virtual void RegisterCanMigrateAsset(const FName OwnerName, UE::AssetTools::FCanMigrateAsset Delegate) = 0;` — Allow to add some restrictions to the assets that can be migrated
- L873 _public prototype_ `virtual void UnregisterCanMigrateAsset(const FName OwnerName) = 0;`
- L876 _public prototype_ `virtual bool CanAssetBePublic(FStringView AssetPath, FText* DisallowReason = nullptr) const = 0;` — Returns whether the specified asset can be public (referenceable from another mount point / plugin)
- L882 _public prototype_ `virtual void RegisterCanAssetBePublic(const FName OwnerName, UE::AssetTools::FCanAssetBePublic Delegate) = 0;` — Register/unregister delegates to specify whether an asset can be made public (referenceable from another mount point / plugin) By default any asset can be public and if any delegate return false, the asset must be private
- L883 _public prototype_ `virtual void UnregisterCanAssetBePublic(const FName OwnerName) = 0;`
- L886 _public prototype_ `virtual void SyncBrowserToAssets(const TArray<UObject*>& AssetsToSync) = 0;` — Syncs the primary content browser to the specified assets, whether or not it is locked. Most syncs that come from AssetTools -feel- like they came from the content browser, so this is okay.
- L887 _public prototype_ `virtual void SyncBrowserToAssets(const TArray<FAssetData>& AssetsToSync) = 0;`

#### class `UAssetToolsHelpers`  
`class UAssetToolsHelpers : public UObject`  
_L892-899_
- reflection: `UCLASS(transient)`
- inherits: `UObject`
- L898 _public prototype_ `static TScriptInterface<IAssetTools> GetAssetTools();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset Tools")`

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace AssetTools` (scope `UE`)
- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPackageMigration, FPackageMigrationContext&);`
- L38 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPackageMigration, FPackageMigrationContext&);` (scope `UE::AssetTools`)
- L40 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FCanMigrateAsset, FName);`
- L40 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FCanMigrateAsset, FName);` (scope `UE::AssetTools`)
- L42 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FCanAssetBePublic, FStringView , FText* );`
- L42 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FCanAssetBePublic, FStringView , FText* );` (scope `UE::AssetTools`)
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FShouldCreateAssetsAsExternallyReferenceableForPath, FStringView , TOptional<bool>& );`
- L44 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FShouldCreateAssetsAsExternallyReferenceableForPath, FStringView , TOptional<bool>& );` (scope `UE::AssetTools`)
- L46 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FShowingContentVersePath);`
- L46 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FShowingContentVersePath);` (scope `UE::AssetTools`)
- L154 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FAdvancedCopyCompletedEvent, bool, bSuccess, const TArray<FAssetRenameData>&, AllCopiedAssets);`
- L154 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FAdvancedCopyCompletedEvent, bool, bSuccess, const TArray<FAssetRenameData>&, AllCopiedAssets);`
- L156 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAssetPostRenameEvent, const TArray<FAssetRenameData>&);`
- L156 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAssetPostRenameEvent, const TArray<FAssetRenameData>&);`
- L157 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsNameAllowed, const FString& , FText* );`
- L157 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsNameAllowed, const FString& , FText* );`
- L158 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsObjectPathAllowed, const FString& , FText* );`
- L158 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsObjectPathAllowed, const FString& , FText* );`
- L159 _delegate_ `DECLARE_DELEGATE_OneParam(FSanitizeName, FString& );`
- L159 _prototype_ `DECLARE_DELEGATE_OneParam(FSanitizeName, FString& );`
- L270 _typedef_ `using FDuplicatedObjects = TArray<TMap<TSoftObjectPtr<UObject>, TSoftObjectPtr<UObject>>>;` — An array of maps each storing pairs of original object -> duplicated object
- L278 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FAssetCreateCompleteDynamic, UFactory*, Factory, UObject*, NewObject);`
- L278 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FAssetCreateCompleteDynamic, UFactory*, Factory, UObject*, NewObject);`
- L279 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetCreateCancelledDynamic, UFactory*, Factory);`
- L279 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetCreateCancelledDynamic, UFactory*, Factory);`
- L280 _delegate_ `DECLARE_DELEGATE_TwoParams(FAssetCreateComplete, UFactory* , UObject* );`
- L280 _prototype_ `DECLARE_DELEGATE_TwoParams(FAssetCreateComplete, UFactory* , UObject* );`
- L281 _delegate_ `DECLARE_DELEGATE_OneParam(FAssetCreateCancelled, UFactory* );`
- L281 _prototype_ `DECLARE_DELEGATE_OneParam(FAssetCreateCancelled, UFactory* );`
- L290 _delegate_ `DECLARE_DELEGATE(FOnAssetsDiscovered);`
- L372 _function_ `PackagePath, AssetClass, Factory, FAssetCreateComplete::CreateLambda([OnComplete](UFactory* Factory, UObject* NewObject) { OnComplete.ExecuteIfBound(Factory, NewObject); }), FAssetCreateCancelled::CreateLambda([OnCancelled](UFactory* Factory) { OnCancelled.ExecuteIfBound(Factory); }), CallingContext, bOverwriteExisting );` (scope `IAssetTools::CreateAssetAsync`)
- L373 _function_ `AssetClass, Factory, FAssetCreateComplete::CreateLambda([OnComplete](UFactory* Factory, UObject* NewObject) { OnComplete.ExecuteIfBound(Factory, NewObject); }), FAssetCreateCancelled::CreateLambda([OnCancelled](UFactory* Factory) { OnCancelled.ExecuteIfBound(Factory); }), CallingContext, bOverwriteExisting );` (scope `IAssetTools::CreateAssetAsync`)
- L402 _function_ `CreateAssetsFrom(TConstArrayView<UObject*>(reinterpret_cast<UObject* const*>(SourceObjects.GetData()), SourceObjects.Num()), CreateAssetType, DefaultSuffix, [FactoryConstructor](UObject* SourceObject){ return FactoryConstructor(Cast<SourceObjectType>(SourceObject)); }, CallingContext);` (scope `IAssetTools::CreateAssetsFrom`)
- L424 _function_ `PackagePath, AssetClass, Factory, FAssetCreateComplete::CreateLambda([OnComplete](UFactory* Factory, UObject* NewObject) { OnComplete.ExecuteIfBound(Factory, NewObject); }), FAssetCreateCancelled::CreateLambda([OnCancelled](UFactory* Factory) { OnCancelled.ExecuteIfBound(Factory); }), CallingContext );` (scope `IAssetTools::CreateAssetWithDialogAsync`)
- L425 _function_ `AssetClass, Factory, FAssetCreateComplete::CreateLambda([OnComplete](UFactory* Factory, UObject* NewObject) { OnComplete.ExecuteIfBound(Factory, NewObject); }), FAssetCreateCancelled::CreateLambda([OnCancelled](UFactory* Factory) { OnCancelled.ExecuteIfBound(Factory); }), CallingContext );` (scope `IAssetTools::CreateAssetWithDialogAsync`)

### `Source/Developer/AssetTools/Public/IAssetTypeActions.h` (Public)


#### enum `EAssetTypeActivationMethod::Type`  
`enum Type`  
_L17-22_
- L19 _public enumerator_ `DoubleClicked`
- L20 _public enumerator_ `Opened`
- L21 _public enumerator_ `Previewed`

#### class `IAssetTypeActions`  
`class IAssetTypeActions : public TSharedFromThis<IAssetTypeActions>`  
_L27-163_
- inherits: `TSharedFromThis<IAssetTypeActions>`
- desc: AssetTypeActions provide actions and other information about asset types
- L31 _public prototype_ `virtual ~IAssetTypeActions()= default;` — Virtual destructor
- L37 _public function_ `virtual bool IsAssetDefinitionInDisguise() const` — Returns if this is actually just an UAssetDefinition.  Which doesn't exist in this module.  UAssetDefinition is replacing IAssetTypeActions, but for now we generate fake IAssetTypeActions that are secretly AssetDefinitions
- L40 _public prototype_ `virtual FText GetName() const = 0;` — Returns the name of this type
- L43 _public prototype_ `virtual UClass* GetSupportedClass() const = 0;` — Get the supported class of this type.
- L46 _public prototype_ `virtual FColor GetTypeColor() const = 0;` — Returns the color associated with this type
- L49 _public function_ `virtual bool ShouldCallGetActions() const` — Returns true if we should call GetActions.
- L52 _public function_ `virtual bool HasActions( const TArray<UObject*>& InObjects ) const` — Returns true if this class can supply actions for InObjects.
- L55 _public function_ `virtual void GetActions( const TArray<UObject*>& InObjects, class FMenuBuilder& MenuBuilder )` — Generates a menubuilder for the specified objects.
- L58 _public function_ `virtual void GetActions(const TArray<UObject*>& InObjects, struct FToolMenuSection& Section)` — Generates a menu section for the specified objects.
- L61 _public prototype_ `virtual bool ShouldFindEditorForAsset() const = 0;` — Returns true if an asset editor window should be created for this asset.
- L64 _public prototype_ `virtual void OpenAssetEditor( const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>() ) = 0;` — Opens the asset editor for the specified objects. If EditWithinLevelEditor is valid, the world-centric editor will be used.
- L67 _public prototype_ `virtual void OpenAssetEditor( const TArray<UObject*>& InObjects, const EAssetTypeActivationOpenedMethod OpenedMethod, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>() ) = 0;` — Opens the asset editor for the specified objects. If EditWithinLevelEditor is valid, the world-centric editor will be used.
- L70 _public prototype_ `virtual bool AssetsActivatedOverride(const TArray<UObject*>& InObjects, EAssetTypeActivationMethod::Type ActivationType) = 0;` — Allows overriding asset activation to perform asset type specific activation for the supplied assets. This happens when the user double clicks, presses enter, or presses space. Return true if you have overridden the behavior.
- L73 _public prototype_ `virtual bool CanRename(const FAssetData& InAsset, FText* OutErrorMsg) const = 0;` — Returns true if this asset can be renamed
- L76 _public prototype_ `virtual bool CanDuplicate(const FAssetData& InAsset, FText* OutErrorMsg) const = 0;` — Returns true if this asset can be duplicated
- L79 _public prototype_ `virtual TArray<FAssetData> GetValidAssetsForPreviewOrEdit(TArrayView<const FAssetData> InAssetDatas, bool bIsPreview) = 0;` — Returns the set of asset data that is valid to load.
- L82 _public prototype_ `virtual bool CanFilter() = 0;` — Returns true if this class can be used as a filter in the content browser
- L85 _public prototype_ `virtual FName GetFilterName() const = 0;` — Returns name to use for filter in the content browser
- L88 _public prototype_ `virtual bool CanLocalize() const = 0;` — Returns true if this class can be localized
- L91 _public prototype_ `virtual bool CanMerge() const = 0;` — Returns true if this class can be merged (either manually or automatically)
- L94 _public prototype_ `virtual void Merge( UObject* InObject ) = 0;` — Begins a merge operation for InObject (automatically determines remote/base versions needed to resolve)
- L97 _public prototype_ `virtual void Merge(UObject* BaseAsset, UObject* RemoteAsset, UObject* LocalAsset, const FOnMergeResolved& ResolutionCallback) = 0;` — Begins a merge between the specified assets
- L100 _public prototype_ `virtual uint32 GetCategories() = 0;` — Returns the categories that this asset type appears in. The return value is one or more flags from EAssetTypeCategories.
- L103 _public prototype_ `virtual FString GetObjectDisplayName(UObject* Object) const = 0;` — Returns the display name for that object.
- L106 _public prototype_ `virtual const TArray<FText>& GetSubMenus() const = 0;` — Returns array of sub-menu names that this asset type is parented under in the Asset Creation Context Menu.
- L109 _public prototype_ `virtual bool ShouldForceWorldCentric() = 0;` — @return True if we should force world-centric mode for newly-opened assets
- L112 _public prototype_ `virtual void PerformAssetDiff(UObject* OldAsset, UObject* NewAsset, const struct FRevisionInfo& OldRevision, const struct FRevisionInfo& NewRevision) const = 0;` — Performs asset-specific diff on the supplied asset
- L115 _public prototype_ `virtual class UThumbnailInfo* GetThumbnailInfo(UObject* Asset) const = 0;` — Returns the thumbnail info for the specified asset, if it has one.
- L119 _public prototype_ `virtual EThumbnailPrimType GetDefaultThumbnailPrimitiveType(UObject* Asset) const = 0;` — `UE_DEPRECATED(5.2, "When overriding GetThumbnailInfo, The default thumbnail primitive is now a property on USceneThumbnailInfoWithPrimitive. The default only applies to this thumbnail type, so it has been relocated as an implementation detail of it.")` — Returns the default thumbnail type that should be rendered when rendering primitive shapes.  This does not need to be implemented if the asset does not render a primitive shape
- L123 _public prototype_ `virtual TSharedPtr<class SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const = 0;` — `UE_DEPRECATED(5.5, "Convert the Action class over to the Definition system and use the new GetThumbnailActionOverlay, see UAssetDefinition for more information")` — Optionally returns a custom widget to overlay on top of this assets' thumbnail
- L126 _public prototype_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const = 0;` — Returns additional tooltip information for the specified asset, if it has any (otherwise return the null widget)
- L129 _public prototype_ `virtual bool IsImportedAsset() const = 0;` — Returns whether the asset was imported from an external source
- L132 _public prototype_ `virtual void GetResolvedSourceFilePaths(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFilePaths) const = 0;` — Collects the resolved source paths for the imported assets
- L135 _public prototype_ `virtual void GetSourceFileLabels(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFileLabels) const = 0;` — Collects the source file labels for the imported assets
- L138 _public prototype_ `virtual void BuildBackendFilter(struct FARFilter& InFilter) = 0;` — Builds the filter for this class
- L141 _public prototype_ `virtual FText GetDisplayNameFromAssetData(const FAssetData& AssetData) const = 0;` — Optionally gets a class display name for this asset (otherwise, returns empty text (e.g. `FText::GetEmpty()`)
- L145 _public function_ `virtual void SetSupported(bool bInSupported) final` — `UE_DEPRECATED(5.2, "Use IAssetTools::IsAssetClassSupported")` — Sets whether or not this asset type is a supported type for this editor session.
- L149 _public function_ `virtual bool IsSupported() const final` — `UE_DEPRECATED(5.2, "Use IAssetTools::IsAssetClassSupported")` — Is this asset type supported in the current session?
- L153 _public prototype_ `virtual FTopLevelAssetPath GetClassPathName() const = 0;` — `UE_DEPRECATED(5.2, "Just call GetSupportedClass()->GetClassPathName();")` — Returns class path name as a package + class FName pair
- L156 _public prototype_ `virtual bool SupportsOpenedMethod(const EAssetTypeActivationOpenedMethod OpenedMethod) const = 0;` — Does this asset support edit or view methods?
- L159 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const = 0;` — Returns thumbnail brush unique for the given asset data.  Returning null falls back to class thumbnail brush.
- L162 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const = 0;` — Returns icon brush unique for the given asset data.  Returning null falls back to class icon brush.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace EAssetTypeActivationMethod`

### `Source/Developer/AssetTools/Public/IClassTypeActions.h` (Public)


#### class `IClassTypeActions`  
`class IClassTypeActions : public TSharedFromThis<IClassTypeActions>`  
_L9-20_
- inherits: `TSharedFromThis<IClassTypeActions>`
- desc: ClassTypeActions provide actions and other information about asset types that host classes
- L13 _public prototype_ `virtual ~IClassTypeActions()= default;` — Virtual destructor
- L16 _public prototype_ `virtual UClass* GetSupportedClass() const = 0;` — Checks to see if the specified object is handled by this type.
- L19 _public prototype_ `virtual TSharedPtr<class SWidget> GetThumbnailOverlay(const struct FAssetData& AssetData) const = 0;` — Optionally returns a custom widget to overlay on top of this assets' thumbnail

### `Source/Developer/AssetTools/Public/ILocalizedAssetTools.h` (Public)


#### enum `ELocalizedAssetsOnDiskResult`  
`enum class ELocalizedAssetsOnDiskResult : uint8`  
_L7-13_
- L10 _public enumerator_ `Success` — Getting localized assets on disk succeeded
- L12 _public enumerator_ `PackageNamesError` — PackageNames could not be converted to FAssetData

#### enum `ELocalizedAssetsInSCCResult`  
`enum class ELocalizedAssetsInSCCResult : uint8`  
_L15-21_
- L18 _public enumerator_ `Success` — Getting localized assets in Revision Control succeeded
- L20 _public enumerator_ `RevisionControlNotAvailable` — Revision Control is required but unavailable

#### enum `ELocalizedAssetsResult`  
`enum class ELocalizedAssetsResult : uint8`  
_L23-31_
- L26 _public enumerator_ `Success` — Getting localized assets in Revision Control succeeded
- L28 _public enumerator_ `PackageNamesError` — PackageNames could not be converted to FAssetData
- L30 _public enumerator_ `RevisionControlNotAvailable` — Revision Control is required but unavailable

#### enum `ELocalizedVariantsInclusion`  
`enum class ELocalizedVariantsInclusion : uint8`  
_L33-41_
- L36 _public enumerator_ `Include` — Include localized variants (and possibly source assets) to an operation
- L38 _public enumerator_ `Exclude` — Exclude localized variants (or related source asset) from an operation
- L40 _public enumerator_ `Cancel` — Cancel the current operation if the user do not want to choose between Including or Excluding localized variants.

#### class `ILocalizedAssetTools`  
`class ILocalizedAssetTools`  
_L43-74_
- L46 _public prototype_ `virtual bool CanLocalize(const UClass* Class) const = 0;`
- L49 _public prototype_ `virtual ELocalizedAssetsOnDiskResult GetLocalizedVariantsOnDisk(const TArray<FName>& InPackages, TMap<FName, TArray<FName>>& OutLocalizedVariantsBySource, TArray<FName>* OutPackagesNotFound = nullptr) const = 0;` — Get localized variants on disk from an asset name list
- L52 _public prototype_ `virtual ELocalizedAssetsInSCCResult GetLocalizedVariantsInRevisionControl(const TArray<FName>& InPackages, TMap<FName, TArray<FName>>& OutLocalizedVariantsBySource, TArray<FName>* OutPackagesNotFound = nullptr) const = 0;` — Get localized variants in Revision Control from an asset name list
- L55 _public prototype_ `virtual ELocalizedAssetsResult GetLocalizedVariants(const TArray<FName>& InPackages, TMap<FName, TArray<FName>>& OutLocalizedVariantsBySourceOnDisk, bool bAlsoCheckInRevisionControl, TMap<FName, TArray<FName>>& OutLocalizedVariantsBySourceInRevisionControl, TArray<FName>* OutPackagesNotFound = nullptr) const = 0;` — Get localized variants on disk then in Revision Control if Project Settings requires it
- L58 _public prototype_ `virtual void OpenRevisionControlRequiredDialog() const = 0;` — Open a dialog to required Revision Control to be configured
- L61 _public prototype_ `virtual void OpenFilesInRevisionControlRequiredDialog(const TArray<FText>& FileList) const = 0;` — Open a dialog to required files in Revision Control to be on disk
- L64 _public prototype_ `virtual void OpenLocalizedVariantsListMessageDialog(const FText& Header, const FText& Message, const TArray<FText>& FileList) const = 0;` — Open a dialog with a file list (localized variants) with a custom message
- L67 _public prototype_ `virtual ELocalizedVariantsInclusion OpenIncludeLocalizedVariantsListDialog(const TArray<FText>& FileList, ELocalizedVariantsInclusion RecommendedBehavior = ELocalizedVariantsInclusion::Include, bool bAllowOperationCanceling = true, ELocalizedVariantsInclusion UnattendedDefaultBehavior = ELocalizedVariantsInclusion::Exclude) const = 0;` — Open a dialog to ask to include/exclude localized variants from an operation
- L70 _public prototype_ `virtual const FText& GetFilesNeedToBeOnDiskWarningText() const = 0;` — Get shared text to warn that some files need to be on disk (not only in Revision Control)
- L73 _public prototype_ `virtual const FText& GetRevisionControlIsNotAvailableWarningText() const = 0;` — Get shared text to warn that Revision Control needs to be available

### `Source/Developer/AssetTools/Public/PackageMigrationContext.h` (Public)


#### struct `UE::AssetTools::FPackageMigrationContext`  
`struct FPackageMigrationContext : public FGCObject`  
_L22-195_
- inherits: `FGCObject`
- L26 _public prototype_ `EPackageMigrationStep GetCurrentStep() const;`
- L29 _public prototype_ `void AddSucessfullMigrationMessage(const FText& InMessage);` — Notify the user that files where migrated. It should tell the user what was migrated and where it is in the destination.
- L32 _public prototype_ `void AddWarningMigrationMessage(const FText& InMessage);` — Notify the user that some asset may require some extra work to fully migrate
- L35 _public prototype_ `void AddErrorMigrationMessage(const FText& InMessage);` — Notify the user that some asset couldn't be migrated
- L38 _public prototype_ `const FScopedMountPoint& GetDestinationMountPoint() const;`
- L42 _public prototype_ `const TArray<FMigrationPackageData>& GetMigrationPackagesData() const;` — Return the data associated to a package that is migrated
- L45 _public prototype_ `const TArray<UPackage*>& GetMovedOutOfTheWayPackages() const;` — Return the array of non instanced package where moved because they were in the way of the migration
- L48 _public prototype_ `const TArray<FString>& GetExcludedDependencies() const;` — Return the array of package dependencies that where not migrated because there where excluded by some automated filters
- L137 _public prototype_ `FPackageMigrationContext(const FPackageMigrationContext&) = delete;`
- L138 _public prototype_ `FPackageMigrationContext(FPackageMigrationContext&&) = delete;`
- L139 _public prototype_ `FPackageMigrationContext operator=(const FPackageMigrationContext&) = delete;`
- L140 _public prototype_ `FPackageMigrationContext operator=(FPackageMigrationContext&&) = delete;`
- L143 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L145 _public prototype_ `virtual FString GetReferencerName() const override;`
- L153 _private prototype_ `void MoveInTheWayPackage(UPackage* Package);` — Move a package out of the way for the duration of the migration
- L155 _private prototype_ `FPackageMigrationContext(FScopedMountPoint&& InMountPoint);`
- L157 _private prototype_ `~FPackageMigrationContext() = default;`
- L171 _private member_ `EPackageMigrationStep CurrentStep;`
- L174 _private member_ `TArray<FText> MigratedPackageMessages;` — Message of the for the successfully migrated asset
- L177 _private member_ `TArray<FText> WarningMessage;` — Message to warn the user that some extra step may be required from him to complete the migration
- L180 _private member_ `TArray<FText> ErrorMessages;` — General Error messages of the migration
- L182 _private member_ `FScopedMountPoint DestinationMountPoint;`
- L185 _private member_ `TArray<FScopedTemporalyMovedPackage> TemporalyMovedPackages;` — Helper for the package that were moved because they were in the way of migrated packages
- L188 _private member_ `TArray<TObjectPtr<UPackage>> PackagesThatWhereMoved;` — The package that have been moved during the migration
- L191 _private member_ `TArray<FMigrationPackageData> MigrationPackagesData;` — The data associated to the packages that take part of the migration process.
- L194 _private member_ `TArray<FString> ExcludedDependencies;` — The excluded dependencies of the asset that are being migrated (these don't include the asset a user might have exclude voluntary from the migration)

#### enum `UE::AssetTools::FPackageMigrationContext::EPackageMigrationStep`  
`enum class EPackageMigrationStep`  
_L50-74_
- L53 _public enumerator_ `BeginMigration` — Called before the migration begin
- L55 _public enumerator_ `PostAssetMigrationPackageDataCreated` — Called after the non external packages to migrate where processed
- L57 _public enumerator_ `PostExternalMigrationPackageDataCreated` — Called after the non external packages to migrate where processed
- L59 _public enumerator_ `PostExcludedDependenciesCreated` — Called after the excluded depencies where processed
- L61 _public enumerator_ `InTheWayPackagesMoved` — Called after all the package that might be in the way for the migration where move
- L63 _public enumerator_ `InstancedPackagesCreated` — Called after the instanced package where created with their load linker setup being already set to load the right file
- L65 _public enumerator_ `InstancedPackagesLoaded` — Called after the instanced package where loaded
- L67 _public enumerator_ `InstancedPackagesSaved` — Called after the instanced package were saved into the destination
- L69 _public enumerator_ `PostCleaningInstancedPackages` — Called after the instanced package were removed
- L71 _public enumerator_ `InTheWayPackagesRestored` — Called after all the package that were in the way for the migration where restored
- L73 _public enumerator_ `EndMigration` — Called at the end of the migration. After the in the way package where restored but before the log is processed

#### struct `UE::AssetTools::FPackageMigrationContext::FScopedMountPoint`  
`struct FScopedMountPoint`  
_L77-106_
- desc: Utility to manage the temp mount point if needed and to help convert the paths during the migration
- L80 _public prototype_ `FScopedMountPoint() = delete;`
- L81 _public prototype_ `FScopedMountPoint(const FScopedMountPoint&) = delete;`
- L82 _public prototype_ `FScopedMountPoint& operator=(const FScopedMountPoint&) = delete;`
- L84 _public prototype_ `FScopedMountPoint(FScopedMountPoint&&) = default;`
- L85 _public prototype_ `FScopedMountPoint& operator=(FScopedMountPoint&&) = default;`
- L87 _public prototype_ `const FString& GetRootPath() const;`
- L88 _public prototype_ `const FString& GetContentPath() const;`
- L90 _public prototype_ `FString GetMigratedPackageFilename(const FString& LongPackageName, const FStringView& InExtension) const;`
- L93 _public prototype_ `FString GetNewPackageNameForMigration(const FString& LongPackageName) const;` — Get name of package when moved under the destination mount point
- L100 _private prototype_ `FScopedMountPoint(FString&& InRootPath, FString&& InContentPath);`
- L101 _private prototype_ `~FScopedMountPoint();`
- L103 _private member_ `FString RootPath;`
- L104 _private member_ `FString ContentPath;`
- L105 _private member_ `bool bHasMountedANewMountPoint = false;`

#### struct `UE::AssetTools::FPackageMigrationContext::FMigrationPackageData`  
`struct FMigrationPackageData`  
_L109-135_
- desc: The data associated to an package that take part of the migration process.
- L111 _public prototype_ `const FString& GetInstancedPackageName() const;`
- L112 _public prototype_ `const FString& GetOriginalPackageName() const;`
- L113 _public prototype_ `const FString& GetDestinationFilename() const;`
- L115 _public prototype_ `UPackage* GetInstancedPackage() const;`
- L118 _public member_ `bool bNeedInstancedLoad = false;` — Tell the migration that package must be loaded
- L121 _public member_ `bool bNeedToBeSaveMigrated = false;` — Tell the migration that the package must be migrated by save
- L123 _public prototype_ `FMigrationPackageData(const FString& InInstancedPackageName, const FString& InOriginalPackageName, const FString& InDestinationFilename);`
- L130 _private member_ `FString InstancedPackageName;`
- L131 _private member_ `FString OriginalPackageName;`
- L133 _private member_ `FString DestinationFilename;`
- L134 _private member_ `TObjectPtr<UPackage> InstancedPackage = nullptr;`

#### struct `UE::AssetTools::FPackageMigrationContext::FScopedTemporalyMovedPackage`  
`struct FScopedTemporalyMovedPackage`  
_L160-169_
- desc: Helper to move existing package out of the way during the migration
- L163 _public prototype_ `FScopedTemporalyMovedPackage(UPackage* InPackageToMove);`
- L165 _public prototype_ `~FScopedTemporalyMovedPackage();`
- L167 _public member_ `TObjectPtr<UPackage> PackageToMove = nullptr;`
- L168 _public member_ `FString OriginalName;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ASSETTOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace AssetTools` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::AssetTools`)
