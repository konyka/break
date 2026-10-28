# Plugins / ACLPlugin

- module root: `Plugins/Animation/ACLPlugin/Source/ACLPlugin`
- headers: 13; symbols: 310
- symbol kinds: class=11, enum=6, enumerator=20, externvar=1, function=88, macro=6, member=83, namespace=3, prototype=71, struct=15, typedef=6
- PrivateDependencyModuleNames: DesktopPlatform, TraceLog, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Classes/AnimBoneCompressionCodec_ACL.h` (Public)


#### class `UAnimBoneCompressionCodec_ACL`  
`class UAnimBoneCompressionCodec_ACL : public UAnimBoneCompressionCodec_ACLBase`  
_L14-44_
- reflection: `UCLASS(MinimalAPI, config = Engine, meta = (DisplayName = "Anim Compress ACL"))`
- inherits: `UAnimBoneCompressionCodec_ACLBase`
- desc: Uses the open source Animation Compression Library with default settings suitable for general purpose animations.
- L21 _private member_ `TArray<TObjectPtr<class USkeletalMesh>> OptimizationTargets;` — `UPROPERTY(EditAnywhere, Category = "ACL Options")` — The skeletal meshes used to estimate the skinning deformation during compression.
- L25 _private member_ `FPerPlatformFloat KeyframeStrippingProportion;` — `UPROPERTY(EditAnywhere, Category = "ACL Destructive Options", meta = (ClampMin = "0", ClampMax = "1"))` — The minimum proportion of keyframes that should be stripped.
- L29 _private member_ `FPerPlatformFloat KeyframeStrippingThreshold;` — `UPROPERTY(EditAnywhere, Category = "ACL Destructive Options", meta = (ClampMin = "0"))` — The error threshold below which to strip keyframes. If a keyframe can be reconstructed with an error below the threshold, it is stripped.
- L33 _private prototype_ `virtual void PopulateDDCKey(const UE::Anim::Compression::FAnimDDCKeyArgs& KeyArgs, FArchive& Ar) override;` — UAnimBoneCompressionCodec implementation
- L36 _private prototype_ `virtual void GetCompressionSettings(const class ITargetPlatform* TargetPlatform, acl::compression_settings& OutSettings) const override;` — UAnimBoneCompressionCodec_ACLBase implementation
- L37 _private function_ `virtual TArray<class USkeletalMesh*> GetOptimizationTargets() const override`
- L41 _private prototype_ `virtual void DecompressPose(FAnimSequenceDecompressionContext& DecompContext, const BoneTrackArray& RotationPairs, const BoneTrackArray& TranslationPairs, const BoneTrackArray& ScalePairs, TArrayView<FTransform>& OutAtoms) const override;` — UAnimBoneCompressionCodec implementation
- L42 _private prototype_ `virtual void DecompressPose(FAnimSequenceDecompressionContext& DecompContext, const UE::Anim::FAnimPoseDecompressionData& DecompressionData) const override;`
- L43 _private prototype_ `virtual void DecompressBone(FAnimSequenceDecompressionContext& DecompContext, int32 TrackIndex, FTransform& OutAtom) const override;`

### `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Classes/AnimBoneCompressionCodec_ACLBase.h` (Public)


#### struct `FACLCompressedAnimDataBase`  
`struct FACLCompressedAnimDataBase : public ICompressedAnimData`  
_L25-32_
- inherits: `ICompressedAnimData`
- L28 _public member_ `bool bCompressionFailed = false;` — Whether or not compression failed
- L31 _public prototype_ `virtual void SerializeCompressedData(UObject* DataOwner, FArchive& Ar) override;` — ICompressedAnimData implementation

#### struct `FACLCompressedAnimData`  
`struct FACLCompressedAnimData final : public FACLCompressedAnimDataBase`  
_L34-45_
- inherits: `FACLCompressedAnimDataBase`
- L37 _public member_ `TArrayView<uint8> CompressedByteStream;` — Holds the compressed_tracks instance
- L39 _public function_ `const acl::compressed_tracks* GetCompressedTracks() const`
- L42 _public function_ `virtual void Bind(const TArrayView<uint8> BulkData) override` — ICompressedAnimData implementation
- L43 _public function_ `virtual int64 GetApproxCompressedSize() const override`
- L44 _public prototype_ `virtual bool IsValid() const override;`

#### class `UAnimBoneCompressionCodec_ACLBase`  
`class UAnimBoneCompressionCodec_ACLBase : public UAnimBoneCompressionCodec`  
_L49-90_
- reflection: `UCLASS(abstract, MinimalAPI)`
- inherits: `UAnimBoneCompressionCodec`
- desc: The base codec implementation for ACL support.
- L56 _private member_ `TEnumAsByte<ACLCompressionLevel> CompressionLevel;` — `UPROPERTY(EditAnywhere, Category = "ACL Options")` — The compression level to use. Higher levels will be slower to compress but yield a lower memory footprint.
- L60 _private member_ `ACLPhantomTrackMode PhantomTrackMode;` — `UPROPERTY(EditAnywhere, Category = "ACL Options")` — How to treat phantom tracks. Phantom tracks are not mapped to a skeleton bone.
- L64 _private member_ `float DefaultVirtualVertexDistance;` — `UPROPERTY(EditAnywhere, Category = "ACL Options", meta = (ClampMin = "0"))` — The default virtual vertex distance for normal bones.
- L68 _private member_ `float SafeVirtualVertexDistance;` — `UPROPERTY(EditAnywhere, Category = "ACL Options", meta = (ClampMin = "0"))` — The virtual vertex distance for bones that requires extra accuracy.
- L72 _private member_ `float ErrorThreshold;` — `UPROPERTY(EditAnywhere, Category = "ACL Options", meta = (ClampMin = "0"))` — The error threshold to use when optimizing and compressing the animation sequence.
- L75 _private prototype_ `virtual bool IsHighFidelity(const FCompressibleAnimData& CompressibleAnimData) const override;` — UAnimBoneCompressionCodec implementation
- L76 _private prototype_ `virtual bool Compress(const FCompressibleAnimData& CompressibleAnimData, FCompressibleAnimDataResult& OutResult) override;`
- L77 _private prototype_ `virtual void PopulateDDCKey(const UE::Anim::Compression::FAnimDDCKeyArgs& KeyArgs, FArchive& Ar) override;`
- L78 _private prototype_ `virtual int64 EstimateCompressionMemoryUsage(const UAnimSequence& AnimSequence) const override;`
- L81 _private function_ `virtual void PostCompression(const FCompressibleAnimData& CompressibleAnimData, FCompressibleAnimDataResult& OutResult) const` — Our implementation
- L82 _private prototype_ `virtual void GetCompressionSettings(const class ITargetPlatform* TargetPlatform, acl::compression_settings& OutSettings) const PURE_VIRTUAL(UAnimBoneCompressionCodec_ACLBase::GetCompressionSettings, );`
- L83 _private function_ `virtual TArray<class USkeletalMesh*> GetOptimizationTargets() const`
- L87 _private prototype_ `virtual TUniquePtr<ICompressedAnimData> AllocateAnimData() const override;` — UAnimBoneCompressionCodec implementation
- L88 _private prototype_ `virtual void ByteSwapIn(ICompressedAnimData& AnimData, TArrayView<uint8> CompressedData, FMemoryReader& MemoryStream) const override;`
- L89 _private prototype_ `virtual void ByteSwapOut(ICompressedAnimData& AnimData, TArrayView<uint8> CompressedData, FMemoryWriter& MemoryStream) const override;`

### `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Classes/AnimBoneCompressionCodec_ACLCustom.h` (Public)


#### class `UAnimBoneCompressionCodec_ACLCustom`  
`class UAnimBoneCompressionCodec_ACLCustom : public UAnimBoneCompressionCodec_ACLBase`  
_L13-55_
- reflection: `UCLASS(MinimalAPI, config = Engine, meta = (DisplayName = "Anim Compress ACL Custom"))`
- inherits: `UAnimBoneCompressionCodec_ACLBase`
- desc: Uses the open source Animation Compression Library with custom settings suitable for debugging purposes.
- L20 _private member_ `TEnumAsByte<ACLRotationFormat> RotationFormat;` — `UPROPERTY(EditAnywhere, Category = Clip)` — The rotation format to use.
- L24 _private member_ `TEnumAsByte<ACLVectorFormat> TranslationFormat;` — `UPROPERTY(EditAnywhere, Category = Clip)` — The translation format to use.
- L28 _private member_ `TEnumAsByte<ACLVectorFormat> ScaleFormat;` — `UPROPERTY(EditAnywhere, Category = Clip)` — The scale format to use.
- L32 _private member_ `TArray<TObjectPtr<class USkeletalMesh>> OptimizationTargets;` — `UPROPERTY(EditAnywhere, Category = "ACL Options")` — The skeletal meshes used to estimate the skinning deformation during compression.
- L36 _private member_ `FPerPlatformFloat KeyframeStrippingProportion;` — `UPROPERTY(EditAnywhere, Category = "ACL Destructive Options", meta = (ClampMin = "0", ClampMax = "1"))` — The minimum proportion of keyframes that should be stripped.
- L40 _private member_ `FPerPlatformFloat KeyframeStrippingThreshold;` — `UPROPERTY(EditAnywhere, Category = "ACL Destructive Options", meta = (ClampMin = "0"))` — The error threshold below which to strip keyframes. If a keyframe can be reconstructed with an error below the threshold, it is stripped.
- L45 _private prototype_ `virtual void PopulateDDCKey(const UE::Anim::Compression::FAnimDDCKeyArgs& KeyArgs, FArchive& Ar) override;` — UAnimBoneCompressionCodec implementation
- L48 _private prototype_ `virtual void GetCompressionSettings(const class ITargetPlatform* TargetPlatform, acl::compression_settings& OutSettings) const override;` — UAnimBoneCompressionCodec_ACLBase implementation
- L49 _private function_ `virtual TArray<class USkeletalMesh*> GetOptimizationTargets() const override`
- L53 _private prototype_ `virtual void DecompressPose(FAnimSequenceDecompressionContext& DecompContext, const BoneTrackArray& RotationPairs, const BoneTrackArray& TranslationPairs, const BoneTrackArray& ScalePairs, TArrayView<FTransform>& OutAtoms) const override;` — UAnimBoneCompressionCodec implementation
- L54 _private prototype_ `virtual void DecompressBone(FAnimSequenceDecompressionContext& DecompContext, int32 TrackIndex, FTransform& OutAtom) const override;`

### `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Classes/AnimBoneCompressionCodec_ACLDatabase.h` (Public)


#### struct `FACLDatabaseCompressedAnimData`  
`struct FACLDatabaseCompressedAnimData final : public FACLCompressedAnimDataBase`  
_L18-52_
- inherits: `FACLCompressedAnimDataBase`
- L21 _public member_ `TArrayView<uint8> CompressedByteStream;` — Maps the compressed_tracks instance. Used in cooked build only.
- L24 _public member_ `acl::database_context<UEDefaultDatabaseSettings>* DatabaseContext = nullptr;` — Maps the database context instance. Used in cooked build only.
- L27 _public member_ `const class UAnimBoneCompressionCodec_ACLDatabase* Codec = nullptr;` — The codec instance that owns us.
- L30 _public member_ `uint32 SequenceNameHash = 0;` — The sequence name hash that owns this data.
- L34 _public member_ `TArray<uint8> CompressedClip;` — Holds the compressed_tracks instance for the anim sequence
- L38 _public function_ `const acl::compressed_tracks* GetCompressedTracks() const`
- L48 _public prototype_ `virtual void SerializeCompressedData(UObject* DataOwner, FArchive& Ar) override;`
- L49 _public prototype_ `virtual void Bind(const TArrayView<uint8> BulkData) override;`
- L50 _public prototype_ `virtual int64 GetApproxCompressedSize() const override;`
- L51 _public prototype_ `virtual bool IsValid() const override;`

#### class `UAnimBoneCompressionCodec_ACLDatabase`  
`class UAnimBoneCompressionCodec_ACLDatabase : public UAnimBoneCompressionCodec_ACLBase`  
_L60-93_
- reflection: `UCLASS(MinimalAPI, config = Engine, meta = (DisplayName = "Anim Compress ACL Database"))`
- inherits: `UAnimBoneCompressionCodec_ACLBase`
- desc: Uses the open source Animation Compression Library with default settings and database support. The referenced database can be used to strip the least important keyframes on a per platform basis or they can be streamed in/out on demand through Blueprint or C++.
- L66 _private member_ `TObjectPtr<UAnimationCompressionLibraryDatabase> DatabaseAsset;` — `UPROPERTY(EditAnywhere, Category = "ACL Options")` — The database asset that will hold the compressed animation data.
- L71 _private member_ `TArray<TObjectPtr<class USkeletalMesh>> OptimizationTargets;` — `UPROPERTY(EditAnywhere, Category = "ACL Options")` — The skeletal meshes used to estimate the skinning deformation during compression.
- L75 _private prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;` — UObject
- L76 _private prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L79 _private prototype_ `virtual void PopulateDDCKey(const UE::Anim::Compression::FAnimDDCKeyArgs& KeyArgs, FArchive& Ar) override;` — UAnimBoneCompressionCodec implementation
- L82 _private prototype_ `virtual void PostCompression(const FCompressibleAnimData& CompressibleAnimData, FCompressibleAnimDataResult& OutResult) const override;` — UAnimBoneCompressionCodec_ACLBase implementation
- L83 _private prototype_ `virtual void GetCompressionSettings(const class ITargetPlatform* TargetPlatform, acl::compression_settings& OutSettings) const override;`
- L84 _private function_ `virtual TArray<class USkeletalMesh*> GetOptimizationTargets() const override`
- L88 _private prototype_ `virtual TUniquePtr<ICompressedAnimData> AllocateAnimData() const override;` — UAnimBoneCompressionCodec implementation
- L89 _private prototype_ `virtual void ByteSwapIn(ICompressedAnimData& AnimData, TArrayView<uint8> CompressedData, FMemoryReader& MemoryStream) const override;`
- L90 _private prototype_ `virtual void ByteSwapOut(ICompressedAnimData& AnimData, TArrayView<uint8> CompressedData, FMemoryWriter& MemoryStream) const override;`
- L91 _private prototype_ `virtual void DecompressPose(FAnimSequenceDecompressionContext& DecompContext, const BoneTrackArray& RotationPairs, const BoneTrackArray& TranslationPairs, const BoneTrackArray& ScalePairs, TArrayView<FTransform>& OutAtoms) const override;`
- L92 _private prototype_ `virtual void DecompressBone(FAnimSequenceDecompressionContext& DecompContext, int32 TrackIndex, FTransform& OutAtom) const override;`

### `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Classes/AnimBoneCompressionCodec_ACLSafe.h` (Public)


#### class `UAnimBoneCompressionCodec_ACLSafe`  
`class UAnimBoneCompressionCodec_ACLSafe : public UAnimBoneCompressionCodec_ACLBase`  
_L13-28_
- reflection: `UCLASS(MinimalAPI, config = Engine, meta = (DisplayName = "Anim Compress ACL Safe"))`
- inherits: `UAnimBoneCompressionCodec_ACLBase`
- desc: Uses the open source Animation Compression Library with the safest and least destructive settings suitable when animations must be preserved with near raw fidelity.
- L19 _private prototype_ `virtual void PopulateDDCKey(const UE::Anim::Compression::FAnimDDCKeyArgs& KeyArgs, FArchive& Ar) override;` — UAnimBoneCompressionCodec implementation
- L22 _private prototype_ `virtual void GetCompressionSettings(const class ITargetPlatform* TargetPlatform, acl::compression_settings& OutSettings) const override;` — UAnimBoneCompressionCodec_ACLBase implementation
- L26 _private prototype_ `virtual void DecompressPose(FAnimSequenceDecompressionContext& DecompContext, const BoneTrackArray& RotationPairs, const BoneTrackArray& TranslationPairs, const BoneTrackArray& ScalePairs, TArrayView<FTransform>& OutAtoms) const override;` — UAnimBoneCompressionCodec implementation
- L27 _private prototype_ `virtual void DecompressBone(FAnimSequenceDecompressionContext& DecompContext, int32 TrackIndex, FTransform& OutAtom) const override;`

### `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Classes/AnimCurveCompressionCodec_ACL.h` (Public)


#### class `UAnimCurveCompressionCodec_ACL`  
`class UAnimCurveCompressionCodec_ACL : public UAnimCurveCompressionCodec`  
_L15-43_
- reflection: `UCLASS(MinimalAPI, config = Engine, meta = (DisplayName = "ACL Curves"))`
- inherits: `UAnimCurveCompressionCodec`
- desc: Uses the open source Animation Compression Library with default settings suitable for general purpose animation curves.
- L22 _private member_ `float CurvePrecision;` — `UPROPERTY(EditAnywhere, Category = "ACL Options", meta = (ClampMin = "0"))` — The curve precision to target when compressing the animation curves.
- L26 _private member_ `float MorphTargetPositionPrecision;` — `UPROPERTY(EditAnywhere, Category = "ACL Options", meta = (ClampMin = "0", EditCondition = "MorphTargetSource != nullptr"))` — The mesh deformation precision to target when compressing morph target animation curves.
- L30 _private member_ `TObjectPtr<class USkeletalMesh> MorphTargetSource;` — `UPROPERTY(EditAnywhere, Category = "ACL Options")` — The skeletal mesh used to estimate the morph target deformation during compression.
- L34 _private prototype_ `virtual void PopulateDDCKey(FArchive& Ar) override;` — UAnimCurveCompressionCodec implementation
- L35 _private prototype_ `virtual bool Compress(const FCompressibleAnimData& AnimSeq, FAnimCurveCompressionResult& OutResult) override;`
- L36 _private prototype_ `virtual int64 EstimateCompressionMemoryUsage(const UAnimSequence& AnimSequence) const override;`
- L40 _private prototype_ `virtual bool ValidateCompressedData(UObject* DataOwner, const FCompressedAnimSequence& AnimSeq) const override;` — UAnimCurveCompressionCodec implementation
- L41 _private prototype_ `virtual void DecompressCurves(const FCompressedAnimSequence& AnimSeq, FBlendedCurve& Curves, float CurrentTime) const override;`
- L42 _private prototype_ `virtual float DecompressCurve(const FCompressedAnimSequence& AnimSeq, FName CurveName, float CurrentTime) const override;`

### `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Classes/AnimationCompressionLibraryDatabase.h` (Public)


#### enum `ACLVisualFidelity`  
`enum class ACLVisualFidelity : uint8`  
_L23-28_
- reflection: `UENUM()`
- desc: An enum to represent the ACL visual fidelity level.
- L25 _public enumerator_ `Highest UMETA(DisplayName = "Highest")`
- L26 _public enumerator_ `Medium UMETA(DisplayName = "Medium")`
- L27 _public enumerator_ `Lowest UMETA(DisplayName = "Lowest")`

#### enum `ACLVisualFidelityChangeResult`  
`enum class ACLVisualFidelityChangeResult : uint8`  
_L32-37_
- reflection: `UENUM(BlueprintType)`
- desc: An enum to represent the result of latent visual fidelity change requests.
- L34 _public enumerator_ `Dispatched`
- L35 _public enumerator_ `Completed`
- L36 _public enumerator_ `Failed`

#### struct `FFidelityChangeRequest`  
`struct FFidelityChangeRequest`  
_L40-47_
- desc: Represents a pending visual fidelity change request
- L42 _public member_ `ACLVisualFidelityChangeResult* Result;` — Optional, present when triggered from a blueprint
- L44 _public member_ `uint32 RequestID;`
- L45 _public member_ `ACLVisualFidelity Fidelity;`
- L46 _public member_ `bool bIsInProgress;`

#### class `UAnimationCompressionLibraryDatabase`  
`class UAnimationCompressionLibraryDatabase : public UObject`  
_L51-211_
- reflection: `UCLASS(MinimalAPI, config = Engine, meta = (DisplayName = "ACL Database"))`
- inherits: `UObject`
- desc: An ACL database object references several UAnimSequence instances that it contains.
- L58 _private member_ `TArray<uint8> CookedCompressedBytes;` — `UPROPERTY()` — The raw binary data for our compressed database and anim sequences. Present only in cooked builds.
- L62 _private member_ `TArray<uint64> CookedAnimSequenceMappings;` — `UPROPERTY()` — Stores a mapping for each anim sequence, where its compressed data lives in our compressed buffer. Each 64 bit value is split into 32 bits: (Hash << 32) | Offset. Present only in cooked builds.
- L65 _private member_ `FByteBulkData CookedBulkData;` — Bulk data that we'll stream. Present only in cooked builds.
- L68 _private member_ `acl::database_context<UEDefaultDatabaseSettings> DatabaseContext;` — The database decompression context object. Bound to the compressed database instance.
- L71 _private member_ `TUniquePtr<acl::database_streamer> DatabaseStreamer;` — The streamer instance used by the database context. Only used in cooked builds.
- L74 _private member_ `ACLVisualFidelity CurrentVisualFidelity;` — The current visual fidelity level.
- L77 _private member_ `uint32 NextFidelityChangeRequestID;` — The next fidelity change request ID. Always increments.
- L80 _private member_ `TArray<FFidelityChangeRequest> FidelityChangeRequests;` — A queue of visual fidelity change requests.
- L83 _private member_ `FTSTicker::FDelegateHandle FidelityUpdateTickerHandle;` — The handle to the fidelity update ticket.
- L88 _private member_ `float HighestImportanceProportion;` — `UPROPERTY(VisibleAnywhere, Category = "Database")` — What percentage of the key frames should remain in the anim sequences.
- L92 _private member_ `float MediumImportanceProportion;` — `UPROPERTY(EditAnywhere, Category = "Database", meta = (ClampMin = "0", ClampMax = "1"))` — What percentage of the key frames should be moved to the database. Medium importance key frames are moved second.
- L96 _private member_ `float LowestImportanceProportion;` — `UPROPERTY(EditAnywhere, Category = "Database", meta = (ClampMin = "0", ClampMax = "1"))` — What percentage of the key frames should be moved to the database. Least important key frames are moved first.
- L100 _private member_ `FPerPlatformBool StripLowestImportanceTier;` — `UPROPERTY(EditAnywhere, Category = "Database")` — Whether or not to strip the lowest importance tier entirely from disk. Stripping the lowest tier means that the visual fidelity of Highest and Medium are equivalent.
- L105 _private member_ `uint32 MaxStreamRequestSizeKB;` — `UPROPERTY(EditAnywhere, Category = "Database", meta = (ClampMin = "4", ClampMax = "1048576"))` — The maximum size in KiloBytes of streaming requests. Setting this to 0 will force tiers to load in a single request regardless of their size.
- L109 _private member_ `ACLVisualFidelity DefaultVisualFidelity;` — `UPROPERTY(EditAnywhere, Category = "Database")` — The default level of quality to set when the database loads in-game. By default, nothing is streamed in.
- L114 _private member_ `ACLVisualFidelity PreviewVisualFidelity;` — `UPROPERTY(EditAnywhere, Transient, Category = "Debug")` — The level of quality to preview with the database when decompressing in the editor.
- L117 _private member_ `TArray<uint8> PreviewCompressedBytes;` — Editor only, transient, preview version of 'CookedCompressedBytes'.
- L120 _private member_ `TArray<uint64> PreviewAnimSequenceMappings;` — Editor only, transient, preview version of 'CookedAnimSequenceMappings'.
- L123 _private member_ `TArray<uint8> PreviewBulkData;` — Editor only, transient, preview version of 'CookedBulkData'.
- L126 _private member_ `TUniquePtr<acl::database_streamer> PreviewDatabaseStreamer;` — Editor only, transient, preview version of 'DatabaseStreamer'.
- L130 _private member_ `TArray<TObjectPtr<class UAnimSequence>> AnimSequences;` — `UPROPERTY(VisibleAnywhere, Category = "Metadata")` — The anim sequences contained within the database. Built manually from the asset UI, content browser, or with a commandlet.
- L134 _private member_ `int32 NumAnimSequences;` — `UPROPERTY(VisibleAnywhere, Category = "Stats")` — The total num of Animation Sequences in this database.
- L138 _private member_ `int32 AnimSequencesOldSizeKB;` — `UPROPERTY(VisibleAnywhere, Category = "Stats")` — The total size of all Animation Sequences if the database were not used.
- L142 _private member_ `int32 AnimSequencesNewSizeKB;` — `UPROPERTY(VisibleAnywhere, Category = "Stats")` — The total size of all Animation Sequences with the database in use.
- L146 _private member_ `int32 DatabaseSizeKB;` — `UPROPERTY(VisibleAnywhere, Category = "Stats")` — The total size of the database.
- L150 _private member_ `int32 DatabaseMetadataSizeKB;` — `UPROPERTY(VisibleAnywhere, Category = "Stats")` — The size of the database metadata.
- L154 _private member_ `int32 MediumImportanceSizeKB;` — `UPROPERTY(VisibleAnywhere, Category = "Stats")` — The size of the database medium importance streaming tier.
- L158 _private member_ `int32 LowImportanceSizeSizeKB;` — `UPROPERTY(VisibleAnywhere, Category = "Stats")` — The size of the database low importance streaming tier before any stripping.
- L163 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject implementation
- L164 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L167 _public prototype_ `bool UpdateReferencingAnimSequenceList();` — Updates the internal list of anim sequences that reference this database. Returns whether or not anything changed.
- L172 _public prototype_ `virtual void BeginDestroy() override;` — UObject implementation
- L173 _public prototype_ `virtual void PostLoad() override;`
- L174 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L177 _public prototype_ `void SetVisualFidelity(ACLVisualFidelity VisualFidelity);` — Initiate a latent database change in visual fidelity by streaming in/out as necessary.
- L180 _public function_ `ACLVisualFidelity GetVisualFidelity() const` — Retrieves the current visual fidelity level.
- L184 _public prototype_ `static void SetVisualFidelity(UObject* WorldContextObject, FLatentActionInfo LatentInfo, UAnimationCompressionLibraryDatabase* DatabaseAsset, ACLVisualFidelityChangeResult& Result, ACLVisualFidelity VisualFidelity = ACLVisualFidelity::Highest);` — `UFUNCTION(BlueprintCallable, Category = "Animation|ACL", meta = (DisplayName = "Set Database Visual Fidelity", WorldContext="WorldContextObject", Latent, LatentInfo = "LatentInfo", ExpandEnumAsExecs="Result"))` — Initiate a latent database change in quality by streaming in/out as necessary.
- L187 _public prototype_ `static ACLVisualFidelity GetVisualFidelity(UAnimationCompressionLibraryDatabase* DatabaseAsset);` — `UFUNCTION(BlueprintCallable, Category = "Animation|ACL", meta = (DisplayName = "Get Database Visual Fidelity"))`
- L192 _private prototype_ `void BuildDatabase(TArray<uint8>& OutCompressedBytes, TArray<uint64>& OutAnimSequenceMappings, TArray<uint8>& OutBulkData, bool bStripLowestTier = false);` — Builds our database and its related mappings as well as the new anim sequence data.
- L195 _private prototype_ `void UpdatePreviewState(bool bBuildDatabase);` — Updates the internal preview state and optionally builds the database when requested.
- L199 _private prototype_ `uint32 SetVisualFidelityImpl(ACLVisualFidelity VisualFidelity, ACLVisualFidelityChangeResult* OutResult);` — Shared implementation between C++ and blueprint interfaces. Returns the request ID necessary to abort or ~0 if no change is required.
- L202 _private prototype_ `void CancelVisualFidelityRequestImpl(uint32 RequestID);` — Cancels an ongoing visual fidelity request. Only supported if the request hasn't completed. Will not update the ACLVisualFidelityChangeResult of the request.
- L205 _private prototype_ `bool UpdateVisualFidelityTicker(float DeltaTime);` — Core ticker update function to update our visual fidelity state.

### `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Private/ACLDecompressionImpl.h` (Private)


#### struct `FACLTransform`  
`struct FACLTransform final : public FTransform`  
_L25-61_
- inherits: `FTransform`
- desc: The FTransform type does not support setting the members directly from vector types so we derive from it and expose that functionality.
- L29 _public function_ `FORCEINLINE_DEBUGGABLE void RTM_SIMD_CALL SetRotationRaw(rtm::quatf_arg0 Rotation_)`
- L40 _public function_ `FORCEINLINE_DEBUGGABLE void RTM_SIMD_CALL SetTranslationRaw(rtm::vector4f_arg0 Translation_)`
- L51 _public function_ `FORCEINLINE_DEBUGGABLE void RTM_SIMD_CALL SetScale3DRaw(rtm::vector4f_arg0 Scale_)`

#### struct `FAtomIndices`  
`struct FAtomIndices`  
_L64-69_
- desc: These 3 indices map into the output Atom array.
- L66 _public member_ `uint16 Rotation;`
- L67 _public member_ `uint16 Translation;`
- L68 _public member_ `uint16 Scale;`

#### struct `FUEOutputWriter`  
`template<bool bUseBindPose> struct FUEOutputWriter final : public acl::track_writer`  
_L75-162_
- inherits: `acl::track_writer`
- desc: Output pose writer that can selectively skip certain tracks.
- L80 _public member_ `const FTransform* RefPoses;` — The bind pose
- L83 _public member_ `const FTrackToSkeletonMap* TrackToBoneMapping;` — Maps track indices to bone indices
- L86 _public member_ `const FAtomIndices* TrackToAtomsMap;` — The track to output transform index map
- L89 _public member_ `FACLTransform* Atoms;` — The output transforms we write
- L91 _public function_ `FUEOutputWriter(const FAtomIndices* TrackToAtomsMap_, TArrayView<FTransform>& Atoms_) : RefPoses(nullptr) , TrackToBoneMapping(nullptr) , TrackToAtomsMap(TrackToAtomsMap_) , Atoms(static_cast<FACLTransform*>(Atoms_.GetData()))`
- L98 _public function_ `FUEOutputWriter(const TArrayView<const FTransform>& RefPoses_, const TArrayView<const FTrackToSkeletonMap>& TrackToSkeletonMap, const FAtomIndices* TrackToAtomsMap_, TArrayView<FTransform>& Atoms_) : RefPoses(RefPoses_.GetData()) , TrackToBoneMapping(TrackToSkeletonMap.GetData()) , TrackToAtomsMap(TrackToAtomsMap_) , Atoms(static_cast<FACLTransform*>(Atoms_.GetData()))`
- L109 _public function_ `FORCEINLINE_DEBUGGABLE bool skip_track_rotation(uint32_t BoneIndex) const` — Override the OutputWriter behavior If we use the bind pose, each default sub-track will grab the bind pose value Otherwise we output the constant default values
- L110 _public function_ `FORCEINLINE_DEBUGGABLE bool skip_track_translation(uint32_t BoneIndex) const`
- L111 _public function_ `FORCEINLINE_DEBUGGABLE bool skip_track_scale(uint32_t BoneIndex) const`
- L113 _public function_ `static constexpr acl::default_sub_track_mode get_default_rotation_mode()`
- L114 _public function_ `static constexpr acl::default_sub_track_mode get_default_translation_mode()`
- L115 _public function_ `static constexpr acl::default_sub_track_mode get_default_scale_mode()`
- L118 _public function_ `FORCEINLINE_DEBUGGABLE rtm::quatf RTM_SIMD_CALL get_variable_default_rotation(uint32_t TrackIndex) const` — TODO: There is a performance impact here because the ref pose might use doubles on PC
- L123 _public function_ `FORCEINLINE_DEBUGGABLE rtm::vector4f RTM_SIMD_CALL get_variable_default_translation(uint32_t TrackIndex) const`
- L128 _public function_ `FORCEINLINE_DEBUGGABLE rtm::vector4f RTM_SIMD_CALL get_variable_default_scale(uint32_t TrackIndex) const`
- L135 _public function_ `FORCEINLINE_DEBUGGABLE void RTM_SIMD_CALL write_rotation(uint32_t BoneIndex, rtm::quatf_arg0 Rotation)` — Called by the decoder to write out a quaternion rotation value for a specified bone index
- L145 _public function_ `FORCEINLINE_DEBUGGABLE void RTM_SIMD_CALL write_translation(uint32_t BoneIndex, rtm::vector4f_arg0 Translation)` — Called by the decoder to write out a translation value for a specified bone index
- L155 _public function_ `FORCEINLINE_DEBUGGABLE void RTM_SIMD_CALL write_scale(uint32_t BoneIndex, rtm::vector4f_arg0 Scale)` — Called by the decoder to write out a scale value for a specified bone index

#### struct `FUEOutputWriterSoA`  
`template<bool bUseBindPose> struct FUEOutputWriterSoA final : public acl::track_writer`  
_L168-271_
- inherits: `acl::track_writer`
- desc: Output pose writer that can selectively skip certain tracks.
- L173 _public member_ `const FTransform* RefPoses;` — The bind pose
- L176 _public member_ `const FTrackToSkeletonMap* TrackToBoneMapping;` — Maps track indices to bone indices
- L179 _public member_ `const FAtomIndices* TrackToAtomsMap;` — The track to output transform index map
- L182 _public member_ `FQuat* Rotations;` — The output transforms we write
- L183 _public member_ `FVector* Translations;`
- L184 _public member_ `FVector* Scales3D;`
- L186 _public function_ `FUEOutputWriterSoA( const FAtomIndices* InTrackToAtomsMap, TArrayView<FQuat>& InRotations, TArrayView<FVector>& InTranslations, TArrayView<FVector>& InScales3D) : RefPoses(nullptr) , TrackToBoneMapping(nullptr) , TrackToAtomsMap(InTrackToAtomsMap) , Rotations(InRotations.GetData()) , Translations(InTranslations.GetData()) , Scales3D(InScales3D.GetData())`
- L199 _public function_ `FUEOutputWriterSoA( const TArrayView<const FTransform>& InRefPoses, const TArrayView<const FTrackToSkeletonMap>& TrackToSkeletonMap, const FAtomIndices* InTrackToAtomsMap, TArrayView<FQuat>& InRotations, TArrayView<FVector>& InTranslations, TArrayView<FVector>& InScales3D) : RefPoses(InRefPoses.GetData()) , TrackToBoneMapping(TrackToSkeletonMap.GetData()) , TrackToAtomsMap(InTrackToAtomsMap) , Rotations(InRotations.GetData()) , Translations(InTranslations.GetData()) , Scales3D(InScales3D.GetData())`
- L218 _public function_ `FORCEINLINE_DEBUGGABLE bool skip_track_rotation(uint32_t BoneIndex) const` — Override the OutputWriter behavior If we use the bind pose, each default sub-track will grab the bind pose value Otherwise we output the constant default values
- L219 _public function_ `FORCEINLINE_DEBUGGABLE bool skip_track_translation(uint32_t BoneIndex) const`
- L220 _public function_ `FORCEINLINE_DEBUGGABLE bool skip_track_scale(uint32_t BoneIndex) const`
- L222 _public function_ `static constexpr acl::default_sub_track_mode get_default_rotation_mode()`
- L223 _public function_ `static constexpr acl::default_sub_track_mode get_default_translation_mode()`
- L224 _public function_ `static constexpr acl::default_sub_track_mode get_default_scale_mode()`
- L227 _public function_ `FORCEINLINE_DEBUGGABLE rtm::quatf RTM_SIMD_CALL get_variable_default_rotation(uint32_t TrackIndex) const` — TODO: There is a performance impact here because the ref pose might use doubles on PC
- L232 _public function_ `FORCEINLINE_DEBUGGABLE rtm::vector4f RTM_SIMD_CALL get_variable_default_translation(uint32_t TrackIndex) const`
- L237 _public function_ `FORCEINLINE_DEBUGGABLE rtm::vector4f RTM_SIMD_CALL get_variable_default_scale(uint32_t TrackIndex) const`
- L244 _public function_ `FORCEINLINE_DEBUGGABLE void RTM_SIMD_CALL write_rotation(uint32_t BoneIndex, rtm::quatf_arg0 Rotation)` — Called by the decoder to write out a quaternion rotation value for a specified bone index
- L254 _public function_ `FORCEINLINE_DEBUGGABLE void RTM_SIMD_CALL write_translation(uint32_t BoneIndex, rtm::vector4f_arg0 Translation)` — Called by the decoder to write out a translation value for a specified bone index
- L264 _public function_ `FORCEINLINE_DEBUGGABLE void RTM_SIMD_CALL write_scale(uint32_t BoneIndex, rtm::vector4f_arg0 Scale)` — Called by the decoder to write out a scale value for a specified bone index

#### struct `UEOutputTrackWriter`  
`template<bool bUseBindPose> struct UEOutputTrackWriter final : public acl::track_writer`  
_L277-350_
- inherits: `acl::track_writer`
- desc: Output track writer for a single track.
- L280 _public member_ `const FTransform* RefPoses;` — The bind pose
- L283 _public member_ `const FTrackToSkeletonMap* TrackToBoneMapping;` — Maps track indices to bone indices
- L286 _public member_ `FACLTransform& Atom;` — Raw reference for performance reasons, caller is responsible for ensuring data is valid
- L288 _public function_ `explicit UEOutputTrackWriter(FTransform& Atom_) : RefPoses(nullptr) , TrackToBoneMapping(nullptr) , Atom(static_cast<FACLTransform&>(Atom_))`
- L294 _public function_ `UEOutputTrackWriter(const TArrayView<const FTransform>& RefPoses_, const TArrayView<const FTrackToSkeletonMap>& TrackToSkeletonMap, FTransform& Atom_) : RefPoses(RefPoses_.GetData()) , TrackToBoneMapping(TrackToSkeletonMap.GetData()) , Atom(static_cast<FACLTransform&>(Atom_))`
- L310 _public function_ `static constexpr acl::default_sub_track_mode get_default_rotation_mode()` — Override the OutputWriter behavior If we use the bind pose, each default sub-track will grab the bind pose value Otherwise we output the constant default values
- L311 _public function_ `static constexpr acl::default_sub_track_mode get_default_translation_mode()`
- L312 _public function_ `static constexpr acl::default_sub_track_mode get_default_scale_mode()`
- L315 _public function_ `FORCEINLINE_DEBUGGABLE rtm::quatf RTM_SIMD_CALL get_variable_default_rotation(uint32_t TrackIndex) const` — TODO: There is a performance impact here because the ref pose might use doubles on PC
- L320 _public function_ `FORCEINLINE_DEBUGGABLE rtm::vector4f RTM_SIMD_CALL get_variable_default_translation(uint32_t TrackIndex) const`
- L325 _public function_ `FORCEINLINE_DEBUGGABLE rtm::vector4f RTM_SIMD_CALL get_variable_default_scale(uint32_t TrackIndex) const`
- L332 _public function_ `FORCEINLINE_DEBUGGABLE void RTM_SIMD_CALL write_rotation(uint32_t BoneIndex, rtm::quatf_arg0 Rotation)` — Called by the decoder to write out a quaternion rotation value for a specified bone index
- L339 _public function_ `FORCEINLINE_DEBUGGABLE void RTM_SIMD_CALL write_translation(uint32_t BoneIndex, rtm::vector4f_arg0 Translation)` — Called by the decoder to write out a translation value for a specified bone index
- L346 _public function_ `FORCEINLINE_DEBUGGABLE void RTM_SIMD_CALL write_scale(uint32_t BoneIndex, rtm::vector4f_arg0 Scale)` — Called by the decoder to write out a scale value for a specified bone index

#### Free symbols / members of external scopes

- L19 _function_ `constexpr acl::sample_rounding_policy get_rounding_policy(EAnimInterpolationType InterpType)`
- L353 _function_ `template<class ACLContextType> FORCEINLINE_DEBUGGABLE void DecompressBone(FAnimSequenceDecompressionContext& DecompContext, ACLContextType& ACLContext, int32 TrackIndex, FTransform& OutAtom)`
- L388 _function_ `template<class ACLContextType> FORCEINLINE_DEBUGGABLE void DecompressPose(FAnimSequenceDecompressionContext& DecompContext, ACLContextType& ACLContext, const BoneTrackArray& RotationPairs, const BoneTrackArray& TranslationPairs, const BoneTrackArray& ScalePairs, TArrayView<FTransform>& OutAtoms)`
- L496 _function_ `template<class ACLContextType> FORCEINLINE_DEBUGGABLE void DecompressPose( const FAnimSequenceDecompressionContext& DecompContext, ACLContextType& ACLContext, const UE::Anim::FAnimPoseDecompressionData& DecompressionData)`

### `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Private/EditorDatabaseMonitor.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace EditorDatabaseMonitor`
- L15 _prototype_ `void RegisterMonitor();` (scope `EditorDatabaseMonitor`)
- L16 _prototype_ `void UnregisterMonitor();` (scope `EditorDatabaseMonitor`)
- L18 _prototype_ `void MarkDirty(UAnimationCompressionLibraryDatabase* Database);` (scope `EditorDatabaseMonitor`)

### `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Private/UEDatabasePreviewStreamer.h` (Private)


#### class `UEDatabasePreviewStreamer`  
`class UEDatabasePreviewStreamer final : public acl::database_streamer`  
_L19-60_
- inherits: `acl::database_streamer`
- desc: A simple UE preview streamer. Everything is assumed to be in memory and no real streaming is done.
- L22 _public function_ `UEDatabasePreviewStreamer(const acl::compressed_database& CompressedDatabase, const TArray<uint8>& BulkData_) : database_streamer(Requests, acl::k_num_database_tiers)`
- L32 _public function_ `virtual bool is_initialized() const override`
- L34 _public function_ `virtual const uint8_t* get_bulk_data(acl::quality_tier Tier) const override`
- L41 _public function_ `virtual void stream_in(uint32_t Offset, uint32_t Size, bool CanAllocateBulkData, acl::quality_tier Tier, acl::streaming_request_id RequestID) override`
- L47 _public function_ `virtual void stream_out(uint32_t Offset, uint32_t Size, bool CanDeallocateBulkData, acl::quality_tier Tier, acl::streaming_request_id RequestID) override`
- L54 _private prototype_ `UEDatabasePreviewStreamer(const UEDatabasePreviewStreamer&) = delete;`
- L55 _private prototype_ `UEDatabasePreviewStreamer& operator=(const UEDatabasePreviewStreamer&) = delete;`
- L57 _private member_ `const uint8* BulkData[acl::k_num_database_tiers];`
- L59 _private member_ `acl::streaming_request Requests[acl::k_num_database_tiers];` — One request per tier is enough

### `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Private/UEDatabaseStreamer.h` (Private)


#### class `UEDatabaseStreamer`  
`class UEDatabaseStreamer final : public acl::database_streamer`  
_L22-189_
- inherits: `acl::database_streamer`
- desc: A simple async UE streamer. Memory is allocated on the first stream in request and deallocated on the last stream out request.
- L25 _public function_ `UEDatabaseStreamer(const acl::compressed_database& CompressedDatabase, FByteBulkData& StreamableBulkData_) : database_streamer(Requests, acl::k_num_database_tiers) , StreamableBulkData(StreamableBulkData_) , PendingIORequest(nullptr)`
- L48 _public function_ `virtual ~UEDatabaseStreamer()`
- L61 _public function_ `virtual bool is_initialized() const override`
- L63 _public function_ `virtual const uint8_t* get_bulk_data(acl::quality_tier Tier) const override`
- L70 _public function_ `virtual void stream_in(uint32_t Offset, uint32_t Size, bool CanAllocateBulkData, acl::quality_tier Tier, acl::streaming_request_id RequestID) override`
- L127 _public function_ `virtual void stream_out(uint32_t Offset, uint32_t Size, bool CanDeallocateBulkData, acl::quality_tier Tier, acl::streaming_request_id RequestID) override`
- L163 _public function_ `void WaitForStreamingToComplete()`
- L174 _private prototype_ `UEDatabaseStreamer(const UEDatabaseStreamer&) = delete;`
- L175 _private prototype_ `UEDatabaseStreamer& operator=(const UEDatabaseStreamer&) = delete;`
- L177 _private member_ `FByteBulkData& StreamableBulkData;`
- L178 _private member_ `uint8* BulkData[acl::k_num_database_tiers];`
- L179 _private member_ `uint32 BulkDataSize[acl::k_num_database_tiers];`
- L181 _private member_ `IBulkDataIORequest* PendingIORequest;`
- L183 _private member_ `acl::streaming_request Requests[acl::k_num_database_tiers];` — One request per tier is enough
- L186 _private member_ `FPlatformMemory::FPlatformVirtualMemoryBlock StreamedBulkDataBlock;`
- L187 _private member_ `bool bIsBulkDataCommited;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define WITH_VMEM_MANAGEMENT 0` — UE 4.25 doesn't expose its virtual memory management, see FPlatformMemory::FPlatformVirtualMemoryBlock
- L84 _function_ `` (scope `UEDatabaseStreamer::stream_in`)

### `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Public/ACLImpl.h` (Public)


#### class `ACLAllocator`  
`class ACLAllocator final : public acl::iallocator`  
_L98-110_
- inherits: `acl::iallocator`
- desc: The ACL allocator implementation simply forwards to the default heap allocator.
- L101 _public function_ `virtual void* allocate(size_t size, size_t alignment = acl::iallocator::k_default_alignment)`
- L106 _public function_ `virtual void deallocate(void* ptr, size_t size)`

#### struct `UEDefaultDecompressionSettings`  
`struct UEDefaultDecompressionSettings : public acl::default_transform_decompression_settings`  
_L133-146_
- inherits: `acl::default_transform_decompression_settings`
- desc: The decompression settings used by ACL
- L136 _public function_ `static constexpr acl::compressed_tracks_version16 version_supported()` — Only support our latest version

#### struct `UEDebugDecompressionSettings`  
`struct UEDebugDecompressionSettings : public acl::debug_transform_decompression_settings`  
_L148-152_
- inherits: `acl::debug_transform_decompression_settings`
- L151 _public function_ `static constexpr acl::compressed_tracks_version16 version_supported()` — Only support our latest version

#### struct `UESafeDecompressionSettings`  
`struct UESafeDecompressionSettings final : public UEDefaultDecompressionSettings`  
_L157-161_
- inherits: `UEDefaultDecompressionSettings`
- L159 _public function_ `static constexpr bool is_rotation_format_supported(acl::rotation_format8 format)`
- L160 _public function_ `static constexpr acl::rotation_format8 get_rotation_format(acl::rotation_format8 )`

#### struct `UEDefaultDatabaseSettings`  
`struct UEDefaultDatabaseSettings final : public acl::default_database_settings`  
_L163-167_
- inherits: `acl::default_database_settings`
- L166 _public function_ `static constexpr acl::compressed_tracks_version16 version_supported()` — Only support our latest version

#### struct `UEDefaultDBDecompressionSettings`  
`struct UEDefaultDBDecompressionSettings final : public UEDefaultDecompressionSettings`  
_L169-172_
- inherits: `UEDefaultDecompressionSettings`
- L171 _public typedef_ `using database_settings_type = UEDefaultDatabaseSettings;`

#### struct `UEDebugDBDecompressionSettings`  
`struct UEDebugDBDecompressionSettings final : public UEDebugDecompressionSettings`  
_L176-179_
- inherits: `UEDebugDecompressionSettings`
- L178 _public typedef_ `using database_settings_type = UEDebugDatabaseSettings;`

#### enum `ACLRotationFormat`  
`enum ACLRotationFormat : int`  
_L184-189_
- reflection: `UENUM()`
- desc: An enum for ACL rotation formats.
- L186 _public enumerator_ `ACLRF_Quat_128 UMETA(DisplayName = "Quat Full Bit Rate")`
- L187 _public enumerator_ `ACLRF_QuatDropW_96 UMETA(DisplayName = "Quat Drop W Full Bit Rate")`
- L188 _public enumerator_ `ACLRF_QuatDropW_Variable UMETA(DisplayName = "Quat Drop W Variable Bit Rate")`

#### enum `ACLVectorFormat`  
`enum ACLVectorFormat : int`  
_L193-197_
- reflection: `UENUM()`
- desc: An enum for ACL Vector3 formats.
- L195 _public enumerator_ `ACLVF_Vector3_96 UMETA(DisplayName = "Vector3 Full Bit Rate")`
- L196 _public enumerator_ `ACLVF_Vector3_Variable UMETA(DisplayName = "Vector3 Variable Bit Rate")`

#### enum `ACLCompressionLevel`  
`enum ACLCompressionLevel : int`  
_L201-209_
- reflection: `UENUM()`
- desc: An enum for ACL compression levels.
- L203 _public enumerator_ `ACLCL_Lowest UMETA(DisplayName = "Lowest")`
- L204 _public enumerator_ `ACLCL_Low UMETA(DisplayName = "Low")`
- L205 _public enumerator_ `ACLCL_Medium UMETA(DisplayName = "Medium")`
- L206 _public enumerator_ `ACLCL_High UMETA(DisplayName = "High")`
- L207 _public enumerator_ `ACLCL_Highest UMETA(DisplayName = "Highest")`
- L208 _public enumerator_ `ACLCL_Automatic UMETA(DisplayName = "Automatic")`

#### enum `ACLPhantomTrackMode`  
`enum class ACLPhantomTrackMode : uint8`  
_L222-232_
- reflection: `UENUM()`
- desc: An enum to control how to handle UE phantom tracks. A phantom tracks are present in an animation sequence but aren't mapped to skeleton bones. As such, they cannot be queried by the engine except manually through DecompressBone. It should generally be safe to Strip them but we default to Ignore. Re-importing the animation sequence should clean up any such stale data.
- L225 _public enumerator_ `Ignore` — Ignore phantom tracks and compress them anyway (same as UE codecs).
- L228 _public enumerator_ `Strip` — Strip the phantom track to save memory by collapsing them to the identity transform while maintaining the track ordering.
- L231 _public enumerator_ `Warn` — We ignore the phantom tracks and output a warning to the log.

#### Free symbols / members of external scopes

- L18 _macro_ `#define ACL_ON_ASSERT_CUSTOM`
- L21 _macro_ `#define RTM_ASSERT_STRING_FORMAT_SPECIFIER "%hs"` — Override the string format specifier for UE
- L22 _macro_ `#define SJSON_ASSERT_STRING_FORMAT_SPECIFIER "%hs"`
- L23 _macro_ `#define ACL_ASSERT_STRING_FORMAT_SPECIFIER "%hs"`
- L25 _macro_ `#define ACL_ASSERT(expression, format, ...) checkf(expression, TEXT(format), ##__VA_ARGS__)`
- L112 _externvar_ `extern ACLAllocator ACLAllocatorImpl;`
- L115 _function_ `inline FQuat RTM_SIMD_CALL UEQuatCast(const FQuat4f& Input)` — RTM <-> UE conversion utilities and aliases.
- L116 _function_ `inline FVector RTM_SIMD_CALL UEVector3Cast(const FVector3f& Input)`
- L117 _function_ `inline FVector RTM_SIMD_CALL UEVector3Cast(const FVector3d& Input)`
- L119 _function_ `inline rtm::vector4f RTM_SIMD_CALL UEVector3ToACL(const FVector3f& Input)`
- L120 _function_ `inline rtm::vector4f RTM_SIMD_CALL UEVector3ToACL(const FVector& Input)`
- L121 _function_ `inline FVector3f RTM_SIMD_CALL ACLVector3ToUE(rtm::vector4f_arg0 Input)`
- L123 _function_ `inline rtm::quatf RTM_SIMD_CALL UEQuatToACL(const FQuat4f& Input)`
- L124 _function_ `inline rtm::quatf RTM_SIMD_CALL UEQuatToACL(const FQuat& Input)`
- L125 _function_ `inline FQuat4f RTM_SIMD_CALL ACLQuatToUE(rtm::quatf_arg0 Input)`
- L127 _function_ `inline FTransform RTM_SIMD_CALL ACLTransformToUE(rtm::qvvf_arg0 Input)`
- L129 _typedef_ `using FRawAnimTrackQuat = FQuat4f;`
- L130 _typedef_ `using FRawAnimTrackVector3 = FVector3f;`
- L155 _typedef_ `using UECustomDecompressionSettings = UEDebugDecompressionSettings;` — Same as debug settings for now since everything is allowed
- L174 _typedef_ `using UEDebugDatabaseSettings = acl::debug_database_settings;`
- L242 _prototype_ `acl::rotation_format8 GetRotationFormat(ACLRotationFormat Format);`
- L243 _prototype_ `acl::vector_format8 GetVectorFormat(ACLVectorFormat Format);`
- L244 _prototype_ `acl::compression_level8 GetCompressionLevel(ACLCompressionLevel Level);`
- L246 _prototype_ `acl::track_array_qvvf BuildACLTransformTrackArray(ACLAllocator& AllocatorImpl, const FCompressibleAnimData& CompressibleAnimData, float DefaultVirtualVertexDistance, float SafeVirtualVertexDistance, bool bBuildAdditiveBase, ACLPhantomTrackMode PhantomTrackMode);`
- L251 _prototype_ `uint32 GetNumSamples(const FCompressibleAnimData& CompressibleAnimData);` — Compatibility utilities
- L252 _prototype_ `float GetSequenceLength(const UAnimSequence& AnimSeq);`
- L254 _namespace_ `namespace ACL`
- L256 _namespace_ `namespace Private` (scope `ACL`)
- L258 _prototype_ `float GetPerPlatformFloat(const FPerPlatformFloat& PerPlatformFloat, const ITargetPlatform* TargetPlatform);` (scope `ACL::Private`)

### `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Public/IACLPluginModule.h` (Public)


#### class `IACLPlugin`  
`class IACLPlugin : public IModuleInterface`  
_L11-23_
- inherits: `IModuleInterface`
- desc: The main ACL plugin module interface.
- L14 _public function_ `static inline IACLPlugin& Get()`
- L19 _public function_ `static inline bool IsAvailable()`
