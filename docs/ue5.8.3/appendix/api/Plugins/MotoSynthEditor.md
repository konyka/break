# Plugins / MotoSynthEditor

- module root: `Plugins/Experimental/MotoSynth/Source/MotoSynthEditor`
- headers: 3; symbols: 24
- symbol kinds: class=6, delegate=1, function=7, member=1, prototype=9
- PrivateDependencyModuleNames: AssetDefinition, DeveloperSettings
- PrivateIncludePathModuleNames: AssetTools
- PublicDependencyModuleNames: AudioEditor, AudioMixer, ContentBrowser, Core, CoreUObject, Engine, MotoSynth, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/Experimental/MotoSynth/Source/MotoSynthEditor/Private/MotoSynthSourceFactory.h` (Private)


#### class `UAssetDefinition_MotoSynthPreset`  
`class UAssetDefinition_MotoSynthPreset : public UAssetDefinitionDefault`  
_L14-31_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

#### class `UMotoSynthPresetFactory`  
`class UMotoSynthPresetFactory : public UFactory`  
_L35-42_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- L40 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

#### class `FAssetTypeActions_MotoSynthSource`  
`class FAssetTypeActions_MotoSynthSource : public FAssetTypeActions_Base`  
_L44-51_
- inherits: `FAssetTypeActions_Base`
- L47 _public function_ `virtual FText GetName() const override`
- L48 _public function_ `virtual FColor GetTypeColor() const override`
- L49 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L50 _public function_ `virtual uint32 GetCategories() override`

#### class `UMotoSynthSourceFactory`  
`class UMotoSynthSourceFactory : public UFactory`  
_L54-63_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- L59 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L62 _private member_ `TWeakObjectPtr<USoundWave> StagedSoundWave;`

### `Plugins/Experimental/MotoSynth/Source/MotoSynthEditor/Public/MotoSynthEditorModule.h` (Public)


#### class `FMotoSynthEditorModule`  
`class FMotoSynthEditorModule : public IModuleInterface`  
_L12-22_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _private prototype_ `void RegisterMenus();`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMotoSynthEditor, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMotoSynthEditor, Log, All);`

### `Plugins/Experimental/MotoSynth/Source/MotoSynthEditor/Public/SoundWaveAssetActionExtenderMotoSynth.h` (Public)


#### class `FMotoSynthExtension`  
`class FMotoSynthExtension`  
_L5-10_
- L8 _public prototype_ `static void RegisterMenus();`
- L9 _public prototype_ `static void ExecuteCreateMotoSynthSource(const struct FToolMenuContext& MenuContext);`
