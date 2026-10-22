# Plugins / MetaHumanCharacterUAFEditor

- module root: `Plugins/Experimental/MetaHuman/MetaHumanCharacterUAF/Source/MetaHumanCharacterUAFEditor`
- headers: 1; symbols: 7
- symbol kinds: class=1, function=4, member=1, prototype=1
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, MetaHumanCharacterEditor, MetaHumanCharacterPalette, MetaHumanDefaultEditorPipeline, MetaHumanSDKRuntime, RigVMDeveloper, SubobjectDataInterface, UAF, UAFAnimGraph, UAFUncookedOnly

### `Plugins/Experimental/MetaHuman/MetaHumanCharacterUAF/Source/MetaHumanCharacterUAFEditor/Private/MetaHumanCharacterUAFProjectSettings.h` (Private)


#### class `UMetaHumanCharacterUAFProjectSettings`  
`class UMetaHumanCharacterUAFProjectSettings : public UDeveloperSettings`  
_L12-31_
- reflection: `UCLASS(Config = MetaHumanCharacterUAF, DefaultConfig)`
- inherits: `UDeveloperSettings`
- L17 _public prototype_ `UMetaHumanCharacterUAFProjectSettings();`
- L20 _public function_ `virtual FName GetCategoryName() const override`
- L21 _public function_ `virtual FName GetSectionName() const override`
- L23 _public function_ `virtual FText GetSectionText() const override`
- L24 _public function_ `virtual FText GetSectionDescription() const override`
- L30 _public member_ `TMap<EMetaHumanQualityLevel, TSoftClassPtr<AActor>> Blueprints;` — `UPROPERTY(Config, EditAnywhere, Category = "Build", EditFixedSize, NoClear)` — Default actor blueprints to use when assembling a MetaHuman for UAF.
