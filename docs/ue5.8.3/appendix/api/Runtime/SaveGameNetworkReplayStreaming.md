# Runtime / SaveGameNetworkReplayStreaming

- module root: `Source/Runtime/NetworkReplayStreaming/SaveGameNetworkReplayStreaming`
- headers: 1; symbols: 79
- symbol kinds: class=2, function=1, member=17, prototype=55, struct=4
- PrivateDependencyModuleNames: Engine, Json
- PublicDependencyModuleNames: Core, LocalFileNetworkReplayStreaming, NetworkReplayStreaming

### `Source/Runtime/NetworkReplayStreaming/SaveGameNetworkReplayStreaming/Public/SaveGameNetworkReplayStreaming.h` (Public)


#### class `FSaveGameNetworkReplayStreamer`  
`class FSaveGameNetworkReplayStreamer : public FLocalFileNetworkReplayStreamer`  
_L32-168_
- inherits: `FLocalFileNetworkReplayStreamer`
- desc: Local file streamer that supports playback/recording to files on disk, and transferring replays to and from SaveGame slots. EnumerateStreams may be used to list all available replays that are in SaveGame slots. The Name member in any FNetworkReplayStreamInfo returned will be the SaveGame slot where the replay lives. EnumerateRecentStreams may be used to list all available replays that are not in SaveGame slots. The Name member in any FNetworkReplayStreamInfo returned will be the relative path where the replay lives. StartStreaming can be used to play replays both in and not in SaveGame slots. StartStreaming does not automatically put a replay in a SaveGame slot. KeepReplay can be used to move a non SaveGame slot replay into a SaveGame slot. The original replay is left untouched. DeleteFinishedStream can be used to delete replays both in and not in SaveGame slots. Only one Save Game operation is permitted to occur at a single time (even across Streamers). TODO: Proper handling of UserIndex.
- L36 _public prototype_ `FSaveGameNetworkReplayStreamer();`
- L37 _public prototype_ `FSaveGameNetworkReplayStreamer(const FString& DemoSavePath, const FString& PlaybackReplayName);`
- L40 _public prototype_ `virtual void StartStreaming(const FStartStreamingParameters& Params, const FStartStreamingCallback& Delegate) override;` — INetworkReplayStreamer implementation
- L41 _public prototype_ `virtual void DeleteFinishedStream(const FString& ReplayName, const FDeleteFinishedStreamCallback& Delegate) override;`
- L42 _public prototype_ `virtual void DeleteFinishedStream(const FString& StreamName, const int32 UserIndex, const FDeleteFinishedStreamCallback& Delegate) override;`
- L43 _public prototype_ `virtual void EnumerateStreams(const FNetworkReplayVersion& InReplayVersion, const int32 UserIndex, const FString& MetaString, const TArray< FString >& ExtraParms, const FEnumerateStreamsCallback& Delegate) override;`
- L44 _public prototype_ `virtual void EnumerateRecentStreams(const FNetworkReplayVersion& ReplayVersion, const int32 UserIndex, const FEnumerateStreamsCallback& Delegate) override;`
- L45 _public prototype_ `virtual void KeepReplay(const FString& ReplayName, const bool bKeep, const FKeepReplayCallback& Delegate) override;`
- L46 _public prototype_ `virtual void KeepReplay(const FString& ReplayName, const bool bKeep, const int32 UserIndex, const FKeepReplayCallback& Delegate) override;`
- L47 _public prototype_ `virtual void RenameReplayFriendlyName(const FString& ReplayName, const FString& NewFriendlyName, const FRenameReplayCallback& Delegate) override;`
- L48 _public prototype_ `virtual void RenameReplayFriendlyName(const FString& ReplayName, const FString& NewFriendlyName, const int32 UserIndex, const FRenameReplayCallback& Delegate) override;`
- L49 _public prototype_ `virtual void RenameReplay(const FString& ReplayName, const FString& NewName, const FRenameReplayCallback& Delegate) override;`
- L50 _public prototype_ `virtual void RenameReplay(const FString& ReplayName, const FString& NewName, const int32 UserIndex, const FRenameReplayCallback& Delegate) override;`
- L52 _public prototype_ `virtual void EnumerateEvents(const FString& ReplayName, const FString& Group, const FEnumerateEventsCallback& Delegate) override;`
- L53 _public prototype_ `virtual void EnumerateEvents( const FString& ReplayName, const FString& Group, const int32 UserIndex, const FEnumerateEventsCallback& Delegate) override;`
- L54 _public prototype_ `virtual void RequestEventData(const FString& EventID, const FRequestEventDataCallback& Delegate) override;`
- L55 _public prototype_ `virtual void RequestEventData(const FString& ReplayName, const FString& EventID, const FRequestEventDataCallback& Delegate) override;`
- L56 _public prototype_ `virtual void RequestEventData(const FString& ReplayName, const FString& EventId, const int32 UserIndex, const FRequestEventDataCallback& Delegate) override;`
- L57 _public prototype_ `virtual void RequestEventGroupData(const FString& Group, const FRequestEventGroupDataCallback& Delegate) override;`
- L58 _public prototype_ `virtual void RequestEventGroupData(const FString& ReplayName, const FString& Group, const FRequestEventGroupDataCallback& Delegate) override;`
- L59 _public prototype_ `virtual void RequestEventGroupData(const FString& ReplayName, const FString& Group, const int32 UserIndex, const FRequestEventGroupDataCallback& Delegate) override;`
- L62 _protected prototype_ `void StartStreamingSaved(const FStartStreamingParameters& Params, const FStartStreamingCallback& Delegate);`
- L63 _protected prototype_ `void DeleteFinishedStreamSaved(const FString& ReplayName, const int32 UserIndex, const FDeleteFinishedStreamCallback& Delegate) const;`
- L64 _protected prototype_ `void KeepReplaySaved(const FString& ReplayName, const bool bKeep, const int32 UserIndex, const FKeepReplayCallback& Result);`
- L65 _protected prototype_ `void RenameReplayFriendlyNameSaved(const FString& ReplayName, const FString& NewFriendlyName, const int32 UserIndex, const FRenameReplayCallback& Delegate) const;`
- L66 _protected prototype_ `void RenameReplaySaved(const FString& ReplayName, const FString& NewName, const int32 UserIndex, const FRenameReplayCallback& Delegate);`
- L67 _protected prototype_ `void EnumerateEventsSaved(const FString& ReplayName, const FString& Group, const int32 UserIndex, const FEnumerateEventsCallback& Delegate) const;`
- L68 _protected prototype_ `void RequestEventDataSaved(const FString& ReplayName, const FString& EventID, const int32 UserIndex, const FRequestEventDataCallback& Delegate);`
- L69 _protected prototype_ `void RequestEventGroupDataSaved(const FString& ReplayName, const FString& Group, const int32 UserIndex, const FRequestEventGroupDataCallback& Delegate);`
- L71 _protected prototype_ `void StartStreaming_Internal(const FStartStreamingParameters& Params, FStartStreamingResult& Result);`
- L72 _protected prototype_ `void DeleteFinishedStream_Internal(const FString& ReplayName, const int32 UserIndex, FDeleteFinishedStreamResult& Result) const;`
- L73 _protected prototype_ `void EnumerateStreams_Internal(const FNetworkReplayVersion& ReplayVersion, const int32 UserIndex, const FString& MetaString, const TArray< FString >& ExtraParms, FEnumerateStreamsResult& Result);`
- L74 _protected prototype_ `void KeepReplay_Internal(const FString& ReplayName, const bool bKeep, const int32 UserIndex, FKeepReplayResult& Result);`
- L75 _protected prototype_ `void RenameReplayFriendlyName_Internal(const FString& ReplayName, const FString& NewFriendlyName, const int32 UserIndex, FRenameReplayResult& Result) const;`
- L76 _protected prototype_ `void EnumerateEvents_Internal(const FString& ReplayName, const FString& Group, const int32 UserIndex, FEnumerateEventsResult& Result) const;`
- L77 _protected prototype_ `void RequestEventData_Internal(const FString& ReplayName, const FString& EventID, const int32 UserIndex, FRequestEventDataResult& Result);`
- L78 _protected prototype_ `void RequestEventGroupData_Internal(const FString& ReplayName, const FString& Group, const int32 UserIndex, FRequestEventGroupDataResult& Result);`
- L108 _protected prototype_ `bool StreamNameToSanitizedNames(const FString& StreamName, FSaveGameSanitizedNames& OutSanitizedNames) const;`
- L109 _protected prototype_ `void ReplayIndexToSanitizedNames(const int32 ReplayIndex, FSaveGameSanitizedNames& OutSanitizedNames) const;`
- L111 _protected prototype_ `bool ReadMetaDataFromLocalStream(FArchive& Archive, FSaveGameMetaData& OutMetaData) const;`
- L112 _protected prototype_ `bool ReadMetaDataFromSaveGame(class ISaveGameSystem& SaveGameSystem, const FSaveGameSanitizedNames& SanitizedNames, const int32 UserIndex, FSaveGameMetaData& OutMetaData, FStreamingResultBase& OutResult) const;`
- L113 _protected prototype_ `void PopulateStreamInfoFromMetaData(const FSaveGameMetaData& MetaData, FNetworkReplayStreamInfo& OutStreamInfo) const;`
- L115 _protected prototype_ `bool SerializeMetaData(FArchive& Archive, FSaveGameMetaData& MetaData) const;`
- L116 _protected prototype_ `bool SerializeVersionedMetaData(FArchive& Archive, FSaveGameMetaData& MetaData) const;`
- L119 _protected prototype_ `bool IsSaveGameFileName(const FString& ReplayName) const;` — Returns whether the input name corresponds to a save game.
- L121 _protected prototype_ `int32 GetReplayIndexFromName(const FString& ReplayName) const;`
- L123 _protected prototype_ `FString GetFullPlaybackName() const;`
- L124 _protected prototype_ `FString GetLocalPlaybackName() const;`
- L126 _protected prototype_ `virtual TArrayView<const FString> GetAdditionalRelativeDemoPaths() const override;`
- L149 _protected function_ `virtual bool GetSaveGameOption(const FSaveGameOptionInfo& OptionInfo, FString& OptionValue) const` — Called during KeepReplay to get options when saving a replay. Note, this may be called off the GameThread and may not be called on every platform. @see FGameDelegates::GetExtendedSaveGameInfoDelegate @param OptionInfo	Info struct that describes the requested option and current streamer status. @param OptionValue	(Out) The desired value for the option. @return True if this event was handled. False if it should be passed to the original delegate (
- L153 _protected member_ `const FString PlaybackReplayName;` — Special replay name that will be used when copying over SaveGame replays for playback.
- L155 _protected prototype_ `static const FString& GetDefaultDemoSavePath();`
- L156 _protected prototype_ `static const FString& GetTempDemoRelativeSavePath();`
- L157 _protected prototype_ `static const FString& GetDefaultPlaybackName();`
- L161 _private prototype_ `TFunction<bool(const TCHAR*, EGameDelegates_SaveGame, FString&)> WrapGetSaveGameOption() const;`
- L165 _private member_ `mutable TWeakPtr<FSaveGameOptionInfo> WeakOptionInfo;` — Although this isn't used on the GameThread, it should only be created / destroyed from the same thread. Therefore, no need to make it thread safe (for now).

#### struct `FSaveGameNetworkReplayStreamer::FSaveGameReplayVersionedInfo`  
`struct FSaveGameReplayVersionedInfo`  
_L80-90_
- L83 _public member_ `uint32 FileVersion;` — Save game file version.
- L86 _public member_ `FReplayEventList Events;` — Events that are serialized in the header.
- L89 _public member_ `TArray<TArray<uint8>> EventData;` — Actual event data. Indices correlate to Event index.

#### struct `FSaveGameNetworkReplayStreamer::FSaveGameMetaData`  
`struct FSaveGameMetaData`  
_L92-99_
- L94 _public member_ `FString ReplayName;`
- L96 _public member_ `FLocalFileReplayInfo ReplayInfo;`
- L98 _public member_ `FSaveGameReplayVersionedInfo VersionedInfo;`

#### struct `FSaveGameNetworkReplayStreamer::FSaveGameSanitizedNames`  
`struct FSaveGameSanitizedNames`  
_L101-106_
- L103 _public member_ `FString ReplayMetaName;`
- L104 _public member_ `FString ReplayName;`
- L105 _public member_ `int32 ReplayIndex;`

#### struct `FSaveGameNetworkReplayStreamer::FSaveGameOptionInfo`  
`struct FSaveGameOptionInfo`  
_L128-137_
- L130 _public member_ `EGameDelegates_SaveGame Option;`
- L131 _public member_ `bool bIsForRename = false;`
- L132 _public member_ `bool bIsSavingMetaData = false;`
- L133 _public member_ `int32 SaveDataSize = INDEX_NONE;`
- L135 _public member_ `FString ReplayFriendlyName;`
- L136 _public member_ `FString ReplaySaveName;`

#### class `FSaveGameNetworkReplayStreamingFactory`  
`class FSaveGameNetworkReplayStreamingFactory : public FLocalFileNetworkReplayStreamingFactory`  
_L170-176_
- inherits: `FLocalFileNetworkReplayStreamingFactory`
- L173 _public prototype_ `virtual void StartupModule() override;`
- L175 _public prototype_ `virtual TSharedPtr<INetworkReplayStreamer> CreateReplayStreamer() override;`
