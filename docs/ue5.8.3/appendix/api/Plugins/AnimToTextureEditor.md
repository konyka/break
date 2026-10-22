# Plugins / AnimToTextureEditor

- module root: `Plugins/Experimental/AnimToTexture/Source/AnimToTextureEditor`
- headers: 6; symbols: 106
- symbol kinds: class=5, delegate=1, function=7, member=27, namespace=3, prototype=54, struct=5, typedef=4
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AnimToTexture, AssetTools, ContentBrowser, CoreUObject, Engine, MeshDescription, RawMesh, SkeletalMeshDescription, Slate, SlateCore, StaticMeshDescription, ToolMenus, UnrealEd
- PublicDependencyModuleNames: AssetDefinition, Core, MaterialEditor, MessageLog

### `Plugins/Experimental/AnimToTexture/Source/AnimToTextureEditor/Public/AnimToTextureBPLibrary.h` (Public)


#### class `UAnimToTextureBPLibrary`  
`class UAnimToTextureBPLibrary : public UBlueprintFunctionLibrary`  
_L21-109_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Converts a series of animation frames into a Vertex Animation Texture (VAT) The texture can store Vertex positions and normals or Bone positions and rotations.
- L31 _private prototype_ `static UPARAM(DisplayName="bSuccess") bool AnimationToTexture(UAnimToTextureDataAsset* Dat` — `UFUNCTION(BlueprintCallable, meta = (Category = "AnimToTexture"))` — Bakes Animation Data into Textures.
- L37 _private prototype_ `static UStaticMesh* ConvertSkeletalMeshToStaticMesh(USkeletalMesh* SkeletalMesh, const FString PackageName, const int32 LODIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = "AnimToTexture")` — Utility for converting SkeletalMesh into a StaticMesh
- L43 _private prototype_ `static UPARAM(DisplayName = "bSuccess") bool SetLightMapIndex(UStaticMesh* StaticMesh, const int32 LODIndex, const int32 LightmapIndex=1, bool bGenerateLightmapUV` — `UFUNCTION(BlueprintCallable, Category = "AnimToTexture")` — Utility for setting a StaticMesh LightMapIndex.
- L49 _private prototype_ `static void UpdateMaterialInstanceFromDataAsset(const UAnimToTextureDataAsset* DataAsset, class UMaterialInstanceConstant* MaterialInstance, const EMaterialParameterAssociation MaterialParameterAssociation = EMaterialParameterAssociation::GlobalParameter);` — `UFUNCTION(BlueprintCallable, meta = (Category = "AnimToTexture"))` — Updates a material's parameters to match those of an AnimToTexture DataAsset
- L58 _private prototype_ `static bool CheckDataAsset(const UAnimToTextureDataAsset* DataAsset, int32& OutSocketIndex, TArray<FAnimToTextureAnimSequenceInfo>& OutAnimSequences);` — Runs some validations for the assets in DataAsset Returns false if there is any problems with the data, warnings will be printed in Log
- L62 _private prototype_ `static int32 GetAnimationFrameRange(const FAnimToTextureAnimSequenceInfo& Animation, int32& OutStartFrame, int32& OutEndFrame);` — Returns Start, EndFrame and NumFrames in Animation
- L67 _private prototype_ `static void GetVertexDeltasAndNormals(const USkeletalMeshComponent* SkeletalMeshComponent, const int32 LODIndex, const AnimToTexture_Private::FSourceMeshToDriverMesh& SourceMeshToDriverMesh, const FTransform RootTransform, TArray<FVector3f>& OutVertexDeltas, TArray<FVector3f>& OutVertexNormals);` — Get Vertex and Normals from Current Pose The VertexDelta is returned from the RefPose
- L73 _private prototype_ `static int32 GetRefBonePositionsAndRotations(const USkeletalMesh* SkeletalMesh, TArray<FVector3f>& OutBoneRefPositions, TArray<FVector4f>& OutBoneRefRotations);` — Gets RefPose Bone Position and Rotations.
- L78 _private prototype_ `static int32 GetBonePositionsAndRotations(const USkeletalMeshComponent* SkeletalMeshComponent, const TArray<FVector3f>& BoneRefPositions, TArray<FVector3f>& BonePositions, TArray<FVector4f>& BoneRotations);` — Gets Bone Position and Rotations for Current Pose. The BonePosition is returned relative to the RefPose
- L82 _private prototype_ `static void NormalizeVertexData( const TArray<FVector3f>& Deltas, const TArray<FVector3f>& Normals, FVector3f& OutMinBBox, FVector3f& OutSizeBBox, TArray<FVector3f>& OutNormalizedDeltas, TArray<FVector3f>& OutNormalizedNormals);` — Normalizes Deltas and Normals between [0-1] with Bounding Box
- L88 _private prototype_ `static void NormalizeBoneData( const TArray<FVector3f>& Positions, const TArray<FVector4f>& Rotations, FVector3f& OutMinBBox, FVector3f& OutSizeBBox, TArray<FVector3f>& OutNormalizedPositions, TArray<FVector4f>& OutNormalizedRotations);` — Normalizes Positions and Rotations between [0-1] with Bounding Box
- L95 _private prototype_ `static bool FindBestResolution(const int32 NumFrames, const int32 NumElements, int32& OutHeight, int32& OutWidth, int32& OutRowsPerFrame, const int32 MaxHeight = 4096, const int32 MaxWidth = 4096, bool bEnforcePowerOfTwo = false);` — Returns best resolution for the given data. Returns false if data doesnt fit in the the max range
- L100 _private prototype_ `static void SetFullPrecisionUVs(UStaticMesh* StaticMesh, const int32 LODIndex, bool bFullPrecision=true);` — Sets Static Mesh FullPrecisionUVs Property
- L103 _private prototype_ `static void SetBoundsExtensions(UStaticMesh* StaticMesh, const FVector& MinBBox, const FVector& SizeBBox);` — Sets Static Mesh Bound Extensions
- L106 _private prototype_ `static bool CreateUVChannel(UStaticMesh* StaticMesh, const int32 LODIndex, const int32 UVChannelIndex, const int32 Height, const int32 Width);` — Creates UV Coord with vertices

### `Plugins/Experimental/AnimToTexture/Source/AnimToTextureEditor/Public/AnimToTextureEditorModule.h` (Public)


#### class `FAnimToTextureEditorModule`  
`class FAnimToTextureEditorModule : public IModuleInterface`  
_L9-16_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimToTextureEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimToTextureEditor, Log, All);`

### `Plugins/Experimental/AnimToTexture/Source/AnimToTextureEditor/Public/AnimToTextureMeshMapping.h` (Public)


#### struct `AnimToTexture_Private::FSourceVertexDriverTriangleData`  
`struct FSourceVertexDriverTriangleData`  
_L11-19_
- L13 _public member_ `uint8 TangentLocalIndex;`
- L14 _public member_ `float InverseDistanceWeight;`
- L15 _public member_ `FIntVector3 Triangle;`
- L16 _public member_ `FVector3f BarycentricCoords;`
- L17 _public member_ `FMatrix44f InvMatrix;`
- L18 _public member_ `VertexSkinWeightMax SkinWeights;`

#### class `AnimToTexture_Private::FSourceVertexData`  
`class FSourceVertexData`  
_L21-34_
- L25 _public prototype_ `FSourceVertexData() = default;`
- L27 _public prototype_ `void Update(const FVector3f& SourceVertex, const TArray<FVector3f>& DriverVertices, const TArray<FIntVector3>& DriverTriangles, const TArray<VertexSkinWeightMax>& DriverSkinWeights, const int32 NumDrivers, const float Sigma=1.f);`
- L32 _public member_ `TArray<FSourceVertexDriverTriangleData> DriverTriangleData;` — DriverTriangle Data specific to this SourceVertex

#### class `AnimToTexture_Private::FSourceMeshToDriverMesh`  
`class FSourceMeshToDriverMesh`  
_L37-73_
- desc: Creates Mapping between StaticMesh (Source) and SkeletalMesh (Driver)
- L41 _public prototype_ `FSourceMeshToDriverMesh() = default;`
- L43 _public prototype_ `void Update(const UStaticMesh* StaticMesh, const int32 StaticMeshLODIndex, const USkeletalMesh* SkeletalMesh, const int32 SkeletalMeshLODIndex, const int32 NumDrivers, const float Sigma=1.f);`
- L48 _public prototype_ `int32 GetNumSourceVertices() const;` — Returns Number of Source Vertices
- L50 _public prototype_ `int32 GetSourceVertices(TArray<FVector3f>& OutVertices) const;` — Returns Source Vertices
- L52 _public prototype_ `int32 GetSourceNormals(TArray<FVector3f>& OutNormals) const;` — Returns Source Normals
- L55 _public prototype_ `void DeformVerticesAndNormals(const TArray<FVector3f>& DriverVertices, TArray<FVector3f>& OutVertices, TArray<FVector3f>& OutNormals) const;` — Deforms Source Vertices with Driver Triangles
- L59 _public prototype_ `void ProjectSkinWeights(TArray<VertexSkinWeightMax>& OutSkinWeights) const;` — Project SkinWeights
- L64 _private member_ `TArray<FVector3f> SourceVertices;` — Size of Source Mesh
- L65 _private member_ `TArray<FVector3f> SourceNormals;`
- L66 _private member_ `TArray<FSourceVertexData> SourceVerticesData;`
- L69 _private member_ `TArray<FVector3f> DriverVertices;` — Driver Data
- L70 _private member_ `TArray<FIntVector3> DriverTriangles;`
- L71 _private member_ `TArray<VertexSkinWeightMax> DriverSkinWeights;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace AnimToTexture_Private`

### `Plugins/Experimental/AnimToTexture/Source/AnimToTextureEditor/Public/AnimToTextureSkeletalMesh.h` (Public)


#### struct `AnimToTexture_Private::TVertexSkinWeight`  
`template <uint16 NumInfluences> struct TVertexSkinWeight`  
_L14-18_
- L16 _public member_ `TStaticArray<uint16, NumInfluences> MeshBoneIndices;`
- L17 _public member_ `TStaticArray<uint8, NumInfluences> BoneWeights;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace AnimToTexture_Private`
- L20 _typedef_ `using VertexSkinWeightMax = TVertexSkinWeight<MAX_TOTAL_INFLUENCES>;` (scope `AnimToTexture_Private`)
- L21 _typedef_ `using VertexSkinWeightFour = TVertexSkinWeight<4>;` (scope `AnimToTexture_Private`)
- L24 _prototype_ `int32 GetVertices(const UStaticMesh* StaticMesh, const int32 LODIndex, TArray<FVector3f>& OutPositions, TArray<FVector3f>& OutNormals);` (scope `AnimToTexture_Private`) — Returns StaticMesh Vertex Positions
- L28 _prototype_ `int32 GetVertices(const USkeletalMesh* SkeletalMesh, const int32 LODIndex, TArray<FVector3f>& OutPositions);` (scope `AnimToTexture_Private`) — Returns RefPose Vertex Positions
- L32 _prototype_ `int32 GetTriangles(const USkeletalMesh* SkeletalMesh, const int32 LODIndex, TArray<FIntVector3>& OutTriangles);` (scope `AnimToTexture_Private`) — Returns Triangles vertex indices
- L36 _prototype_ `void GetSkinnedVertices(const USkeletalMeshComponent* SkeletalMeshComponent, const int32 LODIndex, TArray<FVector3f>& OutPositions);` (scope `AnimToTexture_Private`) — Computes CPUSkinning at Pose
- L40 _prototype_ `void GetSkinWeights(const USkeletalMesh* SkeletalMesh, const int32 LODIndex, TArray<VertexSkinWeightMax>& OutSkinWeights);` (scope `AnimToTexture_Private`) — Gets Skin Weights Data from SkeletalMeshComponent
- L44 _prototype_ `void ReduceSkinWeights(const TArray<VertexSkinWeightMax>& InSkinWeights, TArray<VertexSkinWeightFour>& OutSkinWeights);` (scope `AnimToTexture_Private`) — Reduce Weights from MAX_TOTAL_INFLUENCES to 4
- L47 _prototype_ `void InterpolateVertexSkinWeights(const TArray<VertexSkinWeightMax>& VertexSkinWeights, const TArray<float>& Weights, VertexSkinWeightMax& OutVertexSkinWeights);` (scope `AnimToTexture_Private`) — Interpolates an Array of SkinWeights with an Array of Weights(InverseDistanceWeights)
- L51 _prototype_ `int32 GetNumBones(const USkeletalMesh* SkeletalMesh);` (scope `AnimToTexture_Private`) — Returns Number of RawBones (no virtual bones)
- L56 _prototype_ `void GetRefBoneTransforms(const USkeletalMesh* SkeletalMesh, TArray<FTransform>& OutTransforms);` (scope `AnimToTexture_Private`) — Returns RefPose Bone Transforms. Only the RawBones are returned (no virtual bones) The returned transforms are in ComponentSpace
- L60 _prototype_ `void GetBoneNames(const USkeletalMesh* SkeletalMesh, TArray<FName>& OutNames);` (scope `AnimToTexture_Private`) — Returns Bone Names. Only the RawBones are returned (no virtual bones)
- L63 _prototype_ `FVector3f FindClosestPointToTriangle(const FVector3f& Point, const FVector3f& PointA, const FVector3f& PointB, const FVector3f& PointC);` (scope `AnimToTexture_Private`) — Computes closest point to triangle
- L66 _prototype_ `FVector3f BarycentricCoordinates(const FVector3f& Point, const FVector3f& PointA, const FVector3f& PointB, const FVector3f& PointC);` (scope `AnimToTexture_Private`) — Computes Barycentric coordinates from point to triangle
- L69 _prototype_ `FVector3f PointAtBarycentricCoordinates(const FVector3f& PointA, const FVector3f& PointB, const FVector3f& PointC, const FVector3f& BarycentricCoords);` (scope `AnimToTexture_Private`) — Returns Point at Barycentric coordinates of the given triangle
- L72 _prototype_ `FVector3f GetTriangleNormal(const FVector3f& PointA, const FVector3f& PointB, const FVector3f& PointC);` (scope `AnimToTexture_Private`) — Computes Triangle Normal (not normalized)
- L78 _prototype_ `uint8 GetTriangleTangentLocalIndex(const FVector3f& Point, const FVector3f& PointA, const FVector3f& PointB, const FVector3f& PointC);` (scope `AnimToTexture_Private`) — Returns TangentLocalIndex for Triangle TangentLocalIndex 0: PointA - PointP TangentLocalIndex 1: PointB - PointP TangentLocalIndex 2: PointC - PointP
- L81 _prototype_ `FMatrix44f GetTriangleMatrix(const FVector3f& Point, const FVector3f& PointA, const FVector3f& PointB, const FVector3f& PointC, const uint8 TangentLocalIndex);` (scope `AnimToTexture_Private`) — Computes Triangle Matrix
- L85 _prototype_ `void InverseDistanceWeights(const FVector3f& Point, const TArray<FVector3f>& Points, TArray<float>& OutWeights, const float Sigma = 1.f);` (scope `AnimToTexture_Private`) — Returns a list of weights from Point to each of the given Points. The returned Weights are the size of Points and normalized (sum to 1.0)

### `Plugins/Experimental/AnimToTexture/Source/AnimToTextureEditor/Public/AnimToTextureUtils.h` (Public)


#### struct `AnimToTexture_Private::FVector4u16`  
`struct FVector4u16`  
_L14-20_
- L16 _public member_ `uint16 X;`
- L17 _public member_ `uint16 Y;`
- L18 _public member_ `uint16 Z;`
- L19 _public member_ `uint16 W;`

#### struct `AnimToTexture_Private::FLowPrecision`  
`struct FLowPrecision`  
_L22-29_
- L24 _public typedef_ `using ColorType = FColor;`
- L25 _public member_ `static constexpr EPixelFormat PixelFormat = EPixelFormat::PF_B8G8R8A8;`
- L26 _public member_ `static constexpr ETextureSourceFormat TextureSourceFormat = ETextureSourceFormat::TSF_BGRA8;`
- L27 _public member_ `static constexpr TextureCompressionSettings CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;`
- L28 _public member_ `static constexpr ColorType DefaultColor = FColor(0, 0, 0, 0);`

#### struct `AnimToTexture_Private::FHighPrecision`  
`struct FHighPrecision`  
_L31-38_
- L33 _public typedef_ `using ColorType = FVector4u16;`
- L34 _public member_ `static constexpr EPixelFormat PixelFormat = EPixelFormat::PF_R16G16B16A16_UNORM;`
- L35 _public member_ `static constexpr ETextureSourceFormat TextureSourceFormat = ETextureSourceFormat::TSF_RGBA16;`
- L36 _public member_ `static constexpr TextureCompressionSettings CompressionSettings = TextureCompressionSettings::TC_HDR;`
- L37 _public member_ `static constexpr ColorType DefaultColor = { 0, 0, 0, 0 };`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AnimToTexture_Private`
- L43 _prototype_ `template<class V, class TextureSettings> bool WriteVectorsToTexture(const TArray<V>& Vectors, const int32 NumFrames, const int32 RowsPerFrame, const int32 Height, const int32 Width, UTexture2D* Texture);` (scope `AnimToTexture_Private`) — Writes list of vectors into texture Note: They must be pre-normalized.
- L52 _prototype_ `template<class TextureSettings> bool WriteSkinWeightsToTexture(const TArray<VertexSkinWeightFour>& SkinWeights, const int32 NumBones, const int32 RowsPerFrame, const int32 Height, const int32 Width, UTexture2D* Texture);` (scope `AnimToTexture_Private`) — Writes list of skinweights into texture. The SkinWeights data is already in uint8 & uint16 format, no need for normalizing it.
- L59 _prototype_ `template<class TextureSettings> bool WriteToTexture(UTexture2D* Texture, const uint32 Height, const uint32 Width, const TArray<typename TextureSettings::ColorType>& Data);` (scope `AnimToTexture_Private`) — Helper utility for writing 8 or 16 bits textures
- L62 _prototype_ `template<class V , class C > void VectorToColor(const V& Vector, C& Color);` (scope `AnimToTexture_Private`)
- L65 _prototype_ `void DecomposeTransformation(const FTransform& Transform, FVector3f& OutTranslation, FVector4f& OutRotation);` (scope `AnimToTexture_Private`) — Decomposes Transform in Translation and AxisAndAngle
- L66 _prototype_ `void DecomposeTransformations(const TArray<FTransform>& Transforms, TArray<FVector3f>& OutTranslations, TArray<FVector4f>& OutRotations);` (scope `AnimToTexture_Private`)
- L74 _function_ `template<> inline void AnimToTexture_Private::VectorToColor(const FVector3f& Vector, FColor& Color)` (scope `AnimToTexture_Private`) — LowPrecision
- L88 _function_ `template<> inline void AnimToTexture_Private::VectorToColor(const FVector4f& Vector, FColor& Color)` (scope `AnimToTexture_Private`) — LowPrecision
- L103 _function_ `template<> inline void AnimToTexture_Private::VectorToColor(const FVector3f& Vector, FVector4u16& Color)` (scope `AnimToTexture_Private`) — HighPrecision
- L113 _function_ `template<> inline void AnimToTexture_Private::VectorToColor(const FVector4f& Vector, FVector4u16& Color)` (scope `AnimToTexture_Private`) — HighPrecision
- L122 _function_ `template<class V, class TextureSettings> inline bool AnimToTexture_Private::WriteVectorsToTexture(const TArray<V>& Vectors, const int32 NumFrames, const int32 RowsPerFrame, const int32 Height, const int32 Width, UTexture2D* Texture)` (scope `AnimToTexture_Private`)
- L158 _function_ `template<class TextureSettings> inline bool AnimToTexture_Private::WriteSkinWeightsToTexture(const TArray<AnimToTexture_Private::VertexSkinWeightFour>& SkinWeights, const int32 NumBones, const int32 RowsPerFrame, const int32 Height, const int32 Width, UTexture2D* Texture)` (scope `AnimToTexture_Private`)
- L205 _function_ `template<class TextureSettings> inline bool AnimToTexture_Private::WriteToTexture( UTexture2D* Texture, const uint32 Height, const uint32 Width, const TArray<typename TextureSettings::ColorType>& Pixels)` (scope `AnimToTexture_Private`)

### `Plugins/Experimental/AnimToTexture/Source/AnimToTextureEditor/Public/AssetDefinition_AnimToTexture.h` (Public)


#### class `UAssetDefinition_AnimToTexture`  
`class UAssetDefinition_AnimToTexture : public UAssetDefinitionDefault`  
_L10-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _protected prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L17 _protected prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _protected prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _protected prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
