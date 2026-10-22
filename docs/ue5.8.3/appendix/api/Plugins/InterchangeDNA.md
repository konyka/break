# Plugins / InterchangeDNA

- module root: `Plugins/MetaHuman/MetaHumanSDK/Source/InterchangeDNA`
- headers: 3; symbols: 56
- symbol kinds: class=6, delegate=1, function=5, macro=2, member=12, prototype=29, struct=1
- PrivateDependencyModuleNames: ContentBrowser, ContentBrowserData, CoreUObject, Engine, MetaHumanSDKEditor, PhysicsUtilities, Projects, RigLogicModule, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, InterchangeCommon, InterchangeCore, InterchangeEngine, InterchangeImport, InterchangeNodes, InterchangePipelines, LevelSequence, MeshDescription, RigLogicLib, SkeletalMeshDescription, StaticMeshDescription, ToolMenus

### `Plugins/MetaHuman/MetaHumanSDK/Source/InterchangeDNA/Private/MetaHumanDNAImportColorMap.h` (Private)


#### struct `FMeshVertexColorData`  
`struct FMeshVertexColorData`  
_L11-20_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public member_ `FString MeshName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Vertex Colors")`
- L19 _public member_ `TArray<FLinearColor> Colors;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Vertex Colors")`

#### class `UDNAMeshVertexColorDataAsset`  
`class UDNAMeshVertexColorDataAsset : public UDataAsset`  
_L23-44_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- L29 _public member_ `TArray<FMeshVertexColorData> MeshColorEntries;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Vertex Colors")`
- L32 _public function_ `FLinearColor GetColorByMeshAndIndex(const FString& InMeshName, int32 InVertexId) const` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Vertex Colors")`

### `Plugins/MetaHuman/MetaHumanSDK/Source/InterchangeDNA/Public/InterchangeDnaModule.h` (Public)


#### class `FInterchangeDnaModule`  
`class FInterchangeDnaModule : public IModuleInterface`  
_L16-36_
- inherits: `IModuleInterface`
- L21 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _public prototype_ `static FInterchangeDnaModule& GetModule();`
- L28 _public prototype_ `void SetSkelMeshDNAData(TNotNull<class USkeletalMesh*> InSkelMesh, TSharedPtr<IDNAReader> InDNAReader);` — `UE_DEPRECATED(5.8, "This function has been deprecated, use CreateAndAttachDNAToSkeletalMesh instead")` — Set DNA asset user data and map joints for skeletal mesh
- L31 _public prototype_ `void CreateAndAttachDNAToSkeletalMesh(TNotNull<class USkeletalMesh*> InSkelMesh, TSharedPtr<IDNAReader> InDNAReader);` — Create DNA Asset and attach it to skeletal mesh via DNAAssetUserData
- L34 _public prototype_ `class USkeletalMesh* ImportSync(const FString& InNewRigAssetName, const FString& InNewRigPath, TSharedPtr<IDNAReader> InDNAReader, TSoftObjectPtr<class USkeleton> InSkeleton, const FDNAConfig& DNAConfig = FDNAConfig());` — DNAInterchangeModule implementation

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INTERCHANGEDNA_API`

### `Plugins/MetaHuman/MetaHumanSDK/Source/InterchangeDNA/Public/MetaHumanInterchangeDnaTranslator.h` (Public)


#### class `FDnaPayloadContextBase`  
`class FDnaPayloadContextBase`  
_L21-29_
- L24 _public prototype_ `virtual ~FDnaPayloadContextBase() = default;`
- L25 _public prototype_ `virtual FString GetPayloadType() const = 0;`
- L27 _public function_ `virtual bool FetchMeshPayload(TSharedPtr<IDNAReader> InDNAReader, const FTransform& MeshGlobalTransform, UE::Interchange::FMeshPayloadData& OutMeshPayloadData)`

#### class `FDnaMeshPayloadContext`  
`class FDnaMeshPayloadContext : public FDnaPayloadContextBase`  
_L31-51_
- inherits: `FDnaPayloadContextBase`
- L34 _public prototype_ `virtual ~FDnaMeshPayloadContext() = default;`
- L35 _public function_ `virtual FString GetPayloadType() const override`
- L38 _public prototype_ `static void PopulateStaticMeshDescription(FMeshDescription& OutMeshDescription, const IDNAReader& InDNAReader, const int32 InMeshIndex);` — Populates mesh description attributes with  static mesh data from the DNA reader for specified mesh
- L41 _public prototype_ `virtual bool FetchMeshPayload(TSharedPtr<IDNAReader> InDNAReader, const FTransform& MeshGlobalTransform, UE::Interchange::FMeshPayloadData& OutMeshPayloadData) override;`
- L43 _public member_ `bool bIsSkinnedMesh = false;`
- L44 _public member_ `int32 DnaLodIndex;`
- L45 _public member_ `int32 DnaMeshIndex;`
- L47 _private prototype_ `bool FetchMeshPayloadInternal(TSharedPtr<IDNAReader> InDNAReader , const FTransform& MeshGlobalTransform , FMeshDescription& OutMeshDescription , TArray<FString>& OutJointNames) const;`

#### class `FDnaMorphTargetPayloadContext`  
`class FDnaMorphTargetPayloadContext : public FDnaPayloadContextBase`  
_L53-68_
- inherits: `FDnaPayloadContextBase`
- L56 _public prototype_ `virtual ~FDnaMorphTargetPayloadContext() = default;`
- L57 _public function_ `virtual FString GetPayloadType() const override`
- L59 _public prototype_ `virtual bool FetchMeshPayload(TSharedPtr<IDNAReader> InDNAReader, const FTransform& MeshGlobalTransform, UE::Interchange::FMeshPayloadData& OutMeshPayloadData) override;`
- L60 _public member_ `int32 DnaMeshIndex;`
- L61 _public member_ `int32 DnaMorphTargetIndex;`
- L62 _public member_ `int32 DnaChannelIndex;`
- L65 _private prototype_ `bool FetchMeshPayloadInternal(TSharedPtr<IDNAReader> InDNAReader , const FTransform& MeshGlobalTransform , FMeshDescription& OutMorphTargetMeshDescription) const;`

#### class `UMetaHumanInterchangeDnaTranslator`  
`class UMetaHumanInterchangeDnaTranslator : public UInterchangeTranslatorBase , public IInterchangeMeshPayloadInterface`  
_L71-126_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTranslatorBase,IInterchangeMeshPayloadInterface`
- L76 _public prototype_ `UMetaHumanInterchangeDnaTranslator();`
- L79 _public prototype_ `virtual bool IsThreadSafe() const override;` — Begin UInterchangeTranslatorBase API
- L80 _public prototype_ `virtual EInterchangeTranslatorType GetTranslatorType() const override;`
- L81 _public prototype_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const override;`
- L82 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`
- L83 _public prototype_ `virtual bool CanImportSourceData(const UInterchangeSourceData* InSourceData) const override;`
- L84 _public prototype_ `virtual bool Translate(UInterchangeBaseNodeContainer& BaseNodeContainer) const override;`
- L85 _public prototype_ `virtual void ReleaseSource() override;`
- L86 _public prototype_ `virtual void ImportFinish() override;`
- L101 _public function_ `virtual TOptional<UE::Interchange::FMeshPayloadData> GetMeshPayloadData(const FInterchangeMeshPayLoadKey& PayLoadKey, const FTransform& MeshGlobalTransform) const override` — `UE_DEPRECATED(5.6, "Deprecated. Use GetMeshPayloadData(const FInterchangeMeshPayLoadKey&) instead.")` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param SourceData - The source data containing the data to translate @param PayloadKey - The key to retrieve the a particular payload contain into the specified source data. @return a PayloadData containing the imported data. The TOptional will not be set if there is an error.
- L108 _public prototype_ `virtual TOptional<UE::Interchange::FMeshPayloadData> GetMeshPayloadData(const FInterchangeMeshPayLoadKey& PayLoadKey, const UE::Interchange::FAttributeStorage& PayloadAttributes) const override;`
- L113 _private member_ `mutable TSharedPtr<IDNAReader> DNAReader;`
- L114 _private member_ `mutable TMap<FString, TSharedPtr<FDnaPayloadContextBase>> PayloadContexts;`
- L117 _private prototype_ `FString GetJointHierarchyName(TSharedPtr<IDNAReader> InDNAReader, int32 JointIndex) const;` — Returns a string containing joint heirarchy as expected by the Interchange system
- L120 _private prototype_ `FString AddDNAMissingJoints(UInterchangeBaseNodeContainer& NodeContainer, const FString& InLastNodeId, FTransform& OutCombinedTransform, const FDNAConfig& DNAConfig) const;` — Add the hard-coded joints that are missing in the DNA file but is expected by the import
- L123 _private prototype_ `bool FetchMeshPayloadData(const FString& PayloadKey, const FTransform& MeshGlobalTransform, UE::Interchange::FMeshPayloadData& OutMeshPayloadData) const;` — A helper function to do sanity checks and further call Fetch payload data on PayloadContexts
- L125 _private member_ `static const TArray<FString> DNAMissingJoints;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API INTERCHANGEDNA_API`
- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(InterchangeDNATranslator, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(InterchangeDNATranslator, Log, All);`
