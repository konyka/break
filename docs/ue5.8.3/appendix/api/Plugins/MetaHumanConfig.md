# Plugins / MetaHumanConfig

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanConfig`
- headers: 3; symbols: 58
- symbol kinds: class=3, enum=1, enumerator=4, macro=1, member=18, prototype=31
- PrivateDependencyModuleNames: CaptureDataCore, CoreUObject, Engine, MeshTrackerInterface, MetaHumanCaptureData, MetaHumanCore, MetaHumanCoreTech, MetaHumanCoreTechLib, PlatformCrypto, PlatformCryptoContext, PlatformCryptoTypes, Projects, RigLogicModule, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanConfig/Private/MetaHumanConfigStyle.h` (Private)


#### class `FMetaHumanConfigStyle`  
`class FMetaHumanConfigStyle : public FSlateStyleSet`  
_L9-26_
- inherits: `FSlateStyleSet`
- desc: A Style set for MetaHuman Config asset
- L13 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L14 _public prototype_ `static const FMetaHumanConfigStyle& Get();`
- L16 _public prototype_ `static void ReloadTextures();`
- L18 _public prototype_ `static void Register();`
- L19 _public prototype_ `static void Unregister();`
- L23 _private prototype_ `FMetaHumanConfigStyle();`
- L25 _private member_ `static FName StyleName;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanConfig/Public/MetaHumanConfig.h` (Public)


#### class `FMetaHumanConfig`  
`class FMetaHumanConfig`  
_L14-22_
- L19 _public prototype_ `static bool GetInfo(class UCaptureData* InCaptureData, const FString& InComponent, FString& OutDisplayName);` — Gets the config directory and user-friendly display name associated with some capture data
- L20 _public prototype_ `static bool GetInfo(class UCaptureData* InCaptureData, const FString& InComponent, UMetaHumanConfig*& OutConfig);`
- L21 _public prototype_ `static bool GetInfo(class UCaptureData* InCaptureData, const FString& InComponent, FString& OutDisplayName, UMetaHumanConfig*& OutConfig);`

#### enum `EMetaHumanConfigType`  
`enum class EMetaHumanConfigType : uint8`  
_L27-33_
- reflection: `UENUM()`
- L29 _public enumerator_ `Unspecified`
- L30 _public enumerator_ `Solver`
- L31 _public enumerator_ `Fitting`
- L32 _public enumerator_ `PredictiveSolver`

#### class `UMetaHumanConfig`  
`class UMetaHumanConfig : public UObject`  
_L43-112_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: MetaHuman Config Asset Holds configuration info used by other MetaHuman components.
- L49 _public prototype_ `bool ReadFromDirectory(const FString& InPath);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Import")`
- L51 _public prototype_ `FString GetSolverTemplateData() const;`
- L52 _public prototype_ `FString GetSolverConfigData() const;`
- L53 _public prototype_ `FString GetSolverDefinitionsData() const;`
- L54 _public prototype_ `FString GetSolverHierarchicalDefinitionsData() const;`
- L55 _public prototype_ `FString GetSolverHierarchicalDefinitionsPlusChinCompressData() const;`
- L56 _public prototype_ `FString GetSolverPCAFromDNAData() const;`
- L58 _public prototype_ `FString GetFittingTemplateData() const;`
- L59 _public prototype_ `FString GetFittingConfigData() const;`
- L60 _public prototype_ `FString GetFittingConfigTeethData() const;`
- L61 _public prototype_ `FString GetFittingIdentityModelData() const;`
- L62 _public prototype_ `FString GetFittingControlsData() const;`
- L64 _public prototype_ `TArray<uint8> GetPredictiveGlobalTeethTrainingData() const;`
- L65 _public prototype_ `TArray<uint8> GetPredictiveTrainingData() const;`
- L68 _public member_ `EMetaHumanConfigType Type = EMetaHumanConfigType::Unspecified;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Parameters")`
- L71 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = "Parameters")`
- L74 _public member_ `FString Version;` — `UPROPERTY(EditAnywhere, Category = "Parameters")`
- L77 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L83 _private member_ `int32 InternalVersion = 1;` — `UPROPERTY()` — To increase version dont adjust this default, but set InternalVersion in ReadFromDirectory
- L85 _private member_ `FByteBulkData SolverTemplateDataCipherText;`
- L86 _private member_ `FByteBulkData SolverConfigDataCipherText;`
- L87 _private member_ `FByteBulkData SolverDefinitionsCipherText;`
- L88 _private member_ `FByteBulkData SolverHierarchicalDefinitionsCipherText;`
- L89 _private member_ `FByteBulkData SolverHierarchicalDefinitionsPlusChinCompressCipherText;`
- L90 _private member_ `FByteBulkData SolverPCAFromDNACipherText;`
- L91 _private member_ `FByteBulkData FittingTemplateDataCipherText;`
- L92 _private member_ `FByteBulkData FittingConfigDataCipherText;`
- L93 _private member_ `FByteBulkData FittingConfigTeethDataCipherText;`
- L94 _private member_ `FByteBulkData FittingIdentityModelDataCipherText;`
- L95 _private member_ `FByteBulkData FittingControlsDataCipherText;`
- L96 _private member_ `FByteBulkData PredictiveGlobalTeethTrainingData;`
- L97 _private member_ `FByteBulkData PredictiveTrainingData;`
- L99 _private prototype_ `bool Encrypt(const FString& InPlainText, FByteBulkData& OutCipherText) const;`
- L100 _private prototype_ `bool Decrypt(const FByteBulkData& InCipherText, FString& OutPlainText) const;`
- L102 _private prototype_ `FString DecryptToString(const FByteBulkData& InCipherText) const;`
- L104 _private prototype_ `UMetaHumanConfig* GetBaseConfig() const;`
- L106 _private prototype_ `bool VerifyFittingConfig(const FString& InFittingTemplateDataJson, const FString& InFittingConfigDataJson, const FString& InFittingConfigTeethDataJson, const FString& InFittingIdentityModelDataJson, const FString& InFittingControlsDataJson, FString& OutErrorString) const;`
- L109 _private prototype_ `bool VerifySolverConfig(const FString& InSolverTemplateDataJson, const FString& InSolverConfigDataJson, const FString& InSolverDefinitionsDataJson, const FString& InSolverHierarchicalDefinitionsDataJson, const FString& InSolverHierarchicalDefinitionsPlusChinCompressDataJson, const FString& InSolverPCAFromDNADataJson, FString& OutErrorString) const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCONFIG_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanConfig/Public/MetaHumanConfigLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanConfig, Log, All);`
