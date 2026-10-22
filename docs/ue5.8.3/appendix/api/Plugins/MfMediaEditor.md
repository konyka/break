# Plugins / MfMediaEditor

- module root: `Plugins/Media/MfMedia/Source/MfMediaEditor`
- headers: 1; symbols: 3
- symbol kinds: class=1, prototype=2
- PrivateDependencyModuleNames: Core, CoreUObject, MediaAssets, UnrealEd

### `Plugins/Media/MfMedia/Source/MfMediaEditor/Private/MfFileMediaSourceFactory.h` (Private)


#### class `UMfFileMediaSourceFactory`  
`class UMfFileMediaSourceFactory : public UFactory`  
_L14-25_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UFileMediaSource objects.
- L23 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L24 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
