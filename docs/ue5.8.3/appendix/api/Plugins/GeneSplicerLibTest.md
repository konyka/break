# Plugins / GeneSplicerLibTest

- module root: `Plugins/Animation/GeneSplicer/Source/GeneSplicerLibTest`
- headers: 13; symbols: 436
- symbol kinds: class=13, delegate=1, enum=1, enumerator=2, externvar=34, function=313, macro=15, member=35, namespace=8, prototype=1, struct=1, typedef=6, variable=6
- PublicDependencyModuleNames: Core, GeneSplicerLib, GoogleTest, RigLogicLib

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLibTest/Private/gstests/Assertions.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace gs4`
- L23 _function_ `inline void assertVec3Near(Vec3 result, Vec3 expected, float threshold)` (scope `gs4`)
- L29 _function_ `inline void assertNeutralMeshes(Reader* output, Reader* expected, float threshold)` (scope `gs4`)
- L41 _function_ `inline void assertNeutralMeshes(ConstArrayView<RawVector3Vector> neutralMeshes, Reader* expected)` (scope `gs4`)
- L60 _function_ `inline void assertNeutralMeshPoolData(ConstArrayView<XYZTiledMatrix<16u>> actualData, const Vector<Matrix<XYZBlock<16u>>>& expectedData)` (scope `gs4`)
- L77 _function_ `inline void assertBlendShapeTargets(Reader* output, Reader* expected, float threshold)` (scope `gs4`)
- L98 _function_ `inline void assertBlendShapeTargets(const VariableWidthMatrix<RawBlendShapeTarget>& blendShapeTargets, Reader* expected)` (scope `gs4`)
- L123 _function_ `inline void assertBlendShapePoolVertexIndices(ConstArrayView<VariableWidthMatrix<std::uint32_t>> indices, const Vector<Matrix<std::uint32_t>>& expectedIndices)` (scope `gs4`)
- L139 _function_ `template<std::uint16_t BlockSize> inline void assertBlendShapePoolDeltas(const VariableWidthMatrix<AlignedVariableWidthMatrix<XYZBlock<BlockSize>>>& deltas, const Matrix<Matrix<XYZBlock<BlockSize>>>& expectedDeltas)` (scope `gs4`)
- L164 _function_ `template<std::uint16_t BlockSize> inline void assertBlendShapePoolArchDeltas(const Vector<AlignedVariableWidthMatrix<XYZBlock<BlockSize>>>& deltas, const Vector<Matrix<XYZBlock<BlockSize>>>& expectedDeltas)` (scope `gs4`)
- L187 _function_ `inline void assertBlendShapePoolDNAIndices(const VariableWidthMatrix<VariableWidthMatrix<std::uint16_t>>& dnaIndices, const Matrix<Matrix<std::uint16_t>>& expectedDNAIndices)` (scope `gs4`)
- L212 _function_ `inline void assertNeutralJointTranslations(Reader* output, Reader* expected, float threshold)` (scope `gs4`)
- L221 _function_ `inline void assertNeutralJointTranslation(const RawVector3Vector& neutralJoints, Reader* expected)` (scope `gs4`)
- L232 _function_ `inline void assertNeutralJoints(const RawVector3Vector& actual, Vector<Vector3> expected, float threshold)` (scope `gs4`)
- L241 _function_ `inline void assertNeutralJointPool(const XYZTiledMatrix<16u>& actual, const Matrix<XYZBlock<16u>>& expected)` (scope `gs4`)
- L258 _function_ `inline void assertNeutralJointRotations(Reader* output, Reader* expected, float threshold)` (scope `gs4`)
- L267 _function_ `inline void assertNeutralJointRotation(const RawVector3Vector& neutralJoints, Reader* expected)` (scope `gs4`)
- L278 _function_ `inline void assertJointBehavior(Reader* output, Reader* expected, float threshold)` (scope `gs4`)
- L295 _function_ `inline void assertJointBehavior(ConstArrayView<RawJointGroup> jointGroups, Reader* expected)` (scope `gs4`)
- L317 _function_ `inline void assertJointBehaviorPoolIndices(const VariableWidthMatrix<std::uint16_t>& indices, const Matrix<std::uint16_t>& expectedIndices)` (scope `gs4`)
- L326 _function_ `inline void assertJointBehaviorValues(ConstArrayView<SingleJointBehavior> actualJoints, const Vector<canonical::JBJoint>& expectedJoints)` (scope `gs4`)
- L348 _function_ `inline void assertSkinWeights(Reader* output, Reader* expected, float threshold)` (scope `gs4`)
- L364 _function_ `inline void assertSkinWeights(ConstArrayView<Vector<RawVertexSkinWeights>> skinWeights, Reader* expected)` (scope `gs4`)
- L386 _function_ `inline void assertSkinWeightPoolJointIndices(ConstArrayView<VariableWidthMatrix<std::uint16_t>> indices, const Vector<Matrix<std::uint16_t>>& expectedIndices)` (scope `gs4`)
- L402 _function_ `inline void assertSkinWeightPoolValues(const VariableWidthMatrix<TiledMatrix2D<16u>>& weights, const Matrix<Matrix<VBlock<16u>>>& expectedWeights)` (scope `gs4`)
- L430 _function_ `inline void assertRawGenes(const RawGenes& rawGenes, Reader* expected)` (scope `gs4`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLibTest/Private/gstests/Defs.h` (Private)


#### Free symbols / members of external scopes

- L26 _macro_ `#define INSTANTIATE_TEST_SUITE_P INSTANTIATE_TEST_CASE_P`
- L30 _macro_ `#define TYPED_TEST_SUITE_P TYPED_TEST_CASE_P`
- L34 _macro_ `#define REGISTER_TYPED_TEST_SUITE_P REGISTER_TYPED_TEST_CASE_P`
- L38 _macro_ `#define INSTANTIATE_TYPED_TEST_SUITE_P INSTANTIATE_TYPED_TEST_CASE_P`
- L42 _macro_ `#define ASSERT_ELEMENTS_EQ(result, expected, count) \`
- L49 _macro_ `#define ASSERT_ELEMENTS_AND_SIZE_EQ(result, expected) \`
- L57 _macro_ `#define EXPECT_ELEMENTS_EQ(result, expected, count) \`
- L64 _macro_ `#define ASSERT_ELEMENTS_NEAR(result, expected, count, threshold) \`
- L71 _macro_ `#define EXPECT_ELEMENTS_NEAR(result, expected, count, threshold) \`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLibTest/Private/gstests/FixtureReader.h` (Private)


#### class `gs4::FixtureReader`  
`class FixtureReader : public dna::MockedReader`  
_L22-293_
- inherits: `dna::MockedReader`
- L30 _public function_ `static FixtureReader* create(std::uint16_t dnaIndex)`
- L34 _public function_ `static void destroy(FixtureReader* instance)`
- L38 _public function_ `explicit FixtureReader(std::uint16_t dnaIndex_) : dnaIndex`
- L42 _public function_ `StringView getName() const override`
- L46 _public function_ `std::uint16_t getPSDCount() const override`
- L50 _public function_ `std::uint16_t getMeshCount() const override`
- L54 _public function_ `std::uint16_t getJointCount() const override`
- L58 _public function_ `StringView getMeshName(std::uint16_t meshIndex) const override`
- L62 _public function_ `StringView getJointName(std::uint16_t jointIndex) const override`
- L66 _public function_ `StringView getBlendShapeChannelName(std::uint16_t channelIndex) const override`
- L70 _public function_ `Vector3 getNeutralJointTranslation(std::uint16_t index) const override`
- L76 _public function_ `ConstArrayView<float> getNeutralJointTranslationXs() const override`
- L80 _public function_ `ConstArrayView<float> getNeutralJointTranslationYs() const override`
- L84 _public function_ `ConstArrayView<float> getNeutralJointTranslationZs() const override`
- L88 _public function_ `Vector3 getNeutralJointRotation(std::uint16_t index) const override`
- L94 _public function_ `ConstArrayView<float> getNeutralJointRotationXs() const override`
- L98 _public function_ `ConstArrayView<float> getNeutralJointRotationYs() const override`
- L102 _public function_ `ConstArrayView<float> getNeutralJointRotationZs() const override`
- L106 _public function_ `std::uint32_t getVertexPositionCount(std::uint16_t meshIndex) const override`
- L110 _public function_ `dna::Position getVertexPosition(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L116 _public function_ `ConstArrayView<float> getVertexPositionXs(std::uint16_t meshIndex) const override`
- L120 _public function_ `ConstArrayView<float> getVertexPositionYs(std::uint16_t meshIndex) const override`
- L124 _public function_ `ConstArrayView<float> getVertexPositionZs(std::uint16_t meshIndex) const override`
- L128 _public function_ `std::uint32_t getVertexNormalCount(std::uint16_t meshIndex) const override`
- L132 _public function_ `dna::Normal getVertexNormal(std::uint16_t meshIndex, std::uint32_t normalIndex) const override`
- L138 _public function_ `ConstArrayView<float> getVertexNormalXs(std::uint16_t meshIndex) const override`
- L142 _public function_ `ConstArrayView<float> getVertexNormalYs(std::uint16_t meshIndex) const override`
- L146 _public function_ `ConstArrayView<float> getVertexNormalZs(std::uint16_t meshIndex) const override`
- L150 _public function_ `ConstArrayView<float> getSkinWeightsValues(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L154 _public function_ `ConstArrayView<std::uint16_t> getSkinWeightsJointIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L158 _public function_ `std::uint32_t getSkinWeightsCount(std::uint16_t meshIndex) const override`
- L162 _public function_ `std::uint16_t getMaximumInfluencePerVertex(std::uint16_t meshIndex) const override`
- L166 _public function_ `std::uint16_t getJointGroupCount() const override`
- L170 _public function_ `ConstArrayView<std::uint16_t> getJointGroupLODs(std::uint16_t jointGroupIndex) const override`
- L174 _public function_ `ConstArrayView<std::uint16_t> getJointGroupInputIndices(std::uint16_t jointGroupIndex) const override`
- L178 _public function_ `ConstArrayView<std::uint16_t> getJointGroupOutputIndices(std::uint16_t jointGroupIndex) const override`
- L182 _public function_ `ConstArrayView<float> getJointGroupValues(std::uint16_t jointGroupIndex) const override`
- L186 _public function_ `ConstArrayView<std::uint16_t> getJointGroupJointIndices(std::uint16_t jointGroupIndex) const override`
- L190 _public function_ `std::uint16_t getBlendShapeChannelCount() const override`
- L194 _public function_ `std::uint16_t getBlendShapeTargetCount(std::uint16_t meshIndex) const override`
- L198 _public function_ `std::uint32_t getBlendShapeTargetDeltaCount(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L202 _public function_ `dna::Delta getBlendShapeTargetDelta(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, std::uint32_t deltaIndex) const override`
- L209 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaXs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L214 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaYs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L219 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaZs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L224 _public function_ `ConstArrayView<std::uint32_t> getBlendShapeTargetVertexIndices(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L229 _public function_ `std::uint16_t getMLTypeCount() const override`
- L233 _public function_ `std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const override`
- L237 _public function_ `std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override`
- L241 _public function_ `dna::MachineLearnedBehaviorOperationType getMLOperationType(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L247 _public function_ `ConstArrayView<std::uint32_t> getMLOperationParameters(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L253 _public function_ `ConstArrayView<std::uint16_t> getMLOperationDependencyOperationSetIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L259 _public function_ `ConstArrayView<std::uint16_t> getMLOperationDependencyOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L265 _public function_ `std::uint16_t getMLOperationIndexListCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override`
- L269 _public function_ `ConstArrayView<std::uint16_t> getMLOperationIndicesForLOD(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t lod) const override`
- L275 _public function_ `ConstArrayView<std::uint16_t> getMLJointsInputIndices() const override`
- L279 _public function_ `ConstArrayView<std::uint16_t> getMLJointsOutputIndices() const override`
- L283 _public function_ `ConstArrayView<std::uint16_t> getMLJointsParameterKeys() const override`
- L287 _public function_ `ConstArrayView<std::uint16_t> getMLJointsParameterValues() const override`
- L292 _private member_ `std::uint16_t dnaIndex;`

#### enum `gs4::FixtureReader::(anonymous)`  
`enum`  
_L24-27_

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace gs4`
- L25 _enumerator_ `archetype = 2u` (scope `gs4::FixtureReader::__anon00a871e30103`)
- L26 _enumerator_ `expected = 3u` (scope `gs4::FixtureReader::__anon00a871e30103`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLibTest/Private/gstests/Fixtures.h` (Private)


#### struct `gs4::canonical::JBJoint`  
`struct JBJoint`  
_L59-64_
- L60 _public member_ `Vector<Matrix<VBlock<16u>>> blockValues;`
- L61 _public member_ `std::uint16_t jointGroup;`
- L62 _public member_ `std::uint16_t outIndexTargetPos[6];`
- L63 _public member_ `std::uint8_t vBlockRemainder;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace gs4`
- L16 _namespace_ `namespace canonical` (scope `gs4`)
- L18 _variable_ `static constexpr std::uint16_t dnaCount = 3;` (scope `gs4::canonical`)
- L19 _variable_ `static constexpr std::uint16_t meshCount = 2;` (scope `gs4::canonical`)
- L20 _variable_ `static constexpr std::uint16_t regionCount = 2;` (scope `gs4::canonical`)
- L21 _variable_ `static constexpr std::uint16_t jointCount = 3;` (scope `gs4::canonical`)
- L22 _variable_ `static constexpr std::uint16_t psdCount = 2;` (scope `gs4::canonical`)
- L23 _variable_ `static constexpr std::uint16_t blendShapeCount = 2;` (scope `gs4::canonical`)
- L25 _externvar_ `extern const Matrix<Matrix<float>> neutralMeshes;` (scope `gs4::canonical`)
- L26 _externvar_ `extern const Matrix<Matrix<float>> skinWeightsValues;` (scope `gs4::canonical`)
- L27 _externvar_ `extern const Matrix<Matrix<std::uint16_t>> skinWeightsJointIndices;` (scope `gs4::canonical`)
- L28 _externvar_ `extern const Vector<Matrix<float>> neutralJointTranslations;` (scope `gs4::canonical`)
- L29 _externvar_ `extern const Vector<Matrix<float>> neutralJointRotations;` (scope `gs4::canonical`)
- L30 _externvar_ `extern const Vector<Matrix<std::uint16_t>> jointGroupLODs;` (scope `gs4::canonical`)
- L31 _externvar_ `extern const Vector<Matrix<std::uint16_t>> jointGroupJointIndices;` (scope `gs4::canonical`)
- L32 _externvar_ `extern const Vector<Matrix<std::uint16_t>> jointGroupOutputIndices;` (scope `gs4::canonical`)
- L33 _externvar_ `extern const Matrix<std::uint16_t> jointGroupInputIndices;` (scope `gs4::canonical`)
- L34 _externvar_ `extern const Vector<Matrix<float>> jointGroupValues;` (scope `gs4::canonical`)
- L35 _externvar_ `extern const Vector<Matrix<std::uint32_t>> blendShapeTargetVertexIndices;` (scope `gs4::canonical`)
- L36 _externvar_ `extern const Matrix<Matrix<float>> blendShapeTargetDeltas;` (scope `gs4::canonical`)
- L38 _externvar_ `extern const Vector<Matrix<XYZBlock<16u>>> expectedNeutralMeshPoolValues;` (scope `gs4::canonical`)
- L39 _externvar_ `extern const Matrix<XYZBlock<16u>> expectedNeutralJointPoolTranslations;` (scope `gs4::canonical`)
- L40 _externvar_ `extern const Matrix<XYZBlock<16u>> expectedNeutralJointPoolRotations;` (scope `gs4::canonical`)
- L41 _externvar_ `extern const Vector<Vector<std::size_t>> expectedBlendShapePoolBucketOffsets;` (scope `gs4::canonical`)
- L42 _externvar_ `extern const Vector<std::uint32_t> expectedBlendShapePoolBucketVertexIndices;` (scope `gs4::canonical`)
- L43 _externvar_ `extern const Vector<std::size_t> expectedBlendShapePoolBucketDNABlockOffsets;` (scope `gs4::canonical`)
- L44 _externvar_ `extern const Vector<XYZBlock<4u>> expectedBlendShapePoolArchDeltas;` (scope `gs4::canonical`)
- L45 _externvar_ `extern const Vector<XYZBlock<4u>> expectedBlendShapePoolDNADeltas;` (scope `gs4::canonical`)
- L46 _externvar_ `extern const Vector<std::uint16_t> expectedBlendShapePoolDNAIndices;` (scope `gs4::canonical`)
- L48 _externvar_ `extern const Vector<Matrix<std::uint32_t>> expectedBlendShapePoolVertexIndices;` (scope `gs4::canonical`)
- L49 _externvar_ `extern const Vector<Matrix<std::uint16_t>> expectedSWPoolJointIndices;` (scope `gs4::canonical`)
- L50 _externvar_ `extern const Matrix<Matrix<VBlock<16u>>> expectedSWPoolWeights;` (scope `gs4::canonical`)
- L51 _externvar_ `extern const Vector<std::uint16_t> expectedSWPoolMaxInfluences;` (scope `gs4::canonical`)
- L52 _externvar_ `extern const Matrix<std::uint16_t> expectedJBPoolInputIndices;` (scope `gs4::canonical`)
- L53 _externvar_ `extern const Matrix<std::uint16_t> expectedJBPoolOutputIndices;` (scope `gs4::canonical`)
- L54 _externvar_ `extern const Matrix<std::uint16_t> expectedJBPoolLODs;` (scope `gs4::canonical`)
- L56 _externvar_ `extern const Vector<Vector3> expectedRawGenesNeutralJointTranslations;` (scope `gs4::canonical`)
- L57 _externvar_ `extern const Vector<Vector3> expectedRawGenesNeutralJointRotations;` (scope `gs4::canonical`)
- L65 _externvar_ `extern const Vector<JBJoint> expectedJBPoolBlock;` (scope `gs4::canonical`)
- L66 _externvar_ `extern const Vector<Vector<Vector<float>>> accustomedArchetypeBlendShapeDeltas;` (scope `gs4::canonical`)
- L67 _externvar_ `extern const Vector<AlignedVector<float>> accustomedArchetypeJointGroupValues;` (scope `gs4::canonical`)
- L68 _externvar_ `extern const Vector<float> spliceWeights;` (scope `gs4::canonical`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLibTest/Private/gstests/MockedReader.h` (Private)


#### class `dna::MockedReader`  
`class MockedReader : public Reader`  
_L20-772_
- inherits: `Reader`
- L23 _public function_ `std::uint16_t getFileFormatGeneration() const override` — HeaderReader methods
- L27 _public function_ `std::uint16_t getFileFormatVersion() const override`
- L32 _public function_ `StringView getName() const override` — DescriptorReader methods
- L36 _public function_ `Archetype getArchetype() const override`
- L40 _public function_ `Gender getGender() const override`
- L44 _public function_ `std::uint16_t getAge() const override`
- L48 _public function_ `std::uint32_t getMetaDataCount() const override`
- L52 _public function_ `StringView getMetaDataKey(std::uint32_t index) const override`
- L56 _public function_ `StringView getMetaDataValue(const char* key) const override`
- L60 _public function_ `TranslationUnit getTranslationUnit() const override`
- L64 _public function_ `RotationUnit getRotationUnit() const override`
- L68 _public function_ `CoordinateSystem getCoordinateSystem() const override`
- L72 _public function_ `RotationSequence getRotationSequence() const override`
- L76 _public function_ `RotationSign getRotationSign() const override`
- L80 _public function_ `FaceWindingOrder getFaceWindingOrder() const override`
- L84 _public function_ `std::uint16_t getLODCount() const override`
- L88 _public function_ `std::uint16_t getDBMaxLOD() const override`
- L92 _public function_ `StringView getDBComplexity() const override`
- L96 _public function_ `StringView getDBName() const override`
- L101 _public function_ `std::uint16_t getGUIControlCount() const override` — DefinitionReader methods
- L105 _public function_ `StringView getGUIControlName(std::uint16_t index) const override`
- L109 _public function_ `std::uint16_t getRawControlCount() const override`
- L113 _public function_ `StringView getRawControlName(std::uint16_t index) const override`
- L117 _public function_ `std::uint16_t getJointCount() const override`
- L121 _public function_ `StringView getJointName(std::uint16_t index) const override`
- L125 _public function_ `ArrayView<const std::uint16_t> getJointIndicesForLOD(std::uint16_t lod) const override`
- L129 _public function_ `std::uint16_t getJointParentIndex(std::uint16_t index) const override`
- L136 _public function_ `std::uint16_t getBlendShapeChannelCount() const override`
- L140 _public function_ `StringView getBlendShapeChannelName(std::uint16_t index) const override`
- L144 _public function_ `ArrayView<const std::uint16_t> getBlendShapeChannelIndicesForLOD(std::uint16_t lod) const override`
- L148 _public function_ `std::uint16_t getAnimatedMapCount() const override`
- L152 _public function_ `ArrayView<const std::uint16_t> getAnimatedMapIndicesForLOD(std::uint16_t lod) const override`
- L156 _public function_ `StringView getAnimatedMapName(std::uint16_t index) const override`
- L160 _public function_ `std::uint16_t getMeshCount() const override`
- L164 _public function_ `StringView getMeshName(std::uint16_t index) const override`
- L168 _public function_ `std::uint16_t getMeshBlendShapeChannelMappingCount() const override`
- L172 _public function_ `MeshBlendShapeChannelMapping getMeshBlendShapeChannelMapping(std::uint16_t index) const override`
- L176 _public function_ `ArrayView<const std::uint16_t> getMeshBlendShapeChannelMappingIndicesForLOD(std::uint16_t lod) const override`
- L180 _public function_ `ArrayView<const std::uint16_t> getMeshIndicesForLOD(std::uint16_t lod) const override`
- L184 _public function_ `Vector3 getNeutralJointTranslation(std::uint16_t index) const override`
- L188 _public function_ `ConstArrayView<float> getNeutralJointTranslationXs() const override`
- L192 _public function_ `ConstArrayView<float> getNeutralJointTranslationYs() const override`
- L196 _public function_ `ConstArrayView<float> getNeutralJointTranslationZs() const override`
- L200 _public function_ `Vector3 getNeutralJointRotation(std::uint16_t index) const override`
- L204 _public function_ `ConstArrayView<float> getNeutralJointRotationXs() const override`
- L208 _public function_ `ConstArrayView<float> getNeutralJointRotationYs() const override`
- L212 _public function_ `ConstArrayView<float> getNeutralJointRotationZs() const override`
- L217 _public function_ `ArrayView<const std::uint16_t> getGUIToRawInputIndices() const override` — BehaviorReader methods
- L221 _public function_ `ArrayView<const std::uint16_t> getGUIToRawOutputIndices() const override`
- L225 _public function_ `ConstArrayView<float> getGUIToRawFromValues() const override`
- L229 _public function_ `ConstArrayView<float> getGUIToRawToValues() const override`
- L233 _public function_ `ConstArrayView<float> getGUIToRawSlopeValues() const override`
- L237 _public function_ `ConstArrayView<float> getGUIToRawCutValues() const override`
- L241 _public function_ `std::uint16_t getPSDCount() const override`
- L245 _public function_ `ArrayView<const std::uint16_t> getPSDRowIndices() const override`
- L249 _public function_ `ArrayView<const std::uint16_t> getPSDColumnIndices() const override`
- L253 _public function_ `ConstArrayView<float> getPSDValues() const override`
- L257 _public function_ `ArrayView<const std::uint16_t> getJointVariableAttributeIndices(std::uint16_t lod) const override`
- L261 _public function_ `std::uint16_t getJointRowCount() const override`
- L265 _public function_ `std::uint16_t getJointColumnCount() const override`
- L269 _public function_ `std::uint16_t getJointGroupCount() const override`
- L273 _public function_ `ArrayView<const std::uint16_t> getJointGroupLODs(std::uint16_t jointGroupIndex) const override`
- L277 _public function_ `ArrayView<const std::uint16_t> getJointGroupInputIndices(std::uint16_t jointGroupIndex) const override`
- L281 _public function_ `ArrayView<const std::uint16_t> getJointGroupOutputIndices(std::uint16_t jointGroupIndex) const override`
- L285 _public function_ `ConstArrayView<float> getJointGroupValues(std::uint16_t jointGroupIndex) const override`
- L289 _public function_ `ArrayView<const std::uint16_t> getJointGroupJointIndices(std::uint16_t jointGroupIndex) const override`
- L293 _public function_ `ArrayView<const std::uint16_t> getBlendShapeChannelLODs() const override`
- L297 _public function_ `ArrayView<const std::uint16_t> getBlendShapeChannelInputIndices() const override`
- L301 _public function_ `ArrayView<const std::uint16_t> getBlendShapeChannelOutputIndices() const override`
- L305 _public function_ `ArrayView<const std::uint16_t> getAnimatedMapLODs() const override`
- L309 _public function_ `ArrayView<const std::uint16_t> getAnimatedMapInputIndices() const override`
- L313 _public function_ `ArrayView<const std::uint16_t> getAnimatedMapOutputIndices() const override`
- L317 _public function_ `ConstArrayView<float> getAnimatedMapFromValues() const override`
- L321 _public function_ `ConstArrayView<float> getAnimatedMapToValues() const override`
- L325 _public function_ `ConstArrayView<float> getAnimatedMapSlopeValues() const override`
- L329 _public function_ `ConstArrayView<float> getAnimatedMapCutValues() const override`
- L334 _public function_ `std::uint32_t getVertexPositionCount(std::uint16_t meshIndex) const override` — GeometryReader methods
- L338 _public function_ `Position getVertexPosition(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L342 _public function_ `ConstArrayView<float> getVertexPositionXs(std::uint16_t meshIndex) const override`
- L346 _public function_ `ConstArrayView<float> getVertexPositionYs(std::uint16_t meshIndex) const override`
- L350 _public function_ `ConstArrayView<float> getVertexPositionZs(std::uint16_t meshIndex) const override`
- L354 _public function_ `std::uint32_t getVertexTextureCoordinateCount(std::uint16_t meshIndex) const override`
- L358 _public function_ `TextureCoordinate getVertexTextureCoordinate(std::uint16_t meshIndex, std::uint32_t textureCoordinateIndex) const override`
- L362 _public function_ `ConstArrayView<float> getVertexTextureCoordinateUs(std::uint16_t meshIndex) const override`
- L366 _public function_ `ConstArrayView<float> getVertexTextureCoordinateVs(std::uint16_t meshIndex) const override`
- L370 _public function_ `std::uint32_t getVertexNormalCount(std::uint16_t meshIndex) const override`
- L374 _public function_ `Normal getVertexNormal(std::uint16_t meshIndex, std::uint32_t normalIndex) const override`
- L378 _public function_ `ConstArrayView<float> getVertexNormalXs(std::uint16_t meshIndex) const override`
- L382 _public function_ `ConstArrayView<float> getVertexNormalYs(std::uint16_t meshIndex) const override`
- L386 _public function_ `ConstArrayView<float> getVertexNormalZs(std::uint16_t meshIndex) const override`
- L390 _public function_ `std::uint32_t getFaceCount(std::uint16_t meshIndex) const override`
- L394 _public function_ `ArrayView<const std::uint32_t> getFaceVertexLayoutIndices(std::uint16_t meshIndex, std::uint32_t faceIndex) const override`
- L398 _public function_ `std::uint32_t getVertexLayoutCount(std::uint16_t meshIndex) const override`
- L402 _public function_ `VertexLayout getVertexLayout(std::uint16_t meshIndex, std::uint32_t layoutIndex) const override`
- L406 _public function_ `ArrayView<const std::uint32_t> getVertexLayoutPositionIndices(std::uint16_t meshIndex) const override`
- L410 _public function_ `ArrayView<const std::uint32_t> getVertexLayoutTextureCoordinateIndices(std::uint16_t meshIndex) const override`
- L414 _public function_ `ArrayView<const std::uint32_t> getVertexLayoutNormalIndices(std::uint16_t meshIndex) const override`
- L418 _public function_ `std::uint16_t getMaximumInfluencePerVertex(std::uint16_t meshIndex) const override`
- L422 _public function_ `ConstArrayView<float> getSkinWeightsValues(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L426 _public function_ `ArrayView<const std::uint16_t> getSkinWeightsJointIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L430 _public function_ `std::uint16_t getBlendShapeTargetCount(std::uint16_t meshIndex) const override`
- L434 _public function_ `std::uint16_t getBlendShapeChannelIndex(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L438 _public function_ `std::uint32_t getBlendShapeTargetDeltaCount(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L442 _public function_ `Delta getBlendShapeTargetDelta(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, std::uint32_t deltaIndex) const override`
- L448 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaXs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L453 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaYs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L458 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaZs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L463 _public function_ `ArrayView<const std::uint32_t> getBlendShapeTargetVertexIndices(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L468 _public function_ `std::uint16_t getJointIndexListCount() const override`
- L472 _public function_ `std::uint16_t getBlendShapeChannelIndexListCount() const override`
- L476 _public function_ `std::uint16_t getAnimatedMapIndexListCount() const override`
- L480 _public function_ `std::uint16_t getMeshIndexListCount() const override`
- L485 _public function_ `std::uint16_t getMLControlCount() const override` — MachineLearnedBehaviorReader methods
- L489 _public function_ `StringView getMLControlName(std::uint16_t index) const override`
- L493 _public function_ `std::uint16_t getNeuralNetworkCount() const override`
- L497 _public function_ `std::uint16_t getNeuralNetworkIndexListCount() const override`
- L501 _public function_ `ConstArrayView<std::uint16_t> getNeuralNetworkIndicesForLOD(std::uint16_t lod) const override`
- L505 _public function_ `std::uint16_t getMeshRegionCount(std::uint16_t meshIndex) const override`
- L509 _public function_ `StringView getMeshRegionName(std::uint16_t meshIndex, std::uint16_t regionIndex) const override`
- L513 _public function_ `ConstArrayView<std::uint16_t> getNeuralNetworkIndicesForMeshRegion(std::uint16_t meshIndex, std::uint16_t regionIndex) const override`
- L518 _public function_ `ConstArrayView<std::uint16_t> getNeuralNetworkInputIndices(std::uint16_t neuralNetIndex) const override`
- L522 _public function_ `ConstArrayView<std::uint16_t> getNeuralNetworkOutputIndices(std::uint16_t neuralNetIndex) const override`
- L526 _public function_ `std::uint16_t getNeuralNetworkLayerCount(std::uint16_t neuralNetIndex) const override`
- L530 _public function_ `ActivationFunction getNeuralNetworkLayerActivationFunction(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L535 _public function_ `ConstArrayView<float> getNeuralNetworkLayerActivationFunctionParameters(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L540 _public function_ `ConstArrayView<float> getNeuralNetworkLayerBiases(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L544 _public function_ `ConstArrayView<float> getNeuralNetworkLayerWeights(std::uint16_t neuralNetIndex, std::uint16_t layerIndex) const override`
- L548 _public function_ `std::uint16_t getRBFPoseCount() const override`
- L552 _public function_ `StringView getRBFPoseName(std::uint16_t poseIndex) const override`
- L556 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseJointOutputIndices(std::uint16_t poseIndex) const override`
- L560 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseBlendShapeChannelOutputIndices(std::uint16_t poseIndex) const override`
- L564 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseAnimatedMapOutputIndices(std::uint16_t poseIndex) const override`
- L568 _public function_ `ConstArrayView<float> getRBFPoseJointOutputValues(std::uint16_t poseIndex) const override`
- L572 _public function_ `float getRBFPoseScale(std::uint16_t poseIndex) const override`
- L576 _public function_ `std::uint16_t getRBFPoseControlCount() const override`
- L580 _public function_ `StringView getRBFPoseControlName(std::uint16_t poseControlIndex) const override`
- L584 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseInputControlIndices(std::uint16_t poseIndex) const override`
- L588 _public function_ `ConstArrayView<std::uint16_t> getRBFPoseOutputControlIndices(std::uint16_t poseIndex) const override`
- L592 _public function_ `ConstArrayView<float> getRBFPoseOutputControlWeights(std::uint16_t poseIndex) const override`
- L596 _public function_ `std::uint16_t getRBFSolverCount() const override`
- L600 _public function_ `std::uint16_t getRBFSolverIndexListCount() const override`
- L604 _public function_ `ConstArrayView<std::uint16_t> getRBFSolverIndicesForLOD(std::uint16_t lod) const override`
- L608 _public function_ `StringView getRBFSolverName(std::uint16_t solverIndex) const override`
- L612 _public function_ `ConstArrayView<std::uint16_t> getRBFSolverRawControlIndices(std::uint16_t solverIndex) const override`
- L616 _public function_ `ConstArrayView<std::uint16_t> getRBFSolverPoseIndices(std::uint16_t solverIndex) const override`
- L620 _public function_ `ConstArrayView<float> getRBFSolverRawControlValues(std::uint16_t solverIndex) const override`
- L624 _public function_ `RBFSolverType getRBFSolverType(std::uint16_t solverIndex) const override`
- L628 _public function_ `float getRBFSolverRadius(std::uint16_t solverIndex) const override`
- L632 _public function_ `AutomaticRadius getRBFSolverAutomaticRadius(std::uint16_t solverIndex) const override`
- L636 _public function_ `float getRBFSolverWeightThreshold(std::uint16_t solverIndex) const override`
- L640 _public function_ `RBFDistanceMethod getRBFSolverDistanceMethod(std::uint16_t solverIndex) const override`
- L644 _public function_ `RBFNormalizeMethod getRBFSolverNormalizeMethod(std::uint16_t solverIndex) const override`
- L648 _public function_ `RBFFunctionType getRBFSolverFunctionType(std::uint16_t solverIndex) const override`
- L652 _public function_ `TwistAxis getRBFSolverTwistAxis(std::uint16_t solverIndex) const override`
- L656 _public function_ `TranslationRepresentation getJointTranslationRepresentation(std::uint16_t jointIndex) const override`
- L660 _public function_ `RotationRepresentation getJointRotationRepresentation(std::uint16_t jointIndex) const override`
- L664 _public function_ `ScaleRepresentation getJointScaleRepresentation(std::uint16_t jointIndex) const override`
- L668 _public function_ `std::uint16_t getTwistCount() const override`
- L672 _public function_ `TwistAxis getTwistSetupTwistAxis(std::uint16_t twistIndex) const override`
- L676 _public function_ `ConstArrayView<std::uint16_t> getTwistInputControlIndices(std::uint16_t twistIndex) const override`
- L680 _public function_ `ConstArrayView<std::uint16_t> getTwistOutputJointIndices(std::uint16_t twistIndex) const override`
- L684 _public function_ `ConstArrayView<float> getTwistBlendWeights(std::uint16_t twistIndex) const override`
- L688 _public function_ `std::uint16_t getSwingCount() const override`
- L692 _public function_ `TwistAxis getSwingSetupTwistAxis(std::uint16_t swingIndex) const override`
- L696 _public function_ `ConstArrayView<std::uint16_t> getSwingInputControlIndices(std::uint16_t swingIndex) const override`
- L700 _public function_ `ConstArrayView<std::uint16_t> getSwingOutputJointIndices(std::uint16_t swingIndex) const override`
- L704 _public function_ `ConstArrayView<float> getSwingBlendWeights(std::uint16_t swingIndex) const override`
- L708 _public function_ `std::uint16_t getMLTypeCount() const override`
- L712 _public function_ `std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const override`
- L716 _public function_ `std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override`
- L720 _public function_ `MachineLearnedBehaviorOperationType getMLOperationType(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L726 _public function_ `ConstArrayView<std::uint32_t> getMLOperationParameters(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L732 _public function_ `ConstArrayView<std::uint16_t> getMLOperationDependencyOperationSetIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L738 _public function_ `ConstArrayView<std::uint16_t> getMLOperationDependencyOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override`
- L744 _public function_ `std::uint16_t getMLOperationIndexListCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override`
- L748 _public function_ `ConstArrayView<std::uint16_t> getMLOperationIndicesForLOD(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t lod) const override`
- L754 _public function_ `ConstArrayView<std::uint16_t> getMLJointsInputIndices() const override`
- L758 _public function_ `ConstArrayView<std::uint16_t> getMLJointsOutputIndices() const override`
- L762 _public function_ `ConstArrayView<std::uint16_t> getMLJointsParameterKeys() const override`
- L766 _public function_ `ConstArrayView<std::uint16_t> getMLJointsParameterValues() const override`
- L770 _public function_ `void unload(DataLayer dataLayer) override`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace dna`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLibTest/Private/gstests/splicedata/MockedArchetypeReader.h` (Private)


#### class `MockedArchetypeReader`  
`class MockedArchetypeReader : public dna::MockedReader`  
_L20-112_
- inherits: `dna::MockedReader`
- L22 _public function_ `MockedArchetypeReader()`
- L34 _public function_ `std::uint16_t getJointCount() const override`
- L38 _public function_ `std::uint16_t getJointGroupCount() const override`
- L42 _public function_ `gs4::ArrayView<const std::uint16_t> getJointGroupOutputIndices(std::uint16_t jointGroupIndex) const override`
- L46 _public function_ `gs4::ArrayView<const std::uint16_t> getJointGroupJointIndices(std::uint16_t jointGroupIndex) const override`
- L50 _public function_ `std::uint16_t getMeshCount() const override`
- L54 _public function_ `std::uint32_t getVertexPositionCount(std::uint16_t meshIndex) const override`
- L59 _public function_ `gs4::ArrayView<const std::uint16_t> getSkinWeightsJointIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L65 _public function_ `gs4::ConstArrayView<float> getSkinWeightsValues(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L70 _public function_ `std::uint32_t getSkinWeightsCount(std::uint16_t meshIndex) const override`
- L75 _public function_ `std::uint16_t getDBMaxLOD() const override`
- L79 _public function_ `gs4::StringView getDBComplexity() const override`
- L83 _public function_ `gs4::StringView getDBName() const override`
- L87 _public function_ `void setDBMaxLod(std::uint16_t lodCount)`
- L91 _public function_ `void setDBComplexity(gs4::String<char> complexity)`
- L95 _public function_ `void setDBname(gs4::String<char> name)`
- L99 _public function_ `void setJointCount(std::uint16_t jointCount_)`
- L104 _private member_ `gs4::Matrix<std::uint16_t> outputIndicesPerJointGroup;`
- L105 _private member_ `gs4::Matrix<std::uint16_t> jointIndicesPerJointGroup;`
- L106 _private member_ `gs4::Matrix<std::uint16_t> jointIndicesPerVertex;`
- L107 _private member_ `gs4::Matrix<float> jointWeightsPerVertex;`
- L108 _private member_ `gs4::String<char> dbComplexity;`
- L109 _private member_ `gs4::String<char> dbName;`
- L110 _private member_ `std::uint16_t jointCount;`
- L111 _private member_ `std::uint16_t dbMaxLodCount;`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLibTest/Private/gstests/splicedata/MockedRegionAffiliationReader.h` (Private)


#### class `MockedRegionAffiliationReader`  
`class MockedRegionAffiliationReader : public gs4::RegionAffiliationReader`  
_L18-95_
- inherits: `gs4::RegionAffiliationReader`
- L20 _private member_ `static const std::uint16_t vertexCount = 21;`
- L23 _public function_ `MockedRegionAffiliationReader()`
- L42 _public function_ `std::uint16_t getMeshCount() const override`
- L46 _public function_ `std::uint32_t getVertexCount(std::uint16_t meshIndex) const override`
- L53 _public function_ `gs4::ConstArrayView<std::uint16_t> getVertexRegionIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L61 _public function_ `gs4::ConstArrayView<float> getVertexRegionAffiliation(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override`
- L70 _public function_ `std::uint16_t getJointCount() const override`
- L74 _public function_ `gs4::ConstArrayView<std::uint16_t> getJointRegionIndices(std::uint16_t jointIndex) const override`
- L78 _public function_ `gs4::ConstArrayView<float> getJointRegionAffiliation(std::uint16_t jointIndex) const override`
- L82 _public function_ `std::uint16_t getRegionCount() const override`
- L86 _public function_ `av::StringView getRegionName(std::uint16_t regionIndex) const override`
- L91 _protected member_ `gs4::Matrix<std::uint16_t> vertexRegionIndices;`
- L92 _protected member_ `gs4::Matrix<float> vertexRegionAffiliations;`
- L93 _protected member_ `gs4::Matrix<std::uint16_t> jointRegionIndices;`
- L94 _protected member_ `gs4::Matrix<float> jointRegionAffiliations;`

#### class `MockedRegionAffiliationReaderMeshCountOther`  
`class MockedRegionAffiliationReaderMeshCountOther : public MockedRegionAffiliationReader`  
_L97-101_
- inherits: `MockedRegionAffiliationReader`
- L98 _private function_ `std::uint16_t getMeshCount() const override`

#### class `MockedRegionAffiliationReaderJointCountOther`  
`template<std::uint16_t JointCount> class MockedRegionAffiliationReaderJointCountOther : public MockedRegionAffiliationReader`  
_L104-117_
- inherits: `MockedRegionAffiliationReader`
- L106 _public function_ `std::uint16_t getJointCount() const override`
- L110 _public function_ `gs4::ConstArrayView<std::uint16_t> getJointRegionIndices(std::uint16_t jointIndex) const override`
- L114 _public function_ `gs4::ConstArrayView<float> getJointRegionAffiliation(std::uint16_t jointIndex) const override`

#### class `MockedRegionAffiliationReaderVertexCountOther`  
`class MockedRegionAffiliationReaderVertexCountOther : public MockedRegionAffiliationReader`  
_L119-123_
- inherits: `MockedRegionAffiliationReader`
- L120 _private function_ `std::uint32_t getVertexCount(std::uint16_t meshIndex) const override`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLibTest/Private/gstests/splicedata/genepool/TestPool.h` (Private)


#### class `gs4::TestPool`  
`class TestPool : public ::testing::Test`  
_L20-45_
- inherits: `::testing::Test`
- L22 _protected typedef_ `using ReaderVector = Vector<const dna::Reader*>;`
- L25 _protected function_ `void SetUp() override`
- L37 _protected member_ `pma::AlignedMemoryResource memRes;`
- L38 _protected member_ `pma::ScopedPtr<FixtureReader> arch;`
- L39 _protected member_ `pma::ScopedPtr<FixtureReader> dna0;`
- L40 _protected member_ `pma::ScopedPtr<FixtureReader> dna1;`
- L41 _protected member_ `pma::ScopedPtr<FixtureReader> expectedReader;`
- L43 _protected member_ `ReaderVector readers;`
- L44 _protected member_ `ReaderVector readerOthers;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLibTest/Private/gstests/splicedata/rawgenes/AccustomedArchetypeReader.h` (Private)


#### class `gs4::AccustomedArchetypeReader`  
`class AccustomedArchetypeReader : public FixtureReader`  
_L22-63_
- inherits: `FixtureReader`
- L24 _public function_ `explicit AccustomedArchetypeReader() : FixtureReader`
- L28 _public function_ `ConstArrayView<std::uint32_t> getBlendShapeTargetVertexIndices(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override`
- L33 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaXs(std::uint16_t,` — There is only one mesh
- L38 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaYs(std::uint16_t,` — There is only one mesh
- L43 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaZs(std::uint16_t,` — There is only one mesh
- L48 _public function_ `ConstArrayView<float> getJointGroupValues(std::uint16_t jointGroupIndex) const override`
- L52 _public function_ `ConstArrayView<std::uint16_t> getJointGroupLODs(std::uint16_t jointGroupIndex) const override`
- L56 _public function_ `ConstArrayView<std::uint16_t> getJointGroupInputIndices(std::uint16_t jointGroupIndex) const override`
- L60 _public function_ `ConstArrayView<std::uint16_t> getJointGroupOutputIndices(std::uint16_t jointGroupIndex) const override`

#### class `gs4::RawGeneArchetypeDNAReader`  
`class RawGeneArchetypeDNAReader : public FixtureReader`  
_L65-86_
- inherits: `FixtureReader`
- L68 _public function_ `explicit RawGeneArchetypeDNAReader() : FixtureReader`
- L72 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaXs(std::uint16_t,` — There is only one mesh
- L77 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaYs(std::uint16_t,` — There is only one mesh
- L82 _public function_ `ConstArrayView<float> getBlendShapeTargetDeltaZs(std::uint16_t,` — There is only one mesh

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLibTest/Private/gstests/splicedata/rawgenes/TestRawGenes.h` (Private)


#### class `gs4::TestRawGenes`  
`class TestRawGenes : public ::testing::Test`  
_L26-48_
- inherits: `::testing::Test`
- L28 _protected typedef_ `using ReaderVector = Vector<const dna::Reader*>;`
- L31 _protected function_ `void SetUp() override`
- L41 _protected member_ `AlignedMemoryResource memRes;`
- L42 _protected member_ `ScopedPtr<FixtureReader> expectedDNA;`
- L43 _protected member_ `ScopedPtr<FixtureReader> arch;`
- L44 _protected member_ `ScopedPtr<FixtureReader> dna0;`
- L45 _protected member_ `ScopedPtr<FixtureReader> dna1;`
- L46 _protected member_ `ScopedPtr<AccustomedArchetypeReader> accustomedArch;`
- L47 _protected member_ `ScopedPtr<RawGeneArchetypeDNAReader> rawGenesArch;`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLibTest/Private/raftests/Defs.h` (Private)


#### Free symbols / members of external scopes

- L24 _macro_ `#define INSTANTIATE_TEST_SUITE_P INSTANTIATE_TEST_CASE_P`
- L28 _macro_ `#define TYPED_TEST_SUITE_P TYPED_TEST_CASE_P`
- L32 _macro_ `#define REGISTER_TYPED_TEST_SUITE_P REGISTER_TYPED_TEST_CASE_P`
- L36 _macro_ `#define INSTANTIATE_TYPED_TEST_SUITE_P INSTANTIATE_TYPED_TEST_CASE_P`
- L39 _macro_ `#define ASSERT_ELEMENTS_EQ(result, expected, count) \`
- L44 _macro_ `#define ASSERT_ELEMENTS_NEAR(lhs, rhs, threshold) \`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLibTest/Private/raftests/TestRegionAffiliationReaderWriter.h` (Private)


#### class `RegionAffiliationReaderWriterTest`  
`template<typename TReaderWriterPair> class RegionAffiliationReaderWriterTest : public ::testing::Test`  
_L19-37_
- inherits: `::testing::Test`
- L21 _protected typedef_ `using TStreamReaderImpl = typename std::tuple_element<0, TReaderWriterPair>::type;`
- L22 _protected typedef_ `using TStreamWriterImpl = typename std::tuple_element<1, TReaderWriterPair>::type;`
- L23 _protected typedef_ `using TStreamReader = typename TStreamReaderImpl::ReaderInterface;`
- L24 _protected typedef_ `using TStreamWriter = typename TStreamWriterImpl::WriterInterface;`
- L27 _protected function_ `void SetUp() override`
- L34 _protected member_ `pma::ScopedPtr<trio::MemoryStream> stream;`
- L35 _protected member_ `pma::ScopedPtr<TStreamReader> reader;`
- L36 _protected member_ `pma::ScopedPtr<TStreamWriter> writer;`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLibTest/Public/GeneSplicerLibTest.h` (Public)


#### class `FGeneSplicerLibTest`  
`class FGeneSplicerLibTest : public IModuleInterface`  
_L10-12_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeneSplicerLibTest, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeneSplicerLibTest, Log, All);`
