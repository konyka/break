# Developer / Merge

- module root: `Source/Developer/Merge`
- headers: 8; symbols: 144
- symbol kinds: class=6, delegate=3, enum=3, enumerator=11, function=12, macro=1, member=48, namespace=3, prototype=54, struct=3
- PrivateDependencyModuleNames: AssetTools, Core, CoreUObject, EditorFramework, Engine, GraphEditor, InputCore, Kismet, PropertyEditor, Slate, SlateCore, SourceControl, UnrealEd

### `Source/Developer/Merge/Private/BlueprintMergeData.h` (Private)


#### struct `FBlueprintMergeData`  
`struct FBlueprintMergeData`  
_L11-52_
- desc: This data is shared by the various controls (graph view, components view, and defaults view) that are presented as part of the merge tool. Each view keeps its own shallow copy of the data:
- L13 _public function_ `FBlueprintMergeData() : OwningEditor() , BlueprintLocal(NULL) , RevisionLocal(FRevisionInfo::InvalidRevision()) , BlueprintBase(NULL) , RevisionBase(FRevisionInfo::InvalidRevision()) , BlueprintRemote(NULL) , RevisionRemote(FRevisionInfo::InvalidRevision())`
- L24 _public function_ `FBlueprintMergeData( TWeakPtr<class FBlueprintEditor> InOwningEditor , const class UBlueprint* InBlueprintLocal , const class UBlueprint* InBlueprintBase , FRevisionInfo InRevisionBase , const class UBlueprint* InBlueprintRemote , FRevisionInfo InRevisionRemote ) : OwningEditor( InOwningEditor ) , BlueprintLocal( InBlueprintLocal ) , RevisionLocal( FRevisionInfo::InvalidRevision()) , BlueprintBase( InBlueprintBase ) , RevisionBase( InRevisionBase ) , BlueprintRemote( InBlueprintRemote ) , RevisionRemote( InRevisionRemote )`
- L42 _public member_ `TWeakPtr<class FBlueprintEditor> OwningEditor;`
- L44 _public member_ `const class UBlueprint* BlueprintLocal;`
- L45 _public member_ `FRevisionInfo RevisionLocal;`
- L47 _public member_ `const class UBlueprint* BlueprintBase;`
- L48 _public member_ `FRevisionInfo RevisionBase;`
- L50 _public member_ `const class UBlueprint* BlueprintRemote;`
- L51 _public member_ `FRevisionInfo RevisionRemote;`

#### enum `EMergeParticipant::Type`  
`enum Type`  
_L56-63_
- L58 _public enumerator_ `Remote`
- L59 _public enumerator_ `Base`
- L60 _public enumerator_ `Local`
- L62 _public enumerator_ `Max_None`

#### Free symbols / members of external scopes

- L54 _namespace_ `namespace EMergeParticipant`
- L66 _delegate_ `DECLARE_DELEGATE(FOnMergeNodeSelected);`
- L66 _prototype_ `DECLARE_DELEGATE(FOnMergeNodeSelected);`

### `Source/Developer/Merge/Private/MergeUtils.h` (Private)


#### enum `EMergeAssetId::Type`  
`enum Type`  
_L15-21_
- L17 _public enumerator_ `MergeRemote = 0`
- L18 _public enumerator_ `MergeBase`
- L19 _public enumerator_ `MergeLocal`
- L20 _public enumerator_ `Count`

#### struct `FMergeToolUtils`  
`struct FMergeToolUtils`  
_L25-72_
- desc: Unified helper lib, serving shared utility functions across the merge module.
- L34 _public prototype_ `static FSourceControlStatePtr GetSourceControlState(const FString& PackageName);` — Retrieves the source-control state of a specified package. @param  PackageName  The name of the asset package that you want state for. @return An invalid source-control pointer if the package doesn't exist, or if it doesn't have any source-control state; otherwise, a valid source-control state object.
- L44 _public prototype_ `static UObject const* LoadRevision(const FString& AssetName, const ISourceControlRevision& DesiredRevision);` — Attempts to load the specified asset from the supplied source-control revision. @param  AssetName		The name of the asset you want loaded from the revision. @param  DesiredRevision	The source-control revision you want loaded. @return The asset object you wanted loaded, could be null if the asset wasn't found in the supplied revision.
- L53 _public prototype_ `static UObject const* LoadRevision(const FString& PackageName, const FRevisionInfo& DesiredRevision);` — Attempts to load the supplied revision of the specified package. @param  PackageName		The name of the package you want loaded. @param  DesiredRevision	Details the revision you want loaded. @return The package's asset object, could be null if the specified revision could not be loaded.
- L62 _public prototype_ `static UObject const* LoadRevision(const UObject* AssetObject, const FRevisionInfo& DesiredRevision);` — Attempts to load the specified revision of the supplied asset. @param  AssetObject		The asset you want a different revision of. @param  DesiredRevision	Details the revision you want loaded. @return The requested version of the specified asset object, could be null if the supplied revision failed to load.
- L71 _public prototype_ `static UObject const* LoadAssetFromPackage(const FString& PackageFileName, const FString& AssetName);` — Attempts to load the specified asset from the provided package. @param  PackageFileName  The file name of the package where to look for the asset. @param  AssetName        The name of the asset you want loaded from the package. @return The asset object you wanted loaded, could be null if the asset wasn't found in the package.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace EMergeAssetId`

### `Source/Developer/Merge/Private/SBlueprintMerge.h` (Private)


#### class `SBlueprintMerge`  
`class SBlueprintMerge : public SCompoundWidget`  
_L18-132_
- inherits: `SCompoundWidget`
- L21 _public prototype_ `SBlueprintMerge();`
- L23 _public function_ `SLATE_BEGIN_ARGS(SBlueprintMerge) : _bForcePickAssets(false)`
- L26 _public prototype_ `SLATE_ARGUMENT(bool, bForcePickAssets) SLATE_EVENT(FOnMergeResolved, OnMergeResolved) SLATE_END_ARGS() void Construct(const FArguments InArgs, const FBlueprintMergeData& InData);`
- L34 _private prototype_ `UBlueprint* GetTargetBlueprint();` — Helper functions
- L37 _private prototype_ `void NextDiff();` — Event handlers
- L38 _private prototype_ `void PrevDiff();`
- L39 _private prototype_ `bool HasNextDiff() const;`
- L40 _private prototype_ `bool HasPrevDiff() const;`
- L42 _private prototype_ `void NextConflict();`
- L43 _private prototype_ `void PrevConflict();`
- L44 _private prototype_ `bool HasNextConflict() const;`
- L45 _private prototype_ `bool HasPrevConflict() const;`
- L47 _private prototype_ `void OnStartMerge();`
- L48 _private prototype_ `void OnFinishMerge();`
- L49 _private prototype_ `void OnCancelClicked();`
- L50 _private prototype_ `void OnModeChanged(FName NewMode);`
- L51 _private prototype_ `void OnAcceptRemote();`
- L52 _private prototype_ `void OnAcceptLocal();`
- L53 _private prototype_ `void ResolveMerge(UBlueprint* Result);`
- L62 _private prototype_ `bool IsActivelyMerging() const;` — If the user has yet to pick their remote/base/local assets, then they're not "actively" merging yet. This query checks the state of the merge-tool to see if the user has selected to "Start Merge" yet. @return False if the AssetPickerControl should be up, otherwise true.
- L71 _private prototype_ `bool CanStartMerge() const;` — The user cannot start a merge until they have chosen a remote, base, & local asset/revision to use in the merge. This checks the state of their choices. @return True, if the user has selected all three merge assets.
- L81 _private prototype_ `void OnMergeAssetSelected(EMergeAssetId::Type AssetId, const FAssetRevisionInfo& AssetInfo);` — Callback function, utilized every time the user picks an asset/revision in the AssetPickerControl view. Records the user's choices, so this can start the merge appropriately. @param  AssetId		Defines the asset that was altered (remote, base, or local). @param  AssetInfo	Defines the asset selection (name, revision, etc.)
- L83 _private member_ `FBlueprintMergeData Data;`
- L84 _private member_ `FString BackupSubDir;`
- L86 _private member_ `TSharedPtr<SBox> MainView;`
- L93 _private member_ `FString RemotePath;` — We track the package name-paths for the remote, base, & local assets (so we know what to load when the user starts an active merge)... Used to determine when a merge can be started.
- L94 _private member_ `FString BasePath;`
- L95 _private member_ `FString LocalPath;`
- L102 _private member_ `FString LocalBackupPath;` — When we make a malformed copy (readable data only) of the local Blueprint, then we fill this in with a backup file path; that way, the file can be copied for OnAcceptLocal(), instead of the loaded Blueprint object (which is "malformed").
- L104 _private member_ `TSharedPtr<SWidget> GraphControl;`
- L105 _private member_ `TSharedPtr<SWidget> TreeControl;`
- L106 _private member_ `TSharedPtr<SWidget> DetailsControl;`
- L107 _private member_ `TSharedPtr<SWidget> AssetPickerControl;`
- L109 _private member_ `bool bIsPickingAssets;`
- L110 _private member_ `FOnMergeResolved OnMergeResolved;`
- L113 _private member_ `TSharedPtr<SBorder> TreeViewContainer;` — Container widget for the treeview of differences:
- L116 _private member_ `TSharedPtr< STreeView< TSharedPtr< class FBlueprintDifferenceTreeEntry > > > DifferencesTreeView;` — Treeview to display all differences collected across all panels:
- L119 _private member_ `TArray< TSharedPtr<class FBlueprintDifferenceTreeEntry> > PrimaryDifferencesList;` — List of differences collected across all panels:
- L122 _private member_ `TArray< TSharedPtr<class FBlueprintDifferenceTreeEntry> > RealDifferences;` — List of all differences, cached so that we can iterate only the differences and not labels, etc:
- L125 _private member_ `TArray< TSharedPtr<class FBlueprintDifferenceTreeEntry> > MergeConflicts;` — List of all merge conflicts:
- L130 _private member_ `TArray< TSharedPtr<struct FDiffSingleResult> > LocalDiffResults;` — This has to be allocated here because SListView cannot own the list that it is displaying. It also seems like the display list *has* to be a list of TSharedPtrs.
- L131 _private member_ `TArray< TSharedPtr<struct FDiffSingleResult> > RemoteDiffResults;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MERGE_API`

### `Source/Developer/Merge/Private/SMergeAssetPickerView.h` (Private)


#### struct `FAssetRevisionInfo`  
`struct FAssetRevisionInfo`  
_L16-20_
- L18 _public member_ `FString AssetName;`
- L19 _public member_ `FRevisionInfo Revision;`

#### class `SMergeAssetPickerView`  
`class SMergeAssetPickerView : public SCompoundWidget`  
_L26-43_
- inherits: `SCompoundWidget`
- L31 _public function_ `SLATE_BEGIN_ARGS(SMergeAssetPickerView)`
- L32 _public prototype_ `SLATE_EVENT(FOnMergeAssetChanged, OnAssetChanged) SLATE_END_ARGS() void Construct(const FArguments InArgs, const FBlueprintMergeData& InData);`
- L38 _private prototype_ `void HandleAssetChange(const UObject* NewAsset, EMergeAssetId::Type PanelId);`
- L39 _private prototype_ `void HandleRevisionChange(const FRevisionInfo& NewRevision, EMergeAssetId::Type PanelId);`
- L41 _private member_ `FOnMergeAssetChanged OnAssetChanged;`
- L42 _private member_ `FAssetRevisionInfo MergeAssetSet[EMergeAssetId::Count];`

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMergeAssetChanged, EMergeAssetId::Type, const FAssetRevisionInfo&) public: SLATE_BEGIN_ARGS(SMergeAssetPickerView){} SLATE_EVENT(FOnMergeAssetChanged, OnAssetChanged) SLATE_END_ARGS() void Construct(const FArguments InArgs, const FBlueprintMergeData& InData);`

### `Source/Developer/Merge/Private/SMergeDetailsView.h` (Private)


#### class `SMergeDetailsView`  
`class SMergeDetailsView : public SCompoundWidget`  
_L11-41_
- inherits: `SCompoundWidget`
- L14 _public prototype_ `virtual ~SMergeDetailsView() = default;`
- L16 _public function_ `SLATE_BEGIN_ARGS(SMergeDetailsView)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments InArgs , const FBlueprintMergeData& InData , FOnMergeNodeSelected SelectionCallback , TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutTreeEntries , TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutRealDifferences , TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutConflicts);`
- L27 _private prototype_ `void HighlightDifference(FPropertySoftPath Path);`
- L28 _private prototype_ `FDetailsDiff& GetRemoteDetails();`
- L29 _private prototype_ `FDetailsDiff& GetBaseDetails();`
- L30 _private prototype_ `FDetailsDiff& GetLocalDetails();`
- L32 _private member_ `TArray< FPropertySoftPath > MergeConflicts;`
- L33 _private member_ `int CurrentMergeConflict;`
- L35 _private member_ `FBlueprintMergeData Data;`
- L36 _private member_ `TArray< FDetailsDiff > DetailsViews;`
- L39 _private member_ `TArray< FPropertySoftPath > DifferingProperties;` — These have been duplicated from FCDODiffControl, opportunity to refactor exists:
- L40 _private member_ `int CurrentDifference;`

### `Source/Developer/Merge/Private/SMergeGraphView.h` (Private)


#### class `SMergeGraphView`  
`class SMergeGraphView : public SCompoundWidget`  
_L14-51_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SMergeGraphView)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments InArgs , const FBlueprintMergeData& InData , FOnMergeNodeSelected SelectionCallback , TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutTreeEntries , TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutRealDifferences , TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutConflicts);`
- L28 _private prototype_ `void FocusGraph(const FString& GraphPath);` — Helper functions and event handlers:
- L29 _private prototype_ `void HighlightEntry(const struct FMergeGraphRowEntry& Conflict);`
- L30 _private prototype_ `bool HasNoDifferences() const;`
- L32 _private prototype_ `TSharedRef<SDockTab> CreateGraphDiffViews(const FSpawnTabArgs& Args);`
- L33 _private prototype_ `TSharedRef<SDockTab> CreateMyBlueprintsViews(const FSpawnTabArgs& Args);`
- L35 _private function_ `FDiffPanel& GetRemotePanel()`
- L36 _private function_ `FDiffPanel& GetBasePanel()`
- L37 _private function_ `FDiffPanel& GetLocalPanel()`
- L39 _private prototype_ `FReply OnToggleLockView();`
- L40 _private prototype_ `const FSlateBrush* GetLockViewImage() const;`
- L42 _private member_ `TArray< FDiffPanel > DiffPanels;`
- L43 _private member_ `FBlueprintMergeData Data;`
- L45 _private member_ `TSharedPtr< TArray< struct FMergeGraphEntry > > Differences;`
- L47 _private member_ `bool bViewsAreLocked;`
- L50 _private member_ `TSharedPtr<FTabManager> TabManager;` — We can't use the global tab manager because we need to instance the merge control, so we have our own tab manager:

### `Source/Developer/Merge/Private/SMergeTreeView.h` (Private)


#### class `SMergeTreeView`  
`class SMergeTreeView : public SCompoundWidget`  
_L12-42_
- inherits: `SCompoundWidget`
- L15 _public prototype_ `virtual ~SMergeTreeView() = default;`
- L17 _public function_ `SLATE_BEGIN_ARGS(SMergeTreeView)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments InArgs , const FBlueprintMergeData& InData , FOnMergeNodeSelected SelectionCallback , TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutTreeEntries , TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutRealDifferences , TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutConflicts);`
- L28 _private prototype_ `void HighlightDifference( FSCSIdentifier VarName, FPropertySoftPath Property );`
- L30 _private prototype_ `TSharedRef<FSCSDiff>& GetRemoteView();`
- L31 _private prototype_ `TSharedRef<FSCSDiff>& GetBaseView();`
- L32 _private prototype_ `TSharedRef<FSCSDiff>& GetLocalView();`
- L34 _private member_ `FBlueprintMergeData Data;`
- L35 _private member_ `TArray< TSharedRef<FSCSDiff> > SCSViews;`
- L37 _private member_ `FSCSDiffRoot MergeConflicts;`
- L38 _private member_ `int CurrentMergeConflict;`
- L40 _private member_ `FSCSDiffRoot DifferingProperties;`
- L41 _private member_ `int CurrentDifference;`

### `Source/Developer/Merge/Public/Merge.h` (Public)


#### enum `EMergeResult::Type`  
`enum Type`  
_L13-18_
- L15 _public enumerator_ `Unknown`
- L16 _public enumerator_ `Completed`
- L17 _public enumerator_ `Cancelled`

#### class `IMerge`  
`class IMerge : public IModuleInterface`  
_L25-63_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L36 _public function_ `static inline IMerge& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L46 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L56 _public prototype_ `virtual TSharedPtr<class SDockTab> GenerateMergeWidget( const UBlueprint& Object, TSharedRef< class FBlueprintEditor> Editor ) = 0;` — Generates a widget used to perform a three way merge operation. @return The merge view widget
- L57 _public prototype_ `virtual TSharedPtr<class SDockTab> GenerateMergeWidget(const UBlueprint* BaseBlueprint, const UBlueprint* RemoteBlueprint, const UBlueprint* LocalBlueprint, const FOnMergeResolved& MergeResolutionCallback, TSharedRef<class FBlueprintEditor> Editor) = 0;`
- L62 _public prototype_ `virtual bool PendingMerge(const UBlueprint& BlueprintObj) const = 0;` — @return whether the blueprint is in a conflicted state, and can therefore be merged.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace EMergeResult`
- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMergeResolved, UPackage*, EMergeResult::Type);`
- L20 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnMergeResolved, UPackage*, EMergeResult::Type);`
