# Plugins / DNACalibLibTest

- module root: `Plugins/Animation/DNACalib/Source/DNACalibLibTest`
- headers: 7; symbols: 318
- symbol kinds: class=6, delegate=1, function=255, macro=8, member=42, namespace=1, prototype=5
- PublicDependencyModuleNames: Core, DNACalibLib, GoogleTest, RigLogicLib

### `Plugins/Animation/DNACalib/Source/DNACalibLibTest/Private/dnactests/Defs.h` (Private)


#### Free symbols / members of external scopes

- L28 _macro_ `#define INSTANTIATE_TEST_SUITE_P INSTANTIATE_TEST_CASE_P`
- L32 _macro_ `#define TYPED_TEST_SUITE_P TYPED_TEST_CASE_P`
- L36 _macro_ `#define REGISTER_TYPED_TEST_SUITE_P REGISTER_TYPED_TEST_CASE_P`
- L40 _macro_ `#define INSTANTIATE_TYPED_TEST_SUITE_P INSTANTIATE_TYPED_TEST_CASE_P`
- L44 _macro_ `#define ASSERT_ELEMENTS_EQ(result, expected, count) \`
- L51 _macro_ `#define EXPECT_ELEMENTS_EQ(result, expected, count) \`
- L58 _macro_ `#define ASSERT_ELEMENTS_NEAR(result, expected, count, threshold) \`
- L65 _macro_ `#define EXPECT_ELEMENTS_NEAR(result, expected, count, threshold) \`

### `Plugins/Animation/DNACalib/Source/DNACalibLibTest/Private/dnactests/commands/AnimatedMapDNAReader.h` (Private)


#### class `AnimatedMapDNAReader`  
`class AnimatedMapDNAReader : public dna::FakeDNACReader`  
_L14-107_
- inherits: `dna::FakeDNACReader`
- L16 _public function_ `explicit AnimatedMapDNAReader(dnac::MemoryResource* memRes = nullptr) : animatedMapNames`
- L46 _public prototype_ `~AnimatedMapDNAReader();`
- L48 _public function_ `std::uint16_t getLODCount() const override`
- L52 _public function_ `std::uint16_t getAnimatedMapCount() const override`
- L56 _public function_ `dnac::StringView getAnimatedMapName(std::uint16_t index) const override`
- L60 _public function_ `dnac::ConstArrayView<std::uint16_t> getAnimatedMapIndicesForLOD(std::uint16_t lod) const override`
- L67 _public function_ `dnac::ConstArrayView<std::uint16_t> getAnimatedMapLODs() const override`
- L71 _public function_ `dnac::ConstArrayView<std::uint16_t> getAnimatedMapInputIndices() const override`
- L75 _public function_ `dnac::ConstArrayView<std::uint16_t> getAnimatedMapOutputIndices() const override`
- L79 _public function_ `dnac::ConstArrayView<float> getAnimatedMapFromValues() const override`
- L83 _public function_ `dnac::ConstArrayView<float> getAnimatedMapToValues() const override`
- L87 _public function_ `dnac::ConstArrayView<float> getAnimatedMapSlopeValues() const override`
- L91 _public function_ `dnac::ConstArrayView<float> getAnimatedMapCutValues() const override`
- L96 _private member_ `std::uint16_t lodCount;`
- L97 _private member_ `dnac::Vector<dnac::String<char>> animatedMapNames;`
- L99 _private member_ `dnac::Matrix<std::uint16_t> animatedMapIndicesPerLOD;`
- L100 _private member_ `dnac::Vector<std::uint16_t> animatedMapLODs;`
- L101 _private member_ `dnac::Vector<std::uint16_t> animatedMapInputIndices;`
- L102 _private member_ `dnac::Vector<std::uint16_t> animatedMapOutputIndices;`
- L103 _private member_ `dnac::Vector<float> animatedMapFromValues;`
- L104 _private member_ `dnac::Vector<float> animatedMapToValues;`
- L105 _private member_ `dnac::Vector<float> animatedMapSlopeValues;`
- L106 _private member_ `dnac::Vector<float> animatedMapCutValues;`

### `Plugins/Animation/DNACalib/Source/DNACalibLibTest/Private/dnactests/commands/BlendShapeDNAReader.h` (Private)


#### class `BlendShapeDNAReader`  
`class BlendShapeDNAReader : public dna::FakeDNACReader`  
_L14-221_
- inherits: `dna::FakeDNACReader`
- L16 _public function_ `explicit BlendShapeDNAReader(dnac::MemoryResource* memRes = nullptr) : blendShapeNames`
- L86 _public prototype_ `~BlendShapeDNAReader();`
- L88 _public function_ `std::uint16_t getLODCount() const override`
- L92 _public function_ `std::uint16_t getMeshCount() const override`
- L96 _public function_ `dnac::StringView getMeshName(std::uint16_t index) const override`
- L100 _public function_ `std::uint16_t getBlendShapeChannelCount() const override`
- L104 _public function_ `dnac::StringView getBlendShapeChannelName(std::uint16_t index) const override`
- L108 _public function_ `dnac::ConstArrayView<std::uint16_t> getBlendShapeChannelIndicesForLOD(std::uint16_t lod) const override`
- L115 _public function_ `dnac::ConstArrayView<std::uint16_t> getBlendShapeChannelLODs() const override`
- L119 _public function_ `dnac::ConstArrayView<std::uint16_t> getBlendShapeChannelInputIndices() const override`
- L123 _public function_ `dnac::ConstArrayView<std::uint16_t> getBlendShapeChannelOutputIndices() const override`
- L127 _public function_ `std::uint16_t getBlendShapeTargetCount(std::uint16_t meshIndex) const override`
- L134 _public function_ `std::uint16_t getBlendShapeChannelIndex(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L143 _public function_ `std::uint32_t getBlendShapeTargetDeltaCount(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L152 _public function_ `dnac::Vector3 getBlendShapeTargetDelta(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, std::uint32_t deltaIndex) const override`
- L167 _public function_ `dnac::ConstArrayView<float> getBlendShapeTargetDeltaXs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L177 _public function_ `dnac::ConstArrayView<float> getBlendShapeTargetDeltaYs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L187 _public function_ `dnac::ConstArrayView<float> getBlendShapeTargetDeltaZs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L197 _public function_ `dnac::ConstArrayView<std::uint32_t> getBlendShapeTargetVertexIndices(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L208 _private member_ `std::uint16_t lodCount;`
- L209 _private member_ `dnac::Vector<dnac::String<char>> blendShapeNames;`
- L210 _private member_ `dnac::Vector<dnac::String<char>> meshNames;`
- L212 _private member_ `dnac::Matrix<std::uint16_t> bsChannelIndicesPerLOD;`
- L213 _private member_ `dnac::Vector<std::uint16_t> bsChannelLODs;`
- L214 _private member_ `dnac::Vector<std::uint16_t> bsChannelInputIndices;`
- L215 _private member_ `dnac::Vector<std::uint16_t> bsChannelOutputIndices;`
- L217 _private member_ `dnac::Matrix<std::uint16_t> bsChannelIndices;`
- L219 _private member_ `dnac::Matrix<dnac::RawVector3Vector> bsTargetDeltas;`
- L220 _private member_ `dnac::Matrix<dnac::Vector<std::uint32_t>> bsTargetVertexIndices;`

### `Plugins/Animation/DNACalib/Source/DNACalibLibTest/Private/dnactests/commands/FakeDNACReader.h` (Private)


#### class `dna::FakeDNACReader`  
`class FakeDNACReader : public Reader`  
_L22-777_
- inherits: `Reader`
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

### `Plugins/Animation/DNACalib/Source/DNACalibLibTest/Private/dnactests/commands/JointDNAReader.h` (Private)


#### class `JointDNAReader`  
`class JointDNAReader : public dna::FakeDNACReader`  
_L13-195_
- inherits: `dna::FakeDNACReader`
- L15 _public function_ `explicit JointDNAReader(dnac::MemoryResource* memRes = nullptr) : jointNames`
- L72 _public prototype_ `~JointDNAReader();`
- L74 _public function_ `std::uint16_t getLODCount() const override`
- L78 _public function_ `std::uint16_t getJointIndexListCount() const override`
- L82 _public function_ `dnac::ConstArrayView<std::uint16_t> getJointIndicesForLOD(std::uint16_t lod) const override`
- L86 _public function_ `std::uint16_t getJointParentIndex(std::uint16_t index) const override`
- L90 _public function_ `std::uint16_t getJointCount() const override`
- L94 _public function_ `dnac::StringView getJointName(std::uint16_t i) const override`
- L98 _public function_ `std::uint16_t getMeshCount() const override`
- L102 _public function_ `dnac::StringView getMeshName(std::uint16_t ) const override`
- L106 _public function_ `dnac::Vector3 getNeutralJointTranslation(std::uint16_t index) const override`
- L112 _public function_ `dnac::ConstArrayView<float> getNeutralJointTranslationXs() const override`
- L116 _public function_ `dnac::ConstArrayView<float> getNeutralJointTranslationYs() const override`
- L120 _public function_ `dnac::ConstArrayView<float> getNeutralJointTranslationZs() const override`
- L124 _public function_ `dnac::Vector3 getNeutralJointRotation(std::uint16_t index) const override`
- L128 _public function_ `dnac::ConstArrayView<float> getNeutralJointRotationXs() const override`
- L132 _public function_ `dnac::ConstArrayView<float> getNeutralJointRotationYs() const override`
- L136 _public function_ `dnac::ConstArrayView<float> getNeutralJointRotationZs() const override`
- L140 _public function_ `std::uint16_t getJointGroupCount() const override`
- L144 _public function_ `dnac::ConstArrayView<std::uint16_t> getJointGroupJointIndices(std::uint16_t ) const override`
- L148 _public function_ `dnac::ConstArrayView<std::uint16_t> getJointGroupLODs(std::uint16_t ) const override`
- L152 _public function_ `dnac::ConstArrayView<std::uint16_t> getJointGroupInputIndices(std::uint16_t ) const override`
- L156 _public function_ `dnac::ConstArrayView<std::uint16_t> getJointGroupOutputIndices(std::uint16_t ) const override`
- L160 _public function_ `dnac::ConstArrayView<float> getJointGroupValues(std::uint16_t ) const override`
- L164 _public function_ `std::uint32_t getSkinWeightsCount(std::uint16_t ) const override`
- L168 _public function_ `dnac::ConstArrayView<float> getSkinWeightsValues(std::uint16_t , std::uint32_t vertexIndex) const override`
- L172 _public function_ `dnac::ConstArrayView<std::uint16_t> getSkinWeightsJointIndices(std::uint16_t , std::uint32_t vertexIndex) const override`
- L178 _private member_ `std::uint16_t lodCount;`
- L179 _private member_ `dnac::Vector<dnac::String<char>> jointNames;`
- L180 _private member_ `dnac::Matrix<std::uint16_t> jointIndicesPerLOD;`
- L181 _private member_ `dnac::Vector<std::uint16_t> jointHierarchy;`
- L183 _private member_ `dnac::RawVector3Vector neutralJointTranslations;`
- L184 _private member_ `dnac::RawVector3Vector neutralJointRotations;`
- L186 _private member_ `std::uint16_t jointGroupCount;`
- L187 _private member_ `dnac::Vector<std::uint16_t> jointGroupJointIndices;`
- L188 _private member_ `dnac::Vector<std::uint16_t> jointGroupLODs;`
- L189 _private member_ `dnac::Vector<std::uint16_t> jointGroupInputIndices;`
- L190 _private member_ `dnac::Vector<std::uint16_t> jointGroupOutputIndices;`
- L191 _private member_ `dnac::Vector<float> jointGroupValues;`
- L193 _private member_ `dnac::Matrix<float> skinWeightsValues;`
- L194 _private member_ `dnac::Matrix<std::uint16_t> skinWeightsJointIndices;`

### `Plugins/Animation/DNACalib/Source/DNACalibLibTest/Private/dnactests/commands/MeshDNAReader.h` (Private)


#### class `MeshDNAReader`  
`class MeshDNAReader : public dna::FakeDNACReader`  
_L16-153_
- inherits: `dna::FakeDNACReader`
- L18 _public function_ `explicit MeshDNAReader(dnac::MemoryResource* memRes = nullptr) : blendShapeNames`
- L76 _public prototype_ `~MeshDNAReader();`
- L78 _public function_ `std::uint16_t getLODCount() const override`
- L82 _public function_ `std::uint16_t getMeshCount() const override`
- L86 _public function_ `dnac::StringView getMeshName(std::uint16_t index) const override`
- L90 _public function_ `std::uint16_t getBlendShapeChannelCount() const override`
- L94 _public function_ `dnac::StringView getBlendShapeChannelName(std::uint16_t index) const override`
- L98 _public function_ `dnac::ConstArrayView<std::uint16_t> getBlendShapeChannelIndicesForLOD(std::uint16_t lod) const override`
- L102 _public function_ `std::uint16_t getMeshBlendShapeChannelMappingCount() const override`
- L106 _public function_ `dna::MeshBlendShapeChannelMapping getMeshBlendShapeChannelMapping(std::uint16_t index) const override`
- L110 _public function_ `dnac::ConstArrayView<std::uint16_t> getMeshBlendShapeChannelMappingIndicesForLOD(std::uint16_t lod) const override`
- L114 _public function_ `std::uint16_t getMeshIndexListCount() const override`
- L118 _public function_ `dnac::ConstArrayView<std::uint16_t> getMeshIndicesForLOD(std::uint16_t lod) const override`
- L122 _public function_ `std::uint32_t getVertexPositionCount(std::uint16_t meshIndex) const override`
- L126 _public function_ `dna::Position getVertexPosition(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L132 _public function_ `dnac::ConstArrayView<float> getVertexPositionXs(std::uint16_t meshIndex) const override`
- L136 _public function_ `dnac::ConstArrayView<float> getVertexPositionYs(std::uint16_t meshIndex) const override`
- L140 _public function_ `dnac::ConstArrayView<float> getVertexPositionZs(std::uint16_t meshIndex) const override`
- L145 _private member_ `std::uint16_t lodCount;`
- L146 _private member_ `dnac::Vector<dnac::String<char>> blendShapeNames;`
- L147 _private member_ `dnac::Matrix<std::uint16_t> blendShapeChannelIndicesPerLOD;`
- L148 _private member_ `dnac::Vector<dnac::String<char>> meshNames;`
- L149 _private member_ `dnac::Vector<dna::MeshBlendShapeChannelMapping> meshBlendShapeChannelMappings;`
- L150 _private member_ `dnac::Matrix<std::uint16_t> meshBlendShapeChannelMappingIndicesPerLOD;`
- L151 _private member_ `dnac::Matrix<std::uint16_t> meshIndicesPerLOD;`
- L152 _private member_ `dnac::Matrix<dnac::Vector<float>> vertexPositions;`

### `Plugins/Animation/DNACalib/Source/DNACalibLibTest/Public/DNACalibLibTest.h` (Public)


#### class `FDNACalibLibTest`  
`class FDNACalibLibTest : public IModuleInterface`  
_L10-12_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDNACalibLibTest, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDNACalibLibTest, Log, All);`
