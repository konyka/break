# Plugins / USDUtilities

- module root: `Plugins/Runtime/USDCore/Source/USDUtilities`
- headers: 20; symbols: 1057
- symbol kinds: class=14, delegate=1, enum=15, enumerator=80, function=32, macro=10, member=174, namespace=51, prototype=637, struct=25, typedef=17, variable=1
- PrivateDependencyModuleNames: CinematicCamera, ControlRig, DesktopPlatform, DeveloperSettings, Engine, Foliage, GeometryCache, HairStrandsCore, IntelTBB, Landscape, LiveLinkComponents, MaterialBaking, MaterialEditor, MeshDescription, MeshUtilities, MessageLog, MovieScene, MovieSceneTracks, OpenSubdiv, PropertyEditor, RHI, RenderCore, SkeletalMeshDescription, Slate, SlateCore, StaticMeshDescription, TextureUtilitiesCommon, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, HairStrandsCore, MaterialX, USDClasses, UnrealUSDWrapper

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/Objects/USDInfoCache.h` (Public)


#### enum `ECollapsingType`  
`enum class ECollapsingType`  
_L20-24_
- L22 _public enumerator_ `Assets`
- L23 _public enumerator_ `Components`

#### class `FUsdInfoCache`  
`class FUsdInfoCache`  
_L36-116_
- desc: Caches information about a specific USD Stage
- L39 _public prototype_ `FUsdInfoCache();`
- L40 _public prototype_ `virtual ~FUsdInfoCache();`
- L42 _public prototype_ `void CopyImpl(const FUsdInfoCache& Other);`
- L44 _public prototype_ `bool Serialize(FArchive& Ar);`
- L47 _public prototype_ `bool ContainsInfoAboutPrim(const UE::FSdfPath& Path) const;` — Returns whether we contain any info about prim at 'Path' at all
- L50 _public prototype_ `TArray<UE::FSdfPath> GetChildren(const UE::FSdfPath& ParentPath) const;` — Retrieves the children of a prim from the cached information
- L52 _public prototype_ `void RebuildCacheForSubtree(const UE::FUsdPrim& Prim, FUsdSchemaTranslationContext& Context);`
- L53 _public prototype_ `void RebuildCacheForSubtrees(const TArray<UE::FSdfPath>& SubtreeRoots, FUsdSchemaTranslationContext& Context);`
- L55 _public prototype_ `void Clear();`
- L56 _public prototype_ `bool IsEmpty();`
- L59 _public prototype_ `bool IsPathCollapsed(const UE::FSdfPath& Path, ECollapsingType CollapsingType) const;`
- L60 _public prototype_ `bool DoesPathCollapseChildren(const UE::FSdfPath& Path, ECollapsingType CollapsingType) const;`
- L63 _public prototype_ `UE::FSdfPath UnwindToNonCollapsedPath(const UE::FSdfPath& Path, ECollapsingType CollapsingType) const;` — Returns Path in case it represents an uncollapsed prim, or returns the path to the prim that collapsed it
- L69 _public prototype_ `TSet<UE::FSdfPath> GetMainPrims(const UE::FSdfPath& AuxPrimPath) const;` — Returns the paths to prims that, when translated into assets or components, also require reading the prim at 'Path'. e.g. providing the path to a Shader prim will return the paths to all Material prims for which the translation involves reading that particular Shader.
- L73 _public prototype_ `TSet<UE::FSdfPath> GetAuxiliaryPrims(const UE::FSdfPath& MainPrimPath) const;` — The inverse of the function above: Provide it with the path to a Material prim and it will return the set of paths to all Shader prims that need to be read to translate that Material prim into material assets
- L76 _public prototype_ `TSet<UE::FSdfPath> GetMaterialUsers(const UE::FSdfPath& Path) const;`
- L77 _public prototype_ `bool IsMaterialUsed(const UE::FSdfPath& Path) const;`
- L84 _public prototype_ `TOptional<uint64> GetSubtreeVertexCount(const UE::FSdfPath& Path);` — Provides the total vertex or material slots counts for each prim *and* its subtree. This is built inside RebuildCacheForSubtree, so it will factor in the used Context's bMergeIdenticalMaterialSlots. Note that these aren't affected by actual collapsing: A prim that doesn't collapse its children will still provide the total sum of vertex counts of its entire subtree when queried
- L85 _public prototype_ `TOptional<uint64> GetSubtreeMaterialSlotCount(const UE::FSdfPath& Path);`
- L86 _public prototype_ `TOptional<TArray<UsdUtils::FUsdPrimMaterialSlot>> GetSubtreeMaterialSlots(const UE::FSdfPath& Path);`
- L92 _public prototype_ `void ResetTranslatedPrototypes();` — Marks/checks if the provided path to a prototype prim is already being translated. This is used during scene translation with instanceables, so that the schema translators can early out in case they have been created to translate multiple instances of the same prototype
- L93 _public prototype_ `bool IsPrototypeTranslated(const UE::FSdfPath& PrototypePath);`
- L94 _public prototype_ `void MarkPrototypeAsTranslated(const UE::FSdfPath& PrototypePath);`
- L108 _private prototype_ `TOptional<bool> CanXformableSubtreeBeCollapsed(const UE::FSdfPath& RootPath, FUsdSchemaTranslationContext& Context) const;` — Returns true if every prim on the subtree below RootPath (including the RootPath prim itself) returns true for CanBeCollapsed(), according to their own schema translators. WARNING: This is intended for internal use, and exclusively during the actual info cache build process as it will need to query the prim/stage directly. Calling it after the info cache build may yield back an empty optional, meaning it is unknown at this point whether the prim CanBeCollapsed or not. In general, you shouldn't call this, but just use "IsPathCollapsed" or "DoesPathCollapseChildren" instead.
- L112 _private prototype_ `bool IsPotentialGeometryCacheRoot(const UE::FUsdPrim& Prim) const;` — Analogous to the function above, this overload of IsPotentialGeometryCacheRoot is meant for internal use, and exists because during the info cache build (in some contexts) we can fill in this geometry cache information on-demand, for better performance.
- L115 _private member_ `TUniquePtr<FUsdInfoCacheImpl> Impl;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API USDUTILITIES_API`
- L14 _namespace_ `namespace UE`
- L26 _namespace_ `namespace UsdUtils`

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/Objects/USDPrimLinkCache.h` (Public)


#### class `FUsdPrimLinkCache`  
`class FUsdPrimLinkCache`  
_L18-88_
- L23 _public prototype_ `FUsdPrimLinkCache();`
- L24 _public prototype_ `~FUsdPrimLinkCache();`
- L27 _public prototype_ `void Serialize(FArchive& Ar);`
- L31 _public prototype_ `bool ContainsInfoAboutPrim(const UE::FSdfPath& Path) const;` — Returns whether we contain any info about prim at 'Path' at all
- L33 _public prototype_ `void Clear();`
- L34 _public prototype_ `bool IsEmpty();`
- L37 _public prototype_ `void LinkAssetToPrim(const UE::FSdfPath& Path, UObject* Asset);`
- L38 _public prototype_ `void UnlinkAssetFromPrim(const UE::FSdfPath& Path, UObject* Asset);`
- L40 _public prototype_ `TArray<TWeakObjectPtr<UObject>> RemoveAllAssetPrimLinks(const UE::FSdfPath& Path);`
- L41 _public prototype_ `TArray<UE::FSdfPath> RemoveAllAssetPrimLinks(const UObject* Asset);`
- L42 _public prototype_ `void RemoveAllAssetPrimLinks();`
- L44 _public prototype_ `TArray<TWeakObjectPtr<UObject>> GetAllAssetsForPrim(const UE::FSdfPath& Path) const;`
- L47 _public function_ `template<typename T = UObject> T* GetSingleAssetForPrim(const UE::FSdfPath& Path) const`
- L65 _public function_ `template<typename T> TArray<T*> GetAssetsForPrim(const UE::FSdfPath& Path) const`
- L83 _public prototype_ `TArray<UE::FSdfPath> GetPrimsForAsset(const UObject* Asset) const;`
- L84 _public prototype_ `TMap<UE::FSdfPath, TArray<TWeakObjectPtr<UObject>>> GetAllAssetPrimLinks() const;`
- L87 _private member_ `TUniquePtr<FUsdPrimLinkCacheImpl> Impl;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API USDUTILITIES_API`
- L13 _namespace_ `namespace UE`

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/Objects/USDSchemaTranslator.h` (Public)


#### class `FRegisteredSchemaTranslatorHandle`  
`class FRegisteredSchemaTranslatorHandle`  
_L43-80_
- L46 _public function_ `FRegisteredSchemaTranslatorHandle() : Id(CurrentSchemaTranslatorId++)`
- L51 _public function_ `explicit FRegisteredSchemaTranslatorHandle(const FString& InSchemaName) : FRegisteredSchemaTranslatorHandle()`
- L57 _public function_ `int32 GetId() const`
- L61 _public function_ `void SetId(int32 InId)`
- L66 _public function_ `const FString& GetSchemaName() const`
- L70 _public function_ `void SetSchemaName(const FString& InSchemaName)`
- L76 _private member_ `static int32 CurrentSchemaTranslatorId;`
- L78 _private member_ `FString SchemaName;`
- L79 _private member_ `int32 Id;`

#### class `FUsdSchemaTranslatorRegistry`  
`class FUsdSchemaTranslatorRegistry`  
_L82-131_
- L84 _private typedef_ `using FCreateTranslator = TFunction<TSharedRef<FUsdSchemaTranslator>(TSharedRef<FUsdSchemaTranslationContext>, const UE::FUsdTyped&)>;`
- L85 _private typedef_ `using FSchemaTranslatorsStack = TArray<FRegisteredSchemaTranslator, TInlineAllocator<1>>;`
- L88 _public prototype_ `static FUsdSchemaTranslatorRegistry& Get();`
- L93 _public prototype_ `TSharedPtr<FUsdSchemaTranslator> CreateTranslatorForSchema( TSharedRef<FUsdSchemaTranslationContext> InTranslationContext, const UE::FUsdTyped& InSchema );` — Returns the translator to use for InSchema
- L104 _public function_ `template<typename SchemaTranslatorType> FRegisteredSchemaTranslatorHandle Register(const FString& SchemaName)` — Registers SchemaTranslatorType to translate schemas of type SchemaName. Registration order is important as the last to register for a given schema will be the one handling it. Thus, you will want to register base schemas before the more specialized ones.
- L115 _public prototype_ `void Unregister(const FRegisteredSchemaTranslatorHandle& TranslatorHandle);`
- L117 _public prototype_ `int32 GetExternalSchemaTranslatorCount();`
- L120 _protected prototype_ `FRegisteredSchemaTranslatorHandle Register(const FString& SchemaName, FCreateTranslator CreateFunction);`
- L122 _protected prototype_ `FSchemaTranslatorsStack* FindSchemaTranslatorStack(const FString& SchemaName);`
- L124 _protected member_ `TArray<TPair<FString, FSchemaTranslatorsStack>> RegisteredSchemaTranslators;`
- L129 _private prototype_ `void ResetExternalTranslatorCount();`
- L130 _private member_ `int32 ExternalSchemaTranslatorCount = 0;`

#### class `FRegisteredSchemaTranslator`  
`class FRegisteredSchemaTranslator`  
_L133-140_
- L135 _private typedef_ `using FCreateTranslator = TFunction<TSharedRef<FUsdSchemaTranslator>(TSharedRef<FUsdSchemaTranslationContext>, const UE::FUsdTyped&)>;`
- L138 _public member_ `FRegisteredSchemaTranslatorHandle Handle;`
- L139 _public member_ `FCreateTranslator CreateFunction;`

#### struct `FUsdSchemaTranslationContext`  
`struct FUsdSchemaTranslationContext : public TSharedFromThis<FUsdSchemaTranslationContext>`  
_L142-298_
- inherits: `TSharedFromThis<FUsdSchemaTranslationContext>`
- L144 _public prototype_ `explicit FUsdSchemaTranslationContext(const UE::FUsdStage& InStage);`
- L145 _public prototype_ `explicit FUsdSchemaTranslationContext(const UE::FUsdStage& InStage, UUsdAssetCache3& InAssetCache);`
- L148 _public member_ `bool bIsImporting = false;` — True if we're a context created by the USDStageImporter to fully import to persistent assets and actors
- L151 _public member_ `bool bIsJustRepopulatingLevelSequence = false;` — True if we're just re-adding animations onto the LevelSequence, and not creating/updating components
- L157 _public member_ `bool bIsBuildingInfoCache = false;` — True if we're building the InfoCache assigned to this context. This usually means we shouldn't query it for information, and should instead compute it manually so that it can be cached
- L160 _public member_ `UE::FUsdStage Stage;` — pxr::UsdStage we're translating from
- L163 _public member_ `ULevel* Level = nullptr;` — Level to spawn actors in
- L166 _public member_ `EObjectFlags ObjectFlags;` — Flags used when creating UObjects
- L169 _public member_ `USceneComponent* ParentComponent = nullptr;` — The parent component when translating children
- L172 _public member_ `float Time = 0.f;` — The time at which we are translating
- L175 _public member_ `EUsdPurpose PurposesToLoad;` — We're only allowed to load prims with purposes that match these flags
- L178 _public member_ `FName RenderContext;` — The render context to use when translating materials
- L181 _public member_ `FName MaterialPurpose;` — The material purpose to use when translating material bindings
- L184 _public member_ `EUsdRootMotionHandling RootMotionHandling = EUsdRootMotionHandling::NoAdditionalRootMotion;` — Describes what to add to the root bone animation within generated AnimSequences, if anything
- L187 _public member_ `EUsdCollisionType FallbackCollisionType = EUsdCollisionType::ConvexHull;` — What type of collision to use for static meshes generated from Prims that don't have physics schemas applied
- L190 _public member_ `EGeometryCacheImport GeometryCacheImport = EGeometryCacheImport::Never;` — How geometry caches are handled in the stage workflow
- L193 _public member_ `int32 SubdivisionLevel = 0;` — Subdivision level to use for all subdivision meshes on the opened stage. 0 means "don't subdivide"
- L195 _public member_ `FUsdMetadataImportOptions MetadataOptions;`
- L198 _public member_ `int32 NaniteTriangleThreshold;` — If a generated UStaticMesh has at least this many triangles we will attempt to enable Nanite
- L201 _public member_ `TStrongObjectPtr<UUsdAssetCache3> UsdAssetCache;` — Where the translated assets will be stored
- L204 _public member_ `FUsdInfoCache* UsdInfoCache;` — Caches various information about prims that are expensive to query
- L207 _public member_ `FUsdPrimLinkCache* PrimLinkCache;` — Caches which assets were generated from which USD prims
- L210 _public member_ `TSharedPtr<UE::FUsdGeomBBoxCache> BBoxCache;` — Bounding box cache used for the USD stage in case we have to spawn bounds components
- L213 _public member_ `UsdUtils::FBlendShapeMap* BlendShapesByPath = nullptr;` — Where we place imported blend shapes, if available
- L222 _public member_ `TMap<UTexture*, TSet<UMaterialInterface*>> TextureToUserMaterials;` — Sometimes we must upgrade a material from non-VT to VT, and so upgrade all of its textures to VT (and then upgrade all materials that use them to VT, etc.). This member lets us cache which generated materials use which generated textures in order to help with that. Material parsing is synchronous. If we ever upgrade it to paralllel/async-task-based, we'll need a mutex around this member.
- L228 _public member_ `EUsdDefaultKind KindsToCollapse = EUsdDefaultKind::Component | EUsdDefaultKind::Subcomponent;` — Whether to try to combine individual assets and components of the same type on a kind-per-kind basis, like multiple Mesh prims into a single Static Mesh
- L234 _public member_ `bool bUsePrimKindsForCollapsing = true;` — Use KindsToCollapse to determine when to collapse prim subtrees or not (defaults to enabled). Disable this if you want to prevent collapsing, or to control it manually by right-clicking on individual prims.
- L240 _public member_ `bool bMergeIdenticalMaterialSlots = true;` — Identical material slots will be combined into a single slot if this is enabled. This is only performed in the context of mesh collapsing, or when parsing LOD variant sets (see bInterpretLODs)
- L247 _public member_ `bool bShareAssetsForIdenticalPrims = true;` — If true, whenever two prims would have generated identical UAssets (like identical StaticMeshes or materials) then only one instance of that asset is generated, and the asset is shared by the components generated for both prims. If false, we will always generate a dedicated asset for each prim.
- L253 _public member_ `bool bAllowInterpretingLODs = true;` — If true, prims with a "LOD" variant set, and "LOD0", "LOD1", etc. variants containing each a prim can be parsed into a single UStaticMesh asset with multiple LODs
- L256 _public member_ `bool bAllowParsingSkeletalAnimations = true;` — If true, we will also try creating UAnimSequence skeletal animation assets when parsing Skeleton prims
- L259 _public member_ `bool bAllowParsingGroomAssets = true;` — If true, means we will try generating GroomAssets, GroomCaches and GroomBindings
- L262 _public member_ `bool bAllowParsingSparseVolumeTextures = true;` — If true, means we will try generating Sparse Volume Textures
- L265 _public member_ `bool bAllowParsingSounds = true;` — If true, means we will try generating SoundWave assets from sound files referenced by UsdMediaSpatialAudio prims
- L268 _public member_ `bool bTranslateOnlyUsedMaterials = false;` — Skip the import of materials that aren't being used by any prim on the stage
- L274 _public member_ `bool bAllowRecomputingMaterialOverrides = true;` — We set material overrides within UsdGeomXformableTranslator::UpdateComponents when this flag is set. Since that is a non-trivial amount of computation, this flag can be disabled for situations where material overrides shouldn't change (e.g. animating components)
- L277 _public member_ `TArray<FHairGroupsInterpolation> GroomInterpolationSettings;` — Groom group interpolation settings
- L288 _public member_ `bool bSequencerIsAnimating = false;` — True if the Sequencer is currently opened and animating the stage level sequence. Its relevant to know this because some translator ::UpdateComponents overloads may try to animate their components by themselves, which could be wasteful and glitchy in case the sequencer is opened: It will likely also have an animation track for that component and on next editor tick would override the animation with what is sampled from the track. In the future we'll likely get rid of the "Time" track on the generated LevelSequence, at which point we can remove this
- L290 _public function_ `bool IsValid() const`
- L295 _public prototype_ `void CompleteTasks();`
- L297 _public member_ `TArray<TSharedPtr<FUsdSchemaTranslatorTaskChain>> TranslatorTasks;`

#### enum `ESchemaTranslationStatus`  
`enum class ESchemaTranslationStatus`  
_L300-305_
- L302 _public enumerator_ `Pending`
- L303 _public enumerator_ `InProgress`
- L304 _public enumerator_ `Done`

#### enum `ESchemaTranslationLaunchPolicy`  
`enum class ESchemaTranslationLaunchPolicy`  
_L307-320_
- L313 _public enumerator_ `ExclusiveSync` — Task will run on main thread, with the guarantee that no other tasks are being run concurrently to it. Note: This is slow, and should not be used for realtime workflows (i.e. USDStage editor)
- L316 _public enumerator_ `Sync` — Task will run on main thread, while other tasks may be running concurrently
- L319 _public enumerator_ `Async` — Task may run on another thread, while other tasks may be running concurrently

#### class `FUsdSchemaTranslator`  
`class FUsdSchemaTranslator`  
_L322-394_
- L325 _public function_ `explicit FUsdSchemaTranslator(TSharedRef<FUsdSchemaTranslationContext> InContext, const UE::FUsdTyped& InSchema) : PrimPath(InSchema.GetPrim().GetPrimPath()) , Context(InContext)`
- L331 _public prototype_ `virtual ~FUsdSchemaTranslator() = default;`
- L333 _public function_ `virtual void CreateAssets()`
- L337 _public function_ `virtual USceneComponent* CreateComponents()`
- L341 _public function_ `virtual void UpdateComponents(USceneComponent* SceneComponent)`
- L345 _public function_ `virtual bool CollapsesChildren(ECollapsingType CollapsingType) const`
- L355 _public function_ `virtual TSet<UE::FSdfPath> CollectAuxiliaryPrims() const` — Returns the set of prims that also need to be read in order to translate the prim at PrimPath. Note: This function never needs to return PrimPath itself, as the query function in the InfoCache will always append it to the result
- L360 _public prototype_ `bool IsCollapsed(ECollapsingType CollapsingType) const;`
- L361 _public function_ `virtual bool CanBeCollapsed(ECollapsingType CollapsingType) const`
- L377 _public prototype_ `bool ShouldSkipInstance() const;` — This checks if the current prim is an instance, and if so, whether its prototype is already being translated. Returns false otherwise. WARNING: In case this prim is an instance but the prototype is not being translated yet, running this check will also mark that prototype as being currently translated on the info cache! The intent here is that the first schema translator that calls this for a prototype will "own" the translation for that prototype, and any subsequent calls by other schema translators with the same prototype will just return true so they can early out.
- L384 _public prototype_ `UE::FSdfPath GetPrototypePrimPath() const;` — If this prim is a prototype or an instance proxy, returns the prototype path (or the path to the analogue prim in the prototype's hierarchy). If this prim is just a regular non-instance prim, this just returns our PrimPath member.
- L386 _public function_ `UE::FUsdPrim GetPrim() const`
- L392 _protected member_ `UE::FSdfPath PrimPath;`
- L393 _protected member_ `TSharedRef<FUsdSchemaTranslationContext> Context;`

#### struct `FSchemaTranslatorTask`  
`struct FSchemaTranslatorTask`  
_L396-428_
- L398 _public function_ `explicit FSchemaTranslatorTask(ESchemaTranslationLaunchPolicy InPolicy, TFunction<bool()> InCallable) : Callable(InCallable) , LaunchPolicy(InPolicy) , bIsDone(false)`
- L404 _public prototype_ `FSchemaTranslatorTask(const FSchemaTranslatorTask& Other) = delete;`
- L406 _public member_ `TFunction<bool()> Callable;`
- L407 _public member_ `TOptional<TFuture<bool>> Result;`
- L408 _public member_ `TSharedPtr<FSchemaTranslatorTask> Continuation;`
- L410 _public member_ `ESchemaTranslationLaunchPolicy LaunchPolicy;`
- L412 _public member_ `FThreadSafeBool bIsDone;`
- L414 _public prototype_ `void Start();`
- L415 _public prototype_ `void StartIfAsync();`
- L417 _public function_ `bool IsStarted() const`
- L422 _public prototype_ `bool DoWork();`
- L424 _public function_ `bool IsDone() const`

#### class `FUsdSchemaTranslatorTaskChain`  
`class FUsdSchemaTranslatorTaskChain`  
_L430-442_
- L433 _public prototype_ `virtual ~FUsdSchemaTranslatorTaskChain() = default;`
- L435 _public prototype_ `FUsdSchemaTranslatorTaskChain& Do(ESchemaTranslationLaunchPolicy Policy, TFunction<bool()> Callable);`
- L436 _public prototype_ `FUsdSchemaTranslatorTaskChain& Then(ESchemaTranslationLaunchPolicy Policy, TFunction<bool()> Callable);`
- L438 _public prototype_ `ESchemaTranslationStatus Execute(bool bExclusiveSyncTasks = false);`
- L441 _private member_ `TSharedPtr<FSchemaTranslatorTask> CurrentTask;`

#### Free symbols / members of external scopes

- L38 _namespace_ `namespace UE`
- L108 _function_ `` (scope `FUsdSchemaTranslatorRegistry::Register`)

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDAttributeUtils.h` (Public)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L23 _namespace_ `namespace UsdUtils`
- L27 _prototype_ `bool MuteAttribute(UE::FUsdAttribute& Attribute, const UE::FUsdStage& Stage);` (scope `UsdUtils`) — Adds a "Muted" CustomData entry to the attribute at the stage's UE state sublayer, which will prevent it from being animated when loaded into UE
- L30 _prototype_ `bool UnmuteAttribute(UE::FUsdAttribute& Attribute, const UE::FUsdStage& Stage);` (scope `UsdUtils`) — Removes the "Muted" CustomData entry from the attribute at the stage's UE state sublayer, letting it be animated when loaded into UE
- L34 _prototype_ `bool IsAttributeMuted(const UE::FUsdAttribute& Attribute, const UE::FUsdStage& Stage);` (scope `UsdUtils`) — Returns whether this attribute has the "Muted" CustomData on the stage's UE state sublayer, meaning it shouldn't be animated when loaded into UE
- L37 _prototype_ `bool HasAuthoredDefaultOpinion(const UE::FUsdAttribute& Attribute);` (scope `UsdUtils`) — Returns true only if the attribute has an authored default opinion. If the attribute only has timeSamples, splines, or no opinion at all, this will return false
- L40 _prototype_ `bool HasAuthoredAnimatedOpinion(const UE::FUsdAttribute& Attribute);` (scope `UsdUtils`) — Returns true only if the attribute has an authored animated (timeSample or splines) opinion. If the attribute only has a default opinion (or no opinion at all) this will return false
- L47 _prototype_ `bool ClearAllTimeSamples(const pxr::UsdAttribute& Attribute);` (scope `UsdUtils`) — Calls pxr::UsdAttribute::GetTimeSamples(), and then pxr::UsdAttribute::ClearAtTime() for each timeSample value, clearing all timeSample opinions at the current edit target.
- L57 _prototype_ `void NotifyIfOverriddenOpinion(const pxr::UsdProperty& Property);` (scope `UsdUtils`) — If Attribute has opinions authored on layers stronger than the current edit target this will emit a warning to the user, indicating that the new value may not be visible on the USD Stage, and may cease to be visible on the UE level after a reload. Use this after setting any attribute: This function does nothing in case the Stage's current edit target has the strongest opinion for the attribute already
- L64 _prototype_ `bool NotifyIfInstanceProxy(const pxr::UsdPrim& Prim);` (scope `UsdUtils`) — Generally we are not allowed to author opinions inside instanceables. Our actual results when doing that will range from USD coding errors to seeming like nothing has happened on the stage. This will show a warning and return true if Prim is an instance, letting us avoid those scenarios
- L67 _prototype_ `UE::FUsdAttribute GetStrongestAttribute(const TArray<UE::FUsdAttribute>& Attributes, double TimeCode);` (scope `UsdUtils`) — Returns the attribute that has the strongest spec, acrosss the provided Attributes array

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDConversionUtils.h` (Public)


#### enum `UsdUtils::ECollapsingPreference`  
`enum class ECollapsingPreference : uint8`  
_L281-286_
- L283 _public enumerator_ `Default`
- L284 _public enumerator_ `Allow`
- L285 _public enumerator_ `Never`

#### enum `UsdUtils::ESparseVolumeAttributesFormat`  
`enum class ESparseVolumeAttributesFormat : uint8`  
_L314-319_
- desc: Copy-pasted from OpenVDBImportOptions.h because that is editor-only, and we want to avoid spreading more #if WITH_EDITORs around
- L316 _public enumerator_ `Unorm8 = 0`
- L317 _public enumerator_ `Float16 = 1`
- L318 _public enumerator_ `Float32 = 2`

#### struct `UsdUtils::FVolumePrimInfo`  
`struct FVolumePrimInfo`  
_L321-337_
- L323 _public member_ `FString SourceVDBFilePath;`
- L325 _public member_ `TArray<double> TimeSamplePathTimeCodes;`
- L326 _public member_ `TArray<int32> TimeSamplePathIndices;`
- L327 _public member_ `TArray<FString> TimeSamplePaths;` — First item may equal SourceVDBFilePath. May have duplicate entries
- L330 _public member_ `TArray<FString> VolumeFieldNames;` — Fields on the Volume prim that were connected to this .vdb file
- L331 _public member_ `TArray<FString> SourceOpenVDBAssetPrimPaths;`
- L334 _public member_ `TMap<FString, TMap<FString, FString>> GridNameToChannelComponentMapping;` — e.g. {'velocity': {'AttributesA.R': 'X', 'AttributesA.G': 'Y', 'AttributesA.B': 'Z'}}
- L335 _public member_ `TOptional<ESparseVolumeAttributesFormat> AttributesAFormat;`
- L336 _public member_ `TOptional<ESparseVolumeAttributesFormat> AttributesBFormat;`

#### Free symbols / members of external scopes

- L41 _typedef_ `using UsdStageRefPtr = TfRefPtr<UsdStage>;`
- L46 _typedef_ `using SdfPrimSpecHandle = SdfHandle<SdfPrimSpec>;`
- L64 _namespace_ `namespace UE`
- L69 _namespace_ `namespace UsdUtils`
- L74 _namespace_ `namespace UsdUtils`
- L77 _function_ `template<typename T> T* FindOrCreateObject(UObject* InParent, const FString& InName, EObjectFlags Flags)` (scope `UsdUtils`)
- L97 _prototype_ `FString AddHashToPrimPath(const FString& PrimPath);` (scope `UsdUtils`) — Adds or removes a case sensitive hash suffix to the PrimPath string. We mainly use this to make sure that prim paths that differ only by case don't cause collisions inside case insensitive TMaps and TSets. We can sometimes use the case sensitive versions of those containers (see USDSetUtils.h), but sometimes that is not possible, due to backwards compatibility or due to the container being a UPROPERTY
- L98 _prototype_ `FString RemoveHashFromPrimPath(const FString& HashedPrimPath);` (scope `UsdUtils`)
- L102 _prototype_ `template<typename ValueType> ValueType GetUsdValue(const pxr::UsdAttribute& Attribute, pxr::UsdTimeCode TimeCode);` (scope `UsdUtils`)
- L104 _prototype_ `pxr::TfToken GetUsdStageUpAxis(const pxr::UsdStageRefPtr& Stage);` (scope `UsdUtils`)
- L105 _prototype_ `EUsdUpAxis GetUsdStageUpAxisAsEnum(const pxr::UsdStageRefPtr& Stage);` (scope `UsdUtils`)
- L107 _prototype_ `void SetUsdStageUpAxis(const pxr::UsdStageRefPtr& Stage, pxr::TfToken Axis);` (scope `UsdUtils`)
- L108 _prototype_ `void SetUsdStageUpAxis(const pxr::UsdStageRefPtr& Stage, EUsdUpAxis Axis);` (scope `UsdUtils`)
- L110 _prototype_ `double GetUsdStageMetersPerUnit(const pxr::UsdStageRefPtr& Stage);` (scope `UsdUtils`)
- L111 _prototype_ `void SetUsdStageMetersPerUnit(const pxr::UsdStageRefPtr& Stage, double MetersPerUnit);` (scope `UsdUtils`)
- L113 _prototype_ `int32 GetUsdStageNumFrames(const pxr::UsdStageRefPtr& Stage);` (scope `UsdUtils`)
- L124 _prototype_ `int64 GetUsdUtilsStageCacheStageId(const pxr::UsdStageRefPtr& Stage);` (scope `UsdUtils`) — Simple API to interact with the UsdUtils' singleton StageCache from modules not setup to interact with the USD SDK directly like Interchange's Import module. Note: We do this instead of having a UsdStageCache wrapper type because when dealing with stage caches we are realistically going to be using the UsdUtils' singleton instance. The wrapper types all *own* the USD version of their objects, and so having the FUsdStageCache wrapper *refer* to an external, existing instance of the USD version of itself instead (the singleton instance) would likely be very misleading and confusing.
- L125 _prototype_ `UE::FUsdStage FindUsdUtilsStageCacheStageId(int64 Id);` (scope `UsdUtils`)
- L126 _prototype_ `int64 InsertStageIntoUsdUtilsStageCache(const pxr::UsdStageRefPtr& Stage);` (scope `UsdUtils`)
- L127 _prototype_ `bool RemoveStageFromUsdUtilsStageCache(int64 StageId);` (scope `UsdUtils`)
- L129 _prototype_ `bool HasCompositionArcs(const pxr::UsdPrim& Prim);` (scope `UsdUtils`)
- L130 _prototype_ `bool HasCompositionArcs(const pxr::SdfPrimSpecHandle& PrimSpec);` (scope `UsdUtils`)
- L132 _prototype_ `UClass* GetActorTypeForPrim(const pxr::UsdPrim& Prim);` (scope `UsdUtils`)
- L133 _prototype_ `UClass* GetComponentTypeForPrim(const pxr::UsdPrim& Prim);` (scope `UsdUtils`)
- L136 _prototype_ `FString GetSchemaNameForComponent(const USceneComponent& Component);` (scope `UsdUtils`) — Returns the USD schema name that should be used when exporting Component (e.g. "Xform", "Mesh", "Camera", etc.)
- L148 _prototype_ `FString GetPrimPathForObject( const UObject* ActorOrComponent, const FString& ParentPrimPath = TEXT(""), bool bUseActorFolders = false, const FString& RootPrimName = TEXT("Root") );` (scope `UsdUtils`) — Returns a prim path to use when exporting a given ActorOrComponent, assuming we're exporting according to the component attachment hierarchy. e.g. We have a top-level actor with label "Actor" with an attached child actor "Child" that has a component "Comp1" attached to its root, and "Comp2" attached to "Comp1". If Comp2 is provided to this function, it will return "/<RootPrimName>/Actor/Child/Comp1/Comp2". The actor label is always used in place of the root component name. ParentPrimPath is optional, and without it the function will recurse upwards and build the full path all the way to the root. Actor folders are handled just like if they were actors/components
- L155 _prototype_ `TUsdStore<pxr::TfToken> GetUVSetName(int32 UVChannelIndex);` (scope `UsdUtils`)
- L169 _prototype_ `TArray<TUsdStore<pxr::UsdGeomPrimvar>> GetUVSetPrimvars( const pxr::UsdPrim& UsdPrim, int32 MaxNumPrimvars = USD_PREVIEW_SURFACE_MAX_UV_SETS );` (scope `UsdUtils`) — Gets the primvars that should be used as UV sets, per index, for this UsdPrim. This will return between 0 and MaxNumPrimvars primvars, where the first item of array is the primvar that should be used for UV index 0 (if any), the second the primvar that should be used for UV set 1, etc. In case there are more than MaxNumPrimvars available primvars, the returned list will contain all the 'texCoord2f' role primvars (sorted lexicographically), followed by the regular float2 primvars (also separately sorted lexicographically). @param UsdPrim - UsdPrim that contains primvars that can be used as texture coordinates. @param MaxNumPrimvars - Maximum number of primvars to return from this function. @return Array of up to MaxNumPrimvars primvars sorted by priority (most important come first)
- L190 _prototype_ `TArray<TUsdStore<pxr::UsdGeomPrimvar>> AssemblePrimvarsIntoUVSets( const TArray<TUsdStore<pxr::UsdGeomPrimvar>>& AllMeshUVPrimvars, const TMap<FString, int32>& AllowedPrimvarsToUVIndex );` (scope `UsdUtils`) — Rearranges an array of primvars into another array of up to USD_PREVIEW_SURFACE_MAX_UV_SETS primvars, describing which primvars should be used for each UV set according to the provided AllowedPrimvarsToUVIndex mapping. The intent is to use this when e.g. a Mesh prim is to be collapsed together with other Mesh prims into a single StaticMesh, and they all need consistent UV sets across them. So even though AllMeshUVPrimvars contains [aaa, bbb, eee], AllowedPrimvarsToUVIndex may instruct us to assign these to UV indices [0, 1, 4] (and not just [0, 1, 2]) because our Mesh is to be merged with another Mesh prim that contains [aaa, bbb, ccc, ddd], so that ccc can be put on index 2 and ddd on index 3. @param AllMeshUVPrimvars - Array of primvars extracted from some mesh sorted by priority (most important come first) @param AllowedPrimvarsToUVIndex - Mapping from primvar names to the UV index that they're allowed to be assigned to @return Array where each index gives the primvar that should be used for that UV index
- L201 _prototype_ `TMap<FString, int32> AssemblePrimvarsIntoPrimvarToUVIndexMap(const TArray<TUsdStore<pxr::UsdGeomPrimvar>>& AllMeshUVPrimvars);` (scope `UsdUtils`) — Constructs a mapping from primvar name to their position in the provided AllMeshUVPrimvars array. @param AllMeshUVPrimvars - Array of primvars extracted from some mesh sorted by priority (most important come first) @return Mapping from primvar names to the UV index
- L208 _prototype_ `TMap<FString, int32> CombinePrimvarsIntoUVSets(const TSet<FString>& AllPrimvars, const TSet<FString>& PreferredPrimvars);` (scope `UsdUtils`) — Given an array of primvars, and an array of which of those are preferred (AllPrimvars should also include PreferredPrimvars), this will sort lexicographically and return a prioritized PrimvarToUVIndex assignment map of up to USD_PREVIEW_SURFACE_MAX_UV_SETS UV indices
- L214 _prototype_ `TMap<FString, int32> GetPrimvarToUVIndexMap(const pxr::UsdPrim& UsdPrim, int32 MaxNumPrimvars = USD_PREVIEW_SURFACE_MAX_UV_SETS);` (scope `UsdUtils`) — Calls GetUVSetPrimvars() followed by AssemblePrimvarsIntoPrimvarToUVIndexMap(). This exists so that it can be called without having to manipulate the USD types (e.g. for Interchange)
- L217 _function_ `template<typename T, typename U> FString StringifyMap(const TMap<T, U>& Map)` (scope `UsdUtils`)
- L229 _prototype_ `bool IsAnimated(const pxr::UsdPrim& Prim);` (scope `UsdUtils`)
- L230 _prototype_ `bool HasAnimatedAttributes(const pxr::UsdPrim& Prim);` (scope `UsdUtils`)
- L231 _prototype_ `bool HasAnimatedTransform(const pxr::UsdPrim& Prim);` (scope `UsdUtils`)
- L232 _prototype_ `bool HasAnimatedVisibility(const pxr::UsdPrim& Prim);` (scope `UsdUtils`)
- L239 _prototype_ `bool HasAnimatedBounds( const pxr::UsdPrim& Prim, EUsdPurpose IncludedPurposes = EUsdPurpose::Proxy | EUsdPurpose::Render, bool bUseExtentsHint = true, bool bIgnoreVisibility = false );` (scope `UsdUtils`) — Returns true if Prim should have animated bounds (either from having authored animated `extent` or `extentsHint` attributes, or potentially from having computed bounds and child prims that should make those computed bounds animated, like having animated child Xforms)
- L252 _prototype_ `bool GetAnimatedBoundsTimeSamples( const pxr::UsdPrim& InPrim, TArray<double>& OutTimeSamples, EUsdPurpose InIncludedPurposes = EUsdPurpose::Proxy | EUsdPurpose::Render, bool bInUseExtentsHint = true, bool bInIgnoreVisibility = false );` (scope `UsdUtils`) — Similar to HasAnimatedBounds, except that this will also collect all the timeSamples that are relevant for sampling animated bounds. For example this could just be the timeSamples for an authored `extentsHint` or `extent` animation, but this could instead be the timeSamples of child Xforms transform animations instead. Note that OutTimeSamples may end up with duplicate timeSamples, but those will always be at least sorted.
- L261 _prototype_ `TArray<UE::FUsdAttribute> GetAnimatedAttributes(const pxr::UsdPrim& Prim);` (scope `UsdUtils`) — Returns all of the Prim attributes that contain timeSamples
- L264 _prototype_ `TArray<FString> GetAppliedAPISchemaPropertyNames(const FString& SchemaName);` (scope `UsdUtils`) — Returns a list of all the registered property names for a provided APISchema name. Also works for codeless schemas
- L267 _prototype_ `bool HasAuthoredKind(const pxr::UsdPrim& Prim);` (scope `UsdUtils`) — Returns true if this prim has any authored opinion for prim kind
- L270 _prototype_ `EUsdDefaultKind GetDefaultKind(const pxr::UsdPrim& Prim);` (scope `UsdUtils`) — Returns whether Prim belongs to any of the default kinds, or a kind derived from them. The result can be a union of different kinds.
- L279 _prototype_ `bool SetDefaultKind(pxr::UsdPrim& Prim, EUsdDefaultKind NewKind);` (scope `UsdUtils`) — Sets the prim kind for Prim to the provided NewKind. Differs from IUsdPrim::SetKind in that we don't have to provide the USD token. @param NewKind - New kind to set. Must be a single flag, and not a combination of multiple plags @param Prim - Prim to receive the new Kind @return Whether we managed to set the kind or not.
- L291 _prototype_ `ECollapsingPreference GetCollapsingPreference(const pxr::UsdPrim& Prim);` (scope `UsdUtils`) — Gets how this prim wants to be collapsed: Whether we should allow/never try to do it, or whether we should check its kind for that purpose
- L296 _prototype_ `bool SetCollapsingPreference(const pxr::UsdPrim& Prim, ECollapsingPreference NewPreference);` (scope `UsdUtils`) — Sets how this prim wants to be collapsed: Whether we should always/never try to do it, or whether we should check its kind for that purpose
- L299 _prototype_ `bool PrimCollapses( const pxr::UsdPrim& Prim, EUsdDefaultKind KindsToCollapse, bool bUsePrimKindsForCollapsing, bool bUseSchemaForCollapsing, bool bCanCollapseByDefault );` (scope `UsdUtils`) — Checks the prim kind and the collapsing schema to determine whether the provided prim should collapse or not
- L311 _prototype_ `EUsdDrawMode GetAppliedDrawMode(const pxr::UsdPrim& Prim);` (scope `UsdUtils`) — Returns whether the prim has the UsdGeomModelAPI schema and should be drawn with one of the alternative draw modes, such as cards or bounds. Will return EUsdDrawMode::Default in case the prim should be drawn as usual instead, or in case of error.
- L343 _prototype_ `TMap<FString, FVolumePrimInfo> GetVolumeInfoByFilePathHash(const pxr::UsdPrim& VolumePrim);` (scope `UsdUtils`) — Collects an FVolumePrimInfo for each SparseVolumeTexture that should be generated for VolumePrim. The map keys are FilePathHashes, because some of these SparseVolumeTextures may consume multiple .vdb files (e.g .animations)
- L349 _prototype_ `TMultiMap<FString, FString> GetVolumeMaterialParameterToFieldNameMap(const pxr::UsdPrim& VolumePrim);` (scope `UsdUtils`) — Extracts from the volume prim a desired mapping between Unreal material parameter and the volume field name (note the corresponding VolumeFieldNames field within FVolumePrimInfo)
- L352 _prototype_ `TArray<FString> GetSparseVolumeTextureParameterNames(const UMaterial* Material);` (scope `UsdUtils`) — Gets the names of all SparseVolumeTexture material parameters within the provided material
- L358 _prototype_ `TArray<TUsdStore<pxr::UsdPrim>> GetAllPrimsOfType( const pxr::UsdPrim& StartPrim, const pxr::TfType& SchemaType, const TArray<TUsdStore<pxr::TfType>>& ExcludeSchemaTypes = {} );` (scope `UsdUtils`) — Returns all prims of type SchemaType (or a descendant type) in the subtree of prims rooted at StartPrim. Stops going down the subtrees when it hits a schema type to exclude.
- L363 _prototype_ `TArray<TUsdStore<pxr::UsdPrim>> GetAllPrimsOfType( const pxr::UsdPrim& StartPrim, const pxr::TfType& SchemaType, TFunction<bool(const pxr::UsdPrim&)> PruneChildren, const TArray<TUsdStore<pxr::TfType>>& ExcludeSchemaTypes = {} );` (scope `UsdUtils`)
- L370 _prototype_ `FString GetAssetPathFromPrimPath(const FString& RootContentPath, const pxr::UsdPrim& Prim);` (scope `UsdUtils`)
- L373 _prototype_ `TArray<UE::FUsdPrim> GetAllPrimsOfType(const UE::FUsdPrim& StartPrim, const TCHAR* SchemaName);` (scope `UsdUtils`)
- L374 _prototype_ `TArray<UE::FUsdPrim> GetAllPrimsOfType( const UE::FUsdPrim& StartPrim, const TCHAR* SchemaName, TFunction<bool(const UE::FUsdPrim&)> PruneChildren, const TArray<const TCHAR*>& ExcludeSchemaNames = {} );` (scope `UsdUtils`)
- L382 _prototype_ `double GetDefaultTimeCode();` (scope `UsdUtils`) — Returns the time code for non-timesampled values. Usually a quiet NaN.
- L385 _prototype_ `double GetEarliestTimeCode();` (scope `UsdUtils`) — Returns the earliest possible timecode. Use it to always fetch the first frame of an animated attribute
- L394 _prototype_ `FString GetAssetHashPrefix(const pxr::UsdPrim& PrimForAsset, bool bShareAssetsForIdenticalPrims);` (scope `UsdUtils`) — Simple utility that generates a prefix that should be added to the hash when using it to cache/query an UsdAssetCache2 object. The idea is to use this prefix alongside the hash whenever bShareAssetsForIdenticalPrims is false, so as to generate a new hash for each prim. Whenever bShareAssetsForIdenticalPrims is true, the prefix will be the empty string. Whenever bShareAssetsForIdenticalPrims is false, the prefix will be a SHA1 hash of the prim path and its stage identifier.
- L409 _prototype_ `void AddReference( UE::FUsdPrim& Prim, const TCHAR* AbsoluteFilePath, const UE::FSdfPath& TargetPrimPath = {}, double TimeCodeOffset = 0.0, double TimeCodeScale = 1.0 );` (scope `UsdUtils`) — Adds a reference on Prim to the layer at AbsoluteFilePath, optionally specifying a target prim inside that layer. @param Prim - Referencer prim @param AbsoluteFilePath - Path to the layer to reference (can be empty for internal references). e.g. "C:\MyFolder\Cube.usda" @param TargetPrimPath - Path to a specific prim to reference within the target layer. e.g. "/SomeOtherPrim" @param TimeCodeOffset - Offset in timeCodes to author on the reference @param TimeCodeScale - TimeCode scale to author on the reference @param ReferencerSchemaHandling - How to behave when Prim has a different type than the referenced prim. Passing an unset TOptional will check the project settings for the value instead. The default value is MatchReferencedType for backwards compatibility. Note: If this is set to ShowDialog, the call may create an Editor transaction.
- L416 _prototype_ `void AddReference( UE::FUsdPrim& Prim, const TCHAR* AbsoluteFilePath, TOptional<EReferencerTypeHandling> ReferencerTypeHandling, const UE::FSdfPath& TargetPrimPath = {}, double TimeCodeOffset = 0.0, double TimeCodeScale = 1.0 );` (scope `UsdUtils`)
- L426 _prototype_ `bool GetReferenceFilePath(const UE::FUsdPrim& Prim, const FString& FileExtension, FString& OutReferenceFilePath);` (scope `UsdUtils`) — Gets the strongest direct reference on Prim with the given FileExtension. Returns true if there was one.
- L429 _prototype_ `TArray<FString> GetReferenceOrPayloadFilePaths(const UE::FUsdPrim& Prim);` (scope `UsdUtils`) — Returns the filepaths that this prim is referencing or using as a payload, in case it has any external reference or payload authored
- L443 _prototype_ `void AddPayload( UE::FUsdPrim& Prim, const TCHAR* AbsoluteFilePath, const UE::FSdfPath& TargetPrimPath = {}, double TimeCodeOffset = 0.0, double TimeCodeScale = 1.0 );` (scope `UsdUtils`) — Adds a payload on Prim pointing at the layer at AbsoluteFilePath, optionally specifying a target prim inside that layer. @param Prim - Prim to receive the payload @param AbsoluteFilePath - Path to the layer to use as payload (can be empty for internal references). e.g. "C:\MyFolder\Cube.usda" @param TargetPrimPath - Path to a specific prim to use as payload within the target layer. e.g. "/SomeOtherPrim" @param TimeCodeOffset - Offset in timeCodes to author on the payload @param TimeCodeScale - TimeCode scale to author on the payload @param ReferencerSchemaHandling - How to behave when Prim has a different type than the prim used by the payload. Passing an unset TOptional will check the project settings for the value instead. The default value is MatchReferencedType for backwards compatibility. Note: If this is set to ShowDialog, the call may create an Editor transaction.
- L450 _prototype_ `void AddPayload( UE::FUsdPrim& Prim, const TCHAR* AbsoluteFilePath, TOptional<EReferencerTypeHandling> ReferencerTypeHandling, const UE::FSdfPath& TargetPrimPath = {}, double TimeCodeOffset = 0.0, double TimeCodeScale = 1.0 );` (scope `UsdUtils`)
- L469 _prototype_ `bool RenamePrim(UE::FUsdPrim& Prim, const TCHAR* NewPrimName);` (scope `UsdUtils`) — Renames a single prim to a new name WARNING: This will lead to issues if called from within a pxr::SdfChangeBlock. This because it needs to be able to send separate notices: One notice about the renaming, that the transactor can record on the current edit target, and one extra notice about the definition of an auxiliary prim on the session layer, that the transactor *must* record as having taken place on the session layer. @param Prim - Prim to rename @param NewPrimName - New name for the prim e.g. "MyNewName" @return True if we managed to rename
- L476 _prototype_ `FString GetValidChildName(FString InName, const pxr::UsdPrim& ParentPrim);` (scope `UsdUtils`) — Returns a sanitized, valid version of 'InName' that can be used as the name for a child prim of 'ParentPrim'. Returns the empty string in case of an error.
- L485 _prototype_ `FString SanitizeUsdIdentifier(const TCHAR* InIdentifier);` (scope `UsdUtils`) — Returns a modified version of InIdentifier that can be used as a USD prim or property name. This means only allowing letters, numbers and the underscore character. All others are replaced with underscores. Additionally, the first character cannot be a number. Note that this obviously doesn't check for a potential name collision.
- L488 _prototype_ `void MakeVisible(UE::FUsdPrim& Prim, double TimeCode = UsdUtils::GetDefaultTimeCode());` (scope `UsdUtils`) — Will call UsdGeomImageable::MakeVisible/MakeInvisible if Prim is a UsdGeomImageable
- L489 _prototype_ `void MakeInvisible(UE::FUsdPrim& Prim, double TimeCode = UsdUtils::GetDefaultTimeCode());` (scope `UsdUtils`)
- L492 _prototype_ `bool IsVisible(const UE::FUsdPrim& Prim, double TimeCode = UsdUtils::GetDefaultTimeCode());` (scope `UsdUtils`) — Returns if the ComputedVisibility for Prim says it should be visible
- L495 _prototype_ `bool HasInheritedVisibility(const UE::FUsdPrim& Prim, double TimeCode = UsdUtils::GetDefaultTimeCode());` (scope `UsdUtils`) — Returns whether Prim has visibility set to 'inherited'
- L502 _prototype_ `bool HasInvisibleParent( const UE::FUsdPrim& Prim, const UE::FUsdPrim& RootPrim, double TimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UsdUtils`) — Travels up from Prim and returns true if we hit any invisible prim before we hit the stage pseudoroot. Does not check `Prim` itself (or `RootPrim`, so that you can just pass the PseudoRoot in most cases). Completely ignores whether non-UsdGeomImageable prims are visible or not and keeps travelling up.
- L512 _prototype_ `TArray<UE::FUsdPrim> GetVisibleChildren(const UE::FUsdPrim& Prim, EUsdPurpose AllowedPurposes);` (scope `UsdUtils`) — Returns the prims in the subtree of Prim (potentially including Prim itself) that are visible due to the visibility attribute and prim purpose
- L527 _prototype_ `UE::FSdfPath GetPrimSpecPathForLayer(const UE::FUsdPrim& Prim, const UE::FSdfLayer& Layer);` (scope `UsdUtils`) — Returns a path exactly like Prim.GetPrimPath(), except that if the prim is within variant sets, it will return the full path with variant selections in it (i.e. the spec path), like "/Root/Child{Varset=Var}Inner" instead of just "/Root/Child/Inner". It needs a layer because it is possible for a prim to be defined within a variant set in some layer, but then have an 'over' opinion defined in another layer without a variant, meaning the actual spec path depends on the layer. Note that stage operations that involve manipulating specs require this full path instead (like removing/renaming prims), while other operations need the path with the stripped variant selections (like getting/defining/overriding prims) Returns an empty path in case the layer doesn't have a spec for this prim.
- L542 _prototype_ `void RemoveAllLocalPrimSpecs(const UE::FUsdPrim& Prim, const UE::FSdfLayer& Layer = UE::FSdfLayer{});` (scope `UsdUtils`) — Removes all the prim specs for Prim on the given Layer, if the layer belongs to the stage's local layer stack. This function is useful in case the prim is inside a variant set: In that case, just calling FUsdStage::RemovePrim() will attempt to remove the "/Root/Example/Child", which wouldn't remove the "/Root{Varset=Var}Example/Child" spec, meaning the prim may still be left on the stage. Note that it's even possible to have both of those specs at the same time: for example when we have a prim inside a variant set, but outside of it we have overrides to the same prim. This function will remove both. @param Prim - Prim to remove @param Layer - Layer to remove prim specs from. This can be left with the invalid layer (default) in order to remove all specs from the entire stage's local layer stack.
- L551 _prototype_ `bool CutPrims(const TArray<UE::FUsdPrim>& Prims);` (scope `UsdUtils`) — Copies flattened versions of the input prims onto the clipboard stage and removes all the prim specs for Prims from their stages. These cut prims can then be pasted with PastePrims. @param Prims - Prims to cut @return True if we managed to cut
- L560 _prototype_ `bool CopyPrims(const TArray<UE::FUsdPrim>& Prims);` (scope `UsdUtils`) — Copies flattened versions of the input prims onto the clipboard stage. These copied prims can then be pasted with PastePrims. @param Prims - Prims to copy @return True if we managed to copy
- L574 _prototype_ `TArray<UE::FSdfPath> PastePrims(const UE::FUsdPrim& ParentPrim);` (scope `UsdUtils`) — Pastes the prims from the clipboard stage as children of ParentPrim. The pasted prims may be renamed in order to have valid names for the target location, which is why this function returns the pasted prim paths. This function returns just paths instead of actual prims because USD needs to respond to the notices about the created prim specs before the prims are fully created, which means we wouldn't be able to return the created prims yet, in case this function was called from within an SdfChangeBlock. @param ParentPrim - Prim that will become parent to the pasted prims @return Paths to the pasted prim specs, after they were added as children of ParentPrim
- L577 _prototype_ `bool CanPastePrims();` (scope `UsdUtils`) — Returns true if we have prims that we can paste within our clipboard stage
- L580 _prototype_ `void ClearPrimClipboard();` (scope `UsdUtils`) — Clears all prims from our clipboard stage
- L597 _prototype_ `TArray<UE::FSdfPath> DuplicatePrims( const TArray<UE::FUsdPrim>& Prims, EUsdDuplicateType DuplicateType, const UE::FSdfLayer& TargetLayer = UE::FSdfLayer{} );` (scope `UsdUtils`) — Duplicates all provided Prims one-by-one, performing the requested DuplicateType. See the documentation on EUsdDuplicateType for the different operation types. The duplicated prims may be renamed in order to have valid names for the target location, which is why this function returns the pasted prim paths. This function returns just paths instead of actual prims because USD needs to respond to the notices about the created prim specs before the prims are fully created, which means we wouldn't be able to return the created prims yet, in case this function was called from within an SdfChangeBlock. @param Prims - Prims to duplicate @param DuplicateType - Type of prim duplication to perform @param TargetLayer - Target layer to use when duplicating, if relevant for that duplication type @return Paths to the duplicated prim specs, after they were added as children of ParentPrim.
- L604 _prototype_ `void SetPrimAssetInfo(UE::FUsdPrim& Prim, const FUsdUnrealAssetInfo& Info);` (scope `UsdUtils`) — Adds to Prim the assetInfo metadata the values described in Info
- L607 _prototype_ `FUsdUnrealAssetInfo GetPrimAssetInfo(const UE::FUsdPrim& Prim);` (scope `UsdUtils`) — Retrieves from Prim the assetInfo metadata values that we use as export metadata, when exporting Unreal assets
- L611 _prototype_ `bool ClearNonEssentialPrimMetadata(const pxr::UsdPrim& Prim);` (scope `UsdUtils`) — Removes all metadata from Prim, except the typeName and specifier entries
- L615 _prototype_ `void CollectSchemaAnalytics(const UE::FUsdStage& Stage, TArray<FAnalyticsEventAttribute>& OutAttributes);` (scope `UsdUtils`) — Collects how many times each schema shows up on the provided stage and appends those attributes to the provided OutAttributes
- L618 _prototype_ `void ReadStageMetaData(UE::FUsdStage Stage, TMap<FString, FString>& OutMetaDataMap);` (scope `UsdUtils`) — Parses and stores primary Stage metadata key-info pairs in the MetadataMap
- L621 _prototype_ `bool IsInstancingAwareTranslationEnabled();` (scope `UsdUtils`) — Whether or not instancing-aware translation is enabled
- L624 _prototype_ `UE::FUsdPrim GetPrototypePrim(const UE::FUsdPrim& Prim);` (scope `UsdUtils`) — Retrieves the equivalent of this prim in the prototype it's referenced from, where applicable
- L627 _prototype_ `UE::FSdfPath GetPrototypePrimPath(const UE::FUsdPrim& Prim);` (scope `UsdUtils`) — Retrieves the prototype path for the prim

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDErrorUtils.h` (Public)


#### class `FUsdLogManager`  
`class FUsdLogManager`  
_L36-85_
- L39 _public typedef_ `using FMessageDisplayCallback = TFunction<void(const TArray<TSharedRef<FTokenizedMessage>>&)>;`
- L42 _public function_ `UE_NODEBUG static constexpr uint32 FileHashForEnsure(const char* Filename)` — Copied from AssertionMacros.h as it's private there
- L58 _public prototype_ `static void Log(EMessageSeverity::Type Severity, const FString& Message, uint32 MessageID);` — Log a message that shows only on the output log. Prefer using the USD_LOG_INFO, USD_LOG_WARNING, USD_LOG_ERROR, USD_LOG_USERINFO, USD_LOG_USERWARNING, USD_LOG_USERERROR macros.
- L62 _public prototype_ `static void Log(EMessageSeverity::Type Severity, const FText& Message, uint32 MessageID);` — Log a message that shows on the output log and the message log, if we're inside of a FScopedUsdMessageLog scope. Prefer using the USD_LOG_INFO, USD_LOG_WARNING, USD_LOG_ERROR, USD_LOG_USERINFO, USD_LOG_USERWARNING, USD_LOG_USERERROR macros.
- L66 _public prototype_ `static bool HasAccumulatedErrors();` — Returns whether we have currently accumulated any message with severity warning or higher. If we're not in the scope of any FScopedUsdMessageLog, returns false.
- L68 _public prototype_ `static void RegisterDiagnosticDelegate();`
- L70 _public prototype_ `static void UnregisterDiagnosticDelegate();`
- L72 _public prototype_ `static void DisplayMessagesOnMessageLog(const TArray<TSharedRef<FTokenizedMessage>>& Messages);`
- L75 _public prototype_ `static void LogMessage(EMessageSeverity::Type Severity, const FText& Message);` — `UE_DEPRECATED(5.6, "Use Log, or ideally the USD_LOG_INFO, USD_LOG_WARNING, etc. macros")`
- L78 _public prototype_ `static void LogMessage(const TSharedRef<FTokenizedMessage>& Message);` — `UE_DEPRECATED(5.6, "Use Log, or ideally the USD_LOG_INFO, USD_LOG_WARNING, etc. macros")`
- L81 _public prototype_ `static void EnableMessageLog();` — `UE_DEPRECATED(5.6, "Used FScopedUsdMessageLog instead.")`
- L84 _public prototype_ `static void DisableMessageLog();` — `UE_DEPRECATED(5.6, "Used FScopedUsdMessageLog instead.")`

#### class `FScopedUsdMessageLog`  
`class FScopedUsdMessageLog`  
_L115-125_
- desc: Begins a scope where all logged messages (user and non-user facing, USD SDK errors and even USD error mark messages) are collected and deduplicated. The deduplication only happens if the bOptimizeUsdLog project setting is enabled (default). If the USD.UseMessageLog cvar is enabled (default), it will add the user-facing messages (and the USD SDK and error mark messages) to the Message Log, (whether deduplication is enabled or disabled), also displaying a toast letting the user know that those messages can be viewed there.
- L118 _public prototype_ `FScopedUsdMessageLog(FUsdLogManager::FMessageDisplayCallback = FUsdLogManager::DisplayMessagesOnMessageLog);`
- L119 _public prototype_ `~FScopedUsdMessageLog();`
- L121 _public prototype_ `FScopedUsdMessageLog(const FScopedUsdMessageLog&) = delete;`
- L122 _public prototype_ `FScopedUsdMessageLog& operator=(const FScopedUsdMessageLog&) = delete;`
- L123 _public prototype_ `FScopedUsdMessageLog(FScopedUsdMessageLog&&) = delete;`
- L124 _public prototype_ `FScopedUsdMessageLog& operator=(FScopedUsdMessageLog&&) = delete;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USDUTILITIES_API`
- L11 _namespace_ `namespace UsdUtils`
- L17 _prototype_ `void StartMonitoringErrors();` (scope `UsdUtils`) — `UE_DEPRECATED(5.6, "Use FScopedUsdMessageLog instead.")` — Pushes an USD error monitoring object into the stack and catches any emitted errors
- L24 _prototype_ `TArray<FString> GetErrorsAndStopMonitoring();` (scope `UsdUtils`) — `UE_DEPRECATED(5.6, "Use FScopedUsdMessageLog and FUsdLogManager::HasAccumulatedErrors() instead.")` — Returns all errors that were captured since StartMonitoringErrors(), clears and pops an error monitoring object from the stack
- L33 _prototype_ `bool ShowErrorsAndStopMonitoring(const FText& ToastMessage = FText());` (scope `UsdUtils`) — `UE_DEPRECATED(5.6, "Use FScopedUsdMessageLog instead.")` — Displays the error messages for each captured error since StartMonitoringErrors(), clears and pops an error monitoring object from the stack. If ToastMessage is empty, a default message will be displayed. Returns true if there were any errors.
- L100 _macro_ `#define USD_LOG_INFO(Format, ...) FUsdLogManager::Log(EMessageSeverity::Info, FString::Printf(Format, ##__VA_ARGS__), HashCombine(FUsdLogManager::FileHashForEnsure(__FILE__), __LINE__));` — Display an Info/Warn/Error message on the Output Log (USD_LOG_INFO, USD_LOG_WARNING, USD_LOG_ERROR), or display a user-facing Info/Warn/Error message, that is additionally added to the Message Log (USD_LOG_USERINFO, USD_LOG_USERWARNING, USD_LOG_USERERROR). The user-facing message must be within the scope of a FScopedUsdMessageLog to be added to the Message Log, otherwise it is treated as the non-user analogue. See FScopedUsdMessageLog right below this for more info. Usage examples: USD_LOG_WARNING(TEXT("Some error directly to the Output Log: %s"), *MyString); USD_LOG_USERERROR(LOCTEXT("MyMessage", "This is an error message that will show on the Message Log")); USD_LOG_USERWARNING(FText::Format(LOCTEXT("InvalidBinding", "Binding {0} is invalid!"), FText::FromString(UsdToUnreal::ConvertPath(InSkeletonRoot.GetPath()))));
- L101 _macro_ `#define USD_LOG_WARNING(Format, ...) FUsdLogManager::Log(EMessageSeverity::Warning, FString::Printf(Format, ##__VA_ARGS__), HashCombine(FUsdLogManager::FileHashForEnsure(__FILE__), __LINE__));`
- L102 _macro_ `#define USD_LOG_ERROR(Format, ...) FUsdLogManager::Log(EMessageSeverity::Error, FString::Printf(Format, ##__VA_ARGS__), HashCombine(FUsdLogManager::FileHashForEnsure(__FILE__), __LINE__));`
- L103 _macro_ `#define USD_LOG_USERINFO(text) FUsdLogManager::Log(EMessageSeverity::Info, text, HashCombine(FUsdLogManager::FileHashForEnsure(__FILE__), __LINE__));`
- L104 _macro_ `#define USD_LOG_USERWARNING(text) FUsdLogManager::Log(EMessageSeverity::Warning, text, HashCombine(FUsdLogManager::FileHashForEnsure(__FILE__), __LINE__));`
- L105 _macro_ `#define USD_LOG_USERERROR(text) FUsdLogManager::Log(EMessageSeverity::Error, text, HashCombine(FUsdLogManager::FileHashForEnsure(__FILE__), __LINE__));`

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDExportUtils.h` (Public)


#### class `UsdUnreal::ExportUtils::FUniquePathScope`  
`class FUniquePathScope final`  
_L30-40_
- desc: Utility to call BeginUniquePathScope() on construction and EndUniquePathScope() on destruction
- L33 _public prototype_ `FUniquePathScope();`
- L34 _public prototype_ `~FUniquePathScope();`
- L36 _public prototype_ `FUniquePathScope(const FUniquePathScope&) = delete;`
- L37 _public prototype_ `FUniquePathScope(FUniquePathScope&&) = delete;`
- L38 _public prototype_ `FUniquePathScope& operator=(const FUniquePathScope&) = delete;`
- L39 _public prototype_ `FUniquePathScope& operator=(FUniquePathScope&&) = delete;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API USDUTILITIES_API`
- L9 _namespace_ `namespace UsdUnreal`
- L9 _namespace_ `namespace ExportUtils` (scope `UsdUnreal`)
- L19 _prototype_ `void BeginUniquePathScope();` (scope `UsdUnreal::ExportUtils`) — Begins a UniquePathScope, incrementing the internal scope counter. During a UniquePathScope, all paths returned by GetUniqueFilePathForExport will be globally unique (i.e. it will never return the same path twice). Opening a scope while another scope is opened has no effect but to increment the scope counter further.
- L27 _prototype_ `void EndUniquePathScope();` (scope `UsdUnreal::ExportUtils`) — Ends a UniquePathScope, decrementing the internal scope counter. If the internal scope counter reaches zero (i.e. all previously opened scopes are ended) this also clears the cache of unique paths.
- L48 _prototype_ `FString GetUniqueFilePathForExport(const FString& DesiredPathWithExtension);` (scope `UsdUnreal::ExportUtils`) — If we're inside of a UniquePathScope, returns a sanitized (and potentially suffixed) path that is guaranteed to not collide with any other path returned from this function during the UniquePathScope. If we're not inside of a UniquePathScope, returns the sanitized version of DesiredPathWithExtension.
- L54 _prototype_ `void SanitizeFilePath(FString& Path);` (scope `UsdUnreal::ExportUtils`) — Sanitizes the Path to be used as a clean absolute file path. Normalizes separators, removes duplicate separators, collapses relative paths, etc.

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDGeomMeshConversion.h` (Public)


#### struct `UsdToUnreal::FUsdMeshConversionOptions`  
`struct FUsdMeshConversionOptions`  
_L62-129_
- desc: Common options to mesh conversion functions
- L80 _public prototype_ `FUsdMeshConversionOptions(const FUsdMeshConversionOptions& Other) = default;` — These need to be explicitly defaulted surrounded by the deprecation macros or else the implicit versions will be generated elsewhere, use MaterialToPrimvarToUVIndex and trigger the deprecation warnings
- L81 _public prototype_ `FUsdMeshConversionOptions& operator=(const FUsdMeshConversionOptions& Other) = default;`
- L84 _public member_ `const static FUsdMeshConversionOptions DefaultOptions;`
- L85 _public prototype_ `FUsdMeshConversionOptions();`
- L88 _public member_ `TSet<FString> PrimvarNames;` — List of the primvars that should be stored on the MeshDescription
- L91 _public member_ `FTransform AdditionalTransform;` — Additional UE-space transform to bake into the mesh's vertices
- L94 _public member_ `EUsdPurpose PurposesToLoad;` — Only prims with these purposes will be traversed
- L97 _public member_ `pxr::TfToken RenderContext;` — Render context to use when parsing Mesh materials
- L100 _public member_ `pxr::TfToken MaterialPurpose;` — Material purpose to use when parsing Mesh materials
- L103 _public member_ `pxr::UsdTimeCode TimeCode;` — USD timecode when the prims should be sampled for mesh data and converted
- L107 _public member_ `bool bMergeIdenticalMaterialSlots;` — Whether to try reusing material slots (both local and the ones already in MaterialAssignments) when converting the material assignments from the mesh
- L111 _public member_ `int32 SubdivisionLevel;` — What subdivision level to subdivide to, if the converted mesh is a subdivision mesh. 0 means no subdivision should take place (default).
- L114 _public member_ `EImportPrimvar ImportPrimvars;` — How to store the primvars in the MeshDescription
- L117 _public member_ `bool bOffsetJointIndicesForMultipleRootBones;` — Whether to add an additional offset to vertex join indices if the skinned mesh's skeleton has multiple root bones
- L123 _public member_ `bool bForceCheckUnrealMaterialAttribute;` — Whether to always check the deprecated "unrealMaterial" string attribute on prims regardless of the configured RenderContext. When false (the default), the unrealMaterial attribute is only checked when the RenderContext is "unreal". This is mainly used by Interchange: The render context is resolved only later (and we always provide 'universal'), so we need this additional parameter to not ignore the string attribute completely
- L128 _public member_ `bool bRequireMaterialsHaveProvidedRenderContext;` — If true, a bound material is only used if it has a surface shader output for the configured RenderContext. If it doesn't, the binding is rejected and processing falls through to the DisplayColor fallback. Legacy USD importers set this to true; Interchange sets it to false because the render context is resolved at a later stage.

#### enum `UsdToUnreal::FUsdMeshConversionOptions::EImportPrimvar`  
`enum EImportPrimvar`  
_L65-75_
- desc: This enum must match EInterchangeUsdPrimvar in InterchangeUsdDefinitions.h
- L68 _public enumerator_ `Standard = 0` — Store only the standard primvars such as UVs, VertexColors, etc.
- L71 _public enumerator_ `Bake` — Store only primvars in the Mesh Description used for baking to textures (basically <geompropvalue> node from MaterialX shadergraphs that are converted to <image>)
- L74 _public enumerator_ `All` — Store all primvars in the MeshDescription, regardless

#### enum `UsdUtils::EPrimAssignmentType`  
`enum class EPrimAssignmentType : uint8`  
_L338-344_
- desc: Describes what type of material assignment a FUsdPrimMaterialSlot represents
- L340 _public enumerator_ `None` — There is no assignment for this material slot (or no material override)
- L341 _public enumerator_ `DisplayColor` — MaterialSource is a serialized FDisplayColorMaterial (e.g. '!DisplayColor_0_0')
- L342 _public enumerator_ `MaterialPrim` — MaterialSource is the USD path to a Material prim on the stage (e.g. '/Root/Materials/Red')
- L343 _public enumerator_ `UnrealMaterial` — MaterialSource is the package path to an UE material (e.g. '/Game/Materials/Red.Red')

#### struct `UsdUtils::FUsdPrimMaterialSlot`  
`struct FUsdPrimMaterialSlot`  
_L350-394_
- desc: Description of a material slot we need to add to a UStaticMesh or USkeletalMesh to have it represent a material binding in a prim. It may or may not contain an actual material assignment.
- L356 _public member_ `TSet<FString> PrimPaths;` — Path to the prims that contain this material assignment (e.g. '/Root/my_cube' or '/Root/my_cube/geomsubset_0'. This is a set because this single material slot in UE may be merged from N identical prims.
- L359 _public member_ `FString MaterialSource;` — What this represents depends on AssignedMaterialType
- L360 _public member_ `EPrimAssignmentType AssignmentType = EPrimAssignmentType::None;`
- L361 _public member_ `bool bMeshIsDoubleSided = false;`

#### struct `UsdUtils::FUsdPrimMaterialAssignmentInfo`  
`struct FUsdPrimMaterialAssignmentInfo`  
_L397-406_
- desc: Complete description of material assignment data of a pxr::UsdPrim
- L399 _public member_ `TArray<FUsdPrimMaterialSlot> Slots;`
- L402 _public member_ `TArray<int32> MaterialIndices;` — Describes the index of the Slot that each polygon/face of a mesh uses. Matches the order in Slots
- L405 _public member_ `TMap<FString, int32> PrimvarToUVIndex;` — Describes which primvars should be assigned to each UV index for this mesh.

#### struct `UsdUtils::FUsdPointInstancerInstancesData`  
`struct FUsdPointInstancerInstancesData`  
_L510-519_
- L518 _public member_ `TArray<FUsdPrototypeInstances> Prototypes;`

#### struct `UsdUtils::FUsdPointInstancerInstancesData::FUsdPrototypeInstances`  
`struct FUsdPrototypeInstances`  
_L512-516_
- L514 _public member_ `FString PathString;`
- L515 _public member_ `TArray<FTransform> InstanceTransforms;`

#### enum `UsdUtils::EMeshTopologyVariance`  
`enum class EMeshTopologyVariance : uint8`  
_L533-538_
- desc: Mesh topology variance as defined by Alembic's MeshTopologyVariance
- L535 _public enumerator_ `Constant` — unchanging topology
- L536 _public enumerator_ `Homogenous` — connectivity is unchanging, but the positions may change
- L537 _public enumerator_ `Heterogenous` — connectivity and positions may change

#### Free symbols / members of external scopes

- L43 _namespace_ `namespace UsdUtils`
- L48 _namespace_ `namespace UE`
- L53 _namespace_ `namespace UsdUnreal`
- L53 _namespace_ `namespace MaterialUtils` (scope `UsdUnreal`)
- L59 _namespace_ `namespace UsdToUnreal`
- L148 _prototype_ `bool ConvertGeomMesh( const pxr::UsdGeomMesh& Mesh, FMeshDescription& InOutMeshDescription, UsdUtils::FUsdPrimMaterialAssignmentInfo& InOutMaterialAssignments, const FUsdMeshConversionOptions& CommonOptions = FUsdMeshConversionOptions::DefaultOptions, const pxr::UsdSkelSkinningQuery* SkinningQuery = nullptr, const pxr::UsdSkelSkeletonQuery* SkeletonQuery = nullptr );` (scope `UsdToUnreal`) — Converts an UsdGeomMesh and appends the converted data to InOutMeshDescription and InOutMaterialAssignments. If a PrimvarToUVIndex mapping is provided in InOutMaterialAssignments, it will be used to remap the read primvars into UV sets. Otherwise, a new PrimvarToUVIndex map will be constructed on-demand and assigned to InOutMaterialAssignments instead. If SkinningQuery and SkeletonQuery are provided we parse the Skeletal Attributes and fill the FMeshDescription accordingly. @param Mesh - Mesh prim to convert @param InOutMeshDescription - Input/Output parameter that will be filled with the converted data @param InOutMaterialAssignments - Input/Output parameter that will be filled with the material data extracted from Mesh @param CommonOptions - Shared options used for the conversion @param SkinningQuery - For computing Skinned Points, if the target and source data set is for a SkeletalMesh. @param SkeletonQuery - For computing Skinned Points, if the target and source data set is for a SkeletalMesh. (primarily for MeshToSkeletonRestPose calculations) @return Whether the conversion was successful or not.
- L156 _prototype_ `bool ConvertGeomMesh( const pxr::UsdPrim& MeshPrim, FMeshDescription& InOutMeshDescription, UsdUtils::FUsdPrimMaterialAssignmentInfo& InOutMaterialAssignments, const FUsdMeshConversionOptions& CommonOptions = FUsdMeshConversionOptions::DefaultOptions, const pxr::UsdSkelSkinningQuery* SkinningQuery = nullptr, const pxr::UsdSkelSkeletonQuery* SkeletonQuery = nullptr );` (scope `UsdToUnreal`)
- L175 _prototype_ `bool ConvertPointInstancerToMesh( const pxr::UsdGeomPointInstancer& PointInstancer, FMeshDescription& OutMeshDescription, UsdUtils::FUsdPrimMaterialAssignmentInfo& OutMaterialAssignments, const FUsdMeshConversionOptions& CommonOptions = FUsdMeshConversionOptions::DefaultOptions );` (scope `UsdToUnreal`) — Bake a point instancer prim into a single FMeshDescription and MaterialAssignments, manually "instancing" all the prototype instances into a single combined mesh. @param PointInstancer - UsdGeomPointInstancer to bake @param OutMeshDescription - Output parameter that will be filled with the converted data @param OutMaterialAssignments - Output parameter that will be filled with the material data extracted from PointInstancer @param CommonOptions - Shared options used for the conversion @return Whether the conversion was successful or not.
- L200 _prototype_ `bool ConvertGeomMeshSubtree( const pxr::UsdPrim& SubtreeRootPrim, FMeshDescription& InOutMeshDescription, UsdUtils::FUsdPrimMaterialAssignmentInfo& InOutMaterialAssignments, const FUsdMeshConversionOptions& CommonOptions = FUsdMeshConversionOptions::DefaultOptions, bool bSkipRootPrimTransform = false, bool bSkipRootPrimVisiblity = false );` (scope `UsdToUnreal`) — Recursively traverses down Prim's subtree parsing all Mesh data (including Prim's), baking all transforms and putting the resulting mesh data within OutMeshDescription and OutMaterialAssignments. It will not bake Prim's own transform into the Mesh data. If a PrimvarToUVIndex mapping is provided in InOutMaterialAssignments, it will be used to remap the read primvars into UV sets. Otherwise, a new PrimvarToUVIndex map will be constructed on-demand and assigned to the InOutMaterialAssignments instead. @param Prim - Prim that will be converted (result will include its mesh and its children's) @param OutMeshDescription - Input/Output parameter that will be filled with the converted mesh descriptions @param OutMaterialAssignments - Input/Output parameter that will be filled with the material data extracted from UsdSchema. Each item of the array matches the mesh description of same index @param CommonOptions - Shared options used for the conversion @param bSkipRootPrimTransform - Whether to bake in the transform of SubtreeRootPrim into the mesh @param bSkipRootPrimVisiblity - Whether to bake in the visibility of SubtreeRootPrim into the mesh @return Whether the conversion was successful or not.
- L209 _prototype_ `bool ConvertGeomMeshHierarchy( const pxr::UsdPrim& Prim, FMeshDescription& InOutMeshDescription, UsdUtils::FUsdPrimMaterialAssignmentInfo& InOutMaterialAssignments, const FUsdMeshConversionOptions& CommonOptions = FUsdMeshConversionOptions::DefaultOptions, bool bSkipRootPrimTransformAndVisibility = false );` (scope `UsdToUnreal`) — `UE_DEPRECATED(5.6, "Use ConvertGeomMeshSubtree instead.")`
- L230 _prototype_ `bool ConvertGeomPrimitive( const pxr::UsdPrim& Prim, FMeshDescription& InOutMeshDescription, UsdUtils::FUsdPrimMaterialAssignmentInfo& InOutMaterialAssignments, const FUsdMeshConversionOptions& CommonOptions = FUsdMeshConversionOptions::DefaultOptions );` (scope `UsdToUnreal`) — Converts an UsdGeomCapsule(_1), UsdGeomCone, UsdGeomCube, UsdGeomCylinder(_1), UsdGeomPlane or UsdGeomSphere and appends the converted data to InOutMeshDescription and InOutMaterialAssignments. Note that all generated meshes will have extents within the [-0.5, 0.5] box centered on the origin. You can pass additional transforms on CommonOptions.AdditionalTransform though. @param Prim - USD Prim prim to convert @param InOutMeshDescription - Input/Output parameter that will be filled with the converted data @param InOutMaterialAssignments - Input/Output parameter that will be filled with the material data extracted from Mesh @param CommonOptions - Shared options used for the conversion @return Whether the conversion was successful or not.
- L251 _prototype_ `bool ConvertGeomPrimitiveTransform(const pxr::UsdPrim& InPrim, const pxr::UsdTimeCode& InTimeCode, FTransform& OutTransform);` (scope `UsdToUnreal`) — Extracts a "primitive transform" from the provided UsdGeomCapsule(_1), UsdGeomCone, UsdGeomCube, UsdGeomCylinder(_1), UsdGeomPlane or UsdGeomSphere and places the converted, UE coordinate system transform on OutTransform. This is intended to be applied to the primitive data generated by ConvertGeomPrimitive, and concatenated with any actual Xform on the prim (Xform applied after). The idea is that the meshes generated there are standard size and fill the [-0.5, 0.5] box centered on the origin (length 1). If a Cylinder has "height=2.5", this function will produce a scaling of 2.5 on the longitudinal axis for that cylinder. @param Prim - USD Prim prim to convert @param InTimeCode - TimeCode to sample the @param OutTransform - The converted transform on the UE coordinate system @return Whether the conversion was successful or not.
- L254 _namespace_ `namespace UnrealToUsd`
- L270 _prototype_ `bool ConvertStaticMesh( const UStaticMesh* StaticMesh, pxr::UsdPrim& UsdPrim, pxr::UsdTimeCode TimeCode = pxr::UsdTimeCode::Default(), UE::FUsdStage* StageForMaterialAssignments = nullptr, int32 LowestMeshLOD = 0, int32 HighestMeshLOD = INT32_MAX, bool bExportStaticMeshSourceData = false );` (scope `UnrealToUsd`) — Extracts mesh data from StaticMesh and places the results in UsdPrim, as children UsdGeomMeshes. This function receives the parent UsdPrim as it may create a variant set named 'LOD', and create a separate UsdGeomMeshes for each LOD, as a variant of 'LOD' @param StaticMesh - StaticMesh to convert @param UsdPrim - Prim to receive the mesh data or LOD variant set @param TimeCode - TimeCode to author the attributes with @param StageForMaterialAssignments - Stage to use when authoring material assignments (we use this when we want to export the mesh to a payload layer, but the material assignments to an asset layer) @param LowestMeshLOD - Lowest LOD of the UStaticMesh to export (start of the LOD range) @param HighestMeshLOD - Lowest LOD of the UStaticMesh to export (end of the LOD range) @param bExportStaticMeshSourceData - Whether to export the source mesh description data (if true) or the render data (if false) @return Whether the conversion was successful or not.
- L286 _prototype_ `bool ConvertMeshDescriptions( const TArray<FMeshDescription>& LODIndexToMeshDescription, pxr::UsdPrim& UsdPrim, const FMatrix& AdditionalTransform, const pxr::UsdTimeCode TimeCode = pxr::UsdTimeCode::Default() );` (scope `UnrealToUsd`) — Converts an array of mesh descriptions into mesh data, and places that data within the UsdGeomMesh UsdPrim. If only one MeshDescription is provided, the mesh data is added directly to the prim. If more than one MeshDescription are provided, a 'LOD' variant set will be created for UsdPrim, and LOD0, LOD1, etc. variants will be created for each provided LOD index. Within each variant, a single Mesh prim also named LOD0, LOD1, etc. will contain the mesh data.
- L301 _prototype_ `bool ConvertGeometryCache( const UGeometryCache* GeometryCache, pxr::UsdPrim& UsdPrim, UE::FUsdStage* StageForMaterialAssignments = nullptr );` (scope `UnrealToUsd`) — Extracts animated mesh data from GeometryCache and places the results in UsdPrim. @param GeometryCache - GeometryCache to convert @param UsdPrim - Prim to receive the mesh data @param StageForMaterialAssignments - Stage to use when authoring material assignments (we use this when we want to export the mesh to a payload layer, but the material assignments to an asset layer) @return Whether the conversion was successful or not.
- L307 _prototype_ `bool ConvertSkeletalMeshToStaticMesh( const USkeletalMesh* SkeletalMesh, pxr::UsdPrim& UsdPrim, const pxr::UsdTimeCode TimeCode = pxr::UsdTimeCode::Default(), UE::FUsdStage* StageForMaterialAssignments = nullptr );` (scope `UnrealToUsd`)
- L314 _prototype_ `bool ConvertAnimSequenceToAnimatedMesh( UAnimSequence* AnimSequence, USkeletalMesh* SkeletalMesh, pxr::UsdPrim& UsdPrim, UE::FUsdStage* StageForMaterialAssignments = nullptr );` (scope `UnrealToUsd`)
- L325 _prototype_ `bool CreateSkeletalAnimationToMeshBaker( UE::FUsdPrim& MeshPrim, USkeletalMeshComponent& Component, struct FComponentBaker& OutBaker );` (scope `UnrealToUsd`) — Creates a baker responsible for baking the skinned mesh of a skeletal mesh component to a Mesh prim, returning true if a EBakingType::Skeletal baker was created
- L333 _namespace_ `namespace UsdUtils`
- L335 _typedef_ `using FDisplayColorMaterial = UsdUnreal::MaterialUtils::FDisplayColorMaterial;` (scope `UsdUtils`)
- L363 _function_ `friend bool operator==(const FUsdPrimMaterialSlot& Lhs, const FUsdPrimMaterialSlot& Rhs)` (scope `UsdUtils`)
- L372 _function_ `friend uint32 GetTypeHash(const FUsdPrimMaterialSlot& Slot)` (scope `UsdUtils`)
- L385 _function_ `friend FArchive& operator<<(FArchive& Ar, FUsdPrimMaterialSlot& Slot)` (scope `UsdUtils`)
- L408 _prototype_ `void RepairNormalsAndTangents(const FString& PrimPath, FMeshDescription& MeshDescription);` (scope `UsdUtils`)
- L412 _prototype_ `TOptional<FDisplayColorMaterial> ExtractDisplayColorMaterial( const pxr::UsdGeomGprim& Gprim, const pxr::UsdTimeCode TimeCode = pxr::UsdTimeCode::EarliestTime() );` (scope `UsdUtils`) — Creates a FDisplayColorMaterial object describing the vertex color/opacity data from Gprim at time TimeCode
- L433 _prototype_ `FUsdPrimMaterialAssignmentInfo GetPrimMaterialAssignments( const pxr::UsdPrim& UsdPrim, const pxr::UsdTimeCode TimeCode = pxr::UsdTimeCode::EarliestTime(), bool bProvideMaterialIndices = true, const pxr::TfToken& RenderContext = pxr::UsdShadeTokens->universalRenderContext, const pxr::TfToken& MaterialPurpose = pxr::UsdShadeTokens->allPurpose, bool bForceCheckUnrealMaterialAttribute = false, bool bRequireMaterialsHaveProvidedRenderContext = true );` (scope `UsdUtils`) — Extracts all material assignment data from UsdPrim, including material binding, multiple assignment with GeomSubsets, and the unrealMaterial custom USD attribute. Guaranteed to return at least one material slot. If UsdPrim is a UsdGeomMesh, it is also guaranteed to have valid material indices (one for every face). @param UsdPrim - Prim to extract material assignments from @param TimeCode - Instant where the material data is sampled @param bProvideMaterialIndices - Whether to fill out the material index information for the assignment info (which can be expensive). If this is false, MaterialIndices on the result Struct will have zero values @param RenderContext - Which render context to get the materials for. Defaults to universal. @param MaterialPurpose - Which material purpose to use when retrieving material bindings @param bForceCheckUnrealMaterialAttribute - Whether to always check the "unrealMaterial" string attribute regardless of render context @param bRequireMaterialsHaveProvidedRenderContext - If this is enabled, we'll only consider a material binding if it has a surface output for the provided render context. If this is false, we'll use the bound material regardless @return Struct containing an array of material assignments, and a corresponding array of material indices for all polygons of the prim, matching the ordering of the material assignments.
- L445 _prototype_ `bool DoesPrimContainMeshLODs(const pxr::UsdPrim& Prim);` (scope `UsdUtils`) — Returns whether this prim can be interpreted as describing a static mesh with multiple LODs (i.e. if the prim holds the LOD variant set itself)
- L448 _prototype_ `bool IsGeomMeshALOD(const pxr::UsdPrim& UsdMeshPrim);` (scope `UsdUtils`) — Returns whether this UsdMesh can be interpreted as a LOD of a mesh with multiple LODs (i.e. if the Mesh prim is inside a LOD variant)
- L451 _prototype_ `bool IsCollisionEnabledForPrim(const pxr::UsdPrim& UsdPrim);` (scope `UsdUtils`) — Returns whether this UsdPrim has the UsdPhysicsCollisionAPI schema and has enabled collisions
- L454 _prototype_ `bool IsCollisionMesh(const pxr::UsdPrim& UsdPrim);` (scope `UsdUtils`) — Returns whether this UsdPrim is a custom collision mesh
- L457 _prototype_ `EUsdCollisionType GetCollisionApproximationType(const pxr::UsdPrim& UsdPrim);` (scope `UsdUtils`) — Returns which collision type should be generated for the provided prim, according to the applied physics schemas
- L461 _prototype_ `int32 GetNumberOfLODVariants(const pxr::UsdPrim& Prim);` (scope `UsdUtils`) — Returns how many LOD variants the Prim has. Note that this will return 0 if called on one of the LOD meshes themselves, it's meant to be called on its parent
- L470 _prototype_ `bool IterateLODMeshes(const pxr::UsdPrim& ParentPrim, TFunction<bool(const pxr::UsdGeomMesh& LODMesh, int32 LODIndex)> Func);` (scope `UsdUtils`) — If a prim has a variant set named "LOD", with variants named "LOD0", "LOD1", etc., and each has a single Mesh prim, this function will actively switch the variants of ParentPrim so that each child mesh is loaded, and call Func on each. Returns whether ParentPrim met the aforementioned criteria and Func was called at least once. WARNING: There is no guarantee about LOD index ordering! Func may receive LOD2, followed by LOD0, then LOD1, etc. WARNING: This will temporarily mutate the stage, and can invalidate references to children of ParentPrim!
- L483 _prototype_ `void ReplaceUnrealMaterialsWithBaked( const UE::FUsdStage& Stage, const UE::FSdfLayer& LayerToAuthorIn, const TMap<FString, FString>& BakedMaterials, bool bIsAssetLayer, bool bUsePayload );` (scope `UsdUtils`) — Traverses `Stage` and authors material binding attributes for all `unrealMaterials` that were baked into USD material assets. @param Stage - Stage to replace the unrealMaterials attributes in. All of it's layers will be traversed. @param LayerToAuthorIn - Where the material binding opinions are authored @param BakedMaterials - Maps from material path names to file paths where they were baked Example: { "/Game/MyMaterials/Red.Red": "C:/MyFolder/Red.usda" } @param bIsAssetLayer - True when we're exporting a single mesh/animation asset. False when we're exporting a level. Dictates minor behaviors when authoring the material binding relationships, e.g. whether we author them inside variants or not @param bUsePayload - Should be True if the Stage was exported using payload files to store the actual Mesh prims. Also dictates minor behaviors when authoring the material binding relationships.
- L495 _prototype_ `FString HashGeomMeshPrim(const UE::FUsdStage& Stage, const FString& PrimPath, double TimeCode);` (scope `UsdUtils`) — Hashes the attributes of the GeomMesh at the given prim path on the Stage at TimeCode If the prim path is invalid or not a GeomMesh, it will return an empty hash
- L496 _prototype_ `void HashGeomMeshPrim(const UE::FUsdStage& Stage, const FString& PrimPath, double TimeCode, FMD5& InOutHashState);` (scope `UsdUtils`)
- L502 _prototype_ `bool GetPointInstancerTransforms( const FUsdStageInfo& StageInfo, const pxr::UsdGeomPointInstancer& PointInstancer, const int32 ProtoIndex, pxr::UsdTimeCode EvalTime, TArray<FTransform>& OutInstanceTransforms );` (scope `UsdUtils`) — Places in OutInstanceTransforms the UE-space instance transforms for a given point instancer prototype index. Returns whether the transforms were successfully retrieved or not.
- L522 _prototype_ `void GetPointInstancerInstancesData(const pxr::UsdPrim& Prim, FUsdPointInstancerInstancesData& InstancesData);` (scope `UsdUtils`) — Acquires the Prototypes from the PointInstancer and the related InstanceTransforms.
- L525 _prototype_ `bool IsAnimatedMesh(const pxr::UsdPrim& Prim);` (scope `UsdUtils`) — Returns true if Prim is a GeomMesh with animated attributes
- L527 _prototype_ `void GetAnimatedMeshTimeCodes(const UE::FUsdStage& Stage, const FString& PrimPath, int32& OutStartFrame, int32& OutEndFrame);` (scope `UsdUtils`)
- L530 _prototype_ `TArray<UE::FUsdAttribute> GetAnimatedMeshAttributes(const pxr::UsdPrim& Prim);` (scope `UsdUtils`) — Returns all of the Prim UsdGeomMesh-related attributes (points, faceVertexIndices, etc.) that contain timeSamples
- L541 _prototype_ `EMeshTopologyVariance GetMeshTopologyVariance(const pxr::UsdGeomMesh& UsdMesh);` (scope `UsdUtils`) — Returns the type of topology variance UsdMesh has
- L542 _prototype_ `EMeshTopologyVariance GetMeshTopologyVariance(const UE::FUsdPrim& UsdPrim);` (scope `UsdUtils`)
- L544 _prototype_ `uint64 GetGprimVertexCount(const pxr::UsdGeomGprim& Gprim, double TimeCode);` (scope `UsdUtils`)
- L546 _prototype_ `void AuthorIdentityTransformGprimAttributes(const pxr::UsdPrim& Gprim, bool bDefaultValues, bool bTimeSampleValues);` (scope `UsdUtils`)

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDGroomConversion.h` (Public)


#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UsdToUnreal`
- L35 _prototype_ `bool ConvertGroomHierarchy( const pxr::UsdPrim& Prim, const pxr::UsdTimeCode& TimeCode, const FTransform& ParentTransform, FHairDescription& HairDescription, FGroomAnimationInfo* AnimInfo = nullptr, bool bCheckGroomAttributes = true );` (scope `UsdToUnreal`) — Converts an UsdPrim groom hierarchy and appends the converted data to HairDescription @param Prim - Prim to convert @param TimeCode - The timecode at which to query the prim attributes @param ParentTransform - The prim transform to propagate to the children @param HairDescription - The hair description where the groom prim data is outputted @param AnimInfo -  Optional GroomAnimationInfo to fill when parsing the hierarchy @param bCheckGroomAttributes -  Optional Whether to check the groom-scope attributes, should only be checked (true) on the top-level prim @return true if the conversion was successful; false otherwise

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDIntegrationUtils.h` (Public)


#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UsdUtils`
- L26 _prototype_ `bool PrimHasSchema(const pxr::UsdPrim& Prim, const pxr::TfToken& Schema);` (scope `UsdUtils`) — Returns true if Prim has the given Schema
- L29 _prototype_ `bool CanApplySchema(pxr::UsdPrim Prim, pxr::TfToken SchemaName);` (scope `UsdUtils`) — Returns true if we can apply a single-apply API schema named "SchemaName" to Prim
- L32 _prototype_ `bool ApplySchema(const pxr::UsdPrim& Prim, const pxr::TfToken& Schema);` (scope `UsdUtils`) — Apply the given Schema to the Prim. Returns true if the application was successful
- L35 _prototype_ `bool CanRemoveSchema(pxr::UsdPrim Prim, pxr::TfToken SchemaName);` (scope `UsdUtils`) — Returns true if we can remove a single-apply API schema named "SchemaName" from Prim
- L38 _prototype_ `bool RemoveSchema(const pxr::UsdPrim& Prim, const pxr::TfToken& Schema);` (scope `UsdUtils`) — Remove the given Schema from the Prim. Returns true if was successful
- L42 _namespace_ `namespace UnrealToUsd`
- L52 _prototype_ `void ConvertLiveLinkProperties(const UActorComponent* InComponent, pxr::UsdPrim& InOutPrim);` (scope `UnrealToUsd`) — Converts UE component properties related to LiveLink into values for the attributes of our custom LiveLinkAPI schema. @param InComponent		The main component with data to convert @param InOutPrim			Prim with the LiveLinkAPI schema to receive the data

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDLayerUtils.h` (Public)


#### enum `UsdUtils::EBrowseFileMode`  
`enum class EBrowseFileMode`  
_L39-49_
- L42 _public enumerator_ `Open` — Browse for a file for the purpose of opening a stage with that file as the stage's root layer.
- L45 _public enumerator_ `Composition` — Browse for a file for the purpose of using that file as the target of a composition arc (e.g. a sublayer, reference, payload, etc.).
- L48 _public enumerator_ `Save` — Browse for a file for the purpose of saving or exporting a layer to that file.

#### enum `UsdUtils::EUSDZDecompressResult`  
`enum class EUSDZDecompressResult`  
_L51-61_
- L54 _public enumerator_ `Failed` — Extraction failed due to invalid, unsafe, or unsupported archive contents.
- L57 _public enumerator_ `SuccessWithSkippedEntries` — Extraction succeeded, but some entries were skipped.
- L60 _public enumerator_ `Success` — Extraction succeeded with all entries processed.

#### enum `UsdUtils::ECanInsertSublayerResult`  
`enum class ECanInsertSublayerResult`  
_L63-70_
- L65 _public enumerator_ `Success`
- L66 _public enumerator_ `ErrorSubLayerNotFound`
- L67 _public enumerator_ `ErrorSubLayerInvalid`
- L68 _public enumerator_ `ErrorSubLayerIsParentLayer`
- L69 _public enumerator_ `ErrorCycleDetected`

#### Free symbols / members of external scopes

- L26 _typedef_ `using SdfLayerRefPtr = TfRefPtr<SdfLayer>;`
- L27 _typedef_ `using UsdStageRefPtr = TfRefPtr<UsdStage>;`
- L30 _namespace_ `namespace UE`
- L37 _namespace_ `namespace UsdUtils`
- L71 _prototype_ `FText ToText(ECanInsertSublayerResult Result);` (scope `UsdUtils`)
- L77 _prototype_ `ECanInsertSublayerResult CanInsertSubLayer(const pxr::SdfLayerRefPtr& ParentLayer, const TCHAR* SubLayerIdentifier);` (scope `UsdUtils`) — Checks whether we can add SubLayerIdentifier as a sublayer to ParentLayer. The index is actually not relevant.
- L89 _prototype_ `bool InsertSubLayer( const pxr::SdfLayerRefPtr& ParentLayer, const TCHAR* SubLayerFile, int32 Index = -1, double OffsetTimeCodes = 0.0, double TimeCodesScale = 1.0 );` (scope `UsdUtils`) — Inserts the SubLayerFile path into ParentLayer as a sublayer @param ParentLayer - Layer to receive the new sublayer entry @param SubLayerFile - Absolute path to a usd file to use as sublayer @param Index - Zero-based index on the list of ParentLayer's sublayers list to insert the new sublayer. -1 means "at the end" (the default) @param OffsetTimeCodes - Offset in USD time codes to use for the sublayer reference @param TimeCodesScale - Scale to use for the sublayer reference @return Whether the sublayer reference was added successfully or not
- L99 _prototype_ `TOptional<FString> BrowseUsdFile(EBrowseFileMode Mode);` (scope `UsdUtils`) — Opens a file dialog to open or save a USD file. The returned file path will always be absolute
- L107 _prototype_ `FString MakePathRelativeToProjectDir(const FString& Path);` (scope `UsdUtils`) — Converts the file path from being absolute or relative to engine binary, into being relative to the current project's directory. It will only do this if the file is actually within the project's directory (or within its folder tree). Otherwise it will return an absolute path
- L114 _prototype_ `bool IsZipArchive(const FString& InUSDZFilePath);` (scope `UsdUtils`)
- L120 _prototype_ `bool SplitUSDZAssetPath(const FString& InFilePathIntoUSDZArchive, FString& OutUSDZFilePath, FString& OutInnerAssetPath);` (scope `UsdUtils`) — If InFilePathIntoUSDZArchive is a path to something inside an USDZ file, like "C:/MyFiles/scene.usdz[0/texture.png]", this will put "C:/MyFiles/scene.usdz" on OutUSDZFilePath, and "0/texture.png" on OutInnerAssetPath and return true. Returns false when it can't split the provided path in that way.
- L129 _prototype_ `EUSDZDecompressResult DecompressUSDZFile(const FString& InUSDZFilePath, const FString& InOutputDir, FString* OutDecompressedRootLayer = nullptr);` (scope `UsdUtils`) — If InUSDZFilePath points at an actual USDZ file, this function will decompress the archive and put its contents inside InOutputDir, returning Success or SuccessWithSkippedEntries if succeeding. In that case OutDecompressedRootLayer will also be set to the path of the root layer of the decompressed USDZ archive. Note that for safety reasons, InOutputDir must not exist prior to calling this function. The directory will be created once the zip file contents have been validated, and will be removed if an error is encountered during decompression.
- L132 _prototype_ `TUsdStore<pxr::SdfLayerRefPtr> CreateNewLayer( TUsdStore<pxr::UsdStageRefPtr> UsdStage, const TUsdStore<pxr::SdfLayerRefPtr>& ParentLayer, const TCHAR* LayerFilePath );` (scope `UsdUtils`) — Creates a new layer with a default prim
- L139 _prototype_ `UE::FSdfLayer FindLayerForPrim(const pxr::UsdPrim& Prim);` (scope `UsdUtils`) — Finds which layer introduced the prim in the stage local layer stack
- L142 _prototype_ `UE::FSdfLayer FindLayerForAttribute(const pxr::UsdAttribute& Attribute, double TimeCode);` (scope `UsdUtils`) — Finds the strongest layer contributing to an attribute
- L146 _prototype_ `UE::FSdfLayer FindLayerForAttributes( const TArray<UE::FUsdAttribute>& Attributes, double TimeCode, bool bIncludeSessionLayers = true );` (scope `UsdUtils`) — `UE_DEPRECATED(5.7, "Use UsdUtils::GetStrongestAttribute() and then UsdUtils::FindLayerForAttribute()")` — Finds the strongest layer that contributes to a set of attributes. Assumes these attributes are on the same stage
- L153 _prototype_ `UE::FSdfLayer FindLayerForSubLayerPath(const UE::FSdfLayer& RootLayer, const FStringView& SubLayerPath);` (scope `UsdUtils`) — Finds the layer for a sublayer path of a given root layer
- L156 _prototype_ `bool SetRefOrPayloadLayerOffset(pxr::UsdPrim& Prim, const UE::FSdfLayerOffset& LayerOffset);` (scope `UsdUtils`) — Sets the layer offset for the strongest reference or payload in this prim composition arcs
- L159 _prototype_ `UE::FSdfLayerOffset GetLayerToStageOffset(const pxr::UsdAttribute& Attribute);` (scope `UsdUtils`) — Finds the layer offset that converts the Attribute local times to stage times
- L162 _prototype_ `UE::FSdfLayerOffset GetPrimToStageOffset(const UE::FUsdPrim& Prim);` (scope `UsdUtils`) — Finds the full offset for a prim with respect to the composed stage
- L165 _prototype_ `void AddTimeCodeRangeToLayer(const pxr::SdfLayerRefPtr& Layer, double StartTimeCode, double EndTimeCode);` (scope `UsdUtils`) — Makes sure that the layer start and end timecodes include StartTimeCode and EndTimeCode
- L168 _prototype_ `void MakePathRelativeToLayer(const UE::FSdfLayer& Layer, FString& Path);` (scope `UsdUtils`) — Makes Path relative to the file path of Layer. Conversion happens in-place.
- L172 _prototype_ `UE::FSdfLayer GetUEPersistentStateSublayer(const UE::FUsdStage& Stage, bool bCreateIfNeeded = true);` (scope `UsdUtils`) — Loads and returns the session sublayer that is used for storing persistent UE state, which can be saved to disk (e.g. metadata for whether an attribute is muted or not)
- L176 _prototype_ `UE::FSdfLayer GetUESessionStateSublayer(const UE::FUsdStage& Stage, bool bCreateIfNeeded = true);` (scope `UsdUtils`) — Loads and returns the anonymous session sublayer that is used for storing transient UE session state, and won't be saved to disk (e.g. the opinion that actually mutes the attribute)
- L180 _prototype_ `UE::FSdfLayer FindLayerForIdentifier(const TCHAR* Identifier, const UE::FUsdStage& Stage);` (scope `UsdUtils`) — Uses FindOrOpen to return the layer with the given identifier if possible. If the identifier is for an anonymous layer, it will search via display name instead
- L183 _prototype_ `bool IsSessionLayerWithinStage(const pxr::SdfLayerRefPtr& Layer, const pxr::UsdStageRefPtr& Stage);` (scope `UsdUtils`) — Returns true if Layer is a session layer within Stage's layer stack
- L189 _prototype_ `UE::FSdfLayer FlattenLayerStack(const pxr::UsdStageRefPtr& Stage);` (scope `UsdUtils`) — Uses the USD SDK's pxr::UsdUtilsFlattenLayerStack to essentially flatten all the sublayer composition into a single layer, preserving other composition arcs like references and payloads
- L195 _prototype_ `void ConvertAssetRelativePathsToAbsolute(UE::FSdfLayer& LayerToConvert, const UE::FSdfLayer& AnchorLayer);` (scope `UsdUtils`) — Finds all fields that have asset paths as values (e.g. texture references) in LayerToConvert and (if they're relative paths) updates them to be absolute with respect to AnchorLayer. LayerToConvert and AnchorLayer can be the same layer, but they don't have to
- L197 _prototype_ `int32 GetSdfLayerNumFrames(const pxr::SdfLayerRefPtr& Layer);` (scope `UsdUtils`)

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDLightConversion.h` (Public)


#### Free symbols / members of external scopes

- L31 _typedef_ `using UsdStageRefPtr = TfRefPtr<UsdStage>;`
- L59 _namespace_ `namespace UsdToUnreal`
- L61 _prototype_ `bool ConvertLight( const pxr::UsdPrim& Prim, ULightComponentBase& LightComponent, double UsdTimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UsdToUnreal`)
- L66 _prototype_ `bool ConvertDistantLight( const pxr::UsdPrim& Prim, UDirectionalLightComponent& LightComponent, double UsdTimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UsdToUnreal`)
- L71 _prototype_ `bool ConvertRectLight( const pxr::UsdPrim& Prim, URectLightComponent& LightComponent, double UsdTimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UsdToUnreal`)
- L76 _prototype_ `bool ConvertDiskLight( const pxr::UsdPrim& Prim, URectLightComponent& LightComponent, double UsdTimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UsdToUnreal`)
- L81 _prototype_ `bool ConvertSphereLight( const pxr::UsdPrim& Prim, UPointLightComponent& LightComponent, double UsdTimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UsdToUnreal`)
- L86 _prototype_ `bool ConvertLuxShapingAPI( const pxr::UsdPrim& Prim, USpotLightComponent& LightComponent, double UsdTimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UsdToUnreal`)
- L93 _prototype_ `float ConvertLightIntensity(float UsdIntensity, float UsdExposure);` (scope `UsdToUnreal`) — Applies the USD exposure, essentially just returning UsdIntensity * 2.0^(UsdExposure)
- L103 _prototype_ `void ConvertSpotLightConeAngles(float InConeAngle, float InConeSoftness, float& OutOuterConeAngle, float& OutInnerConeAngle);` (scope `UsdToUnreal`) — Receives InConeAngle (degrees) and InConeSoftness ([0,1] range) USD spot light property values, and produces the corresponding Unreal outer and inner cone angles (also degrees) for a spot light component. Softness 0 corresponds to a hard transition where the outer and inner angle the same: Max brightness from center until the cone angle, and zero after it Softness 0.5 corresponds to an inner angle with half the size of the outer angle: Max brightness until the inner angle, and it lerps to zero until the outer angle Softness 1 corresponds to zero inner angle, so the brightness lerps from max at the center all the way to zero on the outer cone angle
- L106 _prototype_ `float ConvertLightIntensityAttr(float UsdIntensity, float UsdExposure);` (scope `UsdToUnreal`) — `UE_DEPRECATED(5.8, "This has been renamed to ConvertLightIntensity.")`
- L108 _prototype_ `float ConvertDistantLightIntensityAttr(float UsdIntensity, float UsdExposure);` (scope `UsdToUnreal`) — `UE_DEPRECATED(5.8, "No longer used as this implicitly hard-coded the intensity units. Compute the solid angle and area with the other utils functions and use ConvertIntensityFromNits.")`
- L110 _prototype_ `float ConvertRectLightIntensityAttr(float UsdIntensity, float UsdExposure, float UsdWidth, float UsdHeight, const FUsdStageInfo& StageInfo);` (scope `UsdToUnreal`) — `UE_DEPRECATED(5.8, "No longer used as this implicitly hard-coded the intensity units. Compute the solid angle and area with the other utils functions and use ConvertIntensityFromNits.")`
- L112 _prototype_ `float ConvertDiskLightIntensityAttr(float UsdIntensity, float UsdExposure, float UsdRadius, const FUsdStageInfo& StageInfo);` (scope `UsdToUnreal`) — `UE_DEPRECATED(5.8, "No longer used as this implicitly hard-coded the intensity units. Compute the solid angle and area with the other utils functions and use ConvertIntensityFromNits.")`
- L114 _prototype_ `float ConvertSphereLightIntensityAttr(float UsdIntensity, float UsdExposure, float UsdRadius, const FUsdStageInfo& StageInfo);` (scope `UsdToUnreal`) — `UE_DEPRECATED(5.8, "No longer used as this implicitly hard-coded the intensity units. Compute the solid angle and area with the other utils functions and use ConvertIntensityFromNits.")`
- L116 _prototype_ `float ConvertLuxShapingAPIIntensityAttr(float UsdIntensity, float UsdExposure, float UsdRadius, float UsdConeAngle, float UsdConeSoftness, const FUsdStageInfo& StageInfo);` (scope `UsdToUnreal`) — `UE_DEPRECATED(5.8, "No longer used as this implicitly hard-coded the intensity units. Compute the solid angle and area with the other utils functions and use ConvertIntensityFromNits.")`
- L118 _prototype_ `float ConvertConeAngleSoftnessAttr(float UsdConeAngle, float UsdConeSoftness, float& OutInnerConeAngle);` (scope `UsdToUnreal`) — `UE_DEPRECATED(5.8, "Use ConvertSpotLightConeAngles().")`
- L121 _namespace_ `namespace UnrealToUsd`
- L123 _prototype_ `bool ConvertLightComponent( const ULightComponentBase& LightComponent, pxr::UsdPrim& Prim, double UsdTimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UnrealToUsd`)
- L128 _prototype_ `bool ConvertDirectionalLightComponent( const UDirectionalLightComponent& LightComponent, pxr::UsdPrim& Prim, double UsdTimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UnrealToUsd`)
- L133 _prototype_ `bool ConvertRectLightComponent( const URectLightComponent& LightComponent, pxr::UsdPrim& Prim, double UsdTimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UnrealToUsd`)
- L138 _prototype_ `bool ConvertPointLightComponent( const UPointLightComponent& LightComponent, pxr::UsdPrim& Prim, double UsdTimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UnrealToUsd`)
- L143 _prototype_ `bool ConvertSkyLightComponent( const USkyLightComponent& LightComponent, pxr::UsdPrim& Prim, double UsdTimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UnrealToUsd`)
- L148 _prototype_ `bool ConvertSpotLightComponent( const USpotLightComponent& LightComponent, pxr::UsdPrim& Prim, double UsdTimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UnrealToUsd`)
- L158 _prototype_ `void ConvertSpotLightConeAngles(float InOuterConeAngle, float InInnerConeAngle, float& OutConeAngle, float& OutConeSoftness);` (scope `UnrealToUsd`) — Produces the USD cone angle (degrees) and softness ([0,1] range) values for a spot light that corresponds to an unreal outer and inner cone angles (also degrees). This is the inverse of UsdToUnreal::ConvertSpotLightConeAngles().
- L161 _prototype_ `float ConvertLightIntensityProperty(float Intensity);` (scope `UnrealToUsd`) — `UE_DEPRECATED(5.8, "No longer used as it didn't really do anything.")`
- L163 _prototype_ `float ConvertRectLightIntensityProperty(float Intensity, float Width, float Height, const FUsdStageInfo& StageInfo, ELightUnits SourceUnits);` (scope `UnrealToUsd`) — `UE_DEPRECATED(5.8, "Compute the solid angle and area with the other utils functions and use ConvertIntensityToNits().")`
- L165 _prototype_ `float ConvertRectLightIntensityProperty(float Intensity, float Radius, const FUsdStageInfo& StageInfo, ELightUnits SourceUnits);` (scope `UnrealToUsd`) — `UE_DEPRECATED(5.8, "Compute the solid angle and area with the other utils functions and use ConvertIntensityToNits().")`
- L167 _prototype_ `float ConvertPointLightIntensityProperty(float Intensity, float SourceRadius, const FUsdStageInfo& StageInfo, ELightUnits SourceUnits);` (scope `UnrealToUsd`) — `UE_DEPRECATED(5.8, "Compute the solid angle and area with the other utils functions and use ConvertIntensityToNits().")`
- L169 _prototype_ `float ConvertSpotLightIntensityProperty(float Intensity, float OuterConeAngle, float InnerConeAngle, float SourceRadius, const FUsdStageInfo& StageInfo, ELightUnits SourceUnits);` (scope `UnrealToUsd`) — `UE_DEPRECATED(5.8, "Compute the solid angle and area with the other utils functions and use ConvertIntensityToNits().")`
- L171 _prototype_ `float ConvertOuterConeAngleProperty(float OuterConeAngle);` (scope `UnrealToUsd`) — `UE_DEPRECATED(5.8, "Use ConvertSpotLightConeAngles().")`
- L173 _prototype_ `float ConvertInnerConeAngleProperty(float InnerConeAngle, float OuterConeAngle);` (scope `UnrealToUsd`) — `UE_DEPRECATED(5.8, "Use ConvertSpotLightConeAngles().")`
- L176 _namespace_ `namespace UsdUtils`
- L182 _prototype_ `float GetRectLightSideFromDiskLight(float DiskLightRadius);` (scope `UsdUtils`) — Returns the side length of a square that possesses the same area as a circle with DiskLightRadius. Output units are the same as the input units.
- L188 _prototype_ `float GetDiskLightRadiusFromRectLight(float RectLightWidth, float RectLightHeight);` (scope `UsdUtils`) — Returns the radius of a circle that posseses the same area as a rectangle with sides RectLightWidth and RectLightHeight Output units are the same as the input units.
- L194 _prototype_ `float GetRectLightArea(float Width, float Height);` (scope `UsdUtils`) — Returns the values that should be used as "surface area" for unreal lights of different types. Output units are the square of the input units.
- L195 _prototype_ `float GetDiskLightArea(float Radius);` (scope `UsdUtils`)
- L196 _prototype_ `float GetPointLightArea(float Radius);` (scope `UsdUtils`)
- L197 _prototype_ `float GetSpotLightArea(float Radius);` (scope `UsdUtils`)
- L200 _prototype_ `float GetRectLightSolidAngle();` (scope `UsdUtils`) — Returns the values that should be used as "solid angle" for unreal lights of different types, in steradians.
- L201 _prototype_ `float GetDiskLightSolidAngle();` (scope `UsdUtils`)
- L202 _prototype_ `float GetPointLightSolidAngle();` (scope `UsdUtils`)
- L203 _prototype_ `float GetSpotLightSolidAngle(float OuterConeAngle, float InnerConeAngle);` (scope `UsdUtils`)
- L206 _prototype_ `float ConvertIntensityToNits(float Intensity, float SolidAngle, float AreaInSqMeters, ELightUnits SourceUnits);` (scope `UsdUtils`) — For a light with the provided SolidAngle and surface AreaInSqMeters, converts the Intensity value in the provided SourceUnits into Intensity in Nits
- L209 _prototype_ `float ConvertIntensityFromNits(float Intensity, float SolidAngle, float AreaInSqMeters, ELightUnits DestUnits);` (scope `UsdUtils`) — For a light with the provided SolidAngle and surface AreaInSqMeters, converts the Intensity value in Nits into the provided DestUnits
- L220 _prototype_ `template<typename T> T GetLightAttrValueWithInputsFallback( const pxr::UsdAttribute& Attribute, double UsdTimeCode = UsdUtils::GetDefaultTimeCode(), bool* bOutIsAuthored = nullptr );` (scope `UsdUtils`) — Reads the value of Attribute at the given time code. If the attribute has no authored opinion and its name starts with "inputs:", strips the prefix and tries the unprefixed attribute. This handles backwards compatibility with pre-21.05 USD scenes. If bOutIsAuthored is non-null, sets it to true if the value came from an authored opinion (either on the original attribute or the fallback), false if it's only a schema default.

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDMaterialXShaderGraph.h` (Public)


#### class `FUsdMaterialXShaderGraph`  
`class FUsdMaterialXShaderGraph`  
_L35-135_
- desc: Create a MaterialX shader graph from a UsdPrim, all <geompropvalue> nodes are either converted to an <image> or a proper <geomcolor> Just get the Document in order to search for the surface material, by just looking for the name of the Prim it will return the correct surface material.
- L51 _public prototype_ `FUsdMaterialXShaderGraph(const pxr::UsdPrim& MaterialPrim, const TCHAR* RenderContext);` — @param UsdShadeMaterialPrim - The prim used to generate the shader graph, should be a valid pxr::UsdShadeMaterial @param RenderContext - Which render context output to read from the UsdShadeMaterial
- L53 _public prototype_ `MaterialX::DocumentPtr GetDocument() const;`
- L56 _public prototype_ `const TArray<FGeomProp>& GetGeomPropValueNames() const;` — Return the names of the <geompropvalue> nodes which have converted to <image> node
- L61 _private prototype_ `void CreateMaterial(const pxr::UsdShadeMaterial& UsdShadeMaterial, const TCHAR* RenderContext);` — Create either a <surfacematerial> or a <volumematerial> if possible.
- L63 _private prototype_ `bool ComputeShaderGraph(MaterialX::NodePtr Node, const pxr::UsdShadeShader& Shader, MaterialX::GraphElementPtr Graph);`
- L65 _private prototype_ `bool IsGeomColor(const pxr::UsdShadeShader& GeomPropValueShader);`
- L67 _private prototype_ `void SetInputValue(MaterialX::InputPtr Input, const pxr::UsdShadeInput& UsdInput);`
- L70 _private prototype_ `bool SetInterfaceName(MaterialX::InputPtr Input, const pxr::UsdShadeConnectionSourceInfo& Source, MaterialX::GraphElementPtr Graph);` — Set the interfaceName of the input if any
- L79 _private prototype_ `MaterialX::NodePtr GetNode(const pxr::UsdShadeConnectionSourceInfo& Source, MaterialX::GraphElementPtr Graph, bool& bIsNodeAlreadyExist);` — Get the MaterialX node from a UsdShadeConnectionSourceInfo @param Source - upstream source in the Shader Graph, usually the connected node to an input @param Graph - either the Document or a nodegraph @param bIsNodeAlreadyExist - return true if the node was already present in the shader graph, false otherwise @return The corresponding MaterialX node in the shader graph, if it doesn't exist it creates one
- L81 _private prototype_ `MaterialX::InputPtr GetInput(MaterialX::NodePtr Node, const pxr::UsdShadeInput& UsdInput);`
- L83 _private prototype_ `MaterialX::NodeDefPtr GetNodeDef(const pxr::UsdShadeConnectionSourceInfo& Source, bool& bIsGeomPropValue);`
- L85 _private prototype_ `MaterialX::NodeGraphPtr GetNodeGraph(const pxr::UsdShadeConnectionSourceInfo& Source, MaterialX::GraphElementPtr Graph);`
- L92 _private prototype_ `bool GetMatchingType(const std::string& Name, std::string& InOutType);` — Given an input/output type, retrieve the MaterialX associated type @param Name - The name of the input/output @param InOutType - The type of the input/output, if it's valid it will now be the MaterialX type @return true if there is a valid match between USD and MaterialX or if it's already a MaterialX type, false otherwise
- L94 _private prototype_ `bool IsTangentSpaceInput(const pxr::UsdShadeInput& UsdInput) const;`
- L96 _private prototype_ `void GetInterfaceNameInputs(const pxr::UsdShadeNodeGraph& UsdShadeGraph, MaterialX::GraphElementPtr Graph);`
- L100 _private member_ `std::unordered_set<std::string> MaterialXTypes;`
- L102 _private member_ `std::unordered_map<std::string, std::string> UsdToMaterialXTypes;`
- L105 _private member_ `std::unordered_set<std::string> TangentSpaceInputs;` — Names of the inputs from a <surfaceshader> that requires to be in tangent space for the baking of the primvars later on
- L108 _private member_ `std::unordered_map<MaterialX::GraphElementPtr, std::unordered_set<std::string>> InterfaceNames;` — MaterialX interfacenames relatives to their nodegraph (the Document if no nodegraph), some inputs use them instead of a value or a direct connection to a node
- L110 _private member_ `MaterialX::DocumentPtr Document;`
- L112 _private member_ `TArray<FGeomProp> GeomPropValueNames;`
- L114 _private member_ `bool bTangentSpaceInput = false;`
- L116 _private member_ `bool bConvertGeomPropValueToSparseVolume = false;`
- L123 _private typedef_ `template<typename MtlxType> using FPairingUsdMtlxType_t = std::conditional_t< std::is_same_v<MtlxType, MaterialX::Color4> || std::is_same_v<MtlxType, MaterialX::Vector4>, pxr::GfVec4f, std::conditional_t< std::is_same_v<MtlxType, MaterialX::Color3> || std::is_same_v<MtlxType, MaterialX::Vector3>, pxr::GfVec3f, std::conditional_t< std::is_same_v<MtlxType, MaterialX::Vector2>, pxr::GfVec2f, MtlxType>>>;` — complex template to just retrieve the right type, basically a mapping between Usd and Mtlx for Vector types, otherwise we just take the type (float, int, string)

#### struct `FUsdMaterialXShaderGraph::FGeomProp`  
`struct FGeomProp`  
_L39-43_
- L41 _public member_ `FString Name;`
- L42 _public member_ `bool bTangentSpace = false;`

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDNaniteAssemblyUtils.h` (Public)


#### enum `UsdToUnreal::NaniteAssemblyUtils::ENaniteAssemblyMeshType`  
`enum class ENaniteAssemblyMeshType : uint32`  
_L22-30_
- L25 _public enumerator_ `None` — The prim either does not have the root API schema or has an invalid meshType
- L27 _public enumerator_ `StaticMesh` — Static Mesh Nanite assembly root
- L29 _public enumerator_ `SkeletalMesh` — Skeletal Mesh Nanite assembly root

#### enum `UsdToUnreal::NaniteAssemblyUtils::EMeshCategory`  
`enum class EMeshCategory : uint32`  
_L37-47_
- desc: Nanite assembly static/skeletal meshes must be categorized as either a 'base' or a 'part'. Base meshes reference part meshes and instance them one or more times via Nanite assembly nodes. Note that Nanite assembly meshes cannot currently be nested, and so a mesh cannot be both a base and part mesh.
- L40 _public enumerator_ `None` — No category determined for this mesh
- L43 _public enumerator_ `Base` — This mesh is a base mesh. It will depend on one one more referenced part meshes.
- L46 _public enumerator_ `Part` — This mesh is a part mesh, used by one or more base meshes.

#### struct `UsdToUnreal::NaniteAssemblyUtils::FPrimPrototypeEntry`  
`struct FPrimPrototypeEntry`  
_L54-66_
- desc: Basic structure to hold information about the current pointinstancer, the current prototype path, and the corresponding prototype index, as it relates to an instance proxy mesh. A stack of these entries can be used to fully describe nested pointinstancer subtrees.
- L56 _public member_ `UE::FSdfPath PointInstancerPrimPath;`
- L59 _public member_ `UE::FSdfPath PrototypePrimPath;` — The active prototype of the above pointinstancer
- L62 _public member_ `int32 PrototypeIndex;` — The index of the above prototype
- L65 _public member_ `int32 PrototypeCount;` — The total number of prototypes used by the pointinstancer

#### struct `UsdToUnreal::NaniteAssemblyUtils::FMeshEntry`  
`struct FMeshEntry`  
_L71-100_
- desc: Mesh structure to hold assembly meshes.
- L74 _public member_ `const EMeshCategory Category = EMeshCategory::None;` — The category of this mesh.
- L77 _public member_ `const UE::FSdfPath PrimPath;` — The full instance proxy path of this mesh
- L81 _public member_ `const UE::FSdfPath SkelBindingPath;` — For skeletal mesh parts, the path of the (possibly ancestor) prim with NaniteAssemblySkelBindingAPI binding info applied (empty for static mesh parts)
- L84 _public member_ `const TArray<FTransform> TransformStack;` — The transform stack for this mesh for the case of nested pointinstancers
- L87 _public member_ `const TArray<FPrimPrototypeEntry> PrototypeStack;` — The prototype stack for this mesh for the case of nested pointinstancers
- L90 _public member_ `FString NodeUid;` — The interchange node uid of this mesh.
- L92 _public prototype_ `FMeshEntry( EMeshCategory Category, const UE::FSdfPath& PrimPath, const UE::FSdfPath& SkelBindingPath, const TArray<FTransform>& TransformStack, const TArray<FPrimPrototypeEntry>& PrototypeStack);`
- L99 _public prototype_ `void Print() const;`

#### struct `UsdToUnreal::NaniteAssemblyUtils::FPrototypesToPartsRemappingInfo`  
`struct FPrototypesToPartsRemappingInfo`  
_L106-130_
- desc: Structure to hold mapping information between source pointinstancer prototypes and their prims, and interchange uids used for the corresponding Nanite assembly parts.
- L109 _public member_ `TArray<TArray<FString>> PartUids;` — The arrays of part mesh uids generated by the pointinstancers prototype meshes
- L113 _public member_ `TArray<FTransform> LocalTransforms;` — Local space transforms needed to transform the parts into the correct space for the current pointinstancer and prototype
- L117 _public member_ `TMap<int32, FInt32Range> OriginalPrototypeIndexToNewPartRangeTable;` — A table mapping original pointinstancer prototype indices into the corresponding range of part uids in the PartUids array
- L120 _public member_ `int32 OriginalPrototypeCount = INDEX_NONE;` — The original number of prototypes used by the originating pointinstancer
- L126 _public function_ `bool IsRemapped() const` — Returns true if the part uids were remapped, false otherwise. Part meshes that have the identity transform do not require remapping. When all the parts in the assembly have the identity transform no remapping is required, and the original PartUid array can be used as-is.

#### class `UsdToUnreal::NaniteAssemblyUtils::FNaniteAssemblyTraversalResult`  
`class FNaniteAssemblyTraversalResult`  
_L145-226_
- desc: Structure to retain the needed data of a Nanite assembly USD subtree for later use during payload retrieval. This data should be created during translation and utilized during payload retrieval to generate the corresponding UE::Interchange::FNaniteAssemblyDescription representation of the data. This data contains sufficient information about prototype meshes and their (potentially nested) hierarchies that it's unnecessary to re-traverse the USD assembly subtree a second time when creating the payload data. Prototype prim information such as paths and transforms is stored directly in the structure. Large pointinstancer arrays e.g. prototype indices, transforms, bone influences, are not stored. Computing these should be deferred until payload generation.
- L150 _public member_ `const ENaniteAssemblyMeshType AssemblyMeshType;` — The assembly mesh type (static or skeletal)
- L153 _public member_ `const UE::FSdfPath AssemblyRootPrimPath;` — Path of the prim with the NaniteAssemblyRootAPI schema applied
- L158 _private member_ `TArray<TSharedPtr<FMeshEntry>> Entries;` — Array of the USD meshes used as either base or parts of the assembly
- L161 _private member_ `TSet<UE::FSdfPath> EntryPaths;` — The mesh prim paths in this result
- L166 _public prototype_ `explicit FNaniteAssemblyTraversalResult( ENaniteAssemblyMeshType InMeshType, const UE::FSdfPath& InAssemblyRootPrimPath);` — Construct for the given mesh type and assembly root path.
- L170 _public prototype_ `bool AddEntry(const TSharedPtr<FMeshEntry>& Entry);`
- L173 _public prototype_ `bool IsMeshType(ENaniteAssemblyMeshType MeshType) const;` — returns true if the assembly this result represents is the given type, false otherwise.
- L176 _public prototype_ `TSet<UE::FSdfPath> GetTopLevelPointInstancerPaths() const;` — Get the top-level pointinstancer paths (used for instancing parts) contained in this assembly.
- L186 _public prototype_ `bool CheckAndGetNativeInstancedPartMeshEntries( TArray<TSharedPtr<FMeshEntry>>& OutEntries, TMap<FString, int32>& OutMeshUidToPartIndexTable, TArray<TArray<FString>>& OutPartUids) const;` — Get the non-pointinstancer native-instanced part meshes for this assembly. @param OutEntries                 Output array native-instanced part entries @param OutMeshUidToPartIndexTable Output table that maps mesh uids to the corresponding index in the OutPartUids array @param OutPartUids                Output array of arrays of part uids
- L198 _public prototype_ `bool CheckAndGetMeshEntriesByPrototypeIndex( const UE::FSdfPath& PointInstancerPrimPath, TMap<int32, TArray<TSharedPtr<FMeshEntry>>>& OutMeshEntriesByPrototypeIndex, int32& OutPrototypeCount) const;` — Get entries for the given pointinstancer arranged by prototype index. @param PointInstancerPrimPath         The pointinstancer in the assembly to query @param OutMeshEntriesByPrototypeIndex Output table that groups entries by their originating prototype index @param OutPrototypeCount              The total number of prototypes defined by the pointinstancer
- L210 _public prototype_ `bool GetRemappedPartsForTopLevelPointInstancer( const UE::FUsdPrim& PointInstancerPrim, int32 IndexStartOffset, FPrototypesToPartsRemappingInfo& OutRemappingInfo) const;` — Get the remapped part information for the given top-level pointinstancer. @param PointInstancerPrimPath The pointinstancer in the assembly to query @param IndexStartOffset       The index offset to apply to the generated mapping @param OutRemappingInfo       The output remapping info
- L216 _public prototype_ `bool HasEntriesForCategory(EMeshCategory Category) const;` — Return true if there are mesh entries for the given category, false otherwise
- L219 _public prototype_ `TArray<TSharedPtr<FMeshEntry>> GetEntriesForCategory(EMeshCategory Category) const;` — Get all the entries for the given category (part or base mesh)
- L222 _public prototype_ `TArray<FString> GetMeshUidsForCategory(EMeshCategory Category) const;` — Get all the interchange mesh uids for the given category
- L225 _public prototype_ `static TArray<FString> ConvertMeshEntryArrayToMeshUidArray(const TArray<TSharedPtr<FMeshEntry>>& Entries);` — Convert the given entries into an array of mesh uids

#### struct `UsdToUnreal::NaniteAssemblyUtils::FNaniteAssemblyPointInstancerData`  
`struct FNaniteAssemblyPointInstancerData`  
_L238-258_
- desc: Pointinstancer structure suitable for holding the regular pointinstancer properties (proto indices, transforms), as well as the additional joint binding data needed by skeletal mesh assemblies. Each pointinstancer instance will be translated into a Nanite assembly node. Rather than the regular array of prototype paths, a remapping table is available that maps assembly part meshes back to the original pointinstancer prototypes. This is needed because multiple pointinstancers can be combined into a single Nanite assembly mesh and so the indices need rearranging accordingly. .
- L240 _public member_ `TArray<int32> ProtoIndices;`
- L242 _public member_ `TArray<FTransform> Transforms;`
- L245 _public member_ `FPrototypesToPartsRemappingInfo ProtoRemappingInfo;` — Pointinstancer prototypes, assembly part arrays, and remapping ranges
- L248 _public member_ `TArray<int32> JointIndices;` — Joint binding indices for skeletal mesh assemblies (should be kept empty for static mesh assemblies)
- L251 _public member_ `TArray<float> JointWeights;` — Joint binding weights for skeletal mesh assemblies (should be kept empty for static mesh assemblies)
- L254 _public member_ `TArray<int32> NumInfluencesPerInstance;` — Nanite assembly bindings support multiple joints/weights (again, empty for static mesh assemblies).
- L257 _public member_ `bool bIsValid = false;` — Validity field, check this before attempting to access the data

#### class `UsdToUnreal::NaniteAssemblyUtils::FJointBindingHelper`  
`class FJointBindingHelper`  
_L261-286_
- desc: Simple utility class to efficiently resolve Nanite assembly joint bindings for multiple prims.
- L264 _private member_ `const FString SkelIdentifier;` — Skeleton identifier, used for log messages only
- L266 _private member_ `const TArray<FString> JointNames;`
- L268 _private member_ `const float Time = 0.f;`
- L270 _private member_ `TMap<FString, int32> JointIndexByJointNameTable;`
- L275 _public prototype_ `FJointBindingHelper(const FString& InSkelIdentifier, const TArray<FString>& InJointNames, float InTime);` — Initialize the helper with the given array of joint names.
- L281 _public prototype_ `bool Get( const UE::FUsdPrim& Prim, TArray<int32>& OutJointIndices, TArray<float>& OutJointWeights, int32& OutElementSize) const;` — Get the authored joint indices, weights and element size from the given prim. The prim must have the NaniteAssemblySkelBindingAPI schema applied.

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UsdToUnreal`
- L20 _namespace_ `namespace NaniteAssemblyUtils` (scope `UsdToUnreal`)
- L309 _prototype_ `bool GetJointBindingData( const UE::FUsdPrim& Prim, const FString& SkelIdentifier, const TArray<FString>& SkelJointNames, float Time, TArray<int32>& OutJointIndices, TArray<float>& OutJointWeights, int32& OutElementSize, const TMap<FString, int32>* JointIndexByJointNameTable = nullptr);` (scope `UsdToUnreal::NaniteAssemblyUtils`) — Get Nanite joint binding data from the given prim. The prim must have the NaniteAssemblySkelBindingAPI schema applied (the caller must check before calling this function). Regular and pointinstancer prims are supported. The given array of skeleton joint names is needed in order to convert the joint names supplied by the schema into indices relative to the meshes base skeleton. @param Prim            A prim with NaniteAssemblySkelBindingAPI applied (typically an xform or pointinstancer prim) @param SkelIdentifier  Used only for log messages. @param SkelJointNames  The array of joint names from the assembly base skeleton. @param OutJointIndices The joint binding indices, acquired via mandatory primvar 'primvars:unreal:naniteAssembly:bindJoints' @param OutJointWeights The joint binding weights, as specified by the optional primvar 'primvars:unreal:naniteAssembly:bindJointWeights' @param OutElementSize  The number of bindings per instance. @param JointIndexByJointNameTable Optional pre-generated table to accelerate joint index lookups @return                True if binding data was successfully retrieved, false otherwise
- L325 _prototype_ `ENaniteAssemblyMeshType GetNaniteAssemblyMeshType(const UE::FUsdPrim& NaniteAssemblyRootPrim);` (scope `UsdToUnreal::NaniteAssemblyUtils`) — Gets the Nanite assembly mesh type token ('staticMesh' or 'skeletalMesh'). The prim must have the NaniteAssemblyRootAPI schema applied (caller must check before calling this function). @return The mesh type, or ENaniteAssemblyMeshType::None if the given prim was invalid or misconfigured.
- L342 _prototype_ `bool GetExternalAssetReference(const UE::FUsdPrim& Prim, FString& OutAssetRef);` (scope `UsdToUnreal::NaniteAssemblyUtils`) — Check whether or not NaniteAssemblyExternalRefAPI is applied to the given prim, and if so, sets the output string to the value of the attribute 'unreal:naniteAssembly:meshAssetPath' (or an empty string if the attribute does not exist or is unauthored). Note that this function always returns true if NaniteAssemblyExternalRefAPI is applied, even if the specified string is not a valid asset or package. Since hierarchy traversal should always halt when this schema is encountered, the caller should use the return value irrespective of the validity of the supplied asset reference string. Since pipelines are, in theory, free to modify the assembly references if they want, it isn't really possible for translators to verify ahead of time anyway. @param Prim        The prim to check @param OutAssetRef The specified user asset reference @return            True if NaniteAssemblyExternalRefAPI is applied, false otherwise
- L352 _prototype_ `UE::FUsdPrim GetBaseSkeletonPrimForSkeletalMeshAssembly(const UE::FUsdPrim& NaniteAssemblyRootPrim);` (scope `UsdToUnreal::NaniteAssemblyUtils`) — Returns the base UsdSkelSkeleton prim for the given Nanite assembly root prim. Note that this function does not re-verify whether the NaniteAssemblyRootAPI schema is applied, or if the meshType attribute is set to "skeletalMesh". The caller must check before calling this function. @param NaniteAssemblyRootPrim The input prim @return                       A valid UsdSkelSkeleton prim on success, or an invalid prim if no skeleton could be found
- L359 _prototype_ `bool GetPointInstancerProtoIndices(const UE::FUsdPrim& PointInstancerPrim, float Time, TArray<int32>& OutProtoIndices);` (scope `UsdToUnreal::NaniteAssemblyUtils`) — Gets the masked prototype indices for the given pointinstancer prim at the given time. @return true if the prototype indices were successfully acquired, false otherwise.
- L366 _prototype_ `bool GetPointInstancerTransforms( const UE::FUsdPrim& PointInstancerPrim, const FTransform& ParentTransform, float Time, TArray<FTransform>& OutTransforms);` (scope `UsdToUnreal::NaniteAssemblyUtils`) — Gets the masked transforms multiplied by the given parent transform for the given pointinstancer prim at the given time. @return true if the transforms were successfully acquired, false otherwise.
- L375 _prototype_ `TArray<UE::FSdfPath> GetPointInstancerPrototypePaths(const UE::FUsdPrim& PointInstancerPrim);` (scope `UsdToUnreal::NaniteAssemblyUtils`) — Gets the array of prototype paths for the given pointinstancer prim.
- L389 _prototype_ `FNaniteAssemblyPointInstancerData GetPointInstancerData( const UE::FUsdPrim& PointInstancerPrim, const UsdToUnreal::FUsdMeshConversionOptions& Options, const FNaniteAssemblyTraversalResult& TraversalResult, const FString& SkelIdentifier, const TArray<FString>& JointNames, int32 PartIndexStartOffset = 0);` (scope `UsdToUnreal::NaniteAssemblyUtils`) — High-level wrapper of most of the above functions that, if everything is valid, returns a structure containing all the needed pointinstancer data to construct one or more instanced assembly parts. @param PointInstancerPrim   The pointinstancer prim to process. @param Options              The current mesh options, e.g. current time coordinate. @param TraversalResult      The FNaniteAssemblyTraversalResult containing instance and prototype information. @param SkelIdentifier       The base skeleton name for this assembly  (used only for log messages). @param JointNames           Array of joint names extracted from the base skeleton. @param PartIndexStartOffset The offset to use when generating remapped prototype/part slots. @return                     FNaniteAssemblyPointInstancerData instance, check the bIsValid member before using.

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDPrimConversion.h` (Public)


#### struct `UsdToUnreal::FPropertyTrackReader`  
`struct FPropertyTrackReader`  
_L189-195_
- desc: Struct with lambda functions that can be used to sample an FUsdPrim's attributes at a provided UsdTimeCode and return a converted result. The target prims, stage and the actual attributes are captured into the lambda when creating it with CreatePropertyTrackReader. This is used so that the reading process can be decoupled from the baking process (ConvertXTimeSamples functions) and reused for different attributes c.f. CreatePropertyTrackReader
- L191 _public member_ `TFunction<float(double)> FloatReader;`
- L192 _public member_ `TFunction<bool(double)> BoolReader;`
- L193 _public member_ `TFunction<FLinearColor(double)> ColorReader;`
- L194 _public member_ `TFunction<FTransform(double)> TransformReader;`

#### enum `UnrealToUsd::EBakingType`  
`enum class EBakingType : uint8`  
_L378-387_
- desc: We will defer to the common UnrealToUsd::ConvertXComponent functions when baking level sequences, which will already bake all of the properties of a component out at the same time. We use this enum to keep track of which type of baking was already being done for a component, so that if e.g. we have a track for camera aperture and another for camera focal length, we end up just baking that camera only once (as only once will be enough to handle all animated properties)
- L380 _public enumerator_ `None = 0`
- L381 _public enumerator_ `Transform = 1`
- L382 _public enumerator_ `Visibility = 2`
- L383 _public enumerator_ `Camera = 4`
- L384 _public enumerator_ `Light = 8`
- L385 _public enumerator_ `Skeletal = 16`
- L386 _public enumerator_ `Bounds = 32`

#### struct `UnrealToUsd::FComponentBaker`  
`struct FComponentBaker`  
_L392-397_
- desc: Contains a lambda function responsible for baking a USceneComponent on the level into a prim on an FUsdStage
- L394 _public member_ `EBakingType BakerType;`
- L395 _public member_ `FString ComponentPath;` — Used for sorting, to ensure we evaluate parents and skeletal stuff before children and attached stuff
- L396 _public member_ `TFunction<void(double UsdTimeCode)> BakerFunction;`

#### struct `UnrealToUsd::FPropertyTrackWriter`  
`struct FPropertyTrackWriter`  
_L433-441_
- desc: Struct with lambda functions that can be used to convert an UE property's value into the corresponding USD attribute values at the received UsdTimeCode. The target prims, stage and the actual attributes are captured into the lambda when creating it with CreatePropertyTrackWriter. This is used so that the writing process can be decoupled from the baking process (ConvertXTrack functions) and reused for different attributes c.f. CreatePropertyTrackWriter
- L435 _public member_ `TFunction<void(float, double)> FloatWriter;`
- L436 _public member_ `TFunction<void(bool, double)> BoolWriter;`
- L437 _public member_ `TFunction<void(const FLinearColor&, double)> ColorWriter;`
- L438 _public member_ `TFunction<void(const FVector&, const FVector&, double)> TwoVectorWriter;` — Just used for the bounds tracks, where we use a vector for min
- L440 _public member_ `TFunction<void(const FTransform&, double)> TransformWriter;` — and another for max

#### Free symbols / members of external scopes

- L28 _typedef_ `using UsdStageRefPtr = TfRefPtr<UsdStage>;`
- L60 _namespace_ `namespace UE`
- L66 _namespace_ `namespace UsdToUnreal`
- L77 _prototype_ `bool ConvertXformable( const pxr::UsdStageRefPtr& Stage, const pxr::UsdTyped& Schema, USceneComponent& SceneComponent, double EvalTime, bool bUsePrimTransform = true );` (scope `UsdToUnreal`) — Converts a pxr::UsdGeomXformable's attribute values into an USceneComponent's property values @param Stage - Stage that contains the prim to convert @param Schema - Prim to convert @param SceneComponent - Output component to receieve the converted data @param EvalTime - Time at which to sample the prim's attributes @param bUsePrimTransform - Whether to convert transform data or not @return Whether the conversion was successful or not.
- L94 _prototype_ `bool ConvertXformable( const pxr::UsdStageRefPtr& Stage, const pxr::UsdTyped& Schema, FTransform& OutTransform, double EvalTime, bool* bOutResetTransformStack = nullptr );` (scope `UsdToUnreal`) — Converts a pxr::UsdGeomXformable's transform attribute values into a UE-space FTransform @param Stage - Stage that contains the prim to convert @param Schema - Prim to convert @param OutTransform - Output transform to receieve the converted data @param EvalTime - Time at which to sample the prim's attributes @param bOutResetTransformStack - Output parameter that, when available, will be set to true if this prim uses the "!resetXformStack!" op @return Whether the conversion was successful or not.
- L110 _prototype_ `void PropagateTransform( const pxr::UsdStageRefPtr& Stage, const pxr::UsdPrim& Root, const pxr::UsdPrim& Leaf, double EvalTime, FTransform& OutTransform );` (scope `UsdToUnreal`) — Propagates the transform from Root to Leaf prims inclusively into a UE-space FTransform if they are connected by Xformables @param Stage - Stage that contains the prims to process @param Root - Prim to start the propagation from @param Leaf - Prim where to end the propagation @param EvalTime - Time at which to sample the prim's attributes @param OutTransform - The composed transform; identity if Leaf is not completely connected to Root by Xformables
- L118 _prototype_ `bool ConvertGeomCamera( const UE::FUsdPrim& Prim, UCineCameraComponent& CameraComponent, double UsdTimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UsdToUnreal`)
- L129 _prototype_ `bool ConvertBoolTimeSamples( const UE::FUsdStage& UsdStage, const TArray<double>& UsdTimeSamples, const TFunction<bool(double)>& ReaderFunc, UMovieSceneBoolTrack& MovieSceneTrack, const FMovieSceneSequenceTransform& SequenceTransform );` (scope `UsdToUnreal`) — Calls the ReaderFunc on each time sample of UsdTimeSamples in order to bake values into MovieSceneTrack. This is mostly used when reading attributes from USD into tracks for the automatically generated ULevelSequence provided with AUsdStageActors. The bounds version must use a BBoxCache: If one is not provided it will be created on-demand for this call alone.
- L136 _prototype_ `bool ConvertBoolTimeSamples( const UE::FUsdStage& UsdStage, const TArray<double>& UsdTimeSamples, const TFunction<bool(double)>& ReaderFunc, UMovieSceneVisibilityTrack& MovieSceneTrack, const FMovieSceneSequenceTransform& SequenceTransform );` (scope `UsdToUnreal`)
- L143 _prototype_ `bool ConvertFloatTimeSamples( const UE::FUsdStage& UsdStage, const TArray<double>& UsdTimeSamples, const TFunction<float(double)>& ReaderFunc, FMovieSceneFloatChannel& FloatChannel, const UMovieScene& MovieSceneOuter, const FMovieSceneSequenceTransform& SequenceTransform, TOptional<ERichCurveInterpMode> InterpolationModeOverride = {} );` (scope `UsdToUnreal`)
- L152 _prototype_ `bool ConvertFloatTimeSamples( const UE::FUsdStage& UsdStage, const TArray<double>& UsdTimeSamples, const TFunction<float(double)>& ReaderFunc, UMovieSceneFloatTrack& MovieSceneTrack, const FMovieSceneSequenceTransform& SequenceTransform, TOptional<ERichCurveInterpMode> InterpolationModeOverride = {} );` (scope `UsdToUnreal`)
- L160 _prototype_ `bool ConvertColorTimeSamples( const UE::FUsdStage& UsdStage, const TArray<double>& UsdTimeSamples, const TFunction<FLinearColor(double)>& ReaderFunc, UMovieSceneColorTrack& MovieSceneTrack, const FMovieSceneSequenceTransform& SequenceTransform );` (scope `UsdToUnreal`)
- L167 _prototype_ `bool ConvertTransformTimeSamples( const UE::FUsdStage& UsdStage, const TArray<double>& UsdTimeSamples, const TFunction<FTransform(double)>& ReaderFunc, UMovieScene3DTransformTrack& MovieSceneTrack, const FMovieSceneSequenceTransform& SequenceTransform );` (scope `UsdToUnreal`)
- L174 _prototype_ `bool ConvertBoundsTimeSamples( const UE::FUsdPrim& InPrim, const TArray<double>& InUsdTimeSamples, const FMovieSceneSequenceTransform& InSequenceTransform, UMovieSceneDoubleVectorTrack& InOutMinTrack, UMovieSceneDoubleVectorTrack& InOutMaxTrack, UE::FUsdGeomBBoxCache* InOutBBoxCache = nullptr );` (scope `UsdToUnreal`)
- L204 _prototype_ `CreatePropertyTrackReader(const UE::FUsdPrim& Prim, const FName& PropertyPath, bool bIgnorePrimLocalTransform = false);` (scope `UsdToUnreal`)
- L211 _prototype_ `bool ConvertDrawMode( const pxr::UsdPrim& Prim, UUsdDrawModeComponent* DrawModeComponent, double EvalTime = UsdUtils::GetDefaultTimeCode(), pxr::UsdGeomBBoxCache* BBoxCache = nullptr );` (scope `UsdToUnreal`) — Convert a prim with UsdGeomModelAPI and an alternative drawMode (bounds, cards or origin) into property values of an UUsdDrawModeComponent at EvalTime. Must use a BBoxCache: If one is not provided it will be created on-demand for this call alone.
- L222 _prototype_ `bool ConvertMetadata( const pxr::UsdPrim& Prim, FUsdCombinedPrimMetadata& PrimMetadata, const TArray<FString>& BlockedPrefixFilters = {}, bool bInvertFilters = false, bool bCollectFromEntireSubtrees = false );` (scope `UsdToUnreal`) — Collects all metadata from Prim (and its subtree in case bCollectFromEntireSubtrees is true), using the provided filters, and places them into PrimMetadata
- L234 _prototype_ `bool ConvertMetadata( const pxr::UsdPrim& Prim, UUsdAssetUserData* AssetUserData, const TArray<FString>& BlockedPrefixFilters = {}, bool bInvertFilters = false, bool bCollectFromEntireSubtrees = false );` (scope `UsdToUnreal`) — Collects all metadata from Prim (and its subtree in case bCollectFromEntireSubtrees is true), using the provided filters, and places them into AssetUserData
- L243 _namespace_ `namespace UnrealToUsd`
- L245 _prototype_ `bool ConvertCameraComponent( const UCineCameraComponent& CameraComponent, pxr::UsdPrim& Prim, double UsdTimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UnrealToUsd`)
- L251 _prototype_ `bool ConvertAudioComponent( const UAudioComponent& AudioComponent, pxr::UsdPrim& Prim, bool bFilePathOnly, double UsdTimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UnrealToUsd`)
- L258 _prototype_ `bool ConvertAudioSection( const UMovieSceneAudioSection& AudioSection, const FMovieSceneSequenceTransform& SequenceTransform, pxr::UsdPrim& Prim );` (scope `UnrealToUsd`)
- L269 _prototype_ `bool ConvertFloatChannel( const FMovieSceneFloatChannel& MovieSceneChannel, const UMovieScene& MovieSceneOuter, const FMovieSceneSequenceTransform& SequenceTransform, const TFunction<void(float, double)>& WriterFunc, UE::FUsdPrim& Prim );` (scope `UnrealToUsd`) — Functions that call WriterFunc on each UsdTimeSample that corresponds to the keyframes of MovieSceneTrack, writing out time samples for attributes of Prim. Mostly used to write out to USD the modified tracks from the automatically generated ULevelSequence owned by AUsdStageActors
- L276 _prototype_ `bool ConvertFloatTrack( const UMovieSceneFloatTrack& MovieSceneTrack, const FMovieSceneSequenceTransform& SequenceTransform, const TFunction<void(float, double)>& WriterFunc, UE::FUsdPrim& Prim );` (scope `UnrealToUsd`)
- L282 _prototype_ `bool ConvertBoolTrack( const UMovieScenePropertyTrack& MovieSceneTrack,` (scope `UnrealToUsd`)
- L288 _prototype_ `bool ConvertColorTrack( const UMovieSceneColorTrack& MovieSceneTrack, const FMovieSceneSequenceTransform& SequenceTransform, const TFunction<void(const FLinearColor&, double)>& WriterFunc, UE::FUsdPrim& Prim );` (scope `UnrealToUsd`)
- L294 _prototype_ `bool ConvertBoundsVectorTracks( const UMovieSceneDoubleVectorTrack* MinTrack, const UMovieSceneDoubleVectorTrack* MaxTrack, const FMovieSceneSequenceTransform& SequenceTransform, const TFunction<void(const FVector&, const FVector&, double)>& WriterFunc, UE::FUsdPrim& Prim );` (scope `UnrealToUsd`)
- L301 _prototype_ `bool Convert3DTransformTrack( const UMovieScene3DTransformTrack& MovieSceneTrack, const FMovieSceneSequenceTransform& SequenceTransform, const TFunction<void(const FTransform&, double)>& WriterFunc, UE::FUsdPrim& Prim );` (scope `UnrealToUsd`)
- L308 _prototype_ `bool ConvertSceneComponent(const pxr::UsdStageRefPtr& Stage, const USceneComponent* SceneComponent, pxr::UsdPrim& UsdPrim);` (scope `UnrealToUsd`)
- L310 _prototype_ `bool ConvertMeshComponent(const pxr::UsdStageRefPtr& Stage, const UMeshComponent* MeshComponent, pxr::UsdPrim& UsdPrim);` (scope `UnrealToUsd`)
- L312 _prototype_ `bool ConvertHierarchicalInstancedStaticMeshComponent( const UHierarchicalInstancedStaticMeshComponent* HISMComponent, pxr::UsdPrim& UsdPrim, double TimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UnrealToUsd`)
- L318 _prototype_ `bool ConvertInstancedStaticMeshComponent( const UInstancedStaticMeshComponent* ISMComponent, pxr::UsdPrim& UsdPrim, double TimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UnrealToUsd`)
- L334 _prototype_ `bool ConvertMaterialOverrides( const UObject* MeshAsset, const TArray<UMaterialInterface*> MaterialOverrides, pxr::UsdPrim& UsdPrim, int32 LowestLOD = INDEX_NONE, int32 HighestLOD = INDEX_NONE, bool bCheckAssetUserData = true );` (scope `UnrealToUsd`) — Sets the material overrides as opinions on MeshPrim, taking care to figure out whether it needs to create LOD or subsection prims, and which ones given the chosen export LOD range. Leaving the LOD range at default of INDEX_NONE will author the material override opinions assuming all LODs of the MeshAsset were exported. MeshAsset should be an UStaticMesh, USkeletalMesh or UGeometryCache. If bCheckAssetUserData is enabled, this function will check the asset's USD Asset User Data in order to determine the mapping between material slot and prim path, which is useful when exporting multiple slots to geom subsets or LOD prims. If this is false, The overrides will be authored to standard paths used by the USDImporter plugin (i.e. LOD<N> prims when needed, UsdGeomSubsets named "Section<N>")
- L350 _prototype_ `bool ConvertXformable( const UMovieScene3DTransformTrack& MovieSceneTrack, pxr::UsdPrim& UsdPrim, const FMovieSceneSequenceTransform& SequenceTransform );` (scope `UnrealToUsd`) — Converts a UMovieScene3DTransformTrack to a UsdGeomXformable @param MovieSceneTrack      The track to read the time sampled transform from @param Prim                 The Xformable to write to @param SequenceTransform    The time transform to apply to the track keys to get them from Usd Stage time to track time (in other words: from main sequence to subsequence)
- L355 _prototype_ `bool ConvertXformable(const FTransform& RelativeTransform, pxr::UsdPrim& UsdPrim, double TimeCode);` (scope `UnrealToUsd`)
- L366 _prototype_ `bool ConvertInstancedFoliageActor( const AInstancedFoliageActor& Actor, pxr::UsdPrim& UsdPrim, double TimeCode, ULevel* InstancesLevel = nullptr );` (scope `UnrealToUsd`) — Converts a AInstancedFoliageActor to a prim containing a pxr::UsdGeomPointInstancer schema. Each foliage type should correspond to a prototype. This function only converts the protoIndices, positions, orientations and scales attributes. @param Actor				   The actor to convert data from @param Prim                 The pxr::UsdGeomPointInstancer to write to @param TimeCode			   TimeCode to write the attribute values at. Use UsdUtils::GetDefaultTimeCode() for the Default value. @param InstancesLevel	   If this is not nullptr, only foliage instances placed on components that belong to this level will be exported
- L388 _prototype_ `ENUM_CLASS_FLAGS(EBakingType);` (scope `UnrealToUsd`)
- L389 _variable_ `const static inline int32 NumBakingTypes = 6;` (scope `UnrealToUsd`)
- L409 _prototype_ `bool CreateComponentPropertyBaker( UE::FUsdPrim& Prim, const USceneComponent& Component, const FString& PropertyPath, FComponentBaker& OutBaker );` (scope `UnrealToUsd`) — Creates a property baker responsible for baking Component's current state onto Prim according to its component type, if PropertyPath describes a property that we map from UE to USD for that component type. Returns whether a baker was created or not. e.g. if we provide a UCineCameraComponent and PropertyPath == "FocusSettings.ManualFocusDistance" it will create a EBakingType::Camera baker (that bakes all of the mappable UE cine camera properties at once) and return true. If we provide PropertyPath == "FocusSettings.FocusSmoothingInterpSpeed" it will return false as that is not mapped to USD.
- L420 _prototype_ `bool CreateSkeletalAnimationBaker( UE::FUsdPrim& SkeletonPrim, UE::FUsdPrim& SkelAnimation, USkeletalMeshComponent& Component, FComponentBaker& OutBaker );` (scope `UnrealToUsd`) — Creates a property baker responsible for baking the joint/blend shape state of Component as a SkelAnimation, returning true if a EBakingType::Skeletal baker was created
- L450 _prototype_ `FPropertyTrackWriter CreatePropertyTrackWriter( const USceneComponent& Component, const UMovieScenePropertyTrack& Track, UE::FUsdPrim& Prim, TSet<FName>& OutPropertyPathsToRefresh );` (scope `UnrealToUsd`) — Creates an FPropertyTrackWriter that can be used to receive, convert and output to USD the values of UE properties contained in Track, baking frame-by-frame when needed. e.g. calling this with a RectLight prim and UnrealIdentifiers::SourceWidthPropertyName will return a writer with a FloatWriter member that writes not only to the width, but also the intensity attributes of Prim at each UsdTimeCode. Also outputs OutPropertyPathsToRefresh: In the case above containing "Intensity", which lets us know to refresh and re-read from USD the Intensity track, if we have one
- L462 _prototype_ `bool ConvertDrawModeComponent( const UUsdDrawModeComponent& DrawModeComponent, pxr::UsdPrim& UsdPrim, bool bWriteExtents = false, double UsdTimeCode = UsdUtils::GetDefaultTimeCode() );` (scope `UnrealToUsd`) — Converts the properties values from UUsdDrawModeComponent into attribute values of a prim with UsdGeomModelAPI. Note that this will even apply the schema itself to UsdPrim if it doesn't already have it, and potentially author the 'kind' metadata on it and all of its ancestors (as UsdGeomModelAPI requires the prim to be a "model" to have function)
- L477 _prototype_ `bool ConvertMetadata( const FUsdCombinedPrimMetadata& CombinedPrimMetadata, const pxr::UsdPrim& Prim, const TArray<FString>& BlockedPrefixFilters = {}, bool bInvertFilter = false );` (scope `UnrealToUsd`) — Writes out all metadata from CombinedPrimMetadata onto Prim, as actual USD metadata fields. Only fields that pass the filters will be allowed. If CombinedPrimMetadata contains metadata from multiple prim paths, this overload has some heuristics in order to try and get all of the provided metadata written out to that single prim. This means some of these metadata entries may not end up on prim at the "top level", but may instead be placed within nested metadata maps that mirror the prim path hierarchy. If this behavior is not desired, feel free to use another overload of this function for more precise control.
- L488 _prototype_ `bool ConvertMetadata( const FUsdPrimMetadata& PrimMetadata, const pxr::UsdPrim& Prim, const TArray<FString>& BlockedPrefixFilters = {}, bool bInvertFilter = false );` (scope `UnrealToUsd`) — Writes out all metadata from PrimMetadata onto Prim, as actual USD metadata fields. Only fields that pass the filters will be allowed.
- L501 _prototype_ `bool ConvertMetadata( const UUsdAssetUserData* AssetUserData, const pxr::UsdPrim& Prim, const TArray<FString>& BlockedPrefixFilters = {}, bool bInvertFilter = false );` (scope `UnrealToUsd`) — Writes out all of the collected metadata from AssetUserData onto Prim, as actual USD metadata fields. Only fields that pass the filters will be allowed. This overload will essentially just loop over all entries of AssetUserData's StageIdentifierToMetadata property and write them all out using the overload of ConvertMetadata that receives FUsdCombinedPrimMetadata.
- L509 _namespace_ `namespace UsdUtils`
- L516 _prototype_ `TArray<UE::FUsdAttribute> GetAttributesForProperty(const UE::FUsdPrim& Prim, const FName& PropertyPath);` (scope `UsdUtils`) — Returns the attributes that in USD correspond to a property in UE. The first one is the "main" attribute, when appropriate. e.g. for a RectLight prim and UnrealIdentifiers::IntensityPropertyName, we'll receive intensity, exposure, width and height, in that order.
- L524 _prototype_ `TArray<FName> GetPropertiesForAttribute(const UE::FUsdPrim& Prim, const FString& AttrName);` (scope `UsdUtils`) — Returns the names of UE properties that need to be written to, when reading an USD attribute. Example: If AttrName is "inputs:radius" and Prim is a SphereLight, this will return [UnrealIdentifiers::SourceRadiusPropertyName]; If AttrName is "inputs:radius" and Prim is a DiskLight, this will return [UnrealIdentifiers::SourceWidthPropertyName, UnrealIdentifiers::SourceHeightPropertyName].
- L532 _prototype_ `void DensifyTimeSamplesIfNeeded( const UE::FUsdPrim& Prim, const FName& PropertyPath, TArray<double>& InOutTimeSamples );` (scope `UsdUtils`) — Checks if the given property requires frame-by-frame baking due to non-linear attribute interactions (e.g. light intensity = inputs:intensity * 2^inputs:exposure). If so, densifies InOutTimeSamples to include every integer time code between the first and last existing sample, ensuring the non-linear combination is properly captured as linear keyframes.

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDShadeConversion.h` (Public)


#### struct `UsdToUnreal::FTextureParameterValue`  
`struct FTextureParameterValue`  
_L50-73_
- L52 _public member_ `UTexture* Texture = nullptr;` — Only used for the ConvertMaterial overloads that receive TexturesCache
- L55 _public member_ `FString TextureFilePath;` — Parameters of the texture asset itself
- L56 _public member_ `TextureGroup Group = TEXTUREGROUP_World;`
- L57 _public member_ `TOptional<bool> bSRGB;`
- L58 _public member_ `bool bIsUDIM = false;`
- L59 _public member_ `TextureAddress AddressX = TA_Wrap;`
- L60 _public member_ `TextureAddress AddressY = TA_Wrap;`
- L63 _public member_ `FString Primvar;` — Parameters about the texture usage
- L64 _public member_ `int32 OutputIndex = 0;`
- L65 _public member_ `FVector2f UVTranslation;`
- L66 _public member_ `float UVRotation = 0.0f;`
- L67 _public member_ `FScale2f UVScale;`
- L72 _public prototype_ `bool GetSRGBValue() const;` — Returns whether the texture should be parsed as sRGB or not, given the actually authored "bSRGB" member and the fallback opinion provided by the texture group

#### struct `UsdToUnreal::FPrimvarReaderParameterValue`  
`struct FPrimvarReaderParameterValue`  
_L75-79_
- L77 _public member_ `FString PrimvarName;`
- L78 _public member_ `FVector FallbackValue;`

#### struct `UsdToUnreal::FUsdPreviewSurfaceMaterialData`  
`struct FUsdPreviewSurfaceMaterialData`  
_L83-99_
- L85 _public member_ `TMap<FString, FParameterValue> Parameters;`
- L98 _public member_ `TMap<FString, int32> PrimvarToUVIndex;` — Describes which UV set this material will target with each primvar e.g. {'firstPrimvar': 0, 'st': 1, 'st1': 2}. We store this here because deciding this assignment involves combining and sorting all the existing primvars that the texture parameters want to read, which we do when first calling ConvertMaterial(). This will later be compared with the primvar to UV index mapping we generate when parsing mesh data. If they are compatible, we'll be able to use the material directly on that mesh. Otherwise we'll need to generate a new instance of this material that assigns different primvars to each UV index (check CreatePrimvarCompatibleVersionOfMaterial).

#### Free symbols / members of external scopes

- L43 _namespace_ `namespace UE`
- L48 _namespace_ `namespace UsdToUnreal`
- L81 _typedef_ `using FParameterValue = TVariant<float, FVector, FTextureParameterValue, FPrimvarReaderParameterValue, bool, int32>;` (scope `UsdToUnreal`)
- L113 _prototype_ `bool ConvertMaterial( const pxr::UsdPrim& InUsdShadeMaterialPrim, FUsdPreviewSurfaceMaterialData& OutMaterial, const TCHAR* InRenderContext = nullptr );` (scope `UsdToUnreal`) — Extracts material data from UsdShadeMaterial and places the results in Material. Note that since this is used for UMaterialInstanceDynamics at runtime as well, it will not set base property overrides (e.g. BlendMode) or the parent material, and will just assume that the caller handles that. Note that in order to receive the primvar to UV index mapping calculated within this function, the provided Material should have an UUsdMaterialAssetImportData object as its AssetImportData. @param UsdShadeMaterial - Shade material with the data to convert @param OutMaterial - Output parameter that will be filled with the converted data @param TexturesCache - Cache to prevent importing a texture more than once @param RenderContext - Which render context output to read from the UsdShadeMaterial @param bShareAssetsForIdenticalPrims - Whether to reuse identical textures found in the TextureCache or to create dedicated textures for each material @return Whether the conversion was successful or not.
- L118 _prototype_ `bool ConvertMaterial( const pxr::UsdShadeMaterial& UsdShadeMaterial, UMaterialInstance& OutMaterial, UUsdAssetCache3* TexturesCache = nullptr, const TCHAR* RenderContext = nullptr, bool bShareAssetsForIdenticalPrims = true );` (scope `UsdToUnreal`)
- L125 _prototype_ `bool ConvertMaterial( const pxr::UsdShadeMaterial& UsdShadeMaterial, UMaterial& OutMaterial, UUsdAssetCache3* TexturesCache = nullptr, const TCHAR* RenderContext = nullptr, bool bShareAssetsForIdenticalPrims = true );` (scope `UsdToUnreal`)
- L144 _prototype_ `bool ConvertShadeInputsToParameters( const pxr::UsdShadeMaterial& UsdShadeMaterial, UMaterialInstance& MaterialInstance, UUsdAssetCache3* TexturesCache, const TCHAR* RenderContext = nullptr, bool bShareAssetsForIdenticalPrims = true );` (scope `UsdToUnreal`) — Attemps to assign the values of the surface shader inputs to the MaterialInstance parameters by matching the inputs display names to the parameters names. @param UsdShadeMaterial - Shade material with the data to convert @param MaterialInstance - Material instance on which we will set the parameter values @param TexturesCache - Cache to prevent importing a texture more than once @param RenderContext - The USD render context to use when fetching the surface shader @param ReuseIdenticalAssets - Whether to reuse identical textures found in the TextureCache or to create dedicated textures for each material @return Whether the conversion was successful or not.
- L154 _namespace_ `namespace UnrealToUsd`
- L167 _prototype_ `bool ConvertMaterialToBakedSurface( const UMaterialInterface& InMaterial, const TArray<FPropertyEntry>& InMaterialProperties, const FIntPoint& InDefaultTextureSize, const FDirectoryPath& InTexturesDir, pxr::UsdPrim& OutUsdShadeMaterialPrim, bool bInDecayTexturesToSinglePixel = true );` (scope `UnrealToUsd`) — Bakes InMaterial into textures and constants, and configures OutUsdShadeMaterial to use the baked data. @param InMaterial - Source material to bake @param InMaterialProperties - Material properties to bake from InMaterial @param InDefaultTextureSize - Size of the baked texture to use for any material property that does not have a custom size set @param InTexturesDir - Directory where the baked textures will be placed @param OutUsdShadeMaterialPrim - UsdPrim with the UsdShadeMaterial schema that will be configured to use the baked textures and constants @param bInDecayTexturesToSinglePixel - Whether to use a single value directly on the material instead of writing out textures with that have a single uniform color value for all pixels @return Whether the conversion was successful or not.
- L188 _prototype_ `bool ConvertFlattenMaterial( const FString& InMaterialName, FFlattenMaterial& InMaterial, const TArray<FPropertyEntry>& InMaterialProperties, const FDirectoryPath& InTexturesDir, UE::FUsdPrim& OutUsdShadeMaterialPrim );` (scope `UnrealToUsd`) — Converts a flattened material's data into textures placed at InTexturesDir, and configures OutUsdShadeMaterial to use the baked textures. Note that to avoid a potentially useless copy, InMaterial's samples will be modified in place to have 255 alpha before being exported to textures. @param MaterialName - Name of the material, used as prefix on the exported texture filenames @param InMaterial - Source material to bake @param InMaterialProperties - Object used *exclusively* to provide floating point constant values if necessary @param InTexturesDir - Directory where the baked textures will be placed @param OutUsdShadeMaterialPrim - UsdPrim with the UsdShadeMaterial schema that will be configured to use the baked textures and constants @return Whether the conversion was successful or not.
- L198 _namespace_ `namespace UsdUtils`
- L205 _prototype_ `void AuthorUnrealMaterialBinding( pxr::UsdPrim& MeshOrGeomSubsetPrim, const FString& UnrealMaterialPathName, bool bStrongerThanDescendants = false );` (scope `UsdUtils`) — Writes UnrealMaterialPathName as a material binding for MeshOrGeomSubsetPrim, either by reusing an existing UsdShadeMaterial binding if it already has an 'unreal' render context output and the expected structure, or by creating a new Material prim that fulfills those requirements and binding to it (optionally with strongerThanDescendants strength in that case). Doesn't write to the 'unrealMaterial' attribute at all, as we intend on deprecating it in the future.
- L222 _prototype_ `void AuthorUnrealCollectionBasedMaterialBinding( const pxr::UsdPrim& CollectionPrim, const pxr::UsdPrim& TargetMeshOrGeomSubsetPrim, const FString& UnrealMaterialPathName );` (scope `UsdUtils`) — Similar to AuthorUnrealMaterialBinding, but instead of authoring material bindings directly to TargetMeshOrGeomSubsetPrim, it will instead author collection-based material bindings on the CollectionPrim, that instead target TargetMeshOrGeomSubsetPrim. It will try reusing existing collections and UnrealMaterials, but otherwise it will author a new collection within CollectionPrim, and a new UnrealMaterial as a sibling of CollectionPrim, referring to UnrealMaterialPathName. This is useful if CollectionPrim is an instance root, and TargetMeshOrGeomSubsetPrim is an instance proxy, for example. WARNING: In order to get collection-based bindings to work, TargetMeshOrGeomSubsetPrim must be a descendant of CollectionPrim.
- L230 _prototype_ `TOptional<FString> GetUnrealSurfaceOutput(const pxr::UsdPrim& MaterialPrim);` (scope `UsdUtils`) — Returns a path to an UE asset (e.g. "/Game/Assets/Red.Red") if MaterialPrim has an 'unreal' render context surface output that points at one
- L240 _prototype_ `bool SetUnrealSurfaceOutput(pxr::UsdPrim& MaterialPrim, const FString& UnrealMaterialPathName);` (scope `UsdUtils`) — Sets which UE material asset the 'unreal' render context surface output of MaterialPrim is pointing at (creating the surface output on-demand if needed) @param MaterialPrim - pxr::UsdPrim with the pxr::UsdShadeMaterial schema to update the 'unreal' surface output of @param UnrealMaterialPathName - Path to an UE UMaterialInterface asset (e.g. "/Game/Assets/Red.Red") @return Whether we successfully set the surface output or not
- L243 _prototype_ `bool HasSurfaceOutput(const pxr::UsdPrim& MaterialPrim, const FName& RenderContext);` (scope `UsdUtils`) — Returns whether MaterialPrim is an actual Material, and has a surface output authored for the provided render context
- L244 _prototype_ `bool HasSurfaceOutput(const pxr::UsdPrim& MaterialPrim, const TArray<FString>& RenderContexts);` (scope `UsdUtils`)
- L247 _prototype_ `bool HasDisplacementOutput(const pxr::UsdPrim& MaterialPrim, const FName& RenderContext);` (scope `UsdUtils`) — Returns whether MaterialPrim is an actual Material, and has a displacement output authored for the provided render context
- L248 _prototype_ `bool HasDisplacementOutput(const pxr::UsdPrim& MaterialPrim, const TArray<FString>& RenderContexts);` (scope `UsdUtils`)
- L251 _prototype_ `bool HasVolumeOutput(const pxr::UsdPrim& MaterialPrim, const FName& RenderContext);` (scope `UsdUtils`) — Returns whether MaterialPrim is an actual Material, and has a volume output authored for the provided render context
- L252 _prototype_ `bool HasVolumeOutput(const pxr::UsdPrim& MaterialPrim, const TArray<FString>& RenderContexts);` (scope `UsdUtils`)
- L258 _prototype_ `bool IsMaterialTranslucent(const pxr::UsdShadeMaterial& UsdShadeMaterial);` (scope `UsdUtils`) — Returns whether the material needs to be rendered with the Translucent rendering mode. This function exists because we need this information *before* we pick the right parent for a material instance and properly convert it.
- L259 _prototype_ `bool IsMaterialTranslucent(const UsdToUnreal::FUsdPreviewSurfaceMaterialData& ConvertedMaterial);` (scope `UsdUtils`)
- L261 _prototype_ `FSHAHash HashShadeMaterial(` (scope `UsdUtils`)
- L265 _prototype_ `void HashShadeMaterial(` (scope `UsdUtils`)
- L272 _prototype_ `FString GetResolvedAssetPath(const pxr::UsdAttribute& AssetPathAttr, pxr::UsdTimeCode TimeCode = pxr::UsdTimeCode::Default());` (scope `UsdUtils`) — Returns the resolved path from an pxr::SdfAssetPath attribute. For UDIMs path, returns the path to the 1001 tile.
- L279 _prototype_ `FString GetTextureHash( const FString& ResolvedTexturePath, bool bSRGB, TextureCompressionSettings CompressionSettings, TextureAddress AddressX, TextureAddress AddressY );` (scope `UsdUtils`) — Computes and returns the hash string for the texture at the given path. Handles regular texture asset paths as well as asset paths identifying textures inside Usdz archives. Returns an empty string if the texture could not be hashed.
- L287 _prototype_ `UTexture* CreateTexture( const FString& ResolvedTexturePath, FName SanitizedName, TextureGroup Group = TEXTUREGROUP_World, EObjectFlags Flags = RF_Public | RF_Standalone | RF_Transactional, UObject* Outer = GetTransientPackage(), bool bForceLinear = false, bool bIsUDIMPath = false );` (scope `UsdUtils`)
- L298 _prototype_ `void NotifyIfVirtualTexturesNeeded(UTexture* Texture);` (scope `UsdUtils`) — Checks if this texture needs virtual textures and emits a warning if it is disabled for the project
- L302 _prototype_ `EFlattenMaterialProperties MaterialPropertyToFlattenProperty(EMaterialProperty MaterialProperty);` (scope `UsdUtils`) — Convert between the two different types used to represent material channels to bake
- L305 _prototype_ `EMaterialProperty FlattenPropertyToMaterialProperty(EFlattenMaterialProperties FlattenProperty);` (scope `UsdUtils`) — Convert between the two different types used to represent material channels to bake
- L309 _prototype_ `void CollapseConstantChannelsToSinglePixel(FFlattenMaterial& InMaterial);` (scope `UsdUtils`) — Converts channels that have the same value for every pixel into a channel that only has a single pixel with that value
- L312 _prototype_ `bool MarkMaterialPrimWithWorldSpaceNormals(const UE::FUsdPrim& MaterialPrim);` (scope `UsdUtils`) — Temporary function until UnrealWrappers can create attributes, just adds a custom bool attribute 'worldSpaceNormals' as true
- L315 _prototype_ `void SetScalarParameterValue(UMaterialInstance& Material, const TCHAR* ParameterName, float ParameterValue);` (scope `UsdUtils`) — Sets material instance parameters whether Material is a MaterialInstanceConstant or a MaterialInstanceDynamic
- L316 _prototype_ `void SetVectorParameterValue(UMaterialInstance& Material, const TCHAR* ParameterName, FLinearColor ParameterValue);` (scope `UsdUtils`)
- L317 _prototype_ `void SetTextureParameterValue(UMaterialInstance& Material, const TCHAR* ParameterName, UTexture* ParameterValue);` (scope `UsdUtils`)
- L318 _prototype_ `void SetBoolParameterValue(UMaterialInstance& Material, const TCHAR* ParameterName, bool bParameterValue);` (scope `UsdUtils`)
- L322 _prototype_ `TArray<FString> GetMaterialXFilePaths(const pxr::UsdPrim& Prim);` (scope `UsdUtils`) — Retrieve MaterialX file from a prim

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDSkeletalDataConversion.h` (Public)


#### struct `UsdUtils::FUsdBlendShapeInbetween`  
`struct FUsdBlendShapeInbetween`  
_L66-79_
- L69 _public member_ `FString Name;` — Name of the FUsdBlendShape/UMorphTarget that holds the morph data for this inbetween
- L71 _public member_ `float InbetweenWeight;`

#### struct `UsdUtils::FUsdBlendShape`  
`struct FUsdBlendShape`  
_L81-104_
- L83 _public member_ `FString Name;`
- L88 _public member_ `TSet<int32> LODIndicesThatUseThis;` — Because Meshes need to target BlendShapes with USD relationships, and because relationships can't target things inside USD variants, we get that we can never have different data for different LODs within the same blend shape, like UMorphTarget does. At most, we can be *used* by different USD LOD meshes, which this member tracks.
- L89 _public member_ `TArray<FMorphTargetDelta> Vertices;`
- L90 _public member_ `TArray<FUsdBlendShapeInbetween> Inbetweens;`
- L91 _public member_ `bool bHasAuthoredTangents = false;`
- L93 _public function_ `bool IsValid() const`

#### struct `UsdToUnreal::FUsdSkeletonData`  
`struct FUsdSkeletonData`  
_L207-221_
- L220 _public member_ `TArray<FBone> Bones;`

#### struct `UsdToUnreal::FUsdSkeletonData::FBone`  
`struct FBone`  
_L209-218_
- L211 _public member_ `FString Name;`
- L213 _public member_ `FTransform LocalRestTransform = FTransform::Identity;`
- L214 _public member_ `FTransform LocalBindTransform = FTransform::Identity;`
- L216 _public member_ `TArray<int32> ChildIndices;`
- L217 _public member_ `int32 ParentIndex = INDEX_NONE;` — Root bones remain with INDEX_NONE

#### Free symbols / members of external scopes

- L45 _namespace_ `namespace SkeletalMeshImportData`
- L51 _namespace_ `namespace UsdUtils`
- L57 _namespace_ `namespace UE`
- L64 _namespace_ `namespace UsdUtils`
- L73 _function_ `friend FArchive& operator<<(FArchive& Ar, FUsdBlendShapeInbetween& BlendShape)` (scope `UsdUtils`)
- L98 _function_ `friend FArchive& operator<<(FArchive& Ar, FUsdBlendShape& BlendShape)` (scope `UsdUtils`)
- L111 _typedef_ `using FBlendShapeMap = TMap<FString, FUsdBlendShape, FDefaultSetAllocator, FCaseSensitiveStringMapFuncs<FUsdBlendShape>>;` (scope `UsdUtils`) — Maps from a full blend shape path (e.g. '/Scene/Mesh/BlendShapeName') to the parsed FUsdBlendShape struct. We need this to be case sensitive because USD paths are, and even the sample HumanFemale Skel scene has paths that differ only by case (e.g. 'JawUD' and 'JAWUD' blend shapes)
- L121 _prototype_ `void ResolveWeightsForBlendShape( const FUsdBlendShape& InBlendShape, float InWeight, float& OutPrimaryWeight, TArray<float>& OutInbetweenWeights );` (scope `UsdUtils`) — We decompose inbetween blend shapes on import into separate morph targets, alongside the primary blend shape, which also becomes a morph target. This function returns the morph target weights for the primary morph target, as well as all the morph targets for inbetween shapes of 'InBlendShape', given an initial input weight value for the USD blend shape. Calculations are done following the equations at https://graphics.pixar.com/usd/docs/api/_usd_skel__schemas.html#UsdSkel_BlendShape_Inbetweens Note: This assumes that the morph targets in InBlendShape are sorted by weight.
- L128 _prototype_ `void GetBoneTransforms(USkeletalMeshComponent* Component, TArray<FTransform>& BoneTransforms);` (scope `UsdUtils`)
- L129 _prototype_ `void RefreshSkeletalMeshComponent(USkeletalMeshComponent& Component);` (scope `UsdUtils`)
- L133 _prototype_ `UE::FUsdSkelSkinningQuery CreateSkinningQuery( const pxr::UsdPrim& SkinnedMeshPrim, const pxr::UsdSkelSkeletonQuery& SkeletonQuery );` (scope `UsdUtils`) — Allows creation of a skinning query from the underlying skinned mesh and skeleton. Adapted from the USD SDK implementation
- L142 _prototype_ `void BindAnimationSource(pxr::UsdPrim& Prim, const pxr::UsdPrim& AnimationSource);` (scope `UsdUtils`) — Sets prim AnimationSource as the animation source for prim Prim. Applies the SkelBindingAPI to Prim. See pxr::SkelBindingAPI::GetAnimationSourceRel.
- L147 _prototype_ `UE::FUsdPrim FindFirstAnimationSource(const UE::FUsdPrim& InSkelRootPrim);` (scope `UsdUtils`) — Returns the SkelAnimation prim that is resolved for the first skeletal binding of SkelRootPrim, if it is a SkelRoot.
- L152 _prototype_ `UE::FUsdPrim FindAnimationSource(const pxr::UsdPrim& InSkelRootPrim, const pxr::UsdPrim& InSkeletonPrim);` (scope `UsdUtils`) — Returns the SkelAnimation prim that is bound as animation source for the provided skeleton
- L158 _prototype_ `UE::FUsdPrim GetClosestParentSkelRoot(const pxr::UsdPrim& SomePrim);` (scope `UsdUtils`) — Convenience function that traverses through ancestors up from SomePrim and returns the first SkelRoot prim that it finds, returning an invalid prim in case it doesn't find anything
- L166 _prototype_ `bool GetSkelQueries( const pxr::UsdSkelRoot& InSkelRootPrim, const pxr::UsdSkelSkeleton& InSkeletonPrim, pxr::UsdSkelBinding& OutSkelBinding, pxr::UsdSkelSkeletonQuery& OutSkeletonQuery, pxr::UsdSkelCache* InOutSkelCache = nullptr );` (scope `UsdUtils`) — Convenience function to use/populate a SkelCache on a SkelRoot and retrieve the SkelBinding/SkeletonQuery for a particular InSkeletonPrim. You can retrieve the AnimQuery from the SkeletonQuery as well. A temp SkelCache will be constructed if none is provided. Returns true whether we managed to retrieve everything.
- L187 _prototype_ `bool ApplyBlendShape( FMeshDescription& InOutMeshDescription, const pxr::UsdPrim& InBlendShapePrim, const FTransform& AdditionalTransform, float Weight = 1.0f, const FString InInbetweenName = {} );` (scope `UsdUtils`) — Converts and applies the blend shape deltas from InBlendShapePrim onto the mesh described by InOutMeshDescription. Note that we expect InOutMeshDescription and InBlendShapePrim to at least have a matching number of vertices/points. @param InOutMeshDescription - The mesh data to deform with the blend shape @param InBlendShapePrim - The UsdSkelBlendShape prim to deform the mesh with @param GeomBindTransform - USD-space transform applied to the point/normal deltas before any other transformation @param AdditionalTransform - Unreal-space transform applied to the normal deltas after all other transformations @param Weight - Scalar that multiplies the deltas before they're applied to the mesh deformation: 0.0f means no effect, 1.0f adds the deltas at full strength, etc. @param InInbetweenName - The name of the inbetween shape of InBlendShapePrim to apply instead, if any. If left empty (default) the main blend shape is applied instead. @return Whether the conversion was successful or not.
- L194 _prototype_ `bool ApplyBlendShape( FMeshDescription& InOutMeshDescription, const pxr::UsdPrim& InBlendShapePrim, const FMatrix& GeomBindTransform, const FTransform& AdditionalTransform, float Weight = 1.0f, const FString InInbetweenName = {} );` (scope `UsdUtils`)
- L205 _namespace_ `namespace UsdToUnreal`
- L233 _prototype_ `bool ConvertSkeleton( const pxr::UsdSkelSkeletonQuery& UsdSkeletonQuery, FUsdSkeletonData& ConvertedData, bool bEnsureAtLeastOneBone = true, bool bEnsureSingleRootBone = true );` (scope `UsdToUnreal`) — Extracts skeleton data from UsdSkeletonQuery and places the results in ConvertedData. @param UsdSkeletonQuery - SkeletonQuery with the data to convert @param ConvertedData - Output parameter that will be filled with the converted data @param bEnsureAtLeastOneBone - Whether to ensure the resulting ConvertedData contains at least one bone (adding one if needed) @param bEnsureSingleRootBone - Whether to ensure the resulting ConvertedData has a *single* root bone (adding a new one and reparenting the previous root bones to it, if needed) @return Whether the conversion was successful or not.
- L245 _prototype_ `bool ConvertSkeleton(const pxr::UsdSkelSkeletonQuery& UsdSkeletonQuery, FSkeletalMeshImportData& SkelMeshImportData);` (scope `UsdToUnreal`) — Extracts skeleton data from UsdSkeletonQuery and places the results in SkelMeshImportData. @param UsdSkeletonQuery - SkeletonQuery with the data to convert @param SkelMeshImportData - Output parameter that will be filled with the converted data @return Whether the conversion was successful or not.
- L263 _prototype_ `bool ConvertBlendShape( const pxr::UsdSkelBlendShape& UsdBlendShape, const FUsdStageInfo& StageInfo, uint32 PointIndexOffset, TSet<FString>& UsedMorphTargetNames, UsdUtils::FBlendShapeMap& OutBlendShapes, const FUsdMeshConversionOptions& Options = FUsdMeshConversionOptions::DefaultOptions );` (scope `UsdToUnreal`) — Converts an USD blend shape into zero, one or more FUsdBlendShapes, and places them in OutBlendShapes @param UsdBlendShape - Source USD object with the blend shape data @param StageInfo - Details about the stage, required to do the coordinate conversion from the USD blend shape to morph target data @param LODIndex - LODIndex of the SkeletalMesh that will use the imported FUsdBlendShape @param AdditionalTransform - Additional affine transform to apply to the blend shape deltas and tangents (Note: No longer used, even in the deprecated overload of this function) @param PointIndexOffset - Index into the corresponding SkelMeshImportData.Points where the points corresponding to the UsdBlendShape's prim start @param UsedMorphTargetNames - Names that the newly created FUsdBlendShapes cannot have (this function will also add the names of the newly created FUsdBlendShapes to it) @param OutBlendShapes - Where the newly created blend shapes will be added to @param Options - Generic mesh conversion options to use when converting the blend shape @param GeomBindTransform - USD-space transform to be applied to the point and normal offsets before any other coordinate space conversion @return Whether the conversion was successful or not.
- L271 _prototype_ `bool ConvertBlendShape( const pxr::UsdSkelBlendShape& UsdBlendShape, const FUsdStageInfo& StageInfo, int32 LODIndex, uint32 PointIndexOffset, TSet<FString>& UsedMorphTargetNames, UsdUtils::FBlendShapeMap& OutBlendShapes, const FUsdMeshConversionOptions& Options, const pxr::GfMatrix4d* GeomBindTransform = nullptr );` (scope `UsdToUnreal`)
- L298 _prototype_ `bool ConvertSkinnedMesh( const pxr::UsdSkelSkinningQuery& UsdSkinningQuery, const pxr::UsdSkelSkeletonQuery& SkeletonQuery, FSkeletalMeshImportData& SkelMeshImportData, UsdUtils::FUsdPrimMaterialAssignmentInfo& MaterialAssignments, const FUsdMeshConversionOptions& CommonOptions = FUsdMeshConversionOptions::DefaultOptions );` (scope `UsdToUnreal`) — Extracts skeletal mesh data fro UsdSkinningQuery, and places the results in SkelMeshImportData. If a PrimvarToUVIndex mapping is provided in MaterialAssignments, it will be used to remap the read primvars into UV sets. Otherwise, a new PrimvarToUVIndex map will be constructed on-demand and assigned to MaterialAssignments instead. @param UsdSkinningQuery - SkinningQuery with the data to convert @param SkeletonQuery - Query object for the skeleton this mesh is bound to @param AdditionalTransform - Additional transform to apply to the vertices of the mesh (Note: No longer used, even in the deprecated overload of this function) @param SkelMeshImportData - Output parameter that will be filled with the converted data @param MaterialAssignments - Output parameter that will be filled with the material assignment data extracted from UsdSkinningQuery @param CommonOptions - Generic mesh conversion options to use for the conversion @return Whether the conversion was successful or not.
- L326 _prototype_ `bool ConvertSkelAnim( const pxr::UsdSkelSkeletonQuery& InUsdSkeletonQuery, const pxr::VtArray<pxr::UsdSkelSkinningQuery>* InSkinningTargets, const UsdUtils::FBlendShapeMap* InBlendShapes, bool bInInterpretLODs, const pxr::UsdPrim& RootMotionPrim, UAnimSequence* OutSkeletalAnimationAsset, float* OutStartOffsetSeconds = nullptr, float* OutScaleSeconds = nullptr );` (scope `UsdToUnreal`) — Will extract animation data from the animation source of InUsdSkeletonQuery's skeleton, and populate OutSkeletalAnimationAsset with the data. Warning: UAnimSequence must be previously set with a USkeleton generated from the skeletal data of the same UsdSkelSkeletonQuery. @param InUsdSkeletonQuery - SkinningQuery with the data to convert @param InSkinningTargets - Skinned meshes that use the skeleton of InUsdSkeletonQuery. Required to fetch the blend shape ordering of each mesh. Optional (can be nullptr to ignore) @param InBlendShapes - Converted blend shape data that will be used to interpret blend shape weights as morph target weight float curves. Optional (can be nullptr to ignore) @param InInterpretLODs - Whether we try parsing animation data from all LODs of skinning meshes that are inside LOD variant sets @param RootMotionPrim - Optional prim whose transform animation will be concatenaded into the root bone's regular joint animation @param OutSkeletalAnimationAsset - Output parameter that will be filled with the converted data @param OutStartOffsetSeconds - Optional output parameter that will be filled with the offset in seconds of when this UAnimSequence asset should be played since the start of the stage to match the intended composed animation. The baked UAnimSequence will only contain the range between the first and last joint and/or blend shape timeSamples, and so the offset is needed to properly position the animation on the stage's timeline. This is in seconds bec
- L345 _prototype_ `bool ConvertSkeletalImportData( TArray<FSkeletalMeshImportData>& InLODIndexToSkeletalMeshImportData, const TArray<SkeletalMeshImportData::FBone>& InSkeletonBones, UsdUtils::FBlendShapeMap& InBlendShapesByPath, USkeletalMesh* InOutSkeletalMesh );` (scope `UsdToUnreal`) — Fills in InOutSkeletalMesh (and its Skeleton) with all the provided data converted from USD. @param InLODIndexToSkeletalMeshImportData - Container with the imported skeletal mesh data per LOD level @param InSkeletonBones - Bones to use for the reference skeleton (skeleton data on each LODIndexToSkeletalMeshImportData will be ignored). @param InBlendShapesByPath - Blend shapes to convert to morph targets @param InOutSkeletalMesh - SkeletalMesh to receive the converted data. It should have a valid USkeleton set. @return Whether the conversion was successful or not.
- L356 _namespace_ `namespace UnrealToUsd`
- L367 _prototype_ `bool ConvertSkeleton(const USkeleton* Skeleton, pxr::UsdSkelSkeleton& UsdSkeleton);` (scope `UnrealToUsd`) — Converts the bone data from Skeleton into UsdSkeleton. WARNING: Sometimes Skeleton->ReferenceSkeleton() has slightly different transforms than USkeletalMesh->GetRefSkeleton(), so make sure you're using the correct one for what you wish to do! @param Skeleton - Source UE data to convert @param UsdSkeleton - Previously created prim with the UsdSkelSkeleton schema that will be filled with converted data @return Whether the conversion was successful or not.
- L368 _prototype_ `bool ConvertSkeleton(const FReferenceSkeleton& ReferenceSkeleton, pxr::UsdSkelSkeleton& UsdSkeleton);` (scope `UnrealToUsd`)
- L371 _prototype_ `bool ConvertJointsAttribute(const FReferenceSkeleton& ReferenceSkeleton, pxr::UsdAttribute& JointsAttribute);` (scope `UnrealToUsd`) — Fill out a UsdSkelAnimation's Joints attribute with data from ReferenceSkeleton, taking care to concatenate bone paths
- L386 _prototype_ `bool ConvertSkeletalMesh( const USkeletalMesh* SkeletalMesh, pxr::UsdPrim& SkelRootPrim, const pxr::UsdTimeCode TimeCode = pxr::UsdTimeCode::Default(), UE::FUsdStage* StageForMaterialAssignments = nullptr, int32 LowestMeshLOD = 0, int32 HighestMeshLOD = INT32_MAX );` (scope `UnrealToUsd`) — Converts SkeletalMesh, its skeleton and morph target data into the corresponding USD objects and populates SkelRoot with them, at time TimeCode @param SkeletalMesh - Mesh with the source data. If it contains multiple LODs it will lead to the creation of LOD variant sets and variants within SkelRoot @param SkelRoot - Root prim of the output source data. Child UsdSkelSkeleton, UsdGeomMesh, and UsdSkelBlendShape will be created as children of it, containing the converted data @param TimeCode - TimeCode with which the converted data will be placed in the USD stage @param StageForMaterialAssignments - Stage to use when authoring material assignments (we use this when we want to export the mesh to a payload layer, but the material assignments to an asset layer) @param LowestMeshLOD - Lowest LOD of the UStaticMesh to export (start of the LOD range) @param HighestMeshLOD - Lowest LOD of the UStaticMesh to export (end of the LOD range) @return Whether the conversion was successful or not.
- L402 _prototype_ `bool ConvertAnimSequence(UAnimSequence* AnimSequence, pxr::UsdPrim& SkelAnimPrim);` (scope `UnrealToUsd`) — Converts an AnimSequence to a UsdSkelAnimation. Includes bone transforms and blend shape weights. Keys will be baked at the stage TimeCodesPerSecond resolution. @param AnimSequence - The AnimSequence to convert @param SkelAnimPrim - Expected to be of type UsdkSkelAnimation @return Whether the conversion was successful or not.
- L422 _prototype_ `bool ConvertControlRigSection( UMovieSceneControlRigParameterSection* InSection, const FMovieSceneInverseSequenceTransform& InTransform, UMovieScene* InMovieScene, IMovieScenePlayer* InPlayer, const FReferenceSkeleton& InRefSkeleton, pxr::UsdPrim& InSkelRoot, pxr::UsdPrim& OutSkelAnimPrim, const UsdUtils::FBlendShapeMap* InBlendShapeMap = nullptr );` (scope `UnrealToUsd`) — Plays the provided Section in the background, driving its ControlRig and baking to USD the animated bones and curves end result. @param InSection - The section to bake; @param InTransform - A time transform to apply to the baked data before writing out; @param InMovieScene - The MovieScene that contains InSection (we can't access via the Outer chain from this RTTI module); @param IMovieScenePlayer - The player to drive the InSection with (e.g. a Sequencer instance); @param InRefSkeleton - Skeleton that describes the target Skeleton prim bone structure to use (the control rig may have an arbitrary bone hierarchy, but we always want to write bones compatible with the target UsdSkelRoot and its child prims); @param InSkelRoot - The SkelRoot that we're writing to (in some cases we need to update Mesh prims, and only the meshes within this SkelRoot will be updated); @param OutSkelAnimPrim - The SkelAnimation prim to receive the baked data; @param InBlendShapeMap - Optional map describing the stage blend shapes, in case baking of the rig's animation curves is desired; @return Whether the conversion was successful or not.

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDTypesConversion.h` (Public)


#### struct `FUsdStageInfo`  
`struct FUsdStageInfo`  
_L50-56_
- L52 _public member_ `EUsdUpAxis UpAxis = EUsdUpAxis::ZAxis;`
- L53 _public member_ `double MetersPerUnit = 0.01;`
- L55 _public prototype_ `explicit FUsdStageInfo(const pxr::UsdStageRefPtr& Stage);`

#### Free symbols / members of external scopes

- L41 _typedef_ `using UsdStageRefPtr = TfRefPtr<UsdStage>;`
- L58 _namespace_ `namespace UsdToUnreal`
- L60 _prototype_ `FString ConvertString(const std::string& InString);` (scope `UsdToUnreal`)
- L61 _prototype_ `FString ConvertString(const char* InString);` (scope `UsdToUnreal`)
- L63 _prototype_ `FString ConvertPath(const pxr::SdfPath& Path);` (scope `UsdToUnreal`)
- L65 _prototype_ `FName ConvertName(const char* InString);` (scope `UsdToUnreal`)
- L66 _prototype_ `FName ConvertName(const std::string& InString);` (scope `UsdToUnreal`)
- L68 _prototype_ `FString ConvertToken(const pxr::TfToken& Token);` (scope `UsdToUnreal`)
- L71 _prototype_ `FLinearColor ConvertColor(const pxr::GfVec3f& InValue);` (scope `UsdToUnreal`) — Assumes the input color is in linear space
- L72 _prototype_ `FLinearColor ConvertColor(const pxr::GfVec4f& InValue);` (scope `UsdToUnreal`)
- L74 _prototype_ `FVector2D ConvertVector(const pxr::GfVec2h& InValue);` (scope `UsdToUnreal`)
- L75 _prototype_ `FVector2D ConvertVector(const pxr::GfVec2f& InValue);` (scope `UsdToUnreal`)
- L76 _prototype_ `FVector2D ConvertVector(const pxr::GfVec2d& InValue);` (scope `UsdToUnreal`)
- L77 _prototype_ `FIntPoint ConvertVector(const pxr::GfVec2i& InValue);` (scope `UsdToUnreal`)
- L79 _prototype_ `FVector ConvertVector(const pxr::GfVec3h& InValue);` (scope `UsdToUnreal`)
- L80 _prototype_ `FVector ConvertVector(const pxr::GfVec3f& InValue);` (scope `UsdToUnreal`)
- L81 _prototype_ `FVector ConvertVector(const pxr::GfVec3d& InValue);` (scope `UsdToUnreal`)
- L82 _prototype_ `FIntVector ConvertVector(const pxr::GfVec3i& InValue);` (scope `UsdToUnreal`)
- L83 _prototype_ `FVector ConvertVector(const FUsdStageInfo& StageInfo, const pxr::GfVec3h& InValue);` (scope `UsdToUnreal`)
- L84 _prototype_ `FVector ConvertVector(const FUsdStageInfo& StageInfo, const pxr::GfVec3f& InValue);` (scope `UsdToUnreal`)
- L85 _prototype_ `FVector ConvertVector(const FUsdStageInfo& StageInfo, const pxr::GfVec3d& InValue);` (scope `UsdToUnreal`)
- L87 _prototype_ `FVector4 ConvertVector(const pxr::GfVec4h& InValue);` (scope `UsdToUnreal`)
- L88 _prototype_ `FVector4 ConvertVector(const pxr::GfVec4f& InValue);` (scope `UsdToUnreal`)
- L89 _prototype_ `FVector4 ConvertVector(const pxr::GfVec4d& InValue);` (scope `UsdToUnreal`)
- L90 _prototype_ `FIntVector4 ConvertVector(const pxr::GfVec4i& InValue);` (scope `UsdToUnreal`)
- L92 _prototype_ `FMatrix2D ConvertMatrix(const pxr::GfMatrix2d& Matrix);` (scope `UsdToUnreal`)
- L93 _prototype_ `FMatrix3D ConvertMatrix(const pxr::GfMatrix3d& Matrix);` (scope `UsdToUnreal`)
- L94 _prototype_ `FMatrix ConvertMatrix(const pxr::GfMatrix4d& Matrix);` (scope `UsdToUnreal`)
- L96 _prototype_ `FTransform ConvertMatrix(const FUsdStageInfo& StageInfo, const pxr::GfMatrix4d& InMatrix);` (scope `UsdToUnreal`)
- L98 _prototype_ `FQuat ConvertQuat(const pxr::GfQuath& InValue);` (scope `UsdToUnreal`)
- L99 _prototype_ `FQuat ConvertQuat(const pxr::GfQuatf& InValue);` (scope `UsdToUnreal`)
- L100 _prototype_ `FQuat ConvertQuat(const pxr::GfQuatd& InValue);` (scope `UsdToUnreal`)
- L103 _prototype_ `float ConvertDistance(const FUsdStageInfo& StageInfo, float InValue);` (scope `UsdToUnreal`) — Returns a distance in "UE units" (i.e. cm)
- L106 _namespace_ `namespace UnrealToUsd`
- L108 _prototype_ `TUsdStore<std::string> ConvertString(const TCHAR* InString);` (scope `UnrealToUsd`)
- L110 _prototype_ `TUsdStore<pxr::SdfPath> ConvertPath(const TCHAR* InString);` (scope `UnrealToUsd`)
- L112 _prototype_ `TUsdStore<std::string> ConvertName(const FName& InName);` (scope `UnrealToUsd`)
- L114 _prototype_ `TUsdStore<pxr::TfToken> ConvertToken(const TCHAR* InString);` (scope `UnrealToUsd`)
- L117 _prototype_ `pxr::GfVec4f ConvertColor(const FLinearColor& InValue);` (scope `UnrealToUsd`) — Assumes the input color is in linear space. Returns a color in linear space
- L120 _prototype_ `pxr::GfVec4f ConvertColor(const FColor& InValue);` (scope `UnrealToUsd`) — Assumes the input color is in sRGB space. Returns a color in linear space
- L122 _prototype_ `pxr::GfVec2h ConvertVectorHalf(const FVector2D& InValue);` (scope `UnrealToUsd`)
- L123 _prototype_ `pxr::GfVec2f ConvertVectorFloat(const FVector2D& InValue);` (scope `UnrealToUsd`)
- L124 _prototype_ `pxr::GfVec2d ConvertVectorDouble(const FVector2D& InValue);` (scope `UnrealToUsd`)
- L125 _prototype_ `pxr::GfVec2i ConvertVectorInt(const FIntPoint& InValue);` (scope `UnrealToUsd`)
- L127 _prototype_ `pxr::GfVec3h ConvertVectorHalf(const FVector& InValue);` (scope `UnrealToUsd`)
- L128 _prototype_ `pxr::GfVec3f ConvertVectorFloat(const FVector& InValue);` (scope `UnrealToUsd`)
- L129 _prototype_ `pxr::GfVec3d ConvertVectorDouble(const FVector& InValue);` (scope `UnrealToUsd`)
- L130 _prototype_ `pxr::GfVec3i ConvertVectorInt(const FIntVector& InValue);` (scope `UnrealToUsd`)
- L131 _prototype_ `pxr::GfVec3h ConvertVectorHalf(const FUsdStageInfo& StageInfo, const FVector& InValue);` (scope `UnrealToUsd`)
- L132 _prototype_ `pxr::GfVec3f ConvertVectorFloat(const FUsdStageInfo& StageInfo, const FVector& InValue);` (scope `UnrealToUsd`)
- L133 _prototype_ `pxr::GfVec3d ConvertVectorDouble(const FUsdStageInfo& StageInfo, const FVector& InValue);` (scope `UnrealToUsd`)
- L135 _prototype_ `pxr::GfVec4h ConvertVectorHalf(const FVector4& InValue);` (scope `UnrealToUsd`)
- L136 _prototype_ `pxr::GfVec4f ConvertVectorFloat(const FVector4& InValue);` (scope `UnrealToUsd`)
- L137 _prototype_ `pxr::GfVec4d ConvertVectorDouble(const FVector4& InValue);` (scope `UnrealToUsd`)
- L138 _prototype_ `pxr::GfVec4i ConvertVectorInt(const FIntVector4& InValue);` (scope `UnrealToUsd`)
- L140 _prototype_ `pxr::GfMatrix2d ConvertMatrix(const FMatrix2D& Matrix);` (scope `UnrealToUsd`)
- L141 _prototype_ `pxr::GfMatrix3d ConvertMatrix(const FMatrix3D& Matrix);` (scope `UnrealToUsd`)
- L142 _prototype_ `pxr::GfMatrix4d ConvertMatrix(const FMatrix& Matrix);` (scope `UnrealToUsd`)
- L144 _prototype_ `pxr::GfQuath ConvertQuatHalf(const FQuat& InValue);` (scope `UnrealToUsd`)
- L145 _prototype_ `pxr::GfQuatf ConvertQuatFloat(const FQuat& InValue);` (scope `UnrealToUsd`)
- L146 _prototype_ `pxr::GfQuatd ConvertQuatDouble(const FQuat& InValue);` (scope `UnrealToUsd`)
- L148 _prototype_ `pxr::GfMatrix4d ConvertTransform(const FUsdStageInfo& StageInfo, const FTransform& Transform);` (scope `UnrealToUsd`)
- L151 _prototype_ `float ConvertDistance(const FUsdStageInfo& StageInfo, float InValue);` (scope `UnrealToUsd`) — Returns a distance in USD units (depends on metersPerUnit)
- L153 _prototype_ `TUsdStore<pxr::VtArray<pxr::GfVec3f>> ConvertBounds(const FUsdStageInfo& StageInfo, FBox Bounds);` (scope `UnrealToUsd`)
- L156 _namespace_ `namespace UsdUtils`
- L163 _prototype_ `FTransform DecomposeWithUniformReflection(const FMatrix& InMatrix);` (scope `UsdUtils`) — Decomposes the FMatrix into an FTransform. Identical to FTransform::SetFromMatrix, except that if a reflection is detected all axes are flipped instead of only the X axis, which keeps a uniform scaling.
- L165 _prototype_ `FTransform ConvertTransformToUsdSpace(const FUsdStageInfo& StageInfo, const FTransform& TransformInUESpace);` (scope `UsdUtils`)
- L166 _prototype_ `FTransform ConvertTransformToUESpace(const FUsdStageInfo& StageInfo, const FTransform& TransformInUsdSpace);` (scope `UsdUtils`)
- L169 _prototype_ `FTransform GetUsdToUESpaceTransform(const FUsdStageInfo& StageInfo);` (scope `UsdUtils`) — Produces a transform that can be applied to a point from USD space to convert it into UE space
- L171 _prototype_ `FTransform ConvertAxes(const bool bZUp, const FTransform Transform);` (scope `UsdUtils`)

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDUtilitiesModule.h` (Public)


#### class `IUsdUtilitiesModule`  
`class IUsdUtilitiesModule : public IModuleInterface`  
_L9-22_
- inherits: `IModuleInterface`
- L20 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool , FOnReferenceHandlingDialog, const FText& , EReferencerTypeHandling& );` — Delegate that is invoked when the AddReference / AddPayload functions want to display a dialog so the user can pick the desired behavior for handling referencer type names. This is needed because those functions are in RTTI=true modules, where Slate code doesn't compile, and also USDUtilities can't easily depend on any other USD module that is RTTI=false. The USDStageEditorModule should register the intended dialog here when it runs its StartupModule()
- L21 _public member_ `FOnReferenceHandlingDialog OnReferenceHandlingDialog;`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool , FOnReferenceHandlingDialog, const FText& , EReferencerTypeHandling& );` — Delegate that is invoked when the AddReference / AddPayload functions want to display a dialog so the user can pick the desired behavior for handling referencer type names. This is needed because those functions are in RTTI=true modules, where Slate code doesn't compile, and also USDUtilities can't easily depend on any other USD module that is RTTI=false. The USDStageEditorModule should register the intended dialog here when it runs its StartupModule()

### `Plugins/Runtime/USDCore/Source/USDUtilities/Public/USDValueConversion.h` (Public)


#### enum `UsdUtils::EUsdBasicDataTypes`  
`enum class EUsdBasicDataTypes`  
_L39-82_
- desc: Source: https://graphics.pixar.com/usd/docs/api/_usd__page__datatypes.html
- L41 _public enumerator_ `None`
- L43 _public enumerator_ `Bool`
- L44 _public enumerator_ `Uchar`
- L45 _public enumerator_ `Int`
- L46 _public enumerator_ `Uint`
- L47 _public enumerator_ `Int64`
- L48 _public enumerator_ `Uint64`
- L50 _public enumerator_ `Half`
- L51 _public enumerator_ `Float`
- L52 _public enumerator_ `Double`
- L54 _public enumerator_ `Timecode`
- L56 _public enumerator_ `String`
- L57 _public enumerator_ `Token`
- L58 _public enumerator_ `Asset`
- L60 _public enumerator_ `Matrix2d`
- L61 _public enumerator_ `Matrix3d`
- L62 _public enumerator_ `Matrix4d`
- L64 _public enumerator_ `Quatd`
- L65 _public enumerator_ `Quatf`
- L66 _public enumerator_ `Quath`
- L68 _public enumerator_ `Double2`
- L69 _public enumerator_ `Float2`
- L70 _public enumerator_ `Half2`
- L71 _public enumerator_ `Int2`
- L73 _public enumerator_ `Double3`
- L74 _public enumerator_ `Float3`
- L75 _public enumerator_ `Half3`
- L76 _public enumerator_ `Int3`
- L78 _public enumerator_ `Double4`
- L79 _public enumerator_ `Float4`
- L80 _public enumerator_ `Half4`
- L81 _public enumerator_ `Int4`

#### struct `UsdUtils::FConvertedVtValue`  
`struct FConvertedVtValue`  
_L93-102_
- desc: Corresponds to a value held by a pxr::VtValue converted into UE types. Should handle anything a VtValue can hold, including arrays of values
- L95 _public member_ `TArray<FConvertedVtValueEntry> Entries;`
- L97 _public member_ `EUsdBasicDataTypes SourceType = EUsdBasicDataTypes::None;`
- L98 _public member_ `FString ExtraTypeInfo;` — Used so that we can serialize something like SdfListOp<Token> as basically a token array, but still get the same
- L100 _public member_ `bool bIsArrayValued = false;` — type when converting back on the other end.
- L101 _public member_ `bool bIsEmpty = false;` — Helps differentiating between empty arrays and having actually no value

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace UE`
- L36 _namespace_ `namespace UsdUtils`
- L86 _typedef_ `using FConvertedVtValueComponent = TVariant<bool, uint8, int32, uint32, int64, uint64, float, double, FString>;` (scope `UsdUtils`) — WARNING: Do not change the order of the types in this TVariant declaration, or it will break backwards compatibility with data that was serialized before the change, due to how `operator<<( FArchive& Ar, FConvertedVtValueComponent& Component )` is implemented
- L89 _typedef_ `using FConvertedVtValueEntry = TArray<FConvertedVtValueComponent>;` (scope `UsdUtils`) — Represents a single non-array value held by a pxr::VtValue object, like a 'float', a 'TfToken' or a 'GfMatrix3d'
- L105 _prototype_ `FArchive& operator<<(FArchive& Ar, UsdUtils::FConvertedVtValue& Struct);`
- L106 _prototype_ `FArchive& operator<<(FArchive& Ar, UsdUtils::FConvertedVtValueComponent& Component);`
- L108 _namespace_ `namespace UsdToUnreal`
- L110 _prototype_ `bool ConvertValue(const UE::FVtValue& InValue, UsdUtils::FConvertedVtValue& OutValue);` (scope `UsdToUnreal`)
- L113 _namespace_ `namespace UnrealToUsd`
- L115 _prototype_ `bool ConvertValue(const UsdUtils::FConvertedVtValue& InValue, UE::FVtValue& OutValue);` (scope `UnrealToUsd`)
- L118 _namespace_ `namespace UsdUtils`
- L125 _prototype_ `FString Stringify(const UE::FVtValue& Value);` (scope `UsdUtils`) — Mostly uses USD to stringify the underlying value of the provided pxr::VtValue, but will use some custom implementation depending on the type. For string-like types in particular we will mostly use our own implementations, as they preserve quotes and delimiters in a way that we can unstringify later.
- L127 _prototype_ `FString Stringify(const pxr::VtValue& Value);` (scope `UsdUtils`)
- L140 _prototype_ `FString StringifyAsBool(bool Value);` (scope `UsdUtils`) — Converts the UE type into a string that can be set as USD metadata with the corresponding USD data type. We need these explicit functions here as well as the generic Stringify() because our Python/Blueprint libraries need to do these operations, but they are on modules that can't manipulate the USD types directly, and we need to be able to internally e.g. convert a TArray<FString> into a pxr::SdfListOp<pxr::TfToken> to stringify some of these. We provide Python/Blueprint libraries that can do these stringify/unstringify functions in the first place because otherwise a user that tried to manipulate metadata values from Python/Blueprint would be forced to either be content with just strings and not actual types, or to try unstringifying these types on their own (and it would not be trivial to unstringify an e.g. matrix3d[] on Blueprint)
- L141 _prototype_ `FString StringifyAsUChar(uint8 Value);` (scope `UsdUtils`)
- L142 _prototype_ `FString StringifyAsInt(int32 Value);` (scope `UsdUtils`)
- L143 _prototype_ `FString StringifyAsUInt(uint32 Value);` (scope `UsdUtils`)
- L144 _prototype_ `FString StringifyAsInt64(int64 Value);` (scope `UsdUtils`)
- L145 _prototype_ `FString StringifyAsUInt64(uint64 Value);` (scope `UsdUtils`)
- L146 _prototype_ `FString StringifyAsHalf(float Value);` (scope `UsdUtils`)
- L147 _prototype_ `FString StringifyAsFloat(float Value);` (scope `UsdUtils`)
- L148 _prototype_ `FString StringifyAsDouble(double Value);` (scope `UsdUtils`)
- L149 _prototype_ `FString StringifyAsTimeCode(double Value);` (scope `UsdUtils`)
- L150 _prototype_ `FString StringifyAsString(const FString& Value);` (scope `UsdUtils`)
- L151 _prototype_ `FString StringifyAsToken(const FString& Value);` (scope `UsdUtils`)
- L152 _prototype_ `FString StringifyAsAssetPath(const FString& Value);` (scope `UsdUtils`)
- L153 _prototype_ `FString StringifyAsMatrix2d(const FMatrix2D& Value);` (scope `UsdUtils`)
- L154 _prototype_ `FString StringifyAsMatrix3d(const FMatrix3D& Value);` (scope `UsdUtils`)
- L155 _prototype_ `FString StringifyAsMatrix4d(const FMatrix& Value);` (scope `UsdUtils`)
- L156 _prototype_ `FString StringifyAsQuatd(const FQuat& Value);` (scope `UsdUtils`)
- L157 _prototype_ `FString StringifyAsQuatf(const FQuat& Value);` (scope `UsdUtils`)
- L158 _prototype_ `FString StringifyAsQuath(const FQuat& Value);` (scope `UsdUtils`)
- L159 _prototype_ `FString StringifyAsDouble2(const FVector2D& Value);` (scope `UsdUtils`)
- L160 _prototype_ `FString StringifyAsFloat2(const FVector2D& Value);` (scope `UsdUtils`)
- L161 _prototype_ `FString StringifyAsHalf2(const FVector2D& Value);` (scope `UsdUtils`)
- L162 _prototype_ `FString StringifyAsInt2(const FIntPoint& Value);` (scope `UsdUtils`)
- L163 _prototype_ `FString StringifyAsDouble3(const FVector& Value);` (scope `UsdUtils`)
- L164 _prototype_ `FString StringifyAsFloat3(const FVector& Value);` (scope `UsdUtils`)
- L165 _prototype_ `FString StringifyAsHalf3(const FVector& Value);` (scope `UsdUtils`)
- L166 _prototype_ `FString StringifyAsInt3(const FIntVector& Value);` (scope `UsdUtils`)
- L167 _prototype_ `FString StringifyAsDouble4(const FVector4& Value);` (scope `UsdUtils`)
- L168 _prototype_ `FString StringifyAsFloat4(const FVector4& Value);` (scope `UsdUtils`)
- L169 _prototype_ `FString StringifyAsHalf4(const FVector4& Value);` (scope `UsdUtils`)
- L170 _prototype_ `FString StringifyAsInt4(const FIntVector4& Value);` (scope `UsdUtils`)
- L171 _prototype_ `FString StringifyAsBoolArray(const TArray<bool>& Value);` (scope `UsdUtils`)
- L172 _prototype_ `FString StringifyAsUCharArray(const TArray<uint8>& Value);` (scope `UsdUtils`)
- L173 _prototype_ `FString StringifyAsIntArray(const TArray<int32>& Value);` (scope `UsdUtils`)
- L174 _prototype_ `FString StringifyAsUIntArray(const TArray<uint32>& Value);` (scope `UsdUtils`)
- L175 _prototype_ `FString StringifyAsInt64Array(const TArray<int64>& Value);` (scope `UsdUtils`)
- L176 _prototype_ `FString StringifyAsUInt64Array(const TArray<uint64>& Value);` (scope `UsdUtils`)
- L177 _prototype_ `FString StringifyAsHalfArray(const TArray<float>& Value);` (scope `UsdUtils`)
- L178 _prototype_ `FString StringifyAsFloatArray(const TArray<float>& Value);` (scope `UsdUtils`)
- L179 _prototype_ `FString StringifyAsDoubleArray(const TArray<double>& Value);` (scope `UsdUtils`)
- L180 _prototype_ `FString StringifyAsTimeCodeArray(const TArray<double>& Value);` (scope `UsdUtils`)
- L181 _prototype_ `FString StringifyAsStringArray(const TArray<FString>& Value);` (scope `UsdUtils`)
- L182 _prototype_ `FString StringifyAsTokenArray(const TArray<FString>& Value);` (scope `UsdUtils`)
- L183 _prototype_ `FString StringifyAsAssetPathArray(const TArray<FString>& Value);` (scope `UsdUtils`)
- L184 _prototype_ `FString StringifyAsListOpTokens(const TArray<FString>& Value);` (scope `UsdUtils`)
- L185 _prototype_ `FString StringifyAsMatrix2dArray(const TArray<FMatrix2D>& Value);` (scope `UsdUtils`)
- L186 _prototype_ `FString StringifyAsMatrix3dArray(const TArray<FMatrix3D>& Value);` (scope `UsdUtils`)
- L187 _prototype_ `FString StringifyAsMatrix4dArray(const TArray<FMatrix>& Value);` (scope `UsdUtils`)
- L188 _prototype_ `FString StringifyAsQuatdArray(const TArray<FQuat>& Value);` (scope `UsdUtils`)
- L189 _prototype_ `FString StringifyAsQuatfArray(const TArray<FQuat>& Value);` (scope `UsdUtils`)
- L190 _prototype_ `FString StringifyAsQuathArray(const TArray<FQuat>& Value);` (scope `UsdUtils`)
- L191 _prototype_ `FString StringifyAsDouble2Array(const TArray<FVector2D>& Value);` (scope `UsdUtils`)
- L192 _prototype_ `FString StringifyAsFloat2Array(const TArray<FVector2D>& Value);` (scope `UsdUtils`)
- L193 _prototype_ `FString StringifyAsHalf2Array(const TArray<FVector2D>& Value);` (scope `UsdUtils`)
- L194 _prototype_ `FString StringifyAsInt2Array(const TArray<FIntPoint>& Value);` (scope `UsdUtils`)
- L195 _prototype_ `FString StringifyAsDouble3Array(const TArray<FVector>& Value);` (scope `UsdUtils`)
- L196 _prototype_ `FString StringifyAsFloat3Array(const TArray<FVector>& Value);` (scope `UsdUtils`)
- L197 _prototype_ `FString StringifyAsHalf3Array(const TArray<FVector>& Value);` (scope `UsdUtils`)
- L198 _prototype_ `FString StringifyAsInt3Array(const TArray<FIntVector>& Value);` (scope `UsdUtils`)
- L199 _prototype_ `FString StringifyAsDouble4Array(const TArray<FVector4>& Value);` (scope `UsdUtils`)
- L200 _prototype_ `FString StringifyAsFloat4Array(const TArray<FVector4>& Value);` (scope `UsdUtils`)
- L201 _prototype_ `FString StringifyAsHalf4Array(const TArray<FVector4>& Value);` (scope `UsdUtils`)
- L202 _prototype_ `FString StringifyAsInt4Array(const TArray<FIntVector4>& Value);` (scope `UsdUtils`)
- L210 _prototype_ `bool Unstringify(const FString& String, const FString& TypeName, pxr::VtValue& Output);` (scope `UsdUtils`) — Unstringifies the data in String according to what TypeName it is. The unstringified USD value is placed into a VtValue for type erasure. Example: String is "(1, 0.5, 0.3)" and TypeName "float3" means Output will contain a pxr::GfVec3f(1, 0.5, 0.3) value
- L214 _prototype_ `bool UnstringifyAsBool(const FString& String, bool& OutValue);` (scope `UsdUtils`) — c.f. comment above StringifyAsBool
- L215 _prototype_ `bool UnstringifyAsUChar(const FString& String, uint8& OutValue);` (scope `UsdUtils`)
- L216 _prototype_ `bool UnstringifyAsInt(const FString& String, int32& OutValue);` (scope `UsdUtils`)
- L217 _prototype_ `bool UnstringifyAsUInt(const FString& String, uint32& OutValue);` (scope `UsdUtils`)
- L218 _prototype_ `bool UnstringifyAsInt64(const FString& String, int64& OutValue);` (scope `UsdUtils`)
- L219 _prototype_ `bool UnstringifyAsUInt64(const FString& String, uint64& OutValue);` (scope `UsdUtils`)
- L220 _prototype_ `bool UnstringifyAsHalf(const FString& String, float& OutValue);` (scope `UsdUtils`)
- L221 _prototype_ `bool UnstringifyAsFloat(const FString& String, float& OutValue);` (scope `UsdUtils`)
- L222 _prototype_ `bool UnstringifyAsDouble(const FString& String, double& OutValue);` (scope `UsdUtils`)
- L223 _prototype_ `bool UnstringifyAsTimeCode(const FString& String, double& OutValue);` (scope `UsdUtils`)
- L224 _prototype_ `bool UnstringifyAsString(const FString& String, FString& OutValue);` (scope `UsdUtils`)
- L225 _prototype_ `bool UnstringifyAsToken(const FString& String, FString& OutValue);` (scope `UsdUtils`)
- L226 _prototype_ `bool UnstringifyAsAssetPath(const FString& String, FString& OutValue);` (scope `UsdUtils`)
- L227 _prototype_ `bool UnstringifyAsMatrix2d(const FString& String, FMatrix2D& OutValue);` (scope `UsdUtils`)
- L228 _prototype_ `bool UnstringifyAsMatrix3d(const FString& String, FMatrix3D& OutValue);` (scope `UsdUtils`)
- L229 _prototype_ `bool UnstringifyAsMatrix4d(const FString& String, FMatrix& OutValue);` (scope `UsdUtils`)
- L230 _prototype_ `bool UnstringifyAsQuatd(const FString& String, FQuat& OutValue);` (scope `UsdUtils`)
- L231 _prototype_ `bool UnstringifyAsQuatf(const FString& String, FQuat& OutValue);` (scope `UsdUtils`)
- L232 _prototype_ `bool UnstringifyAsQuath(const FString& String, FQuat& OutValue);` (scope `UsdUtils`)
- L233 _prototype_ `bool UnstringifyAsDouble2(const FString& String, FVector2D& OutValue);` (scope `UsdUtils`)
- L234 _prototype_ `bool UnstringifyAsFloat2(const FString& String, FVector2D& OutValue);` (scope `UsdUtils`)
- L235 _prototype_ `bool UnstringifyAsHalf2(const FString& String, FVector2D& OutValue);` (scope `UsdUtils`)
- L236 _prototype_ `bool UnstringifyAsInt2(const FString& String, FIntPoint& OutValue);` (scope `UsdUtils`)
- L237 _prototype_ `bool UnstringifyAsDouble3(const FString& String, FVector& OutValue);` (scope `UsdUtils`)
- L238 _prototype_ `bool UnstringifyAsFloat3(const FString& String, FVector& OutValue);` (scope `UsdUtils`)
- L239 _prototype_ `bool UnstringifyAsHalf3(const FString& String, FVector& OutValue);` (scope `UsdUtils`)
- L240 _prototype_ `bool UnstringifyAsInt3(const FString& String, FIntVector& OutValue);` (scope `UsdUtils`)
- L241 _prototype_ `bool UnstringifyAsDouble4(const FString& String, FVector4& OutValue);` (scope `UsdUtils`)
- L242 _prototype_ `bool UnstringifyAsFloat4(const FString& String, FVector4& OutValue);` (scope `UsdUtils`)
- L243 _prototype_ `bool UnstringifyAsHalf4(const FString& String, FVector4& OutValue);` (scope `UsdUtils`)
- L244 _prototype_ `bool UnstringifyAsInt4(const FString& String, FIntVector4& OutValue);` (scope `UsdUtils`)
- L245 _prototype_ `bool UnstringifyAsBoolArray(const FString& String, TArray<bool>& OutValue);` (scope `UsdUtils`)
- L246 _prototype_ `bool UnstringifyAsUCharArray(const FString& String, TArray<uint8>& OutValue);` (scope `UsdUtils`)
- L247 _prototype_ `bool UnstringifyAsIntArray(const FString& String, TArray<int32>& OutValue);` (scope `UsdUtils`)
- L248 _prototype_ `bool UnstringifyAsUIntArray(const FString& String, TArray<uint32>& OutValue);` (scope `UsdUtils`)
- L249 _prototype_ `bool UnstringifyAsInt64Array(const FString& String, TArray<int64>& OutValue);` (scope `UsdUtils`)
- L250 _prototype_ `bool UnstringifyAsUInt64Array(const FString& String, TArray<uint64>& OutValue);` (scope `UsdUtils`)
- L251 _prototype_ `bool UnstringifyAsHalfArray(const FString& String, TArray<float>& OutValue);` (scope `UsdUtils`)
- L252 _prototype_ `bool UnstringifyAsFloatArray(const FString& String, TArray<float>& OutValue);` (scope `UsdUtils`)
- L253 _prototype_ `bool UnstringifyAsDoubleArray(const FString& String, TArray<double>& OutValue);` (scope `UsdUtils`)
- L254 _prototype_ `bool UnstringifyAsTimeCodeArray(const FString& String, TArray<double>& OutValue);` (scope `UsdUtils`)
- L255 _prototype_ `bool UnstringifyAsStringArray(const FString& String, TArray<FString>& OutValue);` (scope `UsdUtils`)
- L256 _prototype_ `bool UnstringifyAsTokenArray(const FString& String, TArray<FString>& OutValue);` (scope `UsdUtils`)
- L257 _prototype_ `bool UnstringifyAsAssetPathArray(const FString& String, TArray<FString>& OutValue);` (scope `UsdUtils`)
- L258 _prototype_ `bool UnstringifyAsListOpTokens(const FString& String, TArray<FString>& OutValue);` (scope `UsdUtils`)
- L259 _prototype_ `bool UnstringifyAsMatrix2dArray(const FString& String, TArray<FMatrix2D>& OutValue);` (scope `UsdUtils`)
- L260 _prototype_ `bool UnstringifyAsMatrix3dArray(const FString& String, TArray<FMatrix3D>& OutValue);` (scope `UsdUtils`)
- L261 _prototype_ `bool UnstringifyAsMatrix4dArray(const FString& String, TArray<FMatrix>& OutValue);` (scope `UsdUtils`)
- L262 _prototype_ `bool UnstringifyAsQuatdArray(const FString& String, TArray<FQuat>& OutValue);` (scope `UsdUtils`)
- L263 _prototype_ `bool UnstringifyAsQuatfArray(const FString& String, TArray<FQuat>& OutValue);` (scope `UsdUtils`)
- L264 _prototype_ `bool UnstringifyAsQuathArray(const FString& String, TArray<FQuat>& OutValue);` (scope `UsdUtils`)
- L265 _prototype_ `bool UnstringifyAsDouble2Array(const FString& String, TArray<FVector2D>& OutValue);` (scope `UsdUtils`)
- L266 _prototype_ `bool UnstringifyAsFloat2Array(const FString& String, TArray<FVector2D>& OutValue);` (scope `UsdUtils`)
- L267 _prototype_ `bool UnstringifyAsHalf2Array(const FString& String, TArray<FVector2D>& OutValue);` (scope `UsdUtils`)
- L268 _prototype_ `bool UnstringifyAsInt2Array(const FString& String, TArray<FIntPoint>& OutValue);` (scope `UsdUtils`)
- L269 _prototype_ `bool UnstringifyAsDouble3Array(const FString& String, TArray<FVector>& OutValue);` (scope `UsdUtils`)
- L270 _prototype_ `bool UnstringifyAsFloat3Array(const FString& String, TArray<FVector>& OutValue);` (scope `UsdUtils`)
- L271 _prototype_ `bool UnstringifyAsHalf3Array(const FString& String, TArray<FVector>& OutValue);` (scope `UsdUtils`)
- L272 _prototype_ `bool UnstringifyAsInt3Array(const FString& String, TArray<FIntVector>& OutValue);` (scope `UsdUtils`)
- L273 _prototype_ `bool UnstringifyAsDouble4Array(const FString& String, TArray<FVector4>& OutValue);` (scope `UsdUtils`)
- L274 _prototype_ `bool UnstringifyAsFloat4Array(const FString& String, TArray<FVector4>& OutValue);` (scope `UsdUtils`)
- L275 _prototype_ `bool UnstringifyAsHalf4Array(const FString& String, TArray<FVector4>& OutValue);` (scope `UsdUtils`)
- L276 _prototype_ `bool UnstringifyAsInt4Array(const FString& String, TArray<FIntVector4>& OutValue);` (scope `UsdUtils`)
- L284 _prototype_ `template<typename T> TOptional<T> GetUnderlyingValue(const UE::FVtValue& InValue);` (scope `UsdUtils`) — Uses USD to quickly fetch the underlying value of the wrapped pxr::VtValue for fundamental data types. For complex vector/array types ConvertValue must be used instead. Template implementation must be hidden on cpp as we can't expose USD implementation on the header files.
- L294 _prototype_ `template<typename T> bool SetUnderlyingValue(UE::FVtValue& InValue, const T& UnderlyingValue);` (scope `UsdUtils`) — Uses USD to quickly set the underlying value of the wrapped pxr::VtValue for fundamental data types. This will not allow changing the underlying type of InValue, i.e. you can only set a float if InValue already contains a float or if its otherwise empty. For complex vector/array types ConvertValue must be used instead. Template implementation must be hidden on cpp as we can't expose USD implementation on the header files.
- L303 _prototype_ `FString GetImpliedTypeName(const UE::FVtValue& Value);` (scope `UsdUtils`) — Returns the name of the SdfValueTypeName object for the type of Value Note that this is the "Value type token" (e.g. will be something like 'matrix4d' or 'double2', and not 'GfMatrix4d' or 'GfVec2d') Note that this may not be the correct SdfValueTypeName for the *attribute*, it's just the implied type of the value (e.g. for an attribute with SdfValueTypeName 'normal3d', it's VtValues would have underlying type 'GfVec3d', and so this function would return 'double3')
