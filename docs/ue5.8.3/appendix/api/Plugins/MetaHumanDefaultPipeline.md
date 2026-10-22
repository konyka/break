# Plugins / MetaHumanDefaultPipeline

- module root: `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultPipeline`
- headers: 11; symbols: 231
- symbol kinds: class=12, delegate=1, enum=3, enumerator=17, function=4, macro=2, member=110, namespace=3, prototype=65, struct=12, typedef=2
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: ChaosClothAssetEngine, ChaosOutfitAssetEngine, Core, CoreUObject, Engine, HairStrandsCore, MetaHumanCharacter, MetaHumanCharacterPalette

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultPipeline/Private/MetaHumanDefaultPipelineLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanDefaultPipeline, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanDefaultPipeline, Log, All);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultPipeline/Public/Item/MetaHumanDefaultGroomPipeline.h` (Public)


#### class `UMetaHumanDefaultGroomPipelineMaterialParameters`  
`class UMetaHumanDefaultGroomPipelineMaterialParameters : public UObject`  
_L21-97_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Class defining the MetaHuman groom standard - it lists all the available parameters and maps them against the material parameter name. This class is not meant to be instantiated, it's only for storing properties and metadata.
- L27 _public member_ `float Melanin = 0.16f;` — `UPROPERTY(meta = (MaterialParamName = "hairMelanin", GroomCategory = "Default", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f, ColorPickerID = "Hair Color", ColorPickerChannel = "U", ColorPickerTexture = "/MetaHumanCharacter/Tools/T_HairColorImage"))`
- L30 _public member_ `float Redness = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "hairRedness", GroomCategory = "Default", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f, ColorPickerID = "Hair Color", ColorPickerChannel = "V", ColorPickerTexture = "/MetaHumanCharacter/Tools/T_HairColorImage"))`
- L33 _public member_ `float Roughness = 0.25f;` — `UPROPERTY(meta = (MaterialParamName = "HairRoughness", GroomCategory = "Default", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f))`
- L36 _public member_ `float Whiteness = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "WhiteAmount", GroomCategory = "Default", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f))`
- L39 _public member_ `float Lightness = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "LightAmount", GroomCategory = "Default", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f))`
- L42 _public member_ `FLinearColor DyeColor;` — `UPROPERTY(meta = (MaterialParamName = "HairDye", GroomCategory = "Default"))`
- L45 _public member_ `bool bUseOmbre = false;` — `UPROPERTY(meta = (MaterialParamName = "Ombre", GroomCategory = "Ombre"))`
- L48 _public member_ `float OmbreU = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "OmbreMelanin", GroomCategory = "Ombre", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f, ColorPickerID = "Ombre", ColorPickerChannel = "U", ColorPickerTexture = "/MetaHumanCharacter/Tools/T_HairColorImage"))`
- L51 _public member_ `float OmbreV = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "OmbreRedness", GroomCategory = "Ombre", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f, ColorPickerID = "Ombre", ColorPickerChannel = "V", ColorPickerTexture = "/MetaHumanCharacter/Tools/T_HairColorImage"))`
- L54 _public member_ `FLinearColor OmbreColor = FLinearColor::White;` — `UPROPERTY(meta = (MaterialParamName = "OmbreHairDye", GroomCategory = "Ombre"))`
- L57 _public member_ `float OmbreShift = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "OmbreShift", GroomCategory = "Ombre", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f))`
- L60 _public member_ `float OmbreContrast = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "OmbreContrast", GroomCategory = "Ombre", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f))`
- L63 _public member_ `float OmbreIntensity = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "OmbreIntensity", GroomCategory = "Ombre", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f))`
- L66 _public member_ `bool bUseRegions = false;` — `UPROPERTY(meta = (MaterialParamName = "Region", GroomCategory = "Regions"))`
- L69 _public member_ `float RegionsU = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "RegionMelanin", GroomCategory = "Regions", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f))`
- L72 _public member_ `float RegionsV = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "RegionRedness", GroomCategory = "Regions", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f))`
- L75 _public member_ `FLinearColor RegionsColor = FLinearColor::White;` — `UPROPERTY(meta = (MaterialParamName = "RegionhairDye", GroomCategory = "Regions"))`
- L78 _public member_ `bool bUseHighlights = false;` — `UPROPERTY(meta = (MaterialParamName = "Highlights", GroomCategory = "Highlights"))`
- L81 _public member_ `float HighlightsU = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "HighlightsMelanin", GroomCategory = "Highlights", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f, ColorPickerID = "Highlights", ColorPickerChannel = "U", ColorPickerTexture = "/MetaHumanCharacter/Tools/T_HairColorImage"))`
- L84 _public member_ `float HighlightsV = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "HighlightsRedness", GroomCategory = "Highlights", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f, ColorPickerID = "Highlights", ColorPickerChannel = "V", ColorPickerTexture = "/MetaHumanCharacter/Tools/T_HairColorImage"))`
- L87 _public member_ `FLinearColor HighlightsColor = FLinearColor::White;` — `UPROPERTY(meta = (MaterialParamName = "HighlightsHairDye", GroomCategory = "Highlights"))`
- L90 _public member_ `float HighlightsBlending = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "HighlightsBlending", GroomCategory = "Highlights", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f))`
- L93 _public member_ `float HighlightsIntensity = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "HighlightsIntensity", GroomCategory = "Highlights", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f))`
- L96 _public member_ `float HighlightsVariation = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "HighlightsVariationNumber", GroomCategory = "Highlights", Min = 0.0f, UIMin = 0.0f, Max = 3.0f, UIMax = 3.0f))`

#### enum `EHairLODTransition`  
`enum class EHairLODTransition : uint8`  
_L100-107_
- reflection: `UENUM()`
- L102 _public enumerator_ `StrandsToCardsToMesh UMETA(DisplayName = "Strands->Cards->Mesh")`
- L103 _public enumerator_ `StrandsToCardsToTexture UMETA(DisplayName = "Strands->Cards->Texture")`
- L104 _public enumerator_ `StrandsToCardsAndTextureToTexture UMETA(DisplayName = "Strands->Cards & Texture->Texture")`
- L105 _public enumerator_ `StrandsToCardsAndTextureToMeshToTexture UMETA(DisplayName = "Strands->Cards & Texture->Mesh & Texture")`
- L106 _public enumerator_ `StrandsToTexture UMETA(DisplayName = "Strands->Texture")`

#### class `UMetaHumanDefaultGroomPipeline`  
`class UMetaHumanDefaultGroomPipeline : public UMetaHumanGroomPipeline`  
_L113-191_
- reflection: `UCLASS(Blueprintable, EditInlineNew)`
- inherits: `UMetaHumanGroomPipeline`
- desc: Groom pipeline used for compatibility with the original MetaHumanCreator.
- L118 _public prototype_ `UMetaHumanDefaultGroomPipeline();`
- L122 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L127 _public member_ `EMetaHumanRuntimeMaterialParameterSlotTarget SlotTarget = EMetaHumanRuntimeMaterialParameterSlotTarget::SlotNames;` — `UPROPERTY(EditAnywhere, Category = "Support")`
- L130 _public member_ `TArray<FName> SlotNames;` — `UPROPERTY(EditAnywhere, Category = "Support", meta = (EditCondition = "SlotTarget == EMetaHumanRuntimeMaterialParameterSlotTarget::SlotNames"))`
- L133 _public member_ `TArray<int32> SlotIndices;` — `UPROPERTY(EditAnywhere, Category = "Support", meta = (EditCondition = "SlotTarget == EMetaHumanRuntimeMaterialParameterSlotTarget::SlotIndices"))`
- L136 _public member_ `bool bSupportsOmbre = true;` — `UPROPERTY(EditAnywhere, Category = "Support")`
- L139 _public member_ `bool bSupportsRegions = true;` — `UPROPERTY(EditAnywhere, Category = "Support")`
- L142 _public member_ `bool bSupportsHightlights = true;` — `UPROPERTY(EditAnywhere, Category = "Support")`
- L145 _public member_ `float HighlightsRootDistance = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Groom")`
- L148 _public member_ `TSoftObjectPtr<UTexture> HighlightsMask;` — `UPROPERTY(EditAnywhere, Category = "Groom")`
- L152 _public member_ `TSoftObjectPtr<UTexture> BakedGroomTexture;` — `UPROPERTY(EditAnywhere, Category = "Groom")` — The texture that will be used to bake the groom onto the face material at worse LODs
- L156 _public member_ `EHairLODTransition LODTransition;` — `UPROPERTY(EditAnywhere, Category = "Groom")` — The LOD strategy for this groom
- L160 _public member_ `int32 GroomTextureMinLOD = 5;` — `UPROPERTY(EditAnywhere, Category = "Groom")` — The best LOD (lowest index) that this groom will be baked onto the face
- L163 _public prototype_ `void SetFaceMaterialParameters( const TArray<UMaterialInstance*>& FaceMaterials, const TArray<int32>& LODToMaterial, FName SlotName, const FInstancedPropertyBag& InstanceParameters, bool bIsProduction, bool bHideHair, bool bForceCards, int32& OutFirstLODBaked) const;`
- L173 _public prototype_ `virtual void SetPostAssemblyParameters(const FSetPostAssemblyParametersParams& Params, FInstancedStruct& InOutItemAssemblyOutput) const override;`
- L177 _protected prototype_ `virtual void OverrideInitialMaterialValues(TNotNull<UMaterialInstanceDynamic*> InMID, FName InSlotName) const override;`
- L181 _private prototype_ `void SetFaceMaterialParametersForLOD( UMaterialInstance* FaceMaterial, FName SlotName, const FInstancedPropertyBag& InstanceParameters, UTexture* Texture) const;`
- L187 _private prototype_ `void AddRuntimeParameter(TNotNull<FProperty*> InProperty, const FName& InMaterialParameterName);`
- L190 _private prototype_ `void UpdateParameters();`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultPipeline/Public/Item/MetaHumanDefaultSkeletalMeshPipeline.h` (Public)


#### class `UMetaHumanDefaultSkeletalMeshPipelineMaterialParameters`  
`class UMetaHumanDefaultSkeletalMeshPipelineMaterialParameters : public UObject`  
_L16-27_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Class defining the MetaHuman skeletal mesh standard - it lists all the available parameters and maps them against the material parameter name.
- L22 _public member_ `FLinearColor Color1;` — `UPROPERTY(meta = (MaterialParamName = "diffuse_color_1", SkelMeshCategory = "Default"))`
- L25 _public member_ `FLinearColor Color2;` — `UPROPERTY(meta = (MaterialParamName = "diffuse_color_2", SkelMeshCategory = "Default"))`

#### class `UMetaHumanDefaultSkeletalMeshPipeline`  
`class UMetaHumanDefaultSkeletalMeshPipeline : public UMetaHumanSkeletalMeshPipeline`  
_L33-61_
- reflection: `UCLASS(Blueprintable, EditInlineNew)`
- inherits: `UMetaHumanSkeletalMeshPipeline`
- desc: Skeletal Mesh pipeline used for compatibility with the original MetaHumanCreator.
- L38 _public prototype_ `UMetaHumanDefaultSkeletalMeshPipeline();`
- L42 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L47 _public member_ `EMetaHumanRuntimeMaterialParameterSlotTarget SlotTarget = EMetaHumanRuntimeMaterialParameterSlotTarget::SlotNames;` — `UPROPERTY(EditAnywhere, Category = "Support")`
- L50 _public member_ `TArray<FName> SlotNames;` — `UPROPERTY(EditAnywhere, Category = "Support", meta = (EditCondition = "SlotTarget == EMetaHumanRuntimeMaterialParameterSlotTarget::SlotNames"))`
- L53 _public member_ `TArray<int32> SlotIndices;` — `UPROPERTY(EditAnywhere, Category = "Support", meta = (EditCondition = "SlotTarget == EMetaHumanRuntimeMaterialParameterSlotTarget::SlotIndices"))`
- L57 _private prototype_ `void AddRuntimeParameter(TNotNull<FProperty*> InProperty, const FName& InMaterialParameterName);`
- L60 _private prototype_ `void UpdateParameters();`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultPipeline/Public/Item/MetaHumanGroomPipeline.h` (Public)


#### struct `FMetaHumanGroomPipelineBuildOutput`  
`struct FMetaHumanGroomPipelineBuildOutput`  
_L20-30_
- reflection: `USTRUCT()`
- L26 _public member_ `TArray<TObjectPtr<UGroomBindingAsset>> Bindings;` — `UPROPERTY()`
- L29 _public member_ `bool bRequiresBinding = true;` — `UPROPERTY()`

#### struct `FMetaHumanGroomPipelineAssemblyInput`  
`struct FMetaHumanGroomPipelineAssemblyInput`  
_L33-40_
- reflection: `USTRUCT()`
- L39 _public member_ `TObjectPtr<const USkeletalMesh> TargetMesh;` — `UPROPERTY()`

#### struct `FMetaHumanGroomPipelineAssemblyOutput`  
`struct FMetaHumanGroomPipelineAssemblyOutput`  
_L43-58_
- reflection: `USTRUCT(BlueprintType)`
- L49 _public member_ `TObjectPtr<UGroomBindingAsset> Binding;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Groom")`
- L53 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Groom")` — Key is slot name
- L57 _public member_ `TMap<FName, TObjectPtr<UMaterialInstanceDynamic>> FaceMeshOverrideMaterials;` — `UPROPERTY()` — Key is slot name, face mesh skin MIDs for baked groom color param updates

#### class `UMetaHumanGroomPipeline`  
`class UMetaHumanGroomPipeline : public UMetaHumanItemPipeline`  
_L61-109_
- reflection: `UCLASS(Blueprintable, EditInlineNew)`
- inherits: `UMetaHumanItemPipeline`
- L66 _public prototype_ `UMetaHumanGroomPipeline();`
- L69 _public prototype_ `virtual void SetDefaultEditorPipeline() override;`
- L71 _public prototype_ `virtual const UMetaHumanItemEditorPipeline* GetEditorPipeline() const override;`
- L74 _public prototype_ `virtual void AssembleItem(const FAssembleItemParams& Params, const FOnAssemblyComplete& OnComplete) const override;`
- L76 _public prototype_ `virtual void SetPostAssemblyParameters(const FSetPostAssemblyParametersParams& Params, FInstancedStruct& InOutItemAssemblyOutput) const override;`
- L78 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterPipelineSpecification*> GetSpecification() const override;`
- L81 _public prototype_ `static void ApplyGroomAssemblyOutputToGroomComponent(const FMetaHumanGroomPipelineAssemblyOutput& GroomAssemblyOutput, UGroomComponent* GroomComponent);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Pipeline")`
- L84 _public prototype_ `static UE::MetaHuman::MaterialUtils::FFetchSlotNameDelegate MakeFetchSlotNameDelegate(TConstArrayView<FHairGroupsMaterial> HairMaterials);` — Internal functions to reduce implementation boilerplate
- L85 _public prototype_ `static UE::MetaHuman::MaterialUtils::FFetchSlotMaterialDelegate MakeFetchSlotMaterialDelegate(TConstArrayView<FHairGroupsMaterial> HairMaterials);`
- L88 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")`
- L91 _public member_ `TArray<FMetaHumanMaterialParameter> RuntimeMaterialParameters;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")`
- L95 _protected function_ `virtual void OverrideInitialMaterialValues(TNotNull<UMaterialInstanceDynamic*> InMID, FName InSlotName) const` — Allows pipeline to override default material values before they're initialized
- L99 _private prototype_ `TSubclassOf<UMetaHumanItemEditorPipeline> GetEditorPipelineClass() const;`
- L104 _private member_ `TObjectPtr<UMetaHumanItemEditorPipeline> EditorPipeline;` — `UPROPERTY(EditAnywhere, NoClear, Instanced, Category = "Pipeline", meta = (FullyExpand, AllowedClasses = "/Script/MetaHumanDefaultEditorPipeline.MetaHumanGroomEditorPipeline"))`
- L108 _private member_ `TObjectPtr<UMetaHumanCharacterPipelineSpecification> Specification;` — `UPROPERTY(Transient)`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultPipeline/Public/Item/MetaHumanMaterialPipelineCommon.h` (Public)


#### enum `EMetaHumanRuntimeMaterialParameterType`  
`enum class EMetaHumanRuntimeMaterialParameterType`  
_L20-31_
- reflection: `UENUM()`
- desc: Material parameters that can be changed at runtime A subset of EMaterialParameterType
- L22 _public enumerator_ `Toggle`
- L23 _public enumerator_ `Scalar`
- L24 _public enumerator_ `Vector`
- L25 _public enumerator_ `DoubleVector`
- L26 _public enumerator_ `Texture`
- L27 _public enumerator_ `TextureCollection`
- L28 _public enumerator_ `Font`
- L29 _public enumerator_ `RuntimeVirtualTexture`
- L30 _public enumerator_ `SparseVolumeTexture`

#### enum `EMetaHumanRuntimeMaterialParameterSlotTarget`  
`enum class EMetaHumanRuntimeMaterialParameterSlotTarget`  
_L37-45_
- reflection: `UENUM()`
- desc: Used to determine how to obtain material interface for the given parameter.
- L40 _public enumerator_ `SlotNames` — Apply to the material slots whose names are listed in SlotNames.
- L42 _public enumerator_ `SlotIndices` — Apply to the material slots whose indices are listed in SlotIndices.
- L44 _public enumerator_ `AllSlots` — Apply to every material slot managed by the pipeline. Slot names and indices are ignored.

#### struct `FMetaHumanMaterialParameter`  
`struct FMetaHumanMaterialParameter`  
_L52-77_
- reflection: `USTRUCT()`
- desc: Used to describe material parameter that we can modify on the material obtained from the slot name or index.
- L58 _public member_ `FName InstanceParameterName;` — `UPROPERTY(EditAnywhere, Category = "Material")`
- L61 _public member_ `EMetaHumanRuntimeMaterialParameterSlotTarget SlotTarget = EMetaHumanRuntimeMaterialParameterSlotTarget::SlotNames;` — `UPROPERTY(EditAnywhere, Category = "Material")`
- L64 _public member_ `TArray<FName> SlotNames;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (EditCondition = "SlotTarget == EMetaHumanRuntimeMaterialParameterSlotTarget::SlotNames"))`
- L67 _public member_ `TArray<int32> SlotIndices;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (EditCondition = "SlotTarget == EMetaHumanRuntimeMaterialParameterSlotTarget::SlotIndices"))`
- L70 _public member_ `FMaterialParameterInfo MaterialParameter;` — `UPROPERTY(EditAnywhere, Category = "Material")`
- L73 _public member_ `EMetaHumanRuntimeMaterialParameterType ParameterType = EMetaHumanRuntimeMaterialParameterType::Scalar;` — `UPROPERTY(EditAnywhere, Category = "Material")`
- L76 _public member_ `TMap<FName, FString> PropertyMetadata;` — `UPROPERTY(EditAnywhere, Category = "Material")`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METAHUMANDEFAULTPIPELINE_API`
- L84 _namespace_ `namespace UE`
- L84 _namespace_ `namespace MetaHuman` (scope `UE`)
- L84 _namespace_ `namespace MaterialUtils` (scope `UE::MetaHuman`)
- L92 _typedef_ `using FFetchSlotNameDelegate = TDelegate<FName(int32)>;` (scope `UE::MetaHuman::MaterialUtils`) — On an asset that has material slots, such as a mesh, return the name of the material slot that corresponds to the given slot index. Should handle invalid slot indices gracefully and return NAME_None.
- L95 _typedef_ `using FFetchSlotMaterialDelegate = TDelegate<const UMaterialInterface*(int32)>;` (scope `UE::MetaHuman::MaterialUtils`) — Similar to FFetchSlotNameDelegate, but returns the material assigned to the slot, if any.
- L97 _prototype_ `FFetchSlotNameDelegate MakeFetchSlotNameDelegate(TConstArrayView<FSkeletalMaterial> SkeletalMaterials);` (scope `UE::MetaHuman::MaterialUtils`)
- L98 _prototype_ `FFetchSlotMaterialDelegate MakeFetchSlotMaterialDelegate(TConstArrayView<FSkeletalMaterial> SkeletalMaterials);` (scope `UE::MetaHuman::MaterialUtils`)
- L99 _prototype_ `TMap<FName, TObjectPtr<UMaterialInstanceDynamic>> CastMaterialMapToDynamic(const TMap<FName, TObjectPtr<UMaterialInterface>>& MaterialMap);` (scope `UE::MetaHuman::MaterialUtils`)
- L103 _prototype_ `void GenerateAssemblyParameters( const TMap<FName, TObjectPtr<UMaterialInterface>>& OverrideMaterials, TConstArrayView<FMetaHumanMaterialParameter> RuntimeMaterialParameters, int32 NumMaterialSlots, const FFetchSlotNameDelegate& FetchSlotName, const FFetchSlotMaterialDelegate& FetchSlotMaterial, FInstancedPropertyBag& OutAssemblyParameters);` (scope `UE::MetaHuman::MaterialUtils`) — Generate Assembly Parameters for an item at build time
- L120 _prototype_ `UObject* CreateUniqueNamedObject( UObject* InOuter, FName& InOutGeneratedName, TFunctionRef<UObject*(FName)> InMakeObject);` (scope `UE::MetaHuman::MaterialUtils`) — Creates a UObject with a deterministic, unique name under InOuter. InOutGeneratedName is used as the initial name, and if the name is taken, it's permuted until a unique name is found. InMakeObject should be a function that makes the actual object.
- L130 _prototype_ `UMaterialInstanceDynamic* CreateUniqueNamedMaterialInstanceDynamic( TNotNull<const UMaterialInterface*> InParentMaterial, UObject* InOuter, FName& InOutGeneratedName);` (scope `UE::MetaHuman::MaterialUtils`) — Creates a UMaterialInstanceDynamic with a deterministic, unique name. @see CreateUniqueNamedObject
- L140 _prototype_ `void ProcessAssemblyParameters( const TMap<FName, TObjectPtr<UMaterialInterface>>& SourceOverrideMaterials, TConstArrayView<FMetaHumanMaterialParameter> RuntimeMaterialParameters, const FString& ItemFriendlyName, const FString& PreferredSubfolderPathForGeneratedAssets, int32 NumMaterialSlots, const FFetchSlotNameDelegate& FetchSlotName, const FFetchSlotMaterialDelegate& FetchSlotMaterial, UObject* OuterForGeneratedObjects, TMap<FName, TObjectPtr<UMaterialInterface>>& OutOverrideMaterials, FInstancedPropertyBag& OutPostAssemblyParameters, TArray<FMetaHumanGeneratedAssetMetadata>& OutMetadata);` (scope `UE::MetaHuman::MaterialUtils`) — At assembly time, set any Assembly Parameters generated by GenerateAssemblyParameters and generate Post-Assembly Parameters, including generating dynamic Material Instances for the materials.
- L161 _prototype_ `void SetInstanceParameters( const TArray<FMetaHumanMaterialParameter>& InMaterialParameters, const TMap<FName, TObjectPtr<class UMaterialInstanceDynamic>>& InMaterialInstanceMapping, const FFetchSlotNameDelegate& InFetchSlotName, const FInstancedPropertyBag& InPropertyBag);` (scope `UE::MetaHuman::MaterialUtils`) — Updates materials from the given material parameters. @param InMaterialParameters Parameters that will be applied onto the material (doesn't contain the actual data) @param InMaterialInstanceMapping Materials to updated @param InFetchSlotName Returns the name of the material slot for a given slot index @param InPropertyBag Values for the material parameters.
- L168 _prototype_ `void SetInstanceParameters( const TArray<FMetaHumanMaterialParameter>& InMaterialParameters, const TMap<FName, TObjectPtr<UMaterialInstanceDynamic>>& InMaterialInstanceMapping, const TArray<FName>& InAvailableSlots, const struct FInstancedPropertyBag& InPropertyBag);` (scope `UE::MetaHuman::MaterialUtils`) — `UE_DEPRECATED(5.8, "Use the SetInstanceParameters overload that takes a delegate instead of InAvailableSlots")`
- L182 _prototype_ `bool ParametersToPropertyBag( TNotNull<const UMaterialInterface*> InMaterial, const TArray<FMetaHumanMaterialParameter>& InMaterialParameters, FInstancedPropertyBag& InOutPropertyBag);` (scope `UE::MetaHuman::MaterialUtils`) — Outputs the property bag with parameters that are present on the given material. @param InMaterial Material to get values from @param InMaterialParameters Parameters to look for @param InOutPropertyBag Output result containing property name and the material parameter value @return true if any of the parameters were adeded or already in the bag.
- L190 _prototype_ `EMetaHumanRuntimeMaterialParameterType PropertyToParameterType(TNotNull<FProperty*> InProperty);` (scope `UE::MetaHuman::MaterialUtils`) — Converts the given property name to the parameter type.
- L196 _prototype_ `TMap<FName, FString> CopyMetadataFromProperty(TNotNull<FProperty*> InProperty);` (scope `UE::MetaHuman::MaterialUtils`) — Reads metadata from the given property.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultPipeline/Public/Item/MetaHumanOutfitPipeline.h` (Public)


#### struct `FMetaHumanOutfitGeneratedAssets`  
`struct FMetaHumanOutfitGeneratedAssets`  
_L18-45_
- reflection: `USTRUCT()`
- L24 _public member_ `TObjectPtr<UChaosOutfitAsset> Outfit;` — `UPROPERTY()`
- L27 _public member_ `TObjectPtr<USkeletalMesh> OutfitMesh;` — `UPROPERTY()`
- L30 _public member_ `TObjectPtr<USkeletalMesh> CombinedBodyMesh;` — `UPROPERTY()`
- L33 _public member_ `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture HeadHiddenFaceMap;` — `UPROPERTY()`
- L36 _public member_ `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture BodyHiddenFaceMap;` — `UPROPERTY()`
- L40 _public member_ `TArray<FName> AvailableSourceSizes;` — `UPROPERTY()` — The source sizes of the outfit that were available
- L44 _public member_ `FName AutoSelectedSourceSize;` — `UPROPERTY()` — The source size of the outfit that was auto-selected by the resizing graph

#### struct `FMetaHumanOutfitPipelineBuildOutput`  
`struct FMetaHumanOutfitPipelineBuildOutput`  
_L48-60_
- reflection: `USTRUCT()`
- L59 _public member_ `TMap<FMetaHumanPaletteItemKey, FMetaHumanOutfitGeneratedAssets> CharacterAssets;` — `UPROPERTY()` — Map from Character item key to the fitted outfit for that Character. If the outfit can't be fitted, this will just be a reference to the original outfit asset.

#### struct `FMetaHumanOutfitPipelineAssemblyInput`  
`struct FMetaHumanOutfitPipelineAssemblyInput`  
_L63-71_
- reflection: `USTRUCT()`
- L70 _public member_ `FMetaHumanPaletteItemKey SelectedCharacter;` — `UPROPERTY()`

#### struct `FMetaHumanOutfitPipelineAssemblyOutput`  
`struct FMetaHumanOutfitPipelineAssemblyOutput`  
_L74-93_
- reflection: `USTRUCT(BlueprintType)`
- L80 _public member_ `TObjectPtr<UChaosOutfitAsset> Outfit;` — `UPROPERTY()`
- L83 _public member_ `TObjectPtr<USkeletalMesh> OutfitMesh;` — `UPROPERTY()`
- L86 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY()`
- L89 _public member_ `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture HeadHiddenFaceMap;` — `UPROPERTY()`
- L92 _public member_ `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture BodyHiddenFaceMap;` — `UPROPERTY()`

#### class `UMetaHumanOutfitPipeline`  
`class UMetaHumanOutfitPipeline : public UMetaHumanItemPipeline`  
_L96-139_
- reflection: `UCLASS(Blueprintable, EditInlineNew)`
- inherits: `UMetaHumanItemPipeline`
- L101 _public prototype_ `UMetaHumanOutfitPipeline();`
- L104 _public prototype_ `virtual void SetDefaultEditorPipeline() override;`
- L106 _public prototype_ `virtual const UMetaHumanItemEditorPipeline* GetEditorPipeline() const override;`
- L109 _public prototype_ `virtual void AssembleItem(const FAssembleItemParams& Params, const FOnAssemblyComplete& OnComplete) const override;`
- L111 _public prototype_ `virtual void SetPostAssemblyParameters(const FSetPostAssemblyParametersParams& Params, FInstancedStruct& InOutItemAssemblyOutput) const override;`
- L113 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterPipelineSpecification*> GetSpecification() const override;`
- L116 _public prototype_ `static void ApplyOutfitAssemblyOutputToClothComponent(const FMetaHumanOutfitPipelineAssemblyOutput& InOutfitAssemblyOutput, UChaosClothComponent* InClothComponent);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Pipeline")`
- L119 _public prototype_ `static void ApplyOutfitAssemblyOutputToMeshComponent(const FMetaHumanOutfitPipelineAssemblyOutput& InOutfitAssemblyOutput, USkeletalMeshComponent* InMeshComponent, bool bUpdateSkelMesh = false);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Pipeline")`
- L122 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")`
- L125 _public member_ `TArray<FMetaHumanMaterialParameter> RuntimeMaterialParameters;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")`
- L129 _private prototype_ `TSubclassOf<UMetaHumanItemEditorPipeline> GetEditorPipelineClass() const;`
- L134 _private member_ `TObjectPtr<UMetaHumanItemEditorPipeline> EditorPipeline;` — `UPROPERTY(EditAnywhere, NoClear, Instanced, Category = "Pipeline", meta = (FullyExpand, AllowedClasses = "/Script/MetaHumanDefaultEditorPipeline.MetaHumanOutfitEditorPipeline"))`
- L138 _private member_ `TObjectPtr<UMetaHumanCharacterPipelineSpecification> Specification;` — `UPROPERTY(Transient)`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultPipeline/Public/Item/MetaHumanSkeletalMeshPipeline.h` (Public)


#### struct `FMetaHumanSkeletalMeshPipelineBuildOutput`  
`struct FMetaHumanSkeletalMeshPipelineBuildOutput`  
_L19-32_
- reflection: `USTRUCT()`
- L25 _public member_ `TObjectPtr<USkeletalMesh> Mesh;` — `UPROPERTY()`
- L28 _public member_ `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture HeadHiddenFaceMap;` — `UPROPERTY()`
- L31 _public member_ `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture BodyHiddenFaceMap;` — `UPROPERTY()`

#### struct `FMetaHumanSkeletalMeshPipelineAssemblyOutput`  
`struct FMetaHumanSkeletalMeshPipelineAssemblyOutput`  
_L35-54_
- reflection: `USTRUCT(BlueprintType)`
- L41 _public member_ `TObjectPtr<USkeletalMesh> SkelMesh;` — `UPROPERTY()`
- L44 _public member_ `TSoftObjectPtr<UAnimBlueprint> AnimBlueprintToUse;` — `UPROPERTY()`
- L47 _public member_ `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture HeadHiddenFaceMap;` — `UPROPERTY()`
- L50 _public member_ `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture BodyHiddenFaceMap;` — `UPROPERTY()`
- L53 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY()`

#### class `UMetaHumanSkeletalMeshPipeline`  
`class UMetaHumanSkeletalMeshPipeline : public UMetaHumanItemPipeline`  
_L57-103_
- reflection: `UCLASS(Blueprintable, EditInlineNew)`
- inherits: `UMetaHumanItemPipeline`
- L62 _public prototype_ `UMetaHumanSkeletalMeshPipeline();`
- L65 _public prototype_ `virtual void SetDefaultEditorPipeline() override;`
- L67 _public prototype_ `virtual const UMetaHumanItemEditorPipeline* GetEditorPipeline() const override;`
- L70 _public prototype_ `virtual void AssembleItem(const FAssembleItemParams& Params, const FOnAssemblyComplete& OnComplete) const override;`
- L72 _public prototype_ `virtual void SetPostAssemblyParameters(const FSetPostAssemblyParametersParams& Params, FInstancedStruct& InOutItemAssemblyOutput) const override;`
- L74 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterPipelineSpecification*> GetSpecification() const override;`
- L77 _public prototype_ `static void ApplySkeletalMeshAssemblyOutputToSkeletalMeshComponent( const FMetaHumanSkeletalMeshPipelineAssemblyOutput& InAssemblyOutput, USkeletalMeshComponent* InComponent, USkeletalMeshComponent* InLeaderComponent);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Pipeline")`
- L83 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")`
- L86 _public member_ `TArray<FMetaHumanMaterialParameter> RuntimeMaterialParameters;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")`
- L89 _public member_ `TSoftObjectPtr<UAnimBlueprint> AnimBlueprintToUse;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")`
- L93 _private prototype_ `TSubclassOf<UMetaHumanItemEditorPipeline> GetEditorPipelineClass() const;`
- L98 _private member_ `TObjectPtr<UMetaHumanItemEditorPipeline> EditorPipeline;` — `UPROPERTY(EditAnywhere, NoClear, Instanced, Category = "Pipeline", meta = (FullyExpand, AllowedClasses = "/Script/MetaHumanDefaultEditorPipeline.MetaHumanSkeletalMeshEditorPipeline"))`
- L102 _private member_ `TObjectPtr<UMetaHumanCharacterPipelineSpecification> Specification;` — `UPROPERTY(Transient)`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultPipeline/Public/MetaHumanDefaultPipeline.h` (Public)


#### class `UMetaHumanDefaultPipeline`  
`class UMetaHumanDefaultPipeline : public UMetaHumanDefaultPipelineBase`  
_L20-41_
- reflection: `UCLASS(Abstract, Blueprintable, EditInlineNew)`
- inherits: `UMetaHumanDefaultPipelineBase`
- desc: The default pipeline for building MetaHumans. This pipeline should cover the needs of most users who are making simple MetaHumans. Note that this class is itself abstract. A Blueprint subclass should be used to reference the content this pipeline depends on.
- L26 _public prototype_ `virtual void SetDefaultEditorPipeline() override;`
- L27 _public prototype_ `virtual const UMetaHumanCollectionEditorPipeline* GetEditorPipeline() const override;`
- L28 _public prototype_ `virtual UMetaHumanCollectionEditorPipeline* GetMutableEditorPipeline() override;`
- L31 _public prototype_ `virtual TSubclassOf<AActor> GetActorClass() const override;`
- L36 _private member_ `TObjectPtr<UMetaHumanCollectionEditorPipeline> EditorPipeline;` — `UPROPERTY(EditAnywhere, NoClear, Instanced, Category = "Character", meta = (FullyExpand, AllowedClasses = "/Script/MetaHumanDefaultEditorPipeline.MetaHumanDefaultEditorPipeline"))`
- L40 _private member_ `TSubclassOf<AActor> ActorClass;` — `UPROPERTY(EditAnywhere, Category = "Character", meta = (MustImplement = "/Script/MetaHumanCharacterPalette.MetaHumanCharacterActorInterface"))`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultPipeline/Public/MetaHumanDefaultPipelineBase.h` (Public)


#### struct `FMetaHumanCharacterPartOutput`  
`struct FMetaHumanCharacterPartOutput`  
_L27-34_
- reflection: `USTRUCT()`
- L33 _public member_ `FMetaHumanCharacterGeneratedAssets GeneratedAssets;` — `UPROPERTY()`

#### struct `FMetaHumanDefaultAssemblyOutput`  
`struct FMetaHumanDefaultAssemblyOutput`  
_L37-71_
- reflection: `USTRUCT(BlueprintType)`
- L43 _public member_ `TObjectPtr<class USkeletalMesh> FaceMesh;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`
- L46 _public member_ `TObjectPtr<class USkeletalMesh> BodyMesh;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`
- L49 _public member_ `FMetaHumanGroomPipelineAssemblyOutput Hair;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`
- L52 _public member_ `FMetaHumanGroomPipelineAssemblyOutput Eyebrows;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`
- L55 _public member_ `FMetaHumanGroomPipelineAssemblyOutput Beard;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`
- L58 _public member_ `FMetaHumanGroomPipelineAssemblyOutput Mustache;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`
- L61 _public member_ `FMetaHumanGroomPipelineAssemblyOutput Eyelashes;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`
- L64 _public member_ `FMetaHumanGroomPipelineAssemblyOutput Peachfuzz;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`
- L67 _public member_ `TArray<FMetaHumanSkeletalMeshPipelineAssemblyOutput> SkeletalMeshData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`
- L70 _public member_ `TArray<FMetaHumanOutfitPipelineAssemblyOutput> ClothData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`

#### class `UMetaHumanDefaultPipelineBase`  
`class UMetaHumanDefaultPipelineBase : public UMetaHumanCollectionPipeline`  
_L79-108_
- reflection: `UCLASS(Abstract, MinimalAPI, meta=(MetaHumanCreatorOnly))`
- inherits: `UMetaHumanCollectionPipeline`
- desc: The common base class for the current and legacy default MetaHuman pipelines. Contains shared functionality for building simple MetaHumans.
- L84 _public prototype_ `UMetaHumanDefaultPipelineBase();`
- L86 _public prototype_ `virtual void AssembleCollection(const FAssembleCollectionParams& Params, const FOnAssemblyComplete& OnComplete) const override;`
- L88 _public function_ `virtual TNotNull<const UMetaHumanCharacterPipelineSpecification*> GetSpecification() const override`
- L93 _public prototype_ `virtual const UMetaHumanItemPipeline* GetFallbackItemPipelineForAssetType(const TSoftClassPtr<UObject>& InAssetClass) const override;`
- L95 _public member_ `static const FName OutfitsSlotName;`
- L96 _public member_ `static const FName TopGarmentSlotName;`
- L97 _public member_ `static const FName BottomGarmentSlotName;`
- L98 _public member_ `static const FName SkeletalMeshSlotName;`
- L103 _private member_ `TObjectPtr<UMetaHumanCharacterPipelineSpecification> Specification;` — `UPROPERTY(Transient)` — The specification that this pipeline implements
- L107 _private member_ `TMap<TSoftClassPtr<UObject>, TSubclassOf<UMetaHumanItemPipeline>> DefaultAssetPipelines;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")` — Default item pipeline per asset type. Used if wardrobe item doesn't have a pipeline specified

#### class `IMetaHumanCharacterPipelineExtender`  
`class IMetaHumanCharacterPipelineExtender : public IModularFeature`  
_L115-125_
- inherits: `IModularFeature`
- desc: Pipeline functionality extender. Extenders can e.g. be registered from external plugins, modifying the blueprint after the base pipeline depending on if the plugin is enabled or not.
- L118 _public prototype_ `virtual ~IMetaHumanCharacterPipelineExtender() = default;`
- L119 _public member_ `static inline const FName FeatureName = TEXT("Met`
- L121 _public function_ `virtual TSubclassOf<AActor> GetOverwriteBlueprint(EMetaHumanQualityLevel QualityLevel, FName AnimationSystemName) const`
- L124 _public function_ `virtual void ModifyBlueprint(TNotNull<UBlueprint*> InBlueprint)` — Additional modifications called after the base pipeline blueprint modification.

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API METAHUMANDEFAULTPIPELINE_API`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultPipeline/Public/MetaHumanDefaultPipelineLegacy.h` (Public)


#### class `UMetaHumanDefaultPipelineLegacy`  
`class UMetaHumanDefaultPipelineLegacy : public UMetaHumanDefaultPipelineBase`  
_L20-37_
- reflection: `UCLASS(Abstract, Blueprintable, EditInlineNew)`
- inherits: `UMetaHumanDefaultPipelineBase`
- desc: Pipeline for building legacy actor-based MetaHumans. This pipeline produces MetaHuman assets with the same structure as those produced by the cloud-based MetaHuman Creator app as much as possible, and is useful for users who have their own tooling built around that structure. New users should use the non-legacy pipeline instead. Note that this class is itself abstract. A Blueprint subclass should be used to reference the content this pipeline depends on.
- L26 _public prototype_ `virtual void SetDefaultEditorPipeline() override;`
- L27 _public prototype_ `virtual const UMetaHumanCollectionEditorPipeline* GetEditorPipeline() const override;`
- L28 _public prototype_ `virtual UMetaHumanCollectionEditorPipeline* GetMutableEditorPipeline() override;`
- L31 _public prototype_ `virtual TSubclassOf<AActor> GetActorClass() const override;`
- L35 _public member_ `TObjectPtr<UMetaHumanCollectionEditorPipeline> EditorPipeline;` — `UPROPERTY(EditAnywhere, NoClear, Instanced, Category = "Character", meta = (FullyExpand, AllowedClasses = "/Script/MetaHumanDefaultEditorPipeline.MetaHumanDefaultEditorPipelineLegacy"))`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanDefaultPipeline/Public/MetaHumanDefaultPipelineUEFN.h` (Public)


#### class `UMetaHumanDefaultPipelineUEFN`  
`class UMetaHumanDefaultPipelineUEFN : public UMetaHumanDefaultPipelineLegacy`  
_L20-33_
- reflection: `UCLASS(Abstract)`
- inherits: `UMetaHumanDefaultPipelineLegacy`
- desc: Pipeline for building UEFN actor-based MetaHumans. This pipeline is based on the legacy version since the UEFN structure for MetaHumans is the same as the one from the legacy pipelines but it will save the assets at the end of the build process and will add the MetaHuman Component for UEFN in the MetaHuman blueprint. Note that this class is itself abstract. A Blueprint subclass should be used to reference the content this pipeline depends on.
- L27 _public prototype_ `virtual void SetDefaultEditorPipeline() override;`
- L32 _public member_ `FFilePath UefnProjectFilePath;` — `UPROPERTY(EditAnywhere, Category = "Build", Meta = (FilePathFilter = "UEFN Project (*.uefnproject)|*.uefnproject"))`
