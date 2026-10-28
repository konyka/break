# Plugins / NNERuntimeCoreMLEditor

- module root: `Plugins/Experimental/NNERuntimeCoreML/Source/NNERuntimeCoreMLEditor`
- headers: 2; symbols: 7
- symbol kinds: class=2, prototype=5
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, MainFrame, NNE, NNERuntimeCoreML, NNERuntimeCoreMLUtils, Slate, SlateCore, UnrealEd

### `Plugins/Experimental/NNERuntimeCoreML/Source/NNERuntimeCoreMLEditor/Private/NNERuntimeCoreMLEditorModule.h` (Private)


#### class `FNNERuntimeCoreMLEditorModule`  
`class FNNERuntimeCoreMLEditorModule : public IModuleInterface`  
_L8-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/NNERuntimeCoreML/Source/NNERuntimeCoreMLEditor/Public/NNERuntimeCoreMLModelDataFactory.h` (Public)


#### class `UNNERuntimeCoreMLModelDataFactory`  
`class UNNERuntimeCoreMLModelDataFactory : public UFactory`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L16 _public prototype_ `UNNERuntimeCoreMLModelDataFactory(const FObjectInitializer& ObjectInitializer);`
- L20 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
- L21 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
