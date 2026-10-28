# Plugins / MetaHumanGenerator

- module root: `Plugins/Experimental/Toolsets/MetaHumanGenerator/Source`
- headers: 1; symbols: 8
- symbol kinds: class=2, delegate=1, prototype=5
- PrivateDependencyModuleNames: CoreUObject, Engine, MetaHumanCharacter, MetaHumanCharacterEditor, MetaHumanCoreTechLib, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/Toolsets/MetaHumanGenerator/Source/Public/MetaHumanGenerator.h` (Public)


#### class `FMetaHumanGeneratorModule`  
`class FMetaHumanGeneratorModule : public IModuleInterface`  
_L15-20_
- inherits: `IModuleInterface`
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`

#### class `UMetaHumanGeneratorSubsystemWrapper`  
`class UMetaHumanGeneratorSubsystemWrapper : public UObject`  
_L23-34_
- reflection: `UCLASS()`
- inherits: `UObject`
- L29 _public prototype_ `static void ResetNeckToBody(UMetaHumanCharacter* InCharacter);` — `UFUNCTION(BlueprintCallable, Category = "MetaHumanGenerator")`
- L33 _private prototype_ `static bool IsOptionalContentInstalled();` — `UFUNCTION(BlueprintCallable, Category = "MetaHumanGenerator")`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanGenerator, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanGenerator, Log, All);`
