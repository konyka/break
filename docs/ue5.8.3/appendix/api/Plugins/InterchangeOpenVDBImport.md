# Plugins / InterchangeOpenVDBImport

- module root: `Plugins/Interchange/Extensions/OpenVDB/Source/Import`
- headers: 3; symbols: 24
- symbol kinds: class=2, delegate=1, member=3, namespace=5, prototype=13
- PrivateDependencyModuleNames: InterchangeCore, InterchangeEngine, InterchangeImport, InterchangeNodes, SparseVolumeTexture
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Interchange/Extensions/OpenVDB/Source/Import/Private/InterchangeOpenVDBImportLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeOpenVDBImport, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeOpenVDBImport, Log, All);`

### `Plugins/Interchange/Extensions/OpenVDB/Source/Import/Public/InterchangeOpenVDBImportModule.h` (Public)


#### class `FInterchangeOpenVDBImportModule`  
`class FInterchangeOpenVDBImportModule : public IModuleInterface`  
_L7-15_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule() override;`
- L11 _public prototype_ `virtual void ShutdownModule() override;`
- L14 _private member_ `FDelegateHandle PostEngineInitHandle;`

### `Plugins/Interchange/Extensions/OpenVDB/Source/Import/Public/InterchangeOpenVDBTranslator.h` (Public)


#### class `UInterchangeOpenVDBTranslator`  
`class UInterchangeOpenVDBTranslator : public UInterchangeTranslatorBase , public IInterchangeVolumePayloadInterface`  
_L24-53_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UInterchangeTranslatorBase,IInterchangeVolumePayloadInterface`
- L31 _public prototype_ `UInterchangeOpenVDBTranslator();`
- L34 _public prototype_ `virtual EInterchangeTranslatorType GetTranslatorType() const override;` — Begin UInterchangeTranslatorBase interface
- L35 _public prototype_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const override;`
- L36 _public prototype_ `virtual bool CanImportSourceData(const UInterchangeSourceData* InSourceData) const override;`
- L37 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`
- L38 _public prototype_ `virtual bool Translate(UInterchangeBaseNodeContainer& BaseNodeContainer) const override;`
- L39 _public prototype_ `virtual void ReleaseSource() override;`
- L40 _public prototype_ `virtual UInterchangeTranslatorSettings* GetSettings() const override;`
- L41 _public prototype_ `virtual void SetSettings(const UInterchangeTranslatorSettings* InterchangeTranslatorSettings) override;`
- L45 _public prototype_ `virtual TOptional<UE::Interchange::FVolumePayloadData> GetVolumePayloadData(const UE::Interchange::FVolumePayloadKey& PayloadKey) const override;` — Begin Interchange payload interfaces
- L49 _private member_ `TUniquePtr<UE::InterchangeOpenVDBTranslator::Private::UInterchangeOpenVDBTranslatorImpl> Impl;`
- L52 _private member_ `mutable TObjectPtr<UInterchangeVolumeTranslatorSettings> TranslatorSettings = nullptr;` — `UPROPERTY(Transient, DuplicateTransient)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Interchange` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace InterchangeOpenVDBTranslator` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::InterchangeOpenVDBTranslator`)
