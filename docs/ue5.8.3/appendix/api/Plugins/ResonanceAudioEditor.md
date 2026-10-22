# Plugins / ResonanceAudioEditor

- module root: `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudioEditor`
- headers: 6; symbols: 27
- symbol kinds: class=6, delegate=1, function=11, member=1, namespace=1, prototype=7
- PrivateDependencyModuleNames: AssetDefinition, EditorFramework, Eigen, Landscape, Projects, PropertyEditor, Slate, SlateCore
- PublicDependencyModuleNames: AudioEditor, AudioMixer, Core, CoreUObject, Engine, InputCore, LevelEditor, RHI, RenderCore, ResonanceAudio, UnrealEd

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudioEditor/Private/AssetDefinition_ResonanceAudioReverbPluginPreset.h` (Private)


#### class `UAssetDefinition_ResonanceAudioReverbPluginPreset`  
`class UAssetDefinition_ResonanceAudioReverbPluginPreset : public UAssetDefinitionDefault`  
_L12-34_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual bool CanRegisterStatically() const override`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudioEditor/Private/AssetDefinition_ResonanceAudioSpatializationSourceSettings.h` (Private)


#### class `UAssetDefinition_ResonanceAudioSpatializationSourceSettings`  
`class UAssetDefinition_ResonanceAudioSpatializationSourceSettings : public UAssetDefinitionDefault`  
_L12-33_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudioEditor/Private/ResonanceAudioEditorModule.h` (Private)


#### class `ResonanceAudio::FResonanceAudioEditorModule`  
`class FResonanceAudioEditorModule : public IResonanceAudioEditorModule`  
_L15-23_
- inherits: `IResonanceAudioEditorModule`
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _private member_ `TSharedPtr<FSlateStyleSet> ResonanceAudioStyleSet;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogResonanceAudioEditor, Warning, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogResonanceAudioEditor, Warning, All);`
- L13 _namespace_ `namespace ResonanceAudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudioEditor/Private/ResonanceAudioReverbPluginPresetFactory.h` (Private)


#### class `UResonanceAudioReverbPluginPresetFactory`  
`class UResonanceAudioReverbPluginPresetFactory : public UFactory`  
_L11-17_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- L15 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L16 _private prototype_ `virtual uint32 GetMenuCategories() const override;`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudioEditor/Private/ResonanceAudioSpatializationSourceSettingsFactory.h` (Private)


#### class `UResonanceAudioSpatializationSourceSettingsFactory`  
`class UResonanceAudioSpatializationSourceSettingsFactory : public UFactory`  
_L11-17_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- L15 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L16 _private prototype_ `virtual uint32 GetMenuCategories() const override;`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudioEditor/Public/IResonanceAudioEditorModule.h` (Public)


#### class `IResonanceAudioEditorModule`  
`class IResonanceAudioEditorModule : public IModuleInterface`  
_L9-32_
- inherits: `IModuleInterface`
- L18 _public function_ `static inline IResonanceAudioEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L28 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
