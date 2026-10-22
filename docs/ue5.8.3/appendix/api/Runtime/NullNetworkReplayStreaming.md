# Runtime / NullNetworkReplayStreaming

- module root: `Source/Runtime/NetworkReplayStreaming/NullNetworkReplayStreaming`
- headers: 1; symbols: 76
- symbol kinds: class=3, function=18, member=14, prototype=41
- PrivateDependencyModuleNames: Core, Engine, Json, NetworkReplayStreaming

### `Source/Runtime/NetworkReplayStreaming/NullNetworkReplayStreaming/Public/NullNetworkReplayStreaming.h` (Public)


#### class `FNullReplayInfo`  
`class FNullReplayInfo : public FJsonSerializable`  
_L14-34_
- inherits: `FJsonSerializable`
- desc: Class to hold metadata about an entire replay
- L17 _public function_ `FNullReplayInfo() : LengthInMS(0), NetworkVersion(0), Changelist(0), DemoFileLastOffset(0), bIsValid(false)`
- L19 _public member_ `int32 LengthInMS;`
- L20 _public member_ `uint32 NetworkVersion;`
- L21 _public member_ `uint32 Changelist;`
- L22 _public member_ `FString FriendlyName;`
- L23 _public member_ `int32 DemoFileLastOffset;`
- L24 _public member_ `bool bIsValid;`

#### class `FNullNetworkReplayStreamer`  
`class FNullNetworkReplayStreamer : public INetworkReplayStreamer, public FTickableGameObject`  
_L37-153_
- inherits: `INetworkReplayStreamer,FTickableGameObject`
- desc: Default streamer that goes straight to the HD
- L40 _public function_ `FNullNetworkReplayStreamer() : StreamerState(EReplayStreamerState::Idle), CurrentCheckpointIndex( 0 ), LastKnownFileSize( 0 )`
- L47 _public prototype_ `virtual void StartStreaming(const FStartStreamingParameters& Params, const FStartStreamingCallback& Delegate) override;` — INetworkReplayStreamer implementation
- L48 _public prototype_ `virtual void StopStreaming() override;`
- L49 _public prototype_ `virtual FArchive* GetHeaderArchive() override;`
- L50 _public prototype_ `virtual FArchive* GetStreamingArchive() override;`
- L51 _public prototype_ `virtual FArchive* GetCheckpointArchive() override;`
- L52 _public prototype_ `virtual void FlushCheckpoint( const uint32 TimeInMS ) override;`
- L53 _public prototype_ `virtual void GotoCheckpointIndex( const int32 CheckpointIndex, const FGotoCallback& Delegate, EReplayCheckpointType CheckpointType ) override;`
- L54 _public prototype_ `virtual void GotoTimeInMS( const uint32 TimeInMS, const FGotoCallback& Delegate, EReplayCheckpointType CheckpointType ) override;`
- L55 _public prototype_ `virtual void UpdateTotalDemoTime( uint32 TimeInMS ) override;`
- L56 _public function_ `virtual void UpdatePlaybackTime(uint32 TimeInMS) override`
- L57 _public function_ `virtual uint32 GetTotalDemoTime() const override`
- L58 _public prototype_ `virtual bool IsDataAvailable() const override;`
- L59 _public function_ `virtual void SetHighPriorityTimeRange( const uint32 StartTimeInMS, const uint32 EndTimeInMS ) override`
- L60 _public function_ `virtual bool IsDataAvailableForTimeRange( const uint32 StartTimeInMS, const uint32 EndTimeInMS ) override`
- L61 _public function_ `virtual bool IsLoadingCheckpoint() const override`
- L62 _public prototype_ `virtual bool IsLive() const override;`
- L63 _public prototype_ `virtual void DeleteFinishedStream( const FString& StreamName, const FDeleteFinishedStreamCallback& Delegate) override;`
- L64 _public prototype_ `virtual void DeleteFinishedStream( const FString& StreamName, const int32 UserIndex, const FDeleteFinishedStreamCallback& Delegate ) override;`
- L65 _public prototype_ `virtual void EnumerateStreams( const FNetworkReplayVersion& InReplayVersion, const int32 UserIndex, const FString& MetaString, const TArray< FString >& ExtraParms, const FEnumerateStreamsCallback& Delegate ) override;`
- L66 _public prototype_ `virtual void EnumerateRecentStreams( const FNetworkReplayVersion& ReplayVersion, const int32 UserIndex, const FEnumerateStreamsCallback& Delegate ) override;`
- L67 _public prototype_ `virtual void AddUserToReplay(const FString& UserString) override;`
- L68 _public prototype_ `virtual void AddEvent(const uint32 TimeInMS, const FString& Group, const FString& Meta, const TArray<uint8>& Data) override;`
- L69 _public function_ `virtual void AddOrUpdateEvent( const FString& Name, const uint32 TimeInMS, const FString& Group, const FString& Meta, const TArray<uint8>& Data ) override`
- L71 _public prototype_ `virtual void EnumerateEvents( const FString& Group, const FEnumerateEventsCallback& EnumerationCompleteDelegate ) override;`
- L72 _public prototype_ `virtual void EnumerateEvents( const FString& ReplayName, const FString& Group, const FEnumerateEventsCallback& EnumerationCompleteDelegate ) override;`
- L73 _public prototype_ `virtual void EnumerateEvents( const FString& ReplayName, const FString& Group, const int32 UserIndex, const FEnumerateEventsCallback& Delegate ) override;`
- L75 _public prototype_ `virtual void RequestEventData(const FString& EventID, const FRequestEventDataCallback& Delegate) override;`
- L76 _public prototype_ `virtual void RequestEventData(const FString& ReplayName, const FString& EventID, const FRequestEventDataCallback& Delegate) override;`
- L77 _public prototype_ `virtual void RequestEventData(const FString& ReplayName, const FString& EventId, const int32 UserIndex, const FRequestEventDataCallback& Delegate) override;`
- L78 _public prototype_ `virtual void RequestEventGroupData(const FString& Group, const FRequestEventGroupDataCallback& Delegate) override;`
- L79 _public prototype_ `virtual void RequestEventGroupData(const FString& ReplayName, const FString& Group, const FRequestEventGroupDataCallback& Delegate) override;`
- L80 _public prototype_ `virtual void RequestEventGroupData(const FString& ReplayName, const FString& Group, const int32 UserIndex, const FRequestEventGroupDataCallback& Delegate) override;`
- L81 _public prototype_ `virtual void SearchEvents(const FString& EventGroup, const FSearchEventsCallback& Delegate) override;`
- L82 _public prototype_ `virtual void KeepReplay(const FString& ReplayName, const bool bKeep, const FKeepReplayCallback& Delegate) override;`
- L83 _public prototype_ `virtual void KeepReplay(const FString& ReplayName, const bool bKeep, const int32 UserIndex, const FKeepReplayCallback& Delegate) override;`
- L84 _public prototype_ `virtual void RenameReplayFriendlyName(const FString& ReplayName, const FString& NewFriendlyName, const FRenameReplayCallback& Delegate) override;`
- L85 _public prototype_ `virtual void RenameReplayFriendlyName(const FString& ReplayName, const FString& NewFriendlyName, const int32 UserIndex, const FRenameReplayCallback& Delegate) override;`
- L86 _public prototype_ `virtual void RenameReplay(const FString& ReplayName, const FString& NewName, const FRenameReplayCallback& Delegate) override;`
- L87 _public prototype_ `virtual void RenameReplay(const FString& ReplayName, const FString& NewName, const int32 UserIndex, const FRenameReplayCallback& Delegate) override;`
- L88 _public function_ `virtual FString GetReplayID() const override`
- L89 _public function_ `virtual EReplayStreamerState GetReplayStreamerState() const override`
- L90 _public function_ `virtual void SetTimeBufferHintSeconds(const float InTimeBufferHintSeconds) override`
- L91 _public function_ `virtual void RefreshHeader() override`
- L92 _public function_ `virtual void DownloadHeader(const FDownloadHeaderCallback& Delegate) override`
- L100 _public prototype_ `virtual void Tick(float DeltaSeconds) override;` — FTickableObjectBase implementation
- L101 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L102 _public prototype_ `virtual TStatId GetStatId() const override;`
- L105 _public function_ `virtual bool IsTickableWhenPaused() const override` — FTickableGameObject implementation
- L107 _public function_ `virtual uint32 GetMaxFriendlyNameSize() const override`
- L109 _public function_ `virtual EStreamingOperationResult SetDemoPath(const FString& DemoPath) override`
- L114 _public prototype_ `virtual EStreamingOperationResult GetDemoPath(FString& DemoPath) const override;`
- L116 _public function_ `virtual bool IsCheckpointTypeSupported(EReplayCheckpointType CheckpointType) const override`
- L119 _private prototype_ `bool IsNamedStreamLive( const FString& StreamName ) const;`
- L122 _private prototype_ `void GotoCheckpointIndexInternal(int32 CheckpointIndex, const FGotoCallback& Delegate, int32 TimeInMS);` — Handles the details of loading a checkpoint
- L125 _private prototype_ `void ReopenStreamFileForReading();` — Reopen the file to refresh it's size, since file-based FArchives do not appear to update their size if they're being written to.
- L128 _private prototype_ `void UpdateReplayInfoIfValid();` — Overwrites the cached ReplayInfo only if the read succeeded
- L131 _private member_ `TUniquePtr<FArchive> HeaderAr;` — Handle to the archive that will read/write the demo header
- L134 _private member_ `TUniquePtr<FArchive> FileAr;` — Handle to the archive that will read/write network packets
- L137 _private member_ `TUniquePtr<FArchive> CheckpointAr;` — Handle to the archive that will read/write checkpoint files
- L140 _private member_ `EReplayStreamerState StreamerState;` — Overall state of the streamer
- L143 _private member_ `FString CurrentStreamName;` — Remember the name of the current stream, if any.
- L146 _private member_ `int32 CurrentCheckpointIndex;` — Current number of checkpoints written.
- L149 _private member_ `FNullReplayInfo ReplayInfo;` — Currently playing or recording replay metadata
- L152 _private member_ `int64 LastKnownFileSize;` — Last known size of the replay stream file.

#### class `FNullNetworkReplayStreamingFactory`  
`class FNullNetworkReplayStreamingFactory : public INetworkReplayStreamingFactory`  
_L155-159_
- inherits: `INetworkReplayStreamingFactory`
- L158 _public prototype_ `virtual TSharedPtr< INetworkReplayStreamer > CreateReplayStreamer();`
