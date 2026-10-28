# Plugins / MovieScenePoseSearchTracksEditor

- module root: `Plugins/Experimental/MovieScenePoseSearchTracks/Source/MovieScenePoseSearchTracksEditor`
- headers: 3; symbols: 47
- symbol kinds: class=4, function=4, member=3, namespace=4, prototype=32
- PublicDependencyModuleNames: AnimGraphRuntime, Core, CoreUObject, Engine, MovieScene, MovieSceneAnimMixer, MovieSceneAnimMixerEditor, MovieScenePoseSearchTracks, MovieSceneTools, MovieSceneTracks, PoseSearch, Sequencer, SequencerCore, Slate, SlateCore, UAF, UAFAnimGraph, UAFPoseSearch, UnrealEd

### `Plugins/Experimental/MovieScenePoseSearchTracks/Source/MovieScenePoseSearchTracksEditor/Private/MovieScenePoseSearchTracksEditorModule.h` (Private)


#### class `UE::MovieScene::FMovieScenePoseSearchTracksEditorModule`  
`class FMovieScenePoseSearchTracksEditorModule : public IModuleInterface`  
_L11-18_
- inherits: `IModuleInterface`
- L14 _private prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L15 _private prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `FDelegateHandle StitchAnimationTrackCreateEditorHandle;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MovieScene` (scope `UE`)

### `Plugins/Experimental/MovieScenePoseSearchTracks/Source/MovieScenePoseSearchTracksEditor/Private/MovieScenePoseSearchTracksEditorStyle.h` (Private)


#### class `FMovieScenePoseSearchTracksEditorStyle`  
`class FMovieScenePoseSearchTracksEditorStyle final : public FSlateStyleSet`  
_L10-36_
- inherits: `FSlateStyleSet`
- desc: Style set containing icons for the MovieScenePoseSearchTracks editor.
- L14 _public function_ `FMovieScenePoseSearchTracksEditorStyle() : FSlateStyleSet("MovieScenePoseSearchTracksEditorStyle")`
- L26 _public function_ `~FMovieScenePoseSearchTracksEditorStyle()`
- L31 _public function_ `static FMovieScenePoseSearchTracksEditorStyle& Get()`

### `Plugins/Experimental/MovieScenePoseSearchTracks/Source/MovieScenePoseSearchTracksEditor/Private/TrackEditors/StitchAnimTrackEditor.h` (Private)


#### class `FStitchAnimTrackEditor`  
`class FStitchAnimTrackEditor : public FMovieSceneTrackEditor , public IMovieSceneAnimMixerItemMenuProvider`  
_L33-89_
- inherits: `FMovieSceneTrackEditor,IMovieSceneAnimMixerItemMenuProvider`
- desc: Tools for stitch anim tracks
- L42 _public prototype_ `FStitchAnimTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L45 _public function_ `virtual ~FStitchAnimTrackEditor()` — Virtual destructor.
- L53 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L58 _public prototype_ `virtual void OnInitialize() override;` — ISequencerTrackEditor interface
- L59 _public prototype_ `virtual void OnRelease() override;`
- L60 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L61 _public prototype_ `virtual bool HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid) override;`
- L62 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L63 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L64 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L65 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L66 _public prototype_ `virtual bool OnAllowDrop(const FDragDropEvent& DragDropEvent, FSequencerDragDropParams& DragDropParams) override;`
- L67 _public prototype_ `virtual FReply OnDrop(const FDragDropEvent& DragDropEvent, const FSequencerDragDropParams& DragDropParams) override;`
- L72 _private prototype_ `TSharedRef<SWidget> BuildAddAnimationSubMenu(FGuid ObjectBinding, USkeleton* Skeleton, UE::Sequencer::TWeakViewModelPtr<UE::Sequencer::FViewModel> WeakViewModel, TFunction<void(UMovieSceneSection*)> InSectionCallback = nullptr);` — Animation sub menu
- L73 _private prototype_ `TSharedRef<SWidget> BuildAnimationSubMenu(FGuid ObjectBinding, USkeleton* Skeleton, UMovieSceneTrack* Track, TFunction<void(UMovieSceneSection*)> InSectionCallback = nullptr);`
- L74 _private prototype_ `void AddAnimationSubMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings, USkeleton* Skeleton, UMovieSceneTrack* Track, TFunction<void(UMovieSceneSection*)> InSectionCallback = nullptr);`
- L77 _private prototype_ `void OnAnimationDatabaseAssetSelected(const FAssetData& AssetData, TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track, TFunction<void(UMovieSceneSection*)> InSectionCallback);` — Animation asset selected
- L80 _private prototype_ `void OnAnimationDatabaseAssetEnterPressed(const TArray<FAssetData>& AssetData, TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track, TFunction<void(UMovieSceneSection*)> InSectionCallback);` — Animation asset enter pressed
- L83 _private prototype_ `FKeyPropertyResult AddKeyInternal(FFrameNumber KeyTime, UObject* Object, UPoseSearchDatabase* PoseSearchDatabase, UMovieSceneTrack* Track, int32 RowIndex, TFunction<void(UMovieSceneSection*)> InSectionCallback);` — Delegate for AnimatablePropertyChanged in AddKey
- L86 _private prototype_ `const UClass* GetHandledMixerItemClass() const override;` — IMovieSceneAnimMixerItemMenuProvider interface
- L87 _private prototype_ `void PopulateAddMixerItemMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track, TSharedPtr<ISequencer> Sequencer, int32 RowIndex) override;`
- L88 _private prototype_ `void PopulateObjectBindingAnimationMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass, bool bIsInsideSubmenu) override;`

#### class `FStitchAnimSection`  
`class FStitchAnimSection : public ISequencerSection , public TSharedFromThis<FStitchAnimSection>`  
_L93-123_
- inherits: `ISequencerSection,TSharedFromThis<FStitchAnimSection>`
- desc: Class for stitch anim sections
- L100 _public prototype_ `FStitchAnimSection(UMovieSceneSection& InSection);` — Constructor.
- L103 _public prototype_ `virtual ~FStitchAnimSection();` — Virtual destructor.
- L109 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;`
- L110 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L111 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L112 _public prototype_ `virtual FText GetSectionToolTip() const override;`
- L113 _public prototype_ `virtual float GetSectionHeight(const UE::Sequencer::FViewDensityInfo& ViewDensity) const override;`
- L114 _public prototype_ `virtual FMargin GetContentPadding() const override;`
- L115 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override;`
- L120 _private member_ `UMovieSceneStitchAnimSection& Section;` — The section we are visualizing
- L122 _private member_ `TUniquePtr<FMovieSceneSequenceTransform> InitialDragTransform;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Sequencer` (scope `UE`)
