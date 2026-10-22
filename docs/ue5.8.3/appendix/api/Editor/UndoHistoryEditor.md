# Editor / UndoHistoryEditor

- module root: `Source/Editor/UndoHistoryEditor`
- headers: 4; symbols: 63
- symbol kinds: class=4, delegate=2, externvar=1, function=12, macro=1, member=18, prototype=24, struct=1
- PrivateDependencyModuleNames: CoreUObject, InputCore, Slate, SlateCore, ToolWidgets, UndoHistory, UnrealEd
- PublicDependencyModuleNames: Core

### `Source/Editor/UndoHistoryEditor/Private/UndoHistorySettings.h` (Private)


#### class `UUndoHistorySettings`  
`class UUndoHistorySettings : public UObject`  
_L14-23_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Implements the settings for the UndoHistory.
- L22 _public member_ `bool bShowTransactionDetails;` — `UPROPERTY(config)` — True when the UndoHistory is showing transaction details.

### `Source/Editor/UndoHistoryEditor/Private/Widgets/SUndoHistory.h` (Private)


#### class `SUndoHistory`  
`class SUndoHistory : public SCompoundWidget`  
_L18-134_
- inherits: `SCompoundWidget`
- desc: Implements the undo history panel.
- L37 _public function_ `SLATE_BEGIN_ARGS(SUndoHistory)`
- L40 _public prototype_ `virtual ~SUndoHistory();`
- L47 _public prototype_ `void Construct( const FArguments& InArgs );` — Construct this widget @param InArgs The declaration data for this widget.
- L50 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L58 _protected prototype_ `void ReloadUndoList( );` — Reloads the list of undo transactions.
- L59 _protected prototype_ `void OnUndoBufferChanged();`
- L60 _protected prototype_ `void OnTransactionStateChanged(const FTransactionContext& TransactionContext, ETransactionStateEventType TransactionState);`
- L65 _private prototype_ `void SelectLastTransaction();` — Select the last transaction in the undo history.
- L68 _private prototype_ `FReply HandleDiscardHistoryButtonClicked( );` — Callback for clicking the 'Discard History' button.
- L71 _private prototype_ `TSharedRef<ITableRow> HandleUndoListGenerateRow( TSharedPtr<FTransactionInfo> TransactionInfo, const TSharedRef<STableViewBase>& OwnerTable );` — Callback for generating a row widget for the message list view.
- L74 _private prototype_ `void HandleGoToTransaction(const FGuid& TargetTransactionId);` — Callback for when a user wants to jump to a certain transaction.
- L77 _private prototype_ `bool HandleIsCurrentUndoBarrier(int32 InQueueIndex) const;` — Callback for checking if the given index is the current undo barrier index.
- L80 _private prototype_ `bool HandleIsLastTransactionIndex(int32 InQueueIndex) const;` — Callback for checking if the given index is the last active transaction.
- L83 _private prototype_ `void HandleUndoBarrierButtonClicked(int32 InQueueIndex);` — Callback for when a user clicks to add or remove an undo barrier.
- L86 _private prototype_ `bool HandleUndoListRowIsApplied( int32 QueueIndex ) const;` — Callback for checking whether the specified undo list row transaction is applied.
- L89 _private prototype_ `void HandleUndoListSelectionChanged( TSharedPtr<FTransactionInfo> TransactionInfo, ESelectInfo::Type SelectInfo );` — Callback for selecting a message in the message list view.
- L92 _private prototype_ `FText HandleUndoSizeTextBlockText( ) const;` — Callback for getting the undo size text.
- L95 _private prototype_ `EVisibility HandleUndoWarningVisibility() const;` — Callback for getting the right undo size text color.
- L98 _private prototype_ `void HandleUndoListJumpToTransaction(TSharedPtr<FTransactionInfo> InItem);` — Callback for clicking on a transaction to display details.
- L101 _private prototype_ `EVisibility HandleUndoHistoryDetailsVisibility() const;` — Callback to handle UndoHistoryDetails visibility.
- L104 _private prototype_ `TSharedRef<SWidget> GetViewButtonContent() const;` — Callback for getting the view button's content.
- L107 _private prototype_ `void ToggleShowTransactionDetails();` — Toggle visibility of the transaction details section.
- L110 _private prototype_ `bool IsShowingTransactionDetails() const;` — Whether the transaction details section should be displayed.
- L115 _private member_ `int32 LastActiveTransactionIndex;` — Holds the index of the last active transaction.
- L118 _private member_ `TArray<TSharedPtr<FTransactionInfo> > UndoList;` — Holds the list of undo transaction indices.
- L121 _private member_ `TSharedPtr<SListView<TSharedPtr<FTransactionInfo> > > UndoListView;` — Holds the undo list view.
- L124 _private member_ `TSharedPtr<class SUndoHistoryDetails> UndoDetailsView;` — Holds the undo details panel view.
- L127 _private member_ `TSharedPtr<SSplitter> Splitter;` — Holds the Transaction panel splitter.
- L130 _private member_ `TSharedPtr<SSplitter::FSlot> DetailsSlot;` — Holds the Details slot from the splitter.
- L133 _private member_ `TSharedPtr<SButton> DiscardButton;` — Holds the undo history discard button.

#### struct `SUndoHistory::FTransactionInfo`  
`struct FTransactionInfo`  
_L22-33_
- desc: Structure for transaction information.
- L25 _public member_ `int32 QueueIndex;` — Holds the transactions index in the transaction queue.
- L28 _public function_ `FTransactionInfo( int32 InQueueIndex ) : QueueIndex(InQueueIndex)` — Creates and initializes a new instance.
- L32 _public prototype_ `const FTransaction* GetTransaction() const;`

### `Source/Editor/UndoHistoryEditor/Private/Widgets/SUndoHistoryTableRow.h` (Private)


#### class `SUndoHistoryTableRow`  
`class SUndoHistoryTableRow : public SMultiColumnTableRow<TSharedPtr<int32> >`  
_L36-167_
- inherits: `SMultiColumnTableRow<TSharedPtr<int32>>`
- desc: Implements a row widget for the undo history list.
- L42 _public function_ `SLATE_BEGIN_ARGS(SUndoHistoryTableRow)`
- L59 _public function_ `void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView )` — Constructs the widget. @param InArgs The construction arguments.
- L91 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override`
- L129 _private function_ `FSlateColor HandleTitleTextColorAndOpacity( ) const` — Callback for getting the color of the 'Title' text.
- L142 _private member_ `TAttribute<bool> IsApplied;` — Holds an attribute that determines whether the transaction in this row is applied.
- L145 _private member_ `TAttribute<bool> IsCurrentUndoBarrier;` — Holds an attribute that determines whether the transaction in this row is the current undo barrier.
- L148 _private member_ `TAttribute<bool> IsLastTransactionIndex;` — Holds an attribute that determines whether the transaction in this row is the last active transaction.
- L151 _private member_ `int32 QueueIndex;` — Holds the transaction's index in the transaction queue.
- L154 _private member_ `FGuid TransactionId;` — Holds the current transaction's id.
- L157 _private member_ `FText Title;` — Holds the transaction's title text.
- L160 _private member_ `FText Description;` — Holds the transaction's description text.
- L163 _private member_ `FOnGotoTransactionClicked OnGotoTransactionClicked;` — Delegate called when the Goto button is clicked
- L166 _private member_ `FOnUndoBarrierButtonClicked OnUndoBarrierButtonClicked;` — Delegate called when the Barrier button is clicked

#### Free symbols / members of external scopes

- L28 _macro_ `#define LOCTEXT_NAMESPACE "SUndoHistoryTableRow"`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGotoTransactionClicked, const FGuid&) DECLARE_DELEGATE_OneParam(FOnUndoBarrierButtonClicked, int32) class SUndoHistoryTableRow : public SMultiColumnTableRow<TSharedPtr<int32> > { public: SLATE_BEGIN_ARGS(SUndoHistoryTableRow) { } SLATE_ATTRIBUTE(bool, IsApplied) SLATE_ATTRIBUTE(bool, IsCurrentUndoBarrier) SLATE_ATTRIBUTE(bool, IsLastTransactionIndex) SLATE_ARGUMENT(int32, QueueIndex) SLATE_ARGUMENT(const FTransaction*, Transaction) SLATE_EVENT(FOnGotoTransactionClicked, OnGotoTransactionClicked) SLATE_EVENT(FOnUndoBarrierButtonClicked, OnUndoBarrierButtonClicked) SLATE_END_ARGS() public: void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView ) { IsApplied = InArgs._IsApplied; IsCurrentUndoBarrier = InArgs._IsCurrentUndoBarrier; IsLastTransactionIndex = InArgs._IsLastTransactionIndex; QueueIndex = InArgs._QueueIndex; OnGotoTransactionClicked = InArgs._OnGotoTransactionClicked; OnUndoBarrierButtonClicked = InArgs._OnUndoBarrierButtonClicked; FSuperRowType::FArguments Args = FSuperRowType::FArguments() .Style(&FAppStyle::Get().GetWidgetStyle<FTableRowStyle>("SceneOutliner.TableViewRow"));`
- L31 _delegate_ `DECLARE_DELEGATE_OneParam(FOnUndoBarrierButtonClicked, int32) class SUndoHistoryTableRow : public SMultiColumnTableRow<TSharedPtr<int32> > { public: SLATE_BEGIN_ARGS(SUndoHistoryTableRow) { } SLATE_ATTRIBUTE(bool, IsApplied) SLATE_ATTRIBUTE(bool, IsCurrentUndoBarrier) SLATE_ATTRIBUTE(bool, IsLastTransactionIndex) SLATE_ARGUMENT(int32, QueueIndex) SLATE_ARGUMENT(const FTransaction*, Transaction) SLATE_EVENT(FOnGotoTransactionClicked, OnGotoTransactionClicked) SLATE_EVENT(FOnUndoBarrierButtonClicked, OnUndoBarrierButtonClicked) SLATE_END_ARGS() public: void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView ) { IsApplied = InArgs._IsApplied; IsCurrentUndoBarrier = InArgs._IsCurrentUndoBarrier; IsLastTransactionIndex = InArgs._IsLastTransactionIndex; QueueIndex = InArgs._QueueIndex; OnGotoTransactionClicked = InArgs._OnGotoTransactionClicked; OnUndoBarrierButtonClicked = InArgs._OnUndoBarrierButtonClicked; FSuperRowType::FArguments Args = FSuperRowType::FArguments() .Style(&FAppStyle::Get().GetWidgetStyle<FTableRowStyle>("SceneOutliner.TableViewRow"));`
- L98 _function_ `.OnClicked_Lambda([this]() { OnGotoTransactionClicked.ExecuteIfBound(TransactionId); return FReply::Handled(); }) .Visibility_Lambda([this]() { return this->IsHovered() ? EVisibility::Visible : EVisibility::Hidden; });` (scope `SUndoHistoryTableRow::GenerateWidgetForColumn`)
- L99 _function_ `.Visibility_Lambda([this]() { return this->IsHovered() ? EVisibility::Visible : EVisibility::Hidden; });` (scope `SUndoHistoryTableRow::GenerateWidgetForColumn`)
- L116 _function_ `.ToolTipText_Lambda( [this]() { if (IsCurrentUndoBarrier.Get()) { return LOCTEXT("RemoveUndoBarrierTooltip", "Remove Undo Barrier"); } return LOCTEXT("SetUndoBarrierTooltip", "Set Undo Barrier"); }) .Icon(FAppStyle::GetBrush("Icons.PlusCircle")) .OnClicked_Lambda([this]() { OnUndoBarrierButtonClicked.ExecuteIfBound(QueueIndex); return FReply::Handled(); }) .Visibility_Lambda([this]() { return (GEditor && (!GEditor->PlayWorld || GEditor->bIsSimulatingInEditor)) && this->IsHovered() && (IsCurrentUndoBarrier.Get() || IsLastTransactionIndex.Get()) ? EVisibility::Visible : EVisibility::Hidden; });` (scope `SUndoHistoryTableRow::GenerateWidgetForColumn`)
- L118 _function_ `.OnClicked_Lambda([this]() { OnUndoBarrierButtonClicked.ExecuteIfBound(QueueIndex); return FReply::Handled(); }) .Visibility_Lambda([this]() { return (GEditor && (!GEditor->PlayWorld || GEditor->bIsSimulatingInEditor)) && this->IsHovered() && (IsCurrentUndoBarrier.Get() || IsLastTransactionIndex.Get()) ? EVisibility::Visible : EVisibility::Hidden; });` (scope `SUndoHistoryTableRow::GenerateWidgetForColumn`)
- L119 _function_ `.Visibility_Lambda([this]() { return (GEditor && (!GEditor->PlayWorld || GEditor->bIsSimulatingInEditor)) && this->IsHovered() && (IsCurrentUndoBarrier.Get() || IsLastTransactionIndex.Get()) ? EVisibility::Visible : EVisibility::Hidden; });` (scope `SUndoHistoryTableRow::GenerateWidgetForColumn`)

### `Source/Editor/UndoHistoryEditor/Public/IUndoHistoryEditorModule.h` (Public)


#### class `IUndoHistoryEditorModule`  
`class IUndoHistoryEditorModule : public IModuleInterface`  
_L11-21_
- inherits: `IModuleInterface`
- L15 _public function_ `static IUndoHistoryEditorModule& Get()`
- L20 _public prototype_ `virtual void ExecuteOpenUndoHistory() = 0;`

#### Free symbols / members of external scopes

- L9 _externvar_ `extern const FName UndoHistoryTabName;`
