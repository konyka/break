# Plugins / TedsEverythingPicker

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsEverythingPicker`
- headers: 3; symbols: 51
- symbol kinds: class=4, delegate=1, function=5, macro=1, member=10, namespace=15, prototype=15
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Slate, SlateCore, TedsQueryStack, TedsTableViewer, TedsTypeInfo
- PublicDependencyModuleNames: TypedElementFramework

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsEverythingPicker/Public/Context/TedsPickerContext.h` (Public)


#### class `UE::Editor::DataStorage::FPickerContext`  
`class FPickerContext : public TSlotBase<FPickerContext>`  
_L13-21_
- inherits: `TSlotBase<FPickerContext>`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsEverythingPicker/Public/Context/TedsPickerContextUtil.h` (Public)


#### class `UE::Editor::DataStorage::Picker::SObjectReferenceContextView`  
`class SObjectReferenceContextView : public SCompoundWidget`  
_L25-41_
- inherits: `SCompoundWidget`
- L28 _public function_ `SLATE_BEGIN_ARGS(SObjectReferenceContextView) : _SearchingEnabled(false) , _Columns({ FTypedElementLabelColumn::StaticStruct(), FTypedElementClassTypeInfoColumn::StaticStruct() })`
- L32 _public prototype_ `SLATE_ARGUMENT(FQueryDescription, Query) SLATE_ARGUMENT(TSharedPtr<QueryStack::IRowNode>, QueryStack)`

#### class `UE::Editor::DataStorage::Picker::STypeListContextView`  
`class STypeListContextView : public SCompoundWidget`  
_L43-57_
- inherits: `SCompoundWidget`
- L46 _public function_ `SLATE_BEGIN_ARGS(STypeListContextView) : _SearchingEnabled(false)`
- L49 _public prototype_ `SLATE_ARGUMENT(FQueryDescription, Query)` — If set will perform the requested query. Ex: Select().Where().All<FClassTypeInfoTag>().Compile(). Results Intersect with BaseType

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEDSEVERYTHINGPICKER_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Editor` (scope `UE`)
- L21 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L21 _namespace_ `namespace Picker` (scope `UE::Editor::DataStorage`)
- L23 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSelectionChanged, RowHandle, ESelectInfo::Type);`
- L23 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSelectionChanged, RowHandle, ESelectInfo::Type);` (scope `UE::Editor::DataStorage::Picker`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsEverythingPicker/Public/Widgets/SEverythingPicker.h` (Public)


#### class `UE::Editor::DataStorage::Picker::SEverythingPicker`  
`class SEverythingPicker : public SCompoundWidget`  
_L17-107_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SEverythingPicker) : _WidthOverride(FOptionalSize()) , _HeightOverride(FOptionalSize()) , _MinDesiredWidth(FOptionalSize()) , _MinDesiredHeight(FOptionalSize()) , _MaxDesiredWidth(FOptionalSize()) , _MaxDesiredHeight(FOptionalSize()) , _ShowTabLabelWhenSingle(true)`
- L31 _public prototype_ `SLATE_SLOT_ARGUMENT(FPickerContext, Contexts) SLATE_ATTRIBUTE(FOptionalSize, WidthOverride) SLATE_ATTRIBUTE(FOptionalSize, HeightOverride) SLATE_ATTRIBUTE(FOptionalSize, MinDesiredWidth) SLATE_ATTRIBUTE(FOptionalSize, MinDesiredHeight) SLATE_ATTRIBUTE(FOptionalSize, MaxDesiredWidth) SLATE_ATTRIBUTE(FOptionalSize, MaxDesiredHeight)`
- L52 _public prototype_ `virtual ~SEverythingPicker();`
- L54 _public prototype_ `void Construct(const FArguments& InArgs);`
- L56 _public prototype_ `void AddContext(const FPickerContext::FSlotArguments& SlotArgs);`
- L58 _public function_ `static FPickerContext::FSlotArguments Context()`
- L63 _public function_ `static FPickerContext::FSlotArguments Context(FPickerContext::FSlotArguments&& InContext)`
- L69 _public prototype_ `void SetWidthOverride(TAttribute<FOptionalSize> InWidthOverride);` — See WidthOverride attribute
- L72 _public prototype_ `void SetHeightOverride(TAttribute<FOptionalSize> InHeightOverride);` — See HeightOverride attribute
- L75 _public prototype_ `void SetMinDesiredWidth(TAttribute<FOptionalSize> InMinDesiredWidth);` — See MinDesiredWidth attribute
- L78 _public prototype_ `void SetMinDesiredHeight(TAttribute<FOptionalSize> InMinDesiredHeight);` — See MinDesiredHeight attribute
- L81 _public prototype_ `void SetMaxDesiredWidth(TAttribute<FOptionalSize> InMaxDesiredWidth);` — See MaxDesiredWidth attribute
- L84 _public prototype_ `void SetMaxDesiredHeight(TAttribute<FOptionalSize> InMaxDesiredHeight);` — See MaxDesiredHeight attribute
- L88 _private prototype_ `ECheckBoxState IsContextTabSelected(int32 ContextId) const;`
- L89 _private prototype_ `void OnActiveContextChanged(ECheckBoxState State, int32 ContextId);`
- L91 _private member_ `int32 ActiveContextId = 0;`
- L92 _private member_ `TSharedPtr<SBox> ContainerBox;`
- L93 _private member_ `TSharedPtr<SHorizontalBox> ContextTabs;`
- L94 _private member_ `TSharedPtr<SWidgetSwitcher> ContextTabViews;`
- L96 _private member_ `TSlateAttribute<FOptionalSize> WidthOverride;`
- L98 _private member_ `TSlateAttribute<FOptionalSize> HeightOverride;`
- L100 _private member_ `TSlateAttribute<FOptionalSize> MinDesiredWidth;`
- L102 _private member_ `TSlateAttribute<FOptionalSize> MinDesiredHeight;`
- L104 _private member_ `TSlateAttribute<FOptionalSize> MaxDesiredWidth;`
- L106 _private member_ `TSlateAttribute<FOptionalSize> MaxDesiredHeight;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace Picker` (scope `UE::Editor::DataStorage`)
