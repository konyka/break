# Plugins / MetaHumanCoreTechLib

- module root: `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib`
- headers: 316; symbols: 6803
- symbol kinds: class=237, delegate=1, enum=59, enumerator=242, function=1759, macro=67, member=1299, namespace=63, prototype=2804, struct=149, typedef=122, variable=1
- PrivateDependencyModuleNames: CaptureDataCore, Core, CoreUObject, Engine, ImageCore, Json, MetaHumanCoreTech, OnlineSubsystem, Projects, UnrealEd, simde
- PublicDependencyModuleNames: Eigen, MetaHumanSDKRuntime, RigLogicLib, RigLogicModule

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/MetaHumanPluginResourceLoader.h` (Private)


#### class `FMetaHumanPluginResourceLoader`  
`class FMetaHumanPluginResourceLoader : public coretechlib::epic::nls::IMetaHumanFileResourceLoader`  
_L10-26_
- inherits: `coretechlib::epic::nls::IMetaHumanFileResourceLoader`
- L15 _public prototype_ `virtual ~FMetaHumanPluginResourceLoader() override = default;`
- L17 _public prototype_ `virtual bool Exists(const char* InPathUtf8) const override;`
- L18 _public prototype_ `virtual bool ReadAllText(const char* InPathUtf8, char*& OutData, std::size_t& OutSize) const override;`
- L19 _public prototype_ `virtual bool ReadAllBytes(const char* InPathUtf8, void*& OutData, std::size_t& OutSize) const override;`
- L20 _public prototype_ `virtual void Free(const void* InPtr) const override;`
- L21 _public prototype_ `virtual bool ResolveDataLoadingPath(const char* InBasePathUtf8, const std::size_t& InBaseSize, const char* InAppendPathUtf8, std::size_t& InAppendSize, char*& OutPathUtf8, std::size_t& OutSize) const override;`
- L25 _private prototype_ `FString GetResolvedMetaHumanPluginContentPath(const FString& InPath) const;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/MetaHumanTextureSynthesisModelData.h` (Private)


#### struct `FMetaHumanTextureSynthesizerModelData`  
`struct FMetaHumanTextureSynthesizerModelData`  
_L12-88_
- desc: Helper for loading and storing the data needed to use the titan texture synthesis model
- L48 _public member_ `int32 HFResolution = 0;` — Resolution of the loaded HF model data
- L51 _public member_ `int32 LFResolution = 0;` — Resolution of the loaded LF model data
- L54 _public member_ `TSortedMap<TITAN_NAMESPACE::ts::Data_Type, FModelDataContainer> SynthesisModelData;` — Model data used to do the synthesis part of the model
- L60 _public member_ `FModelDataContainer AlbedoHFMaps[4];` — Maps that complement the synthesis to get the final result Correspond to the types of supported maps: neutral and animated 1-3
- L61 _public member_ `FModelDataContainer AlbedoLFMaps[4];`
- L62 _public member_ `FModelDataContainer NormalHFMaps[4];`
- L63 _public member_ `FModelDataContainer CavityHFMap;`
- L70 _public prototype_ `void Load(const FString& InModelDataFolderPath, const FString& InCompressedFileName = TEXT("comp` — Load the model data from the input folder First checks if there is a compressed file with the data in the folder, tries to load the raw loose files if no archive is available
- L77 _public prototype_ `void LoadMapsFromFolder(const FString& InModelDataFolderPath, bool bLoadHFAnimatedMaps = true);` — Load the model data from the loose files in the input folder @param InModelDataFolderPath, folder with the npy files storing the model data for the texture synthesis model @param bLoadAnimatedMaps, set to false to not load the HF animated map from the data
- L82 _public prototype_ `bool IsValidForSynthesis() const;` — Returns true if the loaded model data can be used to do synthesis
- L87 _public prototype_ `void Serialize(FArchive& InAr);` — Serialize to an archive, all internal data containers will be compressed

#### struct `FMetaHumanTextureSynthesizerModelData::FModelDataContainer`  
`struct FModelDataContainer`  
_L18-45_
- desc: Buffer with the data for a specific model map Reflects the storage passed to the texture model via the Model_Data type, providing UE lifetime management
- L20 _public function_ `FModelDataContainer() : NumRows(0), NumColumns(0), WordSize(0)`
- L27 _public function_ `FModelDataContainer(int32 InNumRows, int32 InNumColumns, int32 InWordSize) : NumRows(InNumRows), NumColumns(InNumColumns), WordSize(InWordSize)`
- L35 _public member_ `int32 NumRows;`
- L36 _public member_ `int32 NumColumns;`
- L37 _public member_ `int32 WordSize;`
- L38 _public member_ `TArray<uint8> DataBuffer;`
- L44 _public prototype_ `void Serialize(FArchive& InAr);` — Serialize the data into an archive DataBuffer will be compressed, empty buffers are handled gracefully

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/SerializeTextureSynthesisModelDataCommandlet.h` (Private)


#### class `USerializeTextureSynthesisModelDataCommandlet`  
`class USerializeTextureSynthesisModelDataCommandlet : public UCommandlet`  
_L14-21_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Serializes and compresses the texture synthesis model data into a UE archive
- L19 _private prototype_ `virtual int32 Main(const FString& Params) override;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/TitanVersion.h` (Private)


#### Free symbols / members of external scopes

- L3 _macro_ `#define MHCTL_TITAN_MAJOR_VERSION 9`
- L4 _macro_ `#define MHCTL_TITAN_MINOR_VERSION 0`
- L5 _macro_ `#define MHCTL_TITAN_PATCH_VERSION 9`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/api/ActorCreationAPI.h` (Private)


#### enum `TITAN_API_NAMESPACE::FittingMaskType`  
`enum class FittingMaskType`  
_L28-40_
- L30 _public enumerator_ `RIGID`
- L31 _public enumerator_ `NONRIGID`
- L32 _public enumerator_ `FINE`
- L33 _public enumerator_ `EYE_INTERFACE_LEFT`
- L34 _public enumerator_ `EYE_INTERFACE_RIGHT`
- L35 _public enumerator_ `TEETH`
- L36 _public enumerator_ `EYE`
- L37 _public enumerator_ `MOUTH_SOCKET`
- L38 _public enumerator_ `STABILIZATION`
- L39 _public enumerator_ `TEETH_HEAD_COLLISION_INTERFACE`

#### enum `TITAN_API_NAMESPACE::ScanMaskType`  
`enum class ScanMaskType`  
_L42-46_
- L44 _public enumerator_ `GLOBAL`
- L45 _public enumerator_ `EYE_FITTING`

#### enum `TITAN_API_NAMESPACE::IdentityModelType`  
`enum class IdentityModelType`  
_L48-52_
- L50 _public enumerator_ `FACE`
- L51 _public enumerator_ `COMBINED`

#### class `TITAN_API_NAMESPACE::ActorCreationAPI`  
`class ActorCreationAPI`  
_L54-497_
- L57 _public prototype_ `ActorCreationAPI();`
- L58 _public prototype_ `~ActorCreationAPI();`
- L59 _public prototype_ `ActorCreationAPI(ActorCreationAPI&&) = delete;`
- L60 _public prototype_ `ActorCreationAPI(const ActorCreationAPI&) = delete;`
- L61 _public prototype_ `ActorCreationAPI& operator=(ActorCreationAPI&&) = delete;`
- L62 _public prototype_ `ActorCreationAPI& operator=(const ActorCreationAPI&) = delete;`
- L71 _public prototype_ `bool Init(const std::string& InConfigurationDirectory);` — Initialize actor creation. Note this way of initializing the API is now deprecated. @param[in] InConfigurationDirectory  Directory containing a template_description.json and a dna_description.json file. @returns True if initialization is successful, False otherwise.
- L80 _public prototype_ `bool Init(const char* InTemplateDescriptionJson, const char* InIdentityModelJson);` — Initialize actor creation. @param[in] InTemplateDescriptionJson  the flattened template description json @param[in] InIdentityModelJson        the flattened identity model json @returns True if initialization is successful, False otherwise.
- L85 _public prototype_ `bool SetNumThreads(int numThreads);` — Set the number of processing threads for the API. Recreates the global thread pool with the specified number of threads
- L95 _public prototype_ `bool SetDepthInputData(const std::map<std::string, const std::map<std::string, FaceTrackingLandmarkData>>& InLandmarksDataPerCamera, const std::map<std::string, const float*>& InDepthMaps);` — Set the depth input data for one frame. @param[in] InLandmarksDataPerCamera  The distorted landmarks for each camera. @param[in] InDepthMaps Depthmap data per (depthmap) camera. @returns True if setting the data was successful. @warning Fails if scan data was set before.
- L108 _public prototype_ `bool SetScanInputData(const std::map<std::string, const FaceTrackingLandmarkData>& In3dLandmarksData, const std::map<std::string, const std::map<std::string, FaceTrackingLandmarkData>>& In2dLandmarksData, const MeshInputData& InScanData, bool& bOutInvalidMeshTopology);` — Set the scan input data. @param[in] In3dLandmarksData  Landmarks in 3D. @param[in] In2dLandmarksData  The distorted landmarks per camera view. @param[in] InScanData  Input scan data with triangles stored as numTriangles x 3 and vertices as numVertices x 3 in column major format. @param[out] bOutInvalidMeshTopology Set to false if the mesh has a valid topology, true if all vertices on the input mesh are invalid eg due to all disconnected triangles @returns True if setting the data was successful. @warning Fails if depthmap data was set before.
- L120 _public prototype_ `bool SetCameras(const std::map<std::string, OpenCVCamera>& InCameras);` — Set up the cameras for fitting. @param[in] InCameras  Input cameras for landmarks and depth projection. @returns True if successful, false upon any error.
- L130 _public prototype_ `bool CalculateAndUpdateScanMask(const std::string& InCameraName, ScanMaskType InScanMaskType);` — Set the scan mask type. Method enables specific scan mask creation for eyes fitting or global mesh mask (masking out invalid input points). Note that when generating eyes fitting mask, landmarks are needed for calculation. This means that the landmarks from the camera with label *InCameraName* will be used. @param[in] InCameraName  Input camera name. Note that this camera must already be set through *SetCameras*. @param[in] InScanMaskType  Input scan mask type. Currently supports specific eye mask and global mask. @returns True if successful, false upon any error.
- L136 _public prototype_ `float GetModelRegularization() const;` — Get regularization for non-rigid fitting. @returns regularization multiplier for non-rigid fitting.
- L142 _public prototype_ `void SetModelRegularization(float regularization);` — Set regularization for non-rigid fitting. @param[in] regularization multiplier
- L148 _public prototype_ `float GetPerVertexOffsetRegularization() const;` — Get offset regularization for per-vertex fitting. @returns regularization multiplier for per-vertex fitting.
- L154 _public prototype_ `void SetPerVertexOffsetRegularization(float regularization);` — Set regularization for per-vertex fitting. @param[in] regularization multiplier
- L160 _public prototype_ `float GetPerVertexLaplacianRegularization() const;` — Get Laplacian regularization for per-vertex fitting. @returns regularization multiplier for per-vertex fitting.
- L166 _public prototype_ `void SetPerVertexLaplacianRegularization(float regularization);` — Set Laplacian regularization for per-vertex fitting. @param[in] regularization multiplier
- L172 _public prototype_ `float GetMinimumDistanceThreshold() const;` — Get ICP minimum distance threshold (used for all types of fitting). @returns threshold value.
- L178 _public prototype_ `void SetMinimumDistanceThreshold(float threshold);` — Set ICP minimum distance threshold (used for all types of fitting). @param[in] threshold value
- L184 _public prototype_ `bool GetUseMinimumDistanceThreshold() const;` — Get the switch option to use / not to use ICP distance threshold. @returns if true, distance threshold will be used in fitting.
- L190 _public prototype_ `void SetUseMinimumDistanceThreshold(bool useIcpDistanceThreshold);` — Set the switch option to use / not to use ICP distance threshold. @param[in] if true, distance treshold will be used to reduce search
- L196 _public prototype_ `float GetLandmarksWeight() const;` — Get landmarks weight (used for all types of fitting). @returns landmarks weight multiplier for all types of fitting.
- L202 _public prototype_ `void SetLandmarksWeight(float weight);` — Set landmarks weight (used for all types of fitting). @param[in] weight value
- L208 _public prototype_ `bool GetAutoMultiViewLandmarkMasking() const;` — Get is the multi-view landmark masking enabled @returns is multi-view landmark masking enabled
- L214 _public prototype_ `void SetAutoMultiViewLandmarkMasking(bool useLandmarkMask);` — Set option to use auto multi-view landmark masking @param[in] bool value
- L220 _public prototype_ `float GetInnerLipsLandmarksWeight() const;` — Get landmarks weight for inner lips (used for all types of fitting). @returns landmarks weight multiplier for all types of fitting.
- L226 _public prototype_ `void SetInnerLipsLandmarksWeight(float weight);` — Set landmarks weight (used for all types of fitting). @param[in] weight value
- L232 _public prototype_ `float GetInnerLipsCollisionWeight() const;` — Get collision weight for inner lips (used for all types of fitting). @returns collision weight multiplier for all types of fitting.
- L238 _public prototype_ `void SetInnerLipsCollisionWeight(float weight);` — Set collision weight (used for all types of fitting). @param[in] collision weight value
- L244 _public prototype_ `float GetRigLogicL1RegularizationWeight() const;` — Get regularization weight for rig logic fit. @returns regularization weight multiplier for rig logic.
- L250 _public prototype_ `void SetRigLogicL1RegularizationWeight(float weight);` — Set regularization weight for rig logic. @param[in] regularization weight value
- L258 _public prototype_ `bool GetFittingMask(float* OutVertexWeights, FittingMaskType InMaskType) const;` — Get vertex weights for mask type. @param[out] InVertexWeights weight values @param[in] InMaskType mask type @returns True if was successful.
- L266 _public prototype_ `bool SetFittingMask(float* InVertexWeights, FittingMaskType InMaskType);` — Set vertex weights for mask type. @param[in] InVertexWeights weight values @param[in] InMaskType mask type @returns True if was successful.
- L278 _public prototype_ `bool FitRigid(float* OutVertexPositions, float* OutStackedToScanTransforms, float* OutStackedToScanScales, int32_t InNumIters = 3, const bool InAutoMode = true);` — Fit identity given input data. @param[out] OutVertexPositions  Vertex positions describing new identity as numVertices x 3 in column major format placed in *RIG COORDINATE SPACE*. @param[out] OutStackedToScanTransforms  Stacked 4x4 transform matrices in column major format. @param[out] OutStackedToScanScales  Stacked scale values. Scale is not a linear part of ToScanTransform, and needs to be applied after the transformation. @param[in] InNumIters  Number of iterations of the optimization. @param[in] InAutoMode  Enable auto mode where optimization will have iterations with decreasing regularization (InNumIters then have no effect). @returns True if fitting was successful.
- L292 _public prototype_ `bool SaveDebuggingData(const std::string& InDebugDataDirectory);` — Save debugging data. Saves the debugging data for Actor Creation. This method will save cameras (as .json), 2D landmarks (as .json) and a mesh for each depthmap or scan (as an .obj mesh) into the specified folder. Requires all data to have been set using SetCameras, SetScanInputData or SetDepthInputData before calling. Saving this data should allow a researcher to replicate bugs found in UE. Currently does not support saving of 3D landmarks. @param[in] InDebugDataDirectory  The folder to save the debug data to. @returns True if saving the debugging data was successful.
- L304 _public prototype_ `bool FitNonRigid(float* OutVertexPositions, float* OutStackedToScanTransforms, float* OutStackedToScanScales, int32_t InNumIters = 3, const bool InAutoMode = true);` — Fit identity given input data. @param[out] OutVertexPositions  Vertex positions describing new identity as numVertices x 3 in column major format placed in *RIG COORDINATE SPACE*. @param[out] OutStackedToScanTransforms  Stacked 4x4 transform matrices in column major format. @param[out] OutStackedToScanScales  Stacked scale values. Scale is not a linear part of ToScanTransform, and needs to be applied after the transformation. @param[in] InNumIters  Number of iterations of the optimization. @param[in] InAutoMode  Enable auto mode where optimization will have iterations with decreasing regularization (InNumIters then have no effect). @returns True if fitting was successful.
- L321 _public prototype_ `bool FitPerVertex(float* OutVertexPositions, float* OutStackedToScanTransforms, float* OutStackedToScanScales, int32_t InNumIters = 3, const std::string& InDebugDataDirectory = {});` — Fit identity given input data. @param[out] OutVertexPositions  Vertex positions describing new identity as numVertices x 3 in column major format placed in *RIG COORDINATE SPACE*. @param[out] OutStackedToScanTransforms  Stacked 4x4 transform matrices in column major format. @param[out] OutStackedToScanScales  Stacked scale values. Scale is not a linear part of ToScanTransform, and needs to be applied after the transformation. @param[in] InNumIters  Number of iterations of the optimization. @param[in] InDebugDataDirectory  The folder to save the debug data to. If not empty, saves the conformed mesh to the supplied folder as face_conformed.obj @returns True if fitting was successful.
- L337 _public prototype_ `bool FitRigLogic(dna::Reader* InDnaStream, float* OutVertexPositions, float* OutStackedToScanTransforms, float* OutStackedToScanScales, int32_t InNumIters = 3);` — Fit expression using riglogic given input data. @param[in] InDnaStream  Input DNA -must be RigLogic rig- to be used as deformable model to fit the expression. @param[out] OutVertexPositions  Vertex positions describing new identity as numVertices x 3 in column major format placed in *RIG COORDINATE SPACE*. @param[out] OutStackedToScanTransforms  Stacked 4x4 transform matrices in column major format. @param[out] OutStackedToScanScales  Stacked scale values. Scale is not a linear part of ToScanTransform, and needs to be applied after the transformation. @param[in] InNumIters  Number of iterations of the optimization. @returns True if fitting was successful.
- L356 _public prototype_ `bool FitPcaRig(dna::Reader* InDnaStream, float* OutVertexPositions, float* OutStackedToScanTransforms, float* OutStackedToScanScales, const float* OptionalInNeutralVertexPositions = nullptr, int32_t InNumIters = 3, const std::string& InDebugDataDirectory = {});` — Fit expression using PCA rog given input data. @param[in] InDnaStream  Input DNA -must be PCA rig- to be used as deformable model to fit the expression. @param[out] OutVertexPositions  Vertex positions describing new identity as numVertices x 3 in column major format placed in *RIG COORDINATE SPACE*. @param[out] OutStackedToScanTransforms  Stacked 4x4 transform matrices in column major format. @param[out] OutStackedToScanScales  Stacked scale values. Scale is not a linear part of ToScanTransform, and needs to be applied after the transformation. @param[in] InNumIters  Number of iterations of the optimization. @param[in] OptionalInNeutralVertexPositions  Optional referent neutral vertices for auto stabilization procedure. @param[in] InDebugDataDirectory  The folder to save debugging data to for the teeth fitting. If not empty, saves the conformed teeth mesh to the supplied folder as face_fitted.obj @returns True if fitting was successful.
- L372 _public prototype_ `bool FitTeeth(float* OutVertexPositions, int32_t InNumIters = 3, const std::string& InDebugDataDirectory = {});` — Update teeth model and position in the rig given input data. @param[out] OutVertexPositions  Vertex positions describing updated teeth fitted to the data and in *RIG COORDINATE SPACE*. @param[in] InNumIters  Number of iterations of the optimization. @param[in] InDebugDataDirectory  The folder to save debugging data to for the teeth fitting. If not empty, saves the conformed teeth mesh to the supplied folder as teeth_conformed.obj @returns True if fitting was successful.
- L379 _public prototype_ `bool UpdateTeethSource(const float* InVertexPositions);` — Update teeth source mesh model. Important if depth regularization for *FitTeeth* is used since it will use the source mesh as reference. @param[in] InVertexPositions  Vertex positions describing teeth shape in *RIG COORDINATE SPACE*. @returns True if fitting was successful.
- L386 _public prototype_ `bool UpdateHeadSource(const float* InVertexPositions);` — Update head source mesh model. Important for ActorTeethUpdateApp so that dna identity is referenced rather than generic template. @param[in] InVertexPositions  Vertex positions describing head shape assuming *RIG COORDINATE SPACE* of actor dna. @returns True if fitting was successful.
- L397 _public prototype_ `bool CalcTeethDepthDelta(float InDeltaDistanceFromCamera, float& OutDx, float& OutDy, float& OutDz);` — Calculate the offset in *RIG COORDINATE SPACE* to move the teeth a distance InDeltaDistanceFromCamera away from the first (1st) camera. Assumes FitTeeth has been called. @param[out] OutDx delta x for teeth in *RIG COORDINATE SPACE*. @param[out] OutDy delta y for teeth in *RIG COORDINATE SPACE*. @param[out] OutDz delta z for teeth in *RIG COORDINATE SPACE*. @param[in] InDeltaDistanceFromCamera The distance in cm to move the current teeth away from the camera position. @returns True if fitting was successful.
- L410 _public prototype_ `bool FitEyes(float* OutLeftEyeVertexPositions, float* OutRightEyeVertexPositions, bool InSetInterfaceForFaceFitting = true, int32_t InNumIters = 3, const bool InAutoMode = true, const std::string& InDebugDataDirectory = {});` — Update eye model and position in the rig given input data. @param[out] OutLeftEyeVertexPositions  Vertex positions describing updated teeth fitted to the data and in *RIG COORDINATE SPACE*. @param[out] OutRightEyeVertexPositions  Vertex positions describing updated teeth fitted to the data and in *RIG COORDINATE SPACE*. @param[in] InSetInterfaceForFaceFitting  If true, this method will also set the result of eyes fitting as eye-to-face interface for FitPerVertex. @param[in] InNumIters  Number of iterations of the optimization. @param[in] InAutoMode  Enable auto mode where optimization will have iterations with decreasing regularization (InNumIters then have no effect). @param[in] InDebugDataDirectory  The folder to save debugging data to for the eye fitting. If not empty, saves the conformed left eye and right eye meshes to the supplied folder as left_eye_conformed.obj and right_eye_conformed.obj @returns True if fitting was successful.
- L432 _public prototype_ `bool GetFittingState(float* OutStackedToScanTransforms, float* OutStackedToScanScales, float* OutFaceMeshVertices, float* OutTeethMeshVertices, float* OutLeftEyeMeshVertices, float* OutRightEyeMeshVertices);` — Retrieve the fitting state @param[out] OutStackedToScanTransforms  Stacked 4x4 transform matrices in column major format. @param[out] OutStackedToScanScales  Stacked scale values. Scale is not a linear part of ToScanTransform, and needs to be applied after the transformation. @param[out] OutFaceMeshVertices     Current state of head mesh vertices; vertices are stored as XYZ triples. It's caller responsibility to allocate the memory to the right size before calling the function. @param[out] OutTeethMeshVertices    Current state of teeth mesh vertices; vertices are stored as XYZ triples. It's caller responsibility to allocate the memory to the right size before calling the function. @param[out] OutLeftEyeMeshVertices  Current state of eye left mesh vertices; vertices are stored as XYZ triples. It's caller responsibility to allocate the memory to the right size before calling the function. @param[out] OutRightEyeMeshVertices Current state of eye right mesh vertices; vertices are stored as XYZ triples. It's caller responsibility to allocate the memory to the right size before calling the function. @returns True if the state could be retrieved, False if there is no valid fitting state.
- L444 _public prototype_ `bool GetIdentityModelType(IdentityModelType& OutIdentityModelType);` — Get identity model type derived from configuration files. @param[out] identity model type - can be COMBINED or FACE. If combined, identity model also contains teeth and eye vertices. @returns regularization multiplier for non-rigid fitting.
- L452 _public prototype_ `static bool CheckPcaModelFromDnaRigConfig(const char* InConfigurationFileOrJson, dna::Reader* InDnaStream);` — Check that the supplied PCA from DNA rig config is valid. @param[in] InConfigurationFileOrJson  Path to pca from dna configuration file or Json string containing the config. @param[in] InDnaStream  An example DNA asset to be used with the config. @returns true if the config is valid, false otherwise
- L462 _public prototype_ `static bool CalculatePcaModelFromDnaRig(const char* InConfigurationFileOrJson, dna::Reader* InDnaStream, dna::Writer* OutDnaStream, const std::string& InDebugDataDirectory = "");` — Creates a PCA rig out of input DNA RigLogic rig. Rig is stored in dna format. @param[in] InConfigurationFileOrJson  Path to pca from dna configuration file, or a Json string containing the config @param[in] InDnaStream  Input DNA stream containing RigLogic rig. @param[out] OutDnaStream  Output DNA stream containing PCA rig. @param[in] InDebugDataDirectory If this is not empty, save the calculated pca rig as file pca_rig.dna @returns True if DNA update was successful.
- L475 _public prototype_ `bool GenerateBrowMeshLandmarks(const std::string& InCameraName, std::string& OutJsonStream, float & OutFractionLandmarksInBrowRegion, bool InConcatenate = false) const;` — Projects brow target landmarks to fitted mesh. Outputs brows projected to mesh as mesh landmarks. @param[in]  InCameraName  Which camera landmarks to use for projection. @param[out] OutJsonStream  Serialized json containing all mesh landmarks. @param[out] OutFractionLandmarksInBrowRegion  The fraction of brow landmarks which were inside the brow region. @param[in]  InConcatenate  Should OutJsonStream contain just projected brow landmarks (false), or to concatenate with all mesh landmarks (true). @returns True if brow landmarks are generated successfully.
- L482 _public prototype_ `bool LoadFittingConfigurations(const std::string& InJsonStream);` — Loads fitting parameters for multiple solvers. @param[in]  InJsonStream  Serialized solver configuration json @returns True if loading json was successful.
- L489 _public prototype_ `bool SaveFittingConfigurations(std::string& OutJsonStream) const;` — Saves fitting parameters for multiple solvers. @param[out]  OutJsonStream  Serialized json containing solver configuration information @returns True if saving json was successful.
- L492 _public prototype_ `bool ResetInputData();` — Resets all input data
- L496 _private member_ `Private* m{};`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace dna`
- L25 _namespace_ `namespace TITAN_API_NAMESPACE`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/api/ActorRefinementAPI.h` (Private)


#### enum `TITAN_API_NAMESPACE::RefinementMaskType`  
`enum class RefinementMaskType`  
_L22-26_
- L24 _public enumerator_ `MOUTH_SOCKET`
- L25 _public enumerator_ `TEETH_PLACEMENT`

#### enum `TITAN_API_NAMESPACE::RefinementMeshCorrespondenceType`  
`enum class RefinementMeshCorrespondenceType`  
_L28-33_
- L30 _public enumerator_ `RIGID`
- L31 _public enumerator_ `DELTA_TRANSFER`
- L32 _public enumerator_ `UV_SPACE_PROJECTION`

#### class `TITAN_API_NAMESPACE::ActorRefinementAPI`  
`class ActorRefinementAPI`  
_L35-231_
- L38 _public prototype_ `ActorRefinementAPI();`
- L39 _public prototype_ `~ActorRefinementAPI();`
- L40 _public prototype_ `ActorRefinementAPI(ActorRefinementAPI&&) = delete;`
- L41 _public prototype_ `ActorRefinementAPI(const ActorRefinementAPI&) = delete;`
- L42 _public prototype_ `ActorRefinementAPI& operator=(ActorRefinementAPI&&) = delete;`
- L43 _public prototype_ `ActorRefinementAPI& operator=(const ActorRefinementAPI&) = delete;`
- L51 _public prototype_ `bool GetRefinementMask(float* OutVertexWeights, RefinementMaskType InMaskType) const;` — Get vertex weights for mask type. @param[out] InVertexWeights weight values @param[in] InMaskType mask type @returns True if was successful.
- L60 _public prototype_ `bool SetRefinementMask(int32_t NumVertices, const float* InVertexWeights, RefinementMaskType InMaskType);` — Set vertex weights for mask type. @param[in] Num of input weights @param[in] InVertexWeights weight values @param[in] InMaskType mask type @returns True if was successful.
- L69 _public prototype_ `bool UpdateRigWithTeethMeshVertices(dna::Reader* InDnaStream, const float* InTeethMeshVertexPositions, dna::Writer* OutDnaStream);` — Update teeth model and position in the rig given input data. @param[in] InDnaStream  Input DNA stream. @param[in] InTeethMeshVertexPositions  Input target vertex positions - Teeth mesh vertices - as numVertices x 3 in column major order.. @param[out] OutDnaStream  Updated dna stream. @returns True if fitting and DNA update was successful.
- L78 _public prototype_ `bool UpdateRigWithHeadMeshVertices(dna::Reader* InDnaStream, const float* InHeadMeshVertexPositions, const float* InTeethMeshVertexPositions, const float* InEyeLeftMeshVertexPositions, const float* InEyeRightMeshVertexPositions, dna::Writer* OutDnaStream);` — Update the joints and mesh assets using target head mesh vertex positions. @param[in] InDnaStream  Input DNA stream. @param[in] InHeadMeshVertexPositions  Input target vertex positions - Head mesh vertices - as numVertices x 3 in column major order. @param[out] OutDnaStream  Updated dna stream. @returns True if DNA update was successful.
- L93 _public prototype_ `bool RefineRig(dna::Reader* InDnaStream, std::map<std::string, const float*> InVertexPositions, dna::Writer* OutDnaStream, std::map<std::string, std::tuple<std::string, std::vector<int>, std::vector<std::vector<float>>>>& OutDeltaTransferCorrespondanceData);` — Update the joints and mesh assets using target vertex positions. @param[in] InDnaStream  Input DNA stream. @param[in] InVertexPositions  Input target vertex positions - as numVertices x 3 in column major order. @param[out] OutDnaStream  Updated dna stream. @param[out] deltaTransferCorrespondanceData  delta transfer mesh correspondance in neutral. @returns True if DNA update was successful.
- L101 _public prototype_ `bool CheckControlsConfig(const char* InControlsConfigJson);` — Check that the supplied json string for the controls config is valid. @param[in] InControlsConfigJson: the json config defining the set of shapes which help position the teeth without intersecting the mesh @returns true if controls config json is valid, false otherwise
- L112 _public prototype_ `bool RefineTeethPlacement(dna::Reader* InDnaStream, dna::Reader* InRefDnaStream, const char* InControlsConfigJson, dna::Writer* OutDnaStream);` — Optimize and update the teeth position in the rig based on the input reference rig. @param[in] InDnaStream  Input DNA stream. @param[in] InRefDnaStream  Input referent rig DNA stream. @param[in] InControlsConfigJson  Contains the Json for the controls config @param[out] OutDnaStream  Updated dna stream. @returns True if DNA update was successful.
- L124 _public prototype_ `bool TransformRigOrigin(dna::Reader* InDnaStream, const float* InTransformMatrix, dna::Writer* OutDnaStream);` — Transform the rig with 4x4 transform matrix. @param[in] InDnaStream  Input DNA stream. @param[in] InTransformMatrix  Input 4x4 transformation matrix in column major order. @param[out] OutDnaStream  Updated dna stream. @returns True if DNA update was successful.
- L134 _public prototype_ `bool ScaleRig(dna::Reader* InDnaStream, const float InScale, const float* InScalingPivot, dna::Writer* OutDnaStream);` — Scale the rig with scale parameter and scaling pivot. @param[in] InDnaStream  Input DNA stream. @param[in] InScale  Input scale parameter. @param[in] InScaingPivot Input 3D vector representing scaling pivot point. @param[out] OutDnaStream  Updated dna stream. @returns True if DNA update was successful.
- L145 _public prototype_ `bool ScaleAndTransformRig(dna::Reader* InDnaStream, const float* InTransformMatrix, const float InScale, const float* InScalingPivot, dna::Writer* OutDnaStream);` — Apply transform and scale to the rig with 4x4 transform, scale parameter and scaling pivot. @param[in] InDnaStream  Input DNA stream. @param[in] InTransformMatrix  Input 4x4 transformation matrix in column major order. @param[in] InScale  Input scale parameter. @param[in] InScaingPivot Input 3D vector representing scaling pivot point. @param[out] OutDnaStream  Updated dna stream. @returns True if DNA update was successful.
- L160 _public prototype_ `bool ApplyDNA(dna::Reader* InDna, dna::Reader* InDeltaDna, dna::Writer* OutFinalDna, const std::vector<float>& InMask = {});` — Applies delta dna to existing DNA and stores result in InOutDna. [in] InDna input DNA stream. [in] InDeltaDna delta dna. [out] OutFinalDna - final DNA. [in] InMask optional mask to multiply delta before applying. Default value should be used. @returns True if operation was successful, False otherwise.
- L174 _public prototype_ `bool GenerateDeltaDNA(dna::Reader* InFromDna, dna::Reader* InToDna, dna::Writer* OutDeltaDna, const std::vector<float>& InMask = {});` — Generates delta dna as InToDna - InFromDna and stores result in OutDeltaDna. [in] InFromDna input DNA stream - subtrahend. [in] InToDna input DNA stream - minuend. [out] OutFinalDna - deltaDNA [in] InMask optional mask to multiply delta before applying. Default value should be used. @returns True if operation was successful, False otherwise.
- L185 _public prototype_ `bool SetDrivingMeshNames(const std::vector<std::string>& InDrivingMeshNames);` — Set the mesh names from the dna file used as main reference for rig refinement. [in] InDrivingMeshNames input vector of mesh names (corresponding to naming convention in dna file) @returns True if operation was successful, False otherwise.
- L193 _public prototype_ `bool SetInactiveJointNames(const std::vector<std::string>& InInactiveJointNames);` — Set the joint names from the dna file which can only be transformed with global rigid transformation. [in] InInactiveJointNames input vector of joint names (corresponding to naming convention in dna file) @returns True if operation was successful, False otherwise.
- L202 _public prototype_ `bool SetMeshCorrespondance(const std::map<std::string, std::vector<std::string>>& InDrivenMeshNames, RefinementMeshCorrespondenceType InCorrespondanceType);` — Set the relationship between other meshes in the rig with the main reference meshes. [in] InDrivenMeshNames input map of main mesh names as keys and vector of dependent mesh names (corresponding to naming convention in dna file) [in] InCorrespondanceType type of the mesh correspondance @returns True if operation was successful, False otherwise.
- L210 _public prototype_ `bool SetDrivenJointNames(const std::map<std::string, std::vector<std::string>>& InDrivenJointNames);` — Set the relationship between joints in the rig with the main reference meshes. [in] InDrivenJointNames input map of main mesh names as keys and vector of joint names (corresponding to naming convention in dna file) @returns True if operation was successful, False otherwise.
- L218 _public prototype_ `bool SetOptimizationJointNames(const std::vector<std::string>& OptimizationJointNames);` — Set the joint names from the dna file which will be placed based on the sphere optimization. [in] InOptimizationJointNames input vector of joint names (corresponding to naming convention in dna file) @returns True if operation was successful, False otherwise.
- L226 _public prototype_ `bool SetDependentJointNames(const std::map<std::string, std::vector<std::string>>& InDependentJointNames);` — Set the relationship between joints in the rig with the same position and behavior. [in] InDependentJointNames input map of main mesh names as keys and vector of joint names (corresponding to naming convention in dna file) @returns True if operation was successful, False otherwise.
- L230 _private member_ `Private* m;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dna`
- L19 _namespace_ `namespace TITAN_API_NAMESPACE`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/api/Common.h` (Private)


#### Free symbols / members of external scopes

- L9 _macro_ `#define TITAN_RESET_ERROR if (!sc::StatusProvider::isOk()) sc::StatusProvider::set({ 0, "" })`
- L10 _macro_ `#define TITAN_SET_ERROR(errorCode, message) sc::StatusProvider::set({ errorCode, message })`
- L12 _macro_ `#define TITAN_CHECK_OR_RETURN(condition, returnValue, ...) if (!(condition)) { \`
- L17 _macro_ `#define TITAN_HANDLE_EXCEPTION(...) { \`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/api/Defs.h` (Private)


#### Free symbols / members of external scopes

- L10 _macro_ `#define TITAN_NAMESPACE epic::nls`
- L14 _macro_ `#define TITAN_API_NAMESPACE titan::api`
- L18 _macro_ `#define TITAN_API`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/api/EvaluateRigAPI.h` (Private)


#### class `TITAN_API_NAMESPACE::EvaluateRigAPI`  
`class EvaluateRigAPI`  
_L25-101_
- L28 _public prototype_ `EvaluateRigAPI();`
- L29 _public prototype_ `~EvaluateRigAPI();`
- L30 _public prototype_ `EvaluateRigAPI(EvaluateRigAPI&&) = delete;`
- L31 _public prototype_ `EvaluateRigAPI(const EvaluateRigAPI&) = delete;`
- L32 _public prototype_ `EvaluateRigAPI& operator=(EvaluateRigAPI&&) = delete;`
- L33 _public prototype_ `EvaluateRigAPI& operator=(const EvaluateRigAPI&) = delete;`
- L41 _public prototype_ `bool LoadDNA(dna::Reader* InDNAStream);` — Load the DNA file. @param[in] InDNAStream  DNA input stream. @returns True if the DNA file could be loaded.
- L48 _public prototype_ `bool IsRigDNASet() const;` — Return whether the rig DNA has been set for the class @returns true if the rig DNA has been set, false otherwise
- L59 _public prototype_ `bool EvaluateRawControls(const std::map<std::string, float>& InControls, const std::vector<int>& InMeshIndices, int InLod, std::vector<Eigen::Matrix<float, 3, -1>>& OutMeshVertices) const;` — Evaluate the supplied map of raw controls, and return the evaluated mesh vertices for the specified mesh indices. Rig must have been set using LoadDNA. @param[in] InControls: a map of raw control name to control value. Only valid controls will be set, and any controls not set will be set to 0. Control names should use the control names used in the DNA rather than those used in the animation sequence ie CTRL_expressions. rather than CTRL_expressions_ @param[in] InMeshIndices: an array of mesh indices for which we want to evaluate the vertices. Mesh Indices must be in the range 0-GetNumMeshes()-1 @param[in] InLod: the lod to evaluate the mesh vertices for @param[out] OutMeshVertices: an array of array of vector. Each array contains the evaluated vertices for the specified mesh index. @returns true if evaluated successfully, false otherwise
- L66 _public prototype_ `bool GetNumMeshes(int& OutNumMeshes) const;` — Get the number of meshes for the rig DNA. Rig must have been set using LoadDNA. @param[out] OutNumMeshes: contains the number of meshes for the rig DNA. @returns true if evaluated successfully, false otherwise
- L74 _public prototype_ `bool GetMeshIndex(const std::string& InMeshName, int& OutMeshIndex) const;` — Get the mesh index for the specified mesh name for the rig DNA. Rig must have been set using LoadDNA. @param[in] InMeshName: the mesh name. Must be a valid mesh name for the rig. @param[out] OutMeshIndex: contains the corresponding mesh index for the mesh name. @returns true if evaluated successfully, false otherwise
- L82 _public prototype_ `bool GetNumLODs(int& OutNumLODs) const;` — Get the number of lods for the rig DNA. Rig must have been set using LoadDNA. @param[out] OutNumLODs: contains the number of lods for the rig DNA. @returns true if evaluated successfully, false otherwise
- L89 _public prototype_ `bool GetRawControlNames(std::vector<std::string>& OutRawControlNames)const;` — Get the raw control names for the rig DNA. Rig must have been set using LoadDNA. @param[out] OutRawControlNames: contains the control names @returns true if evaluated successfully, false otherwise
- L96 _public prototype_ `bool GetMeshNames(std::vector<std::string>& OutMeshNames)const;` — Get the mesh names for the rig DNA. Rig must have been set using LoadDNA. @param[out] OutMeshNames: contains the mesh names @returns true if evaluated successfully, false otherwise
- L100 _private member_ `Private* m{};`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace dna`
- L21 _namespace_ `namespace TITAN_API_NAMESPACE`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/api/Internals/ActorCreationUtils.h` (Private)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace TITAN_API_NAMESPACE`
- L20 _prototype_ `MultiCameraSetup<float> ScaledCameras(const MultiCameraSetup<float>& cameras, float scale);` (scope `TITAN_API_NAMESPACE`)
- L22 _prototype_ `std::vector<MultiCameraSetup<float>> ScaledCamerasPerFrame(const MultiCameraSetup<float>& cameras, const std::vector<float>& scales);` (scope `TITAN_API_NAMESPACE`)
- L24 _prototype_ `std::pair<std::vector<Eigen::VectorX<float>>, std::vector<std::shared_ptr<const Mesh<float>>>> CollectDepthmapsAsMeshes( const std::vector<std::shared_ptr<FrameInputData>>& frameData);` (scope `TITAN_API_NAMESPACE`)
- L27 _prototype_ `std::pair<std::vector<Eigen::VectorX<float>>, std::vector<std::shared_ptr<const Mesh<float>>>> CollectMeshes( const std::vector<std::shared_ptr<FrameInputData>>& frameData, std::vector<float> scale);` (scope `TITAN_API_NAMESPACE`)
- L31 _prototype_ `std::pair<LandmarkInstance<float, 2>, Camera<float>> Extract2DLandmarksForCamera(const std::shared_ptr<FrameInputData>& frameData, const MultiCameraSetup<float>& cameras, const std::string& cameraName);` (scope `TITAN_API_NAMESPACE`)
- L35 _prototype_ `std::vector<std::vector<std::pair<LandmarkInstance<float, 2>, Camera<float>>>> Collect2DLandmarks(const std::vector<std::shared_ptr<FrameInputData>>& frameData, const MultiCameraSetup<float>& cameras);` (scope `TITAN_API_NAMESPACE`)
- L38 _prototype_ `std::vector<std::vector<std::pair<LandmarkInstance<float, 2>, Camera<float>>>> Collect2DLandmarks(const std::vector<std::shared_ptr<FrameInputData>>& frameData, const std::vector<MultiCameraSetup<float>>& camerasPerFrame);` (scope `TITAN_API_NAMESPACE`)
- L41 _prototype_ `std::vector<LandmarkInstance<float, 3>> Collect3DLandmarks(const std::vector<std::shared_ptr<FrameInputData>>& frameData);` (scope `TITAN_API_NAMESPACE`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/api/Internals/ActorRefinementUtils.h` (Private)


#### enum `TITAN_API_NAMESPACE::Operation`  
`enum class Operation`  
_L20-24_
- L22 _public enumerator_ `Add = 0`
- L23 _public enumerator_ `Substract`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dna`
- L17 _namespace_ `namespace TITAN_API_NAMESPACE`
- L26 _prototype_ `void ApplyDNAInternal(dna::Reader* dna1, dna::Reader* dna2, dna::Writer* resultDna, Operation operation, const std::vector<float>& mask);` (scope `TITAN_API_NAMESPACE`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/api/Internals/FrameInputData.h` (Private)


#### enum `TITAN_API_NAMESPACE::InputDataType`  
`enum class InputDataType`  
_L16-21_
- L18 _public enumerator_ `DEPTHS`
- L19 _public enumerator_ `SCAN`
- L20 _public enumerator_ `NONE`

#### struct `TITAN_API_NAMESPACE::GeometryData`  
`struct GeometryData`  
_L23-27_
- L25 _public member_ `std::shared_ptr<const Mesh<float>> mesh;`
- L26 _public member_ `Eigen::VectorXf weights;`

#### class `TITAN_API_NAMESPACE::FrameInputData`  
`class FrameInputData`  
_L29-59_
- L32 _public prototype_ `FrameInputData(const std::map<std::string, std::shared_ptr<const LandmarkInstance<float, 2>>>& landmarks, const std::map<std::string, GeometryData>& depthmapsData);`
- L35 _public prototype_ `FrameInputData(const std::map<std::string, std::shared_ptr<const LandmarkInstance<float, 2>>>& landmarks2d, const std::shared_ptr<const LandmarkInstance<float, 3>>& landmarks3d, const GeometryData& scanData);`
- L38 _public prototype_ `~FrameInputData() = default;`
- L40 _public prototype_ `const std::map<std::string, std::shared_ptr<const LandmarkInstance<float, 2>>>& LandmarksPerCamera() const;`
- L42 _public prototype_ `const std::shared_ptr<const LandmarkInstance<float, 3>>& Landmarks3D() const;`
- L44 _public prototype_ `const GeometryData& Scan() const;`
- L46 _public prototype_ `const std::map<std::string, GeometryData>& DepthmapsAsMeshes() const;`
- L48 _public prototype_ `void UpdateScanMask(const Eigen::VectorXf& newWeights);`
- L50 _public prototype_ `void UpdateDepthmapsMask(const std::map<std::string, Eigen::VectorXf>& vectorOfNewWeights);`
- L52 _public prototype_ `void Clear();`
- L55 _private member_ `std::map<std::string, std::shared_ptr<const LandmarkInstance<float, 2>>> m_perCameraLandmarkData;`
- L56 _private member_ `std::shared_ptr<const LandmarkInstance<float, 3>> m_landmark3Ddata;`
- L57 _private member_ `GeometryData m_scan;`
- L58 _private member_ `std::map<std::string, GeometryData> m_depthmapsAsMeshes;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TITAN_API_NAMESPACE`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/api/Internals/LandmarkInstanceUtils.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TITAN_API_NAMESPACE`
- L16 _prototype_ `std::shared_ptr<const TITAN_NAMESPACE::LandmarkInstance<float, 2>> CreateLandmarkInstanceForCamera(const std::map<std::string, FaceTrackingLandmarkData>& perCameraLandmarkData, const std::map<std::string, std::vector<std::string>>& curvesToMerge, const TITAN_NAMESPACE::MetaShapeCamera<float>& camera);` (scope `TITAN_API_NAMESPACE`)
- L20 _prototype_ `std::shared_ptr<const TITAN_NAMESPACE::LandmarkInstance<float, 3>> Create3dLandmarkInstance(const std::map<std::string, const FaceTrackingLandmarkData>& landmarkData, const std::map<std::string, std::vector<std::string>>& curvesToMerge);` (scope `TITAN_API_NAMESPACE`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/api/Internals/OpenCVCamera2MetaShapeCamera.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TITAN_API_NAMESPACE`
- L14 _function_ `template <class T, class C = float> TITAN_NAMESPACE::MetaShapeCamera<T> OpenCVCamera2MetaShapeCamera(const char* InCameraName, const OpenCVCameraTemplate<C>& InCameraParameters)` (scope `TITAN_API_NAMESPACE`)
- L36 _function_ `template <class T, class C = float> static std::pair<std::string, OpenCVCameraTemplate<C>> MetaShape2OpenCVCamera(const TITAN_NAMESPACE::MetaShapeCamera<T>& InCamera)` (scope `TITAN_API_NAMESPACE`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/api/Internals/ReferenceAligner.h` (Private)


#### class `TITAN_API_NAMESPACE::ReferenceAligner`  
`class ReferenceAligner`  
_L16-35_
- L19 _public prototype_ `ReferenceAligner(Mesh<float> reference, BarycentricCoordinates<float> fr, BarycentricCoordinates<float> rr, BarycentricCoordinates<float> fl, BarycentricCoordinates<float> rl);`
- L25 _public prototype_ `~ReferenceAligner() = default;`
- L27 _public prototype_ `std::pair<float, Affine<float, 3, 3>> EstimateScaleAndRigid(const Eigen::Matrix3Xf& vertices) const;`
- L30 _private member_ `Mesh<float> m_reference;`
- L31 _private member_ `BarycentricCoordinates<float> m_fr;`
- L32 _private member_ `BarycentricCoordinates<float> m_rr;`
- L33 _private member_ `BarycentricCoordinates<float> m_fl;`
- L34 _private member_ `BarycentricCoordinates<float> m_rl;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TITAN_API_NAMESPACE`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/api/LandmarkData.h` (Private)


#### class `TITAN_API_NAMESPACE::FaceTrackingLandmarkData`  
`class FaceTrackingLandmarkData`  
_L17-40_
- desc: Simple class to pass landmark data to FaceTrackingAPI and ActCreationAPI.
- L20 _public prototype_ `FaceTrackingLandmarkData();`
- L21 _public prototype_ `~FaceTrackingLandmarkData();`
- L22 _public prototype_ `FaceTrackingLandmarkData(const FaceTrackingLandmarkData& other);`
- L23 _public prototype_ `FaceTrackingLandmarkData& operator=(const FaceTrackingLandmarkData& other);`
- L24 _public prototype_ `void swap(FaceTrackingLandmarkData&);`
- L25 _public prototype_ `FaceTrackingLandmarkData(FaceTrackingLandmarkData&&);`
- L26 _public prototype_ `FaceTrackingLandmarkData& operator=(FaceTrackingLandmarkData&&);`
- L28 _public prototype_ `const std::vector<float>& ConfidenceData() const;`
- L29 _public prototype_ `const std::vector<float>& PointsData() const;`
- L31 _public prototype_ `int32_t NumPoints() const;`
- L32 _public prototype_ `int32_t PointsDimension() const;`
- L35 _public prototype_ `static FaceTrackingLandmarkData Create(const float* PointsData, const float* ConfidenceData, int32_t NumPoints, int32_t Dim);` — Create FaceTrackingLandmarkData from a float array and optional confidence data.
- L39 _private member_ `Private* m{};`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TITAN_API_NAMESPACE`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/api/MeshInputData.h` (Private)


#### struct `TITAN_API_NAMESPACE::MeshInputData`  
`struct MeshInputData`  
_L10-16_
- L12 _public member_ `const int m_numTriangles;`
- L13 _public member_ `const int* m_triangles;`
- L14 _public member_ `const int m_numVertices;`
- L15 _public member_ `const float* m_vertices;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TITAN_API_NAMESPACE`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/api/MetaHumanCreatorAPI.h` (Private)


#### enum `TITAN_API_NAMESPACE::AlignmentOptions`  
`enum class AlignmentOptions`  
_L36-43_
- L38 _public enumerator_ `None`
- L39 _public enumerator_ `Translation`
- L40 _public enumerator_ `RotationTranslation`
- L41 _public enumerator_ `ScalingTranslation`
- L42 _public enumerator_ `ScalingRotationTranslation`

#### enum `TITAN_API_NAMESPACE::HeadFitToTargetMeshes`  
`enum class HeadFitToTargetMeshes`  
_L45-51_
- L47 _public enumerator_ `Head`
- L48 _public enumerator_ `LeftEye`
- L49 _public enumerator_ `RightEye`
- L50 _public enumerator_ `Teeth`

#### class `TITAN_API_NAMESPACE::MetaHumanCreatorAPI`  
`class MetaHumanCreatorAPI : public std::enable_shared_from_this<MetaHumanCreatorAPI>`  
_L53-168_
- inherits: `std::enable_shared_from_this<MetaHumanCreatorAPI>`
- L61 _public prototype_ `~MetaHumanCreatorAPI();`
- L62 _public prototype_ `MetaHumanCreatorAPI(MetaHumanCreatorAPI&&) = delete;`
- L63 _public prototype_ `MetaHumanCreatorAPI(const MetaHumanCreatorAPI&) = delete;`
- L64 _public prototype_ `MetaHumanCreatorAPI& operator=(MetaHumanCreatorAPI&&) = delete;`
- L65 _public prototype_ `MetaHumanCreatorAPI& operator=(const MetaHumanCreatorAPI&) = delete;`
- L67 _public prototype_ `static std::shared_ptr<MetaHumanCreatorAPI> CreateMHCApi( dna::Reader* InDnaReader, const char* InMhcDataPath, int numThreads = -1, dna::Reader* InBodyDnaReader = nullptr);`
- L73 _public prototype_ `void SetNumThreads(int numThreads);`
- L74 _public prototype_ `int GetNumThreads() const;`
- L76 _public prototype_ `std::shared_ptr<State> CreateState() const;`
- L78 _public prototype_ `const std::vector<int> & GetVertexSymmetries() const;`
- L80 _public prototype_ `const std::vector<std::string> & GetExpressionNames() const;`
- L83 _public prototype_ `const std::vector<std::string>& GetRegionNames() const;` — @returns all region names
- L85 _public prototype_ `int NumVertices() const;`
- L88 _public prototype_ `Eigen::Matrix<int, 3, -1> GetLod0TriangleIndices() const;` — @returns LOD 0 triangle indices
- L91 _public prototype_ `std::shared_ptr<TITAN_NAMESPACE::PatchBlendModel<float>> GetFacePatchBlendModel() const;` — @returns the face-only PatchBlendModel (reduced to face mesh vertices only, no teeth/eyes)
- L94 _public prototype_ `std::shared_ptr<TITAN_NAMESPACE::MeshLandmarks<float>> GetFaceTrackingLandmarks() const;` — @returns the landmarks used for face landmark tracking
- L99 _public prototype_ `const TITAN_NAMESPACE::VertexWeights<float>* GetMask(const std::string& name) const;` — @returns the named vertex-weight mask loaded from the MHC config (e.g. "body_blend"), or nullptr if not present. Indexed against the face patch blend model's vertex layout (shares indices with the combined BSE mesh).
- L101 _public prototype_ `bool Evaluate(const State& State, float* OutVertices) const;`
- L104 _public prototype_ `bool Evaluate(const State& State, Eigen::Matrix<float, 3, -1>& OutVertices) const;` — Evaluates the state and sets all joints and vertices that are defined by the dna
- L107 _public prototype_ `bool EvaluateNormals(const State& State, const Eigen::Matrix<float, 3, -1>& InVertices, Eigen::Matrix<float, 3, -1>& OutNormals, const std::vector<Eigen::Ref<const Eigen::Matrix<float, 3, -1>>>& InBodyNormals) const;` — Computes the normals for all meshes and stores it to @p OutNormals
- L109 _public prototype_ `bool GetVertex(const float* InVertices, int DNAMeshIndex, int DNAVertexIndex, float OutVertexXYZ[3]) const;`
- L112 _public prototype_ `bool GetMeshVertices(const float* InVertices, int DNAMeshIndex, Eigen::Matrix<float, 3, -1>& OutVertices) const;` — Gets the mesh vertices @p OutVertices based on @p InVertices (as calculated by @see Evaluate())
- L115 _public prototype_ `bool GetBindPose(const float* InVertices, Eigen::Matrix<float, 3, -1>& OutBindPose) const;` — Gets the joint positions @p OutBindPose based on @p InVertices (as calculated by @see Evaluate())
- L118 _public prototype_ `bool GetParameters(const State& State, Eigen::VectorXf& OutParameters) const;` — Gets the state parameters @p OutParameters based on @p State
- L121 _public prototype_ `bool SetParameters(State& State, const Eigen::VectorXf& InParameters) const;` — Sets the state parameters @p InParameters into @p State
- L124 _public prototype_ `bool GetModelIdentifier(const State& State, std::string& OutIdentifier) const;` — Gets the model identifier
- L127 _public prototype_ `std::vector<std::string> GetPresetNames() const;` — @returns all available presets
- L130 _public prototype_ `bool AddPreset(const std::string& PresetName, std::shared_ptr<const State>& State);` — adds state @p State as preset with name @p PresetName
- L133 _public prototype_ `bool RemovePreset(const std::string& PresetName);` — remove preset @p PresetName from the list
- L135 _public prototype_ `int NumHFVariants() const;`
- L138 _public prototype_ `std::vector<std::string> GetVariantTypes() const;` — @return types of variants e.g. eyelashes or teeth
- L141 _public prototype_ `std::vector<std::string> GetVariantNames(const std::string& variantType) const;` — @return get name of variants for a certain variant type
- L144 _public prototype_ `bool StateToDna(const State& State, dna::Writer* InOutDnaWriter) const;` — Convert the current face state to DNA. Note that this does NOT currently include the updated skinning weights which should be generated post auto-rigging using func UpdateFaceSkinningWeightsFromBody
- L146 _public prototype_ `bool CopyBodyJointsToFace(const dna::Reader* InBodyDnaReader, const dna::Reader* InFaceDnaReader, dna::Writer* InOutDnaWriter, bool bUpdateDescendentJoints) const;`
- L148 _public prototype_ `bool AddRbfControlsFromReference(dna::Reader* InReferenceDnaReader, dna::Reader* InTargetDnaReader, dna::Writer* InOutDnaWriter) const;`
- L152 _public prototype_ `bool UpdateFaceSkinWeightsFromBody(const std::vector<std::pair<int, std::vector<Eigen::Triplet<float>>>>& InCombinedBodySkinWeights, const dna::Reader* InFaceDnaReader, dna::Writer* InOutDnaWriter) const;` — Update the face skinning weights from the combined body, such that the skinning weights exactly match those of the body at the neck seam and are blended between body and head in the neck region; weights should be provided for each lod as a pair of number of combined model vertices at that lod and triplets from a sparse joint influence matrix
- L155 _public prototype_ `int SelectVertex(const Eigen::Matrix<float, 3, -1>& Vertices, const Eigen::Vector3f& Origin, const Eigen::Vector3f& Direction) const;` — Selects a vertex from @p Vertices based on the ray defined by @p Origin and @p Direction.
- L158 _public prototype_ `int GetNeckRegionIndex() const;` — @returns the neck region index
- L161 _public prototype_ `int GetNumLOD0MeshVertices(HeadFitToTargetMeshes InMeshType) const;` — Get the number of vertices for the supplied mesh type at LOD 0
- L164 _private prototype_ `MetaHumanCreatorAPI();`
- L167 _private member_ `Private* m {};`

#### class `TITAN_API_NAMESPACE::MetaHumanCreatorAPI::State`  
`class MetaHumanCreatorAPI::State`  
_L170-415_
- L181 _public prototype_ `~State();`
- L182 _public prototype_ `State(State&&) = delete;`
- L183 _public prototype_ `State& operator=(State&&) = delete;`
- L184 _public prototype_ `State& operator=(const State&) = delete;`
- L186 _public prototype_ `std::shared_ptr<State> Clone() const;`
- L188 _public prototype_ `int NumGizmos() const;`
- L189 _public prototype_ `bool EvaluateGizmos(const float* InVertices, float* OutGizmos) const;`
- L191 _public prototype_ `int NumLandmarks() const;`
- L192 _public prototype_ `bool EvaluateLandmarks(const float* InVertices, float* OutLandmarks) const;`
- L195 _public prototype_ `bool UpdateDmt();` — Update the underlying dmt model
- L198 _public prototype_ `bool Reset(bool resetBody = false);` — Reset the model to the mean
- L208 _public prototype_ `bool ResetRegion(int GizmoIndex, float Alpha, const BlendOptions& InBlendOptions);` — Reset a region using @p alpha as a blend factor (1.0 will do a full reset). @p Type defines whether proportions, features, or both are reset.
- L214 _public prototype_ `bool Blend(int GizmoIndex, const std::vector<std::pair<float, const State*>>& States, const BlendOptions& InBlendOptions);` — Blend region @p GizmoIndex (all regions besides neck if -1) to @p States. @p Type defines whether proportions, features, or both are blended.
- L216 _public prototype_ `bool Randomize(float magnitude);`
- L218 _public prototype_ `bool SelectPreset(int GizmoIndex, const std::string& PresetName, const BlendOptions& InBlendOptions);`
- L220 _public prototype_ `bool BlendPresets(int GizmoIndex, const std::vector<std::pair<float, std::string>>& alphaAndPresetNames, const BlendOptions& InBlendOptions);`
- L247 _public prototype_ `bool FitToTarget(const float* InVertices, int NumVertices);`
- L249 _public prototype_ `bool FitToTarget(const std::map<int, Eigen::Ref<const Eigen::Matrix<float, 3, -1>>>& InVertices, const FitToTargetOptions& options, FitToTargetResult* result = nullptr, bool useStabModel = true);`
- L251 _public prototype_ `bool FitToTarget(const dna::Reader* InDnaReader, const FitToTargetOptions& option, FitToTargetResult* result = nullptr);`
- L253 _public prototype_ `bool FitToTarget(const Eigen::Matrix<float, 3, -1>& InBodyVertices, const FitToTargetOptions& options);`
- L256 _public prototype_ `bool GetHeadPartVerticesFromBody(const Eigen::Matrix<float, 3, -1>& InBodyVertices, Eigen::Matrix<float, 3, -1>& OutHeadVertices) const;` — Extract the head-mesh vertex block from a combined body vertex array.
- L259 _public prototype_ `bool AdaptNeck();` — Adapt the neck by blending the vertex delta to zero. Does not do anything if the vertex delta of the neck seam is alerady zero.
- L276 _public prototype_ `bool CalculateM2MHDelta(const Eigen::Matrix<float, 3, -1>& targetFaceVertices);` — Capture a runtime residual delta between @p targetFaceVertices and the face mesh the current state evaluates to, so subsequent Evaluate() calls land on the target. @param targetFaceVertices  3 x numFaceVertices, in canonical face DNA topology, in the same scaled output space that Evaluate produces. Caller is responsible for slicing combined-body topology down to the face range before calling. Subsequent Evaluate() calls add @c scale * delta on top of the regular pipeline. Calling Calculate again replaces (does not accumulate) the delta. The delta is captured against the *current* face state - if the caller mutates face state afterwards the delta becomes stale until Reset / Calculate is called again. Runtime-only - not serialized.
- L279 _public prototype_ `bool CalculateM2MHDeltaFromBodyVertices(const Eigen::Matrix<float, 3, -1>& InBodyVertices);` — Calculate targetFaceVertices from body vertices and calculates M2MH Delta
- L282 _public prototype_ `void ResetM2MHDelta();` — Clear the M2MH residual delta. Does not change face PCA / per-patch state.
- L285 _public prototype_ `void SetM2MHDeltaScale(float scale);` — Runtime-only scale applied to the M2MH delta during Evaluate. Not serialized.
- L288 _public prototype_ `float GetM2MHDeltaScale() const;` — Get scale applied to the M2MH delta.
- L296 _public prototype_ `void SetEvaluateBodyState(bool enabled);` — Runtime toggle: when @p enabled is false, UpdateCombinedState skips the bodyState merge so combinedState mirrors faceState (face-only render). Use during M2MH / preview flows where the body-side contribution should be temporarily ignored. Defaults to true; not serialized.
- L298 _public prototype_ `bool HasGizmo(int GizmoIndex) const;`
- L307 _public prototype_ `bool TranslateGizmo(int GizmoIndex, const float DeltaXYZ[3], bool bInSymmetric);`
- L308 _public prototype_ `bool TranslateGizmo(int GizmoIndex, const float DeltaXYZ[3], const TranslateGizmoOptions& InTranslateGizmoOptions);`
- L316 _public prototype_ `bool SetGizmoPosition(int InGizmoIndex, const float InPosition[3], const GizmoPositionOptions& InGizmoPositionOptions);`
- L317 _public prototype_ `bool GetGizmoPosition(int InGizmoIndex, float OutPosition[3]) const;`
- L323 _public prototype_ `bool GetGizmoPositionBounds(int InGizmoIndex, float OutMinPosition[3], float OutMaxPosition[3], float InBBoxReduction, bool bInExpandToCurrent) const;` — Get the bounds of the gizmo @param [in] InBBoxReduction      How much to reduce the bounding box ratio. @param [in] bInExpandToCurrent   Whether to expand the bounds to include the current gizmo position
- L330 _public prototype_ `bool SetGizmoRotation(int GizmoIndex, const float Eulers[3], bool bInSymmetric);`
- L331 _public prototype_ `bool SetGizmoRotation(int GizmoIndex, const float Eulers[3], const GizmoRotationOptions& InGizmoRotationOptions);`
- L332 _public prototype_ `bool GetGizmoRotation(int GizmoIndex, float Euler[3]) const;`
- L333 _public prototype_ `bool GetGizmoRotationBounds(int InGizmoIndex, float OutMinEuler[3], float OutMaxEuler[3], bool bInExpandToCurrent) const;`
- L340 _public prototype_ `bool SetGizmoScale(int GizmoIndex, float scale, bool bInSymmetric);`
- L341 _public prototype_ `bool SetGizmoScale(int GizmoIndex, float scale, const GizmoScalingOptions& InGizmoScalingOptions);`
- L342 _public prototype_ `bool GetGizmoScale(int GizmoIndex, float& scale) const;`
- L343 _public prototype_ `bool GetGizmoScaleBounds(int GizmoIndex, float& OutMinScale, float& OutMaxScale, bool bInExpandToCurrent) const;`
- L345 _public prototype_ `bool SetGlobalScale(float scale);`
- L347 _public prototype_ `bool GetGlobalScale(float& scale) const;`
- L349 _public prototype_ `bool SetFaceScale(float scale);`
- L351 _public prototype_ `bool GetFaceScale(float& scale) const;`
- L353 _public prototype_ `bool TranslateLandmark(int LandmarkIndex, const float DeltaXYZ[3], bool bInSymmetric);`
- L355 _public prototype_ `bool AddLandmark(int VertexIndex);`
- L357 _public prototype_ `bool HasLandmark(int VertexIndex) const;`
- L359 _public prototype_ `bool RemoveLandmark(int LandmarkIndex);`
- L361 _public prototype_ `int SelectFaceVertex(const Eigen::Vector3f& InOriginXYZ, const Eigen::Vector3f& InDirectionXYZ, Eigen::Vector3f& OutVertex, Eigen::Vector3f& OutNormal) const;`
- L367 _public prototype_ `bool Serialize(std::string& OutArchive) const;` — Serialize the state to a string. IMPORTANT: variants, expressions, HF variant, face scale and global scale are not currently serialized; we may address this in future
- L373 _public prototype_ `bool Serialize(trio::BoundedIOStream* OutputStream) const;` — Serialize the state to a stream. IMPORTANT: variants, expressions, HF variant, face scale and global scale are not currently serialized; we may address this in future
- L375 _public prototype_ `bool Deserialize(const std::string& InArchive);`
- L376 _public prototype_ `bool Deserialize(trio::BoundedIOStream* InputStream);`
- L378 _public prototype_ `const std::shared_ptr<const Settings>& GetSettings() const;`
- L380 _public prototype_ `void SetSettings(const std::shared_ptr<Settings>& settings);`
- L382 _public prototype_ `bool SetExpressionActivations(const std::map<std::string, float>& expressionActivations);`
- L384 _public prototype_ `bool ResetNeckExclusionMask();`
- L387 _public prototype_ `bool SetBodyJointsAndBodyFaceVertices(const float* InBodyBindPoses, const float* InBodyVertices);` — Update the face state base on the body bind pose and body "face" vertices (face vertices in the combined body/face model)
- L390 _public prototype_ `bool SetHFVariant(int HFIndex);` — Set high frequency variant @p HFIndex. Disable HF if @p HFIndex < 0
- L391 _public prototype_ `int GetHFVariant() const;`
- L394 _public prototype_ `bool SetVariant(const std::string& VariantType, const float* VariantValues);` — Set values for variant @p VariantType. Set VariantValues to nullptr to clear the variants.
- L396 _public prototype_ `bool GetVariant(const std::string& VariantType, float* VariantValues) const;`
- L399 _public prototype_ `bool Calibrate();` — Calibrate expressions based on the Neutral state
- L402 _public prototype_ `bool DumpDataForAR(const std::string& directoryName) const;` — Dump all data required for auto rigging to local directory @p directoryName
- L404 _public prototype_ `int GetSerializationVersion() const;`
- L407 _private prototype_ `State();`
- L408 _private prototype_ `State(const State&);`
- L411 _private member_ `Private* m {};`

#### enum `TITAN_API_NAMESPACE::MetaHumanCreatorAPI::State::FaceAttribute`  
`enum class FaceAttribute`  
_L173-178_
- L175 _public enumerator_ `Proportions`
- L176 _public enumerator_ `Features`
- L177 _public enumerator_ `Both`

#### struct `TITAN_API_NAMESPACE::MetaHumanCreatorAPI::State::BlendOptions`  
`struct BlendOptions`  
_L200-205_
- L202 _public member_ `FaceAttribute Type = FaceAttribute::Both;`
- L203 _public member_ `bool bBlendSymmetrically { true };`
- L204 _public member_ `bool bBlendRelativeTranslation { false };`

#### struct `TITAN_API_NAMESPACE::MetaHumanCreatorAPI::State::FitToTargetOptions`  
`struct FitToTargetOptions`  
_L222-226_
- L225 _public member_ `AlignmentOptions alignmentOptions { AlignmentOptions::ScalingRotationTranslation };` — alignment when fitting meshes or a dna file

#### struct `TITAN_API_NAMESPACE::MetaHumanCreatorAPI::State::FitToTargetResult`  
`struct FitToTargetResult`  
_L235-239_
- L237 _public member_ `Eigen::Matrix4f transform;`
- L238 _public member_ `float scale;`

#### struct `TITAN_API_NAMESPACE::MetaHumanCreatorAPI::State::TranslateGizmoOptions`  
`struct TranslateGizmoOptions`  
_L300-306_
- L302 _public member_ `bool bSymmetric { true };`
- L303 _public member_ `bool bEnforceBounds { true };`
- L304 _public member_ `float BBoxSoftBound { 0.2f };`
- L305 _public member_ `float BBoxReduction { 0.2f };`

#### struct `TITAN_API_NAMESPACE::MetaHumanCreatorAPI::State::GizmoPositionOptions`  
`struct GizmoPositionOptions`  
_L310-315_
- L312 _public member_ `bool bSymmetric { true };`
- L313 _public member_ `bool bEnforceBounds { true };`
- L314 _public member_ `float BBoxReduction { 0.2f };`

#### struct `TITAN_API_NAMESPACE::MetaHumanCreatorAPI::State::GizmoRotationOptions`  
`struct GizmoRotationOptions`  
_L325-329_
- L327 _public member_ `bool bSymmetric { true };`
- L328 _public member_ `bool bEnforceBounds { true };`

#### struct `TITAN_API_NAMESPACE::MetaHumanCreatorAPI::State::GizmoScalingOptions`  
`struct GizmoScalingOptions`  
_L335-339_
- L337 _public member_ `bool bSymmetric { true };`
- L338 _public member_ `bool bEnforceBounds { true };`

#### class `TITAN_API_NAMESPACE::MetaHumanCreatorAPI::Settings`  
`class MetaHumanCreatorAPI::Settings`  
_L417-499_
- L420 _public prototype_ `Settings();`
- L421 _public prototype_ `~Settings();`
- L422 _public prototype_ `Settings(Settings&&) = delete;`
- L423 _public prototype_ `Settings& operator=(Settings&&) = delete;`
- L424 _public prototype_ `Settings& operator=(const Settings&) = delete;`
- L426 _public prototype_ `std::shared_ptr<Settings> Clone() const;`
- L428 _public prototype_ `float GlobalVertexDeltaScale() const;`
- L429 _public prototype_ `void SetGlobalVertexDeltaScale(float globalVertexDeltaScale);`
- L431 _public prototype_ `float RegionVertexDeltaScale(int patchId) const;`
- L432 _public prototype_ `void SetRegionVertexDeltaScale(int patchId, float vertexDeltaScale);`
- L434 _public prototype_ `bool GenerateAssetsAndEvaluateAllLODs() const;`
- L435 _public prototype_ `void SetGenerateAssetsAndEvaluateAllLODs(bool bGenerateAssetsAndEvaluateAllLODs);`
- L437 _public prototype_ `bool DmtWithSymmetry() const;`
- L438 _public prototype_ `void SetDmtWithSymmetry(bool isDmtWithSymmetry);`
- L440 _public prototype_ `float DmtPcaThreshold() const;`
- L441 _public prototype_ `void SetDmtPcaThreshold(float DmtPcaThreshold);`
- L443 _public prototype_ `float DmtRegularization() const;`
- L444 _public prototype_ `void SetDmtRegularization(float bInDmtRegularization);`
- L446 _public prototype_ `bool DmtStabilizeFixLandmarks() const;`
- L447 _public prototype_ `void SetDmtStabilizeFixLandmarks(bool bInDmtStabilizeFixLandmarks);`
- L449 _public prototype_ `bool LockFaceScale() const;`
- L450 _public prototype_ `void SetLockFaceScale(bool lockFaceScale);`
- L452 _public prototype_ `bool LockBodyFaceState() const;`
- L453 _public prototype_ `void SetLockBodyFaceState(bool lockBodyState);`
- L455 _public prototype_ `bool UpdateBodyJointsInEvaluation() const;`
- L456 _public prototype_ `void SetUpdateBodyJointsInEvaluation(bool updateBodyJoints);`
- L458 _public prototype_ `bool UpdateFaceSurfaceJointsInEvaluation() const;`
- L459 _public prototype_ `void SetUpdateFaceSurfaceJointsInEvaluation(bool updateFaceSurfaceJoints);`
- L461 _public prototype_ `bool UpdateFaceVolumetricJointsInEvaluation() const;`
- L462 _public prototype_ `void SetUpdateFaceVolumetricJointsInEvaluation(bool updateFaceVolumetricJoints);`
- L464 _public prototype_ `bool UpdateBodySurfaceJointsInEvaluation() const;`
- L465 _public prototype_ `void SetUpdateBodySurfaceJointsInEvaluation(bool updateFaceSurfaceJoints);`
- L468 _public prototype_ `bool UseCompatibilityEvaluation() const;` — Used for restoring old states as they were dependent on body state
- L470 _public prototype_ `void SetUseCompatibilityEvaluation(bool useCompatibilityEvaluation);` — Used for restoring old states as they were dependent on body state
- L473 _public prototype_ `bool UseScaleInBodyFit() const;`
- L474 _public prototype_ `void SetUseScaleInBodyFit(bool useScaleInBodyFit);`
- L476 _public prototype_ `float BodyFitRegularization() const;`
- L477 _public prototype_ `void SetBodyFitRegularization(float bodyFitRegularization);`
- L479 _public prototype_ `bool UseCanoncialBodyInEvaluation() const;`
- L480 _public prototype_ `void SetUseCanonicalBodyInEvaluation(bool useCanconicalBodyInEvaluation);`
- L482 _public prototype_ `float GlobalHFScale() const;`
- L483 _public prototype_ `void SetGlobalHFScale(float Scale);`
- L485 _public prototype_ `float RegionHfScale(int patchId) const;`
- L486 _public prototype_ `void SetRegionHfScale(int patchId, float vertexDeltaScale);`
- L488 _public prototype_ `int HFIterations() const;`
- L489 _public prototype_ `void SetHFIterations(int Iterations);`
- L492 _private prototype_ `Settings(const Settings&);`
- L495 _private member_ `Private* m {};`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace dna`
- L21 _namespace_ `namespace trio`
- L26 _namespace_ `namespace TITAN_NAMESPACE`
- L33 _namespace_ `namespace TITAN_API_NAMESPACE`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/api/MetaHumanCreatorBodyAPI.h` (Private)


#### class `TITAN_API_NAMESPACE::MetaHumanCreatorBodyAPI`  
`class MetaHumanCreatorBodyAPI : public std::enable_shared_from_this<MetaHumanCreatorBodyAPI>`  
_L46-337_
- inherits: `std::enable_shared_from_this<MetaHumanCreatorBodyAPI>`
- L59 _public prototype_ `~MetaHumanCreatorBodyAPI();`
- L60 _public prototype_ `MetaHumanCreatorBodyAPI(MetaHumanCreatorBodyAPI&&) = delete;`
- L61 _public prototype_ `MetaHumanCreatorBodyAPI(const MetaHumanCreatorBodyAPI&) = delete;`
- L62 _public prototype_ `MetaHumanCreatorBodyAPI& operator=(MetaHumanCreatorBodyAPI&&) = delete;`
- L63 _public prototype_ `MetaHumanCreatorBodyAPI& operator=(const MetaHumanCreatorBodyAPI&) = delete;`
- L65 _public prototype_ `static std::shared_ptr<MetaHumanCreatorBodyAPI> CreateMHCBodyApi(const dna::Reader* PCABodyModel, dna::Reader* InCombinedBodyArchetypeDnaReader, const std::string& RBFModelPath, const std::string& SkinModelPath, const std::string& CombinedSkinningWeightGenerationConfigPath, const std::string& CombinedLodGenerationConfigPath = {}, const std::string& PhysicsBodiesConfigPath = {}, const std::string& BodyMasksPath = {}, const std::string& RegionLandmarksPath = {}, const std::string& PipelinePresetsPath = {}, std::shared_ptr<TITAN_NAMESPACE::PatchBlendModel<float>> FacePatchBlendModel = nullptr, std::shared_ptr<TITAN_NAMESPACE::MeshLandmarks<float>> FaceTrackingLandmarks = nullptr, int numThreads = -1);`
- L79 _public prototype_ `void SetNumThreads(int numThreads);`
- L80 _public prototype_ `int GetNumThreads() const;`
- L82 _public prototype_ `std::shared_ptr<State> CreateState() const;`
- L84 _public prototype_ `bool GetVertex(int lod, const float* InVertices, int DNAVertexIndex, float OutVertexXYZ[3]) const;`
- L86 _public prototype_ `void Evaluate(State& State) const;`
- L87 _public prototype_ `void EvaluateConstraintRange(const State& state, av::ArrayView<float> MinValues, av::ArrayView<float> MaxValues, bool bScaleWithHeight = false) const;`
- L88 _public prototype_ `void StateToDna(const State& State, dna::Writer* InOutDnaWriter, bool combinedBodyAndFace = false, bool usePosedJoints = false) const;`
- L90 _public prototype_ `void DumpState(const State& State, trio::BoundedIOStream* Stream) const;`
- L91 _public prototype_ `bool RestoreState(trio::BoundedIOStream* Stream, std::shared_ptr<State> OutState) const;`
- L94 _public prototype_ `void AddLegacyBody(const dna::Reader* LegacyBody, const av::StringView& LegacyBodyName);` — Add Legacy body - dna needs to contine the combined body/face model
- L97 _public prototype_ `int NumLegacyBodies() const;` — @returns the number of legacy bodies
- L100 _public prototype_ `const std::string& LegacyBodyName(int LegacyBodyIndex) const;` — @returns the name of legacy body @p LegacyBodyIndex
- L103 _public prototype_ `void SelectLegacyBody(State& State, int LegacyBodyIndex, bool Fit = false) const;` — Update @p State using legacy body at index @p LegacyBodyIndex
- L106 _public prototype_ `int NumLODs() const;` — @returns the number of LODs supported by the API
- L109 _public prototype_ `av::ConstArrayView<int> GetTriangles(int lod) const;` — @returns the triangle indices of LODs supported by the API
- L112 _public prototype_ `int NumPresetBodies() const;` — @returns the number of preset bodies
- L115 _public prototype_ `const std::vector<std::string>& GetPresetNames() const;` — @returns all preset names
- L118 _public prototype_ `const std::string& PresetBodyName(int PresetBodyIndex) const;` — @returns the name of preset body @p PresetBodyIndex
- L121 _public prototype_ `void SelectPresetBody(State& State, int PresetBodyIndex) const;` — Update @p State using preset body at index @p PresetBodyIndex
- L124 _public prototype_ `void GetVertexInfluenceWeights(const State& State, std::vector<TITAN_NAMESPACE::SparseMatrix<float>>& vertexInfluenceWeights) const;` — Calculates the combined body vertex influence weights for the supplied body state at each lod; the body must have a pca skinning model
- L127 _public prototype_ `int NumPhysicsBodyVolumes(const ::std::string& JointName) const;` — @returns the numbers of physics body volumes
- L130 _public prototype_ `bool GetPhysicsBodyBoundingBox(const State& State, const ::std::string& JointName, int BodyVolumeIndex, Eigen::Vector3f& OutCenter, Eigen::Vector3f& OutExtents) const;` — Calculates the physics bounding box for the joint and volume index
- L132 _public prototype_ `int NumJoints() const;`
- L133 _public prototype_ `void GetNeutralJointTransform(const State& State, std::uint16_t JointIndex, Eigen::Vector3f& OutJointTranslation, Eigen::Vector3f& OutJointRotation) const;`
- L134 _public prototype_ `void GetNeutralJointTransform(const std::vector<Eigen::Transform<float, 3, Eigen::Affine>>& BindPoseMatrices, std::uint16_t JointIndex, Eigen::Vector3f& OutJointTranslation, Eigen::Vector3f& OutJointRotation) const;`
- L136 _public prototype_ `void SetNeutralJointsTranslations(State& State, const Eigen::Ref<const Eigen::Matrix<float, 3, -1>> InJoints) const;`
- L138 _public prototype_ `void SetNeutralJointRotations(State& State, av::ConstArrayView<float> inJointRotations) const;`
- L140 _public prototype_ `void ResetGuiControls(State& State) const;`
- L146 _public prototype_ `void SetGuiControls(State& State, av::ConstArrayView<float> guiControls) const;` — Overwrite the full GUI-control vector on the state and re-evaluate. Caller must pass exactly GetGuiControlNames().size() values; existing values are replaced wholesale. Mirrors ResetGuiControls but lets the caller specify the pose (e.g. for tests that need to set pose_rigid_root.t* / pose_rigid_pelvis.r* before evaluation).
- L147 _public prototype_ `void ResetScale(State& State) const;`
- L148 _public prototype_ `void UpdateEvaluatePose(State& State, bool bEvaluatePose) const;`
- L149 _public prototype_ `void UpdateApplyFloorOffset(State& State, bool bApplyFloorOffset) const;`
- L151 _public prototype_ `bool SetNeutralMesh(State& State, const Eigen::Ref<const Eigen::Matrix<float, 3, -1>> inMesh) const;`
- L161 _public prototype_ `Eigen::Matrix3Xf RigidAttachmentToBind( const State& state, const std::string& jointName, const Eigen::Ref<const Eigen::Matrix3Xf>& posedVertices) const;` — Move `posedVertices` from the state's current pose frame back to the state's shape-adjusted bind frame, treating them as a rigid attachment to the joint named `jointName` (typically "head" for face attachments like eyes / teeth). Thin wrapper around `BodyShapeEditor::RigidAttachmentToBind` that pulls the BSE + BSE state from the PImpl, so callers don't need direct access to the underlying editor. Returns an empty matrix when `jointName` can't be resolved or the state's joint matrices aren't populated.
- L166 _public prototype_ `av::ConstArrayView<int> CoreJoints() const;`
- L167 _public prototype_ `av::ConstArrayView<int> HelperJoints() const;`
- L170 _public prototype_ `void FixJoints(State& State) const;` — Sets neutral joint translation based on vertex positions
- L172 _public prototype_ `void VolumetricallyFitHandAndFeetJoints(State& state) const;`
- L175 _public prototype_ `int NumGizmos() const;` — @returns all number of gizmos used for region blending
- L178 _public prototype_ `bool EvaluateGizmos(const State& State, float* OutGizmos) const;` — Gets the positions of the gizmos used for region blending
- L181 _public prototype_ `const std::vector<std::string>& GetRegionNames() const;` — @returns all region names
- L184 _public prototype_ `const std::vector<std::string>& GetGuiControlNames() const;` — @returns all gui control names
- L187 _public prototype_ `const std::vector<std::string>& GetRawControlNames() const;` — @returns all raw control names
- L193 _public prototype_ `bool Blend(State& state, int RegionIndex, const std::vector<std::pair<float, const State*>>& States, BodyAttribute Type) const;` — Blend region @p RegionIndex (all regions if -1) to @p States. @p Type defines whether skeleton, shaping, or both are blended.
- L195 _public prototype_ `bool SelectPreset(State& state, int RegionIndex, const std::string& PresetName, BodyAttribute Type) const;`
- L197 _public prototype_ `bool BlendPresets(State& state, int RegionIndex, const std::vector<std::pair<float, std::string>>& alphaAndPresetNames, BodyAttribute Type) const;`
- L199 _public prototype_ `bool SetVertexDeltaScale(State& state, float VertexDeltaScale) const;`
- L200 _public prototype_ `bool ClearVertexDeltas(State& State) const;`
- L201 _public prototype_ `bool ClearJointDeltas(State& State) const;`
- L205 _public prototype_ `bool SetFaceBlend(State& state, float faceBlend) const;` — Blend the face PCA into the body mesh — 0 keeps the body face, 1 fully replaces it with the MHC face state's face. Re-evaluates.
- L208 _public prototype_ `bool SetSeamBlend(State& state, float seamBlend) const;` — Blend the body-seam delta (smooth seam between head and body) — 0 disables, 1 fully applies. Effective only when faceBlend > 0.
- L218 _public prototype_ `bool AdaptNeckSeam(State& State, const AdaptNeckSeamParams& Params) const;`
- L219 _public prototype_ `bool ResetNeckSeam(State& State) const;`
- L238 _public typedef_ `using IterationFunc = std::function<bool(const av::ConstArrayView<float> , const av::ConstArrayView<float> , av::ConstArrayView<float> , int, ESolveStepType)>;`
- L240 _public prototype_ `static bool BuildCombinedSolveTarget( const Eigen::Ref<const Eigen::Matrix<float, 3, -1>> vertices, const Eigen::Ref<const Eigen::Matrix<int, 3, -1>> triangleIndices, const std::vector<std::pair<int, Eigen::Vector3f>>& keyPointCorrespondences, const std::shared_ptr<TITAN_NAMESPACE::LandmarkConstraints2D<float>>& landmarkConstraints2D, TITAN_NAMESPACE::BodyShapeEditorTarget& outSolveTarget);`
- L247 _public prototype_ `static bool BuildHeadOnlySolveTarget( const Eigen::Ref<const Eigen::Matrix<float, 3, -1>> vertices, const Eigen::Ref<const Eigen::Matrix<int, 3, -1>> triangleIndices, const std::vector<std::pair<int, Eigen::Vector3f>>& keyPointCorrespondences, const std::shared_ptr<TITAN_NAMESPACE::LandmarkConstraints2D<float>>& landmarkConstraints2D, TITAN_NAMESPACE::BodyShapeEditorTarget& outSolveTarget);`
- L254 _public prototype_ `static bool BuildBodyOnlySolveTarget( const Eigen::Ref<const Eigen::Matrix<float, 3, -1>> vertices, const Eigen::Ref<const Eigen::Matrix<int, 3, -1>> triangleIndices, const std::vector<std::pair<int, Eigen::Vector3f>>& keyPointCorrespondences, const std::shared_ptr<TITAN_NAMESPACE::LandmarkConstraints2D<float>>& landmarkConstraints2D, TITAN_NAMESPACE::BodyShapeEditorTarget& outSolveTarget);`
- L261 _public prototype_ `static bool BuildHeadAndBodySolveTarget( const Eigen::Ref<const Eigen::Matrix<float, 3, -1>> headVertices, const Eigen::Ref<const Eigen::Matrix<int, 3, -1>> headTriangleIndices, const Eigen::Ref<const Eigen::Matrix<float, 3, -1>> bodyVertices, const Eigen::Ref<const Eigen::Matrix<int, 3, -1>> bodyTriangleIndices, const std::vector<std::pair<int, Eigen::Vector3f>>& keyPointCorrespondences, const std::shared_ptr<TITAN_NAMESPACE::LandmarkConstraints2D<float>>& landmarkConstraints2D, TITAN_NAMESPACE::BodyShapeEditorTarget& outSolveTarget);`
- L270 _public prototype_ `std::shared_ptr<TITAN_NAMESPACE::LandmarkConstraints2D<float>> CreateLandmarkConstraints( const std::map<std::string, FaceTrackingLandmarkData>& faceLandmarks, const TITAN_NAMESPACE::MetaShapeCamera<float>& camera) const;`
- L274 _public prototype_ `bool FitToTarget(State& state, const FitToTargetOptions& options, const Eigen::Ref<const Eigen::Matrix<float, 3, -1>> InVertices, av::ConstArrayView<float> jointRotations = {}, IterationFunc iterationFunc = {}) const;`
- L278 _public prototype_ `bool FitToTarget(State& state, const FitToTargetOptions& options, const dna::Reader* InDnaReader) const;`
- L282 _public prototype_ `bool FitToArbitraryTarget(State& state, const ArbitraryFitSolveOptions& options, const TITAN_NAMESPACE::BodyShapeEditorTarget& solveTarget, IterationFunc iterationFunc = {}) const;`
- L287 _public prototype_ `bool AlignToTargetMesh(State& state, const TITAN_NAMESPACE::BodyShapeEditorTarget& solveTarget) const;`
- L290 _public prototype_ `bool FitFaceToArbitraryTarget(State& state, const ArbitraryFitSolveOptions& options, const TITAN_NAMESPACE::BodyShapeEditorTarget& solveTarget, IterationFunc iterationFunc = {}) const;`
- L295 _public prototype_ `bool RefineVertices(State& state, const TITAN_NAMESPACE::BodySolveConfiguration& options, const TITAN_NAMESPACE::BodyShapeEditorTarget& solveTarget, const std::string& overrideVertexMaskName = "") const;`
- L300 _public prototype_ `bool PipelineFitToArbitraryTarget(State& state, const std::string& pipelineName, const ArbitraryFitSolveOptions& options, const TITAN_NAMESPACE::BodyShapeEditorTarget& solveTarget, IterationFunc iterationFunc = {}) const;`
- L307 _public prototype_ `bool GetMeasurements(Eigen::Ref<const Eigen::Matrix<float, 3, -1>> combinedBodyAndFaceVertices, Eigen::VectorXf& measurements, std::vector<std::string>& measurementNames) const;` — Calculate measurements on the combined body vertices
- L310 _public prototype_ `bool GetMeasurements(Eigen::Ref<const Eigen::Matrix<float, 3, -1>> faceVertices, Eigen::Ref<const Eigen::Matrix<float, 3, -1>> bodyVertices, Eigen::VectorXf& measurements, std::vector<std::string>& measurementNames) const;` — Calculate measurements on the body and face vertices
- L313 _public prototype_ `bool GetNumLOD0MeshVertices(int& OutNumMeshVertices, bool bInCombined) const;` — Get the number of mesh vertices for LOD 0, either for the standalone body, or the combined body
- L315 _public prototype_ `av::ConstArrayView<int> GetBodyToCombinedMapping(int lod) const;`
- L317 _public prototype_ `int SelectVertex(const State& State, const Eigen::Vector3f& Origin, const Eigen::Vector3f& Direction, Eigen::Vector3f& OutVertex, Eigen::Vector3f& OutNormal) const;`
- L319 _public prototype_ `void SetFacePatchBlendModel(std::shared_ptr<TITAN_NAMESPACE::PatchBlendModel<float>> facePatchModel);`
- L320 _public prototype_ `bool SetFacePatchBlendModelParameters(State& state, const Eigen::VectorXf& parameters) const;`
- L321 _public prototype_ `bool ResetFacePatchBlendModel(State& state) const;`
- L322 _public prototype_ `bool AreFacePatchBlendModelParametersDefault(const State& state) const;`
- L330 _public prototype_ `std::vector<Keypoint> GetDefaultKeypoints() const;`
- L333 _private prototype_ `MetaHumanCreatorBodyAPI();`
- L336 _private member_ `Private* m {};`

#### enum `TITAN_API_NAMESPACE::MetaHumanCreatorBodyAPI::BodyAttribute`  
`enum class BodyAttribute`  
_L51-56_
- L53 _public enumerator_ `Skeleton`
- L54 _public enumerator_ `Shape`
- L55 _public enumerator_ `Both`

#### struct `TITAN_API_NAMESPACE::MetaHumanCreatorBodyAPI::AdaptNeckSeamParams`  
`struct AdaptNeckSeamParams`  
_L210-216_
- L212 _public member_ `TITAN_NAMESPACE::SeamLockSide seamLockSide = TITAN_NAMESPACE::SeamLockSide::None;`
- L213 _public member_ `float laplacianWeight = 1.5f;`
- L214 _public member_ `int rings = 12;`
- L215 _public member_ `int iterations = 15;`

#### struct `TITAN_API_NAMESPACE::MetaHumanCreatorBodyAPI::FitToTargetOptions`  
`struct FitToTargetOptions`  
_L221-226_
- L223 _public member_ `bool isAPose{false};`
- L224 _public member_ `bool enforceAnatomicalPose {false};`
- L225 _public member_ `int iterations = 9;`

#### struct `TITAN_API_NAMESPACE::MetaHumanCreatorBodyAPI::ArbitraryFitSolveOptions`  
`struct ArbitraryFitSolveOptions`  
_L228-234_
- L230 _public member_ `TITAN_NAMESPACE::BodySolveConfiguration bodySolveConfiguration;`
- L232 _public member_ `bool bReloadSolveConfigurations = false;`
- L233 _public member_ `bool bSolveForPose = true;`

#### enum `TITAN_API_NAMESPACE::MetaHumanCreatorBodyAPI::ESolveStepType`  
`enum class ESolveStepType`  
_L236-236_
- L236 _public enumerator_ `enum class ESolveStepType { ScaleSolve, BodySolve, FaceSolve, RefineVerticesSolve }; using IterationFunc = std::function<bool(const av::ConstArrayView<float> , const av::ConstArrayView<float> , av::ConstArrayView<float> , int, ESolveStepType)>; TITAN_API static bool BuildCombinedSolveTarget( const Eigen::Ref<const Eigen::Matrix<float, 3, -1>> vertices, const Eigen::Ref<const Eigen::Matrix<int, 3, -1>> triangleIndices, const std::vector<std::pair<int, Eigen::Vector3f>>& keyPointCorrespondences,`
- L236 _public enumerator_ `enum class ESolveStepType { ScaleSolve, BodySolve, FaceSolve, RefineVerticesSolve }; using IterationFunc = std::function<bool(const av::ConstArrayView<float> , const av::ConstArrayView<float> , av::ConstArrayView<float> , int, ESolveStepType)>; TITAN_API static bool BuildCombinedSolveTarget( const Eigen::Ref<const Eigen::Matrix<float, 3, -1>> vertices, const Eigen::Ref<const Eigen::Matrix<int, 3, -1>> triangleIndices, const std::vector<std::pair<int, Eigen::Vector3f>>& keyPointCorrespondences,`
- L236 _public enumerator_ `enum class ESolveStepType { ScaleSolve, BodySolve, FaceSolve, RefineVerticesSolve }; using IterationFunc = std::function<bool(const av::ConstArrayView<float> , const av::ConstArrayView<float> , av::ConstArrayView<float> , int, ESolveStepType)>; TITAN_API static bool BuildCombinedSolveTarget( const Eigen::Ref<const Eigen::Matrix<float, 3, -1>> vertices, const Eigen::Ref<const Eigen::Matrix<int, 3, -1>> triangleIndices, const std::vector<std::pair<int, Eigen::Vector3f>>& keyPointCorrespondences,`
- L236 _public enumerator_ `enum class ESolveStepType { ScaleSolve, BodySolve, FaceSolve, RefineVerticesSolve }; using IterationFunc = std::function<bool(const av::ConstArrayView<float> , const av::ConstArrayView<float> , av::ConstArrayView<float> , int, ESolveStepType)>; TITAN_API static bool BuildCombinedSolveTarget( const Eigen::Ref<const Eigen::Matrix<float, 3, -1>> vertices, const Eigen::Ref<const Eigen::Matrix<int, 3, -1>> triangleIndices, const std::vector<std::pair<int, Eigen::Vector3f>>& keyPointCorrespondences,`

#### struct `TITAN_API_NAMESPACE::MetaHumanCreatorBodyAPI::Keypoint`  
`struct Keypoint`  
_L324-328_
- L326 _public member_ `int index = 0;`
- L327 _public member_ `std::string name;`

#### class `TITAN_API_NAMESPACE::MetaHumanCreatorBodyAPI::State`  
`class MetaHumanCreatorBodyAPI::State`  
_L339-394_
- L342 _public prototype_ `~State();`
- L343 _public prototype_ `State(State&&) = delete;`
- L344 _public prototype_ `State& operator=(State&&) = delete;`
- L345 _public prototype_ `State& operator=(const State&) = delete;`
- L347 _public prototype_ `std::shared_ptr<State> Clone() const;`
- L349 _public prototype_ `bool Reset();`
- L351 _public prototype_ `av::ConstArrayView<float> GetMesh(int lod) const;`
- L352 _public prototype_ `av::ConstArrayView<float> GetMeshNormals(int lod) const;`
- L353 _public prototype_ `av::ConstArrayView<float> GetBindPose() const;`
- L354 _public prototype_ `av::ConstArrayView<float> GetWorldPose() const;`
- L355 _public prototype_ `av::ConstArrayView<float> GetMeasurements() const;`
- L356 _public prototype_ `av::ConstArrayView<float> GetGuiControls() const;`
- L357 _public prototype_ `bool AreGuiControlsZero() const;`
- L358 _public prototype_ `bool GetFacePatchBlendModelParameters(Eigen::VectorXf& OutParameters) const;`
- L359 _public prototype_ `av::ConstArrayView<float> GetRawControls() const;`
- L361 _public prototype_ `void SetCustomVertexInfluenceWeightsLOD0(const TITAN_NAMESPACE::SparseMatrix<float>& vertexInfluenceWeights);`
- L363 _public prototype_ `Eigen::Matrix3Xf GetContourVertices(int ConstraintIndex) const;`
- L364 _public prototype_ `Eigen::Matrix3Xf GetContourDebugVertices(int ConstraintIndex) const;`
- L366 _public prototype_ `int GetConstraintNum() const;`
- L367 _public prototype_ `const std::string& GetConstraintName(int ConstraintIndex) const;`
- L368 _public prototype_ `bool GetConstraintTarget(int ConstraintIndex, float& OutTarget) const;`
- L369 _public prototype_ `bool SetConstraintTarget(int ConstraintIndex, float Target);`
- L370 _public prototype_ `bool RemoveConstraintTarget(int ConstraintIndex);`
- L372 _public prototype_ `bool SetApplyFloorOffset(bool floorOffset);`
- L373 _public prototype_ `bool GetApplyFloorOffset() const;`
- L378 _public prototype_ `bool GetEvaluatePose() const;` — Use MetaHumanCreatorBodyAPI::UpdateEvaluatePose(state, value) — the toggle re-derives VertexDeltas to preserve the mesh and needs the owning API instance.
- L380 _public prototype_ `float GetFaceBlend() const;`
- L381 _public prototype_ `float GetSeamBlend() const;`
- L383 _public prototype_ `float VertexDeltaScale() const;`
- L386 _private prototype_ `State();`
- L387 _private prototype_ `State(const State&);`
- L390 _private member_ `Private* m {};`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace dna`
- L27 _namespace_ `namespace trio`
- L34 _namespace_ `namespace TITAN_NAMESPACE`
- L43 _namespace_ `namespace TITAN_API_NAMESPACE`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/api/OpenCVCamera.h` (Private)


#### struct `TITAN_API_NAMESPACE::OpenCVCameraTemplate`  
`template<typename T> struct OpenCVCameraTemplate`  
_L12-27_
- L14 _public member_ `int32_t width;`
- L15 _public member_ `int32_t height;`
- L16 _public member_ `T fx;`
- L17 _public member_ `T fy;`
- L18 _public member_ `T cx;`
- L19 _public member_ `T cy;`
- L20 _public member_ `T k1;`
- L21 _public member_ `T k2;`
- L22 _public member_ `T k3;`
- L23 _public member_ `T p1;`
- L24 _public member_ `T p2;`
- L26 _public member_ `T Extrinsics[16];` — Transform from world coordinates to camera coordinates in column-major format.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TITAN_API_NAMESPACE`
- L29 _typedef_ `using OpenCVCameraD = OpenCVCameraTemplate<double>;` (scope `TITAN_API_NAMESPACE`)
- L30 _typedef_ `using OpenCVCamera = OpenCVCameraTemplate<float>;` (scope `TITAN_API_NAMESPACE`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/bodyshapeeditor/include/bodyshapeeditor/BodyJointEstimator.h` (Private)


#### class `BodyJointEstimator`  
`class BodyJointEstimator`  
_L15-40_
- L18 _public prototype_ `BodyJointEstimator();`
- L19 _public prototype_ `~BodyJointEstimator();`
- L20 _public prototype_ `BodyJointEstimator(const BodyJointEstimator& other);`
- L21 _public prototype_ `BodyJointEstimator(BodyJointEstimator&& other) noexcept;`
- L22 _public prototype_ `BodyJointEstimator& operator=(const BodyJointEstimator& other);`
- L23 _public prototype_ `BodyJointEstimator& operator=(BodyJointEstimator&& other) noexcept;`
- L25 _public prototype_ `void Init(const std::string& json);`
- L26 _public prototype_ `void Init(const JsonElement& json);`
- L28 _public prototype_ `const std::vector<int>& SurfaceJoints() const;`
- L29 _public prototype_ `const std::vector<int>& CoreJoints() const;`
- L30 _public prototype_ `const std::vector<int>& DependentJoints() const;`
- L31 _public prototype_ `const SparseMatrix<float>& VertexJointMatrix() const;`
- L32 _public prototype_ `const SparseMatrix<float>& JointJointMatrix() const;`
- L34 _public prototype_ `Eigen::Matrix<float, 3, -1> EstimateJointWorldTranslations(const Eigen::Ref<const Eigen::Matrix<float, 3, -1>>& vertices) const;`
- L35 _public prototype_ `void FixJointOrients(const BodyGeometry<float>& archetypeJoints, std::vector<Eigen::Transform<float, 3, Eigen::Affine>>& targetJoints, const Eigen::Matrix3Xf& vertices) const;`
- L39 _private member_ `Private* m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/bodyshapeeditor/include/bodyshapeeditor/BodyMeasurement.h` (Private)


#### class `BodyMeasurement`  
`class BodyMeasurement`  
_L21-94_
- L29 _public prototype_ `static std::vector<BodyMeasurement> FromJSON(const JsonElement& json, const Eigen::Matrix3Xf& baseVertices);`
- L33 _public prototype_ `static Eigen::VectorXf GetBodyMeasurements(const std::vector<BodyMeasurement>& measurements, const Eigen::Matrix<float, 3, -1>& mesh, const Eigen::VectorXf& RawControls);`
- L38 _public prototype_ `static void UpdateBodyMeasurementPoints(std::vector<BodyMeasurement>& measurements, const Eigen::Matrix<float, 3, -1>& vertices, const Eigen::Matrix<float, 3, -1>& vertexNormals, const HalfEdgeMesh<float>& heTopology, TaskThreadPool* threadPool, bool debug = false);` — Update all measurement points (note that it is the callers responsibility to ensure that meshTools has been prepared with the right topology and half edge data structure
- L45 _public prototype_ `static BodyMeasurement CreateSemanticMeasurement(const std::string& name, const Eigen::VectorXf& weights);`
- L47 _public prototype_ `void UpdateVisualizationMeasurementPoints(const Eigen::Matrix3Xf& vertices, int resampling);`
- L49 _public prototype_ `Eigen::Matrix3Xf GetMeasurementPoints() const;`
- L50 _public prototype_ `Eigen::Matrix3Xf GetMeasurementDebugPoints(const Eigen::Matrix3Xf& vertices) const;`
- L51 _public function_ `static std::string GetAlias(const std::string& name)`
- L67 _public function_ `type_t GetType() const`
- L68 _public function_ `const std::string& GetName() const`
- L69 _public function_ `const std::vector<int>& GetVertexIDs() const`
- L70 _public function_ `const Eigen::VectorXf& GetWeights() const`
- L71 _public function_ `const Eigen::Vector3f& GetNormal() const`
- L72 _public function_ `float GetFixedMaxInput () const`
- L73 _public function_ `float GetFixedMinInput () const`
- L74 _public function_ `std::pair<float, float> GetVariableMaxInput() const`
- L75 _public function_ `std::pair<float, float> GetVariableMinInput() const`
- L76 _public function_ `const std::vector<BarycentricCoordinates<float>>& GetBarycentricCoordinates() const`
- L78 _public member_ `static constexpr float InvalidValue = std::numeric_limits<float>::min();`
- L81 _private member_ `type_t m_type;`
- L82 _private member_ `std::string m_name;`
- L83 _private member_ `std::vector<int> m_vertexIDs;`
- L84 _private member_ `Eigen::VectorXf m_weights;`
- L85 _private member_ `Eigen::Vector3f m_normal;`
- L86 _private member_ `int m_numVertices{};`
- L87 _private member_ `std::vector<BarycentricCoordinates<float>> m_barycentricCoordinates;`
- L88 _private member_ `std::vector<Eigen::Vector3f> m_debugPoints;`
- L89 _private member_ `float minInputValue = InvalidValue;`
- L90 _private member_ `float maxInputValue = InvalidValue;`
- L91 _private member_ `std::pair<float, float> variableMinInputValues = {InvalidValue, InvalidValue};`
- L92 _private member_ `std::pair<float, float> variableMaxInputValues = {InvalidValue, InvalidValue};`
- L93 _private member_ `Eigen::Matrix<float, 3, -1> m_points;`

#### enum `BodyMeasurement::type_t`  
`enum type_t`  
_L24-27_
- L26 _public enumerator_ `Circumference`
- L26 _public enumerator_ `Circumference`
- L26 _public enumerator_ `Circumference`
- L26 _public enumerator_ `Circumference`
- L26 _public enumerator_ `Circumference`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/bodyshapeeditor/include/bodyshapeeditor/BodyShapeEditor.h` (Private)


#### struct `Constraint2D`  
`struct Constraint2D`  
_L32-38_
- L34 _public member_ `Eigen::Vector2f screenPosition;` — Normalized screen coords [-1,1]
- L35 _public member_ `int index = -1;` — Joint or vertex index
- L36 _public member_ `bool isJoint = false;`
- L37 _public member_ `float weight = 1.0f;`

#### class `BodyShapeEditor`  
`class BodyShapeEditor`  
_L47-391_
- L66 _public prototype_ `~BodyShapeEditor();`
- L67 _public prototype_ `BodyShapeEditor();`
- L69 _public prototype_ `BodyShapeEditor(const BodyShapeEditor& other) = delete;`
- L70 _public prototype_ `BodyShapeEditor(BodyShapeEditor&& other) = delete;`
- L71 _public prototype_ `BodyShapeEditor& operator=(const BodyShapeEditor& other) = delete;`
- L72 _public prototype_ `BodyShapeEditor& operator=(BodyShapeEditor&& other) = delete;`
- L74 _public prototype_ `void SetThreadPool(const std::shared_ptr<TaskThreadPool>& threadPool);`
- L76 _public prototype_ `void Init(const dna::Reader* reader, trio::BoundedIOStream* rbfModelStream, trio::BoundedIOStream* skinModelStream, dna::Reader* InCombinedBodyArchetypeDnaReader, const std::vector<std::map<std::string, std::map<std::string, float>>>& JointSkinningWeightLodPropagationMap, const std::vector<int>& maxSkinWeightsPerVertexForEachLod = { 12, 8, 8, 4}, std::shared_ptr<const LodGeneration<float>> combinedLodGenerationData = nullptr);`
- L83 _public prototype_ `void Init(std::shared_ptr<BodyLogic<float>> BodyLogic, std::shared_ptr<BodyGeometry<float>> CombinedBodyArchetypeGeometry, std::shared_ptr<RigLogic<float>> CombinedBodyRigLogic, std::shared_ptr<BodyGeometry<float>> BodyGeometry, av::ConstArrayView<BodyMeasurement> contours, const std::vector<std::map<std::string, std::map<std::string, float>>>& JointSkinningWeightLodPropagationMap, const std::vector<int>& maxSkinWeightsPerVertexForEachLod = { 12, 8, 8, 4 }, std::shared_ptr<const LodGeneration<float>> combinedLodGenerationData = nullptr, const std::map<std::string, VertexWeights<float>>& partWeights = {});`
- L93 _public prototype_ `void SetFittingVertexIDs(const std::vector<int>& vertexIds);`
- L95 _public prototype_ `void SetNeckSeamVertexIDs(const std::vector<std::vector<int>>& vertexIds);`
- L97 _public prototype_ `void SetBodyToCombinedMapping(int lod, const std::vector<int>& bodyToCombinedMapping);`
- L99 _public prototype_ `const std::vector<int>& GetBodyToCombinedMapping(int lod = 0) const;`
- L101 _public prototype_ `int NumLODs() const;`
- L103 _public prototype_ `void EvaluateConstraintRange(const State& state, av::ArrayView<float> MinValues, av::ArrayView<float> MaxValues, bool bScaleWithHeight) const;`
- L105 _public prototype_ `std::shared_ptr<State> CreateState() const;`
- L128 _public prototype_ `void EvaluateState(State& State) const;` — Evaluate the state and update the meshes. Convenience wrapper that reads both axes off State (CalcStrategy::Auto routes via State::EvaluatePose; applyPose is taken directly from State::EvaluatePose).
- L136 _public prototype_ `void EvaluateState(State& State, CalcStrategy strategy, bool isEvaluatingPose) const;` — Explicit form — caller chooses both axes independently of the State's flag. `isEvaluatingPose` drives whether pose values are applied (RBF correctives, pose-driver shape controls, root/pelvis math); `strategy` selects the shape evaluator (linear approximation vs full skeletal). Auto pairs the path with isEvaluatingPose to preserve legacy behavior.
- L144 _public prototype_ `void SetEvaluatePose(State& State, bool evaluatePose) const;` — Flip the state's EvaluatePose flag while preserving the visible mesh. Captures the current mesh under the OLD flag, flips the flag on the state, then re-derives VertexDeltas (via SetNeutralMesh) so the NEXT EvaluateState — under the new flag — reproduces the same vertices. Use this instead of State::SetEvaluatePose when you don't want the linear-vs-skeletal cross-term drift to surface on toggle.
- L146 _public prototype_ `std::shared_ptr<BodyLogic<float>> GetBodyLogic() const;`
- L148 _public prototype_ `const std::vector<std::string>& GetGuiControlNames() const;`
- L149 _public prototype_ `const std::vector<std::string>& GetRawControlNames() const;`
- L152 _public prototype_ `void UpdateGuiFromRawControls(State& state) const;` — Estimate Gui from Raw controls
- L154 _public prototype_ `std::shared_ptr<State> RestoreState(trio::BoundedIOStream* InputStream);`
- L155 _public prototype_ `void DumpState(const State& State, trio::BoundedIOStream* OutputStream);`
- L157 _public prototype_ `void Solve(State& State, float priorWeight = 1.0f, const int iterations = 2) const;`
- L165 _public typedef_ `using IterationFunc = std::function<void(const Eigen::Matrix<float, 3, -1>&, const Eigen::Matrix<float, 3, -1>&, int, float, std::vector<Eigen::Transform<float, 3, Eigen::Affine>>)>;`
- L166 _public prototype_ `Vector<float> SolveForTemplateMesh(State& State, const Eigen::Ref<const Eigen::Matrix<float, 3, -1>> InVertices, const FitToTargetOptions& fitToTargetOptions, av::ConstArrayView<float> inJointRotations = {}, Eigen::VectorXf vertexWeightsOverride = {}, IterationFunc func = [](const Eigen::Matrix<float, 3, -1>&, const Eigen::Matrix<float, 3, -1>&, int, float, std::vector<Eigen::Transform<float, 3, Eigen::Affine>>) {} );`
- L171 _public function_ `const Eigen::Matrix<float, 3, -1>&, int, float, std::vector<Eigen::Transform<float, 3, Eigen::Affine>>)`
- L177 _public prototype_ `void AdaptNeckSeam(State& state, float laplacianWeight, int rings, int iterations, SeamLockSide lockSide = SeamLockSide::None);` — AdaptNeckSeam smooths the neck seam via Laplacian relaxation on a ring band around the seam loop. See SeamLockSide in BodySolveConfiguration.h for the lock-side semantics. Default lockSide = None (seam free, both sides relax between outer pins).
- L192 _public prototype_ `static Camera<float> ComputeCameraFromLandmarks(const std::vector<Eigen::Vector3f>& positions, int imageWidth = 1024, int imageHeight = 1024);`
- L193 _public prototype_ `static FacePlaneResult ComputeCameraFromLandmarksEx(const std::vector<Eigen::Vector3f>& positions, int imageWidth = 1024, int imageHeight = 1024);`
- L194 _public prototype_ `static Camera<float> ComputeOptimalLandmarkCamera( const LandmarkConstraints2D<float>& landmarks, const Mesh<float>& targetMesh, const Eigen::Vector3f& targetOffset = Eigen::Vector3f::Zero());`
- L198 _public prototype_ `static FacePlaneResult ComputeOptimalLandmarkCameraEx( const LandmarkConstraints2D<float>& landmarks, const Mesh<float>& targetMesh, const Eigen::Vector3f& targetOffset = Eigen::Vector3f::Zero(), const AABBTree<float>* aabbTree = nullptr);`
- L203 _public prototype_ `int GetNumFaceVertices() const;`
- L205 _public prototype_ `void SetFacePatchBlendModel(std::shared_ptr<PatchBlendModel<float>> facePatchModel);`
- L207 _public prototype_ `Eigen::Vector3f GetModelMeshExtents() const;`
- L209 _public prototype_ `bool SetTargetScaleAndRigidSolve(State& state, const Eigen::Matrix<float, 3, -1>& targetVertices, const BodySolveConfiguration& options);`
- L218 _public prototype_ `void AlignToTargetMesh(State& state, const BodyShapeEditorTarget& target);` — Fit the rig to a target scan via rigid (R=I) + uniform scale + translation. Correspondence sources are auto-selected from what the target carries: face landmarks/curves if a Landmarks2D is present, body keypoints if any are set. Writes pose_rigid_root.tx/ty/tz and clears pose_rigid_pelvis.r*. No rotation is ever applied — rigs and scans are expected to share a canonical orientation.
- L220 _public prototype_ `Vector<float> SolveForArbitraryMeshWithICP( State& state, const BodyShapeEditorTarget& target, const BodySolveConfiguration& options, const std::vector<int>& lockedControlIndices = {}, IterationFunc iterationFunc = [](const Eigen::Matrix<float, 3, -1>&, const Eigen::Matrix<float, 3, -1>&, int, float, std::vector<Eigen::Transform<float, 3, Eigen::Affine>>) {} );`
- L231 _public prototype_ `void SolveFace( State& state, const BodyShapeEditorTarget& target, const BodySolveConfiguration& options, IterationFunc iterationFunc = [](const Eigen::Matrix<float, 3, -1>&, const Eigen::Matrix<float, 3, -1>&, int, float, std::vector<Eigen::Transform<float, 3, Eigen::Affine>>) {} );`
- L241 _public prototype_ `void RunPipeline( State& state, const BodyShapeEditorTarget& target, const BodySolveConfiguration& defaultConfig, const std::vector<SolveStep>& steps, IterationFunc iterationFunc = [](const Eigen::Matrix<float, 3, -1>&, const Eigen::Matrix<float, 3, -1>&, int, float, std::vector<Eigen::Transform<float, 3, Eigen::Affine>>) {}, std::function<void(int, int, const std::string&)> progressFunc = [](int, int, const std::string&) {});`
- L248 _public function_ `const std::vector<SolveStep>& steps, IterationFunc iterationFunc = [](const Eigen::Matrix<float, 3, -1>&, const Eigen::Matrix<float, 3, -1>&, int, float, std::vector<Eigen::Transform<float, 3, Eigen::Affine>>)`
- L249 _public function_ `IterationFunc iterationFunc = [](const Eigen::Matrix<float, 3, -1>&, const Eigen::Matrix<float, 3, -1>&, int, float, std::vector<Eigen::Transform<float, 3, Eigen::Affine>>)`
- L251 _public prototype_ `void RefineVertices( State& state, const BodyShapeEditorTarget& target, const BodySolveConfiguration& solveConfig);`
- L256 _public prototype_ `void SetNeutralJointRotations(State& state, av::ConstArrayView<float> inJointRotations);`
- L258 _public prototype_ `void VolumetricallyFitHandAndFeetJoints(State& state);`
- L260 _public prototype_ `void SetNeutralJointsTranslations(State& State, const Eigen::Ref<const Eigen::Matrix<float, 3, -1>> InJoints);`
- L261 _public prototype_ `bool SetNeutralMesh(State& State, const Eigen::Ref<const Eigen::Matrix<float, 3, -1>> inMesh) const;`
- L263 _public prototype_ `void ResetPoseGuiControls(State& State);`
- L265 _public prototype_ `void ResetFaceState(State& State);`
- L267 _public prototype_ `void ClearJointDeltas(State& State);`
- L269 _public prototype_ `const BodyJointEstimator& JointEstimator();`
- L271 _public prototype_ `void UpdateMeasurementPoints(State& State) const;`
- L273 _public prototype_ `void StateToDna(const State& State, dna::Writer* InOutDnaWriter, bool combinedBodyAndFace = false, bool usePosedJoints = false) const;`
- L275 _public prototype_ `int NumJoints() const;`
- L276 _public prototype_ `const std::vector<std::string>& GetJointNames() const;`
- L277 _public prototype_ `const std::vector<int>& GetJointParentIndices() const;`
- L278 _public prototype_ `void GetNeutralJointTransform(const State& State, std::uint16_t JointIndex, Eigen::Vector3f& OutJointTranslation, Eigen::Vector3f& OutJointRotation) const;`
- L279 _public prototype_ `void GetNeutralJointTransform(const std::vector<Eigen::Transform<float, 3, Eigen::Affine>>& BindPoseMatrices, std::uint16_t JointIndex, Eigen::Vector3f& OutJointTranslation, Eigen::Vector3f& OutJointRotation) const;`
- L281 _public prototype_ `void SetCustomGeometryToState(State& state, std::shared_ptr<const BodyGeometry<float>> Geometry, bool Fit);`
- L284 _public prototype_ `void GetVertexInfluenceWeights(const State& state, std::vector<SparseMatrix<float>>& vertexInfluenceWeights) const;` — calculate the skinning weights for the supplied body state at each lod; the body must have a skin weights pca present for this to work
- L287 _public prototype_ `const std::vector<int>& GetMaxSkinWeights() const;` — get the maximum number of skin weights for each joint at each LOD of the combined body model (by default this is set to 12, 8, 8, 4)
- L289 _public prototype_ `void SetMaxSkinWeights(const std::vector<int>& MaxSkinWeights);` — set the maximum number of skin weights for each joint at each LOD of the combined body model
- L291 _public prototype_ `int GetJointIndex(const std::string& JointName) const;`
- L317 _public prototype_ `Eigen::Matrix3Xf RigidAttachmentToBind( const State& state, const std::string& jointName, const Eigen::Ref<const Eigen::Matrix3Xf>& posedVertices) const;` — Move `posedVertices` (in the state's current pose frame) back to the state's shape-adjusted bind frame, treating them as a rigid attachment to the joint named `jointName`. Useful for taking eyes / teeth meshes that the user provided on a fitted, posed character and converting them into the bind-frame inputs the PBM eyes/teeth fitter expects — cheaper and more accurate than a Procrustes guess because the rig state already tells us the transform. Works regardless of the state's `EvaluatePose` flag: both bind and world matrices are composed via `ComposePoseFrame` from the same evaluation, so callers can A-pose the body (`UpdateEvaluatePose(false)`) before invoking this — the head-joint un-skin still uses the fitted-pose transform implied by the state's GuiControls. The matrices used are NOT the static rig bind / world matrices — they're the per-state, shape-adjusted versions (JointDeltas + scale + root offset baked in). `FloorOffsetApplied` is forced off internally so the bind/world pair is self-consistent regardless of the caller's flag (floor offset is computed from the body's lowest Y vertex, which differs between linear and skeletal modes — mismatched Δ would inject a residual translation into the rigid transform). Returns an empty matrix when `jointName` is unknown or the state's joint matrices aren't populated.
- L326 _public prototype_ `Eigen::Matrix3Xf BindToRigidAttachment( const State& state, const std::string& jointName, const Eigen::Ref<const Eigen::Matrix3Xf>& bindVertices) const;` — Reverse direction: bind-frame vertices → current pose frame, treating them as a rigid attachment to `jointName`. Like `RigidAttachmentToBind`, this is independent of the state's `EvaluatePose` and `FloorOffsetApplied` flags.
- L345 _public prototype_ `PoseFrame ComposePoseFrame(const State& state) const;` — Return the posed bind+world matrices implied by `state`'s GuiControls, regardless of `EvaluatePose`. With the flag on, returns the cached matrices off the state; with it off, re-runs the nonlinear evaluator on a throwaway clone (the cached `WorldMatrices` equal `JointBindMatrices` in that mode and would otherwise collapse `bind * world^-1` to identity).
- L348 _public prototype_ `const std::vector<std::string>& GetRegionNames() const;` — @returns the region names
- L351 _public prototype_ `bool Blend(State& state, int RegionIndex, const std::vector<std::pair<float, const State*>>& States, BodyAttribute Type);` — Blends the states
- L354 _public prototype_ `bool GetMeasurements(Eigen::Ref<const Eigen::Matrix<float, 3, -1>> combinedBodyAndFaceVertices, Eigen::VectorXf& measurements, std::vector<std::string>& measurementNames) const;` — Calculate measurements on the combined body vertices
- L357 _public prototype_ `bool GetMeasurements(Eigen::Ref<const Eigen::Matrix<float, 3, -1>> faceVertices, Eigen::Ref<const Eigen::Matrix<float, 3, -1>> bodyVertices, Eigen::VectorXf& measurements, std::vector<std::string>& measurementNames) const;` — Calculate measurements on the body and face vertices
- L360 _public prototype_ `int GetNumLOD0MeshVertices(bool bInCombined) const;` — Get the number of mesh vertices for LOD 0, either for the standalone body, or the combined body
- L363 _public prototype_ `const Eigen::Matrix<int, 3, -1>& GetMeshTriangles(int lod) const;` — Get the mesh triangle indices for LOD
- L366 _public prototype_ `std::vector<std::string> GetPartWeightNames() const;` — Get the names of all available part weights (masks)
- L369 _public prototype_ `const VertexWeights<float>* GetPartWeight(const std::string& name) const;` — Get a specific part weight by name, returns nullptr if not found
- L374 _public prototype_ `void SetBodyBlendMask(const VertexWeights<float>& mask);` — Set the body-blend mask (alpha=1 pure body, alpha=0 pure face, soft ramp across the neck seam). Used by AdaptNeckSeam to define pinned boundary values outside the ring band. Indexed against combined-mesh vertices.
- L375 _public prototype_ `const VertexWeights<float>* GetBodyBlendMask() const;`
- L378 _public prototype_ `const std::vector<Keypoint>& GetKeypoints() const;` — Get the list of default keypoints
- L381 _private prototype_ `void UpdateSkinningAndRBF(const Eigen::VectorXf& rawControls, const Eigen::VectorXf& joints, std::shared_ptr<BodyGeometry<float>> poseLogic, std::shared_ptr<BodyLogic<float>> poseGeometry) const;`
- L386 _private prototype_ `void ComputePosedRBFJointGroups(const State& State, dna::Writer* InOutDnaWriter) const;` — Compute re-linearized RBF joint group values for posed DNA export. Evaluates the Jacobian of WorldMatrices w.r.t. RBF controls at the current pose operating point using central finite differences, then writes the result to the DNA writer.
- L390 _private member_ `Private* m;`

#### struct `BodyShapeEditor::Keypoint`  
`struct Keypoint`  
_L52-56_
- L54 _public member_ `int index = 0;`
- L55 _public member_ `std::string name;`

#### enum `BodyShapeEditor::BodyAttribute`  
`enum class BodyAttribute`  
_L58-63_
- L60 _public enumerator_ `Skeleton`
- L61 _public enumerator_ `Shape`
- L62 _public enumerator_ `Both`

#### enum `BodyShapeEditor::CalcStrategy`  
`enum class CalcStrategy`  
_L117-122_
- desc: Body-geometry computation strategy. Independent of the EvaluatePose flag — applying the pose and the path used to compute shape are orthogonal, even if the public EvaluateState entry point currently pairs them. Auto:      defer to State::EvaluatePose (true → Nonlinear, false → Linear). Default — preserves existing call-site behavior. Linear:    identityVertexEvaluationMatrix approximation + a closed- form root pose application. Fast. Nonlinear: full EvaluateBodyGeometry skinning (RBF + twist/swing). Highest fidelity.
- L119 _public enumerator_ `Auto`
- L120 _public enumerator_ `Linear`
- L121 _public enumerator_ `Nonlinear`

#### struct `BodyShapeEditor::FitToTargetOptions`  
`struct FitToTargetOptions`  
_L159-163_
- L160 _public member_ `int iterations = 20;`
- L161 _public member_ `float epsilon1 = 1e-3f;`
- L162 _public member_ `float epsilon2 = 1e-3f;`

#### struct `BodyShapeEditor::FacePlaneResult`  
`struct FacePlaneResult`  
_L181-189_
- L183 _public member_ `Camera<float> camera;`
- L184 _public member_ `Eigen::Vector3f centroid = Eigen::Vector3f::Zero();`
- L185 _public member_ `Eigen::Vector3f normal = Eigen::Vector3f::Zero();`
- L186 _public member_ `float radius = 0;`
- L187 _public member_ `std::vector<Eigen::Vector3f> positions;`
- L188 _public member_ `bool valid = false;`

#### struct `BodyShapeEditor::PoseFrame`  
`struct PoseFrame`  
_L333-337_
- desc: Bind+world matrix pair for one evaluation, used to drive the rigid-attachment helpers above.
- L335 _public member_ `std::vector<Eigen::Transform<float, 3, Eigen::Affine>> bind;`
- L336 _public member_ `std::vector<Eigen::Transform<float, 3, Eigen::Affine>> world;`

#### class `BodyShapeEditor::State`  
`class BodyShapeEditor::State`  
_L394-477_
- L397 _private prototype_ `State();`
- L400 _public prototype_ `~State();`
- L401 _public prototype_ `State(const State&);`
- L403 _public prototype_ `const Mesh<float>& GetMesh(int lod) const;`
- L404 _public prototype_ `const std::vector<Eigen::Transform<float, 3, Eigen::Affine>>& GetJointBindMatrices() const;`
- L405 _public prototype_ `const std::vector<Eigen::Transform<float, 3, Eigen::Affine>>& GetWorldMatrices() const;`
- L406 _public prototype_ `const Eigen::VectorX<float>& GetNamedConstraintMeasurements() const;`
- L407 _public prototype_ `const Eigen::VectorX<float>& GetCustomPose() const;`
- L408 _public prototype_ `Eigen::Matrix3Xf GetContourVertices(int ConstraintIndex) const;`
- L409 _public prototype_ `Eigen::Matrix3Xf GetContourDebugVertices(int ConstraintIndex) const;`
- L411 _public prototype_ `void Reset();`
- L413 _public prototype_ `int GetConstraintNum() const;`
- L414 _public prototype_ `const std::string& GetConstraintName(int ConstraintIndex) const;`
- L416 _public prototype_ `bool GetConstraintTarget(int ConstraintIndex, float& OutTarget) const;`
- L417 _public prototype_ `void SetConstraintTarget(int ConstraintIndex, float Target);`
- L418 _public prototype_ `void RemoveConstraintTarget(int ConstraintIndex);`
- L420 _public prototype_ `void SetVertexInfluenceWeights(const SparseMatrix<float>& vertexInfluenceWeights);`
- L422 _public prototype_ `float VertexDeltaScale() const;`
- L423 _public prototype_ `void SetVertexDeltaScale(float VertexDeltaScale);`
- L425 _public prototype_ `const Eigen::Matrix<float, 3, -1>& GetVertexDeltas() const;`
- L426 _public prototype_ `void SetVertexDeltas(const Eigen::Matrix<float, 3, -1>& vertexDeltas);`
- L427 _public prototype_ `const Eigen::Matrix<float, 3, -1>& GetBodySeamDelta() const;`
- L428 _public prototype_ `void SetBodySeamDelta(const Eigen::Matrix<float, 3, -1>& delta);`
- L430 _public prototype_ `void SetSymmetry(const bool sym);`
- L431 _public prototype_ `bool GetSymmetric() const;`
- L432 _public prototype_ `void SetSemanticWeight(float weight);`
- L433 _public prototype_ `float GetSemanticWeight();`
- L435 _public prototype_ `bool GetApplyFloorOffset() const;`
- L436 _public prototype_ `void SetApplyFloorOffset(bool floorOffset);`
- L438 _public prototype_ `bool GetEvaluatePose() const;`
- L443 _public prototype_ `void SetGuiControls(const Eigen::VectorXf& guiControls);`
- L444 _public prototype_ `const Eigen::VectorXf& GetGuiControls() const;`
- L445 _public prototype_ `const Eigen::VectorXf& GetRawControls() const;`
- L447 _public prototype_ `float GetUniformScale() const;`
- L448 _public prototype_ `void SetUniformScale(float scale);`
- L450 _public prototype_ `void SetLockedControlIndices(const std::vector<int>& indices);`
- L451 _public prototype_ `void ClearLockedControls();`
- L452 _public prototype_ `const std::vector<int>& GetLockedControlIndices() const;`
- L454 _public prototype_ `PatchBlendModel<float>::State* GetFaceState();`
- L455 _public prototype_ `const PatchBlendModel<float>::State* GetFaceState() const;`
- L457 _public prototype_ `float GetFaceBlend() const;`
- L458 _public prototype_ `void SetFaceBlend(float blend);`
- L460 _public prototype_ `float GetPoseBlend() const;`
- L461 _public prototype_ `void SetPoseBlend(float blend);`
- L465 _public prototype_ `float GetSeamBlend() const;` — Scales the BodySeamDelta contribution at evaluation time. Not serialized (always defaults to 1.0 on load, like PoseBlend). Clamped to [0,1].
- L466 _public prototype_ `void SetSeamBlend(float blend);`
- L469 _public prototype_ `State(State&&) = delete;`
- L470 _public prototype_ `State& operator=(State&&) = delete;`
- L471 _public prototype_ `State& operator=(const State&) = delete;`
- L476 _private member_ `std::unique_ptr<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/bodyshapeeditor/include/bodyshapeeditor/BodyShapeEditorTarget.h` (Private)


#### class `BodyShapeEditorTarget`  
`class BodyShapeEditorTarget`  
_L28-74_
- desc: Domain-owned fit target for all BSE solve entry points. Replaces the legacy POD `SolveTarget`. Holds up to three mesh slots (Head/Body/Combined) plus sparse keypoint/joint correspondences, 2D viewport constraints, and face landmark constraints. Accessors only — fields are pimpl'd.
- L33 _public prototype_ `BodyShapeEditorTarget();`
- L34 _public prototype_ `~BodyShapeEditorTarget();`
- L35 _public prototype_ `BodyShapeEditorTarget(const BodyShapeEditorTarget&);`
- L36 _public prototype_ `BodyShapeEditorTarget& operator=(const BodyShapeEditorTarget&);`
- L37 _public prototype_ `BodyShapeEditorTarget(BodyShapeEditorTarget&&) noexcept;`
- L38 _public prototype_ `BodyShapeEditorTarget& operator=(BodyShapeEditorTarget&&) noexcept;`
- L40 _public prototype_ `BodyShapeEditorTarget& SetMesh(MeshSlot slot, std::shared_ptr<const Mesh<float>> mesh);`
- L41 _public prototype_ `BodyShapeEditorTarget& AddKeypoint(int vertex, Eigen::Vector3f pos);`
- L42 _public prototype_ `BodyShapeEditorTarget& AddJointCorrespondence(int vertex, Eigen::Vector3f pos);`
- L43 _public prototype_ `BodyShapeEditorTarget& SetLandmarks2D(std::shared_ptr<LandmarkConstraints2D<float>> lm);`
- L44 _public prototype_ `BodyShapeEditorTarget& AddViewportConstraints(Eigen::Matrix4f mvp, std::vector<Constraint2D> c);`
- L45 _public prototype_ `BodyShapeEditorTarget& AddViewportConstraints(std::vector<ViewportConstraints2D> list);`
- L46 _public prototype_ `BodyShapeEditorTarget& SetJointRotations(av::ConstArrayView<float> jointRotations);`
- L50 _public prototype_ `std::shared_ptr<const Mesh<float>> MeshFor(MeshSlot slot) const;` — Returns the mesh set on `slot` if present, otherwise the first-set slot's mesh (the "primary" mesh). Returns nullptr if no slot is set.
- L52 _public prototype_ `std::shared_ptr<const Mesh<float>> PrimaryMesh() const;` — Shortcut: first-set slot's mesh, or nullptr if no slot set.
- L53 _public prototype_ `bool HasMesh(MeshSlot slot) const;`
- L54 _public prototype_ `bool HasAnyMesh() const;`
- L56 _public prototype_ `const std::vector<std::pair<int, Eigen::Vector3f>>& Keypoints() const;`
- L57 _public prototype_ `const std::vector<std::pair<int, Eigen::Vector3f>>& Joints() const;`
- L58 _public prototype_ `av::ConstArrayView<float> JointRotations() const;`
- L59 _public prototype_ `const std::vector<ViewportConstraints2D>& Viewports() const;`
- L60 _public prototype_ `std::shared_ptr<LandmarkConstraints2D<float>> Landmarks2D() const;`
- L69 _public prototype_ `const Eigen::VectorXf& NonDegenerateMaskFor(MeshSlot slot) const;` — Per-vertex weight mask (0 / 1) flagging non-degenerate target vertices. Computed and cached automatically when SetMesh is called: a vertex's mask is 0 iff every incident triangle has area < minArea (default 1e-8 in mesh units), 1 otherwise. Solvers can feed this straight into ICPConstraints::SetTargetWeights or LandmarkConstraints to skip pinch points / collapsed verts that survived a noisy reconstruction. Returns an empty vector when the slot has no mesh.
- L73 _private member_ `std::unique_ptr<Impl> m;`

#### enum `BodyShapeEditorTarget::MeshSlot`  
`enum class MeshSlot : uint8_t`  
_L31-31_
- L31 _public enumerator_ `enum class MeshSlot : uint8_t { Head = 0, Body = 1, Combined = 2 }; BodyShapeEditorTarget(); ~BodyShapeEditorTarget(); BodyShapeEditorTarget(const BodyShapeEditorTarget&); BodyShapeEditorTarget& operator=(const BodyShapeEditorTarget&); BodyShapeEditorTarget(BodyShapeEditorTarget&&) noexcept; BodyShapeEditorTarget& operator=(BodyShapeEditorTarget&&) noexcept;`
- L31 _public enumerator_ `enum class MeshSlot : uint8_t { Head = 0, Body = 1, Combined = 2 }; BodyShapeEditorTarget(); ~BodyShapeEditorTarget(); BodyShapeEditorTarget(const BodyShapeEditorTarget&); BodyShapeEditorTarget& operator=(const BodyShapeEditorTarget&); BodyShapeEditorTarget(BodyShapeEditorTarget&&) noexcept; BodyShapeEditorTarget& operator=(BodyShapeEditorTarget&&) noexcept;`
- L31 _public enumerator_ `enum class MeshSlot : uint8_t { Head = 0, Body = 1, Combined = 2 }; BodyShapeEditorTarget(); ~BodyShapeEditorTarget(); BodyShapeEditorTarget(const BodyShapeEditorTarget&); BodyShapeEditorTarget& operator=(const BodyShapeEditorTarget&); BodyShapeEditorTarget(BodyShapeEditorTarget&&) noexcept; BodyShapeEditorTarget& operator=(BodyShapeEditorTarget&&) noexcept;`

#### Free symbols / members of external scopes

- L22 _typedef_ `using ViewportConstraints2D = std::pair<Eigen::Matrix4f, std::vector<Constraint2D>>;` — Declared in BodyShapeEditor.h — redeclare the alias here so this header is standalone.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/bodyshapeeditor/include/bodyshapeeditor/BodySolveConfiguration.h` (Private)


#### struct `BodySolveConfiguration`  
`struct BodySolveConfiguration`  
_L16-30_
- L17 _public member_ `Configuration body;`
- L18 _public member_ `Configuration face;`
- L19 _public member_ `Configuration refinement;`
- L20 _public member_ `Eigen::VectorXf vertexMask;` — single mask shared across all sub-solvers
- L26 _public member_ `bool lockScale = false;` — Runtime flag — when true, SolveForArbitraryMeshWithICP pins the uniform scaleVar as constant (MakeConstant) so only the pose + proportions solve and ScaleFactor stays wherever AlignToTargetMesh left it. Not serialised via Configuration because it's a per-invocation toggle, not a knob.
- L28 _public prototype_ `BodySolveConfiguration();`
- L29 _public prototype_ `BodySolveConfiguration(Configuration body, Configuration face, Configuration refinement);`

#### enum `SeamLockSide`  
`enum class SeamLockSide : int`  
_L42-42_
- desc: A single step in a RunPipeline execution. Masks are resolved + combined into `config.vertexMask` by the app before handoff. `lockedControls` is the runtime-resolved set of locked indices computed from `controlGroupNames` via the app's ControlGroupLibrary; BSE::RunPipeline reads `lockedControls`, not `controlGroupNames`. Which side of the neck seam stays locked during AdaptNeckSeam. - None: seam is free, both sides relax between outer pins (default). - Face: face outside the seam stays at the face-solve offset; body ring adapts. - Body: body outside the seam stays at 0; face ring adapts. Useful e.g. when template-fitting to a body-only target and the body must stay as-is.
- L42 _public enumerator_ `enum class SeamLockSide : int { None = 0, Face = 1, Body = 2 }; enum class StepKind : int { BodySolve = 0, FaceSolve = 1,` — A single step in a RunPipeline execution. Masks are resolved + combined into `config.vertexMask` by the app before handoff. `lockedControls` is the runtime-resolved set of locked indices computed from `controlGroupNames` via the app's ControlGroupLibrary; BSE::RunPipeline reads `lockedControls`, not `controlGroupNames`. Which side of the neck seam stays locked during AdaptNeckSeam. - None: seam is free, both sides relax between outer pins (default). - Face: face outside the seam stays at the face-solve offset; body ring adapts. - Body: body outside the seam stays at 0; face ring adapts. Useful e.g. when template-fitting to a body-only target and the body must stay as-is.
- L42 _public enumerator_ `enum class SeamLockSide : int { None = 0, Face = 1, Body = 2 }; enum class StepKind : int { BodySolve = 0, FaceSolve = 1,` — A single step in a RunPipeline execution. Masks are resolved + combined into `config.vertexMask` by the app before handoff. `lockedControls` is the runtime-resolved set of locked indices computed from `controlGroupNames` via the app's ControlGroupLibrary; BSE::RunPipeline reads `lockedControls`, not `controlGroupNames`. Which side of the neck seam stays locked during AdaptNeckSeam. - None: seam is free, both sides relax between outer pins (default). - Face: face outside the seam stays at the face-solve offset; body ring adapts. - Body: body outside the seam stays at 0; face ring adapts. Useful e.g. when template-fitting to a body-only target and the body must stay as-is.
- L42 _public enumerator_ `enum class SeamLockSide : int { None = 0, Face = 1, Body = 2 }; enum class StepKind : int { BodySolve = 0, FaceSolve = 1,` — A single step in a RunPipeline execution. Masks are resolved + combined into `config.vertexMask` by the app before handoff. `lockedControls` is the runtime-resolved set of locked indices computed from `controlGroupNames` via the app's ControlGroupLibrary; BSE::RunPipeline reads `lockedControls`, not `controlGroupNames`. Which side of the neck seam stays locked during AdaptNeckSeam. - None: seam is free, both sides relax between outer pins (default). - Face: face outside the seam stays at the face-solve offset; body ring adapts. - Body: body outside the seam stays at 0; face ring adapts. Useful e.g. when template-fitting to a body-only target and the body must stay as-is.

#### enum `StepKind`  
`enum class StepKind : int`  
_L47-53_
- desc: One kind per SolveStep. RunPipeline dispatches by this. Fields on SolveStep that only make sense for a particular kind (alignRegion / seam* / …) are ignored when `kind` is something else.
- L48 _public enumerator_ `BodySolve = 0`
- L49 _public enumerator_ `FaceSolve = 1`
- L50 _public enumerator_ `Align = 2`
- L51 _public enumerator_ `AdaptNeck = 3`
- L52 _public enumerator_ `Refine = 4`

#### struct `SolveStep`  
`struct SolveStep`  
_L55-91_
- L56 _public member_ `std::string name;`
- L57 _public member_ `bool enabled = true;`
- L58 _public member_ `StepKind kind = StepKind::BodySolve;`
- L61 _public member_ `std::vector<std::string> maskNames;` — Common — used by most kinds.
- L62 _public member_ `BodyShapeEditorTarget::MeshSlot targetSlot =` — which scan slot to solve against
- L64 _public member_ `std::vector<std::string> controlGroupNames;` — UI-facing, JSON-persisted
- L65 _public member_ `std::vector<int> lockedControls;` — runtime-resolved, not persisted
- L66 _public member_ `std::map<std::string, float> initialControls;`
- L73 _public member_ `Configuration config{"", {}};` — Per-step solver config. A single Configuration object, sized/named for the step's kind (CreateBodySolveConfig / CreateFaceSolveConfig / CreateRefinementConfig). Empty for Align / AdaptNeck kinds — those carry their params as fields below. Default-initialised to an empty Configuration so SolveStep is default-constructible.
- L76 _public member_ `Eigen::VectorXf vertexMask;` — Per-step vertex mask (resolved from `maskNames` by the app before dispatch).
- L81 _public member_ `bool lockScale = false;` — Kind::BodySolve — if true, the uniform scaleVar is locked during solve (pose + proportions still optimise). Lets the Align-produced scale stick through later passes like finger_foot that should only refine pose.
- L87 _public member_ `SeamLockSide seamLockSide = SeamLockSide::None;` — Kind::AdaptNeck.
- L88 _public member_ `int seamRings = 10;`
- L89 _public member_ `int seamIterations = 3;`
- L90 _public member_ `float seamLaplacian = 1.5f;` — SOR relaxation factor

#### Free symbols / members of external scopes

- L93 _prototype_ `Configuration CreateBodySolveConfig();`
- L94 _prototype_ `Configuration CreateFaceSolveConfig();`
- L95 _prototype_ `Configuration CreateRefinementConfig();`
- L97 _prototype_ `JsonElement SolveConfigurationToJson(const BodySolveConfiguration& cfg);`
- L98 _prototype_ `bool SolveConfigurationFromJson(BodySolveConfiguration& cfg, const JsonElement& json);`
- L100 _prototype_ `JsonElement ControlGroupsToJson(const std::map<std::string, std::vector<int>>& groups);`
- L101 _prototype_ `bool ControlGroupsFromJson(std::map<std::string, std::vector<int>>& groups, const JsonElement& json);`
- L109 _prototype_ `JsonElement PipelineToJson(const std::vector<SolveStep>& steps);` — Pipeline JSON is versioned. New writes emit version:2 with targetSlot as int. Legacy (version unset / <2) input is migrated: - targetMeshName string → targetSlot enum - runScale=true → runAlign=true, alignLockScale=false - configPreset (name ref) → dropped (no preset table in v2) - legacy maskName / masks arrays merged into maskNames
- L110 _prototype_ `bool PipelineFromJson(std::vector<SolveStep>& steps, const JsonElement& json);`
- L112 _prototype_ `JsonElement PipelinePresetsToJson(const std::map<std::string, std::vector<SolveStep>>& pipelines);`
- L113 _prototype_ `bool PipelinePresetsFromJson(std::map<std::string, std::vector<SolveStep>>& pipelines, const JsonElement& json);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/bodyshapeeditor/include/bodyshapeeditor/PipelineBundle.h` (Private)


#### struct `PipelineBundle`  
`struct PipelineBundle`  
_L30-37_
- L32 _public member_ `std::map<std::string, std::vector<SolveStep>> pipelines;`
- L33 _public member_ `std::string activePipeline;`
- L34 _public member_ `std::map<std::string, std::vector<int>> controlGroups;`
- L35 _public member_ `std::map<std::string, VertexWeights<float>> masks;`
- L36 _public member_ `std::map<std::string, std::vector<std::string>> maskGroups;`

#### Free symbols / members of external scopes

- L41 _prototype_ `bool SavePipelineBundle(const std::string& jsonPath, const PipelineBundle& bundle);` — Write <jsonPath> (JSON config) + <jsonPath>.masks.bin (binary weights sidecar). Returns true on success. If the mask map is empty the binary sidecar is not written.
- L52 _prototype_ `bool LoadPipelineBundle(const std::string& jsonPath, BodyShapeEditor* bse, PipelineBundle& bundle);` — If `bse` is non-null its part weights are ingested into bundle.masks (padded to the body vertex count). This mirrors the behaviour of the scan-fitting app's MaskLibrary so callers don't have to know which masks are user-authored and which come from BSE parts — everything resolves through bundle.masks by name.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/bodyshapeeditor/include/bodyshapeeditor/SerializationHelper.h` (Private)


#### Free symbols / members of external scopes

- L12 _typedef_ `using MHCBinaryInputArchive = terse::BinaryInputArchive<trio::BoundedIOStream, std::uint32_t, std::uint32_t, terse::Endianness::Little>;`
- L13 _typedef_ `using MHCBinaryOutputArchive = terse::BinaryOutputArchive<trio::BoundedIOStream, std::uint32_t, std::uint32_t, terse::Endianness::Little>;`
- L16 _function_ `template <typename T, int R, int C> void SerializeEigenMatrix(MHCBinaryOutputArchive& archive, trio::BoundedIOStream* OutputStream, const Eigen::Matrix<T, R, C>& mat)`
- L43 _function_ `template <typename T, int R, int C> void DeserializeEigenMatrix(MHCBinaryInputArchive& archive, trio::BoundedIOStream* InputStream, Eigen::Matrix<T, R, C>& mat)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/bodyshapeeditor/include/bodyshapeeditor/WeightSchedule.h` (Private)


#### enum `ScheduleCurve`  
`enum class ScheduleCurve`  
_L13-13_
- L13 _public enumerator_ `enum class ScheduleCurve { Static, Linear, Quadratic, Log }; struct WeightSchedule { float start = 1.0f; float end = 1.0f; ScheduleCurve curve = ScheduleCurve::Static; float Evaluate(int iter, int totalIters) const`
- L13 _public enumerator_ `enum class ScheduleCurve { Static, Linear, Quadratic, Log }; struct WeightSchedule { float start = 1.0f; float end = 1.0f; ScheduleCurve curve = ScheduleCurve::Static; float Evaluate(int iter, int totalIters) const`
- L13 _public enumerator_ `enum class ScheduleCurve { Static, Linear, Quadratic, Log }; struct WeightSchedule { float start = 1.0f; float end = 1.0f; ScheduleCurve curve = ScheduleCurve::Static; float Evaluate(int iter, int totalIters) const`
- L13 _public enumerator_ `enum class ScheduleCurve { Static, Linear, Quadratic, Log }; struct WeightSchedule { float start = 1.0f; float end = 1.0f; ScheduleCurve curve = ScheduleCurve::Static; float Evaluate(int iter, int totalIters) const`

#### struct `WeightSchedule`  
`struct WeightSchedule`  
_L15-71_
- L16 _public member_ `float start = 1.0f;`
- L17 _public member_ `float end = 1.0f;`
- L18 _public member_ `ScheduleCurve curve = ScheduleCurve::Static;`
- L20 _public function_ `float Evaluate(int iter, int totalIters) const`
- L30 _public function_ `JsonElement ToJson() const`
- L42 _public function_ `void FromJson(const JsonElement& j)`
- L54 _public function_ `static const char* CurveToString(ScheduleCurve c)`
- L64 _public function_ `static ScheduleCurve CurveFromString(const std::string& s)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/bodyshapeeditor/src/BodyMeasurementHelper.h` (Private)


#### enum `BarycentricCoordinatesType`  
`enum class BarycentricCoordinatesType`  
_L14-20_
- L16 _public enumerator_ `Invalid`
- L17 _public enumerator_ `Vertex`
- L18 _public enumerator_ `Edge`
- L19 _public enumerator_ `Face`

#### struct `BCoordExt`  
`struct BCoordExt`  
_L22-30_
- L24 _public member_ `BarycentricCoordinates<float> bc;`
- L25 _public member_ `BarycentricCoordinatesType type{BarycentricCoordinatesType::Invalid};`
- L26 _public function_ `bool IsValid() const`
- L27 _public function_ `bool IsVertex() const`
- L28 _public function_ `bool IsEdge() const`
- L29 _public function_ `bool IsFace() const`

#### Free symbols / members of external scopes

- L33 _function_ `static inline float PointToLineDistanceSquared(const Eigen::Vector3f& query, const Eigen::Vector3f& origin, const Eigen::Vector3f& direction)` — @returns the squared distance of point @p query to the line defined by @p origin and @p direction
- L40 _function_ `static inline std::pair<float, float> PointToSegmentSquared(const Eigen::Vector3f& query, const Eigen::Vector3f& a, const Eigen::Vector3f& b)` — @returns the squared distance of point @p query to the segment defined by @p a and @p b
- L56 _function_ `static inline std::pair<float, float> SegmentToLineDistanceSquared(const Eigen::Vector3f& a, const Eigen::Vector3f& b, const Eigen::Vector3f& origin, const Eigen::Vector3f& direction)` — @returns the closest point on segment @p a and @p b (as coefficient t) and its square distance to the line defined by @p origin and @p direction
- L73 _function_ `static inline Eigen::Vector3f ClosestPointOnTriangle(const Eigen::Vector3f& p, const Eigen::Vector3f& a, const Eigen::Vector3f& b, const Eigen::Vector3f& c)` — @returns the barycentric coordinates of the point in the triangle @p a, @p b, and @p c that is closest to @p p
- L100 _function_ `static inline std::pair<bool, Eigen::Vector3f> IntersectLineAndTriangle(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction, const Eigen::Vector3f& a, const Eigen::Vector3f& b, const Eigen::Vector3f& c)` — @brief Intersects the line defined by @p origin and @p direction with plane defined by @p a, @p b, and @p c and returns whether the line intersects and the barycentric coordinates of the intersection. @note the returned point is only the closest point on the triangle to the line if and only the line and point intersect (otherwise a vertex or edge may be closer to the line)
- L129 _function_ `static inline BCoordExt ClosestMeshCoordToPoint(const HalfEdgeMesh<float>& heMesh, const Eigen::Matrix<float, 3, -1>& vertices, int startVertexIndex, const Eigen::Vector3f& query)`
- L296 _function_ `static inline BCoordExt ClosestMeshCoordToLine(const HalfEdgeMesh<float>& heMesh, const Eigen::Matrix<float, 3, -1>& vertices, int startVertexIndex, const Eigen::Vector3f& origin, const Eigen::Vector3f& direction)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/Algorithm.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`
- L29 _function_ `template <class T> bool ConcatenateVectorsWithMatchingEndPointsAndUnknownDirection(const std::vector<T>& vector1, const std::vector<T>& vector2, std::vector<T>& mergedVector)` — Concatenates two vectors with undown direction along one matching end point (removing the duplicate). Fails if there is no matching end point or if either vector is empty.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/Common.h` (Private)


#### struct `always_false`  
`template <class T> struct always_false : std::false_type`  
_L13-13_
- inherits: `std::false_type`

#### Free symbols / members of external scopes

- L8 _macro_ `#define CARBON_SUPPRESS_UNUSED(x) (void)(x)`
- L19 _function_ `inline std::string from_u8string(const std::string &s)` — @brief support converting u8string to string as of C++20 based on https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1423r2.html: "Use explicit conversion functions"
- L24 _function_ `inline std::string from_u8string(std::string &&s)`
- L30 _function_ `inline std::string from_u8string(const std::u8string &s)`
- L36 _macro_ `#define FROM_U8STRING(x) TITAN_NAMESPACE::from_u8string(x).c_str()`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/Math.h` (Private)
_(no declarations extracted)_

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/common/Common.h` (Private)
_(no declarations extracted)_

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/common/Defs.h` (Private)


#### Free symbols / members of external scopes

- L5 _macro_ `#define CARBON_NAMESPACE_BEGIN(name) namespace name {`
- L6 _macro_ `#define CARBON_NAMESPACE_END(name) }`
- L9 _macro_ `#define TITAN_NAMESPACE epic::nls`
- L13 _macro_ `#define CARBON_SUPRESS_MS_WARNING(Warning)`
- L14 _macro_ `#define CARBON_REENABLE_MS_WARNING`
- L18 _macro_ `#define CARBON_DISABLE_EIGEN_WARNINGS THIRD_PARTY_INCLUDES_START // use UE warning suppression if we can`
- L19 _macro_ `#define CARBON_RENABLE_WARNINGS THIRD_PARTY_INCLUDES_END`
- L21 _macro_ `#define CARBON_DISABLE_EIGEN_WARNINGS \`
- L25 _macro_ `#define CARBON_RENABLE_WARNINGS \`
- L34 _macro_ `#define CARBON_RENABLE_WARNINGS __pragma(warning(pop))`
- L35 _macro_ `#define CARBON_SUPRESS_MS_WARNING(Warning) \`
- L38 _macro_ `#define CARBON_REENABLE_MS_WARNING CARBON_RENABLE_WARNINGS`
- L44 _macro_ `#define CARBON_RENABLE_WARNINGS _Pragma("GCC diagnostic pop")`
- L48 _macro_ `#define CARBON_DISABLE_EIGEN_WARNINGS`
- L49 _macro_ `#define CARBON_RENABLE_WARNINGS`
- L58 _macro_ `#define DEBUG_PRECONDITION(condition, message) (void)(condition)`
- L60 _macro_ `#define DEBUG_PRECONDITION(condition, message) if (!(condition)) throw std::runtime_error(message)`
- L66 _macro_ `#define EPIC_CARBON_API` — API symbol export import preprocessor defines. Currently Carbon is forced to be a static library, so no need for export/import defines
- L82 _macro_ `#define CARBON_PI 3.14159265358979323846 // pi` — CONSTANTS
- L84 _macro_ `#define CARBON_CRITICAL(...) { \`
- L92 _macro_ `#define CARBON_PRECONDITION(condition, ...) if (!(condition)) { \`
- L98 _macro_ `#define CARBON_POSTCONDITION(condition, ...) if (!(condition)) { \`
- L104 _macro_ `#define CARBON_ASSERT(condition, ...) if (!(condition)) { \`
- L111 _macro_ `#define CARBON_PRECONDITION(condition, ...) (void)(condition)`
- L112 _macro_ `#define CARBON_POSTCONDITION(condition, ...) (void)(condition)`
- L113 _macro_ `#define CARBON_ASSERT(condition, ...) (void)(condition)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/common/EigenDenseBackwardsCompatible.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Eigen`
- L15 _typedef_ `template <typename T> using Matrix2 = Matrix<T, 2, 2>;` (scope `Eigen`)
- L18 _typedef_ `template <typename T> using Matrix2X = Matrix<T, 2, Dynamic>;` (scope `Eigen`)
- L21 _typedef_ `template <typename T> using Matrix3 = Matrix<T, 3, 3>;` (scope `Eigen`)
- L24 _typedef_ `template <typename T> using Matrix3X = Matrix<T, 3, Dynamic>;` (scope `Eigen`)
- L27 _typedef_ `template <typename T> using Matrix4 = Matrix<T, 4, 4>;` (scope `Eigen`)
- L30 _typedef_ `template <typename T> using Matrix4X = Matrix<T, 4, Dynamic>;` (scope `Eigen`)
- L33 _typedef_ `template <typename T> using MatrixX = Matrix<T, Dynamic, Dynamic>;` (scope `Eigen`)
- L36 _typedef_ `template <typename T> using MatrixX2 = Matrix<T, Dynamic, 2>;` (scope `Eigen`)
- L39 _typedef_ `template <typename T> using MatrixX3 = Matrix<T, Dynamic, 3>;` (scope `Eigen`)
- L42 _typedef_ `template <typename T> using MatrixX4 = Matrix<T, Dynamic, 4>;` (scope `Eigen`)
- L45 _typedef_ `template <typename T, int Size> using RowVector = Matrix<T, 1, Size>;` (scope `Eigen`)
- L48 _typedef_ `template <typename T> using RowVector2 = RowVector<T, 2>;` (scope `Eigen`)
- L51 _typedef_ `template <typename T> using RowVector3 = RowVector<T, 3>;` (scope `Eigen`)
- L54 _typedef_ `template <typename T> using RowVector4 = RowVector<T, 4>;` (scope `Eigen`)
- L57 _typedef_ `template <typename T> using RowVectorX = RowVector<T, Dynamic>;` (scope `Eigen`)
- L60 _typedef_ `template <typename T, int Size> using Vector = Matrix<T, Size, 1>;` (scope `Eigen`)
- L63 _typedef_ `template <typename T> using Vector2 = Vector<T, 2>;` (scope `Eigen`)
- L66 _typedef_ `template <typename T> using Vector3 = Vector<T, 3>;` (scope `Eigen`)
- L69 _typedef_ `template <typename T> using Vector4 = Vector<T, 4>;` (scope `Eigen`)
- L72 _typedef_ `template <typename T> using VectorX = Vector<T, Dynamic>;` (scope `Eigen`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/common/External.h` (Private)
_(no declarations extracted)_

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/common/Format.h` (Private)


#### Free symbols / members of external scopes

- L22 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::fmt)`
- L41 _function_ `template<> inline std::string to_string<bool>(const bool& value)` — ! Specialization for bool type
- L48 _function_ `template<typename ... Types> std::string format(Types&& ... args)`
- L53 _function_ `template<typename ... Types> void print(Types&& ... args)`
- L60 _function_ `template<typename ... Types> std::string BasicFormat(const std::string& str, Types&& ... args)`
- L88 _function_ `inline std::string format()`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/common/Integration.h` (Private)


#### struct `Integration`  
`struct Integration`  
_L13-17_
- desc: @Brief Integration structure wraps objects that implements core functionalities from the external client.
- L15 _public member_ `Logger logger{};`
- L16 _public member_ `pma::MemoryResource* memoryResource{};`

#### Free symbols / members of external scopes

- L24 _prototype_ `Integration& GetIntegrationParams();` — @Brief Gets/Sets Integration struct to be used in the core tech lib @returns Integraton parameters - singleton instance.
- L29 _macro_ `#define LOGGER TITAN_NAMESPACE::GetIntegrationParams().logger` — Singletone instances - recommended usage is providing object through DI
- L30 _macro_ `#define MEM_RESOURCE TITAN_NAMESPACE::GetIntegrationParams().memoryResource`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/common/Log.h` (Private)


#### Free symbols / members of external scopes

- L10 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`
- L26 _macro_ `#define LOG_INTERNAL(LogLevel,...) LOGGER.Log(LogLevel, "(%s, l%d): %s\n\0", TITAN_NAMESPACE::ConstexprBasename(__FILE__), static_cast<int>(__LINE__),\`
- L29 _macro_ `#define LOG_CONDITION(format,condition,args) LOGGER.Log(TITAN_NAMESPACE::LogLevel::ERR, format, condition, TITAN_NAMESPACE::ConstexprBasename(__FILE__), static_cast<int>(__LINE__),args)`
- L31 _macro_ `#define LOG_INFO(...) LOGGER.Log(TITAN_NAMESPACE::LogLevel::INFO, "%s\n\0", TITAN_NAMESPACE::fmt::format(__VA_ARGS__).c_str())`
- L33 _macro_ `#define LOG_WARNING(...) LOG_INTERNAL(TITAN_NAMESPACE::LogLevel::WARNING, __VA_ARGS__)`
- L35 _macro_ `#define LOG_ERROR(...) LOG_INTERNAL(TITAN_NAMESPACE::LogLevel::ERR, __VA_ARGS__)`
- L37 _macro_ `#define LOG_CRITICAL(...) LOG_INTERNAL(TITAN_NAMESPACE::LogLevel::CRITICAL, __VA_ARGS__);`
- L39 _macro_ `#define LOG_VERBOSE(...) LOG_INTERNAL(TITAN_NAMESPACE::LogLevel::VERBOSE, __VA_ARGS__)`
- L41 _macro_ `#define LOG_FATAL(...) LOG_INTERNAL(TITAN_NAMESPACE::LogLevel::FATAL, __VA_ARGS__)`
- L43 _macro_ `#define LOG_PRECONDITION(failedPrecondition, ...) LOG_CONDITION("FAILED PRECONDITION - %s in (%s, l%d): %s\n\0", TITAN_NAMESPACE::fmt::to_string(failedPrecondition).c_str(), TITAN_NAMESPACE::fmt::format(__VA_ARGS__).c_str());`
- L45 _macro_ `#define LOG_POSTCONDITION(failedPostcondition, ...) LOG_CONDITION("FAILED POSTCONDITION - %s in (%s, l%d): %s\n\0", TITAN_NAMESPACE::fmt::to_string(failedPostcondition).c_str(), TITAN_NAMESPACE::fmt::format(__VA_ARGS__).c_str());`
- L47 _macro_ `#define LOG_ASSERT(failedAssert, ...) LOG_CONDITION("FAILED ASSERT - %s in (%s, l%d): %s\n\0", TITAN_NAMESPACE::fmt::to_string(failedAssert).c_str(), TITAN_NAMESPACE::fmt::format(__VA_ARGS__).c_str());`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/common/Logger.h` (Private)


#### enum `LogLevel`  
`enum class LogLevel`  
_L9-18_
- L11 _public enumerator_ `VERBOSE = 0`
- L12 _public enumerator_ `WARNING = 1`
- L13 _public enumerator_ `INFO = 2`
- L14 _public enumerator_ `DEBUG = 3`
- L15 _public enumerator_ `ERR = 4`
- L16 _public enumerator_ `CRITICAL = 5`
- L17 _public enumerator_ `FATAL = 6`

#### class `Logger`  
`class Logger final`  
_L27-77_
- desc: @Brief Logger class is simple logging functionality wrapper. Its main purpose is integration of logging functionality from external system (for example UE)
- L34 _public prototype_ `Logger() noexcept;` — Default Constructor.
- L42 _public prototype_ `Logger(LogFunction logFunction_) noexcept;` — Constructor. @param[in] logFunction_ logging function provided from the external system. Initially set to DefaultLogger.
- L47 _public prototype_ `~Logger() noexcept;` — Destructor.
- L61 _public function_ `template<typename ...ARGS> void Log(LogLevel logLevel, const char* format, ARGS&& ...params)` — Send message to log system. @param[in] logLevel Log level of message. @param[in] format format string. @param[in] params multiple parameters to be embeded in the format string. @note C style formatting syntax needs to be applied
- L70 _public function_ `void SetVerbose(bool enable)` — Set whether to log verbose output
- L73 _private prototype_ `static void DefaultLogger(LogLevel logLevel, const char* format, ...);`
- L75 _private member_ `LogFunction m_logFunction{ DefaultLogger };`
- L76 _private member_ `bool m_logVerbose{true};`

#### Free symbols / members of external scopes

- L20 _typedef_ `using LogFunction = void(*)(LogLevel , const char* , ...);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/common/Pimpl.h` (Private)


#### class `Pimpl`  
`template <class T, class Deleter = std::default_delete<T>> class Pimpl`  
_L21-41_
- desc: Most basic const-forwarding pointer wrapper for use with the Pimpl programming technique. https://en.cppreference.com/w/cpp/language/pimpl. Use a custom delete Deleter = void(*)(T*) when the class does not have a destructor. E.g. in the cpp class use Pimpl(std::unique_ptr<T, void(*)(T*)>(new T, [](T* ptr) {std::default_delete<T>()(ptr);})) @warning does not work with class that have a DLL interface.
- L24 _public function_ `Pimpl(std::unique_ptr<T, Deleter>&& obj) : m_ptr(std::move(obj))`
- L25 _public function_ `Pimpl(T* ptr) : m_ptr(ptr)`
- L26 _public prototype_ `~Pimpl() = default;`
- L27 _public prototype_ `Pimpl(Pimpl&&) = default;`
- L28 _public prototype_ `Pimpl(const Pimpl&) = delete;`
- L29 _public prototype_ `Pimpl& operator=(Pimpl&&) = default;`
- L30 _public prototype_ `Pimpl& operator=(const Pimpl&) = delete;`
- L32 _public function_ `constexpr T* operator->()`
- L33 _public function_ `constexpr const T* operator->() const`
- L34 _public function_ `constexpr T& operator*()`
- L35 _public function_ `constexpr const T& operator*() const`
- L36 _public function_ `constexpr T* Get()`
- L37 _public function_ `constexpr const T* Get() const`
- L40 _private member_ `std::unique_ptr<T, Deleter> m_ptr;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/data/CameraModelOpenCV.h` (Private)


#### class `CameraModelOpenCV`  
`template<class T> class CameraModelOpenCV : public CameraModelPinhole<T>`  
_L30-79_
- inherits: `CameraModelPinhole<T>`
- L46 _public prototype_ `CameraModelOpenCV() noexcept;`
- L56 _public prototype_ `virtual ~CameraModelOpenCV() noexcept;`
- L65 _public prototype_ `const Eigen::Vector<T, 5>& GetDistortionParams() const noexcept;`
- L74 _public prototype_ `void SetDistortionParams(const Eigen::Vector<T, 5>& distortion) noexcept;`
- L78 _private member_ `Eigen::Vector<T, 5> m_distortion;` — OpenCV format distortion parameters (k1, k2, p1, p2, k3)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/data/CameraModelPinhole.h` (Private)


#### class `CameraModelPinhole`  
`template<class T> class CameraModelPinhole`  
_L35-192_
- L50 _public prototype_ `CameraModelPinhole() noexcept;`
- L60 _public prototype_ `virtual ~CameraModelPinhole() noexcept;`
- L68 _public prototype_ `const Eigen::Matrix<T, 3, 3, Eigen::DontAlign>& GetIntrinsics() const noexcept;`
- L79 _public prototype_ `void SetIntrinsics(const Eigen::Matrix<T, 3, 3, Eigen::DontAlign>& intrinsics);`
- L90 _public prototype_ `const Eigen::Matrix<T, 3, 4, Eigen::DontAlign>& GetExtrinsics() const noexcept;`
- L101 _public prototype_ `void SetExtrinsics(const Eigen::Matrix<T, 3, 4, Eigen::DontAlign>& extrinsics);`
- L110 _public prototype_ `int GetWidth() const noexcept;`
- L119 _public prototype_ `void SetWidth(const int width) noexcept;`
- L128 _public prototype_ `int GetHeight() const noexcept;`
- L137 _public prototype_ `void SetHeight(const int height) noexcept;`
- L147 _public prototype_ `std::string GetLabel() const noexcept;`
- L156 _public prototype_ `void SetLabel(std::string label) noexcept;`
- L165 _public prototype_ `std::string GetModel() const noexcept;`
- L174 _public prototype_ `void SetModel(std::string model) noexcept;`
- L178 _protected member_ `Eigen::Matrix<T, 3, 3, Eigen::DontAlign> m_intrinsics;` — Intrinsics matrix
- L181 _protected member_ `Eigen::Matrix<T, 3, 4, Eigen::DontAlign> m_extrinsics;` — Extrinsics matrix [R|t]
- L184 _protected member_ `int m_width;` — Image dimensions
- L185 _protected member_ `int m_height;`
- L188 _protected member_ `std::string m_label;` — Label of the camera
- L191 _protected member_ `std::string m_model;` — Camera model

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/geometry/AABBTree.h` (Private)


#### struct `AABBTreeDefaultEPS`  
`template <typename scalar_t> struct AABBTreeDefaultEPS`  
_L19-22_
- L21 _public member_ `static constexpr scalar_t eps = std::numeric_limits<scalar_t>::epsilon() * scalar_t(10);`

#### struct `AABBTreeZeroEPS`  
`struct AABBTreeZeroEPS`  
_L24-27_
- L26 _public member_ `static constexpr double eps = 0;`

#### class `AABBTree`  
`template <typename scalar_t, size_t leafSize = 8, typename AABBTreeEPS = AABBTreeDefaultEPS<scalar_t>, typename compatibility_t = NoCompatibility<scalar_t>> class AABBTree`  
_L31-954_
- L34 _public typedef_ `using point_data_t = Eigen::Matrix<scalar_t, Eigen::Dynamic, 3, Eigen::RowMajor>;`
- L35 _public typedef_ `using primitive_data_t = Eigen::Matrix<int, Eigen::Dynamic, 3, Eigen::RowMajor>;`
- L36 _public typedef_ `using point_t = Eigen::RowVector<scalar_t, 3>;`
- L37 _public typedef_ `using point2_t = Eigen::RowVector<scalar_t, 2>;`
- L38 _public typedef_ `using primitive_t = Eigen::RowVector<int, 3>;`
- L39 _public typedef_ `using leaf_data_t = std::array<point_t, leafSize>;`
- L40 _public typedef_ `using bbox_t = std::pair<point_t, point_t>;`
- L41 _public member_ `static constexpr size_t invalid = std::numeric_limits<size_t>::max();`
- L42 _public member_ `static constexpr scalar_t eps = AABBTreeEPS::eps;`
- L68 _private member_ `Eigen::Map<const point_data_t> points{nullptr};` — members for storing the data
- L69 _private member_ `Eigen::Map<const primitive_data_t> primitives{nullptr};`
- L70 _private member_ `std::vector<helper_data_t> meta;`
- L73 _private member_ `std::vector<int> indices;` — tree structure data
- L74 _private member_ `std::vector<node_t> nodes;`
- L76 _private member_ `compatibility_t comp;`
- L80 _public function_ `template <typename ... Types> AABBTree(const scalar_t* pointsData_, int numPoints_, const int* primitivesData_, int numPrimitives_, Types&& ... args) : points(Eigen::Map<const point_data_t>(pointsData_, numPoints_, 3)), primitives(Eigen::Map<const primitive_data_t>(primitivesData_, numPrimitives_, 3)), comp(args ...)`
- L116 _public function_ `template <typename ... Types> AABBTree(const Eigen::Ref<const point_data_t>& points_, const Eigen::Ref<const primitive_data_t>& primitives_, Types&& ... args) : AABBTree(points_.data(), (int)points_.rows(), primitives_.data(), (int)primitives_.rows(), args ...)`
- L122 _public function_ `template <typename... Types> std::vector<std::tuple<int64_t, point_t, scalar_t>> getAllPointsWithinDistance(const Eigen::Ref<const point_t>& point, const scalar_t& distance, Types&&... args) const` — Computes all points <= the specified distance from the supplied point
- L205 _public function_ `void Update(TaskThreadPool* threadPool = nullptr)` — Update the current AABB tree with updated points. This assumes that the referenced points (see constructor) have been updated.
- L233 _public function_ `void Update(const scalar_t* pointsData_, TaskThreadPool* threadPool = nullptr)` — Update the current AABB tree with updated points. This assumes that the referenced points (see constructor) have been updated.
- L241 _public function_ `template <typename ... Types> std::tuple<int64_t, point_t, scalar_t> getClosestPoint(const Eigen::Ref<const point_t>& point, const scalar_t& distance, Types&& ... args) const`
- L323 _public function_ `std::tuple<int, point_t, scalar_t> intersectRay(const Eigen::Ref<const point_t>& origin, const Eigen::Ref<const point_t>& direction) const`
- L466 _public function_ `std::tuple<int, point_t, scalar_t> intersectRayBidirectional(const Eigen::Ref<const point_t>& origin, const Eigen::Ref<const point_t>& direction) const` — Finds the closest intersection of the ray with the AABB tree in both the positive and the negative direction. @return Tuple containing the triangle index (-1 if there is no intersection), the barycentric coordinates of the intersection, and the absolute distance from the origin to the intersection point.
- L607 _private function_ `std::tuple<scalar_t, point_t> getClosestPointToPrimitive(const Eigen::Ref<const point_t>& point, const size_t index) const` — --- point-primitive distance + helper functions ---
- L742 _private function_ `inline void getMinEdge02(const scalar_t& a11, const scalar_t& b1, point2_t& p) const`
- L759 _private function_ `inline void getMinEdge12(const scalar_t& a01, const scalar_t& a11, const scalar_t& b1, const scalar_t& f10, const scalar_t& f01, point2_t& p) const`
- L781 _private function_ `inline void getMinInterior(const point2_t& p0, const scalar_t& h0, const point2_t& p1, const scalar_t& h1, point2_t& p) const`
- L788 _private function_ `std::tuple<bool, point_t, scalar_t> intersectRayPrimitive(const Eigen::Ref<const point_t>& origin, const Eigen::Ref<const point_t>& direction, const size_t& index) const` — --- ray-primitive intersection function ---
- L824 _private function_ `void splitNode(size_t index)` — --- hierarchy construction function and helpers ---
- L887 _private function_ `void updateNode(size_t index, int level, TaskThreadPool* threadPool)` — the split and bounding box of the nodes
- L920 _private function_ `inline bbox_t centroidBoundingBox(const size_t start, const size_t end) const`
- L936 _private function_ `inline bbox_t primitiveBoundingBox(const size_t start, const size_t end) const`

#### struct `AABBTree::node_t`  
`struct node_t`  
_L45-56_
- L47 _public member_ `std::pair<size_t, size_t> children = { invalid, invalid };`
- L48 _public member_ `std::pair<size_t, size_t> range;`
- L49 _public member_ `bbox_t bbox;`
- L50 _public member_ `size_t dim = invalid;`
- L51 _public member_ `scalar_t split = 0.0f;`
- L53 _public function_ `node_t(size_t start, size_t end) : range({ start, end })`

#### struct `AABBTree::helper_data_t`  
`struct helper_data_t`  
_L58-65_
- L60 _public member_ `point_t edge0;`
- L61 _public member_ `point_t edge1;`
- L62 _public member_ `point_t normal;`
- L63 _public member_ `point_t centroid;`
- L64 _public member_ `point_t a;`

#### Free symbols / members of external scopes

- L209 _function_ `` (scope `AABBTree::Update`)
- L858 _function_ `` (scope `AABBTree::splitNode`)
- L902 _function_ `futures.Add(threadPool->AddTask([&]() { updateNode(node.children.first, level + 1, threadPool); }));` (scope `AABBTree::updateNode`)
- L903 _function_ `futures.Add(threadPool->AddTask([&]() { updateNode(node.children.second, level + 1, threadPool); }));` (scope `AABBTree::updateNode`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/geometry/KdTree.h` (Private)


#### struct `NoCompatibility`  
`template <typename scalar_t> struct NoCompatibility`  
_L19-28_
- desc: some basic compatibility structures that might be useful empty compatibility structure
- L21 _public function_ `NoCompatibility()`
- L24 _public function_ `inline bool isCompatible(const size_t) const`

#### struct `NormalCompatiblityFunction`  
`template <typename scalar_t, size_t dimension = 3> struct NormalCompatiblityFunction`  
_L33-47_
- desc: compatibility function checking if the normal is pointing in a similar direction
- L35 _public typedef_ `using data_t = Eigen::Matrix<scalar_t, Eigen::Dynamic, dimension, Eigen::RowMajor>;`
- L36 _public typedef_ `using value_t = Eigen::RowVector<scalar_t, dimension>;`
- L38 _public member_ `const Eigen::Ref<const data_t> normals;`
- L40 _public function_ `NormalCompatiblityFunction(const Eigen::Ref<const data_t>& normals_) : normals(normals_)`
- L43 _public function_ `inline bool isCompatible(const size_t index, const Eigen::Ref<const value_t>& normal, const scalar_t threshold) const`

#### class `KdTree`  
`template <typename scalar_t, typename compatibility_t = NoCompatibility<scalar_t>, size_t dimension = 3, size_t leafSize = 32> class KdTree`  
_L52-386_
- desc: kd-tree class supporting compatibility structures
- L55 _public typedef_ `using data_t = Eigen::Matrix<scalar_t, Eigen::Dynamic, dimension, Eigen::RowMajor>;`
- L56 _public typedef_ `using vector_t = Eigen::RowVector<scalar_t, dimension>;`
- L57 _public typedef_ `using leaf_data_t = std::array<vector_t, leafSize>;`
- L58 _public typedef_ `using bbox_t = std::pair<vector_t, vector_t>;`
- L59 _public member_ `static constexpr size_t invalid = std::numeric_limits<size_t>::max();`
- L78 _private member_ `const Eigen::Ref<const data_t> points;` — members for storing the data
- L79 _private member_ `const size_t numPoints;`
- L80 _private member_ `compatibility_t comp;`
- L83 _private member_ `std::vector<size_t> indices;` — tree structure data
- L84 _private member_ `std::vector<node_t> nodes;`
- L88 _public function_ `template <typename ... Types> KdTree(const Eigen::Ref<const data_t>& points_, Types&& ... args) : points(points_), numPoints(points.rows()), comp(args ...)`
- L105 _public function_ `vector_t getReferencePoint(const size_t index) const`
- L111 _public function_ `template <typename ... Types> std::pair<int64_t, scalar_t> getClosestPoint(const Eigen::Ref<const vector_t>& point, const scalar_t& distance, Types&& ... args) const`
- L201 _public function_ `template <typename ... Types> std::pair<std::vector<int64_t>, std::vector<scalar_t>> getPointsInRadius(const Eigen::Ref<const vector_t>& point, const scalar_t& distance, Types&& ... args) const`
- L291 _public function_ `void Search(const scalar_t* qrs, int numPts, int* resultIndices, scalar_t* distances = nullptr, const scalar_t maxDistance = std::numeric_limits<scalar_t>::max()) const`
- L309 _public function_ `Eigen::VectorXi Search(const scalar_t* qrs, int numPts, const scalar_t maxDistance = std::numeric_limits<scalar_t>::max()) const`
- L317 _private function_ `bbox_t boundingBox(const size_t start, const size_t end) const`
- L333 _private function_ `void splitNode(size_t index)`

#### struct `KdTree::node_t`  
`struct node_t`  
_L62-74_
- L64 _public member_ `std::pair<size_t, size_t> children = { invalid, invalid };`
- L65 _public member_ `std::pair<size_t, size_t> range;`
- L66 _public member_ `bbox_t bbox;`
- L67 _public member_ `size_t dim = invalid;`
- L68 _public member_ `scalar_t split = 0.0f;`
- L69 _public member_ `leaf_data_t data;`
- L71 _public function_ `node_t(size_t start, size_t end) : range({ start, end })`

#### Free symbols / members of external scopes

- L363 _function_ `` (scope `KdTree::splitNode`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/io/CameraIO.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template<class T> std::vector<CameraModelOpenCV<T> > ReadOpenCvModelJson(const std::string& filename);`
- L31 _prototype_ `template<class T> std::vector<CameraModelPinhole<T> > ReadPinholeModelJson(const std::string& filename);` — @brief Read Digital Humans Json camera file. Read Digital Humans Json camera file format with no distortion model - pinhole cameras (in the case of working with undistorted images, for example). @param filename String with file path.
- L41 _prototype_ `template<class T> void WriteOpenCvModelJson(const std::string& filename, const std::vector<CameraModelOpenCV<T> >& cameras);` — @brief Write Digital Humans Json camera file. Write Digital Humans Json camera file format with OpenCV distortion as distortion model (k1, k2, p1, p2, k3). @param cameras Vector of cameras with OpenCV distortion model.
- L50 _prototype_ `template<class T> void WritePinholeModelJson(const std::string& filename, const std::vector<CameraModelPinhole<T> >& cameras);` — @brief Write Digital Humans Json camera file. Write Digital Humans Json camera file format with pinhole camera model. @param cameras Vector of cameras with pinhole camera model.
- L60 _prototype_ `template<class T> std::vector<CameraModelOpenCV<T> > ReadOpenCvModelXml(const std::string& filename);` — @brief Read Agisoft Metashape xml camera file. Read Agisoft Metashape xml camera file format with OpenCV distortion as distortion model (k1, k2, p1, p2, k3). @param filename String with file path.
- L69 _prototype_ `template<class T> std::vector<CameraModelPinhole<T> > ReadPinholeModelXml(const std::string& filename);` — @brief Read Agisoft Metashape xml camera file. Read Agisoft Metashape xml camera file format with as Pinhole camera model. @param filename String with file path.
- L82 _prototype_ `template<class T> void WriteOpenCvModelXml(const std::string& filename, const std::vector<CameraModelOpenCV<T> >& cameras);`
- L94 _prototype_ `template<class T> void WritePinholeModelXml(const std::string& filename, const std::vector<CameraModelPinhole<T> >& cameras);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/io/JsonIO.h` (Private)


#### class `JsonElement`  
`class JsonElement`  
_L20-376_
- desc: JSON elements as defined in http://ietf.org/rfc/rfc4627.txt
- L39 _public function_ `JsonElement() : m_type(JsonType::Null), m_container()`
- L42 _public function_ `explicit JsonElement(JsonType type) : m_type(type)`
- L51 _public function_ `explicit JsonElement(int value) : m_type(JsonType::Int), m_container(static_cast<int64_t>(value))`
- L54 _public function_ `explicit JsonElement(int64_t value) : m_type(JsonType::Int), m_container(value)`
- L57 _public function_ `explicit JsonElement(double value) : m_type(JsonType::Double), m_container(value)`
- L60 _public function_ `explicit JsonElement(const std::string& str) : m_type(JsonType::String), m_container(str)`
- L63 _public function_ `explicit JsonElement(const char* str) : m_type(JsonType::String), m_container(str)`
- L66 _public function_ `explicit JsonElement(std::vector<JsonElement>&& array) : m_type(JsonType::Array), m_container(std::move(array))`
- L69 _public function_ `explicit JsonElement(std::map<std::string, JsonElement>&& object) : m_type(JsonType::Object), m_container(std::move( object))`
- L73 _public function_ `static JsonElement Obj()`
- L74 _public function_ `static JsonElement Arr()`
- L77 _public function_ `template<typename T> JsonElement& Set(const std::string& key, T value) &`
- L82 _public function_ `template<typename T> JsonElement&& Set(const std::string& key, T value) &&`
- L87 _public function_ `JsonElement& Set(const std::string& key, JsonElement element) &`
- L91 _public function_ `JsonElement&& Set(const std::string& key, JsonElement element) &&`
- L97 _public function_ `template<typename T> JsonElement& Add(T value) &`
- L102 _public function_ `template<typename T> JsonElement&& Add(T value) &&`
- L107 _public function_ `JsonElement& Add(JsonElement element) &`
- L111 _public function_ `JsonElement&& Add(JsonElement element) &&`
- L116 _public function_ `explicit JsonElement(bool value) : m_type(value ? JsonType::True : JsonType::False)`
- L120 _public function_ `template<typename T> explicit JsonElement(const std::pair<T, T>& pair) : m_type(JsonType::Array)`
- L127 _public function_ `template<typename ... Types> explicit JsonElement(const std::tuple<Types ...>& tuple) : m_type(JsonType::Array)`
- L135 _public function_ `template<typename T> explicit JsonElement(const std::vector<T>& vec) : m_type(JsonType::Array)`
- L143 _public function_ `template<typename T> explicit JsonElement(const std::map<std::string, T>& map) : m_type(JsonType::Object)`
- L150 _public prototype_ `JsonElement(const JsonElement&) = delete;`
- L151 _public prototype_ `JsonElement& operator=(const JsonElement&) = delete;`
- L153 _public function_ `JsonElement(JsonElement&& other) : m_type(other.m_type), m_container(std::move(other.m_container))`
- L157 _public function_ `JsonElement& operator=(JsonElement&& other)`
- L166 _public function_ `JsonType Type() const`
- L170 _public function_ `bool IsNull() const`
- L174 _public function_ `bool IsTrue() const`
- L178 _public function_ `bool IsFalse() const`
- L182 _public function_ `bool IsInt() const`
- L186 _public function_ `bool IsDouble() const`
- L190 _public function_ `bool IsNumber() const`
- L194 _public function_ `bool IsString() const`
- L198 _public function_ `bool IsArray() const`
- L202 _public function_ `bool IsObject() const`
- L207 _public function_ `template<class T, typename DISCARD = typename std::enable_if<std::is_arithmetic<T>::value>::type> T Value() const`
- L211 _public function_ `std::string& String()`
- L212 _public function_ `const std::string& String() const`
- L214 _public function_ `std::vector<JsonElement>& Array()`
- L215 _public function_ `const std::vector<JsonElement>& Array() const`
- L217 _public function_ `std::map<std::string, JsonElement>& Object()`
- L218 _public function_ `const std::map<std::string, JsonElement>& Object() const`
- L220 _public function_ `bool Boolean() const`
- L231 _public function_ `template<class T> T Get() const` — ! Generic get function which calls the specializations using typeHelper.
- L235 _public function_ `size_t Size() const`
- L245 _public function_ `JsonElement& operator[](size_t index)`
- L255 _public function_ `const JsonElement& operator[](size_t index) const`
- L265 _public function_ `void Append(JsonElement&& element)`
- L272 _public function_ `bool Contains(const std::string& key) const`
- L276 _public function_ `const JsonElement& operator[](const std::string& key) const`
- L288 _public function_ `JsonElement& operator[](const std::string& key)`
- L300 _public function_ `const std::map<std::string, JsonElement>& Map() const`
- L304 _public function_ `void Insert(const std::string& key, JsonElement&& element)`
- L314 _private prototype_ `template<typename T> T Get(typeHelper<T>) const;` — ! Generic Get function. B
- L318 _private function_ `template<typename S, typename T> std::pair<S, T> Get(typeHelper<std::pair<S, T> >) const` — ! Partial specialization for std::pair.
- L330 _private function_ `template<typename ... Types> std::tuple<Types ...> Get(typeHelper<std::tuple<Types ...> >) const` — ! Partial specialization for std::tuple.
- L348 _private function_ `template<typename S> std::vector<S> Get(typeHelper<std::vector<S> >) const` — ! Partial specialization for std::vector.
- L362 _private function_ `template<typename S> std::map<std::string, S> Get(typeHelper<std::map<std::string, S> >) const` — ! Partial specialization for std::map.
- L374 _private member_ `JsonType m_type;`
- L375 _private member_ `std::variant<int64_t, double, std::string, std::vector<JsonElement>, std::map<std::string, JsonElement> > m_container;`
- L379 _function_ `template<> inline int JsonElement::Get<int>(typeHelper<int>) const` — ! Get spezializations
- L384 _function_ `template<> inline int64_t JsonElement::Get<int64_t>(typeHelper<int64_t>) const` — ! Get spezializations
- L388 _function_ `template<> inline size_t JsonElement::Get<size_t>(typeHelper<size_t>) const`
- L392 _function_ `template<> inline float JsonElement::Get<float>(typeHelper<float>) const`
- L396 _function_ `template<> inline double JsonElement::Get<double>(typeHelper<double>) const`
- L400 _function_ `template<> inline std::string JsonElement::Get<std::string>(typeHelper<std::string>) const`

#### struct `JsonElement::typeHelper`  
`template<typename T> struct typeHelper`  
_L24-24_
- desc: ! helper struct to implement partial specialization

#### enum `JsonElement::JsonType`  
`enum class JsonType`  
_L28-37_
- desc: ! allowed types
- L29 _public enumerator_ `False`
- L30 _public enumerator_ `Null`
- L31 _public enumerator_ `True`
- L32 _public enumerator_ `Object`
- L33 _public enumerator_ `Array`
- L34 _public enumerator_ `Int`
- L35 _public enumerator_ `Double`
- L36 _public enumerator_ `String`

#### Free symbols / members of external scopes

- L129 _function_ `std::apply([&](auto&&... arg) { (Append(JsonElement(arg)), ...); }, tuple);` (scope `JsonElement::JsonElement`)
- L339 _function_ `std::apply([&](auto&&... arg) { size_t i(0); ((arg = Array()[i++].Get<typename std::remove_reference<decltype(arg)>::type>()), ...); }, tupleOut);` (scope `JsonElement::Get`)
- L404 _prototype_ `JsonElement ReadJson(const std::string& jsonString);`
- L407 _prototype_ `std::string WriteJson(const JsonElement& json, int tabs = -1);` — ! Write @p json to string. Set @p tabs to 0 or positive to pretty print with tabs and newlines.
- L410 _prototype_ `void WriteJson(std::ostream& stream, const JsonElement& element, int tabs = -1);` — ! Write @p json to @p stream. Set @p tabs to 0 or positive to pretty print with tabs and newlines.
- L412 _function_ `inline JsonElement DeepCopy(const JsonElement& src)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/io/NpyFileFormat.h` (Private)


#### struct `NPYHeader`  
`struct NPYHeader`  
_L23-32_
- L25 _public member_ `std::string m_dataType;` — supported: "<i4" (32-bit int), "<f4" (32-bit float), "<f8" (64-bit double)
- L26 _public member_ `std::vector<int> m_shape;`
- L27 _public member_ `bool m_fortranOrder;`
- L29 _public prototype_ `int DataTypeSize() const;`
- L31 _public function_ `template <typename T> bool IsType()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define CARBON_NPY_NAMESPACE TITAN_NAMESPACE::npy`
- L19 _prototype_ `CARBON_NAMESPACE_BEGIN(CARBON_NPY_NAMESPACE) template <typename T> std::string NpyTypeName();`
- L34 _prototype_ `void SaveNPYRaw(std::ostream& out, const NPYHeader& header, const uint8_t* data, size_t dataSize);`
- L36 _function_ `template <class T> void SaveNPY(std::ostream& out, const NPYHeader& header, const std::vector<T>& data)`
- L40 _function_ `template <class T> void SaveNPY(const std::string& filename, const NPYHeader& header, const std::vector<T>& data)`
- L47 _function_ `template <class T, int R, int C, int MatrixOrder> void SaveMatrixAsNpy(std::ostream& out, const Eigen::Matrix<T, R, C, MatrixOrder>& matrix)`
- L57 _function_ `template <class T, int R, int C, int MatrixOrder> void SaveMatrixAsNpy(const std::string& filename, const Eigen::Matrix<T, R, C, MatrixOrder>& matrix)`
- L69 _prototype_ `void LoadNPYRawHeader(const std::vector<char>& htxt, NPYHeader& header);`
- L70 _prototype_ `void LoadNPYRawHeader(std::istream& in, NPYHeader& header);`
- L71 _prototype_ `void LoadNPYRawData(std::istream& in, const NPYHeader& header, std::vector<uint8_t>& data);`
- L72 _prototype_ `void LoadNPYRaw(std::istream& in, NPYHeader& header, std::vector<uint8_t>& data);`
- L74 _prototype_ `void LoadNPYRawHeader(FILE* pFile, NPYHeader& header);`
- L75 _prototype_ `void LoadNPYRawData(FILE* pFile, const NPYHeader& header, std::vector<uint8_t>& data);`
- L78 _function_ `template <class T, std::enable_if_t<!std::is_same_v<T, uint8_t>, bool> = true> void LoadNPY(std::istream& in, NPYHeader& header, std::vector<T>& data)`
- L91 _function_ `template <class T, std::enable_if_t<!std::is_same_v<T, uint8_t>, bool> = true> void LoadNPY(const std::string& filename, NPYHeader& header, std::vector<T>& data)`
- L98 _function_ `template <class T, int R, int C, int MatrixOrder> void LoadMatrixFromNpy(std::istream& in, Eigen::Matrix<T, R, C, MatrixOrder>& matrix)`
- L153 _function_ `template <class T, int R, int C, int MatrixOrder> void LoadMatrixFromNpy(FILE* pFile, Eigen::Matrix<T, R, C, MatrixOrder>& matrix)`
- L206 _function_ `template <class T, int R, int C, int MatrixOrder> void LoadMatrixFromNpy(const std::string& filename, Eigen::Matrix<T, R, C, MatrixOrder>& matrix)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/io/Utils.h` (Private)


#### Free symbols / members of external scopes

- L8 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) FILE* OpenUtf8File(const std::string& utf8Path, const char* mode);`
- L23 _prototype_ `std::string ReadFile(const std::string& filename);` — @brief Reads all data in @p filename and returns it as std::string. @return std::string with all data in the file. @throw std::runtime_error if the file cannot be opened.
- L30 _prototype_ `bool FileExists(const std::string& filename);` — @brief Check if the @p filename exists. @return bool indicating if the file exists. False if filename is greater than max filename length. @throw std::filesystem::filesystem_error upon error.
- L36 _prototype_ `void WriteFile(const std::string& filename, const std::string& data);` — @brief Writes @p data to file @p filename. @throw std::runtime_error if the file could not be written.
- L42 _prototype_ `void ThrowReadFileErrorWithInfo(const std::string& filename);` — @brief Throw file reading error with troubleshooting information if the file reading fails @throw std::runtime_error if the file cannot be opened.
- L47 _prototype_ `std::string GetUsername();` — @return The username as read from the environment.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/io/XmlIO.h` (Private)


#### class `XMLElement`  
`class XMLElement`  
_L19-99_
- desc: XML element with name, attributes, text, and xml element children.
- L22 _public function_ `XMLElement(const std::string& name) : m_name(name)` — ! Creates an XMLElement with name @p name
- L26 _public function_ `XMLElement& AddChild(const std::string& childName)` — ! Add a child element and return reference to it.
- L31 _public function_ `const std::string& Name() const`
- L35 _public function_ `void SetText(const std::string& text)`
- L39 _public function_ `const std::string& Text() const`
- L43 _public function_ `void AddAttribute(const std::string& attributeName, const std::string& attributeValue)`
- L47 _public function_ `const std::string& Attribute(const std::string& attributeName) const`
- L56 _public function_ `const std::map<std::string, std::string>& Attributes() const`
- L60 _public function_ `const std::vector<std::unique_ptr<XMLElement> >& Children() const`
- L65 _public function_ `std::vector<XMLElement*> ChildrenWithName(const std::string& childName)` — ! @returns all children with element name @p childName
- L81 _public function_ `template<bool failIfNotUnique = true> XMLElement* UniqueChild(const std::string& childName)` — @returns a unique child element @p childName. @param[in] childName   The name of the child. @param[in] failIfNotUnique  If True then the method throws an exception is there is no child or multiple children with the name, otherwise it will return a nullptr.
- L94 _private member_ `std::string m_name;`
- L95 _private member_ `std::map<std::string, std::string> m_attributes;`
- L96 _private member_ `std::string m_text;`
- L98 _private member_ `std::vector<std::unique_ptr<XMLElement> > m_children;` — ! Store children as unique_ptr to handle any potential vector resizing which would break the references

#### Free symbols / members of external scopes

- L102 _prototype_ `void WriteXML(std::ostream& out, const XMLElement& element);` — ! Writes the XML element to @p output
- L105 _prototype_ `std::string WriteXML(const XMLElement& element);` — ! Writes the XML element to std::string.
- L108 _prototype_ `XMLElement ReadXML(const std::string& xmlData);` — ! Reads XML data from @p xmlData and @returns it as XMLElemen.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/simd/Simd.h` (Private)


#### struct `SimdTypeBase`  
`template <typename T, int C> struct SimdTypeBase`  
_L14-19_
- L16 _public function_ `inline static constexpr int Alignment()`
- L17 _public function_ `inline static constexpr int Size()`
- L18 _public function_ `inline static int Pad(int n)`

#### struct `_SimdType`  
`template <> struct _SimdType<bool, 1> : public SimdTypeBase<int, 1>`  
_L30-36_
- inherits: `SimdTypeBase<int,1>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### struct `_SimdType`  
`template <> struct _SimdType<int, 1> : public SimdTypeBase<int, 1>`  
_L38-69_
- inherits: `SimdTypeBase<int,1>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### struct `_SimdType`  
`template <> struct _SimdType<float, 1> : public SimdTypeBase<float, 1>`  
_L72-110_
- inherits: `SimdTypeBase<float,1>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### struct `_SimdType`  
`template <> struct _SimdType<bool, 4> : public SimdTypeBase<int, 4>`  
_L155-161_
- inherits: `SimdTypeBase<int,4>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### struct `_SimdType`  
`template <> struct _SimdType<int, 4> : public SimdTypeBase<int, 4>`  
_L164-196_
- inherits: `SimdTypeBase<int,4>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### struct `_SimdType`  
`template <> struct _SimdType<float, 4> : public SimdTypeBase<float, 4>`  
_L199-236_
- inherits: `SimdTypeBase<float,4>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### struct `_SimdType`  
`template <> struct _SimdType<bool, 8> : public SimdTypeBase<int, 8>`  
_L295-301_
- inherits: `SimdTypeBase<int,8>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### struct `_SimdType`  
`template <> struct _SimdType<int, 8> : public SimdTypeBase<int, 8>`  
_L304-336_
- inherits: `SimdTypeBase<int,8>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### struct `_SimdType`  
`template <> struct _SimdType<float, 8> : public SimdTypeBase<float, 8>`  
_L339-376_
- inherits: `SimdTypeBase<float,8>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### Free symbols / members of external scopes

- L24 _prototype_ `template <class T, int C> inline _SimdType<T, C> Abs(const _SimdType<T, C>& value);`
- L25 _prototype_ `template <class T, int C> inline _SimdType<T, C> Abs(const _SimdType<T, C>& value);`
- L26 _prototype_ `template <class T, int C> inline _SimdType<T, C> Abs(const _SimdType<T, C>& value);`
- L27 _prototype_ `template <class T, int C> inline _SimdType<T, C> Abs(const _SimdType<T, C>& value);`
- L125 _function_ `inline _SimdType<bool, 1> operator&&(const _SimdType<bool, 1>& a, const _SimdType<bool, 1>& b)`
- L126 _function_ `inline _SimdType<bool, 1> operator||(const _SimdType<bool, 1>& a, const _SimdType<bool, 1>& b)`
- L128 _function_ `template <typename T> inline _SimdType<bool, 1> operator==(const _SimdType<T, 1>& a, const _SimdType<T, 1>& b)`
- L129 _function_ `template <typename T> inline _SimdType<bool, 1> operator==(const _SimdType<T, 1>& a, const _SimdType<T, 1>& b)`
- L130 _function_ `template <typename T> inline _SimdType<bool, 1> operator==(const _SimdType<T, 1>& a, const _SimdType<T, 1>& b)`
- L131 _function_ `template <typename T> inline _SimdType<bool, 1> operator==(const _SimdType<T, 1>& a, const _SimdType<T, 1>& b)`
- L132 _function_ `template <typename T> inline _SimdType<bool, 1> operator!=(const _SimdType<T, 1>& a, const _SimdType<T, 1>& b)`
- L134 _function_ `template <> inline _SimdType<float, 1> Abs(const _SimdType<float, 1>& value)`
- L135 _function_ `template <> inline _SimdType<float, 1> Abs(const _SimdType<float, 1>& value)`
- L142 _function_ `template <> inline _SimdType<float, 1> Max(const _SimdType<float, 1>& value1, const _SimdType<float, 1>& value2)`
- L149 _function_ `template <> inline _SimdType<float, 1> Sqrt(const _SimdType<float, 1>& value)`
- L249 _function_ `inline _SimdType<bool, 4> operator&&(const _SimdType<bool, 4>& a, const _SimdType<bool, 4>& b)`
- L250 _function_ `inline _SimdType<bool, 4> operator||(const _SimdType<bool, 4>& a, const _SimdType<bool, 4>& b)`
- L252 _function_ `inline _SimdType<bool, 4> operator==(const _SimdType<int, 4>& a, const _SimdType<int, 4>& b)`
- L253 _function_ `inline _SimdType<bool, 4> operator>(const _SimdType<int, 4>& a, const _SimdType<int, 4>& b)`
- L254 _function_ `inline _SimdType<bool, 4> operator<=(const _SimdType<int, 4>& a, const _SimdType<int, 4>& b)`
- L255 _function_ `inline _SimdType<bool, 4> operator<(const _SimdType<int, 4>& a, const _SimdType<int, 4>& b)`
- L257 _function_ `inline _SimdType<bool, 4> operator==(const _SimdType<float, 4>& a, const _SimdType<float, 4>& b)`
- L260 _function_ `inline _SimdType<bool, 4> operator!=(const _SimdType<float, 4>& a, const _SimdType<float, 4>& b)`
- L263 _function_ `inline _SimdType<bool, 4> operator<=(const _SimdType<float, 4>& a, const _SimdType<float, 4>& b)`
- L266 _function_ `inline _SimdType<bool, 4> operator<(const _SimdType<float, 4>& a, const _SimdType<float, 4>& b)`
- L269 _function_ `inline _SimdType<bool, 4> operator>(const _SimdType<float, 4>& a, const _SimdType<float, 4>& b)`
- L273 _function_ `template <> inline _SimdType<float, 4> Abs(const _SimdType<float, 4>& value)`
- L274 _function_ `template <> inline _SimdType<float, 4> Abs(const _SimdType<float, 4>& value)`
- L281 _function_ `template <> inline _SimdType<float, 4> Max(const _SimdType<float, 4>& value1, const _SimdType<float, 4>& value2)`
- L288 _function_ `template <> inline _SimdType<float, 4> Sqrt(const _SimdType<float, 4>& value)`
- L388 _function_ `inline _SimdType<bool, 8> operator&&(const _SimdType<bool, 8>& a, const _SimdType<bool, 8>& b)`
- L389 _function_ `inline _SimdType<bool, 8> operator||(const _SimdType<bool, 8>& a, const _SimdType<bool, 8>& b)`
- L391 _function_ `inline _SimdType<bool, 8> operator==(const _SimdType<int, 8>& a, const _SimdType<int, 8>& b)`
- L392 _function_ `inline _SimdType<bool, 8> operator>(const _SimdType<int, 8>& a, const _SimdType<int, 8>& b)`
- L393 _function_ `inline _SimdType<bool, 8> operator<=(const _SimdType<int, 8>& a, const _SimdType<int, 8>& b)`
- L394 _function_ `inline _SimdType<bool, 8> operator<(const _SimdType<int, 8>& a, const _SimdType<int, 8>& b)`
- L396 _function_ `inline _SimdType<bool, 8> operator==(const _SimdType<float, 8>& a, const _SimdType<float, 8>& b)`
- L399 _function_ `inline _SimdType<bool, 8> operator!=(const _SimdType<float, 8>& a, const _SimdType<float, 8>& b)`
- L402 _function_ `inline _SimdType<bool, 8> operator<=(const _SimdType<float, 8>& a, const _SimdType<float, 8>& b)`
- L405 _function_ `inline _SimdType<bool, 8> operator<(const _SimdType<float, 8>& a, const _SimdType<float, 8>& b)`
- L408 _function_ `inline _SimdType<bool, 8> operator>(const _SimdType<float, 8>& a, const _SimdType<float, 8>& b)`
- L412 _function_ `template <> inline _SimdType<float, 8> Abs(const _SimdType<float, 8>& value)`
- L413 _function_ `template <> inline _SimdType<float, 8> Abs(const _SimdType<float, 8>& value)`
- L420 _function_ `template <> inline _SimdType<float, 8> Max(const _SimdType<float, 8>& value1, const _SimdType<float, 8>& value2)`
- L427 _function_ `template <> inline _SimdType<float, 8> Sqrt(const _SimdType<float, 8>& value)`
- L433 _typedef_ `typedef _SimdType<float, 8> SimdType;`
- L434 _typedef_ `typedef _SimdType<int, 8> SimdTypei;`
- L435 _typedef_ `typedef _SimdType<bool, 8> SimdTypeb;`
- L437 _typedef_ `typedef _SimdType<float, 4> SimdType;`
- L438 _typedef_ `typedef _SimdType<int, 4> SimdTypei;`
- L439 _typedef_ `typedef _SimdType<bool, 4> SimdTypeb;`
- L441 _typedef_ `typedef _SimdType<float, 1> SimdType;`
- L442 _typedef_ `typedef _SimdType<int, 1> SimdTypei;`
- L443 _typedef_ `typedef _SimdType<bool, 1> SimdTypeb;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/simd/SimdeWarnings.h` (Private)


#### Free symbols / members of external scopes

- L6 _macro_ `#define CARBON_DISABLE_SIMDE_WARNINGS`
- L7 _macro_ `#define CARBON_REENABLE_SIMDE_WARNINGS`
- L11 _macro_ `#define CARBON_DISABLE_SIMDE_WARNINGS \` — disable warning: sse.h(3979) : warning C6001: Using uninitialized memory 'r_'.: Lines: 3971, 3979
- L14 _macro_ `#define CARBON_REENABLE_SIMDE_WARNINGS __pragma(warning(pop))`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/simd/Utils.h` (Private)


#### Free symbols / members of external scopes

- L19 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) #if defined CARBON_ENABLE_SSE && CARBON_ENABLE_SSE`
- L32 _function_ `inline simde__m128i mul_epi32_sse2(const simde__m128i& a, const simde__m128i& b)`
- L47 _function_ `inline float HorizontalSum(simde__m256 value)` — \return value[0] + value[1] + ... + value[7]

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/simd/VertexUnpack.h` (Private)


#### struct `VertexPack128`  
`struct VertexPack128`  
_L12-17_
- L14 _public member_ `simde__m128 v0;`
- L15 _public member_ `simde__m128 v1;`
- L16 _public member_ `simde__m128 v2;`

#### struct `VertexPack256`  
`struct VertexPack256`  
_L55-60_
- L57 _public member_ `simde__m256 v0;`
- L58 _public member_ `simde__m256 v1;`
- L59 _public member_ `simde__m256 v2;`

#### Free symbols / members of external scopes

- L27 _function_ `static inline VertexPack128 VertexUnpack(const simde__m128& v0, const simde__m128& v1, const simde__m128& v2)` — @brief Converts ArrayOfStructures into StructuresOfArray for 4 vectors with 3 elements each. [x1, y1, z1, x2], [y2, z2, x3, y3] [z3, x4, y4, z4] => [x1, x2, x3, x4], [y1, y2, y3, y4] [z1, z2, z3, z4] This is useful to extract consecutive vertex data and unpack each vertex dimension.
- L70 _function_ `static inline VertexPack256 VertexUnpack(const simde__m256& v0, const simde__m256& v1, const simde__m256& v2)` — @brief Converts ArrayOfStructures into StructuresOfArray for 4 vectors with 3 elements each. [x1, y1, z1, x2], [y2, z2, x3, y3] [z3, x4, y4, z4] => [x1, x2, x3, x4], [y1, y2, y3, y4] [z1, z2, z3, z4] This is useful to extract consecutive vertex data and unpack each vertex dimension.
- L102 _function_ `template <typename T, int C> std::tuple<_SimdType<T, C>, _SimdType<T, C>, _SimdType<T, C>> VertexUnpack(const _SimdType<T, C>& v0, const _SimdType<T, C>& v1, const _SimdType<T, C>& v2)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/utils/Base64.h` (Private)


#### Free symbols / members of external scopes

- L10 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) std::string Base64Encode(const unsigned char* data, size_t length); bool Base64Decode(std::string const& encodedString, std::vector<unsigned char>& decodedData); std::string Base64Decode(std::string const& encodedString);`
- L26 _prototype_ `bool Base64Decode(std::string const& encodedString, std::vector<unsigned char>& decodedData);` — Perform base64 decoding of string to return binary data using base64 alphabet defined in RFC 4648 ( https://en.wikipedia.org/wiki/Base64 ) @param[in] encodedString: the base64 encoded string (length must be a multiple of 4). @param[out] decodedData: the base64 decoded data @returns true if decoded successfully, false otherwise (ie encoded string is not valid base64 data)
- L34 _prototype_ `std::string Base64Decode(std::string const& encodedString);` — Perform base64 decoding of string to return binary data using base64 alphabet defined in RFC 4648 ( https://en.wikipedia.org/wiki/Base64 ) @param[in] encodedString: the base64 encoded string (length must be a multiple of 4). @returns The decoded binary string @throws exception if string cannot be decoded (ie encoded string is not valid base64 data).
- L37 _prototype_ `bool IsBase64Data(const std::string& encodedString);` — @return True if string is base64 data

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/utils/Env.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/utils/FlattenJson.h` (Private)


#### Free symbols / members of external scopes

- L8 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) JsonElement FlattenJson(const JsonElement& jsonIn, const std::string& baseDir);`
- L25 _prototype_ `JsonElement FlattenJson(const std::string& fileName);` — Load the selected file as Json and flatten it, ie for any strings in the Json file, if they exist as a file, if the file extension is .json they will be loaded as json, and if not, they will be loaded as binary and converted to a Base64 string and embedded in the output json @param[in] fileName: the filename of the Json file to flatten @returns the flattened Json

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/utils/ObjectPool.h` (Private)


#### class `ObjectPool`  
`template <typename T> class ObjectPool`  
_L21-90_
- desc: Class to keep a pool of objects. Aquire() returns a shared_ptr to an object of the pool, or it creates a new one if the pool is empty. Upon release of the shared_ptr, the object is returned to the pool via Release(). The class is intended to be used to keep large allocated data structures in the pool and therefore prevent constant mallocs and frees. @warning neither constructor or destructor are called on the objects upon Aquire() and Release(). The caller is responsible to fill all members of the returned object.
- L24 _public function_ `ObjectPool() : m_selfPtr(std::make_shared<ObjectPool<T>*>(this))`
- L26 _public function_ `std::shared_ptr<T> Aquire()`
- L54 _public function_ `size_t Size() const`
- L61 _public function_ `void Clear()` — Clears all objects from the pool that are currently within the pool. Does not remove the ones that have been aquired.
- L72 _public function_ `size_t TotalSize() const` — @returns the total number of objects belonging to the pool, both currently in the pool and the ones that have been aquired.
- L79 _private function_ `void Release(std::unique_ptr<T>&& obj)`
- L86 _private member_ `mutable std::mutex m_mutex;`
- L87 _private member_ `std::stack<std::unique_ptr<T>> m_objects;`
- L88 _private member_ `std::shared_ptr<ObjectPool<T>*> m_selfPtr;`
- L89 _private member_ `size_t m_totalCreatedObjects = 0;`

#### Free symbols / members of external scopes

- L41 _function_ `auto releaseFunctor = [poolWeakPtr](T* ptr)` (scope `ObjectPool::Aquire`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/utils/ProgressReporter.h` (Private)


#### class `AbstractProgressReporter`  
`class AbstractProgressReporter`  
_L22-44_
- desc: Abstract class to represent progress reporting implementation. Simple utility that can be implemented to act as a CLI progress reporter, or maybe part of a more complex GUI application.
- L24 _public prototype_ `virtual ~AbstractProgressReporter() = default;`
- L31 _public prototype_ `virtual void StartProgress(const char* message) = 0;` — Start tracking progress for a particular process. @param message Message that should describe the process.
- L38 _public prototype_ `virtual void SetProgress(float progress) = 0;` — Set the progress to the current state. @param progress New progress value between [0, 1].
- L43 _public prototype_ `virtual void EndProgress() = 0;` — Mark the ending of a progress.

#### class `CLIProgressReporter`  
`class CLIProgressReporter : public AbstractProgressReporter`  
_L56-97_
- inherits: `AbstractProgressReporter`
- desc: A simple command-line interface progress reporter implementation. An example of a fully printed out CMD progress line: Reading images   |==================================================| 100%, done in 44.3064 seconds. It includes a single line progress update (equal signs '=' in the example above though the character can be changed), estimated time printout while progress is running, and elapsed time took to finish the process once it is done.
- L66 _public prototype_ `CLIProgressReporter(unsigned int barLength = 50, unsigned int barStart = 40, char barPin = '=');` — Default Constructor. @param barLength How many character will there be to represent the 100% process. @param barStart The offset character count, acting as a TAB character to denote the offset between the message and progress bar. @param barPin Character that is used to represent a single pin inside the progress bar.
- L68 _public prototype_ `virtual ~CLIProgressReporter();`
- L71 _public prototype_ `void Silence();` — Silence the reporter output (ignore it's update to the stream)
- L74 _public prototype_ `void Unsilence();` — Continue pushing printouts to the stream.
- L85 _public prototype_ `void SetStream(std::ostream* stream);` — Set custom output stream to which the utility prints progress. By default, constructor sets this field to std::cout. @warning Stream instance must live as long as it is the lifetime of this instance. CLIProgressReporter does not take ownership of the stream instance.
- L87 _public prototype_ `virtual void StartProgress(const char* message) override final;`
- L88 _public prototype_ `virtual void SetProgress(float progress) final override;`
- L89 _public prototype_ `virtual void EndProgress() final override;`
- L93 _private member_ `Pimpl<Impl> m_pimpl;`
- L95 _private prototype_ `void PrintProgress();`
- L96 _private prototype_ `void PrintProgressEnd();`

#### class `IncrementingProgressReporter`  
`class IncrementingProgressReporter`  
_L104-150_
- desc: @brief Utility counting progress reporter that can be used to wrap a an AbstractProgressReporter to count progress in increments.
- L106 _public function_ `IncrementingProgressReporter(AbstractProgressReporter* progressReporter) : m_progressReporter(progressReporter) , m_numSteps(1) , m_count(0)`
- L121 _public function_ `void StartProgress(const char* message, int numSteps)` — Start tracking progress for a particular process. @param message Message that should describe the process. @param numSteps Defines how many steps / iterations this progress will contain. @note Based on numSteps update method calculates how much to advance the progress counters.
- L128 _public function_ `void Update()`
- L139 _public function_ `void EndProgress()` — Mark the ending of a progress.
- L147 _private member_ `AbstractProgressReporter* m_progressReporter;`
- L148 _private member_ `std::atomic<int> m_numSteps;`
- L149 _private member_ `std::atomic<int> m_count;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/utils/Stopwatch.h` (Private)


#### class `Stopwatch`  
`template<class Timer = std::chrono::steady_clock> class Stopwatch`  
_L18-76_
- desc: Simple, header-only utility for measuring time based on std::chrono.
- L20 _public function_ `Stopwatch() : m_tick(Timer::now())`
- L23 _public function_ `~Stopwatch()`
- L31 _public function_ `std::chrono::duration<double> Tick()` — Tick the stopwatch - start counting anew. @return Last counted time segment, before the tick.
- L44 _public function_ `void Reset()` — Reset all so far collected times.
- L50 _public function_ `std::chrono::duration<double> LastTime()` — Get what is the last measured time.
- L55 _public function_ `std::chrono::duration<double> ElapsedTime()` — Get what is currently elapsed time since the last tick.
- L63 _public function_ `std::chrono::duration<double> TotalTime()` — Get what is the total elapsed time since the first tick of the stopwatch instance.
- L69 _public function_ `const std::vector<std::chrono::duration<double> >& AllTimes() const` — Get list of all times that is collected in this stopwatch instance.
- L74 _private member_ `std::chrono::time_point<Timer> m_tick;`
- L75 _private member_ `std::vector<std::chrono::duration<double> > m_allTimes;`

#### Free symbols / members of external scopes

- L79 _function_ `inline Stopwatch<std::chrono::steady_clock> SteadyStopwatch()` — Create a stopwatch instance based on std::chrono::steady_clock.
- L84 _function_ `inline Stopwatch<std::chrono::high_resolution_clock> HighResolutionStopwatch()` — Create a stopwatch instance based on std::chrono::high_resolution_clock.
- L89 _function_ `inline Stopwatch<std::chrono::system_clock> SystemStopwatch()` — Create a stopwatch instance based on std::chrono::system_clock.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/utils/StringFormat.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <typename ... Args> std::string StringFormat(const std::string& format, Args ... args)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/utils/StringReplace.h` (Private)


#### Free symbols / members of external scopes

- L9 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) inline std::string ReplaceSubstring(const std::string& input, const std::string& pattern, const std::string& replacement)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/utils/StringUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) inline bool StringEndsWith(const std::string& input, const std::string& suffix)`
- L19 _function_ `inline bool StringStartsWith(const std::string& input, const std::string& prefix)`
- L25 _function_ `inline std::string StringToLower(const std::string& input)`
- L28 _function_ `std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return static_cast<unsigned char>(std::tolower(c)); });` (scope `StringToLower`)
- L34 _function_ `inline std::vector<std::string> Split(const std::string& str, const std::string& delim)`
- L60 _function_ `inline std::string Trim(const std::string& s)`
- L77 _function_ `inline std::filesystem::path Utf8Path(const std::string& utf8)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/utils/TaskThreadPool.h` (Private)


#### Free symbols / members of external scopes

- L15 _typedef_ `using TaskFuture = TaskFutureUE;`
- L16 _typedef_ `using TaskFutures = TaskFuturesUE;`
- L17 _typedef_ `using TaskThreadPool = TaskThreadPoolUE;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/utils/TaskThreadPoolStd.h` (Private)


#### class `TaskThreadPoolStd`  
`class TaskThreadPoolStd`  
_L23-54_
- L26 _public prototype_ `static std::shared_ptr<TaskThreadPoolStd> GlobalInstance(bool createIfNotAvailable, int numThreads = MaxNumThreads());`
- L27 _public prototype_ `static void ParallelFor(int number, std::function<void(int)>&& Body);`
- L29 _public prototype_ `TaskThreadPoolStd(int numThreads);`
- L30 _public prototype_ `~TaskThreadPoolStd();`
- L32 _public prototype_ `void Stop();`
- L34 _public function_ `size_t NumThreads() const`
- L35 _public prototype_ `void SetNumThreads(int numThreads);`
- L36 _public prototype_ `static size_t MaxNumThreads();`
- L38 _public prototype_ `TaskFutureStd AddTask(std::function<void()>&& task);`
- L40 _public prototype_ `void AddTaskRangeAndWait(int numTasks, const std::function<void(int, int)>& processFunction, int numThreadsToUseHint = -1);`
- L43 _public prototype_ `void RunTask();` — explicitly run a task
- L46 _private prototype_ `void RunWorkerThread();`
- L49 _private member_ `std::atomic<bool> m_stop;`
- L50 _private member_ `std::mutex m_mutex;`
- L51 _private member_ `std::condition_variable m_conditionVariable;`
- L52 _private member_ `std::deque<std::packaged_task<void()>> m_tasks;`
- L53 _private member_ `std::vector<std::thread> m_workerThreads;`

#### class `TaskFutureStd`  
`class TaskFutureStd`  
_L56-73_
- L59 _public function_ `TaskFutureStd() : m_future(), m_pool(nullptr)`
- L60 _public function_ `TaskFutureStd(std::future<void>&& future, TaskThreadPoolStd* pool) : m_future(std::move(future)), m_pool(pool)`
- L61 _public prototype_ `TaskFutureStd(TaskFutureStd&&) = default;`
- L62 _public prototype_ `TaskFutureStd(const TaskFutureStd&) = delete;`
- L63 _public prototype_ `TaskFutureStd& operator=(TaskFutureStd&&) = default;`
- L64 _public prototype_ `TaskFutureStd& operator=(const TaskFutureStd&) = delete;`
- L66 _public prototype_ `bool Valid() const;`
- L67 _public prototype_ `bool Ready() const;`
- L68 _public prototype_ `void Wait();`
- L71 _private member_ `std::future<void> m_future;`
- L72 _private member_ `TaskThreadPoolStd* m_pool;`

#### class `TaskFuturesStd`  
`class TaskFuturesStd`  
_L75-88_
- L78 _public prototype_ `TaskFuturesStd() = default;`
- L79 _public prototype_ `~TaskFuturesStd();`
- L81 _public function_ `void Reserve(size_t size)`
- L83 _public prototype_ `void Add(TaskFutureStd&& future);`
- L84 _public prototype_ `void Wait();`
- L87 _private member_ `std::vector<TaskFutureStd> m_futures;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/utils/TaskThreadPoolUE.h` (Private)


#### class `TaskThreadPoolUE`  
`class TaskThreadPoolUE`  
_L22-43_
- L25 _public prototype_ `static std::shared_ptr<TaskThreadPoolUE> GlobalInstance(bool createIfNotAvailable, int numThreads = MaxNumThreads());`
- L26 _public prototype_ `static void ParallelFor(int number, std::function<void(int)>&& Body);`
- L28 _public prototype_ `TaskThreadPoolUE();`
- L29 _public prototype_ `TaskThreadPoolUE(int numThreads);`
- L30 _public prototype_ `~TaskThreadPoolUE();`
- L32 _public prototype_ `static size_t MaxNumThreads();`
- L34 _public prototype_ `void Stop();`
- L35 _public prototype_ `size_t NumThreads() const;`
- L36 _public prototype_ `void SetNumThreads(int numThreads);`
- L37 _public prototype_ `TaskFutureUE AddTask(std::function<void()>&& InFunction);`
- L38 _public prototype_ `void AddTaskRangeAndWait(int numTasks, const std::function<void(int, int)>& processFunction, int numThreadsToUseHint = -1);`
- L39 _public prototype_ `void RunTask();`
- L42 _private member_ `std::atomic<int> m_numThreads{};`

#### class `TaskFutureUE`  
`class TaskFutureUE`  
_L45-65_
- L48 _public prototype_ `TaskFutureUE();`
- L49 _public prototype_ `~TaskFutureUE();`
- L51 _public prototype_ `TaskFutureUE(FGraphEventRef Task);`
- L53 _public prototype_ `TaskFutureUE(TaskFutureUE&&);`
- L54 _public prototype_ `TaskFutureUE(const TaskFutureUE&) = delete;`
- L55 _public prototype_ `TaskFutureUE& operator=(TaskFutureUE&&);`
- L56 _public prototype_ `TaskFutureUE& operator=(const TaskFutureUE&) = delete;`
- L58 _public prototype_ `bool Valid() const;`
- L60 _public prototype_ `void Wait();` — bool Ready() const;
- L64 _private member_ `std::unique_ptr<Data> m_data;`

#### class `TaskFuturesUE`  
`class TaskFuturesUE`  
_L67-80_
- L70 _public prototype_ `TaskFuturesUE() = default;`
- L71 _public prototype_ `~TaskFuturesUE();`
- L73 _public function_ `void Reserve(size_t size)`
- L75 _public prototype_ `void Add(TaskFutureUE&& future);`
- L76 _public prototype_ `void Wait();`
- L79 _private member_ `std::vector<TaskFutureUE> m_futures;`

#### Free symbols / members of external scopes

- L15 _typedef_ `using FGraphEvent = class FBaseGraphTask;`
- L16 _typedef_ `using FGraphEventRef = TRefCountPtr<class FBaseGraphTask>;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/utils/TaskThreadPoolUtils.h` (Private)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace TaskThreadPoolUtils`
- L33 _prototype_ `void RunTaskRangeAndWait(std::shared_ptr<TaskThreadPool> threadPool, int range, const std::function<void(int, int)> &processFunction, int numThreadsToUseHint = -1);` (scope `TaskThreadPoolUtils`) — @brief Run the tasks range with the provided thread pool. If the thread pool is not available, run all tasks in one call to processing function Thread pool will call the processing function (which takes the start and end indices) in parallel until the whole range of tasks is processed. If the thread pool is not available, the processing function will be called for the whole range in the thread that called this function @note It is assumed that the first tasks starts with index 0 and that the last is at index (range - 1) @param[in] threadPool            - thread pool to use @param[in] range                 - range of tasks @param[in] processingFunction    - function that takes start and end index for the tasks to be processed @param[in] numThreadsToUseHint   - optional, hint on how many threads to use at once (default is -1 which means use max available)
- L52 _prototype_ `void RunTaskRangeAndWait(int range, const std::function<void(int, int)> &processFunction, int numThreadsToUseHint = -1, bool createThreadPoolIfNotAvailable = true);` (scope `TaskThreadPoolUtils`) — @brief Create thread pool (optional) and run the tasks range. If the thread pool is not available, run all tasks in one call to processing function Thread pool will call the processing function (which takes the start and end indices) in parallel until the whole range of tasks is processed. If the thread pool is not available (not created or cant be created), the processing function will be called for the whole range in the thread that called this function @note It is assumed that the first tasks starts with index 0 and that the last is at index (range - 1) @param[in] range                             - range of tasks @param[in] processingFunction                - function that takes start and end index for the tasks to be processed @param[in] createThreadPoolIfNotAvailable    - optional, indicates should the thread pool be created if not already available (default is true) @param[in] numThreadsToUseHint               - optional, hint on how many threads to use at once (default is -1 which means use max available)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/utils/Timecode.h` (Private)


#### class `Timecode`  
`class Timecode`  
_L16-70_
- desc: Class to calculate Timecode
- L18 _public prototype_ `Timecode() = default;`
- L20 _public function_ `Timecode(int hours, int minutes, int seconds, int frames, double fps) : m_hours(hours) , m_minutes(minutes) , m_seconds(seconds) , m_frames(frames) , m_fps(fps)`
- L30 _public function_ `void AddSeconds(double seconds)`
- L36 _public function_ `void Round()`
- L42 _public function_ `void MakeCanonical()`
- L55 _public function_ `std::string to_string() const`
- L62 _public function_ `double GetFps() const`
- L65 _private member_ `int m_hours;`
- L66 _private member_ `int m_minutes;`
- L67 _private member_ `int m_seconds;`
- L68 _private member_ `double m_frames;`
- L69 _private member_ `double m_fps;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/include/carbon/utils/Timer.h` (Private)


#### class `Timer`  
`class Timer`  
_L11-29_
- L14 _public function_ `Timer()`
- L19 _public function_ `void Restart()`
- L21 _public function_ `double Current()`
- L28 _private member_ `std::chrono::high_resolution_clock::time_point m_start;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/carbon/src/io/Utils.h` (Private)


#### Free symbols / members of external scopes

- L14 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) JsonElement WriteFileinfo();`
- L18 _prototype_ `void ReadCameraMetadataJson(const JsonElement& json, std::string& label, std::string& model, int& width, int& height);`
- L19 _prototype_ `void ReadSensorMetadataXml(XMLElement* xmlSensor, int& width, int& height, int& id);`
- L21 _prototype_ `void WriteCameraMetadataJson(JsonElement& json, int width, int height, const std::string& label, const std::string& model);`
- L22 _prototype_ `void WriteSensorMetadataXml(XMLElement& xmlSensor, int width, int height, int id);`
- L23 _prototype_ `void WriteCameraMetadataXml(XMLElement& xmlCamera, const std::string& label, int id);`
- L26 _prototype_ `template<class T> void WriteIntrinsicsJson(JsonElement& json, const Eigen::Matrix3<T>& intrinsics);`
- L29 _prototype_ `template<class T> void WriteIntrinsicsXml(XMLElement& xmlCalibration, const Eigen::Matrix3<T>& intrinsics, int width, int height);`
- L32 _prototype_ `template<class T> void ReadIntrinsicsJson(const JsonElement& json, Eigen::Matrix3<T>& intrinsics);`
- L35 _prototype_ `template<class T> void ReadIntrinsicsXml(XMLElement* xmlCalibration, Eigen::Matrix3<T>& intrinsics, int width, int height);`
- L38 _prototype_ `template<class T> JsonElement WriteExtrinsicsJson(const Eigen::Matrix<T, 3, 4>& transform);`
- L41 _prototype_ `template<class T> void WriteExtrinsicsXml(XMLElement& xmlCamera, const Eigen::Matrix<T, 3, 4>& transform);`
- L44 _prototype_ `template<class T> void ReadExtrinsicsJson(const JsonElement& json, Eigen::Matrix<T, 3, 4>& transform);`
- L47 _prototype_ `template<class T> void ReadGlobalTransformXml(XMLElement* xmlChunk, Eigen::Matrix4d& transform, T& scale);`
- L50 _prototype_ `template<class T> void ReadExtrinsicsXml(XMLElement* xmlCamera, const Eigen::Matrix4d& globalTransform, Eigen::Matrix<T, 3, 4>& cameraExtrinsics, T scale);`
- L56 _prototype_ `template<class T> void WriteDistortionOpenCVJson(JsonElement& json, const Eigen::Vector<T, 5>& distortion);`
- L59 _prototype_ `template<class T> void WriteDistortionOpenCVXml(XMLElement& json, const Eigen::Vector<T, 5>& distortion);`
- L62 _prototype_ `template<class T> void ReadDistortionOpenCVJson(const JsonElement& json, Eigen::Vector<T, 5>& distortion);`
- L65 _prototype_ `template<class T> void ReadDistortionOpenCvXml(XMLElement* xmlCalibration, Eigen::Vector<T, 5>& distortion);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/conformer/include/conformer/BrowLandmarksGenerator.h` (Private)


#### class `BrowLandmarksGenerator`  
`template <class T> class BrowLandmarksGenerator`  
_L13-38_
- L16 _public prototype_ `BrowLandmarksGenerator();`
- L17 _public prototype_ `~BrowLandmarksGenerator();`
- L19 _public prototype_ `void Init(const TemplateDescription& templateDesc);`
- L21 _public prototype_ `void SetLandmarks(const std::pair<LandmarkInstance<T, 2>, Camera<T>>& landmarks);`
- L23 _public prototype_ `MeshLandmarks<T> Generate(const Eigen::Matrix<T, 3, -1>& vertices, const Affine<T, 3, 3>& mesh2scanTransform, const T mesh2scanScale, float& fractionLandmarksInBrowRegion, bool concatenate = false);`
- L30 _private member_ `std::vector<int> m_browMaskL, m_browMaskR;`
- L30 _private member_ `std::vector<int> m_browMaskL, m_browMaskR;`
- L31 _private member_ `std::pair<LandmarkInstance<T, 2>, Camera<T>> m_landmarks;`
- L32 _private member_ `Mesh<T> m_topology;`
- L33 _private member_ `MeshLandmarks<T> m_templateMeshLandmarks;`
- L35 _private prototype_ `static bool CheckLandmarkInBrowsMask(const Eigen::Matrix<T, 3, -1>& vertices, const Camera<T>& camera, const Affine<T, 3, 3>& mesh2scanTransform, const T mesh2ScanScale, const Mesh<T>& browMesh, const Eigen::Matrix<T, 2, -1>& curvePts, int ptIndex, BarycentricCoordinates<T>& landmarkBarycentricCoordinates);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/conformer/include/conformer/EyeFittingHelper.h` (Private)


#### class `EyeFittingHelper`  
`template <class T> class EyeFittingHelper`  
_L13-27_
- L16 _public prototype_ `static bool UpdateScanMaskBasedOnLandmarks(const Eigen::Matrix2X<T>& lowerLid, const Eigen::Matrix2X<T>& upperLid, const Eigen::Matrix2X<T>& iris, const Camera<T>& camera, const std::shared_ptr<const Mesh<T>>& scanMesh, Eigen::VectorX<T>& mask);`
- L23 _public prototype_ `static const std::vector<int> CalculateIrisInliers(const Eigen::Matrix2X<T>& lowerLid, const Eigen::Matrix2X<T>& upperLid, const Eigen::Matrix2X<T>& iris, const Camera<T>& camera);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/conformer/include/conformer/FaceFitting.h` (Private)


#### struct `FaceFittingConstraintsDebugInfo`  
`template <class T> struct FaceFittingConstraintsDebugInfo`  
_L30-38_
- desc: Debug Info for current state
- L32 _public member_ `typename MeshCorrespondenceSearch<T>::Result correspondences;`
- L33 _public member_ `LandmarkConstraintsData<T> landmarkConstraints;`
- L34 _public member_ `LandmarkConstraintsData<T> curveConstraints;`
- L35 _public member_ `LandmarkConstraintsData<T> lipConstraintsUpper;`
- L36 _public member_ `LandmarkConstraintsData<T> lipConstraintsLower;`
- L37 _public member_ `LipClosureConstraintsData<T> lipClosureConstraintsData;`

#### class `FaceFitting`  
`template <class T> class FaceFitting`  
_L46-314_
- desc: Module to align a template mesh with a high resolution 3D scan. Implemented for T=float and T=double
- L49 _public prototype_ `FaceFitting();`
- L50 _public prototype_ `~FaceFitting();`
- L51 _public prototype_ `FaceFitting(FaceFitting&& o);`
- L52 _public prototype_ `FaceFitting(const FaceFitting& o) = delete;`
- L53 _public prototype_ `FaceFitting& operator=(FaceFitting&& o);`
- L54 _public prototype_ `FaceFitting& operator=(const FaceFitting& o) = delete;`
- L57 _public function_ `const Configuration& RigidRegistrationConfiguration() const` — get/set the model registration settings (identity PCA model)
- L58 _public function_ `Configuration& RigidRegistrationConfiguration()`
- L61 _public function_ `const Configuration& ModelRegistrationConfiguration() const` — get/set the model registration settings (identity PCA model)
- L62 _public function_ `Configuration& ModelRegistrationConfiguration()`
- L65 _public function_ `const Configuration& FineRegistrationConfiguration() const` — get/set the fine registration settings (per-vertex deformation)
- L66 _public function_ `Configuration& FineRegistrationConfiguration()`
- L68 _public prototype_ `void SetGlobalUserDefinedLandmarkAndCurveWeights(const std::map<std::string, T>& userDefinedLandmarkAndCurveWeights);`
- L70 _public prototype_ `void SetPerInstanceUserDefinedLandmarkAndCurveWeights(const std::vector<std::map<std::string, T>>& perInstanceUserDefinedLandmarkAndCurveWeights);`
- L73 _public prototype_ `void SetupEyeballConstraint(const Eigen::Matrix<T, 3, -1>& leftEyeballVertices, const Eigen::Matrix<T, 3, -1>& rightEyeballVertices);` — Setup rest pose for eyeball constraint with current deformed mesh
- L76 _public prototype_ `void SetFixedCorrespondenceData(const std::vector<std::shared_ptr<const fitting_tools::CorrespondenceData<T>>>& correspondenceData);` — Set fixed correspondence data which will disable ICP when fitting.
- L79 _public prototype_ `void ClearFixedCorrespondeceData();` — Clear fixed correspondence data to enable ICP.
- L82 _public prototype_ `bool HasFixedCorrespondenceData() const;` — Check if the object has fixed correspondence data.
- L85 _public prototype_ `void SetTopology(const Mesh<T>& mesh);` — Set the source mesh.
- L88 _public prototype_ `void SetSourceMesh(const Mesh<T>& mesh);` — Set the source mesh.
- L91 _public prototype_ `void SetEyeballMesh(const Mesh<T>& mesh);` — Set the source mesh.
- L93 _public prototype_ `void SetSourceAndDeformedMesh(const Mesh<T>& baseMesh, const Mesh<T>& deformedMesh);`
- L96 _public prototype_ `void SetEyeConstraintVertexWeights(const VertexWeights<T>& vertexWeightsLeftEye, const VertexWeights<T>& vertexWeightsRightEye);` — Sets the eyeball constraint vertex weights
- L99 _public prototype_ `void SetInnerLipInterfaceVertices(const VertexWeights<T>& maskUpperLip, const VertexWeights<T>& maskLowerLip);` — Sets the lip closure constraint masks
- L102 _public prototype_ `void SetSelfCollisionVertices(const std::vector<std::pair<std::vector<int>, std::vector<int>>>& selfCollisionMasks);` — Sets the collision constraint masks
- L105 _public prototype_ `void SetStaticCollisionMasks(const std::vector<std::tuple<std::vector<int>, Mesh<T>, std::vector<int>>>& staticCollisions);` — Sets the static collision constraints
- L107 _public prototype_ `void SetStaticCollisionVertices(const std::vector<Eigen::Matrix<T, 3, -1>>& staticVertices);`
- L110 _public prototype_ `void SetMeshLandmarks(const MeshLandmarks<T>& meshLandmarks);` — Sets the mesh landmarks that are use for registration
- L113 _public prototype_ `void SetTargetMeshes(const std::vector<std::shared_ptr<const Mesh<T>>>& targetMeshes, const std::vector<Eigen::VectorX<T>>& targetWeights);` — Set the target meshes from multiple frames
- L115 _public prototype_ `void SetTargetDepths(const std::vector<std::vector<std::shared_ptr<const DepthmapData<T>>>>& targetDepths);`
- L118 _public prototype_ `void SetTarget2DLandmarks(const std::vector<std::vector<std::pair<LandmarkInstance<T, 2>, Camera<T>>>>& landmarks);` — Set the target 2D landmarks
- L121 _public prototype_ `void SetTarget3DLandmarks(const std::vector<LandmarkInstance<T, 3>>& landmarks);` — Set the target 3D landmarks
- L124 _public prototype_ `void SetModelFlowConstraints(const std::map<std::string, std::shared_ptr<const FlowConstraintsData<T>>>& flowConstraintsData);` — Set model flow constraints
- L125 _public prototype_ `bool HasModelFlowConstraints() const;`
- L128 _public prototype_ `void SetUVFlowConstraints(const std::map<std::string, std::shared_ptr<const FlowConstraintsData<T>>>& flowConstraintsData);` — Set uv flow constraints
- L129 _public prototype_ `bool HasUVFlowConstraints() const;`
- L132 _public prototype_ `void SetFixedVertices(const std::vector<int>& fixedVertices);` — Set the fixed vertices
- L135 _public prototype_ `void LoadModel(const std::string& identityModelFileOrData);` — @see PatchBlendModel::LoadModel() load model from filename or data as Json string
- L138 _public prototype_ `void LoadModelBinary(const std::string& patchModelBinaryFilepath);` — @see PatchBlendModel::LoadModelBinary() load model from filename
- L141 _public prototype_ `void SetCurrentDeformedVertices(const Eigen::Matrix<T, 3, -1>& deformedVertices);` — Set the current deformed vertices
- L144 _public prototype_ `void SetCurrentModelParameters(const Eigen::VectorXf& modelParameters);` — Set the current model state
- L146 _public prototype_ `const Eigen::VectorX<T>& CurrentModelParameters() const;`
- L149 _public prototype_ `const Eigen::Matrix<T, 3, -1>& CurrentDeformedVertices() const;` — @return the current deformed vertices
- L152 _public prototype_ `const std::map<std::string, Eigen::Vector3<T>> CurrentMeshLandmarks() const;` — @return the current mesh landmarks world position
- L155 _public prototype_ `const std::map<std::string, std::vector<Eigen::Vector3<T>>> CurrentMeshCurves() const;` — @return the current mesh curve points world position
- L162 _public prototype_ `Affine<T, 3, 3> RegisterRigid(const Affine<T, 3, 3>& source2target, const VertexWeights<T>& searchWeights, int numIterations = 10, int scanFrame = 0);` — Run rigid registration. @param sourceAffine                    The (current) affine transformation of the source mesh to the target mesh. @param numIterations                   The number of iterations for rigid registration.
- L164 _public prototype_ `std::vector<Affine<T, 3, 3>> RegisterRigid(const std::vector<Affine<T, 3, 3>>& source2target, const VertexWeights<T>& searchWeights, int numIterations = 10);`
- L168 _public prototype_ `void ResetNonrigid();` — Resets the identity model parameters as well as the per vertex offsets
- L175 _public prototype_ `std::vector<Affine<T, 3, 3>> RegisterNonRigid(const std::vector<Affine<T, 3, 3>>& source2target, const VertexWeights<T>& searchWeights, int numIterations = 10);` — Nonrigid registration using the identity model (discard the per-vertex offsets) @param sourceAffine                    The (current) affine transformation of the source mesh to the target mesh. @param numIterations                   The number of iterations for rigid registration.
- L181 _public prototype_ `void ResetFine();` — Resets the fine registration (per vertex offsets)
- L188 _public prototype_ `std::vector<Affine<T, 3, 3>> RegisterFine(const std::vector<Affine<T, 3, 3>>& source2target, const VertexWeights<T>& searchWeights, int numIterations = 10);` — Nonrigid registration with per-vertex displacement @param source2target                   The (current) affine transformation of the source mesh to the target mesh. @param numIterations                   The number of iterations for rigid registration.
- L192 _public prototype_ `std::shared_ptr<const FaceFittingConstraintsDebugInfo<T>> CurrentDebugConstraints(const Affine<T, 3, 3>& source2target, int frame);` — @return debug information to visualize the data constraints such as ICP and landmarks
- L195 _private prototype_ `void InitIcpConstraints(int numOfObservations);`
- L196 _private prototype_ `void Init2DLandmarksConstraints(int numOfObservations);`
- L197 _private prototype_ `void Init3DLandmarksConstraints(int numOfObservations);`
- L200 _private prototype_ `void LoadInitialCorrespondencesVertices(const Eigen::Matrix<T, 3, -1>& sourceVertices);` — Loads the vertices that are used for the initial correspondences search. It does *not* update the deformation model.
- L202 _private prototype_ `void UpdateIcpConfiguration(const Configuration& targetConfig);`
- L203 _private prototype_ `void Update2DLandmarkConfiguration(const Configuration& targetConfig);`
- L204 _private prototype_ `void Update3DLandmarkConfiguration(const Configuration& targetConfig);`
- L205 _private prototype_ `void UpdateLipClosureConfiguration(const Configuration& targetConfig);`
- L206 _private prototype_ `void UpdateIcpWeights(const VertexWeights<T>& weights);`
- L209 _private member_ `Configuration m_rigidFittingConfig = { std::string("Rigid Fitting Configuration"), {`
- L228 _private member_ `Configuration m_modelFittingConfig = { std::string("Model Fitting Configuration"), {`
- L257 _private member_ `Configuration m_fineFittingConfig = { std::string("Fine Fitting Configuration"), {`
- L313 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/conformer/include/conformer/FittingInitializer.h` (Private)


#### class `FittingInitializer`  
`template <class T> class FittingInitializer`  
_L29-61_
- desc: Module for initial rigid alignment of assets before fitting. Implemented for T=float and T=double
- L32 _public prototype_ `FittingInitializer();`
- L33 _public prototype_ `~FittingInitializer();`
- L34 _public prototype_ `FittingInitializer(FittingInitializer&& o);`
- L35 _public prototype_ `FittingInitializer(const FittingInitializer& o) = delete;`
- L36 _public prototype_ `FittingInitializer& operator=(FittingInitializer&& o);`
- L37 _public prototype_ `FittingInitializer& operator=(const FittingInitializer& o) = delete;`
- L39 _public prototype_ `void SetTargetLandmarks(const std::vector<std::vector<std::pair<LandmarkInstance<T, 2>, Camera<T>>>>& landmarks);`
- L41 _public prototype_ `void SetTargetMeshes(const std::vector<std::shared_ptr<const Mesh<T>>>& mesh);`
- L43 _public prototype_ `void SetToScanTransforms(const std::vector<Affine<T, 3, 3>>& transforms);`
- L45 _public prototype_ `bool InitializeEyes(Affine<T, 3, 3>& leftEyeToHead, Affine<T, 3, 3>& rightEyeToHead, const std::map<std::string, std::vector<Eigen::Vector3<T>>>& leftCurves, const std::map<std::string, std::vector<Eigen::Vector3<T>>>& rightCurves, int frame) const;`
- L51 _public prototype_ `bool InitializeTeeth(Affine<T, 3, 3>& teethToHead, const std::map<std::string, Eigen::Vector3<T>>& currentMeshLandmarks, int frame) const;`
- L53 _public prototype_ `bool InitializeFace(std::vector<Affine<T, 3, 3>>& toScanTransform, std::vector<T>& toScanScale, const std::map<std::string, Eigen::Vector3<T>>& currentMeshLandmarks, bool withScale = false) const;`
- L60 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

#### struct `fitting_tools::CorrespondenceData`  
`template <class T> struct CorrespondenceData`  
_L67-77_
- L69 _public member_ `std::vector<int> srcIDs;`
- L70 _public member_ `std::vector<BarycentricCoordinates<T, 3>> targetBCs;`
- L72 _public prototype_ `Eigen::Matrix<T, 3, -1> EvaluateTargetBCs(const Eigen::Matrix<T, 3, -1>& inputPoints) const;`
- L74 _public prototype_ `TITAN_NAMESPACE::JsonElement SaveToJson() const;`
- L75 _public prototype_ `bool LoadFromJson(const TITAN_NAMESPACE::JsonElement& json);`

#### Free symbols / members of external scopes

- L63 _namespace_ `namespace fitting_tools`
- L80 _prototype_ `template <class T> std::shared_ptr<const CorrespondenceData<T>> FindClosestCorrespondences(const std::shared_ptr<const Mesh<T>>& src, const std::shared_ptr<const Mesh<T>>& tgt, const VertexWeights<T>& srcWeights);` (scope `fitting_tools`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/conformer/include/conformer/GeometryConstraints.h` (Private)


#### class `GeometryConstraints`  
`template <class T> class GeometryConstraints`  
_L22-83_
- desc: Class to evaluate ICP correspondences (point2point and/or point2surface)
- L25 _public prototype_ `GeometryConstraints();`
- L26 _public prototype_ `~GeometryConstraints();`
- L27 _public prototype_ `GeometryConstraints(GeometryConstraints&& o);`
- L28 _public prototype_ `GeometryConstraints(const GeometryConstraints& o) = delete;`
- L29 _public prototype_ `GeometryConstraints& operator=(GeometryConstraints&& o);`
- L30 _public prototype_ `GeometryConstraints& operator=(const GeometryConstraints& o) = delete;`
- L33 _public prototype_ `void SetSourceWeights(const VertexWeights<T>& vertexWeights);` — Sets the correspondence search vertex weights
- L36 _public prototype_ `void SetTargetMesh(const std::shared_ptr<const Mesh<T>>& targetMesh);` — Set the target mesh
- L39 _public prototype_ `void AddTargetDepthAndNormals(const std::shared_ptr<const DepthmapData<T>>& depthData);` — Set the target depthmap and normals
- L42 _public prototype_ `void SetTargetWeights(const Eigen::Vector<T, -1>& targetWeights);` — Set custom target vertex weights for the target mesh.
- L44 _public prototype_ `const Configuration& GetConfiguration() const;`
- L46 _public prototype_ `void SetConfiguration(const Configuration& config, bool ignoreUnknownKeys = false);`
- L49 _public prototype_ `void ClearPreviousCorrespondences();` — Clears any correspondences.
- L52 _public prototype_ `bool HasCorrespondences() const;` — @returns True if ICP correspondences have been set up using SetupCorrespondences() or EvaluateICP()
- L55 _public prototype_ `void SetupCorrespondences(const Mesh<T>& sourceMesh, bool useTarget2Source);` — Find the correspondences and store the result internally (which is then used for EvaluateICP)
- L61 _public prototype_ `Cost<T> EvaluateICP(const DiffDataMatrix<T, 3, -1>& vertices);` — Evaluate the ICP constraint. @param[in] vertices  The differentiable input vertices.
- L64 _public prototype_ `void FindCorrespondences(const Eigen::Matrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& normals, typename MeshCorrespondenceSearch<T>::Result& correspondences) const;` — Finds the correspondences and stores the result in @p correspondences
- L69 _public prototype_ `void SetupConstraints(const Eigen::Transform<T, 3, Eigen::Affine>& rigidTransform, const Eigen::Matrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& normals, VertexConstraints<T, 1, 1>& point2SurfaceVertexConstraints, VertexConstraints<T, 3, 1>& point2PointVertexConstraints);` — Creates the constraints
- L75 _public prototype_ `const std::shared_ptr<const Mesh<T>> TargetMesh() const;`
- L78 _private prototype_ `void FindTarget2SourceCorrespondences(const Mesh<T>& sourceMesh);`
- L82 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/conformer/include/conformer/IdentityModelFitting.h` (Private)


#### class `IdentityModelFitting`  
`template <class T> class IdentityModelFitting`  
_L31-239_
- desc: Module to align a template eye mesh with target landmarks. Implemented for T=float and T=double
- L34 _public prototype_ `IdentityModelFitting();`
- L35 _public prototype_ `~IdentityModelFitting();`
- L36 _public prototype_ `IdentityModelFitting(IdentityModelFitting&& o);`
- L37 _public prototype_ `IdentityModelFitting(const IdentityModelFitting& o) = delete;`
- L38 _public prototype_ `IdentityModelFitting& operator=(IdentityModelFitting&& o);`
- L39 _public prototype_ `IdentityModelFitting& operator=(const IdentityModelFitting& o) = delete;`
- L41 _public prototype_ `void LoadModel(const std::string& identityModelFileOrString);`
- L44 _public function_ `const Configuration& RigidRegistrationConfiguration() const` — get/set the rigid registration settings
- L45 _public function_ `Configuration& RigidRegistrationConfiguration()`
- L48 _public function_ `const Configuration& ModelRegistrationConfiguration() const` — get/set the model registration settings (identity PCA model)
- L49 _public function_ `Configuration& ModelRegistrationConfiguration()`
- L52 _public function_ `const Configuration& FineRegistrationConfiguration() const` — get/set the fine registration settings (per-vertex deformation)
- L53 _public function_ `Configuration& FineRegistrationConfiguration()`
- L56 _public prototype_ `void SetSourceMesh(const Mesh<T>& mesh);` — Set the source mesh.
- L59 _public prototype_ `void SetTargetMeshes(const std::vector<std::shared_ptr<const Mesh<T>>>& targetMeshes, const std::vector<Eigen::VectorX<T>>& targetWeights, bool alignedInputs = false);` — Set the target meshes
- L64 _public prototype_ `void SetTargetDepths(const std::vector<std::vector<std::shared_ptr<const DepthmapData<T>>>>& targetDepths);` — Set the target depth
- L67 _public prototype_ `void SetMeshLandmarks(const MeshLandmarks<T>& meshLandmarks);` — Sets the mesh landmarks that are use for registration
- L70 _public prototype_ `void SetTarget2DLandmarks(const std::vector<std::vector<std::pair<LandmarkInstance<T, 2>, Camera<T>>>>& landmarks);` — Set the target 2D landmarks
- L73 _public prototype_ `void SetTarget3DLandmarks(const std::vector<LandmarkInstance<T, 3>>& landmarks);` — Set the target 3D landmarks
- L76 _public prototype_ `void SetPerInstanceUserDefinedLandmarkAndCurveWeights(const std::vector<std::map<std::string, T>>& perInstanceUserDefinedLandmarkAndCurveWeights);` — Set per instance user confidences for landmarks and curves
- L79 _public prototype_ `void SetGlobalUserDefinedLandmarkAndCurveWeights(const std::map<std::string, T>& userDefinedLandmarkAndCurveWeights);` — Set global provided user confidences for landmarks and curves
- L82 _public prototype_ `void SetCollisionMasks(const VertexWeights<T>& maskSource, const VertexWeights<T>& maskTarget);` — Sets the collision constraint masks
- L85 _public prototype_ `const Eigen::Matrix<T, 3, -1>& CurrentDeformedVertices() const;` — @return the current deformed vertices
- L88 _public prototype_ `const std::map<std::string, Eigen::Vector3<T>> CurrentMeshLandmarks() const;` — @return the current mesh landmarks world position
- L91 _public prototype_ `const std::map<std::string, std::vector<Eigen::Vector3<T>>> CurrentMeshCurves() const;` — @return the current mesh curve points world position
- L94 _public prototype_ `void ResetNonrigid();` — Resets the identity model parameters as well as the per vertex offsets
- L101 _public prototype_ `Affine<T, 3, 3> RegisterRigid(const Affine<T, 3, 3>& source2target, const VertexWeights<T>& searchWeights, int numIterations = 10, int scanFrame = 0);` — Run rigid registration. @param sourceAffine                    The (current) affine transformation of the source mesh to the target mesh. @param numIterations                   The number of iterations for rigid registration.
- L103 _public prototype_ `std::vector<Affine<T, 3, 3>> RegisterRigid(const std::vector<Affine<T, 3, 3>>& source2target, const std::vector<VertexWeights<T>>& searchWeights, int numIterations = 10);`
- L112 _public prototype_ `std::vector<Affine<T, 3, 3>> RegisterNonRigid(const std::vector<Affine<T, 3, 3>>& source2target, const std::vector<VertexWeights<T>>& searchWeights, int numIterations = 10);` — Nonrigid registration using the identity model (discard the per-vertex offsets) @param source2target                    The (current) affine transformation from source to target. @param numIterations                   The number of iterations for registration.
- L124 _public prototype_ `Affine<T, 3, 3> RegisterNonRigidAsset(const std::vector<Affine<T, 3, 3>>& head2Scan, const Affine<T, 3, 3>& assetToHead, const std::vector<VertexWeights<T>>& searchWeights, int numIterations = 10);` — Nonrigid registration using the identity model (discard the per-vertex offsets) @param head2Scan                    The (current) affine transformation from head to target scan (for each frame). @param assetToHead                  The (current) affine transformation from fitting asset to head. @param searchWeights                Vertices to include in fitting. @param numIterations                The number of iterations for registration. @return                             Estimated affine transform from fitting asset to head.
- L130 _public prototype_ `void ResetFine();` — Resets the fine registration (per vertex offsets)
- L137 _public prototype_ `std::vector<Affine<T, 3, 3>> RegisterFine(const std::vector<Affine<T, 3, 3>>& source2target, const std::vector<VertexWeights<T>>& searchWeights, int numIterations = 10);` — Nonrigid registration with per-vertex displacement @param source2target                   The (current) affine transformation of the source mesh to the target mesh. @param numIterations                   The number of iterations for rigid registration.
- L142 _private prototype_ `void InitIcpConstraints(int numOfObservations);`
- L143 _private prototype_ `void Init2DLandmarksConstraints(int numOfObservations);`
- L144 _private prototype_ `void Init3DLandmarksConstraints(int numOfObservations);`
- L146 _private prototype_ `void UpdateIcpConfiguration(const Configuration& targetConfig);`
- L147 _private prototype_ `void Update2DLandmarkConfiguration(const Configuration& targetConfig);`
- L148 _private prototype_ `void Update3DLandmarkConfiguration(const Configuration& targetConfig);`
- L149 _private prototype_ `void UpdateIcpWeights(const std::vector<VertexWeights<T>>& weights);`
- L152 _private member_ `Configuration m_rigidFittingConfig = { std::string("Asset Rigid Fitting Configuration"), {`
- L175 _private member_ `Configuration m_modelFittingConfig = { std::string("Asset Model Fitting Configuration"), {`
- L200 _private member_ `Configuration m_fineFittingConfig = { std::string("Asset Fine Fitting Configuration"), {`
- L238 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/conformer/include/conformer/PcaFittingWrapper.h` (Private)


#### class `PcaRigFitting`  
`template <class T> class PcaRigFitting`  
_L36-143_
- desc: Module for fitting PCA model to input data. Implemented for T=float
- L39 _public prototype_ `PcaRigFitting();`
- L40 _public prototype_ `~PcaRigFitting();`
- L41 _public prototype_ `PcaRigFitting(PcaRigFitting&& o);`
- L42 _public prototype_ `PcaRigFitting(const PcaRigFitting& o) = delete;`
- L43 _public prototype_ `PcaRigFitting& operator=(PcaRigFitting&& o);`
- L44 _public prototype_ `PcaRigFitting& operator=(const PcaRigFitting& o) = delete;`
- L46 _public prototype_ `void LoadRig(dna::Reader* dnaReader);`
- L48 _public prototype_ `void SaveRig(dna::Writer* dnaWriter);`
- L50 _public prototype_ `bool IsRigLoaded() const;`
- L51 _public prototype_ `bool HasNeckPCA() const;`
- L53 _public prototype_ `void SetFlowConstraints(const std::map<std::string, std::shared_ptr<const FlowConstraintsData<T>>>& flowConstraintsData);`
- L54 _public prototype_ `bool HasFlowConstraints() const;`
- L56 _public prototype_ `rt::PCARig GetRig();`
- L59 _public function_ `const Configuration& PcaRigFittingRegistrationConfiguration() const` — get/set the model registration settings (identity PCA model)
- L60 _public function_ `Configuration& PcaRigFittingRegistrationConfiguration()`
- L61 _public function_ `void ResetPcaRigFittingRegistrationConfiguration()`
- L64 _public prototype_ `void SetTargetMeshes(const std::vector<std::shared_ptr<const Mesh<T>>>& targetMeshes, const std::vector<Eigen::VectorX<T>>& targetWeights);` — Set the target mesh
- L67 _public prototype_ `void SetTargetDepths(const std::vector<std::vector<std::shared_ptr<const DepthmapData<T>>>>& targetDepths);` — Set the target depth
- L69 _public prototype_ `void SetTopology(const Mesh<T>& topology);`
- L71 _public prototype_ `void SetInnerLipInterfaceVertices(const VertexWeights<T>& maskUpperLip, const VertexWeights<T>& maskLowerLip);`
- L74 _public prototype_ `void SetMeshLandmarks(const MeshLandmarks<T>& headMeshLandmarks, const MeshLandmarks<T>& teethMeshLandmarks, const MeshLandmarks<T>& eyeLeftMeshLandmarks, const MeshLandmarks<T>& eyeRightMeshLandmarks);` — Sets the mesh landmarks that are use for registration
- L80 _public prototype_ `void SetTarget2DLandmarks(const std::vector<std::vector<std::pair<LandmarkInstance<T, 2>, Camera<T>>>>& landmarks);` — Set the target 2D landmarks
- L83 _public prototype_ `void SetCurrentVertices(const Eigen::Matrix<T, 3, -1>& headVertices);` — Sets the current face vertices and estimate the pca coefficients
- L86 _public prototype_ `Eigen::Matrix<T, 3, -1> CurrentVertices(const int meshId = 0);` — @return the estimated vertices
- L91 _public prototype_ `std::vector<Affine<T, 3, 3>> RegisterPcaRig(const std::vector<Affine<T, 3, 3>>& source2target, const VertexWeights<T>& faceSearchWeights, const VertexWeights<T>& neckSearchWeights, int numIterations = 10);` — PCA rig registration using the PCA rig model
- L97 _private prototype_ `void InitIcpConstraints(int numOfObservations);`
- L98 _private prototype_ `void Init2DLandmarksConstraints(int numOfObservations);`
- L100 _private prototype_ `void UpdateIcpConfiguration(const Configuration& targetConfig);`
- L101 _private prototype_ `void Update2DLandmarkConfiguration(const Configuration& targetConfig);`
- L102 _private prototype_ `void UpdateLipClosureConfiguration(const Configuration& targetConfig);`
- L103 _private prototype_ `void UpdateIcpWeights(const VertexWeights<T>& weights);`
- L106 _private member_ `static inline Configuration s_defaultPcaRigFittingConfig = { std::string("PCA Rig Fitting Configuration"), {`
- L139 _private member_ `Configuration m_pcaRigFittingConfig = s_defaultPcaRigFittingConfig;`
- L142 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/conformer/include/conformer/RigLogicFitting.h` (Private)


#### class `RigLogicFitting`  
`template <class T> class RigLogicFitting`  
_L35-141_
- desc: Module to align a template eye mesh with target landmarks. Implemented for T=float and T=double
- L38 _public prototype_ `RigLogicFitting();`
- L39 _public prototype_ `~RigLogicFitting();`
- L40 _public prototype_ `RigLogicFitting(RigLogicFitting&& o);`
- L41 _public prototype_ `RigLogicFitting(const RigLogicFitting& o) = delete;`
- L42 _public prototype_ `RigLogicFitting& operator=(RigLogicFitting&& o);`
- L43 _public prototype_ `RigLogicFitting& operator=(const RigLogicFitting& o) = delete;`
- L45 _public prototype_ `void LoadRig(dna::Reader* dnaRig);`
- L47 _public prototype_ `void SetRig(const std::shared_ptr<const Rig<T>>& rig);`
- L50 _public function_ `const Configuration& RigLogicRegistrationConfiguration() const` — get/set the model registration settings (identity PCA model)
- L51 _public function_ `Configuration& RigLogicRegistrationConfiguration()`
- L54 _public prototype_ `void SetTargetMeshes(const std::vector<std::shared_ptr<const Mesh<T>>>& targetMeshes, const std::vector<Eigen::VectorX<T>>& targetWeights);` — Set the target mesh
- L57 _public prototype_ `void SetTargetDepths(const std::vector<std::vector<std::shared_ptr<const DepthmapData<T>>>>& targetDepths);` — Set the target depth
- L60 _public prototype_ `void SetGuiControls(const Eigen::VectorX<T>& currentControls);` — Set starting controls
- L63 _public prototype_ `void SetMeshLandmarks(const MeshLandmarks<T>& meshLandmarks);` — Sets the mesh landmarks that are use for registration
- L66 _public prototype_ `void SetTarget2DLandmarks(const std::vector<std::vector<std::pair<LandmarkInstance<T, 2>, Camera<T>>>>& landmarks);` — Set the target 2D landmarks
- L69 _public prototype_ `void SetTarget3DLandmarks(const std::vector<LandmarkInstance<T, 3>>& landmarks);` — Set the target 3D landmarks
- L72 _public prototype_ `void SetInnerLipInterfaceVertices(const VertexWeights<T>& maskUpperLip, const VertexWeights<T>& maskLowerLip);` — Set the lip collision vertices mask
- L75 _public prototype_ `void SetFixedCorrespondenceData(const std::vector<std::shared_ptr<const fitting_tools::CorrespondenceData<T>>>& correspondenceData);` — Set fixed correspondence data which will disable ICP when fitting.
- L78 _public prototype_ `void ClearFixedCorrespondeceData();` — Clear fixed correspondence data to enable ICP.
- L81 _public prototype_ `bool HasFixedCorrespondenceData() const;` — Check if the object has fixed correspondence data.
- L84 _public prototype_ `Eigen::VectorX<T> CurrentGuiControls() const;` — @return the estimated gui riglogic controls
- L87 _public prototype_ `Eigen::Matrix<T, 3, -1> CurrentVertices(const int meshId = 0);` — @return the estimated vertices
- L96 _public prototype_ `std::vector<Affine<T, 3, 3>> RegisterRigLogic(const std::vector<Affine<T, 3, 3>>& source2target, const VertexWeights<T>& searchWeights, int numIterations = 10);` — Nonrigid registration using the identity model (discard the per-vertex offsets) @param initialCorrespondencesVertices  The vertices that should be used for the initial correspondences search. @param sourceAffine                    The (current) affine transformation of the source mesh. @param targetAffine                    The target affine transformation of the target mesh. @param numIterations                   The number of iterations for registration.
- L101 _private prototype_ `void InitIcpConstraints(int numOfObservations);`
- L102 _private prototype_ `void Init2DLandmarksConstraints(int numOfObservations);`
- L103 _private prototype_ `void Init3DLandmarksConstraints(int numOfObservations);`
- L105 _private prototype_ `void UpdateIcpConfiguration(const Configuration& targetConfig);`
- L106 _private prototype_ `void Update2DLandmarkConfiguration(const Configuration& targetConfig);`
- L107 _private prototype_ `void Update3DLandmarkConfiguration(const Configuration& targetConfig);`
- L108 _private prototype_ `void UpdateLipClosureConfiguration(const Configuration& targetConfig);`
- L109 _private prototype_ `void UpdateIcpWeights(const VertexWeights<T>& weights);`
- L112 _private member_ `Configuration m_rigLogicFittingConfig = { std::string("RigLogic Fitting Configuration"), {`
- L140 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/conformer/include/conformer/TargetLandmarksHandler.h` (Private)


#### Free symbols / members of external scopes

- L9 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> const std::vector<std::map<std::string, T>> MaskLandmarksToAvoidAmbiguity(const std::map<std::string, T>& currentGlobalLandmarkWeights, const std::vector<std::vector<std::pair<LandmarkInstance<T, 2>, Camera<T>>>>& targetLandmarks);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/conformer/include/conformer/TeethAlignment.h` (Private)


#### class `TeethAlignment`  
`template <class T> class TeethAlignment`  
_L27-77_
- desc: Module to align teeth asset in the autorig using the reference rig as model Implemented for T=float and T=double
- L30 _public prototype_ `TeethAlignment();`
- L31 _public prototype_ `~TeethAlignment();`
- L32 _public prototype_ `TeethAlignment(TeethAlignment&& o);`
- L33 _public prototype_ `TeethAlignment(const TeethAlignment& o) = delete;`
- L34 _public prototype_ `TeethAlignment& operator=(TeethAlignment&& o);`
- L35 _public prototype_ `TeethAlignment& operator=(const TeethAlignment& o) = delete;`
- L37 _public prototype_ `void LoadRig(dna::Reader* referentRig, dna::Reader* targetRig);`
- L38 _public prototype_ `void SetRig(const std::shared_ptr<Rig<T>>& referentRig, const std::shared_ptr<Rig<T>>& targetRig);`
- L41 _public function_ `const Configuration& RegistrationConfiguration() const` — get/set the model registration settings (identity PCA model)
- L42 _public function_ `Configuration& RegistrationConfiguration()`
- L44 _public prototype_ `void SetControlsToEvaluate(const std::vector<Eigen::VectorX<T>>& controls);`
- L45 _public prototype_ `void SetControlsToEvaluate(const std::vector<std::map<std::string, float>>& controls);`
- L46 _public prototype_ `bool CheckControlsConfig(const std::string& configFilenameOrData);`
- L47 _public prototype_ `void LoadControlsToEvaluate(const std::string& InConfigurationFilenameOrData);`
- L49 _public prototype_ `const Eigen::Matrix<T, 3, -1> CurrentVertices() const;`
- L51 _public prototype_ `void SetInterfaceVertices(const VertexWeights<T>& mask);`
- L59 _public prototype_ `std::pair<T, Affine<T, 3, 3>> Align(const Affine<T, 3, 3>& inAffine, T inScale = T(1), int numIterations = 10);` — Run rigid registration. @param inAffine                        The (current) affine transformation of the source to target. @param inScale                         The (current) scale of the source to target. @param numIterations                   The number of iterations for rigid registration.
- L62 _private member_ `Configuration m_teethPlacementConfig = { std::string("Teeth Rig Placement Configuration"), {`
- L76 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/BlockJacobian.h` (Private)


#### class `BlockJacobian`  
`template <class T> class BlockJacobian`  
_L18-101_
- desc: Jacobian class using block layout with each block being either a sparse or dense matrix.
- L21 _public typedef_ `using DenseMatrixType = Eigen::Matrix<T, -1, -1, Eigen::RowMajor>;`
- L22 _public typedef_ `using SparseMatrixType = Eigen::SparseMatrix<T, Eigen::RowMajor>;`
- L25 _public prototype_ `BlockJacobian() = default;`
- L31 _public prototype_ `BlockJacobian(const std::shared_ptr<const SparseMatrixType>& sparseMatrix, int startCol);` — @brief Create a block jacobian with a sparse matrix of size [rows, cols]. The block jacobian then has size [rows, cols]. @p startCol should be the first non-zero column of the sparse matrix.
- L33 _public prototype_ `BlockJacobian(const std::shared_ptr<const DenseMatrixType>& denseMatrix, int startCol);` — Create a block jacobian with a dense matrix of size [rows, cols]. The block jacobian then has size [rows, startCol + cols]
- L34 _public prototype_ `~BlockJacobian() = default;`
- L35 _public prototype_ `BlockJacobian(BlockJacobian&&) = default;`
- L36 _public prototype_ `BlockJacobian(const BlockJacobian&) = default;`
- L37 _public prototype_ `BlockJacobian& operator=(BlockJacobian&&) = default;`
- L38 _public prototype_ `BlockJacobian& operator=(const BlockJacobian&) = default;`
- L41 _public prototype_ `[[nodiscard]] int Rows() const;` — @returns the number of rows of the Jacobian matrix
- L44 _public prototype_ `[[nodiscard]] int Cols() const;` — @returns the number of columns of the Jacobian matrix
- L47 _public prototype_ `[[nodiscard]] int StartCol() const;` — @returns the first non-zero column of the Jacobian matrix
- L50 _public prototype_ `[[nodiscard]] int NonZeros() const;` — @returns the total number of non zeros
- L53 _public prototype_ `[[nodiscard]] int NonZeros(int r) const;` — @returns the number of non zeros for row @p r
- L56 _public prototype_ `[[nodiscard]] std::shared_ptr<const SparseMatrixType> AsSparseMatrix() const;` — @returns the block jacobian as a sparse matrix of size [Rows(), Cols()]
- L59 _public prototype_ `void CopyToDenseMatrix(Eigen::Ref<DenseMatrixType> dense) const;` — Copies the block jacobian to dense matrix @p dense (of size [Rows(), Cols() - StartCol()])
- L61 _public prototype_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> Premultiply(const SparseMatrixType& sparseMat) const;`
- L63 _public prototype_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> Add(const BlockJacobian<T>& other) const;`
- L64 _public function_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> Add(const std::shared_ptr<const BlockJacobian<T>>& other) const`
- L66 _public prototype_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> Subtract(const BlockJacobian<T>& other) const;`
- L67 _public function_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> Subtract(const std::shared_ptr<const BlockJacobian<T>>& other) const`
- L69 _public prototype_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> Scale(T scale) const;`
- L71 _public prototype_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> RowGather(const Eigen::VectorX<int>& blockIndices, int blockSize) const;`
- L73 _public prototype_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> RowScatter(int outputSize, const Eigen::VectorX<int>& blockIndices, int blockSize) const;`
- L75 _public prototype_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> Repeat(int N) const;`
- L77 _public prototype_ `[[nodiscard]] Eigen::SparseVector<T> Row(int row) const;`
- L80 _public prototype_ `void AddJx(Eigen::Ref<Eigen::VectorX<T>> result, const Eigen::Ref<const Eigen::VectorX<T>>& x, const T scale) const;` — result += scale * Jacobian() * vec
- L83 _public prototype_ `void AddJtx(Eigen::Ref<Eigen::VectorX<T>> result, const Eigen::Ref<const Eigen::VectorX<T>>& x, const T scale) const;` — result += scale * Jacobian().transpose() * vec
- L86 _public prototype_ `void AddSparseJtJLower(std::vector<Eigen::Triplet<T>>& JtJ, const T scale) const;` — JtJ += scale * Jacobian().transpose() * Jacobian()
- L89 _public prototype_ `void AddDenseJtJLower(Eigen::Ref<Eigen::Matrix<T, -1, -1>> JtJ, const T scale, TaskThreadPool* threadPool) const;` — JtJ += scale * Jacobian().transpose() * Jacobian()
- L100 _private member_ `std::vector<Block> m_blocks;`

#### struct `BlockJacobian::Block`  
`struct Block`  
_L92-99_
- L94 _public member_ `std::shared_ptr<const SparseMatrixType> sparseMatrix;`
- L95 _public member_ `std::shared_ptr<const DenseMatrixType> denseMatrix;`
- L96 _public member_ `int startCol;`
- L97 _public member_ `int endCol;`
- L98 _public member_ `T scale;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/BoundedVectorVariable.h` (Private)


#### class `BoundedVectorVariable`  
`template <class T> class BoundedVectorVariable : public VectorVariable<T>`  
_L16-118_
- inherits: `VectorVariable<T>`
- desc: BoundedVectorVariable is a VectorVariable where each dimenion is bounded by some user defined bounds. Note that the Jacobian is correct in the sense that clamping due to the bounds is not taken into account i.e. the Jacobian is the same as VectorVariable.
- L19 _public function_ `BoundedVectorVariable(int size) : VectorVariable<T>(size), m_enforceBounds(true)`
- L25 _public function_ `BoundedVectorVariable(const Vector<T>& vector) : VectorVariable<T>(vector), m_enforceBounds(true)`
- L31 _public prototype_ `BoundedVectorVariable(BoundedVectorVariable&& other) = default;`
- L32 _public prototype_ `BoundedVectorVariable(const BoundedVectorVariable& other) = default;`
- L33 _public prototype_ `BoundedVectorVariable& operator=(BoundedVectorVariable&& other) = default;`
- L34 _public prototype_ `BoundedVectorVariable& operator=(const BoundedVectorVariable& other) = default;`
- L39 _public function_ `void EnforceBounds(bool enforce)` — Change whether the bounds are enforced or not. If the bounds are not enforced then the variable behaves the same as a VectorVariable.
- L50 _public function_ `bool BoundsAreEnforced() const` — @return True if the bounds are enforced when setting/updating the value
- L52 _public function_ `const Eigen::Matrix<T, 2, -1> Bounds() const`
- L54 _public function_ `void SetBounds(const Eigen::Matrix<T, 2, -1>& bounds)`
- L68 _public function_ `void SetBounds(int index, T minValue, T maxValue)`
- L82 _public function_ `void SetRegularizationScaling(const Eigen::VectorX<T>& regularizationScaling)`
- L91 _public function_ `const Eigen::VectorX<T>& RegularizationScaling() const`
- L95 _private function_ `virtual void ProjectToManifold(Vector<T>& value) override final` — Project the variables to the bounds
- L107 _private function_ `void SetUnbounded()` — Set the internal bounds to unbounded i.e. the range is to the minimum and maximum value
- L115 _private member_ `bool m_enforceBounds;`
- L116 _private member_ `Eigen::Matrix<T, 2, -1> m_bounds;`
- L117 _private member_ `Eigen::VectorX<T> m_regularizationScaling;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/Context.h` (Private)


#### class `Context`  
`template <class T> class Context`  
_L29-215_
- desc: The Context class provides the variable context when creating nonlinear optimization problems. In particular a Variable registers its local Jacobian with the Context and retrieves a modified Jacobian where the variable placement (the column indices) has been modified so that multiple Variables can coexist. The functions Value(), Set(), and Update() work similarly to the Variable implementation, but in this case these methods update all Variables that have been registered by the Context. Once a variable has registered a local jacobian it is expeced to remain the same until Next() is being called on the Context. This indicates that the variables have changed and therefore the Jacobians may also change. Note that Update() and Set() wil automatically call Next().
- L48 _public function_ `Context() : m_valueSize(0), m_updateSize(0), m_variableMap()`
- L50 _public function_ `void Clear()`
- L57 _public function_ `void Next()`
- L65 _public function_ `JacobianConstPtr<T> Map(Variable<T>* var, const SparseMatrixConstPtr<T>& localJacobian)`
- L110 _public function_ `void Set(const Vector<T>& x)`
- L129 _public function_ `Vector<T> Value()` — @returns the current variable vector defined by the mapping in this context
- L144 _public function_ `void Update(const Vector<T>& dx)`
- L162 _public function_ `std::vector<Variable<T>*> Variables()`
- L173 _public function_ `int ValueSize() const`
- L174 _public function_ `int UpdateSize() const`
- L177 _public function_ `const VariableInfo& GetVariableInfo(const Variable<T>* var) const` — @returns the column index and size of the variable in the jacobian
- L191 _private function_ `JacobianConstPtr<T> LocalToGlobalJacobian(const SparseMatrixConstPtr<T>& localJacobian, int columnIndex)`
- L211 _private member_ `int m_valueSize;`
- L212 _private member_ `int m_updateSize;`
- L214 _private member_ `std::map<Variable<T>*, VariableInfo> m_variableMap;`

#### struct `Context::VariableInfo`  
`struct VariableInfo`  
_L32-45_
- L35 _public member_ `SparseMatrixConstPtr<T> localJacobian;` — local jacobian of size rows x cols
- L38 _public member_ `JacobianConstPtr<T> globalJacobian;` — global jacobian which is the jacobian shifted by colOffset, total size rows x m_updateSize (when the global Jacobian was last constructed)
- L40 _public member_ `int rows;` — variable output dimension
- L41 _public member_ `int cols;` — variable update dimension
- L42 _public member_ `int rowOffset;` — offset into global value dimension
- L43 _public member_ `int colOffset;` — offset into global update dimension
- L44 _public member_ `int queries;` — how often the variable has been queries since the last call to Next()

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/Cost.h` (Private)


#### class `Cost`  
`template <class T> class Cost`  
_L17-108_
- desc: Cost
- L20 _public prototype_ `Cost() = default;`
- L21 _public prototype_ `~Cost() = default;`
- L22 _public prototype_ `Cost(Cost&&) = default;`
- L23 _public prototype_ `Cost(const Cost&) = delete;`
- L24 _public prototype_ `Cost& operator=(Cost&&) = default;`
- L25 _public prototype_ `Cost& operator=(const Cost&) = delete;`
- L35 _public function_ `void Add(DiffData<T>&& fx, T weight, const std::string& name = std::string(), bool average = false)` — @brief Add a least squares cost term: weight * || f(x) ||^2 @param fx       The f(x) value (with or without Jacobian). @param weight   The weight for the cost term. @param name     An optional name for the cost term. @param average  If True, then the cost term is calculating the average: weight * || f(x) ||^2 / size(f(x)).
- L51 _public function_ `void Add(Cost&& other, T weight = T(1), bool average = false)` — @brief Add another cost term to this cost term: weight * cost(x) @param other    The other cost term. @param weight   A weighting of the other cost term. @param average  If True, then the cost term is added as an average: weight * cost(x) / size(f(x))
- L63 _public prototype_ `Eigen::VectorX<T> Value() const;`
- L65 _public prototype_ `DiffData<T> CostToDiffData() const;`
- L67 _public function_ `int NumTerms() const`
- L69 _public function_ `int Size() const`
- L79 _public function_ `int Rows() const`
- L82 _public prototype_ `int Cols() const;` — @returns the number of columns of the Jacobian. @pre HasJacobian() is True.
- L85 _public prototype_ `void AddJx(Eigen::Ref<Eigen::VectorX<T>> result, const Eigen::Ref<const Eigen::VectorX<T>>& x, const T scale) const;` — result += scale * cost.Jacobian() * vec
- L88 _public prototype_ `void AddJtx(Eigen::Ref<Eigen::VectorX<T>> result, const Eigen::Ref<const Eigen::VectorX<T>>& x, const T scale) const;` — result += scale * cost.Jacobian().transpose() * vec
- L91 _public prototype_ `void AddDenseJtJLower(Eigen::Ref<Eigen::Matrix<T, -1, -1>> JtJ, const T scale, TaskThreadPool* threadPool) const;` — Calculates JtJ of the cost term and accumulates it into JtJ with additional scaling @p scale.
- L94 _public prototype_ `void AddSparseJtJLower(std::vector<Eigen::Triplet<T>>& JtJ, const T scale) const;` — Calculates sparse JtJ of the cost term and accumulates it as triplets with additional scaling @p scale.
- L97 _public prototype_ `bool HasJacobian() const;` — @returns True if all cost terms have a Jacobian.
- L107 _private member_ `std::vector<CostTerm> m_costTerms;`

#### struct `Cost::CostTerm`  
`struct CostTerm`  
_L100-105_
- L102 _public member_ `T weight;`
- L103 _public member_ `DiffData<T> diffdata;`
- L104 _public member_ `std::string name;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/DiffData.h` (Private)


#### class `DiffData`  
`template <class T> class DiffData`  
_L17-90_
- desc: Base data representation required for differentiable data with a vector of values and a Jacobian values: f(x) jacobian: df/dx
- L20 _public function_ `DiffData(Vector<T>&& value, JacobianConstPtr<T>&& jacobian) : m_value(std::move(value)), m_jacobian(std::move(jacobian))`
- L25 _public function_ `DiffData(Vector<T>&& value, const JacobianConstPtr<T>& jacobian) : m_value(std::move(value)), m_jacobian(jacobian)`
- L30 _public function_ `DiffData(Vector<T>&& value) : DiffData(std::move(value), JacobianConstPtr<T>())`
- L32 _public function_ `DiffData(const Vector<T>& value, const JacobianConstPtr<T>& jacobian) : m_value(value), m_jacobian(jacobian)`
- L37 _public function_ `DiffData(const Vector<T>& value) : DiffData(value, JacobianConstPtr<T>())`
- L40 _public function_ `DiffData(const T* values, int size) : DiffData(Eigen::Map<const Vector<T>>(values, size))` — constructor that explicitly copies the data
- L41 _public function_ `DiffData(const T* values, int size, const JacobianConstPtr<T>& jacobian) : DiffData(Eigen::Map<const Vector<T>>(values, size), jacobian)`
- L45 _public function_ `template <class S, int R, int C, typename DISCARD = typename std::enable_if<std::is_same<S, T>::value, void>::type> DiffData(const Eigen::Matrix<S, R, C>& mat) : DiffData((const T*)mat.data(), (int)mat.size())` — constructor that explicitly copies the data
- L49 _public function_ `template <class S, int R, int C, typename DISCARD = typename std::enable_if<std::is_same<S, T>::value, void>::type> DiffData(const Eigen::Matrix<S, R, C>& mat, const JacobianConstPtr<T>& jacobian) : DiffData((const T*)mat.data(), (int)mat.size(), jacobian)` — constructor that explicitly copies the data
- L51 _public prototype_ `DiffData(const DiffData&) = delete;`
- L52 _public prototype_ `DiffData& operator=(const DiffData&) = delete;`
- L53 _public prototype_ `DiffData(DiffData&&) = default;`
- L54 _public prototype_ `DiffData& operator=(DiffData&&) = default;`
- L56 _public function_ `void SanityCheck() const`
- L65 _public function_ `DiffData<T> Clone() const` — explicitly clone the diff data object as copy constructor is disabled (implementation may change in the future)
- L67 _public function_ `int Size() const`
- L68 _public function_ `const Vector<T>& Value() const`
- L70 _public function_ `bool HasJacobian() const`
- L71 _public function_ `const JacobianConstPtr<T>& JacobianPtr() const`
- L72 _public function_ `const TITAN_NAMESPACE::Jacobian<T>& Jacobian() const`
- L74 _public function_ `void SetJacobianPtr(const JacobianConstPtr<T>& jacobian)`
- L80 _public function_ `Vector<T>& MutableValue()` — Convenience function returning a reference to the value. @warning Use with care as any copy of DiffData will have its value modified as well.
- L85 _public function_ `JacobianConstPtr<T>& MutableJacobianPtr()` — Convenience function returning a reference to the jacobian ptr.
- L88 _private member_ `Vector<T> m_value;`
- L89 _private member_ `JacobianConstPtr<T> m_jacobian;`

#### Free symbols / members of external scopes

- L94 _function_ `template <class T> DiffData<T> operator*(const SparseMatrix<T>& A, const DiffData<T>& x)` — Sparse multiplication (linear map) of input @p x.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/DiffDataMatrix.h` (Private)


#### class `DiffDataMatrix`  
`template <class T, int R = -1, int C = -1> class DiffDataMatrix : public DiffData<T>`  
_L17-86_
- inherits: `DiffData<T>`
- desc: Differentiable data but with f(x) being a matrix and not a vector. @see DiffData
- L21 _public function_ `template <bool TMP = true> DiffDataMatrix(DiffData<T>&& o, typename std::enable_if<TMP && ((R >= 0) && (C >= 0))>::type* = 0) : DiffData<T>(std::move(o)) , m_rows(R) , m_cols(C)`
- L31 _public function_ `DiffDataMatrix(int rows, int cols, DiffData<T>&& o) : DiffData<T>(std::move(o)) , m_rows(rows) , m_cols(cols)`
- L42 _public function_ `template <bool TMP = true> DiffDataMatrix(const Eigen::Matrix<T, R, C>& mat, const JacobianConstPtr<T>& jacobian = nullptr, typename std::enable_if<TMP && ((R >= 0) && (C >= 0))>::type* = 0) : DiffDataMatrix(DiffData<T>(mat.data(), int(mat.size()), jacobian))`
- L48 _public function_ `template <bool TMP = true> DiffDataMatrix(const Eigen::Matrix<T, R, C>& mat, const JacobianConstPtr<T>& jacobian = nullptr, typename std::enable_if<TMP && !((R >= 0) && (C >= 0))>::type* = 0) : DiffDataMatrix(int(mat.rows()), int(mat.cols()), DiffData<T>(mat.data(), int(mat.size()), jacobian))`
- L53 _public function_ `int Rows() const`
- L54 _public function_ `int Cols() const`
- L57 _public function_ `Eigen::Map<const Eigen::Matrix<T, R, C>> Matrix() const` — Convenience function returning the value data as a matrix
- L66 _public function_ `Eigen::Map<Eigen::Matrix<T, R, C>> MutableMatrix()` — Convenience function returning the value data as a matrix. @warning Use with care as any copy of DiffDataMatrix will have its value modified as well.
- L70 _public function_ `template <int C2> DiffDataMatrix<T, R, C2> Multiply(const DiffDataMatrix<T, C, C2>& B) const` — Multiplies two matrices C = A * B
- L77 _public function_ `DiffData<T> Multiply(const DiffData<T>& b) const` — Multiplies a matrix and a vector c = A * b
- L84 _private member_ `int m_rows;`
- L85 _private member_ `int m_cols;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/DiffDataSparseMatrix.h` (Private)


#### class `DiffDataSparseMatrix`  
`template <class T, int R = -1, int C = -1> class DiffDataSparseMatrix : public DiffData<T>`  
_L20-134_
- inherits: `DiffData<T>`
- desc: Differentiable data but with f(x) being a sparse matrix and not a vector. Values of the underlying data vector are the dense nonzero entries and will always be in the sparse matrix's storage order. @see DiffData
- L27 _public function_ `template <bool TMP = true> DiffDataSparseMatrix(DiffData<T>&& o, const Eigen::VectorX<int>& outerIndices, const Eigen::VectorX<int>& innerIndices, typename std::enable_if<TMP && ((R >= 0) && (C >= 0))>::type* = 0) : DiffData<T>(std::move(o)) , m_rows(R) , m_cols(C) , m_outerIndices(outerIndices) , m_innerIndices(innerIndices)` — @warning Index arrays follow Eigen's CSC sparse format. len(outerIndices) = R + 1 and len(innerIndices) = o.Size()
- L43 _public function_ `DiffDataSparseMatrix(int rows, int cols, DiffData<T>&& o, const Eigen::VectorX<int>& outerIndices, const Eigen::VectorX<int>& innerIndices) : DiffData<T>(std::move(o)) , m_rows(rows) , m_cols(cols) , m_outerIndices(outerIndices) , m_innerIndices(innerIndices)`
- L62 _public function_ `template <bool TMP = true> DiffDataSparseMatrix(DiffData<T>&& o, const SparseMatrix<T>& mat, typename std::enable_if<TMP && ((R >= 0) && (C >= 0))>::type* = 0) : DiffDataSparseMatrix(std::move(o), Eigen::Map<const Eigen::VectorX<int>>(mat.outerIndexPtr(), mat.outerSize() + 1), Eigen::Map<const Eigen::VectorX<int>>(mat.innerIndexPtr(), mat.nonZeros()))` — @warning This constructor uses 'mat' ONLY for the sparsity structure for convenience. The nonzero data and jacobian comes from DiffData input
- L73 _public function_ `template <bool TMP = true> DiffDataSparseMatrix(DiffData<T>&& o, const SparseMatrix<T>& mat, typename std::enable_if<TMP && !((R >= 0) && (C >= 0))>::type* = 0) : DiffDataSparseMatrix(int(mat.rows()), int(mat.cols()), std::move(o), Eigen::Map<const Eigen::VectorX<int>>(mat.outerIndexPtr(), mat.outerSize() + 1), Eigen::Map<const Eigen::VectorX<int>>(mat.innerIndexPtr(), mat.nonZeros()))` — @warning This constructor uses 'mat' ONLY for the sparsity structure for convenience. The nonzero data and jacobian comes from DiffData input
- L83 _public function_ `template <bool TMP = true> DiffDataSparseMatrix(const SparseMatrix<T>& mat, const JacobianConstPtr<T>& jacobian = nullptr, typename std::enable_if<TMP && ((R >= 0) && (C >= 0))>::type* = 0) : DiffDataSparseMatrix(DiffData<T>(mat.valuePtr(), int(mat.nonZeros()), jacobian), Eigen::Map<const Eigen::VectorX<int>>(mat.outerIndexPtr(), mat.outerSize() + 1), Eigen::Map<const Eigen::VectorX<int>>(mat.innerIndexPtr(), mat.nonZeros()))`
- L91 _public function_ `template <bool TMP = true> DiffDataSparseMatrix(const SparseMatrix<T>& mat, const JacobianConstPtr<T>& jacobian = nullptr, typename std::enable_if<TMP && !((R >= 0) && (C >= 0))>::type* = 0) : DiffDataSparseMatrix(int(mat.rows()), int(mat.cols()), DiffData<T>(mat.valuePtr(),int(mat.nonZeros()), jacobian), Eigen::Map<const Eigen::VectorX<int>>(mat.outerIndexPtr(), mat.outerSize() + 1), Eigen::Map<const Eigen::VectorX<int>>(mat.innerIndexPtr(), mat.nonZeros()))`
- L101 _public function_ `int Rows() const`
- L102 _public function_ `int Cols() const`
- L104 _public function_ `const Eigen::VectorX<int>& OuterIndices() const`
- L105 _public function_ `const Eigen::VectorX<int>& InnerIndices() const`
- L108 _public function_ `Eigen::Map<const SparseMatrix<T>> Matrix() const` — Convenience function returning the value data as a sparse matrix
- L117 _public function_ `Eigen::Map<SparseMatrix<T>> MutableMatrix()` — Convenience function returning the value data as a sparse matrix. @warning Use with care as any copy of DiffDataSparseMatrix will have its value modified as well.
- L123 _public function_ `DiffData<T> Multiply(const DiffData<T>& b) const` — Multiplies a matrix and a vector c = A * b
- L130 _private member_ `int m_rows;`
- L131 _private member_ `int m_cols;`
- L132 _private member_ `Eigen::VectorX<int> m_outerIndices;`
- L133 _private member_ `Eigen::VectorX<int> m_innerIndices;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/DiffScalar.h` (Private)


#### class `DiffScalar`  
`template <typename T> class DiffScalar`  
_L21-37_
- desc: Base data representation representing a scalar and a Jacobian as a sparse vector value: f(x) jacobian: df/dx
- L24 _public function_ `DiffScalar(const T value, const Eigen::SparseVector<T>& jacobian) : m_value(value), m_jacobian(jacobian)`
- L27 _public function_ `explicit DiffScalar(const T value) : m_value(value), m_jacobian()`
- L29 _public function_ `const T Value() const`
- L31 _public function_ `bool HasJacobian() const`
- L32 _public function_ `const Eigen::SparseVector<T>& Jacobian() const`
- L35 _private member_ `T m_value;`
- L36 _private member_ `Eigen::SparseVector<T> m_jacobian;`

#### Free symbols / members of external scopes

- L41 _function_ `template <typename T> DiffScalar<T> ExtractScalar(const DiffData<T>& diffData, int index)` — Extract the @p index row from @p diffData.
- L53 _function_ `template <typename T> DiffData<T> AssembleDiffData(const std::vector<DiffScalar<T>>& diffScalars)` — Assemble all DiffScalar into on DiffData
- L100 _function_ `template <typename T> inline DiffScalar<T> operator+(const DiffScalar<T>& f)` — Unary +
- L106 _function_ `template <typename T> inline DiffScalar<T> operator-(const DiffScalar<T>& f)` — Unary -
- L111 _function_ `template <class T> Eigen::SparseVector<T> AutoResizeAdd(const Eigen::SparseVector<T>& a, const Eigen::SparseVector<T>& b)`
- L146 _function_ `template <typename T> inline DiffScalar<T> operator+(const DiffScalar<T>& f, const DiffScalar<T>& g)` — Binary +
- L152 _function_ `template <typename T> inline DiffScalar<T> operator+(const DiffScalar<T>& f, T s)` — Binary + with scalar f + s
- L158 _function_ `template <typename T> inline DiffScalar<T> operator+(T s, const DiffScalar<T>& f)` — Binary + with scalar s + f
- L164 _function_ `template <typename T> inline DiffScalar<T> operator-(const DiffScalar<T>& f, const DiffScalar<T>& g)` — Binary -
- L170 _function_ `template <typename T> inline DiffScalar<T> operator-(const DiffScalar<T>& f, T s)` — Binary - with scalar f - s
- L176 _function_ `template <typename T> inline DiffScalar<T> operator-(T s, const DiffScalar<T>& f)` — Binary - with scalar s - f
- L182 _function_ `template <typename T> inline DiffScalar<T> operator*(const DiffScalar<T>& f, const DiffScalar<T>& g)` — Binary *
- L188 _function_ `template <typename T> inline DiffScalar<T> operator*(const DiffScalar<T>& f, T s)` — Binary * with scalar f * s
- L194 _function_ `template <typename T> inline DiffScalar<T> operator*(T s, const DiffScalar<T>& f)` — Binary * with scalar s * f
- L200 _function_ `template <typename T> inline DiffScalar<T> operator/(const DiffScalar<T>& f, const DiffScalar<T>& g)` — Binary /
- L208 _function_ `template <typename T> inline DiffScalar<T> operator/(const DiffScalar<T>& f, T s)` — Binary / with scalar f / s
- L215 _function_ `template <typename T> inline DiffScalar<T> operator/(T s, const DiffScalar<T>& f)` — Binary / with scalar s / f
- L222 _function_ `template <typename T> inline DiffScalar<T> max(const DiffScalar<T> f, const DiffScalar<T>& g)` — maximum (the Jacobian is not well defined when both values are equal, so in this case we return the average Jacobian)
- L233 _function_ `template <typename T> inline DiffScalar<T> max(T s, const DiffScalar<T>& f)`
- L242 _function_ `template <typename T> inline DiffScalar<T> max(const DiffScalar<T>& f, T s)`
- L246 _function_ `template <typename T> inline DiffScalar<T> min(const DiffScalar<T> f, const DiffScalar<T>& g)` — minimum (the Jacobian is not well defined when both values are equal, so in this case we return the average Jacobian)
- L257 _function_ `template <typename T> inline DiffScalar<T> min(T s, const DiffScalar<T>& f)`
- L266 _function_ `template <typename T> inline DiffScalar<T> min(const DiffScalar<T>& f, T s)`
- L270 _function_ `template <typename T> inline DiffScalar<T> clamp(const DiffScalar<T>& f, T a, T b)` — clamp

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/Jacobian.h` (Private)


#### Free symbols / members of external scopes

- L14 _macro_ `#define USE_BLOCK_JACOBIAN 0`
- L18 _typedef_ `template <class T> using JacobianPtr = std::shared_ptr<BlockJacobian<T>>;`
- L21 _typedef_ `template <class T> using JacobianConstPtr = std::shared_ptr<const BlockJacobian<T>>;`
- L24 _typedef_ `template <class T> using Jacobian = BlockJacobian<T>;`
- L27 _typedef_ `template <class T> using DenseJacobian = BlockJacobian<T>;`
- L29 _typedef_ `template <class T> using SparseJacobian = BlockJacobian<T>;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/MatrixVariable.h` (Private)


#### class `MatrixVariable`  
`template <class T, int R = -1, int C = -1, typename DISCARD = typename std::enable_if<(R >= -1 && C >= -1), void>::type> class MatrixVariable : public VectorVariable<T>`  
_L21-84_
- inherits: `VectorVariable<T>`
- L24 _public member_ `static constexpr int ROWS = R;`
- L25 _public member_ `static constexpr int COLS = C;`
- L30 _public function_ `template <typename U = T> MatrixVariable(typename std::enable_if<std::is_same<U, T>::value && ((R >= 0) && (C >= 0))>::type* = 0) : MatrixVariable( R* C)` — constructor for fixed size matrices (calls the protected version further below with the correct updateDimension)
- L35 _public function_ `template <typename U = T> MatrixVariable(int rows, int cols, typename std::enable_if<std::is_same<U, T>::value && !((R >= 0) && (C >= 0))>::type* = 0) : MatrixVariable(rows, cols, rows* cols)` — constructor for dynamic size matrices (calls the protected version further below with the correct updateDimension)
- L38 _public function_ `int Rows() const`
- L39 _public function_ `int Cols() const`
- L42 _public function_ `void SetMatrix(const Eigen::Matrix<T, R, C>& M)` — Sets the matrix and projects it to the manifold.
- L48 _public function_ `Eigen::Map<const Eigen::Matrix<T, R, C>> Matrix() const` — Convenience function returning the variable data as a matrix.
- L54 _public function_ `DiffDataMatrix<T, R, C> EvaluateMatrix(Context<T>* context = nullptr)` — Convenience function returning a matrix with Jacobian (DiffDataMatrix) instead of just a vector
- L57 _public function_ `void SetIdentity()` — convenience function to set the identity matrix
- L60 _public function_ `void SetRandom()` — convenience function to set a random matrix
- L65 _protected function_ `template <typename U = T> MatrixVariable(int updateDimension, typename std::enable_if<std::is_same<U, T>::value && ((R >= 0) && (C >= 0))>::type* = 0) : VectorVariable<T>(R * C, updateDimension), dimInfo(R, C)` — Only subclasses can call this constructor to set up a matrix variable with an underlying manifold representation e.g. quaternion.
- L70 _protected function_ `template <typename U = T> MatrixVariable(int rows, int cols, int updateDimension, typename std::enable_if<std::is_same<U, T>::value && !((R >= 0) && (C >= 0))>::type* = 0) : VectorVariable<T>(rows * cols, updateDimension), dimInfo(rows, cols)` — Only subclasses can call this constructor to set up a matrix variable with an underlying manifold representation e.g. quaternion.
- L77 _protected function_ `void SetMatrix(const Eigen::Matrix<T, R, C>& M, bool projectToManifold)` — Sets the matrix and optionally projects it to the manifold. Note that the caller needs to ensure that the matrix is already on the manifold if projectToManifold=false.
- L80 _protected function_ `void SetMatrix(const Eigen::Map<const Eigen::Matrix<T, R, C>>& M, bool projectToManifold)` — @see SetMatrix above
- L83 _private member_ `internal::DimInfo<R, C> dimInfo;`

#### class `internal::DimInfo`  
`template <int R, int C> class DimInfo`  
_L92-98_
- desc: helper class to have fixed and dynamic size dimensions
- L95 _public function_ `DimInfo(int, int)`
- L96 _public function_ `static constexpr int Rows()`
- L97 _public function_ `static constexpr int Cols()`
- L104 _public function_ `DimInfo(int rows, int cols) : cols(cols)`
- L110 _public function_ `int Rows() const`
- L111 _public function_ `int Cols() const`
- L114 _private member_ `int cols;`
- L121 _public function_ `DimInfo(int rows, int cols) : rows(rows)`
- L131 _private member_ `int rows;`
- L138 _public function_ `DimInfo(int rows, int cols) : rows(rows), cols(cols)`

#### class `internal::DimInfo`  
`template <int R> class DimInfo<R, -1>`  
_L101-115_
- L95 _public function_ `DimInfo(int, int)`
- L96 _public function_ `static constexpr int Rows()`
- L97 _public function_ `static constexpr int Cols()`
- L104 _public function_ `DimInfo(int rows, int cols) : cols(cols)`
- L110 _public function_ `int Rows() const`
- L111 _public function_ `int Cols() const`
- L114 _private member_ `int cols;`
- L121 _public function_ `DimInfo(int rows, int cols) : rows(rows)`
- L131 _private member_ `int rows;`
- L138 _public function_ `DimInfo(int rows, int cols) : rows(rows), cols(cols)`

#### class `internal::DimInfo`  
`template <int C> class DimInfo<-1, C>`  
_L118-132_
- L95 _public function_ `DimInfo(int, int)`
- L96 _public function_ `static constexpr int Rows()`
- L97 _public function_ `static constexpr int Cols()`
- L104 _public function_ `DimInfo(int rows, int cols) : cols(cols)`
- L110 _public function_ `int Rows() const`
- L111 _public function_ `int Cols() const`
- L114 _private member_ `int cols;`
- L121 _public function_ `DimInfo(int rows, int cols) : rows(rows)`
- L131 _private member_ `int rows;`
- L138 _public function_ `DimInfo(int rows, int cols) : rows(rows), cols(cols)`

#### class `internal::DimInfo`  
`template <> class DimInfo<-1, -1>`  
_L135-149_
- L95 _public function_ `DimInfo(int, int)`
- L96 _public function_ `static constexpr int Rows()`
- L97 _public function_ `static constexpr int Cols()`
- L104 _public function_ `DimInfo(int rows, int cols) : cols(cols)`
- L110 _public function_ `int Rows() const`
- L111 _public function_ `int Cols() const`
- L114 _private member_ `int cols;`
- L121 _public function_ `DimInfo(int rows, int cols) : rows(rows)`
- L131 _private member_ `int rows;`
- L138 _public function_ `DimInfo(int rows, int cols) : rows(rows), cols(cols)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace internal`
- L87 _namespace_ `namespace internal`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/PatternCheck.h` (Private)


#### class `PatternCheck`  
`template <class T> class PatternCheck`  
_L14-50_
- desc: Helper class to check whether the sparsity pattern of a matrix has changed.
- L18 _public function_ `template <int Options> bool checkAndUpdatePattern(const Eigen::SparseMatrix<T, Options>& mat)`
- L45 _private member_ `Eigen::VectorXi jtjPattern;`
- L46 _private member_ `int options = 0;`
- L47 _private member_ `int64_t rows = 0;`
- L48 _private member_ `int64_t cols = 0;`
- L49 _private member_ `int64_t numNonZeros = 0;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/RobustLoss.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> void makeDiag(SparseMatrix<T>* sparseMat, const Vector<T>& diagValues)`
- L80 _function_ `template <class T> DiffData<T> smoothL1(const DiffData<T>& diffData, T beta, bool calcSqrt = true)` — @brief Compute a smooth L1 loss. A smooth L1 penalty variant is implemented by this function. It behaves like an L2 around zero and like an L1 far away from it. The option to return the square root, rather than just the loss value, facilitates the application in the context of Gauss-Newton optimization.
- L163 _function_ `template <class T> DiffData<T> generalizedCharbonnier(const DiffData<T>& diffData, T alpha, T eps, bool calcSqrt = true, bool zeroMin = true, T smallEps = T(1e-07))` — @brief Compute the generalized Charbonnier loss. This function establishes a generalized Charbonnier loss. It is a robust loss which can provide edge-preserving smoothing regularization for rig inverse problems. The square root of the loss can be optionally computed.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/Variable.h` (Private)


#### class `Variable`  
`template <class T> class Variable`  
_L13-189_
- L16 _public typedef_ `using value_type = T;`
- L19 _public function_ `Variable(const Vector<T>& vector) : m_outputDimension(int(vector.size())) , m_updateDimension(int(vector.size())) , m_constant(false) , m_value(vector) , m_cachedLocalJacobian()`
- L27 _public function_ `Variable(int outputDimension, int updateDimension) : m_outputDimension(outputDimension) , m_updateDimension(updateDimension) , m_constant(false) , m_value(Vector<T>::Zero(m_outputDimension)) , m_cachedLocalJacobian()`
- L35 _public function_ `Variable(int outputDimension) : Variable(outputDimension, outputDimension)`
- L39 _public prototype_ `virtual ~Variable() = default;`
- L42 _public prototype_ `Variable(Variable&&) = default;` — accept copy and move constructor as we are not duplicating the objects this way
- L43 _public prototype_ `Variable& operator=(Variable&&) = default;`
- L45 _public function_ `int OutputDimension() const`
- L46 _public function_ `int UpdateDimension() const`
- L47 _public function_ `int Size() const`
- L49 _public function_ `void MakeConstant()`
- L51 _public function_ `virtual void MakeMutable()`
- L53 _public function_ `bool IsConstant() const`
- L55 _public function_ `const Vector<T>& Value() const`
- L57 _public function_ `DiffData<T> Evaluate(Context<T>* context = nullptr)`
- L75 _public prototype_ `virtual void Set(const Vector<T>& value) = 0;` — Sets the variable \p value. The dimension of \p value needs to be OutputDimension(). A variable may have its internal valid manifold, and the function will project the value to the corresponding manifold. This means that calling Value() will return a value that may be different from the one passed to Set().
- L78 _public prototype_ `virtual void Update(const Vector<T>& dx) = 0;` — Updates the variable values by an offset dx. The dimension of dx needs to be UpdateDimension()
- L81 _public prototype_ `virtual bool RealJacobian() = 0;` — Method indicating with the Jacobian is the real Jacobian or some simplification (e.g. the Jacobian may not include the projection to the manifold).
- L84 _protected function_ `void SetValue(const VectorConstPtr<T>& valuePtr, bool projectToManifold)`
- L98 _protected function_ `void SetValue(const T* data, int64_t size, bool projectToManifold)`
- L110 _protected function_ `void InvalidateCachedJacobian()`
- L112 _protected function_ `Variable(const Variable& other) : m_outputDimension(other.m_outputDimension) , m_updateDimension(other.m_updateDimension) , m_constant(other.m_constant) , m_value(other.m_value) , m_cachedLocalJacobian()`
- L120 _protected function_ `Variable& operator=(const Variable& other)`
- L134 _private function_ `JacobianConstPtr<T> GlobalJacobianMatrixPtr(Context<T>* context)`
- L154 _private function_ `void SetValue(Vector<T>&& value)`
- L161 _private function_ `void SetValue(const Vector<T>& value)`
- L168 _private function_ `SparseMatrixConstPtr<T> LocalJacobianMatrixPtr()`
- L178 _private prototype_ `virtual SparseMatrixConstPtr<T> CalculateLocalJacobianMatrix() = 0;`
- L181 _private prototype_ `virtual void ProjectToManifold(Vector<T>& value) = 0;` — Projects the variable to the valid manifold of the underlying representation.
- L184 _private member_ `int m_outputDimension;`
- L185 _private member_ `int m_updateDimension;`
- L186 _private member_ `bool m_constant = false;`
- L187 _private member_ `Vector<T> m_value;`
- L188 _private member_ `SparseMatrixConstPtr<T> m_cachedLocalJacobian;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/VectorVariable.h` (Private)


#### class `VectorVariable`  
`template <class T> class VectorVariable : public Variable<T>`  
_L12-107_
- inherits: `Variable<T>`
- L15 _public function_ `VectorVariable(int size) : Variable<T>(size)`
- L16 _public function_ `VectorVariable(const Vector<T>& vector) : Variable<T>(vector)`
- L17 _public prototype_ `VectorVariable(VectorVariable&& other) = default;`
- L18 _public prototype_ `VectorVariable& operator=(VectorVariable&& other) = default;`
- L20 _public function_ `void SetZero()`
- L22 _public function_ `virtual void Set(const Vector<T>& value) override`
- L29 _public function_ `virtual void Update(const Vector<T>& dx) override`
- L35 _public function_ `virtual bool RealJacobian() override`
- L41 _public function_ `virtual void MakeMutable() override` — Specialization of MakeMutable() to also clear any constant indices
- L48 _public function_ `void MakeIndividualIndicesConstant(const std::vector<int>& constantIndices)` — Make invidual values of the variable constant
- L62 _public function_ `const std::vector<int>& ConstantIndices() const` — @return which indices are constant
- L66 _protected function_ `VectorVariable(int size, int updateDimension) : Variable<T>(size, updateDimension)` — Only subclasses can call this constructor to set up a vector variable with a different update dimension
- L68 _protected prototype_ `VectorVariable(const VectorVariable& other) = default;`
- L69 _protected prototype_ `VectorVariable& operator=(const VectorVariable&) = default;`
- L72 _private function_ `virtual SparseMatrixConstPtr<T> CalculateLocalJacobianMatrix() override`
- L103 _private function_ `virtual void ProjectToManifold(Vector<T>& ) override` — Nothing to do for a generic vector variable.
- L106 _private member_ `std::vector<int> m_constantIndices;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/VertexOptimization.h` (Private)


#### struct `VertexOptimization`  
`template <class T> struct VertexOptimization`  
_L60-402_
- desc: Class supporting vertex optimization problems
- L62 _public typedef_ `using ScalarType = T;`
- L64 _public member_ `int numVertices;`
- L67 _public member_ `Eigen::SparseMatrix<T, Eigen::RowMajor> baseLtL;` — Base Laplacian
- L69 _public member_ `Eigen::SparseMatrix<T, Eigen::RowMajor> tmpLtL;` — Temporary laplacian with removed "fixed" rows
- L71 _public member_ `Eigen::SparseMatrix<T, Eigen::RowMajor> LtL;` — Final laplacian with removed "fixed" rows and columns
- L73 _public member_ `std::vector<Eigen::Matrix<T, 3, 3>> diagonalBlocks;`
- L74 _public member_ `std::vector<bool> validDiagonal;`
- L75 _public member_ `std::vector<int> vertexMap;`
- L77 _public member_ `std::vector<Eigen::Matrix<T, 3, 3>> offDiagonalBlocks;`
- L78 _public member_ `std::vector<std::pair<int, int>> offDiagonalIndices;`
- L80 _public member_ `Eigen::VectorX<T> Jtb;`
- L82 _public member_ `std::shared_ptr<TITAN_NAMESPACE::TaskThreadPool> threadPool;`
- L84 _public function_ `int NumUnknowns() const`
- L85 _public function_ `int NumVariableVertices() const`
- L86 _public function_ `int NumVertices() const`
- L87 _public function_ `bool HasFixedVertices() const`
- L89 _public function_ `void SetTopology(const Mesh<T>& mesh)`
- L109 _public function_ `void Clear(const std::vector<int>& fixVertices = {})`
- L153 _public function_ `void Setup(const Eigen::Matrix<T, 3, -1>& vertexOffsets, T laplacianRegularization, T offsetRegularization, T updateRegularization)`
- L272 _public function_ `template <int ResidualSize, int NumConstraintVertices> void AddConstraints(const VertexConstraints<T, ResidualSize, NumConstraintVertices>& vertexConstraints)`
- L313 _public function_ `const Eigen::VectorX<T>& Rhs() const`
- L315 _public function_ `Eigen::VectorX<T> DiagonalPreconditioner() const`
- L350 _public function_ `int NumSegments() const`
- L352 _public function_ `void MatrixMultiply(Eigen::Ref<Eigen::VectorX<T>> out, int segmentId, Eigen::Ref<const Eigen::VectorX<T>> x) const`
- L378 _public function_ `Eigen::Matrix<T, 3, -1> Solve(int cgIterations) const`

#### Free symbols / members of external scopes

- L18 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`
- L32 _function_ `auto func = [&](int start, int end)` (scope `CARBON_NAMESPACE_BEGIN`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/AddFunction.h` (Private)


#### class `AddFunction`  
`template <class T> class AddFunction`  
_L16-49_
- desc: Function to add two value vectors: f(x) = a(x) + b(x)
- L19 _public function_ `AddFunction()`
- L21 _public function_ `DiffData<T> Evaluate(const DiffData<T>& a, const DiffData<T>& b) const`
- L43 _public function_ `template <int R, int C> DiffDataMatrix<T, R, C> Evaluate(const DiffDataMatrix<T, R, C>& a, const DiffDataMatrix<T, R, C>& b) const`

#### Free symbols / members of external scopes

- L52 _function_ `template <class T> DiffData<T> operator+(const DiffData<T>& a, const DiffData<T>& b)`
- L55 _function_ `template <class T, int R, int C> DiffDataMatrix<T, R, C> operator+(const DiffDataMatrix<T, R, C>& a, const DiffDataMatrix<T, R, C>& b)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/AxisConstraintFunction.h` (Private)


#### class `AxisConstraintFunction`  
`template <class T> class AxisConstraintFunction`  
_L12-48_
- L18 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, 3, -1>& v, const int axis, const int minIndex, const int maxIndex, const T targetLength, const T weight)` — Function to calculate a length constraint measured along an axis (i.e. max(v) - min(v) = l)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/BarycentricCoordinatesFunction.h` (Private)


#### class `BarycentricCoordinatesFunction`  
`template <class T, int R, int C = 3> class BarycentricCoordinatesFunction`  
_L18-104_
- desc: Function to add gather values from diff data
- L26 _public function_ `static DiffDataMatrix<T, R, -1> Evaluate(const DiffDataMatrix<T, R, -1>& vertices, const std::vector<BarycentricCoordinates<T, C>>& barycentricCoordinates)` — Evaluates the barycentric coordinates on the input vertices
- L66 _public function_ `static DiffDataMatrix<T, R, -1> Evaluate(const DiffDataMatrix<T, R, -1>& vertices, const std::vector<BarycentricCoordinatesExt<T, C>>& barycentricCoordinates)`

#### class `BarycentricCoordinatesFunctionExt`  
`template <class T> class BarycentricCoordinatesFunctionExt`  
_L111-156_
- desc: Function to add gather values from diff data
- L118 _public function_ `static DiffDataMatrix<T, 3, -1> Evaluate(const DiffDataMatrix<T, 2, -1>& barycentricUVNew, const Eigen::Matrix<T, 3, -1>& vertices, const std::vector<BarycentricCoordinatesExt<T, 3>>& barycentricCoordinatesOld)` — Evaluates the barycentric coordinates on the input vertices

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/BarycentricPointPointConstraintFunction.h` (Private)


#### class `BarycentricPointPointConstraintFunction`  
`template <class T, int C, typename DISCARD = typename std::enable_if<(C == 2 || C ==3), void>::type> class BarycentricPointPointConstraintFunction`  
_L13-67_
- L20 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const std::vector<BarycentricCoordinates<T, 3> >& barycentricCoordinates, const Eigen::Matrix<T, C, -1>& targets, const Vector<T>& weights, const T wPoint2Point)` — Function to calculate the an point-point constraint from vertices given as barycentric coordinates: residual(x) = sqrt(wPoint2Point) * w * (v(x) - target)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/ColwiseAddFunction.h` (Private)


#### class `ColwiseAddFunction`  
`template <class T> class ColwiseAddFunction`  
_L15-49_
- desc: Function to add a vector to a matrix colwise f(x).colwise() += t(x)
- L18 _public function_ `ColwiseAddFunction()`
- L21 _public function_ `template <int R, int C> DiffDataMatrix<T, R, C> colwiseAddFunction(const DiffDataMatrix<T, R, C>& matA, const DiffDataMatrix<T, R, 1>& vecB) const`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/DualQuaternionFunctions.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> SparseMatrix<T> DualQuaternionNormalizationJacobian(const DiffData<T>& dq)`
- L103 _function_ `template <class T> DiffData<T> DualQuaternionNormalizeDiff(const DiffData<T>& dq)`
- L140 _function_ `template <class T> DiffData<T> DualQuaternionVectorTransformDiff(const DiffData<T>& dq, const Eigen::Vector3<T>& v)`
- L166 _function_ `template <class T> DiffData<T> DualQuaternionVectorTransformDiff_2(const DiffData<T>& dq, const Eigen::Vector3<T>& v)`
- L224 _function_ `template <class T> DiffDataMatrix<T, 3, -1> DualQuaternionShapeTransformDiff(const DiffData<T>& dq, const Eigen::Matrix<T, 3, -1>& v)`
- L293 _function_ `template <class T> DiffData<T> DualQuaternionQuatConjugateDiff(const DiffData<T>& dq)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/GatherFunction.h` (Private)


#### class `GatherFunction`  
`template <class T> class GatherFunction`  
_L18-63_
- desc: Function to add gather values from diff data
- L21 _public function_ `GatherFunction()`
- L23 _public function_ `static DiffData<T> Gather(const DiffData<T>& a, const Eigen::VectorX<int>& blockIndices, int blockSize = 1)`
- L49 _public function_ `template <int R, int C1, int C2> static DiffDataMatrix<T, R, C1> GatherColumns(const DiffDataMatrix<T, R, C2>& a, const Eigen::VectorX<int>& colIndices)`
- L59 _public function_ `template <int R, int C1, int C2> static DiffDataMatrix<T, R, C1> GatherColumns(const DiffDataMatrix<T, R, C2>& a, const std::vector<int>& colIndices)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/LengthConstraintFunction.h` (Private)


#### class `LengthConstraintFunction`  
`template <class T, int C, typename DISCARD = typename std::enable_if<(C == 3), void>::type> class LengthConstraintFunction`  
_L13-141_
- L20 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const std::vector<std::vector<int>>& lines, const Vector<T>& target_lengths, const T wLength)` — Function to calculate a length constraint measuremed along a vertex line given by indices i_0...i_n: residual(x) = sqrt(wLength) * (sum(norm(i_{j+1} - i_{j})) - target_length)
- L85 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const std::vector<std::vector<BarycentricCoordinates<T, C>>>& lines, const Vector<T>& target_lengths, const T wLength)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/MatrixMultiplyFunction.h` (Private)


#### class `MatrixMultiplyFunction`  
`template <class T> class MatrixMultiplyFunction`  
_L17-162_
- desc: Function to multiply two matrices: f(x) = A(x) * B(x)
- L20 _public function_ `MatrixMultiplyFunction()`
- L23 _public function_ `template <int R1, int C1, int R2, int C2> static DiffDataMatrix<T, R1, C2> DenseMatrixMatrixMultiply(const DiffDataMatrix<T, R1, C1>& matA, const DiffDataMatrix<T, R2, C2>& matB)`
- L96 _public function_ `template <int R, int C> static DiffData<T> DenseMatrixVectorMultiply(const DiffDataMatrix<T, R, C>& mat, const DiffData<T>& vec)`
- L108 _public function_ `template <int R, int C> static DiffData<T> SparseMatrixVectorMultiply(const DiffDataSparseMatrix<T, R, C>& mat, const DiffData<T>& vec)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/PointPointConstraintFunction.h` (Private)


#### class `PointPointConstraintFunction`  
`template <class T, int C, typename DISCARD = typename std::enable_if<(C == 2 || C == 3), void>::type> class PointPointConstraintFunction`  
_L12-117_
- L19 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const Eigen::Matrix<T, C, -1>& targets, const Vector<T>& weights, const T wPoint2Point)` — Function to calculate the an point-point constraint: residual(x) = sqrt(wPoint2Point) * w * (v(x) - target)
- L69 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const Eigen::VectorXi& indices, const Eigen::Matrix<T, C, -1>& targets, const Vector<T>& weights, const T wPoint2Point)` — Function to calculate the an point-point constraint: residual(x) = sqrt(wPoint2Point) * w * (v(x) - target) Additional indices vector specifying on which vertices to evaluate the constraints. In this case the targets and weights need to have the samme number of points as the size of the indices vector.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/PointSurfaceConstraintFunction.h` (Private)


#### class `PointSurfaceConstraintFunction`  
`template <class T, int C> class PointSurfaceConstraintFunction`  
_L15-130_
- desc: Function to calculate the point surface constraint: residual(x) = sqrt(wNormal) * w * normal.dot(v(x) - target)
- L18 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const Eigen::Vector<T, C>* targets, const Eigen::Vector<T, C>* normals, const T* weights, const T wNormal)`
- L55 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const Eigen::Matrix<T, C, -1>& targets, const Eigen::Matrix<T, C, -1>& normals, const Vector<T>& weights, const T wNormal)`
- L74 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const int* indices, const Eigen::Vector<T, C>* targets, const Eigen::Vector<T, C>* normals, const T* weights, const int numConstraints, const T wNormal)`
- L111 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const Eigen::VectorXi& indices, const Eigen::Matrix<T, C, -1>& targets, const Eigen::Matrix<T, C, -1>& normals, const Vector<T>& weights, const T wNormal)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/ProjectionConstraintFunction.h` (Private)


#### class `ProjectionConstraintFunction`  
`template <class T> class ProjectionConstraintFunction`  
_L12-59_
- L18 _public function_ `static DiffData<T> Evaluate( const DiffData<T>& inputVector, const std::vector<Vector<T>>& projectionVectors, const Vector<T>& targetValues, const T weight)` — Function to a soft error based on the limits of the riglogic class

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/RigidityConstraintFunction.h` (Private)


#### Free symbols / members of external scopes

- L9 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T, int R, int C> DiffData<T> RigidityConstraintFunction(const DiffDataMatrix<T, R, C>& mat, T weight)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/ScaleFunction.h` (Private)


#### Free symbols / members of external scopes

- L10 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> DiffData<T> operator*(const DiffData<T>& a, const T scale)`
- L26 _function_ `template <class T> DiffData<T> operator*(const T scale, const DiffData<T>& a)`
- L29 _function_ `template <class T, int R, int C> DiffDataMatrix<T, R, C> operator*(const DiffDataMatrix<T, R, C>& a, const T scale)`
- L35 _function_ `template <class T, int R, int C> DiffDataMatrix<T, R, C> operator*(const T scale, const DiffDataMatrix<T, R, C>& a)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/ScatterFunction.h` (Private)


#### class `ScatterFunction`  
`template <class T> class ScatterFunction`  
_L16-54_
- desc: Function to add scatter values from diff data
- L19 _public function_ `ScatterFunction()`
- L21 _public function_ `static DiffData<T> Scatter(const DiffData<T>& a, int outputSize, const Eigen::VectorX<int>& blockIndices, int blockSize = 1)`
- L46 _public function_ `template <int R, int C1, int C2> static DiffDataMatrix<T, R, C1> ScatterColumns(const DiffDataMatrix<T, R, C2>& a, int outputCols, const Eigen::VectorX<int>& colIndices)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/SubtractFunction.h` (Private)


#### class `SubtractFunction`  
`template <class T> class SubtractFunction`  
_L16-50_
- desc: Function to subtract two value vectors: f(x) = a(x) - b(x)
- L19 _public function_ `SubtractFunction()`
- L21 _public function_ `DiffData<T> Evaluate(const DiffData<T>& a, const DiffData<T>& b) const`
- L44 _public function_ `template <int R, int C> DiffDataMatrix<T, R, C> Evaluate(const DiffDataMatrix<T, R, C>& a, const DiffDataMatrix<T, R, C>& b) const`

#### Free symbols / members of external scopes

- L54 _function_ `template <class T> DiffData<T> operator-(const DiffData<T>& a, const DiffData<T>& b)`
- L57 _function_ `template <class T, int R, int C> DiffDataMatrix<T, R, C> operator-(const DiffDataMatrix<T, R, C>& a, const DiffDataMatrix<T, R, C>& b)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/VertexConstraintsFunction.h` (Private)


#### Free symbols / members of external scopes

- L10 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T, int ResidualSize, int NumConstraintVertices> DiffData<T> ApplyVertexConstraints(const DiffDataMatrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& baseVertices, const VertexConstraints<T, ResidualSize, NumConstraintVertices>& vertexConstraints)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/functions/WeightedSumFunction.h` (Private)


#### class `WeightedSumFunction`  
`template <class T> class WeightedSumFunction`  
_L15-82_
- desc: Function to calculated the weighted sum of multiple vectors: f(x) = w1 f1(x) + w2 f2(x) + ...
- L18 _public function_ `WeightedSumFunction()`
- L20 _public function_ `DiffData<T> Evaluate(const std::vector<std::reference_wrapper<const DiffData<T>>>& inputs, const std::vector<T>& weights) const`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/Affine.h` (Private)


#### class `Affine`  
`template <class T, int R, int C, typename DISCARD = typename std::enable_if<(R > 0 && C > 0), void>::type> class Affine`  
_L30-126_
- desc: An affine transformation maps y = Mx + b where M is the linear transformation and b a translation https://en.wikipedia.org/wiki/Affine_transformation The matrix is stored as a homogenous matrix i.e. A =  |M b| |0 1| Hence, |y| = A * |x| |1|		 |1| Dimensions: R: row dimension of M and b C: column dimension of M Dimensions of the internal matrix: (R+1),(C+1). This is consitent with Eigen::Transform.
- L33 _public typedef_ `using ScalarType = T;`
- L34 _public typedef_ `using MatrixType = Eigen::Matrix<T, R + 1, C + 1>;`
- L37 _public function_ `Affine()`
- L42 _public function_ `Affine(const Eigen::Matrix<T, R + 1, C + 1>& mat) : m_affineMatrix(mat)`
- L45 _public function_ `Affine& operator=(const Eigen::Matrix<T, R + 1, C + 1>& mat)`
- L51 _public function_ `void SetLinear(const Eigen::Matrix<T, R, C>& linear)`
- L52 _public function_ `Eigen::Matrix<T, R, C> Linear() const`
- L54 _public function_ `void SetTranslation(const Eigen::Vector<T, R>& translation)`
- L55 _public function_ `Eigen::Vector<T, R> Translation() const`
- L57 _public function_ `const Eigen::Matrix<T, R + 1, C + 1>& Matrix() const`
- L59 _public function_ `void SetMatrix(const Eigen::Matrix<T, R + 1, C + 1>& mat)`
- L61 _public function_ `static Affine FromTranslation(const Eigen::Vector<T, R>& translation)`
- L68 _public function_ `static Affine FromLinear(const Eigen::Matrix<T, R, C>& linear)`
- L75 _public function_ `static inline Affine FromEulerXYZ(const Eigen::Vector3f& eulerXYZ, const Eigen::Vector3f& translation, bool radians = true)`
- L90 _public function_ `Eigen::Matrix<T, R, -1> Transform(const Eigen::Matrix<T, C, -1>& vertices) const`
- L102 _public function_ `Affine operator*(const Affine& aff) const`
- L107 _public function_ `void SetIdentity()`
- L109 _public function_ `Affine Inverse() const`
- L119 _public function_ `bool HasScaling(const T eps = T(1e-4)) const` — @returns True if the linear component of the affine transformation contains scale
- L125 _private member_ `Eigen::Matrix<T, R + 1, C + 1> m_affineMatrix;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/AffineVariable.h` (Private)


#### class `AffineVariable`  
`template <class LinearTransformationVariable> class AffineVariable`  
_L19-96_
- desc: An AffineTransformationVariable represents an affine transformation of a set of vertices.
- L22 _public typedef_ `typedef typename LinearTransformationVariable::value_type T;`
- L23 _public member_ `static constexpr int R = LinearTransformationVariable::ROWS;`
- L24 _public member_ `static constexpr int C = LinearTransformationVariable::COLS;`
- L27 _public function_ `AffineVariable()`
- L33 _public function_ `DiffDataAffine<T, R, C> EvaluateAffine(Context<T>* context)`
- L41 _public function_ `void SetAffine(const ::TITAN_NAMESPACE::Affine<T, R, C>& A)`
- L47 _public function_ `TITAN_NAMESPACE::Affine<T, R, C> Affine() const`
- L59 _public function_ `static ::TITAN_NAMESPACE::Affine<T, R, C> Random()` — Creates a valid affine transformation matrix. Valid means the linear part of the transformation is on the manifold of the underlying LinearTransformationVariable.
- L69 _public function_ `void MakeConstant(bool makeLinearConstant, bool makeTranslationConstant)`
- L90 _public function_ `LinearTransformationVariable& LinearVariable()`
- L91 _public function_ `MatrixVariable<T, R, 1>& TranslationVariable()`
- L94 _private member_ `LinearTransformationVariable m_linearTransformationVariable;`
- L95 _private member_ `MatrixVariable<T, R, 1> m_translationVariable;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/BarycentricCoordinates.h` (Private)


#### class `BarycentricCoordinates`  
`template <class T, int C = 3> class BarycentricCoordinates`  
_L20-111_
- desc: Representation of barycentric coordinates of a point in a triangle (C=3) or tetrahedron (C=4). Note: negative barycentric coordinates are supported and enable extrapolation outside of the tri/tet.
- L25 _public function_ `BarycentricCoordinates()`
- L31 _public function_ `BarycentricCoordinates(const Eigen::Vector<int, C>& indices, const Eigen::Vector<T, C>& weights) : m_indices(indices) , m_weights(weights)`
- L37 _public function_ `template <int R> Eigen::Vector<T, R> Evaluate(const Eigen::Ref<const Eigen::Matrix<T, R, -1>>& vertices) const`
- L47 _public function_ `int Index(int i) const`
- L52 _public function_ `T Weight(int i) const`
- L57 _public function_ `const Eigen::Vector<int, C>& Indices() const`
- L62 _public function_ `const Eigen::Vector<T, C>& Weights() const`
- L67 _public function_ `static BarycentricCoordinates SingleVertex(int vID)`
- L81 _public function_ `bool operator==(const BarycentricCoordinates& other) const`
- L87 _public prototype_ `static Eigen::Vector<T, C> ComputeBarycentricCoordinates(const Eigen::Vector<T, 3>& p, const Eigen::Vector<int, C>& indices, const Eigen::Matrix<T, 3, -1>& vertices);` — Computes barycentric coordinates of point 'p' w.r.t. a triangle/tet:
- L91 _public function_ `bool Nonnegative() const`
- L108 _private member_ `static constexpr int32_t m_version = 1;`
- L109 _private member_ `Eigen::Vector<int, C> m_indices;`
- L110 _private member_ `Eigen::Vector<T, C> m_weights;`

#### class `BarycentricCoordinatesExt`  
`template <class T, int C = 3> class BarycentricCoordinatesExt : public BarycentricCoordinates<T, C>`  
_L114-133_
- inherits: `BarycentricCoordinates<T,C>`
- L117 _public function_ `BarycentricCoordinatesExt() : BarycentricCoordinates<T, C>()`
- L122 _public function_ `BarycentricCoordinatesExt(const Eigen::Vector<int, C>& indices, const Eigen::Vector<T, C>& weights, const int triangle) : BarycentricCoordinates<T, C>(indices, weights)`
- L127 _public function_ `int Triangle() const`
- L132 _private member_ `int m_triangle;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace trio`
- L137 _function_ `template <typename T, int C = 3> bool ToBinaryFile(FILE* pFile, const BarycentricCoordinates<T, C>& bcs)`
- L147 _function_ `template <typename T, int C = 3> bool FromBinaryFile(FILE* pFile, BarycentricCoordinates<T, C>& bcs)`
- L165 _function_ `template <typename T, int C = 3> bool FromBinaryFile(trio::BoundedIOStream* stream, BarycentricCoordinates<T, C>& bcs)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/BarycentricEmbedding.h` (Private)


#### class `BarycentricEmbedding`  
`template <class T> class BarycentricEmbedding`  
_L22-68_
- desc: Class representing barycentric embedding of a list of points w.r.t. a tetmesh Note: the points do not have to be inside the tetmesh; if outside, negative barycentrics will be used Note 2: the current method to compute barycentric embedding is slow, hence serialization and deserialization is supported
- L25 _public prototype_ `BarycentricEmbedding() = default;`
- L26 _public prototype_ `BarycentricEmbedding(const BarycentricEmbedding& o) = default;`
- L27 _public prototype_ `BarycentricEmbedding& operator=(const BarycentricEmbedding& o) = default;`
- L29 _public function_ `const std::vector<BarycentricCoordinates<T, 4>>& GetBarycentricCoordinates() const`
- L35 _public prototype_ `void SetBarycentricEmbedding(const Eigen::Matrix<T, 3, -1>& points, const TetMesh<T>& tetMesh);` — Computes and sets embedding of 'points' in a 'tetMesh':
- L38 _public prototype_ `void Serialize(std::string fname) const;` — Saves m_barycentricCoordinates to a file:
- L39 _public prototype_ `void Serialize(JsonElement& json) const;`
- L42 _public prototype_ `void Deserialize(std::string fname);` — Sets m_barycentricCoordinates loaded from a file:
- L43 _public prototype_ `void Deserialize(const JsonElement& json);`
- L46 _public function_ `bool allAffine() const` — Checks if all barycentric coordinates are affine (i.e. sum to 1; they may be negative but always must sum to 1):
- L55 _public function_ `T minimalBarycentricCoordinate() const`
- L67 _private member_ `std::vector<BarycentricCoordinates<T, 4>> m_barycentricCoordinates;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/Camera.h` (Private)


#### class `Camera`  
`template <class T> class Camera`  
_L34-281_
- desc: A simple pinhole Camera with the following projection equation: @code px = K * [R|t] * Pw @code where K is a 3x3 triangular camera intrinsic matrix, R is a 3x3 3D rotation matrix, t is a 3x1 translation vector, Pw is a 3D point in world coordinates, and px is the projected point on the image plane (in pixels). K =  | fx  a  cx | |  0  fy cy | |  0  0  1  | Subclasses of the camera may also provide additional distortion parameters. Important: the camera model assumes the origin of the image is the corner of the top left pixel. so the center of the top-left pixel has coordinates (0.5, 0.5). This is different to opencv where the origin is at the center of the top-left pixel.
- L37 _public function_ `Camera() : m_intrinsics(Eigen::Matrix<T, 3, 3>::Identity()) , m_extrinsics() , m_width(0) , m_height(0)`
- L44 _public prototype_ `virtual ~Camera() = default;`
- L46 _public function_ `int Width() const`
- L47 _public function_ `void SetWidth(int width)`
- L49 _public function_ `int Height() const`
- L50 _public function_ `void SetHeight(int height)`
- L52 _public function_ `const std::string& Label() const`
- L53 _public function_ `void SetLabel(const std::string& label)`
- L55 _public function_ `const Eigen::Matrix<T, 3, 3>& Intrinsics() const`
- L56 _public function_ `void SetIntrinsics(const Eigen::Matrix<T, 3, 3>& intrinsics)`
- L65 _public function_ `const Affine<T, 3, 3>& Extrinsics() const`
- L66 _public function_ `void SetExtrinsics(const Affine<T, 3, 3>& extrinsics)`
- L69 _public function_ `const Eigen::Vector3<T> Origin() const` — @return the camera origin in world coordinates
- L72 _public function_ `Eigen::Vector2<T> Project(const Eigen::Vector3<T>& pt, bool withExtrinsics) const` — Projects a 3d point into the image
- L91 _public function_ `Eigen::Vector3<T> ToImagePlane(const Eigen::Vector2<T>& pix) const` — @return the image plane position for pixel @pix
- L99 _public function_ `Eigen::Vector3<T> Unproject(const Eigen::Vector2<T>& pix, T depth, bool withExtrinsics) const` — Unprojects a 2d point into 3D
- L113 _public function_ `void Scale(const T scale)` — Scales the camera parameters which is equivalent to scaling images associated with the camera.
- L147 _public function_ `Eigen::Matrix<T, 4, 4> RenderingProjectionMatrix(const T depthNear, const T depthFar) const` — Calculates a rendering projection matrix without extrinsics. x is mapped between [-1, 1] y is mapped between [-1, 1] z is mapped between [1, 0] where 1=depthNear, and 0=depthFar Calculation to pixel coordinates: [0, width], [0, height] x' = fx X/Z + skew Y/Z + cx y' = fy X/Z + cy Calculation to normalized coordinates: [-1, 1], [-1, 1]: x'' = 2 * x' / width - 1 y'' = 2 * y' / height - 1 Depth: depthNear maps to 1, depthFar maps to 0 a/depthNear + b = 1 a/depthFar + b = 0 => a = depthNear * depthFar / (depthFar - depthNear) => b = - depthNear / (depthFar - depthNear) Important notes: 1) depthNear maps to 1, depthFar maps to 0 (as opposed to the common depthNear=0 and depthFar=1) 2) -1 is the top of the image, not the bottom 3) the camera is looking in positive z direction
- L168 _public function_ `template <bool withExtrinsics> DiffDataMatrix<T, 2, -1> Project(const DiffDataMatrix<T, 3, -1>& pts) const` — Projects the input points into the image and also calculates the Jacobian px = (K(0,0) * p[0] + K(0, 1) * p[1] + K(0,2)) / p[2] py = (K(1,1) * p[1] + K(1,2)) / p[2]
- L220 _public function_ `DiffDataMatrix<T, 2, -1> Project(const DiffDataMatrix<T, 3, -1>& pts, bool withExtrinsics) const`
- L232 _public function_ `std::vector<T> serialize() const`
- L244 _public function_ `bool deserialize(const T* data)`
- L258 _public function_ `bool deserialize(const std::vector<T>& data)`
- L270 _private member_ `Eigen::Matrix<T, 3, 3> m_intrinsics;` — The intrinsics K
- L273 _private member_ `Affine<T, 3, 3> m_extrinsics;` — The camera extrinsics [R|t]
- L276 _private member_ `int m_width;` — The image dimensions
- L277 _private member_ `int m_height;`
- L280 _private member_ `std::string m_label;` — Label of the camera (optional)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/CameraHelpers.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> Camera<T> CameraFromVerticalFOV(const T angleInRadians, int width, int height)`
- L37 _function_ `template <class T> Camera<T> CameraFromHorizontalFOV(const T angleInRadians, int width, int height)` — Calculates the intrinsic camera parameters from a camera resolution and the horizontal field of view.
- L59 _function_ `template <class T> Affine<T, 3, 3> LookAt(const Eigen::Vector3<T>& eye, const Eigen::Vector3<T>& center, const Eigen::Vector3<T>& down)` — Calculates the extrinsics for a camera using a modified version of "lookat". In this version the caller needs to define the down vector which corresponds to the positive y direction in the camera which is pointing downwards in the camera image.
- L83 _function_ `template <class T> Mesh<T> CreateImagePlane(const Camera<T>& camera, const T distance, bool withExtrinsics)` — Creates an image backplane for \p camera at \p distance. @param [in] camera          The camera for which the image plane is created. @param [in] distance        The distance at which the image plane is created. @param [in] withExtrinsics  Whether to create the image plane in world coordinates (true) or in camera coordinates (false). @return A quad mesh with a single quad with the vertices and the texture coordinates so that a camera image can be assigned as texture.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/CatmullRom.h` (Private)


#### class `CatmullRom`  
`template <class T, int D> class CatmullRom`  
_L14-40_
- L17 _public prototype_ `CatmullRom() = default;`
- L18 _public function_ `CatmullRom(const Eigen::Matrix<T, D, -1>& controlPoints, int pointsPerSegment, bool closed)`
- L24 _public prototype_ `void Set(const Eigen::Matrix<T, D, -1>& controlPoints, int pointsPerSegment, bool closed);` — Sets the control points of the catmull rom curve.
- L26 _public function_ `const Polyline<T, D>& ControlPoints() const`
- L27 _public function_ `const Polyline<T, D>& SampledPoints() const`
- L30 _public prototype_ `Eigen::Vector<T, -1> LinearResampling(const Eigen::Vector<T, -1>& values) const;` — Method to resample values at the sample points linearly based on the values at the control points.
- L32 _public function_ `bool IsClosed() const`
- L33 _public function_ `int PointsPerSegment() const`
- L36 _private member_ `Polyline<T, D> m_controlPoints;`
- L37 _private member_ `int m_pointsPerSegment = 1;`
- L38 _private member_ `bool m_closed;`
- L39 _private member_ `Polyline<T, D> m_sampledPoints;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/ClosestPointData.h` (Private)


#### struct `ClosestPointData`  
`template <class T> struct ClosestPointData`  
_L17-35_
- desc: A way of storing data to represent the closest point on a mesh in terms of BaryCentric coordinates for a triangle, and delta Vector from the triangle in terms of its local reference frame (which allows the mesh to be rotated and still obtain a sensible offset)
- L19 _public function_ `ClosestPointData()`
- L21 _public member_ `static constexpr int32_t version = 1;`
- L22 _public member_ `BarycentricCoordinates<T> bcs;`
- L23 _public member_ `T weight;`
- L24 _public member_ `Eigen::Vector<T, 3> deltaInLocalCoordSystem;` — x = delta.dot(Tangent vector), y = delta.dot(Bitangent vector), z = delta.dot(normal vector)
- L27 _public prototype_ `Eigen::Vector<T, 3> CalculateTransformedPoint(const Eigen::Matrix<T, 3, -1>& inTransformedMeshVertices, T normalOffset = 0) const;` — calculate the transformed point in the local coordinate frame; also allows an offset along the normal if we want to offset the results
- L29 _public prototype_ `ClosestPointData(const Eigen::Matrix<T, 3, -1>& inMeshVertices, const Eigen::Vector<T, 3>& inPoint, const BarycentricCoordinates<T>& inBcs, const T& inWeight);`
- L33 _private prototype_ `void CalculateLocalCoordSystem(const Eigen::Matrix<T, 3, -1>& inMeshVertices, Eigen::Vector<T, 3>& outTangent, Eigen::Vector<T, 3>& outBitangent, Eigen::Vector<T, 3>& outNormal) const;`

#### Free symbols / members of external scopes

- L38 _prototype_ `template <class T> bool ToBinaryFile(FILE* pFile, const ClosestPointData<T>& closestPointData);`
- L41 _prototype_ `template <class T> bool FromBinaryFile(FILE* pFile, ClosestPointData<T>& closestPointData);`
- L44 _prototype_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, ClosestPointData<T>& closestPointData);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/DepthmapData.h` (Private)


#### struct `DepthmapData`  
`template <class T> struct DepthmapData`  
_L13-22_
- L15 _public member_ `Camera<T> camera;`
- L16 _public member_ `Eigen::Matrix<T, 4, -1> depthAndNormals;`
- L18 _public prototype_ `void Create(const Camera<T>& cam);`
- L19 _public prototype_ `void Create(const Camera<T>& cam, const T* depthPtr, TaskThreadPool* taskThreadPool = nullptr);`
- L21 _public prototype_ `void ApplyScale(T scale, TaskThreadPool* taskThreadPool = nullptr);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/DiffDataAffine.h` (Private)


#### class `DiffDataAffine`  
`template <class T, int R, int C, typename DISCARD = typename std::enable_if<(R > 0 && C > 0), void>::type> class DiffDataAffine`  
_L17-126_
- desc: Convenience function for differentiable affine transformation Ax + b
- L20 _public typedef_ `using ScalarType = T;`
- L21 _public typedef_ `using MatrixType = Eigen::Matrix<T, R + 1, C + 1>;`
- L24 _public function_ `DiffDataAffine() : m_A(Eigen::Matrix<T, R, C>::Identity()) , m_b(Eigen::Vector<T, R>::Zero())`
- L29 _public function_ `DiffDataAffine(const Eigen::Matrix<T, R + 1, C + 1>& mat) : m_A(mat.template topLeftCorner<R, C>()) , m_b(mat.template topRightCorner<R, 1>())`
- L34 _public function_ `DiffDataAffine(const DiffDataMatrix<T, R, C>& A, const DiffDataMatrix<T, R, 1>& b) : m_A(A) , m_b(b)`
- L39 _public function_ `DiffDataAffine(DiffDataMatrix<T, R, C>&& A, DiffDataMatrix<T, R, 1>&& b) : m_A(std::move(A)) , m_b(std::move(b))`
- L44 _public function_ `DiffDataAffine(const Affine<T, R, C>& aff) : DiffDataAffine(aff.Matrix())`
- L48 _public prototype_ `DiffDataAffine(const DiffDataAffine& aff) = delete;`
- L49 _public prototype_ `DiffDataAffine(DiffDataAffine&& aff) = default;`
- L50 _public prototype_ `DiffDataAffine& operator=(const DiffDataAffine& aff) = delete;`
- L51 _public prototype_ `DiffDataAffine& operator=(DiffDataAffine&& aff) = default;`
- L54 _public function_ `DiffDataAffine Clone() const` — explicitly clone the diff data affine object as copy constructor is disabled (implementation may change in the future)
- L58 _public function_ `DiffDataAffine Multiply(const DiffDataAffine& other) const` — Multiplies two affine transformations A1 (A2 x + b2) + b1 = (A1 A2) x + (A1 b2 + b2)
- L69 _public function_ `DiffDataAffine operator*(const DiffDataAffine& aff) const`
- L74 _public function_ `static DiffDataAffine FromTranslation(const DiffDataMatrix<T, R, 1>& translation)`
- L83 _public function_ `DiffDataMatrix<T, R, -1> Transform(const DiffDataMatrix<T, C, -1>& matX) const` — Applies the affine transformation to some input data y = Ax + b
- L94 _public function_ `Eigen::Matrix<T, R + 1, C + 1> Matrix() const` — Returns the full "homogeneous" matrix
- L104 _public function_ `TITAN_NAMESPACE::Affine<T, R, C> Affine() const`
- L113 _public function_ `bool HasJacobian() const`
- L118 _public function_ `const DiffDataMatrix<T, R, C>& Linear() const`
- L119 _public function_ `DiffDataMatrix<T, R, C>& Linear()`
- L120 _public function_ `const DiffDataMatrix<T, R, 1>& Translation() const`
- L121 _public function_ `DiffDataMatrix<T, R, 1>& Translation()`
- L124 _private member_ `DiffDataMatrix<T, R, C> m_A;`
- L125 _private member_ `DiffDataMatrix<T, R, 1> m_b;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/DualQuaternion.h` (Private)


#### Free symbols / members of external scopes

- L9 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) #if !defined(NDEBUG) || (defined(CARBON_ENABLE_ASSERTS) && CARBON_ENABLE_ASSERTS) #define ASSERT_VALID_DQ_RESULT(dq, result) \ Eigen::Vector2<T> norm = DualQuaternionNorm(dq);`
- L12 _macro_ `#define ASSERT_VALID_DQ_RESULT(dq, result) \`
- L44 _function_ `template <class T> Vector<T> IdentityDq()`
- L53 _function_ `template <class T> Eigen::Matrix4<T> MatrixOfQuaternionPreMultiplication(const Eigen::Vector4<T>& q)`
- L64 _function_ `template <class T> Eigen::Matrix4<T> MatrixOfQuaternionPostMultiplication(const Eigen::Vector4<T>& q)`
- L75 _function_ `template <class T> Eigen::Matrix<T, 8, 8> MatrixOfDualQuaternionPreMultiplication(const Vector<T>& dq)`
- L91 _function_ `template <class T> Eigen::Matrix<T, 8, 8> MatrixOfDualQuaternionPostMultiplication(const Vector<T>& dq)`
- L107 _function_ `template <class T, bool NORMALIZE> Eigen::Matrix3<T> DualQuaternionToRotationMatrix(const Vector<T>& dq)`
- L123 _function_ `template <class T, bool NORMALIZE> Eigen::Vector3<T> DualQuaternionToTranslationVector(const Vector<T>& dq)`
- L145 _function_ `template <class T> Vector<T> RotationMatrixTranslationVectorToDualQuaternion(const Eigen::Matrix3<T>& R, const Eigen::Vector3<T>& t)`
- L157 _function_ `template <class T> Vector<T> TranslationVectorToDualQuaternion(const Eigen::Vector3<T>& t)`
- L164 _function_ `template <class T> Eigen::Vector2<T> DualQuaternionNorm(const Vector<T>& dq)`
- L185 _function_ `template <class T> Vector<T> DualQuaternionNormalize(const Vector<T>& dq)` — Calculates the normalized dual quaternion
- L217 _function_ `template <class T, bool NORMALIZE> Vector<T> DualQuaternionQuatConjugate(const Vector<T>& dq)`
- L233 _function_ `template <class T, bool NORMALIZE> Vector<T> DualQuaternionDualQuatConjugate(const Vector<T>& dq)`
- L249 _function_ `template <class T, bool NORMALIZE> Vector<T> DualQuaternionMultiplication(const Vector<T>& dq1, const Vector<T>& dq2)`
- L281 _function_ `template <class T, bool NORMALIZE> Eigen::Vector3<T> DualQuaternionVectorTransform(const Eigen::Vector3<T>& p, const Vector<T>& dq)`
- L305 _function_ `template <class T> Eigen::Matrix<T, 3, -1> DualQuaternionShapeTransform(const Eigen::Matrix<T, 3, -1>& shape, const Vector<T>& dq)`
- L319 _function_ `template <class T> Eigen::Matrix<T, 4, 4> DualQuaternionToAffineMatrix(const Vector<T>& dq)`
- L332 _function_ `template <class T> Vector<T> AffineMatrixToDualQuaternion(const Eigen::Matrix<T, 4, 4>& m)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/DualQuaternionVariable.h` (Private)


#### class `DualQuaternionVariable`  
`template <class T> class DualQuaternionVariable : public VectorVariable<T>`  
_L21-67_
- inherits: `VectorVariable<T>`
- L24 _public function_ `DualQuaternionVariable() : VectorVariable<T>( 8)`
- L28 _public function_ `DualQuaternionVariable(const Vector<T>& value) : VectorVariable<T>( 8)`
- L35 _public function_ `virtual bool RealJacobian() override`
- L40 _public function_ `void SetIdentity()`
- L48 _private function_ `virtual SparseMatrixConstPtr<T> CalculateLocalJacobianMatrix() override`
- L63 _private function_ `virtual void ProjectToManifold(Vector<T>& value) override`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/EulerAngles.h` (Private)


#### Free symbols / members of external scopes

- L9 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> Eigen::Matrix<T, 3, 3> EulerX(const T angleInRadians)`
- L30 _function_ `template <class T> Eigen::Matrix<T, 3, 3> EulerY(const T angleInRadians)`
- L48 _function_ `template <class T> Eigen::Matrix<T, 3, 3> EulerZ(const T angleInRadians)`
- L67 _function_ `template <typename T> Eigen::Vector3<T> RotationMatrixToEulerXYZ(const Eigen::Matrix<T, 3, 3>& R)` — Calculates the Euler angles given the rotation matrix assuming the XYZ order of Maya i.e. in post-multiply this is EulerZ() * EulerY() * EulerX()
- L71 _function_ `auto wrapToPi = [](T angle)` (scope `RotationMatrixToEulerXYZ`)
- L96 _function_ `template <class T> Eigen::Matrix<T, 3, 3> EulerXYZ(const T rx, const T ry, const T rz)` — Calculates the Euler rotation using the XYZ order of Maya i.e. in post-multiply this is EulerZ() * EulerY() * EulerX() Expects the angles in radians.
- L123 _function_ `template <class T> Eigen::Matrix<T, 3, 3> EulerXYZ(const Eigen::Vector3<T>& angles)`
- L131 _function_ `template <class T> SparseMatrix<T> EulerXYZJacobian(const T rx, const T ry, const T rz)` — Calculates the Jacobian of EulerXYZ
- L185 _function_ `template <class T> Eigen::Matrix<T, 9, 3, Eigen::RowMajor> EulerXYZJacobianDense(const T rx, const T ry, const T rz)` — Calculates the Jacobian of EulerXYZ
- L241 _function_ `template <class T> Eigen::Matrix<T, 3, 3> EulerXYZAndScale(const T rx, const T ry, const T rz, const T sx, const T sy, const T sz)`
- L269 _function_ `template <class T> SparseMatrix<T> EulerXYZAndScaleJacobian(const T rx, const T ry, const T rz, const T sx, const T sy, const T sz)` — Calculates the Jacobian of EulerXYZAndScale
- L335 _function_ `template <class T> Eigen::Matrix<T, 9, 6, Eigen::RowMajor> EulerXYZAndScaleJacobianDense(const T rx, const T ry, const T rz, const T sx, const T sy, const T sz)` — Calculates the Jacobian of EulerXYZAndScale

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/GeometryHelpers.h` (Private)


#### Free symbols / members of external scopes

- L12 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::geoutils) std::vector<std::vector<int>> VertexAdjacency(const Eigen::Matrix<int, 3, -1>& Triangles);`
- L30 _prototype_ `void TriangleAdjacency( const Eigen::Matrix<int, 3, -1>& triangles, Eigen::Matrix<int, 3, -1>& adjacency, Eigen::Matrix<int, 3, -1>& outerTriangleEdges);` — Find the neighboring triangles of each mesh triangle. @param triangles is the input topology @param adjacency (result) contains the neighbors ordered ordered according to the i-th traingle edges. Edge 0: {triangles(0, i), triangles(1, i)}; edge 1: {triangles(1, i), triangles(2, i)}; edge 2: {triangles(2, i), triangles(0, i)}; @param outerTriangleEdges (result) contains for each i-th triangle the id of the edge of the j-th triangle that is shared by (i, j).
- L47 _prototype_ `void QuadAdjacency( const Eigen::Matrix<int, 4, -1>& quads, Eigen::Matrix<int, 4, -1>& adjacency, Eigen::Matrix<int, 4, -1>& outerQuadEdges);` — Find the neighboring quads of each mesh triangle. @param quads is the input topology @param adjacency (result) contains the neighbors ordered ordered according to the i-th traingle edges. Edge 0: {quads(0, i), quads(1, i)}; edge 1: {quads(1, i), quads(2, i)}; edge 2: {quads(2, i), quads(3, i)}; edge 3: {quads(3, i), quads(0, i)}; @param outerTriangleEdges (result) contains for each i-th quad the id of the edge of the j-th quad that is shared by (i, j).
- L55 _prototype_ `std::vector<std::vector<int>> VertexAdjacency(const Eigen::Matrix<int, 4, -1>& Tets);` — Calculate vertex adjacency for a given tet mesh
- L61 _function_ `template <class T> static TITAN_NAMESPACE::Mesh<T> CreatePyramid(const Eigen::Matrix<T, 3, 1>& origin, const Eigen::Matrix<T, 3, 1>& node, T baseDistance)` — Creates a pyramid using origin as a center of the base and node for the apex
- L104 _function_ `template <class T> static TITAN_NAMESPACE::Mesh<T> CreateCylinder( const T radius, const T height, const int numSamplesCircle, const int numSamplesHeight)` — Creates a cylinder by stacking circles from the plane x = 0 y = 0
- L192 _function_ `template <class T> static TITAN_NAMESPACE::Mesh<T> CreateTorus( const Eigen::Vector<T, 2>& radiuses, const Eigen::Vector2i& numSamplesPhiTheta, bool triangulate = false)` — Creates torus by stacking circles around the origin.
- L332 _function_ `template <class T> static TITAN_NAMESPACE::Mesh<T> CreateSphere(int subdivLevels)` — Creates a sphere by subdividing a diamond shape base shape and projecting the subdivision verices to the unit sphere.
- L354 _function_ `auto makeEdge = [](int vID0, int vID1)` (scope `CreateSphere`)
- L409 _function_ `template <class T> static TITAN_NAMESPACE::Mesh<T> CreateGrid(const T extentX, const T extentY, const int subdivX, const int subdivY)` — Creates a grid with a given size and number of subdivisions
- L453 _function_ `template <class T> static const Mesh<T> ConstructMeshFromDepthStream(const Camera<T>& camera, const T* depthPtr, T distThresh)`
- L515 _function_ `template <class T> static const Mesh<T> ConstructMeshFromMeshStream(const int numTriangles, const int* trianglesPtr, const int numVertices, const T* verticesPtr)`
- L564 _function_ `template <class T> static const Eigen::VectorX<T> CalculateMaskBasedOnMeshTopology(const Mesh<T>& inputMesh, bool &bInvalidMeshTopology, T edgeRatioThreshold = T(10))`
- L623 _function_ `template <class T> static Eigen::VectorX<T> ComputeTemplateCoverageMask( const Mesh<T>& templateMesh, const Mesh<T>& scanMesh, const Eigen::VectorX<T>& scanQualityMask, T maxCoverageDistance)`
- L666 _function_ `template <class T> Eigen::VectorX<T> FitEllipse(const Eigen::Matrix2X<T>& points2d)`
- L695 _function_ `template <class T, int D> static Eigen::Matrix<T, D, -1> CombinePoints(const std::vector<Eigen::Matrix<T, D, -1>>& vertices)`
- L715 _function_ `template <class T, int D> static Eigen::Matrix<T, D, -1> CombineRows(const std::vector<Eigen::Matrix<T, D, -1>>& vertices)`
- L735 _function_ `template <class T> static Eigen::VectorX<T> CombinePoints(const std::vector<Eigen::VectorX<T>>& input)`
- L755 _function_ `template <class T> static std::pair<std::vector<int>, Mesh<T>> CombineMeshes(const std::vector<Mesh<T>>& meshes)`
- L782 _function_ `template <class T, int D = 3> static std::vector<Eigen::Matrix<T, D, -1>> SplitVertices(const Eigen::Matrix<T, D, -1>& combined, const std::vector<int>& offsets)`
- L795 _function_ `template <class T> static TITAN_NAMESPACE::Mesh<T> CreateTrapezoidalPrism(T start, T end, T startSize, T endSize)`
- L851 _function_ `template <class T> static std::vector<std::vector<int>> ExtractBoundaryLoops(const Mesh<T>& mesh)` — Extract ordered boundary loops from a mesh. Boundary edges belong to exactly one triangle. Each loop is a closed sequence of vertex indices ordered along the boundary.
- L928 _function_ `template <class T> static std::vector<std::pair<int, int>> FindAlignedBoundaryLoops( const Mesh<T>& meshA, const Mesh<T>& meshB, T tolerance = T(0.01), bool allowDiffCount = false)` — Find pairs of boundary loops from two meshes that are spatially aligned. Returns pairs of (loopIndexA, loopIndexB). @param tolerance      Maximum per-vertex distance to consider aligned (default 0.01) @param allowDiffCount If false (default), only match loops with identical vertex counts
- L986 _function_ `template <class T> static Mesh<T> MergeMeshesAlongBoundary( const Mesh<T>& meshA, const Mesh<T>& meshB, const std::vector<int>& loopA, const std::vector<int>& loopB)` — Merge two meshes along aligned boundary loops by welding matching vertices. loopA and loopB are ordered vertex index sequences from meshA and meshB respectively. Matched boundary vertices from meshB are remapped to use meshA's vertices. @returns Combined mesh with welded boundary

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/HalfEdgeMesh.h` (Private)


#### struct `HalfEdgeMesh`  
`template <class T> struct HalfEdgeMesh`  
_L19-50_
- desc: Half edge mesh class representing meshes with polygonal faces
- L32 _public member_ `Eigen::Matrix<T, 3, -1> vertices;`
- L35 _public member_ `std::vector<HalfEdge> halfEdges;` — list of half edges
- L38 _public member_ `std::vector<int> vertexEdge;` — map from vertex id to one of the half-edges originating at that vertex
- L40 _public member_ `std::vector<int> faces;` — map from face index to one of the half-edges part of that face
- L43 _public prototype_ `HalfEdgeMesh() = default;`
- L44 _public prototype_ `HalfEdgeMesh(const HalfEdgeMesh& o) = default;`
- L45 _public prototype_ `HalfEdgeMesh& operator=(const HalfEdgeMesh& o) = default;`
- L47 _public prototype_ `HalfEdgeMesh(const Mesh<T>& m);`
- L49 _public prototype_ `std::vector<int> GetTopologicalSymmetry(const int referenceEdge) const;`

#### struct `HalfEdgeMesh::HalfEdge`  
`struct HalfEdge`  
_L22-30_
- desc: main half edge data structure
- L24 _public member_ `int v0;` — source vertex index for half-edge
- L25 _public member_ `int v1;` — target vertex index for half-edge
- L26 _public member_ `int next;` — next edge in loop
- L27 _public member_ `int prev;` — previous edge in loop
- L28 _public member_ `int dual;` — dual edge in neighboring face, might be -1 if edge
- L29 _public member_ `int face;` — face index for halfedge

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/ImageHelpers.h` (Private)


#### Free symbols / members of external scopes

- L8 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> T srgb2linear(T srgb)`
- L25 _function_ `template <class T> T linear2srgb(T linear)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/ImageView.h` (Private)


#### enum `PixelDepth`  
`enum class PixelDepth`  
_L10-15_
- L12 _public enumerator_ `UINT8`
- L13 _public enumerator_ `UINT16`
- L14 _public enumerator_ `FLOAT`

#### class `ImageView`  
`class ImageView`  
_L28-53_
- L31 _public function_ `ImageView(void* imageData, int width, int height, PixelFormat pixelFormat, PixelDepth pixelDepth) : m_imageData(imageData) , m_width(width) , m_height(height) , m_pixelFormat(pixelFormat) , m_pixelDepth(pixelDepth)`
- L39 _public function_ `void* Data()`
- L40 _public function_ `const void* Data() const`
- L41 _public function_ `int Width() const`
- L42 _public function_ `int Height() const`
- L43 _public function_ `PixelFormat GetPixelFormat() const`
- L44 _public function_ `PixelDepth GetPixelDepth() const`
- L45 _public function_ `int GetSizeInBytes() const`
- L48 _private member_ `void* m_imageData;`
- L49 _private member_ `int m_width;`
- L50 _private member_ `int m_height;`
- L51 _private member_ `PixelFormat m_pixelFormat;`
- L52 _private member_ `PixelDepth m_pixelDepth;`

#### class `ConstImageView`  
`class ConstImageView`  
_L55-87_
- L58 _public function_ `ConstImageView(const void* imageData, int width, int height, PixelFormat pixelFormat, PixelDepth pixelDepth) : m_imageData(imageData) , m_width(width) , m_height(height) , m_pixelFormat(pixelFormat) , m_pixelDepth(pixelDepth)`
- L66 _public function_ `ConstImageView(const ImageView& other) : m_imageData(other.Data()) , m_width(other.Width()) , m_height(other.Height()) , m_pixelFormat(other.GetPixelFormat()) , m_pixelDepth(other.GetPixelDepth())`
- L74 _public function_ `const void* Data() const`
- L75 _public function_ `int Width() const`
- L76 _public function_ `int Height() const`
- L77 _public function_ `PixelFormat GetPixelFormat() const`
- L78 _public function_ `PixelDepth GetPixelDepth() const`
- L79 _public function_ `int GetSizeInBytes() const`
- L82 _private member_ `const void* m_imageData;`
- L83 _private member_ `int m_width;`
- L84 _private member_ `int m_height;`
- L85 _private member_ `PixelFormat m_pixelFormat;`
- L86 _private member_ `PixelDepth m_pixelDepth;`

#### Free symbols / members of external scopes

- L17 _function_ `inline int BytesForPixelDepth(PixelDepth pixelDepth)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/IncrementalPCA.h` (Private)


#### enum `DataOrder`  
`enum class DataOrder`  
_L20-24_
- L22 _public enumerator_ `RowsAreExamples`
- L23 _public enumerator_ `ColsAreExamples`

#### class `IncrementalPCA`  
`template <typename T> class IncrementalPCA`  
_L34-391_
- desc: @brief Class for training a PCA model incrementally (after an initial training batch) @details Uses the method of Ross et al in: "Incremental Learning for Robust Visual Tracking" https://www.cs.toronto.edu/~dross/ivt/RossLimLinYang_ijcv.pdf @tparam T must be a floating point type such as float, double, etc.
- L63 _public function_ `void AddTrainingData(const Eigen::Matrix<T, -1, -1>& dataMatrix, T forgetFactor, int maxModes, T maxVariance, DataOrder order)` — @brief Add a set of training examples to the model @details If this block is the first set of examples a normal PCA is computed, otherwise the existing model is updated. In the second case, the data must have the same number of dimensions as the original data used to train the model. @param dataMatrix A matrix of training data, where each row or column is a training example according to the order flag @param forgetFactor Typically set to 1.0 this controls how much weight to give to the existing model versus the new data. A forgot factor of 0.0 gives all the weight to the new data essentially completely forgetting all the previous training. @param maxModes The maximum number of modes to retain in the model. @param maxVariance The maximum variance to retain. @param order Flag to specify whether the data is column-wise or row-wise @pre dataMatrix.cols() > 0 @pre dataMatrix.rows() > 0 @pre 0<= forgetFactor <= 1 @pre if IsTrained() then (order==DataOrder::ColsAreExamples && dataMatrix.rows()==NumVariables()) || (order==DataOrder::RowsreExamples && dataMatrix.cols()==NumVariables())
- L86 _public function_ `bool IsTrained()` — @brief Check if the model is trained
- L92 _public function_ `void Reset()` — @brief Reset the model so that the next set of data passed to it is treated as the first set of data.
- L108 _public function_ `Eigen::Matrix<T, -1, -1> Parameterize(const Eigen::Matrix<T, -1, -1>& dataMatrix, DataOrder order)` — @brief Given a set of data examples, return their parameterizations @param dataMatrix A matrix of training data, where each row or column is a training example according to the order flag @param order Flag to specify whether the data is column-wise or row-wise @return A matrix of parameters where each column corresponds to each column of the input data. @pre (IsTrained() && (order==DataOrder::ColsAreExamples && dataMatrix.rows()==NumVariables()) || (order==DataOrder::RowsAreExamples && dataMatrix.cols()==NumVariables()))
- L135 _public function_ `Eigen::Matrix<T, -1, -1> Reconstruct(const Eigen::Matrix<T, -1, -1>& parameterMatrix, DataOrder order)` — @brief Given a set of parameterizations, return their reconstructions @param parameterMatrix A matrix of parameters, where each row or column is an example according to the order flag. @param order Flag to specify whether the data is column-wise or row-wise @return A matrix of reconstructions where each column corresponds to each column of the input data. @pre (IsTrained() && (order==DataOrder::ColsAreExamples && parameterMatrix.rows()==NumParams()) || (order==DataOrder::RowsAreExamples && parameterMatrix.cols()==NumParams()))
- L163 _public function_ `Eigen::Matrix<T, -1, -1> BestFit(const Eigen::Matrix<T, -1, -1>& dataMatrix, DataOrder order)` — @brief Given a set of data, parameterize, the reconstruct their approximations @param dataMatrix A matrix of training data, where each row or column is a training example according to the order flag @param order Flag to specify whether the data is column-wise or row-wise @return A matrix of reconstructions where each column corresponds to each column of the input data. @pre (IsTrained() && (order==DataOrder::ColsAreExamples && dataMatrix.rows()==NumVariables()) || (order==DataOrder::RowsAreExamples && dataMatrix.cols()==NumVariables()))
- L176 _public function_ `int NumModes()` — @brief Return the number of modes in the model. @return The number of modes.
- L182 _public function_ `int NumVariables()` — @brief Return the number of variables in the data the model encodes. @return The number of variables.
- L188 _public function_ `const Eigen::Vector<T, -1>& StandardDeviations()` — @brief Return a vector giving the standard deviations of the modes. @return Vector of standard deviations.
- L194 _public function_ `const Eigen::Matrix<T, -1, -1>& U()` — @brief Return the matrix of modes. @return The modes.
- L200 _public function_ `const Eigen::VectorX<T>& Mean()` — @brief Return the mean. @return The mean.
- L203 _private member_ `bool m_isTrained = false;`
- L204 _private member_ `Eigen::VectorX<T> m_mean;`
- L205 _private member_ `Eigen::Matrix<T, -1, -1> m_U;`
- L206 _private member_ `Eigen::Vector<T, -1> m_singularValues;`
- L207 _private member_ `Eigen::Vector<T, -1> m_stds;`
- L208 _private member_ `T m_n = 0.f;`
- L211 _private function_ `void Train(const Eigen::Matrix<T, -1, -1>& dataMatrix, int maxModes, T maxVariance, DataOrder order)`
- L280 _private function_ `void Update(const Eigen::Matrix<T, -1, -1>& dataMatrix, T forgetFactor, int maxModes, T maxVariance, DataOrder order)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/Interpolation.h` (Private)


#### enum `InterpolationMethod`  
`enum class InterpolationMethod`  
_L12-17_
- L14 _public enumerator_ `NEAREST`
- L15 _public enumerator_ `LINEAR`
- L16 _public enumerator_ `CUBIC`

#### Free symbols / members of external scopes

- L21 _function_ `template <typename TYPE> inline TYPE nearestInterpolate(const TYPE* texture, float x, float y, int maxX, int maxY)` — nearest texture interpolation
- L32 _function_ `template <typename TYPE> inline TYPE bilinearInterpolate(const TYPE* texture, float x, float y, int maxX, int maxY)` — bilinear texture interpolation
- L52 _function_ `template <typename TYPE> inline TYPE cubicValue(float t, TYPE fm, TYPE f0, TYPE f1, TYPE f2)` — cubic interpolation based on implementation in OpenCV
- L64 _function_ `template <typename TYPE> inline TYPE cubicInterpolate(const TYPE* texture, float x, float y, int maxX, int maxY)` — cubic texture interpolation

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/Jacobians.h` (Private)


#### Free symbols / members of external scopes

- L8 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T, int R, int K, int C> SparseMatrix<T> JacobianOfPremultipliedMatrix(const Eigen::Matrix<T, R, K>& M)`
- L40 _function_ `template <class T, int R, int K, int C> Eigen::Matrix<T, R* C, K* C, Eigen::RowMajor> JacobianOfPremultipliedMatrixDense(const Eigen::Matrix<T, R, K>& M)`
- L65 _function_ `template <class T, int R, int K, int C> SparseMatrix<T> JacobianOfPostmultipliedMatrix(const Eigen::Matrix<T, K, C>& M)` — Calculates the Jacobian of the product A = X M A: R x C X: R x K M: K x C @returns dA/dX
- L108 _function_ `template <class T> SparseMatrix<T> JacobianOfCrossProductMatrix(const T SCALE = T(1.0))` — Calculates the Jacobian of the cross product matrix L with an optional scaling: SL = s * |  0  -z   y  | |  z   0  -x  | | -y   x   0  | and X = [x y z]^T @returns dSL/dX dSL/dx = | 0  0  0 | | 0  0 -s | | 0  s  0 | dSL/dy = | 0  0  s | | 0  0  0 | |-s  0  0 | dSL/dz = | 0 -s  0 | | s  0  0 | | 0  0  0 |
- L206 _function_ `template <class T, int C> SparseMatrix<T> JacobianOfCrossProductMatrixPostMultipliedByMatrix(Eigen::Map<const Eigen::Matrix<T, 3, C>> M, const T SCALE = T(1.0))` — Calculates the Jacobian of the product A = L M with L being the cross product matrix and optional scaling: L = |  0  -z   y  | |  z   0  -x  | | -y   x   0  | and X = [x y z]^T @returns dA/dX dL/dx = | 0  0  0 | | 0  0 -1 | | 0  1  0 | dL/dy = | 0  0  1 | | 0  0  0 | |-1  0  0 | dL/dz = | 0 -1  0 | | 1  0  0 | | 0  0  0 | M =  | row(0) | | row(1) | | row(2) | dA/dx =  |  0		| | -2 row(2)	| |  2 row(1)	| dA/dy =  |  2 row(2) | |  0        | | -2 row(0) | dA/dz =  | -2 row(1) | |  2 row(0) | |  0        |
- L296 _function_ `template <class T, int R> SparseMatrix<T> JacobianOfCrossProductMatrixPreMultipliedByMatrix(Eigen::Map<const Eigen::Matrix<T, R, 3>> M, const T SCALE = T(1.0))` — Calculates the Jacobian of the product A = M L with L being the cross product matrix and optional scaling: L = |  0  -z   y  | |  z   0  -x  | | -y   x   0  | and X = [x y z]^T @returns dA/dX dL/dx = | 0  0  0 | | 0  0 -1 | | 0  1  0 | dL/dy = | 0  0  1 | | 0  0  0 | |-1  0  0 | dL/dz = | 0 -1  0 | | 1  0  0 | | 0  0  0 | M =          |    col(0)     col(1)      col(2) | dA/dx =  |  0          2 col(2)   -2 col(1) | dA/dy =  | -2 col(2)   0           2 col(0) | dA/dz =  |  2 col(1)  -2col(0)     0        |

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/LodGeneration.h` (Private)


#### class `LodGenerationConfiguration`  
`template <class T> class LodGenerationConfiguration`  
_L26-62_
- desc: Representation of a configuration representing how Lod Generation is performed
- L45 _public prototype_ `LodGenerationConfiguration() = default;`
- L48 _public prototype_ `bool Load(const std::string& filenameOrData);` — Load data from either file or the data directly.
- L50 _public function_ `const std::map<std::string, LodGenerationData>& RigPartLodGenerationData() const`
- L58 _private prototype_ `bool LoadJson(const std::string& jsonString, const std::string& baseDir, bool isFileBased);`
- L61 _private member_ `std::map<std::string, LodGenerationData> m_rigPartLodGenerationData;` — a map of part name to lod generation data for each rig part

#### struct `LodGenerationConfiguration::LodData`  
`struct LodData`  
_L29-36_
- L31 _public member_ `std::string meshName;`
- L32 _public member_ `std::string driverMesh;`
- L33 _public member_ `std::shared_ptr<const Mesh<T>> mesh;`
- L34 _public member_ `SnapConfig<T> snapConfig;`
- L35 _public prototype_ `bool ReadJson(const JsonElement& element, const std::string& baseDir, bool isFileBased = true);`

#### struct `LodGenerationConfiguration::LodGenerationData`  
`struct LodGenerationData`  
_L38-43_
- L40 _public member_ `std::vector<LodData> lodData;`
- L41 _public member_ `WrapDeformerParams<T> params;`
- L42 _public prototype_ `bool ReadJson(const JsonElement& element, const std::string& baseDir, bool isFileBased = true);`

#### class `LodGeneration`  
`template <class T> class LodGeneration`  
_L68-105_
- desc: Representation of a class for performing Lod generation using wrap deformers
- L71 _public prototype_ `LodGeneration();`
- L74 _public prototype_ `void SetThreadPool(const std::shared_ptr<TITAN_NAMESPACE::TaskThreadPool>& taskThreadPool);` — Set a threadpool for parallelization of lod generation tasks (if not set, the default global threadpool will be used)
- L77 _public prototype_ `bool Init(const LodGenerationConfiguration<T>& config);` — initialize the lod generation object from a config
- L80 _public prototype_ `bool Apply(std::map<std::string, Eigen::Matrix<T, 3, -1>>& lod0MeshVertices, std::map<std::string, Eigen::Matrix<T, 3, -1>>& higherLodMeshVertices, bool bAllowMissingMeshes = false) const;` — apply lod generation to a map of mesh name to vertices, once the object has been initialized, and return the results for the higher lods as a map of mesh name to vertices
- L83 _public prototype_ `void GetDriverMeshClosestPointBarycentricCoordinates(std::map<std::string, std::vector<BarycentricCoordinates<T>>>& driverMeshClosestPointBarycentricCoordinates) const;` — once the object has been initialized, for each higher lod mesh, get the barycentric coordinates for the closest vertices on the driver mesh, returning the results as a map of mesh names to vector of barycemtric coordinates
- L86 _public prototype_ `bool LoadModelBinary(const std::string& lodGenerationModelFile);` — load from a binary lod generation model filename
- L89 _public prototype_ `bool SaveModelBinary(const std::string& lodGenerationModelFile) const;` — save to a binary lod generation model filename
- L91 _public function_ `const std::vector<std::string>& Lod0MeshNames() const`
- L92 _public prototype_ `std::vector<std::string> HigherLodMeshNames() const;`
- L93 _public prototype_ `int LodForMesh(const std::string& meshName) const;`
- L96 _private member_ `static constexpr int32_t m_version = 2;`
- L97 _private member_ `std::vector<std::string> m_baseMeshes;`
- L98 _private member_ `std::map<std::string, std::string> m_driverMeshNames;`
- L99 _private member_ `std::map<std::string, WrapDeformer<T>> m_wrapDeformers;`
- L100 _private member_ `std::map<std::string, SnapConfig<T>> m_snapConfigs;`
- L101 _private member_ `std::map<std::string, int> m_meshLods;`
- L102 _private member_ `std::map<std::string, std::shared_ptr<const Mesh<T>>> m_allMeshes;`
- L104 _private member_ `std::shared_ptr<TITAN_NAMESPACE::TaskThreadPool> m_taskThreadPool;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/Mesh.h` (Private)


#### enum `VertexNormalComputationType`  
`enum class VertexNormalComputationType`  
_L36-41_
- L38 _public enumerator_ `AreaWeighted`
- L39 _public enumerator_ `VoronoiAreaWeighted`
- L40 _public enumerator_ `AngleWeighted`

#### class `Mesh`  
`template <class T> class Mesh`  
_L52-243_
- desc: Mesh class representing quad and triangle meshes. Important note: Texture coordinates are stored with the origin being at the top left corner. Any import/export of meshes, e.g. when writing OBJs, needs to take this into account and flip the y coordinate accordingly. The reason to store texture coordinates with the top left corner is so that this is consistent with image, windows, and normalized coordinates (Vulkan).
- L55 _public prototype_ `Mesh() = default;`
- L56 _public prototype_ `Mesh(const Mesh& o) = default;`
- L57 _public prototype_ `Mesh& operator=(const Mesh& o) = default;`
- L59 _public function_ `int NumVertices() const`
- L60 _public function_ `int NumTriangles() const`
- L61 _public function_ `int NumQuads() const`
- L63 _public function_ `const Eigen::Matrix<T, 3, -1>& Vertices() const`
- L65 _public function_ `void SetVertices(Eigen::Matrix<T, 3, -1>&& vertices)` — Sets the vertices and clears the normals
- L66 _public function_ `void SetVertices(const Eigen::Matrix<T, 3, -1>& vertices)`
- L68 _public function_ `const Eigen::Matrix<int, 3, -1>& Triangles() const`
- L70 _public function_ `void SetTriangles(Eigen::Matrix<int, 3, -1>&& tris)` — Sets the triangles and clears the normals
- L71 _public function_ `void SetTriangles(const Eigen::Matrix<int, 3, -1>& tris)`
- L73 _public function_ `const Eigen::Matrix<int, 4, -1>& Quads() const`
- L75 _public function_ `void SetQuads(Eigen::Matrix<int, 4, -1>&& quads)` — Sets the quads and clears the normals
- L76 _public function_ `void SetQuads(const Eigen::Matrix<int, 4, -1>& quads)`
- L84 _public prototype_ `void SetTopology(const Eigen::VectorXi& topology, const Eigen::VectorXi& vIDs);` — Set the topology using the polygon format (as used in Maya). @pre There should not be any prior tris and quads assigned to the mesh. @param polygons      The number of vertices per polygons (only 3 for tris and 4 for quads are supported) @param vIDs          The vertex IDs for the \p polygons (concatenated)
- L90 _public prototype_ `bool Validate(bool checkVertexUsage) const;` — Validates that all indices are correct (in bound) @checkVertexUsage  Checks whether all vertices are being used
- L100 _public prototype_ `std::vector<std::pair<int, bool>> Triangulate(TriangulationMethod triangulationMethod = TriangulationMethod::Quality, TaskThreadPool* taskThreadPool = nullptr);`
- L103 _public prototype_ `Eigen::Vector<T, -1> TriangleAreas() const;` — Calculates the triangle areas. (only works for pure triangle meshes)
- L109 _public prototype_ `Eigen::Vector<T, -1> VertexAreas() const;` — Calculates the vertex areas (only works for pure triangle meshes) using the mixed area term as described in Fig. 4 Meyer et al, "Discrete Differential-Geometry Operators for Triangulated 2-Manifolds")
- L116 _public prototype_ `Eigen::Matrix<T, 3, -1> VertexMeanCurvatureNormals() const;` — Calculates the vertex mean curvature normal based on Meyer et al, "Discrete Differential-Geometry Operators for Triangulated 2-Manifolds"). The mean curvature value is half the magnitude.
- L119 _public function_ `bool HasVertexNormals() const` — @returns True if the mesh has vertex normals
- L122 _public function_ `void ClearVertexNormals()` — Clears the current normals
- L129 _public prototype_ `const Eigen::Matrix<T, 3, -1>& CalculateVertexNormals(bool recompute = false, VertexNormalComputationType vertexNormalComputationType = VertexNormalComputationType::VoronoiAreaWeighted, bool stableNormalize = true, TaskThreadPool* taskThreadPool = nullptr);` — Calculates the vertex normals weighted by the mixed area term as described in Fig. 4 Meyer et al, "Discrete Differential-Geometry Operators for Triangulated 2-Manifolds") @param recompute  If false then the normals are only calculated if they are not already there, if True then calculation is forced
- L139 _public prototype_ `void CalculateVertexNormals(const Eigen::Matrix<T, 3, -1>& vertices, Eigen::Matrix<T, 3, -1>& normals, VertexNormalComputationType vertexNormalComputationType, bool stableNormalize, TaskThreadPool* taskThreadPool = nullptr) const;` — Calculates the vertex normals using the topology of this mesh and the vertices of @p vertices. Stores the result in @p normals. @param[in] accurate  If True, it uses the mixed area term (see above), otherwise it uses a faster version by weighing using the triangle area.
- L150 _public prototype_ `void CalculateVertexNormalsRef(Eigen::Ref<const Eigen::Matrix<T, 3, -1>> vertices, Eigen::Ref<Eigen::Matrix<T, 3, -1>> normals, VertexNormalComputationType vertexNormalComputationType, bool stableNormalize, TaskThreadPool* taskThreadPool = nullptr) const;` — Calculates the vertex normals using the topology of this mesh and the vertices of @p vertices. Stores the result in @p normals. @param[in] accurate  If True, it uses the mixed area term (see above), otherwise it uses a faster version by weighing using the triangle area.
- L157 _public function_ `const Eigen::Matrix<T, 3, -1>& VertexNormals() const` — @returns the vertex normals
- L160 _public function_ `void SetVertexNormals(Eigen::Matrix<T, 3, -1>&& vertexNormals)` — Sets the vertex normals.
- L161 _public function_ `void SetVertexNormals(const Eigen::Matrix<T, 3, -1>& vertexNormals)`
- L164 _public prototype_ `std::vector<int> CalculateBorderVertices() const;` — @returns the border vertices of the mesh
- L167 _public function_ `bool HasTexcoords() const` — @returns True if the mesh has UV coordinates
- L169 _public function_ `int NumTexcoords() const`
- L170 _public function_ `int NumTexTriangles() const`
- L171 _public function_ `int NumTexQuads() const`
- L174 _public function_ `void SetTexcoords(Eigen::Matrix<T, 2, -1>&& texcoords)` — Sets the texture coordinates. Note that the origin of texture coordinates is at the top left corner (as opposed to how it is stored in OBJs)
- L175 _public function_ `void SetTexcoords(const Eigen::Matrix<T, 2, -1>& texcoords)`
- L177 _public function_ `const Eigen::Matrix<T, 2, -1>& Texcoords() const` — @returns the texture coordinates. Note that the origin of texture coordinates is at the top left corner (as opposed to how it is stored in OBJs)
- L179 _public function_ `const Eigen::Matrix<int, 3, -1>& TexTriangles() const`
- L180 _public function_ `void SetTexTriangles(Eigen::Matrix<int, 3, -1>&& tris)`
- L181 _public function_ `void SetTexTriangles(const Eigen::Matrix<int, 3, -1>& tris)`
- L183 _public function_ `const Eigen::Matrix<int, 4, -1>& TexQuads() const`
- L184 _public function_ `void SetTexQuads(Eigen::Matrix<int, 4, -1>&& quads)`
- L185 _public function_ `void SetTexQuads(const Eigen::Matrix<int, 4, -1>& quads)`
- L188 _public prototype_ `std::vector<std::pair<int, int>> GetEdges(const std::vector<int>& vIDs) const;` — @returns all the edges of the mesh. If vIDs.size() > 0 then only edges which are part of vIDs are returned.
- L191 _public function_ `template <class S> Mesh<S> Cast() const`
- L209 _public prototype_ `void Resample(const std::vector<int>& newToOldMap);` — @brief Resample the mesh such that new vertex i will correspond to previous vertex newToOldMap[i]. In the current implementation texture coordinates and texture faces are discarded. @pre newToOldMap Each new vertex needs to point to an existing vertex, and it needs to be unique.
- L212 _public prototype_ `Eigen::Matrix<T, 3, -1> CalculateTriangleNormals() const;` — Calculate and return the triangle normals
- L215 _public prototype_ `void Mask(const Eigen::VectorX<T>& mask);` — Remove all triangles and quads where any vertex is mask[vID] = 0.
- L218 _public prototype_ `void Mask(const std::vector<int>& vIDs);` — Keep only triangles and quads that contain vIDs
- L230 _private member_ `static constexpr int32_t m_version = 1;`
- L232 _private member_ `Eigen::Matrix<T, 3, -1> m_vertices;`
- L233 _private member_ `Eigen::Matrix<int, 3, -1> m_tris;`
- L234 _private member_ `Eigen::Matrix<int, 4, -1> m_quads;`
- L237 _private member_ `Eigen::Matrix<T, 3, -1> m_normals;` — the normals of the mesh (one normal per vertex)
- L240 _private member_ `Eigen::Matrix<T, 2, -1> m_texcoords;` — UVs of the mesh (may be more than one normal per vertex)
- L241 _private member_ `Eigen::Matrix<int, 3, -1> m_tex_tris;`
- L242 _private member_ `Eigen::Matrix<int, 4, -1> m_tex_quads;`

#### enum `Mesh::TriangulationMethod`  
`enum class TriangulationMethod`  
_L96-99_
- desc: Triangulates the Mesh. Quads will be empty afterwards. @returns for each triangle, the index of the quad (bool = true) from which it was triangulated or the triangle id (bool = false)
- L97 _public enumerator_ `Simple`
- L98 _public enumerator_ `Quality`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace trio`
- L20 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::io) template <typename T> bool ToBinaryFile(FILE* pFile, const Mesh<T>& mesh);`
- L26 _prototype_ `template <typename T> bool FromBinaryFile(FILE* pFile, Mesh<T>& mesh);`
- L29 _prototype_ `template <class U> bool FromBinaryFile(trio::BoundedIOStream* stream, Mesh<U>& mesh);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/MeshCorrespondenceSearch.h` (Private)


#### class `MeshCorrespondenceSearch`  
`template <class T> class MeshCorrespondenceSearch`  
_L14-59_
- L26 _public prototype_ `MeshCorrespondenceSearch();`
- L27 _public prototype_ `~MeshCorrespondenceSearch();`
- L28 _public prototype_ `MeshCorrespondenceSearch(MeshCorrespondenceSearch&& o);`
- L29 _public prototype_ `MeshCorrespondenceSearch(const MeshCorrespondenceSearch& o) = delete;`
- L30 _public prototype_ `MeshCorrespondenceSearch& operator=(MeshCorrespondenceSearch&& o);`
- L31 _public prototype_ `MeshCorrespondenceSearch& operator=(const MeshCorrespondenceSearch& o) = delete;`
- L33 _public prototype_ `void Init(const Mesh<T>& targetMesh);`
- L36 _public prototype_ `const Eigen::Vector<T, -1>& TargetWeights() const;` — @returns the target vertex weights, by default border vertices are zero, all others are one.
- L42 _public prototype_ `void SetTargetWeights(const Eigen::Vector<T, -1>& targetWeights);` — Set custom target vertex weights. @pre @p targetWeights need to have the size of the number of vertices of the target mesh
- L44 _public prototype_ `void Search(const Mesh<T>& srcMesh, Result& result, const Eigen::VectorX<T>* weights = nullptr, T normalIncompatibilityThreshold = T(0.5)) const;`
- L45 _public prototype_ `void Search(const Eigen::Matrix<T, 3, -1>& srcVertices, const Eigen::Matrix<T, 3, -1>& srcNormals, Result& result, const Eigen::VectorX<T>* weights = nullptr, T normalIncompatibilityThreshold = T(0.5)) const;`
- L54 _public prototype_ `BarycentricCoordinates<T, 3> Search(const Eigen::Vector3<T>& pt) const;` — Search for the closest point on the target mesh and return them as barycentric coordinates.
- L58 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

#### struct `MeshCorrespondenceSearch::Result`  
`struct Result`  
_L17-23_
- L19 _public member_ `Eigen::VectorXi srcIndices;`
- L20 _public member_ `Eigen::Matrix<T, 3, -1> targetVertices;`
- L21 _public member_ `Eigen::Matrix<T, 3, -1> targetNormals;`
- L22 _public member_ `Eigen::Vector<T, -1> weights;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/MeshSmoothing.h` (Private)


#### class `MeshSmoothing`  
`template <typename T> class MeshSmoothing`  
_L12-23_
- L15 _public prototype_ `void SetTopology(const Mesh<T>& mesh, T identityWeight = T(0.44), T step = T(0.5));`
- L16 _public function_ `void SetWeights(const Eigen::VectorX<T>& weights)`
- L18 _public prototype_ `void Apply(Eigen::Matrix<T, 3, -1>& vertices, int iterations);`
- L21 _private member_ `Eigen::SparseMatrix<T, Eigen::RowMajor> m_smoothingMatrix;`
- L22 _private member_ `Eigen::VectorX<T> m_weights;`
- L26 _function_ `template <typename T> void MeshSmoothing<T>::SetTopology(const Mesh<T>& mesh, T identityWeight, T step)`
- L56 _function_ `template <typename T> void MeshSmoothing<T>::Apply(Eigen::Matrix<T, 3, -1>& vertices, int iterations)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/MeshTools.h` (Private)


#### struct `FaceCoord`  
`struct FaceCoord`  
_L130-196_
- L138 _public member_ `std::vector<int> indices;`
- L139 _public member_ `std::vector<float> weights;`
- L140 _public member_ `bool fixed{};`
- L142 _public prototype_ `FaceCoord() = default;`
- L143 _public function_ `FaceCoord(int vID) : indices(1, vID), weights(1, 1.0f), fixed(false)`
- L145 _public function_ `bool operator!=(const FaceCoord& other) const`
- L152 _public function_ `bool operator==(const FaceCoord& other) const`
- L157 _public function_ `bool IsSamePosition(const FaceCoord& other) const`
- L163 _public function_ `bool IsValid() const`
- L164 _public function_ `bool IsVertex() const`
- L165 _public function_ `bool IsEdge() const`
- L166 _public function_ `bool IsTriangle() const`
- L167 _public function_ `bool IsQuad() const`
- L169 _public function_ `Eigen::Vector3f Evaluate(const Eigen::Matrix<float, 3, -1>& vertices) const`
- L180 _public function_ `int ClosestVertex(const Eigen::Matrix<float, 3, -1>& vertices) const`

#### enum `FaceCoord::Type`  
`enum class Type`  
_L132-136_
- L133 _public enumerator_ `Vertex`
- L134 _public enumerator_ `Edge`
- L135 _public enumerator_ `Face`

#### struct `ContourCorrespondence`  
`struct ContourCorrespondence`  
_L201-207_
- desc: Correspondence to a contour, where it is assumed a contour is a vector of FaceCoord
- L202 _public member_ `int segment{-1};`
- L203 _public member_ `float t{};`
- L204 _public member_ `float geodesicDistance{};`
- L205 _public member_ `float euclideanDistance{};`
- L206 _public function_ `bool IsValid() const`

#### class `MeshTools`  
`class MeshTools`  
_L210-274_
- L221 _public prototype_ `MeshTools();`
- L222 _public prototype_ `~MeshTools();`
- L225 _public prototype_ `std::pair<int, FaceCoord> Select(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh, const Eigen::Vector3f& query, FaceCoord::Type type, float threshold = 1e-1f);` — Get the mesh selection (vertex, edge, face) based on a query point @p query
- L232 _public prototype_ `std::vector<FaceCoord> ShortestPath(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh, FaceCoord startCoord, FaceCoord endCoord);` — Calculate the shortest path between @p startVertexID and @p endVertexID
- L235 _public prototype_ `std::vector<std::pair<float, int>> GeodesicDistance(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh, const FaceCoord& rootCoord, float radius);` — Calculate the approximate geodesic distance for all mesh vertices from @p rootCoord up to @p radius
- L238 _public prototype_ `std::vector<std::pair<float, int>> EuclideanDistance(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh, const Eigen::Vector3f& query, float radius);` — Calculate the approximate euclidean distance for all mesh vertices from @p rootCoord up to @p radius
- L241 _public prototype_ `FaceCoord ClosestFaceCoord(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh, const Eigen::Vector3f& query, const FaceCoord& initCoord, std::vector<FaceCoord>* path = nullptr);` — Find closest facecoord on the mesh to a target position using a walk over the mesh faces
- L244 _public prototype_ `std::vector<float> CalculateLineLength(const std::shared_ptr<const Mesh<float>>& mesh, const std::vector<FaceCoord>& coords) const;` — Calculate the length of the line
- L247 _public prototype_ `std::vector<ContourCorrespondence> CalculateClosestCorrespondences(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh, const std::vector<FaceCoord>& coords, float maxRadius);` — calculate for every vertex of @p mesh the closest correspondence to the contour defined by @p coords
- L250 _public prototype_ `Contour RefineContour(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh, const Contour& contour, const ContourRefinementOptions& options);` — Refine contour
- L253 _public prototype_ `std::vector<int> TopologicalSymmetry(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh, const FaceCoord& coord);` — Get topologyical symmetry based on a selected edge
- L256 _private prototype_ `void Prepare(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh);`
- L257 _private prototype_ `void PrepareHalfEdgeTopology();`
- L258 _private prototype_ `void PrepareKdTree();`
- L259 _private prototype_ `void PrepareAabbTree();`
- L260 _private prototype_ `void PrepareEdgesMap(bool withDiagonals);`
- L263 _private member_ `std::shared_ptr<const Mesh<float>> m_topology;`
- L264 _private member_ `std::shared_ptr<const Mesh<float>> m_triTopology;`
- L265 _private member_ `std::shared_ptr<const HalfEdgeMesh<float>> m_halfEdgeTopology;`
- L266 _private member_ `std::vector<std::pair<int, bool>> m_triToQuadMapping;`
- L267 _private member_ `std::shared_ptr<const Mesh<float>> m_mesh;`
- L268 _private member_ `std::shared_ptr<AABBTree<float>> m_aabbTree;`
- L269 _private member_ `std::shared_ptr<KdTree<float>> m_kdTree;`
- L270 _private member_ `bool m_requiresEdgesMapNoDiagonalsUpdate{};`
- L271 _private member_ `std::vector<std::vector<std::pair<int, float>>> m_edgesMapNoDiagonals;`
- L272 _private member_ `bool m_requiresEdgesMapIncludingDiagonalsUpdate{};`
- L273 _private member_ `std::vector<std::vector<std::pair<int, float>>> m_edgesMapIncludingDiagonals;`

#### struct `MeshTools::ContourRefinementOptions`  
`struct ContourRefinementOptions`  
_L213-218_
- L215 _public member_ `int segments = 5;`
- L216 _public member_ `bool edgesOnly = true;`
- L217 _public member_ `bool useSpline = true;`

#### Free symbols / members of external scopes

- L14 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`
- L35 _function_ `template <class T, int C> Eigen::Vector<T, C> MeanValueCoordinates(const Eigen::Vector3f& query, const Eigen::Matrix<T, 3, C>& vertices)` — Calculates the mean value coordinates of point @p query in the polygon spanned by @p vertices
- L37 _function_ `auto safeTanHalf = [] (T cosAngle)` (scope `MeanValueCoordinates`)
- L80 _function_ `template <class T> std::vector<T> MeanValueCoordinates(const Eigen::Vector3f& query, const std::vector<int>& indices, const Eigen::Matrix<T, 3, -1>& vertices)` — Calculates the mean value coordinates of point @p query in the polygon spanned by @p indices and index @p vertices
- L198 _typedef_ `typedef std::vector<FaceCoord> Contour;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/MetaShapeCamera.h` (Private)


#### class `MetaShapeCamera`  
`template <class T> class MetaShapeCamera : public Camera<T>`  
_L36-144_
- inherits: `Camera<T>`
- desc: The camera model as used in Agisoft PhotoScan/MetaShape. @see (https://www.agisoft.com/pdf/metashape-pro_1_6_en.pdf, https://www.agisoft.com/pdf/metashape-pro_1_5_en.pdf) We use the more generic version of tangential distortion parameters as used in version 1.5. x = X/Z y = Y/Z r = sqrt(x^2 + y^2) x' = x (1 + K1 r^2 + K2 r^4 + K3 r^6 + K4 r^8) + (P1 (r^2 + 2x^2) + 2 P2 x y) (1 + P3 r^2 + P4 r^4) y' = y (1 + K1 r^2 + K2 r^4 + K3 r^6 + K4 r^8) + (P2 (r^2 + 2y^2) + 2 P1 x y) (1 + P3 r^2 + P4 r^4) px = width * 0.5 + cx + x' f + x' B1 + y' B2 py = height * 0.5 + cy + y' f Thereoretically B2 is the skew parameter "a" in the intrinsics, and B1 can be added to the focal length fx = f + B1 K =  |  fx a  cx' | |  0  fy cy' | |  0  0  1   | However, in Agisoft photoscan undistortion also removes B1 and B2, and therefore we do not map the skew parameters into the intrinsics either. Important note: the tangential distortion parameters are swapped relative to the opencv model. Also the OpenCV does not support the K4 parameter. https://docs.opencv.org/2.4/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html
- L39 _public function_ `MetaShapeCamera() : Camera<T>() , m_radialDistortion(0, 0, 0, 0) , m_tangentialDistortion(0, 0, 0, 0) , m_skew(0, 0) , m_sensorID(-1) , m_cameraID(-1)`
- L47 _public prototype_ `virtual ~MetaShapeCamera() = default;`
- L49 _public function_ `const Eigen::Vector<T, 4>& RadialDistortion() const`
- L50 _public function_ `void SetRadialDistortion(const Eigen::Vector<T, 4>& radialDistortion)`
- L52 _public function_ `const Eigen::Vector<T, 4>& TangentialDistortion() const`
- L53 _public function_ `void SetTangentialDistortion(const Eigen::Vector<T, 4>& tangentialDistortion)`
- L55 _public function_ `const Eigen::Vector<T, 2>& Skew() const`
- L56 _public function_ `void SetSkew(const Eigen::Vector<T, 2>& skew)`
- L58 _public function_ `int SensorID() const`
- L59 _public function_ `void SetSensorID(int id)`
- L61 _public function_ `int CameraID() const`
- L62 _public function_ `void SetCameraID(int id)`
- L65 _public function_ `Eigen::Vector2<T> Distort(const Eigen::Vector2<T>& pix) const` — @return the location of the distorted pixel
- L93 _public function_ `Eigen::Vector2<T> Undistort(const Eigen::Vector2<T>& pix, T eps = T(1e-6), int maxIter = 100) const` — @return the location of the undistorted pixel
- L131 _private member_ `Eigen::Vector<T, 4> m_radialDistortion;` — The radial distortion parameters (K1, K2, K3, K4)
- L134 _private member_ `Eigen::Vector<T, 4> m_tangentialDistortion;` — The tangential distortion parameters (P1, P2, P3, P4)
- L137 _private member_ `Eigen::Vector<T, 2> m_skew;` — The skew parameters (B1, B2)
- L140 _private member_ `int m_sensorID;` — Sensor ID
- L143 _private member_ `int m_cameraID;` — Camera ID

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/MultiCameraSetup.h` (Private)


#### class `MultiCameraSetup`  
`template <class T> class MultiCameraSetup`  
_L16-126_
- desc: Class that contains a full camera setup including depth ranges.
- L19 _public prototype_ `MultiCameraSetup() = default;`
- L21 _public function_ `void Init(const std::vector<MetaShapeCamera<float>>& cameras)`
- L32 _public function_ `void SetCameraRanges(const std::map<std::string, std::pair<T, T>>& cameraRanges)`
- L40 _public function_ `void SetCameraRange(const std::string& cameraName, const std::pair<T, T>& cameraRange)`
- L49 _public function_ `const std::vector<std::string>& GetCameraNames() const`
- L54 _public function_ `std::vector<MetaShapeCamera<T>> GetCamerasAsVector() const`
- L64 _public function_ `bool HasCamera(const std::string& name) const`
- L66 _public function_ `const MetaShapeCamera<T>& GetCamera(const std::string& name) const`
- L79 _public function_ `const std::map<std::string, MetaShapeCamera<T>>& GetCameras() const`
- L81 _public function_ `bool HasCameraRange(const std::string& name) const`
- L83 _public function_ `const std::pair<T, T>& GetCameraRange(const std::string& name) const`
- L96 _public function_ `const std::map<std::string, std::pair<T, T>>& GetCameraRanges() const`
- L98 _public function_ `void ScaleCameras(T scale)`
- L118 _public function_ `T GetScale() const`
- L121 _private member_ `std::vector<std::string> m_cameraNames;`
- L122 _private member_ `std::map<std::string, MetaShapeCamera<T>> m_cameraMap;`
- L123 _private member_ `std::map<std::string, std::pair<T, T>> m_cameraRanges;`
- L125 _private member_ `T m_originalCamerasToCurrentCamerasScale = T(1);` — any scaling that was applied to the cameras after setting up the the camera setup

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/MultiCameraTriangulation.h` (Private)


#### class `MultiCameraTriangulation`  
`template <class T> class MultiCameraTriangulation`  
_L23-91_
- desc: Class to do mutli camera triangulation. Requires at least two points. Supports triangulation via DLT as well as the more accurate nonlinear variant (which should be initialized by the linear version)
- L26 _public function_ `void SetCameras(const std::vector<Camera<T>>& cameras)`
- L40 _public function_ `Eigen::Vector3<T> Triangulate(const std::vector<Eigen::Vector2<T>>& pixels) const`
- L60 _public function_ `Eigen::Vector3<T> TriangulateNonlinear(const Eigen::Vector3<T>& initial, const std::vector<Eigen::Vector2<T>>& pixels, const std::vector<T>& confidences) const`
- L89 _private member_ `std::vector<Camera<T>> m_cameras;`
- L90 _private member_ `std::vector<Eigen::Matrix<T, 3, 4>> m_Ps;`

#### Free symbols / members of external scopes

- L70 _function_ `std::function<DiffData<T>(Context<T>*)> evaluationFunction = [&](Context<T>* context)` (scope `MultiCameraTriangulation::TriangulateNonlinear`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/PCA.h` (Private)


#### struct `EigPCA`  
`template <class T, int MatOrder> struct EigPCA`  
_L121-186_
- L123 _public typedef_ `using scalar_t = T;`
- L125 _public member_ `Eigen::VectorX<T> mean;` — mean of pca
- L127 _public member_ `Eigen::Matrix<T, -1, -1, MatOrder> modes;` — modes of PCA as columns scaled by standard deviation of the mode
- L130 _public function_ `template <int MatOrderInput> void Create(const Eigen::Matrix<T, -1, -1, MatOrderInput>& dataMatrix, const DataOrder& dataOrder, const T varianceToKeep, const int maxModes = 0, bool verbose = false)`

#### struct `SvdPCA`  
`template <class T, int MatOrder> struct SvdPCA`  
_L190-227_
- L192 _public typedef_ `using scalar_t = T;`
- L194 _public member_ `Eigen::VectorX<T> mean;` — mean of pca
- L196 _public member_ `Eigen::Matrix<T, -1, -1, MatOrder> modes;` — modes of PCA as columns scaled by standard deviation of the mode
- L199 _public function_ `template <int MatOrderInput> void Create(const Eigen::Matrix<T, -1, -1, MatOrderInput>& dataMatrix, const DataOrder& dataOrder, const T varianceToKeep, const int maxModes = 0, bool verbose = false)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace PCAHelper`
- L27 _function_ `template <class T> int NumberOfModes(const Eigen::VectorX<T>& stds, const T maxVariance, const int maxModes, bool verbose = false)` (scope `PCAHelper`) — @brief Calculates the number of modes to keep for a vector of standard deviations, either limited by the maximum variance or the maximum modes. @tparam T                float or double @param stds              The vector of standard deviations which are assumed to be ordered in decreasing order and >= 0. @param maxVariance      The maximum variance to keep. @param maxModes          The maximum number of modes to be kept. @param verbose           Whether to print verbose output of the variances. @return int              The number of modes.
- L71 _function_ `template <class T, int MatOrder> int NumSamples(const Eigen::Matrix<T, -1, -1, MatOrder>& dataMatrix, const DataOrder dataOrder)` (scope `PCAHelper`) — return the number of samples
- L85 _function_ `template <class T, int MatOrder> std::pair<Eigen::VectorX<T>, Eigen::Matrix<T, -1, -1, MatOrder>> MeanCenterData(const Eigen::Matrix<T, -1, -1, MatOrder>& dataMatrix, const DataOrder dataOrder)` (scope `PCAHelper`) — mean center the data
- L104 _function_ `template <class T, int MatOrder> void MakeModesDeterministic(Eigen::Matrix<T, -1, -1, MatOrder>& modes)` (scope `PCAHelper`) — flip modes to ensure deterministic output
- L235 _function_ `template <class T> Eigen::Matrix<T, -1, -1> CreatePCAWithMeanCenteredData(const Eigen::Matrix<T, -1, -1>& meanCenteredDataMatrix, const T varianceToKeep, const int maxModes = 0)` — @brief Calculates PCA on the mean centered data matrix @p meanCenteredDataMatrix and returns the modes that keep @p varianceToKeep of the variance. @p meanCenteredDataMatrix  Rows are the data samples, columns the dimensions of the data.
- L255 _function_ `template <class T> std::pair<Eigen::VectorX<T>, Eigen::Matrix<T, -1, -1>> CreatePCA(const Eigen::Matrix<T, -1, -1>& dataMatrix, const T varianceToKeep, const int maxModes = 0)` — @brief Calculates PCA on data matrix @p dataMatrix and returns the modes that keep @p varianceToKeep of the variance. @p dataMatrix  Rows are the data samples, columns the dimensions of the data.
- L273 _function_ `template <class T, int D> std::pair<Eigen::VectorX<T>, Eigen::Matrix<T, -1, -1>> PrepareRegionPCAData(const std::vector<Eigen::Matrix<T, D, -1>>& meshes, const std::vector<std::pair<int, T>>& vertexWeights, const bool premultiplyWeight)` — @brief Helper function for PCA calculation. Input data is vectorized and put as rows into the output matrix. Matrix is zero centered and premultiplied with weights, if stated so. @param[in] meshes - The meshes on which PCA is calculated. @param[in] vertexWeights - The vertices for which PCA is calculated together with a weight per vertex. @param[in] premultiplyWeight   Whether the data is weighted before calculating PCA or after calculating PCA for the region. @returns std::pair<Eigen::VectorX<T>, Eigen::Matrix<T, -1, -1>> where the vector is the mean, and matrix is the data
- L320 _function_ `template <class T, int D> Eigen::Matrix<T, -1, -1> PrepareRegionPCAData(const std::vector<Eigen::Matrix<T, D, -1>>& meshes, const Eigen::Matrix<T, D, -1>& mean, const std::vector<std::pair<int, T>>& vertexWeights, const bool premultiplyWeight)`
- L381 _function_ `template <class T, int D> std::pair<Eigen::VectorX<T>, Eigen::Matrix<T, -1, -1>> CreatePCA(const std::vector<Eigen::Matrix<T, D, -1>>& meshes, const std::vector<std::pair<int, T>>& vertexWeights, const T varianceToKeep, const bool premultiplyWeight, const int maxModes = 0)` — @brief Applies PCA for meshes @p meshes and the region as defined by @p vertexWeights. @param[in] meshes - The meshes on which PCA is calculated. @param[in] vertexWeights - The vertices for which PCA is calculated together with a weight per vertex. @param[in] varianceToKeep - The variance to keep for PCA. @param[in] premultiplyWeight - Whether the data is multiplied by weights before calculating PCA or not @param[in] maxModes - The maximum number of modes to keep. If <= 0 then it will calculate it based on @p varianceToKeep @return std::pair<Eigen::VectorX<T>, Eigen::Matrix<T, -1, -1>>  Returns mean and modes of PCA for just the region. The modes are multiplied by the standard deviation.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/PixelFormat.h` (Private)


#### enum `PixelFormat`  
`enum class PixelFormat`  
_L12-19_
- desc: Pixel formats that are accepted by VulkanAllInOneTexture
- L14 _public enumerator_ `MONOCHROME`
- L15 _public enumerator_ `BGR`
- L16 _public enumerator_ `RGB`
- L17 _public enumerator_ `BGRA`
- L18 _public enumerator_ `RGBA`

#### Free symbols / members of external scopes

- L21 _function_ `inline std::string PixelFormatName(PixelFormat pixelFormat)`
- L34 _function_ `inline int NumChannels(PixelFormat pixelFormat)`
- L51 _prototype_ `template <class T> constexpr T SaturatedValue();`
- L52 _function_ `template <class T> constexpr T SaturatedValue();`
- L57 _function_ `template <class T> void Convert(const T* src, T* target, int width, int height, PixelFormat srcPixelFormat, PixelFormat targetPixelFormat)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/Polyline.h` (Private)


#### class `Polyline`  
`template <class T, int D> class Polyline`  
_L17-256_
- desc: Polyline represents a curve as a set of points. When setting the control points, Polyine automtically removes all invalid i.e. zero-length line segments.
- L20 _public prototype_ `Polyline() = default;`
- L21 _public function_ `Polyline(Eigen::Matrix<T, D, -1>&& controlPoints)`
- L26 _public function_ `Polyline(const Eigen::Matrix<T, D, -1>& controlPoints)`
- L32 _public function_ `void Set(Eigen::Matrix<T, D, -1>&& controlPoints)` — Sets the control points of the polyline. Removes all empty segments.
- L38 _public function_ `void Set(const Eigen::Matrix<T, D, -1>& controlPoints)`
- L44 _public function_ `void RemoveEmptySegments()`
- L62 _public function_ `const Eigen::Matrix<T, D, -1>& ControlPoints() const`
- L64 _public function_ `int NumControlPoints() const`
- L67 _public function_ `bool Valid() const` — a polyline is only valid if it has at least two control points.
- L69 _public function_ `Eigen::Vector<T, D> EvaluatePoint(int segment, T lambda) const`
- L82 _public function_ `T ClosestPoint(const Eigen::Vector<T, D>& query, int& closestSegment, T& closestLambda) const` — Finds the closest point by going through all line segments and finding the closest point. @param [in]  query    The query position. @param [out] segment  The segment on which the closest point lies. @param [out] lambda   The lambda value between [0, 1] on the segment. @return the distance to the line
- L135 _public function_ `T ClosestPointAndDirection(const Eigen::Vector<T, D>& query, Eigen::Vector<T, D>& closest, Eigen::Vector<T, D>& direction, T& confidence, const Eigen::Vector<T, -1>* confidences = nullptr) const` — Finds the closest point by going through all line segments and finding the closest point. @param [in]  query      The query position. @param [out] closest    The closest point. @param [out] direction  The direction of the polyline at the closest point (defined by the line segment). @return the distance to the line
- L176 _public function_ `template <typename U = T> T ClosestPointAndNormal(const Eigen::Vector<T, 2>& query, Eigen::Vector<T, 2>& closest, Eigen::Vector<T, 2>& normal, T& confidence, const Eigen::Vector<T, -1>* confidences = nullptr, typename std::enable_if<std::is_same<U, T>::value && D == 2>::type* = 0) const` — Finds the closest point by going through all line segments and finding the closest point. @param [in]  query    The query position. @param [out] closest  The closest point. @param [out] normal   The normal of the polyline at the closest point (defined by the line segment). @return the distance to the line
- L200 _public function_ `template <typename U = T> T ClosestPointAndNormal(const Eigen::Vector<T, 3>& query, Eigen::Vector<T, 3>& closest, Eigen::Vector<T, 3>& normal, Eigen::Vector<T, 3>& direction, T& confidence, typename std::enable_if<std::is_same<U, T>::value && D == 3>::type* = 0) const` — Finds the closest point by going through all line segments and finding the closest point. @param [in]  query     The query position. @param [out] closest   The closest point. @param [out] normal    The random normal of the polyline. @param [out] direction The direction of the line segment. @return the distance to the line
- L227 _public function_ `template <typename U = T> std::vector<std::pair<T, int>> FindIntersections(const Eigen::Vector2<T>& A, const Eigen::Vector2<T>& B, typename std::enable_if<std::is_same<U, T>::value&& D == 2>::type* = 0) const` — Finds all intersection points of the line [A, B] with the polyline. @returns the intersection points as pairs, which contain alpha and control point index below, where alpha values define the intersection point: (1 - alpha) A + alpha B
- L255 _private member_ `Eigen::Matrix<T, D, -1> m_controlPoints;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/Procrustes.h` (Private)


#### class `Procrustes`  
`template <class T, int C> class Procrustes`  
_L16-131_
- desc: Procrustes Analsysis see https://en.wikipedia.org/wiki/Procrustes_analysis, https://en.wikipedia.org/wiki/Orthogonal_Procrustes_problem
- L22 _public function_ `static Affine<T, C, C> AlignRigid(const Eigen::Matrix<T, C, -1>& src, const Eigen::Matrix<T, C, -1>& target, bool withRotation = true)` — Calculate optimal rigid transformation to align src and target: min_affine || target - affine * src ||
- L56 _public function_ `static Affine<T, C, C> AlignRigidWeighted(const Eigen::Matrix<T, C, -1>& src, const Eigen::Matrix<T, C, -1>& target, const Eigen::VectorX<T>& weights, bool withRotation = true)` — Calculate optimal rigid transformation to align src and target: min_affine || (target - affine * src) * weight ||
- L92 _public function_ `static std::pair<T, Affine<T, C, C>> AlignRigidAndScale(const Eigen::Matrix<T, C, -1>& src, const Eigen::Matrix<T, C, -1>& target, bool withRotation = true)` — Calculate optimal rigid transformation and scale to align src and target: min_affine || target - affine * scale * src ||

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/QRigidMotion.h` (Private)


#### struct `QRigidMotion`  
`template <class T> struct QRigidMotion`  
_L30-68_
- desc: Rigid transform using Quaternion rotation.
- L32 _public member_ `Eigen::Quaternion<T> q;`
- L33 _public member_ `Eigen::Vector3<T> t;`
- L35 _public function_ `QRigidMotion() : q(Eigen::Quaternion<T>::Identity()), t(Eigen::Vector3<T>::Zero())`
- L36 _public function_ `QRigidMotion(const Eigen::Quaternion<T>& q, const Eigen::Vector3<T>& t) : q(q), t(t)`
- L37 _public function_ `QRigidMotion(const Eigen::Matrix<T, 4, 4>& mat) : q(mat.template block<3, 3>(0, 0)), t(mat.template block<3, 1>(0, 3))`
- L38 _public function_ `QRigidMotion(const Eigen::Matrix<T, 3, 3>& rot, const Eigen::Vector<T, 3>& t) : q(rot), t(t)`
- L41 _public function_ `Eigen::Transform<T, 3, Eigen::Affine> ToEigenTransform() const`
- L49 _public function_ `void ToEigenTransform(Eigen::Transform<T, 3, Eigen::Affine>& transform) const`
- L55 _public function_ `QRigidMotion operator*(const QRigidMotion& other) const`
- L62 _public function_ `QRigidMotion Inverse() const`

#### Free symbols / members of external scopes

- L8 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/Quaternion.h` (Private)


#### Free symbols / members of external scopes

- L9 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T, bool NORMALIZE> Eigen::Matrix<T, 3, 3> QuaternionToRotationMatrix(const Vector<T>& quaternion)`
- L58 _function_ `template <class T, bool NORMALIZE> Eigen::Matrix<T, 4, 1> QuaternionInverse(const Eigen::Matrix<T, 4, 1>& q)` — Calculates the inverse of the quaternion.
- L71 _function_ `template <class T, bool NORMALIZE> Eigen::Matrix<T, 4, 1> QuaternionMultiplication(const Eigen::Matrix<T, 4, 1>& q1, const Eigen::Matrix<T, 4, 1>& q2)`
- L95 _function_ `template <class T, bool NORMALIZE> Eigen::Matrix<T, 3, 1> QuaternionVectorMultiplication(const Eigen::Matrix<T, 4, 1>& q, const Eigen::Matrix<T, 3, 1>& p)` — Rotates vector \p p using the quaterion \p q. If NORMALIZE is false then it assumes that the quaternion is normalized, otherwise the return vector will be scaled by the squaredNorm of q.
- L117 _function_ `template <class T, bool NORMALIZE> Eigen::Matrix<T, 9, 4> JacobianOfQuaternionToRotationMatrix(const Eigen::Vector4<T>& quaternion)` — Calculates the Jacobian dR/dq i.e of the rotation matrix R with respect to a Quaternion q. To get consistent Jacobians the normalization flag for JacobianOfQuaternionToRotationMatrix and QuaternionToRotationMatrix need to match.
- L219 _function_ `template <class T, bool NORMALIZE> Eigen::Matrix<T, 9, 4> JacobianOfIdentityQuaternionToRotationMatrix()` — Implements the special case of the Jacobian dR/dq of the rotation matrix R with respect to the identity quaternion q i.e. q = [0,0,0,1]. (i.e. apply these numbers to JacobianOfQuaternionToRotationMatrix()) In case of the calculating Jacobians for normalized quaternions the values for the w coordinate cancel completely out, and therefore that dimension can be dropped in an optimization. (see Iterative Estimation of Rotation and Translation using the Quaternion, by Mark Wheeler, 1995)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/QuaternionAverage.h` (Private)


#### Free symbols / members of external scopes

- L14 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/QuaternionVariable.h` (Private)


#### class `QuaternionVariable`  
`template <class T, bool PREMULTIPLY = true> class QuaternionVariable : public MatrixVariable<T, 3, 3>`  
_L29-103_
- inherits: `MatrixVariable<T,3,3>`
- desc: A Rotation variable using a quaternion as the underlying representation. Quaternion updates are handled "incrementally" as described in "Iterative Estimation of Rotation and Translation using the Quaternion", by Mark Wheeler, 1995 https://www.ri.cmu.edu/publications/iterative-estimation-of-rotation-and-translation-using-the-quaternion/. The advantage is that there are only 3 unknowns instead of the general case of 4 variables per quaternion. There are two options: PREMULTIPLY=true: R' = R * dR PREMULTIPLY=false: R' = dR * R
- L32 _public function_ `QuaternionVariable() : MatrixVariable<T, 3, 3>( 3)`
- L34 _public function_ `virtual void Update(const Vector<T>& dx) override`
- L50 _public function_ `virtual bool RealJacobian() override`
- L59 _private function_ `virtual SparseMatrixConstPtr<T> CalculateLocalJacobianMatrix() override` — @return dR/dq i.e. Jacobian of 3x3 rotation matrix with respect to a normalized quaternion
- L90 _private function_ `virtual void ProjectToManifold(Vector<T>& value) override`
- L102 _private member_ `Eigen::Quaternion<T> m_quaternion;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/RayTriangleIntersection.h` (Private)


#### Free symbols / members of external scopes

- L8 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> bool RayTriangleIntersection(const Eigen::Vector3<T>& rayOrigin, const Eigen::Vector3<T>& rayVector, const Eigen::Vector3<T>& vertex0, const Eigen::Vector3<T>& vertex1, const Eigen::Vector3<T>& vertex2, T* outT, Eigen::Vector3<T>* outIntersection)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/RigidICP.h` (Private)


#### Free symbols / members of external scopes

- L12 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) QRigidMotion<float> RigidICP(const Eigen::Matrix<float, 3, -1>& srcPts, const Eigen::Matrix<float, 3, -1>& srcNormals, const std::vector<int>& srcIndices, const Camera<float>& targetCamera, const Eigen::Matrix<float, 4, -1>& targetDepthAndNormals, const QRigidMotion<float>& inputRigidMotion, const int numIterations);`
- L22 _prototype_ `QRigidMotion<float> RigidICPFast(const Eigen::Matrix<float, 3, -1>& srcPts, const Eigen::Matrix<float, 3, -1>& srcNormals, const std::vector<int>& srcIndices, const Camera<float>& targetCamera, const Eigen::Matrix<float, 4, -1>& targetDepthAndNormals, const QRigidMotion<float>& inputRigidMotion, const int numIterations);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/RigidSolve.h` (Private)


#### Free symbols / members of external scopes

- L10 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) /** * Solves the rigid transformation minimizing the point to surface error i.e. sum(weight * targetNormal.dot(R * src + t - targetPt)) with * R = dR * initR * t = dT * initT * It only runs a single iteration of the linearization, and it optimizes from input transformation @p inputRigidMotion. * @param[in] outputDeltaTransform If True, outputs`
- L33 _prototype_ `template <class T> QRigidMotion<T> SolveRigid(const Eigen::Matrix<T, 3, -1>& srcPts, const Eigen::Matrix<T, 3, -1>& targetPts, const Eigen::Matrix<T, 3, -1>& targetNormals, const Eigen::Vector<T, -1>& weights, const Eigen::Vector<bool, 6>& dimensionsToOptimize);` — Solves the rigid transformation minimizing the point to surface error i.e. sum(weight * targetNormal.dot(R * src + t - targetPt)) with It only runs a single iteration of the linearization @param[in] dimensionsToOptimize  Which dimensions of the rotation and translation to optimize [rx, ry, rz, tx, ty, tz]
- L48 _prototype_ `QRigidMotion<float> SolveRigid(const SimdType* srcPtsX, const SimdType* srcPtsY, const SimdType* srcPtsZ, const SimdType* targetPtsX, const SimdType* targetPtsY, const SimdType* targetPtsZ, const SimdType* targetNormalsX, const SimdType* targetNormalsY, const SimdType* targetNormalsZ, const SimdType* weights, const int numSimdElements, const QRigidMotion<float>& inputRigidMotion, bool outputDeltaTransform = false);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/Rotation2DVariable.h` (Private)


#### class `Rotation2DVariable`  
`template <class T> class Rotation2DVariable : public MatrixVariable<T, 2, 2>`  
_L23-94_
- inherits: `MatrixVariable<T,2,2>`
- desc: A 2D Rotation variable using a an angle as underlying representation. https://en.wikipedia.org/wiki/Rotation_matrix
- L26 _public function_ `Rotation2DVariable() : MatrixVariable<T, 2, 2>( 1)`
- L29 _public function_ `void SetAngle(const T& angle)`
- L35 _public function_ `T Angle() const`
- L40 _public function_ `virtual void Update(const Vector<T>& dx) override`
- L47 _public function_ `virtual bool RealJacobian() override`
- L53 _private function_ `Eigen::Matrix<T, 4, 1> CalculateDenseJacobianMatrix()`
- L64 _private function_ `virtual SparseMatrixConstPtr<T> CalculateLocalJacobianMatrix() override` — @return dR/dq i.e. Jacobian of 2D rotation matrix with respect to the rotation angle
- L83 _private function_ `virtual void ProjectToManifold(Vector<T>& value) override`
- L93 _private member_ `Eigen::Rotation2D<T> m_rotation;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/RotationManifold.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T, int SIZE> Eigen::Matrix<T, SIZE, SIZE> ProjectToClosestRotationMatrix(const Eigen::Matrix<T, SIZE, SIZE>& M);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/SnapConfig.h` (Private)


#### struct `SnapConfig`  
`template <class T> struct SnapConfig`  
_L18-39_
- desc: Representation of a simple configuration for snapping vertices on one mesh to corresponding vertices on another mesh
- L20 _public member_ `static constexpr int32_t version = 1;`
- L21 _public member_ `std::string sourceMesh;`
- L22 _public member_ `std::vector<int> sourceVertexIndices;`
- L23 _public member_ `std::vector<int> targetVertexIndices;`
- L26 _public prototype_ `bool ReadJson(const JsonElement& element);` — read the snap config from a json element and return true if successful, false otherwise
- L32 _public prototype_ `void Apply(const Eigen::Matrix<T, 3, -1>& sourceVertices, Eigen::Matrix<T, 3, -1>& targetVertices) const;` — Apply the snap config to 'snap' the target vertices to the same positions as the source vertices @pre indices in the SnapConfig must be in range for the source and target vertices
- L35 _public prototype_ `bool IsValid(const Eigen::Matrix<T, 3, -1>& sourceVertices, const Eigen::Matrix<T, 3, -1>& targetVertices) const;` — is the SnapConfig valid to apply for the supplied source and target vertices ie source and target vertex indices in range
- L38 _public prototype_ `void WriteJson(JsonElement& json) const;` — Write the SnapConfig to Json

#### Free symbols / members of external scopes

- L43 _function_ `template <class T> bool ToBinaryFile(FILE* pFile, const SnapConfig<T>& snapConfig)`
- L54 _function_ `template <class T> bool FromBinaryFile(FILE* pFile, SnapConfig<T>& snapConfig)`
- L73 _function_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, SnapConfig<T>& snapConfig)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/SubdivisionMesh.h` (Private)


#### class `SubdivisionMesh`  
`template <class T> class SubdivisionMesh`  
_L17-37_
- desc: SubdivisionMesh provides functionality to resample a mesh based on subdivision stencil weights.
- L20 _public prototype_ `void Create(const Mesh<T>& subdivisionTopology, const std::vector<std::tuple<int, int, T>>& stencilWeights);`
- L22 _public prototype_ `void SetBaseMesh(const Mesh<T>& mesh);`
- L23 _public prototype_ `void SetBaseVertices(const Eigen::Matrix<T, 3, -1>& vertices);`
- L25 _public prototype_ `Mesh<T> EvaluateMesh(Eigen::VectorX<T> vertexDisplacements = Eigen::VectorX<T>()) const;`
- L27 _public prototype_ `Eigen::VectorX<T> EvaluateWeights(const Eigen::VectorX<T>& baseWeights) const;`
- L29 _public function_ `int NumVertices() const`
- L31 _public function_ `const Mesh<T>& GetSubdivisionMesh() const`
- L34 _private member_ `std::vector<std::tuple<int, int, T>> m_stencilWeights;`
- L35 _private member_ `Mesh<T> m_subdivisionMesh;`
- L36 _private member_ `Mesh<T> m_triangulatedSubdivisionMesh;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/TetConstraints.h` (Private)


#### class `TetConstraints`  
`template <class T> class TetConstraints`  
_L23-181_
- desc: Various tetrahedral contraints including strain hyperelasticity, volume preservation, and the deformation gradient.
- L31 _public prototype_ `TetConstraints() = default;`
- L32 _public prototype_ `TetConstraints(const TetConstraints& o) = delete;`
- L33 _public prototype_ `TetConstraints& operator=(const TetConstraints& o) = delete;`
- L36 _public function_ `void SetTopology(const Eigen::Matrix<int, 4, -1>& tets)` — Sets the topology of the tetrahedral mesh.
- L39 _public prototype_ `void SetRestPose(const Eigen::Matrix<T, 3, -1>& vertices, bool allowInvertedTets = false);` — Set the rest pose of the tetrahedral mesh.
- L47 _public prototype_ `void SetTetsMask(const Eigen::Vector<int, -1>& mask);` — Set mask for the tets. it is different from fixing vertices in a MatrixVariable as boundary primitives would still be evaluated. (mask > 0) -> the tet is not optimized (mask <= 0) -> the tet is optimized
- L50 _public function_ `void ClearTetsMask()` — Delete the mask for the tets. All the tets will be optimized.
- L56 _public function_ `int NumTets() const` — @returns the number of tetraheda.
- L58 _public function_ `const std::vector<Eigen::Matrix<T, 3, 3>>& InvRestFrame() const`
- L59 _public function_ `const std::vector<T>& SqrtRestVolume() const`
- L67 _public prototype_ `DiffData<T> EvaluateStrain(const DiffDataMatrix<T, 3, -1>& vertices, const T strainWeight, ElasticityModel elModel = Corotated) const;` — Tetrahedral strain hyperelasticity. Evaluates residual function r(x) and its Jacobian, e.g. - corotated: r(x) = F(x) - R(F(x)) - Neo Hookean: r(x) = sqrt(trace(F^T * F)) - sqrt(3)
- L71 _public prototype_ `void SetupStrain(const Eigen::Matrix<T, 3, -1>& vertices, const T strainWeight, VertexConstraintsExt<T, 9, 4>& vertexConstraints) const;` — Setup strain constraints in @p vertexConstraints. It is not compatible with pre-stretch
- L79 _public prototype_ `DiffData<T> EvaluateStrainLinearProjective( const DiffDataMatrix<T, 3, -1>& vertices, const T strainWeight, ElasticityModel elModel = Corotated, T minRange = T(1), T maxRange = T(1)) const;` — Tetrahedral strain hyperelasticity. Evaluates residual function r(x) and its Jacobian, e.g. - linear elasticity: r(x) = F(x) - I - corotated: r(x) = F(x) - R (where R is fixed to the rotation closest to F).
- L90 _public prototype_ `DiffData<T> EvaluateVolumeLoss( const DiffDataMatrix<T, 3, -1>& vertices, T volumeWeight) const;` — Tetrahedral volume loss. Evaluates residual function r(x) and its Jacobian, e.g. r(x) = det(F(x)) - 1
- L98 _public prototype_ `DiffData<T> EvaluateVolumeLossProjective( const DiffDataMatrix<T, 3, -1>& vertices, T volumeWeight, T minRange = T(1), T maxRange = T(1)) const;` — Tetrahedral volume loss. Evaluates residual function r(x) and its Jacobian, e.g. r(x) = F(x) - F' (where F' is fixed to the volume preserving deformation closest to F)
- L105 _public prototype_ `DiffDataMatrix<T, 9, -1> EvaluateDeformationGradient(const DiffDataMatrix<T, 3, -1>& vertices, bool volumeWeighted = true, const std::vector<T>& perTetWeight = std::vector<T>()) const;` — @returns F(x)
- L114 _public prototype_ `DiffData<T> EvaluateStrainActivation( const DiffDataMatrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 9, -1>& activations, const T strainWeight) const;` — Tetrahedral strain hyperelasticity evaluated in terms of activation. Evaluates residual function r(x) and its Jacobian, e.g. - r(x) = F(x) - R(x) * A
- L123 _public prototype_ `DiffDataMatrix<T, 9, -1> EvaluateDeformationGradientLossProjective( const DiffDataMatrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 9, -1>& targetGradients, bool volumeWeighted) const;` — Evaluate residual and Jacobian between deformation gradient and desired gradient value.
- L135 _public prototype_ `DiffData<T> EvaluateGravityPotential( const DiffDataMatrix<T, 3, -1>& vertices, const T acceleration, const T density, const int hAxis = 1) const;` — Evaluate gravity potential per-vertex R(x) = mass * acceleration * location[hAxis] The constraint is undefined for points below the zero plane. In the current implementation, points under the zero plane are given zero potential
- L149 _public prototype_ `Eigen::VectorX<T> EvaluateCauchyGreenStrainTensor( const DiffDataMatrix<T, 3, -1>& vertices) const;` — Evaluates the Cauchy-Green tensor, e.g. r(x) = 0.5 * (F^T * F - I) It is useful for color coding the strain over a mesh. The current implementation does not provide the Jacobian.
- L159 _private prototype_ `DiffData<T> EvaluateStrainCorotated(const DiffDataMatrix<T, 3, -1>& vertices, const T strainWeight) const;` — Tetrahedral strain hyperelasticity. Evaluates residual function r(x) and its Jacobian, e.g. - corotated: r(x) = F(x) - R(F(x))
- L166 _private prototype_ `DiffData<T> EvaluateStrainNH(const DiffDataMatrix<T, 3, -1>& vertices, const T strainWeight) const;` — Tetrahedral strain hyperelasticity. Evaluates residual function r(x) and its Jacobian, e.g. - Neo Hookean: r(x) = sqrt(trace(F^T * F)) - sqrt(3)
- L173 _private prototype_ `Eigen::Matrix<T, 3, 3> EvaluateDeformationGradient(const DiffDataMatrix<T, 3, -1>& vertices, const int* v, const int t) const;` — Evaluate elastic deformation gradient for one tet. F_elastic = F_geometry * F_rest^-1 The elastic deformation gradient is employed in the elastic strain evaluation
- L175 _private member_ `int m_numVertices;`
- L176 _private member_ `Eigen::Matrix<int, 4, -1> m_tets;`
- L177 _private member_ `std::vector<Eigen::Matrix<T, 3, 3>> m_invRestFrame;`
- L178 _private member_ `std::vector<T> m_sqrtRestVolume;`
- L179 _private member_ `std::unordered_set<ElasticityModel> validElModels = {Linear, Corotated, NeoHookean};`
- L180 _private member_ `Eigen::Vector<int, -1> m_mask;`

#### enum `TetConstraints::ElasticityModel`  
`enum ElasticityModel`  
_L26-29_
- L28 _public enumerator_ `Linear = 0`
- L28 _public enumerator_ `Linear = 0`
- L28 _public enumerator_ `Linear = 0`

#### Free symbols / members of external scopes

- L13 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/TetMesh.h` (Private)


#### class `TetMesh`  
`template <class T> class TetMesh`  
_L17-63_
- desc: Class representing tetrahedral meshes.
- L20 _public prototype_ `TetMesh() = default;`
- L21 _public prototype_ `TetMesh(const TetMesh& o) = default;`
- L22 _public prototype_ `TetMesh& operator=(const TetMesh& o) = default;`
- L24 _public function_ `int NumVertices() const`
- L25 _public function_ `int NumTets() const`
- L27 _public function_ `const Eigen::Matrix<T, 3, -1>& Vertices() const`
- L28 _public function_ `void SetVertices(const Eigen::Matrix<T, 3, -1>& vertices)`
- L30 _public function_ `const Eigen::Matrix<int, 4, -1>& Tets() const`
- L31 _public function_ `void SetTets(const Eigen::Matrix<int, 4, -1>& tets)`
- L34 _public prototype_ `void LoadFromNPY(std::string vertices_fname, std::string tets_fname);` — Loads m_vertices and m_tets from NPY files
- L37 _public prototype_ `void SaveToNPY(std::string vertices_fname, std::string tets_fname) const;` — Saves m_vertices and m_tets to NPY files
- L39 _public prototype_ `void BoundingBox(Eigen::Vector3<T>& bbmin, Eigen::Vector3<T>& bbmax) const;`
- L42 _public prototype_ `void CropByPlane(std::vector<bool>& tetMask, const Eigen::Vector<T, 3>& normal, T offset) const;` — Sets to false the tetMask tets which have at least one vertex below a plane specified by normal and offset
- L45 _public prototype_ `void FullVisualizationMesh(Eigen::Matrix<T, 3, -1>& visVertices, Eigen::Matrix<int, 3, -1>& visTriangles) const;` — Sets a full visualization mesh: 12 triangles per tetrahedron
- L48 _public prototype_ `void BoundaryMesh(Eigen::Matrix<T, 3, -1>& visVertices, Eigen::Matrix<int, 3, -1>& visTriangles, std::vector<bool>* tetPresent = nullptr) const;` — Sets a boundary visualization mesh: one triangle per boundary face. tetPresent can flag tets to be ignored.
- L51 _public prototype_ `void BoundaryMesh(Eigen::Matrix<int, 3, -1>& visTriangles, std::vector<bool>* tetPresent = nullptr) const;` — Sets the boundary visualization mesh: one triangle per boundary face. tetPresent can flag tets to be ignored. Vertex indices are the same as for tets.
- L54 _public prototype_ `std::vector<int> BoundaryTets() const;` — @return all boundary tets
- L56 _public prototype_ `void TetVolumeStatistics(T& minVol, T& avgVol, T& maxVol, bool absValue = false) const;`
- L58 _public prototype_ `Eigen::VectorX<T> TetVolumes() const;`
- L61 _private member_ `Eigen::Matrix<T, 3, -1> m_vertices;`
- L62 _private member_ `Eigen::Matrix<int, 4, -1> m_tets;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/Triangle.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> T TriangleQuality(const Eigen::Vector3<T>& v1, const Eigen::Vector3<T>& v2, const Eigen::Vector3<T>& v3)`
- L44 _function_ `template <class T> inline Eigen::Vector3<T> ClosestPtPointTriangle(Eigen::Vector3<T> p, Eigen::Vector3<T> a, Eigen::Vector3<T> b, Eigen::Vector3<T> c)` — Closest point calculation as described in "Real-Time Collision Detection" by Christer Ericson @returns the barycentric coordinates

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/TriangleBending.h` (Private)


#### class `TriangleBending`  
`template <class T> class TriangleBending`  
_L33-115_
- desc: Triangle bending model. The triangle bending model creates bending constraints for each pair of triangles that share an edge. The goal is to keep the dihedral angle for the rest and deformed position consistent. The class implements two different models based on a quadratic bending energy as well as measuring the dihedral error directly. See EvaluateQuadratic() and EvaluateDihedral(). The bending model is rotation and translation invariant. EvaluateQuadratic() is scale invariant in the sense that the energy is the same no matter how you scale the rest and deformed vertices, but the scale needs to be consistent for both meshes. EvaluateDihedral() is scale invariant in the sense that both rest vertices and deformed vertices can have completely different scales. Note regarding scale invariance: you need to be careful when integrating the bending constraint with other constraints that may not be scale invariant (e.g. point to point constraint) or otherwise an energy minimization will result in different results depending on the global scale of the data. You can anchieve this by globally modify the bending energy by passing in a global bending weight. Note that testing on spherical triangle meshes has shown that the bending energy is not equal to the integrated squared mean curvature. TODO: figure out why this is not the case. Implemented for T=float and T=double.
- L36 _public prototype_ `TriangleBending() = default;`
- L37 _public prototype_ `TriangleBending(const TriangleBending& o) = delete;`
- L38 _public prototype_ `TriangleBending& operator=(const TriangleBending& o) = delete;`
- L43 _public prototype_ `void SetTopology(const Eigen::Matrix<int, 3, -1>& triangles);` — Sets the triangles/topology for which to calculate the bending terms.
- L47 _public function_ `int NumBendingTerms() const` — @returns the number of bending constraints i.e. the number of neighbouring triangles that share an edge.
- L53 _public prototype_ `void SetRestPose(const Eigen::Matrix<T, 3, -1>& vertices);` — Initializes the rest position for the bending constraints. Sets up the base data for both Quadratic and Dihedral bending constraints.
- L70 _public prototype_ `DiffData<T> EvaluateQuadratic(const DiffDataMatrix<T, 3, -1>& vertices, const T bendingWeight) const;` — Quadratic bending energy (energy = ||K x||_2^2) as described in Bergou et al, "A Quadratic Bending Model for Inextensible Surfaces", see Implementation Details as well as  Wardetzky et al, "Discrete Quadratic Curvature Energies", where Equation (7) is equivalent to the cotan formulation. The latter shows the relationship to the Dihedral error. The main issue of the quadratic bending model is that it is only accurate for inextensible surface i.e. surfaces that cannot strain which is why the model is not scale invariant for different rest and deformed scales. Also the model cannot differentiate between convex and concave curvature. The advantage of the implementation is that the Jacobian is constant, though the Jacobian is also not fully correct as it does not take the normalization of the target vector into account. (see implementation for details) @param vertices       The current deformed vertex configuration. @param bendingWeight  A global weighting factor: energy = bendingWeight ||K x||_2^2
- L82 _public prototype_ `DiffData<T> EvaluateDihedral(const DiffDataMatrix<T, 3, -1>& vertices, const T bendingWeight) const;` — Dihedral bending energy (energy = (theta - theta_rest)^2 Le^2/Ae) as described in Fröhlich and Botsch, "Example-Driven Deformations Based on Discrete Shells" and Grinspun et al, "Discrete Shells", in each case Equation (2). The advantage over the quadratic model is that it optimizes the dihedral angle of neighbouring triangles directly and it is not influenced by any other in-plane deformation of the triangles. However, the cost is that @param vertices       The current deformed vertex configuration. @param bendingWeight  A global weighting factor.
- L85 _public prototype_ `Eigen::VectorX<T> EvaluateAngles(const Eigen::Matrix<T, 3, -1>& vertices) const;` — Calculates the dihedral angle for all neighbouring triangle pairs. Output size is NumBendingTerms().
- L88 _public function_ `const Eigen::VectorX<T>& RestBendingEnergy() const` — @returns The rest bending energy as calculated using th quadratic bending model
- L90 _public function_ `const Eigen::VectorX<T>& RestEdgeAreaSqrt() const`
- L91 _public function_ `const Eigen::VectorX<T>& RestAngle() const`
- L92 _public function_ `const Eigen::VectorX<T>& RestEdgeLength() const`
- L94 _public function_ `const Eigen::Matrix<int, 4, -1> TrianglePairs() const`
- L97 _public prototype_ `Eigen::VectorX<T> EvaluateQuadraticPerVertex(const DiffDataMatrix<T, 3, -1>& vertices) const;` — Evaluate the quadratic bending per edgepair, and then assign for each vertex the maximum bending value
- L100 _public prototype_ `Eigen::VectorX<T> EvaluateDihedralPerVertex(const DiffDataMatrix<T, 3, -1>& vertices) const;` — Evaluate the diahedral bending per edgepair, and then assign for each vertex the maximum bending value
- L103 _private member_ `int m_numVertices;`
- L105 _private member_ `Eigen::Matrix<int, 3, -1> m_triangles;`
- L106 _private member_ `Eigen::Matrix<int, 4, -1> m_trianglePairs;`
- L108 _private member_ `Eigen::Matrix<T, 4, -1> m_K;`
- L109 _private member_ `Eigen::VectorX<T> m_restBendingEnergy;`
- L111 _private member_ `Eigen::VectorX<T> m_restAngle;`
- L112 _private member_ `Eigen::VectorX<T> m_restEdgeAreaSqrt;`
- L113 _private member_ `Eigen::VectorX<T> m_restOneOverEdgeAreaSqrt;`
- L114 _private member_ `Eigen::VectorX<T> m_restEdgeLength;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/TriangleDeformationGradient.h` (Private)


#### class `TriangleDeformationGradient`  
`template <class T> class TriangleDeformationGradient`  
_L29-63_
- desc: Triangle deformation gradient for deformation transfer as described in "Deformation Transfer for Detail-Preserving Surface Editing" by Botsch et al. (however it currently does not include weighting based on the triangle area) The class can be used for deformation transfer in the following way: Input: undeformedA, undeformedB, deformedA Output: deformedB SetTopology(undeformedA.Triangles()) SetRestPose(undeformedA.Vertices()) G = DeformationGradient(deformedA.Vertices()) SetRestPose(undeformedB.Vertices()) minimize(G - DeformationGradient(deformedB)) // using DiffDataMatrix version
- L32 _public prototype_ `TriangleDeformationGradient() = default;`
- L33 _public prototype_ `TriangleDeformationGradient(const TriangleDeformationGradient& o) = delete;`
- L34 _public prototype_ `TriangleDeformationGradient& operator=(const TriangleDeformationGradient& o) = delete;`
- L37 _public prototype_ `void SetTopology(const Eigen::Matrix<int, 3, -1>& triangles);` — Set the mesh topology
- L40 _public prototype_ `void SetRestPose(const Eigen::Matrix<T, 3, -1>& vertices);` — Set the rest pose
- L43 _public function_ `int NumTriangles() const` — Returns the number of triangles
- L48 _public prototype_ `Eigen::Matrix<T, 9, -1> DeformationGradient3D(const Eigen::Matrix<T, 3, -1>& vertices) const;` — Calculate the 3D deformation gradient from the rest pose (@see SetRestPose()) to @p vertices
- L56 _public prototype_ `DiffDataMatrix<T, 9, -1> DeformationGradient3D(const DiffDataMatrix<T, 3, -1>& vertices) const;` — Calculate the 3D deformation gradient from the rest pose (@see SetRestPose()) to @p vertices. As described in "Deformation Transfer for Detail-Preserving Surface Editing", by Botsch et al the Gradient Matrix G does not need the normal, but instead is set to be zero. The Jacobian output accordingly does not need the normal.
- L59 _private member_ `Eigen::Matrix<int, 3, -1> m_triangles;`
- L62 _private member_ `std::vector<Eigen::Matrix<T, 3, 3>> m_invRestFrame3D;` — inv(RestFrame3D) per triangle - (extended by normal)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/TriangleStrain.h` (Private)


#### class `TriangleStrain`  
`template <class T> class TriangleStrain`  
_L35-131_
- desc: Triangle strain using projections as described in Bouaziz et al, "Projective Dynamics: Fusing Constraint Projections for Fast Simulation" see also https://www.shapeop.org. The deformation gradient from the rest triangle to the current triangle should only have a rotation component but no stretching i.e. you can rotate the triangle but not stretch it. Define a Frame (local coordinate system) as [v1 - v0, v2 - v0] Then we get the following deformation gradient: F = CurrFrame * inv(RestFrame) G should only be a rotation, so the closest valid deformation gradient F' = svd(G).U * svd(F).V.t() The stretch energy is therefore || F - F' ||_2^2 For a triangle the deformation gradient has rank 2, and therefore we can simply project the 3D coordinates to 2D: RestFrame = (Proj2D * RestFrame3D) CurrFrame = CurrFrame3D Then F' is a 3x2 matrix. The stretch energy is then || CurrFrame3D * inv(Proj2D * RestFrame3D) - F' ||_2^2 The stretch energy is scale invariant, so typically you would weight the stretch energy scaled by the triangle area: Stretch Energy = triangleArea  * || CurrFrame3D * inv(Proj2D * RestFrame3D) - F' ||_2^2
- L38 _public prototype_ `TriangleStrain() = default;`
- L39 _public prototype_ `TriangleStrain(const TriangleStrain& o) = delete;`
- L40 _public prototype_ `TriangleStrain& operator=(const TriangleStrain& o) = delete;`
- L42 _public prototype_ `void SetTopology(const Eigen::Matrix<int, 3, -1>& triangles);`
- L44 _public prototype_ `void SetRestPose(const Eigen::Matrix<T, 3, -1>& vertices, bool areaWeighs = false);`
- L46 _public function_ `const std::vector<T>& SqrtRestArea() const`
- L64 _public prototype_ `DiffData<T> EvaluateProjectiveStrain(const DiffDataMatrix<T, 3, -1>& vertices, const T strainWeight, const Eigen::Vector<T, -1>& inversionCheck, const T minLambda = T(1), const T maxLambda = T(1)) const;` — Triangle projective strain Evaluates residual function r(x) and its Jacobian, e.g. r(x) = F(x) - F' (where F' is the closest feasible deformation gradient) Triangle inversions are handled according to inversionCheck. (inversionCheckinversionCheck[i] < 0) -> the triangle is flipped and the eigenvalue of the deformation gradient is reflected (maxLambda > 1) and (minLambda < 1) define the maximum allowed stretch and compression
- L72 _public function_ `DiffData<T> EvaluateProjectiveStrain(const DiffDataMatrix<T, 3, -1>& vertices, const T strainWeight, const T minLambda = T(1), const T maxLambda = T(1)) const` — Triangle projective strain Evaluates residual function r(x) and its Jacobian, e.g. r(x) = F(x) - F' (where F' is the closest feasible deformation gradient) (maxLambda > 1) and (minLambda < 1) define the maximum allowed stretch and compression
- L77 _public prototype_ `DiffData<T> EvaluateGreenStrain(const DiffDataMatrix<T, 3, -1>& vertices, const T strainWeight) const;`
- L84 _public prototype_ `DiffData<T> EvaluateNHStrain(const DiffDataMatrix<T, 3, -1>& vertices, const T strainWeight) const;` — Triangular strain hyperelasticity. Evaluates residual function r(x) and its Jacobian, e.g. - Neo Hookean: r(x) = sqrt(trace(F^T * F)) - sqrt(2)
- L86 _public function_ `const Eigen::Matrix<int, 3, -1>& Triangles() const`
- L89 _public prototype_ `Eigen::VectorX<T> EvaluateProjectiveStrainPerVertex(const DiffDataMatrix<T, 3, -1>& vertices) const;` — Evaluate the projective strain per triangle, and then assign for each vertex the maximum strain value
- L92 _public prototype_ `Eigen::VectorX<T> EvaluateGreenStrainPerVertex(const DiffDataMatrix<T, 3, -1>& vertices) const;` — Evaluate the green strain per triangle, and then assign for each vertex the maximum strain value
- L98 _public prototype_ `DiffData<T> EvaluateAreaLoss(const DiffDataMatrix<T, 3, -1>& vertices, T areaWeight) const;` — Triangle area loss. Evaluates residual function r(x) and its Jacobian, e.g. r(x) = sqrt(det(F(x).T * F)) - 1
- L109 _public prototype_ `DiffData<T> EvaluateAreaLossProjective(const DiffDataMatrix<T, 3, -1>& vertices, const T areaWeight, const Eigen::Vector<T, -1>& inversionCheck, const T minLambda = T(1), const T maxLambda = T(1)) const;` — Triangle projective area loss Evaluates residual function r(x) and its Jacobian, e.g. r(x) = F(x) - F' (where F' is fixed to the area preserving deformation closest to F) Triangle inversions are handled according to inversionCheck. (inversionCheckinversionCheck[i] < 0) -> the triangle is flipped and the eigenvalue of the deformation gradient is reflected (maxLambda > 1) and (minLambda < 1) define the maximum allowed stretch and compression
- L117 _public function_ `DiffData<T> EvaluateAreaLossProjective(const DiffDataMatrix<T, 3, -1>& vertices, const T areaWeight, const T minLambda = T(1), const T maxLambda = T(1)) const` — Triangle projective area loss Evaluates residual function r(x) and its Jacobian, e.g. r(x) = F(x) - F' (where F' is fixed to the area preserving deformation closest to F) (maxLambda > 1) and (minLambda < 1) define the maximum allowed stretch and compression
- L123 _private member_ `int m_numVertices;`
- L125 _private member_ `Eigen::Matrix<int, 3, -1> m_triangles;`
- L128 _private member_ `std::vector<Eigen::Matrix<T, 2, 2>> m_invRestFrame2D;` — inv(Proj2D * RestFrame3D) per triangle
- L130 _private member_ `std::vector<T> m_sqrtRestArea;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/VertexConstraints.h` (Private)


#### class `VertexConstraints`  
`template <class T, int ResidualSize, int NumConstraintVertices> class VertexConstraints`  
_L25-226_
- desc: @brief Class encapsulating a set of linearized vertex constraints. @tparam T                      Scalar type, typically float or double. @tparam ResidualSize           Number of constraints per vertex. @tparam NumConstraintVertices  Number of involved vertices per constraint. The jacobian dCdV (i.e. constraint to vertex) is the same for each involved vertex multiplied with the barycentric weights. i.e. dCdV = w1 * dCdV1 + w2 * dCdV2 in case two vertices are involved in a constraint. For individual jacobian per vertex see VertexConstraintsExt
- L28 _public function_ `int64_t NumberOfConstraints() const`
- L30 _public function_ `int64_t NumberOfReservedConstraints() const`
- L32 _public function_ `void Clear(bool clearMemory = false)`
- L45 _public function_ `void ResizeToFitAdditionalConstraints(int64_t numAdditionalConstraints)`
- L58 _public function_ `void AddConstraint(const Eigen::Vector<int, NumConstraintVertices>& vIDs, const Eigen::Vector<T, NumConstraintVertices>& weightsPerVertex, const Eigen::Vector<T, ResidualSize>& residual, const Eigen::Matrix<T, ResidualSize, 3>& jacobian)`
- L71 _public function_ `void AddConstraint(int vID, const T residual, const Eigen::Matrix<T, ResidualSize, 3>& jacobian)`
- L83 _public function_ `void AddConstraint(int vID, const T residual, Eigen::Matrix<T, ResidualSize, 3>&& jacobian)`
- L95 _public function_ `void AddConstraint(int vID, const Eigen::Vector<T, ResidualSize>& residual, const Eigen::Matrix<T, ResidualSize, 3>& jacobian)`
- L106 _public function_ `void AddConstraint(int vID, const Eigen::Vector<T, ResidualSize>& residual, Eigen::Matrix<T, ResidualSize, 3>&& jacobian)`
- L117 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> Residual() const`
- L122 _public function_ `Eigen::VectorX<T> EvaluateResidual(const Eigen::Matrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& baseVertices) const`
- L139 _public function_ `Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> EvaluateJacobian(const Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>& denseVertexJacobian, Eigen::Matrix<T, -1, -1, Eigen::RowMajor>& denseVertexConstraintJacobian, TITAN_NAMESPACE::TaskThreadPool* taskThreadPool = nullptr) const`
- L186 _public function_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> EvaluateJacobian(const Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>& denseVertexJacobian) const`
- L193 _public function_ `SparseMatrix<T> SparseJacobian(int numVertices) const`
- L215 _public function_ `const std::vector<Eigen::Matrix<T, ResidualSize, 3>>& Jacobians() const`
- L216 _public function_ `const std::vector<Eigen::Vector<int, NumConstraintVertices>>& VertexIDs() const`
- L217 _public function_ `const std::vector<Eigen::Vector<T, NumConstraintVertices>>& WeightsPerVertex() const`
- L220 _private member_ `std::vector<Eigen::Vector<int, NumConstraintVertices>> m_vIDs;`
- L221 _private member_ `std::vector<Eigen::Vector<T, NumConstraintVertices>> m_weightsPerVertex;`
- L222 _private member_ `std::vector<Eigen::Vector<T, ResidualSize>> m_residuals;`
- L223 _private member_ `std::vector<Eigen::Matrix<T, ResidualSize, 3>> m_jacobians;`
- L224 _private member_ `int64_t m_numConstraints = 0;`
- L225 _private member_ `int64_t m_reservedConstraints = 0;`

#### class `VertexConstraintsExt`  
`template <class T, int ResidualSize, int NumConstraintVertices> class VertexConstraintsExt`  
_L239-433_
- desc: @brief Class encapsulating a set of linearized vertex constraints. @tparam T                      Scalar type, typically float or double. @tparam ResidualSize           Number of constraints per vertex. @tparam NumConstraintVertices  Number of involved vertices per constraint. The jacobian dCdV (i.e. constraint to vertex) is different for each vertex.
- L242 _public function_ `int64_t NumberOfConstraints() const`
- L244 _public function_ `int64_t NumberOfReservedConstraints() const`
- L246 _public function_ `void Clear(bool clearMemory = false)`
- L258 _public function_ `void ResizeToFitAdditionalConstraints(int64_t numAdditionalConstraints)`
- L270 _public function_ `void AddConstraint(const Eigen::Vector<int, NumConstraintVertices>& vIDs, const Eigen::Vector<T, ResidualSize>& residual, const Eigen::Matrix<T, ResidualSize, 3 * NumConstraintVertices>& jacobian)`
- L283 _public function_ `void AddConstraint(int vID, const T residual, const Eigen::Matrix<T, ResidualSize, 3 * NumConstraintVertices>& jacobian)`
- L294 _public function_ `void AddConstraint(int vID, const T residual, Eigen::Matrix<T, ResidualSize, 3 * NumConstraintVertices>&& jacobian)`
- L305 _public function_ `void AddConstraint(int vID, const Eigen::Vector<T, ResidualSize>& residual, const Eigen::Matrix<T, ResidualSize, 3 * NumConstraintVertices>& jacobian)`
- L315 _public function_ `void AddConstraint(int vID, const Eigen::Vector<T, ResidualSize>& residual, Eigen::Matrix<T, ResidualSize, 3 * NumConstraintVertices>&& jacobian)`
- L325 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> Residual() const`
- L330 _public function_ `Eigen::VectorX<T> EvaluateResidual(const Eigen::Matrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& baseVertices) const`
- L347 _public function_ `Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> EvaluateJacobian(const Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>& denseVertexJacobian, Eigen::Matrix<T, -1, -1, Eigen::RowMajor>& denseVertexConstraintJacobian, TITAN_NAMESPACE::TaskThreadPool* taskThreadPool = nullptr) const`
- L394 _public function_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> EvaluateJacobian(const Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>& denseVertexJacobian) const`
- L401 _public function_ `SparseMatrix<T> SparseJacobian(int numVertices) const`
- L423 _public function_ `const std::vector<Eigen::Vector<T, ResidualSize>>& Residuals() const`
- L424 _public function_ `const std::vector<Eigen::Matrix<T, ResidualSize, 3 * NumConstraintVertices>>& Jacobians() const`
- L425 _public function_ `const std::vector<Eigen::Vector<int, NumConstraintVertices>>& VertexIDs() const`
- L428 _private member_ `std::vector<Eigen::Vector<int, NumConstraintVertices>> m_vIDs;`
- L429 _private member_ `std::vector<Eigen::Vector<T, ResidualSize>> m_residuals;`
- L430 _private member_ `std::vector<Eigen::Matrix<T, ResidualSize, 3 * NumConstraintVertices>> m_jacobians;`
- L431 _private member_ `int64_t m_numConstraints = 0;`
- L432 _private member_ `int64_t m_reservedConstraints = 0;`

#### Free symbols / members of external scopes

- L150 _function_ `auto process = [&](int start, int end)` (scope `VertexConstraints::EvaluateJacobian`)
- L358 _function_ `auto process = [&](int start, int end)` (scope `VertexConstraintsExt::EvaluateJacobian`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/VertexLaplacian.h` (Private)


#### class `VertexLaplacian`  
`template <class T> class VertexLaplacian`  
_L19-57_
- desc: Class to evaluate the classic cotan Laplacian on the vertices of a triangle mesh i.e. E = || Lx - Lx0 ||_2^2. Implemented for T=float and T=double.
- L30 _public prototype_ `VertexLaplacian() = default;`
- L31 _public prototype_ `VertexLaplacian(const VertexLaplacian& o) = delete;`
- L32 _public prototype_ `VertexLaplacian& operator=(const VertexLaplacian& o) = delete;`
- L39 _public prototype_ `void SetRestPose(const Mesh<T>& mesh, Type type = Type::COTAN);` — Sets the rest pose i.e. defines the Laplacian matrix with weights depending on @p type For all types, the resulting Laplacian weights are normalized and divided by the squared root of the vertex area. This means that the resulting vertex laplacian is scale invariant.
- L46 _public prototype_ `DiffDataMatrix<T, 3, -1> EvaluateLaplacianOnOffsets(const DiffDataMatrix<T, 3, -1>& vertexOffsets, const T laplacianWeight) const;` — Evaluate Ldx (instead of Lx - Lx0) @param vertexOffset   The current deformed vertex configuration. @param laplacianWeight  A global weighting factor: energy = laplacianWeight ||L dx||_2^2
- L53 _public prototype_ `static SparseMatrix<T> LaplacianMatrix(const Mesh<T>& mesh, Type type = Type::COTAN, int dim = 1);` — @brief Calculates the laplacian matrix @param dim Set the output dimension i.e. 3 if we use a laplacian per vertex
- L56 _private member_ `SparseMatrix<T> m_laplacianMatrix;`

#### enum `VertexLaplacian::Type`  
`enum class Type`  
_L22-27_
- L24 _public enumerator_ `UNIFORM` — uniform laplacian
- L25 _public enumerator_ `COTAN` — laplacian using cotangent weights
- L26 _public enumerator_ `MEANVALUE`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/geometry/WrapDeformer.h` (Private)


#### struct `WrapDeformerParams`  
`template <class T> struct WrapDeformerParams`  
_L23-41_
- desc: Parameters for a wrap deformer (see below)
- L31 _public member_ `static constexpr int32_t version = 2;`
- L32 _public member_ `bool bExclusiveBind = true;`
- L33 _public member_ `FalloffType falloffType = FalloffType::Volume;`
- L34 _public member_ `T maxDistance = std::numeric_limits<T>::max();`
- L35 _public member_ `T weightThreshold = 0;`
- L36 _public member_ `bool bAutoWeightThreshold = true;`
- L37 _public member_ `T normalOffset = 0;` — optional parameter; if non-zero, wrapping results will be displaced by the normalOffset along the local reference frame normals, allowing a wrapped result to be displaced slightly from its driver mesh
- L38 _public member_ `Eigen::VectorXi wrappedMeshVertexIndicesToApplyTo;` — optional parameter; if empty, the wrap deformer will be applied to all mesh indices; if contains values, it will only be applied to the specified mesh vertices
- L40 _public prototype_ `bool ReadJson(const JsonElement& element);`

#### enum `WrapDeformerParams::FalloffType`  
`enum class FalloffType`  
_L25-29_
- L27 _public enumerator_ `Volume`
- L28 _public enumerator_ `Surface` — TODO Surface falloff is not currently implemented; not sure what surface distance means; perhaps geodesic distance from closest point?

#### class `WrapDeformer`  
`template <class T> class WrapDeformer`  
_L51-97_
- desc: An implementation of a 'wrap-deformer'. A method for deforming one 'wrapped' mesh to follow the deformations of another 'driver' mesh using local nearest point to surface geometry, defined in the local coordinate space of the mesh. This is similar to the Maya Wrap Deformer in concept and results, although we don't know exactly how that is implemented. There are a couple of minor additions to the vanilla Maya implementation: i) you can offset the wrapped mesh along the driver mesh normals, ii) you can specify a subset of wrapped mesh vertices to apply the wrapping to.
- L54 _public function_ `WrapDeformer()`
- L60 _public prototype_ `void SetMeshes(const std::shared_ptr<const Mesh<T>>& driverMesh, const std::shared_ptr<const Mesh<T>>& wrappedMesh);` — set the driver and wrapped meshes without initializing. Note that the driver mesh must contain triangles only. Note that this does NOT re-initialize the other internals of the class and can be used as a means to (re)set the meshes if they have been stored separately from the class
- L63 _public prototype_ `void Init(const WrapDeformerParams<T>& params);` — initialize the deformer from parameters. The driver and wrapped meshes must have been set already.
- L66 _public prototype_ `void Init(const std::shared_ptr<const Mesh<T>>& driverMesh, const std::shared_ptr<const Mesh<T>>& wrappedMesh, const WrapDeformerParams<T>& params);` — initialize the deformer from the driver mesh, the wrapped mesh, and parameters. Note that the driver mesh must contain triangles only, and if specified, wrappedMeshIndicesToApplyTo must be in range
- L73 _public prototype_ `void Deform(const Eigen::Matrix<T, 3, -1>& deformedDriverMeshVertices, Eigen::Matrix<T, 3, -1>& deformedWrappedMeshVertices) const;` — apply the deformer to the driver mesh vertices to give deformedWrappedMeshVertices as a result; deformedDriverMeshVertices must contain the correct number of vertices. Note that if you have specified wrappedMeshIndicesToApplyTo, if the input deformedWrappedMeshVertices contains vertices and is of the correct size, any vertices not specified in wrappedMeshIndicesToApplyTo will be set to the values of those in deformedWrappedMeshVertices
- L78 _public prototype_ `void GetDriverMeshClosestPointBarycentricCoordinates(std::vector<BarycentricCoordinates<T>>& driverMeshClosestPointBarycentricCoordinates) const;` — once initialized, get the barycentric coordinates of the closest point on the driver mesh to each point on the wrapped mesh ie the highest weighted in the wrap deformer
- L80 _public prototype_ `const WrapDeformerParams<T>& Params() const;`
- L92 _private member_ `static constexpr int32_t m_version = 2;`
- L93 _private member_ `std::shared_ptr<const Mesh<T>> m_driverMesh;`
- L94 _private member_ `std::shared_ptr<const Mesh<T>> m_wrappedMesh;`
- L95 _private member_ `std::vector<std::vector<ClosestPointData<T>>> m_driverMeshCorrespondenceClosestPointData;`
- L96 _private member_ `WrapDeformerParams<T> m_wrappingParams;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace trio`
- L100 _prototype_ `template <class T> bool ToBinaryFile(FILE* pFile, const WrapDeformerParams<T>& params);`
- L103 _prototype_ `template <class T> bool FromBinaryFile(FILE* pFile, WrapDeformerParams<T>& params);`
- L106 _prototype_ `template <class T> bool ToBinaryFile(FILE* pFile, const WrapDeformer<T>& wrapDeformer);`
- L109 _prototype_ `template <class T> bool FromBinaryFile(FILE* pFile, WrapDeformer<T>& wrapDeformer);`
- L112 _prototype_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, WrapDeformerParams<T>& params);`
- L115 _prototype_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, WrapDeformer<T>& wrapDeformer);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/math/MKLWrapper.h` (Private)


#### Free symbols / members of external scopes

- L13 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::mkl)`
- L23 _prototype_ `template <class T, int Options> void CreateEigenSparseMatrix(sparse_matrix_t mklA, Eigen::SparseMatrix<T, Options>& A);` — Creates an Eigen Sparse matrix from an MKL sparse matrix.
- L27 _prototype_ `template <class T, int Options> void ComputeAtA(const Eigen::SparseMatrix<T, Options>& A, Eigen::SparseMatrix<T, Options>& AtA);` — Calculates AAt = A * A.transpose().
- L32 _prototype_ `template <class T, int Options> void ComputeAAt(const Eigen::SparseMatrix<T, Options>& A, Eigen::SparseMatrix<T, Options>& AAt);` — Calculates AAt = A * A.transpose().
- L39 _prototype_ `template <class T> void ComputeAAt_UpperOnly(const Eigen::SparseMatrix<T, Eigen::RowMajor>& A, Eigen::SparseMatrix<T, Eigen::RowMajor>& AAt);` — Calculates AAt for the upper triangular matrix only. Note that this is currently slower than ComputeAAt above, so for now this should be used.
- L46 _prototype_ `template <class T> void ComputeAtA_UpperOnly(const Eigen::SparseMatrix<T, Eigen::RowMajor>& A, Eigen::SparseMatrix<T, Eigen::RowMajor>& AtA);` — Calculates AtA for the upper triangular matrix only. Note that this is currently slower than ComputeAAt above, so for now this should be used.
- L50 _function_ `template <class T, int Options> void SparseMatrixMultiply(const Eigen::SparseMatrix<T, Options>& A, bool transposeA, const Eigen::SparseMatrix<T, Options>& B, bool transposeB, Eigen::SparseMatrix<T, Options>& C)` — Calculates the C = op(A) * op(B) where op() is transpose or none
- L97 _function_ `template <class T, int Options> void SparseMatrixReorder(Eigen::SparseMatrix<T, Options>& A)` — Reorders the inner dimension of the matrix so that the inner indices are in order

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/math/Math.h` (Private)


#### Free symbols / members of external scopes

- L13 _typedef_ `template <class T> using Vector = Eigen::Matrix<T, Eigen::Dynamic, 1>;`
- L16 _typedef_ `template <class T> using VectorPtr = std::shared_ptr<Vector<T>>;`
- L19 _typedef_ `template <class T> using VectorConstPtr = std::shared_ptr<const Vector<T>>;`
- L22 _typedef_ `template <class T> using SparseMatrix = Eigen::SparseMatrix<T, Eigen::RowMajor>;`
- L25 _typedef_ `template <class T> using SparseMatrixPtr = std::shared_ptr<SparseMatrix<T>>;`
- L28 _typedef_ `template <class T> using SparseMatrixConstPtr = std::shared_ptr<const SparseMatrix<T>>;`
- L32 _function_ `template <typename T> inline T random()` — basic implementation of a uniform random variable between 0 and 1
- L35 _function_ `template <typename T> inline T clamp(T value, T minValue, T maxValue)` — clamp value
- L43 _function_ `template <typename T> inline T clamped_acos(T value)` — acos ensuring that input is clamped to -1
- L61 _function_ `template <typename T> T cotangent(const Eigen::Vector3<T>& a, const Eigen::Vector3<T>& b)` — cotangent between vector a and b
- L69 _function_ `template <typename T> constexpr T rad2degreeScale()`
- L73 _function_ `template <typename T> T rad2degree(T deg)` — convert from radian to degree
- L77 _function_ `template <typename T> constexpr T degree2radScale()` — convert from degree to radian
- L80 _function_ `template <typename T> T degree2rad(T rad)`
- L82 _function_ `inline int RoundUp(int value, int multiple)`
- L88 _function_ `inline int RoundDown(int value, int multiple)`
- L92 _function_ `template <class T> static bool isIdentityMatrix(const SparseMatrix<T>& mat)` — @returns True if the sparse matrix is an identity matrix.
- L111 _function_ `template <class T> Eigen::Matrix<T, 3, 3> CrossProductMatrix(const Eigen::Vector<T, 3>& vec)` — Calculates the cross product matrix such that for the cross product c = a x b, we have c = CrossProductMatrix(a) * b CrossProductMatrix([x y z]^T) = |  0  -z   y  | |  z   0  -x  | | -y   x   0  |
- L135 _function_ `template <class T> SparseMatrix<T> AddSparseMatricesAndPadColumns(const SparseMatrix<T>& A, const SparseMatrix<T>& B, bool squeeze)` — Adds two compressed sparse CRS matrices. Both matrices need to have the same number of rows, but the columns may differ. In this case the output matrix will have the larger of the two column dimensions and the smaller of the two matrices is considered to be filled with zeros. A: (rows, cols_a) B: (rows, cols_b) output: (rows, max(cols_a, cols_b))
- L249 _function_ `template <class T> void RepeatRowsOfSparseMatrix(const SparseMatrix<T>& A, SparseMatrix<T>& output, int n)` — Create a new sparse matrix by repeating the rows of the input matrix @p n times output =  | A | | A | | ... | | A |
- L317 _function_ `template <class T> void ConcatenateSparseMatricesAlongRowDimension(const std::vector<std::reference_wrapper<const SparseMatrix<T>>>& inputs, SparseMatrix<T>& output)` — Concatenates a set of sparse matrices along the row dimension. Input matrices may be compressed or uncompressed, the output is always a compressed sparse matrix. Precondition: all input matrices need to be valid (no nullptr) and have the same number of cols.
- L404 _function_ `template <class T> SparseMatrix<T> RowGather(const SparseMatrix<T>& inSparse, const Eigen::VectorX<int>& blockIndices, int blockSize = 1)` — Gathers rows from the sparse matrix. @param blockIndices  The indices indicate which rows to select from the sparse matrix. rowIndex = blockIdx * blockSize @param blockSize		The size of each row block i.e. for blockSize = 1, the blockIndices are equivalent to rowIndices.
- L462 _function_ `template <class T> SparseMatrix<T> RowScatter(const SparseMatrix<T>& inSparse, const int outputRows, const Eigen::VectorX<int>& blockIndices, int blockSize = 1)` — Scatters rows from the sparse matrix. @param blockIndices  The indices indicate where each row of the input matrix is placed in the output matrix. @param blockSize		The size of each row block i.e. for blockSize = 1, the blockIndices are equivalent to rowIndices.
- L514 _function_ `template <class T> SparseMatrix<T> ColGather(const SparseMatrix<T>& inSparse, const Eigen::VectorX<int>& blockIndices, int blockSize = 1)` — Gathers columns from the sparse matrix. @param blockIndices  The indices indicate which rows to select from the sparse matrix. rowIndex = blockIdx * blockSize @param blockSize		The size of each row block i.e. for blockSize = 1, the blockIndices are equivalent to rowIndices.
- L531 _function_ `template <class T> SparseMatrix<T> ColScatter(const SparseMatrix<T>& inSparse, const int outputCols, const Eigen::VectorX<int>& blockIndices, int blockSize = 1)` — Scatters rows from the sparse matrix. @param blockIndices  The indices indicate which rows to select from the sparse matrix. rowIndex = blockIdx * blockSize @param blockSize		The size of each row block i.e. for blockSize = 1, the blockIndices are equivalent to rowIndices.
- L547 _function_ `template <typename _Scalar, int _Options, typename _StorageIndex> void DiscardEmptyInnerDimensions(Eigen::SparseMatrix<_Scalar, _Options, _StorageIndex>& sparse, Eigen::Matrix<int, -1, 1>& indices)` — Removes the empty inner dimensions of a sparse matrix (removes empty rows for row major, and empty columns for column major), and outputs the indices of the old rows/columns to the new rows/columns.
- L605 _function_ `template <class T> void Dense2Sparse(const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>& dense, SparseMatrix<T>& sparse, int rowOffset, int colOffset)` — Convert a dense matrix to a sparse matrix. As opposed to dense.sparseView() it keeps zero values in the matrix. @param colOffset  Offsets the dense matrix keeping the first colOffset colums of the sparse matrix empty
- L626 _function_ `template <class T> inline int NumNonzerosForRow(const SparseMatrix<T>& smat, int row)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/math/PCG.h` (Private)


#### class `PCG`  
`template <typename MatrixType> class PCG`  
_L16-116_
- desc: Preconditioned Conjugate Gradient that uses multi-threading for matrix vector multiplication. Only supports row-major matrices (both dense and sparse).
- L17 _private typedef_ `using T = typename MatrixType::Scalar;`
- L20 _public function_ `PCG(int size = 0, const std::shared_ptr<TaskThreadPool>& threadPool = TaskThreadPool::GlobalInstance(false)) : m_xrpqzc(size, 6) , m_threadPool(threadPool)`
- L27 _public function_ `Eigen::Ref<Eigen::VectorX<T>> Solve(int iterations, const MatrixType& A, const Eigen::VectorX<T>& rhs, const Eigen::VectorX<T>& xInit)` — Solve Ax = b
- L91 _public function_ `Eigen::Ref<Eigen::VectorX<T>> x()`
- L92 _public function_ `Eigen::Ref<Eigen::VectorX<T>> r()`
- L93 _public function_ `Eigen::Ref<Eigen::VectorX<T>> p()`
- L94 _public function_ `Eigen::Ref<Eigen::VectorX<T>> q()`
- L95 _public function_ `Eigen::Ref<Eigen::VectorX<T>> z()`
- L96 _public function_ `Eigen::Ref<Eigen::VectorX<T>> c()`
- L98 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> x() const`
- L99 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> r() const`
- L100 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> p() const`
- L101 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> q() const`
- L102 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> z() const`
- L103 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> c() const`
- L105 _public function_ `const T TolError() const`
- L106 _public function_ `const T ResError() const`
- L107 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> Result() const`
- L110 _private member_ `Eigen::Matrix<T, -1, 6> m_xrpqzc;`
- L112 _private member_ `T m_tolError{};`
- L113 _private member_ `T m_resError{};`
- L115 _private member_ `std::shared_ptr<TaskThreadPool> m_threadPool;`

#### class `ParallelPCG`  
`template <typename CGProblem> class ParallelPCG`  
_L131-259_
- desc: Class to solve a ConjugateGradient Problem where the matrix multiplication residual = rhs - A * x is calculated in multiple segments by a user provide CGProblem type i.e. residual = rhs - sum_i A[i] * x. As opposed @tparam CGProblem  Needs to define all functions to solve the conjugate gradient problem including - Rhs(); which returns the right-hand side of the problem residual = Rhs() - A x() - DiagonalPreconditioner(): the diagonal preconditioner for matrix A - NumSegments(): the number partial matrix multiplications - MatrixMultiply(): the partial multiplication A(i) * x, where A * x = sum_i A(i) x
- L132 _private typedef_ `using T = typename CGProblem::ScalarType;`
- L134 _public function_ `ParallelPCG(const std::shared_ptr<TaskThreadPool>& threadPool) : m_threadPool(threadPool)`
- L142 _public function_ `Eigen::Ref<Eigen::VectorX<T>> Solve(int iterations, const CGProblem& problem, const Eigen::VectorX<T>& xInit = Eigen::VectorX<T>())` — Solve Ax = b
- L233 _public function_ `Eigen::Ref<Eigen::VectorX<T>> x()`
- L234 _public function_ `Eigen::Ref<Eigen::VectorX<T>> r()`
- L235 _public function_ `Eigen::Ref<Eigen::VectorX<T>> p()`
- L236 _public function_ `Eigen::Ref<Eigen::VectorX<T>> z()`
- L237 _public function_ `Eigen::Ref<Eigen::VectorX<T>> c()`
- L239 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> x() const`
- L240 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> r() const`
- L241 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> p() const`
- L242 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> z() const`
- L243 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> c() const`
- L245 _public function_ `Eigen::Ref<Eigen::VectorX<T>> q(int i)`
- L246 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> q(int i) const`
- L248 _public function_ `T TolError() const`
- L249 _public function_ `T ResidualError() const`
- L252 _private member_ `Eigen::Matrix<T, -1, 5> m_xrpzc;`
- L253 _private member_ `Eigen::Matrix<T, -1, -1> m_qs;`
- L255 _private member_ `T m_tolError;`
- L256 _private member_ `T m_resError;`
- L258 _private member_ `std::shared_ptr<TaskThreadPool> m_threadPool;`

#### Free symbols / members of external scopes

- L162 _function_ `taskFutures.Add(m_threadPool->AddTask(std::bind([&](int segmentId) { problem.MatrixMultiply(q(segmentId), segmentId, x()); }, i)));` (scope `ParallelPCG::Solve`)
- L203 _function_ `taskFutures.Add(m_threadPool->AddTask(std::bind([&](int segmentId) { problem.MatrixMultiply(q(segmentId), segmentId, p()); }, i)));` (scope `ParallelPCG::Solve`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/math/ParallelBLAS.h` (Private)


#### Free symbols / members of external scopes

- L8 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`
- L19 _prototype_ `template <class T> void ParallelNoAliasGEMV(Eigen::Ref<Eigen::Matrix<T, -1, 1>, 0, Eigen::InnerStride<1>> out, const Eigen::SparseMatrix<T, Eigen::RowMajor>& A, const Eigen::Ref<const Eigen::Matrix<T, -1, 1>, 0, Eigen::InnerStride<1>>& x, TaskThreadPool* taskThreadPool);` — Method to calculate out = A * x for a sparse matrix with explicit multi-threading.
- L29 _prototype_ `template <class T> void ParallelNoAliasGEMV(Eigen::Ref<Eigen::Matrix<T, -1, 1>, 0, Eigen::InnerStride<1>> out, const Eigen::Ref<const Eigen::Matrix<T, -1, 1>, 0, Eigen::InnerStride<1>>& b, const Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>, 0, Eigen::OuterStride<-1>>& A, const Eigen::Ref<const Eigen::Matrix<T, -1, 1>, 0, Eigen::InnerStride<1>>& x, TaskThreadPool* taskThreadPool);` — Method to calculate out = A * x + b with explicit multi-threading. It is only used in case MKL is not available, as MKL will perform multi-threading for matrix multiplication.
- L41 _prototype_ `template <class T> void ParallelAtALowerAdd(Eigen::Ref<Eigen::Matrix<T, -1, -1>> AtA, const Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>, 0, Eigen::OuterStride<-1>>& A, TaskThreadPool* taskThreadPool);` — Method to calculate the lower triangular matrix of AtA with multi-threading. It is only used in case MKL is not available, as MKL will perform multi-threading for matrix multiplication. AtA.triangularView<Eigen::Lower>() += A.transpose() * A
- L51 _prototype_ `template <class T> void ParallelAtALowerAdd(Eigen::Ref<Eigen::Matrix<T, -1, -1>> AtA, const Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>, 0, Eigen::OuterStride<-1>>& A, T scale, TaskThreadPool* taskThreadPool);` — Method to calculate the lower triangular matrix of scaled AtA with multi-threading. It is only used in case MKL is not available, as MKL will perform multi-threading for matrix multiplication. AtA.triangularView<Eigen::Lower>() += scale * A.transpose() * A
- L62 _prototype_ `template <class T> void ParallelAtALower(Eigen::Ref<Eigen::Matrix<T, -1, -1>> AtA, const Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>, 0, Eigen::OuterStride<-1>>& A, TaskThreadPool* taskThreadPool);` — Method to calculate the lower triangular matrix of AtA with multi-threading. It is only used in case MKL is not available, as MKL will perform multi-threading for matrix multiplication. AtA.triangularView<Eigen::Lower>() = A.transpose() * A

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/math/SparseMatrixBuilder.h` (Private)


#### class `SparseMatrixInnerBuilder`  
`template <class T> class SparseMatrixInnerBuilder`  
_L17-78_
- desc: The SparseMatrixInnerBuilder class is used to incrementally build a sparse inner (row or column) vector by keeping track of the indexed data in an remapping vector and a separate row index and value vector. TODO: it might be faster to use a memset to clear the data once a certain fill factor has been reached
- L20 _public function_ `SparseMatrixInnerBuilder()`
- L24 _public function_ `void Init(int innerSize)` — Create an empty sparse inner vector of size @p innerSize
- L33 _public function_ `void Add(int innerIndex, T value)` — Add @p value at index @p innerIndex
- L51 _public function_ `int Size() const` — @return the number of elements in the sparse vector
- L57 _public function_ `void Clear()` — Clears the remapping by going though all current indices and setting them to -1
- L68 _public function_ `typename Eigen::VectorXi::ConstSegmentReturnType InnerIndices() const` — @return the inner indices
- L71 _public function_ `typename Eigen::VectorX<T>::ConstSegmentReturnType Values() const` — @return the values
- L74 _private member_ `int m_currentCounter = 0;`
- L75 _private member_ `Eigen::VectorXi m_indexMapping;`
- L76 _private member_ `Eigen::VectorXi m_innerIndices;`
- L77 _private member_ `Eigen::VectorX<T> m_values;`

#### class `SparseMatrixBuilder`  
`template <class T, int BLOCK_SIZE> class SparseMatrixBuilder`  
_L104-224_
- desc: The SparseMatrixBuilder class is used to incrementally build a sparse (row or column-major) matrix by filling @p BLOCK_SIZE rows or columns at a time. In the following we sparse inner vector to represent the block of rows or columns that are being filled. The builder can be used for either row or column major matrices, but the caller needs to make sure to use the corresponding outerIndex and innerIndex. Use it in the following way: SparseMatrixBuilder builder(M, N) for (int b = 0; b < M; b += BLOCK_SIZE) { StartBlock(b); // add arbitrary number of values using // Add(outerIndex, innerIndex, value)    where outerIndex needs to be b <= outerIndex < b + BLOCK_SIZE // ... FinalizeBlock(); } SparseMatrix<T> sMat; builder.Build(sMat); Note that the functionality is similar to Eigen::SparseMatrix::startVec(), ::insertBackByOuterInnerUnordered(), and ::finalize() but supports multiple rows at a time.
- L107 _public function_ `SparseMatrixBuilder(int outerSize, int innerSize, T allocationRatio = T(0.1))`
- L127 _public function_ `void StartBlock(int outerIndex)` — Start the next block of sparse inner vectors
- L140 _public function_ `void Add(int outerIndex, int innerIndex, T value)` — Add items to the current block of sparse vectors @pre m_currentOuterIndexStart <= outerIndex < m_currentOuterIndexStart + BLOCK_SIZE
- L157 _public function_ `void FinalizeBlock()` — Finalizes the current block of sparse inner vectors and copies the data to internal arrays.
- L190 _public function_ `template <int Options> void Build(Eigen::SparseMatrix<T, Options>& m)` — Builds an Eigen::SparseMatrix from the assembled sparse vector data.
- L210 _private member_ `int m_outerSize = 0;`
- L211 _private member_ `int m_innerSize = 0;`
- L212 _private member_ `int m_currentOuterIndexStart = 0;`
- L213 _private member_ `SparseMatrixInnerBuilder<T> m_innerBuilders[BLOCK_SIZE];`
- L215 _private member_ `bool m_blockInProgress = false;`
- L218 _private member_ `int m_allocationIncrement = 1;` — data for assembled matrix
- L219 _private member_ `int m_allocatedSize = 0;`
- L220 _private member_ `int m_currentSize = 0;`
- L221 _private member_ `Eigen::VectorXi m_outerIndices;`
- L222 _private member_ `Eigen::VectorXi m_innerIndices;`
- L223 _private member_ `Eigen::VectorX<T> m_values;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/math/SparseMatrixMultiply.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T, int Options> void SparseMatrixMultiply(const Eigen::SparseMatrix<T, Options>& A, bool transposeA, const Eigen::SparseMatrix<T, Options>& B, bool transposeB, Eigen::SparseMatrix<T, Options>& C)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/math/SparseMatrixReorder.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T, int Options> void SparseMatrixReorder(Eigen::SparseMatrix<T, Options>& A)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/rendering/Rasterizer.h` (Private)


#### Free symbols / members of external scopes

- L10 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> T OrientedArea2(const Eigen::Vector2<T> a, const Eigen::Vector2<T> b, const Eigen::Vector2<T> c)`
- L28 _function_ `template <class T> void RasterizeTriangleInsideOut(const Eigen::Matrix<T, 3, 3>& vertices, const Eigen::Matrix<T, 4, 3>& barycentricCoordinates, int width, int height, const std::function<void(int x, int y, T depth, const Eigen::Vector3<T>& bc)>& drawFunction)` — Rasterizes a triangle by traversing the bounding box and testing each pixel using an inside-out test. It assumes that (0,0) is the pixel-center of the top left corner. The reason is that triangle rasterization then works directly with integer coordinates. Depth and homogenous barycentric coordinates are interpolated linearly. Points that have depth outside the range (0, 1] are clipped.
- L108 _function_ `template <class T> void cullAndRasterizeTriangle(const Eigen::Matrix<T, 4, 3>& vertices, const int width, const int height, const std::function<void(int x, int y, T depth, const Eigen::Vector3<T>& bc)>& drawFunction)` — Rasterizes a triangle, but culls triangles that fall outside the view volume. The view volume is defined by x: [-1, 1] y: [-1, 1] z: [1, 0]  // reverse with 0 being the furthest depth @param vertices      The homogeneous vertex matrix (vertices are the columns of the matrix) @param width         The width of the output image @param height        The height of the output image @param drawFunction  For every rasterized pixel the drawFunction() is called with the pixel position (origin is center of top left pixel), the depth of the vertex [1, 0] and the perspectively correct interpolated barycentric coordinates.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/serialization/AffineSerialization.h` (Private)


#### Free symbols / members of external scopes

- L13 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`
- L20 _function_ `template <class T, int R, int C> JsonElement ToJson(const std::vector<Affine<T, R, C>>& aff)`
- L32 _function_ `template <class T, int R, int C> void FromJson(const JsonElement& j, Affine<T, R, C>& aff)` — deserializes an affine matrix from json format
- L38 _function_ `template <class T, int R, int C> void FromJson(const JsonElement& j, std::vector<Affine<T, R, C>>& aff)`
- L51 _function_ `template <class T, int R, int C> bool ToBinaryFile(FILE* pFile, const Affine<T, R, C>& mat)` — Serializes an affine matrix to binary format
- L63 _function_ `template <class T, int R, int C> bool FromBinaryFile(FILE* pFile, Affine<T, R, C>& mat)` — Deserializes an affine matrix from binary format
- L83 _function_ `template <class T, int R, int C> bool FromBinaryFile(trio::BoundedIOStream* stream, Affine<T, R, C>& mat)` — Deserializes an affine matrix from binary format

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/serialization/BinarySerialization.h` (Private)


#### Free symbols / members of external scopes

- L16 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::io) template <class T> bool ToBinaryFile(FILE* pFile, const Eigen::SparseMatrix<T>& mat)`
- L45 _function_ `template <typename T> inline bool ToBinaryFile(FILE* pFile, const T& value, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0)`
- L51 _function_ `template <typename T> inline bool ToBinaryFile(FILE* pFile, const T& str, typename std::enable_if<std::is_same<T, std::string>::value, int>::type = 0)`
- L61 _function_ `template <class T, int R, int C> bool ToBinaryFile(FILE* pFile, const Eigen::Matrix<T, R, C>& mat)` — Serializes a column-major matrix to binary format
- L76 _prototype_ `template <typename S, typename T> inline bool ToBinaryFile(FILE* pFile, const std::map<S,T>& values);`
- L79 _prototype_ `template <typename T> bool ToBinaryFile(FILE* pFile, const Mesh<T>& mesh);`
- L82 _prototype_ `template <typename T> bool FromBinaryFile(FILE* pFile, Mesh<T>& mesh);`
- L85 _prototype_ `template <class T> inline bool ToBinaryFile(FILE* pFile, const std::shared_ptr<const Mesh<T>>& mesh);`
- L88 _prototype_ `template <class T> inline bool FromBinaryFile(FILE* pFile, std::shared_ptr<Mesh<T>>& mesh);`
- L91 _function_ `template <typename T> inline bool ToBinaryFile(FILE* pFile, const std::vector<T>& values, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0)`
- L99 _function_ `template <typename T> bool ToBinaryFile(FILE* pFile, const std::vector<T>& values, typename std::enable_if<!std::is_arithmetic<T>::value, int>::type = 0)`
- L110 _function_ `template <typename S, typename T> inline bool ToBinaryFile(FILE* pFile, const std::map<S,T>& values)`
- L123 _function_ `template <typename S, typename T> inline bool ToBinaryFile(FILE* pFile, const std::pair<S, T>& pair)`
- L135 _function_ `template <typename T> inline bool FromBinaryFile(FILE* pFile, T& value, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0)`
- L141 _function_ `template <typename T> bool FromBinaryFile(FILE* pFile, T& str, typename std::enable_if<std::is_same<T, std::string>::value, int>::type = 0)`
- L150 _function_ `template <class T> bool FromBinaryFile(FILE* pFile, Eigen::SparseMatrix<T>& mat)`
- L197 _function_ `template <class T, int R, int C> bool FromBinaryFile(FILE* pFile, Eigen::Matrix<T, R, C>& mat)` — Deserializes a column-major matrix from binary format
- L231 _prototype_ `template <typename S, typename T> inline bool FromBinaryFile(FILE* pFile, std::map<S,T>& values);`
- L234 _function_ `template <typename T> inline bool FromBinaryFile(FILE* pFile, std::vector<T>& values, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0)`
- L243 _function_ `template <typename T> bool FromBinaryFile(FILE* pFile, std::vector<T>& values, typename std::enable_if<!std::is_arithmetic<T>::value, int>::type = 0)`
- L256 _function_ `template <typename S, typename T> inline bool FromBinaryFile(FILE* pFile, std::map<S,T>& values)`
- L273 _function_ `template <typename S, typename T> inline bool FromBinaryFile(FILE* pFile, std::pair<S, T>& pair)`
- L289 _function_ `template <typename T> inline bool ReadAndCheckOrRevertFromBinaryFile(FILE* pFile, const T& expected)` — utility to read and check for a value, and revert in case the value is not valid
- L307 _function_ `template <typename T> bool ToBinaryFile(FILE* pFile, const Mesh<T>& mesh)`
- L322 _function_ `template <typename T> bool FromBinaryFile(FILE* pFile, Mesh<T>& mesh)`
- L347 _function_ `template <class T> inline bool ToBinaryFile(FILE* pFile, const std::shared_ptr<const Mesh<T>>& mesh)` — template specializations for serializing and deserializing shared ptrs to meshes
- L364 _function_ `template <class T> inline bool FromBinaryFile(FILE* pFile, std::shared_ptr<Mesh<T>>& mesh)`
- L391 _prototype_ `template <typename T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, T& value, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0);`
- L394 _prototype_ `template <typename T> bool FromBinaryFile(trio::BoundedIOStream* stream, T& str, typename std::enable_if<std::is_same<T, std::string>::value, int>::type = 0);`
- L397 _prototype_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, Eigen::SparseMatrix<T>& mat);`
- L400 _prototype_ `template <class T, int R, int C> bool FromBinaryFile(trio::BoundedIOStream* stream, Eigen::Matrix<T, R, C>& mat);`
- L403 _prototype_ `template <typename S, typename T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, std::map<S, T>& values);`
- L406 _prototype_ `template <typename T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, std::vector<T>& values, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0);`
- L409 _prototype_ `template <typename T> bool FromBinaryFile(trio::BoundedIOStream* stream, std::vector<T>& values, typename std::enable_if<!std::is_arithmetic<T>::value, int>::type = 0);`
- L412 _prototype_ `template <typename S, typename T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, std::pair<S, T>& pair);`
- L415 _prototype_ `template <typename T> bool FromBinaryFile(trio::BoundedIOStream* stream, Mesh<T>& mesh);`
- L418 _prototype_ `template <class T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, std::shared_ptr<Mesh<T>>& mesh);`
- L421 _function_ `template <typename T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, T& value, typename std::enable_if<std::is_arithmetic<T>::value, int>::type)`
- L428 _function_ `template <typename T> bool FromBinaryFile(trio::BoundedIOStream* stream, T& str, typename std::enable_if<std::is_same<T, std::string>::value, int>::type)`
- L455 _function_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, Eigen::SparseMatrix<T>& mat)`
- L492 _function_ `template <class T, int R, int C> bool FromBinaryFile(trio::BoundedIOStream* stream, Eigen::Matrix<T, R, C>& mat)`
- L540 _function_ `template <typename T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, std::vector<T>& values, typename std::enable_if<std::is_arithmetic<T>::value, int>::type)`
- L567 _function_ `template <typename T> bool FromBinaryFile(trio::BoundedIOStream* stream, std::vector<T>& values, typename std::enable_if<!std::is_arithmetic<T>::value, int>::type)`
- L593 _function_ `template <typename S, typename T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, std::map<S, T>& values)`
- L627 _function_ `template <typename S, typename T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, std::pair<S, T>& pair)`
- L650 _function_ `template <typename T> bool FromBinaryFile(trio::BoundedIOStream* stream, Mesh<T>& mesh)`
- L675 _function_ `template <class T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, std::shared_ptr<Mesh<T>>& mesh)`
- L705 _function_ `template <typename T> inline bool ReadAndCheckOrRevertFromBoundedIOStream(trio::BoundedIOStream* stream, const T& expected)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/serialization/CSVReader.h` (Private)


#### Free symbols / members of external scopes

- L14 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/serialization/CameraSerialization.h` (Private)


#### struct `RealityCaptureCamera`  
`template<class T> struct RealityCaptureCamera`  
_L32-41_
- desc: Reality Capture camera parameters as stored in XMP sidecar files.
- L33 _public member_ `Eigen::Matrix3<T> rotation;`
- L34 _public member_ `Eigen::Vector3<T> position;`
- L35 _public member_ `Eigen::VectorX<T> distortion;`
- L36 _public member_ `T focalLength35mm = T(0.0);`
- L37 _public member_ `T skew = T(0.0);`
- L38 _public member_ `T aspectRatio = T(0.0);`
- L39 _public member_ `T principalPointU = T(0.0);`
- L40 _public member_ `T principalPointV = T(0.0);`

#### Free symbols / members of external scopes

- L8 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> bool ReadMetaShapeCamerasFromJsonFile(const std::string& filename, std::vector<MetaShapeCamera<T>>& cameras);`
- L20 _prototype_ `template <class T> bool WriteMetaShapeCamerasToJsonFile(const std::string& filename, const std::vector<MetaShapeCamera<T>>& cameras);` — Writes camera calibration information into our own camera json format.
- L26 _prototype_ `template<class T> bool WriteMetaShapeCamerasToXmpFolder(const std::string& folderPath, const std::vector<MetaShapeCamera<T>>& cameras, int type);` — Writes camera calibration information into xmp format.
- L47 _prototype_ `template <class T> RealityCaptureCamera<T> ParseRealityCaptureXmp(const std::string& path);` — Parses a Reality Capture XMP sidecar file into a RealityCaptureCamera.
- L53 _prototype_ `template<typename T> MetaShapeCamera<T> RealityCaptureToMetashapeCamera(T width, T height, const RealityCaptureCamera<T>& rc);` — Converts a RealityCaptureCamera to a MetaShapeCamera given the image dimensions.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/serialization/EigenSerialization.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::io) /** * Serializes an Eigen matrix mat to json format in column major format. * Vectors are serialized to an array [values...] * Matrices are serialized to`
- L55 _function_ `template <class T, int R, int C> void FromJson(const JsonElement& j, Eigen::Matrix<T, R, C>& mat)` — deserializes a matrix from json format (see @ToJson)
- L110 _function_ `template <class MatrixType> MatrixType FromJson(const JsonElement& j)` — Serializes a matrix to json format.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/serialization/GeometrySerialization.h` (Private)


#### Free symbols / members of external scopes

- L9 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) /** * Serializes vertices to a json dictionary`
- L25 _function_ `template <class T> void GeometryFromJson(const JsonElement& j, Eigen::Matrix<T, 3, Eigen::Dynamic>& vertices)` — Deserializes vertices from a json dictionary { “vertices” : 3xN matrix }
- L39 _function_ `template <class T> void MultiGeometryFromJson(const JsonElement& j, std::map<std::string, Eigen::Matrix<T, 3, Eigen::Dynamic>>& geometryMap)` — Deserializes multiple geometries { “geometry” : { “name of geometry” : { “vertices” : 3xN matrix }, ... } }
- L51 _function_ `template <class T> void MultiGeometryFromJson(const JsonElement& j, std::vector<Eigen::Matrix<T, 3, Eigen::Dynamic>>& geometryMap)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/serialization/MeshSerialization.h` (Private)


#### Free symbols / members of external scopes

- L14 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) /** * Serializes a mesh into a json dictionary`
- L90 _function_ `template <class T> void MeshFromJson(const JsonElement& j, Mesh<T>& mesh)` — Deserializes a mesh from a json dictionary. @see MeshToJson

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/serialization/MetaShapeSerialization.h` (Private)


#### Free symbols / members of external scopes

- L8 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> bool ReadMetaShapeCameras(const std::string& filename, std::vector<MetaShapeCamera<T>>& cameras, const Affine<T, 3, 3>& metashapeToWorldTransform, const T metashapeToWorldScale);`
- L26 _prototype_ `template <class T> bool WriteMetaShapeCameras(const std::string& filename, const std::vector<MetaShapeCamera<T>>& cameras);` — Writes the metashape cameras to a cameras.xml file in Agisoft Metashape format. Writes out one sensor per camera even if two or more cameras have the same intrinsics and distortion parameters.
- L35 _prototype_ `template <class T> bool ReadStabilizationFile(const std::string& filename, Affine<T, 3, 3>& transform, T& scale);` — Reads our custom formst stabilization file that describes the transformation from metashape to world coordinates. The stabilisation file has the info as tx, ty, tz, rx, ry, rz, sx, sy, sz in Maya convention (rotations in degrees, xyz order, scale should be uniform). The transformation from metashape to world is therefore: P_world = EulerZ(rx) * EulerY(ry) * EulerX(rx) * sx * P_metashape + (tx, ty, tz)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/serialization/ObjFileFormat.h` (Private)


#### class `ObjFileReader`  
`template <class T> class ObjFileReader`  
_L22-38_
- L25 _public prototype_ `static bool readObj(const std::string& fileName, Mesh<T>& mesh, const std::shared_ptr<TITAN_NAMESPACE::TaskThreadPool>& taskThreadPool = TITAN_NAMESPACE::TaskThreadPool::GlobalInstance( false));`
- L28 _public prototype_ `static bool readObjFromString(const std::string& data, Mesh<T>& mesh, const std::shared_ptr<TITAN_NAMESPACE::TaskThreadPool>& taskThreadPool = TITAN_NAMESPACE::TaskThreadPool::GlobalInstance( false));`
- L37 _public prototype_ `static const char* ErrorTypeToString(ErrorType errorType);`

#### enum `ObjFileReader::ErrorType`  
`enum class ErrorType`  
_L32-35_
- L34 _public enumerator_ `NONE`
- L34 _public enumerator_ `NONE`
- L34 _public enumerator_ `NONE`
- L34 _public enumerator_ `NONE`
- L34 _public enumerator_ `NONE`
- L34 _public enumerator_ `NONE`

#### class `ObjFileWriter`  
`template <class T> class ObjFileWriter`  
_L42-46_
- L45 _public prototype_ `static void writeObj(const Mesh<T>& mesh, const std::string& filename, bool withTexture = true, bool withNormals = false);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/serialization/QsaSerialization.h` (Private)


#### Free symbols / members of external scopes

- L17 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> inline bool LoadQsa(const std::string& filename, std::map<int, std::map<std::string, T>>& valuesPerFrameAndControl)`
- L56 _function_ `template <class T> inline bool WriteQsa(const std::string& filename, const std::vector<std::string>& guiControlNames, const std::vector<Eigen::VectorX<T>>& guiControls, const std::vector<int>& frameNumbers, bool exportControlsThatAreAlwaysZero = true)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/solver/BoundedCoordinateDescentSolver.h` (Private)


#### struct `BoundedCoordinateDescentSolverSettings`  
`template <class T> struct BoundedCoordinateDescentSolverSettings`  
_L15-23_
- L17 _public member_ `int iterations = 10;`
- L18 _public member_ `int coordinateDescentIterations = 100;`
- L19 _public member_ `int maxLineSearchIterations = 10;`
- L20 _public member_ `T l1reg = 0;`
- L21 _public member_ `bool useSaturatedL1 = false;`
- L22 _public member_ `T saturatedL1_m = 2;`

#### class `BoundedCoordinateDescentSolver`  
`template <class T> class BoundedCoordinateDescentSolver`  
_L34-73_
- desc: Special coordinate descent solver with bounds and L1 regularization i.e. LASSO with box constraints. see also https://www.stat.cmu.edu/~ryantibs/convexopt-S15/lectures/22-coord-desc.pdf. https://www.jstatsoft.org/article/view/v033i01/v33i01.pdf Used to solve the function: min 1/2 || evaluationFunction() ||_2^2 + sum_i | l1Reg boundedVectorVariable_i |_1 (optionally using saturated L1)
- L44 _public prototype_ `static bool SolveCostFunction(const std::function<Cost<T>(Context<T>*)>& costFunction, Context<T>& context, const std::vector<BoundedVectorVariable<T>*>& boundedVectorVariables, const BoundedCoordinateDescentSolverSettings<T>& settings, TaskThreadPool* threadPool);` — Run the solve on the cost function with additional L1 regularization. @param costFunction            The least squares evaluation function. @param context                             The context that maps variables to the columns of the Jacobian of the evaluation function @param boundedVectorVariables  A set of vector variable for which the bounds are applied. The costFunction needs to use these bounded variables. @param settings				  The settings for the solver.
- L51 _public prototype_ `static T EvaluateCostFunction(const std::function<Cost<T>(Context<T>*)>& costFunction, const std::vector<BoundedVectorVariable<T>*>& boundedVectorVariables, const BoundedCoordinateDescentSolverSettings<T>& settings);` — Evaluate the total energy for the function: 1/2 || costFunction() ||_2^2 + sum_i | l1Reg boundedVectorVariable_i |_1 (optionally using saturated L1)
- L62 _public prototype_ `static bool Solve(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, Context<T>& context, const std::vector<BoundedVectorVariable<T>*>& boundedVectorVariables, const BoundedCoordinateDescentSolverSettings<T>& settings, TaskThreadPool* threadPool);` — Run the solve on the evaluation function with additional L1 regularization. @param evaluationFunction      The least squares evaluation function. @param context                             The context that maps variables to the columns of the Jacobian of the evaluation function @param boundedVectorVariables  A set of vector variable for which the bounds are applied. The evaluationFunction needs to use these bounded variables. @param settings				  The settings for the solver.
- L70 _public prototype_ `static T Evaluate(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, const std::vector<BoundedVectorVariable<T>*>& boundedVectorVariables, const BoundedCoordinateDescentSolverSettings<T>& settings);` — Evaluate the total energy for the function: 1/2 || evaluationFunction() ||_2^2 + sum_i | l1Reg boundedVectorVariable_i |_1 (optionally using saturated L1)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/solver/GaussNewtonSolver.h` (Private)


#### class `GaussNewtonSolver`  
`template <class T> class GaussNewtonSolver`  
_L17-81_
- L32 _public prototype_ `GaussNewtonSolver() = default;`
- L34 _public function_ `bool Solve(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, int iterations = 1, T reg = DiagonalRegularization<T>()) const`
- L40 _public function_ `bool Solve(const std::function<DiffData<T>(Context<T> *)> &evaluationFunction, const Settings &settings) const`
- L46 _public function_ `bool Solve(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, Context<T>& context, int iterations = 1, T reg = DiagonalRegularization<T>()) const`
- L55 _public prototype_ `bool Solve(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, Context<T>& context, const Settings& settings) const;`
- L57 _public function_ `bool Solve(const std::function<Cost<T>(Context<T>*)>& evaluationFunction, int iterations = 1, T reg = DiagonalRegularization<T>()) const`
- L63 _public function_ `bool Solve(const std::function<Cost<T>(Context<T>*)>& evaluationFunction, const Settings& settings) const`
- L69 _public function_ `bool Solve(const std::function<Cost<T>(Context<T>*)>& evaluationFunction, Context<T>& context, int iterations = 1, T reg = DiagonalRegularization<T>()) const`
- L78 _public prototype_ `bool Solve(const std::function<Cost<T>(Context<T>*)>& evaluationFunction, Context<T>& context, const Settings& settings) const;`

#### struct `GaussNewtonSolver::Settings`  
`struct Settings`  
_L20-30_
- L22 _public member_ `int iterations = 1;`
- L23 _public member_ `T reg = DiagonalRegularization<T>();`
- L24 _public member_ `int cgIterations = 200;` — the number of cg iterations (if pcg is used)
- L25 _public member_ `int maxLineSearchIterations = 10;`
- L26 _public member_ `T residualErrorStoppingCriterion = ResidualErrorStoppingCriterion<T>();`
- L27 _public member_ `T predictionReductionStoppingCriterion = PredictionReductionErrorStoppingCriterion<T>();`
- L28 _public member_ `bool optimizeForRectangularDenseJacobian = false;`
- L29 _public member_ `bool useDenseJtJAccumulation = true;`

#### Free symbols / members of external scopes

- L10 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> T DiagonalRegularization();`
- L13 _prototype_ `template <class T> T DiagonalRegularization();`
- L14 _prototype_ `template <class T> T DiagonalRegularization();`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/solver/LBFGSSolver.h` (Private)


#### class `LBFGSSolver`  
`template <class T> class LBFGSSolver`  
_L12-60_
- L15 _public function_ `LBFGSSolver()`
- L24 _public function_ `bool Solve(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, int iterations = 1) const`
- L31 _public prototype_ `bool Solve(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, Context<T>& context, int iterations = 1) const;`
- L36 _public function_ `void SetResidualErrorStoppingCriterion(T value)` — Setter methods for stopping criteria
- L37 _public function_ `void SetPredictionReductionStoppingCriterion(T value)`
- L38 _public function_ `void SetAbsDeltaStoppingCriterion(T value)`
- L39 _public function_ `void SetAbsDeltaStoppingWindow(int value)`
- L42 _public function_ `T GetResidualErrorStoppingCriterion() const` — Getter methods for stopping criteria
- L43 _public function_ `T GetPredictionReductionStoppingCriterion() const`
- L44 _public function_ `T GetAbsDeltaStoppingCriterion() const`
- L45 _public function_ `int GetAbsDeltaStoppingWindow() const`
- L49 _private member_ `int historySize = 50;` — LBFGS storage
- L50 _private member_ `mutable std::vector<Vector<T>> s;`
- L51 _private member_ `mutable std::vector<Vector<T>> y;`
- L52 _private member_ `mutable Vector<T> p;`
- L53 _private member_ `mutable Vector<T> a;`
- L56 _private member_ `T residualErrorStoppingCriterion = T(1e-8);` — Stopping criteria
- L57 _private member_ `T predictionReductionStoppingCriterion = T(1e-6);`
- L58 _private member_ `T absDeltaStoppingCriterion = T(0);` — disabled by default
- L59 _private member_ `int absDeltaStoppingWindow = 1;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/solver/LMSolver.h` (Private)


#### class `LMSolver`  
`template <class T> class LMSolver`  
_L12-33_
- L15 _public prototype_ `LMSolver() = default;`
- L19 _public function_ `bool Solve(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, int iterations = 1, const T epsilon1 = T(1e-8), const T epsilon2 = T(1e-8)) const` — epsilon1: stopping criterion for gradient norm epsilon2: stopping criterion for step size
- L28 _public prototype_ `bool Solve(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, Context<T>& context, const int iterations = 1, const T epsilon1 = T(1e-8), const T epsilon2 = T(1e-8)) const;` — epsilon1: stopping criterion for gradient norm epsilon2: stopping criterion for step size

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/solver/SimpleGaussNewtonSolver.h` (Private)


#### class `SimpleGaussNewtonSolver`  
`template <class T> class SimpleGaussNewtonSolver`  
_L13-40_
- L16 _public prototype_ `SimpleGaussNewtonSolver() = default;`
- L20 _public function_ `bool Solve(const std::function<Cost<T>(Context<T>*)>& costFunction, int iterations, const T regularization,` — epsilon1: stopping criterion for gradient norm epsilon2: stopping criterion for step size
- L33 _public prototype_ `bool Solve(const std::function<Cost<T>(Context<T>*)>& costFunction, Context<T>& context, const int iterations, const T regularization,` — epsilon1: stopping criterion for gradient norm epsilon2: stopping criterion for step size

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/utils/BilateralFilter.h` (Private)


#### class `BilateralFilter`  
`class BilateralFilter`  
_L9-22_
- L12 _public prototype_ `BilateralFilter() = delete;`
- L13 _public prototype_ `static std::vector<Eigen::VectorXf> CorrelatedFilter(const std::vector<Eigen::VectorXf>& InUnfilteredControls, const float& InDomainStdDev, const float& InRangeStdDev);`
- L16 _public prototype_ `static std::vector<Eigen::VectorXf> IndependentFilter(const std::vector<Eigen::VectorXf>& InUnfilteredControls, const float& InDomainStdDev, const float& InRangeStdDev);`
- L21 _private prototype_ `static std::vector<float> CreateGaussianFilter(const long long& half_width, const float& InDomainStdDev);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/utils/Configuration.h` (Private)


#### class `Configuration`  
`class Configuration`  
_L16-63_
- L18 _public prototype_ `Configuration(const std::string& configName, const std::vector<std::pair<std::string, ConfigurationParameter> >& configParameters);`
- L21 _public prototype_ `void Set(const Configuration& other, bool ignoreUnknownKeys = false);`
- L23 _public prototype_ `std::map<std::string, std::string> StringConfiguration() const;`
- L24 _public prototype_ `void SetStringConfiguration(const std::map<std::string, std::string>& config, bool ignoreUnknownKeys = false);`
- L26 _public prototype_ `bool HasParameter(const std::string& name) const;`
- L28 _public prototype_ `const ConfigurationParameter& operator[](const std::string& name) const;`
- L29 _public prototype_ `ConfigurationParameter& operator[](const std::string& name);`
- L31 _public prototype_ `const std::map<std::string, ConfigurationParameter>& Parameters() const;`
- L32 _public prototype_ `std::map<std::string, ConfigurationParameter>& Parameters();`
- L34 _public prototype_ `const std::string& Name() const;`
- L36 _public prototype_ `void AddParameter(const std::string& key, ConfigurationParameter&& value);`
- L37 _public prototype_ `void AddConfiguration(const std::string& key, const Configuration& config);`
- L38 _public prototype_ `void AddConfiguration(const Configuration& config);`
- L39 _public prototype_ `void AddConfigurations(const std::vector<Configuration>& configs);`
- L41 _public prototype_ `JsonElement ToJson() const;`
- L43 _public prototype_ `void FromJson(const JsonElement& json, std::vector<std::string>& unspecifiedKeys, std::vector<std::string>& unknownKeys);`
- L48 _public function_ `const std::vector<std::string>& ParameterOrder()` — @returns the order in which the parameters were added to the configuration
- L53 _private prototype_ `void FromJson(const JsonElement& json, std::vector<std::string>& unspecifiedKeys, std::vector<std::string>& unknownKeys, const std::string& prefix);`
- L59 _private member_ `std::string m_configName;`
- L60 _private member_ `std::map<std::string, ConfigurationParameter> m_configParameters;`
- L62 _private member_ `std::vector<std::string> m_paramOrder;` — keep the order of the keys as they have been added

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nls/include/nls/utils/ConfigurationParameter.h` (Private)


#### class `ConfigurationParameter`  
`class ConfigurationParameter`  
_L81-255_
- L88 _public function_ `ConfigurationParameter() : m_value(int(0)), m_rangeStart(int(0)), m_rangeEnd(int(0))`
- L96 _public function_ `explicit ConfigurationParameter(bool value) : m_value(value), m_rangeStart(int(0)), m_rangeEnd(int(0))`
- L99 _public function_ `explicit ConfigurationParameter(int value, int rangeStart = 0, int rangeEnd = 1) : m_value(value), m_rangeStart(rangeStart), m_rangeEnd(rangeEnd)`
- L102 _public function_ `explicit ConfigurationParameter(float value, float rangeStart = 0.0f, float rangeEnd = 1.0f) : m_value(value), m_rangeStart(rangeStart), m_rangeEnd(rangeEnd)`
- L106 _public function_ `explicit ConfigurationParameter(double value, double rangeStart = 0.0, double rangeEnd = 1.0) : m_value(value), m_rangeStart(rangeStart), m_rangeEnd( rangeEnd)`
- L110 _public function_ `explicit ConfigurationParameter(const std::string& value) : m_value(value), m_rangeStart(int(0)), m_rangeEnd(int(0))`
- L113 _public function_ `explicit ConfigurationParameter(const char* value) : ConfigurationParameter(std::string(value))`
- L116 _public function_ `explicit ConfigurationParameter(Configuration value) : m_value(value), m_rangeStart(int(0)), m_rangeEnd(int(0))`
- L119 _public function_ `void Set(const std::string& value)`
- L161 _public function_ `void Set(float value)`
- L168 _public function_ `void Set(double value)`
- L175 _public function_ `void Set(int value)`
- L181 _public function_ `void Set(bool value)`
- L188 _public function_ `template <class T> const T& Value() const`
- L194 _public function_ `template <class T> T& Value()`
- L210 _public function_ `template <class T> ConfigurationParameter& operator=(const T& v)`
- L213 _public function_ `std::string AsString() const` — @returns String representation of the underlying value. It does not support the Configuration type.
- L216 _public function_ `template <class T> std::pair<T, T> Range() const`
- L219 _public function_ `template <class T> bool IsType() const`
- L221 _public function_ `ConfigurationParameter& operator[](const std::string& name)`
- L227 _public function_ `const ConfigurationParameter& operator[](const std::string& name) const`
- L233 _public function_ `ConfigurationParameter& operator[](const char* name)`
- L239 _public function_ `const ConfigurationParameter& operator[](const char* name) const`
- L247 _private member_ `std::string m_name;` — the parameter name
- L250 _private member_ `detail::ConfigurationParameterVariant m_value;` — the parameter value
- L253 _private member_ `std::variant<int, float, double> m_rangeStart;` — the range of the parameter value in [m_rangeStart, m_rangeEnd]. Note that the end of the range is included.
- L254 _private member_ `std::variant<int, float, double> m_rangeEnd;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace detail`
- L18 _typedef_ `typedef std::variant<bool, int, float, double, std::string, Configuration> ConfigurationParameterVariant;` (scope `detail`)
- L20 _function_ `template <typename T> inline bool IsType(const ConfigurationParameterVariant& value)` (scope `detail`)
- L22 _function_ `template <typename T> inline T& Value(ConfigurationParameterVariant& value)` (scope `detail`)
- L32 _function_ `template <typename T> inline const T& Value(const ConfigurationParameterVariant& value)` (scope `detail`)
- L42 _function_ `inline std::string AsString(const ConfigurationParameterVariant& value)` (scope `detail`)
- L44 _function_ `return std::visit([](auto&& arg) { using T = std::decay_t<decltype(arg)>; if constexpr (std::is_same_v<T, int> ) { return std::to_string(arg); } else if constexpr (std::is_same_v<T, float> ) { return std::to_string(arg); } else if constexpr (std::is_same_v<T, double> ) { return std::to_string(arg); } else if constexpr (std::is_same_v<T, bool> ) { return std::string(arg ? "True" : "False"); } else if constexpr (std::is_same_v<T, std::string> ) { return arg; } else if constexpr (std::is_same_v<T, Configuration> ) { static_assert("cannot retrieve sub configuration as string"); return std::string(); } else { static_assert(TITAN_NAMESPACE::always_false<T>::value, "non-exhaustive visitor!"); return std::string(); } }, value);` (scope `detail::AsString`)
- L45 _typedef_ `using T = std::decay_t<decltype(arg)>;` (scope `detail::AsString::__anon75beb8000102`)
- L190 _typedef_ `using base_type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;` (scope `ConfigurationParameter::Value`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/AssetGeneration.h` (Private)


#### class `AssetGenerationConfiguration`  
`template <class T> class AssetGenerationConfiguration`  
_L29-73_
- desc: Representation of a configuration representing how Asset Generation is performed
- L33 _public prototype_ `AssetGenerationConfiguration() = default;`
- L36 _public prototype_ `bool Load(const std::string& filenameOrData);` — Load data from either file or the data directly.
- L48 _private prototype_ `bool LoadJson(const std::string& jsonString, const std::string& baseDir);`
- L50 _private member_ `static constexpr int32_t m_version = 1;`
- L52 _private member_ `std::string m_archetypePath;`
- L54 _private member_ `std::string m_salivaDriverMeshName;`
- L55 _private member_ `std::string m_salivaMeshName;`
- L56 _private member_ `WrapDeformerParams<T> m_salivaWrapDeformerParams;`
- L58 _private member_ `std::string m_cartilageDriverMeshName;`
- L59 _private member_ `std::string m_cartilageMeshName;`
- L60 _private member_ `WrapDeformerParams<T> m_cartilageWrapDeformerParams;`
- L62 _private member_ `std::string m_eyelashesDriverMeshName;`
- L63 _private member_ `std::string m_eyelashesMeshName;`
- L64 _private member_ `EyelashesGeneratorParams<T> m_eyelashesGeneratorParams;`
- L66 _private member_ `std::string m_headMeshName;`
- L67 _private member_ `std::string m_eyeLeftMeshName;`
- L68 _private member_ `std::string m_eyeRightMeshName;`
- L69 _private member_ `std::string m_eyeEdgeMeshName;`
- L70 _private member_ `std::string m_eyeshellMeshName;`
- L71 _private member_ `EyeAssetGeneratorParams<T> m_eyeEdgeGeneratorParams;`
- L72 _private member_ `EyeAssetGeneratorParams<T> m_eyeshellGeneratorParams;`

#### class `AssetGeneration`  
`template <class T> class AssetGeneration`  
_L90-122_
- desc: Representation of a class for performing Asset generation using a mixture of vertex 'snapping' wrap deformers and optimization
- L93 _public prototype_ `AssetGeneration();`
- L96 _public prototype_ `void SetThreadPool(const std::shared_ptr<TITAN_NAMESPACE::TaskThreadPool>& taskThreadPool);` — Set a threadpool for parallelization of  asset generation tasks (if not set, the default global threadpool will be used)
- L99 _public prototype_ `bool Init(const AssetGenerationConfiguration<T>& config);` — Initialize the asset generation object from a configuration
- L102 _public prototype_ `bool Apply(const std::map<std::string, Eigen::Matrix<T, 3, -1>>& lod0HeadEyeTeethMeshVertices, std::map<std::string, Eigen::Matrix<T, 3, -1>>& lod0AssetVertices) const;` — Perform asset generation once initialized given head, teeth and eye meshes (which must be triangulated) and return the results as a map of mesh name to asset vertices
- L105 _public prototype_ `bool LoadModelBinary(const std::string& assetGenerationModelFile);` — load from a binary asset generation model filename
- L108 _public prototype_ `bool SaveModelBinary(const std::string& assetGenerationModelFile) const;` — save to a binary asset generation model filename
- L111 _private member_ `static constexpr int32_t m_version = 1;`
- L113 _private member_ `AssetGenerationConfiguration<T> m_config;`
- L114 _private member_ `WrapDeformer<T> m_salivaWrapDeformer;`
- L115 _private member_ `WrapDeformer<T> m_cartilageWrapDeformer;`
- L116 _private member_ `EyelashesGenerator<T> m_eyelashesGenerator;`
- L117 _private member_ `EyeAssetGenerator<T> m_eyeEdgeGenerator;`
- L118 _private member_ `EyeAssetGenerator<T> m_eyeshellGenerator;`
- L119 _private member_ `std::map<std::string, std::shared_ptr<const Mesh<T>>> m_allMeshes;`
- L121 _private member_ `std::shared_ptr<TITAN_NAMESPACE::TaskThreadPool> m_taskThreadPool;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace trio`
- L77 _prototype_ `template <class T> bool ToBinaryFile(FILE* pFile, const AssetGenerationConfiguration<T>& config);`
- L80 _prototype_ `template <class T> bool FromBinaryFile(FILE* pFile, AssetGenerationConfiguration<T>& config);`
- L83 _prototype_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, AssetGenerationConfiguration<T>& config);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/AssetGenerationWrapper.h` (Private)


#### class `AssetGenerationWrapper`  
`template <class T> class AssetGenerationWrapper`  
_L11-22_
- L14 _public prototype_ `AssetGenerationWrapper();`
- L16 _public prototype_ `bool LoadModelBinary(const std::string &path);`
- L18 _public prototype_ `std::string Apply(const std::string &lod0HeadEyeTeethMeshVerticesJson) const;`
- L21 _private member_ `std::unique_ptr<epic::nls::AssetGeneration<T>> m_AssetGeneration;`

#### class `LodGenerationWrapper`  
`template <class T> class LodGenerationWrapper`  
_L26-37_
- L29 _public prototype_ `LodGenerationWrapper();`
- L31 _public prototype_ `bool LoadModelBinary(const std::string &path, const int &option = 0);`
- L33 _public prototype_ `std::string Apply(const std::string &lod0HeadEyeTeethMeshVerticesJson) const;`
- L36 _private member_ `std::unique_ptr<epic::nls::LodGeneration<T>> m_LodGeneration;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/CollisionConstraints.h` (Private)


#### class `CollisionConstraints`  
`template <class T> class CollisionConstraints`  
_L19-70_
- desc: Class to evaluate generic collision constraints between two sets of vertices (from a single mesh or two different meshes).
- L43 _public prototype_ `CollisionConstraints() = default;`
- L44 _public prototype_ `~CollisionConstraints() = default;`
- L45 _public prototype_ `CollisionConstraints(CollisionConstraints&&) = default;`
- L46 _public prototype_ `CollisionConstraints(CollisionConstraints&) = delete;`
- L47 _public prototype_ `CollisionConstraints& operator=(CollisionConstraints&&) = default;`
- L48 _public prototype_ `CollisionConstraints& operator=(const CollisionConstraints&) = delete;`
- L51 _public prototype_ `void SetSourceTopology(const Mesh<T>& mesh, const std::vector<int>& srcMask);` — Set the mask for the source mesh
- L54 _public prototype_ `void SetTargetTopology(const Mesh<T>& mesh, const std::vector<int>& targetMask);` — Set the mask for the target mesh (can be the same mesh as the source mesh)
- L56 _public prototype_ `std::shared_ptr<const Data> CalculateCollisions(const Mesh<T>& srcMesh, const Mesh<T>& targetMesh) const;`
- L59 _public prototype_ `std::shared_ptr<const Data> CalculateCollisions(const Eigen::Matrix<T, 3, -1>& srcVertices, const Eigen::Matrix<T, 3, -1>& targetVertices) const;` — Calculate collision points and the collision normal (calculates the required vertex normals on the fly)
- L62 _public prototype_ `std::shared_ptr<const Data> CalculateCollisions(const Eigen::Matrix<T, 3, -1>& srcVertices, const Eigen::Matrix<T, 3, -1>& srcNormals, const Eigen::Matrix<T, 3, -1>& targetVertices, const Eigen::Matrix<T, 3, -1>& targetNormals) const;` — Calculate collision points and the collision normal
- L66 _protected member_ `std::vector<int> m_srcMask;`
- L67 _protected member_ `Eigen::Matrix<int, 3, -1> m_srcTriangles;`
- L68 _protected member_ `std::vector<int> m_targetMask;`
- L69 _protected member_ `Eigen::Matrix<int, 3, -1> m_targetTriangles;`

#### struct `CollisionConstraints::Data`  
`struct Data`  
_L22-40_
- L24 _public member_ `std::vector<int> srcCollisionIDs;`
- L25 _public member_ `std::vector<BarycentricCoordinates<T, 3>> targetCollisionBCs;`
- L26 _public member_ `std::vector<Eigen::Vector3<T>> targetNormals;`
- L28 _public function_ `void Clear()`
- L35 _public function_ `int NumCollisions() const`
- L38 _public prototype_ `DiffData<T> Evaluate(const DiffDataMatrix<T, 3, -1>& srcVertices, const DiffDataMatrix<T, 3, -1>& targetVertices) const;` — Evaluate collision constraints

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/CompareDNAs.h` (Private)


#### Free symbols / members of external scopes

- L9 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) bool CompareDNAs(dna::BinaryStreamReader* goldDataReader, dna::BinaryStreamReader* outputReader, float positionTolerance = 0.002f, float angleTolerance = 0.001f, float weightTolerance = 0.002f, bool bCompareSkinningWeights = true);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/DMTNormalizationConstraint.h` (Private)


#### class `DMTNormalizationConstraint`  
`template <class T> class DMTNormalizationConstraint`  
_L11-46_
- L14 _public function_ `DiffData<T> EvaluateRegionsSumEquals(const DiffData<T>& vec, int numRegions)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/DMTSymmetryConstraint.h` (Private)


#### class `DMTSymmetryConstraint`  
`template <class T> class DMTSymmetryConstraint`  
_L10-49_
- L13 _public function_ `DiffData<T> EvaluateSymmetry(const DiffData<T>& vec, int numRegions, std::vector<std::pair<int, int>> vecPair)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/DepthmapConstraints.h` (Private)


#### class `DepthmapConstraints`  
`class DepthmapConstraints`  
_L13-60_
- desc: Class to evaluate ICP depthmap correspondences (point 2 surface)
- L29 _public function_ `DepthmapConstraints(const Camera<float>& camera, const Eigen::Matrix<float, 4, -1>& depthAndNormals) : m_camera(camera), m_depthAndNormals(depthAndNormals)`
- L32 _public function_ `void SetVertexMask(const std::vector<int>& vertexMask)`
- L33 _public function_ `const std::vector<int>& VertexMask() const`
- L35 _public prototype_ `void SetupDepthConstraints(const Eigen::Transform<float, 3, Eigen::Affine>& rigidTransform, const Eigen::Matrix<float, 3, -1>& vertices, const Eigen::Matrix<float, 3, -1>& normals, VertexConstraints<float, 1, 1>& vertexConstraints);`
- L41 _public prototype_ `void ClearDynamicDistanceThreshold(float initialThreshold = 1e6f);` — Clear the dynamic distance threshold which is dynamically adapted in @see SetupDepthConstraints().
- L42 _public prototype_ `void SetDynamicDistanceThreshold(float threshold);`
- L45 _public prototype_ `void SetDynamicActorDistanceThresholds(float minimumActorDistance, float maximumActorDistance, bool useDynamicActorDistanceWeight);` — Set the dynamic actor distance threshold which is dynamically adapted in @see SetupDepthConstraints().
- L47 _public function_ `const Options& GetOptions() const`
- L48 _public function_ `Options& GetOptions()`
- L50 _public function_ `const Camera<float>& GetCamera() const`
- L51 _public function_ `const Eigen::Matrix<float, 4, -1>& DepthAndNormals() const`
- L54 _private member_ `const Camera<float>& m_camera;`
- L55 _private member_ `const Eigen::Matrix<float, 4, -1>& m_depthAndNormals;`
- L56 _private member_ `std::vector<int> m_vertexMask;`
- L57 _private member_ `bool m_calculateDynamicDistanceThreshold = true;`
- L58 _private member_ `float m_dynamicDistanceThreshold = 1e6f;`
- L59 _private member_ `Options m_options;`

#### struct `DepthmapConstraints::Options`  
`struct Options`  
_L16-26_
- L18 _public member_ `float geometryWeight = 1.0f;`
- L19 _public member_ `float minimumGeometryWeight = 0.01f;`
- L20 _public member_ `float maximumGeometryWeight = 1.0f;`
- L21 _public member_ `float normalIncompatibilityThreshold = 0.5f;`
- L22 _public member_ `float minimumDistanceThresholdSquared = 4.0f;`
- L23 _public member_ `float minimumDepthRange = 15.0f;`
- L24 _public member_ `float maximumDepthRange = 30.0f;`
- L25 _public member_ `bool useDynamicActorDistanceWeight = false;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/DmtModel.h` (Private)


#### class `DmtModel`  
`template <class T> class DmtModel`  
_L14-63_
- L27 _public prototype_ `DmtModel(std::shared_ptr<const PatchBlendModel<T>> patchBlendModel, const std::vector<int>& patchModelSymmetries, const std::shared_ptr<TaskThreadPool>& taskThreadPool);`
- L31 _public prototype_ `std::shared_ptr<DmtModel> Clone() const;`
- L33 _public prototype_ `void Init(const std::vector<int>& vertexIndices, int vertexIndexOffset, bool singleRegionPerLandmark, T regularizationWeight);`
- L36 _public prototype_ `void ForwardDmtDelta(typename PatchBlendModel<T>::State& state, int landmarkIndex, const Eigen::Vector3<T>& delta, bool symmetric, float pcaThreshold) const;` — @solve for delta pca parameters based on landmark delta. The landmark delta should be in model space (not canonical)
- L39 _public prototype_ `void ForwardDmtDelta(typename PatchBlendModel<T>::State& state, int landmarkIndex, const Eigen::Vector3<T>& delta, const SolveOptions& solveOptions) const;` — @solve for delta pca parameters based on landmark delta. The landmark delta should be in model space (not canonical)
- L42 _public function_ `float GetRegularizationWeight() const` — @returns the regularization weight that we used during Init
- L46 _private prototype_ `void CreateForwardSolveMatrices(std::shared_ptr<Data> modelData, T regularizationWeight);` — Create forward solve matrices i.e. min || A * x - markers || + reg || x ||
- L50 _private member_ `std::shared_ptr<const PatchBlendModel<T>> m_patchBlendModel;` — patch blend model for the entire head (joints + assets)
- L53 _private member_ `std::shared_ptr<const std::vector<int>> m_patchModelSymmetries;` — symmetries for the entrie head (joints + assets)
- L56 _private member_ `std::shared_ptr<const Data> m_modelData;` — the linear dmt model
- L59 _private member_ `std::shared_ptr<TaskThreadPool> m_taskThreadPool;` — thread pool for parallelization
- L62 _private member_ `T m_regularizationWeight {};` — regularization weight that was used

#### struct `DmtModel::SolveOptions`  
`struct SolveOptions`  
_L19-24_
- L21 _public member_ `bool symmetric { true };`
- L22 _public member_ `float pcaThreshold { T(3) };`
- L23 _public member_ `bool markerCompensate { false };`

#### struct `DmtModel::Data`  
`template <class T> struct DmtModel<T>::Data`  
_L66-97_
- L69 _public member_ `int numParameters;` — number of pca parameters
- L72 _public member_ `Eigen::Matrix<T, 3, -1> base;` — mean shape of the landmarks
- L75 _public member_ `std::vector<int> vertexIndices;` — The indices in patchBlendModel the marker correspond to
- L78 _public member_ `std::vector<int> symmetries;` — symmetry mapping with indices into @see vertexIndices
- L81 _public member_ `std::vector<std::vector<int>> regionMarkerIds;` — for each region which markers that are being used (index into @p base)
- L84 _public member_ `std::vector<std::vector<int>> regionVertexIds;` — for each region marker, to which region vertex it maps
- L87 _public member_ `std::vector<Eigen::MatrixX<T>> forwardSolveMatrices;` — forward dmt solve matrices (solves from marker(deltas) to pca coefficients
- L90 _public function_ `bool HasSymmetry(int idx) const` — whether landmark index @p idx has a symmetric mapping
- L93 _public function_ `int GetSymmetricIndex(int idx) const` — @returns the symmetric landmark index of @p idx
- L96 _public function_ `bool IsSelfSymmetric(int idx) const` — @returns True if landmark index @p idx is self-symmetric

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/ExpressionFitting.h` (Private)


#### struct `SculptFittingParams`  
`template <class T> struct SculptFittingParams`  
_L12-28_
- L15 _public member_ `T modelRegularization { T(0.2) };` — @regularization
- L18 _public member_ `T p2pWeight { T(1) };` — @point-to-point weight
- L21 _public member_ `bool fitRigid = false;` — @whether to optimize global rigid transform
- L24 _public member_ `bool fitBlendshapes = true;` — @whether to use blendshapes in the optimization
- L27 _public member_ `int numIterations { 3 };` — @number of iterations

#### struct `SculptFittingState`  
`template <class T> struct SculptFittingState`  
_L31-35_
- L33 _public member_ `Affine<T, 3, 3> toTargetTransform;`
- L34 _public member_ `Eigen::VectorX<T> pcaParameters;`

#### class `SculptFittingOptimization`  
`template <class T> class SculptFittingOptimization`  
_L38-119_
- L43 _public prototype_ `static SculptFittingState<T> RegisterPose(const Eigen::Matrix<T, 3, -1>& targetVertices, const SculptFittingState<T>& previousState, const std::shared_ptr<RigGeometry<T>>& rigGeometry, const std::shared_ptr<IdentityBlendModel<T>> model, const SculptFittingParams<T>& params, const Eigen::VectorX<T>& mask);` — @solve to target vertices
- L51 _public prototype_ `static SculptFittingState<T> RegisterPose(const std::map<std::string, Eigen::Matrix<T, 3, -1>>& targetVertices, const std::map<std::string, Eigen::VectorX<T>>& masks, const std::map<std::string, std::pair<int, int>>& targetToModelMapping, const SculptFittingState<T>& previousState, const std::shared_ptr<RigGeometry<T>>& rigGeometry, const std::shared_ptr<IdentityBlendModel<T>> model, const SculptFittingParams<T>& params);` — @solve to target vertices
- L60 _public prototype_ `static SculptFittingState<T> RegisterPoseProjectToLinear(const std::map<std::string, Eigen::Matrix<T, 3, -1>> &targetVertices, const std::map<std::string, std::pair<int, int>> &targetToModelMapping, const SculptFittingState<T> &previousState, const std::shared_ptr<RigGeometry<T>> &rigGeometry, const std::shared_ptr<IdentityBlendModel<T>> model, const Eigen::Matrix<T, -1, -1> &linearModel, const Eigen::Vector<T, -1> &linearModelMean, const SculptFittingParams<T> &params);` — @solve to target vertices, while projecting the parameters to the linear model defined with
- L70 _public prototype_ `static std::vector<SculptFittingState<T>> RegisterMultiplePosesProjectToLinear( const std::vector<std::map<std::string, Eigen::Matrix<T, 3, -1>>> &targetVertices, const std::vector<std::map<std::string, std::pair<int, int>>> &targetToModelMapping, const std::vector<SculptFittingState<T>> &previousStates, const std::shared_ptr<RigGeometry<T>> &rigGeometry, const std::vector<std::shared_ptr<IdentityBlendModel<T>>> models, const std::vector<Eigen::Matrix<T, -1, -1>> &linearModels, const std::vector<Eigen::Vector<T, -1>> &linearModelsMeans, const SculptFittingParams<T> &params);` — @solve to target vertices, for multiple expressions, while projecting the parameters to the linear model
- L80 _public prototype_ `static std::vector<SculptFittingState<T>> RegisterMultiplePosesPerRegionProjectToLinear( const std::vector<std::map<std::string, Eigen::Matrix<T, 3, -1>>> &targetVertices, const std::vector<std::map<std::string, std::pair<int, int>>> &targetToModelMapping, const std::vector<SculptFittingState<T>> &previousStates, const std::shared_ptr<RigGeometry<T>> &rigGeometry, const std::vector<std::shared_ptr<IdentityBlendModel<T>>> models, const std::vector<std::vector<Eigen::Matrix<T, -1, -1>>> &linearModels, const std::vector<std::vector<Eigen::Vector<T, -1>>> &linearModelsMeans, const std::vector<std::map<std::string, Eigen::Matrix<T, -1, 1>>> &inputMasks, const SculptFittingParams<T> &params);`
- L92 _public prototype_ `static SculptFittingState<T> RegisterPoseJointsOnly(const std::map<std::string, Eigen::Matrix<T, 3, -1>> &targetVertices, const std::map<std::string, std::pair<int, int>> &targetToModelMapping, const SculptFittingState<T> &previousState, const std::shared_ptr<RigGeometry<T>> &rigGeometry, const std::shared_ptr<IdentityBlendModel<T>> model, const SculptFittingParams<T> &params);` — @solve to target vertices only with joints
- L100 _public prototype_ `static SculptFittingState<T> RegisterPoseJointsOnlyProjectToLinear(const std::map<std::string, Eigen::Matrix<T, 3, -1>> &targetVertices, const std::map<std::string, std::pair<int, int>> &targetToModelMapping, const SculptFittingState<T> &previousState, const std::shared_ptr<RigGeometry<T>> &rigGeometry, const std::shared_ptr<IdentityBlendModel<T>> model, const Eigen::Matrix<T, -1, -1> &linearModel, const Eigen::Vector<T, -1> &linearModelMean, const SculptFittingParams<T> &params);` — @solve to target vertices only with joints, while projecting the parameters to the linear model defined with
- L110 _public prototype_ `static std::vector<SculptFittingState<T>> RegisterMultiplePosesJointsOnlyProjectToLinear( const std::vector<std::map<std::string, Eigen::Matrix<T, 3, -1>>> &targetVertices, const std::vector<std::map<std::string, std::pair<int, int>>> &targetToModelMapping, const std::vector<SculptFittingState<T>> &previousStates, const std::shared_ptr<RigGeometry<T>> &rigGeometry, const std::shared_ptr<IdentityBlendModel<T>> jointsModel, const std::vector<Eigen::Matrix<T, -1, -1>> &linearModels, const std::vector<Eigen::Vector<T, -1>> &linearModelsMeans, const SculptFittingParams<T> &params);` — @solve to target vertices only with joints, for multiple expressions, while projecting the parameters to the linear model defined with

#### struct `ExpressionParametersFittingParams`  
`template <class T> struct ExpressionParametersFittingParams`  
_L122-132_
- L125 _public member_ `T modelRegularization { T(1) };` — @regularization
- L128 _public member_ `T geometryWeight { T(10) };` — @point-to-point weight
- L131 _public member_ `int numIterations { 5 };` — @number of iterations

#### class `ExpressionParametersFittingOptimization`  
`template <class T> class ExpressionParametersFittingOptimization`  
_L136-145_
- L140 _public prototype_ `static Eigen::VectorX<T> RegisterPose(const Eigen::Matrix<T, 3, -1>& targetJointDeltas, const Eigen::Matrix<T, 3, -1>& targetBlendshapeDeltas, const Eigen::VectorX<T>& previousParams, const std::shared_ptr<IdentityBlendModel<T>>& model, const ExpressionParametersFittingParams<T>& params);` — @solve to target joint deltas and blendshape deltas

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/EyeAssetGenerator.h` (Private)


#### struct `EyeAssetGeneratorParams`  
`template <class T> struct EyeAssetGeneratorParams`  
_L20-40_
- desc: Parameters for eyelashes generation
- L22 _public member_ `static constexpr int32_t version = 2;`
- L24 _public member_ `WrapDeformerParams<T> wrapDeformerParams;`
- L25 _public member_ `T eyeballNormalDisplacement = static_cast<T>(0.01);`
- L26 _public member_ `T faceLockDistanceThreshold = static_cast<T>(0.1);`
- L27 _public member_ `T eyeDistanceThreshold = static_cast<T>(0.2);`
- L28 _public member_ `int numSolverIterations = 2;`
- L29 _public member_ `int numSolverCGIterations = 20;`
- L30 _public member_ `int leftRightSplitIndex = 0;`
- L31 _public member_ `bool optimizePose = true;`
- L32 _public member_ `Eigen::VectorXi wrapDeformOnlyVertexIndices;`
- L33 _public member_ `T deformationModelVertexWeight = 1.0;`
- L34 _public member_ `T pointToPointConstraintWeight = 2.0;`
- L35 _public member_ `T eyeConstraintWeight = 5.0;`
- L36 _public member_ `Eigen::VectorXi caruncleVertexIndices;`
- L37 _public member_ `T caruncleMultiplier = 0.5;`
- L39 _public prototype_ `bool ReadJson(const JsonElement& element);`

#### class `EyeAssetGenerator`  
`template <class T> class EyeAssetGenerator`  
_L48-116_
- desc: A class which can generate an eye asset (either eyeshell or eyeEdge) from a head mesh, left and right eye meshes, and various parameters. It uses a combination of wrapDeformers plus optimization to ensure that the eye asset does not intersect with the eye mesh and also that it is close in shape to the archetype eye asset shape.
- L51 _public prototype_ `EyeAssetGenerator();`
- L57 _public prototype_ `void SetMeshes(const std::shared_ptr<const Mesh<T>>& headMesh, const std::shared_ptr<const Mesh<T>>& eyeLeftMesh, const std::shared_ptr<const Mesh<T>>& eyeRightMesh, const std::shared_ptr<const Mesh<T>>& eyeAssetMesh);` — set the archetype (LOD0) head mesh, left and right eye meshes, asset mesh. Note that this does NOT re-initialize the other internals of the class and can be used as a means to (re)set the meshes if they have been stored separately from the class
- L61 _public prototype_ `void SetThreadPool(const std::shared_ptr<TITAN_NAMESPACE::TaskThreadPool>& taskThreadPool);` — Set a threadpool for parallelization of eye asset generation tasks (if not set, the default global threadpool will be used)
- L65 _public prototype_ `void Init(const std::shared_ptr<const Mesh<T>>& headMesh, const std::shared_ptr<const Mesh<T>>& eyeLeftMesh, const std::shared_ptr<const Mesh<T>>& eyeRightMesh, const std::shared_ptr<const Mesh<T>>& eyeAssetMesh, const EyeAssetGeneratorParams<T>& params);` — initialize the generator from the archetype (LOD0) head mesh, left and right eye meshes, asset mesh, plus parameters. headMesh and eye asset mesh must be triangulated
- L69 _public prototype_ `void Apply(const Eigen::Matrix<T, 3, -1>& deformedHeadMeshVertices, const Eigen::Matrix<T, 3, -1>& deformedEyeLeftMeshVertices, const Eigen::Matrix<T, 3, -1>& deformedEyeRightMeshVertices, Eigen::Matrix<T, 3, -1>& deformedEyeAssetMeshVertices) const;` — apply the generator to the driver mesh vertices to give deformedEyeAssetMeshVertices as a result; deformedHeadMeshVertices, deformedEyeLeftMeshVertices, deformedEyeRightMeshVertices, deformedCartilageMeshVertices  must contain the correct number of vertices
- L76 _public prototype_ `static void FixCaruncleIntersection(const EyeAssetGenerator<T>& eyeshellAsset, const EyeAssetGenerator<T>& eyeEdgeAsset, Eigen::Matrix<T, 3, -1>& deformedEyeshellAssetMeshVertices, Eigen::Matrix<T, 3, -1>& deformedEyeEdgeAssetMeshVertices);` — simple heuristic helper function which helps fix any intersections between the caruncle regions of an eyeshell and an eyeEdge asset. this is not perfect but is very simple and uses simple user-defined vertex correspondence and vertex normals for the eyeshell asset to define whether the meshes are overlapping
- L88 _private prototype_ `void InitializeAsset();`
- L89 _private prototype_ `void ApplyAsset(const Eigen::Matrix<T, 3, -1>& deformedHeadMeshVertices, const Eigen::Matrix<T, 3, -1>& deformedEyeLeftMeshVertices, const Eigen::Matrix<T, 3, -1>& deformedEyeRightMeshVertices, Eigen::Matrix<T, 3, -1>& deformedAssetVertices) const;`
- L91 _private prototype_ `bool CheckAssetVertexIndices(const Eigen::VectorXi& vertexIndices) const;`
- L93 _private member_ `static constexpr int32_t m_version = 1;`
- L94 _private member_ `std::shared_ptr<const Mesh<T>> m_headMesh;`
- L95 _private member_ `std::shared_ptr<const Mesh<T>> m_eyeRightMesh;`
- L96 _private member_ `std::shared_ptr<const Mesh<T>> m_eyeLeftMesh;`
- L97 _private member_ `std::shared_ptr<const Mesh<T>> m_eyeAssetMesh;`
- L99 _private member_ `Eigen::VectorX<T> m_eyeLeftWeights;`
- L100 _private member_ `Eigen::VectorX<T> m_eyeRightWeights;`
- L101 _private member_ `WrapDeformer<T> m_wrapDeformer;`
- L102 _private member_ `EyeAssetGeneratorParams<T> m_params;`
- L104 _private member_ `Eigen::VectorXi m_rightAssetVertexIndices;`
- L105 _private member_ `Eigen::Matrix<T, 3, -1> m_rightAssetVertices;`
- L106 _private member_ `Eigen::Matrix<int, 3, -1> m_rightAssetTriangles;`
- L107 _private member_ `Eigen::VectorXi m_rightFaceCorrespondenceIndices;`
- L109 _private member_ `Eigen::VectorXi m_leftAssetVertexIndices;`
- L110 _private member_ `Eigen::Matrix<T, 3, -1> m_leftAssetVertices;`
- L111 _private member_ `Eigen::Matrix<int, 3, -1> m_leftAssetTriangles;`
- L112 _private member_ `Eigen::VectorXi m_leftFaceCorrespondenceIndices;`
- L114 _private member_ `std::shared_ptr<TITAN_NAMESPACE::TaskThreadPool> m_taskThreadPool;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace trio`
- L119 _prototype_ `template <class T> bool ToBinaryFile(FILE* pFile, const EyeAssetGeneratorParams<T>& params);`
- L122 _prototype_ `template <class T> bool FromBinaryFile(FILE* pFile, EyeAssetGeneratorParams<T>& params);`
- L125 _prototype_ `template <class T> bool ToBinaryFile(FILE* pFile, const EyeAssetGenerator<T>& eyeAssetGenerator);`
- L128 _prototype_ `template <class T> bool FromBinaryFile(FILE* pFile, EyeAssetGenerator<T>& eyeAssetGenerator);`
- L131 _prototype_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, EyeAssetGeneratorParams<T>& params);`
- L134 _prototype_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, EyeAssetGenerator<T>& eyeAssetGenerator);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/EyeballConstraints.h` (Private)


#### class `EyeballConstraints`  
`template <class T> class EyeballConstraints`  
_L19-116_
- desc: Class to evaluate constraints relative to the eyeballs
- L32 _public prototype_ `EyeballConstraints();`
- L33 _public prototype_ `~EyeballConstraints();`
- L34 _public prototype_ `EyeballConstraints(EyeballConstraints&&);`
- L35 _public prototype_ `EyeballConstraints(EyeballConstraints&) = delete;`
- L36 _public prototype_ `EyeballConstraints& operator=(EyeballConstraints&&);`
- L37 _public prototype_ `EyeballConstraints& operator=(const EyeballConstraints&) = delete;`
- L39 _public prototype_ `const Configuration& GetConfiguration() const;`
- L41 _public prototype_ `void SetConfiguration(const Configuration& config);`
- L44 _public prototype_ `void SetEyeballMesh(const Mesh<T>& eyeballMesh);` — Set the eyeball mesh.
- L47 _public function_ `void SetTargetVertexWeights(const VertexWeights<T>& interfaceVertexWeights)`
- L50 _public prototype_ `void SetInfluenceVertices(const VertexWeights<T>& influenceVertexWeights);` — Set the vertices that are influenced by the eyeball.
- L51 _public prototype_ `const VertexWeights<T>& InfluenceVertices() const;`
- L54 _public prototype_ `void SetInterfaceVertices(const VertexWeights<T>& interfaceVertexWeights);` — Set the vertices that lie on the eyeball.
- L55 _public prototype_ `const VertexWeights<T>& InterfaceVertices() const;`
- L58 _public prototype_ `std::vector<T> GetEyeballDistances(const Eigen::Matrix<T, 3, -1>& vertices) const;` — Calculate for each vertex the distance to the eyeball
- L61 _public prototype_ `std::vector<T> GetEyeballDistances(const Eigen::Matrix<T, 3, -1>& vertices, const std::vector<int>& vIDs) const;` — Calculate for each vertex the distance to the eyeball
- L64 _public prototype_ `void SetRestPose(const Eigen::Matrix<T, 3, -1>& eyeballVertices, const Eigen::Matrix<T, 3, -1>& targetVertices);` — Set the eyeball rest pose. This is only required for influence vertices.
- L67 _public prototype_ `void SetEyeballPose(const Eigen::Matrix<T, 3, -1>& eyeballVertices);` — Set the current eyeball pose.
- L70 _public prototype_ `DiffData<T> EvaluateEyeballConstraints(const DiffDataMatrix<T, 3, -1>& eyeballVertices) const;` — Evaluate the eyeball constraints.
- L73 _public prototype_ `void SetupEyeballConstraints(const Eigen::Matrix<T, 3, -1>& vertices, VertexConstraints<T, 1, 1>& vertexConstraints) const;` — Setup the eyeball constraints
- L76 _public prototype_ `void SetupEyeballInterfaceConstraints(const Eigen::Matrix<T, 3, -1>& vertices, const VertexWeights<T>& interfaceVertexWeights, T eyeballWeight, VertexConstraints<T, 1, 1>& vertexConstraints) const;` — Setup the eyeball interface constraints
- L82 _public prototype_ `void SetupEyeballInfluenceConstraints(const Eigen::Matrix<T, 3, -1>& vertices, const VertexWeights<T>& influenceVertexWeights, const std::vector<T>& influenceEyeballDistances, T eyeballWeight, VertexConstraints<T, 1, 1>& vertexConstraints) const;` — Setup the eyeball influence constraints
- L89 _public prototype_ `Eigen::Matrix<T, 3, -1> Project(const Eigen::Matrix<T, 3, -1>& vertices) const;` — Project the vertices that are interface vertices onto the eyeball, the influence vertices are projected to the reference distance
- L92 _public prototype_ `Eigen::Matrix<T, 3, -1> ProjectOntoEyeball(const Eigen::Matrix<T, 3, -1>& vertices) const;` — Project the vertices onto the eyeball
- L95 _public prototype_ `Eigen::Matrix<T, 3, -1> ProjectOntoEyeball(const Eigen::Matrix<T, 3, -1>& vertices, const std::vector<int>& vIDs) const;` — Project the vertices onto the eyeball
- L98 _public prototype_ `void SetInfluenceEyeballDistances(const std::vector<T>& distances);` — Set the distances of the influence vertices to the eyeball
- L101 _public prototype_ `const std::vector<T>& InfluenceEyeballDistances() const;` — @return the distances of the influence vertices to the eyeball
- L111 _public prototype_ `EyeballMatch GetClosestEyeballPosition(const Eigen::Vector3<T>& vertex, bool useClosestEyeballPosition) const;` — @brief Get the closest eyeball position to @p vertex. @param vertex The query vertex. @param useClosestEyeballPosition   Whether to use the true closest point, otherwise the correspondence is found by intersecting the ray from the eyeball center to the vertex with the eyeball mesh. @return EyeballMatch  The found correspondence.
- L115 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

#### struct `EyeballConstraints::EyeballMatch`  
`struct EyeballMatch`  
_L22-29_
- L24 _public member_ `int64_t tID;` — The triangle id on the eyeball match
- L25 _public member_ `Eigen::Vector3<T> eyeballPosition;` — The vertex position on the eyeball
- L26 _public member_ `Eigen::Vector3<T> eyeballNormal;` — The normal on the eyeball
- L27 _public member_ `Eigen::Vector3<T> dir;` — The direction pointing outside the eyeball
- L28 _public member_ `T dist;` — The distance between the query and the eyeball position. Query is inside the eyeball if negative.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/EyelashesGenerator.h` (Private)


#### struct `EyelashesGeneratorParams`  
`template <class T> struct EyelashesGeneratorParams`  
_L20-26_
- desc: Parameters for eyelashes generation
- L22 _public member_ `static constexpr int32_t version = 1;`
- L23 _public member_ `std::vector<std::pair<int, T>> eyelashesRoots;`
- L25 _public prototype_ `bool ReadJson(const JsonElement& element);`

#### class `EyelashesGenerator`  
`template <class T> class EyelashesGenerator`  
_L34-63_
- desc: A class which can generate eyelashes from an example driver and eyelashes mesh, and then apply this to an updated driver mesh to generate eyelashes for that mesh. Similar in concept to a 'wrap deformer', it finds the mean translation for each eyelash root, and then applies this to each eyelash in turn. Only a translation rather than a full affine transform is applied currently.
- L37 _public function_ `EyelashesGenerator()`
- L43 _public prototype_ `void SetMeshes(const std::shared_ptr<const Mesh<T>>& driverMesh, const std::shared_ptr<const Mesh<T>>& eyelashesMesh);` — set the driver mesh and eyelashes mesh. Note that this does NOT re-initialize the other internals of the class and can be used as a means to (re)set the meshes if they have been stored separately from the class
- L46 _public prototype_ `bool Init(const std::shared_ptr<const Mesh<T>>& driverMesh, const std::shared_ptr<const Mesh<T>>& eyelashesMesh, const EyelashesGeneratorParams<T>& params);` — initialize the generator from the driver mesh, the eyelashes mesh, and parameters. Returns true if initialized successfully, false otherwise
- L49 _public prototype_ `void Apply(const Eigen::Matrix<T, 3, -1>& deformedDriverMeshVertices, Eigen::Matrix<T, 3, -1>& deformedEyelashesMeshVertices) const;` — apply the generator to the driver mesh vertices to give deformedEyelashesMeshVertices as a result; deformedDriverMeshVertices must contain the correct number of vertices
- L59 _private member_ `static constexpr int32_t m_version = 1;`
- L60 _private member_ `std::shared_ptr<const Mesh<T>> m_driverMesh;`
- L61 _private member_ `std::shared_ptr<const Mesh<T>> m_eyelashesMesh;`
- L62 _private member_ `std::vector<std::shared_ptr<EyelashConnectedVertices<T>>> m_eyelashesConnectedVertices;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace trio`
- L66 _prototype_ `template <class T> bool ToBinaryFile(FILE* pFile, const EyelashesGeneratorParams<T>& params);`
- L69 _prototype_ `template <class T> bool FromBinaryFile(FILE* pFile, EyelashesGeneratorParams<T>& params);`
- L72 _prototype_ `template <class T> bool ToBinaryFile(FILE* pFile, const EyelashesGenerator<T>& eyelashesGenerator);`
- L75 _prototype_ `template <class T> bool FromBinaryFile(FILE* pFile, EyelashesGenerator<T>& eyelashesGenerator);`
- L78 _prototype_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, EyelashesGeneratorParams<T>& params);`
- L81 _prototype_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, EyelashesGenerator<T>& eyelashesGenerator);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/FlowConstraints.h` (Private)


#### class `FlowConstraintsData`  
`template <class T> class FlowConstraintsData`  
_L18-25_
- L21 _public member_ `Camera<T> camera;`
- L22 _public member_ `Eigen::Matrix<T, 2, -1> targetPositions;`
- L23 _public member_ `Eigen::VectorX<T> weights;`
- L24 _public member_ `Eigen::VectorXi vertexIndices;`

#### class `FlowConstraints`  
`template <class T> class FlowConstraints`  
_L31-60_
- desc: Class to evaluate flow constraints (2D point2point)
- L34 _public prototype_ `FlowConstraints();`
- L35 _public prototype_ `~FlowConstraints();`
- L36 _public prototype_ `FlowConstraints(FlowConstraints&& other);`
- L37 _public prototype_ `FlowConstraints(const FlowConstraints& other) = delete;`
- L38 _public prototype_ `FlowConstraints& operator=(FlowConstraints&& other);`
- L39 _public prototype_ `FlowConstraints& operator=(const FlowConstraints& other) = delete;`
- L42 _public prototype_ `void SetFlowData(const std::map<std::string, std::shared_ptr<const FlowConstraintsData<T>>>& flowConstraintsData);` — Set FlowData
- L45 _public prototype_ `void SetFlowWeight(T weight);` — Set the flow weight
- L46 _public prototype_ `T FlowWeight() const;`
- L48 _public prototype_ `Cost<T> Evaluate(const DiffDataMatrix<T, 3, -1>& vertices, std::map<std::string, std::shared_ptr<const FlowConstraintsData<T>>>* debugFlowConstraints = nullptr);`
- L51 _public prototype_ `void SetupFlowConstraints(const Eigen::Transform<T, 3, Eigen::Affine>& rigidTransform, const Eigen::Matrix<T, 3, -1>& vertices, VertexConstraints<T, 2, 1>& flowConstraints) const;`
- L55 _public prototype_ `const std::map<std::string, std::shared_ptr<const FlowConstraintsData<T>>>& FlowData() const;`
- L59 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/GridDeformation.h` (Private)


#### class `GridDeformation`  
`template <class T> class GridDeformation`  
_L13-251_
- L16 _public function_ `GridDeformation(int gridSizeX, int gridSizeY, int gridSizeZ) : m_gridSizeX(gridSizeX) , m_gridSizeY(gridSizeY) , m_gridSizeZ(gridSizeZ)`
- L24 _public function_ `GridDeformation(int gridSize) : GridDeformation(gridSize, gridSize, gridSize)`
- L26 _public function_ `GridDeformation(int gridSizeX, int gridSizeY, int gridSizeZ, const Eigen::Vector3<T>& minGridPoint, const Eigen::Vector3<T>& maxGridPoint, const Eigen::Matrix<T, 3, -1>& vertexOffsets) : m_gridSizeX(gridSizeX) , m_gridSizeY(gridSizeY) , m_gridSizeZ(gridSizeZ) , m_minGridPoint(minGridPoint) , m_maxGridPoint(maxGridPoint) , m_vertexOffsets(vertexOffsets)`
- L46 _public function_ `void Init(Eigen::Ref<const Eigen::Matrix<T, 3, -1>> srcVertices)`
- L53 _public function_ `int GridSizeX() const`
- L54 _public function_ `int GridSizeY() const`
- L55 _public function_ `int GridSizeZ() const`
- L57 _public function_ `const Eigen::Vector<T, 3>& GetMinGridPoint() const`
- L58 _public function_ `const Eigen::Vector<T, 3>& GetMaxGridPoint() const`
- L59 _public function_ `const Eigen::Vector<T, 3>& GetDelta() const`
- L61 _public function_ `Eigen::Vector3<T> EvaluateGridPosition(const Eigen::Vector3<T>& pt)`
- L63 _public function_ `Affine<T, 3, 3> EvaluateGridTransform(const Eigen::Vector3<T>& pt)`
- L65 _public function_ `void Solve(const Eigen::Matrix<T, 3, -1>& srcVertices, const Eigen::Matrix<T, 3, -1>& targetVertices, T boundaryWeight = T(10), int maxIterations = 100, const Eigen::VectorX<T>& areaPerVertex = Eigen::VectorX<T>())`
- L171 _public function_ `GridPosition GetGridPosition(const Eigen::Vector3<T>& pt) const`
- L186 _private function_ `int GridToIndex(int x, int y, int z) const`
- L191 _private function_ `std::pair<int, T> EvaluateGridPositionWeight(const GridPosition& gridPos, int xc, int yc, int zc) const`
- L199 _private function_ `Eigen::Vector3<T> EvaluateGridPosition(const GridPosition& gridPos) const`
- L216 _private function_ `Affine<T, 3, 3> EvaluateGridTransform(const GridPosition& gridPos)`
- L236 _private function_ `void UpdateDelta()`
- L244 _private member_ `int m_gridSizeX;`
- L245 _private member_ `int m_gridSizeY;`
- L246 _private member_ `int m_gridSizeZ;`
- L247 _private member_ `Eigen::Vector3<T> m_minGridPoint;`
- L248 _private member_ `Eigen::Vector3<T> m_maxGridPoint;`
- L249 _private member_ `Eigen::Vector3<T> m_delta;`
- L250 _private member_ `Eigen::Matrix<T, 3, -1> m_vertexOffsets;`

#### struct `GridDeformation::GridPosition`  
`struct GridPosition`  
_L161-169_
- L163 _public member_ `int xi;`
- L164 _public member_ `int yi;`
- L165 _public member_ `int zi;`
- L166 _public member_ `T xw;`
- L167 _public member_ `T yw;`
- L168 _public member_ `T zw;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/ICPConstraints.h` (Private)


#### class `ICPConstraints`  
`template <class T> class ICPConstraints`  
_L23-94_
- desc: Class to evaluate ICP correspondences (point2point and/or point2surface)
- L26 _public function_ `static constexpr const char* ConfigName()`
- L28 _public prototype_ `ICPConstraints();`
- L29 _public prototype_ `~ICPConstraints();`
- L30 _public prototype_ `ICPConstraints(ICPConstraints&&);`
- L31 _public prototype_ `ICPConstraints(ICPConstraints&) = delete;`
- L32 _public prototype_ `ICPConstraints& operator=(ICPConstraints&&);`
- L33 _public prototype_ `ICPConstraints& operator=(const ICPConstraints&) = delete;`
- L36 _public prototype_ `void SetCorrespondenceSearchVertexWeights(const VertexWeights<T>& vertexWeights);` — Sets the correspondence search vertex weights
- L39 _public prototype_ `void SetTargetMesh(const Mesh<T>& targetMesh);` — Set the target mesh
- L42 _public prototype_ `const Eigen::Vector<T, -1>& TargetWeights() const;` — @returns the target vertex weights for the target mesh.
- L45 _public prototype_ `void SetTargetWeights(const Eigen::Vector<T, -1>& targetWeights);` — Set custom target vertex weights for the target mesh.
- L48 _public prototype_ `void AddTargetDepthAndNormals(const std::shared_ptr<const DepthmapData<T>>& depthmapData);` — Set the target depthmap and normals
- L50 _public prototype_ `const Configuration& GetConfiguration() const;`
- L52 _public prototype_ `void SetConfiguration(const Configuration& config, bool ignoreUnknownKeys = false);`
- L55 _public prototype_ `void ClearPreviousCorrespondences();` — Clears any correspondences.
- L58 _public prototype_ `bool HasCorrespondences() const;` — @returns True if ICP correspondences have been set up using SetupCorrespondences() or EvaluateICP()
- L61 _public prototype_ `void SetupCorrespondences(const Eigen::Matrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& normals);` — Find the correspondences and store the result internally (which is then used for EvaluateICP)
- L67 _public prototype_ `Cost<T> EvaluateICP(const DiffDataMatrix<T, 3, -1>& vertices);` — Evaluate the ICP constraint. @param[in] vertices  The differentiable input vertices.
- L75 _public prototype_ `Cost<T> EvaluateICP(const DiffDataMatrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& normals, bool searchCorrespondences);` — Evaluate the ICP constraint. First finds correspondences if @p searchCorrespondences is True or if no correspondences hav been set up. @param[in] vertices  The differentiable input vertices. @param[in] normals   The normals that should be used when searching correspondences (only needs to be set when searchCorrespondences=true) @param[in] searchCorrespondences  If True then new correspendences are found using SetupCorrespondences, otherwise the current correspondences are used.
- L78 _public prototype_ `void FindCorrespondences(const Eigen::Matrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& normals, typename MeshCorrespondenceSearch<T>::Result& correspondences) const;` — Finds the correspondences and stores the result in @p correspondences
- L85 _public prototype_ `void SetupICPConstraints(const Eigen::Transform<T, 3, Eigen::Affine>& rigidTransform, const Eigen::Matrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& normals, VertexConstraints<T, 1, 1>& point2SurfaceVertexConstraints, VertexConstraints<T, 3, 1>& point2PointVertexConstraints);` — Alternative way to set up ICP constraints
- L93 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/IdentityBlendModel.h` (Private)


#### class `IdentityBlendModel`  
`template <class T, int D = 3> class IdentityBlendModel`  
_L22-138_
- desc: IdentityBlendModel models the geometry of a face as Vertices = MeanShape + sum_regions (B_region x_region) where B_region is the linear model for a region, and x_region are the coefficients.
- L35 _public prototype_ `IdentityBlendModel();`
- L36 _public prototype_ `~IdentityBlendModel();`
- L37 _public prototype_ `IdentityBlendModel(IdentityBlendModel&& other);`
- L38 _public prototype_ `IdentityBlendModel(const IdentityBlendModel& other) = delete;`
- L39 _public prototype_ `IdentityBlendModel& operator=(IdentityBlendModel&& other);`
- L40 _public prototype_ `IdentityBlendModel& operator=(const IdentityBlendModel& other) = delete;`
- L42 _public prototype_ `std::shared_ptr<IdentityBlendModel> Reduce(const std::vector<int>& vertexIds) const;`
- L45 _public prototype_ `void SetModel(Eigen::Matrix<T, D, -1>&& mean, std::vector<RegionData>&& regionsData);` — Set the model data
- L70 _public prototype_ `void LoadModelJson(const std::string& identityModelFile);` — Load model from json file
- L73 _public prototype_ `void LoadModelJson(const TITAN_NAMESPACE::JsonElement& identityJson);` — Load model from JsonElement object
- L76 _public prototype_ `void SaveModelJson(const std::string& identityModelFile) const;` — Save model to json file
- L79 _public prototype_ `TITAN_NAMESPACE::JsonElement SaveModelJson() const;` — @returns the model as JsonElement object
- L82 _public prototype_ `void SaveModelBinary(const std::string& filename) const;` — Save model to binary file
- L85 _public prototype_ `bool LoadModelBinary(const std::string& identityModelFile);` — Load model from binary file
- L88 _public prototype_ `int NumParameters() const;` — @returns the number of parameters of the model
- L91 _public prototype_ `int NumRegions() const;` — @returns the number of regions in the model
- L94 _public prototype_ `int NumVertices() const;` — @returns the number of vertices in the model
- L97 _public prototype_ `Vector<T> DefaultParameters() const;` — @returns default parameters resulting in an average face
- L100 _public prototype_ `const Eigen::Matrix<T, D, -1>& Base() const;` — @returns the base shape
- L103 _public prototype_ `SparseMatrixConstPtr<T> ModelMatrix() const;` — @returns the model matrix
- L106 _public prototype_ `Eigen::Matrix<T, D, -1> Evaluate(const Vector<T>& parameters) const;` — @returns the evaluated model for the parameters
- L109 _public prototype_ `DiffDataMatrix<T, D, -1> Evaluate(const DiffData<T>& parameters) const;` — @returns the evaluated model for the parameters
- L112 _public prototype_ `DiffData<T> EvaluateRegularization(const DiffData<T>& parameters) const;` — @returns evaluates the regularization on the parameters
- L115 _public prototype_ `const std::string& RegionName(int regionIndex) const;` — @returns the name of the region at index @p regionIndex in the model.
- L118 _public prototype_ `const std::vector<std::string>& ModeNames(int regionIndex) const;` — @returns the name of the modes for a certain region.
- L121 _public prototype_ `const std::vector<std::pair<int, int>>& RegionRanges() const;` — @returns for each region the indeces [startIndex, endIndex) in the parameter array.
- L124 _public prototype_ `const Eigen::VectorXi& RegionVertexIds(int regionIndex) const;` — @returns the vertex ids used for a certain region.
- L127 _public prototype_ `const Eigen::VectorX<T>& RegionWeights(int regionIndex) const;` — @returns the blending weights for a certain region.
- L130 _public prototype_ `const Eigen::Matrix<T, -1, -1>& RegionModes(int regionIndex) const;` — @returns the mode matrix for a certain region.
- L133 _private prototype_ `void UpdateBlendModelMatrix();`
- L137 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

#### struct `IdentityBlendModel::RegionData`  
`struct RegionData`  
_L25-32_
- L27 _public member_ `std::string regionName;`
- L28 _public member_ `Eigen::Matrix<T, -1, -1> modes;`
- L29 _public member_ `Eigen::VectorXi vertexIDs;`
- L30 _public member_ `Eigen::VectorX<T> weights;`
- L31 _public member_ `std::vector<std::string> modeNames;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/ImageConstraints.h` (Private)


#### class `ImageConstraintsData`  
`template <class T> class ImageConstraintsData`  
_L18-26_
- L21 _public member_ `Camera<T> camera;`
- L22 _public member_ `Eigen::Matrix<T, 2, -1> targetPositions;`
- L23 _public member_ `Eigen::Matrix<T, 2, -1> targetNormals;`
- L24 _public member_ `Eigen::VectorX<T> weights;`
- L25 _public member_ `Eigen::VectorXi vertexIndices;`

#### class `ImageConstraints`  
`template <class T> class ImageConstraints`  
_L32-58_
- desc: Class to evaluate flow constraints (2D point2point)
- L35 _public prototype_ `ImageConstraints();`
- L36 _public prototype_ `~ImageConstraints();`
- L37 _public prototype_ `ImageConstraints(ImageConstraints&& other);`
- L38 _public prototype_ `ImageConstraints(const ImageConstraints& other) = delete;`
- L39 _public prototype_ `ImageConstraints& operator=(ImageConstraints&& other);`
- L40 _public prototype_ `ImageConstraints& operator=(const ImageConstraints& other) = delete;`
- L43 _public prototype_ `void SetImageConstraintsData(const std::map<std::string, std::shared_ptr<const ImageConstraintsData<T>>>& imageConstraintsData);` — Set Image constraints data
- L46 _public prototype_ `void SetWeight(T weight);` — Set the weight for image constraints
- L48 _public prototype_ `Cost<T> Evaluate(const DiffDataMatrix<T, 3, -1>& vertices, std::map<std::string, std::shared_ptr<const ImageConstraintsData<T>>>* debugImageConstraints = nullptr);`
- L51 _public prototype_ `void SetupImageConstraints(const Eigen::Transform<T, 3, Eigen::Affine>& rigidTransform, const Eigen::Matrix<T, 3, -1>& vertices, VertexConstraints<T, 1, 1>& flowConstraints) const;`
- L57 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/LinearModel.h` (Private)


#### struct `LinearModel`  
`template <class T> struct LinearModel`  
_L13-22_
- desc: Simple linear model.
- L15 _public member_ `Eigen::VectorX<T> mean;`
- L16 _public member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> modes;`
- L18 _public function_ `const Eigen::VectorX<T> Evaluate(const Eigen::VectorX<T>& coeffs) const`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/LinearVertexModel.h` (Private)


#### struct `LinearVertexModel`  
`template <class T> struct LinearVertexModel`  
_L20-148_
- desc: @brief Dense linear vertex model extended with the last 7 modes representing rigid deformation and scale. v = dR * dscale * (base + modes * coeffs) + dT The rotation mode is a linearlized rotation (differential rotation using quaternion i.e. see QuaternionDerivativeMatrix) and in principle this linearized rotation depends on the current vertices. In practice it is also ok to approximate it with the mean vertices and therefore does not need to be constantly updated. The same applies to scale: the scale coefficient is the scale offset relative to a scale of 1, and the linearization of the scale depends on the current vertices.
- L28 _public prototype_ `LinearVertexModel() = default;`
- L29 _public function_ `LinearVertexModel(const Eigen::Matrix<T, 3, -1>& base, const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>& modes)`
- L34 _public function_ `void Create(const Eigen::Matrix<T, 3, -1>& base, const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>& modes)`
- L45 _public function_ `int NumVertices() const`
- L46 _public function_ `int NumTotalModes() const`
- L47 _public function_ `int NumPCAModes() const`
- L49 _public function_ `void EvaluateLinearized(const Eigen::VectorX<T>& coeffs, EvaluationMode evaluationMode, Eigen::Matrix<T, 3, -1>& output, TaskThreadPool* taskThreadPool = TaskThreadPool::GlobalInstance( false).get()) const`
- L55 _public function_ `Eigen::Matrix<T, 3, -1> EvaluateLinearized(const Eigen::VectorX<T>& coeffs, EvaluationMode evaluationMode, TaskThreadPool* taskThreadPool = TaskThreadPool::GlobalInstance( false).get()) const`
- L70 _public function_ `void EvaluateLinearized(const Eigen::VectorX<T>& coeffs, EvaluationMode evaluationMode, LinearVertexModel& output, bool forceCopyModes = false) const` — @brief Evaluate the linear vertex model and store the result as a vertex model. The modes are only copied if the output modes size is different. @param coeffs The coefficients of the linear model (either with or without the rigid component). @param evaluationMode Whether to evaluate the rigid component of the model. @param output The LinearVertexModel that will contain the result. @param forceCopyModes Force copying the modes even if the size is the same.
- L78 _public function_ `void SetTranslationModes()`
- L85 _public function_ `void SetRotationModes(const Eigen::Matrix<T, 3, -1>& vertices)`
- L100 _public function_ `void SetScaleMode(const Eigen::Matrix<T, 3, -1>& vertices)`
- L105 _public function_ `Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> Modes(EvaluationMode evaluationMode) const`
- L114 _public function_ `const Eigen::Matrix<T, 3, -1>& Base() const`
- L115 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> BaseAsVector() const`
- L118 _public function_ `Eigen::Matrix<T, 3, -1>& MutableBase()` — Direct access to the base vertices of the linear model. Caller needs to know what they are doing.
- L121 _public function_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor>& MutableModes()` — Direct access to the modes of the linear model. Caller needs to know what they are doing.
- L124 _public function_ `void Translate(const Eigen::Vector3<T>& translation)` — Translates the vertex model. Also updates the rotation modes using the new base.
- L132 _public function_ `void Resample(const std::vector<int>& newToOldMap)` — Rebsample the model keeping only the vertices in @p newToOldMap
- L146 _private member_ `Eigen::Matrix<T, 3, -1> m_base;`
- L147 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> m_modes;`

#### enum `LinearVertexModel::EvaluationMode`  
`enum class EvaluationMode`  
_L22-26_
- L23 _public enumerator_ `STATIC`
- L24 _public enumerator_ `RIGID`
- L25 _public enumerator_ `RIGID_SCALE`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/LipClosureConstraints.h` (Private)


#### struct `LipClosureConstraintsData`  
`template <class T> struct LipClosureConstraintsData`  
_L18-34_
- L20 _public member_ `std::vector<int> srcIDs;`
- L21 _public member_ `std::vector<BarycentricCoordinates<T, 3>> targetBCs;`
- L22 _public member_ `std::vector<Eigen::Vector3<T>> normals;`
- L23 _public member_ `std::vector<T> weights;`
- L25 _public function_ `void Clear()`
- L33 _public function_ `int NumConstraints() const`

#### class `LipClosureConstraints`  
`template <class T> class LipClosureConstraints`  
_L40-91_
- desc: Class to evaluate collision constraints
- L43 _public function_ `static constexpr const char* ConfigName()`
- L46 _public prototype_ `LipClosureConstraints();`
- L47 _public prototype_ `~LipClosureConstraints();`
- L48 _public prototype_ `LipClosureConstraints(LipClosureConstraints&&);`
- L49 _public prototype_ `LipClosureConstraints(LipClosureConstraints&) = delete;`
- L50 _public prototype_ `LipClosureConstraints& operator=(LipClosureConstraints&&);`
- L51 _public prototype_ `LipClosureConstraints& operator=(const LipClosureConstraints&) = delete;`
- L54 _public prototype_ `void SetTopology(const Mesh<T>& mesh, const std::vector<int>& upperLipMask, const std::vector<std::vector<int>>& upperContourLines, const std::vector<int>& lowerLipMask, const std::vector<std::vector<int>>& lowerContourLines, TITAN_NAMESPACE::TaskThreadPool* taskThreadPool = nullptr);` — Set the topology with mask for lower and upper lips
- L62 _public prototype_ `void SetLipClosure(const LipClosure3D<T>& lipClosure3D);` — Set the lip closure data (i.e. determine lip closure from landmarks)
- L65 _public prototype_ `void ResetLipClosure();` — Reset the lip closure data
- L68 _public prototype_ `bool ValidLipClosure() const;` — @returns True if the lip closure constraint can be calculated using lip closure landmarks
- L71 _public prototype_ `void CalculateLipClosureData(const Eigen::Matrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& normals, const Eigen::Transform<T, 3, Eigen::Affine>& toCamerasTransform, bool useLandmarks, const Eigen::Transform<T, 3, Eigen::Affine>& toFaceTransform, TITAN_NAMESPACE::TaskThreadPool* taskThreadPool = nullptr);` — Calculate lip closure constraints.
- L79 _public prototype_ `void EvaluateLipClosure(const Eigen::Matrix<T, 3, -1>& vertices, VertexConstraints<T, 3, 1>& lipClosureVertexConstraints) const;` — Evaluate simple lip closure constraints.
- L80 _public prototype_ `void EvaluateLipClosure(const Eigen::Matrix<T, 3, -1>& vertices, VertexConstraints<T, 3, 4>& lipClosureVertexConstraints) const;`
- L83 _public prototype_ `void GetLipClosureData(LipClosureConstraintsData<T>& lipClosureConstraintsData) const;` — Retrieve current closure
- L85 _public prototype_ `Configuration& Config() ;`
- L86 _public prototype_ `const Configuration& Config() const;`
- L90 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/LoadNeckFalloffMasks.h` (Private)


#### Free symbols / members of external scopes

- L10 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> bool LoadNeckFalloffMasks(const JsonElement& neckFalloffMaskJson, const RigGeometry<T>& rigGeometry, std::vector<std::shared_ptr<VertexWeights<T>>>& headVertexSkinningWeightsMasks);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/MeshContourPoint.h` (Private)


#### class `MeshContourPoint`  
`template <class T> class MeshContourPoint`  
_L14-82_
- L21 _public prototype_ `static MeshContourPoint FindContourChange(const std::vector<int>& vIDs, const Eigen::Ref<const Eigen::Matrix<T, 3, -1>>& vertices, const Eigen::Matrix<T, 3, -1>& normals, const Camera<T>& camera);` — Finds the position where the contour line switches from front facing to back facing i.e. it finds where the actual contour is on the mesh. The search is from start to end and it will return the first switch.
- L31 _public prototype_ `static std::vector<MeshContourPoint> FindContourChanges(const std::vector<std::vector<int>>& multiple_vIDs, const Eigen::Ref<const Eigen::Matrix<T, 3, -1>>& vertices, const Eigen::Matrix<T, 3, -1>& normals, const Camera<T>& camera);` — Finds multiple contour points. @see FindContourChange()
- L40 _public prototype_ `static std::pair<std::vector<MeshContourPoint>, std::vector<MeshContourPoint>> FindContourChangesAndOcclusions( const std::vector<std::vector<int>>& vIDsForContourA, const std::vector<std::vector<int>>& vIDsForContourB, const Eigen::Ref<const Eigen::Matrix<T, 3, -1>>& vertices, const Eigen::Matrix<T, 3, -1>& normals, const Camera<T>& camera);` — Finds multiple contour points and occlusions. @see FindContourChange()
- L59 _public prototype_ `static void UpdateContourBasedOnOcclusions(std::vector<MeshContourPoint>& contourA, const std::vector<MeshContourPoint>& contourB);` — Determines for each contour point whether it is occluded by the other contour. Algorithm: - search for closest point on curve of contourB - check whether the contour is occluded by checking the location relative to the curve and the depth Known issue: in many cases the lips self intersect (even in neutral) and in that case one lip contour is set as occluded and the other is not (based on depth), though it would be correct if both are set as occluded. TODO: to determine if a point is truly occluded we could search along a contour line and find the point where the line is not occluded anymore and compare the depth there.
- L61 _public member_ `int vID1;`
- L62 _public member_ `int vID2;`
- L63 _public member_ `T w1;`
- L71 _public member_ `} type;`
- L73 _public member_ `Eigen::Vector3<T> pix{ 0, 0, 0 };` — position of contour point in image space and depth
- L75 _public member_ `Eigen::Vector2<T> normal{ 0, 0 };` — normal of contour point in image space
- L81 _public member_ `T occlusionDepthOffset = std::numeric_limits<T>::max();` — @brief relative depth to contour line that is being used for the occlusion test. If positive, then this contour point is closer to the camera compared to the point on the other contour. If negative, then this contour point is further from the camera than the other contour point.

#### enum `MeshContourPoint::Type`  
`enum class Type`  
_L64-71_
- L66 _public enumerator_ `CONTOUR`
- L67 _public enumerator_ `OCCLUSION`
- L68 _public enumerator_ `BORDER_FRONT`
- L69 _public enumerator_ `BORDER_BACK`
- L70 _public enumerator_ `INVALID`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/MeshLandmarks.h` (Private)


#### struct `ContourData`  
`struct ContourData`  
_L18-22_
- L20 _public member_ `Eigen::VectorXi region;`
- L21 _public member_ `Eigen::VectorXi curve;`

#### class `MeshLandmarks`  
`template <class T> class MeshLandmarks`  
_L25-129_
- L28 _public member_ `static constexpr const char* DEFAULT_MESH_NAME = "he`
- L31 _public prototype_ `MeshLandmarks() = default;`
- L34 _public prototype_ `bool DeserializeJson(const JsonElement& json, const Mesh<T>& mesh, const std::string& meshName = DEFAULT_MESH_NAME);` — loads all landmarks and curves from stream that are part of mesh @p meshName.
- L37 _public prototype_ `bool DeserializeJson(const std::string& data, const Mesh<T>& mesh, const std::string& meshName = DEFAULT_MESH_NAME);` — loads all landmarks and curves from stream that are part of mesh @p meshName.
- L40 _public prototype_ `bool Load(const std::string& filename, const Mesh<T>& mesh, const std::string& meshName = DEFAULT_MESH_NAME);` — loads all landmarks and curves from file @p filename that are pare of mesh @p meshName.
- L43 _public prototype_ `void Save(const std::string& filename, const std::string& meshName = "") const;` — Saves the mesh landmarks to a JSON file
- L46 _public prototype_ `void Append(const std::string& filename, const std::string& meshName = "") const;` — Appends the mesh landmarks to a JSON file
- L48 _public prototype_ `std::string SerializeJson(std::string& previousData, const std::string& meshName) const;`
- L50 _public function_ `const std::map<std::string, BarycentricCoordinates<T>>& LandmarksBarycentricCoordinates() const`
- L55 _public function_ `bool HasLandmark(const std::string& name) const`
- L60 _public function_ `const std::map<std::string, std::vector<BarycentricCoordinates<T>>>& MeshCurvesBarycentricCoordinates() const`
- L65 _public function_ `bool HasCurve(const std::string& name) const`
- L70 _public function_ `const std::vector<std::vector<int>>& InnerLowerLipContourLines() const`
- L71 _public function_ `const std::vector<std::vector<int>>& InnerUpperLipContourLines() const`
- L73 _public function_ `const std::map<std::string, std::vector<std::vector<int>>>& Contours() const`
- L75 _public function_ `bool HasContour(const std::string& name) const`
- L84 _public function_ `const std::vector<std::vector<int>>& Contour(const std::string& name)` — @returns a contour of type @p name @pre a contour of type @p name exists.
- L86 _public function_ `void AddLandmark(const std::string& name, const BarycentricCoordinates<T>& landmark)`
- L88 _public function_ `void AddCurve(const std::string& name, const std::vector<BarycentricCoordinates<T>>& curve)`
- L90 _public prototype_ `void MergeCurves(const std::vector<std::string>& curveNames, const std::string& newCurveName, bool removePreviousCurves);`
- L93 _public prototype_ `std::set<int> GetAllVertexIndices() const;` — get all the vertices that are used by landmarks, mesh curves, and contour lines.
- L96 _public prototype_ `bool Remap(const std::map<int, int>& oldIndexToNewIndex);` — remap the mesh landmarks. @returns True if mapping was successful, false if the map does not map all of the vertex IDs.
- L99 _public prototype_ `bool IsLoop(const std::string& curveName) const;` — @returns True if the curve is a loop.
- L102 _public prototype_ `static std::pair<Eigen::VectorXi, bool> SortCurveUsingMeshTopology(const Mesh<T>& mesh, const Eigen::VectorXi& curve, const std::string& name, bool sortRightToLeft);` — sort a @p curve of unordered points to be sorted based on the mesh edges and optionally sorting it right to left.
- L111 _public prototype_ `static std::vector<std::vector<int>> CalculateContourLines(const Eigen::VectorXi& region, const Eigen::VectorXi& curve, const Mesh<T>& mesh, const std::string& name);` — Calculates the contour lines by walking along the edge loops that are orthogonal to the @p curve line. The resulting contour lines are sorted from front to back on the face.
- L117 _private member_ `std::map<std::string, BarycentricCoordinates<T>> m_meshLandmarksBarycentricCoordinates;`
- L118 _private member_ `std::map<std::string, std::vector<BarycentricCoordinates<T>>> m_meshCurvesBarycentricCoordinates;`
- L119 _private member_ `std::map<std::string, std::vector<std::vector<int>>> m_contours;`
- L120 _private member_ `std::map<std::string, ContourData> m_contourData;`
- L122 _private member_ `std::vector<std::vector<int>> m_innerLowerLipContourLines;`
- L123 _private member_ `std::vector<std::vector<int>> m_innerUpperLipContourLines;`
- L124 _private member_ `ContourData m_innerLowerLipContourData;`
- L125 _private member_ `ContourData m_innerUpperLipContourData;`
- L128 _private member_ `std::set<std::string> m_loops;` — set of curves that are loops

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/NeckSeamSnapConfig.h` (Private)


#### class `NeckSeamSnapConfig`  
`template <class T> class NeckSeamSnapConfig`  
_L16-52_
- desc: Simple class for representing the mapping of the neck seam between combined body rig and face rig
- L19 _public prototype_ `NeckSeamSnapConfig() = default;`
- L28 _public prototype_ `bool Init(const std::string neckSeamPath, const RigGeometry<T>& rigGeometry);` — initialise the neck seam snap config from neckSeamPath json file, for the supplied (head) rigGeometry. This handles the case that there are 8 head lods and only 4 body lods; the neck seam vertices for the 'odd' head lods match exactly. Returns true if loaded successfully, false if not. @param[in] neckSeamPath: filename of json file containing the neck seam vertex indices for the head rig at each lod @param[in] rigGeometry: the rig geometry for the head rig @returns true if successfully loaded, false otherwise
- L31 _public prototype_ `bool ReadJson(const JsonElement& json);` — Read data from json element
- L34 _public prototype_ `void WriteJson(JsonElement& json) const;` — Write the NeckSeamSnapConfig to Json
- L40 _public prototype_ `bool IsValidForCombinedBodyAndFaceRigs(const RigGeometry<T>& combinedBodyRigGeometry, const RigGeometry<T>& faceRigGeometry) const;` — Check if the neck seam snap config is valid for the supplied combined body and face rigs. Returns true if it is valid, false if not. Checks that the map keys match the head mesh names for all lods, and that the vertex indices for the snap config are in range, and that all lods of the body are included
- L47 _public prototype_ `const std::map<std::string, std::pair<int, SnapConfig<T>>>& GetLodNeckSeamSnapConfigs() const;` — Get the map of mesh seam snap configs for each head mesh from combined body mesh to  head mesh for each lod. Returns a map of (head) mesh name at each lod to the corresponding SnapConfig which maps between src vertex indices (on the combined body) to target vertex indices (on the head). The int in each pair is the body lod which corresponds to the current head mesh name
- L51 _private member_ `std::map<std::string, std::pair<int, SnapConfig<T>>> m_neckBodySnapConfig;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/PCAFaceFitting.h` (Private)


#### class `PCAFaceFitting`  
`class PCAFaceFitting`  
_L23-170_
- L91 _public prototype_ `~PCAFaceFitting();`
- L92 _public prototype_ `PCAFaceFitting();`
- L98 _public prototype_ `bool LoadPCARig(const std::string& pcaFilename);` — Load the PCA rig from (DNA) file pcaFilename @pre must have loaded the tracking rig before loading the PCA rig
- L104 _public prototype_ `bool LoadPCARig(dna::Reader* dnaStream);` — Load the PCA rig from (DNA) Reader dnaStream @pre must have loaded the tracking rig before loading the PCA rig
- L106 _public prototype_ `bool SavePCARig(dna::Writer* dnaStream) const;`
- L107 _public prototype_ `void SavePCARigAsNpy(const std::string& filename) const;`
- L110 _public function_ `const rt::PCARig& GetPCARig() const` — @return the loaded pca rig
- L113 _public function_ `Affine<float, 3, 3> PCARigToMesh() const` — @return the alignment of the pca rig to the original mesh
- L116 _public prototype_ `void FitPCAData(const Mesh<float>& topology, std::vector<DepthmapConstraints>& vectorOfDepthmapConstraints, ICPConstraints<float>* icpConstraints, LandmarkConstraints2D<float>* landmarkConstraints, const std::vector<FlowConstraints<float>*>& vectorOfFlowConstraints, ImageConstraints<float>* imageConstraints, LipClosureConstraints<float>* lipClosureConstraints, Affine<float, 3, 3>& rigidMotion, Eigen::VectorX<float>& pcaCoeffs, const std::vector<Eigen::VectorX<float>>& pcaCoeffsPrevFrames, const Settings& settings, std::vector<State>& states) const;` — Fits the PCA model.
- L130 _public prototype_ `void FitPCADataNeck(const Mesh<float>& topology, std::vector<DepthmapConstraints>& vectorOfDepthmapConstraints, ICPConstraints<float>* icpConstraints, const std::vector<FlowConstraints<float>*>& vectorOfFlowConstraints, ImageConstraints<float>* imageConstraints, Affine<float, 3, 3>& rigidMotion, Eigen::Matrix3Xf faceVertices, Eigen::VectorX<float>& pcaCoeffsNeck, const std::vector<Eigen::VectorX<float>>& pcaCoeffsPrevFrames, const Settings& settings, std::vector<State>& states) const;` — Fits the PCA model for neck.
- L142 _public prototype_ `void LoadFaceMeshLandmarks(const MeshLandmarks<float>& faceMeshLandmarks);`
- L143 _public prototype_ `void LoadEyeLeftMeshLandmarks(const MeshLandmarks<float>& eyeLeftMeshLandmarks);`
- L144 _public prototype_ `void LoadEyeRightMeshLandmarks(const MeshLandmarks<float>& eyeRightMeshLandmarks);`
- L145 _public prototype_ `void LoadTeethMeshLandmarks(const MeshLandmarks<float>& teethMeshLandmarks);`
- L148 _private prototype_ `void UpdateSubsampled();`
- L151 _private member_ `rt::PCARig m_pcaRig;`
- L154 _private member_ `MeshLandmarks<float> m_faceMeshLandmarks;` — mesh landmarks that are used for pca face tracking using the full rig
- L155 _private member_ `MeshLandmarks<float> m_eyeLeftMeshLandmarks;`
- L156 _private member_ `MeshLandmarks<float> m_eyeRightMeshLandmarks;`
- L157 _private member_ `MeshLandmarks<float> m_teethMeshLandmarks;`
- L160 _private member_ `rt::PCARig m_pcaRigSubsampled;` — subsampled pca rig only containing vertices that are needed for tracking
- L163 _private member_ `MeshLandmarks<float> m_subsampledFaceMeshLandmarks;` — mesh landmarks that are used for pca face tracking using the subsampled rig
- L164 _private member_ `MeshLandmarks<float> m_subsampledEyeLeftMeshLandmarks;`
- L165 _private member_ `MeshLandmarks<float> m_subsampledEyeRightMeshLandmarks;`
- L166 _private member_ `MeshLandmarks<float> m_subsampledTeethMeshLandmarks;`
- L169 _private member_ `std::unique_ptr<Private> m;`

#### struct `PCAFaceFitting::Settings`  
`struct Settings`  
_L26-33_
- L28 _public member_ `bool withRigid = false;`
- L29 _public member_ `int iterations = 5;`
- L30 _public member_ `float pcaRegularization = 0.1f;`
- L31 _public member_ `float pcaVelocityRegularization = 0.0f;`
- L32 _public member_ `float pcaAccelerationRegularization = 0.0f;`

#### struct `PCAFaceFitting::Cache`  
`struct Cache`  
_L36-76_
- desc: The Cache keeps the memory allocated for the various vertex constraints as well as the jacobians that are calculated at each solver iteration.
- L38 _public member_ `VertexConstraints<float, 1, 1> point2SurfaceVertexConstraints;`
- L39 _public member_ `Eigen::Matrix<float, -1, -1, Eigen::RowMajor> point2SurfaceVertexConstraintsJacobian;`
- L40 _public member_ `VertexConstraints<float, 3, 1> point2PointVertexConstraints;`
- L41 _public member_ `Eigen::Matrix<float, -1, -1, Eigen::RowMajor> point2PointVertexConstraintsJacobian;`
- L42 _public member_ `VertexConstraints<float, 2, 3> landmarksVertexConstraints;`
- L43 _public member_ `Eigen::Matrix<float, -1, -1, Eigen::RowMajor> landmarksVertexConstraintsJacobian;`
- L44 _public member_ `VertexConstraints<float, 1, 3> curvesVertexConstraints;`
- L45 _public member_ `Eigen::Matrix<float, -1, -1, Eigen::RowMajor> curvesVertexConstraintsJacobian;`
- L46 _public member_ `VertexConstraints<float, 1, 2> contourVertexConstraints;`
- L47 _public member_ `Eigen::Matrix<float, -1, -1, Eigen::RowMajor> contourVertexConstraintsJacobian;`
- L48 _public member_ `VertexConstraints<float, 1, 3> eyeLeftCurvesVertexConstraints;`
- L49 _public member_ `Eigen::Matrix<float, -1, -1, Eigen::RowMajor> eyeLeftCurvesVertexConstraintsJacobian;`
- L50 _public member_ `VertexConstraints<float, 1, 3> eyeRightCurvesVertexConstraints;`
- L51 _public member_ `Eigen::Matrix<float, -1, -1, Eigen::RowMajor> eyeRightCurvesVertexConstraintsJacobian;`
- L52 _public member_ `VertexConstraints<float, 2, 3> teethVertexConstraints;`
- L53 _public member_ `Eigen::Matrix<float, -1, -1, Eigen::RowMajor> teethVertexConstraintsJacobian;`
- L54 _public member_ `VertexConstraints<float, 2, 1> flowVertexConstraints;`
- L55 _public member_ `Eigen::Matrix<float, -1, -1, Eigen::RowMajor> flowVertexConstraintsJacobian;`
- L56 _public member_ `VertexConstraints<float, 1, 1> imageVertexConstraints;`
- L57 _public member_ `Eigen::Matrix<float, -1, -1, Eigen::RowMajor> imageVertexConstraintsJacobian;`
- L59 _public member_ `VertexConstraints<float, 3, 4> lipClosureVertexConstraints;` — VertexConstraints<float, 3, 1> lipClosureVertexConstraints; //!< lip closure against mid point
- L60 _public member_ `Eigen::Matrix<float, -1, -1, Eigen::RowMajor> lipClosureVertexConstraintsJacobian;`
- L62 _public function_ `void Clear()`

#### struct `PCAFaceFitting::State`  
`struct State`  
_L80-88_
- desc: tracking state
- L82 _public member_ `rt::LinearVertexModel<float> face;`
- L83 _public member_ `rt::LinearVertexModel<float> neck;`
- L84 _public member_ `rt::LinearVertexModel<float> teeth;`
- L85 _public member_ `rt::LinearVertexModel<float> eyeLeft;`
- L86 _public member_ `rt::LinearVertexModel<float> eyeRight;`
- L87 _public member_ `Cache cache;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/PatchBlendModel.h` (Private)


#### class `PatchBlendModel`  
`template <class T> class PatchBlendModel`  
_L24-126_
- L31 _public prototype_ `PatchBlendModel();`
- L32 _public prototype_ `PatchBlendModel(const std::shared_ptr<TaskThreadPool>& threadPool);`
- L33 _public prototype_ `~PatchBlendModel();`
- L34 _public prototype_ `PatchBlendModel(PatchBlendModel&&);`
- L35 _public prototype_ `PatchBlendModel(const PatchBlendModel&) = delete;`
- L36 _public prototype_ `PatchBlendModel& operator=(PatchBlendModel&&);`
- L37 _public prototype_ `PatchBlendModel& operator=(const PatchBlendModel&) = delete;`
- L39 _public prototype_ `std::shared_ptr<PatchBlendModel> Reduce(const std::vector<int>& vertexIds) const;`
- L41 _public prototype_ `std::pair<DiffDataMatrix<T, 3, -1>, Cost<T>> EvaluateVerticesAndConstraints(Context<T>* context, OptimizationState& state, T modelRegularization, T patchSmoothness) const;`
- L44 _public prototype_ `void LoadModel(const std::string& identityModelFileOrData);` — Load the patch model from filename or data as Json string
- L47 _public prototype_ `void LoadModelBinary(const std::string& filename);` — Load the patch model from binary file (by first loading an IdentityBlendModel)
- L50 _public prototype_ `void LoadFromIdentityModel(const std::shared_ptr<const IdentityBlendModel<T>>& identityModel);` — Load the patch model from identity model
- L53 _public prototype_ `void LoadFromIdentityModel(const std::shared_ptr<const IdentityBlendModel<T, -1>>& identityModel);` — Load the patch model from identity model
- L56 _public prototype_ `Eigen::Vector3<T> PatchCenterOfGravity(int id) const;` — Get patch center of gravity for specified patch id
- L59 _public prototype_ `int NumVertices() const;` — @returns the number of vertices
- L62 _public prototype_ `int NumPatches() const;` — @returns the number of patches
- L65 _public prototype_ `int NumPcaModesForPatch(int id) const;` — Get number of modes for patch at specified patch id
- L68 _public prototype_ `int NumVerticesForPatch(int id) const;` — Get number of vertices for patch
- L71 _public function_ `const std::vector<std::string>& PatchNames() const` — Get the patch names
- L74 _public prototype_ `const std::string& PatchName(int id) const;` — Get the name for patch @p id
- L77 _public prototype_ `Eigen::Matrix<T, 3, -1> DeformedVertices(const State& state, const Eigen::VectorX<T>& vertexDeltaScale = Eigen::VectorX<T>(0)) const;` — @returns the deformed vertex positions
- L80 _public prototype_ `Eigen::Matrix<T, 3, -1> DeformedVertices(OptimizationState& state, bool updateModes = false) const;` — @returns the deformed vertex positions
- L83 _public prototype_ `State CreateState() const;` — Create a new state
- L86 _public prototype_ `OptimizationState CreateOptimizationState() const;` — Create a new optimization state
- L89 _public prototype_ `const std::vector<std::vector<std::tuple<int, int, T>>>& BlendMatrix() const;` — @return the blend matrix
- L92 _public prototype_ `const Eigen::Matrix<T, 3, -1>& BaseVertices() const;` — @returns the base vertex positions
- L95 _public prototype_ `const std::vector<rt::LinearVertexModel<T>>& PatchModels() const;` — get the base region models
- L98 _public prototype_ `std::pair<Eigen::Quaternion<T>, T> EstimateRotationAndScale(int vertex, const State& state) const;` — estimate the approximation rotation and scale for vertex @p vID based on state @p state (estimates the transform as weighted sum)
- L101 _private prototype_ `void UpdateBaseVertices();`
- L102 _private prototype_ `void UpdateRegionModels(OptimizationState& state, bool withModes) const;`
- L104 _private prototype_ `DiffDataMatrix<T, 3, -1> EvaluateVertices(OptimizationState& state, const DiffData<T>& values) const;`
- L105 _private prototype_ `DiffData<T> EvaluateRegularization(OptimizationState& state, const DiffData<T>& values) const;`
- L106 _private prototype_ `DiffData<T> EvaluatePatchSmoothness(OptimizationState& state, const DiffData<T>& values) const;`
- L110 _private member_ `Eigen::Matrix<T, 3, -1> m_baseVertices;` — the base vertices
- L113 _private member_ `std::vector<rt::LinearVertexModel<T>> m_regionModels;` — the linear model per region: dR * (1 + dscale) * (base + modes * params) + dt
- L116 _private member_ `std::vector<Eigen::Vector3<T>> m_centerOfGravityPerRegion;` — gravity center of each region
- L119 _private member_ `std::vector<std::string> m_patchNames;` — names of regions
- L122 _private member_ `std::vector<std::vector<std::tuple<int, int, T>>> m_globalBlendMatrix;` — for each vertex, this points to all regions with region index, vertex within region, and weight.
- L125 _private member_ `std::shared_ptr<TaskThreadPool> m_threadPool;` — thread pool for parallelization

#### class `PatchBlendModel::State`  
`template <class T> class PatchBlendModel<T>::State`  
_L130-207_
- L133 _public prototype_ `State() = default;`
- L134 _public prototype_ `State(int numPatches);`
- L135 _public prototype_ `~State() = default;`
- L136 _public prototype_ `State(const State&) = default;`
- L137 _public prototype_ `State(State&&) = default;`
- L138 _public prototype_ `State& operator=(const State&) = default;`
- L139 _public prototype_ `State& operator=(State&&) = default;`
- L141 _public prototype_ `void Reset(const PatchBlendModel<T>& patchBlendModel);`
- L142 _public function_ `int NumPatches() const`
- L144 _public prototype_ `void CopyTransforms(const State& other);`
- L145 _public prototype_ `void CopyPcaWeights(const State& other);`
- L147 _public function_ `void SetPatchScale(int id, T scale)`
- L148 _public function_ `T PatchScale(int id) const`
- L149 _public function_ `const std::vector<T>& PatchScales() const`
- L151 _public function_ `void SetPatchTranslation(int id, const Eigen::Vector3<T>& t)`
- L152 _public function_ `Eigen::Vector3<T> PatchTranslation(int id) const`
- L154 _public function_ `void SetPatchRotation(int id, const Eigen::Quaternion<T>& q)`
- L155 _public function_ `Eigen::Quaternion<T> PatchRotation(int id) const`
- L157 _public function_ `void SetPatchRotationEulerDegrees(int id, const Eigen::Vector<T, 3>& eulerXYZ)`
- L158 _public function_ `Eigen::Vector<T, 3> PatchRotationEulerDegrees(int id) const`
- L160 _public function_ `void SetPatchPcaWeights(int id, const Eigen::VectorX<T>& w)`
- L161 _public function_ `const Eigen::VectorX<T>& PatchPcaWeights(int id) const`
- L163 _public function_ `void SetPatchVertexDeltas(int id, const Eigen::Matrix<T, 3, -1>& vertexDeltas)`
- L164 _public function_ `const Eigen::Matrix<T, 3, -1>& PatchVertexDeltas(int id) const`
- L165 _public prototype_ `void ResetPatchVertexDeltas();`
- L166 _public prototype_ `void ResetPatchVertexDeltas(int id);`
- L167 _public prototype_ `bool HasPatchVertexDeltas() const;`
- L168 _public prototype_ `bool HasPatchVertexDeltas(int id) const;`
- L170 _public prototype_ `void BakeVertexDeltas(const Eigen::Matrix<T, 3, -1>& vertexDeltas, const PatchBlendModel<T>& patchBlendModel);` — bake the global vertex deltas to each patch
- L172 _public prototype_ `Eigen::Matrix<T, 3, -1> EvaluateVertexDeltas(const PatchBlendModel<T>& patchBlendModel) const;` — evaluate the global vertex deltas
- L176 _public prototype_ `void SymmetrizeRegions(const std::vector<int>& patchSymmetries, bool symmetrizeTransform, bool symmetrizePca, const PatchBlendModel<T>& patchBlendModel, const std::vector<int>& vertexSymmetries);` — symmetrize all regions as defined by @p patchSymmetries.
- L179 _public prototype_ `void SymmetricRegionCopy(const std::vector<int>& patchSymmetries, int regionId, bool includingPcaWeights);` — copy rotation/translation/scale (and optionally pca weights) from @p regionId to its symmetric counterpart as defined by @p patchSymmetries
- L182 _public prototype_ `Eigen::VectorX<T> ConcatenatePatchPcaWeights() const;` — concatenate all pca weights of all patches into vector.
- L185 _public prototype_ `void SetConcatenatedPatchPcaWeights(const Eigen::VectorX<T>& w);` — set the concatenated pca weights.
- L188 _public prototype_ `JsonElement ToJson() const;` — serialize to json
- L191 _public prototype_ `void FromJson(const JsonElement& json);` — deserialize from json
- L194 _public prototype_ `Eigen::VectorX<T> SerializeToVector() const;` — number of regions, regionsScale, regionRotations, regionTranslation, numberOfModesPerRegion, regionPcaWeights
- L196 _public prototype_ `void DeserializeFromVector(const Eigen::VectorX<T>& vector);`
- L199 _private member_ `std::vector<T> regionScales;`
- L200 _private member_ `std::vector<Eigen::Quaternion<T>> regionRotations;`
- L201 _private member_ `std::vector<Eigen::Vector3<T>> regionTranslations;`
- L202 _private member_ `std::vector<Eigen::VectorX<T>> regionPcaWeights;`
- L203 _private member_ `std::vector<Eigen::Matrix3X<T>> regionVertexDeltas;`

#### class `PatchBlendModel::OptimizationState`  
`template <class T> class PatchBlendModel<T>::OptimizationState`  
_L210-321_
- L213 _public prototype_ `OptimizationState() = default;`
- L214 _public prototype_ `~OptimizationState() = default;`
- L215 _public prototype_ `OptimizationState(OptimizationState&&) = default;`
- L216 _public prototype_ `OptimizationState& operator=(OptimizationState&&) = default;`
- L218 _public prototype_ `void CopyFromState(const PatchBlendModel<T>::State& state);`
- L219 _public prototype_ `void CopyToState(PatchBlendModel<T>::State& state) const;`
- L221 _public prototype_ `PatchBlendModel<T>::State CreateState() const;`
- L223 _public prototype_ `int NumParameters() const;`
- L224 _public prototype_ `void ResetParameters(const PatchBlendModel<T>& patchBlendModel);`
- L226 _public prototype_ `int NumPatches() const;`
- L229 _public prototype_ `void SetModelParameters(const Eigen::VectorX<T>& parameters);` — Set current model parameters
- L232 _public prototype_ `T PatchScale(int id) const;` — Get patch scale for specified patch id
- L235 _public prototype_ `Eigen::Vector3<T> PatchTranslation(int id) const;` — Get patch translation for specified patch id
- L238 _public prototype_ `Eigen::Vector3<T> PatchRotation(int id) const;` — Get patch rotation for specified patch id
- L241 _public prototype_ `Eigen::VectorX<T> PatchPcaWeights(int id) const;` — Get patch pca weights for specified patch id
- L243 _public prototype_ `const Eigen::VectorX<T>& GetModelParameters() const;`
- L246 _public prototype_ `void SetPatchScale(int id, T scale);` — Set patch scale for specified patch id
- L249 _public prototype_ `void SetPatchTranslation(int id, const Eigen::Vector3<T>& translation);` — Set patch translation for specified patch id
- L252 _public prototype_ `void SetPatchRotation(int id, const Eigen::Vector3<T>& rotation);` — Set patch center of gravity for specified patch id
- L255 _public prototype_ `int NumPcaModesForPatch(int id) const;` — Get number of modes for patch at specified patch id
- L258 _public prototype_ `void SetPatchPcaWeights(int id, const Eigen::VectorX<T>& weights);` — Set patch pca weights for specified patch id
- L260 _public prototype_ `void ClearFixedPatch();`
- L262 _public prototype_ `int FixedPatch() const;`
- L264 _public prototype_ `void SetFixedPatch(int patchId);`
- L266 _public function_ `bool OptimizeScale() const`
- L267 _public function_ `void SetOptimizeScale(bool _optimizeScale)`
- L269 _public prototype_ `void MakeRotationConstantForPatch(int patchId);`
- L271 _public prototype_ `void MakeTranslationConstantForPatch(int patchId);`
- L273 _public prototype_ `void MakeScaleConstantForPatch(int patchId);`
- L275 _public prototype_ `void RemoveConstraintsOnVariables();`
- L278 _public prototype_ `void TransformPatches(const Affine<T, 3, 3>& aff);` — Transform all patches
- L281 _public prototype_ `void TransformPatch(const Affine<T, 3, 3>& aff, int patchId);` — Transform patch
- L284 _public prototype_ `void BakeRotationLinearization();` — Bake the rotation linearization
- L286 _public function_ `const std::vector<rt::LinearVertexModel<T>>& TransformedRegionModels() const`
- L288 _public function_ `int PatchVariableOffset(int patchId) const`
- L292 _private member_ `VectorVariable<T> allVariables = VectorVariable<T>(0);` — variable containing all variables: coefficients for region PCA models, rotation, translation, and scale
- L295 _private member_ `std::set<int> constantIndices;` — which indices are constant
- L298 _private member_ `std::vector<int> regionVariableOffsets;` — the offset for each region into allVariables
- L301 _private member_ `std::vector<Eigen::Quaternion<T>> regionRotations;` — the rotation per region
- L307 _private member_ `std::vector<rt::LinearVertexModel<T>> transformedRegionModels;` — The linear model after rotation and scale have been applied. rotated = (dR * R) * (scale + dscale) * (base + modes * params) + (T + dt)
- L310 _private member_ `int numNonZerosVertexJacobian = 0;` — cache size of sparse matrices
- L311 _private member_ `int numNonZerosSmoothnessJacobian = 0;`
- L314 _private member_ `int fixedRegion = -1;` — which region should stay "fixed"
- L317 _private member_ `bool optimizeScale = false;` — whether to optimize scale

#### class `PatchBlendModelDataManipulator`  
`template<class T> class PatchBlendModelDataManipulator`  
_L325-397_
- desc: Class made to extract joint deltas and mesh vertices from the patch blend model output.
- L330 _public function_ `PatchBlendModelDataManipulator(const dna::Reader* dnaReader)`
- L349 _public function_ `int GetNumMeshes() const` — @return the number of meshes for the patch blend model
- L352 _public function_ `Eigen::Matrix3X<T> GetJointDeltas(const Eigen::Matrix3X<T> &patchModelData) const` — Get the joint detlas
- L358 _public function_ `Eigen::Matrix3X<T> GetMeshVertices(const Eigen::Matrix3X<T> &patchModelData, int meshIndex) const` — Get the mesh vertices for mesh @p meshName
- L365 _public function_ `Eigen::Matrix3X<T> GetMeshVertices(const Eigen::Matrix3X<T> &patchModelData, const std::string& meshName) const` — Get the mesh vertices for mesh @p meshName
- L370 _public function_ `std::pair<int, int> GetRangeForMeshIndex(int meshIndex) const`
- L376 _public function_ `std::pair<int, int> GetRangeForMesh(const std::string& meshName) const`
- L381 _public function_ `const std::map<std::string, int>& GetMeshNameToIdxMapping() const`
- L386 _public function_ `bool HasMesh(const std::string& meshName) const`
- L389 _public function_ `int Size() const` — @returns the number of joints + vertices
- L392 _public function_ `int NumJoints() const` — @returns the number of joints
- L395 _private member_ `std::vector<int> m_startingIndices;` — Indices that define the start vertex id for each data asset
- L396 _private member_ `mutable std::map<std::string, int> m_meshNameToIdxInRigGeometry;` — Mapping of mesh names and their indices in rig geometry

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/RegionBlendModel.h` (Private)


#### class `RegionBlendModel`  
`template <class T> class RegionBlendModel`  
_L23-82_
- desc: RegionBlendModel models the geometry of a face as Vertices = MeanShape + A * x where A is the matrix of weighted deltas between characters and archetype per character per region, and x are the mixing parameters.
- L26 _public prototype_ `RegionBlendModel();`
- L27 _public prototype_ `~RegionBlendModel();`
- L28 _public prototype_ `RegionBlendModel(RegionBlendModel&& other);`
- L29 _public prototype_ `RegionBlendModel(const RegionBlendModel& other);`
- L30 _public prototype_ `RegionBlendModel& operator=(RegionBlendModel&& other);`
- L31 _public prototype_ `RegionBlendModel& operator=(const RegionBlendModel& other);`
- L33 _public prototype_ `const std::vector<std::string>& RegionNames() const;`
- L34 _public prototype_ `void SetRegionNames(const std::vector<std::string>& regionNames);`
- L35 _public prototype_ `void SetRegion(const std::string& regionName, const Vector<T>& regionData);`
- L36 _public prototype_ `void SetRegions(const std::map<std::string, Vector<T>>& regions);`
- L38 _public prototype_ `const std::vector<std::string>& CharacterNames() const;`
- L39 _public prototype_ `void SetCharacterNames(const std::vector<std::string>& charNames);`
- L40 _public prototype_ `void SetCharacter(const std::string& charName, const Eigen::Matrix<T, 3, -1>& charData);`
- L41 _public prototype_ `void SetCharacters(const std::map<std::string, Eigen::Matrix<T, 3, -1>>& characters);`
- L43 _public prototype_ `void SetArchetype(const Eigen::Matrix<T, 3, -1>& archetype);`
- L45 _public prototype_ `void SetSymmetricRegions(const std::vector<std::pair<std::string, std::string>>& symmetricRegions);`
- L47 _public prototype_ `void Generate();`
- L50 _public prototype_ `int NumParameters() const;` — @returns the number of parameters of the model
- L53 _public prototype_ `int NumRegions() const;` — @returns the number of regions in the model
- L56 _public prototype_ `int NumVertices() const;` — @returns the number of vertices in the model
- L59 _public prototype_ `int NumCharacters() const;` — @returns the number of characters in the model
- L62 _public prototype_ `Vector<T> DefaultParameters() const;` — @returns default parameters resulting in the archetype
- L65 _public prototype_ `SparseMatrixConstPtr<T> ModelMatrix() const;` — @returns the model matrix
- L68 _public prototype_ `Eigen::Matrix<T, 3, -1> Evaluate(const Vector<T>& parameters) const;` — @returns the evaluated model for the parameters
- L71 _public prototype_ `DiffDataMatrix<T, 3, -1> Evaluate(const DiffData<T>& parameters) const;` — @returns the evaluated model for the parameters
- L74 _public prototype_ `DiffData<T> EvaluateRegularization(const DiffData<T>& parameters) const;` — @returns evaluates the regularization on the parameters
- L76 _public prototype_ `void PrintRegionSum(const DiffData<T>& parameters) const;`
- L77 _public prototype_ `const std::vector<std::pair<int, int>>& GetSymmetricRegions() const;`
- L81 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/RigAndControlsOptimization.h` (Private)


#### class `RigAndControlsOptimization`  
`template <class T> class RigAndControlsOptimization`  
_L19-85_
- L22 _public prototype_ `RigAndControlsOptimization();`
- L23 _public prototype_ `~RigAndControlsOptimization();`
- L24 _public prototype_ `RigAndControlsOptimization(RigAndControlsOptimization&& other);`
- L25 _public prototype_ `RigAndControlsOptimization(const RigAndControlsOptimization& other) = delete;`
- L26 _public prototype_ `RigAndControlsOptimization& operator=(RigAndControlsOptimization&& other);`
- L27 _public prototype_ `RigAndControlsOptimization& operator=(const RigAndControlsOptimization& other) = delete;`
- L33 _public prototype_ `void SetRig(dna::BinaryStreamReader* dnaStream);` — Set RigGeometry and RigLogic using a dna binary stream reader. @param dnaStream  dna binary file stream
- L39 _public prototype_ `void SetMeshes(std::vector<std::string> meshNames);` — Set topology @param mesh  map of expected mesh topologies
- L45 _public prototype_ `void SetActiveControls(std::vector<std::string> activeControls);` — Set active GUI controls @param activeControls GUI names of active controls
- L57 _public prototype_ `void OptimizeRigAndControls(std::map<std::string, Eigen::Matrix<T, 3, -1>> targetGeometry, Eigen::VectorX<T> guiControls, std::map<std::string, Vector<T>> vertexWeights, T strainWeight, T bendingWeight, int numIterations = 20);` — Runtime joint rig optimization. @param targetGeometry           The definition of the target geometry @param vertexWeights              The weight of each vertex in the loss function @param rotationRegularization     Regularization on the delta of the joint rotation relative to the rest rig state. @param translationRegularization  Regularization of the delta of the joint translation relative to the rest rig state. @param strainWeight               How much to regularize strain between the evaluated vertices and the target vertices @param bendingWeight              How much to regularize bending between the evaluated vertices and the target vertices @param numIterations              The number of iterations for the optimization
- L65 _public prototype_ `Eigen::VectorX<T> GetControls();` — Get the current controls
- L68 _public prototype_ `Eigen::VectorX<T> GetJointMatrixNonzeros();` — Get the current joint matrix parameters
- L71 _public prototype_ `Eigen::VectorX<T> GetJointState();` — Get the joint deltas from the current state
- L74 _public prototype_ `SparseMatrix<T> GetJointMatrixState();` — Get the joint deltas from the current state
- L80 _public prototype_ `void SetDegreesOfFreedom(bool jointMatrix, bool controls);` — Sets the degrees of freedom: either optimize controls, joint matrix nonzeros, or both
- L84 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

#### struct `RigAndControlsFittingParams`  
`struct RigAndControlsFittingParams`  
_L91-98_
- desc: @brief RigAndControlsFitting class parameters for joints fitting
- L93 _public member_ `bool m_fixJointMatrix = false;` — bool to indicate should the optimization fixes the joint matrix
- L94 _public member_ `bool m_fixPsdControls = true;` — bool to indicate should the optimization fix the psd controls
- L95 _public member_ `int m_numIterations = 2;` — number of iterations for the joints fitting optimizer
- L96 _public member_ `float m_bendingWeight = 0.0f;` — joints bending constraint weight
- L97 _public member_ `float m_strainWeight = 0.0f;` — joints strain constraint weight

#### class `RigAndControlsFitting`  
`template <class T> class RigAndControlsFitting`  
_L109-151_
- desc: @brief Joint rig fitting class. Can be used to calculate joint deltas needed to fit a geometry. Works only on head mesh on LOD0 JointRigOptimizer class is used to calculate the joints translations and rotations that will deform the input geometry to match the deformed one. Gauss-Newton optimizer is used. @note Works only on head mesh on LOD0
- L112 _private member_ `std::unique_ptr<RigAndControlsOptimization<T>> m_pRigOptimization;` — Model used to optimize the rig and controls with the goal of
- L116 _private member_ `dna::BinaryStreamReader* m_pDNAResource;` — DNA file used to initialize the joints optimization
- L119 _public prototype_ `RigAndControlsFitting() = default;`
- L120 _public prototype_ `~RigAndControlsFitting() = default;`
- L122 _public prototype_ `RigAndControlsFitting(RigAndControlsFitting&&) = delete;`
- L123 _public prototype_ `RigAndControlsFitting(RigAndControlsFitting&) = delete;`
- L124 _public prototype_ `RigAndControlsFitting& operator=(RigAndControlsFitting&&) = delete;`
- L125 _public prototype_ `RigAndControlsFitting& operator=(const RigAndControlsFitting&) = delete;`
- L134 _public prototype_ `void Setup(dna::BinaryStreamReader* dnaResource, std::vector<std::string> activeControls);` — @brief Setup the joint rig optimization model @param[in] dnaResource        - DNA resource that is used to setup the joint optimization @param[in] rigGeometry        - Rig geometry model that is used to setup the joint optimization @param[in] currentRigState    - Rig state used to get the
- L147 _public prototype_ `SparseMatrix<T> Optimize(const Eigen::Matrix<T, 3, -1>& targetGeometry, const VertexWeights<T>& fittingMask, const Eigen::VectorX<T> guiControls, const RigAndControlsFittingParams& params);` — @brief Optimize the joint matrix and/or PSD controls so that the resulting mesh is the closes (w.r.t. given constraints) to the target geometry @param[in] targetGeometry    - Target geometry to fit to @param[in] fittingMask       - Mask that selects the vertices that can be moved by the optimization @param[in] guiControls       - GUI controls to initialize the optimization with @param[in] params            - Joints optimization parameters @return Updated joint matrix

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/RigFitting.h` (Private)


#### struct `NeutralPoseFittingParams`  
`template <class T> struct NeutralPoseFittingParams`  
_L13-48_
- L16 _public member_ `T modelRegularization { T(0.1) };` — @regularization
- L19 _public member_ `T patchSmoothness { T(0.5) };` — @patch smoothness
- L22 _public member_ `T p2pWeight { T(1) };` — @point-to-point weight
- L25 _public member_ `bool modelFitOptimizeScale { false };` — @whether to optimize for scale along with mode weights
- L28 _public member_ `bool modelFitOptimizeRigid { true };` — @whether to optimize global rigid transform in model fit
- L31 _public member_ `bool rigidFitOptimizeScale { true };` — @whether to optimize scale in rigid fit
- L34 _public member_ `bool rigidFitOptimizeTranslation { true };` — @whether to optimize translation in rigid fit
- L37 _public member_ `bool rigidFitOptimizeRotation { true };` — @whether to optimize rotation in rigid fit
- L40 _public member_ `int numIterations { 5 };` — @number of iterations
- L43 _public member_ `int fixedRegion { -1 };` — @fixed region
- L45 _public prototype_ `void SetFromConfiguration(const Configuration& config);`
- L47 _public prototype_ `Configuration ToConfiguration() const;`

#### class `NeutralPoseFittingOptimization`  
`template <class T> class NeutralPoseFittingOptimization`  
_L51-68_
- L55 _public prototype_ `static Affine<T, 3, 3> RegisterPose(const Eigen::Matrix<T, 3, -1>& targetData, const Eigen::VectorXi& targetToModelDataMapping, const Affine<T, 3, 3> toTargetTransform, const std::shared_ptr<PatchBlendModel<T>>& model, typename PatchBlendModel<T>::OptimizationState& modelState, const NeutralPoseFittingParams<T>& params, const Eigen::VectorX<T>& mask);` — @solve to target vertices
- L63 _public prototype_ `static std::pair<T, Affine<T, 3, 3>> RegisterPose(const Eigen::Matrix<T, 3, -1>& targetData, const std::shared_ptr<IdentityBlendModel<T>>& model, const NeutralPoseFittingParams<T>& params, const Eigen::VectorX<T>& mask, Eigen::VectorX<T>& result);`

#### class `FastPatchModelFitting`  
`template <class T> class FastPatchModelFitting`  
_L72-116_
- desc: fast fitting of the patch model using projection
- L83 _public prototype_ `void Init(const std::shared_ptr<const PatchBlendModel<T>>& patchModel, const std::shared_ptr<TaskThreadPool>& taskThreadPool);`
- L85 _public prototype_ `void UpdateMask(const VertexWeights<T>& mask);`
- L87 _public prototype_ `void UpdateRegularization(T regularization);`
- L89 _public prototype_ `void Fit(typename PatchBlendModel<T>::State& state, const Eigen::Matrix3X<T>& vertices, const Settings& settings);`
- L91 _public prototype_ `Eigen::VectorX<T> FitRegion(int regionIndex, const Eigen::Matrix3X<T>& vertices) const;`
- L94 _private prototype_ `void UpdateSolveData();`
- L97 _private member_ `std::shared_ptr<const PatchBlendModel<T>> m_patchModel;`
- L99 _private member_ `std::shared_ptr<TaskThreadPool> m_taskThreadPool;`
- L102 _private member_ `T m_regularization = T(1);` — regularization
- L105 _private member_ `VertexWeights<T> m_mask;` — weights
- L115 _private member_ `std::vector<SolveData> m_solveData;` — precalculated solve data

#### struct `FastPatchModelFitting::Settings`  
`struct Settings`  
_L75-80_
- L77 _public member_ `bool withScale = true;`
- L78 _public member_ `int fixedRegion = 19;` — neck (TODO: specify by name?)
- L79 _public member_ `T regularization = T(1);`

#### struct `FastPatchModelFitting::SolveData`  
`struct SolveData`  
_L108-112_
- desc: solve data per region
- L109 _public member_ `std::vector<int> vIDs;`
- L110 _public member_ `Eigen::Matrix<T, 3, -1> base;`
- L111 _public member_ `Eigen::MatrixX<T> AtAinvAt;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/Stabilization.h` (Private)


#### Free symbols / members of external scopes

- L19 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::mps) const std::vector<std::tuple<float, float>> stabilizationCyclesAlphas` — Stabilization alpha parameters, each tuple containing alphaPos and alphaVel for one stabilization cycle
- L30 _function_ `template <class T> int sgn(T val)`
- L33 _function_ `template <class T> T PolyPenalty(const T& x)`
- L48 _function_ `template <class T> T PolyPenaltyDerivative(const T& x)`
- L63 _function_ `template <class T> T Sigmoid(const T& x)`
- L66 _function_ `template <class T> T SigmoidDerivative(const T& x)`
- L68 _variable_ `const double s = 3.5;`
- L71 _function_ `template <class T> T SigmoidPenalty(const T& x)`
- L74 _function_ `template <class T> T SigmoidPenaltyDerivative(const T& x)`
- L77 _function_ `template <class T> T PenaltyFunction(const T& x)`
- L84 _function_ `template <class T> T PenaltyFunctionDerivative(const T& x)`
- L91 _function_ `template <class T> DiffDataMatrix<T, 3, -1> ModePursuitPenalty(const DiffDataMatrix<T, 3, -1>& x, const T alpha)`
- L129 _function_ `template <class T> std::vector<DiffData<T>> CubicCatmullRomSegment(const DiffData<T>& a, const DiffData<T>& b, const DiffData<T>& c, const DiffData<T>& d, const int nInterval)`
- L154 _function_ `template <class T> std::vector<DiffData<T>> CubicCatmullRom(std::vector<DiffData<T>>&& controlPoints, const int nInterval)` — Calculates a cubic catmul rom from the input control points. The input vector of control points is moved from and is in an unknown state
- L191 _function_ `template <class T> std::vector<DiffDataMatrix<T, 3, -1>> CreateDDMVector(const int size)`
- L202 _function_ `template <class T> std::vector<Vector<T>> Stabilize(const Eigen::Matrix<T, 3, -1>& neutral, const std::vector<Eigen::Matrix<T, 3, -1>>& scene, std::vector<Vector<T>> dqs_neutralToScene, const int nCycles, const int nInterval, const int nIterations)`
- L260 _function_ `auto EvaluateSpline = [&](Context<T>* context)` (scope `Stabilize`)
- L277 _function_ `std::function<DiffData<T>(Context<T>*)> evaluationFunction = [&](Context<T>* context)` (scope `Stabilize`)
- L283 _function_ `taskThreadPool->AddTaskRangeAndWait(nFramesExtended, [&](int start, int end) { for (int i = start; i < end; ++i) { const DiffData<T> dqDD_sceneToNeutralCentered = DualQuaternionQuatConjugateDiff<T>(dqsDD_neutralCenteredToScene_ext[i]); sceneStabilizedDDM_ext[i] = DualQuaternionShapeTransformDiff(dqDD_sceneToNeutralCentered, scene_ext[i]); } });` (scope `Stabilize::__anonef7852ce0202`)
- L297 _function_ `taskThreadPool->AddTaskRangeAndWait(nFramesExtended, [&](int start, int end) { for (int i = start; i < end; ++i) { DiffDataMatrix<T, 3, -1> posDiff = sceneStabilizedDDM_ext[i] - neutralCentered_DDM; posLosses[i] = ModePursuitPenalty<T>(posDiff, alphaPos); } });` (scope `Stabilize::__anonef7852ce0202`) — Position loss
- L306 _function_ `taskThreadPool->AddTaskRangeAndWait(nFramesExtended - 1, [&](int start, int end) { for (int i = start; i < end; ++i) { DiffDataMatrix<T, 3, -1> pointVel = sceneStabilizedDDM_ext[i + 1] - sceneStabilizedDDM_ext[i]; velLosses[i] = ModePursuitPenalty<T>(pointVel, alphaVel); } });` (scope `Stabilize::__anonef7852ce0202`) — Velocity loss
- L354 _function_ `template <class T> std::tuple<std::vector<Eigen::Matrix<float, 5, -1>>, std::vector<Eigen::Matrix<float, 5, -1>>> GenerateLossMapsData(const Eigen::Matrix<T, 3, -1>& model, const Eigen::Matrix<T, 3, -1>& neutral, const std::vector<Eigen::Matrix<T, 3, -1>>& scene, const std::vector<Vector<T>>& dqs_sceneToNeutral, const int nCycles, const int resU, const int resV)`
- L396 _function_ `taskThreadPool->AddTaskRangeAndWait(nFrames, [&](int start, int end) { for (int i = start; i < end; ++i) { DiffDataMatrix<T, 3, -1> posDiff = sceneStabilizedDDM[i] - neutralDDM; posLosses[i] = ModePursuitPenalty<T>(posDiff, alphaPos); } });` (scope `GenerateLossMapsData`)
- L406 _function_ `taskThreadPool->AddTaskRangeAndWait(nFrames - 1, [&](int start, int end) { for (int i = start; i < end; ++i) { DiffDataMatrix<T, 3, -1> pointVel = sceneStabilizedDDM[i + 1] - sceneStabilizedDDM[i]; velLosses[i] = ModePursuitPenalty<T>(pointVel, alphaVel); } });` (scope `GenerateLossMapsData`)
- L421 _function_ `taskThreadPool->AddTaskRangeAndWait(nFrames, [&](int start, int end) { for (int frame = start; frame < end; ++frame) { Eigen::Matrix<float, 5, -1>& mapData = posLossMapsData[frame]; mapData = Eigen::Matrix<float, 5, -1>(5, nVertices); const Vector<T>& posLossVec = posLosses[frame].Value(); for (int vertex = 0; vertex < nVertices; ++vertex) { const float x = modelCentered(0, vertex); const float y = modelCentered(1, vertex); mapData(0, vertex) = (x - xMin) / (xMax - xMin) * resU;` (scope `GenerateLossMapsData`)
- L449 _function_ `taskThreadPool->AddTaskRangeAndWait(nFrames - 1, [&](int start, int end) { for (int frame = start; frame < end; ++frame) { Eigen::Matrix<float, 5, -1>& mapData = velLossMapsData[frame]; mapData = Eigen::Matrix<float, 5, -1>(5, nVertices); const Vector<T>& velLossVec = velLosses[frame].Value(); for (int vertex = 0; vertex < nVertices; ++vertex) { const float x = modelCentered(0, vertex); const float y = modelCentered(1, vertex); mapData(0, vertex) = (x - xMin) / (xMax - xMin) * resU;` (scope `GenerateLossMapsData`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/SymmetryMapping.h` (Private)


#### class `SymmetryMapping`  
`class SymmetryMapping`  
_L18-82_
- desc: Simple helper class returning symmetry information
- L21 _public prototype_ `SymmetryMapping() = default;`
- L22 _public function_ `SymmetryMapping(const Eigen::VectorXi& symmetries) : m_symmetries(symmetries)`
- L30 _public function_ `bool Load(const std::string& filename)`
- L37 _public function_ `bool Load(const JsonElement& jSymmetry)`
- L59 _public function_ `int NumSymmetries() const`
- L61 _public function_ `int Map(int vID) const`
- L63 _public function_ `bool IsSelfSymmetric(int vID) const`
- L65 _public function_ `const Eigen::VectorXi& Symmetries() const`
- L67 _public function_ `static bool CheckSymmetries(const Eigen::VectorXi& symmetries)`
- L81 _private member_ `Eigen::VectorXi m_symmetries;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/TemplateConstraints.h` (Private)


#### class `TemplateConstraints`  
`template <class T> class TemplateConstraints`  
_L16-55_
- L37 _public prototype_ `TemplateConstraints() = default;`
- L38 _public prototype_ `~TemplateConstraints() = default;`
- L39 _public prototype_ `TemplateConstraints(TemplateConstraints&&) = default;`
- L40 _public prototype_ `TemplateConstraints(TemplateConstraints&) = delete;`
- L41 _public prototype_ `TemplateConstraints& operator=(TemplateConstraints&&) = default;`
- L42 _public prototype_ `TemplateConstraints& operator=(const TemplateConstraints&) = delete;`
- L44 _public prototype_ `void SetSourceTopology(const Mesh<T>& mesh, const std::vector<int>& srcMask);`
- L46 _public prototype_ `void SetTargetTopology(const Mesh<T>& mesh, const std::vector<int>& targetMask);`
- L48 _public prototype_ `std::shared_ptr<const Data> SetupCorrespondences(const Eigen::Matrix<T, 3, -1>& srcVertices, const Eigen::Matrix<T, 3, -1>& targetVertices) const;`
- L51 _protected member_ `std::vector<int> m_srcMask;`
- L52 _protected member_ `Eigen::Matrix<int, 3, -1> m_srcTriangles;`
- L53 _protected member_ `std::vector<int> m_targetMask;`
- L54 _protected member_ `Eigen::Matrix<int, 3, -1> m_targetTriangles;`

#### struct `TemplateConstraints::Data`  
`struct Data`  
_L19-34_
- L21 _public member_ `std::vector<int> srcIDs;`
- L22 _public member_ `std::vector<BarycentricCoordinates<T, 3>> targetTemplateBCs;`
- L23 _public member_ `Eigen::Matrix3X<T> templateDeltas;`
- L25 _public function_ `void Clear()`
- L32 _public prototype_ `DiffData<T> Evaluate(const DiffDataMatrix<T, 3, -1>& srcVertices, const DiffDataMatrix<T, 3, -1>& targetVertices) const;` — Evaluate template constraints

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/TemplateDescription.h` (Private)


#### class `TemplateDescription`  
`class TemplateDescription`  
_L24-151_
- desc: Class containing all template face specific data such as mesh symmetry information, landmark positions on the mesh, weight masks etc. The class does not contain any geometry/texture information for an individual.
- L27 _public prototype_ `TemplateDescription() = default;`
- L30 _public prototype_ `bool Load(const std::string& filenameOrData);` — Load data from either file or the data directly.
- L32 _public function_ `const Mesh<float>& Topology() const`
- L34 _public function_ `const Mesh<float>& TriangulatedTopology() const`
- L36 _public function_ `const SymmetryMapping& GetSymmetryMapping() const`
- L38 _public function_ `bool HasVertexWeights(const std::string& maskName) const`
- L39 _public prototype_ `const VertexWeights<float>& GetVertexWeights(const std::string& maskName) const;`
- L40 _public function_ `const std::map<std::string, VertexWeights<float>>& GetVertexWeights() const`
- L41 _public function_ `const std::map<std::string, VertexWeights<float>>& GetExpressionsFittingMasks() const`
- L42 _public prototype_ `const VertexWeights<float>& GetAssetVertexWeights(const std::string& assetName, const std::string maskName) const;`
- L43 _public prototype_ `const std::map<std::string, VertexWeights<float>>& GetAssetVertexWeights(const std::string& assetName) const;`
- L45 _public function_ `bool HasEdgeWeights(const std::string& edgeMapName) const`
- L46 _public prototype_ `const std::vector<std::tuple<int, int, float>>& GetEdgeWeights(const std::string& edgeMapName) const;`
- L48 _public prototype_ `const Mesh<float>& GetAssetTopology(const std::string& assetName) const;`
- L49 _public function_ `bool HasAssetTopology(const std::string& assetName) const`
- L50 _public function_ `bool HasAssetVertexWeights(const std::string& assetName) const`
- L51 _public prototype_ `bool HasAssetVertexWeights(const std::string& assetName, const std::string& maskName) const;`
- L53 _public function_ `bool HasAssetSymmetries(const std::string& assetName) const`
- L54 _public function_ `const SymmetryMapping& GetAssetSymmetryMapping(const std::string& assetName) const`
- L56 _public function_ `const MeshLandmarks<float>& GetMeshLandmarks() const`
- L57 _public function_ `const MeshLandmarks<float>& GetEyeLeftMeshLandmarks() const`
- L58 _public function_ `const MeshLandmarks<float>& GetEyeRightMeshLandmarks() const`
- L59 _public function_ `const MeshLandmarks<float>& GetTeethMeshLandmarks() const`
- L61 _public prototype_ `const MeshLandmarks<float>& GetAssetMeshLandmarks(const std::string& assetName) const;`
- L63 _public function_ `bool HasAssetTexture(const std::string& assetName) const`
- L64 _public prototype_ `const std::string& GetAssetTextureFilename(const std::string& assetName) const;`
- L66 _public function_ `const std::string& TextureFilename() const`
- L68 _public function_ `bool HasSubdivMesh() const`
- L69 _public function_ `const Mesh<float>& SubdivMesh() const`
- L70 _public function_ `const std::vector<std::tuple<int, int, float>>& SubdivStencilWeights() const`
- L72 _public function_ `const std::string& VolumetricModelDirname() const`
- L74 _public function_ `std::map<std::string, std::vector<std::string>> GetPredefinedInfluencesUpstream() const`
- L79 _public function_ `std::map<std::string, std::vector<std::string>> GetPredefinedInfluencesDownstream() const`
- L85 _private prototype_ `bool LoadJson(const std::string& jsonString, const std::string& baseDir, bool isFileBased);`
- L89 _private member_ `Mesh<float> m_topology;` — topology
- L92 _private member_ `Mesh<float> m_triangulatedTopology;` — the triangulated topology
- L95 _private member_ `SymmetryMapping m_symmetryMapping;` — symmetry mapping
- L98 _private member_ `std::map<std::string, VertexWeights<float>> m_vertexWeights;` — named weight maps
- L101 _private member_ `std::map<std::string, VertexWeights<float>> m_rigCalibExpressionsFittingMasks;` — named weight maps for expressions fitting
- L104 _private member_ `std::map<std::string, std::vector<std::tuple<int, int, float>>> m_edgeWeights;` — named edge maps where an edge map is a vector of tuples of form [vID0, vID1, edgeWeight]
- L107 _private member_ `MeshLandmarks<float> m_meshLandmarks;` — mesh landmark information
- L110 _private member_ `MeshLandmarks<float> m_eyeLeftMeshLandmarks;` — mesh landmark information for the left eye ball
- L113 _private member_ `MeshLandmarks<float> m_eyeRightMeshLandmarks;` — mesh landmark information for the right eye ball
- L116 _private member_ `MeshLandmarks<float> m_teethMeshLandmarks;` — mesh landmark information for the teeth
- L119 _private member_ `std::map<std::string, Mesh<float>> m_assetTopologies;` — asset meshes
- L122 _private member_ `std::map<std::string, std::map<std::string, VertexWeights<float>>> m_assetVertexWeights;` — asset weight maps
- L125 _private member_ `std::map<std::string, std::string> m_assetTextureFilename;` — per-asset texture filename
- L128 _private member_ `std::map<std::string, MeshLandmarks<float>> m_assetMeshLandmarks;` — asset mesh landmarks
- L131 _private member_ `std::map<std::string, SymmetryMapping> m_assetSymmetryMappings;` — asset symmetry mapping
- L134 _private member_ `std::string m_textureFilename;` — texture with the guide lines
- L137 _private member_ `Mesh<float> m_subdivMesh;` — subdiv mesh
- L143 _private member_ `std::vector<std::tuple<int, int, float>> m_subdivStencilWeights;` — Subdiv stencil weights mapping from subdiv vID to topology vID and weight. Format: [subdiv_vID, topology_vID, weight]. subdiv_vertices[subdiv_vID] = sum(topology_vertices[topology_vID] * weight)
- L146 _private member_ `std::string m_volumetricModelDirname;` — path to the directory containing the volumetric model of the template
- L149 _private member_ `std::map<std::string, std::vector<std::string>> m_predefinedInfluencedExpressionsUpstream;` — Expressions influenced by other expressions (predefined by hand)
- L150 _private member_ `std::map<std::string, std::vector<std::string>> m_predefinedInfluencedExpressionsDownstream;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/ThinPlateSplineWarper.h` (Private)


#### class `ThinPlateSplineWarper`  
`template <typename T, int D = 3> class ThinPlateSplineWarper`  
_L17-35_
- desc: Thin Plate Spline Warper class, templated on both scalar type and dimensionality of the input data https://user.engineering.uiowa.edu/~aip/papers/bookstein-89.pdf
- L23 _public prototype_ `ThinPlateSplineWarper(const Eigen::Matrix<T, D, -1>& sourcePoints, const Eigen::Matrix<T, D, -1>& targetPoints);` — Construct the warper from source points (D x n) and target points (D x n)
- L26 _public prototype_ `Eigen::Matrix<T, D, -1> Apply(const Eigen::Matrix<T, D, -1>& points) const;` — Warp a set of points
- L29 _private member_ `Eigen::Matrix<T, D, -1> m_sourcePoints;`
- L30 _private member_ `Eigen::Matrix<T, D, -1> m_targetPoints;`
- L31 _private member_ `Eigen::Matrix<T, -1, -1> m_weights;`
- L33 _private prototype_ `void ComputeWeights();`
- L34 _private prototype_ `Eigen::Matrix<T, -1, -1> ComputeKernel(const Eigen::Matrix<T, D, -1>& A, const Eigen::Matrix<T, D, -1>& B) const;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/UpdateHeadMeshSkinningWeightsFromBody.h` (Private)


#### struct `SkinningWeightUpdateParams`  
`template <class T> struct SkinningWeightUpdateParams`  
_L15-32_
- desc: a struct for passing parameters to the function below
- L19 _public member_ `SnapConfig<T> neckBodySnapConfig;` — the snap config for the neck seam for the current lod which maps between src vertex indices (on the combined body) to target vertex indices (on the head).
- L22 _public member_ `std::shared_ptr<VertexWeights<T>> headVertexSkinningWeightsMask;` — a shared pointer to vertex weights which defines a weight for each vertex on head_lod0_mesh and how much weight (0-1) should be given to the body skinning weights for each vertex
- L25 _public member_ `std::vector<std::pair<int, bool>> bodyFaceJointMapping;` — a vector for each combined body rig joint which gives the corresponding face rig joint index (or -1 if not present), and a flag set to true if there is a correspondence or false if not
- L28 _public member_ `std::vector<std::pair<int, bool>> faceBodyJointMapping;` — a vector for each face rig joint which gives the corresponding combined body rig joint index (or if no direct correspondence, contains the face rig parent joint id which maps directly to the body), and a flag set to true if there is a direct correspondence or false if not
- L31 _public member_ `std::map<int, std::vector<int>> faceRigChildrenMap;` — a map of joint index to a vector of joint indices which contains every descendant joint index for the original joint index

#### Free symbols / members of external scopes

- L49 _prototype_ `template <class T> void UpdateHeadMeshSkinningWeightsFromBody(const SparseMatrix<T>& skinningWeightsHead, const SparseMatrix<T>& skinningWeightsCombinedBody, const SkinningWeightUpdateParams<T>& skinningWeightUpdateParams, Eigen::Matrix<T, -1, -1>& updatedHeadSkinningWeightsDense, std::shared_ptr<TITAN_NAMESPACE::TaskThreadPool> taskThreadPool = TITAN_NAMESPACE::TaskThreadPool::GlobalInstance( true));` — Take the supplied skinning weights for head and body rigs, and update the head from the body for the specified mesh name to give updatedHeadSkinningWeightsDense as the output. This gives the results for a single mesh / lod. A neck blend mask is used to blend skinning weights from the neck (on the body) with those on the head, and the neck seam is snapped to exactly match the skinning weights on the body. Output weights are in a dense matrix. We assume that the first n rows of the combined body skinning weights correspond to identical vertices in the head mesh; for even head lods this will be the case, but for odd head lods this will not be the case, and special handling is needed to prepare the data for this function. Only the skinning weights corresponding to head vertices are used from skinningWeightsCombinedBody. @param[in] skinningWeightsHead: a sparse matrix of n head mesh vertices rows x n head mesh joints columns containing the original skinning weights for the head mesh @param[in] skinningWeightsCombinedBody: a sparse matrix of n combined body vertices rows x n combined body joints containing the skinning weights for the combined body @param[in] skinningWeightUpdateParams: a struct containing the parameters used to perform the calculation (see above) @param[out] updatedHeadSkinningWeightsDense: on completion contains a dense matrix containing the updated skinning weights for the head mesh for each vertex for each joint. Weights are normalized such that they sum to 1 f
- L69 _prototype_ `template <class T> void UpdateHeadMeshSkinningWeightsFromBody(const RigGeometry<T>& headRigGeometry, const std::vector<SparseMatrix<T>> & combinedBodySkinningWeights, const std::map<std::string, std::pair<int, SnapConfig<T>>>& neckBodySnapConfig, const std::vector<std::shared_ptr<VertexWeights<T>>>& headVertexSkinningWeightsMasks, const std::vector<std::pair<int, bool>>& bodyFaceJointMapping, const std::vector<std::pair<int, bool>>& faceBodyJointMapping, const std::map<int, std::vector<std::pair<bool, BarycentricCoordinates<T>>>>& barycentricCoordinatesForOddLods, std::vector<Eigen::Matrix<T, -1, -1>>& updatedHeadSkinningWeights, std::shared_ptr<TITAN_NAMESPACE::TaskThreadPool> taskThreadPool = TITAN_NAMESPACE::TaskThreadPool::GlobalInstance( true));` — Take the supplied head and combined body rigs, and update the head from the body to give updatedHeadSkinningWeightsMap as the output. Results are provided for the head mesh at each lod. A set of neck blend masks is used to blend skinning weights from the neck (on the body) with those on the head, and in each case the neck seam is snapped to exactly match the skinning weights on the body. Output weights are in a dense matrix for each lod. @param[in] headRigGeometry: the rig geometry of the head rig which we want the updated skinning weights for @param[in] combinedBodySkinningWeights: a vector of combined body skinning weights at each lod @param[in] neckBodySnapConfig: a set of snap configs defining the mapping between body and head for the neck seam at each lod @param[in] bodyFaceJointMapping: a vector for each combined body rig joint which gives the corresponding face rig joint index (or -1 if not present), and a flag set to true if there is a correspondence or false if not @param[in] faceBodyJointMapping: a vector for each face rig joint which gives the corresponding combined body rig joint index (or if no direct correspondence, contains the face rig parent joint id which maps directly to the body), and a flag set to true if there is a direct correspondence or false if not @params[in] barycentricCoordinatesForOddLods: a map of (face) lod number to a vector which must contain, for each ODD numbered lod, for each vertex in the previous face lod, i) a flag saying whether the ba

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/VertexWeights.h` (Private)


#### class `VertexWeights`  
`template <class T> class VertexWeights`  
_L19-89_
- desc: Simple helper class returning the weights per vertex, the indices of all non-zero vertices, or the indices and weights of all non-zero vertices.
- L22 _public prototype_ `VertexWeights() = default;`
- L23 _public prototype_ `~VertexWeights() = default;`
- L24 _public prototype_ `VertexWeights(VertexWeights&&) = default;`
- L25 _public prototype_ `VertexWeights(const VertexWeights&) = default;`
- L26 _public prototype_ `VertexWeights& operator=(VertexWeights&&) = default;`
- L27 _public prototype_ `VertexWeights& operator=(const VertexWeights&) = default;`
- L30 _public prototype_ `VertexWeights(int numVertices, T weightForAll);` — constructor of weights of size @p numVertices and weights @p weightForAll
- L33 _public prototype_ `VertexWeights(const JsonElement& json, const std::string& weightsName, int numVertices);` — constructor loading weights @p weightsName from json @p json targeting a mask of size @p numVertices
- L36 _public prototype_ `VertexWeights(const std::string& filename, const std::string& weightsName, int numVertices);` — constructor loading weights @p weightsName from file @p filename (either .json or .csv file) targeting a mask of size @p numVertices
- L39 _public prototype_ `VertexWeights(const Eigen::VectorX<T>& weights);` — constructor using weight @p weights
- L41 _public function_ `int NumVertices() const`
- L43 _public function_ `const Eigen::VectorX<T>& Weights() const`
- L45 _public function_ `const std::vector<int>& NonzeroVertices() const`
- L47 _public function_ `const std::vector<std::pair<int, T>>& NonzeroVerticesAndWeights() const`
- L50 _public prototype_ `void Save(JsonElement& json, const std::string& weightsName) const;` — Saves the vertex weights to a json structure using name @p weightsName
- L53 _public prototype_ `void Load(const JsonElement& json, const std::string& weightsName, int numVertices);` — Loads the vertex weights from a json dictionary with key @p weightsName targeting a mask of size @p numVertices
- L56 _public prototype_ `void Load(const std::string& filename, const std::string& weightsName, int numVertices);` — Loads the vertex weights @p weightsName from a file @p filename (either .json or .csv file) targeting a mask of size @p numVertices
- L59 _public prototype_ `static std::map<std::string, VertexWeights> LoadAllVertexWeights(const JsonElement& json, int numVertices);` — Loads all vertex weights from json file @p json targeting a mask of size @p numVertices
- L62 _public prototype_ `static std::map<std::string, VertexWeights> LoadAllVertexWeights(const std::string& fileOrDirectory, int numVertices);` — Loads all vertex weights from file or directory @p fileOrDirectory (either .json or directory of .csv files) targeting a mask of size @p numVertices
- L65 _public prototype_ `static void SaveToJson(const std::string& filename, const std::map<std::string, VertexWeights<T>>& vertexWeights);` — Saves all vertex weights @p vertexWeights to json file @p filename
- L68 _public prototype_ `static void SaveToDirectory(const std::string& dirname, const std::map<std::string, VertexWeights<T>>& vertexWeights);` — Saves all vertex weights @p vertexWeights to directory @p dirname as CSV files
- L71 _public prototype_ `void Invert();` — Inverts the vertex weights i.e. weight = 1 - weight
- L74 _public prototype_ `VertexWeights Inverted() const;` — @return vertex weights that are inverted i.e. weight = 1- weight
- L77 _public function_ `template <typename S> VertexWeights<S> Cast() const`
- L83 _private prototype_ `void CalculateNonzeroData();`
- L86 _private member_ `Eigen::VectorX<T> m_weights;`
- L87 _private member_ `std::vector<int> m_nonzeroVertices;`
- L88 _private member_ `std::vector<std::pair<int, T>> m_nonzeroVerticesAndWeights;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/deformation_models/DeformationModel.h` (Private)


#### class `DeformationModel`  
`template <class T> class DeformationModel`  
_L14-31_
- L17 _public prototype_ `DeformationModel() = default;`
- L18 _public function_ `virtual ~DeformationModel()`
- L21 _public prototype_ `virtual DiffDataMatrix<T, 3, -1> EvaluateVertices(Context<T>* context) = 0;` — Evaluates the vertices of the mesh
- L24 _public prototype_ `virtual Cost<T> EvaluateModelConstraints(Context<T>* context) = 0;` — Evaluates the model constraints such as per-vertex offsets, strain, identity regularization. Depends on the deformation model.
- L27 _public prototype_ `virtual const Configuration& GetConfiguration() const = 0;` — Returns the configuration parameters of this deformation model
- L30 _public prototype_ `virtual void SetConfiguration(const Configuration& config) = 0;` — Sets the configuration of the deformation model

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/deformation_models/DeformationModelIdentity.h` (Private)


#### class `DeformationModelIdentity`  
`template <class T> class DeformationModelIdentity : public DeformationModel<T>`  
_L13-56_
- inherits: `DeformationModel<T>`
- L16 _public prototype_ `DeformationModelIdentity();`
- L18 _public prototype_ `DeformationModelIdentity(DeformationModelIdentity&& other);`
- L19 _public prototype_ `DeformationModelIdentity(const DeformationModelIdentity& other) = delete;`
- L20 _public prototype_ `DeformationModelIdentity& operator=(DeformationModelIdentity&& other);`
- L21 _public prototype_ `DeformationModelIdentity& operator=(const DeformationModelIdentity& other) = delete;`
- L24 _public prototype_ `virtual DiffDataMatrix<T, 3, -1> EvaluateVertices(Context<T>* context) override final;` — inherited from DeformationModel
- L25 _public prototype_ `virtual Cost<T> EvaluateModelConstraints(Context<T>* context) override final;`
- L26 _public prototype_ `virtual const Configuration& GetConfiguration() const override final;`
- L27 _public prototype_ `virtual void SetConfiguration(const Configuration& config) override final;`
- L30 _public prototype_ `void LoadModel(const std::string& identityModelFileOrJsonString);` — Load the identity model
- L33 _public prototype_ `int NumParameters() const;` — @returns the number of parameters
- L36 _public prototype_ `void ResetParameters();` — Resets the model parameters to default.
- L39 _public prototype_ `const Vector<T>& ModelParameters() const;` — @returns the current model parameters
- L42 _public prototype_ `void SetModelParameters(const Vector<T>& params);` — @returns sets the current model parameters
- L45 _public prototype_ `Eigen::Matrix<T, 3, -1> DeformedVertices() const;` — Returns the deformed vertex positions without any rigid transformation
- L48 _public prototype_ `void SetRigidTransformation(const Affine<T, 3, 3>& affine);` — Set the current rigid transformation
- L51 _public prototype_ `Affine<T, 3, 3> RigidTransformation() const;` — Returns the current rigid transformation
- L55 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/deformation_models/DeformationModelRegionBlend.h` (Private)


#### class `DeformationModelRegionBlend`  
`template <class T> class DeformationModelRegionBlend final : public DeformationModel<T>`  
_L16-90_
- inherits: `DeformationModel<T>`
- L19 _public prototype_ `DeformationModelRegionBlend();`
- L21 _public prototype_ `DeformationModelRegionBlend(DeformationModelRegionBlend&& other);`
- L22 _public prototype_ `DeformationModelRegionBlend(const DeformationModelRegionBlend& other) = delete;`
- L23 _public prototype_ `DeformationModelRegionBlend& operator=(DeformationModelRegionBlend&& other);`
- L24 _public prototype_ `DeformationModelRegionBlend& operator=(const DeformationModelRegionBlend& other) = delete;`
- L27 _public prototype_ `virtual DiffDataMatrix<T, 3, -1> EvaluateVertices(Context<T>* context) override;` — inherited from DeformationModel
- L28 _public prototype_ `virtual Cost<T> EvaluateModelConstraints(Context<T>* context) override;`
- L29 _public prototype_ `virtual const Configuration& GetConfiguration() const override;`
- L30 _public prototype_ `virtual void SetConfiguration(const Configuration& config) override;`
- L33 _public prototype_ `void LoadModel(const std::string& regionBlendModelFile);` — Load the region blend model
- L36 _public prototype_ `int NumParameters() const;` — @returns the number of parameters
- L39 _public prototype_ `int NumVertices() const;` — @returns number of vertices.
- L42 _public prototype_ `void ResetParameters();` — Resets the model parameters to default.
- L45 _public prototype_ `const Vector<T>& ModelParameters() const;` — @returns the current model parameters
- L48 _public prototype_ `void SetModelParameters(const Vector<T>& params);` — @returns sets the current model parameters
- L51 _public prototype_ `Eigen::Matrix<T, 3, -1> DeformedVertices() const;` — @returns the deformed vertex positions without any rigid transformation
- L54 _public prototype_ `void SetRigidTransformation(const Affine<T, 3, 3>& affine);` — Set the current rigid transformation
- L57 _public prototype_ `Affine<T, 3, 3> RigidTransformation() const;` — @returns the current rigid transformation
- L60 _public prototype_ `BoundedVectorVariable<T>* Variable();` — @returns the variable representing the parameters
- L63 _public prototype_ `T Scale() const;` — @returns the scale of the model
- L66 _public prototype_ `Eigen::Vector3<T> ScalingPivot() const;` — @returns the pivot which is used for scaling i.e. scaled_model = scale (model - scaling_pivot) + scaling_pivot
- L69 _public prototype_ `void SetModel(const std::shared_ptr<const RegionBlendModel<T>>& regionBlendModel);` — Set the region blend model (copy)
- L71 _public prototype_ `const std::vector<std::string>& RegionNames() const;`
- L72 _public prototype_ `void SetRegionNames(const std::vector<std::string>& regionNames);`
- L73 _public prototype_ `void SetRegion(const std::string& regionName, const Vector<T>& regionData);`
- L74 _public prototype_ `void SetRegions(const std::map<std::string, Vector<T>>& regions);`
- L76 _public prototype_ `const std::vector<std::string>& CharacterNames() const;`
- L77 _public prototype_ `void SetCharacterNames(const std::vector<std::string>& charNames);`
- L78 _public prototype_ `void SetCharacter(const std::string& charName, const Eigen::Matrix<T, 3, -1>& charData);`
- L79 _public prototype_ `void SetCharacters(const std::map<std::string, Eigen::Matrix<T, 3, -1>>& characters);`
- L81 _public prototype_ `void SetArchetype(const Eigen::Matrix<T, 3, -1>& archetype);`
- L83 _public prototype_ `void SetSymmetricRegions(const std::vector<std::pair<std::string, std::string>>& symmetricRegions);`
- L85 _public prototype_ `void GenerateModel();`
- L89 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/deformation_models/DeformationModelRigLogic.h` (Private)


#### class `DeformationModelRigLogic`  
`template <class T> class DeformationModelRigLogic final : public DeformationModel<T>`  
_L19-151_
- inherits: `DeformationModel<T>`
- L22 _public function_ `static constexpr const char* ConfigName()`
- L24 _public prototype_ `DeformationModelRigLogic();`
- L26 _public prototype_ `DeformationModelRigLogic(DeformationModelRigLogic&& other);`
- L27 _public prototype_ `DeformationModelRigLogic(const DeformationModelRigLogic& other);`
- L28 _public prototype_ `DeformationModelRigLogic& operator=(DeformationModelRigLogic&& other);`
- L29 _public prototype_ `DeformationModelRigLogic& operator=(const DeformationModelRigLogic& other);`
- L32 _public prototype_ `virtual DiffDataMatrix<T, 3, -1> EvaluateVertices(Context<T>* context) override;` — inherited from DeformationModel
- L33 _public prototype_ `virtual Cost<T> EvaluateModelConstraints(Context<T>* context) override;`
- L34 _public prototype_ `virtual const Configuration& GetConfiguration() const override;`
- L35 _public prototype_ `virtual void SetConfiguration(const Configuration& config) override;`
- L38 _public prototype_ `DiffDataMatrix<T, 3, -1> EvaluateVertices(Context<T>* context, int lod, int meshIndex, bool withRigid);` — Evaluates the vertices of the mesh at index @p meshIndex
- L41 _public prototype_ `std::vector<DiffDataMatrix<T, 3, -1>> EvaluateVertices(Context<T>* context, int lod, const std::vector<int>& meshIndices, bool withRigid);` — Evaluates the vertices of multiple meshes
- L44 _public prototype_ `void EvaluateVertices(Context<T>* context, int lod, const std::vector<int>& meshIndices, bool withRigid, typename RigGeometry<T>::State& state);` — Evaluates the vertices of multiple meshes
- L47 _public prototype_ `void EvaluateVertices(const DiffDataAffine<T, 3, 3>& rigid, const DiffData<T>& guiControls, int lod, const std::vector<int>& meshIndices, typename RigGeometry<T>::State& state) const;` — Evaluates the vertices of multiple meshes
- L54 _public prototype_ `DiffDataMatrix<T, 3, -1> EvaluateVertices(Context<T>* context, int lod, const char* meshName, bool withRigid);` — Evaluates the vertices of the mesh with name @p meshName
- L57 _public prototype_ `DiffData<T> EvaluateGuiControls(Context<T>* context);` — Evaluates the gui controls
- L60 _public prototype_ `Cost<T> EvaluateSymmetryConstraints(const DiffData<T>& guiControls) const;` — Evaluates the symmetry model constraint
- L63 _public prototype_ `Cost<T> EvaluateMutuallyExclusivePairConstraints(const DiffData<T>& guiControls);` — Evaluate the constraint for mutually exclusive pairs of GUI control activations
- L66 _public prototype_ `Cost<T> EvaluateMutuallyExclusiveTripleConstraints(const DiffData<T>& guiControls);` — Evaluate the constraint for mutually exclusive triples of GUI control activations ie not all three controls can be activated at the same time
- L69 _public prototype_ `void SetRig(const std::shared_ptr<const Rig<T>>& rig);` — Set the RigLogic and geometry (required)
- L72 _public prototype_ `const std::shared_ptr<const Rig<T>>& GetRig() const;` — Get the current rig
- L75 _public prototype_ `void SetRigLogicSolveControls(std::shared_ptr<const RigLogicSolveControls<T>> rigLogicSolveControls);` — Set the RigLogicSolveControls (optional - set to nullptr to use full riglogic)
- L78 _public prototype_ `void SetRigidTransformation(const Affine<T, 3, 3>& affine);` — Set the current rigid transformation
- L81 _public prototype_ `Affine<T, 3, 3> RigidTransformation() const;` — Returns the current rigid transformation
- L84 _public prototype_ `Eigen::Matrix<T, 3, -1> DeformedVertices(int meshIndex);` — Returns the deformed vertex positions for mesh @p meshIndex
- L87 _public prototype_ `Eigen::VectorX<T> GuiControls() const;` — @returns the current Gui controls
- L90 _public prototype_ `void SetGuiControls(const Eigen::VectorX<T>& guiControls);` — Sets the Gui controls
- L93 _public prototype_ `const Eigen::VectorX<T>& SolveControls() const;` — @returns the current solve control values
- L96 _public prototype_ `void SetSolveControls(const Eigen::VectorX<T>& controls);` — Set the solve control values
- L99 _public prototype_ `const std::vector<std::string>& SolveControlNames() const;` — @returns the names of the solve controls
- L102 _public prototype_ `const Eigen::Matrix<T, 2, -1>& SolveControlRanges() const;` — @returns the ranges for eadch solve control
- L105 _public prototype_ `const std::vector<bool>& SolveControlsToOptimize() const;` — @returns which controls are optimized
- L108 _public prototype_ `void SetSolveControlsToOptimize(const std::vector<bool>& controlsToOptimize);` — Sets which controls are optimized
- L111 _public prototype_ `const Eigen::VectorX<T>& SolveControlRegularizationScaling() const;` — @returns the regularization scaling per control
- L114 _public prototype_ `void SetSolveControlRegularizationScaling(const Eigen::VectorX<T>& regularizationScaling);` — Sets the regularization scaling per control
- L117 _public prototype_ `BoundedVectorVariable<T>* SolveControlVariable();` — @returns a pointer to the underlying solve control variable
- L120 _public prototype_ `int MeshIndex(const char* meshName) const;` — @returns the mesh index for the mesh with name @p name
- L123 _public prototype_ `int LeftEyeMeshIndex() const;` — @returns the mesh index of the left eye mesh
- L126 _public prototype_ `int RightEyeMeshIndex() const;` — @returns the mesh index of the right eye mesh
- L129 _public prototype_ `int TeethMeshIndex() const;` — @return the mesh index of the teeth mesh
- L136 _public prototype_ `const std::vector<std::tuple<std::string, std::string, T>>& SymmetricControls() const;` — @returns the symmetric controls that are be enforced as model constraints e.g. CTRL_L_mouth_funnelU.ty and CTRL_R_mouth_funnelU.ty should be activated in the same way. This represents a L2 constraints of the form w * || rigControl[id1] - rigControl[id2] ||_2^2
- L139 _public prototype_ `void SetSymmetricControls(const std::vector<std::tuple<std::string, std::string, T>>& symmetricControls);` — Sets symmetric controls. @see SymmetricControls().
- L142 _public prototype_ `void SetMutuallyExclusiveControlPairs(const std::vector< std::tuple<std::string, std::string, T>>& controlNamesAndWeights);` — Sets mutual exclusivity pairs of controls.
- L145 _public prototype_ `void SetMutuallyExclusiveControlTriples(const std::vector< std::tuple<std::string, std::string, std::string, T, T, T>>& controlNamesAndWeights);` — Sets mutual exclusivity triples of controls. The three weights are i) weighting for the constraint, ii) sharpness: how fast the control is activated, and iii) startVal: the starting value for the activation
- L150 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/deformation_models/DeformationModelRigid.h` (Private)


#### class `DeformationModelRigid`  
`template <class T> class DeformationModelRigid final : public DeformationModel<T>`  
_L13-46_
- inherits: `DeformationModel<T>`
- L16 _public function_ `static constexpr const char* ConfigName()`
- L18 _public prototype_ `DeformationModelRigid();`
- L20 _public prototype_ `DeformationModelRigid(DeformationModelRigid&& other);`
- L21 _public prototype_ `DeformationModelRigid(const DeformationModelRigid& other);`
- L22 _public prototype_ `DeformationModelRigid& operator=(DeformationModelRigid&& other);`
- L23 _public prototype_ `DeformationModelRigid& operator=(const DeformationModelRigid& other);`
- L26 _public prototype_ `virtual DiffDataMatrix<T, 3, -1> EvaluateVertices(Context<T>* context) override;` — inherited from DeformationModel
- L27 _public prototype_ `virtual Cost<T> EvaluateModelConstraints(Context<T>* context) override;`
- L28 _public prototype_ `virtual const Configuration& GetConfiguration() const override;`
- L29 _public prototype_ `virtual void SetConfiguration(const Configuration& config) override;`
- L32 _public prototype_ `DiffDataAffine<T, 3, 3> EvaluateAffine(Context<T>* context);` — Evaluate the affine transformation
- L35 _public prototype_ `void SetVertices(const Eigen::Matrix<T, 3, -1>& vertices);` — Set the current mesh (required)
- L38 _public prototype_ `void SetRigidTransformation(const Affine<T, 3, 3>& affine);` — Set the current rigid transformation
- L41 _public prototype_ `Affine<T, 3, 3> RigidTransformation() const;` — Returns the current rigid transformation
- L45 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/deformation_models/DeformationModelRigidScale.h` (Private)


#### class `DeformationModelRigidScale`  
`template <class T> class DeformationModelRigidScale final : public DeformationModel<T>`  
_L13-53_
- inherits: `DeformationModel<T>`
- L16 _public prototype_ `DeformationModelRigidScale();`
- L18 _public prototype_ `DeformationModelRigidScale(DeformationModelRigidScale&& other);`
- L19 _public prototype_ `DeformationModelRigidScale(const DeformationModelRigidScale& other) = delete;`
- L20 _public prototype_ `DeformationModelRigidScale& operator=(DeformationModelRigidScale&& other);`
- L21 _public prototype_ `DeformationModelRigidScale& operator=(const DeformationModelRigidScale& other) = delete;`
- L24 _public prototype_ `virtual DiffDataMatrix<T, 3, -1> EvaluateVertices(Context<T>* context) override;` — inherited from DeformationModel
- L25 _public prototype_ `virtual Cost<T> EvaluateModelConstraints(Context<T>* context) override;`
- L26 _public prototype_ `virtual const Configuration& GetConfiguration() const override;`
- L27 _public prototype_ `virtual void SetConfiguration(const Configuration& config) override;`
- L30 _public prototype_ `void SetVertices(const Eigen::Matrix<T, 3, -1>& vertices);` — Set the current mesh (required)
- L39 _public prototype_ `Affine<T, 3, 3> RigidTransformation(bool preScale) const;` — @returns the current rigid transformation either assuming the vertices are first scaled and then transformed, or alternatively first transformed and then scaled. Note that the deformation model first moves the vertices to the center of gravity before scaling and rotating the vertices. However, when retrieving the transformation and scale, the customer needs to determine whether first to transform and then scale (preScale=false) or scale and then transform (preScale=true)
- L45 _public prototype_ `void SetRigidTransformation(const Affine<T, 3, 3>& affine, bool preScale);` — Set the current rigid transformation either assuming the vertices are first scaled and then transformed, or alternatively first transformed and then scaled.
- L48 _public prototype_ `T Scale() const;` — @returns the estimate scale
- L52 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/deformation_models/DeformationModelVertex.h` (Private)


#### class `DeformationModelVertex`  
`template <class T> class DeformationModelVertex final : public DeformationModel<T>`  
_L13-63_
- inherits: `DeformationModel<T>`
- L16 _public function_ `static constexpr const char* ConfigName()`
- L18 _public prototype_ `DeformationModelVertex();`
- L20 _public prototype_ `DeformationModelVertex(DeformationModelVertex&& other);`
- L21 _public prototype_ `DeformationModelVertex(const DeformationModelVertex& other) = delete;`
- L22 _public prototype_ `DeformationModelVertex& operator=(DeformationModelVertex&& other);`
- L23 _public prototype_ `DeformationModelVertex& operator=(const DeformationModelVertex& other) = delete;`
- L26 _public prototype_ `virtual DiffDataMatrix<T, 3, -1> EvaluateVertices(Context<T>* context) override;` — inherited from DeformationModel
- L27 _public prototype_ `virtual Cost<T> EvaluateModelConstraints(Context<T>* context) override;`
- L28 _public prototype_ `virtual const Configuration& GetConfiguration() const override;`
- L29 _public prototype_ `virtual void SetConfiguration(const Configuration& config) override;`
- L31 _public prototype_ `std::pair<DiffDataMatrix<T, 3, -1>, DiffDataMatrix<T, 3, -1>> EvaluateBothStabilizedAndTransformedVertices(Context<T>* context);`
- L34 _public prototype_ `void SetMeshTopology(const Mesh<T>& mesh);` — Set the mesh topolgy (required for model constraints)
- L37 _public prototype_ `void SetRestVertices(const Eigen::Matrix<T, 3, -1>& vertices);` — Set the rest vertex positions (required)
- L40 _public prototype_ `void SetVertexOffsets(const Eigen::Matrix<T, 3, -1>& offsets);` — Sets the vertex offsets (optional)
- L43 _public prototype_ `Eigen::Matrix<T, 3, -1> VertexOffsets() const;` — Returns the vertex offsets
- L46 _public prototype_ `Eigen::Matrix<T, 3, -1> DeformedVertices() const;` — Returns the deformed vertex positions (RestVertices() + VertexOffsets())
- L49 _public prototype_ `void SetRigidTransformation(const Affine<T, 3, 3>& affine);` — Set the current rigid transformation
- L52 _public prototype_ `Affine<T, 3, 3> RigidTransformation() const;` — Returns the current rigid transformation
- L55 _public prototype_ `void MakeVerticesConstant(const std::vector<int>& constantIndices);` — Make vertices with specified IDs constant.
- L58 _public prototype_ `void MakeVerticesMutable();` — Make all vertices mutable.
- L62 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/landmarks/LandmarkConfiguration.h` (Private)


#### class `LandmarkConfiguration`  
`class LandmarkConfiguration`  
_L13-119_
- L16 _public prototype_ `LandmarkConfiguration() = default;`
- L17 _public function_ `LandmarkConfiguration(int numPoints, const std::map<std::string, int>& landmarkMapping, const std::map<std::string, std::vector<int>>& curvesMapping) : m_numPoints(numPoints) , m_landmarkMapping(landmarkMapping) , m_curvesMapping(curvesMapping)`
- L25 _public function_ `LandmarkConfiguration(int numPoints, std::map<std::string, int>&& landmarkMapping, std::map<std::string, std::vector<int>>&& curvesMapping) : m_numPoints(numPoints) , m_landmarkMapping(landmarkMapping) , m_curvesMapping(curvesMapping)`
- L33 _public prototype_ `std::shared_ptr<LandmarkConfiguration> Clone()const;`
- L35 _public prototype_ `bool LoadConfiguration(const TITAN_NAMESPACE::JsonElement& j);`
- L36 _public prototype_ `void ImportIndices(const std::map<std::string, int> & lmIndices, const std::map<std::string, std::vector<int>> & curveIndices);`
- L38 _public prototype_ `void AddLandmark(const std::string& landmarkName);`
- L39 _public prototype_ `void SetLandmark(const std::string& landmarkName, int idx);`
- L40 _public prototype_ `void AddCurve(const std::string& curveName, int numPoints);`
- L41 _public prototype_ `void AddCurve(const std::string& curveName, const std::string & startLandmark, const std::string & endLandmark, int numInbetweenPoints);`
- L42 _public prototype_ `void RemoveLandmark(const std::string& landmarkName);`
- L43 _public prototype_ `void RemoveCurve(const std::string& curveName);`
- L45 _public prototype_ `void RemoveUnwantedCurvesAndLandmarks(const std::vector<std::string>& validLandmarks ,const std::vector<std::string>& validCurves);`
- L47 _public function_ `int NumPoints() const`
- L49 _public function_ `bool HasLandmark(const std::string& landmarkName) const`
- L52 _public prototype_ `int IndexForLandmark(const std::string& landmarkName) const;` — @return the global index of the landmark
- L54 _public function_ `bool HasCurve(const std::string& curveName) const`
- L60 _public prototype_ `const std::vector<int>& IndicesForCurve(const std::string& curveName) const;` — @return the indices for the curve @p curveName. @pre the curve needs to exists. See HasCurve()
- L62 _public function_ `const std::map<std::string, int>& LandmarkMapping() const`
- L63 _public function_ `const std::map<std::string, std::vector<int>>& CurvesMapping() const`
- L64 _public prototype_ `std::vector<std::string> CurveNames()const;`
- L65 _public prototype_ `std::vector<std::string> LandmarkNames()const;`
- L79 _public prototype_ `template <class T, int D> bool MergeCurves(const std::vector<std::string>& curveNames, const std::string& newCurveName, const Eigen::Matrix<T, D, -1>& pts, bool ignoreMissingCurves, bool removeMergedCurves = false);` — Merges curves @p curveNames into a single @p newCurveName concatenating points along matching indices. Landmarks and curves have potentially duplicates, so the caller needs to pass in a set of landmarks @p pts and duplicated landmarks are found using the landmark positions (@see FindDuplicatesAndCreateMap). This way the curves can be merged. If @p ignoreMissingCurves is True, then all curves that are not part of the landmark configuration are ignored. @return True if the new curve was generated, False if nothing could be merged. Ideally we can replace it in the future if we can guarantee that the loaded landmarks never have duplicates, and instead curves are stored as vector of indices in the json files.
- L86 _public prototype_ `void MergeConfiguration(const LandmarkConfiguration& otherConfiguration);` — Combine two landmark configurations
- L90 _public prototype_ `template <class T, int D> std::map<int, int> FindDuplicatesAndCreateMap(const Eigen::Matrix<T, D, -1>& pts) const;` — Finds duplicated landmarks and returns a map to a single unique landmark
- L98 _public prototype_ `std::vector<int> RemapLandmarksAndCurvesAndCompress(const std::map<int, int>& map);` — Remap landmarks and curves based on the input @p map, removing all unused points, and moving all points into one continuous chunk. @param[in] map  The map specifying which landmarks/curve indices map to what unique landmark index (e.g. as created by FindDuplicatesAndCreateMap) @return A vector the size of the new number of landmarks, where each entry maps to the unique landmark before compression.
- L101 _public prototype_ `std::string LandmarkNameForPointIndex(int index) const;` — returns the Landmark name associated with the specified index
- L106 _public prototype_ `bool DoesConfigMatch(const LandmarkConfiguration & other)const;` — Comparison check agains an external Landmark Configuration instance
- L110 _private member_ `int m_numPoints = 0;` — total number of points in points matrix (see LandmarkInstance, may have duplicate points)
- L113 _private member_ `std::map<std::string, int> m_landmarkMapping;` — map from landmark name to index in points matrix (see LandmarkInstance)
- L116 _private member_ `std::map<std::string, std::vector<int>> m_curvesMapping;` — map from curve name to indices in points matrix (see LandmarkInstance)
- L118 _private prototype_ `bool IsLandmarkInAnyCurve(const std::string & landmarkName, const std::vector<std::string>& validCurveNames);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/landmarks/LandmarkConstraints2D.h` (Private)


#### class `LandmarkConstraints2D`  
`template <class T> class LandmarkConstraints2D : public LandmarkConstraintsBase<T>`  
_L10-151_
- inherits: `LandmarkConstraintsBase<T>`
- L15 _public prototype_ `virtual ~LandmarkConstraints2D() = default;`
- L18 _public function_ `void Clear()` — Clear target landmarks
- L21 _public function_ `void SetTargetLandmarks(const std::vector<std::pair<LandmarkInstance<T, 2>, Camera<T>>>& landmarks)` — Set target landmarks - in case of 2D landmarks, input is a vector of 2D LandmarkInstance paired with a corresponding camera
- L22 _public function_ `const std::vector<std::pair<LandmarkInstance<T, 2>, Camera<T>>>& GetTargetLandmarks() const`
- L27 _public prototype_ `virtual Cost<T> Evaluate(const DiffDataMatrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& normals, bool enforceConsistentSparsityPattern = true) const override;` — Evaluates landmarks, curves, and inner lips according to the configuration parameters.
- L31 _public prototype_ `virtual Cost<T> EvaluateEyeConstraints(const DiffDataMatrix<T, 3, -1>& eyeLeftVertices, const DiffDataMatrix<T, 3, -1>& eyeRightVertices) const override;` — evaluates the eye curves according to the configuration parameters
- L34 _public prototype_ `virtual Cost<T> EvaluateTeethConstraints(const DiffDataMatrix<T, 3, -1>& teethVertices) const override;` — evaluates the teeth landmarks according to the configuration parameters
- L37 _public prototype_ `void SetupLandmarkConstraints(const Eigen::Transform<T, 3, Eigen::Affine>& rigidTransform, const Eigen::Matrix<T, 3, -1>& vertices, const MeshLandmarks<T>* meshLandmarks, const MeshType meshType, VertexConstraints<T, 2, 3>& landmarkVertexConstraints) const;` — Creates the landmark constraints as vertex constraints into @p landmarkVertexConstraints
- L44 _public prototype_ `void SetupCurveConstraints(const Eigen::Transform<T, 3, Eigen::Affine>& rigidTransform, const Eigen::Matrix<T, 3, -1>& vertices, const MeshLandmarks<T>* meshLandmarks, const MeshType meshType, VertexConstraints<T, 1, 3>& curveVertexConstraints) const;` — Creates the curves constraints as vertex constraints into @p curveVertexConstraints
- L51 _public prototype_ `void SetupContourConstraints(const Eigen::Transform<T, 3, Eigen::Affine>& rigidTransform, const Eigen::Matrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& normals, const MeshLandmarks<T>* meshLandmarks, const MeshType meshType, VertexConstraints<T, 1, 2>& contourVertexConstraints) const;` — Creates the contour constraints as vertex constraints into @p contourVertexConstraints
- L60 _public prototype_ `void SetupInnerLipConstraints(const Eigen::Transform<T, 3, Eigen::Affine>& rigidTransform, const Eigen::Matrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& normals, const MeshLandmarks<T>* meshLandmarks, VertexConstraints<T, 1, 2>& innerLipVertexConstraints) const;` — Creates the inner lips constraints as vertex constraints into @p innerLipVertexConstraints
- L70 _public prototype_ `void SetupLandmarkConstraints(const Eigen::Transform<T, 3, Eigen::Affine>& rigidTransform, const Eigen::Matrix<T, 3, -1>& vertices, const MeshLandmarks<T>* meshLandmarks, const MeshType meshType, const std::vector<std::pair<const LandmarkInstance<T, 2>*, Camera<T>>>& targetLandmarks, VertexConstraints<T, 2, 3>& landmarkVertexConstraints) const;` — Creates the landmark constraints as vertex constraints into @p landmarkVertexConstraints
- L78 _public prototype_ `void SetupCurveConstraints(const Eigen::Transform<T, 3, Eigen::Affine>& rigidTransform, const Eigen::Matrix<T, 3, -1>& vertices, const MeshLandmarks<T>* meshLandmarks, const MeshType meshType, const std::vector<std::pair<const LandmarkInstance<T, 2>*, Camera<T>>>& targetLandmarks, VertexConstraints<T, 1, 3>& curveVertexConstraints) const;` — Creates the curves constraints as vertex constraints into @p curveVertexConstraints
- L96 _public prototype_ `void SetupInnerLipConstraints(const Eigen::Transform<T, 3, Eigen::Affine>& rigidTransform, const Eigen::Matrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& normals, const MeshLandmarks<T>* meshLandmarks, const std::vector<std::pair<const LandmarkInstance<T, 2>*, Camera<T>>>& targetLandmarks, VertexConstraints<T, 1, 2>& innerLipVertexConstraints) const;` — Creates the inner lips constraints as vertex constraints into @p innerLipVertexConstraints
- L110 _public prototype_ `virtual Cost<T> EvaluateLandmarks(const DiffDataMatrix<T, 3, -1>& vertices, MeshType meshType = MeshType::Face, LandmarkConstraintsData<T>* debugInfo = nullptr) const override;` — Evaluates the landmark point2point constraint for all current camera/landmark pairs (does *not* scale it by the configuration weight, use Evaluate() instead)
- L117 _public prototype_ `virtual Cost<T> EvaluateCurves(const DiffDataMatrix<T, 3, -1>& vertices, MeshType meshType = MeshType::Face, LandmarkConstraintsData<T>* debugInfo = nullptr) const override;` — Evaluates the curve point2surface constraint for all current camera/curve pairs (does *not* scale it by the configuration weight, use Evaluate() instead)
- L126 _public prototype_ `Cost<T> EvaluateContours(const DiffDataMatrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& normals, MeshType meshType = MeshType::Face, LandmarkConstraintsData<T>* debugInfo = nullptr) const;` — Evaluates the contour point2surface constraint for all current camera/curve pairs (does *not* scale it by the configuration weight, use Evaluate() instead) For this, for each contour line it finds first the position on the contour line where the normal switches from front facing to back facing in the camera, and then evaluates a point2surface constraint to the 2D landmark contour.
- L137 _public prototype_ `Cost<T> EvaluateInnerLips(const DiffDataMatrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& normals, LandmarkConstraintsData<T>* debugInfoUpper = nullptr, LandmarkConstraintsData<T>* debugInfoLower = nullptr) const;` — Evaluates the inner lip point2surface constraint for all current camera/inner lip contour curve pairs (does *not* scale it by the configuration weight, use Evaluate() instead) For this, for each contour line it finds first the position on the contour line where the normal switches from front facing to back facing in the camera, and then evaluates a point2surface constraint to the 2D landmark contour.
- L143 _private prototype_ `virtual bool EvaluateMeshActivity(const MeshLandmarks<T>* meshLandmarksPtr) const override;`
- L150 _private member_ `std::vector<std::pair<LandmarkInstance<T, 2>, Camera<T>>> m_targetLandmarks;` — A set of landmark instances adhering to the landmark configuration and cameras. The cameras describe the projection of a 3D point into a 2D image, and the landmarks are assumed to be in that camera space.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/landmarks/LandmarkConstraints3D.h` (Private)


#### class `LandmarkConstraints3D`  
`template <class T> class LandmarkConstraints3D : public LandmarkConstraintsBase<T>`  
_L10-67_
- inherits: `LandmarkConstraintsBase<T>`
- L15 _public function_ `virtual ~LandmarkConstraints3D()`
- L18 _public function_ `void SetTargetLandmarks(const LandmarkInstance<T, 3>& landmarks)` — Set target landmarks - in case of 3D landmarks input is LandmarkInstance3D
- L23 _public prototype_ `virtual Cost<T> Evaluate(const DiffDataMatrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& normals, bool enforceConsistentSparsityPattern = true) const override;` — Evaluates landmarks and curves according to the configuration parameters.
- L27 _public prototype_ `virtual Cost<T> EvaluateEyeConstraints(const DiffDataMatrix<T, 3, -1>& eyeLeftVertices, const DiffDataMatrix<T, 3, -1>& eyeRightVertices) const override;` — evaluates the eye curves according to the configuration parameters
- L30 _public prototype_ `virtual Cost<T> EvaluateTeethConstraints(const DiffDataMatrix<T, 3, -1>& teethVertices) const override;` — evaluates the teeth landmarks according to the configuration parameters
- L33 _public prototype_ `void SetupLandmarkConstraints(const Eigen::Transform<T, 3, Eigen::Affine>& rigidTransform, const Eigen::Matrix<T, 3, -1>& vertices, const MeshLandmarks<T>* meshLandmarks, const MeshType meshType, VertexConstraints<T, 3, 3>& landmarkVertexConstraints) const;` — Creates the landmark constraints as vertex constraints into @p landmarkVertexConstraints
- L40 _public prototype_ `void SetupCurveConstraints(const Eigen::Transform<T, 3, Eigen::Affine>& rigidTransform, const Eigen::Matrix<T, 3, -1>& vertices, const MeshLandmarks<T>* meshLandmarks, const MeshType meshType, VertexConstraints<T, 2, 3>& curveVertexConstraints) const;` — Creates the curves constraints as vertex constraints into @p curveVertexConstraints
- L51 _public prototype_ `virtual Cost<T> EvaluateLandmarks(const DiffDataMatrix<T, 3, -1>& vertices, MeshType meshType = MeshType::Face, LandmarkConstraintsData<T>* debugInfo = nullptr) const override;` — Evaluates the landmark point2point constraint for all current camera/landmark pairs (does *not* scale it by the configuration weight, use Evaluate() instead)
- L58 _public prototype_ `virtual Cost<T> EvaluateCurves(const DiffDataMatrix<T, 3, -1>& vertices, MeshType meshType = MeshType::Face, LandmarkConstraintsData<T>* debugInfo = nullptr) const override;` — Evaluates the curve point2surface constraint for all current camera/curve pairs (does *not* scale it by the configuration weight, use Evaluate() instead)
- L63 _private prototype_ `virtual bool EvaluateMeshActivity(const MeshLandmarks<T>* meshLandmarksPtr) const override;` — @returns true if submesh {EyeLeft,EyeRight,Teeth} is provided with tracked landmarks or curves.
- L66 _private member_ `LandmarkInstance<T, 3> m_targetLandmarks;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/landmarks/LandmarkConstraintsBase.h` (Private)


#### class `LandmarkConstraintsData`  
`template <class T> class LandmarkConstraintsData`  
_L23-35_
- L34 _public member_ `std::map<std::string, std::vector<ConstraintData>> constraintDataPerCamera;`

#### struct `LandmarkConstraintsData::ConstraintData`  
`struct ConstraintData`  
_L26-33_
- L28 _public member_ `BarycentricCoordinates<T> barycentricCoordinate;` — The barycentric coordinate for which the constraint is applicable
- L29 _public member_ `Eigen::Vector<T, 2> vertexProjection;` — The projection of the mesh vertex into the camera.
- L30 _public member_ `Eigen::Vector<T, 2> target;` — The target position.
- L31 _public member_ `Eigen::Vector<T, 2> targetNormal;` — The target normal.
- L32 _public member_ `T weight;` — The weight of the constraint.

#### class `LandmarkConstraintsBase`  
`template <class T> class LandmarkConstraintsBase`  
_L38-171_
- L49 _public function_ `static constexpr const char* ConfigName()`
- L52 _public function_ `virtual ~LandmarkConstraintsBase()`
- L57 _public prototype_ `virtual Cost<T> Evaluate(const DiffDataMatrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& normals, bool enforceConsistentSparsityPattern = true) const = 0;` — Evaluates landmarks and curves according to the configuration parameters.
- L61 _public prototype_ `virtual Cost<T> EvaluateEyeConstraints(const DiffDataMatrix<T, 3, -1>& eyeLeftVertices, const DiffDataMatrix<T, 3, -1>& eyeRightVertices) const = 0;` — evaluates the eye curves according to the configuration parameters
- L64 _public prototype_ `virtual Cost<T> EvaluateTeethConstraints(const DiffDataMatrix<T, 3, -1>& teethVertices) const = 0;` — evaluates the teeth landmarks according to the configuration parameters
- L71 _public prototype_ `virtual Cost<T> EvaluateLandmarks(const DiffDataMatrix<T, 3, -1>& vertices, MeshType meshType = MeshType::Face, LandmarkConstraintsData<T>* debugInfo = nullptr) const = 0;` — Evaluates the landmark point2point constraint for all current camera/landmark pairs (does *not* scale it by the configuration weight, use Evaluate() instead)
- L78 _public prototype_ `virtual Cost<T> EvaluateCurves(const DiffDataMatrix<T, 3, -1>& vertices, MeshType meshType = MeshType::Face, LandmarkConstraintsData<T>* debugInfo = nullptr) const = 0;` — Evaluates the curve point2surface constraint for all current camera/curve pairs (does *not* scale it by the configuration weight, use Evaluate() instead)
- L83 _public prototype_ `const std::vector<int> ExcludeInactiveMeshIndices(std::vector<int>) const;` — @returns vector of ints for each submesh {EyeLeft,EyeRight,Teeth}, where the meshIndex is replaced with -1 if not tracked.
- L86 _public prototype_ `static std::string MeshTypeToName(MeshType meshType);` — @returns mesh name string for given MeshType
- L89 _public function_ `void SetMeshLandmarks(const MeshLandmarks<T>& meshLandmarks)` — Set head mesh landmarks to be used in constraint evaluation
- L92 _public function_ `const MeshLandmarks<T>& GetMeshLandmarks() const` — Get head mesh landmarks
- L95 _public function_ `void SetEyeMeshLandmarks(const MeshLandmarks<T>& eyeLeftMeshLandmarks, const MeshLandmarks<T>& eyeRightMeshLandmarks)` — Set eye meshes landmarks to be used in constraint evaluation
- L102 _public function_ `void SetTeethMeshLandmarks(const MeshLandmarks<T>& teethMeshLandmarks)` — Set teeth mesh landmarks to be used in constraint evaluation
- L105 _public function_ `void SetUserDefinedLandmarkAndCurveWeights(const std::map<std::string, T>& userDefinedLandmarkAndCurveWeights)` — Set individual weights for landmarks and/or curves
- L111 _public prototype_ `const Configuration& GetConfiguration() const;` — Get parameters configuration
- L114 _public prototype_ `void SetConfiguration(const Configuration& config);` — Set parameters configuration
- L118 _protected prototype_ `const MeshLandmarks<T>* MeshLandmarksForType(MeshType type) const;` — @returns the MeshLandmarks structure that belongs to the mesh type
- L121 _protected prototype_ `T UserDefinedWeight(const std::string& landmarkOrCurveName) const;` — @returns the user defined landmark or curve weight or 1.0 if not defined
- L124 _protected prototype_ `virtual bool EvaluateMeshActivity(const MeshLandmarks<T>* meshLandmarksPtr) const = 0;` — @returns true if submesh {EyeLeft,EyeRight,Teeth} is provided with tracked landmarks or curves.
- L128 _protected member_ `MeshLandmarks<T> m_meshLandmarks;` — Landmarks and curves on the face mesh corresponding to landmarks and curves as annotated in 2D images
- L131 _protected member_ `MeshLandmarks<T> m_eyeLeftMeshLandmarks;` — Curves on the left eye mesh corresponding to landmarks and curves as annotated in 2D images
- L134 _protected member_ `MeshLandmarks<T> m_eyeRightMeshLandmarks;` — Curves on the right eye mesh corresponding to landmarks and curves as annotated in 2D images
- L137 _protected member_ `MeshLandmarks<T> m_teethMeshLandmarks;` — Landarmks on the teeth mesh corresponding to landmarks and curves as annotated in 2D images
- L140 _protected member_ `std::map<std::string, T> m_userDefinedLandmarkAndCurveWeights;` — optional weighting of landmarks and curves
- L142 _protected member_ `Configuration m_config = { ConfigName(), {`
- L170 _protected member_ `mutable SparseMatrixConstPtr<T> m_zeroWeightAuxillaryMatrix;` — This is a zero weight pattern matrix that makes sure that when calculating JtJ on the Jacobian of the output diffdata then the sparsity pattern of JtJ stays the same. The problem is that for inner lip constraints the constraint is set on an edge between two vertices, therefore the output Jacobian matrix will change based on what edge is selected. By adding all(!) possible inner lip constraints as zero terms the sparsity structure will stay consistent. However, it adds cost as there are more terms and the Jacobian density increases.

#### enum `LandmarkConstraintsBase::MeshType`  
`enum class MeshType`  
_L41-47_
- L43 _public enumerator_ `Face`
- L44 _public enumerator_ `EyeLeft`
- L45 _public enumerator_ `EyeRight`
- L46 _public enumerator_ `Teeth`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/landmarks/LandmarkInstance.h` (Private)


#### class `LandmarkInstance`  
`template <class T, int D> class LandmarkInstance`  
_L18-151_
- L21 _public prototype_ `LandmarkInstance() = default;`
- L22 _public function_ `LandmarkInstance(const Eigen::Matrix<T, D, -1> points, const Eigen::Vector<T, -1>& confidence)`
- L27 _public function_ `std::shared_ptr<LandmarkInstance<T, D>> Clone()const`
- L37 _public function_ `void Clear(int numLandmarks)`
- L43 _public function_ `void SetLandmark(int landmarkIndex, const Eigen::Vector<T, D>& pos, T confidence)`
- L49 _public function_ `void SetLandmarkConfiguration(const std::shared_ptr<const LandmarkConfiguration>& landmarkConfiguration)`
- L58 _public function_ `const std::shared_ptr<const LandmarkConfiguration>& GetLandmarkConfiguration() const`
- L60 _public function_ `void Set(const Eigen::Matrix<T, D, -1> points, const Eigen::Vector<T, -1>& confidence)`
- L70 _public function_ `int NumLandmarks() const`
- L72 _public function_ `int FrameNumber() const`
- L73 _public function_ `void SetFrameNumber(int frameNumber)`
- L75 _public function_ `const Eigen::Matrix<T, D, -1>& Points() const`
- L76 _public function_ `const Eigen::Vector<T, -1>& Confidence() const`
- L78 _public function_ `Eigen::Vector<T, D> Point(int index) const`
- L79 _public function_ `T Confidence(int index) const`
- L81 _public prototype_ `Eigen::Matrix<T, D, -1> Points(const std::vector<int>& indices) const;`
- L82 _public prototype_ `Eigen::Vector<T, -1> Confidences(const std::vector<int>& indices) const;`
- L89 _public prototype_ `bool MergeCurves(const std::vector<std::string>& curveNames, const std::string& newCurveName, bool ignoreMissingCurves, bool removeMergedCurves = false);` — Merges curves @curveNames into a single @p newCurveName concatenating points along matching points. See LandmarkConfiguration::MergeCurves. If @p ignoreMissingCurves is True, then missing curves are simply ignored. @return True if the new curve was generated, False if nothing could be merged.
- L91 _public prototype_ `void MergeInstance(const LandmarkInstance& other);`
- L97 _public prototype_ `void SimplifyCurve(const std::string& curveName, T eps = T(1));` — Method to reduce the number of points along the curve in order to have better control while manually modifying. @param[in] curveName    name of the curve to simplify
- L103 _public prototype_ `void SimplifyCurves(T eps = T(1));` — Method to reduce the number of points along the curve in order to have better control while manually modifying. Applies to all curves in landmark configuration.
- L112 _public prototype_ `static std::shared_ptr<const LandmarkInstance<T, D>> CreateLandmarkInstance(const std::map<std::string, Eigen::Matrix<T, D, -1>>& namedLandmarkData, const std::map<std::string, std::vector<std::string>>& curvesToMerge);` — Convenience function to create a landmark instance and a landmark configuration from a set of landmark data and optionally a description on what curves to merge. @param[in] namedLandmarkData   Landmark data mapping the name to the landmark/curve. @param[in] curvesToMerge       Description on what curves to merge for the instance. @return The created landmakr instance including landmark configuration.
- L118 _public prototype_ `void RemoveDuplicatesAndCompress();` — Remove duplicates based on the exact equality of the landmarks and curves points and compresses the remaining points into one continuous chunk.
- L121 _public prototype_ `void RemoveLandmarkOrCurvePoint(int landmark);` — Remove landmark/curve points with index @p landmark from the landmark instance.
- L130 _public prototype_ `void AddPointToCurve(const std::string& curveName, int segment, const Eigen::Vector<T, D>& pos, T confidence);` — Add a point to an existing curve. @param[in] curveName  Name of the curve that is modified. @param[in] segment    The index of the segment after which the point is added. @param[in] pos        The position of the new curve point. @param[in] confidence The confidence of the new curve point.
- L133 _public prototype_ `bool LoadFromJson(const JsonElement& json);` — Load the landmark instance from a json structure.
- L136 _public prototype_ `JsonElement SaveToJson() const;` — Save the landmark instance to json
- L141 _public prototype_ `std::shared_ptr<LandmarkInstance<T, D>> CloneSubSet(const std::vector<std::string> &landmarks, const std::vector<std::string> &curves)const;` — Make a deep copy of the LandmarkInstance only copying the specified landmarks and curves
- L144 _public prototype_ `void UpdatePointsForCurve(const std::string & curveName, const Eigen::Matrix<T, D, -1>& newPoints);` — Sets the points for a curve. The number of points can be different from the existing points
- L147 _private member_ `Eigen::Matrix<T, D, -1> m_points;`
- L148 _private member_ `Eigen::Vector<T, -1> m_confidence;`
- L149 _private member_ `int m_frameNumber = -1;`
- L150 _private member_ `std::shared_ptr<const LandmarkConfiguration> m_landmarkConfiguration;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/landmarks/LandmarkSequence.h` (Private)


#### class `LandmarkSequence`  
`template <class T> class LandmarkSequence`  
_L20-70_
- L23 _public prototype_ `LandmarkSequence();`
- L31 _public prototype_ `bool Load(const std::string& filename, int frameOffset);` — Loads the landmarks from @p filename. If @p frameOffset >= 0, then landmarks are loaded sequentially from the landmark file and the internal frame number of the landmarks is ignored, instead it will be frameOffset + index. If @p frameOffset < 0, then the frame number of the landmarks are used.
- L32 _public prototype_ `void Save(const std::string& filename, int tabs = 1) const;`
- L34 _public prototype_ `bool HasLandmarks(int frame) const;`
- L36 _public prototype_ `const LandmarkInstance<T, 2>& Landmarks(int frame) const;`
- L38 _public prototype_ `std::shared_ptr<const LandmarkInstance<T, 2>> LandmarksPtr(int frame) const;`
- L44 _public prototype_ `void Undistort(const MetaShapeCamera<T>& camera);` — Undistort all landmarks and curves in the sequence. Precondition: landmarks and curves have not yet been undistorted.
- L51 _public prototype_ `bool MergeCurves(const std::vector<std::string>& curveNames, const std::string& newCurveName, bool ignoreMissingCurves, bool removeMergedCurves = false);` — Merges curves @curveNames into a single @p newCurveName concatenating points along matching points. See LandmarkConfiguration::MergeCurves. If @p ignoreMissingCurves is True, then missing curves are simply ignored. @return True if the new curve was generated, False if nothing could be merged.
- L54 _public prototype_ `void MergeSequences(const LandmarkSequence& otherSequence);` — Combine two landmark sequences
- L57 _public prototype_ `std::map<int, std::shared_ptr<const LandmarkInstance<T, 2>>> LandmarkInstances() const;` — convenience function to get access to all landmark instances
- L60 _public prototype_ `void SetLandmarkInstances(const std::map<int, std::shared_ptr<const LandmarkInstance<T, 2>>>& landmarkInstances);` — set the landmark sequences
- L62 _public prototype_ `void SetLandmarkInstance(int frame, const std::shared_ptr<const LandmarkInstance<T, 2>>& landmarkInstance);`
- L64 _public prototype_ `std::unique_ptr<LandmarkSequence<T>> Clone()const;`
- L66 _public prototype_ `void OffsetFrameNumbers(int offset);`
- L69 _private member_ `std::map<int, std::shared_ptr<const LandmarkInstance<T, 2>>> m_landmarkInstances;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/landmarks/LandmarkTriangulation.h` (Private)


#### Free symbols / members of external scopes

- L19 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> std::map<std::string, Eigen::Vector3<T>> TriangulateLandmarks(const MultiCameraSetup<T>& cameraSetup, const std::map<std::string, LandmarkInstance<T, 2>>& landmarkInstances)`
- L88 _function_ `template <class T> std::map<std::string, Eigen::Vector3<T>> TriangulateLandmarksViaRayCasting(const Camera<T>& camera, const LandmarkInstance<T, 2>& landmarkInstance, const Mesh<T>& mesh)` — Triangulate landmarks by intersecting the 2D landmarks with the Mesh
- L140 _function_ `template <class T> std::map<std::string, std::pair<Eigen::Vector3<T>, bool>> TriangulateLandmarksViaAABB(const Camera<T>& camera, const LandmarkInstance<T, 2>& landmarkInstance, const Mesh<T>& mesh)` — Triangulate landmarks by intersecting the 2D landmarks with the Mesh using AABB tree
- L179 _function_ `template <class T> std::map<std::string, Eigen::Matrix3X<T>> TriangulateCurvesViaRayCasting(const Camera<T>& camera, const LandmarkInstance<T, 2>& landmarkInstance, const Mesh<T>& mesh)` — Triangulate landmarks by intersecting the 2D landmarks with the Mesh
- L242 _function_ `template <class T> std::map<std::string, std::pair<Eigen::Matrix3X<T>, std::vector<bool>>> TriangulateCurvesViaAABB(const Camera<T>& camera, const LandmarkInstance<T, 2>& landmarkInstance, const Mesh<T>& mesh)` — Triangulate landmarks by intersecting the 2D curves with the Mesh using AABB tree
- L290 _function_ `template <class T> std::map<std::string, Eigen::Vector3<T>> TriangulateLandmarksViaDepthmap(const Camera<T>& camera, const LandmarkInstance<T, 2>& landmarkInstance, const Camera<T>& depthmapCamera, const Eigen::Matrix<T, 4, -1>& depthAndNormals)` — Triangulate landmarks by looking up the position in a depthmap
- L330 _function_ `template <class T> Eigen::Matrix<T, 3, -1> TriangulatePointsViaDepthmap(const Camera<T>& camera, const Eigen::Matrix<T, 2, -1>& points, const Camera<T>& depthmapCamera, const Eigen::Matrix<T, 4, -1>& depthAndNormals, std::vector<bool>& triangulatedPointValidityFlags)` — Triangulate raw 2D points by looking up the position in a depthmap.
- L371 _function_ `template <class T> Eigen::Matrix<T, 3, -1> TriangulatePointsViaRayCasting(const Camera<T>& camera, const Eigen::Matrix<T, 2, -1>& points, const Mesh<T>& mesh, std::vector<bool>& triangulatedPointValidityFlags)` — Triangulate raw 2D points by intersecting the 2D landmarks with the Mesh

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/landmarks/LipClosure.h` (Private)


#### class `LipClosure`  
`template <class T> class LipClosure`  
_L21-87_
- desc: Class to calculate if a point in 2D is closest to the closed or open lips.
- L24 _public prototype_ `LipClosure() = default;`
- L26 _public function_ `bool Valid() const`
- L27 _public function_ `void Reset()`
- L29 _public function_ `void Init(const LandmarkInstance<T, 2>& landmarkInstance)`
- L61 _public function_ `T ClosureValue(const Eigen::Vector2<T>& pt) const` — @brief Calculates if a point @p pt is closest to closed or open lips @return T(1) if lips are closed, or T(0) if lips are open.
- L81 _private member_ `Eigen::Vector2<T> m_cornerLeft;`
- L82 _private member_ `Eigen::Vector2<T> m_cornerRight;`
- L83 _private member_ `Eigen::Vector2<T> m_contactLeft;`
- L84 _private member_ `Eigen::Vector2<T> m_contactRight;`
- L85 _private member_ `bool m_valid = false;`
- L86 _private member_ `T m_globalWeight = 0;`

#### class `LipClosure3D`  
`template <class T> class LipClosure3D`  
_L95-138_
- desc: Class to calculate if a point in 3D, when projected into multiple 2D landmarks, whether it projects to open or closed lips.
- L98 _public prototype_ `LipClosure3D() = default;`
- L100 _public function_ `void Reset()`
- L106 _public function_ `bool Valid() const`
- L108 _public function_ `void Add(const LandmarkInstance<T, 2>& landmarkInstance, const Camera<T>& camera)`
- L123 _public function_ `T ClosureValue(const Eigen::Vector3<T>& pt) const` — @brief Calculates if a 3d point @p pt, projected into each image and measured for 2D lip closure. @return T(1) if lips are closed, or T(0) if lips are open.
- L136 _private member_ `std::vector<LipClosure<T>> m_lipClosures;`
- L137 _private member_ `std::vector<Camera<T>> m_cameras;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/rt/EulerXYZTransform.h` (Private)


#### struct `EulerXYZTransform`  
`template <class T> struct EulerXYZTransform : public Eigen::Vector<T, 6>`  
_L12-36_
- inherits: `Eigen::Vector<T,6>`
- desc: Class representing a rigid motion as an EulerXYZ rotation and a translation.
- L14 _public function_ `EulerXYZTransform() : Eigen::Vector<T, 6>()`
- L16 _public function_ `Eigen::Ref< Eigen::Vector3<T>> Rotation()`
- L17 _public function_ `Eigen::Ref<const Eigen::Vector3<T>> Rotation() const`
- L18 _public function_ `Eigen::Ref< Eigen::Vector3<T>> Translation()`
- L19 _public function_ `Eigen::Ref<const Eigen::Vector3<T>> Translation() const`
- L21 _public function_ `Eigen::Transform<T, 3, Eigen::Affine> Transform() const`
- L29 _public function_ `static EulerXYZTransform FromTransform(const Eigen::Transform<T, 3, Eigen::Affine>& transform)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/rt/HeadState.h` (Private)


#### struct `HeadState`  
`template <class T> struct HeadState`  
_L15-72_
- desc: Head state with vertices for face and teeth, and a delta transformation for the left and right eye.
- L17 _public member_ `Eigen::Matrix<T, 3, -1> faceVertices;`
- L18 _public member_ `Eigen::Matrix<T, 3, -1> teethVertices;`
- L19 _public member_ `EulerXYZTransform<T> eyeLeftDeltaTransform;`
- L20 _public member_ `EulerXYZTransform<T> eyeRightDeltaTransform;`
- L23 _public function_ `Eigen::VectorX<T> Flatten() const` — @returns the data of the head state flattened to a vector
- L42 _public function_ `static HeadState FromHeadVertexState(const HeadVertexState<T>& headVertexState, const RigidBody<T>& eyeLeftRigidBody, const RigidBody<T>& eyeRightRigidBody)` — @brief  Converts the head vertex state to a state with a rigid transform for the left and right eye. Calculates the rigid transform using Eigen::umeyama().
- L63 _public function_ `HeadVertexState<T> ToHeadVertexState(const RigidBody<T>& eyeLeftRigidBody, const RigidBody<T>& eyeRightRigidBody) const` — Converts the HeadState back to vertex state.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/rt/HeadVertexState.h` (Private)


#### struct `HeadVertexState`  
`template <class T> struct HeadVertexState`  
_L12-56_
- desc: Head state with vertices for face, teeth, left eye, and right eye.
- L14 _public member_ `Eigen::Matrix<T, 3, -1> faceVertices;`
- L15 _public member_ `Eigen::Matrix<T, 3, -1> teethVertices;`
- L16 _public member_ `Eigen::Matrix<T, 3, -1> eyeLeftVertices;`
- L17 _public member_ `Eigen::Matrix<T, 3, -1> eyeRightVertices;`
- L19 _public function_ `bool IsValidFaceData() const`
- L20 _public function_ `bool IsValidTeethData() const`
- L21 _public function_ `bool IsValidLeftEyeData() const`
- L22 _public function_ `bool IsValidRightEyeData() const`
- L23 _public function_ `bool IsValidEyesData() const`
- L25 _public function_ `void Reset()`
- L32 _public function_ `void ResetFace()`
- L34 _public function_ `void ResetTeeth()`
- L36 _public function_ `void ResetEyes()`
- L42 _public function_ `Eigen::VectorX<T> Flatten() const`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/rt/LinearEyeModel.h` (Private)


#### struct `LinearEyeModel`  
`template <class T> struct LinearEyeModel`  
_L15-140_
- desc: Eye model with a rigid body for the eye mesh and a linear model representing rotation and translation.
- L17 _public member_ `RigidBody<T> eyeBody;`
- L18 _public member_ `LinearModel<T> linearTransformModel;`
- L33 _public function_ `Eigen::Matrix<T, 3, -1> EvaluateVertices(const Eigen::VectorX<T>& coeffs, typename LinearVertexModel<T>::EvaluationMode evaluationMode) const` — @brief Evaluates the eye vertices using the linear model coefficients. Optionally a linearized rigid transform and a scale can be passed as part of the coefficients. @param coeffs     Parameters for the local linear rotation/translation model as well as optinoally a linearized rigid transform and scale. @param evaluationMode Whether to just evaluate the model, apply also global rigid transformation, or a rigid transformation and scale. @return Eigen::Matrix<T, 3, -1> The eye vertices. The transform of the eye ball is: vertices = eyeBody.baseTransform * deltaTransform * eyeBody.baseVertices with rigid: vertices = globalDeltaTransform * vertices with rigid and scale: vertices = globalDeltaTransform * scale * vertices
- L67 _public function_ `void EvaluateVerticesAndJacobian(const Eigen::VectorX<T>& coeffs, typename LinearVertexModel<T>::EvaluationMode evaluationMode, LinearVertexModel<T>& vertexModel) const` — @brief Evaluates the eye vertices and also calculates the Jacobian of the vertices with respect to the coefficients.
- L106 _public function_ `void Translate(const Eigen::Vector3<T>& translation)` — translates the eye model
- L109 _public function_ `void Resample(const std::vector<int>& newToOldMap)` — Resample the model keeping only the vertices in @p newToOldMap
- L123 _private function_ `void Verify(const Eigen::VectorX<T>& coeffs, typename LinearVertexModel<T>::EvaluationMode evaluationMode) const`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/rt/PCARig.h` (Private)


#### struct `PCARig`  
`struct PCARig`  
_L36-89_
- L39 _public member_ `LinearVertexModel<float> facePCA;` — PCA model of the face vertices
- L42 _public member_ `LinearVertexModel<float> teethPCA;` — PCA model of the teeth vertices
- L45 _public member_ `LinearEyeModel<float> eyeLeftTransformPCA;` — PCA model of the parameters of the left eye (rotation, translation)
- L48 _public member_ `LinearEyeModel<float> eyeRightTransformPCA;` — PCA model of the parameters of the right eye (rotation, translation)
- L51 _public member_ `LinearVertexModel<float> neckPCA;` — PCA model of the face vertices
- L54 _public member_ `Eigen::Transform<float, 3, Eigen::Affine> rootBindPose;` — global root bind pose (required to save the eye joints relative to the root)
- L57 _public member_ `Mesh<float> meshes[4];` — meshes of face, teeth, eye left, and eye right
- L60 _public member_ `Eigen::Vector3f offset = Eigen::Vector3f::Zero();` — offset that was applied to the pca model @see Translate()
- L63 _public function_ `Affine<float, 3, 3> ToOriginalPosition() const` — @returns the affine transformation that moves the pca rig back to the original position (removes the offset)
- L65 _public function_ `int NumCoeffs() const`
- L66 _public function_ `int NumCoeffsNeck() const`
- L67 _public prototype_ `HeadVertexState<float> EvaluatePCARig(const Eigen::VectorX<float>& pcaCoeffs) const;`
- L69 _public prototype_ `Eigen::Matrix3Xf EvaluatePCARigNeck(const Eigen::VectorX<float>& pcaCoeffs) const;`
- L71 _public prototype_ `Eigen::VectorX<float> Project(const HeadVertexState<float>& headVertexState, const Eigen::VectorX<float>& coeffs) const;`
- L73 _public prototype_ `Eigen::VectorX<float> ProjectNeck(const HeadVertexState<float>& headVertexState, const HeadVertexState<float>& neutralHeadVertexState, const Eigen::VectorX<float>& coeffs) const;`
- L76 _public prototype_ `void Translate(const Eigen::Vector3f& translation);` — Translates the rig globally, moving the vertices and the bind poses
- L79 _public prototype_ `Eigen::Vector3f EyesMidpoint() const;` — @returns the midepoint between the eyes
- L81 _public prototype_ `void SaveAsDNA(const std::string& filename) const;`
- L82 _public prototype_ `void SaveAsDNA(dna::Writer* writer) const;`
- L85 _public prototype_ `void SaveAsNpy(const std::string& filename) const;` — Save the pca model as a large npy matrix including face, teeth, and eyes
- L87 _public prototype_ `bool LoadFromDNA(const std::string& filename);`
- L88 _public prototype_ `bool LoadFromDNA(dna::Reader* reader);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`
- L20 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::rt) const char* EyeLeftJointName();`
- L23 _prototype_ `const char* EyeRightJointName();`
- L24 _prototype_ `const char* FacialRootJointName();`
- L26 _prototype_ `const char* HeadMeshName();`
- L27 _prototype_ `const char* TeethMeshName();`
- L28 _prototype_ `const char* EyeLeftMeshName();`
- L29 _prototype_ `const char* EyeRightMeshName();`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/rt/PCARigCreator.h` (Private)


#### class `PCARigCreator`  
`class PCARigCreator`  
_L22-162_
- desc: Class to create a PCA rig from a DNA rig.
- L44 _public prototype_ `PCARigCreator(const std::string& dnaFilename, const std::string& configFilename);`
- L45 _public prototype_ `PCARigCreator(std::shared_ptr<const Rig<float>> rig);`
- L48 _public prototype_ `bool LoadConfig(const std::string& configFilenameOrData);` — Loads the configuration for creating a PCA model from a rig; may also contain a Json string containing the config data
- L57 _public prototype_ `bool Create(int maxModes = -1);` — @brief Create the PCA model for the input dna and the current config. @param maxModes  The maximum number of modes to be used for the PCA model. If negative, then the maximum number of modes is as defined in config file (and 100 if not defined in the config). @return True is PCA model was created, false otherwise.
- L60 _public function_ `int NumRigTrainingSampleSets() const` — @returns the number of animation sample sets. Includes also the sample set for all facial expressions.
- L63 _public prototype_ `bool LoadRigTrainingSamples(const std::string& qsaFilename);` — Load training samples from a qsa file @p qsaFilename for face pca
- L66 _public prototype_ `bool LoadRigNeckTrainingSamples(const std::string& qsaFilename);` — Load training samples from a qsa file @p qsaFilename for neck pca
- L69 _public prototype_ `void SaveRigTrainingSamples(int idx, const std::string& qsaFilename) const;` — Save the training samples at index @p idx to file @p qsaFilename.
- L72 _public prototype_ `void CreateRigTrainingSamples(const std::string& name);` — Create an empty traing samples set.
- L75 _public prototype_ `void CreateRigNeckTrainingSamples(const std::string& name);` — Create an empty traing samples set.
- L78 _public function_ `std::vector<RigTrainingData>& RigTrainingSamples()` — Training samples
- L79 _public function_ `const std::vector<RigTrainingData>& RigTrainingSamples() const`
- L82 _public function_ `int NumMeshTrainingSampleSets() const` — @returns the number of mesh training sample sets.
- L85 _public prototype_ `bool LoadMeshTrainingSamples(const std::string& dirname, bool recursive, bool isNumpy, float rotAngle);` — Load training samples from a directory @p dirname
- L88 _public prototype_ `void SetMeshTrainingSamples(const std::vector<std::vector<Eigen::Matrix<float, 3, -1>>>& trainingMeshes, float rotAngle);` — Set training samples from runtime
- L91 _public function_ `std::vector<MeshTrainingData>& MeshTrainingSamples()` — Training samples
- L92 _public function_ `const std::vector<MeshTrainingData>& MeshTrainingSamples() const`
- L95 _public prototype_ `int GuiControlIndex(const std::string& guiControlName) const;` — @returns the index of the gui control @p guiControlName.
- L98 _public prototype_ `int RawControlIndex(const std::string& rawControlName) const;` — @returns the index of the raw control @p rawControlName.
- L101 _public prototype_ `Eigen::VectorXf DefaultRawControls() const;` — @returns the default raw controls
- L104 _public prototype_ `rt::HeadVertexState<float> EvaluateExpression(const Eigen::VectorXf& rawControls) const;` — evaluate the face on the rig
- L106 _public function_ `const std::shared_ptr<const Rig<float>>& GetRig() const`
- L107 _public function_ `const rt::PCARig& GetPCARig() const`
- L110 _public prototype_ `void LoadFaceMask(const std::string& filename, const std::string& maskName = "");` — load mask for the face vertices
- L113 _public function_ `VertexWeights<float> FaceMask() const` — @returns the face mask
- L117 _private prototype_ `void CreateFacePCARig(Eigen::VectorXf& mean, Eigen::Matrix<float, -1, -1, Eigen::RowMajor>& modes, std::vector<int>& offsetsPerModel, const Eigen::Transform<float, 3, Eigen::Affine>& defaultRootTransform);` — Create the Face PCA Rig
- L123 _private prototype_ `bool LoadRigTrainingSamples(const std::string& qsaFilename, bool useForNeck);` — Load training samples from a qsa file @p qsaFilename
- L126 _private prototype_ `std::vector<Eigen::VectorXf> AllFaceExpressions() const;` — @returns all expressions for the face
- L129 _private prototype_ `std::vector<Eigen::VectorXf> AllNeckExpressions() const;` — @returns all neck expressions for the face
- L132 _private prototype_ `Eigen::Matrix<float, -1, -1> GetFaceDataMatrix(std::vector<rt::HeadVertexState<float>>& headVertexStates);` — @returns data matrix from head vertex states
- L135 _private prototype_ `Eigen::Matrix<float, -1, -1> GetNeckDataMatrix(std::vector<rt::HeadVertexState<float>>& headVertexStates, const int numFaceVertices, Eigen::Index maxModes);` — @returns data matrix from head vertex states for neck region
- L138 _private prototype_ `std::pair<Eigen::VectorXf, Eigen::Matrix<float, -1, -1, Eigen::RowMajor>> CreatePCAFromDataMatrix(Eigen::Matrix<float, -1, -1>& dataMatrix, int maxModes);` — @calculate pca from data matrix
- L141 _private member_ `std::map<std::string, float> m_defaultRawControls;`
- L142 _private member_ `std::set<std::string> m_fixedControls;`
- L143 _private member_ `std::set<std::string> m_neckControls;`
- L144 _private member_ `std::shared_ptr<const Rig<float>> m_rig;`
- L146 _private member_ `rt::PCARig m_pcaRig;`
- L147 _private member_ `rt::RigidBody<float> m_eyeLeftBody;`
- L148 _private member_ `rt::RigidBody<float> m_eyeRightBody;`
- L150 _private member_ `std::vector<int> m_meshIndices;`
- L151 _private member_ `int m_headMeshIndex;`
- L152 _private member_ `int m_teethMeshIndex;`
- L153 _private member_ `int m_eyeLeftMeshIndex;`
- L154 _private member_ `int m_eyeRightMeshIndex;`
- L156 _private member_ `int m_defaultMaxModes = 100;`
- L158 _private member_ `std::vector<RigTrainingData> m_rigControlTrainingSamples;`
- L159 _private member_ `std::vector<MeshTrainingData> m_meshTrainingSamples;`
- L161 _private member_ `VertexWeights<float> m_faceMask;`

#### struct `PCARigCreator::RigTrainingData`  
`struct RigTrainingData`  
_L25-33_
- L27 _public member_ `std::string name;`
- L28 _public member_ `bool useForTraining = true;`
- L29 _public member_ `bool useForNeck = false;`
- L30 _public member_ `std::vector<int> frameNumbers;`
- L31 _public member_ `std::vector<Eigen::VectorXf> rawControls;`
- L32 _public member_ `std::vector<Eigen::VectorXf> guiControls;`

#### struct `PCARigCreator::MeshTrainingData`  
`struct MeshTrainingData`  
_L35-41_
- L37 _public member_ `std::string name;`
- L38 _public member_ `bool useForTraining = true;`
- L39 _public member_ `std::vector<int> frameNumbers;`
- L40 _public member_ `std::vector<rt::HeadVertexState<float>> headVertexStates;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/rt/PCAVertexRig.h` (Private)


#### struct `PCAVertexRig`  
`struct PCAVertexRig`  
_L23-53_
- L25 _public member_ `LinearVertexModel<float> facePCA;`
- L26 _public member_ `LinearVertexModel<float> teethPCA;`
- L27 _public member_ `LinearVertexModel<float> eyeLeftPCA;`
- L28 _public member_ `LinearVertexModel<float> eyeRightPCA;`
- L31 _public member_ `Eigen::Transform<float, 3, Eigen::Affine> rootBindPose;` — global root bind pose
- L34 _public member_ `Mesh<float> meshes[4];` — meshes of face, teeth, eye left, and eye right
- L36 _public member_ `Eigen::ColPivHouseholderQR<Eigen::Matrix<float, -1, -1>> solver;`
- L38 _public function_ `int NumCoeffs() const`
- L40 _public prototype_ `HeadVertexState<float> EvaluatePCARig(const Eigen::VectorX<float>& pcaCoeffs) const;`
- L42 _public prototype_ `Eigen::VectorX<float> Project(const HeadVertexState<float>& headVertexState, const Eigen::VectorX<float>& coeffs) const;`
- L45 _public prototype_ `void Translate(const Eigen::Vector3f& translation);` — Translates the rig globally, moving the vertices and the bind pose
- L48 _public prototype_ `Eigen::Vector3f EyesMidpoint() const;` — @returns the midepoint between the eyes
- L50 _public prototype_ `void SaveAsDNA(const std::string& filename) const;`
- L51 _public prototype_ `bool LoadFromDNA(const std::string& filename);`
- L52 _public prototype_ `bool LoadFromDNA(dna::Reader* reader);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/rt/RigidBody.h` (Private)


#### struct `RigidBody`  
`template <class T> struct RigidBody`  
_L12-47_
- desc: Rigid body with a set of vertices and a base transform.
- L14 _public member_ `Eigen::Matrix<T, 3, -1> baseVertices;`
- L15 _public member_ `Eigen::Transform<T, 3, Eigen::Affine> baseTransform;`
- L17 _public function_ `Eigen::Transform<T, 3, Eigen::Affine> EvaluateTransform(const EulerXYZTransform<T>& deltaTransform) const`
- L22 _public function_ `Eigen::Matrix<T, 3, -1> EvaluateVertices(const EulerXYZTransform<T>& deltaTransform) const`
- L28 _public function_ `Eigen::Matrix<T, 3, 6> Derivative(const EulerXYZTransform<T>& deltaTransform) const` — get the derivative info for the delta transform

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/serialization/RegionBlendModelSerialization.h` (Private)


#### Free symbols / members of external scopes

- L10 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> void RegionBlendModelFromJson(const JsonElement& j, RegionBlendModel<T>& regionBlendModel)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/serialization/VertexWeightsSerialization.h` (Private)


#### Free symbols / members of external scopes

- L8 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`
- L19 _function_ `template<class T> bool FromBinaryFile(FILE *pFile, VertexWeights<T> &vertexWeights)` — Deserializes VertexWeights from binary format

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/volumetric/VolumetricDeformation.h` (Private)


#### class `VolumetricDeformation`  
`template <class T> class VolumetricDeformation`  
_L18-105_
- L25 _public prototype_ `static VolumetricFaceModel<T> MorphVolumetricFaceModelUsingGrid(const VolumetricFaceModel<T>& inputVolModel, Eigen::Ref<const Eigen::Matrix<T, 3, -1>> srcVertices, Eigen::Ref<const Eigen::Matrix<T, 3, -1>> targetVertices, int gridSize = 32);` — Morphs the @p inputVolModel by optimizing a grid deformation from @p srcVertices to @p targetVertices and apply the grid deformation on all vertices of the @p inputVolModel.
- L37 _public prototype_ `static Eigen::Matrix<T, 3, -1> DeformFleshMeshUsingSkinAndEyes(const VolumetricFaceModel<T>& inputVolModel, const TemplateDescription& templateDescription, const Mesh<T>& newSkinMesh, const Mesh<T>& newEyeLeftMesh, const Mesh<T>& newEyeRightMesh);` — Deforms the flesh mesh vertices to coincide with the skin mesh (based on the mapping) and also ensures that the flesh mesh conforms to the input eyes. Note that there is not a correspondence between eyeballs and the flesh mesh, in particular the skin mesh can slide over the eyeballs, and hence using a fixed correspondence would lead to artifacts.
- L52 _public prototype_ `static VolumetricFaceModel<T> MorphVolumetricFaceModelUsingGrid(const VolumetricFaceModel<T>& inputVolModel, const TemplateDescription& templateDescription, const Mesh<T>& newSkinMesh, const Mesh<T>& newTeethMesh, const Mesh<T>& newEyeLeftMesh, const Mesh<T>& newEyeRightMesh, int gridSize = 32);` — Morphs the volumetric model using a grid deformation model. As boundary counstraints the grid deformation uses the skin mesh @p newSkinMesh, the teeth mesh @p newTeethMesh, as well as the eye meshes. @param[in] inputVolModel  The input volumetric model that is morphed. @param[in] newSkinMesh    The skin mesh that acts as target for the volumetric morph. @param[in] newTeethMesh   The teeth mesh that acts as target for the volumetric morph. @returns the morphed volumetric model were each mesh has been morphed, and skin and possible teeth mesh are replaced by the input meshes. @warning the method does *NOT* update the tet mesh.
- L73 _public prototype_ `static VolumetricFaceModel<T> DeformFleshMeshUsingCraniumMandibleSkinAndEyesAsBoundaryConditions(const VolumetricFaceModel<T>& inputVolModel, const Mesh<T>& referenceFleshMesh, const TemplateDescription& templateDescription, const Mesh<T>& eyeLeftMesh, const Mesh<T>& eyeRightMesh);` — Deforms the flesh mesh using the cranium, mandible, skin, and eyes as boundary conditions. This method only deforms the flesh mesh and the tet mesh is not modified. Smoothness of the flesh mesh is based on the @p referenceFleshMesh. The vertices of the flesh mesh that coincide with vertices of cranium, mandible, and skin are directly set to the corresponding vertices of these meshes to have perfect alignment. This method is intended to be used for identities where there is no knowledge on the volume of the flesh. To optimize the mesh of a known identity see @DeformTetsAndFleshMeshUsingCraniumMandibleAndSkinAsBoundaryConditions. @param[in] inputVolModel  The input volumetric model for which the flesh mesh is modified. @param[in] referenceFleshMesh   The reference flesh mesh that is used for smoothness constraints. @returns the volumetric model with the flesh mesh being smoothly deformed. @warning the method does *NOT* update the tet mesh. @see UpdateTetsUsingFleshMesh().
- L84 _public prototype_ `static void UpdateTetsUsingFleshMesh(VolumetricFaceModel<T>& volModel, const VolumetricFaceModel<T>& referenceVolModel);` — Deform the tets based on the flesh mesh. @param[inout] volModel  The volumetric face model or which the tests are updated. @param[in] referenceVolModel  The reference volumetric model that defines the rest state of the tets
- L91 _public prototype_ `static void DeformTetsAndFleshMeshUsingCraniumMandibleAndSkinAsBoundaryConditions(VolumetricFaceModel<T>& volModel, const VolumetricFaceModel<T>& referenceVolModel);` — TODO: comment @param[inout] volModel  The volumetric model with deformed mandible and skin (cranium should never change). The flesh and tet mesh are updated. @param[in] referenceVolModel  The reference model. Typically the same "identity" as @p volModel but in Neutral position.
- L94 _public prototype_ `static void ConformCraniumAndMandibleToTeeth(VolumetricFaceModel<T>& volModel, const TemplateDescription& templateDescription);`
- L97 _public prototype_ `static std::pair<typename MeshCorrespondenceSearch<T>::Result, typename MeshCorrespondenceSearch<T>::Result> CraniumAndMandibleToTeethCorrespondences(VolumetricFaceModel<T>& volModel, const TemplateDescription& templateDescription);`
- L100 _public prototype_ `static bool CreateVolumetricFaceModelFromRig(const Rig<T>& rig, const TemplateDescription& templateDescription, const VolumetricFaceModel<T>& referenceModel, VolumetricFaceModel<T>& output, bool optimizeTets);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/nrr/include/nrr/volumetric/VolumetricFaceModel.h` (Private)


#### class `VolumetricFaceModel`  
`template <class T> class VolumetricFaceModel`  
_L17-65_
- L20 _public prototype_ `bool Load(const std::string& directory);`
- L21 _public prototype_ `bool Save(const std::string& directory, bool forceOverwrite = false) const;`
- L23 _public prototype_ `const std::string GetCraniumMeshName() const;`
- L24 _public prototype_ `const std::string GetMandibleMeshName() const;`
- L25 _public prototype_ `const std::string GetFleshMeshName() const;`
- L27 _public function_ `const Mesh<T>& GetSkinMesh() const`
- L28 _public function_ `const Mesh<T>& GetFleshMesh() const`
- L29 _public function_ `const Mesh<T>& GetCraniumMesh() const`
- L30 _public function_ `const Mesh<T>& GetMandibleMesh() const`
- L31 _public function_ `const Mesh<T>& GetTeethMesh() const`
- L32 _public function_ `const TetMesh<T>& GetTetMesh() const`
- L33 _public function_ `const BarycentricEmbedding<T>& Embedding() const`
- L34 _public function_ `const std::vector<std::pair<int, int>>& SkinFleshMapping() const`
- L35 _public function_ `const std::vector<std::pair<int, int>>& CraniumFleshMapping() const`
- L36 _public function_ `const std::vector<std::pair<int, int>>& MandibleFleshMapping() const`
- L37 _public function_ `const std::vector<std::pair<int, BarycentricCoordinates<T>>>& TetFleshMapping() const`
- L38 _public function_ `const std::vector<std::pair<int, BarycentricCoordinates<T>>>& FleshTetMapping() const`
- L40 _public prototype_ `void SetSkinMeshVertices(const Eigen::Matrix<T, 3, -1>& skinVertices);`
- L41 _public prototype_ `void SetFleshMeshVertices(const Eigen::Matrix<T, 3, -1>& fleshVertices);`
- L42 _public prototype_ `void SetCraniumMeshVertices(const Eigen::Matrix<T, 3, -1>& craniumVertices);`
- L43 _public prototype_ `void SetMandibleMeshVertices(const Eigen::Matrix<T, 3, -1>& mandibleVertices);`
- L44 _public prototype_ `void SetTeethMeshVertices(const Eigen::Matrix<T, 3, -1>& teethVertices);`
- L45 _public prototype_ `void SetTetMeshVertices(const Eigen::Matrix<T, 3, -1>& tetVertices);`
- L47 _public prototype_ `void UpdateFleshMeshVerticesFromSkinCraniumAndMandible();`
- L50 _private member_ `Mesh<T> m_skinMesh;`
- L51 _private member_ `Mesh<T> m_fleshMesh;`
- L52 _private member_ `Mesh<T> m_craniumMesh;`
- L53 _private member_ `Mesh<T> m_mandibleMesh;`
- L54 _private member_ `Mesh<T> m_teethMesh;`
- L56 _private member_ `TetMesh<T> m_tetMesh;`
- L58 _private member_ `BarycentricEmbedding<T> m_embedding;`
- L59 _private member_ `std::vector<std::pair<int, BarycentricCoordinates<T>>> m_tetFleshMapping;`
- L60 _private member_ `std::vector<std::pair<int, BarycentricCoordinates<T>>> m_fleshTetMapping;`
- L62 _private member_ `std::vector<std::pair<int, int>> m_skinFleshMapping;`
- L63 _private member_ `std::vector<std::pair<int, int>> m_craniumFleshMapping;`
- L64 _private member_ `std::vector<std::pair<int, int>> m_mandibleFleshMapping;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/resourceloader/include/resourceloader/IMetaHumanFileResourceLoader.h` (Private)


#### class `IMetaHumanFileResourceLoader`  
`class IMetaHumanFileResourceLoader`  
_L11-33_
- L14 _public prototype_ `virtual ~IMetaHumanFileResourceLoader() = default;`
- L17 _public prototype_ `virtual bool Exists(const char* InPathUtf8) const = 0;` — Check if a path (UTF-8) exists.
- L20 _public prototype_ `virtual bool ReadAllText(const char* InPathUtf8, char*& OutData, std::size_t& OutSize) const = 0;` — Read text file as raw UTF-8 bytes. Allocates a buffer that has to be freed
- L23 _public prototype_ `virtual bool ReadAllBytes(const char* InPathUtf8, void*& OutData, std::size_t& OutSize) const = 0;` — /  Read binary file as raw bytes. Allocates a buffer that has to be freed
- L26 _public prototype_ `virtual void Free(const void* InPtr) const = 0;` — Release any pointer previously returned via Read / Resolve functions
- L31 _public prototype_ `virtual bool ResolveDataLoadingPath(const char* InBasePathUtf8, const std::size_t& InBaseSize, const char* InAppendPathUtf8, std::size_t& InAppendSize, char*& OutPathUtf8, std::size_t& OutSize) const = 0;` — Constructs a valid path for data that could be loaded based on the resource loader type. Allocates a buffer that has to be freed. Expects a null terminated base and appended input

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/resourceloader/include/resourceloader/MetaHumanFileResourceLoader.h` (Private)


#### class `FMetaHumanFileResourceLoader`  
`class FMetaHumanFileResourceLoader : public IMetaHumanFileResourceLoader`  
_L16-59_
- inherits: `IMetaHumanFileResourceLoader`
- L20 _public prototype_ `virtual bool Exists(const char* InPathUtf8) const override;` — IMetaHumanFileResourceLoader
- L21 _public prototype_ `virtual bool ReadAllText(const char* InPathUtf8, char*& OutData, std::size_t& OutSize) const override;`
- L22 _public prototype_ `virtual bool ReadAllBytes(const char* InPathUtf8, void*& OutData, std::size_t& OutSize) const override;`
- L23 _public prototype_ `virtual void Free(const void* InPtr) const override;`
- L24 _public prototype_ `virtual bool ResolveDataLoadingPath(const char* InBasePathUtf8, const std::size_t& InBaseSize, const char* InAppendPathUtf8, std::size_t& InAppendSize, char*& OutPathUtf8, std::size_t& OutSize) const override;`
- L28 _public prototype_ `static TITAN_NAMESPACE::JsonElement GetJsonElementForFile(const std::string& InFilePath);` — Reads the json data based on static IResourceLoader implementation of ReadAllText override and returns json element
- L31 _public prototype_ `static std::string GetResolvedPathForFile(const std::string& InBasePathUtf8, const std::string& InAppendPathUtf8);` — Appends the paths based on the corresponding implementation of static IResourceLoader
- L34 _public prototype_ `static bool ResourceExists(const std::string& InResourcePathUtf8);` — A convenience function that wraps around the overriden Exists function for static IResourceLoader
- L50 _public typedef_ `using BoundedStreamPtr = pma::ScopedPtr<::trio::BoundedIOStream, BoundedDestroy>;` — Unified smart pointer type that contains deleter
- L53 _public prototype_ `static BoundedStreamPtr GetBoundedIOStreamFromFile(const std::string& InFilePath, bool bForceMemoryStream = false);` — A convenience function that returns File or Memory based IO stream for input binary file. Or nullptr if failed
- L58 _private prototype_ `static std::string ToStdString(const char* InData, std::size_t InSize);` — Copies raw UTF-8 (InData/InSize) into std::string.

#### struct `FMetaHumanFileResourceLoader::BoundedDestroy`  
`struct BoundedDestroy`  
_L37-47_
- desc: Type-erased deleter that can call either FileStream::destroy or MemoryStream::destroy
- L39 _public typedef_ `using Fn = void (*)(trio::BoundedIOStream*);`
- L40 _public member_ `Fn fn { nullptr };`
- L42 _public function_ `void operator()(trio::BoundedIOStream* p)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace trio`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/resourceloader/include/resourceloader/MetaHumanResourceLoaderHub.h` (Private)


#### class `FMetaHumanResourceLoaderHub`  
`class FMetaHumanResourceLoaderHub`  
_L9-26_
- L13 _public prototype_ `static void Install(IMetaHumanFileResourceLoader* InResourceLoader);` — Install a process-wide loader for the singleton
- L16 _public prototype_ `static IMetaHumanFileResourceLoader& GetResourceLoader();` — Access the active loader. Never null.
- L19 _private prototype_ `FMetaHumanResourceLoaderHub() = default;`
- L20 _private prototype_ `FMetaHumanResourceLoaderHub(const FMetaHumanResourceLoaderHub&) = delete;`
- L21 _private prototype_ `FMetaHumanResourceLoaderHub& operator=(const FMetaHumanResourceLoaderHub&) = delete;`
- L23 _private prototype_ `static IMetaHumanFileResourceLoader& FallbackFileLoader();`
- L25 _private member_ `static IMetaHumanFileResourceLoader* ResourceLoader;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/BarycentricCoordinatesForOddLods.h` (Private)


#### class `BarycentricCoordinatesForOddLods`  
`template <class T> class BarycentricCoordinatesForOddLods`  
_L17-51_
- desc: Simple class for representing the barycentric coordinates for the head mesh for odd lods which are calculated relative to the previous lod head mesh
- L20 _public prototype_ `BarycentricCoordinatesForOddLods() = default;`
- L26 _public prototype_ `void Init(const RigGeometry<T>& headRigGeometry);` — initialise the class from the supplied (head) rigGeometry. @param[in] rigGeometry: the rig geometry for the head rig.
- L29 _public prototype_ `bool ReadJson(const JsonElement& json);` — Read data from json element
- L32 _public prototype_ `void WriteJson(JsonElement& json) const;` — Write the BarycentricCoordinatesForOddLods to Json
- L39 _public prototype_ `bool IsValidForRig(const RigGeometry<T>& faceRigGeometry) const;` — Check if the confifg is valid for the supplied face rig. Returns true if it is valid, false if not. Checks that a set of barycentric coordinates is available for each odd lod, and that there are the correct number of barycentric coordinates for the current lod head mesh, and that the vertex indices for the bcs are in range for the previous lod head mesh
- L46 _public prototype_ `const std::map<int, std::vector<std::pair<bool, BarycentricCoordinates<T>>>>& GetBarycentricCoordinatesForOddLods() const;` — Get the map of mesh seam snap configs for each head mesh from combined body mesh to head mesh for each lod. Returns a map of (head) lod to a corresponding vector of pairs of boolean and BaryCentric coordinates, for each vertex in the current lod head mesh, how it maps onto the vertices of the previous lod, with the bool set to true to indicate a valid mapping and false to indicate an invalid mapping
- L50 _private member_ `std::map<int, std::vector<std::pair<bool, BarycentricCoordinates<T>>>> m_barycentricCoordinatesForOddLods;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/BindPoseJointsCalculation.h` (Private)


#### class `BindPoseJointsCalculation`  
`class BindPoseJointsCalculation`  
_L12-48_
- L15 _public prototype_ `BindPoseJointsCalculation();`
- L16 _public prototype_ `~BindPoseJointsCalculation();`
- L17 _public prototype_ `BindPoseJointsCalculation(BindPoseJointsCalculation&& o);`
- L18 _public prototype_ `BindPoseJointsCalculation(const BindPoseJointsCalculation& o) = delete;`
- L19 _public prototype_ `BindPoseJointsCalculation& operator=(BindPoseJointsCalculation&& o);`
- L20 _public prototype_ `BindPoseJointsCalculation& operator=(const BindPoseJointsCalculation& o) = delete;`
- L22 _public prototype_ `bool LoadVolumetricConfig(const std::string& filepath);`
- L23 _public prototype_ `bool LoadVolumetricJointsJson(const JsonElement& json);`
- L25 _public prototype_ `bool LoadSurfaceConfig(const std::string& filepath);`
- L26 _public prototype_ `bool LoadSurfaceJointsMapFromJson(const JsonElement& jsonData);`
- L28 _public prototype_ `bool Load(const std::string& surfaceJointsConfig, const std::string& volumetricJointsConfig);`
- L30 _public prototype_ `void UpdateVolumetric(Eigen::Matrix<float, 3, -1>& vertices, const std::map<std::string, std::pair<int, int>>& meshMapping, const std::map<std::string, int>& jointNameToId) const;`
- L34 _public prototype_ `void UpdateSurface(Eigen::Matrix<float, 3, -1>& vertices, const int jointOffset, const std::map<std::string, int>& jointNameToId) const;`
- L36 _public prototype_ `void Update(Eigen::Matrix<float, 3, -1>& vertices, const int jointOffset, const std::map<std::string, std::pair<int, int>>& meshMapping, const std::map<std::string, int>& jointNameToId) const;`
- L39 _public prototype_ `bool VolumetricDataLoaded() const;`
- L41 _public prototype_ `bool SurfaceDataLoaded() const;`
- L43 _public prototype_ `std::vector<std::string> SurfaceJointsList() const;`
- L47 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/BodyGeometry.h` (Private)


#### class `BodyGeometry`  
`template <class T> class BodyGeometry`  
_L20-149_
- desc: BodyGeometry implements the rig geometry evaluation based on rig logic inputs.
- L26 _public prototype_ `explicit BodyGeometry(const std::shared_ptr<TaskThreadPool>& taskThreadPool);`
- L27 _public prototype_ `explicit BodyGeometry(bool useMultithreading = true);`
- L28 _public prototype_ `BodyGeometry(int numLods, bool useMultithreading = true);`
- L29 _public prototype_ `~BodyGeometry() = default;`
- L30 _public prototype_ `BodyGeometry(BodyGeometry&&) = default;`
- L31 _public prototype_ `BodyGeometry(BodyGeometry&) = default;`
- L32 _public prototype_ `BodyGeometry& operator=(BodyGeometry&&) = default;`
- L33 _public prototype_ `BodyGeometry& operator=(const BodyGeometry&) = default;`
- L35 _public prototype_ `void SetThreadPool(const std::shared_ptr<TaskThreadPool>& taskThreadPool);`
- L37 _public prototype_ `std::shared_ptr<BodyGeometry> Clone() const;`
- L39 _public prototype_ `void SetNumLODs(const int l);`
- L40 _public prototype_ `int GetNumLODs() const;`
- L43 _public prototype_ `bool Init(const dna::Reader* reader, bool computeMeshNormals = false);` — Initializes BodyGeometry with the data from the dna::BinaryStreamReader
- L45 _public prototype_ `static Mesh<T> ReadMesh(const dna::Reader* reader, int meshIndex);` — Assembles the mesh at index @p meshIndex stored within dna::BinaryStreamReader
- L48 _public prototype_ `State EvaluateBodyGeometry(const int lod, const DiffData<T>& diffJoints, const DiffData<T>& diffPsd) const;` — Sets the joints and evaluates the mesh vertices for LOD @p lod and mesh indices @p meshIndices.
- L51 _public prototype_ `State& EvaluateBodyGeometry(const int lod, const DiffData<T>& diffJoints, const DiffData<T>& diffPsd, State& state) const;` — Sets the joints and evaluates the mesh vertices for LOD @p lod and mesh indices @p meshIndices.
- L52 _public prototype_ `State& EvaluateIndexedBodyGeometry(const int lod, const DiffData<T>& diffJoints, const DiffData<T>& diffPsd, const std::vector<int>& indices, State& state) const;`
- L53 _public prototype_ `State& EvaluateBodyGeometryWithOffset(const int lod, const DiffDataMatrix<T, 3, -1>& offset, const DiffData<T>& diffJoints, const DiffData<T>& diffPsd, State& state) const;`
- L56 _public function_ `const Mesh<T>& GetMesh(const int lod) const` — @return the mesh
- L57 _public function_ `Mesh<T>& GetMesh(const int lod)`
- L60 _public function_ `int NumJoints() const` — get num components
- L61 _public function_ `int NumBlendshapes(int lod) const`
- L64 _public function_ `const std::vector<std::string>& GetJointNames() const` — get joint names
- L65 _public function_ `std::vector<std::string>& GetJointNames()`
- L68 _public prototype_ `int GetJointIndex(const std::string& jointName) const;` — get joint index by name
- L71 _public function_ `const Eigen::VectorXi& GetBlendshapeMap(const int lod) const` — get blendshape data
- L72 _public function_ `Eigen::VectorXi& GetBlendshapeMap(const int lod)`
- L73 _public function_ `const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>& GetBlendshapeMatrix(const int lod) const`
- L74 _public function_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor>& GetBlendshapeMatrix(const int lod)`
- L77 _public function_ `const std::vector<int>& GetJointParentIndices() const` — get joint parent indices
- L78 _public function_ `std::vector<int>& GetJointParentIndices()`
- L79 _public prototype_ `int GetParentIndex(int jointIndex) const;`
- L82 _public function_ `const std::vector<Eigen::Transform<T, 3, Eigen::Affine>>& GetBindMatrices() const` — @return the current bind matrix of the joint rig.
- L84 _public function_ `const Eigen::Matrix3X<T>& GetJointRestPoses() const`
- L85 _public function_ `Eigen::Matrix3X<T>& GetJointRestPoses()`
- L87 _public function_ `const std::vector<Eigen::Matrix<T, 3, 3>>& GetJointRestOrientation() const`
- L88 _public function_ `std::vector<Eigen::Matrix<T, 3, 3>>& GetJointRestOrientation()`
- L90 _public function_ `const SparseMatrix<T>& GetVertexInfluenceWeights(const int lod) const`
- L91 _public function_ `SparseMatrix<T>& GetVertexInfluenceWeights(const int lod)`
- L93 _public prototype_ `void UpdateBindPoses();`
- L96 _public prototype_ `void EvaluateJointDeltas(const DiffData<T>& diffJoints, State& state, bool evaluateSkinningMatrices = true) const;` — Evaluates the joint deltas and stores it in @p state.
- L98 _public prototype_ `const Eigen::Matrix3X<T> EvaluateInverseSkinning(const int lod, const State& state, const Eigen::Matrix3X<T>& vertices);` — perform inverse skinning for a given state plus optional mesh
- L102 _private prototype_ `void EvaluateJointDeltasWithoutJacobians(const DiffData<T>& diffJoints, State& state) const;` — Evaluates the joint deltas and stores it in @p state.
- L105 _private prototype_ `const std::pair<Eigen::Matrix<T, 3, -1>, std::vector<Eigen::Matrix<T, 3, 3>>> EvaluateInverseJointDeltas(const DiffData<T>& diffJoints, const State& state) const;` — Get original joint rest poses from state and pose
- L114 _private prototype_ `void EvaluateBlendshapes(const int lod, const DiffData<T>& diffPsd, State& state) const;` — Evaluates the mesh vertices of for LOD @p lod and mesh index @p meshIndex. @param diffPsd          The psd coefficients. Typically the output from RigLogic::EvaluatePsd() @param lod              The lod for which to evalute the vertices. @param meshIndex        Which mesh to evaluate. @return the evaluated deformed mesh vertices. The output contains Jacobians if either the internal rig has the jacobians set, or if @diffBlendshapes contains the Jacobian.
- L115 _private prototype_ `void EvaluateIndexedBlendshapes(const int lod, const DiffData<T>& diffPsd, State& state, const std::vector<int>& indices) const;`
- L118 _private prototype_ `void EvaluateSkinningWithoutJacobians(const int lod, State& state) const;` — evaluates the skinning for geometry @p geometryName with state as input (evaluated blendshape vertices) and output (final vertices).
- L119 _private prototype_ `void EvaluateSkinningWithJacobians(const int lod, State& state) const;`
- L123 _private prototype_ `void EvaluateIndexedSkinningWithoutJacobians(const int lod, State& state, const std::vector<int>& indices) const;` — evaluates the skinning only for the given vertex indices for geometry @p geometryName with state as input (evaluated blendshape vertices) and output (final vertices).
- L124 _private prototype_ `void EvaluateIndexedSkinningWithJacobians(const int lod, State& state, const std::vector<int>& indices) const;`
- L128 _private member_ `std::vector<Mesh<T>> mesh;` — the mesh topology
- L131 _private member_ `std::vector<Eigen::VectorXi> blendshapeControlsToMeshBlendshapeControls;` — selection of which blendshapes are used by this mesh
- L132 _private member_ `std::vector<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> blendshapeMatrixDense;`
- L135 _private member_ `std::vector<SparseMatrix<T>> vertexInfluenceWeights;` — skinning data
- L138 _private member_ `std::vector<std::string> jointNames;` — joint data
- L139 _private member_ `std::vector<int> jointParentIndices;`
- L141 _private member_ `Eigen::Matrix<T, 3, -1> jointRestPose;`
- L142 _private member_ `std::vector<Eigen::Matrix<T, 3, 3>> jointRestOrientation;`
- L145 _private member_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> jointBindPoses;` — bind pose
- L146 _private member_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> jointInverseBindPoses;`
- L148 _private member_ `std::shared_ptr<TaskThreadPool> taskThreadPool{};`

#### class `BodyGeometry::State`  
`template <class T> class BodyGeometry<T>::State`  
_L154-235_
- desc: Rig geometry state containing results of a specific evaluation
- L157 _public function_ `State()`
- L158 _public prototype_ `~State() = default;`
- L159 _public prototype_ `State(State&&) = default;`
- L160 _public prototype_ `State& operator=(State&&) = default;`
- L161 _public prototype_ `State(const State&) = default;`
- L162 _public prototype_ `State& operator=(const State&) = default;`
- L170 _public function_ `const DiffDataMatrix<T, 3, -1>& Vertices() const` — @return const std::vector<DiffDataMatrix<T, 3, -1>>&  the evaluated vertices. See BodyGeometry<T>::EvaluateBodyGeometry @warning The returned DiffDataMatrices are only valid as long as the State has not been updated by another call to BodyGeometry<T>::EvaluateBodyGeometry with the same state. Explanation: the dense matrix of the Jacobian is resized in BodyGeometry<T>::EvaluateBodyGeometry and therefore the DiffDataMatrix Jacobian will map to an invalidated dense matrix.
- L173 _public function_ `const std::vector<Eigen::Transform<T, 3, Eigen::Affine>>& GetWorldMatrices() const` — @return the current world matrix of the joint rig.
- L175 _public function_ `const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>& GetWorldMatricesJacobian() const`
- L178 _public function_ `const std::vector<Eigen::Transform<T, 3, Eigen::Affine>>& GetLocalMatrices() const` — @return the current local matrix of the joint rig.
- L181 _public function_ `const std::vector<Eigen::Transform<T, 3, Eigen::Affine>>& GetSkinningMatrices() const` — @return the current skinning matrix of the joint rig.
- L184 _public function_ `const Vector<T>& GetBlendshapeCoefficients() const` — @return the blendshape coefficients
- L187 _public function_ `const Eigen::Matrix3X<T>& GetBlendshapeVertices() const` — @return the blendshape mesh of index i
- L190 _public function_ `const std::shared_ptr<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>& GetBlendshapeJacobian() const` — @return the blendshape mesh jacobian
- L194 _private member_ `DiffDataMatrix<T, 3, -1> vertices = DiffDataMatrix<T, 3, -1>(Eigen::Matrix<T, 3, -1>());` — the evaluated vertices
- L196 _private member_ `DiffDataMatrix<T, 3, -1> jointWorldTranslations = DiffDataMatrix<T, 3, -1>(Eigen::Matrix<T, 3, -1>());`
- L199 _private member_ `bool withJacobians = false;` — flag specifying whether the state has been set including Jacobians
- L202 _private member_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> localMatrices;` — the evaluated local transformations for each joint
- L205 _private member_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> worldMatrices;` — the evaluated world transformations for each joint
- L208 _private member_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> skinningMatrices;` — the evaluated skinning transformations for each joint
- L211 _private member_ `DiffData<T> diffMeshBlendshapes = DiffData<T>(Eigen::VectorX<T>());` — the evaluated blendshape weights
- L214 _private member_ `int jointJacobianColOffset = -1;` — local caching of the jacobians for the joints
- L215 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> jointDeltasJacobian;`
- L216 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> localMatricesJacobian;`
- L217 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> worldMatricesJacobian;`
- L218 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> skinningMatricesJacobian;`
- L221 _private member_ `Eigen::Matrix<T, 3, -1> blendshapeVertices;` — blendshapes as they were evaluated
- L222 _private member_ `std::shared_ptr<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> blendshapeJacobianRM = std::make_shared<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>();`
- L223 _private member_ `int blendshapeJacobianColOffset = -1;`
- L226 _private member_ `int offsetJacobianColOffset = -1;` — offset Jacobian info (for differentiable offset in EvaluateBodyGeometryWithOffset)
- L227 _private member_ `std::shared_ptr<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> offsetJacobianRM = std::make_shared<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>();`
- L230 _private member_ `Eigen::Matrix<T, 3, -1> finalVertices;` — final vertices after applying the joint evaluation
- L231 _private member_ `std::shared_ptr<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> finalJacobianRM = std::make_shared<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>();`
- L232 _private member_ `int finalJacobianColOffset = -1;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/BodyLogic.h` (Private)


#### class `BodyLogic`  
`template <class T> class BodyLogic`  
_L23-128_
- desc: BodyLogic implements rig logic including Jacobian for parametric body models This is quite more open than the face rig version, as we need to have easy acces to edit/change the values of things
- L37 _public prototype_ `BodyLogic();`
- L38 _public prototype_ `BodyLogic(int _numLods);`
- L39 _public prototype_ `~BodyLogic() = default;`
- L40 _public prototype_ `BodyLogic(BodyLogic&&) = default;`
- L41 _public prototype_ `BodyLogic(BodyLogic&) = default;`
- L42 _public prototype_ `BodyLogic& operator=(BodyLogic&&) = default;`
- L43 _public prototype_ `BodyLogic& operator=(const BodyLogic&) = default;`
- L45 _public prototype_ `std::shared_ptr<BodyLogic> Clone() const;`
- L48 _public prototype_ `bool Init(const dna::Reader* reader);` — Initializes BodyLogic with the data from the dna::BinaryStreamReader
- L50 _public prototype_ `bool InitRBFJointMatrix(const dna::Reader* reader);`
- L53 _public function_ `int NumGUIControls() const` — @return the number of gui controls of the rig
- L56 _public function_ `int NumRawControls() const` — @return the number of raw controls of the rig
- L59 _public function_ `int NumLODs() const` — @return the number of lods
- L60 _public prototype_ `void SetNumLODs(const int l);`
- L66 _public prototype_ `DiffData<T> EvaluateRawControls(const DiffData<T>& guiControls) const;` — Evaluate the raw controls given the input gui controls. Throws an expection is the size is incorrect. There is no clamping involved, any gui controls exceeding their range will extrapolate the values.
- L72 _public prototype_ `DiffData<T> EvaluateJoints(const int lod, const DiffData<T>& rawControls) const;` — Evaluate the joint values from the raw values. Throws an expection is the size is incorrect. You would typically call it with the output from EvaluateRawControls().
- L73 _public prototype_ `DiffData<T> EvaluateRbfJoints(const int lod, const DiffData<T>& rbfControls) const;`
- L78 _public function_ `const std::vector<std::string>& GuiControlNames() const` — @return the names of the GUI controls.
- L79 _public function_ `std::vector<std::string>& GuiControlNames()`
- L84 _public function_ `const std::vector<std::string>& RawControlNames() const` — @return the names of the raw controls.
- L85 _public function_ `std::vector<std::string>& RawControlNames()`
- L90 _public function_ `const std::vector<GuiToRawInfo>& GuiToRawMapping() const` — @return the gui control mapping
- L91 _public function_ `std::vector<GuiToRawInfo>& GuiToRawMapping()`
- L96 _public function_ `const Eigen::Matrix<T, 2, -1>& GuiControlRanges() const` — @return the gui control ranges
- L97 _public function_ `Eigen::Matrix<T, 2, -1>& GuiControlRanges()`
- L102 _public function_ `const SparseMatrix<T>& GetJointMatrix(const int lod) const` — @return the joint matrix mapping raw controls to joint maps for the given lod
- L103 _public function_ `SparseMatrix<T>& GetJointMatrix(const int lod)`
- L105 _public function_ `const SparseMatrix<T>& GetRbfJointMatrix(const int lod) const`
- L106 _public function_ `SparseMatrix<T>& GetRbfJointMatrix(const int lod)`
- L109 _private prototype_ `void SortGuiControlMapping();`
- L112 _private member_ `int numLODs;`
- L114 _private member_ `std::vector<std::string> guiControlNames;`
- L115 _private member_ `std::vector<std::string> rawControlNames;`
- L118 _private member_ `std::vector<GuiToRawInfo> guiToRawMapping;` — ### GUI to Raw mapping ###
- L121 _private member_ `Eigen::Matrix<T, 2, -1> guiControlRanges;` — the ranges for each gui control
- L124 _private member_ `std::vector<SparseMatrix<T>> jointMatrix;` — joint mapping
- L127 _private member_ `std::vector<SparseMatrix<T>> rbfJointMatrix;` — rbf joint matrix

#### struct `BodyLogic::GuiToRawInfo`  
`struct GuiToRawInfo`  
_L26-34_
- L28 _public member_ `int inputIndex;` — gui control (col index)
- L29 _public member_ `int outputIndex;` — raw control (row index)
- L30 _public member_ `T from;`
- L31 _public member_ `T to;`
- L32 _public member_ `T slope;`
- L33 _public member_ `T cut;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/CombinedBodyJointLodMapping.h` (Private)


#### class `CombinedBodyJointLodMapping`  
`template <class T> class CombinedBodyJointLodMapping`  
_L21-62_
- desc: A class for calculating a simple mapping for how skinning weights for joints should be propagated from LOD0 to higher LODs. This is intended for a rig where joints for higher lods are represented by a simple parent child relationship ie no new joints are introduced at intermediate lods. The approach first works out which joints are active for each lod, and for each joint in a higher lod, if that joint is not active, it pushes it up to the first active parent. The user can also specify options joints for which joints can be propagated to a combination of the first active parent joint, and the closest active sibling joint. The user can decide the split in influence between the parent joint (giving stability) and the sibling joint (giving more specific localized behaviour), and can also apply an optional inverse distance weighting ie if the parent joint is further away it gives less influence (and vice versa). Sibling joint propagation works well for joint clusters like fingers (and possibly toes) where some of the digits may be removed at higher lod(s).
- L24 _public function_ `CombinedBodyJointLodMapping()`
- L27 _public prototype_ `void CalculateMapping(const RigGeometry<T>& rigGeometry);` — | Calculate the joint mapping from RigGeometry as above
- L31 _public prototype_ `const std::vector<std::map<std::string, std::map<std::string, T>>>& GetJointMapping() const;` — Get the joint mapping for all Lods. For each lod, this returns a mapping for each lod which defines how to take each joint influence for that joint from lod 0 and spread it onto joint(s) in the current lod as a weighted sum of values from lod0
- L34 _public prototype_ `JsonElement ToJson() const;` — save the mapping to json
- L37 _public prototype_ `bool ReadJson(const JsonElement& jointPropagationMapJson);` — read the mapping from json
- L40 _public prototype_ `bool UseDistanceWeightingForSiblingPropagation() const;` — get whether or not we use distance weighting for sibling propagation
- L43 _public prototype_ `void SetUseDistanceWeightingForSiblingPropagation(bool bUseDistanceWeighting);` — set whether we use distance weighting for sibling propagation
- L46 _public prototype_ `T ParentWeightForSiblingPropagation() const;` — get the parent weighting for sibling propagation
- L49 _public prototype_ `void SetParentWeightForSiblingPropagation(const T& parentWeighting);` — set the parent weighting for sibling propagation
- L52 _public prototype_ `const std::vector<std::string>& JointsToIncludeSiblingsInPropagation() const;` — get the list of (parent) joints to include in sibling propagation ie all child joints below this joint will use sibling propagation
- L55 _public prototype_ `void SetJointsToIncludeSiblingsInPropagation(const std::vector<std::string>& jointsToIncludeInSiblingPropagation);` — set the list of (parent) joints to include in sibling propagation ie all child joints below this joint will use sibling propagation
- L58 _private member_ `std::vector<std::map<std::string, std::map<std::string, T>>> m_combinedBodyJointLodMapping;`
- L59 _private member_ `std::vector<std::string> m_jointsToIncludeSiblingsInPropagation = { "hand_r",`
- L60 _private member_ `T m_parentWeightForSiblingPropagation = T(0.25f);`
- L61 _private member_ `bool m_bUseDistanceWeightingForSiblingPropagation = true;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/DriverJointControls.h` (Private)


#### class `DriverJointControls`  
`class DriverJointControls`  
_L23-72_
- L43 _public prototype_ `DriverJointControls();`
- L44 _public prototype_ `~DriverJointControls();`
- L45 _public prototype_ `DriverJointControls(DriverJointControls&& other) noexcept;`
- L46 _public prototype_ `DriverJointControls& operator=(DriverJointControls&& other) noexcept;`
- L47 _public prototype_ `DriverJointControls(const DriverJointControls& other);`
- L48 _public prototype_ `DriverJointControls& operator=(const DriverJointControls& other);`
- L51 _public prototype_ `template <class T> DiffData<T> EvaluateRawControlsFromEuler(const DiffData<T>& eulerControls) const;`
- L54 _public prototype_ `template <class T> DiffData<T> EvaluateRawControlsFromJoints(const DiffData<T>& jointDiff) const;`
- L57 _public prototype_ `const std::vector<std::string>& EulerControlNames() const;`
- L58 _public prototype_ `const std::vector<std::uint16_t>& RawControlIndices() const;`
- L60 _public prototype_ `const std::map<int, Mapping>& Mappings() const;`
- L62 _public prototype_ `int JointIndexFromEulerControl(std::uint16_t control) const;`
- L63 _public prototype_ `int JointIndexFromRawControl(std::uint16_t control) const;`
- L65 _public prototype_ `void Init(const dna::Reader* reader);`
- L66 _public prototype_ `void RemoveJoints(const std::vector<int>& newToOldJointMapping);`
- L70 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

#### struct `DriverJointControls::Mapping`  
`struct Mapping`  
_L26-41_
- L28 _public member_ `std::string jointName;`
- L30 _public member_ `std::uint16_t eulerX;`
- L31 _public member_ `std::uint16_t eulerY;`
- L32 _public member_ `std::uint16_t eulerZ;`
- L34 _public member_ `std::uint16_t rawX;`
- L35 _public member_ `std::uint16_t rawY;`
- L36 _public member_ `std::uint16_t rawZ;`
- L37 _public member_ `std::uint16_t rawW;`
- L38 _public prototype_ `static std::map<int, Mapping> Generate(const dna::Reader* reader);`
- L39 _public prototype_ `static std::vector<std::string> GetEulerControlNames(const std::map<int, Mapping>& mappings);`
- L40 _public prototype_ `static std::vector<std::uint16_t> GetRawControlIndices(const std::map<int, Mapping>& mappings);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/EyelashConnectedVertices.h` (Private)


#### struct `EyelashConnectedVertices`  
`template <class T> struct EyelashConnectedVertices`  
_L17-36_
- desc: a little struct to represent eyelash connected vertices and how they should be transformed relative to the head mesh
- L19 _public member_ `static constexpr int32_t version = 1;`
- L21 _public member_ `bool valid = false;`
- L22 _public member_ `std::vector<int> indices;`
- L23 _public member_ `Affine<T, 3, 3> affine;`
- L24 _public member_ `std::vector<int> headvIDs;`
- L27 _public prototype_ `static bool InitializeEyelashMapping(const Mesh<T>& headMesh, const Mesh<T>& eyelashesMesh, const std::vector<std::pair<int, T>>& eyelashRoots, std::vector<std::shared_ptr<EyelashConnectedVertices<T>>>& eyelashConnectedVertices);` — initialize the eyelash mapping between the eyelashes mesh and head mesh, returning the mapping as a vector of eyelash connected vertices. Returns true if initialized successfully, false otherwise (eg if eyelashRoots indices are out of range)
- L31 _public prototype_ `static void ApplyEyelashMapping(const Mesh<T>& srcHeadMesh, const Eigen::Matrix<T, 3, -1>& targetHeadMeshVertices, const Mesh<T>& srcEyelashesMesh, const std::vector<std::shared_ptr<EyelashConnectedVertices<T>>>& eyelashConnectedVertices, Eigen::Matrix<T, 3, -1>& updatedEyelashVertices);` — apply the eyelash mapping using the supplied head and eyelash meshes and eyelash connected vertices, returning the results in updatedEyelashVertices. Will fail with a CARBON_CRITICAL if the head meshes do not contain a consistent number of verticesm or the eyelash mesh and eyelashConnectedVertices are inconsistent with each other or with the head mesh
- L35 _public prototype_ `static void Reduce(std::vector<std::shared_ptr<EyelashConnectedVertices<T>>>& eyelashConnectedVertices);` — reduce the number of eyelashes to segments

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace trio`
- L40 _prototype_ `template <class T> bool ToBinaryFile(FILE* pFile, const EyelashConnectedVertices<T>& eyelashConnectedVertices);`
- L43 _prototype_ `template <class T> bool FromBinaryFile(FILE* pFile, EyelashConnectedVertices<T>& eyelashConnectedVertices);`
- L46 _prototype_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, EyelashConnectedVertices<T>& eyelashConnectedVertices);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/Joint.h` (Private)


#### struct `JointHelper`  
`template <class T> struct JointHelper`  
_L19-19_
- L24 _public typedef_ `using SCALAR = T;`

#### struct `JointHelper`  
`template <class T, int R, int C> struct JointHelper<Eigen::Matrix<T, R, C>>`  
_L22-25_
- L24 _public typedef_ `using SCALAR = T;`

#### struct `JointHelper`  
`template <class T, int R, int C> struct JointHelper<DiffDataAffine<T, R, C>>`  
_L28-31_
- L24 _public typedef_ `using SCALAR = T;`

#### struct `JointHelper`  
`template <class T, int R, int C> struct JointHelper<Affine<T, R, C>>`  
_L33-36_
- L24 _public typedef_ `using SCALAR = T;`

#### class `Joint`  
`template <class AffineType> class Joint`  
_L42-232_
- desc: A Joint represents a local transformation
- L44 _private typedef_ `using T = typename JointHelper<AffineType>::SCALAR;`
- L47 _public function_ `Joint(const std::string& name = "") : m_name(name), m_parent(nullptr)`
- L49 _public function_ `const std::string& Name() const`
- L51 _public function_ `bool HasParent() const`
- L53 _public function_ `bool IsRoot() const`
- L55 _public function_ `const Joint* Parent() const`
- L57 _public function_ `bool SetParent(Joint* parent)`
- L80 _public function_ `void AddChild(Joint* child)`
- L89 _public function_ `void RemoveChild(Joint* child)`
- L94 _public function_ `int NumChildren() const`
- L97 _public function_ `bool HasChild(Joint* j, bool recursive) const` — @returns whether joint @p j is a child of this joint. Use @p recursive to check recursively.
- L117 _public function_ `const AffineType& LocalMatrix()`
- L119 _public function_ `void SetLocalMatrix(const AffineType& localMatrix)`
- L125 _public function_ `void SetLocalMatrix(AffineType&& localMatrix)`
- L131 _public function_ `const Affine<T, 3, 3>& BindMatrix() const`
- L136 _public function_ `void SetBindMatrix(const Affine<T, 3, 3>& bindMatrix)`
- L143 _public function_ `const AffineType& WorldMatrix()`
- L159 _public function_ `const AffineType& SkinningMatrix()`
- L170 _private function_ `void RemoveChild(Joint* child, bool updateChild)`
- L184 _private function_ `void InvalidateWorldMatrix()` — Set the world matrix as invalid, and therefore all children are also invalid
- L201 _private member_ `std::string m_name;` — name of this joint
- L204 _private member_ `Joint<AffineType>* m_parent;` — parent
- L207 _private member_ `std::vector<Joint<AffineType>*> m_children;` — children
- L210 _private member_ `AffineType m_localMatrix;` — local transformation matrix
- L213 _private member_ `Affine<T, 3, 3> m_bindMatrix;` — bind matrix
- L216 _private member_ `Affine<T, 3, 3> m_bindMatrixInverse;` — inverse of the bind matrix
- L224 _private member_ `std::optional<AffineType> m_worldMatrix;` — world transformation matrix
- L227 _private member_ `std::optional<AffineType> m_skinningMatrix;` — skinning matrix (m_worldMatrix * m_bindMatrixInverse)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/JointRig.h` (Private)


#### struct `InfluenceWeights`  
`template <class T> struct InfluenceWeights`  
_L13-20_
- L17 _public member_ `Eigen::VectorX<int> indices;` — vertex indices
- L19 _public member_ `Eigen::VectorX<T> weights;` — vertex weights

#### class `JointRig`  
`template <class AffineType> class JointRig`  
_L28-307_
- desc: A JointRig represents a hierarchy of joints and the set of influence weights on how each joint influences geometry. The deformed geometry can be evaluated with or without Jacobians.
- L31 _public typedef_ `using T = typename JointHelper<AffineType>::SCALAR;`
- L32 _public typedef_ `using JointPtr = std::shared_ptr<Joint<AffineType>>;`
- L35 _public function_ `JointRig()`
- L36 _public prototype_ `virtual ~JointRig() = default;`
- L38 _public prototype_ `JointRig(JointRig&) = delete;`
- L39 _public prototype_ `JointRig& operator=(const JointRig&) = delete;`
- L41 _public function_ `virtual void Clear()`
- L49 _public function_ `void AddJoint(const JointPtr& joint)` — Adds a new joint to the rig
- L63 _public function_ `JointPtr GetJoint(const std::string& name) const`
- L76 _public function_ `const std::map<std::string, JointPtr>& GetJoints() const`
- L78 _public function_ `std::vector<std::string> GetJointNames() const`
- L92 _public function_ `void AddInfluenceWeights(const std::string& geometryName, const std::map<std::string, InfluenceWeights<T>>& jointInfluenceWeights, int numVertices = -1)` — Add all joint influence weights for geometry @p geometryName. @param[in] numVertices  If numVertices < 0 then the number of vertices are infered from the vertex indices in @p jointInfluenceWeights.
- L167 _public function_ `InfluenceWeights<T> GetInfluenceWeights(const std::string& jointName, const std::string& geometryName) const`
- L214 _public function_ `std::vector<std::string> GetGeometryNames() const`
- L225 _public function_ `std::map<std::string, Affine<T, 3, 3>> GetState() const` — Returns the current state (local matrices) of all the joints
- L236 _public function_ `virtual void SetState(const std::map<std::string, Affine<T, 3, 3>>& state)` — Set the state of the joints
- L253 _public prototype_ `Eigen::Matrix<T, 3, -1> EvaluateGeometry(const std::string& geometryName, const Eigen::Matrix<T, 3, -1>& restVertices) const;` — Basic geometry evaluation. This does not calculate any Jacobian. Instantiated for float and double versions of Affine<T, 3, 3> and DiffDataAffine<T, 3, 3>
- L261 _public prototype_ `DiffDataMatrix<T, 3, -1> EvaluateGeometry(const std::string& geometryName, const DiffDataMatrix<T, 3, -1>& restVertices) const;` — Geometry evaluation with Jacobian. Instantiated for float and double versions of DiffDataAffine<T, 3, 3>
- L268 _public prototype_ `DiffData<T> EvaluateRegularization(const T rotationWeight, const T translationWeight, const std::map<std::string, Affine<T, 3, 3>>& restStates, const bool regularizeRoot = false) const;` — Calculates a regularization residual of the affine transformations of the rig against the save state Instantiated for float and double versions of DiffDataAffine<T, 3, 3>
- L275 _public function_ `void CheckValidity()` — Sanity checks for the rig
- L278 _public function_ `void CheckSingleRoot()` — JointRig only supports rigs with a single root joint
- L300 _private member_ `std::map<std::string, JointPtr> m_joints;` — map of joint name to joint
- L303 _private member_ `std::vector<JointPtr> m_jointsVector;` — vector of joints
- L306 _private member_ `std::map<std::string, SparseMatrix<T>> m_vertexInfluenceWeights;` — map of geometry name to map of vertex index to list of joint indices (@see m_jointsVector) and weight

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/JointRig2.h` (Private)


#### class `JointRig2`  
`template <class T> class JointRig2`  
_L16-134_
- desc: A JointRig represents a hierarchy of joints and the set of influence weights on how each joint influences geometry.
- L27 _public prototype_ `JointRig2() = default;`
- L28 _public prototype_ `~JointRig2() = default;`
- L29 _public prototype_ `JointRig2(JointRig2&&) = default;`
- L30 _public prototype_ `JointRig2& operator=(JointRig2&&) = default;`
- L31 _public prototype_ `JointRig2(JointRig2&) = default;`
- L32 _public prototype_ `JointRig2& operator=(const JointRig2&) = default;`
- L34 _public prototype_ `void Clear();`
- L36 _public function_ `int NumJoints() const`
- L42 _public prototype_ `void AddJoint(const std::string& newJointName);` — Adds a new joint to the rig
- L44 _public function_ `const std::vector<std::string>& GetJointNames() const`
- L49 _public prototype_ `int GetJointIndex(const std::string& jointName) const;`
- L51 _public function_ `int GetParentIndex(int jointIndex) const`
- L57 _public prototype_ `void AttachJointToParent(const std::string& childJointName, const std::string& parentJointName);` — Sets a joint to be the parent of another joint
- L60 _public prototype_ `bool IsChildOf(const std::string& jointName, const std::string& parentJointName) const;` — Checks if @p jointName is child of parentJointName
- L63 _public prototype_ `int HierarchyLevel(const std::string& jointName) const;` — @return the hierarchy level of the joint. 0 is a root joint, 1 is a joint one below the root, ...
- L64 _public prototype_ `int HierarchyLevel(int jointIndex) const;`
- L67 _public prototype_ `std::vector<std::vector<int>> GetJointsPerHierarchyLevel() const;` — @return vector of which joints indices are at what level
- L73 _public prototype_ `void SetSkinningWeights(const std::string& geometryName, const std::map<std::string, InfluenceWeights<T>>& jointInfluenceWeights, int numVertices = -1, bool normalizeWeights = true, bool allowNegativeWeights = false, ErrorInfo* errorInfo = nullptr);` — Add all joint influence weights for geometry @p geometryName. @param[in] numVertices  If numVertices < 0 then the number of vertices are infered from the vertex indices in @p jointInfluenceWeights.
- L84 _public prototype_ `Eigen::VectorX<T> GetSkinningWeights(const std::string& jointName, const std::string& geometryName, bool includingChildren = false) const;` — @returns the skinning weights for joint @p jointName on geometry @p geometryName. If @p inclduingChildren is True, then it will add the skinning weights of child joints.
- L87 _public prototype_ `InfluenceWeights<T> GetSkinningWeightsAsStruct(const std::string& jointName, const std::string& geometryName) const;` — Temporary method which returns JointRig API skinning weights
- L89 _public prototype_ `std::vector<std::string> GetGeometryNames() const;`
- L92 _public prototype_ `void CheckValidity();` — Sanity checks for the rig
- L95 _public prototype_ `void CheckSingleRoot();` — JointRig only supports rigs with a single root joint
- L98 _public prototype_ `const SparseMatrix<T>& GetSkinningWeights(const std::string& geometryName) const;` — @return the skin weights matrix for geometry @p geometryName
- L101 _public prototype_ `void SetSkinningWeights(const std::string& geometryName, const SparseMatrix<T>& smat);` — Explicity set the joint matrix for geometry @p geometryName
- L104 _public prototype_ `void RemoveSkinningWeights(const std::string& geometryName);` — Remove skin weights for a geometry @p geometryName
- L107 _public prototype_ `bool HasSkinningWeights(const std::string& geometryName) const;` — Check if skinning weights exist for geometry @p geometryName
- L112 _public prototype_ `void Resample(const std::string& geometryName, const std::vector<int>& newToOldMap);` — Resample the vertex influence weights for geometry @p geometryName, where influence for the new vertex i will have the old weights of vertex newToOldMap[i].
- L119 _public prototype_ `std::vector<int> RemoveUnusedJoints();` — @brief Remove all unused joints. @return Maps new joint indices to previous joint indices.
- L123 _public prototype_ `std::vector<int> GetSymmetricJointIndices() const;` — @returns vector of indices pointing to the symmetric joint. Symmetric joints are determined by looking at the joint names and searching for _R or _L in the name.
- L127 _private member_ `std::vector<std::string> m_jointNames;` — names of the joints
- L130 _private member_ `std::vector<int> m_jointParentIndices;` — maps a joint to its parent (via indices)
- L133 _private member_ `std::map<std::string, SparseMatrix<T>> m_skinningWeights;` — map of geometry name to sparse matrix with rows: vertices, columns: joint index, values: skin weight

#### struct `JointRig2::ErrorInfo`  
`struct ErrorInfo`  
_L19-24_
- L21 _public member_ `std::vector<int> unskinnedVertices;`
- L22 _public member_ `std::vector<int> unnormalizedVertices;`
- L23 _public member_ `std::vector<int> negativeWeightsVertices;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/JointRigVariable.h` (Private)


#### class `JointRigVariable`  
`template <class T> class JointRigVariable : public JointRig<DiffDataAffine<T, 3, 3>>`  
_L20-91_
- inherits: `JointRig<DiffDataAffine<T,3,3>>`
- desc: A 3D JointRig with variable local matrices that can be optimized
- L22 _private typedef_ `using JointPtr = typename JointRig<DiffDataAffine<T, 3, 3>>::JointPtr;`
- L25 _public prototype_ `virtual ~JointRigVariable() = default;`
- L27 _public function_ `virtual void Clear() override`
- L34 _public function_ `void CreateVariables()` — Create all variables associated to the joints
- L48 _public function_ `void EvaluateVariables(Context<T>* context)` — Evaluates the joint variables and sets the local affine transformation matrix of the rig including the Jacobians.
- L59 _public function_ `virtual void SetState(const std::map<std::string, Affine<T, 3, 3>>& state) override` — Set the joint state and update the variables
- L78 _public function_ `void SetDegreesOfFreedom(const std::string& jointName, bool rotation, bool translation)` — Sets the degrees of freedom of a joint @param rotation     Whether rotation is a degree of freedom (3 DOFs really) @param translation  Whether translation is a degree of freedom (3 DOFs really)
- L90 _private member_ `std::map<std::string, std::shared_ptr<AffineVariable<QuaternionVariable<T>>>> m_variables;` — the variables associated with the joints

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/LimitConstraintFunction.h` (Private)


#### class `LimitConstraintFunction`  
`template <class T> class LimitConstraintFunction`  
_L13-82_
- L18 _public function_ `static DiffData<T> Evaluate( const DiffData<T>& guiControls, const BodyLogic<T>& rig, const T weight)` — Function to a soft error based on the limits of the riglogic class

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/RBFLogic.h` (Private)


#### class `RBFLogic`  
`template <class T> class RBFLogic`  
_L28-70_
- L31 _public typedef_ `using SolverPtr = pma::ScopedPtr<rbfs::RBFSolver>;`
- L33 _public prototype_ `RBFLogic();`
- L34 _public prototype_ `~RBFLogic();`
- L36 _public prototype_ `RBFLogic(RBFLogic&&);`
- L37 _public prototype_ `RBFLogic& operator=(RBFLogic&&);`
- L39 _public prototype_ `RBFLogic(const RBFLogic&);`
- L40 _public prototype_ `RBFLogic& operator=(const RBFLogic&);`
- L42 _public prototype_ `DiffData<T> EvaluatePoseControlsFromRawControls(const DiffData<T>& rawControls) const;`
- L43 _public prototype_ `DiffData<T> EvaluatePoseControlsFromJoints(const DiffData<T>& joints, bool withJointScaling = false) const;`
- L45 _public prototype_ `bool Init(const dna::Reader* reader);`
- L46 _public prototype_ `void Write(dna::Writer* writer);`
- L48 _public prototype_ `const SolverPtr& GetSolver(int solverIndex) const;`
- L49 _public prototype_ `const std::vector<SolverPtr>& RBFSolvers() const;`
- L50 _public prototype_ `std::vector<std::uint16_t> SolverRawControlIndices(int solverIndex) const;`
- L51 _public prototype_ `const std::vector<float>& SolverRawTargetValues(int solverIndex) const;`
- L52 _public prototype_ `const std::vector<std::string>& SolverNames() const;`
- L53 _public prototype_ `const std::vector<std::uint16_t>& SolverPoseIndices(int solverIndex) const;`
- L54 _public prototype_ `const std::vector<std::uint16_t>& PoseOutputControlIndices(int poseIndex) const;`
- L55 _public prototype_ `const std::string& PoseOutputControlName(int poseOutputControlIndex) const;`
- L56 _public prototype_ `std::uint16_t PoseControlCount() const;`
- L57 _public prototype_ `std::uint16_t PoseControlOffset() const;`
- L58 _public prototype_ `const std::vector<std::string>& PoseNames() const;`
- L59 _public prototype_ `const std::vector<std::string>& PoseControlNames() const;`
- L60 _public prototype_ `bool SolverAutomaticRadius(int solverIndex) const;`
- L61 _public prototype_ `const DriverJointControls& GetDriverJointControls() const;`
- L63 _public prototype_ `void SetSolver(int solverIndex, const std::string& solverName, const std::vector<std::uint16_t>& poseIndices, rbfs::RBFSolverRecipe recipe);`
- L65 _public prototype_ `void RemoveJoints(const std::vector<int>& newToOldJointMapping);`
- L69 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/Rig.h` (Private)


#### class `Rig`  
`template <class T> class Rig`  
_L17-125_
- desc: Class combining RigLogic, RigGeometry, and the default values.
- L20 _public prototype_ `Rig();`
- L21 _public prototype_ `~Rig();`
- L23 _public prototype_ `Rig(const std::shared_ptr<const RigLogic<T>>& rigLogic, const std::shared_ptr<const RigGeometry<T>>& rigGeometry);`
- L33 _public prototype_ `bool LoadRig(const std::string& DNAFilename, bool withJointScaling = false, std::map<std::string, typename RigGeometry<T>::ErrorInfo>* errorInfo = nullptr);` — @brief Loads the rig from @p DNAFilename. @param DNAFilename The name of the DNA file. @param withJointScaling If False, then any joint scaling that is part of the DNA is discarded. Currently only pupils have scaling information. @return true   If DNA file could be read. @return false  If any error occurred during reading.
- L43 _public prototype_ `bool LoadRig(const dna::Reader* DNAStream, bool withJointScaling = false, std::map<std::string, typename RigGeometry<T>::ErrorInfo>* errorInfo = nullptr);` — @brief Loads the rig from @p DNAStream. @param DNAStream The DNA stream. @param withJointScaling If False, then any joint scaling that is part of the DNA is discarded. Currently only pupils have scaling information. @return true   If DNA file could be read. @return false  If any error occurred during reading.
- L46 _public prototype_ `bool VerifyTopology(const Mesh<T>& topology) const;` — Tests whether the rig adheres to \p topology
- L48 _public function_ `const std::shared_ptr<const RigLogic<T>>& GetRigLogic() const`
- L49 _public function_ `const std::shared_ptr<const RigGeometry<T>>& GetRigGeometry() const`
- L50 _public prototype_ `const std::vector<std::string>& GetGuiControlNames() const;`
- L51 _public prototype_ `const std::vector<std::string>& GetRawControlNames() const;`
- L53 _public function_ `const Mesh<T>& GetBaseMesh() const`
- L54 _public function_ `const Mesh<T>& GetBaseMeshTriangulated() const`
- L57 _public prototype_ `void UpdateBaseMeshTriangulation(const Mesh<T>& triangulatedMesh);` — Update the base mesh triangulation using @p triangulatedMesh
- L66 _public prototype_ `std::vector<Eigen::Matrix<T, 3, -1>> EvaluateVertices(const Eigen::VectorX<T>& controls, int lod, const std::vector<int>& meshIndices, ControlsType controlsType = ControlsType::GuiControls) const;` — Evaluates the vertices of multiple meshes
- L72 _public prototype_ `void EvaluateVertices(const Eigen::VectorX<T>& controls, int lod, const std::vector<int>& meshIndices, typename RigGeometry<T>::State& state, ControlsType controlsType = ControlsType::GuiControls) const;` — Evaluates the vertices of multiple meshes
- L79 _public prototype_ `void MakeBlendshapeOnly();` — Convert joint-based shapes into blendshape-only shapes. Does not create blendshapes for the eye geometry.
- L82 _public prototype_ `void ReduceToLOD0Only();` — Only keep the highest resolution mesh
- L88 _public prototype_ `void ReduceToMeshes(const std::vector<int>& meshIndices);` — @brief Reduce the rig to only contain the meshes @p meshIndices Removes unused joints in the rig.
- L91 _public prototype_ `void RemoveBlendshapes(const std::vector<int>& meshIndices);` — Remove the blendshapes for meshes @p meshIndices
- L94 _public prototype_ `void ReduceToGuiControls(const std::vector<int>& guiControls);` — Simplify the rig to only support @p guiControls. All other gui controls will be ignored even if the are non-zero.
- L97 _public prototype_ `void Resample(const std::map<int, std::vector<int>>& vertexIndicesMap);` — Resample the rig such that for each mesh, a new vertex i will correspond to previous vertex vertexIndices[i].
- L100 _public prototype_ `void SetMesh(int meshIndex, const Eigen::Matrix<T, 3, -1>& vertices);` — Update the @p meshIndex 'th mesh vertices
- L102 _public prototype_ `void Translate(const Eigen::Vector3<T>& translation);`
- L105 _public prototype_ `void Mirror(const std::map<std::string, std::vector<int>>& symmetries, const std::map<std::string, std::vector<std::pair<int, T>>>& meshRoots);` — Mirror the rig horizontally
- L108 _public prototype_ `void UpdateRestOrientationEuler(const Eigen::Matrix<T, 3, -1>& restOrientationEuler);` — Update the rest orientation and also update the joint deltas due to change of the rest orientation
- L111 _public prototype_ `void UpdateRestPose(const Eigen::Matrix<T, 3, -1>& restPose, CoordinateSystem coordinateSystem);` — Update the rest pose
- L114 _public prototype_ `void CreateSubdivision(const Mesh<T>& subdivisionTopology, const std::vector<std::tuple<int, int, T>>& stencilWeights, int meshIndex);` — Create a subdivision version of mesh @p meshIndex
- L117 _private member_ `std::shared_ptr<const RigLogic<T>> m_rigLogic;`
- L118 _private member_ `std::shared_ptr<const RigGeometry<T>> m_rigGeometry;`
- L121 _private member_ `Mesh<T> m_baseMesh;` — The base mesh (quads)
- L124 _private member_ `Mesh<T> m_baseMeshTriangulated;` — the base mesh (triangulated)

#### enum `Rig::ControlsType`  
`enum class ControlsType`  
_L59-63_
- L61 _public enumerator_ `GuiControls`
- L62 _public enumerator_ `RawControls`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/RigGeometry.h` (Private)


#### enum `CoordinateSystem`  
`enum class CoordinateSystem`  
_L28-32_
- desc: An enum to define whether coordinate system is Local or World
- L30 _public enumerator_ `Local`
- L31 _public enumerator_ `World`

#### class `RigGeometry`  
`template <class T> class RigGeometry`  
_L36-291_
- desc: RigGeometry implements the rig geometry evaluation based on rig logic inputs.
- L51 _public prototype_ `explicit RigGeometry(bool useMultithreading = true);`
- L52 _public prototype_ `~RigGeometry();`
- L53 _public prototype_ `RigGeometry(RigGeometry&&);`
- L54 _public prototype_ `RigGeometry(RigGeometry&) = delete;`
- L55 _public prototype_ `RigGeometry& operator=(RigGeometry&&);`
- L56 _public prototype_ `RigGeometry& operator=(const RigGeometry&) = delete;`
- L58 _public prototype_ `std::shared_ptr<RigGeometry> Clone() const;`
- L61 _public prototype_ `bool Init(const dna::Reader* reader, bool withJointScaling = false, std::map<std::string, ErrorInfo>* errorInfo = nullptr);` — Initializes RigGeometry with the data from the dna::Reader
- L64 _public prototype_ `State EvaluateRigGeometry(const DiffDataAffine<T, 3, 3>& diffRigid, const DiffData<T>& diffJoints, const DiffData<T>& diffPsd, const std::vector<int>& meshIndices) const;` — Sets the joints and evaluates the mesh vertices for LOD @p lod and mesh indices @p meshIndices.
- L68 _public prototype_ `State& EvaluateRigGeometry(const DiffDataAffine<T, 3, 3>& diffRigid, const DiffData<T>& diffJoints, const DiffData<T>& diffPsd, const std::vector<int>& meshIndices, State& state) const;` — Sets the joints and evaluates the mesh vertices for LOD @p lod and mesh indices @p meshIndices.
- L72 _public prototype_ `State& EvaluateWithPerMeshBlendshapes(const DiffDataAffine<T, 3, 3>& diffRigid, const DiffData<T>& diffJoints, const std::vector<DiffDataMatrix<T, 3, -1>>& diffBlendshapes, const std::vector<int>& meshIndices, const std::vector<Eigen::Ref<const Eigen::Matrix<T, 3, -1>>>& meshNeutrals, State& state) const;` — Sets the joints and evaluates the mesh vertices for LOD @p lod and mesh indices @p meshIndices.
- L80 _public prototype_ `State& EvaluateWithPerMeshBlendshapes(const DiffDataAffine<T, 3, 3>& diffRigid, const DiffData<T>& diffJoints, const std::vector<DiffDataMatrix<T, 3, -1>>& diffBlendshapes, const std::vector<int>& meshIndices, State& state) const;` — Sets the joints and evaluates the mesh vertices for LOD @p lod and mesh indices @p meshIndices.
- L87 _public prototype_ `State EvaluateWithPerMeshBlendshapes(const DiffDataAffine<T, 3, 3>& diffRigid, const DiffData<T>& diffJoints, const std::vector<DiffDataMatrix<T, 3, -1>>& diffBlendshapes, const std::vector<int>& meshIndices) const;` — Sets the joints and evaluates the mesh vertices for LOD @p lod and mesh indices @p meshIndices.
- L93 _public prototype_ `const Mesh<T>& GetMesh(int meshIndex) const;` — @return the @p meshIndex 'th mesh
- L96 _public prototype_ `const Mesh<T>& GetMesh(const std::string& meshName) const;` — @return the mesh @p meshName
- L99 _public prototype_ `const std::string& GetMeshName(int meshIndex) const;` — @return the name of the @p meshIndex 'th mesh
- L102 _public prototype_ `int GetMeshIndex(const std::string& meshName) const;` — @return the index of the mesh with name @p meshName
- L105 _public prototype_ `bool IsValid(int meshIndex) const;` — @return True if there is valid data for mesh @p meshIndex
- L108 _public prototype_ `int NumMeshes() const;` — @return the number of meshes
- L111 _public prototype_ `const std::vector<int>& GetMeshIndicesForLOD(int lod) const;` — @return all mesh indices that are part of @p lod
- L114 _public prototype_ `const std::vector<int>& GetBlendshapeMeshIndices() const;` — @return all mesh indices that contains blendshape targets
- L117 _public prototype_ `const std::vector<int>& JointIndicesForLOD(int lod) const;` — @return the joint indices that are used on LOD @p lod
- L120 _public prototype_ `const JointRig2<T>& GetJointRig() const;` — @return the underlying joint rig
- L123 _public prototype_ `Eigen::Matrix<T, 4, 4> GetBindMatrix(int jointIndex) const;` — @return the current bind matrix of the joint rig.
- L126 _public prototype_ `Eigen::Matrix<T, 4, 4> GetRestMatrix(int jointIndex) const;` — @return the current rest matrix of the joint rig.
- L129 _public prototype_ `const Eigen::Matrix<T, 3, -1>& GetRestOrientationEuler() const;` — @return the current rest orientation of all joints in euler angles.
- L132 _public prototype_ `const Eigen::Matrix<T, 3, -1>& GetRestPose() const;` — @return the current rest pose of all joints in euler angles.
- L138 _public prototype_ `void SetRestPose(Eigen::Matrix<T, 3, -1> restPose, CoordinateSystem coordSystem = CoordinateSystem::Local);` — @brief Set the rest pose. @param coordSystem: the coordinate system that the rest pose is provided in. This may be Local (the default) or World
- L145 _public prototype_ `void SetRestOrientationEuler(Eigen::Matrix<T, 3, -1> restOrientationEuler, CoordinateSystem coordSystem = CoordinateSystem::Local, bool bUpdateJointPositionsToPreviousValues = false);` — @brief Set the rest orientation (does not update joint deltas, see @p UpdateRestOrientationEuler ) @param coordSystem: the coordinate system that the rest orientation is provided in. This may be Local (the default) or World @param bUpdateJointPositionsToPreviousValues: if set to false, then the rest pose is not changed; if set to true then the rest pose is updated so that joint positions are the same as before
- L148 _public prototype_ `void UpdateRestOrientationEuler(const Eigen::Matrix<T, 3, -1>& restOrientationEuler, RigLogic<T>& rigLogic);` — Update the rest orientation and also update the joint deltas due to change of the rest orientation
- L153 _public prototype_ `void MakeBlendshapeOnly(const RigLogic<T>& rigLogic);` — @brief Makes a blendshape only rig. However, it keeps the eyes as joints.
- L156 _public prototype_ `void RemoveUnusedJoints(RigLogic<T>& rigLogic);` — Removes all unused joints from both RigGeometry and RigLogic.
- L159 _public prototype_ `void ReduceToLOD0Only();` — Remove all LODs besides the highest.
- L162 _public prototype_ `void ReduceToMeshes(const std::vector<int>& meshIndices);` — Only keep the mesh indices in the the rig. Keeps the removed meshes as empty meshes.
- L165 _public prototype_ `void RemoveBlendshapes(const std::vector<int>& meshIndices);` — Remove the blendshapes for meshes @p meshIndices
- L168 _public prototype_ `void SetMesh(int meshIndex, const Eigen::Matrix<T, 3, -1>& vertices);` — Update the @p meshIndex 'th mesh vertices
- L171 _public prototype_ `static Mesh<T> ReadMesh(const dna::Reader* reader, int meshIndex, bool triangulate = false);` — Assembles the mesh at index @p meshIndex stored within dna::Reader
- L174 _public prototype_ `void Resample(int meshIndex, const std::vector<int>& newToOldMap);` — Resample the rig geometry such that new vertex i will correspond to previous vertex newToOldMap[i].
- L177 _public prototype_ `std::string HeadMeshName(int lod) const;` — @return the name of the head mesh
- L180 _public prototype_ `std::string TeethMeshName(int lod) const;` — @return the name of the teeth mesh
- L183 _public prototype_ `std::string EyeLeftMeshName(int lod) const;` — @return the name of the left eye mesh
- L186 _public prototype_ `std::string EyeRightMeshName(int lod) const;` — @return the name of the right eye mesh
- L189 _public prototype_ `int HeadMeshIndex(int lod) const;` — @return the index of the head mesh
- L192 _public prototype_ `int TeethMeshIndex(int lod) const;` — @return the index of the teeth mesh
- L195 _public prototype_ `int EyeLeftMeshIndex(int lod) const;` — @return the index of the left eye mesh
- L198 _public prototype_ `int EyeRightMeshIndex(int lod) const;` — @return the index of the right eye mesh
- L202 _public prototype_ `int CorrespondingMeshIndexAtLod(int meshIndex, int lod) const;` — @return for mesh index @p meshIndex, returns the corresponding mesh index at LOD @p lod. -1 if the mesh does not exist.
- L206 _public prototype_ `SparseMatrix<T> VertexInfluenceWeights(const std::string& meshName) const;` — Returns vertex influence weights as a sparse matrix. Matrix is row major, rows correspond to vertices, and columns to joints
- L209 _public prototype_ `void Translate(const Eigen::Vector3<T>& translation);` — Update the rig by translating all elements
- L212 _public prototype_ `Eigen::Vector3<T> EyesMidpoint() const;` — @return the eye midpoint position
- L223 _public prototype_ `void Mirror(const std::map<std::string, std::vector<int>>& symmetries, const std::map<std::string, std::vector<std::pair<int, T>>>& meshRoots, RigLogic<T>& rigLogic);` — @brief Mirror the rig. @param symmetries  The symmetry mapping for meshes that are symmetric. Eyes are handled explicitly. @param meshRoots   The roots of meshes that are used to apply an as-rigid-as-possible deformation based on the head mesh. Used to mirror eyelashes as they are not symmetric, hence an acceptable deformation to the new symmetric head mesh is required. Roots are defined indices with a weight above 1. @param rigLogic    The riglogic component that also needs to be mirrored.
- L228 _public prototype_ `std::string GetSymmetricMeshName(const std::string& meshName) const;` — @returns the symmetric mesh for @p meshName. All meshes are self symmetric besides eyeLeft and eyeRight.
- L231 _public prototype_ `void CreateSubdivision(const Mesh<T>& subdivisionTopology, const std::vector<std::tuple<int, int, T>>& stencilWeights, int meshIndex);` — Cfreate a subdivision version of mesh @p meshIndex replacing the current version of the mesh.
- L234 _public prototype_ `void Transfer(int meshIndex, const RigGeometry<T>& otherRig, int otherMeshIndex);` — Copy the mesh of @p otherRig to mesh @p meshIndex of this rig using the blendshapes of this mesh.
- L237 _public prototype_ `void SaveBindPoseToDna(dna::Writer* writer) const;` — Save the rig bind pose to the dna binary stream
- L240 _public prototype_ `void SaveDna(dna::Writer* writer, int meshIndex) const;` — Save a specific mesh index to the binary stream
- L243 _public prototype_ `void SaveBlendshapeMappingToDna(dna::Writer* writer) const;` — Save the blendshape mapping to the dna binary stream
- L246 _public prototype_ `Eigen::Transform<T, 3, Eigen::Affine> GetRestPose(int jointIndex) const;` — Get joint rest pose
- L248 _public prototype_ `const Eigen::Matrix<T, -1, -1>& GetBlendshapeMatrix(int meshIndex) const;`
- L251 _public prototype_ `const Eigen::VectorXi GetBlendshapePsdControls(int meshIndex) const;` — get for each blendshape by which control it is being driven
- L254 _public prototype_ `std::uint16_t NumLODs() const;` — the number of LODs
- L256 _public prototype_ `void CalculateLocalJointTransformsFromWorldTransforms(const std::vector<Affine<T, 3, 3>>& jointWorldTransforms, Eigen::Matrix<T, 3, -1>& restPose, Eigen::Matrix<T, 3, -1>& restOrientationEulers) const;`
- L261 _private prototype_ `void EvaluateJointDeltas(const DiffDataAffine<T, 3, 3>& diffRigid, const DiffData<T>& diffJoints, State& state) const;` — Evaluates the joint deltas and stores it in @p state.
- L264 _private prototype_ `void EvaluateJointDeltasWithoutJacobians(const DiffDataAffine<T, 3, 3>& diffRigid, const DiffData<T>& diffJoints, State& state) const;` — Evaluates the joint deltas and stores it in @p state.
- L273 _private prototype_ `void EvaluateBlendshapes(const DiffData<T>& diffPsd, int meshIndex, State& state) const;` — Evaluates the mesh vertices of for LOD @p lod and mesh index @p meshIndex. @param diffPsd          The psd coefficients. Typically the output from RigLogic::EvaluatePsd() @param meshIndex        Which mesh to evaluate. @return the evaluated deformed mesh vertices. The output contains Jacobians if either the internal rig has the jacobians set, or if @diffBlendshapes contains the Jacobian.
- L277 _private prototype_ `void EvaluateSkinningWithoutJacobians(int meshIndex, State& state) const;` — evaluates the skinning for geometry @p geometryName with state as input (evaluated blendshape vertices) and output (final vertices).
- L279 _private prototype_ `void EvaluateSkinningWithJacobians(int meshIndex, State& state) const;`
- L281 _private prototype_ `void UpdateBindPoses();`
- L283 _private prototype_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> GetPreviousBindPose(const Eigen::Matrix<T, 3, -1>& restOrientationEuler) const;`
- L285 _private prototype_ `void UpdateRestPose(const std::vector<Eigen::Transform<T, 3, Eigen::Affine>>& prevBindPoses);`
- L290 _private member_ `std::unique_ptr<Private> m;` — TITAN_NAMESPACE::Pimpl<Private> m;

#### struct `RigGeometry::ErrorInfo`  
`struct ErrorInfo`  
_L43-48_
- L45 _public member_ `std::vector<std::pair<std::string, std::vector<int>>> duplicateBlendshapes;`
- L46 _public member_ `std::vector<std::pair<std::string, std::vector<int>>> zeroBlendshapes;`
- L47 _public member_ `typename JointRig2<T>::ErrorInfo skinningWeightsErrors;`

#### class `RigGeometry::State`  
`template <class T> class RigGeometry<T>::State`  
_L296-395_
- desc: Rig geometry state containing results of a specific evaluation
- L299 _public prototype_ `State();`
- L300 _public prototype_ `~State();`
- L301 _public prototype_ `State(State&&);`
- L302 _public prototype_ `State& operator=(State&&);`
- L303 _public prototype_ `State(const State&) = delete;`
- L304 _public prototype_ `State& operator=(const State&) = delete;`
- L314 _public prototype_ `const std::vector<DiffDataMatrix<T, 3, -1>>& Vertices() const;` — @return const std::vector<DiffDataMatrix<T, 3, -1>>&  the evaluated vertices. See RigGeometry<T>::EvaluateRigGeometry @warning The returned DiffDataMatrices are only valid as long as the State has not been updated by another call to RigGeometry<T>::EvaluateRigGeometry with the same state. Explanation: the dense matrix of the Jacobian is resized in RigGeometry<T>::EvaluateRigGeometry and therefore the DiffDataMatrix Jacobian will map to an invalidated dense matrix.
- L317 _public prototype_ `const Eigen::Matrix<T, 3, -1>& BlendshapeVertices(int meshId) const;` — @return blendshape deltas in bind pose space
- L320 _public prototype_ `const std::vector<int>& MeshIndices() const;` — @return the mesh indices that were passed to RigGeometry<T>::EvaluateRigGeometry for evalution
- L323 _public function_ `const std::vector<Eigen::Transform<T, 3, Eigen::Affine>>& GetWorldMatrices() const` — @return all world matrices
- L326 _public prototype_ `Eigen::Matrix<T, 4, 4> GetWorldMatrix(int jointIndex) const;` — @return the current world matrix of the joint rig.
- L329 _public prototype_ `Eigen::Matrix<T, 4, 4> GetLocalMatrix(int jointIndex) const;` — @return the current local matrix of the joint rig.
- L332 _public prototype_ `void SetLocalMatrix(int jointIndex, const Eigen::Matrix<T, 4, 4>& jointTransform);` — Set the current local matrix of the joint rig.
- L335 _public prototype_ `Eigen::Matrix<T, 4, 4> GetSkinningMatrix(int jointIndex) const;` — @return the current skinning matrix of the joint rig
- L338 _public prototype_ `std::vector<Eigen::Matrix<T, 4, 4>> GetAllSkinningMatrices() const;` — @return the current skinning matrices for all joints
- L341 _public prototype_ `std::vector<DiffDataMatrix<T, 3, -1>> MoveVertices();` — std::move the vertices from the state
- L345 _private prototype_ `void SetupForMesh(int meshIndex);` — setup the state to support adding data for mesh @p meshIndex
- L349 _private member_ `std::vector<DiffDataMatrix<T, 3, -1>> m_vertices;` — the evaluated vertices
- L352 _private member_ `std::vector<int> m_meshIndices;` — vector containing mapping mesh indices to the evaluated vertices
- L355 _private member_ `bool m_withJacobians = false;` — flag specifying whether the state has been set including Jacobians
- L358 _private member_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> m_localMatrices;` — the evaluated local transformations for each joint
- L361 _private member_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> m_worldMatrices;` — the evaluated world transformations for each joint
- L364 _private member_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> m_skinningMatrices;` — the evaluated skinning transformations for each joint
- L367 _private member_ `int m_jointJacobianColOffset = -1;` — local caching of the jacobians for the joints
- L368 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> m_jointDeltasJacobian;`
- L369 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> m_localMatricesJacobian;`
- L370 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> m_worldMatricesJacobian;`
- L371 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> m_skinningMatricesJacobian;`
- L392 _private member_ `std::vector<JacobianData> m_meshJacobianData;` — structure containing temporary data for jacobian calculations of the blendshapes

#### struct `RigGeometry::State::JacobianData`  
`struct JacobianData`  
_L373-389_
- L376 _public member_ `Eigen::Matrix<T, 3, -1> blendshapeVertices;` — blendshapes as they were evaluated
- L377 _public member_ `std::shared_ptr<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> blendshapeJacobianRM = std::make_shared<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>();`
- L381 _public member_ `int blendshapeJacobianColOffset = -1;`
- L384 _public member_ `Eigen::Matrix<T, 3, -1> finalVertices;` — final vertices after applying the joint evaluation
- L385 _public member_ `std::shared_ptr<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> finalJacobianRM = std::make_shared<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>();`
- L388 _public member_ `int finalJacobianColOffset = -1;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/RigLogic.h` (Private)


#### class `RigLogic`  
`template <class T> class RigLogic`  
_L37-270_
- desc: RigLogic implements rig logic including Jacobian. Opens: - TODO: animated map clamping needs to be fixed, once clamping in RigLogic has been fixed - TODO: the clamping scheme needs to be investigated: when using clamps the Jacobians would become 0, which would hurt any optimization. currently Jacobians are not supported when clamping is enabled
- L40 _public prototype_ `RigLogic();`
- L41 _public prototype_ `~RigLogic();`
- L42 _public prototype_ `RigLogic(RigLogic&&);`
- L43 _public prototype_ `RigLogic(RigLogic&) = delete;`
- L44 _public prototype_ `RigLogic& operator=(RigLogic&&);`
- L45 _public prototype_ `RigLogic& operator=(const RigLogic&) = delete;`
- L47 _public prototype_ `std::shared_ptr<RigLogic> Clone() const;`
- L50 _public prototype_ `bool Init(const dna::Reader* reader, bool withJointScaling = false);` — Initializes RigLogic with the data from the dna::Reader
- L53 _public prototype_ `int NumGUIControls() const;` — @return the number of gui controls of the rig
- L56 _public prototype_ `int NumRawControls() const;` — @return the number of raw controls of the rig
- L59 _public prototype_ `int NumPsdControls() const;` — @return the number of psd controls of the rig
- L62 _public prototype_ `int NumMLControls() const;` — @return the number of ML controls of the rig
- L65 _public prototype_ `int NumRBFControls() const;` — @return the number of RBF controls of the rig
- L68 _public prototype_ `int NumTotalControls() const;` — @return the number of total output controls of the rig i.e. sum of raw, psd, and ml controls, and the side of the data that is output of EvaluatePSD()
- L71 _public prototype_ `int NumNeuralNetworks() const;` — @return the number of neural networks
- L77 _public prototype_ `DiffData<T> EvaluateRawControls(const DiffData<T>& guiControls) const;` — Evaluate the raw controls given the input gui controls. Throws an expection is the size is incorrect. There is no clamping involved, any gui controls exceeding their range will extrapolate the values.
- L87 _public prototype_ `DiffData<T> EvaluatePSD(const DiffData<T>& rawControls, const Eigen::VectorX<T>& maskWeights = Eigen::VectorX<T>()) const;` — Evaluates the full controls from raw controls. Throws an expection is the size is incorrect. Full controls contains [raw_controls, psd_controls, ml_controls] You would typically call it with the output from EvaluateRawControls(). @param rawControls  The raw control values. @see EvaluateRawControls() @param maskWeights  Neural networks are weighted by a mask weight. An empty vector is equivalent to weight=1. @note we may want to rename EvaluatePSD() to EvaluateControls() to be clear that it does not only refer to PSD controls.
- L99 _public prototype_ `DiffData<T> EvaluateJoints(const DiffData<T>& psdControls, int lod) const;` — Evaluate the joint values from the psd values. Throws an expection if the size is incorrect. You would typically call it with the output from EvaluatePSD().
- L106 _public prototype_ `DiffData<T> EvaluateJoints(const DiffData<T>& psdControls, const DiffDataSparseMatrix<T>& jointMatrix) const;` — Evaluate the joint values from the psd values and additionaly a specified joint matrix. Throws an expection if the size is incorrect. You would typically call it with the output from EvaluatePSD().
- L112 _public prototype_ `DiffData<T> EvaluateAnimatedMaps(const DiffData<T>& psdControls, int lod) const;` — Evaluate the animated map coefficients from the psd values. Throws an expection is the size is incorrect. You would typically call it with the output from EvaluatePSD().
- L117 _public prototype_ `const std::vector<std::string>& GuiControlNames() const;` — @return the names of the GUI controls.
- L122 _public prototype_ `const std::vector<std::string>& RawControlNames() const;` — @return the names of the raw controls.
- L127 _public prototype_ `const DriverJointControls& GetDriverJointControls() const;` — @return DriverJointControls used for evaluating directly
- L132 _public prototype_ `const std::vector<std::string>& MLControlNames() const;` — @return the names of the ML controls.
- L137 _public prototype_ `const std::vector<std::string>& RBFPoseNames() const;` — @return the names of the RBF poses.
- L142 _public prototype_ `const std::vector<std::string>& RBFPoseControlNames() const;` — @return the names of the RBF pose controls.
- L145 _public prototype_ `const std::vector<std::string>& MLNetworkNames() const;` — @return the name of neural networks
- L148 _public prototype_ `const std::vector<std::string>& GetAllControlNames() const;` — @return the name of neural networks
- L153 _public prototype_ `const Eigen::Matrix<T, 2, -1>& GuiControlRanges() const;` — @return the range of the GUI controls
- L158 _public prototype_ `int NumLODs() const;` — @return the number of LODs in the rig.
- L163 _public prototype_ `int NumJoints() const;` — @return the number of joints in the rig.
- L169 _public prototype_ `const SparseMatrix<T>& PsdToRawMap() const;` — @return the matrix mapping psd controls to raw controls i.e psd = PsdToRawMap() * rawControls. (output size NumTotalControls()) @note the first NumRawControls() rows map raw controls to itself.
- L175 _public prototype_ `const SparseMatrix<T>& JointMatrix(int lod) const;` — @return the matrix mapping psd controls to joint deltas i.e. jointDeltas = jointMatrix * psdControls Matrix size is therefore (dofPerJoint * numJoints, totalControlCount) == (jointRowCount, jointColumnCount)
- L178 _public prototype_ `void SetJointMatrix(int lod, const SparseMatrix<T>& mat);` — Set the joint matrix @p mat for lod @p load.
- L181 _public prototype_ `void ReduceToLOD0Only();` — Remove all LODs besides the highest.
- L184 _public prototype_ `bool WithJointScaling() const;` — @return whether joint scaling is output by RigLogic
- L192 _public prototype_ `std::vector<std::tuple<int, int, Eigen::VectorX<T>>> GetAllExpressions() const;` — The PSD values for all expressions (raw controls, and each corretive expression) of the rig sorted by the number of raw controls that affect the expression. @return vector with tuples containing the number of raw controls affecting the expression, the index into the PSD output (EvaluatePSD()) for the expression, and the psd control activations.
- L197 _public prototype_ `void RemoveJoints(const std::vector<int>& newToOldJointMapping);` — @brief Remove joints from RigLogic. This is being together with simplification in RigGeometry.
- L200 _public prototype_ `void ReduceToGuiControls(const std::vector<int>& guiControls);` — @brief Reduce internal PSD logic to only support @p guiControls. All other gui controls will be ignored even if the are non-zero.
- L208 _public prototype_ `Eigen::VectorX<T> GuiControlsFromRawControls(const Eigen::VectorX<T>& rawControls, std::vector<int>& inconsistentGuiControls) const;` — @brief Calculates the inverse of EvaluateRawControls i.e. gets the gui controls based on the raw controls. @param[out] inconsistentGuiControls  It is possible that the raw controls lead to inconsistent gui controls. the gui controls that are not well defined are set here. @returns the GUI controls that map to raw controls.
- L211 _public prototype_ `std::vector<int> UnusedGuiControls() const;` — @returns all gui controls that do not affect any raw control.
- L214 _public prototype_ `std::vector<int> UnusedRawControls() const;` — @returns all raw controls that are not affected by gui controls.
- L217 _public prototype_ `std::vector<int> UnmappedJoints() const;` — @returns which joints are unmapped by riglogic
- L220 _public prototype_ `int GuiControlIndex(const char* name) const;` — @returns the index for gui control @p name
- L223 _public prototype_ `int RawControlIndex(const char* name) const;` — @returns the index for raw control @p name
- L226 _public prototype_ `void MirrorJoints(const std::vector<int>& symmetricJointIndices);` — Mirror the riglogic joint activations.
- L235 _public prototype_ `std::vector<std::pair<int, T>> GetSymmetricGuiControlIndices() const;` — Get the symmetric gui control indices. Entries point to the symmetric index. The multiplier needs to be applied to the symmetric controls. This is used for controls such as CTRL_jaw.tx as it has a [-1, 1] mapping as well as the symmetric CTRL_L_eye.tx and CTRL_R_eye.tx.
- L238 _public prototype_ `std::vector<std::vector<int>> GetUsedRawControls() const;` — Get the used raw controls for a gui control
- L241 _public prototype_ `std::vector<int> GetSymmetricRawControlIndices() const;` — Get the symmetric raw control indices
- L244 _public prototype_ `std::vector<int> GetSymmetricPsdIndices() const;` — Get the symmetric psd indices
- L247 _public prototype_ `const std::vector<int>& GetJointGroupIndices() const;` — Get the joint group indices per joint
- L250 _public prototype_ `const std::vector<Eigen::VectorX<std::uint16_t>>& GetJointGroupJointIndices() const;` — Get the joint group joint indices
- L253 _public prototype_ `const std::vector<Eigen::VectorX<std::uint16_t>>& GetJointGroupInputIndices() const;` — Get the joint group input indices
- L256 _public prototype_ `const std::vector<Eigen::VectorX<std::uint16_t>>& GetJointGroupOutputIndices() const;` — Get the joint group output indices
- L259 _public prototype_ `const std::vector<Eigen::VectorX<std::uint16_t>>& GetJointGroupLODs() const;` — Get the joint group LODs
- L262 _public prototype_ `void SaveJointDeltas(dna::Writer* writer) const;` — Save joint deltas to the dna binary stream
- L265 _private prototype_ `void SortGuiControlMapping();`
- L269 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/RigLogicDNAResource.h` (Private)


#### class `RigLogicDNAResource`  
`class RigLogicDNAResource`  
_L22-46_
- desc: Wrapper to load RigLogic DNA resources.
- L25 _public prototype_ `RigLogicDNAResource();`
- L26 _public prototype_ `~RigLogicDNAResource();`
- L27 _public prototype_ `RigLogicDNAResource(RigLogicDNAResource&&);`
- L28 _public prototype_ `RigLogicDNAResource(const RigLogicDNAResource&) = delete;`
- L29 _public prototype_ `RigLogicDNAResource& operator=(RigLogicDNAResource&&);`
- L30 _public prototype_ `RigLogicDNAResource& operator=(const RigLogicDNAResource&) = delete;`
- L36 _public prototype_ `static std::shared_ptr<const RigLogicDNAResource> LoadDNA(const std::string& dnaFile, bool retain);` — Read the DNA file from \p dnaFile. @param [in] retain  Cache the resource in memory for subsequent accesses. Only necessary if the same DNA file is being loaded multiple times.
- L41 _public prototype_ `dna::Reader* Stream() const;` — Returns the pointer to the underlying RL4 BinaryStreamReader. Only valid as long as the instance is alive.
- L45 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/RigLogicSolveControls.h` (Private)


#### class `RigLogicSolveControls`  
`template <class T> class RigLogicSolveControls`  
_L17-69_
- desc: Higher level solve controls that map to GUI controls of RigLogic.
- L20 _public prototype_ `RigLogicSolveControls();`
- L21 _public prototype_ `~RigLogicSolveControls();`
- L22 _public prototype_ `RigLogicSolveControls(RigLogicSolveControls&&);`
- L23 _public prototype_ `RigLogicSolveControls(RigLogicSolveControls&) = delete;`
- L24 _public prototype_ `RigLogicSolveControls& operator=(RigLogicSolveControls&&);`
- L25 _public prototype_ `RigLogicSolveControls& operator=(const RigLogicSolveControls&) = delete;`
- L28 _public prototype_ `bool Init(const RigLogic<T>& rigLogicReference, const JsonElement& rigLogicSolveControlJson);` — Initializes RigLogicSolveControls with the rig logic reference and a json description of the solve controls
- L31 _public prototype_ `const std::string& Name() const;` — @returns the name of the riglogic solve control set
- L34 _public prototype_ `int NumSolveControls() const;` — @returns the number of solve controls of the rig
- L39 _public prototype_ `DiffData<T> EvaluateGuiControls(const DiffData<T>& solveControls) const;` — Evaluate the GUI controls given the solve controls.
- L44 _public prototype_ `const std::vector<std::string>& SolveControlNames() const;` — @returns the names of the Solve controls.
- L49 _public prototype_ `const Eigen::Matrix<T, 2, -1>& SolveControlRanges() const;` — @returns the range of the Solve controls
- L52 _public prototype_ `const Eigen::VectorX<T>& SolveControlRegularizationScaling() const;` — @returns the regularization scaling of the solve controls
- L58 _public prototype_ `Eigen::VectorX<T> SolveControlsFromGuiControls(const Eigen::VectorX<T>& guiControls, std::vector<int>& inconsistentSolveControls) const;` — Calculate solve controls from Gui Controls. @param[out] inconsistentSolveControls  Marks all solve controls that are not consistent in the mapping.
- L61 _public prototype_ `const std::vector<int>& UsedGuiControls() const;` — @returns all gui controls that are triggered by the solve controls
- L64 _public prototype_ `std::vector<std::vector<int>> UsedGuiControlsPerSolveControl() const;` — @returns per solve control which gui control is affected
- L68 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/RigUtils.h` (Private)


#### Free symbols / members of external scopes

- L12 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::rigutils) template <class T> std::map<std::string, int> JointNameToIndexMap(const RigGeometry<T>& rigGeometry);`
- L17 _prototype_ `std::map<std::string, int> JointNameToIndexMap(const dna::Reader* reader);`
- L21 _prototype_ `template <class T> std::vector<Affine<T, 3, 3>> JointWorldTransforms(const RigGeometry<T>& rigGeometry);` — returns per joint rotation and translation as affine transform.
- L26 _prototype_ `template <class T> std::pair<Eigen::Matrix<T, 3, -1>, Eigen::Matrix<T, 3, -1>> CalculateLocalJointRotationAndTranslation(const RigGeometry<T>& rigGeometry, const std::vector<Affine<T, 3, 3>>& worldTransforms);` — returns per joint rotation and translation as separate data streams. Rotation is stored as Euler angles, and both rotation and translation are in local space.
- L30 _prototype_ `template <class T> std::vector<Affine<T, 3, 3>> WorldToLocalJointDeltas(const RigGeometry<T>& rigGeometry, const std::vector<Affine<T, 3, 3>>& worldJointDeltas);`
- L33 _prototype_ `void AddRBFLayerToDnaStream(dna::Reader* reader, dna::Reader* rbfReader, dna::Writer* writer);`
- L35 _prototype_ `std::vector<int> GetJointsWithVariableSkinning(const dna::Reader* reader, const std::string& regionName);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/SkinningWeightUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::skinningweightutils) template <class T> void SnapNeckSeamSkinningWeightsToBodySkinningWeights(const SparseMatrix<T>& skinningWeightsCombinedBody, const std::vector<std::pair<int, bool>>& faceBodyJointMapping, const SnapConfig<T>& snapConfig, Eigen::Matrix<T, -1, -1>& updatedHeadSkinningWeightsDense);`
- L38 _prototype_ `template <class T> std::map<int, std::vector<int>> GetJointChildrenRecursive(const JointRig2<T>& jointRig, const std::string& mustContainStr = {});` — For each joint in a joint rig, return a vector of all descendant joint indices. Optionally mass in a string (mustContainStr) which the joint name must contain to be considered for recursion (for example if you just want to consider FACIAL joints). @param[in] jointRig: the rig which we are analyzing @param[in] mustContainStr: an optional string which allows us to only consider joints which contain the supplied string (for example if we just want to consider FACIAL joints) @returns a map of joint index to a vector containing the joint indices of all the descendants of that joint
- L48 _prototype_ `template <class T> std::vector<std::pair<int, bool>> CalculateBodyFaceJointMapping(const JointRig2<T>& faceJointRig, const JointRig2<T>& bodyJointRig);` — Calculate the mapping for each body rig joint to corresponding face rig joint. If there is a match, result will contain the matching joint index and true; if not, it will be - 1 and false @param[in]: faceJointRig the face joint rig @param[in]: bodyJointRig the body joint rig @returns a vector containing for each body joint index, a pair which contains either the matching face joint index and true, or -1 and false if no match
- L58 _prototype_ `template <class T> std::vector<std::pair<int, bool>> CalculateFaceBodyJointMapping(const JointRig2<T>& faceJointRig, const JointRig2<T>& bodyJointRig);` — Calculate the mapping for each face rig joint to corresponding body rig joint. If there is a match, result will contain the matching joint index and true; if not, it will contain the facial parent joint which matches the body and false @param[in]: faceJointRig the face joint rig @param[in]: bodyJointRig the body joint rig @returns a vector containing for each face joint index, a pair which contains either the matching body joint index and true, or the corresponding body rig parent joint and false
- L73 _prototype_ `template <class T> void CalculateSkinningWeightsForBarycentricCoordinates(const std::vector<BarycentricCoordinates<T>>& barycentricCoordinates, const Eigen::Matrix<T, 3, -1>& vertices, const SparseMatrix<T>& skinningWeights, SparseMatrix<T>& outputSkinningWeights);` — Take a vector of barycentric coordinates, a corresponding matrix of vertex positions, and skinning weights for those vertices. Evaluate the barycentric coordinates and return a matrix of skinning weights for each joint, for each element of the vector of barycentric coordinates. No pruning or re-normalization is performed by this function currently, so output skinning weights will not necessarily be normalize to sum to 1 per vertex, or have the right number of influences per vertex. @param[in] barycentricCoordinates: the barycentric coordinates for each vertex for which we want to create skinning weights; for each vertex, this is the closest point on the mesh of vertices contained in vertices (typically a lower lod) @param[in] vertices: a 3 x n vertices matrix containing the coordinates of the vertices at the lower lod; this would typically be lod 0 @param[in] skinningWeights: a n vertices x n joints sparse matrix containing the skinning weights at the lower lod (typically lod 0) @param[out] outputSkinningWeights: on output will contain a matrix of barycentricCoordinates.size() x skinningWeights.cols() skinning weights which are generated by calculating a weighted sum of the source skinningWeights for each set of barycentric coordinates. The output weights are not normalized or pruned. @pre skinningWeights must contain the same number of rows as the number of columns in vertices @pre barycentric coordinates indices must be consistent with the vertices ie all indices in the ran
- L96 _prototype_ `template <class T, class R> void PropagateSkinningWeightsToHigherLOD(const std::vector<BarycentricCoordinates<T>>& higherLodBarycentricCoordinates, const Eigen::Matrix<T, 3, -1>& lowerLodVertices, const SparseMatrix<T>& lowerLodSkinningWeights, const std::map<std::string, std::map<std::string, T>>& jointMappingFromLod0, const SnapConfig<T>& lowerLodSnapConfig, const R& jointRig, int maxNumWeightsForLod, SparseMatrix<T>& outputHighLodSkinningWeights);` — Take an input sparse matrix of skinning weights which have been generated, and a 'template' matrix of skinning weights for the archetype at a (higher) required lod level, plus a corresponding joint rig, and modify the input skinning weights so that any joint influences not present in the archetype are . Finally, sort, prune and re-normalize the weights for each vertex to the required maximum number per vertex for the lod. This function assumes that the joints in different lods follow a simple parent child relationship ie at each level joint influences can simply be summed up and pushed up to their parents (as required). The function is templated on the scalar type T and also on the rig type R. This is so that it can work with both a JointRig2 and and a BodyGeometry type (which supports the required functionality) @param[in] higherLodBarycentricCoordinates: the barycentric coordinates for each vertex in the higher lod which we want to create skinning weights; for each higher lod vertex, this is the closest point on the lower lod mesh @param[in] lowerLodVertices: a 3 x n vertices matrix containing the coordinates of the vertices at the lower lod; this would typically be lod 0 @param[in] lowerLodSkinningWeights: a n vertices x n joints sparse matrix containing the skinning weights at the lower lod (typically lod 0) @params[in] jointMappingFromLod0: a map which for each joint in the rig used in lod0 defines how joint influences should be redistributed to joints in the higher lod 
- L106 _prototype_ `template <class T> void SortPruneAndRenormalizeSkinningWeights(SparseMatrix<T>& skin, int maxSkinWeights);` — sort, prune and renormalize the weights in the skinning weight matrix, limiting the influence for each vertex to maxSkinWeights joints. skin is n vertices rows x n joints columns matrix @param[out] skin: the input skinning weight matrix (n vertices rows x n joints columns) which on output will be pruned and normalized such that the joint weights for each vertex sum to 1 and no more than maxSkinWeights are > 0 @param[in] maxSkinWeights: the maximum number of joint weights for each vertex which may have a non-zero value

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/SymmetricControls.h` (Private)


#### class `SymmetricControls`  
`template <class T> class SymmetricControls`  
_L15-50_
- desc: Creates a symmetric control layer on top of the exisitng riglogic gui controls
- L18 _public prototype_ `SymmetricControls(const BodyLogic<T>& bodyLogicReference);`
- L19 _public prototype_ `~SymmetricControls();`
- L20 _public prototype_ `SymmetricControls(SymmetricControls&&);`
- L21 _public prototype_ `SymmetricControls(SymmetricControls&) = delete;`
- L22 _public prototype_ `SymmetricControls& operator=(SymmetricControls&&);`
- L23 _public prototype_ `SymmetricControls& operator=(const SymmetricControls&) = delete;`
- L26 _public prototype_ `int NumSolveControls() const;` — @returns the number of solve controls of the rig
- L31 _public prototype_ `DiffData<T> EvaluateSymmetricControls(const DiffData<T>& solveControls) const;` — Evaluate the GUI controls given the solve controls.
- L33 _public prototype_ `const Vector<T> GuiToSymmetricControls(const Vector<T>& guiControls) const;`
- L34 _public prototype_ `const Vector<T> SymmetricToGuiControls(const Vector<T>& symmetricControls) const;`
- L36 _public prototype_ `const std::vector<int> GetSymmetryMapping() const;`
- L37 _public prototype_ `const std::vector<std::string>& GetControlNames() const;`
- L39 _public prototype_ `std::vector<int> GuiIndicesToSymmetricIndices(const std::vector<int>& guiIndices) const;`
- L41 _public prototype_ `std::vector<int> GetSymmetricGuiIndices() const;`
- L43 _public prototype_ `std::vector<int> GetNonSymmetricGuiIndices() const;`
- L45 _public prototype_ `const Eigen::SparseMatrix<T, Eigen::RowMajor>& SymmetricToGuiControlsMatrix() const;`
- L49 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/TwistSwingLogic.h` (Private)


#### class `TwistSwingLogic`  
`template <class T> class TwistSwingLogic`  
_L20-44_
- L24 _public prototype_ `TwistSwingLogic();`
- L25 _public prototype_ `~TwistSwingLogic();`
- L27 _public prototype_ `TwistSwingLogic(TwistSwingLogic&&);`
- L28 _public prototype_ `TwistSwingLogic& operator=(TwistSwingLogic&&);`
- L30 _public prototype_ `TwistSwingLogic(const TwistSwingLogic&);`
- L31 _public prototype_ `TwistSwingLogic& operator=(const TwistSwingLogic&);`
- L33 _public prototype_ `DiffData<T> EvaluateJointsFromJoints(const DiffData<T>& jointDiff) const;`
- L34 _public prototype_ `DiffData<T> EvaluateJointsFromRawControls(const DiffData<T>& rawControls) const;`
- L36 _public prototype_ `void RemoveJoints(const std::vector<int>& newToOldJointMapping);`
- L38 _public prototype_ `bool Init(const dna::Reader* reader, bool withJointScaling = false);`
- L39 _public prototype_ `void Write(dna::Writer* writer);`
- L43 _private member_ `Pimpl<Private> m;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/rbfs/AdditiveRBFSolver.h` (Private)


#### class `AdditiveRBFSolver`  
`class AdditiveRBFSolver : public RBFSolverBase`  
_L10-19_
- inherits: `RBFSolverBase`
- L12 _public prototype_ `explicit AdditiveRBFSolver(pma::MemoryResource* memRes);`
- L13 _public prototype_ `AdditiveRBFSolver(const RBFSolverRecipe& recipe, pma::MemoryResource* memRes);`
- L14 _public prototype_ `explicit AdditiveRBFSolver(const RBFSolverBase* other);`
- L17 _public prototype_ `RBFSolverType getSolverType() const override;`
- L18 _public prototype_ `void solve(dna::ArrayView<float> input, dna::ArrayView<float> intermediateWeights, dna::ArrayView<float> outputWeights) const override;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/rbfs/InterpolativeRBFSolver.h` (Private)


#### class `InterpolativeRBFSolver`  
`class InterpolativeRBFSolver : public RBFSolverBase`  
_L10-24_
- inherits: `RBFSolverBase`
- L12 _public prototype_ `InterpolativeRBFSolver(const RBFSolverRecipe& recipe, pma::MemoryResource* memRes);`
- L13 _public prototype_ `explicit InterpolativeRBFSolver(InterpolativeRBFSolver* other);`
- L14 _public prototype_ `explicit InterpolativeRBFSolver(pma::MemoryResource* memRes);`
- L17 _public prototype_ `RBFSolverType getSolverType() const override;`
- L18 _public prototype_ `void solve(dna::ArrayView<float> input, dna::ArrayView<float> intermediateWeights, dna::ArrayView<float> outputWeights) const override;`
- L20 _public prototype_ `const Matrix<float>& getCoefficients() const;`
- L23 _private member_ `Matrix<float> coefficients;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/rbfs/RBFSolver.h` (Private)


#### enum `RBFSolverType`  
`enum class RBFSolverType`  
_L20-34_
- L25 _public enumerator_ `Additive` — The additive solver sums up contributions from each target. It's faster but may require more targets for a good coverage, and requires the normalization step to be performed for smooth results.
- L33 _public enumerator_ `Interpolative` — The interpolative solver interpolates the values from each target based on distance. As long as the input values are within the area bounded by the targets, the interpolation is well-behaved and returns weight values within the 0% - 100% limit with no normalization required. Interpolation also gives smoother results, with fewer targets than additive solver, but at a higher computational cost.

#### enum `RBFFunctionType`  
`enum class RBFFunctionType`  
_L36-42_
- L37 _public enumerator_ `Gaussian`
- L38 _public enumerator_ `Exponential`
- L39 _public enumerator_ `Linear`
- L40 _public enumerator_ `Cubic`
- L41 _public enumerator_ `Quintic`

#### enum `RBFDistanceMethod`  
`enum class RBFDistanceMethod`  
_L44-53_
- L46 _public enumerator_ `Euclidean` — Standard n-dimensional distance measure
- L48 _public enumerator_ `Quaternion` — Treat inputs as quaternion
- L50 _public enumerator_ `SwingAngle` — Treat inputs as quaternion, and find distance between rotated TwistAxis direction
- L52 _public enumerator_ `TwistAngle` — Treat inputs as half quaternion, and find distance between rotations around the TwistAxis direction

#### enum `RBFNormalizeMethod`  
`enum class RBFNormalizeMethod`  
_L55-58_
- L56 _public enumerator_ `OnlyNormalizeAboveOne`
- L57 _public enumerator_ `AlwaysNormalize`

#### enum `AutomaticRadius`  
`enum class AutomaticRadius`  
_L60-63_
- L61 _public enumerator_ `On`
- L62 _public enumerator_ `Off`

#### enum `TwistAxis`  
`enum class TwistAxis`  
_L65-69_
- L66 _public enumerator_ `X`
- L67 _public enumerator_ `Y`
- L68 _public enumerator_ `Z`

#### struct `RBFSolverRecipe`  
`struct RBFSolverRecipe`  
_L71-83_
- L72 _public member_ `RBFSolverType solverType;`
- L73 _public member_ `RBFDistanceMethod distanceMethod;`
- L74 _public member_ `RBFFunctionType weightFunction;`
- L75 _public member_ `RBFNormalizeMethod normalizeMethod;`
- L76 _public member_ `TwistAxis twistAxis;`
- L77 _public member_ `bool isAutomaticRadius;`
- L78 _public member_ `float radius;`
- L79 _public member_ `float weightThreshold;`
- L80 _public member_ `std::uint16_t rawControlCount;`
- L81 _public member_ `dna::ConstArrayView<float> targetValues;`
- L82 _public member_ `dna::ConstArrayView<float> targetScales;`

#### class `RBFSolver`  
`class RBFSolver`  
_L85-110_
- L87 _public prototype_ `static RBFSolver* create(RBFSolverRecipe recipe, pma::MemoryResource* memRes = nullptr);`
- L88 _public prototype_ `static RBFSolver* create(pma::MemoryResource* memRes = nullptr);`
- L89 _public prototype_ `static RBFSolver* create(RBFSolver* other);`
- L91 _public prototype_ `static void destroy(RBFSolver* instance);`
- L94 _public prototype_ `virtual ~RBFSolver();`
- L96 _public prototype_ `virtual RBFSolverType getSolverType() const = 0;`
- L97 _public prototype_ `virtual void solve(dna::ArrayView<float> input, dna::ArrayView<float> intermediateWeights, dna::ArrayView<float> outputWeights) const = 0;`
- L100 _public prototype_ `virtual dna::ConstArrayView<float> getTarget(std::uint16_t targetIndex) const = 0;`
- L101 _public prototype_ `virtual std::uint16_t getTargetCount() const = 0;`
- L103 _public prototype_ `virtual dna::ConstArrayView<float> getTargetScales() const = 0;`
- L104 _public prototype_ `virtual float getRadius() const = 0;`
- L105 _public prototype_ `virtual float getWeightThreshold() const = 0;`
- L106 _public prototype_ `virtual RBFDistanceMethod getDistanceMethod() const = 0;`
- L107 _public prototype_ `virtual RBFFunctionType getWeightFunction() const = 0;`
- L108 _public prototype_ `virtual RBFNormalizeMethod getNormalizeMethod() const = 0;`
- L109 _public prototype_ `virtual TwistAxis getTwistAxis() const = 0;`

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<TITAN_NAMESPACE::rbfs::RBFSolver>`  
_L117-119_
- L118 _public typedef_ `using type = FactoryCreate<TITAN_NAMESPACE::rbfs::RBFSolver>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<TITAN_NAMESPACE::rbfs::RBFSolver>`  
_L122-124_
- L123 _public typedef_ `using type = FactoryDestroy<TITAN_NAMESPACE::rbfs::RBFSolver>;`

#### Free symbols / members of external scopes

- L114 _namespace_ `namespace pma`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/rbfs/RBFSolverBase.h` (Private)


#### class `RBFSolverBase`  
`class RBFSolverBase : public RBFSolver`  
_L37-81_
- inherits: `RBFSolver`
- L40 _public typedef_ `using DistanceWeightFun = std::function<void (dna::ConstArrayView<AlignedVector<float> >, dna::ConstArrayView<float>, dna::ArrayView<float>, float)>;`
- L43 _public typedef_ `using InputConvertFun = std::function<void (dna::ArrayView<float>)>;`
- L45 _public prototype_ `explicit RBFSolverBase(dna::MemoryResource* memRes);`
- L46 _public prototype_ `RBFSolverBase(const RBFSolverRecipe& recipe, dna::MemoryResource* memRes);`
- L48 _public prototype_ `virtual ~RBFSolverBase() = 0;`
- L50 _public prototype_ `RBFSolverBase& operator=(const RBFSolverBase&) = default;`
- L51 _public prototype_ `RBFSolverBase(const RBFSolverBase&) = default;`
- L54 _public prototype_ `dna::MemoryResource* getMemoryResource() const;`
- L56 _public prototype_ `dna::ConstArrayView<float> getTarget(std::uint16_t targetIndex) const override;`
- L57 _public prototype_ `std::uint16_t getTargetCount() const override;`
- L59 _public prototype_ `dna::ConstArrayView<float> getTargetScales() const override;`
- L60 _public prototype_ `float getRadius() const override;`
- L61 _public prototype_ `float getWeightThreshold() const override;`
- L62 _public prototype_ `RBFDistanceMethod getDistanceMethod() const override;`
- L63 _public prototype_ `RBFFunctionType getWeightFunction() const override;`
- L64 _public prototype_ `RBFNormalizeMethod getNormalizeMethod() const override;`
- L65 _public prototype_ `TwistAxis getTwistAxis() const override;`
- L68 _protected prototype_ `void normalizeAndCutOff(dna::ArrayView<float> outputWeights) const;`
- L71 _protected member_ `dna::Vector<AlignedVector<float> > targets;`
- L72 _protected member_ `dna::Vector<float> targetScale;`
- L73 _protected member_ `DistanceWeightFun getDistanceWeight;`
- L74 _protected member_ `InputConvertFun convertInput;`
- L75 _protected member_ `float radius;`
- L76 _protected member_ `float weightThreshold;`
- L77 _protected member_ `RBFDistanceMethod distanceMethod;`
- L78 _protected member_ `RBFFunctionType weightFunction;`
- L79 _protected member_ `RBFNormalizeMethod normalizeMethod;`
- L80 _protected member_ `TwistAxis twistAxis;`

#### Free symbols / members of external scopes

- L23 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::rbfs) static constexpr std::size_t cacheLineAlignment = 64ul;`
- L28 _typedef_ `template<typename T> using AlignedAllocator = pma::PolyAllocator<T, cacheLineAlignment, pma::AlignedMemoryResource>;`
- L31 _typedef_ `template<typename T> using AlignedVector = pma::Vector<T, AlignedAllocator<T>>;`
- L34 _typedef_ `template<typename T, typename Allocator = pma::PolyAllocator<pma::Vector<T> > > using Matrix = pma::Vector<pma::Vector<T>, Allocator>;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/rbfs/TDMQuaternionJacobian.h` (Private)


#### struct `SlerpJacobian`  
`template <class T> struct SlerpJacobian`  
_L151-156_
- L152 _public member_ `Eigen::Matrix<T,4,4> dqdq1;` — derivative of q wrt q1
- L153 _public member_ `Eigen::Matrix<T,4,4> dqdq2;` — derivative of q wrt q2
- L154 _public member_ `Eigen::Matrix<T,4,1> dqdt;` — derivative of q wrt t
- L155 _public member_ `tdm::quat<T> q;` — slerp result (x,y,z,w)

#### Free symbols / members of external scopes

- L18 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> Eigen::Matrix<T, 3, 4> QuaternionToEulerXYZJacobian(const tdm::quat<T>& q)`
- L96 _function_ `template <typename T> Eigen::Matrix<T, 4, 4> QuaternionNormalizationJacobian(const tdm::quat<T>& quat)`
- L106 _function_ `template <class T> Eigen::Matrix<T, 4, 3> EulerXYZToQuaternionJacobian(const tdm::rad3<T>& rot)`
- L159 _function_ `template <class T> inline SlerpJacobian<T> SlerpJacobianAll(const tdm::quat<T>& q1, const tdm::quat<T>& q2, T t)`
- L174 _function_ `auto asEigen = [](const tdm::quat<T> q)` (scope `SlerpJacobianAll`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/serialization/DirectoryMeshReader.h` (Private)


#### Free symbols / members of external scopes

- L11 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`
- L19 _prototype_ `template <class T> Mesh<T> ReadMeshFromObjOrDNA(const std::string& filename, int meshId);` — meshId used only when loading DNA files (0 - head, 1 - teeth, 3 - left eye, 4 - right eye)
- L21 _prototype_ `std::vector<std::string> GetObjsOrDNAsFromDirectory(const std::string& dir, bool objOnly = false);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rig/include/rig/serialization/JointRigSerialization.h` (Private)


#### Free symbols / members of external scopes

- L12 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) /** * Deserializes the joint rig from json format. * * TODO: open questions: how to handle the case when the root node itself has a parent with * a global transformation. For now we ignore the case and throw an exception if the local and bind pose of the root node do not match. * * Format for joints: * joints`
- L43 _typedef_ `using T = typename JointHelper<AffineType>::SCALAR;` (scope `CARBON_NAMESPACE_BEGIN`)
- L44 _typedef_ `using Joint = TITAN_NAMESPACE::Joint<AffineType>;` (scope `CARBON_NAMESPACE_BEGIN`)
- L45 _typedef_ `using JointPtr = std::shared_ptr<Joint>;` (scope `CARBON_NAMESPACE_BEGIN`)
- L139 _function_ `template <class AffineType> void JointRigStateFromJson(const JsonElement& j, JointRig<AffineType>& jointRig)` — Deserializes the joint state from json format i.e. it only reads the local transformation matrix per joint Format for joint states (note that any other entries in the dictionaries are ignored) joints { “name of joint” : { “local”: 4x4 matrix (column major, pre multiply - should be possible to calculate it from the parent) }, ... (next joint) }
- L143 _typedef_ `using T = typename JointHelper<AffineType>::SCALAR;` (scope `JointRigStateFromJson`)
- L159 _function_ `template <class AffineType> JsonElement JointRigStateToJson(const JointRig<AffineType>& jointRig)` — Serializes the joint state to json format i.e. it only writes the local transformation matrix per joint. @see JointRigStateFromJson
- L161 _typedef_ `using T = typename JointHelper<AffineType>::SCALAR;` (scope `JointRigStateToJson`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rigcalibration_core/include/rigcalibration/ModelData.h` (Private)


#### struct `SkinningRegionData`  
`struct SkinningRegionData`  
_L17-25_
- L19 _public member_ `Eigen::VectorXf weights;`
- L20 _public member_ `Eigen::VectorXi combinedVertexMapping;`
- L21 _public member_ `Eigen::VectorXi jointsMapping;`
- L22 _public member_ `Eigen::MatrixXf mean;`
- L23 _public member_ `Eigen::SparseMatrix<float> modes;`
- L24 _public member_ `std::string name;`

#### class `ModelData`  
`class ModelData`  
_L27-70_
- L30 _public prototype_ `ModelData();`
- L31 _public prototype_ `~ModelData();`
- L32 _public prototype_ `ModelData(ModelData&& other) = delete;`
- L33 _public prototype_ `ModelData(const ModelData& other) = delete;`
- L34 _public prototype_ `ModelData& operator=(ModelData&& other) = delete;`
- L35 _public prototype_ `ModelData& operator=(const ModelData& other) = delete;`
- L37 _public prototype_ `bool Load(const RigCalibrationDatabaseDescription& modelHandler, bool loadBlendshapes = true);`
- L39 _public prototype_ `void Set(const std::map<std::string, std::shared_ptr<IdentityBlendModel<float, -1>>>& models, const std::string& neutralName, const std::string& skinningName, const std::map<std::string, std::pair<Eigen::VectorXf, Eigen::MatrixXf>>& geneCode, const std::map<std::string, std::map<std::string, std::pair<int, int>>>& geneCodeExprRange, const std::map<std::string, SkinningRegionData>& skinningModel, const std::shared_ptr<IdentityBlendModel<float>>& stabilizationModel);`
- L47 _public prototype_ `int NumModels() const;`
- L49 _public prototype_ `const std::shared_ptr<IdentityBlendModel<float, -1>> GetModel(const std::string& modelName) const;`
- L51 _public prototype_ `const std::string& GetNeutralName() const;`
- L52 _public prototype_ `const std::string& GetSkinningName() const;`
- L53 _public prototype_ `const std::vector<std::string>& GetModelNames() const;`
- L54 _public prototype_ `const std::string& GetModelVersionIdentifier() const;`
- L56 _public prototype_ `const std::map<std::string, std::pair<Eigen::VectorXf, Eigen::MatrixXf>>& GetRegionGeneCodeMatrices() const;`
- L57 _public prototype_ `const std::map<std::string, std::map<std::string, std::pair<int, int>>>& GetRegionGeneCodeExprRanges() const;`
- L58 _public prototype_ `const std::map<std::string, SkinningRegionData>& GetSkinningModel() const;`
- L59 _public prototype_ `SkinningRegionData GetRegionSkinningModel(const std::string& region) const;`
- L60 _public prototype_ `const std::vector<std::string>& GetSkinningModelRegions() const;`
- L62 _public prototype_ `const std::shared_ptr<IdentityBlendModel<float>>& GetStabilizationModel() const;`
- L65 _public prototype_ `std::vector<std::pair<Eigen::VectorXf, Eigen::MatrixXf>> GetExpressionGeneCodeModes(const std::string expressionName) const;` — per region, gene code modes for given expressions
- L69 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rigcalibration_core/include/rigcalibration/RigCalibrationConfigurationData.h` (Private)


#### class `RigCalibrationConfigurationData`  
`class RigCalibrationConfigurationData`  
_L13-17_
- L16 _public prototype_ `static const std::shared_ptr<RigCalibrationParams> Load(const RigCalibrationDatabaseDescription& modelHandler);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rigcalibration_core/include/rigcalibration/RigCalibrationCore.h` (Private)


#### class `RigCalibrationCore`  
`class RigCalibrationCore`  
_L10-17_
- L13 _public prototype_ `static std::map<std::string, Eigen::VectorXf> CalibrateExpressionsAndSkinning(const std::shared_ptr<ModelData> &data, const std::map<std::string, Eigen::VectorXf> &currentParams, RigCalibrationParams params, bool linearize = false);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rigcalibration_core/include/rigcalibration/RigCalibrationDatabaseDescription.h` (Private)


#### class `RigCalibrationDatabaseDescription`  
`class RigCalibrationDatabaseDescription`  
_L13-72_
- L16 _public prototype_ `RigCalibrationDatabaseDescription() = default;`
- L17 _public prototype_ `~RigCalibrationDatabaseDescription() = default;`
- L19 _public prototype_ `bool Load(const std::string &file, bool jointsAndBlends = true);`
- L21 _public function_ `const std::vector<std::string>& GetExpressionModelPaths() const`
- L23 _public function_ `const std::string& GetIdentityModelName() const`
- L25 _public function_ `const std::vector<std::string>& GetExpressionModelNames() const`
- L27 _public prototype_ `const std::string& GetExpressionModelPath(const int it) const;`
- L29 _public prototype_ `const std::string& GetExpressionBlendshapeModelPath(const int it) const;`
- L31 _public function_ `const std::string& GetGeneCodeMatrixFilePath() const`
- L33 _public function_ `const std::string& GetModelVersionIdentifer() const`
- L35 _public prototype_ `const std::string& GetRigDefinitionFilePath(bool withoutRbf) const;`
- L37 _public prototype_ `const std::string& GetArchetypeDnaFilePath(bool withoutRbf) const;`
- L39 _public function_ `const std::string& GetCalibrationConfigurationFile() const`
- L41 _public function_ `const std::string& GetNeutralFittingConfigurationFile() const`
- L43 _public function_ `const std::string& GetBlendshapeModelSuffix() const`
- L45 _public function_ `const std::vector<int>& GetModelMeshIds() const`
- L47 _public function_ `const std::vector<int>& GetSkinningMeshIds() const`
- L49 _public function_ `const std::string& GetSkinningModelFilePath() const`
- L51 _public function_ `const std::string& GetSkinningModelName() const`
- L53 _public function_ `const std::string& GetStabilizationModelFilePath() const`
- L56 _private member_ `std::vector<std::string> m_loadedModelPaths;`
- L57 _private member_ `std::vector<std::string> m_loadedBlendshapeModelPaths;`
- L58 _private member_ `std::string m_stabModelPath;`
- L59 _private member_ `std::string m_geneCodeMatrixPath;`
- L60 _private member_ `std::string m_skinningModelName;`
- L61 _private member_ `std::string m_skinningModelPath;`
- L62 _private member_ `std::vector<std::string> m_loadedModelNames;`
- L63 _private member_ `std::string m_loadedIdentityModelName;`
- L64 _private member_ `std::array<std::string, 2> m_archetypeDnaPath;`
- L65 _private member_ `std::array<std::string, 2> m_rigDefinitionPath;`
- L66 _private member_ `std::string m_calibrationConfigurationFile;`
- L67 _private member_ `std::string m_neutralFittingConfigurationFile;`
- L68 _private member_ `std::string m_blendshapeModelSuffix = "_b`
- L69 _private member_ `std::string m_modelVersionIdentifier;`
- L70 _private member_ `std::vector<int> m_modelMeshIds;`
- L71 _private member_ `std::vector<int> m_skinningMeshIds;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rigcalibration_core/include/rigcalibration/RigCalibrationParams.h` (Private)


#### struct `RigCalibrationParams`  
`struct RigCalibrationParams`  
_L9-17_
- L12 _public member_ `float regularization { 0.5f };` — @regularization
- L14 _public prototype_ `void SetFromConfiguration(const Configuration& config);`
- L16 _public prototype_ `Configuration ToConfiguration() const;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rigcalibration_core/src/RigCalibrationUtils.h` (Private)


#### Free symbols / members of external scopes

- L12 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) inline std::pair<std::vector<int>, std::vector<DiffDataMatrix<float, 3, -1>>> BlendshapeDeltasToDiffDataMat(const std::map<std::string, Eigen::Matrix<float, 3, -1>> input, const std::shared_ptr<RigGeometry<float>>& rigGeometry)`
- L36 _function_ `inline void LoadConfiguration(const std::string& filename, const std::string& configurationNameSuffix, Configuration& configuration)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/rigmorpher/include/rigmorpher/RigMorphModule.h` (Private)


#### class `MeshMorphModule`  
`template <class T> class MeshMorphModule`  
_L17-25_
- L20 _public prototype_ `static Eigen::Matrix<T, 3, -1> Morph(const Eigen::Matrix<T, 3, -1>& sourceMeshVerticesStart, const Eigen::Matrix<T, 3, -1>& sourceMeshVerticesEnd, const Eigen::Matrix<T, 3, -1>& targetMeshVerticesStart, const VertexWeights<T>& targetVerticesMask, int gridSize = 128);`

#### class `RigMorphModule`  
`template <class T> class RigMorphModule`  
_L28-73_
- L32 _public prototype_ `static bool Morph(dna::Reader* reader, dna::Writer* writer, const std::map<std::string, Eigen::Matrix<T, 3, -1>>& targetVertices, const std::vector<std::string>& drivingMeshNames, const std::vector<std::string>& inactiveJointNames, const std::map<std::string, std::vector<std::string>>& drivenJointNames, const std::map<std::string, std::vector<std::string>>& dependentJointNames, const std::vector<std::string>& jointsToOptimize, const std::map<std::string, std::vector<std::string>>& deltaTransferMeshNames, const std::map<std::string, std::vector<std::string>>& rigidTransformMeshNames, const std::map<std::string, std::vector<std::string>>& uvProjectionMeshNames, const VertexWeights<T>& mainMeshGridDeformMask, int gridSize = 128, bool inParallel = true);` — perform the volumetric morph assuming that input target meshes are in "rig" space
- L50 _public prototype_ `static void UpdateTeeth(dna::Reader* reader, dna::Writer* writer, const Eigen::Matrix<T, 3, -1>& teethMeshVertices, const std::string& teethMeshName, const std::string& headMeshName, const std::vector<std::string>& drivenJointNames, const std::vector<std::string>& deltaTransferMeshNames, const std::vector<std::string>& rigidTransformMeshNames, const std::vector<std::string>& uvProjectionMeshNames, const VertexWeights<T>& mouthSocketVertices, int gridSize = 128, bool inParallel = true);` — update teeth in dna @ teethMesh is assumed to be in original space
- L64 _public prototype_ `static std::map<std::string, std::tuple<std::string, std::vector<int>, std::vector<std::vector<T>>>> CollectDeltaTransferCorrespondences( dna::Reader* reader, const std::map<std::string, std::vector<std::string>>& deltaTransferMeshNames);`
- L69 _public prototype_ `static void ApplyRigidTransform(dna::Reader* reader, dna::Writer* writer, const Affine<T, 3, 3>& rigidTransform, bool inParallel = true);` — apply rigid transform to the internal rig
- L72 _public prototype_ `static void ApplyScale(dna::Reader* reader, dna::Writer* writer, const T scale, const Eigen::Vector3<T>& scalingPivot, bool inParallel = true);` — apply scale to the internal rig

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/texture_synthesis/include/ts/ResizeHelper.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define TS_SSE_SUPPORT_RESIZE`
- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::ts)`
- L26 _prototype_ `Eigen::Matrix<Eigen::Vector3f, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> ResizeImageCubic3fSimple( Eigen::Ref<const Eigen::Matrix<Eigen::Vector3f, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> input, int rows, int cols, Eigen::Vector3f offset, TaskThreadPool* taskThreadPool);`
- L34 _prototype_ `Eigen::Matrix<Eigen::Vector3f, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> ResizeImageCubic3fSSE( Eigen::Ref<const Eigen::Matrix<Eigen::Vector3f, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> input, int rows, int cols, Eigen::Vector3f offset, TaskThreadPool* taskThreadPool);`
- L42 _prototype_ `Eigen::Matrix<Eigen::Vector3f, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> ResizeImageCubic3f( Eigen::Ref<const Eigen::Matrix<Eigen::Vector3f, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> input, int rows, int cols, Eigen::Vector3f offset, TaskThreadPool* taskThreadPool);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/texture_synthesis/include/ts/model_data_provider_interface.h` (Private)


#### struct `Model_Data`  
`struct Model_Data`  
_L13-78_
- desc: Thin wrapper for accessing matrix/vector representations of the texture synthesis model data Layout is [rows, cols, channels] of word_size bytes Model_Data objects *DO NOT* assume ownership of the underlying buffer
- L15 _public function_ `Model_Data() : _rows(0), _cols(0), _word_size(0), _channels(0), _data(nullptr)`
- L23 _public function_ `Model_Data(int32_t rows, int32_t cols, int32_t channels, int32_t word_size, uint8_t* data) : _rows(rows) , _cols(cols) , _word_size(word_size) , _channels(channels) , _data(data)`
- L31 _public prototype_ `Model_Data(const Model_Data& rhs) = default;`
- L33 _public function_ `constexpr operator bool() const`
- L38 _public function_ `constexpr int32_t cols() const`
- L43 _public function_ `constexpr int32_t rows() const`
- L48 _public function_ `constexpr int32_t word_size() const`
- L53 _public function_ `constexpr int32_t channels() const`
- L59 _public function_ `template<typename T> constexpr const T* data() const`
- L64 _public prototype_ `bool reshape(int32_t rows, int32_t cols, int32_t channels);`
- L67 _public prototype_ `[[nodiscard]] Model_Data row_view(int32_t row) const;` — Returns a Model_Data object with the data of single row
- L70 _public prototype_ `[[nodiscard]] Model_Data row_view_as_image(int32_t row, int32_t image_resolution) const;` — Returns a Model_Data object with the data of single row but reshaped as a 3 channel square image (image_resolution x image_resolution x 3)
- L73 _protected member_ `int32_t _rows;`
- L74 _protected member_ `int32_t _cols;`
- L75 _protected member_ `int32_t _word_size;`
- L76 _protected member_ `int32_t _channels;`
- L77 _protected member_ `uint8_t* _data;`

#### struct `IModel_Data_Provider`  
`struct IModel_Data_Provider`  
_L84-108_
- desc: Storage abstraction for TS model data Implement this to support different storage formats and access types
- L101 _public prototype_ `[[nodiscard]] virtual Model_Data load(TextureType texture_type, Frequency frequency, int map_id, int HFIndex) = 0;` — Load a texture image with the required parameters. The texture images represent different kinds of data, depending on the parameters and on the texture type. This is as follows: - For albedo maps (since we need to syntesize these): LF textures: map_id = 0 (neutral)  -> LF neutral complement map_id > 0 (animated) -> LF animated delta HF textures: map_id = 0 (neutral)  -> neutral HF map_id > 0 (animated) -> HF animated delta - For normal and cavity maps (since we need to directly select those): LF textures not present HF textures: map_id = 0 (neutral)  -> full neutral texture map_id > 0 (animated) -> full animated delta (normals only)
- L104 _public prototype_ `[[nodiscard]] virtual Model_Data load(TextureType texture_type) = 0;` — Load data types dependent on texture type. Our only case: LF models
- L107 _public prototype_ `[[nodiscard]] virtual Model_Data load(Data_Type type) = 0;` — Load data types which are independent of other parameters (uv mask, pca matrices, v_to_vui_map)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/texture_synthesis/include/ts/pca.h` (Private)


#### class `PCA`  
`template <typename MatrixType> class PCA`  
_L10-40_
- L12 _private typedef_ `typedef typename MatrixType::Scalar Scalar;`
- L15 _public function_ `PCA()`
- L16 _public function_ `PCA(const Eigen::VectorX<Scalar>& mu, const MatrixType& S, const MatrixType& T) : m_mu(mu) , m_S(S) , m_T(T)`
- L21 _public function_ `PCA(Eigen::VectorX<Scalar>&& mu, MatrixType&& S, MatrixType&& T) : m_mu(std::move(mu)) , m_S(std::move(S)) , m_T(std::move(T))`
- L27 _public function_ `int Size() const`
- L28 _public function_ `int NumCoeffs() const`
- L30 _public function_ `const Eigen::VectorX<Scalar>& Mu() const`
- L31 _public function_ `const MatrixType& S() const`
- L32 _public function_ `const MatrixType& T() const`
- L34 _public function_ `Eigen::VectorX<Scalar> Reconstruct(const Eigen::VectorX<Scalar>& v) const`
- L37 _private member_ `Eigen::VectorX<Scalar> m_mu;`
- L38 _private member_ `MatrixType m_S;`
- L39 _private member_ `MatrixType m_T;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/texture_synthesis/include/ts/sl_model.h` (Private)


#### class `SLModel`  
`class SLModel`  
_L15-47_
- L18 _public typedef_ `using Scalar = float;`
- L19 _public typedef_ `using Vector2 = Eigen::Vector2<Scalar>;`
- L20 _public typedef_ `using Vector3 = Eigen::Vector3<Scalar>;`
- L21 _public typedef_ `using VectorX = Eigen::VectorX<Scalar>;`
- L22 _public typedef_ `using RowVectorX = Eigen::RowVectorX<Scalar>;`
- L23 _public typedef_ `using MatrixType = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;`
- L24 _public typedef_ `using ImageType = Eigen::Matrix<Vector3, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;`
- L27 _public function_ `SLModel()`
- L28 _public prototype_ `SLModel(const TextureModelParams& params);`
- L31 _public prototype_ `bool Load(IModel_Data_Provider& modelDataProvider);` — load the required data
- L34 _public prototype_ `bool is_valid() const;` — @returns True if the SL model has valid data.
- L35 _public prototype_ `ImageType synthesize_neutral_LF(const Vector2& v, const float yellow_offset=0.0f) const;`
- L36 _public function_ `Vector3 skin_tone(const Vector2& v) const`
- L37 _public prototype_ `const MatrixType& LF_model() const;`
- L38 _public prototype_ `Vector2 ProjectSkinTone(const Vector3& skin_tone) const;`
- L41 _private prototype_ `MatrixType yellow_graded_LF_model(const float yellow_offset) const;`
- L43 _private member_ `int m_res_LF{};`
- L44 _private member_ `PCA<MatrixType> m_skin_tones_pca{};`
- L45 _private member_ `MatrixType m_LF_model{};`
- L46 _private member_ `RowVectorX m_yellow_mask{};`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/texture_synthesis/include/ts/texture_model.h` (Private)


#### class `TextureModel`  
`class TextureModel`  
_L14-93_
- L17 _public typedef_ `using Scalar = SLModel::Scalar;`
- L18 _public typedef_ `using Vector2 = SLModel::Vector2;`
- L19 _public typedef_ `using Vector3 = SLModel::Vector3;`
- L20 _public typedef_ `using VectorX = SLModel::VectorX;`
- L21 _public typedef_ `using MatrixType = SLModel::MatrixType;`
- L22 _public typedef_ `using ImageType = SLModel::ImageType;`
- L26 _public prototype_ `bool Load(const std::string& ts_params_path, IModel_Data_Provider& modelDataProvider);` — load the required data and initialize the texture model
- L28 _public prototype_ `bool IsValid() const;`
- L29 _public function_ `std::string LocalModelVersion() const`
- L30 _public function_ `std::string RequiredModelVersion() const`
- L31 _public function_ `const TextureModelParams& Parameters()`
- L32 _public prototype_ `Vector2 ApplyAxisTransform(const Vector2& vui, int vuiAxisTransform) const;`
- L53 _public prototype_ `bool GetTexture(Eigen::Vector4<uint8_t>* const outData, const SynthesizeParams& params, IModel_Data_Provider& modelDataProvider, TITAN_NAMESPACE::TaskThreadPool* taskThreadPool = nullptr) const;` — Generates the texture based on the input params See more the SynthesizeParams & IModel_Data_Provider properties for more details outData should be preallocated Eigen buffer matching the size of the model data providers after a successfully execution, it will contain the returned image in BGRA 8 bits per color optionally a TaskThreadPool can be passed to use multi threading, otherwise all operations will execute on the caller's thread
- L58 _public prototype_ `bool SynthesizeAlbedo(Eigen::Vector4<uint8_t>* const outData, const SynthesizeParams& params, IModel_Data_Provider& modelDataProvider, TITAN_NAMESPACE::TaskThreadPool* taskThreadPool = nullptr) const;`
- L63 _public prototype_ `bool SynthesizeAlbedoAnimatedDelta(Eigen::Vector4<uint8_t>* const out_data, const SynthesizeParams& params, IModel_Data_Provider& modelDataProvider, TITAN_NAMESPACE::TaskThreadPool* task_thread_pool) const;`
- L68 _public prototype_ `bool DirectSelection(Eigen::Vector4<uint8_t>* const outData, const SynthesizeParams& params, IModel_Data_Provider& modelDataProvider, TITAN_NAMESPACE::TaskThreadPool* taskThreadPool = nullptr) const;`
- L73 _public function_ `Vector3 SkinTone(const Vector2& v) const`
- L74 _public prototype_ `Vector2 VuiToV(const Vector2& vui) const;`
- L75 _public prototype_ `Vector2 VToVui(const Vector2& v) const;`
- L76 _public prototype_ `Vector3 BodyAlbedoGain(const Vector2& vui) const;`
- L77 _public prototype_ `Vector2 ProjectMigrationSkinTone(const Vector3& skin_tone, const int HF_i, IModel_Data_Provider& modelDataProvider) const;`
- L82 _private prototype_ `bool VersionCheck();`
- L83 _private prototype_ `void GradeHF(ImageType& HF, const float redness_HF, const float saturation_HF, TITAN_NAMESPACE::TaskThreadPool* taskThreadPool = nullptr) const;`
- L88 _private member_ `const std::string m_requiredTsModelVersion { "1.3"`
- L89 _private member_ `TextureModelParams m_params;`
- L90 _private member_ `std::vector<CharacterParams> m_characterParams;`
- L91 _private member_ `SLModel m_slModel {};`
- L92 _private member_ `MatrixType m_v1Ranges {};`

#### struct `TextureModel::SynthesizeParams`  
`struct SynthesizeParams`  
_L35-43_
- desc: Parameters for synthezing texture with the model
- L37 _public member_ `TextureType texture_type;` — The texture to synthesize, current selection between ALBEDO/NORMAL/CAVITY
- L38 _public member_ `Vector2 v_ui;` — Vector2 containing values in [0, 1], representing the UI coordinates of the skin tone selection
- L39 _public member_ `int HF_index;` — Index for the HF model data
- L40 _public member_ `int map_id;` — 0: Neutral map; 1, 2, 3: Animated maps
- L41 _public member_ `bool animated_delta;` — An animated delta is returned instead of a full texture. Ignored if map_id == 0
- L42 _public member_ `int resolution;` — Expected image resolution. An error is thrown if this doesn't match the model resolution

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/texture_synthesis/include/ts/ts_types.h` (Private)


#### enum `Data_Type`  
`enum Data_Type : uint8_t`  
_L14-23_
- L16 _public enumerator_ `LF_model = 0`
- L17 _public enumerator_ `pca_mu`
- L18 _public enumerator_ `pca_S`
- L19 _public enumerator_ `pca_T`
- L20 _public enumerator_ `v1_ranges`
- L21 _public enumerator_ `yellow_mask`
- L22 _public enumerator_ `Count`

#### enum `TextureType`  
`enum TextureType : uint8_t`  
_L25-30_
- L27 _public enumerator_ `ALBEDO = 0`
- L28 _public enumerator_ `NORMAL = 1`
- L29 _public enumerator_ `CAVITY = 2`

#### enum `Frequency`  
`enum Frequency : uint8_t`  
_L32-36_
- L34 _public enumerator_ `LF = 0`
- L35 _public enumerator_ `HF = 1`

#### struct `TextureModelParams`  
`struct TextureModelParams`  
_L38-55_
- L40 _public member_ `std::string ts_version;`
- L41 _public member_ `int resolution_LF;`
- L42 _public member_ `int n_HF_index;`
- L43 _public member_ `std::map<TextureType, int> n_textures_of_type_per_chr;`
- L44 _public member_ `int v_ui_axis_transform;`
- L45 _public member_ `float v0_range_min;`
- L46 _public member_ `float v0_range_max;`
- L48 _public prototype_ `TextureModelParams(const JsonElement& j);`
- L49 _public function_ `TextureModelParams()`
- L51 _public member_ `static constexpr TextureType ALL_TEXTURE_TYPES[3] = { TextureType::ALBEDO, TextureType::NORMAL, TextureType::CAVITY };`
- L52 _public prototype_ `static const char* TextureTypeToStr(TextureType texture_type);`
- L53 _public prototype_ `static const char* FrequencyToStr(Frequency frequency);`
- L54 _public prototype_ `static TextureType TextureStrToTextureType(const std::string& texture_str);`

#### struct `CharacterParams`  
`struct CharacterParams`  
_L57-71_
- L59 _public member_ `std::array<float, 2> gain_LF;`
- L60 _public member_ `std::array<float, 2> gain_HF;`
- L61 _public member_ `std::array<float, 2> redness_HF;`
- L62 _public member_ `std::array<float, 2> saturation_HF;`
- L63 _public member_ `std::array<float, 2> yellowness_LF;`
- L64 _public member_ `float v_ui_chr_0;`
- L65 _public member_ `std::array<std::array<Eigen::Vector3f, 2>, 4> colour_ranges_LF;`
- L66 _public member_ `std::map<int, std::array<std::array<Eigen::Vector3f, 2>, 4>> colour_ranges_HF;`
- L68 _public prototype_ `CharacterParams(const JsonElement& j);`
- L69 _public prototype_ `std::pair<Eigen::Vector3f, Eigen::Vector3f> GetLFColourRange(const int map_i) const;`
- L70 _public prototype_ `std::pair<Eigen::Vector3f, Eigen::Vector3f> GetHFColourRange(const int res, const int map_i) const;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/texture_synthesis/include/ts/utils/cached_data_provider.h` (Private)


#### struct `CachedModelData`  
`struct CachedModelData : public Model_Data`  
_L25-98_
- inherits: `Model_Data`
- desc: Bespoke data container and memory manager for model data used by TS This class manages memory allocated for matrices etc and each instance provides information similar to NPY arrays: rows, cols, word_size Memory managed by this class is either cached or uncached; * Uncached model data is intended for data used by TS regardless of the specific character map being synthesised, i.e. PCA and mask data * Cached model data is intended for use by the large HF arrays specific to a character map being synthesised. This data is keyed (and can therefore be re-used without reloading) and can also be purged to reduce memory usage with the Model_Data::trim_cache function See main_texturesynthesis.cpp and texture_model.cpp for examples of how this is used
- L27 _public typedef_ `using key_t = uint64_t;`
- L28 _public member_ `static constexpr key_t nullkey = 0UL;`
- L29 _public member_ `static const CachedModelData InvalidCachedData;`
- L31 _public function_ `CachedModelData() : Model_Data() , _allocation_size(0) , _loaded(nullptr)`
- L37 _public prototype_ `CachedModelData(const CachedModelData& rhs) = default;`
- L41 _public function_ `template <typename T> constexpr T* data()` — Write access
- L46 _public prototype_ `static const CachedModelData& get_cached(key_t key_base);`
- L49 _public prototype_ `static const CachedModelData& allocate(int32_t cols, int32_t rows, int32_t word_size, int32_t channels);` — allocate an uncached Model_Data instance
- L63 _public prototype_ `static const CachedModelData& allocate_cached(key_t key_base, int32_t cols, int32_t rows, int32_t word_size, int32_t channels);` — NOTE: if the keyed entry already exists in the cache it is returned but if the shape of the stored data mismatches the return is an empty Model_Data instance TODO: this could be an assert, but we don't want to bomb out on it in here, or perhaps include carbon for CARBON_ASSERT?
- L69 _public prototype_ `static void free_all();` — <summary> free all allocated memory </summary> after this call any Model_Data instance is invalid and access to its data will crash
- L76 _public prototype_ `static void trim_cache(size_t max_cached_allocation_size);` — <summary> clears out cached items, if available, to drive the size of cached allocations down to or below the given ceiling </summary> NOTE: Only call this when no threads are using data, i.e. this can be done in serialized portions of the caller code ONLY <param name="max_cached_allocation_size"></param>
- L78 _public prototype_ `void make_available();`
- L80 _public prototype_ `bool is_available() const;`
- L82 _public function_ `constexpr size_t allocation_size() const`
- L88 _private member_ `size_t _allocation_size;`
- L89 _private typedef_ `using shared_loaded_flag = std::shared_ptr<std::atomic<bool>>;`
- L90 _private member_ `shared_loaded_flag _loaded;`
- L92 _private typedef_ `using cached_allocations_t = std::map<CachedModelData::key_t, CachedModelData>;`
- L93 _private typedef_ `using allocations_t = std::vector<CachedModelData>;`
- L95 _private member_ `static allocations_t _allocated;`
- L96 _private member_ `static cached_allocations_t _allocated_cached;`
- L97 _private member_ `static size_t _cached_allocation_size;`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Private/texture_synthesis/include/ts/utils/ts_utils.h` (Private)


#### struct `detail::load_npy_model_data_no_concurrency_policy`  
`struct load_npy_model_data_no_concurrency_policy`  
_L25-41_
- desc: default lock policy for load_npy_model_data
- L27 _public typedef_ `using lock_t = void*;`
- L28 _public function_ `static lock_t lock_shared()`
- L31 _public function_ `static lock_t lock_unique()`
- L35 _public function_ `static void raise_critical_error()`
- L38 _public function_ `static bool critical_error_signal_set()`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace detail`
- L44 _function_ `template <typename T> Eigen::Map<const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> ModelDataToEigenMap(const Model_Data& model_data)` (scope `detail`)
- L54 _function_ `template <typename T> Eigen::Map<const Eigen::Matrix<Eigen::Vector3<T>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> ReshapeSquare(Eigen::Ref<const Eigen::VectorX<T>> src)` (scope `detail`)
- L63 _function_ `template <typename T> Eigen::Matrix<Eigen::Vector3f, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> UintToFp(const uint8_t* imageData, const int resolution, const std::pair<Eigen::Vector3f, Eigen::Vector3f>& range, TITAN_NAMESPACE::TaskThreadPool* task_thread_pool)` (scope `detail`)
- L79 _function_ `auto convert = [&](int start, int end)` (scope `detail::UintToFp`)
- L94 _prototype_ `Eigen::Matrix<Eigen::Vector3f, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> ResizeImage(const Eigen::Matrix<Eigen::Vector3f, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& image, const int new_size, const Eigen::Vector3f& offset = Eigen::Vector3f::Zero(), TaskThreadPool* threadPool = nullptr);` (scope `detail`)
- L96 _prototype_ `Eigen::Matrix<Eigen::Vector3f, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> ModelDataToImageType(const Model_Data& model_data, const std::pair<Eigen::Vector3f, Eigen::Vector3f>& range, TITAN_NAMESPACE::TaskThreadPool* task_thread_pool);` (scope `detail`)
- L100 _prototype_ `bool LoadTSParams(const JsonElement& ts_params_json, TextureModelParams& model_params, std::vector<CharacterParams>& character_params);` (scope `detail`)
- L102 _prototype_ `float Interpolate(const std::array<float, 2>& extremes, const float x);` (scope `detail`)
- L104 _prototype_ `float InterpolatePiecewise(const std::array<float, 2>& extremes, const float x, const float v_ui_chr_0, const float param_baseline);` (scope `detail`)
- L106 _prototype_ `std::string zfill(const std::string& input, size_t width);` (scope `detail`)
- L108 _prototype_ `bool AreFloatsEqual(const float a, const float b);` (scope `detail`)
- L110 _prototype_ `bool HasFourTextureColourRangesFormat(const JsonElement& texture_ranges_json);` (scope `detail`)
- L112 _prototype_ `bool HasTextureModelParamsFormat(const JsonElement& model_json);` (scope `detail`)
- L114 _prototype_ `bool HasCharacterParamsFormat(const JsonElement& chr_json);` (scope `detail`)
- L133 _function_ `template<typename T = float, typename ConcurrencyPolicy = detail::load_npy_model_data_no_concurrency_policy> inline CachedModelData load_npy_model_data(const std::string& npy_path, CachedModelData::key_t key = CachedModelData::nullkey)` — load npy model data and allocate a Model_Data instance for it If the data is loaded as cached the result might not be available immediately and it is the caller's responsibility to check (and potentially wait) for the data to be available by checking ts::Model_Data::is_available() ConcurrencyPolicy is a policy that dictates how locking and error signals are handled and is a choice left to the implementor (of IModel_Data_Provider for example). ERROR HANDLING * Any file open or load issue is considered "critical" but what this means is delegated to the ConcurrencyPolicy implementation * No exceptions are thrown, but an empty Model_Data instance is returned on error key is a hash value or Model_Data::nullkey if the data should NOT be cached
- L223 _function_ `template<class T, int vec_size> std::string vector_to_str(const Eigen::Vector<T, vec_size>& vec, const bool reverse = false)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Public/EvaluateRig.h` (Public)


#### struct `FArrayOfVertices`  
`struct FArrayOfVertices`  
_L16-22_
- reflection: `USTRUCT(BlueprintType)`
- desc: Wrapper struct so we can return an array of mesh vertex data
- L21 _public member_ `TArray<FVector> Vertices;` — `UPROPERTY(BlueprintReadWrite, Category = "MetaHuman|EvaluateRig")`

#### class `UEvaluateRig`  
`class UEvaluateRig : public UObject`  
_L29-70_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UObject`
- desc: Blueprint class to allow a DNA rig to be evaluated for raw control values and the mesh vertices returned
- L37 _public function_ `bool SetRigDNAFromAsset(UDNA* InDNA)` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|EvaluateRig")` — Set the rig DNA from UDNA asset
- L45 _public function_ `bool SetRigDNA(UDNAAsset* InDNAAsset)` — `UE_DEPRECATED(5.8, "Use SetRigDNAFromAsset(UDNA*) instead")` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|EvaluateRig", meta = (DeprecatedFunction, DeprecationMessage = "Use SetRigDNAFromAsset with UDNA asset instead"))` — Set the rig DNA from legacy DNAAsset (deprecated - use UDNA instead)
- L54 _public function_ `void EvaluateRawControls(const TMap<FString, float>& InControls, const TArray<int>& InMeshIndices, int32 InLod, TArray<FArrayOfVertices>& OutMeshVertices, bool & bOutSuccess) const` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|EvaluateRig")` — evaluate the passed in raw controls for the specified mesh indices and lod, returning the evaluated vertices for each mesh in OutMeshVertices. Note that only valid raw control names will be set in the rig
- L69 _private member_ `UE::Wrappers::FMetaHumanEvaluateRig EvaluateRig;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCORETECHLIB_API`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Public/FReader.h` (Public)


#### class `dna::FReader`  
`class FReader : public BinaryStreamReader`  
_L13-228_
- inherits: `BinaryStreamReader`
- desc: Wrapper stream reader for accessing asset DNA data via the BinaryStreamReader interface The code is similar to the FSkelMeshDNAReader but implements the dna::BinaryStreamReader interface instead of the IDNAReader one
- L17 _public function_ `explicit FReader(UDNAAsset* DNAAsset)`
- L22 _public member_ `const Reader* DNAReader;`
- L25 _public function_ `virtual std::uint32_t getVertexPositionCount(std::uint16_t meshIndex) const override` — geometry
- L26 _public function_ `virtual Position getVertexPosition(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L27 _public function_ `virtual ConstArrayView<float> getVertexPositionXs(std::uint16_t meshIndex) const override`
- L28 _public function_ `virtual ConstArrayView<float> getVertexPositionYs(std::uint16_t meshIndex) const override`
- L29 _public function_ `virtual ConstArrayView<float> getVertexPositionZs(std::uint16_t meshIndex) const override`
- L30 _public function_ `virtual std::uint32_t getVertexTextureCoordinateCount(std::uint16_t meshIndex) const override`
- L31 _public function_ `virtual TextureCoordinate getVertexTextureCoordinate(std::uint16_t meshIndex, std::uint32_t textureCoordinateIndex) const override`
- L32 _public function_ `virtual ConstArrayView<float> getVertexTextureCoordinateUs(std::uint16_t meshIndex) const override`
- L33 _public function_ `virtual ConstArrayView<float> getVertexTextureCoordinateVs(std::uint16_t meshIndex) const override`
- L34 _public function_ `virtual std::uint32_t getVertexNormalCount(std::uint16_t meshIndex) const override`
- L35 _public function_ `virtual Normal getVertexNormal(std::uint16_t meshIndex, std::uint32_t normalIndex) const override`
- L36 _public function_ `virtual ConstArrayView<float> getVertexNormalXs(std::uint16_t meshIndex) const override`
- L37 _public function_ `virtual ConstArrayView<float> getVertexNormalYs(std::uint16_t meshIndex) const override`
- L38 _public function_ `virtual ConstArrayView<float> getVertexNormalZs(std::uint16_t meshIndex) const override`
- L39 _public function_ `virtual std::uint32_t getVertexLayoutCount(std::uint16_t meshIndex) const override`
- L40 _public function_ `virtual VertexLayout getVertexLayout(std::uint16_t meshIndex, std::uint32_t layoutIndex) const override`
- L41 _public function_ `virtual ConstArrayView<std::uint32_t> getVertexLayoutPositionIndices(std::uint16_t meshIndex) const override`
- L42 _public function_ `virtual ConstArrayView<std::uint32_t> getVertexLayoutTextureCoordinateIndices(std::uint16_t meshIndex) const override`
- L43 _public function_ `virtual ConstArrayView<std::uint32_t> getVertexLayoutNormalIndices(std::uint16_t meshIndex) const override`
- L44 _public function_ `virtual std::uint32_t getFaceCount(std::uint16_t meshIndex) const override`
- L45 _public function_ `virtual ConstArrayView<std::uint32_t> getFaceVertexLayoutIndices(std::uint16_t meshIndex, std::uint32_t faceIndex) const override`
- L46 _public function_ `virtual std::uint16_t getMaximumInfluencePerVertex(std::uint16_t meshIndex) const override`
- L47 _public function_ `virtual std::uint32_t getSkinWeightsCount(std::uint16_t meshIndex) const override`
- L48 _public function_ `virtual ConstArrayView<float> getSkinWeightsValues(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L49 _public function_ `virtual ConstArrayView<std::uint16_t> getSkinWeightsJointIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L50 _public function_ `virtual std::uint16_t getBlendShapeTargetCount(std::uint16_t meshIndex) const override`
- L51 _public function_ `virtual std::uint16_t getBlendShapeChannelIndex(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L52 _public function_ `virtual std::uint32_t getBlendShapeTargetDeltaCount(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L53 _public function_ `virtual Delta getBlendShapeTargetDelta(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, std::uint32_t deltaIndex) const override`
- L54 _public function_ `virtual ConstArrayView<float> getBlendShapeTargetDeltaXs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L55 _public function_ `virtual ConstArrayView<float> getBlendShapeTargetDeltaYs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L56 _public function_ `virtual ConstArrayView<float> getBlendShapeTargetDeltaZs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L57 _public function_ `virtual ConstArrayView<std::uint32_t> getBlendShapeTargetVertexIndices(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L60 _public function_ `virtual ConstArrayView<std::uint16_t> getGUIToRawInputIndices() const override` — behaviour
- L61 _public function_ `virtual ConstArrayView<std::uint16_t> getGUIToRawOutputIndices() const override`
- L62 _public function_ `virtual ConstArrayView<float> getGUIToRawFromValues() const override`
- L63 _public function_ `virtual ConstArrayView<float> getGUIToRawToValues() const override`
- L64 _public function_ `virtual ConstArrayView<float> getGUIToRawSlopeValues() const override`
- L65 _public function_ `virtual ConstArrayView<float> getGUIToRawCutValues() const override`
- L66 _public function_ `virtual std::uint16_t getPSDCount() const override`
- L67 _public function_ `virtual ConstArrayView<std::uint16_t> getPSDRowIndices() const override`
- L68 _public function_ `virtual ConstArrayView<std::uint16_t> getPSDColumnIndices() const override`
- L69 _public function_ `virtual ConstArrayView<float> getPSDValues() const override`
- L70 _public function_ `virtual std::uint16_t getJointRowCount() const override`
- L71 _public function_ `virtual std::uint16_t getJointColumnCount() const override`
- L72 _public function_ `virtual ConstArrayView<std::uint16_t> getJointVariableAttributeIndices(std::uint16_t lod) const override`
- L73 _public function_ `virtual std::uint16_t getJointGroupCount() const override`
- L74 _public function_ `virtual ConstArrayView<std::uint16_t> getJointGroupLODs(std::uint16_t jointGroupIndex) const override`
- L75 _public function_ `virtual ConstArrayView<std::uint16_t> getJointGroupInputIndices(std::uint16_t jointGroupIndex) const override`
- L76 _public function_ `virtual ConstArrayView<std::uint16_t> getJointGroupOutputIndices(std::uint16_t jointGroupIndex) const override`
- L77 _public function_ `virtual ConstArrayView<float> getJointGroupValues(std::uint16_t jointGroupIndex) const override`
- L78 _public function_ `virtual ConstArrayView<std::uint16_t> getJointGroupJointIndices(std::uint16_t jointGroupIndex) const override`
- L79 _public function_ `virtual ConstArrayView<std::uint16_t> getBlendShapeChannelLODs() const override`
- L80 _public function_ `virtual ConstArrayView<std::uint16_t> getBlendShapeChannelInputIndices() const override`
- L81 _public function_ `virtual ConstArrayView<std::uint16_t> getBlendShapeChannelOutputIndices() const override`
- L82 _public function_ `virtual ConstArrayView<std::uint16_t> getAnimatedMapLODs() const override`
- L83 _public function_ `virtual ConstArrayView<std::uint16_t> getAnimatedMapInputIndices() const override`
- L84 _public function_ `virtual ConstArrayView<std::uint16_t> getAnimatedMapOutputIndices() const override`
- L85 _public function_ `virtual ConstArrayView<float> getAnimatedMapFromValues() const override`
- L86 _public function_ `virtual ConstArrayView<float> getAnimatedMapToValues() const override`
- L87 _public function_ `virtual ConstArrayView<float> getAnimatedMapSlopeValues() const override`
- L88 _public function_ `virtual ConstArrayView<float> getAnimatedMapCutValues() const override`
- L91 _public function_ `virtual std::uint16_t getGUIControlCount() const override` — definition
- L92 _public function_ `virtual StringView getGUIControlName(std::uint16_t index) const override`
- L93 _public function_ `virtual std::uint16_t getRawControlCount() const override`
- L94 _public function_ `virtual StringView getRawControlName(std::uint16_t index) const override`
- L95 _public function_ `virtual std::uint16_t getJointCount() const override`
- L96 _public function_ `virtual StringView getJointName(std::uint16_t index) const override`
- L97 _public function_ `virtual std::uint16_t getJointIndexListCount() const override`
- L98 _public function_ `virtual ConstArrayView<std::uint16_t> getJointIndicesForLOD(std::uint16_t lod) const override`
- L99 _public function_ `virtual std::uint16_t getJointParentIndex(std::uint16_t index) const override`
- L100 _public function_ `virtual std::uint16_t getBlendShapeChannelCount() const override`
- L101 _public function_ `virtual StringView getBlendShapeChannelName(std::uint16_t index) const override`
- L102 _public function_ `virtual std::uint16_t getBlendShapeChannelIndexListCount() const override`
- L103 _public function_ `virtual ConstArrayView<std::uint16_t> getBlendShapeChannelIndicesForLOD(std::uint16_t lod) const override`
- L104 _public function_ `virtual std::uint16_t getAnimatedMapCount() const override`
- L105 _public function_ `virtual StringView getAnimatedMapName(std::uint16_t index) const override`
- L106 _public function_ `virtual std::uint16_t getAnimatedMapIndexListCount() const override`
- L107 _public function_ `virtual ConstArrayView<std::uint16_t> getAnimatedMapIndicesForLOD(std::uint16_t lod) const override`
- L108 _public function_ `virtual std::uint16_t getMeshCount() const override`
- L109 _public function_ `virtual StringView getMeshName(std::uint16_t index) const override`
- L110 _public function_ `virtual std::uint16_t getMeshIndexListCount() const override`
- L111 _public function_ `virtual ConstArrayView<std::uint16_t> getMeshIndicesForLOD(std::uint16_t lod) const override`
- L112 _public function_ `virtual std::uint16_t getMeshBlendShapeChannelMappingCount() const override`
- L113 _public function_ `virtual MeshBlendShapeChannelMapping getMeshBlendShapeChannelMapping(std::uint16_t index) const override`
- L114 _public function_ `virtual ConstArrayView<std::uint16_t> getMeshBlendShapeChannelMappingIndicesForLOD(std::uint16_t lod) const override`
- L115 _public function_ `virtual Vector3 getNeutralJointTranslation(std::uint16_t index) const override`
- L116 _public function_ `virtual ConstArrayView<float> getNeutralJointTranslationXs() const override`
- L117 _public function_ `virtual ConstArrayView<float> getNeutralJointTranslationYs() const override`
- L118 _public function_ `virtual ConstArrayView<float> getNeutralJointTranslationZs() const override`
- L119 _public function_ `virtual Vector3 getNeutralJointRotation(std::uint16_t index) const override`
- L120 _public function_ `virtual ConstArrayView<float> getNeutralJointRotationXs() const override`
- L121 _public function_ `virtual ConstArrayView<float> getNeutralJointRotationYs() const override`
- L122 _public function_ `virtual ConstArrayView<float> getNeutralJointRotationZs() const override`
- L125 _public function_ `virtual StringView getName() const override` — description
- L126 _public function_ `virtual Archetype getArchetype() const override`
- L127 _public function_ `virtual Gender getGender() const override`
- L128 _public function_ `virtual std::uint16_t getAge() const override`
- L129 _public function_ `virtual std::uint32_t getMetaDataCount() const override`
- L130 _public function_ `virtual StringView getMetaDataKey(std::uint32_t index) const override`
- L131 _public function_ `virtual StringView getMetaDataValue(const char* key) const override`
- L132 _public function_ `virtual TranslationUnit getTranslationUnit() const override`
- L133 _public function_ `virtual RotationUnit getRotationUnit() const override`
- L134 _public function_ `virtual CoordinateSystem getCoordinateSystem() const override`
- L135 _public function_ `virtual RotationSequence getRotationSequence() const override`
- L136 _public function_ `virtual RotationSign getRotationSign() const override`
- L137 _public function_ `virtual FaceWindingOrder getFaceWindingOrder() const override`
- L138 _public function_ `virtual std::uint16_t getLODCount() const override`
- L139 _public function_ `virtual std::uint16_t getDBMaxLOD() const override`
- L140 _public function_ `virtual StringView getDBComplexity() const override`
- L141 _public function_ `virtual StringView getDBName() const override`
- L144 _public function_ `virtual std::uint16_t getFileFormatGeneration() const override` — Machine Learned Behavior
- L145 _public function_ `virtual std::uint16_t getFileFormatVersion() const override`
- L146 _public function_ `virtual std::uint16_t getMLControlCount() const override`
- L147 _public function_ `virtual StringView getMLControlName(std::uint16_t index) const override`
- L148 _public function_ `virtual std::uint16_t getNeuralNetworkCount() const override`
- L149 _public function_ `virtual std::uint16_t getNeuralNetworkIndexListCount() const override`
- L150 _public function_ `virtual ConstArrayView<std::uint16_t> getNeuralNetworkIndicesForLOD(std::uint16_t lod) const override`
- L151 _public function_ `virtual std::uint16_t getMeshRegionCount(std::uint16_t meshIndex) const override`
- L152 _public function_ `virtual StringView getMeshRegionName(std::uint16_t meshIndex, std::uint16_t regionIndex) const override`
- L153 _public function_ `virtual ConstArrayView<std::uint16_t> getNeuralNetworkIndicesForMeshRegion(std::uint16_t meshIndex, std::uint16_t regionIndex) const override`
- L154 _public function_ `virtual ConstArrayView<std::uint16_t> getNeuralNetworkInputIndices(std::uint16_t netIndex) const override`
- L155 _public function_ `virtual ConstArrayView<std::uint16_t> getNeuralNetworkOutputIndices(std::uint16_t netIndex) const override`
- L156 _public function_ `virtual std::uint16_t getNeuralNetworkLayerCount(std::uint16_t netIndex) const override`
- L157 _public function_ `virtual ActivationFunction getNeuralNetworkLayerActivationFunction(std::uint16_t netIndex, std::uint16_t layerIndex) const override`
- L158 _public function_ `virtual ConstArrayView<float> getNeuralNetworkLayerActivationFunctionParameters(std::uint16_t netIndex, std::uint16_t layerIndex) const override`
- L159 _public function_ `virtual ConstArrayView<float> getNeuralNetworkLayerBiases(std::uint16_t netIndex, std::uint16_t layerIndex) const override`
- L160 _public function_ `virtual ConstArrayView<float> getNeuralNetworkLayerWeights(std::uint16_t netIndex, std::uint16_t layerIndex) const override`
- L163 _public function_ `virtual std::uint16_t getRBFPoseCount() const override` — RBFDNAReader methods
- L164 _public function_ `virtual StringView getRBFPoseName(std::uint16_t poseIndex) const override`
- L165 _public function_ `virtual ConstArrayView<std::uint16_t> getRBFPoseJointOutputIndices(std::uint16_t poseIndex) const override`
- L166 _public function_ `virtual ConstArrayView<std::uint16_t> getRBFPoseBlendShapeChannelOutputIndices(std::uint16_t poseIndex) const override`
- L167 _public function_ `virtual ConstArrayView<std::uint16_t> getRBFPoseAnimatedMapOutputIndices(std::uint16_t poseIndex) const override`
- L168 _public function_ `virtual ConstArrayView<float> getRBFPoseJointOutputValues(std::uint16_t poseIndex) const override`
- L169 _public function_ `virtual float getRBFPoseScale(std::uint16_t poseIndex) const override`
- L170 _public function_ `virtual std::uint16_t getRBFPoseControlCount() const override`
- L171 _public function_ `virtual StringView getRBFPoseControlName(std::uint16_t poseControlIndex) const override`
- L172 _public function_ `virtual ConstArrayView<std::uint16_t> getRBFPoseInputControlIndices(std::uint16_t poseIndex) const override`
- L173 _public function_ `virtual ConstArrayView<std::uint16_t> getRBFPoseOutputControlIndices(std::uint16_t poseIndex) const override`
- L174 _public function_ `virtual ConstArrayView<float> getRBFPoseOutputControlWeights(std::uint16_t poseIndex) const override`
- L175 _public function_ `virtual std::uint16_t getRBFSolverCount() const override`
- L176 _public function_ `virtual std::uint16_t getRBFSolverIndexListCount() const override`
- L177 _public function_ `virtual ConstArrayView<std::uint16_t> getRBFSolverIndicesForLOD(std::uint16_t lod) const override`
- L178 _public function_ `virtual StringView getRBFSolverName(std::uint16_t solverIndex) const override`
- L179 _public function_ `virtual ConstArrayView<std::uint16_t> getRBFSolverRawControlIndices(std::uint16_t solverIndex) const override`
- L180 _public function_ `virtual ConstArrayView<std::uint16_t> getRBFSolverPoseIndices(std::uint16_t solverIndex) const override`
- L181 _public function_ `virtual ConstArrayView<float> getRBFSolverRawControlValues(std::uint16_t solverIndex) const override`
- L182 _public function_ `virtual RBFSolverType getRBFSolverType(std::uint16_t solverIndex) const override`
- L183 _public function_ `virtual float getRBFSolverRadius(std::uint16_t solverIndex) const override`
- L184 _public function_ `virtual AutomaticRadius getRBFSolverAutomaticRadius(std::uint16_t solverIndex) const override`
- L185 _public function_ `virtual float getRBFSolverWeightThreshold(std::uint16_t solverIndex) const override`
- L186 _public function_ `virtual RBFDistanceMethod getRBFSolverDistanceMethod(std::uint16_t solverIndex) const override`
- L187 _public function_ `virtual RBFNormalizeMethod getRBFSolverNormalizeMethod(std::uint16_t solverIndex) const override`
- L188 _public function_ `virtual RBFFunctionType getRBFSolverFunctionType(std::uint16_t solverIndex) const override`
- L189 _public function_ `virtual TwistAxis getRBFSolverTwistAxis(std::uint16_t solverIndex) const override`
- L192 _public function_ `virtual TranslationRepresentation getJointTranslationRepresentation(std::uint16_t jointIndex) const override` — JointBehaviorMetadataReader methods
- L193 _public function_ `virtual RotationRepresentation getJointRotationRepresentation(std::uint16_t jointIndex) const override`
- L194 _public function_ `virtual ScaleRepresentation getJointScaleRepresentation(std::uint16_t jointIndex) const override`
- L197 _public function_ `virtual std::uint16_t getTwistCount() const override` — TwistSwingDNAReader methods
- L198 _public function_ `virtual TwistAxis getTwistSetupTwistAxis(std::uint16_t twistIndex) const override`
- L199 _public function_ `virtual ConstArrayView<std::uint16_t> getTwistInputControlIndices(std::uint16_t twistIndex) const override`
- L200 _public function_ `virtual ConstArrayView<std::uint16_t> getTwistOutputJointIndices(std::uint16_t twistIndex) const override`
- L201 _public function_ `virtual ConstArrayView<float> getTwistBlendWeights(std::uint16_t twistIndex) const override`
- L202 _public function_ `virtual std::uint16_t getSwingCount() const override`
- L203 _public function_ `virtual TwistAxis getSwingSetupTwistAxis(std::uint16_t swingIndex) const override`
- L204 _public function_ `virtual ConstArrayView<std::uint16_t> getSwingInputControlIndices(std::uint16_t swingIndex) const override`
- L205 _public function_ `virtual ConstArrayView<std::uint16_t> getSwingOutputJointIndices(std::uint16_t swingIndex) const override`
- L206 _public function_ `virtual ConstArrayView<float> getSwingBlendWeights(std::uint16_t swingIndex) const override`
- L209 _public function_ `virtual uint16 getMLTypeCount() const override` — MachineLearnedBehaviorExtReader methods
- L210 _public function_ `uint16 getMLOperationSetCount(uint16 mlTypeIndex) const override`
- L211 _public function_ `uint16 getMLOperationCount(uint16 mlTypeIndex, uint16 mlOperationSetIndex) const override`
- L212 _public function_ `dna::MachineLearnedBehaviorOperationType getMLOperationType(uint16 mlTypeIndex, uint16 mlOperationSetIndex, uint16 mlOperationIndex) const override`
- L213 _public function_ `dna::ConstArrayView<uint32> getMLOperationParameters(uint16 mlTypeIndex, uint16 mlOperationSetIndex, uint16 mlOperationIndex) const override`
- L214 _public function_ `dna::ConstArrayView<uint16> getMLOperationDependencyOperationSetIndices(uint16 mlTypeIndex, uint16 mlOperationSetIndex, uint16 mlOperationIndex) const override`
- L215 _public function_ `dna::ConstArrayView<uint16> getMLOperationDependencyOperationIndices(uint16 mlTypeIndex, uint16 mlOperationSetIndex, uint16 mlOperationIndex) const override`
- L216 _public function_ `uint16 getMLOperationIndexListCount(uint16 mlTypeIndex, uint16 mlOperationSetIndex) const override`
- L217 _public function_ `dna::ConstArrayView<uint16> getMLOperationIndicesForLOD(uint16 mlTypeIndex, uint16 mlOperationSetIndex, uint16 lod) const override`
- L218 _public function_ `dna::ConstArrayView<uint16> getMLJointsInputIndices() const override`
- L219 _public function_ `dna::ConstArrayView<uint16> getMLJointsOutputIndices() const override`
- L220 _public function_ `dna::ConstArrayView<uint16> getMLJointsParameterKeys() const override`
- L221 _public function_ `dna::ConstArrayView<uint16> getMLJointsParameterValues() const override`
- L224 _public function_ `virtual void unload(dna::DataLayer Layer) override` — Reader
- L227 _public function_ `virtual void read() override` — StreamReader

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Public/IMetaHumanCoreTechLib.h` (Public)


#### class `IMetaHumanCoreTechLib`  
`class IMetaHumanCoreTechLib : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMetaHumanCoreTechLib& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Public/MetaHumanCharacterBodyIdentity.h` (Public)


#### enum `ESolveStepType`  
`enum class ESolveStepType : uint8`  
_L17-17_
- reflection: `UENUM()`
- L17 _public enumerator_ `enum class ESolveStepType : uint8 { ScaleSolve, BodySolve, FaceSolve, RefineVerticesSolve }; DECLARE_DELEGATE_RetVal_FourParams(bool, FMeshConformIteration, const FMetaHumanRigEvaluatedState& InRigEvaluatedState, const TArray<FMatrix44f>& InBindPoseMatrices, int32 InIterationCount, ESolveStepType InSolveStepType); UENUM(BlueprintType) enum class EBodyBlendOptions : uint8 { Skeleton UMETA(Tooltip = "Only skeletal proportions are blended, while maintaining shaping."),`
- L17 _public enumerator_ `enum class ESolveStepType : uint8 { ScaleSolve, BodySolve, FaceSolve, RefineVerticesSolve }; DECLARE_DELEGATE_RetVal_FourParams(bool, FMeshConformIteration, const FMetaHumanRigEvaluatedState& InRigEvaluatedState, const TArray<FMatrix44f>& InBindPoseMatrices, int32 InIterationCount, ESolveStepType InSolveStepType); UENUM(BlueprintType) enum class EBodyBlendOptions : uint8 { Skeleton UMETA(Tooltip = "Only skeletal proportions are blended, while maintaining shaping."),`
- L17 _public enumerator_ `enum class ESolveStepType : uint8 { ScaleSolve, BodySolve, FaceSolve, RefineVerticesSolve }; DECLARE_DELEGATE_RetVal_FourParams(bool, FMeshConformIteration, const FMetaHumanRigEvaluatedState& InRigEvaluatedState, const TArray<FMatrix44f>& InBindPoseMatrices, int32 InIterationCount, ESolveStepType InSolveStepType); UENUM(BlueprintType) enum class EBodyBlendOptions : uint8 { Skeleton UMETA(Tooltip = "Only skeletal proportions are blended, while maintaining shaping."),`
- L17 _public enumerator_ `enum class ESolveStepType : uint8 { ScaleSolve, BodySolve, FaceSolve, RefineVerticesSolve }; DECLARE_DELEGATE_RetVal_FourParams(bool, FMeshConformIteration, const FMetaHumanRigEvaluatedState& InRigEvaluatedState, const TArray<FMatrix44f>& InBindPoseMatrices, int32 InIterationCount, ESolveStepType InSolveStepType); UENUM(BlueprintType) enum class EBodyBlendOptions : uint8 { Skeleton UMETA(Tooltip = "Only skeletal proportions are blended, while maintaining shaping."),`

#### enum `EBodyBlendOptions`  
`enum class EBodyBlendOptions : uint8`  
_L22-27_
- reflection: `UENUM(BlueprintType)`
- L24 _public enumerator_ `Skeleton UMETA(Tooltip = "Only skeletal proportions are blended, while maintaining shaping.")`
- L25 _public enumerator_ `Shape UMETA(Tooltip = "Blends shape-based characteristics while maintaining the core skeletal proportions.")`
- L26 _public enumerator_ `Both UMETA(Tooltip = "Both skeletal proportions and shaping (volume) are blended.")`

#### enum `EMetaHumanCharacterBodyFitOptions`  
`enum class EMetaHumanCharacterBodyFitOptions : uint8`  
_L31-36_
- reflection: `UENUM(BlueprintType)`
- L33 _public enumerator_ `FitFromMeshOnly UMETA(Tooltip="Uses mesh only from the DNA file")`
- L34 _public enumerator_ `FitFromMeshAndSkeleton UMETA(Tooltip="Uses mesh and core (animation) skeleton from the DNA file")`
- L35 _public enumerator_ `FitFromMeshToFixedSkeleton UMETA(Tooltip="Uses mesh from the DNA file and the core (animation) skeleton from the current MHC state")`

#### struct `FConformBodyParams`  
`struct FConformBodyParams`  
_L39-64_
- reflection: `USTRUCT(BlueprintType)`
- L45 _public member_ `bool bBlendNeckToBody = true;` — `UPROPERTY(EditAnywhere, Category = "Import")` — True to blend the neck joint to the body
- L49 _public member_ `bool bImportHelperJoints = true;` — `UPROPERTY(EditAnywhere, Category = "Import")` — When disabled, will import core joints only. When enabled, will import core joints and helper joints
- L53 _public member_ `bool bTargetIsInMetaHumanAPose = true;` — `UPROPERTY(EditAnywhere, Category = "Conform", DisplayName = "Target Mesh is in Metahuman A-pose")` — Gives much better conform if the target is already posed in meta human A-pose
- L57 _public member_ `bool bEstimateJointsFromMesh = false;` — `UPROPERTY(EditAnywhere, Category = "Conform", AdvancedDisplay)` — Estimate joints volumetrically from mesh vertices
- L62 _public member_ `bool bAutoRigHelperJoints = true;` — `UPROPERTY(EditAnywhere, Category = "Import Mesh")` — When enabled, helper joints will be repositioned to fit the new mesh, and RBF weights will be updated. When disabled, current helper joint positions and RBF weights will be preserved.

#### class `FMetaHumanCharacterBodyIdentity`  
`class FMetaHumanCharacterBodyIdentity`  
_L66-86_
- L69 _public prototype_ `FMetaHumanCharacterBodyIdentity();`
- L70 _public prototype_ `~FMetaHumanCharacterBodyIdentity();`
- L72 _public prototype_ `bool Init(const FString& InPCAModelPath, const FString& InLegacyBodiesPath, const TSharedPtr<FMetaHumanCharacterIdentity>& InFaceIdentity = nullptr);`
- L75 _public prototype_ `int32 GetNumLOD0MeshVertices(bool bInCombined) const;` — get the number of vertices in the body model for LOD0, either for the body model or the combined body model
- L78 _public prototype_ `TArray<int32> GetBodyToCombinedMapping() const;` — get mapping from body mesh to combined mesh
- L81 _public prototype_ `TSharedPtr<FState> CreateState() const;`
- L85 _private member_ `TPimplPtr<FImpl> Impl;`

#### struct `FMetaHumanCharacterBodyConstraint`  
`struct FMetaHumanCharacterBodyConstraint`  
_L89-107_
- reflection: `USTRUCT(BlueprintType)`
- L94 _public member_ `FName Name;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Constraint")`
- L97 _public member_ `bool bIsActive = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constraint")`
- L100 _public member_ `float TargetMeasurement = 100.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constraint")`
- L103 _public member_ `float MinMeasurement = 50.0f;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Constraint")`
- L106 _public member_ `float MaxMeasurement = 50.0f;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Constraint")`

#### struct `PhysicsBodyVolume`  
`struct PhysicsBodyVolume`  
_L109-113_
- L111 _public member_ `FVector Center;`
- L112 _public member_ `FVector Extent;`

#### struct `FFloatTriplet`  
`struct FFloatTriplet`  
_L116-121_
- desc: a Simple struct representing an Eigen::Triplet in UE types which can be mem copied from Eigen::Triplet<float>
- L118 _public member_ `int32 Row;`
- L119 _public member_ `int32 Col;`
- L120 _public member_ `float Value;`

#### class `FMetaHumanCharacterBodyIdentity::FState`  
`class FMetaHumanCharacterBodyIdentity::FState`  
_L123-293_
- L126 _public prototype_ `FState();`
- L127 _public prototype_ `~FState();`
- L128 _public prototype_ `FState(const FState& InOther);`
- L131 _public prototype_ `TArray<FMetaHumanCharacterBodyConstraint> GetBodyConstraints(bool bScaleMeasurementRangesWithHeight = false) const;` — Get the body constraints from the model
- L134 _public prototype_ `void EvaluateBodyConstraints(const TArray<FMetaHumanCharacterBodyConstraint>& BodyConstraints);` — Set the body constraints and evaluate the DNA vertices based on the state
- L137 _public prototype_ `FMetaHumanRigEvaluatedState GetVerticesAndVertexNormals() const;` — Get the DNA vertices and vertex normals from the state
- L141 _public prototype_ `void GetVerticesWithAndWithoutDeltas(FMetaHumanRigEvaluatedState& OutNoDelta, FMetaHumanRigEvaluatedState& OutWithDelta) const;` — Get body state evaluated with no deltas and with full deltas at scale 1. Neither modifies the current state - both operate on internal clones.
- L144 _public prototype_ `TArray<int32> GetNumVerticesPerLOD() const;` — Get the number of vertices per LOD
- L147 _public prototype_ `TArray<int32> GetTrianglesIndices() const;` — Get the triangle indices from the state
- L150 _public prototype_ `FVector3f GetVertex(const TArray<FVector3f>& InVertices, int32 InDNAMeshIndex, int32 InDNAVertexIndex) const;` — Get vertex in UE coordinate system for a specific dna mesh and dna vertex index
- L153 _public prototype_ `TArray<FVector3f> GetRegionGizmos() const;` — Get gizmo positions used for blending regions
- L156 _public prototype_ `void BlendPresets(int32 InGizmoIndex, const TArray<TPair<float, const FState*>>& InStates, EBodyBlendOptions InBodyBlendOptions);` — Blend region based on preset weights
- L159 _public prototype_ `int32 SelectVertex(FVector3f InOrigin, FVector3f InDirection, FVector3f& OutVertex, FVector3f& OutNormal) const;` — Selects a vertex given the input ray
- L162 _public prototype_ `int32 GetNumberOfConstraints() const;` — Get the number of constraints from the model
- L165 _public prototype_ `float GetMeasurement(int32 ConstraintIndex) const;` — Get the actual measurement on the mesh for a particular constraint
- L168 _public prototype_ `void GetMeasurementsForFaceAndBody(TSharedRef<IDNAReader> InFaceDNA, TSharedRef<IDNAReader> InBodyDNA, TMap<FString, float>& OutMeasurements) const;` — Obtains measurements map (string to float) for given face and body DNAs
- L171 _public prototype_ `void GetMeasurementsForFaceAndBody(const TArray<FVector3f>& InFaceRawVertices, TMap<FString, float>& OutMeasurements) const;` — Obtains measurements map (string to float) for body state with given face vertices
- L174 _public prototype_ `TArray<FVector> GetContourVertices(int32 ConstraintIndex) const;` — Get the contour vertex positions on the mesh for a particular constraint
- L177 _public prototype_ `TArray<FMatrix44f> CopyBindPose() const;` — Copy the bind pose transforms
- L180 _public prototype_ `TArray<FMatrix44f> CopyComponentPose() const;` — Copy the current component pose transforms
- L183 _public prototype_ `void SetEvaluatePose(bool bEvaluatePose);` — Sets if a pose other than MetaHuman A pose should be evaluated
- L186 _public prototype_ `void SetApplyFloorOffset(bool bApplyFloorOffset);` — Sets if a floor offset should be applied to set body state on the floor
- L188 _public prototype_ `int32 GetNumberOfJoints() const;`
- L189 _public prototype_ `void GetNeutralJointTransform(int32 JointIndex, FVector3f& OutJointTranslation, FRotator3f& OutJointRotation) const;`
- L190 _public prototype_ `void GetNeutralJointTransforms(const TArray<FMatrix44f>& InBindPoseMatrices, TArray<FVector3f>& OutJointTranslations, TArray<FRotator3f>& OutJointRotations) const;`
- L193 _public prototype_ `void CopyCombinedModelVertexInfluenceWeights(TArray<TPair<int32, TArray<FFloatTriplet>>> & OutCombinedModelVertexInfluenceWeights) const;` — Copy the combined body model skinning weights as an array of triplets which can be used to reconstruct a sparse matrix of skinning weights
- L196 _public prototype_ `void SetCombinedModelVertexInfluenceWeightsLOD0(TArray<FFloatTriplet> InCombinedModelVertexInfluenceWeightsLOD0);` — Copy the combined body model skinning weights as an array of triplets for LOD0
- L199 _public prototype_ `void GetCombinedModelVertexInfluenceWeightsLOD0(TArray<FFloatTriplet> & OutCombinedModelVertexInfluenceWeightsLOD0) const;` — Copy the combined body model skinning weights as an array of triplets for LOD0
- L202 _public prototype_ `void Reset();` — Reset the body to the archetype
- L205 _public prototype_ `void ResetFaceModel();` — Reset the face model in body state
- L208 _public prototype_ `void ResetBodyOnly();` — Reset the body model only in body state, leaving the face unchanged
- L211 _public prototype_ `void ClearVertexDeltas();` — Clear any vertex-level deltas from the body state
- L214 _public prototype_ `EMetaHumanBodyType GetMetaHumanBodyType() const;` — Get MetaHuman body type
- L217 _public prototype_ `void SetMetaHumanBodyType(EMetaHumanBodyType InMetaHumanBodyType, bool bFitFromLegacy = false);` — Set MetaHuman body type
- L222 _public prototype_ `bool FitToBodyDna(TSharedRef<class IDNAReader> InBodyDna, EMetaHumanCharacterBodyFitOptions InBodyFitOptions);` — `UE_DEPRECATED(5.7, "FitToBodyDna with EMetaHumanCharacterBodyFitOptions has been deprecated, please use FitToBodyDna with FConformBodyParams instead.")` — Fit the Character to the supplied DNA
- L226 _public prototype_ `bool FitToTarget(const TArray<FVector3f>& InVertices, const TArray<FVector3f>& InComponentJointTranslations, EMetaHumanCharacterBodyFitOptions InBodyFitOptions);` — `UE_DEPRECATED(5.7, "FitToTarget with EMetaHumanCharacterBodyFitOptions has been deprecated, please use FitToTarget with FConformBodyParams instead.")` — Fit the Character to the supplied vertices
- L230 _public prototype_ `bool Conform(const TArray<FVector3f>& InVertices, const TArray<FVector3f>& InJointRotations, bool bTargetIsInAPose, bool bEstimateJointsFromMesh);` — Conforms the model to target parameters. Vertices must be in MH topology.
- L233 _public prototype_ `bool ConformTarget(const FConformTargetParams& InConformTargetParams);` — Conforms the model to target parameters. Vertices can be any topology.
- L236 _public prototype_ `bool AlignToTargetMesh(const FConformTargetParams& InConformTargetParams);` — Rigidly aligns the model to the target mesh using only global controls (scale, translation).
- L239 _public prototype_ `FMeshConformIteration& OnMeshConformIteration() const;` — Get delegate for updates from each iteration in conform process
- L242 _public prototype_ `bool RefineVerticesToTarget(const FRefinementTargetParams& InRefinementTargetParams);` — Refines vertices to the target mesh
- L245 _public prototype_ `bool SetJointTranslations(const TArray<FVector3f>& InComponentJointTranslations, bool bImportHelperJoints);` — Set custom joint positions
- L248 _public prototype_ `bool SetJointRotations(const TArray<FVector3f>& InJointRotations, bool bImportHelperJoints);` — Set custom joint rotations
- L251 _public prototype_ `TArray<FVector3f> GetJointTranslations() const;` — Get joint positions
- L254 _public prototype_ `bool SetMesh(const TArray<FVector3f>& InVertices, bool bRepositionHelperJoints);` — Set custom mesh
- L257 _public prototype_ `float GetGlobalDeltaScale() const;` — Get and set the body vertex and joint global delta scale
- L258 _public prototype_ `void SetGlobalDeltaScale(float InVertexDelta);`
- L262 _public prototype_ `bool Serialize(FSharedBuffer& OutArchive) const;` — Serialize/Deserialize
- L263 _public prototype_ `bool Deserialize(const FSharedBuffer& InArchive);`
- L266 _public prototype_ `TSharedRef<IDNAReader> StateToDna(dna::Reader* InDnaReader, bool bIsCombined = false, bool bUsePosedJoints = false) const;` — Create updated dna from state
- L270 _public prototype_ `TSharedRef<IDNAReader> StateToDna(UDNAAsset* InBodyDna) const;` — `UE_DEPRECATED(5.8, "Use StateToDna with reader as argument instead because old DNAAsset stored as asset user data is deprecated")` — This function is also deprecated since it seems quite useless since we can get DNA Reader directly from DNA and here we do unnecessary writing and reading from DNA
- L273 _public prototype_ `TArray<PhysicsBodyVolume> GetPhysicsBodyVolumes(const FName& InJointName) const;` — Get the list of physics volumes for a joint
- L276 _public prototype_ `TMap<FName, int32> GetPresetBodyKeyPoints() const;` — Get preset body keypoints from the body archetype
- L279 _public prototype_ `TArray<float> GetBodyModelCoefficients() const;` — Get the GUI controls from the underlying body state
- L285 _public prototype_ `TArray<FVector3f> TransformTargetVerticesToBindPose(const TArray<FVector3f>& InVertices) const;` — Transform a set of template vertices (in UE coordinate space) that are rigidly attached to the body's head joint into the body identity's shape-adjusted bind frame, also in UE space. Intended for positioning template eyes / teeth so they can be fed into the face state's FitToTarget as an accurate bind-pose target.
- L292 _private member_ `TPimplPtr<FImpl> Impl;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METAHUMANCORETECHLIB_API`
- L19 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FMeshConformIteration, const FMetaHumanRigEvaluatedState& InRigEvaluatedState, const TArray<FMatrix44f>& InBindPoseMatrices, int32 InIterationCount, ESolveStepType InSolveStepType);`
- L19 _prototype_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FMeshConformIteration, const FMetaHumanRigEvaluatedState& InRigEvaluatedState, const TArray<FMatrix44f>& InBindPoseMatrices, int32 InIterationCount, ESolveStepType InSolveStepType);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Public/MetaHumanCharacterIdentity.h` (Public)


#### enum `EMetaHumanCharacterOrientation`  
`enum class EMetaHumanCharacterOrientation : uint8`  
_L22-26_
- L24 _public enumerator_ `Y_UP = 0`
- L25 _public enumerator_ `Z_UP = 1`

#### enum `EHeadFitToTargetMeshes`  
`enum class EHeadFitToTargetMeshes : uint8`  
_L28-34_
- L30 _public enumerator_ `Head`
- L31 _public enumerator_ `LeftEye`
- L32 _public enumerator_ `RightEye`
- L33 _public enumerator_ `Teeth`

#### enum `EAlignmentOptions`  
`enum class EAlignmentOptions : uint8`  
_L41-48_
- reflection: `UENUM(meta = (ScriptName = "MetaHumanAlignmentOptions"))`
- desc: the alignment options used when performing FitToTarget
- L43 _public enumerator_ `None`
- L44 _public enumerator_ `Translation`
- L45 _public enumerator_ `RotationTranslation`
- L46 _public enumerator_ `ScalingTranslation`
- L47 _public enumerator_ `ScalingRotationTranslation`

#### struct `FFitToTargetOptions`  
`struct FFitToTargetOptions`  
_L52-64_
- reflection: `USTRUCT(BlueprintType)`
- desc: the options for performing fit to target: how alignment of the head is performed
- L57 _public member_ `EAlignmentOptions AlignmentOptions{ EAlignmentOptions::ScalingRotationTranslation };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conforming")`
- L60 _public member_ `bool bDisableHighFrequencyDelta = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conforming")`
- L63 _public member_ `bool bAdaptNeck = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conforming")`

#### enum `EBlendOptions`  
`enum class EBlendOptions : uint8`  
_L68-73_
- reflection: `UENUM()`
- desc: the options used when performing Blend
- L70 _public enumerator_ `Proportions UMETA(ToolTip = "Blends shape-based characteristics while maintaining the core skeletal proportions.")`
- L71 _public enumerator_ `Features UMETA(ToolTip = "Only skeletal proportions are blended, while maintaining shaping.")`
- L72 _public enumerator_ `Both UMETA(ToolTip = "Both skeletal proportions and shaping (volume) are blended.")`

#### class `FMetaHumanCharacterIdentity`  
`class FMetaHumanCharacterIdentity`  
_L75-112_
- L78 _public prototype_ `FMetaHumanCharacterIdentity();`
- L79 _public prototype_ `~FMetaHumanCharacterIdentity();`
- L82 _public prototype_ `bool Init(const FString& InMHCDataPath, const FString& InBodyMHCDataPath, class UDNAAsset* InDNAAsset, EMetaHumanCharacterOrientation InDNAAssetOrient);` — `UE_DEPRECATED(5.8, "This function is deprecated, use Init function that accepts DNAReader instead.")`
- L85 _public prototype_ `bool Init(const FString& InMHCDataPath, const FString& InBodyMHCDataPath, TNotNull<dna::Reader*> InDNAReader, EMetaHumanCharacterOrientation InDNAAssetOrient);`
- L89 _public prototype_ `TSharedPtr<FState> CreateState() const;`
- L95 _public prototype_ `TArray<FString> GetPresetNames() const;` — Retrieve all available presets
- L98 _public prototype_ `TSharedPtr<class IDNAReader> CopyBodyJointsToFace(dna::Reader* InBodyDnaReader, dna::Reader* InFaceDnaReader, bool bUpdateDescendentJoints = false) const;` — Copy joint bind poses from body to the face dna. Optionally update descendent joints, default behaviour is for descendent joints to not move in world space.
- L101 _public prototype_ `TSharedPtr<class IDNAReader> UpdateFaceSkinWeightsFromBodyAndVertexNormals(const TArray<TPair<int32, TArray<FFloatTriplet>>>& InCombinedBodySkinWeights, dna::Reader* InFaceDnaReader, const FMetaHumanCharacterIdentity::FState& InState) const;` — Update skin weights for the overlapping joints in the face from the body and vertex normals
- L104 _public prototype_ `int32 GetNumLOD0MeshVertices(EHeadFitToTargetMeshes InMeshType) const;` — Get the number of mesh vertices for LOD 0, for the specified mesh; returns -1 if fails
- L108 _private prototype_ `const coretechlib::titan::api::MetaHumanCreatorAPI* GetMHCAPIPtr() const;`
- L111 _private member_ `TPimplPtr<FImpl> Impl;`

#### class `FMetaHumanCharacterIdentity::FSettings`  
`class FMetaHumanCharacterIdentity::FSettings`  
_L114-148_
- L117 _public prototype_ `FSettings();`
- L118 _public prototype_ `~FSettings();`
- L119 _public prototype_ `FSettings(const FSettings& InOther);`
- L122 _public prototype_ `float GlobalVertexDeltaScale() const;` — Return the global per vertex delta used when evaluating
- L125 _public prototype_ `void SetGlobalVertexDeltaScale(float InGlobalVertexDeltaScale);` — Set the global per vertex delta used when evaluating
- L128 _public prototype_ `bool UseCompatibilityEvaluation() const;` — Return true if compatibility evaluation is used
- L131 _public prototype_ `void SetCompatibilityEvaluation(bool bInIsCompatibilityEvaluation);` — Set whether to use compatability evaluation for combining body and head
- L134 _public prototype_ `float GlobalHighFrequencyScale() const;` — Return the global scale used for applying high frequency variant
- L137 _public prototype_ `void SetGlobalHighFrequencyScale(float InGlobalHighFrequencyScale);` — Set the global scale used for applying high frequency variant
- L140 _public prototype_ `void SetHighFrequencyIteration(int32 InHighFrequencyScale);` — Set the iterations used when applying high frequency variant
- L147 _private member_ `TPimplPtr<FImpl> Impl;`

#### class `FMetaHumanCharacterIdentity::FState`  
`class FMetaHumanCharacterIdentity::FState`  
_L151-352_
- L154 _public prototype_ `FState();`
- L155 _public prototype_ `~FState();`
- L156 _public prototype_ `FState(const FState& InOther);`
- L159 _public prototype_ `FMetaHumanRigEvaluatedState Evaluate() const;` — Evaluate the DNA vertices and vertex normals based on the state
- L162 _public prototype_ `FVector3f GetVertex(const TArray<FVector3f>& InVertices, int32 InDNAMeshIndex, int32 InDNAVertexIndex) const;` — Get vertex in UE coordinate system for a specific dna mesh and dna vertex index
- L165 _public prototype_ `FVector3f GetRawVertex(const TArray<FVector3f>& InVertices, int32 InDNAMeshIndex, int32 InDNAVertexIndex) const;` — Get vertex in unconverted for a specific dna mesh and dna vertex index
- L168 _public prototype_ `void GetRawBindPose(const TArray<FVector3f>& InVertices, TArray<float>& OutBindPose) const;` — Get the raw bind pose (in DNA coord system)
- L171 _public prototype_ `void GetTrianglesIndices(TArray<int32>& OutTriangleIndices) const;` — Get the triangle indices from the state
- L174 _public prototype_ `void GetFaceModelCoefficients(TArray<float>& OutCoefficients) const;` — Get the coefficients of the underlying model
- L177 _public prototype_ `void SetFaceModelCoefficients(const TArray<float>& InCoefficients);` — Set the coefficients of the underlying model
- L180 _public prototype_ `void GetModelIdentifier(FString& OutModelIdentifier) const;` — Get the identifier of the underlying model
- L183 _public prototype_ `TArray<FVector3f> EvaluateGizmos(const TArray<FVector3f>& InVertices) const;` — Evaluate the Gizmos
- L186 _public prototype_ `int32 NumGizmos() const;` — Get the number of gizmos
- L189 _public prototype_ `TArray<FVector3f> EvaluateLandmarks(const TArray<FVector3f>& InVertices) const;` — Evaluate the Landmarks
- L192 _public prototype_ `int32 NumLandmarks() const;` — get the number of landmarks
- L195 _public prototype_ `bool HasLandmark(int32 InVertexIndex) const ;` — Is there a landmark present for the supplied vertex index
- L198 _public prototype_ `void AddLandmark(int32 InVertexIndex);` — Adds a single landmark.
- L201 _public prototype_ `void RemoveLandmark(int32 InLandmarkIndex);` — Removes a single landmark for a given landmark index. The landmark index must be in the range 0-NumLandmarks() - 1
- L204 _public prototype_ `int32 SelectFaceVertex(FVector3f InOrigin, FVector3f InDirection, FVector3f& OutVertex, FVector3f& OutNormal);` — Selects a face vertex given the input ray
- L207 _public prototype_ `void Reset();` — Reset the face to the archetype
- L210 _public prototype_ `void ResetNeckRegion();` — Reset the neck region to the body state
- L213 _public prototype_ `void Randomize(float InMagnitude);` — Randomize the face
- L216 _public prototype_ `void GetPreset(const FString& PresetName, int32 InPresetType, int32 InPresetRegion);` — Create a state based on preset
- L219 _public prototype_ `void BlendPresets(int32 InGizmoIndex, const TArray<TPair<float, const FState*>>& InStates, EBlendOptions InBlendOptions, bool bInBlendSymmetrically);` — Blend region based on preset weights
- L222 _public prototype_ `void SetGizmoPosition(int32 InGizmoIndex, const FVector3f& InPosition, bool bInSymmetric, bool bInEnforceBounds);` — Set the gizmo position
- L225 _public prototype_ `void GetGizmoPosition(int32 InGizmoIndex, FVector3f& OutPosition) const;` — Get the gizmo position
- L228 _public prototype_ `void GetGizmoPositionBounds(int32 InGizmoIndex, FVector3f& OutMinPosition, FVector3f& OutMaxPosition, float InBBoxReduction, bool bInExpandToCurrent) const;` — Get the gizmo position bounds
- L231 _public prototype_ `void SetGizmoRotation(int32 InGizmoIndex, const FVector3f& InRotation, bool bInSymmetric, bool bInEnforceBounds);` — Set the gizmo rotation
- L234 _public prototype_ `void GetGizmoRotation(int32 InGizmoIndex, FVector3f& OutRotation) const;` — Get the gizmo rotation
- L237 _public prototype_ `void GetGizmoRotationBounds(int32 InGizmoIndex, FVector3f& OutMinRotation, FVector3f& OutMaxRotation, bool bInExpandToCurrent) const;` — Get the gizmo rotation bounds
- L240 _public prototype_ `void SetGizmoScale(int32 InGizmoIndex, float InScale, bool bInSymmetric, bool bInEnforceBounds);` — Scale the gizmo
- L243 _public prototype_ `void GetGizmoScale(int32 InGizmoIndex, float& OutScale) const;` — Get the gizmo scale
- L246 _public prototype_ `void GetGizmoScaleBounds(int32 InGizmoIndex, float& OutMinScale, float& OutMaxScale, bool bInExpandToCurrent) const;` — Get the gizmo scale bounds
- L249 _public prototype_ `void TranslateLandmark(int32 InLandmarkIndex, const FVector3f& InDelta, bool bInSymmetric);` — Translate the landmarks
- L252 _public prototype_ `void SetFaceScale(float InFaceScale);` — Set the face scale relative to the body.
- L255 _public prototype_ `float GetFaceScale() const;` — Returns the face scale relative to the body.
- L258 _public prototype_ `bool FitWithVertexDeltasFromBody(const TArray<FMatrix44f>& InBodyJoints, const TArray<FVector3f>& InBodyStateVerticesNoDelta, const TArray<FVector3f>& InBodyStateVerticesWithDelta, const TArray<FVector3f>& InBodyVertexNormals, const TArray<int32>& InNumVerticesPerLod);` — Fits the face state to the supplied body joints and vertices, calculates the M2MH delta from NoDelta to WithDelta vertices
- L265 _public prototype_ `void SetBodyJointsAndBodyFaceVertices(const TArray<FMatrix44f>& InBodyJoints, const TArray<FVector3f>& InVertices);` — Update the face state from body (bind pose, vertices)
- L268 _public prototype_ `void SetBodyVertexNormals(const TArray<FVector3f>& InVertexNormals, const TArray<int32>& InNumVerticesPerLod);` — Set the body vertex normals, and an array giving the number of vertices for each lod
- L271 _public prototype_ `void ResetNeckExclusionMask();` — Reset the neck exclusion mask
- L274 _public prototype_ `int32 GetVariantsCount(const FString& InVariantName) const;` — Returns the number of variants for variant of name InVariantName (can be "eyelashes" or "teeth")
- L277 _public prototype_ `void SetVariant(const FString& InVariantName, TConstArrayView<float> InVariantWeights);` — Sets variant of name InVariantName  to State (can be "eyelashes" or "teeth")
- L280 _public prototype_ `void SetExpressionActivations(TMap<FString, float>& InExpressionActivations);` — Set the expression activations for the face state to those defined in the InExpressionActivations map
- L283 _public prototype_ `int32 GetNumHighFrequencyVariants() const;` — Returns the maximum number of High Frequency variants supported by the state
- L286 _public prototype_ `void SetHighFrequencyVariant(int32 InHighFrequencyVariant);` — Set the high frequency variant to be used by this state. Set <0 for no variant.
- L289 _public prototype_ `int32 GetHighFrequencyVariant() const;` — Returns the high frequency variant used by this state.
- L292 _public prototype_ `int32 GetInternalSerializationVersion() const;` — Gets internal face serialization version
- L298 _public prototype_ `bool FitToTarget(const TMap<int32, TArray<FVector3f>>& InPartsVertices, const FFitToTargetOptions& InFitToTargetOptions);` — Fit the Character Identity to the map of supplied part vertices (which must contain the Head, but also optionally can contain Eyes and Teeth), using the supplied options. Note that this leaves the Identity in a state where it needs autorigging. Returns true if successful, false if not
- L304 _public prototype_ `bool FitFromBodyVertices(const TArray<FVector3f>& InBodyStateVertices, const FFitToTargetOptions& InFitToTargetOptions);` — Fit the Character Identity to the body state vertices, using the supplied options. Note that this leaves the Identity in a state where it needs autorigging. Returns true if successful, false if not
- L310 _public prototype_ `TArray<FVector3f> GetHeadPartVerticesFromBody(const TArray<FVector3f>& InBodyStateVertices) const;` — Extract the head-mesh vertices from a combined body vertex array. Returns the leading face-vertex-count entries of InBodyStateVertices, matching the slice that FitFromBodyVertices feeds to the underlying MHC state. Returns an empty array if InBodyStateVertices has too few vertices.
- L314 _public prototype_ `void SetFromBodyVertexDeltaScale(float InFromBodyVertexDeltaScale);` — Sets the runtime scale applied to the M2MH vertex delta during Evaluate
- L317 _public prototype_ `void ClearFromBodyVertexDeltas();` — Clears the M2MH vertex delta applied during Evaluate
- L320 _public prototype_ `float GetFromBodyVertexDeltaScale() const;` — Gets the runtime scale applied to the M2MH vertex delta during Evaluate
- L326 _public prototype_ `bool FitToFaceDna(TSharedRef<class IDNAReader> InFaceDna, const FFitToTargetOptions& InFitToTargetOptions);` — Fit the Character Identity to the supplied DNA, using the supplied options. Note that this leaves the Identity in a state where it needs autorigging. Returns true if successful, false otherwise (for example if the DNA selected is not appropriate)
- L329 _public prototype_ `FMetaHumanCharacterIdentity::FSettings GetSettings() const;` — get settings
- L332 _public prototype_ `void SetSettings(const FMetaHumanCharacterIdentity::FSettings& InSettings);` — set settings
- L335 _public prototype_ `bool GetGlobalScale(float& scale) const;` — get global scale
- L337 _public prototype_ `void WriteDebugAutoriggingData(const FString& DirectoryPath) const;`
- L339 _public prototype_ `void Serialize(FSharedBuffer& OutArchive) const;`
- L340 _public prototype_ `bool Deserialize(const FSharedBuffer& InArchive);`
- L342 _public prototype_ `TSharedRef<class IDNAReader> StateToDna(TNotNull<dna::Reader*> InDnaReader) const;`
- L345 _public prototype_ `TSharedRef<class IDNAReader> StateToDna(class UDNAAsset* InFaceDNA) const;` — `UE_DEPRECATED(5.8, "Use StateToDna with reader as argument instead because old DNAAsset stored as asset user data is deprecated")`
- L351 _private member_ `TPimplPtr<FImpl> Impl;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METAHUMANCORETECHLIB_API`
- L16 _namespace_ `namespace coretechlib`
- L16 _namespace_ `namespace titan` (scope `coretechlib`)
- L16 _namespace_ `namespace api` (scope `coretechlib::titan`)
- L18 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Public/MetaHumanConformSolverSettings.h` (Public)


#### enum `EWeightScheduleCurve`  
`enum class EWeightScheduleCurve : uint8`  
_L10-16_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `Static`
- L13 _public enumerator_ `Linear`
- L14 _public enumerator_ `Quadratic`
- L15 _public enumerator_ `Log`

#### struct `FWeightSchedule`  
`struct FWeightSchedule`  
_L19-31_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public member_ `float Start = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weights", meta = (ClampMin = "0", UIMax = "1000"))`
- L27 _public member_ `float End = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weights", meta = (EditCondition = "Curve != EWeightScheduleCurve::Static", ClampMin = "0", UIMax = "1000"))`
- L30 _public member_ `EWeightScheduleCurve Curve = EWeightScheduleCurve::Static;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weights")`

#### struct `FBodyConformSolveSettings`  
`struct FBodyConformSolveSettings`  
_L35-145_
- reflection: `USTRUCT(BlueprintType)`
- L41 _public member_ `FString PipelineName;` — `UPROPERTY(BlueprintReadWrite, Category = "Pipeline Solve")` — Name of the solver pipeline to use.
- L45 _public member_ `bool bSolvePose = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Solve")` — Whether to solve for body pose.
- L49 _public member_ `bool bSymmetricalSolve = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Solve")` — Enforces left - right body symmetry during fitting.
- L53 _public member_ `int Iterations = 13;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Solve", meta = (ClampMin = "0", UIMax = "100"))` — Number of fitting passes. More = finer result but slower.
- L57 _public member_ `FWeightSchedule IcpGeometryWeight = { 70.0f, 70.0f, EWeightScheduleCurve::Static };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Solve")` — How strongly the surface tries to match the scan. Higher = tighter fit to scan geometry.
- L61 _public member_ `FWeightSchedule IcpSearchTolerance = { 50.0f, 50.0f, EWeightScheduleCurve::Static };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Solve")` — Maximum distance (mm) to consider a scan point as a match. Ramps down each iteration for progressively tighter matching.
- L65 _public member_ `FWeightSchedule IcpNormalCompatibility = { 0.8f, 0.8f, EWeightScheduleCurve::Static };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Solve")` — Rejects scan points whose surface normal disagrees with the model normal. Lower = more permissive matching.
- L69 _public member_ `FWeightSchedule IcpKeyPointWeight = { 1.0f, 1.0f, EWeightScheduleCurve::Static };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Solve")` — How strongly detected body keypoints (shoulders, hips, etc.) pull the rig into pose.
- L73 _public member_ `FWeightSchedule IcpLandmarksWeight = { 0.557f, 0.0f, EWeightScheduleCurve::Linear };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Solve")` — How strongly 2D landmark positions guide the fit.
- L77 _public member_ `FWeightSchedule RegularizationGlobalControls = { 0.682f, 0.682f, EWeightScheduleCurve::Static };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Solve")` — Resistance to overall shape change. Higher = stays closer to the base model shape.
- L81 _public member_ `FWeightSchedule RegularizationLocalControls = { 1.0f, 1.0f, EWeightScheduleCurve::Static };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Solve")` — Resistance to local surface deformation. Higher = smoother surface.
- L85 _public member_ `FWeightSchedule RegularizationProportions = { 1.0f, 1.0f, EWeightScheduleCurve::Static };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Solve")` — Resistance to changing body proportions. Higher = preserves original proportions.
- L89 _public member_ `FWeightSchedule RegularizationPose = { 2.0f, 0.5f, EWeightScheduleCurve::Linear };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Solve")` — Resistance to changing joint angles. Higher = stays closer to detected pose.
- L93 _public member_ `int CurveResampling = 5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Solve", meta = (ClampMin = "0", UIMax = "100"))` — Number of points used to resample curve constraints. Higher = more accurate curve matching.
- L97 _public member_ `int FaceIterations = 7;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Solve", meta = (ClampMin = "0", UIMax = "100"))` — Number of fitting passes for face solve. More = finer result but slower.
- L101 _public member_ `FWeightSchedule FaceIcpWeight = { 30.0f, 30.0f, EWeightScheduleCurve::Static };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Solve")` — How strongly the face surface tries to match the scan. Higher = tighter fit to scan geometry.
- L105 _public member_ `FWeightSchedule FaceIcpSearchTolerance = { 30.0f, 30.0f, EWeightScheduleCurve::Static };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Solve")` — Maximum distance (mm) to consider a scan point as a match for face solve. Ramps down each iteration for progressively tighter matching.
- L109 _public member_ `FWeightSchedule FaceNormalCompatibility = { 0.8f, 0.8f, EWeightScheduleCurve::Static };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Solve")` — Rejects scan points whose surface normal disagrees with the model normal for face solve. Lower = more permissive matching.
- L113 _public member_ `FWeightSchedule FaceKeypointWeight = { 10.0f, 10.0f, EWeightScheduleCurve::Static };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Solve")` — How strongly detected face keypoints (eye corners, nose tip, etc.) pull the rig into pose for face solve.
- L117 _public member_ `FWeightSchedule FaceLandmark2DWeight = { 0.2f, 0.2f, EWeightScheduleCurve::Static };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Solve")` — How strongly 2D face landmark positions guide the face fit.
- L121 _public member_ `FWeightSchedule ModelRegularization = { 10.0f, 10.0f, EWeightScheduleCurve::Static };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Solve")` — Regularization strength for the face patch blend model. Higher = less face deformation.
- L125 _public member_ `FWeightSchedule PatchSmoothness = { 1.0f, 1.0f, EWeightScheduleCurve::Static };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Solve")` — Smoothness penalty for face patch deformation. Higher = smoother face patches.
- L128 _public member_ `float LandmarkDamping = 0.01f;` — `UPROPERTY(BlueprintReadWrite, Category = "Face Solve", meta = (ClampMin = "0", UIMax = "100"))`
- L132 _public member_ `bool bApplyNeckSeamSmoothing = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neck Seam")` — Apply neck seam smoothing after solve
- L136 _public member_ `int SeamIterations = 3;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neck Seam", meta = (ClampMin = "0", UIMax = "100"))` — Number of fitting passes for the neck seam. More = finer result but slower.
- L140 _public member_ `float SeamLaplacian = 1.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neck Seam", meta = (ClampMin = "0", UIMax = "100"))` — Laplacian smoothness regularization on vertex offsets for the neck seam.
- L144 _public member_ `int SeamRings = 12;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neck Seam", meta = (ClampMin = "0", UIMax = "100"))` — Number of rings around neck seam to apply smoothing over

#### struct `FRefinementSettings`  
`struct FRefinementSettings`  
_L148-192_
- reflection: `USTRUCT(BlueprintType)`
- L154 _public member_ `int Iterations = 5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refinement", meta = (ClampMin = "0", UIMax = "100"))` — Number of fitting passes. More = finer result but slower.
- L158 _public member_ `float VertexWeight = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refinement", meta = (ClampMin = "0", UIMax = "100"))` — Weight of the vertex position constraint relative to other constraints.
- L162 _public member_ `float KeypointWeight = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refinement", meta = (ClampMin = "0", UIMax = "100"))` — How strongly detected body keypoints (shoulders, hips, etc.) pull the rig into pose.
- L166 _public member_ `float Landmark2DWeight = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refinement", meta = (ClampMin = "0", UIMax = "100"))` — How strongly 2D face landmark positions guide the face fit.
- L170 _public member_ `float Laplacian = 0.8f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refinement", meta = (ClampMin = "0", UIMax = "100"))` — Laplacian smoothness regularization on vertex offsets.
- L174 _public member_ `float Bending = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refinement", meta = (ClampMin = "0", UIMax = "100"))` — Bending resistance for triangle mesh deformation.
- L178 _public member_ `float Strain = 0.135f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refinement", meta = (ClampMin = "0", UIMax = "100"))` — Strain regularization resisting stretching and compression.
- L182 _public member_ `float VertexOffsetReg = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refinement", meta = (ClampMin = "0", UIMax = "100"))` — Regularization penalizing the magnitude of per-vertex offsets.
- L186 _public member_ `float VertexRegularization = 3e-3f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refinement", meta = (ClampMin = "0", UIMax = "100"))` — Small regularization term on vertex variables for numerical stability.
- L190 _public member_ `float DistanceTolerance = 5.95f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refinement", meta = (ClampMin = "0", UIMax = "100"))` — Maximum distance (mm) to consider a scan point as a match. Ramps down each iteration for progressively tighter matching.

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Public/MetaHumanConformTargetParams.h` (Public)


#### enum `ETargetPartsType`  
`enum class ETargetPartsType : uint8`  
_L15-21_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `Combined`
- L18 _public enumerator_ `BodyOnly`
- L19 _public enumerator_ `HeadOnly`
- L20 _public enumerator_ `HeadAndBody`

#### struct `FTrackingPoints`  
`struct FTrackingPoints`  
_L24-30_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public member_ `TArray<FVector2D> TrackingPoints;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`

#### struct `FConformTargetMesh`  
`struct FConformTargetMesh`  
_L33-54_
- reflection: `USTRUCT(BlueprintType)`
- L38 _public member_ `ETargetPartsType TargetPartsType = ETargetPartsType::Combined;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L41 _public member_ `TArray<FVector3f> BodyVertices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L44 _public member_ `TArray<int32> BodyVertexIndices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L47 _public member_ `TArray<FVector3f> BodyJointRotations;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L50 _public member_ `TArray<FVector3f> HeadVertices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L53 _public member_ `TArray<int32> HeadVertexIndices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`

#### struct `FConformTargetParams`  
`struct FConformTargetParams`  
_L60-87_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct to contain parameters used to conform to a target
- L65 _public member_ `FConformTargetMesh ConformTargetMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L68 _public member_ `TMap<int32, FVector3f> KeyPointTargets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L71 _public member_ `TMap<FString, FTrackingPoints> CurveTrackingPoints;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L74 _public member_ `FMinimalViewInfo CameraViewInfo;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L77 _public member_ `FIntPoint ImageSize = FIntPoint::ZeroValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L80 _public member_ `bool bEstimateBodyJointsFromMesh = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L83 _public member_ `bool bAutoSolve = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L86 _public member_ `FBodyConformSolveSettings BodyConformSolveSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`

#### struct `FRefinementTargetParams`  
`struct FRefinementTargetParams`  
_L91-112_
- reflection: `USTRUCT(BlueprintType)`
- L96 _public member_ `FConformTargetMesh ConformTargetMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L99 _public member_ `TMap<int32, FVector3f> KeyPointTargets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L102 _public member_ `TMap<FString, FTrackingPoints> CurveTrackingPoints;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L105 _public member_ `FMinimalViewInfo CameraViewInfo;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L108 _public member_ `FIntPoint ImageSize = FIntPoint::ZeroValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L111 _public member_ `FRefinementSettings RefinementSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Public/MetaHumanConformer.h` (Public)


#### class `UE::Wrappers::FMetaHumanConformer`  
`class FMetaHumanConformer`  
_L26-275_
- desc: Brief@ FMetaHumanConformer is a wrapper class around core tech lib that provides conformed mesh i.e. identity fitting.
- L30 _public prototype_ `FMetaHumanConformer();`
- L39 _public prototype_ `bool Init(const FString& InTemplateDescriptionJson, const FString& InIdentityModelJson, const FString& InFittingConfigurationJson);` — Initialize face fitting. @param[in] InTemplateDescriptionJson  the flattened templated description json @param[in] InIdentityModelJson		 the flattened identity model json (dna database description) @param[in] InFittingConfigurationJson the fitting configuration json @returns True if initialization is successful, False otherwise.
- L49 _public prototype_ `bool SetDepthInputData(const TMap<FString, const FFrameTrackingContourData*>& InLandmarksDataPerCamera, const TMap<FString, const float*>& InDepthMaps);` — Set the depth input data for one frame. @param[in] InLandmarksDataPerCamera  The distorted landmarks for each camera. @param[in] InDepthMaps Depthmap data per (depthmap) camera. @returns True if setting the data was successful. @warning Fails if scan data was set before.
- L64 _public prototype_ `bool SetScanInputData(const TSortedMap<FString, const FFrameTrackingContourData*>& InLandmarks2DData, const TSortedMap<FString, const FTrackingContour3D*>& InLandmarks3DData, const TArray<int32_t>& InTrianlges, const TArray<float>& InVertices, bool& bOutInvalidMeshTopology);` — Set the scan input data. @param[in] InLandmarks2DData  The distorted 2D landmarks per camera view. @param[in] InLandmarks3DData  The distorted 3D landmarks. @param[in] InTrianlges  Input scan data with triangles stored as numTriangles x 3  in column major format. @param[in] InVertices  Input scan data with vertices as numVertices x 3 in column major format. @param[out] bOutInvalidMeshTopology  bOutInvalidMeshTopology Set to false if the mesh has a valid topology, true if all vertices on the input mesh are invalid eg due to all disconnected triangles @returns True if setting the data was successful. @warning Fails if depthmap data was set before.
- L74 _public prototype_ `bool SetCameras(const TArray<FCameraCalibration>& InCalibrations);`
- L88 _public prototype_ `EIdentityErrorCode FitIdentity(TArray<float>& OutVerticesFace, TArray<float>& OutVerticesLeftEye, TArray<float>& OutVerticesRightEye, TArray<float>& OutStackedToScanTransforms, TArray<float>& OutStackedToScanScales, bool bInFitEyes = false, const FString& InDebuggingDataFolder = {});` — Fit identity given input data. @param[out] OutVerticesFace: Vertex positions describing new identity face mesh as numVertices x 3 in column major format. @param[out] OutVerticesLeftEye: Vertex positions describing new identity left eye mesh as numVertices x 3 in column major format. @param[out] OutVerticesRightEye: Vertex positions describing new identity right eye mesh as numVertices x 3 in column major format. @param[out] Stacked rigid transforms, one for each input depth map (this will be 1 for a single mesh) containing 16 float values per transform @params[out] Stacked scales, one for each input depth map (this will be 1 value for a single mesh) @params[in] bInFitEyes, a bool if set to true, fit the eye meshes during conformation, if false, don't fit the eye meshes (which will be empty on output) @params[in] InDebuggingDataFolder, a string containing a debugging folder to save to. If not empty, tries to save debugging data including all input data (camera calib json, landmarks json, reference images, depth maps as images and objs, and also results of eye fitting as objs if this is enabled. @returns an error code which described whether the fitting was successful and what went wrong if it failed
- L97 _public prototype_ `bool FitTeeth(TArray<float>& OutVerticesTeeth, const FString& InDebuggingDataFolder = {});` — Update teeth model and position in the rig given input data. @param[out] Vertex positions describing updated identity face mesh as numVertices x 3 in column major format. @params[in] InDebuggingDataFolder, a string containing a debugging folder to save to. If not empty, tries to save debugging data including all input data (camera calib json, landmarks json, reference images, depth maps as images and objs, and also results of teeth fitting as obj. @returns True if fitting and DNA update was successful.
- L103 _public prototype_ `bool ResetInputData();` — Clears previous configuration. @returns True if successful.
- L113 _public prototype_ `bool GenerateBrowMeshLandmarks(const FString& InCameraName, TArray<uint8>& OutJsonStream, float & OutFractionLandmarksInBrowRegion, bool bInConcatenate = false) const;` — Projects brow target landmarks to fitted mesh. Outputs brows projected to mesh as mesh landmarks. @param[in]  InCameraName  Which camera landmarks to use for projection. @param[out] OutJsonStream  Serialized json containing all mesh landmarks. @param[out] OutFractionLandmarksInBrowRegion  The fraction of brow landmarks in the brow region when projected onto the face mesh. @param[in]  bInConcatenate  Should OutJsonStream contain just projected brow landmarks (false), or to concatenate with all mesh landmarks (true). @returns True if brow landmarks are generated successfully.
- L123 _public prototype_ `static bool CalculatePcaModelFromDnaRig(const FString& InConfigurationJson, const TArray<uint8>& InDNA, TArray<uint8>& OutPCARigMemoryBuffer, const FString& InDebuggingDataFolder = {});` — Creates a PCA rig out of input DNA RigLogic rig. @param[in] InConfigurationJson  A json string containing the config to convert from DNA to PCA model @param[in] InDNA  Input DNA containing RigLogic rig. @param[out] OutPCARigMemoryBuffer  Output block of memory for the PCA rig @params[in] InDebuggingDataFolder, a string containing a debugging folder to save to. If not empty, tries to save debugging data which in this case is the fitted face mesh as face_fitted.obj @returns True if calculation of the PCA rig was successful
- L131 _public prototype_ `bool UpdateTeethSource(const TArray<uint8>& InDNA);` — Update the teeth source for the conformer from the supplied DNA @param[in] InDNA  Input DNA. @returns True if update happened successfully
- L142 _public prototype_ `bool CalcTeethDepthDelta(float InDeltaDistanceFromCamera, float& OutDx, float& OutDy, float& OutDz);` — Calculate the offset in *RIG COORDINATE SPACE* to move the teeth a distance InDeltaDistanceFromCamera away from the first (1st) camera. Assumes FitTeeth has been called. @param[out] OutDx delta x for teeth in *RIG COORDINATE SPACE*. @param[out] OutDy delta y for teeth in *RIG COORDINATE SPACE*. @param[out] OutDz delta z for teeth in *RIG COORDINATE SPACE*. @param[in] InDeltaDistanceFromCamera The distance in cm to move the current teeth away from the camera position. @returns True if fitting was successful.
- L151 _public prototype_ `static bool CheckPcaModelFromDnaRigConfig(const FString& InConfigurationJson, UDNAAsset* InDNAAsset);` — `UE_DEPRECATED(5.8, "Use CheckPcaModelFromDnaRigConfig that's accepting DNAReader instead, DNAAsset as asset user data has been deprecated.")` — Check that the supplied PCA from DNA rig config is valid. @param[in] InConfigurationJson  Path to pca from dna configuration file or Json string containing the config. @param[in] InDNAAsset  An example DNA asset to be used with the config. @returns True if the config is valid, false otherwise
- L159 _public prototype_ `static bool CheckPcaModelFromDnaRigConfig(const FString& InConfigurationJson, TSharedPtr<IDNAReader> InDNAReader);` — Check that the supplied PCA from DNA reader rig config is valid. @param[in] InConfigurationJson  Path to pca from dna configuration file or Json string containing the config. @param[in] InDNAReader  An example DNA reader to be used with the config. @returns True if the config is valid, false otherwise
- L168 _public prototype_ `static bool CalculatePcaModelFromDnaRig(const FString& InConfigurationFilename, const FString& InDNAFilename, TArray<uint8>& OutPCARigMemoryBuffer);` — Creates a PCA rig out of input DNA RigLogic rig. @param[in] InConfigurationFilename  Path to pca from dna configuration file. @param[in] InDNAFilename  Path to input DNA rig file. @param[out] OutPCARigMemoryBuffer  Output block of memory for the PCA rig @returns True if calculation of the PCA rig was successful
- L178 _public prototype_ `bool FitRigid(TArray<float> &OutVerticesFace, TArray<float>& OutStackedToScanTranform, TArray<float>& OutStackedToScanScale, int32 InIterations);` — Fit identity given input data. @param[out] OutVerticesFace  Vertex positions describing new identity as numVertices x 3 in column major format placed in *RIG COORDINATE SPACE*. @param[out] OutStackedToScanTransforms  Stacked 4x4 transform matrices in column major format. @param[out] OutStackedToScanScales  Stacked scale values. Scale is not a linear part of ToScanTransform, and needs to be applied after the transformation. @param[in] InNumIters  Number of iterations of the optimization. @returns True if fitting was successful.
- L190 _public prototype_ `bool FitPcaRig(const TArray<uint8>& InPcaRig, const TArray<uint8>& InNeutralDNABuffer, TArray<float>& OutVerticesFace, TArray<float>& OutStackedToScanTranform, TArray<float>& OutStackedToScanScale, const FString& InDebuggingDataFolder = {});` — Fit expression using PCA rog given input data. @param[in] InPcaRig  Input DNA -must be PCA rig- to be used as deformable model to fit the expression. @param[in] InNeutralDNABuffer  the DNA for the neutral pose @param[out] OutVertexPositions  Vertex positions describing new identity as numVertices x 3 in column major format placed in *RIG COORDINATE SPACE*. @param[out] OutStackedToScanTransforms  Stacked 4x4 transform matrices in column major format. @param[out] OutStackedToScanScales  Stacked scale values. Scale is not a linear part of ToScanTransform, and needs to be applied after the transformation. @params[in] InDebuggingDataFolder, a string containing a debugging folder to save to. If not empty, tries to save debugging data which in this case is the fitted face mesh as face_fitted.obj @returns True if fitting was successful.
- L199 _public prototype_ `bool UpdateRigWithTeethMeshVertices(const TArray<uint8>& InDNA, const TArray<float>& InVertices, TArray<uint8>& OutDNA);` — Update teeth model and position in the rig given input data. @param[in] InDNA  Input DNA. @param[in] InVertices  Input target vertex positions - Teeth mesh vertices - as numVertices x 3 in column major order.. @param[out] OutDna  Updated dna. @returns True if fitting and DNA update was successful.
- L206 _public prototype_ `bool SetModelRegularization(float InValue);` — Set regularization for non-rigid fitting. @param[in] regularization multiplier @returns True if successful.
- L215 _public prototype_ `bool ApplyDeltaDNA(const TArray<uint8>& InRawDNABuffer, const TArray<uint8>& InRawDeltaDNABuffer, TArray<uint8>& OutRawCombinedUnscaledDNABuffer) const;` — Apply the supplied delta DNA to the DNA, and then scale the output about the scaling pivot position, and return in the output buffer. @param[in] InRawDNABuffer  The input base DNA supplied as a raw block of memory. @param[in] InRawDeltaDNABuffer  The input delta DNA supplied as a raw block of memory. @param[out] OutRawCombinedUnscaledDNABuffer  Output block of memory for the combined DNA (but not scaled to metric scale). @returns True if calculation of the combined DNA rig was successful, false otherwise
- L226 _public prototype_ `bool ApplyScaleToDNA(const TArray<uint8>& InRawDNABuffer, float InScale, const FVector& InScalingPivot, TArray<uint8>& OutRawScaledDNABuffer) const;` — Scale the supplied input DNA about the scaling pivot position, and return in the output buffer. @param[in] InRawDNABuffer  The input  DNA supplied as a raw block of memory. @param[in] InScale  The scaling factor to apply. @param[in] InScalingPivot  The input delta DNA supplied as a raw buffer of data. @param[out] OutRawScaledDNABuffer  Output block of memory for the scaled DNA. @returns True if calculation of the scaled DNA rig was successful, false otherwise
- L236 _public prototype_ `bool TransformRigOrigin(const TArray<uint8>& InRawDNABuffer, const FMatrix44f& InTransformMatrix, TArray<uint8>& OutTransformedDNABuffer) const;` — Apply the supplied rigid transform to the input DNA, and and return in the output buffer. @param[in] InRawDNABuffer  The input DNA supplied as a raw block of memory. @param[in] InTransformMatrix  The transform matrix to apply. The transform matrix should be supplied in OpenCV coordinate system. @param[out] OutTransformedDNABuffer  Output block of memory for the transformed DNA. @returns True if calculation of the transformed DNA rig was successful, false otherwise
- L244 _public prototype_ `static TArray<uint8> DNAToBuffer(UDNAAsset* InDNAAsset);` — `UE_DEPRECATED(5.8, "Use DNAToBuffer that's accepting DNAReader instead, DNAAsset as asset user data has been deprecated.")` — Converts a DNA asset into a byte array. @param[in] InDNAAsset  DNA asset. @returns The byte array
- L252 _public prototype_ `static TArray<uint8> DNAToBuffer(TSharedPtr<IDNAReader> InDNAReader);` — Converts a DNA reader into a byte array. @param[in] InDNAReader  DNA reader. @returns The byte array
- L259 _public prototype_ `bool CheckControlsConfig(const FString& InControlsConfigJson) const;` — Check that the supplied json string for the controls config is valid. @param[in] InControlsConfigJson: the json config defining the set of shapes which help position the teeth without intersecting the mesh @returns True if controls config json is valid, false otherwise
- L269 _public prototype_ `bool RefineTeethPlacement(const FString& InControlsConfigJson, const TArray<uint8>& InRawDNAPlusDeltaDNABuffer, const TArray<uint8>& InRawDNABuffer, TArray<uint8>& OutRawRefinedDNAPlusDeltaDNABuffer) const;` — Refine the teeth placement provided as output from the autorigging service so that they are in a better starting position @param[in] InControlsConfigJson: the json config defining the set of shapes which help position the teeth without intersecting the mesh @param[in] InRawDNAPlusDeltaDNABuffer: a buffer containing the raw DNA plus delta DNA from the autorigging service (unscaled) @param[in] InRawDNABuffer: a buffer containing the raw DNA returned from the autorigging service (to be used as reference) @param[out] OutRawRefinedDNAPlusDeltaDNABuffer: a buffer containing a refined version of InDNAPlusDeltaDNABuffer with the teeth in a better position @returns True if calculation of DNA with refined teeth placement was successful, false otherwise
- L273 _private member_ `TPimplPtr<Private> Impl;`
- L274 _private member_ `FCriticalSection AccessMutex;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METAHUMANCORETECHLIB_API`
- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Wrappers` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Public/MetaHumanCoreTechLibGlobals.h` (Public)


#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCoreTechLib, Log, All);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Public/MetaHumanCoreTechLibVersion.h` (Public)


#### struct `FMetaHumanCoreTechLibVersion`  
`struct FMetaHumanCoreTechLibVersion`  
_L10-14_
- desc: Version for TitanLib
- L13 _public prototype_ `static FString GetMetaHumanCoreTechLibVersionString();` — Returns the Titan Lib version as a string

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API METAHUMANCORETECHLIB_API`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Public/MetaHumanCoreTechMeshUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCORETECHLIB_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MetaHuman` (scope `UE`)
- L21 _prototype_ `TArray<TPair<int32, float>> GetClosestUVIndices(const TArray<FVector2f>& InMeshUVs, const TArray<FVector2f>& InInputUVs);` (scope `UE::MetaHuman`) — For each InInputUVs, find the closest UV from the InMeshUVs and return the index and distance in UV space from it @param[in] InMeshUVs Mesh UVs to be searched within @param[in] InInputUVs Array of UVs. For each UV, finds the closest UV in InMeshUVs and returns it's index @returns Returns the index of corresponding UV in InMeshUVs and distance to UV for each input UV in InInputUVs
- L23 _prototype_ `TMap<int32, TArray<int32>> GetNeighbouringVertices(const TSharedPtr<IDNAReader>& InDNAReader, int32 InDNAMeshIndex, const TArray<int32>& InVertexIds);` (scope `UE::MetaHuman`)
- L25 _prototype_ `TArray<FVector3f> GetJointWorldTranslations(const TSharedPtr<IDNAReader>& InDNAReader);` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Public/MetaHumanEvaluateRig.h` (Public)


#### class `UE::Wrappers::FMetaHumanEvaluateRig`  
`class FMetaHumanEvaluateRig`  
_L19-101_
- desc: Brief@ FMetaHumanEvaluateRig is a wrapper class around core tech lib which allows evaluation of rig raw controls, and returns the vertices for user-specified mesh(es)
- L26 _public prototype_ `FMetaHumanEvaluateRig();` — Default constructor
- L33 _public prototype_ `bool SetRigDNA(UDNA* InDNA);` — Set the DNA of the rig to be evaluated @param[in] InDNA: the UDNA asset containing the rig to be evaluated @returns true if the DNA is set successfully, false otherwise
- L42 _public prototype_ `bool SetRigDNA(UDNAAsset* InDNAAsset);` — `UE_DEPRECATED(5.8, "Use SetRigDNA(UDNA*) instead")` — Set the DNA of the rig to be evaluated (deprecated - use UDNA instead) @param[in] InDNAAsset: the legacy DNAAsset containing the rig to be evaluated @returns true if the DNAAsset is set successfully, false otherwise @deprecated Use SetRigDNA(UDNA*) instead
- L48 _public prototype_ `bool IsRigDNASet() const;` — Return whether the rig DNA has been set for the class @returns true if the rig DNA has been set, false otherwise
- L59 _public prototype_ `bool EvaluateRawControls(const TMap<FString, float>& InControls, const TArray<int> & InMeshIndices, int32 InLod, TArray<TArray<FVector>>& OutMeshVertices) const;` — Evaluate the supplied map of raw controls, and return the evaluated mesh vertices for the specified mesh indices. Rig must have been set using SetRigDNA. @param[in] InControls: a map of raw control name to control value. Additional controls will be ignored; missing controls will be set to 0. Control names should use the control names used in MH Animation sequences ie CTRL_expressions_ rather than CTRL_expressions. @param[in] InMeshIndices: an array of mesh indices for which we want to evaluate the vertices. Mesh Indices must be in the range 0-GetNumMeshes()-1 @param[in] InLod: the lod to evaluate the vertices for, which must be >=0 and < GetNumLods() @param[out] OutMeshVertices: an array of array of vector. Each array contains the evaluated vertices for the specified mesh index. @returns true if evaluated successfully, false otherwise
- L66 _public prototype_ `bool GetNumMeshes(int32& OutNumMeshes) const;` — Get the number of meshes for the rig DNA. Rig must have been set using SetRigDNA. @param[out] OutNumMeshes: contains the number of meshes for the rig DNA. @returns true if evaluated successfully, false otherwise
- L73 _public prototype_ `bool GetNumLODs(int32& OutNumLods) const;` — Get the number of lods for the rig DNA. Rig must have been set using SetRigDNA. @param[out] OutNumLods: contains the number of lods for the rig DNA. @returns true if evaluated successfully, false otherwise
- L81 _public prototype_ `bool GetMeshIndex(const FString& InMeshName, int32& OutMeshIndex) const;` — Get the mesh index for the specified mesh name for the rig DNA. Rig must have been set using SetRigDNA. @param[in] InMeshName: the mesh name. Must be a valid mesh name for the rig. @param[out] OutMeshIndex: contains the corresponding mesh index for the mesh name. @returns true if evaluated successfully, false otherwise
- L88 _public prototype_ `bool GetRawControlNames(TArray<FString>& OutRawControlNames)const;` — Get the raw control names for the rig DNA. Rig must have been set using SetRigDNA. @param[out] OutRawControlNames: contains the control names @returns true if evaluated successfully, false otherwise
- L95 _public prototype_ `bool GetMeshNames(TArray<FString>& OutMeshNames)const;` — Get the mesh names for the rig DNA. Rig must have been set using SetRigDNA. @param[out] OutMeshNames: contains the mesh names @returns true if evaluated successfully, false otherwise
- L100 _private member_ `TPimplPtr<Private> Impl;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCORETECHLIB_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Wrappers` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Public/MetaHumanFaceTextureSynthesizer.h` (Public)


#### class `FMetaHumanFaceTextureSynthesizer`  
`class FMetaHumanFaceTextureSynthesizer`  
_L17-155_
- desc: UE API for creating MH Face textures based on the Texture Synthesis module feature set developed in titan
- L21 _public prototype_ `FMetaHumanFaceTextureSynthesizer();`
- L22 _public function_ `~FMetaHumanFaceTextureSynthesizer()`
- L27 _public prototype_ `FMetaHumanFaceTextureSynthesizer(const FMetaHumanFaceTextureSynthesizer& InOther) = delete;`
- L34 _public prototype_ `bool Init(const FString& InTextureSynthesisFolderPath, int32 InNumThreads = 0);` — Initialize the Texture Synthesis object by loading all the necessary model data from the MetaHumanCharacter content InTextureSynthesisFolderPath should point to a folder with the texture synthesis model data as used by the UE data loader InNumThreads is the number of threads to use for each texture synthesis map, pass 0 for single thread synthesis
- L39 _public prototype_ `bool IsValid() const;` — Returns whether the Texture Synthesis object has been initialized and the internal model data are valid
- L44 _public prototype_ `void Clear();` — Releases any memory allocated by the Texture Synthesis object
- L49 _public prototype_ `int32 GetMaxHighFrequencyIndex() const;` — Get the maximum value for the HF index the model supports
- L54 _public prototype_ `int32 GetTextureSizeX() const;` — Size of the generated Textures along the first dimension
- L59 _public prototype_ `int32 GetTextureSizeY() const;` — Size of the generated Textures along the second dimension
- L64 _public prototype_ `ERawImageFormat::Type GetTextureFormat() const;` — Image format of the generated textures
- L69 _public prototype_ `EGammaSpace GetTextureColorSpace() const;` — Color space of the generated textures
- L85 _public prototype_ `TArray<EMapType> GetSupportedAlbedoMapTypes() const;` — Returns the albedo map types that can be synthesized by this model (without input HF maps)
- L90 _public prototype_ `TArray<EMapType> GetSupportedNormalMapTypes() const;` — Returns the normal map types that can be selected by this model
- L106 _public prototype_ `FLinearColor GetSkinTone(const FVector2f& InUV) const;` — Gets the Skin Tone for a given Skin UV value @returns Color in sRGB space
- L114 _public prototype_ `FVector2f ProjectSkinTone(const FLinearColor& InSkinTone, const int HFIndex) const;` — Projects a skin tone to the texture model and returns the Skin UV Value The returned UV value is clamped to [0,1] if the input skin tone is projected outside the bounds what the texture model can represent. @param InSkinTone the skin tone to project in sRGB space.
- L120 _public prototype_ `FVector3f GetBodyAlbedoGain(const FVector2f& InUV) const;` — Gets the body albedo gain for a given Skin UV value @returns Albedo gain
- L126 _public prototype_ `bool SynthesizeAlbedo(const FTextureSynthesisParams& InTextureSynthesisParams, FImageView OutAlbedoImage) const;` — Synthesize an albedo texture map with the input parameters and store in the passed ImageView object OutAlbedoImage should be pre-allocated with the appropriate size and format
- L132 _public prototype_ `bool SynthesizeAlbedoWithHF(const FTextureSynthesisParams& InTextureSynthesisParams, const TStaticArray<TArray<uint8>, 4>& InHFMaps, FImageView OutAlbedoImage) const;` — Synthesize an albedo texture map using the input HF maps OutAlbedoImage should be pre-allocated with the same target resolution of the input HFMap and this model output format
- L138 _public prototype_ `bool SelectNormal(const FTextureSynthesisParams& InTextureSynthesisParams, FImageView OutNormalImage) const;` — Select a normal texture map based on the input parameters OutNormalImage should be pre-allocated with the appropriate size and format
- L144 _public prototype_ `bool SelectCavity(int32 HighFrequencyIndex, FImageView OutCavityImage) const;` — Select the cavity texture map to be used for this HF index OutCavityImage should be pre-allocated with the appropriate size and format
- L150 _public prototype_ `const FMetaHumanFaceTextureAttributeMap& GetFaceTextureAttributeMap() const;` — Gets the texture attribute map associated with the face texture synthesizer.
- L154 _private member_ `TPimplPtr<FImpl> Impl;`

#### enum `FMetaHumanFaceTextureSynthesizer::EMapType`  
`enum class EMapType : int32`  
_L74-80_
- desc: Enum with indices corresponding to the TS model supported maps
- L76 _public enumerator_ `Base = 0`
- L77 _public enumerator_ `Animated0 = 1`
- L78 _public enumerator_ `Animated1 = 2`
- L79 _public enumerator_ `Animated2 = 3`

#### struct `FMetaHumanFaceTextureSynthesizer::FTextureSynthesisParams`  
`struct FTextureSynthesisParams`  
_L95-100_
- desc: Parameters for synthesizing a texture from the model
- L97 _public member_ `FVector2f SkinUVFromUI;` — UV skin coordinates, as defined in the MHC UI
- L98 _public member_ `int32 HighFrequencyIndex;` — Index to the HF map
- L99 _public member_ `EMapType MapType;` — Index to one of the supported map types

#### class `FMetaHumanFaceTextureAttributeMap`  
`class FMetaHumanFaceTextureAttributeMap`  
_L158-180_
- L161 _public prototype_ `bool Init(const FString& InTextureSynthesisFolderPath, int32 NumTextures);`
- L163 _public function_ `int32 NumAttributes() const`
- L165 _public prototype_ `const FString& GetAttributeName(int32 Idx) const;`
- L167 _public prototype_ `const TArray<FString>& GetAttributeValueNames(int32 Idx) const;`
- L169 _public prototype_ `const TArray<int32>& GetAttributeValues(int32 Idx) const;`
- L171 _public function_ `const TArray<int32>& GetAllIndices() const`
- L173 _public prototype_ `TArray<int32> Filter(int32 AttributeIndex, int32 AttributeValue, const TArray<int32>& InIndices) const;`
- L176 _private member_ `TArray<FString> AttributeNames;`
- L177 _private member_ `TArray<TArray<FString>> AttributeValueNames;`
- L178 _private member_ `TArray<TArray<int32>> AttributeValues;`
- L179 _private member_ `TArray<int32> AllIndices;`

#### class `FMetaHumanFilteredFaceTextureIndices`  
`class FMetaHumanFilteredFaceTextureIndices`  
_L183-196_
- L186 _public prototype_ `FMetaHumanFilteredFaceTextureIndices(const FMetaHumanFaceTextureAttributeMap& FaceTextureAttributeMap, const TArray<int32>& AttributeValues);`
- L188 _public function_ `int32 Num() const`
- L190 _public prototype_ `int32 ConvertTextureIndexToFilterIndex(int32 TextureIndex) const;`
- L192 _public prototype_ `int32 ConvertFilterIndexToTextureIndex(int32 FilterIndex) const;`
- L195 _private member_ `TArray<int32> Indices;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCORETECHLIB_API`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Public/MetaHumanIdentityErrorCode.h` (Public)


#### enum `EIdentityErrorCode`  
`enum class EIdentityErrorCode : uint8`  
_L8-41_
- reflection: `UENUM()`
- L10 _public enumerator_ `None = 0`
- L11 _public enumerator_ `MLRig`
- L12 _public enumerator_ `CreateRigFromDNA`
- L13 _public enumerator_ `LoadBrows`
- L14 _public enumerator_ `NoDNA`
- L15 _public enumerator_ `NoTemplate`
- L16 _public enumerator_ `CreateDebugFolder`
- L17 _public enumerator_ `CalculatePCAModel`
- L18 _public enumerator_ `Initialization`
- L19 _public enumerator_ `CameraParameters`
- L20 _public enumerator_ `ScanInput`
- L21 _public enumerator_ `DepthInput`
- L22 _public enumerator_ `TeethSource`
- L23 _public enumerator_ `FitRigid`
- L24 _public enumerator_ `FitPCA`
- L25 _public enumerator_ `FitTeethFailed`
- L26 _public enumerator_ `TeethDepthDelta`
- L27 _public enumerator_ `UpdateRigWithTeeth`
- L28 _public enumerator_ `InvalidDNA`
- L29 _public enumerator_ `ApplyDeltaDNA`
- L30 _public enumerator_ `RefineTeeth`
- L31 _public enumerator_ `ApplyScaleToDNA`
- L32 _public enumerator_ `NoPart`
- L33 _public enumerator_ `InCompatibleDNA`
- L34 _public enumerator_ `CaptureDataInvalid`
- L35 _public enumerator_ `SolveFailed`
- L36 _public enumerator_ `BrowsFailed`
- L37 _public enumerator_ `NoPose`
- L38 _public enumerator_ `FitEyesFailed`
- L39 _public enumerator_ `BadInputMeshTopology`
- L40 _public enumerator_ `BrowsProjectionWarning`

#### enum `EAutoRigIdentityValidationError`  
`enum class EAutoRigIdentityValidationError : uint8`  
_L50-58_
- reflection: `UENUM()`
- L52 _public enumerator_ `None = 0`
- L53 _public enumerator_ `BodyNotSelected`
- L54 _public enumerator_ `BodyIndexInvalid`
- L55 _public enumerator_ `EmptyConformalMesh`
- L56 _public enumerator_ `MeshNotConformed`
- L57 _public enumerator_ `NoFacePart`

#### Free symbols / members of external scopes

- L44 _function_ `constexpr bool IsIdentityErrorCodeWarningOnly(EIdentityErrorCode InIdentityErrorOrWarning)` — a helper function which distinguishes warnings from errors for the enum above

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTechLib/Public/MetaHumanRigEvaluatedState.h` (Public)


#### struct `FMetaHumanRigEvaluatedState`  
`struct FMetaHumanRigEvaluatedState`  
_L11-15_
- desc: Helper struct to contain evaluated state for either the face or the body model
- L13 _public member_ `TArray<FVector3f> Vertices;`
- L14 _public member_ `TArray<FVector3f> VertexNormals;`
