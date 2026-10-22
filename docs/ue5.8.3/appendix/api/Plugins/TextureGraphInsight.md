# Plugins / TextureGraphInsight

- module root: `Plugins/TextureGraph/Source/TextureGraphInsight`
- headers: 13; symbols: 631
- symbol kinds: class=40, delegate=6, enum=1, enumerator=7, function=143, macro=14, member=193, prototype=157, struct=2, typedef=64, union=1, variable=3
- PrivateDependencyModuleNames: Continuable, FreeImage, Function2, Slate, SlateCore, TextureGraphEngine, UMG
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, RHI, RenderCore

### `Plugins/TextureGraph/Source/TextureGraphInsight/Public/Model/TextureGraphInsightObserver.h` (Public)


#### class `TextureGraphInsightDeviceObserver`  
`class TextureGraphInsightDeviceObserver : public DeviceObserverSource`  
_L17-28_
- inherits: `DeviceObserverSource`
- desc: Concrete DeviceObserver interface
- L20 _protected member_ `DeviceType DevType;`
- L23 _protected prototype_ `virtual void DeviceBuffersUpdated(HashNDescArray&& AddedBuffers, HashArray&& RemovedBuffers) override;` — Protected interface of emitters called by the device to notify the observers
- L25 _public prototype_ `TextureGraphInsightDeviceObserver();`
- L26 _public prototype_ `explicit TextureGraphInsightDeviceObserver(DeviceType);`

#### class `TextureGraphInsightBlobberObserver`  
`class TextureGraphInsightBlobberObserver : public BlobberObserverSource`  
_L31-41_
- inherits: `BlobberObserverSource`
- desc: Concrete BlobberObserver interface
- L36 _protected prototype_ `virtual void BlobberUpdated(HashArray&& AddedHashes, HashArray&& RemappedHashes) override;` — Protected interface of emitters called by the device to notify the observers
- L39 _public prototype_ `TextureGraphInsightBlobberObserver();`

#### class `TextureGraphInsightSchedulerObserver`  
`class TextureGraphInsightSchedulerObserver : public SchedulerObserverSource`  
_L44-60_
- inherits: `SchedulerObserverSource`
- desc: Concrete SchedulerObserver interface
- L49 _protected prototype_ `virtual void Start() override;` — Protected interface of emitters called by the scheduler to notify the observers
- L50 _protected prototype_ `virtual void UpdateIdle() override;`
- L51 _protected prototype_ `virtual void Stop() override;`
- L52 _protected prototype_ `virtual void BatchAdded(JobBatchPtr Batch) override;`
- L53 _protected prototype_ `virtual void BatchDone(JobBatchPtr Batch) override;`
- L54 _protected prototype_ `virtual void BatchJobsDone(JobBatchPtr Batch) override;`
- L58 _public prototype_ `TextureGraphInsightSchedulerObserver();`

#### class `TextureGraphInsightEngineObserver`  
`class TextureGraphInsightEngineObserver : public EngineObserverSource`  
_L67-81_
- inherits: `EngineObserverSource`
- desc: Concrete EngineObserver interface Responsible for: 1/ watching the engine life cycle 2/ owning the other system observers, and installing them appropirately when an Engine is active 3/ notifying Insight
- L71 _protected prototype_ `virtual void Created() override;` — Protected interface of emitters called by the engine to notify the observers
- L72 _protected prototype_ `virtual void Destroyed() override;`
- L75 _public prototype_ `TextureGraphInsightEngineObserver();`
- L78 _public member_ `std::shared_ptr<TextureGraphInsightDeviceObserver> _deviceObservers[(uint32)DeviceType::Count];`
- L79 _public member_ `std::shared_ptr<TextureGraphInsightBlobberObserver> BlobberObserver;`
- L80 _public member_ `std::shared_ptr<TextureGraphInsightSchedulerObserver> SchedulerObserver;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHINSIGHT_API`
- L12 _typedef_ `using HashArray = DeviceObserverSource::HashArray;`
- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureGraphInsightObserver, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureGraphInsightObserver, Log, All);`

### `Plugins/TextureGraph/Source/TextureGraphInsight/Public/Model/TextureGraphInsightRecord.h` (Public)


#### class `T_TiledGrid`  
`template <typename DimType> class T_TiledGrid`  
_L15-49_
- L18 _public typedef_ `using Size = DimType;`
- L19 _public typedef_ `using Index = int32_t;`
- L21 _public member_ `Size _rows = 0;`
- L22 _public member_ `Size _cols = 0;`
- L24 _public function_ `T_TiledGrid()`
- L25 _public function_ `T_TiledGrid(Size size) : T_TiledGrid(size, size)`
- L26 _public function_ `T_TiledGrid(Size rows, Size cols) : _rows(rows), _cols(cols)`
- L28 _public function_ `FORCEINLINE Index operator()(Size tx, Size ty) const`
- L29 _public function_ `FORCEINLINE Size Rows() const`
- L30 _public function_ `FORCEINLINE Size Cols() const`
- L31 _public function_ `FORCEINLINE Index NumTiles() const`
- L32 _public function_ `FORCEINLINE bool IsEmpty() const`
- L33 _public function_ `FORCEINLINE bool IsUnique() const`
- L34 _public function_ `FORCEINLINE bool IsTiled() const`
- L36 _public function_ `FORCEINLINE bool IsValidTile(Size tx, Size ty) const`
- L39 _public function_ `template<typename Functor> FORCEINLINE void ForEach(Functor functor) const`

#### class `T_Tiled`  
`template <typename Type> class T_Tiled`  
_L53-83_
- L56 _public typedef_ `using Size = typename TiledGrid::Size;`
- L57 _public typedef_ `using TypeArray = std::vector<Type>;`
- L60 _public member_ `TiledGrid _grid;`
- L61 _public member_ `TypeArray _tiles;`
- L63 _public function_ `T_Tiled()`
- L64 _public function_ `T_Tiled(Size size) : T_Tiled(size, size)`
- L65 _public function_ `T_Tiled(Size rows, Size cols) : _grid(rows, cols)`
- L67 _public function_ `FORCEINLINE void Resize(Size size)`
- L68 _public function_ `FORCEINLINE void Resize(Size rows, Size cols)`
- L69 _public function_ `FORCEINLINE void Resize(TiledGrid grid)`
- L70 _public function_ `FORCEINLINE void Fill(const Type& value)`
- L72 _public function_ `FORCEINLINE const Type& operator()(Size tx, Size ty) const`
- L73 _public function_ `FORCEINLINE Type& operator()(Size tx, Size ty)`
- L74 _public function_ `FORCEINLINE const TiledGrid& Grid() const`
- L80 _public function_ `template<typename Functor> FORCEINLINE void ForEach(Functor functor)`
- L82 _public function_ `template<typename Functor> FORCEINLINE void ForEachGetTile(Functor functor) const`

#### struct `RecordID`  
`struct RecordID`  
_L116-165_
- L138 _public function_ `RecordID(uint8 t, uint32_t p, uint32_t s) :type(t), prim(p), second(s)`
- L139 _public function_ `RecordID(uint64 recordId) :id(recordId)`
- L140 _public prototype_ `RecordID() = default;`
- L142 _public function_ `FORCEINLINE bool IsValid() const`
- L143 _public function_ `FORCEINLINE bool IsBuffer() const`
- L144 _public function_ `FORCEINLINE bool IsDevice() const`
- L145 _public function_ `FORCEINLINE bool IsBlob() const`
- L146 _public function_ `FORCEINLINE bool IsJob() const`
- L147 _public function_ `FORCEINLINE bool IsBatch() const`
- L148 _public function_ `FORCEINLINE bool IsAction() const`
- L149 _public function_ `FORCEINLINE bool IsMix() const`
- L151 _public function_ `FORCEINLINE uint32 Buffer() const`
- L152 _public function_ `FORCEINLINE uint32 Buffer_DeviceType() const`
- L153 _public function_ `FORCEINLINE uint32 Blob() const`
- L154 _public function_ `FORCEINLINE uint32 Batch() const`
- L155 _public function_ `FORCEINLINE uint32 Job() const`
- L156 _public function_ `FORCEINLINE uint32 Action() const`
- L157 _public function_ `FORCEINLINE uint32 Mix() const`
- L159 _public function_ `static RecordID fromBuffer(DeviceType t, uint32_t b)`
- L160 _public function_ `static RecordID fromBlob(uint32_t b)`
- L161 _public function_ `static RecordID fromBatch(uint32_t b)`
- L162 _public function_ `static RecordID fromBatchJob(uint32_t b, uint32_t j)`
- L163 _public function_ `static RecordID fromAction(uint32_t a)`
- L164 _public function_ `static RecordID fromMix(uint32_t a)`

#### enum `RecordID::Type`  
`enum Type : uint8`  
_L118-127_
- L120 _public enumerator_ `kInvalid = 0xFF`
- L121 _public enumerator_ `kBatch = 0`
- L122 _public enumerator_ `kJob`
- L123 _public enumerator_ `kBlob`
- L124 _public enumerator_ `kDeviceBuffer`
- L125 _public enumerator_ `kAction`
- L126 _public enumerator_ `kMix`

#### union `RecordID::(anonymous)`  
``  
_L129-137_

#### struct `RecordID::__anon71687d9d030a::(anonymous)`  
``  
_L131-135_

#### class `DeviceBufferRecord`  
`class DeviceBufferRecord`  
_L172-192_
- L176 _public function_ `DeviceBufferRecord()` — adding a default constructor to enforce this to be a non POD class to successfully initialize
- L178 _public member_ `RecordID SourceID;` — RecordID						_selfID;
- L180 _public member_ `static const DeviceBufferRecord null;`
- L181 _public member_ `DeviceType DevType = DeviceType::Null;`
- L182 _public member_ `uint64 ID = 0;`
- L183 _public member_ `HashType HashValue = 0;`
- L184 _public member_ `HashType PrevHashValue = 0;`
- L185 _public member_ `BufferDescriptor Descriptor;`
- L187 _public member_ `mutable uint64 RawBufferMemSize = 0;` — The true size as informed
- L188 _public member_ `mutable uint64 Rank = 0;`
- L190 _public member_ `mutable bool bErased = false;`
- L191 _public member_ `mutable bool bLeaked = false;`

#### class `BlobRecord`  
`class BlobRecord`  
_L200-234_
- desc: Blob Record
- L204 _public function_ `BlobRecord()` — adding a default constructor to enforce this to be a non POD class to successfully initialize
- L205 _public member_ `RecordID SelfID;`
- L207 _public member_ `static const BlobRecord null;`
- L208 _public member_ `uint32 ReplayCount = 0;`
- L210 _public member_ `FString Name;`
- L212 _public member_ `RecordID SourceID;` — Source job or action or which has generated this Blob
- L214 _public member_ `HashType HashValue = 0;`
- L215 _public member_ `uint32 TexWidth = 0;`
- L216 _public member_ `uint32 TexHeight = 0;`
- L218 _public member_ `uint32 NumMapped = 0;` — if this blob is mapped by other blobs, here is the number of mapping to this
- L219 _public member_ `RecordID MappedID;` — if this blob hash is remapped, here is the remapped to blob ID
- L220 _public member_ `uint64 RawBufferMemSize = 0;` — The true size as informed
- L224 _public member_ `Uint8Tiles TileIdxs;` — A tiled blob reference its sub tile blobs in the following fields _tileIdxs and _uniqueBlobs The tiled information for the blob and the indices of the unique blobs which make the tiles grid
- L225 _public member_ `std::vector<uint16_t> UniqueBlobs;`
- L227 _public function_ `FORCEINLINE const TiledGrid& Grid() const`
- L228 _public function_ `FORCEINLINE bool IsTiled() const`
- L229 _public function_ `FORCEINLINE int32_t NumTiles() const`
- L230 _public function_ `FORCEINLINE RecordID GetTileBlob(uint8_t x, uint8_t y) const`
- L232 _public function_ `FORCEINLINE int32_t NumUniqueBlobs() const`
- L233 _public function_ `FORCEINLINE RecordID GetUniqueBlob(uint8_t i) const`

#### class `JobRecord`  
`class JobRecord`  
_L242-298_
- desc: Individual Job Record is the leaf of the data model It gather meta information to present what the job has done the inputs and output blob
- L246 _public function_ `JobRecord()` — adding a default constructor to enforce this to be a non POD class to successfully initialize
- L247 _public member_ `static const JobRecord GNull;`
- L249 _public member_ `RecordID SelfID;`
- L251 _public member_ `uint32 JobIdx = -1;` — Index of the job in the batch
- L252 _public member_ `int32 PhaseIdx = 0;` — Phase index of the Job within the job
- L255 _public member_ `int Priority = 0;`
- L256 _public member_ `FString TransformName;`
- L258 _public member_ `HashType JobHash = 0;`
- L260 _public member_ `uint32 TexWidth = 0;`
- L261 _public member_ `uint32 TexHeight = 0;`
- L263 _public member_ `double BeginTimeMS = 0;`
- L264 _public member_ `double BeginRunTimeMS = 0;`
- L265 _public member_ `double EndTimeMS = 0;`
- L267 _public member_ `RecordID ResultBlobId;`
- L268 _public member_ `RecordIDArray InputBlobIds;`
- L269 _public member_ `FStringArray InputArgNames;`
- L272 _public member_ `BoolTiles Tiles;` — Information about the tiled job
- L274 _public function_ `FORCEINLINE uint64 GetNumPixels() const`
- L275 _public function_ `FORCEINLINE uint64 GetNumPixelsPerTile() const`
- L277 _public function_ `FORCEINLINE const TiledGrid& GetGrid() const`
- L278 _public function_ `FORCEINLINE bool IsTiled() const`
- L279 _public function_ `FORCEINLINE int32 GetNumTiles() const`
- L281 _public function_ `FORCEINLINE bool IsTileInvalidated(uint8_t x, uint8_t y) const`
- L282 _public function_ `FORCEINLINE int32 GetNumInvalidated() const`
- L284 _public function_ `FORCEINLINE double GetBeginTimeMS() const`
- L285 _public function_ `FORCEINLINE double GetBeginRunTimeMS() const` — Ideal begin runtime, use begin TIme if none assigned
- L286 _public function_ `FORCEINLINE double GetRunTimeMS() const` — Runtime must be positive, clamp to 0
- L287 _public function_ `FORCEINLINE double GetPreRunTimeMS() const`
- L289 _public function_ `FORCEINLINE double GetFillRate() const`
- L291 _public function_ `FORCEINLINE bool IsNoOp() const`
- L293 _public function_ `FORCEINLINE bool IsMainPhase() const`
- L296 _public member_ `bool bIsDone = false;`
- L297 _public member_ `uint32 ReplayCount = 0;`

#### class `BatchRecord`  
`class BatchRecord`  
_L304-341_
- desc: Batch Record Hold the Job Records
- L308 _public function_ `BatchRecord()` — adding a default constructor to enforce this to be a non POD class to successfully initialize
- L310 _public member_ `RecordID SelfID;`
- L312 _public member_ `static const BatchRecord null;`
- L314 _public member_ `RecordID MixID;`
- L316 _public member_ `BatchID BatchID = INVALID_RECORD_ID;`
- L317 _public member_ `FrameID FrameID = INVALID_RECORD_ID;`
- L318 _public member_ `JobRecordArray Jobs;`
- L320 _public member_ `RecordIDArray ResultBlobs;`
- L322 _public member_ `FString Action;`
- L324 _public member_ `double BeginTimeMS = 0;`
- L325 _public member_ `double EndTimeMS = 0;`
- L327 _public member_ `uint16_t NumTiles = 0;`
- L328 _public member_ `uint16_t NumInvalidatedTiles = 0;`
- L330 _public member_ `uint32_t ReplayCount = 0;`
- L332 _public member_ `bool bIsDone = false;`
- L333 _public member_ `bool bIsJobsDone = false;`
- L335 _public member_ `bool bIsNoCache = false;`
- L336 _public member_ `bool bIsFromIdle = false;`
- L338 _public function_ `FORCEINLINE const JobRecord& GetJob(RecordID ID) const`
- L339 _public function_ `FORCEINLINE double ScopeTime_ms() const`

#### class `ActionRecord`  
`class ActionRecord`  
_L348-360_
- desc: Action Record Hold the Action Records
- L352 _public function_ `ActionRecord()` — adding a default constructor to enforce this to be a non POD class to successfully initialize
- L353 _public member_ `static const ActionRecord null;`
- L355 _public member_ `FString Name;`
- L356 _public member_ `FString Meta;`
- L358 _public member_ `mutable RecordID ParentAction;`
- L359 _public member_ `RecordIDArray SubActions;`

#### class `MixRecord`  
`class MixRecord`  
_L367-387_
- desc: Mix Record Hold the Mix Records
- L371 _public function_ `MixRecord()` — adding a default constructor to enforce this to be a non POD class to successfully initialize
- L372 _public member_ `RecordID SelfID;`
- L374 _public member_ `static const MixRecord null;`
- L376 _public member_ `RecordID ParentMixID;` — If mix is an instance, it has a parentMix
- L377 _public function_ `bool IsInstanceMix() const`
- L379 _public member_ `RecordIDArray InstanceMixIDs;` — Or it may have instances
- L380 _public function_ `bool HasInstances() const`
- L382 _public member_ `FString Name;`
- L383 _public member_ `FString AssetName;`
- L385 _public member_ `RecordIDArray Batches;`

#### class `SessionRecord`  
`class SessionRecord`  
_L394-461_
- desc: Session Record container defining the namespace for all the recordIDs
- L397 _private member_ `BatchRecordArray Batches;`
- L398 _private member_ `RecordFromBatchIDMap RecordFromBatchID;`
- L400 _private member_ `DeviceBufferRecordArray DeviceBuffers[(uint32) DeviceType::Count];`
- L401 _private member_ `RecordFromDeviceBufferIDMap BufferFromDeviceBufferIDActive[(uint32)DeviceType::Count];` — Store the current active (or leaked) device buffer in a per device map
- L402 _private member_ `RecordFromDeviceBufferIDMap BufferFromDeviceBufferIDErased;` — Once erased, store all the device buffer in this map
- L403 _private member_ `RecordFromHashMap BufferFromHash;`
- L405 _private member_ `BlobRecordArray Blobs;`
- L406 _private member_ `RecordFromBlobIDMap BlobFromBlobID;`
- L408 _private member_ `ActionRecordArray Actions;`
- L409 _private member_ `RecordFromActionIDMap ActionFromActionID;`
- L411 _private member_ `MixRecordArray Mixes;`
- L412 _private member_ `RecordFromMixIDMap RecordFromMixID;`
- L415 _public function_ `double StartTime_ms() const`
- L418 _public prototype_ `RecordID FindBatchRecord(BatchID InBatchID) const;` — Batch records
- L419 _public typedef_ `using BatchRecordConstructor = std::function<BatchRecord (RecordID RecId)>;`
- L420 _public typedef_ `using BatchRecordEditor = std::function<bool (BatchRecord& r)>;`
- L421 _public prototype_ `RecordID NewBatchRecord(BatchID InBatchID, BatchRecordConstructor Constructor);`
- L422 _public prototype_ `bool EditBatchRecord(RecordID RecId, BatchRecordEditor Editor);`
- L425 _public prototype_ `std::tuple<RecordID, bool> NewDeviceBufferRecord(DeviceType DevType, DeviceBufferID BufferID, const DeviceBufferRecord& Record);` — Device Buffer records
- L426 _public prototype_ `RecordID EraseDeviceBufferRecord(DeviceType DevType, DeviceBufferID BufferID);` — Assuming the db is in the current map, then move its key in the erased map and tag it erased
- L429 _public prototype_ `RecordIDArray FindActiveDeviceBufferRecords(DeviceType DevType, const DeviceBufferIDArray& BufferIDs, RecordIDArray& LeakedBuffers);` — Find the records from the array of bufferIDs & output the leaked buffers
- L431 _public prototype_ `RecordID FindDeviceBufferRecord(DeviceBufferID BufferID) const;`
- L432 _public prototype_ `RecordIDArray FindDeviceBufferRecords(const DeviceBufferIDArray& BufferIDs) const;`
- L433 _public prototype_ `RecordIDArray FetchActiveDeviceBufferIDs(DeviceType DevType) const;`
- L435 _public prototype_ `RecordID FindDeviceBufferRecordFromHash(HashType InHash) const;`
- L438 _public prototype_ `RecordID FindBlobRecord(BlobID InBlobID) const;` — Blob records
- L439 _public typedef_ `using BlobRecordConstructor = std::function<BlobRecord(RecordID RecId)>;`
- L440 _public typedef_ `using BlobRecordEditor = std::function<bool(BlobRecord& r)>;`
- L441 _public prototype_ `RecordID NewBlobRecord(BlobID InBlobID, BlobRecordConstructor Constructor);`
- L442 _public prototype_ `bool EditBlobRecord(RecordID RecId, BlobRecordEditor Editor);`
- L444 _public prototype_ `RecordID NewActionRecord(ActionID InActionID, const ActionRecord& Record);`
- L445 _public prototype_ `RecordID FindActionRecord(ActionID InActionID) const;`
- L448 _public prototype_ `RecordID FindMixRecord(MixID MixID) const;` — Mix records
- L449 _public typedef_ `using MixRecordConstructor = std::function<MixRecord(RecordID RecId)>;`
- L450 _public typedef_ `using MixRecordEditor = std::function<bool(MixRecord& r)>;`
- L451 _public prototype_ `RecordID NewMixRecord(BatchID InBatchID, MixRecordConstructor constructor);`
- L452 _public prototype_ `bool EditMixRecord(RecordID RecId, MixRecordEditor editor);`
- L454 _public function_ `FORCEINLINE const DeviceBufferRecord& GetBuffer(RecordID RecId) const`
- L455 _public function_ `FORCEINLINE const BlobRecord& GetBlob(RecordID RecId) const`
- L456 _public function_ `FORCEINLINE const BatchRecord& GetBatch(RecordID RecId) const`
- L457 _public function_ `FORCEINLINE const JobRecord& GetJob(RecordID RecId) const`
- L458 _public function_ `FORCEINLINE const ActionRecord& GetAction(RecordID RecId) const`
- L459 _public function_ `FORCEINLINE const MixRecord& GetMix(RecordID RecId) const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHINSIGHT_API`
- L12 _typedef_ `using FStringArray = std::vector<FString>;`
- L50 _typedef_ `using TiledGrid = T_TiledGrid<uint8_t>;`
- L82 _function_ `template<typename Functor> FORCEINLINE void ForEachGetTile(Functor functor) const` (scope `T_Tiled::ForEachGetTile`)
- L84 _typedef_ `using BoolTiles = T_Tiled<uint8_t>;`
- L85 _typedef_ `using Uint8Tiles = T_Tiled<uint8_t>;`
- L88 _function_ `template<typename Type> int32_t TiledSum(const T_Tiled<Type>& tiles)`
- L92 _function_ `` (scope `TiledSum`)
- L98 _typedef_ `using DeviceBufferID = uint64;`
- L99 _typedef_ `using DeviceBufferIDArray = std::vector<DeviceBufferID>;`
- L101 _typedef_ `using BlobID = uint64;`
- L103 _typedef_ `using BatchID = uint64;`
- L104 _typedef_ `using FrameID = uint64;`
- L105 _typedef_ `using QueueID = uint32;`
- L107 _typedef_ `using ActionID = uint64;`
- L109 _typedef_ `using MixID = uint64;`
- L112 _variable_ `static const uint16_t INVALID_SHORT = 0xFFFF;`
- L113 _variable_ `static const uint32_t INVALID_INDEX = 0xFFFFFFFF;`
- L114 _variable_ `static const uint64_t INVALID_RECORD_ID = 0xFFFFFFFFFFFFFFFF;`
- L132 _member_ `uint8 type;` (scope `RecordID::__anon71687d9d030a::__anon71687d9d0408`)
- L133 _member_ `uint32_t prim;` (scope `RecordID::__anon71687d9d030a::__anon71687d9d0408`)
- L134 _member_ `uint32_t second : 24;` (scope `RecordID::__anon71687d9d030a::__anon71687d9d0408`)
- L136 _member_ `uint64 id = INVALID_RECORD_ID;` (scope `RecordID::__anon71687d9d030a`)
- L166 _typedef_ `using RecordIDArray = std::vector<RecordID>;`
- L167 _typedef_ `using RecordIDTiles = T_Tiled<RecordID>;`
- L193 _typedef_ `using DeviceBufferRecordArray = std::vector< DeviceBufferRecord >;`
- L194 _typedef_ `using RecordFromDeviceBufferIDMap = std::unordered_map<DeviceBufferID, RecordID>;`
- L195 _typedef_ `using RecordFromHashMap = std::unordered_map<HashType, RecordID>;`
- L235 _typedef_ `using BlobRecordArray = std::vector< BlobRecord >;`
- L236 _typedef_ `using RecordFromBlobIDMap = std::unordered_map<BlobID, RecordID>;`
- L299 _typedef_ `using JobRecordArray = std::vector< JobRecord >;`
- L342 _typedef_ `using BatchRecordArray = std::vector< BatchRecord >;`
- L343 _typedef_ `using RecordFromBatchIDMap = std::unordered_map<BatchID, RecordID>;`
- L361 _typedef_ `using ActionRecordArray = std::vector< ActionRecord >;`
- L362 _typedef_ `using RecordFromActionIDMap = std::unordered_map<ActionID, RecordID>;`
- L388 _typedef_ `using MixRecordArray = std::vector< MixRecord >;`
- L389 _typedef_ `using RecordFromMixIDMap = std::unordered_map<MixID, RecordID>;`
- L463 _typedef_ `using SessionRecordPtr = std::shared_ptr<SessionRecord>;`

### `Plugins/TextureGraph/Source/TextureGraphInsight/Public/Model/TextureGraphInsightSession.h` (Public)


#### class `TextureGraphInsightSession`  
`class TextureGraphInsightSession`  
_L15-171_
- L49 _protected prototype_ `void EngineCreated();` — Protected interface of emitters called by the engine observer
- L50 _protected prototype_ `void EngineDestroyed();`
- L51 _protected prototype_ `void EmitOnEngineReset(bool);`
- L55 _protected prototype_ `uint32 ParseDeviceBuffersCache(DeviceType type, RecordIDArray& addedBufferIds);`
- L56 _protected prototype_ `void DeviceBuffersUpdated(DeviceType DevType, TextureGraphInsightDeviceObserver::HashNDescArray&& AddedBuffers, TextureGraphInsightDeviceObserver::HashArray&& RemovedBuffers);`
- L60 _protected prototype_ `void BlobberHashesUpdated(TextureGraphInsightBlobberObserver::HashArray&& AddedHashes, TextureGraphInsightBlobberObserver::HashArray&& RemappedHashes);`
- L64 _protected prototype_ `void UpdateIdle();` — Protected interface of emitters called by the scheduler observer
- L65 _protected prototype_ `void BatchAdded(JobBatchPtr Batch);`
- L66 _protected prototype_ `void BatchDone(JobBatchPtr Batch);`
- L67 _protected prototype_ `void BatchJobsDone(JobBatchPtr Batch);`
- L70 _protected prototype_ `BatchRecord MakeBatchRecord(RecordID RecId, JobBatchPtr Batch, bool isDone = true);` — manage creation and update of the Batch job records
- L71 _protected prototype_ `void UpdateBatchRecord(JobBatchPtr Batch, BatchRecord& record);`
- L72 _protected prototype_ `JobRecord MakeJobRecord(JobPtrW job, uint32 idx, int32 phaseIdx = 0);`
- L73 _protected prototype_ `void UpdateJobRecord(JobPtrW job, JobRecord& record, double batchBeginTime_ms, double batchEndTime_ms);`
- L77 _protected prototype_ `RecordID FindOrCreateBlobRecordFromHash(HashType hash);` — manage creation and update of the BlobObj records
- L78 _protected prototype_ `RecordID RemapBlobHash(HashType oldHash, HashType newHash);`
- L79 _protected prototype_ `RecordID FindOrCreateBlobRecord(BlobPtr BlobObj, RecordID sourceID = RecordID());`
- L80 _protected prototype_ `BlobRecord MakeBlobRecord(RecordID RecId, BlobPtr BlobObj, RecordID sourceID = RecordID());`
- L81 _protected prototype_ `void EditTiledBlobRecord(BlobRecord& rd, const RecordIDTiles& subTiles);`
- L82 _protected prototype_ `void UpdateBlobRecord(RecordID RecId, BlobPtr BlobObj);`
- L83 _protected member_ `RecordIDArray NewBlobsToNotify;`
- L84 _protected member_ `RecordIDArray MappedBlobsToNotify;`
- L85 _protected prototype_ `void EmitOnNewBlob();`
- L86 _protected prototype_ `void EmitOnMappedBlob();`
- L89 _protected prototype_ `RecordID AssociateBatchToMix(RecordID Batch, MixPtr MixObj);` — manage creation and update of the MixObj records
- L90 _protected prototype_ `RecordID FindOrCreateMixRecord(MixPtr MixObj);`
- L93 _protected member_ `RecordIDArray NewBuffersToNotify;` — manage creation and update of the buffer records
- L97 _protected member_ `SessionRecordPtr Record;` — The session record, collecting all the VALUES A session record is renewed for each engine
- L98 _protected member_ `std::mutex RecordMutex;`
- L102 _protected member_ `std::shared_ptr<LiveCache> Cache;` — Keep all the pointers to "real" TextureGraph Engine objects in the live cache A session live cache is renewed for each engine
- L104 _protected member_ `int32 EngineID = -1;`
- L107 _public prototype_ `TextureGraphInsightSession();`
- L108 _public prototype_ `~TextureGraphInsightSession();`
- L110 _public function_ `FORCEINLINE SessionRecord& GetRecord()`
- L111 _public function_ `FORCEINLINE LiveCache& GetCache()`
- L114 _public prototype_ `void SendToInspector(RecordID RecId) const;` — Send the specified record to be inspected
- L117 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEngineReset, int32);` — Notifier subscription
- L118 _public function_ `FOnEngineReset& OnEngineReset()`
- L120 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnUpdateIdle);`
- L121 _public function_ `FOnUpdateIdle& OnUpdateIdle()`
- L123 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRecordIDArray, const RecordIDArray&);`
- L125 _public function_ `FOnRecordIDArray& OnDeviceBufferAdded()`
- L126 _public function_ `FOnRecordIDArray& OnDeviceBufferRemoved()`
- L127 _public function_ `FOnRecordIDArray& OnBlobAdded()`
- L128 _public function_ `FOnRecordIDArray& OnBlobMapped()`
- L130 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRecordID, RecordID);`
- L132 _public function_ `FOnRecordID& OnBatchAdded()`
- L133 _public function_ `FOnRecordID& OnBatchDone()`
- L134 _public function_ `FOnRecordID& OnBatchJobsDone()`
- L136 _public function_ `FOnRecordID& OnMixAdded()`
- L137 _public function_ `FOnRecordID& OnMixUpdated()`
- L139 _public function_ `FOnRecordID& OnBatchInspected()`
- L140 _public function_ `FOnRecordID& OnJobInspected()`
- L141 _public function_ `FOnRecordID& OnBlobInspected()`
- L142 _public function_ `FOnRecordID& OnBufferInspected()`
- L147 _public prototype_ `bool ReplayBatch(RecordID batchRecordID, bool captureRenderDoc);` — Trigger Replay of Batch and jobs this call is async and returns if the scheduling of the replay is successful or not
- L148 _public prototype_ `bool ReplayJob(RecordID jobRecordID, bool captureRenderDoc);`
- L151 _protected member_ `FOnEngineReset OnEngineResetEvent;`
- L152 _protected member_ `FOnUpdateIdle OnUpdateIdleEvent;`
- L154 _protected member_ `FOnRecordIDArray OnDeviceBufferAddedEvent;`
- L155 _protected member_ `FOnRecordIDArray OnDeviceBufferRemovedEvent;`
- L157 _protected member_ `FOnRecordIDArray OnBlobAddedEvent;`
- L158 _protected member_ `FOnRecordIDArray OnBlobMappedEvent;`
- L160 _protected member_ `FOnRecordID OnBatchAddedEvent;`
- L161 _protected member_ `FOnRecordID OnBatchDoneEvent;`
- L162 _protected member_ `FOnRecordID OnBatchJobsDoneEvent;`
- L164 _protected member_ `FOnRecordID OnMixAddedEvent;`
- L165 _protected member_ `FOnRecordID OnMixUpdatedEvent;`
- L167 _protected member_ `FOnRecordID OnBatchInspectedEvent;`
- L168 _protected member_ `FOnRecordID OnJobInspectedEvent;`
- L169 _protected member_ `FOnRecordID OnBlobInspectedEvent;`
- L170 _protected member_ `FOnRecordID OnBufferInspectedEvent;`

#### class `TextureGraphInsightSession::LiveCache`  
`class LiveCache`  
_L19-43_
- desc: Keep all the pointers to "real" TextureGraph Engine objects in the live runtime cache
- L22 _public function_ `LiveCache(TextureGraphInsightSession* InSession) : Session(InSession)`
- L23 _public member_ `TextureGraphInsightSession* Session = nullptr;`
- L26 _public member_ `std::vector<JobBatchPtrW> Batches;` — TODO: Find a better way to keep the Batch pointer alive, for now, only the last one will still be valid
- L27 _public typedef_ `using BlobEntry= HashType;`
- L28 _public member_ `std::vector<BlobEntry> Blobs;`
- L29 _public member_ `std::vector<MixPtrW> Mixes;`
- L31 _public prototype_ `void AddBlob(RecordID RecId, BlobPtr BlobObj);`
- L32 _public prototype_ `BlobPtr GetBlob(RecordID RecId) const;`
- L34 _public prototype_ `void AddBatch(RecordID RecId, JobBatchPtr Batch);`
- L35 _public prototype_ `JobBatchPtr GetBatch(RecordID RecId) const;`
- L37 _public member_ `uint64 DeviceCacheVersions[(uint32)DeviceType::Count] = { 0, 0, 0, 0, 0, 0 , 0};`
- L39 _public prototype_ `DeviceBufferPtr GetDeviceBuffer(RecordID RecId) const;`
- L41 _public prototype_ `void AddMix(RecordID RecId, MixPtr MixObj);`
- L42 _public prototype_ `MixPtr GetMix(RecordID RecId) const;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEXTUREGRAPHINSIGHT_API`
- L10 _typedef_ `using MixPtr = UMixInterface*;`
- L11 _typedef_ `using MixPtrW = UMixInterface*;`
- L117 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEngineReset, int32);` — Notifier subscription
- L120 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnUpdateIdle);`
- L123 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRecordIDArray, const RecordIDArray&);`
- L130 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRecordID, RecordID);`

### `Plugins/TextureGraph/Source/TextureGraphInsight/Public/TextureGraphInsight.h` (Public)


#### class `FTextureGraphInsightModule`  
`class FTextureGraphInsightModule : public FDefaultGameModuleImpl`  
_L16-20_
- inherits: `FDefaultGameModuleImpl`
- L19 _public prototype_ `virtual void StartupModule() override;`

#### class `TextureGraphInsight`  
`class TextureGraphInsight`  
_L24-44_
- L27 _private member_ `static TextureGraphInsight* GInstance;` — Static instance. Use Create to create a new instance. Destroy the current instance first
- L28 _private prototype_ `TextureGraphInsight();`
- L29 _private prototype_ `~TextureGraphInsight();`
- L31 _private member_ `TextureGraphInsightSessionPtr Session;`
- L33 _public prototype_ `static bool Create();` — Create the Insight Instance ONLY if no other currently created AND if a TextureGraphEngine is already created
- L36 _public prototype_ `static bool Destroy();` — Destroy the current instance
- L41 _public function_ `FORCEINLINE static TextureGraphInsight* Instance()`
- L43 _public function_ `FORCEINLINE TextureGraphInsightSessionPtr GetSession() const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHINSIGHT_API`
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureGraphInsight, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureGraphInsight, Log, All);`
- L14 _typedef_ `using TextureGraphInsightSessionPtr = std::shared_ptr<TextureGraphInsightSession>;`
- L48 _macro_ `#define HashToFString(h) FString::Printf(TEXT("%llX"), (h))` — Macro to control in one place how we display hash value #define HashToFString(h) FString::Printf(TEXT("%20llu"), (h))

### `Plugins/TextureGraph/Source/TextureGraphInsight/Public/View/STextureGraphInsightActionView.h` (Public)


#### class `STextureGraphInsightActionView`  
`class STextureGraphInsightActionView : public SCompoundWidget`  
_L13-49_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(STextureGraphInsightActionView)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L23 _public typedef_ `using FItem = TSharedPtr<FItemData>;`
- L24 _public typedef_ `using FItemArray = TArray< FItem >;`
- L33 _public typedef_ `using SItemTableView = STreeView< FItem >;`
- L36 _public prototype_ `TSharedRef<ITableRow> OnGenerateRowForView(FItem item, const TSharedRef<STableViewBase>& OwnerTable);` — Standard delegates for the view
- L37 _public function_ `FORCEINLINE void OnGetChildrenForView(FItem item, FItemArray& children)`
- L38 _public prototype_ `void OnClickItemForView(FItem item);`
- L39 _public prototype_ `void OnDoubleClickItemForView(FItem item);`
- L42 _public member_ `FItemArray _rootItems;` — The list of root items
- L45 _public member_ `TSharedPtr<SItemTableView> _tableView;` — The TreeView widget
- L47 _public prototype_ `void OnActionNew(RecordID rid);`
- L48 _public prototype_ `void OnEngineReset(int);`

#### class `STextureGraphInsightActionView::FItemData`  
`class FItemData`  
_L25-32_
- L28 _public function_ `FItemData(RecordID rid) : _recordID(rid)`
- L29 _public member_ `TSharedPtr < STextureGraphInsightActionViewRow > _widget;`
- L30 _public member_ `RecordID _recordID;`
- L31 _public member_ `FItemArray _children;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPHINSIGHT_API`

### `Plugins/TextureGraph/Source/TextureGraphInsight/Public/View/STextureGraphInsightBlobView.h` (Public)


#### class `STextureGraphInsightBlobView`  
`class STextureGraphInsightBlobView : public SBorder, public FGCObject`  
_L16-56_
- inherits: `SBorder,FGCObject`
- desc: Need FGCObject to control garbage collection of objects
- L19 _public function_ `SLATE_BEGIN_ARGS(STextureGraphInsightBlobView) : _withHighlight(false)`
- L21 _public prototype_ `SLATE_ARGUMENT(RecordID, recordID) SLATE_ARGUMENT(bool, withHighlight) SLATE_ARGUMENT(BoolTiles, tilesMask) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L29 _public member_ `RecordID _recordID;`
- L30 _public member_ `RecordID _inspectedID;`
- L33 _public member_ `TSharedPtr<FSlateBrush> _brush;` — Needs our own brush to display the blob content
- L34 _public member_ `TObjectPtr<UMaterialInstanceDynamic> _brushMaterial = nullptr;`
- L37 _public member_ `TSharedPtr<FSlateColorBrush> _borderBrush;` — Border brush
- L39 _public prototype_ `FReply OnInspect();`
- L42 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Capture mouse clicks here
- L43 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L46 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L51 _public function_ `virtual FString GetReferencerName() const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHINSIGHT_API`

### `Plugins/TextureGraph/Source/TextureGraphInsight/Public/View/STextureGraphInsightDeviceBufferView.h` (Public)


#### class `STextureGraphInsightDeviceBufferView`  
`class STextureGraphInsightDeviceBufferView : public SBorder, public FGCObject`  
_L14-50_
- inherits: `SBorder,FGCObject`
- desc: Need FGCObject to control garbage collection of objects
- L17 _public function_ `SLATE_BEGIN_ARGS(STextureGraphInsightDeviceBufferView) : _withToolTip(false), _withDescription(false)`
- L20 _public prototype_ `SLATE_ARGUMENT(RecordID, recordID) SLATE_ARGUMENT(RecordID, blobID) SLATE_ARGUMENT(bool, withToolTip) SLATE_ARGUMENT(bool, withDescription) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L28 _public member_ `RecordID _recordID;`
- L29 _public member_ `RecordID _blobID;`
- L30 _public member_ `uint32 _imageWidth = 1;`
- L31 _public member_ `uint32 _imageHeight = 1;`
- L32 _public member_ `FString _imageName;`
- L35 _public member_ `TSharedPtr<FSlateBrush> _brush;` — Needs our own brush to display the blob content
- L36 _public member_ `TObjectPtr<UMaterialInstanceDynamic> _brushMaterial = nullptr;`
- L38 _public prototype_ `void CreateWidgetBrush(UTexture* blobTexture);`
- L39 _public prototype_ `void MakeWidgetMaterial();`
- L41 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L46 _public function_ `virtual FString GetReferencerName() const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHINSIGHT_API`

### `Plugins/TextureGraph/Source/TextureGraphInsight/Public/View/STextureGraphInsightDeviceView.h` (Public)


#### class `STextureGraphInsightDeviceListView`  
`class STextureGraphInsightDeviceListView : public SCompoundWidget`  
_L17-75_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(STextureGraphInsightDeviceListView) : _inspectOnSimpleClick(false), _inspectDevices(true)`
- L22 _public prototype_ `SLATE_ARGUMENT(RecordID, recordID)` — Can use an empty RecordID with type device and the expected Device type to only care about that device
- L31 _public typedef_ `using FItem = TSharedPtr<FItemData>;`
- L32 _public typedef_ `using FItemW = TWeakPtr<FItemData>;`
- L33 _public typedef_ `using FItemArray = TArray< FItem >;`
- L45 _public typedef_ `using SItemTableView = STreeView< FItem >;`
- L48 _public prototype_ `TSharedRef<ITableRow> OnGenerateRowForView(FItem item, const TSharedRef<STableViewBase>& OwnerTable);` — Standard delegates for the view
- L49 _public function_ `FORCEINLINE void OnGetChildrenForView(FItem item, FItemArray& children)`
- L50 _public prototype_ `void OnClickItemForView(FItem item);`
- L51 _public prototype_ `void OnDoubleClickItemForView(FItem item);`
- L52 _public prototype_ `void OnInspect(FItem item);`
- L54 _public member_ `RecordID _rootDevice;` — Can use an empty RecordID parameter with type DeviceBuffer and the expected Device type to only care about that device
- L58 _public member_ `bool _inspectOnSimpleClick = false;` — Inspect on double click always eventually trigger inspect on simple click
- L60 _public member_ `bool _inspectDevices = true;`
- L63 _public member_ `FItemArray _rootItems;` — The list of root items
- L66 _public member_ `TSharedPtr<SItemTableView> _tableView;` — The TreeView widget
- L68 _public prototype_ `void OnDeviceBufferAdded(const RecordIDArray& rids);`
- L69 _public prototype_ `void OnDeviceBufferRemoved(const RecordIDArray& rids);`
- L70 _public prototype_ `void OnEngineReset(int);`
- L72 _public prototype_ `void Reset();`
- L74 _public prototype_ `void RefreshRootItems();`

#### class `STextureGraphInsightDeviceListView::FItemData`  
`class FItemData`  
_L34-44_
- L37 _public function_ `FItemData(RecordID rid, int32 metaItem = 0) : _recordID(rid), _metaItem(metaItem)`
- L38 _public member_ `TSharedPtr < STextureGraphInsightDeviceListViewRow > _widget;`
- L39 _public member_ `RecordID _recordID;`
- L40 _public member_ `FItemArray _children;`
- L41 _public member_ `FItem _removedRoot;`
- L42 _public member_ `const int32 _metaItem = 0;`
- L43 _public member_ `int32 _rank = 0;`

#### class `STextureGraphInsightDeviceView`  
`class STextureGraphInsightDeviceView : public SCompoundWidget`  
_L79-100_
- inherits: `SCompoundWidget`
- L81 _private function_ `SLATE_BEGIN_ARGS(STextureGraphInsightDeviceView)`
- L82 _private prototype_ `SLATE_ARGUMENT(DeviceType, deviceType) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L87 _private member_ `DeviceType _deviceType;`
- L89 _private member_ `TSharedPtr<STextBlock> _mem_percent;`
- L90 _private member_ `TSharedPtr<STextBlock> _mem_number;`
- L91 _private member_ `TSharedPtr<STextBlock> _mem_budget;`
- L93 _private member_ `TSharedPtr<STextBlock> _buffer_percent;`
- L94 _private member_ `TSharedPtr<STextBlock> _buffer_number;`
- L95 _private member_ `TSharedPtr<STextBlock> _buffer_budget;`
- L97 _private member_ `TSharedPtr<STextBlock> _threadCount;`
- L99 _private prototype_ `void Refresh();`

#### class `STextureGraphInsightDeviceManagerView`  
`class STextureGraphInsightDeviceManagerView : public SCompoundWidget`  
_L102-114_
- inherits: `SCompoundWidget`
- L104 _private function_ `SLATE_BEGIN_ARGS(STextureGraphInsightDeviceManagerView)`
- L105 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L109 _private member_ `std::vector < TSharedPtr< STextureGraphInsightDeviceView >> _deviceViews;`
- L111 _private prototype_ `void Reset();` — Rebuild the full ui of this widget, called by update
- L112 _private prototype_ `void OnUpdate();`
- L113 _private prototype_ `void OnEngineReset(int32);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHINSIGHT_API`
- L77 _function_ `inline bool operator ==(const STextureGraphInsightDeviceListView::FItem& i, const RecordID& rid)`

### `Plugins/TextureGraph/Source/TextureGraphInsight/Public/View/STextureGraphInsightInspectorView.h` (Public)


#### class `STextureGraphInsightBatchInspectorView`  
`class STextureGraphInsightBatchInspectorView : public SCompoundWidget`  
_L14-49_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(STextureGraphInsightBatchInspectorView)`
- L18 _public prototype_ `SLATE_ARGUMENT(RecordID, recordID) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L25 _public typedef_ `using FItem = TSharedPtr<FItemData>;`
- L26 _public typedef_ `using FItemArray = TArray< FItem >;`
- L36 _public typedef_ `using SItemTileView = STileView< FItem >;`
- L39 _public prototype_ `TSharedRef<ITableRow> OnGenerateTileForView(FItem item, const TSharedRef<STableViewBase>& OwnerTable);` — Standard delegates for the tree view
- L42 _public member_ `FItemArray _rootItems;` — The list of root items
- L44 _public member_ `TSharedPtr<SItemTileView> _view;` — The TreeView widget
- L48 _public prototype_ `void InspectBatch(RecordID job);` — Inspect the specified batch (Called by Constructor with recordID param)

#### class `STextureGraphInsightBatchInspectorView::FItemData`  
`class FItemData`  
_L27-35_
- L30 _public function_ `FItemData(RecordID batchID) : _batchID(batchID)`
- L31 _public function_ `FItemData(RecordID batchID, int32 targetIdx) : _batchID(batchID), _targetIndex(targetIdx)`
- L33 _public member_ `RecordID _batchID;`
- L34 _public member_ `int32 _targetIndex = -1;` — -1 meaning it is not an input

#### class `STextureGraphInsightJobInspectorView`  
`class STextureGraphInsightJobInspectorView : public SCompoundWidget`  
_L51-91_
- inherits: `SCompoundWidget`
- L54 _public function_ `SLATE_BEGIN_ARGS(STextureGraphInsightJobInspectorView)`
- L55 _public prototype_ `SLATE_ARGUMENT(RecordID, recordID) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L62 _public typedef_ `using FItem = TSharedPtr<FItemData>;`
- L63 _public typedef_ `using FItemArray = TArray< FItem >;`
- L75 _public typedef_ `using SItemTileView = STileView< FItem >;`
- L78 _public prototype_ `TSharedRef<ITableRow> OnGenerateTileForView(FItem item, const TSharedRef<STableViewBase>& OwnerTable);` — Standard delegates for the tree view
- L81 _public member_ `TSharedPtr<STextureGraphInsightBlobView> _outBlobView;` — The output blob view generated by the job
- L84 _public member_ `FItemArray _rootItems;` — The list of root items
- L86 _public member_ `TSharedPtr<SItemTileView> _view;` — The TreeView widget
- L90 _public prototype_ `void InspectJob(RecordID job);` — Inspect the specified Job (Called by Constructor with recordID param)

#### class `STextureGraphInsightJobInspectorView::FItemData`  
`class FItemData`  
_L64-74_
- L67 _public function_ `FItemData(RecordID jobID) : _jobID(jobID)`
- L68 _public function_ `FItemData(RecordID jobID, BoolTiles mask) : _jobID(jobID), _tilesMask(mask)`
- L69 _public function_ `FItemData(RecordID jobID, int32 inputIdx) : _jobID(jobID), _inputIndex(inputIdx)`
- L71 _public member_ `RecordID _jobID;`
- L72 _public member_ `BoolTiles _tilesMask;`
- L73 _public member_ `int32 _inputIndex = -1;` — -1 meaning it is not an input

#### class `STextureGraphInsightBlobInspectorView`  
`class STextureGraphInsightBlobInspectorView : public SCompoundWidget`  
_L94-108_
- inherits: `SCompoundWidget`
- L97 _public function_ `SLATE_BEGIN_ARGS(STextureGraphInsightBlobInspectorView)`
- L98 _public prototype_ `SLATE_ARGUMENT(RecordID, recordID) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L104 _public member_ `TSharedPtr<STextureGraphInsightBlobView> _blobView;` — The main blob view generated by the job
- L107 _public prototype_ `void InspectBlob(RecordID blob);` — Inspect the specified Blob (Called by Constructor with recordID param)

#### class `STextureGraphInsightDeviceBufferInspectorView`  
`class STextureGraphInsightDeviceBufferInspectorView : public SCompoundWidget`  
_L110-122_
- inherits: `SCompoundWidget`
- L113 _public function_ `SLATE_BEGIN_ARGS(STextureGraphInsightDeviceBufferInspectorView)`
- L114 _public prototype_ `SLATE_ARGUMENT(RecordID, recordID) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L121 _public prototype_ `void InspectBuffer(RecordID buffer);` — Inspect the specified buffer (Called by Constructor with recordID param)

#### class `STextureGraphInsightInspectorView`  
`class STextureGraphInsightInspectorView : public SCompoundWidget`  
_L124-140_
- inherits: `SCompoundWidget`
- L127 _public function_ `SLATE_BEGIN_ARGS(STextureGraphInsightInspectorView)`
- L128 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L132 _public member_ `TSharedPtr<STextureGraphInsightRecordTrailView> _recordTrail;`
- L134 _public member_ `TSharedPtr<SOverlay> _stack;`
- L138 _public prototype_ `void OnInspected(RecordID rid);`
- L139 _public prototype_ `void OnEngineReset(int32);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXTUREGRAPHINSIGHT_API`

### `Plugins/TextureGraph/Source/TextureGraphInsight/Public/View/STextureGraphInsightMixView.h` (Public)


#### class `STextureGraphInsightMixListView`  
`class STextureGraphInsightMixListView : public SCompoundWidget`  
_L15-58_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(STextureGraphInsightMixListView)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L25 _public typedef_ `using FItem = TSharedPtr<FItemData>;`
- L26 _public typedef_ `using FItemArray = TArray< FItem >;`
- L36 _public typedef_ `using SItemTableView = STreeView< FItem >;` — using SItemTableView = SListView< FItem >;
- L40 _public prototype_ `TSharedRef<ITableRow> OnGenerateRowForView(FItem item, const TSharedRef<STableViewBase>& OwnerTable);` — Standard delegates for the view
- L41 _public function_ `FORCEINLINE void OnGetChildrenForView(FItem item, FItemArray& children)`
- L42 _public prototype_ `void OnClickItemForView(FItem item);`
- L43 _public prototype_ `void OnDoubleClickItemForView(FItem item);`
- L46 _public member_ `FItemArray _rootItems;` — The list of root items
- L49 _public member_ `TSharedPtr<SItemTableView> _tableView;` — The TreeView widget
- L51 _public prototype_ `void RefreshRootItems();`
- L53 _public prototype_ `void OnMixNew(RecordID rid);`
- L54 _public prototype_ `void OnMixUpdate(RecordID rid);`
- L55 _public prototype_ `void OnEngineReset(int id);`
- L57 _public prototype_ `void UpdateItemData(FItemData& item);`

#### class `STextureGraphInsightMixListView::FItemData`  
`class FItemData`  
_L27-34_
- L30 _public function_ `FItemData(RecordID rid) : _recordID(rid)`
- L31 _public member_ `TSharedPtr < STextureGraphInsightMixListViewRow > _widget;`
- L32 _public member_ `RecordID _recordID;`
- L33 _public member_ `FItemArray _children;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHINSIGHT_API`

### `Plugins/TextureGraph/Source/TextureGraphInsight/Public/View/STextureGraphInsightRecordTrailView.h` (Public)


#### class `STextureGraphInsightRecordTrailView`  
`class STextureGraphInsightRecordTrailView : public SCompoundWidget`  
_L12-27_
- inherits: `SCompoundWidget`
- L14 _private member_ `TSharedPtr< SBreadcrumbTrail<RecordID> > _trail;`
- L16 _public function_ `SLATE_BEGIN_ARGS(STextureGraphInsightRecordTrailView)`
- L17 _public prototype_ `SLATE_ARGUMENT(RecordID, recordID) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L22 _public prototype_ `void Refresh(RecordID rid);`
- L24 _public prototype_ `static RecordID FindRootRecord(RecordID rid);`
- L26 _public prototype_ `void OnCrumbClicked(const RecordID& blob);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPHINSIGHT_API`

### `Plugins/TextureGraph/Source/TextureGraphInsight/Public/View/STextureGraphInsightResourceView.h` (Public)


#### class `STextureGraphInsightResourceView`  
`class STextureGraphInsightResourceView : public SCompoundWidget`  
_L15-56_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(STextureGraphInsightResourceView)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L25 _public typedef_ `using FItem = TSharedPtr<FItemData>;`
- L26 _public typedef_ `using FItemArray = TArray< FItem >;`
- L36 _public typedef_ `using SItemTableView = STreeView< FItem >;` — using SItemTableView = SListView< FItem >;
- L40 _public prototype_ `TSharedRef<ITableRow> OnGenerateRowForView(FItem item, const TSharedRef<STableViewBase>& OwnerTable);` — Standard delegates for the view
- L41 _public function_ `FORCEINLINE void OnGetChildrenForView(FItem item, FItemArray& children)`
- L42 _public prototype_ `void OnClickItemForView(FItem item);`
- L43 _public prototype_ `void OnDoubleClickItemForView(FItem item);`
- L46 _public member_ `FItemArray _rootItems;` — The list of root items
- L49 _public member_ `TSharedPtr<SItemTableView> _tableView;` — The TreeView widget
- L51 _public prototype_ `void RefreshRootItems();`
- L53 _public prototype_ `void OnBlobNew(const RecordIDArray& rids);`
- L54 _public prototype_ `void OnBlobMapped(const RecordIDArray& rids);`
- L55 _public prototype_ `void OnEngineReset(int id);`

#### class `STextureGraphInsightResourceView::FItemData`  
`class FItemData`  
_L27-34_
- L30 _public function_ `FItemData(RecordID rid) : _recordID(rid)`
- L31 _public member_ `TSharedPtr < STextureGraphInsightResourceViewRow > _widget;`
- L32 _public member_ `RecordID _recordID;`
- L33 _public member_ `FItemArray _children;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHINSIGHT_API`

### `Plugins/TextureGraph/Source/TextureGraphInsight/Public/View/STextureGraphInsightSessionView.h` (Public)


#### class `STextureGraphInsightBatchJobView`  
`class STextureGraphInsightBatchJobView : public SCompoundWidget`  
_L16-68_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(STextureGraphInsightBatchJobView) : _inspectOnSimpleClick(false)`
- L21 _public prototype_ `SLATE_ARGUMENT(RecordID, recordID) SLATE_ARGUMENT(bool, inspectOnSimpleClick) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L29 _public typedef_ `using FItem = TSharedPtr<FItemData>;`
- L30 _public typedef_ `using FItemArray = TArray< FItem >;`
- L40 _public typedef_ `using SItemTreeView = STreeView< FItem >;`
- L43 _public prototype_ `TSharedRef<ITableRow> OnGenerateRowForTree(FItem item, const TSharedRef<STableViewBase>& OwnerTable);` — Standard delegates for the tree view
- L44 _public function_ `FORCEINLINE void OnGetChildrenForView(FItem item, FItemArray& children)`
- L45 _public prototype_ `void OnClickItemForTree(FItem item);`
- L46 _public prototype_ `void OnDoubleClickItemForTree(FItem item);`
- L47 _public prototype_ `TSharedPtr<SWidget> OnContextMenuOpeningForTree();`
- L48 _public prototype_ `TSharedPtr<SWidget> OnContextMenuBatch(FItem batchItem);`
- L49 _public prototype_ `TSharedPtr<SWidget> OnContextMenuJob(FItem jobItem);`
- L53 _public member_ `bool _inspectOnSimpleClick = false;` — Inspect on double click always eventually trigger inspect on simple click
- L56 _public member_ `FItemArray _rootItems;` — The list of root items
- L59 _public member_ `TSharedPtr<SItemTreeView> _treeView;` — The TreeView widget
- L62 _public prototype_ `void OnReplayBatch(RecordID batchId, bool captureRenderDoc);`
- L63 _public prototype_ `void OnReplayJob(RecordID batchId, bool captureRenderDoc);`
- L65 _public prototype_ `void OnBatchNew(RecordID batch);`
- L66 _public prototype_ `void OnBatchUpdate(RecordID batch);`
- L67 _public prototype_ `void OnEngineReset(int32);`

#### class `STextureGraphInsightBatchJobView::FItemData`  
`class FItemData`  
_L31-39_
- L34 _public function_ `FItemData(RecordID id, bool isMainPhase = true) : _recordID(id), _isMainPhase(isMainPhase)`
- L35 _public member_ `TSharedPtr < STextureGraphInsightBatchJobViewRow > _widget;`
- L36 _public member_ `RecordID _recordID;`
- L37 _public member_ `FItemArray _children;`
- L38 _public member_ `bool _isMainPhase = true;`

#### class `STextureGraphInsightSessionView`  
`class STextureGraphInsightSessionView : public SCompoundWidget`  
_L71-80_
- inherits: `SCompoundWidget`
- L74 _public function_ `SLATE_BEGIN_ARGS(STextureGraphInsightSessionView)`
- L75 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L79 _public member_ `TSharedPtr<STextureGraphInsightBatchJobView> _batchJobView;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPHINSIGHT_API`
