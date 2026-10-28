# Plugins / MediaCompositing

- module root: `Plugins/Media/MediaCompositing/Source/MediaCompositing`
- headers: 9; symbols: 175
- symbol kinds: class=6, function=22, macro=3, member=63, namespace=2, prototype=73, struct=6
- PrivateDependencyModuleNames: Media, MediaAssets, RHI, RenderCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MediaUtils, MovieScene, MovieSceneTracks, TimeManagement

### `Plugins/Media/MediaCompositing/Source/MediaCompositing/Private/MovieScene/MovieSceneMediaPlayerPropertyTemplate.h` (Private)


#### struct `FMovieSceneMediaPlayerPropertySectionTemplate`  
`struct FMovieSceneMediaPlayerPropertySectionTemplate : public FMovieScenePropertySectionTemplate`  
_L15-40_
- reflection: `USTRUCT()`
- inherits: `FMovieScenePropertySectionTemplate`
- L21 _public function_ `FMovieSceneMediaPlayerPropertySectionTemplate() : MediaSource(nullptr), bLoop(false)` — Default constructor.
- L22 _public prototype_ `FMovieSceneMediaPlayerPropertySectionTemplate(const UMovieSceneMediaPlayerPropertySection* InSection, const UMovieSceneMediaPlayerPropertyTrack* InTrack);`
- L26 _public prototype_ `virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`
- L27 _public function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L28 _public function_ `virtual void SetupOverrides() override`
- L33 _private member_ `TObjectPtr<UMediaSource> MediaSource;` — `UPROPERTY()`
- L36 _private member_ `FFrameNumber SectionStartFrame;` — `UPROPERTY()`
- L39 _private member_ `bool bLoop;` — `UPROPERTY()`

### `Plugins/Media/MediaCompositing/Source/MediaCompositing/Private/MovieScene/MovieSceneMediaPlayerStore.h` (Private)


#### struct `FMovieSceneMediaPlayerPriority`  
`struct FMovieSceneMediaPlayerPriority`  
_L15-44_
- desc: Defines a priority for media players used in media sections. The priority is derived from the section's information and used for comparing media players when resolving evaluation conflicts.
- L18 _public member_ `int32 Priority = 0;` — Primary sort priority (hierarchical)
- L20 _public member_ `FFrameNumber SectionStartFrame = FFrameNumber(0);` — Secondary sort temporal priority
- L22 _public function_ `bool operator==(const FMovieSceneMediaPlayerPriority& InOther) const`
- L27 _public function_ `bool operator >(const FMovieSceneMediaPlayerPriority& InOther) const`
- L36 _public function_ `bool operator <(const FMovieSceneMediaPlayerPriority& InOther) const`

#### class `FMovieSceneMediaPlayerStore`  
`class FMovieSceneMediaPlayerStore`  
_L56-123_
- desc: Keep a temporary store of media players so they can be reused after recompiling a media section. During the track evaluation, the expired templates will be torn down first, then the new templates get initialized. The torn down templates will submit their media player in this store associated with the owning media section, so that the new template data (for the media section) can reuse the same player. If players are not reused by the end of the evaluation, it means the media section is not evaluating anymore and the remaining players can be closed and discarded.
- L59 _public prototype_ `FMovieSceneMediaPlayerStore();`
- L60 _public prototype_ `virtual ~FMovieSceneMediaPlayerStore();`
- L70 _public prototype_ `void ScheduleMediaPlayerForRelease(const FObjectKey& InPersistentObjectKey, UMediaPlayer* InMediaPlayer);` — Associate the given media player to the persistent object. If not acquired again with the given persistent object by the end of the frame, it will be closed and discarded. @param InPersistentObjectKey Persistent object (ex section) we want to associate the player with. @param InMediaPlayer Media player to reuse.
- L77 _public prototype_ `UMediaPlayer* TryAcquireMediaPlayer(const FObjectKey& InPersistentObjectKey);` — @brief Get the media player registered to the given persistent object. Remove from pool if found. @param InPersistentObjectKey Persistent object (ex section) the media player is associated with. @return pointer to media player if found, null otherwise.
- L87 _public prototype_ `void SetMediaPlayerPriority(const UMediaPlayer* InMediaPlayer, const FMovieSceneMediaPlayerPriority& InPriority);` — Associate a priority to media players used to play a media section. This priority is used to resolve which player has access to a media texture in case of overlap of multiple media sections with the same media texture. @param InMediaPlayer Media player @param InPriority Priority
- L96 _public prototype_ `TOptional<FMovieSceneMediaPlayerPriority> GetMediaPlayerPriority(const UMediaPlayer* InMediaPlayer) const;` — Retrieve the associated priority for the media player (if it has one). Only players managed by media section data will have a priority associated to them. @param InMediaPlayer Media Player @return Associated priority, if found, for this player.
- L103 _public prototype_ `static void CloseMediaPlayer(UMediaPlayer* InMediaPlayer, bool bInCleanUpBeforeDestroy = true);` — @brief Close the given media player and remove from root. @param InMediaPlayer Input media player, validity is checked. @param bInCleanUpBeforeDestroy Optionally calls CleanUpBeforeDestroy() to ensure player resources a freed immediately.
- L107 _private prototype_ `void OnEndFrame();` — Delegate handler for OnEndFrame. This is used to hook up CloseRemainingPlayers() somewhere after the end of the sequence evaluation.
- L110 _private prototype_ `void OnPreExit();` — Delegate handler for OnPreExit. This is used to hook up CloseRemainingPlayers() before the final GC in case the application exits.
- L113 _private prototype_ `void CloseRemainingPlayers();` — Called after the evaluation is completed to close all non-acquired players.
- L116 _private member_ `TMap<FObjectKey, UMediaPlayer*> MediaPlayers;` — Map of media players.
- L119 _private member_ `TMap<FObjectKey, FMovieSceneMediaPlayerPriority> MediaPlayerPriorities;` — Map of media player priorities used to resolve media texture access.
- L121 _private member_ `FDelegateHandle OnEndFrameDelegateHandle;`
- L122 _private member_ `FDelegateHandle OnPreExitDelegateHandle;`

#### class `FMovieSceneMediaPlayerStoreContainer`  
`class FMovieSceneMediaPlayerStoreContainer : public IPersistentEvaluationData`  
_L130-149_
- inherits: `IPersistentEvaluationData`
- desc: Persistent Evaluation Data Wrapper for the media player association store. Using this pattern to be able to get a shared/weak ptr to the media player store so the media section data, which is also a persistent evaluation data, can keep a weak ptr to solving the order of destruction issue.
- L133 _public prototype_ `FMovieSceneMediaPlayerStoreContainer();`
- L134 _public prototype_ `virtual ~FMovieSceneMediaPlayerStoreContainer() override = default;`
- L139 _public prototype_ `static FMovieSceneMediaPlayerStoreContainer& GetOrAdd(FPersistentEvaluationData& InPersistentData);` — Get the media player data container from the persistent data. Will be created if missing.
- L142 _public function_ `TSharedPtr<FMovieSceneMediaPlayerStore> GetMediaPlayerStore() const` — Get the shared media player store.
- L148 _private member_ `TSharedPtr<FMovieSceneMediaPlayerStore> MediaPlayerStore;`

### `Plugins/Media/MediaCompositing/Source/MediaCompositing/Private/MovieScene/MovieSceneMediaPlayerUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MovieSceneMediaPlayerUtils` (scope `UE`)
- L26 _prototype_ `TRange<FTimespan> AdjustPlaybackTimeRange(const TRange<FTimespan>& InSectionPlaybackRange, UMediaPlayer* InMediaPlayer, const FTimespan& InFrameDuration);` (scope `UE::MovieSceneMediaPlayerUtils`) — Utility function to adjust the playback range of the section according to proper looping logic and what is possible to do with the current player's playback range. In more detail, the current player's playback range must be smaller or equal to the full clip length. This limits us to the case where the section's playback range is also smaller than the full clip. We can't specify a playback range that would be 2.5 times the full clip length for instance. In that case, another method of looping will have to be implemented (ex: using a second player). @param InSectionPlaybackRange Playback range derived from the media section @param InMediaPlayer Player to adjust against @param InFrameDuration Sequencer frame duration, used for tolerance @return
- L33 _prototype_ `void SetPlayerPlaybackTimeRange(UMediaPlayer* InMediaPlayer, const TRange<FTimespan>& InPlaybackRange);` (scope `UE::MovieSceneMediaPlayerUtils`) — Utility function to set the specified playback time range. @param InMediaPlayer Player to use @param InPlaybackRange Specifies the playback range to set. Must be already clamped. If empty, player's full range is restored.
- L38 _prototype_ `FTimespan ClampTimeToPlaybackRange(const FTimespan& InMediaTime, UMediaPlayer* InMediaPlayer, const FMovieSceneMediaPlaybackParams& InPlaybackParams);` (scope `UE::MovieSceneMediaPlayerUtils`) — Ensures that the given time is properly clamped to player's playback range.

### `Plugins/Media/MediaCompositing/Source/MediaCompositing/Private/MovieScene/MovieSceneMediaTemplate.h` (Private)


#### struct `FMovieSceneMediaSectionParams`  
`struct FMovieSceneMediaSectionParams`  
_L21-69_
- reflection: `USTRUCT()`
- L26 _public member_ `TObjectPtr<UMediaSoundComponent> MediaSoundComponent;` — `UPROPERTY()`
- L29 _public member_ `TObjectPtr<UMediaSource> MediaSource;` — `UPROPERTY()`
- L32 _public member_ `FMovieSceneObjectBindingID MediaSourceProxy;` — `UPROPERTY()`
- L35 _public member_ `int32 MediaSourceProxyIndex;` — `UPROPERTY()`
- L38 _public member_ `TObjectPtr<UMediaTexture> MediaTexture;` — `UPROPERTY()`
- L41 _public member_ `TObjectPtr<UMediaPlayer> MediaPlayer;` — `UPROPERTY()`
- L44 _public member_ `FFrameNumber SectionStartFrame;` — `UPROPERTY()`
- L47 _public member_ `FFrameNumber SectionEndFrame;` — `UPROPERTY()`
- L50 _public member_ `bool bLooping;` — `UPROPERTY()`
- L53 _public member_ `FFrameNumber StartFrameOffset;` — `UPROPERTY()`
- L56 _public member_ `FMovieSceneFloatChannel ProxyTextureBlend;` — `UPROPERTY()`
- L59 _public member_ `FMediaSourceCacheSettings CacheSettings;` — `UPROPERTY()`
- L61 _public function_ `FMovieSceneMediaSectionParams() : MediaSoundComponent(nullptr) , MediaSource(nullptr) , MediaSourceProxyIndex(0) , MediaTexture(nullptr) , MediaPlayer(nullptr) , bLooping(false)`

#### struct `FMovieSceneMediaSectionTemplate`  
`struct FMovieSceneMediaSectionTemplate : public FMovieSceneEvalTemplate`  
_L73-106_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneEvalTemplate`
- L79 _public function_ `FMovieSceneMediaSectionTemplate()` — Default constructor.
- L87 _public prototype_ `FMovieSceneMediaSectionTemplate(const UMovieSceneMediaSection& InSection, const UMovieSceneMediaTrack& InTrack);` — Create and initialize a new instance. @param InSection @param InTrack
- L93 _public prototype_ `virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`
- L94 _public prototype_ `virtual UScriptStruct& GetScriptStructImpl() const override;`
- L95 _public prototype_ `virtual void Initialize(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) const override;`
- L96 _public prototype_ `virtual void SetupOverrides() override;`
- L97 _public prototype_ `virtual void TearDown(FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) const override;`
- L102 _private member_ `FMovieSceneMediaSectionParams Params;` — `UPROPERTY()`
- L105 _private member_ `TObjectPtr<const UMovieSceneMediaSection> MediaSection;` — `UPROPERTY()`

### `Plugins/Media/MediaCompositing/Source/MediaCompositing/Public/MovieSceneMediaData.h` (Public)


#### struct `FMovieSceneMediaPlaybackParams`  
`struct FMovieSceneMediaPlaybackParams`  
_L19-37_
- desc: Playback parameters to update the media player.
- L25 _public member_ `bool bIsLooping = false;` — Indicate if player is looping from the corresponding media section parameter. We need to store this here to have it in HandleMediaPlayerEvent.
- L31 _public member_ `TRange<FTimespan> SectionTimeRange;` — If specified, this is the playback time range (in player's time) calculated from the section and sequencer. We need to store this here to have it in HandleMediaPlayerEvent.
- L36 _public member_ `FTimespan FrameDuration;` — Sequencer frame duration used for range tolerance calculations.

#### struct `FMovieSceneMediaData`  
`struct FMovieSceneMediaData : PropertyTemplate::FSectionData`  
_L42-171_
- inherits: `PropertyTemplate::FSectionData`
- desc: Persistent data that's stored for each currently evaluating section.
- L46 _public prototype_ `FMovieSceneMediaData();` — Default constructor.
- L58 _public prototype_ `UMediaPlayer* GetMediaPlayer();` — Get the media player used by this persistent data. @return The currently used media player, if any.
- L63 _public function_ `UObject* GetPlayerProxy()` — Get the optional proxy object used by this persistent data.
- L68 _public function_ `bool IsPlayerProxyStale()` — Returns true if the player proxy object has become stale.
- L73 _public function_ `int32 GetProxyLayerIndex()` — Get the layer index we are using (when using a proxy).
- L78 _public function_ `int32 GetProxyTextureIndex()` — Get the texture index we are using (when using a proxy).
- L85 _public prototype_ `void SeekOnOpen(FTimespan Time);` — Set the time to seek to after opening a media source has finished. @param Time The time to seek to.
- L88 _public prototype_ `void Setup(const TSharedPtr<FMovieSceneMediaPlayerStore>& InMediaPlayerStore, const UObject* InSection, UMediaPlayer* OverrideMediaPlayer, UObject* InPlayerProxy, int32 InProxyLayerIndex, int32 InProxyTextureIndex);` — `UE_DEPRECATED(5.6, "Use new Setup function with the playback parameters")`
- L91 _public prototype_ `void Setup(const TSharedPtr<FMovieSceneMediaPlayerStore>& InMediaPlayerStore, const UObject* InSection, UMediaPlayer* OverrideMediaPlayer, UObject* InPlayerProxy, int32 InProxyLayerIndex, int32 InProxyTextureIndex, const FMovieSceneMediaPlaybackParams& InPlaybackParams);` — Set up this persistent data object.
- L94 _public prototype_ `void UpdatePlayerProxy(UObject* InPlayerProxy);` — Update the player proxy interface object.
- L99 _public prototype_ `void Initialize(bool bIsEvaluating);` — Called from FMovieSceneMediaSectionTemplate::Initialize.
- L104 _public prototype_ `void TearDown();` — Called from FMovieSceneMediaSectionTemplate::TearDown.
- L107 _public prototype_ `TSharedPtr<FMediaTextureSampleQueue> TransferSampleQueue();` — Retrieve the sample queue and release the ownership.
- L110 _public prototype_ `UMediaTexture* GetProxyMediaTexture();` — Get the proxy media texture.
- L115 _public member_ `bool bIsAspectRatioSet;` — Stores if the aspect ratio has been set yet.
- L121 _public member_ `bool bHasBeenExecuted = false;` — Indicate if the section template has been executed already or not. This is used to detect when a evaluation template was rebuilt and has potentially changed.
- L127 _private prototype_ `void StartUsingProxyMediaTexture();` — Does the work needed so we can use our proxy media texture.
- L132 _private prototype_ `void StopUsingProxyMediaTexture();` — Does the work needed when we no longer use our proxy media texture.
- L135 _private prototype_ `void HandleMediaPlayerEvent(EMediaEvent Event);` — Callback for media player events.
- L138 _private member_ `bool bOverrideMediaPlayer;`
- L141 _private member_ `UMediaPlayer* MediaPlayer;` — The media player used by this object.
- L143 _private member_ `TWeakObjectPtr<UObject> PlayerProxy;` — Optional proxy for the media player.
- L145 _private member_ `TWeakObjectPtr<UMediaTexture> ProxyMediaTexture;` — Media texture allocated from the proxy.
- L147 _private member_ `int32 ProxyLayerIndex;` — Layer that this section should reside in.
- L149 _private member_ `int32 ProxyTextureIndex;` — Index of texture allocated from the proxy.
- L158 _private member_ `TSharedPtr<FMediaTextureSampleQueue> SampleQueue;` — Sample queue to be used as video sink for the media player. It is owned by the media section because it must be set in the player prior to entering the playback section, i.e. in preroll. We can't ue the internal media texture sample queue because it is in use by another section during this section's preroll. Each section needs it's sample queue independently of the media texture.
- L161 _private member_ `FTimespan SeekOnOpenTime;` — The time to seek to after the media source is opened.
- L164 _private member_ `TWeakPtr<FMovieSceneMediaPlayerStore> MediaPlayerStoreWeak;` — Pointer to the media player store this section data was setup with. Will be used to return the media player to the store on destruction.
- L167 _private member_ `FObjectKey MediaSection;` — Owning Media Section. Used as persistent identifier for media player data.
- L170 _private member_ `FMovieSceneMediaPlaybackParams PlaybackParams;` — Additional player parameters to set before the first seek.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MEDIACOMPOSITING_API`

### `Plugins/Media/MediaCompositing/Source/MediaCompositing/Public/MovieSceneMediaPlayerPropertySection.h` (Public)


#### class `UMovieSceneMediaPlayerPropertySection`  
`class UMovieSceneMediaPlayerPropertySection : public UMovieSceneSection`  
_L14-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- desc: Implements a movie scene section for media playback on a UMediaPlayer.
- L23 _public member_ `TObjectPtr<UMediaSource> MediaSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Media")` — The source to play with this video track.
- L27 _public member_ `bool bLoop;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Media")` — Whether to loop this video.
- L29 _public prototype_ `UMovieSceneMediaPlayerPropertySection(const FObjectInitializer& ObjectInitializer);`

### `Plugins/Media/MediaCompositing/Source/MediaCompositing/Public/MovieSceneMediaPlayerPropertyTrack.h` (Public)


#### class `UMovieSceneMediaPlayerPropertyTrack`  
`class UMovieSceneMediaPlayerPropertyTrack : public UMovieScenePropertyTrack , public IMovieSceneTrackTemplateProducer`  
_L12-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack,IMovieSceneTrackTemplateProducer`
- L20 _public prototype_ `UMovieSceneMediaPlayerPropertyTrack(const FObjectInitializer& ObjectInitializer);`
- L24 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L25 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L26 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`

### `Plugins/Media/MediaCompositing/Source/MediaCompositing/Public/MovieSceneMediaSection.h` (Public)


#### class `UMovieSceneMediaSection`  
`class UMovieSceneMediaSection : public UMovieSceneSection`  
_L27-204_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- desc: Implements a movie scene section for media playback.
- L38 _public member_ `TObjectPtr<UMediaSource> MediaSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Media")` — The source to play with this video track if MediaSourceProxy is not available.
- L42 _public member_ `int32 MediaSourceProxyIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")` — The index to pass to MediaSourceProxy to get the media source.
- L46 _public member_ `bool bLooping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")` — Should the media player be set to loop? This can be helpful for media formats that can use this information (such as exr sequences) to pre-cache the starting data when nearing the end of playback. Does not cause the media to continue playing after the end of the section is reached.
- L50 _public member_ `FFrameNumber StartFrameOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Media")` — Offset into the source media.
- L54 _public member_ `TObjectPtr<UMediaTexture> MediaTexture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Media", meta = (EditCondition = "!bUseExternalMediaPlayer"))` — The media texture that receives the track's video output.
- L58 _public member_ `TObjectPtr<UMediaSoundComponent> MediaSoundComponent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Media")` — The media sound component that receives the track's audio output.
- L62 _public member_ `bool bUseExternalMediaPlayer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Media", AdvancedDisplay)` — If true, this track will control a previously created media player instead of automatically creating one.
- L66 _public member_ `TObjectPtr<UMediaPlayer> ExternalMediaPlayer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Media", meta = (EditCondition = "bUseExternalMediaPlayer"), AdvancedDisplay)` — The external media player this track should control.
- L70 _public member_ `FMediaSourceCacheSettings CacheSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (EditCondition = "!bHasMediaPlayerProxy", HideEditConditionToggle = true, EditConditionHides), AdvancedDisplay)` — Override the default cache settings. Not used if we have a player proxy as the settings come from the proxy instead.
- L74 _public member_ `int32 TextureIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (EditCondition = "bHasMediaPlayerProxy", HideEditConditionToggle = true, EditConditionHides), AdvancedDisplay)` — If using an object like a MediaPlate, then this determines which texture to use for crossfading purposes.
- L78 _public member_ `bool bManualFrameRateAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Media", meta = (InlineEditConditionToggle), AdvancedDisplay)` — If true, the specified framerate alignment will be used instead of the media's frame rate. Use this in case the automatic media frame rate is inaccurate.
- L82 _public member_ `FFrameRate FrameRateAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (EditCondition = "bManualFrameRateAlignment"), AdvancedDisplay)` — Specify the frame rate for internal presentation frame alignment (i.e. frame duration used for Block On Range calculation).
- L86 _public member_ `bool bHasMediaPlayerProxy;` — `UPROPERTY(Transient)` — True if the object bound to this track has a media player proxy.
- L90 _public member_ `FMovieSceneBoolChannel ChannelCanPlayerBeOpen;` — `UPROPERTY()` — If true then the media player can be open.
- L99 _public prototype_ `UMovieSceneMediaSection(const FObjectInitializer& ObjectInitializer);` — Create and initialize a new instance. @param ObjectInitializer The object initializer.
- L101 _public prototype_ `virtual void PostInitProperties() override;`
- L106 _protected prototype_ `virtual void TrimSection(FQualifiedFrameTime TrimTime, bool bTrimLeft, bool bDeleteKeys) override;`
- L107 _protected prototype_ `virtual UMovieSceneSection* SplitSection(FQualifiedFrameTime SplitTime, bool bDeleteKeys) override;`
- L108 _protected prototype_ `virtual TOptional<FFrameTime> GetOffsetTime() const override;`
- L109 _protected prototype_ `virtual void MigrateFrameTimes(FFrameRate SourceRate, FFrameRate DestinationRate) override;`
- L110 _protected prototype_ `virtual void OnBindingIDsUpdated(const TMap<UE::MovieScene::FFixedObjectBindingID, UE::MovieScene::FFixedObjectBindingID>& OldFixedToNewFixedMap, FMovieSceneSequenceID LocalSequenceID, TSharedRef<UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) override;`
- L111 _protected prototype_ `virtual void GetReferencedBindings(TArray<FGuid>& OutBindings) override;`
- L112 _protected prototype_ `virtual UObject* GetSourceObject() const override;`
- L122 _public prototype_ `UMediaSource* GetMediaSource() const;` — Get this section's video source. @return The media source object. @see SetMediaSource
- L130 _public function_ `void SetMediaSource(UMediaSource* InMediaSource)` — Set this section's video source. @param InMediaSource The media source object to set. @see GetMediaSource
- L138 _public function_ `const FMovieSceneObjectBindingID& GetMediaSourceProxy() const` — Get this section's video source proxy.
- L149 _public function_ `void SetMediaSourceProxy(const FMovieSceneObjectBindingID& InObjectBinding, int32 InIndex)` — Set this section's video source proxy. @param InObjectBinding		The object this binds to should implement IMediaPlayerProxyInterface. @param InIndex				Index to pass to IMediaPlayerProxyInterface.
- L162 _public prototype_ `UMediaSource* GetMediaSourceOrProxy(IMovieScenePlayer& Player, FMovieSceneSequenceID SequenceID) const;` — If there is a proxy, get the media source from it. Otherwise return our media source. @param Player				Player used to get the proxy object from the binding. @param SequenceID			ID used to get the proxy object from the binding.
- L170 _public prototype_ `static UMediaSource* GetMediaSourceOrProxy(IMovieScenePlayer& InPlayer, FMovieSceneSequenceID InSequenceID, UMediaSource* InMediaSource, const FMovieSceneObjectBindingID& InMediaSourceProxyBindingID, int32 InMediaSourceProxyIndex);` — Static version of GetMediaSourceOrProxy. @param Player				Player used to get the proxy object from the binding. @param SequenceID			ID used to get the proxy object from the binding.
- L176 _public function_ `float GetThumbnailReferenceOffset() const` — @return The thumbnail reference frame offset from the start of this section
- L182 _public function_ `void SetThumbnailReferenceOffset(float InNewOffset)` — Set the thumbnail reference offset
- L194 _public member_ `float ThumbnailReferenceOffset;` — `UPROPERTY()` — The reference frame offset for single thumbnail rendering
- L202 _private member_ `FMovieSceneObjectBindingID MediaSourceProxyBindingID;` — `UPROPERTY(EditAnywhere, Category = "Section")` — The object to get the source to play from if you don't want to directly specify a media source.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MEDIACOMPOSITING_API`

### `Plugins/Media/MediaCompositing/Source/MediaCompositing/Public/MovieSceneMediaTrack.h` (Public)


#### class `UMovieSceneMediaTrack`  
`class UMovieSceneMediaTrack : public UMovieSceneNameableTrack , public IMovieSceneTrackTemplateProducer`  
_L26-140_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack,IMovieSceneTrackTemplateProducer`
- desc: Implements a movie scene track for media playback.
- L39 _public prototype_ `UMovieSceneMediaTrack(const FObjectInitializer& ObjectInitializer);` — Create and initialize a new instance. @param ObjectInitializer The object initializer.
- L44 _public prototype_ `virtual UMovieSceneSection* AddNewMediaSourceOnRow(UMediaSource& MediaSource, FFrameNumber Time, int32 RowIndex);` — Adds a new media source to the track.
- L46 _public prototype_ `virtual UMovieSceneSection* AddNewMediaSourceProxyOnRow(UMediaSource* MediaSource, const FMovieSceneObjectBindingID& ObjectBinding, int32 MediaSourceProxyIndex, FFrameNumber Time, int32 RowIndex);` — Adds a new media source to the track.
- L49 _public function_ `virtual UMovieSceneSection* AddNewMediaSource(UMediaSource& MediaSource, FFrameNumber Time)` — Adds a new media source on the next available/non-overlapping row.
- L51 _public function_ `virtual UMovieSceneSection* AddNewMediaSourceProxy(UMediaSource* MediaSource, const FMovieSceneObjectBindingID& ObjectBinding, int32 MediaSourceProxyIndex, FFrameNumber Time)` — Adds a new media source on the next available/non-overlapping row.
- L59 _public prototype_ `void TickOutput();` — Called from the media clock.
- L65 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L66 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L67 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L68 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`
- L69 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L70 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L71 _public prototype_ `virtual bool IsEmpty() const override;`
- L72 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L73 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L74 _public function_ `virtual bool SupportsMultipleRows() const override`
- L79 _public prototype_ `virtual void BeginDestroy() override;`
- L81 _public prototype_ `virtual EMovieSceneSectionMovedResult OnSectionMoved(UMovieSceneSection& Section, const FMovieSceneSectionMovedParams& Params);`
- L90 _public member_ `bool bSynchronousScrubbing = false;` — `UPROPERTY(EditAnywhere, Category = "Media Track")` — Force synchronous frame requests *while* manually scrubbing the media track, at the cost of blocking the editor. This can be valuable for always maintaining alignment of media & CG while working.
- L94 _private prototype_ `UMovieSceneMediaSection* AddNewSectionOnRow(FFrameNumber Time, int32 RowIndex);` — Base function to add a new section.
- L98 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> MediaSections;` — `UPROPERTY()` — List of all media sections.
- L103 _private member_ `TArray<TPair<TStrongObjectPtr<UMediaPlayer>, TWeakObjectPtr<UMovieSceneSection>>> NewSections;` — List of players that are we are trying to get durations from for the corresponding sections.
- L105 _private member_ `TSharedPtr<FMovieSceneMediaTrackClockSink, ESPMode::ThreadSafe> ClockSink;` — Our media clock sink.
- L107 _private member_ `bool bGetDurationDelay;` — If true then don't check for the duration this frame.
- L115 _private prototype_ `void UpdateSectionTextureIndices();` — Updates all our sections so they have correct texture indices so the proxy can blend all the sections together correctly.
- L125 _private prototype_ `void StartGetDuration(UMediaSource* MediaSource, UMovieSceneSection* Section);` — Starts the process to get the duration of the media. It might take a frame or more. @param MediaSource		Media to inspect. @param Section			Will set this sequencer section to the length of the media.
- L134 _private prototype_ `bool GetDuration(const TStrongObjectPtr<UMediaPlayer>& MediaPlayer, TWeakObjectPtr<UMovieSceneSection>& NewSection);` — Call this after StartGetDuration to try and get the duration of the media. @param MediaPlayer		Player that is opening the media. @param NewSection		Movie section will be set to the media duration. @return True if it is done and the player can be removed.
- L137 _private function_ `void StartGetDuration(UMediaSource* MediaSource, UMovieSceneSection* Section)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MEDIACOMPOSITING_API`
