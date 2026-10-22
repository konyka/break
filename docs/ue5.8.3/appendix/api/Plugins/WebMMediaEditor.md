# Plugins / WebMMediaEditor

- module root: `Plugins/Media/WebMMedia/Source/WebMMediaEditor`
- headers: 1; symbols: 3
- symbol kinds: class=1, prototype=2
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, MediaAssets, UnrealEd

### `Plugins/Media/WebMMedia/Source/WebMMediaEditor/Private/WebMFileMediaSourceFactory.h` (Private)


#### class `UWebMPlatFileMediaSourceFactory`  
`class UWebMPlatFileMediaSourceFactory : public UFactory`  
_L14-24_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UFileMediaSource objects.
- L22 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L23 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
