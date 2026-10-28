# Plugins / RigLogicLibTest

- module root: `Plugins/Animation/RigLogic/Source/RigLogicLibTest`
- headers: 46; symbols: 2013
- symbol kinds: class=16, delegate=1, externvar=226, function=526, macro=76, member=902, namespace=59, prototype=90, struct=66, typedef=38, variable=13
- PublicDependencyModuleNames: Core, GoogleTest, RigLogicLib

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/arrayviewtests/Defs.h` (Private)


#### Free symbols / members of external scopes

- L24 _macro_ `#define INSTANTIATE_TEST_SUITE_P INSTANTIATE_TEST_CASE_P`
- L28 _macro_ `#define TYPED_TEST_SUITE_P TYPED_TEST_CASE_P`
- L32 _macro_ `#define REGISTER_TYPED_TEST_SUITE_P REGISTER_TYPED_TEST_CASE_P`
- L36 _macro_ `#define INSTANTIATE_TYPED_TEST_SUITE_P INSTANTIATE_TYPED_TEST_CASE_P`
- L40 _macro_ `#define ASSERT_ELEMENTS_EQ(result, expected, count) \`
- L47 _macro_ `#define EXPECT_ELEMENTS_EQ(result, expected, count) \`
- L54 _macro_ `#define ASSERT_ELEMENTS_NEAR(result, expected, count, threshold) \`
- L61 _macro_ `#define EXPECT_ELEMENTS_NEAR(result, expected, count, threshold) \`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/arrayviewtests/TestArrayView.h` (Private)


#### class `av::TestArrayView`  
`template<typename T> class TestArrayView : public ::testing::Test`  
_L23-52_
- inherits: `::testing::Test`
- L26 _public function_ `template<std::size_t size> std::array<T, size> initArray()`
- L35 _public function_ `template<std::size_t size> void initArray(T* ptr)`
- L42 _public function_ `template<std::size_t size> std::vector<T> initVector()`
- L48 _public function_ `template<typename U> bool equal(const ArrayView<U>& arr, T* ptr, const std::size_t size)`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace av`
- L56 _function_ `template<> template<std::size_t size> std::array<std::string, size> TestArrayView<std::string>::initArray()` (scope `av::TestArrayView::string`)
- L66 _function_ `template<> template<std::size_t size> void TestArrayView<std::string>::initArray(std::string* ptr)` (scope `av::TestArrayView::string`)
- L72 _typedef_ `using ValueTypes = ::testing::Types<int, int32_t, int64_t, float, double, std::string>;` (scope `av`)
- L73 _variable_ `constexpr std::size_t length{10};` (scope `av`)

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/arrayviewtests/Utils.h` (Private)


#### struct `true_sink`  
`template<typename> struct true_sink : std::true_type`  
_L17-17_
- inherits: `std::true_type`

#### Free symbols / members of external scopes

- L20 _prototype_ `template<typename T, typename... Args> static auto try_instantiate(std::int32_t , Args&&... args) -> true_sink<decltype(T{std::forward<Args>(args)...})>;`
- L23 _prototype_ `template<typename T, typename... Args> static auto try_instantiate(std::uint32_t , Args&&... ) -> std::false_type;`
- L30 _function_ `template<typename T, typename... Args> constexpr bool can_instantiate(Args&&... args)`
- L31 _typedef_ `using Result = decltype(try_instantiate<T>(0, std::forward<Args>(args)...));` (scope `can_instantiate`)

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/dnatests/Defs.h` (Private)


#### Free symbols / members of external scopes

- L24 _macro_ `#define INSTANTIATE_TEST_SUITE_P INSTANTIATE_TEST_CASE_P`
- L28 _macro_ `#define TYPED_TEST_SUITE_P TYPED_TEST_CASE_P`
- L32 _macro_ `#define REGISTER_TYPED_TEST_SUITE_P REGISTER_TYPED_TEST_CASE_P`
- L36 _macro_ `#define INSTANTIATE_TYPED_TEST_SUITE_P INSTANTIATE_TYPED_TEST_CASE_P`
- L40 _macro_ `#define ASSERT_ELEMENTS_EQ(result, expected, count) \`
- L47 _macro_ `#define EXPECT_ELEMENTS_EQ(result, expected, count) \`
- L54 _macro_ `#define ASSERT_ELEMENTS_NEAR(result, expected, count, threshold) \`
- L61 _macro_ `#define EXPECT_ELEMENTS_NEAR(result, expected, count, threshold) \`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/dnatests/FakeDNAReader.h` (Private)


#### class `dna::FakeDNAReader`  
`class FakeDNAReader : public Reader`  
_L22-777_
- inherits: `Reader`
- L24 _public prototype_ `~FakeDNAReader();`
- L27 _public function_ `std::uint16_t getFileFormatGeneration() const override` — HeaderReader methods
- L31 _public function_ `std::uint16_t getFileFormatVersion() const override`
- L36 _public function_ `StringView getName() const override` — DescriptorReader methods
- L40 _public function_ `Archetype getArchetype() const override`
- L44 _public function_ `Gender getGender() const override`
- L48 _public function_ `std::uint16_t getAge() const override`
- L52 _public function_ `std::uint32_t getMetaDataCount() const override`
- L56 _public function_ `StringView getMetaDataKey(std::uint32_t index) const override`
- L60 _public function_ `StringView getMetaDataValue(const char* key) const override`
- L64 _public function_ `TranslationUnit getTranslationUnit() const override`
- L68 _public function_ `RotationUnit getRotationUnit() const override`
- L72 _public function_ `CoordinateSystem getCoordinateSystem() const override`
- L76 _public function_ `RotationSequence getRotationSequence() const override`
- L80 _public function_ `RotationSign getRotationSign() const override`
- L84 _public function_ `FaceWindingOrder getFaceWindingOrder() const override`
- L88 _public function_ `std::uint16_t getLODCount() const override`
- L92 _public function_ `std::uint16_t getDBMaxLOD() const override`
- L96 _public function_ `StringView getDBComplexity() const override`
- L100 _public function_ `StringView getDBName() const override`
- L105 _public function_ `std::uint16_t getGUIControlCount() const override` — DefinitionReader methods
- L109 _public function_ `StringView getGUIControlName(std::uint16_t index) const override`
- L113 _public function_ `std::uint16_t getRawControlCount() const override`
- L117 _public function_ `StringView getRawControlName(std::uint16_t index) const override`
- L121 _public function_ `std::uint16_t getJointCount() const override`
- L125 _public function_ `StringView getJointName(std::uint16_t index) const override`
- L129 _public function_ `std::uint16_t getJointIndexListCount() const override`
- L133 _public function_ `ConstArrayView<std::uint16_t> getJointIndicesForLOD(std::uint16_t lod) const override`
- L137 _public function_ `std::uint16_t getJointParentIndex(std::uint16_t index) const override`
- L141 _public function_ `std::uint16_t getBlendShapeChannelCount() const override`
- L145 _public function_ `StringView getBlendShapeChannelName(std::uint16_t index) const override`
- L149 _public function_ `std::uint16_t getBlendShapeChannelIndexListCount() const override`
- L153 _public function_ `ConstArrayView<std::uint16_t> getBlendShapeChannelIndicesForLOD(std::uint16_t lod) const override`
- L157 _public function_ `std::uint16_t getAnimatedMapCount() const override`
- L161 _public function_ `std::uint16_t getAnimatedMapIndexListCount() const override`
- L165 _public function_ `ConstArrayView<std::uint16_t> getAnimatedMapIndicesForLOD(std::uint16_t lod) const override`
- L169 _public function_ `StringView getAnimatedMapName(std::uint16_t index) const override`
- L173 _public function_ `std::uint16_t getMeshCount() const override`
- L177 _public function_ `StringView getMeshName(std::uint16_t index) const override`
- L181 _public function_ `std::uint16_t getMeshBlendShapeChannelMappingCount() const override`
- L185 _public function_ `MeshBlendShapeChannelMapping getMeshBlendShapeChannelMapping(std::uint16_t index) const override`
- L189 _public function_ `ConstArrayView<std::uint16_t> getMeshBlendShapeChannelMappingIndicesForLOD(std::uint16_t lod) const override`
- L193 _public function_ `std::uint16_t getMeshIndexListCount() const override`
- L197 _public function_ `ConstArrayView<std::uint16_t> getMeshIndicesForLOD(std::uint16_t lod) const override`
- L201 _public function_ `Vector3 getNeutralJointTranslation(std::uint16_t index) const override`
- L205 _public function_ `ConstArrayView<float> getNeutralJointTranslationXs() const override`
- L209 _public function_ `ConstArrayView<float> getNeutralJointTranslationYs() const override`
- L213 _public function_ `ConstArrayView<float> getNeutralJointTranslationZs() const override`
- L217 _public function_ `Vector3 getNeutralJointRotation(std::uint16_t index) const override`
- L221 _public function_ `ConstArrayView<float> getNeutralJointRotationXs() const override`
- L225 _public function_ `ConstArrayView<float> getNeutralJointRotationYs() const override`
- L229 _public function_ `ConstArrayView<float> getNeutralJointRotationZs() const override`
- L234 _public function_ `ConstArrayView<std::uint16_t> getGUIToRawInputIndices() const override` — BehaviorReader methods
- L238 _public function_ `ConstArrayView<std::uint16_t> getGUIToRawOutputIndices() const override`
- L242 _public function_ `ConstArrayView<float> getGUIToRawFromValues() const override`
- L246 _public function_ `ConstArrayView<float> getGUIToRawToValues() const override`
- L250 _public function_ `ConstArrayView<float> getGUIToRawSlopeValues() const override`
- L254 _public function_ `ConstArrayView<float> getGUIToRawCutValues() const override`
- L258 _public function_ `std::uint16_t getPSDCount() const override`
- L262 _public function_ `ConstArrayView<std::uint16_t> getPSDRowIndices() const override`
- L266 _public function_ `ConstArrayView<std::uint16_t> getPSDColumnIndices() const override`
- L270 _public function_ `ConstArrayView<float> getPSDValues() const override`
- L274 _public function_ `ConstArrayView<std::uint16_t> getJointVariableAttributeIndices(std::uint16_t lod) const override`
- L278 _public function_ `std::uint16_t getJointRowCount() const override`
- L282 _public function_ `std::uint16_t getJointColumnCount() const override`
- L286 _public function_ `std::uint16_t getJointGroupCount() const override`
- L290 _public function_ `ConstArrayView<std::uint16_t> getJointGroupLODs(std::uint16_t jointGroupIndex) const override`
- L294 _public function_ `ConstArrayView<std::uint16_t> getJointGroupInputIndices(std::uint16_t jointGroupIndex) const override`
- L298 _public function_ `ConstArrayView<std::uint16_t> getJointGroupOutputIndices(std::uint16_t jointGroupIndex) const override`
- L302 _public function_ `ConstArrayView<float> getJointGroupValues(std::uint16_t jointGroupIndex) const override`
- L306 _public function_ `ConstArrayView<std::uint16_t> getJointGroupJointIndices(std::uint16_t jointGroupIndex) const override`
- L310 _public function_ `ConstArrayView<std::uint16_t> getBlendShapeChannelLODs() const override`
- L314 _public function_ `ConstArrayView<std::uint16_t> getBlendShapeChannelInputIndices() const override`
- L318 _public function_ `ConstArrayView<std::uint16_t> getBlendShapeChannelOutputIndices() const override`
- L322 _public function_ `ConstArrayView<std::uint16_t> getAnimatedMapLODs() const override`
- L326 _public function_ `ConstArrayView<std::uint16_t> getAnimatedMapInputIndices() const override`
- L330 _public function_ `ConstArrayView<std::uint16_t> getAnimatedMapOutputIndices() const override`
- L334 _public function_ `ConstArrayView<float> getAnimatedMapFromValues() const override`
- L338 _public function_ `ConstArrayView<float> getAnimatedMapToValues() const override`
- L342 _public function_ `ConstArrayView<float> getAnimatedMapSlopeValues() const override`
- L346 _public function_ `ConstArrayView<float> getAnimatedMapCutValues() const override`
- L351 _public function_ `std::uint32_t getVertexPositionCount(std::uint16_t meshIndex) const override` — GeometryReader methods
- L355 _public function_ `Position getVertexPosition(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L359 _public function_ `ConstArrayView<float> getVertexPositionXs(std::uint16_t meshIndex) const override`
- L363 _public function_ `ConstArrayView<float> getVertexPositionYs(std::uint16_t meshIndex) const override`
- L367 _public function_ `ConstArrayView<float> getVertexPositionZs(std::uint16_t meshIndex) const override`
- L371 _public function_ `std::uint32_t getVertexTextureCoordinateCount(std::uint16_t meshIndex) const override`
- L375 _public function_ `TextureCoordinate getVertexTextureCoordinate(std::uint16_t meshIndex, std::uint32_t textureCoordinateIndex) const override`
- L379 _public function_ `ConstArrayView<float> getVertexTextureCoordinateUs(std::uint16_t meshIndex) const override`
- L383 _public function_ `ConstArrayView<float> getVertexTextureCoordinateVs(std::uint16_t meshIndex) const override`
- L387 _public function_ `std::uint32_t getVertexNormalCount(std::uint16_t meshIndex) const override`
- L391 _public function_ `Normal getVertexNormal(std::uint16_t meshIndex, std::uint32_t normalIndex) const override`
- L395 _public function_ `ConstArrayView<float> getVertexNormalXs(std::uint16_t meshIndex) const override`
- L399 _public function_ `ConstArrayView<float> getVertexNormalYs(std::uint16_t meshIndex) const override`
- L403 _public function_ `ConstArrayView<float> getVertexNormalZs(std::uint16_t meshIndex) const override`
- L407 _public function_ `std::uint32_t getFaceCount(std::uint16_t meshIndex) const override`
- L411 _public function_ `ConstArrayView<std::uint32_t> getFaceVertexLayoutIndices(std::uint16_t meshIndex, std::uint32_t faceIndex) const override`
- L415 _public function_ `std::uint32_t getVertexLayoutCount(std::uint16_t meshIndex) const override`
- L419 _public function_ `VertexLayout getVertexLayout(std::uint16_t meshIndex, std::uint32_t layoutIndex) const override`
- L423 _public function_ `ConstArrayView<std::uint32_t> getVertexLayoutPositionIndices(std::uint16_t meshIndex) const override`
- L427 _public function_ `ConstArrayView<std::uint32_t> getVertexLayoutTextureCoordinateIndices(std::uint16_t meshIndex) const override`
- L431 _public function_ `ConstArrayView<std::uint32_t> getVertexLayoutNormalIndices(std::uint16_t meshIndex) const override`
- L435 _public function_ `std::uint16_t getMaximumInfluencePerVertex(std::uint16_t meshIndex) const override`
- L439 _public function_ `std::uint32_t getSkinWeightsCount(std::uint16_t meshIndex) const override`
- L443 _public function_ `ConstArrayView<float> getSkinWeightsValues(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L447 _public function_ `ConstArrayView<std::uint16_t> getSkinWeightsJointIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L451 _public function_ `std::uint16_t getBlendShapeTargetCount(std::uint16_t meshIndex) const override`
- L455 _public function_ `std::uint16_t getBlendShapeChannelIndex(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L459 _public function_ `std::uint32_t getBlendShapeTargetDeltaCount(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L463 _public function_ `Delta getBlendShapeTargetDelta(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, std::uint32_t deltaIndex) const override`
- L469 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaXs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L474 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaYs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L479 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaZs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L484 _public function_ `ConstArrayView<std::uint32_t> getBlendShapeTargetVertexIndices(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L490 _public function_ `std::uint16_t getMLControlCount() const override` — MachineLearnedBehaviorReader methods
- L494 _public function_ `StringView getMLControlName(std::uint16_t index) const override`
- L498 _public function_ `std::uint16_t getNeuralNetworkCount() const override`
- L502 _public function_ `std::uint16_t getNeuralNetworkIndexListCount() const override`
- L506 _public function_ `ConstArrayView<std::uint16_t> getNeuralNetworkIndicesForLOD(std::uint16_t lod) const override`
- L510 _public function_ `std::uint16_t getMeshRegionCount(std::uint16_t meshIndex) const override`
- L514 _public function_ `StringView getMeshRegionName(std::uint16_t meshIndex, std::uint16_t regionIndex) const override`
- L518 _public function_ `ConstArrayView<std::uint16_t> getNeuralNetworkIndicesForMeshRegion(std::uint16_t meshIndex, std::uint16_t regionIndex) const override`
- L523 _public function_ `ConstArrayView<std::uint16_t> getNeuralNetworkInputIndices(std::uint16_t neuralNetIndex) const override`
- L527 _public function_ `ConstArrayView<std::uint16_t> getNeuralNetworkOutputIndices(std::uint16_t neuralNetIndex) const override`
- L531 _public function_ `std::uint16_t getNeuralNetworkLayerCount(std::uint16_t neuralNetIndex) const override`
- L535 _public function_ `ActivationFunction getNeuralNetworkLayerActivationFunction(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L540 _public function_ `ConstArrayView<float> getNeuralNetworkLayerActivationFunctionParameters(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L545 _public function_ `ConstArrayView<float> getNeuralNetworkLayerBiases(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L549 _public function_ `ConstArrayView<float> getNeuralNetworkLayerWeights(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L553 _public function_ `std::uint16_t getRBFPoseCount() const override`
- L557 _public function_ `StringView getRBFPoseName(std::uint16_t poseIndex) const override`
- L561 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseJointOutputIndices(std::uint16_t poseIndex) const override`
- L565 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseBlendShapeChannelOutputIndices(std::uint16_t poseIndex) const override`
- L569 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseAnimatedMapOutputIndices(std::uint16_t poseIndex) const override`
- L573 _public function_ `ConstArrayView<float> getRBFPoseJointOutputValues(std::uint16_t poseIndex) const override`
- L577 _public function_ `float getRBFPoseScale(std::uint16_t poseIndex) const override`
- L581 _public function_ `std::uint16_t getRBFPoseControlCount() const override`
- L585 _public function_ `StringView getRBFPoseControlName(std::uint16_t poseControlIndex) const override`
- L589 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseInputControlIndices(std::uint16_t poseIndex) const override`
- L593 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseOutputControlIndices(std::uint16_t poseIndex) const override`
- L597 _public function_ `ConstArrayView<float> getRBFPoseOutputControlWeights(std::uint16_t poseIndex) const override`
- L601 _public function_ `std::uint16_t getRBFSolverCount() const override`
- L605 _public function_ `std::uint16_t getRBFSolverIndexListCount() const override`
- L609 _public function_ `ConstArrayView<std::uint16_t> getRBFSolverIndicesForLOD(std::uint16_t lod) const override`
- L613 _public function_ `StringView getRBFSolverName(std::uint16_t solverIndex) const override`
- L617 _public function_ `ConstArrayView<std::uint16_t> getRBFSolverRawControlIndices(std::uint16_t solverIndex) const override`
- L621 _public function_ `ConstArrayView<std::uint16_t> getRBFSolverPoseIndices(std::uint16_t solverIndex) const override`
- L625 _public function_ `ConstArrayView<float> getRBFSolverRawControlValues(std::uint16_t solverIndex) const override`
- L629 _public function_ `RBFSolverType getRBFSolverType(std::uint16_t solverIndex) const override`
- L633 _public function_ `float getRBFSolverRadius(std::uint16_t solverIndex) const override`
- L637 _public function_ `AutomaticRadius getRBFSolverAutomaticRadius(std::uint16_t solverIndex) const override`
- L641 _public function_ `float getRBFSolverWeightThreshold(std::uint16_t solverIndex) const override`
- L645 _public function_ `RBFDistanceMethod getRBFSolverDistanceMethod(std::uint16_t solverIndex) const override`
- L649 _public function_ `RBFNormalizeMethod getRBFSolverNormalizeMethod(std::uint16_t solverIndex) const override`
- L653 _public function_ `RBFFunctionType getRBFSolverFunctionType(std::uint16_t solverIndex) const override`
- L657 _public function_ `TwistAxis getRBFSolverTwistAxis(std::uint16_t solverIndex) const override`
- L661 _public function_ `TranslationRepresentation getJointTranslationRepresentation(std::uint16_t jointIndex) const override`
- L665 _public function_ `RotationRepresentation getJointRotationRepresentation(std::uint16_t jointIndex) const override`
- L669 _public function_ `ScaleRepresentation getJointScaleRepresentation(std::uint16_t jointIndex) const override`
- L673 _public function_ `std::uint16_t getTwistCount() const override`
- L677 _public function_ `TwistAxis getTwistSetupTwistAxis(std::uint16_t twistIndex) const override`
- L681 _public function_ `ConstArrayView<std::uint16_t> getTwistInputControlIndices(std::uint16_t twistIndex) const override`
- L685 _public function_ `ConstArrayView<std::uint16_t> getTwistOutputJointIndices(std::uint16_t twistIndex) const override`
- L689 _public function_ `ConstArrayView<float> getTwistBlendWeights(std::uint16_t twistIndex) const override`
- L693 _public function_ `std::uint16_t getSwingCount() const override`
- L697 _public function_ `TwistAxis getSwingSetupTwistAxis(std::uint16_t swingIndex) const override`
- L701 _public function_ `ConstArrayView<std::uint16_t> getSwingInputControlIndices(std::uint16_t swingIndex) const override`
- L705 _public function_ `ConstArrayView<std::uint16_t> getSwingOutputJointIndices(std::uint16_t swingIndex) const override`
- L709 _public function_ `ConstArrayView<float> getSwingBlendWeights(std::uint16_t swingIndex) const override`
- L713 _public function_ `std::uint16_t getMLTypeCount() const override`
- L717 _public function_ `std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const override`
- L721 _public function_ `std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override`
- L725 _public function_ `MachineLearnedBehaviorOperationType getMLOperationType(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L731 _public function_ `ConstArrayView<std::uint32_t> getMLOperationParameters(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L737 _public function_ `ConstArrayView<std::uint16_t> getMLOperationDependencyOperationSetIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L743 _public function_ `ConstArrayView<std::uint16_t> getMLOperationDependencyOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L749 _public function_ `std::uint16_t getMLOperationIndexListCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override`
- L753 _public function_ `ConstArrayView<std::uint16_t> getMLOperationIndicesForLOD(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t lod) const override`
- L759 _public function_ `ConstArrayView<std::uint16_t> getMLJointsInputIndices() const override`
- L763 _public function_ `ConstArrayView<std::uint16_t> getMLJointsOutputIndices() const override`
- L767 _public function_ `ConstArrayView<std::uint16_t> getMLJointsParameterKeys() const override`
- L771 _public function_ `ConstArrayView<std::uint16_t> getMLJointsParameterValues() const override`
- L775 _public function_ `void unload(DataLayer layer) override`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/dnatests/FixturesJSON.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`
- L14 _externvar_ `extern const char* jsonDNA;` (scope `dna`)

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/dnatests/Fixturesv21.h` (Private)


#### struct `dna::RawV21`  
`struct RawV21`  
_L14-28_
- L15 _public member_ `static const unsigned char header[39];`
- L16 _public member_ `static const unsigned char descriptor[87];`
- L17 _public member_ `static const unsigned char definition[794];`
- L18 _public member_ `static const unsigned char controls[2];`
- L19 _public member_ `static const unsigned char conditionals[324];`
- L20 _public member_ `static const unsigned char psds[204];`
- L21 _public member_ `static const unsigned char joints[444];`
- L22 _public member_ `static const unsigned char blendshapes[44];`
- L23 _public member_ `static const unsigned char animatedmaps[8];`
- L24 _public member_ `static const unsigned char geometry[1080];`
- L25 _public member_ `static const unsigned char footer[3];`
- L27 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::DecodedV21`  
`struct DecodedV21`  
_L30-111_
- L31 _public typedef_ `using VectorOfCharStringMatrix = pma::Vector<pma::Matrix<pma::String<char>>>;`
- L32 _public typedef_ `using StringPair = std::pair<pma::String<char>, pma::String<char>>;`
- L35 _public member_ `static const pma::String<char> name;` — Descriptor
- L36 _public member_ `static const Archetype archetype;`
- L37 _public member_ `static const Gender gender;`
- L38 _public member_ `static const std::uint16_t age;`
- L40 _public member_ `static const pma::Vector<StringPair> metadata;`
- L41 _public member_ `static const TranslationUnit translationUnit;`
- L42 _public member_ `static const RotationUnit rotationUnit;`
- L43 _public member_ `static const CoordinateSystem coordinateSystem;`
- L44 _public member_ `static const std::uint16_t lodCount[3ul];`
- L45 _public member_ `static const std::uint16_t maxLODs[3ul];`
- L46 _public member_ `static const pma::String<char> complexity;`
- L47 _public member_ `static const pma::String<char> dbName;`
- L50 _public member_ `static const pma::Vector<pma::String<char>> guiControlNames;` — Definition
- L51 _public member_ `static const pma::Vector<pma::String<char>> rawControlNames;`
- L52 _public member_ `static const VectorOfCharStringMatrix jointNames;`
- L53 _public member_ `static const VectorOfCharStringMatrix blendShapeNames;`
- L54 _public member_ `static const VectorOfCharStringMatrix animatedMapNames;`
- L55 _public member_ `static const VectorOfCharStringMatrix meshNames;`
- L56 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> meshBlendShapeIndices;`
- L57 _public member_ `static const pma::Matrix<std::uint16_t> jointHierarchy;`
- L58 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> neutralJointTranslations;`
- L59 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> neutralJointRotations;`
- L62 _public member_ `static const std::uint16_t guiControlCount;` — Behavior
- L63 _public member_ `static const std::uint16_t rawControlCount;`
- L64 _public member_ `static const std::uint16_t psdCount;`
- L65 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> conditionalInputIndices;`
- L66 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> conditionalOutputIndices;`
- L67 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalFromValues;`
- L68 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalToValues;`
- L69 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalSlopeValues;`
- L70 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalCutValues;`
- L71 _public member_ `static const pma::Vector<std::uint16_t> psdRowIndices;`
- L72 _public member_ `static const pma::Vector<std::uint16_t> psdColumnIndices;`
- L73 _public member_ `static const pma::Vector<float> psdValues;`
- L74 _public member_ `static const pma::Vector<std::uint16_t> jointRowCount;`
- L75 _public member_ `static const std::uint16_t jointColumnCount;`
- L76 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> jointVariableIndices;`
- L77 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> jointGroupLODs;`
- L78 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupInputIndices;`
- L79 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupOutputIndices;`
- L80 _public member_ `static const pma::Matrix<pma::Matrix<float>> jointGroupValues;`
- L81 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupJointIndices;`
- L82 _public member_ `static const pma::Matrix<std::uint16_t> blendShapeLODs;`
- L83 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> blendShapeInputIndices;`
- L84 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> blendShapeOutputIndices;`
- L85 _public member_ `static const pma::Vector<std::uint16_t> animatedMapCount;`
- L86 _public member_ `static const pma::Matrix<std::uint16_t> animatedMapLODs;`
- L89 _public member_ `static const pma::Vector<std::uint32_t> meshCount;` — Geometry
- L90 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> vertexPositions;`
- L91 _public member_ `static const pma::Vector<pma::Matrix<TextureCoordinate>> vertexTextureCoordinates;`
- L92 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> vertexNormals;`
- L93 _public member_ `static const pma::Vector<pma::Matrix<VertexLayout>> vertexLayouts;`
- L94 _public member_ `static const pma::Matrix<pma::Matrix<std::uint32_t>> faces;`
- L95 _public member_ `static const pma::Matrix<std::uint16_t> maxInfluencePerVertex;`
- L96 _public member_ `static const pma::Matrix<pma::Matrix<float>> skinWeightsValues;`
- L97 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> skinWeightsJointIndices;`
- L98 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> correctiveBlendShapeIndices;`
- L99 _public member_ `static const pma::Matrix<pma::Matrix<Vector3>> correctiveBlendShapeDeltas;`
- L100 _public member_ `static const pma::Matrix<pma::Matrix<std::uint32_t>> correctiveBlendShapeVertexIndices;`
- L102 _public prototype_ `static std::size_t lodConstraintToIndex(std::uint16_t maxLOD, std::uint16_t minLOD);`
- L103 _public prototype_ `static RawJoints getJoints(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L104 _public prototype_ `static RawBlendShapeChannels getBlendShapes(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L107 _public prototype_ `static RawConditionalTable getConditionals(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L110 _public prototype_ `static RawAnimatedMaps getAnimatedMaps(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/dnatests/Fixturesv22.h` (Private)


#### struct `dna::RawV22`  
`struct RawV22`  
_L14-29_
- L15 _public member_ `static const unsigned char header[107];`
- L16 _public member_ `static const unsigned char descriptor[87];`
- L17 _public member_ `static const unsigned char definition[794];`
- L18 _public member_ `static const unsigned char controls[2];`
- L19 _public member_ `static const unsigned char conditionals[324];`
- L20 _public member_ `static const unsigned char psds[204];`
- L21 _public member_ `static const unsigned char joints[444];`
- L22 _public member_ `static const unsigned char blendshapes[44];`
- L23 _public member_ `static const unsigned char animatedmaps[8];`
- L24 _public member_ `static const unsigned char geometry[1080];`
- L25 _public member_ `static const unsigned char unknownLayer1[16];`
- L26 _public member_ `static const unsigned char unknownLayer2[32];`
- L28 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::RawV22WithUnknownDataIgnoredAndDNARewritten`  
`struct RawV22WithUnknownDataIgnoredAndDNARewritten`  
_L31-35_
- L32 _public member_ `static const unsigned char header[75];`
- L34 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::RawV2xNewer`  
`struct RawV2xNewer`  
_L37-47_
- L38 _public member_ `static const unsigned char header[107];`
- L39 _public member_ `static const unsigned char unknownDescriptor[16];`
- L40 _public member_ `static const unsigned char unknownDefinition[16];`
- L41 _public member_ `static const unsigned char unknownBehavior[32];`
- L42 _public member_ `static const unsigned char unknownGeometry[32];`
- L43 _public member_ `static const unsigned char unknownCustom1[16];`
- L44 _public member_ `static const unsigned char unknownCustom2[32];`
- L46 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::RawV2xNewerWithUnknownDataPreservedAndDNARewritten`  
`struct RawV2xNewerWithUnknownDataPreservedAndDNARewritten`  
_L49-64_
- L50 _public member_ `static const unsigned char header[283];`
- L51 _public member_ `static const unsigned char descriptor[36];`
- L52 _public member_ `static const unsigned char definition[92];`
- L53 _public member_ `static const unsigned char behavior[86];`
- L54 _public member_ `static const unsigned char geometry[4];`
- L55 _public member_ `static const unsigned char machineLearnedBehavior[24];`
- L56 _public member_ `static const unsigned char rbfBehavior[16];`
- L57 _public member_ `static const unsigned char rbfBehaviorExt[8];`
- L58 _public member_ `static const unsigned char jointBehaviorMetaData[4];`
- L59 _public member_ `static const unsigned char twistSwingBehavior[8];`
- L60 _public member_ `static const unsigned char machineLearnedBehaviorExt[20];`
- L61 _public member_ `static const unsigned char descriptorExt[17];`
- L63 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::RawV2xNewerWithUnknownDataIgnoredAndDNARewritten`  
`struct RawV2xNewerWithUnknownDataIgnoredAndDNARewritten`  
_L66-70_
- L67 _public member_ `static const unsigned char header[187];`
- L69 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::RawV22Empty`  
`struct RawV22Empty`  
_L72-76_
- L73 _public member_ `static const unsigned char header[75];`
- L75 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::RawV22WithUnknownDataFromNewer2x`  
`struct RawV22WithUnknownDataFromNewer2x`  
_L78-82_
- L79 _public member_ `static const unsigned char header[171];`
- L81 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::DecodedV22`  
`struct DecodedV22`  
_L84-165_
- L85 _public typedef_ `using VectorOfCharStringMatrix = pma::Vector<pma::Matrix<pma::String<char>>>;`
- L86 _public typedef_ `using StringPair = std::pair<pma::String<char>, pma::String<char>>;`
- L89 _public member_ `static const pma::String<char> name;` — Descriptor
- L90 _public member_ `static const Archetype archetype;`
- L91 _public member_ `static const Gender gender;`
- L92 _public member_ `static const std::uint16_t age;`
- L94 _public member_ `static const pma::Vector<StringPair> metadata;`
- L95 _public member_ `static const TranslationUnit translationUnit;`
- L96 _public member_ `static const RotationUnit rotationUnit;`
- L97 _public member_ `static const CoordinateSystem coordinateSystem;`
- L98 _public member_ `static const std::uint16_t lodCount[3ul];`
- L99 _public member_ `static const std::uint16_t maxLODs[3ul];`
- L100 _public member_ `static const pma::String<char> complexity;`
- L101 _public member_ `static const pma::String<char> dbName;`
- L104 _public member_ `static const pma::Vector<pma::String<char>> guiControlNames;` — Definition
- L105 _public member_ `static const pma::Vector<pma::String<char>> rawControlNames;`
- L106 _public member_ `static const VectorOfCharStringMatrix jointNames;`
- L107 _public member_ `static const VectorOfCharStringMatrix blendShapeNames;`
- L108 _public member_ `static const VectorOfCharStringMatrix animatedMapNames;`
- L109 _public member_ `static const VectorOfCharStringMatrix meshNames;`
- L110 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> meshBlendShapeIndices;`
- L111 _public member_ `static const pma::Matrix<std::uint16_t> jointHierarchy;`
- L112 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> neutralJointTranslations;`
- L113 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> neutralJointRotations;`
- L116 _public member_ `static const std::uint16_t guiControlCount;` — Behavior
- L117 _public member_ `static const std::uint16_t rawControlCount;`
- L118 _public member_ `static const std::uint16_t psdCount;`
- L119 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> conditionalInputIndices;`
- L120 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> conditionalOutputIndices;`
- L121 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalFromValues;`
- L122 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalToValues;`
- L123 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalSlopeValues;`
- L124 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalCutValues;`
- L125 _public member_ `static const pma::Vector<std::uint16_t> psdRowIndices;`
- L126 _public member_ `static const pma::Vector<std::uint16_t> psdColumnIndices;`
- L127 _public member_ `static const pma::Vector<float> psdValues;`
- L128 _public member_ `static const pma::Vector<std::uint16_t> jointRowCount;`
- L129 _public member_ `static const std::uint16_t jointColumnCount;`
- L130 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> jointVariableIndices;`
- L131 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> jointGroupLODs;`
- L132 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupInputIndices;`
- L133 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupOutputIndices;`
- L134 _public member_ `static const pma::Matrix<pma::Matrix<float>> jointGroupValues;`
- L135 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupJointIndices;`
- L136 _public member_ `static const pma::Matrix<std::uint16_t> blendShapeLODs;`
- L137 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> blendShapeInputIndices;`
- L138 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> blendShapeOutputIndices;`
- L139 _public member_ `static const pma::Vector<std::uint16_t> animatedMapCount;`
- L140 _public member_ `static const pma::Matrix<std::uint16_t> animatedMapLODs;`
- L143 _public member_ `static const pma::Vector<std::uint32_t> meshCount;` — Geometry
- L144 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> vertexPositions;`
- L145 _public member_ `static const pma::Vector<pma::Matrix<TextureCoordinate>> vertexTextureCoordinates;`
- L146 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> vertexNormals;`
- L147 _public member_ `static const pma::Vector<pma::Matrix<VertexLayout>> vertexLayouts;`
- L148 _public member_ `static const pma::Matrix<pma::Matrix<std::uint32_t>> faces;`
- L149 _public member_ `static const pma::Matrix<std::uint16_t> maxInfluencePerVertex;`
- L150 _public member_ `static const pma::Matrix<pma::Matrix<float>> skinWeightsValues;`
- L151 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> skinWeightsJointIndices;`
- L152 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> correctiveBlendShapeIndices;`
- L153 _public member_ `static const pma::Matrix<pma::Matrix<Vector3>> correctiveBlendShapeDeltas;`
- L154 _public member_ `static const pma::Matrix<pma::Matrix<std::uint32_t>> correctiveBlendShapeVertexIndices;`
- L156 _public prototype_ `static std::size_t lodConstraintToIndex(std::uint16_t maxLOD, std::uint16_t minLOD);`
- L157 _public prototype_ `static RawJoints getJoints(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L158 _public prototype_ `static RawBlendShapeChannels getBlendShapes(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L161 _public prototype_ `static RawConditionalTable getConditionals(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L164 _public prototype_ `static RawAnimatedMaps getAnimatedMaps(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/dnatests/Fixturesv23.h` (Private)


#### struct `dna::RawV23`  
`struct RawV23`  
_L14-28_
- L15 _public member_ `static const unsigned char header[91];`
- L16 _public member_ `static const unsigned char descriptor[87];`
- L17 _public member_ `static const unsigned char definition[794];`
- L18 _public member_ `static const unsigned char controls[2];`
- L19 _public member_ `static const unsigned char conditionals[324];`
- L20 _public member_ `static const unsigned char psds[204];`
- L21 _public member_ `static const unsigned char joints[444];`
- L22 _public member_ `static const unsigned char blendshapes[44];`
- L23 _public member_ `static const unsigned char animatedmaps[8];`
- L24 _public member_ `static const unsigned char geometry[1080];`
- L25 _public member_ `static const unsigned char machineLearnedBehavior[762];`
- L27 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::RawV22DowngradedFromV23`  
`struct RawV22DowngradedFromV23`  
_L30-32_
- L31 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::DecodedV23`  
`struct DecodedV23`  
_L34-128_
- L35 _public typedef_ `using VectorOfCharStringMatrix = pma::Vector<pma::Matrix<pma::String<char>>>;`
- L36 _public typedef_ `using StringPair = std::pair<pma::String<char>, pma::String<char>>;`
- L39 _public member_ `static const pma::String<char> name;` — Descriptor
- L40 _public member_ `static const Archetype archetype;`
- L41 _public member_ `static const Gender gender;`
- L42 _public member_ `static const std::uint16_t age;`
- L44 _public member_ `static const pma::Vector<StringPair> metadata;`
- L45 _public member_ `static const TranslationUnit translationUnit;`
- L46 _public member_ `static const RotationUnit rotationUnit;`
- L47 _public member_ `static const CoordinateSystem coordinateSystem;`
- L48 _public member_ `static const std::uint16_t lodCount[3ul];`
- L49 _public member_ `static const std::uint16_t maxLODs[3ul];`
- L50 _public member_ `static const pma::String<char> complexity;`
- L51 _public member_ `static const pma::String<char> dbName;`
- L54 _public member_ `static const pma::Vector<pma::String<char>> guiControlNames;` — Definition
- L55 _public member_ `static const pma::Vector<pma::String<char>> rawControlNames;`
- L56 _public member_ `static const VectorOfCharStringMatrix jointNames;`
- L57 _public member_ `static const VectorOfCharStringMatrix blendShapeNames;`
- L58 _public member_ `static const VectorOfCharStringMatrix animatedMapNames;`
- L59 _public member_ `static const VectorOfCharStringMatrix meshNames;`
- L60 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> meshBlendShapeIndices;`
- L61 _public member_ `static const pma::Matrix<std::uint16_t> jointHierarchy;`
- L62 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> neutralJointTranslations;`
- L63 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> neutralJointRotations;`
- L66 _public member_ `static const std::uint16_t guiControlCount;` — Behavior
- L67 _public member_ `static const std::uint16_t rawControlCount;`
- L68 _public member_ `static const std::uint16_t psdCount;`
- L69 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> conditionalInputIndices;`
- L70 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> conditionalOutputIndices;`
- L71 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalFromValues;`
- L72 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalToValues;`
- L73 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalSlopeValues;`
- L74 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalCutValues;`
- L75 _public member_ `static const pma::Vector<std::uint16_t> psdRowIndices;`
- L76 _public member_ `static const pma::Vector<std::uint16_t> psdColumnIndices;`
- L77 _public member_ `static const pma::Vector<float> psdValues;`
- L78 _public member_ `static const pma::Vector<std::uint16_t> jointRowCount;`
- L79 _public member_ `static const std::uint16_t jointColumnCount;`
- L80 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> jointVariableIndices;`
- L81 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> jointGroupLODs;`
- L82 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupInputIndices;`
- L83 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupOutputIndices;`
- L84 _public member_ `static const pma::Matrix<pma::Matrix<float>> jointGroupValues;`
- L85 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupJointIndices;`
- L86 _public member_ `static const pma::Matrix<std::uint16_t> blendShapeLODs;`
- L87 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> blendShapeInputIndices;`
- L88 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> blendShapeOutputIndices;`
- L89 _public member_ `static const pma::Vector<std::uint16_t> animatedMapCount;`
- L90 _public member_ `static const pma::Matrix<std::uint16_t> animatedMapLODs;`
- L93 _public member_ `static const pma::Vector<std::uint32_t> meshCount;` — Geometry
- L94 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> vertexPositions;`
- L95 _public member_ `static const pma::Vector<pma::Matrix<TextureCoordinate>> vertexTextureCoordinates;`
- L96 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> vertexNormals;`
- L97 _public member_ `static const pma::Vector<pma::Matrix<VertexLayout>> vertexLayouts;`
- L98 _public member_ `static const pma::Matrix<pma::Matrix<std::uint32_t>> faces;`
- L99 _public member_ `static const pma::Matrix<std::uint16_t> maxInfluencePerVertex;`
- L100 _public member_ `static const pma::Matrix<pma::Matrix<float>> skinWeightsValues;`
- L101 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> skinWeightsJointIndices;`
- L102 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> correctiveBlendShapeIndices;`
- L103 _public member_ `static const pma::Matrix<pma::Matrix<Vector3>> correctiveBlendShapeDeltas;`
- L104 _public member_ `static const pma::Matrix<pma::Matrix<std::uint32_t>> correctiveBlendShapeVertexIndices;`
- L107 _public member_ `static const pma::Vector<pma::String<char>> mlControlNames;` — Machine learned behavior
- L108 _public member_ `static const VectorOfCharStringMatrix regionNames;`
- L109 _public member_ `static const pma::Matrix<std::uint16_t> neuralNetworkIndicesPerLOD;`
- L110 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> neuralNetworkIndicesPerMeshRegion;`
- L111 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkInputIndices;`
- L112 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkOutputIndices;`
- L113 _public member_ `static const pma::Matrix<std::uint16_t> neuralNetworkLayerCount;`
- L114 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkActivationFunction;`
- L115 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkActivationFunctionParameters;`
- L116 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkBiases;`
- L117 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkWeights;`
- L119 _public prototype_ `static std::size_t lodConstraintToIndex(std::uint16_t maxLOD, std::uint16_t minLOD);`
- L120 _public prototype_ `static RawJoints getJoints(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L121 _public prototype_ `static RawBlendShapeChannels getBlendShapes(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L124 _public prototype_ `static RawConditionalTable getConditionals(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L127 _public prototype_ `static RawAnimatedMaps getAnimatedMaps(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/dnatests/Fixturesv24.h` (Private)


#### struct `dna::RawV24`  
`struct RawV24`  
_L14-31_
- L15 _public member_ `static const unsigned char header[139];`
- L16 _public member_ `static const unsigned char descriptor[87];`
- L17 _public member_ `static const unsigned char definition[794];`
- L18 _public member_ `static const unsigned char controls[2];`
- L19 _public member_ `static const unsigned char conditionals[324];`
- L20 _public member_ `static const unsigned char psds[204];`
- L21 _public member_ `static const unsigned char joints[444];`
- L22 _public member_ `static const unsigned char blendshapes[44];`
- L23 _public member_ `static const unsigned char animatedmaps[8];`
- L24 _public member_ `static const unsigned char geometry[1080];`
- L25 _public member_ `static const unsigned char machineLearnedBehavior[762];`
- L26 _public member_ `static const unsigned char rbfBehavior[327];`
- L27 _public member_ `static const unsigned char jointBehaviorMetadata[58];`
- L28 _public member_ `static const unsigned char twistSwingBehavior[200];`
- L30 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::RawV23DowngradedFromV24`  
`struct RawV23DowngradedFromV24`  
_L33-35_
- L34 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::DecodedV24`  
`struct DecodedV24`  
_L37-165_
- L38 _public typedef_ `using VectorOfCharStringMatrix = pma::Vector<pma::Matrix<pma::String<char>>>;`
- L39 _public typedef_ `using StringPair = std::pair<pma::String<char>, pma::String<char>>;`
- L42 _public member_ `static const pma::String<char> name;` — Descriptor
- L43 _public member_ `static const Archetype archetype;`
- L44 _public member_ `static const Gender gender;`
- L45 _public member_ `static const std::uint16_t age;`
- L47 _public member_ `static const pma::Vector<StringPair> metadata;`
- L48 _public member_ `static const TranslationUnit translationUnit;`
- L49 _public member_ `static const RotationUnit rotationUnit;`
- L50 _public member_ `static const CoordinateSystem coordinateSystem;`
- L51 _public member_ `static const std::uint16_t lodCount[3ul];`
- L52 _public member_ `static const std::uint16_t maxLODs[3ul];`
- L53 _public member_ `static const pma::String<char> complexity;`
- L54 _public member_ `static const pma::String<char> dbName;`
- L57 _public member_ `static const pma::Vector<pma::String<char>> guiControlNames;` — Definition
- L58 _public member_ `static const pma::Vector<pma::String<char>> rawControlNames;`
- L59 _public member_ `static const VectorOfCharStringMatrix jointNames;`
- L60 _public member_ `static const VectorOfCharStringMatrix blendShapeNames;`
- L61 _public member_ `static const VectorOfCharStringMatrix animatedMapNames;`
- L62 _public member_ `static const VectorOfCharStringMatrix meshNames;`
- L63 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> meshBlendShapeIndices;`
- L64 _public member_ `static const pma::Matrix<std::uint16_t> jointHierarchy;`
- L65 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> neutralJointTranslations;`
- L66 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> neutralJointRotations;`
- L69 _public member_ `static const std::uint16_t guiControlCount;` — Behavior
- L70 _public member_ `static const std::uint16_t rawControlCount;`
- L71 _public member_ `static const std::uint16_t psdCount;`
- L72 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> conditionalInputIndices;`
- L73 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> conditionalOutputIndices;`
- L74 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalFromValues;`
- L75 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalToValues;`
- L76 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalSlopeValues;`
- L77 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalCutValues;`
- L78 _public member_ `static const pma::Vector<std::uint16_t> psdRowIndices;`
- L79 _public member_ `static const pma::Vector<std::uint16_t> psdColumnIndices;`
- L80 _public member_ `static const pma::Vector<float> psdValues;`
- L81 _public member_ `static const pma::Vector<std::uint16_t> jointRowCount;`
- L82 _public member_ `static const std::uint16_t jointColumnCount;`
- L83 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> jointVariableIndices;`
- L84 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> jointGroupLODs;`
- L85 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupInputIndices;`
- L86 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupOutputIndices;`
- L87 _public member_ `static const pma::Matrix<pma::Matrix<float>> jointGroupValues;`
- L88 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupJointIndices;`
- L89 _public member_ `static const pma::Matrix<std::uint16_t> blendShapeLODs;`
- L90 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> blendShapeInputIndices;`
- L91 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> blendShapeOutputIndices;`
- L92 _public member_ `static const pma::Vector<std::uint16_t> animatedMapCount;`
- L93 _public member_ `static const pma::Matrix<std::uint16_t> animatedMapLODs;`
- L96 _public member_ `static const pma::Vector<std::uint32_t> meshCount;` — Geometry
- L97 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> vertexPositions;`
- L98 _public member_ `static const pma::Vector<pma::Matrix<TextureCoordinate>> vertexTextureCoordinates;`
- L99 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> vertexNormals;`
- L100 _public member_ `static const pma::Vector<pma::Matrix<VertexLayout>> vertexLayouts;`
- L101 _public member_ `static const pma::Matrix<pma::Matrix<std::uint32_t>> faces;`
- L102 _public member_ `static const pma::Matrix<std::uint16_t> maxInfluencePerVertex;`
- L103 _public member_ `static const pma::Matrix<pma::Matrix<float>> skinWeightsValues;`
- L104 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> skinWeightsJointIndices;`
- L105 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> correctiveBlendShapeIndices;`
- L106 _public member_ `static const pma::Matrix<pma::Matrix<Vector3>> correctiveBlendShapeDeltas;`
- L107 _public member_ `static const pma::Matrix<pma::Matrix<std::uint32_t>> correctiveBlendShapeVertexIndices;`
- L110 _public member_ `static const pma::Vector<pma::String<char>> mlControlNames;` — Machine learned behavior
- L111 _public member_ `static const VectorOfCharStringMatrix regionNames;`
- L112 _public member_ `static const pma::Matrix<std::uint16_t> neuralNetworkIndicesPerLOD;`
- L113 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> neuralNetworkIndicesPerMeshRegion;`
- L114 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkInputIndices;`
- L115 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkOutputIndices;`
- L116 _public member_ `static const pma::Matrix<std::uint16_t> neuralNetworkLayerCount;`
- L117 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkActivationFunction;`
- L118 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkActivationFunctionParameters;`
- L119 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkBiases;`
- L120 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkWeights;`
- L123 _public member_ `static const pma::Vector<pma::String<char>> poseNames;` — RBF behavior
- L124 _public member_ `static const pma::Vector<std::uint16_t> poseDistanceMethod;`
- L125 _public member_ `static const pma::Vector<std::uint16_t> poseFunctionType;`
- L126 _public member_ `static const pma::Vector<float> poseScale;`
- L127 _public member_ `static const pma::Matrix<std::uint16_t> solverIndicesPerLOD;`
- L128 _public member_ `static const pma::Vector<pma::String<char>> solverNames;`
- L129 _public member_ `static const pma::Vector<float> solverRadius;`
- L130 _public member_ `static const pma::Vector<float> solverWeightThreshold;`
- L131 _public member_ `static const pma::Vector<std::uint16_t> solverType;`
- L132 _public member_ `static const pma::Vector<std::uint16_t> solverAutomaticRadius;`
- L133 _public member_ `static const pma::Vector<std::uint16_t> solverDistanceMethod;`
- L134 _public member_ `static const pma::Vector<std::uint16_t> solverNormalizeMethod;`
- L135 _public member_ `static const pma::Vector<std::uint16_t> solverFunctionType;`
- L136 _public member_ `static const pma::Vector<std::uint16_t> solverTwistAxis;`
- L137 _public member_ `static const pma::Matrix<std::uint16_t> solverRawControlIndices;`
- L138 _public member_ `static const pma::Matrix<std::uint16_t> solverPoseIndices;`
- L139 _public member_ `static const pma::Matrix<float> solverRawControlValues;`
- L142 _public member_ `static const pma::Matrix<TranslationRepresentation> jointTranslationRepresentation;` — Joint behavior metadata
- L143 _public member_ `static const pma::Matrix<RotationRepresentation> jointRotationRepresentation;`
- L144 _public member_ `static const pma::Matrix<ScaleRepresentation> jointScaleRepresentation;`
- L147 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> swingInputControlIndices;` — Twist swing setups
- L148 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> swingOutputJointIndices;`
- L149 _public member_ `static const pma::Vector<pma::Matrix<float>> swingBlendWeights;`
- L150 _public member_ `static const pma::Matrix<TwistAxis> swingTwistAxes;`
- L151 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> twistInputControlIndices;`
- L152 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> twistOutputJointIndices;`
- L153 _public member_ `static const pma::Vector<pma::Matrix<float>> twistBlendWeights;`
- L154 _public member_ `static const pma::Matrix<TwistAxis> twistTwistAxes;`
- L156 _public prototype_ `static std::size_t lodConstraintToIndex(std::uint16_t maxLOD, std::uint16_t minLOD);`
- L157 _public prototype_ `static RawJoints getJoints(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L158 _public prototype_ `static RawBlendShapeChannels getBlendShapes(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L161 _public prototype_ `static RawConditionalTable getConditionals(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L164 _public prototype_ `static RawAnimatedMaps getAnimatedMaps(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/dnatests/Fixturesv25.h` (Private)


#### struct `dna::RawV25`  
`struct RawV25`  
_L14-32_
- L15 _public member_ `static const unsigned char header[155];`
- L16 _public member_ `static const unsigned char descriptor[87];`
- L17 _public member_ `static const unsigned char definition[794];`
- L18 _public member_ `static const unsigned char controls[2];`
- L19 _public member_ `static const unsigned char conditionals[324];`
- L20 _public member_ `static const unsigned char psds[204];`
- L21 _public member_ `static const unsigned char joints[444];`
- L22 _public member_ `static const unsigned char blendshapes[44];`
- L23 _public member_ `static const unsigned char animatedmaps[8];`
- L24 _public member_ `static const unsigned char geometry[1080];`
- L25 _public member_ `static const unsigned char machineLearnedBehavior[762];`
- L26 _public member_ `static const unsigned char rbfBehavior[327];`
- L27 _public member_ `static const unsigned char rbfBehaviorExt[228];`
- L28 _public member_ `static const unsigned char jointBehaviorMetadata[58];`
- L29 _public member_ `static const unsigned char twistSwingBehavior[200];`
- L31 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::RawV24DowngradedFromV25`  
`struct RawV24DowngradedFromV25`  
_L34-36_
- L35 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::DecodedV25`  
`struct DecodedV25`  
_L38-173_
- L39 _public typedef_ `using VectorOfCharStringMatrix = pma::Vector<pma::Matrix<pma::String<char>>>;`
- L40 _public typedef_ `using StringPair = std::pair<pma::String<char>, pma::String<char>>;`
- L43 _public member_ `static const pma::String<char> name;` — Descriptor
- L44 _public member_ `static const Archetype archetype;`
- L45 _public member_ `static const Gender gender;`
- L46 _public member_ `static const std::uint16_t age;`
- L48 _public member_ `static const pma::Vector<StringPair> metadata;`
- L49 _public member_ `static const TranslationUnit translationUnit;`
- L50 _public member_ `static const RotationUnit rotationUnit;`
- L51 _public member_ `static const CoordinateSystem coordinateSystem;`
- L52 _public member_ `static const std::uint16_t lodCount[3ul];`
- L53 _public member_ `static const std::uint16_t maxLODs[3ul];`
- L54 _public member_ `static const pma::String<char> complexity;`
- L55 _public member_ `static const pma::String<char> dbName;`
- L58 _public member_ `static const pma::Vector<pma::String<char>> guiControlNames;` — Definition
- L59 _public member_ `static const pma::Vector<pma::String<char>> rawControlNames;`
- L60 _public member_ `static const VectorOfCharStringMatrix jointNames;`
- L61 _public member_ `static const VectorOfCharStringMatrix blendShapeNames;`
- L62 _public member_ `static const VectorOfCharStringMatrix animatedMapNames;`
- L63 _public member_ `static const VectorOfCharStringMatrix meshNames;`
- L64 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> meshBlendShapeIndices;`
- L65 _public member_ `static const pma::Matrix<std::uint16_t> jointHierarchy;`
- L66 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> neutralJointTranslations;`
- L67 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> neutralJointRotations;`
- L70 _public member_ `static const std::uint16_t guiControlCount;` — Behavior
- L71 _public member_ `static const std::uint16_t rawControlCount;`
- L72 _public member_ `static const std::uint16_t psdCount;`
- L73 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> conditionalInputIndices;`
- L74 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> conditionalOutputIndices;`
- L75 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalFromValues;`
- L76 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalToValues;`
- L77 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalSlopeValues;`
- L78 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalCutValues;`
- L79 _public member_ `static const pma::Vector<std::uint16_t> psdRowIndices;`
- L80 _public member_ `static const pma::Vector<std::uint16_t> psdColumnIndices;`
- L81 _public member_ `static const pma::Vector<float> psdValues;`
- L82 _public member_ `static const pma::Vector<std::uint16_t> jointRowCount;`
- L83 _public member_ `static const std::uint16_t jointColumnCount;`
- L84 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> jointVariableIndices;`
- L85 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> jointGroupLODs;`
- L86 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupInputIndices;`
- L87 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupOutputIndices;`
- L88 _public member_ `static const pma::Matrix<pma::Matrix<float>> jointGroupValues;`
- L89 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupJointIndices;`
- L90 _public member_ `static const pma::Matrix<std::uint16_t> blendShapeLODs;`
- L91 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> blendShapeInputIndices;`
- L92 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> blendShapeOutputIndices;`
- L93 _public member_ `static const pma::Vector<std::uint16_t> animatedMapCount;`
- L94 _public member_ `static const pma::Matrix<std::uint16_t> animatedMapLODs;`
- L97 _public member_ `static const pma::Vector<std::uint32_t> meshCount;` — Geometry
- L98 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> vertexPositions;`
- L99 _public member_ `static const pma::Vector<pma::Matrix<TextureCoordinate>> vertexTextureCoordinates;`
- L100 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> vertexNormals;`
- L101 _public member_ `static const pma::Vector<pma::Matrix<VertexLayout>> vertexLayouts;`
- L102 _public member_ `static const pma::Matrix<pma::Matrix<std::uint32_t>> faces;`
- L103 _public member_ `static const pma::Matrix<std::uint16_t> maxInfluencePerVertex;`
- L104 _public member_ `static const pma::Matrix<pma::Matrix<float>> skinWeightsValues;`
- L105 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> skinWeightsJointIndices;`
- L106 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> correctiveBlendShapeIndices;`
- L107 _public member_ `static const pma::Matrix<pma::Matrix<Vector3>> correctiveBlendShapeDeltas;`
- L108 _public member_ `static const pma::Matrix<pma::Matrix<std::uint32_t>> correctiveBlendShapeVertexIndices;`
- L111 _public member_ `static const pma::Vector<pma::String<char>> mlControlNames;` — Machine learned behavior
- L112 _public member_ `static const VectorOfCharStringMatrix regionNames;`
- L113 _public member_ `static const pma::Matrix<std::uint16_t> neuralNetworkIndicesPerLOD;`
- L114 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> neuralNetworkIndicesPerMeshRegion;`
- L115 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkInputIndices;`
- L116 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkOutputIndices;`
- L117 _public member_ `static const pma::Matrix<std::uint16_t> neuralNetworkLayerCount;`
- L118 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkActivationFunction;`
- L119 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkActivationFunctionParameters;`
- L120 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkBiases;`
- L121 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkWeights;`
- L124 _public member_ `static const pma::Vector<pma::String<char>> poseNames;` — RBF behavior
- L125 _public member_ `static const pma::Vector<std::uint16_t> poseDistanceMethod;`
- L126 _public member_ `static const pma::Vector<std::uint16_t> poseFunctionType;`
- L127 _public member_ `static const pma::Vector<float> poseScale;`
- L129 _public member_ `static const pma::Matrix<std::uint16_t> solverIndicesPerLOD;`
- L130 _public member_ `static const pma::Vector<pma::String<char>> solverNames;`
- L131 _public member_ `static const pma::Vector<float> solverRadius;`
- L132 _public member_ `static const pma::Vector<float> solverWeightThreshold;`
- L133 _public member_ `static const pma::Vector<std::uint16_t> solverType;`
- L134 _public member_ `static const pma::Vector<std::uint16_t> solverAutomaticRadius;`
- L135 _public member_ `static const pma::Vector<std::uint16_t> solverDistanceMethod;`
- L136 _public member_ `static const pma::Vector<std::uint16_t> solverNormalizeMethod;`
- L137 _public member_ `static const pma::Vector<std::uint16_t> solverFunctionType;`
- L138 _public member_ `static const pma::Vector<std::uint16_t> solverTwistAxis;`
- L139 _public member_ `static const pma::Matrix<std::uint16_t> solverRawControlIndices;`
- L140 _public member_ `static const pma::Matrix<std::uint16_t> solverPoseIndices;`
- L141 _public member_ `static const pma::Matrix<float> solverRawControlValues;`
- L144 _public member_ `static const pma::Vector<pma::String<char>> poseControlNames;` — RBF behavior ext
- L145 _public member_ `static const pma::Matrix<std::uint16_t> poseInputControlIndices;`
- L146 _public member_ `static const pma::Matrix<std::uint16_t> poseOutputControlIndices;`
- L147 _public member_ `static const pma::Matrix<float> poseOutputControlWeights;`
- L150 _public member_ `static const pma::Matrix<TranslationRepresentation> jointTranslationRepresentation;` — Joint behavior metadata
- L151 _public member_ `static const pma::Matrix<RotationRepresentation> jointRotationRepresentation;`
- L152 _public member_ `static const pma::Matrix<ScaleRepresentation> jointScaleRepresentation;`
- L155 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> swingInputControlIndices;` — Twist swing setups
- L156 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> swingOutputJointIndices;`
- L157 _public member_ `static const pma::Vector<pma::Matrix<float>> swingBlendWeights;`
- L158 _public member_ `static const pma::Matrix<TwistAxis> swingTwistAxes;`
- L159 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> twistInputControlIndices;`
- L160 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> twistOutputJointIndices;`
- L161 _public member_ `static const pma::Vector<pma::Matrix<float>> twistBlendWeights;`
- L162 _public member_ `static const pma::Matrix<TwistAxis> twistTwistAxes;`
- L164 _public prototype_ `static std::size_t lodConstraintToIndex(std::uint16_t maxLOD, std::uint16_t minLOD);`
- L165 _public prototype_ `static RawJoints getJoints(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L166 _public prototype_ `static RawBlendShapeChannels getBlendShapes(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L169 _public prototype_ `static RawConditionalTable getConditionals(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L172 _public prototype_ `static RawAnimatedMaps getAnimatedMaps(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/dnatests/Fixturesv26.h` (Private)


#### struct `dna::RawV26`  
`struct RawV26`  
_L14-33_
- L15 _public member_ `static const unsigned char header[171];`
- L16 _public member_ `static const unsigned char descriptor[87];`
- L17 _public member_ `static const unsigned char definition[794];`
- L18 _public member_ `static const unsigned char controls[2];`
- L19 _public member_ `static const unsigned char conditionals[324];`
- L20 _public member_ `static const unsigned char psds[204];`
- L21 _public member_ `static const unsigned char joints[444];`
- L22 _public member_ `static const unsigned char blendshapes[44];`
- L23 _public member_ `static const unsigned char animatedmaps[8];`
- L24 _public member_ `static const unsigned char geometry[1080];`
- L25 _public member_ `static const unsigned char machineLearnedBehavior[762];`
- L26 _public member_ `static const unsigned char rbfBehavior[327];`
- L27 _public member_ `static const unsigned char rbfBehaviorExt[228];`
- L28 _public member_ `static const unsigned char jointBehaviorMetadata[58];`
- L29 _public member_ `static const unsigned char twistSwingBehavior[200];`
- L30 _public member_ `static const unsigned char machineLearnedBehaviorExt[448];`
- L32 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::RawV25DowngradedFromV26`  
`struct RawV25DowngradedFromV26`  
_L35-37_
- L36 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::DecodedV26`  
`struct DecodedV26`  
_L39-181_
- L40 _public typedef_ `using VectorOfCharStringMatrix = pma::Vector<pma::Matrix<pma::String<char>>>;`
- L41 _public typedef_ `using StringPair = std::pair<pma::String<char>, pma::String<char>>;`
- L44 _public member_ `static const pma::String<char> name;` — Descriptor
- L45 _public member_ `static const Archetype archetype;`
- L46 _public member_ `static const Gender gender;`
- L47 _public member_ `static const std::uint16_t age;`
- L49 _public member_ `static const pma::Vector<StringPair> metadata;`
- L50 _public member_ `static const TranslationUnit translationUnit;`
- L51 _public member_ `static const RotationUnit rotationUnit;`
- L52 _public member_ `static const CoordinateSystem coordinateSystem;`
- L53 _public member_ `static const std::uint16_t lodCount[3ul];`
- L54 _public member_ `static const std::uint16_t maxLODs[3ul];`
- L55 _public member_ `static const pma::String<char> complexity;`
- L56 _public member_ `static const pma::String<char> dbName;`
- L59 _public member_ `static const pma::Vector<pma::String<char>> guiControlNames;` — Definition
- L60 _public member_ `static const pma::Vector<pma::String<char>> rawControlNames;`
- L61 _public member_ `static const VectorOfCharStringMatrix jointNames;`
- L62 _public member_ `static const VectorOfCharStringMatrix blendShapeNames;`
- L63 _public member_ `static const VectorOfCharStringMatrix animatedMapNames;`
- L64 _public member_ `static const VectorOfCharStringMatrix meshNames;`
- L65 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> meshBlendShapeIndices;`
- L66 _public member_ `static const pma::Matrix<std::uint16_t> jointHierarchy;`
- L67 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> neutralJointTranslations;`
- L68 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> neutralJointRotations;`
- L71 _public member_ `static const std::uint16_t guiControlCount;` — Behavior
- L72 _public member_ `static const std::uint16_t rawControlCount;`
- L73 _public member_ `static const std::uint16_t psdCount;`
- L74 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> conditionalInputIndices;`
- L75 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> conditionalOutputIndices;`
- L76 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalFromValues;`
- L77 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalToValues;`
- L78 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalSlopeValues;`
- L79 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalCutValues;`
- L80 _public member_ `static const pma::Vector<std::uint16_t> psdRowIndices;`
- L81 _public member_ `static const pma::Vector<std::uint16_t> psdColumnIndices;`
- L82 _public member_ `static const pma::Vector<float> psdValues;`
- L83 _public member_ `static const pma::Vector<std::uint16_t> jointRowCount;`
- L84 _public member_ `static const std::uint16_t jointColumnCount;`
- L85 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> jointVariableIndices;`
- L86 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> jointGroupLODs;`
- L87 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupInputIndices;`
- L88 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupOutputIndices;`
- L89 _public member_ `static const pma::Matrix<pma::Matrix<float>> jointGroupValues;`
- L90 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupJointIndices;`
- L91 _public member_ `static const pma::Matrix<std::uint16_t> blendShapeLODs;`
- L92 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> blendShapeInputIndices;`
- L93 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> blendShapeOutputIndices;`
- L94 _public member_ `static const pma::Vector<std::uint16_t> animatedMapCount;`
- L95 _public member_ `static const pma::Matrix<std::uint16_t> animatedMapLODs;`
- L98 _public member_ `static const pma::Vector<std::uint32_t> meshCount;` — Geometry
- L99 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> vertexPositions;`
- L100 _public member_ `static const pma::Vector<pma::Matrix<TextureCoordinate>> vertexTextureCoordinates;`
- L101 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> vertexNormals;`
- L102 _public member_ `static const pma::Vector<pma::Matrix<VertexLayout>> vertexLayouts;`
- L103 _public member_ `static const pma::Matrix<pma::Matrix<std::uint32_t>> faces;`
- L104 _public member_ `static const pma::Matrix<std::uint16_t> maxInfluencePerVertex;`
- L105 _public member_ `static const pma::Matrix<pma::Matrix<float>> skinWeightsValues;`
- L106 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> skinWeightsJointIndices;`
- L107 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> correctiveBlendShapeIndices;`
- L108 _public member_ `static const pma::Matrix<pma::Matrix<Vector3>> correctiveBlendShapeDeltas;`
- L109 _public member_ `static const pma::Matrix<pma::Matrix<std::uint32_t>> correctiveBlendShapeVertexIndices;`
- L112 _public member_ `static const pma::Vector<pma::String<char>> mlControlNames;` — Machine learned behavior
- L113 _public member_ `static const VectorOfCharStringMatrix regionNames;`
- L114 _public member_ `static const pma::Matrix<std::uint16_t> neuralNetworkIndicesPerLOD;`
- L115 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> neuralNetworkIndicesPerMeshRegion;`
- L116 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkInputIndices;`
- L117 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkOutputIndices;`
- L118 _public member_ `static const pma::Matrix<std::uint16_t> neuralNetworkLayerCount;`
- L119 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkActivationFunction;`
- L120 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkActivationFunctionParameters;`
- L121 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkBiases;`
- L122 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkWeights;`
- L125 _public member_ `static const pma::Vector<pma::String<char>> poseNames;` — RBF behavior
- L126 _public member_ `static const pma::Vector<std::uint16_t> poseDistanceMethod;`
- L127 _public member_ `static const pma::Vector<std::uint16_t> poseFunctionType;`
- L128 _public member_ `static const pma::Vector<float> poseScale;`
- L130 _public member_ `static const pma::Matrix<std::uint16_t> solverIndicesPerLOD;`
- L131 _public member_ `static const pma::Vector<pma::String<char>> solverNames;`
- L132 _public member_ `static const pma::Vector<float> solverRadius;`
- L133 _public member_ `static const pma::Vector<float> solverWeightThreshold;`
- L134 _public member_ `static const pma::Vector<std::uint16_t> solverType;`
- L135 _public member_ `static const pma::Vector<std::uint16_t> solverAutomaticRadius;`
- L136 _public member_ `static const pma::Vector<std::uint16_t> solverDistanceMethod;`
- L137 _public member_ `static const pma::Vector<std::uint16_t> solverNormalizeMethod;`
- L138 _public member_ `static const pma::Vector<std::uint16_t> solverFunctionType;`
- L139 _public member_ `static const pma::Vector<std::uint16_t> solverTwistAxis;`
- L140 _public member_ `static const pma::Matrix<std::uint16_t> solverRawControlIndices;`
- L141 _public member_ `static const pma::Matrix<std::uint16_t> solverPoseIndices;`
- L142 _public member_ `static const pma::Matrix<float> solverRawControlValues;`
- L145 _public member_ `static const pma::Vector<pma::String<char>> poseControlNames;` — RBF behavior ext
- L146 _public member_ `static const pma::Matrix<std::uint16_t> poseInputControlIndices;`
- L147 _public member_ `static const pma::Matrix<std::uint16_t> poseOutputControlIndices;`
- L148 _public member_ `static const pma::Matrix<float> poseOutputControlWeights;`
- L151 _public member_ `static const pma::Matrix<TranslationRepresentation> jointTranslationRepresentation;` — Joint behavior metadata
- L152 _public member_ `static const pma::Matrix<RotationRepresentation> jointRotationRepresentation;`
- L153 _public member_ `static const pma::Matrix<ScaleRepresentation> jointScaleRepresentation;`
- L156 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> swingInputControlIndices;` — Twist swing setups
- L157 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> swingOutputJointIndices;`
- L158 _public member_ `static const pma::Vector<pma::Matrix<float>> swingBlendWeights;`
- L159 _public member_ `static const pma::Matrix<TwistAxis> swingTwistAxes;`
- L160 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> twistInputControlIndices;`
- L161 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> twistOutputJointIndices;`
- L162 _public member_ `static const pma::Vector<pma::Matrix<float>> twistBlendWeights;`
- L163 _public member_ `static const pma::Matrix<TwistAxis> twistTwistAxes;`
- L166 _public member_ `static const pma::Matrix<pma::Matrix<MachineLearnedBehaviorOperationType>> mlOperationTypes;` — Machine learned behavior ext
- L167 _public member_ `static const pma::Vector<pma::Matrix<pma::Matrix<std::uint32_t>>> mlOperationParameters;`
- L168 _public member_ `static const pma::Vector<pma::Matrix<pma::Matrix<std::uint16_t>>> mlDependencyOperationSetIndices;`
- L169 _public member_ `static const pma::Vector<pma::Matrix<pma::Matrix<std::uint16_t>>> mlDependencyOperationIndices;`
- L170 _public member_ `static const pma::Vector<pma::Matrix<pma::Matrix<std::uint16_t>>> mlOperationIndicesPerLOD;`
- L172 _public prototype_ `static std::size_t lodConstraintToIndex(std::uint16_t maxLOD, std::uint16_t minLOD);`
- L173 _public prototype_ `static RawJoints getJoints(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L174 _public prototype_ `static RawBlendShapeChannels getBlendShapes(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L177 _public prototype_ `static RawConditionalTable getConditionals(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L180 _public prototype_ `static RawAnimatedMaps getAnimatedMaps(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/dnatests/Fixturesv27.h` (Private)


#### struct `dna::RawV27`  
`struct RawV27`  
_L14-34_
- L15 _public member_ `static const unsigned char header[187];`
- L16 _public member_ `static const unsigned char descriptor[87];`
- L17 _public member_ `static const unsigned char definition[794];`
- L18 _public member_ `static const unsigned char controls[2];`
- L19 _public member_ `static const unsigned char conditionals[324];`
- L20 _public member_ `static const unsigned char psds[204];`
- L21 _public member_ `static const unsigned char joints[444];`
- L22 _public member_ `static const unsigned char blendshapes[44];`
- L23 _public member_ `static const unsigned char animatedmaps[8];`
- L24 _public member_ `static const unsigned char geometry[1080];`
- L25 _public member_ `static const unsigned char machineLearnedBehavior[762];`
- L26 _public member_ `static const unsigned char rbfBehavior[327];`
- L27 _public member_ `static const unsigned char rbfBehaviorExt[228];`
- L28 _public member_ `static const unsigned char jointBehaviorMetadata[58];`
- L29 _public member_ `static const unsigned char twistSwingBehavior[200];`
- L30 _public member_ `static const unsigned char machineLearnedBehaviorExt[448];`
- L31 _public member_ `static const unsigned char descriptorExt[16];`
- L33 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::RawV26DowngradedFromV27`  
`struct RawV26DowngradedFromV27`  
_L36-38_
- L37 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::DecodedV27`  
`struct DecodedV27`  
_L40-187_
- L41 _public typedef_ `using VectorOfCharStringMatrix = pma::Vector<pma::Matrix<pma::String<char>>>;`
- L42 _public typedef_ `using StringPair = std::pair<pma::String<char>, pma::String<char>>;`
- L45 _public member_ `static const pma::String<char> name;` — Descriptor
- L46 _public member_ `static const Archetype archetype;`
- L47 _public member_ `static const Gender gender;`
- L48 _public member_ `static const std::uint16_t age;`
- L50 _public member_ `static const pma::Vector<StringPair> metadata;`
- L51 _public member_ `static const TranslationUnit translationUnit;`
- L52 _public member_ `static const RotationUnit rotationUnit;`
- L53 _public member_ `static const CoordinateSystem coordinateSystem;`
- L54 _public member_ `static const std::uint16_t lodCount[3ul];`
- L55 _public member_ `static const std::uint16_t maxLODs[3ul];`
- L56 _public member_ `static const pma::String<char> complexity;`
- L57 _public member_ `static const pma::String<char> dbName;`
- L60 _public member_ `static const pma::Vector<pma::String<char>> guiControlNames;` — Definition
- L61 _public member_ `static const pma::Vector<pma::String<char>> rawControlNames;`
- L62 _public member_ `static const VectorOfCharStringMatrix jointNames;`
- L63 _public member_ `static const VectorOfCharStringMatrix blendShapeNames;`
- L64 _public member_ `static const VectorOfCharStringMatrix animatedMapNames;`
- L65 _public member_ `static const VectorOfCharStringMatrix meshNames;`
- L66 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> meshBlendShapeIndices;`
- L67 _public member_ `static const pma::Matrix<std::uint16_t> jointHierarchy;`
- L68 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> neutralJointTranslations;`
- L69 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> neutralJointRotations;`
- L72 _public member_ `static const std::uint16_t guiControlCount;` — Behavior
- L73 _public member_ `static const std::uint16_t rawControlCount;`
- L74 _public member_ `static const std::uint16_t psdCount;`
- L75 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> conditionalInputIndices;`
- L76 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> conditionalOutputIndices;`
- L77 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalFromValues;`
- L78 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalToValues;`
- L79 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalSlopeValues;`
- L80 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalCutValues;`
- L81 _public member_ `static const pma::Vector<std::uint16_t> psdRowIndices;`
- L82 _public member_ `static const pma::Vector<std::uint16_t> psdColumnIndices;`
- L83 _public member_ `static const pma::Vector<float> psdValues;`
- L84 _public member_ `static const pma::Vector<std::uint16_t> jointRowCount;`
- L85 _public member_ `static const std::uint16_t jointColumnCount;`
- L86 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> jointVariableIndices;`
- L87 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> jointGroupLODs;`
- L88 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupInputIndices;`
- L89 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupOutputIndices;`
- L90 _public member_ `static const pma::Matrix<pma::Matrix<float>> jointGroupValues;`
- L91 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupJointIndices;`
- L92 _public member_ `static const pma::Matrix<std::uint16_t> blendShapeLODs;`
- L93 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> blendShapeInputIndices;`
- L94 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> blendShapeOutputIndices;`
- L95 _public member_ `static const pma::Vector<std::uint16_t> animatedMapCount;`
- L96 _public member_ `static const pma::Matrix<std::uint16_t> animatedMapLODs;`
- L99 _public member_ `static const pma::Vector<std::uint32_t> meshCount;` — Geometry
- L100 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> vertexPositions;`
- L101 _public member_ `static const pma::Vector<pma::Matrix<TextureCoordinate>> vertexTextureCoordinates;`
- L102 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> vertexNormals;`
- L103 _public member_ `static const pma::Vector<pma::Matrix<VertexLayout>> vertexLayouts;`
- L104 _public member_ `static const pma::Matrix<pma::Matrix<std::uint32_t>> faces;`
- L105 _public member_ `static const pma::Matrix<std::uint16_t> maxInfluencePerVertex;`
- L106 _public member_ `static const pma::Matrix<pma::Matrix<float>> skinWeightsValues;`
- L107 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> skinWeightsJointIndices;`
- L108 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> correctiveBlendShapeIndices;`
- L109 _public member_ `static const pma::Matrix<pma::Matrix<Vector3>> correctiveBlendShapeDeltas;`
- L110 _public member_ `static const pma::Matrix<pma::Matrix<std::uint32_t>> correctiveBlendShapeVertexIndices;`
- L113 _public member_ `static const pma::Vector<pma::String<char>> mlControlNames;` — Machine learned behavior
- L114 _public member_ `static const VectorOfCharStringMatrix regionNames;`
- L115 _public member_ `static const pma::Matrix<std::uint16_t> neuralNetworkIndicesPerLOD;`
- L116 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> neuralNetworkIndicesPerMeshRegion;`
- L117 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkInputIndices;`
- L118 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkOutputIndices;`
- L119 _public member_ `static const pma::Matrix<std::uint16_t> neuralNetworkLayerCount;`
- L120 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkActivationFunction;`
- L121 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkActivationFunctionParameters;`
- L122 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkBiases;`
- L123 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkWeights;`
- L126 _public member_ `static const pma::Vector<pma::String<char>> poseNames;` — RBF behavior
- L127 _public member_ `static const pma::Vector<std::uint16_t> poseDistanceMethod;`
- L128 _public member_ `static const pma::Vector<std::uint16_t> poseFunctionType;`
- L129 _public member_ `static const pma::Vector<float> poseScale;`
- L131 _public member_ `static const pma::Matrix<std::uint16_t> solverIndicesPerLOD;`
- L132 _public member_ `static const pma::Vector<pma::String<char>> solverNames;`
- L133 _public member_ `static const pma::Vector<float> solverRadius;`
- L134 _public member_ `static const pma::Vector<float> solverWeightThreshold;`
- L135 _public member_ `static const pma::Vector<std::uint16_t> solverType;`
- L136 _public member_ `static const pma::Vector<std::uint16_t> solverAutomaticRadius;`
- L137 _public member_ `static const pma::Vector<std::uint16_t> solverDistanceMethod;`
- L138 _public member_ `static const pma::Vector<std::uint16_t> solverNormalizeMethod;`
- L139 _public member_ `static const pma::Vector<std::uint16_t> solverFunctionType;`
- L140 _public member_ `static const pma::Vector<std::uint16_t> solverTwistAxis;`
- L141 _public member_ `static const pma::Matrix<std::uint16_t> solverRawControlIndices;`
- L142 _public member_ `static const pma::Matrix<std::uint16_t> solverPoseIndices;`
- L143 _public member_ `static const pma::Matrix<float> solverRawControlValues;`
- L146 _public member_ `static const pma::Vector<pma::String<char>> poseControlNames;` — RBF behavior ext
- L147 _public member_ `static const pma::Matrix<std::uint16_t> poseInputControlIndices;`
- L148 _public member_ `static const pma::Matrix<std::uint16_t> poseOutputControlIndices;`
- L149 _public member_ `static const pma::Matrix<float> poseOutputControlWeights;`
- L152 _public member_ `static const pma::Matrix<TranslationRepresentation> jointTranslationRepresentation;` — Joint behavior metadata
- L153 _public member_ `static const pma::Matrix<RotationRepresentation> jointRotationRepresentation;`
- L154 _public member_ `static const pma::Matrix<ScaleRepresentation> jointScaleRepresentation;`
- L157 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> swingInputControlIndices;` — Twist swing setups
- L158 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> swingOutputJointIndices;`
- L159 _public member_ `static const pma::Vector<pma::Matrix<float>> swingBlendWeights;`
- L160 _public member_ `static const pma::Matrix<TwistAxis> swingTwistAxes;`
- L161 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> twistInputControlIndices;`
- L162 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> twistOutputJointIndices;`
- L163 _public member_ `static const pma::Vector<pma::Matrix<float>> twistBlendWeights;`
- L164 _public member_ `static const pma::Matrix<TwistAxis> twistTwistAxes;`
- L167 _public member_ `static const pma::Matrix<pma::Matrix<MachineLearnedBehaviorOperationType>> mlOperationTypes;` — Machine learned behavior ext
- L168 _public member_ `static const pma::Vector<pma::Matrix<pma::Matrix<std::uint32_t>>> mlOperationParameters;`
- L169 _public member_ `static const pma::Vector<pma::Matrix<pma::Matrix<std::uint16_t>>> mlDependencyOperationSetIndices;`
- L170 _public member_ `static const pma::Vector<pma::Matrix<pma::Matrix<std::uint16_t>>> mlDependencyOperationIndices;`
- L171 _public member_ `static const pma::Vector<pma::Matrix<pma::Matrix<std::uint16_t>>> mlOperationIndicesPerLOD;`
- L174 _public member_ `static const RotationSequence rotationSequence;` — Descriptor ext
- L175 _public member_ `static const RotationSign rotationSign;`
- L176 _public member_ `static const FaceWindingOrder faceWindingOrder;`
- L178 _public prototype_ `static std::size_t lodConstraintToIndex(std::uint16_t maxLOD, std::uint16_t minLOD);`
- L179 _public prototype_ `static RawJoints getJoints(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L180 _public prototype_ `static RawBlendShapeChannels getBlendShapes(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L183 _public prototype_ `static RawConditionalTable getConditionals(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L186 _public prototype_ `static RawAnimatedMaps getAnimatedMaps(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/dnatests/Fixturesv28.h` (Private)


#### struct `dna::RawV28`  
`struct RawV28`  
_L14-34_
- L15 _public member_ `static const unsigned char header[187];`
- L16 _public member_ `static const unsigned char descriptor[87];`
- L17 _public member_ `static const unsigned char definition[794];`
- L18 _public member_ `static const unsigned char controls[2];`
- L19 _public member_ `static const unsigned char conditionals[324];`
- L20 _public member_ `static const unsigned char psds[204];`
- L21 _public member_ `static const unsigned char joints[444];`
- L22 _public member_ `static const unsigned char blendshapes[44];`
- L23 _public member_ `static const unsigned char animatedmaps[8];`
- L24 _public member_ `static const unsigned char geometry[1080];`
- L25 _public member_ `static const unsigned char machineLearnedBehavior[762];`
- L26 _public member_ `static const unsigned char rbfBehavior[327];`
- L27 _public member_ `static const unsigned char rbfBehaviorExt[228];`
- L28 _public member_ `static const unsigned char jointBehaviorMetadata[58];`
- L29 _public member_ `static const unsigned char twistSwingBehavior[200];`
- L30 _public member_ `static const unsigned char machineLearnedBehaviorExt[448];`
- L31 _public member_ `static const unsigned char descriptorExt[17];`
- L33 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::RawV27DowngradedFromV28`  
`struct RawV27DowngradedFromV28`  
_L36-38_
- L37 _public prototype_ `static std::vector<char> getBytes();`

#### struct `dna::DecodedV28`  
`struct DecodedV28`  
_L40-187_
- L41 _public typedef_ `using VectorOfCharStringMatrix = pma::Vector<pma::Matrix<pma::String<char>>>;`
- L42 _public typedef_ `using StringPair = std::pair<pma::String<char>, pma::String<char>>;`
- L45 _public member_ `static const pma::String<char> name;` — Descriptor
- L46 _public member_ `static const Archetype archetype;`
- L47 _public member_ `static const Gender gender;`
- L48 _public member_ `static const std::uint16_t age;`
- L50 _public member_ `static const pma::Vector<StringPair> metadata;`
- L51 _public member_ `static const TranslationUnit translationUnit;`
- L52 _public member_ `static const RotationUnit rotationUnit;`
- L53 _public member_ `static const CoordinateSystem coordinateSystem;`
- L54 _public member_ `static const std::uint16_t lodCount[3ul];`
- L55 _public member_ `static const std::uint16_t maxLODs[3ul];`
- L56 _public member_ `static const pma::String<char> complexity;`
- L57 _public member_ `static const pma::String<char> dbName;`
- L60 _public member_ `static const pma::Vector<pma::String<char>> guiControlNames;` — Definition
- L61 _public member_ `static const pma::Vector<pma::String<char>> rawControlNames;`
- L62 _public member_ `static const VectorOfCharStringMatrix jointNames;`
- L63 _public member_ `static const VectorOfCharStringMatrix blendShapeNames;`
- L64 _public member_ `static const VectorOfCharStringMatrix animatedMapNames;`
- L65 _public member_ `static const VectorOfCharStringMatrix meshNames;`
- L66 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> meshBlendShapeIndices;`
- L67 _public member_ `static const pma::Matrix<std::uint16_t> jointHierarchy;`
- L68 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> neutralJointTranslations;`
- L69 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> neutralJointRotations;`
- L72 _public member_ `static const std::uint16_t guiControlCount;` — Behavior
- L73 _public member_ `static const std::uint16_t rawControlCount;`
- L74 _public member_ `static const std::uint16_t psdCount;`
- L75 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> conditionalInputIndices;`
- L76 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> conditionalOutputIndices;`
- L77 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalFromValues;`
- L78 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalToValues;`
- L79 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalSlopeValues;`
- L80 _public member_ `static const pma::Vector<pma::Matrix<float>> conditionalCutValues;`
- L81 _public member_ `static const pma::Vector<std::uint16_t> psdRowIndices;`
- L82 _public member_ `static const pma::Vector<std::uint16_t> psdColumnIndices;`
- L83 _public member_ `static const pma::Vector<float> psdValues;`
- L84 _public member_ `static const pma::Vector<std::uint16_t> jointRowCount;`
- L85 _public member_ `static const std::uint16_t jointColumnCount;`
- L86 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> jointVariableIndices;`
- L87 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> jointGroupLODs;`
- L88 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupInputIndices;`
- L89 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupOutputIndices;`
- L90 _public member_ `static const pma::Matrix<pma::Matrix<float>> jointGroupValues;`
- L91 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> jointGroupJointIndices;`
- L92 _public member_ `static const pma::Matrix<std::uint16_t> blendShapeLODs;`
- L93 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> blendShapeInputIndices;`
- L94 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> blendShapeOutputIndices;`
- L95 _public member_ `static const pma::Vector<std::uint16_t> animatedMapCount;`
- L96 _public member_ `static const pma::Matrix<std::uint16_t> animatedMapLODs;`
- L99 _public member_ `static const pma::Vector<std::uint32_t> meshCount;` — Geometry
- L100 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> vertexPositions;`
- L101 _public member_ `static const pma::Vector<pma::Matrix<TextureCoordinate>> vertexTextureCoordinates;`
- L102 _public member_ `static const pma::Vector<pma::Matrix<Vector3>> vertexNormals;`
- L103 _public member_ `static const pma::Vector<pma::Matrix<VertexLayout>> vertexLayouts;`
- L104 _public member_ `static const pma::Matrix<pma::Matrix<std::uint32_t>> faces;`
- L105 _public member_ `static const pma::Matrix<std::uint16_t> maxInfluencePerVertex;`
- L106 _public member_ `static const pma::Matrix<pma::Matrix<float>> skinWeightsValues;`
- L107 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> skinWeightsJointIndices;`
- L108 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> correctiveBlendShapeIndices;`
- L109 _public member_ `static const pma::Matrix<pma::Matrix<Vector3>> correctiveBlendShapeDeltas;`
- L110 _public member_ `static const pma::Matrix<pma::Matrix<std::uint32_t>> correctiveBlendShapeVertexIndices;`
- L113 _public member_ `static const pma::Vector<pma::String<char>> mlControlNames;` — Machine learned behavior
- L114 _public member_ `static const VectorOfCharStringMatrix regionNames;`
- L115 _public member_ `static const pma::Matrix<std::uint16_t> neuralNetworkIndicesPerLOD;`
- L116 _public member_ `static const pma::Matrix<pma::Matrix<std::uint16_t>> neuralNetworkIndicesPerMeshRegion;`
- L117 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkInputIndices;`
- L118 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkOutputIndices;`
- L119 _public member_ `static const pma::Matrix<std::uint16_t> neuralNetworkLayerCount;`
- L120 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> neuralNetworkActivationFunction;`
- L121 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkActivationFunctionParameters;`
- L122 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkBiases;`
- L123 _public member_ `static const pma::Matrix<pma::Matrix<float>> neuralNetworkWeights;`
- L126 _public member_ `static const pma::Vector<pma::String<char>> poseNames;` — RBF behavior
- L127 _public member_ `static const pma::Vector<std::uint16_t> poseDistanceMethod;`
- L128 _public member_ `static const pma::Vector<std::uint16_t> poseFunctionType;`
- L129 _public member_ `static const pma::Vector<float> poseScale;`
- L131 _public member_ `static const pma::Matrix<std::uint16_t> solverIndicesPerLOD;`
- L132 _public member_ `static const pma::Vector<pma::String<char>> solverNames;`
- L133 _public member_ `static const pma::Vector<float> solverRadius;`
- L134 _public member_ `static const pma::Vector<float> solverWeightThreshold;`
- L135 _public member_ `static const pma::Vector<std::uint16_t> solverType;`
- L136 _public member_ `static const pma::Vector<std::uint16_t> solverAutomaticRadius;`
- L137 _public member_ `static const pma::Vector<std::uint16_t> solverDistanceMethod;`
- L138 _public member_ `static const pma::Vector<std::uint16_t> solverNormalizeMethod;`
- L139 _public member_ `static const pma::Vector<std::uint16_t> solverFunctionType;`
- L140 _public member_ `static const pma::Vector<std::uint16_t> solverTwistAxis;`
- L141 _public member_ `static const pma::Matrix<std::uint16_t> solverRawControlIndices;`
- L142 _public member_ `static const pma::Matrix<std::uint16_t> solverPoseIndices;`
- L143 _public member_ `static const pma::Matrix<float> solverRawControlValues;`
- L146 _public member_ `static const pma::Vector<pma::String<char>> poseControlNames;` — RBF behavior ext
- L147 _public member_ `static const pma::Matrix<std::uint16_t> poseInputControlIndices;`
- L148 _public member_ `static const pma::Matrix<std::uint16_t> poseOutputControlIndices;`
- L149 _public member_ `static const pma::Matrix<float> poseOutputControlWeights;`
- L152 _public member_ `static const pma::Matrix<TranslationRepresentation> jointTranslationRepresentation;` — Joint behavior metadata
- L153 _public member_ `static const pma::Matrix<RotationRepresentation> jointRotationRepresentation;`
- L154 _public member_ `static const pma::Matrix<ScaleRepresentation> jointScaleRepresentation;`
- L157 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> swingInputControlIndices;` — Twist swing setups
- L158 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> swingOutputJointIndices;`
- L159 _public member_ `static const pma::Vector<pma::Matrix<float>> swingBlendWeights;`
- L160 _public member_ `static const pma::Matrix<TwistAxis> swingTwistAxes;`
- L161 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> twistInputControlIndices;`
- L162 _public member_ `static const pma::Vector<pma::Matrix<std::uint16_t>> twistOutputJointIndices;`
- L163 _public member_ `static const pma::Vector<pma::Matrix<float>> twistBlendWeights;`
- L164 _public member_ `static const pma::Matrix<TwistAxis> twistTwistAxes;`
- L167 _public member_ `static const pma::Matrix<pma::Matrix<MachineLearnedBehaviorOperationType>> mlOperationTypes;` — Machine learned behavior ext
- L168 _public member_ `static const pma::Vector<pma::Matrix<pma::Matrix<std::uint32_t>>> mlOperationParameters;`
- L169 _public member_ `static const pma::Vector<pma::Matrix<pma::Matrix<std::uint16_t>>> mlDependencyOperationSetIndices;`
- L170 _public member_ `static const pma::Vector<pma::Matrix<pma::Matrix<std::uint16_t>>> mlDependencyOperationIndices;`
- L171 _public member_ `static const pma::Vector<pma::Matrix<pma::Matrix<std::uint16_t>>> mlOperationIndicesPerLOD;`
- L174 _public member_ `static const RotationSequence rotationSequence;` — Descriptor ext
- L175 _public member_ `static const RotationSign rotationSign;`
- L176 _public member_ `static const FaceWindingOrder faceWindingOrder;`
- L178 _public prototype_ `static std::size_t lodConstraintToIndex(std::uint16_t maxLOD, std::uint16_t minLOD);`
- L179 _public prototype_ `static RawJoints getJoints(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L180 _public prototype_ `static RawBlendShapeChannels getBlendShapes(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L183 _public prototype_ `static RawConditionalTable getConditionals(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`
- L186 _public prototype_ `static RawAnimatedMaps getAnimatedMaps(std::uint16_t currentMaxLOD, std::uint16_t currentMinLOD, pma::MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/dnatests/TestBinaryStreamWriter.h` (Private)


#### class `BinaryStreamWriterTest`  
`class BinaryStreamWriterTest : public ::testing::Test`  
_L12-33_
- inherits: `::testing::Test`
- L14 _public prototype_ `~BinaryStreamWriterTest();`
- L17 _protected function_ `void SetUp() override`
- L23 _protected function_ `void TearDown() override`
- L29 _protected member_ `pma::ScopedPtr<trio::MemoryStream, pma::FactoryDestroy<trio::MemoryStream>> stream;`
- L30 _protected member_ `pma::DefaultMemoryResource memRes;`
- L31 _protected member_ `dna::BinaryStreamWriter* writer;`
- L32 _protected member_ `dna::BinaryStreamReader* reader;`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/dnatests/TestStreamReadWriteIntegration.h` (Private)


#### struct `APICopyParameters`  
`struct APICopyParameters`  
_L16-33_
- L17 _public typedef_ `using Reader = TReader;`
- L18 _public typedef_ `using Writer = TWriter;`
- L19 _public typedef_ `using RawBytes = TRawBytes;`
- L20 _public typedef_ `using DecodedData = TDecodedData;`
- L22 _public function_ `static constexpr std::uint16_t maxLOD()`
- L26 _public function_ `static constexpr std::uint16_t minLOD()`
- L30 _public function_ `static constexpr std::uint16_t currentLOD()`

#### class `StreamReadWriteAPICopyIntegrationTest`  
`template<typename TAPICopyParameters> class StreamReadWriteAPICopyIntegrationTest : public ::testing::Test`  
_L36-39_
- inherits: `::testing::Test`
- L38 _protected typedef_ `using Parameters = TAPICopyParameters;`

#### struct `RawCopyParameters`  
`struct RawCopyParameters`  
_L46-61_
- L47 _public typedef_ `using RawBytes = TRawBytes;`
- L48 _public typedef_ `using ExpectedBytes = TExpectedBytes;`
- L50 _public function_ `static constexpr dna::UnknownLayerPolicy policy()`
- L54 _public function_ `static constexpr std::uint16_t generation()`
- L58 _public function_ `static constexpr std::uint16_t version()`

#### class `StreamReadWriteRawCopyIntegrationTest`  
`template<typename TRawCopyParameters> class StreamReadWriteRawCopyIntegrationTest : public ::testing::Test`  
_L64-67_
- inherits: `::testing::Test`
- L66 _protected typedef_ `using Parameters = TRawCopyParameters;`

#### struct `ReadWriteMultipleParameters`  
`template<typename TRawBytes> struct ReadWriteMultipleParameters`  
_L70-72_
- L71 _public typedef_ `using RawBytes = TRawBytes;`

#### class `StreamReadWriteMultipleIntegrationTest`  
`template<typename TReadWriteMultipleParameters> class StreamReadWriteMultipleIntegrationTest : public ::testing::Test`  
_L75-78_
- inherits: `::testing::Test`
- L77 _protected typedef_ `using Parameters = TReadWriteMultipleParameters;`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/pmatests/Defs.h` (Private)


#### Free symbols / members of external scopes

- L24 _macro_ `#define INSTANTIATE_TEST_SUITE_P INSTANTIATE_TEST_CASE_P`
- L28 _macro_ `#define TYPED_TEST_SUITE_P TYPED_TEST_CASE_P`
- L32 _macro_ `#define REGISTER_TYPED_TEST_SUITE_P REGISTER_TYPED_TEST_CASE_P`
- L36 _macro_ `#define INSTANTIATE_TYPED_TEST_SUITE_P INSTANTIATE_TYPED_TEST_CASE_P`
- L40 _macro_ `#define ASSERT_ELEMENTS_EQ(result, expected, count) \`
- L47 _macro_ `#define EXPECT_ELEMENTS_EQ(result, expected, count) \`
- L54 _macro_ `#define ASSERT_ELEMENTS_NEAR(result, expected, count, threshold) \`
- L61 _macro_ `#define EXPECT_ELEMENTS_NEAR(result, expected, count, threshold) \`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/Defs.h` (Private)


#### Free symbols / members of external scopes

- L24 _macro_ `#define INSTANTIATE_TEST_SUITE_P INSTANTIATE_TEST_CASE_P`
- L28 _macro_ `#define TYPED_TEST_SUITE_P TYPED_TEST_CASE_P`
- L32 _macro_ `#define REGISTER_TYPED_TEST_SUITE_P REGISTER_TYPED_TEST_CASE_P`
- L36 _macro_ `#define INSTANTIATE_TYPED_TEST_SUITE_P INSTANTIATE_TYPED_TEST_CASE_P`
- L40 _macro_ `#define ASSERT_ELEMENTS_EQ(result, expected, count) \`
- L47 _macro_ `#define EXPECT_ELEMENTS_EQ(result, expected, count) \`
- L54 _macro_ `#define ASSERT_ELEMENTS_NEAR(result, expected, count, threshold) \`
- L61 _macro_ `#define EXPECT_ELEMENTS_NEAR(result, expected, count, threshold) \`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/StorageValueType.h` (Private)


#### Free symbols / members of external scopes

- L8 _typedef_ `using StorageValueType = std::uint16_t;`
- L10 _typedef_ `using StorageValueType = float;`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/animatedmaps/AnimatedMapFixtures.h` (Private)


#### struct `AnimatedMapsFactory`  
`struct AnimatedMapsFactory`  
_L11-15_
- L13 _public prototype_ `static rl4::AnimatedMapsImpl withDefaults(rl4::ConditionalTable&& conditionals, rl4::MemoryResource* memRes);`
- L14 _public prototype_ `static rl4::AnimatedMapsOutputInstance::Factory getInstanceFactory(std::uint16_t animatedMapCount);`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/blendshapes/BlendShapeFixtures.h` (Private)


#### struct `rltests::BlendShapesFactory`  
`struct BlendShapesFactory`  
_L35-38_
- L36 _public prototype_ `static rl4::BlendShapesImpl createTestBlendShapes(rl4::MemoryResource* memRes);`
- L37 _public prototype_ `static rl4::BlendShapesOutputInstance::Factory getInstanceFactory(std::uint16_t animatedMapCount);`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace rltests`
- L20 _variable_ `static const std::size_t LODCount = 4ul;` (scope `rltests`)
- L21 _variable_ `static const std::uint16_t LOD0 = 10u;` (scope `rltests`)
- L22 _variable_ `static const std::uint16_t LOD1 = 7u;` (scope `rltests`)
- L23 _variable_ `static const std::uint16_t LOD2 = 4u;` (scope `rltests`)
- L24 _variable_ `static const std::uint16_t LOD3 = 1u;` (scope `rltests`)
- L26 _variable_ `static const std::uint16_t LODs[] = {LOD0, LOD1, LOD2, LOD3};` (scope `rltests`)
- L28 _variable_ `static const std::array<float, 15ul> blendShapeInputs = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f};` (scope `rltests`)
- L30 _variable_ `static const std::uint16_t blendShapeCount = 10u;` (scope `rltests`)
- L31 _variable_ `static const std::uint16_t blendShapeInputIndices[blendShapeCount] = {0, 1, 3, 4, 6, 7, 8, 10, 12, 14};` (scope `rltests`)
- L32 _variable_ `static const std::uint16_t blendShapeOutputIndices[blendShapeCount] = {0, 2, 1, 3, 4, 5, 6, 7, 8, 9};` (scope `rltests`)
- L33 _variable_ `static const std::array<float, 10ul> blendShapeOutputs = {1.0f, 4.0f, 2.0f, 5.0f, 7.0f, 8.0f, 9.0f, 11.0f, 13.0f, 15.0f};` (scope `rltests`)

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/conditionaltable/ConditionalTableFixtures.h` (Private)


#### struct `ConditionalTableFactory`  
`struct ConditionalTableFactory`  
_L20-32_
- L22 _public prototype_ `static rl4::ConditionalTable withSingleIO(rl4::Vector<float>&& fromValues, rl4::Vector<float>&& toValues, rl4::Vector<float>&& cutValues, rl4::MemoryResource* memRes);`
- L26 _public prototype_ `static rl4::ConditionalTable withMultipleIO(rl4::Vector<float>&& fromValues, rl4::Vector<float>&& toValues, rl4::MemoryResource* memRes);`
- L29 _public prototype_ `static rl4::ConditionalTable withSingleIODefaults(rl4::MemoryResource* memRes);`
- L30 _public prototype_ `static rl4::ConditionalTable withMultipleIODefaults(rl4::MemoryResource* memRes);`
- L31 _public prototype_ `static rl4::ConditionalTable withInterleavedIO(rl4::MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L18 _variable_ `static const std::array<float, 9ul> conditionalTableInputs = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f};`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/controls/ControlFixtures.h` (Private)


#### struct `ControlsFactory`  
`struct ControlsFactory`  
_L10-16_
- L11 _public prototype_ `static rl4::ControlsInputInstance::Factory getInstanceFactory(std::uint16_t guiControlCount, std::uint16_t rawControlCount, std::uint16_t psdControlCount, std::uint16_t mlControlCount, std::uint16_t rbfControlCount);`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/dna/DNAFixtures.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace rltests`
- L12 _namespace_ `namespace raw` (scope `rltests`)
- L14 _externvar_ `extern const unsigned char header[91];` (scope `rltests::raw`)
- L15 _externvar_ `extern const unsigned char descriptor[87];` (scope `rltests::raw`)
- L16 _externvar_ `extern const unsigned char definition[794];` (scope `rltests::raw`)
- L17 _externvar_ `extern const unsigned char controls[2];` (scope `rltests::raw`)
- L18 _externvar_ `extern const unsigned char conditionals[324];` (scope `rltests::raw`)
- L19 _externvar_ `extern const unsigned char psds[204];` (scope `rltests::raw`)
- L20 _externvar_ `extern const unsigned char joints[444];` (scope `rltests::raw`)
- L21 _externvar_ `extern const unsigned char blendshapes[44];` (scope `rltests::raw`)
- L22 _externvar_ `extern const unsigned char animatedmaps[8];` (scope `rltests::raw`)
- L23 _externvar_ `extern const unsigned char geometry[1080];` (scope `rltests::raw`)
- L24 _externvar_ `extern const unsigned char machineLearnedBehavior[762];` (scope `rltests::raw`)
- L26 _prototype_ `std::vector<char> getBytes();` (scope `rltests::raw`)
- L30 _namespace_ `namespace decoded` (scope `rltests`)
- L32 _typedef_ `using VectorOfCharStringMatrix = Vector<Matrix<String<char>>>;` (scope `rltests::decoded`)
- L33 _typedef_ `using StringPair = std::pair<String<char>, String<char>>;` (scope `rltests::decoded`)
- L36 _externvar_ `extern const String<char> name;` (scope `rltests::decoded`) — Descriptor
- L37 _externvar_ `extern const Archetype archetype;` (scope `rltests::decoded`)
- L38 _externvar_ `extern const Gender gender;` (scope `rltests::decoded`)
- L39 _externvar_ `extern const std::uint16_t age;` (scope `rltests::decoded`)
- L41 _externvar_ `extern const Vector<StringPair> metadata;` (scope `rltests::decoded`)
- L42 _externvar_ `extern const TranslationUnit translationUnit;` (scope `rltests::decoded`)
- L43 _externvar_ `extern const RotationUnit rotationUnit;` (scope `rltests::decoded`)
- L44 _externvar_ `extern const CoordinateSystem coordinateSystem;` (scope `rltests::decoded`)
- L45 _externvar_ `extern const std::uint16_t lodCount[3ul];` (scope `rltests::decoded`)
- L46 _externvar_ `extern const std::uint16_t maxLODs[3ul];` (scope `rltests::decoded`)
- L47 _externvar_ `extern const String<char> complexity;` (scope `rltests::decoded`)
- L48 _externvar_ `extern const String<char> dbName;` (scope `rltests::decoded`)
- L51 _externvar_ `extern const Vector<String<char>> guiControlNames;` (scope `rltests::decoded`) — Definition
- L52 _externvar_ `extern const Vector<String<char>> rawControlNames;` (scope `rltests::decoded`)
- L53 _externvar_ `extern const VectorOfCharStringMatrix jointNames;` (scope `rltests::decoded`)
- L54 _externvar_ `extern const VectorOfCharStringMatrix blendShapeNames;` (scope `rltests::decoded`)
- L55 _externvar_ `extern const VectorOfCharStringMatrix animatedMapNames;` (scope `rltests::decoded`)
- L56 _externvar_ `extern const VectorOfCharStringMatrix meshNames;` (scope `rltests::decoded`)
- L57 _externvar_ `extern const Vector<Matrix<std::uint16_t>> meshBlendShapeIndices;` (scope `rltests::decoded`)
- L58 _externvar_ `extern const Matrix<std::uint16_t> jointHierarchy;` (scope `rltests::decoded`)
- L59 _externvar_ `extern const Vector<Matrix<Vector3>> neutralJointTranslations;` (scope `rltests::decoded`)
- L60 _externvar_ `extern const Vector<Matrix<Vector3>> neutralJointRotations;` (scope `rltests::decoded`)
- L63 _externvar_ `extern const std::uint16_t guiControlCount;` (scope `rltests::decoded`) — Behavior
- L64 _externvar_ `extern const std::uint16_t rawControlCount;` (scope `rltests::decoded`)
- L65 _externvar_ `extern const std::uint16_t psdControlCount;` (scope `rltests::decoded`)
- L66 _externvar_ `extern const Vector<Matrix<std::uint16_t>> conditionalInputIndices;` (scope `rltests::decoded`)
- L67 _externvar_ `extern const Vector<Matrix<std::uint16_t>> conditionalOutputIndices;` (scope `rltests::decoded`)
- L68 _externvar_ `extern const Vector<Matrix<float>> conditionalFromValues;` (scope `rltests::decoded`)
- L69 _externvar_ `extern const Vector<Matrix<float>> conditionalToValues;` (scope `rltests::decoded`)
- L70 _externvar_ `extern const Vector<Matrix<float>> conditionalSlopeValues;` (scope `rltests::decoded`)
- L71 _externvar_ `extern const Vector<Matrix<float>> conditionalCutValues;` (scope `rltests::decoded`)
- L72 _externvar_ `extern const Vector<std::uint16_t> psdRowIndices;` (scope `rltests::decoded`)
- L73 _externvar_ `extern const Vector<std::uint16_t> psdColumnIndices;` (scope `rltests::decoded`)
- L74 _externvar_ `extern const Vector<float> psdValues;` (scope `rltests::decoded`)
- L75 _externvar_ `extern const Vector<std::uint16_t> jointRowCount;` (scope `rltests::decoded`)
- L76 _externvar_ `extern const std::uint16_t jointColumnCount;` (scope `rltests::decoded`)
- L77 _externvar_ `extern const Vector<Matrix<std::uint16_t>> jointVariableIndices;` (scope `rltests::decoded`)
- L78 _externvar_ `extern const Vector<Matrix<std::uint16_t>> jointGroupLODs;` (scope `rltests::decoded`)
- L79 _externvar_ `extern const Matrix<Matrix<std::uint16_t>> jointGroupInputIndices;` (scope `rltests::decoded`)
- L80 _externvar_ `extern const Matrix<Matrix<std::uint16_t>> jointGroupOutputIndices;` (scope `rltests::decoded`)
- L81 _externvar_ `extern const Matrix<Matrix<float>> jointGroupValues;` (scope `rltests::decoded`)
- L82 _externvar_ `extern const Matrix<Matrix<std::uint16_t>> jointGroupJointIndices;` (scope `rltests::decoded`)
- L83 _externvar_ `extern const Matrix<std::uint16_t> blendShapeLODs;` (scope `rltests::decoded`)
- L84 _externvar_ `extern const Vector<Matrix<std::uint16_t>> blendShapeInputIndices;` (scope `rltests::decoded`)
- L85 _externvar_ `extern const Vector<Matrix<std::uint16_t>> blendShapeOutputIndices;` (scope `rltests::decoded`)
- L86 _externvar_ `extern const Vector<std::uint16_t> animatedMapCount;` (scope `rltests::decoded`)
- L87 _externvar_ `extern const Matrix<std::uint16_t> animatedMapLODs;` (scope `rltests::decoded`)
- L90 _externvar_ `extern const Vector<std::uint32_t> meshCount;` (scope `rltests::decoded`) — Geometry
- L91 _externvar_ `extern const Vector<Matrix<Vector3>> vertexPositions;` (scope `rltests::decoded`)
- L92 _externvar_ `extern const Vector<Matrix<TextureCoordinate>> vertexTextureCoordinates;` (scope `rltests::decoded`)
- L93 _externvar_ `extern const Vector<Matrix<Vector3>> vertexNormals;` (scope `rltests::decoded`)
- L94 _externvar_ `extern const Vector<Matrix<VertexLayout>> vertexLayouts;` (scope `rltests::decoded`)
- L95 _externvar_ `extern const Matrix<Matrix<std::uint32_t>> faces;` (scope `rltests::decoded`)
- L96 _externvar_ `extern const Matrix<std::uint16_t> maxInfluencePerVertex;` (scope `rltests::decoded`)
- L97 _externvar_ `extern const Matrix<Matrix<float>> skinWeightsValues;` (scope `rltests::decoded`)
- L98 _externvar_ `extern const Matrix<Matrix<std::uint16_t>> skinWeightsJointIndices;` (scope `rltests::decoded`)
- L99 _externvar_ `extern const Vector<Matrix<std::uint16_t>> correctiveBlendShapeIndices;` (scope `rltests::decoded`)
- L100 _externvar_ `extern const Matrix<Matrix<Vector3>> correctiveBlendShapeDeltas;` (scope `rltests::decoded`)
- L101 _externvar_ `extern const Matrix<Matrix<std::uint32_t>> correctiveBlendShapeVertexIndices;` (scope `rltests::decoded`)
- L104 _externvar_ `extern const Vector<String<char>> mlControlNames;` (scope `rltests::decoded`) — Machine learned behavior
- L105 _externvar_ `extern const VectorOfCharStringMatrix regionNames;` (scope `rltests::decoded`)
- L106 _externvar_ `extern const Matrix<std::uint16_t> neuralNetworkIndicesPerLOD;` (scope `rltests::decoded`)
- L107 _externvar_ `extern const Matrix<Matrix<std::uint16_t>> neuralNetworkIndicesPerMeshRegion;` (scope `rltests::decoded`)
- L108 _externvar_ `extern const Vector<Matrix<std::uint16_t>> neuralNetworkInputIndices;` (scope `rltests::decoded`)
- L109 _externvar_ `extern const Vector<Matrix<std::uint16_t>> neuralNetworkOutputIndices;` (scope `rltests::decoded`)
- L110 _externvar_ `extern const Matrix<std::uint16_t> neuralNetworkLayerCount;` (scope `rltests::decoded`)
- L111 _externvar_ `extern const Vector<Matrix<std::uint16_t>> neuralNetworkActivationFunction;` (scope `rltests::decoded`)
- L112 _externvar_ `extern const Matrix<Matrix<float>> neuralNetworkActivationFunctionParameters;` (scope `rltests::decoded`)
- L113 _externvar_ `extern const Matrix<Matrix<float>> neuralNetworkBiases;` (scope `rltests::decoded`)
- L114 _externvar_ `extern const Matrix<Matrix<float>> neuralNetworkWeights;` (scope `rltests::decoded`)

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/dna/FakeReader.h` (Private)


#### class `dna::FakeReader`  
`class FakeReader : public Reader`  
_L22-782_
- inherits: `Reader`
- L24 _public prototype_ `~FakeReader();`
- L27 _public function_ `std::uint16_t getFileFormatGeneration() const override` — HeaderReader methods
- L31 _public function_ `std::uint16_t getFileFormatVersion() const override`
- L36 _public function_ `StringView getName() const override` — DescriptorReader methods start
- L40 _public function_ `Archetype getArchetype() const override`
- L44 _public function_ `Gender getGender() const override`
- L48 _public function_ `std::uint16_t getAge() const override`
- L52 _public function_ `std::uint32_t getMetaDataCount() const override`
- L56 _public function_ `StringView getMetaDataKey(std::uint32_t index) const override`
- L60 _public function_ `StringView getMetaDataValue(const char* key) const override`
- L64 _public function_ `TranslationUnit getTranslationUnit() const override`
- L68 _public function_ `RotationUnit getRotationUnit() const override`
- L72 _public function_ `CoordinateSystem getCoordinateSystem() const override`
- L76 _public function_ `RotationSequence getRotationSequence() const override`
- L80 _public function_ `RotationSign getRotationSign() const override`
- L84 _public function_ `FaceWindingOrder getFaceWindingOrder() const override`
- L88 _public function_ `std::uint16_t getLODCount() const override`
- L92 _public function_ `std::uint16_t getDBMaxLOD() const override`
- L96 _public function_ `StringView getDBComplexity() const override`
- L100 _public function_ `StringView getDBName() const override`
- L105 _public function_ `std::uint16_t getGUIControlCount() const override` — DefinitionReader methods
- L109 _public function_ `StringView getGUIControlName(std::uint16_t index) const override`
- L113 _public function_ `std::uint16_t getRawControlCount() const override`
- L117 _public function_ `StringView getRawControlName(std::uint16_t index) const override`
- L121 _public function_ `std::uint16_t getJointCount() const override`
- L125 _public function_ `StringView getJointName(std::uint16_t index) const override`
- L129 _public function_ `std::uint16_t getJointIndexListCount() const override`
- L133 _public function_ `ConstArrayView<std::uint16_t> getJointIndicesForLOD(std::uint16_t lod) const override`
- L137 _public function_ `std::uint16_t getJointParentIndex(std::uint16_t index) const override`
- L141 _public function_ `std::uint16_t getBlendShapeChannelCount() const override`
- L145 _public function_ `StringView getBlendShapeChannelName(std::uint16_t index) const override`
- L149 _public function_ `std::uint16_t getBlendShapeChannelIndexListCount() const override`
- L153 _public function_ `ConstArrayView<std::uint16_t> getBlendShapeChannelIndicesForLOD(std::uint16_t lod) const override`
- L157 _public function_ `std::uint16_t getAnimatedMapCount() const override`
- L161 _public function_ `std::uint16_t getAnimatedMapIndexListCount() const override`
- L165 _public function_ `ConstArrayView<std::uint16_t> getAnimatedMapIndicesForLOD(std::uint16_t lod) const override`
- L169 _public function_ `StringView getAnimatedMapName(std::uint16_t index) const override`
- L173 _public function_ `std::uint16_t getMeshCount() const override`
- L177 _public function_ `StringView getMeshName(std::uint16_t index) const override`
- L181 _public function_ `std::uint16_t getMeshBlendShapeChannelMappingCount() const override`
- L185 _public function_ `MeshBlendShapeChannelMapping getMeshBlendShapeChannelMapping(std::uint16_t index) const override`
- L189 _public function_ `ConstArrayView<std::uint16_t> getMeshBlendShapeChannelMappingIndicesForLOD(std::uint16_t lod) const override`
- L193 _public function_ `std::uint16_t getMeshIndexListCount() const override`
- L197 _public function_ `ConstArrayView<std::uint16_t> getMeshIndicesForLOD(std::uint16_t lod) const override`
- L201 _public function_ `Vector3 getNeutralJointTranslation(std::uint16_t index) const override`
- L205 _public function_ `ConstArrayView<float> getNeutralJointTranslationXs() const override`
- L209 _public function_ `ConstArrayView<float> getNeutralJointTranslationYs() const override`
- L213 _public function_ `ConstArrayView<float> getNeutralJointTranslationZs() const override`
- L217 _public function_ `Vector3 getNeutralJointRotation(std::uint16_t index) const override`
- L221 _public function_ `ConstArrayView<float> getNeutralJointRotationXs() const override`
- L225 _public function_ `ConstArrayView<float> getNeutralJointRotationYs() const override`
- L229 _public function_ `ConstArrayView<float> getNeutralJointRotationZs() const override`
- L234 _public function_ `ConstArrayView<std::uint16_t> getGUIToRawInputIndices() const override` — BehaviorReader methods
- L238 _public function_ `ConstArrayView<std::uint16_t> getGUIToRawOutputIndices() const override`
- L242 _public function_ `ConstArrayView<float> getGUIToRawFromValues() const override`
- L246 _public function_ `ConstArrayView<float> getGUIToRawToValues() const override`
- L250 _public function_ `ConstArrayView<float> getGUIToRawSlopeValues() const override`
- L254 _public function_ `ConstArrayView<float> getGUIToRawCutValues() const override`
- L258 _public function_ `std::uint16_t getPSDCount() const override`
- L262 _public function_ `ConstArrayView<std::uint16_t> getPSDRowIndices() const override`
- L266 _public function_ `ConstArrayView<std::uint16_t> getPSDColumnIndices() const override`
- L270 _public function_ `ConstArrayView<float> getPSDValues() const override`
- L274 _public function_ `ConstArrayView<std::uint16_t> getJointVariableAttributeIndices(std::uint16_t lod) const override`
- L278 _public function_ `std::uint16_t getJointRowCount() const override`
- L282 _public function_ `std::uint16_t getJointColumnCount() const override`
- L286 _public function_ `std::uint16_t getJointGroupCount() const override`
- L290 _public function_ `ConstArrayView<std::uint16_t> getJointGroupLODs(std::uint16_t jointGroupIndex) const override`
- L294 _public function_ `ConstArrayView<std::uint16_t> getJointGroupInputIndices(std::uint16_t jointGroupIndex) const override`
- L298 _public function_ `ConstArrayView<std::uint16_t> getJointGroupOutputIndices(std::uint16_t jointGroupIndex) const override`
- L302 _public function_ `ConstArrayView<float> getJointGroupValues(std::uint16_t jointGroupIndex) const override`
- L306 _public function_ `ConstArrayView<std::uint16_t> getJointGroupJointIndices(std::uint16_t jointGroupIndex) const override`
- L310 _public function_ `ConstArrayView<std::uint16_t> getBlendShapeChannelLODs() const override`
- L314 _public function_ `ConstArrayView<std::uint16_t> getBlendShapeChannelInputIndices() const override`
- L318 _public function_ `ConstArrayView<std::uint16_t> getBlendShapeChannelOutputIndices() const override`
- L322 _public function_ `ConstArrayView<std::uint16_t> getAnimatedMapLODs() const override`
- L326 _public function_ `ConstArrayView<std::uint16_t> getAnimatedMapInputIndices() const override`
- L330 _public function_ `ConstArrayView<std::uint16_t> getAnimatedMapOutputIndices() const override`
- L334 _public function_ `ConstArrayView<float> getAnimatedMapFromValues() const override`
- L338 _public function_ `ConstArrayView<float> getAnimatedMapToValues() const override`
- L342 _public function_ `ConstArrayView<float> getAnimatedMapSlopeValues() const override`
- L346 _public function_ `ConstArrayView<float> getAnimatedMapCutValues() const override`
- L351 _public function_ `std::uint32_t getVertexPositionCount(std::uint16_t meshIndex) const override` — GeometryReader methods
- L355 _public function_ `Position getVertexPosition(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L359 _public function_ `ConstArrayView<float> getVertexPositionXs(std::uint16_t meshIndex) const override`
- L363 _public function_ `ConstArrayView<float> getVertexPositionYs(std::uint16_t meshIndex) const override`
- L367 _public function_ `ConstArrayView<float> getVertexPositionZs(std::uint16_t meshIndex) const override`
- L371 _public function_ `std::uint32_t getVertexTextureCoordinateCount(std::uint16_t meshIndex) const override`
- L375 _public function_ `TextureCoordinate getVertexTextureCoordinate(std::uint16_t meshIndex, std::uint32_t textureCoordinateIndex) const override`
- L379 _public function_ `ConstArrayView<float> getVertexTextureCoordinateUs(std::uint16_t meshIndex) const override`
- L383 _public function_ `ConstArrayView<float> getVertexTextureCoordinateVs(std::uint16_t meshIndex) const override`
- L387 _public function_ `std::uint32_t getVertexNormalCount(std::uint16_t meshIndex) const override`
- L391 _public function_ `Normal getVertexNormal(std::uint16_t meshIndex, std::uint32_t normalIndex) const override`
- L395 _public function_ `ConstArrayView<float> getVertexNormalXs(std::uint16_t meshIndex) const override`
- L399 _public function_ `ConstArrayView<float> getVertexNormalYs(std::uint16_t meshIndex) const override`
- L403 _public function_ `ConstArrayView<float> getVertexNormalZs(std::uint16_t meshIndex) const override`
- L407 _public function_ `std::uint32_t getFaceCount(std::uint16_t meshIndex) const override`
- L411 _public function_ `ConstArrayView<std::uint32_t> getFaceVertexLayoutIndices(std::uint16_t meshIndex, std::uint32_t faceIndex) const override`
- L415 _public function_ `std::uint32_t getVertexLayoutCount(std::uint16_t meshIndex) const override`
- L419 _public function_ `VertexLayout getVertexLayout(std::uint16_t meshIndex, std::uint32_t layoutIndex) const override`
- L423 _public function_ `ConstArrayView<std::uint32_t> getVertexLayoutPositionIndices(std::uint16_t meshIndex) const override`
- L427 _public function_ `ConstArrayView<std::uint32_t> getVertexLayoutTextureCoordinateIndices(std::uint16_t meshIndex) const override`
- L431 _public function_ `ConstArrayView<std::uint32_t> getVertexLayoutNormalIndices(std::uint16_t meshIndex) const override`
- L435 _public function_ `std::uint16_t getMaximumInfluencePerVertex(std::uint16_t meshIndex) const override`
- L439 _public function_ `std::uint32_t getSkinWeightsCount(std::uint16_t meshIndex) const override`
- L443 _public function_ `ConstArrayView<float> getSkinWeightsValues(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L447 _public function_ `ConstArrayView<std::uint16_t> getSkinWeightsJointIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L451 _public function_ `std::uint16_t getBlendShapeTargetCount(std::uint16_t meshIndex) const override`
- L455 _public function_ `std::uint16_t getBlendShapeChannelIndex(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L459 _public function_ `std::uint32_t getBlendShapeTargetDeltaCount(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L463 _public function_ `Delta getBlendShapeTargetDelta(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, std::uint32_t deltaIndex) const override`
- L469 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaXs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L474 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaYs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L479 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaZs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L484 _public function_ `ConstArrayView<std::uint32_t> getBlendShapeTargetVertexIndices(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L490 _public function_ `std::uint16_t getMLControlCount() const override` — MachineLearnedBehaviorReader methods
- L494 _public function_ `StringView getMLControlName(std::uint16_t index) const override`
- L498 _public function_ `std::uint16_t getNeuralNetworkCount() const override`
- L502 _public function_ `std::uint16_t getNeuralNetworkIndexListCount() const override`
- L506 _public function_ `ConstArrayView<std::uint16_t> getNeuralNetworkIndicesForLOD(std::uint16_t lod) const override`
- L510 _public function_ `std::uint16_t getMeshRegionCount(std::uint16_t meshIndex) const override`
- L514 _public function_ `StringView getMeshRegionName(std::uint16_t meshIndex, std::uint16_t regionIndex) const override`
- L518 _public function_ `ConstArrayView<std::uint16_t> getNeuralNetworkIndicesForMeshRegion(std::uint16_t meshIndex, std::uint16_t regionIndex) const override`
- L523 _public function_ `ConstArrayView<std::uint16_t> getNeuralNetworkInputIndices(std::uint16_t neuralNetIndex) const override`
- L527 _public function_ `ConstArrayView<std::uint16_t> getNeuralNetworkOutputIndices(std::uint16_t neuralNetIndex) const override`
- L531 _public function_ `std::uint16_t getNeuralNetworkLayerCount(std::uint16_t neuralNetIndex) const override`
- L535 _public function_ `ActivationFunction getNeuralNetworkLayerActivationFunction(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L540 _public function_ `ConstArrayView<float> getNeuralNetworkLayerActivationFunctionParameters(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L545 _public function_ `ConstArrayView<float> getNeuralNetworkLayerBiases(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L549 _public function_ `ConstArrayView<float> getNeuralNetworkLayerWeights(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L554 _public function_ `std::uint16_t getRBFPoseCount() const override` — RBFBehaviorReader
- L558 _public function_ `StringView getRBFPoseName(std::uint16_t poseIndex) const override`
- L562 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseJointOutputIndices(std::uint16_t poseIndex) const override`
- L566 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseBlendShapeChannelOutputIndices(std::uint16_t poseIndex) const override`
- L570 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseAnimatedMapOutputIndices(std::uint16_t poseIndex) const override`
- L574 _public function_ `ConstArrayView<float> getRBFPoseJointOutputValues(std::uint16_t poseIndex) const override`
- L578 _public function_ `float getRBFPoseScale(std::uint16_t poseIndex) const override`
- L582 _public function_ `std::uint16_t getRBFPoseControlCount() const override`
- L586 _public function_ `StringView getRBFPoseControlName(std::uint16_t poseControlIndex) const override`
- L590 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseInputControlIndices(std::uint16_t poseIndex) const override`
- L594 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseOutputControlIndices(std::uint16_t poseIndex) const override`
- L598 _public function_ `ConstArrayView<float> getRBFPoseOutputControlWeights(std::uint16_t poseIndex) const override`
- L602 _public function_ `std::uint16_t getRBFSolverCount() const override`
- L606 _public function_ `std::uint16_t getRBFSolverIndexListCount() const override`
- L610 _public function_ `ConstArrayView<std::uint16_t> getRBFSolverIndicesForLOD(std::uint16_t lod) const override`
- L614 _public function_ `StringView getRBFSolverName(std::uint16_t index) const override`
- L618 _public function_ `ConstArrayView<std::uint16_t> getRBFSolverRawControlIndices(std::uint16_t solverIndex) const override`
- L622 _public function_ `ConstArrayView<std::uint16_t> getRBFSolverPoseIndices(std::uint16_t solverIndex) const override`
- L626 _public function_ `ConstArrayView<float> getRBFSolverRawControlValues(std::uint16_t solverIndex) const override`
- L630 _public function_ `RBFSolverType getRBFSolverType(std::uint16_t solverIndex) const override`
- L634 _public function_ `float getRBFSolverRadius(std::uint16_t solverIndex) const override`
- L638 _public function_ `AutomaticRadius getRBFSolverAutomaticRadius(std::uint16_t solverIndex) const override`
- L642 _public function_ `float getRBFSolverWeightThreshold(std::uint16_t solverIndex) const override`
- L646 _public function_ `RBFDistanceMethod getRBFSolverDistanceMethod(std::uint16_t solverIndex) const override`
- L650 _public function_ `RBFNormalizeMethod getRBFSolverNormalizeMethod(std::uint16_t solverIndex) const override`
- L654 _public function_ `RBFFunctionType getRBFSolverFunctionType(std::uint16_t solverIndex) const override`
- L658 _public function_ `TwistAxis getRBFSolverTwistAxis(std::uint16_t solverIndex) const override`
- L663 _public function_ `TranslationRepresentation getJointTranslationRepresentation(std::uint16_t jointIndex) const override` — JointBehaviorMetadataReader
- L667 _public function_ `RotationRepresentation getJointRotationRepresentation(std::uint16_t jointIndex) const override`
- L671 _public function_ `ScaleRepresentation getJointScaleRepresentation(std::uint16_t jointIndex) const override`
- L676 _public function_ `std::uint16_t getTwistCount() const override` — TwistSwingBehaviorReader
- L680 _public function_ `TwistAxis getTwistSetupTwistAxis(std::uint16_t twistIndex) const override`
- L684 _public function_ `ConstArrayView<std::uint16_t> getTwistInputControlIndices(std::uint16_t twistIndex) const override`
- L688 _public function_ `ConstArrayView<std::uint16_t> getTwistOutputJointIndices(std::uint16_t twistIndex) const override`
- L692 _public function_ `ConstArrayView<float> getTwistBlendWeights(std::uint16_t twistIndex) const override`
- L696 _public function_ `std::uint16_t getSwingCount() const override`
- L700 _public function_ `TwistAxis getSwingSetupTwistAxis(std::uint16_t swingIndex) const override`
- L704 _public function_ `ConstArrayView<std::uint16_t> getSwingInputControlIndices(std::uint16_t swingIndex) const override`
- L708 _public function_ `ConstArrayView<std::uint16_t> getSwingOutputJointIndices(std::uint16_t swingIndex) const override`
- L712 _public function_ `ConstArrayView<float> getSwingBlendWeights(std::uint16_t swingIndex) const override`
- L718 _public function_ `std::uint16_t getMLTypeCount() const override`
- L722 _public function_ `std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const override`
- L726 _public function_ `std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override`
- L730 _public function_ `MachineLearnedBehaviorOperationType getMLOperationType(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L736 _public function_ `ConstArrayView<std::uint32_t> getMLOperationParameters(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L742 _public function_ `ConstArrayView<std::uint16_t> getMLOperationDependencyOperationSetIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L748 _public function_ `ConstArrayView<std::uint16_t> getMLOperationDependencyOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L754 _public function_ `std::uint16_t getMLOperationIndexListCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override`
- L758 _public function_ `ConstArrayView<std::uint16_t> getMLOperationIndicesForLOD(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t lod) const override`
- L764 _public function_ `ConstArrayView<std::uint16_t> getMLJointsInputIndices() const override`
- L768 _public function_ `ConstArrayView<std::uint16_t> getMLJointsOutputIndices() const override`
- L772 _public function_ `ConstArrayView<std::uint16_t> getMLJointsParameterKeys() const override`
- L776 _public function_ `ConstArrayView<std::uint16_t> getMLJointsParameterValues() const override`
- L780 _public function_ `void unload(DataLayer ) override`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/joints/Helpers.h` (Private)


#### struct `RotationOutputTypeSelector`  
`template<> struct RotationOutputTypeSelector<rl4::PassthroughAdapter>`  
_L14-22_
- L15 _public function_ `static constexpr std::size_t value()`
- L19 _public function_ `static constexpr rl4::RotationType rotation()`

#### struct `RotationOutputTypeSelector`  
`template<typename T> struct RotationOutputTypeSelector<rl4::QuaternionsToEulerAngles<T, tdm::rot_seq::zyx>>`  
_L25-33_
- L15 _public function_ `static constexpr std::size_t value()`
- L19 _public function_ `static constexpr rl4::RotationType rotation()`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/joints/bpcm/Assertions.h` (Private)


#### struct `rl4::CPUJointsEvaluator::Accessor`  
`struct CPUJointsEvaluator::Accessor`  
_L12-21_
- L14 _public function_ `static JointsEvaluator* getBPCMEvaluator(CPUJointsEvaluator* parent)`
- L18 _public function_ `static JointsEvaluator* getQuaternionEvaluator(CPUJointsEvaluator* parent)`

#### struct `rl4::bpcm::Evaluator::Accessor`  
`struct Evaluator::Accessor`  
_L25-70_
- L28 _public function_ `template<typename T> static void assertRawDataEqual(const Evaluator& result, const Evaluator& expected)`
- L38 _public function_ `template<typename T> static void assertJointGroupsEqual(const Evaluator& result, const Evaluator& expected)`
- L56 _public function_ `template<typename T> static void assertLODsEqual(const Evaluator& result, const Evaluator& expected)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`
- L23 _namespace_ `namespace bpcm` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/joints/bpcm/BPCMFixturesBlock4.h` (Private)


#### class `block4::CanonicalReader`  
`class CanonicalReader : public dna::FakeReader`  
_L77-144_
- inherits: `dna::FakeReader`
- L79 _public prototype_ `~CanonicalReader();`
- L81 _public function_ `std::uint16_t getLODCount() const override`
- L85 _public function_ `std::uint16_t getRawControlCount() const override`
- L89 _public function_ `std::uint16_t getJointCount() const override`
- L93 _public function_ `ConstArrayView<float> getNeutralJointTranslationXs() const override`
- L97 _public function_ `ConstArrayView<float> getNeutralJointTranslationYs() const override`
- L101 _public function_ `ConstArrayView<float> getNeutralJointTranslationZs() const override`
- L105 _public function_ `ConstArrayView<float> getNeutralJointRotationXs() const override`
- L109 _public function_ `ConstArrayView<float> getNeutralJointRotationYs() const override`
- L113 _public function_ `ConstArrayView<float> getNeutralJointRotationZs() const override`
- L117 _public function_ `std::uint16_t getJointRowCount() const override`
- L121 _public function_ `std::uint16_t getJointColumnCount() const override`
- L125 _public function_ `std::uint16_t getJointGroupCount() const override`
- L129 _public function_ `ConstArrayView<std::uint16_t> getJointGroupLODs(std::uint16_t jointGroupIndex) const override`
- L133 _public function_ `ConstArrayView<std::uint16_t> getJointGroupInputIndices(std::uint16_t jointGroupIndex) const override`
- L137 _public function_ `ConstArrayView<std::uint16_t> getJointGroupOutputIndices(std::uint16_t jointGroupIndex) const override`
- L141 _public function_ `ConstArrayView<float> getJointGroupValues(std::uint16_t jointGroupIndex) const override`

#### struct `block4::OptimizedStorage`  
`template<typename TValue> struct OptimizedStorage`  
_L147-160_
- L148 _public typedef_ `using StrategyPtr = std::unique_ptr<bpcm::JointGroupLinearCalculationStrategy, std::function<void(bpcm::JointGroupLinearCalculationStrategy*)>>;`
- L151 _public prototype_ `static bpcm::Evaluator create(StrategyPtr strategy, std::size_t rotationSelectorIndex, rl4::RotationType rotationType, MemoryResource* memRes);`
- L155 _public prototype_ `static bpcm::Evaluator create(StrategyPtr strategy, std::size_t rotationSelectorIndex, rl4::RotationType rotationType, std::uint16_t jointGroupIndex, MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace block4`
- L30 _namespace_ `namespace unoptimized` (scope `block4`)
- L32 _externvar_ `extern const tdm::rot_sign rotationSigns;` (scope `block4::unoptimized`)
- L33 _externvar_ `extern const std::uint16_t lodCount;` (scope `block4::unoptimized`)
- L34 _externvar_ `extern const std::uint16_t rawControlCount;` (scope `block4::unoptimized`)
- L35 _externvar_ `extern const Extent dimensions;` (scope `block4::unoptimized`)
- L36 _externvar_ `extern const Matrix<float> values;` (scope `block4::unoptimized`)
- L37 _externvar_ `extern const Matrix<std::uint16_t> inputIndices;` (scope `block4::unoptimized`)
- L38 _externvar_ `extern const Matrix<std::uint16_t> outputIndices;` (scope `block4::unoptimized`)
- L39 _externvar_ `extern const Matrix<std::uint16_t> lods;` (scope `block4::unoptimized`)
- L40 _externvar_ `extern const Vector<float> neutralJointTranslationXs;` (scope `block4::unoptimized`)
- L41 _externvar_ `extern const Vector<float> neutralJointTranslationYs;` (scope `block4::unoptimized`)
- L42 _externvar_ `extern const Vector<float> neutralJointTranslationZs;` (scope `block4::unoptimized`)
- L43 _externvar_ `extern const Vector<float> neutralJointRotationXs;` (scope `block4::unoptimized`)
- L44 _externvar_ `extern const Vector<float> neutralJointRotationYs;` (scope `block4::unoptimized`)
- L45 _externvar_ `extern const Vector<float> neutralJointRotationZs;` (scope `block4::unoptimized`)
- L49 _namespace_ `namespace optimized` (scope `block4`)
- L51 _externvar_ `extern const Extent dimensions;` (scope `block4::optimized`)
- L52 _externvar_ `extern const AlignedMatrix<float> floatValues;` (scope `block4::optimized`)
- L53 _externvar_ `extern const AlignedMatrix<std::uint16_t> halfFloatValues;` (scope `block4::optimized`)
- L54 _externvar_ `extern const AlignedMatrix<std::uint16_t> inputIndices;` (scope `block4::optimized`)
- L55 _externvar_ `extern const Vector<Vector<AlignedVector<std::uint16_t>>> outputIndices;` (scope `block4::optimized`)
- L56 _externvar_ `extern const Vector<Vector<AlignedVector<std::uint16_t>>> outputRotationIndices;` (scope `block4::optimized`)
- L57 _externvar_ `extern const Vector<Vector<AlignedVector<std::uint16_t>>> outputRotationLODs;` (scope `block4::optimized`)
- L58 _externvar_ `extern const Vector<Vector<bpcm::JointGroup>> jointGroups;` (scope `block4::optimized`)
- L59 _externvar_ `extern const Matrix<LODRegion> lodRegions;` (scope `block4::optimized`)
- L63 _namespace_ `namespace input` (scope `block4`)
- L66 _externvar_ `extern const Vector<float> values;` (scope `block4::input`) — Calculation input values
- L70 _namespace_ `namespace output` (scope `block4`)
- L73 _externvar_ `extern const Vector<Matrix<float>> valuesPerLOD;` (scope `block4::output`) — Calculation output values

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/joints/bpcm/BPCMFixturesBlock8.h` (Private)


#### class `block8::CanonicalReader`  
`class CanonicalReader : public dna::FakeReader`  
_L71-110_
- inherits: `dna::FakeReader`
- L73 _public prototype_ `~CanonicalReader();`
- L75 _public function_ `std::uint16_t getLODCount() const override`
- L79 _public function_ `std::uint16_t getRawControlCount() const override`
- L83 _public function_ `std::uint16_t getJointRowCount() const override`
- L87 _public function_ `std::uint16_t getJointColumnCount() const override`
- L91 _public function_ `std::uint16_t getJointGroupCount() const override`
- L95 _public function_ `ConstArrayView<std::uint16_t> getJointGroupLODs(std::uint16_t jointGroupIndex) const override`
- L99 _public function_ `ConstArrayView<std::uint16_t> getJointGroupInputIndices(std::uint16_t jointGroupIndex) const override`
- L103 _public function_ `ConstArrayView<std::uint16_t> getJointGroupOutputIndices(std::uint16_t jointGroupIndex) const override`
- L107 _public function_ `ConstArrayView<float> getJointGroupValues(std::uint16_t jointGroupIndex) const override`

#### struct `block8::OptimizedStorage`  
`template<typename TValue> struct OptimizedStorage`  
_L113-126_
- L114 _public typedef_ `using StrategyPtr = std::unique_ptr<bpcm::JointGroupLinearCalculationStrategy, std::function<void(bpcm::JointGroupLinearCalculationStrategy*)>>;`
- L117 _public prototype_ `static bpcm::Evaluator create(StrategyPtr strategy, std::size_t rotationSelectorIndex, rl4::RotationType rotationType, MemoryResource* memRes);`
- L121 _public prototype_ `static bpcm::Evaluator create(StrategyPtr strategy, std::size_t rotationSelectorIndex, rl4::RotationType rotationType, std::uint16_t jointGroupIndex, MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace block8`
- L30 _namespace_ `namespace unoptimized` (scope `block8`)
- L32 _externvar_ `extern const tdm::rot_sign rotationSigns;` (scope `block8::unoptimized`)
- L33 _externvar_ `extern const std::uint16_t lodCount;` (scope `block8::unoptimized`)
- L34 _externvar_ `extern const std::uint16_t rawControlCount;` (scope `block8::unoptimized`)
- L35 _externvar_ `extern const Extent dimensions;` (scope `block8::unoptimized`)
- L36 _externvar_ `extern const Matrix<float> values;` (scope `block8::unoptimized`)
- L37 _externvar_ `extern const Matrix<std::uint16_t> inputIndices;` (scope `block8::unoptimized`)
- L38 _externvar_ `extern const Matrix<std::uint16_t> outputIndices;` (scope `block8::unoptimized`)
- L39 _externvar_ `extern const Matrix<std::uint16_t> lods;` (scope `block8::unoptimized`)
- L43 _namespace_ `namespace optimized` (scope `block8`)
- L45 _externvar_ `extern const Extent dimensions;` (scope `block8::optimized`)
- L46 _externvar_ `extern const AlignedMatrix<float> floatValues;` (scope `block8::optimized`)
- L47 _externvar_ `extern const AlignedMatrix<std::uint16_t> halfFloatValues;` (scope `block8::optimized`)
- L48 _externvar_ `extern const AlignedMatrix<std::uint16_t> inputIndices;` (scope `block8::optimized`)
- L49 _externvar_ `extern const Vector<Vector<AlignedVector<std::uint16_t>>> outputIndices;` (scope `block8::optimized`)
- L50 _externvar_ `extern const Vector<Vector<AlignedVector<std::uint16_t>>> outputRotationIndices;` (scope `block8::optimized`)
- L51 _externvar_ `extern const Vector<Vector<AlignedVector<std::uint16_t>>> outputRotationLODs;` (scope `block8::optimized`)
- L52 _externvar_ `extern const Vector<Vector<bpcm::JointGroup>> jointGroups;` (scope `block8::optimized`)
- L53 _externvar_ `extern const Matrix<LODRegion> lodRegions;` (scope `block8::optimized`)
- L57 _namespace_ `namespace input` (scope `block8`)
- L60 _externvar_ `extern const Vector<float> values;` (scope `block8::input`) — Calculation input values
- L64 _namespace_ `namespace output` (scope `block8`)
- L67 _externvar_ `extern const Vector<Matrix<float>> valuesPerLOD;` (scope `block8::output`) — Calculation output values

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/joints/bpcm/Helpers.h` (Private)


#### struct `OutputScope`  
`struct OutputScope`  
_L11-15_
- L12 _public member_ `std::uint16_t lod;`
- L13 _public member_ `std::size_t offset;`
- L14 _public member_ `std::size_t size;`

#### struct `StrategyTestParams`  
`struct StrategyTestParams`  
_L17-19_
- L18 _public member_ `std::uint16_t lod;`

#### struct `TStrategyTestParams`  
`template<std::uint16_t LOD> struct TStrategyTestParams`  
_L22-27_
- L24 _public function_ `static constexpr std::uint16_t lod()`

#### struct `TCalculationType`  
`template<rl4::CalculationType CalcType> struct TCalculationType`  
_L30-35_
- L32 _public function_ `static constexpr rl4::CalculationType get()`

#### struct `BPCMRotationOutputTypeSelector`  
`template<> struct BPCMRotationOutputTypeSelector<rl4::bpcm::NoopAdapter>`  
_L41-49_
- L42 _public function_ `static constexpr std::size_t value()`
- L46 _public function_ `static constexpr rl4::RotationType rotation()`

#### struct `BPCMRotationOutputTypeSelector`  
`template<typename T> struct BPCMRotationOutputTypeSelector<rl4::bpcm::EulerAnglesToQuaternions<T, tdm::rot_seq::zyx>>`  
_L52-60_
- L42 _public function_ `static constexpr std::size_t value()`
- L46 _public function_ `static constexpr rl4::RotationType rotation()`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/joints/quaternions/QuaternionFixtures.h` (Private)


#### struct `rltests::qs::optimized::Values`  
`template<> struct Values<float>`  
_L57-61_
- L58 _public function_ `static const AlignedMatrix<float>& get()`
- L65 _public function_ `static const AlignedMatrix<std::uint16_t>& get()`

#### struct `rltests::qs::optimized::Values`  
`template<> struct Values<std::uint16_t>`  
_L64-68_
- L58 _public function_ `static const AlignedMatrix<float>& get()`
- L65 _public function_ `static const AlignedMatrix<std::uint16_t>& get()`

#### class `rltests::qs::QuaternionReader`  
`class QuaternionReader : public dna::FakeReader`  
_L86-133_
- inherits: `dna::FakeReader`
- L88 _public prototype_ `~QuaternionReader();`
- L90 _public function_ `dna::RotationSign getRotationSign() const override`
- L94 _public function_ `dna::RotationSequence getRotationSequence() const override`
- L98 _public function_ `std::uint16_t getLODCount() const override`
- L102 _public function_ `std::uint16_t getJointRowCount() const override`
- L106 _public function_ `std::uint16_t getJointColumnCount() const override`
- L110 _public function_ `std::uint16_t getJointGroupCount() const override`
- L114 _public function_ `ConstArrayView<std::uint16_t> getJointGroupLODs(std::uint16_t jointGroupIndex) const override`
- L118 _public function_ `ConstArrayView<std::uint16_t> getJointGroupInputIndices(std::uint16_t jointGroupIndex) const override`
- L122 _public function_ `ConstArrayView<std::uint16_t> getJointGroupOutputIndices(std::uint16_t jointGroupIndex) const override`
- L126 _public function_ `ConstArrayView<float> getJointGroupValues(std::uint16_t jointGroupIndex) const override`
- L130 _public function_ `dna::RotationRepresentation getJointRotationRepresentation(std::uint16_t jointIndex) const override`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace rltests`
- L26 _namespace_ `namespace qs` (scope `rltests`)
- L30 _namespace_ `namespace unoptimized` (scope `rltests::qs`)
- L32 _externvar_ `extern const tdm::rot_sign rotationSigns;` (scope `rltests::qs::unoptimized`)
- L33 _externvar_ `extern const std::uint16_t lodCount;` (scope `rltests::qs::unoptimized`)
- L34 _externvar_ `extern const Extent dimensions;` (scope `rltests::qs::unoptimized`)
- L35 _externvar_ `extern const Matrix<float> values;` (scope `rltests::qs::unoptimized`)
- L36 _externvar_ `extern const Matrix<std::uint16_t> inputIndices;` (scope `rltests::qs::unoptimized`)
- L37 _externvar_ `extern const Matrix<std::uint16_t> outputIndices;` (scope `rltests::qs::unoptimized`)
- L38 _externvar_ `extern const Matrix<std::uint16_t> lods;` (scope `rltests::qs::unoptimized`)
- L39 _externvar_ `extern const Vector<Extent> subMatrices;` (scope `rltests::qs::unoptimized`)
- L40 _externvar_ `extern const Vector<dna::RotationRepresentation> jointRotationRepresentations;` (scope `rltests::qs::unoptimized`)
- L44 _namespace_ `namespace optimized` (scope `rltests::qs`)
- L46 _externvar_ `extern const AlignedMatrix<float> floatValues;` (scope `rltests::qs::optimized`)
- L47 _externvar_ `extern const AlignedMatrix<std::uint16_t> halfFloatValues;` (scope `rltests::qs::optimized`)
- L48 _externvar_ `extern const Vector<Extent> subMatrices;` (scope `rltests::qs::optimized`)
- L49 _externvar_ `extern const Matrix<std::uint16_t> inputIndices;` (scope `rltests::qs::optimized`)
- L50 _externvar_ `extern const Matrix<Vector<std::uint16_t>> outputIndices;` (scope `rltests::qs::optimized`)
- L51 _externvar_ `extern const Matrix<LODRegion> lodRegions;` (scope `rltests::qs::optimized`)
- L72 _namespace_ `namespace input` (scope `rltests::qs`)
- L75 _externvar_ `extern const Vector<float> values;` (scope `rltests::qs::input`) — Calculation input values
- L79 _namespace_ `namespace output` (scope `rltests::qs`)
- L82 _externvar_ `extern const Vector<Matrix<float>> valuesPerLODPerConfig;` (scope `rltests::qs::output`) — Calculation output values

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/joints/twistswing/TwistSwingFixtures.h` (Private)


#### class `rltests::twsw::TwistSwingReader`  
`class TwistSwingReader : public dna::FakeReader`  
_L70-113_
- inherits: `dna::FakeReader`
- L72 _public prototype_ `~TwistSwingReader();`
- L74 _public function_ `std::uint16_t getTwistCount() const override`
- L78 _public function_ `dna::TwistAxis getTwistSetupTwistAxis(std::uint16_t twistIndex) const override`
- L82 _public function_ `ConstArrayView<std::uint16_t> getTwistInputControlIndices(std::uint16_t twistIndex) const override`
- L86 _public function_ `ConstArrayView<std::uint16_t> getTwistOutputJointIndices(std::uint16_t twistIndex) const override`
- L90 _public function_ `ConstArrayView<float> getTwistBlendWeights(std::uint16_t twistIndex) const override`
- L94 _public function_ `std::uint16_t getSwingCount() const override`
- L98 _public function_ `dna::TwistAxis getSwingSetupTwistAxis(std::uint16_t swingIndex) const override`
- L102 _public function_ `ConstArrayView<std::uint16_t> getSwingInputControlIndices(std::uint16_t swingIndex) const override`
- L106 _public function_ `ConstArrayView<std::uint16_t> getSwingOutputJointIndices(std::uint16_t swingIndex) const override`
- L110 _public function_ `ConstArrayView<float> getSwingBlendWeights(std::uint16_t swingIndex) const override`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace rltests`
- L25 _namespace_ `namespace twsw` (scope `rltests`)
- L29 _namespace_ `namespace unoptimized` (scope `rltests::twsw`)
- L31 _externvar_ `extern const tdm::rot_sign rotationSigns;` (scope `rltests::twsw::unoptimized`)
- L32 _externvar_ `extern const std::uint16_t lodCount;` (scope `rltests::twsw::unoptimized`)
- L33 _externvar_ `extern const pma::Matrix<float> swingBlendWeights;` (scope `rltests::twsw::unoptimized`)
- L34 _externvar_ `extern const pma::Matrix<std::uint16_t> swingOutputJointIndices;` (scope `rltests::twsw::unoptimized`)
- L35 _externvar_ `extern const pma::Matrix<std::uint16_t> swingInputControlIndices;` (scope `rltests::twsw::unoptimized`)
- L36 _externvar_ `extern const pma::Vector<dna::TwistAxis> swingTwistAxes;` (scope `rltests::twsw::unoptimized`)
- L37 _externvar_ `extern const pma::Matrix<float> twistBlendWeights;` (scope `rltests::twsw::unoptimized`)
- L38 _externvar_ `extern const pma::Matrix<std::uint16_t> twistOutputJointIndices;` (scope `rltests::twsw::unoptimized`)
- L39 _externvar_ `extern const pma::Matrix<std::uint16_t> twistInputControlIndices;` (scope `rltests::twsw::unoptimized`)
- L40 _externvar_ `extern const pma::Vector<dna::TwistAxis> twistTwistAxes;` (scope `rltests::twsw::unoptimized`)
- L44 _namespace_ `namespace optimized` (scope `rltests::twsw`)
- L46 _externvar_ `extern const std::uint16_t setupCount;` (scope `rltests::twsw::optimized`)
- L47 _externvar_ `extern const pma::Matrix<float> swingBlendWeights;` (scope `rltests::twsw::optimized`)
- L48 _externvar_ `extern const pma::Vector<pma::Matrix<std::uint16_t>> swingOutputIndices;` (scope `rltests::twsw::optimized`)
- L49 _externvar_ `extern const pma::Matrix<std::uint16_t> swingInputIndices;` (scope `rltests::twsw::optimized`)
- L50 _externvar_ `extern const pma::Matrix<float> twistBlendWeights;` (scope `rltests::twsw::optimized`)
- L51 _externvar_ `extern const pma::Vector<pma::Matrix<std::uint16_t>> twistOutputIndices;` (scope `rltests::twsw::optimized`)
- L52 _externvar_ `extern const pma::Matrix<std::uint16_t> twistInputIndices;` (scope `rltests::twsw::optimized`)
- L56 _namespace_ `namespace input` (scope `rltests::twsw`)
- L59 _externvar_ `extern const Vector<float> values;` (scope `rltests::twsw::input`) — Calculation input values
- L63 _namespace_ `namespace output` (scope `rltests::twsw`)
- L66 _externvar_ `extern const Vector<Matrix<float>> valuesPerLODPerConfig;` (scope `rltests::twsw::output`) — Calculation output values

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/ml/cpu/FixturesBlock4.h` (Private)


#### struct `rltests::ml::block4::optimized::Values`  
`template<typename TValue> struct Values`  
_L65-68_
- L66 _public prototype_ `static const rl4::Vector<rl4::AlignedMatrix<TValue>>& weights();`
- L67 _public prototype_ `static const rl4::Vector<rl4::AlignedMatrix<TValue>>& biases();`

#### class `rltests::ml::block4::CanonicalReader`  
`class CanonicalReader : public dna::FakeReader`  
_L86-161_
- inherits: `dna::FakeReader`
- L88 _public prototype_ `~CanonicalReader();`
- L90 _public function_ `std::uint16_t getRawControlCount() const override`
- L94 _public function_ `std::uint16_t getLODCount() const override`
- L98 _public function_ `std::uint16_t getMLTypeCount() const override`
- L102 _public function_ `std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const override`
- L106 _public function_ `std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override`
- L110 _public function_ `dna::MachineLearnedBehaviorOperationType getMLOperationType(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L116 _public function_ `ConstArrayView<std::uint32_t> getMLOperationParameters(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L122 _public function_ `ConstArrayView<std::uint16_t> getMLOperationDependencyOperationSetIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L128 _public function_ `ConstArrayView<std::uint16_t> getMLOperationDependencyOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L134 _public function_ `ConstArrayView<std::uint16_t> getMLOperationIndicesForLOD(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t lod) const override`
- L140 _public function_ `std::uint16_t getNeuralNetworkLayerCount(std::uint16_t neuralNetIndex) const override`
- L144 _public function_ `dna::ActivationFunction getNeuralNetworkLayerActivationFunction(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L149 _public function_ `ConstArrayView<float> getNeuralNetworkLayerActivationFunctionParameters(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L154 _public function_ `ConstArrayView<float> getNeuralNetworkLayerBiases(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L158 _public function_ `ConstArrayView<float> getNeuralNetworkLayerWeights(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace rltests`
- L26 _namespace_ `namespace ml` (scope `rltests`)
- L28 _namespace_ `namespace block4` (scope `rltests::ml`)
- L32 _namespace_ `namespace unoptimized` (scope `rltests::ml::block4`)
- L34 _externvar_ `extern const std::uint16_t rawControlCount;` (scope `rltests::ml::block4::unoptimized`)
- L35 _externvar_ `extern const std::uint16_t mlControlCount;` (scope `rltests::ml::block4::unoptimized`)
- L36 _externvar_ `extern const std::uint16_t lodCount;` (scope `rltests::ml::block4::unoptimized`)
- L37 _externvar_ `extern const Vector<Matrix<dna::MachineLearnedBehaviorOperationType>> mlOperationTypes;` (scope `rltests::ml::block4::unoptimized`)
- L38 _externvar_ `extern const Matrix<Matrix<std::uint32_t>> mlOperationParameters;` (scope `rltests::ml::block4::unoptimized`)
- L39 _externvar_ `extern const Matrix<Matrix<std::uint16_t>> mlDependencyOperationSetIndices;` (scope `rltests::ml::block4::unoptimized`)
- L40 _externvar_ `extern const Matrix<Matrix<std::uint16_t>> mlDependencyOperationIndices;` (scope `rltests::ml::block4::unoptimized`)
- L41 _externvar_ `extern const Matrix<Matrix<std::uint16_t>> mlOperationIndicesPerLOD;` (scope `rltests::ml::block4::unoptimized`)
- L44 _externvar_ `extern const Matrix<dna::ActivationFunction> mlbNetActivationFunctions;` (scope `rltests::ml::block4::unoptimized`) — [neuralNetIndex][layerIndex]
- L46 _externvar_ `extern const Vector<Matrix<float>> mlbNetActivationFunctionParameters;` (scope `rltests::ml::block4::unoptimized`) — [neuralNetIndex][layerIndex][paramIndex]
- L48 _externvar_ `extern const Vector<Matrix<float>> mlbNetWeights;` (scope `rltests::ml::block4::unoptimized`) — [neuralNetIndex][layerIndex][weightIndex]
- L50 _externvar_ `extern const Vector<Matrix<float>> mlbNetBiases;` (scope `rltests::ml::block4::unoptimized`) — [neuralNetIndex][layerIndex][biasIndex]
- L54 _namespace_ `namespace optimized` (scope `rltests::ml::block4`)
- L56 _externvar_ `extern const Vector<Matrix<rl4::ml::cpu::OperationSetType>> mlOperationTypes;` (scope `rltests::ml::block4::optimized`)
- L57 _externvar_ `extern const Matrix<Matrix<std::uint32_t>> mlOperationParameters;` (scope `rltests::ml::block4::optimized`)
- L58 _externvar_ `extern const Vector<AlignedMatrix<float>> mlbNetWeightsFloat;` (scope `rltests::ml::block4::optimized`)
- L59 _externvar_ `extern const Vector<AlignedMatrix<std::uint16_t>> mlbNetWeightsHalfFloat;` (scope `rltests::ml::block4::optimized`)
- L60 _externvar_ `extern const Vector<AlignedMatrix<float>> mlbNetBiasesFloat;` (scope `rltests::ml::block4::optimized`)
- L61 _externvar_ `extern const Vector<AlignedMatrix<std::uint16_t>> mlbNetBiasesHalfFloat;` (scope `rltests::ml::block4::optimized`)
- L62 _externvar_ `extern const Matrix<LODSpec<std::uint16_t>> lods;` (scope `rltests::ml::block4::optimized`)
- L72 _namespace_ `namespace input` (scope `rltests::ml::block4`)
- L75 _externvar_ `extern const Vector<float> values;` (scope `rltests::ml::block4::input`) — Calculation input values
- L79 _namespace_ `namespace output` (scope `rltests::ml::block4`)
- L82 _externvar_ `extern const Matrix<float> valuesPerLOD;` (scope `rltests::ml::block4::output`) — Calculation output values

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/ml/cpu/FixturesMLBChained.h` (Private)


#### class `rltests::ml::chained::CanonicalReader`  
`class CanonicalReader : public dna::FakeReader`  
_L54-129_
- inherits: `dna::FakeReader`
- L56 _public prototype_ `~CanonicalReader();`
- L58 _public function_ `std::uint16_t getRawControlCount() const override`
- L62 _public function_ `std::uint16_t getLODCount() const override`
- L66 _public function_ `std::uint16_t getMLTypeCount() const override`
- L70 _public function_ `std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const override`
- L74 _public function_ `std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override`
- L78 _public function_ `dna::MachineLearnedBehaviorOperationType getMLOperationType(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L84 _public function_ `ConstArrayView<std::uint32_t> getMLOperationParameters(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L90 _public function_ `ConstArrayView<std::uint16_t> getMLOperationDependencyOperationSetIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L96 _public function_ `ConstArrayView<std::uint16_t> getMLOperationDependencyOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L102 _public function_ `ConstArrayView<std::uint16_t> getMLOperationIndicesForLOD(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t lod) const override`
- L108 _public function_ `std::uint16_t getNeuralNetworkLayerCount(std::uint16_t neuralNetIndex) const override`
- L112 _public function_ `dna::ActivationFunction getNeuralNetworkLayerActivationFunction(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L117 _public function_ `ConstArrayView<float> getNeuralNetworkLayerActivationFunctionParameters(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L122 _public function_ `ConstArrayView<float> getNeuralNetworkLayerBiases(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L126 _public function_ `ConstArrayView<float> getNeuralNetworkLayerWeights(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace rltests`
- L23 _namespace_ `namespace ml` (scope `rltests`)
- L27 _namespace_ `namespace chained` (scope `rltests::ml`)
- L31 _externvar_ `extern const std::uint16_t rawControlCount;` (scope `rltests::ml::chained`)
- L32 _externvar_ `extern const std::uint16_t mlControlCount;` (scope `rltests::ml::chained`)
- L33 _externvar_ `extern const std::uint16_t lodCount;` (scope `rltests::ml::chained`)
- L35 _externvar_ `extern const Vector<Matrix<dna::MachineLearnedBehaviorOperationType>> mlOperationTypes;` (scope `rltests::ml::chained`)
- L36 _externvar_ `extern const Matrix<Matrix<std::uint32_t>> mlOperationParameters;` (scope `rltests::ml::chained`)
- L37 _externvar_ `extern const Matrix<Matrix<std::uint16_t>> mlDependencyOperationSetIndices;` (scope `rltests::ml::chained`)
- L38 _externvar_ `extern const Matrix<Matrix<std::uint16_t>> mlDependencyOperationIndices;` (scope `rltests::ml::chained`)
- L39 _externvar_ `extern const Matrix<Matrix<std::uint16_t>> mlOperationIndicesPerLOD;` (scope `rltests::ml::chained`)
- L41 _externvar_ `extern const Matrix<dna::ActivationFunction> mlbNetActivationFunctions;` (scope `rltests::ml::chained`)
- L42 _externvar_ `extern const Vector<Matrix<float>> mlbNetActivationFunctionParameters;` (scope `rltests::ml::chained`)
- L43 _externvar_ `extern const Vector<Matrix<float>> mlbNetWeights;` (scope `rltests::ml::chained`)
- L44 _externvar_ `extern const Vector<Matrix<float>> mlbNetBiases;` (scope `rltests::ml::chained`)
- L46 _namespace_ `namespace input` (scope `rltests::ml::chained`)
- L47 _externvar_ `extern const Vector<float> values;` (scope `rltests::ml::chained::input`)
- L50 _namespace_ `namespace output` (scope `rltests::ml::chained`)
- L51 _externvar_ `extern const Matrix<float> valuesPerLOD;` (scope `rltests::ml::chained::output`)

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/rltests/rbf/cpu/RBFFixtures.h` (Private)


#### class `rltests::rbf::RBFReader`  
`class RBFReader : public dna::FakeReader`  
_L80-167_
- inherits: `dna::FakeReader`
- L82 _public prototype_ `~RBFReader();`
- L84 _public function_ `std::uint16_t getLODCount() const override`
- L88 _public function_ `std::uint16_t getRawControlCount() const override`
- L92 _public function_ `std::uint16_t getRBFPoseCount() const override`
- L96 _public function_ `float getRBFPoseScale(std::uint16_t poseIndex) const override`
- L100 _public function_ `std::uint16_t getRBFSolverCount() const override`
- L104 _public function_ `ConstArrayView<std::uint16_t> getRBFSolverIndicesForLOD(std::uint16_t lod) const override`
- L108 _public function_ `ConstArrayView<std::uint16_t> getRBFSolverRawControlIndices(std::uint16_t solverIndex) const override`
- L112 _public function_ `ConstArrayView<std::uint16_t> getRBFSolverPoseIndices(std::uint16_t solverIndex) const override`
- L116 _public function_ `ConstArrayView<float> getRBFSolverRawControlValues(std::uint16_t solverIndex) const override`
- L120 _public function_ `dna::RBFSolverType getRBFSolverType(std::uint16_t solverIndex) const override`
- L124 _public function_ `float getRBFSolverRadius(std::uint16_t solverIndex) const override`
- L128 _public function_ `dna::AutomaticRadius getRBFSolverAutomaticRadius(std::uint16_t solverIndex) const override`
- L132 _public function_ `float getRBFSolverWeightThreshold(std::uint16_t solverIndex) const override`
- L136 _public function_ `dna::RBFDistanceMethod getRBFSolverDistanceMethod(std::uint16_t solverIndex) const override`
- L140 _public function_ `dna::RBFNormalizeMethod getRBFSolverNormalizeMethod(std::uint16_t solverIndex) const override`
- L144 _public function_ `dna::RBFFunctionType getRBFSolverFunctionType(std::uint16_t solverIndex) const override`
- L148 _public function_ `dna::TwistAxis getRBFSolverTwistAxis(std::uint16_t solverIndex) const override`
- L152 _public function_ `std::uint16_t getRBFPoseControlCount() const override`
- L156 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseInputControlIndices(std::uint16_t poseIndex) const override`
- L160 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseOutputControlIndices(std::uint16_t poseIndex) const override`
- L164 _public function_ `ConstArrayView<float> getRBFPoseOutputControlWeights(std::uint16_t poseIndex) const override`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace rltests`
- L23 _namespace_ `namespace rbf` (scope `rltests`)
- L27 _namespace_ `namespace unoptimized` (scope `rltests::rbf`)
- L29 _externvar_ `extern const std::uint16_t rawControlCount;` (scope `rltests::rbf::unoptimized`)
- L30 _externvar_ `extern const std::uint16_t lodCount;` (scope `rltests::rbf::unoptimized`)
- L31 _externvar_ `extern const pma::Matrix<std::uint16_t> solverIndicesPerLOD;` (scope `rltests::rbf::unoptimized`)
- L32 _externvar_ `extern const pma::Matrix<std::uint16_t> solverRawControlIndices;` (scope `rltests::rbf::unoptimized`)
- L34 _externvar_ `extern const pma::Vector<float> poseScales;` (scope `rltests::rbf::unoptimized`)
- L35 _externvar_ `extern const std::uint16_t poseControlCount;` (scope `rltests::rbf::unoptimized`)
- L36 _externvar_ `extern const Matrix<std::uint16_t> poseInputControlIndices;` (scope `rltests::rbf::unoptimized`)
- L37 _externvar_ `extern const Matrix<std::uint16_t> poseOutputControlIndices;` (scope `rltests::rbf::unoptimized`)
- L38 _externvar_ `extern const Matrix<float> poseOutputControlWeights;` (scope `rltests::rbf::unoptimized`)
- L39 _externvar_ `extern const pma::Vector<dna::RBFSolverType> solverTypes;` (scope `rltests::rbf::unoptimized`)
- L40 _externvar_ `extern const pma::Vector<dna::RBFDistanceMethod> solverDistanceMethods;` (scope `rltests::rbf::unoptimized`)
- L41 _externvar_ `extern const pma::Vector<dna::RBFFunctionType> solverFunctionType;` (scope `rltests::rbf::unoptimized`)
- L42 _externvar_ `extern const pma::Vector<dna::RBFNormalizeMethod> solverNormalizeMethods;` (scope `rltests::rbf::unoptimized`)
- L43 _externvar_ `extern const pma::Vector<dna::TwistAxis> solverTwistAxis;` (scope `rltests::rbf::unoptimized`)
- L44 _externvar_ `extern const pma::Vector<dna::AutomaticRadius> solverAutomaticRadius;` (scope `rltests::rbf::unoptimized`)
- L45 _externvar_ `extern const pma::Vector<float> solverRadius;` (scope `rltests::rbf::unoptimized`)
- L46 _externvar_ `extern const pma::Vector<float> solverWeightThreshold;` (scope `rltests::rbf::unoptimized`)
- L47 _externvar_ `extern const pma::Matrix<std::uint16_t> solverPoseIndices;` (scope `rltests::rbf::unoptimized`)
- L48 _externvar_ `extern const pma::Matrix<float> solverRawControlValues;` (scope `rltests::rbf::unoptimized`)
- L52 _namespace_ `namespace optimized` (scope `rltests::rbf`)
- L54 _externvar_ `extern const LODSpec<std::uint16_t> lods;` (scope `rltests::rbf::optimized`)
- L55 _externvar_ `extern const Matrix<std::uint16_t> solverRawControlInputIndices;` (scope `rltests::rbf::optimized`)
- L56 _externvar_ `extern const Vector<std::uint16_t> inputCountPerSolver;` (scope `rltests::rbf::optimized`)
- L57 _externvar_ `extern const Vector<std::uint16_t> targetCountPerSolver;` (scope `rltests::rbf::optimized`)
- L59 _externvar_ `extern const Vector<Matrix<float>> targetValues;` (scope `rltests::rbf::optimized`)
- L60 _externvar_ `extern const Vector<Matrix<float>> coefficients;` (scope `rltests::rbf::optimized`)
- L61 _externvar_ `extern const pma::Vector<float> solverRadius;` (scope `rltests::rbf::optimized`)
- L62 _externvar_ `extern const pma::Matrix<float> solverPoseScales;` (scope `rltests::rbf::optimized`)
- L66 _namespace_ `namespace input` (scope `rltests::rbf`)
- L69 _externvar_ `extern const Vector<float> values;` (scope `rltests::rbf::input`) — Calculation input values
- L73 _namespace_ `namespace output` (scope `rltests::rbf`)
- L76 _externvar_ `extern const Matrix<float> valuesPerLOD;` (scope `rltests::rbf::output`) — Calculation output values

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/sctests/Defs.h` (Private)


#### Free symbols / members of external scopes

- L24 _macro_ `#define INSTANTIATE_TEST_SUITE_P INSTANTIATE_TEST_CASE_P`
- L28 _macro_ `#define TYPED_TEST_SUITE_P TYPED_TEST_CASE_P`
- L32 _macro_ `#define REGISTER_TYPED_TEST_SUITE_P REGISTER_TYPED_TEST_CASE_P`
- L36 _macro_ `#define INSTANTIATE_TYPED_TEST_SUITE_P INSTANTIATE_TYPED_TEST_CASE_P`
- L40 _macro_ `#define ASSERT_ELEMENTS_EQ(result, expected, count) \`
- L47 _macro_ `#define EXPECT_ELEMENTS_EQ(result, expected, count) \`
- L54 _macro_ `#define ASSERT_ELEMENTS_NEAR(result, expected, count, threshold) \`
- L61 _macro_ `#define EXPECT_ELEMENTS_NEAR(result, expected, count, threshold) \`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/tdmtests/Defs.h` (Private)


#### Free symbols / members of external scopes

- L24 _macro_ `#define INSTANTIATE_TEST_SUITE_P INSTANTIATE_TEST_CASE_P`
- L28 _macro_ `#define TYPED_TEST_SUITE_P TYPED_TEST_CASE_P`
- L32 _macro_ `#define REGISTER_TYPED_TEST_SUITE_P REGISTER_TYPED_TEST_CASE_P`
- L36 _macro_ `#define INSTANTIATE_TYPED_TEST_SUITE_P INSTANTIATE_TYPED_TEST_CASE_P`
- L40 _macro_ `#define ASSERT_ELEMENTS_EQ(result, expected, count) \`
- L47 _macro_ `#define EXPECT_ELEMENTS_EQ(result, expected, count) \`
- L54 _macro_ `#define ASSERT_ELEMENTS_NEAR(result, expected, count, threshold) \`
- L61 _macro_ `#define EXPECT_ELEMENTS_NEAR(result, expected, count, threshold) \`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/tdmtests/Helpers.h` (Private)


#### Free symbols / members of external scopes

- L5 _macro_ `#define ASSERT_VEC_NEAR(v1, v2, threshold) \`
- L11 _macro_ `#define ASSERT_MAT_NEAR(m1, m2, threshold) \`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/tersetests/Defs.h` (Private)


#### Free symbols / members of external scopes

- L24 _macro_ `#define INSTANTIATE_TEST_SUITE_P INSTANTIATE_TEST_CASE_P`
- L28 _macro_ `#define TYPED_TEST_SUITE_P TYPED_TEST_CASE_P`
- L32 _macro_ `#define REGISTER_TYPED_TEST_SUITE_P REGISTER_TYPED_TEST_CASE_P`
- L36 _macro_ `#define INSTANTIATE_TYPED_TEST_SUITE_P INSTANTIATE_TYPED_TEST_CASE_P`
- L40 _macro_ `#define ASSERT_ELEMENTS_EQ(result, expected, count) \`
- L47 _macro_ `#define EXPECT_ELEMENTS_EQ(result, expected, count) \`
- L54 _macro_ `#define ASSERT_ELEMENTS_NEAR(result, expected, count, threshold) \`
- L61 _macro_ `#define EXPECT_ELEMENTS_NEAR(result, expected, count, threshold) \`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/tersetests/FakeStream.h` (Private)


#### struct `tersetests::FakeStream`  
`struct FakeStream`  
_L21-77_
- L23 _public function_ `FakeStream() : position`
- L27 _public function_ `void open()`
- L31 _public function_ `void close()`
- L35 _public function_ `std::uint64_t tell()`
- L39 _public function_ `void seek(std::uint64_t position_)`
- L50 _public function_ `std::size_t read(char* buffer, std::size_t size)`
- L61 _public function_ `std::size_t write(const char* buffer, std::size_t size)`
- L71 _public function_ `std::uint64_t size()`
- L75 _public member_ `std::vector<char> data;`
- L76 _public member_ `std::size_t position;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace tersetests`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/tersetests/archives/binary/Common.h` (Private)


#### struct `ComplexType`  
`struct ComplexType`  
_L20-32_
- L21 _public member_ `std::int8_t a;`
- L22 _public member_ `std::uint8_t b;`
- L23 _public member_ `std::int16_t c;`
- L24 _public member_ `std::uint16_t d;`
- L25 _public member_ `std::int32_t e;`
- L26 _public member_ `std::uint32_t f;`
- L29 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `Child`  
`struct Child`  
_L34-47_
- L35 _public member_ `pma::Vector<std::uint16_t> integers;`
- L36 _public member_ `pma::Vector<float> floats;`
- L38 _public function_ `explicit Child(pma::MemoryResource* memRes) : integers`
- L44 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `Root`  
`struct Root`  
_L49-61_
- L50 _public member_ `std::string name;`
- L51 _public member_ `pma::Vector<Child> children;`
- L53 _public function_ `explicit Root(pma::MemoryResource* memRes) : children`
- L58 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `OffsetUtilizer`  
`struct OffsetUtilizer`  
_L63-88_
- L64 _public member_ `terse::ArchiveOffset<std::uint32_t> layerStart;`
- L65 _public member_ `terse::ArchiveOffset<std::uint32_t> first;`
- L66 _public member_ `terse::ArchiveOffset<std::uint32_t> second;`
- L68 _public member_ `std::int32_t a;`
- L69 _public member_ `char b;`
- L70 _public member_ `std::string c;`
- L72 _public member_ `terse::ArchiveOffset<std::uint32_t>::Proxy layerMarker;`
- L73 _public member_ `terse::ArchiveOffset<std::uint32_t>::Proxy firstMarker;`
- L74 _public member_ `std::int32_t firstInt;`
- L75 _public member_ `terse::ArchiveOffset<std::uint32_t>::Proxy secondMarker;`
- L76 _public member_ `std::int32_t secondInt;`
- L78 _public function_ `OffsetUtilizer() : layerMarker`
- L85 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `SerializableByFreeSerialize`  
`struct SerializableByFreeSerialize`  
_L90-93_
- L91 _public member_ `std::uint32_t a;`
- L92 _public member_ `std::uint16_t b;`

#### struct `SerializableByFreeLoadSave`  
`struct SerializableByFreeLoadSave`  
_L100-103_
- L101 _public member_ `std::uint32_t a;`
- L102 _public member_ `std::uint16_t b;`

#### struct `UpgradedSerializableType`  
`struct UpgradedSerializableType`  
_L115-138_
- L116 _public member_ `std::uint32_t a;`
- L117 _public member_ `std::uint16_t b;`
- L120 _public function_ `template<class Archive> void load(Archive& archive, terse::Version<1> )`
- L125 _public function_ `template<class Archive> void load(Archive& archive, terse::Version<2> )`
- L130 _public function_ `template<class Archive> void save(Archive& archive, terse::Version<1> )`
- L135 _public function_ `template<class Archive> void save(Archive& archive, terse::Version<2> )`

#### Free symbols / members of external scopes

- L96 _function_ `template<class TArchive> void serialize(TArchive& archive, SerializableByFreeSerialize& target)`
- L106 _function_ `template<class TArchive> void load(TArchive& archive, SerializableByFreeLoadSave& dest)`
- L111 _function_ `template<class TArchive> void save(TArchive& archive, const SerializableByFreeLoadSave& source)`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/tersetests/archives/json/Common.h` (Private)


#### struct `JSONStruct`  
`struct JSONStruct`  
_L18-41_
- L19 _public member_ `std::int8_t a;`
- L20 _public member_ `std::uint8_t b;`
- L21 _public member_ `std::int16_t c;`
- L22 _public member_ `std::uint16_t d;`
- L23 _public member_ `std::int32_t e;`
- L24 _public member_ `std::uint32_t f;`
- L27 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `NestedJSONStruct`  
`struct NestedJSONStruct`  
_L47-75_
- L48 _public member_ `JSONStruct a;`
- L49 _public member_ `JSONStruct b;`
- L50 _public member_ `std::vector<std::uint16_t> c;`
- L62 _public member_ `NestedVector d;`
- L65 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `NestedJSONStruct::NestedVector`  
`struct NestedVector`  
_L52-60_
- L53 _public member_ `std::vector<std::int32_t> cc;`
- L56 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `InnerOpaque`  
`struct InnerOpaque`  
_L85-96_
- L86 _public member_ `std::uint32_t a;`
- L87 _public member_ `std::uint32_t b;`
- L90 _public function_ `template<typename Archive> void serialize(Archive& archive)`

#### struct `OuterTransparent`  
`struct OuterTransparent`  
_L98-105_
- L99 _public member_ `InnerOpaque inner;`
- L102 _public function_ `template<typename Archive> void serialize(Archive& archive)`

#### Free symbols / members of external scopes

- L43 _function_ `inline bool operator==(const JSONStruct& lhs, const JSONStruct& rhs)`
- L77 _function_ `inline bool operator==(const NestedJSONStruct::NestedVector& lhs, const NestedJSONStruct::NestedVector& rhs)`
- L81 _function_ `inline bool operator==(const NestedJSONStruct& lhs, const NestedJSONStruct& rhs)`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/trimdtests/Defs.h` (Private)


#### Free symbols / members of external scopes

- L33 _macro_ `#define INSTANTIATE_TEST_SUITE_P INSTANTIATE_TEST_CASE_P`
- L37 _macro_ `#define TYPED_TEST_SUITE_P TYPED_TEST_CASE_P`
- L41 _macro_ `#define REGISTER_TYPED_TEST_SUITE_P REGISTER_TYPED_TEST_CASE_P`
- L45 _macro_ `#define INSTANTIATE_TYPED_TEST_SUITE_P INSTANTIATE_TYPED_TEST_CASE_P`
- L49 _macro_ `#define ASSERT_ELEMENTS_EQ(result, expected, count) \`
- L56 _macro_ `#define EXPECT_ELEMENTS_EQ(result, expected, count) \`
- L63 _macro_ `#define ASSERT_ELEMENTS_NEAR(result, expected, count, threshold) \`
- L70 _macro_ `#define EXPECT_ELEMENTS_NEAR(result, expected, count, threshold) \`
- L77 _function_ `template<typename TVec> inline bool near(const TVec& lhs, const TVec& rhs, float threshold)`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/triotests/Defs.h` (Private)


#### Free symbols / members of external scopes

- L24 _macro_ `#define INSTANTIATE_TEST_SUITE_P INSTANTIATE_TEST_CASE_P`
- L28 _macro_ `#define TYPED_TEST_SUITE_P TYPED_TEST_CASE_P`
- L32 _macro_ `#define REGISTER_TYPED_TEST_SUITE_P REGISTER_TYPED_TEST_CASE_P`
- L36 _macro_ `#define INSTANTIATE_TYPED_TEST_SUITE_P INSTANTIATE_TYPED_TEST_CASE_P`
- L40 _macro_ `#define ASSERT_ELEMENTS_EQ(result, expected, count) \`
- L47 _macro_ `#define EXPECT_ELEMENTS_EQ(result, expected, count) \`
- L54 _macro_ `#define ASSERT_ELEMENTS_NEAR(result, expected, count, threshold) \`
- L61 _macro_ `#define EXPECT_ELEMENTS_NEAR(result, expected, count, threshold) \`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/triotests/TestStreams.h` (Private)


#### struct `StreamFactory`  
`template<> struct StreamFactory<trio::FileStream>`  
_L32-38_
- L33 _public typedef_ `using PointerType = pma::ScopedPtr<trio::FileStream, pma::FactoryDestroy<trio::FileStream>>;`
- L35 _public function_ `static PointerType create(const char* path, trio::AccessMode accessMode)`
- L42 _public typedef_ `using PointerType = pma::ScopedPtr<trio::MemoryMappedFileStream, pma::FactoryDestroy<trio::MemoryMappedFileStream>>;`

#### struct `StreamFactory`  
`template<> struct StreamFactory<trio::MemoryMappedFileStream>`  
_L41-47_
- L33 _public typedef_ `using PointerType = pma::ScopedPtr<trio::FileStream, pma::FactoryDestroy<trio::FileStream>>;`
- L35 _public function_ `static PointerType create(const char* path, trio::AccessMode accessMode)`
- L42 _public typedef_ `using PointerType = pma::ScopedPtr<trio::MemoryMappedFileStream, pma::FactoryDestroy<trio::MemoryMappedFileStream>>;`

#### class `StreamTest`  
`template<typename T> class StreamTest : public ::testing::Test`  
_L50-87_
- inherits: `::testing::Test`
- L52 _protected typedef_ `using TStream = T;`
- L55 _protected function_ `static const char* GetTestFileName()`
- L59 _protected function_ `static void CreateTestFile(const char* data = nullptr, std::streamsize size = 0u)`
- L66 _protected function_ `static void CompareTestFile(const char* expected, std::streamsize size)`
- L74 _protected function_ `void SetUp()`
- L81 _protected function_ `void TearDown()`

#### Free symbols / members of external scopes

- L21 _macro_ `#define ASSERT_STATUS_OK() \`
- L26 _macro_ `#define ASSERT_STATUS_IS(candidate) ASSERT_EQ(trio::Status::get(), candidate);`
- L89 _typedef_ `using StreamTypes = ::testing::Types<trio::FileStream, trio::MemoryMappedFileStream>;`

### `Plugins/Animation/RigLogic/Source/RigLogicLibTest/Public/RigLogicLibTest.h` (Public)


#### class `FRigLogicLibTest`  
`class FRigLogicLibTest : public IModuleInterface`  
_L10-12_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigLogicLibTest, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigLogicLibTest, Log, All);`
