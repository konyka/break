# Runtime / LocalFileNetworkReplayStreaming

- module root: `Source/Runtime/NetworkReplayStreaming/LocalFileNetworkReplayStreaming`
- headers: 1; symbols: 339
- symbol kinds: class=10, delegate=1, enum=6, enumerator=51, function=51, member=90, namespace=1, prototype=122, struct=6, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Json, NetworkReplayStreaming

### `Source/Runtime/NetworkReplayStreaming/LocalFileNetworkReplayStreaming/Public/LocalFileNetworkReplayStreaming.h` (Public)


#### struct `FLocalFileReplayCustomVersion`  
`struct FLocalFileReplayCustomVersion`  
_L21-45_
- L42 _public member_ `const static FGuid Guid;` — The GUID for this custom version number
- L44 _public prototype_ `FLocalFileReplayCustomVersion() = delete;`

#### enum `FLocalFileReplayCustomVersion::Type`  
`enum Type`  
_L23-39_
- L26 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made
- L28 _public enumerator_ `FixedSizeFriendlyName = 1`
- L29 _public enumerator_ `CompressionSupport = 2`
- L30 _public enumerator_ `RecordingTimestamp = 3`
- L31 _public enumerator_ `StreamChunkTimes = 4`
- L32 _public enumerator_ `FriendlyNameCharEncoding = 5`
- L33 _public enumerator_ `EncryptionSupport = 6`
- L34 _public enumerator_ `CustomVersions = 7`
- L37 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L38 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### enum `ELocalFileChunkType`  
`enum class ELocalFileChunkType : uint32`  
_L47-54_
- L49 _public enumerator_ `Header`
- L50 _public enumerator_ `ReplayData`
- L51 _public enumerator_ `Checkpoint`
- L52 _public enumerator_ `Event`
- L53 _public enumerator_ `Unknown = 0xFFFFFFFF`

#### enum `EReadReplayInfoFlags`  
`enum class EReadReplayInfoFlags : uint32`  
_L56-60_
- L58 _public enumerator_ `None = 0`
- L59 _public enumerator_ `SkipHeaderChunkTest = 1`

#### enum `EUpdateReplayInfoFlags`  
`enum class EUpdateReplayInfoFlags : uint32`  
_L64-68_
- L66 _public enumerator_ `None = 0`
- L67 _public enumerator_ `FullUpdate = 1`

#### struct `FLocalFileChunkInfo`  
`struct FLocalFileChunkInfo`  
_L73-86_
- desc: Struct to hold chunk metadata
- L75 _public function_ `FLocalFileChunkInfo() : ChunkType(ELocalFileChunkType::Unknown), SizeInBytes(0), TypeOffset(0), DataOffset(0)`
- L82 _public member_ `ELocalFileChunkType ChunkType;`
- L83 _public member_ `int32 SizeInBytes;`
- L84 _public member_ `int64 TypeOffset;`
- L85 _public member_ `int64 DataOffset;`

#### struct `FLocalFileReplayDataInfo`  
`struct FLocalFileReplayDataInfo`  
_L89-108_
- desc: Struct to hold replay data chunk metadata
- L91 _public function_ `FLocalFileReplayDataInfo() : ChunkIndex(INDEX_NONE), Time1(0), Time2(0), SizeInBytes(0), MemorySizeInBytes(0), ReplayDataOffset(0), StreamOffset(0)`
- L101 _public member_ `int32 ChunkIndex;`
- L102 _public member_ `uint32 Time1;`
- L103 _public member_ `uint32 Time2;`
- L104 _public member_ `int32 SizeInBytes;`
- L105 _public member_ `int32 MemorySizeInBytes;`
- L106 _public member_ `int64 ReplayDataOffset;`
- L107 _public member_ `int64 StreamOffset;`

#### struct `FLocalFileEventInfo`  
`struct FLocalFileEventInfo`  
_L111-133_
- desc: Struct to hold event metadata
- L113 _public function_ `FLocalFileEventInfo() : ChunkIndex(INDEX_NONE), Time1(0), Time2(0), SizeInBytes(0), EventDataOffset(0)`
- L121 _public member_ `int32 ChunkIndex;`
- L123 _public member_ `FString Id;`
- L124 _public member_ `FString Group;`
- L125 _public member_ `FString Metadata;`
- L126 _public member_ `uint32 Time1;`
- L127 _public member_ `uint32 Time2;`
- L129 _public member_ `int32 SizeInBytes;`
- L130 _public member_ `int64 EventDataOffset;`
- L132 _public prototype_ `void CountBytes(FArchive& Ar) const;`

#### struct `FLocalFileReplayInfo`  
`struct FLocalFileReplayInfo`  
_L136-172_
- desc: Struct to hold metadata about an entire replay
- L138 _public function_ `FLocalFileReplayInfo() : LengthInMS(0), NetworkVersion(0), Changelist(0), Timestamp(0), TotalDataSizeInBytes(0), bIsLive(false), bIsValid(false), bCompressed(false), bEncrypted(false), HeaderChunkIndex(INDEX_NONE)`
- L151 _public member_ `int32 LengthInMS;`
- L152 _public member_ `uint32 NetworkVersion;`
- L153 _public member_ `uint32 Changelist;`
- L154 _public member_ `FString FriendlyName;`
- L155 _public member_ `FDateTime Timestamp;`
- L156 _public member_ `int64 TotalDataSizeInBytes;`
- L157 _public member_ `bool bIsLive;`
- L158 _public member_ `bool bIsValid;`
- L159 _public member_ `bool bCompressed;`
- L161 _public member_ `bool bEncrypted;`
- L162 _public member_ `TArray<uint8> EncryptionKey;`
- L164 _public member_ `int32 HeaderChunkIndex;`
- L166 _public member_ `TArray<FLocalFileChunkInfo> Chunks;`
- L167 _public member_ `TArray<FLocalFileEventInfo> Checkpoints;`
- L168 _public member_ `TArray<FLocalFileEventInfo> Events;`
- L169 _public member_ `TArray<FLocalFileReplayDataInfo> DataChunks;`
- L171 _public prototype_ `void CountBytes(FArchive& Ar) const;`

#### class `FLocalFileStreamFArchive`  
`class FLocalFileStreamFArchive : public FArchive`  
_L175-210_
- inherits: `FArchive`
- desc: Archive to wrap the file reader and respect chunk boundaries
- L179 _public function_ `FLocalFileStreamFArchive() : Pos(0), bAtEndOfReplay(false)`
- L180 _public prototype_ `FLocalFileStreamFArchive(const FLocalFileStreamFArchive&) = default;`
- L181 _public prototype_ `FLocalFileStreamFArchive& operator=(const FLocalFileStreamFArchive&) = default;`
- L184 _public prototype_ `virtual void Serialize(void* V, int64 Length) override;`
- L185 _public prototype_ `virtual int64 Tell() override;`
- L186 _public prototype_ `virtual int64 TotalSize() override;`
- L187 _public prototype_ `virtual void Seek(int64 InPos) override;`
- L188 _public prototype_ `virtual bool AtEnd() override;`
- L190 _public prototype_ `int64 Tell() const;`
- L191 _public prototype_ `int64 TotalSize() const;`
- L193 _public function_ `void Reset()`
- L203 _public member_ `TArray<uint8> Buffer;`
- L205 _public member_ `int32 Pos;` — `UE_DEPRECATED(5.3, "Please use Tell/Seek instead")`
- L206 _public member_ `bool bAtEndOfReplay;`
- L209 _private member_ `int64 ArchivePos = 0;`

#### enum `EQueuedLocalFileRequestType::Type`  
`enum Type`  
_L214-236_
- L216 _public enumerator_ `StartRecording`
- L217 _public enumerator_ `WriteHeader`
- L218 _public enumerator_ `WritingHeader`
- L219 _public enumerator_ `WritingStream`
- L220 _public enumerator_ `StopRecording`
- L221 _public enumerator_ `StartPlayback`
- L222 _public enumerator_ `ReadingHeader`
- L223 _public enumerator_ `ReadingStream`
- L224 _public enumerator_ `EnumeratingStreams`
- L225 _public enumerator_ `WritingCheckpoint`
- L226 _public enumerator_ `ReadingCheckpoint`
- L227 _public enumerator_ `UpdatingEvent`
- L228 _public enumerator_ `EnumeratingEvents`
- L229 _public enumerator_ `RequestingEvent`
- L230 _public enumerator_ `StopStreaming`
- L231 _public enumerator_ `DeletingFinishedStream`
- L232 _public enumerator_ `RefreshingLiveStream`
- L233 _public enumerator_ `KeepReplay`
- L234 _public enumerator_ `RenameReplay`
- L235 _public enumerator_ `RenameReplayFriendlyName`

#### enum `ELocalFileReplayResult`  
`enum class ELocalFileReplayResult : uint32`  
_L289-303_
- reflection: `UENUM()`
- L291 _public enumerator_ `Success`
- L292 _public enumerator_ `InvalidReplayInfo`
- L293 _public enumerator_ `StreamChunkIndexMismatch`
- L294 _public enumerator_ `DecompressBuffer`
- L295 _public enumerator_ `CompressionNotSupported`
- L296 _public enumerator_ `DecryptBuffer`
- L297 _public enumerator_ `EncryptionNotSupported`
- L298 _public enumerator_ `EncryptBuffer`
- L299 _public enumerator_ `CompressBuffer`
- L300 _public enumerator_ `InvalidName`
- L301 _public enumerator_ `FileWriter`
- L302 _public enumerator_ `Unknown`

#### class `FCachedFileRequest`  
`class FCachedFileRequest`  
_L309-326_
- L312 _public function_ `FCachedFileRequest(const TArray<uint8>& InRequestData, const double InLastAccessTime) : RequestData(InRequestData) , LastAccessTime(InLastAccessTime)`
- L318 _public function_ `FCachedFileRequest(TArray<uint8>&& InRequestData, const double InLastAccessTime) : RequestData(MoveTemp(InRequestData)) , LastAccessTime(InLastAccessTime)`
- L324 _public member_ `TArray<uint8> RequestData;`
- L325 _public member_ `double LastAccessTime;`

#### class `FQueuedLocalFileRequest`  
`class FQueuedLocalFileRequest`  
_L328-352_
- L331 _public function_ `FQueuedLocalFileRequest(const TSharedPtr<FLocalFileNetworkReplayStreamer>& InStreamer, EQueuedLocalFileRequestType::Type InType) : Streamer(InStreamer) , RequestType(InType) , bCancelled(false)`
- L338 _public prototype_ `virtual ~FQueuedLocalFileRequest() = default;`
- L340 _public function_ `EQueuedLocalFileRequestType::Type GetRequestType() const`
- L342 _public function_ `virtual bool GetCachedRequest()`
- L343 _public prototype_ `virtual void IssueRequest() = 0;`
- L344 _public prototype_ `virtual void FinishRequest() = 0;`
- L346 _public prototype_ `void CancelRequest();`
- L349 _protected member_ `TSharedPtr<FLocalFileNetworkReplayStreamer> Streamer;`
- L350 _protected member_ `EQueuedLocalFileRequestType::Type RequestType;`
- L351 _protected member_ `FThreadSafeBool bCancelled;`

#### class `FGenericQueuedLocalFileRequest`  
`class FGenericQueuedLocalFileRequest : public FQueuedLocalFileRequest, public TSharedFromThis<FGenericQueuedLocalFileRequest, ESPMode::ThreadSafe>`  
_L354-370_
- inherits: `FQueuedLocalFileRequest,TSharedFromThis<FGenericQueuedLocalFileRequest,ESPMode::ThreadSafe>`
- L357 _public function_ `FGenericQueuedLocalFileRequest(const TSharedPtr<FLocalFileNetworkReplayStreamer>& InStreamer, EQueuedLocalFileRequestType::Type InType, TFunction<void()>&& InFunction, TFunction<void()>&& InCompletionCallback) : FQueuedLocalFileRequest(InStreamer, InType) , RequestFunction(MoveTemp(InFunction)) , CompletionCallback(MoveTemp(InCompletionCallback))`
- L364 _public prototype_ `virtual void IssueRequest() override;`
- L365 _public prototype_ `virtual void FinishRequest() override;`
- L368 _protected member_ `TFunction<void()> RequestFunction;`
- L369 _protected member_ `TFunction<void()> CompletionCallback;`

#### class `TLocalFileAsyncGraphTask`  
`template<typename ResultType> class TLocalFileAsyncGraphTask : public FAsyncGraphTaskBase`  
_L373-406_
- inherits: `FAsyncGraphTaskBase`
- L376 _public function_ `TLocalFileAsyncGraphTask(TFunction<ResultType()>&& InFunction, TPromise<ResultType>&& InPromise) : Function(MoveTemp(InFunction)) , Promise(MoveTemp(InPromise))`
- L383 _public function_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)`
- L388 _public function_ `ENamedThreads::Type GetDesiredThread()`
- L393 _public function_ `TStatId GetStatId() const`
- L398 _public function_ `TFuture<ResultType> GetFuture()`
- L404 _private member_ `TFunction<ResultType()> Function;`
- L405 _private member_ `TPromise<ResultType> Promise;`

#### class `TGenericQueuedLocalFileRequest`  
`template <typename StorageType> class TGenericQueuedLocalFileRequest : public FQueuedLocalFileRequest, public TSharedFromThis<TGenericQueuedLocalFileRequest<StorageType>, ESPMode::ThreadSafe>`  
_L409-459_
- inherits: `FQueuedLocalFileRequest,TSharedFromThis<TGenericQueuedLocalFileRequest<StorageType>,ESPMode::ThreadSafe>`
- L412 _public function_ `TGenericQueuedLocalFileRequest(const TSharedPtr<FLocalFileNetworkReplayStreamer>& InStreamer, EQueuedLocalFileRequestType::Type InType, TFunction<void(StorageType&)>&& InFunction, TFunction<void(StorageType&)>&& InCompletionCallback) : FQueuedLocalFileRequest(InStreamer, InType) , Storage() , RequestFunction(MoveTemp(InFunction)) , CompletionCallback(MoveTemp(InCompletionCallback))`
- L420 _public function_ `virtual void IssueRequest() override`
- L441 _public function_ `virtual void FinishRequest() override`
- L454 _public member_ `StorageType Storage;`
- L457 _protected member_ `TFunction<void(StorageType&)> RequestFunction;`
- L458 _protected member_ `TFunction<void(StorageType&)> CompletionCallback;`

#### class `TLocalFileRequestCommonData`  
`template <typename DelegateResultType> class TLocalFileRequestCommonData`  
_L462-476_
- L465 _public member_ `DelegateResultType DelegateResult;`
- L468 _public member_ `FLocalFileReplayInfo ReplayInfo;` — `UE_DEPRECATED(5.3, "No longer used")`
- L470 _public member_ `TArray<uint8> DataBuffer;`
- L473 _public member_ `bool bAsyncError = false;` — `UE_DEPRECATED(5.1, "No longer used")`
- L475 _public member_ `ELocalFileReplayResult AsyncError = ELocalFileReplayResult::Success;`

#### class `TGenericCachedLocalFileRequest`  
`template <typename DelegateResultType> class TGenericCachedLocalFileRequest : public TGenericQueuedLocalFileRequest<TLocalFileRequestCommonData<DelegateResultType>>`  
_L479-503_
- inherits: `TGenericQueuedLocalFileRequest<TLocalFileRequestCommonData<DelegateResultType>>`
- L482 _public function_ `TGenericCachedLocalFileRequest(int32 InCacheKey, const TSharedPtr<FLocalFileNetworkReplayStreamer>& InStreamer, EQueuedLocalFileRequestType::Type InType, TFunction<void(TLocalFileRequestCommonData<DelegateResultType>&)>&& InFunction, TFunction<void(TLocalFileRequestCommonData<DelegateResultType>&)>&& InCompletionCallback) : TGenericQueuedLocalFileRequest<TLocalFileRequestCommonData<DelegateResultType>>(InStreamer, InType, MoveTemp(InFunction), MoveTemp(InCompletionCallback)) , CacheKey(InCacheKey)`
- L487 _public function_ `virtual bool GetCachedRequest() override`
- L502 _protected member_ `int32 CacheKey;`

#### class `FLocalFileNetworkReplayStreamer`  
`class FLocalFileNetworkReplayStreamer : public INetworkReplayStreamer, public TSharedFromThis<FLocalFileNetworkReplayStreamer>`  
_L508-797_
- inherits: `INetworkReplayStreamer,TSharedFromThis<FLocalFileNetworkReplayStreamer>`
- desc: Local file streamer that supports playback/recording to a single file on disk
- L510 _private typedef_ `using FLocalFileReplayResult = UE::Net::TNetResult<ELocalFileReplayResult>;`
- L513 _public prototype_ `FLocalFileNetworkReplayStreamer();`
- L514 _public prototype_ `FLocalFileNetworkReplayStreamer(const FString& InDemoSavePath);`
- L515 _public prototype_ `virtual ~FLocalFileNetworkReplayStreamer();`
- L518 _public prototype_ `virtual void StartStreaming(const FStartStreamingParameters& Params, const FStartStreamingCallback& Delegate) override;` — INetworkReplayStreamer implementation
- L519 _public prototype_ `virtual void StopStreaming() override;`
- L520 _public prototype_ `virtual FArchive* GetHeaderArchive() override;`
- L521 _public prototype_ `virtual FArchive* GetStreamingArchive() override;`
- L522 _public prototype_ `virtual FArchive* GetCheckpointArchive() override;`
- L523 _public prototype_ `virtual void FlushCheckpoint(const uint32 TimeInMS) override;`
- L524 _public prototype_ `virtual void GotoCheckpointIndex(const int32 CheckpointIndex, const FGotoCallback& Delegate, EReplayCheckpointType CheckpointType) override;`
- L525 _public prototype_ `virtual void GotoTimeInMS(const uint32 TimeInMS, const FGotoCallback& Delegate, EReplayCheckpointType CheckpointType) override;`
- L526 _public prototype_ `virtual void UpdateTotalDemoTime(uint32 TimeInMS) override;`
- L527 _public function_ `virtual void UpdatePlaybackTime(uint32 TimeInMS) override`
- L528 _public function_ `virtual uint32 GetTotalDemoTime() const override`
- L529 _public prototype_ `virtual bool IsDataAvailable() const override;`
- L530 _public prototype_ `virtual void SetHighPriorityTimeRange(const uint32 StartTimeInMS, const uint32 EndTimeInMS) override;`
- L531 _public prototype_ `virtual bool IsDataAvailableForTimeRange(const uint32 StartTimeInMS, const uint32 EndTimeInMS) override;`
- L532 _public prototype_ `virtual bool IsLoadingCheckpoint() const override;`
- L533 _public prototype_ `virtual bool IsLive() const override;`
- L534 _public prototype_ `virtual void DeleteFinishedStream(const FString& StreamName, const FDeleteFinishedStreamCallback& Delegate) override;`
- L535 _public prototype_ `virtual void DeleteFinishedStream( const FString& StreamName, const int32 UserIndex, const FDeleteFinishedStreamCallback& Delegate ) override;`
- L536 _public prototype_ `virtual void EnumerateStreams( const FNetworkReplayVersion& InReplayVersion, const int32 UserIndex, const FString& MetaString, const TArray< FString >& ExtraParms, const FEnumerateStreamsCallback& Delegate ) override;`
- L537 _public prototype_ `virtual void EnumerateRecentStreams( const FNetworkReplayVersion& ReplayVersion, const int32 UserIndex, const FEnumerateStreamsCallback& Delegate ) override;`
- L538 _public prototype_ `virtual void AddUserToReplay(const FString& UserString) override;`
- L539 _public prototype_ `virtual void AddEvent(const uint32 TimeInMS, const FString& Group, const FString& Meta, const TArray<uint8>& Data) override;`
- L540 _public prototype_ `virtual void AddOrUpdateEvent(const FString& Name, const uint32 TimeInMS, const FString& Group, const FString& Meta, const TArray<uint8>& Data) override;`
- L541 _public prototype_ `virtual void EnumerateEvents(const FString& Group, const FEnumerateEventsCallback& Delegate) override;`
- L542 _public prototype_ `virtual void EnumerateEvents(const FString& ReplayName, const FString& Group, const FEnumerateEventsCallback& Delegate) override;`
- L543 _public prototype_ `virtual void EnumerateEvents( const FString& ReplayName, const FString& Group, const int32 UserIndex, const FEnumerateEventsCallback& Delegate ) override;`
- L544 _public prototype_ `virtual void RequestEventData(const FString& EventID, const FRequestEventDataCallback& Delegate) override;`
- L545 _public prototype_ `virtual void RequestEventData(const FString& ReplayName, const FString& EventID, const FRequestEventDataCallback& Delegate) override;`
- L546 _public prototype_ `virtual void RequestEventData(const FString& ReplayName, const FString& EventId, const int32 UserIndex, const FRequestEventDataCallback& Delegate) override;`
- L547 _public prototype_ `virtual void RequestEventGroupData(const FString& Group, const FRequestEventGroupDataCallback& Delegate) override;`
- L548 _public prototype_ `virtual void RequestEventGroupData(const FString& ReplayName, const FString& Group, const FRequestEventGroupDataCallback& Delegate) override;`
- L549 _public prototype_ `virtual void RequestEventGroupData(const FString& ReplayName, const FString& Group, const int32 UserIndex, const FRequestEventGroupDataCallback& Delegate) override;`
- L550 _public prototype_ `virtual void SearchEvents(const FString& EventGroup, const FSearchEventsCallback& Delegate) override;`
- L551 _public prototype_ `virtual void KeepReplay(const FString& ReplayName, const bool bKeep, const FKeepReplayCallback& Delegate) override;`
- L552 _public prototype_ `virtual void KeepReplay(const FString& ReplayName, const bool bKeep, const int32 UserIndex, const FKeepReplayCallback& Delegate) override;`
- L553 _public prototype_ `virtual void RenameReplayFriendlyName(const FString& ReplayName, const FString& NewFriendlyName, const FRenameReplayCallback& Delegate) override;`
- L554 _public prototype_ `virtual void RenameReplayFriendlyName(const FString& ReplayName, const FString& NewFriendlyName, const int32 UserIndex, const FRenameReplayCallback& Delegate) override;`
- L555 _public prototype_ `virtual void RenameReplay(const FString& ReplayName, const FString& NewName, const FRenameReplayCallback& Delegate) override;`
- L556 _public prototype_ `virtual void RenameReplay(const FString& ReplayName, const FString& NewName, const int32 UserIndex, const FRenameReplayCallback& Delegate) override;`
- L557 _public function_ `virtual FString GetReplayID() const override`
- L558 _public function_ `virtual EReplayStreamerState GetReplayStreamerState() const override`
- L559 _public function_ `virtual void SetTimeBufferHintSeconds(const float InTimeBufferHintSeconds) override`
- L560 _public prototype_ `virtual void RefreshHeader() override;`
- L561 _public prototype_ `virtual void DownloadHeader(const FDownloadHeaderCallback& Delegate) override;`
- L563 _public prototype_ `virtual bool IsCheckpointTypeSupported(EReplayCheckpointType CheckpointType) const override;`
- L565 _public function_ `virtual bool SupportsCompression() const`
- L567 _public function_ `virtual bool DecompressBuffer(const TArray<uint8>& InCompressed, TArray<uint8>& OutBuffer) const`
- L568 _public function_ `virtual bool CompressBuffer(const TArray<uint8>& InBuffer, TArray<uint8>& OutCompressed) const`
- L570 _public function_ `virtual bool SupportsEncryption() const`
- L571 _public function_ `virtual void GenerateEncryptionKey(TArray<uint8>& EncryptionKey)`
- L572 _public function_ `virtual bool EncryptBuffer(TArrayView<const uint8> Plaintext, TArray<uint8>& Ciphertext, TArrayView<const uint8> EncryptionKey) const`
- L573 _public function_ `virtual bool DecryptBuffer(TArrayView<const uint8> Ciphertext, TArray<uint8>& Plaintext, TArrayView<const uint8> EncryptionKey) const`
- L575 _public prototype_ `bool AllowEncryptedWrite() const;`
- L577 _public prototype_ `void Tick(float DeltaSeconds);`
- L579 _public prototype_ `virtual uint32 GetMaxFriendlyNameSize() const override;`
- L581 _public function_ `virtual EStreamingOperationResult SetDemoPath(const FString& DemoPath) override`
- L594 _public function_ `virtual EStreamingOperationResult GetDemoPath(FString& DemoPath) const override`
- L600 _public prototype_ `void OnFileRequestComplete(const TSharedPtr<FQueuedLocalFileRequest, ESPMode::ThreadSafe>& Request);`
- L602 _public prototype_ `bool IsStreaming() const;`
- L604 _public prototype_ `bool HasPendingFileRequests() const;`
- L606 _public function_ `void AddSimpleRequestToQueue(EQueuedLocalFileRequestType::Type RequestType, TFunction<void()>&& InFunction, TFunction<void()>&& InCompletionCallback)`
- L612 _public function_ `template <typename StorageType> void AddGenericRequestToQueue(EQueuedLocalFileRequestType::Type RequestType, TFunction<void(StorageType&)>&& InFunction, TFunction<void(StorageType&)>&& InCompletionCallback)`
- L618 _public function_ `template<typename DelegateResultType> void AddDelegateFileRequestToQueue(EQueuedLocalFileRequestType::Type RequestType, TFunction<void(TLocalFileRequestCommonData<DelegateResultType>&)>&& InFunction, TFunction<void(TLocalFileRequestCommonData<DelegateResultType>&)>&& InCompletionCallback)`
- L624 _public function_ `template<typename DelegateType, typename DelegateResultType> void AddDelegateFileRequestToQueue(EQueuedLocalFileRequestType::Type RequestType, const DelegateType& Delegate, TFunction<void(TLocalFileRequestCommonData<DelegateResultType>&)>&& InFunction)`
- L634 _public function_ `template<typename DelegateResultType> void AddCachedFileRequestToQueue(EQueuedLocalFileRequestType::Type RequestType, int32 InCacheKey, TFunction<void(TLocalFileRequestCommonData<DelegateResultType>&)>&& InFunction, TFunction<void(TLocalFileRequestCommonData<DelegateResultType>&)>&& InCompletionCallback)`
- L640 _public member_ `TSharedPtr<FArchive> LocalFileAr;` — Current stream Archive
- L643 _public member_ `TMap<int32, TSharedPtr<FCachedFileRequest>> RequestCache;` — Map of chunk index to cached value
- L646 _public member_ `TMap<int32, TSharedPtr<FCachedFileRequest>> DeltaCheckpointCache;` — Map of checkpoint index to cached value
- L648 _public member_ `static FOnLocalFileReplayFinishedWriting OnReplayFinishedWriting;`
- L650 _public function_ `TFunction<void(TFunction<void()> Complete)> PostHeaderDownloaded = [](TFunction<void()> Complete)`
- L650 _public member_ `TFunction<void(TFunction<void()> Complete)> PostHeaderDownloaded = [](TFunction<void()> Complete) { Complete(); };`
- L654 _protected prototype_ `void DeleteFinishedStream_Internal(const FString& StreamName, const int32 UserIndex, const FDeleteFinishedStreamCallback& Delegate);`
- L655 _protected prototype_ `void EnumerateEvents_Internal(const FString& ReplayName, const FString& Group, const int32 UserIndex, const FEnumerateEventsCallback& Delegate);`
- L656 _protected prototype_ `void RequestEventData_Internal(const FString& ReplayName, const FString& EventId, const int32 UserIndex, const FRequestEventDataCallback& Delegate);`
- L657 _protected prototype_ `void KeepReplay_Internal(const FString& ReplayName, const bool bKeep, const int32 UserIndex, const FKeepReplayCallback& Delegate);`
- L658 _protected prototype_ `void RenameReplayFriendlyName_Internal(const FString& ReplayName, const FString& NewFriendlyName, const int32 UserIndex, const FRenameReplayCallback& Delegate);`
- L659 _protected prototype_ `void RenameReplay_Internal(const FString& ReplayName, const FString& NewName, const int32 UserIndex, const FRenameReplayCallback& Delegate);`
- L668 _protected member_ `FLocalFileReplayInfo CurrentReplayInfo;` — Currently playing or recording replay metadata The values may not accurately reflect what is currently on disk during recording.  They will be updated as each queued task completes on the game thread.
- L670 _protected member_ `TInterval<uint32> StreamTimeRange;`
- L671 _protected member_ `int64 StreamDataOffset;`
- L673 _protected member_ `int32 StreamChunkIndex;`
- L674 _protected member_ `double LastChunkTime;`
- L675 _protected member_ `double LastRefreshTime;`
- L676 _protected member_ `bool bStopStreamingCalled;`
- L677 _protected member_ `uint32 HighPriorityEndTime;`
- L678 _protected member_ `int64 LastGotoTimeInMS;`
- L680 _protected member_ `TArray<TSharedPtr<FQueuedLocalFileRequest, ESPMode::ThreadSafe>> QueuedRequests;`
- L681 _protected member_ `TSharedPtr<FQueuedLocalFileRequest, ESPMode::ThreadSafe> ActiveRequest;`
- L683 _protected prototype_ `bool ProcessNextFileRequest();`
- L684 _protected prototype_ `bool IsFileRequestInProgress() const;`
- L685 _protected prototype_ `bool IsFileRequestPendingOrInProgress(const EQueuedLocalFileRequestType::Type RequestType) const;`
- L686 _protected prototype_ `void CancelStreamingRequests();`
- L690 _protected function_ `void SetLastError(const ENetworkReplayError::Type InLastError)` — `UE_DEPRECATED(5.1, "No longer used")`
- L696 _protected prototype_ `void SetLastError(FLocalFileReplayResult&& Result);`
- L698 _protected prototype_ `void ConditionallyFlushStream();`
- L699 _protected prototype_ `void ConditionallyLoadNextChunk();`
- L700 _protected prototype_ `void ConditionallyRefreshReplayInfo();`
- L702 _protected prototype_ `void FlushCheckpointInternal(const uint32 TimeInMS);`
- L717 _protected function_ `bool ReadReplayInfo(const FString& StreamName, FLocalFileReplayInfo& OutReplayInfo) const`
- L722 _protected prototype_ `bool ReadReplayInfo(const FString& StreamName, FLocalFileReplayInfo& OutReplayInfo, EReadReplayInfoFlags Flags) const;`
- L723 _protected prototype_ `bool ReadReplayInfo(FArchive& Archive, FLocalFileReplayInfo& OutReplayInfo, EReadReplayInfoFlags Flags) const;`
- L724 _protected prototype_ `bool ReadReplayInfo(FArchive& Archive, FLocalFileReplayInfo& OutReplayInfo, struct FLocalFileSerializationInfo& SerializationInfo, EReadReplayInfoFlags Flags) const;`
- L726 _protected prototype_ `bool WriteReplayInfo(FArchive& Archive, const FLocalFileReplayInfo& ReplayInfo);`
- L727 _protected prototype_ `bool WriteReplayInfo(FArchive& Archive, const FLocalFileReplayInfo& InReplayInfo, struct FLocalFileSerializationInfo& SerializationInfo);`
- L729 _protected prototype_ `void FixupFriendlyNameLength(const FString& UnfixedName, FString& FixedName) const;`
- L731 _protected prototype_ `bool IsNamedStreamLive(const FString& StreamName) const;`
- L733 _protected prototype_ `void FlushStream(const uint32 TimeInMS);`
- L735 _protected prototype_ `void WriteHeader();`
- L737 _protected prototype_ `virtual TSharedPtr<FArchive> CreateLocalFileReader(const FString& InFilename) const;`
- L738 _protected prototype_ `virtual TSharedPtr<FArchive> CreateLocalFileWriter(const FString& InFilename) const;`
- L739 _protected prototype_ `virtual TSharedPtr<FArchive> CreateLocalFileWriterForOverwrite(const FString& InFilename) const;`
- L741 _protected prototype_ `FString GetDemoPath() const;`
- L743 _protected function_ `virtual TArrayView<const FString> GetAdditionalRelativeDemoPaths() const` — Must be relative to the base demo path
- L744 _protected prototype_ `FString GetDemoFullFilename(const FString& FileName) const;`
- L749 _protected prototype_ `FString GetAutomaticDemoName() const;` — Returns a name formatted as "demoX", where X is between 1 and MAX_DEMOS, inclusive. Returns the first value that doesn't yet exist, or if they all exist, returns the oldest one (it will be overwritten).
- L751 _protected prototype_ `FString GetLocalPlayerUniqueNetId() const;`
- L754 _protected member_ `FLocalFileStreamFArchive HeaderAr;` — Handle to the archive that will read/write the demo header
- L757 _protected member_ `FLocalFileStreamFArchive StreamAr;` — Handle to the archive that will read/write network packets
- L760 _protected member_ `FLocalFileStreamFArchive CheckpointAr;` — Handle to the archive that will read/write checkpoint files
- L763 _protected member_ `EReplayStreamerState StreamerState;` — Overall state of the streamer
- L766 _protected member_ `FString CurrentStreamName;` — Remember the name of the current stream, if any.
- L768 _protected member_ `FString DemoSavePath;`
- L770 _protected prototype_ `void AddRequestToCache(int32 ChunkIndex, const TArray<uint8>& RequestData);`
- L771 _protected prototype_ `void AddRequestToCache(int32 ChunkIndex, TArray<uint8>&& RequestData);`
- L772 _protected prototype_ `void CleanupRequestCache();`
- L774 _protected member_ `bool bCacheFileReadsInMemory;`
- L775 _protected member_ `mutable TMap<FString, TArray<uint8>> FileContentsCache;`
- L776 _protected prototype_ `const TArray<uint8>& GetCachedFileContents(const FString& Filename) const;`
- L778 _protected prototype_ `void UpdateCurrentReplayInfo(FLocalFileReplayInfo& ReplayInfo, EUpdateReplayInfoFlags UpdateFlags = EUpdateReplayInfoFlags::None);`
- L780 _protected prototype_ `virtual int32 GetDecompressedSizeBackCompat(FArchive& InCompressed) const;`
- L783 _public prototype_ `static const FString& GetDefaultDemoSavePath();`
- L784 _public prototype_ `static FString GetDemoFullFilename(const FString& DemoPath, const FString& FileName);`
- L785 _public prototype_ `static bool CleanUpOldReplays(const FString& DemoPath = GetDefaultDemoSavePath(), TArrayView<const FString> AdditionalRelativeDemoPaths = {});`
- L786 _public prototype_ `static bool GetDemoFreeStorageSpace(uint64& DiskFreeSpace, const FString& DemoPath);`
- L788 _public member_ `static const uint32 FileMagic;`
- L789 _public member_ `static const uint32 MaxFriendlyNameLen;`
- L792 _public member_ `static const uint32 LatestVersion;` — `UE_DEPRECATED(5.2, "No longer used, replaced with custom version.")`
- L796 _private member_ `FLocalFileReplayInfo TaskReplayInfo;` — Manipulated by queued replay tasks, likely from another thread

#### struct `FLocalFileNetworkReplayStreamer::FLocalFileSerializationInfo`  
`struct FLocalFileSerializationInfo`  
_L704-715_
- L706 _public prototype_ `FLocalFileSerializationInfo();`
- L708 _public prototype_ `FLocalFileReplayCustomVersion::Type GetLocalFileReplayVersion() const;`
- L711 _public member_ `uint32 FileVersion;` — `UE_DEPRECATED(5.2, "Replaced by FileCustomVersions.")`
- L713 _public member_ `FString FileFriendlyName;`
- L714 _public member_ `FCustomVersionContainer FileCustomVersions;`

#### class `FLocalFileNetworkReplayStreamingFactory`  
`class FLocalFileNetworkReplayStreamingFactory : public INetworkReplayStreamingFactory, public FTickableGameObject`  
_L799-818_
- inherits: `INetworkReplayStreamingFactory,FTickableGameObject`
- L802 _public prototype_ `virtual void StartupModule() override;`
- L803 _public prototype_ `virtual void ShutdownModule() override;`
- L805 _public prototype_ `virtual TSharedPtr<INetworkReplayStreamer> CreateReplayStreamer() override;`
- L806 _public prototype_ `virtual void Flush() override;`
- L809 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableGameObject
- L810 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L811 _public prototype_ `virtual TStatId GetStatId() const override;`
- L812 _public function_ `bool IsTickableWhenPaused() const override`
- L815 _protected prototype_ `bool HasAnyPendingRequests() const;`
- L817 _protected member_ `TArray<TSharedPtr<FLocalFileNetworkReplayStreamer>> LocalFileStreamers;`

#### Free symbols / members of external scopes

- L62 _prototype_ `ENUM_CLASS_FLAGS(EReadReplayInfoFlags);`
- L70 _prototype_ `ENUM_CLASS_FLAGS(EUpdateReplayInfoFlags);`
- L212 _namespace_ `namespace EQueuedLocalFileRequestType`
- L238 _function_ `inline const TCHAR* ToString( EQueuedLocalFileRequestType::Type Type )` (scope `EQueuedLocalFileRequestType`)
- L305 _prototype_ `DECLARE_NETRESULT_ENUM(ELocalFileReplayResult);`
- L307 _prototype_ `const TCHAR* LexToString(ELocalFileReplayResult Enum);`
- L426 _function_ `` (scope `TGenericQueuedLocalFileRequest::IssueRequest`)
- L434 _function_ `` (scope `TGenericQueuedLocalFileRequest::IssueRequest::__anond3c772840202`)
- L505 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLocalFileReplayFinishedWriting, const FString& , const FString& );`
- L505 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLocalFileReplayFinishedWriting, const FString& , const FString& );`
- L628 _function_ `` (scope `FLocalFileNetworkReplayStreamer::AddDelegateFileRequestToQueue`)
