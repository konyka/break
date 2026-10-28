# Runtime / SequenceRuntimeRecorder

- module root: `Source/Runtime/SequenceRuntimeRecorder`
- headers: 3; symbols: 39
- symbol kinds: enum=1, enumerator=4, function=1, member=10, namespace=4, prototype=15, struct=4
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, Slate, SlateCore
- PublicDependencyModuleNames: SerializedRecorderInterface, TimeManagement

### `Source/Runtime/SequenceRuntimeRecorder/Public/IAnimRecorderInstance.h` (Public)


#### struct `UE::AnimationRecording::IAnimRecorderInstance`  
`struct IAnimRecorderInstance`  
_L20-43_
- desc: Base interface for animation recorder instances. Manages the lifecycle of a single recording session for a skeletal mesh component.
- L23 _public prototype_ `virtual ~IAnimRecorderInstance() = default;`
- L26 _public prototype_ `virtual void Init(USkeletalMeshComponent* InComponent, UAnimSequence* InSequence, FAnimationSerializer* InAnimationSerializer, const FAnimationRecordingSettings& InSettings) = 0;` — Initializes the instance to record into an existing animation sequence.
- L29 _public prototype_ `virtual bool BeginRecording() = 0;` — Starts the recording session. Returns true on success.
- L32 _public prototype_ `virtual void Update(float DeltaTime) = 0;` — Records a single frame of pose data. Call each tick while recording.
- L35 _public prototype_ `virtual void FinishRecording(bool bShowMessage = true) = 0;` — Stops recording and finalizes the animation sequence.
- L38 _public prototype_ `virtual void ProcessRecordedTimes( UAnimSequence* AnimSequence, USkeletalMeshComponent* SkeletalMeshComponent, const FTimecodeBoneMethod& TimecodeBoneMethod, const FProcessRecordedTimeParams& TimecodeInfo) = 0;` — Process any time data captured and apply it to the bones on the given SkeletalMeshComponent.
- L42 _public prototype_ `virtual TSharedPtr<UE::AnimationRecording::IAnimationRecorder> GetRecorder() const = 0;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace AnimationRecording` (scope `UE`)

### `Source/Runtime/SequenceRuntimeRecorder/Public/IAnimationRecorder.h` (Public)


#### struct `FProcessRecordedTimeParams`  
`struct FProcessRecordedTimeParams`  
_L20-33_
- L22 _public member_ `FString HoursName;`
- L23 _public member_ `FString MinutesName;`
- L24 _public member_ `FString SecondsName;`
- L25 _public member_ `FString FramesName;`
- L26 _public member_ `FString SubFramesName;`
- L29 _public member_ `TOptional<FString> RateName;` — Optionally support writing the Timecode Rate into time data.
- L31 _public member_ `FString SlateName;`
- L32 _public member_ `FString Slate;`

#### struct `UE::AnimationRecording::IAnimationRecorder`  
`struct IAnimationRecorder`  
_L45-71_
- desc: Base interface for animation recorders. Inheriting from this interface allows different animation recording implementations as required.
- L47 _public prototype_ `virtual ~IAnimationRecorder() = default;`
- L50 _public prototype_ `virtual void StartRecord(USkeletalMeshComponent* Component, UAnimSequence* InAnimationObject) = 0;` — Begins recording pose data from the component into the given animation sequence.
- L53 _public prototype_ `virtual UAnimSequence* StopRecord(bool bShowMessage) = 0;` — Stops recording and finalizes the animation sequence. Returns the recorded sequence.
- L56 _public prototype_ `virtual void UpdateRecord(USkeletalMeshComponent* Component, float DeltaTime) = 0;` — Records a single frame of pose data from the component. Call each tick while recording.
- L59 _public prototype_ `virtual bool InRecording() const = 0;` — Returns true if a recording is currently in progress.
- L62 _public prototype_ `virtual void SetCurrentFrameTimeGetter(TFunction<TOptional<FQualifiedFrameTime>()> InGetCurrentTimeFunction) = 0;` — Sets the function that should be used to get the current timecode for the current frame.
- L65 _public prototype_ `virtual const FTransform& GetInitialRootTransform() const = 0;` — Returns the root bone transform captured at the start of recording.
- L68 _public prototype_ `virtual void ProcessRecordedTimes( UAnimSequence* AnimSequence, USkeletalMeshComponent* SkeletalMeshComponent, const FTimecodeBoneMethod& TimecodeBoneMethod, const FProcessRecordedTimeParams& TimecodeInfo) = 0;` — Process any time data captured and apply it to the bones on the given SkeletalMeshComponent.

#### Free symbols / members of external scopes

- L38 _namespace_ `namespace UE`
- L38 _namespace_ `namespace AnimationRecording` (scope `UE`)

### `Source/Runtime/SequenceRuntimeRecorder/Public/TimecodeBoneMethod.h` (Public)


#### enum `ETimecodeBoneMode`  
`enum class ETimecodeBoneMode : uint8`  
_L11-17_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `All`
- L14 _public enumerator_ `Root`
- L15 _public enumerator_ `UserDefined`
- L16 _public enumerator_ `MAX UMETA(Hidden)`

#### struct `FTimecodeBoneMethod`  
`struct FTimecodeBoneMethod`  
_L20-34_
- reflection: `USTRUCT(BlueprintType)`
- L25 _public function_ `FTimecodeBoneMethod() : BoneMode(ETimecodeBoneMode::Root)` — Default constructor, initializing with default values
- L29 _public member_ `ETimecodeBoneMode BoneMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timecode")` — The timecode bone mode
- L33 _public member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timecode")` — Name of the bone to assign timecode values to
