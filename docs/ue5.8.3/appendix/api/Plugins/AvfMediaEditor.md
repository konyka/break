# Plugins / AvfMediaEditor

- module root: `Plugins/Media/AvfMedia/Source/AvfMediaEditor`
- headers: 1; symbols: 3
- symbol kinds: class=1, prototype=2
- PrivateDependencyModuleNames: Core, CoreUObject, MediaAssets, UnrealEd

### `Plugins/Media/AvfMedia/Source/AvfMediaEditor/Private/AvfFileMediaSourceFactory.h` (Private)


#### class `UAvfFileMediaSourceFactory`  
`class UAvfFileMediaSourceFactory : public UFactory`  
_L15-26_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UFileMediaSource objects.
- L24 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L25 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
