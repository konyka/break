# Plugins / MediaCompositingEditor

- module root: `Plugins/Media/MediaCompositing/Source/MediaCompositingEditor`
- headers: 11; symbols: 209
- symbol kinds: class=12, delegate=1, enum=3, enumerator=10, function=17, macro=3, member=49, namespace=6, prototype=105, struct=3
- PrivateDependencyModuleNames: AssetRegistry, ContentBrowser, Core, CoreUObject, DeveloperSettings, EditorFramework, EditorWidgets, Engine, ImageCore, ImgMedia, InputCore, LevelSequence, MediaAssets, MediaCompositing, MediaUtils, MovieScene, MovieSceneTracks, RHI, RenderCore, SequenceRecorder, Sequencer, SequencerCore, Slate, SlateCore, TimeManagement, UnrealEd
- PublicDependencyModuleNames: MovieSceneTools

### `Plugins/Media/MediaCompositing/Source/MediaCompositingEditor/Private/Sequencer/MediaPlayerPropertyTrackEditor.h` (Private)


#### class `FMediaPlayerPropertyTrackEditor`  
`class FMediaPlayerPropertyTrackEditor : public FPropertyTrackEditor<UMovieSceneMediaPlayerPropertyTrack>`  
_L17-51_
- inherits: `FPropertyTrackEditor<UMovieSceneMediaPlayerPropertyTrack>`
- desc: Track editor that understands how to animate MediaPlayer properties on objects
- L22 _public function_ `FMediaPlayerPropertyTrackEditor(TSharedRef<ISequencer> InSequencer) : FPropertyTrackEditor(InSequencer, GetAnimatedPropertyTypes())`
- L26 _public function_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer)`
- L32 _public function_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes()`
- L39 _private prototype_ `virtual FText GetDisplayName() const override;`
- L40 _private prototype_ `virtual UMovieSceneTrack* AddTrack(UMovieScene* FocusedMovieScene, const FGuid& ObjectHandle, TSubclassOf<class UMovieSceneTrack> TrackClass, FName UniqueTypeName) override;`
- L41 _private prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L42 _private prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L43 _private prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L44 _private prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L45 _private prototype_ `virtual void OnAnimatedPropertyChanged(const FPropertyChangedParams& PropertyChangedParams) override;`
- L47 _private function_ `virtual void GenerateKeysFromPropertyChanged(const FPropertyChangedParams&, UMovieSceneSection* SectionToKey, FGeneratedTrackKeys&) override`
- L49 _private prototype_ `void AddNewSection(const FAssetData& AssetData, UMovieSceneMediaPlayerPropertyTrack* MediaTrack);`
- L50 _private prototype_ `void AddNewSectionEnterPressed(const TArray<FAssetData>& AssetData, UMovieSceneMediaPlayerPropertyTrack* Track);`

### `Plugins/Media/MediaCompositing/Source/MediaCompositingEditor/Private/Sequencer/MediaPlayerRecording.h` (Private)


#### enum `EMediaPlayerRecordingNumerationStyle`  
`enum class EMediaPlayerRecordingNumerationStyle : uint8`  
_L17-21_
- reflection: `UENUM()`
- L19 _public enumerator_ `AppendFrameNumber`
- L20 _public enumerator_ `AppendSampleTime`

#### enum `EMediaPlayerRecordingImageFormat`  
`enum class EMediaPlayerRecordingImageFormat : uint8`  
_L24-30_
- reflection: `UENUM()`
- L26 _public enumerator_ `PNG`
- L27 _public enumerator_ `JPEG`
- L28 _public enumerator_ `BMP`
- L29 _public enumerator_ `EXR`

#### struct `FMediaPlayerRecordingSettings`  
`struct FMediaPlayerRecordingSettings`  
_L33-83_
- reflection: `USTRUCT()`
- L37 _public function_ `FMediaPlayerRecordingSettings() : bActive(true) , bRecordMediaFrame(false) , BaseFilename(TEXT("Frame")) , NumerationStyle(EMediaPlayerRecordingNumerationStyle::AppendFrameNumber) , ImageFormat(EMediaPlayerRecordingImageFormat::BMP) , CompressionQuality(0) , bResetAlpha(false)`
- L51 _public member_ `bool bActive;` — `UPROPERTY(EditAnywhere, Category = "MediaPlayer Event Recording")` — Whether this MediaPlayer is active and its event will be recorded when the 'Record' button is pressed.
- L55 _public member_ `bool bRecordMediaFrame;` — `UPROPERTY(EditAnywhere, Category = "MediaPlayer Frame Recording")` — Whether this MediaPlayer is active and the image frame will be recorded when the 'Record' button is pressed.
- L59 _public member_ `FString BaseFilename;` — `UPROPERTY(EditAnywhere, Category = "MediaPlayer Frame Recording", meta = (EditCondition = "bRecordMediaFrame"))` — How to name each frame.
- L63 _public member_ `EMediaPlayerRecordingNumerationStyle NumerationStyle;` — `UPROPERTY(EditAnywhere, Category = "MediaPlayer Frame Recording", meta = (EditCondition = "bRecordMediaFrame"))` — How to numerate the filename.
- L67 _public member_ `EMediaPlayerRecordingImageFormat ImageFormat;` — `UPROPERTY(EditAnywhere, Category = "MediaPlayer Frame Recording", meta = (EditCondition = "bRecordMediaFrame"))` — The image format we wish to record to.
- L75 _public member_ `int32 CompressionQuality;` — `UPROPERTY(EditAnywhere, Category = "MediaPlayer Frame Recording", meta = (EditCondition = "bRecordMediaFrame"))` — An image format specific compression setting. For EXRs, either 0 (Default) or 1 (Uncompressed) For PNGs & JPEGs, 0 (Default) or a value between 1 (worst quality, best compression) and 100 (best quality, worst compression)
- L82 _public member_ `bool bResetAlpha;` — `UPROPERTY(EditAnywhere, Category = "MediaPlayer Frame Recording", meta = (EditCondition = "bRecordMediaFrame"))` — If the format support it, set the alpha to 1 (or 255). @note Removing alpha increase the memory foot print.

#### class `UMediaPlayerRecording`  
`class UMediaPlayerRecording : public USequenceRecordingBase`  
_L86-118_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USequenceRecordingBase`
- L92 _public prototype_ `virtual bool StartRecording(class ULevelSequence* CurrentSequence = nullptr, float CurrentSequenceTime = 0.0f, const FString& BaseAssetPath = FString(), const FString& SessionName = FString()) override;` — UItemRecordingBase override
- L93 _public prototype_ `virtual bool StopRecording(class ULevelSequence* CurrentSequence = nullptr, float CurrentSequenceTime = 0.0f) override;`
- L94 _public prototype_ `virtual void Tick(ULevelSequence* CurrentSequence = nullptr, float CurrentSequenceTime = 0.0f) override;`
- L95 _public prototype_ `virtual bool IsRecording() const override;`
- L96 _public function_ `virtual UObject* GetObjectToRecord() const override`
- L97 _public function_ `virtual bool IsActive() const`
- L98 _public function_ `virtual FString GetRecordingLabel() const`
- L101 _public prototype_ `UMediaPlayer* GetMediaPlayerToRecord() const;` — Get the MediaPlayer to record.
- L104 _public prototype_ `void SetMediaPlayerToRecord(UMediaPlayer* InMediaPlayer);` — Set the MediaPlayer to record
- L109 _public member_ `FMediaPlayerRecordingSettings RecordingSettings;` — `UPROPERTY(EditAnywhere, Category = "MediaPlayer Recording")` — Whether this MediaPlayer is active and its event will be recorded when the 'Record' button is pressed.
- L114 _private member_ `TWeakObjectPtr<UMediaPlayer> MediaPlayerToRecord;` — `UPROPERTY(EditAnywhere, Category = "MediaPlayer Recording")` — The MediaPlayer we want to record
- L117 _private member_ `TArray<TSharedPtr<class IMovieSceneSectionRecorder>> SectionRecorders;` — This MediaPlayer's current set of section recorders

### `Plugins/Media/MediaCompositing/Source/MediaCompositingEditor/Private/Sequencer/MediaSequenceRecorderExtender.h` (Private)


#### class `UMediaSequenceRecorderSettings`  
`class UMediaSequenceRecorderSettings : public UObject`  
_L23-37_
- reflection: `UCLASS(config = Editor)`
- inherits: `UObject`
- L27 _private prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L32 _public member_ `bool bRecordMediaPlayerEnabled;` — `UPROPERTY(Config, EditAnywhere, Category = "MediaPlayer Recording")` — Whether to enabled MediaPlayer recording into this sequence.
- L36 _public member_ `FString MediaPlayerSubDirectory;` — `UPROPERTY(Config, EditAnywhere, Category = "MediaPlayer Recording")` — The name of the subdirectory MediaPlayer will be placed in. Leave this empty to place into the same directory as the sequence base path

#### class `FMediaSequenceRecorderExtender`  
`class FMediaSequenceRecorderExtender : public ISequenceRecorderExtender`  
_L42-68_
- inherits: `ISequenceRecorderExtender`
- desc: Sequence Recorder extender to record media player
- L45 _public prototype_ `FMediaSequenceRecorderExtender();`
- L48 _public prototype_ `virtual TSharedPtr<IDetailsView> MakeSettingDetailsView() override;`
- L49 _public prototype_ `virtual TSharedPtr<SWidget> MakeListWidget(TSharedPtr<SListView<USequenceRecordingBase*>>& OutCreatedListView, FListViewSelectionChanged OnListViewSelectionChanged) override;`
- L50 _public prototype_ `virtual void SetListViewSelection(USequenceRecordingBase* InSelectedBase) override;`
- L51 _public prototype_ `virtual USequenceRecordingBase* AddNewQueueRecording(UObject* SequenceRecordingObjectToRecord) override;`
- L52 _public prototype_ `virtual void BuildQueuedRecordings(const TArray<USequenceRecordingBase*>& InQueuedRecordings) override;`
- L55 _private prototype_ `UMediaPlayerRecording * FindRecording(UMediaPlayer* InMediaPlayer) const;`
- L57 _private prototype_ `TSharedRef<ITableRow> MakeMediaPlayerListViewWidget(USequenceRecordingBase* Recording, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L58 _private prototype_ `void OnMediaPlayerListSelectionChanged(USequenceRecordingBase* Recording, ESelectInfo::Type SelectionType);`
- L59 _private prototype_ `EVisibility GetRecordMediaPlayerVisible() const;`
- L60 _private prototype_ `bool OnRecordingMediaPlayerListAllowDrop(TSharedPtr<FDragDropOperation> DragDropOperation);`
- L61 _private prototype_ `FReply OnRecordingMediaPlayerListDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent);`
- L64 _private member_ `bool bInsideSelectionChanged;`
- L65 _private member_ `FListViewSelectionChanged OnListViewSelectionChanged;`
- L66 _private member_ `TSharedPtr<SListView<USequenceRecordingBase*>> MediaPlayerListView;`
- L67 _private member_ `TArray<USequenceRecordingBase*> QueuedMediaPlayerRecordings;`

### `Plugins/Media/MediaCompositing/Source/MediaCompositingEditor/Private/Sequencer/MediaSequencerFilters.h` (Private)


#### class `UMediaCompositingTrackFilter`  
`class UMediaCompositingTrackFilter : public USequencerTrackFilterExtension`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `USequencerTrackFilterExtension`
- L15 _public prototype_ `virtual void AddTrackFilterExtensions(ISequencerTrackFilters& InFilterInterface , const TSharedRef<FFilterCategory>& InPreferredCategory , TArray<TSharedRef<FSequencerTrackFilter>>& InOutFilterList) const override;`

### `Plugins/Media/MediaCompositing/Source/MediaCompositingEditor/Private/Sequencer/MovieSceneMediaPlayerSectionRecorder.h` (Private)


#### class `FMovieSceneMediaPlayerSectionRecorderFactory`  
`class FMovieSceneMediaPlayerSectionRecorderFactory : public IMovieSceneSectionRecorderFactory`  
_L17-28_
- inherits: `IMovieSceneSectionRecorderFactory`
- L20 _public prototype_ `virtual ~FMovieSceneMediaPlayerSectionRecorderFactory() = default;`
- L22 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override;`
- L24 _public prototype_ `TSharedPtr<class FMovieSceneMediaPlayerSectionRecorder> CreateSectionRecorder(const FMediaPlayerRecordingSettings& Settings, const FString& BasePackageName) const;`
- L27 _private prototype_ `virtual TSharedPtr<IMovieSceneSectionRecorder> CreateSectionRecorder(const FActorRecordingSettings& InActorRecordingSettings) const override;`

#### class `FMovieSceneMediaPlayerSectionRecorder`  
`class FMovieSceneMediaPlayerSectionRecorder : public IMovieSceneSectionRecorder`  
_L30-85_
- inherits: `IMovieSceneSectionRecorder`
- L33 _public prototype_ `FMovieSceneMediaPlayerSectionRecorder(const FMediaPlayerRecordingSettings& Settings, const FString& BasePackageName);`
- L34 _public prototype_ `virtual ~FMovieSceneMediaPlayerSectionRecorder() = default;`
- L36 _public prototype_ `virtual void CreateSection(UObject* InObjectToRecord, class UMovieScene* MovieScene, const FGuid& Guid, float Time) override;`
- L37 _public prototype_ `virtual void FinalizeSection(float CurrentTime) override;`
- L38 _public prototype_ `virtual void Record(float CurrentTime) override;`
- L40 _public function_ `virtual void InvalidateObjectToRecord() override`
- L45 _public function_ `virtual UObject* GetSourceObject() const override`
- L50 _public function_ `UMediaPlayer* GetMediaPlayer() const`
- L53 _private prototype_ `void StartPlayerRecording(float CurrentTime);`
- L54 _private prototype_ `void StopPlayerRecording(float CurrentTime);`
- L58 _private member_ `TWeakObjectPtr<UMediaPlayer> ObjectToRecord;` — Object to record from
- L61 _private member_ `TWeakObjectPtr<UMovieScene> MovieScene;` — MovieScene to record to
- L64 _private member_ `TWeakObjectPtr<UMovieSceneMediaTrack> MovieSceneTrack;` — Track to record to
- L67 _private member_ `TWeakObjectPtr<UMovieSceneMediaSection> MovieSceneSection;` — Section to record to
- L69 _private member_ `FMediaRecorder MediaRecorder;`
- L71 _private member_ `FMediaPlayerRecordingSettings RecordingSettings;`
- L73 _private member_ `FString MediaSourceBasePackageName;`
- L74 _private member_ `float RecordingStartTime;`
- L75 _private member_ `bool bMediaWasPlaying;`
- L84 _private member_ `TArray<FRecordedTrackInfo> RecordedInfos;`

#### struct `FMovieSceneMediaPlayerSectionRecorder::FRecordedTrackInfo`  
`struct FRecordedTrackInfo`  
_L77-83_
- L79 _public member_ `float RecordingStartTime;`
- L80 _public member_ `float RecordingEndTime;`
- L81 _public member_ `FString RecordingFrameFolder;`
- L82 _public member_ `UMediaSource* MediaSource;`

### `Plugins/Media/MediaCompositing/Source/MediaCompositingEditor/Private/Shared/MediaCompositingEditorStyle.h` (Private)


#### class `FMediaCompositingEditorStyle`  
`class FMediaCompositingEditorStyle : public FSlateStyleSet`  
_L9-40_
- inherits: `FSlateStyleSet`
- L15 _public prototype_ `FMediaCompositingEditorStyle();` — Default constructor.
- L18 _public prototype_ `~FMediaCompositingEditorStyle();` — Destructor.
- L22 _public function_ `static FMediaCompositingEditorStyle& Get()`
- L32 _public function_ `static void Destroy()`
- L39 _private member_ `static TOptional<FMediaCompositingEditorStyle> Singleton;`

### `Plugins/Media/MediaCompositing/Source/MediaCompositingEditor/Private/Utils/MediaCompositingEditorSettings.h` (Private)


#### class `UMediaCompositingEditorSettings`  
`class UMediaCompositingEditorSettings : public UDeveloperSettings`  
_L10-17_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings, meta = (DisplayName = "Media Compositing Editor Settings"))`
- inherits: `UDeveloperSettings`
- L16 _public member_ `bool bDisplayMediaTexturePrompt = true;` — `UPROPERTY(EditAnywhere, Config, Category="Media Compositing")`

### `Plugins/Media/MediaCompositing/Source/MediaCompositingEditor/Private/Utils/SMovieSceneMediaSectionMediaTexturePrompt.h` (Private)


#### enum `UE::MediaCompositingEditor::Private::EMovieSceneMediaSectionMediaTexturePromptResponse`  
`enum class EMovieSceneMediaSectionMediaTexturePromptResponse : uint8`  
_L15-21_
- L17 _public enumerator_ `CreateAsset`
- L18 _public enumerator_ `SelectAsset`
- L19 _public enumerator_ `Skip`
- L20 _public enumerator_ `Disable`

#### class `UE::MediaCompositingEditor::Private::SMovieSceneMediaSectionMediaTexturePrompt`  
`class SMovieSceneMediaSectionMediaTexturePrompt : public SCompoundWidget`  
_L23-59_
- inherits: `SCompoundWidget`
- L26 _public function_ `SLATE_BEGIN_ARGS(SMovieSceneMediaSectionMediaTexturePrompt)`
- L28 _public prototype_ `SLATE_END_ARGS() static TSharedRef<SMovieSceneMediaSectionMediaTexturePrompt> PromptUser(TArrayView<TWeakObjectPtr<UMediaTexture>> InUsedTexturesWeak);`
- L32 _public prototype_ `void Construct(const FArguments& InArgs, TArrayView<TWeakObjectPtr<UMediaTexture>> InUsedTexturesWeak);`
- L34 _public prototype_ `EMovieSceneMediaSectionMediaTexturePromptResponse GetResponse() const;`
- L36 _public prototype_ `UMediaTexture* GetMediaTexture() const;`
- L39 _protected member_ `TArrayView<TWeakObjectPtr<UMediaTexture>> UsedTexturesWeak;`
- L40 _protected member_ `TSharedPtr<SWindow> Window;`
- L41 _protected member_ `EMovieSceneMediaSectionMediaTexturePromptResponse Response = EMovieSceneMediaSectionMediaTexturePromptResponse::Skip;`
- L42 _protected member_ `TStrongObjectPtr<UMediaTexture> Texture;`
- L44 _protected prototype_ `FReply OnCreateNewClicked();`
- L46 _protected prototype_ `FReply OnSelectAssetClicked();`
- L48 _protected prototype_ `FReply OnSkipClicked();`
- L50 _protected prototype_ `FReply OnDisableClicked();`
- L52 _protected prototype_ `void RequestClose();`
- L54 _protected prototype_ `void ShowAssetCreator();`
- L56 _protected prototype_ `void ShowAssetPicker();`
- L58 _protected prototype_ `void OnUsedTexturePicked(TWeakObjectPtr<UMediaTexture> InPickedTextureWeak);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MediaCompositingEditor` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::MediaCompositingEditor`)

### `Plugins/Media/MediaCompositing/Source/MediaCompositingEditor/Public/Sequencer/MediaThumbnailSection.h` (Public)


#### class `FMediaThumbnailSection`  
`class FMediaThumbnailSection : public FGCObject , public FThumbnailSection , public ICustomThumbnailClient`  
_L27-167_
- inherits: `FGCObject,FThumbnailSection,ICustomThumbnailClient`
- desc: Implements a thumbnail section for media tracks.
- L41 _public prototype_ `FMediaThumbnailSection(UMovieSceneMediaSection& InSection, TSharedPtr<FTrackEditorThumbnailPool> InThumbnailPool, TSharedPtr<ISequencer> InSequencer);` — Create and initialize a new instance. @param InSection The movie scene section associated with this thumbnail section. @param InThumbnailPool The thumbnail pool to use for drawing media frame thumbnails. @param InSequencer The Sequencer object that owns this section.
- L44 _public prototype_ `virtual ~FMediaThumbnailSection();` — Virtual destructor.
- L50 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L51 _public function_ `virtual FString GetReferencerName() const override`
- L60 _public prototype_ `virtual FMargin GetContentPadding() const override;`
- L61 _public prototype_ `virtual float GetSectionHeight(const UE::Sequencer::FViewDensityInfo& ViewDensity) const override;`
- L62 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L63 _public prototype_ `virtual void SetSingleTime(double GlobalTime) override;`
- L64 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& InPainter) const override;`
- L65 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const FGeometry& ClippedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L69 _public prototype_ `virtual void BeginResizeSection() override;`
- L70 _public prototype_ `virtual void ResizeSection(ESequencerSectionResizeMode ResizeMode, FFrameNumber ResizeTime) override;`
- L71 _public prototype_ `virtual void BeginSlipSection() override;`
- L72 _public prototype_ `virtual void SlipSection(FFrameNumber SlipTime) override;`
- L78 _public prototype_ `virtual void Draw(FTrackEditorThumbnail& TrackEditorThumbnail) override;`
- L79 _public prototype_ `virtual void Setup() override;`
- L89 _protected prototype_ `void DrawFilmBorder(FSequencerSectionPainter& InPainter, FVector2D SectionSize) const;` — Draw the section's film border decoration. @param InPainter The object that paints the geometry. @param SectionSize The size of the section (in local coordinates).
- L97 _protected prototype_ `void DrawLoopIndicators(FSequencerSectionPainter& InPainter, FTimespan MediaDuration, FVector2D SectionSize) const;` — Draw indicators for where the media source is looping. @param InPainter The object that paints the geometry. @param SectionSize The size of the section (in local coordinates).
- L100 _protected prototype_ `void DrawSampleStates(FSequencerSectionPainter& InPainter, FTimespan MediaDuration, FVector2D SectionSize, const TRangeSet<FTimespan>& RangeSet, const FLinearColor& Color) const;` — Draw the caching state of the given media samples.
- L109 _protected prototype_ `void DrawMediaInfo(FSequencerSectionPainter& InPainter, UMediaPlayer* MediaPlayer, FVector2D SectionSize) const;` — Draw the info about the current media. @param InPainter			The object that paints the geometry. @param MediaPlayer		The player to get media info from. @param SectionSize		The size of the section (in local coordinates).
- L114 _protected prototype_ `UMediaSource* GetMediaSource() const;` — Helper function to get the media source.
- L121 _protected prototype_ `UMediaPlayer* GetTemplateMediaPlayer() const;` — Get the media player that is used by the evaluation template. @return The media player, or nullptr if not found.
- L126 _protected prototype_ `void CopyTexture(FSlateTextureRenderTarget2DResource* RenderTarget, FTextureReferenceRHIRef SourceTexture);` — Helper function to copy a texture.
- L130 _private prototype_ `void OnBeginScrubbingEvent();` — Called when sequencer begins scrubbing.
- L133 _private prototype_ `void OnEndScrubbingEvent();` — Called when sequencer ends scrubbing.
- L136 _private prototype_ `void UpdateCachedMediaInfo(const UMediaPlayer* InMediaPlayer);` — Update cached information from the player. (called every tick)
- L139 _private member_ `TWeakObjectPtr<UMovieSceneMediaSection> SectionPtr;` — The section object that owns this section.
- L142 _private member_ `FFrameNumber InitialStartOffsetDuringResize;` — Cached start offset value valid only during resize
- L145 _private member_ `FFrameNumber InitialStartTimeDuringResize;` — Cached start time valid only during resize
- L148 _private member_ `FString PlayerInfoPrefix;` — Cached player info prefix (everything before the FPS clause) to be displayed in the next paint.
- L151 _private member_ `FString PlayerFrameRateText;` — Cached FPS clause for the player info row. Includes the inline " (Sequence: X fps)" suffix when the rates differ.
- L154 _private member_ `bool bFrameRateMismatch = false;` — True when the effective media rate differs from the sequence's display rate (drives yellowing of PlayerFrameRateText).
- L157 _private member_ `bool bDrawSeekPerformanceWarning = false;` — Show the seek performance warning.
- L160 _private member_ `bool bDrawMissingMediaTextureWarning = false;` — Show the "missing media texture" warning.
- L163 _private member_ `FString CachedWarningString;` — Cached Warning string to be displayed in the next paint.
- L166 _private member_ `bool bIsSequencerScrubbing = false;` — True if the sequencer is currently scrubbing.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MEDIACOMPOSITINGEDITOR_API`

### `Plugins/Media/MediaCompositing/Source/MediaCompositingEditor/Public/Sequencer/MediaTrackEditor.h` (Public)


#### class `FMediaTrackEditor`  
`class FMediaTrackEditor : public FMovieSceneTrackEditor`  
_L22-113_
- inherits: `FMovieSceneTrackEditor`
- desc: Track editor that understands how to animate MediaPlayer properties on objects
- L33 _public function_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer)` — Create a new media track editor instance. @param OwningSequencer The sequencer object that will own the track editor. @return The new track editor.
- L43 _public prototype_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes();` — Get the list of all property types that this track editor animates. @return List of animated properties.
- L49 _public member_ `static FOnBuildOutlinerEditWidget OnBuildOutlinerEditWidget;` — Event for when we build the widget for adding to the track. Hook into this if you want to add custom options.
- L58 _public prototype_ `FMediaTrackEditor(TSharedRef<ISequencer> InSequencer);` — Create and initialize a new instance. @param InSequencer The sequencer object that owns this track editor.
- L61 _public prototype_ `virtual ~FMediaTrackEditor();` — Virtual destructor.
- L67 _public prototype_ `virtual FText GetDisplayName() const override;`
- L68 _public prototype_ `virtual UMovieSceneTrack* AddTrack(UMovieScene* FocusedMovieScene, const FGuid& ObjectHandle, TSubclassOf<class UMovieSceneTrack> TrackClass, FName UniqueTypeName) override;`
- L69 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L70 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L71 _public prototype_ `virtual bool HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid) override;`
- L72 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L73 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L74 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> TrackClass) const override;`
- L75 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L76 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L77 _public prototype_ `virtual void OnRelease() override;`
- L82 _protected prototype_ `FKeyPropertyResult AddAttachedMediaSource(FFrameNumber KeyTime, class UMediaSource* MediaSource, TArray<TWeakObjectPtr<UObject>> ObjectsToAttachTo, int32 RowIndex);` — Callback for AnimatablePropertyChanged in HandleAssetAdded for attached media sources.
- L85 _protected prototype_ `FKeyPropertyResult AddMediaSource(FFrameNumber KeyTime, class UMediaSource* MediaSource, int32 RowIndex);` — Callback for AnimatablePropertyChanged in HandleAssetAdded for media sources.
- L87 _protected prototype_ `void AddNewSection(const FAssetData& Asset, UMovieSceneMediaTrack* Track);`
- L89 _protected prototype_ `void AddNewSectionEnterPressed(const TArray<FAssetData>& Asset, UMovieSceneMediaTrack* Track);`
- L91 _protected function_ `TSharedPtr<FTrackEditorThumbnailPool> GetThumbnailPool() const`
- L95 _private prototype_ `void HandleAddMediaTrackMenuEntryExecute();` — Callback for executing the "Add Media Track" menu entry.
- L97 _private prototype_ `void OnSequencerDataChanged(EMovieSceneDataChangeType DataChangeType);` — Callback for when some sequencer data like bindings change.
- L105 _private prototype_ `void UpdateMediaTrackBinding(UMovieSceneMediaTrack* MediaTrack, const FMovieSceneBinding& Binding);` — Updates a media track with the current binding information. @param MediaTrack			Track to update. @param Binding				Binding to get object from.
- L107 _private prototype_ `void OnMediaPlateStateChanged(const TArray<FString>& InActorsPathNames, uint8 InEnumState, bool bInRemoteBroadcast);`
- L111 _private member_ `TSharedPtr<FTrackEditorThumbnailPool> ThumbnailPool;`
- L112 _private member_ `FDelegateHandle OnMediaPlateStateChangedHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MEDIACOMPOSITINGEDITOR_API`
- L17 _delegate_ `DECLARE_EVENT_OneParam(FMediaTrackEditor, FOnBuildOutlinerEditWidget, FMenuBuilder&);`
- L17 _prototype_ `DECLARE_EVENT_OneParam(FMediaTrackEditor, FOnBuildOutlinerEditWidget, FMenuBuilder&);`

### `Plugins/Media/MediaCompositing/Source/MediaCompositingEditor/Public/Utils/MovieSceneMediaSectionHelpers.h` (Public)


#### struct `UE::MediaCompositingEditor::Private::FMovieSceneMediaSectionHelpers`  
`struct FMovieSceneMediaSectionHelpers`  
_L15-25_
- L17 _public prototype_ `static void ShowMediaTexturePrompt(UMovieSceneMediaSection* InMediaSection);`
- L21 _private prototype_ `static void DisablePrompt();` — Disables the prompt for the future.
- L24 _private prototype_ `static void SetMediaTexture(UMovieSceneMediaSection* InSection, UMediaTexture* InTexture);` — Callback to set the media texture on to the section.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MEDIACOMPOSITINGEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MediaCompositingEditor` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::MediaCompositingEditor`)
