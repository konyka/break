# Plugins / AndroidMediaEditor

- module root: `Plugins/Media/AndroidMedia/Source/AndroidMediaEditor`
- headers: 1; symbols: 3
- symbol kinds: class=1, prototype=2
- PrivateDependencyModuleNames: Core, CoreUObject, MediaAssets, UnrealEd

### `Plugins/Media/AndroidMedia/Source/AndroidMediaEditor/Private/AndroidFileMediaSourceFactory.h` (Private)


#### class `UAndroidFileMediaSourceFactory`  
`class UAndroidFileMediaSourceFactory : public UFactory`  
_L12-23_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UFileMediaSource objects.
- L21 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L22 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
