# Plugins / InlineMaterialInstanceEditor

- module root: `Plugins/Experimental/InlineMaterialInstance/Source/InlineMaterialInstanceEditor`
- headers: 2; symbols: 21
- symbol kinds: class=2, function=5, member=6, prototype=8
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, Landscape, MaterialEditor, PropertyEditor, Slate, SlateCore, UnrealEd

### `Plugins/Experimental/InlineMaterialInstance/Source/InlineMaterialInstanceEditor/Private/Widgets/SMaterialDynamicParametersPanelWidget.h` (Private)


#### class `SMaterialDynamicParametersPanelWidget`  
`class SMaterialDynamicParametersPanelWidget : public SCompoundWidget`  
_L17-50_
- inherits: `SCompoundWidget`
- desc: Dynamic Material parameters view. The view creates all widgets for dynamic material instance parameters Most of the logic copied from SMaterialParametersOverviewTreeItem
- L22 _public function_ `SLATE_BEGIN_ARGS(SMaterialDynamicParametersPanelWidget) : _InMaterialInstance(nullptr)`
- L26 _public prototype_ `SLATE_ARGUMENT(UMaterialInstance*, InMaterialInstance) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L32 _public prototype_ `void UpdateInstance(UMaterialInstance* InMaterialInstance);` — Update material instance for tree generation and refresh
- L36 _private prototype_ `void Refresh();` — Refresh MaterialParameters tree
- L40 _private member_ `TWeakObjectPtr<UMaterialInstance> MaterialInstance;` — The set of material parameters this is associated with
- L43 _private member_ `TSharedPtr<class SMaterialDynamicParametersOverviewTree> NestedTree;` — The tree contained in this item
- L46 _private member_ `TSharedPtr<class SScrollBar> ExternalScrollbar;` — Optional external Scroll bar
- L49 _private member_ `TSharedPtr<IPropertyRowGenerator> Generator;` — Row generator instance

### `Plugins/Experimental/InlineMaterialInstance/Source/InlineMaterialInstanceEditor/Private/Widgets/SMaterialDynamicWidgets.h` (Private)


#### class `SMaterialDynamicView`  
`class SMaterialDynamicView : public SCompoundWidget`  
_L18-77_
- inherits: `SCompoundWidget`
- desc: Creates the view for material dynamic view
- L21 _public function_ `SLATE_BEGIN_ARGS(SMaterialDynamicView)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FMaterialItemView>& InMaterialItemView, UActorComponent* InCurrentComponent);`
- L30 _private function_ `template<typename TMaterialClass> TAttribute<EVisibility> GetButtonVisibilityAttribute(const bool bIsInvertedResult = false) const` — Get Visibility for extension button
- L48 _private prototype_ `FReply OnRevertButtonClicked() const;` — Button handler for revert to original material for the slot
- L51 _private prototype_ `FReply OnResetButtonClicked() const;` — Button handler for reset parameters to default instance material parameter
- L54 _private prototype_ `FReply OnCopyToOriginalButtonClicked() const;` — Button handler for copy material parameters to original instance material
- L57 _private prototype_ `FReply OnCreateDynamicMaterialButtonClicked() const;` — Button handler for create dynamic material
- L61 _private function_ `template<typename TReturnType, typename TInputType> TReturnType* GetMaterialParent(UMaterialInterface* InMaterialInterface) const` — Get parent material and cast to specified type
- L73 _private member_ `TWeakPtr<FMaterialItemView> MaterialItemViewWeakPtr;` — Weak Pointer to Material Item View
- L76 _private member_ `TWeakObjectPtr<UActorComponent> CurrentComponent;` — Weak pointer to current component using the current material

#### Free symbols / members of external scopes

- L33 _function_ `` (scope `SMaterialDynamicView::GetButtonVisibilityAttribute`)
