# Plugins / InterchangeEditorUtilities

- module root: `Plugins/Interchange/Editor/Source/Utilities`
- headers: 3; symbols: 12
- symbol kinds: class=3, function=2, macro=2, prototype=5
- PrivateDependencyModuleNames: DesktopPlatform, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InterchangeCore, InterchangeEngine

### `Plugins/Interchange/Editor/Source/Utilities/Public/InterchangeEditorUtilities.h` (Public)


#### class `UInterchangeEditorUtilities`  
`class UInterchangeEditorUtilities : public UInterchangeEditorUtilitiesBase`  
_L12-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeEditorUtilitiesBase`
- L20 _protected prototype_ `virtual bool SaveAsset(UObject* Asset) const override;`
- L22 _protected prototype_ `virtual bool IsRuntimeOrPIE() const override;`
- L24 _protected prototype_ `virtual bool ClearEditorSelection() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEEDITORUTILITIES_API`

### `Plugins/Interchange/Editor/Source/Utilities/Public/InterchangeEditorUtilitiesModule.h` (Public)


#### class `IInterchangeEditorUtilitiesModule`  
`class IInterchangeEditorUtilitiesModule : public IModuleInterface`  
_L11-36_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L22 _public function_ `static inline IInterchangeEditorUtilitiesModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Interchange/Editor/Source/Utilities/Public/InterchangeOpenFileDialog.h` (Public)


#### class `UInterchangeFilePickerGeneric`  
`class UInterchangeFilePickerGeneric : public UInterchangeFilePickerBase`  
_L12-22_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `UInterchangeFilePickerBase`
- L20 _protected prototype_ `virtual bool FilePickerForTranslatorAssetType(const EInterchangeTranslatorAssetType TranslatorAssetType, const FInterchangeFilePickerParameters& Parameters, TArray<FString>& OutFilenames) override;`
- L21 _protected prototype_ `virtual bool FilePickerForTranslatorType(const EInterchangeTranslatorType TranslatorType, const FInterchangeFilePickerParameters& Parameters, TArray<FString>& OutFilenames) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEEDITORUTILITIES_API`
