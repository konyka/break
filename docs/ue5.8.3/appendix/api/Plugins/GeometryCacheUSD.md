# Plugins / GeometryCacheUSD

- module root: `Plugins/Importers/USDImporter/Source/GeometryCacheUSD`
- headers: 5; symbols: 57
- symbol kinds: class=5, function=1, macro=2, member=14, prototype=34, typedef=1
- PrivateDependencyModuleNames: USDClasses
- PrivateIncludePathModuleNames: DerivedDataCache
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GeometryCache, GeometryCacheStreamer, RHI, RenderCore, USDUtilities, UnrealUSDWrapper

### `Plugins/Importers/USDImporter/Source/GeometryCacheUSD/Public/GeometryCacheTrackUSD.h` (Public)


#### class `UGeometryCacheTrackUsd`  
`class UGeometryCacheTrackUsd : public UGeometryCacheTrack`  
_L22-96_
- inherits: `UGeometryCacheTrack`
- L26 _private prototype_ `UGeometryCacheTrackUsd();`
- L29 _public prototype_ `void Initialize( const UE::FUsdStage& InStage, const FString& InPrimPath, int32 InStartFrameIndex, int32 InEndFrameIndex, FReadUsdMeshFunction InReadFunc );`
- L38 _public prototype_ `virtual void BeginDestroy() override;`
- L39 _public prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L43 _public prototype_ `virtual const bool UpdateMeshData(const float Time, const bool bLooping, int32& InOutMeshSampleIndex, FGeometryCacheMeshData*& OutMeshData) override;`
- L45 _public prototype_ `virtual const bool UpdateBoundsData( const float Time, const bool bLooping, const bool bIsPlayingBackward, int32& InOutBoundsSampleIndex, FBox& OutBounds ) override;`
- L52 _public prototype_ `virtual const FGeometryCacheTrackSampleInfo& GetSampleInfo(float Time, const bool bLooping) override;`
- L53 _public prototype_ `virtual bool GetMeshDataAtTime(float Time, FGeometryCacheMeshData& OutMeshData) override;`
- L54 _public prototype_ `virtual bool GetMeshDataAtSampleIndex(int32 SampleIndex, FGeometryCacheMeshData& OutMeshData) override;`
- L55 _public prototype_ `virtual void UpdateTime(float Time, bool bLooping) override;`
- L58 _public prototype_ `const int32 FindSampleIndexFromTime(const float Time, const bool bLooping) const;`
- L59 _public prototype_ `float GetTimeFromSampleIndex(int32 SampleIndex) const;`
- L60 _public prototype_ `void GetFractionalFrameIndexFromTime(const float Time, const bool bLooping, int& OutFrameIndex, float& OutFraction) const;`
- L62 _public prototype_ `const FGeometryCacheTrackSampleInfo& GetSampleInfo(int32 SampleIndex);` — GetSampleInfo version that avoids converting time to index. Prefer this version when the index is already available
- L64 _public prototype_ `bool GetMeshData(int32 SampleIndex, FGeometryCacheMeshData& OutMeshData);`
- L68 _public prototype_ `bool LoadUsdStage();` — Upgrades our CurrentStageWeak into CurrentStagePinned, or re-opens the stage if its stale. Returns whether the stage was successfully opened or not
- L71 _public prototype_ `void UnloadUsdStage();` — Discards our CurrentStagePinned to release the stage
- L73 _public prototype_ `void RegisterStream();`
- L74 _public prototype_ `void UnregisterStream();`
- L77 _public member_ `double FramesPerSecond;`
- L78 _public member_ `int32 StartFrameIndex;`
- L79 _public member_ `int32 EndFrameIndex;`
- L81 _public member_ `FString PrimPath;`
- L84 _public member_ `UsdToUnreal::FUsdMeshConversionOptions MeshConversionOptions;`
- L87 _public member_ `UE::FUsdStage CurrentStagePinned;`
- L88 _public member_ `UE::FUsdStageWeak CurrentStageWeak;`
- L89 _public member_ `FString StageRootLayerPath;`
- L92 _private member_ `FGeometryCacheMeshData MeshData;`
- L93 _private member_ `TArray<FGeometryCacheTrackSampleInfo> SampleInfos;`
- L95 _private member_ `TUniquePtr<FGeometryCacheUsdStream> UsdStream;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API GEOMETRYCACHEUSD_API`

### `Plugins/Importers/USDImporter/Source/GeometryCacheUSD/Public/GeometryCacheTrackUSDTypes.h` (Public)


#### Free symbols / members of external scopes

- L11 _typedef_ `typedef TFunction<bool(const TWeakObjectPtr<UGeometryCacheTrackUsd>, float Time, FGeometryCacheMeshData&)> FReadUsdMeshFunction;`

### `Plugins/Importers/USDImporter/Source/GeometryCacheUSD/Public/GeometryCacheUSDComponent.h` (Public)


#### class `UGeometryCacheUsdComponent`  
`class UGeometryCacheUsdComponent : public UGeometryCacheComponent`  
_L16-33_
- inherits: `UGeometryCacheComponent`
- L22 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L26 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L30 _public prototype_ `virtual void OnRegister() override;`
- L31 _public prototype_ `virtual void OnUnregister() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYCACHEUSD_API`

### `Plugins/Importers/USDImporter/Source/GeometryCacheUSD/Public/GeometryCacheUSDSceneProxy.h` (Public)


#### class `FGeometryCacheUsdSceneProxy`  
`class FGeometryCacheUsdSceneProxy final : public FGeometryCacheSceneProxy`  
_L9-13_
- inherits: `FGeometryCacheSceneProxy`
- desc: Scene proxy that uses FGeomCacheTrackUsdProxy
- L12 _public prototype_ `FGeometryCacheUsdSceneProxy(class UGeometryCacheUsdComponent* Component);`

#### class `FGeomCacheTrackUsdProxy`  
`class FGeomCacheTrackUsdProxy : public FGeomCacheTrackProxy`  
_L16-38_
- inherits: `FGeomCacheTrackProxy`
- desc: Track proxy that gets its data from a GeometryCacheUsdTrack
- L19 _public function_ `FGeomCacheTrackUsdProxy(ERHIFeatureLevel::Type InFeatureLevel) : FGeomCacheTrackProxy(InFeatureLevel)`
- L25 _public prototype_ `virtual bool UpdateMeshData(float Time, bool bLooping, int32& InOutMeshSampleIndex, FGeometryCacheMeshData& OutMeshData) override;`
- L26 _public prototype_ `virtual bool GetMeshData(int32 SampleIndex, FGeometryCacheMeshData& OutMeshData) override;`
- L27 _public prototype_ `virtual bool IsTopologyCompatible(int32 SampleIndexA, int32 SampleIndexB) override;`
- L28 _public prototype_ `virtual const FVisibilitySample& GetVisibilitySample(float Time, const bool bLooping) const override;`
- L29 _public prototype_ `virtual void FindSampleIndexesFromTime( float Time, bool bLooping, bool bIsPlayingBackwards, int32& OutFrameIndex, int32& OutNextFrameIndex, float& InterpolationFactor ) override;`

### `Plugins/Importers/USDImporter/Source/GeometryCacheUSD/Public/GeometryCacheUSDStream.h` (Public)


#### class `FGeometryCacheUsdStream`  
`class FGeometryCacheUsdStream : public FGeometryCacheStreamBase`  
_L12-29_
- inherits: `FGeometryCacheStreamBase`
- L15 _public prototype_ `FGeometryCacheUsdStream(UGeometryCacheTrackUsd* InUsdTrack, FReadUsdMeshFunction InReadFunc);`
- L18 _public prototype_ `virtual bool GetFrameData(int32 FrameIndex, FGeometryCacheMeshData& OutMeshData) override;`
- L19 _public prototype_ `virtual void UpdateRequestStatus(TArray<int32>& OutFramesCompleted) override;`
- L23 _protected prototype_ `virtual void PrepareRead() override;`
- L24 _protected prototype_ `virtual void GetMeshData(int32 FrameIndex, int32 ConcurrencyIndex, FGeometryCacheMeshData& OutMeshData) override;`
- L26 _protected member_ `UGeometryCacheTrackUsd* UsdTrack;`
- L27 _protected member_ `FReadUsdMeshFunction ReadFunc;`
- L28 _protected member_ `std::atomic<bool> bReadyForRead;`
