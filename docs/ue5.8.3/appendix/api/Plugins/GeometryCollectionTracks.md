# Plugins / GeometryCollectionTracks

- module root: `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionTracks`
- headers: 4; symbols: 55
- symbol kinds: class=3, function=9, member=10, prototype=30, struct=3
- DynamicallyLoadedModuleNames: GeometryCollectionSequencer
- PrivateDependencyModuleNames: AnimGraphRuntime, Slate, SlateCore, TimeManagement
- PublicDependencyModuleNames: Chaos, Core, CoreUObject, Engine, GeometryCollectionEngine, MovieScene, MovieSceneTracks
- PublicIncludePathModuleNames: GeometryCollectionSequencer, TargetPlatform

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionTracks/Public/GeometryCollectionTracksModule.h` (Public)


#### class `FGeometryCollectionTracksModule`  
`class FGeometryCollectionTracksModule : public IModuleInterface`  
_L12-41_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L15 _public function_ `FGeometryCollectionTracksModule()`
- L17 _public prototype_ `virtual void StartupModule();`
- L18 _public prototype_ `virtual void ShutdownModule();`
- L26 _public function_ `static inline FGeometryCollectionTracksModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L36 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionTracks/Public/MovieSceneGeometryCollectionSection.h` (Public)


#### struct `FMovieSceneGeometryCollectionParams`  
`struct FMovieSceneGeometryCollectionParams`  
_L15-65_
- reflection: `USTRUCT()`
- L19 _public prototype_ `FMovieSceneGeometryCollectionParams();`
- L20 _public prototype_ `virtual ~FMovieSceneGeometryCollectionParams() = default;`
- L23 _public function_ `float GetDuration() const` — Gets the animation duration, modified by play rate
- L34 _public function_ `float GetSequenceLength() const` — Gets the animation sequence length, not modified by play rate
- L52 _public member_ `FSoftObjectPath GeometryCollectionCache;` — `UPROPERTY(EditAnywhere, Category="GeometryCollection", meta=(AllowedClasses = "/Script/GeometryCollectionEngine.GeometryCollectionCache"))` — The animation this section plays
- L56 _public member_ `FFrameNumber StartFrameOffset;` — `UPROPERTY(EditAnywhere, Category="GeometryCollection")` — The offset into the beginning of the animation clip
- L60 _public member_ `FFrameNumber EndFrameOffset;` — `UPROPERTY(EditAnywhere, Category="GeometryCollection")` — The offset into the end of the animation clip
- L64 _public member_ `float PlayRate;` — `UPROPERTY(EditAnywhere, Category="GeometryCollection")` — The playback rate of the animation clip

#### class `UMovieSceneGeometryCollectionSection`  
`class UMovieSceneGeometryCollectionSection : public UMovieSceneSection`  
_L71-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- desc: Movie scene section that control geometry cache playback
- L79 _public member_ `FMovieSceneGeometryCollectionParams Params;` — `UPROPERTY(EditAnywhere, Category = "Animation", meta=(ShowOnlyInnerProperties))`
- L82 _public prototype_ `virtual float MapTimeToAnimation(FFrameTime InPosition, FFrameRate InTickResolution) const;` — Get Frame Time as Animation Time
- L86 _protected prototype_ `virtual TOptional<TRange<FFrameNumber> > GetAutoSizeRange() const override;`
- L87 _protected prototype_ `virtual void TrimSection(FQualifiedFrameTime TrimTime, bool bTrimLeft, bool bDeleteKeys) override;`
- L88 _protected prototype_ `virtual UMovieSceneSection* SplitSection(FQualifiedFrameTime SplitTime, bool bDeleteKeys) override;`
- L89 _protected prototype_ `virtual void GetSnapTimes(TArray<FFrameNumber>& OutSnapTimes, bool bGetSectionBorders) const override;`
- L90 _protected prototype_ `virtual TOptional<FFrameTime> GetOffsetTime() const override;`
- L91 _protected prototype_ `virtual void MigrateFrameTimes(FFrameRate SourceRate, FFrameRate DestinationRate) override;`
- L92 _protected prototype_ `virtual UObject* GetSourceObject() const override;`
- L100 _private prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L101 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L103 _public member_ `float PreviousPlayRate;`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionTracks/Public/MovieSceneGeometryCollectionTemplate.h` (Public)


#### struct `FMovieSceneGeometryCollectionSectionTemplateParameters`  
`struct FMovieSceneGeometryCollectionSectionTemplateParameters : public FMovieSceneGeometryCollectionParams`  
_L12-30_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneGeometryCollectionParams`
- L16 _public function_ `FMovieSceneGeometryCollectionSectionTemplateParameters()`
- L17 _public function_ `FMovieSceneGeometryCollectionSectionTemplateParameters(const FMovieSceneGeometryCollectionParams& BaseParams, FFrameNumber InSectionStartTime, FFrameNumber InSectionEndTime) : FMovieSceneGeometryCollectionParams(BaseParams) , SectionStartTime(InSectionStartTime) , SectionEndTime(InSectionEndTime)`
- L23 _public prototype_ `float MapTimeToAnimation(FFrameTime InPosition, FFrameRate InTickResolution) const;`
- L26 _public member_ `FFrameNumber SectionStartTime;` — `UPROPERTY()`
- L29 _public member_ `FFrameNumber SectionEndTime;` — `UPROPERTY()`

#### struct `FMovieSceneGeometryCollectionSectionTemplate`  
`struct FMovieSceneGeometryCollectionSectionTemplate : public FMovieSceneEvalTemplate`  
_L33-45_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneEvalTemplate`
- L37 _public function_ `FMovieSceneGeometryCollectionSectionTemplate()`
- L38 _public prototype_ `FMovieSceneGeometryCollectionSectionTemplate(const UMovieSceneGeometryCollectionSection& Section);`
- L40 _public function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L41 _public prototype_ `virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`
- L44 _public member_ `FMovieSceneGeometryCollectionSectionTemplateParameters Params;` — `UPROPERTY()`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionTracks/Public/MovieSceneGeometryCollectionTrack.h` (Public)


#### class `UMovieSceneGeometryCollectionTrack`  
`class UMovieSceneGeometryCollectionTrack : public UMovieSceneNameableTrack , public IMovieSceneTrackTemplateProducer`  
_L17-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack,IMovieSceneTrackTemplateProducer`
- L27 _public prototype_ `virtual UMovieSceneSection* AddNewAnimation(FFrameNumber KeyTime, UGeometryCollectionComponent* GeomCacheComp);` — Adds a new animation to this track
- L30 _public prototype_ `TArray<UMovieSceneSection*> GetAnimSectionsAtTime(FFrameNumber Time);` — Gets the animation sections at a certain time
- L35 _public prototype_ `virtual void RemoveAllAnimationData() override;` — UMovieSceneTrack interface
- L36 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L37 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L38 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L39 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L40 _public prototype_ `virtual bool IsEmpty() const override;`
- L41 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L42 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L43 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L45 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`
- L48 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L55 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> AnimationSections;` — `UPROPERTY()` — List of all animation sections
