# Plugins / ReplayTracksEditor

- module root: `Plugins/MovieScene/ReplayTracks/Source/ReplayTracksEditor`
- headers: 2; symbols: 37
- symbol kinds: class=4, function=1, member=3, prototype=29
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, MovieScene, MovieSceneTools, MovieSceneTracks, ReplayTracks, Sequencer, Slate, SlateCore, TimeManagement, UnrealEd

### `Plugins/MovieScene/ReplayTracks/Source/ReplayTracksEditor/Private/ReplayTracksEditorModule.h` (Private)


#### class `UReplayTracksCameraModifier`  
`class UReplayTracksCameraModifier : public UCameraModifier`  
_L14-27_
- reflection: `UCLASS()`
- inherits: `UCameraModifier`
- desc: Camera modifier that lets us set the correct FOV and post-process settings on the spectator pawn when we want to lock into a camera.
- L19 _public prototype_ `void SetLockedActor(AActor* InLockedActor);`
- L22 _protected prototype_ `virtual void ModifyCamera(float DeltaTime, FVector ViewLocation, FRotator ViewRotation, float FOV, FVector& NewViewLocation, FRotator& NewViewRotation, float& NewFOV) override;`
- L23 _protected prototype_ `virtual void ModifyPostProcess(float DeltaTime, float& PostProcessBlendWeight, FPostProcessSettings& PostProcessSettings) override;`
- L26 _private member_ `TWeakObjectPtr<AActor> LockedActor;`

#### class `IReplayTracksEditorModule`  
`class IReplayTracksEditorModule : public IModuleInterface`  
_L32-36_
- inherits: `IModuleInterface`
- desc: The interface for the replay tracks module.
- L35 _public prototype_ `virtual void SetLockedActor(UWorld* World, AActor* LockedActor) = 0;`

### `Plugins/MovieScene/ReplayTracks/Source/ReplayTracksEditor/Private/TrackEditors/ReplayTrackEditor.h` (Private)


#### class `FReplayTrackEditor`  
`class FReplayTrackEditor : public FMovieSceneTrackEditor`  
_L13-58_
- inherits: `FMovieSceneTrackEditor`
- L16 _public prototype_ `FReplayTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L18 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);`
- L22 _public prototype_ `TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;` — ISequencerTrackEditor interface
- L23 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L24 _public prototype_ `virtual bool SupportsType(TSubclassOf<class UMovieSceneTrack> TrackClass) const override;`
- L25 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L27 _public prototype_ `virtual void OnInitialize() override;`
- L28 _public prototype_ `virtual void OnRelease() override;`
- L30 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L33 _private prototype_ `bool HandleAddReplayTrackMenuEntryCanExecute() const;`
- L34 _private prototype_ `void HandleAddReplayTrackMenuEntryExecute();`
- L36 _private prototype_ `UMovieSceneReplayTrack* FindOrCreateReplayTrack(bool* bWasCreated = nullptr);`
- L38 _private prototype_ `TSharedRef<SWidget> HandleAddReplayTrackComboButtonGetMenuContent();`
- L39 _private prototype_ `FText HandleGetToggleReplayButtonContent() const;`
- L40 _private prototype_ `FSlateColor HandleGetToggleReplayButtonColor() const;`
- L41 _private prototype_ `bool HandleToggleReplayButtonIsEnabled() const;`
- L42 _private prototype_ `FText HandleToggleReplayButtonToolTipText() const;`
- L43 _private prototype_ `FReply HandleToggleReplayButtonClicked();`
- L45 _private prototype_ `FKeyPropertyResult AddKeyInternal(FFrameNumber AutoKeyTime);`
- L47 _private prototype_ `void OnGlobalTimeChanged();`
- L49 _private prototype_ `UWorld* GetPIEPlaybackWorld() const;`
- L50 _private prototype_ `AActor* GetPIEViewportLockedActor();`
- L51 _private prototype_ `void MoveLockedActorsToPIEViewTarget(UWorld* PlaybackWorld);`
- L52 _private prototype_ `void MovePIEViewTargetToLockedActor(UWorld* PlaybackWorld);`
- L55 _private member_ `TWeakObjectPtr<AActor> LastLockedActor;`
- L57 _private member_ `FDelegateHandle GlobalTimeChangedHandle;`

#### class `FReplaySection`  
`class FReplaySection : public FSequencerSection , public TSharedFromThis<FReplaySection>`  
_L60-67_
- inherits: `FSequencerSection,TSharedFromThis<FReplaySection>`
- L65 _public prototype_ `FReplaySection(TSharedPtr<ISequencer> InSequencer, UMovieSceneReplaySection& InSection);`
- L66 _public function_ `virtual ~FReplaySection()`
