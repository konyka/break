# Editor / AssetTagsEditor

- module root: `Source/Editor/AssetTagsEditor`
- headers: 2; symbols: 34
- symbol kinds: class=2, delegate=1, enum=1, enumerator=2, function=16, macro=1, member=6, prototype=2, struct=2, typedef=1
- PublicDependencyModuleNames: Core, CoreUObject, Slate, SlateCore

### `Source/Editor/AssetTagsEditor/Public/AssetTagItemTypes.h` (Public)


#### enum `EAssetTagItemViewMode`  
`enum class EAssetTagItemViewMode : uint8`  
_L8-12_
- L10 _public enumerator_ `Standard`
- L11 _public enumerator_ `Compact`

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef TFunctionRef<void(const FText&, const FText&)> FOnBuildAssetTagItemToolTipInfoEntry;`
- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBuildAssetTagItemToolTipInfo, const FOnBuildAssetTagItemToolTipInfoEntry&);`
- L15 _prototype_ `DECLARE_DELEGATE_OneParam(FOnBuildAssetTagItemToolTipInfo, const FOnBuildAssetTagItemToolTipInfoEntry&);`

### `Source/Editor/AssetTagsEditor/Public/SAssetTagItem.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <typename ItemType> struct TWidgetTypeTraits<class SAssetTagItemTableRow<ItemType>>`  
_L36-39_
- L38 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SAssetTagItemTableRow`  
`template <typename ItemType> class SAssetTagItemTableRow : public STableRow<ItemType>`  
_L43-109_
- inherits: `STableRow<ItemType>`
- desc: Custom table row used to contain asset tag items within list and tree views
- L46 _public function_ `void Construct(const typename STableRow<ItemType>::FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)`
- L57 _public function_ `void SetIsDropTarget(const TAttribute<bool>& InIsDropTarget)`
- L62 _public function_ `virtual void SetContent(TSharedRef<SWidget> InContent) override`
- L67 _public function_ `virtual const FSlateBrush* GetBorder() const override`
- L78 _private function_ `TSharedRef<SWidget> WrapContentInSelectionBorder(const TSharedRef<SWidget> InContent) const`
- L89 _private function_ `TAttribute<FMargin> ApplySelectionBorderOuterPadding(const TAttribute<FMargin>& InPadding) const`
- L108 _private member_ `TAttribute<bool> IsDropTarget;`

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SAssetTagItem>`  
_L112-115_
- L38 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SAssetTagItem`  
`class SAssetTagItem : public SCompoundWidget`  
_L118-236_
- inherits: `SCompoundWidget`
- desc: A single asset tag item in the tags and collections tree.
- L121 _public function_ `SLATE_BEGIN_ARGS(SAssetTagItem) : _ViewMode(EAssetTagItemViewMode::Standard) , _BaseColor(FLinearColor::White)`
- L127 _public prototype_ `SLATE_ARGUMENT(EAssetTagItemViewMode, ViewMode) SLATE_ATTRIBUTE(FLinearColor, BaseColor) SLATE_ATTRIBUTE(FText, DisplayName) SLATE_ATTRIBUTE(FText, CountText) SLATE_ATTRIBUTE(FText, WarningText) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ATTRIBUTE(bool, IsNameReadOnly) SLATE_ATTRIBUTE(bool, IsCheckBoxEnabled) SLATE_ATTRIBUTE(ECheckBoxState, IsChecked) SLATE_EVENT(FOnCheckStateChanged, OnCheckStateChanged) SLATE_EVENT(FOnBeginTextEdit, OnBeginNameEdit) SLATE_EVENT(FOnTextCommitted, OnNameCommitted) SLATE_EVENT(FOnVerifyTextChanged, OnVerifyName) SLATE_EVENT(FIsSelected, IsSelected)` — Should this asset tag item use the standard or compact view?
- L176 _public function_ `void RequestRename()`
- L185 _private function_ `FLinearColor GetAssetTagBrightColor() const`
- L190 _private function_ `FLinearColor GetAssetTagDullColor() const`
- L195 _private function_ `FLinearColor GetAssetTagDisabledColor() const`
- L200 _private function_ `FText GetCheckBoxTooltipText() const`
- L209 _private function_ `FSlateColor GetCountBackgroundColor() const`
- L214 _private function_ `EVisibility GetWarningIconVisibility() const`
- L223 _private member_ `TAttribute<FLinearColor> BaseColor;` — Binding to get the base color of this asset tag item
- L226 _private member_ `TAttribute<FText> WarningText;` — Binding to get the warning text of this asset tag item (unset to omit the warning UI)
- L229 _private member_ `FIsSelected IsSelectedCallback;` — Callback to check if the asset tag item is selected (should only be hooked up if a parent widget is handling selection or focus)
- L232 _private member_ `TSharedPtr<SCheckBox> CheckBox;` — The check box for enabling/disabling the asset tag item
- L235 _private member_ `TSharedPtr<SInlineEditableTextBlock> InlineRenameWidget;` — The widget to display the name of the asset tag item and allows for renaming

#### Free symbols / members of external scopes

- L26 _macro_ `#define UE_API ASSETTAGSEDITOR_API`
- L96 _function_ `` (scope `SAssetTagItemTableRow::ApplySelectionBorderOuterPadding`)
