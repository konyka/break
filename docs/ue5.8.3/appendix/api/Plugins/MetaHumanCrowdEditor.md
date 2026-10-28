# Plugins / MetaHumanCrowdEditor

- module root: `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowdEditor`
- headers: 14; symbols: 217
- symbol kinds: class=7, delegate=1, enum=3, enumerator=9, function=1, member=116, namespace=15, prototype=48, struct=16, variable=1
- PrivateDependencyModuleNames: AssetTools, ContentBrowser, Slate, SlateCore, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: AnimationBlueprintLibrary, ChaosClothAssetEngine, ChaosOutfitAssetEngine, Core, CoreUObject, DNACalibModule, DataflowEngine, DerivedDataCache, Engine, HairStrandsCore, ImageCore, MeshBoneReduction, MeshDescription, MetaHumanCharacter, MetaHumanCharacterEditor, MetaHumanCharacterPalette, MetaHumanCharacterPaletteEditor, MetaHumanCrowd, MetaHumanDefaultEditorPipeline, MetaHumanDefaultPipeline, RHI, RigLogicModule, SkeletalMeshDescription, SkeletalMeshModifiers, SkeletalMeshUtilitiesCommon, StaticMeshDescription

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowdEditor/Private/MetaHumanCrowdBodyMerge.h` (Private)


#### struct `UE::MetaHuman::CrowdBodyMerge::FSlotItemData`  
`struct FSlotItemData`  
_L16-27_
- desc: Data for a single outfit item within a slot, including its per-body geometry bundles and face map.
- L20 _public member_ `TMap<FMetaHumanPaletteItemKey, FMetaHumanCrowdMeshGeometryBundle*> BodyToOutfitGeometryMap;` — Map from body item key to the fitted outfit geometry bundle for this item. Bundles are modified in place -- body geometry is appended to them.
- L23 _public member_ `GeometryRemoval::FHiddenFaceMapImage BodyHiddenFaceMapImage;` — The body hidden face map image for this outfit item (CPU-side).
- L26 _public member_ `bool bHasValidFaceMap = false;` — Whether this item has a valid body hidden face map.

#### struct `UE::MetaHuman::CrowdBodyMerge::FSlotData`  
`struct FSlotData`  
_L30-43_
- desc: Data for a single clothing slot (virtual slot), which may contain multiple outfit items.
- L33 _public member_ `FName VirtualSlotName;` — The virtual slot name (e.g. "Top Garment").
- L36 _public member_ `TArray<FSlotItemData> Items;` — All outfit items that belong to this slot.
- L39 _public member_ `TMap<FName, float> MaxBoneWeights;` — Max bone weight observed per bone name for vertices owned by this slot.
- L42 _public member_ `FLinearColor SlotColor = FLinearColor::White;` — Color used for debug visualization of this slot.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MetaHuman` (scope `UE`)
- L11 _namespace_ `namespace CrowdBodyMerge` (scope `UE::MetaHuman`)
- L13 _variable_ `static constexpr uint8 UnclaimedSlotIndex = MAX_uint8;` (scope `UE::MetaHuman::CrowdBodyMerge`)
- L56 _prototype_ `void MergeBodyOntoOutfits( const TMap<FMetaHumanPaletteItemKey, FMetaHumanCrowdMeshGeometryBundle*>& BodyGeometryBundles, TArray<FSlotData>& Slots, TConstArrayView<int32> LODIndicesToProcess, const USkeleton* TargetSkeleton, const FString& DebugImagePath = FString());` (scope `UE::MetaHuman::CrowdBodyMerge`) — Merges body geometry onto fitted outfit geometry bundles so that visible parts of the body (arms, hands, etc.) are rendered as part of the clothing mesh instead of a separate body mesh. @param BodyGeometryBundles  Map from body item key to the body geometry bundle. @param Slots                Array of slot data (one per virtual slot with face maps). Modified in place. @param LODIndicesToProcess  The union of actor and instanced body LOD indices to process. @param TargetSkeleton       The shared skeleton all meshes will be rebound to. @param DebugImagePath       If non-empty and the debug cvar is enabled, writes a debug PNG of the ownership bitmap to this path.

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowdEditor/Private/MetaHumanCrowdEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCrowdEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCrowdEditor, Log, All);`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowdEditor/Private/MetaHumanCrowdEditorPipelineLocals.h` (Private)


#### struct `FMetaHumanCrowdDeferredItemBuild`  
`struct FMetaHumanCrowdDeferredItemBuild`  
_L25-37_
- reflection: `USTRUCT()`
- desc: An item-pipeline build result held temporarily by the collection editor pipeline so that its contents (geometry bundles, hidden face maps, etc.) can be consumed during later build phases, then transformed into the collection-level build output and integrated into the main built data.
- L32 _public member_ `FName SlotName;` — `UPROPERTY()` — The virtual slot that owns this item (passed to IntegrateItemBuiltData later).
- L36 _public member_ `FMetaHumanPaletteBuiltData BuiltData;` — `UPROPERTY()` — The raw item-pipeline built data, containing e.g. FMetaHumanCrowdOutfitBuildOutput.

#### struct `FMetaHumanCrowdBakedAnimEntry`  
`struct FMetaHumanCrowdBakedAnimEntry`  
_L43-55_
- reflection: `USTRUCT()`
- desc: A bake-config entry paired with the merged UAnimSequence it produced.
- L50 _public member_ `FMetaHumanCrowdBakeAnimationData Config;` — `UPROPERTY()` — Source bake config that drove the merge.
- L54 _public member_ `TObjectPtr<UAnimSequence> AnimSequence;` — `UPROPERTY()` — Merged animation produced for this entry.

#### struct `FMetaHumanCrowdEditorPipelineLocals`  
`struct FMetaHumanCrowdEditorPipelineLocals`  
_L58-98_
- reflection: `USTRUCT()`
- L64 _public member_ `TMap<FMetaHumanPaletteItemKey, FMetaHumanCrowdOutfitFitTarget> OutfitFitTargets;` — `UPROPERTY()`
- L67 _public member_ `TMap<FMetaHumanPaletteItemKey, FMetaHumanCrowdGroomFitTarget> HeadGroomFitTargets;` — `UPROPERTY()`
- L71 _public member_ `TMap<FMetaHumanPaletteItemPath, FMetaHumanCrowdDeferredItemBuild> DeferredOutfitBuilds;` — `UPROPERTY()` — Outfit item pipeline build results, held until transformed into collection-level outputs.
- L75 _public member_ `TMap<FMetaHumanPaletteItemPath, FMetaHumanCrowdDeferredItemBuild> DeferredGroomBuilds;` — `UPROPERTY()` — Groom item pipeline build results, held until transformed into collection-level outputs.
- L82 _public member_ `TMap<FMetaHumanPaletteItemKey, FMetaHumanCrowdCharacterBuildOutput> HeadCharacterBuildOutputs;` — `UPROPERTY()` — Head character-pipeline build outputs, held until the collection-level head build output is synthesised and integrated at the end of the build. Keyed by head item key.
- L89 _public member_ `TMap<FMetaHumanPaletteItemKey, FMetaHumanCrowdCharacterBuildOutput> BodyCharacterBuildOutputs;` — `UPROPERTY()` — Body character-pipeline build outputs, held until the collection-level body build output is synthesised and integrated at the end of the build. Keyed by body item key.
- L93 _public member_ `TMap<FName, FMetaHumanCrowdBakedAnimEntry> AnimSequencePerEntry;` — `UPROPERTY()` — Merged animation cache keyed by config entry name.
- L97 _public member_ `TMap<FName, TObjectPtr<const UMetaHumanItemPipeline>> DefaultPipelinesByClass;` — `UPROPERTY()` — Default pipelines for any items that don't have a pipeline

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowdEditor/Private/MetaHumanCrowdEditorUtilities.h` (Private)


#### struct `UE::MetaHuman::CrowdEditorUtilities::FMeshConstructionParams`  
`struct FMeshConstructionParams`  
_L118-184_
- desc: Parameters for constructing a USkeletalMesh from a geometry bundle.
- L121 _public member_ `TArray<int32> LODsToKeep;` — Which LOD indices to extract from the geometry bundle.
- L124 _public member_ `USkeleton* TargetSkeleton = nullptr;` — Skeleton to rebind to. Required.
- L127 _public member_ `bool bEnableNanite = false;` — If true, enable Nanite rendering (replaces unsupported materials).
- L130 _public member_ `bool bOptimizeForInstancing = false;` — If true, set bOptimizeForInstancing on all LODs.
- L133 _public member_ `int32 BoneInfluenceLimit = 0;` — If > 0, set BoneInfluenceLimit on all LOD build settings.
- L136 _public member_ `TArray<FName> SectionsToRemove;` — Material slot names whose sections should be removed entirely.
- L144 _public member_ `TArray<FName> ForceKeepBoneNames;` — Bones to keep in the pruned skeleton even if no vertices are weighted to them. Their ancestor chain up to the skeleton root is also preserved. Use for bones the runtime animation references (e.g. head/neck_01/neck_02 on a body mesh) so ISKM and ABP playback agree on world-space bone positions.
- L147 _public member_ `TArray<FName> SectionsToDisableShadow;` — Material slot names whose sections should have shadow casting disabled.
- L150 _public member_ `bool bRemoveTranslucentSections = false;` — If true, remove any section whose material has a translucent blend mode.
- L153 _public member_ `bool bPreserveDNA = false;` — If true, preserve DNA from SourceDNAMesh (copy UDNAAssetUserData and calibrate LODs).
- L156 _public member_ `USkeletalMesh* SourceDNAMesh = nullptr;` — Source mesh to copy DNA from (only used when bPreserveDNA is true).
- L162 _public member_ `const FReferenceSkeleton* AlignmentRefSkeleton = nullptr;` — Optional reference skeleton to align the constructed mesh's body chain against. The chain ending at AlignmentBoneName has its local ref-pose transforms overwritten from this skeleton.
- L165 _public member_ `FName AlignmentBoneName = NAME_None;` — Optional leaf bone of the chain to align. Walks parents from this bone up to the root.
- L168 _public member_ `TArray<FPerPlatformFloat> ScreenSizes;` — LOD screen size thresholds
- L171 _public member_ `float ScreenSizeScaleFactor = 1.0f;` — Uniform multiplier applied to every ScreenSizes entry.
- L181 _public member_ `int32 RecomputeTangentsLODIndexThreshold = -1;` — Recompute Tangents is enabled on every section whose material slot name appears in RecomputeTangentsMaterialSlotNames, on every LOD whose index is <= RecomputeTangentsLODIndexThreshold. SkinCacheUsage is forced to Enabled on any LOD where at least one matching section was found.
- L182 _public member_ `TArray<FName> RecomputeTangentsMaterialSlotNames;`
- L183 _public member_ `ESkinVertexColorChannel RecomputeTangentsVertexMaskChannel = ESkinVertexColorChannel::Green;`

#### class `UE::MetaHuman::CrowdEditorUtilities::FScopedSkeletalMeshChange`  
`class FScopedSkeletalMeshChange`  
_L253-271_
- desc: RAII scope that wraps the engine's FScopedSkeletalMeshPostEditChange and, immediately before the wrapped scope destructs and triggers the mesh build, calls ApplyContentAddressableSkelMeshGuid on the mesh to ensure a deterministic SkeletalMeshModelGUID is set prior to the DDC key being computed.
- L256 _public prototype_ `explicit FScopedSkeletalMeshChange(TNotNull<USkeletalMesh*> InMesh);`
- L257 _public prototype_ `~FScopedSkeletalMeshChange();`
- L259 _public prototype_ `FScopedSkeletalMeshChange(const FScopedSkeletalMeshChange&) = delete;`
- L260 _public prototype_ `FScopedSkeletalMeshChange& operator=(const FScopedSkeletalMeshChange&) = delete;`
- L261 _public prototype_ `FScopedSkeletalMeshChange(FScopedSkeletalMeshChange&&) = delete;`
- L262 _public prototype_ `FScopedSkeletalMeshChange& operator=(FScopedSkeletalMeshChange&&) = delete;`
- L265 _private member_ `TNotNull<USkeletalMesh*> Mesh;`
- L270 _private member_ `FScopedSkeletalMeshPostEditChange EngineScope;` — Declared last so its destructor runs after our destructor body applies the GUID. The engine scope's destructor is what actually triggers PostEditChange / the build when the outermost scope exits.

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MetaHuman` (scope `UE`)
- L21 _namespace_ `namespace CrowdEditorUtilities` (scope `UE::MetaHuman`)
- L26 _prototype_ `void SafeEnableNanite(TNotNull<USkeletalMesh*> Mesh);` (scope `UE::MetaHuman::CrowdEditorUtilities`) — Enables Nanite on a mesh, changing any settings necessary to ensure it will render correctly.
- L33 _prototype_ `void ApplyMinLODToMesh(USkeletalMesh* Mesh, const FPerPlatformInt& MinLOD, const FPerQualityLevelInt& QualityLevelMinLOD);` (scope `UE::MetaHuman::CrowdEditorUtilities`) — Applies per-platform and per-quality-level MinLOD to a skeletal mesh. Values are clamped to the valid range [0, GetLODNum() - 1] before being written to the asset.
- L36 _prototype_ `void RemoveUnusedBones(TNotNull<USkeletalMesh*> Mesh);` (scope `UE::MetaHuman::CrowdEditorUtilities`) — Remove unskinned bones to reduce animation cost
- L39 _prototype_ `void SetOptimizeForInstancing(TNotNull<USkeletalMesh*> Mesh);` (scope `UE::MetaHuman::CrowdEditorUtilities`) — Set bOptimizeForInstancing on all LODs so the mesh works efficiently with ISMKs
- L50 _prototype_ `bool TryRebindToSkeleton(TNotNull<USkeletalMesh*> Mesh, TNotNull<USkeleton*> NewSkeleton);` (scope `UE::MetaHuman::CrowdEditorUtilities`) — Rebind a skeletal mesh to a different skeleton. For each LOD, skin weights on bones that do not exist in the new skeleton are redistributed to the nearest surviving ancestor bone. The mesh's reference skeleton is then rebuilt to match the new skeleton and the skeleton pointer is updated. @param Mesh			The skeletal mesh to rebind. @param NewSkeleton	The target skeleton. Must share at least one bone with the mesh. @return true if the rebind succeeded, false otherwise.
- L79 _prototype_ `UAnimSequence* BakeAnimation( TNotNull<UAnimSequence*> SourceAnim, TNotNull<USkeletalMesh*> TargetMesh, TObjectPtr<UAnimBoneCompressionSettings> BoneCompressionSettingsOverride, const FString& AnimAssetName, UObject* Outer, FName FaceRootBoneName = NAME_None);` (scope `UE::MetaHuman::CrowdEditorUtilities`) — Bake a source animation (bone tracks + float curves) through TargetMesh's post-process ABP. Per-frame evaluation drives the source animation through the mesh's post-process ABP (e.g. RigLogic) to produce final bone transforms. Output bone tracks for the strict descendants of FaceRootBoneName come from the baked head mesh pose (so RigLogic-driven facial bones are captured correctly). Tracks for all other bones - including FaceRootBoneName itself - are copied verbatim from the source animation. The face root bone is intentionally excluded from the bake so any body-driven head motion in the source survives untouched. The head mesh component only produces component-space transforms for bones it has skin weights on, so body bones aren't in its evaluated pose and must come from the source instead. @param SourceAnim		Source animation; may carry bone tracks, float curves, or both. @param TargetMesh		Mesh whose post-process ABP drives the bake (typically the head mesh). @param BoneCompressionSettingsOverride Optional override for the output anim's BoneCompressionSettings. If null, the engine's default animation-recorder preset is used. @param AnimAssetName		Name of the output UAnimSequence asset. @param Outer				Outer object for the new UAnimSequence. @param FaceRootBoneName	Strict descendants of this bone come from the baked head pose; the bone itself and everything outside the sub-tree pass through from the source animation. If NAME_None, every bone present in the head mesh comes fr
- L108 _prototype_ `UAnimSequence* MergeAnimations( UAnimSequence* FaceAnim, UAnimSequence* BodyAnim, TNotNull<USkeleton*> TargetSkeleton, TObjectPtr<UAnimBoneCompressionSettings> BoneCompressionSettingsOverride, const FString& AnimAssetName, UObject* Outer, FName FaceRootBoneName = NAME_None);` (scope `UE::MetaHuman::CrowdEditorUtilities`) — Merge a baked face animation and/or a raw body animation into a single UAnimSequence on TargetSkeleton. Face bone tracks (filtered to FaceRootBoneName and its children when set) take priority over body bone tracks for any shared bones. Cases handled: FaceAnim + BodyAnim  -> face bone tracks + body bone tracks FaceAnim only        -> face bone tracks only; body bone tracks omitted BodyAnim only        -> body bone tracks only; face bone tracks omitted @param FaceAnim			Optional pre-baked face animation (from BakeAnimation). @param BodyAnim			Optional raw body animation. @param TargetSkeleton	The merged skeleton covering all bones. @param BoneCompressionSettingsOverride Optional override for the output anim's BoneCompressionSettings. If null, the engine's default animation-recorder preset is used. @param AnimAssetName		Name of the output UAnimSequence asset. @param Outer				Outer object for the new UAnimSequence. @param FaceRootBoneName	If set, only face tracks from this bone and its children are used. @return					The merged UAnimSequence, or nullptr on failure.
- L199 _prototype_ `USkeletalMesh* ConstructMeshFromBundle( const FMetaHumanCrowdMeshGeometryBundle& Bundle, const FMeshConstructionParams& Params, UObject* Outer, FName MeshName = NAME_None);` (scope `UE::MetaHuman::CrowdEditorUtilities`) — Constructs a USkeletalMesh from a geometry bundle with the given parameters. Selects LODs, prunes the RefSkeleton to only referenced bones, initialises from MeshDescriptions, rebinds to TargetSkeleton, and applies post-processing (Nanite, instancing, bone limits, section removal, DNA preservation). @param Bundle	The geometry bundle to construct from. @param Params	Construction parameters. @param Outer		Outer object for the new mesh. @param MeshName	Optional name for the new mesh. @return The constructed mesh, or nullptr on failure.
- L214 _prototype_ `void ExtractGeometryBundle( TNotNull<const USkeletalMesh*> Mesh, FMetaHumanCrowdMeshGeometryBundle& OutBundle);` (scope `UE::MetaHuman::CrowdEditorUtilities`) — Extracts a geometry bundle from an existing USkeletalMesh by reading all LODs' MeshDescriptions, the RefSkeleton, the Materials array, and the per-LOD material maps. MeshDescription polygon group slot names are preserved as imported (they may be raw FBX names that do not match the canonical MaterialSlotName of the section's actual material). Consumers should use LODMaterialMaps to resolve each PG to its Materials index via ResolveBundleMaterialIndex.
- L228 _prototype_ `int32 ResolveBundleMaterialIndex( const FMetaHumanCrowdMeshGeometryBundle& Bundle, int32 LODIndex, int32 PGIndex);` (scope `UE::MetaHuman::CrowdEditorUtilities`) — Resolve a polygon-group index in Bundle.MeshDescriptions[LODIndex] to an index into Bundle.Materials. Mirrors the engine's render-time material resolution: LODMaterialMap[SectionIdx] with identity fallback when the map is empty or INDEX_NONE. The engine sets Face.MatIndex = PolygonGroupID.GetValue() (see FSkeletalMeshImportData::CreateFromMeshDescription), so for any MeshDescription produced by ExtractGeometryBundle, PG index == the source section index that LODMaterialMap is indexed by.
- L245 _prototype_ `void ApplyContentAddressableSkelMeshGuid(TNotNull<USkeletalMesh*> Mesh);` (scope `UE::MetaHuman::CrowdEditorUtilities`) — Write a content-addressable GUID into the mesh's FSkeletalMeshModel::SkeletalMeshModelGUID, so identical mesh state converges to the same DDC key, for the properties that the Crowd pipeline cares about. This shouldn't be used in a generic engine context. Maximises DDC hits for redundant invalidations, reverts, and across machines arriving at the same state, while still forcing a miss whenever any hashed input changes. Must be called AFTER any edits to Materials/LODMaterialMap and BEFORE PostEditChange triggers the build, so that FSkeletalMeshRenderData::Cache computes the new key before the DDC fetch. No-op if Mesh->GetImportedModel() is null.
- L293 _prototype_ `UAnimSequence* CopyAnimationCurves( TNotNull<UAnimSequence*> FaceAnim, TNotNull<UAnimSequence*> BodyAnim, TNotNull<USkeleton*> TargetSkeleton, TObjectPtr<UAnimBoneCompressionSettings> BoneCompressionSettingsOverride, const FString& AnimAssetName, UObject* Outer);` (scope `UE::MetaHuman::CrowdEditorUtilities`) — Combine a body animation's bone tracks with a face animation's float curves into a single UAnimSequence on TargetSkeleton. Body bone tracks are copied verbatim (no rest-pose rebase); face float curves are layered on top. Bone tracks from FaceAnim and float curves from BodyAnim are ignored. Intended for pipelines where face motion is driven by curves (e.g. RigLogic) rather than explicit face bone tracks, so the output can be evaluated on a mesh whose post-process ABP consumes those curves. @param FaceAnim			Animation whose float curves should be copied. @param BodyAnim			Animation whose bone tracks should be copied (and used as length/rate). @param TargetSkeleton	The merged skeleton covering all bones. @param BoneCompressionSettingsOverride Optional override for the output anim's BoneCompressionSettings. If null, the engine's default animation-recorder preset is used. @param AnimAssetName		Name of the output UAnimSequence asset. @param Outer				Outer object for the new UAnimSequence. @return					The combined UAnimSequence, or nullptr on failure.

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowdEditor/Private/MetaHumanCrowdMaterialEditorUtils.h` (Private)


#### enum `UE::MetaHuman::CrowdMaterialEditorUtils::EFaceMeshVariant`  
`enum class EFaceMeshVariant : uint8`  
_L35-39_
- desc: Which face-mesh variant a material-override pass is targeting. Selects which of the override's Actor/Instanced soft material pointers wins, and drives generated MIC names.
- L37 _public enumerator_ `Actor`
- L38 _public enumerator_ `Instanced`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MetaHuman` (scope `UE`)
- L14 _namespace_ `namespace CrowdMaterialEditorUtils` (scope `UE::MetaHuman`)
- L26 _prototype_ `void BuildSlotSourceLODsMap( TNotNull<USkeletalMesh*> InMesh, TConstArrayView<int32> InVariantSourceLODs, TMap<FName, FMetaHumanCrowdFaceSlotLODs>& OutSlotToSourceLODs);` (scope `UE::MetaHuman::CrowdMaterialEditorUtils`) — Walks InMesh's imported model and produces a per-slot list of source-LOD indices the slot covers. InVariantSourceLODs maps each output-LOD index in InMesh to the source-LOD index the build picked for it (e.g. for a list of {4, 6}, output LOD 0 -> source LOD 4 and output LOD 1 -> source LOD 6). The map is consumed at assembly time to decide whether a per-slot parameter binding applies to a given MID: a slot whose source-LOD coverage doesn't intersect the binding's applicable LODs is skipped to avoid writing overrides on unrelated LODs.
- L51 _prototype_ `void ApplySlotMaterialOverrides( TNotNull<USkeletalMesh*> InMesh, const TArray<FMetaHumanCrowdFaceMaterialOverride>& InOverrides, const FString& InMICNamePrefix, const FString& InAssetName, EFaceMeshVariant InVariant, UObject* InOuter);` (scope `UE::MetaHuman::CrowdMaterialEditorUtils`) — Replaces material slots on InMesh whose name matches an entry in InOverrides with a fresh UMaterialInstanceConstant parented to the override material. Scalar, vector and texture parameters are copied from the existing slot MIC so any per-character data (e.g. synthesised textures, makeup tweaks) survives the swap. Slots without a matching override, or whose entry has a null Material, are left untouched. The new MIC is named "MI_{InMICNamePrefix}_{InAssetName}_{SlotName}_{VariantSuffix}", where VariantSuffix is "Actor" or "Inst" derived from InVariant.
- L68 _prototype_ `void ApplyMaskAtHighLODs( TNotNull<USkeletalMesh*> InMesh, TConstArrayView<int32> InVariantSourceLODs, int32 InMinLOD, UMaterialInterface* InMaskMaterial);` (scope `UE::MetaHuman::CrowdMaterialEditorUtils`) — Replaces material slots on InMesh with InMaskMaterial when the slot is only referenced by source LODs >= InMinLOD. Geometry still renders, but the mask material produces no visible output (transparent/masked), letting another renderer take over those LODs without competing geometry. InVariantSourceLODs maps output-LOD index -> source LOD index, matching the order ConstructMeshFromBundle consumed when building InMesh.

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowdEditor/Private/MetaHumanCrowdSkeletonPickerDialog.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MetaHuman` (scope `UE`)
- L10 _namespace_ `namespace CrowdEditor` (scope `UE::MetaHuman`)
- L22 _prototype_ `bool PromptForTargetSkeleton(USkeleton* TemplateSkeleton, const FString& DefaultCreatePath, USkeleton*& OutSkeleton);` (scope `UE::MetaHuman::CrowdEditor`) — Prompt the user to either select an existing skeleton or create a new one duplicated from the given template skeleton. @param TemplateSkeleton  The template to duplicate when the user chooses "create new" @param DefaultCreatePath Optional long package path used as the default location in the "create new" save asset dialog @param OutSkeleton       On success, set to the chosen / created skeleton. @return true if the user chose or created a satisfactory skeleton.
- L32 _prototype_ `bool PromptToAddCompatibleSkeletons( TNotNull<const UMetaHumanCollection*> Collection, USkeleton* TargetSkeleton, const TArray<USkeleton*>& SkeletonsToConsider);` (scope `UE::MetaHuman::CrowdEditor`) — Prompt the user to add a list of skeletons to TargetSkeleton's CompatibleSkeletons list. @param Collection          The Collection being built, for logging purposes. @param TargetSkeleton      The skeleton being prepared for use by the pipeline. @param SkeletonsToConsider Candidate skeletons to add. Duplicates and nulls are tolerated. @return true if the user agreed (or there was nothing to do); false if the user cancelled.

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowdEditor/Private/MetaHumanHashUtilities.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MetaHuman` (scope `UE`)
- L11 _namespace_ `namespace HashUtilities` (scope `UE::MetaHuman`)
- L20 _prototype_ `FIoHash HashUObject(TNotNull<const UObject*> Object, bool bLogDetails = false);` (scope `UE::MetaHuman::HashUtilities`) — Hashes state of a UObject via its Serialize path. @param Object		The object to hash. @param bLogDetails	If true, log the object name, serialized byte count, and hash. Additional diagnostics are controlled by the MetaHuman.Crowd.HashDiagnostics cvar.
- L30 _prototype_ `FIoHash HashUStruct(TNotNull<const UScriptStruct*> Struct, TNotNull<const void*> StructData, bool bLogDetails = false);` (scope `UE::MetaHuman::HashUtilities`) — Hashes state of a USTRUCT instance via UStruct::SerializeItem. @param Struct		The UScriptStruct describing the struct type. @param StructData	Pointer to the struct instance data. @param bLogDetails	If true, log the struct name, serialized byte count, and hash. Additional diagnostics are controlled by the MetaHuman.Crowd.HashDiagnostics cvar.

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowdEditor/Public/Item/MetaHumanCrowdCharacterEditorPipeline.h` (Public)


#### enum `EMetaHumanCrowdCharacterMeshRequirement`  
`enum class EMetaHumanCrowdCharacterMeshRequirement : uint8`  
_L13-25_
- reflection: `UENUM()`
- L16 _public enumerator_ `NotNeeded` — The mesh is not needed and will not be generated.
- L20 _public enumerator_ `ReadOnly` — The mesh is needed but will not be modified by the caller. Pre-built meshes can be passed through without duplication.
- L24 _public enumerator_ `Modifiable` — The mesh is needed and may be modified by the caller. Pre-built meshes will be duplicated so the original is not affected.

#### struct `FMetaHumanCrowdCharacterBuildInput`  
`struct FMetaHumanCrowdCharacterBuildInput`  
_L28-44_
- reflection: `USTRUCT()`
- L34 _public member_ `EMetaHumanCrowdCharacterMeshRequirement FaceMeshRequirement = EMetaHumanCrowdCharacterMeshRequirement::Modifiable;` — `UPROPERTY()`
- L37 _public member_ `EMetaHumanCrowdCharacterMeshRequirement BodyMeshRequirement = EMetaHumanCrowdCharacterMeshRequirement::Modifiable;` — `UPROPERTY()`
- L40 _public member_ `EMetaHumanCrowdCharacterMeshRequirement MergedHeadAndBodyMeshRequirement = EMetaHumanCrowdCharacterMeshRequirement::NotNeeded;` — `UPROPERTY()`
- L43 _public member_ `bool bGenerateBodyMeasurements = false;` — `UPROPERTY()`

#### class `UMetaHumanCrowdCharacterEditorPipeline`  
`class UMetaHumanCrowdCharacterEditorPipeline : public UMetaHumanItemEditorPipeline`  
_L47-90_
- reflection: `UCLASS(EditInlineNew)`
- inherits: `UMetaHumanItemEditorPipeline`
- L52 _public prototype_ `UMetaHumanCrowdCharacterEditorPipeline();`
- L54 _public prototype_ `virtual UE::Tasks::TTask<FMetaHumanPaletteBuiltData> BuildItem(const FBuildItemParams& Params) const override;`
- L56 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterEditorPipelineSpecification*> GetSpecification() const override;`
- L65 _public member_ `TObjectPtr<USkeletalMesh> FaceMesh;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")` — Pre-built face mesh from the MetaHuman Character editor's Cinematic assembly.
- L69 _public member_ `TObjectPtr<USkeletalMesh> BodyMesh;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")` — Pre-built body mesh from the MetaHuman Character editor's Cinematic assembly.
- L75 _public member_ `TObjectPtr<USkeletalMesh> MergedHeadAndBodyMesh;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")` — Pre-built merged head and body mesh from the MetaHuman Character editor's Cinematic assembly. Body measurements will be read from the UChaosOutfitAssetBodyUserData attached to this mesh if available.
- L85 _public member_ `TObjectPtr<UMetaHumanCharacter> CompatibleBody;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")` — If this Character has been conformed to the body of another Character, assign the other Character to this property. This lets the Collection pipeline know that the neck seams of these two Characters are identical, and so the heads can safely be swapped.
- L89 _private member_ `TObjectPtr<UMetaHumanCharacterEditorPipelineSpecification> Specification;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowdEditor/Public/Item/MetaHumanCrowdGroomEditorPipeline.h` (Public)


#### struct `FMetaHumanCrowdGroomFitTarget`  
`struct FMetaHumanCrowdGroomFitTarget`  
_L16-25_
- reflection: `USTRUCT()`
- L21 _public member_ `TSoftObjectPtr<UMetaHumanCharacter> OptionalCharacter;` — `UPROPERTY()`
- L24 _public member_ `TObjectPtr<USkeletalMesh> TargetMesh;` — `UPROPERTY()`

#### struct `FMetaHumanCrowdGroomBuildInput`  
`struct FMetaHumanCrowdGroomBuildInput`  
_L28-49_
- reflection: `USTRUCT()`
- L34 _public member_ `TMap<FMetaHumanPaletteItemKey, FMetaHumanCrowdGroomFitTarget> FitTargets;` — `UPROPERTY()`
- L37 _public member_ `TArray<int32> ActorFaceLODs;` — `UPROPERTY()`
- L40 _public member_ `TArray<int32> InstancedFaceLODs;` — `UPROPERTY()`
- L48 _public member_ `FName PipelineSlotName;` — `UPROPERTY()` — Pipeline slot the groom item lives in (e.g. "Hair", "Eyebrows", "Beard", "Mustache"). Used as a parameter-name prefix when binding the groom's BakedGroomTexture and runtime colour parameters to the face material (e.g. "HairAttributeMap", "BeardMelanin").

#### enum `EMetaHumanCrowdGroomSkinWeightCopyMethod`  
`enum class EMetaHumanCrowdGroomSkinWeightCopyMethod : uint8`  
_L61-83_
- reflection: `UENUM(BlueprintType)`
- desc: Method for copying skin weights from source to target mesh. Note: this setting only applies fully to hair-card LODs. Helmet LODs (sourced from FHairGroupsMeshesSourceDescription) are solid hair caps rather than strands, so the pipeline only honours None vs. SingleBone for them: if you pick None, helmets get no skin weights; otherwise (PerVertex / StrandBased / SingleBone) helmets are forced to SingleBone (every helmet vertex parented to TargetBoneName).
- L64 _public enumerator_ `None` — Do not copy any weights
- L72 _public enumerator_ `PerVertex` — Each vertex finds closest point on source surface, interpolates weights (smooth, independent per-vertex). When TargetBoneName is specified, only source triangles influenced by that bone or its descendants are considered (same filtering as StrandBased; prevents long hair from picking up shoulder/spine weights).
- L79 _public enumerator_ `StrandBased` — Identify strands via connected components, copy anchor weights to entire strand. When TargetBoneName is specified, only source triangles influenced by that bone or its descendants are considered for anchor matching (prevents long hair from picking up shoulder/spine weights).
- L82 _public enumerator_ `SingleBone` — All vertices assigned to a single target bone with weight 1.0

#### struct `FGroomCardConversionParams`  
`struct FGroomCardConversionParams`  
_L87-115_
- reflection: `USTRUCT()`
- desc: Parameters for converting groom hair cards to skinned skeletal meshes.
- L93 _public member_ `EMetaHumanCrowdGroomSkinWeightCopyMethod SkinWeightMethod = EMetaHumanCrowdGroomSkinWeightCopyMethod::StrandBased;` — `UPROPERTY(EditAnywhere, Category = "Groom")` — Method used to copy skin weights from source mesh to converted cards.
- L97 _public member_ `float BlendWeightsThreshold = 0.002f;` — `UPROPERTY(EditAnywhere, Category = "Groom")` — Minimum weight threshold for bone influences. Weights below this value are discarded.
- L104 _public member_ `TArray<FName> ExcludedMaterialSlotNames;` — `UPROPERTY(EditAnywhere, Category = "Groom")` — Material slot names to exclude from source mesh when finding closest triangles. Useful for excluding geometry like eyelashes that would cause incorrect weight transfer.
- L114 _public member_ `FName TargetBoneName;` — `UPROPERTY(EditAnywhere, Category = "Groom")` — Target bone used by multiple skin weight methods: - SingleBone: All vertices are assigned to this bone with weight 1.0 - StrandBased / PerVertex: Only source triangles influenced by this bone or its descendants are considered for closest-point matching (prevents long hair from picking up body weights).

#### class `UMetaHumanCrowdGroomEditorPipeline`  
`class UMetaHumanCrowdGroomEditorPipeline : public UMetaHumanItemEditorPipeline`  
_L118-181_
- reflection: `UCLASS(EditInlineNew)`
- inherits: `UMetaHumanItemEditorPipeline`
- L123 _public prototype_ `UMetaHumanCrowdGroomEditorPipeline();`
- L125 _public prototype_ `virtual UE::Tasks::TTask<FMetaHumanPaletteBuiltData> BuildItem(const FBuildItemParams& Params) const override;`
- L127 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterEditorPipelineSpecification*> GetSpecification() const override;`
- L130 _public member_ `TArray<TSoftObjectPtr<UMetaHumanCharacter>> CompatibleHeads;` — `UPROPERTY(EditAnywhere, Category = "Groom")`
- L134 _public member_ `TSoftObjectPtr<UMaterialInterface> CardsMaterial;` — `UPROPERTY(EditAnywhere, Category = "Groom")` — Parent material used for hair cards. Card textures will be applied to this material's parameters.
- L142 _public member_ `TSoftObjectPtr<UMaterialInterface> HelmetsMaterial;` — `UPROPERTY(EditAnywhere, Category = "Groom")` — Parent material used for helmet (solid hair cap) LODs. Same texture parameters as CardsMaterial, but the difference is that the helmet variant authoring sets up the shading graph for solid-cap rendering rather than strand sampling.
- L146 _public member_ `FGroomCardConversionParams CardConversionParams;` — `UPROPERTY(EditAnywhere, Category = "Groom")` — Parameters controlling how groom hair cards are converted to skinned skeletal meshes.
- L160 _public member_ `TSoftObjectPtr<UTexture> BakedGroomTexture;` — `UPROPERTY(EditAnywhere, Category = "Groom")` — Pre-authored "baked groom" texture used as a face-material overlay on LODs that have no card or helmet geometry. Bound to the face MIC's "{PipelineSlotName}AttributeMap" parameter (e.g. "HairAttributeMap" for grooms in the Hair slot). Lets strands-only grooms (buzzcut, eyebrows, etc.) still render on the face when the crowd pipeline doesn't carry strand renderers. If unset, falls back to the value from the source groom's UMetaHumanDefaultGroomPipeline (the runtime pipeline's SourceGroomItem) when one is configured, so existing groom WIs work without per-asset duplication.
- L176 _public member_ `int32 GroomTextureMinLOD = -1;` — `UPROPERTY(EditAnywhere, Category = "Groom", meta = (ClampMin = -1))` — First face LOD at which the baked-groom texture is bound to the face material. Cards/helmets cover lower LODs (< GroomTextureMinLOD); the baked texture takes over from GroomTextureMinLOD upward. Cards/helmets at masked-out LODs render with a transparent material so they don't compete with the baked texture. `-1` (default) falls back to the value from the source groom's UMetaHumanDefaultGroomPipeline (the runtime pipeline's SourceGroomItem) when one is configured; otherwise the threshold becomes `0` (baked covers every face LOD). `N` (any non-negative value) reserves face LODs `0..N-1` for cards/helmet rendering and switches to the baked texture for face LODs `>= N`.
- L180 _private member_ `TObjectPtr<UMetaHumanCharacterEditorPipelineSpecification> Specification;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowdEditor/Public/Item/MetaHumanCrowdOutfitEditorPipeline.h` (Public)


#### struct `FMetaHumanCrowdOutfitFitTarget`  
`struct FMetaHumanCrowdOutfitFitTarget`  
_L15-25_
- reflection: `USTRUCT()`
- L21 _public member_ `TSoftObjectPtr<UMetaHumanCharacter> BodyCharacter;` — `UPROPERTY()`
- L24 _public member_ `TObjectPtr<USkeletalMesh> MergedHeadAndBodyMesh;` — `UPROPERTY()`

#### struct `FMetaHumanCrowdOutfitBuildInput`  
`struct FMetaHumanCrowdOutfitBuildInput`  
_L28-38_
- reflection: `USTRUCT()`
- L34 _public member_ `TMap<FMetaHumanPaletteItemKey, FMetaHumanCrowdOutfitFitTarget> FitTargets;` — `UPROPERTY()`
- L37 _public member_ `TObjectPtr<UDataflow> OutfitResizeDataflowAsset;` — `UPROPERTY()`

#### class `UMetaHumanCrowdOutfitEditorPipeline`  
`class UMetaHumanCrowdOutfitEditorPipeline : public UMetaHumanItemEditorPipeline`  
_L41-58_
- reflection: `UCLASS(EditInlineNew)`
- inherits: `UMetaHumanItemEditorPipeline`
- L46 _public prototype_ `UMetaHumanCrowdOutfitEditorPipeline();`
- L48 _public prototype_ `virtual UE::Tasks::TTask<FMetaHumanPaletteBuiltData> BuildItem(const FBuildItemParams& Params) const override;`
- L50 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterEditorPipelineSpecification*> GetSpecification() const override;`
- L53 _public member_ `TArray<TSoftObjectPtr<UMetaHumanCharacter>> CompatibleBodies;` — `UPROPERTY(EditAnywhere, Category = "Outfit")`
- L57 _private member_ `TObjectPtr<UMetaHumanCharacterEditorPipelineSpecification> Specification;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowdEditor/Public/Item/MetaHumanCrowdSkeletalClothingEditorPipeline.h` (Public)


#### class `UMetaHumanCrowdSkeletalClothingEditorPipeline`  
`class UMetaHumanCrowdSkeletalClothingEditorPipeline : public UMetaHumanItemEditorPipeline`  
_L16-33_
- reflection: `UCLASS(EditInlineNew)`
- inherits: `UMetaHumanItemEditorPipeline`
- desc: Editor pipeline for the crowd Skeletal Mesh clothing item pipeline.
- L21 _public prototype_ `UMetaHumanCrowdSkeletalClothingEditorPipeline();`
- L23 _public prototype_ `virtual UE::Tasks::TTask<FMetaHumanPaletteBuiltData> BuildItem(const FBuildItemParams& Params) const override;`
- L25 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterEditorPipelineSpecification*> GetSpecification() const override;`
- L28 _public member_ `TArray<TSoftObjectPtr<UMetaHumanCharacter>> CompatibleBodies;` — `UPROPERTY(EditAnywhere, Category = "SkeletalClothing")`
- L32 _private member_ `TObjectPtr<UMetaHumanCharacterEditorPipelineSpecification> Specification;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowdEditor/Public/MetaHumanCrowdAnimationConfig.h` (Public)


#### struct `FMetaHumanCrowdBakeAnimationData`  
`struct FMetaHumanCrowdBakeAnimationData`  
_L11-60_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "Crowd")` — Name used to identify this animation entry. Matches FMetaHumanCrowdAnimationAssemblyOutput::Name.
- L22 _public member_ `bool bUseMergedAnimation = false;` — `UPROPERTY(EditAnywhere, Category = "Crowd")` — Toggles the animation input mode
- L26 _public member_ `TObjectPtr<UAnimSequence> FaceAnimSequence;` — `UPROPERTY(EditAnywhere, Category = "Crowd", meta = (EditCondition = "!bUseMergedAnimation", EditConditionHides))` — Optional source animation to bake through the face mesh post-process ABP (RigLogic).
- L30 _public member_ `TObjectPtr<UAnimSequence> BodyAnimSequence;` — `UPROPERTY(EditAnywhere, Category = "Crowd", meta = (EditCondition = "!bUseMergedAnimation", EditConditionHides))` — Source animation for the body. Bone tracks are sampled directly and merged with the baked face animation.
- L34 _public member_ `TObjectPtr<UAnimSequence> MergedAnimSequence;` — `UPROPERTY(EditAnywhere, Category = "Crowd", meta = (EditCondition = "bUseMergedAnimation", EditConditionHides))` — Merged animation, expected to contain body animation and face animation curves (optional).
- L38 _public member_ `bool bLoop = true;` — `UPROPERTY(EditAnywhere, Category = "Crowd")` — Whether to set the output animation sequence asset to loop by default
- L42 _public member_ `bool bRootMotion = true;` — `UPROPERTY(EditAnywhere, Category = "Crowd")` — Whether to set the root motion flags
- L44 _public function_ `bool IsValid() const`

#### class `UMetaHumanCrowdAnimationConfig`  
`class UMetaHumanCrowdAnimationConfig : public UDataAsset`  
_L63-79_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UDataAsset`
- L75 _public member_ `FName FaceRootBoneName = FName("hea` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")` — When merging baked face and body animations, only face bone tracks that are children of this bone (inclusive) are taken from the baked face animation. All other bones come from the body animation. Defaults to "head", which is the typical choice for MetaHuman face rigs. Set to None to use all bones from the face bake with no filtering.
- L78 _public member_ `TArray<FMetaHumanCrowdBakeAnimationData> AnimationsToBake;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowdEditor/Public/MetaHumanCrowdEditorModule.h` (Public)
_(no declarations extracted)_

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowdEditor/Public/MetaHumanCrowdEditorPipeline.h` (Public)


#### struct `FMetaHumanCrowdFaceMaterialOverride`  
`struct FMetaHumanCrowdFaceMaterialOverride`  
_L30-58_
- reflection: `USTRUCT()`
- desc: Per-slot face material override for the Crowd pipeline. When the slot name on the face skeletal mesh matches SlotName and Material is non-null, the build replaces that slot's material with a fresh UMaterialInstanceConstant parented to Material; scalar/vector/texture parameters from the existing slot MIC are copied across so per-character textures (e.g. synthesised face basecolor/normal/cavity) survive the swap. Slots without an entry, or whose entry has Material == nullptr, keep their source MetaHuman Character material untouched.
- L36 _public member_ `FName SlotName;` — `UPROPERTY(EditAnywhere, Category = "Face")` — Slot name on the face skeletal mesh.
- L43 _public member_ `TSoftObjectPtr<UMaterialInterface> ActorMaterial;` — `UPROPERTY(EditAnywhere, Category = "Face")` — Override parent material for the actor face variant. Reads color from MIC scalar parameters (driven by per-actor MIDs at runtime). None = leave the slot alone.
- L51 _public member_ `TSoftObjectPtr<UMaterialInterface> InstancedMaterial;` — `UPROPERTY(EditAnywhere, Category = "Face")` — Override parent material for the instanced (ISKM) face variant. Reads color from per-instance custom data (written into the face ISKM's custom-data buffer at AssembleCollection time). None = leave the slot alone.
- L57 _public member_ `TMap<FName, FMetaHumanCrowdOutfitCustomDataFormat> InstanceParameterNameToCustomDataFormat;` — `UPROPERTY(EditAnywhere, Category = "Face")` — Per-instance custom-data offsets for parameters that drive this face slot's material.

#### struct `FMetaHumanCrowdActorLODSettings`  
`struct FMetaHumanCrowdActorLODSettings`  
_L61-68_
- reflection: `USTRUCT()`
- L67 _public member_ `int32 SourceLOD = 0;` — `UPROPERTY(EditAnywhere, Category = "Crowd")` — The index of the source LOD on the original MetaHuman mesh to pull this LOD's geometry from

#### struct `FMetaHumanCrowdInstancedLODSettings`  
`struct FMetaHumanCrowdInstancedLODSettings`  
_L71-86_
- reflection: `USTRUCT()`
- L77 _public member_ `int32 SourceLOD = 0;` — `UPROPERTY(EditAnywhere, Category = "Crowd")` — The index of the source LOD on the original MetaHuman mesh to pull this LOD's geometry from
- L85 _public member_ `FPerPlatformFloat ScreenSize = FPerPlatformFloat(1.0f);` — `UPROPERTY(EditAnywhere, Category = "Crowd")` — Screen size at which this LOD becomes active when Nanite is not enabled. Nanite always uses the top LOD and scales down procedurally from there.

#### class `UMetaHumanCrowdEditorPipeline`  
`class UMetaHumanCrowdEditorPipeline : public UMetaHumanCollectionEditorPipeline`  
_L89-306_
- reflection: `UCLASS(EditInlineNew)`
- inherits: `UMetaHumanCollectionEditorPipeline`
- L94 _public prototype_ `UMetaHumanCrowdEditorPipeline();`
- L96 _public prototype_ `virtual void BuildCollection(const FBuildCollectionParams& Params, const FOnBuildComplete& OnComplete) const override;`
- L98 _public prototype_ `virtual bool CanBuild() const override;`
- L100 _public prototype_ `virtual bool TryUnpackInstanceAssets( TNotNull<UMetaHumanInstance*> Instance, FInstancedStruct& AssemblyOutput, TArray<FMetaHumanGeneratedAssetMetadata>& AssemblyAssetMetadata, const FString& TargetFolder) const override;`
- L106 _public prototype_ `virtual TSubclassOf<AActor> GetEditorActorClass() const override;`
- L108 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterEditorPipelineSpecification*> GetSpecification() const override;`
- L110 _public prototype_ `virtual EMetaHumanWardrobeItemCompatibility TestWardrobeItemCompatibilityWithSlot(FName SlotName, TNotNull<const UMetaHumanWardrobeItem*> WardrobeItem) const override;`
- L112 _public prototype_ `virtual bool TryCreateItemForImport( TNotNull<UMetaHumanCollection*> Collection, FName SlotName, TNotNull<const UMetaHumanWardrobeItem*> SourceWardrobeItem, FMetaHumanCharacterPaletteItem& OutItem) override;`
- L118 _public prototype_ `virtual bool ValidateCollection(TNotNull<UMetaHumanCollection*> Collection) override;`
- L122 _public member_ `TArray<FMetaHumanCrowdActorLODSettings> ActorFaceLODs;` — `UPROPERTY(EditAnywhere, Category = "Actor Meshes")` — LOD settings for actor face and groom meshes.
- L126 _public member_ `TArray<FMetaHumanCrowdActorLODSettings> ActorBodyLODs;` — `UPROPERTY(EditAnywhere, Category = "Actor Meshes")` — LOD settings for actor body and clothing meshes.
- L130 _public member_ `FPerPlatformInt ActorMeshMinLOD;` — `UPROPERTY(EditAnywhere, Category = "Actor Meshes")` — Per-platform MinLOD applied to every actor skeletal mesh produced
- L138 _public member_ `FPerQualityLevelInt ActorMeshQualityLevelMinLOD;` — `UPROPERTY(EditAnywhere, Category = "Actor Meshes")` — Per-quality-level MinLOD applied to every actor skeletal mesh produced. Note that this is only used if the Use Skeletal Mesh Min LOD Per Quality Levels project setting is enabled.
- L152 _public member_ `int32 FaceRecomputeTangentsLODThreshold = 1;` — `UPROPERTY(EditAnywhere, Category = "Actor Meshes")` — Recompute tangents will be enabled using the skin cache on actor face LODs whose index is less than or equal to this threshold. In other words, this is the index of the worst LOD where it will be enabled. Note that this is a LOD index on the generated actor mesh, regardless of which source LODs it was generated from. Set to a negative value to disable on all LODs.
- L166 _public member_ `int32 FacialAnimationLODThreshold = 1;` — `UPROPERTY(EditAnywhere, Category = "Actor Meshes")` — The post-process anim blueprint that animates the face will be enabled on actor face LODs whose index is less than or equal to this threshold. In other words, this is the index of the worst LOD where it will be enabled. Note that this is a LOD index on the generated actor mesh, regardless of which source LODs it was generated from. Set to a negative value to disable on all LODs.
- L181 _public member_ `int32 BodyCorrectivesLODThreshold = 0;` — `UPROPERTY(EditAnywhere, Category = "Actor Meshes")` — The post-process anim blueprint that applies correctives to the body, improving volume preservation for example, will be enabled on actor body LODs whose index is less than or equal to this threshold. In other words, this is the index of the worst LOD where it will be enabled. Note that this is a LOD index on the generated actor mesh, regardless of which source LODs it was generated from. Set to a negative value to disable on all LODs.
- L185 _public member_ `TArray<FMetaHumanCrowdInstancedLODSettings> InstancedFaceLODs;` — `UPROPERTY(EditAnywhere, Category = "Instanced Meshes")` — LOD settings for instanced face meshes
- L189 _public member_ `TArray<FMetaHumanCrowdInstancedLODSettings> InstancedBodyLODs;` — `UPROPERTY(EditAnywhere, Category = "Instanced Meshes")` — LOD settings for instanced body meshes
- L193 _public member_ `FPerPlatformInt InstancedMeshMinLOD;` — `UPROPERTY(EditAnywhere, Category = "Instanced Meshes")` — Per-platform MinLOD applied to every instanced skeletal mesh produced.
- L201 _public member_ `FPerQualityLevelInt InstancedMeshQualityLevelMinLOD;` — `UPROPERTY(EditAnywhere, Category = "Instanced Meshes")` — Per-quality-level MinLOD applied to every instanced skeletal mesh produced. Note that this is only used if the Use Skeletal Mesh Min LOD Per Quality Levels project setting is enabled.
- L205 _public member_ `bool bKeepTeethInInstancedMeshes = false;` — `UPROPERTY(EditAnywhere, Category = "Instanced Meshes")` — Whether to include the teeth mesh section in instanced meshes.
- L209 _public member_ `bool bApplyHiddenFaceMaps = true;` — `UPROPERTY(EditAnywhere, Category = "Crowd")` — Whether to remove hidden body geometry according to the hidden face maps of the clothing items
- L212 _public member_ `bool bEnableNaniteOnInstancedMeshes = true;` — `UPROPERTY(EditAnywhere, Category = "Crowd")`
- L216 _public member_ `TObjectPtr<UDataflow> OutfitResizeDataflowAsset;` — `UPROPERTY(EditAnywhere, Category = "Crowd")` — The dataflow asset used to resize outfits to fit different body proportions
- L229 _public member_ `TObjectPtr<USkeleton> TargetSkeleton;` — `UPROPERTY(EditAnywhere, Category = "Crowd")` — The skeleton to bind all meshes to. The Instanced Skinned Mesh Component requires meshes to use the same skeleton as the animation playing on them. This skeleton should be in the project or a project plugin, because some unrelated actions, such as importing a new animation, can modify the skeleton and it's good practise to avoid modifying assets provided with the engine.
- L236 _public member_ `TSoftObjectPtr<USkeleton> TargetSkeletonTemplate;` — `UPROPERTY(EditDefaultsOnly, Category = "Crowd")` — The skeleton that TargetSkeleton will be copied from during ValidateCollection, if the user chooses to create a new skeleton.
- L247 _public member_ `TObjectPtr<UMetaHumanCrowdAnimationConfig> AnimationConfig;` — `UPROPERTY(EditAnywhere, Category = "Crowd")` — Animation configuration asset defining which animations to bake and merge for this crowd collection. Each entry produces one merged UAnimSequence per head character, on the shared TargetSkeleton. Two input modes are supported: a face + body pair that gets merged here (face curves are baked through the head mesh post-process ABP, then merged with body bone tracks), or a pre-merged sequence that is duplicated and rebound to TargetSkeleton. If not set, no animation baking is performed during BuildCollection.
- L254 _public member_ `TObjectPtr<class UAnimBoneCompressionSettings> BoneCompressionSettingsOverride;` — `UPROPERTY(EditDefaultsOnly, Category = "Crowd", meta = (ForceShowEngineContent))` — Bone compression settings for the procedurally-baked animations produced during BuildCollection. If null, the engine's animation-recorder preset is used.
- L263 _public member_ `TArray<FName> BodyForceKeepBones = { TEXT("neck_01"), TEXT("neck_02"` — `UPROPERTY(EditDefaultsOnly, Category = "Crowd")` — Bones that should remain in the reference skeleton of body, outfit, and groom meshes even when no geometry is weighted to them. Keeps the bone hierarchy consistent across every variant the pipeline produces (instanced and actor) so ISKM playback (which skips runtime retargeting) lines up with ABP playback.
- L270 _public member_ `FName HeadAlignmentBoneName = TEXT("hea` — `UPROPERTY(EditDefaultsOnly, Category = "Crowd")` — Bone used to align the head and body skeletons. Set it to the common bone where the two skeletons should align (typically 'head' on standard MetaHumans).
- L279 _public member_ `TArray<FMetaHumanCrowdFaceMaterialOverride> FaceMaterialOverrides;` — `UPROPERTY(EditAnywhere, Category = "Face")` — Per-slot overrides for face skeletal mesh materials. Use this to swap in crowd-specific shading parents (e.g. baked-groom face material, lower cost teeth/eye materials) while preserving per-character parameters from the source MICs.
- L288 _public member_ `TSoftObjectPtr<UMaterialInterface> InvisibleMaterial;` — `UPROPERTY(EditDefaultsOnly, Category = "Face")` — Material applied to groom skeletal-mesh slots at face LODs >= the groom's GroomTextureMinLOD. Renders nothing (transparent/masked) so the baked-groom texture on the face material can take over without competing geometry. Required when any groom item has a BakedGroomTexture set; if null, no LOD-based masking happens and cards keep rendering at high LODs.
- L292 _public member_ `TSubclassOf<UMetaHumanCrowdGroomPipeline> GroomPipelineClass;` — `UPROPERTY(EditDefaultsOnly, Category = "Item Pipelines")` — Pipeline class used for imported groom wardrobe items.
- L296 _public member_ `TSubclassOf<UMetaHumanCrowdOutfitPipeline> OutfitPipelineClass;` — `UPROPERTY(EditDefaultsOnly, Category = "Item Pipelines")` — Pipeline class used for imported outfit wardrobe items.
- L300 _public member_ `TSubclassOf<UMetaHumanCrowdSkeletalClothingPipeline> SkeletalClothingPipelineClass;` — `UPROPERTY(EditDefaultsOnly, Category = "Item Pipelines")` — Pipeline class used for imported skeletal mesh clothing wardrobe items.
- L305 _private member_ `TObjectPtr<UMetaHumanCharacterEditorPipelineSpecification> Specification;` — `UPROPERTY()`
