# Plugins / LiveLinkSequencer

- module root: `Plugins/Animation/LiveLink/Source/LiveLinkSequencer`
- headers: 7; symbols: 104
- symbol kinds: class=8, delegate=1, function=11, macro=3, member=30, prototype=50, struct=1
- PrivateDependencyModuleNames: EditorFramework, HeadMountedDisplay, LevelSequence, LiveLink, MovieSceneTools, MovieSceneTracks, Projects, SequenceRecorder, Sequencer, SerializedRecorderInterface, Slate, SlateCore, TakeMovieScene, TakeRecorder, TakeRecorderSources, TakesCore, TargetPlatform, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, LiveLinkComponents, LiveLinkInterface, LiveLinkMovieScene, MovieScene, TakeTrackRecorders

### `Plugins/Animation/LiveLink/Source/LiveLinkSequencer/Private/LiveLinkSequencerPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkSequencer, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkSequencer, Log, All);`

### `Plugins/Animation/LiveLink/Source/LiveLinkSequencer/Private/Sequencer/LiveLinkPropertyTrackEditor.h` (Private)


#### class `FLiveLinkPropertyTrackEditor`  
`class FLiveLinkPropertyTrackEditor : public FKeyframeTrackEditor<UMovieSceneLiveLinkTrack>`  
_L11-47_
- inherits: `FKeyframeTrackEditor<UMovieSceneLiveLinkTrack>`
- desc: A property track editor for Live Link properties.
- L16 _public function_ `FLiveLinkPropertyTrackEditor(TSharedRef<ISequencer> InSequencer) : FKeyframeTrackEditor<UMovieSceneLiveLinkTrack>(InSequencer)`
- L27 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L32 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerTrackEditor interface
- L34 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L36 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L37 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L38 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L39 _public prototype_ `virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;`
- L40 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L45 _protected prototype_ `void HandleAddLiveLinkTrackMenuEntryExecute();` — Callback for executing the "Add Live Link" menu entry.
- L46 _protected prototype_ `bool HandleAddLiveLinkTrackMenuEntryCanExecute() const;`

### `Plugins/Animation/LiveLink/Source/LiveLinkSequencer/Private/TakeRecorderSource/TakeRecorderLiveLinkSource.h` (Private)


#### struct `FLiveLinkSubjectProperty`  
`struct FLiveLinkSubjectProperty`  
_L11-32_
- reflection: `USTRUCT(BlueprintType)`
- L15 _public function_ `FLiveLinkSubjectProperty() : SubjectName(NAME_None) , bEnabled(true)`
- L21 _public function_ `FLiveLinkSubjectProperty(const FName& InName, const bool bInEnabled)`
- L28 _public member_ `FName SubjectName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subjects")`
- L31 _public member_ `bool bEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subjects")`

#### class `ULiveLinkSubjectProperties`  
`class ULiveLinkSubjectProperties : public UObject`  
_L36-44_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L43 _public member_ `TArray<FLiveLinkSubjectProperty> Properties;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subjects")`

#### class `UTakeRecorderLiveLinkSource`  
`class UTakeRecorderLiveLinkSource : public UTakeRecorderSource`  
_L48-103_
- reflection: `UCLASS(Category="Live Link", config=EditorSettings)`
- inherits: `UTakeRecorderSource`
- desc: A recording source that records LiveLink
- L54 _public prototype_ `UTakeRecorderLiveLinkSource(const FObjectInitializer& ObjInit);`
- L58 _public member_ `bool bReduceKeys;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Live Link Source")` — Whether to perform key-reduction algorithms as part of the recording
- L62 _public member_ `FName SubjectName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subjects")` — Name of the subject to record
- L66 _public member_ `bool bSaveSubjectSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subjects")` — Whether we should save subject settings in the the live link section. If not, we'll create one with subject information with no settings
- L73 _public member_ `bool bUseSourceTimecode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subjects")` — Whether the livelink subject's timecode or the system time should be used for the recording. @note If set, the livelink subject's timecode will be used even if it does not match the engine timecode.
- L77 _public member_ `bool bDiscardSamplesBeforeStart;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subjects", meta=(EditCondition = bUseSourceTimecode))` — If true discard livelink samples with timecode that occurs before the start of recording
- L83 _public member_ `TObjectPtr<UMovieSceneLiveLinkTrackRecorder> TrackRecorder;` — `UPROPERTY()` — The track recorder we created.
- L88 _private prototype_ `virtual TArray<UTakeRecorderSource*> PreRecording(ULevelSequence* InSequence, FMovieSceneSequenceID InSequenceID, ULevelSequence* InRootSequence, FManifestSerializer* InManifestSerializer) override;` — UTakeRecorderSource
- L89 _private prototype_ `virtual void StartRecording(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame, class ULevelSequence* InSequence) override;`
- L90 _private prototype_ `virtual void TickRecording(const FQualifiedFrameTime& CurrentSequenceTime) override;`
- L91 _private prototype_ `virtual void StopRecording(class ULevelSequence* InSequence) override;`
- L92 _private prototype_ `virtual TArray<UTakeRecorderSource*> PostRecording(class ULevelSequence* InSequence, class ULevelSequence* InRootSequence, const bool bCancelled) override;`
- L94 _private prototype_ `virtual FText GetDisplayTextImpl() const override;`
- L95 _private prototype_ `virtual void AddContentsToFolder(class UMovieSceneFolder* InFolder) override;`
- L96 _private prototype_ `virtual bool CanAddSource(UTakeRecorderSources* InSources) const override;`
- L97 _private function_ `virtual bool SupportsSubscenes() const override`
- L98 _private prototype_ `virtual FString GetSubsceneTrackName(ULevelSequence* InSequence) const override;`
- L99 _private prototype_ `virtual FString GetSubsceneAssetName(ULevelSequence* InSequence) const override;`
- L100 _private prototype_ `virtual FText GetAddSourceDisplayTextImpl() const override;`

### `Plugins/Animation/LiveLink/Source/LiveLinkSequencer/Public/LiveLinkSequencerSettings.h` (Public)


#### class `ULiveLinkSequencerSettings`  
`class ULiveLinkSequencerSettings : public UDeveloperSettings`  
_L21-39_
- reflection: `UCLASS(MinimalAPI, config=Game)`
- inherits: `UDeveloperSettings`
- desc: Settings for LiveLink Sequence Editor
- L27 _public prototype_ `virtual FName GetCategoryName() const;`
- L29 _public prototype_ `virtual FText GetSectionText() const override;`
- L30 _public prototype_ `virtual FName GetSectionName() const override;`
- L38 _public member_ `TMap<TSubclassOf<ULiveLinkControllerBase>, TSubclassOf<UMovieSceneLiveLinkControllerTrackRecorder>> DefaultTrackRecordersForController;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLink", meta = (AllowAbstract = "false"))` — Default Track Recorder class to use for the specified LiveLink controller

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LIVELINKSEQUENCER_API`

### `Plugins/Animation/LiveLink/Source/LiveLinkSequencer/Public/MovieSceneLiveLinkControllerMapTrackRecorder.h` (Public)


#### class `FMovieSceneLiveLinkControllerMapTrackRecorderFactory`  
`class FMovieSceneLiveLinkControllerMapTrackRecorderFactory : public IMovieSceneTrackRecorderFactory`  
_L17-31_
- inherits: `IMovieSceneTrackRecorderFactory`
- desc: Movie Scene track recorder factory for the LiveLink Component's Controller Map
- L20 _public prototype_ `virtual ~FMovieSceneLiveLinkControllerMapTrackRecorderFactory() = default;`
- L23 _public function_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override`
- L24 _public prototype_ `virtual bool CanRecordProperty(class UObject* InObjectToRecord, class FProperty* InPropertyToRecord) const override;`
- L26 _public prototype_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForObject() const override;`
- L27 _public function_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForProperty(UObject* InObjectToRecord, const FName& InPropertyToRecord) const override`
- L29 _public function_ `virtual FText GetDisplayName() const override`

#### class `UMovieSceneLiveLinkControllerMapTrackRecorder`  
`class UMovieSceneLiveLinkControllerMapTrackRecorder : public UMovieSceneTrackRecorder`  
_L35-57_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieSceneTrackRecorder`
- desc: Movie Scene track recorder for LiveLink Component's Controller Map
- L39 _public prototype_ `virtual ~UMovieSceneLiveLinkControllerMapTrackRecorder() = default;`
- L42 _public prototype_ `virtual void CreateTrackImpl() override;`
- L43 _public prototype_ `virtual void SetSectionStartTimecodeImpl(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame) override;`
- L44 _public prototype_ `virtual void RecordSampleImpl(const FQualifiedFrameTime& CurrentTime) override;`
- L45 _public prototype_ `virtual void StopRecordingImpl() override;`
- L46 _public prototype_ `virtual void FinalizeTrackImpl() override;`
- L51 _private prototype_ `TSubclassOf<UMovieSceneLiveLinkControllerTrackRecorder> GetRecorderClassForLiveLinkController(const TSubclassOf<ULiveLinkControllerBase> ControllerClass);` — Return the desired track recorder class that supports the input LiveLink controller class
- L56 _private member_ `TArray<TObjectPtr<UMovieSceneLiveLinkControllerTrackRecorder>> ControllerRecorders;` — `UPROPERTY(Transient)` — Array of track recorders that will record each of the LiveLink controller's in the Controller Map

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LIVELINKSEQUENCER_API`

### `Plugins/Animation/LiveLink/Source/LiveLinkSequencer/Public/MovieSceneLiveLinkControllerTrackRecorder.h` (Public)


#### class `UMovieSceneLiveLinkControllerTrackRecorder`  
`class UMovieSceneLiveLinkControllerTrackRecorder : public UMovieSceneTrackRecorder`  
_L13-28_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UMovieSceneTrackRecorder`
- desc: Abstract based for movie scene track recorders that can record LiveLink Controllers
- L19 _public prototype_ `virtual bool IsLiveLinkControllerSupported(const TSubclassOf<ULiveLinkControllerBase>& ControllerToSupport) const PURE_VIRTUAL(UMovieSceneLiveLinkControllerTrackRecorder::IsLiveLinkControllerSupported, return false;);` — Returns true if this track recorder class supports the input LiveLink controller class, false otherwise
- L22 _public function_ `void SetLiveLinkController(ULiveLinkControllerBase* InLiveLinkController)` — Set the LiveLink controller object that this track recorder will record properties from
- L27 _protected member_ `TObjectPtr<ULiveLinkControllerBase> LiveLinkControllerToRecord;` — `UPROPERTY(Transient)` — The LiveLink controller that this track record will record properties from

### `Plugins/Animation/LiveLink/Source/LiveLinkSequencer/Public/MovieSceneLiveLinkTrackRecorder.h` (Public)


#### class `UMovieSceneLiveLinkTrackRecorder`  
`class UMovieSceneLiveLinkTrackRecorder : public UMovieSceneTrackRecorder`  
_L27-115_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieSceneTrackRecorder`
- L31 _public prototype_ `virtual ~UMovieSceneLiveLinkTrackRecorder() = default;`
- L34 _public prototype_ `virtual void RecordSampleImpl(const FQualifiedFrameTime& CurrentTime) override;` — UMovieSceneTrackRecorder Interface
- L35 _public prototype_ `virtual void FinalizeTrackImpl() override;`
- L36 _public prototype_ `virtual void SetSectionStartTimecodeImpl(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame) override;`
- L37 _public function_ `virtual UMovieSceneSection* GetMovieSceneSection() const override`
- L38 _public prototype_ `virtual void StopRecordingImpl() override;`
- L39 _public function_ `virtual void SetSavedRecordingDirectory(const FString& InDirectory)`
- L43 _public prototype_ `virtual bool LoadRecordedFile(const FString& InFileName, UMovieScene *InMovieScene, TMap<FGuid, AActor*>& ActorGuidToActorMap, TFunction<void()> InCompletionCallback) override;`
- L48 _public prototype_ `void CreateTrack(UMovieScene* InMovieScene, const FName& InSubjectName, bool bInSaveSubjectSettings, bool bInAlwaysUseTimecode, bool bDiscardSamplesBeforeStart, UMovieSceneTrackRecorderSettings* InSettingsObject);` — we don't call UMovieSceneTrackRecorder::CreateTrack or CreateTrackImpl since that expects an  ObjectToRecord and a GUID which isn't needed.
- L49 _public prototype_ `void AddContentsToFolder(UMovieSceneFolder* InFolder);`
- L50 _public function_ `void SetReduceKeys(bool bInReduce)`
- L53 _public prototype_ `void ProcessRecordedTimes(ULevelSequence *InLevelSequence);` — Tell the recorder to write the take track using the recorded times.
- L56 _private prototype_ `UMovieSceneLiveLinkTrack* DoesLiveLinkTrackExist(const FName& TrackName, const TSubclassOf<ULiveLinkRole>& InTrackRole);`
- L58 _private prototype_ `void CreateTracks();`
- L60 _private prototype_ `void OnStaticDataReceived(FLiveLinkSubjectKey InSubjectKey, TSubclassOf<ULiveLinkRole> InSubjectRole, const FLiveLinkStaticDataStruct& InStaticData);`
- L61 _private prototype_ `void OnFrameDataReceived(FLiveLinkSubjectKey InSubjectKey, TSubclassOf<ULiveLinkRole> InSubjectRole, const FLiveLinkFrameDataStruct& InFrameData);`
- L65 _private member_ `FName SubjectName;` — Name of Subject To Record
- L68 _private member_ `bool bSaveSubjectSettings;` — Whether we should save subject preset in the the live link section. If not, we'll create one with subject information with no settings
- L71 _private member_ `bool bUseSourceTimecode;` — Whether or not we use timecode time or world time
- L74 _private member_ `bool bDiscardSamplesBeforeStart;` — Whether to discard livelink samples with timecode that occurs before the start of recording
- L77 _private member_ `TSubclassOf<ULiveLinkRole> SubjectRole;` — Role of the subject we will record
- L80 _private member_ `TWeakObjectPtr<UMovieSceneLiveLinkTrack> LiveLinkTrack;` — Cached LiveLink Tracks, section per each maps to SubjectNames
- L83 _private member_ `TWeakObjectPtr<UMovieSceneLiveLinkSection> MovieSceneSection;` — Sections to record to on each track
- L87 _private member_ `double SecondsDiff;` — Diff between Engine Time from when starting to record and Platform Time which is used by Live Link. Still used if no TimeCode present.
- L90 _private member_ `FFrameNumber RecordStartFrame;` — The frame at the start of this recording section
- L93 _private member_ `FGuid HandlerGuid;` — Guid when registered to get LiveLinkData
- L96 _private member_ `FString Directory;` — Cached directory for serializers to save to
- L99 _private member_ `bool bReduceKeys;` — Cached Key Reduction from Live Link Source Properties
- L102 _private member_ `bool bIsVirtualSubject = false;` — Whether the Subject is Virtual or not
- L105 _private member_ `bool bRecordTimecode = false;` — Should we record timecode data.
- L108 _private member_ `FDelegateHandle OnStaticDataReceivedHandle;` — Delegates registered during recording to receive live link data as it comes in
- L109 _private member_ `FDelegateHandle OnFrameDataReceivedHandle;`
- L111 _private member_ `TArray<FLiveLinkFrameDataStruct> FramesToProcess;`
- L114 _private member_ `TArray<TPair<FQualifiedFrameTime, FQualifiedFrameTime>> RecordedTimes;` — Pairs of recorded times with the corresponding timecode.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LIVELINKSEQUENCER_API`
