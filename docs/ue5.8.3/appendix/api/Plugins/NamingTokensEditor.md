# Plugins / NamingTokensEditor

- module root: `Plugins/Developer/NamingTokens/Source/NamingTokensEditor`
- headers: 8; symbols: 56
- symbol kinds: class=8, function=2, macro=1, member=10, namespace=5, prototype=30
- PrivateDependencyModuleNames: AssetDefinition, BlueprintGraph, Blutility, CoreUObject, EditorToolEvents, Engine, EngineAssetDefinitions, InputCore, Projects, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, NamingTokens

### `Plugins/Developer/NamingTokens/Source/NamingTokensEditor/Private/AssetDefinition_EditorUtilityNamingTokens.h` (Private)


#### class `UAssetDefinition_EditorUtilityNamingTokens`  
`class UAssetDefinition_EditorUtilityNamingTokens : public UAssetDefinition_Blueprint`  
_L11-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- desc: Asset definition for a UEditorUtilityNamingTokens asset
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L18 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L19 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`

### `Plugins/Developer/NamingTokens/Source/NamingTokensEditor/Private/AssetDefinition_NamingTokens.h` (Private)


#### class `UAssetDefinition_NamingTokens`  
`class UAssetDefinition_NamingTokens : public UAssetDefinition_Blueprint`  
_L10-19_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- L15 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L16 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L18 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`

### `Plugins/Developer/NamingTokens/Source/NamingTokensEditor/Private/Customization/NamingTokensCustomization.h` (Private)


#### class `FNamingTokensCustomization`  
`class FNamingTokensCustomization final : public IDetailCustomization`  
_L14-29_
- inherits: `IDetailCustomization`
- L17 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L26 _private member_ `TSharedPtr<IPropertyHandle> NamespacePropertyHandle;` — Handle to namespace property.
- L28 _private member_ `TSharedPtr<FText> TokenKeyErrorMessage;` — Stores error text.

#### class `FNamingTokensDataCustomization`  
`class FNamingTokensDataCustomization final : public IPropertyTypeCustomization`  
_L31-78_
- inherits: `IPropertyTypeCustomization`
- L34 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L39 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L40 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L43 _public prototype_ `UNamingTokens* GetOwningNamingTokens() const;` — The naming tokens owning this customization.
- L47 _private prototype_ `TArray<UFunction*> GetAvailableFunctions() const;` — Available functions which can be assigned to naming tokens.
- L49 _private prototype_ `TSharedRef<SWidget> MakeComboBoxWidget(TSharedPtr<FString> InItem);` — Make the combo box for selecting functions.
- L51 _private prototype_ `void OnFunctionSelected( TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo, TSharedPtr<IPropertyHandle> InFunctionNameHandle);` — When the user selects a function.
- L56 _private prototype_ `FText GetSelectedFunctionText() const;` — The text of the currently selected function.
- L58 _private prototype_ `FReply OnAddFunctionClicked();` — User clicked the button to add a new function.
- L60 _private prototype_ `bool CanAddFunction() const;` — If a new function can be added.
- L64 _private member_ `IPropertyTypeCustomizationUtils* CustomizationUtilsPtr = nullptr;` — Customization pointer.
- L66 _private member_ `TWeakObjectPtr<UBlueprint> OwningBlueprint;` — Blueprint of the naming tokens.
- L69 _private member_ `TArray<TSharedPtr<FString>> FunctionNames;` — All available function names.
- L71 _private member_ `TSharedPtr<FString> SelectedFunctionName;` — The selected function name.
- L73 _private member_ `TSharedPtr<IPropertyHandle> FunctionNameHandle;` — Property handle to the function name.
- L75 _private member_ `TSharedPtr<IPropertyHandle> TokenKeyHandle;` — Property handle to the token key.
- L77 _private member_ `TSharedPtr<FText> NamespaceErrorMessage;` — Stores error text.

### `Plugins/Developer/NamingTokens/Source/NamingTokensEditor/Private/EditorUtilityNamingTokensFactory.h` (Private)


#### class `UEditorUtilityNamingTokensFactory`  
`class UEditorUtilityNamingTokensFactory : public UFactory`  
_L12-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- desc: Factory class used to create new UEditorUtilityNamingTokens objects
- L17 _public prototype_ `UEditorUtilityNamingTokensFactory();`
- L19 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Developer/NamingTokens/Source/NamingTokensEditor/Private/NamingTokensEditorModule.h` (Private)


#### class `FNamingTokensEditorModule`  
`class FNamingTokensEditorModule : public IModuleInterface`  
_L8-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Developer/NamingTokens/Source/NamingTokensEditor/Private/NamingTokensStyle.h` (Private)


#### class `FNamingTokensStyle`  
`class FNamingTokensStyle : public FSlateStyleSet`  
_L9-20_
- inherits: `FSlateStyleSet`
- desc: Slate style set for Naming Tokens
- L12 _public member_ `static FName StyleName;`
- L15 _public prototype_ `static FNamingTokensStyle& Get();` — Access the singleton instance for this style set
- L18 _private prototype_ `FNamingTokensStyle();`
- L19 _private prototype_ `~FNamingTokensStyle();`

### `Plugins/Developer/NamingTokens/Source/NamingTokensEditor/Private/Utils/NamingTokensEditorUtils.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NamingTokens` (scope `UE`)
- L9 _namespace_ `namespace Utils` (scope `UE::NamingTokens`)
- L9 _namespace_ `namespace Editor` (scope `UE::NamingTokens::Utils`)
- L9 _namespace_ `namespace Private` (scope `UE::NamingTokens::Utils::Editor`)
- L12 _prototype_ `FString CreateBaseTokenFunctionName(const FString& InTokenKey);` (scope `UE::NamingTokens::Utils::Editor::Private`) — Create the default function token name to use, before unique naming adjustments.
- L15 _prototype_ `FName CreateNewTokenGraph(UBlueprint* InBlueprint, const FString& InTokenKey);` (scope `UE::NamingTokens::Utils::Editor::Private`) — Creates a new k2 graph in a blueprint for a given token key.

### `Plugins/Developer/NamingTokens/Source/NamingTokensEditor/Public/EditorUtilityNamingTokens.h` (Public)


#### class `UEditorUtilityNamingTokens`  
`class UEditorUtilityNamingTokens : public UNamingTokens`  
_L15-25_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract, meta = (ShowWorldContextPin))`
- inherits: `UNamingTokens`
- desc: Subclass to define naming tokens for editor use only.
- L20 _public prototype_ `UEditorUtilityNamingTokens();`
- L22 _public prototype_ `virtual void PostLoad() override;`
- L24 _public prototype_ `virtual bool IsEditorOnly() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API NAMINGTOKENSEDITOR_API`
