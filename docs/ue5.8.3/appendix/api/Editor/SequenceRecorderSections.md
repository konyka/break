# Editor / SequenceRecorderSections

- module root: `Source/Editor/SequenceRecorderSections`
- headers: 5; symbols: 71
- symbol kinds: class=9, function=19, member=20, prototype=22, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, MovieScene, MovieSceneTracks, SequenceRecorder, TimeManagement

### `Source/Editor/SequenceRecorderSections/Public/MovieScene3DAttachSectionRecorder.h` (Public)


#### class `FMovieScene3DAttachSectionRecorderFactory`  
`class FMovieScene3DAttachSectionRecorderFactory : public IMovieSceneSectionRecorderFactory`  
_L20-27_
- inherits: `IMovieSceneSectionRecorderFactory`
- L23 _public function_ `virtual ~FMovieScene3DAttachSectionRecorderFactory()`
- L25 _public prototype_ `virtual TSharedPtr<IMovieSceneSectionRecorder> CreateSectionRecorder(const struct FActorRecordingSettings& InActorRecordingSettings) const override;`
- L26 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override;`

#### class `FMovieScene3DAttachSectionRecorder`  
`class FMovieScene3DAttachSectionRecorder : public IMovieSceneSectionRecorder`  
_L29-67_
- inherits: `IMovieSceneSectionRecorder`
- L32 _public function_ `virtual ~FMovieScene3DAttachSectionRecorder()`
- L34 _public prototype_ `virtual void CreateSection(UObject* InObjectToRecord, class UMovieScene* InMovieScene, const FGuid& Guid, float Time) override;`
- L35 _public prototype_ `virtual void FinalizeSection(float CurrentTime) override;`
- L36 _public prototype_ `virtual void Record(float CurrentTime) override;`
- L37 _public function_ `virtual void InvalidateObjectToRecord() override`
- L41 _public function_ `virtual UObject* GetSourceObject() const override`
- L48 _private member_ `TWeakObjectPtr<class AActor> ActorToRecord;` — Object to record from
- L51 _private member_ `TWeakObjectPtr<class UMovieScene3DAttachSection> MovieSceneSection;` — Section to record to
- L54 _private member_ `TWeakObjectPtr<class UMovieScene3DAttachTrack> AttachTrack;` — Track we are recording to
- L57 _private member_ `TWeakObjectPtr<class UMovieScene> MovieScene;` — Movie scene we are recording to
- L60 _private member_ `TWeakObjectPtr<class AActor> ActorAttachedTo;` — Track the actor we are attached to
- L63 _private member_ `FGuid ObjectGuid;` — Identifier of the object we are recording
- L66 _private member_ `FMovieSceneTimecodeSource TimecodeSource;` — The timecode source at the beginning of recording

### `Source/Editor/SequenceRecorderSections/Public/MovieSceneParticleTrackSectionRecorder.h` (Public)


#### class `FMovieSceneParticleTrackSectionRecorderFactory`  
`class FMovieSceneParticleTrackSectionRecorderFactory : public IMovieSceneSectionRecorderFactory`  
_L16-23_
- inherits: `IMovieSceneSectionRecorderFactory`
- L19 _public function_ `virtual ~FMovieSceneParticleTrackSectionRecorderFactory()`
- L21 _public prototype_ `virtual TSharedPtr<IMovieSceneSectionRecorder> CreateSectionRecorder(const struct FActorRecordingSettings& InActorRecordingSettings) const override;`
- L22 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override;`

#### class `UMovieSceneParticleTrackSectionRecorder`  
`class UMovieSceneParticleTrackSectionRecorder : public UObject`  
_L26-40_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable)`
- inherits: `UObject`
- L31 _public function_ `UMovieSceneParticleTrackSectionRecorder() : SectionRecorder(nullptr)`
- L37 _public prototype_ `void OnTriggered(UParticleSystemComponent* Component, bool bActivating);` — `UFUNCTION()`
- L39 _public member_ `FMovieSceneParticleTrackSectionRecorder* SectionRecorder;`

#### struct `FMovieSceneParticleTrackSectionRecorder`  
`struct FMovieSceneParticleTrackSectionRecorder : public IMovieSceneSectionRecorder`  
_L42-83_
- inherits: `IMovieSceneSectionRecorder`
- L47 _public function_ `FMovieSceneParticleTrackSectionRecorder() : SystemToRecord(nullptr) , MovieSceneSection(nullptr) , bWasTriggered(false) , PreviousState(EParticleKey::Activate) , DelegateProxy(nullptr)`
- L57 _public prototype_ `virtual ~FMovieSceneParticleTrackSectionRecorder();`
- L59 _public prototype_ `virtual void CreateSection(UObject* InObjectToRecord, class UMovieScene* MovieScene, const FGuid& Guid, float Time) override;`
- L60 _public prototype_ `virtual void FinalizeSection(float CurrentTime) override;`
- L61 _public prototype_ `virtual void Record(float CurrentTime) override;`
- L62 _public function_ `virtual void InvalidateObjectToRecord() override`
- L66 _public function_ `virtual UObject* GetSourceObject() const override`
- L73 _private member_ `TWeakObjectPtr<class UParticleSystemComponent> SystemToRecord;` — Object to record from
- L76 _private member_ `TWeakObjectPtr<class UMovieSceneParticleSection> MovieSceneSection;` — Section to record to
- L78 _private member_ `bool bWasTriggered;`
- L80 _private member_ `EParticleKey PreviousState;`
- L82 _private member_ `TWeakObjectPtr<UMovieSceneParticleTrackSectionRecorder> DelegateProxy;`

### `Source/Editor/SequenceRecorderSections/Public/MovieSceneSpawnSectionRecorder.h` (Public)


#### class `FMovieSceneSpawnSectionRecorderFactory`  
`class FMovieSceneSpawnSectionRecorderFactory : public IMovieSceneSectionRecorderFactory`  
_L16-23_
- inherits: `IMovieSceneSectionRecorderFactory`
- L19 _public function_ `virtual ~FMovieSceneSpawnSectionRecorderFactory()`
- L21 _public prototype_ `virtual TSharedPtr<IMovieSceneSectionRecorder> CreateSectionRecorder(const struct FActorRecordingSettings& InActorRecordingSettings) const override;`
- L22 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override;`

#### class `FMovieSceneSpawnSectionRecorder`  
`class FMovieSceneSpawnSectionRecorder : public IMovieSceneSectionRecorder`  
_L25-50_
- inherits: `IMovieSceneSectionRecorder`
- L28 _public function_ `virtual ~FMovieSceneSpawnSectionRecorder()`
- L30 _public prototype_ `virtual void CreateSection(UObject* InObjectToRecord, class UMovieScene* MovieScene, const FGuid& Guid, float Time) override;`
- L31 _public prototype_ `virtual void FinalizeSection(float CurrentTime) override;`
- L32 _public prototype_ `virtual void Record(float CurrentTime) override;`
- L33 _public function_ `virtual void InvalidateObjectToRecord() override`
- L37 _public function_ `virtual UObject* GetSourceObject() const override`
- L44 _private member_ `TWeakObjectPtr<UObject> ObjectToRecord;` — Object to record from
- L47 _private member_ `TWeakObjectPtr<class UMovieSceneBoolSection> MovieSceneSection;` — Section to record to
- L49 _private member_ `bool bWasSpawned;`

### `Source/Editor/SequenceRecorderSections/Public/MovieSceneVisibilitySectionRecorder.h` (Public)


#### class `FMovieSceneVisibilitySectionRecorderFactory`  
`class FMovieSceneVisibilitySectionRecorderFactory : public IMovieSceneSectionRecorderFactory`  
_L21-29_
- inherits: `IMovieSceneSectionRecorderFactory`
- L24 _public function_ `virtual ~FMovieSceneVisibilitySectionRecorderFactory()`
- L26 _public prototype_ `virtual TSharedPtr<IMovieSceneSectionRecorder> CreateSectionRecorder(const struct FActorRecordingSettings& InActorRecordingSettings) const override;`
- L27 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override;`
- L28 _public function_ `virtual UObject* CreateSettingsObject(class UObject* InOuter) const override`

#### class `FMovieSceneVisibilitySectionRecorder`  
`class FMovieSceneVisibilitySectionRecorder : public IMovieSceneSectionRecorder`  
_L31-57_
- inherits: `IMovieSceneSectionRecorder`
- L34 _public function_ `virtual ~FMovieSceneVisibilitySectionRecorder()`
- L36 _public prototype_ `virtual void CreateSection(UObject* InObjectToRecord, class UMovieScene* MovieScene, const FGuid& Guid, float Time) override;`
- L37 _public prototype_ `virtual void FinalizeSection(float CurrentTime) override;`
- L38 _public prototype_ `virtual void Record(float CurrentTime) override;`
- L39 _public function_ `virtual void InvalidateObjectToRecord() override`
- L43 _public function_ `virtual UObject* GetSourceObject() const override`
- L50 _private member_ `TWeakObjectPtr<class UObject> ObjectToRecord;` — Object to record from
- L53 _private member_ `TWeakObjectPtr<class UMovieSceneBoolSection> MovieSceneSection;` — Section to record to
- L56 _private member_ `bool bWasVisible;` — Flag used to track visibility state and add keys when this changes

### `Source/Editor/SequenceRecorderSections/Public/MovieSceneVisibilitySectionRecorderSettings.h` (Public)


#### class `UMovieSceneVisibilitySectionRecorderSettings`  
`class UMovieSceneVisibilitySectionRecorderSettings : public UObject`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UObject`
- L16 _public function_ `UMovieSceneVisibilitySectionRecorderSettings() : bRecordVisibility(true)`
- L22 _public member_ `bool bRecordVisibility;` — `UPROPERTY(EditAnywhere, Category = "Actor Recording")` — Whether to record actor visibility.
