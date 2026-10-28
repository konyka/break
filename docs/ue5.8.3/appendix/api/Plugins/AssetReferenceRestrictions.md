# Plugins / AssetReferenceRestrictions

- module root: `Plugins/Editor/AssetReferenceRestrictions/Source/AssetReferenceRestrictions`
- headers: 6; symbols: 144
- symbol kinds: class=5, delegate=2, enum=3, enumerator=6, function=11, macro=5, member=60, prototype=43, struct=8, typedef=1
- PrivateDependencyModuleNames: DataValidation, DeveloperSettings, DeveloperToolSettings, EditorFramework, EditorSubsystem, Engine, Json, Projects, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Editor/AssetReferenceRestrictions/Source/AssetReferenceRestrictions/Private/AssetValidator_AssetReferenceRestrictions.h` (Private)


#### class `UAssetValidator_AssetReferenceRestrictions`  
`class UAssetValidator_AssetReferenceRestrictions : public UEditorValidatorBase`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UEditorValidatorBase`
- L16 _public prototype_ `UAssetValidator_AssetReferenceRestrictions();`
- L20 _protected prototype_ `virtual bool CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const override;`
- L21 _protected prototype_ `virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) override;`
- L25 _private prototype_ `void ValidateAssetInternal(const FAssetData& InAssetData, const IAssetRegistry& InAssetRegistry);`

### `Plugins/Editor/AssetReferenceRestrictions/Source/AssetReferenceRestrictions/Private/EditorValidator_PluginAssetReferences.h` (Private)


#### class `UEditorValidator_PluginAssetReferences`  
`class UEditorValidator_PluginAssetReferences : public UEditorValidatorBase`  
_L10-17_
- reflection: `UCLASS()`
- inherits: `UEditorValidatorBase`
- L15 _public prototype_ `virtual bool CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InObject, FDataValidationContext& InContext) const override;`
- L16 _public prototype_ `virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& Context) override;`

### `Plugins/Editor/AssetReferenceRestrictions/Source/AssetReferenceRestrictions/Public/AssetReferencingDomains.h` (Public)


#### struct `FDomainData`  
`struct FDomainData final : public TSharedFromThis<FDomainData>`  
_L22-54_
- inherits: `TSharedFromThis<FDomainData>`
- L24 _public member_ `FText UserFacingDomainName;`
- L25 _public member_ `FText ErrorMessageIfUsedElsewhere;`
- L28 _public member_ `TArray<FString> DomainRootPaths;` — The list of root paths, always of the format /Mount/ or /Mount/Path/To/ with both leading and trailing /
- L31 _public member_ `TArray<FName> SpecificAssetPackages;` — A list of specific packages that are part of this domain
- L34 _public member_ `TSet<TSharedPtr<FDomainData>> DomainsVisibleFromHere;` — The domains that are visible from here (if bCanSeeEverything is true, then literally everything is visible from here)
- L37 _public member_ `bool bCanSeeEverything = false;` — Can we see everything?
- L40 _public member_ `bool bCanBeSeenByEverything = false;` — Can we be seen by everything?
- L42 _public function_ `bool IsValid() const`
- L47 _public function_ `void Reset()`

#### struct `FDomainDatabase`  
`struct FDomainDatabase final`  
_L56-125_
- L58 _public prototype_ `FDomainDatabase();`
- L59 _public prototype_ `~FDomainDatabase();`
- L61 _public prototype_ `void Init();`
- L63 _public prototype_ `void MarkDirty();`
- L64 _public prototype_ `void UpdateIfNecessary();`
- L67 _public function_ `TMulticastDelegate<void()>& PostDatabaseUpdated()` — Delegate that's called whenever the database has been updated to allow people to respond to the change
- L69 _public prototype_ `void ValidateAllDomains();`
- L70 _public prototype_ `void DebugPrintAllDomains();`
- L72 _public prototype_ `void OnPluginCreatedOrMounted(IPlugin& NewPlugin);`
- L74 _public prototype_ `TSharedPtr<FDomainData> FindDomainFromAssetData(const FAssetData& AssetData) const;`
- L76 _public prototype_ `TTuple<bool, FText> CanDomainsSeeEachOther(TSharedPtr<FDomainData> Referencee, TSharedPtr<FDomainData> Referencer) const;`
- L78 _public function_ `const TArray<FString>& GetDomainsDefinedByPlugins() const`
- L79 _public function_ `bool IsPlugin(TSharedPtr<FDomainData> Domain) const`
- L81 _public prototype_ `TSharedPtr<FDomainData> FindOrAddDomainByName(const FString& Name);`
- L84 _private prototype_ `void RebuildFromScratch();`
- L86 _private prototype_ `void BuildDomainFromPlugin(TSharedRef<IPlugin> Plugin);`
- L87 _private prototype_ `void BuildUnrestrictedDomainFromPlugin(TSharedRef<IPlugin> Plugin);`
- L89 _private prototype_ `void AddDomainVisibilityList(TSharedPtr<FDomainData> Domain, const TArray<FString>& VisibilityList);`
- L92 _private member_ `TMap<FString, TSharedPtr<FDomainData>> DomainNameMap;` — Map from domain name to
- L95 _private member_ `TSharedPtr<FDomainPathNode> PathMap;` — Map from path to domain
- L98 _private member_ `TMap<FName, TSharedPtr<FDomainData>> SpecificAssetPackageDomains;` — Specific packages that are forced into certain domains
- L101 _private member_ `TSharedPtr<FDomainData> EngineDomain;` — The engine content domain
- L104 _private member_ `TSharedPtr<FDomainData> ScriptDomain;` — The default script domain (for reflected types)
- L108 _private member_ `TSharedPtr<FDomainData> TempDomain;` — Used for various 'special' mount points like /Temp/, /Memory/, and /Extra/ Not visible as a domain for other domains to see, and can see everything
- L111 _private member_ `TSharedPtr<FDomainData> GameDomain;` — The game content domain
- L114 _private member_ `TSharedPtr<FDomainData> NeverCookDomain;` — The never cooked content domain
- L117 _private member_ `TArray<FString> DomainsDefinedByPlugins;` — List of domains that came from plugins (used for domain pickers in the settings)
- L120 _private member_ `TSet<TSharedPtr<FDomainData>> PluginDomains;` — Plugin Domains
- L122 _private member_ `bool bDatabaseOutOfDate = false;`
- L124 _private member_ `TMulticastDelegate<void()> OnPostDatabaseUpdated;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ASSETREFERENCERESTRICTIONS_API`
- L10 _macro_ `#define UE_ASSET_DOMAIN_FILTERING_DEBUG_LOGGING 0` — @TODO: Debug printing
- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAssetReferenceRestrictions, Verbose, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAssetReferenceRestrictions, Verbose, All);`
- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAssetReferenceRestrictions, Log, Log);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAssetReferenceRestrictions, Log, Log);`

### `Plugins/Editor/AssetReferenceRestrictions/Source/AssetReferenceRestrictions/Public/AssetReferencingPolicySettings.h` (Public)


#### struct `FARPDefaultPluginDomainRules`  
`struct FARPDefaultPluginDomainRules`  
_L15-32_
- reflection: `USTRUCT()`
- L22 _public member_ `TArray<FString> CanReferenceTheseDomains;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(GetOptions="GetListOfDomains_NoPluginsOrEngine"))` — The list of additional domains always visible from a plugin (EngineContent is always visible, as is content from other plugins that are explicitly referenced)
- L26 _public member_ `bool bCanProjectAccessThesePlugins = true;` — `UPROPERTY(config, EditAnywhere, Category=Settings)` — Can content in the ProjectContent domain access plugin content automatically (for plugins that don't match a specific rule)?
- L31 _public member_ `bool bCanBeSeenByOtherDomainsWithoutDependency = false;` — `UPROPERTY(config, EditAnywhere, Category=Settings)` — Can content in other domains access plugin content automatically (for plugins that don't match a specific rule)? Note: This rule may be deprecated in the future!

#### enum `EARPPluginMatchMode`  
`enum class EARPPluginMatchMode : uint8`  
_L35-39_
- reflection: `UENUM()`
- L37 _public enumerator_ `MatchByCategory`
- L38 _public enumerator_ `MatchByPathPrefix`

#### struct `FARPDomainDefinitionForMatchingPlugins`  
`struct FARPDomainDefinitionForMatchingPlugins`  
_L42-88_
- reflection: `USTRUCT()`
- L49 _public member_ `FText DisplayName;` — `UPROPERTY(EditAnywhere, Category=Settings)` — The display name of this rule (used in error message when attempting to reference content incorrectly) The token {0} will be replaced with the plugin name
- L53 _public member_ `FText ErrorMessageIfUsedElsewhere;` — `UPROPERTY(EditAnywhere, Category=Settings)` — The error message if something that is not allowed to attempts to reference content from this domain
- L57 _public member_ `EARPPluginMatchMode MatchRule = EARPPluginMatchMode::MatchByPathPrefix;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Type of matching for this rule
- L62 _public member_ `FString PluginPathPrefix;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(EditCondition="MatchRule==EARPPluginMatchMode::MatchByPathPrefix", EditConditionHides))` — If set, a plugin with the same rooted directory path will match this rule (use "/FirstFolder/SecondFolder/" to match a plugin like $YourProjectDir/Plugins/FirstFolder/SecondFolder/MyCoolPlugin/MyCoolPlugin.uplugin)
- L66 _public member_ `FString PluginCategoryPrefix;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(EditCondition="MatchRule==EARPPluginMatchMode::MatchByCategory", EditConditionHides))` — If set, a plugin with a matching Category will match this rule
- L71 _public member_ `TArray<FString> CanReferenceTheseDomains;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(GetOptions="GetListOfDomains_NoPluginsOrEngine"))` — The list of additional domains always visible from a plugin (EngineContent is always visible, as is content from other plugins that are explicitly referenced)
- L73 _public function_ `bool IsValid() const`

#### struct `FARPDomainSettingsForPlugins`  
`struct FARPDomainSettingsForPlugins`  
_L91-107_
- reflection: `USTRUCT()`
- L97 _public member_ `FARPDefaultPluginDomainRules DefaultRule;` — `UPROPERTY(EditAnywhere, Category=Settings)` — The default rule if a more specific plugin rule doesn't apply
- L106 _public member_ `TArray<FARPDomainDefinitionForMatchingPlugins> AdditionalRules;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(TitleProperty="DisplayName"))` — Discovered plugins will be matched against these templates Priority rules (a path match is preferred to a category match, and within each the longest match wins): Highest: The most specific path match Any path match The most specific category match Any category match

#### struct `FARPDefaultProjectDomainRules`  
`struct FARPDefaultProjectDomainRules`  
_L111-121_
- reflection: `USTRUCT()`
- L120 _public member_ `TArray<FString> CanReferenceTheseDomains;` — `UPROPERTY(EditAnywhere, Category = Settings, meta=(GetOptions="GetListOfDomains_NoEngineOrGame"))` — The list of additional domains always visible from this domain. EngineContent and Project Content in the '/Game/' directory are always visible

#### enum `EARPDomainAllowedToReferenceMode`  
`enum class EARPDomainAllowedToReferenceMode : uint8`  
_L125-129_
- reflection: `UENUM()`
- L127 _public enumerator_ `AdditionalDomains`
- L128 _public enumerator_ `AllDomains UMETA(DisplayName = "All Domains (DANGER)")`

#### struct `FARPDomainDefinitionByContentRoot`  
`struct FARPDomainDefinitionByContentRoot`  
_L133-176_
- reflection: `USTRUCT()`
- L139 _public member_ `FString DomainName;` — `UPROPERTY(EditAnywhere, Category=Settings)` — The name of this domain
- L143 _public member_ `FText DomainDisplayName;` — `UPROPERTY(EditAnywhere, Category=Settings)` — The display name of this domain (used in error message when attempting to reference content incorrectly)
- L147 _public member_ `FText ErrorMessageIfUsedElsewhere;` — `UPROPERTY(EditAnywhere, Category=Settings)` — The error message if something that is not allowed to attempts to reference content from this domain
- L151 _public member_ `TArray<FDirectoryPath> ContentRoots;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(ContentDir))` — The list of content root paths considered to be part of this domain
- L155 _public member_ `TArray<FName> SpecificAssets;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(LongPackageName))` — A list of specific assets considered to be part of this domain
- L159 _public member_ `EARPDomainAllowedToReferenceMode ReferenceMode = EARPDomainAllowedToReferenceMode::AdditionalDomains;` — `UPROPERTY(EditAnywhere, Category = Settings)` — What content is this domain allowed to access?
- L164 _public member_ `TArray<FString> CanReferenceTheseDomains;` — `UPROPERTY(EditAnywhere, Category = Settings, meta=(GetOptions="GetListOfDomains_NoEngine", EditCondition="ReferenceMode==EARPDomainAllowedToReferenceMode::AdditionalDomains", EditConditionHides))` — The list of additional domains always visible from this domain (EngineContent is always visible)
- L166 _public function_ `bool IsValid() const`

#### class `UAssetReferencingPolicySettings`  
`class UAssetReferencingPolicySettings : public UDeveloperSettings`  
_L180-252_
- reflection: `UCLASS(MinimalAPI, config=Game, defaultconfig, meta=(DisplayName="Asset Referencing Policy"))`
- inherits: `UDeveloperSettings`
- desc: Settings for the Asset Referencing Policy, these settings are used to determine which plugins and game folders can reference content from each other
- L187 _public member_ `bool bUseAssetReferenceRestrictions = true;` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — High level switch to enable or disable all AssetReferenceRestrictions
- L191 _public member_ `FARPDomainSettingsForPlugins EnginePlugins;` — `UPROPERTY(config, EditAnywhere, Category="Engine Plugins")` — Settings/rules for engine plugins
- L195 _public member_ `FARPDomainSettingsForPlugins ProjectPlugins;` — `UPROPERTY(config, EditAnywhere, Category="Project Plugins")` — Settings/rules for project plugins
- L199 _public member_ `FARPDefaultProjectDomainRules DefaultProjectContentRule;` — `UPROPERTY(config, EditAnywhere, Category="Project Content")` — The default rules for project content (if a more specific rule doesn't apply)
- L203 _public member_ `TArray<FARPDomainDefinitionByContentRoot> AdditionalDomains;` — `UPROPERTY(config, EditAnywhere, Category="Project Content", meta=(TitleProperty=DomainName))` — List of additional domains to carve out from the project content folder
- L207 _public member_ `bool bIgnoreEditorOnlyReferences = true;` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — If true, ignore any editor-only domain references that will not affect the cooked game
- L210 _public member_ `static const FString EngineDomainName;` — The names of the project, special system mount, and game domains
- L211 _public member_ `static const FString ScriptDomainName;`
- L212 _public member_ `static const FString GameDomainName;`
- L213 _public member_ `static const FString TempDomainName;`
- L214 _public member_ `static const FString NeverCookDomainName;`
- L219 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L223 _public prototype_ `UAssetReferencingPolicySettings(const FObjectInitializer& ObjectInitializer);`
- L226 _private prototype_ `TArray<FString> GetListOfDomains(bool bAllowPlugins, bool bAllowEngine, bool bAllowGame) const;`
- L229 _private function_ `TArray<FString> GetListOfDomains_All() const` — `UFUNCTION()`
- L235 _private function_ `TArray<FString> GetListOfDomains_NoEngine() const` — `UFUNCTION()`
- L241 _private function_ `TArray<FString> GetListOfDomains_NoEngineOrGame() const` — `UFUNCTION()`
- L247 _private function_ `TArray<FString> GetListOfDomains_NoPluginsOrEngine() const` — `UFUNCTION()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ASSETREFERENCERESTRICTIONS_API`

### `Plugins/Editor/AssetReferenceRestrictions/Source/AssetReferenceRestrictions/Public/AssetReferencingPolicySubsystem.h` (Public)


#### enum `EAssetReferenceErrorType`  
`enum class EAssetReferenceErrorType`  
_L19-23_
- L21 _public enumerator_ `DoesNotExist`
- L22 _public enumerator_ `Illegal`

#### struct `FAssetReferenceError`  
`struct FAssetReferenceError`  
_L25-32_
- L27 _public member_ `bool bTreatErrorAsWarning = false;`
- L28 _public member_ `EAssetReferenceErrorType Type;`
- L29 _public member_ `FAssetData ReferencedAsset;`
- L30 _public member_ `FText Message;`
- L31 _public member_ `FText Suffix;`

#### class `UAssetReferencingPolicySubsystem`  
`class UAssetReferencingPolicySubsystem : public UEditorSubsystem`  
_L36-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: Subsystem to register the domain-based asset referencing policy restrictions with the editor
- L42 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L43 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L44 _public prototype_ `virtual void Deinitialize() override;`
- L48 _public prototype_ `bool ShouldValidateAssetReferences(const FAssetData& Asset) const;` — Returns whether the given asset's outgoing references are restricted in any way and should be individually validated
- L51 _public prototype_ `TValueOrError<void, TArray<FAssetReferenceError>> ValidateAssetReferences(const FAssetData& Asset) const;` — Check the outgoing references of the given asset according to the asset registry and return details of any errors
- L52 _public prototype_ `TValueOrError<void, TArray<FAssetReferenceError>> ValidateAssetReferences(const FAssetData& Asset, const EAssetReferenceFilterRole Role) const;`
- L54 _public prototype_ `TSharedPtr<FDomainDatabase> GetDomainDB() const;`
- L56 _private prototype_ `void UpdateDBIfNecessary() const;`
- L58 _private prototype_ `TSharedPtr<IAssetReferenceFilter> HandleMakeAssetReferenceFilter(const FAssetReferenceFilterContext& Context);`
- L60 _private member_ `TSharedPtr<FDomainDatabase> DomainDB;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ASSETREFERENCERESTRICTIONS_API`

### `Plugins/Editor/AssetReferenceRestrictions/Source/AssetReferenceRestrictions/Public/DomainAssetReferenceFilter.h` (Public)


#### class `FDomainAssetReferenceFilter`  
`class FDomainAssetReferenceFilter : public IAssetReferenceFilter`  
_L15-47_
- inherits: `IAssetReferenceFilter`
- L18 _public prototype_ `FDomainAssetReferenceFilter(const FAssetReferenceFilterContext& Context, TSharedPtr<FDomainDatabase> InDomainDB);`
- L19 _public prototype_ `~FDomainAssetReferenceFilter();`
- L22 _public prototype_ `virtual bool PassesFilter(const FAssetData& AssetData, FText* OutOptionalFailureReason = nullptr) const override;`
- L26 _public prototype_ `static void UpdateAllFilters();` — Update any cached information for all filters
- L28 _private typedef_ `using FAssetDataInfo = TTuple<FAssetData, TSharedPtr<FDomainData>>;`
- L30 _private prototype_ `bool PassesFilterImpl(const FAssetData& AssetData, FText& OutOptionalFailureReason) const;`
- L31 _private prototype_ `bool IsCrossPluginReferenceAllowed(const FAssetDataInfo& ReferencingAssetDataInfo, const FAssetDataInfo& ReferencedAssetDataInfo) const;`
- L33 _private prototype_ `void DetermineReferencingDomain();`
- L36 _private prototype_ `void TryGetAssociatedAssetsFromPossiblyPreviewObject(UObject* PossiblyPreviewObject, TArray<FAssetData>& InOutAssetsToConsider) const;` — Heuristic to find actual assets from preview assets (i.e., the material editor's preview material)
- L39 _private member_ `static TArray<FDomainAssetReferenceFilter*> FilterInstances;`
- L41 _private member_ `TSharedPtr<FDomainDatabase> DomainDB;`
- L43 _private member_ `TArray<FAssetReferenceFilterReferencerInfo> OriginalReferencingAssets;`
- L44 _private member_ `TSet<FAssetDataInfo> ReferencingAssetDataInfos;`
- L46 _private member_ `FText Failure_CouldNotDetermineDomain;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ASSETREFERENCERESTRICTIONS_API`
