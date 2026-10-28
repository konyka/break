# Plugins / NiagaraSimCaching

- module root: `Plugins/FX/NiagaraSimCaching/Source/NiagaraSimCaching`
- headers: 4; symbols: 68
- symbol kinds: class=3, delegate=1, enum=2, enumerator=4, function=8, macro=1, member=17, prototype=29, struct=3

### `Plugins/FX/NiagaraSimCaching/Source/NiagaraSimCaching/Private/Niagara/Sequencer/MovieSceneNiagaraCacheTemplate.h` (Private)


#### struct `FMovieSceneNiagaraSectionTemplateParameter`  
`struct FMovieSceneNiagaraSectionTemplateParameter`  
_L10-36_
- reflection: `USTRUCT()`
- L15 _public member_ `FMovieSceneFrameRange SectionRange;` — `UPROPERTY()`
- L18 _public member_ `FMovieSceneNiagaraCacheParams Params;` — `UPROPERTY()`
- L20 _public function_ `bool IsTimeWithinSection(const FFrameNumber& Position) const`
- L25 _public function_ `FFrameNumber GetInclusiveStartFrame() const`
- L31 _public function_ `FFrameNumber GetExclusiveEndFrame() const`

#### struct `FMovieSceneNiagaraCacheSectionTemplate`  
`struct FMovieSceneNiagaraCacheSectionTemplate : public FMovieSceneTrackImplementation`  
_L39-58_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneTrackImplementation`
- L43 _public function_ `FMovieSceneNiagaraCacheSectionTemplate()`
- L44 _public prototype_ `FMovieSceneNiagaraCacheSectionTemplate(TArray<FMovieSceneNiagaraSectionTemplateParameter> CacheSections);`
- L46 _public function_ `virtual void SetupOverrides() override`
- L52 _private function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L53 _private prototype_ `virtual void Evaluate(const FMovieSceneEvaluationTrack& Track, TArrayView<const FMovieSceneFieldEntry_ChildTemplate> Children, const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`
- L57 _private member_ `TArray<FMovieSceneNiagaraSectionTemplateParameter> CacheSections;` — `UPROPERTY()`

### `Plugins/FX/NiagaraSimCaching/Source/NiagaraSimCaching/Public/Niagara/NiagaraSimCachingPlugin.h` (Public)


#### class `INiagaraSimCachingPlugin`  
`class INiagaraSimCachingPlugin : public IModuleInterface`  
_L12-40_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _public function_ `static INiagaraSimCachingPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNiagaraSimCaching, Verbose, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNiagaraSimCaching, Verbose, All);`

### `Plugins/FX/NiagaraSimCaching/Source/NiagaraSimCaching/Public/Niagara/Sequencer/MovieSceneNiagaraCacheSection.h` (Public)


#### enum `ENiagaraSimCacheSectionPlayMode`  
`enum class ENiagaraSimCacheSectionPlayMode : uint8`  
_L13-24_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `SimWithoutCache` — When the sequence has no cached data to display, the Niagara component runs the simulation normally
- L23 _public enumerator_ `DisplayCacheOnly` — When the sequence has no cached data to display, the Niagara component is disabled

#### enum `ENiagaraSimCacheSectionStretchMode`  
`enum class ENiagaraSimCacheSectionStretchMode : uint8`  
_L27-38_
- reflection: `UENUM(BlueprintType)`
- L32 _public enumerator_ `Repeat` — When the cache section is stretched in the track it will repeat the cached data
- L37 _public enumerator_ `TimeDilate` — When the cache section is stretched in the track it will dilate the input time so the cached data is stretched once over the full section

#### struct `FMovieSceneNiagaraCacheParams`  
`struct FMovieSceneNiagaraCacheParams : public FMovieSceneBaseCacheParams`  
_L41-89_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneBaseCacheParams`
- L45 _public prototype_ `FMovieSceneNiagaraCacheParams();`
- L46 _public prototype_ `virtual ~FMovieSceneNiagaraCacheParams() override = default;`
- L49 _public prototype_ `virtual float GetSequenceLength() const override;` — Gets the animation sequence length, not modified by play rate
- L52 _public member_ `FNiagaraSimCacheCreateParameters CacheParameters;` — `UPROPERTY(EditAnywhere, Category = "NiagaraCache")`
- L56 _public member_ `TObjectPtr<UNiagaraSimCache> SimCache;` — `UPROPERTY(EditAnywhere, Category = "NiagaraCache")` — The sim cache this section plays and records into
- L60 _public member_ `bool bLockCacheToReadOnly = false;` — `UPROPERTY(EditAnywhere, Category = "NiagaraCache")` — If true then the section properties might still be changed (so the section itself is not locked), but the cache cannot be rerecorded to prevent accidentally overriding the data within
- L63 _public member_ `bool bOverrideQualityLevel = false;` — `UPROPERTY(EditAnywhere, Category = "NiagaraCache", meta=(InlineEditConditionToggle))`
- L67 _public member_ `EPerQualityLevels RecordQualityLevel = EPerQualityLevels::Cinematic;` — `UPROPERTY(EditAnywhere, Category = "NiagaraCache", meta=(EditCondition="bOverrideQualityLevel"))` — If set, then the engine scalability setting will be overriden with this value when recording a new cache for this track
- L71 _public member_ `ENiagaraSimCacheSectionPlayMode CacheReplayPlayMode = ENiagaraSimCacheSectionPlayMode::DisplayCacheOnly;` — `UPROPERTY(EditAnywhere, Category="SimCache")` — What should the effect do when the track has no cache data to display
- L75 _public member_ `ENiagaraSimCacheSectionStretchMode SectionStretchMode = ENiagaraSimCacheSectionStretchMode::TimeDilate;` — `UPROPERTY(EditAnywhere, Category="SimCache")` — What should the effect do when the cache section is stretched?
- L80 _public member_ `bool bOverrideRecordRate = false;` — `UPROPERTY(EditAnywhere, Category = "Cache", meta = (InlineEditConditionToggle))` — True if the cache should be recorded at a rate that is slower than the sequencer play rate.
- L87 _public member_ `float CacheRecordRateFPS = 24.0f;` — `UPROPERTY(EditAnywhere, Category = "Cache", meta = (EditCondition = "bOverrideRecordRate"))` — The rate at which the cache should be recorded. Will be ignored if the sequence plays at a lower rate than this number. This option is useful if you need to play the sequence at a very high fps for simulation stability (e.g. 240fps), but then later want to play back the cache at a normal rate (e.g. 24fps). Please note that using this option might result in rendering artifacts for things like motion blur, velocity interpolation or inconsistent grid data in fluids, due to the dropped cache frames.

#### class `UMovieSceneNiagaraCacheSection`  
`class UMovieSceneNiagaraCacheSection : public UMovieSceneBaseCacheSection`  
_L95-112_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneBaseCacheSection`
- desc: Movie scene section that control NiagaraCache playback
- L101 _public prototype_ `UMovieSceneNiagaraCacheSection();`
- L104 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L108 _public member_ `FMovieSceneNiagaraCacheParams Params;` — `UPROPERTY(EditAnywhere, Category = "NiagaraCache", meta = (ShowOnlyInnerProperties))`
- L111 _public member_ `bool bCacheOutOfDate = false;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API NIAGARASIMCACHING_API`

### `Plugins/FX/NiagaraSimCaching/Source/NiagaraSimCaching/Public/Niagara/Sequencer/MovieSceneNiagaraCacheTrack.h` (Public)


#### class `UMovieSceneNiagaraCacheTrack`  
`class UMovieSceneNiagaraCacheTrack : public UMovieSceneNameableTrack , public IMovieSceneTrackTemplateProducer , public IMovieSceneCachedTrack`  
_L14-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack,IMovieSceneTrackTemplateProducer,IMovieSceneCachedTrack`
- desc: Handles animation of NiagaraCache
- L24 _public prototype_ `virtual UMovieSceneSection* AddNewAnimation(FFrameNumber KeyTime, class UNiagaraComponent* NiagaraComponent);` — Adds a new animation to this track
- L27 _public prototype_ `TArray<UMovieSceneSection*> GetAnimSectionsAtTime(FFrameNumber Time);` — Gets the animation sections at a certain time
- L30 _public prototype_ `virtual void RemoveAllAnimationData() override;` — UMovieSceneTrack interface
- L31 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L32 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L33 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L34 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L35 _public prototype_ `virtual bool IsEmpty() const override;`
- L36 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L37 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L38 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L39 _public prototype_ `virtual bool PopulateEvaluationTree(TMovieSceneEvaluationTree<FMovieSceneTrackEvaluationData>& OutData) const override;`
- L40 _public prototype_ `virtual void PostCompile(FMovieSceneEvaluationTrack& OutTrack, const FMovieSceneTrackCompilerArgs& Args) const override;`
- L43 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`
- L46 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L50 _public prototype_ `virtual void ResetCache() override;`
- L51 _public prototype_ `virtual void SetCacheRecordingAllowed(bool bShouldRecord) override;`
- L52 _public prototype_ `virtual bool IsCacheRecordingAllowed() const override;`
- L53 _public prototype_ `virtual int32 GetMinimumEngineScalabilitySetting() const override;`
- L56 _public member_ `bool bIsRecording = false;` — `UPROPERTY(Transient)`
- L62 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> AnimationSections;` — `UPROPERTY()` — List of all animation sections
- L65 _private member_ `bool bCacheRecordingEnabled = true;` — `UPROPERTY()`
