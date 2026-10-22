# Plugins / NiagaraSimCachingEditor

- module root: `Plugins/FX/NiagaraSimCaching/Source/NiagaraSimCachingEditor`
- headers: 4; symbols: 78
- symbol kinds: class=6, delegate=1, function=5, macro=1, member=18, prototype=47

### `Plugins/FX/NiagaraSimCaching/Source/NiagaraSimCachingEditor/Private/Niagara/NiagaraSimCachingEditorStyle.h` (Private)


#### class `FNiagaraSimCachingEditorStyle`  
`class FNiagaraSimCachingEditorStyle : public FSlateStyleSet`  
_L10-23_
- inherits: `FSlateStyleSet`
- desc: Slate style set that defines all the styles for the take recorder UI
- L14 _public member_ `static FName StyleName;`
- L17 _public prototype_ `static FNiagaraSimCachingEditorStyle& Get();` — Access the singleton instance for this style set
- L21 _private prototype_ `FNiagaraSimCachingEditorStyle();`

### `Plugins/FX/NiagaraSimCaching/Source/NiagaraSimCachingEditor/Public/Niagara/NiagaraSimCachingEditorPlugin.h` (Public)


#### class `INiagaraSimCachingEditorPlugin`  
`class INiagaraSimCachingEditorPlugin : public IModuleInterface`  
_L22-53_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _private member_ `TArray<IConsoleObject*> EditorCommands;`
- L27 _public prototype_ `virtual void StartupModule() override;`
- L28 _public prototype_ `virtual void ShutdownModule() override;`
- L36 _public function_ `static INiagaraSimCachingEditorPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L46 _public function_ `static bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L50 _private member_ `FDelegateHandle TrackEditorBindingHandle;`
- L52 _private member_ `FMovieSceneNiagaraTrackRecorderFactory MovieSceneNiagaraCacheTrackRecorder;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNiagaraSimCachingEditor, Verbose, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNiagaraSimCachingEditor, Verbose, All);`

### `Plugins/FX/NiagaraSimCaching/Source/NiagaraSimCachingEditor/Public/Sequencer/MovieSceneNiagaraTrackRecorder.h` (Public)


#### class `FMovieSceneNiagaraTrackRecorderFactory`  
`class FMovieSceneNiagaraTrackRecorderFactory : public IMovieSceneTrackRecorderFactory`  
_L21-36_
- inherits: `IMovieSceneTrackRecorderFactory`
- L24 _public prototype_ `virtual ~FMovieSceneNiagaraTrackRecorderFactory() = default;`
- L27 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override;`
- L28 _public prototype_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForObject() const override;`
- L29 _public prototype_ `virtual class UMovieSceneTrackRecorder* CreateTrackRecorderForCacheTrack(IMovieSceneCachedTrack* CachedTrack, const TObjectPtr<ULevelSequence>& Sequence, const TSharedPtr<ISequencer>& Sequencer) const override;`
- L32 _public function_ `virtual bool CanRecordProperty(class UObject* InObjectToRecord, class FProperty* InPropertyToRecord) const override` — Particle Systems are entire components and you can't animate them as a property
- L33 _public prototype_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForProperty(UObject* InObjectToRecord, const FName& InPropertyToRecord) const override;`
- L34 _public function_ `virtual FText GetDisplayName() const override`

#### class `UMovieSceneNiagaraTrackRecorder`  
`class UMovieSceneNiagaraTrackRecorder : public UMovieSceneTrackRecorder`  
_L39-81_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieSceneTrackRecorder`
- L45 _public prototype_ `virtual void RecordSampleImpl(const FQualifiedFrameTime& CurrentFrameTime) override;`
- L46 _public prototype_ `virtual void FinalizeTrackImpl() override;`
- L47 _public prototype_ `virtual void SetSectionStartTimecodeImpl(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame) override;`
- L48 _public prototype_ `virtual UMovieSceneSection* GetMovieSceneSection() const override;`
- L49 _public prototype_ `virtual void CreateTrackImpl() override;`
- L50 _public prototype_ `virtual bool ShouldContinueRecording(const FQualifiedFrameTime& FrameTime) const override;`
- L54 _public function_ `TWeakObjectPtr<UMovieSceneNiagaraCacheTrack> GetNiagaraCacheTrack() const` — Returns the Niagara cache track on which the cache manager will be recorded
- L57 _protected prototype_ `void SetRecordingEnabled(bool bEnabled);`
- L58 _protected prototype_ `void OnRecordFrame(float DeltaSeconds);`
- L63 _private member_ `TWeakObjectPtr<UMovieSceneNiagaraCacheTrack> NiagaraCacheTrack;` — The NiagaraCache Track to record onto
- L66 _private member_ `TWeakObjectPtr<UMovieSceneNiagaraCacheSection> NiagaraCacheSection;` — Sections to record to on each track
- L69 _private member_ `TWeakObjectPtr<UNiagaraComponent> SystemToRecord;` — Object to record from
- L71 _private member_ `TOptional<FFrameNumberRange> RecordRange;`
- L73 _private member_ `bool bRecordedFirstFrame = false;`
- L74 _private member_ `bool bRecordingEnabled = false;`
- L75 _private member_ `bool bRequestFinalize = false;`
- L76 _private member_ `FFrameNumber LastRecordedFrame;`
- L77 _private member_ `FFrameNumber RecordingFrameNumber;`
- L78 _private member_ `FDelegateHandle PostEditorTickHandle;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API NIAGARASIMCACHINGEDITOR_API`

### `Plugins/FX/NiagaraSimCaching/Source/NiagaraSimCachingEditor/Public/Sequencer/NiagaraCacheTrackEditor.h` (Public)


#### class `FNiagaraCacheTrackEditor`  
`class FNiagaraCacheTrackEditor : public FMovieSceneTrackEditor`  
_L14-61_
- inherits: `FMovieSceneTrackEditor`
- desc: Editor for Niagara Cache tracks
- L22 _public prototype_ `FNiagaraCacheTrackEditor( TSharedRef<ISequencer> InSequencer );` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L25 _public prototype_ `virtual ~FNiagaraCacheTrackEditor() override = default;` — Virtual destructor.
- L33 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer );` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L38 _public prototype_ `virtual FText GetDisplayName() const override;`
- L39 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L40 _public prototype_ `virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;`
- L41 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L42 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L43 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L44 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerColumnWidget(const FBuildColumnWidgetParams& Params, const FName& ColumnName) override;`
- L45 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L51 _private prototype_ `void BuildNiagaraCacheTrack(TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track);` — Build an internal Niagara cache track
- L54 _private prototype_ `FKeyPropertyResult AddKeyInternal(FFrameNumber KeyTime, class UNiagaraComponent* NiagaraComponent, UMovieSceneTrack* Track);` — Delegate for AnimatablePropertyChanged in AddKey
- L56 _private prototype_ `FReply RecordCacheTrack(IMovieSceneCachedTrack* Track);`
- L58 _private prototype_ `static bool IsCacheTrackOutOfDate(UMovieSceneTrack* Track);`
- L59 _private prototype_ `bool HasConflictingLifecycleTrack(UMovieSceneTrack* Track) const;`
- L60 _private prototype_ `FText GetCacheTrackWarnings(UMovieSceneTrack* Track) const;`

#### class `FNiagaraCacheSection`  
`class FNiagaraCacheSection : public ISequencerSection , public TSharedFromThis<FNiagaraCacheSection>`  
_L64-101_
- inherits: `ISequencerSection,TSharedFromThis<FNiagaraCacheSection>`
- desc: Niagara cache sequencer section
- L71 _public prototype_ `FNiagaraCacheSection( UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer);` — Constructor.
- L74 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;`
- L75 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L76 _public prototype_ `virtual float GetSectionHeight(const UE::Sequencer::FViewDensityInfo& ViewDensity) const override;`
- L77 _public prototype_ `virtual int32 OnPaintSection( FSequencerSectionPainter& Painter ) const override;`
- L78 _public prototype_ `virtual void BeginResizeSection() override;`
- L79 _public prototype_ `virtual void ResizeSection(ESequencerSectionResizeMode ResizeMode, FFrameNumber ResizeTime) override;`
- L80 _public prototype_ `virtual void BeginSlipSection() override;`
- L81 _public prototype_ `virtual void SlipSection(FFrameNumber SlipTime) override;`
- L82 _public prototype_ `virtual void BeginDilateSection() override;`
- L83 _public prototype_ `virtual void DilateSection(const TRange<FFrameNumber>& NewRange, float DilationFactor) override;`
- L88 _private prototype_ `void UpdateSection(FFrameNumber& UpdateTime) const;`
- L91 _private member_ `class UMovieSceneNiagaraCacheSection& Section;` — The section we are visualizing
- L94 _private member_ `TWeakPtr<ISequencer> Sequencer;` — Used to draw animation frame, need selection state and local time
- L97 _private member_ `FFrameNumber InitialFirstLoopStartOffsetDuringResize;` — Cached first loop start offset value valid only during resize
- L100 _private member_ `FFrameNumber InitialStartTimeDuringResize;` — Cached start time valid only during resize
