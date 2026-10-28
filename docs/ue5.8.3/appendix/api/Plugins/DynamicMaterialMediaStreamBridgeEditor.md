# Plugins / DynamicMaterialMediaStreamBridgeEditor

- module root: `Plugins/Experimental/DynamicMaterialMediaStreamBridge/Source/DynamicMaterialMediaStreamBridgeEditor`
- headers: 3; symbols: 20
- symbol kinds: class=3, member=1, prototype=16
- PrivateDependencyModuleNames: DynamicMaterialEditor, DynamicMaterialMediaStreamBridge, MediaStream, MediaStreamEditor, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DynamicMaterial, Engine

### `Plugins/Experimental/DynamicMaterialMediaStreamBridge/Source/DynamicMaterialMediaStreamBridgeEditor/Private/DMMaterialValueMediaStreamPropertyRowGenerator.h` (Private)


#### class `FDMMaterialValueMediaStreamPropertyRowGenerator`  
`class FDMMaterialValueMediaStreamPropertyRowGenerator : public FDMComponentPropertyRowGenerator`  
_L9-31_
- inherits: `FDMComponentPropertyRowGenerator`
- L12 _public prototype_ `static const TSharedRef<FDMMaterialValueMediaStreamPropertyRowGenerator>& Get();`
- L14 _public prototype_ `virtual ~FDMMaterialValueMediaStreamPropertyRowGenerator() override = default;`
- L17 _public prototype_ `virtual void AddComponentProperties(FDMComponentPropertyRowGeneratorParams& InParams) override;`
- L20 _public prototype_ `void AddControlCategory(FDMComponentPropertyRowGeneratorParams& InParams);`
- L22 _public prototype_ `void AddSourceCategory(FDMComponentPropertyRowGeneratorParams& InParams);`
- L24 _public prototype_ `void AddDetailsCategory(FDMComponentPropertyRowGeneratorParams& InParams);`
- L26 _public prototype_ `void AddTextureCategory(FDMComponentPropertyRowGeneratorParams& InParams, bool bInPreview);`
- L28 _public prototype_ `void AddCacheCategory(FDMComponentPropertyRowGeneratorParams& InParams);`
- L30 _public prototype_ `void AddPlayerProperty(FDMComponentPropertyRowGeneratorParams& InParams);`

### `Plugins/Experimental/DynamicMaterialMediaStreamBridge/Source/DynamicMaterialMediaStreamBridgeEditor/Private/DMMediaStreamStageSourceMenuExtender.h` (Private)


#### class `FDMMediaStreamStageSourceMenuExtender`  
`class FDMMediaStreamStageSourceMenuExtender`  
_L8-25_
- L11 _public prototype_ `static FDMMediaStreamStageSourceMenuExtender& Get();`
- L13 _public prototype_ `void Integrate();`
- L16 _private member_ `bool bIntegrated = false;`
- L18 _private prototype_ `void ExtendMenu_ChangeSource(FToolMenuSection& InSection);`
- L20 _private prototype_ `void ExtendMenu_AddLayer(FToolMenuSection& InSection);`
- L22 _private prototype_ `void ChangeSourceToMediaStreamFromContext(UDMMenuContext* InMenuContext);`
- L24 _private prototype_ `void AddMediaStreamLayerFromContext(UDMMenuContext* InMenuContext);`

### `Plugins/Experimental/DynamicMaterialMediaStreamBridge/Source/DynamicMaterialMediaStreamBridgeEditor/Private/DynamicMaterialMediaStreamBridgeEditorModule.h` (Private)


#### class `FDynamicMaterialMediaStreamBridgeEditorModule`  
`class FDynamicMaterialMediaStreamBridgeEditorModule : public IModuleInterface`  
_L10-16_
- inherits: `IModuleInterface`
- desc: Media Stream Material Designer Bridge Editor - Integrates the Media Stream plugin with the Material Designer.
- L14 _public prototype_ `virtual void StartupModule() override;`
