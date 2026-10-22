# Editor / SequenceRecorder

- module root: `Source/Editor/SequenceRecorder`
- headers: 30; symbols: 668
- symbol kinds: class=32, delegate=5, enum=1, enumerator=2, function=74, macro=6, member=227, namespace=1, prototype=306, struct=14
- DynamicallyLoadedModuleNames: Persona
- PrivateDependencyModuleNames: AssetRegistry, CinematicCamera, Core, CoreUObject, EditorFramework, EditorStyle, EditorWidgets, Engine, InputCore, Kismet, LevelEditor, LevelSequence, LiveLinkInterface, MovieScene, MovieSceneTracks, NetworkReplayStreaming, Projects, PropertyEditor, SceneOutliner, Sequencer, Slate, SlateCore, UnrealEd, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: Persona
- PublicDependencyModuleNames: SequenceRuntimeRecorder, SerializedRecorderInterface, TimeManagement

### `Source/Editor/SequenceRecorder/Private/ActorGroupDetailsCustomization.h` (Private)


#### class `FActorGroupDetailsCustomization`  
`class FActorGroupDetailsCustomization : public IDetailCustomization`  
_L15-37_
- inherits: `IDetailCustomization`
- L18 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance(TWeakPtr<SSequenceRecorder> InSequenceRecorder)`
- L23 _public function_ `FActorGroupDetailsCustomization(TWeakPtr<SSequenceRecorder> InSequenceRecorder)`
- L29 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L32 _private prototype_ `TSharedRef<SWidget> CreateRecordingGroupButton(const FText& InGlyph, TSharedPtr<FUICommandInfo> InCommand);`
- L33 _private prototype_ `TSharedRef<SWidget> FillRecordingProfileOptions();`
- L34 _private prototype_ `void HandleRecordingGroupNameCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L35 _private member_ `TSharedPtr<SEditableTextBox> SequenceRecorderGroupNameTextBox;`
- L36 _private member_ `TWeakPtr<SSequenceRecorder> SequenceRecorder;`

### `Source/Editor/SequenceRecorder/Private/ActorRecordingDetailsCustomization.h` (Private)


#### class `FActorRecordingDetailsCustomization`  
`class FActorRecordingDetailsCustomization : public IDetailCustomization`  
_L13-23_
- inherits: `IDetailCustomization`
- desc: Customize the actor recording object so we can expand external settings in-line
- L16 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Source/Editor/SequenceRecorder/Private/AnimationRecorderParameters.h` (Private)


#### class `UAnimationRecordingParameters`  
`class UAnimationRecordingParameters : public UObject`  
_L15-51_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L20 _public prototype_ `float GetRecordingDurationSeconds();`
- L21 _public prototype_ `const FFrameRate& GetRecordingFrameRate();`
- L23 _public function_ `virtual void PostInitProperties() override`
- L38 _public member_ `FFrameRate SampleFrameRate = FAnimationRecordingSettings::DefaultSampleFrameRate;` — `UPROPERTY(EditAnywhere, config, Category = Options)` — Sample frame-rate of the recorded animation
- L42 _public member_ `bool bEndAfterDuration = false;` — `UPROPERTY(EditAnywhere, config, Category = Options)` — If enabled, this animation recording will automatically end after a set amount of time
- L46 _public member_ `float MaximumDurationSeconds = FAnimationRecordingSettings::DefaultMaximumLength;` — `UPROPERTY(EditAnywhere, config, Category = Options, meta = (EditCondition = "bEndAfterDuration", UIMin = "0.03333", ClampMin = "0.03333"))` — The maximum duration of this animation recording
- L50 _public member_ `float SampleRate = 0.f;` — `UE_DEPRECATED(5.0, "SampleRate has been deprecated and replaced with SampleFrameRate")` — `UPROPERTY(config)`

### `Source/Editor/SequenceRecorder/Private/PropertiesToRecordForClassDetailsCustomization.h` (Private)


#### class `FPropertiesToRecordForClassDetailsCustomization`  
`class FPropertiesToRecordForClassDetailsCustomization : public IPropertyTypeCustomization`  
_L12-23_
- inherits: `IPropertyTypeCustomization`
- L15 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

#### class `FPropertiesToRecordForActorClassDetailsCustomization`  
`class FPropertiesToRecordForActorClassDetailsCustomization : public IPropertyTypeCustomization`  
_L25-36_
- inherits: `IPropertyTypeCustomization`
- L28 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L34 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L35 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Source/Editor/SequenceRecorder/Private/SClassPropertyRecorderSettings.h` (Private)


#### class `SClassPropertyRecorderSettings`  
`class SClassPropertyRecorderSettings : public SCompoundWidget, public IDetailPropertyExtensionHandler`  
_L22-61_
- inherits: `SCompoundWidget,IDetailPropertyExtensionHandler`
- L24 _private function_ `SLATE_BEGIN_ARGS(SClassPropertyRecorderSettings)`
- L28 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<class IPropertyHandle>& InClassHandle, const TSharedRef<class IPropertyHandle>& InPropertiesHandle, IPropertyTypeCustomizationUtils& CustomizationUtils);`
- L34 _private prototype_ `FText GetText() const;` — Get the text to display describing the properties we are recording
- L37 _private prototype_ `FReply HandleChoosePropertiesButtonClicked();` — Handle clicking the 'edit' button
- L40 _private prototype_ `bool ShouldShowProperty(const FPropertyAndParent& InPropertyAndParent) const;` — Hide non-keyable properties in the picker window
- L43 _private prototype_ `bool IsPropertyReadOnly(const FPropertyAndParent& InPropertyAndParent) const;` — Make all properties read-only
- L46 _private prototype_ `void HandlePropertyCheckStateChanged(ECheckBoxState InState, TSharedPtr<IPropertyHandle> PropertyHandle);` — Handle a property being marked for recording
- L49 _private prototype_ `TArray<FName>* GetPropertyNameArray() const;` — Helper function to get the actual name array from the property handle
- L52 _private prototype_ `virtual bool IsPropertyExtendable(const UClass* InObjectClass, const class IPropertyHandle& PropertyHandle) const override;` — IDetailPropertyExtensionHandler interface
- L53 _private prototype_ `virtual void ExtendWidgetRow(FDetailWidgetRow& InWidgetRow, const IDetailLayoutBuilder& InDetailLayoutBuilder, const UClass* InObjectClass, TSharedPtr<IPropertyHandle> PropertyHandle) override;`
- L57 _private member_ `TSharedPtr<class IPropertyHandle> PropertiesHandle;` — Handle to the property we are editing
- L60 _private member_ `TSharedPtr<class IPropertyHandle> ClassHandle;` — Handle to the class property in the struct

### `Source/Editor/SequenceRecorder/Private/SCreateAnimationDlg.h` (Private)


#### class `SCreateAnimationDlg`  
`class SCreateAnimationDlg : public SWindow`  
_L12-56_
- inherits: `SWindow`
- L15 _public function_ `SLATE_BEGIN_ARGS(SCreateAnimationDlg)`
- L18 _public function_ `SLATE_ARGUMENT(FText, DefaultAssetPath) SLATE_END_ARGS() SCreateAnimationDlg() : UserResponse(EAppReturnType::Cancel)`
- L25 _public prototype_ `void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `EAppReturnType::Type ShowModal();` — Displays the dialog in a blocking fashion
- L32 _public prototype_ `FString GetAssetPath();` — Gets the resulting asset path
- L35 _public prototype_ `FString GetAssetName();` — Gets the resulting asset name
- L38 _public prototype_ `FString GetFullAssetPath();` — Gets the resulting full asset path (path+'/'+name)
- L41 _public function_ `UAnimationRecordingParameters* GetRecordingParameters() const` — Gets the resulting sample rate and recording duration
- L45 _protected prototype_ `void OnPathChange(const FString& NewPath);`
- L46 _protected prototype_ `void OnNameChange(const FText& NewName, ETextCommit::Type CommitInfo);`
- L47 _protected prototype_ `FReply OnButtonClick(EAppReturnType::Type ButtonID);`
- L49 _protected prototype_ `bool ValidatePackage();`
- L51 _protected member_ `EAppReturnType::Type UserResponse;`
- L52 _protected member_ `FText AssetPath;`
- L53 _protected member_ `FText AssetName;`
- L55 _protected member_ `static FText LastUsedAssetPath;`

### `Source/Editor/SequenceRecorder/Private/SSequenceRecorder.h` (Private)


#### class `SSequenceRecorder`  
`class SSequenceRecorder : public SCompoundWidget`  
_L25-143_
- inherits: `SCompoundWidget`
- L27 _private function_ `SLATE_BEGIN_ARGS(SSequenceRecorder)`
- L31 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L36 _private prototype_ `~SSequenceRecorder();` — SSequenceRecorder destructor
- L40 _private prototype_ `void BindCommands();`
- L42 _private prototype_ `TSharedRef<ITableRow> MakeListViewWidget(UActorRecording* Recording, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L44 _private prototype_ `FText GetRecordingActorName(UActorRecording* Recording) const;`
- L46 _private prototype_ `void OnActorListSelectionChanged(UActorRecording* Recording, ESelectInfo::Type SelectionType);`
- L48 _private prototype_ `void OnListSelectionChanged(USequenceRecordingBase* Recording);`
- L50 _private prototype_ `void HandleRecord();`
- L52 _private prototype_ `EActiveTimerReturnType StartDelayedRecord(double InCurrentTime, float InDeltaTime);`
- L54 _private prototype_ `bool CanRecord() const;`
- L56 _private prototype_ `bool IsRecordVisible() const;`
- L58 _private prototype_ `void HandleStopAll();`
- L60 _private prototype_ `bool CanStopAll() const;`
- L62 _private prototype_ `bool IsStopAllVisible() const;`
- L64 _private prototype_ `void HandleAddRecording();`
- L65 _private prototype_ `void HandleRecordingGroupAddedToSequenceRecorder(TWeakObjectPtr<class USequenceRecorderActorGroup> ActorGroup);`
- L67 _private prototype_ `bool CanAddRecording() const;`
- L69 _private prototype_ `void HandleAddCurrentPlayerRecording();`
- L71 _private prototype_ `bool CanAddCurrentPlayerRecording() const;`
- L73 _private prototype_ `void HandleRemoveRecording();`
- L75 _private prototype_ `bool CanRemoveRecording() const;`
- L77 _private prototype_ `void HandleRemoveAllRecordings();`
- L79 _private prototype_ `bool CanRemoveAllRecordings() const;`
- L81 _private prototype_ `void HandleAddRecordingGroup();`
- L84 _private prototype_ `bool CanAddRecordingGroup() const;`
- L86 _private prototype_ `void HandleRemoveRecordingGroup();`
- L88 _private prototype_ `bool CanRemoveRecordingGroup() const;`
- L90 _private prototype_ `void HandleDuplicateRecordingGroup();`
- L92 _private prototype_ `bool CanDuplicateRecordingGroup() const;`
- L94 _private prototype_ `void HandleRecordingProfileNameCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L96 _private prototype_ `EActiveTimerReturnType HandleRefreshItems(double InCurrentTime, float InDeltaTime);`
- L98 _private prototype_ `void HandleMapUnload(UObject* Object);`
- L100 _private prototype_ `TOptional<float> GetDelayPercent() const;`
- L102 _private prototype_ `void OnDelayChanged(float NewValue);`
- L104 _private prototype_ `EVisibility GetDelayProgressVisibilty() const;`
- L106 _private prototype_ `FText GetTargetSequenceName() const;`
- L108 _private prototype_ `FReply OnRecordingActorListDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent );`
- L110 _private prototype_ `bool OnRecordingActorListAllowDrop( TSharedPtr<FDragDropOperation> DragDropOperation );`
- L113 _public function_ `TSharedPtr<FUICommandList> GetCommandList() const`
- L118 _public prototype_ `void HandleLoadRecordingActorGroup(FName Name);`
- L122 _private member_ `TSharedPtr<IDetailsView> SequenceRecordingDetailsView;` — This is the Detail View for the USequenceRecorderSettings
- L125 _private member_ `TSharedPtr<IDetailsView> SelectedRecordingItemDetailsView;` — This is the Detail View for the currently selected UActorRecording or an item from an Extender
- L128 _private member_ `TSharedPtr<IDetailsView> RecordingGroupDetailsView;` — This is the Detail View for the currently selected USequenceActorGroup
- L130 _private member_ `TSharedPtr<SListView<UActorRecording*>> ActorListView;`
- L133 _private member_ `TArray<TSharedPtr<SListView<USequenceRecordingBase*>>> ExtenderListViews;` — List of all the the Detail View created by Extenders
- L135 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L138 _private member_ `TWeakPtr<FActiveTimerHandle> ActiveTimerHandle;` — The handle to the refresh tick timer
- L140 _private member_ `TSharedPtr<SProgressBar> DelayProgressBar;`
- L142 _private member_ `mutable bool bInsideSelectionChanged;`

### `Source/Editor/SequenceRecorder/Private/Sections/MovieScene3DTransformSectionRecorder.h` (Private)


#### class `FMovieScene3DTransformSectionRecorderFactory`  
`class FMovieScene3DTransformSectionRecorderFactory : public IMovieSceneSectionRecorderFactory`  
_L17-29_
- inherits: `IMovieSceneSectionRecorderFactory`
- L20 _public prototype_ `virtual ~FMovieScene3DTransformSectionRecorderFactory() = default;`
- L22 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override;`
- L23 _public function_ `virtual UObject* CreateSettingsObject(class UObject* InOuter) const override`
- L25 _public prototype_ `TSharedPtr<class FMovieScene3DTransformSectionRecorder> CreateSectionRecorder(bool bRecordTransforms, TSharedPtr<class FMovieSceneAnimationSectionRecorder> InAnimRecorder) const;`
- L28 _private prototype_ `virtual TSharedPtr<IMovieSceneSectionRecorder> CreateSectionRecorder(const FActorRecordingSettings& InActorRecordingSettings) const override;`

#### struct `FBufferedTransformKeys`  
`struct FBufferedTransformKeys`  
_L32-55_
- desc: Structure used to buffer up transform keys. Keys are inserted into tracks in FinalizeSection()
- L34 _public function_ `void Add(const FTransform& InTransform, FFrameNumber InKeyTime)`
- L51 _public member_ `TArray<FFrameNumber> Times;`
- L52 _public member_ `TArray<float> LocationX, LocationY, LocationZ;`
- L52 _public member_ `TArray<float> LocationX, LocationY, LocationZ;`
- L52 _public member_ `TArray<float> LocationX, LocationY, LocationZ;`
- L53 _public member_ `TArray<float> RotationX, RotationY, RotationZ;`
- L53 _public member_ `TArray<float> RotationX, RotationY, RotationZ;`
- L53 _public member_ `TArray<float> RotationX, RotationY, RotationZ;`
- L54 _public member_ `TArray<float> ScaleX, ScaleY, ScaleZ;`
- L54 _public member_ `TArray<float> ScaleX, ScaleY, ScaleZ;`
- L54 _public member_ `TArray<float> ScaleX, ScaleY, ScaleZ;`

#### class `FMovieScene3DTransformSectionRecorder`  
`class FMovieScene3DTransformSectionRecorder : public IMovieSceneSectionRecorder`  
_L57-115_
- inherits: `IMovieSceneSectionRecorder`
- L60 _public function_ `FMovieScene3DTransformSectionRecorder(bool bInActuallyRecord, TSharedPtr<class FMovieSceneAnimationSectionRecorder> InAnimRecorder = nullptr) : bRecording(bInActuallyRecord) , AnimRecorder(InAnimRecorder)`
- L65 _public prototype_ `virtual ~FMovieScene3DTransformSectionRecorder() = default;`
- L67 _public prototype_ `virtual void CreateSection(UObject* InObjectToRecord, class UMovieScene* InMovieScene, const FGuid& Guid, float Time) override;`
- L68 _public prototype_ `virtual void FinalizeSection(float CurrentTime) override;`
- L69 _public prototype_ `virtual void Record(float CurrentTime) override;`
- L70 _public function_ `virtual void InvalidateObjectToRecord() override`
- L74 _public function_ `virtual UObject* GetSourceObject() const override`
- L80 _private prototype_ `bool GetTransformToRecord(FTransform& TransformToRecord);`
- L84 _private member_ `TWeakObjectPtr<UObject> ObjectToRecord;` — Object to record from
- L87 _private member_ `TWeakObjectPtr<class UMovieScene> MovieScene;` — MovieScene to record to
- L90 _private member_ `TWeakObjectPtr<class UMovieScene3DTransformTrack> MovieSceneTrack;` — Track to record to
- L93 _private member_ `TWeakObjectPtr<class UMovieScene3DTransformSection> MovieSceneSection;` — Section to record to
- L96 _private member_ `FBufferedTransformKeys BufferedTransforms;` — Buffer of transform keys. Keys are inserted into tracks in FinalizeSection()
- L99 _private member_ `bool bRecording;` — Flag if we are actually recording or not
- L102 _private member_ `TSharedPtr<class FMovieSceneAnimationSectionRecorder> AnimRecorder;` — Animation recorder we use to sync our transforms to
- L105 _private member_ `FTransform DefaultTransform;` — The default transform this recording starts with
- L108 _private member_ `bool bWasAttached;` — Flag indicating that some time while this recorder was active an attachment was also in place
- L111 _private member_ `FGuid Guid;` — The guid being recorded to
- L114 _private member_ `float RecordingStartTime;` — The guid being recorded to

### `Source/Editor/SequenceRecorder/Private/Sections/MovieScene3DTransformSectionRecorderSettings.h` (Private)


#### class `UMovieScene3DTransformSectionRecorderSettings`  
`class UMovieScene3DTransformSectionRecorderSettings : public UObject`  
_L11-22_
- reflection: `UCLASS()`
- inherits: `UObject`
- L21 _public member_ `bool bRecordTransforms;` — `UPROPERTY(EditAnywhere, Category = "Actor Recording")` — Whether to record actor transforms. This can be useful if you want the actors to end up in specific locations after the sequence. By default we rely on animations to provide transforms, but this can be changed using the "Record In World Space" animation setting.

### `Source/Editor/SequenceRecorder/Private/Sections/MovieSceneAnimationSectionRecorder.h` (Private)


#### class `FMovieSceneAnimationSectionRecorderFactory`  
`class FMovieSceneAnimationSectionRecorderFactory : public IMovieSceneSectionRecorderFactory`  
_L18-29_
- inherits: `IMovieSceneSectionRecorderFactory`
- L21 _public prototype_ `virtual ~FMovieSceneAnimationSectionRecorderFactory() = default;`
- L23 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override;`
- L25 _public prototype_ `TSharedPtr<class FMovieSceneAnimationSectionRecorder> CreateSectionRecorder(UAnimSequence* InAnimSequence, const FAnimationRecordingSettings& InAnimationSettings, const FString& InAnimAssetPath = FString(), const FString& InAnimAssetName = FString()) const;`
- L28 _private prototype_ `virtual TSharedPtr<IMovieSceneSectionRecorder> CreateSectionRecorder(const FActorRecordingSettings& InActorRecordingSettings) const override;`

#### class `FMovieSceneAnimationSectionRecorder`  
`class FMovieSceneAnimationSectionRecorder : public IMovieSceneSectionRecorder`  
_L31-82_
- inherits: `IMovieSceneSectionRecorder`
- L34 _public prototype_ `FMovieSceneAnimationSectionRecorder(const FAnimationRecordingSettings& InAnimationSettings, UAnimSequence* InSpecifiedSequence, const FString& InAnimAssetPath = FString(), const FString& InAnimAssetName = FString());`
- L35 _public prototype_ `virtual ~FMovieSceneAnimationSectionRecorder() = default;`
- L37 _public prototype_ `virtual void CreateSection(UObject* InObjectToRecord, class UMovieScene* MovieScene, const FGuid& Guid, float Time) override;`
- L38 _public prototype_ `virtual void FinalizeSection(float CurrentTime) override;`
- L39 _public prototype_ `virtual void Record(float CurrentTime) override;`
- L40 _public function_ `virtual void InvalidateObjectToRecord() override`
- L44 _public function_ `virtual UObject* GetSourceObject() const override`
- L49 _public function_ `void SetRemoveRootTransform(bool bInRemoveRootTransform)`
- L51 _public function_ `UAnimSequence* GetAnimSequence() const`
- L53 _public function_ `USkeletalMesh* GetSkeletalMesh() const`
- L55 _public function_ `USkeletalMeshComponent* GetSkeletalMeshComponent() const`
- L57 _public function_ `const FTransform& GetComponentTransform() const`
- L59 _public member_ `FAnimationRecordingSettings AnimationSettings;`
- L63 _private member_ `TWeakObjectPtr<UObject> ObjectToRecord;` — Object to record from
- L66 _private member_ `TWeakObjectPtr<class UMovieSceneSkeletalAnimationSection> MovieSceneSection;` — Section to record to
- L68 _private member_ `TWeakObjectPtr<class UAnimSequence> AnimSequence;`
- L70 _private member_ `TWeakObjectPtr<class USkeletalMeshComponent> SkeletalMeshComponent;`
- L72 _private member_ `TWeakObjectPtr<class USkeletalMesh> SkeletalMesh;`
- L74 _private member_ `bool bRemoveRootTransform;`
- L77 _private member_ `FTransform ComponentTransform;` — Local transform of the component we are recording
- L79 _private member_ `FString AnimAssetPath;`
- L81 _private member_ `FString AnimAssetName;`

### `Source/Editor/SequenceRecorder/Private/Sections/MovieSceneMultiPropertyRecorder.h` (Private)


#### class `FMovieSceneMultiPropertyRecorderFactory`  
`class FMovieSceneMultiPropertyRecorderFactory : public IMovieSceneSectionRecorderFactory`  
_L15-22_
- inherits: `IMovieSceneSectionRecorderFactory`
- L18 _public prototype_ `virtual ~FMovieSceneMultiPropertyRecorderFactory() = default;`
- L20 _public prototype_ `virtual TSharedPtr<IMovieSceneSectionRecorder> CreateSectionRecorder(const struct FActorRecordingSettings& InActorRecordingSettings) const override;`
- L21 _public prototype_ `virtual bool CanRecordObject(UObject* InObjectToRecord) const override;`

#### class `FMovieSceneMultiPropertyRecorder`  
`class FMovieSceneMultiPropertyRecorder : public IMovieSceneSectionRecorder`  
_L24-52_
- inherits: `IMovieSceneSectionRecorder`
- L27 _public prototype_ `FMovieSceneMultiPropertyRecorder();`
- L28 _public prototype_ `virtual ~FMovieSceneMultiPropertyRecorder() = default;`
- L31 _public prototype_ `virtual void CreateSection(UObject* InObjectToRecord, class UMovieScene* InMovieScene, const FGuid& Guid, float Time) override;` — IMovieSceneSectionRecorder interface
- L32 _public prototype_ `virtual void FinalizeSection(float CurrentTime) override;`
- L33 _public prototype_ `virtual void Record(float CurrentTime) override;`
- L34 _public function_ `virtual void InvalidateObjectToRecord() override`
- L38 _public function_ `virtual UObject* GetSourceObject() const override`
- L44 _public prototype_ `static bool CanPropertyBeRecorded(const FProperty& InProperty);` — Check if the property can be recorded
- L48 _private member_ `TWeakObjectPtr<class UObject> ObjectToRecord;` — Object to record from
- L51 _private member_ `TArray<TSharedPtr<class IMovieScenePropertyRecorder>> PropertyRecorders;` — All of our property recorders

### `Source/Editor/SequenceRecorder/Private/SequenceRecorder.h` (Private)


#### struct `FSequenceRecorder`  
`struct FSequenceRecorder`  
_L23-242_
- L26 _public member_ `static FName MovieScenePropertyRecorderFactoryName;`
- L29 _public prototype_ `static FSequenceRecorder& Get();` — Singleton accessor
- L32 _public prototype_ `void Initialize();` — Initialize any resources we need
- L35 _public prototype_ `void Shutdown();` — Clear any resources we need
- L38 _public prototype_ `bool StartRecording(const FString& InPathToRecordTo = FString(), const FString& InSequenceName = FString());` — Starts recording a sequence.
- L41 _public prototype_ `bool StartRecordingForReplay(UWorld* World, const struct FSequenceRecorderActorFilter& ActorFilter);` — Starts recording a sequence for the specified world.
- L44 _public prototype_ `bool StopRecording(bool bAllowLooping = false);` — Stops any currently recording sequence
- L47 _public prototype_ `void Tick(float DeltaSeconds);` — Tick the sequence recorder
- L50 _public prototype_ `bool IsDelaying() const;` — Get whether we are currently delaying a recording
- L53 _public prototype_ `float GetCurrentDelay() const;` — Get the current delay we are waiting for
- L55 _public function_ `TWeakObjectPtr<class ULevelSequence> GetCurrentSequence()`
- L57 _public prototype_ `bool IsRecordingQueued(AActor* Actor) const;`
- L58 _public prototype_ `bool IsRecordingQueued(UObject* SequenceRecordingObjectToRecord) const;`
- L60 _public prototype_ `UActorRecording* FindRecording(AActor* Actor) const;`
- L61 _public prototype_ `USequenceRecordingBase* FindRecording(UObject* SequenceRecordingObjectToRecord) const;`
- L63 _public prototype_ `void StartAllQueuedRecordings();`
- L65 _public prototype_ `void StopAllQueuedRecordings();`
- L67 _public prototype_ `void StopRecordingDeadAnimations();`
- L69 _public prototype_ `void AddNewQueuedRecordingsForSelectedActors();`
- L71 _public prototype_ `void AddNewQueuedRecordingForCurrentPlayer();`
- L73 _public prototype_ `bool CanAddNewQueuedRecordingForCurrentPlayer() const;`
- L75 _public prototype_ `class UActorRecording* AddNewQueuedRecording(AActor* Actor = nullptr, UAnimSequence* AnimSequence = nullptr, float Length = 0.0f);`
- L76 _public prototype_ `class USequenceRecordingBase* AddNewQueuedRecording(UObject* SequenceRecordingObjectToRecord);`
- L78 _public prototype_ `void RemoveQueuedRecording(USequenceRecordingBase* Recording);`
- L80 _public prototype_ `bool HasQueuedRecordings() const;`
- L82 _public prototype_ `void ClearQueuedRecordings();`
- L84 _public function_ `const TArray<UActorRecording*>& GetQueuedActorRecordings()`
- L85 _public function_ `const TArray<USequenceRecordingBase*>& GetQueuedRecordings()`
- L87 _public function_ `bool AreQueuedRecordingsDirty() const`
- L89 _public function_ `void ResetQueuedRecordingsDirty()`
- L91 _public prototype_ `bool IsRecording() const;`
- L94 _public prototype_ `void DrawDebug(UCanvas* InCanvas, APlayerController* InPlayerController);` — Draw the countdown to the screen
- L97 _public prototype_ `void HandleActorSpawned(AActor* Actor);` — Handle actors being spawned
- L100 _public prototype_ `void HandleActorDespawned(AActor* Actor);` — Handle actors being de-spawned
- L102 _public function_ `TWeakObjectPtr<USequenceRecorderActorGroup> GetCurrentRecordingGroup() const`
- L107 _public prototype_ `TWeakObjectPtr<ASequenceRecorderGroup> GetRecordingGroupActor();`
- L109 _public prototype_ `TWeakObjectPtr<USequenceRecorderActorGroup> AddRecordingGroup();`
- L110 _public prototype_ `void RemoveCurrentRecordingGroup();`
- L111 _public prototype_ `TWeakObjectPtr<USequenceRecorderActorGroup> DuplicateRecordingGroup();`
- L112 _public prototype_ `TWeakObjectPtr<USequenceRecorderActorGroup> LoadRecordingGroup(const FName Name);`
- L114 _public prototype_ `TArray<FName> GetRecordingGroupNames() const;`
- L116 _public prototype_ `FString GetSequenceRecordingBasePath() const;`
- L117 _public prototype_ `FString GetSequenceRecordingName() const;`
- L119 _public function_ `TArray<TSharedPtr<ISequenceRecorderExtender>>& GetSequenceRecorderExtenders()`
- L122 _public function_ `const FMovieSceneAnimationSectionRecorderFactory& GetAnimationRecorderFactory() const` — Get the built-in animation factory (as this uses special case handling)
- L128 _public function_ `const FMovieScene3DTransformSectionRecorderFactory& GetTransformRecorderFactory() const` — Get the built-in transform factory (as this uses special case handling)
- L134 _public function_ `const FString& GetNextSequenceName() const` — Get the name of the next sequence we are targeting
- L137 _public prototype_ `void RefreshNextSequence();` — Refresh the name of the next sequence we will be recording
- L140 _public prototype_ `void ForceRefreshNextSequence();` — Force refresh the name of the next sequence, disregard the current sequence name
- L143 _public member_ `FOnRecordingStarted OnRecordingStartedDelegate;` — Multicast delegate fired when recording is started
- L146 _public member_ `FOnRecordingFinished OnRecordingFinishedDelegate;` — Multicast delegate fired when recording has finished
- L149 _public member_ `FOnRecordingGroupAdded OnRecordingGroupAddedDelegate;` — Multicast delegate fired when a recording group has been added
- L153 _private prototype_ `bool StartRecordingInternal(UWorld* World);` — Starts recording a sequence, possibly delayed
- L156 _private prototype_ `bool IsActorValidForRecording(AActor* Actor);` — Check if an actor is valid for recording
- L159 _private prototype_ `void HandleEndPIE(bool bSimulating);` — Handle exiting cleanly from PIE
- L162 _private prototype_ `void SetImmersive();` — Set immersive mode and store whether viewports were immersive
- L165 _private prototype_ `void RestoreImmersive();` — Restore immersive mode to stored value
- L167 _private prototype_ `void BuildQueuedRecordings();`
- L171 _private prototype_ `FSequenceRecorder();` — Constructor, private - use Get() function
- L174 _private member_ `TWeakObjectPtr<class ULevelSequence> CurrentSequence;` — Currently recording level sequence, if any
- L177 _private member_ `TWeakObjectPtr<class UWorld> CurrentReplayWorld;` — World we are recording a replay for, if any. Is only valid if we're recording from Replay network drivers.
- L180 _private member_ `TWeakObjectPtr<class UWorld> CurrentRecordingWorld;` — Actor World that our last started recording was. Null if there is not a recording in progress.
- L183 _private member_ `TWeakObjectPtr<USequenceRecorderActorGroup> CurrentRecorderGroup;` — Recorder Group that our actor recordings go into.
- L186 _private member_ `TWeakObjectPtr<ASequenceRecorderGroup> CachedRecordingActor;` — Cached actor for this level who holds the recording group.
- L188 _private member_ `TArray<UActorRecording*> QueuedActorRecordings;`
- L190 _private member_ `TArray<USequenceRecordingBase*> QueuedRecordings;`
- L192 _private member_ `TArray<USequenceRecordingBase*> DeadRecordings;`
- L194 _private member_ `bool bQueuedRecordingsDirty;`
- L196 _private member_ `bool bWasImmersive;`
- L199 _private member_ `TArray<TSharedPtr<ISequenceRecorderExtender>> SequenceRecorderExtenders;` — Recorder Extenders
- L202 _private member_ `float CurrentDelay;` — The delay we are currently waiting for
- L205 _private member_ `float CurrentTime;` — Current recording time
- L208 _private member_ `float CachedGlobalTimeDilation;` — Cached Global Time dilation, used to restore previous time dilation after recording stops.
- L211 _private member_ `TMap<TWeakObjectPtr<UWorld>, FDelegateHandle> ActorSpawningDelegateHandles;` — Delegate handles for FOnActorSpawned events
- L214 _private member_ `TWeakObjectPtr<UTexture> CountdownTexture;` — Texture we use for the countdown
- L217 _private member_ `TWeakObjectPtr<UTexture> RecordingIndicatorTexture;` — Texture we use for the recording indicator
- L220 _private member_ `FString SequenceName;` — Cached sequence name to record to
- L223 _private member_ `FString NextSequenceName;` — The next sequence we will be targeting. Name can change depending on assets being deleted, moved, renamed etc.
- L226 _private member_ `FString PathToRecordTo;` — Cached sequence path to record to
- L229 _private member_ `FMovieSceneAnimationSectionRecorderFactory AnimationSectionRecorderFactory;` — Built-in animation recorder factory
- L232 _private member_ `FMovieScene3DTransformSectionRecorderFactory TransformSectionRecorderFactory;` — Built-in transform recorder factory
- L235 _private member_ `TUniquePtr<ISequenceAudioRecorder> AudioRecorder;` — Audio recorder
- L238 _private member_ `FMovieSceneMultiPropertyRecorderFactory MultiPropertySectionRecorder;` — Built in multi-property recorder
- L241 _private member_ `TArray<TWeakObjectPtr<ALevelSequenceActor>> DupActorsToTrigger;` — Duplicated level sequence actors to trigger, to be stopped at the end of recording

### `Source/Editor/SequenceRecorder/Private/SequenceRecorderCommands.h` (Private)


#### class `FSequenceRecorderCommands`  
`class FSequenceRecorderCommands : public TCommands<FSequenceRecorderCommands>`  
_L10-27_
- inherits: `TCommands<FSequenceRecorderCommands>`
- L13 _public prototype_ `FSequenceRecorderCommands();`
- L15 _public member_ `TSharedPtr<FUICommandInfo> RecordAll;`
- L16 _public member_ `TSharedPtr<FUICommandInfo> StopAll;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> AddRecording;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> AddCurrentPlayerRecording;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> RemoveRecording;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> RemoveAllRecordings;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> AddRecordingGroup;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> RemoveRecordingGroup;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> DuplicateRecordingGroup;`
- L26 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Source/Editor/SequenceRecorder/Private/SequenceRecorderDetailsCustomization.h` (Private)


#### class `FSequenceRecorderDetailsCustomization`  
`class FSequenceRecorderDetailsCustomization : public IDetailCustomization`  
_L10-20_
- inherits: `IDetailCustomization`
- L13 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Source/Editor/SequenceRecorder/Private/TimecodeBoneMethodCustomization.h` (Private)


#### class `FTimecodeBoneMethodCustomization`  
`class FTimecodeBoneMethodCustomization : public IPropertyTypeCustomization`  
_L14-36_
- inherits: `IPropertyTypeCustomization`
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization instance
- L21 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L25 _protected member_ `TSharedPtr<IPropertyHandle> BoneModeHandle;`
- L26 _protected member_ `TSharedPtr<IPropertyHandle> BoneNameHandle;`
- L30 _private prototype_ `bool IsBoneNameEnabled();`
- L31 _private prototype_ `void OnGetAllowedClasses(TArray<const UClass*>& AllowedClasses);`
- L32 _private prototype_ `bool OnShouldFilterActor(const AActor* const InActor);`
- L33 _private prototype_ `void OnActorSelected(AActor* InActor);`
- L34 _private prototype_ `void ActorComponentPicked(FName ComponentName, AActor* InActor);`
- L35 _private prototype_ `void ActorSocketPicked(FName SocketName, USceneComponent* InComponent);`

### `Source/Editor/SequenceRecorder/Public/ActorRecording.h` (Public)


#### class `UActorRecording`  
`class UActorRecording : public USequenceRecordingBase`  
_L23-162_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USequenceRecordingBase`
- L29 _public prototype_ `static bool IsRelevantForRecording(AActor* Actor);` — Check whether it is worth recording this actor - i.e. is it going to affect the end result of the sequence
- L32 _public prototype_ `virtual bool StartRecording(class ULevelSequence* CurrentSequence = nullptr, float CurrentSequenceTime = 0.0f, const FString& BaseAssetPath = FString(), const FString& SessionName = FString()) override;` — UItemRecordingBase override
- L33 _public prototype_ `virtual bool StopRecording(class ULevelSequence* CurrentSequence = nullptr, float CurrentSequenceTime = 0.0f) override;`
- L34 _public prototype_ `virtual void Tick(ULevelSequence* CurrentSequence = nullptr, float CurrentSequenceTime = 0.0f) override;`
- L35 _public prototype_ `virtual bool IsRecording() const override;`
- L36 _public function_ `virtual UObject* GetObjectToRecord() const override`
- L37 _public function_ `virtual bool IsActive() const override`
- L40 _public prototype_ `void InvalidateObjectToRecord();` — Simulate a de-spawned actor
- L43 _public function_ `const FGuid& GetSpawnableGuid() const` — Get the Guid that identifies our spawnable in a recorded sequence
- L49 _public prototype_ `AActor* GetActorToRecord() const;` — Get the actor to record. This finds the corresponding actor in the Simulation / PIE world.
- L52 _public prototype_ `void SetActorToRecord(AActor* InActor);` — Set the actor to record
- L55 _public prototype_ `ULevelSequence* GetActiveLevelSequence(ULevelSequence* InLevelSequence);` — Get the active level sequence, optionally overridden by the target level sequence
- L58 _public prototype_ `FString GetTargetName(AActor* InActor);` — Get target name
- L61 _public prototype_ `FGuid GetActorInSequence(AActor* InActor, ULevelSequence* CurrentSequence);` — Get the object binding for the actor if it exists in the level sequence either as a track with the track name or a tag with the actor label
- L66 _private prototype_ `bool ShouldDuplicateLevelSequence();` — Get whether should duplicate the level sequence before recording into it
- L69 _private prototype_ `bool ValidComponent(UActorComponent* ActorComponent) const;` — Check component validity for recording
- L72 _private prototype_ `void FindOrAddFolder(UMovieScene* MovieScene);` — Adds us to a folder for better sequence organization
- L75 _private prototype_ `void StartRecordingActorProperties(ULevelSequence* CurrentSequence, float CurrentSequenceTime);` — Start recording actor properties to a sequence
- L78 _private prototype_ `TSharedPtr<class FMovieSceneAnimationSectionRecorder> StartRecordingComponentProperties(const FName& BindingName, UActorComponent* ActorComponent, UObject* BindingContext, ULevelSequence* CurrentSequence, float CurrentSequenceTime, const FAnimationRecordingSettings& InAnimationSettings, UAnimSequence* InTargetSequence);` — Start recording component properties to a sequence
- L81 _private prototype_ `void StartRecordingNewComponents(ULevelSequence* CurrentSequence, float CurrentSequenceTime);` — Start recording components that are added at runtime
- L84 _private prototype_ `void GetAllComponents(TArray<UActorComponent*>& OutArray, bool bIncludeNonCDO = true);` — Helper function to grab all components base actor and scene
- L87 _private prototype_ `void GetSceneComponents(TArray<UActorComponent*>& OutArray, bool bIncludeNonCDO = true);` — Helper function to grab all scene components in the actor's hierarchy
- L90 _private prototype_ `void GetNonSceneActorComponents(TArray<UActorComponent*>& OutArray);` — Helper to get all Non-Scene Actor Componets
- L93 _private prototype_ `void SyncTrackedComponents(bool bIncludeNonCDO = true);` — Sync up tracked components with the actor
- L96 _private prototype_ `void ProcessNewComponentArray(TInlineComponentArray<UActorComponent*>& ProspectiveComponents) const;` — Ensure that we are recording any parents required for the specified component, and sort the specified array
- L99 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L103 _public member_ `FActorRecordingSettings ActorSettings;` — `UPROPERTY(EditAnywhere, Category = "Actor Recording")`
- L107 _public member_ `bool bActive;` — `UPROPERTY(EditAnywhere, Category = "Actor Recording")` — Whether this actor is active and to be recorded when the 'Record' button is pressed.
- L111 _public member_ `bool bCreateLevelSequence;` — `UPROPERTY(EditAnywhere, Category = "Actor Recording")` — Whether to create a level sequence for this actor recording
- L115 _public member_ `TObjectPtr<class ULevelSequence> TargetLevelSequence;` — `UPROPERTY(EditAnywhere, Category = "Actor Recording", meta=(EditCondition = "bCreateLevelSequence"))` — The level sequence to record into
- L119 _public member_ `FText TargetName;` — `UPROPERTY(EditAnywhere, Category = "Actor Recording", meta=(EditCondition = "bCreateLevelSequence"))` — Optional target name to record to. If not specified, the actor label will be used
- L123 _public member_ `uint32 TakeNumber;` — `UPROPERTY(EditAnywhere, Category = "Actor Recording", meta=(EditCondition = "bCreateLevelSequence"))` — Specify the take number for the new recording
- L127 _public member_ `bool bSpecifyTargetAnimation;` — `UPROPERTY(EditAnywhere, Category = "Animation Recording")` — Whether we should specify the target animation or auto-create it
- L131 _public member_ `TObjectPtr<class UAnimSequence> TargetAnimation;` — `UPROPERTY(EditAnywhere, Category = "Animation Recording", meta=(EditCondition = "bSpecifyTargetAnimation"))` — The target animation we want to record to
- L135 _public member_ `FAnimationRecordingSettings AnimationSettings;` — `UPROPERTY(EditAnywhere, Category = "Animation Recording")` — The settings to apply to this actor's animation
- L139 _public member_ `bool bRecordToPossessable;` — `UPROPERTY(EditAnywhere, Category = "Actor Recording")` — Whether to record to 'possessable' (i.e. level-owned) or 'spawnable' (i.e. sequence-owned) actors. Defaults to the global setting.
- L142 _public member_ `bool bWasSpawnedPostRecord;` — Whether this actor recording was triggered from an actor spawn
- L147 _private member_ `TSoftObjectPtr<AActor> ActorToRecord;` — `UPROPERTY(EditAnywhere, Category = "Actor Recording")` — The actor we want to record
- L150 _private member_ `TArray<TSharedPtr<class IMovieSceneSectionRecorder>> SectionRecorders;` — This actor's current set of section recorders
- L153 _private member_ `TArray<TWeakObjectPtr<UActorComponent>> TrackedComponents;` — Track components to check if any have changed
- L155 _private member_ `TMap<FObjectKey, TWeakObjectPtr<UActorComponent>> DuplicatedDynamicComponents;`
- L158 _private member_ `bool bNewComponentAddedWhileRecording;` — Flag to track whether we created new components
- L161 _private member_ `FGuid Guid;` — Guid that identifies our spawnable in a recorded sequence

### `Source/Editor/SequenceRecorder/Public/ActorRecordingSettings.h` (Public)


#### struct `FActorRecordingSettings`  
`struct FActorRecordingSettings`  
_L19-54_
- reflection: `USTRUCT()`
- L23 _public prototype_ `FActorRecordingSettings();`
- L25 _public prototype_ `FActorRecordingSettings(class UObject* InOuter);`
- L27 _public prototype_ `void CreateSettingsObjectsFromFactory();`
- L30 _public function_ `template <typename SettingsType> SettingsType* GetSettingsObject() const`
- L45 _private prototype_ `void CreateSettingsObjectsIfNeeded() const;`
- L50 _private member_ `TArray<TObjectPtr<UObject>> Settings;` — `UPROPERTY(EditAnywhere, Category = "Actor Recording")` — External settings objects for recorders that supply them. Displayed via a details customization
- L53 _private member_ `TWeakObjectPtr<UObject> Outer;` — An optional outer that settings objects should be created with.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SEQUENCERECORDER_API`

### `Source/Editor/SequenceRecorder/Public/AnimationRecorder.h` (Public)


#### struct `FAnimationRecorder`  
`struct FAnimationRecorder : public UE::AnimationRecording::IAnimationRecorder , public FGCObject`  
_L33-191_
- inherits: `UE::AnimationRecording::IAnimationRecorder,FGCObject`
- desc: records the mesh pose to animation input
- L39 _private member_ `static const int32 UnBoundedFrameCount = -1;` — Frame count used to signal an unbounded animation
- L42 _private member_ `FFrameRate RecordingRate;`
- L43 _private member_ `FFrameNumber MaxFrame;`
- L44 _private member_ `FFrameNumber LastFrame;`
- L45 _private member_ `double TimePassed;`
- L46 _private member_ `TObjectPtr<UAnimSequence> AnimationObject;`
- L47 _private member_ `TArray<FTransform> PreviousSpacesBases;`
- L48 _private member_ `FBlendedHeapCurve PreviousAnimCurves;`
- L49 _private member_ `FTransform PreviousComponentToWorld;`
- L50 _private member_ `FTransform InvInitialRootTransform;`
- L51 _private member_ `FTransform InitialRootTransform;`
- L52 _private member_ `int32 SkeletonRootIndex;`
- L55 _private member_ `TMap<UAnimNotify*, UAnimNotify*> UniqueNotifies;` — Unique notifies added to this sequence during recording
- L58 _private member_ `TMap<UAnimNotifyState*, UAnimNotifyState*> UniqueNotifyStates;` — Unique notify states added to this sequence during recording
- L61 _private member_ `TFunction<TOptional<FQualifiedFrameTime>()> GetCurrentFrameTimeFunction;` — This function returns the current timecode that the recorder should use to label the current frame
- L88 _private member_ `TArray<FRecordedAnimNotify> RecordedAnimNotifies;` — Notify events recorded at any point, processed and inserted into animation when recording has finished
- L91 _private member_ `TArray<FRecordedAnimNotify> RecordingAnimNotifies;` — Currently recording notify events that have duration
- L93 _private member_ `static float DefaultSampleRate;`
- L96 _private member_ `TArray<FQualifiedFrameTime> RecordedTimes;` — Array of times recorded
- L99 _public prototype_ `FAnimationRecorder();`
- L103 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface start
- L104 _public function_ `virtual FString GetReferencerName() const override`
- L111 _public prototype_ `bool TriggerRecordAnimation(USkeletalMeshComponent* Component);` — Starts recording an animation. Prompts for asset path and name via dialog if none provided
- L112 _public prototype_ `bool TriggerRecordAnimation(USkeletalMeshComponent* Component, const FString& AssetPath, const FString& AssetName);`
- L115 _public prototype_ `virtual void StartRecord(USkeletalMeshComponent* Component, UAnimSequence* InAnimationObject) override;` — IAnimationRecorder interface start
- L116 _public prototype_ `virtual UAnimSequence* StopRecord(bool bShowMessage) override;`
- L117 _public prototype_ `virtual void UpdateRecord(USkeletalMeshComponent* Component, float DeltaTime) override;`
- L118 _public function_ `virtual bool InRecording() const override`
- L121 _public prototype_ `virtual void SetCurrentFrameTimeGetter(TFunction<TOptional<FQualifiedFrameTime>()> InGetCurrentTimeFunction) override;` — Sets the function that should be used to get the current timecode for the current frame.
- L123 _public function_ `virtual const FTransform& GetInitialRootTransform() const override`
- L126 _public prototype_ `virtual void ProcessRecordedTimes(UAnimSequence* AnimSequence, USkeletalMeshComponent* SkeletalMeshComponent, const FTimecodeBoneMethod& TimecodeBoneMethod, const FProcessRecordedTimeParams& TimecodeInfo) override;` — Process any time data captured and apply it to the bones on the given SkeletalMeshComponent.
- L129 _public function_ `UAnimSequence* GetAnimationObject() const`
- L130 _public function_ `double GetTimeRecorded() const`
- L133 _public prototype_ `void SetSampleRateAndLength(FFrameRate SampleFrameRate, float LengthInSeconds);` — Sets a new sample rate & max length for this recorder. Don't call while recording.
- L135 _public prototype_ `bool SetAnimCompressionScheme(UAnimBoneCompressionSettings* Settings);`
- L138 _public prototype_ `void ProcessRecordedTimes(UAnimSequence* AnimSequence, USkeletalMeshComponent* SkeletalMeshComponent, const FString& HoursName, const FString& MinutesName, const FString& SecondsName, const FString& FramesName, const FString& SubFramesName, const FString& SlateName, const FString& Slate, const FTimecodeBoneMethod& TimecodeBoneMethod);` — `UE_DEPRECATED(5.5, "Use the ProcessRecordedTimes method that takes a FProcessRecordedTimeParams struct.")`
- L141 _public member_ `uint8 bRecordLocalToWorld :1;` — If true, it will record root to include LocalToWorld
- L143 _public member_ `uint8 bAutoSaveAsset : 1;` — If true, asset will be saved to disk after recording. If false, asset will remain in mem and can be manually saved.
- L145 _public member_ `uint8 bRemoveRootTransform : 1;` — If true, the root bone transform will be removed from all bone transforms
- L147 _public member_ `uint8 bCheckDeltaTimeAtBeginning : 1;` — If true we check delta time at beginning of recording
- L149 _public member_ `EAnimInterpolationType Interpolation;` — Interpolation type for the recorded sequence
- L151 _public member_ `ERichCurveInterpMode InterpMode;` — The interpolation mode for the recorded keys
- L153 _public member_ `ERichCurveTangentMode TangentMode;` — The tangent mode for the recorded keys
- L155 _public member_ `FAnimationSerializer* AnimationSerializer;` — Serializer, if set we also store data out incrementally while running
- L157 _public member_ `uint8 bSetRetargetSourceAsset : 1;` — Whether or not to set Retarget Source Asset
- L159 _public member_ `uint8 bRecordTransforms : 1;` — Whether or not to record transforms
- L161 _public member_ `uint8 bRecordMorphTargets : 1;` — Whether or not to record morph targets
- L163 _public member_ `uint8 bRecordAttributeCurves : 1;` — Whether or not to record attribute curves
- L165 _public member_ `uint8 bRecordMaterialCurves : 1;` — Whether or not to record material curves
- L167 _public member_ `uint8 bSkipCurvesWithZeroValue : 1;` — If enabled, we will skip any curves that have only zero values
- L169 _public member_ `uint8 bRemoveExcludedCurves : 1;` — If enabled, curves in ExcludeAnimationNames that already exist in the target sequence will be removed at the start of recording
- L171 _public member_ `TArray<FString> IncludeAnimationNames;` — Include list
- L173 _public member_ `TArray<FString> ExcludeAnimationNames;` — Exclude list
- L175 _public member_ `bool bTransactRecording;` — Whether or not to transact any IAnimationDataController changes
- L178 _public prototype_ `static void GetBoneTransforms(USkeletalMeshComponent* Component, TArray<FTransform>& BoneTransforms);` — Helper function to get space bases depending on leader pose component
- L181 _private prototype_ `bool Record(USkeletalMeshComponent* Component, FTransform const& ComponentToWorld, const TArray<FTransform>& SpacesBases, const FBlendedHeapCurve& AnimationCurves, int32 FrameToAdd);`
- L183 _private prototype_ `void RecordNotifies(USkeletalMeshComponent* Component, const TArray<FAnimNotifyEventReference>& AnimNotifies, float DeltaTime, float RecordTime);`
- L185 _private prototype_ `void ProcessNotifies();`
- L187 _private prototype_ `bool ShouldSkipName(const FName& InName) const;`
- L189 _private member_ `TArray<FBlendedHeapCurve> RecordedCurves;`
- L190 _private member_ `TArray<FRawAnimSequenceTrack> RawTracks;`

#### struct `FAnimationRecorder::FRecordedAnimNotify`  
`struct FRecordedAnimNotify`  
_L63-85_
- L65 _public function_ `FRecordedAnimNotify(const FAnimNotifyEvent& InNewNotifyEvent, const FAnimNotifyEvent* InOriginalNotifyEvent, float InAnimNotifyStartTime, float InAnimNotifyEndTime) : NewNotifyEvent(InNewNotifyEvent) , OriginalNotifyEvent(InOriginalNotifyEvent) , AnimNotifyStartTime(InAnimNotifyStartTime) , AnimNotifyEndTime(InAnimNotifyEndTime) , bWasActive(true)`
- L74 _public member_ `FAnimNotifyEvent NewNotifyEvent;` — Notify which will be added to this sequence
- L77 _public member_ `const FAnimNotifyEvent* OriginalNotifyEvent;` — Notify which was called on the sequence being recorded
- L80 _public member_ `float AnimNotifyStartTime;` — The time in the recorded animation at which the recorded notify started and ended
- L81 _public member_ `float AnimNotifyEndTime;`
- L84 _public member_ `bool bWasActive;` — Whether this notify was active this frame

#### struct `FAnimRecorderInstance`  
`struct FAnimRecorderInstance : public UE::AnimationRecording::IAnimRecorderInstance`  
_L196-238_
- inherits: `UE::AnimationRecording::IAnimRecorderInstance`
- L199 _public prototype_ `FAnimRecorderInstance();`
- L202 _public prototype_ `void Init(USkeletalMeshComponent* InComponent, const FString& InAssetPath, const FString& InAssetName, const FAnimationRecordingSettings& InSettings);`
- L206 _public prototype_ `virtual void Init(USkeletalMeshComponent* InComponent, UAnimSequence* InSequence, FAnimationSerializer *InAnimationSerializer, const FAnimationRecordingSettings& InSettings) override;` — IAnimRecorderInstance interface start
- L207 _public prototype_ `virtual bool BeginRecording() override;`
- L208 _public prototype_ `virtual void Update(float DeltaTime) override;`
- L209 _public prototype_ `virtual void FinishRecording(bool bShowMessage = true) override;`
- L212 _public prototype_ `virtual void ProcessRecordedTimes(UAnimSequence* AnimSequence, USkeletalMeshComponent* SkeletalMeshComponent, const FTimecodeBoneMethod& TimecodeBoneMethod, const FProcessRecordedTimeParams& TimecodeInfo) override;` — Process any time data captured and apply it to the bones on the given SkeletalMeshComponent.
- L213 _public function_ `virtual TSharedPtr<UE::AnimationRecording::IAnimationRecorder> GetRecorder() const override`
- L217 _public prototype_ `void ProcessRecordedTimes(UAnimSequence* AnimSequence, USkeletalMeshComponent* SkeletalMeshComponent, const FString& HoursName, const FString& MinutesName, const FString& SecondsName, const FString& FramesName, const FString& SubFramesName, const FString& SlateName, const FString& Slate, const FTimecodeBoneMethod& TimecodeBoneMethod);` — `UE_DEPRECATED(5.5, "Use the ProcessRecordedTimes method that takes a FProcessRecordedTimeParams struct.")`
- L220 _private prototype_ `void InitInternal(USkeletalMeshComponent* InComponent, const FAnimationRecordingSettings& Settings, FAnimationSerializer *InAnimationSerializer = nullptr);`
- L223 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SkelComp;`
- L224 _public member_ `TWeakObjectPtr<UAnimSequence> Sequence;`
- L225 _public member_ `FString AssetPath;`
- L226 _public member_ `FString AssetName;`
- L229 _public member_ `int CachedSkelCompForcedLodModel;` — Original ForcedLodModel setting on the SkelComp, so we can modify it and restore it when we are done.
- L231 _public member_ `TSharedPtr<FAnimationRecorder> Recorder;`
- L234 _public member_ `EVisibilityBasedAnimTickOption CachedVisibilityBasedAnimTickOption;` — Used to store/restore update flag when recording
- L237 _public member_ `bool bCachedEnableUpdateRateOptimizations;` — Used to store/restore URO when recording

#### struct `FAnimationRecorderManager`  
`struct FAnimationRecorderManager`  
_L244-283_
- L248 _public prototype_ `static FAnimationRecorderManager& Get();` — Singleton accessor
- L251 _public prototype_ `virtual ~FAnimationRecorderManager();` — Destructor
- L254 _public prototype_ `bool RecordAnimation(USkeletalMeshComponent* Component, const FString& AssetPath = FString(), const FString& AssetName = FString(), const FAnimationRecordingSettings& Settings = FAnimationRecordingSettings());` — Starts recording an animation.
- L256 _public prototype_ `bool RecordAnimation(USkeletalMeshComponent* Component, UAnimSequence* Sequence, const FAnimationRecordingSettings& Settings = FAnimationRecordingSettings());`
- L258 _public prototype_ `bool RecordAnimation(USkeletalMeshComponent* Component, UAnimSequence* Sequence, FAnimationSerializer *InAnimationSerializer, const FAnimationRecordingSettings& Settings = FAnimationRecordingSettings());`
- L260 _public prototype_ `bool IsRecording(USkeletalMeshComponent* Component);`
- L262 _public prototype_ `bool IsRecording();`
- L264 _public prototype_ `UAnimSequence* GetCurrentlyRecordingSequence(USkeletalMeshComponent* Component);`
- L265 _public prototype_ `float GetCurrentRecordingTime(USkeletalMeshComponent* Component);`
- L266 _public prototype_ `void StopRecordingAnimation(USkeletalMeshComponent* Component, bool bShowMessage = true);`
- L267 _public prototype_ `void StopRecordingAllAnimations();`
- L268 _public prototype_ `const FTransform& GetInitialRootTransform(USkeletalMeshComponent* Component) const;`
- L270 _public prototype_ `void Tick(float DeltaTime);`
- L272 _public prototype_ `void Tick(USkeletalMeshComponent* Component, float DeltaTime);`
- L274 _public prototype_ `void StopRecordingDeadAnimations(bool bShowMessage = true);`
- L278 _private prototype_ `FAnimationRecorderManager();` — Constructor, private - use Get() function
- L280 _private member_ `TArray<FAnimRecorderInstance> RecorderInstances;`
- L282 _private prototype_ `void HandleEndPIE(bool bSimulating);`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API SEQUENCERECORDER_API`
- L27 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(AnimationSerialization, Verbose, All);`
- L27 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(AnimationSerialization, Verbose, All);`

### `Source/Editor/SequenceRecorder/Public/IMovieSceneSectionRecorder.h` (Public)


#### class `IMovieSceneSectionRecorder`  
`class IMovieSceneSectionRecorder`  
_L8-45_
- desc: A recorder class used to create and populate individual sections in level sequences
- L18 _public prototype_ `virtual void CreateSection(UObject* InObjectToRecord, class UMovieScene* InMovieScene, const FGuid& InGuid, float InTime) = 0;` — Start recording a section. Should create the section and setup anything needed for recording here. @param	InObjectToRecord	The object (Actor of USceneComponent) to record. @param	InMovieScene		The movie scene we are recording to @param	InGuid				The Guid of the object in the movie scene @param	InTime				The current recording time in the movie scene
- L24 _public prototype_ `virtual void FinalizeSection(float InCurrentTime) = 0;` — Called when recording finishes and the section will no longer be recorded into. @param	InCurrentTime	The current recording time in the movie scene
- L30 _public prototype_ `virtual void Record(float InCurrentTime) = 0;` — Called each frame to record into the section. @param	InCurrentTime	The current recording time in the movie scene
- L38 _public prototype_ `virtual void InvalidateObjectToRecord() = 0;` — Added to deal with actor pooling implementations. Usually a recorder would track a weak ptr to the object to record and no longer record if the object became invalid. This function allows pooling implementations that do not necessarily destroy objects to deal with stopping recording correctly. Usually it is enough to invalidate the object that this recorder is recording, hence the function name.
- L44 _public prototype_ `virtual UObject* GetSourceObject() const = 0;` — Retrieve the source object that this section recorder is recording changes to @return the source object, or nullptr if it's no longer valid

### `Source/Editor/SequenceRecorder/Public/IMovieSceneSectionRecorderFactory.h` (Public)


#### class `IMovieSceneSectionRecorderFactory`  
`class IMovieSceneSectionRecorderFactory : public IModularFeature`  
_L13-37_
- inherits: `IModularFeature`
- desc: Factory class interface that allows the recorder to determine what recorders to apply to actors/components/objects it is presented with.
- L21 _public prototype_ `virtual TSharedPtr<class IMovieSceneSectionRecorder> CreateSectionRecorder(const struct FActorRecordingSettings& InActorRecordingSettings) const = 0;` — Create a section recorder from this factory. @param	InActorRecording	The actor recording that will be using this recorder @return a new property recorder, or nullptr if no recorder needs to be created given the settings
- L30 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const = 0;` — Check whether an object can be recorded by this section recorder. If so then the actor recorder will call CreateSectionRecorder() to acquire a new instance to use in recording. @param	InObjectToRecord	The object to check @return true if the object can be recorded by this recorder
- L36 _public function_ `virtual UObject* CreateSettingsObject(class UObject* InOuter) const` — Create a per-recording settings object. You can access this object at record time using FActorRecordingSettings::Settings @return an object used for user settings for this recorder

### `Source/Editor/SequenceRecorder/Public/ISequenceAudioRecorder.h` (Public)


#### struct `FSequenceAudioRecorderSettings`  
`struct FSequenceAudioRecorderSettings`  
_L11-33_
- desc: Sequencer version of the audio recording settings.
- L14 _public member_ `FDirectoryPath Directory;` — Directory to create the asset within (empty for transient package)
- L17 _public member_ `FString AssetName;` — Name of the asset.
- L20 _public member_ `float RecordingDuration;` — Optional audio recording duration in seconds.
- L23 _public member_ `float GainDb;` — Gain in decibels of the output asset.
- L26 _public member_ `bool bSplitChannels;` — Whether or not to split input channels into separate assets.
- L28 _public function_ `FSequenceAudioRecorderSettings() : RecordingDuration(-1.0f) , GainDb(0.0f) , bSplitChannels(false)`

#### class `ISequenceAudioRecorder`  
`class ISequenceAudioRecorder`  
_L35-47_
- L40 _public prototype_ `virtual ~ISequenceAudioRecorder() = default;` — Virtual destructor
- L43 _public prototype_ `virtual void Start(const FSequenceAudioRecorderSettings& Settings) = 0;` — Start recording audio data
- L46 _public prototype_ `virtual void Stop(TArray<USoundWave*>& OutSoundWaves) = 0;` — Stop recording audio data

### `Source/Editor/SequenceRecorder/Public/ISequenceRecorder.h` (Public)


#### class `ISequenceRecorder`  
`class ISequenceRecorder : public IModuleInterface`  
_L24-178_
- inherits: `IModuleInterface`
- L33 _public prototype_ `virtual bool StartRecording(UWorld* World, const struct FSequenceRecorderActorFilter& ActorFilter) = 0;` — Start recording the passed-in actors. @param	World			The world we use to record actors @param	ActorFilter		Actor filter to gather actors spawned in this world for recording @return true if recording was successfully started
- L36 _public prototype_ `virtual void StopRecording() = 0;` — Stop recording current sequence, if any
- L39 _public prototype_ `virtual bool IsRecording() = 0;` — Are we currently recording a sequence
- L42 _public prototype_ `virtual FQualifiedFrameTime GetCurrentRecordingLength() = 0;` — How long is the currently recording sequence
- L51 _public prototype_ `virtual bool StartRecording(TArrayView<AActor* const> ActorsToRecord, const FString& PathToRecordTo = FString(), const FString& SequenceName = FString()) = 0;` — Start a recording, possibly with some delay (specified by the sequence recording settings). @param	ActorsToRecord		Actors to record. @param	PathToRecordTo		Optional path to a sequence to record to. If none is specified we use the defaults in the settings. @param	SequenceName		Optional name of a sequence to record to. If none is specified we use the defaults in the settings. @return true if recording was successfully started
- L60 _public function_ `bool StartRecording(AActor* ActorToRecord, const FString& PathToRecordTo = FString(), const FString& SequenceName = FString())` — Start a recording, possibly with some delay (specified by the sequence recording settings). @param	ActorToRecord		Actor to record. @param	PathToRecordTo		Optional path to a sequence to record to. If none is specified we use the defaults in the settings. @param	SequenceName		Optional name of a sequence to record to. If none is specified we use the defaults in the settings. @return true if recording was successfully started
- L70 _public prototype_ `virtual void NotifyActorStartRecording(AActor* Actor) = 0;` — Notify we should start recording an actor - usually used for 'actor pooling' implementations to simulate spawning. Has no effect when recording is not in progress. @param	Actor	The actor that was 'spawned'
- L77 _public prototype_ `virtual void NotifyActorStopRecording(AActor* Actor) = 0;` — Notify we should stop recording an actor - usually used for 'actor pooling' implementations to simulate de-spawning. Has no effect when recording is not in progress. @param	Actor	The actor that was 'de-spawned'
- L84 _public prototype_ `virtual FGuid GetRecordingGuid(AActor* Actor) const = 0;` — Get the spawnable Guid in the currently recording movie scene for the specified actor. @param	Actor	The Actor to check @return the spawnable Guid
- L91 _public prototype_ `virtual FDelegateHandle RegisterAudioRecorder(const TFunction<TUniquePtr<ISequenceAudioRecorder>()>& FactoryFunction) = 0;` — Register a function that will return a new audio capturer for the specified parameters @param	FactoryFunction		Function used to generate a new audio recorder @return A handle to be passed to UnregisterAudioRecorder to unregister the recorder
- L97 _public prototype_ `virtual void UnregisterAudioRecorder(FDelegateHandle RegisteredHandle) = 0;` — Unregister a previously registered audio recorder factory function @param	RegisteredHandle	The handle returned from RegisterAudioRecorder
- L103 _public prototype_ `virtual bool HasAudioRecorder() const = 0;` — Check whether we have an audio recorder registered or not @return true if we have an audio recorder registered, false otherwise
- L109 _public prototype_ `virtual UActorRecording* QueueActorToRecord(AActor* ActorToRecord) = 0;` — Add an actor to be recorded when the next recording pass begins @param	ActorToRecord	The actor to queue for recording
- L115 _public prototype_ `virtual USequenceRecordingBase* QueueObjectToRecord(UObject* ObjectToRecord) = 0;` — Add an object to be recorded when the next recording pass begins @param	ObjectToRecord	The object to queue for recording
- L122 _public prototype_ `virtual uint32 GetTakeNumberForActor(AActor* InActor) const = 0;` — Get the take number of an actor that is queued to record in the current group @param	InActor		The actor to fetch the take number for @return the take number for the given actor, 0 if actor isn't queued or no group is active
- L129 _public prototype_ `virtual TUniquePtr<ISequenceAudioRecorder> CreateAudioRecorder() const = 0;` — Attempt to create an audio recorder @param	Settings	Settings for the audio recorder @return A valid ptr to an audio recorder or null
- L132 _public prototype_ `virtual FOnRecordingStarted& OnRecordingStarted() = 0;` — Get the sequence recorder started delegate
- L135 _public prototype_ `virtual FOnRecordingFinished& OnRecordingFinished() = 0;` — Get the sequence recorder finished delegate
- L138 _public prototype_ `virtual FString GetSequenceRecordingName() const = 0;` — Get the name the of the sequence recording.
- L141 _public prototype_ `virtual FString GetSequenceRecordingBasePath() const = 0;` — Get the directory that the sequence should record into.
- L144 _public prototype_ `virtual TWeakObjectPtr<USequenceRecorderActorGroup> GetCurrentRecordingGroup() const = 0;` — Returns the current recording group (if any), otherwise returns nullptr.
- L147 _public prototype_ `virtual TWeakObjectPtr<USequenceRecorderActorGroup> AddRecordingGroup() = 0;` — Adds a new recording group and picks a default name. Returns the new recording group and sets as the current recording group.
- L150 _public prototype_ `virtual void RemoveCurrentRecordingGroup() = 0;` — Removes the current recording group if any. Will make GetRecordingGroup() return nullptr.
- L153 _public prototype_ `virtual TWeakObjectPtr<USequenceRecorderActorGroup> DuplicateRecordingGroup() = 0;` — Duplicates the current recording group if any. Returns the new recording group and sets as the current recording group.
- L156 _public prototype_ `virtual TWeakObjectPtr<USequenceRecorderActorGroup> LoadRecordingGroup(const FName Name) = 0;` — Attempts to load a recording group from the specified name. Returns a pointer to the group if successfully loaded, otherwise nullptr.
- L159 _public prototype_ `virtual TArray<FName> GetRecordingGroupNames() const = 0;` — Returns a list of names for the recording groups stored in this map.
- L162 _public prototype_ `virtual FOnRecordingGroupAdded& OnRecordingGroupAdded() = 0;` — Get the Recording Group added delegate
- L165 _public prototype_ `virtual void AddSequenceRecorderExtender(TSharedPtr<ISequenceRecorderExtender> SequenceRecorderExternder) = 0;` — Add an extension to the SequenceRecorder
- L168 _public prototype_ `virtual void RemoveSequenceRecorderExtender(TSharedPtr<ISequenceRecorderExtender> SequenceRecorderExternder) = 0;` — Remove an extension from the SequenceRecorder
- L177 _public prototype_ `virtual bool RecordSingleNodeInstanceToAnimation(USkeletalMeshComponent* PreviewComponent, UAnimSequence* NewAsset, bool bShowMessage = true) = 0;` — Play the current single node instance on the PreviewComponent from time [0, GetLength()], and record to NewAsset @param: PreviewComponent - this component should contains SingleNodeInstance with time-line based asset, currently support AnimSequence or AnimComposite @param: NewAsset - this is the asset that should be recorded. This will reset all animation data internally @param: bShowMessage - show a notification of new asset creation

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRecordingStarted, class UMovieSceneSequence* );`
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRecordingStarted, class UMovieSceneSequence* );`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRecordingFinished, class UMovieSceneSequence* );`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRecordingFinished, class UMovieSceneSequence* );`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRecordingGroupAdded, TWeakObjectPtr<USequenceRecorderActorGroup> );`
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRecordingGroupAdded, TWeakObjectPtr<USequenceRecorderActorGroup> );`

### `Source/Editor/SequenceRecorder/Public/ISequenceRecorderExtender.h` (Public)


#### class `ISequenceRecorderExtender`  
`class ISequenceRecorderExtender : public TSharedFromThis<ISequenceRecorderExtender>`  
_L14-29_
- inherits: `TSharedFromThis<ISequenceRecorderExtender>`
- L17 _public prototype_ `virtual ~ISequenceRecorderExtender() = default;`
- L19 _public prototype_ `virtual TSharedPtr<IDetailsView> MakeSettingDetailsView() = 0;`
- L21 _public prototype_ `DECLARE_DELEGATE_OneParam(FListViewSelectionChanged, USequenceRecordingBase*);`
- L22 _public prototype_ `virtual TSharedPtr<SWidget> MakeListWidget(TSharedPtr<SListView<USequenceRecordingBase*>>& OutCreatedListView, FListViewSelectionChanged OnListViewSelectionChanged) = 0;`
- L24 _public prototype_ `virtual void SetListViewSelection(USequenceRecordingBase* InSelectedBase) = 0;`
- L26 _public prototype_ `virtual USequenceRecordingBase* AddNewQueueRecording(UObject* SequenceRecordingObjectToRecord) = 0;`
- L28 _public prototype_ `virtual void BuildQueuedRecordings(const TArray<USequenceRecordingBase*>& InQueuedRecordings) = 0;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FListViewSelectionChanged, USequenceRecordingBase*);`

### `Source/Editor/SequenceRecorder/Public/MovieScenePropertyRecorder.h` (Public)


#### class `IMovieScenePropertyRecorder`  
`class IMovieScenePropertyRecorder`  
_L29-38_
- desc: Interface for a generic property recorder
- L32 _public prototype_ `virtual ~IMovieScenePropertyRecorder() = default;`
- L33 _public prototype_ `virtual void Create(UObject* InObjectToRecord, class UMovieScene* InMovieScene, const FGuid& InGuid, float InTime) = 0;`
- L35 _public prototype_ `virtual void Record(UObject* InObjectToRecord, float InCurrentTime) = 0;`
- L37 _public prototype_ `virtual void Finalize(UObject* InObjectToRecord, float InCurrentTime) = 0;`

#### struct `FPropertyKey`  
`template <typename PropertyType> struct FPropertyKey`  
_L42-46_
- desc: Helper struct for recording properties
- L44 _public member_ `PropertyType Value;`
- L45 _public member_ `FFrameNumber Time;`

#### class `FMovieScenePropertyRecorder`  
`template <typename PropertyType> class FMovieScenePropertyRecorder : public IMovieScenePropertyRecorder`  
_L50-144_
- inherits: `IMovieScenePropertyRecorder`
- desc: Recorder for a simple property of type PropertyType
- L53 _public function_ `FMovieScenePropertyRecorder(const FTrackInstancePropertyBindings& InBinding) : Binding(InBinding)`
- L57 _public prototype_ `virtual ~FMovieScenePropertyRecorder() = default;`
- L59 _public function_ `virtual void Create(UObject* InObjectToRecord, class UMovieScene* InMovieScene, const FGuid& InGuid, float InTime) override`
- L69 _public function_ `virtual void Record(UObject* InObjectToRecord, float InCurrentTime) override`
- L97 _public function_ `virtual void Finalize(UObject* InObjectToRecord, float InCurrentTime) override`
- L121 _private prototype_ `bool ShouldAddNewKey(const PropertyType& InNewValue) const;` — Helper function, specialized by type, used to check if we do capture-time filtering of keys based on previous values
- L124 _private prototype_ `class UMovieSceneSection* AddSection(UObject* InObjectToRecord, class UMovieScene* InMovieScene, const FGuid& InGuid, float InTime);` — Helper function, specialized by type, used to add an appropriate section to the movie scene
- L127 _private prototype_ `void AddKeyToSection(UMovieSceneSection* InSection, const FPropertyKey<PropertyType>& InKey);` — Helper function, specialized by type, used to add keys to the movie scene section at Finalize() time
- L130 _private prototype_ `void ReduceKeys(UMovieSceneSection* InSection);` — Helper function, specialized by type, used to reduce keys
- L134 _private member_ `FTrackInstancePropertyBindings Binding;` — Binding for this property
- L137 _private member_ `TArray<FPropertyKey<PropertyType>> Keys;` — The keys that are being recorded
- L140 _private member_ `TWeakObjectPtr<class UMovieSceneSection> MovieSceneSection;` — Section we are recording
- L143 _private member_ `PropertyType PreviousValue;` — Previous value we use to establish whether we should key

#### class `FMovieScenePropertyRecorderEnum`  
`class FMovieScenePropertyRecorderEnum : public IMovieScenePropertyRecorder`  
_L147-237_
- inherits: `IMovieScenePropertyRecorder`
- desc: Recorder for a simple property of type enum
- L150 _public function_ `FMovieScenePropertyRecorderEnum(const FTrackInstancePropertyBindings& InBinding) : Binding(InBinding)`
- L154 _public prototype_ `virtual ~FMovieScenePropertyRecorderEnum() = default;`
- L156 _public function_ `virtual void Create(UObject* InObjectToRecord, class UMovieScene* InMovieScene, const FGuid& InGuid, float InTime) override`
- L166 _public function_ `virtual void Record(UObject* InObjectToRecord, float InCurrentTime) override`
- L194 _public function_ `virtual void Finalize(UObject* InObjectToRecord, float InCurrentTime) override`
- L214 _private prototype_ `bool ShouldAddNewKey(const int64& InNewValue) const;` — Helper function, specialized by type, used to check if we do capture-time filtering of keys based on previous values
- L217 _private prototype_ `class UMovieSceneSection* AddSection(UObject* InObjectToRecord, class UMovieScene* InMovieScene, const FGuid& InGuid, float InTime);` — Helper function, specialized by type, used to add an appropriate section to the movie scene
- L220 _private prototype_ `void AddKeyToSection(UMovieSceneSection* InSection, const FPropertyKey<int64>& InKey);` — Helper function, specialized by type, used to add keys to the movie scene section at Finalize() time
- L223 _private prototype_ `void ReduceKeys(UMovieSceneSection* InSection);` — Helper function, specialized by type, used to reduce keys
- L227 _private member_ `FTrackInstancePropertyBindings Binding;` — Binding for this property
- L230 _private member_ `TArray<FPropertyKey<int64>> Keys;` — The keys that are being recorded
- L233 _private member_ `TWeakObjectPtr<class UMovieSceneSection> MovieSceneSection;` — Section we are recording
- L236 _private member_ `int64 PreviousValue;` — Previous value we use to establish whether we should key

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API SEQUENCERECORDER_API`

### `Source/Editor/SequenceRecorder/Public/SequenceRecorderActorFilter.h` (Public)


#### struct `FSequenceRecorderActorFilter`  
`struct FSequenceRecorderActorFilter`  
_L12-19_
- reflection: `USTRUCT()`
- L18 _public member_ `TArray<TSubclassOf<AActor>> ActorClassesToRecord;` — `UPROPERTY(EditAnywhere, Category="Actor Filter")` — Actor classes to accept for recording

### `Source/Editor/SequenceRecorder/Public/SequenceRecorderActorGroup.h` (Public)


#### class `USequenceRecorderActorGroup`  
`class USequenceRecorderActorGroup : public UObject`  
_L16-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L20 _public function_ `USequenceRecorderActorGroup()`
- L30 _public member_ `FName GroupName;` — `UPROPERTY(EditAnywhere, Category = "Recording Groups")`
- L34 _public member_ `FString SequenceName;` — `UPROPERTY(EditAnywhere, Category = "Recording Groups")` — The base name of the sequence to record to. This name will also be used to auto-generate any assets created by this recording.
- L38 _public member_ `FDirectoryPath SequenceRecordingBasePath;` — `UPROPERTY(EditAnywhere, Category = "Recording Groups", meta = (ContentDir))` — Base path for this recording. Sub-assets will be created in subdirectories as specified
- L42 _public member_ `bool bSpecifyTargetLevelSequence;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Recording Groups")` — Whether we should specify the target level sequence or auto-create it
- L46 _public member_ `TObjectPtr<class ULevelSequence> TargetLevelSequence;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Recording Groups", meta=(EditCondition = "bSpecifyTargetLevelSequence"))` — The level sequence to record into
- L50 _public member_ `bool bDuplicateTargetLevelSequence;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Recording Groups", meta=(EditCondition = "bSpecifyTargetLevelSequence"))` — Whether we should duplicate the target level sequence and record into the duplicate
- L54 _public member_ `bool bRecordTargetLevelSequenceLength;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Recording Groups", meta=(EditCondition = "bSpecifyTargetLevelSequence"))` — Whether we should record to the length of the target level sequence
- L58 _public member_ `TArray<TObjectPtr<UActorRecording>> RecordedActors;` — `UPROPERTY(VisibleAnywhere, Category = "Recording Groups")` — A list of actor recordings in this group which contains both the actors to record as well as settings for each one.
- L60 _public prototype_ `void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`

#### class `ASequenceRecorderGroup`  
`class ASequenceRecorderGroup : public AActor`  
_L67-101_
- reflection: `UCLASS(MinimalAPI, hidedropdown, NotBlueprintable)`
- inherits: `AActor`
- L71 _public function_ `ASequenceRecorderGroup() : AActor()`
- L78 _public function_ `virtual bool IsEditorOnly() const final` — AActor Interface
- L84 _public function_ `TWeakObjectPtr<USequenceRecorderActorGroup> FindActorGroup(const FName& Name)`
- L100 _public member_ `TArray<TObjectPtr<USequenceRecorderActorGroup>> ActorGroups;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SEQUENCERECORDER_API`

### `Source/Editor/SequenceRecorder/Public/SequenceRecorderBlueprintLibrary.h` (Public)


#### class `USequenceRecorderBlueprintLibrary`  
`class USequenceRecorderBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L15-33_
- reflection: `UCLASS(MinimalAPI, meta=(ScriptName="SequenceRecorderLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L24 _private prototype_ `static void StartRecordingSequence(const TArray<AActor*>& ActorsToRecord);` — `UFUNCTION(BlueprintCallable, Category="Sequence Recording")` — Start recording the passed-in actors to a level sequence. @param	ActorsToRecord	The actors to record
- L28 _private prototype_ `static bool IsRecordingSequence();` — `UFUNCTION(BlueprintPure, Category="Sequence Recording")` — Are we currently recording a sequence
- L32 _private prototype_ `static void StopRecordingSequence();` — `UFUNCTION(BlueprintCallable, Category="Sequence Recording")` — Stop recording the current sequence, if any

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SEQUENCERECORDER_API`

### `Source/Editor/SequenceRecorder/Public/SequenceRecorderSettings.h` (Public)


#### enum `EAudioRecordingMode`  
`enum class EAudioRecordingMode : uint8`  
_L23-27_
- reflection: `UENUM()`
- desc: Enum denoting if (and how) to record audio
- L25 _public enumerator_ `None UMETA(DisplayName="Don't Record Audio")`
- L26 _public enumerator_ `AudioTrack UMETA(DisplayName="Into Audio Track")`

#### struct `FPropertiesToRecordForActorClass`  
`struct FPropertiesToRecordForActorClass`  
_L30-48_
- reflection: `USTRUCT()`
- L34 _public function_ `FPropertiesToRecordForActorClass()`
- L37 _public function_ `FPropertiesToRecordForActorClass(TSubclassOf<AActor> InClass) : Class(InClass)`
- L43 _public member_ `TSubclassOf<AActor> Class;` — `UPROPERTY(Config, EditAnywhere, AdvancedDisplay, Category = "Sequence Recording")` — The class of the actor we can record
- L47 _public member_ `TArray<FName> Properties;` — `UPROPERTY(Config, EditAnywhere, AdvancedDisplay, Category = "Sequence Recording")` — List of properties we want to record for this class

#### struct `FPropertiesToRecordForClass`  
`struct FPropertiesToRecordForClass`  
_L51-69_
- reflection: `USTRUCT()`
- L55 _public function_ `FPropertiesToRecordForClass()`
- L58 _public function_ `FPropertiesToRecordForClass(TSubclassOf<UActorComponent> InClass) : Class(InClass)`
- L64 _public member_ `TSubclassOf<UActorComponent> Class;` — `UPROPERTY(Config, EditAnywhere, AdvancedDisplay, Category = "Sequence Recording")` — The class of the object we can record
- L68 _public member_ `TArray<FName> Properties;` — `UPROPERTY(Config, EditAnywhere, AdvancedDisplay, Category = "Sequence Recording")` — List of properties we want to record for this class

#### struct `FSettingsForActorClass`  
`struct FSettingsForActorClass`  
_L72-83_
- reflection: `USTRUCT()`
- L78 _public member_ `TSubclassOf<AActor> Class;` — `UPROPERTY(Config, EditAnywhere, AdvancedDisplay, Category = "Sequence Recording")` — The class of the actor we want to record
- L82 _public member_ `bool bRecordToPossessable = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording")` — Whether to record to 'possessable' (i.e. level-owned) or 'spawnable' (i.e. sequence-owned) actors.

#### class `USequenceRecorderSettings`  
`class USequenceRecorderSettings : public UObject`  
_L86-196_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UObject`
- L90 _private prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L95 _public member_ `bool bCreateLevelSequence;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording")` — Whether to create a level sequence when recording. Actors and animations will be inserted into this sequence
- L99 _public member_ `bool bImmersiveMode;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording")` — Whether to maximize the viewport when recording
- L103 _public member_ `float SequenceLength;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording", meta = (ClampMin="0.0", UIMin = "0.0"))` — The length of the recorded sequence
- L107 _public member_ `float RecordingDelay;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording", meta = (ClampMin="0.0", UIMin = "0.0", ClampMax="9.0", UIMax = "9.0"))` — Delay that we will use before starting recording
- L111 _public member_ `bool bAllowLooping;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording")` — Allow the recording to be looped. Subsequence recorded assets will be saved to unique filenames.
- L115 _public member_ `float GlobalTimeDilation;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "10.0"))` — Global Time dilation to set the world to when recording starts. Useful for playing back a scene in slow motion.
- L119 _public member_ `bool bIgnoreTimeDilation;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording")` — Should Sequence Recorder ignore global time dilation? If true recorded animations will only be as long as they would have been without global time dilation.
- L123 _public member_ `FString AnimationSubDirectory;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording")` — The name of the subdirectory animations will be placed in. Leave this empty to place into the same directory as the sequence base path
- L127 _public member_ `EAudioRecordingMode RecordAudio;` — `UPROPERTY(Config, EditAnywhere, Category = "Audio Recording")` — Whether to record audio alongside animation or not
- L131 _public member_ `float AudioGain;` — `UPROPERTY(Config, EditAnywhere, Category = "Audio Recording", meta = (ClampMin="0.0", UIMin = "0.0"))` — Gain in decibels to apply to recorded audio
- L135 _public member_ `bool bSplitAudioChannelsIntoSeparateTracks;` — `UPROPERTY(Config, EditAnywhere, Category = "Audio Recording")` — Whether or not to split mic channels into separate audio tracks. If not true, a max of 2 input channels is supported.
- L139 _public member_ `bool bReplaceRecordedAudio;` — `UPROPERTY(Config, EditAnywhere, Category = "Audio Recording")` — Replace existing recorded audio with any newly recorded audio
- L143 _public member_ `FText AudioTrackName;` — `UPROPERTY(Config, EditAnywhere, Category = "Audio Recording")` — Name of the recorded audio track name
- L147 _public member_ `FString AudioSubDirectory;` — `UPROPERTY(Config, EditAnywhere, Category = "Audio Recording")` — The name of the subdirectory audio will be placed in. Leave this empty to place into the same directory as the sequence base path
- L151 _public member_ `bool bRecordNearbySpawnedActors;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording")` — Whether to record nearby spawned actors. If an actor matches a class in the ActorFilter, this state will be bypassed.
- L155 _public member_ `float NearbyActorRecordingProximity;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording", meta = (ClampMin="0.0", UIMin = "0.0"))` — Proximity to currently recorded actors to record newly spawned actors.
- L159 _public member_ `bool bRecordWorldSettingsActor;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording")` — Whether to record the world settings actor in the sequence (some games use this to attach world SFX)
- L163 _public member_ `bool bReduceKeys;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording")` — Whether to remove keyframes within a tolerance from the recorded tracks
- L167 _public member_ `bool bAutoSaveAsset;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording")` — Whether to auto-save asset when recording is completed. Defaults to false
- L171 _public member_ `FSequenceRecorderActorFilter ActorFilter;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording")` — Filter to check spawned actors against to see if they should be recorded
- L175 _public member_ `TArray<TWeakObjectPtr<class ALevelSequenceActor>> LevelSequenceActorsToTrigger;` — `UPROPERTY(Transient, EditAnywhere, Category = "Sequence Recording")` — Sequence actors to trigger playback on when recording starts (e.g. for recording synchronized sequences)
- L179 _public member_ `FAnimationRecordingSettings DefaultAnimationSettings;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording")` — Default animation settings which are used to initialize all new actor recording's animation settings
- L183 _public member_ `bool bRecordSequencerSpawnedActors;` — `UPROPERTY(Config, EditAnywhere, AdvancedDisplay, Category = "Sequence Recording")` — Whether to record actors that are spawned by sequencer itself (this is usually disabled as results can be unexpected)
- L187 _public member_ `TArray<FPropertiesToRecordForClass> ClassesAndPropertiesToRecord;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording")` — The properties to record for specified classes. Component classes specified here will be recorded. If an actor does not contain one of these classes it will be ignored.
- L191 _public member_ `TArray<FPropertiesToRecordForActorClass> ActorsAndPropertiesToRecord;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequence Recording")` — The properties to record for specified actors. Actor classes specified here will be recorded. If an actor does not contain one of these properties it will be ignored.
- L195 _public member_ `TArray<FSettingsForActorClass> PerActorSettings;` — `UPROPERTY(Config, EditAnywhere, AdvancedDisplay, Category = "Sequence Recording")` — Settings applied to actors of a specified class

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API SEQUENCERECORDER_API`

### `Source/Editor/SequenceRecorder/Public/SequenceRecorderUtils.h` (Public)


#### struct `SequenceRecorderUtils::FTakeInfo`  
`struct FTakeInfo`  
_L183-194_
- L185 _public function_ `FTakeInfo(const FString& InActorLabel, uint32 InTakeNumber, ULevelSequence* InTargetLevelSequence) : ActorLabel(InActorLabel) , TakeNumber(InTakeNumber) , TargetLevelSequence(InTargetLevelSequence)`
- L191 _public member_ `FString ActorLabel;`
- L192 _public member_ `uint32 TakeNumber;`
- L193 _public member_ `ULevelSequence* TargetLevelSequence;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace SequenceRecorderUtils`
- L28 _function_ `template<typename AssetType> static AssetType* MakeNewAsset(const FString& BaseAssetPath, const FString& BaseAssetName)` (scope `SequenceRecorderUtils`) — Utility function that creates an asset with the specified asset path and name. If the asset cannot be created (as one already exists), we try to postfix the asset name until we can successfully create the asset.
- L66 _function_ `static UObject* DuplicateAsset(const FString& BaseAssetPath, const FString& BaseAssetName, UObject* ObjectToDuplicate)` (scope `SequenceRecorderUtils`)
- L108 _function_ `static FString MakeNewAssetName(const FString& BaseAssetPath, const FString& BaseAssetName)` (scope `SequenceRecorderUtils`)
- L134 _function_ `static FString MakeTakeName(const FString& ActorName, const FString& SessionName, uint32 TakeNumber)` (scope `SequenceRecorderUtils`)
- L144 _function_ `static bool DoesTakeExist(const FString& AssetPath, const FString& ActorName, const FString& SessionName, uint32 TakeNumber)` (scope `SequenceRecorderUtils`)
- L158 _function_ `static int32 GetNewTakeNumber(const FString& AssetPath, const FString& ActorName, const FString& SessionName, uint32 TakeNumber)` (scope `SequenceRecorderUtils`)
- L169 _prototype_ `FString MakeNewGroupName(const FString& BaseAssetPath, const FString& BaseAssetName, const TArray<FName>& ExistingGroupNames);` (scope `SequenceRecorderUtils`) — Make an actor recording group name that is unique to the parent and to level sequence assets
- L172 _prototype_ `bool ParseTakeName(const FString& InTakeName, FString& OutActorName, FString& OutSessionName, uint32& OutTakeNumber, const FString& InSessionName = FString());` (scope `SequenceRecorderUtils`) — Parse the take number into its multiple parts
- L175 _prototype_ `void CreateCameraCutTrack(ULevelSequence* LevelSequence, const FGuid& RecordedCameraGuid, const FMovieSceneSequenceID& SequenceID);` (scope `SequenceRecorderUtils`) — Create a camera cut track for the recorded camera
- L178 _prototype_ `void ExtendSequencePlaybackRange(ULevelSequence* LevelSequence);` (scope `SequenceRecorderUtils`) — Extend the level sequence playback range to encompass the section ranges
- L181 _prototype_ `void SaveAsset(UObject* InObject);` (scope `SequenceRecorderUtils`) — Save the asset
- L196 _prototype_ `void GatherTakeInfo(ULevelSequence* LevelSequence, TArray<FTakeInfo>& TakeInfos);` (scope `SequenceRecorderUtils`)
- L199 _prototype_ `AActor* GetAttachment(AActor* InActor, FName& SocketName, FName& ComponentName);` (scope `SequenceRecorderUtils`) — Helper function - check whether our component hierarchy has some attachment outside of its owned components
- L208 _prototype_ `bool RecordSingleNodeInstanceToAnimation(USkeletalMeshComponent* PreviewComponent, UAnimSequence* NewAsset, bool bShowMessage = true);` (scope `SequenceRecorderUtils`) — Play the current single node instance on the PreviewComponent from time [0, GetLength()], and record to NewAsset @param: PreviewComponent - this component should contains SingleNodeInstance with time-line based asset, currently support AnimSequence or AnimComposite @param: NewAsset - this is the asset that should be recorded. This will reset all animation data internally @param: bShowMessage - show a notification of new asset creation
- L213 _prototype_ `FMovieSceneTimecodeSource GetTimecodeSource();` (scope `SequenceRecorderUtils`) — Get timecode source

### `Source/Editor/SequenceRecorder/Public/SequenceRecordingBase.h` (Public)


#### class `USequenceRecordingBase`  
`class USequenceRecordingBase : public UObject`  
_L15-37_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UObject`
- L21 _public prototype_ `virtual bool StartRecording(class ULevelSequence* CurrentSequence = nullptr, float CurrentSequenceTime = 0.0f, const FString& BaseAssetPath = FString(), const FString& SessionName = FString()) PURE_VIRTUAL(USequenceRecordingBase::StartRecording, return false;);` — Start this queued recording. Sequence can be nullptr
- L24 _public prototype_ `virtual bool StopRecording(class ULevelSequence* CurrentSequence = nullptr, float CurrentSequenceTime = 0.0f) PURE_VIRTUAL(USequenceRecordingBase::StopRecording, return false;);` — Stop this recording. Has no effect if we are not currently recording. Sequence can be nullptr
- L27 _public prototype_ `virtual void Tick(ULevelSequence* CurrentSequence = nullptr, float CurrentSequenceTime = 0.0f) PURE_VIRTUAL(USequenceRecordingBase::Tick, );` — Tick this recording
- L30 _public prototype_ `virtual bool IsRecording() const PURE_VIRTUAL(USequenceRecordingBase::IsRecording, return false;);` — Whether we are currently recording
- L33 _public prototype_ `virtual UObject* GetObjectToRecord() const PURE_VIRTUAL(USequenceRecordingBase::GetObjectToRecord, return nullptr;);` — Get the item to record.
- L36 _public prototype_ `virtual bool IsActive() const PURE_VIRTUAL(USequenceRecordingBase::IsActive, return false;);` — Get the item to record.
