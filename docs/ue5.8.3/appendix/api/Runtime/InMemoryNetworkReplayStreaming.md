# Runtime / InMemoryNetworkReplayStreaming

- module root: `Source/Runtime/NetworkReplayStreaming/InMemoryNetworkReplayStreaming`
- headers: 1; symbols: 101
- symbol kinds: class=3, function=23, member=23, prototype=49, struct=3
- PrivateDependencyModuleNames: Core, Json, NetworkReplayStreaming
- PublicDependencyModuleNames: Engine
- PublicIncludePathModuleNames: Engine

### `Source/Runtime/NetworkReplayStreaming/InMemoryNetworkReplayStreaming/Public/InMemoryNetworkReplayStreaming.h` (Public)


#### struct `FInMemoryReplay`  
`struct FInMemoryReplay`  
_L19-85_
- desc: Holds all data about an entire replay
- L49 _public function_ `FInMemoryReplay() : NetworkVersion(0)`
- L56 _public member_ `TArray<uint8> Header;`
- L57 _public member_ `TArray<FStreamChunk> StreamChunks;`
- L58 _public member_ `TArray<uint8> Metadata;`
- L59 _public member_ `TArray<FCheckpoint> Checkpoints;`
- L60 _public member_ `FNetworkReplayStreamInfo StreamInfo;`
- L61 _public member_ `uint32 NetworkVersion;`
- L63 _public function_ `int64 TotalStreamSize() const`

#### struct `FInMemoryReplay::FCheckpoint`  
`struct FCheckpoint`  
_L21-37_
- L23 _public function_ `FCheckpoint() : TimeInMS(0), StreamByteOffset(0)`
- L27 _public member_ `TArray<uint8> Data;`
- L28 _public member_ `uint32 TimeInMS;`
- L29 _public member_ `uint32 StreamByteOffset;`
- L31 _public function_ `void Reset()`

#### struct `FInMemoryReplay::FStreamChunk`  
`struct FStreamChunk`  
_L40-47_
- desc: Represents a chunk of replay stream data between two checkpoints.
- L42 _public function_ `FStreamChunk() : StartIndex(0), TimeInMS(0)`
- L44 _public member_ `int32 StartIndex;`
- L45 _public member_ `uint32 TimeInMS;`
- L46 _public member_ `TArray<uint8> Data;`

#### class `FInMemoryReplayStreamArchive`  
`class FInMemoryReplayStreamArchive : public FArchive`  
_L92-111_
- inherits: `FArchive`
- desc: An archive that handles the in-memory replay stream being divided into multiple chunks, and earlier chunks being dropped when FInMemoryNetworkReplayStreamer::NumCheckpointsToKeep is set. Assumes that that a single Serialize() call will not need to span multiple chunks!
- L95 _public function_ `FInMemoryReplayStreamArchive(TArray<FInMemoryReplay::FStreamChunk>& InChunks) : Pos(0) , Chunks(InChunks)`
- L100 _public prototype_ `virtual void Serialize(void* V, int64 Length);`
- L101 _public prototype_ `virtual int64 Tell();`
- L102 _public prototype_ `virtual int64 TotalSize();`
- L103 _public prototype_ `virtual void Seek(int64 InPos);`
- L104 _public prototype_ `virtual bool AtEnd();`
- L107 _private prototype_ `FInMemoryReplay::FStreamChunk* GetCurrentChunk() const;`
- L109 _private member_ `int64 Pos;`
- L110 _private member_ `TArray<FInMemoryReplay::FStreamChunk>& Chunks;`

#### class `FInMemoryNetworkReplayStreamer`  
`class FInMemoryNetworkReplayStreamer : public INetworkReplayStreamer, public FTickableGameObject`  
_L114-256_
- inherits: `INetworkReplayStreamer,FTickableGameObject`
- desc: Streamer that keeps all data in memory only
- L117 _public function_ `FInMemoryNetworkReplayStreamer(FInMemoryNetworkReplayStreamingFactory* InFactory) : OwningFactory(InFactory), StreamerState(EReplayStreamerState::Idle), TimeBufferHintSeconds(-1.0f)`
- L126 _public prototype_ `virtual void StartStreaming(const FStartStreamingParameters& Params, const FStartStreamingCallback& Delegate) override;` — INetworkReplayStreamer implementation
- L127 _public prototype_ `virtual void StopStreaming() override;`
- L128 _public prototype_ `virtual FArchive* GetHeaderArchive() override;`
- L129 _public prototype_ `virtual FArchive* GetStreamingArchive() override;`
- L130 _public prototype_ `virtual FArchive* GetCheckpointArchive() override;`
- L131 _public prototype_ `virtual void FlushCheckpoint( const uint32 TimeInMS ) override;`
- L132 _public prototype_ `virtual void GotoCheckpointIndex( const int32 CheckpointIndex, const FGotoCallback& Delegate, EReplayCheckpointType CheckpointType ) override;`
- L133 _public prototype_ `virtual void GotoTimeInMS( const uint32 TimeInMS, const FGotoCallback& Delegate, EReplayCheckpointType CheckpointType ) override;`
- L134 _public prototype_ `virtual void UpdateTotalDemoTime( uint32 TimeInMS ) override;`
- L135 _public function_ `virtual void UpdatePlaybackTime(uint32 TimeInMS) override`
- L136 _public prototype_ `virtual uint32 GetTotalDemoTime() const override;`
- L137 _public prototype_ `virtual bool IsDataAvailable() const override;`
- L138 _public function_ `virtual void SetHighPriorityTimeRange( const uint32 StartTimeInMS, const uint32 EndTimeInMS ) override`
- L139 _public function_ `virtual bool IsDataAvailableForTimeRange( const uint32 StartTimeInMS, const uint32 EndTimeInMS ) override`
- L140 _public function_ `virtual bool IsLoadingCheckpoint() const override`
- L141 _public prototype_ `virtual bool IsLive() const override;`
- L142 _public prototype_ `virtual void DeleteFinishedStream( const FString& StreamName, const FDeleteFinishedStreamCallback& Delegate) override;`
- L143 _public prototype_ `virtual void DeleteFinishedStream( const FString& StreamName, const int32 UserIndex, const FDeleteFinishedStreamCallback& Delegate ) override;`
- L144 _public prototype_ `virtual void EnumerateStreams( const FNetworkReplayVersion& ReplayVersion, const int32 UserIndex, const FString& MetaString, const TArray< FString >& ExtraParms, const FEnumerateStreamsCallback& Delegate ) override;`
- L145 _public prototype_ `virtual void EnumerateRecentStreams( const FNetworkReplayVersion& ReplayVersion, const int32 UserIndex, const FEnumerateStreamsCallback& Delegate ) override;`
- L146 _public prototype_ `virtual void AddUserToReplay(const FString& UserString) override;`
- L147 _public prototype_ `virtual void AddEvent(const uint32 TimeInMS, const FString& Group, const FString& Meta, const TArray<uint8>& Data) override;`
- L148 _public function_ `virtual void AddOrUpdateEvent( const FString& Name, const uint32 TimeInMS, const FString& Group, const FString& Meta, const TArray<uint8>& Data ) override`
- L149 _public prototype_ `virtual void EnumerateEvents(const FString& Group, const FEnumerateEventsCallback& Delegate) override;`
- L150 _public prototype_ `virtual void EnumerateEvents( const FString& ReplayName, const FString& Group, const FEnumerateEventsCallback& Delegate ) override;`
- L151 _public prototype_ `virtual void EnumerateEvents( const FString& ReplayName, const FString& Group, const int32 UserIndex, const FEnumerateEventsCallback& Delegate ) override;`
- L152 _public prototype_ `virtual void RequestEventData(const FString& EventID, const FRequestEventDataCallback& Delegate) override;`
- L153 _public prototype_ `virtual void RequestEventData(const FString& ReplayName, const FString& EventID, const FRequestEventDataCallback& Delegate) override;`
- L154 _public prototype_ `virtual void RequestEventData(const FString& ReplayName, const FString& EventId, const int32 UserIndex, const FRequestEventDataCallback& Delegate) override;`
- L155 _public prototype_ `virtual void RequestEventGroupData(const FString& Group, const FRequestEventGroupDataCallback& Delegate) override;`
- L156 _public prototype_ `virtual void RequestEventGroupData(const FString& ReplayName, const FString& Group, const FRequestEventGroupDataCallback& Delegate) override;`
- L157 _public prototype_ `virtual void RequestEventGroupData(const FString& ReplayName, const FString& Group, const int32 UserIndex, const FRequestEventGroupDataCallback& Delegate) override;`
- L158 _public prototype_ `virtual void SearchEvents(const FString& EventGroup, const FSearchEventsCallback& Delegate) override;`
- L159 _public prototype_ `virtual void KeepReplay(const FString& ReplayName, const bool bKeep, const int32 UserIndex, const FKeepReplayCallback& Delegate) override;`
- L160 _public prototype_ `virtual void KeepReplay(const FString& ReplayName, const bool bKeep, const FKeepReplayCallback& Delegate) override;`
- L161 _public prototype_ `virtual void RenameReplayFriendlyName(const FString& ReplayName, const FString& NewFriendlyName, const FRenameReplayCallback& Delegate) override;`
- L162 _public prototype_ `virtual void RenameReplayFriendlyName(const FString& ReplayName, const FString& NewFriendlyName, const int32 UserIndex, const FRenameReplayCallback& Delegate) override;`
- L163 _public prototype_ `virtual void RenameReplay(const FString& ReplayName, const FString& NewName, const FRenameReplayCallback& Delegate) override;`
- L164 _public prototype_ `virtual void RenameReplay(const FString& ReplayName, const FString& NewName, const int32 UserIndex, const FRenameReplayCallback& Delegate) override;`
- L165 _public function_ `virtual FString GetReplayID() const override`
- L166 _public function_ `virtual EReplayStreamerState GetReplayStreamerState() const override`
- L167 _public function_ `virtual void SetTimeBufferHintSeconds(const float InTimeBufferHintSeconds) override`
- L168 _public function_ `virtual void RefreshHeader() override`
- L169 _public function_ `virtual void DownloadHeader(const FDownloadHeaderCallback& Delegate) override`
- L176 _public prototype_ `virtual void Tick(float DeltaSeconds) override;` — FTickableObjectBase implementation
- L177 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L178 _public prototype_ `virtual TStatId GetStatId() const override;`
- L181 _public function_ `virtual bool IsTickableWhenPaused() const override` — FTickableGameObject implementation
- L183 _public function_ `virtual uint32 GetMaxFriendlyNameSize() const override`
- L185 _public function_ `virtual EStreamingOperationResult SetDemoPath(const FString& DemoPath) override`
- L190 _public function_ `virtual EStreamingOperationResult GetDemoPath(FString& DemoPath) const override`
- L195 _public function_ `virtual bool IsCheckpointTypeSupported(EReplayCheckpointType CheckpointType) const override`
- L198 _private prototype_ `bool IsNamedStreamLive( const FString& StreamName ) const;`
- L201 _private prototype_ `void GotoCheckpointIndexInternal(int32 CheckpointIndex, const FGotoCallback& Delegate, int32 TimeInMS);` — Handles the details of loading a checkpoint
- L207 _private prototype_ `FInMemoryReplay* GetCurrentReplay();` — Returns a pointer to the currently active (recording or playback) replay in the owning factory's map. May return null if if the streamer state is idle.
- L213 _private prototype_ `FInMemoryReplay* GetCurrentReplay() const;` — Returns a pointer to the currently active (recording or playback) replay in the owning factory's map. May return null if if the streamer state is idle.
- L219 _private prototype_ `FInMemoryReplay* GetCurrentReplayChecked();` — Returns a pointer to the currently active (recording or playback) replay in the owning factory's map. Asserts if the returned replay pointer would be null.
- L225 _private prototype_ `FInMemoryReplay* GetCurrentReplayChecked() const;` — Returns a pointer to the currently active (recording or playback) replay in the owning factory's map. Asserts if the returned replay pointer would be null.
- L228 _private member_ `FInMemoryNetworkReplayStreamingFactory* OwningFactory;` — Pointer to the factory that owns this streamer instance
- L231 _private member_ `TUniquePtr<FArchive> HeaderAr;` — Handle to the archive that will read/write the demo header
- L234 _private member_ `TUniquePtr<FArchive> FileAr;` — Handle to the archive that will read/write network packets
- L237 _private member_ `TUniquePtr<FArchive> CheckpointAr;` — Handle to the archive that will read/write checkpoint files
- L243 _private member_ `FInMemoryReplay::FCheckpoint CheckpointCurrentlyBeingSaved;` — Temporary checkpoint used during recording. Will be moved onto the replay's checkpoint list in FlushCheckpoint to commit it.
- L246 _private member_ `EReplayStreamerState StreamerState;` — Overall state of the streamer
- L249 _private member_ `FString CurrentStreamName;` — Remember the name of the current stream, if any.
- L255 _private member_ `float TimeBufferHintSeconds;` — If greater than zero, checkpoints that wouldn't be needed to rewind farther than this value, and the stream data associated with them, will be freed periodically to help limit memory usage.

#### class `FInMemoryNetworkReplayStreamingFactory`  
`class FInMemoryNetworkReplayStreamingFactory : public INetworkReplayStreamingFactory`  
_L258-267_
- inherits: `INetworkReplayStreamingFactory`
- L261 _public prototype_ `virtual TSharedPtr< INetworkReplayStreamer > CreateReplayStreamer();`
- L266 _private member_ `TMap<FString, TUniquePtr<FInMemoryReplay>> Replays;`
