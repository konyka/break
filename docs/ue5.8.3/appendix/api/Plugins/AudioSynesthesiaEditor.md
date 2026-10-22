# Plugins / AudioSynesthesiaEditor

- module root: `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaEditor`
- headers: 9; symbols: 44
- symbol kinds: class=9, externvar=1, function=13, member=6, namespace=1, prototype=14
- PrivateDependencyModuleNames: AssetDefinition
- PublicDependencyModuleNames: AudioAnalyzer, AudioEditor, AudioSynesthesia, Core, CoreUObject, EditorFramework, EditorStyle, Engine, InputCore, Slate, SlateCore, UnrealEd

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaEditor/Classes/AudioSynesthesiaNRTFactory.h` (Public)


#### class `UAudioSynesthesiaNRTFactory`  
`class UAudioSynesthesiaNRTFactory : public UFactory`  
_L15-27_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UFactory`
- desc: UAudioSynesthesiaNRTFactory UAudioSynesthesiaNRTFactory implements the factory for UAudioSynesthesiaNRT assets.
- L21 _private member_ `TSubclassOf<UAudioSynesthesiaNRT> AudioSynesthesiaNRTClass;` — `UPROPERTY(EditAnywhere, Category = AudioSynesthesiaFactory)` — The type of audio analyzer settings that will be created
- L24 _private prototype_ `virtual bool ConfigureProperties() override;`
- L25 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaEditor/Classes/AudioSynesthesiaNRTSettingsFactory.h` (Public)


#### class `UAudioSynesthesiaNRTSettingsFactory`  
`class UAudioSynesthesiaNRTSettingsFactory : public UFactory`  
_L15-27_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UFactory`
- desc: UAudioSynesthesiaNRTSettingsFactory UAudioSynesthesiaNRTSettingsFactory implements the factory for UAudioSynesthesiaNRTSettings assets.
- L21 _private member_ `TSubclassOf<UAudioSynesthesiaNRTSettings> AudioSynesthesiaNRTSettingsClass;` — `UPROPERTY(EditAnywhere, Category = AudioSynesthesiaFactory)` — The type of audio analyzer settings that will be created
- L24 _private prototype_ `virtual bool ConfigureProperties() override;`
- L25 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaEditor/Classes/AudioSynesthesiaSettingsFactory.h` (Public)


#### class `UAudioSynesthesiaSettingsFactory`  
`class UAudioSynesthesiaSettingsFactory : public UFactory`  
_L15-27_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UFactory`
- desc: UAudioSynesthesiaSettingsFactory UAudioSynesthesiaSettingsFactory implements the factory for UAudioSynesthesiaSettings assets.
- L21 _private member_ `TSubclassOf<UAudioSynesthesiaSettings> AudioSynesthesiaSettingsClass;` — `UPROPERTY(EditAnywhere, Category = AudioSynesthesiaFactory)` — The type of audio analyzer settings that will be created
- L24 _private prototype_ `virtual bool ConfigureProperties() override;`
- L25 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaEditor/Private/AssetDefinition_AudioSynesthesiaDynamic.h` (Private)


#### class `UAssetDefinition_AudioSynesthesiaDynamic`  
`class UAssetDefinition_AudioSynesthesiaDynamic : public UAssetDefinitionDefault_AudioDiffable`  
_L10-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public function_ `virtual bool CanRegisterStatically() const override`
- L21 _public prototype_ `void Initialize(TSubclassOf<UAudioAnalyzerAssetBase> InClass);`
- L24 _private member_ `TStrongObjectPtr<UAudioAnalyzerAssetBase> SynesthesiaCDO;`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaEditor/Private/AssetDefinition_AudioSynesthesiaNRT.h` (Private)


#### class `UAssetDefinition_AudioSynesthesiaNRT`  
`class UAssetDefinition_AudioSynesthesiaNRT : public UAssetDefinitionDefault_AudioDiffable`  
_L10-29_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L15 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L16 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L17 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L18 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaEditor/Private/AssetDefinition_AudioSynesthesiaNRTSettings.h` (Private)


#### class `UAssetDefinition_AudioSynesthesiaNRTSettings`  
`class UAssetDefinition_AudioSynesthesiaNRTSettings : public UAssetDefinitionDefault_AudioDiffable`  
_L9-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaEditor/Private/AssetDefinition_AudioSynesthesiaSettings.h` (Private)


#### class `UAssetDefinition_AudioSynesthesiaSettings`  
`class UAssetDefinition_AudioSynesthesiaSettings : public UAssetDefinitionDefault_AudioDiffable`  
_L9-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaEditor/Private/AudioSynesthesiaClassFilter.h` (Private)


#### class `Audio::FAssetClassParentFilter`  
`class FAssetClassParentFilter : public IClassViewerFilter`  
_L10-22_
- inherits: `IClassViewerFilter`
- L14 _public member_ `TSet< const UClass* > AllowedChildrenOfClasses;` — All children of these classes will be included unless filtered out by another setting.
- L17 _public member_ `EClassFlags DisallowedClassFlags;` — Disallowed class flags.
- L19 _public prototype_ `virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override;`
- L21 _public prototype_ `virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaEditor/Public/AudioSynesthesiaEditorModule.h` (Public)


#### class `IAudioSynesthesiaEditorModule`  
`class IAudioSynesthesiaEditorModule : public IModuleInterface`  
_L13-18_
- inherits: `IModuleInterface`
- desc: audio analyzer editor module interface
- L17 _public prototype_ `virtual void RegisterAssetActions() = 0;` — Registers audio analyzer asset actions.

#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioSynesthesiaEditor, Log, All);`
- L10 _externvar_ `extern const FName AudioSynesthesiaEditorAppIdentifier;`
