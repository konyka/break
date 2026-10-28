# Plugins / MetaHumanPipelineCore

- module root: `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore`
- headers: 16; symbols: 677
- symbol kinds: class=46, delegate=2, enum=25, enumerator=102, externvar=1, function=18, macro=13, member=208, namespace=49, prototype=203, struct=4, typedef=6
- PrivateDependencyModuleNames: AudioPlatformConfiguration, CaptureDataCore, Core, CoreUObject, Engine, EventLoop, MetaHumanCaptureData, MetaHumanCoreTech, ModelingOperators, NNE, OpenCV, OpenCVHelper, Projects, SpeechAnimationSolver, UnrealEd
- PublicDependencyModuleNames: Eigen

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore/Private/Pipeline/PipelineProcess.h` (Private)


#### class `UE::MetaHuman::Pipeline::FNodeInternal`  
`class FNodeInternal : public FNode`  
_L19-24_
- inherits: `FNode`
- L23 _public prototype_ `FNodeInternal(const FString& InName);`

#### class `UE::MetaHuman::Pipeline::FPipelineDataQueue`  
`class FPipelineDataQueue`  
_L26-48_
- L30 _public prototype_ `FPipelineDataQueue(const TNodePair& InNodePair);`
- L31 _public prototype_ `FPipelineDataQueue(const FPipelineDataQueue& InOther);`
- L33 _public prototype_ `bool IsEmpty() const;`
- L34 _public prototype_ `bool CanPush() const;`
- L36 _public prototype_ `void Push(const TSharedPtr<FPipelineData>& InPipelineData);`
- L38 _public prototype_ `TSharedPtr<FPipelineData> Pop();`
- L40 _public prototype_ `void RemoveFramesAbove(int32 InFrameNumber);`
- L44 _private member_ `int32 MaxSize = 1;`
- L45 _private member_ `TArray<TSharedPtr<FPipelineData>> Queue;`
- L47 _private member_ `mutable FCriticalSection Mutex;`

#### class `UE::MetaHuman::Pipeline::FPipelineProcess`  
`class FPipelineProcess : public UE::Geometry::FAbortableBackgroundTask`  
_L50-110_
- inherits: `UE::Geometry::FAbortableBackgroundTask`
- L54 _public prototype_ `FPipelineProcess(const TArray<TSharedPtr<FNode>>& InNodes, const TArray<FConnection>& InConnections, const FPipelineRunParameters& InPipelineRunParameters, ENamedThreads::Type InCallingThread);`
- L57 _public prototype_ `void DoWork();`
- L59 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L64 _public member_ `UE::Geometry::FAsyncTaskExecuterWithAbort<FPipelineProcess>* TaskWrapper;`
- L66 _public prototype_ `void StartNode(const TSharedPtr<FNode>& InNode);`
- L67 _public prototype_ `bool ProcessNode(const TSharedPtr<FNode>& InNode);`
- L68 _public prototype_ `void EndNode(const TSharedPtr<FNode>& InNode);`
- L70 _public function_ `bool IsRunning() const`
- L74 _private member_ `TArray<TSharedPtr<FNode>> Nodes;`
- L75 _private member_ `TArray<FConnection> Connections;`
- L77 _private member_ `FPipelineRunParameters PipelineRunParameters;`
- L78 _private member_ `ENamedThreads::Type CallingThread;`
- L80 _private member_ `TSharedPtr<FNode> InternalSourceNode;`
- L81 _private member_ `TSharedPtr<FNode> InternalSyncNode;`
- L83 _private member_ `TMap<TSharedPtr<FNode>, TArray<TSharedPtr<FNode>>> UpstreamNodes;`
- L84 _private member_ `TMap<TSharedPtr<FNode>, TArray<TSharedPtr<FNode>>> DownstreamNodes;`
- L85 _private member_ `TMap<TNodePair, FPipelineDataQueue> Queue;`
- L87 _private prototype_ `void RunPipeline();`
- L88 _private prototype_ `void ConnectPins();`
- L89 _private prototype_ `void MakeNodeConnectionLookupsAndQueues();`
- L91 _private prototype_ `void PushSingleThreaded();`
- L92 _private prototype_ `void PushThreadPerNode();`
- L94 _private member_ `static constexpr int32 MaxRate = 500;` — Arbitrary max processing rate otherwise game thread becomes overloaded handling "frame complete" messages
- L96 _private member_ `FThreadSafeBool bIsRunning = true;`
- L97 _private member_ `FThreadSafeBool bIsProducing = true;`
- L99 _private member_ `static const int32 NotExited = -1;` — Value for ExitFrame for when the value is not actually a frame number
- L100 _private member_ `static const int32 ExitedOnStart = -2;`
- L101 _private member_ `static const int32 ExitedOnEnd = -3;`
- L103 _private member_ `FCriticalSection ExitMutex;`
- L104 _private member_ `int32 ExitFrame = FPipelineProcess::NotExited;`
- L105 _private member_ `TSharedPtr<FPipelineData> ExitPipelineData = nullptr;`
- L107 _private member_ `int32 Frame = 0;`
- L109 _private member_ `double StartTime = 0;`

#### class `UE::MetaHuman::Pipeline::FPipelineNodeProcess`  
`class FPipelineNodeProcess : public UE::Geometry::FAbortableBackgroundTask`  
_L112-129_
- inherits: `UE::Geometry::FAbortableBackgroundTask`
- L116 _public prototype_ `FPipelineNodeProcess(const TSharedPtr<FNode>& InNode, FPipelineProcess* InPipelineProcess);`
- L118 _public prototype_ `void DoWork();`
- L120 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L127 _private member_ `TSharedPtr<FNode> Node;`
- L128 _private member_ `FPipelineProcess* PipelineProcess;`

#### class `UMetaHumanPipelineProcess`  
`class UMetaHumanPipelineProcess : public UObject`  
_L135-170_
- reflection: `UCLASS()`
- inherits: `UObject`
- L141 _public prototype_ `UMetaHumanPipelineProcess();`
- L143 _public prototype_ `virtual void BeginDestroy() override;`
- L145 _public prototype_ `void Start(const TArray<TSharedPtr<UE::MetaHuman::Pipeline::FNode>>& InNodes, const TArray<UE::MetaHuman::Pipeline::FConnection>& InConnections, const UE::MetaHuman::Pipeline::FPipelineRunParameters& InPipelineRunParameters);`
- L149 _public prototype_ `void Stop(bool bInClearMessageQueue = false);`
- L151 _public prototype_ `bool IsRunning() const;`
- L153 _public prototype_ `void PipelineNowInvalid();`
- L157 _private member_ `UE::MetaHuman::Pipeline::FPipelineRunParameters PipelineRunParameters;`
- L159 _private member_ `UE::Geometry::FAsyncTaskExecuterWithAbort<UE::MetaHuman::Pipeline::FPipelineProcess>* Process = nullptr;`
- L161 _private prototype_ `void FrameComplete(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`
- L162 _private prototype_ `void ProcessComplete(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`
- L164 _private member_ `FTimerHandle MessageTimerHandle;`
- L165 _private member_ `TArray<TPair<bool, TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData>>> MessageQueue;`
- L166 _private prototype_ `void AddToMessageQueue(bool bInIsFrameComplete, TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`
- L167 _private prototype_ `void DispatchMessageQueue();`
- L169 _private member_ `bool bClearMessageQueue = false;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MetaHuman` (scope `UE`)
- L13 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)
- L17 _typedef_ `using TNodePair = TPair<TSharedPtr<FNode>, TSharedPtr<FNode>>;` (scope `UE::MetaHuman::Pipeline`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore/Public/Nodes/AudioUtilNodes.h` (Public)


#### class `UE::MetaHuman::Pipeline::FAudioLoadNode`  
`class FAudioLoadNode : public FNode`  
_L15-43_
- inherits: `FNode`
- L19 _public prototype_ `FAudioLoadNode(const FString& InName);`
- L21 _public prototype_ `bool Load(const USoundWave* InSoundWave);`
- L23 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L24 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L25 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L27 _public member_ `float FrameRate = 30;`
- L28 _public member_ `int32 FrameOffset = 0;`
- L37 _private member_ `int32 PcmIndex = 0;`
- L38 _private member_ `int32 StartFrame = -1;`
- L40 _private member_ `TArray<uint8> PcmData;`
- L41 _private member_ `uint16 NumChannels = 0;`
- L42 _private member_ `uint32 SampleRate = 0;`

#### enum `UE::MetaHuman::Pipeline::FAudioLoadNode::ErrorCode`  
`enum ErrorCode`  
_L30-33_
- L32 _public enumerator_ `NoAudio = 0`

#### class `UE::MetaHuman::Pipeline::FAudioSaveNode`  
`class FAudioSaveNode : public FNode`  
_L45-66_
- inherits: `FNode`
- L49 _public prototype_ `FAudioSaveNode(const FString& InName);`
- L51 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L52 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L54 _public member_ `FString FilePath;`
- L63 _private member_ `int32 NumChannels = 0;`
- L64 _private member_ `int32 SampleRate = 0;`
- L65 _private member_ `TArray<uint8> PcmData;`

#### enum `UE::MetaHuman::Pipeline::FAudioSaveNode::ErrorCode`  
`enum ErrorCode`  
_L56-59_
- L58 _public enumerator_ `FailedToSave = 0`

#### class `UE::MetaHuman::Pipeline::FAudioConvertNode`  
`class FAudioConvertNode : public FNode`  
_L68-90_
- inherits: `FNode`
- L72 _public prototype_ `FAudioConvertNode(const FString& InName);`
- L74 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L75 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L77 _public member_ `int32 NumChannels = 0;`
- L78 _public member_ `int32 SampleRate = 0;`
- L88 _private member_ `Audio::FResampler Resampler;`
- L89 _private member_ `bool bResamplerInitialized = false;`

#### enum `UE::MetaHuman::Pipeline::FAudioConvertNode::ErrorCode`  
`enum ErrorCode`  
_L80-84_
- L82 _public enumerator_ `UnsupportedChannelMix = 0`
- L83 _public enumerator_ `FailedToResample`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANPIPELINECORE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MetaHuman` (scope `UE`)
- L12 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore/Public/Nodes/HyprsenseRealtimeNode.h` (Public)


#### enum `EHyprsenseRealtimeNodeDebugImage`  
`enum class EHyprsenseRealtimeNodeDebugImage : uint8`  
_L21-29_
- reflection: `UENUM()`
- L23 _public enumerator_ `None = 0`
- L24 _public enumerator_ `Input UMETA(DisplayName = "Input Video")`
- L25 _public enumerator_ `FaceDetect`
- L26 _public enumerator_ `Headpose`
- L27 _public enumerator_ `Trackers`
- L28 _public enumerator_ `Solver`

#### enum `EHyprsenseRealtimeNodeState`  
`enum class EHyprsenseRealtimeNodeState : uint8`  
_L32-38_
- reflection: `UENUM()`
- L34 _public enumerator_ `Unknown = 0`
- L35 _public enumerator_ `OK`
- L36 _public enumerator_ `NoFace`
- L37 _public enumerator_ `SubjectTooFar`

#### enum `EFaceUnsolvedFrameBehavior`  
`enum class EFaceUnsolvedFrameBehavior : uint8`  
_L42-48_
- reflection: `UENUM()`
- desc: How to handle face frames where head rotation exceeds the allowed yaw or pitch.
- L45 _public enumerator_ `None UMETA(DisplayName = "None")` — Leave the frame empty. Exported curves interpolate across the gap based on the curve interpolation setting.
- L47 _public enumerator_ `NeutralPose UMETA(DisplayName = "Neutral Pose")` — Fill the frame with a neutral face pose.

#### enum `EHyprsenseRealtimeNodeModelConfiguration`  
`enum class EHyprsenseRealtimeNodeModelConfiguration : uint8`  
_L51-56_
- reflection: `UENUM()`
- L53 _public enumerator_ `Default = 0`
- L54 _public enumerator_ `StereoHMC`
- L55 _public enumerator_ `SmallFace`

#### struct `FMonocularAnimationPipelineModels`  
`struct FMonocularAnimationPipelineModels`  
_L59-90_
- reflection: `USTRUCT(BlueprintType)`
- L63 _public prototype_ `FMonocularAnimationPipelineModels();`
- L66 _public prototype_ `void SetModelConfiguration(EHyprsenseRealtimeNodeModelConfiguration InModelConfiguration);` — set the model configuration for the realtime animation pipeline models
- L70 _public member_ `FString NNEBackend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties, meta = (DisplayName = "NNE Backend"))` — The NNE runtime backend to use for inference (e.g. "NNERuntimeCoreML", "NNERuntimeORTCpu")
- L74 _public member_ `FSoftObjectPath FaceDetector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties, meta = (AllowedClasses = "/Script/NNE.NNEModelData"))` — The model which will be used for initial face detection
- L78 _public member_ `FSoftObjectPath FaceHeadPoseTracker;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties, meta = (AllowedClasses = "/Script/NNE.NNEModelData"))` — The model which will be used for face headpose calculation
- L82 _public member_ `FSoftObjectPath FaceSolver;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties, meta = (AllowedClasses = "/Script/NNE.NNEModelData"))` — The model which will be used for solving
- L85 _public prototype_ `bool IsValid() const;` — are all model paths set?
- L89 _private member_ `EHyprsenseRealtimeNodeModelConfiguration ModelConfiguration = EHyprsenseRealtimeNodeModelConfiguration::Default;` — The model configuration — cached so we can re-apply defaults when the backend changes

#### struct `UE::MetaHuman::Pipeline::FModelOutputDesc`  
`struct FModelOutputDesc`  
_L103-112_
- L105 _public member_ `FString Name;`
- L106 _public member_ `UE::NNE::FTensorShape Shape;`
- L111 _public member_ `TConstArrayView<const bool> ActiveControlFlags;` — Solver variants only. For compact outputs where only a subset of controls are active, maps each position in the full layout to whether it is present in the compact output. Empty means all controls are present (no expansion needed).

#### class `UE::MetaHuman::Pipeline::FHyprsenseRealtimeNode`  
`class FHyprsenseRealtimeNode : public FNode, public FHyprsenseUtils`  
_L116-223_
- inherits: `FNode,FHyprsenseUtils`
- L120 _public prototype_ `FHyprsenseRealtimeNode(const FString& InName);`
- L122 _public prototype_ `void SetModels(const FMonocularAnimationPipelineModels& InModels);`
- L124 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L125 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L127 _public prototype_ `bool LoadModels();`
- L137 _public prototype_ `void SetDebugImage(EHyprsenseRealtimeNodeDebugImage InDebugImage);`
- L138 _public prototype_ `EHyprsenseRealtimeNodeDebugImage GetDebugImage();`
- L140 _public prototype_ `void SetFocalLength(float InFocalLength);`
- L141 _public prototype_ `float GetFocalLength();`
- L143 _public prototype_ `void SetHeadStabilization(bool bInHeadStabilization);`
- L144 _public prototype_ `bool GetHeadStabilization() const;`
- L146 _public prototype_ `void SetHeadAllowedRotation(bool bInEnabled, float InLeftRight, float InUpDown);`
- L147 _public prototype_ `void SetHeadRotationErrorHandler(EFaceUnsolvedFrameBehavior InHandler);`
- L149 _public prototype_ `void SetNNEBackend(const FString& InNNEBackend);`
- L151 _public prototype_ `FString GetNNEBackend() const;`
- L169 _private member_ `EHyprsenseRealtimeNodeDebugImage DebugImage = EHyprsenseRealtimeNodeDebugImage::None;`
- L170 _private member_ `FCriticalSection DebugImageMutex;`
- L172 _private member_ `float FocalLength = -1;`
- L173 _private member_ `FCriticalSection FocalLengthMutex;`
- L175 _private member_ `FThreadSafeBool bHeadStabilization = true;`
- L177 _private member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> FaceDetector = nullptr;`
- L178 _private member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> Headpose = nullptr;`
- L179 _private member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> Solver = nullptr;`
- L185 _private member_ `FModelVariant DetectorModelVariant;` — Resolved tensor names and output index maps — populated once in LoadModels. Each model variant (ONNX, CoreML) may use different names for the same logical outputs. The index maps allow Process() to place output buffers at the correct position without per-frame lookups.
- L186 _private member_ `FModelVariant HeadposeModelVariant;`
- L187 _private member_ `FModelVariant SolverModelVariant;`
- L188 _private member_ `TMap<FString, int32> DetectorOutputIndices;`
- L189 _private member_ `TMap<FString, int32> HeadposeOutputIndices;`
- L190 _private member_ `TMap<FString, int32> SolverOutputIndices;`
- L192 _private member_ `const uint32 HeadposeInputSizeX = 256;`
- L193 _private member_ `const uint32 HeadposeInputSizeY = 256;`
- L196 _private member_ `uint32 SolverInputSizeX = 256;` — size of solver input can vary
- L197 _private member_ `uint32 SolverInputSizeY = 512;`
- L200 _private member_ `uint32 DetectorOutputCount = 4212;` — number of face detector outputs can vary
- L202 _private member_ `bool bFaceDetected = false;`
- L203 _private member_ `TArray<FVector2D> TrackingPoints;`
- L204 _private member_ `FVector HeadTranslation = FVector::ZeroVector;`
- L206 _private member_ `bool bApplyAngleLimits = false;`
- L208 _private member_ `const float FaceScoreThreshold = 0.5;`
- L209 _private member_ `float LeftRightHeadRotationThreshold = 45;`
- L210 _private member_ `float UpDownHeadRotationThreshold = 30;`
- L211 _private member_ `EFaceUnsolvedFrameBehavior HeadRotationErrorHandler = EFaceUnsolvedFrameBehavior::None;`
- L213 _private member_ `const float LandmarkAwareSmoothingThresholdInCm = 1.5f;`
- L214 _private member_ `TArray<FVector2D> PreviousTrackingPoints;`
- L215 _private member_ `FTransform PreviousTransform;`
- L216 _private prototype_ `FTransform LandmarkAwareSmooth(const TArray<FVector2D>& InTrackingPoints, const FTransform& InTransform, const float InFocalLength);`
- L218 _private prototype_ `Matrix23f GetTransformFromPoints(const TArray<FVector2D>& InPoints, const FVector2D& InSize, bool bInIsStableBox, Matrix23f& OutTransformInv) const;`
- L220 _private prototype_ `bool CheckModels(TSharedPtr<UE::NNE::IModelInstanceRunSync> InDetector, TSharedPtr<UE::NNE::IModelInstanceRunSync> InHeadpose, TSharedPtr<UE::NNE::IModelInstanceRunSync> InSolver, FModelValidationResult& OutValidationResult) const;`
- L222 _private member_ `FMonocularAnimationPipelineModels MonocularAnimationPipelineModels;`

#### enum `UE::MetaHuman::Pipeline::FHyprsenseRealtimeNode::ErrorCode`  
`enum ErrorCode`  
_L129-135_
- L131 _public enumerator_ `FailedToInitialize = 0`
- L132 _public enumerator_ `FailedToDetect`
- L133 _public enumerator_ `FailedToTrack`
- L134 _public enumerator_ `FailedToSolve`

#### struct `UE::MetaHuman::Pipeline::FHyprsenseRealtimeNode::FModelValidationResult`  
`struct FModelValidationResult`  
_L156-166_
- L159 _public member_ `int32 DetectorVariantIndex = INDEX_NONE;` — Matched variant indices into ModelVariants::Detector/Headpose/Solver tables
- L160 _public member_ `int32 HeadposeVariantIndex = INDEX_NONE;`
- L161 _public member_ `int32 SolverVariantIndex = INDEX_NONE;`
- L164 _public member_ `uint32 SolverInputSizeY = 0;` — FaceSolver matched input size (512x256 standard or 256x128 small-faces)
- L165 _public member_ `uint32 SolverInputSizeX = 0;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METAHUMANPIPELINECORE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace NNE` (scope `UE`)
- L93 _namespace_ `namespace UE`
- L93 _namespace_ `namespace MetaHuman` (scope `UE`)
- L93 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)
- L114 _typedef_ `using FModelVariant = TMap<FString, FModelOutputDesc>;` (scope `UE::MetaHuman::Pipeline`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore/Public/Nodes/HyprsenseRealtimeSmoothingNode.h` (Public)


#### class `UE::MetaHuman::Pipeline::FHyprsenseRealtimeSmoothingNode`  
`class FHyprsenseRealtimeSmoothingNode : public FNode`  
_L16-38_
- inherits: `FNode`
- L20 _public prototype_ `FHyprsenseRealtimeSmoothingNode(const FString& InName);`
- L22 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L23 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L24 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L26 _public member_ `TMap<FName, FMetaHumanRealtimeSmoothingParam> Parameters;`
- L27 _public member_ `double DeltaTime = 0;`
- L36 _private member_ `TSharedPtr<FMetaHumanRealtimeSmoothing> Smoothing;`
- L37 _private member_ `TArray<FName> Keys;`

#### enum `UE::MetaHuman::Pipeline::FHyprsenseRealtimeSmoothingNode::ErrorCode`  
`enum ErrorCode`  
_L29-32_
- L31 _public enumerator_ `SmoothingFailed = 0`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANPIPELINECORE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MetaHuman` (scope `UE`)
- L13 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore/Public/Nodes/HyprsenseUtils.h` (Public)


#### class `UE::MetaHuman::Pipeline::FHyprsenseUtils`  
`class FHyprsenseUtils`  
_L17-49_
- L21 _protected typedef_ `using Matrix23f = Eigen::Matrix<float, 2, 3>;`
- L22 _protected typedef_ `using Matrix32f = Eigen::Matrix<float, 3, 2>;`
- L23 _protected typedef_ `using Matrix33f = Eigen::Matrix<float, 3, 3>;`
- L40 _protected member_ `uint32 DetectorInputSizeX = 300;`
- L41 _protected member_ `uint32 DetectorInputSizeY = 300;`
- L43 _protected prototype_ `Matrix23f GetTransformFromBbox(const Bbox& InBbox, int32 InImageWidth, int32 InImageHeight, int32 InCropBoxSize, float InRotation, bool bInFlip, PartType InPartType) const;`
- L45 _protected prototype_ `TArray<float, TAlignedHeapAllocator<64>> WarpAffineBilinear(const uint8* InSrcImage, int32 InSrcWidth, int32 InSrcHeight, const Matrix23f& InTransform, int32 InTargetWidth, int32 InTargetHeight, bool bInIsDetector) const;`
- L47 _protected prototype_ `TArray<Bbox> HardNMS(const TArray<float, TAlignedHeapAllocator<64>>& InScores, const TArray<float, TAlignedHeapAllocator<64>>& InBoxes, float InIouThreshold, float InProbThreshold, int32 InTotalSize, int32 InTopK = -1) const;`
- L48 _protected prototype_ `float IOU(const Bbox& InBox1, const Bbox& InBox2) const;`

#### struct `UE::MetaHuman::Pipeline::FHyprsenseUtils::Bbox`  
`struct Bbox`  
_L25-31_
- L27 _public member_ `float X1, Y1;`
- L27 _public member_ `float X1, Y1;`
- L28 _public member_ `float X2, Y2;`
- L28 _public member_ `float X2, Y2;`
- L29 _public member_ `float Score;`
- L30 _public member_ `float Area;`

#### enum `UE::MetaHuman::Pipeline::FHyprsenseUtils::PartType`  
`enum class PartType : uint8`  
_L33-38_
- L35 _public enumerator_ `FaceDetector`
- L36 _public enumerator_ `SparseTracker`
- L37 _public enumerator_ `PartwiseTracker`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METAHUMANPIPELINECORE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MetaHuman` (scope `UE`)
- L15 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore/Public/Nodes/ImageUtilNodes.h` (Public)


#### class `UE::MetaHuman::Pipeline::FUEImageLoadNode`  
`class FUEImageLoadNode : public FNode`  
_L21-40_
- inherits: `FNode`
- L25 _public prototype_ `FUEImageLoadNode(const FString& InName);`
- L28 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L30 _public member_ `TUniquePtr<IFramePathResolver> FramePathResolver;`
- L31 _public member_ `bool bFailOnMissingFile = false;`

#### enum `UE::MetaHuman::Pipeline::FUEImageLoadNode::ErrorCode`  
`enum ErrorCode`  
_L33-39_
- L35 _public enumerator_ `FailedToLoadFile = 0`
- L36 _public enumerator_ `FailedToFindFile`
- L37 _public enumerator_ `NoFramePathResolver`
- L38 _public enumerator_ `BadFilePath`

#### class `UE::MetaHuman::Pipeline::FUEImageSaveNode`  
`class FUEImageSaveNode : public FNode`  
_L42-59_
- inherits: `FNode`
- L46 _public prototype_ `FUEImageSaveNode(const FString& InName);`
- L48 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L50 _public member_ `FString FilePath;`
- L51 _public member_ `int32 FrameNumberOffset = 0;`

#### enum `UE::MetaHuman::Pipeline::FUEImageSaveNode::ErrorCode`  
`enum ErrorCode`  
_L53-58_
- L55 _public enumerator_ `FailedToSaveFile = 0`
- L56 _public enumerator_ `FailedToCompressData`
- L57 _public enumerator_ `MissingFrameFormatSpecifier`

#### class `UE::MetaHuman::Pipeline::FUEImageResizeNode`  
`class FUEImageResizeNode : public FNode`  
_L61-70_
- inherits: `FNode`
- L65 _public prototype_ `FUEImageResizeNode(const FString& InName);`
- L67 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L69 _public member_ `int32 MaxSize = 1;`

#### class `UE::MetaHuman::Pipeline::FUEImageCropNode`  
`class FUEImageCropNode : public FNode`  
_L72-89_
- inherits: `FNode`
- L76 _public prototype_ `FUEImageCropNode(const FString& InName);`
- L78 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L80 _public member_ `int32 X = -1;`
- L81 _public member_ `int32 Y = -1;`
- L82 _public member_ `int32 Width = -1;`
- L83 _public member_ `int32 Height = -1;`

#### enum `UE::MetaHuman::Pipeline::FUEImageCropNode::ErrorCode`  
`enum ErrorCode`  
_L85-88_
- L87 _public enumerator_ `BadValues = 0`

#### class `UE::MetaHuman::Pipeline::FUEImageRotateNode`  
`class FUEImageRotateNode : public FNode`  
_L91-111_
- inherits: `FNode`
- L95 _public prototype_ `FUEImageRotateNode(const FString& InName);`
- L97 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L99 _public prototype_ `void SetAngle(float InAngle);`
- L100 _public prototype_ `float GetAngle();`
- L109 _private member_ `float Angle = 0;`
- L110 _private member_ `FCriticalSection AngleMutex;`

#### enum `UE::MetaHuman::Pipeline::FUEImageRotateNode::ErrorCode`  
`enum ErrorCode`  
_L102-105_
- L104 _public enumerator_ `UnsupportedAngle = 0`

#### class `UE::MetaHuman::Pipeline::FUEImageCompositeNode`  
`class FUEImageCompositeNode : public FNode`  
_L113-120_
- inherits: `FNode`
- L117 _public prototype_ `FUEImageCompositeNode(const FString& InName);`
- L119 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FUEImageToUEGrayImageNode`  
`class FUEImageToUEGrayImageNode : public FNode`  
_L122-129_
- inherits: `FNode`
- L126 _public prototype_ `FUEImageToUEGrayImageNode(const FString& InName);`
- L128 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FUEGrayImageToUEImageNode`  
`class FUEGrayImageToUEImageNode : public FNode`  
_L131-138_
- inherits: `FNode`
- L135 _public prototype_ `FUEGrayImageToUEImageNode(const FString& InName);`
- L137 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FUEImageToHSImageNode`  
`class FUEImageToHSImageNode : public FNode`  
_L140-147_
- inherits: `FNode`
- L144 _public prototype_ `FUEImageToHSImageNode(const FString& InName);`
- L146 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FBurnContoursNode`  
`class FBurnContoursNode : public FNode`  
_L149-159_
- inherits: `FNode`
- L153 _public prototype_ `FBurnContoursNode(const FString& InName);`
- L155 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L157 _public member_ `int32 Size = 1;`
- L158 _public member_ `int32 LineWidth = 0;` — set this to a value > 0 to connect the contour points by lines

#### class `UE::MetaHuman::Pipeline::FDepthLoadNode`  
`class FDepthLoadNode : public FNode`  
_L161-179_
- inherits: `FNode`
- L165 _public prototype_ `FDepthLoadNode(const FString& InName);`
- L168 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L170 _public member_ `TUniquePtr<IFramePathResolver> FramePathResolver;`
- L171 _public member_ `bool bFailOnMissingFile = false;`

#### enum `UE::MetaHuman::Pipeline::FDepthLoadNode::ErrorCode`  
`enum ErrorCode`  
_L173-178_
- L175 _public enumerator_ `FailedToLoadFile = 0`
- L176 _public enumerator_ `FailedToFindFile`
- L177 _public enumerator_ `NoFramePathResolver`

#### class `UE::MetaHuman::Pipeline::FDepthSaveNode`  
`class FDepthSaveNode : public FNode`  
_L181-199_
- inherits: `FNode`
- L185 _public prototype_ `FDepthSaveNode(const FString& InName);`
- L187 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L189 _public member_ `FString FilePath;`
- L190 _public member_ `int32 FrameNumberOffset = 0;`
- L191 _public member_ `bool bShouldCompressFiles = true;`

#### enum `UE::MetaHuman::Pipeline::FDepthSaveNode::ErrorCode`  
`enum ErrorCode`  
_L193-198_
- L195 _public enumerator_ `FailedToSaveFile = 0`
- L196 _public enumerator_ `FailedToCompressData`
- L197 _public enumerator_ `MissingFrameFormatSpecifier`

#### class `UE::MetaHuman::Pipeline::FDepthQuantizeNode`  
`class FDepthQuantizeNode : public FNode`  
_L201-210_
- inherits: `FNode`
- L205 _public prototype_ `FDepthQuantizeNode(const FString& InName);`
- L207 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L209 _public member_ `float Factor = 80;` — Eightieth of a cm (0.125mm). This equals the oodle compression quantization.

#### class `UE::MetaHuman::Pipeline::FDepthResizeNode`  
`class FDepthResizeNode : public FNode`  
_L212-221_
- inherits: `FNode`
- L216 _public prototype_ `FDepthResizeNode(const FString& InName);`
- L218 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L220 _public member_ `int32 Factor = 1;`

#### class `UE::MetaHuman::Pipeline::FDepthToUEImageNode`  
`class FDepthToUEImageNode : public FNode`  
_L223-238_
- inherits: `FNode`
- L227 _public prototype_ `FDepthToUEImageNode(const FString& InName);`
- L229 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L231 _public member_ `float Min = 0.0f;`
- L232 _public member_ `float Max = 1.0f;`

#### enum `UE::MetaHuman::Pipeline::FDepthToUEImageNode::ErrorCode`  
`enum ErrorCode`  
_L234-237_
- L236 _public enumerator_ `BadRange = 0`

#### class `UE::MetaHuman::Pipeline::FFColorToUEImageNode`  
`class FFColorToUEImageNode : public FNode`  
_L240-255_
- inherits: `FNode`
- L243 _public prototype_ `FFColorToUEImageNode(const FString& InName);`
- L245 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L247 _public member_ `TArray<FColor> Samples;`
- L248 _public member_ `int32 Width = -1;`
- L249 _public member_ `int32 Height = -1;`

#### enum `UE::MetaHuman::Pipeline::FFColorToUEImageNode::ErrorCode`  
`enum ErrorCode`  
_L251-254_
- L253 _public enumerator_ `NoInputImage = 0`

#### class `UE::MetaHuman::Pipeline::FCopyImagesNode`  
`class FCopyImagesNode : public FNode`  
_L257-275_
- inherits: `FNode`
- L260 _public prototype_ `FCopyImagesNode(const FString& InName);`
- L262 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L264 _public member_ `int32 FrameNumberOffset = 0;`
- L266 _public member_ `FString InputFilePath;`
- L267 _public member_ `FString OutputDirectoryPath;`

#### enum `UE::MetaHuman::Pipeline::FCopyImagesNode::ErrorCode`  
`enum ErrorCode`  
_L269-274_
- L271 _public enumerator_ `FailedToFindFile = 0`
- L272 _public enumerator_ `FailedToCopyFile`
- L273 _public enumerator_ `MissingFrameFormatSpecifier`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANPIPELINECORE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MetaHuman` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MetaHuman` (scope `UE`)
- L18 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore/Public/Nodes/NeutralFrameNode.h` (Public)


#### class `UE::MetaHuman::Pipeline::FNeutralFrameNode`  
`class FNeutralFrameNode : public FNode`  
_L16-25_
- inherits: `FNode`
- L20 _public prototype_ `FNeutralFrameNode(const FString& InName);`
- L22 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L24 _public member_ `FThreadSafeBool bIsNeutralFrame = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANPIPELINECORE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MetaHuman` (scope `UE`)
- L13 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore/Public/Nodes/RealtimeSpeechToAnimNode.h` (Public)


#### class `UE::MetaHuman::Pipeline::FRealtimeSpeechToAnimNode`  
`class FRealtimeSpeechToAnimNode : public FNode`  
_L17-61_
- inherits: `FNode`
- L21 _public prototype_ `FRealtimeSpeechToAnimNode(const FString& InName);`
- L23 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L24 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L25 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L27 _public prototype_ `bool LoadModels();`
- L29 _public prototype_ `void SetMood(EAudioDrivenAnimationMood InMood);`
- L30 _public prototype_ `EAudioDrivenAnimationMood GetMood(void);`
- L32 _public prototype_ `void SetMoodIntensity(float InMoodIntensity);`
- L33 _public prototype_ `float GetMoodIntensity(void);`
- L35 _public prototype_ `void SetLookahead(int32 InLookahead);`
- L36 _public prototype_ `int32 GetLookahead(void);`
- L38 _public prototype_ `void SetNNEBackend(const FString& InNNEBackend);`
- L39 _public prototype_ `FString GetNNEBackend(void) const;`
- L51 _private member_ `TSharedPtr<FSpeechAnimationSolverV4> Solver = nullptr;`
- L53 _private member_ `FString NNEBackend;`
- L55 _private member_ `EAudioDrivenAnimationMood Mood = EAudioDrivenAnimationMood::AutoDetect;`
- L56 _private member_ `float MoodIntensity = 1.0;`
- L57 _private member_ `FCriticalSection MoodMutex;`
- L59 _private member_ `int32 Lookahead = 80;`
- L60 _private member_ `FCriticalSection LookaheadMutex;`

#### enum `UE::MetaHuman::Pipeline::FRealtimeSpeechToAnimNode::ErrorCode`  
`enum ErrorCode`  
_L41-47_
- L43 _public enumerator_ `FailedToInitialize = 0`
- L44 _public enumerator_ `UnsupportedNumberOfChannels`
- L45 _public enumerator_ `UnsupportedSampleRate`
- L46 _public enumerator_ `FailedToRun`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANPIPELINECORE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MetaHuman` (scope `UE`)
- L14 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore/Public/Pipeline/Connection.h` (Public)


#### class `UE::MetaHuman::Pipeline::FConnection`  
`class FConnection`  
_L14-26_
- L18 _public prototype_ `FConnection(const TSharedPtr<FNode>& InFrom, const TSharedPtr<FNode>& InTo, int32 InFromGroup = 0, int32 InToGroup = 0);`
- L20 _public member_ `TSharedPtr<FNode> From;`
- L21 _public member_ `TSharedPtr<FNode> To;`
- L22 _public member_ `int32 FromGroup;`
- L23 _public member_ `int32 ToGroup;`
- L25 _public prototype_ `FString ToString() const;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANPIPELINECORE_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MetaHuman` (scope `UE`)
- L9 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore/Public/Pipeline/DataTree.h` (Public)


#### class `UE::MetaHuman::Pipeline::FDataTree`  
`class FDataTree`  
_L15-127_
- L20 _public function_ `template<typename T> void SetData(const FPin& InPin, const T& InValue)`
- L27 _public function_ `template<typename T> void SetData(const FPin& InPin, T&& InValue)`
- L34 _public function_ `template<typename T> void SetData(const FString& InName, const T& InValue)`
- L46 _public function_ `template<typename T> void SetData(const FString& InName, T&& InValue)`
- L58 _public function_ `template<typename T> bool HasData(const FString& InName) const`
- L70 _public function_ `template<typename T> const T& GetData(const FPin& InPin) const`
- L77 _public function_ `template<typename T> const T& GetData(const FString& InName) const`
- L96 _public function_ `template<typename T> T&& MoveData(const FString& InName)`
- L114 _public prototype_ `void MoveTo(TSharedPtr<FDataTree> InOther);`
- L116 _public prototype_ `FString ToString(int32 InDepth = 0) const;`
- L120 _private member_ `FDataTreeType Data;`
- L121 _private member_ `TMap<FString, TSharedPtr<FDataTree>> Children;`
- L123 _private member_ `mutable FCriticalSection Mutex;`
- L125 _private prototype_ `TSharedPtr<FDataTree> GetChild(const FString& InName) const;`
- L126 _private prototype_ `TSharedPtr<FDataTree> GetChildOrCreate(const FString& InName);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANPIPELINECORE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MetaHuman` (scope `UE`)
- L12 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore/Public/Pipeline/DataTreeTypes.h` (Public)


#### class `UE::MetaHuman::Pipeline::FInvalidDataType`  
`class FInvalidDataType`  
_L17-19_

#### enum `UE::MetaHuman::Pipeline::EPipelineExitStatus`  
`enum class EPipelineExitStatus`  
_L21-43_
- L23 _public enumerator_ `Unknown = 0`
- L24 _public enumerator_ `OutOfScope`
- L25 _public enumerator_ `AlreadyRunning`
- L26 _public enumerator_ `NotInGameThread`
- L27 _public enumerator_ `InvalidNodeTypeName`
- L28 _public enumerator_ `InvalidNodeName`
- L29 _public enumerator_ `DuplicateNodeName`
- L30 _public enumerator_ `InvalidPinName`
- L31 _public enumerator_ `DuplicatePinName`
- L32 _public enumerator_ `InvalidConnection`
- L33 _public enumerator_ `AmbiguousConnection`
- L34 _public enumerator_ `Unconnected`
- L35 _public enumerator_ `LoopConnection`
- L36 _public enumerator_ `Ok`
- L37 _public enumerator_ `Aborted`
- L38 _public enumerator_ `StartError`
- L39 _public enumerator_ `ProcessError`
- L40 _public enumerator_ `EndError`
- L41 _public enumerator_ `TooFast`
- L42 _public enumerator_ `InsufficientThreadsForNodes`

#### class `UE::MetaHuman::Pipeline::FUEImageDataType`  
`class FUEImageDataType`  
_L45-52_
- L49 _public member_ `int32 Width = -1;`
- L50 _public member_ `int32 Height = -1;`
- L51 _public member_ `TArray<uint8> Data;` — bgra order, a=255 for fully opaque

#### class `UE::MetaHuman::Pipeline::FUEGrayImageDataType`  
`class FUEGrayImageDataType`  
_L54-61_
- L58 _public member_ `int32 Width = -1;`
- L59 _public member_ `int32 Height = -1;`
- L60 _public member_ `TArray<uint8> Data;`

#### class `UE::MetaHuman::Pipeline::FHSImageDataType`  
`class FHSImageDataType`  
_L63-70_
- L67 _public member_ `int32 Width = -1;`
- L68 _public member_ `int32 Height = -1;`
- L69 _public member_ `TArray<float> Data;`

#### class `UE::MetaHuman::Pipeline::FScalingDataType`  
`class FScalingDataType`  
_L72-77_
- L76 _public member_ `float Factor = -1.0f;`

#### class `UE::MetaHuman::Pipeline::FDepthDataType`  
`class FDepthDataType`  
_L79-86_
- L83 _public member_ `int32 Width = -1;`
- L84 _public member_ `int32 Height = -1;`
- L85 _public member_ `TArray<float> Data;`

#### class `UE::MetaHuman::Pipeline::FFlowOutputDataType`  
`class FFlowOutputDataType`  
_L88-96_
- L92 _public member_ `TArray<float> Flow;`
- L93 _public member_ `TArray<float> Confidence;`
- L94 _public member_ `TArray<float> SourceCamera;`
- L95 _public member_ `TArray<float> TargetCamera;`

#### class `UE::MetaHuman::Pipeline::FAudioDataType`  
`class FAudioDataType`  
_L98-107_
- L102 _public member_ `int32 NumChannels = -1;`
- L103 _public member_ `int32 SampleRate = -1;`
- L104 _public member_ `int32 NumSamples = -1;`
- L105 _public member_ `TArray<float> Data;`
- L106 _public member_ `bool bContiguous = true;` — whether consecutive audio sample are contiguous

#### class `UE::MetaHuman::Pipeline::FCalibrationDataType`  
`class FCalibrationDataType`  
_L109-137_
- L121 _public member_ `FString CameraId;`
- L122 _public member_ `EType CameraType = EType::Unknown;`
- L124 _public member_ `FVector2D ImageSize = FVector2D::Zero();`
- L125 _public member_ `FVector2D FocalLength = FVector2D::Zero();`
- L126 _public member_ `FVector2D PrincipalPoint = FVector2D::Zero();`
- L128 _public member_ `double K1 = 0;`
- L129 _public member_ `double K2 = 0;`
- L130 _public member_ `double P1 = 0;`
- L131 _public member_ `double P2 = 0;`
- L132 _public member_ `double K3 = 0;`
- L133 _public member_ `double K4 = 0;`
- L134 _public member_ `double K5 = 0;`
- L135 _public member_ `double K6 = 0;`
- L136 _public member_ `FMatrix Transform = FMatrix::Identity;`

#### enum `UE::MetaHuman::Pipeline::FCalibrationDataType::EType`  
`enum EType`  
_L113-119_
- L115 _public enumerator_ `Video = 0`
- L116 _public enumerator_ `Depth`
- L118 _public enumerator_ `Unknown`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MetaHuman` (scope `UE`)
- L14 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)
- L139 _typedef_ `using FDataTreeType = TVariant<FInvalidDataType, EPipelineExitStatus, int32, float, double, bool, FString, FUEImageDataType, FUEGrayImageDataType, FHSImageDataType, FScalingDataType, FFrameTrackingContourData, FFrameAnimationData, FDepthDataType, FFrameTrackingConfidenceData, TArray<int32>, TArray<FFrameAnimationData>, FFlowOutputDataType, TMap<FString, FDepthMapDiagnosticsResult>, FAudioDataType, FQualifiedFrameTime, FCalibrationDataType>;` (scope `UE::MetaHuman::Pipeline`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore/Public/Pipeline/Log.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanPipeline, Log, All);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore/Public/Pipeline/Node.h` (Public)


#### class `UE::MetaHuman::Pipeline::FNode`  
`class FNode`  
_L14-40_
- L18 _public prototype_ `FNode(const FString& InTypeName, const FString& InName);`
- L19 _public prototype_ `virtual ~FNode();`
- L21 _public function_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData)`
- L22 _public function_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData)`
- L23 _public function_ `virtual bool Idle(const TSharedPtr<FPipelineData>& InPipelineData)`
- L24 _public function_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData)`
- L26 _public function_ `virtual bool RequiresIdle() const`
- L27 _public function_ `virtual bool ProcessesExitFrame() const`
- L29 _public member_ `FString TypeName;`
- L30 _public member_ `FString Name;`
- L31 _public member_ `FString ID;`
- L33 _public member_ `TArray<FPin> Pins;`
- L35 _public member_ `int32 QueueSize = 1;`
- L37 _public prototype_ `FString ToString() const;`
- L39 _public member_ `const bool *bAbort = nullptr;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANPIPELINECORE_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MetaHuman` (scope `UE`)
- L9 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore/Public/Pipeline/Pin.h` (Public)


#### enum `UE::MetaHuman::Pipeline::EPinDirection`  
`enum class EPinDirection`  
_L12-16_
- L14 _public enumerator_ `Input = 0`
- L15 _public enumerator_ `Output`

#### enum `UE::MetaHuman::Pipeline::EPinType`  
`enum class EPinType`  
_L18-41_
- desc: Cant replace with std::type_info, due to RTTI
- L20 _public enumerator_ `Int = 0`
- L21 _public enumerator_ `Float`
- L22 _public enumerator_ `Bool`
- L23 _public enumerator_ `String`
- L24 _public enumerator_ `UE_Image` — 4 channel BGRA
- L25 _public enumerator_ `UE_GrayImage` — single channel
- L26 _public enumerator_ `HS_Image`
- L27 _public enumerator_ `Points`
- L28 _public enumerator_ `Contours`
- L29 _public enumerator_ `Scaling`
- L30 _public enumerator_ `Animation`
- L31 _public enumerator_ `Depth`
- L32 _public enumerator_ `TrackingConfidence`
- L33 _public enumerator_ `LiveLinkFrame`
- L34 _public enumerator_ `IntArray`
- L35 _public enumerator_ `AnimationArray`
- L36 _public enumerator_ `FlowOutput`
- L37 _public enumerator_ `DepthMapDiagnostics`
- L38 _public enumerator_ `Audio`
- L39 _public enumerator_ `QualifiedFrameTime`
- L40 _public enumerator_ `Calibration`

#### class `UE::MetaHuman::Pipeline::FPin`  
`class FPin`  
_L43-61_
- L47 _public prototype_ `FPin(const FString& InName, EPinDirection InDirection, EPinType InType);`
- L48 _public prototype_ `FPin(const FString& InName, EPinDirection InDirection, EPinType InType, int32 InGroup);`
- L49 _public prototype_ `FPin(const FString& InName, EPinDirection InDirection, EPinType InType, int32 InGroup, bool bInIsPassthrough, bool bInIsOptional);`
- L51 _public member_ `FString Name;`
- L52 _public member_ `EPinDirection Direction;`
- L53 _public member_ `EPinType Type;`
- L54 _public member_ `int32 Group = 0;`
- L55 _public member_ `bool bIsPassthrough = true;`
- L56 _public member_ `bool bIsOptional = false;`
- L58 _public member_ `FString Address;`
- L60 _public prototype_ `FString ToString() const;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANPIPELINECORE_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MetaHuman` (scope `UE`)
- L9 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore/Public/Pipeline/Pipeline.h` (Public)


#### enum `UE::MetaHuman::Pipeline::EPipelineMode`  
`enum class EPipelineMode`  
_L24-31_
- L26 _public enumerator_ `PushSync = 0`
- L27 _public enumerator_ `PushAsync`
- L28 _public enumerator_ `PushSyncNodes`
- L29 _public enumerator_ `PushAsyncNodes`
- L30 _public enumerator_ `Pull`

#### class `UE::MetaHuman::Pipeline::FPipelineRunParameters`  
`class FPipelineRunParameters`  
_L33-93_
- L37 _public prototype_ `FPipelineRunParameters() = default;`
- L39 _public prototype_ `void SetMode(EPipelineMode InMode);`
- L40 _public prototype_ `EPipelineMode GetMode() const;`
- L42 _public prototype_ `void SetOnFrameComplete(const FFrameComplete& InOnFrameComplete);`
- L43 _public prototype_ `const FFrameComplete& GetOnFrameComplete() const;`
- L45 _public prototype_ `void SetOnProcessComplete(const FProcessComplete& InOnProcessComplete);`
- L46 _public prototype_ `const FProcessComplete& GetOnProcessComplete() const;`
- L48 _public prototype_ `void SetStartFrame(int32 InStartFrame);`
- L49 _public prototype_ `int32 GetStartFrame() const;`
- L51 _public prototype_ `void SetEndFrame(int32 InEndFrame);`
- L52 _public prototype_ `int32 GetEndFrame() const;`
- L54 _public prototype_ `void SetRestrictStartingToGameThread(bool bInRestrictStartingToGameThread);`
- L55 _public prototype_ `bool GetRestrictStartingToGameThread() const;`
- L57 _public prototype_ `void SetProcessNodesInRandomOrder(bool bInProcessNodesInRandomOrder);`
- L58 _public prototype_ `bool GetProcessNodesInRandomOrder() const;`
- L60 _public prototype_ `void SetCheckThreadLimit(bool bInCheckThreadLimit);`
- L61 _public prototype_ `bool GetCheckThreadLimit() const;`
- L63 _public prototype_ `void SetCheckProcessingSpeed(bool bInCheckProcessingSpeed);`
- L64 _public prototype_ `bool GetCheckProcessingSpeed() const;`
- L66 _public prototype_ `void SetVerbosity(ELogVerbosity::Type InVerbosity);`
- L67 _public prototype_ `ELogVerbosity::Type GetVerbosity() const;`
- L69 _public prototype_ `void SetGpuToUse(const FString& InUseGPU);`
- L70 _public prototype_ `void UnsetGpuToUse();`
- L71 _public prototype_ `TOptional<FString> GetGpuToUse() const;`
- L75 _private member_ `EPipelineMode Mode = EPipelineMode::PushAsync;`
- L77 _private member_ `FFrameComplete OnFrameComplete;`
- L78 _private member_ `FProcessComplete OnProcessComplete;`
- L80 _private member_ `int32 StartFrame = 0;`
- L81 _private member_ `int32 EndFrame = -1;`
- L83 _private member_ `bool bRestrictStartingToGameThread = true;`
- L84 _private member_ `bool bProcessNodesInRandomOrder = true;`
- L85 _private member_ `bool bCheckThreadLimit = true;`
- L86 _private member_ `bool bCheckProcessingSpeed = true;`
- L88 _private member_ `ELogVerbosity::Type Verbosity = ELogVerbosity::Display;`
- L90 _private member_ `TOptional<FString> UseGPU;`

#### class `UE::MetaHuman::Pipeline::FPipeline`  
`class FPipeline`  
_L95-140_
- L99 _public prototype_ `FPipeline();`
- L100 _public prototype_ `~FPipeline();`
- L103 _public prototype_ `FPipeline(const FPipeline& InOther) = delete;` — Make class non-copyable - copying is not supported due to how the Process member is protected from garbage collection
- L104 _public prototype_ `FPipeline(FPipeline&& InOther) = delete;`
- L105 _public prototype_ `FPipeline& operator=(const FPipeline& InOther) = delete;`
- L107 _public prototype_ `void Reset();`
- L110 _public function_ `template<typename T, typename... InArgTypes> TSharedPtr<T> MakeNode(InArgTypes&&... InArgs)`
- L117 _public prototype_ `void AddNode(const TSharedPtr<FNode>& InNode);`
- L119 _public prototype_ `void MakeConnection(const TSharedPtr<FNode>& InFrom, const TSharedPtr<FNode>& InTo, int32 InFromGroup = 0, int32 InToGroup = 0);`
- L121 _public prototype_ `void Run(EPipelineMode InPipelineMode, const FFrameComplete& InOnFrameComplete, const FProcessComplete& InOnProcessComplete);`
- L122 _public prototype_ `void Run(const FPipelineRunParameters& InPipelineRunParameters);`
- L123 _public prototype_ `bool IsRunning() const;`
- L124 _public prototype_ `void Cancel();`
- L125 _public prototype_ `int32 GetNodeCount() const;`
- L127 _public prototype_ `FString ToString() const;`
- L129 _public prototype_ `static bool GetPhysicalDeviceLUIDs(FString& OutUEPhysicalDeviceLUID, TArray<FString>& OutAllPhysicalDeviceLUIDs);`
- L130 _public prototype_ `static FString PickPhysicalDevice();`
- L134 _private member_ `TArray<TSharedPtr<FNode>> Nodes;`
- L135 _private member_ `TArray<FConnection> Connections;`
- L137 _private member_ `TWeakObjectPtr<UMetaHumanPipelineProcess> Process = nullptr;`
- L139 _private prototype_ `void StopProcess(bool bInClearMessageQueue = false);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANPIPELINECORE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MetaHuman` (scope `UE`)
- L13 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)
- L16 _externvar_ `extern TAutoConsoleVariable<bool> CVarBalancedGPUSelection;` (scope `UE::MetaHuman::Pipeline`)
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FFrameComplete, TSharedPtr<FPipelineData> InPipelineData);`
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FFrameComplete, TSharedPtr<FPipelineData> InPipelineData);` (scope `UE::MetaHuman::Pipeline`)
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FProcessComplete, TSharedPtr<FPipelineData> InPipelineData);`
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FProcessComplete, TSharedPtr<FPipelineData> InPipelineData);` (scope `UE::MetaHuman::Pipeline`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanPipelineCore/Public/Pipeline/PipelineData.h` (Public)


#### class `UE::MetaHuman::Pipeline::FPipelineData`  
`class FPipelineData : public FDataTree`  
_L13-56_
- inherits: `FDataTree`
- L17 _public prototype_ `FPipelineData();`
- L19 _public prototype_ `void SetFrameNumber(int32 InFrameNumber);`
- L20 _public prototype_ `int32 GetFrameNumber() const;`
- L22 _public prototype_ `void SetExitStatus(EPipelineExitStatus InExitStatus);`
- L23 _public prototype_ `EPipelineExitStatus GetExitStatus() const;`
- L25 _public prototype_ `void SetErrorMessage(const FString& InErrorMessage);`
- L26 _public prototype_ `const FString& GetErrorMessage() const;`
- L28 _public prototype_ `void SetErrorNodeName(const FString& InErrorNodeName);`
- L29 _public prototype_ `const FString& GetErrorNodeName() const;`
- L31 _public prototype_ `void SetErrorNodeCode(int32 InErrorNodeCode);`
- L32 _public prototype_ `int32 GetErrorNodeCode() const;`
- L34 _public prototype_ `void SetErrorNodeMessage(const FString& InErrorNodeMessage);`
- L35 _public prototype_ `const FString& GetErrorNodeMessage() const;`
- L37 _public prototype_ `void SetEndFrameMarker(bool bInEndFrameMarker);`
- L38 _public prototype_ `bool GetEndFrameMarker() const;`
- L40 _public prototype_ `void SetDropFrame(bool bInDropFrame);`
- L41 _public prototype_ `bool GetDropFrame() const;`
- L43 _public prototype_ `void SetMarkerStartTime(const FString& InMarkerName);`
- L44 _public prototype_ `double GetMarkerStartTime(const FString& InMarkerName) const;`
- L46 _public prototype_ `void SetMarkerEndTime(const FString& InMarkerName);`
- L47 _public prototype_ `double GetMarkerEndTime(const FString& InMarkerName) const;`
- L49 _public prototype_ `void SetUseGPU(const FString& InUseGPU);`
- L50 _public prototype_ `FString GetUseGPU() const;`
- L54 _private prototype_ `void SetMarkerTime(const FString& InMarkerName);`
- L55 _private prototype_ `double GetMarkerTime(const FString& InMarkerName) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANPIPELINECORE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MetaHuman` (scope `UE`)
- L10 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)
