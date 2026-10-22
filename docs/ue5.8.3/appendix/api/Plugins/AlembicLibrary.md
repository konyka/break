# Plugins / AlembicLibrary

- module root: `Plugins/Importers/AlembicImporter/Source/AlembicLibrary`
- headers: 14; symbols: 440
- symbol kinds: class=15, enum=8, enumerator=33, function=44, macro=6, member=163, namespace=11, prototype=148, struct=10, typedef=1, variable=1
- PrivateDependencyModuleNames: EditorFramework, MeshDescription, StaticMeshDescription
- PublicDependencyModuleNames: AlembicLib, Core, CoreUObject, Eigen, Engine, GeometryCache, Imath, InputCore, MaterialUtilities, MeshUtilities, PropertyEditor, RHI, RenderCore, Slate, SlateCore, UnrealEd

### `Plugins/Importers/AlembicImporter/Source/AlembicLibrary/Private/AbcImportSettingsCustomization.h` (Private)


#### class `FAbcImportSettingsCustomization`  
`class FAbcImportSettingsCustomization : public IDetailCustomization`  
_L12-27_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& LayoutBuilder) override;` — Begin IDetailCustomization interface
- L21 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Creates a new instance.
- L23 _protected prototype_ `void OnImportTypeChanged(IDetailLayoutBuilder* LayoutBuilder);`
- L26 _protected member_ `UAbcImportSettings* ImportSettings;`

#### class `FAbcSamplingSettingsCustomization`  
`class FAbcSamplingSettingsCustomization : public IPropertyTypeCustomization`  
_L30-49_
- inherits: `IPropertyTypeCustomization`
- desc: AbcSampling settings customizations handles hiding/showing properties according to the frame sampling type
- L34 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L36 _public function_ `FAbcSamplingSettingsCustomization()`
- L39 _public prototype_ `virtual ~FAbcSamplingSettingsCustomization() = default;`
- L42 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override` — Begin IPropertyTypeCustomization interface
- L43 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L47 _protected prototype_ `EVisibility ArePropertiesVisible(const int32 VisibleType) const;`
- L48 _protected member_ `TSharedPtr<IPropertyHandle> SamplingTypeHandle;`

#### class `FAbcCompressionSettingsCustomization`  
`class FAbcCompressionSettingsCustomization : public IPropertyTypeCustomization`  
_L52-71_
- inherits: `IPropertyTypeCustomization`
- desc: AbcCompression settings customizations handles hiding/showing properties according to the base calculation type
- L56 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L58 _public function_ `FAbcCompressionSettingsCustomization()`
- L61 _public prototype_ `virtual ~FAbcCompressionSettingsCustomization() = default;`
- L64 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override` — Begin IPropertyTypeCustomization interface
- L65 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L69 _protected prototype_ `EVisibility ArePropertiesVisible(const int32 VisibleType) const;`
- L70 _protected member_ `TSharedPtr<IPropertyHandle> BaseCalculationTypeHandle;`

#### class `FAbcConversionSettingsCustomization`  
`class FAbcConversionSettingsCustomization : public IPropertyTypeCustomization`  
_L73-92_
- inherits: `IPropertyTypeCustomization`
- L77 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L79 _public function_ `FAbcConversionSettingsCustomization() : Settings(nullptr)`
- L80 _public prototype_ `virtual ~FAbcConversionSettingsCustomization() = default;`
- L83 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override` — Begin IPropertyTypeCustomization interface
- L84 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L88 _protected prototype_ `void OnConversionPresetChanged();`
- L89 _protected prototype_ `void OnConversionValueChanged();`
- L91 _protected member_ `struct FAbcConversionSettings* Settings;`

### `Plugins/Importers/AlembicImporter/Source/AlembicLibrary/Private/AbcImportUtilities.h` (Private)


#### enum `ESampleReadFlags`  
`enum class ESampleReadFlags : uint8`  
_L38-48_
- L40 _public enumerator_ `Default = 0`
- L41 _public enumerator_ `Positions = 1 << 1`
- L42 _public enumerator_ `Indices = 1 << 2`
- L43 _public enumerator_ `UVs = 1 << 3`
- L44 _public enumerator_ `Normals = 1 << 4`
- L45 _public enumerator_ `Colors = 1 << 5`
- L46 _public enumerator_ `MaterialIndices = 1 << 6`
- L47 _public enumerator_ `Velocities = 1 << 7`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace Alembic`
- L24 _namespace_ `namespace Abc` (scope `Alembic`)
- L24 _namespace_ `namespace v12` (scope `Alembic::Abc`)
- L25 _namespace_ `namespace Alembic`
- L25 _namespace_ `namespace AbcCoreAbstract` (scope `Alembic`)
- L25 _namespace_ `namespace v12` (scope `Alembic::AbcCoreAbstract`)
- L26 _namespace_ `namespace Alembic`
- L26 _namespace_ `namespace AbcGeom` (scope `Alembic`)
- L26 _namespace_ `namespace v12` (scope `Alembic::AbcGeom`)
- L49 _prototype_ `ENUM_CLASS_FLAGS(ESampleReadFlags);`
- L51 _namespace_ `namespace AbcImporterUtilities`
- L54 _function_ `template<typename T> bool IsType(const Alembic::Abc::MetaData& MetaData)` (scope `AbcImporterUtilities`) — Templated function to check whether or not an object is of a certain type
- L65 _prototype_ `FMatrix ConvertAlembicMatrix(const Alembic::Abc::M44d& AbcMatrix);` (scope `AbcImporterUtilities`) — ConvertAlembicMatrix, converts Abc(Alembic) matrix to UnrealEngine matrix format @param AbcMatrix - Alembic style matrix @return FMatrix
- L67 _prototype_ `uint32 GenerateMaterialIndicesFromFaceSets(Alembic::AbcGeom::IPolyMeshSchema &Schema, const Alembic::Abc::ISampleSelector FrameSelector, TArray<int32> &MaterialIndicesOut);` (scope `AbcImporterUtilities`)
- L69 _prototype_ `void RetrieveFaceSetNames(Alembic::AbcGeom::IPolyMeshSchema &Schema, TArray<FString>& NamesOut);` (scope `AbcImporterUtilities`)
- L71 _function_ `template<typename T, typename U> bool RetrieveTypedAbcData(T InSampleDataPtr, TArray<U>& OutDataArray )` (scope `AbcImporterUtilities`)
- L100 _function_ `template<typename T> void ExpandVertexAttributeArray(const TArray<uint32>& InIndices, TArray<T>& InOutArray)` (scope `AbcImporterUtilities`) — Expands the given vertex attribute array to not be indexed
- L115 _prototype_ `void TriangulateIndexBuffer(const TArray<uint32>& InFaceCounts, TArray<uint32>& InOutIndices);` (scope `AbcImporterUtilities`) — Triangulates the given index buffer (assuming incoming data is quads or quad/triangle mix)
- L118 _function_ `template<typename T> void TriangulateVertexAttributeBuffer(const TArray<uint32>& InFaceCounts, TArray<T>& InOutData)` (scope `AbcImporterUtilities`) — Triangulates the given (non-indexed) vertex attribute data buffer (assuming incoming data is quads or quad/triangle mix)
- L156 _function_ `template<typename T> void ExpandPrimitiveAttributeArray(const TArray<uint32>& InFaceCounts, TArray<T>& InOutArray)` (scope `AbcImporterUtilities`)
- L196 _function_ `template<typename T> void ProcessVertexAttributeArray(const TArray<uint32>& InIndices, const TArray<uint32>& InFaceCounts, const bool bTriangulation, const uint32 NumVertices, TArray<T>& InOutArray)` (scope `AbcImporterUtilities`)
- L216 _prototype_ `void TriangulateMaterialIndices(const TArray<uint32>& InFaceCounts, TArray<int32>& InOutData);` (scope `AbcImporterUtilities`) — Triangulates material indices according to the face counts (quads will have to be split up into two faces / material indices)
- L219 _function_ `template<typename T> Alembic::Abc::ISampleSelector GenerateAlembicSampleSelector(const T SelectionValue)` (scope `AbcImporterUtilities`)
- L226 _prototype_ `FAbcMeshSample* GenerateAbcMeshSampleForFrame(const Alembic::AbcGeom::IPolyMeshSchema& Schema, const Alembic::Abc::ISampleSelector FrameSelector, const ESampleReadFlags ReadFlags, const bool bFirstFrame = false);` (scope `AbcImporterUtilities`) — Generates the data for an FAbcMeshSample instance given an Alembic PolyMesh schema and frame index
- L229 _prototype_ `ESampleReadFlags GenerateAbcMeshSampleReadFlags(const Alembic::AbcGeom::IPolyMeshSchema& Schema);` (scope `AbcImporterUtilities`) — Generates a sample read bit mask to reduce unnecessary reads / memory allocations
- L233 _prototype_ `void GenerateSmoothingGroups(TMultiMap<uint32, uint32> &TouchingFaces, const TArray<FVector3f>& FaceNormals, TArray<uint32>& FaceSmoothingGroups, uint32& HighestSmoothingGroup, const float HardAngleDotThreshold);` (scope `AbcImporterUtilities`) — Generated smoothing groups based on the given face normals, will compare angle between adjacent normals to determine whether or not an edge is hard/soft and calculates the smoothing group information with the edge data
- L237 _prototype_ `bool GenerateAbcMeshSampleDataForFrame(const Alembic::AbcGeom::IPolyMeshSchema &Schema, const Alembic::Abc::ISampleSelector FrameSelector, FAbcMeshSample* &Sample, const ESampleReadFlags ReadFlags, const bool bFirstFrame );` (scope `AbcImporterUtilities`) — Generates AbcMeshSample with given parameters and schema
- L240 _prototype_ `void ReadUVSetData(Alembic::AbcGeom::IV2fGeomParam &UVCoordinateParameter, const Alembic::Abc::ISampleSelector FrameSelector, TArray<FVector2f>& OutUVs, const TArray<uint32>& MeshIndices, const bool bNeedsTriangulation, const TArray<uint32>& FaceCounts, const int32 NumVertices);` (scope `AbcImporterUtilities`) — Read out texture coordinate data from Alembic GeometryParameter
- L242 _prototype_ `void GenerateSmoothingGroupsIndices(FAbcMeshSample* MeshSample, float HardEdgeAngleThreshold);` (scope `AbcImporterUtilities`)
- L244 _prototype_ `void CalculateNormals(FAbcMeshSample* Sample);` (scope `AbcImporterUtilities`)
- L246 _prototype_ `void CalculateSmoothNormals(FAbcMeshSample* Sample);` (scope `AbcImporterUtilities`)
- L248 _prototype_ `void CalculateNormalsWithSmoothingGroups(FAbcMeshSample* Sample, const TArray<uint32>& SmoothingMasks, const uint32 NumSmoothingGroups);` (scope `AbcImporterUtilities`)
- L249 _prototype_ `void CalculateNormalsWithSampleData(FAbcMeshSample* Sample, const FAbcMeshSample* SourceSample);` (scope `AbcImporterUtilities`)
- L251 _prototype_ `void ComputeTangents(FAbcMeshSample* Sample, bool bIgnoreDegenerateTriangles, IMeshUtilities& MeshUtilities);` (scope `AbcImporterUtilities`)
- L253 _function_ `template<typename T> float RetrieveTimeForFrame(T& Schema, const uint32 FrameIndex)` (scope `AbcImporterUtilities`)
- L261 _function_ `template<typename T> void GetMinAndMaxTime(T& Schema, float& MinTime, float& MaxTime)` (scope `AbcImporterUtilities`)
- L269 _function_ `template<typename T> void GetStartTimeAndFrame(T& Schema, float& StartTime, uint32& StartFrame)` (scope `AbcImporterUtilities`)
- L281 _function_ `template<typename T> void GetStartTimeAndFrame(T& Schema, float& StartTime, int32& StartFrame)` (scope `AbcImporterUtilities`)
- L293 _prototype_ `FAbcMeshSample* MergeMeshSamples(const TArray<const FAbcMeshSample*>& Samples);` (scope `AbcImporterUtilities`)
- L295 _prototype_ `FAbcMeshSample* MergeMeshSamples(FAbcMeshSample* MeshSampleOne, FAbcMeshSample* MeshSampleTwo);` (scope `AbcImporterUtilities`)
- L297 _prototype_ `void AppendMeshSample(FAbcMeshSample* MeshSampleOne, const FAbcMeshSample* MeshSampleTwo);` (scope `AbcImporterUtilities`)
- L299 _prototype_ `void GetHierarchyForObject(const Alembic::Abc::IObject& Object, TDoubleLinkedList<Alembic::AbcGeom::IXform>& Hierarchy);` (scope `AbcImporterUtilities`)
- L301 _prototype_ `void PropogateMatrixTransformationToSample(FAbcMeshSample* Sample, const FMatrix& Matrix);` (scope `AbcImporterUtilities`)
- L304 _prototype_ `void GenerateDeltaFrameDataMatrix(const TArray<FVector3f>& FrameVertexData, const TArray<FVector3f>& FrameNormalData, const TArray<FVector3f>& AverageVertexData, const TArray<FVector3f>& AverageNormalData, const int32 SampleIndex, const int32 AverageVertexOffset, const int32 AverageIndexOffset, const FVector& SamplePositionOffset, TArray64<float>& OutGeneratedMatrix, TArray64<float>& OutGeneratedNormalsMatrix);` (scope `AbcImporterUtilities`) — Generates the delta frame data for the given average and frame vertex data
- L308 _prototype_ `void GenerateCompressedMeshData(FCompressedAbcData& CompressedData, const uint32 NumUsedSingularValues, const uint32 NumSamples, const TArrayView64<float>& BasesMatrix, const TArrayView64<float>& NormalsBasesMatrix, const TArray64<float>& BasesWeights, const float SampleTimeStep, const float StartTime);` (scope `AbcImporterUtilities`) — Populates compressed data structure from the result PCA compression bases and weights
- L311 _prototype_ `void CalculateNewStartAndEndFrameIndices(const float FrameStepRatio, int32& InOutStartFrameIndex, int32& InOutEndFrameIndex );` (scope `AbcImporterUtilities`)
- L313 _prototype_ `bool AreVerticesEqual(const FSoftSkinVertex& V1, const FSoftSkinVertex& V2);` (scope `AbcImporterUtilities`)
- L316 _prototype_ `void ApplyConversion(FAbcMeshSample* InOutSample, const FAbcConversionSettings& InConversionSettings, const bool bShouldInverseBuffers);` (scope `AbcImporterUtilities`) — Applies user/preset conversion to the given sample
- L319 _prototype_ `void ApplyConversion(TArray<FMatrix>& InOutMatrices, const FAbcConversionSettings& InConversionSettings);` (scope `AbcImporterUtilities`) — Applies user/preset conversion to the given matrices
- L322 _prototype_ `void ApplyConversion(FMatrix& InOutMatrix, const FAbcConversionSettings& InConversionSettings);` (scope `AbcImporterUtilities`) — Applies user/preset conversion to the given matrices
- L325 _prototype_ `FBoxSphereBounds ExtractBounds(Alembic::Abc::IBox3dProperty InBoxBoundsProperty);` (scope `AbcImporterUtilities`) — Extracts the bounding box from the given alembic property (initialised to zero if the property is invalid)
- L328 _prototype_ `void ApplyConversion(FBoxSphereBounds& InOutBounds, const FAbcConversionSettings& InConversionSettings);` (scope `AbcImporterUtilities`) — Applies user/preset conversion to the given BoxSphereBounds
- L330 _prototype_ `bool IsObjectVisible(const Alembic::Abc::IObject& Object, const Alembic::Abc::ISampleSelector FrameSelector);` (scope `AbcImporterUtilities`) — Returns whether or not the given Object is visible according at the retrieved frame using SampleSelector (this includes parent Objects)
- L332 _prototype_ `bool IsObjectVisibilityConstant(const Alembic::Abc::IObject& Object);` (scope `AbcImporterUtilities`) — Returns whether or not the Objects visibility property is constant across the entire sequence (this includes parent Objects)
- L335 _prototype_ `void GeometryCacheDataForMeshSample(FGeometryCacheMeshData &OutMeshData, const FAbcMeshSample* MeshSample, const uint32 MaterialOffset, const float SecondsPerFrame, const bool bUseVelocitiesAsMotionVectors, const bool bStoreImportedVertexNumbers);` (scope `AbcImporterUtilities`) — Generates and populates a FGeometryCacheMeshData instance from and for the given mesh sample
- L352 _prototype_ `void MergePolyMeshesToMeshData(int32 FrameIndex, int32 FrameStart, float SecondsPerFrame, bool bUseVelocitiesAsMotionVectors, const TArray<FAbcPolyMesh*>& PolyMeshes, const TArray<int32> LookupMaterialSlot, float& FrameTime, FGeometryCacheMeshData& MeshData, int32& PreviousNumVertices, bool& bConstantTopology, bool bStoreImportedVertexNumbers);` (scope `AbcImporterUtilities`) — Merges the given PolyMeshes at the given FrameIndex into a GeometryCacheMeshData @param FrameIndex			The frame index to merge the PolyMeshes at @param FrameStart			The starting frame number of the range being processed @param SecondsPerFrame		The time step of the Abc file @param bUseVelocitiesAsMotionVectors		Converts the AbcPolyMesh velocities to motion vectors @param PolyMeshes			The PolyMeshes to merge, which will be sampled at FrameIndex @param LookupMaterialSlot	Mapping from original face set index (index in flattened list of facesets to import) to material slot (one for each unique faceset name) @param FrameTime				The frame time that corresponds to FrameIndex @param MeshData				The GeometryCacheMeshData where to output the merged PolyMeshes @param PreviousNumVertices	The number of vertices in the merged PolyMeshes, used to determine if its topology is constant between 2 frames @param bConstantTopology		Flag to indicate if the merged PolyMeshes has constant topology @param bStoreImportedVertexNumbers Set to true when we want to store the original dcc vertex numbers for each vertex.
- L359 _prototype_ `UMaterialInterface* RetrieveMaterial(FAbcFile& AbcFile, const FString& MaterialName, UObject* InParent, EObjectFlags Flags);` (scope `AbcImporterUtilities`) — Retrieves a material from an AbcFile according to the given name and resaves it into the parent package

### `Plugins/Importers/AlembicImporter/Source/AlembicLibrary/Private/AlembicTestCommandlet.h` (Private)


#### class `UAlembicTestCommandlet`  
`class UAlembicTestCommandlet : public UCommandlet`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- L14 _private member_ `TArray<FString> CmdLineTokens;` — Parsed commandline tokens
- L17 _private member_ `TArray<FString> CmdLineSwitches;` — Parsed commandline switches
- L19 _private prototype_ `virtual int32 Main(const FString& Params) override;`

### `Plugins/Importers/AlembicImporter/Source/AlembicLibrary/Private/EigenHelper.h` (Private)


#### Free symbols / members of external scopes

- L9 _macro_ `#define EIGEN_MPL2_ONLY`
- L26 _macro_ `#define USE_MEMCPY_FOR_EIGEN_CONVERSION 1`
- L28 _namespace_ `namespace EigenHelpers`
- L31 _function_ `static void SetNumEigenThreads(const int32 InNumThreads)` (scope `EigenHelpers`) — Sets the number of thread used by Eigen
- L41 _function_ `static void ConvertArrayToEigenMatrix(const TArray64<float>& InArray, const int32 InRows, const int32 InColumns, Eigen::MatrixXf& OutMatrix)` (scope `EigenHelpers`) — Converts a float array into an Eigen Matrix
- L61 _function_ `static void ConvertEigenMatrixToArray(const Eigen::MatrixXf& InMatrix, TArray64<float>& OutArray, uint32& OutColumns, uint32& OutRows )` (scope `EigenHelpers`) — Converts an Eigen Matrix into a float array
- L84 _function_ `static void PerformSVD(const Eigen::MatrixXf& InMatrix, Eigen::MatrixXf& OutU, Eigen::MatrixXf& OutV, Eigen::MatrixXf& OutS)` (scope `EigenHelpers`) — Performs Singular value decomposition on the given matrix and returns respective the calculated U, V and S Matrix
- L93 _function_ `static void PerformSVD(const TArray64<float>& InMatrix, const int32 InRows, const int32 InColumns, TArray64<float>& OutU, TArray64<float>& OutV, TArray64<float>& OutS)` (scope `EigenHelpers`) — Performs Singular value decomposition on the given matrix and returns respective the calculated U, V and S Matrix

### `Plugins/Importers/AlembicImporter/Source/AlembicLibrary/Public/AbcAssetImportData.h` (Public)


#### class `UAbcAssetImportData`  
`class UAbcAssetImportData : public UAssetImportData`  
_L14-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetImportData`
- desc: Base class for import data and options used when importing any asset from Alembic
- L19 _public member_ `TArray<FString> TrackNames;` — `UPROPERTY()`
- L22 _public member_ `FAbcSamplingSettings SamplingSettings;` — `UPROPERTY()`
- L25 _public member_ `FAbcNormalGenerationSettings NormalGenerationSettings;` — `UPROPERTY()`
- L28 _public member_ `FAbcMaterialSettings MaterialSettings;` — `UPROPERTY()`
- L31 _public member_ `FAbcCompressionSettings CompressionSettings;` — `UPROPERTY()`
- L34 _public member_ `FAbcStaticMeshSettings StaticMeshSettings;` — `UPROPERTY()`
- L37 _public member_ `FAbcGeometryCacheSettings GeometryCacheSettings;` — `UPROPERTY()`
- L40 _public member_ `FAbcConversionSettings ConversionSettings;` — `UPROPERTY()`

### `Plugins/Importers/AlembicImporter/Source/AlembicLibrary/Public/AbcFile.h` (Public)


#### enum `EFrameReadFlags`  
`enum class EFrameReadFlags : uint8`  
_L33-42_
- desc: Read flags for the abc file
- L35 _public enumerator_ `None = 0`
- L37 _public enumerator_ `PositionAndNormalOnly = 1 << 1` — Will only read position and normal data for the objects
- L39 _public enumerator_ `ApplyMatrix = 1 << 2` — Will pre-multiply the world matrix with the read sample positions
- L41 _public enumerator_ `ForceSingleThreaded = 1 << 4` — Will force single thread processing

#### class `FAbcFile`  
`class FAbcFile`  
_L46-179_
- L49 _public prototype_ `FAbcFile(const FString& InFilePath);`
- L50 _public prototype_ `~FAbcFile();`
- L53 _public prototype_ `EAbcImportError Open();` — Opens the ABC file and reads initial data for import options
- L55 _public prototype_ `EAbcImportError Import(UAbcImportSettings* InImportSettings);` — Sets up import data and propagates import settings to read objects
- L58 _public prototype_ `const FString GetFilePath() const;` — Get file path for currently opened ABC file
- L61 _public prototype_ `bool ProcessFrames(TFunctionRef<void(int32, FAbcFile*)> InCallback, const EFrameReadFlags InFlags, const FSlowTask* SlowTask = nullptr);` — Process all to-import frames for each poly mesh inside of the ABC file, optional SlowTask to interrupt process and returns 'completed'
- L64 _public prototype_ `const int32 GetMinFrameIndex() const;` — Returns ABC specific frame and timing information
- L65 _public prototype_ `const int32 GetMaxFrameIndex() const;`
- L66 _public prototype_ `const float GetImportTimeOffset() const;`
- L67 _public prototype_ `const float GetImportLength() const;`
- L68 _public prototype_ `const int32 GetImportNumFrames() const;`
- L69 _public prototype_ `const float GetFramerate() const;`
- L70 _public prototype_ `const float GetSecondsPerFrame() const;`
- L71 _public prototype_ `const FBoxSphereBounds& GetArchiveBounds() const;`
- L72 _public prototype_ `const bool ContainsHeterogeneousMeshes() const;`
- L75 _public prototype_ `const int32 GetStartFrameIndex() const;` — Returns start/end frame index of imported playback range
- L76 _public prototype_ `const int32 GetEndFrameIndex() const;`
- L79 _public prototype_ `const UAbcImportSettings* GetImportSettings() const;` — Returns user specified import settings
- L82 _public prototype_ `const TArray<FAbcPolyMesh*>& GetPolyMeshes() const;` — Return array of PolyMeshes inside of the ABC file
- L84 _public prototype_ `const int32 GetNumPolyMeshes() const;` — Return number of PolyMeshes inside of the ABC file
- L86 _public prototype_ `const TArray<FAbcTransform*>& GetTransforms() const;` — Return array of Transform Objects inside of the ABC file
- L89 _public prototype_ `IMeshUtilities* GetMeshUtilities() const;` — Return mesh utilities module ptr (used in non-gamethread jobs)
- L91 _public prototype_ `UMaterialInterface** GetMaterialByName(const FString& InMaterialName);` — Returns a material for the specified material(faceset) name or null if it wasn't created or found
- L93 _public prototype_ `int32 GetFrameIndex(float Time);` — Returns frame index equivalent to a given time, based on the frame rate of the file
- L95 _public prototype_ `void ReadFrame(int32 FrameIndex, const EFrameReadFlags InFlags, const int32 ReadIndex = INDEX_NONE);` — Reads the frame data for the given FrameIndex, with the ReadIndex used to specify the current read when doing concurrent reads (up to 8 at the same time)
- L97 _public prototype_ `void CleanupFrameData(const int32 ReadIndex);` — Cleans up frame data. Must be called after ReadFrame when the frame data (with matching ReadIndex) is not needed anymore
- L99 _public function_ `const TArray<FString>& GetUniqueFaceSetNames() const` — Returns the list of unique face set names from the meshes to be imported
- L101 _public function_ `const TArray<int32>& GetLookupMaterialSlot() const` — Returns the mapping from material index (stored in per triangle material indices of FAbcMeshSample) to material slot (one for each unique faceset name)
- L103 _public function_ `int32 GetNumMaterialSlots() const` — Returns the number of material slots ( == number of unique facesets )
- L105 _public typedef_ `typedef TPair<FString, FString> FMetaData;`
- L107 _public prototype_ `TArray<FMetaData> GetArchiveMetaData() const;` — Returns the metadata of the Alembic archive
- L109 _public member_ `static const FString NoFaceSetNameStr;`
- L112 _protected prototype_ `void TraverseAbcHierarchy(const Alembic::Abc::IObject& InObject, IAbcObject* InParent);`
- L113 _protected prototype_ `void ExtractCustomAttributes(const Alembic::AbcGeom::IPolyMesh& InMesh);`
- L116 _protected member_ `const FString FilePath;` — File path for the ABC file
- L118 _protected member_ `UAbcImportSettings* ImportSettings;` — Cached user set import settings
- L121 _protected member_ `Alembic::AbcCoreFactory::IFactory Factory;` — Factory used to generate objects
- L122 _protected member_ `Alembic::AbcCoreFactory::IFactory::CoreType CompressionType;`
- L124 _protected member_ `Alembic::Abc::IArchive Archive;` — Archive-typed ABC file
- L126 _protected member_ `Alembic::Abc::IObject TopObject;` — Alembic typed root (top) object
- L129 _protected member_ `TArray<IAbcObject*> Objects;` — Abstract and typed objects part of this ABC file
- L130 _protected member_ `TArray<FAbcPolyMesh*> PolyMeshes;`
- L131 _protected member_ `TArray<FAbcTransform*> Transforms;`
- L133 _protected member_ `IAbcObject* RootObject;` — Root (top) object in the ABC file
- L136 _protected member_ `int32 MinFrameIndex;` — Min and maximum frame index which contain actual data in the Alembic file
- L137 _protected member_ `int32 MaxFrameIndex;`
- L140 _protected member_ `float ArchiveSecondsPerFrame;` — FPS stored inside of the ABC file
- L143 _protected member_ `TMap<FString, UMaterialInterface*> MaterialMap;` — Map of material created for the imported alembic file identified by material names
- L144 _protected member_ `TArray<FString> UniqueFaceSetNames;`
- L145 _protected member_ `TArray<int32> LookupMaterialSlot;`
- L148 _protected member_ `int32 NumFrames;` — Total (max) number of frames in the Alembic file
- L150 _protected member_ `float FramesPerSecond;` — Frames per second (retrieved and specified in top Alembic object)
- L152 _protected member_ `float SecondsPerFrame;` — Seconds per frame (calculated according to FPS)
- L155 _protected member_ `int32 StartFrameIndex;` — Frame indices at which to start and stop importing
- L156 _protected member_ `int32 EndFrameIndex;`
- L159 _protected member_ `FBoxSphereBounds ArchiveBounds;` — Entire bounds of the archive over time
- L162 _protected member_ `float MinTime;` — Min and maximum time found in the Alembic file
- L163 _protected member_ `float MaxTime;`
- L164 _protected member_ `float ImportTimeOffset;`
- L166 _protected member_ `float ImportLength;` — Final length (in seconds)_of sequence we are importing
- L169 _protected member_ `IMeshUtilities* MeshUtilities;` — Cached Mesh utilities ptr for normal calculations
- L171 _protected member_ `FString AppName;`
- L172 _protected member_ `FString LibVersionString;`
- L173 _protected member_ `uint32 LibVersion;`
- L174 _protected member_ `FString DateWritten;`
- L175 _protected member_ `FString UserDescription;`
- L176 _protected member_ `FString Hash;`
- L178 _protected member_ `TMap<FString, FString> CustomAttributes;`

#### Free symbols / members of external scopes

- L44 _prototype_ `ENUM_CLASS_FLAGS(EFrameReadFlags);`

### `Plugins/Importers/AlembicImporter/Source/AlembicLibrary/Public/AbcImportLogger.h` (Public)


#### class `FAbcImportLogger`  
`class FAbcImportLogger`  
_L9-24_
- L12 _protected prototype_ `FAbcImportLogger();`
- L15 _public prototype_ `static void AddImportMessage(const TSharedRef<FTokenizedMessage> Message);` — Adds an import message to the stored array for later output
- L17 _public prototype_ `static void OutputMessages(const FString& PageName);` — Outputs the messages to a new named page in the message log
- L19 _public prototype_ `static TArray<TSharedRef<FTokenizedMessage>> RetrieveMessages();` — Returns the messages and flushes them from the logger
- L22 _private member_ `static TArray<TSharedRef<FTokenizedMessage>> TokenizedErrorMessages;` — Error messages
- L23 _private member_ `static FCriticalSection MessageLock;`

### `Plugins/Importers/AlembicImporter/Source/AlembicLibrary/Public/AbcImportSettings.h` (Public)


#### enum `EAlembicImportType`  
`enum class EAlembicImportType : uint8`  
_L11-19_
- reflection: `UENUM(BlueprintType)`
- desc: Enum that describes type of asset to import
- L14 _public enumerator_ `StaticMesh` — Imports only the first frame as one or multiple static meshes
- L16 _public enumerator_ `GeometryCache UMETA(DisplayName = "Geometry Cache")` — Imports the Alembic file as flipbook and matrix animated objects
- L18 _public enumerator_ `Skeletal` — Imports the Alembic file as a skeletal mesh containing base poses as morph targets and blending between them to achieve the correct animation frame

#### enum `EBaseCalculationType`  
`enum class EBaseCalculationType : uint8`  
_L22-31_
- reflection: `UENUM(BlueprintType)`
- L24 _public enumerator_ `None = 0 UMETA(Hidden)`
- L26 _public enumerator_ `PercentageBased = 1` — Determines the number of bases that should be used with the given percentage
- L28 _public enumerator_ `FixedNumber` — Set a fixed number of bases to import
- L30 _public enumerator_ `NoCompression` — One base per frame, uncompressed

#### struct `FAbcCompressionSettings`  
`struct FAbcCompressionSettings`  
_L34-72_
- reflection: `USTRUCT(Blueprintable)`
- L38 _public function_ `FAbcCompressionSettings()`
- L51 _public member_ `bool bMergeMeshes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Compression)` — Whether or not the individual meshes should be merged for compression purposes
- L55 _public member_ `bool bBakeMatrixAnimation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Compression)` — Whether or not Matrix-only animation should be baked out as vertex animation (or skipped?)
- L59 _public member_ `EBaseCalculationType BaseCalculationType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Compression)` — Determines how the final number of bases that are stored as morph targets are calculated
- L63 _public member_ `float PercentageOfTotalBases;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Compression, meta = (EnumCondition = 1, ClampMin = "1.0", ClampMax="100.0"))` — Will generate given percentage of the given bases as morph targets
- L67 _public member_ `int32 MaxNumberOfBases;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Compression, meta = (EnumCondition = 2, ClampMin = "1"))` — Will generate given fixed number of bases as morph targets
- L71 _public member_ `float MinimumNumberOfVertexInfluencePercentage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = Compression, meta = (ClampMin = "0.0", ClampMax = "100.0"))` — Minimum percentage of influenced vertices required for a morph target to be valid

#### enum `EAlembicSamplingType`  
`enum class EAlembicSamplingType : uint8`  
_L75-83_
- reflection: `UENUM(BlueprintType)`
- L78 _public enumerator_ `PerFrame` — Samples the animation according to the imported data (default)
- L80 _public enumerator_ `PerXFrames UMETA(DisplayName = "Per X Frames")` — Samples the animation at given intervals determined by Frame Steps
- L82 _public enumerator_ `PerTimeStep` — Samples the animation at given intervals determined by Time Steps

#### struct `FAbcSamplingSettings`  
`struct FAbcSamplingSettings`  
_L86-122_
- reflection: `USTRUCT(Blueprintable)`
- L90 _public function_ `FAbcSamplingSettings()`
- L101 _public member_ `EAlembicSamplingType SamplingType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sampling)` — Type of sampling performed while importing the animation
- L105 _public member_ `int32 FrameSteps;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sampling, meta = (EnumCondition = 1,ClampMin = "1"))` — Steps to take when sampling the animation
- L109 _public member_ `float TimeSteps;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sampling, meta = (EnumCondition = 2, ClampMin = "0.0001"))` — Time steps to take when sampling the animation
- L113 _public member_ `int32 FrameStart;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sampling)` — Starting index to start sampling the animation from
- L117 _public member_ `int32 FrameEnd;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sampling)` — Ending index to stop sampling the animation at
- L121 _public member_ `bool bSkipEmpty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sampling, meta=(DisplayName = "Skip Empty Frames at Start of Alembic Sequence"))` — Skip empty (pre-roll) frames and start importing at the frame which actually contains data

#### struct `FAbcNormalGenerationSettings`  
`struct FAbcNormalGenerationSettings`  
_L125-157_
- reflection: `USTRUCT(Blueprintable)`
- L129 _public function_ `FAbcNormalGenerationSettings()`
- L140 _public member_ `bool bForceOneSmoothingGroupPerObject;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NormalCalculation)` — Whether or not to force smooth normals for each individual object rather than calculating smoothing groups
- L144 _public member_ `float HardEdgeAngleThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NormalCalculation, meta = (EditCondition = "!bForceOneSmoothingGroupPerObject", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Threshold used to determine whether an angle between two normals should be considered hard, closer to 0 means more smooth vs 1
- L148 _public member_ `bool bRecomputeNormals;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NormalCalculation)` — Determines whether or not the normals should be forced to be recomputed
- L152 _public member_ `bool bIgnoreDegenerateTriangles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NormalCalculation, meta = (EditCondition = "bRecomputeNormals"))` — Determines whether or not the degenerate triangles should be ignored when calculating tangents/normals
- L156 _public member_ `bool bSkipComputingTangents;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hidden, AdvancedDisplay)` — Determines whether tangents are computed for GeometryCache. Skipping them can improve streaming performance but may cause visual artifacts where they are required

#### struct `FAbcMaterialSettings`  
`struct FAbcMaterialSettings`  
_L160-176_
- reflection: `USTRUCT(Blueprintable)`
- L164 _public function_ `FAbcMaterialSettings() : bCreateMaterials(false) , bFindMaterials(false)`
- L171 _public member_ `bool bCreateMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)` — Whether or not to create materials according to found Face Set names (will not work without face sets)
- L175 _public member_ `bool bFindMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)` — Whether or not to try and find materials according to found Face Set names (will not work without face sets)

#### struct `FAbcStaticMeshSettings`  
`struct FAbcStaticMeshSettings`  
_L179-200_
- reflection: `USTRUCT(Blueprintable)`
- L183 _public function_ `FAbcStaticMeshSettings() : bMergeMeshes(true), bPropagateMatrixTransformations(true), bGenerateLightmapUVs(true)`
- L191 _public member_ `bool bMergeMeshes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StaticMesh)` — Whether or not to merge the static meshes on import (remember this can cause problems with overlapping UV-sets)
- L195 _public member_ `bool bPropagateMatrixTransformations;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StaticMesh)` — This will, if applicable, apply matrix transformations to the meshes
- L199 _public member_ `bool bGenerateLightmapUVs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StaticMesh)` — Flag for whether or not lightmap UVs should be generated

#### enum `EAbcConversionPreset`  
`enum class EAbcConversionPreset : uint8`  
_L204-211_
- reflection: `UENUM(Blueprintable)`
- desc: Enum that describes type of asset to import
- L207 _public enumerator_ `Maya UMETA(DisplayName = "Autodesk Maya")` — Imports only the first frame as one or multiple static meshes
- L209 _public enumerator_ `Max UMETA(DisplayName = "Autodesk 3ds Max")` — Imports the Alembic file as flipbook and matrix animated objects
- L210 _public enumerator_ `Custom UMETA(DisplayName = "Custom Settings")`

#### struct `FAbcConversionSettings`  
`struct FAbcConversionSettings`  
_L214-245_
- reflection: `USTRUCT(Blueprintable)`
- L218 _public function_ `FAbcConversionSettings() : Preset(EAbcConversionPreset::Maya) , bFlipU(false) , bFlipV(true) , Scale(FVector(1.0f, -1.0f, 1.0f)) , Rotation(FVector(90.0f, 0.0f, 0.0f))`
- L228 _public member_ `EAbcConversionPreset Preset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conversion)` — Currently preset that should be applied
- L232 _public member_ `bool bFlipU;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conversion)` — Flag whether or not to flip the U channel in the Texture Coordinates
- L236 _public member_ `bool bFlipV;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conversion)` — Flag whether or not to flip the V channel in the Texture Coordinates
- L240 _public member_ `FVector Scale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conversion)` — Scale value that should be applied
- L244 _public member_ `FVector Rotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conversion)` — Rotation in Euler angles that should be applied

#### enum `EAbcGeometryCacheMotionVectorsImport`  
`enum class EAbcGeometryCacheMotionVectorsImport : uint8`  
_L248-256_
- reflection: `UENUM(Blueprintable)`
- L251 _public enumerator_ `NoMotionVectors` — No motion vectors will be present in the geometry cache.
- L253 _public enumerator_ `ImportAbcVelocitiesAsMotionVectors` — Imports the Velocities from the Alembic file and converts them to motion vectors. This will increase file size as the motion vectors will be stored on disc.
- L255 _public enumerator_ `CalculateMotionVectorsDuringImport` — Force calculation of motion vectors during import. This will increase file size as the motion vectors will be stored on disc.

#### struct `FAbcGeometryCacheSettings`  
`struct FAbcGeometryCacheSettings`  
_L259-306_
- reflection: `USTRUCT(Blueprintable)`
- L263 _public function_ `FAbcGeometryCacheSettings() : bFlattenTracks(true), bStoreImportedVertexNumbers(false), bApplyConstantTopologyOptimizations(false), bCalculateMotionVectorsDuringImport_DEPRECATED(false), MotionVectors(EAbcGeometryCacheMotionVectorsImport::NoMotionVectors), bOptimizeIndexBuffers(false), CompressedPositionPrecision(0.01f), CompressedTextureCoordinatesNumberOfBits(10)`
- L276 _public member_ `bool bFlattenTracks;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeometryCache)` — Whether or not to merge all vertex animation into one track
- L281 _public member_ `bool bStoreImportedVertexNumbers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeometryCache, AdvancedDisplay)` — Store the imported vertex numbers. This lets you know the vertex numbers inside the DCC. The values of each vertex number will range from 0 to 7 for a cube. Even if the number of positions might be 24.
- L286 _public member_ `bool bApplyConstantTopologyOptimizations;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeometryCache)` — Force the preprocessor to only do optimization once instead of when the preprocessor decides. This may lead to some problems with certain meshes but makes sure motion blur always works if the topology is constant.
- L290 _public member_ `bool bCalculateMotionVectorsDuringImport_DEPRECATED;` — `UPROPERTY()` — Force calculation of motion vectors during import. This will increase file size as the motion vectors will be stored on disc. Recommended to OFF.
- L293 _public member_ `EAbcGeometryCacheMotionVectorsImport MotionVectors;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = GeometryCache)`
- L297 _public member_ `bool bOptimizeIndexBuffers;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = GeometryCache)` — Optimizes index buffers for each unique frame, to allow better cache coherency on the GPU. Very costly and time-consuming process, recommended to OFF.
- L301 _public member_ `float CompressedPositionPrecision;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeometryCache, meta = (ClampMin = "0.000001", ClampMax = "1000", UIMin = "0.01", UIMax = "100"))` — Precision used for compressing vertex positions (lower = better result but less compression, higher = more lossy compression but smaller size)
- L305 _public member_ `int32 CompressedTextureCoordinatesNumberOfBits;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeometryCache, meta = (ClampMin = "1", ClampMax = "31", UIMin = "4", UIMax = "16"))` — Bit-precision used for compressing texture coordinates (hight = better result but less compression, lower = more lossy compression but smaller size)

#### class `UAbcImportSettings`  
`class UAbcImportSettings : public UObject`  
_L310-347_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject`
- desc: Class that contains all options for importing an alembic file
- L315 _private prototype_ `static UAbcImportSettings* Get();` — Accessor and initializer
- L319 _private member_ `EAlembicImportType ImportType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alembic)` — Type of asset to import from Alembic file
- L322 _private member_ `FAbcSamplingSettings SamplingSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Sampling)`
- L325 _private member_ `FAbcNormalGenerationSettings NormalGenerationSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = NormalCalculation)`
- L328 _private member_ `FAbcMaterialSettings MaterialSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Materials)`
- L331 _private member_ `FAbcCompressionSettings CompressionSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Compression)`
- L334 _private member_ `FAbcStaticMeshSettings StaticMeshSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = StaticMesh)`
- L337 _private member_ `FAbcGeometryCacheSettings GeometryCacheSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = GeometryCache)`
- L340 _private member_ `FAbcConversionSettings ConversionSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Conversion)`
- L342 _private member_ `bool bReimport;`
- L343 _private member_ `int32 NumThreads;`
- L346 _public prototype_ `virtual void Serialize(class FArchive& Archive) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ALEMBICLIBRARY_API`

### `Plugins/Importers/AlembicImporter/Source/AlembicLibrary/Public/AbcImporter.h` (Public)


#### enum `EAbcImportError`  
`enum EAbcImportError : uint32`  
_L43-50_
- L45 _public enumerator_ `AbcImportError_NoError`
- L46 _public enumerator_ `AbcImportError_InvalidArchive`
- L47 _public enumerator_ `AbcImportError_NoValidTopObject`
- L48 _public enumerator_ `AbcImportError_NoMeshes`
- L49 _public enumerator_ `AbcImportError_FailedToImportData`

#### struct `FCompressedAbcData`  
`struct FCompressedAbcData`  
_L52-65_
- L54 _public prototype_ `~FCompressedAbcData();`
- L56 _public member_ `FGuid Guid;` — GUID identifying the poly mesh object this compressed data corresponds to
- L58 _public member_ `FAbcMeshSample* AverageSample;` — Average sample to apply the bases to
- L60 _public member_ `TArray<FAbcMeshSample*> BaseSamples;` — List of base samples calculated using PCA compression
- L62 _public member_ `TArray<TArray<float>> CurveValues;` — Contains the curve values for each individual base
- L64 _public member_ `TArray<TArray<float>> TimeValues;` — Contains the time key values for each individual base

#### struct `FMeshSection`  
`struct FMeshSection`  
_L68-81_
- desc: Mesh section used for chunking the mesh data during Skeletal mesh building
- L70 _public function_ `FMeshSection() : MaterialIndex(0), NumFaces(0)`
- L71 _public member_ `int32 MaterialIndex;`
- L72 _public member_ `TArray<uint32> Indices;`
- L73 _public member_ `TArray<uint32> OriginalIndices;`
- L74 _public member_ `TArray<FVector> TangentX;`
- L75 _public member_ `TArray<FVector> TangentY;`
- L76 _public member_ `TArray<FVector> TangentZ;`
- L77 _public member_ `TArray<FVector2D> UVs[MAX_TEXCOORDS];`
- L78 _public member_ `TArray<FColor> Colors;`
- L79 _public member_ `uint32 NumFaces;`
- L80 _public member_ `uint32 NumUVSets;`

#### class `FAbcImporter`  
`class FAbcImporter`  
_L83-225_
- L86 _public prototype_ `FAbcImporter();`
- L87 _public prototype_ `~FAbcImporter();`
- L95 _public prototype_ `const EAbcImportError OpenAbcFileForImport(const FString InFilePath);` — Opens and caches basic data from the Alembic file to be used for populating the importer UI @param InFilePath - Path to the Alembic file to be opened @return - Possible error code
- L103 _public prototype_ `const EAbcImportError ImportTrackData(const int32 InNumThreads, UAbcImportSettings* ImportSettings);` — Imports the individual tracks from the Alembic file @param InNumThreads - Number of threads to use for importing @return - Possible error code
- L112 _public prototype_ `const TArray<UStaticMesh*> ImportAsStaticMesh(UObject* InParent, EObjectFlags Flags);` — Import Alembic meshes as a StaticMeshInstance @param InParent - ParentObject for the static mesh @param Flags - Object flags @return FStaticMesh*
- L121 _public prototype_ `UGeometryCache* ImportAsGeometryCache(UObject* InParent, EObjectFlags Flags);` — Import an Alembic file as a GeometryCache @param InParent - ParentObject for the static mesh @param Flags - Object flags @return UGeometryCache*
- L123 _public prototype_ `TArray<UObject*> ImportAsSkeletalMesh(UObject* InParent, EObjectFlags Flags);`
- L131 _public prototype_ `const TArray<UStaticMesh*> ReimportAsStaticMesh(UStaticMesh* Mesh);` — Reimport an Alembic mesh @param Mesh - Current StaticMesh instance @return FStaticMesh*
- L139 _public prototype_ `UGeometryCache* ReimportAsGeometryCache(UGeometryCache* GeometryCache);` — Reimport an Alembic file as a GeometryCache @param GeometryCache - Current GeometryCache instance @return UGeometryCache*
- L147 _public prototype_ `TArray<UObject*> ReimportAsSkeletalMesh(USkeletalMesh* SkeletalMesh);` — Reimport an Alembic file as a SkeletalMesh @param SkeletalMesh - Current SkeletalMesh instance @return USkeletalMesh*
- L150 _public prototype_ `const TArray<class FAbcPolyMesh*>& GetPolyMeshes() const;` — Returns the array of imported PolyMesh objects
- L153 _public prototype_ `const uint32 GetStartFrameIndex() const;` — Returns the lowest frame index containing data for the imported Alembic file
- L156 _public prototype_ `const uint32 GetEndFrameIndex() const;` — Returns the highest frame index containing data for the imported Alembic file
- L159 _public prototype_ `const uint32 GetNumMeshTracks() const;` — Returns the number of tracks found in the imported Alembic file
- L161 _public prototype_ `void UpdateAssetImportData(UAbcAssetImportData* AssetImportData);`
- L162 _public prototype_ `void RetrieveAssetImportData(UAbcAssetImportData* ImportData);`
- L171 _private prototype_ `template<typename T> T* CreateObjectInstance(UObject*& InParent, const FString& ObjectName, const EObjectFlags Flags, bool& bObjectAlreadyExists);` — Creates an template object instance taking into account existing Instances and Objects (on reimporting) @param InParent - ParentObject for the geometry cache, this can be changed when parent is deleted/re-created @param ObjectName - Name to be used for the created object @param Flags - Object creation flags
- L185 _private prototype_ `UStaticMesh* CreateStaticMeshFromSample(UObject* InParent, const FString& Name, EObjectFlags Flags, const TArray<FString>& UniqueFaceSetNames, const TArray<int32>& LookupMaterialSlot, const FAbcMeshSample* Sample);` — Creates a Static mesh from the given mesh description @param InParent - ParentObject for the static mesh @param Name - Name for the static mesh @param Flags - Object flags @param NumMaterials - Number of materials to add @param UniqueFaceSetNames - The array of unique face set (material slot) names for merged mesh @param LookupMaterialSlot - Mapping from faceset index (in flattened list) to material slot @param Sample - The FAbcMeshSample from which the static mesh should be constructed @return UStaticMesh*
- L188 _private prototype_ `void GenerateMeshDescriptionFromSample(const TArray<FString>& UniqueFaceSetNames, const TArray<int32>& LookupMaterialSlot, const FAbcMeshSample* Sample, FMeshDescription* MeshDescription);` — Generates and populate a FMeshDescription instance from the given sample
- L191 _private prototype_ `const bool CompressAnimationDataUsingPCA(const FAbcCompressionSettings& InCompressionSettings, const bool bRunComparison = false);` — Compresses the imported animation data, returns true if compression was successful and compressed data was populated
- L193 _private prototype_ `const int32 PerformSVDCompression(const TArray64<float>& OriginalMatrix, const TArray64<float>& OriginalNormalsMatrix, const uint32 NumSamples, const float InPercentage, const int32 InFixedNumValue, TArray64<float>& OutU, TArray64<float>& OutNormalsU, TArray64<float>& OutV);` — Performs the actual SVD compression to retrieve the bases and weights used to set up the Skeletal mesh's morph targets
- L197 _private prototype_ `void CompareCompressionResult(const TArray64<float>& OriginalMatrix, const uint32 NumSamples, const uint32 NumUsedSingularValues, const TArrayView64<float>& OutU, const TArray64<float>& OutV, const float Tolerance);` — Functionality for comparing the matrices and calculating the difference from the original animation
- L200 _private prototype_ `bool BuildSkeletalMesh(FSkeletalMeshLODModel& LODModel, const FReferenceSkeleton& RefSkeleton, FAbcMeshSample* Sample, int32 NumMaterialSlots, const TArray<int32> LookupMaterialSlot, TArray<int32>& OutMorphTargetVertexRemapping, TArray<int32>& OutUsedVertexIndicesForMorphs);` — Build a skeletal mesh from the PCA compressed data
- L205 _private prototype_ `void GenerateMorphTargetVertices(FAbcMeshSample* BaseSample, TArray<FMorphTargetDelta> &MorphDeltas, FAbcMeshSample* AverageSample, uint32 WedgeOffset, const TArray<int32>& RemapIndices, const TArray<int32>& UsedVertexIndicesForMorphs, const uint32 VertexOffset, const uint32 IndexOffset);` — Generate morph target vertices from the PCA compressed bases
- L208 _private prototype_ `void SetupMorphTargetCurves(USkeleton* Skeleton, FName ConstCurveName, UAnimSequence* Sequence, const TArray<float> &CurveValues, const TArray<float>& TimeValues, IAnimationDataController& Controller, bool bShouldTransact);` — Set up correct morph target weights from the PCA compressed data
- L211 _private prototype_ `void SetMetaData(const TArray<UObject*>& Objects);` — Set the Alembic archive metadata on the given objects
- L215 _private member_ `UAbcImportSettings* ImportSettings;` — Cached ptr for the import settings
- L218 _private member_ `TArray<FCompressedAbcData> CompressedMeshData;` — Resulting compressed data from PCA compression
- L221 _private member_ `TOptional<TArray<FVector>> SamplesOffsets;` — Offset for each sample, used as the root bone translation
- L224 _private member_ `class FAbcFile* AbcFile;` — ABC file representation for currently opened filed

### `Plugins/Importers/AlembicImporter/Source/AlembicLibrary/Public/AbcObject.h` (Public)


#### class `IAbcObject`  
`class IAbcObject`  
_L25-72_
- L28 _public prototype_ `IAbcObject(const Alembic::Abc::IObject& InObject, const FAbcFile* InFile, IAbcObject* InParent);`
- L29 _public prototype_ `virtual ~IAbcObject() = default;`
- L31 _public function_ `const FString& GetName() const`
- L32 _public prototype_ `float GetTimeForFrameIndex(const int32 FrameIndex) const;`
- L33 _public function_ `float GetTimeForFirstData() const`
- L34 _public function_ `float GetTimeForLastData() const`
- L35 _public function_ `int32 GetFrameIndexForFirstData() const`
- L36 _public function_ `int32 GetNumberOfSamples() const`
- L37 _public function_ `bool IsConstant() const`
- L39 _public function_ `virtual FMatrix GetMatrix(const int32 FrameIndex) const`
- L40 _public prototype_ `virtual void SetFrameAndTime(const float InTime, const int32 FrameIndex, const EFrameReadFlags InFlags, const int32 TargetIndex = INDEX_NONE) = 0;`
- L41 _public prototype_ `virtual bool HasConstantTransform() const = 0;`
- L42 _public prototype_ `virtual bool ReadFirstFrame(const float InTime, const int32 FrameIndex) = 0;`
- L43 _public prototype_ `virtual void PurgeFrameData(const int32 FrameIndex) = 0;`
- L46 _protected member_ `FString Name;` — Name of this object
- L49 _protected member_ `IAbcObject* Parent;` — Parent object
- L52 _protected member_ `const FAbcFile* File;` — File of which this object is part of
- L54 _protected member_ `const Alembic::Abc::IObject Object;` — Abstract Alembic representation of this object
- L57 _protected member_ `bool bConstant;` — Flag whether or not this object is constant
- L60 _protected member_ `float MinTime;` — Time of first frame containing data
- L62 _protected member_ `float MaxTime;` — Time of last frame containing data
- L64 _protected member_ `int32 StartFrameIndex;` — Frame index of first frame containing data
- L67 _protected member_ `int32 NumSamples;` — Number of data samples for this object
- L69 _protected member_ `float FrameTimes[MaxNumberOfResidentSamples];`
- L70 _protected member_ `int32 ResidentSampleIndices[MaxNumberOfResidentSamples];`
- L71 _protected member_ `bool InUseSamples[MaxNumberOfResidentSamples];`

#### Free symbols / members of external scopes

- L23 _variable_ `static const int32 MaxNumberOfResidentSamples = 8;`

### `Plugins/Importers/AlembicImporter/Source/AlembicLibrary/Public/AbcPolyMesh.h` (Public)


#### struct `FAbcMeshSample`  
`struct FAbcMeshSample`  
_L14-75_
- desc: Structure for storing individual track samples
- L16 _public function_ `FAbcMeshSample() : NumSmoothingGroups(0) , NumUVSets(1) , NumMaterials(0) , SampleTime(0.0f)`
- L23 _public function_ `FAbcMeshSample(const FAbcMeshSample& InSample)` — Constructing from other sample
- L46 _public prototype_ `void Reset(const ESampleReadFlags ReadFlags);`
- L47 _public prototype_ `void Copy(const FAbcMeshSample& InSample, const ESampleReadFlags ReadFlags);`
- L48 _public prototype_ `void Copy(const FAbcMeshSample* InSample, const ESampleReadFlags ReadFlags);`
- L50 _public member_ `TArray<FVector3f> Vertices;`
- L51 _public member_ `TArray<FVector3f> Velocities;`
- L52 _public member_ `TArray<uint32> Indices;`
- L55 _public member_ `TArray<FVector3f> Normals;` — Vertex attributes (per index based)
- L56 _public member_ `TArray<FVector3f> TangentX;`
- L57 _public member_ `TArray<FVector3f> TangentY;`
- L58 _public member_ `TArray<FVector2f> UVs[MAX_TEXCOORDS];`
- L60 _public member_ `TArray<FLinearColor> Colors;`
- L65 _public member_ `TArray<int32> MaterialIndices;` — Per Face material and smoothing group index
- L66 _public member_ `TArray<uint32> SmoothingGroupIndices;`
- L69 _public member_ `uint32 NumSmoothingGroups;` — Number of smoothing groups and different materials (will always be at least 1)
- L70 _public member_ `uint32 NumUVSets;`
- L71 _public member_ `uint32 NumMaterials;`
- L74 _public member_ `float SampleTime;` — Time in track this sample was taken from

#### class `FAbcPolyMesh`  
`class FAbcPolyMesh : public IAbcObject`  
_L77-143_
- inherits: `IAbcObject`
- L80 _public prototype_ `FAbcPolyMesh(const Alembic::AbcGeom::IPolyMesh& InPolyMesh, const FAbcFile* InFile, IAbcObject* InParent = nullptr);`
- L81 _public prototype_ `virtual ~FAbcPolyMesh() = default;`
- L84 _public prototype_ `virtual bool ReadFirstFrame(const float InTime, const int32 FrameIndex) final;` — Begin IAbcObject overrides
- L85 _public prototype_ `virtual void SetFrameAndTime(const float InTime, const int32 FrameIndex, const EFrameReadFlags InFlags, const int32 TargetIndex = INDEX_NONE) final;`
- L86 _public prototype_ `virtual FMatrix GetMatrix(const int32 FrameIndex) const final;`
- L87 _public prototype_ `virtual bool HasConstantTransform() const final;`
- L88 _public prototype_ `virtual void PurgeFrameData(const int32 FrameIndex) final;`
- L92 _public prototype_ `const FAbcMeshSample* GetSample(const int32 FrameIndex) const;` — Returns sample for the given frame index (if it is part of the resident samples)
- L94 _public prototype_ `const FAbcMeshSample* GetFirstSample() const;` — Returns the first sample available for this object
- L96 _public prototype_ `const FAbcMeshSample* GetTransformedFirstSample() const;` — Returns the first sample available for this object transformed by first available matrix
- L98 _public prototype_ `ESampleReadFlags GetSampleReadFlags() const;` — Returns the value of the bitmask used for skipping constant vertex attributes while reading samples
- L100 _public prototype_ `const bool GetVisibility(const int32 FrameIndex) const;` — Returns the visibility value (true = visible, false = hidden) for the given frame index  (if it is part of the resident samples)
- L103 _public member_ `bool bConstantTopology;` — Flag whether or not this object has constant topology (used for eligibility for PCA compression)
- L105 _public member_ `bool bConstantTransformation;` — Flag whether or not this object has a constant world matrix (used whether to incorporate into PCA compression)
- L107 _public member_ `bool bConstantVisibility;` — Flag whether or not this object has a constant visibility value across the entire animated range
- L110 _public member_ `FBoxSphereBounds SelfBounds;` — Cached self and child bounds for entire duration of the animation
- L111 _public member_ `FBoxSphereBounds ChildBounds;`
- L114 _public member_ `TArray<FString> FaceSetNames;` — Array of face set names found for this object
- L117 _public member_ `bool bShouldImport;` — Whether or not this Mesh object should be imported
- L120 _protected prototype_ `void CalculateNormalsForSample(FAbcMeshSample* Sample);` — Calculate normals for sample according to available data and user settings
- L123 _protected member_ `const Alembic::AbcGeom::IPolyMesh PolyMesh;` — Alembic representation of this object
- L125 _protected member_ `const Alembic::AbcGeom::IPolyMeshSchema Schema;` — Schema extracted from Poly Mesh object
- L128 _protected member_ `FAbcMeshSample* FirstSample;` — Initial mesh sample for this object in first frame with available data
- L130 _protected member_ `FAbcMeshSample* TransformedFirstSample;` — Initial mesh sample for this object in first frame with available data, transformed by first available matrix
- L132 _protected member_ `FAbcMeshSample* ResidentSamples[MaxNumberOfResidentSamples];` — Resident set of Mesh Samples for this object, used for parallel reading of samples/frames
- L133 _protected member_ `bool ResidentVisibilitySamples[MaxNumberOfResidentSamples];`
- L135 _protected member_ `ESampleReadFlags SampleReadFlags;` — Bitmask read flag used for skipping constant vertex attributes while reading samples
- L138 _protected member_ `bool bReturnFirstSample;` — Whether or not to just return FirstSample
- L140 _protected member_ `bool bReturnTransformedFirstSample;` — Whether or not to just return the transformed FirstSample
- L142 _protected member_ `bool bFirstFrameVisibility;` — Whether or not the mesh is visible in the first Frame

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ALEMBICLIBRARY_API`

### `Plugins/Importers/AlembicImporter/Source/AlembicLibrary/Public/AbcTransform.h` (Public)


#### class `FAbcTransform`  
`class FAbcTransform : public IAbcObject`  
_L9-35_
- inherits: `IAbcObject`
- L12 _public prototype_ `FAbcTransform(const Alembic::AbcGeom::IXform& InTransform, const FAbcFile* InFile, IAbcObject* InParent = nullptr);`
- L13 _public prototype_ `virtual ~FAbcTransform() = default;`
- L16 _public prototype_ `virtual bool ReadFirstFrame(const float InTime, const int32 FrameIndex) final;` — Begin IAbcObject overrides
- L17 _public prototype_ `virtual void SetFrameAndTime(const float InTime, const int32 FrameIndex, const EFrameReadFlags InFlags, const int32 TargetIndex = INDEX_NONE) final;`
- L18 _public prototype_ `virtual FMatrix GetMatrix(const int32 FrameIndex) const final;`
- L19 _public prototype_ `virtual bool HasConstantTransform() const final;`
- L20 _public prototype_ `virtual void PurgeFrameData(const int32 FrameIndex) final;`
- L24 _public member_ `bool bConstantIdentity;` — Flag whether or not this transformation object is identity constant
- L27 _protected member_ `const Alembic::AbcGeom::IXform Transform;` — Alembic representation of this object
- L29 _protected member_ `const Alembic::AbcGeom::IXformSchema Schema;` — Schema extracted from transform object
- L32 _protected member_ `FMatrix InitialValue;` — Initial value for this object in first frame with available data
- L34 _protected member_ `FMatrix ResidentMatrices[MaxNumberOfResidentSamples];` — Resident set of matrix values for this object, used for parallel reading of samples/frames

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ALEMBICLIBRARY_API`

### `Plugins/Importers/AlembicImporter/Source/AlembicLibrary/Public/AbcUtilities.h` (Public)


#### class `FAbcUtilities`  
`class FAbcUtilities`  
_L14-24_
- L20 _public prototype_ `static void GetFrameMeshData(FAbcFile& AbcFile, int32 FrameIndex, FGeometryCacheMeshData& OutMeshData, int32 ConcurrencyIndex = 0);` — Populates a FGeometryCacheMeshData instance (with merged meshes) for the given frame of an Alembic with ConcurrencyIndex used as the concurrent read index
- L23 _public prototype_ `static void SetupGeometryCacheMaterials(FAbcFile& AbcFile, class UGeometryCache* GeometryCache, UObject* Package);` — Sets up materials from an AbcFile to a GeometryCache and moves them into the given package

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ALEMBICLIBRARY_API`

### `Plugins/Importers/AlembicImporter/Source/AlembicLibrary/Public/AlembicLibraryModule.h` (Public)


#### class `IAlembicLibraryModule`  
`class IAlembicLibraryModule : public IModuleInterface`  
_L7-30_
- inherits: `IModuleInterface`
- L16 _public function_ `static inline IAlembicLibraryModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L26 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
