# Plugins / PPMChainGraphEditor

- module root: `Plugins/Experimental/PostProcessMaterialChainGraph/Source/PostProcessMaterialChainGraphEditor`
- headers: 7; symbols: 35
- symbol kinds: class=7, delegate=1, function=5, member=3, prototype=19
- PrivateDependencyModuleNames: AssetDefinition, Core, CoreUObject, EditorFramework, PPMChainGraph, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: 

### `Plugins/Experimental/PostProcessMaterialChainGraph/Source/PostProcessMaterialChainGraphEditor/Private/AssetDefinition_PPMChainGraph.h` (Private)


#### class `UAssetDefinition_PPMChainGraph`  
`class UAssetDefinition_PPMChainGraph : public UAssetDefinitionDefault`  
_L10-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L21 _public function_ `virtual bool CanImport() const override`
- L23 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L24 _public prototype_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override;`
- L25 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L26 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`

### `Plugins/Experimental/PostProcessMaterialChainGraph/Source/PostProcessMaterialChainGraphEditor/Private/Customizations/PPMChainGraphCustomization.h` (Private)


#### class `FPPMChainGraphCustomization`  
`class FPPMChainGraphCustomization : public IDetailCustomization`  
_L9-18_
- inherits: `IDetailCustomization`
- L12 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/Experimental/PostProcessMaterialChainGraph/Source/PostProcessMaterialChainGraphEditor/Private/Customizations/PPMChainGraphInputCustomization.h` (Private)


#### class `FPPMChainGraphInputCustomization`  
`class FPPMChainGraphInputCustomization : public IPropertyTypeCustomization`  
_L14-40_
- inherits: `IPropertyTypeCustomization`
- L17 _public prototype_ `FPPMChainGraphInputCustomization(TWeakObjectPtr<UPPMChainGraph> InConfigurationObjectProperty);`
- L20 _public function_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override` — IPropertyTypeCustomization interface stub.
- L22 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(TWeakObjectPtr<UPPMChainGraph> InConfigurationObjectProperty)`
- L27 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override;`
- L31 _protected member_ `TSharedPtr<IPropertyHandle> CachedInputsProperty;`
- L32 _protected member_ `TSharedPtr<IPropertyHandle> CachedPassProperty;`
- L34 _protected member_ `TWeakObjectPtr<UPPMChainGraph> PPMChainGraphPtr;`
- L37 _private prototype_ `void AddComboBoxEntry(FMenuBuilder& InMenuBuilder, const FPPMChainGraphInput& InTextureInput);`
- L39 _private prototype_ `TSharedRef<SWidget> PopulateComboBox();`

### `Plugins/Experimental/PostProcessMaterialChainGraph/Source/PostProcessMaterialChainGraphEditor/Private/Factories/ActorFactoryPPMChainGraphActor.h` (Private)


#### class `UActorFactoryPPMChainGraphActor`  
`class UActorFactoryPPMChainGraphActor : public UActorFactory`  
_L11-25_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L16 _private prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L17 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`
- L24 _private prototype_ `void SetUpActor(UObject* Asset, AActor* Actor);` — Set up a PPM Chain Graph Actor.

### `Plugins/Experimental/PostProcessMaterialChainGraph/Source/PostProcessMaterialChainGraphEditor/Private/Factories/PPMChainGraphFactoryNew.h` (Private)


#### class `UPPMChainGraphFactoryNew`  
`class UPPMChainGraphFactoryNew : public UFactory`  
_L11-22_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- L19 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L20 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L21 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Experimental/PostProcessMaterialChainGraph/Source/PostProcessMaterialChainGraphEditor/Private/PPMChainGraphEditorModule.h` (Private)


#### class `FPPMChainGraphEditorModule`  
`class FPPMChainGraphEditorModule : public IPPMChainGraphEditorModule, public TSharedFromThis<FPPMChainGraphEditorModule>`  
_L9-19_
- inherits: `IPPMChainGraphEditorModule,TSharedFromThis<FPPMChainGraphEditorModule>`
- L13 _public prototype_ `virtual ~FPPMChainGraphEditorModule() = default;`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/PostProcessMaterialChainGraph/Source/PostProcessMaterialChainGraphEditor/Public/IPPMChainGraphEditorModule.h` (Public)


#### class `IPPMChainGraphEditorModule`  
`class IPPMChainGraphEditorModule : public IModuleInterface`  
_L12-15_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPPMChainGraphEditor, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPPMChainGraphEditor, Log, All);`
