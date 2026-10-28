# Developer / SkeletalMeshUtilitiesCommon

- module root: `Source/Developer/SkeletalMeshUtilitiesCommon`
- headers: 3; symbols: 110
- symbol kinds: class=4, delegate=1, enum=1, enumerator=6, function=5, macro=1, member=30, namespace=1, prototype=53, struct=7, typedef=1
- PrivateDependencyModuleNames: ClothingSystemRuntimeCommon, Core, CoreUObject, Engine, ImageCore, InterchangeCore, MeshDescription, MeshUtilitiesCommon, RenderCore, SkeletalMeshDescription, Slate, StaticMeshDescription

### `Source/Developer/SkeletalMeshUtilitiesCommon/Public/LODUtilities.h` (Public)


#### struct `FSkeletalMeshUpdateContext`  
`struct FSkeletalMeshUpdateContext`  
_L26-32_
- L28 _public member_ `USkeletalMesh* SkeletalMesh;`
- L29 _public member_ `TArray<UActorComponent*> AssociatedComponents;`
- L31 _public member_ `FExecuteAction OnLODChanged;`

#### struct `FInlineReductionDataParameter`  
`struct FInlineReductionDataParameter`  
_L35-40_
- desc: Helper struct to define inline data when applying morph target on a reduce LOD. Inline data is needed when reduction is inline (LOD reduce itself).
- L37 _public member_ `bool bIsDataValid = false;`
- L38 _public member_ `FSkeletalMeshLODModel InlineOriginalSrcModel;`
- L39 _public member_ `TMap<FString, TArray<FMorphTargetDelta>> InlineOriginalSrcMorphTargetData;`

#### class `FLODUtilities`  
`class FLODUtilities`  
_L48-394_
- L59 _public prototype_ `static void ProcessImportMeshInfluences(const int32 VertexCount, TArray<SkeletalMeshImportData::FRawBoneInfluence>& Influences, const FString& MeshName);` — Process and update the vertex Influences using the predefined wedges @param VertexCount - The number of wedges in the corresponding mesh. @param Influences - BoneWeights and Ids for the corresponding vertices. @param MeshName	- Name of mesh, used for warning messages
- L71 _public prototype_ `static bool RegenerateLOD(USkeletalMesh* SkeletalMesh, const class ITargetPlatform* TargetPlatform, int32 NewLODCount = 0, bool bRegenerateEvenIfImported = false, bool bGenerateBaseLOD = false);` — Regenerate LODs of the mesh @param SkeletalMesh : the mesh that will regenerate LOD @param NewLODCount : Set valid value (>0) if you want to change LOD count. Otherwise, it will use the current LOD and regenerate @param bRegenerateEvenIfImported : If this is true, it only regenerate even if this LOD was imported before If false, it will regenerate for only previously auto generated ones @return true if succeed. If mesh reduction is not available this will return false.
- L78 _public prototype_ `static void RemoveLOD( FSkeletalMeshUpdateContext& UpdateContext, int32 DesiredLOD );` — Removes a particular LOD from the SkeletalMesh. @param UpdateContext - The skeletal mesh and actor components to operate on. @param DesiredLOD   - The LOD index to remove the LOD from.
- L85 _public prototype_ `static void RemoveLODs(FSkeletalMeshUpdateContext& UpdateContext, const TArray<int32>& DesiredLODs);` — Removes the specified LODs from the SkeletalMesh. @param UpdateContext - The skeletal mesh and actor components to operate on. @param DesiredLODs   - The array of LOD index to remove the LOD from. The order is irrelevant since the array will be sorted to be reverse iterate.
- L95 _public prototype_ `static bool SetCustomLOD(USkeletalMesh* DestinationSkeletalMesh, USkeletalMesh* SourceSkeletalMesh, const int32 LodIndex, const FString& SourceDataFilename);` — Add or change the LOD data specified by LodIndex with the content of the sourceSkeletalMesh. @Param DestinationSkeletalMesh - Skeletal mesh receiving the LOD data. @Param SourceSkeletalMesh - Skeletal mesh providing the LOD data we want to use to add or modify the specified destination LOD at LodIndex. The LOD we want to import is always the base LOD of the source mesh. @Param LodIndex - The destination lod index we want to add or modify. @Param SourceDataFilename - The file name we use to import the source skeletal mesh.
- L103 _public prototype_ `static void SimplifySkeletalMeshLOD(FSkeletalMeshUpdateContext& UpdateContext, int32 DesiredLOD, const class ITargetPlatform* TargetPlatform, bool bRestoreClothing = false, std::atomic<bool>* OutNeedsPackageDirtied = nullptr);` — Simplifies the static mesh based upon various user settings for DesiredLOD. @param UpdateContext - The skeletal mesh and actor components to operate on. @param DesiredLOD - The LOD to simplify
- L112 _public prototype_ `static bool RestoreSkeletalMeshLODImportedData_DEPRECATED(USkeletalMesh* SkeletalMesh, int32 LodIndex);` — Restore the LOD imported model to the last imported data. Call this function if you want to remove the reduce on the base LOD @param SkeletalMesh - The skeletal mesh to operate on. @param LodIndex - The LOD index to restore the imported LOD model @param bReregisterComponent - if true the component using the skeletal mesh will all be re register.
- L122 _public prototype_ `static void RefreshLODChange(const USkeletalMesh* SkeletalMesh);` — Refresh LOD Change LOD has changed, it will have to notify all SMC that uses this SM and ask them to refresh LOD @param	InSkeletalMesh	SkeletalMesh that LOD has been changed for
- L128 _public prototype_ `static void RegenerateDependentLODs(USkeletalMesh* SkeletalMesh, int32 LODIndex, const class ITargetPlatform* TargetPlatform);` — Regenerate LOD that are dependent of LODIndex
- L133 _public prototype_ `static void BuildMorphTargets(USkeletalMesh* SkeletalMesh, class FSkeletalMeshImportData &ImportData, int32 LODIndex, bool ShouldImportNormals, bool ShouldImportTangents, bool bUseMikkTSpace, const FOverlappingThresholds& Thresholds);` — Build the morph targets for the specified LOD. The function use the Morph target data stored in the FSkeletalMeshImportData ImportData structure
- L138 _public prototype_ `static void BuildMorphTargets( USkeletalMesh* SkeletalMesh, const FMeshDescription& SkeletalMeshModel, FSkeletalMeshImportData& ImportData, int32 LODIndex, bool ShouldImportNormals, bool ShouldImportTangents, bool bUseMikkTSpace, const FOverlappingThresholds& Thresholds );` — Same as above but use normals from the source mesh description to build up the morph targets.
- L161 _public prototype_ `static bool UpdateAlternateSkinWeights( USkeletalMesh* SkeletalMeshDest, const FName& ProfileNameDest, USkeletalMesh* SkeletalMeshSrc, int32 LODIndexDest, int32 LODIndexSrc, const IMeshUtilities::MeshBuildOptions& Options);` — This function apply the skinning weights from asource skeletal mesh to the destination skeletal mesh. The Destination will receive the weights has the alternate weights. We extract the imported skinning weight data from the SkeletalMeshSrc and we save the imported raw data into the destination mesh. Then we call UpdateAlternateSkinWeights without the SkeletalMeshSrc @param SkeletalMeshDest - The skeletal mesh that will receive the alternate skinning weights. @param SkeletalMeshSrc - The skeletal mesh that contain the alternate skinning weights. @param LODIndexDest - the destination LOD @param LODIndexSrc - the Source LOD index
- L170 _public prototype_ `static bool UpdateAlternateSkinWeights( USkeletalMesh* SkeletalMeshDest, const FName& ProfileNameDest, USkeletalMesh* SkeletalMeshSrc, int32 LODIndexDest, int32 LODIndexSrc, FOverlappingThresholds OverlappingThresholds, bool ShouldImportNormals, bool ShouldImportTangents, bool bUseMikkTSpace, bool bComputeWeightedNormals);` — `UE_DEPRECATED(5.2, "Please use the new overloads of UpdateAlternateSkinWeights that take an IMeshUtilities::MeshBuildOptions. Note that IMeshUtilities::MeshBuildOptions::bComputeNormals/Tangents has the opposite meaning of ShouldImportNormals/Tangents.")`
- L189 _public prototype_ `static bool UpdateAlternateSkinWeights( USkeletalMesh* SkeletalMeshDest, const FName& ProfileNameDest, int32 LODIndexDest, const IMeshUtilities::MeshBuildOptions& Options);` — This function apply the skinning weights from the saved imported skinning weight data to the destination skeletal mesh. The Destination will receive the weights has the alternate weights. @param SkeletalMeshDest - The skeletal mesh that will receive the alternate skinning weights. @param LODIndexDest - the destination LOD
- L196 _public prototype_ `static bool UpdateAlternateSkinWeights( USkeletalMesh* SkeletalMeshDest, const FName& ProfileNameDest, int32 LODIndexDest, FOverlappingThresholds OverlappingThresholds, bool ShouldImportNormals, bool ShouldImportTangents, bool bUseMikkTSpace, bool bComputeWeightedNormals);` — `UE_DEPRECATED(5.2, "Please use the new overloads of UpdateAlternateSkinWeights that take an IMeshUtilities::MeshBuildOptions. Note that IMeshUtilities::MeshBuildOptions::bComputeNormals/Tangents has the opposite meaning of ShouldImportNormals/Tangents.")`
- L206 _public prototype_ `static bool UpdateAlternateSkinWeights( FSkeletalMeshLODModel& LODModelDest, FSkeletalMeshImportData& ImportDataDest, USkeletalMesh* SkeletalMeshDest, const FReferenceSkeleton& RefSkeleton, const FName& ProfileNameDest, int32 LODIndexDest, const IMeshUtilities::MeshBuildOptions& Options);`
- L231 _public prototype_ `static bool UpdateLODInfoVertexAttributes(USkeletalMesh *InSkeletalMesh, int32 InSourceLODIndex, int32 InTargetLODIndex, bool bInCopyAttributeValues);` — Build the vertex attributes
- L238 _public prototype_ `static void RegenerateAllImportSkinWeightProfileData(FSkeletalMeshLODModel& LODModelDest, int32 BoneInfluenceLimit = 0, const ITargetPlatform* TargetPlatform = nullptr);` — Re-generate all (editor-only) skin weight profile, used whenever we rebuild the skeletal mesh data which could change the chunking and bone indices If BoneInfluenceLimit is 0, the DefaultBoneInfluenceLimit from the project settings will be used.
- L240 _public prototype_ `static void UnbindClothingAndBackup(USkeletalMesh* SkeletalMesh, TArray<ClothingAssetUtils::FClothingAssetMeshBinding>& ClothingBindings);`
- L241 _public prototype_ `static void UnbindClothingAndBackup(USkeletalMesh* SkeletalMesh, TArray<ClothingAssetUtils::FClothingAssetMeshBinding>& ClothingBindings, const int32 LODIndex);`
- L243 _public prototype_ `static void RestoreClothingFromBackup(USkeletalMesh* SkeletalMesh, TArray<ClothingAssetUtils::FClothingAssetMeshBinding>& ClothingBindings);`
- L244 _public prototype_ `static void RestoreClothingFromBackup(USkeletalMesh* SkeletalMesh, TArray<ClothingAssetUtils::FClothingAssetMeshBinding>& ClothingBindings, const int32 LODIndex);`
- L256 _public prototype_ `static void BackupCustomImportedMorphTargetData(USkeletalMesh* SkeletalMesh, TMap<FString, TArray<FMorphTargetLodBackupData>>& BackupImportedMorphTargetData);` — Backup all the custom imported morph targets.
- L261 _public prototype_ `static bool RestoreCustomImportedMorphTargetData(USkeletalMesh* SkeletalMesh, const int32 LodIndex, FMeshDescription& LodMeshDescription, const TMap<FString, TArray<FMorphTargetLodBackupData>>& BackupImportedMorphTargetData);` — Restore the custom imported morph target in the mesh description. Return true if the mesh description was changed because it restore some morph targets
- L270 _public prototype_ `static void AdjustImportDataFaceMaterialIndex(const TArray<FSkeletalMaterial>& Materials, TArray<SkeletalMeshImportData::FMaterial>& RawMeshMaterials, TArray<SkeletalMeshImportData::FMeshFace>& LODFaces, int32 LODIndex);` — Before building skeletalmesh base LOD (LOD index 0) using MeshUtilities.BuildSkeletalMesh, we want to adjust the imported faces material index to point on the correct sk material. We use the material name to match the material. @param Materials - The skeletalmesh material list to fit the import data face material @param RawMeshMaterials - The import data material list @param LODFaces - The face to adjust with the material remap @param LODIndex - We can adjust only the base LOD (LODIndex 0), the function will not do anything if LODIndex is not 0
- L296 _public prototype_ `static void MatchImportedMaterials(FSkeletalMeshMatchImportedMaterialsParameters& Parameters);` — When any skeletalmesh LOD get imported or re-imported, we want to have common code to set all materials data. In case we re-import a LOD this code will match the sections using imported material name to be able to keep any section data. The material slot array is not re-order even if we re-import the base LOD.
- L301 _public prototype_ `static void ReorderMaterialSlotToBaseLod(USkeletalMesh* SkeletalMesh);` — Reorder the material slot array to follow the base LOD section order. It will readjust all LOD section material index and LODMaterialMap.
- L306 _public prototype_ `static void RemoveUnusedMaterialSlot(USkeletalMesh* SkeletalMesh);` — Remove any material slot that is not used by any LODs
- L317 _public prototype_ `static bool StripLODGeometry(USkeletalMesh* SkeletalMesh, const int32 LODIndex, UTexture2D* TextureMask, const float Threshold);` — This function will strip all triangle in the specified LOD that don't have any UV area pointing on a black pixel in the TextureMask. We use the UVChannel 0 to find the pixels in the texture. @Param SkeletalMesh: The skeletalmesh we want to optimize @Param LODIndex: The LOD we want to optimize @Param TextureMask: The texture containing the stripping mask. non black pixel strip triangle, black pixel keep them. @Param Threshold: The threshold we want when comparing the texture value with zero.
- L320 _private function_ `FLODUtilities()`
- L323 _private prototype_ `static void GenerateImportedSkinWeightProfileData( FSkeletalMeshLODModel& LODModelDest, struct FImportedSkinWeightProfileData& ImportedProfileData, int32 BoneInfluenceLimit, const class ITargetPlatform* TargetPlatform);` — Generate the editor-only data stored for a skin weight profile (relies on bone indices)
- L369 _private prototype_ `static void SimplifySkeletalMeshLOD( USkeletalMesh* SkeletalMesh, int32 DesiredLOD, const ITargetPlatform* TargetPlatform, bool bRestoreClothing, TArray<FMorphTargetUpdateRequest>& OutMorphRequests, std::atomic<bool>* OutNeedsPackageDirtied = nullptr );` — Simplifies the static mesh based upon various user settings for DesiredLOD This is private function that gets called by SimplifySkeletalMesh @param SkeletalMesh - The skeletal mesh and actor components to operate on. @param DesiredLOD - Desired LOD
- L385 _private prototype_ `static void ApplyMorphTargetsToLOD(USkeletalMesh* SkeletalMesh, int32 SourceLOD, int32 DestinationLOD, const FInlineReductionDataParameter& InlineApplyMorphTargetParameter);` — Remap the morph targets of the base LOD onto the desired LOD. @param SkeletalMesh - The skeletal mesh to operate on. @param SourceLOD      - The source LOD morph target . @param DestinationLOD   - The destination LOD morph target to apply the source LOD morph target
- L393 _private prototype_ `static void ClearGeneratedMorphTarget(USkeletalMesh* SkeletalMesh, int32 DesiredLOD);` — Clear generated morphtargets for the given LODs @param SkeletalMesh - The skeletal mesh and actor components to operate on. @param DesiredLOD - Desired LOD

#### struct `FLODUtilities::FMorphTargetLodBackupData`  
`struct FMorphTargetLodBackupData`  
_L246-251_
- L248 _public member_ `bool bIsEmpty = true;`
- L249 _public member_ `TArray<FVector3f> MorphPositionDeltas;`
- L250 _public member_ `TArray<FVector3f> MorphNormalDeltas;`

#### struct `FLODUtilities::FSkeletalMeshMatchImportedMaterialsParameters`  
`struct FSkeletalMeshMatchImportedMaterialsParameters`  
_L281-289_
- desc: Structure to pass all the needed parameters to do match the material when importing a skeletal mesh LOD. @param SkeletalMesh - The skeletalmesh that get a LOD re/import @param LodIndex - The skeletalmesh LOD index that get re/import @param bIsReImport - whether its a skeletal mesh LOD re-import @param ImportedMaterials - The imported material list @param ExistingOriginalPerSectionMaterialImportName - The previously LOD imported material list (cannot be null if bIsReImport is true) @param CustomImportedLODModel - When importing custom LOD we want to pass the LODModel to synchronize the sections
- L283 _public member_ `USkeletalMesh* SkeletalMesh = nullptr;`
- L284 _public member_ `int32 LodIndex = 0;`
- L285 _public member_ `bool bIsReImport = false;`
- L286 _public member_ `const TArray<SkeletalMeshImportData::FMaterial>* ImportedMaterials = nullptr;`
- L287 _public member_ `const TArray<FName>* ExistingOriginalPerSectionMaterialImportName = nullptr;`
- L288 _public member_ `FSkeletalMeshLODModel* CustomImportedLODModel = nullptr;`

#### struct `FLODUtilities::FMorphTargetUpdateRequest`  
`struct FMorphTargetUpdateRequest`  
_L329-360_
- L331 _public prototype_ `FMorphTargetUpdateRequest() = default;`
- L332 _public function_ `FMorphTargetUpdateRequest(USkeletalMesh* InSkeletalMesh, const int32 InSourceLOD, const int32 InDestinationLOD, FInlineReductionDataParameter&& InReductionData) : SkeletalMesh(InSkeletalMesh), SourceLOD(InSourceLOD), DestinationLOD(InDestinationLOD), ReductionData(MoveTemp(InReductionData))`
- L339 _public function_ `FMorphTargetUpdateRequest(USkeletalMesh* InSkeletalMesh, const int32 InDestinationLOD) : SkeletalMesh(InSkeletalMesh), DestinationLOD(InDestinationLOD)`
- L344 _public member_ `USkeletalMesh* SkeletalMesh = nullptr;`
- L345 _public member_ `int32 SourceLOD = INDEX_NONE;`
- L346 _public member_ `int32 DestinationLOD = INDEX_NONE;`
- L347 _public member_ `FInlineReductionDataParameter ReductionData;`
- L349 _public function_ `void Run() const`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace ClothingAssetUtils`

### `Source/Developer/SkeletalMeshUtilitiesCommon/Public/SkeletalMeshNotifier.h` (Public)


#### enum `ESkeletalMeshNotifyType`  
`enum class ESkeletalMeshNotifyType`  
_L14-22_
- L16 _public enumerator_ `BonesAdded`
- L17 _public enumerator_ `BonesRemoved`
- L18 _public enumerator_ `BonesMoved`
- L19 _public enumerator_ `BonesSelected`
- L20 _public enumerator_ `BonesRenamed`
- L21 _public enumerator_ `HierarchyChanged`

#### class `ISkeletalMeshNotifier`  
`class ISkeletalMeshNotifier`  
_L27-44_
- L30 _public prototype_ `ISkeletalMeshNotifier() = default;`
- L31 _public prototype_ `virtual ~ISkeletalMeshNotifier() = default;`
- L33 _public prototype_ `FSkeletalMeshNotifyDelegate& Delegate();`
- L36 _public prototype_ `virtual void HandleNotification(const TArray<FName>& BoneNames, const ESkeletalMeshNotifyType InNotifyType) = 0;` — override this function to react to notifications locally.
- L38 _public prototype_ `void Notify(const TArray<FName>& BoneNames, const ESkeletalMeshNotifyType InNotifyType) const;`
- L39 _public prototype_ `bool Notifying() const;`
- L42 _private member_ `FSkeletalMeshNotifyDelegate NotifyDelegate;`
- L43 _private member_ `mutable bool bNotifying = false;`

#### class `FSkeletalMeshNotifierBindScope`  
`class FSkeletalMeshNotifierBindScope`  
_L46-59_
- L50 _public prototype_ `FSkeletalMeshNotifierBindScope(TWeakPtr<ISkeletalMeshNotifier> InNotifierA, TWeakPtr<ISkeletalMeshNotifier> InNotifierB);`
- L51 _public prototype_ `~FSkeletalMeshNotifierBindScope();`
- L54 _private member_ `TWeakPtr<ISkeletalMeshNotifier> NotifierA;`
- L55 _private member_ `TWeakPtr<ISkeletalMeshNotifier> NotifierB;`
- L57 _private member_ `FDelegateHandle DelegateToRemoveFromNotifierA;`
- L58 _private member_ `FDelegateHandle DelegateToRemoveFromNotifierB;`

#### class `ISkeletalMeshEditorBinding`  
`class ISkeletalMeshEditorBinding`  
_L61-73_
- L64 _public prototype_ `ISkeletalMeshEditorBinding() = default;`
- L65 _public prototype_ `virtual ~ISkeletalMeshEditorBinding() = default;`
- L67 _public prototype_ `virtual TSharedPtr<ISkeletalMeshNotifier> GetNotifier() = 0;`
- L69 _public typedef_ `using NameFunction = TFunction< TOptional<FName>(HHitProxy*)>;`
- L70 _public prototype_ `virtual NameFunction GetNameFunction() = 0;`
- L72 _public prototype_ `virtual TArray<FName> GetSelectedBones() const = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SKELETALMESHUTILITIESCOMMON_API`
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FSkeletalMeshNotifyDelegate, const TArray<FName>& , const ESkeletalMeshNotifyType );` — A delegate for monitoring to skeletal mesh global notifications.
- L25 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FSkeletalMeshNotifyDelegate, const TArray<FName>& , const ESkeletalMeshNotifyType );` — A delegate for monitoring to skeletal mesh global notifications.

### `Source/Developer/SkeletalMeshUtilitiesCommon/Public/StaticToSkeletalMeshConverter.h` (Public)


#### struct `FStaticToSkeletalMeshConverter`  
`struct FStaticToSkeletalMeshConverter`  
_L20-132_
- L31 _public prototype_ `static bool InitializeSkeletonFromStaticMesh( USkeleton* InSkeleton, const UStaticMesh* InStaticMesh, const FVector& InRelativeRootPosition );` — Creates a skeleton from a static mesh with a single root bone. @param InSkeleton The skeleton to initialize. It has to be freshly created and contain no bones already. @param InStaticMesh The static mesh whose bounding box will be used as a reference. @param InRelativeRootPosition The relative root position in a unit cube that gets scaled up to match the bbox of the static mesh. For example, given FVector(0.5, 0.5, 0.0), the root bone location will be placed at the center of the bottom of the static mesh's bbox. @return \c true if the operation succeeded.
- L50 _public prototype_ `static bool InitializeSkeletonFromStaticMesh( USkeleton* InSkeleton, const UStaticMesh* InStaticMesh, const FVector& InRelativeRootPosition, const FVector& InRelativeEndEffectorPosition, const int32 InIntermediaryJointCount );` — Creates a skeleton from a static mesh with a bone chain going from root to end effector, where the intermediary bones are distributed evenly along a line between the two. @param InSkeleton The skeleton to initialize. It has to be freshly created and contain no bones already. @param InStaticMesh The static mesh whose bounding box will be used as a reference. @param InRelativeRootPosition The relative root position in a unit cube that gets scaled up to match the bbox of the static mesh. For example, given FVector(0.5, 0.5, 0.0), the root bone location will be placed at the center of the bottom of the static mesh's bbox. @param InRelativeEndEffectorPosition The end effector position, positioned in the same manner as the root position. If the end effector is in the same location as the root, only the root bone is created. @param InIntermediaryJointCount Number of joints to create between the root and the end effector. @return \c true if the operation succeeded.
- L65 _public prototype_ `static bool InitializeSkeletalMeshFromStaticMesh( USkeletalMesh* InSkeletalMesh, const UStaticMesh* InStaticMesh, const FReferenceSkeleton& InReferenceSkeleton, const FName InBindBone = NAME_None );` — Initialize a skeletal mesh from the given static mesh and a skeleton. The mesh will initially be created with a rigid binding on the root bone. @param InSkeletalMesh The skeletal mesh to initialize. It has to be freshly created and be completely empty. @param InStaticMesh The static mesh to convert from. @param InReferenceSkeleton The reference skeleton to use. @param InBindBone The bone to bind to. If no bone name is given, the binding defaults to the root bone.
- L85 _public prototype_ `static bool InitializeSkeletalMeshFromMeshDescriptions( USkeletalMesh* InSkeletalMesh, TArrayView<const FMeshDescription*> InMeshDescriptions, TConstArrayView<FSkeletalMaterial> InMaterials, const FReferenceSkeleton& InReferenceSkeleton, const bool bInRecomputeNormals = false, const bool bInRecomputeTangents = true, const bool bCacheOptimize = true );` — `UE_DEPRECATED(5.8, "Please use the new overloads of InitializeSkeletalMeshFromMeshDescriptions that takes FInitializationParams.")` — Create a skeletal mesh from a list of mesh description objects and a reference skeleton. If any mesh description either doesn't contain a skin weight, or any of the skin weights reference a bone that doesn't exist on the reference skeleton, this operation fails. @param InSkeletalMesh The skeletal mesh to initialize. It has to be freshly created and be completely empty. @param InMeshDescriptions The mesh description objects to create each subsequent LOD, starting from LOD0. @param InMaterials The materials to apply to the skeletal mesh. The conversion will attempt a best effort to ensure that the PolygonGroup::ImportedMaterialSlotName attribute will map to existing import names. @param InReferenceSkeleton The reference skeleton to use. @param bInRecomputeNormals Recompute normals when the mesh is generated from the mesh description. @param bInRecomputeTangents Recompute tangents when the mesh is generated from the mesh description. @param bCacheOptimize Enable the cache optimization of the index buffer.
- L126 _public prototype_ `static bool InitializeSkeletalMeshFromMeshDescriptions( USkeletalMesh* InSkeletalMesh, TArrayView<const FMeshDescription*> InMeshDescriptions, const FReferenceSkeleton& InReferenceSkeleton, const FInitializationParams& InParams = {} );` — Create a skeletal mesh from a list of mesh description objects and a reference skeleton. If any mesh description either doesn't contain a skin weight, or any of the skin weights reference a bone that doesn't exist on the reference skeleton, this operation fails. @param InSkeletalMesh The skeletal mesh to initialize. It has to be freshly created and be completely empty. @param InMeshDescriptions The mesh description objects to create each subsequent LOD, starting from LOD0. @param InReferenceSkeleton The reference skeleton to use. @param InParams The initialization parameters used.

#### struct `FStaticToSkeletalMeshConverter::FInitializationParams`  
`struct FInitializationParams`  
_L96-116_
- desc: Structure that defines parameters passed into the initialize skeletal mesh from mesh descriptions function.
- L98 _public function_ `FInitializationParams()`
- L103 _public member_ `TConstArrayView<FSkeletalMaterial> Materials;` — The materials to apply to the skeletal mesh. The conversion will attempt a best effort to ensure that the PolygonGroup::ImportedMaterialSlotName attribute will map to existing import names.
- L106 _public member_ `bool bRecomputeNormals = false;` — Recompute normals when the mesh is generated from the mesh description.
- L109 _public member_ `bool bRecomputeTangents = true;` — Recompute tangents when the mesh is generated from the mesh description.
- L112 _public member_ `bool bCacheOptimize = true;` — Enable the cache optimization of the index buffer.
- L115 _public member_ `TConstArrayView<FName> VertexAttributesForRender;` — Vertex attribute names, as defined in the mesh description, that need to be enabled for render.
