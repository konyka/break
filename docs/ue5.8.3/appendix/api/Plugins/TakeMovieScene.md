# Plugins / TakeMovieScene

- module root: `Plugins/VirtualProduction/Takes/Source/TakeMovieScene`
- headers: 7; symbols: 65
- symbol kinds: class=5, function=4, member=28, namespace=2, prototype=23, struct=3
- PrivateDependencyModuleNames: Core, CoreUObject
- PublicDependencyModuleNames: Engine, MovieScene, MovieSceneTracks

### `Plugins/VirtualProduction/Takes/Source/TakeMovieScene/Public/Hitching/FrameHitchData.h` (Public)


#### struct `UE::TakeMovieScene::FFrameHitchData`  
`struct FFrameHitchData`  
_L9-15_
- L12 _public member_ `FTimecode TargetTimecode;` — The timecode frame engine was supposed to have.
- L14 _public member_ `FTimecode ActualTimecode;` — The timecode the frame actually had.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace TakeMovieScene` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeMovieScene/Public/Hitching/FrameHitchSceneDecoration.h` (Public)


#### class `UFrameHitchSceneDecoration`  
`class UFrameHitchSceneDecoration : public UObject`  
_L17-42_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: This decoration contain stores a target and actual FTimecode for each frame for the purposes of detecting whether the engine was running behind, i.e. was hitching, on a previous frame during take recording. This data can be used to visualize hitches in the Sequencer UI.
- L24 _public member_ `FTakeMovieSceneHitchTimecodeCurves TargetTimecode;` — `UPROPERTY()` — Target timecode that the frame was supposed to have
- L27 _public member_ `FTakeMovieSceneHitchTimecodeCurves ActualTimecode;` — `UPROPERTY()` — Actual timecode that was recorded
- L31 _public member_ `FFrameRate TimecodeProviderFrameRate;` — `UPROPERTY()` — The frame rate the timecode provider was set up with. Determines the number of frames per second in TargetTimecode & ActualTimecode.
- L38 _public member_ `FFrameRate RecordFrameRate;` — `UPROPERTY()` — The frame rate Take Recorder was set up with. Users may (intentionally) set up the provider and sequencer to record at different rates. This information is important for analyzing hitches later as it affects the timecode we should expect each frame.
- L41 _public prototype_ `TOptional<UE::TakeMovieScene::FFrameHitchData> Evaluate(const FFrameTime& InFrameTime) const;` — Evaluates the curve data at the specified time.

### `Plugins/VirtualProduction/Takes/Source/TakeMovieScene/Public/Hitching/TimecodeHitchChannels.h` (Public)


#### struct `FTakeMovieSceneHitchTimecodeCurves`  
`struct FTakeMovieSceneHitchTimecodeCurves`  
_L11-36_
- reflection: `USTRUCT()`
- L17 _public member_ `FMovieSceneIntegerChannel HoursCurve;` — `UPROPERTY()` — Hours curve data
- L20 _public member_ `FMovieSceneIntegerChannel MinutesCurve;` — `UPROPERTY()` — Minutes curve data
- L23 _public member_ `FMovieSceneIntegerChannel SecondsCurve;` — `UPROPERTY()` — Seconds curve data
- L26 _public member_ `FMovieSceneIntegerChannel FramesCurve;` — `UPROPERTY()` — Frames curve data
- L29 _public prototype_ `void Set(TArray<FFrameNumber> Times, TArray<int32> Hours, TArray<int32> Minutes, TArray<int32> Seconds, TArray<int32> Frames);` — Sets the curve content from the given arrays - which must be equal size.
- L32 _public prototype_ `TOptional<FTimecode> Evaluate(const FFrameTime& InFrameTime) const;` — @return The timecode at the frame time.
- L35 _public prototype_ `TConstArrayView<FFrameNumber> GetFrameTimes() const;` — @return Gets all the frame times at which we recorded.

### `Plugins/VirtualProduction/Takes/Source/TakeMovieScene/Public/MovieSceneTakeSection.h` (Public)


#### class `UMovieSceneTakeSection`  
`class UMovieSceneTakeSection : public UMovieSceneSection`  
_L18-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- desc: A section in a Take track
- L26 _public prototype_ `virtual void PostEditImport() override;`
- L32 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;` — Overloaded serializer to ensure that the channel proxy is updated correctly on load and duplicate
- L37 _private prototype_ `void ReconstructChannelProxy();`
- L49 _public prototype_ `TOptional<FSectionData> Evaluate(FFrameTime InTime) const;` — Evaluate the curve data at the specified time and form a timecode / rate and slate values. If any curves failed to evaluate then the optional will be unset.
- L53 _public member_ `FMovieSceneIntegerChannel HoursCurve;` — `UPROPERTY()` — Hours curve data
- L57 _public member_ `FMovieSceneIntegerChannel MinutesCurve;` — `UPROPERTY()` — Minutes curve data
- L61 _public member_ `FMovieSceneIntegerChannel SecondsCurve;` — `UPROPERTY()` — Seconds curve data
- L65 _public member_ `FMovieSceneIntegerChannel FramesCurve;` — `UPROPERTY()` — Frames curve data
- L69 _public member_ `FMovieSceneFloatChannel SubFramesCurve;` — `UPROPERTY()` — Subframes curve data
- L73 _public member_ `FMovieSceneFloatChannel RateCurve;` — `UPROPERTY()` — Timecode rate curve data
- L77 _public member_ `FMovieSceneStringChannel Slate;` — `UPROPERTY()` — Slate data

#### struct `UMovieSceneTakeSection::FSectionData`  
`struct FSectionData`  
_L41-46_
- L43 _public member_ `FTimecode Timecode;`
- L44 _public member_ `FString Slate;`
- L45 _public member_ `float Rate = 24.0f;`

### `Plugins/VirtualProduction/Takes/Source/TakeMovieScene/Public/MovieSceneTakeSettings.h` (Public)


#### class `UMovieSceneTakeSettings`  
`class UMovieSceneTakeSettings : public UObject`  
_L12-50_
- reflection: `UCLASS(config=EditorSettings, MinimalAPI)`
- inherits: `UObject`
- desc: Universal take recorder settings that apply to a whole take
- L17 _public prototype_ `UMovieSceneTakeSettings();`
- L20 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L25 _public member_ `FString HoursName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder")` — Hours Name
- L29 _public member_ `FString MinutesName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder")` — Minutes Name
- L33 _public member_ `FString SecondsName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder")` — Seconds Name
- L37 _public member_ `FString FramesName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder")` — Frames Name
- L41 _public member_ `FString SubFramesName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder")` — SubFrames Name
- L45 _public member_ `FString RateName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder")` — Rate Name
- L49 _public member_ `FString SlateName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder")` — Slate Name

### `Plugins/VirtualProduction/Takes/Source/TakeMovieScene/Public/MovieSceneTakeTrack.h` (Public)


#### class `UMovieSceneTakeTrack`  
`class UMovieSceneTakeTrack : public UMovieSceneNameableTrack`  
_L14-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- desc: Handles manipulation of takes in a movie scene
- L20 _public prototype_ `UMovieSceneTakeTrack(const FObjectInitializer& Init);`
- L23 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;` — UMovieSceneTrack interface
- L24 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L25 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L26 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L27 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L28 _public prototype_ `virtual bool IsEmpty() const override;`
- L29 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L30 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L31 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L34 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L35 _public function_ `virtual bool CanRename() const`
- L41 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()` — The track's sections.

### `Plugins/VirtualProduction/Takes/Source/TakeMovieScene/Public/TakeMovieSceneModule.h` (Public)


#### class `FTakeMovieSceneModule`  
`class FTakeMovieSceneModule : public IModuleInterface`  
_L12-41_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L15 _public function_ `FTakeMovieSceneModule()`
- L17 _public prototype_ `virtual void StartupModule();`
- L18 _public prototype_ `virtual void ShutdownModule();`
- L26 _public function_ `static inline FTakeMovieSceneModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L36 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
