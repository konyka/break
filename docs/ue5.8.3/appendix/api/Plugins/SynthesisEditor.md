# Plugins / SynthesisEditor

- module root: `Plugins/Runtime/Synthesis/Source/SynthesisEditor`
- headers: 5; symbols: 35
- symbol kinds: class=9, delegate=1, function=9, member=2, prototype=14
- PrivateDependencyModuleNames: AssetDefinition, AudioSynesthesiaCore, DeveloperSettings, SignalProcessing, UMG, UMGEditor
- PrivateIncludePathModuleNames: AssetTools
- PublicDependencyModuleNames: AudioEditor, AudioMixer, ContentBrowser, Core, CoreUObject, EditorFramework, Engine, Slate, SlateCore, Synthesis, ToolMenus, UnrealEd

### `Plugins/Runtime/Synthesis/Source/SynthesisEditor/Classes/AudioImpulseResponseAsset.h` (Public)


#### class `FAssetTypeActions_AudioImpulseResponse`  
`class FAssetTypeActions_AudioImpulseResponse : public FAssetTypeActions_Base`  
_L11-18_
- inherits: `FAssetTypeActions_Base`
- L14 _public function_ `virtual FText GetName() const override`
- L15 _public function_ `virtual FColor GetTypeColor() const override`
- L16 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L17 _public function_ `virtual uint32 GetCategories() override`

#### class `FAudioImpulseResponseExtension`  
`class FAudioImpulseResponseExtension`  
_L20-25_
- L23 _public prototype_ `static void RegisterMenus();`
- L24 _public prototype_ `static void ExecuteCreateImpulseResponse(const struct FToolMenuContext& MenuContext);`

#### class `UAudioImpulseResponseFactory`  
`class UAudioImpulseResponseFactory : public UFactory`  
_L29-41_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- L34 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L37 _private member_ `TWeakObjectPtr<USoundWave> StagedSoundWave;`
- L40 _private member_ `Audio::FSoundWavePCMLoader Loader;`

### `Plugins/Runtime/Synthesis/Source/SynthesisEditor/Classes/EpicSynth1PresetBank.h` (Public)


#### class `FAssetTypeActions_ModularSynthPresetBank`  
`class FAssetTypeActions_ModularSynthPresetBank : public FAssetTypeActions_Base`  
_L9-17_
- inherits: `FAssetTypeActions_Base`
- L12 _public function_ `virtual FText GetName() const override`
- L13 _public function_ `virtual FColor GetTypeColor() const override`
- L14 _public prototype_ `virtual const TArray<FText>& GetSubMenus() const override;`
- L15 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L16 _public function_ `virtual uint32 GetCategories() override`

#### class `UModularSynthPresetBankFactory`  
`class UModularSynthPresetBankFactory : public UFactory`  
_L20-27_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- L25 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Runtime/Synthesis/Source/SynthesisEditor/Classes/MonoWaveTablePresetBank.h` (Public)


#### class `FAssetTypeActions_MonoWaveTableSynthPreset`  
`class FAssetTypeActions_MonoWaveTableSynthPreset : public FAssetTypeActions_Base`  
_L9-17_
- inherits: `FAssetTypeActions_Base`
- L12 _public function_ `virtual FText GetName() const override`
- L13 _public function_ `virtual FColor GetTypeColor() const override`
- L14 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L15 _public prototype_ `virtual const TArray<FText>& GetSubMenus() const override;`
- L16 _public function_ `virtual uint32 GetCategories() override`

#### class `UMonoWaveTableSynthPresetFactory`  
`class UMonoWaveTableSynthPresetFactory : public UFactory`  
_L20-27_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- L25 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Runtime/Synthesis/Source/SynthesisEditor/Classes/SynthesisEditorSettings.h` (Public)


#### class `USynthesisEditorSettings`  
`class USynthesisEditorSettings : public UDeveloperSettings`  
_L11-14_
- reflection: `UCLASS(config = EditorSettings, defaultconfig, meta = (DisplayName = "Synthesis and DSP Plugin"))`
- inherits: `UDeveloperSettings`

### `Plugins/Runtime/Synthesis/Source/SynthesisEditor/Public/SynthesisEditorModule.h` (Public)


#### class `FSynthesisEditorModule`  
`class FSynthesisEditorModule : public IModuleInterface`  
_L12-22_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _private prototype_ `void RegisterMenus();`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSynthesisEditor, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSynthesisEditor, Log, All);`
