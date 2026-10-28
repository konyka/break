# Plugins / CustomizableSequencerTracks

- module root: `Plugins/MovieScene/CustomizableSequencerTracks/Source/CustomizableSequencerTracks`
- headers: 3; symbols: 51
- symbol kinds: class=3, enum=1, enumerator=2, function=14, member=11, prototype=19, struct=1
- PublicDependencyModuleNames: Core, CoreUObject, MovieScene, SlateCore

### `Plugins/MovieScene/CustomizableSequencerTracks/Source/CustomizableSequencerTracks/Public/SequencerSectionBP.h` (Public)


#### class `USequencerSectionBP`  
`class USequencerSectionBP : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L13-26_
- reflection: `UCLASS(Blueprintable, Abstract, DisplayName=SequencerSection)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- L21 _public prototype_ `USequencerSectionBP(const FObjectInitializer& ObjInit);`
- L25 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`

### `Plugins/MovieScene/CustomizableSequencerTracks/Source/CustomizableSequencerTracks/Public/SequencerTrackBP.h` (Public)


#### enum `ECustomSequencerTrackType`  
`enum class ECustomSequencerTrackType`  
_L15-19_
- reflection: `UENUM()`
- L17 _public enumerator_ `RootTrack`
- L18 _public enumerator_ `ObjectTrack`

#### class `USequencerTrackBP`  
`class USequencerTrackBP : public UMovieSceneNameableTrack`  
_L23-76_
- reflection: `UCLASS(Blueprintable, Abstract, DisplayName=SequencerTrack)`
- inherits: `UMovieSceneNameableTrack`
- L31 _public member_ `bool bSupportsMultipleRows;` — `UPROPERTY(Category="Sequencer", EditDefaultsOnly, AssetRegistrySearchable)`
- L34 _public member_ `bool bSupportsBlending;` — `UPROPERTY(Category="Sequencer", EditDefaultsOnly, AssetRegistrySearchable)`
- L37 _public member_ `ECustomSequencerTrackType TrackType;` — `UPROPERTY(Category="Sequencer", EditDefaultsOnly, AssetRegistrySearchable)`
- L40 _public member_ `TObjectPtr<UClass> SupportedObjectType;` — `UPROPERTY(Category="Sequencer", EditDefaultsOnly, AssetRegistrySearchable, meta=(EditCondition="TrackType==ECustomSequencerTrackType::ObjectTrack"))`
- L43 _public member_ `TSubclassOf<USequencerSectionBP> DefaultSectionType;` — `UPROPERTY(Category="Sequencer", EditDefaultsOnly, AssetRegistrySearchable)`
- L46 _public member_ `TArray<TSubclassOf<USequencerSectionBP>> SupportedSections;` — `UPROPERTY(Category="Sequencer", EditDefaultsOnly, AssetRegistrySearchable)`
- L49 _public member_ `TSubclassOf<USequencerTrackInstanceBP> TrackInstanceType;` — `UPROPERTY(Category="Sequencer", EditDefaultsOnly, AssetRegistrySearchable)`
- L52 _public member_ `FSlateBrush Icon;` — `UPROPERTY(Category="Sequencer", EditDefaultsOnly, AssetRegistrySearchable)`
- L56 _public function_ `virtual bool SupportsMultipleRows() const override`
- L57 _public function_ `virtual EMovieSceneTrackEasingSupportFlags SupportsEasing(FMovieSceneSupportsEasingParams& Params) const override`
- L58 _public function_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override`
- L59 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L61 _public function_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override`
- L62 _public function_ `virtual void AddSection(UMovieSceneSection& Section) override`
- L63 _public function_ `virtual void RemoveSection(UMovieSceneSection& Section) override`
- L64 _public function_ `virtual void RemoveSectionAt(int32 SectionIndex) override`
- L65 _public function_ `virtual bool HasSection(const UMovieSceneSection& Section) const override`
- L66 _public function_ `virtual bool IsEmpty() const override`
- L68 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L70 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L75 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY(Instanced)`

### `Plugins/MovieScene/CustomizableSequencerTracks/Source/CustomizableSequencerTracks/Public/SequencerTrackInstanceBP.h` (Public)


#### struct `FSequencerTrackInstanceInput`  
`struct FSequencerTrackInstanceInput`  
_L13-26_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public function_ `FSequencerTrackInstanceInput() : Section(nullptr) , Context(FMovieSceneEvaluationRange(0, FFrameRate()))`
- L23 _public member_ `TObjectPtr<USequencerSectionBP> Section;` — `UPROPERTY(Category="Sequencer", BlueprintReadOnly)`
- L25 _public member_ `FMovieSceneContext Context;`

#### class `USequencerTrackInstanceBP`  
`class USequencerTrackInstanceBP : public UMovieSceneTrackInstance`  
_L30-89_
- reflection: `UCLASS(Blueprintable, Abstract, DisplayName=SequencerTrackInstance)`
- inherits: `UMovieSceneTrackInstance`
- L40 _public prototype_ `void K2_OnInitialize();` — `UFUNCTION(Category="Sequencer", DisplayName="OnInitialize", BlueprintImplementableEvent, meta=(CallInEditor=true))`
- L43 _public prototype_ `void K2_OnUpdate();` — `UFUNCTION(Category="Sequencer", DisplayName="OnUpdate", BlueprintImplementableEvent, meta=(CallInEditor=true))`
- L46 _public prototype_ `void K2_OnBeginUpdateInputs();` — `UFUNCTION(Category="Sequencer", DisplayName="OnBeginUpdateInputs", BlueprintImplementableEvent, meta=(CallInEditor=true))`
- L49 _public prototype_ `void K2_OnInputAdded(FSequencerTrackInstanceInput Input);` — `UFUNCTION(Category="Sequencer", DisplayName="OnInputAdded", BlueprintImplementableEvent, meta=(CallInEditor=true))`
- L52 _public prototype_ `void K2_OnInputRemoved(FSequencerTrackInstanceInput Input);` — `UFUNCTION(Category="Sequencer", DisplayName="OnInputRemoved", BlueprintImplementableEvent, meta=(CallInEditor=true))`
- L55 _public prototype_ `void K2_OnEndUpdateInputs();` — `UFUNCTION(Category="Sequencer", DisplayName="OnEndUpdateInputs", BlueprintImplementableEvent, meta=(CallInEditor=true))`
- L58 _public prototype_ `void K2_OnDestroyed();` — `UFUNCTION(Category="Sequencer", DisplayName="OnDestroyed", BlueprintImplementableEvent, meta=(CallInEditor=true))`
- L63 _public prototype_ `UObject* GetAnimatedObject() const;` — `UFUNCTION(Category="Sequencer", BlueprintCallable)`
- L66 _public prototype_ `TArray<FSequencerTrackInstanceInput> GetInputs() const;` — `UFUNCTION(Category="Sequencer", BlueprintCallable)`
- L69 _public prototype_ `int32 GetNumInputs() const;` — `UFUNCTION(Category="Sequencer", BlueprintCallable)`
- L72 _public prototype_ `FSequencerTrackInstanceInput GetInput(int32 Index) const;` — `UFUNCTION(Category="Sequencer", BlueprintCallable, BlueprintPure=false)`
- L76 _private function_ `virtual void OnInitialize() override`
- L78 _private function_ `virtual void OnAnimate() override`
- L80 _private function_ `virtual void OnBeginUpdateInputs() override`
- L82 _private prototype_ `virtual void OnInputAdded(const FMovieSceneTrackInstanceInput& InInput) override;`
- L84 _private prototype_ `virtual void OnInputRemoved(const FMovieSceneTrackInstanceInput& InInput) override;`
- L86 _private function_ `virtual void OnEndUpdateInputs() override`
- L88 _private prototype_ `virtual void OnDestroyed() override;`
