# Plugins / ChaosSolverEditor

- module root: `Plugins/Experimental/ChaosSolverPlugin/Source/ChaosSolverEditor`
- headers: 7; symbols: 37
- symbol kinds: class=7, function=11, macro=1, member=5, prototype=13
- PrivateDependencyModuleNames: AssetDefinition, EditorStyle
- PublicDependencyModuleNames: AssetRegistry, AssetTools, ChaosSolverEngine, Core, CoreUObject, EditorFramework, Engine, PropertyEditor, RHI, RawMesh, RenderCore, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/Experimental/ChaosSolverPlugin/Source/ChaosSolverEditor/Private/Chaos/ActorFactoryChaosSolver.h` (Private)


#### class `UActorFactoryChaosSolver`  
`class UActorFactoryChaosSolver : public UActorFactory`  
_L13-21_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UActorFactory`
- L18 _private prototype_ `virtual void PostSpawnActor( UObject* Asset, AActor* NewActor ) override;`
- L19 _private prototype_ `virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;`

### `Plugins/Experimental/ChaosSolverPlugin/Source/ChaosSolverEditor/Private/Chaos/AssetDefinition_ChaosSolver.h` (Private)


#### class `UAssetDefinition_ChaosSolver`  
`class UAssetDefinition_ChaosSolver : public UAssetDefinitionDefault`  
_L9-40_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L24 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L29 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L38 _public function_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override`

### `Plugins/Experimental/ChaosSolverPlugin/Source/ChaosSolverEditor/Private/Chaos/ChaosSolverEditorDetails.h` (Private)


#### class `FChaosDebugSubstepControlCustomization`  
`class FChaosDebugSubstepControlCustomization : public IPropertyTypeCustomization`  
_L13-32_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for Chaos debug substep controls.
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L19 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L22 _private prototype_ `FReply OnPause(TSharedRef<IPropertyHandle> PropertyHandle);`
- L23 _private prototype_ `FReply OnSubstep(TSharedRef<IPropertyHandle> PropertyHandle);`
- L24 _private prototype_ `FReply OnStep(TSharedRef<IPropertyHandle> PropertyHandle);`
- L26 _private prototype_ `void RefreshPauseButton(TSharedRef<IPropertyHandle> PropertyHandle, TWeakObjectPtr<UObject> Object);`
- L29 _private member_ `TSharedPtr<STextBlock> TextBlockPause;`
- L30 _private member_ `TSharedPtr<SButton> ButtonStep;`
- L31 _private member_ `TSharedPtr<SButton> ButtonSubstep;`

### `Plugins/Experimental/ChaosSolverPlugin/Source/ChaosSolverEditor/Private/Chaos/ChaosSolverEditorStyle.h` (Private)


#### class `FChaosSolverEditorStyle`  
`class FChaosSolverEditorStyle final : public FSlateStyleSet`  
_L9-50_
- inherits: `FSlateStyleSet`
- L12 _public function_ `FChaosSolverEditorStyle() : FSlateStyleSet("ChaosSolverEditorStyle")`
- L27 _public function_ `~FChaosSolverEditorStyle()`
- L34 _public function_ `static FChaosSolverEditorStyle& Get()`
- L43 _public function_ `static void Destroy()`
- L49 _private member_ `static TOptional<FChaosSolverEditorStyle> Singleton;`

### `Plugins/Experimental/ChaosSolverPlugin/Source/ChaosSolverEditor/Public/Chaos/ChaosSolverEditorCommands.h` (Public)


#### class `FChaosSolverCommands`  
`class FChaosSolverCommands`  
_L12-14_
- desc: The public interface to this module

### `Plugins/Experimental/ChaosSolverPlugin/Source/ChaosSolverEditor/Public/Chaos/ChaosSolverEditorPlugin.h` (Public)


#### class `IChaosSolverEditorPlugin`  
`class IChaosSolverEditorPlugin : public IModuleInterface`  
_L13-42_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L15 _private member_ `TArray<IConsoleObject*> EditorCommands;`
- L18 _public prototype_ `virtual void StartupModule();`
- L19 _public prototype_ `virtual void ShutdownModule();`
- L28 _public function_ `static inline IChaosSolverEditorPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L38 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Experimental/ChaosSolverPlugin/Source/ChaosSolverEditor/Public/Chaos/ChaosSolverFactory.h` (Public)


#### class `UChaosSolverFactory`  
`class UChaosSolverFactory : public UFactory`  
_L21-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L26 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L27 _private prototype_ `static UChaosSolver* StaticFactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHAOSSOLVEREDITOR_API`
