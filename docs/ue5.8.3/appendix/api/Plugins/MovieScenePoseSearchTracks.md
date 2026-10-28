# Plugins / MovieScenePoseSearchTracks

- module root: `Plugins/Experimental/MovieScenePoseSearchTracks/Source/MovieScenePoseSearchTracks`
- headers: 5; symbols: 72
- symbol kinds: class=4, function=1, member=32, namespace=6, prototype=26, struct=3
- PublicDependencyModuleNames: AnimGraphRuntime, Core, CoreUObject, Engine, MovieScene, MovieSceneAnimMixer, MovieSceneTracks, PoseSearch, SlateCore, UAF, UAFAnimGraph, UAFPoseSearch

### `Plugins/Experimental/MovieScenePoseSearchTracks/Source/MovieScenePoseSearchTracks/Private/MovieScenePoseSearchTracksModule.h` (Private)


#### class `UE::MovieScene::FMovieScenePoseSearchTracksModule`  
`class FMovieScenePoseSearchTracksModule : public IModuleInterface`  
_L18-23_
- inherits: `IModuleInterface`
- L21 _private prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L22 _private prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MovieScene` (scope `UE`)

### `Plugins/Experimental/MovieScenePoseSearchTracks/Source/MovieScenePoseSearchTracks/Public/PoseSearchTracksComponentTypes.h` (Public)


#### struct `UE::MovieScene::FPoseSearchTracksComponentTypes`  
`struct FPoseSearchTracksComponentTypes`  
_L10-19_
- L12 _public prototype_ `static FPoseSearchTracksComponentTypes* Get();`
- L13 _public prototype_ `static void Destroy();`
- L15 _public member_ `TComponentTypeID<FMovieSceneStitchAnimComponentData> StitchAnim;`
- L18 _private prototype_ `FPoseSearchTracksComponentTypes();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MovieScene` (scope `UE`)

### `Plugins/Experimental/MovieScenePoseSearchTracks/Source/MovieScenePoseSearchTracks/Public/Sections/MovieSceneStitchAnimSection.h` (Public)


#### struct `FMovieSceneStitchAnimComponentData`  
`struct FMovieSceneStitchAnimComponentData`  
_L18-50_
- reflection: `USTRUCT()`
- L23 _public member_ `TObjectPtr<UObject> StitchDatabase;` — `UPROPERTY()`
- L26 _public member_ `TObjectPtr<UAnimationAsset> TargetPoseAsset;` — `UPROPERTY()`
- L29 _public member_ `float TargetAnimationTimeSeconds = 0.0f;` — `UPROPERTY()`
- L32 _public member_ `FTransform TargetTransform;` — `UPROPERTY()`
- L35 _public member_ `FFrameNumber StartFrame;` — `UPROPERTY()`
- L38 _public member_ `FFrameNumber EndFrame;` — `UPROPERTY()`
- L41 _public member_ `EMovieSceneRootMotionSpace TargetTransformSpace = EMovieSceneRootMotionSpace::AnimationSpace;` — `UPROPERTY()`
- L44 _public member_ `bool bAuthoritativeRootMotion = true;` — `UPROPERTY()`
- L47 _public member_ `FName OverridePoseHistoryTag;` — `UPROPERTY()`
- L49 _public prototype_ `double MapTimeToSectionSeconds(FFrameTime InPosition, FFrameRate InFrameRate) const;`

#### struct `FMovieSceneStitchAnimEvaluationTask`  
`struct FMovieSceneStitchAnimEvaluationTask : public FAnimNextEvaluationTask`  
_L53-102_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- L57 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FMovieSceneStitchAnimEvaluationTask)`
- L63 _public member_ `FMovieSceneStitchAnimComponentData StitchData;` — `UPROPERTY(Transient)`
- L67 _public member_ `float InitialTime = -1.f;` — `UPROPERTY(Transient)` — Initial sequencer time when the motion matching calculation was done
- L71 _public member_ `float TimeToTarget = -1.f;` — `UPROPERTY(Transient)` — Time until our target pose
- L75 _public member_ `float PreviousTime = -1.f;` — `UPROPERTY(Transient)` — Previous sequencer time
- L79 _public member_ `float CurrentTime = -1.f;` — `UPROPERTY(Transient)` — Current sequencer time
- L82 _public member_ `FTransform InitialRootTransform = FTransform::Identity;` — `UPROPERTY(Transient)`
- L85 _public member_ `TWeakObjectPtr<const UObject> ContextObject;` — `UPROPERTY(Transient)`
- L88 _public member_ `FTransform SequenceTransformOrigin = FTransform::Identity;` — `UPROPERTY(Transient)`
- L92 _public member_ `mutable TObjectPtr<UAnimationAsset> MatchedAsset;` — `UPROPERTY(Transient)` — Calculated and cached by the motion match at InitialTime
- L95 _public member_ `mutable float MatchedAssetTime = 0.f;` — `UPROPERTY(Transient)`
- L98 _public member_ `FTransform MeshToActorTransform = FTransform::Identity;` — `UPROPERTY(Transient)`
- L101 _public member_ `mutable float MatchedAssetActualIntervalTime = 0.f;` — `UPROPERTY(Transient)`

#### class `UMovieSceneStitchAnimSection`  
`class UMovieSceneStitchAnimSection : public UMovieSceneSection , public IMovieSceneEntityProvider , public IMovieSceneAnimationMixerItemInterface`  
_L109-167_
- reflection: `UCLASS(MinimalAPI, DisplayName="Animation Stitch")`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider,IMovieSceneAnimationMixerItemInterface`
- desc: Handles generating and playing back transitional skeletal animations from a stitch database.
- L118 _public prototype_ `UMovieSceneStitchAnimSection(const FObjectInitializer& ObjectInitializer);`
- L121 _public member_ `TObjectPtr<UObject> StitchDatabase;` — `UPROPERTY(EditAnywhere, Category = "Stitch", meta=(AllowedClasses = "/Script/PoseSearch.PoseSearchDatabase"))`
- L124 _public member_ `TObjectPtr<UAnimationAsset> TargetPoseAsset;` — `UPROPERTY(EditAnywhere, Category = "Stitch")`
- L128 _public member_ `float TargetAnimationTimeSeconds = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Stitch")` — TODO: Is this the best way to specify this?
- L131 _public member_ `FTransform TargetTransform;` — `UPROPERTY(EditAnywhere, Category = "Stitch")`
- L135 _public member_ `FMovieSceneFloatChannel Weight;` — `UPROPERTY()` — The weight curve for this animation section
- L138 _public member_ `EMovieSceneRootMotionSpace TargetTransformSpace = EMovieSceneRootMotionSpace::AnimationSpace;` — `UPROPERTY(EditAnywhere, Category = "Stitch")`
- L141 _public member_ `bool bAuthoritativeRootMotion = true;` — `UPROPERTY(EditAnywhere, Category = "Stitch")`
- L147 _public member_ `FName OverridePoseHistoryTag;` — `UPROPERTY(EditAnywhere, category = "Stitch")` — When using animation blueprints, can be used to search for a specific pose history node by tag. This allow you to have a pose history node pre-sequencer for blending into sequences, but still capture a separate pose history afterwards for blending out.
- L150 _public prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override;`
- L151 _public prototype_ `virtual UObject* GetSourceObject() const override;`
- L153 _public function_ `virtual FColor GetMixerItemTint() const override`
- L160 _protected prototype_ `virtual float GetTotalWeightValue(FFrameTime InTime) const override;`
- L163 _protected prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& InParams, FImportedEntity* OutImportedEntity) override;` — ~IMovieSceneEntityProvider interface
- L165 _protected member_ `FColor MixerTintOverride = FColor(20, 70, 120, 200);`

### `Plugins/Experimental/MovieScenePoseSearchTracks/Source/MovieScenePoseSearchTracks/Public/Systems/MovieSceneStitchAnimSystem.h` (Public)


#### class `UMovieSceneStitchAnimSystem`  
`class UMovieSceneStitchAnimSystem : public UMovieSceneEntityInstantiatorSystem`  
_L12-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntityInstantiatorSystem`
- desc: System to handle updating stitch anim evaluation tasks for the anim mixer.
- L19 _public prototype_ `UMovieSceneStitchAnimSystem(const FObjectInitializer& ObjInit);`
- L23 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`

### `Plugins/Experimental/MovieScenePoseSearchTracks/Source/MovieScenePoseSearchTracks/Public/Tracks/MovieSceneStitchAnimTrack.h` (Public)


#### class `UMovieSceneStitchAnimTrack`  
`class UMovieSceneStitchAnimTrack : public UMovieSceneNameableTrack`  
_L16-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- desc: Handles generating and playing back transitional skeletal animations from a stitch database.
- L23 _public prototype_ `UMovieSceneStitchAnimTrack(const FObjectInitializer& ObjectInitializer);`
- L29 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L30 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L31 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L32 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L33 _public prototype_ `virtual bool IsEmpty() const override;`
- L34 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L35 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L36 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L37 _public prototype_ `virtual bool SupportsMultipleRows() const override;`
- L40 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L44 _public prototype_ `UMovieSceneSection* AddNewAnimationOnRow(FFrameNumber KeyTime, class UPoseSearchDatabase* PoseSearchDatabase, int32 RowIndex);` — Adds a new animation to this track
- L50 _public member_ `TArray<TObjectPtr<UMovieSceneSection>> AnimationSections;` — `UPROPERTY()` — List of all animation sections
