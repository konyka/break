# Plugins / PSDImporterMaterialDesignerBridge

- module root: `Plugins/Experimental/PSDImporterMaterialDesignerBridge/Source`
- headers: 7; symbols: 51
- symbol kinds: class=5, delegate=1, enum=1, enumerator=2, member=2, namespace=2, prototype=28, variable=10
- PrivateDependencyModuleNames: Core, CoreUObject, DynamicMaterial, DynamicMaterialEditor, Engine, ImageCore, ImageWrapper, PSDImporter, PSDImporterCore, Slate, SlateCore, UnrealEd

### `Plugins/Experimental/PSDImporterMaterialDesignerBridge/Source/PSDImporterMaterialDesignerBridge/Private/Factories/PSDImporterMDMaterialFactory.h` (Private)


#### class `UPSDImporterMDMaterialFactory`  
`class UPSDImporterMDMaterialFactory : public UObject`  
_L23-53_
- reflection: `UCLASS()`
- inherits: `UObject`
- L28 _public prototype_ `virtual ~UPSDImporterMDMaterialFactory() override = default;`
- L30 _public prototype_ `bool CanCreateMaterial(const UPSDDocument* InDocument) const;`
- L32 _public prototype_ `UDynamicMaterialInstance* CreateMaterial(UPSDDocument* InDocument) const;`
- L35 _protected prototype_ `UDynamicMaterialInstance* CreateMaterialAsset(UPSDDocument& InDocument) const;`
- L37 _protected prototype_ `void CreateLayers(UDynamicMaterialModelEditorOnlyData& InEditorOnlyData, UPSDDocument& InDocument) const;`
- L39 _protected prototype_ `void CreateLayer(UDMMaterialSlot& InSlot, UPSDDocument& InDocument, const FPSDFileLayer& InLayer, bool bInIsFirstLayer) const;`
- L41 _protected prototype_ `void CreateLayer_Base(UDMMaterialLayerObject& InMaterialLayer, const FPSDFileLayer& InLayer) const;`
- L42 _protected prototype_ `void CreateLayer_Base_Crop(UDMMaterialLayerObject& InMaterialLayer, const FPSDFileLayer& InLayer, const FIntPoint& InDocumentSize) const;`
- L44 _protected prototype_ `void CreateLayer_Mask_None(UDMMaterialLayerObject& InMaterialLayer) const;`
- L46 _protected prototype_ `void CreateLayer_Mask(UDMMaterialLayerObject& InMaterialLayer, const FPSDFileLayer& InLayer) const;`
- L47 _protected prototype_ `void CreateLayer_Mask_Crop(UDMMaterialLayerObject& InMaterialLayer, const FPSDFileLayer& InLayer, const FIntPoint& InDocumentSize) const;`
- L49 _protected prototype_ `void CreateLayer_Crop(UDMMaterialLayerObject& InMaterialLayer, const FPSDFileLayer& InLayer, const FIntPoint& InDocumentSize, UDMMaterialStage* InStage, const FIntRect& InBounds) const;`
- L52 _protected prototype_ `UClass* GetMaterialDesignerBlendMode(EPSDBlendMode InBlendMode) const;`

### `Plugins/Experimental/PSDImporterMaterialDesignerBridge/Source/PSDImporterMaterialDesignerBridge/Private/Factories/PSDImporterMDQuadsFactory.h` (Private)


#### enum `EPSDImporterMaterialDesignerType`  
`enum class EPSDImporterMaterialDesignerType : uint8`  
_L14-18_
- L16 _public enumerator_ `Instance`
- L17 _public enumerator_ `Copy`

#### class `UPSDImporterMDQuadsFactory`  
`class UPSDImporterMDQuadsFactory : public UObject`  
_L21-34_
- reflection: `UCLASS()`
- inherits: `UObject`
- L26 _public prototype_ `virtual ~UPSDImporterMDQuadsFactory() override = default;`
- L28 _public prototype_ `APSDQuadActor* CreateQuadActor(UWorld& InWorld, UPSDDocument& InDocument) const;`
- L30 _public prototype_ `void CreateQuads(APSDQuadActor& InQuadActor, EPSDImporterMaterialDesignerType InType) const;`
- L33 _protected prototype_ `APSDQuadMeshActor* CreateQuad(APSDQuadActor& InQuadActor, int32 InLayerIndex, EPSDImporterMaterialDesignerType InType) const;`

### `Plugins/Experimental/PSDImporterMaterialDesignerBridge/Source/PSDImporterMaterialDesignerBridge/Private/PSDImporterMDBridgeLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPSDImporterMaterialDesignerBridge, All, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPSDImporterMaterialDesignerBridge, All, All);`

### `Plugins/Experimental/PSDImporterMaterialDesignerBridge/Source/PSDImporterMaterialDesignerBridge/Private/PSDImporterMDBridgeModule.h` (Private)


#### class `FPSDImporterMaterialDesignerBridgeModule`  
`class FPSDImporterMaterialDesignerBridgeModule : public IModuleInterface`  
_L9-20_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _protected member_ `FDelegateHandle TextureResetDelegate;`

### `Plugins/Experimental/PSDImporterMaterialDesignerBridge/Source/PSDImporterMaterialDesignerBridge/Private/PSDImporterMDBridgeUtils.h` (Private)


#### class `FPSDImporterMDBridgeUtils`  
`class FPSDImporterMDBridgeUtils`  
_L7-11_
- L10 _public prototype_ `static void ResetTexture(APSDQuadMeshActor& InQuadMeshActor);`

### `Plugins/Experimental/PSDImporterMaterialDesignerBridge/Source/PSDImporterMaterialDesignerBridge/Private/PSDImporterMDContentBrowserIntegration.h` (Private)


#### class `FPSDImporterMaterialDesignerContentBrowserIntegration`  
`class FPSDImporterMaterialDesignerContentBrowserIntegration`  
_L14-33_
- L17 _public prototype_ `static FPSDImporterMaterialDesignerContentBrowserIntegration& Get();`
- L19 _public prototype_ `void Integrate();`
- L21 _public prototype_ `void Disintegrate();`
- L24 _protected prototype_ `TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& InSelectedAssets);`
- L26 _protected prototype_ `void CreateMenuEntries(FMenuBuilder& InMenuBuilder, TArray<FAssetData> InSelectedAssets);`
- L28 _protected prototype_ `void CreatePSDMaterialMaterialDesigner(TArray<FAssetData> InSelectedAssets);`
- L30 _protected prototype_ `void CreatePSDQuadsMaterialDesigner(TArray<FAssetData> InSelectedAssets, EPSDImporterMaterialDesignerType InType);`
- L32 _protected member_ `FDelegateHandle ContentBrowserHandle;`

### `Plugins/Experimental/PSDImporterMaterialDesignerBridge/Source/PSDImporterMaterialDesignerBridge/Public/PSDImporterMDConstants.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PSDImporterMaterialDesignerBridge` (scope `UE`)
- L9 _variable_ `constexpr const TCHAR* TextureEmissiveParameterName = TEXT("Lay` (scope `UE::PSDImporterMaterialDesignerBridge`)
- L10 _variable_ `constexpr const TCHAR* TextureOpacityParameterName = TEXT("Lay` (scope `UE::PSDImporterMaterialDesignerBridge`)
- L11 _variable_ `constexpr const TCHAR* OpacityOffsetXParameterName = TEXT("Lay` (scope `UE::PSDImporterMaterialDesignerBridge`)
- L12 _variable_ `constexpr const TCHAR* OpacityOffsetYParameterName = TEXT("Lay` (scope `UE::PSDImporterMaterialDesignerBridge`)
- L13 _variable_ `constexpr const TCHAR* OpacityTilingXParameterName = TEXT("Lay` (scope `UE::PSDImporterMaterialDesignerBridge`)
- L14 _variable_ `constexpr const TCHAR* OpacityTilingYParameterName = TEXT("Lay` (scope `UE::PSDImporterMaterialDesignerBridge`)
- L15 _variable_ `constexpr const TCHAR* OpacityCropLeft = TEXT("Cro` (scope `UE::PSDImporterMaterialDesignerBridge`)
- L16 _variable_ `constexpr const TCHAR* OpacityCropRight = TEXT("Cro` (scope `UE::PSDImporterMaterialDesignerBridge`)
- L17 _variable_ `constexpr const TCHAR* OpacityCropTop = TEXT("Cro` (scope `UE::PSDImporterMaterialDesignerBridge`)
- L18 _variable_ `constexpr const TCHAR* OpacityCropBottom = TEXT("Cro` (scope `UE::PSDImporterMaterialDesignerBridge`)
