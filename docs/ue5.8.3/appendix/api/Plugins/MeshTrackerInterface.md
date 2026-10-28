# Plugins / MeshTrackerInterface

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MeshTrackerInterface`
- headers: 1; symbols: 80
- symbol kinds: class=9, function=3, prototype=67, typedef=1
- PrivateDependencyModuleNames: CoreUObject, Engine, Projects
- PublicDependencyModuleNames: Core

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MeshTrackerInterface/Public/MetaHumanFaceTrackerInterface.h` (Public)


#### class `IMetaHumanFaceTrackerInterface`  
`class IMetaHumanFaceTrackerInterface`  
_L9-89_
- L12 _public prototype_ `virtual ~IMetaHumanFaceTrackerInterface() = default;`
- L14 _public prototype_ `virtual bool Init(const FString& InTemplateDescriptionJson, const FString& InConfigurationJson, const struct FTrackerOpticalFlowConfiguration& InOptFlowConfig, const FString& InPhysicalDeviceLUID) = 0;`
- L18 _public prototype_ `virtual bool LoadDNA(const FString& InDNAFile) = 0;` — Load the DNA file. Returns: True if the DNA file could be loaded.
- L22 _public prototype_ `virtual bool LoadDNA(class UDNAAsset* InDNAAsset) = 0;` — `UE_DEPRECATED(5.8, "Use LoadDNA function that accepts the reader instead, UDNAAsset has been deprecated.")` — Load the DNA from a UDNAAsset.@returns True if the DNA could be loaded.
- L25 _public prototype_ `virtual bool LoadDNA(TSharedPtr<class IDNAReader> InDNAReader) = 0;` — Load the DNA from a IDNAReader.@returns True if the DNA could be loaded.
- L28 _public prototype_ `virtual bool SetCameras(const TArray<struct FCameraCalibration>& InCalibration) = 0;` — Set up the cameras for tracking. Returns: True if successful, False upon any error.
- L31 _public prototype_ `virtual bool SetCameraRanges(const TMap<FString, TPair<float, float>>& InCameraRanges) = 0;` — Specify the ranges for each camera. @returns True if successful, False upon error.
- L40 _public prototype_ `virtual bool ResetTrack(int32 InFrameStart, int32 InFrameEnd, const struct FTrackerOpticalFlowConfiguration& InOptFlowConfig) = 0;` — Reset and set up a new track. @param[in] InFrameStart  The first frame of the sequence. @param[in] InFrameEnd  The last (not including) frame of the sequence. @param[in] InOptFlowConfig  Optical flow configuration for tracking. @returns True if successful, False upon error.
- L46 _public prototype_ `virtual bool SetStereoCameraPairs(const TArray<TPair<FString, FString>>& InStereoReconstructionPairs) = 0;` — Specify which cameras are used for stereo reconstruction. @returns True if successful, False if the cameras have not been set up via SetCameras().
- L61 _public prototype_ `virtual bool Track(int32 InFrameNumber, const TMap<FString, TPair<TPair<const float*, const float*>, TPair<TPair<const float*, const float*>, TPair<const float*, const float*>>>>& InFlowInfo = {}, bool bUseFastSolver = false, const FString& InDebuggingDataFolder = {}, bool bSkipPredictiveSolver = false, bool bInSkipPerVertexSolve = true) = 0;`
- L64 _public prototype_ `virtual bool GetTrackingState(int32 InFrameNumber, FTransform& OutHeadPose, TArray<float>& OutHeadPoseRaw, TMap<FString, float>& OutControls, TMap<FString, float>& OutRawControls, TArray<float>& OutFaceMeshVertices, TArray<float>& OutTeethMeshVertices, TArray<float>& OutLeftEyeMeshVertices, TArray<float>& OutRightEyeMeshVertices) = 0;`
- L68 _public prototype_ `virtual bool SetPCARig(const TArray<uint8>& InMemoryBuffer) = 0;`
- L70 _public prototype_ `virtual bool AddBrowMeshLandmarks(const FString& InBrowMeshJson) = 0;`
- L72 _public prototype_ `virtual bool TrainSolverModelsSync(const TArray<uint8>& InGlobalTeethPredictiveSolverTrainingDataMemoryBuffer, const TArray<uint8>& InPredictiveSolversTrainingDataMemoryBuffer) = 0;`
- L75 _public prototype_ `virtual bool GetPredictiveSolvers(TArray<uint8>& OutMemoryBufferPredictiveSolvers) = 0;`
- L77 _public prototype_ `virtual bool GetGlobalTeethPredictiveSolver(TArray<uint8>& OutMemoryBufferGlobalTeethPredictiveSolver) = 0;`
- L79 _public prototype_ `virtual bool SetPredictiveSolvers(const TArray<uint8>& InMemoryBufferPredictiveSolvers) = 0;`
- L81 _public prototype_ `virtual bool SetGlobalTeethPredictiveSolver(const TArray<uint8>& InMemoryBufferGlobalTeethPredictiveSolver) = 0;`
- L83 _public prototype_ `virtual bool EstimateScale(int32_t InFrameNumber, float& OutScale) = 0;`
- L85 _public prototype_ `virtual bool CreateFlattenedJsonStringWrapper(const FString& InSolverDefinitionsFile, FString& OutSolverDefinitionsJson) = 0;`
- L87 _public prototype_ `virtual bool LoadPredictiveSolverTrainingDataWrapper(const FString& InGlobalTeethPredictiveSolverDataFilename, const TArray<FString>& InPredictiveSolverDataFilenames, TArray<uint8> & OutGlobalTeethPredictiveSolverTrainingDataMemoryBuffer, TArray<uint8> & OutPredictiveSolversTrainingDataMemoryBuffer) = 0;`

#### class `IDepthGeneratorInterface`  
`class IDepthGeneratorInterface`  
_L91-130_
- L94 _public prototype_ `virtual ~IDepthGeneratorInterface() = default;`
- L96 _public prototype_ `virtual bool Init(const FString& InPhysicalDeviceLUID = "") = 0;`
- L98 _public prototype_ `virtual bool SetCameras(const TArray<struct FCameraCalibration>& InCalibration) = 0;`
- L104 _public prototype_ `virtual bool SetCameraRanges(const TMap<FString, TPair<float, float>>& InCameraRanges) = 0;` — Specify the ranges for each camera. @returns True if successful, False upon error.
- L110 _public prototype_ `virtual bool SetStereoCameraPairs(const TArray<TPair<FString, FString>>& InStereoReconstructionPairs) =0;` — Specify which cameras are used for stereo reconstruction. @returns True if successful, False if the cameras have not been set up via SetCameras().
- L119 _public prototype_ `virtual bool SetInputData(const TMap<FString, const unsigned char*>& InImageDataPerCamera, int32 InLevel = 0) = 0;` — Set the current input data and performs stereo reconstruction. @param[in] InImageDataPerCamera      The distorted images per camera (only images that are used for stereo reconstruction are necessary). @param[in] InLevel - reconstruction level @returns True if setting the data was successful.
- L124 _public prototype_ `virtual uint32 GetReconstructerState() = 0;` — Returns current Reconstructer state.
- L129 _public prototype_ `virtual bool GetDepthMap(int32 InStereoPairIndex, int32& OutWidth, int32& OutHeight, const float*& OutDataconst, const float*& OutIntrinsics, const float*& OutExtrinsics) = 0;` — Gets the depth map data calculated by SetInputData

#### class `IDepthMapDiagnosticsInterface`  
`class IDepthMapDiagnosticsInterface`  
_L132-142_
- L135 _public prototype_ `virtual ~IDepthMapDiagnosticsInterface() = default;`
- L137 _public prototype_ `virtual bool Init(const TArray<struct FCameraCalibration>& InCalibrations) = 0;`
- L139 _public prototype_ `virtual bool CalcDiagnostics(const TMap<FString, const unsigned char*>& InImageDataPerCamera, const TMap<FString, const struct FFrameTrackingContourData*>& InLandmarksDataPerCamera, const TMap<FString, const float*>& InDepthmapDataPerCamera, TMap<FString, struct FDepthMapDiagnosticsResult> & OutDiagnostics) = 0;`

#### class `IOpticalFlowInterface`  
`class IOpticalFlowInterface`  
_L144-157_
- L147 _public prototype_ `virtual ~IOpticalFlowInterface() = default;`
- L149 _public prototype_ `virtual bool Init(const FString& InConfigurationJson, const FString& InPhysicalDeviceLUID) = 0;`
- L151 _public prototype_ `virtual bool SetCameras(const TArray<FCameraCalibration>& InCalibrations) = 0;`
- L153 _public prototype_ `virtual bool CalculateFlow(const FString& InCameraName, bool bInUseConfidence, const TArray<float>& InImage0, const TArray<float>& InImage1, TArray<float>& OutFlow, TArray<float>& OutConfidence, TArray<float>& OutSourceCamera, TArray<float>& OutTargetCamera) = 0;`
- L156 _public prototype_ `virtual bool ConvertImageWrapper(const TArray<uint8_t>& InBGRAImageData, int32_t InWidth, int32_t InHeight, bool bIssRGB, TArray<float>& OutGreyImage) = 0;`

#### class `IFaceTrackerPostProcessingInterface`  
`class IFaceTrackerPostProcessingInterface`  
_L159-266_
- L162 _public prototype_ `virtual ~IFaceTrackerPostProcessingInterface() = default;`
- L170 _public prototype_ `virtual bool Init(const FString& InTemplateDescriptionJson, const FString& InConfigurationJson) = 0;` — Initialize face tracking post processing class. @param[in] InTemplateDescriptionJson: the flattened json for the template_description.json config (containing any none-json embedded objects as base64 strings) @param[in] InConfigurationJson: the flattened json for the configuration.json config (containing any none-json embedded objects as base64 strings) @returns True if initialization is successful, False otherwise.
- L179 _public prototype_ `virtual bool LoadDNA(const FString& InDNAFile, const FString& InSolverDefinitionsJson) = 0;` — Load the DNA file. @param[in] InDNAFile the path to the DNA file @param[in] InSolverDefinitionsJson: the string containing the solver definitions as json; a different config will be used for the standard solve than for the hierarchical solve @returns True if the DNA file could be loaded.
- L189 _public prototype_ `virtual bool LoadDNA(UDNAAsset* InDNAAsset, const FString& InSolverDefinitionsJson) = 0;` — `UE_DEPRECATED(5.8, "Use LoadDNA function that accepts the reader instead, UDNAAsset has been deprecated.")` — Load the DNA from a UDNAAsset. @param[in] InDNAAsset the DNA asset @param[in] InSolverDefinitionsJson: the string containing the solver definitions as json; a different config will be used for the standard solve than for the hierarchical solve @returns True if the DNA could be loaded.
- L198 _public prototype_ `virtual bool LoadDNA(TSharedPtr<IDNAReader> InDNAReader, const FString& InSolverDefinitionsJson) = 0;` — Load the DNA from a IDNAReader. @param[in] InDNAReader the DNA reader @param[in] InSolverDefinitionsJson: the string containing the solver definitions as json; a different config will be used for the standard solve than for the hierarchical solve @returns True if the DNA could be loaded.
- L206 _public prototype_ `virtual bool SetGlobalTeethPredictiveSolver(const TArray<uint8>& InMemoryBufferGlobalTeethSolver) = 0;` — Set the global teeth predictive solver from a memory buffer (this allows the data to be set from within a UE asset) @param[in] InMemoryBufferGlobalTeethSolver the buffer of the solver for the global teeth solve @returns True if successful
- L214 _public prototype_ `virtual bool SetCameras(const TArray<FCameraCalibration>& InCalibration, const FString& InCamera) = 0;` — Set up the cameras for tracking. @param[in] InCalibration An array of camera calibrations. @param[in] InCamera The camera to use. @returns True if successful, False upon any error.
- L222 _public prototype_ `virtual bool ConvertUIControlsToRawControls(const TMap<FString, float>& InGuiControls, TMap<FString, float>& OutRawControls) const = 0;` — Convert UI controls to raw controls @param[in] InGuiControls				The GUI controls @param[out] OutRawControls			The raw controls @returns True if successful, False upon any error.
- L233 _public prototype_ `virtual bool SaveDebuggingData(int32 InFrameNumberFirst, int32 InNumFramesToSolve, const TArray<FFrameTrackingContourData>& InTrackingData, const FString& InFilename, const FString& InDebuggingDataFolder) const = 0;` — Save the current debugging state to the specified folder and filename @param[in] InFrameNumberFirst			The first frame we performed the solve on in the class @param[in] InNumFramesToSolve			The number of frames to perform the offline global solve on @param[in] InTrackingData				The tracking data which was used during the solving steps @param[in] InFilename					The filename to save to @param[in] InDebuggingDataFolder		The folder to save to; if empty, does not save debugging states data @returns True if successful, False upon any error.
- L239 _public prototype_ `virtual void SetDisableGlobalSolves(bool bInDisableGlobalEyeGazeAndTeethSolves) = 0;` — Set whether to enable or disable the global teeth and eye gaze solves. Note by default global solves are enabled. @param[in] bInDisableGlobalEyeGazeAndTeethSolves: if set to true, disable the global eye gaze and teeth solves, otherwise apply these
- L251 _public prototype_ `virtual bool OfflineSolvePrepare(int32 InFrameNumberFirst, int32 InNumFramesToSolve, const TArray<FFrameTrackingContourData>& InTrackingData, TArray<struct FFrameAnimationData>& InOutFrameData, const FString& InDebuggingDataFolder = {}) const = 0;` — Perform offline solve steps (Eye Gaze correction, Teeth fitting) and prepare for the frame by frame processing @param[in] InFrameNumberFirst			The first frame to perform the offline global solve on @param[in] InNumFramesToSolve			The number of frames to perform the offline global solve on @param[in] InTrackingData				The tracking data which is used during the solving steps @param[in] InOutFrameData				The frame data, which contains the current animation state and other required data (eg meshes) which are used as priors and data for the global solves. On output the AnimationData in InOutFrameData is updated to reflect the results of the global solve steps. @param[in] InDebuggingDataFolder		The folder to save to; if empty, does not save debugging states data @returns True if successful, False upon any error.
- L264 _public prototype_ `virtual bool OfflineSolveProcessFrame(int32 InFrameNumber, int32 InFrameNumberFirst, int32 InNumFramesToSolve, TArray<FFrameAnimationData>& InOutFrameData, TArray<int32>& OutUpdatedFrames) const = 0;` — Perform the slow offline solve steps (final solve based upon the corrected eye gaze and teeth) @param[in] InFrameNumber     			The frame to perform the offline global solve on @param[in] InFrameNumberFirst			The first frame to perform the offline global solve on @param[in] InNumFramesToSolve			The number of frames to perform the offline global solve on @param[in] InTrackingData				The tracking data which is used during the solving steps @param[in] InOutFrameData				The frame data, which contains the current animation state and other required data (eg meshes) which are used as priors and data for the global solves. On output the AnimationData in InOutFrameData is updated to reflect the results of the global solve steps. @returns True if successful, False upon any error.

#### class `IFaceTrackerPostProcessingFilter`  
`class IFaceTrackerPostProcessingFilter`  
_L268-317_
- L271 _public prototype_ `virtual ~IFaceTrackerPostProcessingFilter() = default;`
- L279 _public prototype_ `virtual bool Init(const FString& InTemplateDescriptionJson, const FString& InConfigurationJson) = 0;` — Initialize face tracking post processing filter class. @param[in] InTemplateDescriptionJson:  the flattened template description config json string @param[in] InConfigurationJson: the flattened configuration json string c* @returns True if initialization is successful, False otherwise.
- L288 _public prototype_ `virtual bool LoadDNA(const FString& InDNAFile, const FString& InSolverDefinitions) = 0;` — Load the DNA file. @param[in] InDNAFile the path to the DNA file @param[in] InSolverDefinitions: the json string containing the solver definitions (may be from solver_definitions.json or hierarchical_solver_definitions.json) @returns True if the DNA file could be loaded.
- L298 _public prototype_ `virtual bool LoadDNA(UDNAAsset* InDNAAsset, const FString& InSolverDefinitions) = 0;` — `UE_DEPRECATED(5.8, "Use LoadDNA function that accepts the reader instead, UDNAAsset has been deprecated.")` — Load the DNA from a UDNAAsset. @param[in] InDNAAsset the DNA asset @param[in] InSolverDefinitions: the json string containing the solver definitions (may be from solver_definitions.json or hierarchical_solver_definitions.json) @returns True if the DNA could be loaded.
- L307 _public prototype_ `virtual bool LoadDNA(TSharedPtr<IDNAReader> InDNAReader, const FString& InSolverDefinitions) = 0;` — Load the DNA from a IDNAReader. @param[in] InDNAReader the DNA reader @param[in] InSolverDefinitions: the json string containing the solver definitions (may be from solver_definitions.json or hierarchical_solver_definitions.json) @returns True if the DNA could be loaded.
- L316 _public prototype_ `virtual bool OfflineFilter(int32 InFrameNumberFirst, int32 InNumFramesToFilter, TArray<FFrameAnimationData>& InOutFrameData, const FString& InDebuggingDataFolder = {}) const = 0;` — Perform offline filtering @param[in] InFrameNumberFirst			The first frame to perform the offline filter on @param[in] InNumFramesToFilter			The number of frames to perform the offline filter on @param[in] InOutFrameData				The frame data, which contains the current animation state. On output the AnimationData in InOutFrameData is updated to reflect the results of the global solve steps. @returns True if successful, False upon any error.

#### class `IPredictiveSolverInterface`  
`class IPredictiveSolverInterface : public IModularFeature`  
_L319-335_
- inherits: `IModularFeature`
- L323 _public function_ `static FName GetModularFeatureName()`
- L329 _public prototype_ `virtual ~IPredictiveSolverInterface() = default;`
- L330 _public typedef_ `using SolverProgressFunc = TFunction<void(float)>;`
- L332 _public prototype_ `virtual void TrainPredictiveSolver(std::atomic<bool>& bIsDone, std::atomic<float>& InProgress, SolverProgressFunc InOnProgress, std::atomic<bool>& bInIsCancelled, const struct FPredictiveSolversTaskConfig& InConfig, struct FPredictiveSolversResult& OutResult) = 0;`

#### class `IDepthProcessingMetadataProvider`  
`class IDepthProcessingMetadataProvider : public IModularFeature`  
_L337-357_
- inherits: `IModularFeature`
- L340 _public prototype_ `virtual ~IDepthProcessingMetadataProvider() = default;`
- L342 _public function_ `static FName GetModularFeatureName()`
- L353 _public prototype_ `virtual bool ListPhysicalDeviceLUIDs(TArray<FString>& OutDeviceLUIDs) = 0;` — List all GPU devices. Report each one using a locally unique identifier (LUID) @param[out] OutDeviceLUIDs  List of all device LUIDs. @returns True if successful, False otherwise.
- L356 _public prototype_ `virtual FString GetMeshTrackerVersionString() = 0;` — Returns the MeshTracker version of the Depth Processing plugin

#### class `IFaceTrackerNodeImplFactory`  
`class IFaceTrackerNodeImplFactory : public IModularFeature`  
_L359-377_
- inherits: `IModularFeature`
- L362 _public prototype_ `virtual ~IFaceTrackerNodeImplFactory() = default;`
- L364 _public function_ `static FName GetModularFeatureName()`
- L370 _public prototype_ `virtual TSharedPtr<IMetaHumanFaceTrackerInterface> CreateFaceTrackerImplementor() = 0;`
- L371 _public prototype_ `virtual TSharedPtr<IDepthMapDiagnosticsInterface> CreateDepthMapImplementor() = 0;`
- L372 _public prototype_ `virtual TSharedPtr<IDepthGeneratorInterface> CreateDepthGeneratorImplementor() = 0;`
- L373 _public prototype_ `virtual TSharedPtr<IOpticalFlowInterface> CreateOpticalFlowImplementor() = 0;`
- L374 _public prototype_ `virtual TSharedPtr<IFaceTrackerPostProcessingInterface> CreateFaceTrackerPostProcessingImplementor() = 0;`
- L375 _public prototype_ `virtual TSharedPtr<IFaceTrackerPostProcessingFilter> CreateFaceTrackerPostProcessingFilterImplementor() = 0;`
