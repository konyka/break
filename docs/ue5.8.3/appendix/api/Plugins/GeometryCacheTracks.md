# Plugins / GeometryCacheTracks

- module root: `Plugins/Runtime/GeometryCache/Source/GeometryCacheTracks`
- headers: 4; symbols: 61
- symbol kinds: class=3, function=7, macro=1, member=15, prototype=32, struct=3
- DynamicallyLoadedModuleNames: GeometryCacheSequencer
- PrivateDependencyModuleNames: AnimGraphRuntime, Slate, SlateCore, TimeManagement
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GeometryCache, MovieScene, MovieSceneTracks
- PublicIncludePathModuleNames: GeometryCacheSequencer, TargetPlatform

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheTracks/Classes/MovieSceneGeometryCacheSection.h` (Public)


#### struct `FMovieSceneGeometryCacheParams`  
`struct FMovieSceneGeometryCacheParams`  
_L14-54_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public prototype_ `FMovieSceneGeometryCacheParams();`
- L21 _public prototype_ `float GetSequenceLength() const;` — Gets the animation sequence length, not modified by play rate
- L24 _public member_ `TObjectPtr<UGeometryCache> GeometryCacheAsset;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GeometryCache", DisplayName = "Geometry Cache")` — The animation this section plays
- L28 _public member_ `FFrameNumber FirstLoopStartFrameOffset;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GeometryCache")` — The offset for the first loop of the animation clip
- L32 _public member_ `FFrameNumber StartFrameOffset;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GeometryCache")` — The offset into the beginning of the animation clip
- L36 _public member_ `FFrameNumber EndFrameOffset;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GeometryCache")` — The offset into the end of the animation clip
- L40 _public member_ `float PlayRate;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GeometryCache")` — The playback rate of the animation clip
- L44 _public member_ `uint32 bReverse : 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")` — Reverse the playback of the animation clip
- L47 _public member_ `float StartOffset_DEPRECATED;` — `UPROPERTY()`
- L50 _public member_ `float EndOffset_DEPRECATED;` — `UPROPERTY()`
- L53 _public member_ `FSoftObjectPath GeometryCache_DEPRECATED;` — `UPROPERTY()`

#### class `UMovieSceneGeometryCacheSection`  
`class UMovieSceneGeometryCacheSection : public UMovieSceneSection`  
_L60-100_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- desc: Movie scene section that control geometry cache playback
- L68 _public member_ `FMovieSceneGeometryCacheParams Params;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation", meta = (ShowOnlyInnerProperties))`
- L71 _public prototype_ `virtual float MapTimeToAnimation(float ComponentDuration, FFrameTime InPosition, FFrameRate InTickResolution) const;` — Get Frame Time as Animation Time
- L75 _protected prototype_ `virtual TOptional<TRange<FFrameNumber> > GetAutoSizeRange() const override;`
- L76 _protected prototype_ `virtual void TrimSection(FQualifiedFrameTime TrimTime, bool bTrimLeft, bool bDeleteKeys) override;`
- L77 _protected prototype_ `virtual UMovieSceneSection* SplitSection(FQualifiedFrameTime SplitTime, bool bDeleteKeys) override;`
- L78 _protected prototype_ `virtual void GetSnapTimes(TArray<FFrameNumber>& OutSnapTimes, bool bGetSectionBorders) const override;`
- L79 _protected prototype_ `virtual TOptional<FFrameTime> GetOffsetTime() const override;`
- L80 _protected prototype_ `virtual void MigrateFrameTimes(FFrameRate SourceRate, FFrameRate DestinationRate) override;`
- L81 _protected prototype_ `virtual UObject* GetSourceObject() const override;`
- L84 _protected prototype_ `virtual void PostLoad() override;` — ~UObject interface
- L85 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L93 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L94 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L96 _public member_ `float PreviousPlayRate;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GEOMETRYCACHETRACKS_API`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheTracks/Classes/MovieSceneGeometryCacheTrack.h` (Public)


#### class `UMovieSceneGeometryCacheTrack`  
`class UMovieSceneGeometryCacheTrack : public UMovieSceneNameableTrack , public IMovieSceneTrackTemplateProducer`  
_L15-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack,IMovieSceneTrackTemplateProducer`
- L24 _public prototype_ `virtual UMovieSceneSection* AddNewAnimation(FFrameNumber KeyTime, UGeometryCacheComponent* GeomCacheComp);` — Adds a new animation to this track
- L27 _public prototype_ `TArray<UMovieSceneSection*> GetAnimSectionsAtTime(FFrameNumber Time);` — Gets the animation sections at a certain time
- L32 _public prototype_ `virtual void RemoveAllAnimationData() override;` — UMovieSceneTrack interface
- L33 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L34 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L35 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L36 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L37 _public prototype_ `virtual bool IsEmpty() const override;`
- L38 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L39 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L40 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L43 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`
- L46 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L53 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> AnimationSections;` — `UPROPERTY()` — List of all animation sections

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheTracks/Private/MovieSceneGeometryCacheTemplate.h` (Private)


#### struct `FMovieSceneGeometryCacheSectionTemplateParameters`  
`struct FMovieSceneGeometryCacheSectionTemplateParameters : public FMovieSceneGeometryCacheParams`  
_L10-28_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneGeometryCacheParams`
- L14 _public function_ `FMovieSceneGeometryCacheSectionTemplateParameters()`
- L15 _public function_ `FMovieSceneGeometryCacheSectionTemplateParameters(const FMovieSceneGeometryCacheParams& BaseParams, FFrameNumber InSectionStartTime, FFrameNumber InSectionEndTime) : FMovieSceneGeometryCacheParams(BaseParams) , SectionStartTime(InSectionStartTime) , SectionEndTime(InSectionEndTime)`
- L21 _public prototype_ `float MapTimeToAnimation(float ComponentDuration, FFrameTime InPosition, FFrameRate InTickResolution) const;`
- L24 _public member_ `FFrameNumber SectionStartTime;` — `UPROPERTY()`
- L27 _public member_ `FFrameNumber SectionEndTime;` — `UPROPERTY()`

#### struct `FMovieSceneGeometryCacheSectionTemplate`  
`struct FMovieSceneGeometryCacheSectionTemplate : public FMovieSceneEvalTemplate`  
_L31-43_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneEvalTemplate`
- L35 _public function_ `FMovieSceneGeometryCacheSectionTemplate()`
- L36 _public prototype_ `FMovieSceneGeometryCacheSectionTemplate(const UMovieSceneGeometryCacheSection& Section);`
- L38 _public function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L39 _public prototype_ `virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`
- L42 _public member_ `FMovieSceneGeometryCacheSectionTemplateParameters Params;` — `UPROPERTY()`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheTracks/Public/GeometryCacheTracksModule.h` (Public)


#### class `FGeometryCacheTracksModule`  
`class FGeometryCacheTracksModule : public IModuleInterface`  
_L10-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L13 _public function_ `FGeometryCacheTracksModule()`
- L15 _public prototype_ `virtual void StartupModule();`
- L16 _public prototype_ `virtual void ShutdownModule();`
- L24 _public function_ `static inline FGeometryCacheTracksModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
