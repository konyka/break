# Plugins / MetasoundExperimentalEditor

- module root: `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalEditor`
- headers: 5; symbols: 46
- symbol kinds: class=6, function=2, member=10, prototype=28
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AssetDefinition, AssetTools, AudioEditor, AudioWidgets, ContentBrowser, CoreUObject, Engine, MetasoundEditor, MetasoundEngine, MetasoundExperimentalEngineRuntime, MetasoundExperimentalRuntime, MetasoundFrontend, MetasoundGraphCore, PropertyEditor, Slate, SlateCore, StructUtilsEditor, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalEditor/Private/AssetDefinitions/AssetDefinition_CatSoundWaveContainer.h` (Private)


#### class `UAssetDefinition_CatSoundWaveContainer`  
`class UAssetDefinition_CatSoundWaveContainer : public UAssetDefinitionDefault`  
_L12-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L21 _public prototype_ `virtual bool CanImport() const override;`

#### class `FCatSoundWaveContainerExtension`  
`class FCatSoundWaveContainerExtension`  
_L24-29_
- L27 _public prototype_ `static void RegisterMenus();`
- L28 _public prototype_ `static void Execute(const FToolMenuContext& MenuContext);`

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalEditor/Private/CatSoundWaveContainerFactory.h` (Private)


#### class `UCatSoundWaveContainerFactory`  
`class UCatSoundWaveContainerFactory : public UFactory`  
_L10-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L15 _public prototype_ `UCatSoundWaveContainerFactory();`
- L17 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalEditor/Private/MetasoundExampleNodeDetailsCustomization.h` (Private)


#### class `FExampleWidgetNodeConfigurationCustomization`  
`class FExampleWidgetNodeConfigurationCustomization : public Metasound::Editor::FMetaSoundNodeConfigurationCustomization`  
_L6-18_
- inherits: `Metasound::Editor::FMetaSoundNodeConfigurationCustomization`
- L9 _public prototype_ `FExampleWidgetNodeConfigurationCustomization(TSharedPtr<IPropertyHandle> InStructProperty, TWeakObjectPtr<UMetasoundEditorGraphNode> InNode);`
- L11 _public prototype_ `virtual void OnChildRowAdded(IDetailPropertyRow& ChildRow) override;`
- L14 _private prototype_ `void OnChildPropertyChanged(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L16 _private member_ `FString StructPropertyPath;`
- L17 _private member_ `TSharedPtr<IPropertyHandle> MyFloatPropertyHandle;`

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalEditor/Private/MetasoundGranularNodeDetailsCustomization.h` (Private)


#### class `FGranularNodeConfigurationCustomization`  
`class FGranularNodeConfigurationCustomization : public Metasound::Editor::FMetaSoundNodeConfigurationCustomization`  
_L6-18_
- inherits: `Metasound::Editor::FMetaSoundNodeConfigurationCustomization`
- L9 _public prototype_ `FGranularNodeConfigurationCustomization(TSharedPtr<IPropertyHandle> InStructProperty, TWeakObjectPtr<UMetasoundEditorGraphNode> InNode);`
- L11 _public prototype_ `virtual void OnChildRowAdded(IDetailPropertyRow& ChildRow) override;`
- L14 _private prototype_ `void OnChildPropertyChanged(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L16 _private member_ `FString StructPropertyPath;`
- L17 _private member_ `TSharedPtr<IPropertyHandle> EnvelopeTypePropertyHandle;`

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalEditor/Private/MetasoundMappingFunctionDetailsCustomization.h` (Private)


#### class `FMappingFunctionNodeConfigurationCustomization`  
`class FMappingFunctionNodeConfigurationCustomization : public Metasound::Editor::FMetaSoundNodeConfigurationCustomization, public FCurveOwnerInterface`  
_L8-39_
- inherits: `Metasound::Editor::FMetaSoundNodeConfigurationCustomization,FCurveOwnerInterface`
- L11 _public prototype_ `FMappingFunctionNodeConfigurationCustomization(TSharedPtr<IPropertyHandle> InStructProperty, TWeakObjectPtr<UMetasoundEditorGraphNode> InNode);`
- L13 _public prototype_ `virtual void OnChildRowAdded(IDetailPropertyRow& ChildRow) override;`
- L16 _public prototype_ `virtual TArray<FRichCurveEditInfo> GetCurves() override;` — FCurveOwnerInterface interface
- L17 _public prototype_ `virtual void GetCurves(TAdderReserverRef<FRichCurveEditInfoConst> Curves) const override;`
- L18 _public prototype_ `virtual TArray<FRichCurveEditInfoConst> GetCurves() const override;`
- L19 _public function_ `virtual bool HasRichCurves() const override`
- L20 _public function_ `virtual bool IsLinearColorCurve() const override`
- L21 _public prototype_ `virtual bool IsValidCurve(FRichCurveEditInfo CurveInfo) override;`
- L22 _public prototype_ `virtual void MakeTransactional() override;`
- L23 _public prototype_ `virtual void ModifyOwner() override;`
- L24 _public prototype_ `virtual void ModifyOwnerChange() override;`
- L25 _public prototype_ `virtual void OnCurveChanged(const TArray<FRichCurveEditInfo>& ChangedCurveEditInfos) override;`
- L26 _public prototype_ `virtual TArray<const UObject*> GetOwners() const override;`
- L29 _private prototype_ `void OnChildPropertyChanged(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L30 _private prototype_ `void UpdateMappingFunctionData();`
- L32 _private member_ `FString StructPropertyPath;`
- L33 _private member_ `TSharedPtr<IPropertyHandle> CurvePropertyHandle;`
- L34 _private member_ `TSharedPtr<IPropertyHandle> bWrapInputsPropertyHandle;`
- L36 _private member_ `FRuntimeFloatCurve* RuntimeCurve = nullptr;`
- L37 _private member_ `TArray<UObject*> OwnerObjects;`
- L38 _private member_ `TSharedPtr<SCurveEditor> CurveEditorWidget;`
