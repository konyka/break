# Plugins / MetaHumanDefaultEditorPipeline

- module root: `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultEditorPipeline`
- headers: 11; symbols: 253
- symbol kinds: class=12, delegate=1, enum=2, enumerator=8, member=140, namespace=2, prototype=70, struct=18
- PrivateDependencyModuleNames: AssetTools, Blutility, ControlRigDeveloper, DataflowEngine, EditorScriptingUtilities, EditorWidgets, FileUtilities, GeometryScriptingCore, IKRig, ImageCore, Json, Kismet, MaterialEditor, MeshBoneReduction, MeshUtilities, MetaHumanCoreTechLib, MetaHumanSDKEditor, PerformanceCaptureCore, PluginUtils, Projects, PropertyEditor, RenderCore, RigLogicModule, SkeletalMeshUtilitiesCommon, Slate, SlateCore, SubobjectDataInterface, UnrealEd
- PublicDependencyModuleNames: ChaosClothAssetEngine, ChaosOutfitAssetEngine, Core, CoreUObject, Engine, HairStrandsCore, MetaHumanCharacter, MetaHumanCharacterEditor, MetaHumanCharacterPalette, MetaHumanCharacterPaletteEditor, MetaHumanCoreTech, MetaHumanDefaultPipeline, MetaHumanSDKRuntime, TextureGraph

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultEditorPipeline/Private/Customizations/MetaHumanMaterialBakingPropertiesDetailCustomization.h` (Private)


#### class `FMetaHumanMaterialBakingPropertiesDetailCustomization`  
`class FMetaHumanMaterialBakingPropertiesDetailCustomization : public IPropertyTypeCustomization`  
_L12-37_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for the FMetaHumanMaterialBakingProperties struct. Displays a segmented control to switch between Face and Body baking options, then shows output textures grouped by category with resolution selectors.
- L15 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L19 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L30 _private prototype_ `void AddBakingOptionsWidgets( IDetailChildrenBuilder& InChildBuilder, TSharedRef<IPropertyHandle> BakingOptionsHandle, TSharedPtr<EBakingTab> InActiveTab, EBakingTab Tab);`
- L36 _private member_ `TSharedPtr<EBakingTab> ActiveTab;`

#### enum `FMetaHumanMaterialBakingPropertiesDetailCustomization::EBakingTab`  
`enum class EBakingTab : uint8`  
_L24-28_
- L26 _public enumerator_ `Head`
- L27 _public enumerator_ `Body`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultEditorPipeline/Private/MetaHumanCharacterPipelineData.h` (Private)


#### struct `FCharacterPipelineData`  
`struct FCharacterPipelineData`  
_L18-62_
- reflection: `USTRUCT()`
- desc: Transient data for a Character used during assembly
- L23 _public member_ `TObjectPtr<USkeletalMesh> FaceMesh;` — `UPROPERTY()`
- L25 _public member_ `TObjectPtr<USkeletalMesh> BodyMesh;` — `UPROPERTY()`
- L28 _public member_ `FMetaHumanCharacterGeneratedAssets GeneratedAssets;` — `UPROPERTY()`
- L29 _public member_ `bool bIsGeneratedAssetsValid = false;`
- L32 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> FaceRemovedMaterialSlots;` — `UPROPERTY()`
- L35 _public member_ `TArray<TObjectPtr<UTexture2D>> FaceBakedNormalsTextures;` — `UPROPERTY()`
- L38 _public member_ `TObjectPtr<UTexture2D> FollicleMap;` — `UPROPERTY()`
- L41 _public member_ `TArray<TObjectPtr<UTexture>> PreBakedGroomTextures;` — `UPROPERTY()`
- L44 _public member_ `TArray<UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture> HeadHiddenFaceMaps;` — `UPROPERTY()`
- L46 _public member_ `TArray<UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture> BodyHiddenFaceMaps;` — `UPROPERTY()`
- L53 _public member_ `TArray<int32> FaceMaterialChangesPerLOD;` — Each time a material parameter (or set of material parameters) is changed on a face mesh LOD, the entry of the index of that LOD should be incremented in this array. It will be used to determine which face LODs have unique materials and need to be baked separately.
- L56 _public member_ `TObjectPtr<USkeletalMesh> MergedHeadAndBody;` — `UPROPERTY()`
- L58 _public member_ `bool bTransferSkinWeights = true;`
- L59 _public member_ `bool bStripSimMesh = false;`
- L60 _public member_ `bool bHideHair = false;`
- L61 _public member_ `bool bForceCards = false;`

#### class `UCharacterPipelineDataMap`  
`class UCharacterPipelineDataMap : public UObject`  
_L69-76_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: A containing object for FCharacterPipelineData, so that temporary objects it references are visible to GC.
- L75 _public member_ `TMap<FMetaHumanPaletteItemKey, FCharacterPipelineData> Map;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultEditorPipeline/Private/MetaHumanDefaultEditorPipelineLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanDefaultEditorPipeline, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanDefaultEditorPipeline, Log, All);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultEditorPipeline/Public/Item/MetaHumanGroomEditorPipeline.h` (Public)


#### struct `FMetaHumanGroomPipelineBuildInput`  
`struct FMetaHumanGroomPipelineBuildInput`  
_L12-22_
- reflection: `USTRUCT()`
- L18 _public member_ `TArray<TObjectPtr<USkeletalMesh>> BindingMeshes;` — `UPROPERTY()`
- L21 _public member_ `TArray<int32> FaceLODs;` — `UPROPERTY()`

#### class `UMetaHumanGroomEditorPipeline`  
`class UMetaHumanGroomEditorPipeline : public UMetaHumanItemEditorPipeline`  
_L25-39_
- reflection: `UCLASS(EditInlineNew)`
- inherits: `UMetaHumanItemEditorPipeline`
- L30 _public prototype_ `UMetaHumanGroomEditorPipeline();`
- L32 _public prototype_ `virtual UE::Tasks::TTask<FMetaHumanPaletteBuiltData> BuildItem(const FBuildItemParams& Params) const override;`
- L34 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterEditorPipelineSpecification*> GetSpecification() const override;`
- L38 _private member_ `TObjectPtr<UMetaHumanCharacterEditorPipelineSpecification> Specification;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultEditorPipeline/Public/Item/MetaHumanOutfitEditorPipeline.h` (Public)


#### struct `FMetaHumanOutfitPipelineBuildCharacterData`  
`struct FMetaHumanOutfitPipelineBuildCharacterData`  
_L15-33_
- reflection: `USTRUCT()`
- L20 _public member_ `TObjectPtr<USkeletalMesh> MergedHeadAndBody;` — `UPROPERTY()`
- L23 _public member_ `bool bTransferSkinWeights = true;` — `UPROPERTY()`
- L26 _public member_ `bool bGenerateLOD0Only = false;` — `UPROPERTY()`
- L29 _public member_ `bool bStripSimMesh = false;` — `UPROPERTY()`
- L32 _public member_ `TObjectPtr<USkeleton> SkeletonForOutputMesh;` — `UPROPERTY()`

#### struct `FMetaHumanOutfitPipelineBuildInput`  
`struct FMetaHumanOutfitPipelineBuildInput`  
_L36-51_
- reflection: `USTRUCT()`
- L41 _public member_ `TObjectPtr<UDataflow> OutfitResizeDataflowAsset;` — `UPROPERTY()`
- L44 _public member_ `FName TargetBodyPropertyName;` — `UPROPERTY()`
- L47 _public member_ `FName ResizableOutfitPropertyName;` — `UPROPERTY()`
- L50 _public member_ `TMap<FMetaHumanPaletteItemKey, FMetaHumanOutfitPipelineBuildCharacterData> CharacterData;` — `UPROPERTY()`

#### class `UMetaHumanOutfitEditorPipeline`  
`class UMetaHumanOutfitEditorPipeline : public UMetaHumanItemEditorPipeline`  
_L54-98_
- reflection: `UCLASS(EditInlineNew)`
- inherits: `UMetaHumanItemEditorPipeline`
- L59 _public prototype_ `UMetaHumanOutfitEditorPipeline();`
- L61 _public prototype_ `virtual UE::Tasks::TTask<FMetaHumanPaletteBuiltData> BuildItem(const FBuildItemParams& Params) const override;`
- L63 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterEditorPipelineSpecification*> GetSpecification() const override;`
- L66 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L83 _public member_ `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture HeadHiddenFaceMapTexture;` — `UPROPERTY(EditAnywhere, Category = "Outfit")` — If this clothing covers any part of the head mesh, you may want to provide a hidden face map to remove or shrink the head geometry out of the way of the clothing. This helps to prevent the head and clothing geometry from intersecting, especially at lower LODs where the geometry is coarser. The skin mesh sections will sample in their UV space from this map to determine if they should be removed, shrunk or left unmodified. Shrinking is useful for geometry near the edges of the clothing that is partly visible. Note that for backwards compatibility with the previous geometry removal system, all three color channels are sampled and the highest of the three values is used.
- L90 _public member_ `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture BodyHiddenFaceMapTexture;` — `UPROPERTY(EditAnywhere, Category = "Outfit")` — This hidden face map works in the same way as the HeadHiddenFaceMapTexture, except it's applied to the body mesh.
- L94 _private member_ `TObjectPtr<UTexture2D> BodyHiddenFaceMap_DEPRECATED;` — `UPROPERTY()`
- L97 _private member_ `TObjectPtr<UMetaHumanCharacterEditorPipelineSpecification> Specification;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultEditorPipeline/Public/Item/MetaHumanSkeletalMeshEditorPipeline.h` (Public)


#### class `UMetaHumanSkeletalMeshEditorPipeline`  
`class UMetaHumanSkeletalMeshEditorPipeline : public UMetaHumanItemEditorPipeline`  
_L15-53_
- reflection: `UCLASS(EditInlineNew)`
- inherits: `UMetaHumanItemEditorPipeline`
- L20 _public prototype_ `UMetaHumanSkeletalMeshEditorPipeline();`
- L22 _public prototype_ `virtual UE::Tasks::TTask<FMetaHumanPaletteBuiltData> BuildItem(const FBuildItemParams& Params) const override;`
- L24 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterEditorPipelineSpecification*> GetSpecification() const override;`
- L41 _public member_ `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture HeadHiddenFaceMapTexture;` — `UPROPERTY(EditAnywhere, Category = "Outfit")` — If this clothing covers any part of the head mesh, you may want to provide a hidden face map to remove or shrink the head geometry out of the way of the clothing. This helps to prevent the head and clothing geometry from intersecting, especially at lower LODs where the geometry is coarser. The skin mesh sections will sample in their UV space from this map to determine if they should be removed, shrunk or left unmodified. Shrinking is useful for geometry near the edges of the clothing that is partly visible. Note that for backwards compatibility with the previous geometry removal system, all three color channels are sampled and the highest of the three values is used.
- L48 _public member_ `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture BodyHiddenFaceMapTexture;` — `UPROPERTY(EditAnywhere, Category = "Outfit")` — This hidden face map works in the same way as the HeadHiddenFaceMapTexture, except it's applied to the body mesh.
- L52 _private member_ `TObjectPtr<UMetaHumanCharacterEditorPipelineSpecification> Specification;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultEditorPipeline/Public/MetaHumanDefaultEditorPipeline.h` (Public)


#### class `UMetaHumanDefaultEditorPipeline`  
`class UMetaHumanDefaultEditorPipeline : public UMetaHumanDefaultEditorPipelineBase`  
_L13-20_
- reflection: `UCLASS(EditInlineNew)`
- inherits: `UMetaHumanDefaultEditorPipelineBase`
- desc: Editor pipeline for UMetaHumanDefaultPipeline
- L18 _public prototype_ `virtual UBlueprint* WriteActorBlueprint(const FWriteBlueprintSettings& InWriteBlueprintSettings) const override;`
- L19 _public prototype_ `virtual bool UpdateActorBlueprint(const UMetaHumanInstance* InCharacterInstance, UBlueprint* InBlueprint) const override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultEditorPipeline/Public/MetaHumanDefaultEditorPipelineActor.h` (Public)


#### struct `FMetaHumanComponentMaterials`  
`struct FMetaHumanComponentMaterials`  
_L11-20_
- reflection: `USTRUCT()`
- desc: Used to store the original materials for a component while they're being overridden
- L16 _public member_ `TWeakObjectPtr<class UMeshComponent> MeshComponent;` — `UPROPERTY()`
- L19 _public member_ `TArray<TObjectPtr<class UMaterialInterface>> Materials;` — `UPROPERTY()`

#### class `AMetaHumanDefaultEditorPipelineActor`  
`class AMetaHumanDefaultEditorPipelineActor : public AMetaHumanCharacterEditorActor`  
_L26-93_
- reflection: `UCLASS()`
- inherits: `AMetaHumanCharacterEditorActor`
- desc: A preview actor that supports all features of the MetaHuman Default Character Pipeline
- L32 _public prototype_ `AMetaHumanDefaultEditorPipelineActor();`
- L35 _public prototype_ `virtual void InitializeMetaHumanCharacterEditorActor( TNotNull<const UMetaHumanInstance*> InCharacterInstance, TNotNull<UMetaHumanCharacter*> InCharacter, TNotNull<USkeletalMesh*> InFaceMesh, TNotNull<USkeletalMesh*> InBodyMesh, int32 InNumLODs, const TArray<int32>& InFaceLODMapping, const TArray<int32>& InBodyLODMapping) override;`
- L44 _public prototype_ `virtual void SetHairVisibilityState(EMetaHumanHairVisibilityState State) override;`
- L45 _public prototype_ `virtual void SetClothingVisibilityState(EMetaHumanClothingVisibilityState State, UMaterialInterface* OverrideMaterial = nullptr) override;`
- L49 _protected prototype_ `virtual void OnInstanceUpdated();`
- L51 _protected prototype_ `virtual void SetUseCardsOnGroomComponents(bool bInUseCards);`
- L54 _protected member_ `TObjectPtr<class UGroomComponent> HairComponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")`
- L57 _protected member_ `TObjectPtr<class UGroomComponent> EyebrowsComponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")`
- L60 _protected member_ `TObjectPtr<class UGroomComponent> BeardComponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")`
- L63 _protected member_ `TObjectPtr<class UGroomComponent> MustacheComponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")`
- L66 _protected member_ `TObjectPtr<class UGroomComponent> EyelashesComponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")`
- L69 _protected member_ `TObjectPtr<class UGroomComponent> PeachfuzzComponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")`
- L72 _protected member_ `TArray<TObjectPtr<class UChaosClothComponent>> ClothComponents;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")`
- L75 _protected member_ `TArray<TObjectPtr<class USkeletalMeshComponent>> OutfitMeshComponents;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")`
- L78 _protected member_ `TArray<TObjectPtr<class USkeletalMeshComponent>> SkeletalMeshComponents;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")`
- L82 _private member_ `TArray<FMetaHumanComponentMaterials> SavedMaterials;` — `UPROPERTY()`
- L85 _private member_ `EMetaHumanHairVisibilityState CurrentHairState = EMetaHumanHairVisibilityState::Shown;` — `UPROPERTY()`
- L88 _private member_ `EMetaHumanClothingVisibilityState CurrentClothingState = EMetaHumanClothingVisibilityState::Shown;` — `UPROPERTY()`
- L91 _private member_ `TObjectPtr<UMaterialInterface> CurrentOverrideMaterial;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultEditorPipeline/Public/MetaHumanDefaultEditorPipelineBase.h` (Public)


#### struct `FMetaHumanInputTextureProperties`  
`struct FMetaHumanInputTextureProperties`  
_L36-52_
- reflection: `USTRUCT()`
- L43 _public member_ `FName SourceMaterialSlotName;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The name of the material slot on the face mesh that this material is set on
- L47 _public member_ `FName SourceMaterialParameterName;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The name of the material parameter that this texture is set on, on the source material
- L51 _public member_ `FName InputParameterName;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The name of the input parameter for this texture in the Texture Graph

#### struct `FMetaHumanInputMaterialProperties`  
`struct FMetaHumanInputMaterialProperties`  
_L55-77_
- reflection: `USTRUCT()`
- L62 _public member_ `FName SourceMaterialSlotName;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The name of the material slot on the face mesh that this material is set on
- L66 _public member_ `FName InputParameterName;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The name of the input parameter for this material in the Texture Graph
- L76 _public member_ `int32 MainSectionTopLODIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — If the source material slot is part of a group of slots with one for each LOD, set this to the best LOD index that the source material is used on. Where supported, this will be used to skip baking materials for LODs when the baked material would be the same as a better LOD.

#### struct `FMetaHumanOutputTextureProperties`  
`struct FMetaHumanOutputTextureProperties`  
_L80-123_
- reflection: `USTRUCT()`
- L86 _public member_ `FName Category;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking", meta = (GetOptions = "GetTextureCategories"))` — Category to group this texture in
- L90 _public member_ `TArray<int32> UsedInLODs;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — List of LODs this texture is used. If empty it means the texture is used in all LODs
- L94 _public member_ `FName OutputTextureNameInGraph;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The name of the output parameter in the Texture Graph Instance's Export Settings
- L98 _public member_ `FString OutputTextureFolder;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The relative path to the folder where the output texture should be written
- L102 _public member_ `FName OutputTextureName;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The name that the output texture should be given. Leave as None to use the texture name from the Texture Graph Instance.
- L106 _public member_ `bool bOutputsVirtualTexture = false;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — Indicates this will output a virtual texture if support is enabled
- L110 _public member_ `FName OutputVirtualTextureName;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking", meta = (EditCondition = "bOutputsVirtualTexture", EditConditionHides))` — Name of the texture asset if virtual texture support is enabled
- L114 _public member_ `TArray<FName> OutputMaterialSlotNames;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — Names of the material slots where this texture will be set
- L118 _public member_ `FName OutputMaterialParameterName;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The name of the material parameter that this texture should be set on on the output material
- L122 _public member_ `FName OutputMaterialParameterNameVT;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking", meta = (EditCondition = "bOutputsVirtualTexture", EditConditionHides))` — The name of the material parameter that this texture should be set if Virtual Texture its a Virtual Texture

#### struct `FMetaHumanTextureGraphOutputProperties`  
`struct FMetaHumanTextureGraphOutputProperties`  
_L126-143_
- reflection: `USTRUCT()`
- L133 _public member_ `TObjectPtr<UTextureGraphInstance> TextureGraphInstance;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The Texture Graph Instance to use as a template for this bake
- L136 _public member_ `TMap<FName, float> InputValues;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")`
- L139 _public member_ `TArray<FMetaHumanInputMaterialProperties> InputMaterials;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")`
- L142 _public member_ `TArray<FMetaHumanOutputTextureProperties> OutputTextures;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")`

#### struct `FMetaHumanBakedMaterialProperties`  
`struct FMetaHumanBakedMaterialProperties`  
_L146-190_
- reflection: `USTRUCT()`
- L153 _public member_ `FName PrimaryMaterialSlotName;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The name of the main material slot on the baked mesh that this material should be set on
- L157 _public member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The material to use as the parent for the generated material instance
- L161 _public member_ `bool bOutputsMaterialWithVirtualTextures = false;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — Indicates this may output a material with Virtual Texture support if enabled
- L165 _public member_ `TObjectPtr<UMaterialInterface> MaterialVT;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking", meta = (EditCondition = "bOutputsMaterialWithVirtualTextures", EditConditionHides))` — The material to use as parent of for the generated material instance if Virtual Texture support is enabled
- L169 _public member_ `TArray<FName> AdditionalMaterialSlotNames;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The name of any other material slots on the baked mesh that this material should be set on
- L173 _public member_ `FString OutputMaterialFolder;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The relative path to the folder where the generated material instance should be written
- L177 _public member_ `FName OutputMaterialName;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The name that the generated material instance should be given
- L181 _public member_ `FName OutputMaterialNameVT;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking", meta = (EditCondition = "bOutputsMaterialWithVirtualTextures", EditConditionHides))` — The name that the generated material instance should be given if Virtual Texture support is enabled
- L185 _public member_ `bool bCopyAllNumericalParameters = false;` — `UPROPERTY(EditAnywhere, Category = "Material Parameters")` — Copy all numerical parameters from the input material defined in PrimaryMaterialSlotName
- L189 _public member_ `TArray<FName> ParametersToCopy;` — `UPROPERTY(EditAnywhere, Category = "Material Parameters")` — List of individual parameters to copy from the input material defined in PrimaryMaterialSlotName

#### enum `EMetaHumanBuildTextureResolution`  
`enum class EMetaHumanBuildTextureResolution : int32`  
_L193-201_
- reflection: `UENUM()`
- L195 _public enumerator_ `Res256 = 256 UMETA(DisplayName = "256")`
- L196 _public enumerator_ `Res512 = 512 UMETA(DisplayName = "512")`
- L197 _public enumerator_ `Res1024 = 1024 UMETA(DisplayName = "1k")`
- L198 _public enumerator_ `Res2048 = 2048 UMETA(DisplayName = "2k")`
- L199 _public enumerator_ `Res4096 = 4096 UMETA(DisplayName = "4k")`
- L200 _public enumerator_ `Res8192 = 8192 UMETA(DisplayName = "8k")`

#### struct `FMetaHumanHairProperties`  
`struct FMetaHumanHairProperties`  
_L204-285_
- reflection: `USTRUCT()`
- L211 _public member_ `TArray<FName> FollicleMapMaterialSlotNames;` — `UPROPERTY(EditAnywhere, Category = "Hair")` — The material slots on the face mesh to set the follicle map on
- L215 _public member_ `FName FollicleMapMaterialParameterName;` — `UPROPERTY(EditAnywhere, Category = "Hair")` — The material parameter to set the follicle map on
- L225 _public member_ `FName UseFollicleMapMaterialParameterName;` — `UPROPERTY(EditAnywhere, Category = "Hair")` — The material parameter to set to true when a follicle map should be used. Will be set to false when there is no follicle map. If this parameter isn't required, leave this property as None.
- L229 _public member_ `int32 FollicleMapRootRadius = 8;` — `UPROPERTY(EditAnywhere, Category = "Hair")` — Size of the root in the follicle mask (in pixels)
- L233 _public member_ `EMetaHumanBuildTextureResolution FollicleMapResolution = EMetaHumanBuildTextureResolution::Res4096;` — `UPROPERTY(EditAnywhere, Category = "Hair")` — The resolution that the follicle map should be generated at
- L251 _public member_ `bool bUsePreBakedGrooms = false;` — `UPROPERTY(EditAnywhere, Category = "Pre-Baked Grooms")` — Pre-Baked Grooms are an optimization that reduces the number of texture samplers needed in the skin material. Read on for more information. Grooms with short hair are often baked into the skin material, especially at low LODs, to save the cost of having separate Groom Components for them. In order to support multiple grooms at once (beard, eyebrows, etc), the skin material needs to sample from multiple textures. This can cause it to go beyond the maximum number of texture samplers, if other features are enabled that also sample from many textures. The Pre-Baked Grooms feature bakes multiple grooms into a set of two textures, which the skin material then samples from. This allows several grooms to be baked into the skin for the cost of two texture samplers.
- L259 _public member_ `TObjectPtr<UMaterialInterface> PreBakedGroomGeneratorMaterial;` — `UPROPERTY(EditAnywhere, Category = "Pre-Baked Grooms", meta = (EditCondition = "bUsePreBakedGrooms"))` — The material to use for generating the pre-baked groom textures. Must have the same parameters as the skin material for baked grooms.
- L266 _public member_ `TObjectPtr<UTextureGraphInstance> PreBakedGroomTextureGraphInstance;` — `UPROPERTY(EditAnywhere, Category = "Pre-Baked Grooms", meta = (EditCondition = "bUsePreBakedGrooms"))` — A Texture Graph Instance that maps the output of the generator material to the pre-baked groom textures.
- L270 _public member_ `FName PreBakedGroomTextureGraphInputName;` — `UPROPERTY(EditAnywhere, Category = "Pre-Baked Grooms", meta = (EditCondition = "bUsePreBakedGrooms"))` — The name of the material node in the Texture Graph
- L284 _public member_ `TArray<FMetaHumanOutputTextureProperties> PreBakedGroomTextureGraphOutputTextures;` — `UPROPERTY(EditAnywhere, Category = "Pre-Baked Grooms", meta = (EditCondition = "bUsePreBakedGrooms"))` — Setup for the generated pre-baked groom textures. Note that there are some restrictions on this for pre-baked groom textures specifically: 1. Only non-virtual textures are supported 2. OutputTextureName must be set to a valid, unique name Also note that OutputMaterialSlotNames is ignored, as the setup for this is generated procedurally.

#### struct `FMetaHumanCostumeProperties`  
`struct FMetaHumanCostumeProperties`  
_L288-295_
- reflection: `USTRUCT()`
- L294 _public member_ `TObjectPtr<UDataflow> OutfitResizeDataflowAsset;` — `UPROPERTY(EditAnywhere, Category = "Costume")`

#### struct `FMetaHumanBodyRigLogicProperties`  
`struct FMetaHumanBodyRigLogicProperties`  
_L298-318_
- reflection: `USTRUCT()`
- L305 _public member_ `TObjectPtr<UControlRigBlueprint> ControlRig;` — `UPROPERTY(EditAnywhere, Category = "Body")` — The Control Rig to use to unpack Swing/Twist and Half Rotation solvers to. If none is specified a new one will be created.
- L309 _public member_ `bool bUnpackRbfToPoseAssets = false;` — `UPROPERTY(EditAnywhere, Category = "Body RigLogic")` — Unpack the RBF Solvers to PoseAssets and AnimSequences. If PostProcessAnimBp is set, PoseDriver nodes will also be created inside it.
- L313 _public member_ `bool bUnpackFingerHalfRotationsToControlRig = false;` — `UPROPERTY(EditAnywhere, Category = "Body RigLogic", meta = (EditCondition = "bUnpackRbfToPoseAssets"))` — Unpack the finger half rotation RBF solvers to Control Rig for improved performance.
- L317 _public member_ `bool bUnpackSwingTwistToControlRig = false;` — `UPROPERTY(EditAnywhere, Category = "Body RigLogic")` — Unpack the Swing/Twist setup to Control Rig.

#### struct `FMetaHumanBodyProperties`  
`struct FMetaHumanBodyProperties`  
_L321-337_
- reflection: `USTRUCT()`
- L329 _public member_ `class TSoftClassPtr<UAnimInstance> PostProcessAnimBp;` — `UPROPERTY(EditAnywhere, Category = "Body")` — Override the PostProcess AnimBlueprint on the newly created body SkeletalMesh. If UnpackRigLogic is enabled, it will also be used to unpack the RBF Solvers and Control Rig to. If none is specified when unpacking is enabled only PoseAssets will be created.
- L333 _public member_ `bool bUnpackRigLogic = false;` — `UPROPERTY(EditAnywhere, Category = "Body")` — Unpack the body's RigLogic data (RBF solvers and Swing/Twist setup) into standard UE animation assets - PoseAssets/AnimSequences, PoseDriver nodes in the PostProcess AnimBlueprint, and a Control Rig - using the options below. When disabled, RigLogic is evaluated at runtime instead.
- L336 _public member_ `FMetaHumanBodyRigLogicProperties BodyRigLogicUnpackProperties;` — `UPROPERTY(EditAnywhere, Category = "Body", meta = (EditCondition = "bUnpackRigLogic", EditConditionHides))`

#### struct `FMetaHumanLODProperties`  
`struct FMetaHumanLODProperties`  
_L344-371_
- reflection: `USTRUCT()`
- desc: Configures the MetaHuman LODs that the pipeline uses to build a character
- L350 _public member_ `TArray<int32> FaceLODs;` — `UPROPERTY(EditAnywhere, Category = "Face")` — Which LODs of the Face are going to be in the built MetaHuman. If empty all LODs are going to be exported
- L354 _public member_ `TArray<int32> BodyLODs;` — `UPROPERTY(EditAnywhere, Category = "Body")` — Which LODs of the Body are going to be in the built MetaHuman. If empty all LODs are going to be exported
- L358 _public member_ `bool bOverrideFaceLODSettings = false;` — `UPROPERTY(EditAnywhere, Category = "LOD Settings", meta = (InlineEditConditionToggle))` — Whether or not to override the Face Skeletal Mesh LOD Settings
- L362 _public member_ `bool bOverrideBodyLODSettings = false;` — `UPROPERTY(EditAnywhere, Category = "LOD Settings", meta = (InlineEditConditionToggle))` — Whether or not to override the Body Skeletal Mesh LOD Settings
- L366 _public member_ `TSoftObjectPtr<class USkeletalMeshLODSettings> FaceLODSettings;` — `UPROPERTY(EditAnywhere, Category = "LOD Settings", meta = (EditCondition = "bOverrideFaceLODSettings"))` — LOD Settings asset to set to the exported Face Mesh
- L370 _public member_ `TSoftObjectPtr<class USkeletalMeshLODSettings> BodyLODSettings;` — `UPROPERTY(EditAnywhere, Category = "LOD Settings", meta = (EditCondition = "bOverrideBodyLODSettings"))` — LOD Settings asset to set to the exported Body Mesh

#### class `ULODBakingUtility`  
`class ULODBakingUtility : public UEditorUtilityObject`  
_L378-387_
- reflection: `UCLASS(Abstract, Blueprintable)`
- inherits: `UEditorUtilityObject`
- desc: Base class for an Editor Utility Object that is capable of baking the Normals of a skeletal mesh into a texture
- L385 _public prototype_ `UPARAM(DisplayName = "Baked Texture") TArray<UTexture2D*> BakeTangentNormals(USkeletalMesh* InTarget, class UGeometryScriptDebug* InDebug);` — `UFUNCTION(BlueprintImplementableEvent)`

#### class `UMetaHumanMaterialBakingSettings`  
`class UMetaHumanMaterialBakingSettings : public UDataAsset`  
_L390-424_
- reflection: `UCLASS()`
- inherits: `UDataAsset`
- L398 _public member_ `TArray<FName> TextureCategories;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — List of categories to group textures. This defines the order in which the categories are dipslayed in the details panel
- L402 _public member_ `TArray<FMetaHumanTextureGraphOutputProperties> TextureGraphs;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The Texture Graphs to use for baking
- L406 _public member_ `TArray<FMetaHumanBakedMaterialProperties> BakedMaterials;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — The output materials that the baked textures should be set on
- L410 _public member_ `TSubclassOf<ULODBakingUtility> LODBakingUtilityClass;` — `UPROPERTY(EditAnywhere, Category = "LOD Baking")` — The class responsible for baking the normals for use in higher LODs
- L417 _public member_ `bool bGenerateTextureGraphInstanceAssets = false;` — `UPROPERTY(EditAnywhere, Category = "Texture Baking")` — If this is enabled, the Texture Graph Instances and source textures for the bake will be generated as assets so that the user can inspect them and re-run the bake if they wish.
- L422 _public prototype_ `const TArray<FName>& GetTextureCategories() const;` — `UFUNCTION()`

#### struct `FMetaHumanMaterialBakingOptions`  
`struct FMetaHumanMaterialBakingOptions`  
_L430-446_
- reflection: `USTRUCT()`
- desc: Options to configure how the pipeline should bake textures
- L436 _public member_ `TSoftObjectPtr<UMetaHumanMaterialBakingSettings> BakingSettings;` — `UPROPERTY(EditAnywhere, Category = "Baking")` — A settings object containing the texture graphs to be executed and their outputs
- L442 _public member_ `TMap<FName, EMetaHumanBuildTextureResolution> TextureResolutionsOverrides;` — `UPROPERTY(EditAnywhere, Category = "Baking")` — Overrides for the output texture resolutions The key is the OutputTextureName
- L445 _public prototype_ `void RefreshTextureResolutionsOverrides();` — `UE_DEPRECATED(5.8, "Resolution overrides are now managed by the detail customization")`

#### struct `FMetaHumanMaterialBakingProperties`  
`struct FMetaHumanMaterialBakingProperties`  
_L452-463_
- reflection: `USTRUCT()`
- desc: Holds the material baking options for face and body
- L458 _public member_ `FMetaHumanMaterialBakingOptions FaceBakingOptions;` — `UPROPERTY(EditAnywhere, Category = "Baking")` — Configure the material face baking options
- L462 _public member_ `FMetaHumanMaterialBakingOptions BodyBakingOptions;` — `UPROPERTY(EditAnywhere, Category = "Baking")` — Configure the material body baking options

#### struct `FMetaHumanBuildTextureProperties`  
`struct FMetaHumanBuildTextureProperties`  
_L469-476_
- reflection: `USTRUCT()`
- desc: Options to configure the resolutions of synthesized textures
- L475 _public member_ `TMap<EFaceTextureType, EMetaHumanBuildTextureResolution> Face;` — `UPROPERTY(EditAnywhere, Category = "Face")` — Set the override resolutions of the synthesized face textures

#### class `UMetaHumanDefaultEditorPipelineBase`  
`class UMetaHumanDefaultEditorPipelineBase : public UMetaHumanCollectionEditorPipeline`  
_L482-694_
- reflection: `UCLASS(Abstract)`
- inherits: `UMetaHumanCollectionEditorPipeline`
- desc: Common base class for editor pipelines of UMetaHumanDefaultPipelineBase
- L487 _public prototype_ `UMetaHumanDefaultEditorPipelineBase();`
- L490 _public prototype_ `virtual void PostLoad() override;`
- L491 _public prototype_ `virtual void PostInitProperties() override;`
- L494 _public prototype_ `virtual void BuildCollection(const FBuildCollectionParams& Params, const FOnBuildComplete& OnComplete) const override;`
- L496 _public prototype_ `virtual bool CanBuild() const override;`
- L498 _public prototype_ `virtual bool ShouldCookInstanceAsAssembled(TNotNull<const UMetaHumanInstance*> Instance) const override;`
- L500 _public prototype_ `virtual void UnpackCollectionAssets( TNotNull<const UMetaHumanCollection*> Collection, FMetaHumanCollectionBuiltData& CollectionBuiltData, const FOnUnpackComplete& OnComplete) const override;`
- L505 _public prototype_ `virtual bool TryUnpackInstanceAssets( TNotNull<UMetaHumanInstance*> Instance, FInstancedStruct& AssemblyOutput, TArray<FMetaHumanGeneratedAssetMetadata>& AssemblyAssetMetadata, const FString& TargetFolder) const override;`
- L511 _public prototype_ `virtual EMetaHumanWardrobeItemCompatibility TestWardrobeItemCompatibilityWithSlot(FName InSlotName, TNotNull<const UMetaHumanWardrobeItem*> InWardrobeItem) const override;`
- L513 _public prototype_ `virtual void SetValidationContext(TScriptInterface<class IMetaHumanValidationContext> InValidationContext) override;`
- L515 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterEditorPipelineSpecification*> GetSpecification() const override;`
- L516 _public prototype_ `virtual TSubclassOf<AActor> GetEditorActorClass() const override;`
- L519 _public member_ `TSubclassOf<AActor> EditorActorClass;` — `UPROPERTY(EditAnywhere, Category = "Pipeline", meta = (MustImplement = "/Script/MetaHumanCharacterPaletteEditor.MetaHumanCharacterEditorActorInterface"))`
- L523 _public member_ `TSoftObjectPtr<class USkeleton> FaceSkeleton;` — `UPROPERTY(EditAnywhere, Category = "Dependencies|Skeletons", meta = (PipelineDisplay = "Advanced"))` — Which Face Skeleton to use.
- L527 _public member_ `TSoftObjectPtr<class USkeleton> BodySkeleton;` — `UPROPERTY(EditAnywhere, Category = "Dependencies|Skeletons", meta = (PipelineDisplay = "Advanced"))` — Which Body Skeleton to use.
- L533 _public member_ `bool bOptimizeBoneCounts = true;` — `UPROPERTY(EditAnywhere, Category = "Animation", meta = ( PipelineDisplay = "Advanced", ToolTip = "Optimizes bone counts for all generated skeletal meshes except the Body by removing bones that do not have vertices weighted against them from all LODs. The Body mesh is excluded because it serves as the driving skeletal mesh and must retain unweighted bones (such as corrective bones) so other meshes can correctly copy bone transforms from and follow it."))` — Bone count optimization.
- L540 _public member_ `bool bBakeMaterials;` — `UPROPERTY(EditAnywhere, Category = "Materials", meta = (PipelineDisplay = "Materials"))` — If enabled, the materials used in editor will be baked down to textures, so that the built MetaHuman can use simplified materials that are faster to render.
- L544 _public member_ `bool bScalableNormals = false;` — `UPROPERTY(EditAnywhere, Category = "Materials", meta = (EditConditionHides, EditCondition = "bBakeMaterials", PipelineDisplay = "Materials"))` — Whether to enable scalable normals on skin materials
- L548 _public member_ `FName ScalableNormalsType;` — `UPROPERTY(EditAnywhere, Category = "Materials", meta = (GetOptions = GetScalableNormalsTypeOptions, EditConditionHides, EditCondition = "bScalableNormals && bBakeMaterials", PipelineDisplay = "Materials"))` — Scalable normals preset to apply, configured in MetaHuman Character Editor Settings
- L552 _public member_ `FMetaHumanMaterialBakingProperties MaterialBakingOptions;` — `UPROPERTY(EditAnywhere, Category = "Materials", meta = (EditCondition = "bBakeMaterials", EditConditionHides, PipelineDisplay = "Materials"))` — Material baking options for face and body
- L556 _public member_ `FMetaHumanMaterialBakingOptions FaceMaterialBakingOptions_DEPRECATED;` — `UE_DEPRECATED(5.8, "Use MaterialBakingOptions.FaceBakingOptions instead")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use MaterialBakingOptions.FaceBakingOptions instead"))`
- L560 _public member_ `FMetaHumanMaterialBakingOptions BodyMaterialBakingOptions_DEPRECATED;` — `UE_DEPRECATED(5.8, "Use MaterialBakingOptions.BodyBakingOptions instead")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use MaterialBakingOptions.BodyBakingOptions instead"))`
- L564 _public member_ `TMap<FName, EMetaHumanBuildTextureResolution> FaceBakedTextureResolutions_DEPRECATED;` — `UE_DEPRECATED(5.7, "This property has no effect in the pipeline. Please use MaterialBakingOptions.FaceBakingOptions.TextureResolutionsOverrides")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use MaterialBakingOptions.FaceBakingOptions.TextureResolutionsOverrides instead"))`
- L568 _public member_ `TMap<FName, EMetaHumanBuildTextureResolution> BodyBakedTextureResolutions_DEPRECATED;` — `UE_DEPRECATED(5.7, "This property has no effect in the pipeline. Please use MaterialBakingOptions.BodyBakingOptions.TextureResolutionsOverrides")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use MaterialBakingOptions.BodyBakingOptions.TextureResolutionsOverrides instead"))`
- L572 _public member_ `FMetaHumanBuildTextureProperties MaxTextureResolutions;` — `UPROPERTY(EditAnywhere, Category = "Textures")` — Configure the maximum resolution for each of the source textures when building the character
- L576 _public member_ `FMetaHumanLODProperties LODProperties;` — `UPROPERTY(EditAnywhere, Category = "LODs")` — Configure the LODs of the character being built
- L579 _public member_ `FMetaHumanHairProperties HairProperties;` — `UPROPERTY(EditAnywhere, Category = "Hair")`
- L582 _public member_ `FMetaHumanCostumeProperties CostumeProperties;` — `UPROPERTY(EditAnywhere, Category = "Costume")`
- L585 _public member_ `FMetaHumanBodyProperties BodyProperties;` — `UPROPERTY(EditAnywhere, Category = "Body", meta=(PipelineDisplay = "Advanced"))`
- L588 _private prototype_ `bool TryUnpackObject(UObject* Object, const UObject* UnpackingAsset, FString& InOutAssetPath, TSet<FString>& OutUnpackedAssetPaths) const;`
- L589 _private prototype_ `bool TryMoveObjectToAssetPackage(UObject* Object, FStringView NewAssetPath) const;`
- L591 _private prototype_ `static void ReplaceReferencesInAssemblyOutput(FInstancedStruct& AssemblyOutput, TNotNull<const UObject*> OriginalObject, TNotNull<UObject*> ReplacementObject);`
- L605 _private prototype_ `bool TryBakeMaterials( const FString& BaseOutputFolder, const FMetaHumanMaterialBakingOptions& InMaterialBakingOptions, TArray<FSkeletalMaterial>& InOutSkelMeshMaterials, const TMap<FName, TObjectPtr<UMaterialInterface>>& RemovedMaterialSlots, const TArray<int32>& MaterialChangesPerLOD, TNotNull<UObject*> GeneratedAssetOuter, FMetaHumanCharacterGeneratedAssets& InOutGeneratedAssets, TArray<TObjectPtr<UTexture>>& OutGeneratedTextures, bool bCreateInstancesOfBakedMaterials = true) const;` — Bakes materials to textures with the provided settings. If bCreateInstancesOfBakedMaterials is true, the materials specified in FMetaHumanMaterialBakingOptions to be used with the baked textures will be instanced first, so that the original materials aren't modified. This setting should be used when the FMetaHumanMaterialBakingOptions come from an asset on disk. If bCreateInstancesOfBakedMaterials is false, the baked materials will be modified and used directly. This can be used when FMetaHumanMaterialBakingOptions has been generated procedurally and set up with baked materials for this purpose.
- L618 _private prototype_ `TArray<FName> GetScalableNormalsTypeOptions() const;` — `UFUNCTION()` — Get the list of available scalable normal type options
- L621 _private prototype_ `void ResolveDefaultScalableNormalsType();` — Ensures ScalableNormalsType is set to a valid key from settings. Assigns the first available option if None or invalid.
- L628 _protected prototype_ `UBlueprint* WriteActorBlueprintHelper( TSubclassOf<AActor> InBaseActorClass, const FString& InBlueprintPath, const TFunction<bool(UBlueprint*)> CanReuseBlueprintFunc, const TFunction<UBlueprint*(class UPackage*)> GenerateBlueprintFunc) const;` — Helper function for generating the blueprint actor asset. It will try to reuse the existing blueprint, but if it fails or there is no existing blueprint on the given path, it will generate a new one.
- L638 _protected prototype_ `static bool IsPluginAsset(TNotNull<UObject*> InObject);` — Returns true if the object is an asset of this plugin by checking if the package name root matches the name of plugin this class is
- L649 _protected prototype_ `virtual TNotNull<USkeleton*> GenerateSkeleton(FMetaHumanCharacterGeneratedAssets& InGeneratedAssets, TNotNull<USkeleton*> InBaseSkeleton, const FString& InTargetFolderName, TNotNull<UObject*> InOuterForGeneratedAssets) const;` — Generates a skeleton for unpacking. If @p InBaseSkeleton is a plugin asset, unpack it to target common folder, otherwise use it as is @param InGeneratedAssets list of generated assets where this skeleton will be added @param InBaseSkeleton the base skeleton to use. This will be either the Face or Body skeletons selected when configuring the pipeline @param InTargetFolderName the folder name to place the skeleton on @param InOuterForGeneratedAssets the outer to use if the base skeleton needs to be duplicated @return the skeleton to be set in the target skeletal mesh, either the Face or Body
- L659 _protected prototype_ `static void OptimizeBoneCount(USkeletalMesh* SkeletalMesh, int32 LODIndex = 0, const TArray<FName>& ForceKeepBones = {});` — Reduce bone count of a skeletal mesh by removing bones that are not used by skin weights, while preserving manually specified bones to keep. @param SkeletalMesh The skeletal mesh asset to optimize. @param ExtraBonesToKeep Additional bones that must be preserved.
- L662 _protected member_ `TObjectPtr<UMetaHumanCharacterEditorPipelineSpecification> Specification;` — `UPROPERTY(Transient)`
- L665 _protected member_ `TScriptInterface<class IMetaHumanValidationContext> ValidationContext;` — `UPROPERTY(Transient)`
- L672 _private prototype_ `void RemoveLODsIfNeeded(FMetaHumanCharacterGeneratedAssets& InGeneratedAssets, TMap<FName, TObjectPtr<UMaterialInterface>>& OutRemovedMaterialSlots) const;` — Remove LODs if specified by the pipeline
- L674 _private prototype_ `[[nodiscard]] bool ProcessGroomAndClothSlots( TNotNull<const UMetaHumanCollection*> CharacterCollection, FMetaHumanCollectionBuiltData& BuiltData, TConstArrayView<FMetaHumanPinnedSlotSelection> SortedPinnedSlotSelections, TConstArrayView<FMetaHumanPaletteItemPath> SortedItemsToExclude, EMetaHumanCharacterPaletteBuildQuality Quality, TNotNull<UObject*> OuterForGeneratedAssets, const FString& TextureOutputFolder, TMap<FMetaHumanPaletteItemKey, struct FCharacterPipelineData>& CharacterPipelineData) const;`
- L684 _private prototype_ `bool ProcessBakedMaterials( const FString& TextureOutputFolder, FMetaHumanCollectionBuiltData& BuiltData, FMetaHumanCharacterGeneratedAssets& GeneratedAssets, TNotNull<UObject*> OuterForGeneratedAssets, FCharacterPipelineData& PipelineData) const;`
- L691 _private prototype_ `bool CanResizeOutfits() const;`
- L693 _private prototype_ `bool ConfirmUpdateCommonAssetsForBP(TNotNull<const UObject*> InGeneratedBP, const FString& InAssetPath) const;`

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultEditorPipeline/Public/MetaHumanDefaultEditorPipelineLegacy.h` (Public)


#### class `UMetaHumanDefaultEditorPipelineLegacy`  
`class UMetaHumanDefaultEditorPipelineLegacy : public UMetaHumanDefaultEditorPipelineBase`  
_L13-36_
- reflection: `UCLASS(EditInlineNew)`
- inherits: `UMetaHumanDefaultEditorPipelineBase`
- desc: Editor pipeline for UMetaHumanDefaultPipelineLegacy
- L20 _public member_ `TSubclassOf<AActor> TemplateClass;` — `UPROPERTY(EditAnywhere, Category = "Character")` — Blueprint actor class to duplicate when creating a new blueprint
- L22 _public prototype_ `virtual UBlueprint* WriteActorBlueprint(const FWriteBlueprintSettings& InWriteBlueprintSettings) const override;`
- L23 _public prototype_ `virtual bool UpdateActorBlueprint(const UMetaHumanInstance* InCharacterInstance, UBlueprint* InBlueprint) const override;`
- L35 _protected prototype_ `static void OptimizeBoneCounts(UBlueprint* InBlueprint, AActor* ActorCDO);` — Optimize bone counts for all skeletal mesh components except for the Body in the given Blueprint, by removing unskinned bones from their skeletal meshes for all LODs. Intended to be called in late assembly after all skeletal meshes have been assigned to their components. @param InBlueprint The Blueprint being modified. @param ActorCDO The generated class default object used to gather subobjects.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultEditorPipeline/Public/MetaHumanDefaultEditorPipelineUEFN.h` (Public)


#### class `UMetaHumanDefaultEditorPipelineUEFN`  
`class UMetaHumanDefaultEditorPipelineUEFN : public UMetaHumanDefaultEditorPipelineLegacy`  
_L10-66_
- reflection: `UCLASS()`
- inherits: `UMetaHumanDefaultEditorPipelineLegacy`
- L16 _public prototype_ `UMetaHumanDefaultEditorPipelineUEFN();`
- L19 _public prototype_ `virtual bool BeginCharacterEditorAssemble(TNotNull<class UMetaHumanCollection*> InCollection, const FString& InCharacterName) override;`
- L20 _public prototype_ `virtual void EndCharacterEditorAssemble(TNotNull<class UMetaHumanCollection*> InCollection) override;`
- L22 _public prototype_ `virtual UBlueprint* WriteActorBlueprint(const FWriteBlueprintSettings& InWriteBlueprintSettings) const override;`
- L23 _public prototype_ `virtual bool UpdateActorBlueprint(const UMetaHumanInstance* InCharacterInstance, UBlueprint* InBlueprint) const override;`
- L30 _public member_ `FFilePath UefnProjectFilePath;` — `UPROPERTY(EditAnywhere, DisplayName = "UEFN Project", Category = "Targets", meta = (PipelineDisplay = "Targets"))` — File path to the UEFN project where the assembled MetaHuman assets will be exported
- L34 _public member_ `int32 BodyLODThreshold = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Scalability")` — Max LOD level to evaluate body correctives to be set in the MetaHuman Component for UEFN
- L37 _public prototype_ `static void ResizeTexture(TNotNull<UTexture2D*> InTexture);` — Helper functions
- L38 _public prototype_ `static TArray<UMaterialExpression*> ReconnectPathTracingQualitySwitches(TNotNull<UObject*> InMaterialOrMaterialFunction);`
- L39 _public prototype_ `static void RemovePathTracingQualitySwitches(TNotNull<UObject*> InMaterialOrMaterialFunction);`
- L40 _public prototype_ `static void RemoveAssetGuidelines(TNotNull<UObject*> InObject);`
- L41 _public prototype_ `static void SaveObjectForUEFNProject(TNotNull<UObject*> TargetObject);`
- L42 _public prototype_ `static void RemoveAllGraphsFromBlueprint(UBlueprint* Blueprint);`
- L47 _protected prototype_ `virtual TNotNull<USkeleton*> GenerateSkeleton(FMetaHumanCharacterGeneratedAssets& InGeneratedAssets, TNotNull<USkeleton*> InBaseSkeleton, const FString& InTargetFolderName, TNotNull<UObject*> InOuterForGeneratedAssets) const override;`
- L59 _private prototype_ `void UnpackCommonDependencies(TArray<UObject*> InRootObjects, TNotNull<const class UMetaHumanCollection*> InCollection, TMap<UObject*, UObject*>& OutDuplicatedRootObjects) const;` — Gather dependencies of the generated assets so they can be unpacked in the target folder of the pipeline. Dependencies are added as metadata in InGeneratedAssets to be unpacked later
- L61 _private prototype_ `void OnCommonDependenciesUnpacked(const TMap<UObject*, UObject*>& InDuplicatedDependencies) const;`
- L63 _private member_ `TSharedPtr<class IPlugin> UEFNPlugin;`
- L65 _private member_ `FString MountingPoint;`
