# Plugins / MetaHumanSequencer

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSequencer`
- headers: 11; symbols: 119
- symbol kinds: class=10, delegate=1, enum=1, enumerator=1, function=12, macro=7, member=15, namespace=1, prototype=68, struct=2, typedef=1
- PrivateDependencyModuleNames: ControlRig, CoreUObject, GeometryCore, ImgMedia, MediaAssets, MediaCompositingEditor, MetaHumanCaptureData, MetaHumanCore, ModelingOperators, Persona, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: CaptureDataCore, Core, Engine, MediaCompositing, MovieScene, MovieSceneTools, MovieSceneTracks, Sequencer

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSequencer/Public/MetaHumanAudioSection.h` (Public)


#### class `FMetaHumanAudioSection`  
`class FMetaHumanAudioSection : public FAudioSection`  
_L7-16_
- inherits: `FAudioSection`
- L11 _public prototype_ `FMetaHumanAudioSection(UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer);`
- L14 _public prototype_ `virtual bool SectionIsResizable() const;` — ISequencerSectionInterface
- L15 _public prototype_ `virtual bool IsReadOnly() const;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSequencer/Public/MetaHumanAudioTrack.h` (Public)


#### class `UMetaHumanAudioTrack`  
`class UMetaHumanAudioTrack : public UMovieSceneAudioTrack`  
_L13-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneAudioTrack`
- desc: Implements a UMovieSceneAudioTrack customized for the MetaHuman Plugin
- L20 _public prototype_ `UMetaHumanAudioTrack(const FObjectInitializer& InObjectInitializer);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSequencer/Public/MetaHumanAudioTrackEditor.h` (Public)


#### class `FMetaHumanAudioTrackEditor`  
`class FMetaHumanAudioTrackEditor : public FAudioTrackEditor`  
_L8-39_
- inherits: `FAudioTrackEditor`
- L16 _public function_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InOwningSequencer)` — Create a new track editor instance. This is called by ISequencerModule::RegisterPropertyTrackEditor when registering this editor
- L25 _public function_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes()` — Retrieve a list of all property types that this track editor animates, which in the case of this track editor it is just an empty list
- L30 _public prototype_ `FMetaHumanAudioTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L33 _public prototype_ `virtual bool SupportsSequence(class UMovieSceneSequence* InSequence) const override;` — ISequencerTrackEditor interface
- L34 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> TrackClass) const override;`
- L35 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L36 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L37 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L38 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSequencer/Public/MetaHumanMediaSection.h` (Public)


#### class `FMetaHumanMediaSection`  
`class FMetaHumanMediaSection : public FMediaThumbnailSection`  
_L18-34_
- inherits: `FMediaThumbnailSection`
- desc: Extends FMediaThumbnailSection to allow painting on top of the sequencer section
- L22 _public prototype_ `FMetaHumanMediaSection(UMovieSceneMediaSection& InSection, TSharedPtr<class FTrackEditorThumbnailPool> InThumbnailPool, TSharedPtr<class ISequencer> InSequencer);`
- L25 _public prototype_ `virtual bool IsReadOnly() const override;`
- L26 _public prototype_ `virtual bool SectionIsResizable() const override;`
- L27 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& InPainter) const override;`
- L28 _public prototype_ `virtual float GetSectionHeight(const UE::Sequencer::FViewDensityInfo& InViewDensity) const override;`
- L29 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L33 _private member_ `FMetaHumanMovieSceneChannel* KeyContainer = nullptr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANSEQUENCER_API`
- L39 _namespace_ `namespace MetaHumanSectionPainterHelper`
- L41 _prototype_ `int32 PaintExcludedFrames(FSequencerSectionPainter& InPainter, int32 InLayerId, ISequencer* InSequencer, UMovieSceneSection* InSection);` (scope `MetaHumanSectionPainterHelper`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSequencer/Public/MetaHumanMediaTrackEditor.h` (Public)


#### class `FMetaHumanMediaTrackEditor`  
`class FMetaHumanMediaTrackEditor : public FMediaTrackEditor`  
_L14-38_
- inherits: `FMediaTrackEditor`
- desc: MediaTrackEditor that can be added to MetaHumanSequences This can be used to customize the behavior of the sequencer track editor Right now this relies on the functionality available in FMediaTrackEditor
- L23 _public function_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InOwningSequencer)` — Create a new track editor instance. This is called by ISequencerModule::RegisterPropertyTrackEditor when registering this editor
- L28 _public prototype_ `FMetaHumanMediaTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L31 _public prototype_ `virtual bool SupportsSequence(class UMovieSceneSequence* InSequence) const override;`
- L32 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> TrackClass) const override;`
- L33 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L34 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L35 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L36 _public prototype_ `virtual bool IsResizable(UMovieSceneTrack* InTrack) const override;`
- L37 _public prototype_ `virtual void Resize(float NewSize, UMovieSceneTrack* InTrack) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANSEQUENCER_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSequencer/Public/MetaHumanMovieSceneChannel.h` (Public)


#### struct `FMetaHumanMovieSceneChannel`  
`struct FMetaHumanMovieSceneChannel : public FMovieSceneChannel`  
_L23-147_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneChannel`
- L27 _public function_ `FMetaHumanMovieSceneChannel() : DefaultValue(), bHasDefaultValue(false)`
- L36 _public function_ `virtual inline TMovieSceneChannelData<bool> GetData()` — Access a mutable interface for this channel's data @return An object that is able to manipulate this channel's data
- L46 _public function_ `virtual inline TMovieSceneChannelData<const bool> GetData() const` — Access a constant interface for this channel's data @return An object that is able to interrogate this channel's data
- L54 _public function_ `inline TArrayView<const FFrameNumber> GetTimes() const` — Const access to this channel's times
- L62 _public function_ `inline TArrayView<const bool> GetValues() const` — Const access to this channel's values
- L70 _public function_ `inline bool HasAnyData() const` — Check whether this channel has any data
- L82 _public prototype_ `virtual bool Evaluate(FFrameTime InTime, bool& OutValue) const;` — Evaluate this channel @param InTime     The time to evaluate at @param OutValue   A value to receive the result @return true if the channel was evaluated successfully, false otherwise
- L87 _public prototype_ `virtual void GetKeys(const TRange<FFrameNumber>& WithinRange, TArray<FFrameNumber>* OutKeyTimes, TArray<FKeyHandle>* OutKeyHandles) override;`
- L88 _public prototype_ `virtual void GetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<FFrameNumber> OutKeyTimes) override;`
- L89 _public prototype_ `virtual void SetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<const FFrameNumber> InKeyTimes) override;`
- L90 _public prototype_ `virtual void DuplicateKeys(TArrayView<const FKeyHandle> InHandles, TArrayView<FKeyHandle> OutNewHandles) override;`
- L91 _public prototype_ `virtual void DeleteKeys(TArrayView<const FKeyHandle> InHandles) override;`
- L92 _public prototype_ `virtual void DeleteKeysFrom(FFrameNumber InTime, bool bDeleteKeysBefore) override;`
- L93 _public prototype_ `virtual void RemapTimes(const UE::MovieScene::IRetimingInterface& Retimer) override;`
- L94 _public prototype_ `virtual TRange<FFrameNumber> ComputeEffectiveRange() const override;`
- L95 _public prototype_ `virtual int32 GetNumKeys() const override;`
- L96 _public prototype_ `virtual void Reset() override;`
- L97 _public prototype_ `virtual void Offset(FFrameNumber DeltaPosition) override;`
- L98 _public prototype_ `virtual void Optimize(const FKeyDataOptimizationParams& InParameters) override;`
- L99 _public prototype_ `virtual void ClearDefault() override;`
- L108 _public function_ `inline void SetDefault(bool InDefaultValue)` — Set this channel's default value that should be used when no keys are present @param InDefaultValue The desired default value
- L119 _public function_ `inline TOptional<bool> GetDefault() const` — Get this channel's default value that will be used when no keys are present @return (Optional) The channel's default value
- L127 _public function_ `inline void RemoveDefault()` — Remove this channel's default value causing the channel to have no effect where no keys are present
- L135 _protected member_ `TArray<FFrameNumber> Times;` — `UPROPERTY(meta=(KeyTimes))`
- L138 _protected member_ `bool DefaultValue;` — `UPROPERTY()`
- L141 _protected member_ `bool bHasDefaultValue;` — `UPROPERTY()`
- L144 _protected member_ `TArray<bool> Values;` — `UPROPERTY(meta=(KeyValues))`
- L146 _protected member_ `FMovieSceneKeyHandleMap KeyHandles;`

#### struct `TMovieSceneChannelTraits`  
`template<> struct TMovieSceneChannelTraits<FMetaHumanMovieSceneChannel> : TMovieSceneChannelTraitsBase<FMetaHumanMovieSceneChannel>`  
_L150-155_
- inherits: `TMovieSceneChannelTraitsBase<FMetaHumanMovieSceneChannel>`
- L154 _public typedef_ `typedef TMovieSceneExternalValue<bool> ExtendedEditorDataType;`

#### enum `TMovieSceneChannelTraits::(anonymous)`  
`enum`  
_L152-152_

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API METAHUMANSEQUENCER_API`
- L152 _enumerator_ `enum { SupportsDefaults = false }; typedef TMovieSceneExternalValue<bool> ExtendedEditorDataType;` (scope `TMovieSceneChannelTraits::__anon04719c250103`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSequencer/Public/MetaHumanMovieSceneMediaSection.h` (Public)


#### class `UMetaHumanMovieSceneMediaSection`  
`class UMetaHumanMovieSceneMediaSection : public UMovieSceneMediaSection`  
_L17-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneMediaSection`
- L23 _public prototype_ `UMetaHumanMovieSceneMediaSection(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `FMovieSceneChannelDataKeyAddedEvent& OnKeyAddedEventDelegate();`
- L26 _public prototype_ `FMovieSceneChannelDataKeyDeletedEvent& OnKeyDeletedEventDelegate();`
- L28 _public prototype_ `FMetaHumanMovieSceneChannel& GetMetaHumanChannelRef();`
- L30 _public prototype_ `void AddChannelToMovieSceneSection();`
- L35 _private member_ `FMetaHumanMovieSceneChannel MetaHumanChannel;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANSEQUENCER_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSequencer/Public/MetaHumanMovieSceneMediaTrack.h` (Public)


#### class `UMetaHumanMovieSceneMediaTrack`  
`class UMetaHumanMovieSceneMediaTrack : public UMovieSceneMediaTrack`  
_L15-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneMediaTrack`
- desc: Implements a MovieSceneMediaTrack customized for the MetaHumanPerformance plugin
- L21 _public prototype_ `UMetaHumanMovieSceneMediaTrack(const FObjectInitializer& InObjectInitializer);`
- L24 _public prototype_ `virtual UMovieSceneSection* AddNewMediaSourceOnRow(UMediaSource& MediaSource, FFrameNumber Time, int32 RowIndex) override;`
- L25 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L26 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L35 _public prototype_ `float GetRowHeight() const;` — Get the height of this track's rows
- L40 _public prototype_ `void SetRowHeight(int32 NewRowHeight);` — Set the height of this track's rows
- L44 _private member_ `static constexpr float MinRowHeight = 37.0f;` — The minimum height for resizable media tracks
- L48 _private member_ `float RowHeight;` — `UPROPERTY()` — The height for each row of this track

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANSEQUENCER_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSequencer/Public/MetaHumanSequence.h` (Public)


#### class `UMetaHumanSceneSequence`  
`class UMetaHumanSceneSequence : public UMovieSceneSequence`  
_L17-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSequence`
- desc: Movie scene used by the MetaHuman system
- L22 _public prototype_ `UMetaHumanSceneSequence(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `virtual void BindPossessableObject(const FGuid& ObjectId, UObject& PossessedObject, UObject* Context) override;`
- L26 _public prototype_ `virtual bool CanPossessObject(UObject& Object, UObject* InPlaybackContext) const override;`
- L27 _public prototype_ `virtual void LocateBoundObjects(const FGuid& ObjectId, UObject* Context, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const override;`
- L28 _public prototype_ `virtual UMovieScene* GetMovieScene() const override;`
- L29 _public prototype_ `virtual UObject* GetParentObject(UObject* Object) const override;`
- L30 _public prototype_ `virtual void UnbindPossessableObjects(const FGuid& ObjectId) override;`
- L31 _public prototype_ `virtual void UnbindObjects(const FGuid& ObjectId, const TArray<UObject*>& InObjects, UObject* Context) override;`
- L32 _public prototype_ `virtual void UnbindInvalidObjects(const FGuid& ObjectId, UObject* Context) override;`
- L35 _public prototype_ `virtual FText GetDisplayName() const override;`
- L36 _public prototype_ `virtual ETrackSupport IsTrackSupportedImpl(TSubclassOf<class UMovieSceneTrack> InTrackClass) const override;`
- L37 _public prototype_ `void SetTickRate(class UFootageCaptureData* InFootageCaptureData);`
- L42 _public member_ `TObjectPtr<UMovieScene> MovieScene;` — `UPROPERTY()`
- L45 _public prototype_ `DECLARE_DELEGATE_FourParams(FGetExcludedFrameInfo, FFrameRate& OutSourceRate, FFrameRangeMap& OutExcludedFramesMap, int32& OutMediaStartFrame, TRange<FFrameNumber>& OutProcessingLimit);`
- L47 _public member_ `FGetExcludedFrameInfo GetExcludedFrameInfo;`
- L52 _private member_ `TMap<FGuid, TObjectPtr<UObject>> Bindings;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METAHUMANSEQUENCER_API`
- L45 _delegate_ `DECLARE_DELEGATE_FourParams(FGetExcludedFrameInfo, FFrameRate& OutSourceRate, FFrameRangeMap& OutExcludedFramesMap, int32& OutMediaStartFrame, TRange<FFrameNumber>& OutProcessingLimit);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSequencer/Public/MetaHumanSequencerModule.h` (Public)


#### class `FMetaHumanSequencerModule`  
`class FMetaHumanSequencerModule : public IModuleInterface`  
_L9-20_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _private member_ `FDelegateHandle AudioTrackEditorBindingHandle;`
- L19 _private member_ `FDelegateHandle MediaTrackEditorBindingHandle;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSequencer/Public/MetaHumanSequencerPlaybackContext.h` (Public)


#### class `FMetaHumanSequencerPlaybackContext`  
`class FMetaHumanSequencerPlaybackContext : public TSharedFromThis<FMetaHumanSequencerPlaybackContext>`  
_L10-20_
- inherits: `TSharedFromThis<FMetaHumanSequencerPlaybackContext>`
- L14 _public prototype_ `UObject* GetPlaybackContext() const;`
- L17 _private prototype_ `class UWorld* ComputePlaybackContext() const;`
- L19 _private member_ `mutable TWeakObjectPtr<class UWorld> WeakCurrentContext;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANSEQUENCER_API`
