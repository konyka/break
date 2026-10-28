# Plugins / SubtitlesAndClosedCaptions

- module root: `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptions`
- headers: 12; symbols: 126
- symbol kinds: class=9, function=10, macro=4, member=28, namespace=2, prototype=69, struct=4
- PrivateDependencyModuleNames: Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, InputCore, MovieScene, MovieSceneTracks, UMG, ViewportWidgetOverlay

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptions/Public/ActiveSubtitleAssetData.h` (Public)


#### struct `FActiveSubtitleAssetData`  
`struct FActiveSubtitleAssetData`  
_L14-22_
- reflection: `USTRUCT()`
- L19 _public member_ `FSubtitleAssetData Subtitle;` — `UPROPERTY()`
- L21 _public member_ `FTimerHandle DurationTimerHandle;`

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptions/Public/MovieSceneSubtitleComponentTypes.h` (Public)


#### struct `FMovieSceneSubtitleComponentTypes`  
`struct FMovieSceneSubtitleComponentTypes`  
_L14-26_
- desc: Component data present on all Subtitle entities
- L16 _public member_ `UE::MovieScene::TComponentTypeID<FSubtitleDataComponent> SubtitleData;`
- L18 _public prototype_ `static FMovieSceneSubtitleComponentTypes* Get();`
- L19 _public prototype_ `static void Destroy();`
- L22 _private prototype_ `FMovieSceneSubtitleComponentTypes();`
- L24 _private member_ `static bool GMovieSceneSubtitlesComponentTypesDestroyed;`
- L25 _private member_ `static TUniquePtr<FMovieSceneSubtitleComponentTypes> GMovieSceneSubtitlesComponentTypes;`

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptions/Public/MovieSceneSubtitleSection.h` (Public)


#### class `UMovieSceneSubtitleSection`  
`class UMovieSceneSubtitleSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L17-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- L25 _public function_ `TObjectPtr<const USubtitleAssetUserData> GetSubtitle() const`
- L30 _public function_ `void SetSubtitle(const USubtitleAssetUserData& InSubtitle)`
- L36 _public prototype_ `virtual TOptional<TRange<FFrameNumber> > GetAutoSizeRange() const override;`
- L39 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L40 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L45 _private member_ `TObjectPtr<const USubtitleAssetUserData> Subtitle;` — `UPROPERTY(EditAnywhere, Category = "Subtitles")`

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptions/Public/MovieSceneSubtitlesSystem.h` (Public)


#### struct `FEvaluateSubtitles`  
`struct FEvaluateSubtitles`  
_L21-136_
- L24 _public function_ `FEvaluateSubtitles(const UE::MovieScene::FInstanceRegistry& InInstanceRegistry) : InstanceRegistry(InInstanceRegistry)`
- L29 _public function_ `void ForEachAllocation( const UE::MovieScene::FEntityAllocation* Allocation, UE::MovieScene::TRead<UE::MovieScene::FInstanceHandle> SequenceInstanceHandles, UE::MovieScene::TWrite<FSubtitleDataComponent> SubtitleData) const`
- L51 _public function_ `void Evaluate(const UE::MovieScene::FSequenceInstance& SequenceInstance, const FSubtitleDataComponent& SubtitleData, EMovieScenePlayerStatus::Type LastStatus) const`
- L135 _protected member_ `const UE::MovieScene::FInstanceRegistry& InstanceRegistry;`

#### class `UMovieSceneSubtitlesSystem`  
`class UMovieSceneSubtitlesSystem : public UMovieSceneEntitySystem`  
_L139-151_
- reflection: `UCLASS()`
- inherits: `UMovieSceneEntitySystem`
- L145 _public prototype_ `UMovieSceneSubtitlesSystem(const FObjectInitializer& ObjInit);`
- L146 _public prototype_ `virtual ~UMovieSceneSubtitlesSystem();`
- L149 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L150 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptions/Public/MovieSceneSubtitlesTrack.h` (Public)


#### class `UMovieSceneSubtitlesTrack`  
`class UMovieSceneSubtitlesTrack : public UMovieSceneNameableTrack`  
_L14-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- L20 _public prototype_ `UMovieSceneSection* AddNewSubtitle(const USubtitleAssetUserData& Subtitle, FFrameNumber InStartTime);`
- L21 _public prototype_ `UMovieSceneSection* AddNewSubtitleOnRow(const USubtitleAssetUserData& Subtitle, FFrameNumber InStartTime, int32 InRowIndex);`
- L26 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;` — UMovieSceneTrack interface
- L27 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L28 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L29 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L30 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L31 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L32 _public prototype_ `virtual bool IsEmpty() const override;`
- L33 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L34 _public prototype_ `virtual bool SupportsMultipleRows() const override;`
- L35 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L39 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> SubtitleSections;` — `UPROPERTY()`

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptions/Public/SubtitleDataComponent.h` (Public)


#### struct `FSubtitleDataComponent`  
`struct FSubtitleDataComponent`  
_L15-23_
- reflection: `USTRUCT()`
- desc: Component data for subtitles tracks
- L20 _public member_ `TObjectPtr<const UMovieSceneSubtitleSection> SubtitleSection;` — `UPROPERTY()`
- L22 _public member_ `EMovieScenePlayerStatus::Type LastSequenceInstanceStatus = EMovieScenePlayerStatus::Type::Stopped;`

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptions/Public/SubtitleWidget.h` (Public)


#### class `USubtitleWidget`  
`class USubtitleWidget : public UUserWidget`  
_L15-50_
- reflection: `UCLASS(Abstract, BlueprintType, Blueprintable, meta=( DontUseGenericSpawnObject="True", DisableNativeTick), MinimalAPI)`
- inherits: `UUserWidget`
- L20 _private member_ `TMap<ESubtitleType, TOptional<FSubtitleAssetData>> CurrentlyDisplayedSubtitles;`
- L23 _protected prototype_ `virtual void NativeConstruct() override;`
- L27 _protected member_ `TObjectPtr<UTextBlock> DialogSubtitleBlock;` — `UPROPERTY(BlueprintReadOnly, Category = "Subtitles", meta = (BindWidgetOptional))` — Subtitle Text Blocks
- L30 _protected member_ `TObjectPtr<UTextBlock> CaptionSubtitleBlock;` — `UPROPERTY(BlueprintReadOnly, Category = "Subtitles", meta = (BindWidgetOptional))`
- L33 _protected member_ `TObjectPtr<UTextBlock> DescriptionSubtitleBlock;` — `UPROPERTY(BlueprintReadOnly, Category = "Subtitles", meta = (BindWidgetOptional))`
- L37 _protected member_ `TObjectPtr<UBorder> DialogBorder;` — `UPROPERTY(BlueprintReadOnly, Category = "SubtitleBorders", meta = (BindWidgetOptional))` — Borders to the text blocks
- L40 _protected member_ `TObjectPtr<UBorder> CaptionBorder;` — `UPROPERTY(BlueprintReadOnly, Category = "SubtitleBorders", meta = (BindWidgetOptional))`
- L43 _protected member_ `TObjectPtr<UBorder> DescriptionBorder;` — `UPROPERTY(BlueprintReadOnly, Category = "SubtitleBorders", meta = (BindWidgetOptional))`
- L45 _public prototype_ `void StartDisplayingSubtitle(const FSubtitleAssetData& Subtitle);`
- L46 _public prototype_ `void StopDisplayingSubtitle(const FSubtitleAssetData& Subtitle);`
- L47 _public prototype_ `void StopDisplayingAllSubtitles();`
- L49 _public prototype_ `USubtitleWidget(const FObjectInitializer& ObjectInitializer);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SUBTITLESANDCLOSEDCAPTIONS_API`

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptions/Public/SubtitlesAndClosedCaptionsModule.h` (Public)


#### class `FSubtitlesAndClosedCaptionsModule`  
`class FSubtitlesAndClosedCaptionsModule : public ISubtitlesAndClosedCaptionsModule`  
_L13-19_
- inherits: `ISubtitlesAndClosedCaptionsModule`
- L16 _public prototype_ `void StartupModule() override;`
- L17 _public prototype_ `void ShutdownModule() override;`
- L18 _public prototype_ `TSubclassOf<UAssetUserData> GetAssetUserDataClass() const override;`

#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSubtitlesAndClosedCaptions, Log, All);`

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptions/Public/SubtitlesAudioSubsystem.h` (Public)


#### class `USubtitlesAudioSubsystem`  
`class USubtitlesAudioSubsystem : public UAudioEngineSubsystem , public IActiveSoundUpdateInterface`  
_L20-50_
- reflection: `UCLASS(MinimalAPI, config = Game, defaultConfig)`
- inherits: `UAudioEngineSubsystem,IActiveSoundUpdateInterface`
- desc: SubtitlesAudioSubsystem - AudioEngineSubsystem for automatically queueing subtitles on audio classes. Separated from SubtitlesSubsystem, which is a UWorldSubsystem, to avoid issues with lifecycle management as some parts need access to the world and others to the audio device.
- L25 _public prototype_ `USubtitlesAudioSubsystem() = default;`
- L28 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L29 _public prototype_ `virtual void Deinitialize() override;`
- L33 _public prototype_ `virtual void NotifyActiveSoundCreated(FActiveSound& ActiveSound) override;`
- L34 _public prototype_ `virtual void NotifyActiveSoundDeleting(const FActiveSound& ActiveSound) override;`
- L39 _private prototype_ `void OnDialogueSoundWaveProxyParsed(const FActiveSound& ActiveSound, const UDialogueSoundWaveProxy* Proxy);` — Called on the audio thread when a SoundNodeDialoguePlayer first resolves its proxy for a given active sound.
- L42 _private prototype_ `void QueueSubtitleFromParsedSoundWaveProxy(const FText Text, const float Priority, const float Duration, const float StartOffset, const uint32 PlayOrder);` — Game-thread side of the same function
- L44 _private prototype_ `static void QueueSubtitleFromDialogueWaveProxy(const UDialogueSoundWaveProxy* DialogueWaveProxy, const FActiveSound& ActiveSound);`
- L45 _private prototype_ `static void StopSubtitleFromDialogueWaveProxy(const UDialogueSoundWaveProxy* DialogueWaveProxy, const FActiveSound& ActiveSound);`
- L49 _private member_ `TMap<uint32, TArray<FSubtitleAssetData>> QueuedSubtitlesByPlayOrder;` — Tracks which subtitle data is queued for each active sound. PlayOrder, the key, is monotonically incremented by FActiveSound and is thus unique. Used later by NotifyActiveSoundDeleting for stopping the associated subtitles.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SUBTITLESANDCLOSEDCAPTIONS_API`

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptions/Public/SubtitlesBlueprintFunctionLibrary.h` (Public)


#### class `USubtitlesBlueprintFunctionLibrary`  
`class USubtitlesBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L14-54_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "SubtitlesLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L25 _public prototype_ `static void QueueSubtitlesFromAsset(TSoftObjectPtr<USubtitleAssetUserData> SubtitleAsset);` — `UFUNCTION(BlueprintCallable, Category = Subtitles)` — Queues all of the subtitles in a Subtitle asset, accounting for any delayed start offsets set for each. Subtitles queued through this function are internally-timed.
- L29 _public prototype_ `static void StopSubtitlesInAsset(TSoftObjectPtr<USubtitleAssetUserData> SubtitleAsset);` — `UFUNCTION(BlueprintCallable, Category = Subtitles)` — Stops all subtitles in a subtitle asset, regardless of whether they're already queued or if they have a delayed start.
- L34 _public prototype_ `static void QueueSubtitle(const FSubtitleAssetData& Subtitle, const ESubtitleTiming Timing = ESubtitleTiming::InternallyTimed);` — `UE_DEPRECATED(5.8, "Use QueueSingleSubtitle. It removes extraneous and confusing parameters.")` — `UFUNCTION(BlueprintCallable, Category = Subtitles)` — Queues an individual subtitle from a struct, or a single entry in a Subtitle asset's array.
- L39 _public prototype_ `static void QueueSingleSubtitle( const FText Text, const float Duration, const float StartOffset, const float Priority, const ESubtitleType SubtitleType, const ESubtitleTiming Timing = ESubtitleTiming::InternallyTimed);` — `UFUNCTION(BlueprintCallable, Category = Subtitles)` — Queues an individual subtitle. Parameters form an FSubtitleAssetData (see SubtitlesAndClosedCaptionsDelegates.h), but the Duration Type is removed as it is irrelevant for queueing this way.
- L44 _public prototype_ `static bool IsSubtitleActive(const FSubtitleAssetData& Subtitle);` — `UFUNCTION(BlueprintCallable, Category = Subtitles)`
- L47 _public prototype_ `static void StopSubtitle(const FSubtitleAssetData& Subtitle);` — `UFUNCTION(BlueprintCallable, Category = Subtitles)`
- L50 _public prototype_ `static void StopAllSubtitles();` — `UFUNCTION(BlueprintCallable, Category = Subtitles)`
- L53 _public prototype_ `static void ReplaceSubtitleWidget(const TSoftClassPtr<USubtitleWidget>& NewWidgetAsset);` — `UFUNCTION(BlueprintCallable, Category = Subtitles)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SUBTITLESANDCLOSEDCAPTIONS_API`

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptions/Public/SubtitlesSettings.h` (Public)


#### class `USubtitlesSettings`  
`class USubtitlesSettings : public UDeveloperSettings`  
_L12-38_
- reflection: `UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Subtitles And Closed Captions"))`
- inherits: `UDeveloperSettings`
- L17 _public prototype_ `USubtitlesSettings();`
- L21 _public function_ `const TSubclassOf<USubtitleWidget>& GetWidget() const` — Temporarily retaining the old GetWidget to not break builds. Plugin is still experimental, so we don't need to actually deprecate it just yet.
- L22 _public function_ `const TSubclassOf<USubtitleWidget>& GetWidgetDefault() const`
- L24 _private member_ `TSubclassOf<USubtitleWidget> WidgetToUseAsSubclass;`
- L25 _private member_ `TSubclassOf<USubtitleWidget> DefaultWidgetToUseAsSubclass;`
- L28 _public function_ `inline const TSoftClassPtr<USubtitleWidget>& GetWidgetSoftClassPtr() const`
- L29 _public function_ `inline const TSoftClassPtr<USubtitleWidget>& GetWidgetDefaultSoftClassPtr() const`
- L34 _protected member_ `TSoftClassPtr<USubtitleWidget> SubtitleWidgetToUse;` — `UPROPERTY(config, EditDefaultsOnly, Category = Subtitles, AdvancedDisplay)`
- L37 _protected member_ `TSoftClassPtr<USubtitleWidget> SubtitleWidgetToUseDefault;` — `UPROPERTY(config)` — fallback for SubtitleWidgetToUse (not set by user)

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptions/Public/SubtitlesSubsystem.h` (Public)


#### class `USubtitlesSubsystem`  
`class USubtitlesSubsystem : public UWorldSubsystem`  
_L41-122_
- reflection: `UCLASS(MinimalAPI, config = Game, defaultConfig)`
- inherits: `UWorldSubsystem`
- desc: #SUBTITLES_PRD -	Requirement:	Ability to allow designers to “script” subtitle location for sequences and scenes to avoid subtitles overlapping important scenes or characters Use a UEngineSubsystem for blueprints Game configuration for font customization per game
- L45 _public prototype_ `USubtitlesSubsystem() = default;`
- L53 _public prototype_ `virtual void QueueSubtitle(FQueueSubtitleParameters Params, const ESubtitleTiming Timing = ESubtitleTiming::InternallyTimed);` — Adds a subtitle to the queue: Params contains the subtitle asset and an optional duration. The highest-priority subtitle in the queue will be displayed. If Timing is ExternallyTimed, the queued subtitle will remain in the queue until manually removed. If the subtitle asset has a non-zero StartOffset, it will sit in a delayed-start queue instead of being queued for display.
- L56 _public prototype_ `virtual void QueueSubtitleFromSoundWaveName(const FName& SoundName, const FName& PackageName, const float Duration);` — Metasounds may reference a soundwave, but can only really provide the sound's name from the audio thread.
- L59 _public prototype_ `virtual bool IsSubtitleActive(FSubtitleAssetData Data) const;` — Returns true if the given subtitle asset is being displayed.
- L62 _public prototype_ `virtual void StopSubtitle(FSubtitleAssetData Data);` — Stops the given subtitle asset being displayed.  This includes subtitles not yet being displayed due to their StartOffset
- L65 _public prototype_ `virtual void StopAllSubtitles();` — Stops all queued subtitles from being displayed.  This includes subtitles not yet being displayed due to their StartOffset.
- L68 _public prototype_ `virtual void ReplaceWidget(const TSoftClassPtr<USubtitleWidget>& NewWidgetAsset);` — Replaces the Subtitle Widget with a new asset subclassed from the base USubtitleWidget. Used by the Replace Subtitle Widget BP function.
- L72 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L73 _protected prototype_ `virtual void Deinitialize() override;`
- L74 _protected prototype_ `virtual void BindDelegates();`
- L75 _protected prototype_ `virtual void UnbindDelegates();`
- L78 _protected member_ `TMap<ESubtitleType, FSlateFontInfo> SubtitleFontInfo;` — `UPROPERTY()`
- L82 _protected member_ `TArray<FActiveSubtitleAssetData> ActiveSubtitles;` — `UPROPERTY()` — Sorted by priority, desc
- L86 _protected member_ `TArray<FActiveSubtitleAssetData> DelayedSubtitles;` — `UPROPERTY()` — Unsorted; subtitles with a delayed start offset still need to be tracked before entering the queue proper.
- L89 _protected prototype_ `virtual void AddActiveSubtitle(const FSubtitleAssetData& Subtitle, float Duration, const float StartOffset, const ESubtitleTiming Timing);`
- L91 _protected prototype_ `virtual void FindAndQueueSubtitleFromSoundName(const FName& SoundName, const FName& PackageName, const float Duration);`
- L95 _protected prototype_ `virtual void MakeDelayedSubtitleActive(const FSubtitleAssetData& Subtitle, const ESubtitleTiming Timing);` — `UFUNCTION()` — These need to be UFUNCTIONs for the Timer Delegate bindings.
- L98 _protected prototype_ `virtual void RemoveActiveSubtitle(const FSubtitleAssetData& Subtitle);` — `UFUNCTION()`
- L101 _private prototype_ `void AddAndDisplaySubtitle(FActiveSubtitleAssetData& NewActiveSubtitle);`
- L104 _public prototype_ `TWeakObjectPtr<USubtitleWidget> GetActiveSubtitleWidget() const;`
- L108 _public function_ `const TArray<FActiveSubtitleAssetData>& GetActiveSubtitles() const` — GetActiveSubtitles returns the sorted array of queued subtitles. Higher priorities are earlier in the array. For equally-prioritized subtitles, the oldest one is first in this array.
- L115 _private member_ `TObjectPtr<UViewportWidgetOverlay> ViewportWidget = nullptr;` — `UPROPERTY(Transient)`
- L117 _private member_ `bool bInitializedWidget = false;`
- L118 _private member_ `IAssetRegistry* AssetRegistry = nullptr;`
- L119 _private prototype_ `bool TryCreateUMGWidgetFromAsset(const TSoftClassPtr<USubtitleWidget>& WidgetToUse);`
- L120 _private prototype_ `bool TryCreateUMGWidget();`
- L121 _private prototype_ `void UpdateWidgetData();`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API SUBTITLESANDCLOSEDCAPTIONS_API`
- L25 _namespace_ `namespace SubtitlesAndClosedCaptions`
- L25 _namespace_ `namespace Test` (scope `SubtitlesAndClosedCaptions`)
