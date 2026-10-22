# Plugins / GeometryCollectionSequencer

- module root: `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionSequencer`
- headers: 2; symbols: 34
- symbol kinds: class=3, function=2, member=5, prototype=24
- PrivateDependencyModuleNames: AssetTools, Chaos, Core, CoreUObject, EditorFramework, Engine, GeometryCollectionEngine, GeometryCollectionTracks, LevelSequence, MovieScene, MovieSceneTools, MovieSceneTracks, RHI, Sequencer, SequencerCore, Slate, SlateCore, TimeManagement, UnrealEd
- PublicIncludePathModuleNames: Sequencer

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionSequencer/Public/GeometryCollectionSequencerModule.h` (Public)


#### class `FGeometryCollectionSequencerModule`  
`class FGeometryCollectionSequencerModule : public IModuleInterface`  
_L13-37_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L17 _public function_ `virtual void StartupModule() override`
- L25 _public function_ `virtual void ShutdownModule() override`
- L36 _public member_ `FDelegateHandle TrackEditorBindingHandle;`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionSequencer/Public/GeometryCollectionTrackEditor.h` (Public)


#### class `FGeometryCollectionTrackEditor`  
`class FGeometryCollectionTrackEditor : public FMovieSceneTrackEditor`  
_L25-63_
- inherits: `FMovieSceneTrackEditor`
- desc: Tools for Geometry Collection tracks
- L33 _public prototype_ `FGeometryCollectionTrackEditor( TSharedRef<ISequencer> InSequencer );` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L36 _public prototype_ `virtual ~FGeometryCollectionTrackEditor() = default;` — Virtual destructor.
- L44 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer );` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L49 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerTrackEditor interface
- L50 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L51 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface( UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding ) override;`
- L52 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L53 _public prototype_ `virtual bool SupportsType( TSubclassOf<UMovieSceneTrack> Type ) const override;`
- L54 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L55 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L59 _private prototype_ `void BuildGeometryCollectionTrack(FGuid ObjectBinding, UGeometryCollectionComponent *GeometryCollectionComponent, UMovieSceneTrack* Track);`
- L62 _private prototype_ `FKeyPropertyResult AddKeyInternal(FFrameNumber KeyTime, UObject* Object, UGeometryCollectionComponent* GeometryCollectionComponent, UMovieSceneTrack* Track);` — Delegate for AnimatablePropertyChanged in AddKey

#### class `FGeometryCollectionTrackSection`  
`class FGeometryCollectionTrackSection : public ISequencerSection , public TSharedFromThis<FGeometryCollectionTrackSection>`  
_L67-109_
- inherits: `ISequencerSection,TSharedFromThis<FGeometryCollectionTrackSection>`
- desc: Class for animation sections
- L74 _public prototype_ `FGeometryCollectionTrackSection( UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer);` — Constructor.
- L77 _public prototype_ `virtual ~FGeometryCollectionTrackSection() = default;` — Virtual destructor.
- L83 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;`
- L84 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L85 _public prototype_ `virtual float GetSectionHeight() const override;`
- L86 _public prototype_ `virtual int32 OnPaintSection( FSequencerSectionPainter& Painter ) const override;`
- L87 _public prototype_ `virtual void BeginResizeSection() override;`
- L88 _public prototype_ `virtual void ResizeSection(ESequencerSectionResizeMode ResizeMode, FFrameNumber ResizeTime) override;`
- L89 _public prototype_ `virtual void BeginSlipSection() override;`
- L90 _public prototype_ `virtual void SlipSection(FFrameNumber SlipTime) override;`
- L91 _public prototype_ `virtual void BeginDilateSection() override;`
- L92 _public prototype_ `virtual void DilateSection(const TRange<FFrameNumber>& NewRange, float DilationFactor) override;`
- L99 _private member_ `UMovieSceneGeometryCollectionSection& Section;` — The section we are visualizing
- L102 _private member_ `TWeakPtr<ISequencer> Sequencer;` — Used to draw animation frame, need selection state and local time
- L105 _private member_ `FFrameNumber InitialStartOffsetDuringResize;` — Cached start offset value valid only during resize
- L108 _private member_ `FFrameNumber InitialStartTimeDuringResize;` — Cached start time valid only during resize
