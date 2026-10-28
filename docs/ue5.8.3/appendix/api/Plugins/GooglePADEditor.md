# Plugins / GooglePADEditor

- module root: `Plugins/Runtime/GooglePAD/Source/GooglePADEditor`
- headers: 2; symbols: 7
- symbol kinds: class=2, member=3, prototype=2
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, UnrealEd

### `Plugins/Runtime/GooglePAD/Source/GooglePADEditor/Public/GooglePADEditor.h` (Public)


#### class `FGooglePADEditorModule`  
`class FGooglePADEditorModule : public IModuleInterface`  
_L10-19_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;`
- L18 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/GooglePAD/Source/GooglePADEditor/Public/GooglePADRuntimeSettings.h` (Public)


#### class `UGooglePADRuntimeSettings`  
`class UGooglePADRuntimeSettings : public UObject`  
_L15-30_
- reflection: `UCLASS(Config = Engine, DefaultConfig)`
- inherits: `UObject`
- desc: Implements the settings for the GooglePAD plugin.
- L21 _private member_ `bool bEnablePlugin;` — `UPROPERTY(EditAnywhere, config, Category = Packaging)` — Enable GooglePAD plugin
- L25 _private member_ `bool bOnlyDistribution;` — `UPROPERTY(EditAnywhere, config, Category = Packaging)` — Only for distribution builds
- L29 _private member_ `bool bOnlyShipping;` — `UPROPERTY(EditAnywhere, config, Category = Packaging)` — Only for shipping builds
