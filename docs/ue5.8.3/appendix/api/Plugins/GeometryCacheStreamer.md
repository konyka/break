# Plugins / GeometryCacheStreamer

- module root: `Plugins/Runtime/GeometryCache/Source/GeometryCacheStreamer`
- headers: 4; symbols: 69
- symbol kinds: class=4, function=1, macro=3, member=27, prototype=31, struct=2, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, DeveloperSettings, GeometryCache, Slate

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheStreamer/Public/GeometryCacheStreamBase.h` (Public)


#### struct `FGeometryCacheStreamDetails`  
`struct FGeometryCacheStreamDetails`  
_L14-21_
- desc: Details about the animation to be streamed
- L16 _public member_ `int32 NumFrames = 0;`
- L17 _public member_ `float Duration = 0.f;`
- L18 _public member_ `float SecondsPerFrame = 1.f / 24.f;`
- L19 _public member_ `int32 StartFrameIndex = 0;`
- L20 _public member_ `int32 EndFrameIndex = 0;`

#### class `FGeometryCacheStreamBase`  
`class FGeometryCacheStreamBase : public IGeometryCacheStream`  
_L30-83_
- inherits: `IGeometryCacheStream`
- desc: Base class for GeometryCache stream for use with the GeometryCacheStreamer Besides implementing the basic functionalities expected of the stream, it implements basic memory statistics and management for use by the streamer. Derived classes need to implement a way to retrieve the mesh data for a frame through GetMeshData.
- L33 _public prototype_ `FGeometryCacheStreamBase(int32 ReadConcurrency, FGeometryCacheStreamDetails&& Details);`
- L34 _public prototype_ `virtual ~FGeometryCacheStreamBase();`
- L37 _public prototype_ `virtual void Prefetch(int32 StartFrameIndex, int32 NumFrames = 0) override;`
- L38 _public prototype_ `virtual uint32 GetNumFramesNeeded() override;`
- L39 _public prototype_ `virtual bool RequestFrameData() override;`
- L40 _public prototype_ `virtual void UpdateRequestStatus(TArray<int32>& OutFramesCompleted) override;`
- L41 _public prototype_ `virtual bool GetFrameData(int32 FrameIndex, FGeometryCacheMeshData& OutMeshData) override;`
- L42 _public prototype_ `virtual int32 CancelRequests() override;`
- L43 _public prototype_ `virtual const FGeometryCacheStreamStats& GetStreamStats() const override;`
- L44 _public prototype_ `virtual void SetLimits(float MaxMemoryAllowed, float MaxCachedDuration) override;`
- L48 _public prototype_ `void UpdateCurrentFrameIndex(int32 FrameIndex);` — Updates the current position in the stream
- L52 _protected function_ `virtual void PrepareRead()` — Function called from main thread to prepare for GetMeshData
- L55 _protected prototype_ `virtual void GetMeshData(int32 FrameIndex, int32 ReadConcurrencyIndex, FGeometryCacheMeshData& OutMeshData) = 0;` — Derived class must provide a way to get the mesh data for the given FrameIndex, called from worker threads
- L57 _protected prototype_ `void LoadFrameData(int32 FrameIndex);`
- L58 _protected prototype_ `void UpdateFramesNeeded(int32 StartIndex, int32 NumFrames);`
- L59 _protected prototype_ `void IncrementMemoryStat(const FGeometryCacheMeshData& MeshData);`
- L60 _protected prototype_ `void DecrementMemoryStat(const FGeometryCacheMeshData& MeshData);`
- L62 _protected member_ `TArray<int32> ReadIndices;`
- L63 _protected member_ `TArray<FGeometryCacheStreamReadRequest*> ReadRequestsPool;`
- L65 _protected member_ `TArray<int32> FramesNeeded;`
- L66 _protected member_ `TArray<int32> FramesToBeCached;`
- L67 _protected member_ `TArray<FGeometryCacheStreamReadRequest*> FramesRequested;`
- L69 _protected typedef_ `using FFrameIndexToMeshData = TMap<int32, FGeometryCacheMeshData*>;`
- L70 _protected member_ `FFrameIndexToMeshData FramesAvailable;`
- L71 _protected member_ `FRWLock FramesAvailableLock;`
- L73 _protected member_ `FGeometryCacheStreamDetails Details;`
- L74 _protected member_ `mutable FGeometryCacheStreamStats Stats;`
- L75 _protected member_ `int32 CurrentFrameIndex;`
- L76 _protected member_ `int32 MaxCachedFrames;`
- L77 _protected member_ `float MaxCachedDuration;`
- L78 _protected member_ `float MaxMemAllowed;`
- L79 _protected member_ `float MemoryUsed;`
- L81 _protected member_ `std::atomic<bool> bCancellationRequested;`
- L82 _protected member_ `bool bCacheNeedsUpdate;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GEOMETRYCACHESTREAMER_API`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheStreamer/Public/GeometryCacheStreamerSettings.h` (Public)


#### class `UGeometryCacheStreamerSettings`  
`class UGeometryCacheStreamerSettings : public UDeveloperSettings`  
_L13-28_
- reflection: `UCLASS(MinimalAPI, config = Engine, meta = (DisplayName = "Geometry Cache"))`
- inherits: `UDeveloperSettings`
- desc: Settings for the GeometryCache streamer
- L19 _public prototype_ `UGeometryCacheStreamerSettings();`
- L23 _public member_ `float LookAheadBuffer;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Geometry Cache Streamer", meta = (DisplayName = "Look-Ahead Buffer (in seconds)", ClampMin = "0.01", ClampMax = "3600.0"))` — The amount of animation (in seconds) to stream ahead of time (per stream)
- L27 _public member_ `float MaxMemoryAllowed;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Geometry Cache Streamer", meta = (DisplayName = "Maximum Memory Allowed (in MB)", ClampMin = "1.0", ClampMax = "262144.0"))` — The maximum total amount of streamed data allowed in memory (for all streams)

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GEOMETRYCACHESTREAMER_API`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheStreamer/Public/IGeometryCacheStream.h` (Public)


#### class `IGeometryCacheStream`  
`class IGeometryCacheStream`  
_L11-41_
- desc: Interface to stream GeometryCacheMeshData asynchronously from any source through the GeometryCacheStreamer
- L14 _public prototype_ `virtual ~IGeometryCacheStream() = default;`
- L17 _public prototype_ `virtual void Prefetch(int32 StartFrameIndex, int32 NumFrames = 0) = 0;` — Prefetch NumFrames starting from the given StartFrameIndex. If no NumFrames given, prefetch the whole stream
- L20 _public prototype_ `virtual uint32 GetNumFramesNeeded() = 0;` — Return the number of frame indices needed to be loaded
- L23 _public prototype_ `virtual bool RequestFrameData() = 0;` — Request a read of the next frame as determined by the stream. Return true if the request could be handled
- L26 _public prototype_ `virtual void UpdateRequestStatus(TArray<int32>& OutFramesCompleted) = 0;` — Update the status of the read requests currently in progress. Return the frame indices that were completed
- L31 _public prototype_ `virtual bool GetFrameData(int32 FrameIndex, FGeometryCacheMeshData& OutMeshData) = 0;` — Get the MeshData at given FrameIndex without waiting for data to be ready Return true if MeshData could be retrieved
- L34 _public prototype_ `virtual int32 CancelRequests() = 0;` — Cancel the scheduled read requests. Return the number of requests that were canceled
- L37 _public prototype_ `virtual const FGeometryCacheStreamStats& GetStreamStats() const = 0;` — Return the memory usage and related stats for the stream
- L40 _public prototype_ `virtual void SetLimits(float MaxMemoryAllowed, float MaxCachedDuration) = 0;` — Set the memory usage limits for the stream

#### struct `FGeometryCacheStreamStats`  
`struct FGeometryCacheStreamStats`  
_L43-49_
- L45 _public member_ `uint32 NumCachedFrames = 0;` — number of frames currently resident in memory
- L46 _public member_ `float CachedDuration = 0.0f;` — in seconds
- L47 _public member_ `float MemoryUsed = 0.0f;` — in MB
- L48 _public member_ `float AverageBitrate = 0.0f;` — in MB/s

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheStreamer/Public/IGeometryCacheStreamer.h` (Public)


#### class `IGeometryCacheStreamer`  
`class IGeometryCacheStreamer`  
_L14-32_
- desc: Interface to the GeometryCache Streamer that streams data for registered GeometryCacheTracks
- L17 _public prototype_ `static IGeometryCacheStreamer& Get();`
- L20 _public prototype_ `virtual void RegisterTrack(UGeometryCacheTrack* Track, IGeometryCacheStream* Stream) = 0;` — Register the given Track and its associated Stream with the Streamer. The Streamer takes ownership of the Stream
- L23 _public prototype_ `virtual void UnregisterTrack(UGeometryCacheTrack* Track) = 0;` — Unregister the given Track from the Streamer
- L26 _public prototype_ `virtual bool IsTrackRegistered(UGeometryCacheTrack* Track) const = 0;` — Return true if the given Track is registered with the Streamer
- L31 _public prototype_ `virtual bool TryGetFrameData(UGeometryCacheTrack* Track, int32 FrameIndex, FGeometryCacheMeshData& OutMeshData) = 0;` — Get the MeshData for a given Track at given FrameIndex without waiting for data to be ready Return true if MeshData could be retrieved

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GEOMETRYCACHESTREAMER_API`
