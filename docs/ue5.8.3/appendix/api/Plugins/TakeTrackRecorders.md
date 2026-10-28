# Plugins / TakeTrackRecorders

- module root: `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders`
- headers: 15; symbols: 359
- symbol kinds: class=24, delegate=3, enum=1, enumerator=4, function=97, macro=9, member=99, namespace=7, prototype=110, struct=5
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, LevelSequence, MovieScene, MovieSceneTracks, SequenceRecorder, SequenceRuntimeRecorder, Sequencer, SerializedRecorderInterface, TakesCore, TimeManagement, UnrealEd
- PublicDependencyModuleNames: SequenceRuntimeRecorder

### `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Private/TakeTrackRecordersUtils.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TakeTrackRecordersUtils` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::TakeTrackRecordersUtils`)
- L20 _prototype_ `AActor* GetAttachment(AActor* InActor, FName& SocketName, FName& ComponentName);` (scope `UE::TakeTrackRecordersUtils::Private`) — Get the attachment owner of the given actor. @param InActor The actor to find the attachment for. @param SocketName Out name of the socket of the attachment. @param ComponentName Out name of the component of the attachment. @return The attach owning actor.

### `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Public/TrackRecorders/IMovieSceneTrackRecorderFactory.h` (Public)


#### class `IMovieSceneTrackRecorderFactory`  
`class IMovieSceneTrackRecorderFactory : public IModularFeature`  
_L19-96_
- inherits: `IModularFeature`
- desc: Factory class interface that allows the recorder to determine what recorders to apply to actors/components/objects it is presented with.
- L32 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const = 0;` — Check whether an object can be recorded by this section recorder. If so then the actor recorder will call CreateTrackRecorder() to acquire a new instance to use in recording. This should only be implemented for recorders that record something about the Object that isn't tracked via a specific property. It is unlikely (but possible) that a factory should return true for both CanRecordObject and CanRecordProperty. @param	InObjectToRecord	The object to check. @return true if the object can be recorded by this recorder
- L40 _public prototype_ `virtual class UMovieSceneTrackRecorder* CreateTrackRecorderForObject() const = 0;` — Create a track recorder for this factory. Only called if CanRecordObject returns true. Should not return nullptr if CanRecordObject returned true. @return A new property recorder instance.
- L52 _public prototype_ `virtual bool CanRecordProperty(class UObject* InObjectToRecord, class FProperty* InPropertyToRecord) const = 0;` — Check whether or not the specific property on the given object can be recorded. If so, then the actor recorder will call CreateTrackRecorderForProperty to create a new instance to use for recording. This should only be implemented for recorders that record the specific property on the object and claim ownership over recording that property. @param InObjectToRecord - The object to check to see if we can record. @param InPropertyToRecord - The specific property to try and record from that object. @return True if the specific object can be recorded
- L61 _public prototype_ `virtual class UMovieSceneTrackRecorder* CreateTrackRecorderForProperty(UObject* InObjectToRecord, const FName& InPropertyToRecord) const = 0;` — Create a track recorder for this factory. Only called if CanRecordProperty returns true. Should not return nullptr if CanRecordProperty returned true. @return A new property recorder instance.
- L63 _public function_ `virtual class UMovieSceneTrackRecorder* CreateTrackRecorderForCacheTrack(IMovieSceneCachedTrack* CachedTrack, const TObjectPtr<ULevelSequence>& Sequence, const TSharedPtr<ISequencer>& Sequencer) const`
- L70 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Get the human readable display name for the recorder. Used for debugging purposes to help identify which factory is recording a given property. @return Display name for use in the UI for debugging purposes.
- L75 _public function_ `virtual TSubclassOf<UMovieSceneTrackRecorderSettings> GetSettingsClass() const` — Get the settings class for this factory. If this factory is used to record something on an Actor, an instance will be created and passed to created track recorders.
- L80 _public function_ `virtual bool IsSerializable() const` — Whether or not the created section recorder is serializable. If so when it creates a section we will serialize the section's information into a manifest. @return an object used for user settings for this recorder
- L85 _public function_ `virtual FName GetSerializedType() const` — Unique Name that's stored in the serialized manifest when it's recorded
- L90 _public function_ `virtual bool CanHandlePropertyInstance() const` — Allow a factory to handle individual properties on an object, regardless of the property name.
- L95 _public function_ `virtual bool CanCreateTrackRecorderForHost(const IMovieSceneTrackRecorderHost* Host, UObject* ObjectToRecord) const` — Allows a factory to determine if it wants to be created for a given host.

### `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Public/TrackRecorders/IMovieSceneTrackRecorderHost.h` (Public)


#### enum `ETakeRecorderAttachRecordBehaviour`  
`enum class ETakeRecorderAttachRecordBehaviour : uint8`  
_L12-18_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `None UMETA(Tooltip = "Do not record attachments and instead record in world space.")`
- L15 _public enumerator_ `Attachments UMETA(Tooltip = "Do not re-record parents, instead record only an attach track to the parent if it is controlled by a sequence or being recorded.")`
- L16 _public enumerator_ `Hierarchy UMETA(Tooltip = "Record the full parent hierarchy including attachments.")`
- L17 _public enumerator_ `ProjectDefault UMETA(Tooltip = "Use the project settings default value.")`

#### struct `FTakeRecorderPropertyTrackSettings`  
`struct FTakeRecorderPropertyTrackSettings`  
_L21-32_
- reflection: `USTRUCT()`
- L27 _public member_ `FString ComponentPath;` — `UPROPERTY(config, EditAnywhere, Category = PropertyTrack)` — Optional ActorComponent tag (when keying a component property).
- L31 _public member_ `FString PropertyPath;` — `UPROPERTY(config, EditAnywhere, Category = PropertyTrack)` — Path to the keyed property within the Actor or ActorComponent.

#### struct `FTakeRecorderTrackSettings`  
`struct FTakeRecorderTrackSettings`  
_L35-50_
- reflection: `USTRUCT()`
- L41 _public member_ `FSoftClassPath MatchingActorClass;` — `UPROPERTY(config, EditAnywhere, Category = TrackSettings, meta = (MetaClass = "/Script/Engine.Actor"))` — The Actor class to create movie scene tracks for.
- L45 _public member_ `TArray<FTakeRecorderPropertyTrackSettings> DefaultPropertyTracks;` — `UPROPERTY(config, EditAnywhere, Category = TrackSettings)` — List of property names for which movie scene tracks will be created automatically.
- L49 _public member_ `TArray<FTakeRecorderPropertyTrackSettings> ExcludePropertyTracks;` — `UPROPERTY(config, EditAnywhere, Category = TrackSettings)` — List of property names for which movie scene tracks will NOT be created automatically.

#### struct `FTrackRecorderSettings`  
`struct FTrackRecorderSettings`  
_L54-153_
- desc: Generic track recorder settings used by the track recorders
- L56 _public member_ `bool bRecordToPossessable;`
- L57 _public member_ `bool bRemoveRedundantTracks;`
- L58 _public member_ `bool bReduceKeys;`
- L59 _public member_ `bool bSaveRecordedAssets;`
- L60 _public member_ `ETakeRecorderAttachRecordBehaviour AttachRecordBehaviour;`
- L62 _public member_ `float ReduceKeysTolerance;`
- L64 _public member_ `TArray<FTakeRecorderTrackSettings> DefaultTracks;`
- L65 _public member_ `TArray<FString> IncludeAnimationNames;`
- L66 _public member_ `TArray<FString> ExcludeAnimationNames;`
- L67 _public member_ `FTransform TransformOrigin;`
- L69 _public function_ `static bool IsDefaultPropertyTrack(UObject* InObjectToRecord, const FString& InPropertyPath, const TArray<FTakeRecorderTrackSettings>& DefaultTracks)`
- L111 _public function_ `static bool IsExcludePropertyTrack(UObject* InObjectToRecord, const FString& InPropertyPath, const TArray<FTakeRecorderTrackSettings>& DefaultTracks)`

#### class `IMovieSceneTrackRecorderHost`  
`class IMovieSceneTrackRecorderHost`  
_L156-207_
- desc: A class that hosts these track recorders and calls their functions. Allows a recorder to gain some limited context about other recorders.
- L159 _public prototype_ `virtual ~IMovieSceneTrackRecorderHost() = default;`
- L166 _public prototype_ `virtual bool IsOtherActorBeingRecorded(class AActor* OtherActor) const = 0;` — Is the specified actor part of the current recording? This allows us to do some discovery for attachments and hierarchies. @param OtherActor	Actor to check @return True if the specified actor is being recorded by another source.
- L176 _public prototype_ `virtual FGuid GetRecordedActorGuid(class AActor* OtherActor) const = 0;` — Get the object binding for a given actor that is being recorded. An actor can either be a Possessable or a Spawnable but we only have pointers to the original object being recorded. To solve this, we iterate through each actor being recorded and ask it what Guid it ended up with which ends up abstracting away if it's a Spawnable or a Possessable. @param OtherActor Actor to look for. @return A valid guid if the actor is being recorded otherwise an invalid guid.
- L179 _public function_ `virtual ULevelSequence* GetLevelSequence(const AActor* OtherActor)` — Get the level sequence the other actor is coming from.
- L188 _public prototype_ `virtual FMovieSceneSequenceID GetLevelSequenceID(class AActor* OtherActor) = 0;` — Get the sequence id of the level sequence the other actor is coming from. Used for setting cross sequence bindings. @param OtherActor Actor to look for. @return The Sequence ID
- L194 _public prototype_ `virtual FTrackRecorderSettings GetTrackRecorderSettings() const = 0;` — Get generic track recorder settings.
- L200 _public prototype_ `virtual FTransform GetRecordedActorAnimationInitialRootTransform(class AActor* OtherActor) const = 0;` — Returns original transform that may get set when recording a skeletal mesh animation. Needed to correctly transform attached children. @param OtherActor Actor to look for. @return The FTransform applied to the actor when recording animation, that the attached actor may need to apply to themselves to orient correctly.
- L203 _public prototype_ `virtual ULevelSequence* GetRootLevelSequence() const = 0;` — Get the root level sequence being recorded into
- L206 _public prototype_ `virtual FMovieSceneSequenceID GetSequenceID() const = 0;` — /

### `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Public/TrackRecorders/MovieScene3DAttachTrackRecorder.h` (Public)


#### class `FMovieScene3DAttachTrackRecorderFactory`  
`class FMovieScene3DAttachTrackRecorderFactory : public IMovieSceneTrackRecorderFactory`  
_L19-34_
- inherits: `IMovieSceneTrackRecorderFactory`
- L22 _public prototype_ `virtual ~FMovieScene3DAttachTrackRecorderFactory() = default;`
- L24 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override;`
- L25 _public prototype_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForObject() const override;`
- L28 _public function_ `virtual bool CanRecordProperty(class UObject* InObjectToRecord, class FProperty* InPropertyToRecord) const override` — Attachment isn't based on any particular property
- L29 _public function_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForProperty(UObject* InObjectToRecord, const FName& InPropertyToRecord) const override`
- L31 _public prototype_ `virtual bool CanCreateTrackRecorderForHost(const IMovieSceneTrackRecorderHost* Host, UObject* ObjectToRecord) const override;`
- L33 _public function_ `virtual FText GetDisplayName() const override`

#### class `UMovieScene3DAttachTrackRecorder`  
`class UMovieScene3DAttachTrackRecorder : public UMovieSceneTrackRecorder`  
_L37-60_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieSceneTrackRecorder`
- L42 _protected prototype_ `virtual void RecordSampleImpl(const FQualifiedFrameTime& CurrentTime) override;` — UMovieSceneTrackRecorder Interface
- L43 _protected prototype_ `virtual void FinalizeTrackImpl() override;`
- L48 _private member_ `TWeakObjectPtr<class UMovieScene3DAttachSection> MovieSceneSection;` — Section to record to
- L50 _private member_ `FGuid Guid;` — Guid in that section.. todo if more than one section put in arrays
- L53 _private member_ `TWeakObjectPtr<class UMovieScene3DAttachTrack> AttachTrack;` — Track we are recording to
- L56 _private member_ `TWeakObjectPtr<class AActor> ActorAttachedTo;` — Track the actor we are attached to
- L59 _private member_ `TOptional<FMovieSceneSequenceID> CachedTargetSequenceID;` — Cached sequence ID for the attach target when it is not being recorded, set during RecordSampleImpl

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TAKETRACKRECORDERS_API`

### `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Public/TrackRecorders/MovieScene3DTransformTrackRecorder.h` (Public)


#### class `FMovieScene3DTransformTrackRecorderFactory`  
`class FMovieScene3DTransformTrackRecorderFactory : public IMovieSceneTrackRecorderFactory`  
_L31-47_
- inherits: `IMovieSceneTrackRecorderFactory`
- L34 _public prototype_ `virtual ~FMovieScene3DTransformTrackRecorderFactory() = default;`
- L36 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override;`
- L37 _public prototype_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForObject() const override;`
- L40 _public function_ `virtual bool CanRecordProperty(class UObject* InObjectToRecord, class FProperty* InPropertyToRecord) const override` — takerecorder-todo: This should also record "Transform" variable properties, because they can be marked as interp
- L41 _public function_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForProperty(UObject* InObjectToRecord, const FName& InPropertyToRecord) const override`
- L43 _public function_ `virtual FText GetDisplayName() const override`
- L45 _public function_ `virtual bool IsSerializable() const override`
- L46 _public function_ `virtual FName GetSerializedType() const override`

#### struct `UE::TrackRecorders::FBufferedTransformKeys`  
`struct FBufferedTransformKeys`  
_L52-284_
- L55 _public member_ `TArray<FFrameNumber> Times;`
- L56 _public member_ `TArray<double> LocationX, LocationY, LocationZ;`
- L56 _public member_ `TArray<double> LocationX, LocationY, LocationZ;`
- L56 _public member_ `TArray<double> LocationX, LocationY, LocationZ;`
- L57 _public member_ `TArray<double> RotationX, RotationY, RotationZ;`
- L57 _public member_ `TArray<double> RotationX, RotationY, RotationZ;`
- L57 _public member_ `TArray<double> RotationX, RotationY, RotationZ;`
- L58 _public member_ `TArray<double> ScaleX, ScaleY, ScaleZ;`
- L58 _public member_ `TArray<double> ScaleX, ScaleY, ScaleZ;`
- L58 _public member_ `TArray<double> ScaleX, ScaleY, ScaleZ;`
- L60 _public member_ `TArray<FQuat> CachedQuats;` — Currently used only when needed when collapsing when ProcessingAnimation()
- L62 _public function_ `void Add(const FTransform& InTransform, FFrameNumber InKeyTime)`
- L68 _public function_ `void Add(const FTransform& InTransform)`
- L85 _public function_ `void Reset()`
- L93 _public function_ `void Reserve(int32 Num, bool bReserveTime = false)`
- L104 _public function_ `int32 Num() const`
- L108 _public function_ `void CreateCachedQuats()`
- L118 _public function_ `void GetValueFromIndex(int32 CurIndex, FVector& OutLocation, FQuat& OutQuat, FVector& OutScale)`
- L132 _public function_ `float GetU(const FFrameNumber& Time, const FFrameNumber& PrevKeyTime, const FFrameNumber& NextKeyTime)` — normalized 0-1
- L140 _public function_ `void GetValue(const FFrameNumber& Time, int32& CurIndex, FVector& OutLocation, FQuat& OutQuat, FVector& OutScale)` — Get Values at the current Time using linear inteprolation. Uses CurIndex to do the linear search for next Time Value as an optimization since we will be calling this function sequentially
- L191 _public function_ `void PostMultTransform(const FTransform &Transform)`
- L222 _public function_ `FBufferedTransformKeys Collapse(FBufferedTransformKeys& AddLayer)` — Collapse the passed in Additve onto myself, returning a new FBufferedTransformKeys

#### class `UMovieScene3DTransformTrackRecorder`  
`class UMovieScene3DTransformTrackRecorder : public UMovieSceneTrackRecorder`  
_L288-352_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieSceneTrackRecorder`
- L292 _protected function_ `UMovieScene3DTransformTrackRecorder(const FObjectInitializer& ObjInit) : Super(ObjInit) , InterpolationMode(ERichCurveInterpMode::RCIM_Cubic)`
- L299 _protected prototype_ `virtual void CreateTrackImpl() override;` — UMovieSceneTrackRecorder Interface
- L300 _protected prototype_ `virtual void FinalizeTrackImpl() override;`
- L301 _protected prototype_ `virtual void StopRecordingImpl() override;`
- L302 _protected prototype_ `virtual void RecordSampleImpl(const FQualifiedFrameTime& CurrentTime) override;`
- L303 _protected function_ `virtual UMovieSceneSection* GetMovieSceneSection() const override`
- L307 _public function_ `virtual void SetSavedRecordingDirectory(const FString& InDirectory) override`
- L311 _public prototype_ `virtual bool LoadRecordedFile(const FString& InFileName, UMovieScene *InMovieScene, TMap<FGuid, AActor*>& ActorGuidToActorMap, TFunction<void()> InCompletionCallback) override;`
- L312 _public prototype_ `void PostProcessAnimationData(class UMovieSceneAnimationTrackRecorder* AnimTrackRecorder);`
- L314 _private prototype_ `bool ResolveTransformToRecord(FTransform& TransformToRecord);`
- L315 _private prototype_ `bool ShouldAddNewKey(const FTransform& TransformToRecord);`
- L316 _private prototype_ `void SetUpDefaultTransform();`
- L319 _private member_ `TWeakObjectPtr<class UMovieScene3DTransformTrack> MovieSceneTrack;` — Track to record to
- L322 _private member_ `TWeakObjectPtr<UMovieScene3DTransformSection> MovieSceneSection;` — Section to record to
- L325 _private member_ `UE::TrackRecorders::FBufferedTransformKeys BufferedTransforms;` — Buffer of transform keys. Keys are inserted into tracks in FinalizeTrack()
- L328 _private member_ `TOptional<FTransform> DefaultTransform;` — The default transform this recording starts with
- L331 _private member_ `bool bWasAttached;` — Flag indicating that some time while this recorder was active an attachment was also in place
- L334 _private member_ `ERichCurveInterpMode InterpolationMode;` — What Interpolation mode does the resulting Transform Track use?
- L337 _private member_ `FTransform PreviousValue;` — Previous Value And Frame used for checking previous values
- L338 _private member_ `bool bSetFirstKey;`
- L339 _private member_ `TOptional<FFrameNumber> PreviousFrame;`
- L342 _private member_ `FTransformSerializer TransformSerializer;` — Serializer
- L345 _private member_ `TWeakObjectPtr<USceneComponent> ActiveAttachParent;` — Active attach parent. Can be nullptr
- L348 _private member_ `TSharedPtr<class UE::TakesCore::FActorSequenceInformation> AttachParentSequenceInformation;` — Cached sequence information about the attach parent.
- L351 _private member_ `TArray<TWeakObjectPtr<UMovieSceneSection>> SectionsToRemoveOnFinalize;` — An array of UMovieSceneSections that may need removal one finalize. Weak pointers as they may expire earlier.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TAKETRACKRECORDERS_API`
- L23 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(TransformSerialization, Verbose, All);`
- L23 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(TransformSerialization, Verbose, All);`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace TakesCore` (scope `UE`)
- L50 _namespace_ `namespace UE`
- L50 _namespace_ `namespace TrackRecorders` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Public/TrackRecorders/MovieSceneActorReferenceTrackRecorder.h` (Public)


#### class `FMovieSceneActorReferenceTrackRecorderFactory`  
`class FMovieSceneActorReferenceTrackRecorderFactory : public IMovieSceneTrackRecorderFactory`  
_L16-30_
- inherits: `IMovieSceneTrackRecorderFactory`
- L19 _public prototype_ `virtual ~FMovieSceneActorReferenceTrackRecorderFactory() = default;`
- L21 _public prototype_ `virtual bool CanRecordObject(UObject* InObjectToRecord) const override;`
- L22 _public prototype_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForObject() const override;`
- L24 _public prototype_ `virtual bool CanRecordProperty(UObject* InObjectToRecord, FProperty* InPropertyToRecord) const override;`
- L25 _public prototype_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForProperty(UObject* InObjectToRecord, const FName& InPropertyToRecord) const override;`
- L27 _public function_ `virtual FText GetDisplayName() const override`
- L29 _public function_ `virtual bool CanHandlePropertyInstance() const override`

#### class `UMovieSceneActorReferenceTrackRecorder`  
`class UMovieSceneActorReferenceTrackRecorder : public UMovieSceneTrackRecorder`  
_L33-75_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieSceneTrackRecorder`
- L38 _public prototype_ `void CreateBinding(const FName& InPropertyToRecord);`
- L42 _protected prototype_ `virtual void CreateTrackImpl() override;` — UMovieSceneTrackRecorder Interface
- L43 _protected prototype_ `virtual void RecordSampleImpl(const FQualifiedFrameTime& CurrentTime) override;`
- L44 _protected prototype_ `virtual void FinalizeTrackImpl() override;`
- L45 _protected function_ `virtual UMovieSceneSection* GetMovieSceneSection() const override`
- L48 _protected prototype_ `void RemoveRedundantTracks();`
- L52 _private prototype_ `FMovieSceneActorReferenceKey ActorToReferenceKey(AActor* InActor) const;` — Convert an actor to a reference key, locating or creating a binding as necessary, taking into account if the actor is a spawnable or not.
- L58 _private prototype_ `AActor* EvaluateBinding(const UObject* OwningObject = nullptr) const;` — Evaluate the current binding returning the actor value. @param OwningObject Optional object to use for binding evaluation, defaults to the owning take recorder source.
- L62 _private member_ `TWeakObjectPtr<UMovieSceneActorReferenceSection> MovieSceneSection;` — Section to record to
- L65 _private member_ `TSharedPtr<FTrackInstancePropertyBindings> PropertyBinding;` — Binding for this property
- L68 _private member_ `TWeakObjectPtr<AActor> LastBindingValue;` — Value of the last evaluated binding.
- L71 _private member_ `bool bSetFirstKey;` — Flag used to determine whether the first key needs to be set
- L74 _private member_ `bool bIsRecording = false;` — True after a recording has started and until it stops.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TAKETRACKRECORDERS_API`

### `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Public/TrackRecorders/MovieSceneAnimationTrackRecorder.h` (Public)


#### class `FMovieSceneAnimationTrackRecorderFactory`  
`class FMovieSceneAnimationTrackRecorderFactory : public IMovieSceneTrackRecorderFactory`  
_L26-42_
- inherits: `IMovieSceneTrackRecorderFactory`
- L29 _public prototype_ `virtual ~FMovieSceneAnimationTrackRecorderFactory() = default;`
- L31 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override;`
- L32 _public prototype_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForObject() const override;`
- L34 _public function_ `virtual bool CanRecordProperty(class UObject* InObjectToRecord, class FProperty* InPropertyToRecord) const override`
- L35 _public function_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForProperty(UObject* InObjectToRecord, const FName& InPropertyToRecord) const override`
- L37 _public function_ `virtual FText GetDisplayName() const override`
- L38 _public function_ `virtual TSubclassOf<UMovieSceneTrackRecorderSettings> GetSettingsClass() const override`
- L40 _public function_ `virtual bool IsSerializable() const override`
- L41 _public function_ `virtual FName GetSerializedType() const override`

#### class `UMovieSceneAnimationTrackRecorder`  
`class UMovieSceneAnimationTrackRecorder : public UMovieSceneTrackRecorder`  
_L45-117_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieSceneTrackRecorder`
- L50 _protected prototype_ `virtual void CreateTrackImpl() override;` — UMovieSceneTrackRecorder Interface
- L51 _protected prototype_ `virtual void FinalizeTrackImpl() override;`
- L52 _protected prototype_ `virtual void CancelTrackImpl() override;`
- L53 _protected prototype_ `virtual void RecordSampleImpl(const FQualifiedFrameTime& CurrentTime) override;`
- L54 _protected prototype_ `virtual void StopRecordingImpl() override;`
- L55 _protected function_ `virtual void SetSavedRecordingDirectory(const FString& InDirectory) override`
- L59 _protected prototype_ `virtual bool LoadRecordedFile(const FString& InFileName, UMovieScene *InMovieScene, TMap<FGuid, AActor*>& ActorGuidToActorMap, TFunction<void()> InCompletionCallback) override;`
- L60 _protected function_ `virtual UMovieSceneSection* GetMovieSceneSection() const override`
- L64 _public function_ `bool RootWasRemoved() const`
- L65 _public prototype_ `void RemoveRootMotion();`
- L67 _public prototype_ `void ProcessRecordedTimes(const FString& HoursName, const FString& MinutesName, const FString& SecondsName, const FString& FramesName, const FString& SubFramesName, const FString& SlateName, const FString& Slate);` — `UE_DEPRECATED(5.5, "Use the ProcessRecordedTimes method that takes a FProcessRecordedTimeParams struct.")`
- L70 _public prototype_ `void ProcessRecordedTimes(const FProcessRecordedTimeParams& InParams);` — Apply time code data to the animation track.
- L72 _public function_ `UAnimSequence* GetAnimSequence() const`
- L73 _public function_ `USkeletalMesh* GetSkeletalMesh() const`
- L74 _public function_ `USkeletalMeshComponent* GetSkeletalMeshComponent() const`
- L75 _public function_ `const FTransform& GetComponentTransform() const`
- L76 _public function_ `const FTransform& GetInitialRootTransform() const`
- L79 _private prototype_ `bool ResolveTransformToRecord(FTransform& TransformToRecord);`
- L80 _private prototype_ `void CreateAnimationAssetAndSequence(const AActor* Actor, const FDirectoryPath& AnimationDirectory);`
- L83 _private member_ `TWeakObjectPtr<UMovieSceneSkeletalAnimationSection> MovieSceneSection;` — Section to record to
- L85 _private member_ `TWeakObjectPtr<class UAnimSequence> AnimSequence;`
- L87 _private member_ `TWeakObjectPtr<class USkeletalMeshComponent> SkeletalMeshComponent;`
- L89 _private member_ `TWeakObjectPtr<class USkeletalMesh> SkeletalMesh;`
- L92 _private member_ `FTransform ComponentTransform;` — Local transform of the component we are recording
- L95 _private member_ `FTransform InitialRootTransform;` — Inverse we are using to zero out root motion
- L97 _private member_ `bool bAnimationRecorderCreated;`
- L104 _private member_ `bool bRecordingFailedToStart = false;` — True if RecordSampleImpl tried to initialize the AnimationRecorder on the first sample but ObjectToRecord's weak pointer was already null (typically because the source SkeletalMeshComponent was destroyed between CreateTrack and the first sample). When set, further initialization attempts are skipped and the failure is surfaced on record finish to the user through the editor Message Log.
- L107 _private member_ `TSharedPtr<UE::AnimationRecording::IAnimRecorderInstance> AnimationRecorder;` — Animation Recorder
- L110 _private member_ `float PreviousSeconds;` — Previous Seconds to calc Delta used by Animation Recorder
- L113 _private member_ `FAnimationSerializer AnimationSerializer;` — Serializer
- L116 _private member_ `bool bRootWasRemoved = true;` — Root Was Removed

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API TAKETRACKRECORDERS_API`

### `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Public/TrackRecorders/MovieSceneAnimationTrackRecorderSettings.h` (Public)


#### class `UMovieSceneAnimationTrackRecorderEditorSettings`  
`class UMovieSceneAnimationTrackRecorderEditorSettings : public UMovieSceneTrackRecorderSettings`  
_L16-79_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, config=EditorSettings, DisplayName="Animation Recorder")`
- inherits: `UMovieSceneTrackRecorderSettings`
- L20 _public prototype_ `UMovieSceneAnimationTrackRecorderEditorSettings(const FObjectInitializer& ObjInit);`
- L23 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L28 _public member_ `FText AnimationTrackName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Animation Recorder Settings", meta = (NamingTokens))` — Name of the recorded animation track.
- L43 _public member_ `FString AnimationAssetName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Animation Recorder Settings", meta = (NamingTokens))` — The name of the animation asset. Supports any of the following format specifiers that will be substituted when a take is recorded: {day}       - The day of the timestamp for the start of the recording. {month}     - The month of the timestamp for the start of the recording. {year}      - The year of the timestamp for the start of the recording. {hour}      - The hour of the timestamp for the start of the recording. {minute}    - The minute of the timestamp for the start of the recording. {second}    - The second of the timestamp for the start of the recording. {take}      - The take number. {slate}     - The slate string. {actor}     - The name of the actor being recorded.
- L58 _public member_ `FString AnimationSubDirectory;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Animation Recorder Settings", meta = (NamingTokens))` — The name of the subdirectory animations will be placed in. Leave this empty to place into the same directory as the sequence base path. Supports any of the following format specifiers that will be substituted when a take is recorded: {day}       - The day of the timestamp for the start of the recording. {month}     - The month of the timestamp for the start of the recording. {year}      - The year of the timestamp for the start of the recording. {hour}      - The hour of the timestamp for the start of the recording. {minute}    - The minute of the timestamp for the start of the recording. {second}    - The second of the timestamp for the start of the recording. {take}      - The take number. {slate}     - The slate string. {actor}     - The name of the actor being recorded.
- L62 _public member_ `TEnumAsByte<ERichCurveInterpMode> InterpMode;` — `UPROPERTY(EditAnywhere, Category = "Animation Recorder Settings", DisplayName = "Interpolation Mode")` — Interpolation mode for the recorded keys.
- L66 _public member_ `TEnumAsByte<ERichCurveTangentMode> TangentMode;` — `UPROPERTY(EditAnywhere, Category = "Animation Recorder Settings")` — Tangent mode for the recorded keys.
- L70 _public member_ `bool bRemoveRootAnimation;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Animation Recorder Settings")` — If true we remove the root animation and move it to a transform track, if false we leave it on the root bone in the anim sequence
- L74 _public member_ `bool bSetRetargetSourceAsset;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Animation Recorder Settings")` — If true we set the retarget source asset on the saved anim sequence, if not we do not
- L78 _public member_ `FTimecodeBoneMethod TimecodeBoneMethod;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Animation Recorder Settings", meta = (ShowOnlyInnerProperties))` — The method to record timecode values onto bones

#### class `UMovieSceneAnimationTrackRecorderSettings`  
`class UMovieSceneAnimationTrackRecorderSettings : public UMovieSceneAnimationTrackRecorderEditorSettings`  
_L82-90_
- reflection: `UCLASS(MinimalAPI, BlueprintType, config = EditorSettings, DisplayName = "Animation Recorder Settings")`
- inherits: `UMovieSceneAnimationTrackRecorderEditorSettings`
- L86 _public function_ `UMovieSceneAnimationTrackRecorderSettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TAKETRACKRECORDERS_API`

### `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Public/TrackRecorders/MovieSceneParticleTrackRecorder.h` (Public)


#### class `FMovieSceneParticleTrackRecorderFactory`  
`class FMovieSceneParticleTrackRecorderFactory : public IMovieSceneTrackRecorderFactory`  
_L19-32_
- inherits: `IMovieSceneTrackRecorderFactory`
- L22 _public prototype_ `virtual ~FMovieSceneParticleTrackRecorderFactory() = default;`
- L24 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override;`
- L25 _public prototype_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForObject() const override;`
- L28 _public function_ `virtual bool CanRecordProperty(class UObject* InObjectToRecord, class FProperty* InPropertyToRecord) const override` — Particle Systems are entire components and you can't animate them as a property
- L29 _public function_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForProperty(UObject* InObjectToRecord, const FName& InPropertyToRecord) const override`
- L31 _public function_ `virtual FText GetDisplayName() const override`

#### class `UMovieSceneParticleTrackRecorder`  
`class UMovieSceneParticleTrackRecorder : public UMovieSceneTrackRecorder`  
_L35-65_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieSceneTrackRecorder`
- L39 _public function_ `UMovieSceneParticleTrackRecorder() : bWasTriggered(false) , PreviousState(EParticleKey::Activate)`
- L47 _protected prototype_ `virtual void CreateTrackImpl() override;` — UMovieSceneTrackRecorder Interface
- L48 _protected prototype_ `virtual void RecordSampleImpl(const FQualifiedFrameTime& CurrentTime) override;`
- L49 _protected function_ `virtual UMovieSceneSection* GetMovieSceneSection() const override`
- L54 _private prototype_ `void OnTriggered(UParticleSystemComponent* Component, bool bActivating);` — `UFUNCTION()`
- L57 _private member_ `TWeakObjectPtr<class UParticleSystemComponent> SystemToRecord;` — Object to record from
- L60 _private member_ `TWeakObjectPtr<class UMovieSceneParticleSection> MovieSceneSection;` — Section to record to
- L62 _private member_ `bool bWasTriggered;`
- L64 _private member_ `EParticleKey PreviousState;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TAKETRACKRECORDERS_API`

### `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Public/TrackRecorders/MovieScenePropertyTrackRecorder.h` (Public)


#### class `FMovieScenePropertyTrackRecorderFactory`  
`class FMovieScenePropertyTrackRecorderFactory : public IMovieSceneTrackRecorderFactory`  
_L18-38_
- inherits: `IMovieSceneTrackRecorderFactory`
- L21 _public prototype_ `virtual ~FMovieScenePropertyTrackRecorderFactory() = default;`
- L24 _public function_ `virtual bool CanRecordObject(UObject* InObjectToRecord) const override` — Property Track only records individual UProperties on an object.
- L25 _public function_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForObject() const override`
- L27 _public prototype_ `virtual bool CanRecordProperty(UObject* InObjectToRecord, class FProperty* InPropertyToRecord) const override;`
- L28 _public prototype_ `virtual class UMovieSceneTrackRecorder* CreateTrackRecorderForProperty(UObject* InObjectToRecord, const FName& InPropertyToRecord) const override;`
- L31 _public function_ `virtual FText GetDisplayName() const override`
- L33 _public function_ `virtual bool IsSerializable() const override`
- L34 _public function_ `virtual FName GetSerializedType() const override`
- L36 _public prototype_ `UMovieSceneTrackRecorder* CreateTrackRecorderForPropertyEnum(ESerializedPropertyType ePropertyType, const FName& InPropertyToRecord) const;`

#### class `UMovieScenePropertyTrackRecorder`  
`class UMovieScenePropertyTrackRecorder : public UMovieSceneTrackRecorder`  
_L41-68_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieSceneTrackRecorder`
- L46 _protected prototype_ `virtual void CreateTrackImpl() override;` — UMovieSceneTrackRecorder Interface
- L47 _protected prototype_ `virtual void SetSectionStartTimecodeImpl(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame) override;`
- L48 _protected prototype_ `virtual void FinalizeTrackImpl() override;`
- L49 _protected prototype_ `virtual void RecordSampleImpl(const FQualifiedFrameTime& CurrentTime) override;`
- L52 _protected function_ `virtual void SetSavedRecordingDirectory(const FString& InDirectory) override`
- L56 _protected prototype_ `virtual bool LoadRecordedFile(const FString& InFileName, UMovieScene *InMovieScene, TMap<FGuid, AActor*>& ActorGuidToActorMap, TFunction<void()> InCompletionCallback) override;`
- L61 _public member_ `FName PropertyToRecord;` — Name of the specific property that we want to record.
- L64 _public member_ `TSharedPtr<class IMovieSceneTrackPropertyRecorder> PropertyRecorder;` — The property recorder for the specific property that we are recording.
- L67 _public member_ `FString Directory;` — Cached Directory Name for serialization, used later when we create the PropertyRecorder

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TAKETRACKRECORDERS_API`

### `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Public/TrackRecorders/MovieSceneSpawnTrackRecorder.h` (Public)


#### class `FMovieSceneSpawnTrackRecorderFactory`  
`class FMovieSceneSpawnTrackRecorderFactory : public IMovieSceneTrackRecorderFactory`  
_L20-36_
- inherits: `IMovieSceneTrackRecorderFactory`
- L23 _public prototype_ `virtual ~FMovieSceneSpawnTrackRecorderFactory() = default;`
- L25 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override;`
- L26 _public prototype_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForObject() const override;`
- L29 _public function_ `virtual bool CanRecordProperty(class UObject* InObjectToRecord, class FProperty* InPropertyToRecord) const override` — Spawn Track is based on whether or not the recorded object still exists
- L30 _public function_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForProperty(UObject* InObjectToRecord, const FName& InPropertyToRecord) const override`
- L32 _public function_ `virtual FText GetDisplayName() const override`
- L34 _public function_ `virtual bool IsSerializable() const override`
- L35 _public function_ `virtual FName GetSerializedType() const override`

#### class `UMovieSceneSpawnTrackRecorder`  
`class UMovieSceneSpawnTrackRecorder : public UMovieSceneTrackRecorder`  
_L39-64_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieSceneTrackRecorder`
- L44 _protected prototype_ `virtual void CreateTrackImpl() override;` — UMovieSceneTrackRecorder Interface
- L45 _protected prototype_ `virtual void FinalizeTrackImpl() override;`
- L46 _protected prototype_ `virtual void RecordSampleImpl(const FQualifiedFrameTime& CurrentTime) override;`
- L47 _protected function_ `virtual void SetSavedRecordingDirectory(const FString& InDirectory) override`
- L51 _protected prototype_ `virtual bool LoadRecordedFile(const FString& InFileName, UMovieScene *InMovieScene, TMap<FGuid, AActor*>& ActorGuidToActorMap, TFunction<void()> InCompletionCallback) override;`
- L52 _protected function_ `virtual UMovieSceneSection* GetMovieSceneSection() const override`
- L57 _private member_ `TWeakObjectPtr<class UMovieSceneBoolSection> MovieSceneSection;` — Section to record to
- L59 _private member_ `bool bWasSpawned;`
- L62 _private member_ `FSpawnSerializer SpawnSerializer;` — Serializer
- L63 _private member_ `bool bSetFirstKey;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TAKETRACKRECORDERS_API`
- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(SpawnSerialization, Verbose, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(SpawnSerialization, Verbose, All);`

### `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Public/TrackRecorders/MovieSceneTrackPropertyRecorder.h` (Public)


#### class `IMovieSceneTrackPropertyRecorder`  
`class IMovieSceneTrackPropertyRecorder`  
_L20-39_
- desc: Interface for a generic property recorder
- L24 _public prototype_ `virtual ~IMovieSceneTrackPropertyRecorder() = default;`
- L25 _public prototype_ `virtual void Create(IMovieSceneTrackRecorderHost* InRecordingHost, UObject* InObjectToRecord, class UMovieScene* InMovieScene, const FGuid& InGuid, bool bOpenSerializer = false) = 0;`
- L26 _public prototype_ `virtual void SetSectionStartTimecode(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame) = 0;`
- L27 _public prototype_ `virtual void Record(UObject* InObjectToRecord, const FQualifiedFrameTime& CurrentTime) = 0;`
- L29 _public prototype_ `virtual void Finalize(UObject* InObjectToRecord) = 0;`
- L31 _public prototype_ `virtual void SetSavedRecordingDirectory(const FString& InDirectory) = 0;`
- L33 _public function_ `virtual bool LoadRecordedFile(const FString& InFileName, UMovieScene *InMovieScene, TMap<FGuid, AActor*>& ActorGuidToActorMap, TFunction<void()> InCompletionCallback)`
- L38 _protected member_ `IMovieSceneTrackRecorderHost * OwningTakeRecorderSource;` — The Actor Source that owns us

#### struct `FPropertyKey`  
`template <typename PropertyType> struct FPropertyKey`  
_L43-47_
- desc: Helper struct for recording properties
- L45 _public member_ `PropertyType Value;`
- L46 _public member_ `FFrameNumber Time;`

#### class `FMovieSceneTrackPropertyRecorder`  
`template <typename PropertyType> class FMovieSceneTrackPropertyRecorder : public IMovieSceneTrackPropertyRecorder`  
_L51-317_
- inherits: `IMovieSceneTrackPropertyRecorder`
- desc: Recorder for a simple property of type PropertyType
- L54 _public function_ `FMovieSceneTrackPropertyRecorder(const FTrackInstancePropertyBindings& InBinding) : Binding(InBinding)`
- L58 _public prototype_ `virtual ~FMovieSceneTrackPropertyRecorder() = default;`
- L60 _public function_ `virtual void Create(IMovieSceneTrackRecorderHost* InRecordingHost, UObject* InObjectToRecord, class UMovieScene* InMovieScene, const FGuid& InGuid, bool bOpenSerializer) override`
- L94 _public function_ `virtual void SetSectionStartTimecode(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame) override`
- L106 _public function_ `virtual void Record(UObject* InObjectToRecord, const FQualifiedFrameTime& CurrentTime) override`
- L161 _public function_ `virtual void Finalize(UObject* InObjectToRecord) override`
- L188 _public function_ `virtual void RemoveRedundantTracks(UMovieSceneSection* InSection, UObject* InObjectToRecord)`
- L265 _public function_ `virtual void SetSavedRecordingDirectory(const FString& InDirectory) override`
- L269 _public prototype_ `virtual bool LoadRecordedFile(const FString& InFileName, UMovieScene *InMovieScene, TMap<FGuid, AActor*>& ActorGuidToActorMap, TFunction<void()> InCompletionCallback) override;`
- L276 _private prototype_ `bool ShouldAddNewKey(const PropertyType& InNewValue) const;` — Helper function, specialized by type, used to check if we do capture-time filtering of keys based on previous values
- L279 _private prototype_ `class UMovieSceneSection* AddSection(const FString& TrackDisplayName, class UMovieScene* InMovieScene, const FGuid& InGuid, bool bSetDefault = true);` — Helper function, specialized by type, used to add an appropriate section to the movie scene
- L282 _private prototype_ `void PostCreate(IMovieSceneTrackRecorderHost* InRecordingHost, UObject* InObjectToRecord, class UMovieScene* InMovieScene, const FGuid& InGuid, bool bOpenSerializer = false);` — Helper function, specialized by type, after create
- L285 _private prototype_ `void AddKeysToSection(UMovieSceneSection* InSection, const TArray<FPropertyKey<PropertyType>>& InKeys);` — Helper function, specialized by type, used to add keys to the movie scene section at Finalize() time
- L288 _private prototype_ `void ReduceKeys(UMovieSceneSection* InSection, float ReduceKeysTolerance);` — Helper function, specialized by type, used to reduce keys
- L291 _private prototype_ `PropertyType GetDefaultValue(UMovieSceneSection* InSection);` — Get the default value of the track - if there's one key, the value of that key. Otherwise, the default value of the track.
- L294 _private prototype_ `void SetDefaultValue(UMovieSceneSection* InSection, const PropertyType& InNewValue);` — Set the default value of the track
- L297 _private prototype_ `bool OpenSerializer(const FString& InObjectName, const FName& InPropertyName, const FString& InTrackDisplayName, const FGuid& InGuid);` — Open the Serializer of the right PropertyType
- L301 _private member_ `FTrackInstancePropertyBindings Binding;` — Binding for this property
- L304 _private member_ `TArray<FPropertyKey<PropertyType>> Keys;` — The keys that are being recorded
- L307 _private member_ `TWeakObjectPtr<class UMovieSceneSection> MovieSceneSection;` — Section we are recording
- L310 _private member_ `PropertyType PreviousValue;` — Previous value we use to establish whether we should key
- L311 _private member_ `TOptional<FFrameNumber> PreviousFrame;`
- L312 _private member_ `bool bSetFirstKey;`
- L316 _private member_ `TMovieSceneSerializer<FPropertyFileHeader, FSerializedProperty<PropertyType>> Serializer;` — Serializer

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(PropertySerialization, Verbose, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(PropertySerialization, Verbose, All);`

### `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Public/TrackRecorders/MovieSceneTrackRecorder.h` (Public)


#### class `UMovieSceneTrackRecorder`  
`class UMovieSceneTrackRecorder : public UObject`  
_L17-195_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Transient, Abstract)`
- inherits: `UObject`
- L27 _public function_ `void CreateTrack(IMovieSceneTrackRecorderHost* InRecordingHost, UObject* InObjectToRecord, UMovieScene* InMovieScene, UMovieSceneTrackRecorderSettings* InSettingsObject, const FGuid& InObjectGuid)` — CreateTrack is called during PreRecording and should perform any clean up of old data, allocate new tracks if needed and create sections that start at a time of zero. The call to PreRecording can take a significant amount of time when many sources are being recorded (due to the possibly large number of allocations) so the creation time is not passed in. Instead Track recorders should implement SetSectionStartTimecodeImpl which will be called when StartRecording is called. StartRecording is called one after another and should be a non-blocking operation which will ensure all sources will start on the most up to date and in-sync timecode data.
- L56 _public function_ `void SetSectionStartTimecode(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame)` — This is called when Recording actually starts happening. Tracks and Sections should have already been created during CreateTrack so this call simply informs you of: - What the first frame should be for the Section you have created - What Timecode you should embed in your Movie Scene section for syncing via the UI later. This is implemented as a separate call from CreateTrack partially for blocking/sync reasons (in case the Timecode Source is pulled live and not the one cached for a given frame) and partially so that this operation is explicit which will make it easier to follow the timecode logic as the implementations become more integrated with each other. @param InSectionStartTimecode - The externally provided timecode at the time of this recording. @param InSectionFirstFrame - The first frame of the section in sequence tick resolution.
- L80 _public function_ `void FinalizeTrack()` — This is called after recording has finished for each track. This allows a track recorder to do any post-processing it may require such as removing any sections that did not have any changes in them.
- L97 _public function_ `void CancelTrack()` — This is called after recording has finished for each track. This allows a track recorder to do any post-processing it may require such as removing any sections that did not have any changes in them.
- L115 _public function_ `void RecordSample(const FQualifiedFrameTime& CurrentTime)` — This is called each frame and specifies the qualified time that the sampled data should be recorded at. This is passed as a FQualifiedFrameTime for better handling of mixed resolution sequences as a user may have modified a sub-sequence to be a different resolution than the parent sequence.
- L125 _public function_ `void StopRecording()` — This is called when the user presses StopRecording. This should be a non-blocking operation as it is called on all sources one after another as quickly as possible so they all stop at the same time. This can be important for legacy systems that still rely on floating point time.
- L133 _public function_ `virtual bool ShouldContinueRecording(const FQualifiedFrameTime& FrameTime) const` — Returns false if the track for this recorder has finished recording data
- L138 _public function_ `void InvalidateObjectToRecord()`
- L143 _public function_ `UObject* GetSourceObject() const`
- L148 _public function_ `UMovieSceneTrackRecorderSettings* GetTrackRecorderSettings()`
- L158 _public function_ `virtual void SetSavedRecordingDirectory(const FString& InDirectory)` — Set the directory where the recorded values are saved @param InDirectory the directory to save the data
- L166 _public function_ `virtual bool LoadRecordedFile(const FString& InFileName, UMovieScene *InMovieScene, TMap<FGuid, AActor*>& ActorGuidToActorMap, TFunction<void()> InCompletionCallback)` — Load the recorded file and create a section @param InFileName The file to load @param InMovieScene The Movie Scene to put the loaded track and section. @return  Returns true if it was loaded and a section was created, false otherwise.
- L169 _protected function_ `virtual void CreateTrackImpl()`
- L170 _protected function_ `virtual void SetSectionStartTimecodeImpl(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame)`
- L171 _protected function_ `virtual void RecordSampleImpl(const FQualifiedFrameTime& CurrentTime)`
- L172 _protected function_ `virtual void StopRecordingImpl()`
- L173 _protected function_ `virtual void FinalizeTrackImpl()`
- L174 _protected function_ `virtual void CancelTrackImpl()`
- L175 _protected function_ `virtual UMovieSceneSection* GetMovieSceneSection() const`
- L179 _protected member_ `TWeakObjectPtr<UObject> ObjectToRecord;` — Object to record from
- L182 _protected member_ `FGuid ObjectGuid;` — Owning Object GUID in the Level Sequence
- L185 _protected member_ `TWeakObjectPtr<UMovieScene> MovieScene;` — Movie Scene we're supposed to record to
- L188 _protected member_ `IMovieSceneTrackRecorderHost* OwningTakeRecorderSource;` — The Actor Source that owns us
- L191 _protected member_ `TWeakObjectPtr<UMovieSceneTrackRecorderSettings> Settings;` — Settings object for the factory that created us. Can be nullptr if the factory has no settings object.
- L194 _protected member_ `FMovieSceneTimecodeSource StartTimecode;` — The timecode source at the beginning of recording

### `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Public/TrackRecorders/MovieSceneTrackRecorderSettings.h` (Public)


#### class `UMovieSceneTrackRecorderSettings`  
`class UMovieSceneTrackRecorderSettings : public UObject`  
_L9-12_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`

### `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Public/TrackRecorders/MovieSceneVisibilityTrackRecorder.h` (Public)


#### class `FMovieSceneVisibilityTrackRecorderFactory`  
`class FMovieSceneVisibilityTrackRecorderFactory : public IMovieSceneTrackRecorderFactory`  
_L17-30_
- inherits: `IMovieSceneTrackRecorderFactory`
- L20 _public prototype_ `virtual ~FMovieSceneVisibilityTrackRecorderFactory() = default;`
- L22 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override;`
- L23 _public prototype_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForObject() const override;`
- L26 _public prototype_ `virtual bool CanRecordProperty(class UObject* InObjectToRecord, class FProperty* InPropertyToRecord) const override;` — Visibility is based on a different property for components and actors, and they're not marked as interp
- L27 _public function_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForProperty(UObject* InObjectToRecord, const FName& InPropertyToRecord) const override`
- L29 _public function_ `virtual FText GetDisplayName() const override`

#### class `UMovieSceneVisibilityTrackRecorder`  
`class UMovieSceneVisibilityTrackRecorder : public UMovieSceneTrackRecorder`  
_L33-56_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieSceneTrackRecorder`
- L38 _protected prototype_ `virtual void CreateTrackImpl() override;` — UMovieSceneTrackRecorder Interface
- L39 _protected prototype_ `virtual void RecordSampleImpl(const FQualifiedFrameTime& CurrentTime) override;`
- L40 _protected prototype_ `virtual void FinalizeTrackImpl() override;`
- L41 _protected function_ `virtual UMovieSceneSection* GetMovieSceneSection() const override`
- L44 _protected prototype_ `void RemoveRedundantTracks();`
- L45 _protected prototype_ `bool IsObjectVisible() const;`
- L49 _private member_ `TWeakObjectPtr<class UMovieSceneBoolSection> MovieSceneSection;` — Section to record to
- L52 _private member_ `bool bWasVisible;` — Flag used to track visibility state and add keys when this changes
- L55 _private member_ `bool bSetFirstKey;` — Flag used to determine whether the first key needs to be set

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TAKETRACKRECORDERS_API`
