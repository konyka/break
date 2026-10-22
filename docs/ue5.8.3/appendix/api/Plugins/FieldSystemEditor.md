# Plugins / FieldSystemEditor

- module root: `Plugins/Experimental/FieldSystemPlugin/Source/FieldSyStemEditor`
- headers: 6; symbols: 28
- symbol kinds: class=6, function=9, member=3, prototype=10
- PublicDependencyModuleNames: AssetRegistry, AssetTools, Chaos, Core, CoreUObject, EditorFramework, Engine, FieldSystemEngine, PropertyEditor, RHI, RawMesh, RenderCore, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/Experimental/FieldSystemPlugin/Source/FieldSyStemEditor/Private/Field/ActorFactoryFieldSystem.h` (Private)


#### class `UActorFactoryFieldSystem`  
`class UActorFactoryFieldSystem : public UActorFactory`  
_L13-21_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UActorFactory`
- L18 _private prototype_ `virtual void PostSpawnActor( UObject* Asset, AActor* NewActor ) override;`
- L19 _private prototype_ `virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;`

### `Plugins/Experimental/FieldSystemPlugin/Source/FieldSyStemEditor/Private/Field/FieldSystemEditorStyle.h` (Private)


#### class `FFieldSystemEditorStyle`  
`class FFieldSystemEditorStyle final : public FSlateStyleSet`  
_L9-50_
- inherits: `FSlateStyleSet`
- L12 _public function_ `FFieldSystemEditorStyle() : FSlateStyleSet("FieldSystemEditorStyle")`
- L27 _public function_ `~FFieldSystemEditorStyle()`
- L34 _public function_ `static FFieldSystemEditorStyle& Get()`
- L43 _public function_ `static void Destroy()`
- L49 _private member_ `static TOptional<FFieldSystemEditorStyle> Singleton;`

### `Plugins/Experimental/FieldSystemPlugin/Source/FieldSyStemEditor/Public/Field/AssetTypeActions_FieldSystem.h` (Public)


#### class `FAssetTypeActions_FieldSystem`  
`class FAssetTypeActions_FieldSystem : public FAssetTypeActions_Base`  
_L9-20_
- inherits: `FAssetTypeActions_Base`
- L13 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L14 _public prototype_ `virtual void GetActions(const TArray<UObject*>& InObjects, struct FToolMenuSection& Section) override;`
- L15 _public function_ `virtual FColor GetTypeColor() const override`
- L16 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L17 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L18 _public function_ `virtual uint32 GetCategories() override`
- L19 _public prototype_ `virtual UThumbnailInfo* GetThumbnailInfo(UObject* Asset) const override;`

### `Plugins/Experimental/FieldSystemPlugin/Source/FieldSyStemEditor/Public/Field/FieldSystemEditorCommands.h` (Public)


#### class `FFieldSystemCommands`  
`class FFieldSystemCommands`  
_L13-15_
- desc: The public interface to this module

### `Plugins/Experimental/FieldSystemPlugin/Source/FieldSyStemEditor/Public/Field/FieldSystemEditorModule.h` (Public)


#### class `IFieldSystemEditorModule`  
`class IFieldSystemEditorModule : public IModuleInterface`  
_L13-46_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L15 _private member_ `TArray<IConsoleObject*> EditorCommands;`
- L18 _public prototype_ `virtual void StartupModule();`
- L19 _public prototype_ `virtual void ShutdownModule();`
- L28 _public function_ `static inline IFieldSystemEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L38 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L44 _private member_ `class FAssetTypeActions_FieldSystem* AssetTypeActions_FieldSystem;`

### `Plugins/Experimental/FieldSystemPlugin/Source/FieldSyStemEditor/Public/Field/FieldSystemFactory.h` (Public)


#### class `UFieldSystemFactory`  
`class UFieldSystemFactory : public UFactory`  
_L21-31_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L26 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L29 _private prototype_ `static UFieldSystem* StaticFactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn);`
