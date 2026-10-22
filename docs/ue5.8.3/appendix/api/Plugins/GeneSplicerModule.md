# Plugins / GeneSplicerModule

- module root: `Plugins/Animation/GeneSplicer/Source/GeneSplicerModule`
- headers: 14; symbols: 352
- symbol kinds: class=12, delegate=6, enum=5, enumerator=16, function=2, member=18, namespace=7, prototype=283, struct=3
- PrivateDependencyModuleNames: GeneSplicerLib, RigLogicLib, RigLogicModule
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MessageLog, Projects, RigLogicModule, UnrealEd

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerModule/Private/GenePoolAssetCustomVersion.h` (Private)


#### struct `FGenePoolAssetCustomVersion`  
`struct FGenePoolAssetCustomVersion`  
_L9-26_
- desc: Custom serialization version for all packages containing GenePool types
- L22 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L25 _private function_ `FGenePoolAssetCustomVersion()`

#### enum `FGenePoolAssetCustomVersion::Type`  
`enum Type`  
_L11-19_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L17 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L18 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerModule/Private/RegionAffiliationAssetCustomVersion.h` (Private)


#### struct `FRegionAffiliationAssetCustomVersion`  
`struct FRegionAffiliationAssetCustomVersion`  
_L9-26_
- desc: Custom serialization version for all packages containing RegionAffilation types
- L22 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L25 _private function_ `FRegionAffiliationAssetCustomVersion()`

#### enum `FRegionAffiliationAssetCustomVersion::Type`  
`enum Type`  
_L11-19_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L17 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L18 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerModule/Public/GenePool.h` (Public)


#### enum `EGenePoolMask`  
`enum class EGenePoolMask : uint32`  
_L22-30_
- L24 _public enumerator_ `NeutralMeshes = 1 << 0`
- L25 _public enumerator_ `BlendShapes = 1 << 1`
- L26 _public enumerator_ `SkinWeights = 1 << 2`
- L27 _public enumerator_ `NeutralJoints = 1 << 3`
- L28 _public enumerator_ `JointBehavior = 1 << 4`
- L29 _public enumerator_ `All = (1 << 5) - 1`

#### class `FGenePool`  
`class FGenePool`  
_L34-80_
- L43 _public prototype_ `FGenePool(const IDNAReader* DeltaArchetype, TArrayView<IDNAReader*> DNAs, EGenePoolMask GenePoolMask = EGenePoolMask::All);`
- L44 _public prototype_ `FGenePool(const FString& Path, EGenePoolMask GenePoolMask = EGenePoolMask::All);`
- L45 _public prototype_ `FGenePool(FArchive& Ar, EGenePoolMask GenePoolMask = EGenePoolMask::All);`
- L47 _public prototype_ `~FGenePool();`
- L49 _public prototype_ `FGenePool(const FGenePool&) = delete;`
- L50 _public prototype_ `FGenePool& operator=(const FGenePool&) = delete;`
- L52 _public prototype_ `FGenePool(FGenePool&& rhs);`
- L53 _public prototype_ `FGenePool& operator=(FGenePool&& rhs);`
- L55 _public prototype_ `uint16 GetDNACount() const;`
- L56 _public prototype_ `FString GetDNAName(uint16 DNAIndex) const;`
- L57 _public prototype_ `EGender GetDNAGender(uint16 DNAIndex) const;`
- L58 _public prototype_ `uint16 GetDNAAge(uint16 DNAIndex) const;`
- L59 _public prototype_ `uint16 GetMeshCount() const;`
- L60 _public prototype_ `uint32 GetVertexPositionCount(uint16 MeshIndex) const;`
- L61 _public prototype_ `FVector GetDNAVertexPosition(uint16 DNAIndex, uint16 MeshIndex, uint32 VertexIndex) const;`
- L62 _public prototype_ `FVector GetArchetypeVertexPosition(uint16 MeshIndex, uint32 VertexIndex) const;`
- L63 _public prototype_ `uint16 GetJointCount() const;`
- L64 _public prototype_ `FString GetJointName(uint16 JointIndex) const;`
- L65 _public prototype_ `FVector GetDNANeutralJointWorldTranslation(uint16 DNAIndex, uint16 JointIndex) const;`
- L66 _public prototype_ `FVector GetArchetypeNeutralJointWorldTranslation(uint16 JointIndex) const;`
- L67 _public prototype_ `FVector GetDNANeutralJointWorldRotation(uint16 DNAIndex, uint16 JointIndex) const;`
- L68 _public prototype_ `FVector GetArchetypeNeutralJointWorldRotation(uint16 JointIndex) const;`
- L70 _public prototype_ `void WriteToFile(const FString& Path, EGenePoolMask GenePoolMask = EGenePoolMask::All) const;`
- L71 _public prototype_ `void Serialize(FArchive& Ar, EGenePoolMask GenePoolMask = EGenePoolMask::All) const;`
- L76 _private prototype_ `gs4::GenePool* Unwrap() const;`
- L79 _private member_ `TUniquePtr<gs4::GenePool> GenePoolPtr;`

#### enum `FGenePool::ECalculationType`  
`enum class ECalculationType : uint8`  
_L36-40_
- L38 _public enumerator_ `Scalar`
- L39 _public enumerator_ `SSE`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace gs4`
- L17 _namespace_ `namespace trio`
- L31 _prototype_ `ENUM_CLASS_FLAGS(EGenePoolMask);`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerModule/Public/GenePoolAsset.h` (Public)


#### class `UGenePoolAsset`  
`class UGenePoolAsset : public UObject`  
_L14-32_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L18 _public prototype_ `UGenePoolAsset();`
- L21 _public prototype_ `int32 GetDNACount() const;` — `UFUNCTION(BlueprintCallable, Category = "GeneSplicer")`
- L23 _public prototype_ `void SetGenePoolPtr(TSharedPtr<FGenePool> GenePoolPtr);`
- L24 _public prototype_ `const TSharedPtr<FGenePool>& GetGenePoolPtr() const;`
- L26 _public prototype_ `void Serialize(FArchive& Ar) override;`
- L30 _private member_ `FRWLock GenePoolUpdateLock;` — Synchronize GenePool updates
- L31 _private member_ `TSharedPtr<FGenePool> GenePool;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGenePoolAsset, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGenePoolAsset, Log, All);`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerModule/Public/GeneSplicer.h` (Public)


#### class `FGeneSplicer`  
`class FGeneSplicer`  
_L20-98_
- desc: A wrapper class for GeneSplicer
- L38 _public prototype_ `explicit FGeneSplicer(ECalculationType calculationType);` — @brief Constructor @param calculationType Determines which algorithm implementation is used for splicing
- L39 _public prototype_ `~FGeneSplicer();`
- L41 _public prototype_ `FGeneSplicer(const FGeneSplicer&) = delete;`
- L42 _public prototype_ `FGeneSplicer& operator=(const FGeneSplicer&) = delete;`
- L44 _public prototype_ `FGeneSplicer(FGeneSplicer&& rhs);`
- L45 _public prototype_ `FGeneSplicer& operator=(FGeneSplicer&& rhs);`
- L54 _public prototype_ `void Splice(const FSpliceData& InMixData, FGeneSplicerDNAReader& Output);` — @brief Run all the individual splicers. @param spliceData Contains all the necessary input data that is used during splicing. @param Output Output parameter - the DNA Reader that will contain the spliced DNA data.
- L62 _public prototype_ `void SpliceNeutralMeshes(const FSpliceData& InMixData, FGeneSplicerDNAReader& Output);` — @brief Run only the neutral mesh splicer. @param spliceData Contains all the necessary input data that is used during splicing. @param Output Output parameter - the DNA Reader that will contain the spliced DNA data.
- L70 _public prototype_ `void SpliceBlendShapes(const FSpliceData& InMixData, FGeneSplicerDNAReader& Output);` — @brief Run only the blend shape splicer. @param spliceData Contains all the necessary input data that is used during splicing. @param Output Output parameter - the DNA Reader that will contain the spliced DNA data.
- L78 _public prototype_ `void SpliceNeutralJoints(const FSpliceData& InMixData, FGeneSplicerDNAReader& Output);` — @brief Run only the neutral joint splicer. @param spliceData Contains all the necessary input data that is used during splicing. @param Output Output parameter - the DNA Reader that will contain the spliced DNA data.
- L86 _public prototype_ `void SpliceJointBehavior(const FSpliceData& InMixData, FGeneSplicerDNAReader& Output);` — @brief Run only the joint behavior splicer. @param spliceData Contains all the necessary input data that is used during splicing. @param Output Output parameter - the DNA Reader that will contain the spliced DNA data.
- L94 _public prototype_ `void SpliceSkinWeights(const FSpliceData& InMixData, FGeneSplicerDNAReader& Output);` — @brief Run only the skin weight splicer. @param spliceData Contains all the necessary input data that is used during splicing. @param Output Output parameter - the DNA Reader that will contain the spliced DNA data.
- L97 _private member_ `TUniquePtr<gs4::GeneSplicer> GeneSplicerPtr;`

#### enum `FGeneSplicer::ECalculationType`  
`enum class ECalculationType: uint8`  
_L27-31_
- desc: @brief Implementation type for GeneSplicer calculations.
- L29 _public enumerator_ `Scalar` — scalar implementation
- L30 _public enumerator_ `SSE` — vectorized implementation

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeneSplicer, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeneSplicer, Log, All);`
- L14 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerModule/Public/GeneSplicerBP.h` (Public)


#### class `UGeneSplicerBP`  
`class UGeneSplicerBP : public UBlueprintFunctionLibrary`  
_L14-28_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L20 _public prototype_ `static bool CreateGenePool(const FString& DNAFolderPath, const FString& ArchtypePath, const FString& GenePoolOutputPath);` — `UFUNCTION(BlueprintCallable, Category = "GeneSplicer")`
- L23 _public prototype_ `static bool CreateArchetype(const FString& DNAFolderPath, URegionAffiliationAsset* RafAsset, const FString& ArchetypeOutputPath);` — `UFUNCTION(BlueprintCallable, Category = "GeneSplicer")`
- L26 _public prototype_ `static void Splice(USpliceData* SpliceData);` — `UFUNCTION(BlueprintCallable, Category = "GeneSplicer")`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerModule/Public/GeneSplicerDNAReader.h` (Public)


#### class `FGeneSplicerDNAReader`  
`class FGeneSplicerDNAReader : public IDNAReader`  
_L15-210_
- inherits: `IDNAReader`
- desc: @brief A UE wrapper for a special purpose DNA Reader type which serves as the output parameter of GeneSplicer.
- L18 _public prototype_ `explicit FGeneSplicerDNAReader(IDNAReader* Source);`
- L21 _public prototype_ `uint16 GetFileFormatGeneration() const override;` — Header
- L22 _public prototype_ `uint16 GetFileFormatVersion() const override;`
- L24 _public prototype_ `FString GetName() const override;` — Descriptor
- L25 _public prototype_ `EArchetype GetArchetype() const override;`
- L26 _public prototype_ `EGender GetGender() const override;`
- L27 _public prototype_ `uint16 GetAge() const override;`
- L28 _public prototype_ `uint32 GetMetaDataCount() const override;`
- L29 _public prototype_ `FString GetMetaDataKey(uint32 Index) const override;`
- L30 _public prototype_ `FString GetMetaDataValue(const FString& Key) const override;`
- L31 _public prototype_ `ETranslationUnit GetTranslationUnit() const override;`
- L32 _public prototype_ `ERotationUnit GetRotationUnit() const override;`
- L33 _public prototype_ `FCoordinateSystem GetCoordinateSystem() const override;`
- L34 _public prototype_ `ERotationSequence GetRotationSequence() const override;`
- L35 _public prototype_ `FRotationSign GetRotationSign() const override;`
- L36 _public prototype_ `EFaceWindingOrder GetFaceWindingOrder() const override;`
- L37 _public prototype_ `uint16 GetLODCount() const override;`
- L38 _public prototype_ `uint16 GetDBMaxLOD() const override;`
- L39 _public prototype_ `FString GetDBComplexity() const override;`
- L40 _public prototype_ `FString GetDBName() const override;`
- L42 _public prototype_ `uint16 GetGUIControlCount() const override;` — Definition
- L43 _public prototype_ `FString GetGUIControlName(uint16 Index) const override;`
- L44 _public prototype_ `uint16 GetRawControlCount() const override;`
- L45 _public prototype_ `FString GetRawControlName(uint16 Index) const override;`
- L46 _public prototype_ `uint16 GetJointCount() const override;`
- L47 _public prototype_ `FString GetJointName(uint16 Index) const override;`
- L48 _public prototype_ `uint16 GetJointIndexListCount() const override;`
- L49 _public prototype_ `TArrayView<const uint16> GetJointIndicesForLOD(uint16 LOD) const override;`
- L50 _public prototype_ `uint16 GetJointParentIndex(uint16 Index) const override;`
- L51 _public prototype_ `uint16 GetBlendShapeChannelCount() const override;`
- L52 _public prototype_ `FString GetBlendShapeChannelName(uint16 Index) const override;`
- L53 _public prototype_ `uint16 GetBlendShapeChannelIndexListCount() const override;`
- L54 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelIndicesForLOD(uint16 LOD) const override;`
- L55 _public prototype_ `uint16 GetAnimatedMapCount() const override;`
- L56 _public prototype_ `FString GetAnimatedMapName(uint16 Index) const override;`
- L57 _public prototype_ `uint16 GetAnimatedMapIndexListCount() const override;`
- L58 _public prototype_ `TArrayView<const uint16> GetAnimatedMapIndicesForLOD(uint16 LOD) const override;`
- L59 _public prototype_ `uint16 GetMeshCount() const override;`
- L60 _public prototype_ `FString GetMeshName(uint16 Index) const override;`
- L61 _public prototype_ `uint16 GetMeshIndexListCount() const override;`
- L62 _public prototype_ `TArrayView<const uint16> GetMeshIndicesForLOD(uint16 LOD) const override;`
- L63 _public prototype_ `uint16 GetMeshBlendShapeChannelMappingCount() const override;`
- L64 _public prototype_ `FMeshBlendShapeChannelMapping GetMeshBlendShapeChannelMapping(uint16 Index) const override;`
- L65 _public prototype_ `TArrayView<const uint16> GetMeshBlendShapeChannelMappingIndicesForLOD(uint16 LOD) const override;`
- L66 _public prototype_ `FVector GetNeutralJointTranslation(uint16 Index) const override;`
- L67 _public prototype_ `FVector GetNeutralJointRotation(uint16 Index) const override;`
- L69 _public prototype_ `TArrayView<const uint16> GetGUIToRawInputIndices() const override;` — Behavior
- L70 _public prototype_ `TArrayView<const uint16> GetGUIToRawOutputIndices() const override;`
- L71 _public prototype_ `TArrayView<const float> GetGUIToRawFromValues() const override;`
- L72 _public prototype_ `TArrayView<const float> GetGUIToRawToValues() const override;`
- L73 _public prototype_ `TArrayView<const float> GetGUIToRawSlopeValues() const override;`
- L74 _public prototype_ `TArrayView<const float> GetGUIToRawCutValues() const override;`
- L75 _public prototype_ `uint16 GetPSDCount() const override;`
- L76 _public prototype_ `TArrayView<const uint16> GetPSDRowIndices() const override;`
- L77 _public prototype_ `TArrayView<const uint16> GetPSDColumnIndices() const override;`
- L78 _public prototype_ `TArrayView<const float> GetPSDValues() const override;`
- L79 _public prototype_ `uint16 GetJointRowCount() const override;`
- L80 _public prototype_ `uint16 GetJointColumnCount() const override;`
- L81 _public prototype_ `TArrayView<const uint16> GetJointVariableAttributeIndices(uint16 LOD) const override;`
- L82 _public prototype_ `uint16 GetJointGroupCount() const override;`
- L83 _public prototype_ `TArrayView<const uint16> GetJointGroupLODs(uint16 JointGroupIndex) const override;`
- L84 _public prototype_ `TArrayView<const uint16> GetJointGroupInputIndices(uint16 JointGroupIndex) const override;`
- L85 _public prototype_ `TArrayView<const uint16> GetJointGroupOutputIndices(uint16 JointGroupIndex) const override;`
- L86 _public prototype_ `TArrayView<const float> GetJointGroupValues(uint16 JointGroupIndex) const override;`
- L87 _public prototype_ `TArrayView<const uint16> GetJointGroupJointIndices(uint16 JointGroupIndex) const override;`
- L88 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelLODs() const override;`
- L89 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelOutputIndices() const override;`
- L90 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelInputIndices() const override;`
- L91 _public prototype_ `TArrayView<const uint16> GetAnimatedMapLODs() const override;`
- L92 _public prototype_ `TArrayView<const uint16> GetAnimatedMapInputIndices() const override;`
- L93 _public prototype_ `TArrayView<const uint16> GetAnimatedMapOutputIndices() const override;`
- L94 _public prototype_ `TArrayView<const float> GetAnimatedMapFromValues() const override;`
- L95 _public prototype_ `TArrayView<const float> GetAnimatedMapToValues() const override;`
- L96 _public prototype_ `TArrayView<const float> GetAnimatedMapSlopeValues() const override;`
- L97 _public prototype_ `TArrayView<const float> GetAnimatedMapCutValues() const override;`
- L99 _public prototype_ `uint32 GetVertexPositionCount(uint16 MeshIndex) const override;` — Geometry
- L100 _public prototype_ `FVector GetVertexPosition(uint16 MeshIndex, uint32 VertexIndex) const override;`
- L101 _public prototype_ `TArrayView<const float> GetVertexPositionXs(uint16 MeshIndex) const override;`
- L102 _public prototype_ `TArrayView<const float> GetVertexPositionYs(uint16 MeshIndex) const override;`
- L103 _public prototype_ `TArrayView<const float> GetVertexPositionZs(uint16 MeshIndex) const override;`
- L104 _public prototype_ `uint32 GetVertexTextureCoordinateCount(uint16 MeshIndex) const override;`
- L105 _public prototype_ `FTextureCoordinate GetVertexTextureCoordinate(uint16 MeshIndex, uint32 TextureCoordinateIndex) const override;`
- L106 _public prototype_ `uint32 GetVertexNormalCount(uint16 MeshIndex) const override;`
- L107 _public prototype_ `FVector GetVertexNormal(uint16 MeshIndex, uint32 NormalIndex) const override;`
- L108 _public prototype_ `uint32 GetFaceCount(uint16 MeshIndex) const override;`
- L109 _public prototype_ `TArrayView<const uint32> GetFaceVertexLayoutIndices(uint16 MeshIndex, uint32 FaceIndex) const override;`
- L110 _public prototype_ `uint32 GetVertexLayoutCount(uint16 MeshIndex) const override;`
- L111 _public prototype_ `FVertexLayout GetVertexLayout(uint16 MeshIndex, uint32 LayoutIndex) const override;`
- L112 _public prototype_ `uint16 GetMaximumInfluencePerVertex(uint16 MeshIndex) const override;`
- L113 _public prototype_ `uint32 GetSkinWeightsCount(uint16 MeshIndex) const override;`
- L114 _public prototype_ `TArrayView<const float> GetSkinWeightsValues(uint16 MeshIndex, uint32 VertexIndex) const override;`
- L115 _public prototype_ `TArrayView<const uint16> GetSkinWeightsJointIndices(uint16 MeshIndex, uint32 VertexIndex) const override;`
- L116 _public prototype_ `uint16 GetBlendShapeTargetCount(uint16 MeshIndex) const override;`
- L117 _public prototype_ `uint16 GetBlendShapeChannelIndex(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L118 _public prototype_ `uint32 GetBlendShapeTargetDeltaCount(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L119 _public prototype_ `FVector GetBlendShapeTargetDelta(uint16 MeshIndex, uint16 BlendShapeTargetIndex, uint32 DeltaIndex) const override;`
- L120 _public prototype_ `TArrayView<const float> GetBlendShapeTargetDeltaXs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L121 _public prototype_ `TArrayView<const float> GetBlendShapeTargetDeltaYs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L122 _public prototype_ `TArrayView<const float> GetBlendShapeTargetDeltaZs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L123 _public prototype_ `TArrayView<const uint32> GetBlendShapeTargetVertexIndices(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L125 _public prototype_ `uint16 GetMLControlCount() const override;` — Machine Learned Behavior
- L126 _public prototype_ `FString GetMLControlName(uint16 Index) const override;`
- L127 _public prototype_ `uint16 GetNeuralNetworkCount() const override;`
- L128 _public prototype_ `uint16 GetNeuralNetworkIndexListCount() const override;`
- L129 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkIndicesForLOD(uint16 LOD) const override;`
- L130 _public prototype_ `uint16 GetMeshRegionCount(uint16 MeshIndex) const override;`
- L131 _public prototype_ `FString GetMeshRegionName(uint16 MeshIndex, uint16 RegionIndex) const override;`
- L132 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkIndicesForMeshRegion(uint16 MeshIndex, uint16 RegionIndex) const override;`
- L133 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkInputIndices(uint16 NetIndex) const override;`
- L134 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkOutputIndices(uint16 NetIndex) const override;`
- L135 _public prototype_ `uint16 GetNeuralNetworkLayerCount(uint16 NetIndex) const override;`
- L136 _public prototype_ `EActivationFunction GetNeuralNetworkLayerActivationFunction(uint16 NetIndex, uint16 LayerIndex) const override;`
- L137 _public prototype_ `TArrayView<const float> GetNeuralNetworkLayerActivationFunctionParameters(uint16 NetIndex, uint16 LayerIndex) const override;`
- L138 _public prototype_ `TArrayView<const float> GetNeuralNetworkLayerBiases(uint16 NetIndex, uint16 LayerIndex) const override;`
- L139 _public prototype_ `TArrayView<const float> GetNeuralNetworkLayerWeights(uint16 NetIndex, uint16 LayerIndex) const override;`
- L141 _public prototype_ `ETranslationRepresentation GetJointTranslationRepresentation(uint16 JointIndex) const override;` — JointBehaviorMetadataReader
- L142 _public prototype_ `ERotationRepresentation GetJointRotationRepresentation(uint16 JointIndex) const override;`
- L143 _public prototype_ `EScaleRepresentation GetJointScaleRepresentation(uint16 JointIndex) const override;`
- L145 _public prototype_ `uint16 GetRBFPoseCount() const override;` — RBFBehavior
- L146 _public prototype_ `FString GetRBFPoseName(uint16 PoseIndex) const override;`
- L147 _public prototype_ `TArrayView<const uint16> GetRBFPoseJointOutputIndices(uint16 PoseIndex) const override;`
- L148 _public prototype_ `TArrayView<const uint16> GetRBFPoseBlendShapeChannelOutputIndices(uint16 PoseIndex) const override;`
- L149 _public prototype_ `TArrayView<const uint16> GetRBFPoseAnimatedMapOutputIndices(uint16 PoseIndex) const override;`
- L150 _public prototype_ `TArrayView<const float> GetRBFPoseJointOutputValues(uint16 PoseIndex) const override;`
- L151 _public prototype_ `float GetRBFPoseScale(uint16 PoseIndex) const override;`
- L152 _public prototype_ `uint16 GetRBFPoseControlCount() const override;`
- L153 _public prototype_ `FString GetRBFPoseControlName(uint16 PoseControlIndex) const override;`
- L154 _public prototype_ `TArrayView<const uint16> GetRBFPoseInputControlIndices(uint16 PoseIndex) const override;`
- L155 _public prototype_ `TArrayView<const uint16> GetRBFPoseOutputControlIndices(uint16 PoseIndex) const override;`
- L156 _public prototype_ `TArrayView<const float> GetRBFPoseOutputControlWeights(uint16 PoseIndex) const override;`
- L157 _public prototype_ `uint16 GetRBFSolverCount() const override;`
- L158 _public prototype_ `uint16 GetRBFSolverIndexListCount() const override;`
- L159 _public prototype_ `TArrayView<const uint16> GetRBFSolverIndicesForLOD(uint16 LOD) const override;`
- L160 _public prototype_ `FString GetRBFSolverName(uint16 SolverIndex) const override;`
- L161 _public prototype_ `TArrayView<const uint16> GetRBFSolverRawControlIndices(uint16 SolverIndex) const override;`
- L162 _public prototype_ `TArrayView<const uint16> GetRBFSolverPoseIndices(uint16 SolverIndex) const override;`
- L163 _public prototype_ `TArrayView<const float> GetRBFSolverRawControlValues(uint16 SolverIndex) const override;`
- L164 _public prototype_ `ERBFSolverType GetRBFSolverType(uint16 SolverIndex) const override;`
- L165 _public prototype_ `float GetRBFSolverRadius(uint16 SolverIndex) const override;`
- L166 _public prototype_ `EAutomaticRadius GetRBFSolverAutomaticRadius(uint16 SolverIndex) const override;`
- L167 _public prototype_ `float GetRBFSolverWeightThreshold(uint16 SolverIndex) const override;`
- L168 _public prototype_ `ERBFDistanceMethod GetRBFSolverDistanceMethod(uint16 SolverIndex) const override;`
- L169 _public prototype_ `ERBFNormalizeMethod GetRBFSolverNormalizeMethod(uint16 SolverIndex) const override;`
- L170 _public prototype_ `ERBFFunctionType GetRBFSolverFunctionType(uint16 SolverIndex) const override;`
- L171 _public prototype_ `ETwistAxis GetRBFSolverTwistAxis(uint16 SolverIndex) const override;`
- L173 _public prototype_ `uint16 GetTwistCount() const override;` — TwistSwingBehavior
- L174 _public prototype_ `ETwistAxis GetTwistSetupTwistAxis(uint16 TwistIndex) const override;`
- L175 _public prototype_ `TArrayView<const uint16> GetTwistInputControlIndices(uint16 TwistIndex) const override;`
- L176 _public prototype_ `TArrayView<const uint16> GetTwistOutputJointIndices(uint16 TwistIndex) const override;`
- L177 _public prototype_ `TArrayView<const float> GetTwistBlendWeights(uint16 TwistIndex) const override;`
- L178 _public prototype_ `uint16 GetSwingCount() const override;`
- L179 _public prototype_ `ETwistAxis GetSwingSetupTwistAxis(uint16 SwingIndex) const override;`
- L180 _public prototype_ `TArrayView<const uint16> GetSwingInputControlIndices(uint16 SwingIndex) const override;`
- L181 _public prototype_ `TArrayView<const uint16> GetSwingOutputJointIndices(uint16 SwingIndex) const override;`
- L182 _public prototype_ `TArrayView<const float> GetSwingBlendWeights(uint16 SwingIndex) const override;`
- L184 _public prototype_ `uint16 GetMLTypeCount() const override;` — MachineLearnedBehaviorExtReader
- L185 _public prototype_ `uint16 GetMLOperationSetCount(uint16 MLTypeIndex) const override;`
- L186 _public prototype_ `uint16 GetMLOperationCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const override;`
- L187 _public prototype_ `EMachineLearnedBehaviorOperationType GetMLOperationType(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L188 _public prototype_ `TArrayView<const uint32> GetMLOperationParameters(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L189 _public prototype_ `TArrayView<const uint16> GetMLOperationDependencyOperationSetIndices(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L190 _public prototype_ `TArrayView<const uint16> GetMLOperationDependencyOperationIndices(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L191 _public prototype_ `uint16 GetMLOperationIndexListCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const override;`
- L192 _public prototype_ `TArrayView<const uint16> GetMLOperationIndicesForLOD(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 LOD) const override;`
- L193 _public prototype_ `TArrayView<const uint16> GetMLJointsInputIndices() const override;`
- L194 _public prototype_ `TArrayView<const uint16> GetMLJointsOutputIndices() const override;`
- L195 _public prototype_ `TArrayView<const uint16> GetMLJointsParameterKeys() const override;`
- L196 _public prototype_ `TArrayView<const uint16> GetMLJointsParameterValues() const override;`
- L199 _public prototype_ `void Unload(EDNADataLayer Layer) override;` — Reader
- L201 _public prototype_ `const FDNAConfig& GetConfig() const override;`
- L205 _private prototype_ `dna::Reader* Unwrap() const;`
- L208 _private member_ `TUniquePtr<IDNAReader> ReaderPtr;`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerModule/Public/GeneSplicerModule.h` (Public)


#### class `FGeneSplicerModule`  
`class FGeneSplicerModule: public IModuleInterface`  
_L10-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeneSplicerModule, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeneSplicerModule, Log, All);`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerModule/Public/PoolSpliceParams.h` (Public)


#### class `FPoolSpliceParams`  
`class FPoolSpliceParams`  
_L19-38_
- L22 _public prototype_ `~FPoolSpliceParams();`
- L24 _public prototype_ `void SetDNAFilter(TArrayView<const uint16> DNAIndices);`
- L25 _public prototype_ `void SetMeshFilter(TArrayView<const uint16> MeshIndices);`
- L26 _public prototype_ `void SetSpliceWeights(uint16 DNAStartIndex, TArrayView<const float> Weights);`
- L27 _public prototype_ `void SetScale(float scale);`
- L28 _public prototype_ `uint16 GetDNACount() const;`
- L29 _public prototype_ `uint16 GetRegionCount() const;`
- L33 _private prototype_ `FPoolSpliceParams(gs4::PoolSpliceParams* PoolSpliceParams);`
- L34 _private prototype_ `gs4::PoolSpliceParams* Unwrap() const;`
- L37 _private member_ `gs4::PoolSpliceParams* PoolSpliceParamsPtr;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerModule/Public/PoolSpliceParamsBP.h` (Public)


#### class `UPoolSpliceParams`  
`class UPoolSpliceParams : public UObject`  
_L13-39_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L18 _public prototype_ `UPoolSpliceParams() = default;`
- L21 _public prototype_ `void RegisterToSpliceData(USpliceData* SpliceData, const FString& Name, const UGenePoolAsset* GenePoolAsset, URegionAffiliationAsset* Raf);` — `UFUNCTION(BlueprintCallable, Category="GeneSplicer")`
- L24 _public prototype_ `int32 GetDNACount() const;` — `UFUNCTION(BlueprintCallable, Category = "GeneSplicer")`
- L27 _public prototype_ `int32 GetRegionCount() const;` — `UFUNCTION(BlueprintCallable, Category = "GeneSplicer")`
- L30 _public prototype_ `const TArray<FString>& GetRegionNames() const;` — `UFUNCTION(BlueprintCallable, Category = "GeneSplicer")`
- L33 _public prototype_ `void SetSpliceWeights(int32 DNAStartIndex, const TArray<float>& Weights);` — `UFUNCTION(BlueprintCallable, Category = "GeneSplicer")`
- L36 _private member_ `TSharedPtr<FPoolSpliceParams> PoolSpliceParams;`
- L37 _private member_ `TArray<FString> RegionNames;`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerModule/Public/RegionAffiliationAsset.h` (Public)


#### class `URegionAffiliationAsset`  
`class URegionAffiliationAsset : public UObject`  
_L14-34_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L18 _public prototype_ `URegionAffiliationAsset();`
- L21 _public prototype_ `int32 GetRegionCount() const;` — `UFUNCTION(BlueprintCallable, Category = "GeneSplicer")`
- L24 _public prototype_ `FString GetRegionName(int32 RegionIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "GeneSplicer")`
- L26 _public prototype_ `void SetRegionAffiliationPtr(TSharedPtr<FRegionAffiliationReader> RegionAffiliationReaderPtr);`
- L27 _public prototype_ `const TSharedPtr<FRegionAffiliationReader>& getRegionAffiliationReaderPtr();`
- L29 _public prototype_ `void Serialize(FArchive& Ar) override;`
- L32 _private member_ `FRWLock UpdateLock;` — Synchronize raf updates
- L33 _private member_ `TSharedPtr<FRegionAffiliationReader> RegionAffiliationReader;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRegionAffiliationAsset, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRegionAffiliationAsset, Log, All);`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerModule/Public/RegionAffiliationReader.h` (Public)


#### class `FRegionAffiliationReader`  
`class FRegionAffiliationReader`  
_L20-52_
- L23 _public prototype_ `FRegionAffiliationReader(const FString& FilePath);`
- L24 _public prototype_ `FRegionAffiliationReader(FArchive& Ar);`
- L25 _public prototype_ `~FRegionAffiliationReader();`
- L27 _public prototype_ `FRegionAffiliationReader(const FRegionAffiliationReader&) = delete;`
- L28 _public prototype_ `FRegionAffiliationReader& operator=(const FRegionAffiliationReader&) = delete;`
- L30 _public prototype_ `FRegionAffiliationReader(FRegionAffiliationReader&& rhs) = default;`
- L31 _public prototype_ `FRegionAffiliationReader& operator=(FRegionAffiliationReader&& rhs) = default;`
- L33 _public prototype_ `uint16 GetRegionNum() const;`
- L34 _public prototype_ `FString getRegionName(uint16 RegionIndex) const;`
- L35 _public prototype_ `void GetVertexRegionAffiliation(uint16 MeshId, int32 VertexId, TArray<float>& OutRegionAffiliations);`
- L37 _public prototype_ `void Serialize(FArchive& Ar) const;`
- L38 _public prototype_ `void WriteToFile(const FString& Path) const;`
- L43 _private prototype_ `raf::RegionAffiliationBinaryStreamReader* Unwrap() const;`
- L50 _private member_ `TUniquePtr<raf::RegionAffiliationBinaryStreamReader, FRegionAffiliationReaderDeleter> RegionAffiliationPtr;`

#### struct `FRegionAffiliationReader::FRegionAffiliationReaderDeleter`  
`struct FRegionAffiliationReaderDeleter`  
_L46-49_
- L48 _public prototype_ `void operator()(raf::RegionAffiliationBinaryStreamReader* Pointer);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace raf`
- L13 _namespace_ `namespace trio`
- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRegionAffiliationReader, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRegionAffiliationReader, Log, All);`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerModule/Public/SpliceData.h` (Public)


#### class `FSpliceData`  
`class FSpliceData`  
_L20-43_
- L23 _public prototype_ `explicit FSpliceData();`
- L25 _public prototype_ `~FSpliceData();`
- L27 _public prototype_ `FSpliceData(const FSpliceData&) = delete;`
- L28 _public prototype_ `FSpliceData& operator=(const FSpliceData&) = delete;`
- L30 _public prototype_ `FSpliceData(FSpliceData&&);`
- L31 _public prototype_ `FSpliceData& operator=(FSpliceData&&);`
- L33 _public prototype_ `void RegisterGenePool(const FString& name, const FRegionAffiliationReader& RegionAffiliationReader, const TSharedPtr<FGenePool>& GenePool);`
- L34 _public prototype_ `void UnregisterGenePool(const FString& name);`
- L35 _public prototype_ `TSharedPtr<FPoolSpliceParams> GetPoolParams(const FString& name);`
- L36 _public prototype_ `void SetBaseArchetype(TSharedPtr<const IDNAReader> baseArchetype);`
- L39 _private prototype_ `gs4::SpliceData* Unwrap() const;`
- L42 _private member_ `TUniquePtr<gs4::SpliceData> SpliceDataPtr;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerModule/Public/SpliceDataBP.h` (Public)


#### class `USpliceData`  
`class USpliceData : public UObject`  
_L22-65_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L27 _public prototype_ `USpliceData();`
- L31 _public prototype_ `void RegisterGenePool(const FString& Name, UGenePoolAsset* GenePoolAsset, URegionAffiliationAsset* raf);` — `UFUNCTION(BlueprintCallable, Category = "GeneSplicer")`
- L33 _public prototype_ `TSharedPtr<FPoolSpliceParams> InitPoolSpliceParams(const FString& Name, UGenePoolAsset* GenePoolAsset, URegionAffiliationAsset* raf);`
- L36 _public prototype_ `void SetSpliceWeights(const FString& Name, int32 DNAStartIndex, const TArray<float>& Weights);` — `UFUNCTION(BlueprintCallable, Category = "GeneSplicer")`
- L39 _public prototype_ `void SetArchetype(const FString& path);` — `UFUNCTION(BlueprintCallable, Category = "GeneSplicer")`
- L42 _public prototype_ `void SetSkeletalMeshComponent(USkeletalMeshComponent* NewSkelMeshComponent);` — `UFUNCTION(BlueprintCallable, Category = "GeneSplicer")`
- L45 _public prototype_ `USkeletalMeshComponent* GetSkeletalMeshComponent() const;` — `UFUNCTION(BlueprintPure, Category = "GeneSplicer")`
- L47 _public prototype_ `TSharedPtr<FDNAToSkelMeshMap> GetDNASkelMeshMap() const;`
- L49 _public prototype_ `TSharedPtr<FGeneSplicerDNAReader> GetOutputDNA() const;`
- L51 _public prototype_ `FSpliceData& GetSpliceDataImpl();`
- L53 _public prototype_ `const FSpliceData& GetSpliceDataImpl() const;`
- L56 _private prototype_ `void GenerateDNASkelMeshMapping();`
- L60 _private member_ `FSpliceData SpliceDataImpl;`
- L61 _private member_ `USkeletalMeshComponent* SkelMeshComponent;`
- L62 _private member_ `TSharedPtr<FDNAToSkelMeshMap> DNASkelMeshMap;`
- L63 _private member_ `TSharedPtr<FGeneSplicerDNAReader> OutputDNA;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSpliceData, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSpliceData, Log, All);`
