# Plugins / NNERuntimeIREEEditor

- module root: `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREEEditor`
- headers: 2; symbols: 7
- symbol kinds: class=2, prototype=5
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, MainFrame, NNE, NNERuntimeIREE, Slate, SlateCore, UnrealEd

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREEEditor/Private/NNERuntimeIREEEditorModule.h` (Private)


#### class `FNNERuntimeIREEEditorModule`  
`class FNNERuntimeIREEEditorModule : public IModuleInterface`  
_L8-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREEEditor/Public/NNERuntimeIREEModelDataFactory.h` (Public)


#### class `UNNERuntimeIREEModelDataFactory`  
`class UNNERuntimeIREEModelDataFactory : public UFactory`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L16 _public prototype_ `UNNERuntimeIREEModelDataFactory(const FObjectInitializer& ObjectInitializer);`
- L20 _public prototype_ `virtual UObject* FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn) override;`
- L21 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
