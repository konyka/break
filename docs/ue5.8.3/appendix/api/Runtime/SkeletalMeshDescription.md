# Runtime / SkeletalMeshDescription

- module root: `Source/Runtime/SkeletalMeshDescription`
- headers: 5; symbols: 212
- symbol kinds: class=9, delegate=1, externvar=9, function=53, member=16, namespace=6, prototype=92, struct=5, typedef=21
- PrivateIncludePathModuleNames: GeometryCore, MeshConversion
- PublicDependencyModuleNames: Core, CoreUObject, MeshDescription, StaticMeshDescription
- PublicIncludePathModuleNames: AnimationCore, Engine

### `Source/Runtime/SkeletalMeshDescription/Public/SkeletalMeshAttributes.h` (Public)


#### class `FSkeletalMeshAttributesShared`  
`class FSkeletalMeshAttributesShared`  
_L51-225_
- L54 _public typedef_ `using FBoneArray = TMeshElementContainer<FBoneID>;`
- L56 _public typedef_ `using FBoneNameAttributesRef = TMeshAttributesRef<FBoneID, FName>;`
- L57 _public typedef_ `using FBoneNameAttributesConstRef = TMeshAttributesConstRef<FBoneID, FName>;`
- L59 _public typedef_ `using FBoneParentIndexAttributesRef = TMeshAttributesRef<FBoneID, int32>;`
- L60 _public typedef_ `using FBoneParentIndexAttributesConstRef = TMeshAttributesConstRef<FBoneID, int32>;`
- L62 _public typedef_ `using FBonePoseAttributesRef = TMeshAttributesRef<FBoneID, FTransform>;`
- L63 _public typedef_ `using FBonePoseAttributesConstRef = TMeshAttributesConstRef<FBoneID, FTransform>;`
- L65 _public typedef_ `using FBoneColorAttributesRef = TMeshAttributesRef<FBoneID, FVector4f>;`
- L66 _public typedef_ `using FBoneColorAttributesConstRef = TMeshAttributesConstRef<FBoneID, FVector4f>;`
- L68 _public typedef_ `using FSourceGeometryPartArray = TMeshElementContainer<FSourceGeometryPartID>;`
- L70 _public typedef_ `using FSourceGeometryPartNameRef = TMeshAttributesRef<FSourceGeometryPartID, FName>;`
- L71 _public typedef_ `using FSourceGeometryPartNameConstRef = TMeshAttributesConstRef<FSourceGeometryPartID, FName>;`
- L73 _public typedef_ `using FSourceGeometryPartVertexOffsetAndCountRef = TMeshAttributesRef<FSourceGeometryPartID, TArrayView<int32>>;`
- L74 _public typedef_ `using FSourceGeometryPartVertexOffsetAndCountConstRef = TMeshAttributesConstRef<FSourceGeometryPartID, TArrayView<int32>>;`
- L83 _public member_ `static FName BonesElementName;` — Name of the mesh element type representing bones. @note this is different from the MeshAttribute::Bone::Name attribute. This is a name of the element that is added to the  mesh description to represent Bones (similar to the Vertex/Polygons/Edges elements). MeshAttribute::Bone::Name is just one of the attributes of the Bones element.
- L91 _public member_ `static FName SourceGeometryPartElementName;` — Name of the mesh element representing import data for meshes that were imported from separate geometries into a single skeletal mesh piece. Can be used to match parts of the mesh back to the constituent parts of the import source.
- L95 _public member_ `static FName DefaultSkinWeightProfileName;` — The name of the default skin weight profile.
- L97 _public prototype_ `FSkeletalMeshAttributesShared(const FMeshDescription& InMeshDescription);`
- L102 _public function_ `TPolygonGroupAttributesConstRef<int32> GetPolygonGroupParents() const` — Returns the parent polygon group read-only attribute.
- L112 _public prototype_ `TArray<FName> GetSkinWeightProfileNames(const bool bInUserDefinedOnly = false) const;` — Returns the list of all registered skin weight profile names on this mesh. \param bInUserDefinedOnly Only return user-defined profiles, not the default profile. \return The list of the profile names.
- L116 _public prototype_ `static bool IsValidSkinWeightProfileName(const FName InProfileName);` — Returns \c true if the given identifier is a valid profile name. If the name is empty, or matches the default profile, then the profile name is considered invalid.
- L119 _public prototype_ `static bool IsSkinWeightAttribute(const FName InAttributeName);` — Helper function that indicates whether an attribute name represents a skin weight attribute.
- L123 _public prototype_ `static FName GetProfileNameFromAttribute(const FName InAttributeName);` — Returns a skin profile name from the attribute name, if the attribute name is a valid skin weights attribute.
- L125 _public prototype_ `FSkinWeightsVertexAttributesConstRef GetVertexSkinWeights(const FName InProfileName = NAME_None) const;`
- L127 _public prototype_ `FSkinWeightsVertexAttributesConstRef GetVertexSkinWeightsFromAttributeName(const FName InAttributeName = NAME_None) const;`
- L134 _public prototype_ `TArray<FName> GetMorphTargetNames() const;` — Returns the list of all registered morph targets on this mesh.
- L137 _public prototype_ `static bool IsMorphTargetAttribute(const FName InAttributeName);` — Returns \c true if the given attribute name refers to a morph target attribute.
- L140 _public prototype_ `static FName GetMorphTargetNameFromAttribute(const FName InAttributeName);` — Returns the name of a morph target given the attribute name. If the given attribute name is invalid, \c NAME_None is returned.
- L144 _public prototype_ `TVertexAttributesConstRef<FVector3f> GetVertexMorphPositionDelta(const FName InMorphTargetName) const;` — Returns a read-only vertex position delta attribute for the given morph target. The delta is the difference between the point position of the mesh and the point position of the morphed mesh. Adding this value to the point position of the mesh will return the morph point position.
- L150 _public prototype_ `TVertexInstanceAttributesConstRef<FVector3f> GetVertexInstanceMorphNormalDelta(const FName InMorphTargetName) const;` — Returns a read-only vertex instance normal delta attribute for the given morph target. The delta is the difference between the normal vector of the mesh and the normal vector of the desired morphed mesh. Adding this value to the normal vector of the mesh will return the morph's normal vector for this vertex instance. If the morph was not registered to include normals, this will return an invalid attribute.
- L152 _public prototype_ `bool HasMorphTargetPositionsAttribute(const FName InMorphTargetName) const;`
- L154 _public prototype_ `bool HasMorphTargetNormalsAttribute(const FName InMorphTargetName) const;`
- L160 _public prototype_ `bool HasBoneColorAttribute() const;`
- L162 _public prototype_ `bool HasBoneNameAttribute() const;`
- L164 _public prototype_ `bool HasBonePoseAttribute() const;`
- L166 _public prototype_ `bool HasBoneParentIndexAttribute() const;`
- L168 _public prototype_ `const FBoneArray& Bones() const;`
- L170 _public prototype_ `const TAttributesSet<FBoneID>& BoneAttributes() const;`
- L173 _public function_ `bool HasBones() const` — @return true, if bone element was added to the MeshDescription.
- L179 _public prototype_ `int32 GetNumBones() const;` — @return the number of the bones. 0 if bone element does not exist in the FMeshDescription.
- L182 _public prototype_ `bool IsBoneValid(const FBoneID BoneID) const;` — @return true, if the passed bone ID is valid
- L184 _public prototype_ `FBoneNameAttributesConstRef GetBoneNames() const;`
- L186 _public prototype_ `FBoneParentIndexAttributesConstRef GetBoneParentIndices() const;`
- L188 _public prototype_ `FBonePoseAttributesConstRef GetBonePoses() const;`
- L190 _public prototype_ `FBoneColorAttributesConstRef GetBoneColors() const;`
- L194 _public function_ `bool HasSourceGeometryParts() const`
- L199 _public prototype_ `const FSourceGeometryPartArray& SourceGeometryParts() const;`
- L201 _public prototype_ `const TAttributesSet<FSourceGeometryPartID>& SourceGeometryPartAttributes() const;`
- L203 _public prototype_ `int32 GetNumSourceGeometryParts() const;`
- L205 _public prototype_ `bool IsSourceGeometryPartValid(const FSourceGeometryPartID InSourceGeometryPartID) const;`
- L207 _public prototype_ `FSourceGeometryPartNameConstRef GetSourceGeometryPartNames() const;`
- L209 _public prototype_ `FSourceGeometryPartVertexOffsetAndCountConstRef GetSourceGeometryPartVertexOffsetAndCounts() const;`
- L215 _protected prototype_ `static FName CreateSkinWeightAttributeName(const FName InProfileName);` — Construct a name for a skin weight attribute with the given skin weight profile name. Each mesh description can hold different skin weight profiles, although the default is always present.
- L218 _protected prototype_ `static FName CreateMorphTargetAttributeName(const FName InMorphTargetName);` — Construct a name for a morph target attribute with the given a user-visible morph target name.
- L220 _protected member_ `const FMeshElementChannels* BoneElementsShared = nullptr;`
- L221 _protected member_ `const FMeshElementChannels* SourceGeometryPartElementsShared = nullptr;`
- L224 _private member_ `const FMeshDescription& MeshDescriptionShared;`

#### class `FSkeletalMeshAttributes`  
`class FSkeletalMeshAttributes : public FStaticMeshAttributes, public FSkeletalMeshAttributesShared`  
_L228-383_
- inherits: `FStaticMeshAttributes,FSkeletalMeshAttributesShared`
- L234 _public prototype_ `explicit FSkeletalMeshAttributes(FMeshDescription& InMeshDescription);`
- L236 _public prototype_ `virtual void Register(bool bKeepExistingAttribute = false) override;`
- L241 _public function_ `static bool IsReservedAttributeName(const FName InAttributeName)` — Returns \c true if a given attribute name is a name for a reserved attribute or not. If not a reserved attribute, it's one that has been user-defined and is not required by any system.
- L259 _public prototype_ `bool RegisterImportPointIndexAttribute();` — Register an attribute that can be used to maintain a relationship between a given vertex and the point it originated from on the original imported mesh. This can be useful when trying to match the stored mesh to the import mesh as stored in the import file (e.g. FBX, Alembic, glTF, etc).
- L265 _public prototype_ `void UnregisterImportPointIndexAttribute();` — Convenience function to unregister the attribute that maintains the relationship between a given vertex and the originating point on the import mesh. Use if updating the mesh description but no longer maintaining this relationship (e.g. the topology changed and so this map cannot possibly be accurate).
- L272 _public prototype_ `bool RegisterPolygonGroupParentAttribute();` — Register an attribute on the polygon group that can be used for polygon groups that have been split to indicate which group they got split off from. @see FSkeletalMeshOperations::PartitionByMaximumUniqueBoneIndexCount
- L277 _public function_ `TPolygonGroupAttributesRef<int32> GetPolygonGroupParents()` — Returns the parent polygon group attribute.
- L286 _public prototype_ `bool RegisterSkinWeightAttribute(const FName InProfileName);` — Register a new skin weight profile with the given name. The attribute name will encode the profile name and it will be listed in GetSkinWeightProfileNames(). Returns \c true if the profile was successfully registered. Returns \c false if the attribute was already registered or if IsValidSkinWeightProfileName() returned false.
- L291 _public prototype_ `bool UnregisterSkinWeightAttribute(const FName InProfileName);` — Unregister an existing skin weight profile with the given name Returns \c true if theprofile was successfully unregistered. Returns \c false if the attribute wasn't registered or if \c InProfileName is empty.
- L294 _public prototype_ `FSkinWeightsVertexAttributesRef GetVertexSkinWeights(const FName InProfileName = NAME_None);` — Returns the skin weight profile given by its name. NAME_None corresponds to the default profile.
- L296 _public prototype_ `FSkinWeightsVertexAttributesRef GetVertexSkinWeightsFromAttributeName(const FName InAttributeName = NAME_None);`
- L310 _public prototype_ `bool RegisterMorphTargetAttribute(const FName InMorphTargetName, const bool bIncludeNormals);` — Register a new morph target with the given name. The attribute name will encode the user-defined morph target name and it will be listed in GetMorphTargetNames(). Returns \c true if the morph target was successfully registered. Returns \c false if the attribute was already registered or if \c InMorphTargetName is empty. The position delta is stored as a vertex attributes, and the optional normal is stored as a vertex instance attribute to allow for hard edges on morph targets. \param InMorphTargetName The name of the morph target to add. Cannot be empty. \param bIncludeNormals Set to \c true if per-vertex instance normals (Z-tangent) should be included. Otherwise the normals will be automatically computed and only the position delta vertex attribute registered.
- L315 _public prototype_ `bool UnregisterMorphTargetAttribute(const FName InMorphTargetName);` — Unregister an existing morph target with the given name (as returned by GetMorphTargetNames()). Returns \c true if the morph target was successfully unregistered. Returns \c false if the attribute wasn't registered or if \c InMorphTargetName is empty.
- L319 _public prototype_ `TVertexAttributesRef<FVector3f> GetVertexMorphPositionDelta(const FName InMorphTargetName);` — Returns a writable vertex position delta attribute for the given morph target. The delta is the difference between the point position of the mesh and the point position of the morphed mesh. Adding this value to the point position of the mesh will return the morph point position.
- L325 _public prototype_ `TVertexInstanceAttributesRef<FVector3f> GetVertexInstanceMorphNormalDelta(const FName InMorphTargetName);` — Returns a writable vertex instance normal delta attribute for the given morph target. The delta is the difference between the normal vector of the mesh and the normal vector of the desired morphed mesh. Adding this value to the normal vector of the mesh will return the morph's normal vector for this vertex instance. If the morph was not registered to include normals, this will return an invalid attribute.
- L332 _public prototype_ `void RegisterColorAttribute();` — Register an optional color attribute for bones
- L334 _public prototype_ `FBoneArray& Bones();`
- L336 _public prototype_ `TAttributesSet<FBoneID>& BoneAttributes();`
- L339 _public prototype_ `void ReserveNewBones(const int InNumBones);` — Reserves space for this number of new bones
- L342 _public prototype_ `FBoneID CreateBone();` — Adds a new bone and returns its ID
- L345 _public prototype_ `void CreateBone(const FBoneID BoneID);` — Adds a new bone  with the given ID
- L348 _public prototype_ `void DeleteBone(const FBoneID BoneID);` — Deletes a bone with the given ID
- L350 _public prototype_ `FBoneNameAttributesRef GetBoneNames();`
- L352 _public prototype_ `FBoneParentIndexAttributesRef GetBoneParentIndices();`
- L354 _public prototype_ `FBonePoseAttributesRef GetBonePoses();`
- L356 _public prototype_ `FBoneColorAttributesRef GetBoneColors();`
- L364 _public prototype_ `void RegisterSourceGeometryPartsAttributes();` — This will register the source geometry attributes and their element container on the mesh description so that source geometry part information can be stored.
- L366 _public prototype_ `FSourceGeometryPartArray& SourceGeometryParts();`
- L368 _public prototype_ `TAttributesSet<FSourceGeometryPartID>& SourceGeometryPartAttributes();`
- L370 _public prototype_ `FSourceGeometryPartID CreateSourceGeometryPart();`
- L372 _public prototype_ `void DeleteSourceGeometryPart(FSourceGeometryPartID InSourceGeometryPartID);`
- L374 _public prototype_ `FSourceGeometryPartNameRef GetSourceGeometryPartNames();`
- L376 _public prototype_ `FSourceGeometryPartVertexOffsetAndCountRef GetSourceGeometryPartVertexOffsetAndCounts();`
- L381 _private member_ `FMeshElementChannels* BoneElements = nullptr;`
- L382 _private member_ `FMeshElementChannels* SourceGeometryPartElements = nullptr;`

#### class `FSkeletalMeshConstAttributes`  
`class FSkeletalMeshConstAttributes : public FStaticMeshConstAttributes, public FSkeletalMeshAttributesShared`  
_L386-397_
- inherits: `FStaticMeshConstAttributes,FSkeletalMeshAttributesShared`
- L392 _public function_ `explicit FSkeletalMeshConstAttributes(const FMeshDescription& InMeshDescription) : FStaticMeshConstAttributes(InMeshDescription), FSkeletalMeshAttributesShared(InMeshDescription)`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace MeshAttribute`
- L22 _namespace_ `namespace Vertex` (scope `MeshAttribute`)
- L25 _externvar_ `extern const FName SkinWeights;` (scope `MeshAttribute::Vertex`) — Name of the default skin weights attribute.
- L27 _externvar_ `extern const FName ImportPointIndex;` (scope `MeshAttribute::Vertex`)
- L30 _namespace_ `namespace PolygonGroup` (scope `MeshAttribute`)
- L32 _externvar_ `extern const FName ParentPolygonGroup;` (scope `MeshAttribute::PolygonGroup`)
- L35 _namespace_ `namespace Bone` (scope `MeshAttribute`)
- L37 _externvar_ `extern const FName Name;` (scope `MeshAttribute::Bone`)
- L38 _externvar_ `extern const FName ParentIndex;` (scope `MeshAttribute::Bone`)
- L39 _externvar_ `extern const FName Pose;` (scope `MeshAttribute::Bone`)
- L40 _externvar_ `extern const FName Color;` (scope `MeshAttribute::Bone`)
- L43 _namespace_ `namespace SourceGeometryPart` (scope `MeshAttribute`)
- L45 _externvar_ `extern const FName Name;` (scope `MeshAttribute::SourceGeometryPart`)
- L46 _externvar_ `extern const FName VertexOffsetAndCount;` (scope `MeshAttribute::SourceGeometryPart`)

### `Source/Runtime/SkeletalMeshDescription/Public/SkeletalMeshDescription.h` (Public)


#### class `USkeletalMeshDescription`  
`class USkeletalMeshDescription : public UMeshDescriptionBase`  
_L12-29_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UMeshDescriptionBase`
- L17 _public prototype_ `virtual void RegisterAttributes() override;`
- L19 _public function_ `virtual FSkeletalMeshAttributes& GetRequiredAttributes() override`
- L24 _public function_ `virtual const FSkeletalMeshAttributes& GetRequiredAttributes() const override`

### `Source/Runtime/SkeletalMeshDescription/Public/SkeletalMeshElementTypes.h` (Public)


#### struct `FBoneID`  
`struct FBoneID : public FElementID`  
_L10-32_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FElementID`
- L14 _public function_ `FBoneID()`
- L18 _public function_ `FBoneID( const FElementID InitElementID ) : FElementID( InitElementID.GetValue() )`
- L23 _public function_ `FBoneID( const int32 InitIDValue ) : FElementID( InitIDValue )`

#### struct `FSourceGeometryPartID`  
`struct FSourceGeometryPartID : public FElementID`  
_L35-55_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FElementID`
- L39 _public prototype_ `FSourceGeometryPartID() = default;`
- L41 _public function_ `explicit FSourceGeometryPartID( const FElementID InitElementID ) : FElementID( InitElementID.GetValue() )`
- L46 _public function_ `explicit FSourceGeometryPartID( const int32 InitIDValue ) : FElementID( InitIDValue )`

#### Free symbols / members of external scopes

- L28 _function_ `friend uint32 GetTypeHash( const FBoneID& Other )`
- L51 _function_ `friend uint32 GetTypeHash( const FSourceGeometryPartID& Other )`

### `Source/Runtime/SkeletalMeshDescription/Public/SkeletalMeshOperations.h` (Public)


#### class `FSkeletalMeshOperations`  
`class FSkeletalMeshOperations : public FStaticMeshOperations`  
_L21-274_
- inherits: `FStaticMeshOperations`
- L35 _public prototype_ `static void AppendSkinWeight(const FMeshDescription& SourceMesh, FMeshDescription& TargetMesh, FSkeletalMeshAppendSettings& AppendSettings);`
- L48 _public prototype_ `static bool CopySkinWeightAttributeFromMesh( const FMeshDescription& InSourceMesh, FMeshDescription& InTargetMesh, const FName InSourceProfile, const FName InTargetProfile, const TMap<int32, int32>* SourceBoneIndexToTargetBoneIndexMap );` — Copies skin weight attribute from one mesh to another. Assumes the two geometries are identical or near-identical. Uses closest triangle on the target mesh to interpolate skin weights to each of the points on the target mesh. Attributes for the given profiles on both meshes should exist in order for this function to succeed. @param InSourceMesh The mesh to copy skin weights from. @param InTargetMesh The mesh to copy skin weights to. @param InSourceProfile The name of the skin weight profile on the source mesh to read from. @param InTargetProfile The name of the skin weight profile on the target mesh to write to. @param SourceBoneIndexToTargetBoneIndexMap An optional mapping table to map bone indexes on the source mesh to the target mesh. The table needs to be complete for all the source bone indexes to valid target bone indexes, otherwise the behavior is undefined. If the table is not given, the bone indexes on the source and target meshes are assumed to be the same.
- L65 _public prototype_ `static bool RemapBoneIndicesOnSkinWeightAttribute( FMeshDescription& InMesh, TConstArrayView<int32> InBoneIndexMapping );` — Remaps the bone indices on all skin weight attributes from one index to another. The array view should contain a full mapping of all the bone indices contained in the skin weights. The array is indexed by the current bone index and the value at that index is the new bone index. If the mapping is incomplete or if two entries map to the same bone, the result is undefined. No prior checking is performed. @param InMesh The mesh on which to modify all skin weight attributes to remap their bone indices. @param InBoneIndexMapping The mapping from one bone index to another. The old bone index is used to index into the array, the value at that position is the new bone index. @return true if the operation was successful. If the mapping array was incomplete then this will return false. If there are no skin weight attributes on the mesh, then the operation is still deemed successful.
- L81 _public prototype_ `static bool GetPosedMesh( const FMeshDescription& InSourceMesh, FMeshDescription& OutTargetMesh, TConstArrayView<FTransform> InComponentSpaceTransforms, const FName InSkinWeightProfile = NAME_None, const TMap<FName, float>& InMorphTargetWeights = {} );` — Returns a mesh in the pose given by the component-space transforms passed in. The list of transforms should match exactly the list of bones stored on the mesh. If not, the function fails and returns \c false. If there are no skin weights on the mesh, or the named skin weight profile doesn't exist, the function also returns \c false. The resulting bones on the mesh will have their bone-space transforms updated so that the same mesh can be re-posed as needed. @param InSourceMesh The mesh to deform. @param OutTargetMesh The deformed mesh result. @param InComponentSpaceTransforms The component space transforms used to move the mesh joints for deforming, using linear-blend skinning. @param InSkinWeightProfile The skin weight profile to use as the source of skin weights for the deformation. @param InMorphTargetWeights Optional morph target weights to apply. Any morph target that doesn't exist is ignored. @return \c true if the operation succeeded.
- L101 _public prototype_ `static bool GetPosedMesh( const FMeshDescription& InSourceMesh, FMeshDescription& OutTargetMesh, const TMap<FName, FTransform>& InBoneSpaceTransforms, const FName InSkinWeightProfile = NAME_None, const TMap<FName, float>& InMorphTargetWeights = {} );` — Returns a mesh in the pose given by the bone-space transforms passed in. The transforms simply replace the matching ref pose transforms stored in the bone data on the mesh. Any named transform, that does not match a bone on the mesh, is ignored. If there are no skin weights on the mesh, or the named skin weight profile doesn't exist, the function also returns \c false. The resulting bones on the mesh will have their bone-space transforms updated so that the same mesh can be re-posed as needed. @param InSourceMesh The mesh to deform. @param OutTargetMesh The deformed mesh result. @param InBoneSpaceTransforms A map of named bone-space transforms. @param InSkinWeightProfile The skin weight profile to use as the source of skin weights for the deformation. @param InMorphTargetWeights Optional morph target weights to apply. Any morph target that doesn't exist is ignored. @return \c true if the operation succeeded.
- L121 _public prototype_ `static bool GetPosedMeshInPlace( FMeshDescription& InOutTargetMesh, TConstArrayView<FTransform> InComponentSpaceTransforms, const FName InSkinWeightProfile = NAME_None, const TMap<FName, float>& InMorphTargetWeights = {}, bool bInSkipRecomputeNormalsTangents = false, bool bInWriteBonePose = false );` — Returns a mesh in the pose given by the component-space transforms passed in. The list of transforms should match exactly the list of bones stored on the mesh. If not, the function fails and returns \c false. If there are no skin weights on the mesh, or the named skin weight profile doesn't exist, the function also returns \c false. if bInWriteBonePose is true, the resulting bones on the mesh will have their bone-space transforms updated so that the same mesh can be re-posed as needed. @param InOutTargetMesh rest pose mesh to be deformed in place @param InComponentSpaceTransforms The component space transforms used to move the mesh joints for deforming, using linear-blend skinning. @param InSkinWeightProfile The skin weight profile to use as the source of skin weights for the deformation. @param InMorphTargetWeights Optional morph target weights to apply. Any morph target that doesn't exist is ignored. @param bInSkipRecomputeNormalsTangents skip recompute normals and tangents to improve performance @param bInWriteBonePose whether to write the current bone pose into the mesh description. @return \c true if the operation succeeded.
- L141 _public prototype_ `static bool GetUnposedMesh( const FMeshDescription& InPosedMesh, const FMeshDescription& InRefMesh, TArray<FTransform>& RefBoneTransforms, FMeshDescription& OutUnposedMesh, TConstArrayView<FTransform> InComponentSpaceTransforms, const FName InSkinWeightProfile, const TMap<FName, float>& InMorphTargetWeights );` — Returns the unposed version of the provided posed mesh @param InPosedMesh The posed mesh, @param InRefMesh Ref mesh containing morph target deltas of existing morphs @param RefBoneTransforms Ref component space bone transforms @param OutUnposedMesh The mesh with pose reset to reference @param InComponentSpaceTransforms Current component space bone transforms @param InSkinWeightProfile The skin weight profile to use as the source of skin weights for the deformation. @param InMorphTargetWeights Active morph target weights producing the fully deformed mesh. Don't include the weight of the morph target you want to extract @return \c true if the operation succeeded.
- L161 _public prototype_ `static bool GetUnposedMeshInPlace( FMeshDescription& InOutTargetMesh, const FMeshDescription& InRefMesh, TArray<FTransform>& RefBoneTransforms, TConstArrayView<FTransform> InComponentSpaceTransforms, const FName InSkinWeightProfile, const TMap<FName, float>& InMorphTargetWeights, bool bInWriteBonePose = false );` — Returns the unposed version of the provided posed mesh @param InOutTargetMesh input is the posed mesh, output is the mesh reset to ref pose @param InRefMesh Ref mesh containing morph target deltas of existing morphs @param RefBoneTransforms Ref component space bone transforms @param InComponentSpaceTransforms Current component space bone transforms @param InSkinWeightProfile The skin weight profile to use as the source of skin weights for the deformation. @param InMorphTargetWeights Active morph target weights producing the fully deformed mesh. Don't include the weight of the morph target you want to extract @return \c true if the operation succeeded.
- L174 _public prototype_ `static void ConvertHardEdgesToSmoothMasks(const FMeshDescription& InMeshDescription, TArray<uint32>& OutSmoothMasks);` — A simpler variant of FStaticMeshOperations::ConvertHardEdgesToSmoothGroup that assumes that hard edges always form closed regions.
- L183 _public prototype_ `static void FixVertexInstanceStructure(FMeshDescription& SourceMeshDescription, FMeshDescription& TargetMeshDescription , const TArray<uint32>& SourceSmoothingMasks, TArray<uint32>& TargetFaceSmoothingMasks);` — Helper function to follow behavior generated in FSkeletalMeshImportData::GetMeshDescription, just straight on FMeshDescriptions. FSkeletalMeshImportData::GetMeshDescription makes the VertexInstances a single usage semantics. It also re-orders the vertexInstances to be in a straight increasing sequence, which seems to affect the normal and tangent (FSkeletalMeshOperations::Compute..) generation. (Which means, we can't do the restructuring in place.) For that reason we re-create the MeshDescription into the TargetMeshDescription which is expected to be empty.
- L194 _public prototype_ `static void ValidateFixComputeMeshDescriptionData(FMeshDescription& MeshDescription, const TArray<uint32>& FaceSmoothingMasks, int32 LODIndex, const bool bComputeWeightedNormals, const FString& SkeletalMeshPath);` — Helper function to follow behavior generated in FSkeletalMeshImportData::GetMeshDescription, just straight on FMeshDescriptions It will do the following steps: - ConvertSmoothGroupToHardEdges - ValidateAndFixData - HasInvalidVertexInstanceNormalsOrTangents -> ComputeTriangleTangentsAndNormals - (Re)BuildIndexers
- L204 _public prototype_ `static void ValidateAndFixInfluences(FMeshDescription& MeshDescription, bool& bOutInfluenceCountLimitHit);` — Function will do the following steps on the MeshDescription (SkeletalMeshDescription) : - Sort influences by weight and BoneIndex. - Normalize influence weights. - provide flag if InfluenceCount exceeds MAX_TOTAL_INFLUENCES - Make sure all verts have influences set (if none exist bone 0 with weight 1)
- L215 _public prototype_ `static void ApplyRigToGeo(FMeshDescription& RigMeshDescription , FMeshDescription& GeoMeshDescription );` — Applies the Rig / Skinning found in RigMeshDescription to the Geometry found in GeomeshDescription Desired behavior of this function was targeting FSkeletalMeshImportData::ApplyRigToGeo. Important distinction however: FSkeletalMeshImportData::ApplyRigToGeo seem to work based on VertexInstances, it also checks the VertexCandidate Normal and UVs and only finds the candidate legitimate if they match between Rig and Geo) As Influences (BoneIndex and BoneWeights) are Vertex (NOT VertexInstance) dependent. Whilst original implementation in FSkeletalMeshImportData::ApplyRigToGeo was checking and validating against normals and UVs for NearestWedges, with current implementation we try the NearestVertices with the same principle as the FindMatchingPositionVertexIndexes. (aka based on GetSmallestDeltaBetweenTriangleLists)
- L224 _public prototype_ `static void PruneBoneWeights( FMeshDescription& InOutMeshDescription, const UE::AnimationCore::FBoneWeightsSettings& InBoneWeightSettings, TConstArrayView<FName> InProfileNames = {} );` — Prune the skin weights on the given profiles to match the bone weight settings. @param InOutMeshDescription The mesh description to modify. @param InBoneWeightSettings The bone weight settings to use for controlling the pruning. @param InProfileNames The profile names to prune. If empty, will prune every profile. For only the default profile, use FSkeletalMeshAttributes::DefaultSkinWeightProfileName
- L239 _public prototype_ `static void PartitionByMaximumUniqueBoneIndexCount( FMeshDescription& InOutMeshDescription, const int32 InMaxBoneCount, TConstArrayView<FName> InProfileNames = {} );` — Splits the mesh into further polygon groups if the number of unique bones being bound to by all the triangles in that group exceeds the given maximum bone count. If a split happens, a new polygroup attribute is created ("ParentPolygonGroup") that points to the polygon group ID that the split-off group got created from. @param InOutMeshDescription The mesh to partition. @param InMaxBoneCount The maximum number of unique bones in each group. @param InProfileNames The skin weight profiles to consider. If empty, will consider every profile. For only the default profile, use FSkeletalMeshAttributes::DefaultSkinWeightProfileName
- L258 _public prototype_ `static void RemoveBones( FMeshDescription& InOutMeshDescription, TConstArrayView<FName> InBoneNames, const UE::AnimationCore::FBoneWeightsSettings& InBoneWeightSettings, TConstArrayView<FName> InProfileNames = {} );` — Removes the specified bones, and its children, from the mesh on the given skin weight profiles. If the list of profiles is empty, then the bones are removed from all profiles. Any bones to remove that don't exist on the mesh will be ignored. All weights associated with removed bones are shifted to that bone's parent. If the mesh has no bone attributes, this operation is a no-op and the mesh is left unchanged. @note It is not allowed to remove the root bone. @param InOutMeshDescription The skeletal mesh object to remove bones and bone bindings from. @param InBoneNames The list of bone names to remove. @param InBoneWeightSettings The settings to use when setting the new bone weights. @param InProfileNames The list of skin weight profiles to operate on. If empty, all skin weight profiles will be processed.
- L271 _public prototype_ `static void RemoveUnusedBones( FMeshDescription& InOutMeshDescription );` — Removes any unused bones from the bone attribute list and adjust the parent indices accordingly. All profiles are checked for bones-in-use. @param InOutMeshDescription The skeletal mesh object to remove unused bones from.

#### struct `FSkeletalMeshOperations::FSkeletalMeshAppendSettings`  
`struct FSkeletalMeshAppendSettings`  
_L24-33_
- L26 _public function_ `FSkeletalMeshAppendSettings() : SourceVertexIDOffset(0)`
- L30 _public member_ `int32 SourceVertexIDOffset;`
- L31 _public member_ `TArray<FBoneIndexType> SourceRemapBoneIndex;`
- L32 _public member_ `bool bAppendVertexAttributes = false;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletalMeshOperations, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletalMeshOperations, Log, All);`

### `Source/Runtime/SkeletalMeshDescription/Public/SkinWeightsAttributesRef.h` (Public)


#### struct `Internal::FAttributesRefAdapterConst`  
`struct FAttributesRefAdapterConst`  
_L11-36_
- L13 _public typedef_ `using FBoneWeight = UE::AnimationCore::FBoneWeight;`
- L15 _public typedef_ `using ContainerType = const TArrayAttribute<const int32>;`
- L17 _public function_ `static int32 Num(const ContainerType& InContainer)`
- L22 _public function_ `static FBoneWeight Get(const ContainerType& InContainer, int32 InIndex)`
- L28 _public function_ `template<typename Predicate> static int32 IndexOf(const ContainerType& InContainer, Predicate InPredicate)`

#### struct `Internal::FAttributesRefAdapter`  
`struct FAttributesRefAdapter`  
_L38-93_
- L40 _public typedef_ `using FBoneWeight = UE::AnimationCore::FBoneWeight;`
- L42 _public typedef_ `using ContainerType = TArrayAttribute<int32>;`
- L44 _public function_ `static void SetNum(ContainerType& InContainer, int32 InNum)`
- L49 _public function_ `static int32 Num(const ContainerType& InContainer)`
- L54 _public function_ `static FBoneWeight Get(const ContainerType& InContainer, int32 InIndex)`
- L59 _public function_ `static void Set(ContainerType& InContainer, int32 InIndex, FBoneWeight InBoneWeight)`
- L64 _public function_ `static void Add(ContainerType& InContainer, FBoneWeight InBoneWeight)`
- L69 _public function_ `static void Remove(ContainerType& InContainer, int32 InIndex)`
- L75 _public function_ `template<typename Predicate> static void Sort(ContainerType& InContainer, Predicate InPredicate)`
- L85 _public function_ `template<typename Predicate> static int32 IndexOf(const ContainerType& InContainer, Predicate InPredicate)`

#### class `Internal::TVertexBoneWeightsBase`  
`template<typename AdaptorType, typename StorageType> class TVertexBoneWeightsBase : public UE::AnimationCore::TBoneWeights<AdaptorType>`  
_L97-149_
- inherits: `UE::AnimationCore::TBoneWeights<AdaptorType>`
- L100 _private typedef_ `using Super = UE::AnimationCore::TBoneWeights<AdaptorType>;`
- L102 _public function_ `explicit TVertexBoneWeightsBase(const TArrayAttribute<StorageType> InContainer) : Super(Container), Container(InContainer)`
- L144 _public function_ `const_iterator begin() const`
- L145 _public function_ `const_iterator end() const`
- L148 _private member_ `TArrayAttribute<StorageType> Container;`

#### class `Internal::TVertexBoneWeightsBase::const_iterator`  
`class const_iterator`  
_L108-142_
- desc: For compatibility with range-based for loops.
- L111 _public function_ `const_iterator& operator++()`
- L117 _public function_ `bool operator!=(const const_iterator &InOther) const`
- L122 _public function_ `UE::AnimationCore::FBoneWeight operator*() const`
- L130 _protected prototype_ `const_iterator() = delete;`
- L132 _protected function_ `explicit const_iterator(const TVertexBoneWeightsBase<AdaptorType, StorageType> *InWeights, int32 InIndex) : Weights(InWeights), Index(InIndex)`
- L140 _protected member_ `const TVertexBoneWeightsBase<AdaptorType, StorageType> *Weights = nullptr;`
- L141 _protected member_ `int32 Index = INDEX_NONE;`

#### class `FSkinWeightsVertexAttributesRef`  
`class FSkinWeightsVertexAttributesRef`  
_L158-257_
- desc: Merge these two.
- L161 _public prototype_ `FSkinWeightsVertexAttributesRef() = default;`
- L162 _public prototype_ `FSkinWeightsVertexAttributesRef(const FSkinWeightsVertexAttributesRef &) = default;`
- L163 _public prototype_ `FSkinWeightsVertexAttributesRef(FSkinWeightsVertexAttributesRef &&) noexcept = default;`
- L164 _public function_ `FSkinWeightsVertexAttributesRef& operator=(const FSkinWeightsVertexAttributesRef &InAttributesRef)`
- L170 _public function_ `FSkinWeightsVertexAttributesRef& operator=(FSkinWeightsVertexAttributesRef &&InAttributesRef) noexcept`
- L177 _public function_ `bool IsValid() const`
- L182 _public function_ `FVertexBoneWeights Get(const FVertexID InVertexIndex) const`
- L193 _public function_ `void Set(const FVertexID InVertexIndex, const UE::AnimationCore::FBoneWeights &InWeights)` — Set the weights using properly normalized weights. @param InVertexIndex The vertex index to set these weights at. @param InWeights The normalized weights to set.
- L213 _public function_ `void Set( const FVertexID InVertexIndex, TArrayView<const UE::AnimationCore::FBoneWeight> InWeights, const UE::AnimationCore::FBoneWeightsSettings& InSettings = {} )` — Set bone weights using potentially unnormalized weights. The given weights will be pruned and normalized according to the provided settings. If no settings are provided, default settings will be used. @param InVertexIndex The vertex index to set these weights at. @param InWeights The raw weights to set. @param InSettings Optional settings for pruning and normalization.
- L232 _public function_ `void SetRaw( const FVertexID InVertexIndex, TArrayView<const UE::AnimationCore::FBoneWeight> InWeights )` — Blindly set raw weights. The user is responsible to make sure that the weights are normalized. No checking of normalization, maximum weight count, or minimal weight threshold will be performed. @param InVertexIndex The vertex index to set these weights at. @param InWeights The raw weights to set.
- L250 _protected function_ `FSkinWeightsVertexAttributesRef(TVertexAttributesRef<TArrayAttribute<int32>> InAttributesRef) : AttributesRef(InAttributesRef)`
- L256 _private member_ `TVertexAttributesRef<TArrayAttribute<int32>> AttributesRef;`

#### class `FSkinWeightsVertexAttributesConstRef`  
`class FSkinWeightsVertexAttributesConstRef`  
_L260-314_
- L263 _public prototype_ `FSkinWeightsVertexAttributesConstRef() = default;`
- L264 _public prototype_ `FSkinWeightsVertexAttributesConstRef(const FSkinWeightsVertexAttributesConstRef &) = default;`
- L265 _public prototype_ `FSkinWeightsVertexAttributesConstRef(FSkinWeightsVertexAttributesConstRef &&) noexcept = default;`
- L266 _public function_ `FSkinWeightsVertexAttributesConstRef& operator=(const FSkinWeightsVertexAttributesConstRef &InAttributesRef)`
- L272 _public function_ `FSkinWeightsVertexAttributesConstRef& operator=(FSkinWeightsVertexAttributesConstRef &&InAttributesRef) noexcept`
- L280 _public function_ `explicit FSkinWeightsVertexAttributesConstRef(const FSkinWeightsVertexAttributesRef &InAttribs) : AttributesConstRef(InAttribs.AttributesRef)` — Converting constructors from the non-const variant
- L284 _public function_ `FSkinWeightsVertexAttributesConstRef& operator=(const FSkinWeightsVertexAttributesRef &InAttribs)`
- L290 _public function_ `bool IsValid() const`
- L295 _public function_ `FVertexBoneWeightsConst Get(FVertexID InVertexIndex) const`
- L304 _protected function_ `FSkinWeightsVertexAttributesConstRef(TVertexAttributesRef<TArrayAttribute<int32>> InAttributesConstRef) : AttributesConstRef(InAttributesConstRef)`
- L308 _protected function_ `FSkinWeightsVertexAttributesConstRef(TVertexAttributesRef<TArrayAttribute<const int32>> InAttributesConstRef) : AttributesConstRef(InAttributesConstRef)`
- L313 _private member_ `TVertexAttributesConstRef<TArrayAttribute<int32>> AttributesConstRef;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Internal`
- L31 _function_ `` (scope `Internal::FAttributesRefAdapterConst::IndexOf`)
- L78 _function_ `` (scope `Internal::FAttributesRefAdapter::Sort`)
- L88 _function_ `` (scope `Internal::FAttributesRefAdapter::IndexOf`)
- L153 _typedef_ `using FVertexBoneWeights = Internal::TVertexBoneWeightsBase<Internal::FAttributesRefAdapter, int32>;`
- L154 _typedef_ `using FVertexBoneWeightsConst = Internal::TVertexBoneWeightsBase<Internal::FAttributesRefAdapterConst, const int32>;`
