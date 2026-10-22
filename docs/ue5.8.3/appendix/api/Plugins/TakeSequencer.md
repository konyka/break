# Plugins / TakeSequencer

- module root: `Plugins/VirtualProduction/Takes/Source/TakeSequencer`
- headers: 2; symbols: 24
- symbol kinds: class=3, function=5, member=2, prototype=14
- PrivateDependencyModuleNames: Core, CoreUObject, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Engine, MovieScene, MovieSceneTools, MovieSceneTracks, Sequencer, TakeMovieScene

### `Plugins/VirtualProduction/Takes/Source/TakeSequencer/Private/TakeTrackEditor.h` (Private)


#### class `FTakeTrackEditor`  
`class FTakeTrackEditor : public FMovieSceneTrackEditor, public IMovieSceneToolsTrackImporter`  
_L16-56_
- inherits: `FMovieSceneTrackEditor,IMovieSceneToolsTrackImporter`
- L25 _public function_ `FTakeTrackEditor( TSharedRef<ISequencer> InSequencer ) : FMovieSceneTrackEditor( InSequencer)` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L31 _public function_ `virtual ~FTakeTrackEditor()`
- L42 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer );` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L48 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerTrackEditor interface
- L49 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface( UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding ) override;`
- L50 _public prototype_ `virtual bool SupportsType( TSubclassOf<UMovieSceneTrack> Type ) const override;`
- L51 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L54 _public prototype_ `virtual bool ImportAnimatedProperty(const FString& InPropertyName, const FRichCurve& InCurve, FGuid InBinding, UMovieScene* InMovieScene) override;` — IMovieSceneToolsTrackImporter
- L55 _public prototype_ `virtual bool ImportStringProperty(const FString& InPropertyName, const FString& InStringValue, FGuid InBinding, UMovieScene* InMovieScene) override;`

#### class `FTakeSection`  
`class FTakeSection : public ISequencerSection , public TSharedFromThis<FTakeSection>`  
_L60-84_
- inherits: `ISequencerSection,TSharedFromThis<FTakeSection>`
- desc: Class for take sections
- L67 _public prototype_ `FTakeSection( UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer);` — Constructor.
- L70 _public prototype_ `virtual ~FTakeSection() = default;` — Virtual destructor.
- L76 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;`
- L77 _public prototype_ `virtual FText GetSectionToolTip() const override;`
- L78 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter&) const override;`
- L83 _private member_ `UMovieSceneTakeSection& Section;` — The section we are visualizing

### `Plugins/VirtualProduction/Takes/Source/TakeSequencer/Public/TakeSequencerModule.h` (Public)


#### class `FTakeSequencerModule`  
`class FTakeSequencerModule : public IModuleInterface`  
_L12-42_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L15 _public function_ `FTakeSequencerModule()`
- L17 _public prototype_ `virtual void StartupModule();`
- L18 _public prototype_ `virtual void ShutdownModule();`
- L26 _public function_ `static inline FTakeSequencerModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L36 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L41 _private member_ `FDelegateHandle TakeTrackEditorHandle;`
