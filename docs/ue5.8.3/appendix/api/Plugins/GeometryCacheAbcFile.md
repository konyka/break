# Plugins / GeometryCacheAbcFile

- module root: `Plugins/Experimental/GeometryCacheAbcFile/Source/GeometryCacheAbcFile`
- headers: 7; symbols: 68
- symbol kinds: class=8, function=4, member=19, prototype=37
- PrivateDependencyModuleNames: DerivedDataCache, EditorFramework, GeometryCacheStreamer, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: AlembicLibrary, Core, CoreUObject, Engine, GeometryCache, RHI, RenderCore

### `Plugins/Experimental/GeometryCacheAbcFile/Source/GeometryCacheAbcFile/Private/ActorFactoryGeometryCacheAbcFile.h` (Private)


#### class `UActorFactoryGeometryCacheAbcFile`  
`class UActorFactoryGeometryCacheAbcFile : public UActorFactory`  
_L10-15_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L14 _private prototype_ `UActorFactoryGeometryCacheAbcFile();`

### `Plugins/Experimental/GeometryCacheAbcFile/Source/GeometryCacheAbcFile/Private/GeometryCacheAbcFileActor.h` (Private)


#### class `AGeometryCacheAbcFileActor`  
`class AGeometryCacheAbcFileActor : public AActor`  
_L13-20_
- reflection: `UCLASS(ComponentWrapperClass)`
- inherits: `AActor`
- desc: GeometryCacheAbcFile actor serves as a placeable actor for GeometryCache loading from an Alembic file
- L19 _private member_ `TObjectPtr<UGeometryCacheAbcFileComponent> GeometryCacheAbcFileComponent;` — `UPROPERTY(Category = GeometryCacheAbcFileActor, VisibleAnywhere)`

### `Plugins/Experimental/GeometryCacheAbcFile/Source/GeometryCacheAbcFile/Private/GeometryCacheAbcFileComponentCustomization.h` (Private)


#### class `FGeometryCacheAbcFileComponentCustomization`  
`class FGeometryCacheAbcFileComponentCustomization : public IDetailCustomization`  
_L12-26_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L22 _protected prototype_ `FReply ReloadAbcFile();`
- L23 _protected prototype_ `bool IsReloadEnabled() const;`
- L25 _protected member_ `TWeakObjectPtr<class UGeometryCacheAbcFileComponent> GeometryCacheAbcFileComponent;`

### `Plugins/Experimental/GeometryCacheAbcFile/Source/GeometryCacheAbcFile/Private/GeometryCacheAbcStream.h` (Private)


#### class `FGeometryCacheAbcStream`  
`class FGeometryCacheAbcStream : public FGeometryCacheStreamBase`  
_L11-23_
- inherits: `FGeometryCacheStreamBase`
- L14 _public prototype_ `FGeometryCacheAbcStream(UGeometryCacheTrackAbcFile* InAbcTrack);`
- L18 _protected prototype_ `virtual void GetMeshData(int32 FrameIndex, int32 ConcurrencyIndex, FGeometryCacheMeshData& OutMeshData) override;`
- L21 _protected member_ `UGeometryCacheTrackAbcFile* AbcTrack;`
- L22 _protected member_ `FString Hash;`

### `Plugins/Experimental/GeometryCacheAbcFile/Source/GeometryCacheAbcFile/Public/GeometryCacheAbcFileComponent.h` (Public)


#### class `UGeometryCacheAbcFileComponent`  
`class UGeometryCacheAbcFileComponent : public UGeometryCacheComponent`  
_L15-61_
- reflection: `UCLASS(ClassGroup = (Rendering), meta = (BlueprintSpawnableComponent, DisplayName = "Geometry Cache Alembic File"), Experimental, ClassGroup = Experimental)`
- inherits: `UGeometryCacheComponent`
- desc: GeometryCacheAbcFileComponent, encapsulates a transient GeometryCache asset instance that fetches its data from an Alembic file and implements functionality for rendering and playback
- L19 _private prototype_ `UGeometryCacheAbcFileComponent(const FObjectInitializer& ObjectInitializer);`
- L24 _public member_ `FFilePath AlembicFilePath;` — `UPROPERTY(EditAnywhere, Category = "Alembic", meta = (FilePathFilter = "Alembic files (*.abc)|*.abc", RelativeToGameDir))`
- L27 _public member_ `FAbcSamplingSettings SamplingSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alembic")`
- L30 _public member_ `FAbcConversionSettings ConversionSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alembic")`
- L33 _public member_ `FAbcGeometryCacheSettings GeometryCacheSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alembic")`
- L36 _public member_ `FAbcNormalGenerationSettings NormalGenerationSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alembic")`
- L39 _public member_ `FAbcMaterialSettings MaterialSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alembic")`
- L43 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L47 _public prototype_ `virtual void PostLoad() override;`
- L51 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L54 _public prototype_ `void ReloadAbcFile();`
- L57 _protected prototype_ `void InitializeGeometryCache();`
- L60 _protected member_ `TObjectPtr<UAbcImportSettings> AbcSettings;` — `UPROPERTY(Transient)`

### `Plugins/Experimental/GeometryCacheAbcFile/Source/GeometryCacheAbcFile/Public/GeometryCacheAbcFileSceneProxy.h` (Public)


#### class `FGeometryCacheAbcFileSceneProxy`  
`class FGeometryCacheAbcFileSceneProxy final : public FGeometryCacheSceneProxy`  
_L9-13_
- inherits: `FGeometryCacheSceneProxy`
- desc: Scene proxy that uses FGeomCacheTrackAbcFileProxy
- L12 _public prototype_ `FGeometryCacheAbcFileSceneProxy(class UGeometryCacheAbcFileComponent* Component);`

#### class `FGeomCacheTrackAbcFileProxy`  
`class FGeomCacheTrackAbcFileProxy : public FGeomCacheTrackProxy`  
_L16-30_
- inherits: `FGeomCacheTrackProxy`
- desc: Track proxy that gets its data from a GeometryCacheAbcFileTrack
- L19 _public function_ `FGeomCacheTrackAbcFileProxy(ERHIFeatureLevel::Type InFeatureLevel) : FGeomCacheTrackProxy(InFeatureLevel)`
- L24 _public prototype_ `virtual bool UpdateMeshData(float Time, bool bLooping, int32& InOutMeshSampleIndex, FGeometryCacheMeshData& OutMeshData) override;`
- L25 _public prototype_ `virtual bool GetMeshData(int32 SampleIndex, FGeometryCacheMeshData& OutMeshData) override;`
- L26 _public prototype_ `virtual bool IsTopologyCompatible(int32 SampleIndexA, int32 SampleIndexB) override;`
- L27 _public prototype_ `virtual const FVisibilitySample& GetVisibilitySample(float Time, const bool bLooping) const override;`
- L28 _public prototype_ `virtual void FindSampleIndexesFromTime(float Time, bool bLooping, bool bIsPlayingBackwards, int32 &OutFrameIndex, int32 &OutNextFrameIndex, float &InterpolationFactor) override;`

### `Plugins/Experimental/GeometryCacheAbcFile/Source/GeometryCacheAbcFile/Public/GeometryCacheTrackAbcFile.h` (Public)


#### class `UGeometryCacheTrackAbcFile`  
`class UGeometryCacheTrackAbcFile : public UGeometryCacheTrack`  
_L15-68_
- reflection: `UCLASS(collapsecategories, hidecategories = Object, BlueprintType, config = Engine)`
- inherits: `UGeometryCacheTrack`
- desc: GeometryCacheTrack for Alembic file querying
- L19 _private prototype_ `UGeometryCacheTrackAbcFile();`
- L20 _private prototype_ `virtual ~UGeometryCacheTrackAbcFile();`
- L25 _public prototype_ `virtual const bool UpdateMatrixData(const float Time, const bool bLooping, int32& InOutMatrixSampleIndex, FMatrix& OutWorldMatrix) override;`
- L26 _public prototype_ `virtual const bool UpdateMeshData(const float Time, const bool bLooping, int32& InOutMeshSampleIndex, FGeometryCacheMeshData*& OutMeshData) override;`
- L27 _public prototype_ `virtual const bool UpdateBoundsData(const float Time, const bool bLooping, const bool bIsPlayingBackward, int32& InOutBoundsSampleIndex, FBox& OutBounds) override;`
- L28 _public prototype_ `virtual const FGeometryCacheTrackSampleInfo& GetSampleInfo(float Time, const bool bLooping) override;`
- L29 _public prototype_ `virtual bool GetMeshDataAtTime(float Time, FGeometryCacheMeshData& OutMeshData) override;`
- L30 _public prototype_ `virtual bool GetMeshDataAtSampleIndex(int32 SampleIndex, FGeometryCacheMeshData& OutMeshData) override;`
- L31 _public prototype_ `virtual void UpdateTime(float Time, bool bLooping) override;`
- L34 _public prototype_ `bool SetSourceFile(const FString& FilePath, class UAbcImportSettings* AbcSettings, float InitialTime = 0.f, bool bIsLooping = true);`
- L35 _public function_ `const FString& GetSourceFile() const`
- L37 _public prototype_ `const int32 FindSampleIndexFromTime(const float Time, const bool bLooping) const;`
- L39 _public function_ `int32 GetEndFrameIndex() const`
- L41 _public prototype_ `bool GetMeshData(int32 SampleIndex, FGeometryCacheMeshData& OutMeshData);`
- L43 _public prototype_ `void SetupGeometryCacheMaterials(class UGeometryCache* GeometryCache);`
- L45 _public prototype_ `FAbcFile& GetAbcFile();`
- L47 _public function_ `const FString& GetAbcTrackHash() const`
- L49 _public prototype_ `bool IsTopologyCompatible(int32 FrameA, int32 FrameB);`
- L52 _private prototype_ `const FGeometryCacheTrackSampleInfo& GetSampleInfo(int32 FrameIndex);`
- L54 _private prototype_ `void Reset();`
- L55 _private prototype_ `void ShowNotification(const FText& Text);`
- L58 _private member_ `FGeometryCacheMeshData MeshData;`
- L59 _private member_ `TArray<FGeometryCacheTrackSampleInfo> SampleInfos;`
- L60 _private member_ `TUniquePtr<FAbcFile> AbcFile;`
- L61 _private member_ `FString SourceFile;`
- L62 _private member_ `FString Hash;`
- L64 _private member_ `int32 StartFrameIndex;`
- L65 _private member_ `int32 EndFrameIndex;`
- L67 _private member_ `TUniquePtr<FGeometryCacheAbcStream> AbcStream;`
