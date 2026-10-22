# Plugins / ChaosOutfitAssetEditor

- module root: `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEditor`
- headers: 6; symbols: 43
- symbol kinds: class=5, function=5, member=2, namespace=12, prototype=19
- PrivateDependencyModuleNames: AssetDefinition, BaseCharacterFXEditor, ChaosClothAsset, ChaosClothAssetEngine, ChaosClothAssetTools, ChaosOutfitAssetEngine, ContentBrowser, Core, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, Engine, GeometryCore, GeometryFramework, InputCore, InteractiveToolsFramework, Projects, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEditor/Private/ChaosOutfitAsset/AssetDefinition_OutfitAsset.h` (Private)


#### class `UAssetDefinition_OutfitAsset`  
`class UAssetDefinition_OutfitAsset final : public UAssetDefinitionDefault`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _private prototype_ `virtual FText GetAssetDisplayName() const override;`
- L15 _private prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L16 _private prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _private prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L18 _private prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`
- L20 _private prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEditor/Private/ChaosOutfitAsset/OutfitAssetEditorStyle.h` (Private)


#### class `UE::Chaos::OutfitAsset::FOutfitAssetEditorStyle`  
`class FOutfitAssetEditorStyle final : public FSlateStyleSet`  
_L13-24_
- inherits: `FSlateStyleSet`
- desc: Editor style setting up the outfit asset icons in editor.
- L16 _public prototype_ `static FOutfitAssetEditorStyle& Get();`
- L17 _public prototype_ `static void TearDown();`
- L22 _private prototype_ `FOutfitAssetEditorStyle();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Chaos` (scope `UE`)
- L8 _namespace_ `namespace OutfitAsset` (scope `UE::Chaos`)

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEditor/Private/ChaosOutfitAsset/OutfitAssetFactory.h` (Private)


#### class `UChaosOutfitAssetFactory`  
`class UChaosOutfitAssetFactory final : public UFactory`  
_L12-26_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: Allows the Outfit Asset to be created from the Editor's menus.
- L16 _public prototype_ `UChaosOutfitAssetFactory(const FObjectInitializer& ObjectInitializer);`
- L20 _private function_ `virtual bool CanCreateNew() const override`
- L21 _private function_ `virtual bool FactoryCanImport(const FString& Filename) override`
- L22 _private function_ `virtual bool ShouldShowInNewMenu() const override`
- L23 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L24 _private prototype_ `virtual FString GetDefaultNewAssetName() const override;`

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEditor/Private/ChaosOutfitAsset/OutfitEditorCommands.h` (Private)


#### class `UE::Chaos::OutfitAsset::FOutfitEditorCommands`  
`class FOutfitEditorCommands final : public TBaseCharacterFXEditorCommands<FOutfitEditorCommands>`  
_L9-36_
- inherits: `TBaseCharacterFXEditorCommands<FOutfitEditorCommands>`
- L12 _public prototype_ `FOutfitEditorCommands();`
- L19 _public prototype_ `static void UpdateToolCommandBinding(UInteractiveTool* Tool, TSharedPtr<FUICommandList> UICommandList, bool bUnbind = false);` — Add or remove commands relevant to Tool to the given UICommandList. Call this when the active tool changes (e.g. on ToolManager.OnToolStarted / OnToolEnded). @param bUnbind if true, commands are removed, otherwise added.
- L21 _public function_ `const TSharedPtr<FUICommandInfo>& GetConvertToSkeletalMesh() const`
- L30 _private prototype_ `virtual void RegisterCommands() override;`
- L32 _private function_ `virtual void GetToolDefaultObjectList(TArray<UInteractiveTool*>& ToolCDOs) override`
- L35 _private member_ `TSharedPtr<FUICommandInfo> ConvertToSkeletalMesh;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Chaos` (scope `UE`)
- L7 _namespace_ `namespace OutfitAsset` (scope `UE::Chaos`)

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEditor/Private/ChaosOutfitAsset/OutfitEditorStyle.h` (Private)


#### class `UE::Chaos::OutfitAsset::FOutfitEditorStyle`  
`class FOutfitEditorStyle final : public FSlateStyleSet`  
_L13-26_
- inherits: `FSlateStyleSet`
- desc: Slate style set for Cloth Editor.
- L16 _public member_ `static inline const FName StyleName = "Ou`
- L18 _public prototype_ `static FOutfitEditorStyle& Get();`
- L19 _public prototype_ `static void TearDown();`
- L24 _private prototype_ `FOutfitEditorStyle();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Chaos` (scope `UE`)
- L8 _namespace_ `namespace OutfitAsset` (scope `UE::Chaos`)

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEditor/Private/ChaosOutfitAsset/OutfitRenderableTypes.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace Chaos` (scope `UE`)
- L5 _namespace_ `namespace OutfitAsset` (scope `UE::Chaos`)
- L7 _prototype_ `void RegisterOutfitRenderableTypes();` (scope `UE::Chaos::OutfitAsset`)
