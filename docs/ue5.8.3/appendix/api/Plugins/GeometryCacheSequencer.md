# Plugins / GeometryCacheSequencer

- module root: `Plugins/Runtime/GeometryCache/Source/GeometryCacheSequencer`
- headers: 2; symbols: 35
- symbol kinds: class=3, function=2, macro=1, member=5, prototype=24
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, GeometryCache, GeometryCacheTracks, LevelSequence, MovieScene, MovieSceneTracks, Sequencer, SequencerCore, Slate, SlateCore, UnrealEd
- PublicIncludePathModuleNames: Sequencer

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheSequencer/Classes/GeometryCacheTrackEditor.h` (Public)


#### class `FGeometryCacheTrackEditor`  
`class FGeometryCacheTrackEditor : public FMovieSceneTrackEditor`  
_L22-60_
- inherits: `FMovieSceneTrackEditor`
- desc: Tools for Geometry Cache tracks
- L30 _public prototype_ `FGeometryCacheTrackEditor( TSharedRef<ISequencer> InSequencer );` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L33 _public prototype_ `virtual ~FGeometryCacheTrackEditor() = default;` — Virtual destructor.
- L41 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer );` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L46 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerTrackEditor interface
- L47 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L48 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface( UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding ) override;`
- L49 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L50 _public prototype_ `virtual bool SupportsType( TSubclassOf<UMovieSceneTrack> Type ) const override;`
- L51 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L52 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L56 _private prototype_ `void BuildGeometryCacheTrack(TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track);`
- L59 _private prototype_ `FKeyPropertyResult AddKeyInternal(FFrameNumber KeyTime, UObject* Object, UGeometryCacheComponent* GeomCacheComp, UMovieSceneTrack* Track);` — Delegate for AnimatablePropertyChanged in AddKey

#### class `FGeometryCacheSection`  
`class FGeometryCacheSection : public ISequencerSection , public TSharedFromThis<FGeometryCacheSection>`  
_L64-105_
- inherits: `ISequencerSection,TSharedFromThis<FGeometryCacheSection>`
- desc: Class for animation sections
- L71 _public prototype_ `FGeometryCacheSection( UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer);` — Constructor.
- L74 _public prototype_ `virtual ~FGeometryCacheSection() = default;` — Virtual destructor.
- L80 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;`
- L81 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L82 _public prototype_ `virtual float GetSectionHeight() const override;`
- L83 _public prototype_ `virtual int32 OnPaintSection( FSequencerSectionPainter& Painter ) const override;`
- L84 _public prototype_ `virtual void BeginResizeSection() override;`
- L85 _public prototype_ `virtual void ResizeSection(ESequencerSectionResizeMode ResizeMode, FFrameNumber ResizeTime) override;`
- L86 _public prototype_ `virtual void BeginSlipSection() override;`
- L87 _public prototype_ `virtual void SlipSection(FFrameNumber SlipTime) override;`
- L88 _public prototype_ `virtual void BeginDilateSection() override;`
- L89 _public prototype_ `virtual void DilateSection(const TRange<FFrameNumber>& NewRange, float DilationFactor) override;`
- L95 _private member_ `UMovieSceneGeometryCacheSection& Section;` — The section we are visualizing
- L98 _private member_ `TWeakPtr<ISequencer> Sequencer;` — Used to draw animation frame, need selection state and local time
- L101 _private member_ `FFrameNumber InitialFirstLoopStartOffsetDuringResize;` — Cached first loop start offset value valid only during resize
- L104 _private member_ `FFrameNumber InitialStartTimeDuringResize;` — Cached start time valid only during resize

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GEOMETRYCACHESEQUENCER_API`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheSequencer/Public/GeometryCacheSequencerModule.h` (Public)


#### class `FGeometryCacheSequencerModule`  
`class FGeometryCacheSequencerModule : public IModuleInterface`  
_L12-37_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L16 _public function_ `virtual void StartupModule() override`
- L25 _public function_ `virtual void ShutdownModule() override`
- L36 _public member_ `FDelegateHandle TrackEditorBindingHandle;`
