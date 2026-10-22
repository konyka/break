# Plugins / LensComponentEditor

- module root: `Plugins/VirtualProduction/LensComponent/Source/LensComponentEditor`
- headers: 5; symbols: 61
- symbol kinds: class=6, function=4, macro=2, member=12, prototype=37
- PrivateDependencyModuleNames: CameraCalibrationCore, CameraCalibrationCoreEditor, Core, CoreUObject, Engine, LensComponent, LevelSequence, MovieScene, MovieSceneTools, Sequencer, Slate, SlateCore, TakeTrackRecorders, UnrealEd

### `Plugins/VirtualProduction/LensComponent/Source/LensComponentEditor/Private/LensComponentDetailCustomization.h` (Private)


#### class `FLensComponentDetailCustomization`  
`class FLensComponentDetailCustomization : public IDetailCustomization`  
_L12-40_
- inherits: `IDetailCustomization`
- desc: Customizes a ULensComponent details
- L16 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L21 _public prototype_ `~FLensComponentDetailCustomization();`
- L24 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;`
- L29 _protected prototype_ `void OnLensModelChanged();` — Forces the details panel to refresh when the lens model changes
- L32 _protected prototype_ `void OnLensModelChanged(const TSubclassOf<ULensModel>& LensModel);` — Forces the details panel to refresh when the lens model changes
- L36 _protected member_ `IDetailLayoutBuilder* DetailLayout = nullptr;` — Keep a reference to force refresh the layout
- L39 _protected member_ `TWeakObjectPtr<ULensComponent> WeakLensComponent;` — Weak pointer to the lens component being edited

### `Plugins/VirtualProduction/LensComponent/Source/LensComponentEditor/Private/MovieScene/LensComponentTrackEditor.h` (Private)


#### class `FLensComponentTrackEditor`  
`class FLensComponentTrackEditor : public FKeyframeTrackEditor<UMovieSceneLensComponentTrack>`  
_L9-31_
- inherits: `FKeyframeTrackEditor<UMovieSceneLensComponentTrack>`
- desc: A property track editor for Lens Component
- L13 _public function_ `FLensComponentTrackEditor(TSharedRef<ISequencer> InSequencer) : FKeyframeTrackEditor<UMovieSceneLensComponentTrack>(InSequencer)`
- L23 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L27 _public prototype_ `virtual FText GetDisplayName() const override;`
- L28 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L29 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`

### `Plugins/VirtualProduction/LensComponent/Source/LensComponentEditor/Private/MovieScene/MovieSceneLensComponentTrackRecorder.h` (Private)


#### class `FMovieSceneLensComponentTrackRecorderFactory`  
`class FMovieSceneLensComponentTrackRecorderFactory : public IMovieSceneTrackRecorderFactory`  
_L13-25_
- inherits: `IMovieSceneTrackRecorderFactory`
- desc: MovieScene Track Recorder Factory for a Lens Component
- L17 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override;`
- L18 _public prototype_ `virtual bool CanRecordProperty(class UObject* InObjectToRecord, class FProperty* InPropertyToRecord) const override;`
- L20 _public prototype_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForObject() const override;`
- L21 _public prototype_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForProperty(UObject* InObjectToRecord, const FName& InPropertyToRecord) const override;`
- L23 _public prototype_ `virtual FText GetDisplayName() const override;`

#### class `UMovieSceneLensComponentTrackRecorder`  
`class UMovieSceneLensComponentTrackRecorder : public UMovieSceneTrackRecorder`  
_L29-43_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneTrackRecorder`
- desc: MovieScene Track Recorder for a Lens Component
- L34 _public prototype_ `virtual void CreateTrackImpl() override;`
- L35 _public prototype_ `virtual void RecordSampleImpl(const FQualifiedFrameTime& CurrentTime) override;`
- L36 _public prototype_ `virtual void FinalizeTrackImpl() override;`
- L37 _public function_ `virtual UMovieSceneSection* GetMovieSceneSection() const override`
- L42 _private member_ `TWeakObjectPtr<UMovieSceneLensComponentSection> LensComponentSection;` — Section in which to record Lens Component data

### `Plugins/VirtualProduction/LensComponent/Source/LensComponentEditor/Public/MovieScene/MovieSceneLensComponentSection.h` (Public)


#### class `UMovieSceneLensComponentSection`  
`class UMovieSceneLensComponentSection : public UMovieSceneHookSection`  
_L19-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneHookSection`
- desc: Movie Scene section for Lens Component
- L25 _public function_ `UMovieSceneLensComponentSection(const FObjectInitializer& ObjectInitializer) : UMovieSceneHookSection(ObjectInitializer)`
- L32 _public prototype_ `virtual void Begin(TSharedRef<FSharedPlaybackState> SharedPlaybackState, const UE::MovieScene::FEvaluationHookParams& Params) const override;`
- L33 _public prototype_ `virtual void Update(TSharedRef<FSharedPlaybackState> SharedPlaybackState, const UE::MovieScene::FEvaluationHookParams& Params) const override;`
- L34 _public prototype_ `virtual void End(TSharedRef<FSharedPlaybackState> SharedPlaybackState, const UE::MovieScene::FEvaluationHookParams& Params) const override;`
- L38 _public prototype_ `void Initialize(ULensComponent* Component);` — Initialize the section with the Lens Component whose properties it will record
- L41 _public prototype_ `void Finalize();` — Reduce keys in each of the recorded channels
- L44 _public prototype_ `void RecordFrame(FFrameNumber FrameNumber);` — Record the current value of each distortion state property to its appropriate track
- L47 _public prototype_ `virtual void PostEditImport() override;`
- L48 _public prototype_ `virtual void PostLoad() override;`
- L53 _private prototype_ `void CreateChannelProxy();` — Create the channels in which distortion state values will be recorded
- L56 _private prototype_ `void UpdateChannelProxy();` — Add the distortion state channels to the channel proxy
- L59 _private prototype_ `void AddChannelWithEditor(FMovieSceneChannelProxyData& ChannelProxyData, FMovieSceneFloatChannel& Channel, FText GroupName, FText ChannelName, int32 SortOrder);`
- L65 _public member_ `bool bReapplyNodalOffset = false;` — `UPROPERTY(EditAnywhere, Category = "Camera Calibration")` — If true, then every Update, the nodal offset will be re-evaluated on the lens component
- L69 _public member_ `TObjectPtr<ULensFile> OverrideLensFile = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Camera Calibration")` — LensFile asset that should be used instead of the cached LensFile during playback
- L74 _private member_ `TObjectPtr<ULensFile> CachedLensFile = nullptr;` — `UPROPERTY(VisibleAnywhere, Category="Camera Calibration")` — Saved duplicate of the LensFile asset used by the recorded Lens Component at the time of recording
- L78 _private member_ `TArray<FMovieSceneFloatChannel> DistortionParameterChannels;` — `UPROPERTY()` — Channels to store Distortion Parameter values (will be sized during initialization based on the LensComponent's LensModel)
- L82 _private member_ `TArray<FMovieSceneFloatChannel> FxFyChannels;` — `UPROPERTY()` — Channels to store FxFy values
- L86 _private member_ `TArray<FMovieSceneFloatChannel> ImageCenterChannels;` — `UPROPERTY()` — Channels to store Image Center values
- L90 _private member_ `TSubclassOf<ULensModel> LensModelClass;` — `UPROPERTY()` — The Lens Model used by the recorded LensComponent
- L93 _private member_ `TWeakObjectPtr<ULensComponent> RecordedComponent;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API LENSCOMPONENTEDITOR_API`

### `Plugins/VirtualProduction/LensComponent/Source/LensComponentEditor/Public/MovieScene/MovieSceneLensComponentTrack.h` (Public)


#### class `UMovieSceneLensComponentTrack`  
`class UMovieSceneLensComponentTrack : public UMovieSceneNameableTrack`  
_L13-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- desc: Movie Scene track for Lens Component
- L19 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L20 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L21 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L22 _public prototype_ `virtual bool IsEmpty() const override;`
- L23 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L24 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L25 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L27 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L28 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L31 _public prototype_ `virtual FText GetDisplayName() const override;`
- L38 _protected member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()` — Array of movie scene sections managed by this track

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LENSCOMPONENTEDITOR_API`
