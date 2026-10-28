# Plugins / CaptureManagerPipeline

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerPipeline`
- headers: 6; symbols: 75
- symbol kinds: class=7, enum=1, enumerator=2, macro=6, member=15, prototype=41, typedef=3
- PrivateDependencyModuleNames: CaptureUtils, ControlFlows, Core, CoreUObject, ImageWrapper, Projects
- PublicDependencyModuleNames: CaptureManagerTakeMetadata

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerPipeline/Public/CaptureManagerPipeline.h` (Public)


#### enum `EPipelineExecutionPolicy`  
`enum class EPipelineExecutionPolicy`  
_L19-23_
- L21 _public enumerator_ `Asynchronous = 0`
- L22 _public enumerator_ `Synchronous`

#### class `FCaptureManagerPipeline`  
`class FCaptureManagerPipeline : public TSharedFromThis<FCaptureManagerPipeline>`  
_L25-59_
- inherits: `TSharedFromThis<FCaptureManagerPipeline>`
- L28 _public typedef_ `using FResult = TMap<FGuid, FCaptureManagerPipelineNode::FResult>;`
- L30 _public prototype_ `FCaptureManagerPipeline(EPipelineExecutionPolicy InExecutionPolicy);`
- L31 _public prototype_ `~FCaptureManagerPipeline();`
- L33 _public prototype_ `FGuid AddGenericNode(TSharedPtr<FCaptureManagerPipelineNode> InNode);`
- L34 _public prototype_ `FGuid AddConvertVideoNode(TSharedPtr<FConvertVideoNode> InNode);`
- L35 _public prototype_ `FGuid AddConvertAudioNode(TSharedPtr<FConvertAudioNode> InNode);`
- L36 _public prototype_ `FGuid AddConvertDepthNode(TSharedPtr<FConvertDepthNode> InNode);`
- L37 _public prototype_ `FGuid AddConvertCalibrationNode(TSharedPtr<FConvertCalibrationNode> InNode);`
- L39 _public prototype_ `FGuid AddSyncedNode(TSharedPtr<FCaptureManagerPipelineNode> InNode);`
- L42 _public prototype_ `[[nodiscard]] FCaptureManagerPipeline::FResult Run();` — Blocking function
- L44 _public prototype_ `void Cancel();`
- L48 _private prototype_ `FGuid AddParallelPipelineNode(TSharedPtr<FCaptureManagerPipelineNode> InNode);`
- L50 _private member_ `TPimplPtr<class FCaptureManagerPipelineImpl> Impl;`
- L53 _private typedef_ `using FNodeMap = TMap<FGuid, TSharedPtr<FCaptureManagerPipelineNode>>;`
- L55 _private member_ `UE::CaptureManager::TMonitor<FNodeMap> ParallelNodes;`
- L56 _private member_ `UE::CaptureManager::TMonitor<FNodeMap> SyncNodes;`
- L58 _private member_ `EPipelineExecutionPolicy ExecutionPolicy;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API CAPTUREMANAGERPIPELINE_API`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerPipeline/Public/CaptureManagerPipelineNode.h` (Public)


#### class `FCaptureManagerPipelineError`  
`class FCaptureManagerPipelineError`  
_L14-27_
- L17 _public prototype_ `FCaptureManagerPipelineError(FText InMessage, int32 InCode = 0);`
- L19 _public prototype_ `const FText& GetMessage() const;`
- L21 _public prototype_ `int32 GetCode() const;`
- L25 _private member_ `FText Message;`
- L26 _private member_ `int32 Code;`

#### class `FCaptureManagerPipelineNode`  
`class FCaptureManagerPipelineNode : public TSharedFromThis<FCaptureManagerPipelineNode>`  
_L29-52_
- inherits: `TSharedFromThis<FCaptureManagerPipelineNode>`
- L33 _public typedef_ `using FResult = TValueOrError<void, FCaptureManagerPipelineError>;`
- L35 _public prototype_ `FCaptureManagerPipelineNode(const FString& InName);`
- L36 _public prototype_ `virtual ~FCaptureManagerPipelineNode();`
- L38 _public prototype_ `FString GetName() const;`
- L40 _public prototype_ `FResult Execute();`
- L41 _public prototype_ `void Cancel();`
- L45 _protected prototype_ `virtual FResult Prepare() = 0;`
- L46 _protected prototype_ `virtual FResult Run() = 0;`
- L47 _protected prototype_ `virtual FResult Validate() = 0;`
- L51 _private member_ `TPimplPtr<FCaptureManagerPipelineNodeImpl> Impl;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CAPTUREMANAGERPIPELINE_API`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerPipeline/Public/Nodes/ConvertAudioNode.h` (Public)


#### class `FConvertAudioNode`  
`class FConvertAudioNode : public FCaptureManagerPipelineNode`  
_L11-33_
- inherits: `FCaptureManagerPipelineNode`
- L15 _public prototype_ `FConvertAudioNode(const FTakeMetadata::FAudio& InAudio, const FString& InOutputDirectory);`
- L22 _protected member_ `FTakeMetadata::FAudio Audio;`
- L23 _protected member_ `FString OutputDirectory;`
- L27 _private prototype_ `virtual FResult Prepare() override final;`
- L28 _private prototype_ `virtual FResult Validate() override final;`
- L30 _private prototype_ `FString GetAudioDirectory() const;`
- L32 _private prototype_ `static FResult CheckForAudioFile(const FString& InAudioPath);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CAPTUREMANAGERPIPELINE_API`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerPipeline/Public/Nodes/ConvertCalibrationNode.h` (Public)


#### class `FConvertCalibrationNode`  
`class FConvertCalibrationNode : public FCaptureManagerPipelineNode`  
_L11-28_
- inherits: `FCaptureManagerPipelineNode`
- L15 _public prototype_ `FConvertCalibrationNode(const FTakeMetadata::FCalibration& InCalibration, const FString& InOutputDirectory);`
- L19 _protected member_ `FTakeMetadata::FCalibration Calibration;`
- L20 _protected member_ `FString OutputDirectory;`
- L24 _private prototype_ `virtual FResult Prepare() override final;`
- L25 _private prototype_ `virtual FResult Validate() override final;`
- L27 _private prototype_ `FString GetCalibrationDirectory() const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CAPTUREMANAGERPIPELINE_API`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerPipeline/Public/Nodes/ConvertDepthNode.h` (Public)


#### class `FConvertDepthNode`  
`class FConvertDepthNode : public FCaptureManagerPipelineNode`  
_L11-33_
- inherits: `FCaptureManagerPipelineNode`
- L15 _public prototype_ `FConvertDepthNode(const FTakeMetadata::FVideo& InDepth, const FString& InOutputDirectory);`
- L22 _protected member_ `FTakeMetadata::FVideo Depth;`
- L23 _protected member_ `FString OutputDirectory;`
- L27 _private prototype_ `virtual FResult Prepare() override final;`
- L28 _private prototype_ `virtual FResult Validate() override final;`
- L30 _private prototype_ `FString GetDepthDirectory() const;`
- L32 _private prototype_ `static FResult CheckImagesForDepth(const FString& InDepthPath);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CAPTUREMANAGERPIPELINE_API`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerPipeline/Public/Nodes/ConvertVideoNode.h` (Public)


#### class `FConvertVideoNode`  
`class FConvertVideoNode : public FCaptureManagerPipelineNode`  
_L11-33_
- inherits: `FCaptureManagerPipelineNode`
- L15 _public prototype_ `FConvertVideoNode(const FTakeMetadata::FVideo& InVideo, const FString& InOutputDirectory);`
- L22 _protected member_ `FTakeMetadata::FVideo Video;`
- L23 _protected member_ `FString OutputDirectory;`
- L27 _private prototype_ `virtual FResult Prepare() override final;`
- L28 _private prototype_ `virtual FResult Validate() override final;`
- L30 _private prototype_ `FString GetVideoDirectory() const;`
- L32 _private prototype_ `static FResult CheckImagesForVideo(const FString& InVideoPath);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CAPTUREMANAGERPIPELINE_API`
