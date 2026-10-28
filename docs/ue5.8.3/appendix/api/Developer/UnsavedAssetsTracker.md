# Developer / UnsavedAssetsTracker

- module root: `Source/Developer/UnsavedAssetsTracker/Source`
- headers: 4; symbols: 101
- symbol kinds: class=4, delegate=4, enum=1, enumerator=8, function=4, macro=1, member=26, prototype=52, struct=1
- PrivateDependencyModuleNames: CoreUObject, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, EditorSubsystem, Engine, SourceControl, TypedElementFramework, UncontrolledChangelists

### `Source/Developer/UnsavedAssetsTracker/Source/Private/SUnsavedAssetsStatusBarWidget.h` (Private)


#### class `SUnsavedAssetsStatusBarWidget`  
`class SUnsavedAssetsStatusBarWidget : public SCompoundWidget`  
_L16-35_
- inherits: `SCompoundWidget`
- desc: Tracks assets that has in-memory modification not saved to disk yet and checks the source control states of those assets when a source control provider is available.
- L19 _public function_ `SLATE_BEGIN_ARGS(SUnsavedAssetsStatusBarWidget)`
- L22 _public prototype_ `SLATE_EVENT(FOnClicked, OnClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FUnsavedAssetsTracker> InUnsavedAssetTracker);` — Event fired when the status bar button is clicked
- L29 _private prototype_ `const FSlateBrush* GetStatusBarIcon() const;`
- L30 _private prototype_ `FText GetStatusBarText() const;`
- L31 _private prototype_ `FText GetStatusBarTooltip() const;`
- L34 _private member_ `TSharedPtr<FUnsavedAssetsTracker> UnsavedAssetTracker;`

### `Source/Developer/UnsavedAssetsTracker/Source/Private/UnsavedAssetsAutoCheckout.h` (Private)


#### class `FUnsavedAssetsAutoCheckout`  
`class FUnsavedAssetsAutoCheckout : public TSharedFromThis<FUnsavedAssetsAutoCheckout>`  
_L16-42_
- inherits: `TSharedFromThis<FUnsavedAssetsAutoCheckout>`
- desc: Uses the source control provider to attempt automatic checkouts of unsaved assets.
- L19 _public prototype_ `explicit FUnsavedAssetsAutoCheckout(FUnsavedAssetsTrackerModule* Module);`
- L20 _public prototype_ `~FUnsavedAssetsAutoCheckout();`
- L23 _private prototype_ `void OnAsyncCheckout(const FString& AbsoluteAssetFilepath);`
- L25 _private member_ `FSourceControlOperationComplete AsyncCheckoutComplete;`
- L26 _private prototype_ `void OnAsyncCheckoutComplete(const FSourceControlOperationRef&, ECommandResult::Type);`
- L29 _private prototype_ `bool OnProcessCheckoutBatch(float);` — To process checkouts in a single batch once per tick
- L30 _private member_ `bool bProcessCheckoutBatchPending;`
- L32 _private prototype_ `void TriggerAsyncCheckout(const TArray<FString>& FilesToCheckout, const FSourceControlOperationRef& Operation);`
- L34 _private prototype_ `void NotifySuccess(TConstArrayView<FString> Files, const FSourceControlOperationRef& Operation);`
- L35 _private prototype_ `void NotifyFailure(TConstArrayView<FString> Files, const FSourceControlOperationRef& Operation);`
- L36 _private prototype_ `void NotifyCancel(TConstArrayView<FString> Files, const FSourceControlOperationRef& Operation);`
- L38 _private member_ `TMap<FSourceControlOperationRef, TArray<FString>> OperationToFiles;`
- L40 _private member_ `TSet<FString> CheckOutBatch;`
- L41 _private member_ `FSourceControlOperationRef CheckOutOperation;`

### `Source/Developer/UnsavedAssetsTracker/Source/Private/UnsavedAssetsTracker.h` (Private)


#### class `FUnsavedAssetsTracker`  
`class FUnsavedAssetsTracker : public TSharedFromThis<FUnsavedAssetsTracker>`  
_L23-173_
- inherits: `TSharedFromThis<FUnsavedAssetsTracker>`
- desc: Tracks assets that has in-memory modification not saved to disk yet and checks the source control states of those assets when a source control provider is available.
- L26 _public prototype_ `FUnsavedAssetsTracker();`
- L27 _public prototype_ `virtual ~FUnsavedAssetsTracker();`
- L30 _public prototype_ `int32 GetUnsavedAssetNum() const;` — Returns the number of unsaved assets currently tracked.
- L33 _public prototype_ `TArray<FString> GetUnsavedAssets() const;` — Returns the list of unsaved assets.
- L36 _public prototype_ `int32 GetWarningNum() const;` — Returns the number of active warnings.
- L39 _public prototype_ `TMap<FString, FString> GetWarnings() const;` — Returns a map of pathname/warnings.
- L42 _public function_ `void SetWarningNotificationEnabled(bool bEnabled)` — Sets whether a toast notification is emitted when looking up the source control state of an unsaved asset generates a warning.
- L45 _public prototype_ `bool PromptToSavePackages();` — Displays a dialog prompting the user to save the packages.
- L48 _public prototype_ `bool IsAssetUnsaved(const FString& FileAbsPathname) const;` — Check if the input asset is unsaved.
- L77 _private prototype_ `void OnPackageMarkedDirty(UPackage* Package, bool bWasDirty);` — Invoked when a package is marked dirty. @param Pkg The package that was marked as dirty @param bWasDirty Whether the package was previously dirty before the call to MarkPackageDirty
- L86 _private prototype_ `void OnPackageSaved(const FString& PackagePathname, UPackage* Package, FObjectPostSaveContext ObjectSaveContext);` — Invoked when a package is saved. @param Filename The filename the package was saved to @param Package The package that was saved @param ObjectSaveContext The package saving context.
- L91 _private prototype_ `void OnPackageDirtyStateUpdated(UPackage* Package);` — Invoked when the dirty state of a package changed. Used to track when a package was cleaned without being saved.
- L96 _private prototype_ `void OnMapChanged(UWorld* InWorld, EMapChangeType InMapChangeType);` — Invoked when the level editor changes map. Used to track when a temporary 'Untitled' unsaved map is closed without saving.
- L101 _private prototype_ `void OnUndo(const FTransactionContext& TransactionContext, bool Succeeded);` — Invoked when the undo stack changes. Used to track when the undo/redo affect the dirty state of a package.
- L102 _private prototype_ `void OnRedo(const FTransactionContext& TransactionContext, bool Succeeded);`
- L105 _private prototype_ `void OnPostGarbageCollect();` — Invoked after garbage collection.
- L108 _private prototype_ `void OnPackageDeleted(UPackage* Package);` — Invoked when a package is deleted.
- L111 _private prototype_ `void OnActorDeleted(AActor* Actor);` — Invoked when an actor is deleted.
- L114 _private prototype_ `void OnWorldPostRename(UWorld* World);` — Invoked when a world is successfully renamed. Used to track when a temporary 'Untitled' unsaved map is saved with a new name.
- L117 _private prototype_ `void StartTrackingDirtyPackage(const UPackage* Package);` — Starts to track an unsaved package.
- L120 _private prototype_ `void StopTrackingDirtyPackage(const FString& PackagePathname);` — Stops tracking the specified unsaved package if the package was previously tracked.
- L123 _private prototype_ `void OnSourceControlFileStatusUpdate(const FString& Pathname, const ISourceControlState* Status);` — Invoked when the status of a source controlled is updated, with the corresponding warning, if any.
- L126 _private prototype_ `void OnSourceControlWarningNotification(const ISourceControlState& State, FStatus& InOutStatus);` — Invoked when a new warning is discovered.
- L129 _private prototype_ `void ShowWarningNotificationIfNotAlreadyShown(EWarningTypes WarningType, const FText& Msg);` — Show a toast notifications if the warning types hasn't been shown yet.
- L132 _private prototype_ `void SyncWithDirtyPackageList();` — Refresh the list of unsaved files from the list returned by FEditorFileUtils::GetDirtyPackages().
- L135 _private prototype_ `bool Tick(float DeltaTime);` — Invoked by the engine on the game thread.
- L138 _private prototype_ `bool ShouldTrackDirtyPackage(const UPackage* Package);` — Whether the specified package should be tracked.
- L141 _private prototype_ `static void UpdateTedsPackage(const FString& PackagePathname, const bool bIsDirty);` — Adds the Dirty tag to the Package and its contained object rows
- L144 _private prototype_ `static void RemoveTedsPackage(const FString& PackagePathname);` — Removes the Package row from TEDS
- L148 _private member_ `FCriticalSection DirtyNotificationLock;` — Supports multithreaded Dirty notifications.
- L151 _private member_ `TMap<FString, TWeakObjectPtr<UPackage>> DirtyPackageEventsReportedOnBackgroundThread;` — Keep the packages that were marked/unmarked dirty from a background thread to check the status on the game thread.
- L154 _private member_ `TMap<FString, FStatus> UnsavedPackages;` — Maps the package pathname to the status
- L157 _private member_ `TMap<FString, FString> UnsavedAbsFilePathames;` — Maps the packages absolute file name (on file system) to the package pathname for fast reverse lookup.
- L160 _private member_ `TSet<FString> WarningPackagePathnames;` — Packages pathname for which a warning was issued.
- L163 _private member_ `TSet<EWarningTypes> ShownWarnings;` — Sets of warning shown to the user.
- L166 _private member_ `FTSTicker::FDelegateHandle TickerHandle;` — Handle to unregister the tick delegate.
- L169 _private member_ `bool bWarningNotificationEnabled = true;` — Whether toast notification should be shown when a warning is detected.
- L172 _private member_ `bool bSyncWithDirtyPackageList = false;` — Whether the tracker should sync its dirty packages list with what the engine considers dirty.

#### enum `FUnsavedAssetsTracker::EWarningTypes`  
`enum class EWarningTypes`  
_L51-61_
- L53 _public enumerator_ `None`
- L54 _public enumerator_ `Conflicted`
- L55 _public enumerator_ `OutOfDate`
- L56 _public enumerator_ `CheckedOutByOther`
- L57 _public enumerator_ `CheckedOutInOtherBranch`
- L58 _public enumerator_ `ModifiedInOtherBranch`
- L59 _public enumerator_ `PackageWritePermission`
- L60 _public enumerator_ `Other`

#### struct `FUnsavedAssetsTracker::FStatus`  
`struct FStatus`  
_L63-69_
- L65 _public function_ `FStatus(const FString& InAbsFilePathname) : AbsPackageFilePathname(InAbsFilePathname)`
- L66 _public member_ `FString AbsPackageFilePathname;` — On disk.
- L67 _public member_ `EWarningTypes WarningType = EWarningTypes::None;`
- L68 _public member_ `FText WarningText;`

### `Source/Developer/UnsavedAssetsTracker/Source/Public/UnsavedAssetsTrackerModule.h` (Public)


#### class `FUnsavedAssetsTrackerModule`  
`class FUnsavedAssetsTrackerModule : public IModuleInterface`  
_L36-88_
- inherits: `IModuleInterface`
- desc: Tracks assets that has in-memory modification not saved to disk yet and checks the source control states of those assets when a source control provider is available.
- L40 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L41 _public prototype_ `virtual void ShutdownModule() override;`
- L46 _public function_ `static inline FUnsavedAssetsTrackerModule& Get()` — Retrieve the module instance.
- L52 _public prototype_ `int32 GetUnsavedAssetNum() const;` — Returns the number of unsaved assets currently tracked.
- L55 _public prototype_ `TArray<FString> GetUnsavedAssets() const;` — Returns the list of unsaved assets.
- L58 _public prototype_ `bool IsAssetUnsaved(const FString& FileAbsPathname) const;` — Check if the input asset is unsaved.
- L61 _public prototype_ `TSharedRef<SWidget> MakeUnsavedAssetsStatusBarWidget();` — Construct the widget for the Editor status bar.
- L64 _public prototype_ `bool PromptToSavePackages();` — Displays a dialog prompting the user to save unsaved packages.
- L67 _public member_ `FOnUnsavedAssetAdded OnUnsavedAssetAdded;` — Invoked when a file is added to the unsaved list.
- L70 _public member_ `FOnUnsavedAssetRemoved OnUnsavedAssetRemoved;` — Invoked when a file is removed from the unsaved list.
- L74 _public member_ `FPreUnsavedAssetAutoCheckout PreUnsavedAssetAutoCheckout;` — Every notified File/Operation combination is followed by one of the Cancel/Success/Failure notifications below
- L77 _public member_ `FPostUnsavedAssetAutoCheckout PostUnsavedAssetAutoCheckoutCancel;` — Invoked after an asset has been cancelled for automatic check out
- L80 _public member_ `FPostUnsavedAssetAutoCheckout PostUnsavedAssetAutoCheckout;` — Invoked after an asset has been checked out of source control
- L83 _public member_ `FPostUnsavedAssetAutoCheckout PostUnsavedAssetAutoCheckoutFailure;` — Invoked after an asset failed to be checked out of source control
- L86 _private member_ `TSharedPtr<FUnsavedAssetsTracker> UnsavedAssetTracker;`
- L87 _private member_ `TSharedPtr<FUnsavedAssetsAutoCheckout> UnsavedAssetAutoCheckout;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UNSAVEDASSETSTRACKER_API`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnsavedAssetAdded, const FString& );` — Invoked when an asset was modified in memory and added to the tracker list.
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnsavedAssetAdded, const FString& );` — Invoked when an asset was modified in memory and added to the tracker list.
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnsavedAssetRemoved, const FString& );` — Invoked when an asset modified in memory was saved and removed from the tracker list.
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnsavedAssetRemoved, const FString& );` — Invoked when an asset modified in memory was saved and removed from the tracker list.
- L27 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPreUnsavedAssetAutoCheckout, const FString& , FSourceControlOperationRef& );` — Invoked before an asset is potentially automatically checked out of source control
- L27 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPreUnsavedAssetAutoCheckout, const FString& , FSourceControlOperationRef& );` — Invoked before an asset is potentially automatically checked out of source control
- L30 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPostUnsavedAssetAutoCheckout, const FString& , FSourceControlOperationRef const& );` — Invoked after an asset has been checked out of source control
- L30 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPostUnsavedAssetAutoCheckout, const FString& , FSourceControlOperationRef const& );` — Invoked after an asset has been checked out of source control
