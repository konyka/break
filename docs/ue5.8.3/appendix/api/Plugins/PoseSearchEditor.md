# Plugins / PoseSearchEditor

- module root: `Plugins/Animation/PoseSearch/Source/Editor`
- headers: 42; symbols: 1164
- symbol kinds: class=59, delegate=8, enum=3, enumerator=11, externvar=1, function=243, macro=5, member=291, namespace=62, prototype=439, struct=31, typedef=9, variable=2
- PrivateDependencyModuleNames: AdvancedPreviewScene, AnimationEditor, ApplicationCore, AssetDefinition, BlueprintGraph, DetailCustomizations, EditorFramework, EditorStyle, ToolWidgets
- PublicDependencyModuleNames: AnimGraph, AnimGraphRuntime, AnimationBlueprintLibrary, AnimationCore, BlendStack, BlendStackEditor, Chooser, ChooserEditor, Core, CoreUObject, Engine, GameplayInsights, InputCore, PoseSearch, PropertyEditor, RewindDebuggerInterface, Slate, SlateCore, TraceAnalysis, TraceInsights, TraceLog, TraceServices, UnrealEd

### `Plugins/Animation/PoseSearch/Source/Editor/Private/PoseSearchAssetDefinitions.h` (Private)


#### class `UAssetDefinition_PoseSearchDatabase`  
`class UAssetDefinition_PoseSearchDatabase : public UAssetDefinitionDefault`  
_L20-32_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L25 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L26 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L27 _public function_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override`
- L29 _public function_ `virtual FText GetAssetDisplayName() const override`
- L30 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L31 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

#### class `UAssetDefinition_PoseSearchSchema`  
`class UAssetDefinition_PoseSearchSchema : public UAssetDefinitionDefault`  
_L35-46_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L40 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L41 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L42 _public function_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override`
- L44 _public function_ `virtual FText GetAssetDisplayName() const override`
- L45 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

#### class `UAssetDefinition_PoseSearchNormalizationSet`  
`class UAssetDefinition_PoseSearchNormalizationSet : public UAssetDefinitionDefault`  
_L49-60_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L54 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L55 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L56 _public function_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override`
- L58 _public function_ `virtual FText GetAssetDisplayName() const override`
- L59 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

#### class `UAssetDefinition_PoseSearchInteractionAsset`  
`class UAssetDefinition_PoseSearchInteractionAsset : public UAssetDefinitionDefault`  
_L63-75_
- reflection: `UCLASS(Experimental)`
- inherits: `UAssetDefinitionDefault`
- L68 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L69 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L70 _public function_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override`
- L72 _public function_ `virtual FText GetAssetDisplayName() const override`
- L73 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L74 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PoseSearch` (scope `UE`)
- L14 _prototype_ `FLinearColor GetAssetColor();` (scope `UE::PoseSearch`)
- L15 _prototype_ `TConstArrayView<FAssetCategoryPath> GetAssetCategories();` (scope `UE::PoseSearch`)
- L16 _prototype_ `UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData);` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Editor/Private/PoseSearchDatabaseAssetBrowser.h` (Private)


#### class `UE::PoseSearch::SPoseSearchDatabaseAssetBrowser`  
`class SPoseSearchDatabaseAssetBrowser : public SBox`  
_L15-42_
- inherits: `SBox`
- L19 _public function_ `SLATE_BEGIN_ARGS(SPoseSearchDatabaseAssetBrowser)`
- L20 _public prototype_ `SLATE_END_ARGS();`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FDatabaseViewModel> InViewModel);`
- L24 _public prototype_ `void RefreshView();`
- L29 _private member_ `TSharedPtr<SBox> AssetBrowserBox;`
- L30 _private member_ `TSharedPtr<FDatabaseViewModel> DatabaseViewModel;`
- L32 _private prototype_ `void OnAssetDoubleClicked(const FAssetData& AssetData);`
- L33 _private prototype_ `bool OnShouldFilterAsset(const FAssetData& AssetData);`
- L36 _private member_ `FRefreshAssetViewDelegate RefreshAssetViewDelegate;` — We need to be able to refresh the asset list if requested (i.e. Schema changes)
- L39 _private member_ `FDelegateHandle OnPropertyChangedHandle;` — Keep track of delegate used to listen for pose search schema changes
- L41 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent) const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Private/PoseSearchDatabaseEditorClipboard.h` (Private)


#### class `UPoseSearchDatabaseItemCopyObject`  
`class UPoseSearchDatabaseItemCopyObject : public UObject`  
_L11-23_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: Object used to export FPoseSearchDatabaseAnimationAssetBase and derived classes to clipboard
- L18 _public member_ `FName ClassName = NAME_None;` — `UPROPERTY()`
- L22 _public member_ `FString Content;` — `UPROPERTY()` — Store's exported database asset as a string

#### class `UPoseSearchDatabaseEditorClipboardContent`  
`class UPoseSearchDatabaseEditorClipboardContent : public UObject`  
_L26-54_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- L33 _public member_ `TArray<TObjectPtr<UPoseSearchDatabaseItemCopyObject>> DatabaseItems;` — `UPROPERTY(Export)`
- L38 _public prototype_ `void CopyDatabaseItem(const FPoseSearchDatabaseAnimationAssetBase* InItem);` — Store copy of database item.
- L41 _public prototype_ `void CopyToClipboard();` — Copy contents to system's clipboard
- L44 _public prototype_ `void PasteToDatabase(UPoseSearchDatabase* InTargetDatabase) const;` — Paste all items from clipboard to a given pose search database. Note that this will mark the target database as dirty.
- L47 _public prototype_ `static bool CanPasteContentFromClipboard(const FString & InTextToImport);` — Determine if a pose search database clipboard content can be constructed from system's clipboard.
- L50 _public prototype_ `static UPoseSearchDatabaseEditorClipboardContent* CreateFromClipboard();` — Attempt to construct a pose search database clipboard content from system's clipboard. Will return nullptr if it fails to do so.
- L53 _public prototype_ `static UPoseSearchDatabaseEditorClipboardContent* Create();` — Create new transient clipboard content object

### `Plugins/Animation/PoseSearch/Source/Editor/Private/PoseSearchDatabaseEditorUtils.h` (Private)


#### struct `UE::PoseSearch::FPoseSearchEditorUtils`  
`struct FPoseSearchEditorUtils`  
_L12-15_
- L14 _public prototype_ `static bool IsAssetCompatibleWithDatabase(const UPoseSearchDatabase* InDatabase, const FAssetData & InAssetData);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Private/PoseSearchDebugger.h` (Private)


#### class `UE::PoseSearch::FDebugger`  
`class FDebugger : public TSharedFromThis<FDebugger>, public IRewindDebuggerExtension`  
_L23-62_
- inherits: `TSharedFromThis<FDebugger>,IRewindDebuggerExtension`
- desc: PoseSearch debugger, containing the data to be acquired and relayed to the view
- L26 _public prototype_ `virtual void Update(float DeltaTime, IRewindDebugger* InRewindDebugger) override;`
- L27 _public prototype_ `virtual ~FDebugger() = default;`
- L29 _public function_ `static FDebugger* Get()`
- L30 _public prototype_ `static void Initialize();`
- L31 _public prototype_ `static void Shutdown();`
- L32 _public function_ `virtual FString GetName()`
- L35 _public prototype_ `static bool IsPIESimulating();` — Shared data from the Rewind Debugger singleton
- L36 _public prototype_ `static bool IsRecording();`
- L37 _public prototype_ `static double GetRecordingDuration();`
- L38 _public prototype_ `static UWorld* GetWorld();`
- L39 _public prototype_ `static const IRewindDebugger* GetRewindDebugger();`
- L42 _public prototype_ `TSharedPtr<SDebuggerView> GenerateInstance(uint64 InAnimInstanceId, int32 InWantedSearchId = InvalidSearchId);` — Generates the slate debugger view widget
- L43 _public function_ `TWeakPtr<SDebuggerView> GetDebuggerView()`
- L47 _private prototype_ `static void OnViewClosed(uint64 InAnimInstanceId);` — Removes the reference from the model array when closed, destroying the model
- L50 _private prototype_ `static TSharedPtr<FDebuggerViewModel> GetViewModel(uint64 InAnimInstanceId);` — Acquire view model from the array
- L53 _private member_ `const IRewindDebugger* RewindDebugger = nullptr;` — Last stored Rewind Debugger
- L56 _private member_ `TArray<TSharedRef<FDebuggerViewModel>> ViewModels;` — List of all active debugger instances
- L58 _private member_ `TWeakPtr<SDebuggerView> DebuggerView;`
- L61 _private member_ `static FDebugger* Debugger;` — Internal instance

#### class `UE::PoseSearch::FSearchTrack`  
`class FSearchTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L64-84_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- L67 _public prototype_ `FSearchTrack(uint64 InObjectId, int32 InSearchId, FText InTrackName);`
- L68 _public prototype_ `int32 GetSearchId() const;`
- L71 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L72 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L73 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L74 _private function_ `virtual FName GetNameInternal() const override`
- L75 _private prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L76 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L77 _private prototype_ `virtual bool UpdateInternal() override;`
- L79 _private member_ `TSharedPtr<SCostTimelineView> CostTimelineView;`
- L81 _private member_ `uint64 ObjectId;`
- L82 _private member_ `FText TrackName;`
- L83 _private member_ `FSlateIcon Icon;`

#### class `UE::PoseSearch::FDebuggerTrack`  
`class FDebuggerTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L90-109_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- desc: Creates the slate widgets associated with the PoseSearch debugger when prompted by the Rewind Debugger
- L93 _public prototype_ `explicit FDebuggerTrack(uint64 InObjectId);`
- L96 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L97 _private function_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override`
- L98 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L99 _private function_ `virtual FName GetNameInternal() const override`
- L100 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L101 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L102 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L103 _private prototype_ `virtual bool UpdateInternal() override;`
- L105 _private member_ `uint64 ObjectId;`
- L106 _private member_ `FSlateIcon Icon;`
- L108 _private member_ `TArray<TSharedPtr<FSearchTrack>> SearchTracks;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Private/PoseSearchDebuggerDatabaseColumns.h` (Private)


#### struct `UE::PoseSearch::DebuggerDatabaseColumns::IColumn`  
`struct IColumn : TSharedFromThis<IColumn>`  
_L31-62_
- inherits: `TSharedFromThis<IColumn>`
- desc: Column struct to represent each column in the debugger database
- L33 _public function_ `explicit IColumn(int32 InSortIndex, bool InEnabled = true) : SortIndex(InSortIndex) , bEnabled(InEnabled)`
- L40 _public prototype_ `virtual ~IColumn() = default;`
- L42 _public member_ `FName ColumnId;`
- L45 _public member_ `int32 SortIndex = 0;` — Sorted left to right based on this index
- L47 _public member_ `float Width = 1.0f;` — Current width, starts at 1 to be evenly spaced between all columns
- L49 _public member_ `bool bEnabled = false;` — Disabled selectively with view options
- L51 _public prototype_ `virtual FText GetLabel() const = 0;`
- L52 _public function_ `virtual FText GetLabelTooltip() const`
- L54 _public typedef_ `using FRowDataRef = TSharedRef<FDebuggerDatabaseRowData>;`
- L55 _public typedef_ `using FSortPredicate = TFunction<bool(const FRowDataRef&, const FRowDataRef&)>;`
- L57 _public prototype_ `virtual FSortPredicate GetSortPredicate() const = 0;`
- L59 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidget(const FRowDataRef& RowData) const = 0;`
- L61 _public prototype_ `virtual float ComputeColumnWidth(TConstArrayView<FRowDataRef> Rows) const = 0;`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::ITextColumn`  
`struct ITextColumn : IColumn`  
_L65-111_
- inherits: `IColumn`
- desc: Column struct to represent each column in the debugger database
- L67 _public function_ `explicit ITextColumn(int32 InSortIndex, bool InEnabled = true) : IColumn(InSortIndex, InEnabled)`
- L72 _public prototype_ `virtual ~ITextColumn() = default;`
- L74 _public function_ `virtual TSharedRef<SWidget> GenerateWidget(const FRowDataRef& RowData) const override`
- L87 _protected prototype_ `virtual FText GetRowText(const FRowDataRef& Row) const = 0;`
- L88 _protected function_ `virtual FText GetRowToolTipText(const FRowDataRef& Row) const`
- L92 _protected function_ `virtual FSlateColor GetColorAndOpacity(const FRowDataRef& Row) const`
- L97 _protected function_ `virtual float ComputeColumnWidth(TConstArrayView<TSharedRef<FDebuggerDatabaseRowData>> Rows) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FPoseIdx`  
`struct FPoseIdx : ITextColumn`  
_L113-145_
- inherits: `ITextColumn`
- L117 _public function_ `virtual FText GetLabel() const override`
- L123 _public function_ `virtual FText GetLabelTooltip() const override`
- L129 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L137 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FAssetIdx`  
`struct FAssetIdx : ITextColumn`  
_L147-179_
- inherits: `ITextColumn`
- L151 _public function_ `virtual FText GetLabel() const override`
- L157 _public function_ `virtual FText GetLabelTooltip() const override`
- L163 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L171 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FDatabaseName`  
`struct FDatabaseName : IColumn`  
_L182-273_
- inherits: `IColumn`
- L184 _public member_ `TSharedPtr<FDebuggerViewModel> DebuggerViewModel;`
- L186 _public function_ `FDatabaseName(int32 InSortIndex, TSharedPtr<FDebuggerViewModel> InDebuggerViewModel) : IColumn(InSortIndex) , DebuggerViewModel(InDebuggerViewModel)`
- L192 _public function_ `virtual FText GetLabel() const override`
- L198 _public function_ `virtual FText GetLabelTooltip() const override`
- L204 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L212 _public function_ `virtual TSharedRef<SWidget> GenerateWidget(const FRowDataRef& RowData) const override`
- L259 _public function_ `virtual float ComputeColumnWidth(TConstArrayView<FRowDataRef> Rows) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FAssetName`  
`struct FAssetName : IColumn`  
_L275-383_
- inherits: `IColumn`
- L279 _public function_ `virtual FText GetLabel() const override`
- L285 _public function_ `virtual FText GetLabelTooltip() const override`
- L291 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L299 _public function_ `virtual TSharedRef<SWidget> GenerateWidget(const FRowDataRef& RowData) const override`
- L369 _public function_ `virtual float ComputeColumnWidth(TConstArrayView<FRowDataRef> Rows) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FFrame`  
`struct FFrame : ITextColumn`  
_L385-417_
- inherits: `ITextColumn`
- L389 _public function_ `virtual FText GetLabel() const override`
- L395 _public function_ `virtual FText GetLabelTooltip() const override`
- L401 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L409 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FTime`  
`struct FTime : ITextColumn`  
_L419-451_
- inherits: `ITextColumn`
- L423 _public function_ `virtual FText GetLabel() const override`
- L429 _public function_ `virtual FText GetLabelTooltip() const override`
- L435 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L443 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FPercentage`  
`struct FPercentage : ITextColumn`  
_L453-485_
- inherits: `ITextColumn`
- L457 _public function_ `virtual FText GetLabel() const override`
- L463 _public function_ `virtual FText GetLabelTooltip() const override`
- L469 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L477 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FCost`  
`struct FCost : ITextColumn`  
_L487-524_
- inherits: `ITextColumn`
- L491 _public function_ `virtual FText GetLabel() const override`
- L497 _public function_ `virtual FText GetLabelTooltip() const override`
- L503 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L511 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`
- L520 _public function_ `virtual FSlateColor GetColorAndOpacity(const FRowDataRef& Row) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FPCACost`  
`struct FPCACost : ITextColumn`  
_L526-563_
- inherits: `ITextColumn`
- L530 _public function_ `virtual FText GetLabel() const override`
- L536 _public function_ `virtual FText GetLabelTooltip() const override`
- L542 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L550 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`
- L559 _public function_ `virtual FSlateColor GetColorAndOpacity(const FRowDataRef& Row) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FChannelBreakdownCostColumn`  
`struct FChannelBreakdownCostColumn : ITextColumn`  
_L565-626_
- inherits: `ITextColumn`
- L567 _public function_ `FChannelBreakdownCostColumn(int32 SortIndex, int32 InBreakdownCostIndex, const FText& InLabel) : ITextColumn(SortIndex) , Label(InLabel) , LabelTooltip(FText::Format(LOCTEXT("ColumnLabelTooltipChannelBreakdownCost", "Breakdown Cost for the Channel '{0}'"), InLabel)) , BreakdownCostIndex(InBreakdownCostIndex)`
- L575 _public function_ `virtual FText GetLabel() const override`
- L580 _public function_ `virtual FText GetLabelTooltip() const override`
- L585 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L601 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`
- L614 _public function_ `virtual FSlateColor GetColorAndOpacity(const FRowDataRef& Row) const override`
- L623 _public member_ `FText Label;`
- L624 _public member_ `FText LabelTooltip;`
- L625 _public member_ `int32 BreakdownCostIndex = INDEX_NONE;`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FCostModifier`  
`struct FCostModifier : ITextColumn`  
_L628-660_
- inherits: `ITextColumn`
- L632 _public function_ `virtual FText GetLabel() const override`
- L638 _public function_ `virtual FText GetLabelTooltip() const override`
- L644 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L652 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FContinuingPoseCost`  
`struct FContinuingPoseCost : ITextColumn`  
_L662-694_
- inherits: `ITextColumn`
- L666 _public function_ `virtual FText GetLabel() const override`
- L672 _public function_ `virtual FText GetLabelTooltip() const override`
- L678 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L686 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FContinuingInteractionCost`  
`struct FContinuingInteractionCost : ITextColumn`  
_L696-728_
- inherits: `ITextColumn`
- L700 _public function_ `virtual FText GetLabel() const override`
- L706 _public function_ `virtual FText GetLabelTooltip() const override`
- L712 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L720 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FContinuingContextInteractionCost`  
`struct FContinuingContextInteractionCost : ITextColumn`  
_L730-762_
- inherits: `ITextColumn`
- L734 _public function_ `virtual FText GetLabel() const override`
- L740 _public function_ `virtual FText GetLabelTooltip() const override`
- L746 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L754 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FNotifyCost`  
`struct FNotifyCost : ITextColumn`  
_L764-796_
- inherits: `ITextColumn`
- L768 _public function_ `virtual FText GetLabel() const override`
- L774 _public function_ `virtual FText GetLabelTooltip() const override`
- L780 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L788 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FMirrored`  
`struct FMirrored : ITextColumn`  
_L799-841_
- inherits: `ITextColumn`
- L803 _public function_ `virtual FText GetLabel() const override`
- L809 _public function_ `virtual FText GetLabelTooltip() const override`
- L815 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L823 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FLooping`  
`struct FLooping : ITextColumn`  
_L843-885_
- inherits: `ITextColumn`
- L847 _public function_ `virtual FText GetLabel() const override`
- L853 _public function_ `virtual FText GetLabelTooltip() const override`
- L859 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L867 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FBlendParameters`  
`struct FBlendParameters : ITextColumn`  
_L887-921_
- inherits: `ITextColumn`
- L891 _public function_ `virtual FText GetLabel() const override`
- L897 _public function_ `virtual FText GetLabelTooltip() const override`
- L903 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L913 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`

#### struct `UE::PoseSearch::DebuggerDatabaseColumns::FPoseCandidateFlags`  
`struct FPoseCandidateFlags : ITextColumn`  
_L923-1041_
- inherits: `ITextColumn`
- L927 _public function_ `virtual FText GetLabel() const override`
- L933 _public function_ `virtual FText GetLabelTooltip() const override`
- L939 _public function_ `virtual FSortPredicate GetSortPredicate() const override`
- L947 _public function_ `virtual FText GetRowText(const FRowDataRef& Row) const override`
- L994 _public function_ `virtual FText GetRowToolTipText(const FRowDataRef& Row) const override`

#### Free symbols / members of external scopes

- L23 _macro_ `#define LOCTEXT_NAMESPACE "PoseSearchDebugger"`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace PoseSearch` (scope `UE`)
- L25 _namespace_ `namespace DebuggerDatabaseColumns` (scope `UE::PoseSearch`)
- L27 _variable_ `constexpr float ColumnWidthPadding = 10.f;` (scope `UE::PoseSearch::DebuggerDatabaseColumns`)
- L28 _variable_ `constexpr float ColumnSortWidthPadding = 20.f;` (scope `UE::PoseSearch::DebuggerDatabaseColumns`)
- L80 _function_ `.Text_Lambda([this, RowData]() -> FText { return GetRowText(RowData); }) .ToolTipText_Lambda([this, RowData]() -> FText { return GetRowToolTipText(RowData); }) .Justification(ETextJustify::Center) .ColorAndOpacity_Lambda([this, RowData] { return GetColorAndOpacity(RowData); });` (scope `UE::PoseSearch::DebuggerDatabaseColumns::ITextColumn::GenerateWidget`)
- L81 _function_ `.ToolTipText_Lambda([this, RowData]() -> FText { return GetRowToolTipText(RowData); }) .Justification(ETextJustify::Center) .ColorAndOpacity_Lambda([this, RowData] { return GetColorAndOpacity(RowData); });` (scope `UE::PoseSearch::DebuggerDatabaseColumns::ITextColumn::GenerateWidget`)
- L83 _function_ `.ColorAndOpacity_Lambda([this, RowData] { return GetColorAndOpacity(RowData); });` (scope `UE::PoseSearch::DebuggerDatabaseColumns::ITextColumn::GenerateWidget`)
- L132 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FPoseIdx::GetSortPredicate`)
- L166 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FAssetIdx::GetSortPredicate`)
- L207 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FDatabaseName::GetSortPredicate`)
- L218 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FDatabaseName::GenerateWidget`)
- L294 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FAssetName::GetSortPredicate`)
- L304 _function_ `.Text_Lambda([RowData]() -> FText { return FText::FromString(RowData->AssetName); }) .TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("SmallText")) .ToolTipText_Lambda([RowData]() -> FText { return FText::Format( LOCTEXT("AssetHyperlinkTooltipFormat", "Open asset '{0}'"), FText::FromString(RowData->AssetPath)); }) .OnNavigate_Lambda([RowData]() { UObject* Asset = nullptr;` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FAssetName::GenerateWidget`)
- L307 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FAssetName::GenerateWidget`)
- L404 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FFrame::GetSortPredicate`)
- L438 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FTime::GetSortPredicate`)
- L472 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FPercentage::GetSortPredicate`)
- L506 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FCost::GetSortPredicate`)
- L545 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FPCACost::GetSortPredicate`)
- L588 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FChannelBreakdownCostColumn::GetSortPredicate`)
- L647 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FCostModifier::GetSortPredicate`)
- L681 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FContinuingPoseCost::GetSortPredicate`)
- L715 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FContinuingInteractionCost::GetSortPredicate`)
- L749 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FContinuingContextInteractionCost::GetSortPredicate`)
- L783 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FNotifyCost::GetSortPredicate`)
- L818 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FMirrored::GetSortPredicate`)
- L862 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FLooping::GetSortPredicate`)
- L906 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FBlendParameters::GetSortPredicate`)
- L942 _function_ `` (scope `UE::PoseSearch::DebuggerDatabaseColumns::FPoseCandidateFlags::GetSortPredicate`)

### `Plugins/Animation/PoseSearch/Source/Editor/Private/PoseSearchDebuggerDatabaseRow.h` (Private)


#### class `UE::PoseSearch::SDebuggerDatabaseRow`  
`class SDebuggerDatabaseRow : public SMultiColumnTableRow<TSharedRef<FDebuggerDatabaseRowData>>`  
_L16-79_
- inherits: `SMultiColumnTableRow<TSharedRef<FDebuggerDatabaseRowData>>`
- desc: Widget representing a single row of the database view
- L18 _private function_ `SLATE_BEGIN_ARGS(SDebuggerDatabaseRow)`
- L19 _private function_ `SLATE_ATTRIBUTE(const SDebuggerDatabaseView::FColumnMap*, ColumnMap) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FDebuggerDatabaseRowData> InRow, const FTableRowStyle& InRowStyle, const FSlateBrush* InRowBrush, FMargin InPaddingMargin )`
- L47 _private function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override`
- L72 _private member_ `TSharedPtr<FDebuggerDatabaseRowData> Row;` — Row data associated with this widget
- L75 _private member_ `const FSlateBrush* RowBrush = nullptr;` — Used for cell styles (active vs database row)
- L78 _private member_ `TAttribute<const SDebuggerDatabaseView::FColumnMap*> ColumnMap;` — Used to grab the column struct given a column name

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Private/PoseSearchDebuggerDatabaseRowData.h` (Private)


#### class `UE::PoseSearch::FDebuggerDatabaseSharedData`  
`class FDebuggerDatabaseSharedData : public TSharedFromThis<FDebuggerDatabaseSharedData>`  
_L12-24_
- inherits: `TSharedFromThis<FDebuggerDatabaseSharedData>`
- L15 _public member_ `TWeakObjectPtr<UPoseSearchDatabase> SourceDatabase;`
- L18 _public member_ `FString DatabaseName = "";` — `UE_DEPRECATED(5.7, "Use GetNameSafe(SourceDatabase.Get()) instead")`
- L20 _public member_ `FString DatabasePath = "";` — `UE_DEPRECATED(5.7, "Use GetPathNameSafe(SourceDatabase.Get()) instead")`
- L22 _public member_ `TAlignedArray<float> QueryVector;`
- L23 _public member_ `TAlignedArray<float> PCAQueryVector;`

#### class `UE::PoseSearch::FDebuggerDatabaseRowData`  
`class FDebuggerDatabaseRowData : public TSharedFromThis<FDebuggerDatabaseRowData>`  
_L26-52_
- inherits: `TSharedFromThis<FDebuggerDatabaseRowData>`
- L29 _public function_ `explicit FDebuggerDatabaseRowData(TSharedRef<FDebuggerDatabaseSharedData> InSharedData) : SharedData(InSharedData)`
- L30 _public function_ `bool IsValid() const`
- L32 _public member_ `int32 PoseIdx = INDEX_NONE;`
- L33 _public member_ `EPoseCandidateFlags PoseCandidateFlags = EPoseCandidateFlags::None;`
- L34 _public member_ `FString AssetName = "";`
- L35 _public member_ `FString AssetPath = "";`
- L36 _public member_ `int32 DbAssetIdx = 0;`
- L37 _public member_ `int32 AnimFrame = 0;`
- L38 _public member_ `float AnimPercentage = 0.0f;`
- L39 _public member_ `float AssetTime = 0.0f;`
- L40 _public member_ `bool bMirrored = false;`
- L41 _public member_ `bool bLooping = false;`
- L42 _public member_ `FVector BlendParameters = FVector::Zero();`
- L43 _public member_ `FPoseSearchCost PoseCost;`
- L44 _public member_ `FLinearColor CostColor = FLinearColor::White;`
- L45 _public member_ `float PosePCACost = 0.f;`
- L46 _public member_ `FLinearColor PCACostColor = FLinearColor::White;`
- L47 _public member_ `TArray<float> CostBreakdowns;`
- L48 _public member_ `TArray<FLinearColor> CostBreakdownsColors;`
- L49 _public member_ `TArray<float> CostVector;`
- L51 _public member_ `TSharedRef<FDebuggerDatabaseSharedData> SharedData;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Private/PoseSearchDebuggerDatabaseView.h` (Private)


#### class `UE::PoseSearch::SDebuggerDatabaseView`  
`class SDebuggerDatabaseView : public SCompoundWidget`  
_L25-161_
- inherits: `SCompoundWidget`
- desc: Database panel view widget of the PoseSearch debugger
- L27 _private function_ `SLATE_BEGIN_ARGS(SDebuggerDatabaseView)`
- L28 _private prototype_ `SLATE_ARGUMENT(TWeakPtr<class SDebuggerView>, Parent) SLATE_EVENT(FOnPoseSelectionChanged, OnPoseSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L33 _private prototype_ `void Update(const FTraceMotionMatchingStateMessage& State);`
- L35 _private function_ `const TSharedPtr<SListView<TSharedRef<FDebuggerDatabaseRowData>>>& GetActiveRow() const`
- L36 _private function_ `const TSharedPtr<SListView<TSharedRef<FDebuggerDatabaseRowData>>>& GetContinuingPoseRow() const`
- L37 _private function_ `const TSharedPtr<SListView<TSharedRef<FDebuggerDatabaseRowData>>>& GetDatabaseRows() const`
- L38 _private prototype_ `const TSharedRef<FDebuggerDatabaseRowData>& GetPoseIdxDatabaseRow(int32 PoseIdx) const;`
- L41 _private typedef_ `using FColumnMap = TMap<FName, TSharedRef<DebuggerDatabaseColumns::IColumn>>;` — Used by database rows to acquire column-specific information
- L69 _private prototype_ `void AddColumn(TSharedRef<DebuggerDatabaseColumns::IColumn>&& Column);` — Adds a column to the existing list
- L72 _private function_ `const FColumnMap* GetColumnMap() const` — Retrieves current column map, used as an attribute by rows
- L75 _private prototype_ `void SortDatabaseRows();` — Sorts the database by the current sort predicate, updating the view order
- L77 _private prototype_ `void PopulateViewRows();`
- L80 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;` — Acquires sort predicate for the given column
- L83 _private prototype_ `float GetColumnWidth(const FName ColumnId) const;` — Gets active column width, used to align active and database view
- L87 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName & ColumnId, const EColumnSortMode::Type InSortMode);` — Updates the active sort predicate, setting the sorting order of all other columns to none (to be dependent on active column
- L90 _private prototype_ `void OnColumnWidthChanged(const float NewWidth, FName ColumnId) const;` — Aligns the active and database views
- L93 _private prototype_ `void OnFilterTextChanged(const FText& SearchText);` — Called when the text in the filter box is modified to update the filtering
- L96 _private prototype_ `void OnShowAllPosesCheckboxChanged(ECheckBoxState State);` — Called when the ShowAllPoses Checkbox is Toggled
- L99 _private prototype_ `void OnShowOnlyBestAssetPoseCheckboxChanged(ECheckBoxState State);` — Called when the ShowOnlyBestAssetPose Checkbox is Toggled
- L102 _private prototype_ `void OnHideInvalidPosesCheckboxChanged(ECheckBoxState State);` — Called when the HideInvalidPoses Checkbox is Toggled
- L105 _private prototype_ `void OnUseRegexCheckboxChanged(ECheckBoxState State);` — Called when the UseRegex Checkbox is Toggled
- L107 _private prototype_ `void OnViewSelectionChanged(TSharedPtr<FDebuggerDatabaseRowData> Row, FTable& Table);`
- L108 _private prototype_ `void OnActiveViewSelectionChanged(TSharedPtr<FDebuggerDatabaseRowData> Row, ESelectInfo::Type SelectInfo);`
- L109 _private prototype_ `void OnContinuingPoseViewSelectionChanged(TSharedPtr<FDebuggerDatabaseRowData> Row, ESelectInfo::Type SelectInfo);`
- L110 _private prototype_ `void OnFilteredDatabaseViewSelectionChanged(TSharedPtr<FDebuggerDatabaseRowData> Row, ESelectInfo::Type SelectInfo);`
- L112 _private prototype_ `void OnViewMouseButtonClick(const TSharedPtr<FDebuggerDatabaseRowData> Row, FTable& Table);`
- L113 _private prototype_ `void OnActiveViewMouseButtonClick(const TSharedRef<FDebuggerDatabaseRowData> Row);`
- L114 _private prototype_ `void OnContinuingPoseViewMouseButtonClick(const TSharedRef<FDebuggerDatabaseRowData> Row);`
- L115 _private prototype_ `void OnFilteredDatabaseViewMouseButtonClick(const TSharedRef<FDebuggerDatabaseRowData> Row);`
- L118 _private prototype_ `TSharedRef<ITableRow> HandleGenerateDatabaseRow(TSharedRef<FDebuggerDatabaseRowData> Item, const TSharedRef<STableViewBase>& OwnerTable) const;` — Generates a database row widget for the given data
- L121 _private prototype_ `TSharedRef<ITableRow> HandleGenerateActiveRow(TSharedRef<FDebuggerDatabaseRowData> Item, const TSharedRef<STableViewBase>& OwnerTable) const;` — Generates the active row widget for the given data
- L124 _private prototype_ `TSharedRef<ITableRow> HandleGenerateContinuingPoseRow(TSharedRef<FDebuggerDatabaseRowData> Item, const TSharedRef<STableViewBase>& OwnerTable) const;` — Generates the continuing pose row widget for the given data
- L126 _private member_ `TWeakPtr<SDebuggerView> ParentDebuggerViewPtr;`
- L128 _private member_ `FOnPoseSelectionChanged OnPoseSelectionChanged;`
- L131 _private member_ `FName SortColumn = "";` — Current column to sort by
- L134 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::Ascending;` — Current sorting mode
- L137 _private member_ `FColumnMap Columns;` — Column data container, used to emplace defined column structures of various types
- L139 _private member_ `TArray<FText> OldLabels;`
- L140 _private member_ `bool bHasPCACostColumn = false;`
- L141 _private member_ `bool bWasVerbose = false;`
- L144 _private member_ `FTable ActiveView;` — Active row at the top of the view
- L147 _private member_ `FTable ContinuingPoseView;` — Continuing pose row below Active row
- L150 _private member_ `TArray<TSharedRef<FDebuggerDatabaseRowData>> UnfilteredDatabaseRows;` — All database poses
- L151 _private member_ `TArray<TSharedRef<FDebuggerDatabaseRowData>> InvalidDatabaseRows;`
- L154 _private member_ `FTable FilteredDatabaseView;` — Database listing for filtered poses
- L157 _private member_ `TSharedPtr<SSearchBox> FilterBox;` — Search box widget
- L160 _private member_ `FText FilterText;` — Text used to filter DatabaseView

#### struct `UE::PoseSearch::SDebuggerDatabaseView::FTable`  
`struct FTable`  
_L45-66_
- L48 _public member_ `TSharedPtr<SHeaderRow> HeaderRow;` — Header row
- L51 _public member_ `TSharedPtr<SListView<TSharedRef<FDebuggerDatabaseRowData>>> ListView;` — Widget for displaying the list of row objects
- L54 _public member_ `TArray<TSharedRef<FDebuggerDatabaseRowData>> Rows;` — List of row objects
- L57 _public member_ `FTableRowStyle RowStyle;` — Background style for the list view
- L60 _public member_ `FSlateBrush RowBrush;` — Row color
- L63 _public member_ `TSharedPtr<SScrollBar> ScrollBar;` — Scroll bar for the data table
- L65 _public member_ `TArray<TSharedRef<FDebuggerDatabaseRowData>> PreviouslySelectedItems;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PoseSearch` (scope `UE`)
- L14 _prototype_ `UPoseSearchDatabase* ResolveDatabaseFromId(uint64 DatabaseId);` (scope `UE::PoseSearch`)
- L16 _namespace_ `namespace DebuggerDatabaseColumns` (scope `UE::PoseSearch`)
- L20 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnPoseSelectionChanged, const UPoseSearchDatabase*, int32, float) class SDebuggerDatabaseView : public SCompoundWidget { SLATE_BEGIN_ARGS(SDebuggerDatabaseView) {} SLATE_ARGUMENT(TWeakPtr<class SDebuggerView>, Parent) SLATE_EVENT(FOnPoseSelectionChanged, OnPoseSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs); void Update(const FTraceMotionMatchingStateMessage& State); const TSharedPtr<SListView<TSharedRef<FDebuggerDatabaseRowData>>>& GetActiveRow() const { return ActiveView.ListView; } const TSharedPtr<SListView<TSharedRef<FDebuggerDatabaseRowData>>>& GetContinuingPoseRow() const { return ContinuingPoseView.ListView; } const TSharedPtr<SListView<TSharedRef<FDebuggerDatabaseRowData>>>& GetDatabaseRows() const { return FilteredDatabaseView.ListView; } const TSharedRef<FDebuggerDatabaseRowData>& GetPoseIdxDatabaseRow(int32 PoseIdx) const; using FColumnMap = TMap<FName, TSharedRef<DebuggerDatabaseColumns::IColumn>>; private: struct FTable { TSharedPtr<SHeaderRow> HeaderRow; TSharedPtr<SListView<TSharedRef<FDebuggerDatabaseRowData>>> ListView; TArray<TSharedRef<FDebuggerDatabaseRowData>> Rows; FTableRowStyle RowStyle;` — Sets model selection data on row selection

### `Plugins/Animation/PoseSearch/Source/Editor/Private/PoseSearchDebuggerReflection.h` (Private)


#### class `UPoseSearchDebuggerReflection`  
`class UPoseSearchDebuggerReflection : public UObject`  
_L12-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Reflection UObject being observed in the details view panel of the debugger
- L18 _public member_ `EPoseSearchInterruptMode InterruptMode = EPoseSearchInterruptMode::DoNotInterrupt;` — `UPROPERTY(VisibleAnywhere, Category = "Motion Matching State")`
- L22 _public member_ `float ElapsedPoseSearchTime = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category="Motion Matching State", meta = (ForceUnits = "s"))` — Time since last PoseSearch
- L25 _public member_ `float AssetPlayerTime = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Motion Matching State", meta = (ForceUnits = "s"))`
- L28 _public member_ `float LastDeltaTime = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Motion Matching State", meta = (ForceUnits = "s"))`
- L31 _public member_ `float SimLinearVelocity;` — `UPROPERTY(VisibleAnywhere, Category = "Motion Matching State", meta = (ForceUnits = "cm/s"))`
- L34 _public member_ `float SimAngularVelocity;` — `UPROPERTY(VisibleAnywhere, Category = "Motion Matching State", meta = (ForceUnits = "deg/s"))`
- L37 _public member_ `float AnimLinearVelocity;` — `UPROPERTY(VisibleAnywhere, Category = "Motion Matching State", meta = (ForceUnits = "cm/s"))`
- L40 _public member_ `float AnimAngularVelocity;` — `UPROPERTY(VisibleAnywhere, Category = "Motion Matching State", meta = (ForceUnits = "deg/s"))`
- L43 _public member_ `float Playrate;` — `UPROPERTY(VisibleAnywhere, Category = "Motion Matching State", meta = (ForceUnits = "s"))`
- L46 _public member_ `float AnimLinearVelocityNoTimescale;` — `UPROPERTY(VisibleAnywhere, Category = "Motion Matching State", meta = (ForceUnits = "cm/s"))`
- L49 _public member_ `float AnimAngularVelocityNoTimescale;` — `UPROPERTY(VisibleAnywhere, Category = "Motion Matching State", meta = (ForceUnits = "deg/s"))`

### `Plugins/Animation/PoseSearch/Source/Editor/Private/PoseSearchDebuggerSettings.h` (Private)


#### class `UPoseSearchDebuggerConfig`  
`class UPoseSearchDebuggerConfig : public UObject`  
_L12-57_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings, MinimalAPI)`
- inherits: `UObject`
- desc: Settings that holds editor configurations. Not accessible in Project Settings.
- L18 _public prototype_ `UPoseSearchDebuggerConfig();`
- L20 _public prototype_ `static UPoseSearchDebuggerConfig& Get();`
- L26 _public member_ `bool bDrawQuery = false;` — `UPROPERTY(config)` — Used to draw the query used to get pose for this frame from Motion Matching algorithm
- L30 _public member_ `bool bDrawTrajectory = false;` — `UPROPERTY(config)` — Used to show the trajectory used for this frame to run Motion Matching against
- L34 _public member_ `bool bDrawHistory = false;` — `UPROPERTY(config)` — Used to show the traced pose search history value
- L38 _public member_ `bool bIsVerbose = false;` — `UPROPERTY(config)` — Bool used to break down channels and display a complete picture of the weights that determined the final pose from Motion Matching algorithm
- L44 _public member_ `bool bShowAllPoses = false;` — `UPROPERTY(config)` — Bool used to show all poses from display
- L48 _public member_ `bool bShowOnlyBestAssetPose = false;` — `UPROPERTY(config)` — Bool used to show only the best pose of every asset
- L52 _public member_ `bool bHideInvalidPoses = false;` — `UPROPERTY(config)` — Bool used to hide invalid poses from display
- L56 _public member_ `bool bUseRegex = false;` — `UPROPERTY(config)` — Bool used to use FilterText as regex filter

### `Plugins/Animation/PoseSearch/Source/Editor/Private/PoseSearchDebuggerView.h` (Private)


#### class `UE::PoseSearch::SDebuggerDetailsView`  
`class SDebuggerDetailsView : public SCompoundWidget`  
_L28-54_
- inherits: `SCompoundWidget`
- desc: Details panel view widget of the PoseSearch debugger
- L30 _private function_ `SLATE_BEGIN_ARGS(SDebuggerDetailsView)`
- L31 _private prototype_ `SLATE_ARGUMENT(TWeakPtr<class SDebuggerView>, Parent) SLATE_END_ARGS() SDebuggerDetailsView() = default;`
- L37 _private prototype_ `void Construct(const FArguments& InArgs);`
- L38 _private prototype_ `void Update(const FTraceMotionMatchingStateMessage& State) const;`
- L41 _private function_ `const TObjectPtr<UPoseSearchDebuggerReflection> GetReflection() const` — Get a const version of our reflection object
- L45 _private prototype_ `void UpdateReflection(const FTraceMotionMatchingStateMessage& State) const;` — Update our details view object with new state information
- L47 _private member_ `TWeakPtr<SDebuggerView> ParentDebuggerViewPtr;`
- L50 _private member_ `TSharedPtr<IDetailsView> Details;` — Details widget constructed for the MM node
- L53 _private member_ `TObjectPtr<UPoseSearchDebuggerReflection> Reflection;` — Last updated reflection data relative to MM state. This is not gonna be garbage collected because of AddToRoot during Construct

#### class `UE::PoseSearch::SDebuggerView`  
`class SDebuggerView : public IRewindDebuggerView`  
_L62-167_
- inherits: `IRewindDebuggerView`
- desc: Entire view of the PoseSearch debugger, containing all sub-widgets
- L65 _public function_ `SLATE_BEGIN_ARGS(SDebuggerView)`
- L66 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<FDebuggerViewModel>, ViewModel) SLATE_EVENT(FOnViewClosed, OnViewClosed) SLATE_END_ARGS() SDebuggerView() = default;`
- L73 _public prototype_ `void Construct(const FArguments& InArgs, uint64 InAnimInstanceId, int32 InWantedSearchId);`
- L74 _public prototype_ `virtual void SetTimeMarker(double InTimeMarker) override;`
- L75 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L76 _public prototype_ `virtual FName GetName() const override;`
- L77 _public prototype_ `virtual uint64 GetObjectId() const override;`
- L79 _public function_ `TSharedPtr<FDebuggerViewModel> GetViewModel() const`
- L80 _public prototype_ `TArray<TSharedRef<FDebuggerDatabaseRowData>> GetSelectedDatabaseRows() const;`
- L84 _private prototype_ `bool UpdateNodeSelection();` — Check if a node selection was made, true if a node is selected
- L87 _private prototype_ `void UpdateViews() const;` — Update the database and details views
- L90 _private prototype_ `int32 SelectView() const;` — Returns an int32 appropriate to the index of our widget selector
- L93 _private prototype_ `FReply OnUpdateSearchSelection(int32 InSelectedSearchId);` — Callback when a button in the selection view is clicked
- L95 _private prototype_ `void OnPoseSelectionChanged(const UPoseSearchDatabase* Database, int32 PoseIdx, float Time);`
- L98 _private prototype_ `TSharedRef<SWidget> GenerateNoDataMessageView();` — Generates the message view relaying that there is no data
- L101 _private prototype_ `TSharedRef<SHorizontalBox> GenerateReturnButtonView();` — Generates the return button to go back to the selection mode
- L104 _private prototype_ `TSharedRef<SWidget> GenerateNodeDebuggerView();` — Generates the entire node debugger widget, including database and details view
- L107 _private member_ `TAttribute<TSharedPtr<FDebuggerViewModel>> ViewModel;` — Pointer to the debugger instance / model for this view
- L110 _private member_ `FOnViewClosed OnViewClosed;` — Destroy the debugger instanced when closed
- L113 _private member_ `int32 WantedSearchId = InvalidSearchId;` — Active User selected SearchId
- L116 _private member_ `int32 SelectedSearchId = InvalidSearchId;` — Active SearchId being debugged
- L119 _private member_ `TSharedPtr<SDebuggerDatabaseView> DatabaseView;` — Database view of the motion matching node
- L122 _private member_ `TSharedPtr<SDebuggerDetailsView> DetailsView;` — Details panel for introspecting the motion matching node
- L125 _private member_ `TSharedPtr<SSplitter> NodeDebuggerView;` — Node debugger view hosts the above two views
- L128 _private member_ `TSharedPtr<SVerticalBox> SelectionView;` — Selection view before node is selected
- L131 _private member_ `TSharedPtr<SVerticalBox> SimulatingView;` — Gray box occluding the debugger view when simulating
- L141 _private member_ `} SwitcherViewType = StoppedMsg;`
- L144 _private member_ `TSharedPtr<SWidgetSwitcher> Switcher;` — Contains all the above, switches between them depending on context
- L147 _private member_ `TSharedPtr<SVerticalBox> DebuggerView;` — Contains the switcher, the entire debugger view
- L151 _private member_ `uint64 AnimInstanceId = 0;` — AnimInstance this view was created for
- L154 _private member_ `double TimeMarker = -1.0;` — Current position of the time marker
- L157 _private member_ `double PreviousTimeMarker = -1.0;` — Previous position of the time marker
- L160 _private member_ `bool bUpdated = false;` — Tracks if the current time has been updated yet (delayed)
- L163 _private member_ `int32 CurrentConsecutiveFrames = 0;` — Tracks number of consecutive frames, once it reaches threshold it will update the view
- L166 _private member_ `static constexpr int32 ConsecutiveFramesUpdateThreshold = 10;` — Once the frame count has reached this value, an update will trigger for the view

#### enum `UE::PoseSearch::SDebuggerView::ESwitcherViewType`  
`enum ESwitcherViewType : int32`  
_L134-141_
- desc: Used to switch between views in the switcher, int32 maps to index in the SWidgetSwitcher
- L136 _public enumerator_ `Selection = 0`
- L137 _public enumerator_ `Debugger = 1`
- L138 _public enumerator_ `StoppedMsg = 2`
- L139 _public enumerator_ `RecordingMsg = 3`
- L140 _public enumerator_ `NoDataMsg = 4`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace PoseSearch` (scope `UE`)
- L57 _delegate_ `DECLARE_DELEGATE_OneParam(FOnViewClosed, uint64 AnimInstanceId);` — Callback to relay closing of the view to destroy the debugger instance
- L57 _prototype_ `DECLARE_DELEGATE_OneParam(FOnViewClosed, uint64 AnimInstanceId);` (scope `UE::PoseSearch`) — Callback to relay closing of the view to destroy the debugger instance
- L169 _prototype_ `FText GenerateSearchName(const FTraceMotionMatchingStateMessage& MotionMatchingState, const IGameplayProvider* GameplayProvider);` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Editor/Private/PoseSearchDebuggerViewModel.h` (Private)


#### class `UE::PoseSearch::FDebuggerViewModel`  
`class FDebuggerViewModel : public TSharedFromThis<FDebuggerViewModel>`  
_L21-72_
- inherits: `TSharedFromThis<FDebuggerViewModel>`
- L24 _public prototype_ `explicit FDebuggerViewModel(uint64 InAnimInstanceId);`
- L25 _public prototype_ `virtual ~FDebuggerViewModel();`
- L28 _public prototype_ `const FTraceMotionMatchingStateMessage* GetMotionMatchingState() const;` — Used for view callbacks
- L29 _public function_ `const TMap<uint64, TWeakObjectPtr<AActor>>& GetDebugDrawActors() const`
- L30 _public function_ `const TArray<FTraceMotionMatchingStateMessage>& GetMotionMatchingStates() const`
- L32 _public prototype_ `int32 GetNodesNum() const;`
- L35 _public prototype_ `void OnUpdate();` — Update motion matching states for frame
- L38 _public prototype_ `void OnUpdateSearchSelection(int32 InSearchId);` — Updates active motion matching state based on node selection
- L40 _public prototype_ `void SetVerbose(bool bVerbose);`
- L41 _public prototype_ `bool IsVerbose() const;`
- L43 _public prototype_ `void SetDrawQuery(bool bInDrawQuery);`
- L44 _public prototype_ `bool GetDrawQuery() const;`
- L46 _public prototype_ `void SetDrawTrajectory(bool bInDrawTrajectory);`
- L47 _public prototype_ `bool GetDrawTrajectory() const;`
- L49 _public prototype_ `void SetDrawHistory(bool bInDrawHistory);`
- L50 _public prototype_ `bool GetDrawHistory() const;`
- L55 _private member_ `TArray<FTraceMotionMatchingStateMessage> MotionMatchingStates;` — List of all updated motion matching states per node
- L58 _private member_ `int32 ActiveMotionMatchingStateIdx = INDEX_NONE;` — Currently active motion matching state index based on node selection in the view
- L61 _private member_ `TAttribute<const IRewindDebugger*> RewindDebugger;` — Pointer to the active rewind debugger in the scene
- L65 _private member_ `uint64 AnimInstanceId = 0;` — Anim Instance associated with this debugger instance
- L68 _private member_ `TMap<uint64, TWeakObjectPtr<AActor>> DebugDrawActors;` — Actor object populated by the timeline mapped from the MotionMatchingStates.SkeletalMeshComponentIds. used as input for additional bone transforms to draw channels

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Private/PoseSearchMeshComponent.h` (Private)


#### class `UPoseSearchMeshComponent`  
`class UPoseSearchMeshComponent : public UPoseableMeshComponent`  
_L9-16_
- reflection: `UCLASS()`
- inherits: `UPoseableMeshComponent`
- L14 _public prototype_ `void Refresh();`
- L15 _public prototype_ `void Initialize(const FTransform& InComponentToWorld);`

### `Plugins/Animation/PoseSearch/Source/Editor/Private/Trace/PoseSearchTraceAnalyzer.h` (Private)


#### class `UE::PoseSearch::FTraceAnalyzer`  
`class FTraceAnalyzer : public Trace::IAnalyzer`  
_L21-41_
- inherits: `Trace::IAnalyzer`
- desc: Used to relay trace information to the pose search provider
- L24 _public prototype_ `FTraceAnalyzer(TraceServices::IAnalysisSession& InSession, FTraceProvider& InTraceProvider);`
- L27 _protected prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L28 _protected prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L39 _private member_ `TraceServices::IAnalysisSession& Session;`
- L40 _private member_ `FTraceProvider& TraceProvider;`

#### enum `UE::PoseSearch::FTraceAnalyzer::(anonymous)`  
``  
_L33-37_

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PoseSearch` (scope `UE`)
- L34 _enumerator_ `RouteId_MotionMatchingState` (scope `UE::PoseSearch::FTraceAnalyzer::__anon38f671a80103`)
- L35 _enumerator_ `RouteId_MotionMatchingState2` (scope `UE::PoseSearch::FTraceAnalyzer::__anon38f671a80103`)
- L36 _enumerator_ `RouteId_MotionMatchingState3` (scope `UE::PoseSearch::FTraceAnalyzer::__anon38f671a80103`)

### `Plugins/Animation/PoseSearch/Source/Editor/Private/Trace/PoseSearchTraceModule.h` (Private)


#### class `UE::PoseSearch::FTraceModule`  
`class FTraceModule : public TraceServices::IModule`  
_L14-28_
- inherits: `TraceServices::IModule`
- desc: Module used for loading our PoseSearch tracing systems
- L17 _public prototype_ `FTraceModule() = default;`
- L18 _public prototype_ `virtual ~FTraceModule() = default;`
- L20 _public member_ `const static FName ModuleName;`
- L23 _protected prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;`
- L24 _protected prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& InSession) override;`
- L25 _protected prototype_ `virtual void GetLoggers(TArray<const TCHAR*>& OutLoggers) override;`
- L26 _protected prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L27 _protected function_ `virtual const TCHAR* GetCommandLineArgument() override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Private/Trace/PoseSearchTraceProvider.h` (Private)


#### class `UE::PoseSearch::FTraceProvider`  
`class FTraceProvider : public TraceServices::IProvider, public TraceServices::IEditableProvider`  
_L18-185_
- inherits: `TraceServices::IProvider,TraceServices::IEditableProvider`
- desc: Provider to the widgets for pose search functionality, largely mimicking FAnimationProvider
- L21 _public prototype_ `explicit FTraceProvider(TraceServices::IAnalysisSession& InSession);`
- L24 _public function_ `virtual void BeginRead() const override`
- L28 _public function_ `virtual void EndRead() const override`
- L32 _public function_ `virtual void ReadAccessCheck() const override`
- L38 _public function_ `virtual void BeginEdit() const override`
- L42 _public function_ `virtual void EndEdit() const override`
- L46 _public function_ `virtual void EditAccessCheck() const override`
- L51 _public typedef_ `using FMotionMatchingStateTimeline = TraceServices::ITimeline<FTraceMotionMatchingStateMessage>;`
- L54 _public prototype_ `bool ReadMotionMatchingStateTimeline(uint64 InAnimInstanceId, int32 InSearchId, TFunctionRef<void(const FMotionMatchingStateTimeline&)> Callback) const;` — Read the node-relative timeline info of the AnimInstance and provide it via callback
- L57 _public prototype_ `bool EnumerateMotionMatchingStateTimelines(uint64 InAnimInstanceId, TFunctionRef<void(const FMotionMatchingStateTimeline&)> Callback) const;` — Enumerate all node timelines on the AnimInstance and provide them via callback
- L60 _public prototype_ `void AppendMotionMatchingState(const FTraceMotionMatchingStateMessage& InMessage, double InTime);` — Append to the timeline on our object
- L63 _public member_ `static const FName ProviderName;`
- L180 _private member_ `} MotionMatchingStateTimelineStorage;`
- L183 _private member_ `TraceServices::IAnalysisSession& Session;`
- L184 _private member_ `mutable TraceServices::FProviderLock Lock;`

#### struct `UE::PoseSearch::FTraceProvider::TTimelineStorage`  
`template <class MessageType, class TimelineType = TraceServices::TPointTimeline<MessageType>> struct TTimelineStorage`  
_L71-175_
- desc: Convenience struct for creating timelines per message type. We store an array of timelines for every possible AnimInstance Id that gets appended.
- L74 _public typedef_ `using FSearchIdToTimelineMap = TMap<int32, uint32>;` — Map the timelines as AnimInstanceId -> SearchId -> Timeline
- L75 _public typedef_ `using FAnimInstanceToTimelineMap = TMap<uint64, FSearchIdToTimelineMap>;`
- L78 _public function_ `TSharedRef<TimelineType> GetTimeline(TraceServices::IAnalysisSession& InSession, uint64 InAnimInstanceId, int32 InSearchId)` — Retrieves the timeline for internal use, creating it if it does not exist
- L106 _public function_ `bool ReadSearchTimeline(const FSearchIdToTimelineMap* SearchIdToTimelineMap, int32 InSearchId, TFunctionRef<void(const TraceServices::ITimeline<MessageType>&)> Callback) const`
- L119 _public function_ `bool ReadTimeline(uint64 InAnimInstanceId, int32 InSearchId, TFunctionRef<void(const TraceServices::ITimeline<MessageType>&)> Callback) const` — Retrieve a timeline from an anim instance + node and execute the callback
- L131 _public function_ `bool EnumerateSearchTimelines(uint64 InAnimInstanceId, TFunctionRef<void(const TraceServices::ITimeline<MessageType>&)> Callback) const` — Enumerates timelines of all nodes given an AnimInstance
- L152 _public function_ `TSet<int32> GetSearchIds(uint64 InAnimInstanceId) const`
- L171 _public member_ `FAnimInstanceToTimelineMap AnimInstanceIdToTimelines;` — Maps AnimInstanceIds to a map of SearchIds to timelines. AnimInstanceId -> SearchId -> Timeline
- L174 _public member_ `TArray<TSharedRef<TimelineType>> Timelines;` — Timelines per node

#### struct `UE::PoseSearch::FTraceProvider::FMotionMatchingStateTimelineStorage`  
`struct FMotionMatchingStateTimelineStorage : TTimelineStorage<FTraceMotionMatchingStateMessage>`  
_L178-180_
- inherits: `TTimelineStorage<FTraceMotionMatchingStateMessage>`
- desc: Storage for each message type

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PoseSearch` (scope `UE`)
- L13 _externvar_ `extern thread_local TraceServices::FProviderLock::FThreadLocalState GPoseSearchProviderLockState;` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Editor/Public/AnimGraphNode_MotionMatching.h` (Public)


#### class `UAnimGraphNode_MotionMatching`  
`class UAnimGraphNode_MotionMatching : public UAnimGraphNode_BlendStack_Base`  
_L14-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_BlendStack_Base`
- L19 _private member_ `FAnimNode_MotionMatching Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L22 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UAnimGraphNode_Base interface
- L23 _private prototype_ `virtual FText GetTooltipText() const override;`
- L24 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L25 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L26 _private prototype_ `virtual UScriptStruct* GetTimePropertyStruct() const override;`
- L27 _private prototype_ `virtual void OnProcessDuringCompilation(IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData) override;`
- L28 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L29 _private prototype_ `virtual void AddSearchMetaDataInfo(TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L30 _private prototype_ `virtual void GetBoundFunctionsInfo(TArray<TPair<FName, FName>>& InOutBindingsInfo) override;`
- L31 _private prototype_ `virtual bool ReferencesFunction(const FName& InFunctionName, const UStruct* InScope) const override;`
- L32 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L33 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L37 _private function_ `virtual FAnimNode_BlendStack_Standalone* GetBlendStackNode() const override` — UAnimGraphNode_BlendStack_Base interface
- L41 _private member_ `FMemberReference OnMotionMatchingStateUpdatedFunction;` — `UPROPERTY(EditAnywhere, Category = "Functions|Motion Matching", meta=(FunctionReference, AllowFunctionLibraries, PrototypeFunction="/Script/AnimGraphRuntime.AnimExecutionContextLibrary.Prototype_ThreadSafeAnimUpdateCall", DefaultBindingName="OnStateExit"), DisplayName="On Motion Matching State Updated")`

### `Plugins/Animation/PoseSearch/Source/Editor/Public/AnimGraphNode_PoseSearchHistoryCollector.h` (Public)


#### class `UAnimGraphNode_PoseSearchHistoryCollector_Base`  
`class UAnimGraphNode_PoseSearchHistoryCollector_Base : public UAnimGraphNode_Base`  
_L12-26_
- reflection: `UCLASS(Abstract, BlueprintType)`
- inherits: `UAnimGraphNode_Base`
- L15 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L16 _private prototype_ `virtual FText GetTooltipText() const override;`
- L17 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L22 _public prototype_ `virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;`
- L23 _public prototype_ `virtual void PostReconstructNode() override;`
- L24 _public prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`

#### class `UAnimGraphNode_PoseSearchHistoryCollector`  
`class UAnimGraphNode_PoseSearchHistoryCollector : public UAnimGraphNode_PoseSearchHistoryCollector_Base`  
_L29-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_PoseSearchHistoryCollector_Base`
- L34 _private member_ `FAnimNode_PoseSearchHistoryCollector Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L36 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`

#### class `UAnimGraphNode_PoseSearchComponentSpaceHistoryCollector`  
`class UAnimGraphNode_PoseSearchComponentSpaceHistoryCollector : public UAnimGraphNode_PoseSearchHistoryCollector_Base`  
_L40-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_PoseSearchHistoryCollector_Base`
- L45 _private member_ `FAnimNode_PoseSearchComponentSpaceHistoryCollector Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L47 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L48 _private prototype_ `virtual void CreateOutputPins() override;`

### `Plugins/Animation/PoseSearch/Source/Editor/Public/IMultiAnimAssetEditor.h` (Public)


#### class `IMultiAnimAssetEditor`  
`class IMultiAnimAssetEditor : public FAssetEditorToolkit`  
_L9-13_
- inherits: `FAssetEditorToolkit`
- L12 _public prototype_ `virtual void SetPreviewProperties(float AnimAssetTime, const FVector& AnimAssetBlendParameters, bool bAnimAssetPlaying) = 0;`

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchColumnEditor.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PoseSearchEditor` (scope `UE`)
- L9 _prototype_ `void RegisterPoseSearchChooserWidgets();` (scope `UE::PoseSearchEditor`)

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchCustomization.h` (Public)


#### class `FPoseSearchColumnRowReflectionCustomization`  
`class FPoseSearchColumnRowReflectionCustomization : public IPropertyTypeCustomization`  
_L19-29_
- inherits: `IPropertyTypeCustomization`
- desc: Customises FPoseSearchColumnRowReflection so the Database picker only offers UPoseSearchDatabase instances embedded in the owning chooser (NestedObjects), rather than the full project asset browser.
- L22 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L27 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L28 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### class `FPoseSearchDatabaseAnimationAssetCustomization`  
`class FPoseSearchDatabaseAnimationAssetCustomization : public IPropertyTypeCustomization`  
_L31-42_
- inherits: `IPropertyTypeCustomization`
- L34 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L40 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L41 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchDatabaseAssetListItem.h` (Public)


#### class `UE::PoseSearch::SDatabaseAssetListItem`  
`class SDatabaseAssetListItem : public STableRow<TSharedPtr<FDatabaseAssetTreeNode>>`  
_L17-67_
- inherits: `STableRow<TSharedPtr<FDatabaseAssetTreeNode>>`
- L20 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FDatabaseViewModel>& InEditorViewModel, const TSharedRef<STableViewBase>& OwnerTable, TSharedRef<FDatabaseAssetTreeNode> InAssetTreeNode, TSharedRef<FUICommandList> InCommandList, TSharedPtr<SDatabaseAssetTree> InHierarchy);`
- L29 _protected prototype_ `FText GetName() const;`
- L30 _protected prototype_ `TSharedRef<SWidget> GenerateItemWidget();`
- L32 _protected prototype_ `const FSlateBrush* GetGroupBackgroundImage() const;`
- L33 _protected prototype_ `void ConstructGroupItem(const TSharedRef<STableViewBase>& OwnerTable);`
- L34 _protected prototype_ `void ConstructAssetItem(const TSharedRef<STableViewBase>& OwnerTable);`
- L36 _protected prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L38 _protected prototype_ `EVisibility GetSelectedActorIconVisibility() const;`
- L40 _protected prototype_ `void OnAssetPickerObjectChanged(const FAssetData& AssetData);`
- L41 _protected prototype_ `FString GetAssetPickerObjectPath() const;`
- L42 _protected prototype_ `bool GetAssetPickerIsEnabled() const;`
- L43 _protected prototype_ `EVisibility GetAssetPickerCustomContentSlotVisibility() const;`
- L44 _protected prototype_ `FText GetAssetPickerText() const;`
- L45 _protected prototype_ `FSlateColor GetAssetPickerCustomContentSlotTextColor() const;`
- L47 _protected prototype_ `FSlateColor GetLoopingColorAndOpacity() const;`
- L48 _protected prototype_ `FText GetLoopingToolTip() const;`
- L50 _protected prototype_ `FSlateColor GetRootMotionColorAndOpacity() const;`
- L51 _protected prototype_ `FText GetRootMotionOptionToolTip() const;`
- L53 _protected prototype_ `FText GetDisableReselectionToolTip() const;`
- L54 _protected prototype_ `ECheckBoxState GetDisableReselectionChecked() const;`
- L55 _protected prototype_ `void OnDisableReselectionChanged(ECheckBoxState NewCheckboxState);`
- L57 _protected prototype_ `FText GetAssetEnabledToolTip() const;`
- L58 _protected prototype_ `ECheckBoxState GetAssetEnabledChecked() const;`
- L59 _protected prototype_ `void OnAssetIsEnabledChanged(ECheckBoxState NewCheckboxState);`
- L61 _protected member_ `TWeakPtr<FDatabaseAssetTreeNode> WeakAssetTreeNode;`
- L62 _protected member_ `TWeakPtr<FDatabaseViewModel> EditorViewModel;`
- L63 _protected member_ `TWeakPtr<SDatabaseAssetTree> SkeletonView;`
- L65 _protected member_ `FColor AssetTypeColor;`
- L66 _protected member_ `TSharedPtr<SOverlay> AssetThumbnailOverlay;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchDatabaseAssetTree.h` (Public)


#### class `UE::PoseSearch::SDatabaseAssetTree`  
`class SDatabaseAssetTree : public SCompoundWidget, public FSelfRegisteringEditorUndoClient`  
_L17-131_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- L20 _public function_ `SLATE_BEGIN_ARGS(SDatabaseAssetTree)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FDatabaseViewModel> InEditorViewModel);`
- L26 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;` — SWidget interface
- L27 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L28 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L29 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L30 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L34 _public prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;`
- L35 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L36 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L39 _public prototype_ `void RefreshTreeView(bool bIsInitialSetup = false, bool bRecoverSelection = false);`
- L40 _public prototype_ `void FinalizeTreeChanges(bool bRecoverSelection = false, bool bRefreshView = true);`
- L42 _public prototype_ `void SetSelectedItem(int32 SourceAssetIdx, bool bClearSelection);`
- L43 _public function_ `TArray<TSharedPtr<FDatabaseAssetTreeNode>> GetSelectedNodes() const`
- L46 _protected member_ `TWeakPtr<FDatabaseViewModel> EditorViewModel;`
- L49 _protected member_ `TSharedPtr<FUICommandList> CommandList;` — command list we bind to
- L52 _protected member_ `TSharedPtr<STreeView<TSharedPtr<FDatabaseAssetTreeNode>>> TreeView;` — tree view widget
- L53 _protected member_ `TSharedPtr<SWidget> TreeViewDragAndDropSuggestion;`
- L54 _protected member_ `TArray<TSharedPtr<FDatabaseAssetTreeNode>> RootNodes;`
- L56 _protected prototype_ `TSharedRef<ITableRow> MakeTableRowWidget( TSharedPtr<FDatabaseAssetTreeNode> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L59 _protected prototype_ `void HandleGetChildrenForTree( TSharedPtr<FDatabaseAssetTreeNode> InNode, TArray<TSharedPtr<FDatabaseAssetTreeNode>>& OutChildren);`
- L63 _protected prototype_ `TOptional<EItemDropZone> OnCanAcceptDrop( const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FDatabaseAssetTreeNode> TargetItem);`
- L68 _protected prototype_ `FReply OnAcceptDrop( const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FDatabaseAssetTreeNode> TargetItem);`
- L73 _protected prototype_ `TSharedPtr<SWidget> CreateContextMenu();`
- L75 _protected prototype_ `TSharedRef<SWidget> GenerateFilterBoxWidget();`
- L77 _protected prototype_ `FText GetFilterText() const;`
- L78 _protected prototype_ `void OnAssetFilterTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);`
- L80 _protected function_ `void SetAssetFilterString(FString InString)`
- L81 _protected function_ `FString GetAssetFilterString() const`
- L84 _protected member_ `FString AssetFilterString;` — String Filter For Database View
- L86 _protected prototype_ `void OnAddAsset(bool bFinalizeChanges = true);`
- L87 _protected prototype_ `void OnDeleteAsset(TSharedPtr<FDatabaseAssetTreeNode> Node, bool bFinalizeChanges = true);`
- L88 _protected prototype_ `void CreateCommandList();`
- L91 _protected prototype_ `bool CanDeleteNodes() const;` — Removes existing selected component nodes from the tree
- L92 _protected prototype_ `void OnDeleteNodes();`
- L95 _protected prototype_ `void OnCopySelectedNodesToClipboard() const;` — Copy selected nodes to clipboard
- L96 _protected prototype_ `bool CanCopyToClipboard() const;`
- L99 _protected prototype_ `void OnPasteNodesFromClipboard();` — Paste nodes from clipboard. Adds or overwrites curves (if identifiers collide)
- L100 _protected prototype_ `bool CanPasteFromClipboard();`
- L103 _protected prototype_ `void OnCutSelectedNodesToClipboard();` — Cut selected nodes to clipboard
- L104 _protected prototype_ `bool CanCutToClipboard() const;`
- L106 _protected prototype_ `void EnableSelectedNodes(bool bIsEnabled);`
- L107 _protected function_ `void OnEnableNodes()`
- L108 _protected function_ `void OnDisableNodes()`
- L109 _protected prototype_ `void OnSetMirrorOptionForSelectedNodes(EPoseSearchMirrorOption InMirrorOption);`
- L110 _protected prototype_ `void OnSetPoseReselectionForSelectedNodes(bool bIsEnabled);`
- L112 _protected prototype_ `void OnConvertToBranchIn();`
- L118 _protected prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams( FOnSelectionChangedMulticaster, const TArrayView<TSharedPtr<FDatabaseAssetTreeNode>>& , ESelectInfo::Type );` — Called when an item is selected/deselected
- L123 _protected member_ `FOnSelectionChangedMulticaster OnSelectionChanged;`
- L126 _public typedef_ `typedef FOnSelectionChangedMulticaster::FDelegate FOnSelectionChanged;`
- L127 _public prototype_ `void RegisterOnSelectionChanged(const FOnSelectionChanged& Delegate);`
- L128 _public prototype_ `void UnregisterOnSelectionChanged(FDelegateUserObject Unregister);`
- L130 _public prototype_ `void RecoverSelection(const TArray<TSharedPtr<FDatabaseAssetTreeNode>>& PreviouslySelectedNodes);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PoseSearch` (scope `UE`)
- L118 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams( FOnSelectionChangedMulticaster, const TArrayView<TSharedPtr<FDatabaseAssetTreeNode>>& , ESelectInfo::Type );` — Called when an item is selected/deselected

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchDatabaseAssetTreeNode.h` (Public)


#### class `UE::PoseSearch::FDatabaseAssetTreeNode`  
`class FDatabaseAssetTreeNode : public TSharedFromThis<FDatabaseAssetTreeNode>`  
_L17-31_
- inherits: `TSharedFromThis<FDatabaseAssetTreeNode>`
- L21 _public prototype_ `FDatabaseAssetTreeNode(int32 InSourceAssetIdx, const TSharedRef<FDatabaseViewModel>& InEditorViewModel);`
- L22 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FDatabaseAssetTreeNode> InDatabaseAssetNode, TSharedRef<FUICommandList> InCommandList, TSharedPtr<SDatabaseAssetTree> InHierarchy);`
- L23 _public prototype_ `bool IsRootMotionEnabled() const;`
- L24 _public prototype_ `bool IsLooping() const;`
- L25 _public prototype_ `EPoseSearchMirrorOption GetMirrorOption() const;`
- L27 _public member_ `int32 SourceAssetIdx = INDEX_NONE;`
- L28 _public member_ `TSharedPtr<FDatabaseAssetTreeNode> Parent;`
- L29 _public member_ `TArray<TSharedPtr<FDatabaseAssetTreeNode>> Children;`
- L30 _public member_ `TWeakPtr<FDatabaseViewModel> EditorViewModel;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchDatabaseDataDetails.h` (Public)


#### class `UE::PoseSearch::SDatabaseDataDetails`  
`class SDatabaseDataDetails : public SCompoundWidget`  
_L17-35_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS( SDatabaseDataDetails )`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, TSharedRef<FDatabaseViewModel> InEditorViewModel);`
- L24 _public prototype_ `void Reconstruct();`
- L27 _private prototype_ `static void RebuildChannelItemsTreeRecursively(TArray<FChannelItemPtr>& ChannelItems, TConstArrayView<TObjectPtr<UPoseSearchFeatureChannel>> Channels, const FSearchIndex& SearchIndex);`
- L28 _private prototype_ `static void RebuildChannelItemsStats(TArray<FChannelItemPtr>& ChannelItems);`
- L29 _private prototype_ `static void TrackExpandedItems(const TArray<FChannelItemPtr>& ChannelItems, TMap<const FString, bool>& ExpandedItems);`
- L30 _private prototype_ `static void SetExpandedItems(TArray<FChannelItemPtr>& ChannelItems, const TMap<const FString, bool>& ExpandedItems, SChannelItemsTreeView* ChannelItemsTreeView);`
- L32 _private member_ `TSharedPtr<SChannelItemsTreeView> ChannelItemsTreeView;`
- L33 _private member_ `TArray<FChannelItemPtr> ChannelItems;`
- L34 _private member_ `TWeakPtr<FDatabaseViewModel> EditorViewModel;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PoseSearch` (scope `UE`)
- L13 _typedef_ `typedef TSharedPtr<class FChannelItem> FChannelItemPtr;` (scope `UE::PoseSearch`)
- L14 _typedef_ `typedef STreeView<FChannelItemPtr> SChannelItemsTreeView;` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchDatabaseEdMode.h` (Public)


#### class `UE::PoseSearch::FDatabaseEdMode`  
`class FDatabaseEdMode : public FEdMode`  
_L13-50_
- inherits: `FEdMode`
- L17 _public member_ `const static FEditorModeID EdModeId;`
- L19 _public prototype_ `FDatabaseEdMode();`
- L20 _public prototype_ `virtual ~FDatabaseEdMode();`
- L22 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L23 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L24 _public prototype_ `virtual bool HandleClick( FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;`
- L28 _public prototype_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L29 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L30 _public prototype_ `virtual bool InputDelta( FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;`
- L36 _public prototype_ `virtual bool InputKey( FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;`
- L41 _public prototype_ `virtual bool AllowWidgetMove() override;`
- L42 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L43 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L44 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L45 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L46 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L49 _private member_ `FDatabaseViewModel* ViewModel = nullptr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchDatabaseEditor.h` (Public)


#### class `UE::PoseSearch::FDatabaseEditor`  
`class FDatabaseEditor : public FAssetEditorToolkit, public FNotifyHook`  
_L24-103_
- inherits: `FAssetEditorToolkit,FNotifyHook`
- L28 _public prototype_ `void InitAssetEditor( const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UPoseSearchDatabase* DatabaseAsset);`
- L32 _public prototype_ `virtual ~FDatabaseEditor();`
- L34 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L35 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L36 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L37 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L38 _public prototype_ `virtual FText GetToolkitName() const override;`
- L39 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L40 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L42 _public prototype_ `const UPoseSearchDatabase* GetPoseSearchDatabase() const;`
- L43 _public prototype_ `UPoseSearchDatabase* GetPoseSearchDatabase();`
- L44 _public function_ `FDatabaseViewModel* GetViewModel() const`
- L45 _public function_ `TSharedPtr<FDatabaseViewModel> GetViewModelSharedPtr() const`
- L47 _public prototype_ `void SetSelectedPoseIdx(int32 PoseIdx, bool bDrawQuery, TConstArrayView<float> InQueryVector);`
- L48 _public prototype_ `void SetDrawQueryVector(bool bValue);`
- L50 _public prototype_ `void PreviewBackwardEnd();`
- L51 _public prototype_ `void PreviewBackwardStep();`
- L52 _public prototype_ `void PreviewBackward();`
- L53 _public prototype_ `void PreviewPause();`
- L54 _public prototype_ `void PreviewForward();`
- L55 _public prototype_ `void PreviewForwardStep();`
- L56 _public prototype_ `void PreviewForwardEnd();`
- L60 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);`
- L61 _private prototype_ `TSharedRef<SDockTab> SpawnTab_AssetDetails(const FSpawnTabArgs& Args);`
- L62 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSettings(const FSpawnTabArgs& Args);`
- L63 _private prototype_ `TSharedRef<SDockTab> SpawnTab_AssetTreeView(const FSpawnTabArgs& Args);`
- L64 _private prototype_ `TSharedRef<SDockTab> SpawnTab_SelectionDetails(const FSpawnTabArgs& Args);`
- L65 _private prototype_ `TSharedRef<SDockTab> SpawnTab_StatisticsOverview(const FSpawnTabArgs& Args) const;`
- L66 _private prototype_ `TSharedRef<SDockTab> SpawnTab_DataDetails(const FSpawnTabArgs& Args) const;`
- L67 _private prototype_ `TSharedRef<SDockTab> SpawnTab_AssetBrowser(const FSpawnTabArgs& Args) const;`
- L69 _private prototype_ `void OnFinishedChangingSelectionProperties(const FPropertyChangedEvent& PropertyChangedEvent);`
- L70 _private prototype_ `void OnAssetTreeSelectionChanged( const TArrayView<TSharedPtr<FDatabaseAssetTreeNode>>& SelectedItems, ESelectInfo::Type SelectionType);`
- L74 _private prototype_ `void RefreshStatisticsWidgetInformation();`
- L75 _private prototype_ `void RefreshEditor();`
- L82 _private prototype_ `FSelectionWidget& GetInitializedSelectionWidget();`
- L84 _private member_ `TSharedPtr<SDatabasePreview> PreviewWidget;`
- L86 _private member_ `TSharedPtr<SDatabaseAssetTree> AssetTreeWidget;`
- L88 _private member_ `TSharedPtr<SDatabaseDataDetails> DataDetails;`
- L90 _private member_ `TSharedPtr<SPoseSearchDatabaseAssetBrowser> AssetBrowserWidget;`
- L92 _private member_ `TSharedPtr<IDetailsView> EditingAssetWidget;`
- L94 _private member_ `TSharedPtr<SVerticalBox> DetailsContainer;`
- L95 _private member_ `FSelectionWidget SelectionWidget;`
- L97 _private member_ `TSharedPtr<IDetailsView> StatisticsOverviewWidget;`
- L98 _private member_ `UPoseSearchDatabaseStatistics* CachedStatistics = nullptr;`
- L100 _private member_ `TSharedPtr<FDatabasePreviewScene> PreviewScene;`
- L102 _private member_ `TSharedPtr<FDatabaseViewModel> ViewModel;`

#### struct `UE::PoseSearch::FDatabaseEditor::FSelectionWidget`  
`struct FSelectionWidget`  
_L77-81_
- L79 _public member_ `TSharedPtr<IDetailsView> DetailView;`
- L80 _public member_ `TArray<TWeakObjectPtr<UObject>> SelectedReflections;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchDatabaseEditorCommands.h` (Public)


#### class `UE::PoseSearch::FDatabaseEditorCommands`  
`class FDatabaseEditorCommands : public TCommands<FDatabaseEditorCommands>`  
_L12-33_
- inherits: `TCommands<FDatabaseEditorCommands>`
- L15 _public function_ `FDatabaseEditorCommands() : TCommands<FDatabaseEditorCommands>( TEXT("PoseSearchDatabaseEditor"), NSLOCTEXT("Contexts", "PoseSearchDatabase", "Pose Search Database"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L24 _public prototype_ `virtual void RegisterCommands() override;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> ShowDisplayRootMotionSpeed;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> ShowQuantizeAnimationToPoseData;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ShowBones;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> ShowDisplayBlockTransition;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> ShowDisplayEventData;` — Experimental, this feature might be removed without warning, not for production use

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchDatabaseEditorReflection.h` (Public)


#### class `UPoseSearchDatabaseReflectionBase`  
`class UPoseSearchDatabaseReflectionBase : public UObject`  
_L18-24_
- reflection: `UCLASS()`
- inherits: `UObject`
- L23 _public member_ `int32 SourceAssetIdx = INDEX_NONE;`

#### class `UPoseSearchDatabaseAnimationAssetReflection`  
`class UPoseSearchDatabaseAnimationAssetReflection : public UPoseSearchDatabaseReflectionBase`  
_L27-34_
- reflection: `UCLASS()`
- inherits: `UPoseSearchDatabaseReflectionBase`
- L33 _public member_ `FPoseSearchDatabaseAnimationAsset DatabaseAnimationAsset;` — `UPROPERTY(Transient, EditAnywhere, Category = "Selected Animation Asset")`

#### struct `FPoseSearchDatabaseMemoryStats`  
`struct FPoseSearchDatabaseMemoryStats`  
_L37-60_
- reflection: `USTRUCT()`
- L42 _public member_ `FText EstimatedDatabaseSize;` — `UPROPERTY(VisibleAnywhere, Category = "Stats")`
- L45 _public member_ `FText ValuesSize;` — `UPROPERTY(VisibleAnywhere, Category = "Stats")`
- L48 _public member_ `FText PCAValuesSize;` — `UPROPERTY(VisibleAnywhere, Category = "Stats")`
- L51 _public member_ `FText KDTreeSize;` — `UPROPERTY(VisibleAnywhere, Category = "Stats")`
- L54 _public member_ `FText PoseMetadataSize;` — `UPROPERTY(VisibleAnywhere, Category = "Stats")`
- L57 _public member_ `FText AssetsSize;` — `UPROPERTY(VisibleAnywhere, Category = "Stats")`
- L59 _public prototype_ `void Initialize(const UPoseSearchDatabase* PoseSearchDatabase);`

#### class `UPoseSearchDatabaseStatistics`  
`class UPoseSearchDatabaseStatistics : public UObject`  
_L63-162_
- reflection: `UCLASS()`
- inherits: `UObject`
- L71 _public member_ `uint32 AnimationSequences;` — `UPROPERTY(VisibleAnywhere, Category = "General Information")` — Number of Animation Sequences in the database.
- L75 _public member_ `uint32 TotalAnimationPosesInFrames;` — `UPROPERTY(VisibleAnywhere, Category = "General Information")` — Number of total animation poses in frames in the database.
- L79 _public member_ `FText TotalAnimationPosesInTime;` — `UPROPERTY(VisibleAnywhere, Category = "General Information")` — Number of total animation poses in time in the database.
- L83 _public member_ `uint32 SearchableFrames;` — `UPROPERTY(VisibleAnywhere, Category = "General Information")` — Amount of animation frames that are searchable in the database (this will exclude frames that have been removed using Sampling Range).
- L87 _public member_ `FText SearchableTime;` — `UPROPERTY(VisibleAnywhere, Category = "General Information")` — Amount of animation in time that are searchable in the database (this will exclude time that have been removed using Sampling Range).
- L91 _public member_ `uint32 PrunedFrames;` — `UPROPERTY(VisibleAnywhere, Category = "General Information")` — Amount of animation frames (database poses) of pose features data that has been pruned out because close to each other more than PosePruningSimilarityThreshold
- L95 _public member_ `uint32 PrunedPCAFrames;` — `UPROPERTY(VisibleAnywhere, Category = "General Information")` — Amount of animation frames projected in PCA space (database poses) of pose PCA feature data (used to construct the kdtree) that has been pruned out because close to each other more than PCAValuesPruningSimilarityThreshold
- L99 _public member_ `uint32 SchemaCardinality;` — `UPROPERTY(VisibleAnywhere, Category = "General Information")` — Cardinality for the database schema (how many floats per pose to store the pose features data)
- L103 _public member_ `FText AverageSpeed;` — `UPROPERTY(VisibleAnywhere, Category = "Kinematic Information")` — Average speed of the characters trajectory across all animations in the database.
- L107 _public member_ `FText MaxSpeed;` — `UPROPERTY(VisibleAnywhere, Category = "Kinematic Information")` — Highest speed of the characters trajectory across all animations in the database.
- L111 _public member_ `FText AverageAcceleration;` — `UPROPERTY(VisibleAnywhere, Category = "Kinematic Information")` — The average acceleration of the characters trajectory across all the animations in the database.
- L115 _public member_ `FText MaxAcceleration;` — `UPROPERTY(VisibleAnywhere, Category = "Kinematic Information")` — The max acceleration of the characters trajectory across all the animations in the database.
- L120 _public member_ `float ExplainedVariance;` — `UPROPERTY(VisibleAnywhere, Category = "Principal Component Analysis Information", meta = (Units = "Percent"))` — When Pose Search Mode is set to PCAKDTree this value represents how well the variance of the dataset is explained within the chosen Number Of Principal Components: the higher, the better the quality (statistically more significant result) out of the kdtree search.
- L124 _public member_ `FText EstimatedDatabaseSize;` — `UPROPERTY(VisibleAnywhere, Category = "Memory Information")` — aggregated total memory used by this database (including animation assets).
- L128 _public member_ `FText ValuesSize;` — `UPROPERTY(VisibleAnywhere, Category = "Memory Information")` — partial memory size used to store the pose feature vectors.
- L132 _public member_ `FText PCAValuesSize;` — `UPROPERTY(VisibleAnywhere, Category = "Memory Information")` — partial memory size used to store the pose feature vectors in PCA space.
- L136 _public member_ `FText KDTreeSize;` — `UPROPERTY(VisibleAnywhere, Category = "Memory Information")` — partial memory size used by the kdtree.
- L140 _public member_ `FText VPTreeSize;` — `UPROPERTY(VisibleAnywhere, Category = "Memory Information")` — partial memory size used by the vptree.
- L144 _public member_ `FText PoseMetadataSize;` — `UPROPERTY(VisibleAnywhere, Category = "Memory Information")` — partial memory size used to store database metadata.
- L148 _public member_ `FText AssetsSize;` — `UPROPERTY(VisibleAnywhere, Category = "Memory Information")` — partial memory size used to animation data sub ranges, mirror state, blend parameters.
- L153 _public member_ `FText EventDataSize;` — `UPROPERTY(VisibleAnywhere, Category = "Memory Information")` — Experimental, this feature might be removed without warning, not for production use partial memory size used for events.
- L158 _public member_ `FText SourceAnimAssetsSizeCookedEstimate;` — `UPROPERTY(VisibleAnywhere, Category = "Memory Information")` — Experimental, this feature might be removed without warning, not for production use partial memory size used by the cooked animation assets.
- L161 _public prototype_ `void Initialize(const UPoseSearchDatabase* PoseSearchDatabase);` — Initialize statistics given a database

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchDatabaseFactory.h` (Public)


#### class `UPoseSearchDatabaseFactory`  
`class UPoseSearchDatabaseFactory : public UFactory`  
_L16-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L21 _private member_ `TObjectPtr<class UPoseSearchSchema> TargetSchema;` — `UPROPERTY()`
- L23 _private member_ `TSharedPtr<SWindow> PickerWindow;`
- L26 _private prototype_ `virtual bool ConfigureProperties() override;` — UFactory interface
- L27 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L28 _private prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L31 _private prototype_ `void OnTargetSchemaSelected(const FAssetData& SelectedAsset);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API POSESEARCHEDITOR_API`

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchDatabasePreviewScene.h` (Public)


#### class `UE::PoseSearch::FDatabasePreviewScene`  
`class FDatabasePreviewScene : public FAdvancedPreviewScene`  
_L12-32_
- inherits: `FAdvancedPreviewScene`
- L16 _public prototype_ `FDatabasePreviewScene( ConstructionValues CVs, const TSharedRef<FDatabaseEditor>& Editor);`
- L19 _public prototype_ `~FDatabasePreviewScene() = default;`
- L21 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L23 _public function_ `TSharedRef<FDatabaseEditor> GetEditor() const`
- L31 _private member_ `TWeakPtr<FDatabaseEditor> EditorPtr;` — The asset editor we are embedded in

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchDatabaseViewModel.h` (Public)


#### struct `UE::PoseSearch::FDatabasePreviewActor`  
`struct FDatabasePreviewActor`  
_L32-66_
- L35 _public prototype_ `bool SpawnPreviewActor(UWorld* World, const UPoseSearchDatabase* PoseSearchDatabase, int32 IndexAssetIdx, const FRole& Role, const FTransform& SamplerRootTransformOrigin, int32 PoseIdxForTimeOffset = INDEX_NONE);`
- L36 _public prototype_ `void UpdatePreviewActor(const UPoseSearchDatabase* PoseSearchDatabase, float PlayTime, bool bQuantizeAnimationToPoseData);`
- L37 _public prototype_ `static bool DrawPreviewActors(TConstArrayView<FDatabasePreviewActor> PreviewActors, const UPoseSearchDatabase* PoseSearchDatabase, bool bDisplayRootMotionSpeed, bool bDisplayBlockTransition, bool bDisplayEventData, TConstArrayView<float> QueryVector);`
- L39 _public prototype_ `void Destroy();`
- L41 _public prototype_ `UDebugSkelMeshComponent* GetDebugSkelMeshComponent();`
- L42 _public prototype_ `const UDebugSkelMeshComponent* GetDebugSkelMeshComponent() const;`
- L43 _public prototype_ `const UAnimPreviewInstance* GetAnimPreviewInstance() const;`
- L44 _public function_ `const FAnimationAssetSampler& GetSampler() const`
- L46 _public function_ `const AActor* GetActor() const`
- L47 _public function_ `int32 GetIndexAssetIndex() const`
- L48 _public function_ `int32 GetCurrentPoseIndex() const`
- L49 _public function_ `float GetPlayTimeOffset() const`
- L52 _private prototype_ `UAnimPreviewInstance* GetAnimPreviewInstanceInternal();`
- L54 _private member_ `TWeakObjectPtr<AActor> ActorPtr;`
- L55 _private member_ `int32 IndexAssetIndex = INDEX_NONE;`
- L56 _private member_ `int32 CurrentPoseIndex = INDEX_NONE;`
- L57 _private member_ `float PlayTimeOffset = 0.f;`
- L58 _private member_ `float CurrentTime = 0.f;`
- L59 _private member_ `float QuantizedTime = 0.f;`
- L61 _private member_ `FAnimationAssetSampler Sampler;`
- L62 _private member_ `FTransformTrajectory Trajectory;`
- L63 _private member_ `TArray<float> TrajectorySpeed;`
- L65 _private member_ `FRole ActorRole = DefaultRole;`

#### class `UE::PoseSearch::FDatabaseViewModel`  
`class FDatabaseViewModel : public TSharedFromThis<FDatabaseViewModel>, public FGCObject`  
_L68-178_
- inherits: `TSharedFromThis<FDatabaseViewModel>,FGCObject`
- L72 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L73 _public function_ `virtual FString GetReferencerName() const override`
- L75 _public prototype_ `void Initialize(UPoseSearchDatabase* InPoseSearchDatabase, const TSharedRef<FDatabasePreviewScene>& InPreviewScene, const TSharedRef<SDatabaseDataDetails>& InDatabaseDataDetails);`
- L77 _public prototype_ `void RemovePreviewActors();`
- L78 _public prototype_ `void BuildSearchIndex();`
- L80 _public prototype_ `void PreviewBackwardEnd();`
- L81 _public prototype_ `void PreviewBackwardStep();`
- L82 _public prototype_ `void PreviewBackward();`
- L83 _public prototype_ `void PreviewPause();`
- L84 _public prototype_ `void PreviewForward();`
- L85 _public prototype_ `void PreviewForwardStep();`
- L86 _public prototype_ `void PreviewForwardEnd();`
- L88 _public function_ `UPoseSearchDatabase* GetPoseSearchDatabase()`
- L89 _public function_ `const UPoseSearchDatabase* GetPoseSearchDatabase() const`
- L90 _public prototype_ `void OnPreviewActorClassChanged();`
- L92 _public prototype_ `void Tick(float DeltaSeconds);`
- L94 _public function_ `const TArray<TArray<FDatabasePreviewActor>>& GetPreviewActors() const`
- L95 _public function_ `TArray<TArray<FDatabasePreviewActor>>& GetPreviewActors()`
- L97 _public function_ `void ToggleDisplayRootMotionSpeed()`
- L98 _public function_ `bool IsDisplayRootMotionSpeedChecked() const`
- L100 _public function_ `void ToggleQuantizeAnimationToPoseData()`
- L101 _public function_ `bool IsQuantizeAnimationToPoseDataChecked() const`
- L103 _public function_ `void ToggleShowBones()`
- L104 _public function_ `bool IsShowBonesChecked() const`
- L106 _public function_ `void ToggleDisplayBlockTransition()`
- L107 _public function_ `bool IsDisplayBlockTransitionChecked() const`
- L109 _public function_ `void ToggleDisplayEventData()`
- L110 _public function_ `bool IsDisplayEventDataChecked() const`
- L112 _public prototype_ `void AddAnimationAssetToDatabase(UObject* AnimationAsset);`
- L113 _public prototype_ `bool DeleteFromDatabase(int32 AnimationAssetIndex);`
- L115 _public prototype_ `void SetDisableReselection(int32 AnimationAssetIndex, bool bEnabled);`
- L116 _public prototype_ `bool IsDisableReselection(int32 AnimationAssetIndex) const;`
- L118 _public prototype_ `void SetIsEnabled(int32 AnimationAssetIndex, bool bEnabled);`
- L119 _public prototype_ `bool IsEnabled(int32 AnimationAssetIndex) const;`
- L121 _public prototype_ `bool SetAnimationAsset(int32 AnimationAssetIndex, UObject* AnimAsset);`
- L123 _public prototype_ `void SetMirrorOption(int32 AnimationAssetIndex, EPoseSearchMirrorOption InMirrorOption);`
- L124 _public prototype_ `EPoseSearchMirrorOption GetMirrorOption(int32 AnimationAssetIndex);`
- L126 _public prototype_ `int32 SetSelectedNode(int32 PoseIdx, bool bClearSelection, bool bDrawQuery, TConstArrayView<float> InQueryVector);`
- L127 _public prototype_ `void SetSelectedNodes(const TArrayView<TSharedPtr<FDatabaseAssetTreeNode>>& InSelectedNodes);`
- L128 _public prototype_ `void ProcessSelectedActor(AActor* Actor);`
- L130 _public function_ `TConstArrayView<float> GetQueryVector() const`
- L131 _public prototype_ `void SetDrawQueryVector(bool bValue);`
- L132 _public function_ `bool ShouldDrawQueryVector() const`
- L134 _public prototype_ `const FSearchIndexAsset* GetSelectedActorIndexAsset() const;`
- L136 _public prototype_ `TRange<double> GetPreviewPlayRange() const;`
- L138 _public prototype_ `void SetPlayTime(float NewPlayTime, bool bInTickPlayTime);`
- L139 _public prototype_ `float GetPlayTime() const;`
- L140 _public function_ `bool IsEditorSelection() const`
- L141 _public prototype_ `bool GetAnimationTime(int32 SourceAssetIdx, float& CurrentPlayTime, FVector& BlendParameters) const;`
- L144 _private prototype_ `UWorld* GetWorld();`
- L146 _private member_ `float PlayTime = 0.f;`
- L147 _private member_ `float DeltaTimeMultiplier = 1.f;`
- L148 _private member_ `float StepDeltaTime = 1.f / 30.f;`
- L151 _private member_ `TWeakObjectPtr<UPoseSearchDatabase> PoseSearchDatabasePtr;` — Scene asset being viewed and edited by this view model.
- L154 _private member_ `TWeakPtr<FDatabasePreviewScene> PreviewScenePtr;` — Weak pointer to the PreviewScene
- L157 _private member_ `TWeakPtr<SDatabaseDataDetails> DatabaseDataDetails;` — Weak pointer to the SDatabaseDataDetails
- L160 _private member_ `TArray<TArray<FDatabasePreviewActor>> PreviewActors;` — Actors to be displayed in the preview viewport
- L163 _private member_ `float MaxPreviewPlayLength = 0.f;` — From zero to the play length of the longest preview
- L164 _private member_ `float MinPreviewPlayLength = 0.f;`
- L166 _private member_ `bool bIsEditorSelection = true;`
- L167 _private member_ `bool bDrawQueryVector = false;`
- L168 _private member_ `TArray<float> QueryVector;`
- L171 _private member_ `bool bDisplayRootMotionSpeed = false;` — Is animation debug draw enabled
- L172 _private member_ `bool bQuantizeAnimationToPoseData = false;`
- L173 _private member_ `bool bShowBones = false;`
- L174 _private member_ `bool bDisplayBlockTransition = false;`
- L175 _private member_ `bool bDisplayEventData = false;`
- L177 _private member_ `int32 SelectedActorIndexAssetIndex = INDEX_NONE;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchDatabaseViewportClient.h` (Public)


#### class `UE::PoseSearch::FDatabaseViewportClient`  
`class FDatabaseViewportClient : public FEditorViewportClient`  
_L15-49_
- inherits: `FEditorViewportClient`
- L19 _public prototype_ `FDatabaseViewportClient( const TSharedRef<FDatabasePreviewScene>& InPreviewScene, const TSharedRef<SDatabaseViewport>& InViewport, const TSharedRef<FDatabaseEditor>& InAssetEditor);`
- L23 _public prototype_ `virtual ~FDatabaseViewportClient() = default;`
- L26 _public prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L27 _public prototype_ `virtual void TrackingStarted(const struct FInputEventState& InInputState, bool bIsDragging, bool bNudge) override;`
- L28 _public prototype_ `virtual void TrackingStopped() override;`
- L32 _public function_ `TSharedRef<FDatabasePreviewScene> GetPreviewScene() const` — Get the preview scene we are viewing
- L37 _public function_ `TSharedRef<FDatabaseEditor> GetAssetEditor() const`
- L45 _private member_ `TWeakPtr<FDatabasePreviewScene> PreviewScenePtr;` — Preview scene we are viewing
- L48 _private member_ `TWeakPtr<FDatabaseEditor> AssetEditorPtr;` — Asset editor we are embedded in

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchDebuggerTrackCreator.h` (Public)


#### class `UE::PoseSearch::FDebuggerTrackCreator`  
`class FDebuggerTrackCreator : public RewindDebugger::IRewindDebuggerTrackCreator`  
_L13-22_
- inherits: `RewindDebugger::IRewindDebuggerTrackCreator`
- L16 _private prototype_ `virtual FName GetTargetTypeNameInternal() const override;`
- L17 _private function_ `virtual FName GetNameInternal() const override`
- L18 _private prototype_ `virtual void GetTrackTypesInternal(TArray<RewindDebugger::FRewindDebuggerTrackType>& Types) const override;`
- L19 _private prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrackInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L20 _private prototype_ `virtual bool HasDebugInfoInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L21 _private function_ `virtual int32 GetSortOrderPriorityInternal() const override`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API POSESEARCHEDITOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchEditor.h` (Public)


#### class `IPoseSearchEditorModuleInterface`  
`class IPoseSearchEditorModuleInterface : public IModuleInterface`  
_L10-12_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPoseSearchEditor, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPoseSearchEditor, Log, All);`

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchInteractionAssetEditor.h` (Public)


#### struct `UE::PoseSearch::FInteractionAssetPreviewActor`  
`struct FInteractionAssetPreviewActor`  
_L29-50_
- desc: Experimental, this feature might be removed without warning, not for production use
- L32 _public prototype_ `bool SpawnPreviewActor(UWorld* World, const UPoseSearchInteractionAsset* InteractionAsset, const UE::PoseSearch::FRole& Role);`
- L33 _public prototype_ `void UpdatePreviewActor(const UPoseSearchInteractionAsset* InteractionAsset, float PlayTime);`
- L34 _public prototype_ `void Destroy();`
- L35 _public prototype_ `UAnimPreviewInstance* GetAnimPreviewInstance();`
- L36 _public function_ `const UE::PoseSearch::FRole& GetRole() const`
- L37 _public prototype_ `FTransform GetDebugActorTransformFromSampler() const;`
- L38 _public prototype_ `void ForceDebugActorTransform(const FTransform& ActorTransform);`
- L42 _private member_ `TWeakObjectPtr<AActor> ActorPtrs[NumActors];`
- L43 _private member_ `UE::PoseSearch::FAnimationAssetSampler Samplers[NumActors];` — used to keep track of the animation position / orientation
- L45 _private member_ `float CurrentTime = 0.f;`
- L46 _private member_ `UE::PoseSearch::FRole ActorRole = UE::PoseSearch::DefaultRole;`
- L49 _private member_ `FVector BlendParameters = FVector::ZeroVector;` — @todo: add support for blend spaces

#### enum `UE::PoseSearch::FInteractionAssetPreviewActor::(anonymous)`  
`enum`  
_L41-41_

#### class `UE::PoseSearch::FInteractionAssetViewModel`  
`class FInteractionAssetViewModel : public TSharedFromThis<FInteractionAssetViewModel>, public FGCObject`  
_L53-87_
- inherits: `TSharedFromThis<FInteractionAssetViewModel>,FGCObject`
- desc: Experimental, this feature might be removed without warning, not for production use
- L56 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L57 _public function_ `virtual FString GetReferencerName() const override`
- L58 _public prototype_ `void Initialize(UPoseSearchInteractionAsset* InteractionAsset, const TSharedRef<FInteractionAssetPreviewScene>& PreviewScene);`
- L59 _public prototype_ `void PreviewBackwardEnd();`
- L60 _public prototype_ `void PreviewBackwardStep();`
- L61 _public prototype_ `void PreviewBackward();`
- L62 _public prototype_ `void PreviewPause();`
- L63 _public prototype_ `void PreviewForward();`
- L64 _public prototype_ `void PreviewForwardStep();`
- L65 _public prototype_ `void PreviewForwardEnd();`
- L66 _public function_ `const UPoseSearchInteractionAsset* GetInteractionAsset() const`
- L67 _public prototype_ `void Tick(float DeltaSeconds);`
- L68 _public function_ `TConstArrayView<FInteractionAssetPreviewActor> GetPreviewActors() const`
- L69 _public prototype_ `TRange<double> GetPreviewPlayRange() const;`
- L70 _public prototype_ `void SetPlayTime(float NewPlayTime, bool bInTickPlayTime);`
- L71 _public function_ `float GetPlayTime() const`
- L72 _public prototype_ `void SetPreviewProperties(float AnimAssetTime, const FVector& AnimAssetBlendParameters, bool bAnimAssetPlaying);`
- L75 _private prototype_ `UWorld* GetWorld();`
- L77 _private member_ `float PlayTime = 0.f;`
- L78 _private member_ `float DeltaTimeMultiplier = 1.f;`
- L79 _private member_ `float StepDeltaTime = 1.f / 30.f;`
- L82 _private member_ `TWeakObjectPtr<UPoseSearchInteractionAsset> InteractionAssetPtr;` — asset being viewed and edited by this view model.
- L84 _private member_ `TWeakPtr<FInteractionAssetPreviewScene> PreviewScenePtr;` — Weak pointer to the PreviewScene
- L86 _private member_ `TArray<FInteractionAssetPreviewActor> PreviewActors;` — Actors to be displayed in the preview viewport

#### class `UE::PoseSearch::FInteractionAssetEdMode`  
`class FInteractionAssetEdMode : public FEdMode`  
_L90-104_
- inherits: `FEdMode`
- desc: Experimental, this feature might be removed without warning, not for production use
- L93 _public member_ `const static FEditorModeID EdModeId;`
- L95 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L96 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L97 _public prototype_ `virtual bool AllowWidgetMove() override;`
- L98 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L99 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L100 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L103 _private member_ `FInteractionAssetViewModel* ViewModel = nullptr;`

#### class `UE::PoseSearch::FInteractionAssetViewportClient`  
`class FInteractionAssetViewportClient : public FEditorViewportClient`  
_L107-124_
- inherits: `FEditorViewportClient`
- desc: Experimental, this feature might be removed without warning, not for production use
- L110 _public prototype_ `FInteractionAssetViewportClient(const TSharedRef<FInteractionAssetPreviewScene>& InPreviewScene, const TSharedRef<SInteractionAssetViewport>& InViewport, const TSharedRef<FInteractionAssetEditor>& InAssetEditor);`
- L111 _public prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L112 _public prototype_ `virtual void TrackingStarted(const struct FInputEventState& InInputState, bool bIsDragging, bool bNudge) override;`
- L113 _public prototype_ `virtual void TrackingStopped() override;`
- L116 _public function_ `TSharedRef<FInteractionAssetPreviewScene> GetPreviewScene() const` — Get the preview scene we are viewing
- L117 _public function_ `TSharedRef<FInteractionAssetEditor> GetAssetEditor() const`
- L121 _private member_ `TWeakPtr<FInteractionAssetPreviewScene> PreviewScenePtr;` — Preview scene we are viewing
- L123 _private member_ `TWeakPtr<FInteractionAssetEditor> AssetEditorPtr;` — Asset editor we are embedded in

#### class `UE::PoseSearch::FInteractionAssetPreviewScene`  
`class FInteractionAssetPreviewScene : public FAdvancedPreviewScene`  
_L127-137_
- inherits: `FAdvancedPreviewScene`
- desc: Experimental, this feature might be removed without warning, not for production use
- L130 _public prototype_ `FInteractionAssetPreviewScene(ConstructionValues CVs, const TSharedRef<FInteractionAssetEditor>& Editor);`
- L131 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L132 _public function_ `TSharedRef<FInteractionAssetEditor> GetEditor() const`
- L136 _private member_ `TWeakPtr<FInteractionAssetEditor> EditorPtr;` — The asset editor we are embedded in

#### struct `UE::PoseSearch::FInteractionAssetPreviewRequiredArgs`  
`struct FInteractionAssetPreviewRequiredArgs`  
_L140-150_
- desc: Experimental, this feature might be removed without warning, not for production use
- L142 _public function_ `FInteractionAssetPreviewRequiredArgs(const TSharedRef<FInteractionAssetEditor>& InAssetEditor, const TSharedRef<FInteractionAssetPreviewScene>& InPreviewScene) : AssetEditor(InAssetEditor) , PreviewScene(InPreviewScene)`
- L148 _public member_ `TSharedRef<FInteractionAssetEditor> AssetEditor;`
- L149 _public member_ `TSharedRef<FInteractionAssetPreviewScene> PreviewScene;`

#### class `UE::PoseSearch::SInteractionAssetViewport`  
`class SInteractionAssetViewport : public SEditorViewport, public ICommonEditorViewportToolbarInfoProvider`  
_L153-177_
- inherits: `SEditorViewport,ICommonEditorViewportToolbarInfoProvider`
- desc: Experimental, this feature might be removed without warning, not for production use
- L156 _public function_ `SLATE_BEGIN_ARGS(SInteractionAssetViewport)`
- L157 _public prototype_ `SLATE_END_ARGS();`
- L159 _public prototype_ `void Construct(const FArguments& InArgs, const FInteractionAssetPreviewRequiredArgs& InRequiredArgs);`
- L160 _public prototype_ `virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;`
- L161 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L162 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L165 _protected prototype_ `virtual void BindCommands() override;`
- L166 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L167 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L170 _protected member_ `TSharedPtr<SCommonEditorViewportToolbarBase> ViewportToolbar;` — The viewport toolbar
- L172 _protected member_ `TSharedPtr<FInteractionAssetViewportClient> ViewportClient;` — Viewport client
- L174 _protected member_ `TWeakPtr<FInteractionAssetPreviewScene> PreviewScenePtr;` — The preview scene that we are viewing
- L176 _protected member_ `TWeakPtr<FInteractionAssetEditor> AssetEditorPtr;` — Asset editor we are embedded in

#### class `UE::PoseSearch::SInteractionAssetPreview`  
`class SInteractionAssetPreview : public SCompoundWidget`  
_L180-214_
- inherits: `SCompoundWidget`
- desc: Experimental, this feature might be removed without warning, not for production use
- L183 _public function_ `DECLARE_DELEGATE_TwoParams(FOnScrubPositionChanged, double, bool) DECLARE_DELEGATE(FOnButtonClickedEvent) SLATE_BEGIN_ARGS(SInteractionAssetPreview)`
- L187 _public prototype_ `SLATE_ATTRIBUTE(FLinearColor, SliderColor);`
- L188 _public prototype_ `SLATE_ATTRIBUTE(double, SliderScrubTime);`
- L189 _public prototype_ `SLATE_ATTRIBUTE(TRange<double>, SliderViewRange);`
- L190 _public prototype_ `SLATE_EVENT(FOnScrubPositionChanged, OnSliderScrubPositionChanged);`
- L191 _public prototype_ `SLATE_EVENT(FOnButtonClickedEvent, OnBackwardEnd);`
- L192 _public prototype_ `SLATE_EVENT(FOnButtonClickedEvent, OnBackwardStep);`
- L193 _public prototype_ `SLATE_EVENT(FOnButtonClickedEvent, OnBackward);`
- L194 _public prototype_ `SLATE_EVENT(FOnButtonClickedEvent, OnPause);`
- L195 _public prototype_ `SLATE_EVENT(FOnButtonClickedEvent, OnForward);`
- L196 _public prototype_ `SLATE_EVENT(FOnButtonClickedEvent, OnForwardStep);`
- L197 _public prototype_ `SLATE_EVENT(FOnButtonClickedEvent, OnForwardEnd);`
- L198 _public prototype_ `SLATE_END_ARGS();`
- L200 _public prototype_ `void Construct(const FArguments& InArgs, const FInteractionAssetPreviewRequiredArgs& InRequiredArgs);`
- L203 _protected member_ `TAttribute<FLinearColor> SliderColor;`
- L204 _protected member_ `TAttribute<double> SliderScrubTime;`
- L205 _protected member_ `TAttribute<TRange<double>> SliderViewRange = TRange<double>(0.0, 1.0);`
- L206 _protected member_ `FOnScrubPositionChanged OnSliderScrubPositionChanged;`
- L207 _protected member_ `FOnButtonClickedEvent OnBackwardEnd;`
- L208 _protected member_ `FOnButtonClickedEvent OnBackwardStep;`
- L209 _protected member_ `FOnButtonClickedEvent OnBackward;`
- L210 _protected member_ `FOnButtonClickedEvent OnPause;`
- L211 _protected member_ `FOnButtonClickedEvent OnForward;`
- L212 _protected member_ `FOnButtonClickedEvent OnForwardStep;`
- L213 _protected member_ `FOnButtonClickedEvent OnForwardEnd;`

#### class `UE::PoseSearch::FInteractionAssetEditor`  
`class FInteractionAssetEditor : public IMultiAnimAssetEditor, public FNotifyHook`  
_L217-249_
- inherits: `IMultiAnimAssetEditor,FNotifyHook`
- desc: Experimental, this feature might be removed without warning, not for production use
- L220 _public prototype_ `void InitAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UPoseSearchInteractionAsset* InteractionAsset);`
- L222 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L223 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L224 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L225 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L226 _public prototype_ `virtual FText GetToolkitName() const override;`
- L227 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L228 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L229 _public prototype_ `virtual void SetPreviewProperties(float AnimAssetTime, const FVector& AnimAssetBlendParameters, bool bAnimAssetPlaying) override;`
- L231 _public function_ `const UPoseSearchInteractionAsset* GetInteractionAsset() const`
- L232 _public function_ `FInteractionAssetViewModel* GetViewModel() const`
- L233 _public function_ `void PreviewBackwardEnd()`
- L234 _public function_ `void PreviewBackwardStep()`
- L235 _public function_ `void PreviewBackward()`
- L236 _public function_ `void PreviewPause()`
- L237 _public function_ `void PreviewForward()`
- L238 _public function_ `void PreviewForwardStep()`
- L239 _public function_ `void PreviewForwardEnd()`
- L242 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);`
- L243 _private prototype_ `TSharedRef<SDockTab> SpawnTab_AssetDetails(const FSpawnTabArgs& Args);`
- L245 _private member_ `TSharedPtr<SInteractionAssetPreview> PreviewWidget;`
- L246 _private member_ `TSharedPtr<IDetailsView> EditingAssetWidget;`
- L247 _private member_ `TSharedPtr<FInteractionAssetPreviewScene> PreviewScene;`
- L248 _private member_ `TSharedPtr<FInteractionAssetViewModel> ViewModel;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace PoseSearch` (scope `UE`)
- L41 _enumerator_ `enum { PreviewActor, DebugActor, NumActors }; TWeakObjectPtr<AActor> ActorPtrs[NumActors]; UE::PoseSearch::FAnimationAssetSampler Samplers[NumActors]; float CurrentTime = 0.f; UE::PoseSearch::FRole ActorRole = UE::PoseSearch::DefaultRole;` (scope `UE::PoseSearch::FInteractionAssetPreviewActor::__anon42fd7ae00103`)
- L41 _enumerator_ `enum { PreviewActor, DebugActor, NumActors }; TWeakObjectPtr<AActor> ActorPtrs[NumActors]; UE::PoseSearch::FAnimationAssetSampler Samplers[NumActors]; float CurrentTime = 0.f; UE::PoseSearch::FRole ActorRole = UE::PoseSearch::DefaultRole;` (scope `UE::PoseSearch::FInteractionAssetPreviewActor::__anon42fd7ae00103`)
- L41 _enumerator_ `enum { PreviewActor, DebugActor, NumActors }; TWeakObjectPtr<AActor> ActorPtrs[NumActors]; UE::PoseSearch::FAnimationAssetSampler Samplers[NumActors]; float CurrentTime = 0.f; UE::PoseSearch::FRole ActorRole = UE::PoseSearch::DefaultRole;` (scope `UE::PoseSearch::FInteractionAssetPreviewActor::__anon42fd7ae00103`)
- L183 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnScrubPositionChanged, double, bool) DECLARE_DELEGATE(FOnButtonClickedEvent) SLATE_BEGIN_ARGS(SInteractionAssetPreview) {} SLATE_ATTRIBUTE(FLinearColor, SliderColor);`
- L184 _delegate_ `DECLARE_DELEGATE(FOnButtonClickedEvent) SLATE_BEGIN_ARGS(SInteractionAssetPreview) {} SLATE_ATTRIBUTE(FLinearColor, SliderColor);`

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchInteractionAssetFactory.h` (Public)


#### class `UPoseSearchInteractionAssetFactory`  
`class UPoseSearchInteractionAssetFactory : public UFactory`  
_L11-19_
- reflection: `UCLASS(Experimental)`
- inherits: `UFactory`
- L16 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface
- L17 _private prototype_ `virtual FString GetDefaultNewAssetName() const override;`

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchNormalizationSetFactory.h` (Public)


#### class `UPoseSearchNormalizationSetFactory`  
`class UPoseSearchNormalizationSetFactory : public UFactory`  
_L13-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L18 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface
- L19 _private prototype_ `virtual FString GetDefaultNewAssetName() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API POSESEARCHEDITOR_API`

### `Plugins/Animation/PoseSearch/Source/Editor/Public/PoseSearchSchemaFactory.h` (Public)


#### class `UPoseSearchSchemaFactory`  
`class UPoseSearchSchemaFactory : public UFactory`  
_L16-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L21 _private member_ `TObjectPtr<class USkeleton> TargetSkeleton;` — `UPROPERTY()`
- L23 _private member_ `TSharedPtr<SWindow> PickerWindow;`
- L26 _private prototype_ `virtual bool ConfigureProperties() override;` — UFactory interface
- L27 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L28 _private prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L31 _private prototype_ `void OnTargetSkeletonSelected(const FAssetData& SelectedAsset);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API POSESEARCHEDITOR_API`

### `Plugins/Animation/PoseSearch/Source/Editor/Public/SPoseSearchDatabaseViewport.h` (Public)


#### struct `UE::PoseSearch::FDatabasePreviewRequiredArgs`  
`struct FDatabasePreviewRequiredArgs`  
_L17-30_
- L19 _public function_ `FDatabasePreviewRequiredArgs( const TSharedRef<FDatabaseEditor>& InAssetEditor, const TSharedRef<FDatabasePreviewScene>& InPreviewScene) : AssetEditor(InAssetEditor) , PreviewScene(InPreviewScene)`
- L27 _public member_ `TSharedRef<FDatabaseEditor> AssetEditor;`
- L29 _public member_ `TSharedRef<FDatabasePreviewScene> PreviewScene;`

#### class `UE::PoseSearch::SDatabaseViewport`  
`class SDatabaseViewport : public SEditorViewport, public ICommonEditorViewportToolbarInfoProvider`  
_L32-79_
- inherits: `SEditorViewport,ICommonEditorViewportToolbarInfoProvider`
- L35 _public function_ `SLATE_BEGIN_ARGS(SDatabaseViewport)`
- L36 _public prototype_ `SLATE_END_ARGS();`
- L38 _public prototype_ `void Construct(const FArguments& InArgs, const FDatabasePreviewRequiredArgs& InRequiredArgs);`
- L39 _public prototype_ `virtual ~SDatabaseViewport() = default;`
- L42 _public prototype_ `virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;`
- L43 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L44 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L50 _protected prototype_ `virtual void BindCommands() override;`
- L51 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L52 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L55 _protected prototype_ `void OnToggleDisplayRootMotionSpeed();`
- L56 _protected prototype_ `bool IsDisplayRootMotionSpeedChecked() const;`
- L57 _protected prototype_ `void OnToggleQuantizeAnimationToPoseData();`
- L58 _protected prototype_ `bool IsQuantizeAnimationToPoseDataChecked() const;`
- L59 _protected prototype_ `void OnToggleShowBones();`
- L60 _protected prototype_ `bool IsShowBonesChecked() const;`
- L61 _protected prototype_ `void OnToggleDisplayBlockTransition();`
- L62 _protected prototype_ `bool IsDisplayBlockTransitionChecked() const;`
- L64 _protected prototype_ `void OnToggleDisplayEventData();` — Experimental, this feature might be removed without warning, not for production use
- L66 _protected prototype_ `bool IsDisplayEventDataChecked() const;` — Experimental, this feature might be removed without warning, not for production use
- L69 _protected member_ `TSharedPtr<SPoseSearchDatabaseViewportToolBar> ViewportToolbar;` — The viewport toolbar
- L72 _protected member_ `TSharedPtr<FDatabaseViewportClient> ViewportClient;` — Viewport client
- L75 _protected member_ `TWeakPtr<FDatabasePreviewScene> PreviewScenePtr;` — The preview scene that we are viewing
- L78 _protected member_ `TWeakPtr<FDatabaseEditor> AssetEditorPtr;` — Asset editor we are embedded in

#### class `UE::PoseSearch::SDatabasePreview`  
`class SDatabasePreview : public SCompoundWidget`  
_L81-115_
- inherits: `SCompoundWidget`
- L84 _public function_ `DECLARE_DELEGATE_TwoParams(FOnScrubPositionChanged, double, bool) DECLARE_DELEGATE(FOnButtonClickedEvent) SLATE_BEGIN_ARGS(SDatabasePreview)`
- L88 _public prototype_ `SLATE_ATTRIBUTE(FLinearColor, SliderColor);`
- L89 _public prototype_ `SLATE_ATTRIBUTE(double, SliderScrubTime);`
- L90 _public prototype_ `SLATE_ATTRIBUTE(TRange<double>, SliderViewRange);`
- L91 _public prototype_ `SLATE_EVENT(FOnScrubPositionChanged, OnSliderScrubPositionChanged);`
- L92 _public prototype_ `SLATE_EVENT(FOnButtonClickedEvent, OnBackwardEnd);`
- L93 _public prototype_ `SLATE_EVENT(FOnButtonClickedEvent, OnBackwardStep);`
- L94 _public prototype_ `SLATE_EVENT(FOnButtonClickedEvent, OnBackward);`
- L95 _public prototype_ `SLATE_EVENT(FOnButtonClickedEvent, OnPause);`
- L96 _public prototype_ `SLATE_EVENT(FOnButtonClickedEvent, OnForward);`
- L97 _public prototype_ `SLATE_EVENT(FOnButtonClickedEvent, OnForwardStep);`
- L98 _public prototype_ `SLATE_EVENT(FOnButtonClickedEvent, OnForwardEnd);`
- L99 _public prototype_ `SLATE_END_ARGS();`
- L101 _public prototype_ `void Construct(const FArguments& InArgs, const FDatabasePreviewRequiredArgs& InRequiredArgs);`
- L104 _protected member_ `TAttribute<FLinearColor> SliderColor;`
- L105 _protected member_ `TAttribute<double> SliderScrubTime;`
- L106 _protected member_ `TAttribute<TRange<double>> SliderViewRange = TRange<double>(0.0, 1.0);`
- L107 _protected member_ `FOnScrubPositionChanged OnSliderScrubPositionChanged;`
- L108 _protected member_ `FOnButtonClickedEvent OnBackwardEnd;`
- L109 _protected member_ `FOnButtonClickedEvent OnBackwardStep;`
- L110 _protected member_ `FOnButtonClickedEvent OnBackward;`
- L111 _protected member_ `FOnButtonClickedEvent OnPause;`
- L112 _protected member_ `FOnButtonClickedEvent OnForward;`
- L113 _protected member_ `FOnButtonClickedEvent OnForwardStep;`
- L114 _protected member_ `FOnButtonClickedEvent OnForwardEnd;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PoseSearch` (scope `UE`)
- L84 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnScrubPositionChanged, double, bool) DECLARE_DELEGATE(FOnButtonClickedEvent) SLATE_BEGIN_ARGS(SDatabasePreview) {} SLATE_ATTRIBUTE(FLinearColor, SliderColor);`
- L85 _delegate_ `DECLARE_DELEGATE(FOnButtonClickedEvent) SLATE_BEGIN_ARGS(SDatabasePreview) {} SLATE_ATTRIBUTE(FLinearColor, SliderColor);`

### `Plugins/Animation/PoseSearch/Source/Editor/Public/SPoseSearchDatabaseViewportToolbar.h` (Public)


#### class `UE::PoseSearch::SPoseSearchDatabaseViewportToolBar`  
`class SPoseSearchDatabaseViewportToolBar : public SCommonEditorViewportToolbarBase`  
_L13-26_
- inherits: `SCommonEditorViewportToolbarBase`
- L16 _public function_ `SLATE_BEGIN_ARGS(SPoseSearchDatabaseViewportToolBar)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SDatabaseViewport> InViewport);`
- L24 _public prototype_ `virtual TSharedRef<SWidget> GenerateShowMenu() const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PoseSearch` (scope `UE`)
