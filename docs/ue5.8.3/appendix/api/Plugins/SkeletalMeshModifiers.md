# Plugins / SkeletalMeshModifiers

- module root: `Plugins/Runtime/MeshModelingToolset/Source/SkeletalMeshModifiers`
- headers: 4; symbols: 168
- symbol kinds: class=4, enum=6, enumerator=31, function=4, macro=2, member=34, namespace=1, prototype=81, struct=5
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ApplicationCore, CoreUObject, Engine, GeometryCore, GeometryFramework, MeshDescription, RenderCore, SkeletalMeshDescription, SkeletalMeshUtilitiesCommon, Slate, SlateCore, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Runtime/MeshModelingToolset/Source/SkeletalMeshModifiers/Public/SkeletalMeshModifiersModule.h` (Public)


#### class `FSkeletalMeshModifiersModule`  
`class FSkeletalMeshModifiersModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/MeshModelingToolset/Source/SkeletalMeshModifiers/Public/SkeletonClipboard.h` (Public)


#### enum `SkeletonClipboard::EPasteBoneTransformsFromClipboardFlags`  
`enum class EPasteBoneTransformsFromClipboardFlags`  
_L76-81_
- desc: Flags for PasteBoneTransformsFromClipboard
- L78 _public enumerator_ `None = 0`
- L79 _public enumerator_ `UpdateChildren = 1 << 0`
- L80 _public enumerator_ `UsingGlobalTransforms = 1 << 1`

#### struct `FBoneClipboardData`  
`struct FBoneClipboardData`  
_L114-143_
- reflection: `USTRUCT()`
- L118 _public prototype_ `FBoneClipboardData() = default;`
- L122 _public prototype_ `FBoneClipboardData(const FBoneClipboardData&) = default;` — removing deprecation for default copy operator/constructor to avoid deprecation warnings
- L123 _public prototype_ `FBoneClipboardData(FBoneClipboardData&&) = default;`
- L124 _public prototype_ `FBoneClipboardData& operator=(const FBoneClipboardData&) = default;`
- L125 _public prototype_ `FBoneClipboardData& operator=(FBoneClipboardData&&) = default;`
- L129 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY()`
- L132 _public member_ `FName ParentBoneName = NAME_None;` — `UPROPERTY()`
- L136 _public member_ `int32 ParentIndex_DEPRECATED = INDEX_NONE;` — `UE_DEPRECATED(5.8, "Instead refer to ParentBoneName")` — `UPROPERTY()`
- L139 _public member_ `FTransform Global = FTransform::Identity;` — `UPROPERTY()`
- L142 _public member_ `FTransform Local = FTransform::Identity;` — `UPROPERTY()`

#### enum `EBoneClipboardDataType`  
`enum class EBoneClipboardDataType : uint8`  
_L146-151_
- reflection: `UENUM()`
- L148 _public enumerator_ `Invalid`
- L149 _public enumerator_ `Bones`
- L150 _public enumerator_ `BoneTransforms`

#### struct `FHierarchyClipboardData`  
`struct FHierarchyClipboardData`  
_L154-163_
- reflection: `USTRUCT()`
- L159 _public member_ `TArray<FBoneClipboardData> Bones;` — `UPROPERTY()`
- L162 _public member_ `EBoneClipboardDataType Type = EBoneClipboardDataType::Invalid;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace SkeletonClipboard`
- L22 _prototype_ `void CopyToClipboard( const USkeletonModifier& InModifier, const TArray<FName>& InBonesToCopy);` (scope `SkeletonClipboard`) — `UE_DEPRECATED(5.8, "Instead use CopyBonesToClipboard to avoid ambiguity with CopyBoneTransformsToClipboard")` — DEPRECATED 5.8, instead use CopyBonesToClipboard
- L32 _prototype_ `void CopyBonesToClipboard( const USkeletonModifier& InModifier, const TArray<FName>& InBonesToCopy);` (scope `SkeletonClipboard`) — Copies InBonesToCopy data (name, parent, transform) into the clipboard. Also copies children of these bones. @param InModifier				The skeleton modifier that provides the skeleton and the bones to copy. @param InBonesToCopy				The bones which are copied
- L38 _prototype_ `TArray<FName> PasteFromClipboard( USkeletonModifier& InOutModifier, const FName& InDefaultParent);` (scope `SkeletonClipboard`) — `UE_DEPRECATED(5.8, "Instead use the PasteBonesFromClipboard that offers the bUsingGlobalTransforms argument")` — DEPRECATED 5.8, instead use PasteBonesFromClipboard
- L49 _prototype_ `TArray<FName> PasteBonesFromClipboard( USkeletonModifier& InOutModifier, const FName& InDefaultParent, const bool bUsingGlobalTransforms);` (scope `SkeletonClipboard`) — Paste new bones from the clipboard InBonesToCopy data (name, parent, transform) into the InOutModifier. @param InOutModifier				The skeleton modifier that provides the skeleton to which the bones are pasted @param InDefaultParent			The parent to which bones are pasted @param bUsingGlobalTransforms	If true, pastes global transforms
- L60 _prototype_ `TArray<FName> ClipboardDuplicateBones( USkeletonModifier& InOutModifier, const TArray<FName>& InBonesToDuplicate);` (scope `SkeletonClipboard`) — Duplicates InBonesToCopy data (name, parent, transform) using the clipboard. Also duplicates children of these bones. @param InOutModifier				The skeleton modifier that provides the skeleton and the bones to duplicate. @param InBonesToDuplicate		The bones that are being duplicated
- L71 _prototype_ `void CopyBoneTransformsToClipboard( const USkeletonModifier& InModifier, TArray<FName> InBonesToCopy);` (scope `SkeletonClipboard`) — Copies transforms of InBonesToCopy into the clipboard. Hierarchy info & transforms are retrieved via the InModifier. @param InModifier				The skeleton modifier that provides the skeleton and the bones from which transforms are copied. @param InBonesToCopy				The bones from which transforms are copied
- L82 _prototype_ `ENUM_CLASS_FLAGS(EPasteBoneTransformsFromClipboardFlags);` (scope `SkeletonClipboard`)
- L92 _prototype_ `TArray<FName> PasteBoneTransformsFromClipboard( USkeletonModifier& InOutModifier, TArray<FName> InCandidateBoneNames, const EPasteBoneTransformsFromClipboardFlags Flags);` (scope `SkeletonClipboard`) — Paste transforms from the clipboard data into the InOutModifier. @param InOutModifier				The skeleton modifier that provides the skeleton and the bones to which transforms are pasted. @param InCandidateBoneNames		Bones where the transforms should be pasted, not necessarily considered @param Flags						Flags to define how bone transforms should be pasted @return							The bones that were affected by the paste action
- L99 _prototype_ `bool IsClipboardValid();` (scope `SkeletonClipboard`) — `UE_DEPRECATED(5.8, "Instead use IsBoneClipboardValid and IsBoneTransformClipboardValid")` — DEPRECATED 5.8, instead use IsBoneClipboardValid and IsBoneTransformClipboardValid
- L104 _prototype_ `bool IsBoneClipboardValid();` (scope `SkeletonClipboard`) — Checks whether bone clipboard data is valid.
- L109 _prototype_ `bool IsBoneTransformClipboardValid();` (scope `SkeletonClipboard`) — Checks whether bone transform clipboard data is valid.

### `Plugins/Runtime/MeshModelingToolset/Source/SkeletalMeshModifiers/Public/SkeletonModifier.h` (Public)


#### enum `ESkeletalMeshModificationType`  
`enum class ESkeletalMeshModificationType : uint32`  
_L23-36_
- L25 _public enumerator_ `None = 0x000`
- L27 _public enumerator_ `BonesAdded = 0x001`
- L28 _public enumerator_ `BonesRemoved = 0x002`
- L29 _public enumerator_ `BonesRenamed = 0x004`
- L30 _public enumerator_ `TransformChanged = 0x008`
- L31 _public enumerator_ `HierarchyChanged = 0x010`
- L33 _public enumerator_ `IndicesUpdated = HierarchyChanged | BonesRemoved`
- L35 _public enumerator_ `SkeletonUpdated = BonesAdded | BonesRenamed | HierarchyChanged`

#### enum `ESkeletonModificationType`  
`enum class ESkeletonModificationType : uint32`  
_L39-52_
- L41 _public enumerator_ `Cancel = 0x000`
- L42 _public enumerator_ `None = 0x001`
- L44 _public enumerator_ `SimpleMerge = 0x002`
- L45 _public enumerator_ `DuplicateAndMerge = 0x004`
- L46 _public enumerator_ `FullMerge = 0x008`
- L47 _public enumerator_ `FullMergeAll = 0x010`
- L49 _public enumerator_ `DeepMerge = DuplicateAndMerge | FullMerge | FullMergeAll`
- L51 _public enumerator_ `DoUpdate = SimpleMerge | DeepMerge`

#### struct `FMirrorOptions`  
`struct FMirrorOptions`  
_L60-81_
- reflection: `USTRUCT(BlueprintType)`
- L65 _public member_ `TEnumAsByte<EAxis::Type> MirrorAxis = EAxis::X;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mirror")`
- L68 _public member_ `bool bMirrorRotation = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mirror")`
- L71 _public member_ `FString LeftString = TEXT("_l"` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mirror")`
- L74 _public member_ `FString RightString = TEXT("_r"` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mirror")`
- L77 _public member_ `bool bMirrorChildren = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mirror")`
- L79 _public prototype_ `FTransform MirrorTransform(const FTransform& InGlobalTransform) const;`
- L80 _public prototype_ `FVector MirrorVector(const FVector& InVector) const;`

#### enum `EOrientAxis`  
`enum class EOrientAxis : uint8`  
_L88-97_
- reflection: `UENUM()`
- L90 _public enumerator_ `None`
- L91 _public enumerator_ `PositiveX UMETA(DisplayName = "+X", ToolTip = "Orients axis in the positive X direction")`
- L92 _public enumerator_ `PositiveY UMETA(DisplayName = "+Y", ToolTip = "Orients axis in the positive Y direction")`
- L93 _public enumerator_ `PositiveZ UMETA(DisplayName = "+Z", ToolTip = "Orients axis in the positive Z direction")`
- L94 _public enumerator_ `NegativeX UMETA(DisplayName = "-X", ToolTip = "Orients axis in the negative X direction")`
- L95 _public enumerator_ `NegativeY UMETA(DisplayName = "-Y", ToolTip = "Orients axis in the negative Y direction")`
- L96 _public enumerator_ `NegativeZ UMETA(DisplayName = "-Z", ToolTip = "Orients axis in the negative Z direction")`

#### struct `FOrientOptions`  
`struct FOrientOptions`  
_L100-120_
- reflection: `USTRUCT(BlueprintType)`
- L105 _public member_ `EOrientAxis Primary = EOrientAxis::PositiveX;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Orient")`
- L108 _public member_ `EOrientAxis Secondary = EOrientAxis::PositiveY;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Orient", meta=(EditCondition="Primary != EOrientAxis::None"))`
- L111 _public member_ `bool bUsePlaneAsSecondary = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Orient", meta=(EditCondition="Primary != EOrientAxis::None"))`
- L114 _public member_ `FVector SecondaryTarget = FVector::YAxisVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Orient", meta=(EditCondition="Primary != EOrientAxis::None && !bUsePlaneAsSecondary"))`
- L117 _public member_ `bool bOrientChildren = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Orient", meta=(EditCondition="Primary != EOrientAxis::None"))`
- L119 _public prototype_ `FTransform OrientTransform(const FVector& InPrimaryTarget, const FTransform& InTransform) const;`

#### class `USkeletonModifier`  
`class USkeletonModifier : public UObject`  
_L127-320_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L134 _public prototype_ `bool SetSkeletalMesh(USkeletalMesh* InSkeletalMesh);` — `UFUNCTION(BlueprintCallable, Category = "Mesh")`
- L141 _public prototype_ `bool CommitSkeletonToSkeletalMesh();` — `UFUNCTION(BlueprintCallable, Category = "Mesh")` — Applies the skeleton modifications to the skeletal mesh. @return true if commit succeeded.
- L144 _public prototype_ `bool SetDynamicMesh(UDynamicMesh* InDynamicMesh);`
- L146 _public prototype_ `bool SetReferenceSkeleton(const FReferenceSkeleton& InReferenceSkeleton);`
- L148 _public prototype_ `void SetReadOnly(bool bInReadOnly);`
- L149 _public prototype_ `bool IsReadOnly() const;`
- L155 _public prototype_ `bool CommitSkeletonToDynamicMesh();` — Applies the skeleton modifications to the dynamic mesh. @return true if commit succeeded.
- L165 _public prototype_ `bool AddBone(const FName InBoneName, const FName InParentName, const FTransform& InTransform);` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")` — Creates a new bone in the skeleton hierarchy at desired transform @param InBoneName The new bone's name. @param InParentName The new bone parent's name. @param InTransform The default local transform in the parent space. @return \c true if the operation succeeded, false otherwise.
- L167 _public prototype_ `bool AddBones(const TArray<FName>& InBonesName, const TArray<FName>& InParentsName, const TArray<FTransform>& InTransforms);` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")`
- L175 _public prototype_ `bool MirrorBone(const FName InBoneName, const FMirrorOptions& InOptions = FMirrorOptions());` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")` — Mirror bones @param InBoneName The new bone's name. @param InOptions The mirroring options @return \c true if the operation succeeded, false otherwise.
- L177 _public prototype_ `bool MirrorBones(const TArray<FName>& InBonesName, const FMirrorOptions& InOptions = FMirrorOptions());` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")`
- L186 _public prototype_ `bool SetBoneTransform(const FName InBoneName, const FTransform& InNewTransform, const bool bMoveChildren);` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")` — Sets the bone the desired local transform @param InBoneName The new bone's name that needs to be moved. @param InNewTransform The new local transform in the bone's parent space. @param bMoveChildren Propagate new transform to children @return \c true if the operation succeeded, false otherwise.
- L188 _public prototype_ `bool SetBonesTransforms(const TArray<FName>& InBoneNames, const TArray<FTransform>& InNewTransforms, const bool bMoveChildren);` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")`
- L196 _public prototype_ `bool RemoveBone(const FName InBoneName, const bool bRemoveChildren);` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")` — Remove a bone in the skeleton hierarchy @param InBoneName The new bone's name. @param bRemoveChildren Remove children recursively. @return \c true if the operation succeeded, false otherwise.
- L198 _public prototype_ `bool RemoveBones(const TArray<FName>& InBoneNames, const bool bRemoveChildren);` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")`
- L206 _public prototype_ `bool RenameBone(const FName InOldBoneName, const FName InNewBoneName);` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")` — Rename bones @param InOldBoneName The current bone's name. @param InNewBoneName The new bone's name. @return \c true if the operation succeeded, false otherwise.
- L208 _public prototype_ `bool RenameBones(const TArray<FName>& InOldBoneNames, const TArray<FName>& InNewBoneNames);` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")`
- L216 _public prototype_ `bool ParentBone(const FName InBoneName, const FName InParentName);` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")` — Parent bones @param InBoneName The current bone's name. @param InParentName The new parent's name (Name_NONE to unparent). @return \c true if the operation succeeded, false otherwise.
- L218 _public prototype_ `bool ParentBones(const TArray<FName>& InBoneNames, const TArray<FName>& InParentNames);` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")`
- L226 _public prototype_ `bool OrientBone(const FName InBoneName, const FOrientOptions& InOptions = FOrientOptions());` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")` — Align bones @param InBoneName The current bone's name. @param InOptions The orienting options @return \c true if the operation succeeded, false otherwise.
- L228 _public prototype_ `bool OrientBones(const TArray<FName>& InBoneNames, const FOrientOptions& InOptions = FOrientOptions());` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")`
- L236 _public prototype_ `FTransform GetBoneTransform(const FName InBoneName, const bool bGlobal = false) const;` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")` — Get Bone Transform @param InBoneName The current bone's name. @param bGlobal Whether it should return the parent space or global transform @return \c The current bone's transform
- L243 _public prototype_ `FName GetParentName(const FName InBoneName) const;` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")` — Get Parent Name @param InBoneName The current bone's name. @return \c The current bone's parent name
- L251 _public prototype_ `TArray<FName> GetChildrenNames(const FName InBoneName, const bool bRecursive = false) const;` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")` — Get Children Names @param InBoneName The parent's name. @param bRecursive If set to true grand-children will also be added recursively @return \c The children names list
- L257 _public prototype_ `TArray<FName> GetAllBoneNames() const;` — `UFUNCTION(BlueprintCallable, Category = "Skeleton")` — Get All Bone Names @return \c All bone names list
- L261 _public prototype_ `void ExternalUpdate(const FReferenceSkeleton& InRefSkeleton, const TArray<int32>& InIndexTracker);`
- L262 _public prototype_ `void ExternalUpdate(const FReferenceSkeleton& InRefSkeleton);`
- L264 _public prototype_ `FName GetUniqueName(const FName InBoneName, const TArray<FName>& InBoneNames = {}) const;`
- L266 _public prototype_ `const FReferenceSkeleton& GetReferenceSkeleton() const;`
- L267 _public prototype_ `const TArray<int32>& GetBoneIndexTracker() const;`
- L269 _public prototype_ `const FTransform& GetTransform(const int32 InBoneIndex, const bool bGlobal = false) const;`
- L273 _private prototype_ `bool IsReferenceSkeletonValid(const bool bLog = true) const;`
- L275 _private prototype_ `void UpdateBoneTracker(const TArray<FMeshBoneInfo>& InOtherInfos);`
- L278 _private prototype_ `void GetBonesToMirror(const TArray<FName>& InBonesName, const FMirrorOptions& InOptions, TArray<int32>& OutBonesToMirror) const;` — mirroring functions
- L279 _private prototype_ `void GetMirroredNames(const TArray<int32>& InBonesToMirror, const FMirrorOptions& InOptions, TArray<FName>& OutBonesName) const;`
- L280 _private prototype_ `void GetMirroredBones(const TArray<int32>& InBonesToMirror, const TArray<FName>& InMirroredNames, TArray<int32>& OutMirroredBones);`
- L281 _private prototype_ `void GetMirroredTransforms( const TArray<int32>& InBonesToMirror, const TArray<int32>& InMirroredBones, const FMirrorOptions& InOptions, TArray<FTransform>& OutMirroredTransforms) const;`
- L285 _private prototype_ `void GetBonesToOrient(const TArray<FName>& InBonesName, const FOrientOptions& InOptions, TArray<int32>& OutBonesToOrient) const;` — orient function
- L288 _private prototype_ `ESkeletalMeshModificationType PreCommitSkeletalMesh();` — pre/post commit
- L289 _private prototype_ `ESkeletonModificationType PreCommitSkeleton(const ESkeletalMeshModificationType InSkeletalMeshModifications) const;`
- L290 _private prototype_ `void PostCommitSkeleton(const ESkeletonModificationType InSkeletonModifications) const;`
- L292 _private prototype_ `void EnsureSingleRoot();`
- L295 _private prototype_ `bool HasAnyOtherReferences(const bool bSkeletalMeshOnly) const;` — does the skeleton have any references other than the skeletal mesh currently being edited
- L298 _private prototype_ `void CommitChangesToMeshDescription(const ESkeletalMeshModificationType InSkeletalMeshModifications);` — update mesh description on commit
- L301 _private prototype_ `void NotifyFromSkeletonChanges() const;` — notification
- L304 _private member_ `TWeakObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;` — `UPROPERTY(transient)`
- L306 _private member_ `TUniquePtr<FMeshDescription> MeshDescription;`
- L309 _private member_ `TWeakObjectPtr<UDynamicMesh> WeakDynamicMesh = nullptr;` — `UPROPERTY(transient)`
- L311 _private member_ `TUniquePtr<FReferenceSkeleton> ReferenceSkeleton;`
- L312 _private member_ `TUniquePtr<FTransformComposer> TransformComposer;`
- L313 _private member_ `TArray<int32> BoneIndexTracker;`
- L314 _private member_ `bool bReadOnly = false;`
- L319 _public member_ `bool bDebug = false;` — `UPROPERTY(EditAnywhere, Category = Debug)`

#### struct `FTransformComposer`  
`struct FTransformComposer`  
_L322-375_
- L324 _public function_ `FTransformComposer(const FReferenceSkeleton& InRefSkeleton) : RefSkeleton(InRefSkeleton) , Transforms(InRefSkeleton.GetRawRefBonePose())`
- L331 _public function_ `const FTransform& GetGlobalTransform(const uint32 Index)`
- L353 _public function_ `void Invalidate(const uint32 Index = INDEX_NONE)`
- L372 _public member_ `const FReferenceSkeleton& RefSkeleton;`
- L373 _public member_ `TArray<FTransform> Transforms;`
- L374 _public member_ `TBitArray<> TransformCached;`

#### enum `ESKeletalMeshMergeType`  
`enum class ESKeletalMeshMergeType : uint8`  
_L378-382_
- reflection: `UENUM()`
- L380 _public enumerator_ `New UMETA(ToolTip = "Create a new skeleton asset from the current changes.")`
- L381 _public enumerator_ `Merge UMETA(ToolTip = "Merge the current changes to the existing skeleton asset. Note that this may invalidate dependent assets, such as animation clips, pose assets and animation blueprints.")`

#### class `USkeletalMeshMergeOptions`  
`class USkeletalMeshMergeOptions : public UObject`  
_L385-398_
- reflection: `UCLASS(HideCategories=Object, MinimalAPI)`
- inherits: `UObject`
- L393 _public member_ `ESKeletalMeshMergeType MergeType = ESKeletalMeshMergeType::New;` — `UPROPERTY(EditAnywhere, Category="Merge")` — Changes merge type (New or Merge)
- L397 _public member_ `bool bMergeAll = false;` — `UPROPERTY(EditAnywhere, Category="Merge", meta=(EditCondition="MergeType==ESKeletalMeshMergeType::Merge"))` — Also apply the changes to the skeletal meshes referencing the same skeleton

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SKELETALMESHMODIFIERS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/SkeletalMeshModifiers/Public/SkinWeightModifier.h` (Public)


#### class `USkinWeightModifier`  
`class USkinWeightModifier : public UObject`  
_L64-189_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: API used to modify skin weights on a Skeletal Mesh asset. To use: 1. Instantiate an instance of USkinWeightModifier 2. Call "SetSkeletalMesh(MyMeshAsset)", passing in the skeletal mesh you want to edit weights on 3. Use Get/Set weights functions, and Normalize/Prune to edit the weights as desired 4. When ready to commit to the asset, call CommitWeightsToSkeletalMesh() and save the asset if desired This API can be used from C++, Blueprint or Python. Here is a sample usage of the API in Python: import unreal # create a weight modifier for a given skeletal mesh skel_mesh = unreal.EditorAssetLibrary().load_asset("/Game/Characters/Wolf/Meshes/SK_Wolf") weight_modifier = unreal.SkinWeightModifier() weight_modifier.set_skeletal_mesh(skel_mesh) # get weight of vertex 1234 vertex_weights = weight_modifier.get_vertex_weights(1234) print(vertex_weights) # remove neck2 as an influence on this vertex vertex_weights.pop("neck2") weight_modifier.set_vertex_weights(vertex_weights, True) print(vertex_weights) # commit change to the skeletal mesh weight_modifier.commit_weights_to_skeletal_mesh() OUTPUT: {"head": 0.6, "neck1": 0.3, "neck2": 0.1} {"head": 0.6, "neck1": 0.3} In Python, the per-vertex weights are stored as a dictionary mapping Bone Names to float weight values. The "SetVertexWeights()" function expects the same data structure. You can add/remove/edit influences as needed. The SetVertexWeights() function does not normalize the weights. So you can make multiple modifications and cal
- L76 _public prototype_ `bool SetSkeletalMesh(USkeletalMesh* InMesh);` — `UFUNCTION(BlueprintCallable, Category = "Mesh")` — Call this first to load the weights for a skeletal mesh for fast editing. @param InMesh - The skeletal mesh asset to load for weight editing @return bool - true if the mesh weights were successfully loaded.
- L84 _public prototype_ `bool CommitWeightsToSkeletalMesh();` — `UFUNCTION(BlueprintCallable, Category = "Mesh")` — Actually applies the weight modifications to the skeletal mesh. This action creates an undo transaction. The skeletal mesh asset will be dirtied, but it is up to the user to save the asset if required. @return true if weights were applied to a skeletal mesh, false otherwise
- L91 _public function_ `USkeletalMesh* GetSkeletalMesh()` — `UFUNCTION(BlueprintCallable, Category = "Mesh")` — Get a reference to the skeletal mesh that was loaded @return USkeletalMesh* - the mesh that was loaded, or null
- L98 _public prototype_ `int32 GetNumVertices();` — `UFUNCTION(BlueprintCallable, Category = "Mesh Query")` — Get the total number of vertices in the skeletal mesh. @return int, number of vertices
- L105 _public prototype_ `TArray<FName> GetAllBoneNames();` — `UFUNCTION(BlueprintCallable, Category = "Mesh Query")` — Get an array of all bone names in the skeletal mesh. @return array of bone names
- L113 _public prototype_ `TMap<FName, float> GetVertexWeights(const int32 VertexID);` — `UFUNCTION(BlueprintCallable, Category = "Weights")` — Get all bone weights for a single vertex. @param VertexID the index of the vertex @return a map of Bone Name to weight values for all bones that influence the specified vertex.
- L123 _public prototype_ `bool SetVertexWeights( const int32 VertexID, const TMap<FName, float>& InWeights, const bool bReplaceAll=false);` — `UFUNCTION(BlueprintCallable, Category = "Weights")` — Set bone weights for a single vertex. The weights are stored as supplied and not normalized until either "CommitWeightsToSkeletalMesh()" or "NormalizeVertexWeights()" is called. @param VertexID the index of the vertex @param InWeights a map of Bone-Name to Weight for all bones that influence the specified vertex, ie {"Head": 0.6, "Neck": 0.4} @param bReplaceAll if true, all weights on this vertex will be replaced with the input weights. Default is false.
- L134 _public prototype_ `bool NormalizeVertexWeights(const int32 VertexID);` — `UFUNCTION(BlueprintCallable, Category = "Weights")` — Normalize weights on the specified vertex. @param VertexID the index of the vertex to normalize weights on @return true if normalization was performed, false otherwise
- L141 _public prototype_ `bool NormalizeAllWeights();` — `UFUNCTION(BlueprintCallable, Category = "Weights")` — Normalize weights on all vertices in the mesh. @return true if normalization was performed, false otherwise
- L150 _public prototype_ `bool EnforceMaxInfluences(const int32 MaxInfluences=-1);` — `UFUNCTION(BlueprintCallable, Category = "Weights")` — Strips out smallest influences to ensure each vertex does not have weight on more influences than MaxInfluences. Influences with the smallest weight are culled first. @param MaxInfluences The maximum number of influences to allow for each vertex in the mesh. If -1 is passed, will use the project-wide MaxInfluences amount. @return true if influences were removed, false otherwise
- L160 _public prototype_ `bool PruneVertexWeights(const int32 VertexID, const float WeightThreshold);` — `UFUNCTION(BlueprintCallable, Category = "Weights")` — Remove all weights below the given threshold value, on the given vertex. Influences that are pruned will no longer receive weight from normalization. @param VertexID the index of the vertex to prune weights on @param WeightThreshold vertex weights below this value will be removed. @return true if influences were removed, false otherwise
- L168 _public prototype_ `bool PruneAllWeights(const float WeightThreshold);` — `UFUNCTION(BlueprintCallable, Category = "Weights")` — Remove all weights below the given threshold value, on all vertices. @param WeightThreshold vertex weights below this value will be removed. @return true if influences were removed, false otherwise
- L174 _private member_ `TObjectPtr<USkeletalMesh> Mesh;` — `UPROPERTY()` — the skeletal mesh that was loaded by SetSkeletalMesh
- L175 _private member_ `TUniquePtr<FMeshDescription> MeshDescription;`
- L178 _private member_ `TArray<TMap<FName, float>> Weights;` — weights stored in-memory for editing before being committed to the skeletal mesh
- L181 _private prototype_ `bool NormalizeVertexInternal(const int32 VertexID);` — fast internal procedures (do not validate inputs)
- L182 _private prototype_ `void EnforceMaxInfluenceInternal(const int32 VertexID, const int32 Max);`
- L183 _private prototype_ `bool PruneVertexWeightInternal(const int32 VertexID, const float WeightThreshold);`
- L186 _private prototype_ `void Reset();` — reset all internal data when loading a new mesh
- L188 _private member_ `static constexpr int32 LODIndex = 0;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SKELETALMESHMODIFIERS_API`
