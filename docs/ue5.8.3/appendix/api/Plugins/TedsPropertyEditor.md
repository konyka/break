# Plugins / TedsPropertyEditor

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsPropertyEditor`
- headers: 2; symbols: 28
- symbol kinds: class=2, delegate=3, function=2, macro=2, member=8, prototype=11
- DynamicallyLoadedModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine, SceneOutliner, Slate, SlateCore, TedsOutliner, TypedElementFramework, UnrealEd

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsPropertyEditor/Public/TedsRowPickingMode.h` (Public)


#### class `FTedsRowPickingMode`  
`class FTedsRowPickingMode : public UE::Editor::Outliner::FTedsOutlinerMode`  
_L18-33_
- inherits: `UE::Editor::Outliner::FTedsOutlinerMode`
- desc: Picking mode for TEDs Scene Outliner Widgets. Based off of FActorPickingMode
- L21 _public prototype_ `FTedsRowPickingMode(const UE::Editor::Outliner::FTedsOutlinerParams& Params, FOnSceneOutlinerItemPicked OnItemPickedDelegate);`
- L23 _public prototype_ `virtual ~FTedsRowPickingMode() = default;`
- L25 _public prototype_ `virtual void OnItemSelectionChanged(FSceneOutlinerTreeItemPtr Item, ESelectInfo::Type SelectionType, const FSceneOutlinerItemSelection& Selection) override;`
- L28 _public prototype_ `virtual void OnFilterTextCommited(FSceneOutlinerItemSelection& Selection, ETextCommit::Type CommitType) override;` — Allow the user to commit their selection by pressing enter if it is valid
- L30 _public function_ `virtual bool ShowViewButton() const override`
- L32 _private member_ `FOnSceneOutlinerItemPicked OnItemPicked;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEDSPROPERTYEDITOR_API`
- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTedsRowSelected, UE::Editor::DataStorage::RowHandle RowHandle);`
- L11 _prototype_ `DECLARE_DELEGATE_OneParam(FOnTedsRowSelected, UE::Editor::DataStorage::RowHandle RowHandle);`
- L12 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterTedsRow, const UE::Editor::DataStorage::RowHandle RowHandle);`
- L12 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterTedsRow, const UE::Editor::DataStorage::RowHandle RowHandle);`
- L13 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldInteractTedsRow, const UE::Editor::DataStorage::RowHandle RowHandle);`
- L13 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldInteractTedsRow, const UE::Editor::DataStorage::RowHandle RowHandle);`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsPropertyEditor/Public/Widgets/SPropertyMenuTedsRowPicker.h` (Public)


#### class `SPropertyMenuTedsRowPicker`  
`class SPropertyMenuTedsRowPicker : public SCompoundWidget`  
_L10-50_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SPropertyMenuTedsRowPicker) : _AllowClear(true) , _ElementFilter() , _InteractiveFilter()`
- L18 _public prototype_ `SLATE_ARGUMENT(bool, AllowClear) SLATE_ARGUMENT(UE::Editor::DataStorage::FQueryDescription, QueryFilter) SLATE_ARGUMENT(FOnShouldFilterTedsRow, ElementFilter) SLATE_ARGUMENT(FOnShouldInteractTedsRow, InteractiveFilter) SLATE_EVENT(FOnTedsRowSelected, OnSet) SLATE_EVENT(FSimpleDelegate, OnClose) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _private prototype_ `void OnClear();`
- L32 _private prototype_ `void OnElementSelected(UE::Editor::DataStorage::RowHandle RowHandle);`
- L34 _private prototype_ `void SetValue(UE::Editor::DataStorage::RowHandle RowHandle);`
- L37 _private member_ `bool bAllowClear;`
- L39 _private member_ `UE::Editor::DataStorage::FQueryDescription QueryFilter;`
- L41 _private member_ `FOnShouldFilterTedsRow ElementFilter;`
- L43 _private member_ `FOnShouldInteractTedsRow InteractiveFilter;`
- L45 _private member_ `FOnTedsRowSelected OnSet;`
- L47 _private member_ `FSimpleDelegate OnClose;`
- L49 _private member_ `FSimpleDelegate OnUseSelected;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEDSPROPERTYEDITOR_API`
