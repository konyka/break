# Plugins / ChaosClothAsset

- module root: `Plugins/ChaosClothAsset/Source/ChaosClothAsset`
- headers: 15; symbols: 1086
- symbol kinds: class=18, enum=1, enumerator=9, function=212, macro=8, member=114, namespace=50, prototype=558, struct=15, typedef=1, variable=100
- PrivateDependencyModuleNames: ClothingSystemRuntimeCommon, Core, CoreUObject, GeometryCore, MeshConversion, RenderCore

### `Plugins/ChaosClothAsset/Source/ChaosClothAsset/Private/ChaosClothAsset/ClothCollection.h` (Private)


#### class `UE::Chaos::ClothAsset::FConstClothCollection`  
`class FConstClothCollection`  
_L19-376_
- desc: Cloth collection facade data.
- L22 _public member_ `static constexpr int8 MaxNumBoneInfluences = 12;` — This should be <= MAX_TOTAL_INFLUENCES defined in GPUSkinPublicDefs.h
- L23 _public member_ `static constexpr int8 MaxNumTetherAttachments = 4;` — This should be <= FClothTetherDataPrivate::MaxNumAttachments
- L25 _public prototype_ `explicit FConstClothCollection(const TSharedRef<const FManagedArrayCollection>& InManagedArrayCollection);`
- L26 _public prototype_ `~FConstClothCollection() = default;`
- L28 _public prototype_ `FConstClothCollection(const FConstClothCollection&) = delete;`
- L29 _public prototype_ `FConstClothCollection& operator=(const FConstClothCollection&) = delete;`
- L30 _public prototype_ `FConstClothCollection(FConstClothCollection&&) = delete;`
- L31 _public prototype_ `FConstClothCollection& operator=(FConstClothCollection&&) = delete;`
- L34 _public prototype_ `bool IsValid(EClothCollectionExtendedSchemas OptionalSchemas = EClothCollectionExtendedSchemas::None) const;` — Return whether the underlying collection is a valid cloth collection.
- L37 _public prototype_ `int32 GetNumElements(const FName& GroupName) const;` — Get the number of elements of a group.
- L40 _public prototype_ `int32 GetNumElements(const TManagedArray<int32>* StartArray, const TManagedArray<int32>* EndArray, int32 Index) const;` — Get the number of elements of one of the sub groups that have start/end indices.
- L43 _public prototype_ `template<typename T> static inline TConstArrayView<T> GetElements(const TManagedArray<T>* ElementArray, const TManagedArray<int32>* StartArray, const TManagedArray<int32>* EndArray, int32 ArrayIndex);`
- L46 _public prototype_ `template<typename T> static inline TArrayView<T> GetElements(TManagedArray<T>* ElementArray, const TManagedArray<int32>* StartArray, const TManagedArray<int32>* EndArray, int32 ArrayIndex);`
- L49 _public prototype_ `template<typename T> static inline TConstArrayView<T> GetElements(const TManagedArray<T>* ElementArray);`
- L52 _public prototype_ `template<typename T> static inline TArrayView<T> GetElements(TManagedArray<T>* ElementArray);`
- L58 _public prototype_ `static int32 GetElementsOffset(const TManagedArray<int32>* StartArray, int32 BaseElementIndex, int32 ElementIndex);` — Return the difference between the start index of an element to the start index of the first sub-element in the group (base). Usefull for getting back and forth between LOD/pattern indexation modes.
- L66 _public prototype_ `static int32 GetArrayIndexForContainedElement( const TManagedArray<int32>* StartArray, const TManagedArray<int32>* EndArray, int32 ElementIndex);` — Return the ArrayIndex (into StartArray/EndArray) which corresponds with the subarray that contains ElementIndex. Useful for finding which pattern contains a vertex or face index. Returns INDEX_NONE if not found. NOTE: typically we have a small number of patterns (case where this is used), so just doing a linear search since a bisection search would get confused by the empty patterns.
- L71 _public prototype_ `static int32 GetNumSubElements( const TManagedArray<int32>* StartArray, const TManagedArray<int32>* EndArray, const TManagedArray<int32>* StartSubArray, const TManagedArray<int32>* EndSubArray, int32 LodIndex);`
- L79 _public prototype_ `template<typename T> static inline TConstArrayView<T> GetSubElements( const TManagedArray<T>* SubElementArray, const TManagedArray<int32>* StartArray, const TManagedArray<int32>* EndArray, const TManagedArray<int32>* StartSubArray, const TManagedArray<int32>* EndSubArray, int32 ArrayIndex);`
- L88 _public prototype_ `template<typename T> static inline TArrayView<T> GetSubElements( TManagedArray<T>* SubElementArray, const TManagedArray<int32>* StartArray, const TManagedArray<int32>* EndArray, const TManagedArray<int32>* StartSubArray, const TManagedArray<int32>* EndSubArray, int32 ArrayIndex);`
- L97 _public prototype_ `template<bool bStart = true, bool bEnd = true> static TTuple<int32, int32> GetSubElementsStartEnd( const TManagedArray<int32>* StartArray, const TManagedArray<int32>* EndArray, const TManagedArray<int32>* StartSubArray, const TManagedArray<int32>* EndSubArray, int32 ArrayIndex);`
- L107 _public prototype_ `template<typename T> static inline void CopyArrayViewData(const TArrayView<T>& To, const TConstArrayView<T>& From);` — Useful method for copying data between ArrayViews. Putting here for now.
- L110 _public prototype_ `template<typename T UE_REQUIRES(!std::is_array_v<T>)> static inline void CopyArrayViewDataAndApplyOffset(const TArrayView<T>& To, const TConstArrayView<T>& From, const T Offset);`
- L113 _public prototype_ `template<typename T> static inline void CopyArrayViewDataAndApplyOffset(const TArrayView<TArray<T>>& To, const TConstArrayView<TArray<T>>& From, const T Offset);`
- L116 _public prototype_ `template<typename T> static inline uint32 GetElementsTypeHash(const TManagedArray<T>* ElementArray);`
- L120 _public prototype_ `template<typename T UE_REQUIRES(TIsUserAttributeType<T>::Value)> TArray<FName> GetUserDefinedAttributeNames(const FName& GroupName) const;`
- L123 _public prototype_ `template<typename T UE_REQUIRES(TIsUserAttributeType<T>::Value)> bool HasUserDefinedAttribute(const FName& Name, const FName& GroupName) const;`
- L126 _public prototype_ `template<typename T UE_REQUIRES(TIsUserAttributeType<T>::Value)> const TManagedArray<T>* GetUserDefinedAttribute(const FName& Name, const FName& GroupName) const;`
- L128 _public prototype_ `static TArray<FName> GetValidClothCollectionGroupName();`
- L129 _public prototype_ `static bool IsValidClothCollectionGroupName(const FName& GroupName);`
- L130 _public prototype_ `bool IsValidUserDefinedAttributeName(const FName& Name, const FName& GroupName) const;`
- L133 _public function_ `const TManagedArray<FSoftObjectPath>* GetPhysicsAssetSoftObjectPathName() const`
- L134 _public function_ `const TManagedArray<FSoftObjectPath>* GetSkeletalMeshSoftObjectPathName() const`
- L136 _public function_ `const TManagedArray<FString>* GetPhysicsAssetPathName() const` — `UE_DEPRECATED(5.7, "Use GetPhysicsAssetSoftObjectPathName instead")`
- L138 _public function_ `const TManagedArray<FString>* GetSkeletalMeshPathName() const` — `UE_DEPRECATED(5.7, "Use GetSkeletalMeshSoftObjectPathName instead")`
- L139 _public function_ `const TManagedArray<FName>* GetReferenceBoneName() const`
- L140 _public function_ `const TManagedArray<bool>* GetCopyAllUserAttributesToSimModel() const`
- L143 _public function_ `const TManagedArray<FVector3f>* GetSolverGravity() const`
- L144 _public function_ `const TManagedArray<float>* GetSolverAirDamping() const`
- L145 _public function_ `const TManagedArray<int32>* GetSolverSubSteps() const`
- L146 _public function_ `const TManagedArray<float>* GetSolverTimeStep() const`
- L149 _public function_ `const TManagedArray<int32>* GetSeamStitchStart() const`
- L150 _public function_ `const TManagedArray<int32>* GetSeamStitchEnd() const`
- L153 _public function_ `const TManagedArray<FIntVector2>* GetSeamStitch2DEndIndices() const`
- L154 _public function_ `const TManagedArray<int32>* GetSeamStitch3DIndex() const`
- L157 _public function_ `const TManagedArray<FVector3f>* GetFabricBendingStiffness() const`
- L158 _public function_ `const TManagedArray<FVector3f>* GetFabricBucklingStiffness() const`
- L159 _public function_ `const TManagedArray<FVector3f>* GetFabricStretchStiffness() const`
- L160 _public function_ `const TManagedArray<float>* GetFabricBucklingRatio() const`
- L161 _public function_ `const TManagedArray<float>* GetFabricDensity() const`
- L162 _public function_ `const TManagedArray<float>* GetFabricFriction() const`
- L163 _public function_ `const TManagedArray<float>* GetFabricDamping() const`
- L164 _public function_ `const TManagedArray<float>* GetFabricPressure() const`
- L165 _public function_ `const TManagedArray<int32>* GetFabricLayer() const`
- L166 _public function_ `const TManagedArray<float>* GetFabricCollisionThickness() const`
- L169 _public function_ `const TManagedArray<int32>* GetSimVertices2DStart() const`
- L170 _public function_ `const TManagedArray<int32>* GetSimVertices2DEnd() const`
- L171 _public function_ `const TManagedArray<int32>* GetSimFacesStart() const`
- L172 _public function_ `const TManagedArray<int32>* GetSimFacesEnd() const`
- L173 _public function_ `const TManagedArray<int32>* GetSimPatternFabric() const`
- L176 _public function_ `const TManagedArray<int32>* GetRenderVerticesStart() const`
- L177 _public function_ `const TManagedArray<int32>* GetRenderVerticesEnd() const`
- L178 _public function_ `const TManagedArray<int32>* GetRenderFacesStart() const`
- L179 _public function_ `const TManagedArray<int32>* GetRenderFacesEnd() const`
- L180 _public function_ `const TManagedArray<int32>* GetRenderDeformerNumInfluences() const`
- L181 _public function_ `const TManagedArray<FSoftObjectPath>* GetRenderMaterialSoftObjectPathName() const`
- L183 _public function_ `const TManagedArray<FString>* GetRenderMaterialPathName() const` — `UE_DEPRECATED(5.7, "Use GetRenderMaterialSoftObjectPathName instead")`
- L186 _public function_ `const TManagedArray<FIntVector3>* GetSimIndices2D() const`
- L187 _public function_ `const TManagedArray<FIntVector3>* GetSimIndices3D() const`
- L190 _public function_ `const TManagedArray<FVector2f>* GetSimPosition2D() const`
- L191 _public function_ `const TManagedArray<int32>* GetSimVertex3DLookup() const`
- L192 _public function_ `const TManagedArray<int32>* GetSimImportVertexID() const`
- L195 _public function_ `const TManagedArray<FVector3f>* GetSimPosition3D() const`
- L196 _public function_ `const TManagedArray<FVector3f>* GetPreResizedSimPosition3D() const`
- L197 _public function_ `const TManagedArray<FVector3f>* GetSimNormal() const`
- L198 _public function_ `const TManagedArray<TArray<int32>>* GetSimBoneIndices() const`
- L199 _public function_ `const TManagedArray<TArray<float>>* GetSimBoneWeights() const`
- L200 _public function_ `const TManagedArray<TArray<int32>>* GetTetherKinematicIndex() const`
- L201 _public function_ `const TManagedArray<TArray<float>>* GetTetherReferenceLength() const`
- L202 _public function_ `const TManagedArray<TArray<int32>>* GetSimVertex2DLookup() const`
- L203 _public function_ `const TManagedArray<TArray<int32>>* GetSeamStitchLookup() const`
- L204 _public function_ `const TManagedArray<float>* GetSimCustomResizingBlend() const`
- L207 _public prototype_ `const TManagedArray<FVector3f>* GetSimAccessoryMeshPosition3D(const FName& AttributeName) const;`
- L208 _public prototype_ `const TManagedArray<FVector3f>* GetSimAccessoryMeshNormal(const FName& AttributeName) const;`
- L209 _public prototype_ `const TManagedArray<TArray<int32>>* GetSimAccessoryMeshBoneIndices(const FName& AttributeName) const;`
- L210 _public prototype_ `const TManagedArray<TArray<float>>* GetSimAccessoryMeshBoneWeights(const FName& AttributeName) const;`
- L213 _public function_ `const TManagedArray<FString>* GetSimMorphTargetName() const`
- L214 _public function_ `const TManagedArray<int32>* GetSimMorphTargetVerticesStart() const`
- L215 _public function_ `const TManagedArray<int32>* GetSimMorphTargetVerticesEnd() const`
- L218 _public function_ `const TManagedArray<FVector3f>* GetSimMorphTargetPositionDelta() const`
- L219 _public function_ `const TManagedArray<FVector3f>* GetSimMorphTargetTangentZDelta() const`
- L220 _public function_ `const TManagedArray<int32>* GetSimMorphTargetSimVertex3DIndex() const`
- L223 _public function_ `const TManagedArray<FIntVector3>* GetRenderIndices() const`
- L226 _public function_ `const TManagedArray<FVector3f>* GetRenderPosition() const`
- L227 _public function_ `const TManagedArray<FVector3f>* GetRenderNormal() const`
- L228 _public function_ `const TManagedArray<FVector3f>* GetRenderTangentU() const`
- L229 _public function_ `const TManagedArray<FVector3f>* GetRenderTangentV() const`
- L230 _public function_ `const TManagedArray<TArray<FVector2f>>* GetRenderUVs() const`
- L231 _public function_ `const TManagedArray<FLinearColor>* GetRenderColor() const`
- L232 _public function_ `const TManagedArray<TArray<int32>>* GetRenderBoneIndices() const`
- L233 _public function_ `const TManagedArray<TArray<float>>* GetRenderBoneWeights() const`
- L234 _public function_ `const TManagedArray<TArray<FVector4f>>* GetRenderDeformerPositionBaryCoordsAndDist() const`
- L235 _public function_ `const TManagedArray<TArray<FVector4f>>* GetRenderDeformerNormalBaryCoordsAndDist() const`
- L236 _public function_ `const TManagedArray<TArray<FVector4f>>* GetRenderDeformerTangentBaryCoordsAndDist() const`
- L237 _public function_ `const TManagedArray<TArray<FIntVector3>>* GetRenderDeformerSimIndices3D() const`
- L238 _public function_ `const TManagedArray<TArray<float>>* GetRenderDeformerWeight() const`
- L239 _public function_ `const TManagedArray<float>* GetRenderDeformerSkinningBlend() const`
- L240 _public function_ `const TManagedArray<float>* GetRenderCustomResizingBlend() const`
- L243 _public function_ `const TManagedArray<FString>* GetCustomResizingRegionSet() const`
- L244 _public function_ `const TManagedArray<int32>* GetCustomResizingRegionType() const`
- L247 _public function_ `const TManagedArray<FName>* GetSimAccessoryMeshName() const`
- L248 _public function_ `const TManagedArray<FName>* GetSimAccessoryMeshPosition3DAttribute() const`
- L249 _public function_ `const TManagedArray<FName>* GetSimAccessoryMeshNormalAttribute() const`
- L250 _public function_ `const TManagedArray<FName>* GetSimAccessoryMeshBoneIndicesAttribute() const`
- L251 _public function_ `const TManagedArray<FName>* GetSimAccessoryMeshBoneWeightsAttribute() const`
- L257 _protected prototype_ `template<typename T UE_REQUIRES(std::is_same_v<T, FManagedArrayCollection> || std::is_same_v<T, const FManagedArrayCollection>)> FConstClothCollection(const TSharedRef<T>& InManagedArrayCollection, TProtectedInit);`
- L260 _protected member_ `TSharedRef<const FManagedArrayCollection> ManagedArrayCollection;`
- L263 _protected member_ `const TManagedArray<FSoftObjectPath>* PhysicsAssetSoftObjectPathName;`
- L264 _protected member_ `const TManagedArray<FSoftObjectPath>* SkeletalMeshSoftObjectPathName;`
- L266 _protected member_ `const TManagedArray<FString>* PhysicsAssetPathName;` — `UE_DEPRECATED(5.7, "Use PhysicsAssetSoftObjectPathName instead")`
- L268 _protected member_ `const TManagedArray<FString>* SkeletalMeshPathName;` — `UE_DEPRECATED(5.7, "Use SkeletalMeshSoftObjectPathName instead")`
- L269 _protected member_ `const TManagedArray<FName>* ReferenceBoneName;`
- L270 _protected member_ `const TManagedArray<bool>* CopyAllUserAttributesToSimModel;`
- L273 _protected member_ `const TManagedArray<FVector3f>* SolverGravity;`
- L274 _protected member_ `const TManagedArray<float>* SolverAirDamping;`
- L275 _protected member_ `const TManagedArray<int32>* SolverSubSteps;`
- L276 _protected member_ `const TManagedArray<float>* SolverTimeStep;`
- L279 _protected member_ `const TManagedArray<FVector3f>* FabricBendingStiffness;`
- L280 _protected member_ `const TManagedArray<FVector3f>* FabricBucklingStiffness;`
- L281 _protected member_ `const TManagedArray<FVector3f>* FabricStretchStiffness;`
- L282 _protected member_ `const TManagedArray<float>* FabricBucklingRatio;`
- L283 _protected member_ `const TManagedArray<float>* FabricDensity;`
- L284 _protected member_ `const TManagedArray<float>* FabricFriction;`
- L285 _protected member_ `const TManagedArray<float>* FabricDamping;`
- L286 _protected member_ `const TManagedArray<float>* FabricPressure;`
- L287 _protected member_ `const TManagedArray<int32>* FabricLayer;`
- L288 _protected member_ `const TManagedArray<float>* FabricCollisionThickness;`
- L291 _protected member_ `const TManagedArray<int32>* SeamStitchStart;`
- L292 _protected member_ `const TManagedArray<int32>* SeamStitchEnd;`
- L295 _protected member_ `const TManagedArray<FIntVector2>* SeamStitch2DEndIndices;` — Stitched 2D vertex indices pair
- L296 _protected member_ `const TManagedArray<int32>* SeamStitch3DIndex;` — Corresponding stitched 3D vertex
- L299 _protected member_ `const TManagedArray<int32>* SimVertices2DStart;`
- L300 _protected member_ `const TManagedArray<int32>* SimVertices2DEnd;`
- L301 _protected member_ `const TManagedArray<int32>* SimFacesStart;`
- L302 _protected member_ `const TManagedArray<int32>* SimFacesEnd;`
- L303 _protected member_ `const TManagedArray<int32>* SimPatternFabric;`
- L306 _protected member_ `const TManagedArray<int32>* RenderVerticesStart;`
- L307 _protected member_ `const TManagedArray<int32>* RenderVerticesEnd;`
- L308 _protected member_ `const TManagedArray<int32>* RenderFacesStart;`
- L309 _protected member_ `const TManagedArray<int32>* RenderFacesEnd;`
- L310 _protected member_ `const TManagedArray<int32>* RenderDeformerNumInfluences;` — Number of deformer mapping influences per render vertex, either 0 (no mappings), 1 or 5 (= NUM_INFLUENCES_PER_VERTEX as defined in the ush files)
- L311 _protected member_ `const TManagedArray<FSoftObjectPath>* RenderMaterialSoftObjectPathName;`
- L313 _protected member_ `const TManagedArray<FString>* RenderMaterialPathName;` — `UE_DEPRECATED(5.7, "Use RenderMaterialSoftObjectPathName instead")`
- L316 _protected member_ `const TManagedArray<FIntVector3>* SimIndices2D;`
- L317 _protected member_ `const TManagedArray<FIntVector3>* SimIndices3D;`
- L320 _protected member_ `const TManagedArray<FVector2f>* SimPosition2D;`
- L321 _protected member_ `const TManagedArray<int32>* SimVertex3DLookup;` — Lookup into corresponding 3D vertices
- L322 _protected member_ `const TManagedArray<int32>* SimImportVertexID;` — Can be populated by importers to match data
- L325 _protected member_ `const TManagedArray<FVector3f>* SimPosition3D;`
- L326 _protected member_ `const TManagedArray<FVector3f>* SimNormal;` — Used for capture, maxdistance, backstop authoring ...etc
- L327 _protected member_ `const TManagedArray<TArray<int32>>* SimBoneIndices;`
- L328 _protected member_ `const TManagedArray<TArray<float>>* SimBoneWeights;`
- L329 _protected member_ `const TManagedArray<TArray<int32>>* TetherKinematicIndex;`
- L330 _protected member_ `const TManagedArray<TArray<float>>* TetherReferenceLength;`
- L331 _protected member_ `const TManagedArray<TArray<int32>>* SimVertex2DLookup;` — Lookup into corresponding 2D vertices
- L332 _protected member_ `const TManagedArray<TArray<int32>>* SeamStitchLookup;` — Lookup into any seam stitches which weld this vertex
- L333 _protected member_ `const TManagedArray<float>* SimCustomResizingBlend;` — Resizing weight map. How much to use group resizing result (1) vs rbf interpolation result (0) when doing sim mesh resizing
- L334 _protected member_ `const TManagedArray<FVector3f>* PreResizedSimPosition3D;`
- L337 _protected member_ `const TManagedArray<FString>* SimMorphTargetName;`
- L338 _protected member_ `const TManagedArray<int32>* SimMorphTargetVerticesStart;`
- L339 _protected member_ `const TManagedArray<int32>* SimMorphTargetVerticesEnd;`
- L342 _protected member_ `const TManagedArray<FVector3f>* SimMorphTargetPositionDelta;`
- L343 _protected member_ `const TManagedArray<FVector3f>* SimMorphTargetTangentZDelta;`
- L344 _protected member_ `const TManagedArray<int32>* SimMorphTargetSimVertex3DIndex;`
- L347 _protected member_ `const TManagedArray<FIntVector3>* RenderIndices;`
- L350 _protected member_ `const TManagedArray<FVector3f>* RenderPosition;`
- L351 _protected member_ `const TManagedArray<FVector3f>* RenderNormal;`
- L352 _protected member_ `const TManagedArray<FVector3f>* RenderTangentU;`
- L353 _protected member_ `const TManagedArray<FVector3f>* RenderTangentV;`
- L354 _protected member_ `const TManagedArray<TArray<FVector2f>>* RenderUVs;`
- L355 _protected member_ `const TManagedArray<FLinearColor>* RenderColor;`
- L356 _protected member_ `const TManagedArray<TArray<int32>>* RenderBoneIndices;`
- L357 _protected member_ `const TManagedArray<TArray<float>>* RenderBoneWeights;`
- L358 _protected member_ `const TManagedArray<TArray<FVector4f>>* RenderDeformerPositionBaryCoordsAndDist;` — Barycentric coords and distance along normal for the position of the final vert
- L359 _protected member_ `const TManagedArray<TArray<FVector4f>>* RenderDeformerNormalBaryCoordsAndDist;` — Barycentric coords and distance along normal for the location of the unit normal endpoint
- L360 _protected member_ `const TManagedArray<TArray<FVector4f>>* RenderDeformerTangentBaryCoordsAndDist;` — Barycentric coords and distance along normal for the location of the unit Tangent endpoint
- L361 _protected member_ `const TManagedArray<TArray<FIntVector3>>* RenderDeformerSimIndices3D;` — The source mesh triangle
- L362 _protected member_ `const TManagedArray<TArray<float>>* RenderDeformerWeight;` — For weighted averaging of multiple triangle influences
- L363 _protected member_ `const TManagedArray<float>* RenderDeformerSkinningBlend;` — Render weight map. How much the vertex actually contributes, value between 0 (fully deformed) and 1 (fully skinned)
- L364 _protected member_ `const TManagedArray<float>* RenderCustomResizingBlend;` — Resizing weight map. How much to use group resizing result (1) vs rbf interpolation result (0) when doing render mesh resizing
- L367 _protected member_ `const TManagedArray<FString>* CustomResizingRegionSet;` — Name of the set associated with this binding type
- L368 _protected member_ `const TManagedArray<int32>* CustomResizingRegionType;` — Actually an Enum for binding type
- L371 _protected member_ `const TManagedArray<FName>* SimAccessoryMeshName;`
- L372 _protected member_ `const TManagedArray<FName>* SimAccessoryMeshPosition3DAttribute;`
- L373 _protected member_ `const TManagedArray<FName>* SimAccessoryMeshNormalAttribute;`
- L374 _protected member_ `const TManagedArray<FName>* SimAccessoryMeshBoneIndicesAttribute;`
- L375 _protected member_ `const TManagedArray<FName>* SimAccessoryMeshBoneWeightsAttribute;`
- L566 _function_ `template<typename T> inline TConstArrayView<T> FConstClothCollection::GetElements(const TManagedArray<T>* ElementArray, const TManagedArray<int32>* StartArray, const TManagedArray<int32>* EndArray, int32 ArrayIndex)`
- L582 _function_ `template<typename T> inline TArrayView<T> FConstClothCollection::GetElements(TManagedArray<T>* ElementArray, const TManagedArray<int32>* StartArray, const TManagedArray<int32>* EndArray, int32 ArrayIndex)`
- L598 _function_ `template<typename T> inline TConstArrayView<T> FConstClothCollection::GetElements(const TManagedArray<T>* ElementArray)`
- L608 _function_ `template<typename T> inline TArrayView<T> FConstClothCollection::GetElements(TManagedArray<T>* ElementArray)`
- L618 _function_ `template<typename T> inline TConstArrayView<T> FConstClothCollection::GetSubElements( const TManagedArray<T>* SubElementArray, const TManagedArray<int32>* StartArray, const TManagedArray<int32>* EndArray, const TManagedArray<int32>* StartSubArray, const TManagedArray<int32>* EndSubArray, int32 ArrayIndex)`
- L641 _function_ `template<typename T> inline TArrayView<T> FConstClothCollection::GetSubElements( TManagedArray<T>* SubElementArray, const TManagedArray<int32>* StartArray, const TManagedArray<int32>* EndArray, const TManagedArray<int32>* StartSubArray, const TManagedArray<int32>* EndSubArray, int32 ArrayIndex)`
- L664 _function_ `template<typename T> inline void FConstClothCollection::CopyArrayViewData(const TArrayView<T>& To, const TConstArrayView<T>& From)`
- L674 _function_ `template<typename T UE_REQUIRES_DEFINITION(!std::is_array_v<T>)> inline void FConstClothCollection::CopyArrayViewDataAndApplyOffset(const TArrayView<T>& To, const TConstArrayView<T>& From, const T Offset)`
- L684 _function_ `template<typename T> inline void FConstClothCollection::CopyArrayViewDataAndApplyOffset(const TArrayView<TArray<T>>& To, const TConstArrayView<TArray<T>>& From, const T Offset)`
- L698 _function_ `template<typename T> inline uint32 FConstClothCollection::GetElementsTypeHash(const TManagedArray<T>* ElementArray)`

#### struct `UE::Chaos::ClothAsset::FConstClothCollection::TProtectedInit`  
`struct TProtectedInit`  
_L254-254_

#### class `UE::Chaos::ClothAsset::FClothCollection`  
`class FClothCollection final : public FConstClothCollection`  
_L381-563_
- inherits: `FConstClothCollection`
- desc: Cloth collection facade data.
- L384 _public prototype_ `explicit FClothCollection(const TSharedRef<FManagedArrayCollection>& InManagedArrayCollection);`
- L385 _public prototype_ `~FClothCollection() = default;`
- L387 _public prototype_ `FClothCollection(const FClothCollection&) = delete;`
- L388 _public prototype_ `FClothCollection& operator=(const FClothCollection&) = delete;`
- L389 _public prototype_ `FClothCollection(FClothCollection&&) = delete;`
- L390 _public prototype_ `FClothCollection& operator=(FClothCollection&&) = delete;`
- L393 _public prototype_ `void DefineSchema(EClothCollectionExtendedSchemas OptionalSchemas = EClothCollectionExtendedSchemas::None);` — Make the underlying collection a cloth collection.
- L396 _public prototype_ `void PostSerialize(const FArchive& Ar);` — Do any PostSerialize fixups
- L399 _public prototype_ `void SetNumElements(int32 InNumElements, const FName& GroupName);` — Set the number of elements of a group.
- L402 _public prototype_ `int32 SetNumElements(int32 InNumElements, const FName& GroupName, TManagedArray<int32>* StartArray, TManagedArray<int32>* EndArray, int32 Index);` — Set the number of elements to one of the sub groups while maintaining the correct order of the data, and return the first index of the range.
- L405 _public prototype_ `void RemoveElements(const FName& Group, const TArray<int32>& SortedDeletionList);` — Remove Elements
- L408 _public prototype_ `void RemoveElements(const FName& GroupName, const TArray<int32>& SortedDeletionList, TManagedArray<int32>* StartArray, TManagedArray<int32>* EndArray, int32 Index);` — Remove Elements. SortedDeletionList should be global indices.
- L411 _public prototype_ `template<typename T UE_REQUIRES(TIsUserAttributeType<T>::Value)> TManagedArray<T>* FindOrAddUserDefinedAttribute(const FName& Name, const FName& GroupName, const FName& GroupDependency = NAME_None);`
- L414 _public function_ `template<typename T UE_REQUIRES(TIsUserAttributeType<T>::Value)> void AddUserDefinedAttribute(const FName& Name, const FName& GroupName, const FName& GroupDependency = NAME_None)`
- L419 _public prototype_ `void RemoveUserDefinedAttribute(const FName& Name, const FName& GroupName);`
- L422 _public prototype_ `template<typename T UE_REQUIRES(TIsUserAttributeType<T>::Value)> TManagedArray<T>* GetUserDefinedAttribute(const FName& Name, const FName& GroupName);`
- L425 _public function_ `TManagedArray<FSoftObjectPath>* GetPhysicsAssetSoftObjectPathName()`
- L426 _public function_ `TManagedArray<FSoftObjectPath>* GetSkeletalMeshSoftObjectPathName()`
- L428 _public function_ `TManagedArray<FString>* GetPhysicsAssetPathName()` — `UE_DEPRECATED(5.7, "Use GetPhysicsAssetSoftObjectPathName instead")`
- L430 _public function_ `TManagedArray<FString>* GetSkeletalMeshPathName()` — `UE_DEPRECATED(5.7, "Use GetSkeletalMeshSoftObjectPathName instead")`
- L431 _public function_ `TManagedArray<FName>* GetReferenceBoneName()`
- L432 _public function_ `TManagedArray<bool>* GetCopyAllUserAttributesToSimModel()`
- L435 _public function_ `TManagedArray<FVector3f>* GetSolverGravity()`
- L436 _public function_ `TManagedArray<float>* GetSolverAirDamping()`
- L437 _public function_ `TManagedArray<int32>* GetSolverSubSteps()`
- L438 _public function_ `TManagedArray<float>* GetSolverTimeStep()`
- L441 _public function_ `TManagedArray<FVector3f>* GetFabricBendingStiffness()`
- L442 _public function_ `TManagedArray<FVector3f>* GetFabricBucklingStiffness()`
- L443 _public function_ `TManagedArray<FVector3f>* GetFabricStretchStiffness()`
- L444 _public function_ `TManagedArray<float>* GetFabricBucklingRatio()`
- L445 _public function_ `TManagedArray<float>* GetFabricDensity()`
- L446 _public function_ `TManagedArray<float>* GetFabricFriction()`
- L447 _public function_ `TManagedArray<float>* GetFabricDamping()`
- L448 _public function_ `TManagedArray<float>* GetFabricPressure()`
- L449 _public function_ `TManagedArray<int32>* GetFabricLayer()`
- L450 _public function_ `TManagedArray<float>* GetFabricCollisionThickness()`
- L453 _public function_ `TManagedArray<int32>* GetSeamStitchStart()`
- L454 _public function_ `TManagedArray<int32>* GetSeamStitchEnd()`
- L457 _public function_ `TManagedArray<FIntVector2>* GetSeamStitch2DEndIndices()`
- L458 _public function_ `TManagedArray<int32>* GetSeamStitch3DIndex()`
- L461 _public function_ `TManagedArray<int32>* GetSimVertices2DStart()`
- L462 _public function_ `TManagedArray<int32>* GetSimVertices2DEnd()`
- L463 _public function_ `TManagedArray<int32>* GetSimFacesStart()`
- L464 _public function_ `TManagedArray<int32>* GetSimFacesEnd()`
- L465 _public function_ `TManagedArray<int32>* GetSimPatternFabric()`
- L468 _public function_ `TManagedArray<int32>* GetRenderVerticesStart()`
- L469 _public function_ `TManagedArray<int32>* GetRenderVerticesEnd()`
- L470 _public function_ `TManagedArray<int32>* GetRenderFacesStart()`
- L471 _public function_ `TManagedArray<int32>* GetRenderFacesEnd()`
- L472 _public function_ `TManagedArray<int32>* GetRenderDeformerNumInfluences()`
- L473 _public function_ `TManagedArray<FSoftObjectPath>* GetRenderMaterialSoftObjectPathName()`
- L475 _public function_ `TManagedArray<FString>* GetRenderMaterialPathName()` — `UE_DEPRECATED(5.7, "Use GetRenderMaterialSoftObjectPathName instead")`
- L478 _public function_ `TManagedArray<FIntVector3>* GetSimIndices2D()`
- L479 _public function_ `TManagedArray<FIntVector3>* GetSimIndices3D()`
- L482 _public function_ `TManagedArray<FVector2f>* GetSimPosition2D()`
- L483 _public function_ `TManagedArray<int32>* GetSimVertex3DLookup()`
- L484 _public function_ `TManagedArray<int32>* GetSimImportVertexID()`
- L487 _public function_ `TManagedArray<FVector3f>* GetSimPosition3D()`
- L488 _public function_ `TManagedArray<FVector3f>* GetPreResizedSimPosition3D()`
- L489 _public function_ `TManagedArray<FVector3f>* GetSimNormal()`
- L490 _public function_ `TManagedArray<TArray<int32>>* GetSimBoneIndices()`
- L491 _public function_ `TManagedArray<TArray<float>>* GetSimBoneWeights()`
- L492 _public function_ `TManagedArray<TArray<int32>>* GetTetherKinematicIndex()`
- L493 _public function_ `TManagedArray<TArray<float>>* GetTetherReferenceLength()`
- L494 _public function_ `TManagedArray<TArray<int32>>* GetSimVertex2DLookup()`
- L495 _public function_ `TManagedArray<TArray<int32>>* GetSeamStitchLookup()`
- L496 _public function_ `TManagedArray<float>* GetSimCustomResizingBlend()`
- L499 _public function_ `TManagedArray<FVector3f>* GetSimAccessoryMeshPosition3D(const FName& AttributeName)`
- L500 _public function_ `TManagedArray<FVector3f>* GetSimAccessoryMeshNormal(const FName& AttributeName) const`
- L501 _public function_ `TManagedArray<TArray<int32>>* GetSimAccessoryMeshBoneIndices(const FName& AttributeName) const`
- L502 _public function_ `TManagedArray<TArray<float>>* GetSimAccessoryMeshBoneWeights(const FName& AttributeName) const`
- L506 _public prototype_ `FName AddSimAccessoryMeshPosition3D();` — Add accessory mesh attribute and return resulting attribute's name. Note: these currently do a linear search through existing attributes to generate a unique name. This does not record the new attribute in the associated SimAccessoryMesh group Attribute
- L507 _public prototype_ `FName AddSimAccessoryMeshNormal();`
- L508 _public prototype_ `FName AddSimAccessoryMeshBoneIndices();`
- L509 _public prototype_ `FName AddSimAccessoryMeshBoneWeights();`
- L512 _public prototype_ `void RemoveSimAccessoryMeshPosition3D(const FName& AttributeName);` — Remove accessory mesh attribute by name. This does not reset the attribute in the associated SimAccessoryMesh group Attribute
- L513 _public prototype_ `void RemoveSimAccessoryMeshNormal(const FName& AttributeName);`
- L514 _public prototype_ `void RemoveSimAccessoryMeshBoneIndices(const FName& AttributeName);`
- L515 _public prototype_ `void RemoveSimAccessoryMeshBoneWeights(const FName& AttributeName);`
- L518 _public function_ `TManagedArray<FString>* GetSimMorphTargetName()`
- L519 _public function_ `TManagedArray<int32>* GetSimMorphTargetVerticesStart()`
- L520 _public function_ `TManagedArray<int32>* GetSimMorphTargetVerticesEnd()`
- L523 _public function_ `TManagedArray<FVector3f>* GetSimMorphTargetPositionDelta()`
- L524 _public function_ `TManagedArray<FVector3f>* GetSimMorphTargetTangentZDelta()`
- L525 _public function_ `TManagedArray<int32>* GetSimMorphTargetSimVertex3DIndex()`
- L528 _public function_ `TManagedArray<FIntVector3>* GetRenderIndices()`
- L531 _public function_ `TManagedArray<FVector3f>* GetRenderPosition()`
- L532 _public function_ `TManagedArray<FVector3f>* GetRenderNormal()`
- L533 _public function_ `TManagedArray<FVector3f>* GetRenderTangentU()`
- L534 _public function_ `TManagedArray<FVector3f>* GetRenderTangentV()`
- L535 _public function_ `TManagedArray<TArray<FVector2f>>* GetRenderUVs()`
- L536 _public function_ `TManagedArray<FLinearColor>* GetRenderColor()`
- L537 _public function_ `TManagedArray<TArray<int32>>* GetRenderBoneIndices()`
- L538 _public function_ `TManagedArray<TArray<float>>* GetRenderBoneWeights()`
- L539 _public function_ `TManagedArray<TArray<FVector4f>>* GetRenderDeformerPositionBaryCoordsAndDist()`
- L540 _public function_ `TManagedArray<TArray<FVector4f>>* GetRenderDeformerNormalBaryCoordsAndDist()`
- L541 _public function_ `TManagedArray<TArray<FVector4f>>* GetRenderDeformerTangentBaryCoordsAndDist()`
- L542 _public function_ `TManagedArray<TArray<FIntVector3>>* GetRenderDeformerSimIndices3D()`
- L543 _public function_ `TManagedArray<TArray<float>>* GetRenderDeformerWeight()`
- L544 _public function_ `TManagedArray<float>* GetRenderDeformerSkinningBlend()`
- L545 _public function_ `TManagedArray<float>* GetRenderCustomResizingBlend()`
- L548 _public function_ `TManagedArray<FString>* GetCustomResizingRegionSet()`
- L549 _public function_ `TManagedArray<int32>* GetCustomResizingRegionType()`
- L552 _public function_ `TManagedArray<FName>* GetSimAccessoryMeshName() const`
- L553 _public function_ `TManagedArray<FName>* GetSimAccessoryMeshPosition3DAttribute() const`
- L554 _public function_ `TManagedArray<FName>* GetSimAccessoryMeshNormalAttribute() const`
- L555 _public function_ `TManagedArray<FName>* GetSimAccessoryMeshBoneIndicesAttribute() const`
- L556 _public function_ `TManagedArray<FName>* GetSimAccessoryMeshBoneWeightsAttribute() const`
- L559 _private function_ `TSharedRef<FManagedArrayCollection> GetManagedArrayCollection()`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Chaos` (scope `UE`)
- L14 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAsset/Public/ChaosClothAsset/ClothCollectionAttribute.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Chaos` (scope `UE`)
- L7 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
- L12 _namespace_ `namespace ClothCollectionAttribute` (scope `UE::Chaos::ClothAsset`)
- L15 _variable_ `inline const FName PhysicsAssetSoftObjectPathName(TEXT("Phys` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Lods Group
- L16 _variable_ `inline const FName SkeletalMeshSoftObjectPathName(TEXT("Skel` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L17 _variable_ `inline const FName ReferenceBoneName(TEXT("Refe` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L18 _variable_ `inline const FName CopyAllUserAttributesToSimModel(TEXT("Copy` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L21 _variable_ `inline const FName SolverGravity(TEXT("Solv` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Solvers Group
- L22 _variable_ `inline const FName SolverAirDamping(TEXT("Solv` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L23 _variable_ `inline const FName SolverSubSteps(TEXT("Solv` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L24 _variable_ `inline const FName SolverTimeStep(TEXT("Solv` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L27 _variable_ `inline const FName FabricBendingStiffness(TEXT("Fabr` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Fabrics Group
- L28 _variable_ `inline const FName FabricBucklingStiffness(TEXT("Fabr` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L29 _variable_ `inline const FName FabricStretchStiffness(TEXT("Fabr` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L30 _variable_ `inline const FName FabricBucklingRatio(TEXT("Fabr` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L31 _variable_ `inline const FName FabricDensity(TEXT("Fabr` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L32 _variable_ `inline const FName FabricFriction(TEXT("Fabr` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L33 _variable_ `inline const FName FabricDamping(TEXT("Fabr` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L34 _variable_ `inline const FName FabricPressure(TEXT("Fabr` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L35 _variable_ `inline const FName FabricLayer(TEXT("Fabr` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L36 _variable_ `inline const FName FabricCollisionThickness(TEXT("Fabr` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L39 _variable_ `inline const FName SeamStitchStart(TEXT("Seam` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Seam Group
- L40 _variable_ `inline const FName SeamStitchEnd(TEXT("Seam` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L43 _variable_ `inline const FName SeamStitch2DEndIndices(TEXT("Seam` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Seam Stitches Group
- L44 _variable_ `inline const FName SeamStitch3DIndex(TEXT("Seam` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L47 _variable_ `inline const FName SimVertices2DStart(TEXT("SimV` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Sim Patterns Group
- L48 _variable_ `inline const FName SimVertices2DEnd(TEXT("SimV` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L49 _variable_ `inline const FName SimFacesStart(TEXT("SimF` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L50 _variable_ `inline const FName SimFacesEnd(TEXT("SimF` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L51 _variable_ `inline const FName SimPatternFabric(TEXT("SimP` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L54 _variable_ `inline const FName RenderVerticesStart(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Render Patterns Group
- L55 _variable_ `inline const FName RenderVerticesEnd(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L56 _variable_ `inline const FName RenderFacesStart(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L57 _variable_ `inline const FName RenderFacesEnd(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L58 _variable_ `inline const FName RenderMaterialSoftObjectPathName(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L59 _variable_ `inline const FName RenderDeformerNumInfluences(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L62 _variable_ `inline const FName SimIndices2D(TEXT("SimI` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Sim Faces Group
- L63 _variable_ `inline const FName SimIndices3D(TEXT("SimI` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L66 _variable_ `inline const FName SimPosition2D(TEXT("SimP` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Sim Vertices 2D Group
- L67 _variable_ `inline const FName SimVertex3DLookup(TEXT("SimV` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L68 _variable_ `inline const FName SimImportVertexID(TEXT("SimI` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L71 _variable_ `inline const FName SimPosition3D(TEXT("SimP` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Sim Vertices 3D Group
- L72 _variable_ `inline const FName PreResizedSimPosition3D(TEXT("PreR` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L73 _variable_ `inline const FName SimNormal(TEXT("SimN` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L74 _variable_ `inline const FName SimBoneIndices(TEXT("SimB` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L75 _variable_ `inline const FName SimBoneWeights(TEXT("SimB` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L76 _variable_ `inline const FName TetherKinematicIndex(TEXT("Teth` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L77 _variable_ `inline const FName TetherReferenceLength(TEXT("Teth` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L78 _variable_ `inline const FName SimVertex2DLookup(TEXT("SimV` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L79 _variable_ `inline const FName SeamStitchLookup(TEXT("Seam` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L80 _variable_ `inline const FName SimCustomResizingBlend(TEXT("SimC` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L83 _variable_ `inline const FName SimAccessoryMeshPosition3DPrefix(TEXT("SimA` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Sim Vertices 3D Group -- Sim Accessory Mesh
- L84 _variable_ `inline const FName SimAccessoryMeshNormalPrefix(TEXT("SimA` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L85 _variable_ `inline const FName SimAccessoryMeshBoneIndicesPrefix(TEXT("SimA` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L86 _variable_ `inline const FName SimAccessoryMeshBoneWeightsPrefix(TEXT("SimA` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L89 _variable_ `inline const FName SimMorphTargetName(TEXT("SimM` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Sim Morph Targets Group
- L90 _variable_ `inline const FName SimMorphTargetVerticesStart(TEXT("SimM` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L91 _variable_ `inline const FName SimMorphTargetVerticesEnd(TEXT("SimM` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L94 _variable_ `inline const FName SimMorphTargetPositionDelta(TEXT("SimM` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Sim Morph Target Vertices Group
- L95 _variable_ `inline const FName SimMorphTargetTangentZDelta(TEXT("SimM` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L96 _variable_ `inline const FName SimMorphTargetSimVertex3DIndex(TEXT("SimM` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L99 _variable_ `inline const FName RenderIndices(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Render Faces Group
- L102 _variable_ `inline const FName RenderPosition(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Render Vertices Group
- L103 _variable_ `inline const FName RenderNormal(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L104 _variable_ `inline const FName RenderTangentU(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L105 _variable_ `inline const FName RenderTangentV(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L106 _variable_ `inline const FName RenderUVs(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L107 _variable_ `inline const FName RenderColor(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L108 _variable_ `inline const FName RenderBoneIndices(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L109 _variable_ `inline const FName RenderBoneWeights(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L110 _variable_ `inline const FName RenderDeformerPositionBaryCoordsAndDist(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L111 _variable_ `inline const FName RenderDeformerNormalBaryCoordsAndDist(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L112 _variable_ `inline const FName RenderDeformerTangentBaryCoordsAndDist(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L113 _variable_ `inline const FName RenderDeformerSimIndices3D(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L114 _variable_ `inline const FName RenderDeformerWeight(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L115 _variable_ `inline const FName RenderDeformerSkinningBlend(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L116 _variable_ `inline const FName RenderCustomResizingBlend(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L119 _variable_ `inline const FName CustomResizingRegionSet(TEXT("Cust` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Custom Resizing Regions Group
- L120 _variable_ `inline const FName CustomResizingRegionType(TEXT("Cust` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L122 _variable_ `inline const FName SimAccessoryMeshName(TEXT("SimA` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — Sim Accessory Meshes Group
- L123 _variable_ `inline const FName SimAccessoryMeshPosition3DAttribute(TEXT("SimA` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L124 _variable_ `inline const FName SimAccessoryMeshNormalAttribute(TEXT("SimA` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L125 _variable_ `inline const FName SimAccessoryMeshBoneIndicesAttribute(TEXT("SimA` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L126 _variable_ `inline const FName SimAccessoryMeshBoneWeightsAttribute(TEXT("SimA` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`)
- L131 _variable_ `inline const FName PhysicsAssetPathName(TEXT("Phys` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — `UE_DEPRECATED(5.7, "Use PhysicsAssetSoftObjectPath instead")` — Lods Group
- L133 _variable_ `inline const FName SkeletalMeshPathName(TEXT("Skel` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — `UE_DEPRECATED(5.7, "Use SkeletalMeshSoftObjectPathName instead")`
- L137 _variable_ `inline const FName RenderMaterialPathName(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionAttribute`) — `UE_DEPRECATED(5.7, "Use RenderMaterialSoftObjectPathName instead")` — Render Patterns Group

### `Plugins/ChaosClothAsset/Source/ChaosClothAsset/Public/ChaosClothAsset/ClothCollectionExtendedSchemas.h` (Public)


#### enum `UE::Chaos::ClothAsset::EClothCollectionExtendedSchemas`  
`enum class EClothCollectionExtendedSchemas : uint32`  
_L11-22_
- desc: Cloth collection extended schemas.
- L13 _public enumerator_ `None = 0`
- L14 _public enumerator_ `RenderDeformer = 1 << 1`
- L15 _public enumerator_ `Solvers = 1 << 2`
- L16 _public enumerator_ `Fabrics = 1 << 3`
- L17 _public enumerator_ `SimMorphTargets = 1 << 4`
- L18 _public enumerator_ `CookedOnly = 1 << 5` — If this flag is found, only cooked schemas will be considered.
- L19 _public enumerator_ `Resizing = 1 << 6`
- L20 _public enumerator_ `SimAccessoryMeshes = 1 << 7`
- L21 _public enumerator_ `Import = 1 << 8`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Chaos` (scope `UE`)
- L8 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAsset/Public/ChaosClothAsset/ClothCollectionGroup.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Chaos` (scope `UE`)
- L7 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
- L12 _namespace_ `namespace ClothCollectionGroup` (scope `UE::Chaos::ClothAsset`)
- L15 _variable_ `inline const FName Lods = FName(TEXT("Lods` (scope `UE::Chaos::ClothAsset::ClothCollectionGroup`) — LOD information (only one LOD per collection).
- L17 _variable_ `inline const FName Solvers = FName(TEXT("Solv` (scope `UE::Chaos::ClothAsset::ClothCollectionGroup`) — Solvers information (only one Solver per collection for now).
- L19 _variable_ `inline const FName Seams = FName(TEXT("Seam` (scope `UE::Chaos::ClothAsset::ClothCollectionGroup`) — Collection of seam stitches.
- L21 _variable_ `inline const FName SeamStitches = FName(TEXT("Seam` (scope `UE::Chaos::ClothAsset::ClothCollectionGroup`) — Contains pairs of stitched sim vertex indices.
- L23 _variable_ `inline const FName SimPatterns = FName(TEXT("SimP` (scope `UE::Chaos::ClothAsset::ClothCollectionGroup`) — Contains sim pattern relationships to other groups.
- L25 _variable_ `inline const FName RenderPatterns = FName(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionGroup`) — Contains render pattern relationships to other groups.
- L27 _variable_ `inline const FName SimFaces = FName(TEXT("SimF` (scope `UE::Chaos::ClothAsset::ClothCollectionGroup`) — Contains indices to sim vertices.
- L29 _variable_ `inline const FName SimVertices2D = FName(TEXT("SimV` (scope `UE::Chaos::ClothAsset::ClothCollectionGroup`) — Contains 2D positions.
- L31 _variable_ `inline const FName SimVertices3D = FName(TEXT("SimV` (scope `UE::Chaos::ClothAsset::ClothCollectionGroup`) — Contains 3D positions.
- L33 _variable_ `inline const FName RenderFaces = FName(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionGroup`) — Contains indices to render vertex.
- L35 _variable_ `inline const FName RenderVertices = FName(TEXT("Rend` (scope `UE::Chaos::ClothAsset::ClothCollectionGroup`) — Contains 3D render model.
- L37 _variable_ `inline const FName Fabrics = FName(TEXT("Fabr` (scope `UE::Chaos::ClothAsset::ClothCollectionGroup`) — Contains all the fabrics simulation parameters used by the sim patterns .
- L39 _variable_ `inline const FName SimMorphTargets = FName(TEXT("SimM` (scope `UE::Chaos::ClothAsset::ClothCollectionGroup`) — Contains sim morph target relationships to other groups.
- L41 _variable_ `inline const FName SimMorphTargetVertices = FName(TEXT("SimM` (scope `UE::Chaos::ClothAsset::ClothCollectionGroup`) — Contains morph target vertices
- L43 _variable_ `inline const FName CustomResizingRegions = FName(TEXT("Cust` (scope `UE::Chaos::ClothAsset::ClothCollectionGroup`) — Contains custom region resizing data
- L45 _variable_ `inline const FName SimAccessoryMeshes = FName(TEXT("SimA` (scope `UE::Chaos::ClothAsset::ClothCollectionGroup`) — Contains sim accessory mesh relationships to other groups.

### `Plugins/ChaosClothAsset/Source/ChaosClothAsset/Public/ChaosClothAsset/ClothCollectionOptionalSchemas.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Chaos` (scope `UE`)
- L10 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
- L12 _typedef_ `UE_DEPRECATED(5.6, "Use EClothCollectionExtendedSchemas instead") typedef enum EClothCollectionExten` (scope `UE::Chaos::ClothAsset`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAsset/Public/ChaosClothAsset/ClothGeometryTools.h` (Public)


#### struct `UE::Chaos::ClothAsset::FClothGeometryTools`  
`struct FClothGeometryTools`  
_L21-186_
- desc: Geometry tools operating on cloth collections.
- L25 _public prototype_ `static bool HasSimMesh(const TSharedRef<const FManagedArrayCollection>& ClothCollection);` — Return whether at least one pattern of this collection has any faces to simulate.
- L28 _public prototype_ `static bool HasRenderMesh(const TSharedRef<const FManagedArrayCollection>& ClothCollection);` — Return whether at least one pattern of this collection has any faces to render.
- L31 _public prototype_ `static void DeleteRenderMesh(const TSharedRef<FManagedArrayCollection>& ClothCollection);` — Delete the render mesh data.
- L34 _public prototype_ `static void DeleteSimMesh(const TSharedRef<FManagedArrayCollection>& ClothCollection);` — Delete the sim mesh data.
- L37 _public prototype_ `static void DeleteTethers(const TSharedRef<FManagedArrayCollection>& ClothCollection);` — Remove all tethers.
- L40 _public prototype_ `static void DeleteSelections(const TSharedRef<FManagedArrayCollection>& ClothCollection, const FName Group = NAME_None);` — Remove all selections, or the selections from a specific group if specified.
- L43 _public prototype_ `static void CopySimMeshToRenderMesh(const TSharedRef<FManagedArrayCollection>& ClothCollection, const FSoftObjectPath& RenderMaterialPathName, bool bSingleRenderPattern);` — Turn the sim mesh portion of this ClothCollection into a render mesh.
- L46 _public prototype_ `static void ReverseMesh( const TSharedRef<FManagedArrayCollection>& ClothCollection, bool bReverseSimMeshNormals, bool bReverseSimMeshWindingOrder, bool bReverseRenderMeshNormals, bool bReverseRenderMeshWindingOrder, const TArray<int32>& SimPatternSelection, const TArray<int32>& RenderPatternSelection);` — Reverse the mesh normals. Will reverse all normals if pattern selection is empty.
- L56 _public prototype_ `static void RecalculateRenderMeshNormals(const TSharedRef<FManagedArrayCollection>& ClothCollection);` — Recalculate the render mesh normals.
- L63 _public prototype_ `static void BindMeshToRootBone( const TSharedRef<FManagedArrayCollection>& ClothCollection, bool bBindSimMesh, bool bBindRenderMesh);` — Set the skinning weights for all of the sim/render vertices in ClothCollection to be bound to the root node. @param Lods if empty will apply the change to all LODs. Otherwise only LODs specified in the array (if exist) are affected.
- L80 _public prototype_ `static void BuildSimMeshFromDynamicMeshes( const TSharedRef<FManagedArrayCollection>& ClothCollection, const UE::Geometry::FDynamicMesh3& Mesh2D, const UE::Geometry::FDynamicMesh3& Mesh3D, int32 PatternIndexLayerId, bool bTransferWeightMaps, bool bTransferSimSkinningData, bool bAppend, TMap<int, int32>& OutDynamicMeshToClothVertexMap);` — Build (or add to) a ClothCollection Sim Mesh from the given 2D and 3D mesh data. Uses a Polygroup Attribute Layer to specify Pattern topology. @param ClothCollection					The cloth collection whose sim mesh (2D and 3D) will be modified @param Mesh2D								Input 2D sim mesh data @param Mesh3D								Input 3D sim mesh data @param PatternIndexLayerId				Specifies which PolyGroup layer on Mesh2D contains pattern index per triangle information @param bTransferWeightMaps				Copy any weight map layers from Mesh2D into the ClothCollection sim mesh @param bTransferSimSkinningData			Copy any skinning weight data from Mesh2D into the ClothCollection sim mesh @param bAppend							Whether to add the new mesh data to the existing sim mesh, or crete new sim mesh in the collection @param OutDynamicMeshToClothVertexMap		(Output) Computed map of vertex indices in the input Meshes to vertex indices in the output ClothCollection
- L94 _public prototype_ `static void BuildSimMeshFromDynamicMesh( const TSharedRef<FManagedArrayCollection>& ClothCollection, const UE::Geometry::FDynamicMesh3& DynamicMesh, int32 UVChannelIndex, const FVector2f& UVScale, bool bAppend, bool bImportNormals = false, TArray<int32>* OutSim2DToSourceIndex = nullptr);` — Unwrap and build SimMesh data from a DynamicMesh Normals are only imported if the DynamicMesh has both a UVOverlay and a NormalOverlay
- L102 _public prototype_ `static void CleanupAndCompactMesh(const TSharedRef<FManagedArrayCollection>& ClothCollection);` — Remove (topologically) degenerate triangles. Remove any vertices that aren't in a triangle. Compact any lookup arrays that contain INDEX_NONEs. Remove any empty patterns.
- L105 _public prototype_ `static void StripUnusedUserAttributes(const TSharedRef<FManagedArrayCollection>& ClothCollection, bool bStripUnusedSimWeightMaps, const TArray<FName>& ExtraSimWeightMaps, bool bStripUnusedSets, const TArray<FName>& ExtraSets, bool bStripUnusedFaceIntMaps, const TArray<FName>& ExtraFaceIntMaps, bool bStripUnusedRenderWeightMaps, const TArray<FName>& ExtraRenderWeightMaps);` — Strip maps, sets, etc. that are not referenced by properties from a cloth collection.
- L111 _public prototype_ `static void BuildConnectedSeams(const TArray<FIntVector2>& InputStitches, const UE::Geometry::FDynamicMesh3& Mesh, TArray<TArray<FIntVector2>>& Seams);` — Find sets of connected stitches for the input stitches given in random order. Stitch (A, B) is connected to stitch (C, D) if there exist edges {(A, C), (B, D)} *or* {(A, D), (B, C)} in the given DynamicMesh.
- L120 _public prototype_ `static void BuildConnectedSeams2D(const TSharedRef<const FManagedArrayCollection>& ClothCollection, int32 SeamIndex, const UE::Geometry::FDynamicMesh3& Mesh, TArray<TArray<FIntVector2>>& Seams);` — Find sets of connected stitches for the given seam. Stitch (A, B) is connected to stitch (C, D) if there exist edges {(A, C), (B, D)} *or* {(A, D), (B, C)} in the given DynamicMesh. ClothCollection meshes must be manifold.
- L133 _public prototype_ `static void SampleVertices(const TConstArrayView<FVector3f> VertexPositions, float CullDiameterSq, TSet<int32>& OutVertexSet);` — Use Poisson disk sampling to get a set of evenly-spaced vertices @param VertexPositions set of vertex points to sample from @param CullDiameterSq squared minimum distance between samples @param OutVertexSet indices of the sampled subset of VertexPositions
- L146 _public prototype_ `static bool ConvertSelectionToNewGroupType(const TSharedRef<const FManagedArrayCollection>& ClothCollection, const FName& SelectionName, const FName& GroupName, bool bSecondarySelection, TSet<int32>& OutSelectionSet);` — `UE_DEPRECATED(5.5, "Please use the version with no bSecondarySelection parameter")` — Get a copy of the selection, converting to the desired group if possible. Currently only conversions between vertex and face components on the same mesh type are supported. @param ClothCollection to query @param SelectionName the selection name @param GroupName the group name @param bSecondarySelection get the secondary selection @param OutSelectionSet copy of the selection. Unchanged when function returns false. @return success (will return false if the selection is not found or conversion is not possible)
- L157 _public prototype_ `static bool ConvertSelectionToNewGroupType(const TSharedRef<const FManagedArrayCollection>& ClothCollection, const FName& SelectionName, const FName& GroupName, TSet<int32>& OutSelectionSet);` — Get a copy of the selection, converting to the desired group if possible. Currently only conversions between vertex and face components on the same mesh type are supported. @param ClothCollection to query @param SelectionName the selection name @param GroupName the group name @param OutSelectionSet copy of the selection. Unchanged when function returns false. @return success (will return false if the selection is not found or conversion is not possible)
- L162 _public prototype_ `static void SelectAllInGroupType(const TSharedRef<FManagedArrayCollection>& ClothCollection, const FName& SelectionName, const FName& GroupName);` — Create a selection set that selects all members of a group.
- L167 _public prototype_ `static void TransferWeightMap( const TConstArrayView<FVector3f>& SourcePositions, const TConstArrayView<FIntVector3>& InSourceIndices, const TConstArrayView<float>& SourceWeights, const TConstArrayView<FVector3f>& TargetPositions, const TConstArrayView<FVector3f>& TargetNormals, const TConstArrayView<FIntVector3>& InTargetIndices, const TArrayView<float>& TargetWeights);` — Transfer a vertex weight map from a source to target mesh
- L179 _public prototype_ `static TSet<int32> GenerateKinematicVertices3D(const TSharedRef<FManagedArrayCollection>& ClothCollection, const FName& MaxDistanceMap, const FVector2f& MaxDistanceValues, const FName& InputKinematicVertices, float KinematicDistanceThreshold = 0.1f);` — Generate KinematicVertices3D set from the given MaxDistance weight map, MaxDistance values, and any additional kinematic vertices.
- L184 _public prototype_ `static void ApplyProxyDeformer(const TSharedRef<FManagedArrayCollection>& ClothCollection, bool bIgnoreSkinningBlend);` — Update the render mesh by applying the proxy deformer.
- L185 _public prototype_ `static void ApplyProxyDeformer(FCollectionClothFacade& ClothFacade, bool bIgnoreSkinningBlend, const TConstArrayView<FVector3f>& SimPositions, const TConstArrayView<FVector3f>& SimNormals);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSCLOTHASSET_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Chaos` (scope `UE`)
- L13 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAsset/Public/ChaosClothAsset/CollectionClothFabricFacade.h` (Public)


#### struct `UE::Chaos::ClothAsset::FDefaultFabric`  
`struct FDefaultFabric`  
_L11-26_
- L13 _public member_ `inline static constexpr float BendingStiffness = 100.0f;`
- L14 _public member_ `inline static constexpr float StretchStiffness = 100.0f;`
- L15 _public member_ `inline static constexpr float BucklingRatio = 0.5f;`
- L16 _public member_ `inline static constexpr float BucklingStiffness = 50.0f;`
- L17 _public member_ `inline static constexpr float Density = 0.35f;`
- L18 _public member_ `inline static constexpr float Friction = 0.8f;`
- L19 _public member_ `inline static constexpr float Damping = 0.1f;`
- L20 _public member_ `inline static constexpr float Pressure = 0.0f;`
- L21 _public member_ `inline static constexpr int32 Layer = INDEX_NONE;`
- L22 _public member_ `inline static constexpr float CollisionThickness = 1.0f;`
- L23 _public member_ `inline static constexpr float ClothCollisionThickness = 0.f;`
- L24 _public member_ `inline static constexpr float SelfFriction = 0.0f;`
- L25 _public member_ `inline static constexpr float SelfCollisionThickness = 0.5f;`

#### class `UE::Chaos::ClothAsset::FCollectionClothFabricConstFacade`  
`class FCollectionClothFabricConstFacade`  
_L33-106_
- desc: Cloth Asset collection fabric facade class to access cloth fabric data. Constructed from FCollectionClothConstFacade. Const access (read only) version.
- L36 _public prototype_ `FCollectionClothFabricConstFacade() = delete;`
- L38 _public prototype_ `FCollectionClothFabricConstFacade(const FCollectionClothFabricConstFacade&) = delete;`
- L39 _public prototype_ `FCollectionClothFabricConstFacade& operator=(const FCollectionClothFabricConstFacade&) = delete;`
- L41 _public prototype_ `FCollectionClothFabricConstFacade(FCollectionClothFabricConstFacade&&) = default;`
- L42 _public prototype_ `FCollectionClothFabricConstFacade& operator=(FCollectionClothFabricConstFacade&&) = default;`
- L44 _public prototype_ `virtual ~FCollectionClothFabricConstFacade() = default;`
- L62 _public prototype_ `FAnisotropicData GetBendingStiffness() const;` — Return the anisotropic bending stiffness
- L65 _public prototype_ `float GetBucklingRatio() const;` — Return the buckling ratio
- L68 _public prototype_ `FAnisotropicData GetBucklingStiffness() const;` — Return the anisotropic buckling stiffness
- L71 _public prototype_ `FAnisotropicData GetStretchStiffness() const;` — Return the anisotropic stretch stiffness
- L74 _public prototype_ `float GetDensity() const;` — Return the fabric density
- L77 _public prototype_ `float GetDamping() const;` — Return the fabric damping
- L80 _public prototype_ `float GetFriction() const;` — Return the fabric friction
- L83 _public prototype_ `float GetPressure() const;` — Return the fabric pressure
- L86 _public prototype_ `int32 GetLayer() const;` — Return the fabric layer
- L89 _public prototype_ `float GetCollisionThickness() const;` — Return the collision thickness
- L92 _public function_ `int32 GetElementIndex() const` — Get the global element index
- L97 _protected prototype_ `FCollectionClothFabricConstFacade(const TSharedRef<const class FConstClothCollection>& InClothCollection, int32 InFabricIndex);`
- L99 _protected function_ `static constexpr int32 GetBaseElementIndex()`
- L105 _protected member_ `int32 FabricIndex;` — Fabric index that will be referred in the sim patterns

#### struct `UE::Chaos::ClothAsset::FCollectionClothFabricConstFacade::FAnisotropicData`  
`struct FAnisotropicData`  
_L47-59_
- desc: Anisotropic fabric datas structure (Weft,Warp,Bias)
- L49 _public prototype_ `FAnisotropicData(const float WeftValue, const float WarpValue, const float BiasValue);`
- L50 _public prototype_ `FAnisotropicData(const FVector3f& VectorDatas);`
- L51 _public prototype_ `FAnisotropicData(const float& FloatDatas);`
- L53 _public prototype_ `FVector3f GetVectorDatas() const;`
- L56 _public member_ `float Weft;`
- L57 _public member_ `float Warp;`
- L58 _public member_ `float Bias;`

#### class `UE::Chaos::ClothAsset::FCollectionClothFabricFacade`  
`class FCollectionClothFabricFacade final : public FCollectionClothFabricConstFacade`  
_L113-150_
- inherits: `FCollectionClothFabricConstFacade`
- desc: Cloth Asset collection fabric facade class to access cloth fabric data. Constructed from FCollectionClothFacade. Non-const access (read/write) version.
- L116 _public prototype_ `FCollectionClothFabricFacade() = delete;`
- L118 _public prototype_ `FCollectionClothFabricFacade(const FCollectionClothFabricFacade&) = delete;`
- L119 _public prototype_ `FCollectionClothFabricFacade& operator=(const FCollectionClothFabricFacade&) = delete;`
- L121 _public prototype_ `FCollectionClothFabricFacade(FCollectionClothFabricFacade&&) = default;`
- L122 _public prototype_ `FCollectionClothFabricFacade& operator=(FCollectionClothFabricFacade&&) = default;`
- L124 _public prototype_ `virtual ~FCollectionClothFabricFacade() override = default;`
- L127 _public prototype_ `void Initialize(const FAnisotropicData& BendingStiffness, const float BucklingRatio, const FAnisotropicData& BucklingStiffness, const FAnisotropicData& StretchStiffness, const float Density, const float Friction, const float Damping, const float Pressure, const int32 Layer, const float CollisionThickness);` — Initialize the cloth fabric with simulation parameters.
- L132 _public prototype_ `void Initialize(const FCollectionClothFabricConstFacade& OtherFabricFacade);` — Initialize the cloth fabric with another one.
- L135 _public prototype_ `void Initialize(const FCollectionClothFabricConstFacade& OtherFabricFacade, const float Pressure, const int32 Layer, const float CollisionThickness);` — Initialize the cloth fabric from another one and from pattern datas
- L140 _private prototype_ `FCollectionClothFabricFacade(const TSharedRef<class FClothCollection>& InClothCollection, int32 InFabricIndex);`
- L143 _private prototype_ `void SetDefaults();` — Set default values to the fabric properties
- L146 _private prototype_ `void Reset();` — Reset the fabric values properties
- L149 _private prototype_ `TSharedRef<class FClothCollection> GetClothCollection();` — Get the non const cloth collection

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSCLOTHASSET_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Chaos` (scope `UE`)
- L9 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAsset/Public/ChaosClothAsset/CollectionClothFacade.h` (Public)


#### struct `UE::Chaos::ClothAsset::FDefaultSolver`  
`struct FDefaultSolver`  
_L27-33_
- L29 _public member_ `inline static const FVector3f Gravity = FVector3f(0.0f, 0.0f, -980.665f);`
- L30 _public member_ `inline static constexpr float AirDamping = 0.035f;`
- L31 _public member_ `inline static constexpr int32 SubSteps = 1;`
- L32 _public member_ `inline static constexpr float TimeStep = 0.033f;`

#### class `UE::Chaos::ClothAsset::FCollectionClothConstFacade`  
`class FCollectionClothConstFacade`  
_L39-264_
- desc: Cloth Asset collection facade class focused on draping and pattern information. Const access (read only) version.
- L42 _public prototype_ `explicit FCollectionClothConstFacade(const TSharedRef<const FManagedArrayCollection>& ManagedArrayCollection);`
- L44 _public prototype_ `FCollectionClothConstFacade() = delete;`
- L46 _public prototype_ `FCollectionClothConstFacade(const FCollectionClothConstFacade&) = delete;`
- L47 _public prototype_ `FCollectionClothConstFacade& operator=(const FCollectionClothConstFacade&) = delete;`
- L49 _public prototype_ `FCollectionClothConstFacade(FCollectionClothConstFacade&&) = default;`
- L50 _public prototype_ `FCollectionClothConstFacade& operator=(FCollectionClothConstFacade&&) = default;`
- L52 _public prototype_ `virtual ~FCollectionClothConstFacade() = default;`
- L55 _public prototype_ `bool IsValid(EClothCollectionExtendedSchemas OptionalSchemas = EClothCollectionExtendedSchemas::None) const;` — Return whether the facade is defined on the collection.
- L58 _public prototype_ `bool HasValidSimulationData() const;` — Return whether the facade has a non-empty simulation mesh data.
- L61 _public prototype_ `bool HasValidRenderData() const;` — Return whether the facade has a non-empty sim mesh data.
- L64 _public prototype_ `bool HasValidData() const;` — Return whether the facade has a non-empty sim and render mesh data.
- L66 _public prototype_ `uint32 CalculateTypeHash(bool bIncludeWeightMaps, uint32 PreviousHash = 0) const;`
- L67 _public prototype_ `uint32 CalculateWeightMapTypeHash(uint32 PreviousHash = 0) const;`
- L69 _public prototype_ `template<typename T UE_REQUIRES(TIsUserAttributeType<T>::Value)> uint32 CalculateUserDefinedAttributesTypeHash(const FName& GroupName, uint32 PreviousHash = 0) const;`
- L73 _public prototype_ `const FSoftObjectPath& GetPhysicsAssetSoftObjectPathName() const;` — Return the physics asset path names used for this collection.
- L75 _public prototype_ `const FSoftObjectPath& GetSkeletalMeshSoftObjectPathName() const;` — Return the skeleton asset path names used for this collection.
- L77 _public function_ `const FString& GetPhysicsAssetPathName() const` — `UE_DEPRECATED(5.7, "Use GetPhysicsAssetSoftObjectPathName instead")`
- L83 _public function_ `const FString& GetSkeletalMeshPathName() const` — `UE_DEPRECATED(5.7, "Use GetSkeletalMeshSoftObjectPathName instead")`
- L89 _public prototype_ `FName GetReferenceBoneName() const;` — Return the reference bone name used for this collection.
- L90 _public prototype_ `bool GetCopyAllUserAttributesToSimModel() const;`
- L94 _public prototype_ `bool HasSolverElement() const;` — Return true if the solver group has one element
- L96 _public prototype_ `const FVector3f& GetSolverGravity() const;` — Return the solver gravity vector used for this collection.
- L98 _public prototype_ `float GetSolverAirDamping() const;` — Return the solver air damping used for this collection.
- L100 _public prototype_ `float GetSolverTimeStep() const;` — Return the solver time step used for this collection.
- L102 _public prototype_ `int32 GetSolverSubSteps() const;` — Return the solver sub steps used for this collection.
- L106 _public prototype_ `int32 GetNumSimVertices2D() const;` — Return the total number of 2D simulation vertices for this collection.
- L107 _public prototype_ `TConstArrayView<FVector2f> GetSimPosition2D() const;`
- L108 _public prototype_ `TConstArrayView<int32> GetSimVertex3DLookup() const;`
- L109 _public prototype_ `TConstArrayView<int32> GetSimImportVertexID() const;`
- L113 _public prototype_ `int32 GetNumSimVertices3D() const;` — Return the total number of 3D simulation vertices for this collection.
- L114 _public prototype_ `TConstArrayView<FVector3f> GetSimPosition3D() const;`
- L115 _public prototype_ `TConstArrayView<FVector3f> GetPreResizedSimPosition3D() const;`
- L116 _public prototype_ `TConstArrayView<FVector3f> GetSimNormal() const;`
- L117 _public prototype_ `TConstArrayView<TArray<int32>> GetSimBoneIndices() const;`
- L118 _public prototype_ `TConstArrayView<TArray<float>> GetSimBoneWeights() const;`
- L119 _public prototype_ `TConstArrayView<TArray<int32>> GetTetherKinematicIndex() const;`
- L120 _public prototype_ `TConstArrayView<TArray<float>> GetTetherReferenceLength() const;`
- L121 _public prototype_ `TConstArrayView<TArray<int32>> GetSimVertex2DLookup() const;`
- L122 _public prototype_ `TConstArrayView<TArray<int32>> GetSeamStitchLookup() const;`
- L123 _public prototype_ `TConstArrayView<float> GetSimCustomResizingBlend() const;`
- L127 _public prototype_ `int32 GetNumSimFaces() const;` — Return the total number of simulation faces for this collection across all patterns.
- L128 _public prototype_ `TConstArrayView<FIntVector3> GetSimIndices2D() const;`
- L129 _public prototype_ `TConstArrayView<FIntVector3> GetSimIndices3D() const;`
- L133 _public prototype_ `int32 GetNumSimPatterns() const;` — Return the number of patterns in this collection.
- L135 _public prototype_ `FCollectionClothSimPatternConstFacade GetSimPattern(int32 PatternIndex) const;` — Return a pattern facade for the specified pattern index.
- L137 _public prototype_ `int32 FindSimPatternByVertex2D(int32 Vertex2DIndex) const;` — Convenience to find which sim pattern a 2D vertex belongs to
- L139 _public prototype_ `int32 FindSimPatternByFaceIndex(int32 FaceIndex) const;` — Convenience to find which sim pattern a sim face belongs to
- L143 _public prototype_ `int32 GetNumSimMorphTargets() const;` — Return the number of sim morph targets in this collection.
- L145 _public prototype_ `int32 FindSimMorphTargetIndexByName(const FString& MorphTargetName) const;` — Lookup sim morph target by name. Returns INDEX_NONE if not found.
- L147 _public prototype_ `FCollectionClothSimMorphTargetConstFacade GetSimMorphTarget(int32 MorphTargetIndex) const;` — Return a sim morph target facade for the specified morph target index.
- L149 _public prototype_ `TConstArrayView<FString> GetSimMorphTargetName() const;` — Return a view of all sim morph target names
- L153 _public prototype_ `int32 GetNumSimAccessoryMeshes() const;` — Return the number of accessory meshes in this collection.
- L155 _public prototype_ `int32 FindSimAccessoryMeshIndexByName(const FName& AccessoryMeshName) const;` — Lookup sim accessory mesh by name. Returns INDEX_NONE if not found.
- L157 _public prototype_ `FCollectionClothSimAccessoryMeshConstFacade GetSimAccessoryMesh(int32 MeshIndex) const;` — Return the sim accessory mesh facade for the specified accessor mesh index
- L158 _public prototype_ `TConstArrayView<FName> GetSimAccessoryMeshName() const;`
- L159 _public prototype_ `TConstArrayView<FName> GetSimAccessoryMeshPosition3DAttribute() const;`
- L160 _public prototype_ `TConstArrayView<FName> GetSimAccessoryMeshNormalAttribute() const;`
- L161 _public prototype_ `TConstArrayView<FName> GetSimAccessoryMeshBoneIndicesAttribute() const;`
- L162 _public prototype_ `TConstArrayView<FName> GetSimAccessoryMeshBoneWeightsAttribute() const;`
- L166 _public prototype_ `int32 GetNumSimMorphTargetVertices() const;` — Return the total number of sim morph target vertices in this collection.
- L168 _public prototype_ `TConstArrayView<FVector3f> GetSimMorphTargetPositionDelta() const;` — Return a view of all sim morph target position deltas
- L170 _public prototype_ `TConstArrayView<FVector3f> GetSimMorphTargetTangentZDelta() const;` — Return a view of all sim morph target tangent z deltas
- L172 _public prototype_ `TConstArrayView<int32> GetSimMorphTargetSimVertex3DIndex() const;` — Return a view of all sim morph target sim vertex 3d indices
- L176 _public prototype_ `int32 GetNumRenderPatterns() const;` — Return the number of patterns in this collection.
- L178 _public prototype_ `FCollectionClothRenderPatternConstFacade GetRenderPattern(int32 PatternIndex) const;` — Return a pattern facade for the specified pattern index.
- L180 _public prototype_ `TConstArrayView<int32> GetRenderDeformerNumInfluences() const;` — Return a view of all the render deformer number of influences used on this collection across all patterns.
- L182 _public prototype_ `TConstArrayView<FSoftObjectPath> GetRenderMaterialSoftObjectPathName() const;` — Return a view of all the render materials used on this collection across all patterns.
- L184 _public prototype_ `int32 FindRenderPatternByVertex(int32 VertexIndex) const;` — Convenience to find which render pattern a render vertex belongs to
- L186 _public prototype_ `int32 FindRenderPatternByFaceIndex(int32 FaceIndex) const;` — Convenience to find which render pattern a render face belongs to
- L188 _public function_ `TConstArrayView<FString> GetRenderMaterialPathName() const` — `UE_DEPRECATED(5.7, "Use GetRenderMaterialSoftObjectPathName instead")`
- L195 _public prototype_ `int32 GetNumSeams() const;` — Return the number of seams in this collection.
- L197 _public prototype_ `FCollectionClothSeamConstFacade GetSeam(int32 SeamIndex) const;` — Return a seam facade for the specified seam index.
- L201 _public prototype_ `int32 GetNumFabrics() const;` — Return the number of fabrics in this collection.
- L203 _public prototype_ `FCollectionClothFabricConstFacade GetFabric(int32 FabricIndex) const;` — Return a fabric facade for the specified fabric index.
- L207 _public prototype_ `int32 GetNumRenderVertices() const;` — Return the total number of render vertices for this collection.
- L208 _public prototype_ `TConstArrayView<FVector3f> GetRenderPosition() const;`
- L209 _public prototype_ `TConstArrayView<FVector3f> GetRenderNormal() const;`
- L210 _public prototype_ `TConstArrayView<FVector3f> GetRenderTangentU() const;`
- L211 _public prototype_ `TConstArrayView<FVector3f> GetRenderTangentV() const;`
- L212 _public prototype_ `TConstArrayView<TArray<FVector2f>> GetRenderUVs() const;`
- L213 _public prototype_ `TConstArrayView<FLinearColor> GetRenderColor() const;`
- L214 _public prototype_ `TConstArrayView<TArray<int32>> GetRenderBoneIndices() const;`
- L215 _public prototype_ `TConstArrayView<TArray<float>> GetRenderBoneWeights() const;`
- L216 _public prototype_ `TConstArrayView<TArray<FVector4f>> GetRenderDeformerPositionBaryCoordsAndDist() const;`
- L217 _public prototype_ `TConstArrayView<TArray<FVector4f>> GetRenderDeformerNormalBaryCoordsAndDist() const;`
- L218 _public prototype_ `TConstArrayView<TArray<FVector4f>> GetRenderDeformerTangentBaryCoordsAndDist() const;`
- L219 _public prototype_ `TConstArrayView<TArray<FIntVector3>> GetRenderDeformerSimIndices3D() const;`
- L220 _public prototype_ `TConstArrayView<TArray<float>> GetRenderDeformerWeight() const;`
- L221 _public prototype_ `TConstArrayView<float> GetRenderDeformerSkinningBlend() const;`
- L222 _public prototype_ `TConstArrayView<float> GetRenderCustomResizingBlend() const;`
- L225 _public prototype_ `int32 GetNumRenderFaces() const;`
- L226 _public prototype_ `TConstArrayView<FIntVector3> GetRenderIndices() const;`
- L229 _public prototype_ `int32 GetNumCustomResizingRegions() const;`
- L230 _public prototype_ `TConstArrayView<FString> GetCustomResizingRegionSet() const;`
- L231 _public prototype_ `TConstArrayView<int32> GetCustomResizingRegionType() const;`
- L235 _public prototype_ `bool HasWeightMap(const FName& Name) const;` — Return whether this cloth collection has the specified weight map.
- L237 _public prototype_ `TArray<FName> GetWeightMapNames() const;` — Return the name of all user weight maps on this cloth collection.
- L238 _public prototype_ `TConstArrayView<float> GetWeightMap(const FName& Name) const;`
- L242 _public prototype_ `template<typename T UE_REQUIRES(TIsUserAttributeType<T>::Value)> bool HasUserDefinedAttribute(const FName& Name, const FName& GroupName) const;`
- L244 _public prototype_ `template<typename T UE_REQUIRES(TIsUserAttributeType<T>::Value)> TArray<FName> GetUserDefinedAttributeNames(const FName& GroupName) const;`
- L246 _public prototype_ `template<typename T UE_REQUIRES(TIsUserAttributeType<T>::Value)> TConstArrayView<T> GetUserDefinedAttribute(const FName& Name, const FName& GroupName) const;`
- L247 _public prototype_ `static bool IsValidClothCollectionGroupName(const FName& GroupName);`
- L248 _public prototype_ `static TArray<FName> GetValidClothCollectionGroupName();`
- L250 _public prototype_ `void BuildSimulationMesh(TArray<FVector3f>& Positions, TArray<FVector3f>& Normals, TArray<uint32>& Indices, TArray<FVector2f>& PatternsPositions, TArray<uint32>& PatternsIndices, TArray<uint32>& PatternToWeldedIndices, TArray<TArray<int32>>* OptionalWeldedToPatternIndices = nullptr) const;`
- L254 _protected prototype_ `explicit FCollectionClothConstFacade(const TSharedRef<const class FConstClothCollection>& ClothCollection);`

#### class `UE::Chaos::ClothAsset::FCollectionClothFacade`  
`class FCollectionClothFacade final : public FCollectionClothConstFacade`  
_L270-514_
- inherits: `FCollectionClothConstFacade`
- desc: Cloth Asset collection facade class focused on draping and pattern information. Non-const access (read/write) version.
- L273 _public prototype_ `explicit FCollectionClothFacade(const TSharedRef<FManagedArrayCollection>& ManagedArrayCollection);`
- L275 _public prototype_ `FCollectionClothFacade() = delete;`
- L277 _public prototype_ `FCollectionClothFacade(const FCollectionClothFacade&) = delete;`
- L278 _public prototype_ `FCollectionClothFacade& operator=(const FCollectionClothFacade&) = delete;`
- L280 _public prototype_ `FCollectionClothFacade(FCollectionClothFacade&&) = default;`
- L281 _public prototype_ `FCollectionClothFacade& operator=(FCollectionClothFacade&&) = default;`
- L282 _public prototype_ `virtual ~FCollectionClothFacade() override = default;`
- L285 _public prototype_ `void DefineSchema(EClothCollectionExtendedSchemas OptionalSchemas = EClothCollectionExtendedSchemas::None);` — Create this facade's groups and attributes.
- L288 _public prototype_ `void PostSerialize(const FArchive& Ar);` — Post-Serialize upgrade cloth collection
- L291 _public prototype_ `void Reset();` — Remove all LODs from this cloth.
- L294 _public prototype_ `void Initialize(const FCollectionClothConstFacade& Other);` — Initialize the cloth using another cloth collection.
- L297 _public prototype_ `void Append(const FCollectionClothConstFacade& Other);` — Append data from another cloth collection.
- L300 _public prototype_ `void InitializeCookedOnly(const FCollectionClothConstFacade& Other);` — Copy only data that is not stripped on cook
- L304 _public prototype_ `void SetPhysicsAssetSoftObjectPathName(const FSoftObjectPath& PathName);` — Set the physics asset path name.
- L306 _public prototype_ `void SetSkeletalMeshSoftObjectPathName(const FSoftObjectPath& PathName);` — Set the skeletal mesh asset path name and the reference skeleton that will be used with this asset.
- L308 _public function_ `void SetPhysicsAssetPathName(const FString& PathName)` — `UE_DEPRECATED(5.7, "Use SetPhysicsAssetSoftObjectPathName instead")`
- L310 _public function_ `void SetSkeletalMeshPathName(const FString& PathName)` — `UE_DEPRECATED(5.7, "Use SetSkeletalMeshSoftObjectPathName instead")`
- L312 _public prototype_ `void SetReferenceBoneName(const FName& BoneName);` — Set the reference bone name for this asset.
- L314 _public prototype_ `void SetCopyAllUserAttributesToSimModel(bool bValue);` — Set whether all attributes should be copied to the FChaosClothSimulationModel (else legacy behavior of skipping unused sets and face int maps will be followed).
- L318 _public prototype_ `void SetSolverGravity(const FVector3f& SolverGravity);` — Set the solver gravity
- L320 _public prototype_ `void SetSolverAirDamping(const float SolverAirDamping);` — Set the solver air damping
- L322 _public prototype_ `void SetSolverTimeStep(const float SolverTimeStep);` — Set the solver time step
- L324 _public prototype_ `void SetSolverSubSteps(const int32 SolverSubSteps);` — Set the solver substeps
- L328 _public prototype_ `TArrayView<FVector2f> GetSimPosition2D();` — SetNumSimVertices2D per pattern within pattern facade.
- L329 _public prototype_ `TArrayView<int32> GetSimImportVertexID();`
- L332 _public prototype_ `TArrayView<FVector3f> GetSimPosition3D();`
- L333 _public prototype_ `TArrayView<FVector3f> GetPreResizedSimPosition3D();`
- L334 _public prototype_ `TArrayView<FVector3f> GetSimNormal();`
- L335 _public prototype_ `TArrayView<TArray<int32>> GetSimBoneIndices();`
- L336 _public prototype_ `TArrayView<TArray<float>> GetSimBoneWeights();`
- L337 _public prototype_ `TArrayView<TArray<int32>> GetTetherKinematicIndex();`
- L338 _public prototype_ `TArrayView<TArray<float>> GetTetherReferenceLength();`
- L339 _public prototype_ `TArrayView<float> GetSimCustomResizingBlend();`
- L342 _public prototype_ `void RemoveSimVertices3D(int32 NumSimVertices);` — This will remove the 3D vertices, but the associated seams and 2D vertices will still exist, and point to INDEX_NONE
- L343 _public function_ `void RemoveAllSimVertices3D()`
- L344 _public prototype_ `void RemoveSimVertices3D(const TArray<int32>& SortedDeletionList);`
- L346 _public prototype_ `void CompactSimVertex2DLookup();` — Compact SimVertex2DLookup to remove any references to INDEX_NONE that may have been created by deleting 2D vertices.
- L348 _public prototype_ `void CompactSeamStitchLookup();` — Compact SeamStitchLookup to remove any references to INDEX_NONE that may have been created by deleting stitches.
- L352 _public prototype_ `TArrayView<FIntVector3> GetSimIndices2D();` — SetNumSimFaces per pattern within pattern facade.
- L353 _public prototype_ `TArrayView<FIntVector3> GetSimIndices3D();`
- L357 _public prototype_ `void SetNumSimPatterns(int32 NumPatterns);` — Set the new number of patterns to this cloth LOD.
- L359 _public prototype_ `int32 AddSimPattern();` — Add a new pattern to this cloth LOD and return its index in the LOD pattern list.
- L361 _public prototype_ `FCollectionClothSimPatternFacade GetSimPattern(int32 PatternIndex);` — Return a pattern facade for the specified pattern index.
- L363 _public function_ `FCollectionClothSimPatternFacade AddGetSimPattern()` — Add a new pattern to this cloth LOD, and return the cloth pattern facade set to its index.
- L365 _public prototype_ `void RemoveSimPatterns(const TArray<int32>& SortedDeletionList);` — Remove a sorted list of sim patterns.
- L369 _public prototype_ `void SetNumSimMorphTargets(int32 NumMorphTargets, bool bCookedOnly = false);` — Set the new number of sim morph targets to this cloth.
- L371 _public prototype_ `int32 AddSimMorphTarget();` — Add a sim morph target to this cloth and return its index in the sim morph target pattern list
- L373 _public prototype_ `FCollectionClothSimMorphTargetFacade GetSimMorphTarget(int32 MorphTargetIndex);` — Return a sim morph target facade for the specified morph target index.
- L375 _public function_ `FCollectionClothSimMorphTargetFacade AddGetSimMorphTarget()` — Add a new sim morph target to this cloth, and return the morph target facade set to its index.
- L377 _public prototype_ `void RemoveSimMorphTargets(const TArray<int32>& SortedDeletionList);` — Remove a sorted list of sim morph targets.
- L379 _public prototype_ `void CompactSimMorphTargets();` — Remove all morph target vertices with invalid indices. This will also remove any morph targets that are empty.
- L383 _public prototype_ `TArrayView<FVector3f> GetSimMorphTargetPositionDelta();` — Return a view of all sim morph target position deltas
- L385 _public prototype_ `TArrayView<FVector3f> GetSimMorphTargetTangentZDelta();` — Return a view of all sim morph target tangent z deltas
- L387 _public prototype_ `TArrayView<int32> GetSimMorphTargetSimVertex3DIndex();` — Return a view of all sim morph target sim vertex 3d indices
- L389 _public prototype_ `void RemoveSimMorphTargetVertices3D(const TArray<int32>& SortedDeletionList);` — Remove a sorted list of sim morph target vertices.
- L393 _public prototype_ `void SetNumSimAccessoryMeshes(int32 NumMeshes, bool bCookedOnly = false);` — Set the new number of accessory meshes to this cloth.
- L395 _public prototype_ `int32 AddSimAccessoryMesh();` — Add a new accessory mesh to this cloth and return its index in the accessory mesh list.
- L397 _public prototype_ `FCollectionClothSimAccessoryMeshFacade GetSimAccessoryMesh(int32 MeshIndex);` — Return an accessory mesh facade for the specified accessory mesh index.
- L399 _public function_ `FCollectionClothSimAccessoryMeshFacade AddGetSimAccessoryMesh()` — Add a new accessory mesh to this cloth and return the accessory mesh facade set to its index.
- L401 _public prototype_ `void RemoveSimAccessoryMeshes(const TArray<int32>& SortedDeletionList);` — Remove a sorted list of accessory meshes.
- L402 _public prototype_ `TArrayView<FName> GetSimAccessoryMeshName();`
- L403 _public prototype_ `TArrayView<FName> GetSimAccessoryMeshPosition3DAttribute();`
- L404 _public prototype_ `TArrayView<FName> GetSimAccessoryMeshNormalAttribute();`
- L405 _public prototype_ `TArrayView<FName> GetSimAccessoryMeshBoneIndicesAttribute();`
- L406 _public prototype_ `TArrayView<FName> GetSimAccessoryMeshBoneWeightsAttribute();`
- L410 _public prototype_ `void SetNumRenderPatterns(int32 NumPatterns);` — Set the new number of patterns to this cloth LOD.
- L412 _public prototype_ `int32 AddRenderPattern();` — Add a new pattern to this cloth LOD and return its index in the LOD pattern list.
- L414 _public prototype_ `FCollectionClothRenderPatternFacade GetRenderPattern(int32 PatternIndex);` — Return a pattern facade for the specified pattern index.
- L416 _public function_ `FCollectionClothRenderPatternFacade AddGetRenderPattern()` — Add a new pattern to this cloth LOD, and return the cloth pattern facade set to its index.
- L418 _public prototype_ `void RemoveRenderPatterns(const TArray<int32>& SortedDeletionList);` — Remove a sorted list of render patterns.
- L420 _public prototype_ `TArrayView<int32> GetRenderDeformerNumInfluences();` — Return a view of all the render deformer number of influences used on this collection across all patterns.
- L422 _public prototype_ `TArrayView<FSoftObjectPath> GetRenderMaterialSoftObjectPathName();` — Return a view of all the render materials used on this collection across all patterns.
- L424 _public function_ `TArrayView<FString> GetRenderMaterialPathName()` — `UE_DEPRECATED(5.7, "Use GetRenderMaterialSoftObjectPathName instead")`
- L431 _public prototype_ `void SetNumSeams(int32 NumSeams);` — Set the new number of seams to this cloth.
- L433 _public prototype_ `int32 AddSeam();` — Add a new seam to this cloth and return its index in the seam list.
- L435 _public prototype_ `FCollectionClothSeamFacade GetSeam(int32 SeamIndex);` — Return a seam facade for the specified seam index.
- L437 _public function_ `FCollectionClothSeamFacade AddGetSeam()` — Add a new seam to this cloth and return the seam facade set to its index.
- L439 _public prototype_ `void RemoveSeams(const TArray<int32>& SortedDeletionList);` — Remove a sorted list of seams.
- L443 _public prototype_ `void SetNumFabrics(int32 NumFabrics);` — Set the new number of fabrics to this cloth.
- L445 _public prototype_ `int32 AddFabric();` — Add a new fabric to this cloth and return its index in the fabric list.
- L447 _public prototype_ `FCollectionClothFabricFacade GetFabric(int32 FabricIndex);` — Return a fabric facade for the specified fabric index.
- L449 _public function_ `FCollectionClothFabricFacade AddGetFabric()` — Add a new fabric to this cloth and return the fabric facade set to its index.
- L451 _public prototype_ `void RemoveFabrics(const TArray<int32>& SortedDeletionList);` — Remove a sorted list of fabrics.
- L455 _public prototype_ `TArrayView<FVector3f> GetRenderPosition();` — SetNumRenderVertices per pattern within pattern facade.
- L456 _public prototype_ `TArrayView<FVector3f> GetRenderNormal();`
- L457 _public prototype_ `TArrayView<FVector3f> GetRenderTangentU();`
- L458 _public prototype_ `TArrayView<FVector3f> GetRenderTangentV();`
- L459 _public prototype_ `TArrayView<TArray<FVector2f>> GetRenderUVs();`
- L460 _public prototype_ `TArrayView<FLinearColor> GetRenderColor();`
- L461 _public prototype_ `TArrayView<TArray<int32>> GetRenderBoneIndices();`
- L462 _public prototype_ `TArrayView<TArray<float>> GetRenderBoneWeights();`
- L463 _public prototype_ `TArrayView<TArray<FVector4f>> GetRenderDeformerPositionBaryCoordsAndDist();`
- L464 _public prototype_ `TArrayView<TArray<FVector4f>> GetRenderDeformerNormalBaryCoordsAndDist();`
- L465 _public prototype_ `TArrayView<TArray<FVector4f>> GetRenderDeformerTangentBaryCoordsAndDist();`
- L466 _public prototype_ `TArrayView<TArray<FIntVector3>> GetRenderDeformerSimIndices3D();`
- L467 _public prototype_ `TArrayView<TArray<float>> GetRenderDeformerWeight();`
- L468 _public prototype_ `TArrayView<float> GetRenderDeformerSkinningBlend();`
- L469 _public prototype_ `TArrayView<float> GetRenderCustomResizingBlend();`
- L473 _public prototype_ `TArrayView<FIntVector3> GetRenderIndices();` — SetNumRenderFaces per pattern within pattern facade.
- L476 _public prototype_ `void SetNumCustomResizingRegions(int32 NumGroups);`
- L477 _public prototype_ `TArrayView<FString> GetCustomResizingRegionSet();`
- L478 _public prototype_ `TArrayView<int32> GetCustomResizingRegionType();`
- L482 _public prototype_ `void AddWeightMap(const FName& Name);` — Add a new weight map to this cloth. Access is then done per pattern.
- L484 _public prototype_ `void RemoveWeightMap(const FName& Name);` — Remove a weight map from this cloth.
- L485 _public prototype_ `TArrayView<float> GetWeightMap(const FName& Name);`
- L490 _public prototype_ `template<typename T UE_REQUIRES(TIsUserAttributeType<T>::Value)> bool AddUserDefinedAttribute(const FName& Name, const FName& GroupName, const FName& GroupDependency = NAME_None);` — GroupName must be an existing group as defined in ClothCollectionGroup. Returns success
- L491 _public prototype_ `void RemoveUserDefinedAttribute(const FName& Name, const FName& GroupName);`
- L493 _public prototype_ `template<typename T UE_REQUIRES(TIsUserAttributeType<T>::Value)> TArrayView<T> GetUserDefinedAttribute(const FName& Name, const FName& GroupName);`
- L497 _private prototype_ `void SetDefaults();`
- L499 _private prototype_ `TSharedRef<class FClothCollection> GetClothCollection();`
- L505 _private prototype_ `explicit FCollectionClothFacade(const TSharedRef<class FClothCollection>& InClothCollection);`
- L509 _private prototype_ `TArrayView<int32> GetSimVertex3DLookupPrivate();`
- L512 _private prototype_ `TArrayView<TArray<int32>> GetSeamStitchLookupPrivate();`
- L513 _private prototype_ `TArrayView<TArray<int32>> GetSimVertex2DLookupPrivate();`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API CHAOSCLOTHASSET_API`
- L20 _namespace_ `namespace Chaos`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Chaos` (scope `UE`)
- L25 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAsset/Public/ChaosClothAsset/CollectionClothRenderPatternFacade.h` (Public)


#### class `UE::Chaos::ClothAsset::FCollectionClothRenderPatternConstFacade`  
`class FCollectionClothRenderPatternConstFacade`  
_L18-86_
- desc: Cloth Asset collection render pattern facade class to access cloth render pattern data. Constructed from FCollectionClothConstFacade. Const access (read only) version.
- L21 _public prototype_ `FCollectionClothRenderPatternConstFacade() = delete;`
- L23 _public prototype_ `FCollectionClothRenderPatternConstFacade(const FCollectionClothRenderPatternConstFacade&) = delete;`
- L24 _public prototype_ `FCollectionClothRenderPatternConstFacade& operator=(const FCollectionClothRenderPatternConstFacade&) = delete;`
- L26 _public prototype_ `FCollectionClothRenderPatternConstFacade(FCollectionClothRenderPatternConstFacade&&) = default;`
- L27 _public prototype_ `FCollectionClothRenderPatternConstFacade& operator=(FCollectionClothRenderPatternConstFacade&&) = default;`
- L29 _public prototype_ `virtual ~FCollectionClothRenderPatternConstFacade() = default;`
- L32 _public prototype_ `int32 GetRenderDeformerNumInfluences() const;` — Return the render deformer number of influences for this pattern.
- L34 _public prototype_ `const FSoftObjectPath& GetRenderMaterialSoftObjectPathName() const;` — Return the render material for this pattern.
- L36 _public function_ `const FString& GetRenderMaterialPathName() const` — `UE_DEPRECATED(5.7, "Use GetRenderMaterialSoftObjectPathName instead")`
- L45 _public prototype_ `int32 GetNumRenderVertices() const;` — Return the total number of render vertices for this pattern.
- L47 _public prototype_ `int32 GetRenderVerticesOffset() const;` — Return the render vertices offset for this pattern in the render vertices for the collection.
- L48 _public prototype_ `TConstArrayView<FVector3f> GetRenderPosition() const;`
- L49 _public prototype_ `TConstArrayView<FVector3f> GetRenderNormal() const;`
- L50 _public prototype_ `TConstArrayView<FVector3f> GetRenderTangentU() const;`
- L51 _public prototype_ `TConstArrayView<FVector3f> GetRenderTangentV() const;`
- L52 _public prototype_ `TConstArrayView<TArray<FVector2f>> GetRenderUVs() const;`
- L53 _public prototype_ `TConstArrayView<FLinearColor> GetRenderColor() const;`
- L54 _public prototype_ `TConstArrayView<TArray<int32>> GetRenderBoneIndices() const;`
- L55 _public prototype_ `TConstArrayView<TArray<float>> GetRenderBoneWeights() const;`
- L56 _public prototype_ `TConstArrayView<TArray<FVector4f>> GetRenderDeformerPositionBaryCoordsAndDist() const;`
- L57 _public prototype_ `TConstArrayView<TArray<FVector4f>> GetRenderDeformerNormalBaryCoordsAndDist() const;`
- L58 _public prototype_ `TConstArrayView<TArray<FVector4f>> GetRenderDeformerTangentBaryCoordsAndDist() const;`
- L59 _public prototype_ `TConstArrayView<TArray<FIntVector3>> GetRenderDeformerSimIndices3D() const;`
- L60 _public prototype_ `TConstArrayView<TArray<float>> GetRenderDeformerWeight() const;`
- L61 _public prototype_ `TConstArrayView<float> GetRenderDeformerSkinningBlend() const;`
- L62 _public prototype_ `TConstArrayView<float> GetRenderCustomResizingBlend() const;`
- L66 _public prototype_ `int32 GetNumRenderFaces() const;` — Note: RenderIndices points to the collection arrays, not the pattern arrays
- L68 _public prototype_ `int32 GetRenderFacesOffset() const;` — Return the render faces offset for this pattern in the render faces
- L69 _public prototype_ `TConstArrayView<FIntVector3> GetRenderIndices() const;`
- L71 _public prototype_ `bool IsEmpty() const;`
- L74 _public function_ `int32 GetPatternIndex() const` — Return the Pattern index this facade has been created with.
- L79 _protected prototype_ `FCollectionClothRenderPatternConstFacade(const TSharedRef<const class FConstClothCollection>& InClothCollection, int32 InPatternIndex);`
- L81 _protected function_ `static constexpr int32 GetBaseElementIndex()`
- L82 _protected function_ `int32 GetElementIndex() const`
- L85 _protected member_ `int32 PatternIndex;`

#### class `UE::Chaos::ClothAsset::FCollectionClothRenderPatternFacade`  
`class FCollectionClothRenderPatternFacade final : public FCollectionClothRenderPatternConstFacade`  
_L93-157_
- inherits: `FCollectionClothRenderPatternConstFacade`
- desc: Cloth Asset collection render pattern facade class to access cloth render pattern data. Constructed from FCollectionClothFacade. Non-const access (read/write) version.
- L96 _public prototype_ `FCollectionClothRenderPatternFacade() = delete;`
- L98 _public prototype_ `FCollectionClothRenderPatternFacade(const FCollectionClothRenderPatternFacade&) = delete;`
- L99 _public prototype_ `FCollectionClothRenderPatternFacade& operator=(const FCollectionClothRenderPatternFacade&) = delete;`
- L101 _public prototype_ `FCollectionClothRenderPatternFacade(FCollectionClothRenderPatternFacade&&) = default;`
- L102 _public prototype_ `FCollectionClothRenderPatternFacade& operator=(FCollectionClothRenderPatternFacade&&) = default;`
- L104 _public prototype_ `virtual ~FCollectionClothRenderPatternFacade() override = default;`
- L107 _public prototype_ `void Reset();` — Remove all geometry from this cloth pattern.
- L110 _public prototype_ `void Initialize(const FCollectionClothRenderPatternConstFacade& Other, int32 SimVertex3DOffset);` — Initialize from another render pattern. Assumes all indices match between source and target.
- L114 _public function_ `void Initialize(const FCollectionClothRenderPatternConstFacade& Other)` — `UE_DEPRECATED(5.4, "Use Initialize with the SimVertex3DOffset instead")` — Initialize from another render pattern. Assumes all indices match between source and target.
- L117 _public prototype_ `void SetRenderDeformerNumInfluences(int32 NumInfluences);` — Set the render deformer number of influences for this pattern.
- L119 _public prototype_ `void SetRenderMaterialSoftObjectPathName(const FSoftObjectPath& PathName);` — Set the render material for this pattern.
- L121 _public function_ `void SetRenderMaterialPathName(const FString& PathName)` — `UE_DEPRECATED(5.7, "Use SetRenderMaterialSoftObjectPathName instead")`
- L126 _public prototype_ `void SetNumRenderVertices(int32 NumRenderVertices);` — Grow or shrink the space reserved for render vertices for this pattern within the cloth collection and return its start index.
- L127 _public prototype_ `void RemoveRenderVertices(const TArray<int32>& SortedDeletionList);`
- L128 _public prototype_ `TArrayView<FVector3f> GetRenderPosition();`
- L129 _public prototype_ `TArrayView<FVector3f> GetRenderNormal();`
- L130 _public prototype_ `TArrayView<FVector3f> GetRenderTangentU();`
- L131 _public prototype_ `TArrayView<FVector3f> GetRenderTangentV();`
- L132 _public prototype_ `TArrayView<TArray<FVector2f>> GetRenderUVs();`
- L133 _public prototype_ `TArrayView<FLinearColor> GetRenderColor();`
- L134 _public prototype_ `TArrayView<TArray<int32>> GetRenderBoneIndices();`
- L135 _public prototype_ `TArrayView<TArray<float>> GetRenderBoneWeights();`
- L136 _public prototype_ `TArrayView<TArray<FVector4f>> GetRenderDeformerPositionBaryCoordsAndDist();`
- L137 _public prototype_ `TArrayView<TArray<FVector4f>> GetRenderDeformerNormalBaryCoordsAndDist();`
- L138 _public prototype_ `TArrayView<TArray<FVector4f>> GetRenderDeformerTangentBaryCoordsAndDist();`
- L139 _public prototype_ `TArrayView<TArray<FIntVector3>> GetRenderDeformerSimIndices3D();`
- L140 _public prototype_ `TArrayView<TArray<float>> GetRenderDeformerWeight();`
- L141 _public prototype_ `TArrayView<float> GetRenderDeformerSkinningBlend();`
- L142 _public prototype_ `TArrayView<float> GetRenderCustomResizingBlend();`
- L146 _public prototype_ `void SetNumRenderFaces(int32 NumRenderFaces);` — Grow or shrink the space reserved for render faces for this pattern within the cloth collection and return its start index.
- L147 _public prototype_ `void RemoveRenderFaces(const TArray<int32>& SortedDeletionList);`
- L148 _public prototype_ `TArrayView<FIntVector3> GetRenderIndices();`
- L152 _private prototype_ `FCollectionClothRenderPatternFacade(const TSharedRef<class FClothCollection>& InClothCollection, int32 InPatternIndex);`
- L154 _private prototype_ `void SetDefaults();`
- L156 _private prototype_ `TSharedRef<class FClothCollection> GetClothCollection();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSCLOTHASSET_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Chaos` (scope `UE`)
- L11 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAsset/Public/ChaosClothAsset/CollectionClothSeamFacade.h` (Public)


#### class `UE::Chaos::ClothAsset::FCollectionClothSeamConstFacade`  
`class FCollectionClothSeamConstFacade`  
_L16-55_
- desc: Cloth Asset collection seam facade class to access cloth seam data. Constructed from FCollectionClothConstFacade. Const access (read only) version.
- L19 _public prototype_ `FCollectionClothSeamConstFacade() = delete;`
- L21 _public prototype_ `FCollectionClothSeamConstFacade(const FCollectionClothSeamConstFacade&) = delete;`
- L22 _public prototype_ `FCollectionClothSeamConstFacade& operator=(const FCollectionClothSeamConstFacade&) = delete;`
- L24 _public prototype_ `FCollectionClothSeamConstFacade(FCollectionClothSeamConstFacade&&) = default;`
- L25 _public prototype_ `FCollectionClothSeamConstFacade& operator=(FCollectionClothSeamConstFacade&&) = default;`
- L27 _public prototype_ `virtual ~FCollectionClothSeamConstFacade() = default;`
- L30 _public prototype_ `int32 GetNumSeamStitches() const;` — Return the total number of stitches for this seam.
- L33 _public prototype_ `int32 GetSeamStitchesOffset() const;` — Return the seam stitch offset for this seam in the seam stitches for the cloth.
- L37 _public prototype_ `TConstArrayView<FIntVector2> GetSeamStitch2DEndIndices() const;` — Indices correspond with the FCollectionClothConstFacade indices
- L38 _public prototype_ `TConstArrayView<int32> GetSeamStitch3DIndex() const;`
- L41 _public function_ `int32 GetSeamIndex() const` — Return the seam index this facade has been created with.
- L43 _public prototype_ `void ValidateSeam() const;`
- L48 _protected prototype_ `FCollectionClothSeamConstFacade(const TSharedRef<const class FConstClothCollection>& InClothCollection, int32 SeamIndex);`
- L50 _protected function_ `static constexpr int32 GetBaseElementIndex()`
- L51 _protected function_ `int32 GetElementIndex() const`
- L54 _protected member_ `int32 SeamIndex;`

#### class `UE::Chaos::ClothAsset::FCollectionClothSeamFacade`  
`class FCollectionClothSeamFacade final : public FCollectionClothSeamConstFacade`  
_L62-100_
- inherits: `FCollectionClothSeamConstFacade`
- desc: Cloth Asset collection seam facade class to access cloth seam data. Constructed from FCollectionClothFacade. Non-const access (read/write) version.
- L65 _public prototype_ `FCollectionClothSeamFacade() = delete;`
- L67 _public prototype_ `FCollectionClothSeamFacade(const FCollectionClothSeamFacade&) = delete;`
- L68 _public prototype_ `FCollectionClothSeamFacade& operator=(const FCollectionClothSeamFacade&) = delete;`
- L70 _public prototype_ `FCollectionClothSeamFacade(FCollectionClothSeamFacade&&) = default;`
- L71 _public prototype_ `FCollectionClothSeamFacade& operator=(FCollectionClothSeamFacade&&) = default;`
- L73 _public prototype_ `virtual ~FCollectionClothSeamFacade() override = default;`
- L76 _public prototype_ `void Reset();` — Remove all stitches from this seam.
- L79 _public prototype_ `void Initialize(TConstArrayView<FIntVector2> Stitches);` — Initialize from a list of stitches
- L82 _public prototype_ `void Initialize(const FCollectionClothSeamConstFacade& Other, const int32 SimVertex2DOffset, const int32 SimVertex3DOffset);` — Initialize from another seam.
- L85 _public prototype_ `void CleanupAndCompact();` — Clean up references to invalid indices, including updating stitches to maintain topology.
- L89 _private prototype_ `FCollectionClothSeamFacade(const TSharedRef<class FClothCollection>& InClothCollection, int32 SeamIndex);`
- L91 _private prototype_ `void SetDefaults();`
- L95 _private prototype_ `void SetNumSeamStitches(const int32 NumStitches);` — Indices correspond with the FCollectionClothConstFacade indices (e.g., not pattern indices)
- L96 _private prototype_ `TArrayView<FIntVector2> GetSeamStitch2DEndIndices();`
- L97 _private prototype_ `TArrayView<int32> GetSeamStitch3DIndex();`
- L99 _private prototype_ `TSharedRef<class FClothCollection> GetClothCollection();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSCLOTHASSET_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Chaos` (scope `UE`)
- L9 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAsset/Public/ChaosClothAsset/CollectionClothSelectionFacade.h` (Public)


#### class `UE::Chaos::ClothAsset::FCollectionClothSelectionConstFacade`  
`class FCollectionClothSelectionConstFacade`  
_L16-68_
- desc: Cloth Asset collection Selection facade class. Each Selection consists of a set of integer indices, a name, and a string representing the type of element being indexed. Const access (read only) version.
- L19 _public prototype_ `explicit FCollectionClothSelectionConstFacade(const TSharedRef<const FManagedArrayCollection>& ManagedArrayCollection);`
- L21 _public prototype_ `FCollectionClothSelectionConstFacade() = delete;`
- L22 _public prototype_ `FCollectionClothSelectionConstFacade(const FCollectionClothSelectionConstFacade&) = delete;`
- L23 _public prototype_ `FCollectionClothSelectionConstFacade& operator=(const FCollectionClothSelectionConstFacade&) = delete;`
- L24 _public prototype_ `FCollectionClothSelectionConstFacade(FCollectionClothSelectionConstFacade&&) = default;`
- L25 _public prototype_ `FCollectionClothSelectionConstFacade& operator=(FCollectionClothSelectionConstFacade&&) = default;`
- L26 _public prototype_ `virtual ~FCollectionClothSelectionConstFacade() = default;`
- L29 _public prototype_ `bool IsValid() const;` — Return whether the facade is defined on the collection.
- L32 _public prototype_ `int32 GetNumSelections() const;` — Return the number of selections in the collection.
- L35 _public prototype_ `TArray<FName> GetNames() const;` — Return an array of all the selections' name in the collection.
- L38 _public prototype_ `bool HasSelection(const FName& Name) const;` — Return whether a selection with the given name currently exists in the collection.
- L41 _public prototype_ `FName GetSelectionGroup(const FName& Name) const;` — Return the selection group dependency. The selection must exist to call this function.
- L44 _public prototype_ `const TSet<int32>& GetSelectionSet(const FName& Name) const;` — Get the selection set for the given selection name. The selection must exist to call this function.
- L47 _public prototype_ `const TSet<int32>* FindSelectionSet(const FName& Name) const;` — Find a selection with the given name, or nullptr if no such selection exists.
- L52 _public prototype_ `bool HasSelectionSecondarySet(const FName& Name) const;` — `UE_DEPRECATED(5.6, "Secondary selection sets are no longer supported.")` — Return whether a selection with the given name currently exists in the collection and has a secondary set associated with it.
- L56 _public prototype_ `FName GetSelectionSecondaryGroup(const FName& Name) const;` — `UE_DEPRECATED(5.6, "Secondary selection sets are no longer supported.")` — Return the secondary selection set group dependency. The selection must exist and have a secondary set to call this function.
- L60 _public prototype_ `const TSet<int32>& GetSelectionSecondarySet(const FName& Name) const;` — `UE_DEPRECATED(5.6, "Secondary selection sets are no longer supported.")` — Get the secondary selection set for the given selection name. The selection must exist and have a secondary set to call this function.
- L64 _public prototype_ `const TSet<int32>* FindSelectionSecondarySet(const FName& Name) const;` — `UE_DEPRECATED(5.6, "Secondary selection sets are no longer supported.")` — Find the secondary selection set for the given selection name. Returns nullptr if no such selection exists or if it does not have an associated secondary set.
- L67 _protected member_ `TSharedRef<FManagedArrayCollection> ManagedArrayCollection;`

#### class `UE::Chaos::ClothAsset::FCollectionClothSelectionFacade`  
`class FCollectionClothSelectionFacade final : public FCollectionClothSelectionConstFacade`  
_L74-157_
- inherits: `FCollectionClothSelectionConstFacade`
- desc: Cloth Asset collection Selection facade class. Each Selection consists of a set of integer indices, a name, and a string representing the type of element being indexed. Non-const access (read/write) version.
- L77 _public prototype_ `explicit FCollectionClothSelectionFacade(const TSharedRef<FManagedArrayCollection>& ManagedArrayCollection);`
- L80 _public prototype_ `explicit FCollectionClothSelectionFacade(const TSharedRef<const FManagedArrayCollection>& ManagedArrayCollection);` — `UE_DEPRECATED(5.6, "Use the constructor that takes a non const ManagedArrayCollection instead.")`
- L82 _public prototype_ `FCollectionClothSelectionFacade() = delete;`
- L83 _public prototype_ `FCollectionClothSelectionFacade(const FCollectionClothSelectionFacade&) = delete;`
- L84 _public prototype_ `FCollectionClothSelectionFacade& operator=(const FCollectionClothSelectionFacade&) = delete;`
- L85 _public prototype_ `FCollectionClothSelectionFacade(FCollectionClothSelectionFacade&&) = default;`
- L86 _public prototype_ `FCollectionClothSelectionFacade& operator=(FCollectionClothSelectionFacade&&) = default;`
- L87 _public prototype_ `virtual ~FCollectionClothSelectionFacade() override = default;`
- L90 _public prototype_ `void DefineSchema();` — Add the Selection attributes to the underlying collection.
- L93 _public prototype_ `TSet<int32>& GetSelectionSet(const FName& Name);` — Get the selection set for the given selection name. The selection must exist to call this function.
- L96 _public prototype_ `TSet<int32>* FindSelectionSet(const FName& Name);` — Find a selection with the given name, or nullptr if no such selection exists.
- L99 _public prototype_ `void RemoveSelectionSet(const FName& Name);` — Remove the selection with the given name if it exists.
- L103 _public prototype_ `TSet<int32>& GetSelectionSecondarySet(const FName& Name);` — `UE_DEPRECATED(5.6, "Secondary selection sets are no longer supported.")` — Get the secondary selection set for the given selection name. The selection must exist and have a secondary set to call this function.
- L107 _public prototype_ `TSet<int32>* FindSelectionSecondarySet(const FName& Name);` — `UE_DEPRECATED(5.6, "Secondary selection sets are no longer supported.")` — Find the secondary selection set for the given selection name. Returns nullptr if no such selection exists or if it does not have an associated secondary set.
- L111 _public prototype_ `void RemoveSelectionSecondarySet(const FName& Name);` — `UE_DEPRECATED(5.6, "Secondary selection sets are no longer supported.")` — Remove the secondary selection set from the selection with the given name if it exists.
- L121 _public function_ `void Append(const FCollectionClothSelectionConstFacade& Other, bool bOverwriteExistingIfMismatched)` — Append all sets from an existing collection to this collection. Matching sets (i.e., same name and type) will be unioned. Mismatching sets (same name, different type) will be handled according to bOverwriteExistingIfMismatched @param bOverwriteExistingIfMismatched: If true, overwrite existing mismatched sets. If false, keep the existing set.
- L134 _public prototype_ `void AppendWithOffsets(const FCollectionClothSelectionConstFacade& Other, bool bOverwriteExistingIfMismatched, const TMap<FName, int32>& GroupOffsets);` — Append all sets from an existing collection to this collection. Apply an offset to Other's data if its GroupName is in the GroupOffsets table. Matching sets (i.e., same name and type) will be unioned. Mismatching sets (same name, different type) will be handled according to bOverwriteExistingIfMismatched @param bOverwriteExistingIfMismatched: If true, overwrite existing mismatched sets. If false, keep the existing set.
- L141 _public prototype_ `TSet<int32>& FindOrAddSelectionSet(const FName& Name, const FName& GroupName);` — Find, or add if it doesn't already exist, a selection for the specified group with the given name. If the group doesn't already exists, this function will create it. If the selection already exists, but depends on a different group, the old selection will be deleted and a new one recreated with the new group dependency.
- L150 _public prototype_ `TSet<int32>& FindOrAddSelectionSecondarySet(const FName& Name, const FName& GroupName);` — `UE_DEPRECATED(5.6, "Secondary selection sets are no longer supported.")` — Find, or add if it doesn't already exist, a secondary selection set for the specified group with the given name. NOTE: A selection with the given name must already exist. This function just adds a secondary set to the existing selection. If the group doesn't already exists, this function will create it. If the secondary selection set already exists, but depends on a different group, the old secondary selection set will be deleted and a new one recreated with the new group dependency.
- L155 _private prototype_ `TSet<int32>& FindOrAddSelectionSetInternal(const FName& Name, const FName& GroupName, const FName& SelectionGroupName);` — Helper for FindOrAddSelectionSet and FindOrAddSelectionSecondarySet

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Chaos` (scope `UE`)
- L10 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAsset/Public/ChaosClothAsset/CollectionClothSimAccessoryMeshFacade.h` (Public)


#### class `UE::Chaos::ClothAsset::FCollectionClothSimAccessoryMeshConstFacade`  
`class FCollectionClothSimAccessoryMeshConstFacade`  
_L18-59_
- desc: Cloth Asset collection sim accessory mesh facade class to access cloth sim accessory mesh data. Constructed from FCollectionClothConstFacade. Const access (read only) version.
- L21 _public prototype_ `FCollectionClothSimAccessoryMeshConstFacade() = delete;`
- L23 _public prototype_ `FCollectionClothSimAccessoryMeshConstFacade(const FCollectionClothSimAccessoryMeshConstFacade&) = delete;`
- L24 _public prototype_ `FCollectionClothSimAccessoryMeshConstFacade& operator=(const FCollectionClothSimAccessoryMeshConstFacade&) = delete;`
- L26 _public prototype_ `FCollectionClothSimAccessoryMeshConstFacade(FCollectionClothSimAccessoryMeshConstFacade&&) = default;`
- L27 _public prototype_ `FCollectionClothSimAccessoryMeshConstFacade& operator=(FCollectionClothSimAccessoryMeshConstFacade&&) = default;`
- L29 _public prototype_ `virtual ~FCollectionClothSimAccessoryMeshConstFacade() = default;`
- L33 _public prototype_ `FName GetSimAccessoryMeshName() const;` — Return the name for this accessory mesh
- L35 _public prototype_ `FName GetSimAccessoryMeshPosition3DAttribute() const;` — Return the names of dynamic attributes associated with this accessory mesh
- L36 _public prototype_ `FName GetSimAccessoryMeshNormalAttribute() const;`
- L37 _public prototype_ `FName GetSimAccessoryMeshBoneIndicesAttribute() const;`
- L38 _public prototype_ `FName GetSimAccessoryMeshBoneWeightsAttribute() const;`
- L41 _public prototype_ `TConstArrayView<FVector3f> GetSimAccessoryMeshPosition3D() const;`
- L42 _public prototype_ `TConstArrayView<FVector3f> GetSimAccessoryMeshNormal() const;`
- L43 _public prototype_ `TConstArrayView<TArray<int32>> GetSimAccessoryMeshBoneIndices() const;`
- L44 _public prototype_ `TConstArrayView<TArray<float>> GetSimAccessoryMeshBoneWeights() const;`
- L47 _public function_ `int32 GetSimAccessoryMeshIndex() const` — Return the accessory mesh index this facade has been created with.
- L52 _protected prototype_ `FCollectionClothSimAccessoryMeshConstFacade(const TSharedRef<const class FConstClothCollection>& InClothCollection, int32 InMeshIndex);`
- L54 _protected function_ `static constexpr int32 GetBaseElementIndex()`
- L55 _protected function_ `int32 GetElementIndex() const`
- L58 _protected member_ `int32 MeshIndex;`

#### class `UE::Chaos::ClothAsset::FCollectionClothSimAccessoryMeshFacade`  
`class FCollectionClothSimAccessoryMeshFacade final : public FCollectionClothSimAccessoryMeshConstFacade`  
_L66-109_
- inherits: `FCollectionClothSimAccessoryMeshConstFacade`
- desc: Cloth Asset collection sim accessory mesh facade class to access cloth sim accessory mesh data. Constructed from FCollectionClothFacade. Non-const access (read/write) version.
- L69 _public prototype_ `FCollectionClothSimAccessoryMeshFacade() = delete;`
- L71 _public prototype_ `FCollectionClothSimAccessoryMeshFacade(const FCollectionClothSimAccessoryMeshFacade&) = delete;`
- L72 _public prototype_ `FCollectionClothSimAccessoryMeshFacade& operator=(const FCollectionClothSimAccessoryMeshFacade&) = delete;`
- L74 _public prototype_ `FCollectionClothSimAccessoryMeshFacade(FCollectionClothSimAccessoryMeshFacade&&) = default;`
- L75 _public prototype_ `FCollectionClothSimAccessoryMeshFacade& operator=(FCollectionClothSimAccessoryMeshFacade&&) = default;`
- L77 _public prototype_ `virtual ~FCollectionClothSimAccessoryMeshFacade() override = default;`
- L80 _public prototype_ `void Reset();` — Remove all attributes from this accessory mesh.
- L83 _public function_ `void SetDefaults()` — Set any default values for an accessory mesh.
- L86 _public prototype_ `void Initialize(const FCollectionClothSimAccessoryMeshConstFacade& Other);` — Initialize from another accessory mesh. Assumes all indices match between source and target. Does not try to preserve attribute names, just values.
- L89 _public prototype_ `void Initialize(const FName& Name, const TConstArrayView<FVector3f>& Positions, const TConstArrayView<FVector3f>& Normals, const TConstArrayView<TArray<int32>>& BoneIndices, const TConstArrayView<TArray<float>>& BoneWeights);` — Initialize
- L93 _public prototype_ `void SetSimAccessoryMeshName(const FName& MeshName);` — Set the name for this accessory mesh.
- L96 _public prototype_ `TArrayView<FVector3f> GetSimAccessoryMeshPosition3D();`
- L97 _public prototype_ `TArrayView<FVector3f> GetSimAccessoryMeshNormal();`
- L98 _public prototype_ `TArrayView<TArray<int32>> GetSimAccessoryMeshBoneIndices();`
- L99 _public prototype_ `TArrayView<TArray<float>> GetSimAccessoryMeshBoneWeights();`
- L103 _private prototype_ `FCollectionClothSimAccessoryMeshFacade(const TSharedRef<class FClothCollection>& InClothCollection, int32 InMorphTargetIndex);`
- L105 _private prototype_ `void ClearDynamicAttributes();`
- L106 _private prototype_ `void GenerateDynamicAttributesIfNecessary();`
- L108 _private prototype_ `TSharedRef<class FClothCollection> GetClothCollection();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSCLOTHASSET_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Chaos` (scope `UE`)
- L11 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAsset/Public/ChaosClothAsset/CollectionClothSimMorphTargetFacade.h` (Public)


#### class `UE::Chaos::ClothAsset::FCollectionClothSimMorphTargetConstFacade`  
`class FCollectionClothSimMorphTargetConstFacade`  
_L18-58_
- desc: Cloth Asset collection sim morph target facade class to access cloth sim morph target data. Constructed from FCollectionClothConstFacade. Const access (read only) version.
- L21 _public prototype_ `FCollectionClothSimMorphTargetConstFacade() = delete;`
- L23 _public prototype_ `FCollectionClothSimMorphTargetConstFacade(const FCollectionClothSimMorphTargetConstFacade&) = delete;`
- L24 _public prototype_ `FCollectionClothSimMorphTargetConstFacade& operator=(const FCollectionClothSimMorphTargetConstFacade&) = delete;`
- L26 _public prototype_ `FCollectionClothSimMorphTargetConstFacade(FCollectionClothSimMorphTargetConstFacade&&) = default;`
- L27 _public prototype_ `FCollectionClothSimMorphTargetConstFacade& operator=(FCollectionClothSimMorphTargetConstFacade&&) = default;`
- L29 _public prototype_ `virtual ~FCollectionClothSimMorphTargetConstFacade() = default;`
- L32 _public prototype_ `const FString& GetSimMorphTargetName() const;` — Return the name for this morph target
- L36 _public prototype_ `int32 GetNumSimMorphTargetVertices() const;` — Return the total number of vertices for this morph target.
- L38 _public prototype_ `int32 GetSimMorphTargetVerticesOffset() const;` — Return the morph target vertices offset for this morph target in the morph target vertices for the collection.
- L39 _public prototype_ `TConstArrayView<FVector3f> GetSimMorphTargetPositionDelta() const;`
- L40 _public prototype_ `TConstArrayView<FVector3f> GetSimMorphTargetTangentZDelta() const;`
- L41 _public prototype_ `TConstArrayView<int32> GetSimMorphTargetSimVertex3DIndex() const;`
- L43 _public prototype_ `bool IsEmpty() const;`
- L46 _public function_ `int32 GetSimMorphTargetIndex() const` — Return the Morph Target index this facade has been created with.
- L51 _protected prototype_ `FCollectionClothSimMorphTargetConstFacade(const TSharedRef<const class FConstClothCollection>& InClothCollection, int32 InPatternIndex);`
- L53 _protected function_ `static constexpr int32 GetBaseElementIndex()`
- L54 _protected function_ `int32 GetElementIndex() const`
- L57 _protected member_ `int32 MorphTargetIndex;`

#### class `UE::Chaos::ClothAsset::FCollectionClothSimMorphTargetFacade`  
`class FCollectionClothSimMorphTargetFacade final : public FCollectionClothSimMorphTargetConstFacade`  
_L65-108_
- inherits: `FCollectionClothSimMorphTargetConstFacade`
- desc: Cloth Asset collection sim morph target facade class to access cloth sim morph target data. Constructed from FCollectionClothFacade. Non-const access (read/write) version.
- L68 _public prototype_ `FCollectionClothSimMorphTargetFacade() = delete;`
- L70 _public prototype_ `FCollectionClothSimMorphTargetFacade(const FCollectionClothSimMorphTargetFacade&) = delete;`
- L71 _public prototype_ `FCollectionClothSimMorphTargetFacade& operator=(const FCollectionClothSimMorphTargetFacade&) = delete;`
- L73 _public prototype_ `FCollectionClothSimMorphTargetFacade(FCollectionClothSimMorphTargetFacade&&) = default;`
- L74 _public prototype_ `FCollectionClothSimMorphTargetFacade& operator=(FCollectionClothSimMorphTargetFacade&&) = default;`
- L76 _public prototype_ `virtual ~FCollectionClothSimMorphTargetFacade() override = default;`
- L79 _public prototype_ `void Reset();` — Remove all geometry from this morph target.
- L82 _public prototype_ `void Initialize(const FCollectionClothSimMorphTargetConstFacade& Other, int32 SimVertex3DOffset);` — Initialize from another morph target. Assumes all indices match between source and target.
- L85 _public prototype_ `void Initialize(const FString& Name, const TConstArrayView<FVector3f>& PositionDeltas, const TConstArrayView<FVector3f>& TangentZDeltas, const TConstArrayView<int32>& SimVertex3DIndices);` — Initialize
- L88 _public prototype_ `void SetSimMorphTargetName(const FString& MorphTargetName);` — Set the name for this morph target.
- L92 _public prototype_ `void SetNumSimMorphTargetVertices(int32 NumMorphTargetVertices);` — Grow or shrink the space reserved for morph target vertices for this morph target within the cloth collection and return its start index.
- L93 _public prototype_ `void RemoveSimMorphTargetVertices(const TArray<int32>& SortedDeletionList);`
- L94 _public prototype_ `TArrayView<FVector3f> GetSimMorphTargetPositionDelta();`
- L95 _public prototype_ `TArrayView<FVector3f> GetSimMorphTargetTangentZDelta();`
- L96 _public prototype_ `TArrayView<int32> GetSimMorphTargetSimVertex3DIndex();`
- L99 _public prototype_ `void Compact();` — Remove all morph target vertices with invalid indices.
- L103 _private prototype_ `FCollectionClothSimMorphTargetFacade(const TSharedRef<class FClothCollection>& InClothCollection, int32 InMorphTargetIndex);`
- L105 _private prototype_ `void SetDefaults();`
- L107 _private prototype_ `TSharedRef<class FClothCollection> GetClothCollection();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSCLOTHASSET_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Chaos` (scope `UE`)
- L11 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAsset/Public/ChaosClothAsset/CollectionClothSimPatternFacade.h` (Public)


#### struct `UE::Chaos::ClothAsset::TIsIndexType`  
`template<typename T> struct TIsIndexType`  
_L12-12_
- desc: Integral and vector types valid as index type in initializations.
- L12 _public member_ `template<typename T> struct TIsIndexType { static constexpr bool Value = false; };` — Integral and vector types valid as index type in initializations.

#### struct `UE::Chaos::ClothAsset::TIsIndexType`  
`template<typename T> struct TIsIndexType`  
_L13-13_
- desc: Integral and vector types valid as index type in initializations.
- L12 _public member_ `template<typename T> struct TIsIndexType { static constexpr bool Value = false; };` — Integral and vector types valid as index type in initializations.

#### struct `UE::Chaos::ClothAsset::TIsIndexType`  
`template<typename T> struct TIsIndexType`  
_L14-14_
- desc: Integral and vector types valid as index type in initializations.
- L12 _public member_ `template<typename T> struct TIsIndexType { static constexpr bool Value = false; };` — Integral and vector types valid as index type in initializations.

#### struct `UE::Chaos::ClothAsset::TIsIndexType`  
`template<typename T> struct TIsIndexType`  
_L15-15_
- desc: Integral and vector types valid as index type in initializations.
- L12 _public member_ `template<typename T> struct TIsIndexType { static constexpr bool Value = false; };` — Integral and vector types valid as index type in initializations.

#### class `UE::Chaos::ClothAsset::FCollectionClothSimPatternConstFacade`  
`class FCollectionClothSimPatternConstFacade`  
_L22-72_
- desc: Cloth Asset collection sim pattern facade class to access cloth sim pattern data. Constructed from FCollectionClothConstFacade. Const access (read only) version.
- L25 _public prototype_ `FCollectionClothSimPatternConstFacade() = delete;`
- L27 _public prototype_ `FCollectionClothSimPatternConstFacade(const FCollectionClothSimPatternConstFacade&) = delete;`
- L28 _public prototype_ `FCollectionClothSimPatternConstFacade& operator=(const FCollectionClothSimPatternConstFacade&) = delete;`
- L30 _public prototype_ `FCollectionClothSimPatternConstFacade(FCollectionClothSimPatternConstFacade&&) = default;`
- L31 _public prototype_ `FCollectionClothSimPatternConstFacade& operator=(FCollectionClothSimPatternConstFacade&&) = default;`
- L33 _public prototype_ `virtual ~FCollectionClothSimPatternConstFacade() = default;`
- L38 _public prototype_ `int32 GetNumSimVertices2D() const;` — Return the total number of simulation vertices for this pattern.
- L40 _public prototype_ `int32 GetSimVertices2DOffset() const;` — Return the simulation vertices offset for this pattern in the simulation vertices for the collection.
- L41 _public prototype_ `TConstArrayView<FVector2f> GetSimPosition2D() const;`
- L42 _public prototype_ `TConstArrayView<int32> GetSimVertex3DLookup() const;`
- L43 _public prototype_ `TConstArrayView<int32> GetSimImportVertexID() const;`
- L47 _public prototype_ `int32 GetNumSimFaces() const;` — Note: SimIndices points to the collection arrays, not the pattern arrays
- L49 _public prototype_ `int32 GetSimFacesOffset() const;` — Return the simulation faces offset for this pattern in the simulation faces.
- L50 _public prototype_ `TConstArrayView<FIntVector3> GetSimIndices2D() const;`
- L51 _public prototype_ `TConstArrayView<FIntVector3> GetSimIndices3D() const;`
- L54 _public prototype_ `bool IsEmpty() const;` — Whether or not this pattern is empty.
- L57 _public function_ `int32 GetPatternIndex() const` — Return the Pattern index this facade has been created with.
- L60 _public prototype_ `int32 GetFabricIndex() const;` — Return the Pattern index this facade has been created with.
- L65 _protected prototype_ `FCollectionClothSimPatternConstFacade(const TSharedRef<const class FConstClothCollection>& InClothCollection, int32 InPatternIndex);`
- L67 _protected function_ `static constexpr int32 GetBaseElementIndex()`
- L68 _protected function_ `int32 GetElementIndex() const`
- L71 _protected member_ `int32 PatternIndex;`

#### class `UE::Chaos::ClothAsset::FCollectionClothSimPatternFacade`  
`class FCollectionClothSimPatternFacade final : public FCollectionClothSimPatternConstFacade`  
_L79-136_
- inherits: `FCollectionClothSimPatternConstFacade`
- desc: Cloth Asset collection sim pattern facade class to access cloth sim pattern data. Constructed from FCollectionClothFacade. Non-const access (read/write) version.
- L82 _public prototype_ `FCollectionClothSimPatternFacade() = delete;`
- L84 _public prototype_ `FCollectionClothSimPatternFacade(const FCollectionClothSimPatternFacade&) = delete;`
- L85 _public prototype_ `FCollectionClothSimPatternFacade& operator=(const FCollectionClothSimPatternFacade&) = delete;`
- L87 _public prototype_ `FCollectionClothSimPatternFacade(FCollectionClothSimPatternFacade&&) = default;`
- L88 _public prototype_ `FCollectionClothSimPatternFacade& operator=(FCollectionClothSimPatternFacade&&) = default;`
- L90 _public prototype_ `virtual ~FCollectionClothSimPatternFacade() override = default;`
- L93 _public prototype_ `void Reset();` — Remove all geometry from this cloth pattern.
- L97 _public prototype_ `template<typename IndexType UE_REQUIRES(TIsIndexType<IndexType>::Value)> void Initialize(const TArray<FVector2f>& Positions2D, const TArray<FVector3f>& Positions3D, const TArray<IndexType>& Indices, const int32 FabricIndex = INDEX_NONE, const TArray<FVector3f>& Normals = TArray<FVector3f>());` — Initialize the cloth pattern using the specified 3D and 2D positions, and topology. If Normals are not supplied, they will be calculated from the face normals.
- L100 _public prototype_ `void Initialize(const FCollectionClothSimPatternConstFacade& Other, const int32 SimVertex3DOffset, const int32 FabricsOffset = 0);` — Initialize this pattern using another pattern collection.
- L104 _public prototype_ `TArrayView<FVector2f> GetSimPosition2D();` — Note: Use the FCollectionClothConstFacade accessors instead of these for the array indices to match the SimIndices2D values
- L105 _public prototype_ `TArrayView<int32> GetSimImportVertexID();`
- L108 _public prototype_ `void RemoveSimVertices2D(int32 NumSimVertices);` — This will remove the 2D vertices, but the associated seams and 3D vertices will still exist, and point to INDEX_NONE
- L109 _public function_ `void RemoveAllSimVertices2D()`
- L110 _public prototype_ `void RemoveSimVertices2D(const TArray<int32>& SortedDeletionList);`
- L115 _public prototype_ `void SetNumSimFaces(int32 NumSimFaces);` — Grow or shrink the space reserved for simulation faces for this pattern within the cloth collection and return its start index.
- L116 _public prototype_ `TArrayView<FIntVector3> GetSimIndices2D();`
- L117 _public prototype_ `TArrayView<FIntVector3> GetSimIndices3D();`
- L118 _public prototype_ `void RemoveSimFaces(const TArray<int32>& SortedDeletionList);`
- L121 _public prototype_ `void SetFabricIndex(const int32 InFabricIndex);` — Set the fabric index used by this pattern
- L125 _private prototype_ `FCollectionClothSimPatternFacade(const TSharedRef<class FClothCollection>& InClothCollection, int32 InPatternIndex);`
- L127 _private prototype_ `void SetDefaults();`
- L130 _private prototype_ `FIntVector2 AppendSimVertices(int32 NumSimVertices);` — Append this many 2D and 3D SimVertices which correspond to each other. Returns {2D start index (local pattern index), 3D start index}.
- L132 _private prototype_ `void SetNumSimVertices2D(int32 NumSimVertices);`
- L133 _private prototype_ `TArrayView<int32> GetSimVertex3DLookup();`
- L135 _private prototype_ `TSharedRef<class FClothCollection> GetClothCollection();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSCLOTHASSET_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Chaos` (scope `UE`)
- L9 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAsset/Public/ChaosClothAsset/IsUserAttributeType.h` (Public)


#### struct `UE::Chaos::ClothAsset::TIsUserAttributeType`  
`template<typename T> struct TIsUserAttributeType`  
_L10-10_
- desc: User defined attribute types.
- L10 _public member_ `template<typename T> struct TIsUserAttributeType { static constexpr bool Value = false; };` — User defined attribute types.
- L14 _public member_ `template<> struct TIsUserAttributeType<bool> { static constexpr bool Value = true; };`
- L15 _public member_ `template<> struct TIsUserAttributeType<int32> { static constexpr bool Value = true; };`

#### struct `UE::Chaos::ClothAsset::TIsUserAttributeType`  
`template<typename T> struct TIsUserAttributeType`  
_L11-11_
- desc: User defined attribute types.
- L10 _public member_ `template<typename T> struct TIsUserAttributeType { static constexpr bool Value = false; };` — User defined attribute types.
- L14 _public member_ `template<> struct TIsUserAttributeType<bool> { static constexpr bool Value = true; };`
- L15 _public member_ `template<> struct TIsUserAttributeType<int32> { static constexpr bool Value = true; };`

#### struct `UE::Chaos::ClothAsset::TIsUserAttributeType`  
`template<typename T> struct TIsUserAttributeType`  
_L12-12_
- desc: User defined attribute types.
- L10 _public member_ `template<typename T> struct TIsUserAttributeType { static constexpr bool Value = false; };` — User defined attribute types.
- L14 _public member_ `template<> struct TIsUserAttributeType<bool> { static constexpr bool Value = true; };`
- L15 _public member_ `template<> struct TIsUserAttributeType<int32> { static constexpr bool Value = true; };`

#### struct `UE::Chaos::ClothAsset::TIsUserAttributeType`  
`template<typename T> struct TIsUserAttributeType`  
_L13-13_
- desc: User defined attribute types.
- L10 _public member_ `template<typename T> struct TIsUserAttributeType { static constexpr bool Value = false; };` — User defined attribute types.
- L14 _public member_ `template<> struct TIsUserAttributeType<bool> { static constexpr bool Value = true; };`
- L15 _public member_ `template<> struct TIsUserAttributeType<int32> { static constexpr bool Value = true; };`

#### struct `UE::Chaos::ClothAsset::TIsUserAttributeType`  
`template<> struct TIsUserAttributeType<bool>`  
_L14-14_
- L10 _public member_ `template<typename T> struct TIsUserAttributeType { static constexpr bool Value = false; };` — User defined attribute types.
- L14 _public member_ `template<> struct TIsUserAttributeType<bool> { static constexpr bool Value = true; };`
- L15 _public member_ `template<> struct TIsUserAttributeType<int32> { static constexpr bool Value = true; };`

#### struct `UE::Chaos::ClothAsset::TIsUserAttributeType`  
`template<> struct TIsUserAttributeType<int32>`  
_L15-15_
- L10 _public member_ `template<typename T> struct TIsUserAttributeType { static constexpr bool Value = false; };` — User defined attribute types.
- L14 _public member_ `template<> struct TIsUserAttributeType<bool> { static constexpr bool Value = true; };`
- L15 _public member_ `template<> struct TIsUserAttributeType<int32> { static constexpr bool Value = true; };`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Chaos` (scope `UE`)
- L7 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
