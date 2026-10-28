# Plugins / ShaderAudit

- module root: `Plugins/Developer/ShaderToolkit/Source/ShaderAudit`
- headers: 3; symbols: 52
- symbol kinds: class=2, delegate=1, member=27, namespace=3, prototype=11, struct=8
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, ContentBrowser, Core, CoreUObject, DesktopPlatform, EditorSubsystem, Engine, InputCore, MaterialValidation, RHI, RenderCore, Slate, SlateCore, ToolMenus, ToolWidgets, TreeMap, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: ShaderAuditCore

### `Plugins/Developer/ShaderToolkit/Source/ShaderAudit/Internal/ShaderAuditEditorSubsystem.h` (Internal)


#### class `UShaderAuditEditorSubsystem`  
`class UShaderAuditEditorSubsystem : public UEditorSubsystem`  
_L13-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- L19 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — UEditorSubsystem
- L20 _public prototype_ `virtual void Deinitialize() override;`
- L22 _public prototype_ `const TArray<TSharedPtr<FShaderAuditSession>>& GetSessions() const;`
- L23 _public prototype_ `FOnShaderSHKFileLoaded& OnSessionLoaded();`
- L26 _private member_ `FOnShaderSHKFileLoaded OnSessionLoadedDelegate;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnShaderSHKFileLoaded) UCLASS(MinimalAPI) class UShaderAuditEditorSubsystem : public UEditorSubsystem { GENERATED_BODY() public: virtual void Initialize(FSubsystemCollectionBase& Collection) override; virtual void Deinitialize() override; const TArray<TSharedPtr<FShaderAuditSession>>& GetSessions() const; FOnShaderSHKFileLoaded& OnSessionLoaded(); private: FOnShaderSHKFileLoaded OnSessionLoadedDelegate; };`

### `Plugins/Developer/ShaderToolkit/Source/ShaderAudit/Public/ShaderAuditModule.h` (Public)


#### class `FShaderAuditEditorModule`  
`class FShaderAuditEditorModule : public IModuleInterface`  
_L12-23_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _private prototype_ `TSharedRef<SDockTab> SpawnToolTab(const FSpawnTabArgs& Args);`
- L22 _private member_ `TSharedPtr<SShaderAuditWidget> AuditWidget;`

### `Plugins/Developer/ShaderToolkit/Source/ShaderAudit/Public/ShaderAuditUtils.h` (Public)


#### struct `UE::ShaderAudit::Utils::FMaterialResolverConfig`  
`struct FMaterialResolverConfig`  
_L23-37_
- L26 _public member_ `FTopLevelAssetPath AssetUserDataClassPath;` — [SubObjectResolver] — used by ResolveMaterialPath
- L29 _public member_ `FTopLevelAssetPath MappingDataClassPath;` — [SubObjectPrimaries] — used by BatchGetMaterialParents sub-object discovery
- L30 _public member_ `TArray<TPair<FString, FName>> SubObjectPrimaryProps;` — LeafName -> PropertyName
- L34 _public member_ `TArray<FTopLevelAssetPath> ExtraRootClasses;` — [ShaderRootClasses] — asset classes that produce shaders independently of the material hierarchy (e.g. UNiagaraSystem). Enumerated as root entries in BatchGetMaterialParents.
- L36 _public member_ `bool bValid = false;`

#### struct `UE::ShaderAudit::Utils::FSubObjectPrimary`  
`struct FSubObjectPrimary`  
_L39-43_
- L41 _public member_ `FString LeafName;`
- L42 _public member_ `FString PrimaryPackagePath;`

#### struct `UE::ShaderAudit::Utils::FMaterialParentEntry`  
`struct FMaterialParentEntry`  
_L45-49_
- L47 _public member_ `FString Child;`
- L48 _public member_ `FString Parent;`

#### struct `UE::ShaderAudit::Utils::FMaterialParentMapResult`  
`struct FMaterialParentMapResult`  
_L51-57_
- L53 _public member_ `TArray<FMaterialParentEntry> Pairs;`
- L54 _public member_ `TArray<FSubObjectPrimary> SubObjectPrimaries;`
- L55 _public member_ `int32 TotalMaterialInterfaces = 0;`
- L56 _public member_ `int32 MissingParentTag = 0;`

#### struct `UE::ShaderAudit::Utils::FHlslSection`  
`struct FHlslSection`  
_L59-63_
- L61 _public member_ `FString Name;`
- L62 _public member_ `FString Hlsl;`

#### struct `UE::ShaderAudit::Utils::FMaterialInsight`  
`struct FMaterialInsight`  
_L65-71_
- L67 _public member_ `FString Path;`
- L68 _public member_ `TArray<FHlslSection> LegacySections;`
- L69 _public member_ `TArray<FHlslSection> NewSections;`
- L70 _public member_ `bool bUsesNewGenerator = false;`

#### struct `UE::ShaderAudit::Utils::FMaterialInsightFailure`  
`struct FMaterialInsightFailure`  
_L73-77_
- L75 _public member_ `FString Path;`
- L76 _public member_ `FString Reason;`

#### struct `UE::ShaderAudit::Utils::FMaterialInsightsResult`  
`struct FMaterialInsightsResult`  
_L79-85_
- L81 _public member_ `TArray<FMaterialInsight> Materials;`
- L82 _public member_ `TArray<FMaterialInsightFailure> Failed;`
- L83 _public member_ `int32 Succeeded = 0;`
- L84 _public member_ `int32 FailedCount = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ShaderAudit` (scope `UE`)
- L11 _namespace_ `namespace Utils` (scope `UE::ShaderAudit`)
- L88 _prototype_ `const FMaterialResolverConfig& GetMaterialResolverConfig();` (scope `UE::ShaderAudit::Utils`) — Returns the singleton resolver config (loaded once on first call).
- L97 _prototype_ `UMaterialInterface* ResolveMaterialPath(const FString& MaterialPath, FString* OutError = nullptr);` (scope `UE::ShaderAudit::Utils`) — Load a UMaterialInterface from a path string. Handles both regular asset paths and sub-object material paths (e.g. "/Game/Pkg/Asset.Asset:SubObject.LeafName") using the game-specific resolver config from Plugins/ShaderAudit/Config/ShaderAudit.ini. Returns null on failure; sets OutError (if provided) to a reason string.
- L105 _prototype_ `FMaterialParentMapResult BuildMaterialParentMap(const FString& PathFilter = FString());` (scope `UE::ShaderAudit::Utils`) — Walk the Asset Registry and build a material parent map. @param PathFilter  Optional case-sensitive package-path prefix (e.g. "/Game/"). Empty = no filter.
- L116 _prototype_ `FMaterialInsightsResult ExtractMaterialInsights( const TArray<FString>& Paths, const FString& Platform = FString());` (scope `UE::ShaderAudit::Utils`) — Load materials by path, run the HLSL translator (no shader compilation), and return per-material ShaderStringParameters from FMaterialInsights. @param Paths     Package paths of materials to translate. Duplicates are ignored. Capped at 10000 entries per call. @param Platform  Shader platform name (e.g. "PCD3D_SM5"). Empty = current editor's max RHI platform.
