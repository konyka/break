# Runtime / NetworkReplayStreaming

- module root: `Source/Runtime/NetworkReplayStreaming/NetworkReplayStreaming`
- headers: 1; symbols: 217
- symbol kinds: class=5, delegate=19, enum=4, enumerator=17, function=27, member=42, namespace=1, prototype=87, struct=15
- PublicDependencyModuleNames: Analytics, Core, Json, NetCore

### `Source/Runtime/NetworkReplayStreaming/NetworkReplayStreaming/Public/NetworkReplayStreaming.h` (Public)


#### class `FReplayEventListItem`  
`class FReplayEventListItem : public FJsonSerializable`  
_L32-52_
- inherits: `FJsonSerializable`
- L35 _public function_ `FReplayEventListItem() : Time1(0), Time2(0)`
- L36 _public prototype_ `virtual ~FReplayEventListItem() = default;`
- L38 _public member_ `FString ID;`
- L39 _public member_ `FString Group;`
- L40 _public member_ `FString Metadata;`
- L41 _public member_ `uint32 Time1;`
- L42 _public member_ `uint32 Time2;`

#### class `FReplayEventList`  
`class FReplayEventList : public FJsonSerializable`  
_L54-67_
- inherits: `FJsonSerializable`
- L57 _public function_ `FReplayEventList()`
- L59 _public prototype_ `virtual ~FReplayEventList() = default;`
- L61 _public member_ `TArray< FReplayEventListItem > ReplayEvents;`

#### struct `FNetworkReplayStreamInfo`  
`struct FNetworkReplayStreamInfo`  
_L70-100_
- desc: Struct to store information about a stream, returned from search results.
- L72 _public function_ `FNetworkReplayStreamInfo() : Timestamp( 0 ), SizeInBytes( 0 ), LengthInMS( 0 ), NumViewers( 0 ), Changelist( 0 ), bIsLive(false), bShouldKeep( false )`
- L75 _public member_ `FString Name;` — The name of the stream (generally this is auto generated, refer to friendly name for UI)
- L78 _public member_ `FString FriendlyName;` — The UI friendly name of the stream
- L81 _public member_ `FDateTime Timestamp;` — The date and time the stream was recorded
- L84 _public member_ `int64 SizeInBytes;` — The size of the stream
- L87 _public member_ `int32 LengthInMS;` — The duration of the stream in MS
- L90 _public member_ `int32 NumViewers;` — Number of viewers viewing this stream
- L93 _public member_ `int32 Changelist;` — The changelist of the replay
- L96 _public member_ `bool bIsLive;` — True if the stream is live and the game hasn't completed yet
- L99 _public member_ `bool bShouldKeep;` — Debug feature that allows us to mark replays to not be deleted. True if this replay has been marked as such

#### enum `ENetworkReplayError::Type`  
`enum UE_DEPRECATED(5.1, "No longer used") Type`  
_L104-111_
- L107 _public enumerator_ `None` — There are currently no issues
- L110 _public enumerator_ `ServiceUnavailable` — The backend service supplying the stream is unavailable, or connection interrupted

#### enum `EStreamingOperationResult`  
`enum class EStreamingOperationResult`  
_L196-208_
- desc: Possible results for replay commands.
- L198 _public enumerator_ `Success` — The operation succeeded.
- L199 _public enumerator_ `Unsupported` — The operation is not supported by the current streamer.
- L200 _public enumerator_ `ReplayNotFound` — The requested replay was not found.
- L201 _public enumerator_ `ReplayCorrupt` — The requested replay was found but was corrupt.
- L202 _public enumerator_ `NotEnoughSpace` — The operation failed due to insufficient storage space.
- L203 _public enumerator_ `NotEnoughSlots` — The operation failed due to reaching a predefined replay limit.
- L204 _public enumerator_ `Unspecified` — The operation failed for unspecified reasons.
- L205 _public enumerator_ `UnfinishedTask` — The operation failed due to an outstanding task.
- L206 _public enumerator_ `EventNotFound` — The operation failed because the event could not be found.
- L207 _public enumerator_ `DecryptFailure` — The operation failed because decryption failed.

#### struct `FStreamingResultBase`  
`struct FStreamingResultBase`  
_L214-224_
- desc: Base type for all Streaming Operation results. Should be used to store generic result information and convenience methods.
- L216 _public member_ `EStreamingOperationResult Result = EStreamingOperationResult::Unspecified;`
- L218 _public prototype_ `virtual ~FStreamingResultBase() = default;`
- L220 _public function_ `bool WasSuccessful() const`

#### struct `FStartStreamingResult`  
`struct FStartStreamingResult : public FStreamingResultBase`  
_L227-231_
- inherits: `FStreamingResultBase`
- desc: Start StartStreaming Types
- L230 _public member_ `bool bRecording = false;` — Whether or not Recording was requested (vs. Playback).

#### struct `FReplayCheckpointInfo`  
`struct FReplayCheckpointInfo`  
_L254-265_
- desc: Information about a checkpoint that was loaded as a result of a Goto Request.
- L257 _public member_ `static constexpr uint32 INVALID_CHECKPOINT = -2;` — Indicates an invalid checkpoint, or a bad request.
- L261 _public member_ `static constexpr uint32 NO_CHECKPOINT = -1;` — Indicates that no checkpoint was loaded as a part of the request. This can happen if the requested time was before any available checkpoints.
- L263 _public member_ `uint32 CheckpointStartTime = INVALID_CHECKPOINT;`
- L264 _public member_ `uint32 CheckpointIndex = INVALID_CHECKPOINT;`

#### struct `FGotoResult`  
`struct FGotoResult : public FStreamingResultBase`  
_L267-275_
- inherits: `FStreamingResultBase`
- L271 _public member_ `int64 ExtraTimeMS = -1;` — Amount of extra time that the stream may need to be fast forwarded in order to reach the exact time specified (relative to the latest checkpoint before the specified time).
- L274 _public member_ `FReplayCheckpointInfo CheckpointInfo;` — Info about the checkpoint that was loaded as a result of the request.

#### struct `FDeleteFinishedStreamResult`  
`struct FDeleteFinishedStreamResult : public FStreamingResultBase`  
_L296-298_
- inherits: `FStreamingResultBase`
- desc: Start DeleteFinishedStream Types

#### struct `FEnumerateStreamsResult`  
`struct FEnumerateStreamsResult : public FStreamingResultBase`  
_L319-326_
- inherits: `FStreamingResultBase`
- desc: Start EnumerateStreams Types
- L322 _public member_ `TArray<FNetworkReplayStreamInfo> FoundStreams;` — A list of streams that were found
- L325 _public member_ `TArray<FString> CorruptedStreams;` — A list of streams (by name) that were found and were corrupted.

#### struct `FEnumerateEventsResult`  
`struct FEnumerateEventsResult : public FStreamingResultBase`  
_L347-351_
- inherits: `FStreamingResultBase`
- desc: Start EnumerateEvents Types
- L350 _public member_ `FReplayEventList ReplayEventList;` — A list of events that were found

#### struct `FRequestEventDataResult`  
`struct FRequestEventDataResult : public FStreamingResultBase`  
_L372-376_
- inherits: `FStreamingResultBase`
- desc: Start RequestEventData Types
- L375 _public member_ `TArray<uint8> ReplayEventListItem;` — A replay event with its data parameter filled in.

#### struct `FRequestEventGroupDataResult`  
`struct FRequestEventGroupDataResult : public FStreamingResultBase`  
_L397-401_
- inherits: `FStreamingResultBase`
- desc: Start RequestEventGroupData Types
- L399 _public member_ `TArray<FReplayEventListItem> ReplayEventListItems;`
- L400 _public member_ `TArray<FRequestEventDataResult> ReplayEventListResults;`

#### struct `FDownloadHeaderResult`  
`struct FDownloadHeaderResult : public FStreamingResultBase`  
_L407-409_
- inherits: `FStreamingResultBase`
- desc: Start DownloadHeader Types

#### struct `FSearchEventsResult`  
`struct FSearchEventsResult : public FStreamingResultBase`  
_L430-437_
- inherits: `FStreamingResultBase`
- desc: Start SearchEvent Types
- L433 _public member_ `TArray<FNetworkReplayStreamInfo> FoundStreams;` — An array containing information about the streams that were found.
- L436 _public member_ `TArray<FString> CorruptedStreams;` — A list of streams (by name) that were found and were corrupted.

#### struct `FKeepReplayResult`  
`struct FKeepReplayResult : public FStreamingResultBase`  
_L458-468_
- inherits: `FStreamingResultBase`
- desc: Start KeepReplay Types
- L462 _public member_ `FString NewReplayName;` — Saving the replay may cause the name to change. This points to the new name for the replay so it can be referenced in further operations.
- L467 _public member_ `int64 RequiredSpace = 0;` — Only valid if the error is NotEnoughSpace or NotEnoughSlots. For NotEnoughSpace, this will be the amount of storage space needed (in bytes) for the replay. For NotEnoughSlots, this will be the maximum number of slots that can be used to store replays.

#### struct `FRenameReplayResult`  
`struct FRenameReplayResult : public FStreamingResultBase`  
_L474-476_
- inherits: `FStreamingResultBase`
- desc: Start RenameReplay Types

#### enum `EReplayCheckpointType`  
`enum class EReplayCheckpointType : uint8`  
_L481-485_
- L483 _public enumerator_ `Full`
- L484 _public enumerator_ `Delta`

#### struct `FStartStreamingParameters`  
`struct FStartStreamingParameters`  
_L487-495_
- L489 _public member_ `FString CustomName;`
- L490 _public member_ `FString FriendlyName;`
- L491 _public member_ `FString DemoURL;`
- L492 _public member_ `TArray<int32> UserIndices;`
- L493 _public member_ `FNetworkReplayVersion ReplayVersion;`
- L494 _public member_ `bool bRecord;`

#### enum `EReplayStreamerState`  
`enum class EReplayStreamerState : uint8`  
_L497-502_
- L499 _public enumerator_ `Idle` — The streamer is idle. Either we haven't started activity yet, or we are done
- L500 _public enumerator_ `Recording` — We are in the process of recording a replay
- L501 _public enumerator_ `Playback` — We are in the process of playing a replay

#### class `INetworkReplayStreamer`  
`class INetworkReplayStreamer`  
_L515-680_
- desc: Generic interface for network replay streaming When a delegate is provided as an argument, it is expected that the implementation calls that delegate upon completion, and indicates success / failure through an appropriate result type passed into the delegate.
- L518 _public prototype_ `INetworkReplayStreamer();`
- L519 _public prototype_ `virtual ~INetworkReplayStreamer();`
- L521 _public prototype_ `virtual void StartStreaming(const FStartStreamingParameters& Params, const FStartStreamingCallback& Delegate) = 0;`
- L523 _public prototype_ `virtual void StopStreaming() = 0;`
- L524 _public prototype_ `virtual FArchive* GetHeaderArchive() = 0;`
- L525 _public prototype_ `virtual FArchive* GetStreamingArchive() = 0;`
- L526 _public prototype_ `virtual FArchive* GetCheckpointArchive() = 0;`
- L527 _public prototype_ `virtual void FlushCheckpoint(const uint32 TimeInMS) = 0;`
- L529 _public prototype_ `virtual void GotoCheckpointIndex(const int32 CheckpointIndex, const FGotoCallback& Delegate, EReplayCheckpointType CheckpointType) = 0;`
- L531 _public prototype_ `virtual void GotoTimeInMS(const uint32 TimeInMS, const FGotoCallback& Delegate, EReplayCheckpointType CheckpointType) = 0;`
- L533 _public prototype_ `virtual bool IsCheckpointTypeSupported(EReplayCheckpointType CheckpointType) const = 0;`
- L535 _public prototype_ `virtual void UpdateTotalDemoTime(uint32 TimeInMS) = 0;`
- L536 _public prototype_ `virtual void UpdatePlaybackTime(uint32 TimeInMS) = 0;`
- L539 _public prototype_ `virtual uint32 GetTotalDemoTime() const = 0;` — Time in milliseconds
- L541 _public prototype_ `virtual bool IsDataAvailable() const = 0;`
- L542 _public prototype_ `virtual void SetHighPriorityTimeRange(const uint32 StartTimeInMS, const uint32 EndTimeInMS) = 0;`
- L543 _public prototype_ `virtual bool IsDataAvailableForTimeRange(const uint32 StartTimeInMS, const uint32 EndTimeInMS) = 0;`
- L544 _public prototype_ `virtual bool IsLoadingCheckpoint() const = 0;`
- L545 _public prototype_ `virtual void AddEvent(const uint32 TimeInMS, const FString& Group, const FString& Meta, const TArray<uint8>& Data) = 0;`
- L546 _public prototype_ `virtual void AddOrUpdateEvent(const FString& Name, const uint32 TimeInMS, const FString& Group, const FString& Meta, const TArray<uint8>& Data) = 0;`
- L548 _public prototype_ `virtual void EnumerateEvents(const FString& Group, const FEnumerateEventsCallback& Delegate) = 0;`
- L550 _public prototype_ `virtual void EnumerateEvents(const FString& ReplayName, const FString& Group, const FEnumerateEventsCallback& Delegate) = 0;`
- L551 _public prototype_ `virtual void EnumerateEvents( const FString& ReplayName, const FString& Group, const int32 UserIndex, const FEnumerateEventsCallback& Delegate ) = 0;`
- L553 _public prototype_ `virtual void RequestEventData(const FString& EventID, const FRequestEventDataCallback& Delegate) = 0;`
- L554 _public prototype_ `virtual void RequestEventData(const FString& ReplayName, const FString& EventID, const FRequestEventDataCallback& Delegate) = 0;`
- L555 _public prototype_ `virtual void RequestEventData(const FString& ReplayName, const FString& EventID, const int32 UserIndex, const FRequestEventDataCallback& Delegate) = 0;`
- L557 _public prototype_ `virtual void RequestEventGroupData(const FString& Group, const FRequestEventGroupDataCallback& Delegate) = 0;`
- L558 _public prototype_ `virtual void RequestEventGroupData(const FString& ReplayName, const FString& Group, const FRequestEventGroupDataCallback& Delegate) = 0;`
- L559 _public prototype_ `virtual void RequestEventGroupData(const FString& ReplayName, const FString& Group, const int32 UserIndex, const FRequestEventGroupDataCallback& Delegate) = 0;`
- L561 _public prototype_ `virtual void SearchEvents(const FString& EventGroup, const FSearchEventsCallback& Delegate) = 0;`
- L562 _public prototype_ `virtual void RefreshHeader() = 0;`
- L564 _public prototype_ `virtual void DownloadHeader(const FDownloadHeaderCallback& Delegate) = 0;`
- L572 _public prototype_ `virtual void KeepReplay(const FString& ReplayName, const bool bKeep, const FKeepReplayCallback& Delegate) = 0;` — Used to commit a replay to permanent storage. @param ReplayName Name of the replay to keep. @param bKeep Whether or not we actually want to keep this replay.
- L573 _public prototype_ `virtual void KeepReplay(const FString& ReplayName, const bool bKeep, const int32 UserIndex, const FKeepReplayCallback& Delegate) = 0;`
- L582 _public prototype_ `virtual void RenameReplayFriendlyName(const FString& ReplayName, const FString& NewFriendlyName, const FRenameReplayCallback& Delegate) = 0;` — Used to change the friendly name of a replay. Note, changing the friendly name **does not** change the name used to refer to replay. @param ReplayName Name of the replay to rename. @param NewFriendlyName The new friendly name for the replay.
- L583 _public prototype_ `virtual void RenameReplayFriendlyName(const FString& ReplayName, const FString& NewFriendlyName, const int32 UserIndex, const FRenameReplayCallback& Delegate) = 0;`
- L592 _public prototype_ `virtual void RenameReplay(const FString& ReplayName, const FString& NewName, const FRenameReplayCallback& Delegate) = 0;` — Used to change the name of a replay. Note, this **will** change the name used to refer to the replay (if successful). @param ReplayName Name of the replay to rename. @param NewName The new name for the replay.
- L593 _public prototype_ `virtual void RenameReplay(const FString& ReplayName, const FString& NewName, const int32 UserIndex, const FRenameReplayCallback& Delegate) = 0;`
- L596 _public prototype_ `virtual bool IsLive() const = 0;` — Returns true if the playing stream is currently in progress
- L599 _public prototype_ `virtual FString GetReplayID() const = 0;` — Returns the active replay name
- L602 _public function_ `virtual EReplayStreamerState GetReplayStreamerState() const` — Return current recording/playback state
- L610 _public prototype_ `virtual void DeleteFinishedStream(const FString& StreamName, const FDeleteFinishedStreamCallback& Delegate) = 0;` — Attempts to delete the stream with the specified name. May execute asynchronously. @param StreamName The name of the stream to delete @param Delegate A delegate that will be executed if bound when the delete operation completes
- L611 _public prototype_ `virtual void DeleteFinishedStream(const FString& StreamName, const int32 UserIndex, const FDeleteFinishedStreamCallback& Delegate) = 0;`
- L617 _public prototype_ `virtual void EnumerateStreams(const FNetworkReplayVersion& ReplayVersion, const int32 UserIndex, const FString& MetaString, const TArray< FString >& ExtraParms, const FEnumerateStreamsCallback& Delegate) = 0;` — Retrieves the streams that are available for viewing. May execute asynchronously. Allows the caller to pass in a custom list of query parameters
- L624 _public prototype_ `virtual void EnumerateRecentStreams(const FNetworkReplayVersion& ReplayVersion, const int32 UserIndex, const FEnumerateStreamsCallback& Delegate) = 0;` — Retrieves the streams that have been recently viewed. May execute asynchronously. @param Delegate A delegate that will be executed if bound when the list of streams is available
- L629 _public prototype_ `virtual ENetworkReplayError::Type GetLastError() const;` — `UE_DEPRECATED(5.1, "Deprecated in favor of HasError and HandleLastError")` — Returns the last error that occurred while streaming replays
- L632 _public prototype_ `virtual bool HasError() const;`
- L634 _public prototype_ `virtual UE::Net::EHandleNetResult HandleLastError(UE::Net::FNetResultManager& ResultManager);`
- L636 _public prototype_ `virtual void SetExtendedError(UE::Net::FNetResult&& Result);`
- L643 _public prototype_ `virtual void AddUserToReplay( const FString& UserString ) = 0;` — Adds a join-in-progress user to the set of users associated with the currently recording replay (if any) @param UserString a string that uniquely identifies the user, usually their FUniqueNetId
- L650 _public prototype_ `virtual void SetTimeBufferHintSeconds(const float InTimeBufferHintSeconds) = 0;` — Sets a hint for how much data needs to be kept in memory. If set to a value greater than zero, a streamer implementation may free any in-memory data that would be required to go to a time before the beginning of the buffer.
- L653 _public prototype_ `virtual uint32 GetMaxFriendlyNameSize() const = 0;` — Returns the maximum size of the friendly name text for this streamer, or 0 for unlimited.
- L661 _public prototype_ `virtual EStreamingOperationResult SetDemoPath(const FString& DemoPath) = 0;` — Changes the base directory where Demos are stored. Note, this will always fail for streamers that don't support replays stored on disk. This method should not be called after StartStreaming, or while async operations are pending on a streamer.
- L667 _public prototype_ `virtual EStreamingOperationResult GetDemoPath(FString& DemoPath) const = 0;` — Gets the current base directory where Demos are stored. Note, this will always fail for streamers that don't support replays stored on disk.
- L669 _public function_ `virtual void SetAnalyticsProvider(TSharedPtr<IAnalyticsProvider>& InProvider)`
- L671 _public prototype_ `virtual TArray<FAnalyticsEventAttribute> AppendCommonReplayAttributes(TArray<FAnalyticsEventAttribute>&& Attrs) const;`
- L673 _public function_ `virtual void Exec(const TCHAR* Cmd, FOutputDevice& Ar)`
- L676 _public member_ `static FOnReplayGetAnalyticsAttributes OnReplayGetAnalyticsAttributes;` — Called from base streamer interface AppendCommonReplayAttributes to set common attributes
- L679 _private member_ `TPimplPtr<UE::Net::FNetResult, EPimplPtrMode::DeepCopy> ExtendedError;`

#### class `INetworkReplayStreamingFactory`  
`class INetworkReplayStreamingFactory : public IModuleInterface`  
_L683-688_
- inherits: `IModuleInterface`
- desc: Replay streamer factory
- L686 _public prototype_ `virtual TSharedPtr<INetworkReplayStreamer> CreateReplayStreamer() = 0;`
- L687 _public function_ `virtual void Flush()`

#### class `FNetworkReplayStreaming`  
`class FNetworkReplayStreaming : public IModuleInterface, public FSelfRegisteringExec`  
_L691-733_
- inherits: `IModuleInterface,FSelfRegisteringExec`
- desc: Replay streaming factory manager
- L694 _public function_ `FNetworkReplayStreaming()`
- L695 _public prototype_ `virtual ~FNetworkReplayStreaming() = default;`
- L697 _public function_ `static inline FNetworkReplayStreaming& Get()`
- L702 _public prototype_ `void Flush();`
- L704 _public prototype_ `virtual INetworkReplayStreamingFactory& GetFactory(const TCHAR* FactoryNameOverride = nullptr);`
- L706 _public prototype_ `virtual const FString GetAutomaticReplayPrefixExtern() const;`
- L707 _public prototype_ `virtual const int32 GetMaxNumberOfAutomaticReplaysExtern() const;`
- L711 _public prototype_ `static int32 GetMaxNumberOfAutomaticReplays();` — Gets the configured max value for the number of automatic replays to support. 0 indicates no limit.
- L716 _public prototype_ `static FString GetAutomaticReplayPrefix();` — Gets the configured automatic replay name prefix. The prefix should always be a non-empty string. If using streamers that store replays on disk, this must also be comprised of only valid file name characters.
- L720 _public prototype_ `static bool UseDateTimeAsAutomaticReplayPostfix();` — Gets the configured value for whether or not we should use FDateTime::Now as the automatic replay postfix. If false, it's up to the streamer to determine a proper postfix.
- L724 _public prototype_ `static FString GetReplayFileExtension();` — Gets the file extension for replay streamers to use when recording replay files to the local file system. Includes the "." prefix
- L728 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L732 _private member_ `TSet<FName> LoadedFactories;`

#### Free symbols / members of external scopes

- L102 _namespace_ `namespace ENetworkReplayError`
- L114 _function_ `inline const TCHAR* ToString( const ENetworkReplayError::Type FailureType )` (scope `ENetworkReplayError`)
- L134 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnStreamReadyDelegate, const bool, const bool );` — Delegate called when StartStreaming() completes. @param bWasSuccessful Whether streaming was started. @param bRecord Whether streaming is recording or not (vs playing)
- L134 _prototype_ `DECLARE_DELEGATE_TwoParams( FOnStreamReadyDelegate, const bool, const bool );` — Delegate called when StartStreaming() completes. @param bWasSuccessful Whether streaming was started. @param bRecord Whether streaming is recording or not (vs playing)
- L141 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnCheckpointReadyDelegate, const bool, const int64 );` — Delegate called when GotoCheckpointIndex() completes. @param bWasSuccessful Whether streaming was started.
- L141 _prototype_ `DECLARE_DELEGATE_TwoParams( FOnCheckpointReadyDelegate, const bool, const int64 );` — Delegate called when GotoCheckpointIndex() completes. @param bWasSuccessful Whether streaming was started.
- L148 _delegate_ `DECLARE_DELEGATE_OneParam( FOnDeleteFinishedStreamComplete, const bool );` — Delegate called when DeleteFinishedStream() completes. @param bWasSuccessful Whether the stream was deleted.
- L148 _prototype_ `DECLARE_DELEGATE_OneParam( FOnDeleteFinishedStreamComplete, const bool );` — Delegate called when DeleteFinishedStream() completes. @param bWasSuccessful Whether the stream was deleted.
- L155 _delegate_ `DECLARE_DELEGATE_OneParam( FOnEnumerateStreamsComplete, const TArray<FNetworkReplayStreamInfo>& );` — Delegate called when EnumerateStreams() completes. @param Streams An array containing information about the streams that were found.
- L155 _prototype_ `DECLARE_DELEGATE_OneParam( FOnEnumerateStreamsComplete, const TArray<FNetworkReplayStreamInfo>& );` — Delegate called when EnumerateStreams() completes. @param Streams An array containing information about the streams that were found.
- L163 _delegate_ `DECLARE_DELEGATE_TwoParams(FEnumerateEventsCompleteDelegate, const FReplayEventList&, bool);` — Delegate called when EnumerateEvents() completes. @param ReplayEventList A list of events that were found # @param bWasSuccessful Whether enumerating events was successful
- L163 _prototype_ `DECLARE_DELEGATE_TwoParams(FEnumerateEventsCompleteDelegate, const FReplayEventList&, bool);` — Delegate called when EnumerateEvents() completes. @param ReplayEventList A list of events that were found # @param bWasSuccessful Whether enumerating events was successful
- L171 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRequestEventDataComplete, const TArray<uint8>&, bool) DECLARE_DELEGATE_OneParam(FOnDownloadHeaderComplete, const bool);` — Delegate called when RequestEventData() completes. @param ReplayEventListItem A replay event with its data parameter filled in # @param bWasSuccessful Whether enumerating events was successful
- L171 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnRequestEventDataComplete, const TArray<uint8>&, bool) DECLARE_DELEGATE_OneParam(FOnDownloadHeaderComplete, const bool);` — Delegate called when RequestEventData() completes. @param ReplayEventListItem A replay event with its data parameter filled in # @param bWasSuccessful Whether enumerating events was successful
- L178 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDownloadHeaderComplete, const bool);` — Delegate called when DownloadHeader() completes. @param bWasSuccessful Whether the header was successfully downloaded.
- L233 _delegate_ `DECLARE_DELEGATE_OneParam(FStartStreamingCallback, const FStartStreamingResult&);`
- L233 _prototype_ `DECLARE_DELEGATE_OneParam(FStartStreamingCallback, const FStartStreamingResult&);`
- L235 _function_ `static inline FStartStreamingCallback UpgradeStartStreamingDelegate(const FOnStreamReadyDelegate& OldDelegate)`
- L240 _function_ `` (scope `UpgradeStartStreamingDelegate`)
- L277 _delegate_ `DECLARE_DELEGATE_OneParam(FGotoCallback, const FGotoResult&);`
- L277 _prototype_ `DECLARE_DELEGATE_OneParam(FGotoCallback, const FGotoResult&);`
- L279 _function_ `static inline FGotoCallback UpgradeGotoDelegate(const FOnCheckpointReadyDelegate& OldDelegate)`
- L284 _function_ `` (scope `UpgradeGotoDelegate`)
- L300 _delegate_ `DECLARE_DELEGATE_OneParam(FDeleteFinishedStreamCallback, const FDeleteFinishedStreamResult&);`
- L300 _prototype_ `DECLARE_DELEGATE_OneParam(FDeleteFinishedStreamCallback, const FDeleteFinishedStreamResult&);`
- L302 _function_ `static inline FDeleteFinishedStreamCallback UpgradeDeleteFinishedStreamDelegate(const FOnDeleteFinishedStreamComplete& OldDelegate)`
- L307 _function_ `` (scope `UpgradeDeleteFinishedStreamDelegate`)
- L328 _delegate_ `DECLARE_DELEGATE_OneParam(FEnumerateStreamsCallback, const FEnumerateStreamsResult&);`
- L328 _prototype_ `DECLARE_DELEGATE_OneParam(FEnumerateStreamsCallback, const FEnumerateStreamsResult&);`
- L330 _function_ `static inline FEnumerateStreamsCallback UpgradeEnumerateStreamsDelegate(const FOnEnumerateStreamsComplete& OldDelegate)`
- L335 _function_ `` (scope `UpgradeEnumerateStreamsDelegate`)
- L353 _delegate_ `DECLARE_DELEGATE_OneParam(FEnumerateEventsCallback, const FEnumerateEventsResult&);`
- L353 _prototype_ `DECLARE_DELEGATE_OneParam(FEnumerateEventsCallback, const FEnumerateEventsResult&);`
- L355 _function_ `static inline FEnumerateEventsCallback UpgradeEnumerateEventsDelegate(const FEnumerateEventsCompleteDelegate& OldDelegate)`
- L360 _function_ `` (scope `UpgradeEnumerateEventsDelegate`)
- L378 _delegate_ `DECLARE_DELEGATE_OneParam(FRequestEventDataCallback, const FRequestEventDataResult&);`
- L378 _prototype_ `DECLARE_DELEGATE_OneParam(FRequestEventDataCallback, const FRequestEventDataResult&);`
- L380 _function_ `static inline FRequestEventDataCallback UpgradeRequestEventDelegate(const FOnRequestEventDataComplete& OldDelegate)`
- L385 _function_ `` (scope `UpgradeRequestEventDelegate`)
- L403 _delegate_ `DECLARE_DELEGATE_OneParam(FRequestEventGroupDataCallback, const FRequestEventGroupDataResult&);`
- L403 _prototype_ `DECLARE_DELEGATE_OneParam(FRequestEventGroupDataCallback, const FRequestEventGroupDataResult&);`
- L411 _delegate_ `DECLARE_DELEGATE_OneParam(FDownloadHeaderCallback, const FDownloadHeaderResult&);`
- L411 _prototype_ `DECLARE_DELEGATE_OneParam(FDownloadHeaderCallback, const FDownloadHeaderResult&);`
- L413 _function_ `static inline FDownloadHeaderCallback UpgradeDownloadHeaderDelegate(const FOnDownloadHeaderComplete& OldDelegate)`
- L418 _function_ `` (scope `UpgradeDownloadHeaderDelegate`)
- L439 _delegate_ `DECLARE_DELEGATE_OneParam(FSearchEventsCallback, const FSearchEventsResult&);`
- L439 _prototype_ `DECLARE_DELEGATE_OneParam(FSearchEventsCallback, const FSearchEventsResult&);`
- L441 _function_ `static inline FSearchEventsCallback UpgradeSearchEventsDelegate(const FOnEnumerateStreamsComplete& OldDelegate)`
- L446 _function_ `` (scope `UpgradeSearchEventsDelegate`)
- L470 _delegate_ `DECLARE_DELEGATE_OneParam(FKeepReplayCallback, const FKeepReplayResult&);`
- L470 _prototype_ `DECLARE_DELEGATE_OneParam(FKeepReplayCallback, const FKeepReplayResult&);`
- L478 _delegate_ `DECLARE_DELEGATE_OneParam(FRenameReplayCallback, const FRenameReplayResult&);`
- L478 _prototype_ `DECLARE_DELEGATE_OneParam(FRenameReplayCallback, const FRenameReplayResult&);`
- L504 _prototype_ `FString LexToString(const EReplayStreamerState State);`
- L506 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReplayGetAnalyticsAttributes, const class INetworkReplayStreamer* , TArray<FAnalyticsEventAttribute>& );`
- L506 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReplayGetAnalyticsAttributes, const class INetworkReplayStreamer* , TArray<FAnalyticsEventAttribute>& );`
