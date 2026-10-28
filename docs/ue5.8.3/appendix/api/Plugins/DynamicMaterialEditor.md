# Plugins / DynamicMaterialEditor

- module root: `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor`
- headers: 263; symbols: 3427
- symbol kinds: class=255, delegate=26, enum=23, enumerator=142, function=217, member=599, namespace=20, prototype=2096, struct=36, typedef=5, variable=8
- PrivateDependencyModuleNames: AdvancedPreviewScene, AppFramework, ApplicationCore, AssetDefinition, ContentBrowser, ContentBrowserData, CustomDetailsView, DeveloperSettings, DynamicMaterialShaders, DynamicMaterialTextureSet, DynamicMaterialTextureSetEditor, EditorSubsystem, EditorWidgets, InputCore, Json, JsonUtilities, MaterialEditor, Projects, PropertyEditor, RHI, RenderCore, Renderer, Slate, SlateCore, ToolMenus, TypedElementRuntime, UMG, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, CoreUObject, DynamicMaterial, Engine, MaterialEditor

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/DMMaterialLayer_Deprecated.h` (Private)


#### struct `FDMMaterialLayer`  
`struct FDMMaterialLayer`  
_L11-38_
- reflection: `USTRUCT(BlueprintType, Category = "Material Designer")`
- L16 _public member_ `EDMMaterialPropertyType MaterialProperty = EDMMaterialPropertyType::None;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L19 _public member_ `FText LayerName;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L22 _public member_ `TObjectPtr<UDMMaterialStage> Base = nullptr;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L25 _public member_ `TObjectPtr<UDMMaterialStage> Mask = nullptr;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L28 _public member_ `bool bEnabled = true;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L31 _public member_ `bool bBaseEnabled = true;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L34 _public member_ `bool bMaskEnabled = true;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L37 _public member_ `mutable bool bLinkedUVs = true;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPAmbientOcclusion.h` (Private)


#### class `UDMMaterialPropertyAmbientOcclusion`  
`class UDMMaterialPropertyAmbientOcclusion : public UDMMaterialProperty`  
_L11-21_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertyAmbientOcclusion();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPAnisotropy.h` (Private)


#### class `UDMMaterialPropertyAnisotropy`  
`class UDMMaterialPropertyAnisotropy : public UDMMaterialProperty`  
_L11-21_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertyAnisotropy();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPBaseColor.h` (Private)


#### class `UDMMaterialPropertyBaseColor`  
`class UDMMaterialPropertyBaseColor : public UDMMaterialProperty`  
_L11-22_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertyBaseColor();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L20 _public prototype_ `virtual TEnumAsByte<EMaterialSamplerType> GetTextureSamplerType() const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPDisplacement.h` (Private)


#### class `UDMMaterialPropertyDisplacement`  
`class UDMMaterialPropertyDisplacement : public UDMMaterialProperty`  
_L11-23_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertyDisplacement();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L20 _public prototype_ `virtual void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L21 _public prototype_ `virtual void AddAlphaMultiplier(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPEmissiveColor.h` (Private)


#### class `UDMMaterialPropertyEmissiveColor`  
`class UDMMaterialPropertyEmissiveColor : public UDMMaterialProperty`  
_L11-22_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertyEmissiveColor();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L20 _public prototype_ `virtual TEnumAsByte<EMaterialSamplerType> GetTextureSamplerType() const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPMetallic.h` (Private)


#### class `UDMMaterialPropertyMetallic`  
`class UDMMaterialPropertyMetallic : public UDMMaterialProperty`  
_L11-21_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertyMetallic();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPNormal.h` (Private)


#### class `UDMMaterialPropertyNormal`  
`class UDMMaterialPropertyNormal : public UDMMaterialProperty`  
_L11-32_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertyNormal();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L20 _public prototype_ `virtual TEnumAsByte<EMaterialSamplerType> GetTextureSamplerType() const override;`
- L25 _public prototype_ `virtual void AddOutputProcessor(const TSharedRef<FDMMaterialBuildState>& InBuildState) const;` — Adds the SafeNormalize function as an extra output processor.
- L30 _public prototype_ `virtual void AddAlphaMultiplier(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;` — Replaces the regular multiply node with a custom one that doesn't affect the Z axis.

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPOpacity.h` (Private)


#### class `UDMMaterialPropertyOpacity`  
`class UDMMaterialPropertyOpacity : public UDMMaterialProperty`  
_L11-21_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertyOpacity();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPOpacityMask.h` (Private)


#### class `UDMMaterialPropertyOpacityMask`  
`class UDMMaterialPropertyOpacityMask : public UDMMaterialProperty`  
_L11-22_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertyOpacityMask();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L20 _public prototype_ `virtual TEnumAsByte<EMaterialSamplerType> GetTextureSamplerType() const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPPixelDepthOffset.h` (Private)


#### class `UDMMaterialPropertyPixelDepthOffset`  
`class UDMMaterialPropertyPixelDepthOffset : public UDMMaterialProperty`  
_L11-21_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertyPixelDepthOffset();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPRefraction.h` (Private)


#### class `UDMMaterialPropertyRefraction`  
`class UDMMaterialPropertyRefraction : public UDMMaterialProperty`  
_L11-21_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertyRefraction();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPRoughness.h` (Private)


#### class `UDMMaterialPropertyRoughness`  
`class UDMMaterialPropertyRoughness : public UDMMaterialProperty`  
_L11-21_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertyRoughness();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPSpecular.h` (Private)


#### class `UDMMaterialPropertySpecular`  
`class UDMMaterialPropertySpecular : public UDMMaterialProperty`  
_L11-21_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertySpecular();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPSubsurfaceColor.h` (Private)


#### class `UDMMaterialPropertySubsurfaceColor`  
`class UDMMaterialPropertySubsurfaceColor : public UDMMaterialProperty`  
_L11-22_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertySubsurfaceColor();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L20 _public prototype_ `virtual TEnumAsByte<EMaterialSamplerType> GetTextureSamplerType() const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPSurfaceThickness.h` (Private)


#### class `UDMMaterialPropertySurfaceThickness`  
`class UDMMaterialPropertySurfaceThickness : public UDMMaterialProperty`  
_L11-21_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertySurfaceThickness();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPTangent.h` (Private)


#### class `UDMMaterialPropertyTangent`  
`class UDMMaterialPropertyTangent : public UDMMaterialProperty`  
_L11-21_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertyTangent();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialProperties/DMMPWorldPositionOffset.h` (Private)


#### class `UDMMaterialPropertyWorldPositionOffset`  
`class UDMMaterialPropertyWorldPositionOffset : public UDMMaterialProperty`  
_L11-21_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialProperty`
- L16 _public prototype_ `UDMMaterialPropertyWorldPositionOffset();`
- L19 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEAbs.h` (Private)


#### class `UDMMaterialStageExpressionAbs`  
`class UDMMaterialStageExpressionAbs : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionAbs();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEActorPositionWS.h` (Private)


#### class `UDMMaterialStageExpressionActorPositionWS`  
`class UDMMaterialStageExpressionActorPositionWS : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionActorPositionWS();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEAdd.h` (Private)


#### class `UDMMaterialStageExpressionAdd`  
`class UDMMaterialStageExpressionAdd : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionAdd();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEArcCosine.h` (Private)


#### class `UDMMaterialStageExpressionArccosine`  
`class UDMMaterialStageExpressionArccosine : public UDMMaterialStageExpressionMathBase`  
_L10-16_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L15 _public prototype_ `UDMMaterialStageExpressionArccosine();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEArcCosineFast.h` (Private)


#### class `UDMMaterialStageExpressionArccosineFast`  
`class UDMMaterialStageExpressionArccosineFast : public UDMMaterialStageExpressionMathBase`  
_L10-16_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L15 _public prototype_ `UDMMaterialStageExpressionArccosineFast();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEArcSine.h` (Private)


#### class `UDMMaterialStageExpressionArcsine`  
`class UDMMaterialStageExpressionArcsine : public UDMMaterialStageExpressionMathBase`  
_L10-16_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L15 _public prototype_ `UDMMaterialStageExpressionArcsine();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEArcSineFast.h` (Private)


#### class `UDMMaterialStageExpressionArcsineFast`  
`class UDMMaterialStageExpressionArcsineFast : public UDMMaterialStageExpressionMathBase`  
_L10-16_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L15 _public prototype_ `UDMMaterialStageExpressionArcsineFast();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEArctangent.h` (Private)


#### class `UDMMaterialStageExpressionArctangent`  
`class UDMMaterialStageExpressionArctangent : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionArctangent();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEArctangent2.h` (Private)


#### class `UDMMaterialStageExpressionArctangent2`  
`class UDMMaterialStageExpressionArctangent2 : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionArctangent2();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEArctangent2Fast.h` (Private)


#### class `UDMMaterialStageExpressionArctangent2Fast`  
`class UDMMaterialStageExpressionArctangent2Fast : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionArctangent2Fast();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEArctangentFast.h` (Private)


#### class `UDMMaterialStageExpressionArctangentFast`  
`class UDMMaterialStageExpressionArctangentFast : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionArctangentFast();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSECameraPositionWS.h` (Private)


#### class `UDMMaterialStageExpressionCameraPositionWS`  
`class UDMMaterialStageExpressionCameraPositionWS : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionCameraPositionWS();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSECameraVectorWS.h` (Private)


#### class `UDMMaterialStageExpressionCameraVectorWS`  
`class UDMMaterialStageExpressionCameraVectorWS : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionCameraVectorWS();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSECeil.h` (Private)


#### class `UDMMaterialStageExpressionCeil`  
`class UDMMaterialStageExpressionCeil : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionCeil();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEClamp.h` (Private)


#### class `UDMMaterialStageExpressionClamp`  
`class UDMMaterialStageExpressionClamp : public UDMMaterialStageExpressionMathBase`  
_L9-17_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionClamp();`
- L16 _public prototype_ `virtual void AddDefaultInput(int32 InInputIndex) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSECosine.h` (Private)


#### class `UDMMaterialStageExpressionCosine`  
`class UDMMaterialStageExpressionCosine : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionCosine();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSECrossProduct.h` (Private)


#### class `UDMMaterialStageExpressionCrossProduct`  
`class UDMMaterialStageExpressionCrossProduct : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionCrossProduct();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEDeltaTime.h` (Private)


#### class `UDMMaterialStageExpressionDeltaTime`  
`class UDMMaterialStageExpressionDeltaTime : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionDeltaTime();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEDivide.h` (Private)


#### class `UDMMaterialStageExpressionDivide`  
`class UDMMaterialStageExpressionDivide : public UDMMaterialStageExpressionMathBase`  
_L9-17_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionDivide();`
- L16 _public prototype_ `virtual void AddDefaultInput(int32 InInputIndex) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEDotProduct.h` (Private)


#### class `UDMMaterialStageExpressionDotProduct`  
`class UDMMaterialStageExpressionDotProduct : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionDotProduct();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEFloatModulo.h` (Private)


#### class `UDMMaterialStageExpressionFloatModulo`  
`class UDMMaterialStageExpressionFloatModulo : public UDMMaterialStageExpressionMathBase`  
_L9-17_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionFloatModulo();`
- L16 _public prototype_ `virtual void AddDefaultInput(int32 InInputIndex) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEFloor.h` (Private)


#### class `UDMMaterialStageExpressionFloor`  
`class UDMMaterialStageExpressionFloor : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionFloor();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEInverseLinearInterpolate.h` (Private)


#### class `UDMMaterialStageExpressionInverseLinearInterpolate`  
`class UDMMaterialStageExpressionInverseLinearInterpolate : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionInverseLinearInterpolate();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSELightVector.h` (Private)


#### class `UDMMaterialStageExpressionLightVector`  
`class UDMMaterialStageExpressionLightVector : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionLightVector();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSELightmapUVs.h` (Private)


#### class `UDMMaterialStageExpressionLightmapUVs`  
`class UDMMaterialStageExpressionLightmapUVs : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionLightmapUVs();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSELinearInterpolate.h` (Private)


#### class `UDMMaterialStageExpressionLinearInterpolate`  
`class UDMMaterialStageExpressionLinearInterpolate : public UDMMaterialStageExpressionMathBase`  
_L9-17_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionLinearInterpolate();`
- L16 _public prototype_ `virtual void AddDefaultInput(int32 InInputIndex) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSELogarithm10.h` (Private)


#### class `UDMMaterialStageExpressionLogarithm10`  
`class UDMMaterialStageExpressionLogarithm10 : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionLogarithm10();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSELogarithm2.h` (Private)


#### class `UDMMaterialStageExpressionLogarithm2`  
`class UDMMaterialStageExpressionLogarithm2 : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionLogarithm2();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEMax.h` (Private)


#### class `UDMMaterialStageExpressionMax`  
`class UDMMaterialStageExpressionMax : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionMax();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEMin.h` (Private)


#### class `UDMMaterialStageExpressionMin`  
`class UDMMaterialStageExpressionMin : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionMin();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEMultiply.h` (Private)


#### class `UDMMaterialStageExpressionMultiply`  
`class UDMMaterialStageExpressionMultiply : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionMultiply();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEObjectBounds.h` (Private)


#### class `UDMMaterialStageExpressionObjectBounds`  
`class UDMMaterialStageExpressionObjectBounds : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionObjectBounds();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEObjectOrientation.h` (Private)


#### class `UDMMaterialStageExpressionObjectOrientation`  
`class UDMMaterialStageExpressionObjectOrientation : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionObjectOrientation();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEObjectPositionWS.h` (Private)


#### class `UDMMaterialStageExpressionObjectPositionWS`  
`class UDMMaterialStageExpressionObjectPositionWS : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionObjectPositionWS();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEObjectRadius.h` (Private)


#### class `UDMMaterialStageExpressionObjectRadius`  
`class UDMMaterialStageExpressionObjectRadius : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionObjectRadius();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEOneMinus.h` (Private)


#### class `UDMMaterialStageExpressionOneMinus`  
`class UDMMaterialStageExpressionOneMinus : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionOneMinus();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEPanner.h` (Private)


#### class `UDMMaterialStageExpressionPanner`  
`class UDMMaterialStageExpressionPanner : public UDMMaterialStageExpression`  
_L9-19_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionPanner();`
- L17 _public prototype_ `virtual void AddDefaultInput(int32 InInputIndex) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEParticleColor.h` (Private)


#### class `UDMMaterialStageExpressionParticleColor`  
`class UDMMaterialStageExpressionParticleColor : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionParticleColor();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEParticleDirection.h` (Private)


#### class `UDMMaterialStageExpressionParticleDirection`  
`class UDMMaterialStageExpressionParticleDirection : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionParticleDirection();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEParticleMacroUV.h` (Private)


#### class `UDMMaterialStageExpressionParticleMacroUV`  
`class UDMMaterialStageExpressionParticleMacroUV : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionParticleMacroUV();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEParticleMotionBlurFade.h` (Private)


#### class `UDMMaterialStageExpressionParticleMotionBlurFade`  
`class UDMMaterialStageExpressionParticleMotionBlurFade : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionParticleMotionBlurFade();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEParticlePositionWS.h` (Private)


#### class `UDMMaterialStageExpressionParticlePositionWS`  
`class UDMMaterialStageExpressionParticlePositionWS : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionParticlePositionWS();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEParticleRadius.h` (Private)


#### class `UDMMaterialStageExpressionParticleRadius`  
`class UDMMaterialStageExpressionParticleRadius : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionParticleRadius();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEParticleRandom.h` (Private)


#### class `UDMMaterialStageExpressionParticleRandom`  
`class UDMMaterialStageExpressionParticleRandom : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionParticleRandom();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEParticleRelativeTime.h` (Private)


#### class `UDMMaterialStageExpressionParticleRelativeTime`  
`class UDMMaterialStageExpressionParticleRelativeTime : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionParticleRelativeTime();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEParticleSize.h` (Private)


#### class `UDMMaterialStageExpressionParticleSize`  
`class UDMMaterialStageExpressionParticleSize : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionParticleSize();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEParticleSpeed.h` (Private)


#### class `UDMMaterialStageExpressionParticleSpeed`  
`class UDMMaterialStageExpressionParticleSpeed : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionParticleSpeed();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEParticleSubUV.h` (Private)


#### class `UDMMaterialStageExpressionParticleSubUV`  
`class UDMMaterialStageExpressionParticleSubUV : public UDMMaterialStageExpressionTextureSampleBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionTextureSampleBase`
- L14 _public prototype_ `UDMMaterialStageExpressionParticleSubUV();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEParticleSubUVProperties.h` (Private)


#### class `UDMMaterialStageExpressionParticleSubUVProperties`  
`class UDMMaterialStageExpressionParticleSubUVProperties : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionParticleSubUVProperties();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEPixelDepth.h` (Private)


#### class `UDMMaterialStageExpressionPixelDepth`  
`class UDMMaterialStageExpressionPixelDepth : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionPixelDepth();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEPixelNormalWS.h` (Private)


#### class `UDMMaterialStageExpressionPixelNormalWS`  
`class UDMMaterialStageExpressionPixelNormalWS : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionPixelNormalWS();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEPower.h` (Private)


#### class `UDMMaterialStageExpressionPower`  
`class UDMMaterialStageExpressionPower : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionPower();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEReflectionVectorWS.h` (Private)


#### class `UDMMaterialStageExpressionReflectionVectorWS`  
`class UDMMaterialStageExpressionReflectionVectorWS : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionReflectionVectorWS();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSERotateAboutAxis.h` (Private)


#### class `UDMMaterialStageExpressionRotateAboutAxis`  
`class UDMMaterialStageExpressionRotateAboutAxis : public UDMMaterialStageExpression`  
_L9-21_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionRotateAboutAxis();`
- L16 _public prototype_ `virtual void AddExpressionProperties(const TArray<UMaterialExpression*>& InExpressions) const override;`
- L20 _protected member_ `float Period;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSERound.h` (Private)


#### class `UDMMaterialStageExpressionRound`  
`class UDMMaterialStageExpressionRound : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionRound();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSESceneColor.h` (Private)


#### class `UDMMaterialStageExpressionSceneColor`  
`class UDMMaterialStageExpressionSceneColor : public UDMMaterialStageExpression`  
_L10-29_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L15 _public prototype_ `UDMMaterialStageExpressionSceneColor();`
- L18 _public prototype_ `virtual void AddExpressionProperties(const TArray<UMaterialExpression*>& InExpressions) const override;`
- L22 _public function_ `virtual bool SupportsLayerMaskTextureUVLink() const override`
- L23 _public function_ `virtual int32 GetLayerMaskTextureUVLinkInputIndex() const override`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSESceneDepth.h` (Private)


#### class `UDMMaterialStageExpressionSceneDepth`  
`class UDMMaterialStageExpressionSceneDepth : public UDMMaterialStageExpression`  
_L9-20_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionSceneDepth();`
- L17 _public function_ `virtual bool SupportsLayerMaskTextureUVLink() const override`
- L18 _public function_ `virtual int32 GetLayerMaskTextureUVLinkInputIndex() const override`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSESceneTexture.h` (Private)


#### class `UDMMaterialStageExpressionSceneTexture`  
`class UDMMaterialStageExpressionSceneTexture : public UDMMaterialStageExpression`  
_L10-29_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L15 _public prototype_ `UDMMaterialStageExpressionSceneTexture();`
- L18 _public prototype_ `virtual void AddExpressionProperties(const TArray<UMaterialExpression*>& InExpressions) const override;`
- L22 _public function_ `virtual bool SupportsLayerMaskTextureUVLink() const override`
- L23 _public function_ `virtual int32 GetLayerMaskTextureUVLinkInputIndex() const override`
- L28 _protected member_ `TEnumAsByte<ESceneTextureId> SceneTextureId;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEScreenPosition.h` (Private)


#### class `UDMMaterialStageExpressionScreenPosition`  
`class UDMMaterialStageExpressionScreenPosition : public UDMMaterialStageExpression`  
_L9-20_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionScreenPosition();`
- L17 _public function_ `virtual bool SupportsLayerMaskTextureUVLink() const override`
- L18 _public function_ `virtual int32 GetLayerMaskTextureUVLinkInputIndex() const override`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSESign.h` (Private)


#### class `UDMMaterialStageExpressionSign`  
`class UDMMaterialStageExpressionSign : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionSign();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSESine.h` (Private)


#### class `UDMMaterialStageExpressionSine`  
`class UDMMaterialStageExpressionSine : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionSine();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSESmoothStep.h` (Private)


#### class `UDMMaterialStageExpressionSmoothStep`  
`class UDMMaterialStageExpressionSmoothStep : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionSmoothStep();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSESquareRoot.h` (Private)


#### class `UDMMaterialStageExpressionSquareRoot`  
`class UDMMaterialStageExpressionSquareRoot : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionSquareRoot();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEStep.h` (Private)


#### class `UDMMaterialStageExpressionStep`  
`class UDMMaterialStageExpressionStep : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionStep();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSESubtract.h` (Private)


#### class `UDMMaterialStageExpressionSubtract`  
`class UDMMaterialStageExpressionSubtract : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionSubtract();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSETangent.h` (Private)


#### class `UDMMaterialStageExpressionTangent`  
`class UDMMaterialStageExpressionTangent : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionTangent();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSETime.h` (Private)


#### class `UDMMaterialStageExpressionTime`  
`class UDMMaterialStageExpressionTime : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionTime();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSETransform.h` (Private)


#### class `UDMMaterialStageExpressionTransform`  
`class UDMMaterialStageExpressionTransform : public UDMMaterialStageExpression`  
_L10-25_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L15 _public prototype_ `UDMMaterialStageExpressionTransform();`
- L17 _public prototype_ `virtual void AddExpressionProperties(const TArray<UMaterialExpression*>& InExpressions) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSETruncate.h` (Private)


#### class `UDMMaterialStageExpressionTruncate`  
`class UDMMaterialStageExpressionTruncate : public UDMMaterialStageExpressionMathBase`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionMathBase`
- L14 _public prototype_ `UDMMaterialStageExpressionTruncate();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEUVRotator.h` (Private)


#### class `UDMMaterialStageExpressionUVRotator`  
`class UDMMaterialStageExpressionUVRotator : public UDMMaterialStageExpression`  
_L9-35_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionUVRotator();`
- L17 _public prototype_ `virtual void AddExpressionProperties(const TArray<UMaterialExpression*>& InExpressions) const override;`
- L21 _public prototype_ `virtual void AddDefaultInput(int32 InInputIndex) const override;`
- L22 _public function_ `virtual bool SupportsLayerMaskTextureUVLink() const override`
- L23 _public function_ `virtual int32 GetLayerMaskTextureUVLinkInputIndex() const override`
- L28 _protected member_ `float CenterX;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L31 _protected member_ `float CenterY;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L34 _protected member_ `float Speed;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEVertexColor.h` (Private)


#### class `UDMMaterialStageExpressionVertexColor`  
`class UDMMaterialStageExpressionVertexColor : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionVertexColor();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEVertexNormalWS.h` (Private)


#### class `UDMMaterialStageExpressionVertexNormalWS`  
`class UDMMaterialStageExpressionVertexNormalWS : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionVertexNormalWS();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEVertexTangentWS.h` (Private)


#### class `UDMMaterialStageExpressionVertexTangentWS`  
`class UDMMaterialStageExpressionVertexTangentWS : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionVertexTangentWS();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEViewSize.h` (Private)


#### class `UDMMaterialStageExpressionViewSize`  
`class UDMMaterialStageExpressionViewSize : public UDMMaterialStageExpression`  
_L9-15_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionViewSize();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEWorldPosition.h` (Private)


#### class `UDMMaterialStageExpressionWorldPosition`  
`class UDMMaterialStageExpressionWorldPosition : public UDMMaterialStageExpression`  
_L10-22_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L15 _public prototype_ `UDMMaterialStageExpressionWorldPosition();`
- L17 _public prototype_ `virtual void AddExpressionProperties(const TArray<UMaterialExpression*>& InExpressions) const override;`
- L21 _protected member_ `TEnumAsByte<EWorldPositionIncludedOffsets> WorldPositionShaderOffset;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Components/MaterialStageExpressions/DMMSEWorldPositionNoise.h` (Private)


#### class `UDMMaterialStageExpressionWorldPositionNoise`  
`class UDMMaterialStageExpressionWorldPositionNoise : public UDMMaterialStageExpression`  
_L13-93_
- reflection: `UCLASS(BlueprintType, Blueprintable, ClassGroup = "Material Designer", meta = (DisplayName = "Noise"))`
- inherits: `UDMMaterialStageExpression`
- L18 _public prototype_ `UDMMaterialStageExpressionWorldPositionNoise();`
- L21 _public prototype_ `virtual void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L25 _public function_ `virtual EDMLocationType GetLocationType() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L28 _public prototype_ `virtual void SetLocationType(EDMLocationType InLocationType);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L31 _public function_ `virtual TEnumAsByte<EWorldPositionIncludedOffsets> GetShaderOffset() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L34 _public prototype_ `virtual void SetShaderOffset(EWorldPositionIncludedOffsets InShaderOffset);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L37 _public function_ `virtual TEnumAsByte<EVectorNoiseFunction> GetNoiseFunction() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L40 _public prototype_ `virtual void SetNoiseFunction(EVectorNoiseFunction InNoiseFunction);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L43 _public function_ `virtual int32 GetQuality() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L46 _public prototype_ `virtual void SetQuality(int32 InQuality);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L49 _public function_ `virtual bool GetTiling() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L52 _public prototype_ `virtual void SetTiling(bool bInTiling);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L55 _public function_ `virtual int32 GetTileSize() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L58 _public prototype_ `virtual void SetTileSize(int32 InTileSize);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L61 _public prototype_ `virtual void AddDefaultInput(int32 InInputIndex) const override;`
- L62 _public prototype_ `virtual UMaterialExpression* GetExpressionForInput(const TArray<UMaterialExpression*>& InStageSourceExpressions, int32 InInputIndex, int32 InExpressionInputIndex) override;`
- L66 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L72 _protected member_ `EDMLocationType LocationType;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter = SetLocationType, BlueprintSetter = SetLocationType, Category = "Material Designer", meta = (NotKeyframeable, AllowPrivateAccess = "true"))`
- L76 _protected member_ `TEnumAsByte<EWorldPositionIncludedOffsets> ShaderOffset;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter = SetShaderOffset, BlueprintSetter = SetShaderOffset, Category = "Material Designer", meta = (NotKeyframeable, AllowPrivateAccess = "true"))`
- L80 _protected member_ `TEnumAsByte<EVectorNoiseFunction> NoiseFunction;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter = SetNoiseFunction, BlueprintSetter = SetNoiseFunction, Category = "Material Designer", meta = (NotKeyframeable, AllowPrivateAccess = "true"))`
- L84 _protected member_ `int32 Quality;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter = SetQuality, BlueprintSetter = SetQuality, Category = "Material Designer", meta = (NotKeyframeable, AllowPrivateAccess = "true", UIMin = "1", UIMax = "4", ClampMin = "1", ClampMax = "4"))`
- L88 _protected member_ `bool bTiling;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter = SetTiling, BlueprintSetter = SetTiling, Category = "Material Designer", meta = (NotKeyframeable, AllowPrivateAccess = "true"))`
- L92 _protected member_ `int32 TileSize;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter = SetTileSize, BlueprintSetter = SetTileSize, Category = "Material Designer", meta = (NotKeyframeable, AllowPrivateAccess = "true", EditCondition="bTiling", EditConditionHides))`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/DMContentBrowserIntegration.h` (Private)


#### class `FDMContentBrowserIntegration`  
`class FDMContentBrowserIntegration`  
_L16-44_
- L19 _public prototype_ `static void Integrate();`
- L21 _public prototype_ `static void Disintegrate();`
- L23 _public prototype_ `static void UpdateMaterialDesignerMaterialFromTextureSet(TArray<FAssetData> InSelectedAssets, bool bInReplace);`
- L26 _protected member_ `static FDelegateHandle TextureSetPopulateHandle;`
- L27 _protected member_ `static FDelegateHandle ContentBrowserAssetHandle;`
- L29 _protected prototype_ `static void ExtendMenu(FMenuBuilder& InMenuBuilder, const TArray<FAssetData>& InSelectedAssets);`
- L31 _protected prototype_ `static void CreateMaterialDesignerMaterialFromTextureSet(TArray<FAssetData> InSelectedAssets);`
- L33 _protected prototype_ `static void OnCreateMaterialDesignerMaterialFromTextureSetComplete(UDMTextureSet* InTextureSet, bool bInAccepted, FString InPath);`
- L35 _protected prototype_ `static void OnUpdateMaterialDesignerMaterialFromTextureSetComplete(UDMTextureSet* InTextureSet, bool bInAccepted, bool bInReplace);`
- L37 _protected prototype_ `static TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& InSelectedAssets);`
- L39 _protected prototype_ `static void CreateInstance(TArray<FAssetData> InSelectedAssets);`
- L41 _protected prototype_ `static void CreateModelInstance(UDynamicMaterialModel* InModel);`
- L43 _protected prototype_ `static void CreateMaterialInstance(UDynamicMaterialInstance* InInstance);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/DetailsPanel/Customizations/DMStageEditDetailsCustomization.h` (Private)


#### class `FDMStageEditDetailsCustomization`  
`class FDMStageEditDetailsCustomization : public IPropertyTypeCustomization`  
_L13-28_
- inherits: `IPropertyTypeCustomization`
- desc: Material Designer Stage Edit Details Customization
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L22 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L27 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/DetailsPanel/DMMaterialInterfaceTypeCustomizer.h` (Private)


#### class `FDMMaterialInterfaceTypeIdentifier`  
`class FDMMaterialInterfaceTypeIdentifier : public IPropertyTypeIdentifier`  
_L10-16_
- inherits: `IPropertyTypeIdentifier`
- L14 _public prototype_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& InPropertyHandle) const override;`

#### class `FDMMaterialInterfaceTypeCustomizer`  
`class FDMMaterialInterfaceTypeCustomizer : public IPropertyTypeCustomization`  
_L18-32_
- inherits: `IPropertyTypeCustomization`
- L21 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L23 _public prototype_ `FDMMaterialInterfaceTypeCustomizer();`
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> EditorPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — BEGIN IPropertyTypeCustomization interface
- L29 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> EditorPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/DetailsPanel/DMPropertyTypeCustomizer.h` (Private)


#### class `FDMPropertyTypeCustomizer`  
`class FDMPropertyTypeCustomizer : public IPropertyTypeCustomization`  
_L9-23_
- inherits: `IPropertyTypeCustomization`
- L12 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L14 _public prototype_ `FDMPropertyTypeCustomizer();`
- L17 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> EditorPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — Begin IPropertyTypeCustomization interface
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> EditorPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/DetailsPanel/DMValueDetailsRowExtensions.h` (Private)


#### class `FDMValueDetailsRowExtensions`  
`class FDMValueDetailsRowExtensions`  
_L18-46_
- L21 _public prototype_ `static FDMValueDetailsRowExtensions& Get();`
- L23 _public prototype_ `~FDMValueDetailsRowExtensions();`
- L25 _public prototype_ `void RegisterRowExtensions();`
- L27 _public prototype_ `void UnregisterRowExtensions();`
- L30 _private member_ `FDelegateHandle RowExtensionHandle;`
- L32 _private prototype_ `static void HandleCreatePropertyRowExtension(const FOnGenerateGlobalRowExtensionArgs& InArgs, TArray<FPropertyRowExtensionButton>& OutExtensions);`
- L34 _private prototype_ `static void FillPropertyRightClickMenu(UToolMenu* InToolMenu);`
- L36 _private prototype_ `static void FillPropertyRightClickMenu_TextureUV(FToolMenuSection& InSection, UDMTextureUV* InTextureUV, FName InPropertyName);`
- L38 _private prototype_ `static void FillPropertyRightClickMenu_Value(FToolMenuSection& InSection, UDMMaterialValue* InValue);`
- L40 _private prototype_ `static void SetValueParameterName(TWeakObjectPtr<UDMMaterialValue> InValueWeak, FName InName);`
- L42 _private prototype_ `static void SetTextureUVParameterName(TWeakObjectPtr<UDMTextureUV> InTextureUVWeak, FName InPropertyName, int32 InComponent, FName InName);`
- L45 _private prototype_ `static bool VerifyParameterName(const FText& InValue, FText& OutErrorText);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/DetailsPanel/Widgets/SDMDetailsPanelMaterialInterfaceWidget.h` (Private)


#### class `SDMDetailsPanelMaterialInterfaceWidget`  
`class SDMDetailsPanelMaterialInterfaceWidget : public SCompoundWidget`  
_L15-39_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SDMDetailsPanelMaterialInterfaceWidget)`
- L19 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FAssetThumbnailPool>, ThumbnailPool) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InPropertyHandle);`
- L25 _protected member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L27 _protected prototype_ `UObject* GetAsset() const;`
- L28 _protected prototype_ `void SetAsset(UObject* NewAsset);`
- L30 _protected prototype_ `UDynamicMaterialInstance* GetMaterialDesignerMaterial() const;`
- L31 _protected prototype_ `void SetMaterialDesignerMaterial(UDynamicMaterialInstance* InMaterial);`
- L33 _protected prototype_ `FReply OnButtonClicked();`
- L34 _protected prototype_ `FReply CreateMaterialDesignerMaterial();`
- L35 _protected prototype_ `FReply ClearMaterialDesignerMaterial();`
- L36 _protected prototype_ `FReply OpenMaterialDesignerTab();`
- L38 _protected prototype_ `FText GetButtonText() const;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/DetailsPanel/Widgets/SDMDetailsPanelTabSpawner.h` (Private)


#### class `SDMDetailsPanelTabSpawner`  
`class SDMDetailsPanelTabSpawner : public SCompoundWidget`  
_L15-37_
- inherits: `SCompoundWidget`
- L17 _private function_ `SLATE_BEGIN_ARGS(SDMDetailsPanelTabSpawner)`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InPropertyHandle);`
- L24 _protected member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L26 _protected prototype_ `UDynamicMaterialModelBase* GetMaterialModelBase() const;`
- L27 _protected prototype_ `void SetMaterialModelBase(UDynamicMaterialModelBase* InNewModel);`
- L29 _protected prototype_ `FReply OnButtonClicked();`
- L30 _protected prototype_ `FReply CreateDynamicMaterialModel();`
- L31 _protected prototype_ `FReply ClearDynamicMaterialModel();`
- L32 _protected prototype_ `FReply OpenDynamicMaterialModelTab();`
- L34 _protected prototype_ `FText GetButtonText() const;`
- L35 _protected prototype_ `FString GetEditorPath() const;`
- L36 _protected prototype_ `void OnEditorChanged(const FAssetData& InAssetData);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/DetailsPanel/Widgets/SDMMaterialListExtensionWidget.h` (Private)


#### class `SDMMaterialListExtensionWidget`  
`class SDMMaterialListExtensionWidget : public SCompoundWidget`  
_L17-44_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SDMMaterialListExtensionWidget)`
- L23 _public prototype_ `virtual ~SDMMaterialListExtensionWidget() override = default;`
- L25 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FMaterialItemView>& InMaterialItemView, UPrimitiveComponent* InCurrentComponent, IDetailLayoutBuilder& InDetailBuilder);`
- L29 _protected member_ `TWeakPtr<FMaterialItemView> MaterialItemViewWeak;`
- L30 _protected member_ `TWeakObjectPtr<UPrimitiveComponent> CurrentComponentWeak;`
- L32 _protected prototype_ `UObject* GetAsset() const;`
- L33 _protected prototype_ `void SetAsset(UObject* NewAsset);`
- L35 _protected prototype_ `UDynamicMaterialInstance* GetMaterialDesignerMaterial() const;`
- L36 _protected prototype_ `void SetMaterialDesignerMaterial(UDynamicMaterialInstance* InMaterial);`
- L38 _protected prototype_ `FReply OnButtonClicked();`
- L39 _protected prototype_ `FReply CreateMaterialDesignerMaterial();`
- L40 _protected prototype_ `FReply ClearMaterialDesignerMaterial();`
- L41 _protected prototype_ `FReply OpenMaterialDesignerTab();`
- L43 _protected prototype_ `FText GetButtonText() const;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/DynamicMaterialEditorCommands.h` (Private)


#### class `FDynamicMaterialEditorCommands`  
`class FDynamicMaterialEditorCommands : public TCommands<FDynamicMaterialEditorCommands>`  
_L7-40_
- inherits: `TCommands<FDynamicMaterialEditorCommands>`
- L10 _public prototype_ `FDynamicMaterialEditorCommands();`
- L13 _public prototype_ `virtual void RegisterCommands() override;`
- L16 _public member_ `TSharedPtr<FUICommandInfo> OpenEditorSettingsWindow;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> AddDefaultLayer;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> InsertDefaultLayerAbove;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> SelectLayerBaseStage;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> SelectLayerMaskStage;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> MoveLayerUp;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> MoveLayerDown;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> SetCustomPreviewMesh;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> NavigateForward;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> NavigateBack;`
- L30 _public member_ `TArray<TSharedPtr<FUICommandInfo>, TInlineAllocator<10>> SelectLayers;` — Individual commands are initialised as SelectLayerX
- L39 _public member_ `TMap<FKey, FOpacityCommand> SetOpacities;` — Individual commands are initialised as SetOpacityX

#### struct `FDynamicMaterialEditorCommands::FOpacityCommand`  
`struct FOpacityCommand`  
_L32-36_
- L34 _public member_ `const float Opacity;`
- L35 _public member_ `TSharedRef<FUICommandInfo> Command;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/DynamicMaterialEditorModule.h` (Private)


#### class `FDynamicMaterialEditorModule`  
`class FDynamicMaterialEditorModule : public IDynamicMaterialEditorModule`  
_L42-94_
- inherits: `IDynamicMaterialEditorModule`
- desc: Material Designer - Build your own materials in a slimline editor!
- L45 _public member_ `static const FName TabId;`
- L46 _public function_ `static FDMOnUIValueUpdate::RegistrationType& GetOnUIValueUpdate()`
- L48 _public prototype_ `static FDynamicMaterialEditorModule& Get();`
- L50 _public prototype_ `static FDMComponentPropertyRowGeneratorDelegate GetComponentPropertyRowGeneratorDelegate(UClass* InClass);`
- L51 _public prototype_ `static void GeneratorComponentPropertyRows(FDMComponentPropertyRowGeneratorParams& InParams);`
- L53 _public prototype_ `static FDMGetObjectMaterialPropertiesDelegate GetCustomMaterialPropertyGenerator(UClass* InClass);`
- L56 _public prototype_ `static TSharedRef<SWidget> CreateEditor(UDynamicMaterialModelBase* InMaterialModelBase, UWorld* InAssetEditorWorld);` — With a provided world, the editor will bind to the MD world subsystem to receive model changes.
- L58 _public prototype_ `FDynamicMaterialEditorModule();`
- L60 _public function_ `const TSharedRef<FUICommandList>& GetCommandList() const`
- L62 _public prototype_ `void OnWizardComplete(UDynamicMaterialModel* InModel);`
- L65 _public prototype_ `virtual void RegisterComponentPropertyRowGeneratorDelegate(UClass* InClass, FDMComponentPropertyRowGeneratorDelegate InComponentPropertyRowGeneratorDelegate) override;`
- L66 _public prototype_ `virtual void RegisterCustomMaterialPropertyGenerator(UClass* InClass, FDMGetObjectMaterialPropertiesDelegate InGenerator) override;`
- L67 _public prototype_ `virtual void RegisterMaterialModelCreatedCallback(const TSharedRef<IDMOnWizardCompleteCallback> InCallback) override;`
- L68 _public prototype_ `virtual void UnregisterMaterialModelCreatedCallback(const TSharedRef<IDMOnWizardCompleteCallback> InCallback) override;`
- L69 _public prototype_ `virtual void OpenEditor(UWorld* InWorld) const override;`
- L70 _public prototype_ `virtual UDynamicMaterialModelBase* GetOpenedMaterialModel(UWorld* InWorld) const override;`
- L71 _public prototype_ `virtual void OpenMaterialModel(UDynamicMaterialModelBase* InMaterialModel, UWorld* InWorld, bool bInInvokeTab) const override;`
- L72 _public prototype_ `virtual void OpenMaterialObjectProperty(const FDMObjectMaterialProperty& InObjectProperty, UWorld* InWorld, bool bInInvokeTab) const override;`
- L73 _public prototype_ `virtual void OpenMaterial(UDynamicMaterialInstance* InMaterial, UWorld* InWorld, bool bInInvokeTab) const override;`
- L74 _public prototype_ `virtual void OnActorSelected(AActor* InActor, UWorld* InWorld, bool bInInvokeTab) const override;`
- L75 _public prototype_ `virtual void ClearDynamicMaterialModel(UWorld* InWorld) const override;`
- L76 _public prototype_ `virtual IDMWidgetLibrary& GetWidgetLibrary() const override;`
- L80 _public prototype_ `virtual void StartupModule() override;`
- L81 _public prototype_ `virtual void ShutdownModule() override;`
- L85 _protected member_ `static TMap<UClass*, FDMComponentPropertyRowGeneratorDelegate> ComponentPropertyRowGenerators;`
- L86 _protected member_ `static TMap<UClass*, FDMGetObjectMaterialPropertiesDelegate> CustomMaterialPropertyGenerators;`
- L87 _protected member_ `static FDMOnUIValueUpdate OnUIValueUpdate;`
- L88 _protected member_ `static TArray<TSharedRef<IDMOnWizardCompleteCallback>> OnWizardCompleteCallbacks;`
- L90 _protected member_ `TSharedRef<FUICommandList> CommandList;`
- L92 _protected prototype_ `void MapCommands();`
- L93 _protected prototype_ `void UnmapCommands();`

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDynamicMaterialEditor, Log, All);`
- L25 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDynamicMaterialEditor, Log, All);`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace DynamicMaterialEditor` (scope `UE`)
- L29 _variable_ `constexpr bool bMultipleSlotPropertiesEnabled = false;` (scope `UE::DynamicMaterialEditor`)
- L30 _variable_ `constexpr bool bGlobalValuesEnabled = false;` (scope `UE::DynamicMaterialEditor`)
- L31 _variable_ `constexpr bool bAdvancedSlotsEnabled = false;` (scope `UE::DynamicMaterialEditor`)
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE(FDMOnUIValueUpdate);`
- L34 _prototype_ `DECLARE_MULTICAST_DELEGATE(FDMOnUIValueUpdate);`
- L37 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedPtr<SWidget>, FDMCreateValueEditWidgetDelegate, const TSharedPtr<SDMMaterialComponentEditor>&, UDMMaterialValue*);` — Takes a UMaterialValue and returns the widget used to edit it.
- L37 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedPtr<SWidget>, FDMCreateValueEditWidgetDelegate, const TSharedPtr<SDMMaterialComponentEditor>&, UDMMaterialValue*);` — Takes a UMaterialValue and returns the widget used to edit it.

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/DynamicMaterialEditorSettings.h` (Private)


#### struct `FDMMaterialEffectList`  
`struct FDMMaterialEffectList`  
_L21-30_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public member_ `FString Name;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Effects")`
- L29 _public member_ `TArray<TSoftObjectPtr<UMaterialFunctionInterface>> Effects;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Effects")`

#### enum `EDMDefaultMaterialPropertySlotValueType`  
`enum class EDMDefaultMaterialPropertySlotValueType : uint8`  
_L33-37_
- reflection: `UENUM(BlueprintType)`
- L35 _public enumerator_ `Texture`
- L36 _public enumerator_ `Color`

#### struct `FDMDefaultMaterialPropertySlotValue`  
`struct FDMDefaultMaterialPropertySlotValue`  
_L40-58_
- reflection: `USTRUCT(BlueprintType)`
- L44 _public prototype_ `FDMDefaultMaterialPropertySlotValue();`
- L45 _public prototype_ `FDMDefaultMaterialPropertySlotValue(const TSoftObjectPtr<UTexture>& InTexture);`
- L46 _public prototype_ `FDMDefaultMaterialPropertySlotValue(const FLinearColor& InColor);`
- L47 _public prototype_ `FDMDefaultMaterialPropertySlotValue(EDMDefaultMaterialPropertySlotValueType InDefaultType, const TSoftObjectPtr<UTexture>& InTexture, const FLinearColor& InColor);`
- L51 _public member_ `EDMDefaultMaterialPropertySlotValueType DefaultType;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Material Designer")`
- L54 _public member_ `TSoftObjectPtr<UTexture> Texture;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Material Designer")`
- L57 _public member_ `FLinearColor Color;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Material Designer")`

#### struct `FDMMaterialChannelListPreset`  
`struct FDMMaterialChannelListPreset`  
_L61-166_
- reflection: `USTRUCT(BlueprintType)`
- L66 _public member_ `FName Name;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L69 _public member_ `bool bBaseColor = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L72 _public member_ `bool bEmissive = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L75 _public member_ `bool bOpacity = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L78 _public member_ `bool bRoughness = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L81 _public member_ `bool bSpecular = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L84 _public member_ `bool bMetallic = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L87 _public member_ `bool bNormal = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L90 _public member_ `bool bPixelDepthOffset = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L93 _public member_ `bool bWorldPositionOffset = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L96 _public member_ `bool bAmbientOcclusion = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L99 _public member_ `bool bAnisotropy = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L102 _public member_ `bool bRefraction = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L105 _public member_ `bool bTangent = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L108 _public member_ `bool bDisplacement = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L111 _public member_ `bool bSubsurfaceColor = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L114 _public member_ `bool bSurfaceThickness = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L117 _public member_ `TEnumAsByte<EBlendMode> DefaultBlendMode = BLEND_Opaque;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L120 _public member_ `EDMMaterialShadingModel DefaultShadingModel = EDMMaterialShadingModel::Unlit;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channel")`
- L124 _public member_ `int32 UsageFlag = 0;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Usage", meta = (Bitmask, BitmaskEnum = "/Script/DynamicMaterialEditor.EDMMaterialFlagsUsage"))`
- L128 _public member_ `uint8 GeneralFlags = 0;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", meta = (Bitmask, BitmaskEnum = "/Script/DynamicMaterialEditor.EDMMaterialFlagsGeneral"))`
- L132 _public member_ `uint8 LightingFlags = 0;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Lighting", meta = (Bitmask, BitmaskEnum = "/Script/DynamicMaterialEditor.EDMMaterialFlagsLighting"))`
- L136 _public member_ `uint8 TranslucencyFlags = 0;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Translucency", meta = (Bitmask, BitmaskEnum = "/Script/DynamicMaterialEditor.EDMMaterialFlagsTranslucency"))`
- L140 _public member_ `uint8 MotionFlags = 0;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Motion", meta = (Bitmask, BitmaskEnum = "/Script/DynamicMaterialEditor.EDMMaterialFlagsMotion"))`
- L144 _public member_ `uint8 ForwardRendererFlags = 0;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Forward Renderer", meta = (Bitmask, BitmaskEnum = "/Script/DynamicMaterialEditor.EDMMaterialFlagsForwardRenderer"))`
- L146 _public prototype_ `bool IsPropertyEnabled(EDMMaterialPropertyType InProperty) const;`
- L153 _public member_ `bool bDefaultAnimated_DEPRECATED = false;` — `UE_DEPRECATED(5.8, "Moved to MotionFlags")` — `UPROPERTY(Config, meta = (DeprecatedProperty, DeprecationMessage = "Moved to MotionFlags"))` — Deprecated
- L157 _public member_ `bool bDefaultTwoSided_DEPRECATED = true;` — `UE_DEPRECATED(5.8, "Moved to GeneralFlags")` — `UPROPERTY(Config, meta = (DeprecatedProperty, DeprecationMessage = "Moved to GeneralFlags"))`
- L160 _public prototype_ `FDMMaterialChannelListPreset() = default;`
- L161 _public prototype_ `FDMMaterialChannelListPreset(const FDMMaterialChannelListPreset&) = default;`
- L162 _public prototype_ `FDMMaterialChannelListPreset(FDMMaterialChannelListPreset&&) = default;`
- L163 _public prototype_ `FDMMaterialChannelListPreset& operator=(const FDMMaterialChannelListPreset&) = default;`
- L164 _public prototype_ `FDMMaterialChannelListPreset& operator=(FDMMaterialChannelListPreset&&) = default;`

#### enum `EDMMaterialPreviewMesh`  
`enum class EDMMaterialPreviewMesh : uint8`  
_L169-176_
- reflection: `UENUM(BlueprintType)`
- L171 _public enumerator_ `Plane`
- L172 _public enumerator_ `Cube`
- L173 _public enumerator_ `Sphere`
- L174 _public enumerator_ `Cylinder`
- L175 _public enumerator_ `Custom`

#### enum `EDMMaterialEditorLayout`  
`enum class EDMMaterialEditorLayout : uint8`  
_L179-187_
- reflection: `UENUM(BlueprintType)`
- L181 _public enumerator_ `Top`
- L182 _public enumerator_ `TopSlim`
- L183 _public enumerator_ `Left`
- L185 _public enumerator_ `First = Top`
- L186 _public enumerator_ `Last = Left`

#### enum `EDMLiveEditMode`  
`enum class EDMLiveEditMode : uint8`  
_L190-195_
- reflection: `UENUM(BlueprintType)`
- L192 _public enumerator_ `Disabled`
- L193 _public enumerator_ `LiveEditOff`
- L194 _public enumerator_ `LiveEditOn`

#### struct `FDMContentBrowserThumbnailSettings`  
`struct FDMContentBrowserThumbnailSettings`  
_L198-213_
- reflection: `USTRUCT()`
- L203 _public member_ `EDMMaterialPreviewMesh PreviewMesh = EDMMaterialPreviewMesh::Custom;` — `UPROPERTY(Config, EditAnywhere, Category = "Preview")`
- L206 _public member_ `float CustomMeshOrbitPitch = -30.f;` — `UPROPERTY(Config, EditAnywhere, Category = "Preview", meta = (EditCondition = "PreviewMesh == EDMMaterialPreviewMesh::Custom", EditConditionHides))`
- L209 _public member_ `float CustomMeshOrbitYaw = 152.f;` — `UPROPERTY(Config, EditAnywhere, Category = "Preview", meta = (EditCondition = "PreviewMesh == EDMMaterialPreviewMesh::Custom", EditConditionHides))`
- L212 _public member_ `float CustomMeshZoom = -409.f;` — `UPROPERTY(Config, EditAnywhere, Category = "Preview", meta = (EditCondition = "PreviewMesh == EDMMaterialPreviewMesh::Custom", EditConditionHides))`

#### class `UDynamicMaterialEditorSettings`  
`class UDynamicMaterialEditorSettings : public UDeveloperSettings`  
_L219-422_
- reflection: `UCLASS(Config=EditorPerProjectUserSettings, meta = (DisplayName = "Material Designer"))`
- inherits: `UDeveloperSettings`
- desc: Material Designer Settings
- L226 _public prototype_ `UDynamicMaterialEditorSettings();`
- L227 _public prototype_ `virtual ~UDynamicMaterialEditorSettings() override = default;`
- L229 _public prototype_ `DLLEXPORT static UDynamicMaterialEditorSettings* Get();`
- L233 _public member_ `bool bFollowSelection;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Editor")` — Changes the currently active material in the designer following actor/object selection.
- L240 _public member_ `bool bAddDetailsPanelButton;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Editor")` — If true, a "Create with Material Designer" button will show on properties and material lists. The edit buttons will always appear.
- L249 _protected member_ `bool bAutomaticallyCopyParametersToSourceMaterial;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Editor")` — When properties on the preview material are changed, if they are parameter-based then automatically also set those values on the source material (in the world or asset). This value is only used when Live Edit mode is disabled.
- L255 _protected member_ `bool bAutomaticallyCompilePreviewMaterial;` — `UPROPERTY(Config, EditAnywhere, Category = "Editor", meta = (EditCondition = "LiveEditMode == EDMLiveEditMode::Disabled"))` — When a structural material change is made, whether to automatically recompile the preview material to show this change.
- L261 _protected member_ `bool bAutomaticallyApplyToSourceOnPreviewCompile;` — `UPROPERTY(Config, EditAnywhere, Category = "Editor", meta = (EditCondition = "LiveEditMode == EDMLiveEditMode::Disabled"))` — When the preview material is recompiled, whether to automatically also apply those changes to the source material.
- L268 _public member_ `EDMLiveEditMode LiveEditMode;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Editor")` — When enabled, reduces compile options to a single mode called Live Edit.
- L271 _public function_ `bool ShouldAutomaticallyCopyParametersToSourceMaterial() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L282 _public function_ `bool ShouldAutomaticallyCompilePreviewMaterial() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L298 _public function_ `bool ShouldAutomaticallyApplyToSourceOnPreviewCompile() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L314 _public member_ `EDMMaterialEditorLayout Layout;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Layout")`
- L319 _public member_ `float SplitterLocation;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Layout", meta = ( ClampMin = "0.05", UIMin = "0.05", ClampMax = "0.95", UIMax = "0.95"))` — Adjusts the vertical size of the material layer view.
- L324 _public member_ `float PreviewSplitterLocation;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Layout", meta = ( ClampMin = "0.05", UIMin = "0.05", ClampMax = "0.95", UIMax = "0.95"))` — Adjusts the vertical size of the material layer view.
- L327 _public member_ `bool bUVVisualizerVisible;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Layout")`
- L330 _public member_ `bool bUseFullChannelNamesInTopSlimLayout;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Layout")`
- L333 _public member_ `float StagePreviewSize;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Layout")`
- L336 _public member_ `float PropertyPreviewSize;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Layout", meta = (DisplayName = "Channel Preview Size"))`
- L339 _public member_ `double ThumbnailSize;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Thumnnails")`
- L342 _public member_ `EDMMaterialPreviewMesh PreviewMesh;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Preview")`
- L345 _public member_ `TSoftObjectPtr<UStaticMesh> CustomPreviewMesh;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Preview")`
- L348 _public member_ `FDMContentBrowserThumbnailSettings ContentBrowserThumbnail;` — `UPROPERTY(Config, EditAnywhere, Category = "Preview")`
- L351 _public member_ `bool bShowPreviewBackground;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Preview")`
- L354 _public member_ `bool bPreviewImagesUseTextureUVs;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Preview")`
- L357 _public member_ `TSoftObjectPtr<UTexture> DefaultMask;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Preview")`
- L363 _public member_ `TMap<EDMMaterialPropertyType, FDMDefaultMaterialPropertySlotValue> DefaultSlotValueOverrides;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channels")` — Overrides the default values given to slots created in the given material property.
- L380 _public member_ `TArray<FName> CustomEffectsFolders;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Effects")` — Add paths to search for custom effects. Format examples: - /Game/Some/Path - /Plugin/Some/Path The assets must be in a sub-folder of the base path. The sub-folder will be used as the category name. Asset Examples: - /Game/Some/Path/UV/Asset.Asset -> Category: UV - /Plugin/Some/Path/Color/OtherAsset.OtherAsset -> Category: Color
- L383 _public member_ `TArray<FDMMaterialChannelListPreset> MaterialChannelPresets;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Channels", meta = (TitleProperty = Name))`
- L386 _public member_ `bool bUseLinearColorForVectors;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Material Functions")`
- L389 _public member_ `bool bValidatedPresets = false;` — `UPROPERTY(Config)`
- L392 _public member_ `bool bConvertedVarsToFlags = false;` — `UPROPERTY(Config)`
- L395 _public prototype_ `static bool IsUseLinearColorForVectorsEnabled();` — This variable is accessed in multiple places, so this is a quick accessor.
- L397 _public prototype_ `void OpenEditorSettingsWindow() const;`
- L399 _public prototype_ `void ResetAllLayoutSettings();`
- L401 _public prototype_ `TArray<FDMMaterialEffectList> GetEffectList() const;`
- L403 _public prototype_ `const FDMDefaultMaterialPropertySlotValue& GetDefaultSlotValue(EDMMaterialPropertyType InProperty) const;`
- L405 _public prototype_ `const FDMMaterialChannelListPreset* GetPresetByName(FName InName) const;`
- L407 _public prototype_ `FOnFinishedChangingProperties::RegistrationType& GetOnSettingsChanged();`
- L410 _public prototype_ `virtual void PostInitProperties() override;`
- L411 _public prototype_ `virtual void PreEditChange(FEditPropertyChain& InPropertyAboutToChange) override;`
- L412 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L416 _private member_ `TArray<FName> PreEditPresetNames;`
- L417 _private member_ `FOnFinishedChangingProperties OnSettingsChanged;`
- L419 _private prototype_ `void EnsureUniqueChannelPresetNames();`
- L421 _private prototype_ `void ConvertDeprecatedVarsToFlags();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/DynamicMaterialEditorStyle.h` (Private)


#### class `FDynamicMaterialEditorStyle`  
`class FDynamicMaterialEditorStyle final : public FSlateStyleSet`  
_L10-30_
- inherits: `FSlateStyleSet`
- L13 _public function_ `static FDynamicMaterialEditorStyle& Get()`
- L19 _public prototype_ `FDynamicMaterialEditorStyle();`
- L23 _private prototype_ `void SetupGeneralStyles();`
- L24 _private prototype_ `void SetupStageStyles();`
- L25 _private prototype_ `void SetupLayerViewStyles();`
- L26 _private prototype_ `void SetupLayerViewItemHandleStyles();`
- L27 _private prototype_ `void SetupEffectsViewStyles();`
- L28 _private prototype_ `void SetupTextStyles();`
- L29 _private prototype_ `void SetupComponentIcons();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/LevelEditor/DMLevelEditorIntegration.h` (Private)


#### class `FDMLevelEditorIntegration`  
`class FDMLevelEditorIntegration`  
_L11-26_
- L14 _public prototype_ `static void Initialize();`
- L16 _public prototype_ `static void Shutdown();`
- L18 _public prototype_ `static TSharedPtr<SDMMaterialDesigner> GetMaterialDesignerForWorld(UWorld* InWorld);`
- L20 _public prototype_ `static TSharedPtr<SDockTab> InvokeTabForWorld(UWorld* InWorld);`
- L23 _private prototype_ `static void OnMapTearDown(UWorld* InWorld);`
- L25 _private prototype_ `static void OnMapLoad(UWorld* InWorld);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/LevelEditor/DMLevelEditorIntegrationInstance.h` (Private)


#### struct `FDMLevelEditorIntegrationInstance`  
`struct FDMLevelEditorIntegrationInstance`  
_L18-66_
- L21 _public prototype_ `static const FDMLevelEditorIntegrationInstance* AddIntegration(const TSharedRef<ILevelEditor>& InLevelEditor);`
- L23 _public prototype_ `static void RemoveIntegrations();`
- L25 _public prototype_ `static const FDMLevelEditorIntegrationInstance* GetIntegrationForWorld(UWorld* InWorld);`
- L27 _public prototype_ `static FDMLevelEditorIntegrationInstance* GetMutableIntegrationForWorld(UWorld* InWorld);`
- L29 _public prototype_ `~FDMLevelEditorIntegrationInstance();`
- L31 _public prototype_ `TSharedPtr<SDMMaterialDesigner> GetMaterialDesigner() const;`
- L33 _public prototype_ `TSharedPtr<SDockTab> InvokeTab() const;`
- L35 _public prototype_ `const FString& GetLastOpenAssetPartialPath() const;`
- L37 _public prototype_ `void SetLastAssetOpenPartialPath(const FString& InPath);`
- L40 _private member_ `static TArray<FDMLevelEditorIntegrationInstance, TInlineAllocator<1>> Instances;`
- L42 _private prototype_ `static void ValidateInstances();`
- L44 _private member_ `TWeakPtr<ILevelEditor> LevelEditorWeak;`
- L45 _private member_ `TWeakObjectPtr<UTypedElementSelectionSet> ActorSelectionSetWeak;`
- L46 _private member_ `TWeakObjectPtr<UTypedElementSelectionSet> ObjectSelectionSetWeak;`
- L47 _private member_ `TWeakPtr<SDMMaterialDesigner> MaterialDesignerWeak;`
- L48 _private member_ `FString LastOpenAssetPartialPath;`
- L49 _private member_ `TWeakObjectPtr<AActor> LastSelectedActorWeak;`
- L51 _private prototype_ `FDMLevelEditorIntegrationInstance(const TSharedRef<ILevelEditor>& InLevelEditor);`
- L53 _private prototype_ `void RegisterSelectionChange();`
- L55 _private prototype_ `void UnregisterSelectionChange();`
- L57 _private prototype_ `void RegisterWithTabManager();`
- L59 _private prototype_ `void UnregisterWithTabManager();`
- L61 _private prototype_ `void OnActorSelectionChanged(const UTypedElementSelectionSet* InSelectionSet);`
- L63 _private prototype_ `void OnActorSelected(AActor* InActor);`
- L65 _private prototype_ `void OnObjectSelectionChanged(const UTypedElementSelectionSet* InSelectionSet);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Material/AssetDefinition_DynamicMaterialInstance.h` (Private)


#### class `UAssetDefinition_DynamicMaterialInstance`  
`class UAssetDefinition_DynamicMaterialInstance : public UAssetDefinitionDefault`  
_L11-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L18 _public prototype_ `virtual FText GetAssetDisplayName(const FAssetData& InAssetData) const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L22 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAsset) const override;`
- L23 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& InOpenArgs) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Model/AssetDefinition_DynamicMaterialModel.h` (Private)


#### class `UAssetDefinition_DynamicMaterialModel`  
`class UAssetDefinition_DynamicMaterialModel : public UAssetDefinitionDefault`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual FText GetAssetDisplayName(const FAssetData& InAssetData) const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L20 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& InOpenArgs) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Model/AssetDefinition_DynamicMaterialModelDynamic.h` (Private)


#### class `UAssetDefinition_DynamicMaterialModelDynamic`  
`class UAssetDefinition_DynamicMaterialModelDynamic : public UAssetDefinitionDefault`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual FText GetAssetDisplayName(const FAssetData& InAssetData) const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L20 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& InOpenArgs) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Model/DMMaterialModelDefaults.h` (Private)


#### class `FDMMaterialModelDefaults`  
`class FDMMaterialModelDefaults`  
_L7-13_
- L10 _public prototype_ `static void RegisterDefaultsDelegates();`
- L12 _public prototype_ `static void UnregsiterDefaultsDelegates();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Model/DMMaterialNodeArranger.h` (Private)


#### class `FDMMaterialNodeArranger`  
`class FDMMaterialNodeArranger`  
_L14-32_
- desc: Algorithm for arranging material nodes.
- L17 _public prototype_ `FDMMaterialNodeArranger(UMaterial* InDynamicMaterial);`
- L19 _public prototype_ `void ArrangeNodes();`
- L22 _protected prototype_ `static int32 GetNodeWidth(UMaterialExpression& InNode);`
- L24 _protected member_ `UMaterial* DynamicMaterial;`
- L25 _protected member_ `TMap<UMaterialExpression*, FIntPoint> NodePositions;`
- L26 _protected member_ `FIntPoint OffsetStart = {0, 0};`
- L28 _protected prototype_ `void ArrangeMaterialInputNodes(UMaterialExpression* MaterialInputExpression);`
- L30 _protected prototype_ `void ArrangeNode(TMap<UMaterialExpression*, FIntPoint>& InOutNodePositions, const FIntPoint& InOffsetStart, UMaterialExpression* InNode, FIntPoint& InOutNodeSize);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Model/DynamicMaterialModelEditorOnlyDataVersion.h` (Private)


#### struct `FDynamicMaterialModelEditorOnlyDataVersion`  
`struct FDynamicMaterialModelEditorOnlyDataVersion`  
_L8-29_
- L11 _private prototype_ `FDynamicMaterialModelEditorOnlyDataVersion() = delete;`
- L28 _public member_ `static const FGuid GUID;`

#### enum `FDynamicMaterialModelEditorOnlyDataVersion::Type`  
`enum Type : uint8`  
_L14-26_
- L16 _public enumerator_ `PreVersioning = 0`
- L19 _public enumerator_ `GlobalValueRename` — When the global variables were added and a couple were renamed.
- L22 _public enumerator_ `FlagsAdded` — When usage and material flags were added.
- L24 _public enumerator_ `VersionPlusOne`
- L25 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Model/DynamicMaterialModelFactory.h` (Private)


#### class `UDynamicMaterialModelFactory`  
`class UDynamicMaterialModelFactory : public UFactory`  
_L10-24_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L15 _public member_ `static const FString BaseDirectory;`
- L16 _public member_ `static const FString BaseName;`
- L18 _public prototype_ `UDynamicMaterialModelFactory();`
- L20 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`
- L22 _public prototype_ `virtual FText GetDisplayName() const override;`
- L23 _public prototype_ `virtual FText GetToolTip() const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/DragDrop/DMLayerEffectsDragDropOperation.h` (Private)


#### class `FDMLayerEffectsDragDropOperation`  
`class FDMLayerEffectsDragDropOperation : public FDragDropOperation`  
_L19-52_
- inherits: `FDragDropOperation`
- L22 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDMLayerEffectsDragDropOperation, FDragDropOperation) FDMLayerEffectsDragDropOperation(const TSharedRef<SDMMaterialSlotLayerEffectItem>& InLayerItemWidget, const bool bInShouldDuplicate);`
- L26 _public function_ `FORCEINLINE bool IsValidDropLocation()`
- L27 _public function_ `FORCEINLINE void SetValidDropLocation(const bool bIsValid)`
- L28 _public function_ `FORCEINLINE void SetToValidDropLocation()`
- L29 _public function_ `FORCEINLINE void SetToInvalidDropLocation()`
- L31 _public function_ `TSharedPtr<SDMMaterialSlotLayerEffectItem> GetLayerItemWidget() const`
- L33 _public prototype_ `UDMMaterialEffect* GetMaterialEffect() const;`
- L36 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L37 _public prototype_ `virtual FCursorReply OnCursorQuery() override;`
- L41 _protected member_ `TWeakPtr<SDMMaterialSlotLayerEffectItem> LayerItemWidgetWeak;`
- L42 _protected member_ `bool bShouldDuplicate;`
- L44 _protected member_ `bool bValidDropLocation = true;`
- L46 _protected member_ `TSharedPtr<FWidgetRenderer> WidgetRenderer;`
- L48 _protected member_ `TStrongObjectPtr<UTextureRenderTarget2D> TextureRenderTarget;`
- L49 _protected member_ `FSlateBrush WidgetTextureBrush;`
- L51 _protected prototype_ `EVisibility GetInvalidDropVisibility() const;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/DragDrop/DMSlotLayerDragDropOperation.h` (Private)


#### class `FDMSlotLayerDragDropOperation`  
`class FDMSlotLayerDragDropOperation : public FDragDropOperation`  
_L20-52_
- inherits: `FDragDropOperation`
- L23 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDMSlotLayerDragDropOperation, FDragDropOperation) FDMSlotLayerDragDropOperation(const TSharedRef<SDMMaterialSlotLayerItem>& InLayerItemWidget, const bool bInShouldDuplicate);`
- L27 _public function_ `FORCEINLINE TSharedPtr<SDMMaterialSlotLayerItem> GetLayerItemWidget() const`
- L28 _public prototype_ `UDMMaterialLayerObject* GetLayer() const;`
- L30 _public function_ `FORCEINLINE bool IsValidDropLocation()`
- L31 _public function_ `FORCEINLINE void SetValidDropLocation(const bool bIsValid)`
- L32 _public function_ `FORCEINLINE void SetToValidDropLocation()`
- L33 _public function_ `FORCEINLINE void SetToInvalidDropLocation()`
- L36 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L37 _public prototype_ `virtual FCursorReply OnCursorQuery() override;`
- L41 _protected member_ `TWeakPtr<SDMMaterialSlotLayerItem> LayerItemWidgetWeak;`
- L42 _protected member_ `bool bShouldDuplicate;`
- L44 _protected member_ `bool bValidDropLocation = true;`
- L46 _protected member_ `TSharedPtr<FWidgetRenderer> WidgetRenderer;`
- L48 _protected member_ `TStrongObjectPtr<UTextureRenderTarget2D> TextureRenderTarget;`
- L49 _protected member_ `FSlateBrush WidgetTextureBrush;`
- L51 _protected prototype_ `EVisibility GetInvalidDropVisibility() const;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/DragDrop/DMStageDragDropOperation.h` (Private)


#### class `FDMStageDragDropOperation`  
`class FDMStageDragDropOperation : public FDragDropOperation`  
_L13-39_
- inherits: `FDragDropOperation`
- L16 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDMStageDragDropOperation, FDragDropOperation) FDMStageDragDropOperation(const TSharedRef<SDMMaterialStage>& InStageWidget);`
- L20 _public function_ `FORCEINLINE TSharedPtr<SDMMaterialStage> GetStageWidget() const`
- L21 _public prototype_ `UDMMaterialStage* GetStage() const;`
- L23 _public function_ `FORCEINLINE bool IsValidDropLocation()`
- L24 _public function_ `FORCEINLINE void SetValidDropLocation(const bool bIsValid)`
- L25 _public function_ `FORCEINLINE void SetToValidDropLocation()`
- L26 _public function_ `FORCEINLINE void SetToInvalidDropLocation()`
- L29 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L30 _public prototype_ `virtual FCursorReply OnCursorQuery() override;`
- L34 _protected member_ `TWeakPtr<SDMMaterialStage> StageWidgetWeak;`
- L36 _protected member_ `bool bValidDropLocation = true;`
- L38 _protected prototype_ `EVisibility GetInvalidDropVisibility() const;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Menus/DMMaterialSlotLayerAddEffectContext.h` (Private)


#### class `UDMMaterialSlotLayerAddEffectContext`  
`class UDMMaterialSlotLayerAddEffectContext : public UObject`  
_L18-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L23 _public function_ `void SetEditorWidget(const TSharedPtr<SDMMaterialEditor>& InEditor)`
- L25 _public function_ `TSharedPtr<SDMMaterialEditor> GetEditorWidget() const`
- L27 _public function_ `void SetLayer(UDMMaterialLayerObject* InLayer)`
- L29 _public function_ `UDMMaterialLayerObject* GetLayer() const`
- L32 _private member_ `TWeakPtr<SDMMaterialEditor> EditorWidgetWeak;`
- L33 _private member_ `TWeakObjectPtr<UDMMaterialLayerObject> LayerWeak;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Menus/DMMaterialSlotLayerAddEffectMenus.h` (Private)


#### class `FDMMaterialSlotLayerAddEffectMenus`  
`class FDMMaterialSlotLayerAddEffectMenus final`  
_L18-47_
- L21 _public prototype_ `static TSharedRef<SWidget> OpenAddEffectMenu(const TSharedPtr<SDMMaterialEditor>& InEditor, UDMMaterialLayerObject* InLayer);`
- L24 _private prototype_ `static void GenerateAddEffectSubMenu(UToolMenu* InMenu, int32 InCategoryIndex);`
- L26 _private prototype_ `static void GenerateAddEffectMenu(UToolMenu* InMenu);`
- L28 _private prototype_ `static void GenerateSaveEffectsMenu(FToolMenuSection& InSection);`
- L30 _private prototype_ `static void GenerateLoadEffectsMenu(UToolMenu* InMenu);`
- L32 _private prototype_ `static void GenerateEffectPresetMenu(UToolMenu* InMenu);`
- L34 _private prototype_ `static void RegisterAddEffectMenu();`
- L36 _private prototype_ `static void AddEffectSubMenu(UToolMenu* InMenu, UDMMaterialLayerObject* InLayer);`
- L38 _private prototype_ `static bool CanAddEffect(const FToolMenuContext& InContext, TSoftObjectPtr<UMaterialFunctionInterface> InMaterialFunctionPtr);`
- L40 _private prototype_ `static void AddEffect(const FToolMenuContext& InContext, TSoftObjectPtr<UMaterialFunctionInterface> InMaterialFunctionPtr);`
- L42 _private prototype_ `static void SavePreset(const FToolMenuContext& InContext, const FString& InPresetName);`
- L44 _private prototype_ `static bool VerifyFileName(const FText& InValue, FText& OutErrorText);`
- L46 _private prototype_ `static void LoadPreset(const FToolMenuContext& InContext, FString InPresetName);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Menus/DMMaterialSlotLayerMenus.h` (Private)


#### class `FDMMaterialSlotLayerMenus`  
`class FDMMaterialSlotLayerMenus final`  
_L16-42_
- L19 _public prototype_ `static TSharedRef<SWidget> GenerateSlotLayerMenu(const TSharedPtr<SDMMaterialSlotEditor>& InSlotWidget, UDMMaterialLayerObject* InLayer);`
- L21 _public prototype_ `static void AddAddLayerSection(FToolMenuSection& InSection);`
- L24 _private prototype_ `static TSharedRef<SWidget> GenerateSlotLayerMenu_AddLayer(const TSharedPtr<SDMMaterialSlotEditor>& InSlotWidget);`
- L26 _private prototype_ `static TSharedRef<SWidget> GenerateSlotLayerMenu_Layer(const TSharedPtr<SDMMaterialSlotEditor>& InSlotWidget, UDMMaterialLayerObject* InLayer);`
- L28 _private prototype_ `static void AddLayerModifySection(FToolMenuSection& InSection);`
- L30 _private prototype_ `static void AddGlobalValueSection(FToolMenuSection& InSection);`
- L32 _private prototype_ `static void AddSlotMenuEntry(const TSharedPtr<SDMMaterialSlotEditor> InSlotWidget, UToolMenu* InMenu, const FText& InName, UDMMaterialSlot* InSourceSlot, EDMMaterialPropertyType InMaterialProperty);`
- L35 _private prototype_ `static void AddLayerInputsMenu_Slot_Properties(UToolMenu* InMenu, UDMMaterialSlot* InSlot);`
- L37 _private prototype_ `static void AddLayerInputsMenu_Slots(UToolMenu* InMenu);`
- L39 _private prototype_ `static void AddLayerMenu_Gradients(UToolMenu* InMenu);`
- L41 _private prototype_ `static void AddLayerMenu_Advanced(UToolMenu* InMenu);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Menus/DMMaterialSlotMenus.h` (Private)


#### class `FDMMaterialSlotMenus`  
`class FDMMaterialSlotMenus final`  
_L11-15_
- L14 _public prototype_ `static TSharedRef<SWidget> MakeAddLayerButtonMenu(const TSharedPtr<SDMMaterialSlotEditor>& InSlotWidget);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Menus/DMMaterialStageMenus.h` (Private)


#### class `FDMMaterialStageMenus`  
`class FDMMaterialStageMenus final`  
_L13-22_
- L16 _public prototype_ `static TSharedRef<SWidget> GenerateStageMenu(const TSharedPtr<SDMMaterialSlotEditor>& InSlotWidget, const TSharedPtr<SDMMaterialStage>& InStageWidget);`
- L19 _private prototype_ `static void AddStageSettingsSection(FToolMenuSection& InSection);`
- L21 _private prototype_ `static void AddStageSourceSection(FToolMenuSection& InSection);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Menus/DMMaterialStageSourceMenus.h` (Private)


#### class `FDMMaterialStageSourceMenus`  
`class FDMMaterialStageSourceMenus final`  
_L20-65_
- L24 _public prototype_ `static TSharedRef<SWidget> MakeChangeSourceMenu(const TSharedPtr<SDMMaterialSlotEditor>& InSlotWidget, const TSharedPtr<SDMMaterialStage>& InStageWidget);` — Generate right click menu for changing sources
- L26 _public prototype_ `static void CreateSourceMenuTree(TFunction<void(EDMExpressionMenu InMenu, TArray<UDMMaterialStageExpression*>& SubmenuExpressionList)> InCallback, const TArray<TStrongObjectPtr<UClass>>& InAllExpressions);`
- L29 _public prototype_ `static void CreateChangeMaterialStageSource(FToolMenuSection& InSection);`
- L32 _private prototype_ `static void GenerateChangeSourceMenu_NewLocalValues(UToolMenu* InMenu);`
- L34 _private prototype_ `static void GenerateChangeSourceMenu_GlobalValues(UToolMenu* InMenu);`
- L36 _private prototype_ `static void GenerateChangeSourceMenu_NewGlobalValues(UToolMenu* InMenu);`
- L38 _private prototype_ `static void GenerateChangeSourceMenu_Slot_Properties(UToolMenu* InMenu, UDMMaterialSlot* InSlot);`
- L40 _private prototype_ `static void GenerateChangeSourceMenu_Slots(UToolMenu* InMenu);`
- L42 _private prototype_ `static void GenerateChangeSourceMenu_Gradients(UToolMenu* const InMenu);`
- L44 _private prototype_ `static void GenerateChangeSourceMenu_Advanced(UToolMenu* const InMenu);`
- L46 _private prototype_ `static void ChangeSourceToTextureSampleFromContext(UDMMenuContext* InMenuContext);`
- L48 _private prototype_ `static void ChangeSourceToNoiseFromContext(UDMMenuContext* InMenuContext);`
- L50 _private prototype_ `static void ChangeSourceToSolidColorRGBFromContext(UDMMenuContext* InMenuContext);`
- L52 _private prototype_ `static void ChangeSourceToColorAtlasFromContext(UDMMenuContext* InMenuContext);`
- L54 _private prototype_ `static void ChangeSourceToTextureSampleEdgeColorFromContext(UDMMenuContext* InMenuContext);`
- L56 _private prototype_ `static void ChangeSourceToSceneTextureFromContext(UDMMenuContext* InMenuContext);`
- L58 _private prototype_ `static bool CanChangeSourceToSceneTextureFromContext(UDMMenuContext* InMenuContext);`
- L60 _private prototype_ `static void ChangeSourceToMaterialFunctionFromContext(UDMMenuContext* InMenuContext);`
- L62 _private prototype_ `static void ChangeSourceToTextFromContext(UDMMenuContext* InMenuContext);`
- L64 _private prototype_ `static void ChangeSourceToWidgetFromContext(UDMMenuContext* InMenuContext);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Menus/DMToolBarMenus.h` (Private)


#### class `FDMToolBarMenus`  
`class FDMToolBarMenus final`  
_L21-52_
- L24 _public prototype_ `static TSharedRef<SWidget> MakeEditorLayoutMenu(const TSharedPtr<SDMMaterialEditor>& InEditorWidget = nullptr);`
- L27 _private prototype_ `static void AddMenu(UToolMenu* InMenu);`
- L29 _private prototype_ `static void AddExportMenu(UToolMenu* InMenu);`
- L31 _private prototype_ `static void AddSettingsMenu(UToolMenu* InMenu);`
- L33 _private prototype_ `static void AddEditorLayoutSection(UToolMenu* InMenu);`
- L35 _private prototype_ `static void AddAdvancedSection(UToolMenu* InMenu);`
- L37 _private prototype_ `static void AddBoolOptionMenuEntry(FToolMenuSection& InSection, const FName& InPropertyName, const FUIAction InAction);`
- L39 _private prototype_ `static void AddIntOptionMenuEntry(FToolMenuSection& InSection, const FName& InPropertyName, TAttribute<bool> InIsEnabledAttribute = TAttribute<bool>(), TAttribute<EVisibility> InVisibilityAttribute = TAttribute<EVisibility>());`
- L43 _private prototype_ `static void OpenMaterialEditorFromContext(UDMMenuContext* InMenuContext);`
- L45 _private prototype_ `static void ExportMaterial(TWeakObjectPtr<UDynamicMaterialInstance> InMaterialInstanceWeak);`
- L47 _private prototype_ `static void ExportMaterialModel(TWeakObjectPtr<UDynamicMaterialModelBase> InMaterialModelBaseWeak);`
- L49 _private prototype_ `static void SnapshotMaterial(TWeakObjectPtr<UDynamicMaterialModelBase> InMaterialModelBaseWeak, FIntPoint InTextureSize);`
- L51 _private prototype_ `static void CreateSnapshotMaterialMenu(UToolMenu* InMenu);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/PropertyGenerators/DMInputThroughputPropertyRowGenerator.h` (Private)


#### class `FDMInputThroughputPropertyRowGenerator`  
`class FDMInputThroughputPropertyRowGenerator : public FDMThroughputPropertyRowGenerator`  
_L7-17_
- inherits: `FDMThroughputPropertyRowGenerator`
- L10 _public prototype_ `static const TSharedRef<FDMInputThroughputPropertyRowGenerator>& Get();`
- L12 _public prototype_ `virtual ~FDMInputThroughputPropertyRowGenerator() override = default;`
- L15 _public prototype_ `virtual void AddComponentProperties(FDMComponentPropertyRowGeneratorParams& InParams) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/PropertyGenerators/DMMaterialEffectFunctionPropertyRowGenerator.h` (Private)


#### class `FDMMaterialEffectFunctionPropertyRowGenerator`  
`class FDMMaterialEffectFunctionPropertyRowGenerator : public FDMComponentPropertyRowGenerator`  
_L7-17_
- inherits: `FDMComponentPropertyRowGenerator`
- L10 _public prototype_ `static const TSharedRef<FDMMaterialEffectFunctionPropertyRowGenerator>& Get();`
- L12 _public prototype_ `virtual ~FDMMaterialEffectFunctionPropertyRowGenerator() override = default;`
- L15 _public prototype_ `virtual void AddComponentProperties(FDMComponentPropertyRowGeneratorParams& InParams) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/PropertyGenerators/DMMaterialModelPropertyRowGenerator.h` (Private)


#### class `FDMMaterialModelPropertyRowGenerator`  
`class FDMMaterialModelPropertyRowGenerator`  
_L19-38_
- desc: Used to generate editable properties for material models.
- L28 _public prototype_ `static void AddMaterialModelProperties(FDMComponentPropertyRowGeneratorParams& InParams);` — Generate properties for the given component. @param InGlobalSettingEditorWidget The edit widget generating the properties. @param InMaterialModelBase The model being edited. @param InOutPropertyRows The generated rows.
- L30 _public prototype_ `static void AddGlobalValue(FDMComponentPropertyRowGeneratorParams& InParams, UDMMaterialComponent* InComponent, const FText& InNameOverride);`
- L33 _public prototype_ `static void AddVariable(FDMComponentPropertyRowGeneratorParams& InParams, UObject* InObject, FName InPropertyName);`
- L37 _protected prototype_ `static bool IsDynamic(UDynamicMaterialModelBase* InMaterialModelBase);` — Returns true if the component edit widget is editing a Material Designer Dynamic.

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/PropertyGenerators/DMMaterialStageFunctionPropertyRowGenerator.h` (Private)


#### class `FDMMaterialStageFunctionPropertyRowGenerator`  
`class FDMMaterialStageFunctionPropertyRowGenerator : public FDMComponentPropertyRowGenerator`  
_L7-17_
- inherits: `FDMComponentPropertyRowGenerator`
- L10 _public prototype_ `static const TSharedRef<FDMMaterialStageFunctionPropertyRowGenerator>& Get();`
- L12 _public prototype_ `virtual ~FDMMaterialStageFunctionPropertyRowGenerator() override = default;`
- L15 _public prototype_ `virtual void AddComponentProperties(FDMComponentPropertyRowGeneratorParams& InParams) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/PropertyGenerators/DMMaterialValueDynamicPropertyRowGenerator.h` (Private)


#### class `FDMMaterialValueDynamicPropertyRowGenerator`  
`class FDMMaterialValueDynamicPropertyRowGenerator : public FDMComponentPropertyRowGenerator`  
_L7-17_
- inherits: `FDMComponentPropertyRowGenerator`
- L10 _public prototype_ `static const TSharedRef<FDMMaterialValueDynamicPropertyRowGenerator>& Get();`
- L12 _public prototype_ `virtual ~FDMMaterialValueDynamicPropertyRowGenerator() override = default;`
- L15 _public prototype_ `virtual void AddComponentProperties(FDMComponentPropertyRowGeneratorParams& InParams) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/PropertyGenerators/DMMaterialValuePropertyRowGenerator.h` (Private)


#### class `FDMMaterialValuePropertyRowGenerator`  
`class FDMMaterialValuePropertyRowGenerator : public FDMComponentPropertyRowGenerator`  
_L7-17_
- inherits: `FDMComponentPropertyRowGenerator`
- L10 _public prototype_ `static const TSharedRef<FDMMaterialValuePropertyRowGenerator>& Get();`
- L12 _public prototype_ `virtual ~FDMMaterialValuePropertyRowGenerator() override = default;`
- L15 _public prototype_ `virtual void AddComponentProperties(FDMComponentPropertyRowGeneratorParams& InParams) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/PropertyGenerators/DMStagePropertyRowGenerator.h` (Private)


#### class `FDMStagePropertyRowGenerator`  
`class FDMStagePropertyRowGenerator : public FDMComponentPropertyRowGenerator`  
_L11-21_
- inherits: `FDMComponentPropertyRowGenerator`
- L14 _public prototype_ `static const TSharedRef<FDMStagePropertyRowGenerator>& Get();`
- L16 _public prototype_ `virtual ~FDMStagePropertyRowGenerator() override = default;`
- L19 _public prototype_ `virtual void AddComponentProperties(FDMComponentPropertyRowGeneratorParams& InParams) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/PropertyGenerators/DMTextureUVDynamicPropertyRowGenerator.h` (Private)


#### class `FDMTextureUVDynamicPropertyRowGenerator`  
`class FDMTextureUVDynamicPropertyRowGenerator : public FDMComponentPropertyRowGenerator`  
_L7-21_
- inherits: `FDMComponentPropertyRowGenerator`
- L10 _public prototype_ `static const TSharedRef<FDMTextureUVDynamicPropertyRowGenerator>& Get();`
- L12 _public prototype_ `virtual ~FDMTextureUVDynamicPropertyRowGenerator() override = default;`
- L14 _public prototype_ `static void AddPopoutComponentProperties(FDMComponentPropertyRowGeneratorParams& InParams);`
- L17 _public prototype_ `virtual void AddComponentProperties(FDMComponentPropertyRowGeneratorParams& InParams) override;`
- L19 _public prototype_ `virtual bool AllowKeyframeButton(UDMMaterialComponent* InComponent, FProperty* InProperty) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/PropertyGenerators/DMTextureUVPropertyRowGenerator.h` (Private)


#### class `FDMTextureUVPropertyRowGenerator`  
`class FDMTextureUVPropertyRowGenerator : public FDMComponentPropertyRowGenerator`  
_L9-23_
- inherits: `FDMComponentPropertyRowGenerator`
- L12 _public prototype_ `static const TSharedRef<FDMTextureUVPropertyRowGenerator>& Get();`
- L14 _public prototype_ `virtual ~FDMTextureUVPropertyRowGenerator() override = default;`
- L16 _public prototype_ `static void AddPopoutComponentProperties(FDMComponentPropertyRowGeneratorParams& InParams);`
- L19 _public prototype_ `virtual void AddComponentProperties(FDMComponentPropertyRowGeneratorParams& InParams) override;`
- L21 _public prototype_ `virtual bool AllowKeyframeButton(UDMMaterialComponent* InComponent, FProperty* InProperty) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/PropertyGenerators/DMThroughputPropertyRowGenerator.h` (Private)


#### class `FDMThroughputPropertyRowGenerator`  
`class FDMThroughputPropertyRowGenerator : public FDMComponentPropertyRowGenerator`  
_L7-17_
- inherits: `FDMComponentPropertyRowGenerator`
- L10 _public prototype_ `static const TSharedRef<FDMThroughputPropertyRowGenerator>& Get();`
- L12 _public prototype_ `virtual ~FDMThroughputPropertyRowGenerator() override = default;`
- L15 _public prototype_ `virtual void AddComponentProperties(FDMComponentPropertyRowGeneratorParams& InParams) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Utils/DMDropTargetPrivateSetter.h` (Private)


#### struct `UE::DynamicMaterialEditor::Private::DropTarget::FDropTargetSetter`  
`template <auto SDropTarget::* Member> struct FDropTargetSetter`  
_L14-20_

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DynamicMaterialEditor` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::DynamicMaterialEditor`)
- L11 _namespace_ `namespace DropTarget` (scope `UE::DynamicMaterialEditor::Private`)
- L16 _function_ `friend void SetInvalidColor(SDropTarget* InDropTarget, const FSlateColor& InNewColor)` (scope `UE::DynamicMaterialEditor::Private::DropTarget`)
- L22 _variable_ `template struct FDropTargetSetter<&SDropTarget::InvalidColor>;` (scope `UE::DynamicMaterialEditor::Private::DropTarget`)
- L23 _prototype_ `template struct FDropTargetSetter<&SDropTarget::InvalidColor>;` (scope `UE::DynamicMaterialEditor::Private::DropTarget`)

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Utils/DMEditorSelectionContext.h` (Private)


#### enum `EDMMaterialEditorMode`  
`enum class EDMMaterialEditorMode : uint8`  
_L15-21_
- L17 _public enumerator_ `GlobalSettings`
- L18 _public enumerator_ `Properties`
- L19 _public enumerator_ `EditSlot`
- L20 _public enumerator_ `MaterialPreview`

#### struct `FDMMaterialEditorPage`  
`struct FDMMaterialEditorPage`  
_L23-33_
- L25 _public member_ `static FDMMaterialEditorPage Preview;`
- L26 _public member_ `static FDMMaterialEditorPage GlobalSettings;`
- L27 _public member_ `static FDMMaterialEditorPage Properties;`
- L29 _public member_ `EDMMaterialEditorMode EditorMode;`
- L30 _public member_ `EDMMaterialPropertyType MaterialProperty;`
- L32 _public prototype_ `bool operator==(const FDMMaterialEditorPage& InOther) const;`

#### struct `FDMEditorSelectionContext`  
`struct FDMEditorSelectionContext`  
_L35-54_
- L37 _public member_ `EDMMaterialEditorMode EditorMode = EDMMaterialEditorMode::GlobalSettings;`
- L39 _public member_ `bool bModeChanged = false;`
- L41 _public member_ `EDMMaterialPropertyType Property;`
- L43 _public member_ `TWeakObjectPtr<UDMMaterialSlot> Slot = nullptr;`
- L45 _public member_ `TWeakObjectPtr<UDMMaterialLayerObject> Layer = nullptr;`
- L47 _public member_ `TWeakObjectPtr<UDMMaterialComponent> Component = nullptr;`
- L49 _public member_ `TArray<FDMMaterialEditorPage> PageHistory;`
- L51 _public member_ `int32 PageHistoryActive = 0;`
- L53 _public member_ `int32 PageHistoryCount = 0;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Utils/DMPreviewMaterialManager.h` (Private)


#### class `FDMPreviewMaterialManager`  
`class FDMPreviewMaterialManager`  
_L13-27_
- L16 _public prototype_ `UMaterial* CreatePreviewMaterial(UObject* InPreviewing);`
- L18 _public prototype_ `void FreePreviewMaterial(UObject* InPreviewing);`
- L20 _public prototype_ `UMaterialInstanceDynamic* CreatePreviewMaterialDynamic(UMaterial* InMaterialBase);`
- L22 _public prototype_ `void FreePreviewMaterialDynamic(UMaterial* InMaterialBase);`
- L25 _private member_ `TMap<FObjectKey, TStrongObjectPtr<UMaterial>> PreviewMaterials;`
- L26 _private member_ `TMap<FObjectKey, TStrongObjectPtr<UMaterialInstanceDynamic>> PreviewMaterialDynamics;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Utils/DMWidgetLibrary.h` (Private)


#### class `FDMWidgetLibrary`  
`class FDMWidgetLibrary : public IDMWidgetLibrary`  
_L16-81_
- inherits: `IDMWidgetLibrary`
- L19 _public member_ `static const FLazyName PropertyValueWidget;`
- L21 _public prototype_ `static FDMWidgetLibrary& Get();`
- L23 _public prototype_ `virtual ~FDMWidgetLibrary() = default;`
- L25 _public prototype_ `bool GetExpansionState(UObject* InOwner, FName InName, bool& bOutExpanded);`
- L27 _public prototype_ `void SetExpansionState(UObject* InOwner, FName InName, bool bInIsExpanded);`
- L29 _public prototype_ `void ClearPropertyHandles(const SWidget* InOwningWidget);`
- L31 _public prototype_ `TSharedPtr<SWidget> FindWidgetInHierarchy(const TSharedRef<SWidget>& InParent, const FName& InName);`
- L33 _public prototype_ `TSharedPtr<SWidget> GetInnerPropertyValueWidget(const TSharedRef<SWidget>& InWidget);`
- L35 _public prototype_ `void ClearData();`
- L38 _public prototype_ `virtual FDMPropertyHandle GetPropertyHandle(const FDMPropertyHandleGenerateParams& InParams) override;`
- L53 _private function_ `friend uint32 GetTypeHash(const FExpansionItem& InItem)`
- L62 _private member_ `TMap<FExpansionItem, bool> ExpansionStates;`
- L64 _private member_ `TMap<const SWidget*, TArray<FDMPropertyHandle>> PropertyHandleMap;`
- L66 _private prototype_ `FDMPropertyHandle CreatePropertyHandle(const FDMPropertyHandleGenerateParams& InParams);`
- L68 _private prototype_ `static TSharedPtr<IDetailTreeNode> SearchNodesForProperty(const TArray<TSharedRef<IDetailTreeNode>>& InNodes, FName InPropertyName);`
- L70 _private prototype_ `static TSharedPtr<IDetailTreeNode> SearchGeneratorForNode(const TSharedRef<IPropertyRowGenerator>& InGenerator, FName InPropertyName);`
- L72 _private prototype_ `static const FDMPropertyHandle* SearchForHandle(const TArray<FDMPropertyHandle>& InPropertyHandles, UObject* InObject);`
- L74 _private prototype_ `static void AddPropertyMetaData(UObject* InObject, FName InPropertyName, FDMPropertyHandle& InPropertyHandle);`
- L77 _private prototype_ `static EDMPropertyHandlePriority GetPriority(const TSharedRef<IPropertyHandle>& InPropertyHandle);` — Checks the meta data of a property meta data to check for high and low priority specifiers.
- L80 _private prototype_ `static bool IsKeyframeable(const TSharedRef<IPropertyHandle>& InPropertyHandle);` — Checks for the NotKeyframeable meta data.

#### struct `FDMWidgetLibrary::FExpansionItem`  
`struct FExpansionItem`  
_L42-60_
- L44 _public member_ `TObjectKey<UObject> Owner;`
- L45 _public member_ `FName Name;`
- L47 _public function_ `bool operator==(const FExpansionItem& InOther) const`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Utils/DMWidgetSlot.h` (Private)


#### struct `FDMWidgetSlot`  
`struct FDMWidgetSlot`  
_L14-46_
- desc: Handles storing a widget, the slot it's in and its invalidation state. Provides methods and operator overrides to simplify replacing widgets.
- L16 _public prototype_ `FSlotBase* GetSlot() const;`
- L18 _public prototype_ `void SetSlot(FSlotBase* InSlot);`
- L21 _public prototype_ `bool IsValid() const;` — Returns true if the widget is valid and hasn't been invalidated.
- L23 _public prototype_ `bool HasBeenInvalidated() const;`
- L25 _public prototype_ `void Invalidate();`
- L28 _public prototype_ `bool HasWidget() const;` — Will return true even if the widget is invalidated.
- L30 _public prototype_ `void ClearWidget();`
- L32 _public prototype_ `bool operator==(const TSharedRef<SWidget>& InWidget) const;`
- L35 _protected member_ `TWeakPtr<SWidget> Owner;`
- L36 _protected member_ `FSlotBase* Slot = nullptr;`
- L37 _protected member_ `TSharedPtr<SWidget> Widget;`
- L38 _protected member_ `bool bInvalidated = true;`
- L40 _protected prototype_ `FDMWidgetSlot() = default;`
- L41 _protected prototype_ `FDMWidgetSlot(FSlotBase* InSlot, const TSharedRef<SWidget>& InWidget);`
- L43 _protected prototype_ `FSlotBase* FindSlot(const TSharedRef<SWidget>& InParentWidget, int32 InChildSlot) const;`
- L45 _protected prototype_ `void AssignWidget(const TSharedRef<SWidget>& InWidget);`

#### struct `TDMWidgetSlot`  
`template<typename InWidgetType> struct TDMWidgetSlot : public FDMWidgetSlot`  
_L49-84_
- inherits: `FDMWidgetSlot`
- L51 _public typedef_ `using FWidgetType = InWidgetType;`
- L53 _public prototype_ `TDMWidgetSlot() = default;`
- L55 _public function_ `TDMWidgetSlot(FSlotBase* InSlot, const TSharedRef<FWidgetType>& InWidget) : FDMWidgetSlot(InSlot, InWidget)`
- L60 _public function_ `TDMWidgetSlot(const TSharedRef<SWidget>& InParentWidget, int32 InChildSlot, const TSharedRef<FWidgetType>& InWidget) : FDMWidgetSlot(FindSlot(InParentWidget, InChildSlot), InWidget)`
- L65 _public function_ `void operator<<(const TSharedRef<FWidgetType>& InWidget)`
- L70 _public function_ `TSharedPtr<FWidgetType> operator&() const`
- L75 _public function_ `TSharedRef<FWidgetType> operator*() const`
- L80 _public function_ `FWidgetType* operator->() const`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Utils/DynamicMaterialInstanceThumbnailRenderer.h` (Private)


#### class `UDynamicMaterialInstanceThumbnailRenderer`  
`class UDynamicMaterialInstanceThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L17-33_
- reflection: `UCLASS(config = Editor)`
- inherits: `UDefaultSizedThumbnailRenderer`
- desc: This thumbnail renderer displays a given Material Designer Material.
- L22 _private prototype_ `virtual void Draw(UObject* InObject, int32 InX, int32 InY, uint32 InWidth, uint32 InHeight, FRenderTarget* InRenderTarget, FCanvas* InCanvas, bool bInAdditionalViewFamily) override;`
- L24 _private prototype_ `virtual bool CanVisualizeAsset(UObject* InObject) override;`
- L28 _private prototype_ `virtual void BeginDestroy() override;`
- L32 _private member_ `FDynamicMaterialInstanceThumbnailScene* ThumbnailScene;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Utils/DynamicMaterialInstanceThumbnailScene.h` (Private)


#### class `FDynamicMaterialInstanceThumbnailScene`  
`class FDynamicMaterialInstanceThumbnailScene : public FThumbnailPreviewScene`  
_L12-32_
- inherits: `FThumbnailPreviewScene`
- L15 _public prototype_ `FDynamicMaterialInstanceThumbnailScene();`
- L18 _public prototype_ `void SetStaticMesh(UStaticMesh* InStaticMesh);` — Sets the static mesh to render with.
- L21 _public prototype_ `void SetDynamicMaterialInstance(UDynamicMaterialInstance* InMaterialInstance);` — Sets the Material Instance used on the mesh.
- L25 _protected prototype_ `virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;`
- L30 _private member_ `AStaticMeshActor* PreviewActor;`
- L31 _private member_ `UDynamicMaterialInstance* MaterialInstance;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/DMMaterialPreviewViewportClient.h` (Private)


#### class `FDMMaterialPreviewViewportClient`  
`class FDMMaterialPreviewViewportClient : public FEditorViewportClient`  
_L14-40_
- inherits: `FEditorViewportClient`
- desc: Based on FMaterialEditorViewportClient (private)
- L17 _public prototype_ `FDMMaterialPreviewViewportClient(const TSharedRef<SDMMaterialPreview>& InPreviewWidget, FAdvancedPreviewScene& InPreviewScene, TSharedRef<FEditorModeTools> InPreviewModeTools);`
- L26 _public prototype_ `void FocusViewportOnBounds(const FBoxSphereBounds& InBounds, bool bInInstant = false);` — Focuses the viewport to the center of the bounding box/sphere ensuring that the entire bounds are in view @param InBounds   The bounds to focus @param bInInstant Whether or not to focus the viewport instantly or over time
- L29 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& InEventArgs) override;`
- L30 _public prototype_ `virtual bool InputAxis(const FInputKeyEventArgs& InEventArgs) override;`
- L31 _public prototype_ `virtual FLinearColor GetBackgroundColor() const override;`
- L32 _public prototype_ `virtual void Tick(float InDeltaSeconds) override;`
- L33 _public prototype_ `virtual bool ShouldOrbitCamera() const override;`
- L37 _private member_ `TWeakPtr<SDMMaterialPreview> PreviewWidget;`
- L38 _private member_ `FAdvancedPreviewScene* AdvancedPreviewScene;`
- L39 _private member_ `TSharedPtr<FEditorModeTools> PreviewModeTools;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/EditorLayouts/SDMMaterialEditor_Left.h` (Private)


#### class `SDMMaterialEditor_Left`  
`class SDMMaterialEditor_Left : public SDMMaterialEditor_LeftBase`  
_L7-32_
- inherits: `SDMMaterialEditor_LeftBase`
- L9 _private function_ `SLATE_BEGIN_ARGS(SDMMaterialEditor_Left) : _MaterialModelBase(nullptr) , _MaterialProperty(TOptional<FDMObjectMaterialProperty>()) , _PreviewMaterialModelBase(nullptr)`
- L20 _public prototype_ `virtual ~SDMMaterialEditor_Left() override = default;`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialDesigner>& InDesignerWidget);`
- L26 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_Left() override;`
- L30 _protected prototype_ `virtual TSharedRef<SDMMaterialPropertySelector> CreateSlot_PropertySelector_Impl() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/EditorLayouts/SDMMaterialEditor_LeftBase.h` (Private)


#### class `SDMMaterialEditor_LeftBase`  
`class SDMMaterialEditor_LeftBase : public SDMMaterialEditor`  
_L7-47_
- inherits: `SDMMaterialEditor`
- L9 _private function_ `SLATE_BEGIN_ARGS(SDMMaterialEditor_LeftBase) : _MaterialModelBase(nullptr) , _MaterialProperty(TOptional<FDMObjectMaterialProperty>()) , _PreviewMaterialModelBase(nullptr)`
- L20 _public prototype_ `virtual ~SDMMaterialEditor_LeftBase() override = default;`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialDesigner>& InDesignerWidget);`
- L25 _protected member_ `TDMWidgetSlot<SWidget> LeftSlot;`
- L26 _protected member_ `TDMWidgetSlot<SWidget> RightSlot;`
- L28 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_Left() = 0;`
- L30 _protected prototype_ `TSharedRef<SWidget> CreateSlot_Right();`
- L32 _protected prototype_ `TSharedRef<SWidget> CreateSlot_Right_GlobalSettings();`
- L34 _protected prototype_ `TSharedRef<SWidget> CreateSlot_Right_PropertyPreviews();`
- L36 _protected prototype_ `TSharedRef<SWidget> CreateSlot_Right_EditSlot();`
- L39 _protected prototype_ `virtual void ValidateSlots_Main() override;`
- L40 _protected prototype_ `virtual void ClearSlots_Main() override;`
- L41 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_Main() override;`
- L42 _protected prototype_ `virtual void EditSlot_Impl(UDMMaterialSlot* InSlot) override;`
- L43 _protected prototype_ `virtual void EditComponent_Impl(UDMMaterialComponent* InComponent) override;`
- L44 _protected prototype_ `virtual void EditGlobalSettings_Impl() override;`
- L45 _protected prototype_ `virtual void EditProperties_Impl() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/EditorLayouts/SDMMaterialEditor_LeftSlim.h` (Private)


#### class `SDMMaterialEditor_LeftSlim`  
`class SDMMaterialEditor_LeftSlim : public SDMMaterialEditor_LeftBase`  
_L7-32_
- inherits: `SDMMaterialEditor_LeftBase`
- L9 _private function_ `SLATE_BEGIN_ARGS(SDMMaterialEditor_LeftSlim) : _MaterialModelBase(nullptr) , _MaterialProperty(TOptional<FDMObjectMaterialProperty>()) , _PreviewMaterialModelBase(nullptr)`
- L20 _public prototype_ `virtual ~SDMMaterialEditor_LeftSlim() override = default;`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialDesigner>& InDesignerWidget);`
- L26 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_Left() override;`
- L30 _protected prototype_ `virtual TSharedRef<SDMMaterialPropertySelector> CreateSlot_PropertySelector_Impl() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/EditorLayouts/SDMMaterialEditor_TopBase.h` (Private)


#### class `SDMMaterialEditor_TopBase`  
`class SDMMaterialEditor_TopBase : public SDMMaterialEditor`  
_L7-47_
- inherits: `SDMMaterialEditor`
- L9 _private function_ `SLATE_BEGIN_ARGS(SDMMaterialEditor_TopBase) : _MaterialModelBase(nullptr) , _MaterialProperty(TOptional<FDMObjectMaterialProperty>()) , _PreviewMaterialModelBase(nullptr)`
- L20 _public prototype_ `virtual ~SDMMaterialEditor_TopBase() override = default;`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialDesigner>& InDesignerWidget);`
- L25 _protected member_ `TDMWidgetSlot<SWidget> TopSlot;`
- L26 _protected member_ `TDMWidgetSlot<SWidget> BottomSlot;`
- L28 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_Top() = 0;`
- L30 _protected prototype_ `TSharedRef<SWidget> CreateSlot_Bottom();`
- L32 _protected prototype_ `TSharedRef<SWidget> CreateSlot_Bottom_GlobalSettings();`
- L34 _protected prototype_ `TSharedRef<SWidget> CreateSlot_Bottom_PropertyPreviews();`
- L36 _protected prototype_ `TSharedRef<SWidget> CreateSlot_Bottom_EditSlot();`
- L39 _protected prototype_ `virtual void ValidateSlots_Main() override;`
- L40 _protected prototype_ `virtual void ClearSlots_Main() override;`
- L41 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_Main() override;`
- L42 _protected prototype_ `virtual void EditSlot_Impl(UDMMaterialSlot* InSlot) override;`
- L43 _protected prototype_ `virtual void EditComponent_Impl(UDMMaterialComponent* InComponent) override;`
- L44 _protected prototype_ `virtual void EditGlobalSettings_Impl() override;`
- L45 _protected prototype_ `virtual void EditProperties_Impl() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/EditorLayouts/SDMMaterialEditor_TopHorizontal.h` (Private)


#### class `SDMMaterialEditor_TopHorizontal`  
`class SDMMaterialEditor_TopHorizontal : public SDMMaterialEditor_TopBase`  
_L7-32_
- inherits: `SDMMaterialEditor_TopBase`
- L9 _private function_ `SLATE_BEGIN_ARGS(SDMMaterialEditor_TopHorizontal) : _MaterialModelBase(nullptr) , _MaterialProperty(TOptional<FDMObjectMaterialProperty>()) , _PreviewMaterialModelBase(nullptr)`
- L20 _public prototype_ `virtual ~SDMMaterialEditor_TopHorizontal() override = default;`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialDesigner>& InDesignerWidget);`
- L26 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_Top() override;`
- L30 _protected prototype_ `virtual TSharedRef<SDMMaterialPropertySelector> CreateSlot_PropertySelector_Impl() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/EditorLayouts/SDMMaterialEditor_TopSlim.h` (Private)


#### class `SDMMaterialEditor_TopSlim`  
`class SDMMaterialEditor_TopSlim : public SDMMaterialEditor_TopBase`  
_L7-32_
- inherits: `SDMMaterialEditor_TopBase`
- L9 _private function_ `SLATE_BEGIN_ARGS(SDMMaterialEditor_TopSlim) : _MaterialModelBase(nullptr) , _MaterialProperty(TOptional<FDMObjectMaterialProperty>()) , _PreviewMaterialModelBase(nullptr)`
- L20 _public prototype_ `virtual ~SDMMaterialEditor_TopSlim() override = default;`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialDesigner>& InDesignerWidget);`
- L26 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_Top() override;`
- L30 _protected prototype_ `virtual TSharedRef<SDMMaterialPropertySelector> CreateSlot_PropertySelector_Impl() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/EditorLayouts/SDMMaterialEditor_TopVertical.h` (Private)


#### class `SDMMaterialEditor_TopVertical`  
`class SDMMaterialEditor_TopVertical : public SDMMaterialEditor_TopBase`  
_L7-39_
- inherits: `SDMMaterialEditor_TopBase`
- L9 _private function_ `SLATE_BEGIN_ARGS(SDMMaterialEditor_TopVertical) : _MaterialModelBase(nullptr) , _MaterialProperty(TOptional<FDMObjectMaterialProperty>()) , _PreviewMaterialModelBase(nullptr)`
- L20 _public prototype_ `SDMMaterialEditor_TopVertical();`
- L22 _public prototype_ `virtual ~SDMMaterialEditor_TopVertical() override = default;`
- L24 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialDesigner>& InDesignerWidget);`
- L27 _protected member_ `FSlotBase* SplitterSlot_Top;`
- L29 _protected prototype_ `void OnTopSplitterResized();`
- L32 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_Top() override;`
- L36 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_Main() override;`
- L37 _protected prototype_ `virtual TSharedRef<SDMMaterialPropertySelector> CreateSlot_PropertySelector_Impl() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/PropertySelectorLayouts/SDMMaterialPropertySelector_Vertical.h` (Private)


#### class `SDMMaterialPropertySelector_Vertical`  
`class SDMMaterialPropertySelector_Vertical : public SDMMaterialPropertySelector_VerticalBase`  
_L9-23_
- inherits: `SDMMaterialPropertySelector_VerticalBase`
- L11 _private function_ `SLATE_BEGIN_ARGS(SDMMaterialPropertySelector_Vertical)`
- L15 _public prototype_ `virtual ~SDMMaterialPropertySelector_Vertical() override = default;`
- L17 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor> InEditorWidget);`
- L21 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_SelectButton(const FDMMaterialEditorPage& InPage) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/PropertySelectorLayouts/SDMMaterialPropertySelector_VerticalBase.h` (Private)


#### class `SDMMaterialPropertySelector_VerticalBase`  
`class SDMMaterialPropertySelector_VerticalBase : public SDMMaterialPropertySelector`  
_L7-21_
- inherits: `SDMMaterialPropertySelector`
- L9 _private function_ `SLATE_BEGIN_ARGS(SDMMaterialPropertySelector_VerticalBase)`
- L13 _public prototype_ `virtual ~SDMMaterialPropertySelector_VerticalBase() override = default;`
- L15 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor> InEditorWidget);`
- L19 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_PropertyList() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/PropertySelectorLayouts/SDMMaterialPropertySelector_VerticalSlim.h` (Private)


#### class `SDMMaterialPropertySelector_VerticalSlim`  
`class SDMMaterialPropertySelector_VerticalSlim : public SDMMaterialPropertySelector_VerticalBase`  
_L9-24_
- inherits: `SDMMaterialPropertySelector_VerticalBase`
- L11 _private function_ `SLATE_BEGIN_ARGS(SDMMaterialPropertySelector_VerticalSlim)`
- L15 _public prototype_ `virtual ~SDMMaterialPropertySelector_VerticalSlim() override = default;`
- L17 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor> InEditorWidget);`
- L21 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_PropertyList() override;`
- L22 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_SelectButton(const FDMMaterialEditorPage& InPage) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/PropertySelectorLayouts/SDMMaterialPropertySelector_Wrap.h` (Private)


#### class `SDMMaterialPropertySelector_Wrap`  
`class SDMMaterialPropertySelector_Wrap : public SDMMaterialPropertySelector_WrapBase`  
_L7-16_
- inherits: `SDMMaterialPropertySelector_WrapBase`
- L9 _private function_ `SLATE_BEGIN_ARGS(SDMMaterialPropertySelector_Wrap)`
- L13 _public prototype_ `virtual ~SDMMaterialPropertySelector_Wrap() override = default;`
- L15 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor> InEditorWidget);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/PropertySelectorLayouts/SDMMaterialPropertySelector_WrapBase.h` (Private)


#### class `SDMMaterialPropertySelector_WrapBase`  
`class SDMMaterialPropertySelector_WrapBase : public SDMMaterialPropertySelector`  
_L9-24_
- inherits: `SDMMaterialPropertySelector`
- L11 _private function_ `SLATE_BEGIN_ARGS(SDMMaterialPropertySelector_WrapBase)`
- L15 _public prototype_ `virtual ~SDMMaterialPropertySelector_WrapBase() override = default;`
- L17 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor> InEditorWidget);`
- L21 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_PropertyList() override;`
- L22 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_SelectButton(const FDMMaterialEditorPage& InPage) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/PropertySelectorLayouts/SDMMaterialPropertySelector_WrapSlim.h` (Private)


#### class `SDMMaterialPropertySelector_WrapSlim`  
`class SDMMaterialPropertySelector_WrapSlim : public SDMMaterialPropertySelector_WrapBase`  
_L7-22_
- inherits: `SDMMaterialPropertySelector_WrapBase`
- L9 _private function_ `SLATE_BEGIN_ARGS(SDMMaterialPropertySelector_WrapSlim)`
- L13 _public prototype_ `virtual ~SDMMaterialPropertySelector_WrapSlim() override = default;`
- L15 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor> InEditorWidget);`
- L19 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_PropertyList() override;`
- L20 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_SelectButton(const FDMMaterialEditorPage& InPage) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/SDMMaterialComponentEditor.h` (Private)


#### class `SDMMaterialComponentEditor`  
`class SDMMaterialComponentEditor : public SDMObjectEditorWidgetBase`  
_L12-45_
- inherits: `SDMObjectEditorWidgetBase`
- desc: Extends the object editor to provide component-specific events and properties.
- L14 _private function_ `SLATE_DECLARE_WIDGET(SDMMaterialComponentEditor, SCompoundWidget) SLATE_BEGIN_ARGS(SDMMaterialComponentEditor)`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor>& InEditorWidget, UDMMaterialComponent* InMaterialComponent);`
- L24 _public prototype_ `UDMMaterialComponent* GetComponent() const;`
- L27 _public prototype_ `virtual void NotifyPreChange(FProperty* InPropertyAboutToChange) override;`
- L28 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L32 _protected prototype_ `void OnComponentUpdated(UDMMaterialComponent* InComponent, UDMMaterialComponent* InSource, EDMUpdateType InUpdateType);`
- L34 _protected prototype_ `UDMMaterialComponent* GetOriginalComponent(UDMMaterialComponent* InPreviewComponent) const;`
- L36 _protected prototype_ `void BindPropertyRowUpdateDelegates(TConstArrayView<FDMPropertyHandle> InPropertyRows);`
- L39 _protected prototype_ `virtual TSharedRef<ICustomDetailsViewItem> GetDefaultCategory(const TSharedRef<ICustomDetailsView>& InDetailsView, const FCustomDetailsViewItemId& InRootId) override;`
- L41 _protected prototype_ `virtual TArray<FDMPropertyHandle> GetPropertyRows() override;`
- L42 _protected prototype_ `virtual void AddDetailTreeRowExtensionWidgets(const TSharedRef<ICustomDetailsView>& InDetailsView, const FDMPropertyHandle& InPropertyRow, const TSharedRef<ICustomDetailsViewItem>& InItem, const TSharedRef<IPropertyHandle>& InPropertyHandle) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/SDMMaterialGlobalSettingsEditor.h` (Private)


#### class `SDMMaterialGlobalSettingsEditor`  
`class SDMMaterialGlobalSettingsEditor : public SDMObjectEditorWidgetBase`  
_L11-43_
- inherits: `SDMObjectEditorWidgetBase`
- L13 _private function_ `SLATE_DECLARE_WIDGET(SDMMaterialGlobalSettingsEditor, SCompoundWidget) SLATE_BEGIN_ARGS(SDMMaterialGlobalSettingsEditor)`
- L19 _public prototype_ `virtual ~SDMMaterialGlobalSettingsEditor() override = default;`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor>& InEditorWidget, UDynamicMaterialModelBase* InMaterialModelBase);`
- L24 _public prototype_ `UDynamicMaterialModelBase* GetMaterialModelBase() const;`
- L26 _public prototype_ `UDynamicMaterialModelBase* GetOriginalMaterialModelBase() const;`
- L29 _public prototype_ `virtual void NotifyPreChange(FProperty* InPropertyAboutToChange) override;`
- L30 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L34 _protected prototype_ `UDMMaterialComponent* GetOriginalComponent(UDMMaterialComponent* InPreviewComponent) const;`
- L36 _protected prototype_ `void OnComponentUpdated(UDMMaterialComponent* InComponent, UDMMaterialComponent* InSource, EDMUpdateType InUpdateType);`
- L39 _protected prototype_ `virtual TArray<FDMPropertyHandle> GetPropertyRows() override;`
- L40 _protected prototype_ `virtual void AddDetailTreeRowExtensionWidgets(const TSharedRef<ICustomDetailsView>& InDetailsView, const FDMPropertyHandle& InPropertyRow, const TSharedRef<ICustomDetailsViewItem>& InItem, const TSharedRef<IPropertyHandle>& InPropertyHandle) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/SDMMaterialPreview.h` (Private)


#### class `UDMMaterialPreviewContext`  
`class UDMMaterialPreviewContext : public UObject`  
_L29-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L34 _public function_ `void SetPreviewWidget(const TSharedRef<SDMMaterialPreview>& InPreviewWidget)`
- L39 _public function_ `TSharedPtr<SDMMaterialPreview> GetPreviewWidget() const`
- L45 _private member_ `TWeakPtr<SDMMaterialPreview> PreviewWidgetWeak;`

#### class `SDMMaterialPreview`  
`class SDMMaterialPreview : public SEditorViewport, public FGCObject`  
_L50-129_
- inherits: `SEditorViewport,FGCObject`
- desc: Based on SMaterialEditor3DPreviewViewport (private)
- L52 _private function_ `SLATE_DECLARE_WIDGET(SDMMaterialPreview, SCompoundWidget) SLATE_BEGIN_ARGS(SDMMaterialPreview) : _ShowMenu(true) , _IsPopout(false)`
- L65 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor>& InEditorWidget, UDynamicMaterialModelBase* InMaterialModelBase);`
- L69 _public prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;`
- L73 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L74 _public prototype_ `virtual FString GetReferencerName() const override;`
- L78 _protected member_ `TWeakPtr<SDMMaterialEditor> EditorWidgetWeak;`
- L79 _protected member_ `bool bShowMenu;`
- L80 _protected member_ `bool bIsPopout;`
- L82 _protected member_ `TSharedPtr<FDMMaterialPreviewViewportClient> EditorViewportClient;`
- L83 _protected member_ `TSharedPtr<FAdvancedPreviewScene> PreviewScene;`
- L85 _protected member_ `TObjectPtr<UMeshComponent> PreviewMeshComponent;`
- L86 _protected member_ `TObjectPtr<UMaterialInterface> PreviewMaterial;`
- L87 _protected member_ `TObjectPtr<APostProcessVolume> PostProcessVolumeActor;`
- L89 _protected prototype_ `TSharedRef<SWidget> MakeViewportToolbarOverlay();`
- L90 _protected prototype_ `void RefreshViewport();`
- L92 _protected prototype_ `void SetPreviewType(EDMMaterialPreviewMesh InPrimitiveType);`
- L94 _protected prototype_ `ECheckBoxState IsPreviewTypeSet(EDMMaterialPreviewMesh InPrimitiveType) const;`
- L96 _protected prototype_ `void SetPreviewAsset(UObject* InAsset);`
- L98 _protected prototype_ `void SetPreviewMaterial(UMaterialInterface* InMaterialInterface);`
- L100 _protected prototype_ `void ApplyPreviewMaterial_Default();`
- L103 _protected prototype_ `void ApplyPreviewMaterial_PostProcess();` — Spawn post processing volume actor if the material has post processing as domain.
- L105 _protected prototype_ `void SetShowPreviewBackground(bool bInShowBackground);`
- L107 _protected prototype_ `void TogglePreviewBackground();`
- L109 _protected prototype_ `ECheckBoxState IsPreviewBackgroundEnabled() const;`
- L111 _protected prototype_ `void OnPropertyChanged(UObject* InObjectBeingModified, FPropertyChangedEvent& InPropertyChangedEvent);`
- L113 _protected prototype_ `void OnFeatureLevelChanged(EShaderPlatform NewShaderPlatform);`
- L115 _protected prototype_ `TSharedRef<SWidget> GenerateToolbarMenu();`
- L117 _protected prototype_ `static void AddActionMenu(UToolMenu* InMenu);`
- L119 _protected prototype_ `void OnEditorSettingsChanged(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L121 _protected prototype_ `void OpenMaterialPreviewTab();`
- L124 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L125 _protected prototype_ `virtual EVisibility OnGetViewportContentVisibility() const override;`
- L126 _protected prototype_ `virtual void BindCommands() override;`
- L127 _protected prototype_ `virtual void OnFocusViewportToSelection() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/SDMMaterialProperties.h` (Private)


#### class `SDMMaterialProperties`  
`class SDMMaterialProperties : public SCompoundWidget, public FNotifyHook`  
_L26-90_
- inherits: `SCompoundWidget,FNotifyHook`
- L28 _private function_ `SLATE_DECLARE_WIDGET(SDMMaterialProperties, SCompoundWidget) SLATE_BEGIN_ARGS(SDMMaterialProperties)`
- L36 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor>& InEditorWidget);`
- L38 _public prototype_ `void Validate();`
- L41 _public prototype_ `virtual void NotifyPreChange(FProperty* InPropertyAboutToChange) override;`
- L42 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L46 _protected member_ `TWeakPtr<SDMMaterialEditor> EditorWidgetWeak;`
- L48 _protected member_ `TDMWidgetSlot<SWidget> Content;`
- L50 _protected member_ `TArray<TSharedRef<ICustomDetailsViewItem>> GlobalItems;`
- L51 _protected member_ `TArray<TSharedRef<SBox>> PropertyPreviewContainers;`
- L52 _protected member_ `TArray<TSharedRef<SBox>> PropertyEmptyContainers;`
- L53 _protected member_ `TArray<TSharedRef<SDMMaterialComponentPreview>> PropertyPreviews;`
- L54 _protected member_ `TArray<TSharedRef<ICustomDetailsViewItem>> SliderItems;`
- L56 _protected member_ `bool bConstructing = false;`
- L58 _protected prototype_ `TSharedRef<SWidget> CreateSlot_Content();`
- L60 _protected prototype_ `void AddProperty(const TSharedRef<ICustomDetailsView>& InDetailsView, const TSharedRef<ICustomDetailsViewItem>& InCategory, UDMMaterialProperty* InProperty);`
- L63 _protected prototype_ `TSharedRef<SWidget> CreatePropertyRow(UDMMaterialProperty* InProperty);`
- L65 _protected prototype_ `TSharedRef<SWidget> CreateSlot_EnabledButton(EDMMaterialPropertyType InMaterialProperty);`
- L67 _protected prototype_ `TSharedRef<SWidget> CreateSlot_PropertyName(EDMMaterialPropertyType InMaterialProperty);`
- L69 _protected prototype_ `bool GetPropertyEnabledEnabled(EDMMaterialPropertyType InMaterialProperty) const;`
- L70 _protected prototype_ `ECheckBoxState GetPropertyEnabledState(EDMMaterialPropertyType InMaterialProperty) const;`
- L71 _protected prototype_ `void OnPropertyEnabledStateChanged(ECheckBoxState InState, EDMMaterialPropertyType InMaterialProperty);`
- L73 _protected prototype_ `FReply OnPropertyClicked(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent, EDMMaterialPropertyType InMaterialProperty);`
- L75 _protected prototype_ `TSharedRef<SWidget> CreateGlobalSlider(UDMMaterialProperty* InProperty);`
- L77 _protected prototype_ `void OnExpansionStateChanged(const TSharedRef<ICustomDetailsViewItem>& InItem, bool bInExpansionState);`
- L79 _protected prototype_ `void OnSettingsUpdated(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L81 _protected prototype_ `bool OnAssetDraggedOver(TArrayView<FAssetData> InAssets, EDMMaterialPropertyType InMaterialProperty);`
- L83 _protected prototype_ `void OnAssetsDropped(const FDragDropEvent& InDragDropEvent, TArrayView<FAssetData> InAssets, EDMMaterialPropertyType InMaterialProperty);`
- L85 _protected prototype_ `void HandleDrop_Texture(UTexture* InTexture, EDMMaterialPropertyType InMaterialProperty);`
- L87 _protected prototype_ `void OnComponentUpdated(UDMMaterialComponent* InComponent, UDMMaterialComponent* InSource, EDMUpdateType InUpdateType);`
- L89 _protected prototype_ `UDMMaterialComponent* GetOriginalComponent(UDMMaterialComponent* InPreviewComponent) const;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/SDMMaterialPropertySelector.h` (Private)


#### class `SDMMaterialPropertySelector`  
`class SDMMaterialPropertySelector : public SCompoundWidget`  
_L30-81_
- inherits: `SCompoundWidget`
- L32 _private function_ `SLATE_DECLARE_WIDGET(SDMMaterialPropertySelector, SCompoundWidget) SLATE_BEGIN_ARGS(SDMMaterialPropertySelector)`
- L38 _public prototype_ `static FText GetSelectButtonText(const FDMMaterialEditorPage& InPage, bool bInShortName);`
- L40 _public prototype_ `static FText GetButtonToolTip(const FDMMaterialEditorPage& InPage);`
- L42 _public prototype_ `virtual ~SDMMaterialPropertySelector() override = default;`
- L44 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor> InEditorWidget);`
- L46 _public prototype_ `TSharedPtr<SDMMaterialEditor> GetEditorWidget() const;`
- L49 _protected member_ `TWeakPtr<SDMMaterialEditor> EditorWidgetWeak;`
- L51 _protected prototype_ `UDynamicMaterialModelEditorOnlyData* GetEditorOnlyData() const;`
- L53 _protected prototype_ `TSharedPtr<SDMMaterialSlotEditor> GetSlotEditorWidget() const;`
- L55 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_PropertyList() = 0;`
- L57 _protected prototype_ `TSharedRef<SWidget> CreateSlot_EnabledButton(EDMMaterialPropertyType InMaterialProperty);`
- L59 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_SelectButton(const FDMMaterialEditorPage& InPage) = 0;`
- L61 _protected prototype_ `bool IsPropertyEnabled(EDMMaterialPropertyType InMaterialProperty) const;`
- L63 _protected prototype_ `bool SetPropertyEnabled(EDMMaterialPropertyType InMaterialProperty, bool bInEnabled);`
- L65 _protected prototype_ `bool DoesPropertySlotExist(EDMMaterialPropertyType InMaterialProperty) const;`
- L67 _protected prototype_ `bool GetPropertyEnabledEnabled(EDMMaterialPropertyType InMaterialProperty) const;`
- L68 _protected prototype_ `ECheckBoxState GetPropertyEnabledState(EDMMaterialPropertyType InMaterialProperty) const;`
- L69 _protected prototype_ `void OnPropertyEnabledStateChanged(ECheckBoxState InState, EDMMaterialPropertyType InMaterialProperty);`
- L71 _protected prototype_ `bool GetPropertySelectEnabled(FDMMaterialEditorPage InPage) const;`
- L72 _protected prototype_ `ECheckBoxState GetPropertySelectState(FDMMaterialEditorPage InPage) const;`
- L73 _protected prototype_ `void OnPropertySelectStateChanged(ECheckBoxState InState, FDMMaterialEditorPage InPage);`
- L74 _protected prototype_ `FSlateColor GetPropertySelectButtonChipColor(FDMMaterialEditorPage InPage) const;`
- L76 _protected prototype_ `void SetSelectedProperty(const FDMMaterialEditorPage& InPage);`
- L78 _protected prototype_ `void SetupMaterialPreviewButton(const TSharedRef<SWidget>& InSelectButton);`
- L80 _protected prototype_ `void OpenMaterialPreviewTab();`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace DynamicMaterialEditor` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::DynamicMaterialEditor`)
- L23 _namespace_ `namespace PropertySelectorColumns` (scope `UE::DynamicMaterialEditor::Private`)
- L25 _variable_ `constexpr int32 Enable = 0;` (scope `UE::DynamicMaterialEditor::Private::PropertySelectorColumns`)
- L26 _variable_ `constexpr int32 Select = 1;` (scope `UE::DynamicMaterialEditor::Private::PropertySelectorColumns`)

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/SDMMaterialSlotEditor.h` (Private)


#### class `SDMMaterialSlotEditor`  
`class SDMMaterialSlotEditor : public SCompoundWidget, public FNotifyHook`  
_L30-177_
- inherits: `SCompoundWidget,FNotifyHook`
- L32 _private function_ `SLATE_DECLARE_WIDGET(SDMMaterialSlotEditor, SCompoundWidget) SLATE_BEGIN_ARGS(SDMMaterialSlotEditor)`
- L38 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLayerSelectionChanged, const TSharedRef<SDMMaterialSlotLayerView>&, const TSharedPtr<FDMMaterialLayerReference>&) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStageSelectionChanged, const TSharedRef<SDMMaterialSlotLayerItem>&, UDMMaterialStage*) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEffectSelectionChanged, const TSharedRef<SDMMaterialSlotLayerEffectView>&, UDMMaterialEffect*) virtual ~SDMMaterialSlotEditor() override;`
- L49 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor>& InEditorWidget, UDMMaterialSlot* InSlot);`
- L51 _public prototype_ `void ValidateSlots();`
- L53 _public prototype_ `TSharedPtr<SDMMaterialEditor> GetEditorWidget() const;`
- L55 _public prototype_ `DLLEXPORT UDMMaterialSlot* GetSlot() const;`
- L58 _public prototype_ `void ClearSelection();` — Actions
- L60 _public prototype_ `bool CanAddNewLayer() const;`
- L61 _public prototype_ `void AddNewLayer();`
- L63 _public prototype_ `bool CanInsertNewLayer() const;`
- L64 _public prototype_ `void InsertNewLayer();`
- L66 _public prototype_ `bool CanCopySelectedLayer() const;`
- L67 _public prototype_ `void CopySelectedLayer();`
- L69 _public prototype_ `bool CanCutSelectedLayer() const;`
- L70 _public prototype_ `void CutSelectedLayer();`
- L72 _public prototype_ `bool CanPasteLayer() const;`
- L73 _public prototype_ `void PasteLayer();`
- L75 _public prototype_ `bool CanDuplicateSelectedLayer() const;`
- L76 _public prototype_ `void DuplicateSelectedLayer();`
- L78 _public prototype_ `bool CanDeleteSelectedLayer() const;`
- L79 _public prototype_ `void DeleteSelectedLayer();`
- L81 _public prototype_ `bool SelectLayer_CanExecute(int32 InIndex) const;`
- L82 _public prototype_ `void SelectLayer_Execute(int32 InIndex);`
- L84 _public prototype_ `bool SetOpacity_CanExecute();`
- L85 _public prototype_ `void SetOpacity_Execute(float InOpacity);`
- L88 _public prototype_ `TSharedRef<SDMMaterialSlotLayerView> GetLayerView() const;` — Slots
- L90 _public prototype_ `void InvalidateSlotSettings();`
- L92 _public prototype_ `void InvalidateLayerView();`
- L94 _public prototype_ `void InvalidateLayerSettings();`
- L97 _public prototype_ `void SetSelectedLayer(UDMMaterialLayerObject* InLayer);` — Actions
- L100 _public function_ `FOnLayerSelectionChanged::RegistrationType& GetOnLayerSelectionChanged()` — Events
- L101 _public prototype_ `void TriggerLayerSelectionChange(const TSharedRef<SDMMaterialSlotLayerView>& InLayerView, const TSharedPtr<FDMMaterialLayerReference>& InLayerReference);`
- L103 _public function_ `FOnStageSelectionChanged::RegistrationType& GetOnStageSelectionChanged()`
- L104 _public prototype_ `void TriggerStageSelectionChange(const TSharedRef<SDMMaterialSlotLayerItem>& InLayerItem, UDMMaterialStage* InStage);`
- L106 _public function_ `FOnEffectSelectionChanged::RegistrationType& GetOnEffectSelectionChanged()`
- L107 _public prototype_ `void TriggerEffectSelectionChange(const TSharedRef<SDMMaterialSlotLayerEffectView>& InEffectView, UDMMaterialEffect* InEffect);`
- L110 _public prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L111 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L115 _protected member_ `TWeakPtr<SDMMaterialEditor> EditorWidgetWeak;`
- L116 _protected member_ `TWeakObjectPtr<UDMMaterialSlot> MaterialSlotWeak;`
- L117 _protected member_ `bool bIsDynamic;`
- L119 _protected member_ `TDMWidgetSlot<SWidget> ContentSlot;`
- L120 _protected member_ `TDMWidgetSlot<SWidget> SlotSettingsSlot;`
- L121 _protected member_ `TDMWidgetSlot<SDMMaterialSlotLayerView> LayerViewSlot;`
- L122 _protected member_ `TDMWidgetSlot<SWidget> LayerSettingsSlot;`
- L124 _protected member_ `TWeakObjectPtr<UDMMaterialValueFloat1> LayerOpacityValueWeak;`
- L125 _protected member_ `TSharedPtr<SWidget> LayerOpacityItem;`
- L127 _protected member_ `FOnLayerSelectionChanged OnLayerSelectionChanged;`
- L128 _protected member_ `FOnStageSelectionChanged OnStageSelectionChanged;`
- L129 _protected member_ `FOnEffectSelectionChanged OnEffectSelectionChanged;`
- L131 _protected prototype_ `TSharedRef<SWidget> CreateSlot_Container();`
- L133 _protected prototype_ `TSharedRef<SWidget> CreateSlot_SlotSettings();`
- L135 _protected prototype_ `TSharedRef<SWidget> CreateSlot_LayerOpacity();`
- L137 _protected prototype_ `TSharedRef<SDMMaterialSlotLayerView> CreateSlot_LayerView();`
- L139 _protected prototype_ `TSharedRef<SWidget> CreateSlot_LayerSettings();`
- L141 _protected prototype_ `void OnSlotLayersUpdated(UDMMaterialSlot* InSlot);`
- L143 _protected prototype_ `void OnSlotPropertiesUpdated(UDMMaterialSlot* InSlot);`
- L145 _protected prototype_ `FText GetLayerButtonsDescription() const;`
- L146 _protected prototype_ `TSharedRef<SWidget> GetLayerButtonsMenuContent();`
- L148 _protected prototype_ `bool GetLayerCanAddEffect() const;`
- L149 _protected prototype_ `TSharedRef<SWidget> GetLayerEffectsMenuContent();`
- L151 _protected prototype_ `bool GetLayerRowsButtonsCanDuplicate() const;`
- L152 _protected prototype_ `FReply OnLayerRowButtonsDuplicateClicked();`
- L154 _protected prototype_ `bool GetLayerRowsButtonsCanRemove() const;`
- L155 _protected prototype_ `FReply OnLayerRowButtonsRemoveClicked();`
- L157 _protected prototype_ `void OnOpacityUpdated(UDMMaterialComponent* InComponent, UDMMaterialComponent* InSource, EDMUpdateType InUpdateType);`
- L160 _protected prototype_ `bool OnAreAssetsAcceptableForDrop(TArrayView<FAssetData> InAssets);` — Drag and drop.
- L162 _protected prototype_ `void OnAssetsDropped(const FDragDropEvent& InDragDropEvent, TArrayView<FAssetData> InAssets);`
- L164 _protected prototype_ `void HandleDrop_Texture(UTexture* InTexture);`
- L166 _protected prototype_ `void HandleDrop_CreateTextureSet(const TArray<FAssetData>& InTextureAssets);`
- L168 _protected prototype_ `void HandleDrop_TextureSet(UDMTextureSet* InTextureSet);`
- L170 _protected prototype_ `void HandleDrop_MaterialFunction(UMaterialFunctionInterface* InMaterialFunction);`
- L172 _protected prototype_ `bool IsValidLayerDropForDelete(TSharedPtr<FDragDropOperation> InDragDropOperation);`
- L174 _protected prototype_ `bool CanDropLayerForDelete(TSharedPtr<FDragDropOperation> InDragDropOperation);`
- L176 _protected prototype_ `FReply OnLayerDroppedForDelete(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent);`

#### Free symbols / members of external scopes

- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLayerSelectionChanged, const TSharedRef<SDMMaterialSlotLayerView>&, const TSharedPtr<FDMMaterialLayerReference>&) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStageSelectionChanged, const TSharedRef<SDMMaterialSlotLayerItem>&, UDMMaterialStage*) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEffectSelectionChanged, const TSharedRef<SDMMaterialSlotLayerEffectView>&, UDMMaterialEffect*) virtual ~SDMMaterialSlotEditor() override;`
- L41 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStageSelectionChanged, const TSharedRef<SDMMaterialSlotLayerItem>&, UDMMaterialStage*) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEffectSelectionChanged, const TSharedRef<SDMMaterialSlotLayerEffectView>&, UDMMaterialEffect*) virtual ~SDMMaterialSlotEditor() override;`
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEffectSelectionChanged, const TSharedRef<SDMMaterialSlotLayerEffectView>&, UDMMaterialEffect*) virtual ~SDMMaterialSlotEditor() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/SDMObjectEditorWidgetBase.h` (Private)


#### class `SDMObjectEditorWidgetBase`  
`class SDMObjectEditorWidgetBase : public SCompoundWidget, public FNotifyHook`  
_L28-103_
- inherits: `SCompoundWidget,FNotifyHook`
- desc: Base class for the object editor. Provides the methods and layout for producing a Custom Details View.
- L30 _private function_ `SLATE_DECLARE_WIDGET(SDMObjectEditorWidgetBase, SCompoundWidget) SLATE_BEGIN_ARGS(SDMObjectEditorWidgetBase)`
- L38 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor>& InEditorWidget, UObject* InObject);`
- L40 _public function_ `UObject* GetObject() const`
- L42 _public function_ `TSharedPtr<SDMMaterialEditor> GetEditorWidget() const`
- L44 _public prototype_ `void Validate();`
- L47 _public prototype_ `virtual void NotifyPreChange(FProperty* InPropertyAboutToChange) override;`
- L48 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L52 _protected member_ `static constexpr const TCHAR* DefaultCategoryName = TEXT("Gen`
- L54 _protected member_ `TWeakPtr<SDMMaterialEditor> EditorWidgetWeak;`
- L55 _protected member_ `TWeakObjectPtr<UObject> ObjectWeak;`
- L57 _protected member_ `TDMWidgetSlot<SWidget> ContentSlot;`
- L59 _protected member_ `TSharedPtr<IDetailKeyframeHandler> KeyframeHandler;`
- L60 _protected member_ `bool bConstructing;`
- L61 _protected member_ `TArray<FName> Categories;`
- L62 _protected member_ `TSharedPtr<ICustomDetailsViewItem> DefaultCategoryItem;`
- L63 _protected member_ `bool bShowCategories = true;`
- L65 _protected prototype_ `TSharedRef<SWidget> CreateWidget();`
- L67 _protected prototype_ `virtual TSharedRef<ICustomDetailsViewItem> GetDefaultCategory(const TSharedRef<ICustomDetailsView>& InDetailsView, const FCustomDetailsViewItemId& InRootId);`
- L70 _protected prototype_ `TSharedRef<ICustomDetailsViewItem> GetCategoryForRow(const TSharedRef<ICustomDetailsView>& InDetailsView, const FCustomDetailsViewItemId& InRootId, const FDMPropertyHandle& InPropertyRow);`
- L73 _protected prototype_ `void AddDetailTreeRow(const TSharedRef<ICustomDetailsView>& InDetailsView, const TSharedRef<ICustomDetailsViewItem>& InParent, ECustomDetailsTreeInsertPosition InPosition, const FDMPropertyHandle& InPropertyRow);`
- L76 _protected prototype_ `void AddCustomRow(const TSharedRef<ICustomDetailsView>& InDetailsView, const TSharedRef<ICustomDetailsViewItem>& InParent, ECustomDetailsTreeInsertPosition InPosition, const FDMPropertyHandle& InPropertyRow);`
- L79 _protected prototype_ `void OnExpansionStateChanged(const TSharedRef<ICustomDetailsViewItem>& InItem, bool bInExpansionState);`
- L81 _protected prototype_ `virtual TArray<FDMPropertyHandle> GetPropertyRows() = 0;`
- L83 _protected prototype_ `virtual void AddDetailTreeRowExtensionWidgets(const TSharedRef<ICustomDetailsView>& InDetailsView, const FDMPropertyHandle& InPropertyRow, const TSharedRef<ICustomDetailsViewItem>& InItem, const TSharedRef<IPropertyHandle>& InPropertyHandle);`
- L86 _protected prototype_ `TOptional<FPropertyRowExtensionButton> CreateKeyframeButton(TSharedPtr<IPropertyHandle> InPreviewPropertyHandle, TSharedPtr<IPropertyHandle> InOriginalPropertyHandle);`
- L88 _protected prototype_ `FSlateIcon GetCreateKeyIcon(TWeakPtr<IPropertyHandle> InPreviewPropertyHandleWeak, TWeakPtr<IPropertyHandle> InOriginalPropertyHandleWeak) const;`
- L90 _protected prototype_ `bool CanCreateKeyFrame(TWeakPtr<IPropertyHandle> InPreviewPropertyHandleWeak, TWeakPtr<IPropertyHandle> InOriginalPropertyHandleWeak) const;`
- L92 _protected prototype_ `void CreateKeyFrame(TWeakPtr<IPropertyHandle> InPreviewPropertyHandleWeak, TWeakPtr<IPropertyHandle> InOriginalPropertyHandleWeak);`
- L94 _protected prototype_ `FPropertyRowExtensionButton CreateNeedsApplyButton() const;`
- L96 _protected prototype_ `TSharedPtr<ICustomDetailsViewItem> CreateChildItem(const TSharedRef<ICustomDetailsView>& InDetailsView, const TSharedPtr<ICustomDetailsViewItem>& InParent, const TSharedRef<IDetailTreeNode>& InChildNode, FDMPropertyHandle InOriginalRow);`
- L99 _protected prototype_ `virtual TSharedPtr<ICustomDetailsViewItem> CreateChildItem_Impl(const TSharedRef<ICustomDetailsView>& InDetailsView, const TSharedRef<ICustomDetailsViewItem>& InParent, const TSharedRef<IDetailTreeNode>& InChildNode, const TSharedRef<IPropertyHandle>& InPropertyHandle, const FDMPropertyHandle& InOriginalRow);`
- L102 _protected prototype_ `void CustomizeItemContextMenu(const TSharedRef<ICustomDetailsViewItem>& InItem, const FDMPropertyHandle& InPropertyRow);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/SDMStatusBar.h` (Private)


#### class `SDMStatusBar`  
`class SDMStatusBar : public SCompoundWidget`  
_L14-45_
- inherits: `SCompoundWidget`
- L16 _private function_ `SLATE_BEGIN_ARGS(SDMStatusBar)`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor>& InEditorWidget, UDynamicMaterialModelBase* InMaterialModelBase);`
- L25 _protected member_ `TWeakPtr<SDMMaterialEditor> EditorWidgetWeak;`
- L26 _protected member_ `TWeakObjectPtr<UDynamicMaterialModelBase> MaterialModelBaseWeak;`
- L28 _protected member_ `TDMWidgetSlot<SWidget> ContentSlot;`
- L30 _protected member_ `int32 CachedSlotCount = 0;`
- L31 _protected member_ `int32 CachedCurrentLayerCount = 0;`
- L32 _protected member_ `int32 CachedTotalLayerCount = 0;`
- L34 _protected member_ `FMaterialStatistics CachedMaterialStats;`
- L36 _protected prototype_ `TSharedRef<SWidget> CreateContent();`
- L38 _protected prototype_ `SWrapBox::FSlot::FSlotArguments CreateStatsWrapBoxEntry(const FText& InText, const FText& InTooltipText);`
- L40 _protected prototype_ `FText GetNumPixelShaderInstructionsText() const;`
- L41 _protected prototype_ `FText GetNumVertexShaderInstructionsText() const;`
- L42 _protected prototype_ `FText GetNumSamplersText() const;`
- L44 _protected prototype_ `void OnMaterialBuilt(UDynamicMaterialModelBase* InMaterialModelBase);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/SDMToolBar.h` (Private)


#### class `SDMToolBar`  
`class SDMToolBar : public SCompoundWidget`  
_L33-128_
- inherits: `SCompoundWidget`
- desc: Material Designer ToolBar Displays the selected actor that the Material Designer is editing and allows for switching between slots for that actor.
- L36 _public function_ `SLATE_BEGIN_ARGS(SDMToolBar)`
- L39 _public prototype_ `virtual ~SDMToolBar() override = default;`
- L41 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor>& InEditorWidget, const FDMObjectMaterialProperty& InObjectProperty);`
- L43 _public function_ `AActor* GetMaterialActor() const`
- L45 _public prototype_ `FText GetActorName() const;`
- L47 _public prototype_ `TSharedPtr<SDMMaterialEditor> GetEditorWidget() const;`
- L50 _protected member_ `TWeakPtr<SDMMaterialEditor> EditorWidgetWeak;`
- L51 _protected member_ `TWeakObjectPtr<AActor> MaterialActorWeak;`
- L53 _protected member_ `TArray<TSharedPtr<FDMObjectMaterialProperty>> ActorMaterialProperties;`
- L54 _protected member_ `int32 SelectedMaterialElementIndex;`
- L56 _protected member_ `TSharedPtr<SBox> PropertySelectorContainer;`
- L57 _protected member_ `TSharedPtr<SWidget> SaveButtonWidget;`
- L58 _protected member_ `TSharedPtr<SWidget> ActorRowWidget;`
- L59 _protected member_ `TSharedPtr<SWidget> AssetRowWidget;`
- L60 _protected member_ `TSharedPtr<STextBlock> ActorNameWidget;`
- L61 _protected member_ `TSharedPtr<STextBlock> AssetNameWidget;`
- L62 _protected member_ `TSharedPtr<STextBlock> InstanceWidget;`
- L63 _protected member_ `TSharedPtr<SWidget> OpenParentButton;`
- L64 _protected member_ `TSharedPtr<SWidget> ConvertToEditableButton;`
- L65 _protected member_ `TSharedPtr<SWidget> ConvertToInstanceButton;`
- L67 _protected prototype_ `bool IsDynamicMaterialModel() const;`
- L69 _protected prototype_ `bool IsAutoCompileAndApplyOverridden() const;`
- L71 _protected prototype_ `UDynamicMaterialModelBase* GetOriginalMaterialModelBase() const;`
- L73 _protected prototype_ `TSharedRef<SWidget> CreateToolBarEntries();`
- L75 _protected prototype_ `void SetActorPropertySelected(const FDMObjectMaterialProperty& InObjectProperty);`
- L77 _protected prototype_ `int32 GetDuplicateIndex(const FDMObjectMaterialProperty& InObjectProperty) const;`
- L79 _protected prototype_ `void UpdateButtonVisibilities();`
- L81 _protected prototype_ `TSharedRef<SWidget> CreateToolBarButton(TAttribute<const FSlateBrush*> InImageBrush, const TAttribute<FText>& InTooltipText, FOnClicked InOnClicked);`
- L83 _protected prototype_ `TSharedRef<SWidget> CreateSlotsComboBoxWidget();`
- L85 _protected prototype_ `TSharedRef<SWidget> GenerateSelectedMaterialSlotRow(TSharedPtr<FDMObjectMaterialProperty> InSelectedSlot) const;`
- L86 _protected prototype_ `FText GetSlotDisplayName(TWeakPtr<FDMObjectMaterialProperty> InSlotWeak) const;`
- L87 _protected prototype_ `bool GetSlotEnabled(TWeakPtr<FDMObjectMaterialProperty> InSlotWeak) const;`
- L88 _protected prototype_ `FText GetSelectedMaterialSlotName() const;`
- L89 _protected prototype_ `void OnMaterialSlotChanged(TSharedPtr<FDMObjectMaterialProperty> InSelectedSlot, ESelectInfo::Type InSelectInfoType);`
- L91 _protected prototype_ `const FSlateBrush* GetFollowSelectionBrush() const;`
- L92 _protected prototype_ `FSlateColor GetFollowSelectionColor() const;`
- L93 _protected prototype_ `FReply OnFollowSelectionButtonClicked();`
- L95 _protected prototype_ `FReply OnExportMaterialInstanceButtonClicked();`
- L97 _protected prototype_ `FReply OnBrowseClicked();`
- L99 _protected prototype_ `FReply OnUseClicked();`
- L101 _protected prototype_ `FText GetAssetName() const;`
- L103 _protected prototype_ `FText GetAssetToolTip() const;`
- L105 _protected prototype_ `const FSlateBrush* GetSaveIcon() const;`
- L107 _protected prototype_ `FReply OnSaveClicked();`
- L109 _protected prototype_ `FReply OnOpenParentClicked();`
- L111 _protected prototype_ `FReply OnConvertToEditableClicked();`
- L113 _protected prototype_ `FReply OnConvertToInstanceClicked();`
- L115 _protected prototype_ `TSharedRef<SWidget> GenerateSettingsMenu();`
- L117 _protected prototype_ `EVisibility GetAutoCompileVisibility() const;`
- L118 _protected prototype_ `FSlateColor GetAutoCompileColor() const;`
- L119 _protected prototype_ `FReply OnAutoCompileClicked();`
- L121 _protected prototype_ `EVisibility GetAutoApplyVisibility() const;`
- L122 _protected prototype_ `FSlateColor GetAutoApplyColor() const;`
- L123 _protected prototype_ `FReply OnAutoApplyClicked();`
- L125 _protected prototype_ `EVisibility GetLiveEditVisibility() const;`
- L126 _protected prototype_ `FSlateColor GetLiveEditColor() const;`
- L127 _protected prototype_ `FReply OnLiveEditClicked();`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace ESelectInfo`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/SlotEditor/SDMMaterialLayerBlendMode.h` (Private)


#### class `UDMSourceBlendModeContextObject`  
`class UDMSourceBlendModeContextObject : public UObject`  
_L25-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L30 _public prototype_ `TSharedPtr<SDMMaterialLayerBlendMode> GetBlendModeWidget() const;`
- L32 _public prototype_ `void SetBlendModeWidget(const TSharedPtr<SDMMaterialLayerBlendMode>& InBlendModeWidget);`
- L35 _private member_ `TWeakPtr<SDMMaterialLayerBlendMode> BlendModeWidgetWeak;`

#### struct `FDMBlendNameClass`  
`struct FDMBlendNameClass`  
_L38-42_
- L40 _public member_ `FText BlendName;`
- L41 _public member_ `TSubclassOf<UDMMaterialStageBlend> BlendClass;`

#### class `SDMMaterialLayerBlendMode`  
`class SDMMaterialLayerBlendMode : public SCompoundWidget`  
_L44-78_
- inherits: `SCompoundWidget`
- L47 _public function_ `SLATE_BEGIN_ARGS(SDMMaterialLayerBlendMode)`
- L49 _public prototype_ `SLATE_ATTRIBUTE(TSubclassOf<UDMMaterialStageBlend>, SelectedItem) SLATE_END_ARGS() virtual ~SDMMaterialLayerBlendMode() override = default;`
- L54 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialSlotLayerItem> InLayerItem);`
- L57 _protected member_ `static TArray<TStrongObjectPtr<UClass>> SupportedBlendClasses;`
- L58 _protected member_ `static TMap<FName, FDMBlendNameClass> BlendMap;`
- L60 _protected prototype_ `static void EnsureBlendMap();`
- L61 _protected prototype_ `static void EnsureMenuRegistered();`
- L62 _protected prototype_ `static void MakeSourceBlendMenu(UToolMenu* InToolMenu);`
- L64 _protected member_ `TWeakPtr<SDMMaterialSlotLayerItem> LayerItemWidgetWeak;`
- L65 _protected member_ `TAttribute<TSubclassOf<UDMMaterialStageBlend>> SelectedItem;`
- L67 _protected prototype_ `TSharedRef<SWidget> OnGenerateWidget(const FName InItem);`
- L69 _protected prototype_ `FText GetSelectedItemText() const;`
- L71 _protected prototype_ `TSharedRef<SWidget> MakeSourceBlendMenuWidget();`
- L73 _protected prototype_ `void OnBlendModeSelected(UClass* InBlendClass);`
- L74 _protected prototype_ `bool CanSelectBlendMode(UClass* InBlendClass);`
- L75 _protected prototype_ `bool InBlendModeSelected(UClass* InBlendClass);`
- L77 _protected prototype_ `bool IsSelectorEnabled() const;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/SlotEditor/SDMMaterialSlotLayerEffectItem.h` (Private)


#### class `SDMMaterialSlotLayerEffectItem`  
`class SDMMaterialSlotLayerEffectItem : public STableRow<UDMMaterialEffect*>`  
_L15-75_
- inherits: `STableRow<UDMMaterialEffect*>`
- L17 _private function_ `SLATE_DECLARE_WIDGET(SDMMaterialSlotLayerEffectItem, STableRow<UDMMaterialEffect*>) SLATE_BEGIN_ARGS(SDMMaterialSlotLayerEffectItem)`
- L23 _public prototype_ `virtual ~SDMMaterialSlotLayerEffectItem() override = default;`
- L25 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialSlotLayerEffectView>& InEffectView, UDMMaterialEffect* InMaterialEffect);`
- L27 _public prototype_ `TSharedPtr<SDMMaterialSlotLayerEffectView> GetEffectView() const;`
- L29 _public prototype_ `UDMMaterialEffect* GetMaterialEffect() const;`
- L32 _protected member_ `TWeakPtr<SDMMaterialSlotLayerEffectView> EffectViewWeak;`
- L33 _protected member_ `TWeakObjectPtr<UDMMaterialEffect> EffectWeak;`
- L35 _protected prototype_ `int32 OnEffectItemPaintDropIndicator(EItemDropZone InItemDropZone, const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const;`
- L39 _protected prototype_ `UObject* GetEffectAsset() const;`
- L42 _protected prototype_ `TSharedRef<SWidget> CreateMainContent();` — Slots
- L44 _protected prototype_ `TSharedRef<SWidget> CreateLayerBypassButton();`
- L46 _protected prototype_ `TSharedRef<SWidget> CreateLayerRemoveButton();`
- L48 _protected prototype_ `TSharedRef<SWidget> CreateBrowseToEffectButton();`
- L50 _protected prototype_ `FText GetToolTipText() const;`
- L52 _protected prototype_ `FText GetLayerHeaderText() const;`
- L54 _protected prototype_ `bool CanModifyMaterialModel() const;`
- L56 _protected prototype_ `const FSlateBrush* GetLayerBypassButtonImage() const;`
- L58 _protected prototype_ `FReply OnLayerRemoveButtonClick();`
- L60 _protected prototype_ `FReply OnBrowseToEffectButtonClick();`
- L63 _protected prototype_ `TOptional<EItemDropZone> OnEffectItemCanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, UDMMaterialEffect* InMaterialEffect) const;` — Drag and Drop
- L66 _protected prototype_ `FReply OnEffectItemDragDetected(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);`
- L68 _protected prototype_ `FReply OnEffectItemAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, UDMMaterialEffect* InMaterialEffect);`
- L72 _protected prototype_ `FCursorReply OnCursorQuery(const FGeometry& InMyGeometry, const FPointerEvent& InCursorEvent) const override;` — Events
- L74 _protected prototype_ `FReply OnLayerBypassButtonClick();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/SlotEditor/SDMMaterialSlotLayerEffectView.h` (Private)


#### class `SDMMaterialSlotLayerEffectView`  
`class SDMMaterialSlotLayerEffectView : public SListView<UDMMaterialEffect*>, public FSelfRegisteringEditorUndoClient`  
_L17-61_
- inherits: `SListView<UDMMaterialEffect*>,FSelfRegisteringEditorUndoClient`
- L19 _private function_ `SLATE_DECLARE_WIDGET(SDMMaterialSlotLayerEffectView, SListView<UDMMaterialEffect*>) SLATE_BEGIN_ARGS(SDMMaterialSlotLayerEffectView)`
- L27 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialSlotLayerItem>& InLayerItem);`
- L29 _public prototype_ `TSharedPtr<SDMMaterialSlotLayerItem> GetLayerItem() const;`
- L31 _public prototype_ `UDMMaterialEffect* GetSelectedEffect() const;`
- L33 _public prototype_ `void SetSelectedEffect(UDMMaterialEffect* InEffect);`
- L35 _public prototype_ `TSharedPtr<SDMMaterialSlotLayerEffectItem> GetWidgetForEffect(UDMMaterialEffect* InEffect) const;`
- L38 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L39 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L43 _protected member_ `TWeakPtr<SDMMaterialSlotLayerItem> LayerItemWeak;`
- L44 _protected member_ `TArray<UDMMaterialEffect*> Effects;`
- L47 _protected prototype_ `void RegenerateItems();` — List
- L49 _protected prototype_ `TSharedRef<ITableRow> OnGenerateEffectItemWidget(UDMMaterialEffect* InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L51 _protected prototype_ `void OnEffectItemSelectionChanged(UDMMaterialEffect* InSelectedItem, ESelectInfo::Type InSelectInfo);`
- L54 _protected prototype_ `void OnUndo();` — Events
- L56 _protected prototype_ `void OnEffectStackUpdate(UDMMaterialComponent* InComponent, UDMMaterialComponent* InSource, EDMUpdateType InUpdateType);`
- L58 _protected prototype_ `TSharedPtr<SWidget> CreateEffectItemContextMenu();`
- L60 _protected prototype_ `void OnEditedComponentChanged(const TSharedRef<SDMMaterialComponentEditor>& InComponentEditor, UDMMaterialComponent* InComponent);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/SlotEditor/SDMMaterialSlotLayerItem.h` (Private)


#### class `SDMMaterialSlotLayerItem`  
`class SDMMaterialSlotLayerItem : public STableRow<TSharedPtr<FDMMaterialLayerReference>>`  
_L26-132_
- inherits: `STableRow<TSharedPtr<FDMMaterialLayerReference>>`
- desc: Material Slot Layer Represents a single item in the layer view that can be dragged and re-arranged. Displays the base and mask stages, along with enable and link buttons.
- L29 _public function_ `SLATE_DECLARE_WIDGET(SDMMaterialSlotLayerItem, STableRow<TSharedPtr<FDMMaterialLayerReference>>) SLATE_BEGIN_ARGS(SDMMaterialSlotLayerItem)`
- L32 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialSlotLayerView>& InLayerView, const TSharedPtr<FDMMaterialLayerReference>& InLayerReferenceItem);`
- L37 _public prototype_ `TSharedPtr<SDMMaterialSlotLayerView> GetSlotLayerView() const;`
- L39 _public prototype_ `UDMMaterialLayerObject* GetLayer() const;`
- L41 _public prototype_ `int32 GetLayerIndex() const;`
- L43 _public prototype_ `TSharedPtr<SDMMaterialSlotLayerEffectView> GetEffectView() const;`
- L45 _public prototype_ `bool AreEffectsExpanded() const;`
- L47 _public prototype_ `void SetEffectsExpanded(bool bInExpanded);`
- L49 _public prototype_ `TSharedPtr<SDMMaterialStage> GetWidgetForStageType(EDMMaterialLayerStage InLayerStage) const;`
- L51 _public prototype_ `TSharedPtr<SDMMaterialStage> GetWidgetForStage(UDMMaterialStage* InStage) const;`
- L54 _protected member_ `static const FLazyName EffectViewName;`
- L56 _protected member_ `TWeakPtr<SDMMaterialSlotLayerView> LayerViewWeak;`
- L57 _protected member_ `TSharedPtr<FDMMaterialLayerReference> LayerItem;`
- L58 _protected member_ `bool bIsDynamic;`
- L60 _protected member_ `TSharedPtr<SDMMaterialStage> BaseStageWidget;`
- L61 _protected member_ `TSharedPtr<SDMMaterialStage> MaskStageWidget;`
- L62 _protected member_ `TSharedPtr<SBox> LayerHeaderTextContainer;`
- L63 _protected member_ `TSharedPtr<SDMMaterialSlotLayerEffectView> EffectView;`
- L65 _protected prototype_ `bool AreStagesLinked() const;`
- L68 _protected prototype_ `TSharedRef<SWidget> CreateMainContent();` — Slots
- L69 _protected prototype_ `TSharedRef<SWidget> CreateHeaderRowContent();`
- L70 _protected prototype_ `TSharedRef<SWidget> CreateEffectsRowContent();`
- L73 _protected prototype_ `TSharedRef<SWidget> CreateStageWidget(EDMMaterialLayerStage InLayerStage);` — Create components of the slot layer.
- L74 _protected prototype_ `TSharedRef<SWidget> CreateHandleWidget();`
- L76 _protected prototype_ `TSharedRef<SWidget> CreateLayerBypassButton();`
- L77 _protected prototype_ `TSharedRef<SWidget> CreateTogglesWidget();`
- L78 _protected prototype_ `TSharedRef<SWidget> CreateLayerBaseToggleButton();`
- L79 _protected prototype_ `TSharedRef<SWidget> CreateLayerMaskToggleButton();`
- L80 _protected prototype_ `TSharedRef<SWidget> CreateLayerLinkToggleButton();`
- L81 _protected prototype_ `TSharedRef<SWidget> CreateLayerHeaderText();`
- L82 _protected prototype_ `TSharedPtr<SWidget> CreateLayerHeaderEditableText();`
- L83 _protected prototype_ `TSharedRef<SWidget> CreateEffectsToggleButton();`
- L84 _protected prototype_ `TSharedRef<SWidget> CreateStageSourceButton(EDMMaterialLayerStage InStage);`
- L85 _protected prototype_ `TSharedRef<SWidget> CreateBlendModeSelector();`
- L87 _protected prototype_ `EVisibility GetEffectsListVisibility() const;`
- L88 _protected prototype_ `EVisibility GetEffectsToggleButtonVisibility() const;`
- L90 _protected prototype_ `void OnLayerNameChangeCommited(const FText& InText, ETextCommit::Type InCommitType);`
- L92 _protected prototype_ `const FSlateBrush* GetEffectsToggleButtonImage() const;`
- L93 _protected prototype_ `FReply OnEffectsToggleButtonClicked();`
- L95 _protected prototype_ `const FSlateBrush* GetRowHandleBrush() const;`
- L97 _protected prototype_ `const FSlateBrush* GetCreateLayerBypassButtonImage() const;`
- L98 _protected prototype_ `FReply OnCreateLayerBypassButtonClicked();`
- L100 _protected prototype_ `EVisibility GetLayerLinkToggleButtonVisibility() const;`
- L101 _protected prototype_ `const FSlateBrush* GetLayerLinkToggleButtonImage() const;`
- L102 _protected prototype_ `FReply OnLayerLinkToggleButton();`
- L104 _protected prototype_ `const FSlateBrush* GetStageToggleButtonImage(EDMMaterialLayerStage InLayerStage) const;`
- L105 _protected prototype_ `FReply OnStageToggleButtonClicked(EDMMaterialLayerStage InLayerStage);`
- L107 _protected prototype_ `FText GetStageSourceButtonToolTip(EDMMaterialLayerStage InLayerStage) const;`
- L108 _protected prototype_ `const FSlateBrush* GetStageSourceButtonImage(EDMMaterialLayerStage InLayerStage) const;`
- L109 _protected prototype_ `FReply OnStageSourceButtonClicked(EDMMaterialLayerStage InLayerStage);`
- L110 _protected prototype_ `TSharedRef<SWidget> GetStageSourceMenuContent(EDMMaterialLayerStage InLayerStage);`
- L113 _protected prototype_ `FText GetToolTipText() const;` — Text
- L114 _protected prototype_ `FText GetLayerHeaderText() const;`
- L115 _protected prototype_ `FText GetLayerIndexText() const;`
- L116 _protected prototype_ `FText GetBlendModeText() const;`
- L119 _protected prototype_ `int32 OnLayerItemPaintDropIndicator(EItemDropZone InItemDropZone, const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const;` — Drag and Drop
- L123 _protected prototype_ `TOptional<EItemDropZone> OnLayerItemCanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, TSharedPtr<FDMMaterialLayerReference> InSlotLayer) const;`
- L126 _protected prototype_ `FReply OnLayerItemDragDetected(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);`
- L128 _protected prototype_ `FReply OnLayerItemAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, TSharedPtr<FDMMaterialLayerReference> InSlotLayer);`
- L131 _protected prototype_ `void HandleLayerDrop(const TSharedPtr<FDMSlotLayerDragDropOperation>& InOperation);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/SlotEditor/SDMMaterialSlotLayerView.h` (Private)


#### class `SDMMaterialSlotLayerView`  
`class SDMMaterialSlotLayerView : public SListView<TSharedPtr<FDMMaterialLayerReference>>, public FSelfRegisteringEditorUndoClient`  
_L16-76_
- inherits: `SListView<TSharedPtr<FDMMaterialLayerReference>>,FSelfRegisteringEditorUndoClient`
- L18 _private function_ `SLATE_DECLARE_WIDGET(SDMMaterialSlotLayerView, SListView<TSharedPtr<FDMMaterialLayerReference>>) SLATE_BEGIN_ARGS(SDMMaterialSlotLayerView)`
- L26 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialSlotEditor> InSlotEditorWidget);`
- L28 _public prototype_ `TSharedPtr<SDMMaterialSlotEditor> GetSlotEditorWidget() const;`
- L30 _public prototype_ `UDMMaterialLayerObject* GetSelectedLayer() const;`
- L32 _public prototype_ `void SetSelectedLayer(UDMMaterialLayerObject* InLayer);`
- L34 _public prototype_ `TSharedPtr<SDMMaterialSlotLayerItem> GetWidgetForLayer(UDMMaterialLayerObject* InLayer) const;`
- L36 _public prototype_ `void EnsureSelectedStage();`
- L39 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L40 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L44 _protected member_ `TWeakPtr<SDMMaterialSlotEditor> SlotEditorWidgetWeak;`
- L46 _protected member_ `TArray<TSharedPtr<FDMMaterialLayerReference>> LayerItems;`
- L48 _protected prototype_ `void BindCommands();`
- L50 _protected prototype_ `void UnbindCommands();`
- L53 _protected prototype_ `void RegenerateItems();` — List
- L55 _protected prototype_ `TSharedRef<ITableRow> OnGenerateLayerItemWidget(TSharedPtr<FDMMaterialLayerReference> InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L57 _protected prototype_ `void OnLayerItemSelectionChanged(TSharedPtr<FDMMaterialLayerReference> InSelectedItem, ESelectInfo::Type InSelectInfo);`
- L59 _protected prototype_ `TSharedPtr<SWidget> CreateLayerItemContextMenu();`
- L61 _protected prototype_ `TSharedPtr<SDMMaterialSlotLayerItem> WidgetFromLayerItem(const TSharedPtr<FDMMaterialLayerReference>& InItem) const;`
- L64 _protected prototype_ `bool CanSelectLayerStage(EDMMaterialLayerStage InStageType) const;` — Commands
- L66 _protected prototype_ `void ExecuteSelectLayerStage(EDMMaterialLayerStage InStageType);`
- L68 _protected prototype_ `bool CanMoveLayer(int32 InOffset) const;`
- L70 _protected prototype_ `void ExecuteMoveLayer(int32 InOffset);`
- L73 _protected prototype_ `void OnUndo();` — Events
- L75 _protected prototype_ `void OnLayersUpdated(UDMMaterialSlot* InSlot);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Editor/SlotEditor/SDMMaterialStage.h` (Private)


#### class `SDMMaterialStage`  
`class SDMMaterialStage : public SCompoundWidget`  
_L17-62_
- inherits: `SCompoundWidget`
- L19 _private function_ `SLATE_DECLARE_WIDGET(SDMMaterialStage, SCompoundWidget) SLATE_BEGIN_ARGS(SDMMaterialStage)`
- L27 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialSlotLayerItem>& InSlotLayerItem, UDMMaterialStage* InStage);`
- L29 _public prototype_ `TSharedPtr<SDMMaterialSlotLayerItem> GetSlotLayerView() const;`
- L31 _public prototype_ `UDMMaterialStage* GetStage() const;`
- L34 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L35 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L39 _protected member_ `TWeakPtr<SDMMaterialSlotLayerItem> SlotLayerItemWeak;`
- L40 _protected member_ `TWeakObjectPtr<UDMMaterialStage> StageWeak;`
- L41 _protected member_ `TSharedPtr<SDMMaterialComponentPreview> PreviewImage;`
- L42 _protected member_ `TSharedPtr<SDMMaterialComponentPreview> ToolTipImage;`
- L44 _protected prototype_ `bool IsStageSelected() const;`
- L46 _protected prototype_ `const FSlateBrush* GetBorderBrush() const;`
- L48 _protected prototype_ `EVisibility GetDisabledOverlayVisibility() const;`
- L50 _protected prototype_ `void OnSettingsUpdated(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L53 _protected prototype_ `bool OnAssetDraggedOver(TArrayView<FAssetData> InAssets);` — Drag and drop.
- L55 _protected prototype_ `void OnAssetsDropped(const FDragDropEvent& InDragDropEvent, TArrayView<FAssetData> InAssets);`
- L57 _protected prototype_ `void HandleDrop_Texture(UTexture* InTexture);`
- L59 _protected prototype_ `void OnMouseButtonDown_Left();`
- L61 _protected prototype_ `void OnMouseButtonUp_Right();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/SDMActorMaterialSelector.h` (Private)


#### class `SDMActorMaterialSelector`  
`class SDMActorMaterialSelector : public SCompoundWidget`  
_L15-42_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_DECLARE_WIDGET(SDMActorMaterialSelector, SCompoundWidget) SLATE_BEGIN_ARGS(SDMActorMaterialSelector)`
- L23 _public prototype_ `virtual ~SDMActorMaterialSelector() override = default;`
- L25 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialDesigner>& InDesignerWidget, AActor* InActor, TArray<FDMObjectMaterialProperty>&& InActorProperties);`
- L28 _public prototype_ `TSharedPtr<SDMMaterialDesigner> GetDesignerWidget() const;`
- L31 _protected member_ `TWeakPtr<SDMMaterialDesigner> DesignerWidgetWeak;`
- L32 _protected member_ `TWeakObjectPtr<AActor> ActorWeak;`
- L33 _protected member_ `TArray<FDMObjectMaterialProperty> ActorProperties;`
- L35 _protected prototype_ `TSharedRef<SWidget> CreateSelectorLayout();`
- L37 _protected prototype_ `TSharedRef<SWidget> CreateNoPropertiesLayout();`
- L39 _protected prototype_ `TSharedRef<SWidget> CreateActorMaterialPropertyEntry(int32 InActorPropertyIndex, UPrimitiveComponent* InPrimitiveComponent = nullptr);`
- L41 _protected prototype_ `FReply OnCreateMaterialButtonClicked(int32 InActorPropertyIndex);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/SDMMaterialDesigner.h` (Private)


#### class `SDMMaterialDesigner`  
`class SDMMaterialDesigner : public SCompoundWidget`  
_L21-114_
- inherits: `SCompoundWidget`
- L23 _private function_ `SLATE_DECLARE_WIDGET(SDMMaterialDesigner, SCompoundWidget) SLATE_BEGIN_ARGS(SDMMaterialDesigner)`
- L29 _public prototype_ `static bool IsFollowingSelection();`
- L33 _public prototype_ `void Construct(const FArguments& InArgs);`
- L36 _public prototype_ `bool OpenMaterialModelBase(UDynamicMaterialModelBase* InMaterialModelBase);` — Open specific types of objects.
- L38 _public prototype_ `bool OpenMaterialInstance(UDynamicMaterialInstance* InMaterialInstance);`
- L40 _public prototype_ `bool OpenObjectMaterialProperty(const FDMObjectMaterialProperty& InObjectMaterialProperty);`
- L42 _public prototype_ `bool OpenActor(AActor* InActor);`
- L45 _public prototype_ `void ShowSelectPrompt();` — Displays a "select something" message.
- L48 _public prototype_ `void Empty();` — Displays nothing.
- L51 _public prototype_ `void OnMaterialModelBaseSelected(UDynamicMaterialModelBase* InMaterialModelBase);` — Events based on editor selection.
- L53 _public prototype_ `void OnMaterialInstanceSelected(UDynamicMaterialInstance* InMaterialInstance);`
- L55 _public prototype_ `void OnObjectMaterialPropertySelected(const FDMObjectMaterialProperty& InObjectMaterialProperty);`
- L57 _public prototype_ `void OnActorSelected(AActor* InActor);`
- L60 _public prototype_ `UDynamicMaterialModelBase* GetOriginalMaterialModelBase() const;` — Getters
- L63 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L67 _protected member_ `TDMWidgetSlot<SWidget> ContentSlot;`
- L68 _protected member_ `TSharedPtr<SWidget> Content;`
- L71 _protected prototype_ `void OpenMaterialModelBase_Internal(UDynamicMaterialModelBase* InMaterialModelBase);` — Opens assets in specific widget modes.
- L73 _protected prototype_ `void OpenObjectMaterialProperty_Internal(const FDMObjectMaterialProperty& InObjectMaterialProperty);`
- L75 _protected prototype_ `void OpenActor_Internal(AActor* InActor);`
- L78 _protected prototype_ `void SetEmptyView();` — Widget modes.
- L80 _protected prototype_ `void SetSelectPromptView();`
- L82 _protected prototype_ `void SetMaterialSelectorView(AActor* InActor, TArray<FDMObjectMaterialProperty>&& InActorProperties);`
- L84 _protected prototype_ `void SetWizardView(UDynamicMaterialModel* InMaterialModel);`
- L86 _protected prototype_ `void SetWizardView(const FDMObjectMaterialProperty& InObjectMaterialProperty);`
- L88 _protected prototype_ `void SetEditorView(UDynamicMaterialModelBase* InMaterialModelBase);`
- L90 _protected prototype_ `void SetEditorView(const FDMObjectMaterialProperty& InObjectMaterialProperty);`
- L93 _protected prototype_ `void SetWidget(const TSharedRef<SWidget>& InWidget, bool bInIncludeAssetDropTarget);` — Utility methods.
- L95 _protected prototype_ `bool NeedsWizard(UDynamicMaterialModelBase* InMaterialModelBase) const;`
- L97 _protected prototype_ `bool ShouldFollowSelection() const;`
- L100 _protected prototype_ `bool OnAssetDraggedOver(TArrayView<FAssetData> InAssets);` — Drag and drop.
- L102 _protected prototype_ `void OnAssetsDropped(const FDragDropEvent& InDragDropEvent, TArrayView<FAssetData> InAssets);`
- L105 _protected prototype_ `void OnSettingsChanged(const FPropertyChangedEvent& InPropertyChangedEvent);` — Events
- L107 _protected prototype_ `void OnLayoutChanged();`
- L109 _protected prototype_ `bool SetEditorLayout(EDMMaterialEditorLayout InLayout, UDynamicMaterialModelBase* InMaterialModelBase, UDynamicMaterialModelBase* InCurrentPreviewMaterial);`
- L112 _protected prototype_ `bool SetEditorLayout(EDMMaterialEditorLayout InLayout, const FDMObjectMaterialProperty& InObjectMaterialProperty, UDynamicMaterialModelBase* InCurrentPreviewMaterial);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/SDMMaterialEditor.h` (Private)


#### class `SDMMaterialEditor`  
`class SDMMaterialEditor : public SCompoundWidget, public FSelfRegisteringEditorUndoClient, public FGCObject`  
_L54-301_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient,FGCObject`
- L56 _private function_ `SLATE_DECLARE_WIDGET(SDMMaterialEditor, SCompoundWidget) SLATE_BEGIN_ARGS(SDMMaterialEditor) : _MaterialModelBase(nullptr) , _MaterialProperty(TOptional<FDMObjectMaterialProperty>()) , _PreviewMaterialModelBase(nullptr)`
- L69 _public prototype_ `static UPackage* GetSaveablePackage(UObject* InObject);`
- L71 _public prototype_ `SDMMaterialEditor();`
- L75 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialDesigner>& InDesignerWidget);`
- L77 _public prototype_ `TSharedPtr<SDMMaterialDesigner> GetDesignerWidget() const;`
- L80 _public prototype_ `UDynamicMaterialModelBase* GetOriginalMaterialModelBase() const;` — Material Model / Actor
- L82 _public prototype_ `UDynamicMaterialModelBase* GetPreviewMaterialModelBase() const;`
- L84 _public prototype_ `UDynamicMaterialModel* GetPreviewMaterialModel() const;`
- L86 _public prototype_ `bool IsDynamicModel() const;`
- L88 _public prototype_ `const FDMObjectMaterialProperty* GetMaterialObjectProperty() const;`
- L90 _public prototype_ `AActor* GetMaterialActor() const;`
- L92 _public prototype_ `UDMMaterialComponent* GetOriginalComponent(UDMMaterialComponent* InPreviewComponent) const;`
- L95 _public prototype_ `EDMMaterialEditorMode GetEditMode() const;` — Widget Components
- L97 _public prototype_ `EDMMaterialPropertyType GetSelectedPropertyType() const;`
- L99 _public prototype_ `const TSharedRef<FUICommandList>& GetCommandList() const;`
- L101 _public prototype_ `TSharedRef<FDMPreviewMaterialManager> GetPreviewMaterialManager() const;`
- L103 _public prototype_ `TSharedPtr<SDMMaterialSlotEditor> GetSlotEditorWidget() const;`
- L105 _public prototype_ `TSharedPtr<SDMMaterialComponentEditor> GetComponentEditorWidget() const;`
- L107 _public prototype_ `UDMMaterialSlot* SlotSelectedSlot() const;`
- L109 _public prototype_ `UDMMaterialComponent* GetSelectedComponent() const;`
- L112 _public prototype_ `void SelectProperty(EDMMaterialPropertyType InProperty, bool bInForceRefresh = false);` — Actions
- L114 _public prototype_ `void EditSlot(UDMMaterialSlot* InSlot, bool bInForceRefresh = false);`
- L116 _public prototype_ `void EditComponent(UDMMaterialComponent* InComponent, bool bInForceRefresh = false);`
- L118 _public prototype_ `void EditGlobalSettings(bool bInForceRefresh = false);`
- L120 _public prototype_ `void EditProperties(bool bInForceRefresh = false);`
- L122 _public prototype_ `void OnLayerSelected(const TSharedRef<SDMMaterialSlotLayerView>& InSlotView, const TSharedPtr<FDMMaterialLayerReference>& InLayerView);`
- L124 _public prototype_ `void OnStageSelected(const TSharedRef<SDMMaterialSlotLayerItem>& InLayerItem, UDMMaterialStage* InStage);`
- L126 _public prototype_ `void OnEffectSelected(const TSharedRef<SDMMaterialSlotLayerEffectView>& InEffectView, UDMMaterialEffect* InEffect);`
- L128 _public prototype_ `void OpenMaterialPreviewTab();`
- L130 _public prototype_ `void CloseMaterialPreviewTab();`
- L132 _public prototype_ `TSharedPtr<IToolTip> GetMaterialPreviewToolTip();`
- L134 _public prototype_ `void DestroyMaterialPreviewToolTip();`
- L136 _public prototype_ `void Validate();`
- L138 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEditedSlotChanged, const TSharedRef<SDMMaterialSlotEditor>&, UDMMaterialSlot*);`
- L139 _public prototype_ `FOnEditedSlotChanged::RegistrationType& GetOnEditedSlotChanged();`
- L141 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEditedComponentChanged, const TSharedRef<SDMMaterialComponentEditor>&, UDMMaterialComponent*);`
- L142 _public prototype_ `FOnEditedComponentChanged::RegistrationType& GetOnEditedComponentChanged();`
- L144 _public prototype_ `bool PageHistoryBack();`
- L146 _public prototype_ `bool PageHistoryForward();`
- L148 _public prototype_ `bool SetActivePage(const FDMMaterialEditorPage& InPage);`
- L150 _public prototype_ `void SaveOriginal();`
- L152 _public prototype_ `void ApplyToOriginal();`
- L154 _public prototype_ `void Compile();`
- L156 _public prototype_ `void HandleDrop_CreateTextureSet(const TArray<FAssetData>& InTextureAssets);`
- L158 _public prototype_ `void HandleDrop_TextureSet(UDMTextureSet* InTextureSet);`
- L161 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L162 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& InMyGeometry, const FKeyEvent& InKeyEvent) override;`
- L163 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L167 _public prototype_ `virtual void PostUndo(bool bInSuccess) override;`
- L168 _public prototype_ `virtual void PostRedo(bool bInSuccess) override;`
- L172 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L173 _public prototype_ `virtual FString GetReferencerName() const override;`
- L177 _protected member_ `TWeakPtr<SDMMaterialDesigner> DesignerWidgetWeak;`
- L179 _protected member_ `TDMWidgetSlot<SWidget> ContentSlot;`
- L180 _protected member_ `TDMWidgetSlot<SDMToolBar> ToolBarSlot;`
- L181 _protected member_ `TDMWidgetSlot<SWidget> MainSlot;`
- L182 _protected member_ `TDMWidgetSlot<SWidget> MaterialPreviewSlot;`
- L183 _protected member_ `TDMWidgetSlot<SDMMaterialPropertySelector> PropertySelectorSlot;`
- L184 _protected member_ `TDMWidgetSlot<SDMMaterialGlobalSettingsEditor> GlobalSettingsEditorSlot;`
- L185 _protected member_ `TDMWidgetSlot<SDMMaterialProperties> MaterialPropertiesSlot;`
- L186 _protected member_ `FSlotBase* SplitterSlot;`
- L187 _protected member_ `TDMWidgetSlot<SDMMaterialSlotEditor> SlotEditorSlot;`
- L188 _protected member_ `TDMWidgetSlot<SDMMaterialComponentEditor> ComponentEditorSlot;`
- L189 _protected member_ `TDMWidgetSlot<SDMStatusBar> StatusBarSlot;`
- L191 _protected member_ `TWeakObjectPtr<UDynamicMaterialModelBase> OriginalMaterialModelBaseWeak;`
- L192 _protected member_ `TObjectPtr<UDynamicMaterialInstance> PreviewMaterialInstance;`
- L193 _protected member_ `TObjectPtr<UDynamicMaterialModelBase> PreviewMaterialModelBase;`
- L194 _protected member_ `TOptional<FDMObjectMaterialProperty> ObjectMaterialPropertyOpt;`
- L196 _protected member_ `TSharedRef<FUICommandList> CommandList;`
- L197 _protected member_ `TSharedPtr<FDMKeyTracker> KeyTracker_V;`
- L198 _protected member_ `TSharedRef<FDMPreviewMaterialManager> PreviewMaterialManager;`
- L199 _protected member_ `TSharedPtr<SDockTab> MaterialPreviewTab;`
- L200 _protected member_ `TDMWidgetSlot<SWidget> MaterialPreviewTabSlot;`
- L201 _protected member_ `TSharedPtr<IToolTip> MaterialPreviewToolTip;`
- L202 _protected member_ `TDMWidgetSlot<SWidget> MaterialPreviewToolTipSlot;`
- L204 _protected member_ `FDMEditorSelectionContext SelectionContext;`
- L206 _protected member_ `FOnEditedSlotChanged OnEditedSlotChanged;`
- L207 _protected member_ `FOnEditedComponentChanged OnEditedComponentChanged;`
- L209 _protected member_ `TWeakObjectPtr<UDynamicMaterialModelEditorOnlyData> EditorOnlyDataUpdateObject;`
- L211 _protected member_ `bool bSkipApplyOnCompile;`
- L214 _protected prototype_ `void SetMaterialModelBase(UDynamicMaterialModelBase* InMaterialModelBase, UDynamicMaterialModelBase* InPreviewMaterialModelBase);` — Operations
- L216 _protected prototype_ `void SetObjectMaterialProperty(const FDMObjectMaterialProperty& InObjectProperty, UDynamicMaterialModelBase* InPreviewMaterialModelBase);`
- L218 _protected prototype_ `void SetMaterialActor(AActor* InActor);`
- L220 _protected prototype_ `void BindCommands(SDMMaterialSlotEditor* InSlotEditor);`
- L222 _protected prototype_ `bool IsPropertyValidForModel(EDMMaterialPropertyType InProperty) const;`
- L224 _protected prototype_ `void Close();`
- L226 _protected prototype_ `void ValidateSlots();`
- L228 _protected prototype_ `virtual void ValidateSlots_Main() = 0;`
- L230 _protected prototype_ `void ClearSlots();`
- L232 _protected prototype_ `virtual void ClearSlots_Main() = 0;`
- L234 _protected prototype_ `void PageHistoryAdd(const FDMMaterialEditorPage& InPage);`
- L237 _protected prototype_ `void CreateLayout();` — Slots
- L239 _protected prototype_ `TSharedRef<SWidget> CreateSlot_Container();`
- L241 _protected prototype_ `TSharedRef<SDMToolBar> CreateSlot_ToolBar();`
- L243 _protected prototype_ `virtual TSharedRef<SWidget> CreateSlot_Main() = 0;`
- L245 _protected prototype_ `TSharedRef<SDMMaterialGlobalSettingsEditor> CreateSlot_GlobalSettingsEditor();`
- L247 _protected prototype_ `TSharedRef<SDMMaterialProperties> CreateSlot_MaterialProperties();`
- L249 _protected prototype_ `TSharedRef<SWidget> CreateSlot_Preview();`
- L251 _protected prototype_ `TSharedRef<SDMMaterialPropertySelector> CreateSlot_PropertySelector();`
- L253 _protected prototype_ `virtual TSharedRef<SDMMaterialPropertySelector> CreateSlot_PropertySelector_Impl() = 0;`
- L255 _protected prototype_ `TSharedRef<SDMMaterialSlotEditor> CreateSlot_SlotEditor();`
- L257 _protected prototype_ `TSharedRef<SDMMaterialComponentEditor> CreateSlot_ComponentEditor();`
- L259 _protected prototype_ `TSharedRef<SDMStatusBar> CreateSlot_StatusBar();`
- L262 _protected prototype_ `void OnUndo();` — Events
- L264 _protected prototype_ `void ApplySelectionContext();`
- L267 _protected prototype_ `void OnEnginePreExit();` — The material preview window is not cleaned up properly on uobject shutdown, so do it here.
- L269 _protected prototype_ `void OnEditorSplitterResized();`
- L271 _protected prototype_ `void BindEditorOnlyDataUpdate(UDynamicMaterialModelBase* InMaterialModelBase);`
- L273 _protected prototype_ `void UnbindEditorOnlyDataUpdate();`
- L275 _protected prototype_ `void OnMaterialBuilt(UDynamicMaterialModelBase* InMaterialModelBase);`
- L277 _protected prototype_ `void OnPropertyUpdate(UDynamicMaterialModelBase* InMaterialModelBase);`
- L279 _protected prototype_ `void OnSlotListUpdate(UDynamicMaterialModelBase* InMaterialModelBase);`
- L281 _protected prototype_ `void OnSettingsChanged(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L283 _protected prototype_ `void NavigateForward_Execute();`
- L284 _protected prototype_ `bool NavigateForward_CanExecute();`
- L286 _protected prototype_ `void NavigateBack_Execute();`
- L287 _protected prototype_ `bool NavigateBack_CanExecute();`
- L289 _protected prototype_ `bool CheckOpacityInput(const FKeyEvent& InKeyEvent);`
- L292 _protected prototype_ `void SelectProperty_Impl(EDMMaterialPropertyType InProperty);` — Actions
- L294 _protected prototype_ `virtual void EditSlot_Impl(UDMMaterialSlot* InSlot);`
- L296 _protected prototype_ `virtual void EditComponent_Impl(UDMMaterialComponent* InComponent);`
- L298 _protected prototype_ `virtual void EditGlobalSettings_Impl();`
- L300 _protected prototype_ `virtual void EditProperties_Impl();`

#### Free symbols / members of external scopes

- L48 _namespace_ `namespace UE`
- L48 _namespace_ `namespace DynamicMaterialEditor` (scope `UE`)
- L48 _namespace_ `namespace Private` (scope `UE::DynamicMaterialEditor`)
- L50 _variable_ `inline const TCHAR* EditorDarkBackground = TEXT("Bru` (scope `UE::DynamicMaterialEditor::Private`)
- L51 _variable_ `inline const TCHAR* EditorLightBackground = TEXT("Bru` (scope `UE::DynamicMaterialEditor::Private`)
- L138 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEditedSlotChanged, const TSharedRef<SDMMaterialSlotEditor>&, UDMMaterialSlot*);`
- L141 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEditedComponentChanged, const TSharedRef<SDMMaterialComponentEditor>&, UDMMaterialComponent*);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/SDMMaterialSelectPrompt.h` (Private)


#### class `SDMMaterialSelectPrompt`  
`class SDMMaterialSelectPrompt : public SCompoundWidget`  
_L7-18_
- inherits: `SCompoundWidget`
- L9 _private function_ `SLATE_DECLARE_WIDGET(SDMMaterialSelectPrompt, SCompoundWidget) SLATE_BEGIN_ARGS(SDMMaterialSelectPrompt)`
- L15 _public prototype_ `virtual ~SDMMaterialSelectPrompt() override = default;`
- L17 _public prototype_ `void Construct(const FArguments& InArgs);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/SDMMaterialWizard.h` (Private)


#### class `SDMMaterialWizard`  
`class SDMMaterialWizard : public SCompoundWidget`  
_L29-125_
- inherits: `SCompoundWidget`
- L32 _public function_ `SLATE_DECLARE_WIDGET(SDMMaterialWizard, SCompoundWidget) SLATE_BEGIN_ARGS(SDMMaterialWizard) : _MaterialModel(nullptr) , _MaterialProperty(TOptional<FDMObjectMaterialProperty>())`
- L38 _public prototype_ `SLATE_ARGUMENT(UDynamicMaterialModel*, MaterialModel) SLATE_ARGUMENT(TOptional<FDMObjectMaterialProperty>, MaterialProperty) SLATE_END_ARGS() virtual ~SDMMaterialWizard() override;`
- L44 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialDesigner>& InDesignerWidget);`
- L46 _public prototype_ `TSharedPtr<SDMMaterialDesigner> GetDesignerWidget() const;`
- L48 _public prototype_ `UDynamicMaterialModel* GetMaterialModel() const;`
- L50 _public prototype_ `void HandleDrop_CreateTextureSet(const TArray<FAssetData>& InTextureAssets);`
- L52 _public prototype_ `void HandleDrop_TextureSet(UDMTextureSet* InTextureSet);`
- L63 _protected member_ `TWeakPtr<SDMMaterialDesigner> DesignerWidgetWeak;`
- L64 _protected member_ `FName CurrentPreset;`
- L65 _protected member_ `TSharedPtr<SBox> PresetChannelContainer;`
- L66 _protected member_ `TWeakObjectPtr<UDynamicMaterialModel> MaterialModelWeak;`
- L67 _protected member_ `TOptional<FDMObjectMaterialProperty> MaterialObjectProperty;`
- L68 _protected member_ `TSharedPtr<SWidgetSwitcher> Switcher;`
- L69 _protected member_ `TSharedPtr<SAssetView> AssetView;`
- L70 _protected member_ `TSharedPtr<SAssetSearchBox> AssetSearchBox;`
- L71 _protected member_ `TSharedPtr<FAssetTextFilter> TextFilter;`
- L74 _protected prototype_ `TSharedRef<SWidget> CreateLayout();` — Creation of widgets.
- L75 _protected prototype_ `TSharedRef<SWidget> CreateModeSelector();`
- L76 _protected prototype_ `TSharedRef<SWidget> CreateNewTemplateLayout();`
- L77 _protected prototype_ `TSharedRef<SWidget> CreateNewTemplate_ChannelPresets();`
- L78 _protected prototype_ `TSharedRef<SWidget> CreateNewTemplate_ChannelList();`
- L79 _protected prototype_ `TSharedRef<SWidget> CreateNewTemplate_AcceptButton();`
- L80 _protected prototype_ `TSharedRef<SWidget> CreateNewInstanceLayout();`
- L81 _protected prototype_ `TSharedRef<SWidget> CreateNewInstance_SearchBox();`
- L82 _protected prototype_ `TSharedRef<SWidget> CreateNewInstance_Picker();`
- L83 _protected prototype_ `TSharedRef<SWidget> CreateNewInstance_AcceptButton();`
- L86 _protected prototype_ `ECheckBoxState Preset_GetState(FName InPresetName) const;` — Attributes and Events
- L87 _protected prototype_ `void Preset_OnChange(ECheckBoxState InState, FName InPresetName);`
- L89 _protected prototype_ `FReply NewTemplateAccept_OnClick();`
- L91 _protected prototype_ `void OnMaterialBuilt(UDynamicMaterialModelBase* InMaterialModel);`
- L93 _protected prototype_ `void OpenMaterialInEditor();`
- L95 _protected prototype_ `ECheckBoxState IsModeSelected(EDMMaterialWizardMode InMode) const;`
- L97 _protected prototype_ `void SetMode(ECheckBoxState InState, EDMMaterialWizardMode InMode);`
- L99 _protected prototype_ `void OnSearchBoxChanged(const FText& InSearchText);`
- L100 _protected prototype_ `void OnSearchBoxCommitted(const FText& InSearchText, ETextCommit::Type InCommitInfo);`
- L102 _protected prototype_ `FText GetSearchText() const;`
- L103 _protected prototype_ `void SetSearchText(const FText& InSearchText);`
- L105 _protected prototype_ `bool ShouldFilterOutAsset(const FAssetData& InAsset) const;`
- L107 _protected prototype_ `bool NewInstance_CanAccept() const;`
- L109 _protected prototype_ `void OnAssetsActivated(TArrayView<const FContentBrowserItem> InSelectedItems, EAssetTypeActivationMethod::Type InActivationMethod);`
- L111 _protected prototype_ `FReply NewInstanceAccept_OnClick();`
- L113 _protected prototype_ `void OnEnginePreExit();`
- L116 _protected prototype_ `void SelectTemplate(UDynamicMaterialModel* InTemplateModel);` — Operations
- L118 _protected prototype_ `void CreateDynamicMaterialInInstance(UDynamicMaterialModel* InTemplateModel, UDynamicMaterialInstance* InToInstance);`
- L120 _protected prototype_ `void CreateNewDynamicInstanceInActor(UDynamicMaterialModel* InFromModel, FDMObjectMaterialProperty& InMaterialObjectProperty);`
- L122 _protected prototype_ `void SetChannelListInModel(FName InChannelList, UDynamicMaterialModel* InMaterialModel);`
- L124 _protected prototype_ `void CreateTemplateMaterialInActor(FName InChannelList, FDMObjectMaterialProperty& InMaterialObjectProperty);`

#### enum `SDMMaterialWizard::EDMMaterialWizardMode`  
`enum EDMMaterialWizardMode : uint8`  
_L55-61_
- L57 _public enumerator_ `Template = 0`
- L58 _public enumerator_ `Instance = 1`
- L60 _public enumerator_ `Count = 2`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Visualizers/SDMMaterialComponentPreview.h` (Private)


#### class `SDMMaterialComponentPreview`  
`class SDMMaterialComponentPreview : public SCompoundWidget`  
_L22-69_
- inherits: `SCompoundWidget`
- L25 _public function_ `SLATE_BEGIN_ARGS(SDMMaterialComponentPreview) : _PreviewSize(FVector2D(48.f, 48.f))`
- L28 _public prototype_ `SLATE_ARGUMENT(FVector2D, PreviewSize) SLATE_END_ARGS() SDMMaterialComponentPreview();`
- L35 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor>& InEditorWidget, UDMMaterialComponent* InComponent);`
- L37 _public prototype_ `FSlateMaterialBrush& GetBrush();`
- L39 _public prototype_ `const FVector2D& GetPreviewSize() const;`
- L41 _public prototype_ `void SetPreviewSize(const FVector2D& InSize);`
- L43 _public prototype_ `UDMMaterialComponent* GetComponent() const;`
- L45 _public prototype_ `UMaterial* GetPreviewMaterial() const;`
- L47 _public prototype_ `UMaterialInstanceDynamic* GetPreviewMaterialDynamic() const;`
- L50 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L54 _protected member_ `TWeakPtr<SDMMaterialEditor> EditorWidgetWeak;`
- L55 _protected member_ `TWeakObjectPtr<UDMMaterialComponent> ComponentWeak;`
- L56 _protected member_ `TWeakObjectPtr<UDynamicMaterialModelBase> MaterialModelBaseWeak;`
- L57 _protected member_ `TWeakObjectPtr<UMaterial> PreviewMaterialBaseWeak;`
- L58 _protected member_ `TWeakObjectPtr<UMaterialInstanceDynamic> PreviewMaterialDynamicWeak;`
- L59 _protected member_ `FSlateMaterialBrush Brush;`
- L60 _protected member_ `FDelegateHandle EndOfFrameDelegateHandle;`
- L61 _protected member_ `TSharedPtr<SImage> PreviewImage;`
- L62 _protected member_ `FVector2D PreviewSize;`
- L64 _protected prototype_ `void OnComponentUpdated(UDMMaterialComponent* InComponent, UDMMaterialComponent* InSource, EDMUpdateType InUpdateType);`
- L66 _protected prototype_ `void OnEndOfFrame();`
- L68 _protected prototype_ `void RecreateMaterial();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Visualizers/SDMTextureUVVisualizer.h` (Private)


#### class `SDMTextureUVVisualizer`  
`class SDMTextureUVVisualizer : public SCompoundWidget`  
_L26-156_
- inherits: `SCompoundWidget`
- desc: Material Designer Texture UV Visualizer Ability to edit Texture UV settings in a visual manner.
- L46 _public function_ `SLATE_BEGIN_ARGS(SDMTextureUVVisualizer) : _TextureUV(nullptr) , _TextureUVDynamic(nullptr) , _IsPopout(false)`
- L51 _public prototype_ `SLATE_ARGUMENT(UDMTextureUV*, TextureUV) SLATE_ARGUMENT(UDMTextureUVDynamic*, TextureUVDynamic) SLATE_ARGUMENT(bool, IsPopout) SLATE_END_ARGS() SDMTextureUVVisualizer();`
- L59 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor>& InEditorWidget, UDMMaterialStage* InMaterialStage);` — The TextureUV should be a sub-property of the stage
- L61 _public function_ `TSharedPtr<SDMMaterialEditor> GetEditorWidget() const`
- L63 _public prototype_ `EScrubbingMode GetScrubbingMode() const;`
- L65 _public prototype_ `bool IsInPivotEditMode() const;`
- L67 _public prototype_ `void SetInPivotEditMode(bool bInEditingPivot);`
- L69 _public prototype_ `void TogglePivotEditMode();`
- L71 _public prototype_ `UDMMaterialStage* GetStage() const;`
- L73 _public prototype_ `UDMMaterialComponent* GetTextureUVComponent() const;`
- L75 _public prototype_ `UDMTextureUV* GetTextureUV() const;`
- L77 _public prototype_ `UDMTextureUVDynamic* GetTextureUVDynamic() const;`
- L79 _public prototype_ `const FVector2D& GetOffset() const;`
- L80 _public prototype_ `bool SetOffset(const FVector2D& InOffset);`
- L82 _public prototype_ `float GetRotation() const;`
- L83 _public prototype_ `bool SetRotation(float InRotation);`
- L85 _public prototype_ `const FVector2D& GetTiling() const;`
- L86 _public prototype_ `bool SetTiling(const FVector2D& InTiling);`
- L88 _public prototype_ `const FVector2D& GetPivot() const;`
- L89 _public prototype_ `bool SetPivot(const FVector2D& InPivot);`
- L92 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L93 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L94 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& InGeometry, const FPointerEvent& InCursorEvent) const override;`
- L95 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;`
- L100 _protected member_ `TWeakPtr<SDMMaterialEditor> EditorWidgetWeak;`
- L101 _protected member_ `TWeakObjectPtr<UDMMaterialStage> StageWeak;`
- L102 _protected member_ `TWeakObjectPtr<UDMMaterialComponent> TextureUVComponentWeak;`
- L103 _protected member_ `TSharedPtr<SDMMaterialComponentPreview> StagePreview;`
- L104 _protected member_ `bool bIsPopout;`
- L105 _protected member_ `bool bPivotEditMode;`
- L106 _protected member_ `FVector2f CurrentAbsoluteSize;`
- L107 _protected member_ `FVector2f CurrentAbsoluteCenter;`
- L108 _protected member_ `EScrubbingMode ScrubbingMode;`
- L109 _protected member_ `FVector2f ScrubbingStartAbsoluteCenter;`
- L110 _protected member_ `FVector2f ScrubbingStartAbsoluteMouse;`
- L111 _protected member_ `EHandleAxis HandleAxis;`
- L112 _protected member_ `FVector2D ValueStart;`
- L113 _protected member_ `bool bInvertTiling;`
- L114 _protected member_ `TSharedPtr<FScopedTransaction> ScrubbingTransaction;`
- L116 _protected prototype_ `bool HasValidGeometry() const;`
- L118 _protected prototype_ `float GetCircleHandleBaseRadius() const;`
- L120 _protected prototype_ `FVector2f ApplyTextureUVTransform(const FVector2f& InUV) const;`
- L122 _protected prototype_ `FVector2f GetOffsetLocation(const FVector2f& InSize) const;`
- L124 _protected prototype_ `FVector2f GetPivotLocation(const FVector2f& InSize) const;`
- L126 _protected prototype_ `FVector2f GetAbsoluteOffsetLocation() const;`
- L128 _protected prototype_ `FVector2f GetAbsolutePivotLocation() const;`
- L131 _protected prototype_ `float GetCircleHandleRadiusAtAngle(float InAngle) const;` — Degrees clockwise from +Y axis
- L133 _protected prototype_ `EHandleAxis GetCenterHandleAxis(const FVector2f& InAbsolutePosition) const;`
- L135 _protected prototype_ `EHandleAxis GetCircleHandleAxis(const FVector2f& InAbsolutePosition) const;`
- L137 _protected prototype_ `bool TryClickCenterHandle(const FVector2f& InMousePosition, bool bInResetToDefault);`
- L139 _protected prototype_ `bool TryClickCircleHandle(const FVector2f& InMousePosition, bool bInResetToDefault);`
- L141 _protected prototype_ `void UpdatePopoutUVs();`
- L143 _protected prototype_ `void SetScrubbingMode(EScrubbingMode InMode, EHandleAxis InAxis);`
- L145 _protected prototype_ `FVector2f ToPopoutLocation(const FVector2f& InSize, FVector2f&& InLocation) const;`
- L147 _protected prototype_ `FVector2f FromPopoutLocation(const FVector2f& InSize, FVector2f&& InLocation) const;`
- L149 _protected prototype_ `void ModifyTextureUVComponent();`
- L151 _protected prototype_ `void UpdateScrub();`
- L152 _protected prototype_ `void UpdateScrub_Offset();`
- L153 _protected prototype_ `void UpdateScrub_Rotation();`
- L154 _protected prototype_ `void UpdateScrub_Tiling();`
- L155 _protected prototype_ `void UpdateScrub_Pivot();`

#### enum `SDMTextureUVVisualizer::EScrubbingMode`  
`enum class EScrubbingMode : uint8`  
_L29-36_
- L31 _public enumerator_ `None`
- L32 _public enumerator_ `Offset`
- L33 _public enumerator_ `Rotation`
- L34 _public enumerator_ `Tiling`
- L35 _public enumerator_ `Pivot`

#### enum `SDMTextureUVVisualizer::EHandleAxis`  
`enum class EHandleAxis : uint8`  
_L38-44_
- L40 _public enumerator_ `None`
- L41 _public enumerator_ `X`
- L42 _public enumerator_ `Y`
- L43 _public enumerator_ `XY`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Visualizers/SDMTextureUVVisualizerPopout.h` (Private)


#### class `SDMTextureUVVisualizerPopout`  
`class SDMTextureUVVisualizerPopout : public SCompoundWidget, public FNotifyHook`  
_L28-67_
- inherits: `SCompoundWidget,FNotifyHook`
- desc: Material Designer Texture UV Visualizer Popout Houses a Texture UV editor and a few buttons to control it. The popout specifically expands the visible area of the preview to 3x the normal size on the smallest axis. The other axis is expanded to match the aspect ratio.
- L31 _public member_ `static const FName TabId;`
- L33 _public prototype_ `static void CreatePopout(const TSharedRef<SDMMaterialEditor>& InEditorWidget, UDMMaterialStage* InMaterialStage, UDMTextureUV* InTextureUV);`
- L35 _public prototype_ `static void CreatePopout(const TSharedRef<SDMMaterialEditor>& InEditorWidget, UDMMaterialStage* InMaterialStage, UDMTextureUVDynamic* InTextureUVDynamic);`
- L37 _public function_ `SLATE_BEGIN_ARGS(SDMTextureUVVisualizerPopout) : _TextureUV(nullptr) , _TextureUVDynamic(nullptr)`
- L41 _public prototype_ `SLATE_ARGUMENT(UDMTextureUV*, TextureUV) SLATE_ARGUMENT(UDMTextureUVDynamic*, TextureUVDynamic) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor>& InEditorWidget, UDMMaterialStage* InMaterialStage);`
- L49 _public prototype_ `virtual void NotifyPreChange(FProperty* InPropertyAboutToChange) override;`
- L50 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L54 _protected member_ `TSharedPtr<SDMTextureUVVisualizer> Visualizer;`
- L56 _protected prototype_ `FText GetModeButtonText() const;`
- L58 _protected prototype_ `FVector2D GetHorizontalBarSize() const;`
- L60 _protected prototype_ `FVector2D GetSideBlockSize() const;`
- L62 _protected prototype_ `TSharedRef<SWidget> CreatePropertyWidget(const TSharedRef<SDMMaterialEditor>& InEditorWidget, UDMMaterialComponent* InComponent);`
- L64 _protected prototype_ `ECheckBoxState GetModeCheckBoxState(bool bInIsPivot) const;`
- L66 _protected prototype_ `void OnModeCheckBoxStateChanged(ECheckBoxState InState, bool bInIsPivot);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Widgets/Visualizers/SDMTextureUVVisualizerProperty.h` (Private)


#### class `SDMTextureUVVisualizerProperty`  
`class SDMTextureUVVisualizerProperty : public SCompoundWidget`  
_L20-48_
- inherits: `SCompoundWidget`
- desc: Material Designer Texture UV Visualizer Property Houses a Texture UV editor and a few buttons to control it.
- L23 _public function_ `SLATE_BEGIN_ARGS(SDMTextureUVVisualizerProperty) : _TextureUV(nullptr) , _TextureUVDynamic(nullptr)`
- L27 _public prototype_ `SLATE_ARGUMENT(UDMTextureUV*, TextureUV) SLATE_ARGUMENT(UDMTextureUVDynamic*, TextureUVDynamic) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SDMMaterialEditor>& InEditorWidget, UDMMaterialStage* InMaterialStage);`
- L35 _protected member_ `TSharedPtr<SDMTextureUVVisualizer> Visualizer;`
- L37 _protected prototype_ `FReply OnToggleVisualizerClicked();`
- L39 _protected prototype_ `FReply OnToggleModeClicked();`
- L41 _protected prototype_ `FReply OnOpenPopoutClicked();`
- L43 _protected prototype_ `EVisibility GetVisualizerVisibility() const;`
- L45 _protected prototype_ `ECheckBoxState GetModeCheckBoxState(bool bInIsPivot) const;`
- L47 _protected prototype_ `void OnModeCheckBoxStateChanged(ECheckBoxState InState, bool bInIsPivot);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Utils/DMBuildRequestSubsystem.h` (Private)


#### struct `FDMBuildRequestEntry`  
`struct FDMBuildRequestEntry`  
_L12-26_
- L14 _public member_ `FString AssetPath;`
- L15 _public member_ `bool bDirtyAssets;`
- L17 _public function_ `bool operator==(const FDMBuildRequestEntry& InOther) const`

#### class `UDMBuildRequestSubsystem`  
`class UDMBuildRequestSubsystem : public UEditorSubsystem, public FTickableEditorObject`  
_L29-58_
- reflection: `UCLASS()`
- inherits: `UEditorSubsystem,FTickableEditorObject`
- L34 _public prototype_ `static UDMBuildRequestSubsystem* Get();`
- L36 _public prototype_ `void AddBuildRequest(UObject* InToBuild, bool bInDirtyAssets);`
- L38 _public prototype_ `void RemoveBuildRequest(UObject* InToNotBuild);`
- L40 _public prototype_ `void RemoveBuildRequestForOuter(UObject* InOuter);`
- L43 _public prototype_ `virtual void Deinitialize() override;`
- L47 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L48 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L49 _public prototype_ `virtual TStatId GetStatId() const override;`
- L53 _protected member_ `TSet<FDMBuildRequestEntry> BuildRequestList;`
- L55 _protected prototype_ `void ProcessBuildRequestList();`
- L57 _protected prototype_ `void ProcessBuildRequest(UObject* InToBuild, bool bInDirtyAssets);`

#### Free symbols / members of external scopes

- L22 _function_ `friend uint32 GetTypeHash(const FDMBuildRequestEntry& InEntry)`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Utils/DMInputNodeBuilder.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DynamicMaterialEditor` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::DynamicMaterialEditor`)
- L15 _prototype_ `void BuildExpressionInputs(const TSharedRef<FDMMaterialBuildState>& InBuildState, const TArray<FDMMaterialStageConnection>& InputConnectionMap, const TArray<FDMInputInputs>& Inputs);` (scope `UE::DynamicMaterialEditor::Private`)
- L18 _prototype_ `void BuildExpressionOneInput(const TSharedRef<FDMMaterialBuildState>& InBuildState, const TArray<FDMMaterialStageConnection>& InputConnectionMap, const FDMInputInputs& InputOne);` (scope `UE::DynamicMaterialEditor::Private`)
- L21 _prototype_ `void BuildExpressionTwoInputs(const TSharedRef<FDMMaterialBuildState>& InBuildState, const TArray<FDMMaterialStageConnection>& InputConnectionMap, const FDMInputInputs& InputOne, const FDMInputInputs& InputTwo);` (scope `UE::DynamicMaterialEditor::Private`)
- L24 _prototype_ `void BuildExpressionThreeInputs(const TSharedRef<FDMMaterialBuildState>& InBuildState, const TArray<FDMMaterialStageConnection>& InputConnectionMap, const FDMInputInputs& InputOne, const FDMInputInputs& InputTwo, const FDMInputInputs& InputThree);` (scope `UE::DynamicMaterialEditor::Private`)

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Utils/DMMaterialFunctionLibrary.h` (Private)


#### class `FDMMaterialFunctionLibrary`  
`class FDMMaterialFunctionLibrary`  
_L11-35_
- L14 _public prototype_ `static FDMMaterialFunctionLibrary& Get();`
- L16 _public prototype_ `UMaterialFunctionInterface* GetFunction(const FName& Name, const FString& Path);`
- L18 _public prototype_ `UMaterialFunctionInterface* LoadFunction(const FString& Path);`
- L20 _public prototype_ `UMaterialExpressionMaterialFunctionCall* MakeExpression(UMaterial* Parent, UMaterialFunctionInterface* Function, const FString& InComment);`
- L21 _public prototype_ `UMaterialExpressionMaterialFunctionCall* MakeExpression(UMaterial* Parent, const FName& Name, const FString& Path, const FString& InComment);`
- L23 _public prototype_ `UMaterialExpressionMaterialFunctionCall* GetBreakOutFloat2Components(UMaterial* Parent, const FString& InComment);`
- L24 _public prototype_ `UMaterialExpressionMaterialFunctionCall* GetBreakOutFloat3Components(UMaterial* Parent, const FString& InComment);`
- L25 _public prototype_ `UMaterialExpressionMaterialFunctionCall* GetBreakOutFloat4Components(UMaterial* Parent, const FString& InComment);`
- L26 _public prototype_ `UMaterialExpressionMaterialFunctionCall* GetRGVtoHSV(UMaterial* Parent, const FString& InComment);`
- L27 _public prototype_ `UMaterialExpressionMaterialFunctionCall* GetMakeFloat2(UMaterial* Parent, const FString& InComment);`
- L28 _public prototype_ `UMaterialExpressionMaterialFunctionCall* GetMakeFloat3(UMaterial* Parent, const FString& InComment);`
- L29 _public prototype_ `UMaterialExpressionMaterialFunctionCall* GetMakeFloat4(UMaterial* Parent, const FString& InComment);`
- L30 _public prototype_ `UMaterialExpressionMaterialFunctionCall* GetCustomRotator(UMaterial* Parent, const FString& InComment);`
- L31 _public prototype_ `UMaterialExpressionMaterialFunctionCall* GetRadialGradientExponential(UMaterial* Parent, const FString& InComment);` — UMaterialExpressionMaterialFunctionCall* GetCustomRotator(UMaterial* Parent, const FString& InComment);   Possibly promote this to a full expression?
- L34 _protected member_ `TMap<FName, TStrongObjectPtr<UMaterialFunctionInterface>> LoadedFunctions;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Utils/DMMaterialSnapshotLibrary.h` (Private)


#### class `FDMMaterialShapshotLibrary`  
`class FDMMaterialShapshotLibrary`  
_L13-27_
- L16 _public prototype_ `static bool SnapshotMaterial(UMaterialInterface* InMaterial, const FIntPoint& InTextureSize, const FString& InSavePath);`
- L19 _private prototype_ `static void RenderMaterialToRenderTarget(UMaterialInterface* InMaterial, UTextureRenderTarget2D* InRenderTarget);`
- L21 _private prototype_ `static UTextureRenderTarget2D* CreateSnapshotRenderTarget(const FIntPoint& InTextureSize);`
- L23 _private prototype_ `static void ApplyAlphaOneMinusShader(FRHICommandListImmediate& InRHICmdList, FTextureRenderTargetResource* InSourceTextureResource, FTextureRenderTargetResource* InDestTargetResource);`
- L26 _private prototype_ `static UTextureRenderTarget2D* ApplyAlphaOneMinusShader(UTextureRenderTarget2D* InRenderTarget);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/Utils/DMPrivate.h` (Private)


#### struct `UE::DynamicMaterialEditor::Private::FDMInputInputs`  
`struct FDMInputInputs`  
_L22-26_
- L24 _public member_ `int32 InputIndex;`
- L25 _public member_ `TArray<UDMMaterialStageInput*> ChannelInputs;`

#### struct `FDMMaterialLayerReference`  
`struct FDMMaterialLayerReference`  
_L44-54_
- L46 _public member_ `TWeakObjectPtr<UDMMaterialLayerObject> LayerWeak;`
- L48 _public prototype_ `FDMMaterialLayerReference();`
- L49 _public prototype_ `FDMMaterialLayerReference(UDMMaterialLayerObject* InLayer);`
- L51 _public prototype_ `UDMMaterialLayerObject* GetLayer() const;`
- L53 _public prototype_ `bool IsValid() const;`

#### struct `FDMScopedUITransaction`  
`struct FDMScopedUITransaction`  
_L56-62_
- L58 _public member_ `FScopedTransaction Transaction;`
- L59 _public member_ `TGuardValue<bool> UIFeedbackGuard;`
- L61 _public prototype_ `FDMScopedUITransaction(const FText& InSessionName, bool bInShouldActuallyTransact = true);`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace DynamicMaterialEditor` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::DynamicMaterialEditor`)
- L28 _prototype_ `void SetMask(FExpressionInput& InInputConnector, const FExpressionOutput& InOutputConnector, int32 InChannelOverride);` (scope `UE::DynamicMaterialEditor::Private`)
- L31 _prototype_ `int32 ChannelIndexToChannelBit(int32 InChannelIndex);` (scope `UE::DynamicMaterialEditor::Private`) — Converts 0,1,2,3,4 to 0,1,2,4,8
- L33 _prototype_ `int32 ChannelBitToChannelIndex(int32 InChannelBit);` (scope `UE::DynamicMaterialEditor::Private`)
- L35 _prototype_ `bool IsCustomMaterialProperty(EDMMaterialPropertyType InMaterialProperty);` (scope `UE::DynamicMaterialEditor::Private`)
- L37 _prototype_ `void LogError(const FString& InMessage, bool bInToast = true, const UObject* InSource = nullptr);` (scope `UE::DynamicMaterialEditor::Private`)
- L39 _prototype_ `FText GetMaterialPropertyLongDisplayName(EDMMaterialPropertyType InMaterialProperty);` (scope `UE::DynamicMaterialEditor::Private`)
- L41 _prototype_ `FText GetMaterialPropertyShortDisplayName(EDMMaterialPropertyType InMaterialProperty);` (scope `UE::DynamicMaterialEditor::Private`)

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialEffect.h` (Public)


#### enum `EDMMaterialEffectTarget`  
`enum class EDMMaterialEffectTarget : uint8`  
_L19-26_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `None = 0`
- L22 _public enumerator_ `BaseStage = 1 << 0`
- L23 _public enumerator_ `MaskStage = 1 << 1`
- L24 _public enumerator_ `TextureUV = 1 << 2`
- L25 _public enumerator_ `Slot = 1 << 3`

#### class `UDMMaterialEffect`  
`class UDMMaterialEffect : public UDMMaterialComponent, public IDMJsonSerializable`  
_L29-99_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Effect"))`
- inherits: `UDMMaterialComponent,IDMJsonSerializable`
- L35 _public prototype_ `static EDMMaterialEffectTarget StageTypeToEffectType(EDMMaterialLayerStage InStageType);` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L38 _public prototype_ `static UDMMaterialEffect* CreateEffect(UDMMaterialEffectStack* InEffectStack, TSubclassOf<UDMMaterialEffect> InEffectClass);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L41 _public function_ `template<typename InEffectClass> static InEffectClass* CreateEffect(UDMMaterialEffectStack* InEffectStack)`
- L46 _public prototype_ `UDMMaterialEffect();`
- L49 _public prototype_ `UDMMaterialEffectStack* GetEffectStack() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L53 _public prototype_ `int32 FindIndex() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Retrieves the index of this effect in the effect stack.
- L56 _public prototype_ `bool IsEnabled() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L59 _public prototype_ `bool SetEnabled(bool bInIsEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L63 _public prototype_ `EDMMaterialEffectTarget GetEffectTarget() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the type of nodes which this effect targets.
- L66 _public prototype_ `virtual FText GetEffectName() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L69 _public function_ `virtual FText GetEffectDescription() const PURE_VIRTUAL(UDMMaterialEffect::ApplyTo, return FText::GetEmpty();) virtual bool IsCompatibleWith(UDMMaterialEffect* InEffect) const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L75 _public prototype_ `virtual void ApplyTo(const TSharedRef<FDMMaterialBuildState>& InBuildState, TArray<UMaterialExpression*>& InOutExpressions, int32& InOutLastExpressionOutputChannel, int32& InLastExpressionOutputIndex) const PURE_VIRTUAL(UDMMaterialEffect::ApplyTo) virtual UObject* GetAsset() const PURE_VIRTUAL(UMaterialEffect::GetAsset, return nullptr;)` — Apply this effect to the output of something, such as a stage, slot or texture.
- L83 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L84 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L85 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType) override;`
- L86 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L90 _public prototype_ `virtual void PostEditUndo() override;`
- L95 _protected member_ `EDMMaterialEffectTarget EffectTarget;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L98 _protected member_ `bool bEnabled;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialEffectFunction.h` (Public)


#### class `UDMMaterialEffectFunction`  
`class UDMMaterialEffectFunction : public UDMMaterialEffect`  
_L11-85_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer", Meta = (DisplayName = "Material Designer Effect Function"))`
- inherits: `UDMMaterialEffect`
- L16 _public member_ `static const FString InputsPathToken;`
- L18 _public prototype_ `UDMMaterialEffectFunction();`
- L21 _public prototype_ `UMaterialFunctionInterface* GetMaterialFunction() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L24 _public prototype_ `bool SetMaterialFunction(UMaterialFunctionInterface* InFunction);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L28 _public prototype_ `UDMMaterialValue* GetInputValue(int32 InIndex) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the value used as the function input.
- L31 _public prototype_ `TArray<UDMMaterialValue*> BP_GetInputValues() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer", Meta = (DisplayName = "Get Input Values"))`
- L33 _public prototype_ `const TArray<TObjectPtr<UDMMaterialValue>>& GetInputValues() const;`
- L37 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L38 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L43 _public prototype_ `virtual FText GetEffectName() const override;`
- L44 _public prototype_ `virtual FText GetEffectDescription() const override;`
- L45 _public prototype_ `virtual bool IsCompatibleWith(UDMMaterialEffect* InEffect) const override;`
- L46 _public prototype_ `virtual void ApplyTo(const TSharedRef<FDMMaterialBuildState>& InBuildState, TArray<UMaterialExpression*>& InOutExpressions, int32& InOutLastExpressionOutputChannel, int32& InOutLastExpressionOutputIndex) const override;`
- L48 _public prototype_ `virtual UObject* GetAsset() const override;`
- L52 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L53 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L57 _public prototype_ `virtual bool Modify(bool bInAlwaysMarkDirty = true) override;`
- L58 _public prototype_ `virtual void PostLoad() override;`
- L63 _protected member_ `TObjectPtr<UMaterialFunctionInterface> MaterialFunctionPtr;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L66 _protected member_ `TArray<TObjectPtr<UDMMaterialValue>> InputValues;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L69 _protected prototype_ `void OnMaterialFunctionChanged();` — Re-inits the function.
- L72 _protected prototype_ `void InitFunction();` — Adds required inputs.
- L75 _protected prototype_ `void DeinitFunction();` — Removes inputs.
- L78 _protected prototype_ `bool NeedsFunctionInit() const;` — Returns true if the input values do not match the function's input pins.
- L81 _protected prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const override;`
- L82 _protected prototype_ `virtual void OnComponentAdded() override;`
- L83 _protected prototype_ `virtual void OnComponentRemoved() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialEffectStack.h` (Public)


#### struct `FDMMaterialEffectJson`  
`struct FDMMaterialEffectJson`  
_L19-23_
- L21 _public member_ `TSubclassOf<UDMMaterialEffect> Class;`
- L22 _public member_ `TSharedPtr<FJsonValue> Data = nullptr;`

#### struct `FDMMaterialEffectStackJson`  
`struct FDMMaterialEffectStackJson`  
_L26-32_
- reflection: `USTRUCT(BlueprintType)`
- L30 _public member_ `bool bEnabled = false;`
- L31 _public member_ `TArray<FDMMaterialEffectJson> Effects = {};`

#### class `UDMMaterialEffectStack`  
`class UDMMaterialEffectStack : public UDMMaterialComponent`  
_L38-167_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer", Meta = (DisplayName = "Material Designer Effect Stack"))`
- inherits: `UDMMaterialComponent`
- desc: Container for effects. Effects can be applied to either layers (on a per stage basis) or to slots.
- L43 _public member_ `static const FString EffectsPathToken;`
- L45 _public typedef_ `using FEffectCallbackFunc = TFunctionRef<void(UDMMaterialEffect*)>;`
- L48 _public function_ `static UDMMaterialEffectStack* CreateEffectStackForSlot(UDMMaterialSlot* InSlot)` — `UFUNCTION(BlueprintCallable, Category = "Material Designer", Meta = (DisplayName = "Create Effect Stack (For Slot)"))`
- L54 _public function_ `static UDMMaterialEffectStack* CreateEffectStackForLayer(UDMMaterialLayerObject* InLayer)` — `UFUNCTION(BlueprintCallable, Category = "Material Designer", Meta = (DisplayName = "Create Effect Stack (For Layer)"))`
- L59 _public prototype_ `static UDMMaterialEffectStack* CreateEffectStack(UDMMaterialSlot* InSlot);`
- L60 _public prototype_ `static UDMMaterialEffectStack* CreateEffectStack(UDMMaterialLayerObject* InLayer);`
- L62 _public prototype_ `UDMMaterialEffectStack();`
- L65 _public prototype_ `UDMMaterialSlot* GetSlot() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L68 _public prototype_ `UDMMaterialLayerObject* GetLayer() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L71 _public prototype_ `bool IsEnabled() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L74 _public prototype_ `bool SetEnabled(bool bInIsEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L77 _public prototype_ `UDMMaterialEffect* GetEffect(int32 InIndex) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L80 _public prototype_ `TArray<UDMMaterialEffect*> BP_GetEffects() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer", Meta = (DisplayName = "Get Effects"))`
- L82 _public prototype_ `const TArray<TObjectPtr<UDMMaterialEffect>>& GetEffects() const;`
- L85 _public prototype_ `bool HasEffect(const UDMMaterialEffect* InEffect) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L88 _public prototype_ `bool AddEffect(UDMMaterialEffect* InEffect);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L91 _public prototype_ `UDMMaterialEffect* SetEffect(int32 InIndex, UDMMaterialEffect* InEffect);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L94 _public function_ `bool BP_MoveEffectByIndex(int32 InIndex, int32 InNewIndex)` — `UFUNCTION(BlueprintCallable, Category = "Material Designer", Meta = (DisplayName = "Move Effect (By Index)"))`
- L99 _public prototype_ `bool MoveEffect(int32 InIndex, int32 InNewIndex);`
- L102 _public function_ `bool BP_MoveEffectByValue(UDMMaterialEffect* InEffect, int32 InNewIndex)` — `UFUNCTION(BlueprintCallable, Category = "Material Designer", Meta = (DisplayName = "Move Effect (By Value)"))`
- L107 _public prototype_ `bool MoveEffect(UDMMaterialEffect* InEffect, int32 InNewIndex);`
- L110 _public function_ `UDMMaterialEffect* BP_RemoveEffectByIndex(int32 InIndex)` — `UFUNCTION(BlueprintCallable, Category = "Material Designer", Meta = (DisplayName = "Remove Effect (By Index)"))`
- L115 _public prototype_ `UDMMaterialEffect* RemoveEffect(int32 InIndex);`
- L118 _public function_ `bool BP_RemoveEffectByValue(UDMMaterialEffect* InEffect)` — `UFUNCTION(BlueprintCallable, Category = "Material Designer", Meta = (DisplayName = "Remove Effect (By Value)"))`
- L123 _public prototype_ `bool RemoveEffect(UDMMaterialEffect* InEffect);`
- L126 _public prototype_ `bool ApplyEffects(const TSharedRef<FDMMaterialBuildState>& InBuildState, EDMMaterialEffectTarget InEffectTarget, TArray<UMaterialExpression*>& InOutStageExpressions, int32& InOutLastExpressionOutputChannel, int32& InOutLastExpressionOutputIndex) const;` — Apply all matching effect types to the expressions and add them to the array.
- L131 _public prototype_ `FDMMaterialEffectStackJson CreatePreset();` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Creates a preset based on the current stage.
- L135 _public prototype_ `void ApplyPreset(const FDMMaterialEffectStackJson& InPreset);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Apply the given preset to this stack. Does not remove old effects.
- L138 _public prototype_ `virtual UDMMaterialComponent* GetParentComponent() const override;`
- L139 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L140 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L141 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType) override;`
- L142 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L146 _public prototype_ `virtual bool Modify(bool bInAlwaysMarkDirty = true) override;`
- L147 _public prototype_ `virtual void PostEditUndo() override;`
- L152 _protected member_ `bool bEnabled;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L155 _protected member_ `TArray<TObjectPtr<UDMMaterialEffect>> Effects;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L157 _protected prototype_ `TArray<UDMMaterialEffect*> GetIncompatibleEffects(UDMMaterialEffect* InEffect);`
- L160 _protected prototype_ `TArray<UDMMaterialEffect*> RemoveIncompatibleEffects(UDMMaterialEffect* InEffect);` — Returns the removed effects.
- L163 _protected prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const override;`
- L164 _protected prototype_ `virtual void OnComponentAdded() override;`
- L165 _protected prototype_ `virtual void OnComponentRemoved() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialLayer.h` (Public)


#### class `UDMMaterialLayerObject`  
`class UDMMaterialLayerObject : public UDMMaterialComponent`  
_L19-188_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer", Meta = (DisplayName = "Material Designer Layer"))`
- inherits: `UDMMaterialComponent`
- desc: A collection of stages.
- L24 _public member_ `static const FString StagesPathToken;`
- L25 _public member_ `static const FString BasePathToken;`
- L26 _public member_ `static const FString MaskPathToken;`
- L27 _public member_ `static const FString EffectStackPathToken;`
- L29 _public typedef_ `using FStageCallbackFunc = TFunctionRef<void(UDMMaterialStage*)>;`
- L32 _public prototype_ `static UDMMaterialLayerObject* CreateLayer(UDMMaterialSlot* InSlot, EDMMaterialPropertyType InMaterialProperty, const TArray<UDMMaterialStage*>& InStages);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L35 _public prototype_ `static UDMMaterialLayerObject* DeserializeFromString(UDMMaterialSlot* InOuter, const FString& InSerializedString);`
- L37 _public prototype_ `UDMMaterialLayerObject();`
- L40 _public prototype_ `UDMMaterialSlot* GetSlot() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L44 _public prototype_ `int32 FindIndex() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Find the index of this layer in the slot.
- L47 _public function_ `const FText& GetLayerName() const` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L50 _public prototype_ `void SetLayerName(const FText& InName);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L53 _public prototype_ `bool IsEnabled() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L56 _public prototype_ `bool SetEnabled(bool bInIsEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L59 _public prototype_ `EDMMaterialPropertyType GetMaterialProperty() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L62 _public prototype_ `bool SetMaterialProperty(EDMMaterialPropertyType InMaterialProperty);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L66 _public prototype_ `bool IsTextureUVLinkEnabled() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Texture UV Link means that all stages use the same Texture UV from the base stage, if available.
- L70 _public prototype_ `bool SetTextureUVLinkEnabled(bool bInValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Texture UV Link means that all stages use the same Texture UV from the base stage, if available.
- L74 _public prototype_ `bool ToggleTextureUVLinkEnabled();` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Texture UV Link means that all stages use the same Texture UV from the base stage, if available.
- L77 _public prototype_ `UDMMaterialLayerObject* GetPreviousLayer(EDMMaterialPropertyType InUsingProperty, EDMMaterialLayerStage InSearchFor) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L80 _public prototype_ `UDMMaterialLayerObject* GetNextLayer(EDMMaterialPropertyType InUsingProperty, EDMMaterialLayerStage InSearchFor) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L83 _public prototype_ `bool CanMoveLayerAbove(UDMMaterialLayerObject* InLayer) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L86 _public prototype_ `bool CanMoveLayerBelow(UDMMaterialLayerObject* InLayer) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L89 _public prototype_ `UDMMaterialStage* GetStage(EDMMaterialLayerStage InStageType = EDMMaterialLayerStage::All, bool bInCheckEnabled = false) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L92 _public prototype_ `TArray<UDMMaterialStage*> GetStages(EDMMaterialLayerStage InStageType = EDMMaterialLayerStage::All, bool bInCheckEnabled = false) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L94 _public prototype_ `const TArray<TObjectPtr<UDMMaterialStage>>& GetAllStages() const;`
- L97 _public prototype_ `EDMMaterialLayerStage GetStageType(const UDMMaterialStage* InStage) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L100 _public prototype_ `UDMMaterialStage* GetFirstValidStage(EDMMaterialLayerStage InStageScope) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L103 _public prototype_ `UDMMaterialStage* GetLastValidStage(EDMMaterialLayerStage InStageScope) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L106 _public prototype_ `bool HasValidStage(const UDMMaterialStage* InStage) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L109 _public prototype_ `bool HasValidStageOfType(EDMMaterialLayerStage InStageScope = EDMMaterialLayerStage::All) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L112 _public prototype_ `bool IsStageEnabled(EDMMaterialLayerStage InStageScope = EDMMaterialLayerStage::All) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L116 _public prototype_ `UDMMaterialStage* GetFirstEnabledStage(EDMMaterialLayerStage InStageScope) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Checks for the first enabled and valid stage.
- L120 _public prototype_ `UDMMaterialStage* GetLastEnabledStage(EDMMaterialLayerStage InStageScope) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Checks for the last enabled and valid stage.
- L124 _public prototype_ `bool SetStage(EDMMaterialLayerStage InStageType, UDMMaterialStage* InStage);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Replace the specified stage.
- L127 _public prototype_ `bool AreAllStagesValid(EDMMaterialLayerStage InStageScope) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L131 _public prototype_ `bool AreAllStagesEnabled(EDMMaterialLayerStage InStageScope) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Checks if both stages are enabled and valid
- L134 _public prototype_ `void ForEachValidStage(EDMMaterialLayerStage InStageScope, FStageCallbackFunc InCallback) const;` — Iterate over all the valid stages, whether they are enabled or not.
- L137 _public prototype_ `void ForEachEnabledStage(EDMMaterialLayerStage InStageScope, FStageCallbackFunc InCallback) const;` — Iterate over only the enabled stages.
- L140 _public prototype_ `UDMMaterialEffectStack* GetEffectStack() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L143 _public prototype_ `FString SerializeToString() const;` — Used for copy+pasting.
- L145 _public prototype_ `void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const;`
- L148 _public prototype_ `bool ApplyEffects(const TSharedRef<FDMMaterialBuildState>& InBuildState, const UDMMaterialStage* InStage, TArray<UMaterialExpression*>& InOutStageExpressions, int32& InOutLastExpressionOutputChannel, int32& InOutLastExpressionOutputIndex) const;` — Apply the effects from this layer's effect stack to the given expressions based on the type of stage.
- L152 _public prototype_ `virtual UDMMaterialComponent* GetParentComponent() const override;`
- L153 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L154 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L155 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType) override;`
- L156 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L160 _public prototype_ `virtual bool Modify(bool bInAlwaysMarkDirty = true) override;`
- L161 _public prototype_ `virtual void PostEditUndo() override;`
- L166 _protected member_ `EDMMaterialPropertyType MaterialProperty = EDMMaterialPropertyType::None;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L169 _protected member_ `FText LayerName;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L172 _protected member_ `bool bEnabled;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L175 _protected member_ `TArray<TObjectPtr<UDMMaterialStage>> Stages;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L178 _protected member_ `TObjectPtr<UDMMaterialEffectStack> EffectStack;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L181 _protected member_ `bool bLinkedUVs;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L184 _protected prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const override;`
- L185 _protected prototype_ `virtual void OnComponentAdded() override;`
- L186 _protected prototype_ `virtual void OnComponentRemoved() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialProperty.h` (Public)


#### class `UDMMaterialProperty`  
`class UDMMaterialProperty : public UDMMaterialComponent`  
_L28-273_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer", Meta = (DisplayName = "Material Designer Property"))`
- inherits: `UDMMaterialComponent`
- desc: Base Color, Specular, Opacity, etc
- L33 _public member_ `static const FString ComponentsPathToken;`
- L42 _public prototype_ `static UDMMaterialProperty* CreateCustomMaterialPropertyDefaultSubobject(UDynamicMaterialModelEditorOnlyData* InModelEditorOnlyData, EDMMaterialPropertyType InMaterialProperty, const FName& InSubObjName);` — Craetes a material property as a default subobject of the EditorOnlyData object. @param InModelEditorOnlyData The parent EditorOnlyData object. @param InMaterialProperty The property type of the material property. @param InSubObjName The subobject name. @return The newly created default subobject.
- L45 _public prototype_ `UDMMaterialProperty();`
- L48 _public prototype_ `UDynamicMaterialModelEditorOnlyData* GetMaterialModelEditorOnlyData() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L51 _public function_ `EDMMaterialPropertyType GetMaterialProperty() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L54 _public function_ `bool IsEnabled() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L57 _public prototype_ `void SetEnabled(bool bInEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L63 _public prototype_ `FText GetDescription() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — The description of this property based on the EDMMaterialPropertyType enum.
- L70 _public prototype_ `bool IsMaterialPin() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Whether this property represents a material pin. Only materials properties with a pin will be generated by default.
- L76 _public function_ `EDMValueType GetInputConnectorType() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — @return The value type of this property. Will be either VT_Float1, VT_Float3_RGB or VT_Float3_XYZ.
- L82 _public function_ `const FDMMaterialStageConnection& GetInputConnectionMap() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — @return Get the expressions which connect to this property, mapped per channel.
- L87 _public function_ `FDMMaterialStageConnection& GetInputConnectionMap()` — @return Get the expressions which connect to this property, mapped per channel.
- L94 _public function_ `UMaterialFunctionInterface* GetOutputProcessor() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — The output process is an optional material function which is applied in between the property and its inputs. @return The current output processor.
- L101 _public prototype_ `void SetOutputProcessor(UMaterialFunctionInterface* InFunction);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — The output process is an optional material function which is applied in between the property and its inputs. @param InFunction The new output processor.
- L108 _public prototype_ `virtual bool IsValidForModel(const UDynamicMaterialModelEditorOnlyData& InEditorOnlyData) const;` — Check whether the current model settings are valid for this property. @param InMaterialModel The model with the settings. @return True if it is valid.
- L114 _public prototype_ `virtual void ResetInputConnectionMap();` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Empty the connection map and recalculate the input types.
- L121 _public prototype_ `virtual UMaterialExpression* GetDefaultInput(const TSharedRef<FDMMaterialBuildState>& InBuildState) const;` — Generates a default input node for this property if the layer stack is empty. @param InBuildState The current build state. @return The last in the chain of any expressions created (for direct connection to the property).
- L126 _public prototype_ `virtual TEnumAsByte<EMaterialSamplerType> GetTextureSamplerType() const;` — @return The texture sample type to use for any texture samplers connected to this property.
- L132 _public prototype_ `virtual void OnSlotAdded(UDMMaterialSlot* InSlot);` — Triggered when a slot is added to this property. Should create useful, default layer stack. @param InSlot The slot that was created.
- L137 _public prototype_ `virtual void AddDefaultBaseStage(UDMMaterialLayerObject* InLayer);` — Adds the default base stage for a layer in this property.
- L142 _public prototype_ `virtual void AddDefaultMaskStage(UDMMaterialLayerObject* InLayer);` — Adds the default mask stage for a layer in this property.
- L150 _public prototype_ `virtual UDMMaterialComponent* AddComponent(FName InName, UDMMaterialComponent* InComponent);` — Adds a component to the component list. Sets component state to added. @param InName The name of the component in the map. @param InComponent The component to add. @return The replaced component from the map.
- L157 _public prototype_ `virtual bool HasComponent(FName InName) const;` — Checks to see if a component with this name exists. @param InName The name of the component. @return True if it exists, even if it isn't valid.
- L164 _public prototype_ `virtual UDMMaterialComponent* GetComponent(FName InName) const;` — Fetches a component from the component list. @param InName The name of the component. @return The component in the map with that name.
- L167 _public function_ `template<typename InClassName> InClassName* GetTypedComponent(FName InName) const`
- L177 _public prototype_ `virtual UDMMaterialComponent* RemoveComponent(FName InName);` — Removes the component from the component list. Sets component state to removed. @param InName The name of the component. @return The removed component.
- L182 _public prototype_ `virtual void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const;` — Generates the base expressions for this slot.
- L187 _public prototype_ `static void GenerateOpacityExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState, UDMMaterialSlot* InFromSlot, EDMMaterialPropertyType InFromProperty, UMaterialExpression*& OutExpression, int32& OutOutputIndex, int32& OutOutputChannel);` — Adds expressions to opacity properties based on color channel.
- L193 _public prototype_ `virtual void AddAlphaMultiplier(const TSharedRef<FDMMaterialBuildState>& InBuildState) const;` — Adds the alpha multiplier.
- L198 _public prototype_ `virtual void AddOutputProcessor(const TSharedRef<FDMMaterialBuildState>& InBuildState) const;` — Adds the output processor to the end of the current expression chain.
- L203 _public prototype_ `virtual void GeneratePreviewMaterial(UMaterial* InPreviewMaterial);` — Adds nodes to the given material based on this property's generated expressions.
- L206 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType) override;`
- L207 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L208 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L209 _public prototype_ `virtual void PreEditChange(FProperty* InPropertyAboutToChange) override;`
- L210 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L213 _public prototype_ `void LoadDeprecatedModelData(UDMMaterialProperty* InOldProperty);`
- L216 _protected prototype_ `static UMaterialExpression* CreateConstant(const TSharedRef<FDMMaterialBuildState>& InBuildState, float InDefaultValue);`
- L217 _protected prototype_ `static UMaterialExpression* CreateConstant(const TSharedRef<FDMMaterialBuildState>& InBuildState, const FVector2d& InDefaultValue);`
- L218 _protected prototype_ `static UMaterialExpression* CreateConstant(const TSharedRef<FDMMaterialBuildState>& InBuildState, const FVector3d& InDefaultValue);`
- L219 _protected prototype_ `static UMaterialExpression* CreateConstant(const TSharedRef<FDMMaterialBuildState>& InBuildState, const FVector4d& InDefaultValue);`
- L225 _protected member_ `EDMMaterialPropertyType MaterialProperty;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — The property type of this property.
- L231 _protected member_ `bool bEnabled;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — Whether this property is enabled. If it is not enabled, it will generate no expressions.
- L237 _protected member_ `EDMValueType InputConnectorType;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — The value type used to connect to this property. Will be either VT_Float1, VT_Float3_RGB or VT_Float3_XYZ.
- L243 _protected member_ `FDMMaterialStageConnection InputConnectionMap;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — The map of expressions connected to this property's input node.
- L249 _protected member_ `TObjectPtr<UMaterialFunctionInterface> OutputProcessor;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — An optional material function which is applied in between the property and its inputs.
- L252 _protected member_ `TObjectPtr<UMaterialFunctionInterface> OutputProcessor_PreUpdate;` — `UPROPERTY(Transient, TextExportTransient)`
- L258 _protected member_ `TMap<FName, TObjectPtr<UDMMaterialComponent>> Components;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — Components of this property. Not necessarily owned or controlled by this property.
- L260 _protected prototype_ `UDMMaterialProperty(EDMMaterialPropertyType InMaterialProperty, EDMValueType InInputConnectorType);`
- L266 _protected prototype_ `void OnOutputProcessorUpdated();` — Triggered when the output process is updated either through PostEditChangeProperty or via the setter. Will potentially reset the value to null if it is invalid.
- L269 _protected prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const override;`
- L270 _protected prototype_ `virtual void OnComponentAdded() override;`
- L271 _protected prototype_ `virtual void OnComponentRemoved() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialSlot.h` (Public)


#### class `UDMMaterialSlot`  
`class UDMMaterialSlot : public UDMMaterialComponent`  
_L28-190_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer", Meta = (DisplayName = "Material Designer Slot"))`
- inherits: `UDMMaterialComponent`
- desc: A list of operations/inputs daisy chained together to produce an output.
- L36 _public member_ `static const FString LayersPathToken;`
- L38 _public prototype_ `UDMMaterialSlot();`
- L41 _public prototype_ `UDynamicMaterialModelEditorOnlyData* GetMaterialModelEditorOnlyData() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L45 _public function_ `int32 GetIndex() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the index of this slot in the model.
- L47 _public function_ `void SetIndex(int32 InNewIndex)`
- L50 _public prototype_ `FText GetDescription() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L54 _public prototype_ `const TArray<EDMValueType>& GetOutputConnectorTypesForMaterialProperty(EDMMaterialPropertyType InMaterialProperty) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the output types for the last layer with the given material property.
- L58 _public prototype_ `TSet<EDMValueType> GetAllOutputConnectorTypes() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns all possible output connector types.
- L61 _public prototype_ `UDMMaterialLayerObject* GetLayer(int32 InLayerIndex) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer", meta = (DisplayName = "Get Layer"))`
- L64 _public prototype_ `UDMMaterialLayerObject* FindLayer(const UDMMaterialStage* InBaseOrMask) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L67 _public prototype_ `TArray<UDMMaterialLayerObject*> BP_GetLayers() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer", meta = (DisplayName = "Get Layers"))`
- L69 _public function_ `const TArray<TObjectPtr<UDMMaterialLayerObject>>& GetLayers() const`
- L73 _public prototype_ `UDMMaterialLayerObject* AddDefaultLayer(EDMMaterialPropertyType InMaterialProperty);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Adds the default layer type for this slot based on the given material property.
- L77 _public prototype_ `UDMMaterialLayerObject* AddLayer(EDMMaterialPropertyType InMaterialProperty, UDMMaterialStage* InNewBase);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Adds the default layer (with specified base) based on the given material property.
- L81 _public prototype_ `UDMMaterialLayerObject* AddLayerWithMask(EDMMaterialPropertyType InMaterialProperty, UDMMaterialStage* InNewBase, UDMMaterialStage* InNewMask);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Adds a new layer with the specified base and mask layers.
- L85 _public prototype_ `bool PasteLayer(UDMMaterialLayerObject* InLayer);` — Adds the specified layer to the end of the layer list.
- L89 _public prototype_ `bool CanRemoveLayer(UDMMaterialLayerObject* InLayer) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Can't be removed if it is the last remaining layer.
- L93 _public prototype_ `bool RemoveLayer(UDMMaterialLayerObject* InLayer);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Removes the layer, if possible.
- L96 _public prototype_ `bool MoveLayer(UDMMaterialLayerObject* InLayer, int32 InNewIndex);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L99 _public prototype_ `bool MoveLayerBefore(UDMMaterialLayerObject* InLayer, UDMMaterialLayerObject* InBeforeLayer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L102 _public prototype_ `bool MoveLayerAfter(UDMMaterialLayerObject* InLayer, UDMMaterialLayerObject* InAfterLayer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L106 _public prototype_ `UDMMaterialLayerObject* GetLastLayerForMaterialProperty(EDMMaterialPropertyType InMaterialProperty) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Useful for determining output types.
- L108 _public prototype_ `void UpdateOutputConnectorTypes();`
- L110 _public prototype_ `void UpdateMaterialProperties();`
- L113 _public function_ `FDMOnMaterialSlotConnectorsUpdated::RegistrationType& GetOnConnectorsUpdateDelegate()` — Called when the output connectors for this slot change.
- L116 _public function_ `FDMOnMaterialSlotPropertiesUpdated::RegistrationType& GetOnPropertiesUpdateDelegate()` — Called when properties of this slot change.
- L119 _public function_ `FDMOnMaterialSlotLayersUpdated::RegistrationType& GetOnLayersUpdateDelegate()` — Called whenever the properties of a layer change or when one is added, removed or moved.
- L122 _public prototype_ `void OnPropertiesUpdated();` — Calls OnPropertiesUpdateDelegate when the property for this slot is updated.
- L124 _public prototype_ `void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const;`
- L127 _public function_ `const TMap<TWeakObjectPtr<UDMMaterialSlot>, int32>& GetSlotsReferencedBy() const` — Return a map of the slots referencing this slot and how many times that reference exists.
- L131 _public prototype_ `TArray<UDMMaterialSlot*> K2_GetSlotsReferencedBy() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer", Meta = (DisplayName="Get Slots Referenced By"))` — Returns an array of the slots referencing this slot.
- L134 _public prototype_ `bool ReferencedBySlot(UDMMaterialSlot* InOtherSlot);` — Returns true if a new associated is created
- L137 _public prototype_ `bool UnreferencedBySlot(UDMMaterialSlot* InOtherSlot);` — Returns true if all associations have been removed
- L141 _public prototype_ `bool SetLayerMaterialPropertyAndReplaceOthers(UDMMaterialLayerObject* InLayer, EDMMaterialPropertyType InPropertyFrom, EDMMaterialPropertyType InPropertyTo);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Sets the material property of the given layer and changes all other layers matching that property to a different one.
- L146 _public prototype_ `bool ChangeMaterialProperty(EDMMaterialPropertyType InPropertyFrom, EDMMaterialPropertyType InPropertyTo);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Changes the material property of all matching layers to another.
- L149 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType) override;`
- L150 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L151 _public function_ `virtual UDMMaterialComponent* GetParentComponent() const override`
- L152 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L156 _public prototype_ `virtual bool Modify(bool bInAlwaysMarkDirty = true) override;`
- L157 _public prototype_ `virtual void PostEditUndo() override;`
- L158 _public prototype_ `virtual void PostLoad() override;`
- L163 _protected member_ `int32 Index;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L166 _protected member_ `TArray<TObjectPtr<UDMMaterialLayerObject>> LayerObjects;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L169 _protected member_ `TMap<EDMMaterialPropertyType, FDMMaterialSlotOutputConnectorTypes> OutputConnectorTypes;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L172 _protected member_ `TMap<TWeakObjectPtr<UDMMaterialSlot>, int32> SlotsReferencedBy;` — `UPROPERTY()`
- L174 _protected member_ `FDMOnMaterialSlotConnectorsUpdated OnConnectorsUpdateDelegate;`
- L175 _protected member_ `FDMOnMaterialSlotPropertiesUpdated OnPropertiesUpdateDelegate;`
- L176 _protected member_ `FDMOnMaterialSlotLayersUpdated OnLayersUpdateDelegate;`
- L179 _protected prototype_ `virtual void OnComponentAdded() override;`
- L180 _protected prototype_ `virtual void OnComponentRemoved() override;`
- L181 _protected prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const override;`
- L187 _private member_ `TArray<FDMMaterialLayer> Layers;` — `UE_DEPRECATED(5.4, "Promoted to full UObjects.")` — `UPROPERTY()`
- L189 _private prototype_ `void ConvertDeprecatedLayers(TArray<FDMMaterialLayer>& InLayers);`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMOnMaterialSlotConnectorsUpdated, UDMMaterialSlot*);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMOnMaterialSlotConnectorsUpdated, UDMMaterialSlot*);`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMOnMaterialSlotPropertiesUpdated, UDMMaterialSlot*);`
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMOnMaterialSlotPropertiesUpdated, UDMMaterialSlot*);`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMOnMaterialSlotLayersUpdated, UDMMaterialSlot*);`
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMOnMaterialSlotLayersUpdated, UDMMaterialSlot*);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialStage.h` (Public)


#### class `UDMMaterialStage`  
`class UDMMaterialStage : public UDMMaterialComponent`  
_L45-271_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Stage"))`
- inherits: `UDMMaterialComponent`
- desc: A component which wraps a source and its inputs.
- L52 _public member_ `static const FString SourcePathToken;`
- L53 _public member_ `static const FString InputsPathToken;`
- L56 _public prototype_ `static UDMMaterialStage* CreateMaterialStage(UDMMaterialLayerObject* InLayer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L58 _public prototype_ `UDMMaterialStage();`
- L61 _public prototype_ `UDMMaterialLayerObject* GetLayer() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L64 _public function_ `UDMMaterialStageSource* GetSource() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L67 _public function_ `bool IsEnabled() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L70 _public prototype_ `bool SetEnabled(bool bInEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L73 _public function_ `bool CanChangeSource() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L76 _public function_ `void SetCanChangeSource(bool bInCanChangeSource)` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L79 _public prototype_ `void SetSource(UDMMaterialStageSource* InSource);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L82 _public function_ `const TArray<UDMMaterialStageInput*>& GetInputs() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L86 _public function_ `const TArray<FDMMaterialStageConnection>& GetInputConnectionMap() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Determines what connects to what on this stage's Source.
- L88 _public function_ `TArray<FDMMaterialStageConnection>& GetInputConnectionMap()`
- L91 _public prototype_ `EDMValueType GetSourceType(const FDMMaterialStageConnectorChannel& InChannel) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L95 _public prototype_ `bool IsInputMapped(int32 InputIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Returns true if the given source's input is mapped to an input (or the previous stage).
- L103 _public prototype_ `virtual bool IsCompatibleWithPreviousStage(const UDMMaterialStage* InPreviousStage) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns true if the output of the previous stage can connect to this stage. It is now up to the user to sort this particular problem out because it would do more harm than good to force correctness in "transition states" while the user is changing settings.
- L107 _public prototype_ `virtual bool IsCompatibleWithNextStage(const UDMMaterialStage* InNextStage) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — @see IsCompatibleWithPreviousStage
- L110 _public prototype_ `void AddInput(UDMMaterialStageInput* InNewInput);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L113 _public prototype_ `void RemoveInput(UDMMaterialStageInput* InInput);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L116 _public prototype_ `void RemoveAllInputs();` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L119 _public prototype_ `virtual void InputUpdated(UDMMaterialStageInput* InInput, EDMUpdateType InUpdateType);` — Called when one of the inputs triggers it's Update event.
- L123 _public prototype_ `virtual void ResetInputConnectionMap();` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Verifies the entire input connection map.
- L125 _public prototype_ `void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const;`
- L128 _public prototype_ `TMap<EDMMaterialPropertyType, UDMMaterialLayerObject*> GetPreviousStagesPropertyMap();` — Get the last layer for each property type from the previous stages.
- L131 _public prototype_ `TMap<EDMMaterialPropertyType, UDMMaterialLayerObject*> GetPropertyMap();` — Get the last layer for each property type from all stages.
- L133 _public typedef_ `using FSourceInitFunctionPtr = TFunction<void(UDMMaterialStage*, UDMMaterialStageSource*)>;`
- L136 _public function_ `UDMMaterialStageSource* ChangeSource(TSubclassOf<UDMMaterialStageSource> InSourceClass)` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L141 _public prototype_ `UDMMaterialStageSource* ChangeSource(TSubclassOf<UDMMaterialStageSource> InSourceClass, FSourceInitFunctionPtr InPreInit);`
- L145 _public function_ `template<typename InSourceClass> InSourceClass* ChangeSource(FSourceInitFunctionPtr InPreInit = nullptr)`
- L151 _public function_ `template<typename InSourceClass> InSourceClass* ChangeSource(TSubclassOf<UDMMaterialStageSource> InSourceSubclass, FSourceInitFunctionPtr InPreInit = nullptr)`
- L156 _public typedef_ `using FInputInitFunctionPtr = TFunction<void(UDMMaterialStage*, UDMMaterialStageInput*)>;`
- L159 _public function_ `UDMMaterialStageInput* ChangeInput(TSubclassOf<UDMMaterialStageInput> InInputClass, int32 InInputIdx, int32 InInputChannel, int32 InOutputIdx, int32 InOutputChannel)` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L173 _public prototype_ `UDMMaterialStageInput* ChangeInput(TSubclassOf<UDMMaterialStageInput> InInputClass, int32 InInputIdx, int32 InInputChannel, int32 InOutputIdx, int32 InOutputChannel, FInputInitFunctionPtr InPreInit);` — Creates a new input value and maps it to a specific source input. @param InInputIdx Index of the source input. @param InInputChannel The channel of the input that the input connects to. @param InOutputIdx The output index of the new input. @param InOutputChannel The channel of the output to connect. @param InPreInit Called on the new input before initialisation.
- L177 _public function_ `template<typename InInputClass> InInputClass* ChangeInput(int32 InInputIdx, int32 InInputChannel, int32 InOutputIdx, int32 InOutputChannel, FInputInitFunctionPtr InPreInit = nullptr)`
- L185 _public function_ `template<typename InInputClass> InInputClass* ChangeInput(TSubclassOf<UDMMaterialStageInput> InInputSubclass, int32 InInputIdx, int32 InInputChannel, int32 InOutputIdx, int32 InOutputChannel, FInputInitFunctionPtr InPreInit = nullptr)`
- L194 _public prototype_ `UDMMaterialStageSource* ChangeInput_PreviousStage(int32 InInputIdx, int32 InInputChannel, EDMMaterialPropertyType InPreviousStageProperty, int32 InOutputIdx, int32 InOutputChannel);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Changes the input of the given input index to the output of the previous stage with the given material property.
- L198 _public prototype_ `void RemoveUnusedInputs();` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L202 _public prototype_ `bool VerifyAllInputMaps();` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Returns true if any changes were made
- L206 _public prototype_ `bool VerifyInputMap(int32 InInputIdx);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Returns true if any changes were made
- L209 _public prototype_ `void GeneratePreviewMaterial(UMaterial* InPreviewMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L211 _public prototype_ `const FDMMaterialStageConnectorChannel* FindInputChannel(UDMMaterialStageInput* InStageInput);`
- L221 _public prototype_ `void UpdateInputMap(int32 InInputIdx, int32 InSourceIndex, int32 InInputChannel, int32 InOutputIdx, int32 InOutputChannel, EDMMaterialPropertyType InStageProperty);` — Changes the input mapping. @param InInputIdx Index of the source input. @param InInputChannel The channel of the input that the input connects to. @param InOutputIdx The output index of the new input. @param InOutputChannel The channel of the output to connect. @param InStageProperty The property for previous stage connections.
- L226 _public prototype_ `int32 FindIndex() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Returns the index of this stage in the layer.
- L229 _public prototype_ `UDMMaterialStage* GetPreviousStage() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L232 _public prototype_ `UDMMaterialStage* GetNextStage() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L235 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L236 _public prototype_ `virtual FSlateIcon GetComponentIcon() const override;`
- L237 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType) override;`
- L238 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L239 _public prototype_ `virtual UDMMaterialComponent* GetParentComponent() const override;`
- L240 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L244 _public prototype_ `virtual bool Modify(bool bInAlwaysMarkDirty = true) override;`
- L245 _public prototype_ `virtual void PostEditUndo() override;`
- L250 _protected member_ `TObjectPtr<UDMMaterialStageSource> Source;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L253 _protected member_ `TArray<TObjectPtr<UDMMaterialStageInput>> Inputs;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L257 _protected member_ `TArray<FDMMaterialStageConnection> InputConnectionMap;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — How our inputs connect to the inputs of this stage's source
- L260 _protected member_ `bool bEnabled;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L263 _protected member_ `bool bCanChangeSource;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L266 _protected prototype_ `virtual void OnComponentAdded() override;`
- L267 _protected prototype_ `virtual void OnComponentRemoved() override;`
- L268 _protected prototype_ `virtual void GetComponentPathInternal(TArray<FString>& OutChildComponentPathComponents) const override;`
- L269 _protected prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialStageBlend.h` (Public)


#### class `UDMMaterialStageBlend`  
`class UDMMaterialStageBlend : public UDMMaterialStageThroughput`  
_L26-138_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Stage Blend"))`
- inherits: `UDMMaterialStageThroughput`
- desc: A node which represents a blend operation.
- L31 _public member_ `static constexpr int32 InputAlpha = 0;`
- L32 _public member_ `static constexpr int32 InputA = 1;`
- L33 _public member_ `static constexpr int32 InputB = 2;`
- L35 _public prototype_ `static UDMMaterialStage* CreateStage(TSubclassOf<UDMMaterialStageBlend> InMaterialStageBlendClass, UDMMaterialLayerObject* InLayer = nullptr);`
- L37 _public prototype_ `static const TArray<TStrongObjectPtr<UClass>>& GetAvailableBlends();`
- L39 _public prototype_ `UDMMaterialStageBlend();`
- L41 _public prototype_ `UDMMaterialValueFloat1* GetInputAlpha() const;`
- L42 _public prototype_ `UDMMaterialStageInput* GetInputB() const;`
- L45 _public prototype_ `EAvaColorChannel GetBaseChannelOverride() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L48 _public prototype_ `void SetBaseChannelOverride(EAvaColorChannel InMaskChannel);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L51 _public prototype_ `const FText& GetBlendDescription() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L54 _public prototype_ `template<class InNodeType> static void CreateBlendOpacityLayer(const TSharedRef<FDMMaterialBuildState>& InBuildState, UMaterialExpression* InBaseLayerOpacityExpression, int32 InBaseOutputIndex, int32 InBaseOutputChannel, UMaterialExpression* InMyLayerOpacityExpression, int32 InMyOutputIndex, int32 InMyOutputChannel, TArray<UMaterialExpression*>& OutAddedExpressions, int32& OutOutputIndex, int32& OutOutputChannel);`
- L62 _public prototype_ `virtual void BlendOpacityLayer(const TSharedRef<FDMMaterialBuildState>& InBuildState, UMaterialExpression* InBaseLayerOpacityExpression, int32 InBaseOutputIndex, int32 InBaseOutputChannel, UMaterialExpression* InMyLayerOpacityExpression, int32 InMyOutputIndex, int32 InMyOutputChannel, TArray<UMaterialExpression*>& OutAddedExpressions, int32& OutOutputIndex, int32& OutOutputChannel) const;` — When building the opacity (mask) base input, combines the previous layer's alpha output with this ones.
- L67 _public prototype_ `UDMMaterialStageInputValue* GetOpacityValue(UDMMaterialStage* InStage) const;`
- L70 _public prototype_ `virtual bool CanInputAcceptType(int32 InputIndex, EDMValueType ValueType) const override;`
- L71 _public prototype_ `virtual void AddDefaultInput(int32 InInputIndex) const override;`
- L72 _public prototype_ `virtual bool CanChangeInput(int32 InputIndex) const override;`
- L73 _public prototype_ `virtual bool CanChangeInputType(int32 InputIndex) const override;`
- L74 _public prototype_ `virtual bool IsInputVisible(int32 InputIndex) const override;`
- L75 _public prototype_ `virtual int32 ResolveInput(const TSharedRef<FDMMaterialBuildState>& InBuildState, int32 InputIndex, FDMMaterialStageConnectorChannel& OutChannel, TArray<UMaterialExpression*>& OutExpressions) const override;`
- L77 _public prototype_ `virtual void OnPostInputAdded(int32 InInputIdx) override;`
- L81 _public prototype_ `virtual FText GetStageDescription() const override;`
- L82 _public prototype_ `virtual bool SupportsLayerMaskTextureUVLink() const override;`
- L83 _public prototype_ `virtual FDMExpressionInput GetLayerMaskLinkTextureUVInputExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L84 _public prototype_ `virtual void GetMaskAlphaBlendNode(const TSharedRef<FDMMaterialBuildState>& InBuildState, UMaterialExpression*& OutExpression, int32& OutOutputIndex, int32& OutOutputChannel) const override;`
- L86 _public prototype_ `virtual bool GenerateStagePreviewMaterial(UDMMaterialStage* InStage, UMaterial* InPreviewMaterial, UMaterialExpression*& OutMaterialExpression, int32& OutputIndex) override;`
- L91 _public prototype_ `virtual FSlateIcon GetComponentIcon() const override;`
- L92 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType) override;`
- L96 _public prototype_ `virtual void PostEditUndo() override;`
- L97 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L101 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, class FEditPropertyChain* InPropertyThatChanged) override;`
- L105 _protected member_ `static TArray<TStrongObjectPtr<UClass>> Blends;`
- L107 _protected prototype_ `static void GenerateBlendList();`
- L112 _protected member_ `mutable EAvaColorChannel BaseChannelOverride;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Getter, Setter, BlueprintGetter = GetBaseChannelOverride, Category = "Material Designer", DisplayName = "Channel Mask", meta = (NotKeyframeable, ToolTip = "Changes the output channel of the base input."))`
- L116 _protected member_ `FText BlendDescription;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Getter, BlueprintGetter = GetBlendDescription, Category = "Material Designer")`
- L118 _protected prototype_ `UDMMaterialStageBlend(const FText& InName, const FText& InDescription);`
- L121 _protected prototype_ `bool CanUseBaseChannelOverride() const;` — Returns true if there are any outputs on the base input that have more than 1 channel.
- L124 _protected prototype_ `int32 GetDefaultBaseChannelOverrideOutputIndex() const;` — Returns the first output on the base input that has more than 1 channel.
- L127 _protected prototype_ `bool IsValidBaseChannelOverrideOutputIndex(int32 InIndex) const;` — Returns true if the given base output supports more than 1 channel.
- L130 _protected prototype_ `void PullBaseChannelOverride() const;` — Reads the current output setting from the input map.
- L133 _protected prototype_ `void PushBaseChannelOverride();` — Takes the override setting and applies it to the input map.
- L136 _protected prototype_ `virtual void GeneratePreviewMaterial(UMaterial* InPreviewMaterial) override;`
- L141 _function_ `template<class InNodeType> void UDMMaterialStageBlend::CreateBlendOpacityLayer(const TSharedRef<FDMMaterialBuildState>& InBuildState, UMaterialExpression* InBaseLayerOpacityExpression, int32 InBaseOutputIndex, int32 InBaseOutputChannel, UMaterialExpression* InMyLayerOpacityExpression, int32 InMyOutputIndex, int32 InMyOutputChannel, TArray<UMaterialExpression*>& OutAddedExpressions, int32& OutOutputIndex, int32& OutOutputChannel)`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialStageBlendFunction.h` (Public)


#### class `UDMMaterialStageBlendFunction`  
`class UDMMaterialStageBlendFunction : public UDMMaterialStageBlend`  
_L14-38_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlend`
- desc: A blending stage based on a material function.
- L19 _public prototype_ `UDMMaterialStageBlendFunction();`
- L22 _public prototype_ `virtual void ConnectOutputToInput(const TSharedRef<FDMMaterialBuildState>& InBuildState, int32 InInputIdx, int32 InExpressionInputIndex, UMaterialExpression* InSourceExpression, int32 InSourceOutputIndex, int32 InSourceOutputChannel) override;`
- L27 _public prototype_ `virtual void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L32 _protected member_ `TObjectPtr<UMaterialFunctionInterface> MaterialFunction;` — `UPROPERTY()`
- L34 _protected prototype_ `UDMMaterialStageBlendFunction(const FText& InName, const FText& InDescription, UMaterialFunctionInterface* InMaterialFunction);`
- L37 _protected prototype_ `UDMMaterialStageBlendFunction(const FText& InName, const FText& InDescription, const FName& InFunctionName, const FString& InFunctionPath);` — Loads the function asset.

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialStageExpression.h` (Public)


#### enum `EDMExpressionMenu`  
`enum class EDMExpressionMenu : uint8`  
_L17-30_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `Camera`
- L20 _public enumerator_ `Decal`
- L21 _public enumerator_ `Geometry`
- L22 _public enumerator_ `Landscape`
- L23 _public enumerator_ `Math`
- L24 _public enumerator_ `Object`
- L25 _public enumerator_ `Other`
- L26 _public enumerator_ `Particle`
- L27 _public enumerator_ `Texture`
- L28 _public enumerator_ `Time`
- L29 _public enumerator_ `WorldSpace`

#### class `UDMMaterialStageExpression`  
`class UDMMaterialStageExpression : public UDMMaterialStageThroughput`  
_L36-85_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Stage Expression"))`
- inherits: `UDMMaterialStageThroughput`
- desc: A node which directly represents a material expression (or function).
- L41 _public member_ `static TSet<FName> BlockedMaterialExpressionClasses;`
- L43 _public prototype_ `static UDMMaterialStage* CreateStage(TSubclassOf<UDMMaterialStageExpression> InMaterialStageExpressionClass, UDMMaterialLayerObject* InLayer = nullptr);`
- L47 _public prototype_ `static TSubclassOf<UMaterialExpression> FindClass(FString InClassName);` — Some expressions are either exported or not at random. Use this to find ones that aren't.
- L49 _public prototype_ `UDMMaterialStageExpression();`
- L51 _public prototype_ `static const TArray<TStrongObjectPtr<UClass>>& GetAvailableSourceExpressions();`
- L54 _public prototype_ `static UDMMaterialStageExpression* ChangeStageSource_Expression(UDMMaterialStage* InStage, TSubclassOf<UDMMaterialStageExpression> InExpressionClass);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L58 _public function_ `template<typename InExpressionClass> static UDMMaterialStageExpression* ChangeStageSource_Expression(UDMMaterialStage* InStage)`
- L64 _public function_ `TSubclassOf<UMaterialExpression> GetMaterialExpressionClass() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L67 _public function_ `const TArray<EDMExpressionMenu>& GetMenus() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L70 _public prototype_ `virtual void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L74 _protected member_ `static TArray<TStrongObjectPtr<UClass>> SourceExpressions;`
- L76 _protected prototype_ `static void GenerateExpressionList();`
- L79 _protected member_ `TSubclassOf<UMaterialExpression> MaterialExpressionClass;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L82 _protected member_ `TArray<EDMExpressionMenu> Menus;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L84 _protected prototype_ `UDMMaterialStageExpression(const FText& InName, TSubclassOf<UMaterialExpression> InClass);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialStageFunction.h` (Public)


#### class `UDMMaterialStageFunction`  
`class UDMMaterialStageFunction : public UDMMaterialStageThroughput`  
_L13-85_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageThroughput`
- desc: Represents a material function which can be added directly to a stage.
- L18 _public member_ `static constexpr int32 InputPreviousStage = 0;`
- L20 _public member_ `static TSoftObjectPtr<UMaterialFunctionInterface> NoOp;`
- L22 _public prototype_ `static UDMMaterialStage* CreateStage(UDMMaterialLayerObject* InLayer = nullptr);`
- L25 _public prototype_ `static UDMMaterialStageFunction* ChangeStageSource_Function(UDMMaterialStage* InStage, UMaterialFunctionInterface* InMaterialFunction);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L28 _public prototype_ `static UMaterialFunctionInterface* GetNoOpFunction();`
- L30 _public prototype_ `UDMMaterialStageFunction();`
- L33 _public function_ `UMaterialFunctionInterface* GetMaterialFunction() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L36 _public prototype_ `void SetMaterialFunction(UMaterialFunctionInterface* InMaterialFunction);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L39 _public prototype_ `UDMMaterialValue* GetInputValue(int32 InIndex) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L42 _public prototype_ `TArray<UDMMaterialValue*> GetInputValues() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L45 _public prototype_ `virtual void AddDefaultInput(int32 InInputIndex) const override;`
- L46 _public prototype_ `virtual bool CanChangeInput(int32 InputIndex) const override;`
- L47 _public prototype_ `virtual bool CanChangeInputType(int32 InputIndex) const override;`
- L48 _public prototype_ `virtual bool IsInputVisible(int32 InputIndex) const override;`
- L52 _public prototype_ `virtual void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L56 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L60 _public prototype_ `virtual void PreEditChange(FEditPropertyChain& PropertyAboutToChange) override;`
- L61 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L62 _public prototype_ `virtual void PostLoad() override;`
- L68 _protected member_ `TObjectPtr<UMaterialFunctionInterface> MaterialFunction;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetMaterialFunction, Category = "Material Designer", meta = (DisplayThumbnail = true, AllowPrivateAccess = "true", HighPriority, NotKeyframeable, NoCreate))`
- L71 _protected member_ `TObjectPtr<UMaterialFunctionInterface> MaterialFunction_PreEdit;` — `UPROPERTY(Transient, TextExportTransient)`
- L73 _protected prototype_ `void OnMaterialFunctionChanged();`
- L75 _protected prototype_ `void InitFunction();`
- L77 _protected prototype_ `void DeinitFunction();`
- L79 _protected prototype_ `bool NeedsFunctionInit() const;`
- L82 _protected prototype_ `virtual void OnComponentAdded() override;`
- L83 _protected prototype_ `virtual void OnComponentRemoved() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialStageGradient.h` (Public)


#### class `UDMMaterialStageGradient`  
`class UDMMaterialStageGradient : public UDMMaterialStageThroughput`  
_L22-72_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Stage Gradient"))`
- inherits: `UDMMaterialStageThroughput`
- desc: A node which represents UV-based gradient.
- L27 _public member_ `static constexpr int32 InputUV = 0;`
- L28 _public member_ `static constexpr int32 InputStart = 1;`
- L29 _public member_ `static constexpr int32 InputEnd = 2;`
- L32 _public prototype_ `static UDMMaterialStage* CreateStage(TSubclassOf<UDMMaterialStageGradient> InMaterialStageGradientClass, UDMMaterialLayerObject* InLayer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L34 _public prototype_ `static const TArray<TStrongObjectPtr<UClass>>& GetAvailableGradients();`
- L37 _public prototype_ `static UDMMaterialStageGradient* ChangeStageSource_Gradient(UDMMaterialStage* InStage, TSubclassOf<UDMMaterialStageGradient> InGradientClass);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L41 _public function_ `template<typename InGradientClass> static UDMMaterialStageGradient* ChangeStageSource_Gradient(UDMMaterialStage* InStage)`
- L46 _public prototype_ `UDMMaterialStageGradient();`
- L49 _public prototype_ `virtual bool CanChangeInputType(int32 InputIndex) const override;`
- L50 _public prototype_ `virtual void AddDefaultInput(int32 InInputIndex) const override;`
- L54 _public prototype_ `virtual void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L55 _public function_ `virtual bool SupportsLayerMaskTextureUVLink() const override`
- L56 _public function_ `virtual int32 GetLayerMaskTextureUVLinkInputIndex() const override`
- L60 _protected member_ `static TArray<TStrongObjectPtr<UClass>> Gradients;`
- L62 _protected prototype_ `static void GenerateGradientList();`
- L66 _protected member_ `TObjectPtr<UMaterialFunctionInterface> MaterialFunction;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Designer", meta = (DisplayThumbnail = true, AllowPrivateAccess = "true", NoCreate))`
- L68 _protected prototype_ `UDMMaterialStageGradient(const FText& InName);`
- L71 _protected prototype_ `bool SetMaterialFunction(UMaterialFunctionInterface* InMaterialFunction);` — Always set the function. Returns whether an update was called.

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialStageInput.h` (Public)


#### class `UDMMaterialStageInput`  
`class UDMMaterialStageInput : public UDMMaterialStageSource`  
_L16-42_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Stage Input"))`
- inherits: `UDMMaterialStageSource`
- desc: A node which produces an output (e.g. Texture coordinate.)
- L21 _public member_ `static const FString StageInputPrefixStr;`
- L23 _public prototype_ `virtual FText GetChannelDescription(const FDMMaterialStageConnectorChannel& Channel) PURE_VIRTUAL(UDMMaterialStageInput::GetChannelDescription, return FText::GetEmpty();)`
- L28 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType) override;`
- L33 _protected function_ `virtual void UpdateOutputConnectors()` — Updates the output connectors based on the type of input.
- L36 _protected prototype_ `virtual void GeneratePreviewMaterial(UMaterial* InPreviewMaterial) override;`
- L40 _protected prototype_ `virtual void GetComponentPathInternal(TArray<FString>& OutChildComponentPathComponents) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialStageSource.h` (Public)


#### class `UDMMaterialStageSource`  
`class UDMMaterialStageSource : public UDMMaterialComponent`  
_L19-96_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Stage Source"))`
- inherits: `UDMMaterialComponent`
- desc: A node which produces an output.
- L26 _public prototype_ `static const TArray<TStrongObjectPtr<UClass>>& GetAvailableSourceClasses();`
- L29 _public prototype_ `UDMMaterialStage* GetStage() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L33 _public function_ `virtual FText GetStageDescription() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns a description of the stage for which this is the source.
- L36 _public function_ `const TArray<FDMMaterialStageConnector>& GetOutputConnectors() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L39 _public prototype_ `virtual void GetMaskAlphaBlendNode(const TSharedRef<FDMMaterialBuildState>& InBuildState, UMaterialExpression*& OutExpression, int32& OutOutputIndex, int32& OutOutputChannel) const;` — For pre-multiplied alpha, this retrieves the node which should be multiplied against.
- L42 _public function_ `virtual void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const PURE_VIRTUAL(UDMMaterialStageSource::GenerateExpressions) virtual void AddExpressionProperties(const TArray<UMaterialExpression*>& Expressions) const`
- L53 _public prototype_ `virtual void GeneratePreviewMaterial(UMaterial* InPreviewMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Generates a material representing just this node.
- L59 _public prototype_ `virtual int32 GetInnateMaskOutput(int32 OutputIndex, int32 OutputChannels) const;` — Returns the output index (channel WHOLE_CHANNEL) if this expression has pre-masked outputs. Returns INDEX_NONE if it is not supported.
- L66 _public function_ `virtual int32 GetOutputChannelOverride(int32 InOutputIndex) const` — Given an output index, may return an override for output channels on that output. E.g. The texture sample alpha output may override to FOURTH_CHANNEL. Returns INDEX_NONE with no override.
- L69 _public prototype_ `virtual bool GenerateStagePreviewMaterial(UDMMaterialStage* InStage, UMaterial* InPreviewMaterial, UMaterialExpression*& OutMaterialExpression, int32& OutputIndex);` — Generates a preview material based on this source, as owned by the given stage.
- L73 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, class FEditPropertyChain* InPropertyThatChanged) override;`
- L77 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType) override;`
- L78 _public prototype_ `virtual UDMMaterialComponent* GetParentComponent() const override;`
- L82 _public prototype_ `virtual void PostEditUndo() override;`
- L86 _protected member_ `static TArray<TStrongObjectPtr<UClass>> SourceClasses;`
- L88 _protected prototype_ `static void GenerateClassList();`
- L91 _protected member_ `TArray<FDMMaterialStageConnector> OutputConnectors;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L94 _protected prototype_ `virtual void OnComponentAdded() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialStageThroughput.h` (Public)


#### struct `FDMExpressionInput`  
`struct FDMExpressionInput`  
_L15-25_
- L17 _public member_ `TArray<UMaterialExpression*> OutputExpressions = {};`
- L18 _public member_ `int32 OutputIndex = INDEX_NONE;`
- L19 _public member_ `int32 OutputChannel = INDEX_NONE;`
- L21 _public function_ `bool IsValid() const`

#### class `UDMMaterialStageThroughput`  
`class UDMMaterialStageThroughput : public UDMMaterialStageSource`  
_L31-167_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Stage Throughput"))`
- inherits: `UDMMaterialStageSource`
- desc: A node which take one or more inputs and produces an output (e.g. Multiply)
- L36 _public prototype_ `static const TArray<TStrongObjectPtr<UClass>>& GetAvailableThroughputs();`
- L38 _public prototype_ `UDMMaterialStageThroughput();`
- L41 _public function_ `const FText& GetDescription() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L45 _public function_ `bool IsInputRequired() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns true if input is required to successfully compile this node.
- L49 _public function_ `bool AllowsNestedInputs() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns true if this node's inputs can have their own inputs.
- L52 _public function_ `const TArray<FDMMaterialStageConnector>& GetInputConnectors() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L55 _public prototype_ `virtual bool CanInputAcceptType(int32 InThroughputInputIndex, EDMValueType InValueType) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L62 _public prototype_ `virtual bool CanInputConnectTo(int32 InThroughputInputIndex, const FDMMaterialStageConnector& InOutputConnector, int32 InOutputChannel, bool bInCheckSingleFloat = false);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Whether the given output connector can connect to this node. @param bInCheckSingleFloat If the initial compatibility check fails, it will again check against a single float.
- L66 _public prototype_ `virtual bool CanChangeInput(int32 InThroughputInputIndex) const;` — Whether the value of the given input change.
- L69 _public prototype_ `virtual bool CanChangeInputType(int32 InThroughputInputIndex) const;` — Whether you can change the type of the given input.
- L72 _public prototype_ `virtual bool IsInputVisible(int32 InThroughputInputIndex) const;` — Whether this input will show up in the Material Designer editor.
- L81 _public prototype_ `virtual void ConnectOutputToInput(const TSharedRef<FDMMaterialBuildState>& InBuildState, int32 InThroughputInputIndex, int32 InExpressionInputIndex, UMaterialExpression* InSourceExpression, int32 InSourceOutputIndex, int32 InSourceOutputChannel);` — Connect the output of a node to the given input of this node. @param InExpressionInputIndex The input index of this node. @param InSourceExpression The node to take the input from. @param InSourceOutputIndex The output index of the source expression. @param InSourceOutputChannel The channel of the output (RGBA).
- L85 _public function_ `virtual bool SupportsLayerMaskTextureUVLink() const` — Returns true if the layer and mask can have their Texture UV linked.
- L88 _public prototype_ `virtual int32 GetLayerMaskTextureUVLinkInputIndex() const;` — Returns the input index for the default implementation of the below method.
- L94 _public prototype_ `virtual FDMExpressionInput GetLayerMaskLinkTextureUVInputExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const;` — Returns all the material nodes requires to create this node's Texture UV input. If you override this method, you do not need to override GetLayerMaskTextureUVLinkInputIndex.
- L101 _public prototype_ `virtual UMaterialExpression* GetExpressionForInput(const TArray<UMaterialExpression*>& InStageSourceExpressions, int32 InThroughputInputIndex, int32 InExpressionInputIndex);` — Override this to redirect inputs to other nodes. Returns the first node in the array by default --> In [ ]-[ ]-[ ] Out -->
- L105 _public prototype_ `virtual void AddDefaultInput(int32 InInputIndex) const;` — When the node is instantiated, this method adds default input values based on type.
- L111 _public prototype_ `virtual int32 ResolveInput(const TSharedRef<FDMMaterialBuildState>& InBuildState, int32 InThroughputInputIndex, FDMMaterialStageConnectorChannel& OutChannel, TArray<UMaterialExpression*>& OutExpressions) const;` — Generates (or retrieves) expressions that produce this input for the node. @return the actual output index of the material expression
- L115 _public prototype_ `virtual int32 ResolveLayerMaskTextureUVLinkInput(const TSharedRef<FDMMaterialBuildState>& InBuildState, int32 InThroughputInputIndex, FDMMaterialStageConnectorChannel& OutChannel, TArray<UMaterialExpression*>& OutExpressions) const;` — If this is on a Mask stage and it is the UV input index, this method is used to retrieve the base stage's UV input.
- L119 _public function_ `virtual void OnInputUpdated(int32 InThroughputInputIndex, EDMUpdateType InUpdateType)` — This is called when the input value of this node's stage is updated.
- L121 _public function_ `virtual void OnPostInputAdded(int32 InInputIdx)`
- L124 _public function_ `virtual FText GetComponentDescription() const override`
- L128 _protected member_ `static TArray<TStrongObjectPtr<UClass>> Throughputs;`
- L130 _protected prototype_ `static void GenerateThroughputList();`
- L133 _protected prototype_ `static int32 ResolveLayerMaskTextureUVLinkInputImpl(const TSharedRef<FDMMaterialBuildState>& InBuildState, const UDMMaterialStageSource* InStageSource, FDMMaterialStageConnectorChannel& OutChannel, TArray<UMaterialExpression*>& OutExpressions);` — @See ResolveLayerMaskTextureUVLinkInput
- L136 _protected prototype_ `UDMMaterialStageThroughput(const FText& InName);`
- L139 _protected member_ `FText Name;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L142 _protected member_ `bool bInputRequired;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L145 _protected member_ `bool bAllowNestedInputs;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L148 _protected member_ `TArray<FDMMaterialStageConnector> InputConnectors;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L151 _protected prototype_ `virtual bool ShouldKeepInput(int32 InThroughputInputIndex);` — When the stage's source is changed, whether the given of input from the previous source should be kept.
- L154 _protected prototype_ `void ConnectOutputToInput_Internal(const TSharedRef<FDMMaterialBuildState>& InBuildState, UMaterialExpression* InTargetExpression, int32 InExpressionInputIndex, UMaterialExpression* InSourceExpression, int32 InSourceOutputIndex, int32 InSourceOutputChannel) const;` — @See ConnectOutputToInput
- L158 _protected prototype_ `virtual int32 ResolveInputChannel(const TSharedRef<FDMMaterialBuildState>& InBuildState, int32 InThroughputInputIndex, int32 InChannelIndex, FDMMaterialStageConnectorChannel& OutChannel, TArray<UMaterialExpression*>& OutExpressions) const;` — Finds the input for the individual channel. @see ResolveInput
- L162 _protected prototype_ `virtual void GeneratePreviewMaterial(UMaterial* InPreviewMaterial);` — Generates a material based on the output of just this node.
- L165 _protected prototype_ `virtual void OnComponentAdded() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialStageThroughputLayerBlend.h` (Public)


#### class `UDMMaterialStageThroughputLayerBlend`  
`class UDMMaterialStageThroughputLayerBlend : public UDMMaterialStageThroughput`  
_L15-148_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageThroughput`
- desc: Used as the source for mask stages.
- L20 _public member_ `static constexpr int32 InputPreviousLayer = 0;`
- L21 _public member_ `static constexpr int32 InputBaseStage = 1;`
- L22 _public member_ `static constexpr int32 InputMaskSource = 2;`
- L25 _public prototype_ `static UDMMaterialStage* CreateStage(UDMMaterialLayerObject* InLayer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L27 _public prototype_ `UDMMaterialStageThroughputLayerBlend();`
- L31 _public prototype_ `UDMMaterialStageInput* GetInputMask() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Returns the input connected to the Mask input.
- L35 _public prototype_ `EAvaColorChannel GetMaskChannelOverride() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Filters the output of the mask input node with the given channel.
- L39 _public prototype_ `void SetMaskChannelOverride(EAvaColorChannel InMaskChannel);` — `UFUNCTION(BlueprintCallable, Category="Material Designer")` — Filters the output of the mask input node with the given channel.
- L42 _public prototype_ `virtual FSlateIcon GetComponentIcon() const override;`
- L43 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType) override;`
- L44 _public prototype_ `virtual void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L45 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L46 _public prototype_ `virtual bool IsPropertyVisible(FName InProperty) const override;`
- L50 _public prototype_ `virtual FText GetStageDescription() const override;`
- L51 _public prototype_ `virtual bool GenerateStagePreviewMaterial(UDMMaterialStage* InStage, UMaterial* InPreviewMaterial, UMaterialExpression*& OutMaterialExpression, int32& OutputIndex) override;`
- L56 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, class FEditPropertyChain* InPropertyThatChanged) override;`
- L58 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L62 _public prototype_ `virtual void AddDefaultInput(int32 InInputIndex) const override;`
- L63 _public prototype_ `virtual bool CanChangeInput(int32 InputIndex) const override;`
- L64 _public prototype_ `virtual bool IsInputVisible(int32 InputIndex) const override;`
- L65 _public prototype_ `virtual int32 ResolveInput(const TSharedRef<FDMMaterialBuildState>& InBuildState, int32 InputIndex, FDMMaterialStageConnectorChannel& OutChannel, TArray<UMaterialExpression*>& OutExpressions) const override;`
- L67 _public prototype_ `virtual void ConnectOutputToInput(const TSharedRef<FDMMaterialBuildState>& InBuildState, int32 InInputIdx, int32 InExpressionInputIndex, UMaterialExpression* InSourceExpression, int32 InSourceOutputIndex, int32 InSourceOutputChannel) override;`
- L69 _public prototype_ `virtual void OnPostInputAdded(int32 InInputIdx) override;`
- L73 _public prototype_ `void GetMaskOutput(const TSharedRef<FDMMaterialBuildState>& InBuildState, UMaterialExpression*& OutExpression, int32& OutOutputIndex, int32& OutOutputChannel) const;` — Resolves the Mask input.
- L77 _public function_ `bool UsePremultiplyAlpha() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — When true, the base stage's output will be multiplied by this stage (darkening it where it is translucent).
- L81 _public prototype_ `void SetPremultiplyAlpha(bool bInValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — When true, the base stage's output will be multiplied by this stage (darkening it where it is translucent).
- L84 _public prototype_ `virtual void PostLoad() override;`
- L85 _public prototype_ `virtual void PostEditImport() override;`
- L86 _public prototype_ `virtual void PostEditUndo() override;`
- L93 _protected member_ `mutable EAvaColorChannel MaskChannelOverride;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Getter=GetMaskChannelOverride, Setter=SetMaskChannelOverride, BlueprintGetter=GetMaskChannelOverride, Category = "Material Designer", DisplayName = "Channel Mask", meta=(NotKeyframeable))` — Changes the output channel of the mask input.
- L97 _protected member_ `bool bPremultiplyAlpha;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer", meta=(NotKeyframeable))` — Additionally multiplies the output of the RGB Stage by the output from this Stage.
- L101 _protected member_ `bool bIsAlphaOnlyBlend;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer", meta=(NotKeyframeable))`
- L104 _protected member_ `bool bBlockUpdate;` — When doing an update, this will prevent recursive calls.
- L106 _protected prototype_ `virtual int32 ResolveMaskInput(const TSharedRef<FDMMaterialBuildState>& InBuildState, int32 InputIndex, FDMMaterialStageConnectorChannel& OutChannel, TArray<UMaterialExpression*>& OutExpressions) const;`
- L110 _protected prototype_ `virtual void UpdateAlphaOnlyMaskStatus();` — Updates the value of bIsAlphaOnlyBlend based on current conditions.
- L113 _protected prototype_ `virtual void OnStageUpdated(UDMMaterialComponent* InComponent, UDMMaterialComponent* InSource, EDMUpdateType InUpdateType);` — Called when the owning stage is updated.
- L116 _protected prototype_ `virtual void UpdateAlphaOnlyMasks(EDMUpdateType InUpdateType);` — Update this and all parent layer mask stages that are only-only (no based).
- L118 _protected prototype_ `void InitBlendStage();`
- L120 _protected prototype_ `void GenerateMainExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const;`
- L121 _protected prototype_ `void GeneratePreviewExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const;`
- L124 _protected prototype_ `void UpdateLinkedInputStage(EDMUpdateType InUpdateType);` — If this shades any inputs with the base stage, update the base stage.
- L127 _protected prototype_ `bool CanUseMaskChannelOverride() const;` — Returns true if there are any outputs on the mask input that have more than 1 channel.
- L130 _protected prototype_ `int32 GetDefaultMaskChannelOverrideOutputIndex() const;` — Returns the first output on the mask input that has more than 1 channel.
- L133 _protected prototype_ `bool IsValidMaskChannelOverrideOutputIndex(int32 InIndex) const;` — Returns true if the given mask output supports more than 1 channel.
- L136 _protected prototype_ `void PullMaskChannelOverride() const;` — Reads the current output setting from the input map.
- L139 _protected prototype_ `void PushMaskChannelOverride();` — Takes the override setting and applies it to the input map.
- L142 _protected prototype_ `virtual void GeneratePreviewMaterial(UMaterial* InPreviewMaterial) override;`
- L146 _protected prototype_ `virtual void OnComponentAdded() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/DMMaterialSubStage.h` (Public)


#### class `UDMMaterialSubStage`  
`class UDMMaterialSubStage : public UDMMaterialStage`  
_L12-58_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Sub Stage"))`
- inherits: `UDMMaterialStage`
- desc: A stage that is a subobject of another stage, such as when an input throughput has its own inputs.
- L20 _public prototype_ `static UDMMaterialSubStage* CreateMaterialSubStage(UDMMaterialStage* InParentStage);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L24 _public prototype_ `UDMMaterialStage* GetParentStage() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the parent stage of this stage, which is probably not its direct parent.
- L28 _public prototype_ `UDMMaterialStage* GetParentMostStage() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Recursively calls GetParentStage() to find the outer stage.
- L32 _public prototype_ `void SetParentComponent(UDMMaterialComponent* InParentComponent);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Sets which object directly owns this component in the hierarchy.
- L35 _public prototype_ `virtual bool IsCompatibleWithPreviousStage(const UDMMaterialStage* PreviousStage) const override;`
- L36 _public prototype_ `virtual bool IsCompatibleWithNextStage(const UDMMaterialStage* NextStage) const override;`
- L40 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType) override;`
- L41 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L42 _public prototype_ `virtual UDMMaterialComponent* GetParentComponent() const override;`
- L43 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L48 _protected member_ `TObjectPtr<UDMMaterialStage> ParentStage;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L51 _protected member_ `TObjectPtr<UDMMaterialComponent> ParentComponent;` — `UPROPERTY()`
- L53 _protected function_ `UDMMaterialSubStage() : ParentStage(nullptr) , ParentComponent(nullptr)`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBAdd.h` (Public)


#### class `UDMMaterialStageBlendAdd`  
`class UDMMaterialStageBlendAdd : public UDMMaterialStageBlendFunction`  
_L10-23_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- desc: The same as linear dodge
- L15 _public prototype_ `UDMMaterialStageBlendAdd();`
- L18 _public prototype_ `virtual void BlendOpacityLayer(const TSharedRef<FDMMaterialBuildState>& InBuildState, UMaterialExpression* InBaseLayerOpacityExpression, int32 InBaseOutputIndex, int32 InBaseOutputChannel, UMaterialExpression* InMyLayerOpacityExpression, int32 InMyOutputIndex, int32 InMyOutputChannel, TArray<UMaterialExpression*>& OutAddedExpressions, int32& OutOutputIndex, int32& OutOutputChannel) const;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBColor.h` (Public)


#### class `UDMMaterialStageBlendColor`  
`class UDMMaterialStageBlendColor : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendColor();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBColorBurn.h` (Public)


#### class `UDMMaterialStageBlendColorBurn`  
`class UDMMaterialStageBlendColorBurn : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendColorBurn();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBColorDodge.h` (Public)


#### class `UDMMaterialStageBlendColorDodge`  
`class UDMMaterialStageBlendColorDodge : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendColorDodge();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBContrastBase.h` (Public)


#### class `UDMMaterialStageBlendContrastBase`  
`class UDMMaterialStageBlendContrastBase : public UDMMaterialStageBlend`  
_L12-21_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlend`
- L17 _public prototype_ `UDMMaterialStageBlendContrastBase(const FText& InName, const FText& InDescription);`
- L20 _private prototype_ `UDMMaterialStageBlendContrastBase();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBDarken.h` (Public)


#### class `UDMMaterialStageBlendDarken`  
`class UDMMaterialStageBlendDarken : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendDarken();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBDarkenColor.h` (Public)


#### class `UDMMaterialStageBlendDarkenColor`  
`class UDMMaterialStageBlendDarkenColor : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendDarkenColor();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBDifference.h` (Public)


#### class `UDMMaterialStageBlendDifference`  
`class UDMMaterialStageBlendDifference : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendDifference();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBDivide.h` (Public)


#### class `UDMMaterialStageBlendDivide`  
`class UDMMaterialStageBlendDivide : public UDMMaterialStageBlendFunction`  
_L9-22_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendDivide();`
- L17 _public prototype_ `virtual void BlendOpacityLayer(const TSharedRef<FDMMaterialBuildState>& InBuildState, UMaterialExpression* InBaseLayerOpacityExpression, int32 InBaseOutputIndex, int32 InBaseOutputChannel, UMaterialExpression* InMyLayerOpacityExpression, int32 InMyOutputIndex, int32 InMyOutputChannel, TArray<UMaterialExpression*>& OutAddedExpressions, int32& OutOutputIndex, int32& OutOutputChannel) const;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBExclusion.h` (Public)


#### class `UDMMaterialStageBlendExclusion`  
`class UDMMaterialStageBlendExclusion : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendExclusion();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBHardLight.h` (Public)


#### class `UDMMaterialStageBlendHardLight`  
`class UDMMaterialStageBlendHardLight : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendHardLight();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBHardMix.h` (Public)


#### class `UDMMaterialStageBlendHardMix`  
`class UDMMaterialStageBlendHardMix : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendHardMix();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBHue.h` (Public)


#### class `UDMMaterialStageBlendHue`  
`class UDMMaterialStageBlendHue : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendHue();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBLighten.h` (Public)


#### class `UDMMaterialStageBlendLighten`  
`class UDMMaterialStageBlendLighten : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendLighten();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBLightenColor.h` (Public)


#### class `UDMMaterialStageBlendLightenColor`  
`class UDMMaterialStageBlendLightenColor : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendLightenColor();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBLinearBurn.h` (Public)


#### class `UDMMaterialStageBlendLinearBurn`  
`class UDMMaterialStageBlendLinearBurn : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendLinearBurn();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBLinearDodge.h` (Public)


#### class `UDMMaterialStageBlendLinearDodge`  
`class UDMMaterialStageBlendLinearDodge : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendLinearDodge();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBLinearLight.h` (Public)


#### class `UDMMaterialStageBlendLinearLight`  
`class UDMMaterialStageBlendLinearLight : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendLinearLight();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBLuminosity.h` (Public)


#### class `UDMMaterialStageBlendLuminosity`  
`class UDMMaterialStageBlendLuminosity : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendLuminosity();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBMultiply.h` (Public)


#### class `UDMMaterialStageBlendMultiply`  
`class UDMMaterialStageBlendMultiply : public UDMMaterialStageBlendFunction`  
_L9-22_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendMultiply();`
- L17 _public prototype_ `virtual void BlendOpacityLayer(const TSharedRef<FDMMaterialBuildState>& InBuildState, UMaterialExpression* InBaseLayerOpacityExpression, int32 InBaseOutputIndex, int32 InBaseOutputChannel, UMaterialExpression* InMyLayerOpacityExpression, int32 InMyOutputIndex, int32 InMyOutputChannel, TArray<UMaterialExpression*>& OutAddedExpressions, int32& OutOutputIndex, int32& OutOutputChannel) const;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBNormal.h` (Public)


#### class `UDMMaterialStageBlendNormal`  
`class UDMMaterialStageBlendNormal : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendNormal();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBOverlay.h` (Public)


#### class `UDMMaterialStageBlendOverlay`  
`class UDMMaterialStageBlendOverlay : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendOverlay();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBPinLight.h` (Public)


#### class `UDMMaterialStageBlendPinLight`  
`class UDMMaterialStageBlendPinLight : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendPinLight();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBSaturation.h` (Public)


#### class `UDMMaterialStageBlendSaturation`  
`class UDMMaterialStageBlendSaturation : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendSaturation();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBScreen.h` (Public)


#### class `UDMMaterialStageBlendScreen`  
`class UDMMaterialStageBlendScreen : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendScreen();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBSoftLight.h` (Public)


#### class `UDMMaterialStageBlendSoftLight`  
`class UDMMaterialStageBlendSoftLight : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendSoftLight();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBSubtract.h` (Public)


#### class `UDMMaterialStageBlendSubtract`  
`class UDMMaterialStageBlendSubtract : public UDMMaterialStageBlendFunction`  
_L9-22_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendSubtract();`
- L17 _public prototype_ `virtual void BlendOpacityLayer(const TSharedRef<FDMMaterialBuildState>& InBuildState, UMaterialExpression* InBaseLayerOpacityExpression, int32 InBaseOutputIndex, int32 InBaseOutputChannel, UMaterialExpression* InMyLayerOpacityExpression, int32 InMyOutputIndex, int32 InMyOutputChannel, TArray<UMaterialExpression*>& OutAddedExpressions, int32& OutOutputIndex, int32& OutOutputChannel) const;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageBlends/DMMSBVividLight.h` (Public)


#### class `UDMMaterialStageBlendVividLight`  
`class UDMMaterialStageBlendVividLight : public UDMMaterialStageBlendFunction`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageBlendFunction`
- L14 _public prototype_ `UDMMaterialStageBlendVividLight();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageExpressions/DMMSEMathBase.h` (Public)


#### class `UDMMaterialStageExpressionMathBase`  
`class UDMMaterialStageExpressionMathBase : public UDMMaterialStageExpression`  
_L12-54_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L17 _public prototype_ `UDMMaterialStageExpressionMathBase(const FText& InName, TSubclassOf<UMaterialExpression> InClass);`
- L20 _public prototype_ `virtual bool CanInputAcceptType(int32 InInputIndex, EDMValueType InValueType) const override;`
- L21 _public prototype_ `virtual void AddDefaultInput(int32 InInputIndex) const override;`
- L25 _public prototype_ `virtual bool GenerateStagePreviewMaterial(UDMMaterialStage* InStage, UMaterial* InPreviewMaterial, UMaterialExpression*& OutMaterialExpression, int32& OutputIndex) override;`
- L30 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType) override;`
- L36 _protected member_ `bool bSingleChannelOnly;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — Whether this just works with Scalars.
- L40 _protected member_ `int32 VariadicInputCount;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — How many inputs this should automatically create.
- L44 _protected member_ `bool bAllowSingleFloatMatch;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — Allow matching of single floats to match other types of floats.
- L46 _protected prototype_ `UDMMaterialStageExpressionMathBase();`
- L49 _protected prototype_ `void SetupInputs(int32 InCount);` — Add automatic inputs (A-O (15)))
- L52 _protected prototype_ `virtual void GeneratePreviewMaterial(UMaterial* InPreviewMaterial) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageExpressions/DMMSETextureCoordinate.h` (Public)


#### class `UDMMaterialStageExpressionTextureCoordinate`  
`class UDMMaterialStageExpressionTextureCoordinate : public UDMMaterialStageExpression`  
_L9-29_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionTextureCoordinate();`
- L17 _public prototype_ `virtual void AddExpressionProperties(const TArray<UMaterialExpression*>& InExpressions) const override;`
- L22 _protected member_ `int32 CoordinateIndex;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L25 _protected member_ `float UTiling;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L28 _protected member_ `float VTiling;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageExpressions/DMMSETextureSample.h` (Public)


#### class `UDMMaterialStageExpressionTextureSample`  
`class UDMMaterialStageExpressionTextureSample : public UDMMaterialStageExpressionTextureSampleBase`  
_L10-49_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpressionTextureSampleBase`
- L17 _public prototype_ `UDMMaterialStageExpressionTextureSample();`
- L20 _public prototype_ `bool GetUseBaseTexture() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L23 _public prototype_ `void SetUseBaseTexture(bool bInUseBaseTexture);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L26 _public prototype_ `bool CanUseBaseTexture() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L28 _public prototype_ `const UDMMaterialStageExpressionTextureSample* GetBaseTextureSample() const;`
- L31 _public prototype_ `virtual void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L32 _public prototype_ `virtual bool IsPropertyVisible(FName InProperty) const override;`
- L36 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L46 _protected member_ `bool bUseBaseTexture;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Getter = GetUseBaseTexture, Setter = SetUseBaseTexture, BlueprintGetter = GetUseBaseTexture, Category = "Material Designer", DisplayName = "Use Base Texture", meta = (NotKeyframeable))` — When both the base and mask stages are set to a texture and toggle layer UV link is on, use the texture sampler from base stage directly in the mask stage, with no mask stage texture sampler.
- L48 _protected prototype_ `void OnUseBaseTextureChanged();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageExpressions/DMMSETextureSampleBase.h` (Public)


#### class `UDMMaterialStageExpressionTextureSampleBase`  
`class UDMMaterialStageExpressionTextureSampleBase : public UDMMaterialStageExpression`  
_L9-58_
- reflection: `UCLASS(minimalAPI, BlueprintType, Blueprintable, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression`
- L14 _public prototype_ `UDMMaterialStageExpressionTextureSampleBase();`
- L17 _public function_ `virtual bool IsClampTextureEnabled() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L20 _public prototype_ `virtual void SetClampTextureEnabled(bool bInValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L23 _public prototype_ `virtual void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L27 _public prototype_ `virtual void OnComponentAdded() override;`
- L28 _public prototype_ `virtual bool IsPropertyVisible(FName Property) const override;`
- L29 _public prototype_ `virtual void AddExpressionProperties(const TArray<UMaterialExpression*>& InExpressions) const override;`
- L30 _public prototype_ `virtual int32 GetInnateMaskOutput(int32 InOutputIndex, int32 InOutputChannels) const override;`
- L31 _public prototype_ `virtual int32 GetOutputChannelOverride(int32 InOutputIndex) const override;`
- L35 _public prototype_ `virtual bool CanChangeInputType(int32 InInputIndex) const override;`
- L36 _public function_ `virtual bool SupportsLayerMaskTextureUVLink() const override`
- L37 _public function_ `virtual int32 GetLayerMaskTextureUVLinkInputIndex() const override`
- L38 _public prototype_ `virtual void OnInputUpdated(int32 InInputIndex, EDMUpdateType InUpdateType) override;`
- L42 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L43 _public prototype_ `virtual FSlateIcon GetComponentIcon() const override;`
- L47 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L53 _protected member_ `bool bClampTexture;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter = SetClampTextureEnabled, BlueprintSetter = SetClampTextureEnabled, Category = "Material Designer", DisplayName = "Clamp Texture UV", meta = (ToolTip = "Forces a material rebuild.", LowPriority, NotKeyframeable, AllowPrivateAccess = "true"))`
- L55 _protected prototype_ `UDMMaterialStageExpressionTextureSampleBase(const FText& InName, TSubclassOf<UMaterialExpression> InClass);`
- L57 _protected prototype_ `void UpdateMask();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageExpressions/DMMSETextureSampleEdgeColor.h` (Public)


#### enum `EDMEdgeLocation`  
`enum class EDMEdgeLocation : uint8`  
_L10-22_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `TopLeft`
- L13 _public enumerator_ `Top`
- L14 _public enumerator_ `TopRight`
- L15 _public enumerator_ `Left`
- L16 _public enumerator_ `Center`
- L17 _public enumerator_ `Right`
- L18 _public enumerator_ `BottomLeft`
- L19 _public enumerator_ `Bottom`
- L20 _public enumerator_ `BottomRight`
- L21 _public enumerator_ `Custom`

#### class `UDMMaterialStageExpressionTextureSampleEdgeColor`  
`class UDMMaterialStageExpressionTextureSampleEdgeColor : public UDMMaterialStageExpression, public IDMParameterContainer`  
_L25-61_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageExpression,IDMParameterContainer`
- L30 _public prototype_ `UDMMaterialStageExpressionTextureSampleEdgeColor();`
- L33 _public prototype_ `virtual bool CanChangeInputType(int32 InInputIndex) const override;`
- L34 _public prototype_ `virtual void AddDefaultInput(int32 InInputIndex) const override;`
- L38 _public prototype_ `virtual void AddExpressionProperties(const TArray<UMaterialExpression*>& InExpressions) const override;`
- L42 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType) override;`
- L46 _public prototype_ `virtual void PreEditChange(FEditPropertyChain& InPropertyAboutToChange) override;`
- L47 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L51 _public prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`
- L56 _protected member_ `EDMEdgeLocation EdgeLocation;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer", meta=(AllowPrivateAccess = "true"))`
- L58 _protected member_ `EDMEdgeLocation PreEditEdgeLocation;`
- L60 _protected prototype_ `void OnEdgeLocationChanged();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageGradients/DMMSGLinear.h` (Public)


#### enum `ELinearGradientTileType`  
`enum class ELinearGradientTileType : uint8`  
_L12-17_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `NoTile`
- L15 _public enumerator_ `Tile`
- L16 _public enumerator_ `TileAndMirror`

#### class `UDMMaterialStageGradientLinear`  
`class UDMMaterialStageGradientLinear : public UDMMaterialStageGradient`  
_L20-50_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageGradient`
- L25 _public prototype_ `UDMMaterialStageGradientLinear();`
- L28 _public function_ `virtual ELinearGradientTileType GetTilingType() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L31 _public prototype_ `virtual void SetTilingType(ELinearGradientTileType InType);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L34 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L35 _public prototype_ `virtual void PostEditUndo() override;`
- L39 _protected member_ `static TSoftObjectPtr<UMaterialFunctionInterface> LinearGradientNoTileFunction;`
- L40 _protected member_ `static TSoftObjectPtr<UMaterialFunctionInterface> LinearGradientTileFunction;`
- L41 _protected member_ `static TSoftObjectPtr<UMaterialFunctionInterface> LinearGradientTileAndMirrorFunction;`
- L45 _protected member_ `ELinearGradientTileType Tiling;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter = GetTilingType, Setter=SetTilingType, BlueprintSetter = SetTilingType, Category = "Material Designer")`
- L47 _protected prototype_ `UMaterialFunctionInterface* GetMaterialFunctionForTilingType(ELinearGradientTileType) const;`
- L49 _protected prototype_ `void OnTilingChanged();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageGradients/DMMSGRadial.h` (Public)


#### class `UDMMaterialStageGradientRadial`  
`class UDMMaterialStageGradientRadial : public UDMMaterialStageGradient`  
_L12-20_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageGradient`
- L16 _private prototype_ `UDMMaterialStageGradientRadial();`
- L19 _public member_ `static TSoftObjectPtr<UMaterialFunctionInterface> RadialGradientFunction;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageInputs/DMMSIExpression.h` (Public)


#### class `UDMMaterialStageInputExpression`  
`class UDMMaterialStageInputExpression : public UDMMaterialStageInputThroughput`  
_L14-67_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageInputThroughput`
- L20 _public prototype_ `static UDMMaterialStage* CreateStage(TSubclassOf<UDMMaterialStageExpression> InMaterialStageExpressionClass, UDMMaterialLayerObject* InLayer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L22 _public prototype_ `static const TArray<TStrongObjectPtr<UClass>>& GetAvailableInputExpressions();`
- L25 _public prototype_ `static UDMMaterialStageInputExpression* ChangeStageSource_Expression(UDMMaterialStage* InStage, TSubclassOf<UDMMaterialStageExpression> InExpressionClass);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L29 _public function_ `template<typename InExpressionClass> static UDMMaterialStageInputExpression* ChangeStageSource_Expression(UDMMaterialStage* InStage)`
- L42 _public prototype_ `static UDMMaterialStageInputExpression* ChangeStageInput_Expression(UDMMaterialStage* InStage, TSubclassOf<UDMMaterialStageExpression> InExpressionClass, int32 InInputIdx, int32 InInputChannel, int32 InOutputIdx, int32 InOutputChannel);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Change the input type of an input on a stage to an expression. @param InInputIdx Index of the source input. @param InInputChannel The channel of the input that the input connects to. @param InOutputIdx The output index of the new input. @param InOutputChannel The channel of the output to connect.
- L47 _public function_ `template<typename InExpressionClass> static UDMMaterialStageInputExpression* ChangeStageInput_Expression(UDMMaterialStage* InStage, int32 InInputIdx, int32 InInputChannel, int32 InOutputIdx, int32 InOutputChannel)`
- L55 _public prototype_ `TSubclassOf<UDMMaterialStageExpression> GetMaterialStageExpressionClass() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L58 _public prototype_ `void SetMaterialStageExpressionClass(TSubclassOf<UDMMaterialStageExpression> InMaterialStageExpressionClass);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L61 _public prototype_ `UDMMaterialStageExpression* GetMaterialStageExpression() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L64 _protected member_ `static TArray<TStrongObjectPtr<UClass>> InputExpressions;`
- L66 _protected prototype_ `static void GenerateExpressionList();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageInputs/DMMSIFunction.h` (Public)


#### class `UDMMaterialStageInputFunction`  
`class UDMMaterialStageInputFunction : public UDMMaterialStageInputThroughput`  
_L13-47_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageInputThroughput`
- L19 _public prototype_ `static UDMMaterialStage* CreateStage(UDMMaterialLayerObject* InLayer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L22 _public prototype_ `static UDMMaterialStageInputFunction* ChangeStageSource_Function(UDMMaterialStage* InStage, UMaterialFunctionInterface* InMaterialFunction);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L33 _public prototype_ `static UDMMaterialStageInputFunction* ChangeStageInput_Function(UDMMaterialStage* InStage, UMaterialFunctionInterface* InMaterialFunction, int32 InInputIdx, int32 InInputChannel, int32 InOutputIdx, int32 InOutputChannel);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Change the input type of an input on a stage to a function. @param InInputIdx Index of the source input. @param InInputChannel The channel of the input that the input connects to. @param InOutputIdx The output index of the new input. @param InOutputChannel The channel of the output to connect.
- L37 _public prototype_ `void Init();`
- L40 _public prototype_ `UDMMaterialStageFunction* GetMaterialStageFunction() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L43 _public prototype_ `UMaterialFunctionInterface* GetMaterialFunction() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L46 _public prototype_ `void SetMaterialFunction(UMaterialFunctionInterface* InMaterialFunction);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageInputs/DMMSIGradient.h` (Public)


#### class `UDMMaterialStageInputGradient`  
`class UDMMaterialStageInputGradient : public UDMMaterialStageInputThroughput`  
_L14-64_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageInputThroughput`
- L20 _public prototype_ `static UDMMaterialStage* CreateStage(TSubclassOf<UDMMaterialStageGradient> InMaterialStageGradientClass, UDMMaterialLayerObject* InLayer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L22 _public prototype_ `static const TArray<TStrongObjectPtr<UClass>>& GetAvailableGradients();`
- L25 _public prototype_ `static UDMMaterialStageInputGradient* ChangeStageSource_Gradient(UDMMaterialStage* InStage, TSubclassOf<UDMMaterialStageGradient> InGradientClass);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L29 _public function_ `template<typename InGradientClass> static UDMMaterialStageInputGradient* ChangeStageSource_Gradient(UDMMaterialStage* InStage)`
- L41 _public prototype_ `static UDMMaterialStageInputGradient* ChangeStageInput_Gradient(UDMMaterialStage* InStage, TSubclassOf<UDMMaterialStageGradient> InGradientClass, int32 InInputIdx, int32 InInputChannel, int32 InOutputChannel);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Change the input type of an input on a stage to a gradient. @param InInputIdx Index of the source input. @param InInputChannel The channel of the input that the input connects to. @param InOutputChannel The channel of the output to connect.
- L45 _public function_ `template<typename InGradientClass> static UDMMaterialStageInputGradient* ChangeStageInput_Gradient(UDMMaterialStage* InStage, int32 InInputIdx, int32 InInputChannel, int32 InOutputChannel)`
- L52 _public prototype_ `TSubclassOf<UDMMaterialStageGradient> GetMaterialStageGradientClass() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L55 _public prototype_ `void SetMaterialStageGradientClass(TSubclassOf<UDMMaterialStageGradient> InMaterialStageGradientClass);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L58 _public prototype_ `UDMMaterialStageGradient* GetMaterialStageGradient() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L61 _protected member_ `static TArray<TStrongObjectPtr<UClass>> Gradients;`
- L63 _protected prototype_ `static void GenerateGradientList();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageInputs/DMMSISlot.h` (Public)


#### class `UDMMaterialStageInputSlot`  
`class UDMMaterialStageInputSlot : public UDMMaterialStageInput`  
_L15-97_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageInput`
- L20 _public member_ `static const FString SlotPathToken;`
- L23 _public prototype_ `static UDMMaterialStage* CreateStage(UDMMaterialSlot* InSourceSlot, EDMMaterialPropertyType InMaterialProperty, UDMMaterialLayerObject* InLayer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L27 _public prototype_ `static UDMMaterialStageInputSlot* ChangeStageSource_Slot(UDMMaterialStage* InStage, UDMMaterialSlot* InSlot, EDMMaterialPropertyType InProperty);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L39 _public prototype_ `static UDMMaterialStageInputSlot* ChangeStageInput_Slot(UDMMaterialStage* InStage, int32 InInputIdx, int32 InInputChannel, UDMMaterialSlot* InSlot, EDMMaterialPropertyType InProperty, int32 InOutputIdx, int32 InOutputChannel);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Change the input type of an input on a stage to the output of another slot. @param InInputIdx Index of the source input. @param InInputChannel The channel of the input that the input connects to. @param InProperty The property of the slot to use. @param InOutputIdx The output index of the new input. @param InOutputChannel The channel of the output to connect.
- L42 _public prototype_ `UDMMaterialStageInputSlot();`
- L45 _public function_ `UDMMaterialSlot* GetSlot() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L48 _public function_ `EDMMaterialPropertyType GetMaterialProperty() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L51 _public prototype_ `void SetSlot(UDMMaterialSlot* InSlot);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L54 _public prototype_ `void SetMaterialProperty(EDMMaterialPropertyType InMaterialProperty);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L57 _public prototype_ `virtual FText GetChannelDescription(const FDMMaterialStageConnectorChannel& Channel) override;`
- L61 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L62 _public prototype_ `virtual FSlateIcon GetComponentIcon() const override;`
- L63 _public prototype_ `virtual void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L64 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L68 _public prototype_ `virtual void PostLoad() override;`
- L69 _public prototype_ `virtual void PostEditImport() override;`
- L74 _protected member_ `TObjectPtr<UDMMaterialSlot> Slot;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L77 _protected member_ `EDMMaterialPropertyType MaterialProperty;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L79 _protected prototype_ `virtual ~UDMMaterialStageInputSlot() override = default;`
- L81 _protected prototype_ `void OnSlotUpdated(UDMMaterialComponent* InComponent, UDMMaterialComponent* InSource, EDMUpdateType InUpdateType);`
- L82 _protected prototype_ `void OnSlotConnectorsUpdated(UDMMaterialSlot* InSlot);`
- L83 _protected prototype_ `void OnSlotRemoved(UDMMaterialComponent* InComponent, EDMComponentLifetimeState InLifetimeState);`
- L84 _protected prototype_ `void OnParentSlotRemoved(UDMMaterialComponent* InComponent, EDMComponentLifetimeState InLifetimeState);`
- L86 _protected prototype_ `void InitSlot();`
- L87 _protected prototype_ `void DeinitSlot();`
- L90 _protected prototype_ `virtual void UpdateOutputConnectors() override;`
- L94 _protected prototype_ `virtual void OnComponentRemoved() override;`
- L95 _protected prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageInputs/DMMSITextureUV.h` (Public)


#### class `UDMMaterialStageInputTextureUV`  
`class UDMMaterialStageInputTextureUV : public UDMMaterialStageInput`  
_L22-89_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageInput`
- L27 _public member_ `static const FString TextureUVPathToken;`
- L30 _public prototype_ `static UDMMaterialStage* CreateStage(UDynamicMaterialModel* InMaterialModel, UDMMaterialLayerObject* InLayer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L33 _public prototype_ `static UDMMaterialStageInputTextureUV* ChangeStageSource_UV(UDMMaterialStage* InStage, bool bInDoUpdate);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L36 _public prototype_ `static UDMMaterialStageInputTextureUV* ChangeStageInput_UV(UDMMaterialStage* InStage, int32 InInputIdx, int32 InInputChannel, int32 InOutputChannel);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L39 _public prototype_ `UDMMaterialStageInputTextureUV();`
- L41 _public prototype_ `virtual ~UDMMaterialStageInputTextureUV() override = default;`
- L43 _public prototype_ `void Init(UDynamicMaterialModel* InMaterialModel);`
- L46 _public function_ `UDMTextureUV* GetTextureUV()` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L49 _public prototype_ `virtual FText GetChannelDescription(const FDMMaterialStageConnectorChannel& Channel) override;`
- L53 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L54 _public prototype_ `virtual FSlateIcon GetComponentIcon() const override;`
- L55 _public prototype_ `virtual void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L56 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L60 _public prototype_ `virtual bool Modify(bool bInAlwaysMarkDirty = true) override;`
- L61 _public prototype_ `virtual void PostLoad() override;`
- L62 _public prototype_ `virtual void PostEditImport() override;`
- L66 _protected prototype_ `static UMaterialExpressionScalarParameter* CreateScalarParameter(const TSharedRef<FDMMaterialBuildState>& InBuildState, FName InParamName, EDMMaterialParameterGroup InParameterGroup, float InValue = 0.f);`
- L69 _protected prototype_ `static TArray<UMaterialExpression*> CreateTextureUVExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState, UDMTextureUV* InTextureUV);`
- L72 _protected member_ `TObjectPtr<UDMTextureUV> TextureUV;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L74 _protected prototype_ `void OnTextureUVUpdated(UDMMaterialComponent* InComponent, UDMMaterialComponent* InSource, EDMUpdateType InUpdateType);`
- L76 _protected prototype_ `void InitTextureUV();`
- L78 _protected prototype_ `void AddEffects(const TSharedRef<FDMMaterialBuildState>& InBuildState, TArray<UMaterialExpression*>& InOutExpressions) const;`
- L81 _protected prototype_ `virtual void UpdateOutputConnectors() override;`
- L85 _protected prototype_ `virtual void OnComponentAdded() override;`
- L86 _protected prototype_ `virtual void OnComponentRemoved() override;`
- L87 _protected prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageInputs/DMMSIThroughput.h` (Public)


#### class `UDMMaterialStageInputThroughput`  
`class UDMMaterialStageInputThroughput : public UDMMaterialStageInput`  
_L15-72_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageInput`
- L20 _public member_ `static const FString SubStagePathToken;`
- L22 _public prototype_ `UDMMaterialStageInputThroughput();`
- L25 _public prototype_ `TSubclassOf<UDMMaterialStageThroughput> GetMaterialStageThroughputClass() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L28 _public prototype_ `UDMMaterialStageThroughput* GetMaterialStageThroughput() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L31 _public function_ `UDMMaterialSubStage* GetSubStage() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L34 _public prototype_ `virtual FText GetChannelDescription(const FDMMaterialStageConnectorChannel& Channel) override;`
- L38 _public prototype_ `virtual void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L39 _public prototype_ `virtual int32 GetInnateMaskOutput(int32 OutputIndex, int32 OutputChannels) const;`
- L40 _public prototype_ `virtual int32 GetOutputChannelOverride(int32 InOutputIndex) const override;`
- L44 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L45 _public prototype_ `virtual FSlateIcon GetComponentIcon() const override;`
- L46 _public prototype_ `virtual bool IsPropertyVisible(FName Property) const override;`
- L47 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L51 _public prototype_ `virtual bool Modify(bool bInAlwaysMarkDirty = true) override;`
- L52 _public prototype_ `virtual void PostLoad() override;`
- L53 _public prototype_ `virtual void PostEditImport() override;`
- L58 _protected member_ `TObjectPtr<UDMMaterialSubStage> SubStage;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L60 _protected prototype_ `void OnSubStageUpdated(UDMMaterialComponent* InComponent, UDMMaterialComponent* InSource, EDMUpdateType InUpdateType);`
- L62 _protected prototype_ `void SetMaterialStageThroughputClass(TSubclassOf<UDMMaterialStageThroughput> InMaterialStageThroughputClass);`
- L64 _protected prototype_ `void InitSubStage();`
- L67 _protected prototype_ `virtual void OnComponentAdded() override;`
- L68 _protected prototype_ `virtual void OnComponentRemoved() override;`
- L69 _protected prototype_ `virtual void GetComponentPathInternal(TArray<FString>& OutChildComponentPathComponents) const override;`
- L70 _protected prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Components/MaterialStageInputs/DMMSIValue.h` (Public)


#### class `UDMMaterialStageInputValue`  
`class UDMMaterialStageInputValue : public UDMMaterialStageInput`  
_L16-117_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialStageInput`
- L21 _public member_ `static const FString ValuePathToken;`
- L23 _public function_ `static FName GetValuePropertyName()`
- L26 _public prototype_ `static UDMMaterialStage* CreateStage(UDMMaterialValue* InValue, UDMMaterialLayerObject* InLayer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L28 _public prototype_ `static UDMMaterialStageInputValue* ChangeStageSource_NewLocalValue(UDMMaterialStage* InStage, EDMValueType InValueType);`
- L31 _public prototype_ `static UDMMaterialStageInputValue* ChangeStageSource_NewLocalValue(UDMMaterialStage* InStage, TSubclassOf<UDMMaterialValue> InValueClass);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L34 _public prototype_ `static UDMMaterialStageInputValue* ChangeStageSource_Value(UDMMaterialStage* InStage, UDMMaterialValue* InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L36 _public prototype_ `static UDMMaterialStageInputValue* ChangeStageSource_NewValue(UDMMaterialStage* InStage, EDMValueType InValueType);`
- L39 _public prototype_ `static UDMMaterialStageInputValue* ChangeStageSource_NewValue(UDMMaterialStage* InStage, TSubclassOf<UDMMaterialValue> InValueClass);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L41 _public prototype_ `static UDMMaterialStageInputValue* ChangeStageInput_NewLocalValue(UDMMaterialStage* InStage, int32 InInputIdx, int32 InInputChannel, EDMValueType InValueType, int32 InOutputChannel);`
- L45 _public prototype_ `static UDMMaterialStageInputValue* ChangeStageInput_NewLocalValue(UDMMaterialStage* InStage, int32 InInputIdx, int32 InInputChannel, TSubclassOf<UDMMaterialValue> InValueClass, int32 InOutputChannel);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L49 _public prototype_ `static UDMMaterialStageInputValue* ChangeStageInput_Value(UDMMaterialStage* InStage, int32 InInputIdx, int32 InInputChannel, UDMMaterialValue* InValue, int32 InOutputChannel);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L52 _public prototype_ `static UDMMaterialStageInputValue* ChangeStageInput_NewValue(UDMMaterialStage* InStage, int32 InInputIdx, int32 InInputChannel, EDMValueType InValueType, int32 InOutputChannel);`
- L56 _public prototype_ `static UDMMaterialStageInputValue* ChangeStageInput_NewValue(UDMMaterialStage* InStage, int32 InInputIdx, int32 InInputChannel, TSubclassOf<UDMMaterialValue> InValueClass, int32 InOutputChannel);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L59 _public prototype_ `UDMMaterialStageInputValue();`
- L61 _public prototype_ `virtual ~UDMMaterialStageInputValue() override = default;`
- L64 _public function_ `UDMMaterialValue* GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L67 _public prototype_ `void SetValue(UDMMaterialValue* InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L69 _public prototype_ `void ApplyDefaultLayerSettings();`
- L72 _public prototype_ `virtual FText GetChannelDescription(const FDMMaterialStageConnectorChannel& Channel) override;`
- L76 _public prototype_ `virtual int32 GetInnateMaskOutput(int32 OutputIndex, int32 OutputChannels) const override;`
- L80 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L81 _public prototype_ `virtual FSlateIcon GetComponentIcon() const override;`
- L82 _public prototype_ `virtual void GenerateExpressions(const TSharedRef<FDMMaterialBuildState>& InBuildState) const override;`
- L83 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L84 _public prototype_ `virtual bool IsPropertyVisible(FName InProperty) const override;`
- L88 _public prototype_ `virtual bool Modify(bool bInAlwaysMarkDirty = true) override;`
- L89 _public prototype_ `virtual void PostLoad() override;`
- L90 _public prototype_ `virtual void PostEditImport() override;`
- L95 _protected member_ `TObjectPtr<UDMMaterialValue> Value;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L97 _protected prototype_ `void OnValueUpdated(UDMMaterialComponent* InComponent, EDMUpdateType InUpdateType);`
- L99 _protected prototype_ `void InitInputValue();`
- L100 _protected prototype_ `void DeinitInputValue();`
- L102 _protected prototype_ `bool IsSharedStageValue() const;`
- L104 _protected prototype_ `void ApplyWholeLayerValue();`
- L106 _protected prototype_ `bool IsTextureValueVisible() const;`
- L109 _protected prototype_ `virtual void UpdateOutputConnectors() override;`
- L113 _protected prototype_ `virtual void OnComponentAdded() override;`
- L114 _protected prototype_ `virtual void OnComponentRemoved() override;`
- L115 _protected prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/DMEDefs.h` (Public)


#### class `UDMBuildable`  
`class UDMBuildable : public UInterface`  
_L32-36_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UInterface`

#### class `IDMBuildable`  
`class IDMBuildable`  
_L38-47_
- L44 _public prototype_ `void DoBuild(bool bInDirtyAssets);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Material Designer")`
- L46 _public prototype_ `virtual void DoBuild_Implementation(bool bInDirtyAssets) PURE_VIRTUAL(IDMBuildable::DoBuild_Implementation);`

#### struct `FDMMaterialStageConnector`  
`struct FDMMaterialStageConnector`  
_L53-86_
- reflection: `USTRUCT(BlueprintType, Category = "Material Designer", meta = (DisplayName = "Material Designer Stage Connector"))`
- desc: An input or output form a material source/stage (e.g. RGB out.)
- L59 _public member_ `int32 Index = INDEX_NONE;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — This is the index of the input connector on the UMaterialExpression node (not on the stage's input array or the inputconnectors array.)
- L62 _public member_ `FText Name = FText::GetEmpty();` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L65 _public member_ `EDMValueType Type = EDMValueType::VT_Float1;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L67 _public function_ `bool IsCompatibleWith(const FDMMaterialStageConnector& OtherConnector, int32 MyChannel = FDMMaterialStageConnectorChannel::WHOLE_CHANNEL, int32 OtherChannel = FDMMaterialStageConnectorChannel::WHOLE_CHANNEL) const`
- L74 _public function_ `bool IsCompatibleWith(EDMValueType OtherType, int32 MyChannel = FDMMaterialStageConnectorChannel::WHOLE_CHANNEL, int32 OtherChannel = FDMMaterialStageConnectorChannel::WHOLE_CHANNEL) const`
- L81 _public function_ `bool operator==(const FDMMaterialStageConnector& Other) const`

#### struct `FDMMaterialStageConnection`  
`struct FDMMaterialStageConnection`  
_L97-108_
- reflection: `USTRUCT(BlueprintType, Category = "Material Designer", meta = (DisplayName = "Material Designer Stage Connection"))`
- desc: Represents the channels(channel = float, texture, etc.) that connect to an input. Multiple float channels can be combined to create a single put (e.g. R, G, B -> RGB) Individual source channels, from potentially multiple sources, can be directed to specific input channels (e.g. T1.R, T2.B, T3.G -> {T2.B, T1.R, T3.G, T2.B})
- L107 _public member_ `TArray<FDMMaterialStageConnectorChannel> Channels;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — This struct represents the connections made to a single input connector. Can connect single outputs or combine them. Append nodes will be used to combine channels. Combining channels should only be used for float types!

#### struct `FDMMaterialSlotOutputConnectorTypes`  
`struct FDMMaterialSlotOutputConnectorTypes`  
_L111-117_
- reflection: `USTRUCT(BlueprintType, Category = "Material Designer", meta = (DisplayName = "Material Designer Slot Output Connector Types"))`
- L116 _public member_ `TArray<EDMValueType> ConnectorTypes;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`

#### enum `EDMPropertyHandlePriority`  
`enum class EDMPropertyHandlePriority : uint8`  
_L119-124_
- L121 _public enumerator_ `Low`
- L122 _public enumerator_ `Normal`
- L123 _public enumerator_ `High`

#### struct `FDMPropertyGeneratorHandle`  
`struct FDMPropertyGeneratorHandle`  
_L126-131_
- L128 _public member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;`
- L129 _public member_ `TSharedPtr<IDetailTreeNode> DetailTreeNode;`
- L130 _public member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`

#### struct `FDMPropertyHandle`  
`struct FDMPropertyHandle`  
_L133-147_
- L135 _public member_ `FDMPropertyGeneratorHandle OriginalHandle;`
- L136 _public member_ `FDMPropertyGeneratorHandle PreviewHandle;`
- L137 _public member_ `TOptional<FText> NameOverride;`
- L138 _public member_ `TOptional<FText> NameToolTipOverride;`
- L139 _public member_ `TOptional<FResetToDefaultOverride> ResetToDefaultOverride;`
- L140 _public member_ `TSharedPtr<SWidget> ValueWidget;`
- L141 _public member_ `FName ValueName = NAME_None;`
- L142 _public member_ `FName CategoryOverrideName = NAME_None;`
- L143 _public member_ `TOptional<float> MaxWidth;`
- L144 _public member_ `bool bEnabled = true;`
- L145 _public member_ `EDMPropertyHandlePriority Priority = EDMPropertyHandlePriority::Normal;`
- L146 _public member_ `bool bKeyframeable = true;`

#### enum `EDMMaterialLayerStage`  
`enum class EDMMaterialLayerStage : uint8`  
_L150-156_
- reflection: `UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L152 _public enumerator_ `None = 0 UMETA(Hidden)`
- L153 _public enumerator_ `Base = 1 << 0`
- L154 _public enumerator_ `Mask = 1 << 1`
- L155 _public enumerator_ `All = Base | Mask`

#### enum `EAvaColorChannel`  
`enum class EAvaColorChannel : uint8`  
_L160-169_
- reflection: `UENUM(BlueprintType)`
- L162 _public enumerator_ `None = 0`
- L163 _public enumerator_ `Red = 1 << 0`
- L164 _public enumerator_ `Green = 1 << 1`
- L165 _public enumerator_ `Blue = 1 << 2`
- L166 _public enumerator_ `Alpha = 1 << 3`
- L167 _public enumerator_ `RGB = Red|Green|Blue UMETA(Hidden)`
- L168 _public enumerator_ `RGBA = Red|Green|Blue|Alpha UMETA(Hidden)`

#### Free symbols / members of external scopes

- L157 _prototype_ `ENUM_CLASS_FLAGS(EDMMaterialLayerStage);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/DMObjectMaterialProperty.h` (Public)


#### struct `FDMObjectMaterialProperty`  
`struct FDMObjectMaterialProperty`  
_L29-99_
- reflection: `USTRUCT()`
- desc: Defines a material property slot that can be a Material Designer Material.
- L35 _public prototype_ `FDMObjectMaterialProperty();`
- L38 _public prototype_ `FDMObjectMaterialProperty(UPrimitiveComponent* InOuter, int32 InIndex);` — UPrimitiveComponent Material Index
- L41 _public prototype_ `FDMObjectMaterialProperty(UObject* InOuter, FProperty* InProperty, int32 InIndex = INDEX_NONE);` — Class Property (including potential array index)
- L43 _public prototype_ `UObject* GetOuter() const;`
- L45 _public prototype_ `FProperty* GetProperty() const;`
- L47 _public prototype_ `int32 GetIndex() const;`
- L49 _public prototype_ `UDynamicMaterialModelBase* GetMaterialModelBase() const;`
- L51 _public prototype_ `UDynamicMaterialInstance* GetMaterial() const;`
- L53 _public prototype_ `UMaterialInterface* GetMaterialInterface() const;`
- L55 _public prototype_ `bool IsValid() const;`
- L57 _public prototype_ `FText GetPropertyName(bool bInIgnoreNewStatus) const;`
- L59 _public prototype_ `void Reset();`
- L62 _public prototype_ `bool IsProperty() const;` — Whether this is a property on the object.
- L65 _public prototype_ `bool IsElement() const;` — Whether this is an element of a primitive component's material override array.
- L68 _public function_ `template<typename InClass> InClass* GetTypedOuter() const`
- L84 _public prototype_ `void SetMaterialSetterDelegate(const FDMSetMaterialObjectProperty& InDelegate);` — The delegate can be used to override (or preprocess) the material setter function
- L88 _protected member_ `TWeakObjectPtr<UObject> OuterWeak = nullptr;` — `UPROPERTY()`
- L91 _protected member_ `FProperty* Property = nullptr;` — C++ version of property
- L94 _protected member_ `int32 Index = INDEX_NONE;` — Component or array property index.
- L96 _protected member_ `FDMSetMaterialObjectProperty MaterialSetterDelegate;`
- L98 _protected prototype_ `void SetMaterial(UDynamicMaterialInstance* InDynamicMaterial);`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool , FDMSetMaterialObjectProperty, const FDMObjectMaterialProperty& , UDynamicMaterialInstance* ) USTRUCT() struct FDMObjectMaterialProperty { GENERATED_BODY() friend class UDMMaterialInstanceFunctionLibrary; FDMObjectMaterialProperty(); FDMObjectMaterialProperty(UPrimitiveComponent* InOuter, int32 InIndex); FDMObjectMaterialProperty(UObject* InOuter, FProperty* InProperty, int32 InIndex = INDEX_NONE); UObject* GetOuter() const; FProperty* GetProperty() const; int32 GetIndex() const; UDynamicMaterialModelBase* GetMaterialModelBase() const; UDynamicMaterialInstance* GetMaterial() const; UMaterialInterface* GetMaterialInterface() const; bool IsValid() const; FText GetPropertyName(bool bInIgnoreNewStatus) const; void Reset(); bool IsProperty() const;` — Overrides the material setter algorithm. @returns true means that the material was set. False if it was not. If false is returned, the normal material setting algorithm is used.

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/DMWorldSubsystem.h` (Public)


#### class `UDMWorldSubsystem`  
`class UDMWorldSubsystem : public UWorldSubsystem`  
_L27-109_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- L32 _public prototype_ `UDMWorldSubsystem();`
- L34 _public function_ `const TSharedPtr<IDetailKeyframeHandler>& GetKeyframeHandler() const`
- L39 _public function_ `void SetKeyframeHandler(const TSharedPtr<IDetailKeyframeHandler>& InKeyframeHandler)`
- L45 _public function_ `FDMGetMaterialModelDelegate::RegistrationType& GetGetCustomEditorModelDelegate() const` — Gets the material in a custom editor tab.
- L50 _public prototype_ `UDynamicMaterialModelBase* ExecuteGetCustomEditorModelDelegate();`
- L53 _public function_ `FDMSetMaterialModelDelegate::RegistrationType& GetSetCustomEditorModelDelegate() const` — Sets material in a custom editor tab.
- L58 _public prototype_ `void ExecuteSetCustomEditorModelDelegate(UDynamicMaterialModelBase* InMaterialModel);`
- L61 _public function_ `FDMSetMaterialObjectPropertyDelegate::RegistrationType& GetCustomObjectPropertyEditorDelegate() const` — Sets the object property in custom editor tab.
- L66 _public prototype_ `void ExecuteCustomObjectPropertyEditorDelegate(const FDMObjectMaterialProperty& InObjectProperty);`
- L69 _public function_ `FDMSetMaterialActorDelegate::RegistrationType& GetSetCustomEditorActorDelegate() const` — Sets actor in a custom editor tab.
- L74 _public prototype_ `void ExecuteSetCustomEditorActorDelegate(AActor* InActor);`
- L77 _public function_ `FDMIsValidDelegate::RegistrationType& GetIsValidDelegate() const` — Returns true if the supplied material is valid for this world.
- L82 _public prototype_ `bool ExecuteIsValidDelegate(UDynamicMaterialModelBase* InMaterialModel);`
- L85 _public function_ `FDMSetMaterialValueDelegate::RegistrationType& GetMaterialValueSetterDelegate() const` — Used to redirect SetMaterial to different objects/paths.
- L90 _public prototype_ `bool ExecuteMaterialValueSetterDelegate(const FDMObjectMaterialProperty& InObjectProperty, UDynamicMaterialInstance* InMaterialInstance);`
- L93 _public function_ `FDMInvokeTabDelegate::RegistrationType& GetInvokeTabDelegate() const` — Used to show the tab to the user.
- L98 _public prototype_ `void ExecuteInvokeTabDelegate();`
- L101 _protected member_ `TSharedPtr<IDetailKeyframeHandler> KeyframeHandler;`
- L102 _protected member_ `mutable FDMGetMaterialModelDelegate CustomModelEditorGetDelegate;`
- L103 _protected member_ `mutable FDMSetMaterialModelDelegate CustomModelEditorSetDelegate;`
- L104 _protected member_ `mutable FDMSetMaterialObjectPropertyDelegate CustomObjectPropertyEditorDelegate;`
- L105 _protected member_ `mutable FDMSetMaterialActorDelegate CustomActorEditorDelegate;`
- L106 _protected member_ `mutable FDMIsValidDelegate IsValidDelegate;`
- L107 _protected member_ `mutable FDMSetMaterialValueDelegate SetMaterialValueDelegate;`
- L108 _protected member_ `mutable FDMInvokeTabDelegate InvokeTabDelegate;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_RetVal(UDynamicMaterialModelBase*, FDMGetMaterialModelDelegate) DECLARE_DELEGATE_OneParam(FDMSetMaterialModelDelegate, UDynamicMaterialModelBase*) DECLARE_DELEGATE_OneParam(FDMSetMaterialObjectPropertyDelegate, const FDMObjectMaterialProperty&) DECLARE_DELEGATE_OneParam(FDMSetMaterialActorDelegate, AActor*) DECLARE_DELEGATE_RetVal_OneParam(bool, FDMIsValidDelegate, UDynamicMaterialModelBase*) DECLARE_DELEGATE_RetVal_TwoParams(bool, FDMSetMaterialValueDelegate, const FDMObjectMaterialProperty&, UDynamicMaterialInstance*) DECLARE_DELEGATE(FDMInvokeTabDelegate) UCLASS(MinimalAPI) class UDMWorldSubsystem : public UWorldSubsystem { GENERATED_BODY() public: UDMWorldSubsystem(); const TSharedPtr<IDetailKeyframeHandler>& GetKeyframeHandler() const { return KeyframeHandler; } void SetKeyframeHandler(const TSharedPtr<IDetailKeyframeHandler>& InKeyframeHandler) { KeyframeHandler = InKeyframeHandler; } FDMGetMaterialModelDelegate::RegistrationType& GetGetCustomEditorModelDelegate() const { return CustomModelEditorGetDelegate; } UDynamicMaterialModelBase* ExecuteGetCustomEditorModelDelegate(); FDMSetMaterialModelDelegate::RegistrationType& GetSetCustomEditorModelDelegate() const { return CustomModelEditorSetDelegate; }`
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FDMSetMaterialModelDelegate, UDynamicMaterialModelBase*) DECLARE_DELEGATE_OneParam(FDMSetMaterialObjectPropertyDelegate, const FDMObjectMaterialProperty&) DECLARE_DELEGATE_OneParam(FDMSetMaterialActorDelegate, AActor*) DECLARE_DELEGATE_RetVal_OneParam(bool, FDMIsValidDelegate, UDynamicMaterialModelBase*) DECLARE_DELEGATE_RetVal_TwoParams(bool, FDMSetMaterialValueDelegate, const FDMObjectMaterialProperty&, UDynamicMaterialInstance*) DECLARE_DELEGATE(FDMInvokeTabDelegate) UCLASS(MinimalAPI) class UDMWorldSubsystem : public UWorldSubsystem { GENERATED_BODY() public: UDMWorldSubsystem(); const TSharedPtr<IDetailKeyframeHandler>& GetKeyframeHandler() const { return KeyframeHandler; } void SetKeyframeHandler(const TSharedPtr<IDetailKeyframeHandler>& InKeyframeHandler) { KeyframeHandler = InKeyframeHandler; } FDMGetMaterialModelDelegate::RegistrationType& GetGetCustomEditorModelDelegate() const { return CustomModelEditorGetDelegate; } UDynamicMaterialModelBase* ExecuteGetCustomEditorModelDelegate(); FDMSetMaterialModelDelegate::RegistrationType& GetSetCustomEditorModelDelegate() const { return CustomModelEditorSetDelegate; } void ExecuteSetCustomEditorModelDelegate(UDynamicMaterialModelBase* InMaterialModel);`
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FDMSetMaterialObjectPropertyDelegate, const FDMObjectMaterialProperty&) DECLARE_DELEGATE_OneParam(FDMSetMaterialActorDelegate, AActor*) DECLARE_DELEGATE_RetVal_OneParam(bool, FDMIsValidDelegate, UDynamicMaterialModelBase*) DECLARE_DELEGATE_RetVal_TwoParams(bool, FDMSetMaterialValueDelegate, const FDMObjectMaterialProperty&, UDynamicMaterialInstance*) DECLARE_DELEGATE(FDMInvokeTabDelegate) UCLASS(MinimalAPI) class UDMWorldSubsystem : public UWorldSubsystem { GENERATED_BODY() public: UDMWorldSubsystem(); const TSharedPtr<IDetailKeyframeHandler>& GetKeyframeHandler() const { return KeyframeHandler; } void SetKeyframeHandler(const TSharedPtr<IDetailKeyframeHandler>& InKeyframeHandler) { KeyframeHandler = InKeyframeHandler; } FDMGetMaterialModelDelegate::RegistrationType& GetGetCustomEditorModelDelegate() const { return CustomModelEditorGetDelegate; } UDynamicMaterialModelBase* ExecuteGetCustomEditorModelDelegate(); FDMSetMaterialModelDelegate::RegistrationType& GetSetCustomEditorModelDelegate() const { return CustomModelEditorSetDelegate; } void ExecuteSetCustomEditorModelDelegate(UDynamicMaterialModelBase* InMaterialModel);`
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FDMSetMaterialActorDelegate, AActor*) DECLARE_DELEGATE_RetVal_OneParam(bool, FDMIsValidDelegate, UDynamicMaterialModelBase*) DECLARE_DELEGATE_RetVal_TwoParams(bool, FDMSetMaterialValueDelegate, const FDMObjectMaterialProperty&, UDynamicMaterialInstance*) DECLARE_DELEGATE(FDMInvokeTabDelegate) UCLASS(MinimalAPI) class UDMWorldSubsystem : public UWorldSubsystem { GENERATED_BODY() public: UDMWorldSubsystem(); const TSharedPtr<IDetailKeyframeHandler>& GetKeyframeHandler() const { return KeyframeHandler; } void SetKeyframeHandler(const TSharedPtr<IDetailKeyframeHandler>& InKeyframeHandler) { KeyframeHandler = InKeyframeHandler; } FDMGetMaterialModelDelegate::RegistrationType& GetGetCustomEditorModelDelegate() const { return CustomModelEditorGetDelegate; } UDynamicMaterialModelBase* ExecuteGetCustomEditorModelDelegate(); FDMSetMaterialModelDelegate::RegistrationType& GetSetCustomEditorModelDelegate() const { return CustomModelEditorSetDelegate; } void ExecuteSetCustomEditorModelDelegate(UDynamicMaterialModelBase* InMaterialModel);`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FDMIsValidDelegate, UDynamicMaterialModelBase*) DECLARE_DELEGATE_RetVal_TwoParams(bool, FDMSetMaterialValueDelegate, const FDMObjectMaterialProperty&, UDynamicMaterialInstance*) DECLARE_DELEGATE(FDMInvokeTabDelegate) UCLASS(MinimalAPI) class UDMWorldSubsystem : public UWorldSubsystem { GENERATED_BODY() public: UDMWorldSubsystem(); const TSharedPtr<IDetailKeyframeHandler>& GetKeyframeHandler() const { return KeyframeHandler; } void SetKeyframeHandler(const TSharedPtr<IDetailKeyframeHandler>& InKeyframeHandler) { KeyframeHandler = InKeyframeHandler; } FDMGetMaterialModelDelegate::RegistrationType& GetGetCustomEditorModelDelegate() const { return CustomModelEditorGetDelegate; } UDynamicMaterialModelBase* ExecuteGetCustomEditorModelDelegate(); FDMSetMaterialModelDelegate::RegistrationType& GetSetCustomEditorModelDelegate() const { return CustomModelEditorSetDelegate; } void ExecuteSetCustomEditorModelDelegate(UDynamicMaterialModelBase* InMaterialModel); FDMSetMaterialObjectPropertyDelegate::RegistrationType& GetCustomObjectPropertyEditorDelegate() const`
- L23 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FDMSetMaterialValueDelegate, const FDMObjectMaterialProperty&, UDynamicMaterialInstance*) DECLARE_DELEGATE(FDMInvokeTabDelegate) UCLASS(MinimalAPI) class UDMWorldSubsystem : public UWorldSubsystem { GENERATED_BODY() public: UDMWorldSubsystem(); const TSharedPtr<IDetailKeyframeHandler>& GetKeyframeHandler() const { return KeyframeHandler; } void SetKeyframeHandler(const TSharedPtr<IDetailKeyframeHandler>& InKeyframeHandler) { KeyframeHandler = InKeyframeHandler; } FDMGetMaterialModelDelegate::RegistrationType& GetGetCustomEditorModelDelegate() const { return CustomModelEditorGetDelegate; } UDynamicMaterialModelBase* ExecuteGetCustomEditorModelDelegate(); FDMSetMaterialModelDelegate::RegistrationType& GetSetCustomEditorModelDelegate() const { return CustomModelEditorSetDelegate; } void ExecuteSetCustomEditorModelDelegate(UDynamicMaterialModelBase* InMaterialModel); FDMSetMaterialObjectPropertyDelegate::RegistrationType& GetCustomObjectPropertyEditorDelegate() const {`
- L24 _delegate_ `DECLARE_DELEGATE(FDMInvokeTabDelegate) UCLASS(MinimalAPI) class UDMWorldSubsystem : public UWorldSubsystem { GENERATED_BODY() public: UDMWorldSubsystem(); const TSharedPtr<IDetailKeyframeHandler>& GetKeyframeHandler() const { return KeyframeHandler; } void SetKeyframeHandler(const TSharedPtr<IDetailKeyframeHandler>& InKeyframeHandler) { KeyframeHandler = InKeyframeHandler; } FDMGetMaterialModelDelegate::RegistrationType& GetGetCustomEditorModelDelegate() const { return CustomModelEditorGetDelegate; } UDynamicMaterialModelBase* ExecuteGetCustomEditorModelDelegate(); FDMSetMaterialModelDelegate::RegistrationType& GetSetCustomEditorModelDelegate() const { return CustomModelEditorSetDelegate; } void ExecuteSetCustomEditorModelDelegate(UDynamicMaterialModelBase* InMaterialModel); FDMSetMaterialObjectPropertyDelegate::RegistrationType& GetCustomObjectPropertyEditorDelegate() const { return CustomObjectPropertyEditorDelegate;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/IDynamicMaterialEditorModule.h` (Public)


#### struct `FDMComponentPropertyRowGeneratorParams`  
`struct FDMComponentPropertyRowGeneratorParams`  
_L26-46_
- L28 _public member_ `const SWidget* Owner = nullptr;`
- L29 _public member_ `FNotifyHook* NotifyHook = nullptr;`
- L30 _public member_ `UDynamicMaterialModelBase* PreviewMaterialModelBase = nullptr;`
- L31 _public member_ `UDynamicMaterialModelBase* OriginalMaterialModelBase = nullptr;`
- L32 _public member_ `UObject* Object = nullptr;`
- L33 _public member_ `TNotNull<TArray<FDMPropertyHandle>*> PropertyRows;`
- L34 _public member_ `TSet<UObject*>& ProcessedObjects;`
- L36 _public function_ `FDMComponentPropertyRowGeneratorParams(TArray<FDMPropertyHandle>& InPropertyRows, TSet<UObject*>& InProcessedObjects) : PropertyRows(&InPropertyRows) , ProcessedObjects(InProcessedObjects)`
- L42 _public function_ `FDMPropertyHandleGenerateParams CreatePropertyHandleParams(FName InPropertyName) const`

#### class `IDynamicMaterialEditorModule`  
`class IDynamicMaterialEditorModule : public IModuleInterface`  
_L54-114_
- inherits: `IModuleInterface`
- desc: Material Designer - Build your own materials in a slimline editor!
- L57 _protected member_ `static constexpr const TCHAR* ModuleName = TEXT("Dyn`
- L60 _public function_ `static bool IsLoaded()`
- L65 _public function_ `static IDynamicMaterialEditorModule& Get()`
- L70 _public prototype_ `virtual void RegisterComponentPropertyRowGeneratorDelegate(UClass* InClass, FDMComponentPropertyRowGeneratorDelegate InComponentPropertyRowGeneratorDelegate) = 0;`
- L73 _public function_ `template <class InObjClass, class InGenClass> void RegisterComponentPropertyRowGeneratorDelegate()`
- L84 _public prototype_ `virtual void RegisterCustomMaterialPropertyGenerator(UClass* InClass, FDMGetObjectMaterialPropertiesDelegate InGenerator) = 0;`
- L86 _public prototype_ `virtual void RegisterMaterialModelCreatedCallback(const TSharedRef<IDMOnWizardCompleteCallback> InCallback) = 0;`
- L88 _public prototype_ `virtual void UnregisterMaterialModelCreatedCallback(const TSharedRef<IDMOnWizardCompleteCallback> InCallback) = 0;`
- L92 _public function_ `TSharedRef<InCallbackType> RegisterMaterialModelCreatedCallback(InArgsType&&... InArgs)`
- L99 _public prototype_ `virtual void OpenEditor(UWorld* InWorld) const = 0;`
- L101 _public prototype_ `virtual UDynamicMaterialModelBase* GetOpenedMaterialModel(UWorld* InWorld) const = 0;`
- L103 _public prototype_ `virtual void OpenMaterialModel(UDynamicMaterialModelBase* InMaterialModel, UWorld* InWorld, bool bInInvokeTab) const = 0;`
- L105 _public prototype_ `virtual void OpenMaterialObjectProperty(const FDMObjectMaterialProperty& InObjectProperty, UWorld* InWorld, bool bInInvokeTab) const = 0;`
- L107 _public prototype_ `virtual void OpenMaterial(UDynamicMaterialInstance* InInstance, UWorld* InWorld, bool bInInvokeTab) const = 0;`
- L109 _public prototype_ `virtual void OnActorSelected(AActor* InActor, UWorld* InWorld, bool bInInvokeTab) const = 0;`
- L111 _public prototype_ `virtual void ClearDynamicMaterialModel(UWorld* InWorld) const = 0;`
- L113 _public prototype_ `virtual IDMWidgetLibrary& GetWidgetLibrary() const = 0;`

#### Free symbols / members of external scopes

- L48 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TArray<FDMObjectMaterialProperty>, FDMGetObjectMaterialPropertiesDelegate, UObject* InObject) DECLARE_DELEGATE_OneParam(FDMComponentPropertyRowGeneratorDelegate, FDMComponentPropertyRowGeneratorParams&) class IDynamicMaterialEditorModule : public IModuleInterface { protected: static constexpr const TCHAR* ModuleName = TEXT("DynamicMaterialEditor"); public: static bool IsLoaded() { return FModuleManager::Get().IsModuleLoaded(ModuleName); } static IDynamicMaterialEditorModule& Get() { return FModuleManager::LoadModuleChecked<IDynamicMaterialEditorModule>(ModuleName); } virtual void RegisterComponentPropertyRowGeneratorDelegate(UClass* InClass, FDMComponentPropertyRowGeneratorDelegate InComponentPropertyRowGeneratorDelegate) = 0; template <class InObjClass, class InGenClass> void RegisterComponentPropertyRowGeneratorDelegate() { RegisterComponentPropertyRowGeneratorDelegate( InObjClass::StaticClass(), FDMComponentPropertyRowGeneratorDelegate::CreateSP( InGenClass::Get(), &InGenClass::AddComponentProperties ) ); } virtual void RegisterCustomMaterialPropertyGenerator(UClass* InClass, FDMGetObjectMaterialPropertiesDelegate InGenerator) = 0; virtual void RegisterMaterialModelCreatedCallback(const TSharedRef<IDMOnWizardCompleteCallback> InCallback) = 0;`
- L51 _delegate_ `DECLARE_DELEGATE_OneParam(FDMComponentPropertyRowGeneratorDelegate, FDMComponentPropertyRowGeneratorParams&) class IDynamicMaterialEditorModule : public IModuleInterface { protected: static constexpr const TCHAR* ModuleName = TEXT("DynamicMaterialEditor"); public: static bool IsLoaded() { return FModuleManager::Get().IsModuleLoaded(ModuleName); } static IDynamicMaterialEditorModule& Get() { return FModuleManager::LoadModuleChecked<IDynamicMaterialEditorModule>(ModuleName); } virtual void RegisterComponentPropertyRowGeneratorDelegate(UClass* InClass, FDMComponentPropertyRowGeneratorDelegate InComponentPropertyRowGeneratorDelegate) = 0; template <class InObjClass, class InGenClass> void RegisterComponentPropertyRowGeneratorDelegate() { RegisterComponentPropertyRowGeneratorDelegate( InObjClass::StaticClass(), FDMComponentPropertyRowGeneratorDelegate::CreateSP( InGenClass::Get(), &InGenClass::AddComponentProperties ) ); } virtual void RegisterCustomMaterialPropertyGenerator(UClass* InClass, FDMGetObjectMaterialPropertiesDelegate InGenerator) = 0; virtual void RegisterMaterialModelCreatedCallback(const TSharedRef<IDMOnWizardCompleteCallback> InCallback) = 0; virtual void UnregisterMaterialModelCreatedCallback(const TSharedRef<IDMOnWizardCompleteCallback> InCallback) = 0; template<typename InCallbackType, typename... InArgsType` — Creates property rows in the edit widget.

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Material/DynamicMaterialInstanceFactory.h` (Public)


#### class `UDynamicMaterialInstanceFactory`  
`class UDynamicMaterialInstanceFactory : public UFactory`  
_L9-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L14 _public prototype_ `UDynamicMaterialInstanceFactory();`
- L17 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`
- L19 _public prototype_ `virtual FText GetDisplayName() const override;`
- L20 _public prototype_ `virtual FText GetToolTip() const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Model/DMMaterialBuildState.h` (Public)


#### struct `FDMMaterialBuildState`  
`struct FDMMaterialBuildState : public IDMMaterialBuildStateInterface, public TSharedFromThis<FDMMaterialBuildState>`  
_L33-174_
- inherits: `IDMMaterialBuildStateInterface,TSharedFromThis<FDMMaterialBuildState>`
- desc: BuildState is a class that stores the current state of a material that is being built. It stores useful lists of UMaterialExpressions relating to various object within the builder, such a Stages or Sources. It is an entirely transient object. It is not meant to be saved outside of the material building processs. It also provides some helper functions for creating UMaterialExpressions.
- L35 _public prototype_ `FDMMaterialBuildState(UMaterial* InDynamicMaterial, UDynamicMaterialModel* InMaterialModel, bool bInDirtyAssets = true);`
- L39 _public prototype_ `virtual UMaterial* GetDynamicMaterial() const override;`
- L41 _public prototype_ `virtual UDynamicMaterialModel* GetMaterialModel() const override;`
- L47 _public prototype_ `const UDMMaterialProperty* GetCurrentMaterialProperty() const;` — The current material property being generated for. May be null in the case of global values or global parameters.
- L49 _public prototype_ `void SetCurrentMaterialProperty(const UDMMaterialProperty* InProperty);`
- L52 _public function_ `bool ShouldDirtyAssets() const` — Whether assets can potentially be dirtied by the build process.
- L55 _public function_ `bool IsIgnoringUVs() const` — If ignoring UVs is on, UV nodes will not be processed. Useful for preview materials.
- L57 _public prototype_ `void SetIgnoreUVs();`
- L60 _public function_ `UObject* GetPreviewObject() const` — Whether the build state is building a full material or a preview.
- L62 _public prototype_ `void SetPreviewObject(UObject* InObject);`
- L65 _public prototype_ `virtual IDMMaterialBuildUtilsInterface& GetBuildUtils() const override;` — A handy set of tools for creating material expressions.
- L68 _public prototype_ `FExpressionInput* GetMaterialProperty(EDMMaterialPropertyType InProperty) const;` — Returns the FExpressionInput for the given material property on the material's editor only data.
- L71 _public prototype_ `bool HasSlot(const UDMMaterialSlot* InSlot) const;` — Slots
- L73 _public prototype_ `const TArray<UMaterialExpression*>& GetSlotExpressions(const UDMMaterialSlot* InSlot) const;`
- L75 _public prototype_ `UMaterialExpression* GetLastSlotExpression(const UDMMaterialSlot* InSlot) const;`
- L77 _public prototype_ `void AddSlotExpressions(const UDMMaterialSlot* InSlot, const TArray<UMaterialExpression*>& InSlotExpressions);`
- L79 _public prototype_ `bool HasSlotProperties(const UDMMaterialSlot* InSlot) const;`
- L81 _public prototype_ `void AddSlotPropertyExpressions(const UDMMaterialSlot* InSlot, const TMap<EDMMaterialPropertyType, TArray<UMaterialExpression*>>& InSlotPropertyExpressions);`
- L84 _public prototype_ `const TMap<EDMMaterialPropertyType, TArray<UMaterialExpression*>>& GetSlotPropertyExpressions(const UDMMaterialSlot* InSlot);`
- L86 _public prototype_ `UMaterialExpression* GetLastSlotPropertyExpression(const UDMMaterialSlot* InSlot, EDMMaterialPropertyType InMaterialProperty) const;`
- L88 _public prototype_ `TArray<const UDMMaterialSlot*> GetSlots() const;`
- L90 _public prototype_ `const TMap<const UDMMaterialSlot*, TArray<UMaterialExpression*>>& GetSlotMap() const;`
- L93 _public prototype_ `bool HasLayer(const UDMMaterialLayerObject* InLayer) const;` — Layers
- L95 _public prototype_ `const TArray<UMaterialExpression*>& GetLayerExpressions(const UDMMaterialLayerObject* InLayer) const;`
- L97 _public prototype_ `UMaterialExpression* GetLastLayerExpression(const UDMMaterialLayerObject* InLayer) const;`
- L99 _public prototype_ `void AddLayerExpressions(const UDMMaterialLayerObject* InLayer, const TArray<UMaterialExpression*>& InLayerExpressions);`
- L101 _public prototype_ `TArray<const UDMMaterialLayerObject*> GetLayers() const;`
- L103 _public prototype_ `const TMap<const UDMMaterialLayerObject*, TArray<UMaterialExpression*>>& GetLayerMap() const;`
- L106 _public prototype_ `bool HasStage(const UDMMaterialStage* InStage) const;` — Stages
- L108 _public prototype_ `const TArray<UMaterialExpression*>& GetStageExpressions(const UDMMaterialStage* InStage) const;`
- L110 _public prototype_ `UMaterialExpression* GetLastStageExpression(const UDMMaterialStage* InStage) const;`
- L112 _public prototype_ `void AddStageExpressions(const UDMMaterialStage* InStage, const TArray<UMaterialExpression*>& InStageExpressions);`
- L114 _public prototype_ `TArray<const UDMMaterialStage*> GetStages() const;`
- L116 _public prototype_ `const TMap<const UDMMaterialStage*, TArray<UMaterialExpression*>>& GetStageMap() const;`
- L119 _public prototype_ `bool HasStageSource(const UDMMaterialStageSource* InStageSource) const;` — Stage Sources
- L121 _public prototype_ `const TArray<UMaterialExpression*>& GetStageSourceExpressions(const UDMMaterialStageSource* InStageSource) const;`
- L123 _public prototype_ `UMaterialExpression* GetLastStageSourceExpression(const UDMMaterialStageSource* InStageSource) const;`
- L125 _public prototype_ `void AddStageSourceExpressions(const UDMMaterialStageSource* InStageSource, const TArray<UMaterialExpression*>& InStageSourceExpressions);`
- L128 _public prototype_ `TArray<const UDMMaterialStageSource*> GetStageSources() const;`
- L130 _public prototype_ `const TMap<const UDMMaterialStageSource*, TArray<UMaterialExpression*>>& GetStageSourceMap() const;`
- L133 _public prototype_ `virtual bool HasValue(const UDMMaterialValue* InValue) const override;` — Material Values
- L135 _public prototype_ `virtual const TArray<UMaterialExpression*>& GetValueExpressions(const UDMMaterialValue* InValue) const override;`
- L137 _public prototype_ `virtual UMaterialExpression* GetLastValueExpression(const UDMMaterialValue* InValue) const override;`
- L139 _public prototype_ `virtual void AddValueExpressions(const UDMMaterialValue* InValue, const TArray<UMaterialExpression*>& InValueExpressions) override;`
- L141 _public prototype_ `virtual TArray<const UDMMaterialValue*> GetValues() const override;`
- L143 _public prototype_ `virtual const TMap<const UDMMaterialValue*, TArray<UMaterialExpression*>>& GetValueMap() const override;`
- L146 _public prototype_ `virtual void AddOtherExpressions(const TArray<UMaterialExpression*>& InOtherExpressions) override;` — Other
- L148 _public prototype_ `virtual const TSet<UMaterialExpression*>& GetOtherExpressions() override;`
- L151 _public prototype_ `UMaterialExpression* GetGlobalExpression(FName InName) const;` — Global Expressions
- L153 _public prototype_ `void SetGlobalExpression(FName InName, UMaterialExpression* InExpression);`
- L156 _private member_ `UMaterial* DynamicMaterial = nullptr;`
- L157 _private member_ `UDynamicMaterialModel* MaterialModel = nullptr;`
- L158 _private member_ `const UDMMaterialProperty* CurrentProperty = nullptr;`
- L159 _private member_ `bool bDirtyAssets;`
- L160 _private member_ `bool bIgnoreUVs;`
- L161 _private member_ `UObject* PreviewObject = nullptr;`
- L162 _private member_ `TSharedRef<FDMMaterialBuildUtils> Utils;`
- L164 _private member_ `TMap<const UDMMaterialValue*, TArray<UMaterialExpression*>> Values;`
- L165 _private member_ `TMap<const UDMMaterialSlot*, TArray<UMaterialExpression*>> Slots;`
- L166 _private member_ `TMap<const UDMMaterialSlot*, TMap<EDMMaterialPropertyType, TArray<UMaterialExpression*>>> SlotProperties;`
- L167 _private member_ `TMap<const UDMMaterialLayerObject*, TArray<UMaterialExpression*>> Layers;`
- L168 _private member_ `TMap<const UDMMaterialStage*, TArray<UMaterialExpression*>> Stages;`
- L169 _private member_ `TMap<const UDMMaterialStageSource*, TArray<UMaterialExpression*>> StageSources;`
- L170 _private member_ `TSet<UMaterialExpression*> OtherExpressions;`
- L171 _private member_ `TMap<FName, UMaterialExpression*> GlobalExpressions;`
- L173 _private prototype_ `void BuildMaterial();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Model/DMMaterialBuildUtils.h` (Public)


#### struct `FDMMaterialBuildUtils`  
`struct FDMMaterialBuildUtils : public IDMMaterialBuildUtilsInterface`  
_L10-74_
- inherits: `IDMMaterialBuildUtilsInterface`
- desc: Utilities for creating material expressions.
- L12 _public prototype_ `FDMMaterialBuildUtils(FDMMaterialBuildState& InBuildState);`
- L15 _public prototype_ `UMaterialExpression* CreateDefaultExpression() const;` — Creates a default expression outputing 0 on a single channel.
- L21 _public prototype_ `virtual UMaterialExpression* CreateExpression(TSubclassOf<UMaterialExpression> InExpressionClass, const FString& InComment, UObject* InAsset = nullptr) const override;` — Create an expression with the comment as its description. @param InAsset For things like texture nodes, will set the default value of that asset property.
- L27 _public function_ `InExpressionClass* CreateExpression(const FString& InComment, UObject* InAsset = nullptr) const`
- L38 _public prototype_ `virtual UMaterialExpression* CreateExpressionParameter(TSubclassOf<UMaterialExpression> InExpressionClass, FName InParameterName, EDMMaterialParameterGroup InParameterGroup, const FString& InComment, UObject* InAsset = nullptr) const override;` — Create a parameter expression with the comment as its description. @param InParameterName The name of the parameter exposed in the material. @param InParameterGroup Determines the type of group assigned to the parameter. @param InAsset For things like texture nodes, will set the default value of that asset property.
- L44 _public function_ `InExpressionClass* CreateExpressionParameter(FName InParameterName, EDMMaterialParameterGroup InParameterGroup, const FString& InComment, UObject* InAsset = nullptr) const`
- L50 _public prototype_ `virtual TArray<UMaterialExpression*> CreateExpressionInputs(const TArray<FDMMaterialStageConnection>& InInputConnectionMap, int32 InStageSourceInputIdx, const TArray<UDMMaterialStageInput*>& InStageInputs, int32& OutOutputIndex, int32& OutOutputChannel) const override;` — Creates a series of nodes that try to render every single input on different parts of the material.
- L55 _public prototype_ `virtual TArray<UMaterialExpression*> CreateExpressionInput(UDMMaterialStageInput* InInput) const override;` — Creates a series of nodes that display a single input.
- L58 _public prototype_ `virtual int32 FindOutputForBitmask(UMaterialExpression* InExpression, int32 InOutputChannels) const override;` — Searches the outputs of an expression to see if there is an appropriate output to match a requested channel mask. Returns INDEX_NONE on failure.
- L61 _public prototype_ `virtual UMaterialExpressionComponentMask* CreateExpressionBitMask(UMaterialExpression* InExpression, int32 InOutputIndex, int32 InOutputChannels) const override;` — Creates a mask expression with the given channels exposed.
- L65 _public prototype_ `virtual UMaterialExpressionAppendVector* CreateExpressionAppend(UMaterialExpression* InExpressionA, int32 InOutputIndexA, UMaterialExpression* InExpressionB, int32 InOutputIndexB) const override;` — Creates an append expression to combine vectors/scalars together to create larger vectors.
- L69 _public prototype_ `virtual void UpdatePreviewMaterial(UMaterialExpression* InLastExpression, int32 InOutputIndex, int32 InOutputChannel, int32 InSize) const override;` — Updates the emissive channel of the give material to show the output of the given expression.
- L73 _protected member_ `FDMMaterialBuildState& BuildState;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Model/DMOnWizardCompleteCallback.h` (Public)


#### struct `FDMOnWizardCompleteCallbackParams`  
`struct FDMOnWizardCompleteCallbackParams`  
_L16-23_
- L18 _public member_ `UDynamicMaterialModel* MaterialModel;`
- L19 _public member_ `UDynamicMaterialModelEditorOnlyData* EditorOnlyData;`
- L20 _public member_ `UObject* Outer;`
- L21 _public member_ `UActorComponent* OuterComponent;`
- L22 _public member_ `AActor* OuterActor;`

#### struct `IDMOnWizardCompleteCallback`  
`struct IDMOnWizardCompleteCallback : public TSharedPtr<IDMOnWizardCompleteCallback>`  
_L26-37_
- inherits: `TSharedPtr<IDMOnWizardCompleteCallback>`
- desc: Callback interface
- L28 _public prototype_ `virtual ~IDMOnWizardCompleteCallback() = default;`
- L30 _public prototype_ `virtual uint32 GetPriority() const = 0;`
- L31 _public prototype_ `virtual void OnModelCreated(const FDMOnWizardCompleteCallbackParams& InParams) = 0;`
- L33 _public function_ `virtual bool operator<(const IDMOnWizardCompleteCallback& InOther) const`

#### struct `FDMMaterialModelCreatedCallbackBase`  
`struct FDMMaterialModelCreatedCallbackBase : public IDMOnWizardCompleteCallback`  
_L40-52_
- inherits: `IDMOnWizardCompleteCallback`
- desc: Default implementation
- L42 _public prototype_ `FDMMaterialModelCreatedCallbackBase(uint32 InPriority);`
- L44 _public prototype_ `virtual ~FDMMaterialModelCreatedCallbackBase() override = default;`
- L47 _public prototype_ `virtual uint32 GetPriority() const override;`
- L51 _protected member_ `uint32 Priority;`

#### struct `FDMMaterialModelCreatedCallbackDelegate`  
`struct FDMMaterialModelCreatedCallbackDelegate : public FDMMaterialModelCreatedCallbackBase`  
_L55-69_
- inherits: `FDMMaterialModelCreatedCallbackBase`
- desc: Default implementation
- L57 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnModelCreated, const FDMOnWizardCompleteCallbackParams&) FDMMaterialModelCreatedCallbackDelegate(uint32 InPriority, const FOnModelCreated& InOnModelCreatedDelegate);`
- L61 _public prototype_ `virtual ~FDMMaterialModelCreatedCallbackDelegate() override = default;`
- L64 _public prototype_ `virtual void OnModelCreated(const FDMOnWizardCompleteCallbackParams& InParams) override;`
- L68 _protected member_ `FOnModelCreated OnModelCreatedDelegate;`

#### Free symbols / members of external scopes

- L57 _delegate_ `DECLARE_DELEGATE_OneParam(FOnModelCreated, const FDMOnWizardCompleteCallbackParams&) FDMMaterialModelCreatedCallbackDelegate(uint32 InPriority, const FOnModelCreated& InOnModelCreatedDelegate);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Model/DynamicMaterialModelEditorOnlyData.h` (Public)


#### enum `EDMState`  
`enum class EDMState : uint8`  
_L40-44_
- reflection: `UENUM(BlueprintType)`
- L42 _public enumerator_ `Idle`
- L43 _public enumerator_ `Building`

#### enum `EDMMaterialFlagsUsage`  
`enum EDMMaterialFlagsUsage : int32`  
_L48-101_
- reflection: `UENUM(BlueprintType, meta = (BitFlags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Convert engine linear enum to bitflag enum.
- L50 _public enumerator_ `DMMFU_None = 0 UMETA(Hidden)`
- L52 _public enumerator_ `DMMFU_StaticMesh = 1 << EMaterialUsage::MATUSAGE_StaticMesh UMETA(DisplayName = "Static Mesh")` — Indicates that the material and its instances can be used on static meshes.
- L54 _public enumerator_ `DMMFU_SkeletalMesh = 1 << EMaterialUsage::MATUSAGE_SkeletalMesh UMETA(DisplayName = "Skeletal Mesh")` — Indicates that the material and its instances can be used with skeletal meshes.
- L56 _public enumerator_ `DMMFU_SplineMesh = 1 << EMaterialUsage::MATUSAGE_SplineMesh UMETA(DisplayName = "Spline Mesh")` — Indicates that the material and its instances can be used with spline meshes.
- L58 _public enumerator_ `DMMFU_InstancedStaticMeshes = 1 << EMaterialUsage::MATUSAGE_InstancedStaticMeshes UMETA(DisplayName = "Instanced Static Mesh")` — Indicates that the material and its instances can be used with instanced static meshes.
- L60 _public enumerator_ `DMMFU_ParticleSprites = 1 << EMaterialUsage::MATUSAGE_ParticleSprites UMETA(DisplayName = "Particle Sprites")` — Indicates that the material and its instances can be used with particle sprites.
- L62 _public enumerator_ `DMMFU_BeamTrails = 1 << EMaterialUsage::MATUSAGE_BeamTrails UMETA(DisplayName = "Beam Trails")` — Indicates that the material and its instances can be used with beam trails.
- L64 _public enumerator_ `DMMFU_MeshParticles = 1 << EMaterialUsage::MATUSAGE_MeshParticles UMETA(DisplayName = "Mesh Particles")` — Indicates that the material and its instances can be used with mesh particles.
- L66 _public enumerator_ `DMMFU_StaticLighting = 1 << EMaterialUsage::MATUSAGE_StaticLighting UMETA(DisplayName = "Static Lighting")` — Indicates that the material and its instances can be used with static lighting.
- L68 _public enumerator_ `DMMFU_MorphTargets = 1 << EMaterialUsage::MATUSAGE_MorphTargets UMETA(DisplayName = "Morph Targets")` — Indicates that the material and its instances can be used with morph targets.
- L70 _public enumerator_ `DMMFU_GeometryCollections = 1 << EMaterialUsage::MATUSAGE_GeometryCollections UMETA(DisplayName = "Geometry Collections")` — Indicates that the material and its instances can be use with geometry collections.
- L72 _public enumerator_ `DMMFU_GeometryCache = 1 << EMaterialUsage::MATUSAGE_GeometryCache UMETA(DisplayName = "Geometry Cache")` — Indicates that the material and its instances can be use with geometry caches.
- L74 _public enumerator_ `DMMFU_Clothing = 1 << EMaterialUsage::MATUSAGE_Clothing UMETA(DisplayName = "Clothing")` — Indicates that the material and its instances can be used with clothing.
- L76 _public enumerator_ `DMMFU_NiagaraSprites = 1 << EMaterialUsage::MATUSAGE_NiagaraSprites UMETA(DisplayName = "Niagara Sprites")` — Indicates that the material and its instances can be used with Niagara sprites.
- L78 _public enumerator_ `DMMFU_NiagaraRibbons = 1 << EMaterialUsage::MATUSAGE_NiagaraRibbons UMETA(DisplayName = "Niagara Ribbons")` — Indicates that the material and its instances can be used with Niagara ribbons.
- L80 _public enumerator_ `DMMFU_NiagaraMeshParticles = 1 << EMaterialUsage::MATUSAGE_NiagaraMeshParticles UMETA(DisplayName = "Niagara Mesh Particles")` — Indicates that the material and its instances can be used with Niagara meshes.
- L82 _public enumerator_ `DMMFU_Water = 1 << EMaterialUsage::MATUSAGE_Water UMETA(DisplayName = "Water")` — Indicates that the material and its instances can be use with water.
- L84 _public enumerator_ `DMMFU_HairStrands = 1 << EMaterialUsage::MATUSAGE_HairStrands UMETA(DisplayName = "HairStrands")` — Indicates that the material and its instances can be use with hair strands.
- L86 _public enumerator_ `DMMFU_LidarPointCloud = 1 << EMaterialUsage::MATUSAGE_LidarPointCloud UMETA(DisplayName = "Lidar Point Cloud")` — Indicates that the material and its instances can be use with LiDAR Point Clouds.
- L88 _public enumerator_ `DMMFU_VirtualHeightfieldMesh = 1 << EMaterialUsage::MATUSAGE_VirtualHeightfieldMesh UMETA(DisplayName = "Virtual Heightfield Mesh")` — Indicates that the material and its instances can be used with Virtual Heightfield Mesh. (Deprecated).
- L90 _public enumerator_ `DMMFU_Nanite = 1 << EMaterialUsage::MATUSAGE_Nanite UMETA(DisplayName = "Nanite")` — Indicates that the material and its instances can be used with Nanite meshes.
- L92 _public enumerator_ `DMMFU_Voxels = 1 << EMaterialUsage::MATUSAGE_Voxels UMETA(DisplayName = "Voxels")` — Indicates that the material and its instances can be used with Nanite voxel meshes.
- L94 _public enumerator_ `DMMFU_VolumetricCloud = 1 << EMaterialUsage::MATUSAGE_VolumetricCloud UMETA(DisplayName = "Volumetric Clouds")` — Indicates that the material and its instances with volumetric cloud. Without that flag, it can only be used on volumetric fog.
- L96 _public enumerator_ `DMMFU_HeterogeneousVolumes = 1 << EMaterialUsage::MATUSAGE_HeterogeneousVolumes UMETA(DisplayName = "Hetergeneous Volumes")` — Indicates that the material and its instances with heterogeneous volumes. Without that flag, it can only be used on volumetric fog.
- L98 _public enumerator_ `DMMFU_EditorCompositing = 1 << EMaterialUsage::MATUSAGE_EditorCompositing UMETA(DisplayName = "Editor Compositing")` — Indicates that the material and its instances can be used with editor compositing.
- L100 _public enumerator_ `DMMFU_NeuralNetworks = 1 << EMaterialUsage::MATUSAGE_NeuralNetworks UMETA(DisplayName = "Neural Networks")` — Indicates that the material and its instances can be used with neural network engine.

#### enum `EDMMaterialFlagsGeneral`  
`enum class EDMMaterialFlagsGeneral : uint8`  
_L104-115_
- reflection: `UENUM(BlueprintType, meta = (BitFlags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L106 _public enumerator_ `None = 0 UMETA(HIdden)`
- L107 _public enumerator_ `TwoSided = 1 << 0 UMETA(ToolTip = "Indicates that the material should be rendered without backface culling and the normal should be flipped for backfaces.")`
- L108 _public enumerator_ `TangentSpaceNormal = 1 << 1 UMETA(ToolTip = "Whether the material takes a tangent space normal or a world space normal as input. (TangentSpace requires extra instructions but is often more convenient).")`
- L109 _public enumerator_ `UsesDistortion = 1 << 2 UMETA(ToolTip = "Indicates that the material and its instances can be used with distortion. This will result in the shaders required to support distortion being compiled which will increase shader compile time and memory usage.")`
- L110 _public enumerator_ `NormalCurvatureToRoughness = 1 << 3 UMETA(ToolTip = "Reduce roughness based on screen space normal changes.")`
- L111 _public enumerator_ `FullyRough = 1 << 4 UMETA(ToolTip = "Forces the material to be completely rough. Saves a number of instructions and one sampler.")`
- L112 _public enumerator_ `DitheredLODTransition = 1 << 5 UMETA(ToolTip = "Whether meshes rendered with the material should support dithered LOD transitions.")`
- L113 _public enumerator_ `EnableDisplacementFade = 1 << 6 UMETA(ToolTip = "Enables fading out and disabling of dynamic displacement in the distance, as displacement becomes unnoticeable.")`
- L114 _public enumerator_ `GenerateSphericalParticleNormals = 1 << 7 UMETA(ToolTip = "Whether to generate spherical normals for particles that use this material.")`

#### enum `EDMMaterialFlagsLighting`  
`enum class EDMMaterialFlagsLighting : uint8`  
_L119-129_
- reflection: `UENUM(BlueprintType, meta = (BitFlags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L121 _public enumerator_ `None = 0 UMETA(HIdden)`
- L122 _public enumerator_ `CastDynamicShadowAsMasked = 1 << 0 UMETA(ToolTip = "Whether the material should cast shadows as masked even though it has a translucent blend mode.")`
- L123 _public enumerator_ `ContactShadows = 1 << 1 UMETA(ToolTip = "Contact shadows on translucency.")`
- L124 _public enumerator_ `UseEmissiveForDynamicAreaLighting = 1 << 2 UMETA(ToolTip = "Whether the material's emissive colour is injected into the LightPropagationVolume.")`
- L125 _public enumerator_ `CompatibleWithLumenCardSharing = 1 << 3 UMETA(ToolTip = "Whether to allow to share Lumen Cards between different instances even when material uses world position or per instance data, which may change material look per instance. All materials on a component needs this flag set for sharing to work.")`
- L126 _public enumerator_ `AllowTranslucentLocalLightShadow = 1 << 4 UMETA(ToolTip = "Allows a translucent material to receive local light shadows.")`
- L127 _public enumerator_ `UseLightmapDirectionality = 1 << 5 UMETA(ToolTip = "Use lightmap directionality and per pixel normals. If disabled, lighting from lightmaps will be flat but cheaper.")`
- L128 _public enumerator_ `AllowNegativeEmissiveColor = 1 << 6 UMETA(ToolTip = "Whether the material should allow outputting negative emissive color values. Only allowed on unlit materials.")`

#### enum `EDMMaterialFlagsTranslucency`  
`enum class EDMMaterialFlagsTranslucency : uint8`  
_L133-142_
- reflection: `UENUM(BlueprintType, meta = (BitFlags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L135 _public enumerator_ `None = 0 UMETA(HIdden)`
- L136 _public enumerator_ `DisableDepthTest = 1 << 0 UMETA(ToolTip = "Whether to draw on top of opaque pixels even if behind them. This only has meaning for translucency.")`
- L137 _public enumerator_ `ScreenSpaceReflections = 1 << 1 UMETA(ToolTip = "SSR on translucency.")`
- L138 _public enumerator_ `AllowTranslucentCustomDepthWrites = 1 << 2 UMETA(ToolTip = "Allows a translucent material to be used with custom depth writing by compiling additional shaders.")`
- L139 _public enumerator_ `AllowFrontLayerTranslucency = 1 << 3 UMETA(ToolTip = "Allows a translucent material to be used with Front Layer Translucency by compiling additional shaders. Useful for controlling what should be included in Front Layer Translucency.")`
- L140 _public enumerator_ `WriteOnlyAlpha = 1 << 4 UMETA(ToolTip = "Whether the transluency pass should write its alpha, and only the alpha, into the framebuffer.")`
- L141 _public enumerator_ `DitherOpacityMask = 1 << 5 UMETA(ToolTip = "Dither opacity mask. When combined with Temporal AA this can be used as a form of limited translucency which supports all lighting features.")`

#### enum `EDMMaterialFlagsMotion`  
`enum class EDMMaterialFlagsMotion : uint8`  
_L146-152_
- reflection: `UENUM(BlueprintType, meta = (BitFlags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L148 _public enumerator_ `None = 0 UMETA(HIdden)`
- L149 _public enumerator_ `PixelAnimation = 1 << 0 UMETA(ToolTip = "Whether the opaque material has any pixel animations happening, that isn't included in the geometric velocities. This allows to disable renderer's heuristics that assumes animation is fully described with motion vector, such as TSR's anti-flickering heuristic.")`
- L150 _public enumerator_ `ResponsiveAA = 1 << 1 UMETA(ToolTip = "Indicates that the material should be rendered using responsive anti-aliasing. Improves sharpness of small moving particles such as sparks. Only use for small moving features because it will cause aliasing of the background.")`
- L151 _public enumerator_ `OutputTranslucentVelocity = 1 << 2 UMETA(ToolTip = "Whether ranslucent materials will output motion vectors and write to depth buffer in velocity pass.")`

#### enum `EDMMaterialFlagsForwardRenderer`  
`enum class EDMMaterialFlagsForwardRenderer : uint8`  
_L156-165_
- reflection: `UENUM(BlueprintType, meta = (BitFlags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L158 _public enumerator_ `None = 0 UMETA(HIdden)`
- L159 _public enumerator_ `MobileSeparateTranslucency = 1 << 0 UMETA(ToolTip = "Indicates that the translucent material should not be affected by bloom or DOF. (Note: Depth testing is not available).")`
- L160 _public enumerator_ `AlphaToCoverage = 1 << 1 UMETA(ToolTip = "Use alpha to coverage for masked material on mobile, make sure MSAA is enabled as well.")`
- L161 _public enumerator_ `ForwardRenderUsePreintegratedGFForSimpleIBL = 1 << 2 UMETA(ToolTip = "Use preintegrated GF lut for simple IBL, but will use one more sampler.")`
- L162 _public enumerator_ `HighQualityForwardReflections = 1 << 3 UMETA(ToolTip = "Enables multiple parallax-corrected reflection captures that blend together.")`
- L163 _public enumerator_ `ForwardBlendsSkyLightCubemaps = 1 << 4 UMETA(ToolTip = "Enables blending of sky light cubemap textures. When disabled, the secondary cubemap is only visible when the blend factor is 1.")`
- L164 _public enumerator_ `PlanarForwardReflections = 1 << 5 UMETA(ToolTip = "Enabling this setting reduces the number of samplers available to the material as one more sampler will be used for the planar reflection.")`

#### class `UDynamicMaterialModelEditorOnlyData`  
`class UDynamicMaterialModelEditorOnlyData : public UObject, public IDynamicMaterialModelEditorOnlyDataInterface, public FNotifyHook, public IDMBuildable`  
_L169-671_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, DefaultToInstanced, ClassGroup = "Material Designer")`
- inherits: `UObject,IDynamicMaterialModelEditorOnlyDataInterface,FNotifyHook,IDMBuildable`
- L177 _public member_ `static const FString SlotsPathToken;`
- L178 _public member_ `static const FString BaseColorSlotPathToken;`
- L179 _public member_ `static const FString EmissiveSlotPathToken;`
- L180 _public member_ `static const FString OpacitySlotPathToken;`
- L181 _public member_ `static const FString RoughnessPathToken;`
- L182 _public member_ `static const FString SpecularPathToken;`
- L183 _public member_ `static const FString MetallicPathToken;`
- L184 _public member_ `static const FString NormalPathToken;`
- L185 _public member_ `static const FString PixelDepthOffsetPathToken;`
- L186 _public member_ `static const FString WorldPositionOffsetPathToken;`
- L187 _public member_ `static const FString AmbientOcclusionPathToken;`
- L188 _public member_ `static const FString AnisotropyPathToken;`
- L189 _public member_ `static const FString RefractionPathToken;`
- L190 _public member_ `static const FString TangentPathToken;`
- L191 _public member_ `static const FString DisplacementPathToken;`
- L192 _public member_ `static const FString SubsurfaceColorPathToken;`
- L193 _public member_ `static const FString SurfaceThicknessPathToken;`
- L194 _public member_ `static const FString Custom1PathToken;`
- L195 _public member_ `static const FString Custom2PathToken;`
- L196 _public member_ `static const FString Custom3PathToken;`
- L197 _public member_ `static const FString Custom4PathToken;`
- L198 _public member_ `static const FString PropertiesPathToken;`
- L200 _public member_ `static const TArray<EMaterialDomain> SupportedDomains;`
- L201 _public member_ `static const TArray<EBlendMode> SupportedBlendModes;`
- L203 _public member_ `static const FName AlphaValueName;`
- L205 _public prototype_ `static UDynamicMaterialModelEditorOnlyData* Get(UDynamicMaterialModelBase* InModelBase);`
- L206 _public prototype_ `static UDynamicMaterialModelEditorOnlyData* Get(const TWeakObjectPtr<UDynamicMaterialModelBase>& InModelBaseWeak);`
- L207 _public prototype_ `static UDynamicMaterialModelEditorOnlyData* Get(UDynamicMaterialModel* InModel);`
- L208 _public prototype_ `static UDynamicMaterialModelEditorOnlyData* Get(const TWeakObjectPtr<UDynamicMaterialModel>& InModelWeak);`
- L209 _public prototype_ `static UDynamicMaterialModelEditorOnlyData* Get(const TScriptInterface<IDynamicMaterialModelEditorOnlyDataInterface>& InInterface);`
- L210 _public prototype_ `static UDynamicMaterialModelEditorOnlyData* Get(IDynamicMaterialModelEditorOnlyDataInterface* InInterface);`
- L211 _public prototype_ `static UDynamicMaterialModelEditorOnlyData* Get(UDynamicMaterialInstance* InInstance);`
- L213 _public prototype_ `UDynamicMaterialModelEditorOnlyData();`
- L215 _public prototype_ `void Initialize();`
- L218 _public function_ `UDynamicMaterialModel* GetMaterialModel() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L221 _public prototype_ `UMaterial* GetGeneratedMaterial() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L224 _public function_ `EDMState GetState() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L227 _public function_ `TEnumAsByte<EMaterialDomain> GetDomain() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L230 _public prototype_ `void SetDomain(TEnumAsByte<EMaterialDomain> InDomain);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L233 _public function_ `TEnumAsByte<EBlendMode> GetBlendMode() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L236 _public prototype_ `void SetBlendMode(TEnumAsByte<EBlendMode> InBlendMode);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L239 _public function_ `EDMMaterialShadingModel GetShadingModel() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L242 _public prototype_ `void SetShadingModel(EDMMaterialShadingModel InShadingModel);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L245 _public prototype_ `EDMMaterialFlagsUsage GetUsageFlags() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L248 _public prototype_ `bool HasUsageFlag(EDMMaterialFlagsUsage InFlag) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L251 _public prototype_ `bool SetUsageFlag(EDMMaterialFlagsUsage InFlag, bool bInSet);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L254 _public prototype_ `EDMMaterialFlagsGeneral GetGeneralFlags() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L257 _public prototype_ `bool HasGeneralFlag(EDMMaterialFlagsGeneral InFlag) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L260 _public prototype_ `bool SetGeneralFlag(EDMMaterialFlagsGeneral InFlag, bool bInSet);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L263 _public prototype_ `EDMMaterialFlagsLighting GetLightingFlags() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L266 _public prototype_ `bool HasLightingFlag(EDMMaterialFlagsLighting InFlag) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L269 _public prototype_ `bool SetLightingFlag(EDMMaterialFlagsLighting InFlag, bool bInSet);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L272 _public prototype_ `EDMMaterialFlagsTranslucency GetTranslucencyFlags() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L275 _public prototype_ `bool HasTranslucencyFlag(EDMMaterialFlagsTranslucency InFlag) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L278 _public prototype_ `bool SetTranslucencyFlag(EDMMaterialFlagsTranslucency InFlag, bool bInSet);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L281 _public prototype_ `EDMMaterialFlagsMotion GetMotionFlags() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L284 _public prototype_ `bool HasMotionFlag(EDMMaterialFlagsMotion InFlag) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L287 _public prototype_ `bool SetMotionFlag(EDMMaterialFlagsMotion InFlag, bool bInSet);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L290 _public prototype_ `EDMMaterialFlagsForwardRenderer GetForwardRendererFlags() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L293 _public prototype_ `bool HasForwardRendererFlag(EDMMaterialFlagsForwardRenderer InFlag) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L296 _public prototype_ `bool SetForwardRendererFlag(EDMMaterialFlagsForwardRenderer InFlag, bool bInSet);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L299 _public prototype_ `float GetOpacityMaskClipValue() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L302 _public prototype_ `void SetOpacityMaskClipValue(float InClipValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L305 _public prototype_ `float GetDisplacementCenter() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L308 _public prototype_ `void SetDisplacementCenter(float InCenter);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L311 _public prototype_ `float GetDisplacementMagnitude() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L314 _public prototype_ `void SetDisplacementMagnitude(float InMagnitude);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L317 _public prototype_ `void SetChannelListPreset(FName InPresetName);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L320 _public prototype_ `const FMaterialStatistics& GetMaterialStats() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L323 _public prototype_ `void OpenMaterialEditor() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L326 _public prototype_ `TMap<EDMMaterialPropertyType, UDMMaterialProperty*> GetMaterialProperties() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L329 _public prototype_ `UDMMaterialProperty* GetMaterialProperty(EDMMaterialPropertyType InMaterialProperty) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L332 _public function_ `const TArray<UDMMaterialSlot*>& GetSlots() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L336 _public prototype_ `UDMMaterialSlot* GetSlot(int32 Index) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Gets slot by index. Highly recommended to use GetSlotForMaterialProperty(PropertyType).
- L339 _public prototype_ `UDMMaterialSlot* GetSlotForMaterialProperty(EDMMaterialPropertyType InType) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L343 _public prototype_ `UDMMaterialSlot* GetSlotForEnabledMaterialProperty(EDMMaterialPropertyType InType) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Same as the above method, but will only return the slot if the material property is enabled.
- L347 _public prototype_ `UDMMaterialSlot* AddSlot();` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Adds the next available slot. Highly recommended to use AddSlotForMaterialProperty(PropertyType).
- L350 _public prototype_ `UDMMaterialSlot* AddSlotForMaterialProperty(EDMMaterialPropertyType InType);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L354 _public prototype_ `UDMMaterialSlot* RemoveSlot(int32 Index);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Removes the next slot by index. Highly recommended to use RemoveSlotForMaterialProperty(PropertyType).
- L357 _public prototype_ `UDMMaterialSlot* RemoveSlotForMaterialProperty(EDMMaterialPropertyType InType);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L360 _public prototype_ `TArray<EDMMaterialPropertyType> GetMaterialPropertiesForSlot(const UDMMaterialSlot* InSlot) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L363 _public prototype_ `void AssignMaterialPropertyToSlot(EDMMaterialPropertyType InProperty, UDMMaterialSlot* InSlot);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L366 _public prototype_ `void UnassignMaterialProperty(EDMMaterialPropertyType InProperty);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L369 _public prototype_ `bool HasBuildBeenRequested() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L371 _public function_ `FDMOnMaterialBuilt::RegistrationType& GetOnMaterialBuiltDelegate()`
- L372 _public function_ `FDMOnValueListUpdated::RegistrationType& GetOnValueListUpdateDelegate()`
- L373 _public function_ `FDMOnSlotListUpdated::RegistrationType& GetOnSlotListUpdateDelegate()`
- L374 _public function_ `FDMOnPropertyUpdated::RegistrationType& GetOnPropertyUpdateDelegate()`
- L376 _public prototype_ `void OnPropertyUpdate(UDMMaterialProperty* InProperty);`
- L378 _public prototype_ `TSharedRef<FDMMaterialBuildState> CreateBuildState(UMaterial* InMaterialToBuild, bool bInDirtyAssets = true) const;`
- L380 _public prototype_ `bool NeedsWizard() const;`
- L382 _public prototype_ `void OnWizardComplete();`
- L384 _public prototype_ `void SaveEditor();`
- L387 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, class FEditPropertyChain* InPropertyThatChanged);`
- L391 _public prototype_ `virtual void PostLoad() override;`
- L392 _public prototype_ `virtual void PostEditUndo() override;`
- L393 _public prototype_ `virtual void PostEditImport() override;`
- L394 _public prototype_ `virtual void PostDuplicate(bool bInDuplicateForPIE) override;`
- L395 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& InPropertyChangedEvent) override;`
- L396 _public prototype_ `virtual void Serialize(FArchive& InAr) override;`
- L400 _public prototype_ `virtual void DoBuild_Implementation(bool bInDirtyAssets) override;`
- L404 _public prototype_ `virtual void PostEditorDuplicate() override;`
- L405 _public prototype_ `virtual void RequestMaterialBuild(EDMBuildRequestType InRequestType = EDMBuildRequestType::Preview) override;`
- L406 _public prototype_ `virtual void OnValueListUpdate() override;`
- L407 _public prototype_ `virtual void OnValueUpdated(UDMMaterialValue* InValue, EDMUpdateType InUpdateType) override;`
- L408 _public prototype_ `virtual void OnTextureUVUpdated(UDMTextureUV* InTextureUV) override;`
- L409 _public prototype_ `virtual TSharedRef<IDMMaterialBuildStateInterface> CreateBuildStateInterface(UMaterial* InMaterialToBuild) const override;`
- L410 _public prototype_ `virtual void SetPropertyComponent(EDMMaterialPropertyType InPropertyType, FName InComponentName, UDMMaterialComponent* InComponent) override;`
- L411 _public prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath) const override;`
- L412 _public prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const override;`
- L421 _public prototype_ `bool GetHasPixelAnimation() const;` — `UE_DEPRECATED(5.8, "Use HasMotionFlag().")` — `UFUNCTION(meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use HasMotionFlag()."))`
- L425 _public prototype_ `void SetHasPixelAnimation(bool bInHasAnimation);` — `UE_DEPRECATED(5.8, "Use SetMotionFlag().")` — `UFUNCTION(meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use SetMotionFlag()."))`
- L429 _public prototype_ `bool GetIsTwoSided() const;` — `UE_DEPRECATED(5.8, "Use HasGeneralFlag().")` — `UFUNCTION(meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use HasGeneralFlag()."))`
- L433 _public prototype_ `void SetIsTwoSided(bool bInEnabled);` — `UE_DEPRECATED(5.8, "Use SetGeneralFlag().")` — `UFUNCTION(meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use SetGeneralFlag()."))`
- L437 _public prototype_ `bool IsOutputTranslucentVelocityEnabled() const;` — `UE_DEPRECATED(5.8, "Use HasMotionFlag().")` — `UFUNCTION(meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use HasMotionFlag()."))`
- L441 _public prototype_ `void SetOutputTranslucentVelocityEnabled(bool bInEnabled);` — `UE_DEPRECATED(5.8, "Use SetMotionFlag().")` — `UFUNCTION(meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use SetMotionFlag()."))`
- L445 _public prototype_ `bool IsNaniteTessellationEnabled() const;` — `UE_DEPRECATED(5.8, "Use HasUsageFlag().")` — `UFUNCTION(meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use HasUsageFlag()."))`
- L449 _public prototype_ `void SetNaniteTessellationEnabled(bool bInEnabled);` — `UE_DEPRECATED(5.8, "Use SetUsageFlag().")` — `UFUNCTION(meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use SetUsageFlag()."))`
- L453 _public prototype_ `bool IsResponsiveAAEnabled() const;` — `UE_DEPRECATED(5.8, "Use HasMotionFlag().")` — `UFUNCTION(meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use HasMotionFlag()."))`
- L457 _public prototype_ `void SetResponsiveAAEnabled(bool bInEnabled);` — `UE_DEPRECATED(5.8, "Use SetMotionFlag().")` — `UFUNCTION(meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use SetMotionFlag()."))`
- L461 _protected member_ `TObjectPtr<UDynamicMaterialModel> MaterialModel;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L464 _protected member_ `EDMState State;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, TextExportTransient, Category = "Material Designer")`
- L468 _protected member_ `TEnumAsByte<EMaterialDomain> Domain;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer", meta = (NotKeyframeable, ValidEnumValues = "MD_Surface,MD_PostProcess,MD_DeferredDecal,MD_LightFunction"))`
- L472 _protected member_ `TEnumAsByte<EBlendMode> BlendMode;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer", meta = (NotKeyframeable, ValidEnumValues = "BLEND_Opaque,BLEND_Translucent,BLEND_Masked,BLEND_Additive,BLEND_Modulate"))`
- L476 _protected member_ `EDMMaterialShadingModel ShadingModel;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer", meta = (NotKeyframeable, ValidEnumValues = "Unlit,DefaultLit"))`
- L480 _protected member_ `int32 UsageFlags;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer|Usage", meta = (NotKeyframeable, Bitmask, BitmaskEnum = "/Script/DynamicMaterialEditor.EDMMaterialFlagsUsage"))`
- L484 _protected member_ `uint8 GeneralFlags;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer|General", meta = (NotKeyframeable, Bitmask, BitmaskEnum = "/Script/DynamicMaterialEditor.EDMMaterialFlagsGeneral"))`
- L489 _protected member_ `uint8 LightingFlags;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer|Lighting", meta = (NotKeyframeable, Bitmask, BitmaskEnum = "/Script/DynamicMaterialEditor.EDMMaterialFlagsLighting", EditCondition = "ShadingModel == EDMMaterialShadingModel::DefaultLit"))`
- L494 _protected member_ `uint8 TranslucencyFlags;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer|Translucency", meta = (NotKeyframeable, Bitmask, BitmaskEnum = "/Script/DynamicMaterialEditor.EDMMaterialFlagsTranslucency", EditCondition = "BlendMode == EBlendMode::BLEND_Masked || BlendMode == EBlendMode::BLEND_Translucent"))`
- L498 _protected member_ `uint8 MotionFlags;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer|Motion", meta = (NotKeyframeable, Bitmask, BitmaskEnum = "/Script/DynamicMaterialEditor.EDMMaterialFlagsMotion"))`
- L502 _protected member_ `uint8 ForwardRendererFlags;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer|Forward Renderer", meta = (NotKeyframeable, Bitmask, BitmaskEnum = "/Script/DynamicMaterialEditor.EDMMaterialFlagsForwardRenderer"))`
- L507 _protected member_ `float OpacityMaskClipValue;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer|Translucency", meta = (NotKeyframeable, UIMin = 0, UIMax = 1, ClampMin = 0, ClampMax = 1, EditCondition = "BlendMode == EBlendMode::BLEND_Masked"))`
- L513 _protected member_ `float DisplacementCenter;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer|General", meta = (NotKeyframeable, UIMin = 0, UIMax = 1, ClampMin = 0, ClampMax = 1, EditCondition = "IsNaniteEnabled()"))` — Mid point for displacement in the range 0-1.
- L518 _protected member_ `float DisplacementMagnitude;` — `UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Material Designer|General", meta = (NotKeyframeable, EditCondition = "IsNaniteEnabled()"))` — Multipler for displacement values.
- L521 _protected member_ `TMap<EDMMaterialPropertyType, TObjectPtr<UDMMaterialSlot>> PropertySlotMap;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, TextExportTransient, Category = "Material Designer")`
- L524 _protected member_ `TArray<TObjectPtr<UDMMaterialSlot>> Slots;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L527 _protected member_ `TArray<TObjectPtr<UMaterialExpression>> Expressions;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L530 _protected member_ `bool bCreateMaterialPackage;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L533 _protected member_ `FMaterialStatistics MaterialStats;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L535 _protected member_ `FDMOnMaterialBuilt OnMaterialBuiltDelegate;`
- L536 _protected member_ `FDMOnValueListUpdated OnValueListUpdateDelegate;`
- L537 _protected member_ `FDMOnSlotListUpdated OnSlotListUpdateDelegate;`
- L538 _protected member_ `FDMOnPropertyUpdated OnPropertyUpdateDelegate;`
- L541 _protected member_ `TObjectPtr<UDMMaterialProperty> BaseColor;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L544 _protected member_ `TObjectPtr<UDMMaterialProperty> EmissiveColor;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L547 _protected member_ `TObjectPtr<UDMMaterialProperty> Opacity;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L550 _protected member_ `TObjectPtr<UDMMaterialProperty> OpacityMask;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L553 _protected member_ `TObjectPtr<UDMMaterialProperty> Roughness;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L556 _protected member_ `TObjectPtr<UDMMaterialProperty> Specular;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L559 _protected member_ `TObjectPtr<UDMMaterialProperty> Metallic;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L562 _protected member_ `TObjectPtr<UDMMaterialProperty> Normal;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L565 _protected member_ `TObjectPtr<UDMMaterialProperty> PixelDepthOffset;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L568 _protected member_ `TObjectPtr<UDMMaterialProperty> WorldPositionOffset;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L571 _protected member_ `TObjectPtr<UDMMaterialProperty> AmbientOcclusion;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L574 _protected member_ `TObjectPtr<UDMMaterialProperty> Anisotropy;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L577 _protected member_ `TObjectPtr<UDMMaterialProperty> Refraction;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L580 _protected member_ `TObjectPtr<UDMMaterialProperty> Tangent;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L583 _protected member_ `TObjectPtr<UDMMaterialProperty> Displacement;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L586 _protected member_ `TObjectPtr<UDMMaterialProperty> SubsurfaceColor;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L589 _protected member_ `TObjectPtr<UDMMaterialProperty> SurfaceThickness;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L592 _protected member_ `TObjectPtr<UDMMaterialProperty> Custom1;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L595 _protected member_ `TObjectPtr<UDMMaterialProperty> Custom2;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L598 _protected member_ `TObjectPtr<UDMMaterialProperty> Custom3;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L601 _protected member_ `TObjectPtr<UDMMaterialProperty> Custom4;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L603 _protected member_ `bool bBuildRequested;`
- L605 _protected prototype_ `void CreateMaterial();`
- L608 _protected prototype_ `void BuildMaterial(bool bInDirtyAssets);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L610 _protected prototype_ `void SetMaterialFlags(UMaterial* InMaterial);`
- L612 _protected prototype_ `FString GetMaterialAssetPath() const;`
- L613 _protected prototype_ `FString GetMaterialAssetName() const;`
- L614 _protected prototype_ `FString GetMaterialPackageName(const FString& InMaterialBaseName) const;`
- L616 _protected prototype_ `void OnSlotConnectorsUpdated(UDMMaterialSlot* InSlot);`
- L619 _protected prototype_ `void SwapSlotMaterialProperty(EDMMaterialPropertyType InPropertyFrom, EDMMaterialPropertyType InPropertyTo);` — Swaps the material properties from one slot to another, unless both slots exist and/or are the same.
- L625 _protected prototype_ `void EnsureSwapSlotMaterialProperty(EDMMaterialPropertyType InPropertyFrom, EDMMaterialPropertyType InPropertyTo);` — Swaps the material properties from one slot to another, unless both slots exist and/or are the same. Ensuring that the To Property exists.
- L627 _protected prototype_ `void AssignPropertyAlphaValues();`
- L629 _protected prototype_ `void OnDomainChanged();`
- L630 _protected prototype_ `void OnBlendModeChanged();`
- L631 _protected prototype_ `void OnShadingModelChanged();`
- L632 _protected prototype_ `void OnMaterialFlagChanged();`
- L633 _protected prototype_ `void OnMaterialSettingsChanged();`
- L636 _protected prototype_ `virtual void ReinitComponents() override;`
- L643 _protected prototype_ `void ConvertDeprecatedVarsToFlags();`
- L647 _protected member_ `bool bTwoSided_DEPRECATED;` — `UE_DEPRECATED(5.8, "Moved to GeneralFlags")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Moved to GeneralFlags"))`
- L651 _protected member_ `bool bHasPixelAnimation_DEPRECATED;` — `UE_DEPRECATED(5.8, "Moved to MotionFlags")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Moved to MotionFlags"))`
- L655 _protected member_ `bool bOutputTranslucentVelocityEnabled_DEPRECATED;` — `UE_DEPRECATED(5.8, "Moved to MotionFlags")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Moved to MotionFlags"))`
- L659 _protected member_ `bool bNaniteTessellationEnabled_DEPRECATED;` — `UE_DEPRECATED(5.8, "Moved to UsageFlags")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Moved to UsageFlags"))`
- L663 _protected member_ `bool bResponsiveAAEnabled_DEPRECATED;` — `UE_DEPRECATED(5.8, "Moved to MotionFlags")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Moved to MotionFlags"))`
- L667 _private function_ `bool IsNaniteEnabled() const` — `UFUNCTION()`

#### Free symbols / members of external scopes

- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMOnMaterialBuilt, UDynamicMaterialModelBase*);`
- L34 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMOnMaterialBuilt, UDynamicMaterialModelBase*);`
- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMOnValueListUpdated, UDynamicMaterialModelBase*);`
- L35 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMOnValueListUpdated, UDynamicMaterialModelBase*);`
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMOnSlotListUpdated, UDynamicMaterialModelBase*);`
- L36 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMOnSlotListUpdated, UDynamicMaterialModelBase*);`
- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMOnPropertyUpdated, UDynamicMaterialModelBase*);`
- L37 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMOnPropertyUpdated, UDynamicMaterialModelBase*);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/UI/Menus/DMMenuContext.h` (Public)


#### class `UDMMenuContext`  
`class UDMMenuContext : public UObject`  
_L24-75_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L29 _public prototype_ `static UDMMenuContext* CreateEmpty();`
- L31 _public prototype_ `static UDMMenuContext* CreateEditor(const TWeakPtr<SDMMaterialEditor>& InEditorWidget);`
- L33 _public prototype_ `static UDMMenuContext* CreateLayer(const TWeakPtr<SDMMaterialEditor>& InEditorWidget, UDMMaterialLayerObject* InLayerObject);`
- L35 _public prototype_ `static UDMMenuContext* CreateStage(const TWeakPtr<SDMMaterialEditor>& InEditorWidget, const TWeakPtr<SDMMaterialStage>& InStageWidget);`
- L37 _public prototype_ `static UToolMenu* GenerateContextMenuDefault(const FName InMenuName);`
- L39 _public prototype_ `static UToolMenu* GenerateContextMenuEditor(const FName InMenuName, const TWeakPtr<SDMMaterialEditor>& InEditorWidget);`
- L41 _public prototype_ `static UToolMenu* GenerateContextMenuLayer(const FName InMenuName, const TWeakPtr<SDMMaterialEditor>& InEditorWidget, UDMMaterialLayerObject* InLayerObject);`
- L44 _public prototype_ `static UToolMenu* GenerateContextMenuStage(const FName InMenuName, const TWeakPtr<SDMMaterialEditor>& InEditorWidget, const TWeakPtr<SDMMaterialStage>& InStageWidget);`
- L47 _public function_ `const TSharedPtr<SDMMaterialEditor> GetEditorWidget() const`
- L49 _public function_ `const TSharedPtr<SDMMaterialStage> GetStageWidget() const`
- L51 _public prototype_ `UDMMaterialSlot* GetSlot() const;`
- L53 _public prototype_ `UDynamicMaterialModelBase* GetPreviewModelBase() const;`
- L55 _public prototype_ `UDynamicMaterialModel* GetPreviewModel() const;`
- L57 _public prototype_ `UDMMaterialStage* GetStage() const;`
- L59 _public prototype_ `UDMMaterialStageSource* GetStageSource() const;`
- L61 _public prototype_ `UDMMaterialStageBlend* GetStageSourceAsBlend() const;`
- L63 _public prototype_ `UDMMaterialLayerObject* GetLayer() const;`
- L66 _protected member_ `TWeakPtr<SDMMaterialEditor> EditorWidgetWeak;`
- L67 _protected member_ `TWeakPtr<SDMMaterialStage> StageWidgetWeak;`
- L68 _protected member_ `TWeakObjectPtr<UDMMaterialLayerObject> LayerObjectWeak;`
- L70 _protected prototype_ `static UDMMenuContext* Create(const TWeakPtr<SDMMaterialEditor>& InEditorWidget, const TWeakPtr<SDMMaterialStage>& InStageWidget, UDMMaterialLayerObject* InLayerObject);`
- L73 _protected prototype_ `static UToolMenu* GenerateContextMenu(const FName InMenuName, const TWeakPtr<SDMMaterialEditor>& InEditorWidget, const TWeakPtr<SDMMaterialStage>& InStageWidget, UDMMaterialLayerObject* InLayerObject);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/UI/PropertyGenerators/DMComponentPropertyRowGenerator.h` (Public)


#### class `FDMComponentPropertyRowGenerator`  
`class FDMComponentPropertyRowGenerator`  
_L19-55_
- desc: Used to generate editable properties for objects editable in the Material Designer.
- L22 _public prototype_ `static const TSharedRef<FDMComponentPropertyRowGenerator>& Get();`
- L24 _public prototype_ `virtual ~FDMComponentPropertyRowGenerator() = default;`
- L33 _public prototype_ `virtual void AddComponentProperties(FDMComponentPropertyRowGeneratorParams& InParams);` — Generate properties for the given component. @param InComponentEditorWidget The edit widget generating the properties. @param InComponent The component being edited. @param InOutPropertyRows The generated rows. @param InOutProcessedObjects The already processed objects - add to this to avoid possible recursive generation.
- L39 _public prototype_ `virtual void AddPropertyEditRows(FDMComponentPropertyRowGeneratorParams& InParams, const FName& InProperty);` — Add the rows needed for a specific property. @param InProperty The name of the property.
- L47 _public prototype_ `virtual void AddPropertyEditRows(FDMComponentPropertyRowGeneratorParams& InParams, FProperty* InProperty, void* InMemoryPtr);` — Adds the rows needed for a specific property. @param InProperty The FProperty for this property. @param InMemoryPtr The pointer to the property's value in memory
- L50 _public prototype_ `virtual bool AllowKeyframeButton(UDMMaterialComponent* InComponent, FProperty* InProperty);`
- L54 _protected prototype_ `static bool IsDynamic(FDMComponentPropertyRowGeneratorParams& InParams);` — Returns true if the component edit widget is editing a Material Designer Dynamic.

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/UI/Utils/IDMWidgetLibrary.h` (Public)


#### struct `FDMPropertyHandleGenerateParams`  
`struct FDMPropertyHandleGenerateParams`  
_L16-24_
- L18 _public member_ `const SWidget* Widget;`
- L19 _public member_ `FNotifyHook* NotifyHook;`
- L20 _public member_ `UDynamicMaterialModelBase* PreviewMaterialModelBase;`
- L21 _public member_ `UDynamicMaterialModelBase* OriginalMaterialModelBase;`
- L22 _public member_ `UObject* Object;`
- L23 _public member_ `FName PropertyName;`

#### class `IDMWidgetLibrary`  
`class IDMWidgetLibrary`  
_L26-35_
- L29 _public prototype_ `virtual ~IDMWidgetLibrary() = default;`
- L31 _public prototype_ `static IDMWidgetLibrary& Get();`
- L34 _public prototype_ `virtual FDMPropertyHandle GetPropertyHandle(const FDMPropertyHandleGenerateParams& InParams) = 0;` — Creates a DM property handle for use in the details panel section of the Material Designer

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Utils/DMMaterialEffectStackPresetSubsystem.h` (Public)


#### class `UDMMaterialEffectStackPresetSubsystem`  
`class UDMMaterialEffectStackPresetSubsystem : public UEditorSubsystem`  
_L15-33_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UEditorSubsystem`
- L20 _public prototype_ `static UDMMaterialEffectStackPresetSubsystem* Get();`
- L23 _public prototype_ `bool SavePreset(const FString& InPresetName, const FDMMaterialEffectStackJson& InPreset) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L26 _public prototype_ `bool LoadPreset(const FString& InPresetName, FDMMaterialEffectStackJson& OutPreset) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L29 _public prototype_ `bool RemovePreset(const FString& InPresetName) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L32 _public prototype_ `TArray<FString> GetPresetNames() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Utils/DMMaterialFunctionFunctionLibrary.h` (Public)


#### class `UDMMaterialFunctionFunctionLibrary`  
`class UDMMaterialFunctionFunctionLibrary : public UBlueprintFunctionLibrary`  
_L22-36_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Material Function Function Library
- L27 _public prototype_ `static void ApplyMetaData(const FFunctionExpressionInput& InFunctionInput, const TSharedRef<IPropertyHandle>& InPropertyHandle);`
- L30 _public prototype_ `static EDMValueType GetInputValueType(UMaterialExpressionFunctionInput* InFunctionInput);`
- L32 _public prototype_ `static void SetInputDefault(UMaterialExpressionFunctionInput* InFunctionInput, UDMMaterialValue* InValue);`
- L35 _private prototype_ `static void SetInputDefault_Texture(UMaterialExpressionFunctionInput* InFunctionInput, UDMMaterialValueTexture* InTextureValue);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Utils/DMMaterialInstanceFunctionLibrary.h` (Public)


#### class `UDMMaterialInstanceFunctionLibrary`  
`class UDMMaterialInstanceFunctionLibrary : public UBlueprintFunctionLibrary`  
_L23-33_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Material Instance Function Library
- L28 _public prototype_ `static TArray<FDMObjectMaterialProperty> GetActorMaterialProperties(AActor* InActor);`
- L30 _public prototype_ `static bool SetMaterialInObject(FDMObjectMaterialProperty& InMaterialProperty, UDynamicMaterialInstance* InInstance);`
- L32 _public prototype_ `static UDynamicMaterialModel* CreateMaterialInObject(FDMObjectMaterialProperty& InMaterialProperty);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Utils/DMMaterialModelFunctionLibrary.h` (Public)


#### class `UDMMaterialModelFunctionLibrary`  
`class UDMMaterialModelFunctionLibrary : public UBlueprintFunctionLibrary`  
_L20-64_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Material / Model Function Library
- L25 _public prototype_ `static UDynamicMaterialInstance* ExportMaterial(UDynamicMaterialModelBase* InMaterialModelBase);`
- L27 _public prototype_ `static UDynamicMaterialInstance* ExportMaterial(UDynamicMaterialModelBase* InMaterialModel, const FString& InSavePath);`
- L29 _public prototype_ `static UMaterial* ExportGeneratedMaterial(UDynamicMaterialModelBase* InMaterialModelBase);`
- L31 _public prototype_ `static UMaterial* ExportGeneratedMaterial(UDynamicMaterialModelBase* InMaterialModelBase, const FString& InSavePath);`
- L33 _public prototype_ `static UDynamicMaterialModel* ExportToTemplateMaterialModel(UDynamicMaterialModelDynamic* InMaterialModelDynamic);`
- L35 _public prototype_ `static UDynamicMaterialModel* ExportToTemplateMaterialModel(UDynamicMaterialModelDynamic* InMaterialModelDynamic, const FString& InSavePath);`
- L37 _public prototype_ `static UDynamicMaterialInstance* ExportToTemplateMaterial(UDynamicMaterialModelDynamic* InMaterialModelDynamic);`
- L39 _public prototype_ `static UDynamicMaterialInstance* ExportToTemplateMaterial(UDynamicMaterialModelDynamic* InMaterialModelDynamic, const FString& InSavePath);`
- L41 _public prototype_ `static bool IsModelValid(UDynamicMaterialModelBase* InMaterialModelBase);`
- L43 _public prototype_ `static bool DuplicateModelBetweenMaterials(UDynamicMaterialModel* InFromModel, UDynamicMaterialInstance* InToInstance);`
- L45 _public prototype_ `static bool CreateModelInstanceInMaterial(UDynamicMaterialModel* InFromModel, UDynamicMaterialInstance* InToInstance);`
- L47 _public prototype_ `static FString RemoveAssetPrefix(const FString& InAssetName);`
- L49 _public prototype_ `static UDynamicMaterialModelBase* CreatePreviewModel(UDynamicMaterialModelBase* InOriginalModelBase);`
- L55 _public prototype_ `static void MirrorMaterialModel(UDynamicMaterialModelBase* InSource, UDynamicMaterialModelBase*& InTarget);` — Ensures that the source model is entirely mirrored to the target model by updating objects, rather than recreating them. Additions and removals are also propagated.
- L57 _public prototype_ `static UObject* FindSubobject(UObject* InOuter, FStringView InPath);`
- L60 _public function_ `template<typename InClassName> static InClassName* FindSubobject(UObject* InOuter, FStringView InPath)`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Utils/DMMaterialSlotFunctionLibrary.h` (Public)


#### class `UDMMaterialSlotFunctionLibrary`  
`class UDMMaterialSlotFunctionLibrary : public UBlueprintFunctionLibrary`  
_L30-74_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Material Slot Function Library
- L35 _public prototype_ `static UDMMaterialLayerObject* AddNewLayer_NewLocalValue(UDMMaterialSlot* InSlot, EDMValueType InValueType);`
- L37 _public prototype_ `static UDMMaterialLayerObject* AddNewLayer_NewLocalValue(UDMMaterialSlot* InSlot, TSubclassOf<UDMMaterialValue> InValueClass);`
- L40 _public prototype_ `static UDMMaterialLayerObject* AddNewLayer_GlobalValue(UDMMaterialSlot* InSlot, UDMMaterialValue* InValue);`
- L42 _public prototype_ `static UDMMaterialLayerObject* AddNewLayer_NewGlobalValue(UDMMaterialSlot* InSlot, EDMValueType InValueType);`
- L44 _public prototype_ `static UDMMaterialLayerObject* AddNewLayer_NewGlobalValue(UDMMaterialSlot* InSlot, TSubclassOf<UDMMaterialValue> InValueClass);`
- L47 _public prototype_ `static UDMMaterialLayerObject* AddNewLayer_Slot(UDMMaterialSlot* InTargetSlot, UDMMaterialSlot* InSourceSlot, EDMMaterialPropertyType InMaterialProperty);`
- L50 _public prototype_ `static UDMMaterialLayerObject* AddNewLayer_Expression(UDMMaterialSlot* InSlot, TSubclassOf<UDMMaterialStageExpression> InExpressionClass);`
- L53 _public prototype_ `static UDMMaterialLayerObject* AddNewLayer_Blend(UDMMaterialSlot* InSlot, TSubclassOf<UDMMaterialStageBlend> InBlendClass);`
- L56 _public prototype_ `static UDMMaterialLayerObject* AddNewLayer_Gradient(UDMMaterialSlot* InSlot, TSubclassOf<UDMMaterialStageGradient> InGradientClass);`
- L59 _public prototype_ `static UDMMaterialLayerObject* AddNewLayer_UV(UDMMaterialSlot* InSlot);`
- L61 _public prototype_ `static UDMMaterialLayerObject* AddNewLayer_MaterialFunction(UDMMaterialSlot* InSlot, UMaterialFunctionInterface* InFunction = nullptr);`
- L64 _public prototype_ `static UDMMaterialLayerObject* AddNewLayer_SceneTexture(UDMMaterialSlot* InSlot);`
- L66 _public prototype_ `static UDMMaterialLayerObject* AddNewLayer_Renderer(UDMMaterialSlot* InSlot, TSubclassOf<UDMRenderTargetRenderer> InRendererClass);`
- L69 _public prototype_ `static UDMMaterialLayerObject* AddNewLayer(UDMMaterialSlot* InSlot, UDMMaterialStage* InNewBaseStage = nullptr, UDMMaterialStage* InNewMaskStage = nullptr);`
- L72 _public prototype_ `static UDMMaterialLayerObject* AddTextureLayer(UDMMaterialSlot* InSlot, UTexture* InTexture, EDMMaterialPropertyType InPropertyType, bool bInReplaceSlot);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Utils/DMMaterialStageFunctionLibrary.h` (Public)


#### class `UDMMaterialStageFunctionLibrary`  
`class UDMMaterialStageFunctionLibrary : public UBlueprintFunctionLibrary`  
_L19-27_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Material Stage Function Library
- L24 _public prototype_ `static UDMMaterialStageInputValue* FindDefaultStageOpacityInputValue(UDMMaterialStage* InStage);`
- L26 _public prototype_ `static void SetStageInputToRenderer(UDMMaterialStage* InStage, TSubclassOf<UDMRenderTargetRenderer> InRendererClass, int32 InInputIndex);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Public/Utils/DMTextureSetFunctionLibrary.h` (Public)


#### class `UDMTextureSetFunctionLibrary`  
`class UDMTextureSetFunctionLibrary : public UBlueprintFunctionLibrary`  
_L16-31_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Material Stage Function Library
- L29 _public prototype_ `static bool AddTextureSetToModel(UDynamicMaterialModelEditorOnlyData* InEditorOnlyData, UDMTextureSet* InTextureSet, bool bInReplaceSlots);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Integrates a Texture Set with the given model's editor only data. @param InEditorOnlyData The editor only data for the model. @param InTextureSet The set to integrate. @param bInReplaceSlots Whether to add to or completely replace slots. @return True on success.
