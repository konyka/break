# Plugins / NNEModelTestsEditor

- module root: `Plugins/Experimental/NNE/NNEModelTests/Source/NNEModelTestsEditor`
- headers: 2; symbols: 16
- symbol kinds: class=3, delegate=1, prototype=12
- PrivateDependencyModuleNames: AssetTools, Engine, NNE, NNEModelTests
- PublicDependencyModuleNames: Core, CoreUObject, UnrealEd

### `Plugins/Experimental/NNE/NNEModelTests/Source/NNEModelTestsEditor/Private/NNEModelTestsEditorModule.h` (Private)


#### class `FNNEModelTestsEditorModule`  
`class FNNEModelTestsEditorModule : public IModuleInterface`  
_L8-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/NNE/NNEModelTests/Source/NNEModelTestsEditor/Public/NNEModelTestsFactory.h` (Public)


#### class `UNNEModelTestsFactory`  
`class UNNEModelTestsFactory : public UFactory, public FReimportHandler`  
_L15-33_
- reflection: `UCLASS()`
- inherits: `UFactory,FReimportHandler`
- L20 _public prototype_ `UNNEModelTestsFactory(const FObjectInitializer& ObjectInitializer);`
- L24 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
- L25 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L29 _public prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L30 _public prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L31 _public prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`

#### class `UNNEModelTestsDataFactory`  
`class UNNEModelTestsDataFactory : public UFactory`  
_L36-48_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L41 _public prototype_ `UNNEModelTestsDataFactory(const FObjectInitializer& ObjectInitializer);`
- L45 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
- L46 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNEModelTestsFactory, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNEModelTestsFactory, Log, All);`
