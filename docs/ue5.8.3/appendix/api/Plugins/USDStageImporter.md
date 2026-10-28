# Plugins / USDStageImporter

- module root: `Plugins/Importers/USDImporter/Source/USDStageImporter`
- headers: 11; symbols: 215
- symbol kinds: class=13, enum=2, enumerator=7, function=15, macro=5, member=92, namespace=1, prototype=70, struct=5, typedef=5
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, EditorFramework, EditorStyle, Engine, GeometryCache, InputCore, JsonUtilities, LevelSequence, MainFrame, MessageLog, MovieScene, PropertyEditor, RenderCore, Slate, SlateCore, USDClasses, USDSchemas, USDStage, USDUtilities, UnrealEd, UnrealUSDWrapper
- PublicDependencyModuleNames: HairStrandsCore

### `Plugins/Importers/USDImporter/Source/USDStageImporter/Private/USDStageAssetImportFactory.h` (Private)


#### class `UUsdStageAssetImportFactory`  
`class UUsdStageAssetImportFactory : public UFactory , public FReimportHandler`  
_L14-46_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory,FReimportHandler`
- desc: Factory to import USD files that gets called when we hit Import in the Content Browser, as well as during reimport
- L22 _public prototype_ `virtual bool DoesSupportClass(UClass* Class) override;` — UFactory interface
- L23 _public prototype_ `virtual UClass* ResolveSupportedClass() override;`
- L24 _public prototype_ `virtual UObject* FactoryCreateFile( UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled ) override;`
- L34 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L35 _public prototype_ `virtual void CleanUp() override;`
- L38 _public prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames);` — FReimportHandler interface
- L39 _public prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths);`
- L40 _public prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj);`
- L41 _public prototype_ `virtual int32 GetPriority() const override;`
- L45 _private member_ `FUsdStageImportContext ImportContext;` — `UPROPERTY()`

### `Plugins/Importers/USDImporter/Source/USDStageImporter/Private/USDStageImportFactory.h` (Private)


#### class `UUsdStageImportFactory`  
`class UUsdStageImportFactory : public USceneImportFactory`  
_L13-35_
- reflection: `UCLASS(Transient)`
- inherits: `USceneImportFactory`
- desc: Factory to import USD files that gets called when we hit File -> Import into level...
- L19 _public prototype_ `virtual UObject* FactoryCreateFile( UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled ) override;` — UFactory Interface
- L29 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L30 _public prototype_ `virtual void CleanUp() override;`
- L34 _private member_ `FUsdStageImportContext ImportContext;` — `UPROPERTY()`

### `Plugins/Importers/USDImporter/Source/USDStageImporter/Private/USDStageImportOptionsCustomization.h` (Private)


#### class `FUsdStageImportOptionsCustomization`  
`class FUsdStageImportOptionsCustomization : public IDetailCustomization`  
_L14-37_
- inherits: `IDetailCustomization`
- L17 _public prototype_ `FUsdStageImportOptionsCustomization();`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L21 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L22 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L26 _private prototype_ `void OnComboBoxOpening();`
- L27 _private prototype_ `void OnComboBoxSelectionChanged(TSharedPtr<FString> NewContext, ESelectInfo::Type SelectType);`
- L28 _private prototype_ `FText GetComboBoxSelectedOptionText() const;`
- L29 _private prototype_ `void ForceRefreshDetails();`
- L31 _private member_ `UUsdStageImportOptions* CurrentOptions;`
- L33 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> RenderContextComboBox;`
- L34 _private member_ `TArray<TSharedPtr<FString>> RenderContextComboBoxItems;`
- L36 _private member_ `TArray<TSharedPtr<FString>> MaterialPurposeComboBoxItems;`

### `Plugins/Importers/USDImporter/Source/USDStageImporter/Public/USDOptionsWindow.h` (Public)


#### class `SUsdOptionsWindow`  
`class SUsdOptionsWindow : public SCompoundWidget`  
_L15-54_
- inherits: `SCompoundWidget`
- desc: Slate window used to show import/export options for the USDImporter plugin
- L18 _public function_ `SLATE_BEGIN_ARGS(SUsdOptionsWindow) : _OptionsObject(nullptr)`
- L30 _public prototype_ `static bool ShowOptions(UObject& OptionsObject, const FText& WindowTitle, const FText& AcceptText, const UE::FUsdStage* Stage = nullptr);` — Show the options window with the given text
- L33 _public prototype_ `static bool ShowImportOptions(UObject& OptionsObject, const UE::FUsdStage* StageToImport);` — Shortcut functions that show the standard import/export text
- L34 _public prototype_ `static bool ShowExportOptions(UObject& OptionsObject);`
- L36 _public prototype_ `void Construct(const FArguments& InArgs);`
- L37 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L39 _public prototype_ `FReply OnAccept();`
- L40 _public prototype_ `FReply OnCancel();`
- L42 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L43 _public prototype_ `bool UserAccepted() const;`
- L44 _public prototype_ `TArray<FString> GetSelectedFullPrimPaths() const;`
- L47 _private member_ `UObject* OptionsObject;`
- L49 _private member_ `TWeakPtr<SWindow> Window;`
- L50 _private member_ `TSharedPtr<class SUsdStagePreviewTree> StagePreviewTree;`
- L52 _private member_ `FText AcceptText;`
- L53 _private member_ `bool bAccepted;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API USDSTAGEIMPORTER_API`

### `Plugins/Importers/USDImporter/Source/USDStageImporter/Public/USDStageImportContext.h` (Public)


#### struct `FUsdStageImportContext`  
`struct FUsdStageImportContext`  
_L23-134_
- reflection: `USTRUCT()`
- L27 _public member_ `UWorld* World;`
- L33 _public member_ `FTransform TargetSceneActorTargetTransform;` — Whenever we spawn the scene actor, it should have this local transform and be attached to this parent. We use this so that Actions->Import can spawn the scene actor exactly where the original stage actor was
- L34 _public member_ `USceneComponent* TargetSceneActorAttachParent;`
- L38 _public member_ `TObjectPtr<AActor> SceneActor;` — `UPROPERTY()` — Spawned actor that contains the imported scene as a child hierarchy
- L42 _public member_ `FString ObjectName;` — `UPROPERTY()` — Name to use when importing a single mesh
- L45 _public member_ `FString PackagePath;` — `UPROPERTY()`
- L49 _public member_ `FString FilePath;` — `UPROPERTY()` — Path of the main usd file to import
- L52 _public member_ `TObjectPtr<UUsdStageImportOptions> ImportOptions;` — `UPROPERTY()`
- L56 _public member_ `TObjectPtr<UObject> ImportedAsset;` — `UPROPERTY()` — Keep track of the last imported object so that we have something valid to return to upstream code that calls the import factories
- L59 _public member_ `TArray<TObjectPtr<UObject>> ImportedAssets;` — `UPROPERTY()`
- L62 _public member_ `FUsdLevelSequenceHelper LevelSequenceHelper;` — Level sequence that will contain the animation data during the import process
- L65 _public member_ `TObjectPtr<UUsdAssetCache3> UsdAssetCache;` — `UPROPERTY()`
- L70 _public member_ `TObjectPtr<UUsdAssetCache2> AssetCache_DEPRECATED;` — `UE_DEPRECATED(all, "Use the 'UsdAssetCache' member instead, which is of the new UUsdAssetCache3 type")` — `UPROPERTY()`
- L73 _public member_ `TSharedPtr<FUsdInfoCache> InfoCache_DEPRECATED;` — `UE_DEPRECATED(all, "The import process now always builds its own InfoCache, so this member is no longer used")`
- L77 _public member_ `TSharedPtr<UE::FUsdGeomBBoxCache> BBoxCache;` — Bounding box cache used for the USD stage in case we have to spawn bounds components
- L83 _public member_ `TMap<FString, TMap<FString, int32>> MaterialToPrimvarToUVIndex;` — When parsing materials, we keep track of which primvar we mapped to which UV channel. When parsing meshes later, we use this data to place the correct primvar values in each UV channel.
- L86 _public member_ `UE::FUsdStage Stage;` — USD Stage to import
- L89 _public member_ `EObjectFlags ImportObjectFlags;` — Object flags to apply to newly imported objects
- L92 _public member_ `bool bIsAutomated;` — If true, options dialog won't be shown
- L98 _public member_ `bool bReadFromStageCache;` — If true, this will try loading the stage from the static stage cache before re-reading the file. If false, the USD file at FilePath is reopened (but the stage is left untouched).
- L101 _public member_ `bool bStageWasOriginallyOpenInCache;` — If we're reading from the stage cache and the stage was originally open, it will be left open when the import is completed
- L105 _public member_ `double OriginalMetersPerUnit;` — We modify the stage with our meters per unit import option on import. If the stage was already open, we use this to undo the changes after import
- L106 _public member_ `EUsdUpAxis OriginalUpAxis;`
- L109 _public member_ `bool bNeedsGarbageCollection;` — If we need to run GC after the import is complete
- L112 _public prototype_ `FUsdStageImportContext();`
- L115 _public prototype_ `~FUsdStageImportContext() = default;`
- L116 _public prototype_ `FUsdStageImportContext(const FUsdStageImportContext& Other) = default;`
- L117 _public prototype_ `FUsdStageImportContext& operator=(const FUsdStageImportContext& Other) = default;`
- L120 _public prototype_ `bool Init( const FString& InName, const FString& InFilePath, const FString& InInitialPackagePath, EObjectFlags InFlags, bool bInIsAutomated, bool bIsReimport = false, bool bAllowActorImport = true );`
- L129 _public prototype_ `void Reset();`
- L133 _private member_ `TArray<TSharedRef<FTokenizedMessage>> TokenizedErrorMessages;` — Error messages

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API USDSTAGEIMPORTER_API`

### `Plugins/Importers/USDImporter/Source/USDStageImporter/Public/USDStageImportOptions.h` (Public)


#### enum `EReplaceActorPolicy`  
`enum class EReplaceActorPolicy : uint8`  
_L20-33_
- reflection: `UENUM(BlueprintType)`
- L23 _public enumerator_ `Append` — Spawn new actors and components alongside the existing ones
- L26 _public enumerator_ `Replace` — Replaces existing actors and components with new ones
- L29 _public enumerator_ `UpdateTransform` — Update transforms on existing actors but do not replace actors or components
- L32 _public enumerator_ `Ignore` — Ignore any conflicting new assets and components, keeping the old ones

#### enum `EReplaceAssetPolicy`  
`enum class EReplaceAssetPolicy : uint8`  
_L36-46_
- reflection: `UENUM(BlueprintType)`
- L39 _public enumerator_ `Append` — Create new assets with numbered suffixes
- L42 _public enumerator_ `Replace` — Replaces existing asset with new asset
- L45 _public enumerator_ `Ignore` — Ignores the new asset and keeps the existing asset

#### class `UUsdStageImportOptions`  
`class UUsdStageImportOptions : public UObject`  
_L49-252_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L55 _public member_ `bool bImportActors;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "DataToImport", meta = (DisplayName = "Actors"))`
- L58 _public member_ `bool bImportGeometry;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "DataToImport", meta = (DisplayName = "Geometry"))`
- L68 _public member_ `bool bImportSkeletalAnimations;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "DataToImport", meta = (EditCondition = bImportGeometry, DisplayName = "Skeletal Animations"))` — Whether to try importing UAnimSequence skeletal animation assets for each encountered UsdSkelAnimQuery
- L71 _public member_ `bool bImportLevelSequences;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "DataToImport", meta = (DisplayName = "LevelSequences"))`
- L74 _public member_ `bool bImportMaterials;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "DataToImport", meta = (DisplayName = "Materials & Textures"))`
- L78 _public member_ `bool bImportGroomAssets;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "DataToImport", meta = (DisplayName = "Groom Assets"))` — Whether to import GroomAssets, GroomCaches and GroomBindings
- L82 _public member_ `bool bImportSparseVolumeTextures;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "DataToImport", meta = (DisplayName = "Sparse Volume Textures"))` — Whether to import OpenVDB volumes as Sparse Volume Textures
- L86 _public member_ `bool bImportSounds;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "DataToImport", meta = (DisplayName = "Audio"))` — Whether to import audio files referenced by UsdMediaSpatialAudio schemas as Unreal sound assets
- L93 _public member_ `bool bImportOnlyUsedMaterials;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "DataToImport", AdvancedDisplay, meta = (EditCondition = bImportMaterials))` — If this is checked, only materials actively used by the stage and import settings will be parsed. If this is unchecked, all materials present on the stage will be parsed.
- L104 _public member_ `bool bUseExistingAssetCache;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "USD options", meta = (InlineEditConditionToggle))`
- L114 _public member_ `FSoftObjectPath ExistingAssetCache = nullptr;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "USD options", meta = (AllowedClasses = "/Script/USDClasses.UsdAssetCache3", EditCondition = "bUseExistingAssetCache"))` — Copy assets from an existing UsdAsset cache instead of generating them from scratch, if possible
- L124 _public member_ `int32 PurposesToImport;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "USD options", meta = (Bitmask, BitmaskEnum = "/Script/UnrealUSDWrapper.EUsdPurpose"))` — Only import prims with these specific purposes from the USD file
- L128 _public member_ `int32 NaniteTriangleThreshold;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "USD options", meta = (NoSpinbox = "true", UIMin = "0", ClampMin = "0"))` — Try enabling Nanite for static meshes that are generated with at least this many triangles
- L132 _public member_ `FName RenderContextToImport;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "USD options")` — Specifies which set of shaders to use when parsing USD materials, in addition to the universal render context.
- L136 _public member_ `FName MaterialPurpose;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "USD options")` — Specifies which material purpose to use when parsing USD material bindings, in addition to the "allPurpose" fallback
- L140 _public member_ `EUsdRootMotionHandling RootMotionHandling = EUsdRootMotionHandling::NoAdditionalRootMotion;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "USD options", meta = (EditCondition = bImportSkeletalAnimations))` — Describes what to add to the root bone animation within generated AnimSequences, if anything
- L144 _public member_ `EUsdCollisionType FallbackCollisionType;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "USD options")` — What type of collision to use for static meshes generated from Prims that don't have physics schemas applied
- L148 _public member_ `int32 SubdivisionLevel;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "USD options", meta = (ClampMin = "0", ClampMax = "6", UIMin = "0", UIMax = "6"))` — Subdivision level to use for all subdivision meshes on the opened stage. 0 means "don't subdivide"
- L152 _public member_ `FUsdMetadataImportOptions MetadataOptions;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "USD options")` — Describes if/how we should collect metadata from USD prims onto the assets and components we generate when importing
- L156 _public member_ `bool bOverrideStageOptions;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "USD options")` — Whether to use the specified StageOptions instead of the stage's own settings
- L160 _public member_ `FUsdStageOptions StageOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "USD options", meta = (EditCondition = bOverrideStageOptions))` — Custom StageOptions to use for the stage
- L167 _public member_ `bool bImportAtSpecificTimeCode;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "USD options")` — When true the stage will be evaluated at ImportTimeCode for the import. When false, the stage will be evaluated at the default (non-animated) timecode
- L171 _public member_ `float ImportTimeCode;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "USD options", meta = (EditCondition = bImportAtSpecificTimeCode))` — TimeCode to evaluate the stage for import, in case bImportAtSpecificTimeCode is enabled
- L179 _public member_ `bool bShareAssetsForIdenticalPrims;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "USD options")` — If true, whenever two prims would have generated identical UAssets (like identical StaticMeshes or materials) then only one instance of that asset is generated, and the asset is shared by the components generated for both prims. If false, we will always generate a dedicated asset for each prim.
- L183 _public member_ `TArray<FHairGroupsInterpolation> GroomInterpolationSettings;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Groom")` — Groom group interpolation settings
- L187 _public member_ `EReplaceActorPolicy ExistingActorPolicy;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Conflicts with Existing Objects", meta = (EditCondition = bImportActors))` — What should happen when imported actors and components try to overwrite existing actors and components
- L191 _public member_ `EReplaceAssetPolicy ExistingAssetPolicy;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Conflicts with Existing Objects")` — What should happen when imported assets try to overwrite existing assets
- L195 _public member_ `bool bReuseIdenticalAssets_DEPRECATED;` — `UE_DEPRECATED(all, "Use 'Share Assets for Identical Prims' instead")` — `UPROPERTY()`
- L202 _public member_ `bool bPrimPathFolderStructure;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Processing")` — When enabled, assets will be imported into a content folder structure according to their prim path. When disabled, assets are imported into content folders according to asset type (e.g. 'Materials', 'StaticMeshes', etc).
- L209 _public member_ `bool bUsePrimKindsForCollapsing;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Processing")` — Use KindsToCollapse to determine when to collapse prim subtrees or not (defaults to enabled). Disable this if you want to prevent collapsing, or to control it manually by right-clicking on individual prims.
- L222 _public member_ `int32 KindsToCollapse;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Processing", meta = (Bitmask, BitmaskEnum = "/Script/UnrealUSDWrapper.EUsdDefaultKind", EditCondition = bUsePrimKindsForCollapsing))` — Whether to try to combine individual assets and components of the same type on a kind-per-kind basis, like multiple Mesh prims into a single Static Mesh
- L229 _public member_ `bool bMergeIdenticalMaterialSlots;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Processing")` — Identical material slots will be combined into a single slot if this is enabled. This is only performed in the context of mesh collapsing, or when parsing LOD variant sets (see bInterpretLODs)
- L233 _public member_ `bool bCollapseTopLevelPointInstancers_DEPRECATED;` — `UE_DEPRECATED(all, "This option is now controlled via the cvar 'USD.CollapseTopLevelPointInstancers'")` — `UPROPERTY()`
- L245 _public member_ `bool bInterpretLODs;` — `UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Processing", meta = (DisplayName = "Interpret LOD variant sets", ScriptName="InterpretLods;InterpretLODs", EditCondition = bImportGeometry))` — When true, if a prim has a "LOD" variant set with variants named "LOD0", "LOD1", etc. where each contains a UsdGeomMesh, the importer will attempt to parse the meshes as separate LODs of a single UStaticMesh. When false, only the selected variant will be parsed as LOD0 of the UStaticMesh.
- L249 _public prototype_ `void EnableActorImport(bool bEnable);` — `UE_DEPRECATED(5.6, "Use FScopedSuppressActorImport instead.")`
- L251 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

#### struct `UsdUtils::FScopedSuppressActorImport`  
`struct FScopedSuppressActorImport`  
_L256-269_
- L258 _public prototype_ `FScopedSuppressActorImport(UUsdStageImportOptions* InOptions);`
- L259 _public prototype_ `~FScopedSuppressActorImport();`
- L261 _public prototype_ `FScopedSuppressActorImport(const FScopedSuppressActorImport& Other) = delete;`
- L262 _public prototype_ `FScopedSuppressActorImport(FScopedSuppressActorImport&& Other) = delete;`
- L263 _public prototype_ `FScopedSuppressActorImport& operator=(const FScopedSuppressActorImport& Other) = delete;`
- L264 _public prototype_ `FScopedSuppressActorImport& operator=(FScopedSuppressActorImport&& Other) = delete;`
- L267 _private member_ `bool bOldImportActorsValue = true;`
- L268 _private member_ `TWeakObjectPtr<UUsdStageImportOptions> Options;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API USDSTAGEIMPORTER_API`
- L254 _namespace_ `namespace UsdUtils`
- L271 _prototype_ `void AddAnalyticsAttributes(const UUsdStageImportOptions& Options, TArray<FAnalyticsEventAttribute>& InOutAttributes);` (scope `UsdUtils`)

### `Plugins/Importers/USDImporter/Source/USDStageImporter/Public/USDStageImporter.h` (Public)


#### class `UUsdStageImporter`  
`class UUsdStageImporter`  
_L11-22_
- L14 _public prototype_ `void ImportFromFile(FUsdStageImportContext& ImportContext);`
- L16 _public prototype_ `bool ReimportSingleAsset( FUsdStageImportContext& ImportContext, UObject* OriginalAsset, const FString& OriginalPrimPath, UObject*& OutReimportedAsset );`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API USDSTAGEIMPORTER_API`

### `Plugins/Importers/USDImporter/Source/USDStageImporter/Public/USDStageImporterModule.h` (Public)


#### class `IUsdStageImporterModule`  
`class IUsdStageImporterModule : public IModuleInterface`  
_L10-24_
- inherits: `IModuleInterface`
- L13 _public function_ `static inline IUsdStageImporterModule& Get()`
- L18 _public function_ `static inline bool IsAvailable()`
- L23 _public prototype_ `virtual class UUsdStageImporter* GetImporter() = 0;`

### `Plugins/Importers/USDImporter/Source/USDStageImporter/Public/Widgets/IUSDTreeViewItem.h` (Public)


#### class `IUsdTreeViewItem`  
`class IUsdTreeViewItem : public TSharedFromThis<IUsdTreeViewItem>`  
_L7-11_
- inherits: `TSharedFromThis<IUsdTreeViewItem>`
- L10 _public prototype_ `virtual ~IUsdTreeViewItem() = default;`

### `Plugins/Importers/USDImporter/Source/USDStageImporter/Public/Widgets/SUSDStagePreviewTree.h` (Public)


#### struct `FUsdPrimPreviewModel`  
`struct FUsdPrimPreviewModel`  
_L17-38_
- L20 _public member_ `FText Name;` — Prim's name
- L23 _public member_ `FText TypeName;` — Prim's type name (like "Mesh" or "Camera")
- L26 _public member_ `bool bShouldImport = true;` — Whether this prim should be imported or not
- L30 _public member_ `bool bPassesFilter = true;` — Only used to make filtering items with SUsdStagePreviewTree::CurrentFilterText a bit faster: This is not actually used to display anything
- L34 _public member_ `bool bIsExpanded = true;` — Our source of truth for expansion state. Whenever expansion changes on the views we write to this, and whenever we rebuild our views we write this to the tree's sparse infos about its items
- L36 _public member_ `int32 ParentIndex = INDEX_NONE;`
- L37 _public member_ `TArray<int32> ChildIndices;`

#### struct `FUsdPrimPreviewModelView`  
`struct FUsdPrimPreviewModelView : public IUsdTreeViewItem`  
_L40-46_
- inherits: `IUsdTreeViewItem`
- L42 _public member_ `int32 ModelIndex = INDEX_NONE;`
- L44 _public member_ `FUsdPrimPreviewModelViewWeak Parent;`
- L45 _public member_ `TArray<FUsdPrimPreviewModelViewRef> Children;`

#### class `SUsdStagePreviewTree`  
`class SUsdStagePreviewTree : public SUsdTreeView<FUsdPrimPreviewModelViewRef>`  
_L48-102_
- inherits: `SUsdTreeView<FUsdPrimPreviewModelViewRef>`
- L51 _public function_ `SLATE_BEGIN_ARGS(SUsdStagePreviewTree)`
- L54 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UE::FUsdStage& InStage);`
- L58 _public prototype_ `TArray<FString> GetSelectedFullPrimPaths() const;`
- L60 _public prototype_ `void SetFilterText(const FText& NewText);`
- L61 _public function_ `const FText& GetFilterText() const`
- L66 _public function_ `FUsdPrimPreviewModel& GetModel(int32 ModelIndex)`
- L70 _public function_ `const FUsdPrimPreviewModel& GetModel(int32 ModelIndex) const`
- L75 _public prototype_ `void CheckItemsRecursively(const TArray<FUsdPrimPreviewModelViewRef>& Items, bool bCheck);`
- L76 _public prototype_ `void ExpandItemsRecursively(const TArray<FUsdPrimPreviewModelViewRef>& Items, bool bExpand);`
- L80 _private prototype_ `virtual TSharedRef<ITableRow> OnGenerateRow(FUsdPrimPreviewModelViewRef InDisplayNode, const TSharedRef<STableViewBase>& OwnerTable) override;`
- L82 _private prototype_ `virtual void OnGetChildren(FUsdPrimPreviewModelViewRef InParent, TArray<FUsdPrimPreviewModelViewRef>& OutChildren) const override;`
- L84 _private prototype_ `virtual void SetupColumns() override;`
- L89 _private prototype_ `TArray<FUsdPrimPreviewModelViewRef> GetAncestorSelectedViews();` — Returns all selected model views, excluding child views of any other selected view. i.e. if both a child and an ancestor view are selected, the returned array will contain only the ancestor.
- L91 _private prototype_ `TSharedPtr<SWidget> ConstructPrimContextMenu();`
- L95 _private prototype_ `void RebuildModelViews();` — Rebuilds our RootItems array of FUsdPrimPreviewModelViewRefs based on CurrentFilterText and the ItemModels that pass the filter
- L98 _private member_ `FText CurrentFilterText;`
- L100 _private member_ `TArray<FUsdPrimPreviewModel> ItemModels;`
- L101 _private member_ `TMap<int32, FUsdPrimPreviewModelViewRef> ItemModelsToViews;`

#### class `SUsdStagePreviewTreeRow`  
`class SUsdStagePreviewTreeRow : public SUsdTreeRow<FUsdPrimPreviewModelViewRef>`  
_L105-121_
- inherits: `SUsdTreeRow<FUsdPrimPreviewModelViewRef>`
- desc: Custom row so that we can fetch the owning SUsdStagePreviewTree from the columns
- L108 _public function_ `SLATE_BEGIN_ARGS(SUsdStagePreviewTreeRow)`
- L111 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, FUsdPrimPreviewModelViewRef InTreeItem, const TSharedRef<STableViewBase>& OwnerTable, TSharedPtr<FSharedUsdTreeData> InSharedData );`
- L120 _public prototype_ `TSharedPtr<SUsdStagePreviewTree> GetOwnerTree() const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API USDSTAGEIMPORTER_API`
- L13 _typedef_ `using FUsdPrimPreviewModelViewRef = TSharedRef<struct FUsdPrimPreviewModelView>;`
- L14 _typedef_ `using FUsdPrimPreviewModelViewPtr = TSharedPtr<struct FUsdPrimPreviewModelView>;`
- L15 _typedef_ `using FUsdPrimPreviewModelViewWeak = TWeakPtr<struct FUsdPrimPreviewModelView>;`

### `Plugins/Importers/USDImporter/Source/USDStageImporter/Public/Widgets/SUSDTreeView.h` (Public)


#### class `FUsdTreeViewColumn`  
`class FUsdTreeViewColumn`  
_L13-22_
- L16 _public prototype_ `virtual ~FUsdTreeViewColumn() = default;`
- L18 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidget(const TSharedPtr<IUsdTreeViewItem> TreeItem, const TSharedPtr<ITableRow> TableRow) = 0;`
- L21 _public member_ `bool bIsMainColumn = false;`

#### struct `FSharedUsdTreeData`  
`struct FSharedUsdTreeData`  
_L24-27_
- L26 _public member_ `TMap<FName, TSharedRef<FUsdTreeViewColumn>> Columns;`

#### class `SUsdTreeView`  
`template<typename ItemType> class SUsdTreeView : public STreeView<ItemType>`  
_L30-60_
- inherits: `STreeView<ItemType>`
- L33 _public function_ `SLATE_BEGIN_ARGS(SUsdTreeView)`
- L36 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _public prototype_ `void AddColumn( FName ColumnKey, FText ColumnLabel, TSharedRef<FUsdTreeViewColumn> Column, SHeaderRow::FColumn::FArguments ColumnArguments = SHeaderRow::FColumn::FArguments() );`
- L46 _public prototype_ `virtual void SetupColumns() = 0;`
- L48 _public prototype_ `virtual TSharedRef<ITableRow> OnGenerateRow(ItemType InDisplayNode, const TSharedRef<STableViewBase>& OwnerTable) = 0;`
- L49 _public prototype_ `virtual void OnGetChildren(ItemType InParent, TArray<ItemType>& OutChildren) const = 0;`
- L51 _public function_ `virtual void OnTreeItemScrolledIntoView(ItemType TreeItem, const TSharedPtr<ITableRow>& Widget)`
- L56 _protected member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;`
- L57 _protected member_ `TArray<ItemType> RootItems;`
- L59 _protected member_ `TSharedPtr<FSharedUsdTreeData> SharedData;`
- L63 _function_ `template<typename ItemType> inline void SUsdTreeView<ItemType>::AddColumn( FName ColumnKey, FText ColumnLabel, TSharedRef<FUsdTreeViewColumn> Column, SHeaderRow::FColumn::FArguments ColumnArguments )`
- L79 _function_ `template<typename ItemType> inline void SUsdTreeView<ItemType>::Construct(const FArguments& InArgs)`

#### class `SUsdTreeRow`  
`template<typename ItemType> class SUsdTreeRow : public SMultiColumnTableRow<ItemType>`  
_L96-141_
- inherits: `SMultiColumnTableRow<ItemType>`
- L99 _public typedef_ `typedef typename STableRow<ItemType>::FOnCanAcceptDrop FUsdOnCanAcceptDrop;`
- L100 _public typedef_ `typedef typename STableRow<ItemType>::FOnAcceptDrop FUsdOnAcceptDrop;`
- L102 _public function_ `SLATE_BEGIN_ARGS(SUsdTreeRow)`
- L105 _public function_ `SLATE_EVENT(FUsdOnCanAcceptDrop, OnCanAcceptDrop) SLATE_EVENT(FUsdOnAcceptDrop, OnAcceptDrop) SLATE_EVENT(FOnDragDetected, OnDragDetected) SLATE_EVENT(FOnTableRowDragEnter, OnDragEnter) SLATE_EVENT(FOnTableRowDragLeave, OnDragLeave) SLATE_EVENT(FOnTableRowDrop, OnDrop) SLATE_END_ARGS() void Construct( const FArguments& InArgs, ItemType InTreeItem, const TSharedRef<STableViewBase>& OwnerTable, TSharedPtr<FSharedUsdTreeData> InSharedData )`
- L136 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the tree row.
- L139 _private member_ `TSharedPtr<typename ItemType::ElementType> TreeItem;`
- L140 _private member_ `TSharedPtr<FSharedUsdTreeData> SharedData;`
- L144 _function_ `template<typename ItemType> inline TSharedRef<SWidget> SUsdTreeRow<ItemType>::GenerateWidgetForColumn(const FName& ColumnName)`
