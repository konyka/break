# Plugins / GeometryCache

- module root: `Plugins/Runtime/GeometryCache/Source/GeometryCache`
- headers: 31; symbols: 1014
- symbol kinds: class=46, delegate=6, externvar=2, function=130, macro=20, member=359, namespace=7, prototype=392, struct=42, variable=10
- DynamicallyLoadedModuleNames: GeometryCacheEd
- PrivateDependencyModuleNames: GeometryCore, MeshConversion, MeshDescription, MeshUtilitiesCommon, StaticMeshDescription, TraceLog, UnrealEd
- PrivateIncludePathModuleNames: Shaders
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, Niagara, NiagaraCore, RHI, RenderCore, Slate, SlateCore
- PublicIncludePathModuleNames: GeometryCacheEd, TargetPlatform

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCache.h` (Public)


#### class `UGeometryCache`  
`class UGeometryCache : public UObject, public IInterface_AssetUserData`  
_L23-123_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object, BlueprintType, config = Engine)`
- inherits: `UObject,IInterface_AssetUserData`
- desc: A Geometry Cache is a piece/set of geometry that consists of individual Mesh/Transformation samples. In contrast with Static Meshes they can have their vertices animated in certain ways. *
- L28 _public prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;`
- L29 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L30 _public prototype_ `virtual void PostInitProperties() override;`
- L31 _public prototype_ `virtual FString GetDesc() override;`
- L32 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L34 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L35 _public prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L37 _public prototype_ `virtual void BeginDestroy() override;`
- L38 _public prototype_ `virtual bool IsReadyForFinishDestroy() override;`
- L40 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L50 _public prototype_ `void AddTrack(UGeometryCacheTrack* Track);` — AddTrack @param Track - GeometryCacheTrack instance that is a part of the GeometryCacheAsset @return void
- L53 _public prototype_ `void ClearForReimporting();` — Clears all stored data so the reimporting step can fill the instance again
- L58 _public member_ `TObjectPtr<class UAssetImportData> AssetImportData;` — `UPROPERTY(Category = ImportSettings, VisibleAnywhere, Instanced)` — Importing data and options used for this Geometry cache object
- L62 _public member_ `TObjectPtr<class UThumbnailInfo> ThumbnailInfo;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = Thumbnail)` — Information for thumbnail rendering
- L65 _public member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeometryCache)`
- L68 _public member_ `TArray<FName> MaterialSlotNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeometryCache)`
- L72 _public member_ `TArray<TObjectPtr<UGeometryCacheTrack>> Tracks;` — `UPROPERTY(VisibleAnywhere, Category=GeometryCache)` — GeometryCache track defining the samples/geometry data for this GeomCache instance
- L75 _public prototype_ `void SetFrameStartEnd(int32 InStartFrame, int32 InEndFrame);` — Set the start and end frames for the GeometryCache
- L78 _public prototype_ `int32 GetStartFrame() const;` — Get the start frame
- L81 _public prototype_ `int32 GetEndFrame() const;` — Get the end frame
- L84 _public prototype_ `float CalculateDuration() const;` — Calculate it's duration
- L87 _public prototype_ `int32 GetFrameAtTime(const float Time) const;` — Get the Frame at the Specified Time
- L90 _public prototype_ `void GetMeshDataAtTime(float Time, TArray<FGeometryCacheMeshData>& OutMeshData) const;` — Get the mesh data at the specified time
- L93 _public prototype_ `FString GetHash() const;` — Get the hash of the meshes data of the GeometryCache
- L98 _public member_ `TArray<TObjectPtr<UAssetUserData>> AssetUserData;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Instanced, Category = Hidden)` — Array of user data stored with the asset
- L101 _public prototype_ `virtual void AddAssetUserData(UAssetUserData* InUserData) override;`
- L102 _public prototype_ `virtual void RemoveUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override;`
- L103 _public prototype_ `virtual UAssetUserData* GetAssetUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override;`
- L104 _public prototype_ `virtual const TArray<UAssetUserData*>* GetAssetUserDataArray() const override;`
- L107 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnPreSave, UGeometryCache*);`
- L108 _public member_ `FOnPreSave OnPreSave;`
- L112 _private member_ `FRenderCommandFence ReleaseResourcesFence;` — A fence which is used to keep track of the rendering thread releasing the geometry cache resources.
- L116 _protected member_ `int32 StartFrame;` — `UPROPERTY(BlueprintReadOnly, Category = GeometryCache)`
- L119 _protected member_ `int32 EndFrame;` — `UPROPERTY(BlueprintReadOnly, Category = GeometryCache)`
- L122 _protected member_ `uint64 Hash;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYCACHE_API`
- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeometryCache, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeometryCache, Log, All);`
- L107 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPreSave, UGeometryCache*);`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheActor.h` (Public)


#### class `AGeometryCacheActor`  
`class AGeometryCacheActor : public AActor`  
_L14-30_
- reflection: `UCLASS(MinimalAPI, ComponentWrapperClass)`
- inherits: `AActor`
- desc: GeometryCache actor, serves as a place-able actor for GeometryCache objects
- L20 _private prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L25 _private member_ `TObjectPtr<UGeometryCacheComponent> GeometryCacheComponent;` — `UPROPERTY(Category = GeometryCacheActor, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Mesh,Rendering,Physics,Components|GeometryCache", AllowPrivateAccess = "true"))`
- L29 _public prototype_ `UGeometryCacheComponent* GetGeometryCacheComponent() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Returns GeometryCacheComponent subobject

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GEOMETRYCACHE_API`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheCodecBase.h` (Public)


#### struct `FStreamedGeometryCacheChunk`  
`struct FStreamedGeometryCacheChunk`  
_L22-44_
- desc: The smallest unit of streamed geometry cache data. An instance of this struct is kept resident for all chuncks only the BulkData member may not be loaded yet. Other info is permanently available.
- L24 _public prototype_ `FStreamedGeometryCacheChunk();`
- L27 _public member_ `int32 DataSize;` — Size of the chunk of data in bytes
- L30 _public member_ `float FirstFrame;` — Frame index of the earliest frame stored in this block
- L35 _public member_ `float LastFrame;` — End frame index of the interval this chunk contains data for. This closed so the last frame is included in the interval
- L38 _public member_ `FByteBulkData BulkData;` — Bulk data if stored in the package.
- L41 _public prototype_ `void Serialize(FArchive& Ar, UObject* Owner, int32 ChunkIndex);` — Serialization.
- L43 _public prototype_ `void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize);`

#### struct `FGeometryCacheCodecDecodeArguments`  
`struct FGeometryCacheCodecDecodeArguments`  
_L49-66_
- desc: Arguments passed to the decoder. This allows adding arguments easily without needing to change all decoders.
- L51 _public function_ `FGeometryCacheCodecDecodeArguments(FGeometryCacheTrackStreamableRenderResource &SetTrack, TArray<FStreamedGeometryCacheChunk> &SetChunks, uint32 SetFrameIdentifier, FGeometryCacheMeshData& SetOutMeshData) : Track(SetTrack), Chunks(SetChunks), FrameIdentifier(SetFrameIdentifier), OutMeshData(SetOutMeshData)`
- L62 _public member_ `FGeometryCacheTrackStreamableRenderResource &Track;`
- L63 _public member_ `TArray<FStreamedGeometryCacheChunk> &Chunks;`
- L64 _public member_ `uint32 FrameIdentifier;`
- L65 _public member_ `FGeometryCacheMeshData& OutMeshData;`

#### class `FGeometryCacheCodecRenderStateBase`  
`class FGeometryCacheCodecRenderStateBase`  
_L72-99_
- desc: Render thread side state. This is not a full blown FRenderResource it is a child instead of the UGeometryCacheTrackStreamable's Render Resource instance.
- L78 _public function_ `FGeometryCacheCodecRenderStateBase(const TArray<int32> &SetTopologyRanges) : TopologyRanges(SetTopologyRanges)` — Called on the game thread as part of UGeometryCacheCodecBase::CreateRenderState
- L86 _public function_ `virtual ~FGeometryCacheCodecRenderStateBase()` — This will be called on the render thread
- L91 _public function_ `virtual void InitRHI(FRHICommandListBase&)` — Called once we are on the render thread this can create any render buffers etc.
- L93 _public function_ `virtual bool DecodeSingleFrame(FGeometryCacheCodecDecodeArguments &Args)`
- L95 _public prototype_ `virtual bool IsTopologyCompatible(int32 SampleIndexA, int32 SampleIndexB);`
- L98 _private member_ `TArray<int32> TopologyRanges;`

#### struct `FGeometryCacheCodecEncodeArguments`  
`struct FGeometryCacheCodecEncodeArguments`  
_L101-112_
- L103 _public function_ `FGeometryCacheCodecEncodeArguments(const FGeometryCacheMeshData& SetMeshData, float SetSampleTime, bool bSetSameTopologyAsPrevious) : MeshData(SetMeshData), SampleTime(SetSampleTime), bSameTopologyAsPrevious(bSetSameTopologyAsPrevious)`
- L109 _public member_ `const FGeometryCacheMeshData& MeshData;` — Mesh data for the submitted sample
- L110 _public member_ `float SampleTime;` — Time for the submitted sample
- L111 _public member_ `bool bSameTopologyAsPrevious;` — Is the topology the same as the previously submitted sample

#### class `UGeometryCacheCodecBase`  
`class UGeometryCacheCodecBase : public UObject`  
_L117-154_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UObject`
- desc: Interface for assets/objects that can own UserData
- L121 _private prototype_ `virtual ~UGeometryCacheCodecBase() = default;`
- L123 _private function_ `virtual bool DecodeSingleFrame(FGeometryCacheCodecDecodeArguments &Args)`
- L124 _private function_ `virtual bool DecodeBuffer(const uint8* Buffer, uint32 BufferSize, FGeometryCacheMeshData& OutMeshData)`
- L127 _private function_ `virtual FGeometryCacheCodecRenderStateBase *CreateRenderState()` — Create a new FGeometryCacheCodecRenderStateBase for this codec. The returned object will be owned by the calling code.
- L131 _private prototype_ `virtual void BeginCoding(TArray<FStreamedGeometryCacheChunk> &AppendChunksTo);`
- L132 _private function_ `virtual void EndCoding()`
- L133 _private prototype_ `virtual void CodeFrame(const FGeometryCacheCodecEncodeArguments& Args);`
- L134 _private function_ `virtual int32 GetEncoderFrameNumer()`
- L137 _private prototype_ `static bool IsSameTopology(const TArray<int32>& TopologyRanges, int32 FrameA, int32 FrameB);`
- L138 _private function_ `virtual bool IsSameTopology(int32 FrameA, int32 FrameB)`
- L146 _protected member_ `FEncoderBaseData EncoderBaseData;`
- L153 _protected member_ `TArray<int32> TopologyRanges;` — `UPROPERTY(VisibleAnywhere, Category = GeometryCache)` — Frames at which the topology of the decoded frames changes sorted in increasing order this allows fast topology queries between arbitrary frames. each codec has to fill this

#### struct `UGeometryCacheCodecBase::FEncoderBaseData`  
`struct FEncoderBaseData`  
_L142-145_
- L144 _public member_ `int32 FrameId;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GEOMETRYCACHE_API`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheCodecRaw.h` (Public)


#### struct `FGeometryCacheCodecRenderStateRaw`  
`struct FGeometryCacheCodecRenderStateRaw : FGeometryCacheCodecRenderStateBase`  
_L12-16_
- inherits: `FGeometryCacheCodecRenderStateBase`
- L14 _public function_ `FGeometryCacheCodecRenderStateRaw(const TArray<int32> &SetTopologyRanges) : FGeometryCacheCodecRenderStateBase(SetTopologyRanges)`
- L15 _public prototype_ `virtual bool DecodeSingleFrame(FGeometryCacheCodecDecodeArguments &Args) override;`

#### class `UGeometryCacheCodecRaw`  
`class UGeometryCacheCodecRaw : public UGeometryCacheCodecBase`  
_L19-44_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UGeometryCacheCodecBase`
- L23 _private prototype_ `virtual bool DecodeSingleFrame(FGeometryCacheCodecDecodeArguments &Args) override;`
- L24 _private prototype_ `virtual FGeometryCacheCodecRenderStateBase *CreateRenderState() override;`
- L27 _private prototype_ `virtual void BeginCoding(TArray<FStreamedGeometryCacheChunk> &AppendChunksTo) override;`
- L28 _private prototype_ `virtual void EndCoding() override;`
- L29 _private prototype_ `virtual void CodeFrame(const FGeometryCacheCodecEncodeArguments& Args) override;`
- L34 _private member_ `int32 DummyProperty;` — `UPROPERTY(VisibleAnywhere, Category = GeometryCache)`
- L42 _private member_ `FEncoderData EncoderData;`

#### struct `UGeometryCacheCodecRaw::FEncoderData`  
`struct FEncoderData`  
_L37-41_
- L39 _public member_ `int32 CurrentChunkId;` — Index in the AppendChunksTo list of the chunk we are working on
- L40 _public member_ `TArray<FStreamedGeometryCacheChunk> *AppendChunksTo;` — Any chunks this codec creates will be appended to this list

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GEOMETRYCACHE_API`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheCodecV1.h` (Public)


#### struct `FGeometryCacheCodecRenderStateV1`  
`struct FGeometryCacheCodecRenderStateV1 : FGeometryCacheCodecRenderStateBase`  
_L14-20_
- inherits: `FGeometryCacheCodecRenderStateBase`
- L16 _public prototype_ `FGeometryCacheCodecRenderStateV1(const TArray<int32> &SetTopologyRanges);`
- L17 _public prototype_ `~FGeometryCacheCodecRenderStateV1();`
- L19 _public prototype_ `virtual bool DecodeSingleFrame(FGeometryCacheCodecDecodeArguments &Args) override;`

#### class `UGeometryCacheCodecV1`  
`class UGeometryCacheCodecV1 : public UGeometryCacheCodecBase`  
_L23-54_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UGeometryCacheCodecBase`
- L27 _private prototype_ `virtual ~UGeometryCacheCodecV1();`
- L29 _private prototype_ `virtual bool DecodeSingleFrame(FGeometryCacheCodecDecodeArguments &Args) override;`
- L30 _private prototype_ `virtual bool DecodeBuffer(const uint8* Buffer, uint32 BufferSize, FGeometryCacheMeshData& OutMeshData) override;`
- L31 _private prototype_ `virtual FGeometryCacheCodecRenderStateBase *CreateRenderState() override;`
- L34 _private prototype_ `virtual void InitializeEncoder(float InVertexQuantizationPrecision, int32 InUVQuantizationBitRange);`
- L35 _private prototype_ `virtual void BeginCoding(TArray<FStreamedGeometryCacheChunk> &AppendChunksTo) override;`
- L36 _private prototype_ `virtual void EndCoding() override;`
- L37 _private prototype_ `virtual void CodeFrame(const FGeometryCacheCodecEncodeArguments& Args) override;`
- L41 _private member_ `ICodecDecoder* Decoder;`
- L44 _private member_ `ICodecEncoder* Encoder;`
- L51 _private member_ `FEncoderData EncoderData;`
- L52 _private member_ `int32 NextContextId;`

#### struct `UGeometryCacheCodecV1::FEncoderData`  
`struct FEncoderData`  
_L46-50_
- L48 _public member_ `int32 CurrentChunkId;` — Index in the AppendChunksTo list of the chunk we are working on
- L49 _public member_ `TArray<FStreamedGeometryCacheChunk>* AppendChunksTo;` — Any chunks this codec creates will be appended to this list

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GEOMETRYCACHE_API`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheComponent.h` (Public)


#### struct `FTrackRenderData`  
`struct FTrackRenderData`  
_L16-33_
- reflection: `USTRUCT()`
- desc: Stores the RenderData for each individual track
- L20 _public function_ `FTrackRenderData() : Matrix(FMatrix::Identity), BoundingBox(EForceInit::ForceInitToZero), MatrixSampleIndex(INDEX_NONE), BoundsSampleIndex(INDEX_NONE)`
- L25 _public member_ `FMatrix Matrix;` — Transform matrix used to render this specific track. This goes from track local space to component local space.
- L28 _public member_ `FBox BoundingBox;` — Bounding box of this specific track
- L31 _public member_ `int32 MatrixSampleIndex;` — Sample Id's of the values we currently have registered the component with.
- L32 _public member_ `int32 BoundsSampleIndex;`

#### class `UGeometryCacheComponent`  
`class UGeometryCacheComponent : public UMeshComponent`  
_L37-357_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (Rendering), hidecategories = (Object, LOD), meta = (BlueprintSpawnableComponent))`
- inherits: `UMeshComponent`
- desc: GeometryCacheComponent, encapsulates a GeometryCache asset instance and implements functionality for rendering/and playback of GeometryCaches
- L45 _private prototype_ `virtual void BeginDestroy() override;`
- L46 _private prototype_ `virtual void FinishDestroy() override;`
- L47 _private prototype_ `virtual void PostLoad() override;`
- L49 _private prototype_ `virtual void PreEditUndo() override;`
- L50 _private prototype_ `virtual void PostEditUndo() override;`
- L51 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L56 _private prototype_ `virtual void OnRegister() override;`
- L57 _private prototype_ `virtual void OnUnregister() override;`
- L58 _private prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L62 _private prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L64 _private prototype_ `void UpdateLocalBounds();` — Update LocalBounds member from the local box of each section
- L68 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L69 _private prototype_ `virtual void CollectPSOPrecacheData(const FPSOPrecacheParams& BasePrecachePSOParams, FMaterialInterfacePSOPrecacheParamsList& OutParams) override;`
- L73 _private prototype_ `virtual int32 GetNumMaterials() const override;`
- L74 _private prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L75 _private prototype_ `virtual int32 GetMaterialIndex(FName MaterialSlotName) const override;`
- L76 _private prototype_ `virtual TArray<FName> GetMaterialSlotNames() const override;`
- L77 _private prototype_ `virtual bool IsMaterialSlotNameValid(FName MaterialSlotName) const override;`
- L85 _private prototype_ `void OnObjectReimported(UGeometryCache* ImportedGeometryCache);` — OnObjectReimported, Callback function to refresh section data and update scene proxy. @param ImportedGeometryCache
- L90 _public prototype_ `void Play();` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Start playback of GeometryCache
- L94 _public prototype_ `void PlayFromStart();` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Start playback of GeometryCache from the start
- L98 _public prototype_ `void PlayReversed();` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Start playback of GeometryCache in reverse
- L102 _public prototype_ `void PlayReversedFromEnd();` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Start playback of GeometryCache from the end and play in reverse
- L106 _public prototype_ `void Pause();` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Pause playback of GeometryCache
- L110 _public prototype_ `void Stop();` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Stop playback of GeometryCache
- L114 _public prototype_ `bool IsPlaying() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Get whether this GeometryCache is playing or not.
- L118 _public prototype_ `bool IsPlayingReversed() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Get whether this GeometryCache is playing in reverse or not.
- L122 _public prototype_ `bool IsLooping() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Get whether this GeometryCache is looping or not.
- L126 _public prototype_ `void SetLooping( const bool bNewLooping);` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Set whether this GeometryCache is looping or not.
- L130 _public prototype_ `bool IsInterpolatingFrames() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Get whether this GeometryCache is interpolating frames.
- L134 _public prototype_ `void SetInterpolateFrames(const bool bNewInterpolating);` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Set whether this GeometryCache is interpolating frames.
- L138 _public prototype_ `bool IsExtrapolatingFrames() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Get whether this GeometryCache is extrapolating frames.
- L142 _public prototype_ `void SetExtrapolateFrames(const bool bNewExtrapolating);` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Set whether this GeometryCache is extrapolating frames.
- L146 _public prototype_ `float GetPlaybackSpeed() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Get current playback speed for GeometryCache.
- L150 _public prototype_ `void SetPlaybackSpeed(const float NewPlaybackSpeed);` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Set new playback speed for GeometryCache.
- L154 _public prototype_ `float GetMotionVectorScale() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Get the motion vector scale.
- L158 _public prototype_ `void SetMotionVectorScale(const float NewMotionVectorScale);` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Set new motion vector scale.
- L162 _public prototype_ `bool SetGeometryCache( UGeometryCache* NewGeomCache );` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Change the Geometry Cache used by this instance.
- L167 _public prototype_ `UGeometryCache* GetGeometryCache() const;` — Getter for Geometry cache instance referred by the component Note: This getter is not exposed to blueprints as you can use the readonly Uproperty for that
- L171 _public prototype_ `float GetStartTimeOffset() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Get current start time offset for GeometryCache.
- L175 _public prototype_ `void SetStartTimeOffset(const float NewStartTimeOffset);` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Set current start time offset for GeometryCache.
- L179 _public prototype_ `float GetAnimationTime() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Get the current animation time for GeometryCache. Includes the influence of elapsed time and SetStartTimeOffset
- L183 _public prototype_ `float GetElapsedTime() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Get the current elapsed time for GeometryCache. Doesn't include the influence of StartTimeOffset
- L187 _public prototype_ `float GetPlaybackDirection() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Get the playback direction for GeometryCache.
- L191 _public member_ `TObjectPtr<UGeometryCache> GeometryCache;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GeometryCache)` — Geometry Cache instance referenced by the component
- L195 _public prototype_ `float GetDuration() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Get the duration of the playback
- L199 _public prototype_ `int32 GetNumberOfFrames() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Get the number of frames
- L203 _public prototype_ `int32 GetNumberOfTracks() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Get the number of tracks
- L207 _public prototype_ `void SetOverrideWireframeColor(bool bOverride);` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Override wireframe color?
- L211 _public prototype_ `bool GetOverrideWireframeColor() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Check whether we are overriding the wireframe color or not.
- L215 _public prototype_ `void SetWireframeOverrideColor(const FLinearColor Color);` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Set the color, used when overriding the wireframe color is enabled.
- L219 _public prototype_ `FLinearColor GetWireframeOverrideColor() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")` — Get the wireframe override color, used when overriding the wireframe color is enabled.
- L223 _public prototype_ `int32 GetFrameAtTime(const float Time) const;` — Helper to get the frame of the ABC asset at time provided
- L226 _public prototype_ `float GetTimeAtFrame(const int32 Frame) const;` — Helper to get the time at this frame
- L229 _public prototype_ `void SetCurrentTime(const float Time);` — Helper to make the animation jump to this time
- L233 _public prototype_ `void SetManualTick(bool bInManualTick);` — Functions to override the default TickComponent
- L234 _public prototype_ `bool GetManualTick() const;`
- L236 _public prototype_ `void ResetAnimationTime();`
- L239 _public prototype_ `void TickAtThisTime(const float Time, bool bInIsRunning, bool bInBackwards, bool bInIsLooping);` — `UFUNCTION(BlueprintCallable, Category = "Components|GeometryCache")`
- L243 _public prototype_ `void StepForward();` — Animation Helpers for Transport Controls
- L245 _public prototype_ `void ForwardEnd();`
- L247 _public prototype_ `void StepBackward();`
- L249 _public prototype_ `void BackwardEnd();`
- L251 _public prototype_ `void ToggleLooping();`
- L253 _public prototype_ `TArray<FString> GetTrackNames() const;`
- L260 _protected prototype_ `void InvalidateTrackSampleIndices();` — Invalidate both the Matrix and Mesh sample indices
- L265 _protected prototype_ `void ReleaseResources();` — ReleaseResources, clears and removes data stored/copied from GeometryCache instance
- L272 _protected prototype_ `bool UpdateTrackSection(int32 TrackIndex, float Time);` — Updates the game thread state of a track section @param TrackIndex - Index of the track we want to update
- L279 _protected prototype_ `void CreateTrackSection(int32 TrackIndex);` — CreateTrackSection, Create/replace a track section. @param TrackIndex - Index of the track to create (corresponds to an index on the geometry cache)
- L285 _protected prototype_ `void SetupTrackData();` — SetupTrackData Call CreateTrackSection for all tracks in the GeometryCache assigned to this object.
- L291 _protected prototype_ `void ClearTrackData();` — ClearTrackData Clean up data that was required for playback of geometry cache tracks
- L296 _protected prototype_ `void JumpAnimationToTime(float Time, bool bInIsRunning, bool bInBackwards, bool bInIsLooping);` — Jumps animation to time specified.
- L301 _protected prototype_ `void StepAnimationFrame(bool bInBackwards);` — Helper method to tick animation by one frame in PlayDirection
- L305 _protected member_ `bool bRunning;` — `UPROPERTY(EditAnywhere, Interp, Category = GeometryCache)`
- L308 _protected member_ `bool bLooping;` — `UPROPERTY(EditAnywhere, Interp, Category = GeometryCache)`
- L312 _protected member_ `bool bInterpolateFrames;` — `UPROPERTY(EditAnywhere, Category = GeometryCache, AdvancedDisplay)` — Enable frame interpolation for sub-frame sampling of constant topologies
- L316 _protected member_ `bool bExtrapolateFrames;` — `UPROPERTY(EditAnywhere, Category = GeometryCache, AdvancedDisplay)` — Enable frame extrapolation for sub-frame sampling of non-constant topologies with imported motion vectors
- L319 _protected member_ `float StartTimeOffset;` — `UPROPERTY(EditAnywhere, Interp, Category = GeometryCache, meta = (UIMin = "-14400.0", UIMax = "14400.0", ClampMin = "-14400.0", ClampMax = "14400.0"))`
- L322 _protected member_ `float PlaybackSpeed;` — `UPROPERTY(EditAnywhere, Interp, Category = GeometryCache, meta = (UIMin = "0.0", UIMax = "4.0", ClampMin = "0.0", ClampMax = "512.0"))`
- L326 _protected member_ `float MotionVectorScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeometryCache, meta = (ClampMin = "0.0", ClampMax = "100", UIMin = "0.0", UIMax = "100"))` — Scale factor to apply to the imported motion vectors
- L329 _protected member_ `int32 NumTracks;` — `UPROPERTY(VisibleAnywhere, Category = GeometryCache)`
- L332 _protected member_ `float ElapsedTime;` — `UPROPERTY(VisibleAnywhere, transient, Category = GeometryCache)`
- L335 _protected member_ `FBoxSphereBounds LocalBounds;` — Component local space bounds of geometry cache mesh
- L338 _protected member_ `TArray<FTrackRenderData> TrackSections;` — Array containing the TrackData (used for rendering) for each individual track
- L341 _protected member_ `float PlayDirection;` — Play (time) direction, either -1.0f or 1.0f
- L345 _protected member_ `float Duration;` — `UPROPERTY(BlueprintReadOnly, Category = GeometryCache)` — Duration of the animation (maximum time)
- L348 _protected member_ `bool bManualTick;` — `UPROPERTY(EditAnywhere, Category = GeometryCache)`
- L352 _protected member_ `bool bOverrideWireframeColor;` — `UPROPERTY(EditAnywhere, Category = GeometryCache)` — Do we override the wireframe rendering color?
- L356 _protected member_ `FLinearColor WireframeOverrideColor;` — `UPROPERTY(EditAnywhere, Category = GeometryCache, meta = (EditCondition = "bOVerrideWireframeColor"))` — The wireframe override color.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GEOMETRYCACHE_API`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheMeshData.h` (Public)


#### struct `FGeometryCacheMeshBatchInfo`  
`struct FGeometryCacheMeshBatchInfo`  
_L12-32_
- reflection: `USTRUCT()`
- desc: Stores per-batch data used for rendering
- L17 _public member_ `uint32 StartIndex;` — Starting index into IndexBuffer to draw from
- L19 _public member_ `uint32 NumTriangles;` — Total number of Triangles to draw
- L21 _public member_ `uint32 MaterialIndex;` — Index to Material used to draw this batch

#### struct `FGeometryCacheVertexInfo`  
`struct FGeometryCacheVertexInfo`  
_L36-93_
- reflection: `USTRUCT()`
- desc: Stores info on the attributes of a vertex in a mesh
- L41 _public member_ `bool bHasTangentX;` — Info on which attributes are present or valid
- L42 _public member_ `bool bHasTangentZ;`
- L43 _public member_ `bool bHasUV0;`
- L44 _public member_ `bool bHasColor0;`
- L45 _public member_ `bool bHasMotionVectors;`
- L46 _public member_ `bool bHasImportedVertexNumbers;`
- L48 _public member_ `bool bConstantUV0;`
- L49 _public member_ `bool bConstantColor0;`
- L50 _public member_ `bool bConstantIndices;`
- L52 _public function_ `FGeometryCacheVertexInfo()`
- L65 _public function_ `FGeometryCacheVertexInfo( bool bSetTangentX, bool bSetTangentZ, bool bSetUV0, bool bSetColor0, bool bSetMotionVectors0 ) : bHasTangentX(bSetTangentX), bHasTangentZ(bSetTangentZ), bHasUV0(bSetUV0), bHasColor0(bSetColor0), bHasMotionVectors(bSetMotionVectors0)`

#### struct `FGeometryCacheMeshData`  
`struct FGeometryCacheMeshData`  
_L97-171_
- reflection: `USTRUCT()`
- desc: Stores per Track/Mesh data used for rendering
- L101 _public function_ `FGeometryCacheMeshData() : BoundingBox(EForceInit::ForceInitToZero) , Hash(0)`
- L107 _public member_ `TArray<FVector3f> Positions;` — Draw-able vertex data
- L108 _public member_ `TArray<FVector2f> TextureCoordinates;`
- L109 _public member_ `TArray<FPackedNormal> TangentsX;`
- L110 _public member_ `TArray<FPackedNormal> TangentsZ;`
- L111 _public member_ `TArray<FColor> Colors;`
- L114 _public member_ `TArray<uint32> ImportedVertexNumbers;` — The original imported vertex numbers, as they come from the DCC. One for each vertex position.
- L117 _public member_ `TArray<FVector3f> MotionVectors;` — Motion vector for each vertex. The number of motion vectors should be zero (= no motion vectors) or identical to the number of vertices.
- L119 _public member_ `TArray<FGeometryCacheMeshBatchInfo> BatchesInfo;` — Array of per-batch info structs
- L121 _public member_ `FBox3f BoundingBox;` — Bounding box for this sample in the track
- L123 _public member_ `TArray<uint32> Indices;` — Indices for this sample, used for drawing the mesh
- L125 _public member_ `FGeometryCacheVertexInfo VertexInfo;` — Info on the vertex attributes
- L128 _public member_ `TArray<uint8> TempBytes;` — A reusable array of bytes used to decode frame data.
- L140 _public function_ `void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) const`
- L167 _public prototype_ `uint64 GetHash() const;` — Return a hash of the content of the GeometryCacheMeshData
- L170 _private member_ `mutable uint64 Hash;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GEOMETRYCACHE_API`
- L23 _function_ `friend FArchive& operator<<(FArchive& Ar, FGeometryCacheMeshBatchInfo& Mesh)`
- L78 _function_ `friend FArchive& operator<<(FArchive& Ar, FGeometryCacheVertexInfo& Mesh)`
- L134 _function_ `friend FArchive& operator<<(FArchive& Ar, const FGeometryCacheMeshData& Mesh)` — Serialization for const FVertexAnimationSample.

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheStreamingManagerBase.h` (Public)


#### struct `IGeometryCacheStreamingManager`  
`struct IGeometryCacheStreamingManager : public IStreamingManager`  
_L13-55_
- inherits: `IStreamingManager`
- desc: Note IStreamingManager is not really anything like an interface it contains code and members and whatnot. So we just play along here to keep the spirit of the existing audio and texture streaming managers.
- L15 _public function_ `IGeometryCacheStreamingManager()`
- L18 _public prototype_ `virtual ~IGeometryCacheStreamingManager() = default;` — Virtual destructor
- L21 _public prototype_ `static struct IGeometryCacheStreamingManager& Get();` — Getter of the singleton
- L24 _public prototype_ `virtual void AddGeometryCache(UGeometryCacheTrackStreamable* Cache) = 0;` — Adds a new cache to the streaming manager.
- L27 _public prototype_ `virtual void RemoveGeometryCache(UGeometryCacheTrackStreamable* Cache) = 0;` — Removes a cache from the streaming manager.
- L30 _public prototype_ `virtual bool IsManagedGeometryCache(const UGeometryCacheTrackStreamable* Cache) const = 0;` — Returns true if this is a cache is managed by the streaming manager.
- L33 _public prototype_ `virtual bool IsStreamingInProgress(const UGeometryCacheTrackStreamable* Cache) = 0;` — Returns true if this Sound Wave is currently streaming a chunk.
- L35 _public prototype_ `virtual bool CanCreateSoundSource(const FWaveInstance* WaveInstance) const = 0;`
- L38 _public prototype_ `virtual void AddStreamingComponent(UGeometryCacheComponent* CacheComponent) = 0;` — Adds a new Sound Source to the streaming manager.
- L41 _public prototype_ `virtual void RemoveStreamingComponent(UGeometryCacheComponent* CacheComponent) = 0;` — Removes a Sound Source from the streaming manager.
- L44 _public prototype_ `virtual bool IsManagedComponent(const UGeometryCacheComponent* CacheComponent) const = 0;` — Returns true if this is a streaming Sound Source that is managed by the streaming manager.
- L53 _public prototype_ `virtual const uint8* GetLoadedChunk(const UGeometryCacheTrackStreamable* Track, uint32 ChunkIndex, uint32* OutChunkSize = NULL) const = 0;` — Gets a pointer to a chunk of cahed geometry data @param Track Animation track we want a chunk from @param ChunkIndex	Index of the chunk we want @return Either the desired chunk or NULL if it's not loaded

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheTrack.h` (Public)


#### class `UGeometryCacheTrack`  
`class UGeometryCacheTrack : public UObject`  
_L17-171_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, BlueprintType, config = Engine)`
- inherits: `UObject`
- desc: Base class for GeometryCache tracks, stores matrix animation data and implements functionality for it
- L21 _private prototype_ `virtual ~UGeometryCacheTrack();`
- L24 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L25 _private prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L37 _private prototype_ `virtual const bool UpdateMatrixData(const float Time, const bool bLooping, int32& InOutMatrixSampleIndex, FMatrix& OutWorldMatrix);` — UpdateMatrixData @param Time - (Elapsed)Time to check against @param bLooping - Whether or not the animation should be played on a loop @param InOutMatrixSampleIndex - Hold the MatrixSampleIndex and will be updated if changed according to the Elapsed Time @param OutWorldMatrix - Will hold the new WorldMatrix if the SampleIndex changed @return const bool
- L50 _private prototype_ `virtual const bool UpdateBoundsData(const float Time, const bool bLooping, const bool bIsPlayingBackward, int32& InOutBoundsSampleIndex, FBox& OutBounds);` — UpdateBoundsData Note: Bounds may be sampled at a different rate than the matrixes above so they have separate sample indexes to cache. @param Time - (Elapsed)Time to check against @param bLooping - Whether or not the animation should be played on a loop @param InOutBoundsSampleIndex - Hold the BoundsSampleIndex and will be updated if changed according to the Elapsed Time @param OutBounds - Will hold the new bounding box if the SampleIndex changed @return const bool
- L61 _private prototype_ `virtual const bool UpdateMeshData(const float Time, const bool bLooping, int32& InOutMeshSampleIndex, FGeometryCacheMeshData*& OutMeshData );` — UpdateMeshData * @param Time - (Elapsed)Time to check against @param bLooping - Whether or not the animation should be played on a loop @param InOutMeshSampleIndex - Hold the MeshSampleIndex and will be updated if changed according to the Elapsed Time @param OutVertices - Will hold the new VertexData if the SampleIndex changed @return const bool
- L70 _private prototype_ `virtual void SetMatrixSamples(const TArray<FMatrix>& Matrices, const TArray<float>& SampleTimes);` — SetMatrixSamples, Set the Matrix animation Samples @param Matrices - Array of Matrices @param SampleTimes - Array of SampleTimes @return void
- L79 _private prototype_ `virtual void AddMatrixSample(const FMatrix& Matrix, const float SampleTime);` — AddMatrixSample, Adds a single matrix animation sample (recalculates duration according to SampleTime) @param Matrix @param SampleTime - Time for this sample @return void
- L87 _private prototype_ `virtual void SetDuration(float NewDuration);` — Set the duration property. @param NewDuration - Duration to set @return void
- L94 _private prototype_ `virtual float GetDuration();` — Get the value of the duration property. @return The value of the Duration property
- L102 _private prototype_ `virtual const float GetMaxSampleTime() const;` — GetMaxSampleTime, returns the time for the last sample Not the same as the animation length since it might not start at time 0 @return const float
- L109 _private function_ `const uint32 GetNumMaterials() const` — GetNumMaterials, total number of materials inside this track (depends on batches) @return const uint32
- L117 _private prototype_ `virtual const FGeometryCacheTrackSampleInfo& GetSampleInfo(float Time, const bool bLooping);` — Get the info for the sample displayed at the given time. @param Time - (Elapsed)Time to check against @param bLooping - Whether or not the animation is being played in a loop
- L126 _private function_ `virtual bool GetMeshDataAtTime(float Time, FGeometryCacheMeshData& OutMeshData)` — Get the mesh data for the specified time @param Time - The time (in secs) to retrieve the mesh data for @param OutMeshData - Will contain the mesh data that was retrieved, if successful @return True if the mesh data could be retrieved
- L135 _private function_ `virtual bool GetMeshDataAtSampleIndex(int32 SampleIndex, FGeometryCacheMeshData& OutMeshData)` — Get the mesh data for the specified sample index @param SampleIndex - The sample index to get the mesh data for @param OutMeshData - Will contain the mesh data that was retrieved, if successful @return True if the mesh data could be retrieved
- L138 _private function_ `virtual uint64 GetHash() const` — Return the hash of the mesh data of the track
- L141 _private function_ `virtual void UpdateTime(float Time, bool bLooping)` — Update the current time of the track
- L153 _protected member_ `float Duration;` — `UPROPERTY(VisibleAnywhere, Category = GeometryCache)` — The duration of this track's animation. This is an open ended interval [0..Duration[. If the animation is looping this is also the length of the loop. Note: This is set by the importer possibly based on user preferences. There may be less actual frames available. E.g. the animation has data for the first 2 seconds, but duration is set to 5, so it will loop every 5 seconds with the last three seconds showing a static scene.
- L163 _protected prototype_ `const uint32 FindSampleIndexFromTime(const TArray<float>& SampleTimes, const float Time, const bool bLooping);` — FindSampleIndexFromTime uses binary search to find the closest index to Time inside Samples @param SampleTimes - Array of Sample times used for the search @param Time - Time for which the closest index has to be found @param bLooping - Whether or not we should fmod Time according to the last entry in SampleTimes @return const uint32
- L166 _protected member_ `TArray<FMatrix> MatrixSamples;` — Matrix sample data, both FMatrix and time
- L167 _protected member_ `TArray<float> MatrixSampleTimes;`
- L170 _protected member_ `uint32 NumMaterials;` — Number of materials for this track

#### struct `FGeometryCacheTrackSampleInfo`  
`struct FGeometryCacheTrackSampleInfo`  
_L176-189_
- desc: Info stored per sample that is always resident in memory
- L178 _public member_ `float SampleTime;`
- L179 _public member_ `FBox BoundingBox;`
- L180 _public member_ `int32 NumVertices;`
- L181 _public member_ `int32 NumIndices;`
- L183 _public function_ `FGeometryCacheTrackSampleInfo() : SampleTime(0.0f), BoundingBox(EForceInit::ForceInit), NumVertices(0), NumIndices(0)`
- L185 _public function_ `FGeometryCacheTrackSampleInfo(float SetSampleTime, FBox SetBoundingBox, int32 SetNumVertices, int32 SetNumIndices) : SampleTime(SetSampleTime), BoundingBox(SetBoundingBox), NumVertices(SetNumVertices), NumIndices(SetNumIndices)`
- L188 _public member_ `static const FGeometryCacheTrackSampleInfo EmptySampleInfo;`

#### struct `FVisibilitySample`  
`struct FVisibilitySample`  
_L194-209_
- desc: Hold the visibility state for a given time range
- L196 _public prototype_ `FVisibilitySample() = default;`
- L198 _public function_ `FVisibilitySample(bool bVisible) : bVisibilityState(bVisible)`
- L202 _public member_ `TRange<float> Range;`
- L203 _public member_ `bool bVisibilityState;`
- L207 _public member_ `static const FVisibilitySample VisibleSample;`
- L208 _public member_ `static const FVisibilitySample InvisibleSample;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GEOMETRYCACHE_API`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheTrackFlipbookAnimation.h` (Public)


#### class `UDEPRECATED_GeometryCacheTrack_FlipbookAnimation`  
`class UDEPRECATED_GeometryCacheTrack_FlipbookAnimation : public UGeometryCacheTrack`  
_L12-46_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, BlueprintType, config = Engine, deprecated)`
- inherits: `UGeometryCacheTrack`
- desc: Derived GeometryCacheTrack class, used for Transform animation.
- L16 _private prototype_ `virtual ~UDEPRECATED_GeometryCacheTrack_FlipbookAnimation();`
- L19 _private prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L20 _private prototype_ `virtual void BeginDestroy() override;`
- L24 _private prototype_ `virtual const bool UpdateMeshData(const float Time, const bool bLooping, int32& InOutMeshSampleIndex, FGeometryCacheMeshData*& OutMeshData) override;`
- L25 _private prototype_ `virtual const float GetMaxSampleTime() const override;`
- L36 _private prototype_ `void AddMeshSample(const FGeometryCacheMeshData& MeshData, const float SampleTime);` — `UFUNCTION()` — Add a GeometryCacheMeshData sample to the Track @param MeshData - Holds the mesh data for the specific sample @param SampleTime - SampleTime for the specific sample being added @return void
- L41 _private member_ `uint32 NumMeshSamples;` — `UPROPERTY(VisibleAnywhere, Category = GeometryCache)` — Number of Mesh Sample within this track
- L44 _private member_ `TArray<FGeometryCacheMeshData> MeshSamples;` — Stored data for each Mesh sample
- L45 _private member_ `TArray<float> MeshSampleTimes;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GEOMETRYCACHE_API`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheTrackStreamable.h` (Public)


#### struct `FGeometryCacheTrackMeshDataUpdate`  
`struct FGeometryCacheTrackMeshDataUpdate`  
_L17-21_
- L19 _public member_ `void* VertexBuffer;`
- L20 _public member_ `void* IndexBuffer;`

#### class `FGeometryCacheTrackStreamableRenderResource`  
`class FGeometryCacheTrackStreamableRenderResource : public FRenderResource`  
_L28-71_
- inherits: `FRenderResource`
- desc: All render thread state for a geometry cache track. This contains shared render thread state shared by all GeometryCacheComponents that use the same GeometryCache. The per-component state is managed in the GeometryCacheScene proxy.
- L31 _public prototype_ `FGeometryCacheTrackStreamableRenderResource();`
- L32 _public prototype_ `void InitGame(UGeometryCacheTrackStreamable *Track);`
- L33 _public prototype_ `void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L34 _public prototype_ `void ReleaseRHI() override;`
- L36 _public prototype_ `bool UpdateMeshData(float Time, bool bLooping, int32& InOutMeshSampleIndex, FGeometryCacheMeshData& OutMeshData);`
- L44 _public prototype_ `bool DecodeMeshData(int32 SampleIndexToDecode, FGeometryCacheMeshData& OutMeshData);` — Decode a single frame of mesh data. @param SampleIndexToDecode - Index of the frame to decode. Some codecs may have inter-frame dependencies. All complexity related to is handled by the codec but decoding subsequent frames may be more efficient than decoding random frames. @param OutMeshData - The decoded mesh is stored in this object.
- L46 _public prototype_ `bool IsTopologyCompatible(int32 SampleIndexA, int32 SampleIndexB);`
- L58 _public function_ `UGeometryCacheTrackStreamable *GetTrack()` — Get the UGeometryCacheTrackStreamable track corresponding to this render resource. This track data is valid and won't change as long as this FGeometryCacheTrackStreamableRenderResource instance is live. If we need to modify the track we will first tear down this FGeometryCacheTrackStreamableRenderResource instance and sync the renderthread. So you can keep the pointer around as long as you know the FGeometryCacheTrackStreamableRenderResource instance you got it from stays valid.
- L63 _public function_ `FGeometryCacheCodecRenderStateBase *GetCodec()`
- L69 _protected member_ `FGeometryCacheCodecRenderStateBase *Codec;` — Render thread codec instance
- L70 _protected member_ `UGeometryCacheTrackStreamable *Track;` — See docs for GetTrack above.

#### struct `FGeometryCacheTrackStreamableSampleInfo`  
`struct FGeometryCacheTrackStreamableSampleInfo : public FGeometryCacheTrackSampleInfo`  
_L77-85_
- inherits: `FGeometryCacheTrackSampleInfo`
- desc: Info stored per sample that is always resident in memory and does not require parsing the chunks. Needed to keep support for serialization of FGeometryCacheTrackStreamableSampleInfo
- L79 _public function_ `FGeometryCacheTrackStreamableSampleInfo() : FGeometryCacheTrackSampleInfo()`
- L81 _public function_ `FGeometryCacheTrackStreamableSampleInfo(float SetSampleTime, FBox SetBoundingBox, int32 SetNumVertices, int32 SetNumIndices) : FGeometryCacheTrackSampleInfo(SetSampleTime, SetBoundingBox, SetNumVertices, SetNumIndices)`

#### class `UGeometryCacheTrackStreamable`  
`class UGeometryCacheTrackStreamable : public UGeometryCacheTrack`  
_L95-229_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, BlueprintType, config = Engine)`
- inherits: `UGeometryCacheTrack`
- desc: Derived GeometryCacheTrack class, used for Transform animation. \note FGeometryCacheTrackStreamableRenderResource keeps a reference to the track. Be sure to keep the implementation of this class valid so it properly releases the render resoruce before making any changes to this object that may affect the render thread.
- L99 _private prototype_ `virtual ~UGeometryCacheTrackStreamable();`
- L102 _private prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L103 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L104 _private prototype_ `virtual void BeginDestroy() override;`
- L105 _private prototype_ `virtual bool IsReadyForFinishDestroy() override;`
- L106 _private prototype_ `virtual void FinishDestroy() override;`
- L107 _private prototype_ `virtual void PostLoad() override;`
- L108 _private prototype_ `virtual void PostInitProperties() override;`
- L112 _private prototype_ `virtual const bool UpdateMeshData(const float Time, const bool bLooping, int32& InOutMeshSampleIndex, FGeometryCacheMeshData*& OutMeshData) override;`
- L113 _private prototype_ `virtual const bool UpdateBoundsData(const float Time, const bool bLooping, const bool bIsPlayingBackward, int32& InOutBoundsSampleIndex, FBox& OutBounds) override;`
- L114 _private prototype_ `virtual const float GetMaxSampleTime() const override;`
- L115 _private prototype_ `virtual void SetDuration(float NewDuration) override;`
- L116 _private prototype_ `virtual const FGeometryCacheTrackSampleInfo& GetSampleInfo(float Time, const bool bLooping) override;`
- L117 _private prototype_ `virtual bool GetMeshDataAtTime(float Time, FGeometryCacheMeshData& OutMeshData) override;`
- L118 _private prototype_ `virtual bool GetMeshDataAtSampleIndex(int32 SampleIndex, FGeometryCacheMeshData& OutMeshData) override;`
- L119 _private prototype_ `virtual uint64 GetHash() const override;`
- L127 _private prototype_ `void BeginCoding(UGeometryCacheCodecBase* SetCodec, bool bForceSingleOptimization, bool bCalculateAndStoreMotionVectors, bool bOptimizeIndexBuffers);` — Begin coding and set the codec to use for this track. The passed in codec object is assumed to be exclusive to this track.
- L136 _private prototype_ `void AddMeshSample(const FGeometryCacheMeshData& MeshData, const float SampleTime, bool bSameTopologyAsPrevious);` — Add a GeometryCacheMeshData sample to the Track @param MeshData - Holds the mesh data for the specific sample @param SampleTime - SampleTime for the specific sample being added @return void
- L138 _private prototype_ `void AddVisibilitySample(const bool bVisible, const float SampleTime);`
- L143 _private prototype_ `bool EndCoding();` — Finish up coding. Return true if the track has samples
- L148 _private member_ `TObjectPtr<UGeometryCacheCodecBase> Codec;` — `UPROPERTY(VisibleAnywhere, Category = GeometryCache)` — Codec for this track
- L149 _private member_ `FGeometryCachePreprocessor *Preprocessor;`
- L158 _private prototype_ `void GetChunksForTimeRange(float StartTime, float EndTime, bool Looping, TArray<int32>& OutChunkIndexes);` — Get the CunksIds that need to be loaded to display any frames falling within the given time range. @param StartTime Beginning of the range to return chunks for @param EndTime End of the range to return chunks for @param Looping If the animation playback is looping and thus the interval needs to wrap around based on this track's Duration @param OutChunkIndexes This list will be filled with the needed ChunkIds
- L160 _private function_ `const FStreamedGeometryCacheChunk &GetChunk(int32 ChunkID) const`
- L165 _private function_ `FStreamedGeometryCacheChunk &GetChunk(int32 ChunkID)`
- L170 _private function_ `FGeometryCacheTrackStreamableRenderResource *GetRenderResource()`
- L185 _private prototype_ `const uint32 FindSampleIndexFromTime(const float Time, const bool bLooping) const;` — FindSampleIndexFromTime uses binary search to find the closest index to Time inside Samples @param Time - Time for which the closest index has to be found @param bLooping - Whether or not we should fmod Time according to the last entry in SampleTimes @return const uint32
- L195 _private prototype_ `void FindSampleIndexesFromTime(float Time, bool bLooping, bool bIsPlayingBackwards, int32 &OutFrameIndex, int32 &OutNextFrameIndex, float &InterpolationFactor);` — Find the two frames closest to the given time. InterpolationFactor gives the position of the requested time slot between the two returned frames. 0.0 => We are very close to OutFrameIndex 1.0 => We are very close to OutNextFrameIndex If bIsPlayingBackwards it will return exactly the same indexes but in the reversed order. The InterpolationFactor will also be updated accordingly
- L200 _private prototype_ `const FGeometryCacheTrackStreamableSampleInfo& GetSampleInfo(int32 SampleID) const;` — Get the info for the sample with the given ID.
- L202 _private prototype_ `const FVisibilitySample& GetVisibilitySample(float Time, const bool bLooping) const;`
- L206 _private prototype_ `static void TriggerSerializationCrash();`
- L210 _private prototype_ `void ReleaseRenderResources();`
- L211 _private prototype_ `void InitializeRenderResources();`
- L214 _private member_ `TArray<FStreamedGeometryCacheChunk> Chunks;` — Stored data for each Mesh sample
- L215 _private member_ `TArray<FGeometryCacheTrackStreamableSampleInfo> Samples;`
- L217 _private member_ `TArray<FVisibilitySample> VisibilitySamples;`
- L219 _private member_ `TArray<TPair<float, bool>> ImportVisibilitySamples;`
- L222 _private member_ `FGeometryCacheTrackStreamableRenderResource RenderResource;`
- L223 _private member_ `FRenderCommandFence ReleaseResourcesFence;`
- L226 _private member_ `float StartSampleTime;` — `UPROPERTY()`
- L228 _private member_ `uint64 Hash;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYCACHE_API`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheTrackTransformAnimation.h` (Public)


#### class `UDEPRECATED_GeometryCacheTrack_TransformAnimation`  
`class UDEPRECATED_GeometryCacheTrack_TransformAnimation : public UGeometryCacheTrack`  
_L13-34_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, BlueprintType, config = Engine, deprecated)`
- inherits: `UGeometryCacheTrack`
- desc: Derived GeometryCacheTrack class, used for Transform animation.
- L18 _private prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L22 _private prototype_ `virtual const bool UpdateMeshData(const float Time, const bool bLooping, int32& InOutMeshSampleIndex, FGeometryCacheMeshData*& OutMeshData) override;`
- L31 _private prototype_ `void SetMesh(const FGeometryCacheMeshData& NewMeshData);` — `UFUNCTION()` — Sets/updates the MeshData for this track @param NewMeshData - GeometryCacheMeshData instance later used as the rendered mesh
- L33 _private member_ `FGeometryCacheMeshData MeshData;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GEOMETRYCACHE_API`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheTrackTransformGroupAnimation.h` (Public)


#### class `UDEPRECATED_GeometryCacheTrack_TransformGroupAnimation`  
`class UDEPRECATED_GeometryCacheTrack_TransformGroupAnimation : public UGeometryCacheTrack`  
_L13-34_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, BlueprintType, config = Engine, deprecated)`
- inherits: `UGeometryCacheTrack`
- desc: Derived GeometryCacheTrack class, used for Transform animation.
- L18 _private prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L22 _private prototype_ `virtual const bool UpdateMeshData(const float Time, const bool bLooping, int32& InOutMeshSampleIndex, FGeometryCacheMeshData*& OutMeshData) override;`
- L31 _private prototype_ `void SetMesh(const FGeometryCacheMeshData& NewMeshData);` — `UFUNCTION()` — Sets/updates the MeshData for this track @param NewMeshData - GeometryCacheMeshData instance later used as the rendered mesh
- L33 _private member_ `FGeometryCacheMeshData MeshData;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GEOMETRYCACHE_API`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/ICodecDecoder.h` (Public)


#### class `ICodecDecoder`  
`class ICodecDecoder`  
_L11-23_
- desc: Interface to the internal mesh compressor's decoder in order to hide implementation
- L14 _public prototype_ `virtual ~ICodecDecoder() = default;`
- L22 _public prototype_ `virtual bool DecodeFrameData(FBufferReader& Reader, FGeometryCacheMeshData& OutMeshData) = 0;` — Read a frame's bit stream and decode the frame @param Reader - Reader holding the frame's bit stream @param OutMeshData - Decoded mesh

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/ICodecEncoder.h` (Public)


#### class `ICodecEncoder`  
`class ICodecEncoder`  
_L11-23_
- desc: Interface to the internal mesh compressor's encoder in order to hide implementation
- L14 _public prototype_ `virtual ~ICodecEncoder() = default;`
- L22 _public prototype_ `virtual bool EncodeFrameData(FMemoryWriter& Writer, const FGeometryCacheCodecEncodeArguments &Args) = 0;` — Encode a frame and write the bitstream @param Writer - Writer for the output bit stream @param Args - Encoding arguments

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/NiagaraGeometryCacheRendererProperties.h` (Public)


#### struct `FNiagaraGeometryCacheMICOverride`  
`struct FNiagaraGeometryCacheMICOverride`  
_L18-27_
- reflection: `USTRUCT()`
- L23 _public member_ `TObjectPtr<UMaterialInterface> OriginalMaterial;` — `UPROPERTY()`
- L26 _public member_ `TObjectPtr<UMaterialInstanceConstant> ReplacementMaterial;` — `UPROPERTY()`

#### struct `FNiagaraGeometryCacheReference`  
`struct FNiagaraGeometryCacheReference`  
_L30-52_
- reflection: `USTRUCT()`
- L34 _public prototype_ `FNiagaraGeometryCacheReference();`
- L36 _public prototype_ `UMaterialInterface* ResolveMaterial(UGeometryCache* ResolvedCache, int32 MaterialIndex) const;`
- L40 _public member_ `TObjectPtr<UGeometryCache> GeometryCache;` — `UPROPERTY(EditAnywhere, Category = "GeometryCache")` — Reference to the geometry cache asset to use (if the user parameter binding is not set)
- L44 _public member_ `FNiagaraUserParameterBinding GeometryCacheUserParamBinding;` — `UPROPERTY(EditAnywhere, Category = "GeometryCache")` — Use the UGeometryCache bound to this user variable if it is set to a valid value. If this is bound to a valid value and GeometryCache is also set, GeometryCacheUserParamBinding wins.
- L48 _public member_ `TArray<TObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(EditAnywhere, Category = "GeometryCache")` — The materials to be used instead of the GeometryCache's materials. If the GeometryCache requires more materials than exist in this array or any entry in this array is set to None, we will use the GeometryCache's existing material instead.
- L51 _public member_ `TArray<FNiagaraGeometryCacheMICOverride> MICOverrideMaterials;` — `UPROPERTY()`

#### class `UNiagaraGeometryCacheRendererProperties`  
`class UNiagaraGeometryCacheRendererProperties : public UNiagaraRendererProperties`  
_L55-187_
- reflection: `UCLASS(editinlinenew, MinimalAPI, meta = (DisplayName = "Geometry Cache Renderer"))`
- inherits: `UNiagaraRendererProperties`
- L60 _public prototype_ `UNiagaraGeometryCacheRendererProperties();`
- L63 _public prototype_ `virtual void PostLoad() override;` — UObject Interface
- L64 _public prototype_ `virtual void PostInitProperties() override;`
- L66 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L70 _public prototype_ `static void InitCDOPropertiesAfterModuleStartup();`
- L73 _public prototype_ `virtual FNiagaraRenderer* CreateEmitterRenderer(ERHIFeatureLevel::Type FeatureLevel, const FNiagaraEmitterInstance* Emitter, const FNiagaraSystemInstanceController& InController) override;`
- L74 _public function_ `virtual class FNiagaraBoundsCalculator* CreateBoundsCalculator() override`
- L75 _public function_ `virtual bool IsSimTargetSupported(ENiagaraSimTarget InSimTarget) const override`
- L76 _public prototype_ `virtual void GetUsedMaterials(const FNiagaraEmitterInstance* InEmitter, TArray<UMaterialInterface*>& OutMaterials) const override;`
- L77 _public prototype_ `virtual void GetUsedMeshes(const FNiagaraEmitterInstance* InEmitter, TArray<UObject*>& OutMeshes) const override;`
- L78 _public prototype_ `virtual void UpdateSourceModeDerivates(ENiagaraRendererSourceDataMode InSourceMode, bool bFromPropertyEdit = false) override;`
- L79 _public function_ `virtual ENiagaraRendererSourceDataMode GetCurrentSourceMode() const override`
- L80 _public prototype_ `virtual bool PopulateRequiredBindings(FNiagaraParameterStore& InParameterStore) override;`
- L81 _public function_ `virtual bool NeedsMIDsForMaterials() const override`
- L82 _public prototype_ `virtual void CacheFromCompiledData(const FNiagaraDataSetCompiledData* CompiledData) override;`
- L85 _public prototype_ `virtual void GetRendererWidgets(const FNiagaraEmitterInstance* InEmitter, TArray<TSharedPtr<SWidget>>& OutWidgets, TSharedPtr<FAssetThumbnailPool> InThumbnailPool) const override;`
- L86 _public prototype_ `virtual const FSlateBrush* GetStackIcon() const override;`
- L87 _public prototype_ `virtual void GetRendererTooltipWidgets(const FNiagaraEmitterInstance* InEmitter, TArray<TSharedPtr<SWidget>>& OutWidgets, TSharedPtr<FAssetThumbnailPool> InThumbnailPool) const override;`
- L88 _public prototype_ `virtual const TArray<FNiagaraVariable>& GetOptionalAttributes() override;`
- L89 _public prototype_ `virtual void GetRendererFeedback(const FVersionedNiagaraEmitter& InEmitter, TArray<FNiagaraRendererFeedback>& OutErrors, TArray<FNiagaraRendererFeedback>& OutWarnings, TArray<FNiagaraRendererFeedback>& OutInfo) const override;`
- L90 _public prototype_ `virtual TArray<FNiagaraVariable> GetBoundAttributes() const override;`
- L91 _public prototype_ `virtual void RenameVariable(const FNiagaraVariableBase& OldVariable, const FNiagaraVariableBase& NewVariable, const FVersionedNiagaraEmitterBase& InEmitter) override;`
- L92 _public prototype_ `virtual void RemoveVariable(const FNiagaraVariableBase& OldVariable, const FVersionedNiagaraEmitterBase& InEmitter) override;`
- L95 _public prototype_ `void UpdateMICs();`
- L97 _public prototype_ `static UGeometryCache* ResolveGeometryCache(const FNiagaraGeometryCacheReference& Entry, const FNiagaraEmitterInstance* Emitter);`
- L101 _public member_ `TArray<FNiagaraGeometryCacheReference> GeometryCaches;` — `UPROPERTY(EditAnywhere, Category = "GeometryCache")` — Reference to the geometry cache assets to use. If ArrayIndexBinding is not set, a random element is used for each particle.
- L105 _public member_ `ENiagaraRendererSourceDataMode SourceMode = ENiagaraRendererSourceDataMode::Particles;` — `UPROPERTY(EditAnywhere, Category = "GeometryCache")` — Whether or not to draw a single element for the Emitter or to draw the particles.
- L109 _public member_ `bool bIsLooping = true;` — `UPROPERTY(EditAnywhere, Category = "GeometryCache")` — If true, then the geometry cache keeps playing in a loop
- L113 _public member_ `uint32 ComponentCountLimit = 15;` — `UPROPERTY(EditAnywhere, Category = "GeometryCache", meta = (ClampMin = 1))` — The max number of components that this emitter will spawn or update each frame.
- L117 _public member_ `FNiagaraVariableAttributeBinding PositionBinding;` — `UPROPERTY(EditAnywhere, Category = "GeometryCache")` — Which attribute should we use for the geometry cache position?
- L121 _public member_ `FNiagaraVariableAttributeBinding RotationBinding;` — `UPROPERTY(EditAnywhere, Category = "GeometryCache")` — Which attribute should we use for the geometry cache rotation?
- L125 _public member_ `FNiagaraVariableAttributeBinding ScaleBinding;` — `UPROPERTY(EditAnywhere, Category = "GeometryCache")` — Which attribute should we use for the geometry cache component scale?
- L129 _public member_ `FNiagaraVariableAttributeBinding ElapsedTimeBinding;` — `UPROPERTY(EditAnywhere, Category = "GeometryCache")` — Which attribute should we use for the geometry cache's current animation time?
- L133 _public member_ `FNiagaraVariableAttributeBinding EnabledBinding;` — `UPROPERTY(EditAnywhere, Category = "GeometryCache")` — Which attribute should we use to check if rendering should be enabled?
- L137 _public member_ `FNiagaraVariableAttributeBinding ArrayIndexBinding;` — `UPROPERTY(EditAnywhere, Category = "GeometryCache")` — Which attribute should we use to pick the element in the geometry cache array for this renderer? If not set, a random element will be used.
- L141 _public member_ `FNiagaraVariableAttributeBinding RendererVisibilityTagBinding;` — `UPROPERTY(EditAnywhere, Category = "GeometryCache")` — Which attribute should we use for the renderer visibility tag?
- L145 _public member_ `int32 RendererVisibility;` — `UPROPERTY(EditAnywhere, Category = "GeometryCache")` — If a render visibility tag is present, particles whose tag matches this value will be visible in this renderer.
- L150 _public member_ `bool bAssignComponentsOnParticleID = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "GeometryCache")` — If true then components will not be automatically assigned to the first particle available, but try to stick to the same particle based on its unique id. Disabling this option is faster, but a particle can get a different component each tick, which can lead to problems with for example motion blur.
- L154 _public member_ `TEnumAsByte<ECollisionEnabled::Type> EnableCollision = ECollisionEnabled::NoCollision;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Component")` — Determines if the geometry component will affect the engine's physics system with its collision shape.
- L158 _public member_ `bool bAffectsNavigation = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Component")` — If true then the geometry component will invalidate the nav mesh on movement.
- L162 _public member_ `FNiagaraRendererMaterialParameters MaterialParameters;` — `UPROPERTY(EditAnywhere, Category = "Bindings")` — If this array has entries, we will create a MaterialInstanceDynamic per Emitter instance from Material and set the Material parameters using the Niagara simulation variables listed.
- L164 _public member_ `FNiagaraDataSetAccessor<FNiagaraPosition> PositionAccessor;`
- L165 _public member_ `FNiagaraDataSetAccessor<FVector3f> RotationAccessor;`
- L166 _public member_ `FNiagaraDataSetAccessor<FVector3f> ScaleAccessor;`
- L167 _public member_ `FNiagaraDataSetAccessor<float> ElapsedTimeAccessor;`
- L168 _public member_ `FNiagaraDataSetAccessor<FNiagaraBool> EnabledAccessor;`
- L169 _public member_ `FNiagaraDataSetAccessor<int32> ArrayIndexAccessor;`
- L170 _public member_ `FNiagaraDataSetAccessor<int32> VisTagAccessor;`
- L171 _public member_ `FNiagaraDataSetAccessor<int32> UniqueIDAccessor;`
- L173 _public function_ `virtual bool NeedsSystemPostTick() const override`
- L174 _public function_ `virtual bool NeedsSystemCompletion() const override`
- L177 _protected prototype_ `void InitBindings();`
- L179 _protected member_ `static FNiagaraVariable Particles_GeoCacheRotation;`
- L180 _protected member_ `static FNiagaraVariable Particles_Age;`
- L181 _protected member_ `static FNiagaraVariable Particles_GeoCacheIsEnabled;`
- L182 _protected member_ `static FNiagaraVariable Particles_ArrayIndex;`
- L184 _protected prototype_ `static void InitDefaultAttributes();`
- L186 _private member_ `static TArray<TWeakObjectPtr<UNiagaraGeometryCacheRendererProperties>> GeometryCacheRendererPropertiesToDeferredInit;`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/NiagaraRendererGeometryCache.h` (Public)


#### class `FNiagaraRendererGeometryCache`  
`class FNiagaraRendererGeometryCache : public FNiagaraRenderer`  
_L18-61_
- inherits: `FNiagaraRenderer`
- desc: NiagaraRendererGeometryCache renders a geometry cache asset
- L22 _public prototype_ `FNiagaraRendererGeometryCache(ERHIFeatureLevel::Type FeatureLevel, const UNiagaraRendererProperties *InProps, const FNiagaraEmitterInstance* Emitter);`
- L23 _public prototype_ `virtual ~FNiagaraRendererGeometryCache();`
- L26 _public prototype_ `virtual void Initialize(const UNiagaraRendererProperties* InProps, const FNiagaraEmitterInstance* Emitter, const FNiagaraSystemInstanceController& InController) override;` — FNiagaraRenderer interface
- L27 _public prototype_ `virtual void DestroyRenderState_Concurrent() override;`
- L28 _public prototype_ `virtual void PostSystemTick_GameThread(const UNiagaraRendererProperties* InProperties, const FNiagaraEmitterInstance* Emitter) override;`
- L29 _public prototype_ `virtual void OnSystemComplete_GameThread(const UNiagaraRendererProperties* InProperties, const FNiagaraEmitterInstance* Emitter) override;`
- L41 _private prototype_ `UGeometryCacheComponent* CreateOrGetPooledComponent( const UNiagaraGeometryCacheRendererProperties* Properties, USceneComponent* AttachComponent, const FNiagaraEmitterInstance* Emitter, TOptional<int32> DefaultCacheIndex, uint32 ParticleIndex, int32 ParticleID, int32& InOutPoolIndex );`
- L51 _private prototype_ `void ResetComponentPool(bool bResetOwner);`
- L54 _private member_ `TWeakObjectPtr<AActor> SpawnedOwner;` — if the niagara component is not attached to an actor, we need to spawn and keep track of a temporary actor
- L57 _private member_ `TArray<FComponentPoolEntry> ComponentPool;` — all of the spawned components
- L60 _private member_ `TArray<TArray<int32>> MaterialRemapTable;` — Used to remap materials into the compact list so we can use MIDs

#### struct `FNiagaraRendererGeometryCache::FComponentPoolEntry`  
`struct FComponentPoolEntry`  
_L33-39_
- L35 _public member_ `TWeakObjectPtr<UGeometryCacheComponent> Component;`
- L36 _public member_ `float LastActiveTime = 0.0f;`
- L37 _public member_ `float LastElapsedTime = 0.0f;`
- L38 _public member_ `int32 LastAssignedToParticleID = -1;`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Private/CodecV1.h` (Private)


#### class `FQualityMetric2D`  
`class FQualityMetric2D`  
_L15-41_
- desc: Quality metric to calculate Mean Square Error between 2D vectors
- L19 _public function_ `FQualityMetric2D() : SumSquaredX(0.0), SumSquaredY(0.0), Num(0)`
- L23 _public function_ `FORCEINLINE void Register(const FVector2f& Coded, const FVector2f& Original)`
- L31 _public function_ `FORCEINLINE float ReadMSE()` — Mean Squared Error
- L38 _private member_ `double SumSquaredX;`
- L39 _private member_ `double SumSquaredY;`
- L40 _private member_ `uint64 Num;`

#### class `FQualityMetric`  
`class FQualityMetric`  
_L44-72_
- desc: Quality metric to calculate Mean Square Error between vectors
- L48 _public function_ `FQualityMetric() : SumSquaredX(0.0), SumSquaredY(0.0), SumSquaredZ(0.0), Num(0)`
- L52 _public function_ `FORCEINLINE void Register(const FVector3f& Coded, const FVector3f& Original)`
- L61 _public function_ `FORCEINLINE float ReadMSE()` — Mean Squared Error
- L68 _private member_ `double SumSquaredX;`
- L69 _private member_ `double SumSquaredY;`
- L70 _private member_ `double SumSquaredZ;`
- L71 _private member_ `uint64 Num;`

#### struct `FCodecV1DecodingContext`  
`struct FCodecV1DecodingContext`  
_L78-91_
- desc: Any context information to decode a frame in a sequence of frames
- L81 _public member_ `FGeometryCacheMeshData* MeshData;` — Target mesh to decode to
- L83 _public member_ `FHuffmanDecodeTable ResidualIndicesTable;` — Huffman tables
- L84 _public member_ `FHuffmanDecodeTable ResidualVertexPosTable;`
- L85 _public member_ `FHuffmanDecodeTable ResidualImportedVertexNumbersTable;`
- L86 _public member_ `FHuffmanDecodeTable ResidualColorTable;`
- L87 _public member_ `FHuffmanDecodeTable ResidualNormalTangentXTable;`
- L88 _public member_ `FHuffmanDecodeTable ResidualNormalTangentZTable;`
- L89 _public member_ `FHuffmanDecodeTable ResidualUVTable;`
- L90 _public member_ `FHuffmanDecodeTable ResidualMotionVectorTable;`

#### struct `FCodecV1EncoderConfig`  
`struct FCodecV1EncoderConfig`  
_L94-115_
- desc: Configuration settings for the encoder
- L100 _public member_ `float VertexQuantizationPrecision;` — Vertex quantization precision. Each vertex' position is quantized with bin sizes equal to this size, i.e., the full range of the vertex positions is discretized with steps equal in size of this value. E.g., steps 0.1 corresponds to bin sizes of 1 cubic millimeter as 1 unit equals 1 cm. The lower this number, the higher the precision of the vertex positions, but the lower the compression ratio becomes.
- L106 _public member_ `int32 UVQuantizationBitRange;` — Texture coordinate quantization bit range (for the fractional part). Each vertex' texture coordinate is quantized to this bit range, e.g., set to 10 bit, the range [0-1] is mapped to 1024 equal bins. Any range outside [0-1] will be quantized with 'UVQuantizationBitRange' bits for the fraction part, and will need use extra bits for the non-fraction part, e.g., UDIM range [0-6] will use 10+3 bits instead.
- L108 _public function_ `static FCodecV1EncoderConfig DefaultConfig()`

#### struct `FCodecV1EncodingContext`  
`struct FCodecV1EncodingContext`  
_L118-136_
- desc: Any context information to code a frame in a sequence of frames
- L121 _public member_ `bool bPrepass;` — Are we in prepass mode, we do not write anything in prepass mode, only calculate statistics
- L123 _public member_ `const FGeometryCacheMeshData* MeshData;` — Mesh to code
- L125 _public member_ `FHuffmanBitStreamWriter* Writer;` — Huffman bit writer to write bitstream to
- L127 _public member_ `FHuffmanEncodeTable ResidualIndicesTable;` — Huffman tables
- L128 _public member_ `FHuffmanEncodeTable ResidualVertexPosTable;`
- L129 _public member_ `FHuffmanEncodeTable ResidualImportedVertexNumbersTable;`
- L130 _public member_ `FHuffmanEncodeTable ResidualColorTable;`
- L131 _public member_ `FHuffmanEncodeTable ResidualColorSkipTable;`
- L132 _public member_ `FHuffmanEncodeTable ResidualNormalTangentXTable;`
- L133 _public member_ `FHuffmanEncodeTable ResidualNormalTangentZTable;`
- L134 _public member_ `FHuffmanEncodeTable ResidualUVTable;`
- L135 _public member_ `FHuffmanEncodeTable ResidualMotionVectorTable;`

#### class `FCodecV1SharedTools`  
`class FCodecV1SharedTools`  
_L149-163_
- desc: Shared functionality between encoder and decoder
- L153 _public function_ `static FORCEINLINE FIntVector4 SumVector4(const FIntVector4& First, const FIntVector4& Second)` — Sum two IntVector4 vectors, because IntVector4 does not implement arithmetic operations contrary to IntVector
- L159 _public function_ `static FORCEINLINE FIntVector4 SubtractVector4(const FIntVector4& First, const FIntVector4& Second)` — Subtract two IntVector4 vectors, because IntVector4 does not implement arithmetic operations contrary to IntVector

#### struct `FStreamEncodingStatistics`  
`struct FStreamEncodingStatistics`  
_L166-179_
- desc: Statistics on encoding of a single stream/buffer
- L168 _public member_ `uint32 CodedNumBytes;`
- L169 _public member_ `uint32 RawNumBytes;`
- L170 _public member_ `float CompressionRatio;`
- L171 _public member_ `float Quality;`
- L173 _public function_ `FStreamEncodingStatistics() : CodedNumBytes(0), RawNumBytes(0), CompressionRatio(0.0f), Quality(0.0f)`
- L175 _public function_ `FStreamEncodingStatistics(uint32 SetCodedNumBytes, uint32 SetRawNumBytes, float SetQuality) : CodedNumBytes(SetCodedNumBytes), RawNumBytes(SetRawNumBytes), Quality(SetQuality)`

#### class `FCodecV1Encoder`  
`class FCodecV1Encoder : public ICodecEncoder`  
_L182-281_
- inherits: `ICodecEncoder`
- L185 _public prototype_ `FCodecV1Encoder();`
- L186 _public prototype_ `FCodecV1Encoder(const FCodecV1EncoderConfig& Config);`
- L194 _public prototype_ `bool EncodeFrameData(FMemoryWriter& Writer, const FGeometryCacheCodecEncodeArguments &Args);` — Encode a frame and write the bitstream @param Writer - Writer for the output bit stream @param Args - Encoding arguments
- L198 _private prototype_ `bool EncodeFrameData(FMemoryWriter &Writer, const FGeometryCacheMeshData& MeshData, bool bPrepass);` — Encode a single frame in or not in prepass mode and write to the bitstream
- L201 _private prototype_ `void EncodeIndexStream(const uint32* Stream, uint64 ElementOffsetBytes, uint32 ElementCount, FStreamEncodingStatistics& Stats);` — Encode a buffer with vertex indices
- L203 _private prototype_ `void EncodePositionStream(const FVector3f* VertexStream, uint64 VertexElementOffset, uint32 VertexElementCount, FStreamEncodingStatistics& Stats);` — Encode a buffer with vertex positions
- L205 _private prototype_ `void EncodeColorStream(const FColor* Stream, uint64 ElementOffsetBytes, uint32 ElementCount, FStreamEncodingStatistics& Stats);` — Encode a buffer with vertex colors
- L207 _private prototype_ `void EncodeNormalStream(const FPackedNormal* Stream, uint64 ElementOffsetBytes, uint32 ElementCount, FHuffmanEncodeTable& Table, FStreamEncodingStatistics& Stats);` — Encode a buffer with vertex normals
- L209 _private prototype_ `void EncodeUVStream(const FVector2f* Stream, uint64 ElementOffsetBytes, uint32 ElementCount, FStreamEncodingStatistics& Stats);` — Encode a buffer with vertex texture coordinates
- L211 _private prototype_ `void EncodeMotionVectorStream(const FVector3f* Stream, uint64 ElementOffsetBytes, uint32 ElementCount, FStreamEncodingStatistics& Stats);` — Encode a buffer with vertex motion vectors
- L214 _private prototype_ `FORCEINLINE FIntVector FindModeAndPredictVertex(const FIntVector& ValueToCode, uint32 CornerIndex, uint32 PreviousTriangleRotationOffsets[3], FRingBuffer<FIntVector, VertexStreamCodingVertexHistorySize>& ReconstructedVertexHistory, uint32& ChosenMode);` — Find the best prediction mode for a vertex position and predict according to that mode
- L217 _private prototype_ `void SetupTables();` — Setup and write the Huffman coding tables
- L218 _private prototype_ `void WriteTables();`
- L221 _private prototype_ `void SetPrepass(bool bPrepass);` — Set the prepass mode to Huffman tables and any other internal state
- L224 _private prototype_ `void WriteBytes(const void* Data, int64 Num);` — Write a given number of bytes to the bit stream using the Huffman bit writer
- L227 _private prototype_ `void WriteInt32(FHuffmanEncodeTable& ValueTable, int32 Value);` — Write a 32-bit signed value from the bit stream using a Huffman coder
- L230 _private function_ `FORCEINLINE void WriteBits(int32 Data, uint32 NumBits)` — Write a given number of bits to the bit stream using the Huffman bit writer
- L241 _private function_ `FORCEINLINE void WriteSymbol(FHuffmanEncodeTable& table, int32 symbol)` — Write a symbol to the bit stream using a Huffman Table
- L248 _private function_ `FORCEINLINE static int32 HighestSetBit(uint32 Value)` — Zero based index of the highest one bit
- L255 _private prototype_ `void WriteCodedStreamDescription();` — Write which streams are coded in the bit stream
- L258 _private member_ `FCodecV1EncodingContext EncodingContext;` — Any context information to code a frame in a sequence of frames
- L260 _private member_ `FCodecV1EncoderConfig Config;` — Configuration settings for the encoder, e.g., quality settings
- L280 _private member_ `} Statistics;`

#### struct `FCodecV1Encoder::FEncoderStatistics`  
`struct FEncoderStatistics`  
_L264-280_
- desc: Statistics of the encoding process and individual streams. Primarily used during development, a select number can be changed to UE-specific counters
- L266 _public function_ `FEncoderStatistics() : NumVertices(0), DurationMs(0.0f), HuffmanTablesNumBytes(0)`
- L268 _public member_ `FStreamEncodingStatistics Indices;`
- L269 _public member_ `FStreamEncodingStatistics Vertices;`
- L270 _public member_ `FStreamEncodingStatistics ImportedVertexNumbers;`
- L271 _public member_ `FStreamEncodingStatistics Colors;`
- L272 _public member_ `FStreamEncodingStatistics TangentX;`
- L273 _public member_ `FStreamEncodingStatistics TangentY;`
- L274 _public member_ `FStreamEncodingStatistics TexCoords;`
- L275 _public member_ `FStreamEncodingStatistics MotionVectors;`
- L276 _public member_ `FStreamEncodingStatistics All;`
- L277 _public member_ `uint32 NumVertices;`
- L278 _public member_ `float DurationMs;`
- L279 _public member_ `uint32 HuffmanTablesNumBytes;`

#### class `FCodecV1Decoder`  
`class FCodecV1Decoder : public ICodecDecoder`  
_L285-348_
- inherits: `ICodecDecoder`
- L288 _public function_ `FCodecV1Decoder()`
- L290 _public prototype_ `static void InitLUT();`
- L298 _public prototype_ `virtual bool DecodeFrameData(FBufferReader &Reader, FGeometryCacheMeshData &OutMeshData);` — Read a frame's bit stream and decode the frame @param Reader - Reader holding the frame's bit stream @param OutMeshData - Decoded mesh
- L302 _private prototype_ `void DecodeIndexStream(FHuffmanBitStreamReader& Reader, uint32* Stream, uint64 ElementOffset, uint32 ElementCount);` — Decode a buffer of vertex indices from abitstream
- L304 _private prototype_ `void DecodePositionStream(FHuffmanBitStreamReader& Reader, FVector3f* VertexStream, uint64 VertexElementOffset, uint32 VertexElementCount);` — Decode a buffer of vertex positions from a bitstream
- L306 _private prototype_ `void DecodeColorStream(FHuffmanBitStreamReader& Reader, FColor* Stream, uint64 ElementOffset, uint32 ElementCount);` — Decode a buffer of vertex colors from a bitstream
- L308 _private prototype_ `void DecodeNormalStream(FHuffmanBitStreamReader& Reader, FPackedNormal* Stream, uint64 ElementOffset, uint32 ElementCount, FHuffmanDecodeTable& Table);` — Decode a buffer of vertex normals from a bitstream
- L310 _private prototype_ `void DecodeUVStream(FHuffmanBitStreamReader& Reader, FVector2f* Stream, uint64 ElementOffset, uint32 ElementCount);` — Decode a buffer of vertex texture coordinates from a bitstream
- L312 _private prototype_ `void DecodeMotionVectorStream(FHuffmanBitStreamReader& Reader, FVector3f* Stream, uint64 ElementOffset, uint32 ElementCount);` — Decode a buffer of vertex motion vectors from a bitstream
- L315 _private prototype_ `void SetupAndReadTables(FHuffmanBitStreamReader& Reader);` — Initialize and read Huffman tables from a bitstream
- L318 _private prototype_ `FORCEINLINE void ReadBytes(FHuffmanBitStreamReader& Reader, void* Data, uint32 NumBytes);` — Read a given number of bytes from a bit stream using a Huffman bitreader
- L321 _private prototype_ `FORCEINLINE int32 ReadInt32(FHuffmanBitStreamReader& Reader, FHuffmanDecodeTable& ValueTable);` — Read a 32-bit signed value from a bit stream using a Huffman coder
- L324 _private function_ `FORCEINLINE int32 ReadSymbol(FHuffmanBitStreamReader& Reader, FHuffmanDecodeTable& table)` — Read a symbol from a bit stream using a Huffman Table
- L330 _private function_ `FORCEINLINE int32 ReadBits(FHuffmanBitStreamReader& Reader, uint32 NumBits)` — Read a given number of bits from a bit stream
- L336 _private function_ `FORCEINLINE int32 ReadBitsNoRefill(FHuffmanBitStreamReader& Reader, uint32 NumBits)` — Read a given number of bits from a bit stream without refilling bits
- L342 _private prototype_ `void ReadCodedStreamDescription(FHuffmanBitStreamReader& Reader, uint32 Version);` — Read info on the available streams from a bit stream
- L345 _private member_ `FCodecV1DecodingContext DecodingContext;` — Any context information to decode a frame in a sequence of frames, such as any Huffman tables used.
- L347 _private member_ `static int32 CachedHighBitsLUT[64];`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeoCaStreamingCodecV1, Verbose, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeoCaStreamingCodecV1, Verbose, All);`
- L138 _variable_ `const int32 HuffmanTableInt32SymbolCount = 64;` — 31 negative lengths, zero, 32 positive length
- L139 _variable_ `const int32 HuffmanTableInt8SymbolCount = 256;`
- L140 _variable_ `const uint32 VertexStreamCodingIndexHistorySize = 9;` — Sizes of the previously-seen histories used for prediction of the various stream elements
- L141 _variable_ `const uint32 VertexStreamCodingVertexHistorySize = 9;`
- L142 _variable_ `const uint32 IndexStreamCodingHistorySize = 5;`
- L143 _variable_ `const uint32 ColorStreamCodingHistorySize = 5;`
- L144 _variable_ `const uint32 NormalStreamCodingHistorySize = 5;`
- L145 _variable_ `const uint32 UVStreamCodingHistorySize = 9;`
- L146 _variable_ `const uint32 MotionVectorStreamCodingHistorySize = 9;`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Private/CodecV1Test.h` (Private)


#### class `CodecV1Test`  
`class CodecV1Test`  
_L15-166_
- desc: Testing functionality to write raw mesh data to file, read it in a testing scenario and run encoder and decoder on the frames. Outputs frame_%i_raw.dump, frame_%i_encoded.dump, frame_%i_decoded.dump.
- L18 _public function_ `CodecV1Test(const FString& FrameDirectoryPath)`
- L30 _public function_ `static void TestEncoder(int32 FrameIndex, const FString& FrameDirectoryPath, const FCodecV1EncoderConfig& Config)`
- L53 _public function_ `static void TestDecoder(int32 FrameIndex, const FString& FrameDirectoryPath)`
- L74 _public function_ `static void CompareData(int32 FrameIndex, const FString& FrameDirectoryPath)`
- L143 _public function_ `static void WriteRawMeshDataToFile(const FGeometryCacheMeshData& MeshData, const FString& FileName)`
- L153 _public function_ `static bool ReadRawMeshDataFromFile(FGeometryCacheMeshData& MeshData, const FString& FileName)`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Private/FloatCompression.h` (Private)
_(no declarations extracted)_

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Private/GeometryCachePreprocessor.h` (Private)


#### class `FGeometryCachePreprocessor`  
`class FGeometryCachePreprocessor`  
_L15-34_
- desc: A generic object that preprocesses frames coming from the geometry cache importer and transforms them. The processed frames are then passed on to another preprocessor. The final preprocessor in the chain then calls the codec.
- L22 _public function_ `FGeometryCachePreprocessor(FGeometryCachePreprocessor* SetDownStreamProcessor) : DownStreamProcessor(SetDownStreamProcessor)` — @param DownStreamProcessor The processor to pass processed results to. The processor will be owned by this object and deleted then it is destroyed.
- L23 _public function_ `virtual ~FGeometryCachePreprocessor()`
- L30 _public prototype_ `virtual void AddMeshSample(const FGeometryCacheMeshData& MeshData, const float SampleTime, bool bSameTopologyAsPrevious) = 0;`
- L33 _protected member_ `FGeometryCachePreprocessor* DownStreamProcessor;`

#### class `FCodecGeometryCachePreprocessor`  
`class FCodecGeometryCachePreprocessor : public FGeometryCachePreprocessor`  
_L36-43_
- inherits: `FGeometryCachePreprocessor`
- L39 _public function_ `FCodecGeometryCachePreprocessor(UGeometryCacheTrackStreamable *SetTrack) : FGeometryCachePreprocessor(NULL), Track(SetTrack)`
- L40 _public prototype_ `virtual void AddMeshSample(const FGeometryCacheMeshData& MeshData, const float SampleTime, bool bSameTopologyAsPrevious) override;`
- L42 _protected member_ `UGeometryCacheTrackStreamable *Track;`

#### class `FOptimizeGeometryCachePreprocessor`  
`class FOptimizeGeometryCachePreprocessor : public FGeometryCachePreprocessor`  
_L50-92_
- inherits: `FGeometryCachePreprocessor`
- desc: This is a class that is shared by all codecs and does some things like mesh sanitization and other preprocessing tasks before handling the actual mesh to the codecs. This allows common preprocessing tasks to be shared across codecs and allows the codecs to assume a certain guaranteed level of mesh sanitization without putting too much burden on the individual importers.
- L62 _public prototype_ `FOptimizeGeometryCachePreprocessor(FGeometryCachePreprocessor* SetDownStreamProcessor, bool bSetForceSingleOptimization, bool bInOptimizeIndexBuffers);` — @param SetDownStreamProcessor The downstream processor to pass results to @param bSetForceSingleOptimization Only run the optimization phase of the preprocessor once. With generic meshes optimizing without looking at the whole mesh can give some invalid results (eg. triangles drifting apart, changing smoothing groups for normals in animations, ....) this flag tells the system it's ok to ignore all this and just run the optimization once then reuse the results for all frames. This may lead to strange artifacts such as parts drifting apart still being connected by triangles, smoothing group creases not appearing, ... but in for well behaved meshes it's probably going to be almost invisible.
- L65 _public prototype_ `void AddMeshSample(const FGeometryCacheMeshData& MeshData, const float SampleTime, bool bSameTopologyAsPrevious) override;`
- L75 _protected member_ `TArray<FBufferedFrame> BufferedFrames;`
- L76 _protected member_ `int NumFramesInBuffer;`
- L78 _protected prototype_ `void FlushBufferedFrames();`
- L79 _protected prototype_ `bool AreIndexedVerticesEqual(int32 IndexBufferIndexA, int32 IndexBufferIndexB);`
- L83 _protected member_ `IMeshUtilities& MeshUtilities;` — We have to cache the mesh utilities here since we can't load modules from other threads and AddMeshSample is possibly called from worker threads
- L85 _protected member_ `bool bForceSingleOptimization;`
- L86 _protected member_ `bool bOptimizeIndexBuffers;`
- L89 _protected member_ `TArray<uint32> NewIndices;` — These contain the optimization results and are cached when bForceSingleOptimization is forced
- L90 _protected member_ `TArray<int32> NewVerticesReordered;`

#### struct `FOptimizeGeometryCachePreprocessor::FBufferedFrame`  
`struct FBufferedFrame`  
_L69-73_
- L71 _public member_ `float Time;`
- L72 _public member_ `FGeometryCacheMeshData MeshData;`

#### class `FExplicitMotionVectorGeometryCachePreprocessor`  
`class FExplicitMotionVectorGeometryCachePreprocessor : public FGeometryCachePreprocessor`  
_L99-114_
- inherits: `FGeometryCachePreprocessor`
- desc: Adds explicit motion vectors to a mesh by taking the difference between consecutive frames. Any frames which already have explicit motion vectors specified will use these existing motion vectors instead of deriving them.
- L103 _public function_ `FExplicitMotionVectorGeometryCachePreprocessor(FGeometryCachePreprocessor* SetDownStreamProcessor) : FGeometryCachePreprocessor(SetDownStreamProcessor), bHasPreviousFrame(false)`
- L106 _public prototype_ `void AddMeshSample(const FGeometryCacheMeshData& MeshData, const float SampleTime, bool bSameTopologyAsPrevious) override;`
- L109 _protected member_ `FGeometryCacheMeshData PreviousFrame;`
- L110 _protected member_ `float PreviousFrameTime;`
- L111 _protected member_ `bool bHasPreviousFrame;`
- L112 _protected member_ `bool bPreviousTopologySame;`
- L113 _protected prototype_ `void FlushBufferedFrame();`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Private/GeometryCacheStreamingManager.h` (Private)


#### struct `FGeometryCacheRequest`  
`struct FGeometryCacheRequest`  
_L14-18_
- desc: Contains a request to load chunks of a geometry cache
- L16 _public member_ `TArray<uint32> RequiredIndices;`
- L17 _public member_ `bool bPrioritiseRequest;`

#### struct `IGeometryCacheStreamingManager`  
`struct IGeometryCacheStreamingManager : public IStreamingManager`  
_L24-85_
- inherits: `IStreamingManager`
- desc: Note IStreamingManager is not really anything like an interface it contains code and members and whatnot. So we just play along here to keep the spirit of the existing audio and texture streaming managers.
- L26 _public function_ `IGeometryCacheStreamingManager()`
- L29 _public prototype_ `virtual ~IGeometryCacheStreamingManager() = default;` — Virtual destructor
- L32 _public prototype_ `static struct IGeometryCacheStreamingManager& Get();` — Getter of the singleton
- L35 _public prototype_ `static void Register();` — Streaming manager interface registration enrollment
- L38 _public prototype_ `static void Unregister();` — Streaming manager interface registration removal
- L41 _public prototype_ `virtual void AddGeometryCache(UGeometryCacheTrackStreamable* Cache) = 0;` — Adds a new cache to the streaming manager.
- L44 _public prototype_ `virtual void RemoveGeometryCache(UGeometryCacheTrackStreamable* Cache) = 0;` — Removes a cache from the streaming manager.
- L47 _public prototype_ `virtual bool IsManagedGeometryCache(const UGeometryCacheTrackStreamable* Cache) const = 0;` — Returns true if this is a cache is managed by the streaming manager.
- L50 _public prototype_ `virtual bool IsStreamingInProgress(const UGeometryCacheTrackStreamable* Cache) = 0;` — Returns true if this data for this track is currently streaming.
- L53 _public prototype_ `virtual void AddStreamingComponent(UGeometryCacheComponent* CacheComponent) = 0;` — Adds a new component to the streaming manager.
- L56 _public prototype_ `virtual void RemoveStreamingComponent(UGeometryCacheComponent* CacheComponent) = 0;` — Removes the component from the streaming manager.
- L60 _public prototype_ `virtual void PrefetchData(UGeometryCacheComponent* CacheComponent) = 0;` — Prefetch data for the current state component. Data is automatically prefetched when initially registering the component this may be useful when the component has seeked etc.
- L63 _public prototype_ `virtual bool IsManagedComponent(const UGeometryCacheComponent* CacheComponent) const = 0;` — Returns true if this is a streaming component that is managed by the streaming manager.
- L73 _public prototype_ `virtual const uint8* MapChunk(const UGeometryCacheTrackStreamable* Track, uint32 ChunkIndex, uint32* OutChunkSize = nullptr ) = 0;` — Gets a pointer to a chunk of cached geometry data. Can be called from any thread. @param Track Animation track we want a chunk from @param ChunkIndex	Index of the chunk we want @param OutChunkSize If non-null tores the size in bytes of the chunk @return Either the desired chunk or NULL if it's not loaded
- L82 _public prototype_ `virtual void UnmapChunk(const UGeometryCacheTrackStreamable* Track, uint32 ChunkIndex) = 0;` — Releases pointer to a chunk of cahed geometry data. Can be called from any thread. Should be called for every call to MapChunk. @param Track Animation track we want a chunk from @param ChunkIndex	Index of the chunk we want
- L84 _public member_ `FThreadSafeCounter IoBandwidth;`

#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeoCaStreaming, Verbose, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeoCaStreaming, Verbose, All);`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Private/HuffmanBitStream.h` (Private)


#### class `FHuffmanBitStreamWriter`  
`class FHuffmanBitStreamWriter`  
_L13-115_
- desc: A bit stream writer class for use with the Huffman coding. This class allows coding arbitrary sized integers up to 32 bits in size. The bits are written in Little-endian order.
- L20 _public function_ `FHuffmanBitStreamWriter()` — Create a writer. The class will automatically grow it's internal byte buffer used to store the bits.
- L28 _public function_ `void Clear()` — Reset the writer as if it was freshly created. All written data will be discarded.
- L40 _public function_ `void Write(uint32 Bits, uint32 InNumBits)` — Write an NumBits integer value to the stream.
- L60 _public function_ `void Align()` — Flush pending bits and align to byte.
- L75 _public function_ `void Close()` — Close the stream. This ensures the stream's underlying byte buffer is correctly flushed with all bits written to the stream. Once closed you cannot longer Write additional data on the stream.
- L87 _public function_ `const TArray<uint8> &GetBytes()` — Get the bytes corresponding to this stream. The destination will be overwritten with the bytes for this stream. This can only be called on a flushed stream.
- L96 _public function_ `uint32 GetNumBytes() const` — Get the number of bytes written into the stream so far.
- L104 _public function_ `uint32 GetNumBits() const` — Get the number of bits written into the stream so far.
- L110 _private member_ `TArray<uint8> Bytes;`
- L111 _private member_ `uint64 BitBuffer;`
- L112 _private member_ `uint32 BitBufferBits;`
- L113 _private member_ `uint32 NumBits;`
- L114 _private member_ `bool bFlushed;`

#### class `FBitstreamWriterByteCounter`  
`class FBitstreamWriterByteCounter`  
_L120-141_
- desc: Helper class to keep track of the amount of bits written by the BitstreamWriter
- L123 _public function_ `FBitstreamWriterByteCounter(const FHuffmanBitStreamWriter* SetWriter) : StartNumBits(0), StartNumBytes(0), Writer(SetWriter)`
- L132 _public function_ `uint32 Read()` — Returns the amount of bytes written since this object was constructed
- L138 _private member_ `uint32 StartNumBits;`
- L139 _private member_ `uint32 StartNumBytes;`
- L140 _private member_ `const FHuffmanBitStreamWriter* Writer;`

#### class `FHuffmanBitStreamReader`  
`class FHuffmanBitStreamReader`  
_L143-263_
- L151 _public function_ `FHuffmanBitStreamReader(const uint8* InBytes, uint32 InNumBytes)` — Initialize the stream for reading with the specified data bytes. The bitstream doesn't own the data, so the caller is responsible for keeping the data valid while reader is active. Additionally the caller is responsible for over-allocating the buffer by 16 bytes, so we can safely read the data as uint64s. 16 bytes and not 8 bytes, because the input pointer can move 8 bytes past the data and perform a 8 byte read from there.
- L161 _public function_ `void Reset()` — Restart reading from the stream. Reading will begin anew from the start of the stream.
- L172 _public function_ `FORCEINLINE void Refill()` — Fill the internal bit buffer. Will not check against buffer bounds, so make sure the input buffer is large enough to read all the bits requested +16 bytes. After the call the bit buffer is guaranteed to contain at least MINIMUM_BITS_AFTER_REFILL valid bits.
- L196 _public function_ `FORCEINLINE uint32 Read()` — Read a the next bit from the stream.
- L204 _public function_ `FORCEINLINE uint32 Read(uint32 NumBits)` — Read the next NumBits from the stream.
- L216 _public function_ `FORCEINLINE uint32 ReadNoRefill(uint32 NumBits)` — Read the next NumBits from the stream without refilling the bit buffer.
- L227 _public function_ `FORCEINLINE void SkipNoRefill(uint32 NumBits)` — Read the next NumBits from the stream without refilling the bit buffer.
- L236 _public function_ `FORCEINLINE int32 Peek(uint32 NumBits)` — Return the next NumBits in the stream but do not advance the read position.
- L245 _public function_ `FORCEINLINE int32 PeekNoRefill(uint32 NumBits)` — Return the next NumBits in the stream but do not advance the read position without refilling the bit buffer.
- L253 _public function_ `FORCEINLINE int32 GetNumBytes()` — Get the total number of bytes in the stream.
- L258 _private member_ `const uint8* Bytes;`
- L259 _private member_ `uint64 NumBytes;`
- L260 _private member_ `uint64 BitBuffer;`
- L261 _private member_ `uint32 BitBufferBits;`
- L262 _private member_ `uint32 BytePos;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define HUFFMAN_USE_UNALIGNED_READ (PLATFORM_SUPPORTS_UNALIGNED_LOADS && PLATFORM_LITTLE_ENDIAN)`
- L7 _macro_ `#define MINIMUM_BITS_AFTER_REFILL 56 // Minimum number of bits guaranteed to be available in the internal buffer after a buffer refill.`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Private/HuffmanTable.h` (Private)


#### class `FHuffmanEncodeTable`  
`class FHuffmanEncodeTable`  
_L41-90_
- L48 _public prototype_ `void Initialize(int32 NumSymbols);` — Initialize a Huffman table for encoding values in the range [0..NumSymbols[ The table will initially be in prepass mode.
- L53 _public prototype_ `void Serialize(FHuffmanBitStreamWriter& Stream);` — Serialize the Huffman table to the bitstream, deserialize using FHuffmanDecodeTable::Initialize
- L59 _public prototype_ `void SetPrepass(bool bInIsPrepass);` — Toggle between prepass mode and encoding mode. Note: Toggling will update internal data structures and may have take more time than setting a simple variable.
- L64 _public function_ `bool IsPrepass()` — Check if the table is currently operating in prepass mode.
- L72 _public prototype_ `void Encode(FHuffmanBitStreamWriter& Stream, int32 Symbol);` — Encode a symbol to the bitstream. If the table is in prepass mode no actual bits will be emitted to the stream.
- L75 _private member_ `TArray<uint32> SymbolFrequencies;` — This has a sentinel element at index NumValues!! And thus contains NumValues+1 elements
- L76 _private member_ `TArray<int32> CodewordSymbols;`
- L84 _private member_ `TArray<FCodeWord> CodeWords;` — For every symbol the corresponding huffcode bits
- L85 _private member_ `int32 NumCodeWordsOfLength[HUFFMAN_MAX_CODE_LENGTH+1];` — Number of codewords with a given length, element 0 is unused
- L86 _private member_ `int32 NumSymbols;`
- L88 _private prototype_ `void ResetFrequencies();`
- L89 _private member_ `bool bIsPrepass;`

#### struct `FHuffmanEncodeTable::FCodeWord`  
`struct FCodeWord`  
_L78-82_
- L80 _public member_ `int32 Bits;`
- L81 _public member_ `int32 Length;`

#### class `FHuffmanDecodeTable`  
`class FHuffmanDecodeTable`  
_L92-132_
- L98 _public prototype_ `void Initialize(FHuffmanBitStreamReader& Stream);` — Initialize a Huffman decode table based on the serialized table.
- L103 _public function_ `FORCEINLINE int32 Decode(FHuffmanBitStreamReader &Stream)` — Decode the next symbol from the bitstream.
- L116 _public function_ `FORCEINLINE int32 DecodeNoRefill(FHuffmanBitStreamReader &Stream)` — Decode the next symbol from the bitstream without refilling the bit buffer.
- L131 _private member_ `FTableEntry TableEntries[1u << HUFFMAN_MAX_CODE_LENGTH];`

#### struct `FHuffmanDecodeTable::FTableEntry`  
`struct FTableEntry`  
_L125-129_
- L127 _public member_ `int8 Length;`
- L128 _public member_ `int8 Symbol;`

#### Free symbols / members of external scopes

- L36 _macro_ `#define HUFFMAN_MAX_CODES 256`
- L37 _macro_ `#define HUFFMAN_MAX_CODE_LENGTH 11`
- L38 _macro_ `#define HUFFMAN_MAX_CODE_LENGTH_BITS 4 // Number of bits needed to decode a value in the range [0..HUFFMAN_MAX_CODE_LENGTH]`
- L39 _macro_ `#define HUFFMAN_SYMBOL_COUNT_BITS 9 // Number of bits needed to send the number of symbols`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Private/NormalCompression.h` (Private)


#### class `FNormalCoderSmith`  
`class FNormalCoderSmith`  
_L15-100_
- desc: Normal codec according to Smith et al. Codes a unit vector as two indices indexing a quantized unit sphere and exploits coherence between successive coded vectors. See the paper for details on the algorithm [Smith J., Petrova G., and Schaefer S. 2012. Encoding normal vectors using optimized spherical coordinates. Computers & Graphics 36, 5, 360-365.]. States they have better complexity/rate/quality properties than Octa (e.g., Griffith et al.) and Sextant (Deering et al.). Initial experiment and port to UnrealEngine, lots that can be optimized.
- L19 _public member_ `int32 NPhiValue;` — Number of bins spanning the polar range. Determines the precision of the coded results
- L21 _public member_ `TArray<int32> NThetaTable;` — Table with number of bins for each NPhi/polar index value. Small values close to the poles, largest at the equator.
- L24 _public member_ `FMatrix MoveFrameEncoded;` — Encoder transform matrix, transforms a vector from its absolute position to its position relative to the previously-seen vector. This gets the relative vector as close as possible to the top.
- L27 _public member_ `FMatrix MoveFrameDecoded;` — Decoder transform matrix, transforms a vector from its absolute position to its position relative to the previously-seen vector. This gets the relative vector as close as possible to the top.
- L57 _public prototype_ `FNormalCoderSmith();`
- L60 _public prototype_ `FEncodedNormal Encode(const FVector& Value);` — Encode a vector
- L63 _public prototype_ `FVector Decode(const FEncodedNormal& Value);` — Decode a vector
- L66 _public prototype_ `static FORCEINLINE FSphericalCoordinates VectorToSpherical(const FVector& Vector);` — Convert from Cartesian vectors to spherical coordinates
- L68 _public prototype_ `static FORCEINLINE FVector SphericalToVector(const FSphericalCoordinates& Spherical);` — Convert from spherical coordinates to Cartesian vectors
- L72 _private prototype_ `void GenerateNThetaTable(int32 NPhi, float MaxError, TArray<int32>& NTheta);` — Generate our table of NThetas. The lower the MaxError, the higher the values in the NTheta table, i.e., the number of bins
- L74 _private prototype_ `int32 CalcNTheta(int32 JIndex, float MaxError);` — Calculates a NTheta (number of azimuth bins) for a specific polar index
- L76 _private prototype_ `int32 GetTotalBinCount() const;` — The total amount of bins the sphere is split into, i.e., number of possible (J,K) combinations
- L79 _private function_ `FORCEINLINE int32 GetNtheta(int32 IndexJ)` — Number of bins for a given polar index
- L85 _private prototype_ `FORCEINLINE FVector MoveFrameEncode(const FVector& Value);` — Transforms a vector from its absolute position to its relative position to the previously-seen vector
- L87 _private prototype_ `FORCEINLINE FVector UnmoveFrame(const FVector& Moved, FMatrix& TransformMatrix);` — Transforms a relative vector back to its absolute position
- L89 _private prototype_ `FORCEINLINE void UpdateRotationMatrix(const FVector& UnmovedVector, FVector& ColumnX, FVector& ColumnY, FVector& ColumnZ);` — Update our absolute-relative transformation matrix
- L92 _private function_ `int32 PositiveModulo(int32 i, int32 n)` — Always positive modulo operation helper
- L98 _private prototype_ `FORCEINLINE FVector GetMatrixColumn(FMatrix& Matrix, int32 Column);` — Helpers to get our column vectors in our matrix. These can probably be replaced by UnrealEngine-specific operations.
- L99 _private prototype_ `FORCEINLINE void SetMatrixColumn(FMatrix& Matrix, int32 Column, const FVector& Value);`

#### struct `FNormalCoderSmith::FEncodedNormal`  
`struct FEncodedNormal`  
_L30-40_
- desc: Coded normal representation, two indices indexing a bin on the sphere
- L33 _public member_ `int32 JIndex;` — Index J, indexing a bin over the range of elevation/Phi
- L35 _public member_ `int32 KIndex;` — Index K, indexing a bin over the range of azimuth/Theta
- L37 _public function_ `FEncodedNormal(int32 SetJIndex, int32 SetKIndex) : JIndex(SetJIndex), KIndex(SetKIndex)`

#### struct `FNormalCoderSmith::FSphericalCoordinates`  
`struct FSphericalCoordinates`  
_L43-55_
- desc: Spherical coordinates
- L45 _public member_ `float Phi;`
- L46 _public member_ `float Theta;`
- L48 _public function_ `FSphericalCoordinates() : Phi(0.0f), Theta(0.0f)`
- L52 _public function_ `FSphericalCoordinates(float SetPhi, float SetTheta) : Phi(SetPhi), Theta(SetTheta)`

#### class `FNormalCoderSmithTest`  
`class FNormalCoderSmithTest`  
_L103-111_
- desc: Testing functionality.
- L106 _public prototype_ `static void Test();`
- L109 _private prototype_ `static int32 Denormalize(float Value);`
- L110 _private prototype_ `static FIntVector Denormalize(const FVector& Value);`

#### Free symbols / members of external scopes

- L5 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeoCaStreamingNormalCompression, Verbose, All);`
- L5 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeoCaStreamingNormalCompression, Verbose, All);`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Private/RingBuffer.h` (Private)


#### class `FRingBuffer`  
`template <class T, size_t N> class FRingBuffer`  
_L11-74_
- desc: Ring buffer with a given capacity, i.e., a fixed size stack that overwrites old values Push values at the top using Push(), retrieve values using Peek(depth), e.g., Peek(0) for the most recent, Peek(1) second most recent etc.
- L14 _public function_ `FRingBuffer(uint32 Capacity) : Top(0), Count(0)`
- L19 _public function_ `FRingBuffer(uint32 Capacity, const T& DefaultValue) : Top(0), Count(0)`
- L27 _public function_ `FORCEINLINE void Push(const T& value)` — Push an element to the top, Use Peek(0)	to retrieve it
- L37 _public function_ `FORCEINLINE const T& Peek(uint32 Index) const` — Retrieve value indexed starting from the top, e.g., Peek(0) for most recent
- L49 _public function_ `FORCEINLINE const T& operator [](uint32 index) const` — Retrieve value indexed starting from the top, e.g., Peek(0) for most recent
- L57 _public function_ `FORCEINLINE uint32 Capacity() const` — Capacity of the ring buffer
- L65 _public function_ `FORCEINLINE uint32 Num() const` — Number of the actual elements in the buffer
- L71 _private member_ `TArray<T, TInlineAllocator<N>> Buffer;`
- L72 _private member_ `uint32 Top;`
- L73 _private member_ `uint32 Count;`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Private/StreamingGeometryCacheData.h` (Private)


#### struct `FResidentChunk`  
`struct FResidentChunk`  
_L18-24_
- desc: An actual chunk resident in memory.
- L20 _public member_ `void* Memory;`
- L21 _public member_ `int32 DataSize;`
- L22 _public member_ `int32 Refcount;`
- L23 _public member_ `IBulkDataIORequest* IORequest;` — null when resident, nonnull when being loaded

#### struct `FCompletedChunk`  
`struct FCompletedChunk`  
_L29-36_
- desc: The results of a completed async-io request.
- L31 _public member_ `IBulkDataIORequest* ReadRequest;`
- L32 _public member_ `int32 LoadedChunkIndex;`
- L34 _public function_ `FCompletedChunk() : ReadRequest(nullptr), LoadedChunkIndex(0)`
- L35 _public function_ `FCompletedChunk(int32 SetLoadedChunkIndex, IBulkDataIORequest* SetReadRequest) : ReadRequest(SetReadRequest), LoadedChunkIndex(SetLoadedChunkIndex)`

#### class `FStreamingGeometryCacheData`  
`class FStreamingGeometryCacheData`  
_L43-100_
- desc: For every UGeometryCache one of these is created for by the streaming manager. This keeps this functionality separate from the main UGeometryCacheTrackStreamable and tied to the manager. See it as a "component" on the UGeometryCacheTrackStreamable
- L46 _public prototype_ `FStreamingGeometryCacheData(UGeometryCacheTrackStreamable* Track);`
- L47 _public prototype_ `~FStreamingGeometryCacheData();`
- L49 _public prototype_ `void UpdateStreamingStatus();`
- L51 _public prototype_ `const uint8* MapChunk(uint32 ChunkIndex, uint32* OutChunkSize = nullptr);`
- L52 _public prototype_ `void UnmapChunk(uint32 ChunkIndex);`
- L54 _public prototype_ `bool IsStreamingInProgress();`
- L55 _public prototype_ `bool BlockTillAllRequestsFinished(float TimeLimit = 0.0f);`
- L56 _public prototype_ `void PrefetchData(UGeometryCacheComponent* Component);`
- L58 _public prototype_ `void ResetNeededChunks();`
- L59 _public prototype_ `void AddNeededChunk(uint32 ChunkIndex);`
- L63 _private prototype_ `FResidentChunk &AddResidentChunk(int32 ChunkId, const FStreamedGeometryCacheChunk &ChunkInfo);`
- L64 _private prototype_ `void RemoveResidentChunk(FResidentChunk& LoadedChunk);`
- L65 _private prototype_ `void OnAsyncReadComplete(int32 LoadedChunkIndex, IBulkDataIORequest* ReadRequest);`
- L66 _private prototype_ `void ProcessCompletedChunks();`
- L69 _private member_ `UGeometryCacheTrackStreamable *Track;` — The track we are associated with
- L75 _private member_ `TArray<int32> ChunksNeeded;` — Chunks that ideally would be loaded at this point in time There may be more or less actual chunks loaded (more = cached chunks, less = we're still waiting for the disc) This should only be used from the main thread. It can be modified without taking the lock. Changes are then "latched" to other data structures/threads in the UpdateStreamingStatus function.
- L78 _private member_ `TArray<int32> ChunksAvailable;` — List of chunks currently resident in memory
- L82 _private member_ `TMap<int32, FResidentChunk> Chunks;` — This this does not necessary contains only chunks in the ChunksAvailable lists for example chunks in the ChunksRequested will also be in here.
- L85 _private member_ `TArray<int32> ChunksRequested;` — Chunks requested to be streamed in but not available yet
- L89 _private member_ `TArray<int32> ChunksEvicted;` — Chunks to be evicted. Chunks may linger here for a while until they are fully unpinned
- L91 _private member_ `TArray<IAsyncReadRequest*>IoRequestsToCompleteAndDeleteOnGameThread;`
- L95 _private member_ `TQueue<FCompletedChunk, EQueueMode::Mpsc> CompletedChunks;` — Chunks that have finished loading but have not finished their post-load bookkeping they are still not part of the ChunksAvailable list.
- L97 _private member_ `TSet<IBulkDataIORequest*> DelayedDeleteReadRequests;`
- L99 _private member_ `mutable FCriticalSection CriticalSection;`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Public/GeometryCacheConstantTopologyWriter.h` (Public)


#### class `UE::GeometryCacheHelpers::FGeometryCacheConstantTopologyWriter`  
`class FGeometryCacheConstantTopologyWriter`  
_L36-126_
- desc: Helper class to write a GeometryCache asset. Usage: FGeometryCacheConstantTopologyWriter Writer(MyCache); Writer.AddMaterials(...); FGeometryCacheConstantTopologyWriter::FTrackWriter& TrackWriter = Writer.AddGetTrackWriter(); // First track TrackWriter.Indices = ...; TrackWriter.UVs = ...; ... TrackWriter.WriteAndClose(PositionsToMoveFrom); FGeometryCacheConstantTopologyWriter::FTrackWriter& TrackWriter = Writer.AddGetTrackWriter(); // Second track ...
- L50 _public prototype_ `FGeometryCacheConstantTopologyWriter(UGeometryCache& OutCache);` — Construct a new FGeometryCacheConstantTopologyWriter object. This will remove all existing tracks from the cache. @param OutCache
- L51 _public prototype_ `FGeometryCacheConstantTopologyWriter(UGeometryCache& OutCache, const FConfig& Config);`
- L52 _public prototype_ `~FGeometryCacheConstantTopologyWriter();`
- L54 _public prototype_ `FGeometryCacheConstantTopologyWriter(const FGeometryCacheConstantTopologyWriter&) = delete;`
- L55 _public prototype_ `FGeometryCacheConstantTopologyWriter& operator=(const FGeometryCacheConstantTopologyWriter&) = delete;`
- L116 _public prototype_ `FTrackWriter& AddTrackWriter(FName TrackName = FName());`
- L117 _public prototype_ `FTrackWriter& GetTrackWriter(int32 Index);`
- L118 _public prototype_ `int32 GetNumTracks() const;`
- L119 _public prototype_ `void AddMaterials(const TArray<TObjectPtr<UMaterialInterface>>& Materials);`
- L120 _public prototype_ `int32 GetNumMaterials() const;`
- L123 _private member_ `TStrongObjectPtr<UGeometryCache> Cache;`
- L124 _private member_ `TArray<FTrackWriter> TrackWriters;`
- L125 _private member_ `FConfig Config;`

#### struct `UE::GeometryCacheHelpers::FGeometryCacheConstantTopologyWriter::FConfig`  
`struct FConfig`  
_L39-44_
- L41 _public member_ `float FPS = 30.0f;`
- L42 _public member_ `float PositionPrecision = 0.001f;`
- L43 _public member_ `uint32 TextureCoordinatesNumberOfBits = 10;`

#### struct `UE::GeometryCacheHelpers::FGeometryCacheConstantTopologyWriter::FFrameData`  
`struct FFrameData`  
_L57-62_
- L59 _public member_ `TArray<FVector3f> Positions;`
- L60 _public member_ `TArray<FVector3f> Normals;`
- L61 _public member_ `TArray<FVector3f> TangentsX;`

#### struct `UE::GeometryCacheHelpers::FGeometryCacheConstantTopologyWriter::FVisibilitySample`  
`struct FVisibilitySample`  
_L64-68_
- L66 _public member_ `int32 FrameIndex = 0;`
- L67 _public member_ `bool bVisible = true;`

#### struct `UE::GeometryCacheHelpers::FGeometryCacheConstantTopologyWriter::FTrackWriter`  
`struct FTrackWriter`  
_L70-114_
- L72 _public prototype_ `FTrackWriter(FGeometryCacheConstantTopologyWriter& InOwner, FName TrackName = FName());`
- L73 _public prototype_ `~FTrackWriter();`
- L75 _public prototype_ `FTrackWriter(const FTrackWriter&) = delete;`
- L76 _public prototype_ `FTrackWriter& operator=(const FTrackWriter&) = delete;`
- L78 _public member_ `TArray<uint32> Indices;`
- L79 _public member_ `TArray<FVector2f> UVs;`
- L80 _public member_ `TArray<FColor> Colors;`
- L81 _public member_ `TArray<uint32> ImportedVertexNumbers;`
- L82 _public member_ `TArray<FGeometryCacheMeshBatchInfo> BatchesInfo;`
- L83 _public member_ `TOptional<TArray<int32>> SourceVertexIndices;`
- L94 _public prototype_ `bool WriteAndClose(TArrayView<TArray<FVector3f>> PositionsToMoveFrom);` — Move the position data to the cache track and close the TrackWriter. Once closed, the track will be added to the geometry cache and the TrackWriter cannot be used anymore. @param PositionsToMoveFrom Array of positions to move from. The size of the array equals to the number of frames. The size of each array element equals to the number of vertices. The number of vertices must be the same for all frames. @return true if successfully write data and close the track writer.
- L102 _public prototype_ `bool WriteAndClose(TArrayView<FFrameData> FramesToMoveFrom);` — Move the frame data to the cache track and close the TrackWriter. Similar to WriteAndClose(TArrayView<TArray<FVector3f>> PositionsToMoveFrom), but also supports normals and tangents. Normals and tangents are optional. If they are not provided, the track will compute them. Normals and tangents must have the same size as positions.
- L109 _public prototype_ `bool WriteAndClose(TArrayView<FFrameData> FramesToMoveFrom, const TArray<FVisibilitySample>& VisibilitySamples);` — Move the frame data to the cache track and close the TrackWriter. Similar to WriteAndClose(TArrayView<FFrameData> FramesToMoveFrom), but also supports visibility samples. Each visibility sample defines the visibility of the track starting from the specified frame to the next visibility sample
- L112 _private member_ `TStrongObjectPtr<UGeometryCacheTrack> Track;`
- L113 _private member_ `FGeometryCacheConstantTopologyWriter* Owner = nullptr;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace GeometryCacheHelpers` (scope `UE`)
- L139 _prototype_ `int32 AddTrackWriterFromSkinnedAsset(FGeometryCacheConstantTopologyWriter& Writer, const USkinnedAsset& Asset);` (scope `UE::GeometryCacheHelpers`) — @brief This will create a track writer and fill in the track writer's data (indices, UVs, materials .etc) from the skinned asset. This only creates one track for the skinned asset. If you want to create multiple tracks based on imported mesh info, checkout AddTrackWriterFromSkinnedAsset() in ChaosClothGenerator.cpp. Usage: FGeometryCacheConstantTopologyWriter Writer(MyCache); int32 Index = AddTrackWriterFromSkinnedAsset(Writer, Asset); if (Index != INDEX_NONE) { Writer.GetTrackWriter(Index).WriteAndClose(PositionsToMoveFrom); }
- L145 _prototype_ `int32 AddTrackWriterFromSkinnedAssetAndMaterials(FGeometryCacheConstantTopologyWriter& Writer, const USkinnedAsset& Asset, int32 LODIndex, const TArray<TObjectPtr<UMaterialInterface>>& Materials);` (scope `UE::GeometryCacheHelpers`) — @brief This will create a track writer and fill in the track writer's data (indices, UVs, .etc) from the skinned asset, with the option to specify a set of materials which typically come from a specific skeletal mesh component using this skinned asset.
- L160 _prototype_ `int32 AddTrackWriterFromStaticMesh(FGeometryCacheConstantTopologyWriter& Writer, const UStaticMesh& Asset);` (scope `UE::GeometryCacheHelpers`) — @brief This will create a track writer and fill in the track writer's data (indices, UVs, materials .etc) from the static mesh. This only creates one track for the static mesh. If you want to create multiple tracks based on imported mesh info, checkout AddTrackWriterFromSkinnedAsset() in ChaosClothGenerator.cpp. Usage: @code FGeometryCacheConstantTopologyWriter Writer(MyCache); int32 Index = AddTrackWriterFromStaticMesh(Writer, Asset); if (Index != INDEX_NONE) { Writer.GetTrackWriter(Index).WriteAndClose(PositionsToMoveFrom); } @endcode
- L165 _prototype_ `int32 AddTrackWriterFromStaticMeshAndMaterials( FGeometryCacheConstantTopologyWriter& Writer, const UStaticMesh& StaticMesh, int32 LODIndex, const TArray<TObjectPtr<UMaterialInterface>>& Materials);` (scope `UE::GeometryCacheHelpers`) — @brief This will create a track writer and fill in the track writer's data (indices, UVs, .etc) from the static mesh, with the option to specify a set of materials
- L176 _prototype_ `int32 AddTrackWritersFromTemplateCache(FGeometryCacheConstantTopologyWriter& Writer, const UGeometryCache& TemplateCache);` (scope `UE::GeometryCacheHelpers`) — @brief This will create multiple track writers and fill in the track writer's data (indices, UVs, materials .etc) from the template geometry cache. The number of track writers created equals to the number of tracks in the template geometry cache. @return The number of track writers created.

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Public/GeometryCacheHelpers.h` (Public)


#### struct `GeometyCacheHelpers`  
`struct GeometyCacheHelpers`  
_L7-16_
- L12 _public function_ `static inline float WrapAnimationTime(float Time, float Duration)` — Use this instead of fmod when working with looping animations as fmod gives incorrect results when using negative times.

#### struct `UE::GeometryCache::Utils::FMeshDataConversionArguments`  
`struct FMeshDataConversionArguments`  
_L28-34_
- L30 _public member_ `int32 MaterialOffset = 0;`
- L31 _public member_ `float FramesPerSecond = 24.0f;`
- L32 _public member_ `bool bUseVelocitiesAsMotionVectors = true;`
- L33 _public member_ `bool bStoreImportedVertexNumbers = false;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace MeshAttribute`
- L18 _namespace_ `namespace VertexInstance` (scope `MeshAttribute`)
- L20 _externvar_ `extern const FName Velocity;` (scope `MeshAttribute::VertexInstance`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace GeometryCache` (scope `UE`)
- L26 _namespace_ `namespace Utils` (scope `UE::GeometryCache`)
- L36 _prototype_ `void GetGeometryCacheMeshDataFromMeshDescription(FGeometryCacheMeshData& OutMeshData, FMeshDescription& MeshDescription, const FMeshDataConversionArguments& Args);` (scope `UE::GeometryCache::Utils`)

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Public/GeometryCacheModule.h` (Public)


#### class `FGeometryCacheModule`  
`class FGeometryCacheModule : public IModuleInterface`  
_L13-42_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L16 _public function_ `FGeometryCacheModule()`
- L18 _public prototype_ `virtual void StartupModule();`
- L19 _public prototype_ `virtual void ShutdownModule();`
- L27 _public function_ `static inline FGeometryCacheModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L37 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L44 _delegate_ `DECLARE_STATS_GROUP(TEXT("GeometryCache"), STATGROUP_GeometryCache, STATC`

### `Plugins/Runtime/GeometryCache/Source/GeometryCache/Public/GeometryCacheSceneProxy.h` (Public)


#### class `FGeomCacheVertexBuffer`  
`class FGeomCacheVertexBuffer : public FVertexBuffer`  
_L23-95_
- inherits: `FVertexBuffer`
- desc: Resource array to pass
- L27 _public function_ `void Init(int32 InSizeInBytes)`
- L34 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — Create on rhi thread. Uninitialized with NumVertices space.
- L36 _public prototype_ `virtual void ReleaseRHI() override;`
- L41 _public function_ `template<class DataType> void Update(FRHICommandListBase& RHICmdList, const TArray<DataType>& Vertices)` — Sugar function to update from a typed array.
- L47 _public function_ `void UpdatePositionsOnly(FRHICommandListBase& RHICmdList, const TArray<FDynamicMeshVertex>& Vertices)`
- L54 _public function_ `void UpdateExceptPositions(FRHICommandListBase& RHICmdList, const TArray<FDynamicMeshVertex>& Vertices)`
- L68 _public prototype_ `void UpdateRaw(FRHICommandListBase& RHICmdList, const void* Data, int32 NumItems, int32 ItemSizeBytes, int32 ItemStrideBytes);` — Update the raw contents of the buffer, possibly reallocate if needed.
- L73 _public prototype_ `void UpdateSize(FRHICommandListBase& RHICmdList, int32 NewSizeInBytes);` — Resize the buffer but don't initialize it with any data.
- L78 _public function_ `template<class DataType> void UpdateSizeTyped(FRHICommandListBase& RHICmdList, int32 NewSizeInElements)` — Resize the buffer but don't initialize it with any data.
- L86 _public function_ `unsigned GetSizeInBytes()` — Get the current size of the buffer
- L88 _public function_ `virtual FString GetFriendlyName() const override`
- L90 _public function_ `FRHIShaderResourceView* GetBufferSRV() const`
- L93 _protected member_ `int32 SizeInBytes;`
- L94 _protected member_ `FShaderResourceViewRHIRef BufferSRV;`

#### class `FGeomCacheTangentBuffer`  
`class FGeomCacheTangentBuffer : public FGeomCacheVertexBuffer`  
_L97-101_
- inherits: `FGeomCacheVertexBuffer`
- L100 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`

#### class `FGeomCacheColorBuffer`  
`class FGeomCacheColorBuffer : public FGeomCacheVertexBuffer`  
_L103-107_
- inherits: `FGeomCacheVertexBuffer`
- L106 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`

#### class `FGeomCacheIndexBuffer`  
`class FGeomCacheIndexBuffer : public FIndexBuffer`  
_L110-133_
- inherits: `FIndexBuffer`
- desc: Index Buffer
- L113 _public member_ `int32 NumAllocatedIndices = 0;` — Total allocated GPU index buffer size in elements
- L114 _public member_ `int32 NumValidIndices = 0;` — Current valid data region of the index buffer (may be smaller than allocated buffer)
- L117 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — Create on rhi thread. Uninitialized with NumIndices space.
- L119 _public prototype_ `virtual void ReleaseRHI() override;`
- L124 _public prototype_ `void Update(FRHICommandListBase& RHICmdList, const TArray<uint32>& Indices);` — Update the data and possibly reallocate if needed.
- L125 _public prototype_ `void UpdateSizeOnly(FRHICommandListBase& RHICmdList, int32 NewNumIndices);`
- L127 _public function_ `unsigned SizeInBytes()`
- L129 _public function_ `FRHIShaderResourceView* GetBufferSRV() const`
- L132 _protected member_ `FShaderResourceViewRHIRef BufferSRV;`

#### class `FGeomCacheVertexFactory`  
`class FGeomCacheVertexFactory : public FGeometryCacheVertexVertexFactory`  
_L136-146_
- inherits: `FGeometryCacheVertexVertexFactory`
- desc: Vertex Factory
- L139 _public prototype_ `FGeomCacheVertexFactory(ERHIFeatureLevel::Type InFeatureLevel);`
- L142 _public prototype_ `void Init(FRHICommandListBase& RHICmdList, const FVertexBuffer* PositionBuffer, const FVertexBuffer* MotionBlurDataBuffer, const FVertexBuffer* TangentXBuffer, const FVertexBuffer* TangentZBuffer, const FVertexBuffer* TextureCoordinateBuffer, const FVertexBuffer* ColorBuffer);` — `UE_DEPRECATED(5.7, "Use InitComponentVF to setup the FDataType and then call SetData on the vertex factory with the command list")`
- L144 _public prototype_ `static void InitDummyComponentVF(FGeometryCacheVertexVertexFactory::FDataType& OutData);`
- L145 _public prototype_ `static void InitComponentVF(const FVertexBuffer* PositionBuffer, const FVertexBuffer* MotionBlurDataBuffer, const FVertexBuffer* TangentXBuffer, const FVertexBuffer* TangentZBuffer, const FVertexBuffer* TextureCoordinateBuffer, const FVertexBuffer* ColorBuffer, FGeometryCacheVertexVertexFactory::FDataType& OutData);`

#### class `FGeomCacheTrackProxyFixLayout`  
`class FGeomCacheTrackProxyFixLayout`  
_L149-153_
- desc: Hacky base class to avoid 8 bytes of padding after the vtable
- L152 _public prototype_ `virtual ~FGeomCacheTrackProxyFixLayout() = default;`

#### class `FGeomCacheTrackProxy`  
`class FGeomCacheTrackProxy : FGeomCacheTrackProxyFixLayout`  
_L162-284_
- inherits: `FGeomCacheTrackProxyFixLayout`
- desc: This the track proxy has some "double double buffering" going on. First we keep two mesh frames. The one just before the current time and the one just after the current time. This is the full mesh and we interpolate between it to derive the actual mesh for the exact time we're at. Secondly we have two position buffers. The one for the current rendered frame and the one from the previous rendered frame (this is not the same as the mesh frame, the mesh may be at say 10 fps then get interpolated to 60 fps rendered frames)
- L166 _public function_ `FGeomCacheTrackProxy(ERHIFeatureLevel::Type InFeatureLevel) : VertexFactory(InFeatureLevel )`
- L170 _public prototype_ `virtual ~FGeomCacheTrackProxy() = default;`
- L181 _public prototype_ `virtual bool UpdateMeshData(float Time, bool bLooping, int32& InOutMeshSampleIndex, FGeometryCacheMeshData& OutMeshData);` — Update the SampleIndex and MeshData for a given time @param Time - (Elapsed)Time to check against @param bLooping - Whether or not the animation is being played in a loop @param InOutMeshSampleIndex - Hold the MeshSampleIndex and will be updated if changed according to the Elapsed Time @param OutMeshData - Will hold the new MeshData if the SampleIndex changed @return true if the SampleIndex and MeshData were updated
- L190 _public prototype_ `virtual bool GetMeshData(int32 SampleIndex, FGeometryCacheMeshData& OutMeshData);` — Get the MeshData for a given SampleIndex @param SampleIndex - The sample index at which to retrieve the MeshData @param OutMeshData - Will hold the MeshData if it could be retrieved @return true if the MeshData was retrieved successfully
- L199 _public prototype_ `virtual bool IsTopologyCompatible(int32 SampleIndexA, int32 SampleIndexB);` — Check if the topology of two given SampleIndexes are compatible (ie. same topology) @param SampleIndexA - The first sample index to compare the topology @param SampleIndexB - The second sample index to compare the topology @return true if the topology is the same
- L208 _public prototype_ `virtual const FVisibilitySample& GetVisibilitySample(float Time, const bool bLooping) const;` — Get the VisibilitySample for a given time @param Time - (Elapsed)Time to check against @param bLooping - Whether or not the animation is being played in a loop @return the VisibilitySample that corresponds to the given time
- L225 _public prototype_ `virtual void FindSampleIndexesFromTime(float Time, bool bLooping, bool bIsPlayingBackwards, int32& OutFrameIndex, int32& OutNextFrameIndex, float& InInterpolationFactor);` — Find the two frames closest to the given time InterpolationFactor gives the position of the requested time slot between the two returned frames. 0.0 => We are very close to OutFrameIndex 1.0 => We are very close to OutNextFrameIndex If bIsPlayingBackwards it will return exactly the same indexes but in the reversed order. The InterpolationFactor will also be updated accordingly @param Time - (Elapsed)Time to check against @param bLooping - Whether or not the animation is being played in a loop @param bIsPlayingBackwards - Whether the animation is playing backwards or forwards @param OutFrameIndex - The closest frame index that corresponds to the given time @param OutNextFrameIndex - The frame index that follows OutFrameIndex @param InterpolationFactor - The interpolation value between the two frame times
- L233 _public prototype_ `virtual void InitRenderResources(FRHICommandListBase& RHICmdList, int32 NumVertices, int32 NumIndices);` — Initialize the render resources. Must be called before the render resources are used. @param NumVertices - The initial number of vertices to initialize the buffers with. Must be greater than 0 @param NumIndices - The initial number of indices to initialize the buffers with. Must be greater than 0
- L236 _public member_ `FGeometryCacheMeshData* MeshData;` — MeshData storing information used for rendering this Track
- L237 _public member_ `FGeometryCacheMeshData* NextFrameMeshData;`
- L240 _public member_ `int32 FrameIndex;` — Frame numbers corresponding to MeshData, NextFrameMeshData
- L241 _public member_ `int32 NextFrameIndex;`
- L242 _public member_ `int32 PreviousFrameIndex;`
- L243 _public member_ `float InterpolationFactor;`
- L244 _public member_ `float PreviousInterpolationFactor;`
- L245 _public member_ `float SubframeInterpolationFactor;`
- L248 _public member_ `TArray<UMaterialInterface*> Materials;` — Material applied to this Track
- L251 _public member_ `FGeomCacheVertexBuffer PositionBuffers[2];` — Vertex buffers for this Track. There are two position buffers which we double buffer between, current frame and last frame
- L252 _public member_ `uint32 PositionBufferFrameIndices[2];` — Frame indexes of the positions in the position buffer
- L253 _public member_ `float PositionBufferFrameTimes[2];` — Exact time after interpolation of the positions in the position buffer.
- L254 _public member_ `uint32 CurrentPositionBufferIndex;` — CurrentPositionBufferIndex%2  is the last updated position buffer
- L256 _public member_ `int32 UploadedSampleIndex;`
- L258 _public member_ `FGeomCacheTangentBuffer TangentXBuffer;`
- L259 _public member_ `FGeomCacheTangentBuffer TangentZBuffer;`
- L260 _public member_ `FGeomCacheVertexBuffer TextureCoordinatesBuffer;`
- L261 _public member_ `FGeomCacheColorBuffer ColorBuffer;`
- L264 _public member_ `FGeomCacheIndexBuffer IndexBuffer;` — Index buffer for this Track
- L267 _public member_ `FGeomCacheVertexFactory VertexFactory;` — Vertex factory for this Track
- L270 _public member_ `UGeometryCacheTrack* Track;` — The GeometryCacheTrack to which the proxy is associated
- L273 _public member_ `FMatrix WorldMatrix;` — World Matrix for this Track
- L276 _public member_ `bool bNextFrameMeshDataSelected;` — Flag to indicate which frame mesh data was selected during the update
- L278 _public member_ `bool bResourcesInitialized;`
- L281 _public member_ `bool bInitializedRayTracing = false;`
- L282 _public member_ `FRayTracingGeometry RayTracingGeometry;`

#### class `FGeometryCacheSceneProxy`  
`class FGeometryCacheSceneProxy : public FPrimitiveSceneProxy`  
_L287-436_
- inherits: `FPrimitiveSceneProxy`
- desc: Procedural mesh scene proxy
- L290 _public prototype_ `SIZE_T GetTypeHash() const override;`
- L292 _public prototype_ `FGeometryCacheSceneProxy(class UGeometryCacheComponent* Component);`
- L293 _public prototype_ `FGeometryCacheSceneProxy(class UGeometryCacheComponent* Component, TFunction<FGeomCacheTrackProxy*()> TrackProxyCreator);`
- L295 _public prototype_ `virtual ~FGeometryCacheSceneProxy();`
- L299 _public prototype_ `virtual HHitProxy* CreateHitProxies(UPrimitiveComponent* Component, TArray<TRefCountPtr<HHitProxy> >& OutHitProxies) override;`
- L301 _public prototype_ `virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;`
- L302 _public prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L304 _public prototype_ `virtual bool CanBeOccluded() const override;`
- L305 _public prototype_ `virtual bool IsUsingDistanceCullFade() const override;`
- L306 _public prototype_ `virtual uint32 GetMemoryFootprint(void) const;`
- L307 _public prototype_ `uint32 GetAllocatedSize(void) const;`
- L310 _public prototype_ `void UpdateAnimation(FRHICommandListBase& RHICmdList, float NewTime, bool bLooping, bool bIsPlayingBackwards, float PlaybackSpeed, float MotionVectorScale, bool bInterpolateFrames = true);`
- L321 _public prototype_ `void UpdateAnimation(FRHICommandListBase& RHICmdList, const FAnimationUpdateParameters& UpdatedValues);`
- L324 _public prototype_ `void UpdateSectionWorldMatrix(const int32 SectionIndex, const FMatrix& WorldMatrix);` — Update world matrix for specific section
- L326 _public prototype_ `void UpdateSectionVertexBuffer(const int32 SectionIndex, FGeometryCacheMeshData* MeshData);` — Update vertex buffer for specific section
- L328 _public prototype_ `void UpdateSectionIndexBuffer(const int32 SectionIndex, const TArray<uint32>& Indices);` — Update index buffer for specific section
- L331 _public prototype_ `void ClearSections();` — Clears the Sections array
- L334 _public prototype_ `virtual void GetDynamicRayTracingInstances(FRayTracingInstanceCollector& Collector) override final;`
- L335 _public function_ `virtual bool IsRayTracingRelevant() const override`
- L336 _public function_ `virtual bool HasRayTracingRepresentation() const override`
- L339 _public function_ `const TArray<FGeomCacheTrackProxy*>& GetTracks() const`
- L342 _private prototype_ `void FrameUpdate(FRHICommandListBase& RHICmdList) const;`
- L345 _private prototype_ `void InitRayTracing(FRHICommandListBase& RHICmdList);`
- L348 _private prototype_ `void CreateMeshBatch( FRHICommandListBase& RHICmdList, const FGeomCacheTrackProxy* TrackProxy, const struct FGeometryCacheMeshBatchInfo& BatchInfo, class FGeometryCacheVertexFactoryUserDataWrapper& UserDataWrapper, FDynamicPrimitiveUniformBuffer& DynamicPrimitiveUniformBuffer, FMeshBatch& Mesh) const;`
- L358 _private member_ `TArray<FGeomCacheTrackProxy*> Tracks;` — Array of Track Proxies
- L361 _private member_ `TArray<FHitProxyId> HitProxyIds;`
- L415 _private member_ `mutable Scratch;`
- L417 _private member_ `uint32 UpdatedFrameNum;`
- L418 _private member_ `float Time;`
- L419 _private member_ `float PlaybackSpeed;`
- L420 _private member_ `float MotionVectorScale;`
- L422 _private member_ `bool bOverrideWireframeColor = false;`
- L423 _private member_ `FLinearColor WireframeOverrideColor = FLinearColor::Green;`
- L425 _private member_ `FMaterialRelevance MaterialRelevance;`
- L426 _private member_ `uint32 bLooping : 1;`
- L427 _private member_ `uint32 bIsPlayingBackwards : 1;`
- L428 _private member_ `uint32 bExtrapolateFrames : 1;`
- L429 _private member_ `uint32 bInterpolateFrames : 1;`
- L432 _private member_ `TFunction<FGeomCacheTrackProxy*()> CreateTrackProxy;` — Function used to create a new track proxy at construction
- L434 _private member_ `FName RayTracingDebugName = NAME_None;`

#### struct `FGeometryCacheSceneProxy::FAnimationUpdateParameters`  
`struct FAnimationUpdateParameters`  
_L312-320_
- L314 _public member_ `float Time;`
- L315 _public member_ `bool bLooping;`
- L316 _public member_ `bool bIsPlayingBackwards;`
- L317 _public member_ `float PlaybackSpeed;`
- L318 _public member_ `float MotionVectorScale;`
- L319 _public member_ `bool bInterpolateFrames;`

#### struct `FGeometryCacheSceneProxy::FScratchMemory`  
`struct FScratchMemory`  
_L365-414_
- desc: Scratch memory for frame update - do not use directly.
- L367 _public member_ `TArray<FVector3f> InterpolatedPositions;`
- L368 _public member_ `TArray<FPackedNormal> InterpolatedTangentX;`
- L369 _public member_ `TArray<FPackedNormal> InterpolatedTangentZ;`
- L370 _public member_ `TArray<FVector2f> InterpolatedUVs;`
- L371 _public member_ `TArray<FColor> InterpolatedColors;`
- L372 _public member_ `TArray<FVector3f> InterpolatedMotionVectors;`
- L374 _public function_ `void Prepare(int32 NumVertices, bool bHasMotionVectors)`
- L404 _public function_ `void Empty()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYCACHE_API`
- L439 _macro_ `#define GEOMETRY_CACHE_SCENE_PROXY_ISPC_ENABLED_DEFAULT 1`
- L443 _variable_ `static constexpr bool GGeometryCacheSceneProxyUseIspc = INTEL_ISPC && GEOMETRY_CACHE_SCENE_PROXY_ISPC_ENABLED_DEFAULT;`
- L445 _externvar_ `extern bool GGeometryCacheSceneProxyUseIspc;`
