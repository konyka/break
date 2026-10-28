# Plugins / EngineAssetDefinitions

- module root: `Plugins/Editor/EngineAssetDefinitions/Source`
- headers: 98; symbols: 598
- symbol kinds: class=104, function=380, macro=4, member=1, namespace=2, prototype=106, struct=1
- DynamicallyLoadedModuleNames: CurveAssetEditor, CurveTableEditor, DataTableEditor, FontEditor, PhysicsAssetEditor, StaticMeshEditor, TextureEditor, VirtualTexturingEditor
- PrivateDependencyModuleNames: AnimationBlueprintEditor, ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, BlueprintGraph, Blutility, ContentBrowser, ContentBrowserData, CoreUObject, DesktopPlatform, Engine, Foliage, GameProjectGeneration, InputCore, JsonObjectGraph, Kismet, Landscape, MaterialEditor, PhysicsCore, RHI, Slate, SlateCore, SourceControl, ToolMenus, ToolWidgets, UMGEditor, UnrealEd
- PrivateIncludePathModuleNames: CurveAssetEditor, CurveTableEditor, DataTableEditor, FontEditor, MaterialEditor, PhysicsAssetEditor, StaticMeshEditor, TextureEditor, VirtualTexturingEditor
- PublicDependencyModuleNames: Core
- PublicIncludePathModuleNames: SkeletalMeshEditor

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/AssetDefinition_AimOffset.h` (Private)


#### class `UAssetDefinition_AimOffset`  
`class UAssetDefinition_AimOffset : public UAssetDefinition_BlendSpace`  
_L13-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_BlendSpace`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/AssetDefinition_AimOffset1D.h` (Private)


#### class `UAssetDefinition_AimOffset1D`  
`class UAssetDefinition_AimOffset1D : public UAssetDefinition_BlendSpace1D`  
_L13-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_BlendSpace1D`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/AssetDefinition_AnimBank.h` (Private)


#### class `UAssetDefinition_AnimBank`  
`class UAssetDefinition_AnimBank : public UAssetDefinition_AnimationAsset`  
_L13-34_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_AnimationAsset`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override`
- L23 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L28 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L33 _public prototype_ `virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;`

#### class `UAssetDefinition_AnimBankData`  
`class UAssetDefinition_AnimBankData : public UAssetDefinition_TransformProviderData`  
_L37-46_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_TransformProviderData`
- L43 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L44 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/AssetDefinition_AnimBlueprint.h` (Private)


#### class `UAssetDefinition_AnimBlueprint`  
`class UAssetDefinition_AnimBlueprint : public UAssetDefinition_Blueprint`  
_L15-41_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- L21 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Implementation
- L22 _public prototype_ `virtual FText GetAssetDisplayName(const FAssetData& AssetData) const override;`
- L23 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L24 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L25 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L31 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`
- L33 _public prototype_ `virtual void BuildFilters(TArray<FAssetFilterData>& OutFilters) const override;`
- L35 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L39 _public prototype_ `virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const override;` — UAssetDefinition_Blueprint Implementation

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/AssetDefinition_AnimBlueprintGeneratedClass.h` (Private)


#### class `UAssetDefinition_AnimBlueprintGeneratedClass`  
`class UAssetDefinition_AnimBlueprintGeneratedClass : public UAssetDefinition_BlueprintGeneratedClass`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_BlueprintGeneratedClass`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/AssetDefinition_AnimComposite.h` (Private)


#### class `UAssetDefinition_AnimComposite`  
`class UAssetDefinition_AnimComposite : public UAssetDefinition_AnimationAsset`  
_L13-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_AnimationAsset`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/AssetDefinition_AnimMontage.h` (Private)


#### class `UAssetDefinition_AnimMontage`  
`class UAssetDefinition_AnimMontage : public UAssetDefinition_AnimationAsset`  
_L13-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_AnimationAsset`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/AssetDefinition_AnimSequence.h` (Private)


#### class `UAssetDefinition_AnimSequence`  
`class UAssetDefinition_AnimSequence : public UAssetDefinition_AnimationAsset`  
_L13-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_AnimationAsset`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual bool CanImport() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/AssetDefinition_AnimStreamable.h` (Private)


#### class `UAssetDefinition_AnimStreamable`  
`class UAssetDefinition_AnimStreamable : public UAssetDefinition_AnimationAsset`  
_L13-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_AnimationAsset`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/AssetDefinition_AnimationAsset.h` (Private)


#### class `UAssetDefinition_AnimationAsset`  
`class UAssetDefinition_AnimationAsset : public UAssetDefinitionDefault`  
_L11-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`
- L26 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/AssetDefinition_BlendSpace.h` (Private)


#### class `UAssetDefinition_BlendSpace`  
`class UAssetDefinition_BlendSpace : public UAssetDefinition_AnimationAsset`  
_L13-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_AnimationAsset`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/AssetDefinition_BlendSpace1D.h` (Private)


#### class `UAssetDefinition_BlendSpace1D`  
`class UAssetDefinition_BlendSpace1D : public UAssetDefinition_AnimationAsset`  
_L13-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_AnimationAsset`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/AssetDefinition_PoseAsset.h` (Private)


#### class `UAssetDefinition_PoseAsset`  
`class UAssetDefinition_PoseAsset : public UAssetDefinition_AnimationAsset`  
_L13-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_AnimationAsset`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/AssetDefinition_SkeletalMesh.h` (Private)


#### class `UAssetDefinition_SkeletalMesh`  
`class UAssetDefinition_SkeletalMesh : public UAssetDefinitionDefault`  
_L13-42_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public prototype_ `UAssetDefinition_SkeletalMesh();`
- L21 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L22 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L23 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L24 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L29 _public prototype_ `virtual void GetAssetStatusInfo(const TSharedPtr<IAssetStatusInfoProvider>& InAssetStatusInfoProvider, TArray<FAssetDisplayInfo>& OutStatusInfo) const override;`
- L30 _public function_ `virtual bool CanImport() const override`
- L31 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`
- L32 _public prototype_ `virtual TSharedPtr<class SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;`
- L33 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L37 _private prototype_ `void OnAssetRemoved(const FAssetData& AssetData) const;`
- L38 _private prototype_ `EVisibility GetThumbnailSkinningOverlayVisibility(const FAssetData AssetData) const;`
- L39 _private prototype_ `EVisibility GetThumbnailSkinningStatusVisibility(const TSharedPtr<IAssetStatusInfoProvider> InAssetStatusInfoProvider) const;`
- L41 _private member_ `mutable TArray<FString> ThumbnailSkinningOverlayAssetNames;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/AssetDefinition_Skeleton.h` (Private)


#### class `UAssetDefinition_Skeleton`  
`class UAssetDefinition_Skeleton : public UAssetDefinitionDefault`  
_L11-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/AssetDefinition_TransformProviderData.h` (Private)


#### class `UAssetDefinition_TransformProviderData`  
`class UAssetDefinition_TransformProviderData : public UAssetDefinitionDefault`  
_L10-18_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public function_ `virtual FText GetAssetDisplayName() const override`
- L16 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L17 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Animation/SkeletalMeshUtilities.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SkeletalMeshUtilities` (scope `UE`)
- L10 _prototype_ `void AssignSkeletonToMesh(USkeletalMesh* SkelMesh);` (scope `UE::SkeletalMeshUtilities`)

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_Actor.h` (Private)


#### class `UAssetDefinition_Actor`  
`class UAssetDefinition_Actor : public UAssetDefinitionDefault`  
_L15-32_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L21 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L22 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L23 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L24 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L28 _public function_ `virtual FText GetObjectDisplayNameText(UObject* Object) const override`
- L30 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_ActorFolder.h` (Private)


#### class `UAssetDefinition_ActorFolder`  
`class UAssetDefinition_ActorFolder : public UAssetDefinitionDefault`  
_L13-32_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L26 _public function_ `virtual FText GetObjectDisplayNameText(UObject* Object) const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_ActorFoliageSettings.h` (Private)


#### class `UAssetDefinition_ActorFoliageSettings`  
`class UAssetDefinition_ActorFoliageSettings : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_CanvasRenderTarget2D.h` (Private)


#### class `UAssetDefinition_CanvasRenderTarget2D`  
`class UAssetDefinition_CanvasRenderTarget2D : public UAssetDefinition_TextureRenderTarget2D`  
_L11-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinition_TextureRenderTarget2D`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L19 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_Curve.h` (Private)


#### class `UAssetDefinition_Curve`  
`class UAssetDefinition_Curve : public UAssetDefinitionDefault`  
_L15-34_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L21 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L22 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L23 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L24 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L29 _public function_ `virtual bool CanImport() const override`
- L31 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L32 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_CurveFloat.h` (Private)


#### class `UAssetDefinition_CurveFloat`  
`class UAssetDefinition_CurveFloat : public UAssetDefinition_Curve`  
_L11-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Curve`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_CurveLinearColor.h` (Private)


#### class `UAssetDefinition_CurveLinearColor`  
`class UAssetDefinition_CurveLinearColor : public UAssetDefinition_Curve`  
_L11-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Curve`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_CurveLinearColorAtlas.h` (Private)


#### class `UAssetDefinition_CurveLinearColorAtlas`  
`class UAssetDefinition_CurveLinearColorAtlas : public UAssetDefinition_Texture`  
_L11-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Texture`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual bool CanImport() const override`
- L21 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_CurveVector.h` (Private)


#### class `UAssetDefinition_CurveVector`  
`class UAssetDefinition_CurveVector : public UAssetDefinition_Curve`  
_L11-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Curve`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_DataLayer.h` (Private)


#### class `UAssetDefinition_DataLayer`  
`class UAssetDefinition_DataLayer : public UAssetDefinitionDefault`  
_L12-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const override`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_DataLayerInstance.h` (Private)


#### class `UAssetDefinition_DataLayerInstance`  
`class UAssetDefinition_DataLayerInstance : public UAssetDefinitionDefault`  
_L13-33_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L22 _public function_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const override`
- L23 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L27 _public function_ `virtual FText GetObjectDisplayNameText(UObject* Object) const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_EditorUtilityBlueprint.h` (Private)


#### class `UAssetDefinition_EditorUtilityBlueprint`  
`class UAssetDefinition_EditorUtilityBlueprint : public UAssetDefinition_Blueprint`  
_L10-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_EditorUtilityWidgetBlueprint.h` (Private)


#### class `UAssetDefinition_EditorUtilityWidgetBlueprint`  
`class UAssetDefinition_EditorUtilityWidgetBlueprint : public UAssetDefinitionDefault`  
_L10-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public prototype_ `UAssetDefinition_EditorUtilityWidgetBlueprint();`
- L18 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L19 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L20 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L23 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L24 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_ExternalDataLayer.h` (Private)


#### class `UAssetDefinition_ExternalDataLayer`  
`class UAssetDefinition_ExternalDataLayer : public UAssetDefinition_DataLayer`  
_L12-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_DataLayer`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_FbxSceneImportData.h` (Private)


#### class `UAssetDefinition_FbxSceneImportData`  
`class UAssetDefinition_FbxSceneImportData : public UAssetDefinitionDefault`  
_L11-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual bool CanImport() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_Font.h` (Private)


#### class `UAssetDefinition_Font`  
`class UAssetDefinition_Font : public UAssetDefinitionDefault`  
_L11-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L26 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_FontFace.h` (Private)


#### class `UAssetDefinition_FontFace`  
`class UAssetDefinition_FontFace : public UAssetDefinitionDefault`  
_L11-39_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public function_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const`
- L30 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L35 _private prototype_ `bool CanExecuteReimport(const TArray<TWeakObjectPtr<UFontFace>> Objects) const;` — Can we execute a reimport for the selected objects?
- L38 _private prototype_ `void ExecuteReimport(const TArray<TWeakObjectPtr<UFontFace>> Objects) const;` — Handler for when Reimport is selected

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_ForceFeedbackAttenuation.h` (Private)


#### class `UAssetDefinition_ForceFeedbackAttenuation`  
`class UAssetDefinition_ForceFeedbackAttenuation : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_ForceFeedbackEffect.h` (Private)


#### struct `FPreviewForceFeedbackEffect`  
`struct FPreviewForceFeedbackEffect : public FActiveForceFeedbackEffect, public FTickableEditorObject, public FGCObject`  
_L12-25_
- inherits: `FActiveForceFeedbackEffect,FTickableEditorObject,FGCObject`
- L15 _public prototype_ `virtual bool IsTickable() const override;` — FTickableEditorObject Implementation
- L16 _public prototype_ `virtual void Tick( float DeltaTime ) override;`
- L17 _public prototype_ `virtual TStatId GetStatId() const override;`
- L20 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject Implementation
- L21 _public function_ `virtual FString GetReferencerName() const override`

#### class `UAssetDefinition_ForceFeedbackEffect`  
`class UAssetDefinition_ForceFeedbackEffect : public UAssetDefinitionDefault`  
_L28-50_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L34 _protected prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L35 _protected prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L36 _protected prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L37 _protected prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L38 _protected prototype_ `virtual EAssetCommandResult ActivateAssets(const FAssetActivateArgs& InActivateArgs) const override;`
- L39 _protected prototype_ `virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& InAssetData) const override;`
- L40 _protected prototype_ `virtual bool GetThumbnailActionOverlay(const FAssetData& InAssetData, FAssetActionThumbnailOverlayInfo& OutActionOverlayInfo) const override;`
- L45 _public function_ `static FPreviewForceFeedbackEffect& GetPreviewForceFeedbackEffect()`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_HLODLayer.h` (Private)


#### class `UAssetDefinition_HLODLayer`  
`class UAssetDefinition_HLODLayer : public UAssetDefinitionDefault`  
_L12-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const override`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_HLODProxy.h` (Private)


#### class `UAssetDefinition_HLODProxy`  
`class UAssetDefinition_HLODProxy : public UAssetDefinitionDefault`  
_L11-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_HapticFeedbackEffectBuffer.h` (Private)


#### class `UAssetDefinition_HapticFeedbackEffectBuffer`  
`class UAssetDefinition_HapticFeedbackEffectBuffer : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_HapticFeedbackEffectCurve.h` (Private)


#### class `UAssetDefinition_HapticFeedbackEffectCurve`  
`class UAssetDefinition_HapticFeedbackEffectCurve : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_HapticFeedbackEffectSoundWave.h` (Private)


#### class `UAssetDefinition_HapticFeedbackEffectSoundWave`  
`class UAssetDefinition_HapticFeedbackEffectSoundWave : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_InstancedFoliageSettings.h` (Private)


#### class `UAssetDefinition_InstancedFoliageSettings`  
`class UAssetDefinition_InstancedFoliageSettings : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_LandscapeGrassType.h` (Private)


#### class `UAssetDefinition_LandscapeGrassType`  
`class UAssetDefinition_LandscapeGrassType : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_LandscapeLayer.h` (Private)


#### class `UAssetDefinition_LandscapeLayer`  
`class UAssetDefinition_LandscapeLayer : public UAssetDefinitionDefault`  
_L11-29_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_LightWeightInstance.h` (Private)


#### class `UDEPRECATED_AssetDefinition_LightWeightInstance`  
`class UDEPRECATED_AssetDefinition_LightWeightInstance : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS(Deprecated, meta = (DeprecationMessage ="Deprecated in 5.8. Consider using InstancedActors for similar functionality"))`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_NeuralProfile.h` (Private)


#### class `UAssetDefinition_NeuralProfile`  
`class UAssetDefinition_NeuralProfile : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_NodeMappingContainer.h` (Private)


#### class `UAssetDefinition_NodeMappingContainer`  
`class UAssetDefinition_NodeMappingContainer : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_ObjectLibrary.h` (Private)


#### class `UAssetDefinition_ObjectLibrary`  
`class UAssetDefinition_ObjectLibrary : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L24 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_PhysicalMaterial.h` (Private)


#### class `UAssetDefinition_PhysicalMaterial`  
`class UAssetDefinition_PhysicalMaterial : public UAssetDefinitionDefault`  
_L11-41_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L22 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L27 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L32 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_PhysicalMaterialMask.h` (Private)


#### class `UAssetDefinition_PhysicalMaterialMask`  
`class UAssetDefinition_PhysicalMaterialMask : public UAssetDefinitionDefault`  
_L9-44_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L25 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L30 _public function_ `virtual bool CanImport() const override`
- L35 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_PhysicsAsset.h` (Private)


#### class `UAssetDefinition_PhysicsAsset`  
`class UAssetDefinition_PhysicsAsset : public UAssetDefinitionDefault`  
_L11-44_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L22 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L27 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L32 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L41 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L42 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAsset) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_PreviewMeshCollection.h` (Private)


#### class `UAssetDefinition_PreviewMeshCollection`  
`class UAssetDefinition_PreviewMeshCollection : public UAssetDefinitionDefault`  
_L11-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public function_ `virtual FText GetAssetDisplayName() const override`
- L17 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L19 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_ProceduralFoliageSpawner.h` (Private)


#### class `UAssetDefinition_ProceduralFoliageSpawner`  
`class UAssetDefinition_ProceduralFoliageSpawner : public UAssetDefinitionDefault`  
_L11-30_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_SlateBrush.h` (Private)


#### class `UAssetDefinition_SlateBrush`  
`class UAssetDefinition_SlateBrush : public UAssetDefinitionDefault`  
_L11-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_SlateWidgetStyle.h` (Private)


#### class `UAssetDefinition_SlateWidgetStyle`  
`class UAssetDefinition_SlateWidgetStyle : public UAssetDefinitionDefault`  
_L11-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L26 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_SparseVolumeTexture.h` (Private)


#### class `UAssetDefinition_SparseVolumeTexture`  
`class UAssetDefinition_SparseVolumeTexture : public UAssetDefinitionDefault`  
_L12-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L26 _public function_ `virtual bool CanImport() const override`

#### class `UAssetDefinition_StaticSparseVolumeTexture`  
`class UAssetDefinition_StaticSparseVolumeTexture : public UAssetDefinition_SparseVolumeTexture`  
_L31-40_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_SparseVolumeTexture`
- L37 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L38 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

#### class `UAssetDefinition_AnimatedSparseVolumeTexture`  
`class UAssetDefinition_AnimatedSparseVolumeTexture : public UAssetDefinition_SparseVolumeTexture`  
_L43-52_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_SparseVolumeTexture`
- L49 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L50 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_SpecularProfile.h` (Private)


#### class `UAssetDefinition_SpecularProfile`  
`class UAssetDefinition_SpecularProfile : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_StaticMesh.h` (Private)


#### class `UAssetDefinition_StaticMesh`  
`class UAssetDefinition_StaticMesh : public UAssetDefinitionDefault`  
_L11-31_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public function_ `virtual bool CanImport() const override`
- L26 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`
- L28 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`
- L29 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_SubUVAnimation.h` (Private)


#### class `UAssetDefinition_SubUVAnimation`  
`class UAssetDefinition_SubUVAnimation : public UAssetDefinitionDefault`  
_L11-29_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_SubsurfaceProfile.h` (Private)


#### class `UAssetDefinition_SubsurfaceProfile`  
`class UAssetDefinition_SubsurfaceProfile : public UAssetDefinitionDefault`  
_L11-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L26 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_Texture.h` (Private)


#### class `UAssetDefinition_Texture`  
`class UAssetDefinition_Texture : public UAssetDefinitionDefault`  
_L11-30_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public function_ `virtual bool CanImport() const override`
- L27 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`
- L28 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_Texture2D.h` (Private)


#### class `UAssetDefinition_Texture2D`  
`class UAssetDefinition_Texture2D : public UAssetDefinition_Texture`  
_L11-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinition_Texture`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L19 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_Texture2DArray.h` (Private)


#### class `UAssetDefinition_Texture2DArray`  
`class UAssetDefinition_Texture2DArray : public UAssetDefinition_Texture`  
_L11-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinition_Texture`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_TextureCube.h` (Private)


#### class `UAssetDefinition_TextureCube`  
`class UAssetDefinition_TextureCube : public UAssetDefinition_Texture`  
_L11-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinition_Texture`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_TextureCubeArray.h` (Private)


#### class `UAssetDefinition_TextureCubeArray`  
`class UAssetDefinition_TextureCubeArray : public UAssetDefinition_Texture`  
_L11-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinition_Texture`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_TextureLightProfile.h` (Private)


#### class `UAssetDefinition_TextureLightProfile`  
`class UAssetDefinition_TextureLightProfile : public UAssetDefinition_Texture`  
_L11-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinition_Texture`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_TextureRenderTarget.h` (Private)


#### class `UAssetDefinition_TextureRenderTarget`  
`class UAssetDefinition_TextureRenderTarget : public UAssetDefinition_Texture`  
_L11-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinition_Texture`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual bool CanImport() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_TextureRenderTarget2D.h` (Private)


#### class `UAssetDefinition_TextureRenderTarget2D`  
`class UAssetDefinition_TextureRenderTarget2D : public UAssetDefinition_TextureRenderTarget`  
_L11-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinition_TextureRenderTarget`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L19 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_TextureRenderTarget2DArray.h` (Private)


#### class `UAssetDefinition_TextureRenderTarget2DArray`  
`class UAssetDefinition_TextureRenderTarget2DArray : public UAssetDefinition_TextureRenderTarget`  
_L11-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinition_TextureRenderTarget`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L19 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_TextureRenderTargetCube.h` (Private)


#### class `UAssetDefinition_TextureRenderTargetCube`  
`class UAssetDefinition_TextureRenderTargetCube : public UAssetDefinition_TextureRenderTarget`  
_L11-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinition_TextureRenderTarget`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L19 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_TextureRenderTargetVolume.h` (Private)


#### class `UAssetDefinition_TextureRenderTargetVolume`  
`class UAssetDefinition_TextureRenderTargetVolume : public UAssetDefinition_TextureRenderTarget`  
_L11-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinition_TextureRenderTarget`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L19 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_ToonProfile.h` (Private)


#### class `UAssetDefinition_ToonProfile`  
`class UAssetDefinition_ToonProfile : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_TouchInterface.h` (Private)


#### class `UAssetDefinition_TouchInterface`  
`class UAssetDefinition_TouchInterface : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_UserDefinedEnum.h` (Private)


#### class `UAssetDefinition_UserDefinedEnum`  
`class UAssetDefinition_UserDefinedEnum : public UAssetDefinitionDefault`  
_L11-32_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public function_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const override`
- L29 _public prototype_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override;`
- L30 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_UserDefinedStruct.h` (Private)


#### class `UAssetDefinition_UserDefinedStruct`  
`class UAssetDefinition_UserDefinedStruct : public UAssetDefinitionDefault`  
_L11-32_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public function_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const override`
- L29 _public prototype_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override;`
- L30 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_VectorField.h` (Private)


#### class `UAssetDefinition_VectorField`  
`class UAssetDefinition_VectorField : public UAssetDefinitionDefault`  
_L11-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_VectorFieldAnimated.h` (Private)


#### class `UAssetDefinition_VectorFieldAnimated`  
`class UAssetDefinition_VectorFieldAnimated : public UAssetDefinition_VectorField`  
_L11-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_VectorField`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_VectorFieldStatic.h` (Private)


#### class `UAssetDefinition_VectorFieldStatic`  
`class UAssetDefinition_VectorFieldStatic : public UAssetDefinition_VectorField`  
_L11-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_VectorField`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L19 _public function_ `virtual bool CanImport() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/AssetDefinition_VolumeTexture.h` (Private)


#### class `UAssetDefinition_VolumeTexture`  
`class UAssetDefinition_VolumeTexture : public UAssetDefinition_Texture`  
_L11-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinition_Texture`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Material/AssetDefinition_Material.h` (Private)


#### class `UAssetDefinition_Material`  
`class UAssetDefinition_Material : public UAssetDefinition_MaterialInterface`  
_L13-30_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MaterialInterface`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L26 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L28 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Material/AssetDefinition_MaterialFunction.h` (Private)


#### class `UAssetDefinition_MaterialFunction`  
`class UAssetDefinition_MaterialFunction : public UAssetDefinitionDefault`  
_L12-30_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L26 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAsset) const override;`
- L27 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`
- L28 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

#### class `UAssetDefinition_MaterialFunctionMaterialLayer`  
`class UAssetDefinition_MaterialFunctionMaterialLayer : public UAssetDefinition_MaterialFunction`  
_L33-47_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MaterialFunction`
- L39 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L40 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L41 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

#### class `UAssetDefinition_MaterialFunctionLayerBlend`  
`class UAssetDefinition_MaterialFunctionLayerBlend : public UAssetDefinition_MaterialFunction`  
_L50-64_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MaterialFunction`
- L56 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L57 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L58 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Material/AssetDefinition_MaterialFunctionInstance.h` (Private)


#### class `UAssetDefinition_MaterialFunctionInstance`  
`class UAssetDefinition_MaterialFunctionInstance : public UAssetDefinition_MaterialFunction`  
_L13-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MaterialFunction`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAsset) const override;`
- L22 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

#### class `UAssetDefinition_MaterialFunctionLayerInstance`  
`class UAssetDefinition_MaterialFunctionLayerInstance : public UAssetDefinition_MaterialFunctionInstance`  
_L27-41_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MaterialFunctionInstance`
- L33 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L34 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L35 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

#### class `UAssetDefinition_MaterialFunctionLayerBlendInstance`  
`class UAssetDefinition_MaterialFunctionLayerBlendInstance : public UAssetDefinition_MaterialFunctionInstance`  
_L44-58_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MaterialFunctionInstance`
- L50 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L51 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L52 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Material/AssetDefinition_MaterialInstanceConstant.h` (Private)


#### class `UAssetDefinition_MaterialInstanceConstant`  
`class UAssetDefinition_MaterialInstanceConstant : public UAssetDefinition_MaterialInterface`  
_L16-34_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MaterialInterface`
- L22 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L23 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L24 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L25 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L30 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L31 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`
- L32 _public function_ `virtual bool CanImport() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Material/AssetDefinition_MaterialInstanceDynamic.h` (Private)


#### class `UAssetDefinition_MaterialInstanceDynamic`  
`class UAssetDefinition_MaterialInstanceDynamic : public UAssetDefinition_MaterialInterface`  
_L16-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MaterialInterface`
- L22 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L23 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L24 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Material/AssetDefinition_MaterialInterface.h` (Private)


#### class `UAssetDefinition_MaterialInterface`  
`class UAssetDefinition_MaterialInterface : public UAssetDefinitionDefault`  
_L11-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAsset) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Material/AssetDefinition_MaterialParameterCollection.h` (Private)


#### class `UAssetDefinition_MaterialParameterCollection`  
`class UAssetDefinition_MaterialParameterCollection : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Script/AssetDefinition_BlueprintGeneratedClass.h` (Private)


#### class `UAssetDefinition_BlueprintGeneratedClass`  
`class UAssetDefinition_BlueprintGeneratedClass : public UAssetDefinition_ClassTypeBase`  
_L13-35_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_ClassTypeBase`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L30 _public prototype_ `virtual TWeakPtr<IClassTypeActions> GetClassTypeActions(const FAssetData& AssetData) const override;` — UAssetDefinition_ClassTypeBase Implementation
- L33 _public prototype_ `virtual UClass* GetNewDerivedBlueprintClass() const;`
- L34 _public prototype_ `virtual UFactory* GetFactoryForNewDerivedBlueprint(UBlueprintGeneratedClass* GeneratedClass) const;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Script/AssetDefinition_Class.h` (Private)


#### class `UAssetDefinition_Class`  
`class UAssetDefinition_Class : public UAssetDefinition_ClassTypeBase`  
_L14-36_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_ClassTypeBase`
- L20 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Implementation
- L21 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L22 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L23 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L29 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`
- L30 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L34 _public prototype_ `virtual TWeakPtr<IClassTypeActions> GetClassTypeActions(const FAssetData& AssetData) const override;` — UAssetDefinition_ClassTypeBase Implementation

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Table/AssetDefinition_CompositeCurveTable.h` (Private)


#### class `UAssetDefinition_CompositeCurveTable`  
`class UAssetDefinition_CompositeCurveTable : public UAssetDefinition_CurveTable`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_CurveTable`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L19 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L24 _public function_ `virtual bool CanImport() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Table/AssetDefinition_CompositeDataTable.h` (Private)


#### class `UAssetDefinition_CompositeDataTable`  
`class UAssetDefinition_CompositeDataTable : public UAssetDefinition_DataTable`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_DataTable`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L19 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L24 _public function_ `virtual bool CanImport() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Table/AssetDefinition_CurveTable.h` (Private)


#### class `UAssetDefinition_CurveTable`  
`class UAssetDefinition_CurveTable : public UAssetDefinitionDefault`  
_L11-32_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L28 _public function_ `virtual bool CanImport() const override`
- L29 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`
- L30 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Private/Table/AssetDefinition_MirrorDataTable.h` (Private)


#### class `UAssetDefinition_MirrorDataTable`  
`class UAssetDefinition_MirrorDataTable : public UAssetDefinition_DataTable`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_DataTable`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L19 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L24 _public function_ `virtual bool CanImport() const override`

### `Plugins/Editor/EngineAssetDefinitions/Source/Public/AssetDefinition_DataAsset.h` (Public)


#### class `UAssetDefinition_DataAsset`  
`class UAssetDefinition_DataAsset : public UAssetDefinitionDefault`  
_L13-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinitionDefault`
- L19 _public function_ `UAssetDefinition_DataAsset()` — UAssetDefinition Implementation
- L23 _public function_ `virtual FText GetAssetDisplayName() const override`
- L24 _public prototype_ `virtual FText GetAssetDisplayName(const FAssetData& AssetData) const override;`
- L25 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L26 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L35 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L37 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`
- L39 _public prototype_ `virtual bool CanMerge() const override;`
- L40 _public prototype_ `virtual EAssetCommandResult Merge(const FAssetAutomaticMergeArgs& MergeArgs) const override;`
- L41 _public prototype_ `virtual EAssetCommandResult Merge(const FAssetManualMergeArgs& MergeArgs) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ENGINEASSETDEFINITIONS_API`

### `Plugins/Editor/EngineAssetDefinitions/Source/Public/AssetDefinition_Redirector.h` (Public)


#### class `UAssetDefinition_Redirector`  
`class UAssetDefinition_Redirector : public UAssetDefinitionDefault`  
_L15-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinitionDefault`
- L21 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Implementation
- L22 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L23 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L24 _public prototype_ `virtual EAssetCommandResult ActivateAssets(const FAssetActivateArgs& ActivateArgs) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ENGINEASSETDEFINITIONS_API`

### `Plugins/Editor/EngineAssetDefinitions/Source/Public/AssetDefinition_World.h` (Public)


#### class `UAssetDefinition_World`  
`class UAssetDefinition_World : public UAssetDefinitionDefault`  
_L20-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinitionDefault`
- L26 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L27 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L28 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L29 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L31 _public prototype_ `virtual TArray<FAssetData> PrepareToActivateAssets(const FAssetActivateArgs& ActivateArgs) const override;`
- L32 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L33 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`
- L35 _public prototype_ `virtual FAssetSupportResponse CanRename(const FAssetData& InAsset) const override;`
- L36 _public prototype_ `virtual FAssetSupportResponse CanDuplicate(const FAssetData& InAsset) const override;`
- L38 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAsset) const override;`
- L42 _public prototype_ `bool IsPartitionWorldInUse(const FAssetData& InAsset) const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ENGINEASSETDEFINITIONS_API`

### `Plugins/Editor/EngineAssetDefinitions/Source/Public/Script/AssetDefinition_Blueprint.h` (Public)


#### class `UAssetDefinition_Blueprint`  
`class UAssetDefinition_Blueprint : public UAssetDefinition_ClassTypeBase`  
_L16-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinition_ClassTypeBase`
- L22 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Implementation
- L23 _public prototype_ `virtual FText GetAssetDisplayName(const FAssetData& AssetData) const override;`
- L24 _public prototype_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override;`
- L25 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L26 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L27 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L33 _public function_ `virtual bool CanMerge() const override`
- L34 _public prototype_ `virtual EAssetCommandResult Merge(const FAssetAutomaticMergeArgs& MergeArgs) const override;`
- L35 _public prototype_ `virtual EAssetCommandResult Merge(const FAssetManualMergeArgs& MergeArgs) const override;`
- L37 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`
- L39 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`
- L40 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L44 _public prototype_ `virtual TWeakPtr<IClassTypeActions> GetClassTypeActions(const FAssetData& AssetData) const override;` — UAssetDefinition_ClassTypeBase Implementation
- L48 _public prototype_ `virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const;`

### `Plugins/Editor/EngineAssetDefinitions/Source/Public/Script/AssetDefinition_ClassTypeBase.h` (Public)


#### class `UAssetDefinition_ClassTypeBase`  
`class UAssetDefinition_ClassTypeBase : public UAssetDefinitionDefault`  
_L13-31_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UAssetDefinitionDefault`
- desc: Base class for "class type" assets (C++ classes and Blueprints
- L19 _public function_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const override` — UAssetDefinition Begin
- L23 _public prototype_ `virtual TSharedPtr<class SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;`
- L27 _public function_ `virtual TWeakPtr<IClassTypeActions> GetClassTypeActions(const FAssetData& AssetData) const` — Get the class type actions for this asset

### `Plugins/Editor/EngineAssetDefinitions/Source/Public/Table/AssetDefinition_DataTable.h` (Public)


#### class `UAssetDefinition_DataTable`  
`class UAssetDefinition_DataTable : public UAssetDefinitionDefault`  
_L13-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinitionDefault`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public prototype_ `virtual FText GetAssetDisplayName(const FAssetData& AssetData) const override;`
- L21 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L22 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L23 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L28 _public function_ `virtual bool CanImport() const override`
- L29 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`
- L30 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ENGINEASSETDEFINITIONS_API`
