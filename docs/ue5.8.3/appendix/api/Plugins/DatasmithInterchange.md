# Plugins / DatasmithInterchange

- module root: `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange`
- headers: 22; symbols: 354
- symbol kinds: class=20, delegate=2, enum=1, enumerator=3, externvar=21, function=38, macro=1, member=63, namespace=43, prototype=158, struct=2, typedef=2
- PrivateDependencyModuleNames: CADTools, DatasmithContent, DatasmithCore, DatasmithImporter, DatasmithTranslator, DesktopPlatform, Engine, ExternalSource, InputCore, InterchangeCommonParser, InterchangeEditorPipelines, InterchangeEngine, InterchangeFactoryNodes, InterchangeImport, InterchangeNodes, InterchangePipelines, MeshDescription, ParametricSurface, PropertyEditor, Slate, SlateCore, StaticMeshDescription, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, InterchangeCore, InterchangeImport

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Private/InterchangeDatasmithCustomizations.h` (Private)


#### class `FInterchangeDatasmithTranslatorSettingsCustomization`  
`class FInterchangeDatasmithTranslatorSettingsCustomization : public IDetailCustomization`  
_L13-25_
- inherits: `IDetailCustomization`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Creates an instance of this class
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Private/InterchangeDatasmithLevelPipeline.h` (Private)


#### class `UInterchangeDatasmithLevelPipeline`  
`class UInterchangeDatasmithLevelPipeline : public UInterchangeGenericLevelPipeline`  
_L20-37_
- reflection: `UCLASS(BlueprintType, Experimental)`
- inherits: `UInterchangeGenericLevelPipeline`
- L25 _protected prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath) override;`
- L26 _protected prototype_ `virtual void ExecutePostImportPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L28 _protected prototype_ `virtual UInterchangeActorFactoryNode* CreateActorFactoryNode(const UInterchangeBaseNode* TranslatedAssetNode) const override;`
- L30 _protected prototype_ `virtual void SetUpFactoryNode(UInterchangeActorFactoryNode* ActorFactoryNode, const UInterchangeSceneNode* SceneNode, const UInterchangeBaseNode* TranslatedAssetNode, bool bIsRootJoint = false) const override;`
- L34 _private prototype_ `void SetupAreaLight(UInterchangeDatasmithAreaLightFactoryNode* AreaLightFactoryNode, const UInterchangeDatasmithAreaLightNode* AreaLightNode) const;`

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Private/InterchangeDatasmithLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeDatasmith, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeDatasmith, Log, All);`

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Private/InterchangeDatasmithMaterialNode.h` (Private)


#### class `UInterchangeDatasmithPbrMaterialNode`  
`class UInterchangeDatasmithPbrMaterialNode : public UInterchangeShaderGraphNode`  
_L21-125_
- reflection: `UCLASS(BlueprintType, Experimental)`
- inherits: `UInterchangeShaderGraphNode`
- L27 _public function_ `UInterchangeDatasmithPbrMaterialNode()`
- L35 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L41 _public function_ `bool GetCustomShadingModel(EMaterialShadingModel& AttributeValue) const`
- L53 _public function_ `bool SetCustomShadingModel(EMaterialShadingModel AttributeValue)`
- L58 _public function_ `bool GetCustomBlendMode(EBlendMode& AttributeValue) const`
- L70 _public function_ `bool SetCustomBlendMode(EBlendMode AttributeValue)`
- L75 _public function_ `bool GetCustomOpacityMaskClipValue(float& AttributeValue) const`
- L80 _public function_ `bool SetCustomOpacityMaskClipValue(float AttributeValue)`
- L85 _public function_ `bool GetCustomTranslucencyLightingMode(ETranslucencyLightingMode& AttributeValue) const`
- L97 _public function_ `bool SetCustomTranslucencyLightingMode(ETranslucencyLightingMode AttributeValue)`
- L102 _public function_ `void GetMaterialFunctionsDependencies(TArray<FString>& MaterialFunctionUids)`
- L107 _public function_ `bool AddMaterialFunctionsDependency(const FString& MaterialFunctionUid)`
- L112 _public function_ `bool RemoveAllMaterialFunctionsDependencies()`
- L118 _private member_ `static const FString ShadingModelAttrName;`
- L119 _private member_ `static const FString BlendModeAttrName;`
- L120 _private member_ `static const FString OpacityMaskClipValueAttrName;`
- L121 _private member_ `static const FString TranslucencyLightingModeAttrName;`
- L122 _private member_ `static const FString MaterialFunctionsDependenciesKey;`
- L124 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> MaterialFunctionsDependencies;`

#### Free symbols / members of external scopes

- L127 _namespace_ `namespace UE`
- L127 _namespace_ `namespace DatasmithInterchange` (scope `UE`)
- L127 _namespace_ `namespace MaterialUtils` (scope `UE::DatasmithInterchange`)
- L129 _externvar_ `extern const FString DefaultOutputIndexAttrName;` (scope `UE::DatasmithInterchange::MaterialUtils`)
- L130 _externvar_ `extern const FString MaterialFunctionPathAttrName;` (scope `UE::DatasmithInterchange::MaterialUtils`)
- L132 _externvar_ `extern const FString MaterialTypeAttrName;` (scope `UE::DatasmithInterchange::MaterialUtils`)
- L133 _externvar_ `extern const FString MaterialQualityAttrName;` (scope `UE::DatasmithInterchange::MaterialUtils`)
- L134 _externvar_ `extern const FString MaterialParentAttrName;` (scope `UE::DatasmithInterchange::MaterialUtils`)
- L136 _prototype_ `void ProcessMaterialElements(TArray<TSharedPtr<IDatasmithBaseMaterialElement>>& InOutMaterialElements);` (scope `UE::DatasmithInterchange::MaterialUtils`)
- L137 _prototype_ `UInterchangeBaseNode* AddMaterialNode(const TSharedPtr<IDatasmithBaseMaterialElement>& MaterialElement, UInterchangeBaseNodeContainer& NodeContainer);` (scope `UE::DatasmithInterchange::MaterialUtils`)

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Private/InterchangeDatasmithMaterialPipeline.h` (Private)


#### class `UInterchangeDatasmithMaterialPipeline`  
`class UInterchangeDatasmithMaterialPipeline : public UInterchangeGenericMaterialPipeline`  
_L23-44_
- reflection: `UCLASS(BlueprintType, Experimental)`
- inherits: `UInterchangeGenericMaterialPipeline`
- L27 _private prototype_ `UInterchangeDatasmithMaterialPipeline();`
- L30 _protected prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath) override;`
- L31 _protected prototype_ `virtual void ExecutePostImportPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L33 _protected function_ `virtual bool CanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask) override`
- L40 _private prototype_ `void PreImportMaterialNode(UInterchangeBaseNodeContainer* NodeContainer, UInterchangeMaterialInstanceNode* MaterialNode);`
- L41 _private prototype_ `void PostImportMaterialInstanceFactoryNode(const UInterchangeBaseNodeContainer* NodeContainer, UInterchangeMaterialInstanceFactoryNode* FactoryNode, UMaterialInterface* CreatedMaterial);`
- L42 _private prototype_ `void UpdateMaterialFactoryNodes(const TArray<UInterchangeShaderNode*>& ShaderNodes);`
- L43 _private prototype_ `void PreImportDecalMaterialNode(UInterchangeBaseNodeContainer* NodeContainer, UInterchangeDecalMaterialNode* MaterialNode);`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeMaterialPipeline, Log, All);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeMaterialPipeline, Log, All);`

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Private/InterchangeDatasmithStaticMeshData.h` (Private)


#### class `UDatasmithInterchangeStaticMeshDataNode`  
`class UDatasmithInterchangeStaticMeshDataNode : public UInterchangeBaseNode`  
_L14-23_
- reflection: `UCLASS()`
- inherits: `UInterchangeBaseNode`
- L22 _public member_ `TMap<FString, TObjectPtr<UDatasmithAdditionalData>> AdditionalDataMap;` — `UPROPERTY()`

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Private/InterchangeDatasmithStaticMeshPipeline.h` (Private)


#### class `UInterchangeDatasmithStaticMeshPipeline`  
`class UInterchangeDatasmithStaticMeshPipeline : public UInterchangeGenericMeshPipeline`  
_L15-32_
- reflection: `UCLASS(BlueprintType, Experimental)`
- inherits: `UInterchangeGenericMeshPipeline`
- L20 _protected prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath) override;`
- L21 _protected prototype_ `virtual void ExecutePostImportPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L23 _protected function_ `virtual bool CanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask) override`
- L30 _private prototype_ `void ApplyMaterials(const UInterchangeBaseNodeContainer* NodeContainer, const UInterchangeStaticMeshFactoryNode* FactoryNode, UStaticMesh* StaticMesh) const;`
- L31 _private prototype_ `void ApplyAdditionalData(const UInterchangeBaseNodeContainer* NodeContainer, const UInterchangeStaticMeshFactoryNode* FactoryNode, UStaticMesh* StaticMesh) const;`

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Private/InterchangeDatasmithTextureData.h` (Private)


#### struct `UE::DatasmithInterchange::FInterchangeDatasmithTextureDataConst`  
`struct FInterchangeDatasmithTextureDataConst`  
_L17-51_
- desc: Helper struct to get/set Datasmith texture attributes on a node.
- L19 _public prototype_ `static bool HasData(const UInterchangeBaseNode* Node);`
- L21 _public prototype_ `FInterchangeDatasmithTextureDataConst(const UInterchangeBaseNode* InNode);`
- L23 _public prototype_ `bool GetCustomFile(FString& AttributeValue) const;`
- L25 _public prototype_ `bool GetCustomTextureMode(EDatasmithTextureMode& AttributeValue) const;`
- L27 _public prototype_ `bool GetCustomTextureFilter(EDatasmithTextureFilter& AttributeValue) const;`
- L29 _public prototype_ `bool GetCustomTextureAddressX(EDatasmithTextureAddress& AttributeValue) const;`
- L31 _public prototype_ `bool GetCustomTextureAddressY(EDatasmithTextureAddress& AttributeValue) const;`
- L33 _public prototype_ `bool GetCustomAllowResize(bool& AttributeValue) const;`
- L35 _public prototype_ `bool GetCustomRGBCurve(float& AttributeValue) const;`
- L37 _public prototype_ `bool GetCustomSRGB(EDatasmithColorSpace& AttributeValue) const;`
- L40 _protected member_ `const UInterchangeBaseNode* ConstBaseNode;`
- L42 _protected member_ `static const FString DatasmithTextureDataKey;`
- L43 _protected member_ `static const FString FileKey;`
- L44 _protected member_ `static const FString TextureModeKey;`
- L45 _protected member_ `static const FString TextureFilterKey;`
- L46 _protected member_ `static const FString TextureAddressXKey;`
- L47 _protected member_ `static const FString TextureAddressYKey;`
- L48 _protected member_ `static const FString AllowResizeKey;`
- L49 _protected member_ `static const FString RGBCurveKey;`
- L50 _protected member_ `static const FString SRGBKey;`

#### struct `UE::DatasmithInterchange::FInterchangeDatasmithTextureData`  
`struct FInterchangeDatasmithTextureData : public FInterchangeDatasmithTextureDataConst`  
_L53-75_
- inherits: `FInterchangeDatasmithTextureDataConst`
- L55 _public prototype_ `FInterchangeDatasmithTextureData(UInterchangeBaseNode* InNode);`
- L57 _public prototype_ `bool SetCustomFile(const FString& AttributeValue);`
- L59 _public prototype_ `bool SetCustomTextureMode(const EDatasmithTextureMode& AttributeValue);`
- L61 _public prototype_ `bool SetCustomTextureFilter(const EDatasmithTextureFilter& AttributeValue);`
- L63 _public prototype_ `bool SetCustomTextureAddressX(const EDatasmithTextureAddress& AttributeValue);`
- L65 _public prototype_ `bool SetCustomTextureAddressY(const EDatasmithTextureAddress& AttributeValue);`
- L67 _public prototype_ `bool SetCustomAllowResize(const bool& AttributeValue);`
- L69 _public prototype_ `bool SetCustomRGBCurve(const float& AttributeValue);`
- L71 _public prototype_ `bool SetCustomSRGB(const EDatasmithColorSpace& AttributeValue);`
- L74 _private member_ `UInterchangeBaseNode* BaseNode;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DatasmithInterchange` (scope `UE`)
- L77 _namespace_ `namespace TextureUtils` (scope `UE::DatasmithInterchange`)
- L82 _prototype_ `void ApplyTextureElementToNode(const TSharedRef<IDatasmithTextureElement>& TextureElement, UInterchangeBaseNode* BaseNode);` (scope `UE::DatasmithInterchange::TextureUtils`) — Register the properties of the TextureElement into the BaseNode's attributes.

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Private/InterchangeDatasmithTranslator.h` (Private)


#### enum `EInterchangeMesherType`  
`enum class EInterchangeMesherType : uint8`  
_L63-68_
- reflection: `UENUM()`
- L65 _public enumerator_ `UseCADKernel UMETA(DisplayName = "Use CADKernel")`
- L66 _public enumerator_ `UseTechSoft`
- L67 _public enumerator_ `UseNativeTessellator`

#### class `UInterchangeDatasmithTranslatorSettings`  
`class UInterchangeDatasmithTranslatorSettings : public UInterchangeTranslatorSettings`  
_L71-78_
- reflection: `UCLASS(BlueprintType, editinlinenew, MinimalAPI)`
- inherits: `UInterchangeTranslatorSettings`
- L77 _public member_ `TObjectPtr<UDatasmithOptionsBase> DatasmithOption;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Datasmith Options")`

#### class `UInterchangeDatasmithTranslator`  
`class UInterchangeDatasmithTranslator : public UInterchangeTranslatorBase , public IInterchangeTexturePayloadInterface , public IInterchangeTextureLightProfilePayloadInterface , public IInterchangeMeshPayloadInterface , public IInterchangeAnimationPayloadInterface , public IInterchangeVariantSetPayloadInterface`  
_L81-174_
- reflection: `UCLASS(BlueprintType, Experimental)`
- inherits: `UInterchangeTranslatorBase,IInterchangeTexturePayloadInterface,IInterchangeTextureLightProfilePayloadInterface,IInterchangeMeshPayloadInterface,IInterchangeAnimationPayloadInterface,IInterchangeVariantSetPayloadInterface`
- L93 _public prototype_ `virtual bool CanImportSourceData(const UInterchangeSourceData* InSourceData) const override;` — Begin UInterchangeTranslatorBase API
- L95 _public prototype_ `virtual bool Translate(UInterchangeBaseNodeContainer& BaseNodeContainer) const override;`
- L97 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`
- L98 _public function_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const override`
- L102 _public function_ `virtual EInterchangeTranslatorType GetTranslatorType() const override`
- L107 _public function_ `virtual void ReleaseSource() override`
- L112 _public prototype_ `virtual void ImportFinish() override;`
- L114 _public prototype_ `virtual UInterchangeTranslatorSettings* GetSettings() const override;`
- L115 _public prototype_ `virtual void SetSettings(const UInterchangeTranslatorSettings* InterchangeTranslatorSettings) override;`
- L119 _public prototype_ `virtual TOptional<UE::Interchange::FImportImage> GetTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;` — IInterchangeTexturePayloadInterface Begin
- L123 _public prototype_ `virtual TOptional<UE::Interchange::FImportLightProfile> GetLightProfilePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;` — IInterchangeTextureLightProfilePayloadInterface Begin
- L128 _public function_ `virtual TOptional<UE::Interchange::FMeshPayloadData> GetMeshPayloadData(const FInterchangeMeshPayLoadKey& PayLoadKey, const FTransform& MeshGlobalTransform) const override` — `UE_DEPRECATED(5.6, "Deprecated. Use GetMeshPayloadData(const FInterchangeMeshPayLoadKey&) instead.")` — IInterchangeStaticMeshPayloadInterface Begin
- L135 _public prototype_ `virtual TOptional<UE::Interchange::FMeshPayloadData> GetMeshPayloadData(const FInterchangeMeshPayLoadKey& PayLoadKey, const UE::Interchange::FAttributeStorage& PayloadAttributes) const override;`
- L139 _public prototype_ `TOptional<UE::Interchange::FAnimationPayloadData> GetAnimationPayloadData(const UE::Interchange::FAnimationPayloadQuery& PayloadQuery) const;` — IInterchangeAnimationPayloadInterface Begin
- L140 _public prototype_ `virtual TArray<UE::Interchange::FAnimationPayloadData> GetAnimationPayloadData(const TArray<UE::Interchange::FAnimationPayloadQuery>& PayloadQueries) const override;`
- L144 _public prototype_ `virtual TOptional<UE::Interchange::FVariantSetPayloadData> GetVariantSetPayloadData(const FString& PayloadKey) const override;` — IInterchangeVariantSetPayloadInterface Begin
- L149 _private prototype_ `void HandleDatasmithActor(UInterchangeBaseNodeContainer& BaseNodeContainer, const TSharedRef<IDatasmithActorElement>& ActorElement, const UInterchangeSceneNode* ParentNode) const;`
- L151 _private prototype_ `UInterchangePhysicalCameraNode* AddCameraNode(UInterchangeBaseNodeContainer& BaseNodeContainer, const TSharedRef<IDatasmithCameraActorElement>& CameraActor) const;`
- L153 _private prototype_ `UInterchangeBaseLightNode* AddLightNode(UInterchangeBaseNodeContainer& BaseNodeContainer, const TSharedRef<IDatasmithLightActorElement>& LightActor) const;`
- L155 _private prototype_ `UInterchangeDecalNode* AddDecalNode(UInterchangeBaseNodeContainer& BaseNodeContainer, const TSharedRef<IDatasmithDecalActorElement>& DecalActor) const;`
- L157 _private prototype_ `void ProcessIesProfile(UInterchangeBaseNodeContainer& BaseNodeContainer, const IDatasmithLightActorElement& LightElement, UInterchangeLightNode* LightNode) const;`
- L159 _private prototype_ `bool GetMeshDescription(const TSharedPtr<IDatasmithMeshElement>& MeshElement, const FTransform& MeshGlobalTransform, UE::Interchange::FMeshPayloadData& PayloadData) const;`
- L161 _private member_ `mutable TSharedPtr<UE::DatasmithImporter::FExternalSource> LoadedExternalSource;`
- L163 _private member_ `mutable uint64 StartTime = 0;`
- L164 _private member_ `mutable FString FileName;`
- L167 _private member_ `mutable TObjectPtr<UInterchangeDatasmithTranslatorSettings> CachedSettings = nullptr;` — `UPROPERTY(Transient, DuplicateTransient)`
- L169 _private member_ `mutable TMap<FString, UE::DatasmithInterchange::AnimUtils::FAnimationPayloadDesc> AnimationPayLoadMapping;`
- L171 _private member_ `static FRWLock StaticMeshDataNodeLock;`
- L172 _private member_ `mutable TObjectPtr<UDatasmithInterchangeStaticMeshDataNode> StaticMeshDataNode;`
- L173 _private member_ `mutable EAsyncExecution AsyncMode = EAsyncExecution::TaskGraph;`

#### Free symbols / members of external scopes

- L43 _namespace_ `namespace UE`
- L43 _namespace_ `namespace Interchange` (scope `UE`)
- L51 _namespace_ `namespace UE`
- L51 _namespace_ `namespace DatasmithImporter` (scope `UE`)
- L56 _namespace_ `namespace UE`
- L56 _namespace_ `namespace DatasmithInterchange` (scope `UE`)
- L56 _namespace_ `namespace AnimUtils` (scope `UE::DatasmithInterchange`)
- L58 _typedef_ `typedef TPair<float, TSharedPtr<IDatasmithBaseAnimationElement>> FAnimationPayloadDesc;` (scope `UE::DatasmithInterchange::AnimUtils`)
- L59 _prototype_ `extern bool GetAnimationPayloadData(const IDatasmithBaseAnimationElement& AnimationElement, float FrameRate, EInterchangeAnimationPayLoadType PayLoadType, UE::Interchange::FAnimationPayloadData& PayLoadData);` (scope `UE::DatasmithInterchange::AnimUtils`)

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Private/InterchangeDatasmithUtils.h` (Private)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Interchange` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace DatasmithInterchange` (scope `UE`)
- L25 _namespace_ `namespace NodeUtils` (scope `UE::DatasmithInterchange`)
- L27 _externvar_ `extern const FString ActorPrefix;` (scope `UE::DatasmithInterchange::NodeUtils`)
- L28 _externvar_ `extern const FString CameraPrefix;` (scope `UE::DatasmithInterchange::NodeUtils`)
- L29 _externvar_ `extern const FString DatasmithScenePrefix;` (scope `UE::DatasmithInterchange::NodeUtils`)
- L30 _externvar_ `extern const FString LevelSequencePrefix;` (scope `UE::DatasmithInterchange::NodeUtils`)
- L31 _externvar_ `extern const FString LevelVariantSetPrefix;` (scope `UE::DatasmithInterchange::NodeUtils`)
- L32 _externvar_ `extern const FString LightPrefix;` (scope `UE::DatasmithInterchange::NodeUtils`)
- L33 _externvar_ `extern const FString DecalPrefix;` (scope `UE::DatasmithInterchange::NodeUtils`)
- L34 _externvar_ `extern const FString DecalMaterialPrefix;` (scope `UE::DatasmithInterchange::NodeUtils`)
- L35 _externvar_ `extern const FString MaterialPrefix;` (scope `UE::DatasmithInterchange::NodeUtils`)
- L36 _externvar_ `extern const FString MaterialExpressionPrefix;` (scope `UE::DatasmithInterchange::NodeUtils`)
- L37 _externvar_ `extern const FString MaterialFunctionPrefix;` (scope `UE::DatasmithInterchange::NodeUtils`)
- L38 _externvar_ `extern const FString MeshPrefix;` (scope `UE::DatasmithInterchange::NodeUtils`)
- L39 _externvar_ `extern const FString ScenePrefix;` (scope `UE::DatasmithInterchange::NodeUtils`)
- L40 _externvar_ `extern const FString TexturePrefix;` (scope `UE::DatasmithInterchange::NodeUtils`)
- L41 _externvar_ `extern const FString VariantSetPrefix;` (scope `UE::DatasmithInterchange::NodeUtils`)
- L43 _prototype_ `extern FString GetActorUid(const TCHAR* Name);` (scope `UE::DatasmithInterchange::NodeUtils`)
- L44 _prototype_ `extern FString GetLevelSequenceUid(const TCHAR* Name);` (scope `UE::DatasmithInterchange::NodeUtils`)
- L45 _prototype_ `extern FString GetLevelVariantSetUid(const TCHAR* Name);` (scope `UE::DatasmithInterchange::NodeUtils`)
- L46 _prototype_ `extern FString GetMaterialUid(const TCHAR* Name);` (scope `UE::DatasmithInterchange::NodeUtils`)
- L47 _prototype_ `extern FString GetVariantSetUid(const TCHAR* Name);` (scope `UE::DatasmithInterchange::NodeUtils`)
- L51 _function_ `template<typename T> TArray<T*> GetNodes(const UInterchangeBaseNodeContainer* BaseNodeContainer)` (scope `UE::DatasmithInterchange::NodeUtils`) — TODO: This is just a quick helper to get the code started, the real solution would be to use caching and pre-parse the NodeContainer to avoid O(n^2) query.
- L61 _function_ `template<class T> T* FindOrAddFactoryNode(const UInterchangeBaseNode* Node, UInterchangeBaseNodeContainer* NodeContainer, const FString& FactoryNodeUid)` (scope `UE::DatasmithInterchange::NodeUtils`)
- L94 _prototype_ `UInterchangeFactoryBaseNode* FindFactoryNodeFromAsset(const UInterchangeBaseNodeContainer* NodeContainer, const UObject* Asset);` (scope `UE::DatasmithInterchange::NodeUtils`)
- L97 _function_ `template<class T = UInterchangeFactoryBaseNode> T* FindFactoryNodeByUniqueID(UInterchangeBaseNodeContainer* NodeContainer, const FString& NodeUniqueID)` (scope `UE::DatasmithInterchange::NodeUtils`)
- L101 _function_ `` (scope `UE::DatasmithInterchange::NodeUtils::FindFactoryNodeByUniqueID`)
- L117 _prototype_ `template<typename DatasmithElementType> int32 GetDatasmithElementsCount(const TSharedRef<IDatasmithScene>& DatasmithScene);` (scope `UE::DatasmithInterchange::NodeUtils`) — no definition, template should be specialized
- L120 _prototype_ `template<typename DatasmithElementType> TSharedPtr<DatasmithElementType> GetDatasmithElement(const TSharedRef<IDatasmithScene>& DatasmithScene, int32 ElementIndex);` (scope `UE::DatasmithInterchange::NodeUtils`) — no definition, template should be specialized
- L123 _function_ `template<typename DatasmithElementType> TSharedPtr<DatasmithElementType> GetDatasmithElementFromIndex(const TSharedRef<IDatasmithScene>& DatasmithScene, int32 ElementIndex)` (scope `UE::DatasmithInterchange::NodeUtils`)
- L134 _function_ `template<typename DatasmithElementType> TSharedPtr<DatasmithElementType> GetDatasmithElementFromPayloadKey(const TSharedRef<IDatasmithScene>& DatasmithScene, const FString& PayloadKey)` (scope `UE::DatasmithInterchange::NodeUtils`)
- L143 _namespace_ `namespace UE`
- L143 _namespace_ `namespace DatasmithInterchange` (scope `UE`)
- L143 _namespace_ `namespace MeshUtils` (scope `UE::DatasmithInterchange`)
- L145 _externvar_ `extern const FString MeshMaterialAttrName;` (scope `UE::DatasmithInterchange::MeshUtils`)
- L148 _namespace_ `namespace UE`
- L148 _namespace_ `namespace DatasmithInterchange` (scope `UE`)
- L148 _namespace_ `namespace AnimUtils` (scope `UE::DatasmithInterchange`)
- L151 _typedef_ `typedef TPair<float, TSharedPtr<IDatasmithBaseAnimationElement>> FAnimationPayloadDesc;` (scope `UE::DatasmithInterchange::AnimUtils`)
- L153 _prototype_ `extern void TranslateLevelSequences(TArray<TSharedPtr<IDatasmithLevelSequenceElement>>& LevelSequences, UInterchangeBaseNodeContainer& InBaseNodeContainer, TMap<FString, UE::DatasmithInterchange::AnimUtils::FAnimationPayloadDesc>& AnimationPayLoadMapping);` (scope `UE::DatasmithInterchange::AnimUtils`)
- L154 _prototype_ `extern bool GetAnimationPayloadData(const IDatasmithBaseAnimationElement& AnimationElement, float FrameRate, UE::Interchange::FAnimationCurvePayloadData& PayLoadData);` (scope `UE::DatasmithInterchange::AnimUtils`)
- L155 _prototype_ `extern bool GetAnimationPayloadData(const IDatasmithBaseAnimationElement& AnimationElement, float FrameRate, UE::Interchange::FAnimationStepCurvePayloadData& PayLoadData);` (scope `UE::DatasmithInterchange::AnimUtils`)
- L158 _namespace_ `namespace UE`
- L158 _namespace_ `namespace DatasmithInterchange` (scope `UE`)
- L158 _namespace_ `namespace VariantSetUtils` (scope `UE::DatasmithInterchange`)
- L161 _prototype_ `extern void TranslateLevelVariantSets(const TArray<TSharedPtr<IDatasmithLevelVariantSetsElement>>& LevelVariantSets, UInterchangeBaseNodeContainer& InBaseNodeContainer);` (scope `UE::DatasmithInterchange::VariantSetUtils`)
- L162 _prototype_ `extern bool GetVariantSetPayloadData(const IDatasmithVariantSetElement& VariantSet, UE::Interchange::FVariantSetPayloadData& PayLoadData);` (scope `UE::DatasmithInterchange::VariantSetUtils`)
- L166 _function_ `template<> inline int32 UE::DatasmithInterchange::NodeUtils::GetDatasmithElementsCount<IDatasmithTextureElement>(const TSharedRef<IDatasmithScene>& DatasmithScene)` (scope `UE::DatasmithInterchange::NodeUtils`)
- L168 _function_ `template<> inline int32 UE::DatasmithInterchange::NodeUtils::GetDatasmithElementsCount<IDatasmithBaseMaterialElement>(const TSharedRef<IDatasmithScene>& DatasmithScene)` (scope `UE::DatasmithInterchange::NodeUtils`)
- L170 _function_ `template<> inline int32 UE::DatasmithInterchange::NodeUtils::GetDatasmithElementsCount<IDatasmithMeshElement>(const TSharedRef<IDatasmithScene>& DatasmithScene)` (scope `UE::DatasmithInterchange::NodeUtils`)
- L173 _function_ `template<> inline TSharedPtr<IDatasmithTextureElement> UE::DatasmithInterchange::NodeUtils::GetDatasmithElement<IDatasmithTextureElement>(const TSharedRef<IDatasmithScene>& DatasmithScene, int32 ElementIndex)` (scope `UE::DatasmithInterchange::NodeUtils`)
- L175 _function_ `template<> inline TSharedPtr<IDatasmithBaseMaterialElement> UE::DatasmithInterchange::NodeUtils::GetDatasmithElement<IDatasmithBaseMaterialElement>(const TSharedRef<IDatasmithScene>& DatasmithScene, int32 ElementIndex)` (scope `UE::DatasmithInterchange::NodeUtils`)
- L177 _function_ `template<> inline TSharedPtr<IDatasmithMeshElement> UE::DatasmithInterchange::NodeUtils::GetDatasmithElement<IDatasmithMeshElement>(const TSharedRef<IDatasmithScene>& DatasmithScene, int32 ElementIndex)` (scope `UE::DatasmithInterchange::NodeUtils`)

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Private/InterchangeReferenceMaterials/DatasmithC4DMaterialSelector.h` (Private)


#### class `UE::DatasmithInterchange::FDatasmithC4DMaterialSelector`  
`class FDatasmithC4DMaterialSelector : public FDatasmithReferenceMaterialSelector`  
_L14-25_
- inherits: `FDatasmithReferenceMaterialSelector`
- L18 _public prototype_ `FDatasmithC4DMaterialSelector();`
- L19 _public prototype_ `virtual ~FDatasmithC4DMaterialSelector() = default;`
- L21 _public prototype_ `virtual const TCHAR* GetMaterialPath(EDatasmithReferenceMaterialType MaterialType) const override;`
- L23 _public prototype_ `virtual void PostImportProcess(EDatasmithReferenceMaterialType MaterialType, EDatasmithReferenceMaterialQuality MaterialQuality, UMaterialInstanceConstant* MaterialInstance) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DatasmithInterchange` (scope `UE`)

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Private/InterchangeReferenceMaterials/DatasmithCityEngineMaterialSelector.h` (Private)


#### class `UE::DatasmithInterchange::FDatasmithCityEngineMaterialSelector`  
`class FDatasmithCityEngineMaterialSelector : public FDatasmithReferenceMaterialSelector`  
_L13-22_
- inherits: `FDatasmithReferenceMaterialSelector`
- L16 _public prototype_ `FDatasmithCityEngineMaterialSelector();`
- L18 _public prototype_ `virtual const TCHAR* GetMaterialPath(EDatasmithReferenceMaterialType MaterialType) const override;`
- L20 _public prototype_ `virtual void PostImportProcess(EDatasmithReferenceMaterialType MaterialType, EDatasmithReferenceMaterialQuality MaterialQuality, UMaterialInstanceConstant* MaterialInstance) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DatasmithInterchange` (scope `UE`)

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Private/InterchangeReferenceMaterials/DatasmithRevitMaterialSelector.h` (Private)


#### class `UE::DatasmithInterchange::FDatasmithRevitMaterialSelector`  
`class FDatasmithRevitMaterialSelector : public FDatasmithReferenceMaterialSelector`  
_L13-23_
- inherits: `FDatasmithReferenceMaterialSelector`
- L16 _public prototype_ `FDatasmithRevitMaterialSelector();`
- L17 _public prototype_ `virtual ~FDatasmithRevitMaterialSelector() = default;`
- L19 _public prototype_ `virtual const TCHAR* GetMaterialPath(EDatasmithReferenceMaterialType MaterialType) const override;`
- L21 _public prototype_ `virtual void PostImportProcess(EDatasmithReferenceMaterialType MaterialType, EDatasmithReferenceMaterialQuality MaterialQuality, UMaterialInstanceConstant* MaterialInstance) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DatasmithInterchange` (scope `UE`)

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Private/InterchangeReferenceMaterials/DatasmithSketchupMaterialSelector.h` (Private)


#### class `UE::DatasmithInterchange::FDatasmithSketchUpMaterialSelector`  
`class FDatasmithSketchUpMaterialSelector : public FDatasmithReferenceMaterialSelector`  
_L11-21_
- inherits: `FDatasmithReferenceMaterialSelector`
- L14 _public prototype_ `FDatasmithSketchUpMaterialSelector();`
- L15 _public prototype_ `virtual ~FDatasmithSketchUpMaterialSelector() = default;`
- L17 _public prototype_ `virtual const TCHAR* GetMaterialPath(EDatasmithReferenceMaterialType MaterialType) const override;`
- L19 _public prototype_ `virtual void PostImportProcess(EDatasmithReferenceMaterialType MaterialType, EDatasmithReferenceMaterialQuality MaterialQuality, UMaterialInstanceConstant* MaterialInstance) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DatasmithInterchange` (scope `UE`)

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Private/InterchangeReferenceMaterials/DatasmithStdMaterialSelector.h` (Private)


#### class `UE::DatasmithInterchange::FDatasmithStdMaterialSelector`  
`class FDatasmithStdMaterialSelector : public FDatasmithReferenceMaterialSelector`  
_L12-19_
- inherits: `FDatasmithReferenceMaterialSelector`
- L15 _public prototype_ `FDatasmithStdMaterialSelector();`
- L16 _public prototype_ `virtual ~FDatasmithStdMaterialSelector() = default;`
- L18 _public prototype_ `virtual const TCHAR* GetMaterialPath(EDatasmithReferenceMaterialType MaterialType) const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DatasmithInterchange` (scope `UE`)

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Public/DatasmithInterchangeModule.h` (Public)


#### class `IDatasmithInterchangeModule`  
`class IDatasmithInterchangeModule : public IModuleInterface`  
_L14-37_
- inherits: `IModuleInterface`
- desc: The public interface of the DatasmithInterchange module
- L23 _public function_ `static inline IDatasmithInterchangeModule& Get()` — Singleton-like access to IDatasmithImporter @return Returns DatasmithImporter singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L9 _macro_ `#define DATASMITHINTERCHANGE_MODULE_NAME TEXT("DatasmithInterchange")`

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Public/InterchangeDatasmithAreaLightFactory.h` (Public)


#### class `UInterchangeDatasmithAreaLightFactory`  
`class UInterchangeDatasmithAreaLightFactory : public UInterchangeActorFactory`  
_L14-35_
- reflection: `UCLASS(BlueprintType, Experimental)`
- inherits: `UInterchangeActorFactory`
- L22 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L31 _protected prototype_ `virtual UObject* ProcessActor(class AActor& SpawnedActor, const UInterchangeActorFactoryNode& FactoryNode, const UInterchangeBaseNodeContainer& NodeContainer, const FImportSceneObjectsParams& Params) override;`

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Public/InterchangeDatasmithAreaLightFactoryNode.h` (Public)


#### class `UInterchangeDatasmithAreaLightFactoryNode`  
`class UInterchangeDatasmithAreaLightFactoryNode : public UInterchangeActorFactoryNode`  
_L14-149_
- reflection: `UCLASS(BlueprintType, Experimental)`
- inherits: `UInterchangeActorFactoryNode`
- L23 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L25 _public prototype_ `virtual UClass* GetObjectClass() const override;`
- L29 _public prototype_ `bool GetCustomLightType(EDatasmithAreaLightActorType& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L32 _public prototype_ `bool SetCustomLightType(const EDatasmithAreaLightActorType& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L35 _public prototype_ `bool GetCustomLightShape(EDatasmithAreaLightActorShape& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L38 _public prototype_ `bool SetCustomLightShape(const EDatasmithAreaLightActorShape& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L41 _public prototype_ `bool GetCustomDimensions(FVector2D& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L44 _public prototype_ `bool SetCustomDimensions(const FVector2D& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L47 _public prototype_ `bool GetCustomIntensity(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L50 _public prototype_ `bool SetCustomIntensity(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L53 _public prototype_ `bool GetCustomIntensityUnits(ELightUnits& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L56 _public prototype_ `bool SetCustomIntensityUnits(const ELightUnits& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L59 _public prototype_ `bool GetCustomColor(FLinearColor& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L62 _public prototype_ `bool SetCustomColor(const FLinearColor& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L65 _public prototype_ `bool GetCustomTemperature(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L68 _public prototype_ `bool SetCustomTemperature(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L74 _public prototype_ `bool GetCustomIESTexture(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")` — Get the NodeUid of the imported IES Texture.
- L80 _public prototype_ `bool SetCustomIESTexture(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")` — Set the NodeUid of the imported IES Texture.
- L83 _public prototype_ `bool GetCustomUseIESBrightness(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L86 _public prototype_ `bool SetCustomUseIESBrightness(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L89 _public prototype_ `bool GetCustomIESBrightnessScale(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L92 _public prototype_ `bool SetCustomIESBrightnessScale(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L95 _public prototype_ `bool GetCustomRotation(FRotator& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L98 _public prototype_ `bool SetCustomRotation(const FRotator& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L101 _public prototype_ `bool GetCustomSourceRadius(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L104 _public prototype_ `bool SetCustomSourceRadius(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L107 _public prototype_ `bool GetCustomSourceLength(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L110 _public prototype_ `bool SetCustomSourceLength(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L113 _public prototype_ `bool GetCustomAttenuationRadius(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L116 _public prototype_ `bool SetCustomAttenuationRadius(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L119 _public prototype_ `bool GetCustomSpotlightInnerAngle(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L122 _public prototype_ `bool SetCustomSpotlightInnerAngle(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L125 _public prototype_ `bool GetCustomSpotlightOuterAngle(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L128 _public prototype_ `bool SetCustomSpotlightOuterAngle(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L130 _public prototype_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override;`
- L133 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomLightTypeKey;`
- L134 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomLightShapeKey;`
- L135 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomDimensionsKey;`
- L136 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomIntensityKey;`
- L137 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomIntensityUnitsKey;`
- L138 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomColorKey;`
- L139 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomTemperatureKey;`
- L140 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomIESTextureKey;`
- L141 _private member_ `static UE::Interchange::FAttributeKey Macro_CustombUseIESBrightnessKey;`
- L142 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomIESBrightnessScaleKey;`
- L143 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomRotationKey;`
- L144 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomSourceRadiusKey;`
- L145 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomSourceLengthKey;`
- L146 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomAttenuationRadiusKey;`
- L147 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomSpotlightInnerAngleKey;`
- L148 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomSpotlightOuterAngleKey;`

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Public/InterchangeDatasmithAreaLightNode.h` (Public)


#### class `UInterchangeDatasmithAreaLightNode`  
`class UInterchangeDatasmithAreaLightNode : public UInterchangeLightNode`  
_L20-91_
- reflection: `UCLASS(BlueprintType, Experimental)`
- inherits: `UInterchangeLightNode`
- L28 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L35 _public prototype_ `bool GetCustomLightType(EDatasmithAreaLightActorType& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L38 _public prototype_ `bool SetCustomLightType(const EDatasmithAreaLightActorType& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L41 _public prototype_ `bool GetCustomLightShape(EDatasmithAreaLightActorShape& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L44 _public prototype_ `bool SetCustomLightShape(const EDatasmithAreaLightActorShape& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L47 _public prototype_ `bool GetCustomDimensions(FVector2D& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L50 _public prototype_ `bool SetCustomDimensions(const FVector2D& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L53 _public prototype_ `bool GetCustomColor(FLinearColor& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L56 _public prototype_ `bool SetCustomColor(const FLinearColor& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L59 _public prototype_ `bool GetCustomSourceRadius(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L62 _public prototype_ `bool SetCustomSourceRadius(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L65 _public prototype_ `bool GetCustomSourceLength(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L68 _public prototype_ `bool SetCustomSourceLength(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L71 _public prototype_ `bool GetCustomSpotlightInnerAngle(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L74 _public prototype_ `bool SetCustomSpotlightInnerAngle(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L77 _public prototype_ `bool GetCustomSpotlightOuterAngle(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L80 _public prototype_ `bool SetCustomSpotlightOuterAngle(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Datasmith")`
- L83 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomLightTypeKey;`
- L84 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomLightShapeKey;`
- L85 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomDimensionsKey;`
- L86 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomColorKey;`
- L87 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomSourceRadiusKey;`
- L88 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomSourceLengthKey;`
- L89 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomSpotlightInnerAngleKey;`
- L90 _private member_ `static UE::Interchange::FAttributeKey Macro_CustomSpotlightOuterAngleKey;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Public/InterchangeDatasmithPipeline.h` (Public)


#### class `UInterchangeDatasmithPipeline`  
`class UInterchangeDatasmithPipeline : public UInterchangePipelineBase`  
_L27-75_
- reflection: `UCLASS(BlueprintType, Experimental)`
- inherits: `UInterchangePipelineBase`
- L31 _private prototype_ `UInterchangeDatasmithPipeline();`
- L34 _private member_ `TObjectPtr<UInterchangeDatasmithMaterialPipeline> MaterialPipeline;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = "Materials")`
- L37 _private member_ `TObjectPtr<UInterchangeDatasmithStaticMeshPipeline> MeshPipeline;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = "Mesh")`
- L40 _private member_ `TObjectPtr<UInterchangeDatasmithLevelPipeline> LevelPipeline;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = "Level")`
- L43 _private member_ `TObjectPtr<UInterchangeGenericAnimationPipeline> AnimationPipeline;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = "Animation")`
- L46 _private member_ `TObjectPtr<UInterchangeGenericCommonMeshesProperties> CommonMeshesProperties;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = "Common Meshes")`
- L49 _private member_ `TObjectPtr<UInterchangeGenericCommonSkeletalMeshesAndAnimationsProperties> CommonSkeletalMeshesAndAnimationsProperties;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = "Common Skeletal Meshes and Animations")`
- L53 _private member_ `bool bDeleteInvalidMeshes = true;` — `UPROPERTY(EditAnywhere, Category = "Mesh")`
- L57 _private member_ `bool bCreateMaterialReferencesFolders = true;` — `UPROPERTY(EditAnywhere, Category = "Materials")`
- L60 _protected prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* InBaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath) override;`
- L61 _protected prototype_ `virtual void ExecutePostImportPipeline(const UInterchangeBaseNodeContainer* InBaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L62 _protected prototype_ `virtual void AdjustSettingsForContext(const FInterchangePipelineContextParams& ContextParams) override;`
- L64 _protected function_ `virtual bool CanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask) override`
- L71 _private prototype_ `void PreImportTextureFactoryNode(UInterchangeTextureFactoryNode* TextureFactoryNode) const;`
- L74 _private member_ `UInterchangeBaseNodeContainer* BaseNodeContainer = nullptr;`

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Public/InterchangeReferenceMaterials/DatasmithReferenceMaterialManager.h` (Public)


#### class `UE::DatasmithInterchange::FDatasmithReferenceMaterialManager`  
`class FDatasmithReferenceMaterialManager`  
_L14-32_
- L17 _public prototype_ `static void Create();`
- L18 _public prototype_ `static void Destroy();`
- L19 _public prototype_ `static FDatasmithReferenceMaterialManager& Get();`
- L21 _public prototype_ `FString GetHostFromString(const FString& HostString);`
- L23 _public prototype_ `void RegisterSelector(const TCHAR* Host, TSharedPtr< FDatasmithReferenceMaterialSelector > Selector);`
- L24 _public prototype_ `void UnregisterSelector(const TCHAR* Host);`
- L26 _public prototype_ `const TSharedPtr< FDatasmithReferenceMaterialSelector > GetSelector(const TCHAR* Host) const;`
- L29 _private member_ `static TUniquePtr< FDatasmithReferenceMaterialManager > Instance;`
- L31 _private member_ `TMap< FString, TSharedPtr< FDatasmithReferenceMaterialSelector > > Selectors;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DatasmithInterchange` (scope `UE`)

### `Plugins/Experimental/Enterprise/DatasmithInterchange/Source/DatasmithInterchange/Public/InterchangeReferenceMaterials/DatasmithReferenceMaterialSelector.h` (Public)


#### class `UE::DatasmithInterchange::FDatasmithReferenceMaterialSelector`  
`class FDatasmithReferenceMaterialSelector`  
_L14-27_
- L17 _public prototype_ `virtual ~FDatasmithReferenceMaterialSelector() = default;`
- L19 _public function_ `virtual bool IsValid() const`
- L20 _public function_ `virtual const TCHAR* GetMaterialPath(EDatasmithReferenceMaterialType MaterialType) const`
- L22 _public function_ `virtual void PostImportProcess(EDatasmithReferenceMaterialType MaterialType, EDatasmithReferenceMaterialQuality MaterialQuality, UMaterialInstanceConstant* MaterialInstance) const`
- L26 _protected member_ `bool bIsValid = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DatasmithInterchange` (scope `UE`)
