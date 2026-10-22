# Plugins / CinematicPrestreaming

- module root: `Plugins/MovieScene/CinematicPrestreaming/Source/CinematicPrestreaming`
- headers: 5; symbols: 51
- symbol kinds: class=4, delegate=1, function=7, member=16, prototype=21, struct=2
- PrivateDependencyModuleNames: CoreUObject, Engine, RHI, RenderCore
- PublicDependencyModuleNames: Core, MovieScene

### `Plugins/MovieScene/CinematicPrestreaming/Source/CinematicPrestreaming/Private/CinePrestreamingLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCinePrestreaming, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCinePrestreaming, Log, All);`

### `Plugins/MovieScene/CinematicPrestreaming/Source/CinematicPrestreaming/Private/TrackInstances/MovieSceneCinePrestreamingTrackInstance.h` (Private)


#### class `UMovieSceneCinePrestreamingTrackInstance`  
`class UMovieSceneCinePrestreamingTrackInstance : public UMovieSceneTrackInstance`  
_L9-18_
- reflection: `UCLASS()`
- inherits: `UMovieSceneTrackInstance`
- L15 _protected prototype_ `void OnInputAdded(const FMovieSceneTrackInstanceInput& InInput) override;` — UMovieSceneTrackInstance interface
- L16 _protected prototype_ `void OnInputRemoved(const FMovieSceneTrackInstanceInput& InInput) override;`
- L17 _protected prototype_ `void OnAnimate() override;`

### `Plugins/MovieScene/CinematicPrestreaming/Source/CinematicPrestreaming/Public/CinePrestreamingData.h` (Public)


#### struct `FCinePrestreamingVTData`  
`struct FCinePrestreamingVTData`  
_L9-24_
- reflection: `USTRUCT()`
- L19 _public member_ `TArray<uint64> PageIds_DEPRECATED;` — `UPROPERTY()` — Deprecated container format. Will be fixed up into RequestData during editor PostLoad. But it is recommended to re-record the shot to benefit from a more efficient asset size.
- L23 _public member_ `TArray<uint32> RequestData;` — `UPROPERTY(VisibleAnywhere, Category = "Cinematic Prestreaming")` — Compacted request stream for passing virtual texture requests directly to the renderer.

#### struct `FCinePrestreamingNaniteData`  
`struct FCinePrestreamingNaniteData`  
_L27-34_
- reflection: `USTRUCT()`
- L33 _public member_ `TArray<uint32> RequestData;` — `UPROPERTY(VisibleAnywhere, Category = "Cinematic Prestreaming")` — Compacted request stream for passing nanite requests directly to the renderer.

#### class `UCinePrestreamingData`  
`class UCinePrestreamingData : public UObject`  
_L37-72_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L42 _private prototype_ `virtual void PostLoad() override;` — UObject Interface
- L43 _private prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L49 _public member_ `TArray<FFrameNumber> Times;` — `UPROPERTY(VisibleAnywhere, Category = "Cinematic Prestreaming")` — Array of frame number times for the corresponding entries in the VirtualTextureDatas and NaniteDatas arrays.
- L56 _public member_ `TArray<FCinePrestreamingVTData> VirtualTextureDatas;` — `UPROPERTY(VisibleAnywhere, Category = "Cinematic Prestreaming")` — Array of virtual texture request data. Can have empty array slots because the recording process groups requests for time periods to reduce memory cost of repeated data.
- L63 _public member_ `TArray<FCinePrestreamingNaniteData> NaniteDatas;` — `UPROPERTY(VisibleAnywhere, Category = "Cinematic Prestreaming")` — Array of nanite request data. Can have empty array slots because the recording process groups requests for time periods to reduce memory cost of repeated data.
- L67 _public member_ `FDateTime RecordedTime;` — `UPROPERTY(VisibleAnywhere, Category = "Cinematic Prestreaming")` — Time that this asset was generated (in UTC). Used to give better context about how up to date an asset is as they are hard to preview.
- L71 _public member_ `FIntPoint RecordedResolution;` — `UPROPERTY(VisibleAnywhere, Category = "Cinematic Prestreaming")` — What resolution was this asset generated at? Recordings are resolution dependent as different mips will be chosen for different resolutions.

### `Plugins/MovieScene/CinematicPrestreaming/Source/CinematicPrestreaming/Public/Sections/MovieSceneCinePrestreamingSection.h` (Public)


#### class `UMovieSceneCinePrestreamingSection`  
`class UMovieSceneCinePrestreamingSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L15-87_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: Movie Scene Section representing a Prestreaming asset.
- L22 _public prototype_ `UMovieSceneCinePrestreamingSection(const FObjectInitializer& ObjInit);`
- L26 _public function_ `UCinePrestreamingData* GetPrestreamingAsset() const` — `UFUNCTION(BlueprintPure, Category = "Cinematic Prestreaming")` — Get the prestreaming asset pointer. This may return nullptr in cooked build if we are using async loading.
- L29 _public function_ `void SetPrestreamingAsset(UCinePrestreamingData* InData)` — `UFUNCTION(BlueprintCallable, Category = "Cinematic Prestreaming")`
- L33 _public function_ `int32 GetQualityLevel() const` — `UFUNCTION(BlueprintPure, Category = "Cinematic Prestreaming")` — If MovieScene.PreStream.QualityLevel is less than this then discard this section at runtime.
- L36 _public function_ `void SetQualityLevel(const int32 InLevel)` — `UFUNCTION(BlueprintCallable, Category = "Cinematic Prestreaming")`
- L39 _public function_ `void SetStartFrameOffset(const int32 InOffset)` — `UFUNCTION(BlueprintCallable, Category = "Cinematic Prestreaming")`
- L42 _public prototype_ `void AsyncStreamingAddRef();` — Add a reference to the async loader. When the ref count is non-zero the prestreaming asset should be loaded or loading.
- L45 _public prototype_ `void AsyncStreamingReleaseRef();` — Release the reference to the async loader. When the ref count is zero the prestreaming asset can be unloaded.
- L48 _public function_ `virtual TOptional<FFrameTime> GetOffsetTime() const override` — UMovieSceneSection interface
- L52 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L55 _protected prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;` — IMovieSceneEntityProvider interface
- L60 _protected member_ `TObjectPtr<UCinePrestreamingData> PrestreamingAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Prestreaming)` — The asset containing cinematic prestreaming data to use for this section.
- L64 _protected member_ `TSoftObjectPtr<UCinePrestreamingData> SoftPrestreamingAsset;` — `UPROPERTY()` — Soft ref version of the asset for use by async loading.
- L68 _protected member_ `int32 StartFrameOffset = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Prestreaming)` — Number of frames by which to offset the evaluation. Larger values cause prestreaming to happen earlier.
- L72 _protected member_ `int32 QualityLevel = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Prestreaming, AdvancedDisplay)` — If MovieScene.PreStream.QualityLevel is less than this then discard this section at runtime.
- L80 _protected member_ `bool bUseAsyncLoading= false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Prestreaming, AdvancedDisplay)` — Set true to enable async loading of the prestreaming data in game. This can reduce memory overhead for a long cinematic with multiple prestreaming shots. Async loading requires sufficient preroll time to load the asset and still have enough time to run StartFrameOffset frames ahead.
- L83 _protected member_ `uint32 AsyncLoadingRefCount = 0;` — Ref count for async loading of PrestreamingAsset.
- L86 _protected member_ `TSharedPtr<FStreamableHandle> AsyncLoadHandle;` — Handle for async loading of PrestreamingAsset.

### `Plugins/MovieScene/CinematicPrestreaming/Source/CinematicPrestreaming/Public/Tracks/MovieSceneCinePrestreamingTrack.h` (Public)


#### class `UMovieSceneCinePrestreamingTrack`  
`class UMovieSceneCinePrestreamingTrack : public UMovieSceneNameableTrack`  
_L15-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- desc: A track that controls playback of streaming triggers for some rendering systems. This is to ensure that data is available before use where by default for systems like virtual texture and nanite streaming is driven by what is already visible on screen.
- L20 _public prototype_ `UMovieSceneCinePrestreamingTrack(const FObjectInitializer& ObjectInitializer);`
- L23 _public prototype_ `bool IsEmpty() const override;` — UMovieSceneTrack interface
- L24 _public prototype_ `void AddSection(UMovieSceneSection& Section) override;`
- L25 _public prototype_ `void RemoveSection(UMovieSceneSection& Section) override;`
- L26 _public prototype_ `void RemoveSectionAt(int32 SectionIndex) override;`
- L27 _public prototype_ `bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L28 _public prototype_ `UMovieSceneSection* CreateNewSection() override;`
- L29 _public prototype_ `const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L30 _public prototype_ `bool HasSection(const UMovieSceneSection& Section) const override;`
- L31 _public function_ `bool SupportsMultipleRows() const override`
- L34 _public prototype_ `FText GetDefaultDisplayName() const override;`
- L39 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()`
