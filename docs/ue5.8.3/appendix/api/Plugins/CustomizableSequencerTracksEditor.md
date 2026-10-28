# Plugins / CustomizableSequencerTracksEditor

- module root: `Plugins/MovieScene/CustomizableSequencerTracks/Source/CustomizableSequencerTracksEditor`
- headers: 2; symbols: 18
- symbol kinds: class=2, function=1, member=1, prototype=14
- PrivateDependencyModuleNames: AssetRegistry, Core, CoreUObject, CustomizableSequencerTracks, EditorFramework, MovieScene, Sequencer, SequencerCore, Slate, SlateCore, UnrealEd

### `Plugins/MovieScene/CustomizableSequencerTracks/Source/CustomizableSequencerTracksEditor/Private/CustomizableSequencerTracksStyle.h` (Private)


#### class `FCustomizableSequencerTracksStyle`  
`class FCustomizableSequencerTracksStyle : public FSlateStyleSet`  
_L9-24_
- inherits: `FSlateStyleSet`
- L13 _public member_ `static FName StyleName;`
- L16 _public prototype_ `static FCustomizableSequencerTracksStyle& Get();` — Access the singleton instance for this style set
- L18 _public prototype_ `void RegisterNewTrackType(TSubclassOf<USequencerTrackBP> TrackType);`
- L22 _private prototype_ `FCustomizableSequencerTracksStyle();`
- L23 _private prototype_ `~FCustomizableSequencerTracksStyle();`

### `Plugins/MovieScene/CustomizableSequencerTracks/Source/CustomizableSequencerTracksEditor/Private/SequencerTrackBPEditor.h` (Private)


#### class `FSequencerTrackBPEditor`  
`class FSequencerTrackBPEditor : public FMovieSceneTrackEditor`  
_L16-47_
- inherits: `FMovieSceneTrackEditor`
- desc: A track editor that handles all types of USequencerTrackBP
- L21 _public function_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer)`
- L28 _public prototype_ `FSequencerTrackBPEditor(TSharedRef<ISequencer> InSequencer);`
- L32 _private prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L33 _private prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L34 _private prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L35 _private prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L36 _private prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L40 _private prototype_ `void AddNewTrack(FAssetData AssetData);`
- L42 _private prototype_ `void AddNewObjectBindingTrack(FAssetData AssetData, TArray<FGuid> InObjectBindings);`
- L44 _private prototype_ `void MakeMenuEntry(FMenuBuilder& MenuBuilder, USequencerTrackBP* Track, TSubclassOf<USequencerSectionBP> ClassType);`
- L46 _private prototype_ `void CreateNewSection(USequencerTrackBP* Track, TSubclassOf<USequencerSectionBP> ClassType);`
