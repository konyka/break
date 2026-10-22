# Editor / DataHierarchyEditor

- module root: `Source/Editor/DataHierarchyEditor`
- headers: 8; symbols: 628
- symbol kinds: class=17, delegate=15, enum=1, enumerator=4, function=168, macro=5, member=118, namespace=2, prototype=278, struct=20
- PrivateDependencyModuleNames: Engine, InputCore, Slate, ToolMenus, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, EditorWidgets, SlateCore

### `Source/Editor/DataHierarchyEditor/Internal/DataHierarchyEditorCommands.h` (Internal)


#### class `FDataHierarchyEditorCommands`  
`class FDataHierarchyEditorCommands : public TCommands<FDataHierarchyEditorCommands>`  
_L9-23_
- inherits: `TCommands<FDataHierarchyEditorCommands>`
- L13 _public function_ `FDataHierarchyEditorCommands() : TCommands<FDataHierarchyEditorCommands>( TEXT("DataHierarchyEditorCommands"), NSLOCTEXT("DataHierarchyEditorCommands", "Data Hierarchy Editor Commands", "Data Hierarchy Editor Commands"), NAME_None, "DataHierarchyEditorStyle" )`
- L18 _public prototype_ `virtual ~FDataHierarchyEditorCommands() override = default;`
- L20 _public prototype_ `virtual void RegisterCommands() override;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> FindInHierarchy;`

### `Source/Editor/DataHierarchyEditor/Internal/DataHierarchyEditorMisc.h` (Internal)


#### class `UDataHierarchyEditorMenuContext`  
`class UDataHierarchyEditorMenuContext : public UObject`  
_L17-23_
- reflection: `UCLASS()`
- inherits: `UObject`
- L22 _public member_ `TWeakPtr<SDataHierarchyEditor> Widget;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DataHierarchyEditor` (scope `UE`)
- L13 _prototype_ `FName GetUniqueName(FName CandidateName, const TSet<FName>& ExistingNames);` (scope `UE::DataHierarchyEditor`)

### `Source/Editor/DataHierarchyEditor/Internal/DataHierarchyEditorModule.h` (Internal)


#### class `FDataHierarchyEditorModule`  
`class FDataHierarchyEditorModule : public IModuleInterface`  
_L10-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataHierarchyEditor, Log, All) class FDataHierarchyEditorModule : public IModuleInterface { public: virtual void StartupModule() override; virtual void ShutdownModule() override; };`

### `Source/Editor/DataHierarchyEditor/Internal/DataHierarchyEditorStyle.h` (Internal)


#### class `FDataHierarchyEditorStyle`  
`class FDataHierarchyEditorStyle : public FSlateStyleSet`  
_L10-31_
- inherits: `FSlateStyleSet`
- desc: Manages the style which provides resources for Hierarchy Editor widgets.
- L13 _public prototype_ `static void Register();`
- L14 _public prototype_ `static void Unregister();`
- L15 _public prototype_ `static void Shutdown();`
- L18 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L21 _public prototype_ `static const FDataHierarchyEditorStyle& Get();` — @return The Slate style set for Hierarchy Editor widgets
- L23 _public prototype_ `static void ReinitializeStyle();`
- L26 _private prototype_ `FDataHierarchyEditorStyle();`
- L28 _private prototype_ `void InitDataHierarchyEditor();`
- L30 _private member_ `static TSharedPtr<FDataHierarchyEditorStyle> DataHierarchyEditorStyle;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DATAHIERARCHYEDITOR_API`

### `Source/Editor/DataHierarchyEditor/Internal/DataHierarchyElementCustomVersion.h` (Internal)


#### struct `FDataHierarchyElementCustomVersion`  
`struct FDataHierarchyElementCustomVersion`  
_L11-29_
- L25 _public member_ `const static FGuid Guid;` — The GUID for this custom version number
- L28 _private function_ `FDataHierarchyElementCustomVersion()`

#### enum `FDataHierarchyElementCustomVersion::Type`  
`enum Type`  
_L13-22_
- L15 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L17 _public enumerator_ `MetaDataIntroduction` — PostLoad moving hard coded section references on categories into the metadata system
- L20 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L21 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DATAHIERARCHYEDITOR_API`

### `Source/Editor/DataHierarchyEditor/Internal/Widgets/SDataHierarchyEditor.h` (Internal)


#### class `SHierarchySection`  
`class SHierarchySection : public SCompoundWidget`  
_L28-101_
- inherits: `SCompoundWidget`
- L30 _private function_ `DECLARE_DELEGATE_OneParam(FOnSectionActivated, TSharedPtr<FHierarchySectionViewModel> SectionViewModel) SLATE_BEGIN_ARGS(SHierarchySection)`
- L39 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<struct FHierarchySectionViewModel> InSection);`
- L42 _public prototype_ `void TryEnterEditingMode() const;`
- L44 _public prototype_ `TSharedPtr<struct FHierarchySectionViewModel> GetSectionViewModel();`
- L46 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L47 _private prototype_ `int32 PaintDropIndicator(const FPaintArgs& Args, const FGeometry& Geometry, FSlateRect SlateRect, FSlateWindowElementList& OutDrawElements, int32 INT32, const FWidgetStyle& WidgetStyle, bool bParentEnabled) const;`
- L48 _private prototype_ `int32 OnPaintDropIndicator(EItemDropZone ItemDropZone, const FPaintArgs& Args, const FGeometry& Geometry, FSlateRect SlateRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& WidgetStyle, bool bParentEnabled) const;`
- L50 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L51 _private prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L53 _private prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L55 _private prototype_ `bool OnCanAcceptDrop(TSharedPtr<FDragDropOperation> DragDropOperation, EItemDropZone ItemDropZone) const;`
- L56 _private prototype_ `FReply OnDroppedOn(const FGeometry&, const FDragDropEvent& DragDropEvent, EItemDropZone DropZone) const;`
- L58 _private prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L59 _private prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L60 _private prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L61 _private prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L63 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L65 _private prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L67 _private prototype_ `UHierarchySection* TryGetSectionData() const;`
- L69 _private prototype_ `const FSlateBrush* GetImageBrush() const;`
- L70 _private prototype_ `EVisibility GetImageVisibility() const;`
- L72 _private prototype_ `FText GetText() const;`
- L73 _private prototype_ `FText GetTooltipText() const;`
- L74 _private prototype_ `void OnRenameSection(const FText& Text, ETextCommit::Type CommitType) const;`
- L75 _private prototype_ `bool OnVerifySectionRename(const FText& NewName, FText& OutTooltip) const;`
- L77 _private prototype_ `bool IsSectionSelected() const;`
- L78 _private prototype_ `bool IsSectionReadOnly() const;`
- L79 _private prototype_ `ECheckBoxState GetSectionCheckState() const;`
- L80 _private prototype_ `void OnSectionCheckChanged(ECheckBoxState NewState);`
- L81 _private prototype_ `EActiveTimerReturnType ActivateSectionIfDragging(double CurrentTime, float DeltaTime) const;`
- L83 _private prototype_ `const FSlateBrush* GetDropIndicatorBrush(EItemDropZone ItemDropZone) const;`
- L86 _private prototype_ `EItemDropZone ZoneFromPointerPosition(UE::Slate::FDeprecateVector2DParameter LocalPointerPos, UE::Slate::FDeprecateVector2DParameter LocalSize);` — @return the zone (above, onto, below) based on where the user is hovering over within the row
- L89 _private member_ `TSharedPtr<SMenuAnchor> MenuAnchor;`
- L90 _private member_ `TSharedPtr<SCheckBox> CheckBox;`
- L91 _private member_ `TSharedPtr<SInlineEditableTextBlock> InlineEditableTextBlock;`
- L92 _private member_ `TWeakObjectPtr<UDataHierarchyViewModelBase> HierarchyViewModel;`
- L93 _private member_ `TWeakPtr<FHierarchySectionViewModel> SectionViewModelWeak;`
- L95 _private member_ `TAttribute<ECheckBoxState> IsSectionActive;`
- L96 _private member_ `FOnSectionActivated OnSectionActivatedDelegate;`
- L98 _private member_ `mutable bool bDraggedOn = false;`
- L100 _private member_ `mutable TOptional<EItemDropZone> CurrentItemDropZone;`

#### class `SDataHierarchyEditor`  
`class SDataHierarchyEditor : public SCompoundWidget, public FNotifyHook`  
_L103-269_
- inherits: `SCompoundWidget,FNotifyHook`
- L105 _private prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnGenerateRowContentWidget, TSharedRef<FHierarchyElementViewModel> HierarchyElement);`
- L106 _private prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnGenerateCustomDetailsPanelNameWidget, TSharedPtr<FHierarchyElementViewModel> HierarchyElement);`
- L108 _private function_ `SLATE_BEGIN_ARGS(SDataHierarchyEditor) : _bReadOnly(true)`
- L117 _public prototype_ `void Construct(const FArguments& InArgs, TObjectPtr<UDataHierarchyViewModelBase> InHierarchyViewModel);`
- L120 _public prototype_ `void RefreshSourceItems();`
- L121 _public prototype_ `void RefreshAllViews(bool bFullRefresh = false);`
- L122 _public prototype_ `void RequestRefreshAllViewsNextFrame(bool bFullRefresh = false);`
- L123 _public prototype_ `void RefreshSourceView(bool bFullRefresh = false) const;`
- L124 _public prototype_ `void RequestRefreshSourceViewNextFrame(bool bFullRefresh = false);`
- L125 _public prototype_ `void RefreshHierarchyView(bool bFullRefresh = false) const;`
- L126 _public prototype_ `void RequestRefreshHierarchyViewNextFrame(bool bFullRefresh = false);`
- L127 _public prototype_ `void RefreshSectionsView();`
- L128 _public prototype_ `void RequestRefreshSectionsViewNextFrame();`
- L130 _public prototype_ `void NavigateToHierarchyElement(FHierarchyElementIdentity Identity) const;`
- L131 _public prototype_ `void NavigateToHierarchyElement(TSharedPtr<FHierarchyElementViewModel> Item) const;`
- L132 _public prototype_ `bool IsItemSelected(TSharedPtr<FHierarchyElementViewModel> Item) const;`
- L136 _private function_ `virtual bool SupportsKeyboardFocus() const override` — need to do this to enable focus so we can handle shortcuts
- L138 _private prototype_ `TSharedRef<ITableRow> GenerateSourceItemRow(TSharedPtr<FHierarchyElementViewModel> HierarchyItem, const TSharedRef<STableViewBase>& TableViewBase);`
- L139 _private prototype_ `TSharedRef<ITableRow> GenerateHierarchyItemRow(TSharedPtr<FHierarchyElementViewModel> HierarchyItem, const TSharedRef<STableViewBase>& TableViewBase);`
- L141 _private prototype_ `bool FilterForSourceSection(TSharedPtr<const FHierarchyElementViewModel> ItemViewModel) const;`
- L143 _private prototype_ `void Reinitialize();`
- L145 _private prototype_ `void BindToHierarchyRootViewModel();`
- L146 _private prototype_ `void UnbindFromHierarchyRootViewModel() const;`
- L149 _private prototype_ `const TArray<TSharedPtr<FHierarchyElementViewModel>>& GetSourceItems() const;` — Source items reflect the base, unedited status of items to edit into a hierarchy
- L151 _private prototype_ `bool IsDetailsPanelEditingAllowed() const;`
- L153 _private prototype_ `void ClearSourceItems() const;`
- L155 _private prototype_ `void RequestRenameSelectedItem();`
- L156 _private prototype_ `bool CanRequestRenameSelectedItem() const;`
- L158 _private prototype_ `void DeleteItems(TArray<TSharedPtr<FHierarchyElementViewModel>> ItemsToDelete) const;`
- L159 _private prototype_ `void DeleteSelectedHierarchyItems() const;`
- L160 _private prototype_ `bool CanDeleteSelectedElements() const;`
- L162 _private prototype_ `void NavigateToMatchingHierarchyElementFromSelectedSourceElement() const;`
- L163 _private prototype_ `bool CanNavigateToMatchingHierarchyElementFromSelectedSourceElement() const;`
- L165 _private prototype_ `void OnHierarchySectionActivated(TSharedPtr<FHierarchySectionViewModel> Section);`
- L166 _private prototype_ `void OnSourceSectionActivated(TSharedPtr<FHierarchySectionViewModel> Section);`
- L167 _private prototype_ `void OnHierarchySectionAdded(TSharedPtr<FHierarchySectionViewModel> AddedSection);`
- L168 _private prototype_ `void OnHierarchySectionDeleted(TSharedPtr<FHierarchySectionViewModel> DeletedSection);`
- L170 _private prototype_ `void SetActiveSourceSection(TSharedPtr<struct FHierarchySectionViewModel>);`
- L171 _private prototype_ `TSharedPtr<FHierarchySectionViewModel> GetActiveSourceSection() const;`
- L172 _private prototype_ `UHierarchySection* GetActiveSourceSectionData() const;`
- L174 _private prototype_ `TSharedRef<SWidget> OnGetCustomAddContent();`
- L176 _private prototype_ `void OnSelectionChanged(TSharedPtr<FHierarchyElementViewModel> SelectedHierarchyElement, ESelectInfo::Type Type) const;`
- L178 _private prototype_ `void RunSourceSearch();`
- L179 _private prototype_ `void OnSourceSearchTextChanged(const FText& Text);`
- L180 _private prototype_ `void OnSourceSearchTextCommitted(const FText& Text, ETextCommit::Type CommitType);`
- L181 _private prototype_ `void OnSearchButtonClicked(SSearchBox::SearchDirection SearchDirection);`
- L183 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L184 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L185 _private prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L187 _private prototype_ `FReply OnHierarchyRowDragDetected(TSharedRef<FHierarchyElementViewModel> DraggedRow, const FGeometry& Geometry, const FPointerEvent& PointerEvent);`
- L188 _private prototype_ `FReply OnSourceRowDragDetected(TSharedRef<FHierarchyElementViewModel> DraggedRow, const FGeometry& Geometry, const FPointerEvent& PointerEvent);`
- L189 _private prototype_ `FReply HandleMultiDragDetected(const TArray<TSharedPtr<FHierarchyElementViewModel>>& ItemsToDrag, bool bIsSource);`
- L191 _private prototype_ `FReply OnAddCategoryClicked() const;`
- L192 _private prototype_ `FReply OnAddSectionClicked() const;`
- L194 _private prototype_ `TSharedPtr<SWidget> SummonContextMenuForSelectedRows(bool bFromHierarchy) const;`
- L214 _private prototype_ `void GenerateSearchItems(TSharedRef<FHierarchyElementViewModel> Root, TArray<TSharedPtr<FHierarchyElementViewModel>> ParentChain, TArray<FSearchItem>& OutSearchItems);` — This will recursively generated parent chain paths for all items within the given root. Used for expansion purposes.
- L215 _private prototype_ `void ExpandSourceSearchResults();`
- L216 _private prototype_ `void SelectNextSourceSearchResult();`
- L217 _private prototype_ `void SelectPreviousSourceSearchResult();`
- L218 _private prototype_ `TOptional<SSearchBox::FSearchResultData> GetSearchResultData() const;`
- L220 _private prototype_ `void ExpandEntriesByDefault(TSharedPtr<STreeView<TSharedPtr<FHierarchyElementViewModel>>> TreeView) const;`
- L223 _private prototype_ `void SaveExpansionState(TSharedPtr<STreeView<TSharedPtr<FHierarchyElementViewModel>>> TreeView) const;` — Saves the expansion state of all items in the given tree view, keyed by FHierarchyElementIdentity when available, falling back to TObjectKey.
- L225 _private prototype_ `void RestoreExpansionState(TSharedPtr<STreeView<TSharedPtr<FHierarchyElementViewModel>>> TreeView) const;` — Restores previously saved expansion state. Items not in the saved state fall back to IsExpandedByDefault().
- L227 _private prototype_ `FHierarchyElementViewModel::FResultWithUserFeedback CanDropOnRoot(TSharedPtr<FHierarchyElementViewModel> DraggedItem) const;`
- L230 _private prototype_ `FReply HandleHierarchyRootDrop(const FGeometry&, const FDragDropEvent& DragDropEvent) const;` — Callback functions for the root widget
- L231 _private prototype_ `bool OnCanDropOnRoot(TSharedPtr<FDragDropOperation> DragDropOperation) const;`
- L232 _private prototype_ `void OnRootDragEnter(const FDragDropEvent& DragDropEvent) const;`
- L233 _private prototype_ `void OnRootDragLeave(const FDragDropEvent& DragDropEvent) const;`
- L234 _private prototype_ `FSlateColor GetRootIconColor() const;`
- L236 _private prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L240 _private member_ `TWeakObjectPtr<UDataHierarchyViewModelBase> HierarchyViewModel;` — A weak pointer to the hierarchy view model. An external view model created and managed by the implementer.
- L241 _private member_ `TArray<FSearchItem> SourceSearchResults;`
- L242 _private member_ `TOptional<FSearchItem> FocusedSearchResult;`
- L244 _private member_ `mutable TArray<TWeakPtr<FHierarchyElementViewModel>> SelectedDetailsPanelItemViewModels;`
- L245 _private member_ `mutable bool bIsUpdatingSelection = false;`
- L248 _private member_ `TStrongObjectPtr<UHierarchyRoot> SourceRoot;`
- L249 _private member_ `TSharedPtr<FHierarchyRootViewModel> SourceRootViewModel;`
- L250 _private member_ `TSharedPtr<STreeView<TSharedPtr<FHierarchyElementViewModel>>> SourceTreeView;`
- L251 _private member_ `TSharedPtr<STreeView<TSharedPtr<FHierarchyElementViewModel>>> HierarchyTreeView;`
- L252 _private member_ `TStrongObjectPtr<UHierarchySection> AllSourceSection;`
- L253 _private member_ `TSharedPtr<FHierarchySectionViewModel> DefaultSourceSectionViewModel;`
- L254 _private member_ `TWeakPtr<struct FHierarchySectionViewModel> ActiveSourceSection;`
- L255 _private member_ `TSharedPtr<class SWrapBox> SourceSectionBox;`
- L256 _private member_ `TSharedPtr<class SWrapBox> HierarchySectionBox;`
- L257 _private member_ `TSharedPtr<SSearchBox> SourceSearchBox;`
- L258 _private member_ `TSharedPtr<IDetailsView> DetailsPanel;`
- L260 _private member_ `FOnGenerateRowContentWidget OnGenerateRowContentWidget;`
- L261 _private member_ `FOnGenerateCustomDetailsPanelNameWidget OnGenerateCustomDetailsPanelNameWidget;`
- L262 _private member_ `TSharedPtr<FActiveTimerHandle> RefreshHierarchyViewNextFrameHandle;`
- L263 _private member_ `TSharedPtr<FActiveTimerHandle> RefreshSourceViewNextFrameHandle;`
- L264 _private member_ `TSharedPtr<FActiveTimerHandle> RefreshSectionsViewNextFrameHandle;`
- L267 _private member_ `mutable TMap<FHierarchyElementIdentity, bool> SavedExpansionByIdentity;` — Saved expansion state. Uses FHierarchyElementIdentity when available, falls back to TObjectKey for elements without a valid identity.
- L268 _private member_ `mutable TMap<TObjectKey<const UHierarchyElement>, bool> SavedExpansionByObjectKey;`

#### struct `SDataHierarchyEditor::FSearchItem`  
`struct FSearchItem`  
_L196-211_
- L198 _public member_ `TArray<TSharedPtr<FHierarchyElementViewModel>> Path;`
- L200 _public function_ `TSharedPtr<FHierarchyElementViewModel> GetEntry() const`
- L207 _public function_ `bool operator==(const FSearchItem& Item) const`

#### class `SHierarchyElement`  
`class SHierarchyElement : public SCompoundWidget`  
_L271-293_
- inherits: `SCompoundWidget`
- L273 _private function_ `SLATE_BEGIN_ARGS(SHierarchyElement) : _Style(&FCoreStyle::Get().GetWidgetStyle<FInlineEditableTextBlockStyle>("InlineEditableTextBlockStyle") )`
- L281 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<struct FHierarchyElementViewModel> InViewModel);`
- L283 _public prototype_ `void EnterEditingMode() const;`
- L284 _public prototype_ `bool OnVerifyRename(const FText& NewName, FText& OutTooltip) const;`
- L286 _public prototype_ `FText GetElementText() const;`
- L287 _public prototype_ `void OnRenameElement(const FText& NewText, ETextCommit::Type) const;`
- L289 _public prototype_ `FText GetTooltipText() const;`
- L291 _private member_ `TWeakPtr<struct FHierarchyElementViewModel> ElementViewModelWeak;`
- L292 _private member_ `TSharedPtr<SInlineEditableTextBlock> InlineEditableTextBlock;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API DATAHIERARCHYEDITOR_API`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSectionActivated, TSharedPtr<FHierarchySectionViewModel> SectionViewModel) SLATE_BEGIN_ARGS(SHierarchySection) {} SLATE_ATTRIBUTE(ECheckBoxState, IsSectionActive) SLATE_EVENT(FOnSectionActivated, OnSectionActivated) SLATE_END_ARGS() public: void Construct(const FArguments& InArgs, TSharedPtr<struct FHierarchySectionViewModel> InSection);`
- L105 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnGenerateRowContentWidget, TSharedRef<FHierarchyElementViewModel> HierarchyElement);`
- L106 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnGenerateCustomDetailsPanelNameWidget, TSharedPtr<FHierarchyElementViewModel> HierarchyElement);`

### `Source/Editor/DataHierarchyEditor/Public/DataHierarchyCommonTypes.h` (Public)


#### struct `FHierarchyElementIdentity`  
`struct FHierarchyElementIdentity`  
_L12-62_
- reflection: `USTRUCT()`
- desc: This struct is used to identify a given hierarchy element and can be based on guids and/or names. This is particularly useful when a hierarchy element represents an object or a property that is not owned by the hierarchy itself.
- L16 _public function_ `FHierarchyElementIdentity()`
- L17 _public function_ `FHierarchyElementIdentity(TArray<FGuid> InGuids, TArray<FName> InNames) : Guids(InGuids), Names(InNames)`
- L21 _public member_ `TArray<FGuid> Guids;` — `UPROPERTY()` — An array of guids that have to be satisfied in order to match.
- L25 _public member_ `TArray<FName> Names;` — `UPROPERTY()` — Optionally, an array of names can be specified in place of guids. If guids & names are present, guids have to be satisfied first, then names.
- L27 _public function_ `bool IsValid() const`
- L32 _public function_ `bool operator==(const FHierarchyElementIdentity& OtherIdentity) const`
- L58 _public function_ `bool operator!=(const FHierarchyElementIdentity& OtherIdentity) const`

#### struct `FDataHierarchyElementMetaData`  
`struct FDataHierarchyElementMetaData`  
_L82-87_
- reflection: `USTRUCT()`
- L86 _public function_ `FDataHierarchyElementMetaData()`

#### struct `FDataHierarchyElementMetaData_SectionAssociation`  
`struct FDataHierarchyElementMetaData_SectionAssociation : public FDataHierarchyElementMetaData`  
_L90-98_
- reflection: `USTRUCT()`
- inherits: `FDataHierarchyElementMetaData`
- L94 _public function_ `FDataHierarchyElementMetaData_SectionAssociation()`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DATAHIERARCHYEDITOR_API`
- L64 _function_ `FORCEINLINE uint32 GetTypeHash(const FHierarchyElementIdentity& Identity)`

### `Source/Editor/DataHierarchyEditor/Public/DataHierarchyViewModelBase.h` (Public)


#### class `UHierarchyDataRefreshContext`  
`class UHierarchyDataRefreshContext : public UObject`  
_L69-72_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UObject`
- desc: A base class that is used to refresh data that represents external data. Inherit from this class if you need more context data.

#### class `UHierarchyElement`  
`class UHierarchyElement : public UObject`  
_L75-159_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L80 _public prototype_ `UHierarchyElement();`
- L81 _public prototype_ `virtual ~UHierarchyElement() override = default;`
- L83 _public prototype_ `TConstArrayView<const TObjectPtr<UHierarchyElement>> GetChildren() const;`
- L84 _public function_ `TArray<TObjectPtr<UHierarchyElement>>& GetChildrenMutable()`
- L87 _public prototype_ `template<class ChildClass> ChildClass* AddChild();`
- L90 _public prototype_ `template<class ChildClass> ChildClass* AddChild(TSubclassOf<UHierarchyElement> Class, int32 InsertIndex = INDEX_NONE);`
- L92 _public prototype_ `UHierarchyElement* FindChildWithIdentity(FHierarchyElementIdentity ChildIdentity, bool bSearchRecursively = false);`
- L94 _public prototype_ `UHierarchyElement* CopyAndAddItemAsChild(const UHierarchyElement& ItemToCopy);`
- L95 _public prototype_ `UHierarchyElement* CopyAndAddItemUnderParentIdentity(const UHierarchyElement& ItemToCopy, FHierarchyElementIdentity ParentIdentity);`
- L98 _public prototype_ `bool RemoveChildWithIdentity(FHierarchyElementIdentity ChildIdentity, bool bSearchRecursively = false);` — Remove a child with a given identity. Can be searched recursively. This function operates under the assumption there will be only one item with a given identity.
- L101 _public prototype_ `template<class ChildClass> bool DoesOneChildExist(bool bRecursive = false) const;`
- L104 _public prototype_ `template<class ChildClass> void GetChildrenOfType(TArray<ChildClass*>& Out, bool bRecursive = false) const;`
- L107 _public prototype_ `template<class PREDICATE_CLASS> void SortChildren(const PREDICATE_CLASS& Predicate, bool bRecursive = false);`
- L110 _public prototype_ `template<class PREDICATE_CLASS> void StableSortChildren(const PREDICATE_CLASS& Predicate, bool bRecursive = false);`
- L112 _public function_ `virtual FString ToString() const`
- L113 _public function_ `FText ToText() const`
- L116 _public function_ `void SetIdentity(FHierarchyElementIdentity InIdentity)` — An identity can be optionally set to create a mapping from previously existing guids or names to hierarchy items that represent them.
- L117 _public function_ `FHierarchyElementIdentity GetPersistentIdentity() const`
- L118 _public prototype_ `TArray<FHierarchyElementIdentity> GetParentIdentities() const;`
- L119 _public prototype_ `TArray<const TObjectPtr<UHierarchyElement>> GetParentElements() const;`
- L122 _public prototype_ `virtual bool Modify(bool bAlwaysMarkDirty = true) override;` — Overridden modify method to also mark all children as modified
- L125 _public prototype_ `template<typename T> bool HasMetaDataOfType();`
- L128 _public prototype_ `template<typename T> const T* FindMetaDataOfType() const;`
- L131 _public prototype_ `template<typename T> T* FindMetaDataOfType();`
- L134 _public prototype_ `template<typename T> T FindMetaDataOfTypeOrDefault() const;`
- L137 _public prototype_ `template<typename T> T* FindOrAddMetaDataOfType();`
- L140 _public prototype_ `template <typename T> bool DeleteMetaDataOfType();`
- L143 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L144 _protected prototype_ `virtual void PostLoad() override;`
- L147 _protected member_ `TArray<TObjectPtr<UHierarchyElement>> Children;` — `UPROPERTY()`
- L150 _protected member_ `FHierarchyElementIdentity Identity;` — `UPROPERTY()`
- L154 _protected member_ `TMap<TObjectPtr<UStruct>, TInstancedStruct<FDataHierarchyElementMetaData>> MetaData;` — `UPROPERTY()` — A map of metadata. Can be used for anything; an example of this is section association.
- L158 _protected member_ `FGuid Guid_DEPRECATED;` — `UPROPERTY()` — An optional guid; can be used if hierarchy items represent outside items
- L162 _function_ `template <class ChildClass> ChildClass* UHierarchyElement::AddChild()`
- L173 _function_ `template <class ChildClass> ChildClass* UHierarchyElement::AddChild(TSubclassOf<UHierarchyElement> Class, int32 InsertIndex)`
- L191 _function_ `template <class ChildClass> bool UHierarchyElement::DoesOneChildExist(bool bRecursive) const`
- L216 _function_ `template <class ChildClass> void UHierarchyElement::GetChildrenOfType(TArray<ChildClass*>& Out, bool bRecursive) const`
- L236 _function_ `template <class PREDICATE_CLASS> void UHierarchyElement::SortChildren(const PREDICATE_CLASS& Predicate, bool bRecursive)`
- L250 _function_ `template <class PREDICATE_CLASS> void UHierarchyElement::StableSortChildren(const PREDICATE_CLASS& Predicate, bool bRecursive)`
- L264 _function_ `template <typename T> bool UHierarchyElement::HasMetaDataOfType()`
- L272 _function_ `template <typename T> const T* UHierarchyElement::FindMetaDataOfType() const`
- L285 _function_ `template <typename T> T* UHierarchyElement::FindMetaDataOfType()`
- L298 _function_ `template <typename T> T UHierarchyElement::FindMetaDataOfTypeOrDefault() const`
- L312 _function_ `template <typename T> T* UHierarchyElement::FindOrAddMetaDataOfType()`
- L325 _function_ `template <typename T> bool UHierarchyElement::DeleteMetaDataOfType()`

#### class `UHierarchySection`  
`class UHierarchySection : public UHierarchyElement`  
_L339-363_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UHierarchyElement`
- desc: A minimal implementation of a section.
- L344 _public function_ `UHierarchySection()`
- L346 _public function_ `void SetSectionName(FName InSectionName)`
- L347 _public function_ `FName GetSectionName() const`
- L349 _public prototype_ `void SetSectionNameAsText(const FText& Text);`
- L350 _public function_ `FText GetSectionNameAsText() const`
- L352 _public function_ `void SetTooltip(const FText& InTooltip)`
- L353 _public function_ `FText GetTooltip() const`
- L355 _public function_ `virtual FString ToString() const override`
- L358 _private member_ `FName Section;` — `UPROPERTY()`
- L362 _private member_ `FText Tooltip;` — `UPROPERTY(EditAnywhere, Category = "Section", meta = (MultiLine = "true"))` — The tooltip used when the user is hovering this section

#### class `UHierarchyRoot`  
`class UHierarchyRoot : public UHierarchyElement`  
_L367-392_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UHierarchyElement`
- desc: UHierarchyRoot is used as the main object for serialization purposes, and a transient root is created automatically by the widget to populate the source list of items.
- L371 _public function_ `UHierarchyRoot()`
- L372 _public prototype_ `virtual ~UHierarchyRoot() override = default;`
- L374 _public function_ `TConstArrayView<const TObjectPtr<UHierarchySection>> GetSectionData() const`
- L375 _public function_ `TArray<TObjectPtr<UHierarchySection>>& GetSectionDataMutable()`
- L377 _public prototype_ `TSet<FName> GetSectionNames() const;`
- L378 _public prototype_ `int32 GetSectionIndex(UHierarchySection* Section) const;`
- L380 _public prototype_ `UHierarchySection* FindSectionByIdentity(FHierarchyElementIdentity SectionIdentity);`
- L382 _public prototype_ `void DuplicateSectionFromOtherRoot(const UHierarchySection& SectionToCopy);` — This will copy the section element itself
- L384 _public prototype_ `virtual void EmptyAllData();`
- L386 _public prototype_ `virtual bool Modify(bool bAlwaysMarkDirty = true) override;`
- L388 _protected prototype_ `virtual void Serialize(FStructuredArchive::FRecord Record) override;`
- L391 _protected member_ `TArray<TObjectPtr<UHierarchySection>> Sections;` — `UPROPERTY()`

#### class `UHierarchyItem`  
`class UHierarchyItem : public UHierarchyElement`  
_L396-402_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UHierarchyElement`
- desc: A minimal implementation of an item. Inherit from this and add your own properties.
- L400 _public function_ `UHierarchyItem()`
- L401 _public prototype_ `virtual ~UHierarchyItem() override = default;`

#### class `UHierarchyCategory`  
`class UHierarchyCategory : public UHierarchyElement`  
_L407-437_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UHierarchyElement`
- desc: A category, potentially pointing at the section it belongs to. Only top-level categories can belong to sections by default. Inherit from this to add your own properties.
- L411 _public function_ `UHierarchyCategory()`
- L412 _public function_ `UHierarchyCategory(FName InCategory) : Category(InCategory)`
- L414 _public function_ `void SetCategoryName(FName NewCategory)`
- L415 _public function_ `FName GetCategoryName() const`
- L417 _public function_ `FText GetCategoryAsText() const`
- L418 _public function_ `FText GetTooltip() const`
- L420 _public function_ `virtual FString ToString() const override`
- L422 _public prototype_ `static FHierarchyElementIdentity ConstructIdentity();`
- L425 _protected prototype_ `virtual void PostLoad() override;`
- L429 _private member_ `FName Category;` — `UPROPERTY()`
- L433 _private member_ `FText Tooltip;` — `UPROPERTY(EditAnywhere, Category = "Category", meta = (MultiLine = "true"))` — The tooltip used when the user is hovering this category
- L436 _private member_ `TObjectPtr<UHierarchySection> Section_DEPRECATED = nullptr;` — `UPROPERTY()`

#### struct `FDraggedElementEntry`  
`struct FDraggedElementEntry`  
_L443-449_
- desc: Entry wrapping a dragged element view model with computed context about its role in a multi-drag set.
- L445 _public member_ `TWeakPtr<FHierarchyElementViewModel> Element;`
- L448 _public member_ `bool bIsContainedInAnotherDraggedElement = false;` — True if this element is a descendant of another element in the same drag set. When true, drop execution should skip this entry -- the parent's drop already includes it.

#### struct `FDataHierarchyDragDropContext`  
`struct FDataHierarchyDragDropContext`  
_L452-474_
- desc: Context for a hierarchy drag-and-drop operation. Wraps the set of dragged elements with computed hierarchy metadata.
- L454 _public prototype_ `FDataHierarchyDragDropContext() = default;`
- L455 _public prototype_ `~FDataHierarchyDragDropContext();`
- L456 _public prototype_ `explicit FDataHierarchyDragDropContext(const TArray<FDraggedElementEntry>& InEntries);`
- L457 _public prototype_ `explicit FDataHierarchyDragDropContext(TArray<FDraggedElementEntry>&& InEntries);`
- L460 _public prototype_ `const TArray<FDraggedElementEntry>& GetEntries() const;` — All dragged element entries, including those contained in other dragged elements.
- L463 _public prototype_ `TArray<FDraggedElementEntry> GetTopLevelEntries() const;` — Returns only top-level entries (not contained in another dragged element).
- L465 _public prototype_ `int32 GetTopLevelCount() const;` — Returns the number of top-level dragged elements.
- L468 _public prototype_ `TWeakPtr<FHierarchyElementViewModel> GetPrimaryElement() const;` — Returns the first/primary dragged element.
- L470 _public prototype_ `int32 Num() const;`
- L471 _public prototype_ `bool IsEmpty() const;`
- L473 _private member_ `TArray<FDraggedElementEntry> Entries;`

#### class `FHierarchyDragDropOp`  
`class FHierarchyDragDropOp : public FDragDropOperation`  
_L477-512_
- inherits: `FDragDropOperation`
- desc: Inherit from this to allow UI customization for your drag & drop operation by overriding CreateCustomDecorator.
- L480 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FHierarchyDragDropOp, FDragDropOperation) FHierarchyDragDropOp(const FDataHierarchyDragDropContext& InDragContext);`
- L484 _public function_ `virtual void Construct() override`
- L485 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override final;`
- L488 _public function_ `virtual TSharedRef<SWidget> CreateCustomDecorator() const` — Override this custom decorator function to provide custom widget visuals. If not specified, you can still use Label and Description.
- L491 _public function_ `TWeakPtr<FHierarchyElementViewModel> GetDraggedElement() const` — Returns the first/primary dragged element.
- L493 _public function_ `const FDataHierarchyDragDropContext& GetDragContext() const` — Returns the full drag context.
- L495 _public function_ `void SetLabel(FText InText)`
- L496 _public function_ `FText GetLabel() const`
- L498 _public function_ `void SetDescription(FText InText)`
- L499 _public function_ `FText GetDescription() const`
- L501 _public function_ `void SetFromSourceList(bool bInFromSourceList)`
- L502 _public function_ `bool GetIsFromSourceList() const`
- L504 _protected member_ `FDataHierarchyDragDropContext DragContext;`
- L507 _protected member_ `FText Label;` — Label will be displayed if no custom decorator has been specified.
- L509 _protected member_ `FText Description;` — Useful for runtime tweaking of the tooltip based on what we are hovering. Always displayed if not-empty
- L511 _protected member_ `bool bFromSourceList = false;` — If the drag drop op is from the source list, we can further customize the actions

#### class `UHierarchyMenuContext`  
`class UHierarchyMenuContext : public UObject`  
_L515-522_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L520 _public member_ `TWeakObjectPtr<class UDataHierarchyViewModelBase> HierarchyViewModel;`
- L521 _public member_ `TArray<TSharedPtr<FHierarchyElementViewModel>> MenuHierarchyElements;`

#### struct `FHierarchyChangedPayload`  
`struct FHierarchyChangedPayload`  
_L526-535_
- reflection: `USTRUCT()`
- desc: Generic payload struct for when an element in the hierarchy has changed.
- L530 _public prototype_ `FHierarchyChangedPayload() = default;`
- L531 _public function_ `FHierarchyChangedPayload(FString InMessage) : Message(InMessage)`
- L534 _public member_ `FString Message;` — An optional message that can be set.

#### struct `FHierarchyChangedPayload_ElementsAdded`  
`struct FHierarchyChangedPayload_ElementsAdded : public FHierarchyChangedPayload`  
_L538-543_
- reflection: `USTRUCT()`
- inherits: `FHierarchyChangedPayload`
- L542 _public member_ `TArray<TSharedPtr<FHierarchyElementViewModel>> AddedElementViewModels;`

#### struct `FHierarchyChangedPayload_ElementsMoved`  
`struct FHierarchyChangedPayload_ElementsMoved : public FHierarchyChangedPayload`  
_L546-551_
- reflection: `USTRUCT()`
- inherits: `FHierarchyChangedPayload`
- L550 _public member_ `TArray<TSharedPtr<FHierarchyElementViewModel>> MovedElementViewModels;`

#### struct `FHierarchyChangedPayload_ElementsDeleted`  
`struct FHierarchyChangedPayload_ElementsDeleted : public FHierarchyChangedPayload`  
_L554-559_
- reflection: `USTRUCT()`
- inherits: `FHierarchyChangedPayload`
- L558 _public member_ `TArray<TSharedPtr<FHierarchyElementViewModel>> DeletedElementViewModels;`

#### struct `FHierarchyChangedPayload_ElementPropertyChanged`  
`struct FHierarchyChangedPayload_ElementPropertyChanged : public FHierarchyChangedPayload`  
_L562-569_
- reflection: `USTRUCT()`
- inherits: `FHierarchyChangedPayload`
- L566 _public member_ `TSharedPtr<FHierarchyElementViewModel> ElementViewModel;`
- L567 _public member_ `const FPropertyChangedEvent* PropertyChangedEvent = nullptr;`
- L568 _public member_ `FProperty* PropertyThatChanged = nullptr;`

#### struct `FHierarchyChangedPayload_ElementNameChanged`  
`struct FHierarchyChangedPayload_ElementNameChanged : public FHierarchyChangedPayload`  
_L572-579_
- reflection: `USTRUCT()`
- inherits: `FHierarchyChangedPayload`
- L576 _public member_ `TSharedPtr<FHierarchyElementViewModel> ElementViewModel;`
- L577 _public member_ `FName OldName;`
- L578 _public member_ `FName NewName;`

#### class `UDataHierarchyViewModelBase`  
`class UDataHierarchyViewModelBase : public UObject, public FSelfRegisteringEditorUndoClient`  
_L584-789_
- reflection: `UCLASS(MinimalAPI, Abstract, Transient)`
- inherits: `UObject,FSelfRegisteringEditorUndoClient`
- desc: The main controller class for the SHierarchyEditor widget. Defines core hierarchy rules. Inherit from this and override the required virtual functions, instantiate an object, Initialize it and pass it to the SHierarchyEditor widget.
- L587 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHierarchyChanged, const TInstancedStruct<FHierarchyChangedPayload>&) DECLARE_DELEGATE_OneParam(FOnSectionActivated, TSharedPtr<FHierarchySectionViewModel> Section) DECLARE_DELEGATE_OneParam(FOnRefreshViewRequested, bool bForceFullRefresh) DECLARE_DELEGATE_OneParam(FOnNavigateToElementIdentityInHierarchyRequested, FHierarchyElementIdentity Identity) DECLARE_DELEGATE_OneParam(FOnNavigateToElementInHierarchyRequested, TSharedPtr<FHierarchyElementViewModel> ElementViewModel) GENERATED_BODY() UDataHierarchyViewModelBase();`
- L599 _public prototype_ `void Initialize();` — Initialize is called automatically for you, but it is recommended to call it manually after creating the HierarchyViewModel in your own Initialize function. This lets you access external data.
- L601 _public prototype_ `void Finalize();` — Call Finalize manually when you no longer need the HierarchyViewModel.
- L603 _public function_ `bool IsInitialized() const`
- L604 _public function_ `bool IsFinalized() const`
- L605 _public function_ `bool IsValid() const`
- L607 _public prototype_ `FName GetContextMenuName () const;`
- L610 _public prototype_ `TSharedPtr<FHierarchyElementViewModel> CreateViewModelForElement(UHierarchyElement* Element, TSharedPtr<FHierarchyElementViewModel> Parent);` — Creates view model hierarchy elements. To create custom view models, override CreateCustomViewModelForElement.
- L612 _public function_ `TSharedPtr<struct FHierarchyRootViewModel> GetHierarchyRootViewModel() const` — Get the root view model associated with the hierarchy.
- L615 _public prototype_ `const TArray<TSharedPtr<FHierarchyElementViewModel>>& GetHierarchyItems() const;` — Hierarchy items reflect the already edited hierarchy. This should generally be constructed from persistent serialized data.
- L617 _public function_ `TSharedPtr<struct FHierarchySectionViewModel> GetDefaultHierarchySectionViewModel() const`
- L620 _public prototype_ `virtual UHierarchyRoot* GetHierarchyRoot() const PURE_VIRTUAL(UDataHierarchyViewModelBase::GetHierarchyRoot, return nullptr;);` — The hierarchy root the widget is editing. This should point to persistent data stored somewhere else as the serialized root of the hierarchy.
- L624 _public function_ `virtual void PrepareSourceItems(UHierarchyRoot* SourceRoot, TSharedPtr<FHierarchyRootViewModel> SourceRootViewModel)` — Prepares the items we want to create a hierarchy for. Primary purpose is to add children to the source root to gather the items to display in the source panel. The root view model is also given as a way to forcefully sync view models to access additional functionality, if needed. Only used if UsesSourceItems is true.
- L627 _public prototype_ `virtual void OnHierarchyChanged(const TInstancedStruct<FHierarchyChangedPayload>& Payload);` — Generic callback for when something in the hierarchy has changed.
- L630 _public function_ `virtual TArray<TSubclassOf<UHierarchyElement>> GetAdditionalTypesToAddInUi() const` — If specified, will add a button in the Data Hierarchy Editor that allows adding the given types from a menu rather than drag & dropping them into the hierarchy.
- L633 _public function_ `virtual UObject* GetOuterForSourceRoot() const` — The outer for the transient source root creation can be overridden.
- L636 _public prototype_ `virtual TSubclassOf<UHierarchyCategory> GetCategoryDataClass() const;` — The class used for creating categories. You can subclass UHierarchyCategory to add new properties.
- L639 _public prototype_ `virtual TSubclassOf<UHierarchySection> GetSectionDataClass() const;` — The class used for creating sections. You can subclass UHierarchySection to add new properties.
- L641 _public prototype_ `virtual TSharedRef<FHierarchyDragDropOp> CreateDragDropOp(const FDataHierarchyDragDropContext& DragContext);` — Function to implement drag drop ops. FHierarchyDragDropOp is a default implementation. Inherit from it and override CreateCustomDecorator for custom UI.
- L643 _public function_ `virtual bool SupportsDetailsPanel()` — This needs to return true if you want the details panel to show up.
- L645 _public function_ `virtual bool SupportsMultiEditInDetailsPanel()` — If true, selecting multiple elements will show a multi-object details panel. If false, only the last selected element is shown.
- L648 _public function_ `virtual bool SupportsSourcePanel() const` — If false, disables source item functionality (left panel).
- L651 _public function_ `virtual ESelectionMode::Type GetHierarchySelectionMode() const` — The selection mode used for the hierarchy tree view. Override to change the default multi-selection behavior.
- L654 _public function_ `virtual bool SelectRootInsteadOfNone() const` — Attempts to select the root object when no object is selected. Can be used in conjunction with `GetObjectForEditing' to point at external objects.
- L657 _public function_ `virtual TArray<TTuple<UClass*, FOnGetDetailCustomizationInstance>> GetInstanceCustomizations()` — Overriding this allows to define details panel instance customizations for specific UClasses
- L661 _protected function_ `virtual void SetupCommands()` — Additional commands can be specified overriding the SetupCommands function.
- L664 _private function_ `virtual void InitializeInternal()` — Lets you add some additional logic to the Initialize function.
- L665 _private function_ `virtual void FinalizeInternal()`
- L668 _private function_ `virtual TSharedPtr<FHierarchyElementViewModel> CreateCustomViewModelForElement(UHierarchyElement* Element, TSharedPtr<FHierarchyElementViewModel> Parent)` — This function is used to determine custom view models for Hierarchy Elements. Called by CreateViewModelForElement.
- L671 _private prototype_ `virtual void GenerateDynamicContextMenuInternal(UToolMenu* DynamicToolMenu);` — Override this to add custom context menu options. Defaults to common actions such as finding, renaming and deleting. The hierarchy elements to generate this menu for are contained in a UHierarchyMenuContext object accessible through the ToolMenu.
- L673 _public function_ `const UHierarchyDataRefreshContext* GetRefreshContext() const`
- L675 _public function_ `void SetRefreshContext(UHierarchyDataRefreshContext* InContext)` — Set the refresh context to easily allow Hierarchy Elements representing external data to access whether the external data still exists.
- L677 _public prototype_ `void AddElementUnderRoot(TSubclassOf<UHierarchyElement> NewChildClass, FHierarchyElementIdentity ChildIdentity);`
- L678 _public prototype_ `void AddCategory(TSharedPtr<FHierarchyElementViewModel> CategoryParent = nullptr);`
- L681 _public prototype_ `void DeleteElements(TArray<TSharedPtr<FHierarchyElementViewModel>> ViewModels);` — Delete all specified elements.
- L684 _public prototype_ `void DeleteElementWithIdentity(FHierarchyElementIdentity Identity);` — Special case for deleting a specific element based on its identity. Useful for externally removing an element from the hierarchy when you don't have access to the view model.
- L686 _public prototype_ `void NavigateToElementInHierarchy(const FHierarchyElementIdentity& HierarchyIdentity) const;`
- L687 _public prototype_ `void NavigateToElementInHierarchy(const TSharedRef<FHierarchyElementViewModel> HierarchyElement) const;`
- L690 _public prototype_ `void ForceFullRefresh();` — Refreshes all data and widgets
- L691 _public prototype_ `void ForceFullRefreshOnTimer();`
- L692 _public prototype_ `void RequestFullRefreshNextFrame();`
- L694 _public function_ `TSharedRef<FUICommandList> GetCommands() const`
- L696 _public prototype_ `void OnGetChildren(TSharedPtr<FHierarchyElementViewModel> Element, TArray<TSharedPtr<FHierarchyElementViewModel>>& OutChildren) const;`
- L698 _public prototype_ `void RefreshAllViews(bool bFullRefresh = false) const;`
- L699 _public prototype_ `void RefreshSourceView(bool bFullRefresh = false) const;`
- L700 _public prototype_ `void RefreshHierarchyView(bool bFullRefresh = false) const;`
- L701 _public prototype_ `void RefreshSectionsView() const;`
- L704 _public function_ `FSimpleDelegate& OnRefreshSourceItemsRequested()` — Delegate that call functions from SHierarchyEditor
- L705 _public function_ `FOnRefreshViewRequested& OnRefreshSourceView()`
- L706 _public function_ `FOnRefreshViewRequested& OnRefreshHierarchyView()`
- L707 _public function_ `FSimpleDelegate& OnRefreshSectionsView()`
- L710 _public function_ `FOnHierarchyChanged& GetOnHierarchyChangedDelegate()` — Delegates for external systems
- L711 _public function_ `FOnRefreshViewRequested& OnRefreshViewRequested()`
- L712 _public function_ `FOnNavigateToElementIdentityInHierarchyRequested& OnNavigateToElementIdentityInHierarchyRequested()`
- L713 _public function_ `FOnNavigateToElementInHierarchyRequested& OnNavigateToElementInHierarchyRequested()`
- L714 _public function_ `FSimpleDelegate& OnInitialized()`
- L717 _public prototype_ `void SetActiveHierarchySection(TSharedPtr<struct FHierarchySectionViewModel>);` — Sections
- L718 _public prototype_ `TSharedPtr<FHierarchySectionViewModel> GetActiveHierarchySectionViewModel() const;`
- L719 _public prototype_ `const UHierarchySection* GetActiveHierarchySectionData() const;`
- L720 _public prototype_ `bool IsHierarchySectionActive(const UHierarchySection* Section) const;`
- L721 _public function_ `FOnSectionActivated& OnHierarchySectionActivated()`
- L723 _public prototype_ `FString OnElementToStringDebug(TSharedPtr<FHierarchyElementViewModel> ElementViewModel) const;`
- L726 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L727 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L728 _protected prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;`
- L730 _private prototype_ `bool FilterForHierarchySection(TSharedPtr<const FHierarchyElementViewModel> ViewModel) const;`
- L732 _private prototype_ `static void GenerateDynamicContextMenu(UToolMenu* ToolMenu);`
- L734 _private prototype_ `void ToolMenuRequestRename(const FToolMenuContext& Context) const;`
- L735 _private prototype_ `bool ToolMenuCanRequestRename(const FToolMenuContext& Context) const;`
- L737 _private prototype_ `void ToolMenuDelete(const FToolMenuContext& Context);`
- L738 _private prototype_ `bool ToolMenuCanDelete(const FToolMenuContext& Context) const;`
- L740 _private prototype_ `void ToolMenuNavigateTo(const FToolMenuContext& Context) const;`
- L741 _private prototype_ `bool ToolMenuCanNavigateTo(const FToolMenuContext& Context) const;`
- L745 _protected member_ `TObjectPtr<UHierarchyRoot> HierarchyRoot;` — `UPROPERTY()`
- L747 _protected member_ `TSharedPtr<struct FHierarchyRootViewModel> HierarchyRootViewModel;`
- L749 _protected member_ `TSharedPtr<FHierarchySectionViewModel> DefaultHierarchySectionViewModel;`
- L750 _protected member_ `TWeakPtr<struct FHierarchySectionViewModel> ActiveHierarchySectionViewModel;`
- L752 _protected member_ `TSharedPtr<FUICommandList> Commands;`
- L755 _protected member_ `TObjectPtr<UHierarchyDataRefreshContext> RefreshContext = nullptr;` — `UPROPERTY(Transient)`
- L759 _protected member_ `FSimpleDelegate RefreshSourceItemsRequestedDelegate;` — delegate collection to call UI functions
- L760 _protected member_ `FOnRefreshViewRequested RefreshAllViewsRequestedDelegate;`
- L761 _protected member_ `FOnRefreshViewRequested RefreshSourceViewDelegate;`
- L762 _protected member_ `FOnRefreshViewRequested RefreshHierarchyWidgetDelegate;`
- L763 _protected member_ `FSimpleDelegate RefreshSectionsViewDelegate;`
- L764 _protected member_ `FOnNavigateToElementIdentityInHierarchyRequested OnNavigateToElementIdentityInHierarchyRequestedDelegate;`
- L765 _protected member_ `FOnNavigateToElementInHierarchyRequested OnNavigateToElementInHierarchyRequestedDelegate;`
- L767 _protected member_ `FOnSectionActivated OnHierarchySectionActivatedDelegate;`
- L768 _protected member_ `FOnSectionActivated OnSourceSectionActivatedDelegate;`
- L769 _protected member_ `FOnHierarchyChanged OnHierarchyChangedDelegate;`
- L771 _protected member_ `FSimpleDelegate OnInitializedDelegate;`
- L773 _protected member_ `FTimerHandle FullRefreshNextFrameHandle;`
- L777 _private member_ `bool bIsInitialized = false;` — `UPROPERTY(Transient)`
- L780 _private member_ `bool bIsFinalized = false;` — `UPROPERTY(Transient)`
- L784 _private member_ `TObjectPtr<UHierarchySection> AllSection;` — `UPROPERTY(Transient)` — We construct a transient all section that isn't actually contained within the hierarchy.
- L786 _public member_ `static FName AllSectionHierarchyObjectName;`
- L787 _public member_ `static FName AllSectionSourceObjectName;`
- L788 _public member_ `static FText AllSectionDisplayName;`

#### struct `FHierarchyElementViewModel`  
`struct FHierarchyElementViewModel : TSharedFromThis<FHierarchyElementViewModel>, public FTickableEditorObject`  
_L794-1039_
- inherits: `TSharedFromThis<FHierarchyElementViewModel>,FTickableEditorObject`
- desc: The base view model for all elements in the hierarchy. There are four base view models inheriting from this; for roots, items, categories, and sections. When creating a new view model, you should inherit from one of those four base view models.
- L797 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnFilterChild, const TSharedPtr<const FHierarchyElementViewModel> Child);`
- L798 _public function_ `DECLARE_DELEGATE_OneParam(FOnChildRequestedDeletion, TSharedPtr<FHierarchyElementViewModel> Child) FHierarchyElementViewModel(UHierarchyElement* InElement, TSharedPtr<FHierarchyElementViewModel> InParent, TWeakObjectPtr<UDataHierarchyViewModelBase> InHierarchyViewModel, bool bInIsForHierarchy) : Element(InElement) , Parent(InParent) , HierarchyViewModel(InHierarchyViewModel) , bIsForHierarchy(bInIsForHierarchy)`
- L810 _public function_ `virtual void Initialize()` — Can be implemented for additional logic that the constructor isn't valid for.
- L814 _public function_ `UHierarchyElement* GetDataMutable()`
- L815 _public function_ `const UHierarchyElement* GetData() const`
- L818 _public function_ `template<class T> T* GetDataMutable()`
- L821 _public function_ `template<class T> const T* GetData() const`
- L823 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L824 _public prototype_ `virtual TStatId GetStatId() const override;`
- L826 _public function_ `virtual FString ToString() const`
- L827 _public function_ `FText ToStringAsText() const`
- L828 _public function_ `virtual TArray<FString> GetSearchTerms() const`
- L830 _public prototype_ `void RefreshChildrenData();`
- L831 _public prototype_ `void SyncViewModelsToData();`
- L834 _public prototype_ `virtual void SortChildrenData();` — Every item view model can define its own sort order for its children. By default we put categories above items.
- L836 _public function_ `const TArray<TSharedPtr<FHierarchyElementViewModel>>& GetChildren() const`
- L837 _public function_ `TArray<TSharedPtr<FHierarchyElementViewModel>>& GetChildrenMutable()`
- L838 _public prototype_ `const TArray<TSharedPtr<FHierarchyElementViewModel>>& GetFilteredChildren() const;`
- L840 _public prototype_ `void AddChildFilter(FOnFilterChild InFilterChild);`
- L843 _public prototype_ `template<class DataClass, class ViewModelChildClass> void GetChildrenViewModelsForType(TArray<TSharedPtr<ViewModelChildClass>>& OutChildren, bool bRecursive = false) const;`
- L846 _public prototype_ `int32 GetHierarchyDepth() const;` — Returns the hierarchy depth via number of parents above.
- L847 _public prototype_ `bool HasParent(TSharedPtr<FHierarchyElementViewModel> ParentCandidate, bool bRecursive = false) const;`
- L849 _public prototype_ `TSharedRef<FHierarchyElementViewModel> DuplicateToThis(TSharedPtr<FHierarchyElementViewModel> ItemToDuplicate, int32 InsertIndex = INDEX_NONE);`
- L850 _public prototype_ `TSharedRef<FHierarchyElementViewModel> ReparentToThis(TSharedPtr<FHierarchyElementViewModel> ItemToMove, int32 InsertIndex = INDEX_NONE);`
- L853 _public prototype_ `TSharedPtr<FHierarchyElementViewModel> FindViewModelForChild(const UHierarchyElement* Child, bool bSearchRecursively = false) const;` — Finds the view model for a given hierarchy element. Needs to be a child of the current element somewhere down the hierarchy.
- L855 _public prototype_ `TSharedPtr<FHierarchyElementViewModel> FindViewModelForChild(FHierarchyElementIdentity ChildIdentity, bool bSearchRecursively = false) const;` — Finds the view model for a given hierarchy element identity. Needs to be a child of the current element somewhere down the hierarchy.
- L857 _public prototype_ `TSharedPtr<FHierarchyElementViewModel> FindViewModelForObject(const UObject* Object, bool bSearchRecursively = false) const;` — Finds the view model for a given object. Can be a hierarchy element, but view models can also represent other objects not part of the hierarchy.
- L859 _public prototype_ `int32 FindIndexOfChild(const UHierarchyElement* Child) const;`
- L860 _public prototype_ `int32 FindIndexOfDataChild(TSharedPtr<const FHierarchyElementViewModel> Child) const;`
- L861 _public prototype_ `int32 FindIndexOfDataChild(const UHierarchyElement* Child) const;`
- L863 _public prototype_ `TSharedPtr<FHierarchyElementViewModel> AddChild(TSubclassOf<UHierarchyElement> NewChildClass, int32 InsertIndex = INDEX_NONE, FHierarchyElementIdentity ChildIdentity = FHierarchyElementIdentity());`
- L866 _public prototype_ `void Delete();` — Deleting will ask the parent to delete its child
- L867 _public prototype_ `void DeleteChild(TSharedPtr<FHierarchyElementViewModel> Child);`
- L869 _public function_ `TWeakObjectPtr<UDataHierarchyViewModelBase> GetHierarchyViewModel() const`
- L872 _public prototype_ `TOptional<EItemDropZone> OnCanRowAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone, TSharedPtr<FHierarchyElementViewModel> Item);` — Returns a set result if the item can accept a drop either above/onto/below the item.
- L873 _public prototype_ `virtual FReply OnDroppedOnRow(const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone, TSharedPtr<FHierarchyElementViewModel> Item);`
- L874 _public prototype_ `void OnRowDragLeave(const FDragDropEvent& DragDropEvent);`
- L896 _public function_ `virtual void PostEditChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged)` — Called when a property on the underlying data changes.
- L899 _public function_ `virtual FResultWithUserFeedback IsEditableByUser()` — Should return true if properties are supposed to be editable & needs to be true if typical operations should work on it (renaming, dragging, deleting etc.)
- L902 _public function_ `virtual FResultWithUserFeedback CanHaveChildren() const` — Needs to be true in order to allow drag & drop operations to parent items to this item
- L905 _public prototype_ `FResultWithUserFeedback CanDrag();` — Should return true if an item should be draggable. An uneditable item can not be dragged even if CanDragInternal returns true.
- L908 _public function_ `bool CanRename()` — Returns true if renamable
- L910 _public prototype_ `void Rename(FName NewName);`
- L912 _public function_ `void RequestRename()`
- L921 _public function_ `void RequestRenamePending()`
- L930 _public function_ `bool CanDelete()` — Returns true if deletable
- L932 _public prototype_ `bool IsExpandedByDefault() const;`
- L935 _public prototype_ `FResultWithUserFeedback CanDropOn(TSharedPtr<FHierarchyElementViewModel> DraggedElement, EItemDropZone ItemDropZone);` — Returns true if the given item can be dropped on the given target area.
- L938 _public prototype_ `void OnDroppedOn(TSharedPtr<FHierarchyElementViewModel> DroppedItem, EItemDropZone ItemDropZone);` — Gets executed when an item was dropped on this.
- L940 _public function_ `virtual TOptional<FResultWithUserFeedback> CanDropOnOverride(TSharedPtr<FHierarchyElementViewModel> DraggedElement, EItemDropZone ItemDropZone)` — Lets you completely customize the OnDroppedOn behavior. Needs to a specific value if you override this.
- L941 _public function_ `virtual TOptional<bool> OnDroppedOnOverride(TSharedPtr<FHierarchyElementViewModel> DroppedElement, EItemDropZone ItemDropZone)`
- L944 _public prototype_ `FResultWithUserFeedback CanContain(TSubclassOf<UHierarchyElement> HierarchyElementType);` — Returns true if this element can add a new element via the add menu.
- L947 _public function_ `virtual bool RepresentsExternalData() const` — For data cleanup that represents external data, this needs to return true in order for live cleanup to work.
- L951 _public function_ `virtual bool DoesExternalDataStillExist(const UHierarchyDataRefreshContext* Context) const` — This function determines whether a hierarchy item that represents that external data should be maintained during data refresh Needs to be implemented if RepresentsExternalData return true. The context object can be used to add arbitrary data.
- L954 _public function_ `virtual UObject* GetObjectForEditing()` — The UObject we display in the details panel when this item is selected. By default it's the hierarchy element the view model represents.
- L957 _public function_ `virtual bool AllowEditingInDetailsPanel() const` — Source items are transient, which is why we don't allow editing by default. This is useful to override if source data points at actual data to edit.
- L959 _public function_ `bool IsForHierarchy() const`
- L962 _public function_ `virtual void AppendDynamicContextMenuForSingleElement(UToolMenu* ToolMenu)` — Override this to register dynamic context menu entries when right clicking a single hierarchy item
- L964 _public function_ `FSimpleDelegate& GetOnRequestRename()`
- L965 _public function_ `FOnSynced& GetOnSynced()`
- L966 _public function_ `FOnChildRequestedDeletion& OnChildRequestedDeletion()`
- L969 _public function_ `TWeakPtr<FHierarchyElementViewModel> GetParent()` — Returns the parent view model of the hierarchical parent
- L971 _public function_ `virtual const FTableRowStyle* GetRowStyle() const`
- L975 _protected function_ `virtual void PostAddFixup()` — Override this to handle post-add logic (for example when dropping an element on another element, or using the add button).
- L979 _protected function_ `virtual void PostOnDroppedOn(TSharedPtr<FHierarchyElementViewModel> DroppedElementViewModel)` — Called after an element was dropped onto the calling element. Allows inserting specialized fix up. Not called if OnDroppedOnOverride was called. Note: DroppedElementViewModel is the newly created view model _after_ the drop occured.
- L983 _private function_ `virtual FResultWithUserFeedback CanContainInternal(TSubclassOf<UHierarchyElement> InHierarchyElementType)` — Should return true if this element can contain other elements as children. Can optionally specify a message for failure.
- L986 _private function_ `virtual FResultWithUserFeedback CanDragInternal()` — Should return true if draggable. An optional message can be provided if false that will show as a slate notification.
- L989 _private function_ `virtual bool CanRenameInternal()` — Should return true if renamable
- L991 _private function_ `virtual void RenameInternal(FName NewName)`
- L994 _private function_ `virtual bool CanDeleteInternal()` — Should return true if deletable. By default, we can delete items in the hierarchy, not in the source.
- L996 _private prototype_ `virtual bool IsExpandedByDefaultInternal() const;`
- L999 _private prototype_ `virtual FResultWithUserFeedback CanDropOnInternal(TSharedPtr<FHierarchyElementViewModel> DraggedElement, EItemDropZone ItemDropZone);` — Should return true if the given drag drop operation is allowed to succeed.
- L1002 _private function_ `virtual void RefreshChildrenDataInternal()` — Optionally implement this to refresh dependent data.
- L1005 _private function_ `virtual void SyncViewModelsToDataInternal()` — Optionally implement this to further customize the view model sync process. An example for this is how the root view model handles sections, as sections exist outside the children hierarchy
- L1008 _private function_ `virtual void FinalizeInternal()` — Optionally implement this to handle shutdown logic. An example for this is when a section gets deleted, it iterates over all categories to null out the associated section
- L1010 _private prototype_ `void PropagateOnChildSynced();`
- L1013 _protected member_ `UHierarchyElement* const Element;` — The hierarchy element this view model represents. Assumed valid while this view model exists.
- L1016 _protected member_ `TWeakPtr<FHierarchyElementViewModel> Parent;` — Parent should be valid for all instances of this struct except for root objects
- L1017 _protected member_ `TArray<TSharedPtr<FHierarchyElementViewModel>> Children;`
- L1019 _protected member_ `TWeakObjectPtr<UDataHierarchyViewModelBase> HierarchyViewModel;`
- L1021 _protected member_ `TArray<FOnFilterChild> ChildFilters;`
- L1022 _protected member_ `mutable TArray<TSharedPtr<FHierarchyElementViewModel>> FilteredChildren;`
- L1024 _protected member_ `FSimpleDelegate OnRequestRenameDelegate;`
- L1025 _protected member_ `FOnSynced OnSyncedDelegate;`
- L1026 _protected member_ `FOnChildRequestedDeletion OnChildRequestedDeletionDelegate;`
- L1028 _protected member_ `bool bRenamePending = false;`
- L1029 _protected member_ `bool bIsForHierarchy = false;`
- L1030 _protected member_ `bool bIsSyncInProgress = false;`
- L1042 _function_ `template <class DataClass, class ViewModelClass> void FHierarchyElementViewModel::GetChildrenViewModelsForType(TArray<TSharedPtr<ViewModelClass>>& OutChildren, bool bRecursive) const`

#### struct `FHierarchyElementViewModel::FResultWithUserFeedback`  
`struct FResultWithUserFeedback`  
_L876-893_
- L878 _public function_ `FResultWithUserFeedback(bool bInCanPerform) : bResult(bInCanPerform)`
- L880 _public member_ `bool bResult = false;`
- L882 _public member_ `TOptional<FText> UserFeedback;` — A message that can be used for user feedback. Will either be used in tooltips in the hierarchy editor or as popup message etc..
- L884 _public function_ `bool operator==(const bool& bOther) const`
- L889 _public function_ `bool operator!=(const bool& bOther) const`

#### struct `FHierarchyElementViewModel::FDefaultUserFeedback`  
`struct FDefaultUserFeedback`  
_L1032-1038_
- L1034 _public member_ `static FText UneditableTarget;`
- L1035 _public member_ `static FText TargetCantContainType;`
- L1036 _public member_ `static FText AddElementFromSourceToHierarchy;`
- L1037 _public member_ `static FText MoveElementWithinHierarchy;`

#### struct `FHierarchyRootViewModel`  
`struct FHierarchyRootViewModel : FHierarchyElementViewModel`  
_L1061-1103_
- inherits: `FHierarchyElementViewModel`
- L1064 _public function_ `DECLARE_DELEGATE(FOnSectionsChanged) DECLARE_DELEGATE_OneParam(FOnSingleSectionChanged, TSharedPtr<FHierarchySectionViewModel> AddedSection) FHierarchyRootViewModel(UHierarchyElement* InItem, TWeakObjectPtr<UDataHierarchyViewModelBase> InHierarchyViewModel, bool bInIsForHierarchy) : FHierarchyElementViewModel(InItem, nullptr, InHierarchyViewModel, bInIsForHierarchy)`
- L1070 _public prototype_ `virtual void Initialize() override;`
- L1072 _public function_ `virtual FResultWithUserFeedback CanHaveChildren() const override`
- L1074 _public prototype_ `TSharedPtr<struct FHierarchySectionViewModel> AddSection();`
- L1075 _public prototype_ `void DeleteSection(TSharedPtr<FHierarchyElementViewModel> SectionViewModel);`
- L1076 _public function_ `TArray<TSharedPtr<struct FHierarchySectionViewModel>>& GetSectionViewModels()`
- L1078 _public function_ `FOnSyncPropagated& OnSyncPropagated()`
- L1081 _public function_ `FOnSectionsChanged& OnSectionsChanged()` — General purpose delegate for when sections change
- L1083 _public function_ `FOnSingleSectionChanged& OnSectionAdded()` — Delegates for when a section is added or removed
- L1084 _public function_ `FOnSingleSectionChanged& OnSectionDeleted()`
- L1086 _public function_ `virtual void PreEditHierarchyStructure()`
- L1087 _public function_ `virtual void PostEditHierarchyStructure()`
- L1089 _protected function_ `virtual FResultWithUserFeedback IsEditableByUser() override`
- L1090 _protected prototype_ `virtual FResultWithUserFeedback CanContainInternal(TSubclassOf<UHierarchyElement> InHierarchyElementType) override;`
- L1091 _protected prototype_ `virtual FResultWithUserFeedback CanDropOnInternal(TSharedPtr<FHierarchyElementViewModel> DraggedElement, EItemDropZone ItemDropZone) override;`
- L1093 _private prototype_ `void PropagateOnSynced();`
- L1094 _private prototype_ `virtual void SyncViewModelsToDataInternal() override;`
- L1095 _private prototype_ `virtual void PostOnDroppedOn(TSharedPtr<FHierarchyElementViewModel> DroppedElementViewModel) override;`
- L1097 _private member_ `TArray<TSharedPtr<struct FHierarchySectionViewModel>> SectionViewModels;`
- L1099 _private member_ `FOnSyncPropagated OnSyncPropagatedDelegate;`
- L1100 _private member_ `FOnSingleSectionChanged OnSectionAddedDelegate;`
- L1101 _private member_ `FOnSingleSectionChanged OnSectionDeletedDelegate;`
- L1102 _private member_ `FOnSectionsChanged OnSectionsChangedDelegate;`

#### struct `FHierarchySectionViewModel`  
`struct FHierarchySectionViewModel : FHierarchyElementViewModel`  
_L1105-1150_
- inherits: `FHierarchyElementViewModel`
- L1107 _public prototype_ `FHierarchySectionViewModel(UHierarchySection* InItem, TSharedRef<FHierarchyRootViewModel> InParent, TWeakObjectPtr<UDataHierarchyViewModelBase> InHierarchyViewModel);`
- L1108 _public prototype_ `virtual ~FHierarchySectionViewModel() override = default;`
- L1111 _public prototype_ `const UHierarchySection* GetSectionData() const;` — A custom function to retrieve data; if it's the all section, we want to return nullptr as that's what it serializes as.
- L1113 _public prototype_ `virtual FString ToString() const override;`
- L1115 _public prototype_ `void SetSectionName(FName InSectionName);`
- L1116 _public prototype_ `FName GetSectionName() const;`
- L1118 _public prototype_ `void SetSectionNameAsText(const FText& Text);`
- L1119 _public prototype_ `FText GetSectionNameAsText() const;`
- L1120 _public prototype_ `FText GetSectionTooltip() const;`
- L1122 _public function_ `void SetSectionImage(const FSlateBrush* InSectionImage)`
- L1123 _public function_ `virtual const FSlateBrush* GetSectionImageBrush() const`
- L1125 _public function_ `bool IsAllSection() const`
- L1127 _protected prototype_ `virtual bool AllowEditingInDetailsPanel() const override;`
- L1130 _protected prototype_ `virtual FResultWithUserFeedback IsEditableByUser() override;` — Only hierarchy sections are editable
- L1132 _protected function_ `virtual FResultWithUserFeedback CanHaveChildren() const override` — Technically a section does not have 'children' but for drag & drop logic it is considered as such
- L1133 _protected prototype_ `virtual FResultWithUserFeedback CanDragInternal() override;`
- L1136 _protected prototype_ `virtual bool CanRenameInternal() override;` — We can only rename hierarchy sections
- L1137 _protected function_ `virtual void RenameInternal(FName NewName) override`
- L1139 _protected prototype_ `virtual bool CanDeleteInternal() override;`
- L1142 _protected prototype_ `virtual TOptional<bool> OnDroppedOnOverride(TSharedPtr<FHierarchyElementViewModel> DroppedItem, EItemDropZone ItemDropZone) override;` — We override the default dropped on behavior given sections don't actually contain children.
- L1143 _protected prototype_ `virtual FResultWithUserFeedback CanContainInternal(TSubclassOf<UHierarchyElement> InHierarchyElement) override;`
- L1144 _protected prototype_ `virtual FResultWithUserFeedback CanDropOnInternal(TSharedPtr<FHierarchyElementViewModel> DraggedItem, EItemDropZone ItemDropZone) override;`
- L1146 _protected prototype_ `virtual void FinalizeInternal() override;`
- L1149 _private member_ `const FSlateBrush* SectionImage = nullptr;`

#### struct `FHierarchyItemViewModel`  
`struct FHierarchyItemViewModel : FHierarchyElementViewModel`  
_L1152-1166_
- inherits: `FHierarchyElementViewModel`
- L1154 _public function_ `FHierarchyItemViewModel(UHierarchyItem* InElement, TSharedRef<FHierarchyElementViewModel> InParent, TWeakObjectPtr<UDataHierarchyViewModelBase> InHierarchyViewModel) : FHierarchyElementViewModel(InElement, InParent, InHierarchyViewModel, InParent->IsForHierarchy())`
- L1156 _public prototype_ `virtual ~FHierarchyItemViewModel() override = default;`
- L1158 _public function_ `virtual FResultWithUserFeedback IsEditableByUser() override`
- L1159 _public function_ `virtual FResultWithUserFeedback CanHaveChildren() const override`
- L1160 _public function_ `virtual FResultWithUserFeedback CanDragInternal() override`
- L1162 _public prototype_ `virtual FResultWithUserFeedback CanContainInternal(TSubclassOf<UHierarchyElement> InHierarchyElement) override;`
- L1163 _public prototype_ `virtual FResultWithUserFeedback CanDropOnInternal(TSharedPtr<FHierarchyElementViewModel> DraggedItem, EItemDropZone ItemDropZone) override;`
- L1165 _public prototype_ `virtual const FTableRowStyle* GetRowStyle() const override;`

#### struct `FHierarchyCategoryViewModel`  
`struct FHierarchyCategoryViewModel : FHierarchyElementViewModel`  
_L1168-1186_
- inherits: `FHierarchyElementViewModel`
- L1170 _public function_ `FHierarchyCategoryViewModel(UHierarchyCategory* InCategory, TSharedRef<FHierarchyElementViewModel> InParent, TWeakObjectPtr<UDataHierarchyViewModelBase> InHierarchyViewModel) : FHierarchyElementViewModel(InCategory, InParent, InHierarchyViewModel, InParent->IsForHierarchy())`
- L1171 _public prototype_ `virtual ~FHierarchyCategoryViewModel() override= default;`
- L1173 _public function_ `void SetCategoryName(FName InText)`
- L1174 _public function_ `FText GetCategoryName() const`
- L1176 _public function_ `virtual FResultWithUserFeedback IsEditableByUser() override`
- L1177 _public function_ `virtual FResultWithUserFeedback CanHaveChildren() const override`
- L1178 _public function_ `virtual FResultWithUserFeedback CanDragInternal() override`
- L1179 _public function_ `virtual bool CanRenameInternal() override`
- L1180 _public function_ `virtual void RenameInternal(FName NewName) override`
- L1182 _public prototype_ `virtual FResultWithUserFeedback CanContainInternal(TSubclassOf<UHierarchyElement> InHierarchyElement) override;`
- L1183 _public prototype_ `virtual FResultWithUserFeedback CanDropOnInternal(TSharedPtr<FHierarchyElementViewModel>, EItemDropZone ItemDropZone) override;`
- L1185 _public prototype_ `virtual const FTableRowStyle* GetRowStyle() const override;`

#### class `FSectionDragDropOp`  
`class FSectionDragDropOp : public FHierarchyDragDropOp`  
_L1188-1198_
- inherits: `FHierarchyDragDropOp`
- L1191 _public function_ `DRAG_DROP_OPERATOR_TYPE(FSectionDragDropOp, FHierarchyDragDropOp) FSectionDragDropOp(TSharedPtr<FHierarchySectionViewModel> SectionViewModel) : FHierarchyDragDropOp(FDataHierarchyDragDropContext({FDraggedElementEntry{SectionViewModel}}))`
- L1195 _public function_ `TWeakPtr<FHierarchySectionViewModel> GetDraggedSection() const`
- L1197 _private prototype_ `virtual TSharedRef<SWidget> CreateCustomDecorator() const override;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API DATAHIERARCHYEDITOR_API`
- L587 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHierarchyChanged, const TInstancedStruct<FHierarchyChangedPayload>&) DECLARE_DELEGATE_OneParam(FOnSectionActivated, TSharedPtr<FHierarchySectionViewModel> Section) DECLARE_DELEGATE_OneParam(FOnRefreshViewRequested, bool bForceFullRefresh) DECLARE_DELEGATE_OneParam(FOnNavigateToElementIdentityInHierarchyRequested, FHierarchyElementIdentity Identity) DECLARE_DELEGATE_OneParam(FOnNavigateToElementInHierarchyRequested, TSharedPtr<FHierarchyElementViewModel> ElementViewModel) GENERATED_BODY() UDataHierarchyViewModelBase();`
- L588 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSectionActivated, TSharedPtr<FHierarchySectionViewModel> Section) DECLARE_DELEGATE_OneParam(FOnRefreshViewRequested, bool bForceFullRefresh) DECLARE_DELEGATE_OneParam(FOnNavigateToElementIdentityInHierarchyRequested, FHierarchyElementIdentity Identity) DECLARE_DELEGATE_OneParam(FOnNavigateToElementInHierarchyRequested, TSharedPtr<FHierarchyElementViewModel> ElementViewModel) GENERATED_BODY() UDataHierarchyViewModelBase();`
- L589 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRefreshViewRequested, bool bForceFullRefresh) DECLARE_DELEGATE_OneParam(FOnNavigateToElementIdentityInHierarchyRequested, FHierarchyElementIdentity Identity) DECLARE_DELEGATE_OneParam(FOnNavigateToElementInHierarchyRequested, TSharedPtr<FHierarchyElementViewModel> ElementViewModel) GENERATED_BODY() UDataHierarchyViewModelBase();`
- L590 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNavigateToElementIdentityInHierarchyRequested, FHierarchyElementIdentity Identity) DECLARE_DELEGATE_OneParam(FOnNavigateToElementInHierarchyRequested, TSharedPtr<FHierarchyElementViewModel> ElementViewModel) GENERATED_BODY() UDataHierarchyViewModelBase();`
- L591 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNavigateToElementInHierarchyRequested, TSharedPtr<FHierarchyElementViewModel> ElementViewModel) GENERATED_BODY() UDataHierarchyViewModelBase();`
- L796 _delegate_ `DECLARE_DELEGATE(FOnSynced) DECLARE_DELEGATE_RetVal_OneParam(bool, FOnFilterChild, const TSharedPtr<const FHierarchyElementViewModel> Child);`
- L797 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnFilterChild, const TSharedPtr<const FHierarchyElementViewModel> Child);`
- L798 _delegate_ `DECLARE_DELEGATE_OneParam(FOnChildRequestedDeletion, TSharedPtr<FHierarchyElementViewModel> Child) FHierarchyElementViewModel(UHierarchyElement* InElement, TSharedPtr<FHierarchyElementViewModel> InParent, TWeakObjectPtr<UDataHierarchyViewModelBase> InHierarchyViewModel, bool bInIsForHierarchy) : Element(InElement) , Parent(InParent) , HierarchyViewModel(InHierarchyViewModel) , bIsForHierarchy(bInIsForHierarchy) { } virtual void Initialize() {} virtual ~FHierarchyElementViewModel() override;`
- L1063 _delegate_ `DECLARE_DELEGATE(FOnSyncPropagated) DECLARE_DELEGATE(FOnSectionsChanged) DECLARE_DELEGATE_OneParam(FOnSingleSectionChanged, TSharedPtr<FHierarchySectionViewModel> AddedSection) FHierarchyRootViewModel(UHierarchyElement* InItem, TWeakObjectPtr<UDataHierarchyViewModelBase> InHierarchyViewModel, bool bInIsForHierarchy) : FHierarchyElementViewModel(InItem, nullptr, InHierarchyViewModel, bInIsForHierarchy) {} virtual ~FHierarchyRootViewModel() override;`
- L1064 _delegate_ `DECLARE_DELEGATE(FOnSectionsChanged) DECLARE_DELEGATE_OneParam(FOnSingleSectionChanged, TSharedPtr<FHierarchySectionViewModel> AddedSection) FHierarchyRootViewModel(UHierarchyElement* InItem, TWeakObjectPtr<UDataHierarchyViewModelBase> InHierarchyViewModel, bool bInIsForHierarchy) : FHierarchyElementViewModel(InItem, nullptr, InHierarchyViewModel, bInIsForHierarchy) {} virtual ~FHierarchyRootViewModel() override;`
- L1065 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSingleSectionChanged, TSharedPtr<FHierarchySectionViewModel> AddedSection) FHierarchyRootViewModel(UHierarchyElement* InItem, TWeakObjectPtr<UDataHierarchyViewModelBase> InHierarchyViewModel, bool bInIsForHierarchy) : FHierarchyElementViewModel(InItem, nullptr, InHierarchyViewModel, bInIsForHierarchy) {} virtual ~FHierarchyRootViewModel() override;`
