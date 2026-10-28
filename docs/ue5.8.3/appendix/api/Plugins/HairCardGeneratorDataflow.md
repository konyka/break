# Plugins / HairCardGeneratorDataflow

- module root: `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorDataflow`
- headers: 8; symbols: 110
- symbol kinds: class=1, function=2, member=64, namespace=6, prototype=18, struct=15, variable=4
- PublicDependencyModuleNames: Chaos, ChaosCore, Core, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, DataflowEnginePlugin, Engine, GeometryCore, GeometryFramework, HairCardGeneratorEditor, HairCardGeneratorFramework, HairStrandsCore, HairStrandsDataflow, HairStrandsEditor, PlanarCut

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorDataflow/Public/BuildCardsSettingsNode.h` (Public)


#### struct `FGroomCardsSettings`  
`struct FGroomCardsSettings`  
_L24-43_
- reflection: `USTRUCT()`
- L30 _public member_ `TObjectPtr<UHairCardGeneratorPluginSettings> GenerationSettings = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Groom Cards")` — Generator settings to be built
- L34 _public member_ `uint8 GenerationFlags = 0;` — `UPROPERTY(EditAnywhere, Category = "Groom Cards")` — Generation flags to output the assets
- L38 _public member_ `uint8 PipelineFlags = 0;` — `UPROPERTY(EditAnywhere, Category = "Groom Cards")` — Pipeline flags to generate clumps, geometry and textures
- L42 _public member_ `TObjectPtr<UGroomAsset> GroomAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Groom Cards")` — Groom asset to generate the

#### struct `FGroomAdvancedFilterSettings`  
`struct FGroomAdvancedFilterSettings`  
_L47-71_
- reflection: `USTRUCT()`
- L53 _public member_ `bool bUseMultiCardClumps = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Cards Filter")` — Generate multiple cards (3) per strand clump to give the appearance of volume
- L57 _public member_ `bool bUseAdaptiveSubdivision = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Cards Filter")` — Use adaptive subdivision when generating card geometry
- L61 _public member_ `int32 MaxVerticalSegmentsPerCard = 10;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Cards Filter")` — Maximum number of segments along each card (aligned with the strands), ignored for adaptive subdivision
- L65 _public member_ `float StrandWidthScalingFactor = 1.0f;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Cards Filter")` — Scaling factor mapping strand-width to pixel-size for coverage texture
- L70 _public member_ `bool UseOptimizedCompressionFactor = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Cards Filter")` — Compress textures along strand direction to save vertical redolution, if strands are all moving in nearly the same direction

#### struct `FGroomFilterSettings`  
`struct FGroomFilterSettings`  
_L74-105_
- reflection: `USTRUCT()`
- L80 _public member_ `FName FilterName;` — `UPROPERTY(EditAnywhere, Category="Groom Cards")` — Filter group name to be identified in the override settings
- L84 _public member_ `int32 NumClumps = UE::HairCardsGen::Private::NumClumps;` — `UPROPERTY(EditAnywhere, Category="Groom Cards", meta=(ClampMin="1", ClampMax="100000", DisplayName = "Num Clumps"))` — Total number of cards to generate for this LOD settings
- L88 _public member_ `int32 NumFlyaways = UE::HairCardsGen::Private::NumFlyaways;` — `UPROPERTY(EditAnywhere, Category="Groom Cards", meta=(ClampMin="0", ClampMax="1000"))` — Maximum number of cards to assign to flyaway strands
- L92 _public member_ `int32 NumTriangles = UE::HairCardsGen::Private::NumTriangles;` — `UPROPERTY(EditAnywhere, Category="Groom Cards", meta=(ClampMin="1", ClampMax="100000"))` — Total number of triangles to generate for this LOD settings
- L96 _public member_ `int32 NumTextures = UE::HairCardsGen::Private::NumTextures;` — `UPROPERTY(EditAnywhere, Category="Groom Cards")` — Total number of textures to generate for this LOD settings
- L100 _public member_ `TArray<FName> CardGroups;` — `UPROPERTY(EditAnywhere, Category="Groom Cards")` — Card group names that will belong to the filter group settings
- L104 _public member_ `FGroomAdvancedFilterSettings AdvancedOptions;` — `UPROPERTY(EditAnywhere, Category="Groom Cards")` — Advanced options for the filter group settings

#### struct `FGroomAdvancedGenerationSettings`  
`struct FGroomAdvancedGenerationSettings`  
_L108-139_
- reflection: `USTRUCT()`
- L114 _public member_ `bool bReduceCardsFromPreviousLOD = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay,Category="Cards Generation")` — Use previous LOD generated cards and textures but reduce triangle count and flyaways
- L118 _public member_ `bool bGenerateGeometryForAllGroups = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Cards Generation", meta=(AllowPrivateAccess))` — Generate geometry for all groom groups on group 0
- L122 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, AdvancedDisplay,Category="Cards Generation", meta=(ClampMin="0", ClampMax="10000"))` — Seed value for pseudo-random number generation (set to a specific value for repeatable results)
- L126 _public member_ `bool bUseReservedSpaceFromPreviousLOD = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Texture Rendering")` — Place new card textures in reserved space from previous LOD
- L130 _public member_ `EHairCardAtlasSize AtlasSize = EHairCardAtlasSize::AtlasSize4096;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Texture Rendering")` — Size of hair card texture atlases
- L134 _public member_ `int32 ReserveTextureSpaceLOD = 0;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Texture Rendering", meta=(ClampMin="0", ClampMax="75"))` — Percentage of texture atlas space to reserve for higher LODs
- L138 _public member_ `bool bUseGroomAssetStrandWidth = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Texture Rendering")` — Use strand width

#### struct `FGroomGenerationSettings`  
`struct FGroomGenerationSettings`  
_L142-161_
- reflection: `USTRUCT()`
- L148 _public member_ `int32 LODIndex = 0;` — `UPROPERTY(EditAnywhere, Category="Groom Cards")` — LOD index of the filter group settings
- L152 _public member_ `int32 GroupIndex = 0;` — `UPROPERTY(EditAnywhere, Category="Groom Cards")` — Group index of the filter group settings
- L156 _public member_ `TArray<FGroomFilterSettings> FilterSettings;` — `UPROPERTY(EditAnywhere, Category="Groom Cards")` — List of filter settings to use for that generation
- L160 _public member_ `FGroomAdvancedGenerationSettings AdvancedOptions;` — `UPROPERTY(EditAnywhere, AdvancedDisplay,Category="Groom Cards")` — Advanced options for the generation settings

#### struct `FBuildCardsSettingsNode`  
`struct FBuildCardsSettingsNode : public FDataflowNode`  
_L165-210_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Build the cards generation settings
- L173 _public prototype_ `FBuildCardsSettingsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L178 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L180 _private function_ `virtual bool CanDebugDraw() const override`
- L181 _private function_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override`
- L182 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L184 _private prototype_ `virtual void OnPropertyChanged(UE::Dataflow::FContext& Context, const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L189 _private member_ `TObjectPtr<UGroomAsset> GroomAsset;` — `UPROPERTY(EditAnywhere, Category = "Groom Cards", meta = (DataflowInput))` — Groom asset to build the cards settings from
- L193 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))` — Managed array collection to be used to store datas
- L197 _private member_ `TArray<FGroomCardsSettings> CardsSettings;` — `UPROPERTY(meta = (DataflowOutput))` — Generator cards settings to be built
- L201 _private member_ `TArray<FGroomGenerationSettings> GenerationSettings;` — `UPROPERTY(EditAnywhere, Category = "Groom Cards")` — List of filter settings to override
- L205 _private member_ `FString AssetsDirectoryPath = "";` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Groom Cards")` — Assets directory path used when generating the mesh/textures
- L209 _private member_ `FString AssetsBaseName = "";` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Groom Cards")` — Assets base name used when generating the mesh/textures

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace HairCardsGen` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::HairCardsGen`)
- L17 _variable_ `static constexpr int32 NumClumps = 800;` (scope `UE::HairCardsGen::Private`)
- L18 _variable_ `static constexpr int32 NumFlyaways = 100;` (scope `UE::HairCardsGen::Private`)
- L19 _variable_ `static constexpr int32 NumTriangles = 45000;` (scope `UE::HairCardsGen::Private`)
- L20 _variable_ `static constexpr int32 NumTextures = 100;` (scope `UE::HairCardsGen::Private`)

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorDataflow/Public/CardsAssetTerminalNode.h` (Public)


#### struct `FCardsAssetTerminalNode`  
`struct FCardsAssetTerminalNode : public FDataflowTerminalNode`  
_L15-37_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom, DataflowTerminal))`
- inherits: `FDataflowTerminalNode`
- L27 _private prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L28 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L32 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection", DataflowRenderGroups = "CardsTexture"))`
- L36 _private member_ `TArray<FGroomCardsSettings> CardsSettings;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "CardsSettings"))` — Generator settings to be used

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorDataflow/Public/GenerateCardsClumpsNode.h` (Public)


#### struct `FCardsClumpsSettings`  
`struct FCardsClumpsSettings`  
_L15-30_
- reflection: `USTRUCT()`
- L21 _public member_ `FName FilterName = NAME_None;` — `UPROPERTY(EditAnywhere, Category="Groom Cards")` — Card filter name for which we will override the number of cards/flyaways
- L25 _public member_ `int32 NumCards = UE::HairCardsGen::Private::NumClumps;` — `UPROPERTY(EditAnywhere, Category="Groom Cards", meta=(ClampMin="1", ClampMax="100000", DisplayName = "Num Clumps"))` — Total number of cards to generate for this LOD settings
- L29 _public member_ `int32 NumFlyaways = UE::HairCardsGen::Private::NumFlyaways;` — `UPROPERTY(EditAnywhere, Category="Groom Cards", meta=(ClampMin="0", ClampMax="1000"))` — Maximum number of cards to assign to flyaway strands

#### struct `FGenerateCardsClumpsNode`  
`struct FGenerateCardsClumpsNode : public FDataflowNode`  
_L34-65_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Generate the clumps used to build the cards from the strands
- L43 _public member_ `static const FName ObjectNumClumpsAttribute;`
- L44 _public member_ `static const FName CurveFilterIndicesAttribute;`
- L46 _public prototype_ `FGenerateCardsClumpsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L51 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L56 _private member_ `TArray<FCardsClumpsSettings> ClumpsSettings;` — `UPROPERTY(EditAnywhere, Category = "Groom Cards", meta = (DisplayName = "Override Settings"))` — Per LOD settings for each cards generation
- L60 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection", DataflowRenderGroups = "CardsClumps"))` — Managed array collection to be used to store datas
- L64 _private member_ `TArray<FGroomCardsSettings> CardsSettings;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Cards Settings", DataflowPassthrough = "CardsSettings"))` — Generator settings to be used

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorDataflow/Public/GenerateCardsGeometryNode.h` (Public)


#### struct `FCardsGeometrySettings`  
`struct FCardsGeometrySettings`  
_L15-26_
- reflection: `USTRUCT()`
- L21 _public member_ `FName FilterName = NAME_None;` — `UPROPERTY(EditAnywhere, Category="Groom Cards")` — Card filter name for which we will override the number of triangles
- L25 _public member_ `int32 NumTriangles = UE::HairCardsGen::Private::NumTriangles;` — `UPROPERTY(EditAnywhere, Category="Groom Cards", meta=(ClampMin="1", ClampMax="100000"))` — Total number of triangles to generate for this LOD settings

#### struct `FGenerateCardsGeometryNode`  
`struct FGenerateCardsGeometryNode : public FDataflowNode`  
_L30-64_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Generate the geometry used to build the cards from the strands
- L39 _public member_ `static const FName FaceVertexIndicesAttribute;`
- L40 _public member_ `static const FName VertexCardIndicesAttribute;`
- L42 _public member_ `static const FName CardsVerticesGroup;`
- L43 _public member_ `static const FName CardsFacesGroup;`
- L45 _public prototype_ `FGenerateCardsGeometryNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L50 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L55 _private member_ `TArray<FCardsGeometrySettings> GeometrySettings;` — `UPROPERTY(EditAnywhere, Category = "Groom Cards", meta = (DisplayName = "Override Settings"))` — Per LOD settings for each cards generation
- L59 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection", DataflowRenderGroups = "CardsGeometry"))` — Managed array collection to be used to store datas
- L63 _private member_ `TArray<FGroomCardsSettings> CardsSettings;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Cards Settings", DataflowPassthrough = "CardsSettings"))` — Generator settings to be used

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorDataflow/Public/GenerateCardsTexturesNode.h` (Public)


#### struct `FCardsTextureSettings`  
`struct FCardsTextureSettings`  
_L15-26_
- reflection: `USTRUCT()`
- L21 _public member_ `FName FilterName = NAME_None;` — `UPROPERTY(EditAnywhere, Category="Groom Cards")` — Card filter name for which we will override the number of textures
- L25 _public member_ `int32 NumTextures = UE::HairCardsGen::Private::NumTextures;` — `UPROPERTY(EditAnywhere, Category="Groom Cards")` — Total number of textures to generate for this LOD settings

#### struct `FGenerateCardsTexturesNode`  
`struct FGenerateCardsTexturesNode : public FDataflowNode`  
_L30-62_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Generate the cards texture for final rendering
- L40 _public member_ `static const FName ObjectTextureIndicesAttribute;`
- L41 _public member_ `static const FName VertexTextureUVsAttribute;`
- L43 _public prototype_ `FGenerateCardsTexturesNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L48 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L53 _private member_ `TArray<FCardsTextureSettings> TextureSettings;` — `UPROPERTY(EditAnywhere, Category = "Groom Cards", meta = (DisplayName = "Override Settings"))` — Per LOD settings for each cards generation
- L57 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection", DataflowRenderGroups = "CardsTexture"))` — Managed array collection to be used to store datas
- L61 _private member_ `TArray<FGroomCardsSettings> CardsSettings;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Cards Settings", DataflowPassthrough = "CardsSettings"))` — Generator settings to be used

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorDataflow/Public/HairCardDataflowRendering.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace CardGen` (scope `UE`)
- L5 _namespace_ `namespace Private` (scope `UE::CardGen`)
- L7 _prototype_ `void RegisterCollectionRenderableTypes();` (scope `UE::CardGen::Private`)

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorDataflow/Public/HairCardGeneratorDataflowModule.h` (Public)


#### class `FHairCardGeneratorDataflowModule`  
`class FHairCardGeneratorDataflowModule : public IModuleInterface`  
_L9-17_
- inherits: `IModuleInterface`
- desc: Hair card generator dataflow module public interface
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorDataflow/Public/ModifyCardsAttributesNode.h` (Public)


#### struct `FExtractCardsAttributesNode`  
`struct FExtractCardsAttributesNode : public FDataflowNode`  
_L18-45_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Extract the cards attributes from the description onto the collection
- L31 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L36 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection", DataflowRenderGroups = "CardsClumps"))` — Managed array collection to be used to store datas
- L40 _private member_ `TObjectPtr<const UGroomAsset> GroomAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Groom", meta = (DataflowInput, DisplayName = "Groom Asset"))` — Input asset to read the attributes from
- L44 _private member_ `FCollectionAttributeKey CardGroups;` — `UPROPERTY(EditAnywhere, Category = "Groom", meta = (DataflowOutput, DisplayName = "Card Groups"))` — Attribute key for the extracted card group

#### struct `FReportCardsAttributesNode`  
`struct FReportCardsAttributesNode : public FDataflowNode`  
_L49-72_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Reports the cards attributes from the collection onto the description
- L57 _public prototype_ `FReportCardsAttributesNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L62 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L67 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection", DataflowRenderGroups = "CardsClumps"))` — Managed array collection to be used to store data
- L71 _private member_ `TObjectPtr<UGroomAsset> GroomAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Groom", meta = (DataflowInput, DisplayName = "Groom Asset"))` — Input asset to write the attributes onto
