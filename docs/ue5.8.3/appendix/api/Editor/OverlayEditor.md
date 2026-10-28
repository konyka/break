# Editor / OverlayEditor

- module root: `Source/Editor/OverlayEditor`
- headers: 6; symbols: 20
- symbol kinds: class=5, delegate=1, prototype=14
- DynamicallyLoadedModuleNames: AssetTools
- PrivateDependencyModuleNames: EditorFramework, Engine, UnrealEd
- PrivateIncludePathModuleNames: AssetTools, TargetPlatform
- PublicDependencyModuleNames: Core, CoreUObject, Overlay

### `Source/Editor/OverlayEditor/Private/Factories/BasicOverlaysFactory.h` (Private)


#### class `UBasicOverlaysFactory`  
`class UBasicOverlaysFactory : public UFactory`  
_L22-32_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UBasicOverlays objects.
- L30 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename);`
- L31 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`

### `Source/Editor/OverlayEditor/Private/Factories/BasicOverlaysFactoryNew.h` (Private)


#### class `UBasicOverlaysFactoryNew`  
`class UBasicOverlaysFactoryNew : public UFactory`  
_L21-33_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for new UBasicOverlays objects.
- L30 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L31 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L32 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Source/Editor/OverlayEditor/Private/Factories/LocalizedOverlaysFactoryNew.h` (Private)


#### class `ULocalizedOverlaysFactoryNew`  
`class ULocalizedOverlaysFactoryNew : public UFactory`  
_L20-32_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- desc: Implements a factory for new ULocalizedOverlays objects.
- L29 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L30 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L31 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Source/Editor/OverlayEditor/Private/Factories/ReimportBasicOverlaysFactory.h` (Private)


#### class `UReimportBasicOverlaysFactory`  
`class UReimportBasicOverlaysFactory : public UBasicOverlaysFactory, public FReimportHandler`  
_L20-30_
- reflection: `UCLASS(HideCategories=Object)`
- inherits: `UBasicOverlaysFactory,FReimportHandler`
- desc: A factory for reimporting basic overlays
- L25 _private prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L26 _private prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L27 _private prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L28 _private prototype_ `virtual int32 GetPriority() const override;`

### `Source/Editor/OverlayEditor/Private/OverlayEditorPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOverlayEditor, Log, All);` — Declares a log category for this module.
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOverlayEditor, Log, All);` — Declares a log category for this module.

### `Source/Editor/OverlayEditor/Public/IOverlayEditorModule.h` (Public)


#### class `IOverlayEditorModule`  
`class IOverlayEditorModule : public IModuleInterface`  
_L10-16_
- inherits: `IModuleInterface`
- desc: Interface for the OverlayEditor module
- L15 _public prototype_ `virtual ~IOverlayEditorModule() = default;` — Virtual destructor
