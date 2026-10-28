# Plugins / ChaosOutfitAssetEngine

- module root: `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEngine`
- headers: 9; symbols: 208
- symbol kinds: class=5, delegate=2, enum=1, enumerator=1, externvar=22, function=23, macro=4, member=25, namespace=20, prototype=99, struct=5, variable=1
- PrivateDependencyModuleNames: Chaos, ChaosClothAsset, Core, CoreUObject, DataflowEngine, Engine, MeshResizingCore, RHI, RenderCore
- PrivateIncludePathModuleNames: DerivedDataCache
- PublicDependencyModuleNames: ChaosClothAssetEngine

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEngine/Private/ChaosOutfitAsset/OutfitAssetBuilder.h` (Private)


#### struct `UChaosOutfitAsset::FBuilder`  
`struct UChaosOutfitAsset::FBuilder`  
_L17-24_
- desc: Builder utility struct, nested struct of UChaosOutfitAsset. Converts merged FSkeletalMeshLODRenderData into FSkeletalMeshLODModel, applying platform-specific bone influence conforming. This is the reverse of BuildFromLODModel().
- L20 _public prototype_ `static void BuildLod( FSkeletalMeshLODModel& OutLODModel, const FSkeletalMeshLODRenderData& SourceLODRenderData, const ITargetPlatform* TargetPlatform);` — Convert one LOD of merged render data into an FSkeletalMeshLODModel for the specified target platform.

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEngine/Private/ChaosOutfitAsset/OutfitAssetPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosOutfitAsset, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosOutfitAsset, Log, All);`
- L9 _delegate_ `DECLARE_STATS_GROUP(TEXT("ChaosOutfitAsset"), STATGROUP_ChaosOutfitAsset, ST`

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEngine/Public/ChaosOutfitAsset/BodyUserData.h` (Public)


#### class `UChaosOutfitAssetBodyUserData`  
`class UChaosOutfitAssetBodyUserData : public UAssetUserData`  
_L12-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetUserData`
- desc: Asset user data attached to the merged body and face skeletal mesh.
- L17 _public member_ `static inline constexpr float InvalidMeasurement = 0.f;`
- L20 _public member_ `TMap<FString, float> Measurements;` — `UPROPERTY(VisibleAnywhere, Category = "Measurements")`

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEngine/Public/ChaosOutfitAsset/CollectionOutfitFacade.h` (Public)


#### class `UE::Chaos::OutfitAsset::FCollectionOutfitConstFacade`  
`class FCollectionOutfitConstFacade`  
_L27-120_
- desc: Cloth outfit collection facade. Const access (read only) version.
- L37 _public prototype_ `explicit FCollectionOutfitConstFacade(const TSharedRef<const FManagedArrayCollection>& InManagedArrayCollection);`
- L38 _public prototype_ `explicit FCollectionOutfitConstFacade(const FManagedArrayCollection& InManagedArrayCollection);`
- L40 _public prototype_ `FCollectionOutfitConstFacade() = delete;`
- L41 _public prototype_ `FCollectionOutfitConstFacade(const FCollectionOutfitConstFacade&) = delete;`
- L42 _public prototype_ `FCollectionOutfitConstFacade& operator=(const FCollectionOutfitConstFacade&) = delete;`
- L43 _public prototype_ `FCollectionOutfitConstFacade(FCollectionOutfitConstFacade&&) = default;`
- L44 _public prototype_ `FCollectionOutfitConstFacade& operator=(FCollectionOutfitConstFacade&&) = default;`
- L45 _public prototype_ `virtual ~FCollectionOutfitConstFacade();`
- L48 _public prototype_ `bool IsValid() const;` — Return whether the facade is defined on the collection.
- L51 _public prototype_ `TArray<FGuid> GetOutfitGuids() const;` — Return the sized outfits GUID, one per sized outfit which can contain different sized outfits.
- L54 _public prototype_ `bool HasValidBodySize(bool bBodyPartMustExist = false, bool bMeasurementsMustExist = false, bool bInterpolationDataMustExist = false) const;` — Return whether this outfit has at least one valid body size. Definition of valid depends on the passed arguments.
- L57 _public prototype_ `TArray<FSoftObjectPath> GetOutfitBodyPartsSkeletalMeshPaths() const;` — Return all unique body part skeletal meshes used by this outfit.
- L59 _public prototype_ `TArray<FString> GetOutfitBodyPartsSkeletalMeshes() const;` — `UE_DEPRECATED(5.7, "Use GetOutfitBodyPartsSkeletalMeshPaths instead.")`
- L62 _public prototype_ `TArray<int32> GetOutfitBodySizes(const FGuid& Guid) const;` — Return the body size available for the specified outfit GUID.
- L65 _public prototype_ `const FString& GetOutfitName(const FGuid& Guid, const int32 BodySize) const;` — Return the name of the original asset making up the specified outfit body size.
- L68 _public prototype_ `TConstArrayView<FGuid> GetOutfitPiecesGuids() const;` — Return all outfit pieces asset GUIDs.
- L71 _public prototype_ `TMap<FGuid, FString> GetOutfitPieces(const FGuid& Guid, const int32 BodySize) const;` — Return the outfit pieces making up the specified outfit body size.
- L74 _public prototype_ `int32 GetNumBodySizes() const;` — Return the number of body sizes.
- L77 _public function_ `bool HasBodySize(const FString& Name) const` — Return whether this body size already exist.
- L83 _public prototype_ `int32 FindBodySize(const FString& Name) const;` — Return the body size index for the specified name, or INDEX_NONE if it doesn't exist in this outfit.
- L86 _public prototype_ `int32 FindClosestBodySize(const TMap<FString, float>& Measurements) const;` — Return the closest size to the specified measurements, or INDEX_NONE if this outfit has no sizes or the measurements are incomplete.
- L89 _public prototype_ `int32 FindClosestBodySize(const USkeletalMesh& BodyPart) const;` — Return the closest size to the specified body, or INDEX_NONE if this outfit has no sizes or the body has no measurement data.
- L92 _public prototype_ `const FString& GetBodySizeName(const int32 BodySize) const;` — Return the specified body size name which is unique.
- L95 _public prototype_ `TConstArrayView<FSoftObjectPath> GetBodySizeBodyPartsSkeletalMeshPaths(const int32 BodySize) const;` — Return the body part skeletal meshes path name for the specified body size.
- L97 _public function_ `TConstArrayView<FString> GetBodySizeBodyPartsSkeletalMeshes(const int32 BodySize) const` — `UE_DEPRECATED(5.7, "Use GetBodySizeBodyPartsSkeletalMeshPaths instead.")`
- L103 _public prototype_ `int32 GetBodySizeBodyPartOffset(const int32 BodySize) const;` — Return the body size body part offset (to index into the global body part array). Returns INDEX_NONE if BodySize is invalid.
- L106 _public prototype_ `int32 GetBodySizeBodyPartCount(const int32 BodySize) const;` — Return the body size body part count. Returns 0 if BodySize is invalid.
- L109 _public prototype_ `FRBFInterpolationDataWrapper GetBodySizeInterpolationData(const int32 BodySize) const;` — Return  for the specified body size.
- L112 _public prototype_ `TMap<FString, float> GetBodySizeMeasurements(const int32 BodySize) const;` — Return the body measurements stored for this specified body size.
- L116 _protected function_ `const Private::FOutfitCollection* GetOutfitCollection() const`
- L118 _protected member_ `TUniquePtr<const Private::FOutfitCollection> OutfitCollection;`
- L119 _protected member_ `TSharedPtr<const FManagedArrayCollection> ManagedArrayCollection;` — Only used to keep the shared ref alive

#### struct `UE::Chaos::OutfitAsset::FCollectionOutfitConstFacade::FRBFInterpolationDataWrapper`  
`struct FRBFInterpolationDataWrapper`  
_L30-35_
- L32 _public member_ `TConstArrayView<TArray<int32>> SampleIndices;`
- L33 _public member_ `TConstArrayView<TArray<FVector3f>> SampleRestPositions;`
- L34 _public member_ `TConstArrayView<TArray<float>> InterpolationWeights;`

#### class `UE::Chaos::OutfitAsset::FCollectionOutfitFacade`  
`class FCollectionOutfitFacade final : public FCollectionOutfitConstFacade`  
_L126-207_
- inherits: `FCollectionOutfitConstFacade`
- desc: Cloth outfit collection facade. Non-const access (read/write) version.
- L129 _public prototype_ `explicit FCollectionOutfitFacade(const TSharedRef<FManagedArrayCollection>& InManagedArrayCollection);`
- L130 _public prototype_ `explicit FCollectionOutfitFacade(FManagedArrayCollection& InManagedArrayCollection);`
- L132 _public prototype_ `FCollectionOutfitFacade() = delete;`
- L133 _public prototype_ `FCollectionOutfitFacade(const FCollectionOutfitFacade&) = delete;`
- L134 _public prototype_ `FCollectionOutfitFacade& operator=(const FCollectionOutfitFacade&) = delete;`
- L135 _public prototype_ `FCollectionOutfitFacade(FCollectionOutfitFacade&&) = default;`
- L136 _public prototype_ `FCollectionOutfitFacade& operator=(FCollectionOutfitFacade&&) = default;`
- L140 _public prototype_ `void PostSerialize(const FArchive& Ar);` — Do post-serialization fixups
- L143 _public prototype_ `void DefineSchema();` — Add the Selection attributes to the underlying collection.
- L146 _public prototype_ `void Reset();` — Remove all outfit and size information from this collection.
- L152 _public prototype_ `int32 AddBodySize( const FString& Name, const TConstArrayView<FSoftObjectPath> BodyPartsSkeletalMeshes, const TMap<FString, float>& Measurements, const FRBFInterpolationDataWrapper& InterpolationData);` — Add a new body size and returns its index. Any pre-existing sizes data will be replaced.
- L158 _public prototype_ `int32 AddBodySize( const FString& Name, const TConstArrayView<FString> BodyPartsSkeletalMeshes, const TMap<FString, float>& Measurements, const FRBFInterpolationDataWrapper& InterpolationData);` — `UE_DEPRECATED(5.7, "Use version with FSoftObjectPath BodyPartsSkeletalMeshes")`
- L165 _public function_ `int32 FindOrAddBodySize(const FString& Name)` — Find or add a new body size and returns its index.
- L176 _public prototype_ `void AddOutfit( const FGuid& Guid, const int32 BodySize, const UChaosClothAssetBase& ClothAssetBase);` — Add a new sized outfit under the specified outfit GUID. Any pre-existing sizes data will be replaced.
- L187 _public prototype_ `void Append(const FCollectionOutfitConstFacade& Other, int32 SelectedBodySize = INDEX_NONE);` — Append an existing outfit facade to this collection. Any pre-existing sizes data will be replaced. @param Other The source outfit collection to get the data from. @param SelectedBodySize The body size of the source outfit to append, or INDEX_NONE to append all sizes.
- L193 _public function_ `void Append(const FManagedArrayCollection& InManagedArrayCollection)` — Append an existing outfit facade to this collection. Any pre-existing sizes data will be replaced.
- L200 _private prototype_ `void AddOutfit( const FGuid& Guid, const int32 BodySize, const FString& Name, const TMap<FGuid, FString>& Pieces);`
- L206 _private function_ `Private::FOutfitCollection* GetOutfitCollection()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSOUTFITASSETENGINE_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Chaos` (scope `UE`)
- L16 _namespace_ `namespace OutfitAsset` (scope `UE::Chaos`)
- L18 _namespace_ `namespace Private` (scope `UE::Chaos::OutfitAsset`)

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEngine/Public/ChaosOutfitAsset/Outfit.h` (Public)


#### struct `FChaosOutfitPiece`  
`struct FChaosOutfitPiece final`  
_L25-69_
- reflection: `USTRUCT()`
- L30 _public member_ `FName Name;` — `UPROPERTY()`
- L33 _public member_ `FGuid AssetGuid;` — `UPROPERTY()`
- L36 _public member_ `TObjectPtr<const UPhysicsAsset> PhysicsAsset;` — `UPROPERTY()`
- L38 _public member_ `TSharedRef<FChaosClothSimulationModel> ClothSimulationModel;`
- L40 _public member_ `TArray<TSharedRef<const FManagedArrayCollection>> Collections;`
- L42 _public prototype_ `FChaosOutfitPiece();`
- L43 _public prototype_ `~FChaosOutfitPiece();`
- L44 _public prototype_ `FChaosOutfitPiece( FName InName, FGuid InAssetGuid, const UPhysicsAsset* InPhysicsAsset, const FChaosClothSimulationModel& InClothSimulationModel, const TArray<TSharedRef<const FManagedArrayCollection>>& InCollections);`
- L51 _public prototype_ `FChaosOutfitPiece(const UChaosClothAssetBase& ClothAssetBase, int32 ModelIndex);`
- L52 _public function_ `FChaosOutfitPiece(const TArray<FChaosOutfitPiece>& Pieces, int32 ModelIndex) : FChaosOutfitPiece(Pieces[ModelIndex])`
- L54 _public prototype_ `FChaosOutfitPiece(const FChaosOutfitPiece& Other);`
- L56 _public prototype_ `FChaosOutfitPiece(FChaosOutfitPiece&& Other);`
- L58 _public prototype_ `FChaosOutfitPiece& operator=(const FChaosOutfitPiece& Other);`
- L59 _public prototype_ `FChaosOutfitPiece& operator=(FChaosOutfitPiece&& Other);`
- L61 _public prototype_ `bool Serialize(FArchive& Ar);`
- L66 _private prototype_ `void DeepCopyCollections(const TArray<TSharedRef<const FManagedArrayCollection>>& Other);`
- L68 _private prototype_ `void RemapBoneIndices(const TArray<int32>& BoneMap);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosOutfitPiece> : public TStructOpsTypeTraitsBase2<FChaosOutfitPiece>`  
_L72-78_
- inherits: `TStructOpsTypeTraitsBase2<FChaosOutfitPiece>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L75-77_

#### class `UChaosOutfit`  
`class UChaosOutfit final : public UObject`  
_L84-198_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: Outfit class to handle the assembly of an outfit asset.
- L89 _public prototype_ `UChaosOutfit(const FObjectInitializer& ObjectInitializer);`
- L90 _public prototype_ `UChaosOutfit(FVTableHelper& Helper);` — This is declared so we can use TUniquePtr<FClothSimulationModel> with just a forward declare of that class
- L93 _public prototype_ `void Append(const UChaosOutfit& Other, const FString& BodySizeNameFilter = {});`
- L95 _public prototype_ `void Add(const UChaosClothAssetBase& ClothAssetBase);`
- L96 _public prototype_ `void Add(const FChaosSizedOutfitSource& SizedOutfitSource, const FGuid& OutfitGuid = FGuid::NewGuid());`
- L98 _public prototype_ `void CopyTo( TArray<FChaosOutfitPiece>& OutPieces, FReferenceSkeleton& OutReferenceSkeleton, TUniquePtr<FSkeletalMeshRenderData>& OutSkeletalMeshRenderData, TArray<FSkeletalMaterial>& OutMaterials, FManagedArrayCollection& OutOutfitCollection) const;`
- L105 _public function_ `const TArray<FChaosOutfitPiece>& GetPieces() const`
- L110 _public function_ `TArrayView<FChaosOutfitPiece> GetPieces()`
- L115 _public function_ `const TArray<FSkeletalMaterial>& GetMaterials() const`
- L120 _public function_ `TArray<FSkeletalMaterial>& GetMaterials()`
- L125 _public function_ `const FManagedArrayCollection& GetOutfitCollection() const`
- L129 _public function_ `FManagedArrayCollection& GetOutfitCollection()`
- L135 _public prototype_ `int32 GetNumLods() const;` — Return the number of LODs (max LOD contained in any piece).
- L138 _public prototype_ `TArray<TSharedRef<const FManagedArrayCollection>> GetClothCollections(int32 LodIndex) const;` — Return the outfit pieces cloth collections for all LODs.
- L140 _public function_ `const FReferenceSkeleton& GetReferenceSkeleton() const`
- L145 _public prototype_ `bool HasBodySize(const FString& SizeName) const;`
- L148 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L155 _public prototype_ `template<typename RenderDataType UE_REQUIRES(std::is_same_v<RenderDataType, FSkeletalMeshRenderData> || std::is_same_v<RenderDataType, UChaosOutfit::FRenderData>)> static void Init( TArray<FChaosOutfitPiece>& OutPieces, FReferenceSkeleton& OutReferenceSkeleton, TUniquePtr<RenderDataType>& OutSkeletalMeshRenderData, TArray<FSkeletalMaterial>& OutMaterials, FManagedArrayCollection& OutOutfitCollection);`
- L163 _private prototype_ `template<typename InLODRenderDataType, typename OutLODRenderDataType> static void MergeLODRenderDatas( const InLODRenderDataType& LODRenderData, const TArray<FGuid>& AssetGuids, const int32 MaterialOffset, const FReferenceSkeleton& ReferenceSkeleton, const TArray<int32>& BoneMap, OutLODRenderDataType& OutLODRenderData);`
- L172 _private prototype_ `template<typename InRenderDataType, typename OutRenderDataType, typename PiecesType> static void Merge( const FReferenceSkeleton& InReferenceSkeleton, const InRenderDataType* const InRenderData, const TArray<FSkeletalMaterial>& InMaterials, const FManagedArrayCollection& InOutfitCollection, const PiecesType& Pieces, const int32 NumPieces, const FString& BodySizeNameFilter, TArray<FChaosOutfitPiece>& OutPieces, FReferenceSkeleton& OutReferenceSkeleton, OutRenderDataType* const OutRenderData, TArray<FSkeletalMaterial>& OutMaterials, FManagedArrayCollection& OutOutfitCollection);`
- L187 _private member_ `TArray<FChaosOutfitPiece> Pieces;` — `UPROPERTY()`
- L190 _private member_ `TArray<FSkeletalMaterial> Materials;` — `UPROPERTY()`
- L193 _private member_ `FManagedArrayCollection OutfitCollection;` — `UPROPERTY()`
- L195 _private member_ `FReferenceSkeleton ReferenceSkeleton;`
- L197 _private member_ `TUniquePtr<FRenderData> RenderData;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CHAOSOUTFITASSETENGINE_API`
- L76 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anondbd0d7c40103`)

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEngine/Public/ChaosOutfitAsset/OutfitAsset.h` (Public)


#### class `UChaosOutfitAsset`  
`class UChaosOutfitAsset final : public UChaosClothAssetBase`  
_L18-129_
- reflection: `UCLASS(MinimalAPI, HideCategories = Object, BlueprintType, PrioritizeCategories = ("Dataflow"))`
- inherits: `UChaosClothAssetBase`
- desc: Outfit asset for character clothing and simulation.
- L22 _public prototype_ `UChaosOutfitAsset(const FObjectInitializer& ObjectInitializer);`
- L23 _public prototype_ `UChaosOutfitAsset(FVTableHelper& Helper);` — This is declared so we can use TUniquePtr<FClothSimulationModel> with just a forward declare of that class
- L26 _public prototype_ `void Build(const TObjectPtr<const UChaosOutfit> InOutfit, UE::Dataflow::IContextAssetStoreInterface* ContextAssetStore = nullptr, bool bDeferResourceInit = false);`
- L29 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L30 _public prototype_ `virtual void PostLoad() override;`
- L33 _public function_ `const FManagedArrayCollection& GetOutfitCollection() const`
- L39 _public function_ `TObjectPtr<const UChaosOutfit> GetOutfit() const`
- L47 _private prototype_ `virtual bool HasValidClothSimulationModels() const override;`
- L48 _private function_ `virtual int32 GetNumClothSimulationModels() const override`
- L52 _private prototype_ `virtual FName GetClothSimulationModelName(int32 ModelIndex) const override;`
- L53 _private prototype_ `virtual TSharedPtr<const FChaosClothSimulationModel> GetClothSimulationModel(int32 ModelIndex) const override;`
- L54 _private prototype_ `virtual const TArray<TSharedRef<const FManagedArrayCollection>>& GetCollections(int32 ModelIndex) const override;`
- L55 _private prototype_ `virtual const UPhysicsAsset* GetPhysicsAssetForModel(int32 ModelIndex) const override;`
- L56 _private prototype_ `virtual FGuid GetAssetGuid(int32 ModelIndex) const override;`
- L58 _private function_ `virtual UChaosClothAssetBase* CreatePreviewAssetCopy(UObject* Outer, EObjectFlags Flags) const override`
- L69 _private function_ `virtual UPhysicsAsset* GetPhysicsAsset() const override`
- L73 _private function_ `virtual USkeleton* GetSkeleton() override`
- L77 _private function_ `virtual const USkeleton* GetSkeleton() const override`
- L81 _private function_ `virtual void SetSkeleton(USkeleton* InSkeleton) override`
- L83 _private prototype_ `virtual FString BuildDerivedDataKey(const ITargetPlatform* TargetPlatform) override;`
- L84 _private prototype_ `virtual void BuildLODModel(FSkeletalMeshRenderData& RenderData, const ITargetPlatform* TargetPlatform, int32 LODIndex) override;`
- L85 _private function_ `virtual const TCHAR* GetDerivedDataPrefix() const override`
- L89 _private prototype_ `virtual const TCHAR* GetDerivedDataVersion() const override;`
- L90 _private prototype_ `virtual void BeginPostLoadAssetImpl(FSkinnedAssetPostLoadContext& Context) override;`
- L95 _private prototype_ `int32 GetNumLODsFromPieces() const;` — Return the number of LODs derived from Pieces (at least 1).
- L109 _private prototype_ `UChaosClothAssetBase* CreatePreviewAssetCopyImpl( UObject* Outer, EObjectFlags Flags, bool bFilterToSingleSize, bool bBuildSimModelRenderData) const;` — Create a preview copy with outfit-specific options. @param Outer The outer object for the preview copy. @param Flags Object flags for the preview copy. @param bFilterToSingleSize If true, multi-size outfits are filtered to the first body size. @param bBuildSimModelRenderData If true and the asset has no render data, creates render data from the simulation model vertex positions, normals, and bone weights for preview visualization. @return A transient asset copy, or nullptr if this asset can be used directly.
- L117 _private member_ `TArray<FChaosOutfitPiece> Pieces;` — `UPROPERTY()`
- L120 _private member_ `TArray<TObjectPtr<USkeletalMesh>> Bodies;` — `UPROPERTY()` — Only contains dependencies, populated from the outfit collection
- L123 _private member_ `FManagedArrayCollection OutfitCollection;` — `UPROPERTY()`
- L127 _private member_ `TObjectPtr<UChaosOutfit> Outfit;` — `UPROPERTY(Instanced)` — Outfit source model used for generating this outfit asset

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSOUTFITASSETENGINE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEngine/Public/ChaosOutfitAsset/OutfitAssetUtility.h` (Public)


#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Chaos` (scope `UE`)
- L20 _namespace_ `namespace OutfitAsset` (scope `UE::Chaos`)
- L23 _prototype_ `int32 MergeBoneToSkeleton(const int32 BoneIndex, const FReferenceSkeleton& InSkeleton, FReferenceSkeleton& InOutSkeleton);` (scope `UE::Chaos::OutfitAsset`) — Merge bone to a new skeleton and return its new index in the new skeleton
- L25 _prototype_ `TArray<int32> GetChildren(const TArray<FMeshBoneInfo>& MeshBoneInfos, const int32 ParentIndex);` (scope `UE::Chaos::OutfitAsset`)
- L27 _prototype_ `void LogHierarchy(const TArray<FMeshBoneInfo>& MeshBoneInfos, const int32 ParentIndex = INDEX_NONE, int32 Indent = 0);` (scope `UE::Chaos::OutfitAsset`)
- L29 _prototype_ `void MergeSkeletons(const FReferenceSkeleton& InSkeleton, FReferenceSkeleton& InOutSkeleton, TArray<int32>& OutBoneMap);` (scope `UE::Chaos::OutfitAsset`)
- L31 _prototype_ `TArray<uint32> GetIndices(const FMultiSizeIndexContainer& MultiSizeIndexContainer, int32 VertexOffset = 0);` (scope `UE::Chaos::OutfitAsset`)
- L33 _prototype_ `TArray<FVector3f> GetPositions(const FPositionVertexBuffer& PositionVertexBuffer);` (scope `UE::Chaos::OutfitAsset`)
- L35 _prototype_ `TArray<FVector4f> GetTangents(const FStaticMeshVertexBuffer& StaticMeshVertexBuffer, int Axis);` (scope `UE::Chaos::OutfitAsset`)
- L37 _prototype_ `TArray<FVector2f> GetVertexUVs(const FStaticMeshVertexBuffer& StaticMeshVertexBuffer, const uint32 MaxTexCoords);` (scope `UE::Chaos::OutfitAsset`)
- L39 _prototype_ `TArray<FSkinWeightInfo> GetSkinWeights(const FSkinWeightVertexBuffer& SkinWeightVertexBuffer, const bool bUse16BitBoneWeight, const TArray<int32>* const BoneMap = nullptr);` (scope `UE::Chaos::OutfitAsset`)
- L41 _prototype_ `TArray<FColor> GetVertexColors(const FStaticMeshVertexBuffers& StaticMeshVertexBuffers);` (scope `UE::Chaos::OutfitAsset`)
- L43 _prototype_ `TArray<FMeshToMeshVertData> GetClothMappingData(const TArray<FSkelMeshRenderSection>& RenderSections, const TArray<FGuid>* AssetGuids = nullptr);` (scope `UE::Chaos::OutfitAsset`)
- L45 _prototype_ `TArray<FClothBufferIndexMapping> GetClothBufferIndexMappings( const FSkeletalMeshVertexClothBuffer& ClothVertexBuffer, const TArray<FSkelMeshRenderSection>& RenderSections, const int32 VertexOffset = 0, const TArray<FGuid>* AssetGuids = nullptr);` (scope `UE::Chaos::OutfitAsset`)
- L51 _prototype_ `void MergeBones(const FReferenceSkeleton& ReferenceSkeleton, const TArray<int32>& BoneMap, const TArray<FBoneIndexType>& BoneIndices, TArray<FBoneIndexType>& OutBoneIndices);` (scope `UE::Chaos::OutfitAsset`)

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEngine/Public/ChaosOutfitAsset/OutfitCollection.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSOUTFITASSETENGINE_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Chaos` (scope `UE`)
- L9 _namespace_ `namespace OutfitAsset` (scope `UE::Chaos`)
- L14 _namespace_ `namespace OutfitCollection` (scope `UE::Chaos::OutfitAsset`)
- L16 _namespace_ `namespace Group` (scope `UE::Chaos::OutfitAsset::OutfitCollection`)
- L18 _externvar_ `extern const FName Outfits;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Group`)
- L19 _externvar_ `extern const FName Pieces;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Group`)
- L20 _externvar_ `extern const FName BodySizes;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Group`)
- L21 _externvar_ `extern const FName BodyParts;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Group`)
- L22 _externvar_ `extern const FName Measurements;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Group`)
- L24 _namespace_ `namespace Attribute` (scope `UE::Chaos::OutfitAsset::OutfitCollection`)
- L26 _namespace_ `namespace Outfits` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute`)
- L28 _externvar_ `extern const FName Guid;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute::Outfits`) — FGuid
- L29 _externvar_ `extern const FName BodySize;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute::Outfits`) — int32 -> BodySizes
- L30 _externvar_ `extern const FName Name;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute::Outfits`) — FString
- L31 _externvar_ `extern const FName PiecesStart;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute::Outfits`) — int32 -> Pieces
- L32 _externvar_ `extern const FName PiecesCount;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute::Outfits`) — int32
- L34 _namespace_ `namespace Pieces` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute`)
- L36 _externvar_ `extern const FName Guid;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute::Pieces`) — FGuid
- L37 _externvar_ `extern const FName Name;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute::Pieces`) — FString
- L39 _namespace_ `namespace BodySizes` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute`)
- L41 _externvar_ `extern const FName Name;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute::BodySizes`) — FString
- L42 _externvar_ `extern const FName BodyPartsStart;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute::BodySizes`) — int32 -> BodyParts
- L43 _externvar_ `extern const FName BodyPartsCount;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute::BodySizes`) — int32
- L45 _namespace_ `namespace BodyParts` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute`)
- L47 _externvar_ `extern const FName SkeletalMeshPath;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute::BodyParts`) — FSoftObjectPath
- L49 _externvar_ `extern const FName SkeletalMesh;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute::BodyParts`) — `UE_DEPRECATED(5.7, "Use SkeletalMeshPath instead.")` — FString
- L50 _externvar_ `extern const FName RBFInterpolationSampleIndices;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute::BodyParts`) — TArray<int32>
- L51 _externvar_ `extern const FName RBFInterpolationSampleRestPositions;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute::BodyParts`) — TArray<FVector3f>
- L52 _externvar_ `extern const FName RBFInterpolationWeights;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute::BodyParts`) — TArray<float>
- L54 _namespace_ `namespace Measurements` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute`)
- L56 _externvar_ `extern const FName Name;` (scope `UE::Chaos::OutfitAsset::OutfitCollection::Attribute::Measurements`) — FString
- L62 _externvar_ `extern const FName DefaultBodySize;` (scope `UE::Chaos::OutfitAsset`) — Default body size name, when an outfit is created without any specific body size.
- L65 _variable_ `inline constexpr int32 DefaultNumRBFInterpolationPoints = 1500;` (scope `UE::Chaos::OutfitAsset`) — Default number of RBF Interpolation points used for RBF Resizing

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetEngine/Public/ChaosOutfitAsset/SizedOutfitSource.h` (Public)


#### struct `FChaosSizedOutfitSource`  
`struct FChaosSizedOutfitSource final`  
_L17-60_
- reflection: `USTRUCT(BlueprintType)`
- desc: Input structure for setting up a single sized outfit.
- L27 _public member_ `TObjectPtr<const UChaosClothAssetBase> SourceAsset;` — `UPROPERTY(EditAnywhere, Category = "OutfitSourceAsset")` — The cloth or outfit asset to assign for this body size. The asset must be the exact same garment representation for each specified sizes. If multiple garments in multiple sizes are needed, they will have to be composed in another Outfit asset.
- L34 _public member_ `FString SizeName;` — `UPROPERTY(EditAnywhere, Category = "OutfitBodySize")` — The unique name of this body size. The name of the first valid body part skeletal mesh will be used if empty.
- L41 _public member_ `TArray<TObjectPtr<const USkeletalMesh>> SourceBodyParts = { nullptr };` — `UPROPERTY(EditAnywhere, Category = "OutfitBodySize", Meta = (NoElementDuplicate))` — The list of body part skeletal meshes making up the source body for this size name. Usually one single MetaHuman merged body+head skeletal mesh.
- L50 _public member_ `int32 NumResizingInterpolationPoints = UE::Chaos::OutfitAsset::DefaultNumRBFInterpolationPoints;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "OutfitBodySize", Meta = (ClampMin = 0, ClampMax = 5000))` — The number of interpolation points used in the resizing algorithm. These points are distributed evenly across the entire body. Increasing this number increases the quality of the resizing operation, but at additional cost, including the initial operation of generating your resizable Outfit, and the size of your Outfit on disk. If you find you cannot generate acceptable resizing results by increasing this number, we recommend adding a new Size.
- L59 _public prototype_ `FString GetBodySizeName() const;` — Get a usable name for the body size. Return SizeName unless empty, in which case return the name of the first valid body part. If both SizeName and the SourceBodyParts are empty, but a valid SourceAsset is provided, it will return "Default" as the body size name. Otherwise if none of these are valid, an empty string is returned.
