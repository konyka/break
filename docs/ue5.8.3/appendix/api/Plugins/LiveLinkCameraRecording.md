# Plugins / LiveLinkCameraRecording

- module root: `Plugins/VirtualProduction/LiveLinkCamera/Source/LiveLinkCameraRecording`
- headers: 4; symbols: 32
- symbol kinds: class=4, function=3, member=4, namespace=2, prototype=19
- PrivateDependencyModuleNames: CameraCalibrationCore, CinematicCamera, Core, CoreUObject, Engine, LevelSequence, LiveLinkCamera, LiveLinkComponents, LiveLinkInterface, LiveLinkMovieScene, LiveLinkSequencer, MovieScene, MovieSceneTools, MovieSceneTracks, Sequencer, Slate, SlateCore, TakeTrackRecorders, UnrealEd

### `Plugins/VirtualProduction/LiveLinkCamera/Source/LiveLinkCameraRecording/Private/LiveLinkCameraControllerTrackEditor.h` (Private)


#### class `FLiveLinkCameraControllerTrackEditor`  
`class FLiveLinkCameraControllerTrackEditor : public FKeyframeTrackEditor<UMovieSceneLiveLinkCameraControllerTrack>`  
_L9-33_
- inherits: `FKeyframeTrackEditor<UMovieSceneLiveLinkCameraControllerTrack>`
- desc: A property track editor for Live Link Camera Controller properties.
- L13 _public function_ `FLiveLinkCameraControllerTrackEditor(TSharedRef<ISequencer> InSequencer) : FKeyframeTrackEditor<UMovieSceneLiveLinkCameraControllerTrack>(InSequencer)`
- L24 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L29 _public prototype_ `virtual FText GetDisplayName() const override;`
- L30 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L31 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`

### `Plugins/VirtualProduction/LiveLinkCamera/Source/LiveLinkCameraRecording/Private/MovieSceneLiveLinkCameraControllerSection.h` (Private)


#### class `UMovieSceneLiveLinkCameraControllerSection`  
`class UMovieSceneLiveLinkCameraControllerSection : public UMovieSceneHookSection`  
_L17-45_
- reflection: `UCLASS()`
- inherits: `UMovieSceneHookSection`
- desc: Movie Scene section for LiveLink Camera Controller properties
- L23 _public function_ `UMovieSceneLiveLinkCameraControllerSection(const FObjectInitializer& ObjectInitializer) : UMovieSceneHookSection(ObjectInitializer)`
- L30 _public prototype_ `void Initialize(ULiveLinkControllerBase* InLiveLinkController);` — Initialize the movie scene section with the LiveLink controller whose properties it will record
- L33 _public prototype_ `virtual void Update(TSharedRef<FSharedPlaybackState> SharedPlaybackState, const UE::MovieScene::FEvaluationHookParams& Params) const override;`
- L39 _public member_ `bool bApplyNodalOffsetFromCachedLensFile = true;` — `UPROPERTY(EditAnywhere, Category="Camera Calibration")` — If true, the Cached Lens File will be evaluated for nodal offset, and that offset will be applied to the transform of the CameraComponent
- L44 _private member_ `TObjectPtr<ULensFile> CachedLensFile = nullptr;` — `UPROPERTY(VisibleAnywhere, Category="Camera Calibration")` — Saved duplicate of the LensFile asset used by the recorded LiveLink Camera Controller at the time of recording

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MovieScene` (scope `UE`)

### `Plugins/VirtualProduction/LiveLinkCamera/Source/LiveLinkCameraRecording/Private/MovieSceneLiveLinkCameraControllerTrack.h` (Private)


#### class `UMovieSceneLiveLinkCameraControllerTrack`  
`class UMovieSceneLiveLinkCameraControllerTrack : public UMovieSceneNameableTrack`  
_L12-38_
- reflection: `UCLASS()`
- inherits: `UMovieSceneNameableTrack`
- desc: Movie Scene track for LiveLink Camera Controller properties
- L18 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L19 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L20 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L21 _public prototype_ `virtual bool IsEmpty() const override;`
- L22 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L23 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L24 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L26 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L27 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L30 _public prototype_ `virtual FText GetDisplayName() const override;`
- L37 _protected member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()` — Array of movie scene sections managed by this track

### `Plugins/VirtualProduction/LiveLinkCamera/Source/LiveLinkCameraRecording/Private/MovieSceneLiveLinkCameraControllerTrackRecorder.h` (Private)


#### class `UMovieSceneLiveLinkCameraControllerTrackRecorder`  
`class UMovieSceneLiveLinkCameraControllerTrackRecorder : public UMovieSceneLiveLinkControllerTrackRecorder`  
_L13-31_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneLiveLinkControllerTrackRecorder`
- desc: Movie Scene track recorder for LiveLink Camera Controller properties
- L19 _public prototype_ `virtual void CreateTrackImpl() override;`
- L20 _public prototype_ `virtual void RecordSampleImpl(const FQualifiedFrameTime& CurrentTime) override;`
- L21 _public function_ `virtual UMovieSceneSection* GetMovieSceneSection() const override`
- L25 _public prototype_ `virtual bool IsLiveLinkControllerSupported(const TSubclassOf<ULiveLinkControllerBase>& ControllerToSupport) const override;`
- L30 _private member_ `TWeakObjectPtr<UMovieSceneLiveLinkCameraControllerSection> MovieSceneSection;` — Section to record to on the track
