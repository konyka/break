# Plugins / USDStage

- module root: `Plugins/Importers/USDImporter/Source/USDStage`
- headers: 11; symbols: 334
- symbol kinds: class=12, delegate=7, enum=2, enumerator=4, externvar=1, function=6, macro=6, member=81, namespace=10, prototype=202, struct=2, typedef=1
- PrivateDependencyModuleNames: AnimationCore, BlueprintGraph, CinematicCamera, ControlRig, ControlRigDeveloper, Core, CoreUObject, DeveloperToolSettings, EditorStyle, Engine, GeometryCache, GeometryCacheTracks, GeometryCacheUSD, HairStrandsCore, InputCore, Kismet, LevelSequence, LevelSequenceEditor, LiveLinkComponents, LiveLinkInterface, MeshDescription, MovieScene, MovieSceneTools, MovieSceneTracks, Niagara, PropertyEditor, RigVM, RigVMDeveloper, SceneOutliner, Sequencer, Slate, SlateCore, StaticMeshDescription, USDClasses, USDClassesEditor, USDUtilities, UniversalObjectLocator, UniversalObjectLocatorEditor, UnrealEd, UnrealUSDWrapper
- PublicDependencyModuleNames: USDSchemas

### `Plugins/Importers/USDImporter/Source/USDStage/Private/USDLocatorEditors.h` (Private)


#### class `UE::UniversalObjectLocator::FUsdPrimLocatorEditor`  
`class FUsdPrimLocatorEditor : public ILocatorFragmentEditor`  
_L12-27_
- inherits: `ILocatorFragmentEditor`
- L16 _public prototype_ `ELocatorFragmentEditorType GetLocatorFragmentEditorType() const override;`
- L17 _public prototype_ `bool IsAllowedInContext(FName InContextName) const override;`
- L18 _public prototype_ `bool IsDragSupported(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L19 _public prototype_ `UObject* ResolveDragOperation(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L20 _public prototype_ `TSharedPtr<SWidget> MakeEditUI(const FEditUIParameters& InParameters) override;`
- L21 _public prototype_ `FText GetDisplayText(const FUniversalObjectLocatorFragment* InFragment) const override;`
- L22 _public prototype_ `FText GetDisplayTooltip(const FUniversalObjectLocatorFragment* InFragment) const override;`
- L23 _public prototype_ `FSlateIcon GetDisplayIcon(const FUniversalObjectLocatorFragment* InFragment) const override;`
- L24 _public prototype_ `UClass* ResolveClass(const FUniversalObjectLocatorFragment& InFragment, UObject* InContext) const override;`
- L25 _public prototype_ `FUniversalObjectLocatorFragment MakeDefaultLocatorFragment() const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)

### `Plugins/Importers/USDImporter/Source/USDStage/Private/USDStageActorCustomization.h` (Private)


#### class `FUsdStageActorCustomization`  
`class FUsdStageActorCustomization : public IDetailCustomization`  
_L13-36_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `FUsdStageActorCustomization();`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L21 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L25 _private prototype_ `void OnComboBoxSelectionChanged(TSharedPtr<FString> NewContext, ESelectInfo::Type SelectType);`
- L26 _private prototype_ `FText GetComboBoxSelectedOptionText() const;`
- L27 _private prototype_ `void ForceRefreshDetails();`
- L29 _private member_ `AUsdStageActor* CurrentActor;`
- L30 _private member_ `TWeakPtr<IDetailLayoutBuilder> DetailBuilderWeakPtr;`
- L32 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> RenderContextComboBox;`
- L33 _private member_ `TArray<TSharedPtr<FString>> RenderContextComboBoxItems;`
- L35 _private member_ `TArray<TSharedPtr<FString>> MaterialPurposeComboBoxItems;`

### `Plugins/Importers/USDImporter/Source/USDStage/Public/USDDynamicBindingResolverLibrary.h` (Public)


#### class `UUsdDynamicBindingResolverLibrary`  
`class UUsdDynamicBindingResolverLibrary : public UBlueprintFunctionLibrary`  
_L17-43_
- inherits: `UBlueprintFunctionLibrary`
- L36 _public prototype_ `static FMovieSceneDynamicBindingResolveResult ResolveWithStageActor( UObject* WorldContextObject, const FMovieSceneDynamicBindingResolveParams& Params, const FString& StageActorIDNameFilter, const FString& RootLayerFilter, const FString& PrimPath );` — `UFUNCTION(BlueprintPure, Category = "USD|Dynamic Binding", meta = (WorldContext = "WorldContextObject"))` — Resolves a Sequencer Dynamic Binding described on Params, returning the actor or component that the Sequencer should bind to @param WorldContextObject - Some UObject that lives in the UWorld that we're talking about @param Params - The binding to resolve @param StageActorIDNameFilter - The "ID Name"/FName of a AUsdStageActor to restrict our search for actor and components to. Can be empty. @param RootLayerFilter - The root layer file path to restrict our search for actor and components to. This should match what is shown on the Stage Actor's RootLayer property. Can be empty. @param PrimPath - The path to the prim that generates the actor or component that this binding should resolve to (e.g. '/cube') @return The result struct containing the resolved UObject

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API USDSTAGE_API`

### `Plugins/Importers/USDImporter/Source/USDStage/Public/USDInfoCacheObject.h` (Public)


#### class `UUsdInfoCache`  
`class UUsdInfoCache : public UObject`  
_L24-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Minimal UObject wrapper around FUsdInfoCache, since we want this data to be owned by an independently serializable UObject, but the implementation must be in an RTTI-enabled module
- L29 _public prototype_ `UUsdInfoCache();`
- L32 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L35 _public prototype_ `FUsdInfoCache& GetInner();`
- L36 _public prototype_ `const FUsdInfoCache& GetInner() const;`
- L39 _private member_ `TPimplPtr<FUsdInfoCache> Impl;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API USDSTAGE_API`
- L13 _namespace_ `namespace UE`

### `Plugins/Importers/USDImporter/Source/USDStage/Public/USDLevelSequenceHelper.h` (Public)


#### class `FUsdLevelSequenceHelper`  
`class FUsdLevelSequenceHelper`  
_L29-110_
- desc: Builds and maintains the level sequence and subsequences for a Usd Stage
- L32 _public prototype_ `FUsdLevelSequenceHelper();`
- L33 _public prototype_ `virtual ~FUsdLevelSequenceHelper();`
- L36 _public prototype_ `FUsdLevelSequenceHelper(const FUsdLevelSequenceHelper& Other);` — Copy semantics are there for convenience only. Copied FUsdLevelSequenceHelper are empty and require a call to Init().
- L37 _public prototype_ `FUsdLevelSequenceHelper& operator=(const FUsdLevelSequenceHelper& Other);`
- L39 _public prototype_ `FUsdLevelSequenceHelper(FUsdLevelSequenceHelper&& Other);`
- L40 _public prototype_ `FUsdLevelSequenceHelper& operator=(FUsdLevelSequenceHelper&& Other);`
- L44 _public prototype_ `ULevelSequence* Init(const UE::FUsdStage& UsdStage);` — Creates the main level sequence and subsequences from the usd stage layers
- L47 _public prototype_ `bool Serialize(FArchive& Ar);` — Allows serialization for transaction support
- L49 _public prototype_ `void SetPrimLinkCache(UUsdPrimLinkCache* PrimLinkCache);`
- L53 _public prototype_ `void SetBBoxCache(TSharedPtr<UE::FUsdGeomBBoxCache> InBBoxCache);` — Sets the BBoxCache to use when importing bound animations for prims. Needed for importing, where we don't have a stage actor to take the BBoxCache from
- L56 _public prototype_ `bool HasData() const;` — Returns true if we have at least one possessable or a reference to a subsequence
- L59 _public prototype_ `void OnStageActorRenamed();` — Call this whenever the stage actor is renamed, to replace the possessable binding with a new one
- L62 _public prototype_ `void Clear();` — Resets the helper, abandoning all managed LevelSequences
- L65 _public prototype_ `void BindToUsdStageActor(AUsdStageActor* StageActor);` — Creates the time track for the StageActor. This will also set the root handling mode to the provided actor's, if any
- L66 _public prototype_ `void UnbindFromUsdStageActor();`
- L73 _public prototype_ `EUsdRootMotionHandling GetRootMotionHandling() const;` — Gets the current root motion handling mode. We use this to prevent animation that has already been baked into AnimSequences as root joint motion from also being parsed as LevelSequence tracks.
- L78 _public prototype_ `void SetRootMotionHandling(EUsdRootMotionHandling NewValue);` — Sets the current root motion handling mode.
- L89 _public prototype_ `void AddPrim(UUsdPrimTwin& PrimTwin, bool bForceVisibilityTracks = false, TOptional<bool> HasAnimatedBounds = {});` — Adds the necessary tracks for a given prim to the level sequence. If bForceVisibilityTracks is true, will add visibility tracks even if this prim doesn't actually have timeSamples on its visibility attribute (use this when a parent does have animated visibility, and we need to "bake" that out to a dedicated visibility track so that the standalone LevelSequence asset behaves as expected). We'll check the prim for animated bounds and add bounds tracks, unless bHasAnimatedBounds already provides whether the prim has animated bounds or not.
- L92 _public prototype_ `void RemovePrim(const UUsdPrimTwin& PrimTwin);` — Removes any track associated with this prim
- L94 _public prototype_ `void UpdateControlRigTracks(UUsdPrimTwin& PrimTwin);`
- L97 _public prototype_ `void StartMonitoringChanges();` — Blocks updating the level sequences & tracks from object changes.
- L98 _public prototype_ `void StopMonitoringChanges();`
- L99 _public prototype_ `void BlockMonitoringChangesForThisTransaction();`
- L101 _public prototype_ `ULevelSequence* GetMainLevelSequence() const;`
- L102 _public prototype_ `TArray<ULevelSequence*> GetSubSequences() const;`
- L104 _public prototype_ `DECLARE_EVENT_OneParam(FUsdLevelSequenceHelper, FOnSkelAnimationBaked, const FString& );`
- L105 _public prototype_ `FOnSkelAnimationBaked& GetOnSkelAnimationBaked();`
- L109 _private member_ `TUniquePtr<FUsdLevelSequenceHelperImpl> UsdSequencerImpl;`

#### class `FScopedBlockMonitoringChangesForTransaction`  
`class FScopedBlockMonitoringChangesForTransaction final`  
_L112-128_
- L115 _public prototype_ `explicit FScopedBlockMonitoringChangesForTransaction(FUsdLevelSequenceHelper& InHelper);`
- L116 _public prototype_ `explicit FScopedBlockMonitoringChangesForTransaction(FUsdLevelSequenceHelperImpl& InHelperImpl);`
- L117 _public prototype_ `~FScopedBlockMonitoringChangesForTransaction();`
- L119 _public prototype_ `FScopedBlockMonitoringChangesForTransaction() = delete;`
- L120 _public prototype_ `FScopedBlockMonitoringChangesForTransaction(const FScopedBlockMonitoringChangesForTransaction&) = delete;`
- L121 _public prototype_ `FScopedBlockMonitoringChangesForTransaction(FScopedBlockMonitoringChangesForTransaction&&) = delete;`
- L122 _public prototype_ `FScopedBlockMonitoringChangesForTransaction& operator=(const FScopedBlockMonitoringChangesForTransaction&) = delete;`
- L123 _public prototype_ `FScopedBlockMonitoringChangesForTransaction& operator=(FScopedBlockMonitoringChangesForTransaction&&) = delete;`
- L126 _private member_ `FUsdLevelSequenceHelperImpl& HelperImpl;`
- L127 _private member_ `bool bStoppedMonitoringChanges = false;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API USDSTAGE_API`
- L21 _namespace_ `namespace UE`
- L104 _delegate_ `DECLARE_EVENT_OneParam(FUsdLevelSequenceHelper, FOnSkelAnimationBaked, const FString& );`

### `Plugins/Importers/USDImporter/Source/USDStage/Public/USDLocatorFragments.h` (Public)


#### struct `FUsdPrimLocatorFragment`  
`struct FUsdPrimLocatorFragment`  
_L16-48_
- reflection: `USTRUCT()`
- desc: 32 Bytes (40 in-editor).
- L21 _public member_ `bool bPreferComponent = false;` — `UPROPERTY()`
- L24 _public member_ `FString PrimPath;` — `UPROPERTY()`
- L26 _public member_ `static UE::UniversalObjectLocator::TFragmentTypeHandle<FUsdPrimLocatorFragment> FragmentType;`
- L38 _public prototype_ `UE::UniversalObjectLocator::FResolveResult Resolve(const UE::UniversalObjectLocator::FResolveParams& Params) const;`
- L39 _public prototype_ `UE::UniversalObjectLocator::FInitializeResult Initialize(const UE::UniversalObjectLocator::FInitializeParams& InParams);`
- L41 _public prototype_ `void ToString(FStringBuilderBase& OutStringBuilder) const;`
- L42 _public prototype_ `UE::UniversalObjectLocator::FParseStringResult TryParseString(FStringView InString, const UE::UniversalObjectLocator::FParseStringParams& Params);`
- L44 _public prototype_ `static uint32 ComputePriority(const UObject* Object, const UObject* Context);`
- L46 _public prototype_ `static const AUsdStageActor* GetAttachParentStageActor(const UObject* Object);`
- L47 _public prototype_ `static AUsdStageActor* GetAttachParentStageActor(UObject* Object);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUsdPrimLocatorFragment> : public TStructOpsTypeTraitsBase2<FUsdPrimLocatorFragment>`  
_L51-57_
- inherits: `TStructOpsTypeTraitsBase2<FUsdPrimLocatorFragment>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L54-56_

#### Free symbols / members of external scopes

- L28 _function_ `friend uint32 GetTypeHash(const FUsdPrimLocatorFragment& A)`
- L33 _function_ `friend bool operator==(const FUsdPrimLocatorFragment& A, const FUsdPrimLocatorFragment& B)`
- L55 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anone74e0cc20103`)

### `Plugins/Importers/USDImporter/Source/USDStage/Public/USDPrimLinkCacheObject.h` (Public)


#### class `UUsdPrimLinkCache`  
`class UUsdPrimLinkCache : public UObject`  
_L24-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Minimal UObject wrapper around FUsdPrimLinkCache, since we want this to be accessible from USDSchemas which is an RTTI-enabled module, but also to be owned by an independently serializable UObject
- L29 _public prototype_ `UUsdPrimLinkCache();`
- L32 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L35 _public prototype_ `FUsdPrimLinkCache& GetInner();`
- L36 _public prototype_ `const FUsdPrimLinkCache& GetInner() const;`
- L39 _private member_ `TPimplPtr<FUsdPrimLinkCache> Impl;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API USDSTAGE_API`
- L13 _namespace_ `namespace UE`

### `Plugins/Importers/USDImporter/Source/USDStage/Public/USDPrimTwin.h` (Public)


#### class `UUsdPrimTwin`  
`class UUsdPrimTwin final : public UObject`  
_L14-84_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- desc: The Unreal equivalent (twin) of a USD prim
- L19 _public prototype_ `UUsdPrimTwin& AddChild(const FString& InPrimPath);`
- L20 _public prototype_ `void RemoveChild(const TCHAR* InPrimPath);`
- L21 _public function_ `const TMap<FString, TObjectPtr<UUsdPrimTwin>>& GetChildren() const`
- L26 _public function_ `UUsdPrimTwin* GetParent() const`
- L31 _public prototype_ `void Clear();`
- L33 _public function_ `void Iterate(TFunction<void(UUsdPrimTwin&)> Func, bool bRecursive)`
- L51 _public prototype_ `UUsdPrimTwin* Find(const FString& InPrimPath);`
- L52 _public prototype_ `UUsdPrimTwin* Find(const USceneComponent* InSceneComponent);`
- L54 _public prototype_ `USceneComponent* GetSceneComponent() const;`
- L57 _public prototype_ `void Serialize(FArchive& Ar) override;`
- L60 _public prototype_ `DECLARE_EVENT_OneParam(UUsdPrimTwin, FOnUsdPrimTwinDestroyed, const UUsdPrimTwin&);`
- L61 _public member_ `FOnUsdPrimTwinDestroyed OnDestroyed;`
- L64 _public function_ `const static FName GetChildrenPropertyName()`
- L71 _public member_ `FString PrimPath;` — `UPROPERTY()`
- L74 _public member_ `TWeakObjectPtr<class USceneComponent> SceneComponent;` — `UPROPERTY()`
- L80 _private member_ `TMap<FString, TObjectPtr<UUsdPrimTwin>> Children;` — `UPROPERTY(Transient)` — Transient as we don't want to save this to disk, but we'll implement Serialize() to duplicate this over when we're being duplicated
- L83 _private member_ `TWeakObjectPtr<UUsdPrimTwin> Parent;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L60 _delegate_ `DECLARE_EVENT_OneParam(UUsdPrimTwin, FOnUsdPrimTwinDestroyed, const UUsdPrimTwin&);`

### `Plugins/Importers/USDImporter/Source/USDStage/Public/USDStageActor.h` (Public)


#### enum `EUsdStageState`  
`enum class EUsdStageState : uint8`  
_L43-48_
- reflection: `UENUM()`
- L45 _public enumerator_ `Closed`
- L46 _public enumerator_ `Opened`
- L47 _public enumerator_ `OpenedAndLoaded`

#### class `AUsdStageActor`  
`class AUsdStageActor : public AActor`  
_L51-568_
- reflection: `UCLASS(MinimalAPI, config = USDImporter)`
- inherits: `AActor`
- L57 _public member_ `FFilePath RootLayer;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", meta = (RelativeToGameDir))`
- L63 _public member_ `EUsdStageState StageState;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", config)` — What to do with the USD Stage pointed to by RootLayer, if any
- L66 _public member_ `TObjectPtr<UUsdAssetCache3> AssetCache;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD")`
- L80 _public member_ `TObjectPtr<UUsdInfoCache> UsdInfoCache;` — `UPROPERTY(Transient, Instanced)` — 'Transient' as this shouldn't be saved and should be zero'd when loading (i.e. each stage actor should always have a unique instance). 'Instanced' or else even though this is created as a DefaultSubObject the engine will still share the same object between different stage actors in some scenarios (e.g. spawnables going into PIE), which we absolutely never want. In addition, we manually serialize this, PrimLinkCache and RootUsdTwin when going into PIE via ::Serialize (as opposed to letting the engine leave us with reset property values), as we won't LoadUsdStage() when duplicating for PIE, given that the engine will already duplicate our actor/component spawns anyway
- L83 _public member_ `TObjectPtr<UUsdPrimLinkCache> PrimLinkCache;` — `UPROPERTY(Transient, Instanced)`
- L88 _public member_ `TObjectPtr<UUsdAssetCache2> UsdAssetCache_DEPRECATED;` — `UE_DEPRECATED(5.8, "Use the 'AssetCache' Property, that uses the new AssetCache3 asset type.")` — `UPROPERTY()`
- L96 _public member_ `EUsdInitialLoadSet InitialLoadSet;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", config)`
- L99 _public member_ `EUsdInterpolationType InterpolationType;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", config)`
- L102 _public member_ `EGeometryCacheImport GeometryCacheImport;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", config)`
- L109 _public member_ `bool bUsePrimKindsForCollapsing;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", config)` — Use KindsToCollapse to determine when to collapse prim subtrees or not (defaults to enabled). Disable this if you want to prevent collapsing, or to control it manually by right-clicking on individual prims.
- L116 _public member_ `int32 KindsToCollapse;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", config, meta = (Bitmask, BitmaskEnum = "/Script/UnrealUSDWrapper.EUsdDefaultKind"))` — Whether to try to combine individual assets and components of the same type on a kind-per-kind basis, like multiple Mesh prims into a single Static Mesh
- L123 _public member_ `bool bMergeIdenticalMaterialSlots;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", config)` — If enabled, when multiple mesh prims are collapsed into a single static mesh, identical material slots are merged into one slot. Otherwise, materials slots are simply appended to the list.
- L131 _public member_ `bool bShareAssetsForIdenticalPrims;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", config)` — If true, whenever two prims would have generated identical UAssets (like identical StaticMeshes or materials) then only one instance of that asset is generated, and the asset is shared by the components generated for both prims. If false, we will always generate a dedicated asset for each prim.
- L135 _public member_ `bool bReuseIdenticalAssets_DEPRECATED;` — `UE_DEPRECATED(all, "This property has been renamed to 'Share Assets for Identical Prims'")` — `UPROPERTY()`
- L139 _public member_ `bool bCollapseTopLevelPointInstancers_DEPRECATED;` — `UE_DEPRECATED(all, "This option is now controlled via the cvar 'USD.CollapseTopLevelPointInstancers'")` — `UPROPERTY()`
- L143 _public member_ `int32 PurposesToLoad;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", config, meta = (Bitmask, BitmaskEnum = "/Script/UnrealUSDWrapper.EUsdPurpose"))` — Only load prims with these specific purposes from the USD file
- L147 _public member_ `int32 NaniteTriangleThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", config, meta = (NoSpinbox = "true", UIMin = "0", ClampMin = "0"))` — Try enabling Nanite for static meshes that are generated with at least this many triangles
- L151 _public member_ `FName RenderContext;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", config)` — Specifies which set of shaders to use when parsing USD materials, in addition to the universal render context.
- L155 _public member_ `FName MaterialPurpose;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", config)` — Specifies which material purbose to use when parsing USD material bindings, in addition to the "allPurpose" fallback.
- L159 _public member_ `EUsdRootMotionHandling RootMotionHandling;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", config)` — Describes what to add to the root bone animation within generated AnimSequences, if anything
- L163 _public member_ `EUsdCollisionType FallbackCollisionType;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", config)` — What type of collision to use for static meshes generated from Prims that don't have physics schemas applied
- L170 _public member_ `int32 SubdivisionLevel;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", config)` — Subdivision level to use for all subdivision meshes on the opened stage. 0 means "don't subdivide". The maximum level of subdivision allowed can be configured via the 'USD.Subdiv.MaxSubdivLevel' cvar.
- L174 _public member_ `FUsdMetadataImportOptions MetadataOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USD", config)` — Describes if/how we should collect metadata from USD prims onto the assets and components we generate when opening stages
- L177 _public prototype_ `DECLARE_EVENT_OneParam(AUsdStageActor, FOnActorLoaded, AUsdStageActor*);`
- L178 _public member_ `static FOnActorLoaded OnActorLoaded;`
- L180 _public prototype_ `DECLARE_EVENT(AUsdStageActor, FOnStageActorEvent);`
- L181 _public member_ `FOnStageActorEvent OnPreStageChanged;`
- L182 _public member_ `FOnStageActorEvent OnStageChanged;`
- L183 _public member_ `FOnStageActorEvent OnActorDestroyed;`
- L184 _public member_ `FOnStageActorEvent OnStageLoaded;`
- L185 _public member_ `FOnStageActorEvent OnStageUnloaded;`
- L187 _public prototype_ `DECLARE_EVENT_TwoParams(AUsdStageActor, FOnPrimChanged, const FString&, bool);`
- L188 _public member_ `FOnPrimChanged OnPrimChanged;`
- L190 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnUsdStageTimeChanged);`
- L191 _public member_ `FOnUsdStageTimeChanged OnTimeChanged;`
- L193 _public prototype_ `DECLARE_EVENT_OneParam(AUsdStageActor, FOnOpenStageEditorClicked, AUsdStageActor*);`
- L194 _public member_ `static FOnOpenStageEditorClicked OnOpenStageEditorClicked;`
- L198 _public prototype_ `void SetRootLayer(const FString& RootFilePath);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L201 _public prototype_ `void SetStageState(EUsdStageState NewStageState);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L206 _public prototype_ `void SetAssetCache(UUsdAssetCache2* NewCache);` — `UE_DEPRECATED(all, "The UUsdAssetCache2 class has been deprecated. Use UUsdAssetCache3 and call SetUsdAssetCache instead")` — `UFUNCTION()`
- L210 _public prototype_ `void SetUsdAssetCache(UUsdAssetCache3* NewCache);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L213 _public prototype_ `void SetInitialLoadSet(EUsdInitialLoadSet NewLoadSet);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L216 _public prototype_ `void SetInterpolationType(EUsdInterpolationType NewType);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L219 _public prototype_ `void SetGeometryCacheImport(EGeometryCacheImport ImportOption);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L222 _public prototype_ `void SetUsePrimKindsForCollapsing(bool bUse);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L225 _public prototype_ `void SetKindsToCollapse(int32 NewKindsToCollapse);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L228 _public prototype_ `void SetMergeIdenticalMaterialSlots(bool bMerge);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L231 _public prototype_ `void SetShareAssetsForIdenticalPrims(bool bShare);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L235 _public prototype_ `void SetReuseIdenticalAssets(bool bReuse);` — `UE_DEPRECATED(all, "Use 'SetShareAssetsForIdenticalPrims' instead.")` — `UFUNCTION()`
- L239 _public prototype_ `void SetCollapseTopLevelPointInstancers(bool bCollapse);` — `UE_DEPRECATED(all, "This option is now controlled via the cvar 'USD.CollapseTopLevelPointInstancers'")` — `UFUNCTION()`
- L242 _public prototype_ `void SetPurposesToLoad(int32 NewPurposesToLoad);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L245 _public prototype_ `void SetNaniteTriangleThreshold(int32 NewNaniteTriangleThreshold);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L248 _public prototype_ `void SetRenderContext(const FName& NewRenderContext);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L251 _public prototype_ `void SetMaterialPurpose(const FName& NewMaterialPurpose);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L254 _public prototype_ `void SetRootMotionHandling(EUsdRootMotionHandling NewHandlingStrategy);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L257 _public prototype_ `void SetFallbackCollisionType(EUsdCollisionType NewCollisionType);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L260 _public prototype_ `void SetSubdivisionLevel(int32 NewLevel);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L263 _public prototype_ `void SetCollectMetadata(bool bNewCollectValue);` — `UFUNCTION(BlueprintCallable, Category = "USD|Metadata", meta = (CallInEditor = "true"))`
- L266 _public prototype_ `void SetCollectFromEntireSubtrees(bool bNewCollectValue);` — `UFUNCTION(BlueprintCallable, Category = "USD|Metadata", meta = (CallInEditor = "true"))`
- L269 _public prototype_ `void SetCollectOnComponents(bool bNewCollectValue);` — `UFUNCTION(BlueprintCallable, Category = "USD|Metadata", meta = (CallInEditor = "true"))`
- L272 _public prototype_ `void SetBlockedPrefixFilters(const TArray<FString>& NewFilters);` — `UFUNCTION(BlueprintCallable, Category = "USD|Metadata", meta = (CallInEditor = "true"))`
- L275 _public prototype_ `void SetInvertFilters(bool bNewInvertValue);` — `UFUNCTION(BlueprintCallable, Category = "USD|Metadata", meta = (CallInEditor = "true"))`
- L278 _public prototype_ `float GetTime() const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L281 _public prototype_ `void SetTime(float InTime);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L284 _public prototype_ `ULevelSequence* GetLevelSequence() const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))`
- L295 _public prototype_ `USceneComponent* GetGeneratedComponent(const FString& PrimPath) const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Gets the transient component that was generated for a prim with a given prim path. Warning: The lifetime of the component is managed by the AUsdStageActor, and it may be force-destroyed at any time (e.g. when closing the stage) @param PrimPath - Full path to the source prim, e.g. "/root_prim/my_prim" @return The corresponding spawned component. It may correspond to a parent prim, if the prim at PrimPath was collapsed. Nullptr if path is invalid.
- L304 _public prototype_ `TArray<UObject*> GetGeneratedAssets(const FString& PrimPath) const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Gets the transient assets that were generated for a prim with a given prim path. Likely one asset (e.g. UStaticMesh), but can be multiple (USkeletalMesh, USkeleton, etc.) @param PrimPath - Full path to the source prim, e.g. "/root_prim/my_mesh" @return The corresponding generated assets. May be empty if path is invalid or if that prim led to no generated assets.
- L313 _public prototype_ `FString GetSourcePrimPath(const UObject* Object) const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Gets the path to the prim that was parsed to generate the given `Object`. @param Object - UObject to query with. Can be one of the transient components generated when a stage was opened, or something like a UStaticMesh. @return The path to the source prim, e.g. "/root_prim/some_prim". May be empty in case we couldn't find the source prim.
- L317 _public prototype_ `void NewStage();` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Creates a brand new, memory-only USD stage and opens it
- L325 _public prototype_ `void SetIsolatedRootLayer(const FString& IsolatedStageRootLayer);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — If IsolatedStageRootLayer is the identifier of one of the sublayers of the currently opened stage, this will enter isolated mode by creating a new stage with IsolatedStageRootLayer as its root, and displaying that. Provide an empty string to leave isolated mode.
- L332 _public prototype_ `FString GetIsolatedRootLayer() const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Returns the root layer identifier of the currently isolated stage if we're in isolated mode, and the empty string otherwise.
- L337 _public prototype_ `UE::FUsdStage& GetOrOpenUsdStage();` — Opens the stage with RootLayer if its not loaded already, and returns the either the isolated stage (if any) or the base stage
- L340 _public prototype_ `const UE::FUsdStage& GetUsdStage() const;` — Returns either the isolated stage (if any) or the base stage
- L343 _public prototype_ `const UE::FUsdStage& GetBaseUsdStage() const;` — Always returns the base stage, regardless of whether we have an isolated stage or not
- L346 _public prototype_ `const UE::FUsdStage& GetIsolatedUsdStage() const;` — Always returns the isolated stage, being an invalid stage in case we're not isolating anything
- L348 _public prototype_ `void SetUsdStage(const UE::FUsdStage& NewStage);`
- L354 _public prototype_ `void IsolateLayer(const UE::FSdfLayer& Layer, bool bLoadUsdStage = true);` — Enters isolated mode by creating a new USD Stage using the provided layer as its root. @param bLoadUsdStage - Whether to load assets, actors and components from the isolated stage
- L358 _public prototype_ `bool RegenerateLevelSequence();` — Creates new ULevelSequence assets for the root layer and sublayers. If we already had a previous LevelSequence opened, we will close its Sequencer and return true
- L366 _public prototype_ `void RepopulateLevelSequence();` — Fills in the current LevelSequences with animations for the prims of the opened stage. Can be called even if our current LevelSequence has already been populated: It will simply refresh the current LevelSequence, adding/removing tracks and bindings as needed.
- L368 _public prototype_ `void OpenLevelSequence();`
- L370 _public prototype_ `TSharedPtr<UE::FUsdGeomBBoxCache> GetBBoxCache();`
- L371 _public prototype_ `TMap<FString, TMap<FString, int32>> GetMaterialToPrimvarToUVIndex();`
- L372 _public prototype_ `const UsdUtils::FBlendShapeMap& GetBlendShapeMap();`
- L373 _public prototype_ `FUsdListener& GetUsdListener();`
- L374 _public prototype_ `const FUsdListener& GetUsdListener() const;`
- L377 _public prototype_ `void StopListeningToUsdNotices();` — Control whether we respond to USD notices or not. Mostly used to prevent us from responding to them when we're writing data to the stage
- L378 _public prototype_ `void ResumeListeningToUsdNotices();`
- L379 _public prototype_ `bool IsListeningToUsdNotices() const;`
- L382 _public prototype_ `void StopMonitoringLevelSequence();` — Prevents writing back data to the USD stage whenever our LevelSequences are modified
- L383 _public prototype_ `void ResumeMonitoringLevelSequence();`
- L384 _public prototype_ `void BlockMonitoringLevelSequenceForThisTransaction();`
- L387 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L388 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L389 _public prototype_ `virtual void Destroyed() override;`
- L390 _public prototype_ `virtual void PostActorCreated() override;`
- L391 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L392 _public prototype_ `virtual void BeginDestroy() override;`
- L393 _public prototype_ `virtual void PostInitProperties() override;`
- L395 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L396 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L397 _public prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;`
- L398 _public prototype_ `virtual void PreEditUndo() override;`
- L403 _public prototype_ `virtual void Reset() override;`
- L404 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L405 _public prototype_ `virtual void UnregisterAllComponents(bool bForReregister = false) override;`
- L406 _public prototype_ `virtual void PostUnregisterAllComponents() override;`
- L409 _public prototype_ `AUsdStageActor();`
- L412 _protected prototype_ `bool UnloadAssets(const UE::FSdfPath& PrimPath, bool bForEntireSubtree);`
- L415 _protected prototype_ `bool LoadAsset(FUsdSchemaTranslationContext& TranslationContext, const UE::FUsdPrim& Prim);` — Loads the asset for a single prim
- L418 _protected prototype_ `bool LoadAssets(FUsdSchemaTranslationContext& TranslationContext, const UE::FUsdPrim& StartPrim);` — Loads the assets for all prims from StartPrim and its children
- L420 _protected prototype_ `void Refresh() const;`
- L421 _protected prototype_ `void AnimatePrims();`
- L423 _protected prototype_ `UUsdPrimTwin* GetRootPrimTwin();`
- L424 _protected prototype_ `UUsdPrimTwin* GetRootPrimTwin() const;`
- L425 _protected prototype_ `UUsdPrimTwin* GetOrCreatePrimTwin(const UE::FSdfPath& UsdPrimPath);`
- L427 _protected prototype_ `UUsdPrimTwin* ExpandPrim( const UE::FUsdPrim& Prim, bool bResync, FUsdSchemaTranslationContext& TranslationContext, TOptional<bool> bParentHasAnimatedVisibility = {} );`
- L433 _protected prototype_ `void UpdatePrim(const UE::FSdfPath& UsdPrimPath, bool bResync, FUsdSchemaTranslationContext& TranslationContext);`
- L435 _protected prototype_ `void OpenUsdStage();`
- L436 _protected prototype_ `void CloseUsdStage(bool bUnloadIfNeeded = true);`
- L438 _protected prototype_ `void LoadUsdStage(bool bOpenIfNeeded = true);`
- L439 _protected prototype_ `void UnloadUsdStage();`
- L441 _protected prototype_ `void SetupAssetCacheIfNeeded();`
- L442 _protected prototype_ `void SetupBBoxCacheIfNeeded();`
- L444 _protected prototype_ `void RebuildInfoCacheFromStoredChanges();`
- L446 _protected prototype_ `bool HasAuthorityOverStage() const;`
- L448 _protected prototype_ `void UpdateSpawnedObjectsTransientFlag(bool bTransient);`
- L450 _protected prototype_ `void RequestDelayedTransactorReset();`
- L453 _protected prototype_ `void OnBeginPIE(bool bIsSimulating);`
- L454 _protected prototype_ `void OnPostPIEStarted(bool bIsSimulating);`
- L455 _protected prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ObjectReplacementMap);`
- L456 _protected prototype_ `void OnLevelActorDeleted(AActor* DeletedActor);`
- L457 _protected prototype_ `void HandleTransactionStateChanged(const FTransactionContext& InTransactionContext, const ETransactionStateEventType InTransactionState);`
- L460 _protected prototype_ `void OnPreUsdImport(FString FilePath);`
- L461 _protected prototype_ `void OnPostUsdImport(FString FilePath);`
- L462 _protected prototype_ `void OnUsdObjectsChanged(const UsdUtils::FObjectChangesByPath& InfoChanges, const UsdUtils::FObjectChangesByPath& ResyncChanges);`
- L463 _protected prototype_ `void HandleAccumulatedNotices();`
- L464 _protected prototype_ `void OnUsdPrimTwinDestroyed(const UUsdPrimTwin& UsdPrimTwin);`
- L465 _protected prototype_ `void OnObjectPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);`
- L466 _protected prototype_ `void HandlePropertyChangedEvent(FPropertyChangedEvent& PropertyChangedEvent);`
- L467 _protected prototype_ `void OnSkelAnimationBaked(const FString& SkeletonPrimPath);`
- L481 _protected member_ `TObjectPtr<class USceneComponent> SceneComponent;` — `UPROPERTY(Category = UsdStageActor, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Mesh,Rendering,Physics,Components|StaticMesh", AllowPrivateAccess = "true"))`
- L485 _protected member_ `float Time;` — `UPROPERTY(EditAnywhere, Category = "USD")` — TimeCode to evaluate the USD stage at
- L488 _protected member_ `TObjectPtr<ULevelSequence> LevelSequence;` — `UPROPERTY(VisibleAnywhere, Category = "USD", Transient)`
- L494 _protected member_ `TObjectPtr<UUsdPrimTwin> RootUsdTwin;` — `UPROPERTY(Transient, Instanced)` — c.f. UsdInfoCache UPROPERTY for property flag reasoning.
- L497 _protected member_ `TObjectPtr<UUsdTransactor> Transactor;` — `UPROPERTY(Transient, Instanced)`
- L500 _protected member_ `TSet<FString> PrimsToAnimate;` — `UPROPERTY(Transient)`
- L503 _protected member_ `TMap<TObjectPtr<UObject>, FString> ObjectsToWatch;` — `UPROPERTY(Transient)`
- L509 _protected member_ `UsdUtils::FObjectChangesByPath AccumulatedInfoChanges;` — USD can emit multiple notices within the same UE transaction. We accumulate these in here, and respond to them only once, when the transaction is about to finish
- L510 _protected member_ `UsdUtils::FObjectChangesByPath AccumulatedResyncChanges;`
- L511 _protected member_ `bool bLayerReloaded = false;`
- L512 _protected member_ `TArray<UE::FSdfPath> ResyncedPrimsForThisTransaction;`
- L516 _protected member_ `TSharedPtr<FUsdInfoCache> InfoCache;` — Caches various information about prims that are expensive to query
- L520 _protected member_ `TSharedPtr<UE::FUsdGeomBBoxCache> BBoxCache;` — USD bounding box cache for the stage. Constructed on-demand
- L522 _protected member_ `FUsdListener UsdListener;`
- L524 _protected member_ `FUsdLevelSequenceHelper LevelSequenceHelper;`
- L527 _protected member_ `UE::FUsdStage UsdStage;` — The main UsdStage that is currently opened
- L531 _protected member_ `UE::FUsdStage IsolatedStage;` — Another stage that has as root layer one of the non-root local layers of UsdStage. This is the stage we'll be displaying if it is valid, otherwise we'll be displaying UsdStage directly.
- L534 _protected member_ `UsdUtils::FBlendShapeMap BlendShapesByPath;` — Keep track of blend shapes so that we can map 'inbetween shapes' to their separate morph targets when animating
- L540 _protected member_ `TMap<FString, TMap<FString, int32>> MaterialToPrimvarToUVIndex;` — When parsing materials, we keep track of which primvar we mapped to which UV channel. When parsing meshes later, we use this data to place the correct primvar values in each UV channel. We keep this here as these are generated when the materials stored in AssetsCache are parsed, so it should accompany them
- L550 _protected member_ `bool bIsTransitioningIntoPIE;` — We use PostRegisterAllComponents and PostUnregisterAllComponents as main entry points to decide when to load/unload the USD stage. These are the three exceptions we must avoid though: - We don't want to load/unload when duplicating into PIE as we want our duplicated actors/components to go with us; - On the editor, the register/unregister functions are called from AActor::PostEditChangeProperty, and we obviously don't want to load/unload the stage on every single property edit. - We never want to load/unload actors and components on undo/redo: We always want to fetch them from the transaction buffer
- L551 _protected member_ `bool bIsModifyingAProperty;`
- L552 _protected member_ `bool bIsUndoRedoing;`
- L553 _protected member_ `bool bIsAddingBinding = false;`
- L554 _protected member_ `bool bIsPendingTransactorReset = false;`
- L556 _protected member_ `FDelegateHandle OnRedoHandle;`
- L557 _protected member_ `FDelegateHandle OnSequencerCreatedHandle;`
- L559 _protected member_ `FThreadSafeCounter IsBlockedFromUsdNotices;`
- L567 _protected member_ `FFilePath OldRootLayer;` — Helps us know whether a transaction changed our RootLayer or not. We need this because we can only tag spawned transient actors and components after the initial actor/component spawning transaction has completed. Otherwise, the spawns will be replicated on each client in addition to the actors/components that they will spawn by themselves for opening the stage

#### class `FScopedBlockNoticeListening`  
`class FScopedBlockNoticeListening final`  
_L570-584_
- L573 _public prototype_ `explicit FScopedBlockNoticeListening(AUsdStageActor* InStageActor);`
- L574 _public prototype_ `~FScopedBlockNoticeListening();`
- L576 _public prototype_ `FScopedBlockNoticeListening() = delete;`
- L577 _public prototype_ `FScopedBlockNoticeListening(const FScopedBlockNoticeListening&) = delete;`
- L578 _public prototype_ `FScopedBlockNoticeListening(FScopedBlockNoticeListening&&) = delete;`
- L579 _public prototype_ `FScopedBlockNoticeListening& operator=(const FScopedBlockNoticeListening&) = delete;`
- L580 _public prototype_ `FScopedBlockNoticeListening& operator=(FScopedBlockNoticeListening&&) = delete;`
- L583 _private member_ `TWeakObjectPtr<AUsdStageActor> StageActor;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API USDSTAGE_API`
- L32 _namespace_ `namespace UE`
- L37 _namespace_ `namespace UsdUtils`
- L177 _delegate_ `DECLARE_EVENT_OneParam(AUsdStageActor, FOnActorLoaded, AUsdStageActor*);`
- L180 _delegate_ `DECLARE_EVENT(AUsdStageActor, FOnStageActorEvent);`
- L187 _delegate_ `DECLARE_EVENT_TwoParams(AUsdStageActor, FOnPrimChanged, const FString&, bool);`
- L190 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnUsdStageTimeChanged);`
- L193 _delegate_ `DECLARE_EVENT_OneParam(AUsdStageActor, FOnOpenStageEditorClicked, AUsdStageActor*);`

### `Plugins/Importers/USDImporter/Source/USDStage/Public/USDStageModule.h` (Public)


#### class `IUsdStageModule`  
`class IUsdStageModule : public IModuleInterface`  
_L13-22_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual AUsdStageActor& GetUsdStageActor(UWorld* World) = 0;`
- L17 _public prototype_ `virtual AUsdStageActor* FindUsdStageActor(UWorld* World) = 0;`
- L20 _public prototype_ `virtual const TArray<TWeakPtr<ISequencer>>& GetExistingSequencers() const = 0;`

### `Plugins/Importers/USDImporter/Source/USDStage/Public/USDTransactor.h` (Public)


#### class `UUsdTransactor`  
`class UUsdTransactor : public UObject`  
_L42-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Class that allows us to log prim attribute changes into the unreal transaction buffer. The AUsdStageActor owns one of these, and whenever a USD notice is fired this class transacts and serializes the notice data with itself. When undo/redoing it applies its values to the AUsdStageActors' current stage. Additionally this class naturally allows multi-user (ConcertSync) support for USD stage interactions, by letting these notice data to be mirrored on other clients.
- L48 _public prototype_ `UUsdTransactor();` — Boilerplate for Pimpl usage with UObject
- L49 _public prototype_ `UUsdTransactor(FVTableHelper& Helper);`
- L50 _public prototype_ `~UUsdTransactor();`
- L52 _public prototype_ `void Initialize(AUsdStageActor* InStageActor);`
- L53 _public prototype_ `void Update(const UsdUtils::FObjectChangesByPath& NewInfoChanges, const UsdUtils::FObjectChangesByPath& NewResyncChanges);`
- L56 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L58 _public prototype_ `virtual void PreEditUndo();`
- L59 _public prototype_ `virtual void PostEditUndo();`
- L64 _private member_ `TWeakObjectPtr<AUsdStageActor> StageActor;`
- L66 _private member_ `TUniquePtr<UsdUtils::FUsdTransactorImpl> Impl;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API USDSTAGE_API`
- L16 _namespace_ `namespace UsdUtils`
- L21 _typedef_ `using FObjectChangesByPath = TCaseSensitiveStringMap<TArray<FSdfChangeListEntry>>;` (scope `UsdUtils`)
- L24 _namespace_ `namespace UE`
- L26 _namespace_ `namespace UsdTransactor` (scope `UE`)
- L29 _externvar_ `extern const FName ConcertSyncEnableTag;` (scope `UE::UsdTransactor`) — Actors and components cleared to be transacted by ConcertSync even if they are transient will receive this tag
