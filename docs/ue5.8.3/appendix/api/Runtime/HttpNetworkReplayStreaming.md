# Runtime / HttpNetworkReplayStreaming

- module root: `Source/Runtime/NetworkReplayStreaming/HttpNetworkReplayStreaming`
- headers: 1; symbols: 222
- symbol kinds: class=8, enum=2, enumerator=27, function=20, macro=1, member=49, namespace=1, prototype=113, typedef=1
- PrivateDependencyModuleNames: Core, CoreOnline, CoreUObject, Engine, HTTP, Json, NetworkReplayStreaming

### `Source/Runtime/NetworkReplayStreaming/HttpNetworkReplayStreaming/Public/HttpNetworkReplayStreaming.h` (Public)


#### class `FHttpStreamFArchive`  
`class FHttpStreamFArchive : public FArchive`  
_L18-32_
- inherits: `FArchive`
- desc: Archive used to buffer stream over http
- L21 _public function_ `FHttpStreamFArchive() : Pos( 0 ), bAtEndOfReplay( false )`
- L23 _public prototype_ `virtual void Serialize( void* V, int64 Length );`
- L24 _public prototype_ `virtual int64 Tell();`
- L25 _public prototype_ `virtual int64 TotalSize();`
- L26 _public prototype_ `virtual void Seek( int64 InPos );`
- L27 _public prototype_ `virtual bool AtEnd();`
- L29 _public member_ `TArray< uint8 > Buffer;`
- L30 _public member_ `int32 Pos;`
- L31 _public member_ `bool bAtEndOfReplay;`

#### enum `EQueuedHttpRequestType::Type`  
`enum Type`  
_L36-57_
- L38 _public enumerator_ `StartUploading` — We have made a request to start uploading a replay
- L39 _public enumerator_ `UploadingHeader` — We are uploading the replay header
- L40 _public enumerator_ `UploadingStream` — We are in the process of uploading the replay stream
- L41 _public enumerator_ `StopUploading` — We have made the request to stop uploading a live replay stream
- L42 _public enumerator_ `StartDownloading` — We have made the request to start downloading a replay stream
- L43 _public enumerator_ `DownloadingHeader` — We are downloading the replay header
- L44 _public enumerator_ `DownloadingStream` — We are in the process of downloading the replay stream
- L45 _public enumerator_ `RefreshingViewer` — We are refreshing the server to let it know we're still viewing
- L46 _public enumerator_ `EnumeratingSessions` — We are in the process of downloading the available sessions
- L47 _public enumerator_ `EnumeratingCheckpoints` — We are in the process of downloading the available checkpoints
- L48 _public enumerator_ `UploadingCheckpoint` — We are uploading a checkpoint
- L49 _public enumerator_ `DownloadingCheckpoint` — We are downloading a checkpoint
- L50 _public enumerator_ `AddingUser` — We are adding a user who joined in progress during recording
- L51 _public enumerator_ `UploadingCustomEvent` — We are uploading a custom event
- L52 _public enumerator_ `EnumeratingCustomEvent` — We are in the process of enumerating a custom event set
- L53 _public enumerator_ `RequestEventData` — We are in the process of requesting the data for a specific event
- L54 _public enumerator_ `UploadHeader` — Request to upload header (has to be done after we get info from server)
- L55 _public enumerator_ `StopStreaming` — Request to stop streaming
- L56 _public enumerator_ `KeepReplay` — Request to keep replay (or cancel keeping replay)

#### class `FQueuedHttpRequest`  
`class FQueuedHttpRequest`  
_L109-134_
- L112 _public function_ `FQueuedHttpRequest( const EQueuedHttpRequestType::Type InType, TSharedPtr< class IHttpRequest, ESPMode::ThreadSafe > InRequest ) : Type( InType ), Request( InRequest ), RetryProgress( 0 ), MaxRetries( 0 ), RetryDelay( 0.0f ), NextRetryTime( 0.0 )`
- L116 _public function_ `FQueuedHttpRequest( const EQueuedHttpRequestType::Type InType, TSharedPtr< class IHttpRequest, ESPMode::ThreadSafe > InRequest, const int32 InMaxRetries, const float InRetryDelay ) : Type( InType ), Request( InRequest ), RetryProgress( 0 ), MaxRetries( InMaxRetries ), RetryDelay( InRetryDelay ), NextRetryTime( 0.0 )`
- L120 _public prototype_ `virtual ~FQueuedHttpRequest() = default;`
- L122 _public member_ `EQueuedHttpRequestType::Type Type;`
- L123 _public member_ `TSharedPtr< class IHttpRequest, ESPMode::ThreadSafe > Request;`
- L125 _public member_ `int32 RetryProgress;`
- L126 _public member_ `int32 MaxRetries;`
- L127 _public member_ `float RetryDelay;`
- L128 _public member_ `double NextRetryTime;`
- L130 _public function_ `virtual bool PreProcess( FHttpNetworkReplayStreamer* Streamer, const FString& ServerURL, const FString& SessionName )`

#### class `FQueuedHttpRequestAddEvent`  
`class FQueuedHttpRequestAddEvent : public FQueuedHttpRequest`  
_L140-153_
- inherits: `FQueuedHttpRequest`
- desc: FQueuedHttpRequestAddEvent Custom event so that we can defer the need to knowing SessionName until we actually send it (which we should have it by then, since requests are executed in order)
- L143 _public prototype_ `FQueuedHttpRequestAddEvent( const FString& InName, const uint32 InTimeInMS, const FString& InGroup, const FString& InMeta, const TArray<uint8>& InData, TSharedRef<class IHttpRequest, ESPMode::ThreadSafe> InHttpRequest );`
- L145 _public prototype_ `virtual ~FQueuedHttpRequestAddEvent() = default;`
- L147 _public prototype_ `virtual bool PreProcess( FHttpNetworkReplayStreamer* Streamer, const FString& ServerURL, const FString& SessionName ) override;`
- L149 _public member_ `FString Name;`
- L150 _public member_ `uint32 TimeInMS;`
- L151 _public member_ `FString Group;`
- L152 _public member_ `FString Meta;`

#### class `FQueuedHttpRequestAddUser`  
`class FQueuedHttpRequestAddUser : public FQueuedHttpRequest`  
_L159-167_
- inherits: `FQueuedHttpRequest`
- desc: FQueuedHttpRequestAddUser Custom event so that we can defer the need to knowing SessionName until we actually send it (which we should have it by then, since requests are executed in order)
- L162 _public prototype_ `FQueuedHttpRequestAddUser( const FString& InUser, TSharedRef<class IHttpRequest, ESPMode::ThreadSafe> InHttpRequest );`
- L164 _public prototype_ `virtual ~FQueuedHttpRequestAddUser() = default;`
- L166 _public prototype_ `virtual bool PreProcess( FHttpNetworkReplayStreamer* Streamer, const FString& ServerURL, const FString& SessionName ) override;`

#### class `FQueuedGotoFakeCheckpoint`  
`class FQueuedGotoFakeCheckpoint : public FQueuedHttpRequest`  
_L172-180_
- inherits: `FQueuedHttpRequest`
- desc: FQueuedGotoFakeCheckpoint
- L175 _public prototype_ `FQueuedGotoFakeCheckpoint();`
- L177 _public prototype_ `virtual ~FQueuedGotoFakeCheckpoint() = default;`
- L179 _public prototype_ `virtual bool PreProcess( FHttpNetworkReplayStreamer* Streamer, const FString& ServerURL, const FString& SessionName ) override;`

#### class `FCachedResponse`  
`class FCachedResponse`  
_L182-191_
- L185 _public function_ `FCachedResponse( FHttpResponsePtr InResponse, const double InLastAccessTime ) : Response( InResponse ), LastAccessTime( InLastAccessTime )`
- L189 _public member_ `FHttpResponsePtr Response;`
- L190 _public member_ `double LastAccessTime;`

#### enum `EHttpReplayResult`  
`enum class EHttpReplayResult : uint32`  
_L196-206_
- reflection: `UENUM()`
- L198 _public enumerator_ `Success`
- L199 _public enumerator_ `FailedJsonParse`
- L200 _public enumerator_ `DataUnavailable`
- L201 _public enumerator_ `InvalidHttpResponse`
- L202 _public enumerator_ `CompressionFailed`
- L203 _public enumerator_ `DecompressionFailed`
- L204 _public enumerator_ `InvalidPayload`
- L205 _public enumerator_ `Unknown`

#### class `FHttpNetworkReplayStreamer`  
`class FHttpNetworkReplayStreamer : public INetworkReplayStreamer`  
_L215-390_
- inherits: `INetworkReplayStreamer`
- desc: Http network replay streaming manager
- L217 _private typedef_ `using FHttpReplayResult = UE::Net::TNetResult<EHttpReplayResult>;`
- L220 _public prototype_ `FHttpNetworkReplayStreamer();`
- L223 _public prototype_ `virtual void StartStreaming(const FStartStreamingParameters& Params, const FStartStreamingCallback& Delegate) override;` — INetworkReplayStreamer implementation
- L224 _public prototype_ `virtual void StopStreaming() override;`
- L225 _public prototype_ `virtual FArchive* GetHeaderArchive() override;`
- L226 _public prototype_ `virtual FArchive* GetStreamingArchive() override;`
- L227 _public prototype_ `virtual FArchive* GetCheckpointArchive() override;`
- L228 _public prototype_ `virtual void FlushCheckpoint( const uint32 TimeInMS ) override;`
- L229 _public prototype_ `virtual void GotoCheckpointIndex( const int32 CheckpointIndex, const FGotoCallback& Delegate, EReplayCheckpointType CheckpointType ) override;`
- L230 _public prototype_ `virtual void GotoTimeInMS( const uint32 TimeInMS, const FGotoCallback& Delegate, EReplayCheckpointType CheckpointType ) override;`
- L231 _public prototype_ `virtual void UpdateTotalDemoTime( uint32 TimeInMS ) override;`
- L232 _public function_ `virtual void UpdatePlaybackTime(uint32 TimeInMS) override`
- L233 _public function_ `virtual uint32 GetTotalDemoTime() const override`
- L234 _public prototype_ `virtual bool IsDataAvailable() const override;`
- L235 _public prototype_ `virtual void SetHighPriorityTimeRange( const uint32 StartTimeInMS, const uint32 EndTimeInMS ) override;`
- L236 _public prototype_ `virtual bool IsDataAvailableForTimeRange( const uint32 StartTimeInMS, const uint32 EndTimeInMS ) override;`
- L237 _public prototype_ `virtual bool IsLoadingCheckpoint() const override;`
- L238 _public prototype_ `virtual bool IsLive() const override;`
- L239 _public prototype_ `virtual void DeleteFinishedStream( const FString& StreamName, const FDeleteFinishedStreamCallback& Delegate ) override;`
- L240 _public prototype_ `virtual void DeleteFinishedStream( const FString& StreamName, const int32 UserIndex, const FDeleteFinishedStreamCallback& Delegate ) override;`
- L241 _public prototype_ `virtual void EnumerateStreams( const FNetworkReplayVersion& InReplayVersion, const int32 UserIndex, const FString& MetaString, const TArray< FString >& ExtraParms, const FEnumerateStreamsCallback& Delegate ) override;`
- L242 _public prototype_ `virtual void EnumerateEvents( const FString& Group, const FEnumerateEventsCallback& Delegate ) override;`
- L243 _public prototype_ `virtual void EnumerateEvents( const FString& ReplayName, const FString& Group, const FEnumerateEventsCallback& Delegate ) override;`
- L244 _public prototype_ `virtual void EnumerateEvents( const FString& ReplayName, const FString& Group, const int32 UserIndex, const FEnumerateEventsCallback& Delegate ) override;`
- L245 _public prototype_ `virtual void EnumerateRecentStreams( const FNetworkReplayVersion& ReplayVersion, const int32 UserIndex, const FEnumerateStreamsCallback& Delegate ) override;`
- L246 _public prototype_ `virtual void AddUserToReplay(const FString& UserString) override;`
- L247 _public prototype_ `virtual void RequestEventData(const FString& EventId, const FRequestEventDataCallback& Delegate) override;`
- L248 _public prototype_ `virtual void RequestEventData(const FString& ReplayName, const FString& EventId, const FRequestEventDataCallback& Delegate) override;`
- L249 _public prototype_ `virtual void RequestEventData(const FString& ReplayName, const FString& EventId, const int32 UserIndex, const FRequestEventDataCallback& Delegate) override;`
- L250 _public prototype_ `virtual void RequestEventGroupData(const FString& Group, const FRequestEventGroupDataCallback& Delegate) override;`
- L251 _public prototype_ `virtual void RequestEventGroupData(const FString& ReplayName, const FString& Group, const FRequestEventGroupDataCallback& Delegate) override;`
- L252 _public prototype_ `virtual void RequestEventGroupData(const FString& ReplayName, const FString& Group, const int32 UserIndex, const FRequestEventGroupDataCallback& Delegate) override;`
- L253 _public prototype_ `virtual void SearchEvents(const FString& EventGroup, const FSearchEventsCallback& Delegate) override;`
- L254 _public prototype_ `virtual void KeepReplay(const FString& ReplayName, const bool bKeep, const FKeepReplayCallback& Delegate) override;`
- L255 _public prototype_ `virtual void KeepReplay(const FString& ReplayName, const bool bKeep, const int32 UserIndex, const FKeepReplayCallback& Delegate) override;`
- L256 _public prototype_ `virtual void RenameReplayFriendlyName(const FString& ReplayName, const FString& NewFriendlyName, const FRenameReplayCallback& Delegate) override;`
- L257 _public prototype_ `virtual void RenameReplayFriendlyName(const FString& ReplayName, const FString& NewFriendlyName, const int32 UserIndex, const FRenameReplayCallback& Delegate) override;`
- L258 _public prototype_ `virtual void RenameReplay(const FString& ReplayName, const FString& NewName, const FRenameReplayCallback& Delegate) override;`
- L259 _public prototype_ `virtual void RenameReplay(const FString& ReplayName, const FString& NewName, const int32 UserIndex, const FRenameReplayCallback& Delegate) override;`
- L261 _public function_ `virtual FString GetReplayID() const override`
- L262 _public function_ `virtual EReplayStreamerState GetReplayStreamerState() const override`
- L263 _public function_ `virtual void SetTimeBufferHintSeconds(const float InTimeBufferHintSeconds) override`
- L264 _public prototype_ `virtual void RefreshHeader() override;`
- L265 _public prototype_ `virtual void DownloadHeader(const FDownloadHeaderCallback& Delegate);`
- L266 _public function_ `virtual uint32 GetMaxFriendlyNameSize() const override`
- L268 _public function_ `virtual EStreamingOperationResult SetDemoPath(const FString& DemoPath) override`
- L273 _public function_ `virtual EStreamingOperationResult GetDemoPath(FString& DemoPath) const override`
- L278 _public prototype_ `virtual bool IsCheckpointTypeSupported(EReplayCheckpointType CheckpointType) const override;`
- L281 _public prototype_ `void UploadHeader();` — FHttpNetworkReplayStreamer
- L282 _public prototype_ `void FlushStream();`
- L283 _public prototype_ `void ConditionallyFlushStream();`
- L284 _public prototype_ `void StopUploading();`
- L285 _public prototype_ `bool IsTaskPendingOrInFlight( const EQueuedHttpRequestType::Type Type ) const;`
- L286 _public prototype_ `void CancelInFlightOrPendingTask( const EQueuedHttpRequestType::Type Type );`
- L287 _public prototype_ `void ConditionallyDownloadNextChunk();`
- L288 _public prototype_ `void RefreshViewer( const bool bFinal );`
- L289 _public prototype_ `void ConditionallyRefreshViewer();`
- L292 _public function_ `void SetLastError(const ENetworkReplayError::Type InLastError)` — `UE_DEPRECATED(5.1, "No longer used")`
- L293 _public prototype_ `void SetLastError(FHttpReplayResult&& Result);`
- L295 _public prototype_ `virtual void CancelStreamingRequests();`
- L296 _public prototype_ `void FlushCheckpointInternal( uint32 TimeInMS );`
- L297 _public prototype_ `virtual void AddEvent( const uint32 TimeInMS, const FString& Group, const FString& Meta, const TArray<uint8>& Data ) override;`
- L298 _public prototype_ `virtual void AddOrUpdateEvent( const FString& Name, const uint32 TimeInMS, const FString& Group, const FString& Meta, const TArray<uint8>& Data ) override;`
- L299 _public prototype_ `void AddRequestToQueue( const EQueuedHttpRequestType::Type Type, TSharedPtr<class IHttpRequest, ESPMode::ThreadSafe> Request, const int32 InMaxRetries = 0, const float InRetryDelay = 0.0f );`
- L300 _public prototype_ `void AddCustomRequestToQueue( TSharedPtr<FQueuedHttpRequest> Request );`
- L301 _public prototype_ `void AddResponseToCache( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse );`
- L302 _public prototype_ `void CleanupResponseCache();`
- L303 _public prototype_ `bool RetryRequest( TSharedPtr<FQueuedHttpRequest> Request, FHttpResponsePtr HttpResponse, const bool bIgnoreResponseCode = false );`
- L304 _public prototype_ `void EnumerateCheckpoints();`
- L305 _public prototype_ `void ConditionallyEnumerateCheckpoints();`
- L307 _public prototype_ `virtual void ProcessRequestInternal( TSharedPtr< class IHttpRequest, ESPMode::ThreadSafe > Request );`
- L308 _public function_ `virtual bool SupportsCompression() const`
- L309 _public function_ `virtual bool CompressBuffer( const TArray< uint8 >& InBuffer, FHttpStreamFArchive& OutCompressed ) const`
- L310 _public function_ `virtual bool DecompressBuffer(FHttpStreamFArchive& InCompressed, TArray< uint8 >& OutBuffer) const`
- L312 _public prototype_ `virtual FString GetRecordingMetadata() const;`
- L313 _public prototype_ `virtual bool DecompressResponse(FHttpResponsePtr HttpResponse, TArray<uint8>& ResultBuffer) const;`
- L314 _public prototype_ `virtual bool CompressRequest(FHttpRequestPtr HttpRequest, const TArray<uint8>& RequestBuffer) const;`
- L316 _public prototype_ `void InternalGotoTimeInMS(const uint32 TimeInMS, const FGotoCallback& Delegate, bool bDelta);`
- L317 _public prototype_ `void InternalGotoCheckpointIndex(const int32 CheckpointIndex, const FGotoCallback& Delegate, const FHttpRequestCompleteDelegate& RequestDelegate);`
- L320 _public prototype_ `void RequestFinished(EReplayStreamerState ExpectedStreamerState, EQueuedHttpRequestType::Type ExpectedType, FHttpRequestPtr HttpRequest );` — Delegates
- L322 _public prototype_ `void HttpStartDownloadingFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded );`
- L323 _public prototype_ `void HttpDownloadHeaderFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FDownloadHeaderCallback Delegate);`
- L324 _public prototype_ `void HttpDownloadFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, int32 RequestedStreamChunkIndex, bool bStreamWasLive );`
- L325 _public prototype_ `void HttpDownloadCheckpointFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded );`
- L326 _public prototype_ `void HttpDownloadCheckpointDeltaFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded );`
- L327 _public prototype_ `void HttpRefreshViewerFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded );`
- L328 _public prototype_ `void HttpStartUploadingFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded );`
- L329 _public prototype_ `void HttpStopUploadingFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded );`
- L330 _public prototype_ `void HttpHeaderUploadFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded );`
- L331 _public prototype_ `void HttpUploadStreamFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded );`
- L332 _public prototype_ `void HttpUploadCheckpointFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded );`
- L333 _public prototype_ `void HttpUploadCustomEventFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded );`
- L334 _public prototype_ `void HttpEnumerateSessionsFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FEnumerateStreamsCallback Delegate );`
- L335 _public prototype_ `void HttpEnumerateCheckpointsFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded );`
- L336 _public prototype_ `void HttpEnumerateEventsFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FEnumerateEventsCallback EnumerateEventsDelegate );`
- L337 _public prototype_ `void HttpAddUserFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded );`
- L338 _public prototype_ `void HttpRequestEventDataFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FRequestEventDataCallback RequestEventDataCompleteDelegate );`
- L342 _public prototype_ `void KeepReplayFinished( FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FKeepReplayCallback KeepReplayDelegate, FString ReplayName );` — Purposefully passing a copy of a string here, as we call this from a delegate and don't want to inadvertently capture a reference which may go out of scope.
- L344 _public prototype_ `bool ProcessNextHttpRequest();`
- L345 _public prototype_ `void Tick( const float DeltaTime );`
- L346 _public prototype_ `bool IsHttpRequestInFlight() const;` — True there is an http request currently in flight
- L347 _public prototype_ `bool HasPendingHttpRequests() const;` — True if there is an http request in flight, or there are more to process
- L348 _public prototype_ `bool IsStreaming() const;` — True if we are streaming a replay up or down
- L350 _public member_ `FHttpStreamFArchive HeaderArchive;` — Archive used to buffer the header stream
- L351 _public member_ `FHttpStreamFArchive StreamArchive;` — Archive used to buffer the data stream
- L352 _public member_ `FHttpStreamFArchive CheckpointArchive;` — Archive used to buffer checkpoint data
- L353 _public member_ `FString SessionName;` — Name of the session on the http replay server
- L354 _public member_ `FNetworkReplayVersion ReplayVersion;` — Version of the session
- L355 _public member_ `FString ServerURL;` — The address of the server
- L356 _public member_ `int32 StreamChunkIndex;` — Used as a counter to increment the stream.x extension count
- L357 _public member_ `double LastChunkTime;` — The last time we uploaded/downloaded a chunk
- L358 _public member_ `double LastRefreshViewerTime;` — The last time we refreshed ourselves as an active viewer
- L359 _public member_ `double LastRefreshCheckpointTime;`
- L360 _public member_ `EReplayStreamerState StreamerState;` — Overall state of the streamer
- L361 _public member_ `bool bStopStreamingCalled;`
- L362 _public member_ `bool bStreamIsLive;` — If true, we are viewing a live stream
- L363 _public member_ `FString StreamMetadata;`
- L364 _public member_ `int32 NumTotalStreamChunks;`
- L365 _public member_ `uint32 TotalDemoTimeInMS;`
- L366 _public member_ `uint32 LastTotalDemoTimeInMS;`
- L367 _public member_ `uint32 StreamTimeRangeStart;`
- L368 _public member_ `uint32 StreamTimeRangeEnd;`
- L369 _public member_ `FString ViewerName;`
- L370 _public member_ `uint32 HighPriorityEndTime;`
- L372 _public member_ `FStartStreamingCallback StartStreamingDelegate;` — Delegate passed in to StartStreaming
- L373 _public member_ `FGotoCallback GotoCheckpointDelegate;`
- L374 _public member_ `int32 DownloadCheckpointIndex;`
- L375 _public member_ `int32 DeltaDownloadCheckpointIndex;`
- L376 _public member_ `int64 LastGotoTimeInMS;`
- L378 _public member_ `FReplayEventList CheckpointList;`
- L380 _public member_ `TArray< TSharedPtr< FQueuedHttpRequest > > QueuedHttpRequests;`
- L381 _public member_ `TSharedPtr< FQueuedHttpRequest > InFlightHttpRequest;`
- L383 _public member_ `TSet< FString > EventGroupSet;`
- L385 _public member_ `uint64 TotalUploadBytes;`
- L387 _public member_ `TMap< FString, FCachedResponse > ResponseCache;`
- L389 _public member_ `int32 RefreshViewerFails;`

#### class `FHttpNetworkReplayStreamingFactory`  
`class FHttpNetworkReplayStreamingFactory : public INetworkReplayStreamingFactory, public FTickableGameObject`  
_L394-412_
- inherits: `INetworkReplayStreamingFactory,FTickableGameObject`
- L398 _public prototype_ `virtual TSharedPtr< INetworkReplayStreamer > CreateReplayStreamer() override;` — INetworkReplayStreamingFactory
- L401 _public prototype_ `virtual void Tick( float DeltaTime ) override;` — FTickableGameObject
- L402 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L403 _public prototype_ `virtual TStatId GetStatId() const override;`
- L404 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L405 _public prototype_ `virtual void Flush() override;`
- L407 _public prototype_ `virtual void ShutdownModule() override;`
- L409 _public prototype_ `bool HasPendingHttpRequests() const;`
- L411 _public member_ `TArray< TSharedPtr< FHttpNetworkReplayStreamer > > HttpStreamers;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HTTPNETWORKREPLAYSTREAMING_API`
- L34 _namespace_ `namespace EQueuedHttpRequestType`
- L59 _function_ `inline const TCHAR* ToString( EQueuedHttpRequestType::Type Type )` (scope `EQueuedHttpRequestType`)
- L208 _prototype_ `DECLARE_NETRESULT_ENUM(EHttpReplayResult);`
- L210 _prototype_ `const TCHAR* LexToString(EHttpReplayResult Enum);`
