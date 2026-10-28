# Plugins / SoundModImporter

- module root: `Plugins/Runtime/SoundMod/Source/SoundModImporter`
- headers: 3; symbols: 17
- symbol kinds: class=2, delegate=1, function=4, prototype=10
- DynamicallyLoadedModuleNames: AssetRegistry, AssetTools
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, Slate, SlateCore, SoundMod, ToolMenus, UnrealEd
- PrivateIncludePathModuleNames: AssetTools

### `Plugins/Runtime/SoundMod/Source/SoundModImporter/Classes/SoundModImporterFactory.h` (Public)


#### class `USoundModImporterFactory`  
`class USoundModImporterFactory : public UFactory`  
_L12-19_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: Imports a sound module file
- L17 _private prototype_ `virtual UObject* FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn) override;` — UFactory interface

### `Plugins/Runtime/SoundMod/Source/SoundModImporter/Private/AssetTypeActions_SoundMod.h` (Private)


#### class `FAssetTypeActions_SoundMod`  
`class FAssetTypeActions_SoundMod: public FAssetTypeActions_Base`  
_L9-36_
- inherits: `FAssetTypeActions_Base`
- L13 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L14 _public function_ `virtual FColor GetTypeColor() const override`
- L15 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L16 _public prototype_ `virtual void GetActions(const TArray<UObject*>& InObjects, struct FToolMenuSection& Section) override;`
- L17 _public prototype_ `virtual bool AssetsActivatedOverride(const TArray<UObject*>& InObjects, EAssetTypeActivationMethod::Type ActivationType) override;`
- L18 _public function_ `virtual uint32 GetCategories() override`
- L19 _public function_ `virtual bool CanFilter() override`
- L23 _private prototype_ `void ExecutePlaySound(TArray<TWeakObjectPtr<USoundMod>> Objects);` — Handler for when PlaySound is selected
- L26 _private prototype_ `void ExecuteStopSound(TArray<TWeakObjectPtr<USoundMod>> Objects);` — Handler for when StopSound is selected
- L29 _private prototype_ `bool CanExecutePlayCommand(TArray<TWeakObjectPtr<USoundMod>> Objects) const;` — Returns true if only one sound is selected to play
- L32 _private prototype_ `void PlaySound(USoundMod* Sound);` — Plays the specified sound wave
- L35 _private prototype_ `void StopSound();` — Stops any currently playing sounds

### `Plugins/Runtime/SoundMod/Source/SoundModImporter/Private/SoundModImporterPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSoundModImporter, Verbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSoundModImporter, Verbose, All);`
