# Plugins / InterchangeAxF

- module root: `Plugins/Experimental/InterchangeAxF/Runtime/Source/InterchangeAxF`
- headers: 4; symbols: 71
- symbol kinds: class=4, delegate=3, enum=1, enumerator=8, function=1, macro=3, member=13, namespace=4, prototype=32, struct=2
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InterchangeAxFAssets, InterchangeCore, InterchangeEngine, InterchangeFactoryNodes, InterchangeImport, InterchangeNodes, InterchangePipelines, Json, MaterialEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/InterchangeAxF/Runtime/Source/InterchangeAxF/Public/AxFInterchangePipeline.h` (Public)


#### struct `FAxFTextureMap`  
`struct FAxFTextureMap`  
_L26-33_
- reflection: `USTRUCT()`
- L31 _public member_ `TObjectPtr<UTexture2D> Texture;` — `UPROPERTY()`
- L32 _public member_ `FVector2f SizeMM;`

#### class `UAxFInterchangePipeline`  
`class UAxFInterchangePipeline : public UInterchangePipelineBase`  
_L36-104_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UInterchangePipelineBase`
- L41 _public prototype_ `UAxFInterchangePipeline();`
- L46 _public member_ `FString PipelineDisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta = (StandAlonePipelineProperty = "True", PipelineInternalEditionData = "True"))`
- L52 _public member_ `EReimportStrategyFlags ReimportStrategy = EReimportStrategyFlags::ApplyNoProperties;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common", meta = (AdjustPipelineAndRefreshDetailOnChange = "True", PipelineInternalEditionData = "True"))` — Set the reimport strategy.
- L55 _public member_ `bool bUseTriplanarMappingByDefault = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AxF")`
- L58 _protected prototype_ `virtual void ExecutePipeline( UInterchangeBaseNodeContainer* BaseNodeContainer, TArray<UInterchangeSourceData*> const& SourceDatas, FString const& ContentBasePath) override;`
- L62 _protected prototype_ `virtual void ExecutePostImportPipeline( UInterchangeBaseNodeContainer const* BaseNodeContainer, FString const& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L66 _protected prototype_ `virtual void ExecutePostFactoryPipeline( UInterchangeBaseNodeContainer const* BaseNodeContainer, FString const& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L70 _protected prototype_ `virtual void AdjustSettingsForContext(FInterchangePipelineContextParams const& ContextParams) override;`
- L75 _protected prototype_ `void CreateSpecularProfileFactoryNode(const UInterchangeSpecularProfileNode* SpecularProfileNode, UInterchangeBaseNodeContainer* BaseNodeContainer, TObjectPtr<UAxFMaterialObjectNode> AxFNode);` — NOTE: This is a copied and modified version of UInterchangeGenericMaterialPipeline::CreateSpecularProfileFactoryNode(). This would be handled automatically, but for now the compromise is to just do what the Generic Material Pipeline does, in order to remove it as a dependency in the Interchange Pipeline Stack.
- L78 _protected prototype_ `virtual void PreDialogCleanup(FName const PipelineStackName) override;`
- L80 _protected prototype_ `virtual bool IsSettingsAreValid(TOptional<FText>& OutInvalidReason) const override;`
- L82 _protected prototype_ `virtual void FilterPropertiesFromTranslatedData(UInterchangeBaseNodeContainer* InBaseNodeContainer) override;`
- L84 _protected prototype_ `virtual void GetSupportAssetClasses(TArray<UClass*>& PipelineSupportAssetClasses) const override;`
- L88 _private member_ `TArray<TObjectPtr<UAxFMaterialObjectNode>> AxFObjectNodes;` — `UPROPERTY(Transient)`
- L92 _private member_ `TArray<TObjectPtr<UInterchangeTexture2DFactoryNode>> Texture2DFactoryNodes;` — `UPROPERTY(Transient)` — Texture handling
- L95 _private member_ `TMap<FString, FAxFTextureMap> TexturesMap;` — `UPROPERTY()`
- L99 _private member_ `TObjectPtr<USpecularProfile> SpecularProfile;` — `UPROPERTY()` — Specular profile handling
- L103 _private member_ `TObjectPtr<UInterchangeGenericTexturePipeline> TexturePipeline;` — `UPROPERTY()` — Generic texture pipeline to be used to create the necessary texture assets the materials use

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API INTERCHANGEAXF_API`
- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAxFInterchangePipeline, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAxFInterchangePipeline, Log, All);`

### `Plugins/Experimental/InterchangeAxF/Runtime/Source/InterchangeAxF/Public/AxFMaterialObjectNode.h` (Public)


#### enum `EAxFFeature`  
`enum EAxFFeature : uint8`  
_L12-22_
- reflection: `UENUM()`
- L14 _public enumerator_ `Alpha`
- L15 _public enumerator_ `Anisotropy`
- L16 _public enumerator_ `ClearCoat`
- L17 _public enumerator_ `CPA2`
- L18 _public enumerator_ `Flakes`
- L19 _public enumerator_ `Heightmap`
- L20 _public enumerator_ `Sheen`
- L21 _public enumerator_ `Transmission`

#### struct `UE::Interchange::FAxFMaterialObjectData`  
`struct FAxFMaterialObjectData`  
_L28-39_
- L30 _public prototype_ `virtual ~FAxFMaterialObjectData() = default;`
- L31 _public prototype_ `FAxFMaterialObjectData() = default;`
- L32 _public prototype_ `FAxFMaterialObjectData(FAxFMaterialObjectData &&) = default;`
- L33 _public prototype_ `FAxFMaterialObjectData &operator=(FAxFMaterialObjectData &&) = default;`
- L34 _public prototype_ `FAxFMaterialObjectData(const FAxFMaterialObjectData &) = delete;`
- L35 _public prototype_ `FAxFMaterialObjectData &operator=(const FAxFMaterialObjectData &) = delete;`
- L37 _public member_ `TMap<FString, FLinearColor> ValuesMap;`
- L38 _public member_ `TArray<EAxFFeature> UsedFeatures;`

#### class `UAxFMaterialObjectNode`  
`class UAxFMaterialObjectNode : public UInterchangeBaseNode`  
_L44-61_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UInterchangeBaseNode`
- L48 _private prototype_ `UAxFMaterialObjectNode();`
- L52 _public prototype_ `void InitializeAxFMaterialObjectNode(const FString &UniqueID, const FString &DisplayLabel);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AxFObject")`
- L54 _public prototype_ `virtual FString GetTypeName() const override;`
- L56 _public prototype_ `virtual const TOptional<FString> GetPayloadKey() const;`
- L58 _public prototype_ `virtual void SetPayloadKey(const FString &PayloadKey);`
- L60 _public member_ `UE::Interchange::FAxFMaterialObjectData PayloadData;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEAXF_API`
- L24 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Experimental/InterchangeAxF/Runtime/Source/InterchangeAxF/Public/AxFTranslator.h` (Public)


#### class `UAxFTranslator`  
`class UAxFTranslator : public UInterchangeTranslatorBase , public IInterchangeTexturePayloadInterface`  
_L21-44_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UInterchangeTranslatorBase,IInterchangeTexturePayloadInterface`
- L28 _public prototype_ `virtual bool CanImportSourceData(const UInterchangeSourceData* InSourceData) const override;`
- L30 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`
- L32 _public function_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const override`
- L37 _public prototype_ `virtual bool Translate(UInterchangeBaseNodeContainer &BaseNodeContainer) const override;`
- L40 _public prototype_ `virtual TOptional<UE::Interchange::FImportImage> GetTexturePayloadData(const FString &PayloadKey, TOptional<FString> &AlternateTexturePath) const override;` — IInterchangeTexturePayloadInterface
- L41 _public prototype_ `virtual bool SupportCompressedTexturePayloadData() const override;`
- L42 _public prototype_ `virtual TOptional<UE::Interchange::FImportImage> GetCompressedTexturePayloadData(const FString &PayloadKey, TOptional<FString> &AlternateTexturePath) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INTERCHANGEAXF_API`
- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAxFTranslator, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAxFTranslator, Log, All);`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Experimental/InterchangeAxF/Runtime/Source/InterchangeAxF/Public/InterchangeAxF.h` (Public)


#### class `FInterchangeAxFModule`  
`class FInterchangeAxFModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeAxF, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeAxF, Log, All);`
