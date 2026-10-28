# Plugins / InterchangeOpenUSDImport

- module root: `Plugins/Interchange/Extensions/OpenUSD/Source/Import`
- headers: 29; symbols: 480
- symbol kinds: class=27, enum=1, enumerator=2, function=6, macro=24, member=76, namespace=99, prototype=239, struct=3, typedef=3
- PrivateDependencyModuleNames: DynamicMesh, GeometryCore, HairStrandsCore, InterchangeEngine, InterchangeFactoryNodes, InterchangeNodes, InterchangeOpenVDBImport, InterchangePipelines, MaterialX, MeshConversion, MeshDescription, ModelingComponents, StaticMeshDescription, TextureUtilitiesCommon, USDClasses
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InterchangeCommon, InterchangeCommonParser, InterchangeCore, InterchangeImport, USDUtilities, UnrealUSDWrapper

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/InterchangeOpenUSDImportModule.h` (Public)


#### class `FInterchangeOpenUSDImportModule`  
`class FInterchangeOpenUSDImportModule : public IModuleInterface`  
_L13-25_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `int32 GetNumDefaultHandlers() const;`
- L23 _private member_ `TArray<FString> RegisteredHandlers;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Interchange` (scope `UE`)
- L8 _namespace_ `namespace USD` (scope `UE::Interchange`)
- L10 _typedef_ `using FSchemaHandlerIdentifier = int32;` (scope `UE::Interchange::USD`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/InterchangeUSDInfoCache.h` (Public)


#### class `FInterchangeUsdInfoCache`  
`class FInterchangeUsdInfoCache`  
_L27-51_
- desc: Caches information about a specific USD Stage relevant for an Interchange import
- L30 _public prototype_ `FInterchangeUsdInfoCache();`
- L31 _public prototype_ `virtual ~FInterchangeUsdInfoCache();`
- L34 _public prototype_ `bool ContainsInfoAboutPrim(const UE::FSdfPath& Path) const;` — Returns whether we contain any info about prim at 'Path' at all
- L36 _public prototype_ `void Build(UInterchangeUsdContext& Context);`
- L38 _public prototype_ `void Clear();`
- L39 _public prototype_ `bool IsEmpty();`
- L42 _public prototype_ `bool IsPathCollapsed(const UE::FSdfPath& Path) const;`
- L43 _public prototype_ `bool DoesPathCollapseChildren(const UE::FSdfPath& Path) const;`
- L47 _public prototype_ `UE::FSdfPath UnwindToNonCollapsedPath(const UE::FSdfPath& Path) const;` — Returns Path in case it represents an uncollapsed prim, or returns the path to the prim that collapsed it. i.e. this always returns the root of the collapsed subtree that Path is involved in, if any.
- L50 _private member_ `TPimplPtr<UE::UsdInfoCache::Private::FInterchangeUsdInfoCacheImpl> Impl;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L13 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UsdInfoCache` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::UsdInfoCache`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/InterchangeUSDPipeline.h` (Public)


#### class `UInterchangeUsdPipeline`  
`class UInterchangeUsdPipeline : public UInterchangePipelineBase`  
_L14-76_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UInterchangePipelineBase`
- L18 _private prototype_ `UInterchangeUsdPipeline();`
- L27 _public member_ `FString PipelineDisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common", meta = (StandAlonePipelineProperty = "True", PipelineInternalEditionData = "True"))`
- L32 _public member_ `int32 GeometryPurpose;` — `UE_DEPRECATED(5.8, "This option has moved back to the USD translator settings")` — `UPROPERTY(meta = (Bitmask, BitmaskEnum = "/Script/UnrealUSDWrapper.EUsdPurpose"))` — Only import translated nodes from imageable prims (Xforms, Meshes, etc.) with these specific purposes from the USD file
- L36 _public member_ `EInterchangeUsdPrimvar ImportPrimvars = EInterchangeUsdPrimvar::Bake;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")` — Setting to tell what primvars have to be attached to the MeshDescription
- L43 _public member_ `int32 SubdivisionLevel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD", meta = (ClampMin = "0", ClampMax = "6", UIMin = "0", UIMax = "6"))` — Subdivision level to use for all subdivision meshes on the opened stage. 0 means "don't subdivide". The maximum level of subdivision allowed can be configured via the 'USD.Subdiv.MaxSubdivLevel' cvar.
- L50 _public member_ `bool bImportPseudoRoot;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")` — The translator always emits a scene node for the stage pseudoroot named after the stage's root layer filename. Setting this option to false means we will remove it from the factory nodes, making top-level prims lead to top-level actors and components.
- L60 _public member_ `bool bGeneratePrimvarCompatibleMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")` — Imported meshes will place their primvars on arbitrary UV set indices (e.g. "st2" on UV0, "st3" on UV1, etc.). Imported materials may be expecting to read from specific primvars on particular UV indices (e.g. "st1" from UV0, "st2" from UV2, etc.). These mappings won't necessarily correspond to each other. Setting this option to true means we'll generate additional material instances with primvar-UV index mappings made to best match the exact meshes they are assigned to (e.g. "st1" disabled, "st2" from UV0). Setting this to false means we will just assign the incompatible materials to the meshes anyway.
- L64 _public prototype_ `virtual void ExecutePostFactoryPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L66 _public prototype_ `virtual void AdjustSettingsForContext(const FInterchangePipelineContextParams& ContextParams) override;`
- L69 _protected prototype_ `virtual void ExecutePipeline( UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath ) override;`
- L75 _protected prototype_ `virtual bool CanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask) override;`

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/InterchangeUsdContext.h` (Public)


#### class `UInterchangeUsdContext`  
`class UInterchangeUsdContext : public UObject`  
_L31-168_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L36 _public prototype_ `UInterchangeUsdContext();`
- L37 _public prototype_ `virtual void BeginDestroy() override;`
- L39 _public prototype_ `void Initialize(UInterchangeUSDTranslator* Translator, UInterchangeBaseNodeContainer* NodeContainer);`
- L48 _public prototype_ `virtual FString MakeAssetNodeUid(const UE::FUsdPrim& Prim, const FString& Prefix = FString(), const FString& Suffix = FString()) const;` — Generates a UID for an asset node (mesh, material, texture, light, etc.) associated with a prim. Schema handlers should call this instead of directly building UIDs via MakeNodeUid(). By default produces MakeNodeUid(Prefix + GetPrototypePrimPath(Prim) + Suffix). Subclasses can override to produce remapped UIDs (e.g. for pregen target-based deduplication).
- L57 _public prototype_ `virtual FString MakeSceneNodeUid(const UE::FUsdPrim& Prim, const FString& Prefix = FString(), const FString& Suffix = FString()) const;` — Generates a UID for a scene node (actor/component) associated with a prim. Schema handlers should call this instead of directly building UIDs via MakeNodeUid(). By default produces MakeNodeUid(Prim.GetPrimPath() + Suffix). Scene nodes are per-instance (not deduplicated), so this uses the prim's own path.
- L61 _public prototype_ `int64 GetStageId() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | USD")` — Returns the ID the provided stage has within the USDUtils' singleton StageCache.
- L66 _public prototype_ `void SetStageId(int64 InStageId);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | USD")` — Sets the ID of a particular stage from the UsdUtils' singleton StageCache. If this corresponds to a valid USD Stage, that stage will be used for the Interchange import.
- L70 _public prototype_ `UE::FUsdStage GetUsdStage() const;` — Convenience functions to get/set the stage directly, although it will internally just get/set the stage into the UsdUtils' singleton StageCache and track it's Id instead.
- L71 _public prototype_ `bool SetUsdStage(const UE::FUsdStage& InStage);`
- L74 _public prototype_ `FUsdInfoCache* GetInfoCache() const;` — `UE_DEPRECATED(5.8, "Use the SetupInterchangeInfoCache() and GetInterchangeInfoCache() functions instead")`
- L77 _public prototype_ `void SetExternalInfoCache(FUsdInfoCache& InInfoCache);` — `UE_DEPRECATED(5.8, "Use the SetupInterchangeInfoCache() and GetInterchangeInfoCache() functions instead")`
- L80 _public prototype_ `FUsdInfoCache* CreateOwnedInfoCache();` — `UE_DEPRECATED(5.8, "Use the SetupInterchangeInfoCache() and GetInterchangeInfoCache() functions instead")`
- L83 _public prototype_ `void BuildInfoCache();` — `UE_DEPRECATED(5.8, "Use the SetupInterchangeInfoCache() and GetInterchangeInfoCache() functions instead")`
- L86 _public prototype_ `void ReleaseInfoCache();` — `UE_DEPRECATED(5.8, "Use the SetupInterchangeInfoCache() and GetInterchangeInfoCache() functions instead")`
- L88 _public prototype_ `void Reset();`
- L90 _public prototype_ `void SetupTrackSetNode();`
- L92 _public prototype_ `void SetupInterchangeInfoCache();`
- L94 _public prototype_ `UInterchangeUSDTranslator* GetTranslator() const;`
- L95 _public prototype_ `UInterchangeUsdTranslatorSettings* GetTranslatorSettings() const;`
- L96 _public prototype_ `UInterchangeResultsContainer* GetResultsContainer() const;`
- L97 _public prototype_ `UInterchangeBaseNodeContainer* GetNodeContainer() const;`
- L99 _public prototype_ `FInterchangeUsdInfoCache* GetInterchangeInfoCache() const;`
- L103 _private prototype_ `void SetupMeshConversionOptions();`
- L109 _public member_ `TMap<FString, TStrongObjectPtr<UInterchangeTranslatorBase>> SubTranslators;` — Unique identifier to other translators that we spawn in the process of translating the file and producing payloads, in order to handle other format types (MaterialX, OpenVDB, etc.)
- L114 _public member_ `TObjectPtr<UInterchangeAnimationTrackSetNode> CurrentTrackSet = nullptr;` — This node eventually becomes a LevelSequence, and all track nodes are connected to it. For now we only generate a single LevelSequence per stage though, so we'll keep track of this here for easy access when parsing tracks
- L120 _public member_ `TMap<FString, UE::Interchange::USD::FTraversalInfo> NodeUidToCachedTraversalInfo;` — When traversing we'll generate FTraversalInfo objects. If we need to (e.g. for skinned meshes), we'll store the info for that translated node here, so we don't have to recompute it when returning the payload data. Note: We only do this when needed: This shouldn't have data for every prim in the stage.
- L121 _public member_ `mutable FRWLock NodeUidToCachedTraversalInfoLock;`
- L125 _public member_ `mutable FRWLock PrimPathToVariantToStageLock;` — We store temp stages in here that we open in order to parse stuff inside of inactive variants of our main UsdStage. We do this because the payload data are retrieved concurrently, and toggling variants mutates the current stage.
- L126 _public member_ `TMap<FString, TMap<FString, UE::FUsdStage>> PrimPathToVariantToStage;`
- L130 _public member_ `UsdToUnreal::FUsdMeshConversionOptions CachedMeshConversionOptions;` — On UInterchangeUSDTranslator::Translate we set this up based on our TranslatorSettings, and then we can reuse it (otherwise we have to keep converting the FNames into Tokens all the time)
- L132 _public member_ `TMap<FString, UsdUtils::FUsdPrimMaterialAssignmentInfo> CachedMaterialAssignments;`
- L134 _public member_ `FString USDZFilePath;`
- L135 _public member_ `FString DecompressedUSDZRoot;`
- L141 _public member_ `TMap<FString, TArray<FUsdMaterialXShaderGraph::FGeomProp>> MaterialUidToGeomProps;` — Additional information extracted from MaterialX materials. We stash these here because we need both materials and meshes to process the geomprop into primvars properly, but we may run into the Materials first during parsing. TODO: Maybe remove and use info cache?
- L148 _public member_ `TMap<UE::FSdfPath, UE::Interchange::USD::FHandlerAccumulatedInfo> HandledPrimInfo;` — The regular UsdTranslator traversal will not translate prims whose paths are in this map. The UsdTranslator will also automatically mark prims as visited during its regular traversal. This can be use to prevent the regular traversal from visiting prims that a schema handler for a parent prim may have already processed
- L155 _public member_ `TArray<UE::FSdfPath> ParsedPrimsToImport;` — Parsed view of UInterchangeUsdTranslatorSettings::PrimsToImport, populated at the top of UInterchangeUSDTranslator::Translate(). The translator's TranslatePrimSubtree consults this to skip out-of-scope subtrees, and schema handlers driving traversal directly may want to honor it as well. Empty means "no filter" (the fast path); the full-stage default of {"/"} also resolves to empty here.
- L158 _private member_ `TObjectPtr<UInterchangeUSDTranslator> Translator;`
- L159 _private member_ `TObjectPtr<UInterchangeBaseNodeContainer> NodeContainer;`
- L163 _private member_ `int64 StageIdInUsdUtilsStageCache = INDEX_NONE;` — We never store the stage itself, but only it's Id within the UsdUtils' singleton StageCache. The intent here is to allow Python stages to be passed in and manipulated via Python in case of Python imports or pipelines.
- L164 _private member_ `bool bShouldCleanUpFromStageCache = false;`
- L166 _private member_ `TUniquePtr<FInterchangeUsdInfoCache> InfoCache;`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Interchange` (scope `UE`)
- L25 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/InterchangeUsdTranslator.h` (Public)


#### enum `EUsdPointInstancerCollapsing`  
`enum class EUsdPointInstancerCollapsing : uint8`  
_L52-59_
- reflection: `UENUM(BlueprintType)`
- desc: Describes what to do when we're collapsing and encounter a PointInstancer prim in a prim subtree
- L55 _public enumerator_ `NoCollapsing` — Prevent collapsing the subtree the PointInstancer occupies
- L58 _public enumerator_ `CollapseAsStaticMesh` — Collapse the point instancer along with the rest of the subtree, baking its instances into the produced StaticMesh

#### class `UInterchangeUsdTranslatorSettings`  
`class UInterchangeUsdTranslatorSettings : public UInterchangeTranslatorSettings`  
_L62-169_
- reflection: `UCLASS(BlueprintType, editinlinenew, MinimalAPI)`
- inherits: `UInterchangeTranslatorSettings`
- L69 _public member_ `int32 GeometryPurpose;` — `UPROPERTY(EditAnywhere, Category = "USD Translator", meta = (Bitmask, BitmaskEnum = "/Script/UnrealUSDWrapper.EUsdPurpose"))` — Only import geometry prims with these specific purposes from the USD file
- L74 _public member_ `FName RenderContext;` — `UE_DEPRECATED(5.6, "This is no longer used: Reorder and enable/disable the registered material schema handlers to control what render contexts are parsed (see the CustomHandlerEntries property).")` — `UPROPERTY()` — Specifies which set of shaders to use when parsing USD materials, in addition to the universal render context.
- L78 _public member_ `FName MaterialPurpose;` — `UPROPERTY(EditAnywhere, Category = "USD Translator")` — Specifies which material purpose to use when parsing USD material bindings, in addition to the "allPurpose" fallback
- L82 _public member_ `EUsdInterpolationType InterpolationType;` — `UPROPERTY(EditAnywhere, Category = "USD Translator")` — Describes how to interpolate between a timeSample value and the next
- L86 _public member_ `bool bOverrideStageOptions;` — `UPROPERTY(EditAnywhere, Category = "USD Translator")` — Whether to use the specified StageOptions instead of the stage's own settings
- L90 _public member_ `FUsdStageOptions StageOptions;` — `UPROPERTY(EditAnywhere, Category = "USD Translator", meta = (EditCondition = bOverrideStageOptions))` — Custom StageOptions to use for the stage
- L94 _public member_ `EUsdPointInstancerCollapsing PointInstancerCollapsing;` — `UPROPERTY(EditAnywhere, Category = "USD Translator|Collapsing")` — How the USD Translator should behave when it tries collapsing a subtree and encounters a PointInstancer prim
- L100 _public member_ `bool bUseSchemaForCollapsing;` — `UPROPERTY(EditAnywhere, Category = "USD Translator|Collapsing")` — Whether to use the dedicated collapsing schema to collapse prim subtrees into single meshes
- L107 _public member_ `bool bUsePrimKindsForCollapsing;` — `UPROPERTY(EditAnywhere, Category = "USD Translator|Collapsing")` — Use KindsToCollapse to determine when to collapse prim subtrees or not (defaults to disabled on Interchange). Disable this if you want to prevent collapsing, or to control it manually by right-clicking on individual prims.
- L114 _public member_ `int32 KindsToCollapse;` — `UPROPERTY(EditAnywhere, Category = "USD Translator|Collapsing", meta = (Bitmask, BitmaskEnum = "/Script/UnrealUSDWrapper.EUsdDefaultKind", EditCondition = bUsePrimKindsForCollapsing))` — Which prim kinds that are allowed to collapse its children and/or be collapsed. See also the "USD.CollapsePrimsWithoutKind" cvar.
- L123 _public member_ `bool bTranslatePrimAttributes;` — `UPROPERTY(EditAnywhere, Category = "USD Translator")` — Whether to convert USD prim default attribute opinions (i.e. non-animated) into translated node user attributes, ultimately ending up imported as asset and actor metadata. Note that AttributeRegexFilter may be needed in order to select only the desired metadata, as otherwise regular attributes like 'points' and 'faceVertexCounts' will also get translated into Interchange metadata, which could be expensive.
- L127 _public member_ `FString AttributeRegexFilter;` — `UPROPERTY(EditAnywhere, Category = "USD Translator", meta = (EditCondition = bTranslatePrimAttributes))` — Regex to match against USD prim attribute names to decide whether to convert them into translated node user attributes
- L131 _public member_ `bool bTranslatePrimMetadata;` — `UPROPERTY(EditAnywhere, Category = "USD Translator")` — Whether to convert USD prim metadata into translated node user attributes, if they pass the regex filter. See MetadataRegexFilter.
- L141 _public member_ `FString MetadataRegexFilter;` — `UPROPERTY(EditAnywhere, Category = "USD Translator", meta = (EditCondition = bTranslatePrimMetadata))` — Regex to match against the full USD prim metadata key to decide whether to convert them into translated node user attributes. Note that nested dictionaries are flattened using the ":" character as separator. So a myMetadata key inside the customData dictionary will end up with the full key 'customData:myMetadata', and could be selected by a regex filter 'customData:my', or just 'custom', or 'my', etc.
- L165 _public member_ `TArray<FSchemaHandlerEntry> CustomHandlerEntries;` — `UPROPERTY(EditAnywhere, Category = "USD Translator|Handlers", AdvancedDisplay)` — Custom array of schema handlers to use for translation. When this is empty, the default FSchemaHandlerRegistry::RegisteredHandlerEntries array will be used instead. It is expected for this array to essentially be a reorder of FSchemaHandlerRegistry::RegisteredHandlerEntries, with additionally some modified property values on schema handler entries, if needed (e.g. enabled or custom render contexts). It is not sufficient to create a new FSchemaHandlerEntry instance from scratch and insert here directly: If you have a custom handler, you want to register it on FSchemaHandlerRegistry instead, so as to also get the handler generator function correctly registered. At that point, your handler will also be added to FSchemaHandlerRegistry::RegisteredHandlerEntries.
- L168 _public prototype_ `UInterchangeUsdTranslatorSettings();`

#### class `UInterchangeUSDTranslator`  
`class UInterchangeUSDTranslator : public UInterchangeTranslatorBase , public IInterchangeMeshPayloadInterface , public IInterchangeTexturePayloadInterface , public IInterchangeBlockedTexturePayloadInterface , public IInterchangeAnimationPayloadInterface , public IInterchangeVolumePayloadInterface , public IInterchangeGroomPayloadInterface , public IInterchangeAudioPayloadInterface , public IInterchangeGenericPayloadInterface`  
_L172-263_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UInterchangeTranslatorBase,IInterchangeMeshPayloadInterface,IInterchangeTexturePayloadInterface,IInterchangeBlockedTexturePayloadInterface,IInterchangeAnimationPayloadInterface,IInterchangeVolumePayloadInterface,IInterchangeGroomPayloadInterface,IInterchangeAudioPayloadInterface,IInterchangeGenericPayloadInterface`
- L186 _public prototype_ `UInterchangeUSDTranslator();`
- L189 _public prototype_ `virtual EInterchangeTranslatorType GetTranslatorType() const override;` — Begin UInterchangeTranslatorBase API
- L190 _public prototype_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const override;`
- L191 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`
- L192 _public prototype_ `virtual bool Translate(UInterchangeBaseNodeContainer& BaseNodeContainer) const override;`
- L193 _public prototype_ `virtual void ReleaseSource() override;`
- L194 _public prototype_ `virtual void ImportFinish() override;`
- L195 _public prototype_ `virtual UInterchangeTranslatorSettings* GetSettings() const override;`
- L196 _public prototype_ `virtual void SetSettings(const UInterchangeTranslatorSettings* InterchangeTranslatorSettings) override;`
- L207 _public prototype_ `virtual TOptional<UE::Interchange::USD::FHandlerAccumulatedInfo> TranslatePrim( const UE::FUsdPrim& Prim, UE::Interchange::USD::FTraversalInfo& TraversalInfo, bool bAllowSceneNodeGeneration = true ) const;` — Invokes all registered handlers on Prim, producing Interchange translated nodes and adding them to our UsdContext's NodeContainer. The accumulated products from all those handlers is returned as FHandlerAccumulatedInfo, if translation succeeded. This will also mark the Prim as visited on the UsdContext's HandledPrimInfo member, caching the produced FHandlerAccumulatedInfo. Repeated calls for the same prim will just return that cached info instead.
- L223 _public prototype_ `virtual void TranslatePrimSubtree(const UE::FUsdPrim& Prim, const UE::Interchange::USD::FTraversalInfo& TraversalInfo, bool bAllowSceneNodeGeneration = true, UE::Interchange::USD::FHandlerAccumulatedInfo* SubTreeAccumulatedInfo = nullptr) const;` — Recursively traverses their Prim and its children, invoking TranslatePrim(). Traversal will not step into prims if they are already on the UsdContext's HandledPrimInfo member. In general, the regular Translate() implementation will traverse the full stage, recursively calling this function. This is exposed here however in case your schema handler needs to take charge of the stage traversal for whatever reason. You can then choose to process the prims you wish, and then yield back control of the rest of the subtree traversal to the UInterchangeUSDTranslator by calling this function for that subtree.
- L229 _public prototype_ `virtual const TArray<TSharedRef<UE::Interchange::USD::FSchemaHandler>>& GetCurrentSchemaHandlers() const;` — Returns the schema handlers that are currently being used by the translator. These are created during the Translate() call, and released when the import is complete.
- L234 _public function_ `virtual TOptional<UE::Interchange::FMeshPayloadData> GetMeshPayloadData( const FInterchangeMeshPayLoadKey& PayLoadKey, const FTransform& MeshGlobalTransform ) const override` — `UE_DEPRECATED(5.6, "Deprecated. Use GetMeshPayloadData(const FInterchangeMeshPayLoadKey&) instead.")` — Begin Interchange payload interfaces
- L245 _public prototype_ `virtual TOptional<UE::Interchange::FMeshPayloadData> GetMeshPayloadData(const FInterchangeMeshPayLoadKey& PayLoadKey, const UE::Interchange::FAttributeStorage& PayloadAttributes) const override;`
- L246 _public prototype_ `virtual TOptional<UE::Interchange::FImportImage> GetTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;`
- L247 _public prototype_ `virtual TOptional<UE::Interchange::FImportBlockedImage> GetBlockedTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;`
- L248 _public prototype_ `virtual TArray<UE::Interchange::FAnimationPayloadData> GetAnimationPayloadData(const TArray<UE::Interchange::FAnimationPayloadQuery>& PayloadQueries) const override;`
- L249 _public prototype_ `virtual TOptional<UE::Interchange::FVolumePayloadData> GetVolumePayloadData(const UE::Interchange::FVolumePayloadKey& PayloadKey) const override;`
- L250 _public prototype_ `virtual TOptional<UE::Interchange::FGroomPayloadData> GetGroomPayloadData(const FInterchangeGroomPayloadKey& PayloadKey) const override;`
- L251 _public prototype_ `virtual TOptional<UE::Interchange::FInterchangeAudioPayloadData> GetAudioPayloadData(const FString& PayloadSourceFileKey) const override;`
- L252 _public prototype_ `virtual TObjectPtr<UInterchangeGenericPayloadData> GetGenericPayloadData(const FString& PayloadKey) const override;`
- L256 _private member_ `mutable TUniquePtr<UE::InterchangeUsdTranslator::Private::UInterchangeUSDTranslatorImpl> Impl;`
- L259 _private member_ `mutable TObjectPtr<UInterchangeUsdTranslatorSettings> TranslatorSettings = nullptr;` — `UPROPERTY(Transient, DuplicateTransient)`
- L262 _private member_ `mutable TObjectPtr<UInterchangeUsdContext> UsdContext = nullptr;` — `UPROPERTY(Transient, DuplicateTransient)`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace InterchangeUsdTranslator` (scope `UE`)
- L31 _namespace_ `namespace Private` (scope `UE::InterchangeUsdTranslator`)
- L35 _namespace_ `namespace UE`
- L38 _namespace_ `namespace Interchange` (scope `UE`)
- L42 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/InterchangeUsdTraversalInfo.h` (Public)


#### struct `UE::Interchange::USD::FTraversalInfo`  
`struct FTraversalInfo`  
_L30-60_
- desc: Information intended to be passed down from parent to children (by value) as we traverse the stage
- L32 _public typedef_ `using FNaniteAssemblyTraversalResult = UsdToUnreal::NaniteAssemblyUtils::FNaniteAssemblyTraversalResult;`
- L34 _public member_ `UInterchangeBaseNode* ParentNode = nullptr;`
- L36 _public member_ `FTransform SceneGlobalTransform;`
- L39 _public member_ `bool bCurrentlyCollapsing = false;` — Whether we're already collapsing a subtree or not (used to prevent us from creating nested mesh bundles)
- L41 _public member_ `TSharedPtr<UE::FUsdSkelCache> FurthestSkelCache;`
- L42 _public member_ `TSharedPtr<FString> FurthestParentSkelRootPath;` — Used to populate the skel cache
- L43 _public member_ `TSharedPtr<FString> ClosestParentSkelRootPath;`
- L44 _public member_ `TSharedPtr<FString> BoundSkeletonPrimPath;`
- L45 _public member_ `TSharedPtr<TArray<FString>> SkelJointUsdNames;` — Needed for skel mesh payloads
- L48 _public member_ `TSharedPtr<FString> ClosestNaniteAssemblySkelBindingPath;` — Nanite Assembly info
- L49 _public member_ `TSharedPtr<const FNaniteAssemblyTraversalResult> NaniteAssemblyTraversalResult;`
- L51 _public member_ `bool bVisible = true;`
- L52 _public member_ `bool bInsideLODVariant = false;`
- L53 _public member_ `bool bIsLODVariantContainer = false;`
- L56 _public prototype_ `void UpdateWithCurrentPrim(const UE::FUsdPrim& CurrentPrim);`
- L57 _public prototype_ `UE::FUsdSkelSkeletonQuery ResolveSkelQuery(const UE::FUsdStage& Stage) const;`
- L58 _public prototype_ `UE::FUsdPrim ResolveClosestParentSkelRoot(const UE::FUsdStage& Stage) const;`
- L59 _public prototype_ `void RepopulateSkelCache(const UE::FUsdStage& Stage);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UsdToUnreal`
- L21 _namespace_ `namespace NaniteAssemblyUtils` (scope `UsdToUnreal`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Interchange` (scope `UE`)
- L27 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/CameraSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FCameraSchemaHandler`  
`class FCameraSchemaHandler : public FSchemaHandler`  
_L13-30_
- inherits: `FSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L18 _public prototype_ `virtual const FString& GetTargetSchemaName() const override;`
- L20 _public prototype_ `virtual TOptional<bool> CanBeCollapsed(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L22 _public prototype_ `virtual TOptional<bool> CollapsesChildren(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L24 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/CollapsingSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FCollapsingSchemaHandler`  
`class FCollapsingSchemaHandler : public FSchemaHandler`  
_L13-28_
- inherits: `FSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L18 _public prototype_ `virtual const FString& GetTargetSchemaName() const override;`
- L20 _public prototype_ `virtual bool CanHandlePrim(const UE::FUsdPrim& Prim, const UInterchangeUsdContext& UsdContext) const override;`
- L22 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/GeometryCacheSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FGeometryCacheSchemaHandler`  
`class FGeometryCacheSchemaHandler : public FSchemaHandler`  
_L13-45_
- inherits: `FSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L18 _public prototype_ `virtual const FString& GetTargetSchemaName() const override;`
- L20 _public prototype_ `virtual bool CanHandlePrim(const UE::FUsdPrim& Prim, const UInterchangeUsdContext& UsdContext) const override;`
- L22 _public prototype_ `virtual TOptional<bool> CanBeCollapsed(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L24 _public prototype_ `virtual TOptional<bool> CollapsesChildren(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L26 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`
- L33 _public prototype_ `virtual bool OnGetMeshPayloadData( const FInterchangeMeshPayLoadKey& PayloadKey, const UE::Interchange::FAttributeStorage& PayloadAttributes, UInterchangeUsdContext& UsdContext, TOptional<UE::Interchange::FMeshPayloadData>& InOutPayloadData ) override;`
- L40 _public prototype_ `virtual bool OnGetAnimationPayloadData( const TArray<UE::Interchange::FAnimationPayloadQuery>& PayloadQueries, UInterchangeUsdContext& UsdContext, TArray<UE::Interchange::FAnimationPayloadData>& InOutPayloadData ) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/GprimSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FGprimSchemaHandler`  
`class FGprimSchemaHandler : public FSchemaHandler`  
_L13-43_
- inherits: `FSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L18 _public prototype_ `virtual const FString& GetTargetSchemaName() const override;`
- L20 _public prototype_ `virtual bool CanHandlePrim(const UE::FUsdPrim& Prim, const UInterchangeUsdContext& UsdContext) const override;`
- L22 _public prototype_ `virtual TOptional<bool> CanBeCollapsed(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L24 _public prototype_ `virtual TOptional<bool> CollapsesChildren(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L26 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`
- L33 _public prototype_ `virtual bool OnGetMeshPayloadData( const FInterchangeMeshPayLoadKey& PayloadKey, const UE::Interchange::FAttributeStorage& PayloadAttributes, UInterchangeUsdContext& UsdContext, TOptional<UE::Interchange::FMeshPayloadData>& InOutPayloadData ) override;`
- L41 _private member_ `FRWLock SkeletalMeshDescriptionsLock;`
- L42 _private member_ `TMap<FString, FMeshDescription> PayloadKeyToSkeletalMeshDescriptions;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/GroomBindingSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FGroomBindingSchemaHandler`  
`class FGroomBindingSchemaHandler : public FSchemaHandler`  
_L13-22_
- inherits: `FSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L17 _public prototype_ `virtual const FString& GetTargetSchemaName() const override;`
- L18 _public prototype_ `virtual bool CanHandlePrim(const UE::FUsdPrim& Prim, const UInterchangeUsdContext& UsdContext) const override;`
- L19 _public prototype_ `virtual TOptional<bool> CanBeCollapsed(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L20 _public prototype_ `virtual TOptional<bool> CollapsesChildren(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L21 _public prototype_ `virtual bool OnTranslate(const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/GroomSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FGroomSchemaHandler`  
`class FGroomSchemaHandler : public FSchemaHandler`  
_L13-38_
- inherits: `FSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L18 _public prototype_ `virtual const FString& GetTargetSchemaName() const override;`
- L20 _public prototype_ `virtual bool CanHandlePrim(const UE::FUsdPrim& Prim, const UInterchangeUsdContext& UsdContext) const override;`
- L22 _public prototype_ `virtual TOptional<bool> CanBeCollapsed(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L24 _public prototype_ `virtual TOptional<bool> CollapsesChildren(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L26 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`
- L33 _public prototype_ `virtual bool OnGetGroomPayloadData( const FInterchangeGroomPayloadKey& PayloadKey, UInterchangeUsdContext& UsdContext, TOptional<UE::Interchange::FGroomPayloadData>& InOutPayloadData );`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/HandlerAccumulatedInfo.h` (Public)


#### class `UE::Interchange::USD::FHandlerAccumulatedInfo`  
`class FHandlerAccumulatedInfo`  
_L42-103_
- desc: When we translate a USD prim via the USD translator, we will invoke every suitable schema handler in order. This class is used to accumulate the data produced by each schema handler, and is passed as input/output argument to each handler invocation, so that they can share/accumulate the information they produce. For example, before creating a new Mesh node for a prim, you should check whether one was already created and added to PrimAssetNodes. If so, you should probably try reusing that node instead of creating another one
- L50 _public member_ `TArray<UInterchangeBaseNode*> PrimSceneNodes;` — First node is taken as the main scene node, and passed as ParentNode on FTraversalInfo. Note that this main scene node may be an actually "nullptr" value. This would mean that there should not be any scene node translated for this particular prim (e.g. due to UInterchangeUSDTranslator::Translate() having been called with bAllowSceneNodeGeneration) We don't store actual UInterchangeSceneNode* here because some "scene" nodes don't derive from it directly (e.g. UInterchangeSceneComponentNode)
- L51 _public member_ `TArray<UInterchangeBaseNode*> PrimAssetNodes;`
- L60 _public prototype_ `UInterchangeBaseNode* GetMainSceneNode();` — The "main scene node" is the first node in PrimSceneNodes, always (even if nullptr, which allows the caller to control whether scene node information is produced or not. See also the comment on the PrimSceneNodes member). If your handler intends to produce scene node information, it should retrieve it via GetOrCreateMainSceneNode().
- L61 _public prototype_ `UInterchangeBaseNode* GetOrCreateMainSceneNode( const UE::FUsdPrim& Prim, const FTraversalInfo& TraversalInfo, UInterchangeUsdContext& UsdContext );`
- L71 _public prototype_ `UInterchangeBaseNode* GetOrCreateAssetNode( const TSubclassOf<UInterchangeBaseNode>& NodeClass, UInterchangeBaseNodeContainer& NodeContainer, const FString& NewNodeUid, const FString& NewNodeDisplayName, bool* bOutCreatedNode = nullptr );` — Returns the first node found in PrimAssetNodes that matches the desired class. If none of that class can be found, a new one will be created, added to PrimAssetNodes, and returned.
- L79 _public function_ `template<typename T> T* GetOrCreateAssetNode( UInterchangeBaseNodeContainer& NodeContainer, const FString& NewNodeUid, const FString& NewNodeDisplayName, bool* bOutCreatedNode = nullptr )`
- L93 _public prototype_ `UInterchangeBaseNode* GetAssetNodeOfClass(const TSubclassOf<UInterchangeBaseNode>& NodeClass);` — Returns the first node found in PrimAssetNodes that matches the desired class. If none of that class can be found, returns nullptr.
- L95 _public function_ `template<typename T> T* GetAssetNodeOfClass()`
- L101 _public prototype_ `void AppendInfo(const FHandlerAccumulatedInfo& Other);` — Appends the data from 'Other' into this accumulated info
- L102 _public prototype_ `void AppendInfo(FHandlerAccumulatedInfo&& Other);`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L21 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Interchange` (scope `UE`)
- L25 _namespace_ `namespace USD` (scope `UE::Interchange`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Interchange` (scope `UE`)
- L32 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/ImageableSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FImageableSchemaHandler`  
`class FImageableSchemaHandler : public FSchemaHandler`  
_L13-36_
- inherits: `FSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L18 _public prototype_ `virtual const FString& GetTargetSchemaName() const override;`
- L20 _public prototype_ `virtual TOptional<bool> CanBeCollapsed(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L22 _public prototype_ `virtual TOptional<bool> CollapsesChildren(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const;`
- L24 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`
- L31 _public prototype_ `virtual bool OnGetAnimationPayloadData( const TArray<UE::Interchange::FAnimationPayloadQuery>& PayloadQueries, UInterchangeUsdContext& UsdContext, TArray<UE::Interchange::FAnimationPayloadData>& InOutPayloadData ) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/LightSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FLightSchemaHandler`  
`class FLightSchemaHandler : public FSchemaHandler`  
_L13-32_
- inherits: `FSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L18 _public prototype_ `virtual const FString& GetTargetSchemaName() const override;`
- L20 _public prototype_ `virtual bool CanHandlePrim(const UE::FUsdPrim& Prim, const UInterchangeUsdContext& UsdContext) const override;`
- L22 _public prototype_ `virtual TOptional<bool> CanBeCollapsed(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L24 _public prototype_ `virtual TOptional<bool> CollapsesChildren(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L26 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/MaterialSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FMaterialSchemaHandler`  
`class FMaterialSchemaHandler : public FSchemaHandler`  
_L13-46_
- inherits: `FSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetTargetSchemaName() const override;`
- L22 _public prototype_ `virtual const TArray<FString>& GetDefaultRenderContexts() const = 0;` — Returns the list of render contexts that this handler supports by default. This is likely to be a single value, such as 'unreal' or 'mtlx'
- L28 _public prototype_ `virtual bool AllowCustomRenderContexts() const;` — Returns whether this handler allows the user to provide custom render contexts. This being false (the default value) means this handler is hard-coded to work with only specific render contexts.
- L34 _public prototype_ `virtual const TArray<FString>& GetCustomRenderContexts() const;` — Returns the full list of render contexts that this handler will try parsing materials with. This value is initialized with the output of GetDefaultRenderContexts(), so it should include those entries by default.
- L40 _public prototype_ `virtual void SetCustomRenderContexts(const TArray<FString>& RenderContexts);` — Sets the full list of render contexts that this handler will try parsing materials with, if AllowCustomRenderContexts() is enabled.
- L42 _public prototype_ `virtual bool CanHandlePrim(const UE::FUsdPrim& Prim, const UInterchangeUsdContext& UsdContext) const override;`
- L45 _protected member_ `TArray<FString> CustomRenderContexts;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/MaterialXSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FMaterialXSchemaHandler`  
`class FMaterialXSchemaHandler : public FMaterialSchemaHandler`  
_L13-42_
- inherits: `FMaterialSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L18 _public prototype_ `virtual const TArray<FString>& GetDefaultRenderContexts() const override;`
- L20 _public prototype_ `virtual bool CanHandlePrim(const UE::FUsdPrim& Prim, const UInterchangeUsdContext& UsdContext) const override;`
- L22 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`
- L29 _public prototype_ `virtual bool OnGetTexturePayloadData( const FString& PayloadKey, TOptional<FString>& AlternateTexturePath, UInterchangeUsdContext& UsdContext, TOptional<UE::Interchange::FImportImage>& InOutPayloadData ) override;`
- L36 _public prototype_ `virtual bool OnGetBlockedTexturePayloadData( const FString& PayloadKey, TOptional<FString>& AlternateTexturePath, UInterchangeUsdContext& UsdContext, TOptional<UE::Interchange::FImportBlockedImage>& InOutPayloadData ) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/NaniteAssemblySchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FNaniteAssemblySchemaHandler`  
`class FNaniteAssemblySchemaHandler : public FSchemaHandler`  
_L13-32_
- inherits: `FSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L18 _public prototype_ `virtual const FString& GetTargetSchemaName() const override;`
- L20 _public prototype_ `virtual bool CanHandlePrim(const UE::FUsdPrim& Prim, const UInterchangeUsdContext& UsdContext) const override;`
- L22 _public prototype_ `virtual TOptional<bool> CanBeCollapsed(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L24 _public prototype_ `virtual TOptional<bool> CollapsesChildren(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L26 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/PointInstancerSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FPointInstancerSchemaHandler`  
`class FPointInstancerSchemaHandler : public FSchemaHandler`  
_L13-30_
- inherits: `FSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L18 _public prototype_ `virtual const FString& GetTargetSchemaName() const override;`
- L20 _public prototype_ `virtual TOptional<bool> CanBeCollapsed(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L22 _public prototype_ `virtual TOptional<bool> CollapsesChildren(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L24 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/SchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FSchemaHandler`  
`class FSchemaHandler`  
_L68-193_
- desc: Class that can be used to encapsulate the translation of prims of a certain type into Interchange nodes. You can create a custom handler to process a prim with a target schema by deriving this class and overriding its functions. You must then register the class with FSchemaHandlerRegistry::Register(). Whenever a new USD file is imported, a new UInterchangeUSDTranslator is created, spawning instances of all registered handlers. The translator will retain those instances for the entire translation process. Within the UInterchangeUSDTranslator's TranslatePrim() call for a given prim, the translator will go through all of its spawned handlers in order, and for any handler that returns true to CanHandlePrim() it will invoke OnTranslate(). Note that many handlers can be invoked for each individual prim, so that in the general case handlers should try to reuse and append information to the accumulated Interchange nodes created for that prim. Whenever you don't want your handler to be invoked anymore (e.g. when your module is being shut down) you can unregister your handler with FSchemaHandlerRegistry::Unregister(), passing the handler name
- L71 _public prototype_ `virtual ~FSchemaHandler();`
- L74 _public prototype_ `virtual const FString& GetHandlerName() const = 0;` — Returns the name of this handler, which must be unique between all registered handlers
- L77 _public prototype_ `virtual bool IsEnabled() const;` — Gets whether this handler is enabled for this translation or not
- L80 _public prototype_ `virtual void SetEnabled(bool bEnabled);` — Sets whether this handler is enabled for this translation or not
- L88 _public prototype_ `virtual const FString& GetTargetSchemaName() const;` — Returns the schema name of the prim type to which this handler applies ("Mesh", or "Material, or "Xform", etc.). The base implementation of CanHandlePrim() will use this to determine whether a handler applies to a prim (i.e. it will call Prim.IsA(GetTargetSchemaName()))
- L95 _public prototype_ `virtual bool CanHandlePrim(const UE::FUsdPrim& Prim, const UInterchangeUsdContext& UsdContext) const;` — The InterchangeUSDTranslator only calls OnTranslate() for schema handlers that return true from this function. Additionally, the FInterchangeUsdInfoCache only ever queries CanBeCollapsed() and CollapsesChildren() for handlers that return true from this function
- L102 _public prototype_ `virtual TOptional<bool> CanBeCollapsed(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const;` — Returns whether this prim can be collapsed according to this schema handler. Returning an empty optional (the default) means this schema handler has no opinion about this, and yields to weaker schema handlers. This doesn't get queried during regular translation, but instead is used to build the FInterchangeUsdInfoCache.
- L109 _public prototype_ `virtual TOptional<bool> CollapsesChildren(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const;` — Returns whether this prim should collapse its entire subtree into one asset / actor, according to this schema handler. Returning an empty optional (the default) means this schema handler has no opinion about this, and yields to weaker schema handlers. This doesn't get queried during regular translation, but instead is used to build the FInterchangeUsdInfoCache.
- L122 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext );` — Main function that should be implemented in order to translate a prim into Interchange nodes. @param Prim - Prim to translate @param TraversalInfo - Stores hierarchical information that is collected while we traverse the stage from root to leaf prims @param AccumulatedInfo - Stores information generated by all schema handlers when invoked for this same Prim. If your handler creates Interchange nodes when processing a prim, they should be added here (in addition to the UsdContext's NodeContainer). Your handler should also first search for reusable nodes in this struct before creating new nodes, if possible (i.e. prioritize appending information) @param UsdContext - Global context for this USD stage translation, holding the stage, the node container, cached nodes, etc. @return Whether this handler has successfully processed the prim
- L147 _public prototype_ `virtual bool OnGetMeshPayloadData( const FInterchangeMeshPayLoadKey& PayLoadKey, const UE::Interchange::FAttributeStorage& PayloadAttributes, UInterchangeUsdContext& UsdContext, TOptional<UE::Interchange::FMeshPayloadData>& InOutPayloadData );` — Functions that can be implemented by your handler to provide payload data for a given payload key. When retrieving payload data for a given prim, the UInterchangeUSDTranslator will iterate through all of its spawned handlers in order and invoke this function, passing the same InOutPayloadData argument for all handlers. The intent here is to allow handlers to post-process the payload data if they desire. Note that unlike for OnTranslate(), CanHandlePrim() is not checked before invoking this function, and no other check is performed either. This means that your handler should itself validate within this function whether it should affect the payload data or not. See the corresponding Interchange interface classes for details on each individual payload data and parameter types. @param PayLoadKey - Key for the requested payload data @param PayloadAttributes - Attributes provided by the factories in addition to the payload key @param UsdContext - Global context for this USD stage translation, holding the stage, the node container, cached nodes, etc. @param InOutPayloadData - Accumulated payload information passed through all handlers for a particular payload request @return Whether this handler has successfully processed this payload data.
- L153 _public prototype_ `virtual bool OnGetTexturePayloadData( const FString& PayloadKey, TOptional<FString>& AlternateTexturePath, UInterchangeUsdContext& UsdContext, TOptional<UE::Interchange::FImportImage>& InOutPayloadData );`
- L159 _public prototype_ `virtual bool OnGetBlockedTexturePayloadData( const FString& PayloadKey, TOptional<FString>& AlternateTexturePath, UInterchangeUsdContext& UsdContext, TOptional<UE::Interchange::FImportBlockedImage>& InOutPayloadData );`
- L165 _public prototype_ `virtual bool OnGetAnimationPayloadData( const TArray<UE::Interchange::FAnimationPayloadQuery>& PayloadQueries, UInterchangeUsdContext& UsdContext, TArray<UE::Interchange::FAnimationPayloadData>& InOutPayloadData );`
- L170 _public prototype_ `virtual bool OnGetVolumePayloadData( const UE::Interchange::FVolumePayloadKey& PayloadKey, UInterchangeUsdContext& UsdContext, TOptional<UE::Interchange::FVolumePayloadData>& InOutPayloadData );`
- L175 _public prototype_ `virtual bool OnGetGroomPayloadData( const FInterchangeGroomPayloadKey& PayloadKey, UInterchangeUsdContext& UsdContext, TOptional<UE::Interchange::FGroomPayloadData>& InOutPayloadData );`
- L180 _public prototype_ `virtual bool OnGetAudioPayloadData( const FString& PayloadKey, UInterchangeUsdContext& UsdContext, TOptional<UE::Interchange::FInterchangeAudioPayloadData>& InOutPayloadData );`
- L185 _public prototype_ `virtual bool OnGetGenericPayloadData( const FString& PayloadKey, UInterchangeUsdContext& UsdContext, TObjectPtr<UInterchangeGenericPayloadData>& InOutPayloadData );`
- L192 _protected member_ `bool bEnabled = true;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L26 _namespace_ `namespace UE`
- L29 _namespace_ `namespace Interchange` (scope `UE`)
- L42 _namespace_ `namespace USD` (scope `UE::Interchange`)
- L51 _namespace_ `namespace UE`
- L51 _namespace_ `namespace Interchange` (scope `UE`)
- L51 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/SchemaHandlerEntry.h` (Public)


#### struct `FSchemaHandlerEntry`  
`struct FSchemaHandlerEntry`  
_L17-49_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a registered schema handler of a particular type. This class is used instead of directly tracking FSchemaHandlerGenerators in order to allow programmatically inspecting and manipulating the registered persistent handler information without repeatedly instantiating handlers. It's a USTRUCT and kept in a separate file as it's used by UInterchangeUsdTranslatorSettings in order to track custom schema handler settings (like ordering, which is enabled, etc.)
- L23 _public member_ `FString HandlerName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD Translator")`
- L26 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD Translator")`
- L29 _public member_ `FString SchemaName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD Translator")`
- L33 _public member_ `TArray<FString> DefaultRenderContexts;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD Translator")` — For material schema handlers, we also hoist the render contexts the handler supports here, to be visible on the UI
- L40 _public member_ `bool bAllowCustomRenderContexts = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD Translator")` — If true, it means the handler allows the user to manually specify which render contexts to parse (e.g. the default 'universal' handler does this). If false, it means the handler is hard-coded to only look for a particular render context (e.g. the default MaterialX handler does this).
- L48 _public member_ `TArray<FString> CustomRenderContexts;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD Translator")` — The full list of custom render contexts that this handler should try parsing. This is only used whenever bAllowCustomRenderContexts is enabled. This value is initialized with the value of DefaultRenderContexts within FSchemaHandlerRegistry::Register.

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/SchemaHandlerRegistry.h` (Public)


#### class `UE::Interchange::USD::FSchemaHandlerRegistry`  
`class FSchemaHandlerRegistry`  
_L23-117_
- desc: Static storage of all registered FSchemaHandlers.
- L30 _public member_ `static TArray<FSchemaHandlerEntry> RegisteredHandlerEntries;` — Variable that stores the actual registered schema handlers. This is intentionally exposed so as to allow free insertion/reorder/removal of registered handlers.
- L41 _public member_ `static TMap<FString, FSchemaHandlerGenerator> RegisteredHandlerNamesToGenerators;` — Separate mapping of names to generators. This is useful because it lets us freely copy and serialize our handler entries to reorder / configure them. Registering your handler via FSchemaHandlerRegistry::Register() will also register it here. Whenever a handler is executed without having a corresponding generator function registered for its name, a warning will be emitted and the handler will be skipped.
- L50 _public function_ `template<typename SchemaHandlerType> static FString Register()` — Registers a schema handler of a particular type, so that it is invoked when translating USD files. Usage: FString HandlerName = FSchemaHandlerRegistry::Register<FImageableSchemaHandler>();
- L105 _public prototype_ `static bool Unregister(const FString& HandlerName);` — Unregisters a schema handler, so that it will no longer be invoked when translating USD files. Returns true if it unregistered anything.
- L116 _public prototype_ `static TArray<TSharedRef<FSchemaHandler>> GenerateHandlers(const TArray<FSchemaHandlerEntry>* Entries = &RegisteredHandlerEntries);` — Spawns an instance of each entry in RegisteredHandlerEntries, in order. By default this will use the registered handler entries, but a different array of entries can be provided. Before translation, the UInterchangeUSDTranslator calls this function and retains those same spawned handlers throughout the entire import process, so they are allowed to keep internal state between translation and payload retrieval

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Interchange` (scope `UE`)
- L15 _namespace_ `namespace USD` (scope `UE::Interchange`)
- L18 _typedef_ `using FSchemaHandlerGenerator = TFunction<TSharedRef<FSchemaHandler>(const FSchemaHandlerEntry& Entry)>;` (scope `UE::Interchange::USD`) — Main lambda invoked when spawning an FSchemaHandler
- L73 _function_ `` (scope `UE::Interchange::USD::FSchemaHandlerRegistry::Register`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/SchemaHandlerUtils.h` (Public)


#### struct `UE::Interchange::USD::FInterchangeTrackInfo`  
`struct FInterchangeTrackInfo`  
_L182-187_
- L184 _public member_ `FName PropertyName;`
- L185 _public member_ `EInterchangePropertyTracks TrackType;`
- L186 _public member_ `EInterchangeAnimationPayLoadType PayloadType = EInterchangeAnimationPayLoadType::CURVE;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L24 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Interchange` (scope `UE`)
- L31 _namespace_ `namespace USD` (scope `UE::Interchange`)
- L37 _namespace_ `namespace UsdToUnreal`
- L42 _namespace_ `namespace UsdUtils`
- L48 _namespace_ `namespace UE`
- L48 _namespace_ `namespace Interchange` (scope `UE`)
- L48 _namespace_ `namespace USD` (scope `UE::Interchange`)
- L53 _prototype_ `FString GenerateHash(const FString& NodeUid);` (scope `UE::Interchange::USD`) — Generates a case sensitive hash for NodeUid
- L63 _prototype_ `FString MakeNodeUid(const FString& NodeUid);` (scope `UE::Interchange::USD`) — Append a case sensistive hash of NodeUid to the NodeUid itself, making it so that any TMap<FString, T> that stores these IDs behaves in a case sensitive manner. This is needed because unfortunately the default TMap<FString, T> is not case sensitive on the key FStrings, while prim names are case sensitive. Even if we could modify the UInterchangeBaseNodeContainer::Nodes map to be case sensitive, we'd still constantly get issues as any other TMap<FString, T> in the codebase that stores NodeUids would show collisions
- L69 _prototype_ `FString GetMeshPrimPathFromNodeUid(const FString& NodeUid);` (scope `UE::Interchange::USD`) — Removes the Hash postfix and '\\Mesh\\' prefix if present. (Hash Postfix from MakeNodeUid).
- L78 _prototype_ `FString MakeBoneNodeUid(const FString& SkeletonPrimPath, const FString& ConcatBonePath);` (scope `UE::Interchange::USD`) — Produces a node UID intended to be used by interchange scene nodes that represent USD bones. This also internally uses calls MakeNodeUid(). @param SkeletonPrimPath - Full path to the skeleton prim (e.g. /World/Character/Skel) @param ConcatBonePath - Concatenated path to the current bone (e.g. Hips/Neck/Shoulder) @return The full node uid for the bone (e.g. "\Bone\/World/Character/Skel/Hips/Neck/shoulder_46271545415")
- L88 _prototype_ `FString MakeRootBoneNodeUid(const FString& SkeletonPrimPath);` (scope `UE::Interchange::USD`) — Produces a node UID intended to be used by the scene node that represents a root bone of a skeleton (this may even be an artificial, extra bone added to the skeleton in case the USD skeleton contains multiple root bones). This also internally uses calls MakeNodeUid(). Unlike MakeBoneNodeUid(), this will not actually include any bone name into the UID, and instead will use a standard "Root" suffix (e.g. "\Bone\/World/Character/Skel/Root_46271545415"). The intent is that this allows easy construction of the root joint UID from the skeleton prim path without having to parse the USD skeleton itself all the time.
- L91 _prototype_ `FString GetMorphTargetMeshNodeUid( const UInterchangeUsdContext& UsdContext, const UE::FUsdPrim& MeshPrim, int32 MeshBlendShapeIndex, const FString& InbetweenName = FString{} );` (scope `UE::Interchange::USD`) — Produces a node UID meant to be used by mesh nodes that represent USD blend shapes. Internally calls UsdContext.MakeAssetNodeUid().
- L98 _prototype_ `FString GetMorphTargetMeshNodeUid(const FString& MeshPrimPath, int32 MeshBlendShapeIndex, const FString& InbetweenName = FString{});` (scope `UE::Interchange::USD`) — `UE_DEPRECATED(5.8, "Use the other signature that receives the UsdContext")`
- L105 _function_ `template<typename T> T* GetExistingNode(UInterchangeBaseNodeContainer& NodeContainer, const FString& NodeUid)` (scope `UE::Interchange::USD`) — Utility to facilitate trying to fetch a node with a particular UID *and* a specific type from the NodeContainer, emitting a warning in case of an unexpected type.
- L132 _prototype_ `UInterchangeSceneNode* GetOrCreateDefaultSceneNode(const UE::FUsdPrim& Prim, const FTraversalInfo& Info, UInterchangeUsdContext& UsdContext);` (scope `UE::Interchange::USD`) — Creates a generic scene node corresponding to a prim, if that is appropriate. Also converts attributes and metadata into the new node, if needed.
- L137 _prototype_ `void TranslateAttributeAsUserAttribute( const UE::FUsdPrim& Prim, const FString& AttributeName, UInterchangeBaseNode* Node, const double TimeCode = UsdUtils::GetDefaultTimeCode(), bool bAuthoredOnly = true );` (scope `UE::Interchange::USD`) — Generically converts a non-animated prim attribute into Interchange user attributes, adding them to Node.
- L149 _prototype_ `void TranslateAttributes(const UE::FUsdPrim& Prim, UInterchangeBaseNode* Node, const FString& AllowedAttributeRegex);` (scope `UE::Interchange::USD`) — Generically converts non-animated prim attributes into Interchange user attributes, adding them to Node. A regex can be provided and will be matched against the attribute's name to select which attributes to convert.
- L154 _prototype_ `bool TranslateAPISchemaAttributes(const UE::FUsdPrim& Prim, const FString& AppliedAPISchemaName, UInterchangeBaseNode* Node);` (scope `UE::Interchange::USD`) — Retrieves all attribute names registered for the provided schema, and translates them all into Interchange user attributes on Node
- L161 _prototype_ `void TranslateMetadata(const UE::FUsdPrim& Prim, UInterchangeBaseNode* Node, const FString& AllowedMetadataRegex);` (scope `UE::Interchange::USD`) — Generically converts prim metadata values into Interchange user attributes, adding them to Node. A regex can be provided and will be matched against the metadata field's name to select which fields to convert. Nested metadata dictionaries will be flattened, using ':' as a separator
- L167 _prototype_ `void AddTransformAnimationNode(const UE::FUsdPrim& Prim, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext);` (scope `UE::Interchange::USD`) — Creates a new UInterchangeTransformAnimationTrackNode node describing transform animations on Prim, and adds the node to accumulated info, the node container, and the current track set node.
- L173 _prototype_ `void AddPropertyAnimationNode( const FString& SceneNodeUid, const FName& UEPropertyName, EInterchangePropertyTracks TrackType, EInterchangeAnimationPayLoadType PayloadType, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext );` (scope `UE::Interchange::USD`) — Creates a new UInterchangeAnimationTrackNode node describing animation of a provided UE property of the given SceneNodeUid, and adds the node to accumulated info, the node container, and the current track set node.
- L196 _prototype_ `void AddNodesForAnimatedAttributes( const UE::FUsdPrim& Prim, const TMap<FString, TArray<FInterchangeTrackInfo>>& UsdAttributeNameToTrackInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext );` (scope `UE::Interchange::USD`) — Iterates through UsdAttributeNameToTrackInfo and gets the Prim's attributes matching the map's keys. Then, for each animated attribute, invokes AddPropertyAnimationNode() using the corresponding TrackInfo map value as arguments. Multiple FInterchangeTrackInfo can be provided because sometimes USD attributes map to multiple UE properties (e.g. if we animate sensorWidth on an USD orthographic camera, we need to animate both OrthoWidth and AspectRatio in UE)
- L209 _prototype_ `bool ReadBools( const UE::FUsdStage& UsdStage, const TArray<double>& UsdTimeSamples, const TFunction<bool(double)>& ReaderFunc, UE::Interchange::FAnimationPayloadData& OutPayloadData );` (scope `UE::Interchange::USD`) — These functions are intended to be used when producing payloads for animation tracks of different types. ReaderFunc will be invoked at the provided UsdTimeSamples and collect the animated track key-value pairs into OutPayloadData. The produced keys contain time values in seconds, so a reference to the UsdStage is needed to provide the frame rate conversions. These functions return true if the payload was produced successfully.
- L215 _prototype_ `bool ReadFloats( const UE::FUsdStage& UsdStage, const TArray<double>& UsdTimeSamples, const TFunction<float(double)>& ReaderFunc, UE::Interchange::FAnimationPayloadData& OutPayloadData );` (scope `UE::Interchange::USD`)
- L221 _prototype_ `bool ReadColors( const UE::FUsdStage& UsdStage, const TArray<double>& UsdTimeSamples, const TFunction<FLinearColor(double)>& ReaderFunc, UE::Interchange::FAnimationPayloadData& OutPayloadData );` (scope `UE::Interchange::USD`)
- L227 _prototype_ `bool ReadTransforms( const UE::FUsdStage& UsdStage, const TArray<double>& UsdTimeSamples, const TFunction<FTransform(double)>& ReaderFunc, UE::Interchange::FAnimationPayloadData& OutPayloadData );` (scope `UE::Interchange::USD`)
- L233 _prototype_ `bool ReadRawTransforms( const UE::FUsdStage& UsdStage, const TArray<double>& UsdTimeSamples, const TFunction<FTransform(double)>& ReaderFunc, Interchange::FAnimationPayloadData& OutPayloadData );` (scope `UE::Interchange::USD`)
- L251 _prototype_ `UInterchangeBaseNode* GetOrCreateTwoSidedMaterial(UInterchangeBaseNode* MaterialNode, UInterchangeBaseNodeContainer& NodeContainer);` (scope `UE::Interchange::USD`) — If MaterialNode describes a one-sided material, this will create (or reuse from the NodeContainer) a new material instance node that describes a two-sided version of the material. If the MaterialNode itself represents an instance of an UsdPreviewSurface parent material, the produced material will just be an instance of the two-sided version of that parent material. In other cases, the material instance node will have the provided one-sided material as its parent. This function may also just return MaterialNode in case it is already a two-sided material, or if there's nothing that can be done (e.g. in case MaterialNode is an UInterchangeMaterialReferenceNode)
- L261 _prototype_ `template<typename MeshOrSceneNodeType> void SetSlotMaterialDependencies( MeshOrSceneNodeType* MeshOrSceneNode, const UsdUtils::FUsdPrimMaterialAssignmentInfo& MaterialAssignments, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext );` (scope `UE::Interchange::USD`) — Iterates through MaterialAssignments, producing material nodes and setting them as slot material dependencies on MeshOrSceneNode via SetSlotMaterialDependencyUid() Note that this function may invoke new translations, for example when resolving a material assignment that points at another material prim, or when referencing a MaterialX material
- L275 _prototype_ `void FixMaterialSlotNames( FMeshDescription& MeshDescription, const TArray<UsdUtils::FUsdPrimMaterialSlot>& MeshAssingmentSlots, UInterchangeUsdContext& UsdContext );` (scope `UE::Interchange::USD`) — Fixup material slot names to match the material that is assigned. For Interchange it is better to have the material slot names match what is assigned into them, as it will use those names to "merge identical slots" depending on the import options. Note: These names must also match what is set via MeshNode->SetSlotMaterialDependencyUid(SlotName, MaterialUid)
- L281 _prototype_ `void FixMaterialSlotNames(FMeshDescription& MeshDescription, const TArray<UsdUtils::FUsdPrimMaterialSlot>& MeshAssingmentSlots);` (scope `UE::Interchange::USD`) — `UE_DEPRECATED(5.8, "Use the other overload that receives a UsdContext")`
- L291 _prototype_ `FString GetTextureSourcePath(const FString& TexturePathOnDisk);` (scope `UE::Interchange::USD`) — If we're not translating a decompressed USD root, returns TexturePathOnDisk. If we are translating a decompressed USD root, returns the path to the USDZ file itself. The intent here is that in the USDZ case the texture filepath will point at a temp file on disk, that we may dispose of later after importing. In order to allow reimporting the texture at a later time, we'll just put the USDZ path itself as it's source path, and tweak the USD translator to know what to do with this
- L297 _prototype_ `bool IsValidLODName(const FString& PrimName);` (scope `UE::Interchange::USD`) — Checks whether the provided prim name corresponds to a LOD mesh prim name, in case of our convention of variant-set-based LODs. In other words, returns true when the prim name is of the form "LODN" or "LOD_N" where N is a number
- L300 _prototype_ `int32 GetLODIndexFromName(FString Name);` (scope `UE::Interchange::USD`) — If the provided name returns true for IsValidLODName(), the number N will be returned (see the documentation for IsValidLODName())
- L305 _prototype_ `UE::FUsdPrim GetLODMesh(const UE::FUsdPrim& LODContainerPrim, const FString& LODName);` (scope `UE::Interchange::USD`) — Given a prim that contains an LOD variant set, will return the Mesh prim that corresponds to the provided LOD prim name (e.g. LOD2)
- L310 _prototype_ `UE::FUsdPrim GetLODPrim(const UE::FUsdPrim& LODContainerPrim, const FString& LODName);` (scope `UE::Interchange::USD`) — Contrary to GetLODMesh, this allows non mesh types.
- L320 _prototype_ `UE::FUsdPrim TryGettingInactiveLODPrim(const FString& PrimPathString, UInterchangeUsdContext& UsdContext);` (scope `UE::Interchange::USD`) — When given a full path to a LOD mesh prim (e.g. /World/LODContainer/LOD2), this will return the LOD2 mesh prim. It will do this by actively switching the variant on the LODContainer by opening (or reusing) an entirely separate stage kept in the UsdContext, and returning the prim from there. You should only use this function if you can't find PrimPathString on the main UsdContext stage, due to it not belonging to the currently active variant
- L323 _prototype_ `bool CheckAndChopPayloadPrefix(FString& PayloadKey, const FString& Prefix);` (scope `UE::Interchange::USD`) — If PayloadKey starts with Prefix, it removes it and returns true
- L326 _prototype_ `bool DecodeTexturePayloadKey(const FString& PayloadKey, FString& OutTextureFilePath, TextureGroup& OutTextureGroup);` (scope `UE::Interchange::USD`) — These functions encode or decode information into/from FStrings intended to be used as translated node payload keys
- L327 _prototype_ `FString EncodeTexturePayloadKey(const UsdToUnreal::FTextureParameterValue& Value);` (scope `UE::Interchange::USD`)
- L328 _prototype_ `FString GetMorphTargetCurvePayloadKey(const FString& SkeletonPrimPath, int32 SkelAnimChannelIndex, const FString& BlendShapePath);` (scope `UE::Interchange::USD`)
- L329 _prototype_ `FString GetMorphTargetMeshPayloadKey( bool bIsInsideLOD, const FString& MeshPrimPath, int32 MeshBlendShapeIndex, const FString& InbetweenName = FString{} );` (scope `UE::Interchange::USD`)
- L335 _prototype_ `bool ParseMorphTargetMeshPayloadKey( FString InPayloadKey, bool& bOutIsLODMesh, FString& OutMeshPrimPath, int32& OutBlendShapeIndex, FString& OutInbetweenName );` (scope `UE::Interchange::USD`)
- L347 _prototype_ `FString HashAnimPayloadQuery(const Interchange::FAnimationPayloadQuery& Query);` (scope `UE::Interchange::USD`) — This function produces an unique hash describing the FAnimationPayloadQuery, which is currently used to help group up multiple queries that could be resolved together (i.e. correspond to the same skeleton with the same bake settings)
- L355 _prototype_ `void GetNaniteAssemblyPayloadDataForPrims( const UE::FUsdStage& UsdStage, const UsdToUnreal::FUsdMeshConversionOptions& Options, const UsdToUnreal::NaniteAssemblyUtils::FNaniteAssemblyTraversalResult& TraversalResult, const FString& SkelIdentifier, const TArray<FString>& JointNames, TOptional<UE::Interchange::FNaniteAssemblyDescription>& OutNaniteAssemblyDescription );` (scope `UE::Interchange::USD`) — These functions are used by schema handlers to produce payload data of a particular type from the provided prim. They are exposed here as they must be used by multiple schema handlers. For more information check IInterchangeMeshPayloadInterface and InterchangeMeshPayload.h
- L363 _prototype_ `void GetNaniteAssemblyPayloadDataForPointInstancer( const UE::FUsdPrim& PointInstancerPrim, const UsdToUnreal::FUsdMeshConversionOptions& Options, const UsdToUnreal::NaniteAssemblyUtils::FNaniteAssemblyTraversalResult& TraversalResult, const FString& SkelIdentifier, const TArray<FString>& JointNames, TOptional<UE::Interchange::FNaniteAssemblyDescription>& OutNaniteAssemblyDescription );` (scope `UE::Interchange::USD`)
- L371 _prototype_ `bool GetStaticMeshPayloadData( FString PayloadKey, UInterchangeUsdContext& UsdContext, const UsdToUnreal::FUsdMeshConversionOptions& Options, FMeshDescription& OutMeshDescription, TOptional<UE::Interchange::FNaniteAssemblyDescription>& OutNaniteAssemblyDescription );` (scope `UE::Interchange::USD`)
- L382 _prototype_ `FTransform GetCombinedTransform(const UE::FUsdPrim& Ancestor, const UE::FUsdPrim& Descendant);` (scope `UE::Interchange::USD`) — Combines all LocalTransforms from Descendant up to the Ancestor.
- L387 _prototype_ `void SetPrimPath(UInterchangeBaseNode& BaseNode, const FString& PrimPath);` (scope `UE::Interchange::USD`) — Sets/Stores the PrimPath on the BaseNode
- L392 _prototype_ `FString GetPrimPath(const UInterchangeBaseNode& BaseNode);` (scope `UE::Interchange::USD`) — Queries the PrimPath from the BaseNode
- L397 _prototype_ `FString GetMeshPrimPath(const UInterchangeBaseNode& BaseNode);` (scope `UE::Interchange::USD`) — Queries the Mesh PrimPath from the BaseNode, if it does not exist it will try to deduce form the UniqueID.

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/SkeletonSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FSkeletonSchemaHandler`  
`class FSkeletonSchemaHandler : public FSchemaHandler`  
_L13-36_
- inherits: `FSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L18 _public prototype_ `virtual const FString& GetTargetSchemaName() const override;`
- L20 _public prototype_ `virtual TOptional<bool> CanBeCollapsed(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L22 _public prototype_ `virtual TOptional<bool> CollapsesChildren(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L24 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`
- L31 _public prototype_ `virtual bool OnGetAnimationPayloadData( const TArray<UE::Interchange::FAnimationPayloadQuery>& PayloadQueries, UInterchangeUsdContext& UsdContext, TArray<UE::Interchange::FAnimationPayloadData>& InOutPayloadData );`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/SpatialAudioSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FSpatialAudioSchemaHandler`  
`class FSpatialAudioSchemaHandler : public FSchemaHandler`  
_L13-36_
- inherits: `FSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L18 _public prototype_ `virtual const FString& GetTargetSchemaName() const override;`
- L20 _public prototype_ `virtual TOptional<bool> CanBeCollapsed(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L22 _public prototype_ `virtual TOptional<bool> CollapsesChildren(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L24 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`
- L31 _public prototype_ `virtual bool OnGetAudioPayloadData( const FString& PayloadKey, UInterchangeUsdContext& UsdContext, TOptional<UE::Interchange::FInterchangeAudioPayloadData>& InOutPayloadData ) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/UniversalMaterialSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FUniversalMaterialSchemaHandler`  
`class FUniversalMaterialSchemaHandler : public FMaterialSchemaHandler`  
_L13-46_
- inherits: `FMaterialSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L18 _public prototype_ `const TArray<FString>& GetDefaultRenderContexts() const override;`
- L20 _public prototype_ `virtual bool AllowCustomRenderContexts() const override;`
- L22 _public prototype_ `virtual TOptional<bool> CanBeCollapsed(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L24 _public prototype_ `virtual TOptional<bool> CollapsesChildren(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L26 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`
- L33 _public prototype_ `virtual bool OnGetTexturePayloadData( const FString& PayloadKey, TOptional<FString>& AlternateTexturePath, UInterchangeUsdContext& UsdContext, TOptional<UE::Interchange::FImportImage>& InOutPayloadData ) override;`
- L40 _public prototype_ `virtual bool OnGetBlockedTexturePayloadData( const FString& PayloadKey, TOptional<FString>& AlternateTexturePath, UInterchangeUsdContext& UsdContext, TOptional<UE::Interchange::FImportBlockedImage>& InOutPayloadData ) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/UnrealMaterialSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FUnrealMaterialSchemaHandler`  
`class FUnrealMaterialSchemaHandler : public FMaterialSchemaHandler`  
_L13-26_
- inherits: `FMaterialSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L18 _public prototype_ `virtual const TArray<FString>& GetDefaultRenderContexts() const override;`
- L20 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/VolumeSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FVolumeSchemaHandler`  
`class FVolumeSchemaHandler : public FSchemaHandler`  
_L21-58_
- inherits: `FSchemaHandler`
- L24 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L26 _public prototype_ `virtual const FString& GetTargetSchemaName() const override;`
- L28 _public prototype_ `virtual TOptional<bool> CanBeCollapsed(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L30 _public prototype_ `virtual TOptional<bool> CollapsesChildren(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L32 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`
- L39 _public prototype_ `virtual bool OnGetVolumePayloadData( const UE::Interchange::FVolumePayloadKey& PayloadKey, UInterchangeUsdContext& UsdContext, TOptional<UE::Interchange::FVolumePayloadData>& InOutPayloadData ) override;`
- L45 _public prototype_ `virtual bool OnGetAnimationPayloadData( const TArray<UE::Interchange::FAnimationPayloadQuery>& PayloadQueries, UInterchangeUsdContext& UsdContext, TArray<UE::Interchange::FAnimationPayloadData>& InOutPayloadData ) override;`
- L53 _private member_ `TMap<FString, TArray<UsdUtils::FVolumePrimInfo>> PrimPathToVolumeInfo;` — We stash the info we collected from each Volume prim path here, as we'll reuse it between translation and retrieving the payloads
- L57 _private member_ `TMap<FString, TMap<FString, UInterchangeVolumeNode*>> VolumeFilepathToAnimationIDToNode;` — Used within a translation. We cache these because we make a volume node *per .vdb file*, and on the USD side we may have any number of Volume prims internally using the same .vdb file, and we want to share these whenever possible

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L14 _namespace_ `namespace UsdUtils`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Interchange` (scope `UE`)
- L19 _namespace_ `namespace USD` (scope `UE::Interchange`)

### `Plugins/Interchange/Extensions/OpenUSD/Source/Import/Public/SchemaHandlers/XformableSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FXformableSchemaHandler`  
`class FXformableSchemaHandler : public FSchemaHandler`  
_L13-26_
- inherits: `FSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L18 _public prototype_ `virtual const FString& GetTargetSchemaName() const override;`
- L20 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)
