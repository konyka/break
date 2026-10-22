# Plugins / MetaHumanPipeline

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline`
- headers: 19; symbols: 573
- symbol kinds: class=51, enum=15, enumerator=60, function=16, macro=11, member=215, namespace=50, prototype=152, struct=3
- PrivateDependencyModuleNames: AudioPlatformConfiguration, CaptureDataCore, CoreUObject, Engine, GeometryCore, Json, MetaHumanCaptureData, MetaHumanConfig, MetaHumanFaceAnimationSolver, MetaHumanPlatform, ModelingOperators, NNE, Projects, RenderCore, UnrealEd
- PublicDependencyModuleNames: Core, Eigen, MeshTrackerInterface, MetaHumanCore, MetaHumanCoreTech, MetaHumanCoreTechLib, MetaHumanPipelineCore, MetaHumanSpeech2Face

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Private/MetaHumanPipelineModule.h` (Private)


#### class `FMetaHumanPipelineModule`  
`class FMetaHumanPipelineModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Private/Nodes/TestNodes.h` (Private)


#### class `UE::MetaHuman::Pipeline::FIntSrcNode`  
`class FIntSrcNode : public FNode`  
_L11-21_
- inherits: `FNode`
- L15 _public prototype_ `FIntSrcNode(const FString& InName);`
- L17 _public member_ `int32 Value = 1;`
- L18 _public member_ `int32 NumberOfFrames = 1;`
- L20 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FIntIncNode`  
`class FIntIncNode : public FNode`  
_L23-30_
- inherits: `FNode`
- L27 _public prototype_ `FIntIncNode(const FString& InName);`
- L29 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FIntDecNode`  
`class FIntDecNode : public FNode`  
_L32-39_
- inherits: `FNode`
- L36 _public prototype_ `FIntDecNode(const FString& InName);`
- L38 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FIntSumNode`  
`class FIntSumNode : public FNode`  
_L41-48_
- inherits: `FNode`
- L45 _public prototype_ `FIntSumNode(const FString& InName);`
- L47 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FIntLogNode`  
`class FIntLogNode : public FNode`  
_L50-57_
- inherits: `FNode`
- L54 _public prototype_ `FIntLogNode(const FString& InName);`
- L56 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FFltSrcNode`  
`class FFltSrcNode : public FNode`  
_L61-71_
- inherits: `FNode`
- L65 _public prototype_ `FFltSrcNode(const FString& InName);`
- L67 _public member_ `float Value = 1.0f;`
- L68 _public member_ `int32 NumberOfFrames = 1;`
- L70 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FFltIncNode`  
`class FFltIncNode : public FNode`  
_L73-80_
- inherits: `FNode`
- L77 _public prototype_ `FFltIncNode(const FString& InName);`
- L79 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FFltDecNode`  
`class FFltDecNode : public FNode`  
_L82-89_
- inherits: `FNode`
- L86 _public prototype_ `FFltDecNode(const FString& InName);`
- L88 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FFltSumNode`  
`class FFltSumNode : public FNode`  
_L91-98_
- inherits: `FNode`
- L95 _public prototype_ `FFltSumNode(const FString& InName);`
- L97 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FFltLogNode`  
`class FFltLogNode : public FNode`  
_L100-107_
- inherits: `FNode`
- L104 _public prototype_ `FFltLogNode(const FString& InName);`
- L106 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FMixSrcNode`  
`class FMixSrcNode : public FNode`  
_L111-122_
- inherits: `FNode`
- L115 _public prototype_ `FMixSrcNode(const FString& InName);`
- L117 _public member_ `int32 IntValue = 1;`
- L118 _public member_ `float FltValue = 1.0f;`
- L119 _public member_ `int32 NumberOfFrames = 1;`
- L121 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FMixIncNode`  
`class FMixIncNode : public FNode`  
_L124-131_
- inherits: `FNode`
- L128 _public prototype_ `FMixIncNode(const FString& InName);`
- L130 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FMixDecNode`  
`class FMixDecNode: public FNode`  
_L133-140_
- inherits: `FNode`
- L137 _public prototype_ `FMixDecNode(const FString& InName);`
- L139 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FMixSumNode`  
`class FMixSumNode : public FNode`  
_L142-149_
- inherits: `FNode`
- L146 _public prototype_ `FMixSumNode(const FString& InName);`
- L148 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FMixLogNode`  
`class FMixLogNode : public FNode`  
_L151-158_
- inherits: `FNode`
- L155 _public prototype_ `FMixLogNode(const FString& InName);`
- L157 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FErrorNode`  
`class FErrorNode : public FIntIncNode`  
_L162-175_
- inherits: `FIntIncNode`
- L166 _public prototype_ `FErrorNode(const FString& InName);`
- L168 _public member_ `int32 ErrorOnStage = 1;`
- L169 _public member_ `int32 ErrorOnFrame = 1;`
- L170 _public member_ `int32 ErrorCode = 1;`
- L172 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L173 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L174 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FIntsToFltNode`  
`class FIntsToFltNode : public FNode`  
_L179-186_
- inherits: `FNode`
- L183 _public prototype_ `FIntsToFltNode(const FString& InName);`
- L185 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FProcessCountNode`  
`class FProcessCountNode : public FIntIncNode`  
_L190-199_
- inherits: `FIntIncNode`
- L194 _public prototype_ `FProcessCountNode(const FString& InName);`
- L196 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L198 _public member_ `int32 ProcessCount = 0;`

#### class `UE::MetaHuman::Pipeline::FBufferNode`  
`class FBufferNode : public FNode`  
_L203-220_
- inherits: `FNode`
- L207 _public prototype_ `FBufferNode(const FString& InName);`
- L209 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L210 _public prototype_ `virtual bool Idle(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L212 _public function_ `virtual bool RequiresIdle() const override`
- L213 _public function_ `virtual bool ProcessesExitFrame() const override`
- L215 _public member_ `TArray<TSharedPtr<FPipelineData>> BufferedData;`
- L217 _public member_ `double LastAdd = 0;`
- L218 _public member_ `double Delay = 0.1;`
- L219 _public member_ `int32 Capacity = 3;`

#### class `UE::MetaHuman::Pipeline::FSlowIntIncNode`  
`class FSlowIntIncNode : public FIntIncNode`  
_L224-231_
- inherits: `FIntIncNode`
- L228 _public prototype_ `FSlowIntIncNode(const FString& InName);`
- L230 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FAnimSrcNode`  
`class FAnimSrcNode : public FNode`  
_L235-246_
- inherits: `FNode`
- L239 _public prototype_ `FAnimSrcNode(const FString& InName);`
- L241 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L243 _public member_ `int32 NumberOfFrames = 1;`
- L244 _public member_ `TMap<FString, float> AnimationData;`
- L245 _public member_ `TArray<TMap<FString, float>> AnimationDataPerFrame;`

#### class `UE::MetaHuman::Pipeline::FDepthSrcNode`  
`class FDepthSrcNode : public FNode`  
_L250-259_
- inherits: `FNode`
- L254 _public prototype_ `FDepthSrcNode(const FString& InName);`
- L256 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L258 _public member_ `FDepthDataType DepthData;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MetaHuman` (scope `UE`)
- L8 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/DoesNNEAssetExist.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `bool DoesNNEAssetExist(const FString& InAssetPath);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/Nodes/AnimationUtilNodes.h` (Public)


#### class `UE::MetaHuman::Pipeline::FAnimationMergeNode`  
`class FAnimationMergeNode : public FNode`  
_L19-34_
- inherits: `FNode`
- L23 _public prototype_ `FAnimationMergeNode(const FString& InName);`
- L25 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L27 _public member_ `FString Animation0Name = "an` — User friendly name of animation inputs used for logging
- L28 _public member_ `FString Animation1Name = "an`

#### enum `UE::MetaHuman::Pipeline::FAnimationMergeNode::ErrorCode`  
`enum ErrorCode`  
_L30-33_
- L32 _public enumerator_ `UnknownControlValue = 0`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANPIPELINE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MetaHuman` (scope `UE`)
- L10 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/Nodes/AsyncNode.h` (Public)


#### class `UE::MetaHuman::Pipeline::FAsyncNode`  
`template<typename NodeType> class FAsyncNode : public FNode`  
_L15-235_
- inherits: `FNode`
- L21 _public function_ `template<typename... InArgTypes> FAsyncNode(int32 NumberOfNodes, InArgTypes&&... InArgs) : FNode("", "")`
- L38 _public function_ `bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override`
- L81 _public function_ `bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override`
- L137 _public function_ `bool Idle(const TSharedPtr<FPipelineData>& InPipelineData) override`
- L160 _public function_ `bool End(const TSharedPtr<FPipelineData>& InPipelineData) override`
- L207 _public function_ `bool RequiresIdle() const override`
- L212 _public function_ `bool ProcessesExitFrame() const override`
- L217 _public function_ `const TArray<TSharedPtr<NodeType>>& GetNodes() const`
- L232 _private member_ `TArray<TSharedPtr<NodeType>> AllNodes;`
- L233 _private member_ `TArray<TSharedPtr<NodeType>> AvailableNodes;`
- L234 _private member_ `TArray<TFuture<FProcessData>> Futures;`

#### class `UE::MetaHuman::Pipeline::FAsyncNode::FProcessData`  
`class FProcessData`  
_L224-230_
- L227 _public member_ `TSharedPtr<FPipelineData> PipelineData;`
- L228 _public member_ `TSharedPtr<NodeType> Node;`
- L229 _public member_ `bool bProcessOk = false;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MetaHuman` (scope `UE`)
- L11 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)
- L47 _function_ `` (scope `UE::MetaHuman::Pipeline::FAsyncNode::Start`)
- L116 _function_ `` (scope `UE::MetaHuman::Pipeline::FAsyncNode::Process`)
- L173 _function_ `` (scope `UE::MetaHuman::Pipeline::FAsyncNode::End`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/Nodes/ControlUtilNodes.h` (Public)


#### class `UE::MetaHuman::Pipeline::FDropFrameNode`  
`class FDropFrameNode : public FNode`  
_L15-25_
- inherits: `FNode`
- L19 _public prototype_ `FDropFrameNode(const FString& InName);`
- L21 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L23 _public member_ `int32 DropEvery = -1;`
- L24 _public member_ `TArray<FFrameRange> ExcludedFrames;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANPIPELINE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MetaHuman` (scope `UE`)
- L12 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/Nodes/DepthMapDiagnosticsNode.h` (Public)


#### class `UE::MetaHuman::Pipeline::FDepthMapDiagnosticsNode`  
`class FDepthMapDiagnosticsNode : public FNode`  
_L27-49_
- inherits: `FNode`
- L31 _public member_ `TArray<FCameraCalibration> Calibrations;`
- L32 _public member_ `FString Camera;`
- L40 _public prototype_ `FDepthMapDiagnosticsNode(const FString& InName);`
- L42 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L43 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L44 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L48 _private member_ `TSharedPtr<IDepthMapDiagnosticsInterface> Diagnostics = nullptr;`

#### enum `UE::MetaHuman::Pipeline::FDepthMapDiagnosticsNode::ErrorCode`  
`enum ErrorCode`  
_L34-38_
- L36 _public enumerator_ `FailedToInitialize = 0`
- L37 _public enumerator_ `FailedToFindCalibration`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANPIPELINE_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Wrappers` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MetaHuman` (scope `UE`)
- L22 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/Nodes/FaceTrackerNode.h` (Public)


#### class `UE::MetaHuman::Pipeline::FFaceTrackerNodeBase`  
`class FFaceTrackerNodeBase`  
_L24-63_
- L28 _public member_ `FString SolverTemplateData;`
- L29 _public member_ `FString SolverConfigData;`
- L30 _public member_ `FString SolverPCAFromDNAData;`
- L31 _public member_ `TArray<uint8> PredictiveSolverGlobalTeethTrainingData;`
- L32 _public member_ `TArray<uint8> PredictiveSolverTrainingData;`
- L33 _public member_ `FString DNAFile;`
- L34 _public member_ `TArray<uint8> BrowJSONData;`
- L35 _public member_ `TArray<uint8> PCARigMemoryBuffer;`
- L37 _public member_ `TWeakObjectPtr<UDNAAsset> DNAAsset;` — `UE_DEPRECATED(5.8, "Use DNAReader instead, DNAAsset has been deprecated.")`
- L38 _public member_ `TSharedPtr<IDNAReader> DNAReader;`
- L39 _public member_ `TArray<FCameraCalibration> Calibrations;`
- L40 _public member_ `FString Camera;`
- L41 _public member_ `TArray<uint8> PredictiveWithoutTeethSolver;` — use for the global teeth solve
- L42 _public member_ `TArray<uint8> PredictiveSolvers;`
- L43 _public member_ `bool bIsFirstPass = true;`
- L44 _public member_ `bool bTrackingFailureIsError = true;`
- L45 _public member_ `bool bSkipPredictiveSolver = false;`
- L46 _public member_ `bool bSkipPerVertexSolve = true;`
- L47 _public member_ `FString DebuggingFolder;`
- L62 _protected member_ `TSharedPtr<IMetaHumanFaceTrackerInterface> Tracker = nullptr;`

#### enum `UE::MetaHuman::Pipeline::FFaceTrackerNodeBase::ErrorCode`  
`enum ErrorCode`  
_L50-58_
- L52 _public enumerator_ `FailedToInitialize = 0`
- L53 _public enumerator_ `FailedToTrack`
- L54 _public enumerator_ `UntrainedSolvers`
- L55 _public enumerator_ `FailedToCalculatePCA`
- L56 _public enumerator_ `NoContourData`
- L57 _public enumerator_ `FailedToFindCalibration`

#### class `UE::MetaHuman::Pipeline::FFaceTrackerStereoNode`  
`class FFaceTrackerStereoNode : public FNode, public FFaceTrackerNodeBase`  
_L65-74_
- inherits: `FNode,FFaceTrackerNodeBase`
- L69 _public prototype_ `FFaceTrackerStereoNode(const FString& InName);`
- L71 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L72 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L73 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`

#### class `UE::MetaHuman::Pipeline::FFaceTrackerIPhoneNode`  
`class FFaceTrackerIPhoneNode : public FNode, public FFaceTrackerNodeBase`  
_L76-92_
- inherits: `FNode,FFaceTrackerNodeBase`
- L80 _public prototype_ `FFaceTrackerIPhoneNode(const FString& InName);`
- L82 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L83 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L84 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L86 _public member_ `int32 NumberOfFrames = 0;`
- L87 _public member_ `bool bSkipDiagnostics = false;`
- L91 _protected member_ `int32 FrameNumber = 0;`

#### class `UE::MetaHuman::Pipeline::FFaceTrackerIPhoneManagedNode`  
`class FFaceTrackerIPhoneManagedNode : public FFaceTrackerIPhoneNode`  
_L97-102_
- inherits: `FFaceTrackerIPhoneNode`
- L101 _public prototype_ `FFaceTrackerIPhoneManagedNode(const FString& InName);`

#### class `UE::MetaHuman::Pipeline::FDepthGenerateNode`  
`class FDepthGenerateNode : public FNode`  
_L106-131_
- inherits: `FNode`
- L110 _public prototype_ `FDepthGenerateNode(const FString& InName);`
- L112 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L113 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L114 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L116 _public prototype_ `static FCalibrationDataType ConvertCameraCalibration(const FCameraCalibration& InCameraCalibration);`
- L117 _public prototype_ `static FCameraCalibration ConvertCalibrationDataType(const FCalibrationDataType& InCalibrationDataType);`
- L119 _public member_ `TArray<FCameraCalibration> Calibrations;`
- L120 _public member_ `TRange<float> DistanceRange;`
- L130 _protected member_ `TSharedPtr<IDepthGeneratorInterface> Reconstructer = nullptr;`

#### enum `UE::MetaHuman::Pipeline::FDepthGenerateNode::ErrorCode`  
`enum ErrorCode`  
_L122-126_
- L124 _public enumerator_ `FailedToInitialize = 0`
- L125 _public enumerator_ `FailedToGenerateDepth`

#### class `UE::MetaHuman::Pipeline::FFlowNode`  
`class FFlowNode : public FNode`  
_L135-162_
- inherits: `FNode`
- L139 _public prototype_ `FFlowNode(const FString& InName);`
- L141 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L142 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L143 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L145 _public member_ `FString SolverConfigData;`
- L147 _public member_ `bool bUseConfidence = false;`
- L148 _public member_ `TArray<FCameraCalibration> Calibrations;`
- L149 _public member_ `FString Camera;`
- L150 _public member_ `bool bEnableFlow = true;`
- L160 _private member_ `TSharedPtr<IOpticalFlowInterface> Flow = nullptr;`
- L161 _private member_ `TArray<float> PreviousImage;`

#### enum `UE::MetaHuman::Pipeline::FFlowNode::ErrorCode`  
`enum ErrorCode`  
_L152-156_
- L154 _public enumerator_ `FailedToInitialize = 0`
- L155 _public enumerator_ `FailedToGenerateFlow`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METAHUMANPIPELINE_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MetaHuman` (scope `UE`)
- L19 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/Nodes/FaceTrackerPostProcessingFilterNode.h` (Public)


#### class `UE::MetaHuman::Pipeline::FFaceTrackerPostProcessingFilterNode`  
`class FFaceTrackerPostProcessingFilterNode : public FNode`  
_L18-52_
- inherits: `FNode`
- L22 _public prototype_ `FFaceTrackerPostProcessingFilterNode(const FString& InName);`
- L24 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L25 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L26 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L28 _public member_ `FString TemplateData;`
- L29 _public member_ `FString ConfigData;`
- L30 _public member_ `FString DefinitionsData;`
- L31 _public member_ `FString HierarchicalDefinitionsData;`
- L32 _public member_ `FString HierarchicalDefinitionsPlusChinCompressData;`
- L33 _public member_ `FString DNAFile;`
- L35 _public member_ `TWeakObjectPtr<UDNAAsset> DNAAsset;` — `UE_DEPRECATED(5.8, "Use DNAReader instead, DNAAsset has been deprecated in favor of DNA Reader.")`
- L36 _public member_ `TSharedPtr<IDNAReader> DNAReader;`
- L37 _public member_ `TArray<FFrameAnimationData> FrameData;`
- L38 _public member_ `FString DebuggingFolder;`
- L39 _public member_ `EMeshSolverDefinitionsType MeshSolverDefinitionsType = EMeshSolverDefinitionsType::Standard;`
- L41 _public member_ `bool bSolveForTweakers = false;` — `UE_DEPRECATED(5.8, "bSolveForTweakers has been deprecated. Use MeshSolverDefinitionsType instead.")`
- L50 _protected member_ `TSharedPtr<IFaceTrackerPostProcessingFilter> Filter = nullptr;`
- L51 _protected member_ `int32 FrameNumber = 0;`

#### enum `UE::MetaHuman::Pipeline::FFaceTrackerPostProcessingFilterNode::ErrorCode`  
`enum ErrorCode`  
_L43-46_
- L45 _public enumerator_ `FailedToInitialize = 0`

#### class `UE::MetaHuman::Pipeline::FFaceTrackerPostProcessingFilterManagedNode`  
`class FFaceTrackerPostProcessingFilterManagedNode : public FFaceTrackerPostProcessingFilterNode`  
_L57-62_
- inherits: `FFaceTrackerPostProcessingFilterNode`
- L61 _public prototype_ `FFaceTrackerPostProcessingFilterManagedNode(const FString& InName);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METAHUMANPIPELINE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MetaHuman` (scope `UE`)
- L15 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/Nodes/FaceTrackerPostProcessingNode.h` (Public)


#### class `UE::MetaHuman::Pipeline::FFaceTrackerPostProcessingNode`  
`class FFaceTrackerPostProcessingNode : public FNode`  
_L21-63_
- inherits: `FNode`
- L25 _public prototype_ `FFaceTrackerPostProcessingNode(const FString& InName);`
- L27 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L28 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L29 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L31 _public member_ `FString TemplateData;`
- L32 _public member_ `FString ConfigData;`
- L33 _public member_ `FString DefinitionsData;`
- L34 _public member_ `FString HierarchicalDefinitionsData;`
- L35 _public member_ `FString HierarchicalDefinitionsPlusChinCompressData;`
- L36 _public member_ `FString DNAFile;`
- L38 _public member_ `TWeakObjectPtr<UDNAAsset> DNAAsset;` — `UE_DEPRECATED(5.8, "Use DNAReader instead, DNAAsset has been deprecated.")`
- L39 _public member_ `TSharedPtr<IDNAReader> DNAReader;`
- L40 _public member_ `TArray<FCameraCalibration> Calibrations;`
- L41 _public member_ `FString Camera;`
- L42 _public member_ `TArray<uint8> PredictiveWithoutTeethSolver;` — use for the global teeth solve
- L43 _public member_ `TArray<FFrameTrackingContourData> TrackingData;`
- L44 _public member_ `TArray<FFrameAnimationData> FrameData;`
- L45 _public member_ `FString DebuggingFolder;`
- L46 _public member_ `EMeshSolverDefinitionsType MeshSolverDefinitionsType = EMeshSolverDefinitionsType::Standard;`
- L48 _public member_ `bool bSolveForTweakers = false;` — `UE_DEPRECATED(5.8, "bSolveForTweakers has been deprecated. Use MeshSolverDefinitionsType instead.")`
- L49 _public member_ `bool bDisableGlobalSolves = false;`
- L60 _protected member_ `TSharedPtr<IFaceTrackerPostProcessingInterface> Tracker = nullptr;`
- L61 _protected member_ `TMap<int, FFrameAnimationData> AnimationWindow;`
- L62 _protected member_ `int32 FrameNumber = 0;`

#### enum `UE::MetaHuman::Pipeline::FFaceTrackerPostProcessingNode::ErrorCode`  
`enum ErrorCode`  
_L51-56_
- L53 _public enumerator_ `FailedToInitialize = 0`
- L54 _public enumerator_ `FailedToTrack`
- L55 _public enumerator_ `BadFrame`

#### class `UE::MetaHuman::Pipeline::FFaceTrackerPostProcessingManagedNode`  
`class FFaceTrackerPostProcessingManagedNode : public FFaceTrackerPostProcessingNode`  
_L68-73_
- inherits: `FFaceTrackerPostProcessingNode`
- L72 _public prototype_ `FFaceTrackerPostProcessingManagedNode(const FString& InName);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METAHUMANPIPELINE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MetaHuman` (scope `UE`)
- L18 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/Nodes/HyprsenseNode.h` (Public)


#### class `UE::MetaHuman::Pipeline::FHyprsenseNode`  
`class FHyprsenseNode : public FHyprsenseNodeBase`  
_L10-25_
- inherits: `FHyprsenseNodeBase`
- L13 _public prototype_ `FHyprsenseNode(const FString& InName);`
- L15 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L16 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L19 _public prototype_ `bool SetTrackers(const TSharedPtr<UE::NNE::IModelInstanceGPU>& InFaceTracker, const TSharedPtr<UE::NNE::IModelInstanceGPU>& InFaceDetector, const TSharedPtr<UE::NNE::IModelInstanceGPU>& InEyebrowTracker, const TSharedPtr<UE::NNE::IModelInstanceGPU>& InEyeTracker, const TSharedPtr<UE::NNE::IModelInstanceGPU>& InLipsTracker, const TSharedPtr<UE::NNE::IModelInstanceGPU>& InLipZipTracker, const TSharedPtr<UE::NNE::IModelInstanceGPU>& InNasolabialNoseTracker, const TSharedPtr<UE::NNE::IModelInstanceGPU>& InChinTracker, const TSharedPtr<UE::NNE::IModelInstanceGPU>& InTeethTracker, const TSharedPtr<UE::NNE::IModelInstanceGPU>& InTeethConfidenceTracker);` — `UE_DEPRECATED(5.8, "SetTrackers with GPU interface is deprecated. Use SetTrackers with RunSync interface instead.")`
- L21 _public prototype_ `bool SetTrackers(const TSharedPtr<UE::NNE::IModelInstanceRunSync>& InFaceTracker, const TSharedPtr<UE::NNE::IModelInstanceRunSync>& InFaceDetector, const TSharedPtr<UE::NNE::IModelInstanceRunSync>& InEyebrowTracker, const TSharedPtr<UE::NNE::IModelInstanceRunSync>& InEyeTracker, const TSharedPtr<UE::NNE::IModelInstanceRunSync>& InLipsTracker, const TSharedPtr<UE::NNE::IModelInstanceRunSync>& InLipZipTracker, const TSharedPtr<UE::NNE::IModelInstanceRunSync>& InNasolabialNoseTracker, const TSharedPtr<UE::NNE::IModelInstanceRunSync>& InChinTracker, const TSharedPtr<UE::NNE::IModelInstanceRunSync>& InTeethTracker, const TSharedPtr<UE::NNE::IModelInstanceRunSync>& InTeethConfidenceTracker);`
- L23 _public member_ `bool bAddSparseTrackerResultsToOutput = true;`

#### class `UE::MetaHuman::Pipeline::FHyprsenseManagedNode`  
`class FHyprsenseManagedNode : public FHyprsenseNode`  
_L31-36_
- inherits: `FHyprsenseNode`
- L34 _public prototype_ `FHyprsenseManagedNode(const FString& InName, const FString& InNNEBackend = "");`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API METAHUMANPIPELINE_API`
- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MetaHuman` (scope `UE`)
- L8 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/Nodes/HyprsenseNodeBase.h` (Public)


#### class `UE::MetaHuman::Pipeline::FHyprsenseNodeBase`  
`class FHyprsenseNodeBase : public FNode, public FHyprsenseUtils`  
_L21-297_
- inherits: `FNode,FHyprsenseUtils`
- L63 _public prototype_ `FHyprsenseNodeBase(const FString& InTypeName, const FString& InName);`
- L65 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) = 0;`
- L66 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) = 0;`
- L68 _public prototype_ `FString GetErrorMessage() const;`
- L69 _public prototype_ `ErrorCode GetErrorCode() const;`
- L94 _protected prototype_ `Matrix23f GetTransformFromLandmarkPart(int32 InImageWidth, int32 InImageHeight, int32 InCropBoxSize, const TArray<float>& InLandmarks, float InRotation, bool bFlip, PartType InPartType);`
- L95 _protected prototype_ `Matrix23f GetTransformFromLandmarkFacePart(int32 InImageWidth, int32 InImageHeight, int32 InCropBoxSize, const TArray<float>& InLandmarks, FacePart InPartName, float InRotation, bool bFlip, bool isRealtime);`
- L97 _protected prototype_ `TArray<float> SelectLandmarksToCrop(const TArray<float>& InLandmarks, const TArray<int32>& InLandmarkIndices, const TArray<int32>& LandmarkRangeIdxNormal, const TArray<int32>& InLandmarkIdxRangeExtra, const TArray<int32>& InLandmarkIdxCenter, const TArray<int32>& InLandmarkIdxCenterExtra, const TArray<int32>& InLandmarkIdxExtra);`
- L99 _protected prototype_ `void AddContourToOutput(const TArray<float>& InPoints, const TArray<float>& InConfidences, const TMap<FString, Interval>& InCurveMap, const TMap<FString, int32>& InLandmarkMap, FFrameTrackingContourData& OutResult);`
- L101 _protected prototype_ `float GetRotationToUpright(const TArray<float>& InLandmarks);`
- L103 _protected prototype_ `Bbox GetInversedBbox(Bbox& InBbox, const Matrix23f& InTransform);`
- L104 _protected prototype_ `TArray<float> GetInversedPoints(float* InLandmarks, int32 InNum, const Matrix23f& InTransform);`
- L106 _protected prototype_ `void InitTransformLandmark131to159();`
- L107 _protected prototype_ `TArray<float> GetLandmark131to159(const TArray<float>& InLandmarks131);`
- L108 _protected member_ `TArray<int32> Index131to159;`
- L110 _protected prototype_ `bool ProcessLandmarks(const FUEImageDataType& Input, bool isRealtime, TArray<PartPoints>& OutDenseTrackerPointsPerModelInversed, PartPoints& OutSparseTrackerPointsInversed, bool bInRunSparseTrackerOnly);`
- L112 _protected function_ `static inline TArray<float> EmptyConfidences(int32 Size)`
- L119 _protected prototype_ `bool CheckTrackers(const TMap<ETrackerType, UE::NNE::FTensorShape>& InputValidationMap, const TMap<ETrackerType, TArray<UE::NNE::FTensorShape>>& OutputValidationMap, const TMap<TSharedPtr<UE::NNE::IModelInstanceRunSync>, ETrackerType>& TrackerTypeMap);`
- L121 _protected member_ `int32 TrackerInputSizeX = 256;`
- L122 _protected member_ `int32 TrackerInputSizeY = 256;`
- L124 _protected member_ `TArray<int32> TrackerPartInputSizeX;`
- L125 _protected member_ `TArray<int32> TrackerPartInputSizeY;`
- L128 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> FaceTracker{};` — `UE_DEPRECATED(5.8, "FaceTracker is deprecated. Use FaceTrackerModel instead.")`
- L130 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> FaceDetector{};` — `UE_DEPRECATED(5.8, "FaceDetector is deprecated. Use FaceDetectorModel instead.")`
- L132 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> EyebrowTracker{};` — `UE_DEPRECATED(5.8, "EyebrowTracker is deprecated. Use EyebrowTrackerModel instead.")`
- L134 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> EyeTracker{};` — `UE_DEPRECATED(5.8, "EyeTracker is deprecated. Use EyeTrackerModel instead.")`
- L136 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> LipsTracker{};` — `UE_DEPRECATED(5.8, "LipsTracker is deprecated. Use LipsTrackerModel instead.")`
- L138 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> LipzipTracker{};` — `UE_DEPRECATED(5.8, "LipzipTracker is deprecated. Use LipzipTrackerModel instead.")`
- L140 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> NasolabialNoseTracker{};` — `UE_DEPRECATED(5.8, "NasolabialNoseTracker is deprecated. Use NasolabialNoseTrackerModel instead.")`
- L142 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> ChinTracker{};` — `UE_DEPRECATED(5.8, "ChinTracker is deprecated. Use ChinTrackerModel instead.")`
- L144 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> TeethTracker{};` — `UE_DEPRECATED(5.8, "TeethTracker is deprecated. Use TeethTrackerModel instead.")`
- L146 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> LipsNasoNoseTeethTracker{};` — `UE_DEPRECATED(5.8, "LipsNasoNoseTeethTracker is deprecated. Use LipsNasoNoseTeethTrackerModel instead.")`
- L148 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> TeethConfidenceTracker{};` — `UE_DEPRECATED(5.8, "TeethConfidenceTracker is deprecated. Use TeethConfidenceTrackerModel instead.")`
- L150 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> FaceTrackerModel{};`
- L151 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> FaceDetectorModel{};`
- L152 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> EyebrowTrackerModel{};`
- L153 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> EyeTrackerModel{};`
- L154 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> LipsTrackerModel{};`
- L155 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> LipzipTrackerModel{};`
- L156 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> NasolabialNoseTrackerModel{};`
- L157 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> ChinTrackerModel{};`
- L158 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> TeethTrackerModel{};`
- L159 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> LipsNasoNoseTeethTrackerModel{};`
- L160 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> TeethConfidenceTrackerModel{};`
- L162 _protected member_ `TArray<TArray<float>> FaceTrackerOutputData;`
- L163 _protected member_ `TArray<TArray<float>> FaceDetectorOutputData;`
- L164 _protected member_ `TArray<TArray<float>> EyebrowTrackerOutputData;`
- L165 _protected member_ `TArray<TArray<float>> EyeTrackerOutputData;`
- L166 _protected member_ `TArray<TArray<float>> LipsTrackerOutputData;`
- L167 _protected member_ `TArray<TArray<float>> LipzipTrackerOutputData;`
- L168 _protected member_ `TArray<TArray<float>> NasolabialNoseTrackerOutputData;`
- L169 _protected member_ `TArray<TArray<float>> ChinTrackerOutputData;`
- L170 _protected member_ `TArray<TArray<float>> TeethTrackerOutputData;`
- L171 _protected member_ `TArray<TArray<float>> LipsNasoNoseTeethTrackerOutputData;`
- L172 _protected member_ `TArray<TArray<float>> TeethConfidenceTrackerOutputData;`
- L174 _protected member_ `FString NNEBackend;`
- L175 _protected prototype_ `FString GetNNEBackend(void) const;`
- L177 _protected member_ `FString ErrorMessage{ "Not`
- L178 _protected member_ `ErrorCode EErrorCode{};`
- L180 _protected member_ `bool bIsInitialized{};`
- L181 _protected member_ `bool bIsFaceDetected{};`
- L184 _protected member_ `TArray<TSharedPtr<UE::NNE::IModelInstanceGPU>> NNEModels = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };` — `UE_DEPRECATED(5.8, "NNEModels is deprecated. Use NNERunSyncModels instead.")`
- L186 _protected member_ `TArray<TSharedPtr<UE::NNE::IModelInstanceRunSync>> NNERunSyncModels = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };`
- L189 _protected member_ `const bool ImageFlipPart[FacePart::Num] = { true, false, true , false, false, false, false, false, false, false, false };` — To make right part of eye/eyebrow to "left-looking" to make an input for partwise tracker.
- L192 _protected member_ `const bool CombineDataPart[FacePart::Num] = { false, true, false, true, false, false, false, false, false, false, false };` — for separating and merging left/right part
- L195 _protected member_ `const bool isScore[FacePart::Num] = { false, false, false, false, false, false, false, false, false, false, true };` — if the output of the model is the score rather than points, it doesn't need to be translated to resolution
- L197 _protected member_ `TArray<bool> ProcessPart;`
- L199 _protected member_ `const float FaceScoreThreshold = 0.5f;`
- L200 _protected member_ `const int InvalidMarker = -1;`
- L201 _protected member_ `bool bIsTrackerSetToGPU = false;`
- L202 _protected member_ `Matrix23f LastTransform;`
- L204 _protected member_ `const TMap<FString, Interval> CurveLipMap = { {FString("crv_lip_upper_outer_r"), {24,0}}, {FString("crv_lip_philtrum_r"), {31,24}}, {FString("crv_lip_philtrum_l"), {31,38}}, {FString("crv_lip_upper_outer_l"), {38,62}}, {FString("crv_lip_lower_outer_l"), {90,62}}, {FString("crv_lip_lower_outer_r"), {90,117,{0}}},`
- L210 _protected member_ `const TMap<FString, int32> LandmarkLipMap = { {FString("pt_lip_lower_inner_m"), 191}, {FString("pt_lip_lower_outer_m"), 90}, {FString("pt_lip_philtrum_r"), 24}, {FString("pt_lip_philtrum_l"), 38}, {FString("pt_lip_upper_inner_m"), 142}, {FString("pt_lip_upper_outer_m"), 31}, {FString("pt_mouth_corner_r"), 0}, { FS`
- L215 _protected member_ `const TMap<FString, Interval> CurveNasolabMap = { { FString("crv_nasolabial_r"), {0,24} }, { FString("`
- L217 _protected member_ `const TMap<FString, int32> LandmarkNasolabMap = { {FString("pt_naso_upper_r"), 0}, {FString("pt_naso_lower_r"), 24}, {FString("pt_naso_upper_l"), 25}, {FStr`
- L220 _protected member_ `const TMap<FString, Interval> CurveNoseMap = { { FString("crv_nose_r"), {24,0} }, { FString("crv_no`
- L222 _protected member_ `const TMap<FString, int32> LandmarkNoseMap = { {FString("pt_nose_r"), 0}, {FString("pt_nose_m"), 24}, {F`
- L224 _protected member_ `const TMap<FString, Interval> CurveChinMap = { { FString("crv_chin_r"), {24,0} }, { FString("crv_ch`
- L226 _protected member_ `const TMap<FString, int32> LandmarkChinMap = { {FString("pt_chin_r"), 0}, {FString("pt_chin_m"), 24}, {F`
- L228 _protected member_ `const TMap<FString, Interval> CurveLipzipMap = { };`
- L230 _protected member_ `const TMap<FString, int32> LandmarkLipzipMap = { {FString("pt_right_contact"), 0}, {FS`
- L232 _protected member_ `const TMap<FString, Interval> CurveTeethMap = { };`
- L234 _protected member_ `const TMap<FString, int32> LandmarkTeethMap = { {FString("pt_tooth_upper"), 0}, {FString("pt_tooth_lower"), 1}, {FString("pt_tooth_upper_2"), 2}, {FS`
- L237 _protected member_ `const TMap<FString, Interval> CurveEyeIrisMap = { {FString("crv_eyelid_upper_r"), {19,0}}, {FString("crv_eyelid_lower_r"), {19,37, {0} }}, {FString("crv_iris_r"), {63,38}}, {FString("crv_eyelid_upper_l"), {83,64}}, {FString("crv_eyelid_lower_l"), { 83, 101, {64} }}, { FString(`
- L241 _protected member_ `const TMap<FString, int32> LandmarkEyeIrisMap = { {FString("pt_eye_corner_inner_r"), 19}, {FString("pt_eye_corner_inner_l"), 83}, {FString("pt_eye_corner_outer_r"), 0}, {FString("pt_eye_corner_outer_l"), 64}, {FString("pt_iris_top_r"), 38}, { FString`
- L245 _protected member_ `const TMap<FString, Interval> CurveBrowMap = { {FString("crv_brow_upper_r"), {24,0}}, {FString("crv_brow_lower_r"), {29,47,{0}}}, {FString("crv_brow_intermediate_r"), {24,29}}, {FString("crv_brow_intermediate_l"), {72,77}}, {FString("crv_brow_upper_l"), {72,48}}, {FString("crv_`
- L249 _protected member_ `const TMap<FString, int32> LandmarkBrowMap = { {FString("pt_brow_inner_r"), 24}, {FString("pt_brow_inner_l"), 72}, {FString("pt_brow_intermediate_r"), 29}, {FString("pt_brow_intermediate_l"), 77}, {FString("pt_brow_outer_r"), 0}, {FStr`
- L253 _protected member_ `const TMap<FString, Interval> CurveSparseTrackerMap = { { FString("crv_sparse_chin_r"), {8,0} }, { FString("crv_sparse_chin_l"), {8, 16} }, { FString("crv_sparse_brow_upper_r"), {25,17} }, { FString("crv_sparse_brow_lower_r"), {26,33, {17}} }, { FString("crv_sparse_brow_intermediate_r"), {25, 26} }, { FString("crv_sparse_brow_upper_l"), {42,34} }, { FString("crv_sparse_brow_lower_l"), {43,50, {34}} }, { FString("crv_sparse_brow_intermediate_l"), {42, 43} }, { FString("crv_sparse_lip_upper_outer_r"), {100, 94} }, { FString("crv_sparse_lip_upper_outer_l"), {100, 106} }, { FString("crv_sparse_lip_upper_inner_r"), {121, 118, {94}} }, { FString("crv_sparse_lip_upper_inner_l"), {121, 124, {106}} }, { FString("crv_sparse_lip_lower_outer_r"), {112, 117, {94}} }, { FString("crv_sparse_lip_lower_outer_l"), {112, 106} }, { FString("crv_sparse_lip_lower_inner_r"), {128, 131, {94}} }, { FString("crv_sparse_lip_lower_inner_l"), {128, 125, {106}} }, { FString("crv_sparse_nasolabial_r"), {154, 151, {59}} }, { FString("crv_sparse_nasolabial_l"), {158, 155, {65}} }, { FString("crv_sparse_nose_r"), {55, 62} }, { FString("crv_sparse_nose_l"), {69, 62} }, { FString("crv_sparse_nose_m"), {51, 54, {62}} }, { FString("crv_sparse_eyelid_upper_r"), {76,70}}, {FString("crv_sparse_eyelid_lower_r"), {76,81, {70} }}, { FString("crv_sparse_iris_r"), {133,140}}, {FString("crv_sparse_eyelid_upper_l"), {88,82}}, { FString("crv_sparse_eyelid_lower_l"), { 88, 93, {82} }}, { FString("crv_sparse_iris_l"), {142,14 ...`
- L268 _protected member_ `const TMap<FString, int32> LandmarkSparseTrackerMap = { {FString("pt_sparse_chin_r"), 0 }, {FString("pt_sparse_chin_m"), 8 }, {FString("pt_sparse_chin_l"), 16 }, { FString("pt_sparse_brow_inner_r"), 25 }, { FString("pt_sparse_brow_inner_l"), 42 }, { FString("pt_sparse_brow_intermediate_r"), 26 }, {FString("pt_sparse_brow_intermediate_l"), 43 }, { FString("pt_sparse_brow_outer_r"), 17 }, { FString("pt_sparse_brow_outer_l"), 34 }, { FString("pt_sparse_eye_corner_inner_r"), 76 }, { FString("pt_sparse_eye_corner_inner_l"), 88 }, { FString("pt_sparse_eye_corner_outer_r"), 70 }, { FString("pt_sparse_eye_corner_outer_l"), 82 }, { FString("pt_sparse_pupil_r"), 141}, { FString("pt_sparse_pupil_l"), 150 }, { FString("pt_sparse_nose_upper_m"), 51 }, { FString("pt_sparse_nose_lower_m"), 62 }, { FString("pt_sparse_naso_upper_r"), 59 }, { FString("pt_sparse_naso_lower_r"), 154 }, { FString("pt_sparse_naso_upper_l"), 65 }, { FString("pt_sparse_naso_lower_l"), 158 }, { FString("pt_sparse_lip_lower_inner_m"), 128 }, { FString("pt_sparse_lip_lower_outer_m"), 112 }, { FString("pt_sparse_lip_upper_inner_m"), 121 }, { FString("pt_sparse_lip_upper_outer_m"), 100 }, { FString("pt_sparse_mouth_corner_r"), 94 }, { FString("pt_sparse_mouth_corner_l"), 106 }, { FString("pt_sparse_mouth_tongue_m"), 132 } };`
- L284 _protected member_ `const TMap <ETrackerType, FString> TrackerNames = { { ETrackerType::FaceTracker, TEXT("FaceTracker") }, { ETrackerType::FaceDetector, TEXT("FaceDetector") }, { ETrackerType::EyebrowTracker, TEXT("EyebrowTracker") }, { ETrackerType::EyeTracker, TEXT("EyeTracker") }, { ETrackerType::LipsTracker, TEXT("LipsTracker") }, { ETrackerType::LipzipTracker, TEXT("LipzipTracker") }, { ETrackerType::NasoLabialTracker, TEXT("NasoLabialTracker") }, { ETrackerType::ChinTracker, TEXT("ChinTracker") }, { ETrackerType::TeethTracker, TEXT("TeethTracker") }, { ETrackerType::LipsNasoNoseTeethTracker, TEXT("LipsNasoNoseTeethTracker") }, { ETrackerType::TeethConfidenceTracker, TEXT("FaceTeethConfidenceTracker") }, };`

#### enum `UE::MetaHuman::Pipeline::FHyprsenseNodeBase::ErrorCode`  
`enum ErrorCode`  
_L24-30_
- L26 _public enumerator_ `InvalidTracker = 0`
- L27 _public enumerator_ `ModelNotLoaded`
- L28 _public enumerator_ `InvalidIOConfig`
- L29 _public enumerator_ `FailedToTrack`

#### enum `UE::MetaHuman::Pipeline::FHyprsenseNodeBase::ETrackerType`  
`enum class ETrackerType : uint8`  
_L32-45_
- L34 _public enumerator_ `FaceTracker = 0`
- L35 _public enumerator_ `FaceDetector`
- L36 _public enumerator_ `EyebrowTracker`
- L37 _public enumerator_ `EyeTracker`
- L38 _public enumerator_ `LipsTracker`
- L39 _public enumerator_ `LipzipTracker`
- L40 _public enumerator_ `NasoLabialTracker`
- L41 _public enumerator_ `ChinTracker`
- L42 _public enumerator_ `TeethTracker`
- L43 _public enumerator_ `LipsNasoNoseTeethTracker`
- L44 _public enumerator_ `TeethConfidenceTracker`

#### struct `UE::MetaHuman::Pipeline::FHyprsenseNodeBase::Interval`  
`struct Interval`  
_L47-55_
- L50 _public member_ `int32 Start{};` — Defines continuous interval of indices [Start,End]
- L51 _public member_ `int32 End{};`
- L54 _public member_ `TArray<int32> AdditionalIndices{};` — Any additional indices added to continuous interval above

#### struct `UE::MetaHuman::Pipeline::FHyprsenseNodeBase::NNEModelInfo`  
`struct NNEModelInfo`  
_L57-61_
- L59 _public member_ `TArray<int32> Inputs{};`
- L60 _public member_ `TArray<int32> Outputs{};`

#### enum `UE::MetaHuman::Pipeline::FHyprsenseNodeBase::FacePart`  
`enum FacePart`  
_L73-87_
- L75 _public enumerator_ `RightEyeBrow`
- L76 _public enumerator_ `LeftEyeBrow`
- L77 _public enumerator_ `RightEye`
- L78 _public enumerator_ `LeftEye`
- L79 _public enumerator_ `Lips`
- L80 _public enumerator_ `Lipzip`
- L81 _public enumerator_ `NasolabialNose`
- L82 _public enumerator_ `Chin`
- L83 _public enumerator_ `Teeth`
- L84 _public enumerator_ `LipsNasoNoseTeeth`
- L85 _public enumerator_ `TeethConfidence`
- L86 _public enumerator_ `Num = 11`

#### struct `UE::MetaHuman::Pipeline::FHyprsenseNodeBase::PartPoints`  
`struct PartPoints`  
_L89-92_
- L91 _public member_ `TArray<float> Points;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API METAHUMANPIPELINE_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MetaHuman` (scope `UE`)
- L19 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/Nodes/HyprsenseSparseNode.h` (Public)


#### class `UE::MetaHuman::Pipeline::FHyprsenseSparseNode`  
`class FHyprsenseSparseNode : public FHyprsenseNodeBase`  
_L10-22_
- inherits: `FHyprsenseNodeBase`
- L13 _public prototype_ `FHyprsenseSparseNode(const FString& InName);`
- L15 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L16 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L19 _public prototype_ `bool SetTrackers(const TSharedPtr<UE::NNE::IModelInstanceGPU>& InFaceTracker, const TSharedPtr<UE::NNE::IModelInstanceGPU>& InFaceDetector);` — `UE_DEPRECATED(5.8, "SetTrackers with GPU interface is deprecated. Use SetTrackers with RunSync interface instead.")`
- L21 _public prototype_ `bool SetTrackers(const TSharedPtr<UE::NNE::IModelInstanceRunSync>& InFaceTracker, const TSharedPtr<UE::NNE::IModelInstanceRunSync>& InFaceDetector);`

#### class `UE::MetaHuman::Pipeline::FHyprsenseSparseManagedNode`  
`class FHyprsenseSparseManagedNode : public FHyprsenseSparseNode`  
_L28-33_
- inherits: `FHyprsenseSparseNode`
- L31 _public prototype_ `FHyprsenseSparseManagedNode(const FString& InName, const FString& InNNEBackend = "");`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API METAHUMANPIPELINE_API`
- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MetaHuman` (scope `UE`)
- L8 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/Nodes/HyprsenseTestNode.h` (Public)


#### class `UE::MetaHuman::Pipeline::FHyprsenseTestNode`  
`class FHyprsenseTestNode : public FNode`  
_L23-43_
- inherits: `FNode`
- L27 _public prototype_ `FHyprsenseTestNode(const FString& InName);`
- L28 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L29 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L30 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L32 _public member_ `FString InJsonFilePath;`
- L33 _public member_ `FString OutJsonFilePath;`
- L35 _public member_ `TArray<FFrameTrackingContourData> ContourByFrame;`
- L36 _public member_ `TArray<TMap<FString, float>> ContourDiffAverageByFrame;`
- L37 _public member_ `TArray<float> TotalLandmarkDiffAverageByFrame;`
- L39 _public member_ `int32 FrameCount = 0;`
- L40 _public member_ `float MaxAverageDifference = 0;`
- L41 _public member_ `float TotalAverageInAllFrames = 0;`
- L42 _public member_ `bool bAllowExtraCurvesInTrackingData = false;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API METAHUMANPIPELINE_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MetaHuman` (scope `UE`)
- L20 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/Nodes/MeshSolverDefinitionsType.h` (Public)


#### enum `EMeshSolverDefinitionsType`  
`enum EMeshSolverDefinitionsType`  
_L5-10_
- L7 _public enumerator_ `Standard = 0`
- L8 _public enumerator_ `Hierarchical`
- L9 _public enumerator_ `HierarchicalPlusChinCompress`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/Nodes/MiscUtilNodes.h` (Public)


#### class `UE::MetaHuman::Pipeline::FReplaceNode`  
`template<EPinType PinEnum, typename PinData> class FReplaceNode : public FNode`  
_L12-33_
- inherits: `FNode`
- L16 _public function_ `FReplaceNode(const FString& InName) : FNode("Replace-" + InName, InName)`
- L23 _public function_ `bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MetaHuman` (scope `UE`)
- L8 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/Nodes/SpeechToAnimNode.h` (Public)


#### class `UE::MetaHuman::Pipeline::FSpeechToAnimNode`  
`class FSpeechToAnimNode : public FNode`  
_L15-70_
- inherits: `FNode`
- L19 _public prototype_ `FSpeechToAnimNode(const FString& InName);`
- L20 _public prototype_ `FSpeechToAnimNode(const FString& InTypeName, const FString& InName);`
- L23 _public prototype_ `virtual bool LoadModels();`
- L24 _public prototype_ `bool LoadModels(const FAudioDrivenAnimationModels& InModels);`
- L25 _public prototype_ `void SetMood(const EAudioDrivenAnimationMood& InMood);`
- L26 _public prototype_ `void SetMoodIntensity(float InMoodIntensity);`
- L27 _public prototype_ `void SetOutputControls(const EAudioDrivenAnimationOutputControls& InOutputControls);`
- L29 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L30 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L31 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L33 _public prototype_ `void CancelModelSolve();`
- L35 _public member_ `TWeakObjectPtr<class USoundWave> Audio = nullptr;`
- L36 _public member_ `bool bDownmixChannels = true;`
- L37 _public member_ `uint32 AudioChannelIndex = 0;`
- L38 _public member_ `uint32 ProcessingStartFrameOffset = 0;` — Index of the first frame to arrive through pipeline
- L39 _public member_ `float OffsetSec = 0;` — When in audio to start solving
- L40 _public member_ `float FrameRate = 0;`
- L41 _public member_ `bool bClampTongueInOut = true;`
- L42 _public member_ `bool bGenerateBlinks = true;`
- L56 _protected member_ `TUniquePtr<FSpeech2Face> Speech2Face = nullptr;`
- L58 _protected member_ `TArray<TMap<FString, float>> Animation;`
- L59 _protected member_ `TArray<TMap<FString, float>> HeadAnimation;`
- L60 _protected member_ `bool bCancelStart = false;`
- L63 _private prototype_ `virtual bool PreConversionModifyUiControls(TMap<FString, float>& InOutAnimationFrame, FString& OutErrorMsg);`
- L64 _private prototype_ `virtual bool PostConversionModifyRawControls(TMap<FString, float>& InOutAnimationFrame, FString& OutErrorMsg);`
- L65 _private prototype_ `void PrepareFromOutputControls();`
- L67 _private member_ `EAudioDrivenAnimationOutputControls OutputControls = EAudioDrivenAnimationOutputControls::FullFace;`
- L68 _private member_ `EAudioProcessingMode ProcessingMode = EAudioProcessingMode::Undefined;`
- L69 _private member_ `TSet<FString> ActiveRawControls;`

#### enum `UE::MetaHuman::Pipeline::FSpeechToAnimNode::ErrorCode`  
`enum ErrorCode`  
_L44-53_
- L46 _public enumerator_ `InvalidAudio = 0`
- L47 _public enumerator_ `InvalidChannelIndex`
- L48 _public enumerator_ `FailedToSolveSpeechToAnimation`
- L49 _public enumerator_ `FailedToInitialize`
- L50 _public enumerator_ `InvalidFrame`
- L51 _public enumerator_ `FailedToModifyUiControls`
- L52 _public enumerator_ `FailedToModifyRawControls`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MetaHuman` (scope `UE`)
- L12 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/Nodes/TongueTrackerNode.h` (Public)


#### class `UE::MetaHuman::Pipeline::FTongueTrackerNode`  
`class FTongueTrackerNode : public FSpeechToAnimNode`  
_L14-27_
- inherits: `FSpeechToAnimNode`
- L18 _public prototype_ `FTongueTrackerNode(const FString& InName);`
- L21 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L24 _private prototype_ `bool PostConversionModifyRawControls(TMap<FString, float>& InOutAnimationFrame, FString& OutErrorMsg) override;`
- L26 _private member_ `static const TArray<FString> AffectedRawTongueControls;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MetaHuman` (scope `UE`)
- L11 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPipeline/Public/Nodes/TrackerUtilNodes.h` (Public)


#### class `UE::MetaHuman::Pipeline::FJsonTitanTrackerNode`  
`class FJsonTitanTrackerNode : public FNode`  
_L15-36_
- inherits: `FNode`
- L19 _public prototype_ `FJsonTitanTrackerNode(const FString& InName);`
- L21 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L22 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L23 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L25 _public member_ `FString JsonFile;`
- L35 _private member_ `TArray<FFrameTrackingContourData> Contours;`

#### enum `UE::MetaHuman::Pipeline::FJsonTitanTrackerNode::ErrorCode`  
`enum ErrorCode`  
_L27-31_
- L29 _public enumerator_ `FailedToLoadJsonFile = 0`
- L30 _public enumerator_ `InvalidData`

#### class `UE::MetaHuman::Pipeline::FJsonTrackerNode`  
`class FJsonTrackerNode : public FNode`  
_L38-59_
- inherits: `FNode`
- L42 _public prototype_ `FJsonTrackerNode(const FString& InName);`
- L44 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L45 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L46 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L48 _public member_ `FString JsonFile;`
- L58 _private member_ `TArray<FFrameTrackingContourData> Contours;`

#### enum `UE::MetaHuman::Pipeline::FJsonTrackerNode::ErrorCode`  
`enum ErrorCode`  
_L50-54_
- L52 _public enumerator_ `FailedToLoadJsonFile = 0`
- L53 _public enumerator_ `InvalidData`

#### class `UE::MetaHuman::Pipeline::FOffsetContoursNode`  
`class FOffsetContoursNode : public FNode`  
_L61-79_
- inherits: `FNode`
- L65 _public prototype_ `FOffsetContoursNode(const FString& InName);`
- L67 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L68 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L70 _public member_ `FVector2D ConstantOffset = FVector2D(0, 0);`
- L71 _public member_ `FVector2D RandomOffset = FVector2D(0, 0);`
- L75 _private member_ `float RandomOffsetMinX = -1.f;`
- L76 _private member_ `float RandomOffsetMaxX = -1.f;`
- L77 _private member_ `float RandomOffsetMinY = -1.f;`
- L78 _private member_ `float RandomOffsetMaxY = -1.f;`

#### class `UE::MetaHuman::Pipeline::FSaveContoursToJsonNode`  
`class FSaveContoursToJsonNode : public FNode`  
_L81-98_
- inherits: `FNode`
- L84 _public prototype_ `FSaveContoursToJsonNode(const FString& InName);`
- L86 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L87 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L88 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L96 _public member_ `FString FullSavePath;`
- L97 _public member_ `TSharedPtr<FJsonObject> ContourDataJson;`

#### enum `UE::MetaHuman::Pipeline::FSaveContoursToJsonNode::ErrorCode`  
`enum ErrorCode`  
_L90-94_
- L92 _public enumerator_ `FailedToCreateJson = 0`
- L93 _public enumerator_ `InvalidData`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANPIPELINE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MetaHuman` (scope `UE`)
- L12 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)
